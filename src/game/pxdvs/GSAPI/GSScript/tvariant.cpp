#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
    GSvec() {}
};
struct TPCCode { u32 code; };
struct ScriptPeople { u32 group; u32 object; };
struct ScriptObject { u8 reserved[0xA]; u16 id; };

extern "C" {
void OSReport(const char*, ...);
int sprintf(char*, const char*, ...);
char* strncpy(char*, const char*, u32);
char* strcpy(char*, const char*);
char* strcat(char*, const char*);
int strcmp(const char*, const char*);
u32 strlen(const char*);
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
double atof(const char*);
int atoi(const char*);
void* GSmemAlloc(u32);
void GSmemFree(void*);
void PSVECAdd(const GSvec*, const GSvec*, GSvec*);
void PSVECSubtract(const GSvec*, const GSvec*, GSvec*);
void PSVECScale(const GSvec*, GSvec*, f32);
}

class GSBinReadStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    u16 read16() { u16 n = ((u16)current[0] << 8) | (u16)current[1]; current += 2; return n; }
    u32 read32() { u8* p = current; u32 n = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]; current += 4; return n; }
    f32 readFloat() { union { u32 n; f32 f; f64 align; } value; value.n = read32(); return value.f; }
    void read(void* dst, u32 n) { memcpy(dst, current, n); current += n; }
    void skip(u32 n) { current += n; }
};
class GSBinWriteStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    void* allocation;
    u8 writing;
    void write16(u32 n) { if (!writing) current += 2; else { *current++ = n >> 8; *current++ = n; } }
    void write32(u32 n) { if (!writing) current += 4; else { *current++ = n >> 24; *current++ = n >> 16; *current++ = n >> 8; *current++ = n; } }
    void writeFloat(f32 n) { union { u32 n; f32 f; f64 align; } value; value.f = n; write32(value.n); }
    void write(const void* p, u32 n) { if (writing) memcpy(current, p, n); current += n; }
};

namespace GSscript {
void tigaErrMessage(const char*);

struct varPool_t { void* ptr[0x100]; };

struct tigaVariant {
    s16 type;
    s16 flags;
    union { s32 integer; f32 real; void* pointer; } value;

    static const char* getTypeString(int);
    void restoreStateData(GSBinReadStream*);
    void makeStateData(GSBinWriteStream*);
    void setVectorIdx(int, tigaVariant*);
    void condLe(tigaVariant*, tigaVariant*);
    void condLs(tigaVariant*, tigaVariant*);
    void condGe(tigaVariant*, tigaVariant*);
    void condGt(tigaVariant*, tigaVariant*);
    void condNot(tigaVariant*, tigaVariant*);
    void condEqu(tigaVariant*, tigaVariant*);
    void mod(tigaVariant*, tigaVariant*);
    void div(tigaVariant*, tigaVariant*);
    void mul(tigaVariant*, tigaVariant*);
    void sub(tigaVariant*, tigaVariant*);
    void add(tigaVariant*, tigaVariant*);
    char* getCnvString(char*);
    GSvec* getCnvVector();
    f32 getCnvSingle();
    s32 getCnvInteger();

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
    inline const char* getString(char* buf) {
        if (type == 3) return (const char*)value.pointer;
        return getCnvString(buf);
    }
    inline f32 getVX() {
        if (type == 4) return ((GSvec*)value.pointer)->x;
        tigaErrMessage("vec.vx not access");
        return 0.0f;
    }
    inline f32 getVY() {
        if (type == 4) return ((GSvec*)value.pointer)->y;
        tigaErrMessage("vec.vy not access");
        return 0.0f;
    }
    inline f32 getVZ() {
        if (type == 4) return ((GSvec*)value.pointer)->z;
        tigaErrMessage("vec.vz not access");
        return 0.0f;
    }
    inline void setInteger(s32 n) { type = 1; value.integer = n; }
    inline void dupIfNeeded();
    inline void setVec(GSvec* v) {
        type = 4;
        flags = 0;
        value.pointer = v;
        dupIfNeeded();
    }
    inline int getOpType(tigaVariant* b, tigaVariant*& hi, tigaVariant*& lo) {
        if (type == b->type) {
            hi = this;
            lo = b;
            return type;
        }
        int ta = type < 0x40 ? type : 3;
        int tb = b->type < 0x40 ? b->type : 3;
        if (ta == 3) ta = 0x20;
        if (tb == 3) tb = 0x20;
        if (ta > tb) {
            hi = this;
            lo = b;
            if (ta == 0x20) return 3;
            return ta;
        }
        lo = this;
        hi = b;
        if (tb == 0x20) return 3;
        return tb;
    }
};

struct tigaArrayFixed {
    s32 size;
    u32 iter;
    u8 reserved8[8];
    tigaVariant data[1];

    tigaVariant* get(int);
    void set(int, const tigaVariant*);
    void resize(int);
    void push_back(tigaVariant*);
    tigaVariant* fe_get();
    void checkForeach();
    void checkIndex(int);
};

class tigaCellMemory {
public:
    s32 stringCount;
    s32 vectorCount;
    tigaCellMemory();
    virtual ~tigaCellMemory();
    void freeVariant(tigaVariant*);
    void dupVariant(tigaVariant*);
};

struct TigaObjManager {
    GSvec* newVector();
    void deleteVector(GSvec*);
};

class Tiga {
public:
    u8 reserved[0x18];
    TigaObjManager objManager;
    u8 reserved19[0x8F7];
    tigaCellMemory* cellMemory;
    u8 reserved914[0x30];
    TPCCode* codes;
    u8 reserved948[0x18];
    s32 peopleCount;
    ScriptPeople* people;
    s32 objectCount;
    ScriptObject** objects;

    static Tiga* m_cpCurrentObject;

    inline TPCCode* getCode(u32 n) {
        if (n) return &codes[n];
        return 0;
    }
    inline ScriptObject* getObject(s32 i) {
        if (i < 0 || i >= objectCount) return 0;
        return objects[i];
    }
    inline ScriptPeople* searchPeople(u32 group, u32 object) {
        for (int i = 0; i < peopleCount; i++) {
            if (people[i].group == group && people[i].object == object) {
                return &people[i];
            }
        }
        return 0;
    }
};

inline void tigaVariant::dupIfNeeded()
{
    if (type != 1 && type != 2) {
        Tiga::m_cpCurrentObject->cellMemory->dupVariant(this);
    }
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

GSvec nullVec;
varPool_t l_stringPool;
varPool_t l_vectorPool;
static char _tempString[0x100];
static tigaVariant _dummyValue;

static void** varPoolSearchFree(varPool_t* pool)
{
    for (int i = 0; i < 0x100; i++) {
        if (pool->ptr[i] == 0) {
            return &pool->ptr[i];
        }
    }
    return 0;
}

static void** checkAllocedMemory(varPool_t* pool, void* p)
{
    for (int i = 0; i < 0x100; i++) {
        if (pool->ptr[i] == p) {
            return &pool->ptr[i];
        }
    }
    return 0;
}

tigaCellMemory::tigaCellMemory()
{
    nullVec.x = 0.0f;
    nullVec.y = 0.0f;
    nullVec.z = 0.0f;
    stringCount = 0;
    vectorCount = 0;
    memset(&l_stringPool, 0, sizeof(l_stringPool));
    memset(&l_vectorPool, 0, sizeof(l_vectorPool));
}

static inline void freePoolEntry(void*& p)
{
    if (p) {
        GSmemFree(p);
        p = 0;
    }
}

tigaCellMemory::~tigaCellMemory()
{
    if (stringCount != 0 || vectorCount != 0) {
        if (stringCount != 0) {
            for (int i = 0; i < 0x100; i++) {
                if (l_stringPool.ptr[i]) {
                    freePoolEntry(l_stringPool.ptr[i]);
                }
            }
        }
    }
}

void tigaCellMemory::dupVariant(tigaVariant* v)
{
    if (v->type == 3) {
        stringCount++;
        char* p = (char*)GSmemAlloc(0x100);
        strncpy(p, (const char*)v->value.pointer, 0xFF);
        v->value.pointer = p;
        *varPoolSearchFree(&l_stringPool) = p;
    } else if (v->type == 7) {
    } else if (v->type == 4) {
        GSvec* vec = Tiga::m_cpCurrentObject->objManager.newVector();
        if (vec) {
            *vec = *(GSvec*)v->value.pointer;
            v->value.pointer = vec;
        }
    }
}

void tigaCellMemory::freeVariant(tigaVariant* v)
{
    if (v->type == 3) {
        void** slot = checkAllocedMemory(&l_stringPool, v->value.pointer);
        if (slot) {
            *slot = 0;
        } else {
            v->value.pointer = 0;
            v->type = 0;
            return;
        }
        if (v->value.pointer) {
            stringCount--;
            GSmemFree(v->value.pointer);
        }
        v->value.pointer = 0;
        v->type = 0;
    } else if (v->type == 7) {
    } else if (v->type == 4) {
        Tiga::m_cpCurrentObject->objManager.deleteVector((GSvec*)v->value.pointer);
        v->value.pointer = 0;
        v->type = 0;
    }
}

tigaVariant* tigaArrayFixed::get(int i)
{
    if (i < 0 || i >= size) {
        _dummyValue.setInteger(0);
        return &_dummyValue;
    }
    tigaVariant* p = data;
    return p + i;
}

void tigaArrayFixed::set(int i, const tigaVariant* v)
{
    if (i < 0 || i >= size) {
        return;
    }
    data[i] = *v;
}

tigaVariant* tigaArrayFixed::fe_get()
{
    if (iter >= size) {
        _dummyValue.setInteger(0);
        return &_dummyValue;
    }
    tigaVariant* p = data;
    iter++;
    return p + iter - 1;
}

void tigaArrayFixed::resize(int) {}

void tigaArrayFixed::push_back(tigaVariant*) {}

void tigaArrayFixed::checkForeach()
{
    if (iter >= size) {
        OSReport("foreach over index (%d)", iter);
    }
}

void tigaArrayFixed::checkIndex(int i)
{
    if (i < 0 || i >= size) {
        OSReport("over index (%d)", i);
    }
}

s32 tigaVariant::getCnvInteger()
{
    if (type == 3) {
        return atoi((const char*)value.pointer);
    }
    tigaErrMessage("integer convert error");
    return 0;
}

f32 tigaVariant::getCnvSingle()
{
    if (type == 3) {
        return atof((const char*)value.pointer);
    }
    tigaErrMessage("single convert error");
    return 0.0f;
}

GSvec* tigaVariant::getCnvVector()
{
    static GSvec vTemp;
    if (type == 4) {
        return (GSvec*)value.pointer;
    }
    f32 f = getSingle();
    vTemp.x = vTemp.y = vTemp.x = f;
    return &vTemp;
}

char* tigaVariant::getCnvString(char* buf)
{
    if (type == 1) {
        sprintf(buf, "%d", value.integer);
        return buf;
    }
    if (type == 2) {
        sprintf(buf, "%.3f", value.real);
        return buf;
    }
    if (type == 4) {
        GSvec* v = (GSvec*)value.pointer;
        sprintf(buf, "<%.3f,%.3f,%.3f>", v->x, v->y, v->z);
        return buf;
    }
    tigaErrMessage("string convert error");
    buf[0] = 0;
    return buf;
}

void tigaVariant::add(tigaVariant* result, tigaVariant* b)
{
    static char szDest[0x100];
    bool same = b->type == type;
    tigaVariant* hi;
    tigaVariant* lo;
    GSvec tmp;
    char buf[0x100];

    switch (getOpType(b, hi, lo)) {
    case 1:
        result->type = 1;
        result->value.integer = getInteger() + b->getInteger();
        break;
    case 2:
        result->type = 2;
        result->value.real = getSingle() + b->getSingle();
        break;
    case 3:
        strcpy(szDest, getString(buf));
        strcat(szDest, b->getString(buf));
        result->type = 3;
        result->value.pointer = szDest;
        result->dupIfNeeded();
        break;
    case 4:
        result->type = 4;
        if (same) {
            PSVECAdd((GSvec*)value.pointer, (GSvec*)b->value.pointer, &tmp);
            result->value.pointer = &tmp;
            result->dupIfNeeded();
        } else {
            tmp.x = getVX() + lo->getSingle();
            tmp.y = getVY() + lo->getSingle();
            tmp.z = getVZ() + lo->getSingle();
            result->value.pointer = &tmp;
            result->dupIfNeeded();
        }
        break;
    default:
        tigaErrMessage("add convert error");
        break;
    }
}

void tigaVariant::sub(tigaVariant* result, tigaVariant* b)
{
    bool same = b->type == type;
    tigaVariant* hi;
    tigaVariant* lo;
    GSvec tmp;

    switch (getOpType(b, hi, lo)) {
    case 1:
        result->type = 1;
        result->value.integer = getInteger() - b->getInteger();
        break;
    case 2:
        result->type = 2;
        result->value.real = getSingle() - b->getSingle();
        break;
    case 4:
        result->type = 4;
        if (same) {
            PSVECSubtract((GSvec*)value.pointer, (GSvec*)b->value.pointer, &tmp);
            result->value.pointer = &tmp;
            result->dupIfNeeded();
        } else {
            tmp.x = getVX() - lo->getSingle();
            tmp.y = getVY() - lo->getSingle();
            tmp.z = getVZ() - lo->getSingle();
            result->value.pointer = &tmp;
            result->dupIfNeeded();
        }
        break;
    case 3:
    default:
        tigaErrMessage("sub convert error");
        result->setInteger(0);
        break;
    }
}

void tigaVariant::mul(tigaVariant* result, tigaVariant* b)
{
    static char szDest[0x400];
    bool same = b->type == type;
    tigaVariant* hi;
    tigaVariant* lo;
    GSvec tmp;
    char buf[0x100];

    switch (getOpType(b, hi, lo)) {
    case 1:
        result->type = 1;
        result->value.integer = getInteger() * b->getInteger();
        break;
    case 2:
        result->type = 2;
        result->value.real = getSingle() * b->getSingle();
        break;
    case 3: {
        szDest[0] = 0;
        const char* s = hi->getString(buf);
        s32 count = lo->getInteger();
        if (count * strlen(s) > 0xFA) {
            result->type = 3;
            result->value.pointer = (void*)"null";
            result->dupIfNeeded();
            break;
        }
        for (int i = 0; i < count; i++) {
            strcat(szDest, s);
        }
        result->type = 3;
        result->value.pointer = szDest;
        result->dupIfNeeded();
        break;
    }
    case 4:
        result->type = 4;
        if (same) {
            GSvec* va;
            GSvec* vb = (GSvec*)b->value.pointer;
            va = (GSvec*)value.pointer;
            tmp.x = va->x * vb->x;
            tmp.y = va->y * vb->y;
            tmp.z = va->z * vb->z;
            result->value.pointer = &tmp;
            result->dupIfNeeded();
        } else {
            tmp.x = getVX() * lo->getSingle();
            tmp.y = getVY() * lo->getSingle();
            tmp.z = getVZ() * lo->getSingle();
            result->value.pointer = &tmp;
            result->dupIfNeeded();
        }
        break;
    default:
        tigaErrMessage("mul convert error");
        break;
    }
}

void tigaVariant::div(tigaVariant* result, tigaVariant* b)
{
    bool same = b->type == type;
    tigaVariant* hi;
    tigaVariant* lo;
    GSvec tmp;

    switch (getOpType(b, hi, lo)) {
    case 1: {
        result->type = 1;
        s32 d = b->getInteger();
        if (d == 0) {
            tigaErrMessage("integer div 0");
            result->value.integer = 0;
            break;
        }
        result->value.integer = getInteger() / d;
        break;
    }
    case 2: {
        result->type = 2;
        f32 d = b->getSingle();
        if (0.0f == d) {
            tigaErrMessage("single div 0");
            result->value.real = 0.0f;
            break;
        }
        result->value.real = getSingle() / d;
        break;
    }
    case 4:
        result->type = 4;
        if (same) {
            tmp.x = getVX() / b->getVX();
            tmp.y = getVY() / b->getVY();
            tmp.z = getVZ() / b->getVZ();
            result->value.pointer = &tmp;
            result->dupIfNeeded();
        } else {
            f32 d = lo->getSingle();
            GSvec* v = (GSvec*)value.pointer;
            if (0.0f != d) {
                PSVECScale(v, &tmp, 1.0f / d);
            }
            result->value.pointer = &tmp;
            result->dupIfNeeded();
        }
        break;
    case 3:
    default:
        tigaErrMessage("div convert error");
        break;
    }
}

void tigaVariant::mod(tigaVariant* result, tigaVariant* b)
{
    tigaVariant* hi;
    tigaVariant* lo;

    switch (getOpType(b, hi, lo)) {
    case 1:
    case 2: {
        s32 d = b->getInteger();
        if (d == 0) {
            tigaErrMessage("integer mod 0");
        }
        result->setInteger(getInteger() % d);
        break;
    }
    default:
        tigaErrMessage("mod convert error");
        break;
    }
}

static int strcmpw(const char* a, const char* b)
{
    while (*a && *b) {
        if (*a != *b && *a != '?' && *b != '?') {
            if (*a == '*' || *b == '*') {
                return 0;
            }
            return 1;
        }
        a++;
        b++;
    }
    if (!*a && !*b) {
        return 0;
    }
    if (*a) {
        return 1;
    }
    return -1;
}

void tigaVariant::condEqu(tigaVariant* result, tigaVariant* b)
{
    int t;
    bool same = b->type == type;
    result->setInteger(0);
    if (type > b->type) t = type; else t = b->type;
    switch (t) {
    case 1:
        if (getInteger() == b->getInteger()) result->value.integer = 1;
        break;
    case 2:
        if (getSingle() == b->getSingle()) result->value.integer = 1;
        break;
    case 3:
        if (same && strcmpw((const char*)value.pointer, (const char*)b->value.pointer) == 0) result->value.integer = 1;
        break;
    case 4: {
        GSvec d;
        GSvec* vb = b->getVector();
        PSVECSubtract(getVector(), vb, &d);
        d.x = d.x >= 0.0f ? d.x : -d.x;
        d.y = d.y >= 0.0f ? d.y : -d.y;
        d.z = d.z >= 0.0f ? d.z : -d.z;
        if (isZeroVector(&d)) result->value.integer = 1;
        break;
    }
    default:
        tigaErrMessage("equ convert error");
        break;
    }
}

void tigaVariant::condNot(tigaVariant* result, tigaVariant* b)
{
    int t;
    bool same = b->type == type;
    result->setInteger(0);
    if (type > b->type) t = type; else t = b->type;
    switch (t) {
    case 1:
        if (getInteger() != b->getInteger()) result->value.integer = 1;
        break;
    case 2:
        if (getSingle() != b->getSingle()) result->value.integer = 1;
        break;
    case 3:
        if (same && strcmp((const char*)value.pointer, (const char*)b->value.pointer) != 0) result->value.integer = 1;
        break;
    case 4: {
        GSvec d;
        GSvec* vb = b->getVector();
        PSVECSubtract(getVector(), vb, &d);
        d.x = d.x >= 0.0f ? d.x : -d.x;
        d.y = d.y >= 0.0f ? d.y : -d.y;
        d.z = d.z >= 0.0f ? d.z : -d.z;
        if (!isZeroVector(&d)) result->value.integer = 1;
        break;
    }
    default:
        tigaErrMessage("not convert error");
        break;
    }
}

void tigaVariant::condGt(tigaVariant* result, tigaVariant* b)
{
    int t;
    bool same = b->type == type;
    result->setInteger(0);
    if (type > b->type) t = type; else t = b->type;
    switch (t) {
    case 1:
        if (getInteger() > b->getInteger()) result->value.integer = 1;
        break;
    case 2:
        if (getSingle() > b->getSingle()) result->value.integer = 1;
        break;
    case 3:
        if (same && strlen((const char*)value.pointer) > strlen((const char*)b->value.pointer))  result->value.integer = 1;
        break;
    default:
        tigaErrMessage("gt convert error");
        break;
    }
}

void tigaVariant::condGe(tigaVariant* result, tigaVariant* b)
{
    int t;
    bool same = b->type == type;
    result->setInteger(0);
    if (type > b->type) t = type; else t = b->type;
    switch (t) {
    case 1:
        if (getInteger() >= b->getInteger()) result->value.integer = 1;
        break;
    case 2:
        if (getSingle() >= b->getSingle()) result->value.integer = 1;
        break;
    case 3:
        if (same && strlen((const char*)value.pointer) >= strlen((const char*)b->value.pointer))  result->value.integer = 1;
        break;
    default:
        tigaErrMessage("Ge convert error");
        break;
    }
}

void tigaVariant::condLs(tigaVariant* result, tigaVariant* b)
{
    int t;
    bool same = b->type == type;
    result->setInteger(0);
    if (type > b->type) t = type; else t = b->type;
    switch (t) {
    case 1:
        if (getInteger() < b->getInteger()) result->value.integer = 1;
        break;
    case 2:
        if (getSingle() < b->getSingle()) result->value.integer = 1;
        break;
    case 3:
        if (same && strlen((const char*)value.pointer) < strlen((const char*)b->value.pointer))  result->value.integer = 1;
        break;
    default:
        tigaErrMessage("ls convert error");
        break;
    }
}

void tigaVariant::condLe(tigaVariant* result, tigaVariant* b)
{
    int t;
    bool same = b->type == type;
    result->setInteger(0);
    if (type > b->type) t = type; else t = b->type;
    switch (t) {
    case 1:
        if (getInteger() <= b->getInteger()) result->value.integer = 1;
        break;
    case 2:
        if (getSingle() <= b->getSingle()) result->value.integer = 1;
        break;
    case 3:
        if (same && strlen((const char*)value.pointer) <= strlen((const char*)b->value.pointer))  result->value.integer = 1;
        break;
    default:
        tigaErrMessage("le convert error");
        break;
    }
}

void tigaVariant::setVectorIdx(int index, tigaVariant* v)
{
    if (type == 0 || type == 1 || type == 2) {
        GSvec tmp;
        tmp.x = 0.0f;
        tmp.y = 0.0f;
        tmp.z = 0.0f;
        setVec(&tmp);
    }
    if (type != 4) {
        tigaErrMessage("vector set error");
        return;
    }
    GSvec* vec = (GSvec*)value.pointer;
    if (vec == 0) {
        tigaErrMessage("vector error");
        return;
    }
    if (index < 0 || index >= 4) {
        tigaErrMessage("vector index error");
        return;
    }
    (&vec->x)[index] = v->getSingle();
}

void tigaVariant::makeStateData(GSBinWriteStream* stream)
{
    stream->write16(type);
    switch (type) {
    case 0x35:
        if (value.pointer) {
            stream->write32(((u32)value.pointer - (u32)Tiga::m_cpCurrentObject->codes) / sizeof(TPCCode));
        } else {
            stream->write32(0);
        }
        break;
    case 1:
        stream->write32(value.integer);
        break;
    case 2:
        stream->writeFloat(value.real);
        break;
    case 7:
        stream->write32(((ScriptObject*)value.pointer)->id);
        break;
    case 4:
        stream->writeFloat(((GSvec*)value.pointer)->x);
        stream->writeFloat(((GSvec*)value.pointer)->y);
        stream->writeFloat(((GSvec*)value.pointer)->z);
        break;
    case 5:
        stream->write(value.pointer, 0x30);
        break;
    case 0x23:
        stream->write32(((ScriptPeople*)value.pointer)->group);
        stream->write32(((ScriptPeople*)value.pointer)->object);
        break;
    case 3: {
        s32 length = strlen((const char*)value.pointer) + 1;
        stream->write16(length);
        stream->write(value.pointer, length);
        break;
    }
    }
}

void tigaVariant::restoreStateData(GSBinReadStream* stream)
{
    setInteger(0);
    type = stream->read16();
    switch (type) {
    case 0x35: {
        u32 n = stream->read32();
        if (n) {
            value.pointer = &Tiga::m_cpCurrentObject->codes[n];
        } else {
            value.integer = n;
        }
        break;
    }
    case 1:
        value.integer = stream->read32();
        break;
    case 2:
        value.real = stream->readFloat();
        break;
    case 7:
        Tiga* tiga = Tiga::m_cpCurrentObject;
        value.pointer = tiga->getObject(stream->read32());
        if (value.pointer == 0) {
            setInteger(0);
        }
        break;
    case 4: {
        GSvec* v = Tiga::m_cpCurrentObject->objManager.newVector();
        if (v) {
            v->x = stream->readFloat();
            v->y = stream->readFloat();
            v->z = stream->readFloat();
            value.pointer = v;
        } else {
            stream->skip(0xC);
        }
        break;
    }
    case 5:
        stream->read(value.pointer, 0x30);
        break;
    case 0x23: {
        u32 group = stream->read32();
        u32 object = stream->read32();
        value.pointer = Tiga::m_cpCurrentObject->searchPeople(group, object);
        if (value.pointer == 0) {
            setInteger(0);
        }
        break;
    }
    case 3: {
        u16 length = stream->read16();
        stream->read(_tempString, length);
        value.pointer = _tempString;
        dupIfNeeded();
        break;
    }
    }
}

const char* tigaVariant::getTypeString(int t)
{
    static char* commType[] = {
        "type_nodef", "type_integer", "type_single", "type_string", "type_vector",
        "type_matrix", "type_object", "type_tarray", "type_funcptr",
    };
    static char* extendType[] = {
        "cmp_task", "cmp_frame", "cmp_model", "cmp_light", "cmp_texture", "cmp_switch",
        "cmp_frame_motion", "cmp_pad", "cmp_player", "cmp_map", "cmp_enemy", "cmp_camera",
        "cmp_chara", "cmp_adpcm", "cmp_text", "cmp_fog", "cmp_menu", "cmp_blight", "cmp_radio",
        "cmp_item", "cmp_effect", "cmp_sound", "cmp_last",
    };
    if (t < 0) return "type_unknown";
    if (t <= 0x35) return commType[t];
    if (t >= 0x37 && t < 0x38) return extendType[t - 0x40];
    return "type_unknown";
}
}
