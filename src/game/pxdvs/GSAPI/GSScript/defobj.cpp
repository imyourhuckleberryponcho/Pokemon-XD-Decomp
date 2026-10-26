#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
    GSvec() {}
    GSvec(f32 ax, f32 ay, f32 az) : x(ax), y(ay), z(az) {}
};
struct TPCCode { u32 code; };

extern "C" {
int sprintf(char*, const char*, ...);
char* strncpy(char*, const char*, u32);
double acos(double);
void PSVECNormalize(const GSvec*, GSvec*);
void PSVECCrossProduct(const GSvec*, const GSvec*, GSvec*);
f32 PSVECDotProduct(const GSvec*, const GSvec*);
f32 PSVECMag(const GSvec*);
f32 PSVECSquareMag(const GSvec*);
}

namespace GSscript {
struct tigaVariant;
struct tigaCellMemory {
    void freeVariant(tigaVariant*);
    void dupVariant(tigaVariant*);
};
struct tigaArrayFixed {
    s32 size;
    s32 iter;
    tigaVariant* get(int);
    void set(int, const tigaVariant*);
    void resize(int);
    void push_back(tigaVariant*);
    tigaVariant* fe_get();
};
struct tigaVariant {
    s16 type;
    s16 flags;
    union { s32 integer; f32 real; void* pointer; } value;
    s32 getCnvInteger();
    GSvec* getCnvVector();
    f32 getCnvSingle();
    inline f32 getSingle() {
        if (type == 1) return (f32)value.integer;
        if (type == 2) return value.real;
        return getCnvSingle();
    }
    inline s32 getInteger() {
        if (type == 1) return value.integer;
        if (type == 2) return (s32)value.real;
        return getCnvInteger();
    }
    inline GSvec* getVector() {
        if (type == 4) return (GSvec*)value.pointer;
        return getCnvVector();
    }
    inline void setSingle(f32 n) { type = 2; value.real = n; }
    inline void setInteger(s32 n) { type = 1; value.integer = n; }
    inline void clear();
    inline void setVector(GSvec* v);
};
struct TigaContext {
    u8 reserved[0x10];
    tigaVariant result;
    u8 reserved18[0x20];
    char text[0x100];
    GSvec vector;
};
struct TigaThread {
    u8 reserved[0x168];
    u8 waitType;
    u8 waitIndex;
    s32 waitValue;
};
class Tiga {
public:
    u8 reserved[0x8DC];
    s32 threadCount;
    u8 reserved8E0[0x30];
    tigaCellMemory* cellMemory;
    TigaContext* context;
    u8 userFlags[0x10];
    u8 reserved928[0x1C];
    TPCCode* codes;
    u8 reserved948[0x38];
    TigaThread* thread;

    static Tiga* m_cpCurrentObject;

    bool makeThread(TPCCode*, int&, long&);
    void deleteThread(long);
    s32 cmpArray(int, tigaVariant*, tigaVariant*);
    s32 cmpVector(int, tigaVariant*, tigaVariant*);
    s32 cmpThread(int, tigaVariant*, tigaVariant*);

    inline void setRpString(const char* s) {
        strncpy(context->text, s, 0xFF);
        context->result.value.pointer = context->text;
        context->result.type = 3;
    }
    inline void setRpVec(const GSvec* v) {
        context->vector = *v;
        context->result.value.pointer = &context->vector;
        context->result.type = 4;
    }
    inline void setRpVariant(tigaVariant* v, tigaVariant* result) {
        if (v->type == 3) {
            setRpString((const char*)v->value.pointer);
        } else if (v->type == 4) {
            setRpVec((GSvec*)v->value.pointer);
        } else {
            result->type = v->type;
            result->flags = v->flags;
            result->value = v->value;
        }
    }
    inline bool isUserFlagIndex(int i) {
        if (i < 0x10 && i >= 0) return true;
        return false;
    }
    inline void setUserFlag(int i, u8 v) {
        if (isUserFlagIndex(i)) userFlags[i] = v;
    }
    inline u8 getUserFlag(int i) {
        if (isUserFlagIndex(i)) return userFlags[i];
        return 0;
    }
    inline void setWait(u8 type, u8 index, s32 value) {
        TigaThread* t = thread;
        t->waitType = type;
        t->waitIndex = index;
        t->waitValue = value;
    }
};

inline void tigaVariant::clear()
{
    if (type == 1 || type == 2) {
        type = 0;
    } else {
        Tiga::m_cpCurrentObject->cellMemory->freeVariant(this);
        type = 0;
    }
}

inline void tigaVariant::setVector(GSvec* v)
{
    clear();
    type = 4;
    flags = 0;
    value.pointer = v;
    if (type != 1 && type != 2) {
        Tiga::m_cpCurrentObject->cellMemory->dupVariant(this);
    }
}

s32 Tiga::cmpArray(int command, tigaVariant* args, tigaVariant* result)
{
    tigaArrayFixed* array = 0;
    char buf[0x100];

    if (command != 1) {
        array = (tigaArrayFixed*)args[0].value.pointer;
        if (args[0].type != 7 || array == 0) {
            return 0;
        }
    }

    switch (command) {
    case 1:
        break;
    case 3:
        sprintf(buf, "tarray: size=%d", array->size);
        setRpString(buf);
        break;
    case 0x10: {
        s32 size = array->size;
        s32 index = args[1].getInteger();
        if (index >= size) {
            result->setInteger(0);
            break;
        }
        setRpVariant(array->get(index), result);
        break;
    }
    case 0x11: array->set(args[1].getInteger(), &args[2]); break;
    case 0x12: result->setInteger(((tigaArrayFixed*)args[0].value.pointer)->size); break;
    case 0x13: array->resize(args[1].getInteger()); break;
    case 0x19: {
        s32 count = args[1].getInteger();
        tigaVariant* arg = args;
        for (s32 i = 0; i < count; i++) {
            array->push_back(&arg[2]);
            arg++;
        }
        break;
    }
    case 0x14: array->push_back(&args[1]); break;
    case 0x16: array->iter = 0; break;
    case 0x17: setRpVariant(array->fe_get(), result); break;
    case 0x18:
        result->type = 1;
        if (array->size <= array->iter) {
            result->value.integer = 1;
        } else {
            result->value.integer = 0;
        }
        break;
    case 0x1A: break;
    }
    return 0;
}

static inline bool isZeroVector(GSvec* v)
{
    if (v->x < 0.00001f && v->x > -0.00001f
        && v->y < 0.00001f && v->y > -0.00001f
        && v->z < 0.00001f && v->z > -0.00001f) {
        return true;
    }
    return false;
}

s32 Tiga::cmpVector(int command, tigaVariant* args, tigaVariant* result)
{
    GSvec tmp(0.0f, 0.0f, 0.0f);
    GSvec* vec = 0;
    char buf[0x100];

    if (command != 1) {
        if (args[0].type != 4) {
            args[0].setVector(&tmp);
        }
        vec = (GSvec*)args[0].value.pointer;
    }

    switch (command) {
    case 3:
        sprintf(buf, "<%.3f,%.3f,%.3f>", vec->x, vec->y, vec->z);
        setRpString(buf);
        break;
    case 0x10:
        vec->x = vec->y = vec->z = 0.0f;
        break;
    case 0x11: PSVECNormalize(vec, vec); break;
    case 0x12:
        vec->x = args[1].getSingle();
        vec->y = args[2].getSingle();
        vec->z = args[3].getSingle();
        break;
    case 0x13:
        vec->x = args[1].getSingle();
        vec->y = args[2].getSingle();
        vec->z = args[3].getSingle();
        break;
    case 0x14:
        vec->x = vec->y = vec->z = args[1].getSingle();
        break;
    case 0x15:
        vec->x = vec->x >= 0.0f ? vec->x : -vec->x;
        vec->y = vec->y >= 0.0f ? vec->y : -vec->y;
        vec->z = vec->z >= 0.0f ? vec->z : -vec->z;
        break;
    case 0x16:
        vec->x = -vec->x;
        vec->y = -vec->y;
        vec->z = -vec->z;
        break;
    case 0x17:
        if (isZeroVector(vec)) {
            result->setInteger(1);
        } else {
            result->setInteger(0);
        }
        break;
    case 0x18:
        if (args[1].type == 4) {
            PSVECCrossProduct(vec, args[1].getVector(), &tmp);
            setRpVec(&tmp);
        }
        break;
    case 0x19:
        if (args[1].type == 4) {
            result->setSingle(PSVECDotProduct(vec, args[1].getVector()));
        } else {
            result->setSingle(0.0f);
        }
        break;
    case 0x1A: result->setSingle(PSVECMag(vec)); break;
    case 0x1B: result->setSingle(PSVECSquareMag(vec)); break;
    case 0x1C:
        if (args[1].type == 4) {
            GSvec b, a;
            PSVECNormalize(vec, &b);
            PSVECNormalize(args[1].getVector(), &a);
            f32 angle = 57.29578f * (f32)acos(PSVECDotProduct(&b, &a));
            while (angle > 360.0f) angle -= 360.0f;
            while (angle < 0.0f) angle += 360.0f;
            result->setSingle(angle);
        } else {
            result->setSingle(0.0f);
        }
        break;
    }
    return 0;
}

s32 Tiga::cmpThread(int command, tigaVariant* args, tigaVariant* result)
{
    int threadID = 0;
    long handle;
    s32 ret = 0;

    switch (command) {
    case 0x10:
        if (makeThread(&codes[args[1].getInteger()], threadID, handle)) {
            result->setInteger(handle);
        }
        break;
    case 0x11: result->setInteger(threadID); break;
    case 0x12: result->setInteger(threadCount); break;
    case 0x13: deleteThread(args[1].getInteger()); break;
    case 0x14: setUserFlag(args[1].getInteger(), args[2].getInteger()); break;
    case 0x15: result->setInteger(getUserFlag(args[1].getInteger())); break;
    case 0x16:
        if (isUserFlagIndex(args[1].getInteger())) {
            setWait(1, args[1].getInteger(), args[2].getInteger());
            ret = 1;
        }
        break;
    case 0x17:
        if (isUserFlagIndex(args[1].getInteger())) {
            setWait(2, args[1].getInteger(), args[2].getInteger());
            ret = 1;
        }
        break;
    case 0x18:
        break;
    }
    return ret;
}
}
