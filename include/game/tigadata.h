#ifndef GAME_TIGADATA_H
#define GAME_TIGADATA_H
#include <dolphin/types.h>
#include <game/gcdata.h>

struct GSvec;
struct TPCCode;
struct ScriptPeople;
struct FuncEntry;

namespace GSscript {
class Tiga;
class tigaCellMemory;
struct tigaVariant;
struct tigaArrayFixed;
struct TigaContext;
struct TigaThread;

struct tigaWaza { void* sequence; void* waza; };

struct TigaChankView {
#ifdef __MWERKS__
    char* m_data;
    char* m_end;
    s32 m_count;
    void* m_vtable;
#else
    void* m_vtable;
    char* m_data;
    char* m_end;
    s32 m_count;
#endif
};

struct TigaObjManagerView {
    u8 vecUsed[0x80];
    u8 resUsed[0x40];
    f32 vecs[0x80][3];
    s32 res[0x40][2];
};
}

#define GSSCRIPT_TIGA_DATA(CHANK, OBJMANAGER, CONTEXT) \
    CHANK chank;                                       \
    s32 chankSize;                                     \
    u32 ftblId;                                        \
    OBJMANAGER objManager;                             \
    s32 stateId;                                       \
    s32 threadCount;                                   \
    f32 timers[4];                                     \
    ::GSscript::TigaThread* threads[8];                \
    ::GSscript::tigaCellMemory* cellMemory;            \
    CONTEXT* context;                                  \
    u8 userFlags[0x10];                                \
    s32 nextHandle;                                    \
    u8 saveFlag;                                       \
    s32 unk930;                                        \
    s32 wazaCount;                                     \
    ::GSscript::tigaVariant* result;                   \
    s32 codeCount;                                     \
    void* head;                                        \
    ::TPCCode* codes;                                  \
    s32 gvarCount;                                     \
    ::GSscript::tigaVariant* gvars;                    \
    s32 stringCount;                                   \
    char* stringBuffer;                                \
    s32 vectorCount;                                   \
    ::GSvec* vectors;                                  \
    s32 peopleCount;                                   \
    ::ScriptPeople* people;                            \
    s32 arrayCount;                                    \
    gc_ptr32(::GSscript::tigaArrayFixed)* arrays;      \
    s32 funcCount;                                     \
    ::FuncEntry* funcs;                                \
    s32 unk978;                                        \
    u8 unk97C;                                         \
    ::GSscript::TigaThread* thread;

#define GSSCRIPT_TIGA_VIEW_DATA \
    GSSCRIPT_TIGA_DATA(::GSscript::TigaChankView, ::GSscript::TigaObjManagerView, ::GSscript::TigaContext)

#define GSSCRIPT_TIGACONTEXT_DATA(VARIANT, VEC3) \
    ::TPCCode* pc;                              \
    VARIANT* bp;                                \
    VARIANT* sp;                                \
    ::TPCCode** cp;                             \
    VARIANT regs[4];                            \
    VARIANT* stackBase;                         \
    ::TPCCode** callBase;                       \
    char text[0x100];                           \
    VEC3 vector;

#define GSSCRIPT_TIGATHREAD_DATA(CONTEXT, VARIANT) \
    u32 state;                                     \
    f32 sleep;                                     \
    CONTEXT ctx;                                   \
    s32 line;                                      \
    VARIANT* stack;                                \
    s32 stackCount;                                \
    ::TPCCode** callStack;                         \
    s32 callCount;                                 \
    u8 timerIndex;                                 \
    f32 waitTime;                                  \
    u8 waitType;                                   \
    u8 waitIndex;                                  \
    s32 waitValue;                                 \
    ::GSscript::Tiga* owner;                       \
    s32 handle;                                    \
    s32 group;                                     \
    u32 gsThread;

#endif
