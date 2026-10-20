// STATUS: 55/64 exact (9,936 of ~21,900 bytes), CONST OK, .data/.rodata/.sdata2
// LAYOUT OK. Needs extra_cflags=["-inline noauto,deferred"]; functions are written in REVERSE asm order.
// Not exact yet (all register-allocation / scheduling only): execute 99.2% (loop-top `sp` lives in r25
// instead of r6, case 4 scope 2 temps, case 14 zero constants), Tiga::restoreStateData 96.3% (stream/union
// stack slots: target has an unexplained 4-byte hole at sp+0x10), TigaThread::restoreStateData 93.5%,
// setTpcChank 99.7% (base/offset regs swapped), debugDump 98.9% (callee-saved reg numbering),
// getPresetVar 87% (zero reg shared with the type store), tigaErrMessage (target keeps a dead
// lwz+cmplwi), execMethod 99.9% (0x23/0x24 li/or regs), TigaThread::makeStateData 99.9%.
#include <dolphin/types.h>

// GSscript interpreter core: the Tiga virtual machine, its threads and object manager.
#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
    GSvec();
};
struct TPCCode {
    u8 op;
    u8 a;
    union {
        s16 b;
        u16 ub;
    };
};
struct ScriptPeople { u32 group; u32 object; };
struct ScriptObject { u8 reserved[0xA]; u16 id; };
struct GSresID { s32 group; s32 id; };
struct FuncEntry { TPCCode* code; const char* name; };

extern "C" {
void OSReport(const char*, ...);
int sprintf(char*, const char*, ...);
char* strncpy(char*, const char*, u32);
char* strcpy(char*, const char*);
int strncmp(const char*, const char*, u32);
int printf(const char*, ...);
double sin(double);
double cos(double);
double tan(double);
double atan2(double, double);
double acos(double);
char* strcat(char*, const char*);
int strcmp(const char*, const char*);
u32 strlen(const char*);
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
double atof(const char*);
int atoi(const char*);
void* GSmemAlloc(u32);
void GSmemFree(void*);
void* GSgfxLayerFindByName_C(const char*);
void GSprint(void* layer, s32 x, s32 y, u32 color, const char* fmt, ...);
void GSthreadSwitch(void);
void GSthreadTerminate(s32 thread);
void GSthreadSetName(s32 thread, const char* name);
void GSthreadSetArgs(s32 thread, s32 count, ...);
f32 timeGetLastFrameSec(void);
s32 floorCreateThreadLocal(s32, s32, s32, void (*)(void*, s32));
s32 floorGetCurrentFloorGroupID(void);
void PSVECAdd(const GSvec*, const GSvec*, GSvec*);
void PSVECSubtract(const GSvec*, const GSvec*, GSvec*);
void PSVECScale(const GSvec*, GSvec*, f32);
}

extern f32 __float_nan[];
#define NAN (__float_nan[0])
inline int __fpclassifyf(float x)
{
    switch ((*(s32*)&x) & 0x7F800000) {
    case 0x7F800000:
        if ((*(s32*)&x) & 0x007FFFFF) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(s32*)&x) & 0x007FFFFF) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

inline float sqrtf(float x)
{
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (float)(x * guess);
    } else if (x < 0.0) {
        return NAN;
    } else if (__fpclassifyf(x) == 1) {
        return NAN;
    }
    return x;
}

class GSBinReadStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    u8 read8() { return *current++; }
    u16 read16() { u16 n = ((u16)current[0] << 8) | (u16)current[1]; current += 2; return n; }
    u32 read32() { u8* p = current; u32 n = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]; current += 4; return n; }
    f32 readFloat() { union { u32 n; f32 f; f64 align; } value; value.n = read32(); return value.f; }
    void read(void* dst, u32 n) { memcpy(dst, current, n); current += n; }
    void skip(u32 n) { current += n; }
    GSBinReadStream(void* data, s32 length) { begin = current = (u8*)data; size = length; }
};
class GSBinWriteStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    void* allocation;
    u8 writing;
    GSBinWriteStream() { current = 0; allocation = 0; begin = 0; size = 0; writing = 0; }
    ~GSBinWriteStream() { if (allocation) GSmemFree(allocation); }
    void countOnly() { current = 0; allocation = 0; begin = 0; size = 0x10000000; writing = 0; }
    void write8(u32 n) { if (!writing) current++; else *current++ = n; }
    void writeBool(u8 n) { if (!writing) current++; else *current++ = (n != 0); }
    void write16(u32 n) { if (!writing) current += 2; else { *current++ = n >> 8; *current++ = n; } }
    void write32(u32 n) { if (!writing) current += 4; else { *current++ = n >> 24; *current++ = n >> 16; *current++ = n >> 8; *current++ = n; } }
    void writeFloat(f32 n) { union { u32 n; f32 f; f64 align; } value; value.f = n; write32(value.n); }
    void write(const void* p, u32 n) { if (writing) memcpy(current, p, n); current += n; }
    s32 tell() const { return current - begin; }
};

class CChank {
public:
    char* m_data;
    char* m_end;
    s32 m_count;

    CChank();
    virtual ~CChank() {}
    char* searchSubChankID(const char* id);
    char* searchChankID(const char* id, long no);
};

class CChankBlock : public CChank {
public:
    virtual ~CChankBlock() {}
    BOOL loadFromMemory(char* data, char* id);
};

void* operator new(u32);
void* operator new[](u32);
void operator delete(void*);
void operator delete[](void*);

namespace GSscript {
void tigaErrMessage(const char*);

struct Tiga;
struct tigaVariant;

class tigaCellMemory {
public:
    s32 stringCount;
    s32 vectorCount;
    tigaCellMemory();
    virtual ~tigaCellMemory();
    void freeVariant(tigaVariant*);
    void dupVariant(tigaVariant*);
};

struct tigaArrayFixed {
    s32 size;
    u32 iter;
    u8 flag;
    u8 reserved9;
    u16 index;
    u8 reservedC[4];
    tigaVariant* get(int);
};

struct tigaVariant {
    s16 type;
    s16 flags;
    union { s32 integer; f32 real; void* pointer; } value;

    void restoreStateData(GSBinReadStream*);
    void makeStateData(GSBinWriteStream*);
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
    static const char* getTypeString(int);
    inline void setInteger(s32 n) { type = 1; value.integer = n; }
    inline void setSingle(f32 n) { type = 2; value.real = n; }
    inline void clear();
    inline void dupIfNeeded();
    inline void assign(tigaVariant* src) {
        type = src->type;
        flags = src->flags;
        value = src->value;
    }
};

struct TigaContext {
    TPCCode* pc;
    tigaVariant* bp;
    tigaVariant* sp;
    TPCCode** cp;
    tigaVariant regs[4];
    tigaVariant* stackBase;
    TPCCode** callBase;
    char text[0x100];
    f32 vector[3];
};

struct TigaObjManager {
    u8 vecUsed[0x80];
    u8 resUsed[0x40];
    GSvec vecs[0x80];
    GSresID res[0x40];

    TigaObjManager();
    ~TigaObjManager();
    void clear();
    void* newVector();
    void deleteVector(GSvec*);
    void addVectorIdx(GSvec*);
    s32 getVectorIdx(GSvec*);
    void* newResource();
    s32 getResourceIdx(GSresID*);
    void* getResource(int);
};

struct TigaThread {
    u32 state;
    f32 sleep;
    TigaContext ctx;
    s32 line;
    tigaVariant* stack;
    s32 stackCount;
    TPCCode** callStack;
    s32 callCount;
    u8 timerIndex;
    f32 waitTime;
    u8 waitType;
    u8 waitIndex;
    s32 waitValue;
    Tiga* owner;
    s32 handle;
    s32 group;
    u32 gsThread;

    TigaThread();
    ~TigaThread();
    void setSaveFlag(bool);
    void stop();
    s32 restoreStateData(GSBinReadStream*);
    void makeStateData(GSBinWriteStream*);
    bool checkSleepEnd();
    void initTiga();
    void setStackArea(int, int);
    void free();
};

struct Tiga {
public:
    CChankBlock chank;
    s32 chankSize;
    u32 ftblId;
    TigaObjManager objManager;
    s32 stateId;
    s32 threadCount;
    f32 timers[4];
    TigaThread* threads[8];
    tigaCellMemory* cellMemory;
    TigaContext* context;
    u8 userFlags[0x10];
    s32 nextHandle;
    u8 saveFlag;
    s32 unk930;
    s32 wazaCount;
    tigaVariant* result;
    s32 codeCount;
    void* head;
    TPCCode* codes;
    s32 gvarCount;
    tigaVariant* gvars;
    s32 stringCount;
    char* stringBuffer;
    s32 vectorCount;
    GSvec* vectors;
    s32 peopleCount;
    ScriptPeople* people;
    s32 arrayCount;
    tigaArrayFixed** arrays;
    s32 funcCount;
    FuncEntry* funcs;
    s32 unk978;
    u8 unk97C;
    TigaThread* thread;

    static Tiga* m_cpCurrentObject;

    inline bool isUserFlagIndex(int i) {
        if (i < 0x10 && i >= 0) return true;
        return false;
    }
    inline u8 getUserFlag(int i) {
        if (isUserFlagIndex(i)) return userFlags[i];
        return 0;
    }

    inline void setRpString(const char* s) {
        strncpy(context->text, s, 0xFF);
        context->regs[0].value.pointer = context->text;
        context->regs[0].type = 3;
    }
    inline void setTimerWait(u8 index, f32 time) {
        TigaThread* t = thread;
        t->timerIndex = index;
        t->waitTime = time;
        t->state |= 4;
    }
    bool cmpArray(int, tigaVariant*, tigaVariant*);
    bool cmpVector(int, tigaVariant*, tigaVariant*);
    bool cmpThread(int, tigaVariant*, tigaVariant*);

    Tiga();
    virtual bool execExtendMethod(int, int, tigaVariant*, tigaVariant*);
    virtual bool execExtendGlobalFunction(int, tigaVariant*, tigaVariant*);
    virtual s32 getExtendVariable(tigaVariant*, int, int);
    virtual s32 setExtendVariable(tigaVariant*, int, int);
    virtual void mapping() {}
    virtual void unmapping() {}
    virtual ~Tiga();

    void debugDump();
    s32 getStateSize();
    s32 restoreStateData(void*, u32);
    void makeStateData(GSBinWriteStream*);
    s32 getNameToFuncId(const char*);
    s32 getResultValue(long);
    TPCCode* getIdToCodeAdress(int);
    ScriptPeople* searchResID(u32, u32);
    void setPresetVar(tigaVariant*, int, int);
    void getPresetVar(tigaVariant*, int, int);
    bool execMethod(int, int, tigaVariant*, tigaVariant*);
    s32 execute(TigaThread*);
    void calcExpr2(int, tigaVariant*, tigaVariant*, tigaVariant*);
    void calcExpr1(int, tigaVariant*, tigaVariant*);
    s32 executeOneThread(f32, long);
    s32 executeThread(f32);
    void unblockThread(long);
    void blockThread(long);
    void unblockThreadGroup(u32);
    void blockThreadGroup(u32);
    void deleteThreadGroup(u32);
    bool isRunningThread(long);
    void deleteThread(long);
    TigaThread* getHandleToThread(long);
    bool makeThread(TPCCode*, int&, long&);
    s32 runParamsWait(int, tigaVariant*, int, tigaVariant*);
    s32 runParamsPC(TPCCode*, tigaVariant*, int, bool);
    s32 runParams(int, tigaVariant*, int, bool);
    s32 setTpcChank(CChank*);
    void unmappingScript();
    void mappingScript(char*);
    void free();
};

inline void tigaVariant::dupIfNeeded()
{
    if (type != 1 && type != 2) {
        Tiga::m_cpCurrentObject->cellMemory->dupVariant(this);
    }
}

inline void tigaVariant::clear()
{
    if (type == 1 || type == 2) {
        type = 0;
    } else {
        Tiga::m_cpCurrentObject->cellMemory->freeVariant(this);
        type = 0;
    }
}

struct CurrentGuard {
    Tiga* prev;
    CurrentGuard(Tiga* t) { prev = Tiga::m_cpCurrentObject; Tiga::m_cpCurrentObject = t; }
    ~CurrentGuard() { Tiga::m_cpCurrentObject = prev; }
};

struct ChankRec {
    char tag[4];
    s32 size;
    s32 no;
    u32 unkC;
    s32 count;
    s32 unk14;
    s32 id;
    s32 unk1C;
    u8 data[1];
};

// The original reported the message through a debug print that is stripped from retail.
void tigaErrMessage(const char* msg)
{
    if (Tiga::m_cpCurrentObject != 0) {
        const char* m = msg;
    }
}

static void _executeScriptThread(Tiga* t, long id)
{
    t->executeOneThread(timeGetLastFrameSec(), id);
    while (t->isRunningThread(id)) {
        GSthreadSwitch();
        if (!t->isRunningThread(id)) break;
        t->executeOneThread(timeGetLastFrameSec(), id);
    }
}

TigaObjManager::TigaObjManager()
{
    clear();
}

TigaObjManager::~TigaObjManager() {}

void TigaObjManager::clear()
{
    memset(vecUsed, 0, 0x80);
    memset(resUsed, 0, 0x40);
}

void* TigaObjManager::newVector()
{
    s8* p = (s8*)vecUsed;
    s32 i = 0;
    for (; p <= (s8*)&vecUsed[0x80]; p++, i++) {
        if (*p == 0) {
            *p = 1;
            vecs[i].x = 0.0f;
            vecs[i].y = 0.0f;
            vecs[i].z = 0.0f;
            return &vecs[i];
        }
    }
    return 0;
}

void TigaObjManager::deleteVector(GSvec* v)
{
    s32 i = getVectorIdx(v);
    if (i >= 0) {
        u8 c = vecUsed[i];
        if ((s8)c > 0) vecUsed[i] = c - 1;
    }
}

s32 TigaObjManager::getVectorIdx(GSvec* v)
{
    if (v < &vecs[0] || v >= &vecs[0x80]) return -1;
    s32 i = ((u8*)v - (u8*)&vecs[0]) / 12;
    if (i < 0 || i >= 0x80) return -1;
    return i;
}

void TigaObjManager::addVectorIdx(GSvec* v)
{
    s32 i = getVectorIdx(v);
    if (i >= 0) vecUsed[i]++;
}

void* TigaObjManager::newResource()
{
    s32 i = 0;
    for (s8* p = (s8*)resUsed; p <= (s8*)&resUsed[0x40]; p++, i++) {
        if (*p == 0) {
            *p = 1;
            res[i].group = 0;
            res[i].id = 0;
            return &res[i];
        }
    }
    return 0;
}

s32 TigaObjManager::getResourceIdx(GSresID* p)
{
    if (p < &res[0] || p >= &res[0x40]) return -1;
    s32 i = p - res;
    if (i < 0 || i >= 0x40) return -1;
    return i;
}

void* TigaObjManager::getResource(int i)
{
    if (i < 0 || i >= 0x40) return 0;
    return &res[i];
}

TigaThread::TigaThread()
{
    state = 0;
    stack = 0;
    callStack = 0;
    memset(&ctx, 0, 0x144);
    gsThread = 0;
    setStackArea(0x100, 0x80);
}

TigaThread::~TigaThread()
{
    free();
}

void TigaThread::free()
{
    ctx.regs[0].clear();
    if (stack) {
        delete[] stack;
        stack = 0;
    }
    if (callStack) {
        delete[] callStack;
        callStack = 0;
    }
    state = 0;
}

void TigaThread::setStackArea(int a, int b)
{
    free();
    stack = new tigaVariant[a];
    callStack = new TPCCode*[b];
    stackCount = a;
    callCount = b;
}

void TigaThread::initTiga()
{
    memset(&ctx, 0, 0x144);
    ctx.sp = stack + stackCount;
    ctx.cp = callStack + callCount;
    ctx.stackBase = stack;
    ctx.callBase = callStack;
    ctx.sp = ctx.sp - 1;
    ctx.sp->type = 0x35;
    ctx.sp->value.integer = 0;
    ctx.bp = ctx.sp;
    line = 0;
    state = 0;
    group = 0;
    gsThread = 0;
}

bool TigaThread::checkSleepEnd()
{
    if (state & 4) {
        if (owner->timers[timerIndex] >= waitTime) {
            state &= ~4;
        } else {
            return false;
        }
    }
    if (waitType != 0) {
        if (waitType == 2) {
            if (waitValue != owner->getUserFlag(waitIndex)) return false;
        } else if (waitType == 1) {
            if (owner->getUserFlag(waitIndex) >= waitValue) return false;
        }
        waitType = 0;
    }
    return true;
}

void TigaThread::makeStateData(GSBinWriteStream* s)
{    s32 i;
    if (!(state & 0x10)) s->write32(state);
    else s->write32(0);
    s->writeFloat(sleep);
    u32 cpIdx = ((u32)ctx.cp - (u32)ctx.callBase) >> 2;
    u32 pcIdx = ((u32)ctx.pc - (u32)owner->codes) >> 2;
    s->write32(pcIdx);
    s->write32(((u32)ctx.bp - (u32)ctx.stackBase) >> 3);
    s->write32(((u32)ctx.sp - (u32)ctx.stackBase) >> 3);
    s->write32(cpIdx);
    for (i = 0; i < 4; i++) ctx.regs[i].makeStateData(s);
    s->write32(line);
    s->write32(stackCount);
    for (i = 0; i < stackCount; i++) stack[i].makeStateData(s);
    s->write32(callCount);
    for (i = 0; i < callCount; i++) {
        s->write32((u32)(((u32)&callStack[i] - (u32)ctx.callBase) >> 2));
    }
    s->write8(timerIndex);
    s->writeFloat(waitTime);
    s->write8(waitType);
    s->write8(waitIndex);
    s->write32(waitValue);
}

s32 TigaThread::restoreStateData(GSBinReadStream* s)
{
    int i;
    state = s->read32();
    sleep = s->readFloat();
    u32 pcIndex = s->read32();
    u32 bpIndex = s->read32();
    u32 spIndex = s->read32();
    u32 cpIndex = s->read32();
    ctx.pc = owner->codes + pcIndex;
    ctx.bp = ctx.stackBase + bpIndex;
    ctx.sp = ctx.stackBase + spIndex;
    ctx.cp = ctx.callBase + cpIndex;
    for (i = 0; i < 4; i++) ctx.regs[i].restoreStateData(s);
    line = s->read32();
    stackCount = s->read32();
    for (i = 0; i < stackCount; i++) stack[i].restoreStateData(s);
    callCount = s->read32();
    for (i = 0; i < callCount; i++) callStack[i] = (TPCCode*)(ctx.stackBase + s->read32());
    timerIndex = s->read8();
    waitTime = s->readFloat();
    waitType = s->read8();
    waitIndex = s->read8();
    waitValue = s->read32();
    return 1;
}

void TigaThread::stop()
{
    state = 0;
    if (gsThread != 0) {
        GSthreadTerminate(gsThread);
        gsThread = 0;
    }
}

void TigaThread::setSaveFlag(bool on)
{
    if (state != 0) {
        if (on) {
            state &= ~0x10;
            return;
        }
        state |= 0x10;
    }
}

Tiga::Tiga()
{
    if (m_cpCurrentObject == 0) m_cpCurrentObject = this;
    codeCount = 0;
    gvarCount = 0;
    unk930 = 0;
    thread = 0;
    unk978 = 0x200;
    unk97C = 0;
    nextHandle = 1;
    cellMemory = new tigaCellMemory;
    for (s32 i = 0; i < 8; i++) {
        threads[i] = new TigaThread;
        threads[i]->owner = this;
    }
    for (f32* p = timers; p < &timers[4]; p++) *p = 0.0f;
    memset(userFlags, 0, 0x10);
    wazaCount = 0;
    result = 0;
}

Tiga::~Tiga()
{
    free();
    delete cellMemory;
}

void Tiga::free()
{
    m_cpCurrentObject = this;
    s32 j, i;
    for (i = 0; i < gvarCount; i++) {
        gvars[i].clear();
    }
    for (j = 0; j < 8; j++) {
        delete threads[j];
    }
    result = 0;
}

s32 Tiga::setExtendVariable(tigaVariant*, int, int) { return 0; }
s32 Tiga::getExtendVariable(tigaVariant*, int, int) { return 0; }
bool Tiga::execExtendGlobalFunction(int, tigaVariant*, tigaVariant*) { return 0; }
bool Tiga::execExtendMethod(int, int, tigaVariant*, tigaVariant*) { return 0; }

void Tiga::mappingScript(char* data)
{
    wazaCount = 0;
    for (f32* p = timers; p < &timers[4]; p++) *p = 0.0f;
    chank.loadFromMemory(data, 0);
    setTpcChank(&chank);
}

void Tiga::unmappingScript()
{
    codeCount = 0;
    head = 0;
    codes = 0;
    gvarCount = 0;
    gvars = 0;
    stringCount = 0;
    stringBuffer = 0;
    vectorCount = 0;
    vectors = 0;
    peopleCount = 0;
    people = 0;
    funcCount = 0;
    funcs = 0;
    chank.loadFromMemory(0, 0);
    result = 0;
    unmapping();
    objManager.clear();
}

s32 Tiga::setTpcChank(CChank* c)
{
    if (c == 0) {
        unmappingScript();
        return 0;
    }
    thread = 0;
    threadCount = 0;
    chankSize = ((ChankRec*)c->m_data)->size;
    ftblId = 0;
    ChankRec* h = (ChankRec*)c->searchChankID("HEAD", 0);
    if (h == 0) return 0;
    codeCount = h->count;
    h->id = 1;
    head = h->data;
    ChankRec* r = (ChankRec*)c->searchChankID("CODE", 0);
    if (r == 0) return 0;
    codes = (TPCCode*)r->data;
    r = (ChankRec*)c->searchChankID("GVAR", 0);
    if (r == 0) return 0;
    gvarCount = r->count;
    gvars = (tigaVariant*)r->data;
    r = (ChankRec*)c->searchChankID("STRG", 0);
    if (r == 0) return 0;
    stringCount = r->count;
    stringBuffer = (char*)r->data;
    r = (ChankRec*)c->searchChankID("VECT", 0);
    if (r == 0) return 0;
    vectorCount = r->count;
    vectors = (GSvec*)r->data;
    r = (ChankRec*)c->searchChankID("GIRI", 0);
    if (r != 0) {
        peopleCount = r->count;
        people = (ScriptPeople*)r->data;
    }
    r = (ChankRec*)c->searchChankID("FTBL", 0);
    if (r != 0) {
        funcCount = r->count;
        ftblId = r->id;
        funcs = (FuncEntry*)r->data;
        for (FuncEntry* p = funcs; p != funcs + funcCount; p++) {
            p->code = codes + (u32)p->code;
            p->name = (const char*)r + (u32)p->name;
        }
    } else {
        funcs = 0;
    }
    r = (ChankRec*)c->searchChankID("ARRY", 0);
    if (r != 0) {
        u8* base = (u8*)r + 0x10;
        int i = 0;
        arrayCount = *(s32*)base;
        arrays = (tigaArrayFixed**)(base + 0x10);
        for (; i < arrayCount; i++) {
            arrays[i] = (tigaArrayFixed*)(base + (u32)arrays[i]);
            arrays[i]->index = i;
        }
    } else {
        arrayCount = 0;
        arrays = 0;
    }
    mapping();
    return 1;
}

s32 Tiga::runParams(int funcId, tigaVariant* args, int count, bool useThread)
{
    if (codeCount == 0) return 0;
    if ((funcId >> 16) == 0) return 0;
    int id = (u16)funcId;
    if (id >= codeCount || id < 0) return 0;
    TPCCode* code = getIdToCodeAdress(id);
    return runParamsPC(code, args, count, useThread);
}

s32 Tiga::runParamsPC(TPCCode* code, tigaVariant* args, int count, bool useThread)
{
    int index;
    long handle;
    TigaThread* prev = thread;
    if (makeThread(code, index, handle)) {
        thread = threads[index];
        TigaThread* t = threads[index];
        tigaVariant* sp = t->ctx.sp;
        for (int i = 0; i < count; i++) {
            sp--;
            sp->assign(&args[count - i - 1]);
            sp->flags = 0;
        }
        sp--;
        sp->type = 0x35;
        sp->flags = 0;
        sp->value.integer = 0;
        t->ctx.sp = sp;
        t->ctx.cp--;
        *t->ctx.cp = (TPCCode*)t->ctx.bp;
        t->ctx.bp = sp;
        if (useThread) {
            s32 g = floorCreateThreadLocal(1, 0x2000, 1, (void (*)(void*, s32))_executeScriptThread);
            GSthreadSetName(g, "GSscript thread");
            GSthreadSetArgs(g, 2, this, handle);
            t->gsThread = g;
        } else {
            execute(t);
        }
        thread = prev;
        return t->handle;
    }
    thread = prev;
    return 0;
}

s32 Tiga::runParamsWait(int id, tigaVariant* args, int count, tigaVariant* out)
{
    s32 handle = runParams(id, args, count, false);
    if (handle == 0) return 0;
    while (isRunningThread(handle)) {
        executeOneThread(timeGetLastFrameSec(), handle);
        if (!isRunningThread(handle)) break;
        GSthreadSwitch();
    }
    if (out) {
        tigaVariant* r = result;
        out->type = r->type;
        out->flags = r->flags;
        out->value = r->value;
    }
    return 1;
}

bool Tiga::makeThread(TPCCode* code, int& index, long& handle)
{
    s32 i = 0;
    TigaThread** p = threads;
    for (; p < &threads[8]; p++, i++) {
        if ((*p)->state == 0) {
            (*p)->initTiga();
            handle = nextHandle;
            (*p)->handle = nextHandle;
            (*p)->group = floorGetCurrentFloorGroupID();
            TigaThread* t = *p;
            t->ctx.pc = code;
            t->state = 1;
            t->sleep = 0.0f;
            threadCount++;
            index = i;
            nextHandle++;
            if (nextHandle == 0) nextHandle = 1;
            return true;
        }
    }
    return false;
}

TigaThread* Tiga::getHandleToThread(long id)
{
    for (TigaThread** p = threads; p < &threads[8]; p++) {
        TigaThread* t = *p;
        if (t->state != 0 && id == t->handle) return t;
    }
    return 0;
}

void Tiga::deleteThread(long id)
{
    TigaThread* t = getHandleToThread(id);
    if (t) {
        t->stop();
        threadCount--;
    }
}

bool Tiga::isRunningThread(long id)
{
    TigaThread* t = getHandleToThread(id);
    if (t) return t->state != 0;
    return false;
}

void Tiga::deleteThreadGroup(u32 group)
{
    for (TigaThread** p = threads; p < &threads[8]; p++) {
        TigaThread* t = *p;
        if (t->state != 0 && group == t->group) deleteThread(t->handle);
    }
}

void Tiga::blockThreadGroup(u32 group)
{
    for (TigaThread** p = threads; p < &threads[8]; p++) {
        TigaThread* t = *p;
        if (t->state != 0 && group == t->group) blockThread(t->handle);
    }
}

void Tiga::unblockThreadGroup(u32 group)
{
    for (TigaThread** p = threads; p < &threads[8]; p++) {
        TigaThread* t = *p;
        if (t->state != 0 && group == t->group) unblockThread(t->handle);
    }
}

void Tiga::blockThread(long id)
{
    TigaThread* t = getHandleToThread(id);
    if (t) {
        if (t->state != 0) t->state |= 2;
    }
}

void Tiga::unblockThread(long id)
{
    TigaThread* t = getHandleToThread(id);
    if (t) t->state &= ~2;
}

s32 Tiga::executeThread(f32 dt)
{
    Tiga* prev = m_cpCurrentObject;
    m_cpCurrentObject = this;
    saveFlag = 0;
    for (f32* p = timers; p < &timers[4]; p++) *p += dt;
    m_cpCurrentObject = prev;
    return 0;
}

s32 Tiga::executeOneThread(f32 dt, long id)
{
    TigaThread* prevThread;
    TigaThread* t = getHandleToThread(id);
    if (t == 0) return 0;
    Tiga* prevObject = m_cpCurrentObject;
    m_cpCurrentObject = this;
    saveFlag = 0;
    if (t->state == 0) return 0;
    if (t->state & 2) return 1;
    prevThread = thread;
    thread = t;
    if (t->sleep > 0.0f) t->sleep -= dt;
    if (t->checkSleepEnd()) {
        if (t->sleep <= 0.0f) execute(t);
    }
    thread = prevThread;
    m_cpCurrentObject = prevObject;
    return 1;
}

void Tiga::calcExpr1(int op, tigaVariant* result, tigaVariant* a)
{
    char buf[0x100];
    result->type = a->type;
    result->flags = a->flags;
    result->value = a->value;
    switch (op) {
    case 0x10:
        if (a->type == 1) {
            result->value.integer = ~a->value.integer;
        } else if (a->type == 2) {
            result->value.real = ~(s32)a->value.real;
        }
        break;
    case 0x11:
        if (a->type == 1) {
            result->value.integer = -a->value.integer;
        } else if (a->type == 2) {
            result->value.real = -a->value.real;
        } else if (a->type == 4) {
            GSvec* v = (GSvec*)result->value.pointer;
            v->x = -v->x;
            v = (GSvec*)result->value.pointer;
            v->y = -v->y;
            v = (GSvec*)result->value.pointer;
            v->z = -v->z;
        }
        break;
    case 0x12:
        buf[0] = 0;
        if (a->type == 1) {
            sprintf(buf, "%08x", a->value.integer);
        } else if (a->type == 2) {
            sprintf(buf, "%08x", (s32)a->value.real);
        }
        result->type = 3;
        result->value.pointer = buf;
        result->dupIfNeeded();
        break;
    case 0x13:
        buf[0] = 0;
        if (a->type == 1) {
            sprintf(buf, "%d", a->value.integer);
        } else if (a->type == 2) {
            sprintf(buf, "%.3f", a->value.real);
        } else if (a->type == 2) {
            return;
        } else if (a->type == 4) {
            GSvec* v = (GSvec*)a->value.pointer;
            sprintf(buf, "<%.3f, %.3f, %.3f>", v->x, v->y, v->z);
        }
        result->type = 3;
        result->value.pointer = buf;
        result->dupIfNeeded();
        break;
    case 0x14:
        if (a->type == 2) {
            result->type = 1;
            result->value.integer = (s32)a->value.real;
        } else if (a->type == 3) {
            result->type = 1;
            result->value.integer = atoi((const char*)a->value.pointer);
        }
        break;
    case 0x15:
        if (a->type == 1) {
            result->type = 2;
            result->value.real = (f32)a->value.integer;
        } else if (a->type == 3) {
            result->type = 2;
            result->value.real = atof((const char*)a->value.pointer);
        }
        break;
    case 0x16:
        result->setSingle(a->getVX());
        break;
    case 0x17:
        result->setSingle(a->getVY());
        break;
    case 0x18:
        result->setSingle(a->getVZ());
        break;
    case 0x19:
        result->setSingle(0.0f);
        break;
    }
}

void Tiga::calcExpr2(int op, tigaVariant* result, tigaVariant* a, tigaVariant* b)
{
    switch (op) {
    case 0x20:
        result->setInteger(a->getInteger() ^ b->getInteger());
        break;
    case 0x21:
        result->setInteger(a->getInteger() | b->getInteger());
        break;
    case 0x22:
        result->setInteger(a->getInteger() & b->getInteger());
        break;
    case 0x23:
        a->add(result, b);
        break;
    case 0x24:
        a->sub(result, b);
        break;
    case 0x25:
        a->mul(result, b);
        break;
    case 0x26:
        a->div(result, b);
        break;
    case 0x27:
        a->mod(result, b);
        break;
    case 0x30:
        a->condEqu(result, b);
        break;
    case 0x31:
        a->condGt(result, b);
        break;
    case 0x32:
        a->condGe(result, b);
        break;
    case 0x33:
        a->condLs(result, b);
        break;
    case 0x34:
        a->condLe(result, b);
        break;
    case 0x35:
        a->condNot(result, b);
        break;
    }
}

s32 Tiga::execute(TigaThread* t)
{
    bool running = true;
    TigaContext* prevContext;
    Tiga* prevObject;
    TigaContext* c = &t->ctx;
    tigaVariant tmp;
    prevObject = m_cpCurrentObject;
    m_cpCurrentObject = this;
    prevContext = context;
    context = c;
    while (running) {
        if (t->ctx.sp <= t->stack) break;
        TPCCode* pc = c->pc;
        switch (pc->op) {
        case 0:
            c->pc++;
            break;
        case 1:
            if (pc->a < 0x20) {
                calcExpr1(pc->a, &tmp, t->ctx.sp);
                t->ctx.sp->clear();
            } else {
                calcExpr2(pc->a, &tmp, t->ctx.sp + 1, t->ctx.sp);
                t->ctx.sp->clear();
                t->ctx.sp++;
                t->ctx.sp->clear();
            }
            t->ctx.sp->assign(&tmp);
            c->pc++;
            break;
        case 2: {
            u8 vtype = pc->a;
            u16 index = pc->b;
            t->ctx.sp = t->ctx.sp - 1;
            t->ctx.sp->type = vtype;
            t->ctx.sp->flags = 0;
            if (vtype <= 2) {
                c->pc++;
                t->ctx.sp->value.integer = *(s32*)c->pc;
            } else if (vtype == 0x35) {
                t->ctx.sp->type = 1;
                c->pc++;
                t->ctx.sp->value.integer = *(s32*)c->pc;
            } else if (vtype == 3) {
                t->ctx.sp->value.pointer = stringBuffer + index;
            } else if (vtype == 4) {
                t->ctx.sp->value.pointer = &vectors[index];
            } else if (vtype == 0x2C) {
                t->ctx.sp->value.pointer = &people[index];
            }
            if (t->ctx.sp->type != 1 && t->ctx.sp->type != 2) {
                m_cpCurrentObject->cellMemory->dupVariant(t->ctx.sp);
            }
            c->pc++;
            break;
        }
        case 3: {
            u8 scope = pc->a & 0xF;
            s16 index = pc->b;
            t->ctx.sp = t->ctx.sp - 1;
            if (scope == 0) {
                t->ctx.sp->assign(&gvars[index]);
            } else if (scope == 1) {
                t->ctx.sp->assign(&t->ctx.bp[index]);
            } else if (scope == 2) {
                t->ctx.sp->assign(&t->ctx.regs[index]);
            } else if (scope == 3) {
                getPresetVar(t->ctx.sp, index, 0);
            }
            if (t->ctx.sp->type != 1 && t->ctx.sp->type != 2) {
                m_cpCurrentObject->cellMemory->dupVariant(t->ctx.sp);
            }
            c->pc++;
            break;
        }
        case 0x11: {
            u8 scope = pc->a & 0xF;
            s16 index = pc->b;
            t->ctx.sp = t->ctx.sp - 1;
            if (scope == 0) {
                tigaVariant* var = &gvars[index];
                if (c->pc[1].a == 4 && var->type != 4) {
                    var->clear();
                    GSvec* vec = (GSvec*)objManager.newVector();
                    var->type = 4;
                    var->flags = 0;
                    var->value.pointer = vec;
                }
                t->ctx.sp->assign(&gvars[index]);
            } else if (scope == 1) {
                tigaVariant* var = &t->ctx.bp[index];
                if (c->pc[1].a == 4 && var->type != 4) {
                    var->clear();
                    GSvec* vec = (GSvec*)objManager.newVector();
                    var->type = 4;
                    var->flags = 0;
                    var->value.pointer = vec;
                }
                t->ctx.sp->assign(&t->ctx.bp[index]);
            } else if (scope == 2) {
                if (c->pc[1].a == 4) {
                    tigaVariant* var = &t->ctx.regs[index];
                    if (t->ctx.regs[index].type != 4) {
                        var->clear();
                        GSvec* vec = (GSvec*)objManager.newVector();
                        t->ctx.regs[index].type = 4;
                        t->ctx.regs[index].flags = 0;
                        t->ctx.regs[index].value.pointer = vec;
                    }
                }
                t->ctx.sp->assign(&t->ctx.regs[index]);
            } else if (scope == 3) {
                getPresetVar(t->ctx.sp, index, 0);
            }
            if (t->ctx.sp->type == 4) {
                objManager.addVectorIdx(t->ctx.sp->getVector());
            }
            c->pc++;
            break;
        }
        case 4: {
            u8 scope = pc->a & 0xF;
            s16 index = pc->b;
            if (scope == 0) {
                tigaVariant* var = &gvars[index];
                var->clear();
                gvars[index].assign(t->ctx.sp);
            } else if (scope == 1) {
                tigaVariant* var = &t->ctx.bp[index];
                var->clear();
                t->ctx.bp[index].assign(t->ctx.sp);
            } else if (scope == 2) {
                tigaVariant* var = &t->ctx.regs[index];
                var->clear();
                tigaVariant* src = t->ctx.sp;
                t->ctx.regs[index].type = src->type;
                t->ctx.regs[index].flags = src->flags;
                t->ctx.regs[index].value = src->value;
            } else if (scope == 3) {
                setPresetVar(t->ctx.sp, index, 0);
            }
            tigaVariant* top = t->ctx.sp;
            top->type = 0;
            top->value.integer = 0;
            t->ctx.sp++;
            c->pc++;
            break;
        }
        case 5: {
            u8 scope = pc->a & 0xF;
            u8 sub = (pc->a >> 4) & 0xF;
            s16 index = pc->b;
            if (scope == 0) {
                gvars[index].setVectorIdx(sub, t->ctx.sp);
            } else if (scope == 1) {
                t->ctx.bp[index].setVectorIdx(sub, t->ctx.sp);
            } else if (scope == 2) {
                t->ctx.regs[index].setVectorIdx(sub, t->ctx.sp);
            } else if (scope == 3) {
                setPresetVar(t->ctx.sp, index, sub);
            }
            tigaVariant* top = t->ctx.sp;
            top->type = 0;
            top->value.integer = 0;
            t->ctx.sp++;
            c->pc++;
            break;
        }
        case 6: {
            int n = pc->a;
            int i;
            for (i = 0; i < n; i++) {
                t->ctx.sp->clear();
                t->ctx.sp++;
            }
            c->pc++;
            break;
        }
        case 7:
            t->ctx.sp = t->ctx.sp - 1;
            t->ctx.sp->type = 0x35;
            t->ctx.sp->value.integer = (s32)(c->pc + 1);
            c->pc = &codes[(c->pc->a << 16) + c->pc->ub];
            t->ctx.cp--;
            *t->ctx.cp = (TPCCode*)t->ctx.bp;
            t->ctx.bp = t->ctx.sp;
            break;
        case 8: {
            TPCCode* retPc;
            t->ctx.bp = (tigaVariant*)*t->ctx.cp;
            t->ctx.cp++;
            retPc = (TPCCode*)t->ctx.sp->value.pointer;
            if (retPc != 0) {
                c->pc = retPc;
                tigaVariant* top = t->ctx.sp;
                top->type = 0;
                top->value.integer = 0;
                t->ctx.sp++;
            } else {
                result = &t->ctx.regs[0];
                t->ctx.sp++;
                t->stop();
                threadCount--;
                running = false;
            }
            break;
        }
        case 9:
            {
                bool r = execMethod(pc->a, pc->b, t->ctx.sp, &t->ctx.regs[0]);
                context = &t->ctx;
                if (r) running = false; else running = true;
            }
            c->pc++;
            break;
        case 10: {
            if (t->ctx.sp->value.integer != 0) {
                c->pc = &codes[(c->pc->a << 16) + c->pc->ub];
            } else {
                c->pc = pc + 1;
            }
            tigaVariant* top = t->ctx.sp;
            top->type = 0;
            top->value.integer = 0;
            t->ctx.sp++;
            break;
        }
        case 11: {
            if (t->ctx.sp->value.integer == 0) {
                c->pc = &codes[(c->pc->a << 16) + c->pc->ub];
            } else {
                c->pc = pc + 1;
            }
            tigaVariant* top = t->ctx.sp;
            top->type = 0;
            top->value.integer = 0;
            t->ctx.sp++;
            break;
        }
        case 12:
            c->pc = &codes[(c->pc->a << 16) + c->pc->ub];
            break;
        case 13: {
            int n = pc->a;
            int i;
            for (i = 0; i < n; i++) {
                t->ctx.sp = t->ctx.sp - 1;
                tigaVariant* top = t->ctx.sp;
                top->type = 0;
                top->value.integer = 0;
            }
            c->pc++;
            break;
        }
        case 14: {
            int n = pc->a;
            int i;
            for (i = 0; i < (u8)n; i++) {
                t->ctx.sp->clear();
                t->ctx.sp++;
            }
            c->pc++;
            break;
        }
        case 15:
            running = false;
            t->stop();
            threadCount--;
            c->pc++;
            break;
        case 16:
            t->line = pc->b;
            c->pc++;
            break;
        }
    }
    context = prevContext;
    m_cpCurrentObject = prevObject;
    return 1;
}

bool Tiga::execMethod(int type, int cmd, tigaVariant* args, tigaVariant* result)
{
    char buf[0x100];
    bool ret = false;
    result->type = 1;
    result->value.integer = 0;
    if (type == 0) {
        switch (cmd) {
        case 0x10:
            break;
        case 0x11:
            thread->sleep = args[0].getSingle();
            ret = true;
            break;
        case 0x12: {
            int i;
            for (i = 0; i < args[0].getInteger(); i++) {
                GSthreadSwitch();
            }
            break;
        }
        case 0x15: {
            if (args[0].getInteger() >= 4) {
                tigaErrMessage("timer error");
            }
            setTimerWait(args[0].getInteger(), args[1].getSingle());
            ret = true;
            break;
        }
        case 0x14:
            if (args[0].getInteger() >= 4) {
                tigaErrMessage("timer error");
            }
            result->setSingle(timers[args[0].getInteger()]);
            break;
        case 0x13: {
            if (args[0].getInteger() >= 4) {
                tigaErrMessage("timer error");
            }
            int index = args[0].getInteger();
            timers[index] = args[1].getSingle();
            break;
        }
        case 0x16:
            printf(args[0].getString(buf));
            break;
        case 0x17:
            break;
        case 0x19:
        case 0x1A:
            break;
        case 0x1C:
            result->setInteger(args[0].type);
            break;
        case 0x1D:
            setRpString(tigaVariant::getTypeString(args[0].type));
            break;
        case 0x30:
            result->setSingle((f32)sin(0.017453292f * args[0].getSingle()));
            break;
        case 0x31:
            result->setSingle((f32)cos(0.017453292f * args[0].getSingle()));
            break;
        case 0x32:
            result->setSingle((f32)tan(0.017453292f * args[0].getSingle()));
            break;
        case 0x33: {
            f32 x = args[1].getSingle();
            f32 y = args[0].getSingle();
            result->setSingle(57.29578f * (f32)atan2(y, x));
            break;
        }
        case 0x34:
            result->setSingle(57.29578f * (f32)acos(args[0].getSingle()));
            break;
        case 0x35:
            result->setSingle(sqrtf(args[0].getSingle()));
            break;
        case 0x21:
            result->setInteger(args[0].getInteger() | (1 << args[1].getInteger()));
            break;
        case 0x22:
            result->setInteger(args[0].getInteger() & ~(1 << args[1].getInteger()));
            break;
        case 0x23: {
            int a = args[0].getInteger();
            int b = args[1].getInteger();
            result->setInteger(a | b);
            break;
        }
        case 0x24: {
            int a = args[0].getInteger();
            int b = args[1].getInteger();
            result->setInteger(a & ~b);
            break;
        }
        case 0x1E: {
            const char* s = args[0].getString(buf);
            int index = args[1].getInteger();
            if (s != 0 && index >= 0 && strlen(s) > index) {
                char c = s[index];
                result->setInteger((u8)c);
                break;
            }
            result->setInteger(0);
            break;
        }
        case 0x1F:
            buf[0] = args[0].getInteger();
            buf[1] = 0;
            setRpString(buf);
            break;
        case 0x20: {
            const char* s = args[0].getString(buf);
            char buf2[0x100];
            const char* sub = args[0].getString(buf2);
            int i;
            unsigned long len = strlen(sub);
            i = 0;
            for (; *s; s++, i++) {
                if (strncmp(s, sub, len) == 0) {
                    result->setInteger(i);
                    break;
                }
            }
            result->setInteger(-1);
            break;
        }
        default:
            return execExtendGlobalFunction(cmd, args, result);
        }
    } else if (type == 0x36) {
        ret = cmpThread(cmd, args, result);
    } else if (type == 4) {
        ret = cmpVector(cmd, args, result);
    } else if (type == 7) {
        ret = cmpArray(cmd, args, result);
    } else {
        return execExtendMethod(type, cmd, args, result);
    }
    return ret;
}

void Tiga::getPresetVar(tigaVariant* v, int id, int arg)
{
    s32 n;
    n = 0;
    v->type = 0;
    switch (id) {
    case 5:
        v->type = 1;
        n = thread ? thread->handle : 0;
        v->value.integer = n;
        break;
    default:
        getExtendVariable(v, id, arg);
        break;
    }
}

void Tiga::setPresetVar(tigaVariant* v, int id, int arg)
{
    setExtendVariable(v, id, arg);
}

ScriptPeople* Tiga::searchResID(u32 group, u32 object)
{
    for (ScriptPeople* p = people; p != people + peopleCount; p++) {
        if (p->group == group && p->object == object) return p;
    }
    return 0;
}

TPCCode* Tiga::getIdToCodeAdress(int id)
{
    int n = (u16)id;
    if (n < 0 || n > funcCount) return 0;
    return funcs[n].code;
}

s32 Tiga::getResultValue(long)
{
    tigaVariant* v = result;
    if (v && (v->type == 1 || v->type == 2)) return v->getInteger();
    return 0;
}

s32 Tiga::getNameToFuncId(const char* name)
{
    s32 i = 0;
    if (codeCount == 0) return 0;
    for (FuncEntry* e = funcs; e != funcs + funcCount; e++, i++) {
        if (strcmp(e->name, name) == 0) return i | 0x01000000;
    }
    return 0;
}

void Tiga::makeStateData(GSBinWriteStream* stream)
{
    s32 i, j, k;
    stream->write32(0);
    stream->write32(stateId);
    stream->write32(ftblId);
    stream->write32(chankSize);
    stream->write32(threadCount);
    for (i = 0; i < 4; i++) stream->writeFloat(timers[i]);
    for (i = 0; i < 16; i++) stream->write8(userFlags[i]);
    stream->write32(nextHandle);
    stream->writeBool(saveFlag);
    stream->write32(unk930);
    stream->write32(gvarCount);
    for (i = 0; i < gvarCount; i++) gvars[i].makeStateData(stream);
    stream->write32(arrayCount);
    for (i = 0; i < arrayCount; i++) {
        stream->writeBool(arrays[i]->flag);
        if (arrays[i]->flag == 0) {
            stream->write32(arrays[i]->size);
            for (k = 0; k < arrays[i]->size; k++) arrays[i]->get(k)->makeStateData(stream);
        }
    }
    stream->write32(8);
    for (j = 0; j < 8; j++) threads[j]->makeStateData(stream);
}

s32 Tiga::restoreStateData(void* data, u32 length)
{
    GSBinReadStream stream(data, length);
    s32 t;
    s32 handle;
    u32 n;
    CurrentGuard guard(this);
    if (length == 0) return 0;
    if (stream.read32() != 0) return 0;
    stateId = stream.read32();
    u32 id = stream.read32();
    if (id != ftblId && (id != 0 || ftblId != 0)) return 0;
    if (chankSize != stream.read32()) return 0;
    threadCount = stream.read32();
    for (s32 i = 0; i < 4; i++) {
        n = stream.read32();
        timers[i] = *(f32*)&n;
    }
    for (s32 i = 0; 16 > i; i++) userFlags[i] = stream.read8();
    nextHandle = stream.read32();
    saveFlag = stream.read8() != 0;
    unk930 = stream.read32();
    gvarCount = stream.read32();
    for (s32 i = 0; i < gvarCount; i++) gvars[i].restoreStateData(&stream);
    arrayCount = stream.read32();
    for (s32 i = 0; i < arrayCount; i++) {
        if (stream.read8() == 0) {
            stream.read32();
            for (s32 j = 0; j < arrays[i]->size; j++) arrays[i]->get(j)->restoreStateData(&stream);
        }
    }
    s32 count = 8;
    s32 nthreads = stream.read32();
    if (nthreads < 8) count = nthreads;
    for (s32 i = 0; i < count; i++) {
        threads[i]->initTiga();
        threads[i]->restoreStateData(&stream);
        if (threads[i]->state != 0) {
            threads[i]->handle = nextHandle++;
            threads[i]->group = floorGetCurrentFloorGroupID();
            if (nextHandle == 0) nextHandle = 1;
        }
    }
    for (s32 i = 0; i < count; i++) {
        if (threads[i]->state != 0) {
            handle = threads[i]->handle;
            t = floorCreateThreadLocal(1, 0x2000, 1, (void (*)(void*, s32))_executeScriptThread);
            GSthreadSetName(t, "GSscript thread");
            GSthreadSetArgs(t, 2, this, handle);
            threads[i]->gsThread = t;
        }
    }
    return 1;
}

s32 Tiga::getStateSize()
{
    GSBinWriteStream stream;
    stream.countOnly();
    makeStateData(&stream);
    return stream.tell();
}

void Tiga::debugDump()
{
    GSprint(GSgfxLayerFindByName_C("debug menu"), 0x10, 0x28, 0xE0D0FFFF, "run thread size = %d", threadCount);
    GSprint(GSgfxLayerFindByName_C("debug menu"), 0x10, 0x34, 0xE0D0FFFF, "timer");
    GSprint(GSgfxLayerFindByName_C("debug menu"), 0x3C, 0x34, 0xE0D0FFFF, "%3.1f", timers[0]);
    GSprint(GSgfxLayerFindByName_C("debug menu"), 0x6C, 0x34, 0xE0D0FFFF, "%3.1f", timers[1]);
    GSprint(GSgfxLayerFindByName_C("debug menu"), 0x9C, 0x34, 0xE0D0FFFF, "%3.1f", timers[2]);
    GSprint(GSgfxLayerFindByName_C("debug menu"), 0xCC, 0x34, 0xE0D0FFFF, "%3.1f", timers[3]);
    GSprint(GSgfxLayerFindByName_C("debug menu"), 0x10, 0x40, 0xE0D0FFFF, "- : Line  sp  ");
    GSprint(GSgfxLayerFindByName_C("debug menu"), 0x10, 0x4C, 0xE0D0FFFF, "------------------");
    u32 sp;
    s32 y;
    s32 i;
    for (i = 0, y = 0x58; i < 8; i++, y += 0xC) {
        TigaThread* t = threads[i];
        if (t->state == 0) {
            GSprint(GSgfxLayerFindByName_C("debug menu"), 0x10, y, 0xE0D0FFFF, "%d : --", i);
        } else {
            sp = ((u32)t->ctx.sp - (u32)t->ctx.stackBase) >> 3;
            FuncEntry* found = 0;
            for (FuncEntry* e = funcs; e != funcs + funcCount; e++) {
                FuncEntry* prev = found;
                found = e;
                if (e->code == t->ctx.pc) break;
                if (e->code > t->ctx.pc) { found = prev; break; }
            }
            const char* name;
            if (found == 0) name = "unknown";
            else name = found->name;
            GSprint(GSgfxLayerFindByName_C("debug menu"), 0x10, y, 0xE0D0FFFF, "%d : %4d %3d %s", i, t->line, sp, name);
        }
    }
}

Tiga* Tiga::m_cpCurrentObject;
}
