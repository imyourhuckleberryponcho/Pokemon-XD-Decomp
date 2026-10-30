#include <dolphin/types.h>
#pragma peephole off
#pragma pool_strings off
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct FloorData;
enum FloorEnterMode { FloorEnterMode_draft_dummy };
struct FloorModuleEntry;
struct FloorModuleInterface;
struct FloorModuleList;
enum FloorModuleType { FloorTypeFunc, FloorTypeGSvm, FloorTypeTpc, FloorTypeSingleGSvm, FloorTypeSingleTpc, FloorTypeAny };
struct FloorScriptModule;
enum FloorState { FloorState_draft_dummy };
enum FloorStateMode { FloorStateMode_draft_dummy };
struct FloorModuleInterface {
    u32 data[7];
    void (*pushState)(FloorStateMode mode, void* buf, u32 size);
    void (*popState)(FloorStateMode mode, void* buf, u32 size);
    u32 (*getPushSize)(FloorStateMode mode);
    u32 (*getID)();
};
struct GSthread;
struct ScriptTpcNode;

struct FloorModuleInterface;

namespace GSscript {
class tigaVariant;
class Tiga {
public:
    void blockThread(long thread);
    void blockThreadGroup(unsigned long group);
    void unblockThreadGroup(unsigned long group);
    void deleteThreadGroup(unsigned long group);
    void unblockThread(long thread);
    void deleteThread(long thread);
    u8 isRunningThread(long thread);
    s32 runParams(int func, tigaVariant* args, int count, bool now);
};
}
GSscript::Tiga* floorGetCommonScript();
GSscript::Tiga* floorGetCurentScript();

class ScriptTpcNode {
public:
    void setID(u32 id);

    u32 id;
    u32 script;
public:
    void block();
    void exec(unsigned char, unsigned long, FloorEnterMode);
    u8 isRunning();
    void unblock();
    void terminate();
    GSscript::Tiga* getScript();
};

class FloorModuleEntry {
public:
    FloorModuleEntry* getNext() const;
    bool isBlock() const;
    FloorModuleType getType() const;
    u32 getGroupID() const;
    FloorModuleEntry* getPrev() const;
    u32 getHandle() const;
    void setHandle(u32 handle);
    void setPrev(FloorModuleEntry* entry);
    void setNext(FloorModuleEntry* entry);
    u8 getPriority() const;
    bool isEmpty() const;

    FloorModuleEntry* prev;
    FloorModuleEntry* next;
    u32 handle;
    u32 unkC;
    FloorModuleType type;
    u32 groupID;
    u8 priority;
    bool blocked;
    u8 started;
    u8 unk1B;
    u8 module[0x2C];
public:
    FloorModuleEntry();
    void init();
    u8 isScriptRunning(FloorState);
    bool isTpcScript() const;
    void setModule(unsigned char, unsigned long, FloorModuleInterface*);
    void block();
    FloorModuleInterface* getModuleInterface();
    void setScriptModule(unsigned char, unsigned long, unsigned long, unsigned long, unsigned long);
    void exec(FloorState, unsigned int, FloorEnterMode);
    void terminate();
    void kill();
    void unblock();
};

namespace GSscript {
class tigaVariant {
public:
    void setInteger(long value);

    u16 type;
    s32 value;
};
}

extern "C++" {
struct FloorData {
    u8 _draft[1];
};
struct FloorModuleList {
    FloorModuleEntry* entries;
    u32 count;
    u32 nextHandle;
    FloorModuleEntry* head;
    u32 pushSize;
    void restorePopState(void*, FloorStateMode, bool);
    void removeFuncFromList(FloorModuleEntry*);
    void waitFloorScript(FloorState);
    FloorModuleEntry* findFree();
    void insertFuncIntoList(FloorModuleEntry*);
    FloorModuleEntry* getFMEEnd();
    void unblockModule(unsigned long);
    void* makePushState(FloorStateMode);
    u8 executeIsDone(FloorState);
    void unregisterModuleGroup(unsigned long);
    void blockModule(unsigned long);
    void killModule(unsigned long);
    void killModuleGroup(unsigned long);
    void blockModuleGroup(unsigned long);
    u32 getNewHandle();
    FloorModuleEntry* findHandle(unsigned long);
    virtual ~FloorModuleList();
    FloorModuleList(unsigned long);
    void executeAll(unsigned int, FloorState, FloorModuleType, FloorEnterMode, unsigned long);
    u32 registerScriptModule(unsigned char, unsigned long, unsigned long, unsigned long, unsigned long);
    void unblockModuleGroup(unsigned long);
    void unregisterModule(unsigned long);
    u32 registerModule(unsigned char, unsigned long, FloorModuleInterface*);
    void dumpModule();
};
struct FloorScriptModule {
    ScriptTpcNode init;
    ScriptTpcNode enter;
    ScriptTpcNode exit;
    void setIDs(unsigned long, unsigned long, unsigned long);
    void exec(FloorState, unsigned char, unsigned long, FloorEnterMode);
    ScriptTpcNode* stateToNode(FloorState);
    u8 isRunning(FloorState);
    void unblock();
    void terminate();
    void kill();
    void block();
};
struct GSthread {
    u8 _draft[1];
};

extern "C" {
void FloorModuleInterface_clear(FloorModuleInterface*);
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
void GSthreadSetName(GSthread*, const char*);
void GSthreadSwitch(void);
u32 __construct_new_array(void*, s32, s32, s32);
void* floorCreateThread(s32 a, u32 stackSize, s32 c, void* func);
u32 floorDataBiosGetGroupID(FloorData* floor);
FloorData* floorDataBiosGetPtr(u32 key);
void* memset(void* dst, int val, size_t n);
extern s32 this_;
s32 __ct__16FloorModuleEntryFv(s32);
}
extern "C++" {
static void _dispModuleName(FloorModuleInterface* p0, const char* p1);
static const char* _floorStateToStr(FloorState p0);
}

extern "C" {
}

extern "C" {
u8 FloorModuleInterface_exec(s32 *p0, s32 p1, s32 p2, s32 p3, bool p4);
}

#pragma push
#pragma dont_inline on
void FloorModuleList::dumpModule() {
}
#pragma pop
extern "C++" {
void FloorModuleList::restorePopState(void* state, FloorStateMode mode, bool free) {
    if (state == 0) {
        return;
    }
    dumpModule();
    u8* p = (u8*)state + 8;
    u8* end = (u8*)state + ((u32*)state)[1];
    if (((u32*)state)[0] != 0x464C4F52) {
        return;
    }
    while (p < end) {
        u32* hdr = (u32*)p;
        p += 8;
        u32 id = hdr[0];
        u32 size = hdr[1];
        for (FloorModuleEntry* entry = head; entry != 0; entry = entry->getNext()) {
            FloorModuleInterface* iface = entry->getModuleInterface();
            if (iface != 0 && iface->getPushSize != 0 && id == iface->getID()) {
                iface->popState(mode, p, size - 8);
                p += size - 8;
                break;
            }
        }
    }
    if (free) {
        GSmemFree(state);
    }
}
}

extern "C++" {
#pragma push
#pragma dont_inline on
void FloorModuleList::killModuleGroup(unsigned long group) {
    FloorModuleEntry* entry;
    for (entry = head; entry != NULL; entry = entry->getNext()) {
        if (group == entry->getGroupID()) {
            killModule(entry->getHandle());
        }
    }
    floorGetCommonScript()->deleteThreadGroup(group);
    floorGetCurentScript()->deleteThreadGroup(group);
}
extern "C++" {
#pragma push
#pragma dont_inline on
void FloorModuleList::unblockModuleGroup(unsigned long group) {
    FloorModuleEntry* entry;
    for (entry = head; entry != NULL; entry = entry->getNext()) {
        if (group == entry->getGroupID()) {
            unblockModule(entry->getHandle());
        }
    }
    floorGetCommonScript()->unblockThreadGroup(group);
    floorGetCurentScript()->unblockThreadGroup(group);
}
extern "C++" {
#pragma push
#pragma dont_inline on
void FloorModuleList::blockModuleGroup(unsigned long group) {
    FloorModuleEntry* entry;
    for (entry = head; entry != NULL; entry = entry->getNext()) {
        if (group == entry->getGroupID()) {
            blockModule(entry->getHandle());
        }
    }
    floorGetCommonScript()->blockThreadGroup(group);
    floorGetCurentScript()->blockThreadGroup(group);
}
void FloorModuleList::unregisterModuleGroup(unsigned long group) {
    FloorModuleEntry* entry;
    for (entry = entries; entry != &entries[count]; entry++) {
        if (group == entry->getGroupID()) {
            unregisterModule(entry->getHandle());
        }
    }
}
#pragma pop
}
#pragma pop
}
#pragma pop
}

}

extern "C++" {
void FloorModuleList::waitFloorScript(FloorState p0) {
    while (((FloorModuleList*)(this))->executeIsDone((FloorState)(p0)) == 0) {
        GSthreadSwitch();
    }
}
}

extern "C++" {
#pragma peephole off
u8 FloorModuleList::executeIsDone(FloorState state) {
    FloorModuleEntry* entry;
    for (entry = head; entry != NULL; entry = entry->getNext()) {
        if (!entry->isBlock() && entry->isScriptRunning(state)) {
            return 0;
        }
    }
    return 1;
}
#pragma peephole reset
}

extern "C++" {
void FloorModuleList::executeAll(unsigned int arg, FloorState state, FloorModuleType type, FloorEnterMode mode, unsigned long group) {
    FloorModuleEntry* entry;
    FloorModuleEntry* prev;
    FloorModuleEntry* next;

    if (state == 6 || state == 8) {
        entry = getFMEEnd();
        while (entry != 0) {
            prev = entry->getPrev();
            if ((group == entry->getGroupID() || entry->isBlock() == 0) && (type == 0xFF || type == entry->getType())) {
                entry->exec(state, arg, mode);
            }
            if (entry->getPrev() != 0) {
                entry = entry->getPrev();
            } else {
                entry = prev;
            }
        }
        return;
    }
    entry = head;
    while (entry != 0) {
        next = entry->getNext();
        if ((group == entry->getGroupID() || entry->isBlock() == 0) && (type == 0xFF || type == entry->getType())) {
            entry->exec(state, arg, mode);
        }
        if (entry->getNext() != 0) {
            entry = entry->getNext();
        } else {
            entry = next;
        }
    }
}
}

extern "C++" {
extern "C++" {
void* FloorModuleList::makePushState(FloorStateMode mode) {
    FloorModuleInterface* iface;
    u32 size;
    u8* p;
    u8* data;
    u32 total;
    FloorModuleEntry* entry;

    dumpModule();
    total = 0;
    for (entry = head; entry != 0; entry = entry->getNext()) {
        iface = entry->getModuleInterface();
        if (iface != 0 && iface->getPushSize != 0) {
            size = iface->getPushSize(mode);
            if (size != 0) {
                total += ((size + 3) & ~3) + 8;
            }
        }
    }
    u32* state = (u32*)GSmemAlloc(total + 8);
    if (state == 0) {
        return 0;
    }
    pushSize = total + 8;
    state[0] = 0x464C4F52;
    p = (u8*)(state + 2);
    state[1] = total + 8;
    for (entry = head; entry != 0; entry = entry->getNext()) {
        iface = entry->getModuleInterface();
        if (iface != 0 && iface->getPushSize != 0) {
            size = iface->getPushSize(mode);
            if (size == 0) {
                if (mode == 3) {
                    iface->pushState(mode, 0, 0);
                }
            } else {
                size = (size + 3) & ~3;
                if (iface->getID == 0) {
                    return 0;
                }
                ((u32*)p)[0] = iface->getID();
                data = p + 8;
                ((u32*)p)[1] = size + 8;
                iface->pushState(mode, data, size);
                p = data + size;
            }
        }
    }
    return state;
}
}

extern "C++" {
extern "C++" {
extern "C++" {
extern "C++" {
extern "C++" {
void FloorModuleList::killModule(unsigned long p0) {
    FloorModuleEntry *temp_r3;

    temp_r3 = (FloorModuleEntry *)(this->findHandle(p0));
    if (temp_r3 != NULL) {
        ((FloorModuleEntry*)(temp_r3))->kill();
    }
}
extern "C++" {
void FloorModuleList::unblockModule(unsigned long p0) {
    u32 temp_r3;

    temp_r3 = (unsigned long)(this->findHandle(p0));
    if (temp_r3 != 0) {
        ((FloorModuleEntry*)((FloorModuleEntry *) temp_r3))->unblock();
    }
}
}

extern "C++" {
void FloorModuleList::blockModule(unsigned long p0) {
    u32 temp_r3;

    temp_r3 = (unsigned long)(this->findHandle(p0));
    if (temp_r3 != 0) {
        ((FloorModuleEntry*)((FloorModuleEntry *) temp_r3))->block();
    }
}
}

extern "C++" {
void FloorModuleList::unregisterModule(unsigned long p0) {
    u32 temp_r3;

    temp_r3 = (unsigned long)(this->findHandle(p0));
    if (temp_r3 != 0) {
        ((FloorModuleEntry*)((FloorModuleEntry *) temp_r3))->terminate();
        this->removeFuncFromList((FloorModuleEntry*)((FloorModuleEntry *) temp_r3));
        ((FloorModuleEntry*)((FloorModuleEntry *) temp_r3))->init();
    }
}
}

extern "C++" {
void FloorModuleList::removeFuncFromList(FloorModuleEntry* p0) {
    u32 temp_r31;
    u32 temp_r31_2;

    if (((FloorModuleEntry*)(p0))->getPrev() != 0) {
        temp_r31 = (unsigned long)(((FloorModuleEntry*)(p0))->getPrev());
        ((FloorModuleEntry*)((FloorModuleEntry *) temp_r31))->setNext((FloorModuleEntry*)(((FloorModuleEntry*)(p0))->getNext()));
    }
    if (((FloorModuleEntry*)(p0))->getNext() != 0) {
        temp_r31_2 = (unsigned long)(((FloorModuleEntry*)(p0))->getNext());
        ((FloorModuleEntry*)((FloorModuleEntry *) temp_r31_2))->setPrev((FloorModuleEntry*)(((FloorModuleEntry*)(p0))->getPrev()));
    }
    if ((u32) M2C_FIELD(this, u32 *, 0xC) == (u32)(p0)) {
        M2C_FIELD(this, u32 *, 0xC) = (unsigned long)(((FloorModuleEntry*)(p0))->getNext());
    }
    ((FloorModuleEntry*)(p0))->setPrev((FloorModuleEntry*)(NULL));
    ((FloorModuleEntry*)(p0))->setNext((FloorModuleEntry*)(NULL));
}
}

extern "C++" {
FloorModuleEntry* FloorModuleList::findHandle(unsigned long handle) {
    FloorModuleEntry* entry;
    for (entry = entries; entry != &entries[count]; entry++) {
        if (!entry->isEmpty() && handle == entry->getHandle()) {
            return entry;
        }
    }
    return NULL;
}
}

extern "C++" {
FloorModuleEntry* FloorModuleList::findFree() {
    FloorModuleEntry* entry;
    if (entries == NULL) {
        return NULL;
    }
    for (entry = entries; entry != &entries[count]; entry++) {
        if (entry->isEmpty()) {
            return entry;
        }
    }
    return NULL;
}
}

extern "C++" {
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
}

}

extern "C++" {
extern "C++" {
extern "C++" {
extern "C++" {
#pragma push
#pragma peephole off
u32 FloorModuleList::registerScriptModule(unsigned char p0, unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4) {
    FloorModuleEntry *temp_r3;

    temp_r3 = (FloorModuleEntry *)(((FloorModuleList*)(this))->findFree());
    if (temp_r3 == NULL) {
        return 0U;
    }
    ((FloorModuleEntry*)(temp_r3))->init();
    ((FloorModuleEntry*)(temp_r3))->setScriptModule(p0, p1, p2, p3, p4);
    ((FloorModuleList*)(this))->insertFuncIntoList((FloorModuleEntry*)(temp_r3));
    ((FloorModuleEntry*)(temp_r3))->setHandle(((FloorModuleList*)(this))->getNewHandle());
    return ((FloorModuleEntry*)(temp_r3))->getHandle();
}
#pragma pop
}

extern "C++" {
#pragma push
#pragma peephole off
u32 FloorModuleList::registerModule(unsigned char p0, unsigned long p1, FloorModuleInterface* p2) {
    FloorModuleEntry *temp_r3;

    if (p2 == NULL) {
        return 0U;
    }
    temp_r3 = (FloorModuleEntry *)(((FloorModuleList*)(this))->findFree());
    if (temp_r3 == NULL) {
        return 0U;
    }
    ((FloorModuleEntry*)(temp_r3))->init();
    ((FloorModuleEntry*)(temp_r3))->setModule(p0, p1, (FloorModuleInterface*)(p2));
    ((FloorModuleList*)(this))->insertFuncIntoList((FloorModuleEntry*)(temp_r3));
    ((FloorModuleEntry*)(temp_r3))->setHandle(((FloorModuleList*)(this))->getNewHandle());
    return ((FloorModuleEntry*)(temp_r3))->getHandle();
}
#pragma pop
}

extern "C++" {
extern "C++" {
void FloorModuleList::insertFuncIntoList(FloorModuleEntry* entry) {
    if (M2C_FIELD(this, FloorModuleEntry **, 0xC) == NULL) {
        M2C_FIELD(this, FloorModuleEntry **, 0xC) = entry;
        return;
    }
    FloorModuleEntry* cur = M2C_FIELD(this, FloorModuleEntry **, 0xC);
    while (cur->getNext() != NULL) {
        if (!(cur->getPriority() < entry->getPriority())) {
            break;
        }
        cur = cur->getNext();
    }
    if (cur->getNext() == NULL && cur->getPriority() < entry->getPriority()) {
        entry->setPrev(cur);
        entry->setNext(NULL);
        cur->setNext(entry);
        return;
    }
    if (cur->getPrev() != NULL) {
        cur->getPrev()->setNext(entry);
    }
    entry->setPrev(cur->getPrev());
    entry->setNext(cur);
    cur->setPrev(entry);
    if (M2C_FIELD(this, FloorModuleEntry **, 0xC) == cur) {
        M2C_FIELD(this, FloorModuleEntry **, 0xC) = entry;
    }
}
}

extern "C++" {
extern "C++" {
extern "C++" {
FloorModuleEntry* FloorModuleList::getFMEEnd() {
    FloorModuleEntry *var_r31;
    FloorModuleEntry *var_r3;

    var_r3 = M2C_FIELD(this, FloorModuleEntry **, 0xC);
    var_r31 = NULL;
    while (var_r3 != NULL) {
        var_r31 = var_r3;
        var_r3 = ((FloorModuleEntry*)(var_r3))->getNext();
    }
    return var_r31;
}
}

extern "C++" {
#pragma push
#pragma peephole off
FloorModuleList::~FloorModuleList() {
    delete[] entries;
}
#pragma pop
}

extern "C++" {
FloorModuleList::FloorModuleList(unsigned long p0) {
    count = p0;
    head = 0;
    entries = new FloorModuleEntry[p0];
    if (entries == 0) {
        return;
    }
    nextHandle = 1;
}
}

extern "C++" {
u8 FloorModuleEntry::isScriptRunning(FloorState state) {
    switch (type) {
    case 2:
        return ((FloorScriptModule*)module)->isRunning(state);
    case 4:
        if (state == (s32)unkC) {
            return ((ScriptTpcNode*)module)->isRunning();
        }
        return 0;
    }
    return 0;
}
void FloorModuleEntry::exec(FloorState state, unsigned int floorId, FloorEnterMode mode) {
    FloorData* floor = floorDataBiosGetPtr(floorId);
    if (floor != NULL) {
        u32 group = floorDataBiosGetGroupID(floor);
        switch (type) {
        case 0:
            if (FloorModuleInterface_exec((s32*)module, state, floorId, mode, started == 0)) {
                started = 1;
            }
            break;
        case 2:
            ((FloorScriptModule*)module)->exec(state, priority, group, mode);
            break;
        case 4:
            if (state == (s32)unkC) {
                ((ScriptTpcNode*)module)->exec(priority, group, mode);
            }
            break;
        }
    }
}

}

extern "C++" {
extern "C++" {
void FloorModuleEntry::terminate() {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(this, s32 *, 0x10);
    switch (temp_r0) {
    case 2:
        ((FloorScriptModule*)((u8*)this + 0x1C))->terminate();
        return;
    case 4:
        ((ScriptTpcNode*)((u8*)this + 0x1C))->terminate();
    case 3:
        return;
    }
}
}

extern "C++" {
void FloorModuleEntry::kill() {
    if (((FloorModuleEntry*)(this))->isTpcScript() != 0) {
        ((FloorScriptModule*)((u8*)this + 0x1C))->kill();
    }
}
}

extern "C++" {
void FloorModuleEntry::unblock() {
    s32 temp_r0;

    M2C_FIELD(this, s8 *, 0x19) = 0;
    temp_r0 = M2C_FIELD(this, s32 *, 0x10);
    switch (temp_r0) {
    case 2:
        ((FloorScriptModule*)((u8*)this + 0x1C))->unblock();
        return;
    case 4:
        ((ScriptTpcNode*)((u8*)this + 0x1C))->unblock();
    case 3:
        return;
    }
}
}

extern "C++" {
void FloorModuleEntry::block() {
    s32 temp_r0;

    M2C_FIELD(this, s8 *, 0x19) = 1;
    temp_r0 = M2C_FIELD(this, s32 *, 0x10);
    switch (temp_r0) {
    case 2:
        ((FloorScriptModule*)((u8*)this + 0x1C))->block();
        return;
    case 4:
        ((ScriptTpcNode*)((u8*)this + 0x1C))->block();
    case 3:
        return;
    }
}
extern "C++" {
void FloorModuleEntry::setScriptModule(unsigned char p0, unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4) {
    ((FloorModuleEntry*)(this))->init();
    M2C_FIELD(this, s32 *, 0x10) = 2;
    M2C_FIELD(this, u32 *, 0x14) = p1;
    M2C_FIELD(this, u8 *, 0x18) = p0;
    ((FloorScriptModule*)((u8*)this + 0x1C))->setIDs(p2, p3, p4);
}
}

}

extern "C++" {
extern "C++" {
extern "C++" {
void FloorModuleEntry::init() {
    M2C_FIELD(this, s32 *, 0) = 0;
    M2C_FIELD(this, s32 *, 4) = 0;
    M2C_FIELD(this, s8 *, 0x19) = 0;
    M2C_FIELD(this, s8 *, 0x1A) = 0;
    M2C_FIELD(this, s32 *, 8) = 0;
    M2C_FIELD(this, s32 *, 0x14) = 0;
    M2C_FIELD(this, s8 *, 0x18) = 0;
}
}

extern "C++" {
void FloorModuleEntry::setModule(unsigned char priority, unsigned long group, FloorModuleInterface* iface) {
    init();
    type = FloorTypeFunc;
    groupID = group;
    this->priority = priority;
    *(FloorModuleInterface*)module = *iface;
}

FloorModuleEntry::FloorModuleEntry() {
    ((FloorModuleEntry*)(this))->init();
    return;
}

extern "C++" {
GSscript::Tiga* ScriptTpcNode::getScript() {
    if ((id & 0xFFFF0000) == 0x05960000) {
        return floorGetCommonScript();
    }
    return floorGetCurentScript();
}
extern "C" {
u8 FloorModuleInterface_exec(s32 *p0, s32 p1, s32 p2, s32 p3, bool p4) {
    GSthread *temp_r31;
    s32 (*temp_r12)(s32, s32);

        switch (p1) { case 1: goto sw0_c1; case 2: goto sw0_c2; case 4: goto sw0_c4; case 6: goto sw0_c6; case 8: goto sw0_c8; case 0: goto sw0_c0; case 3: goto sw0_c3; case 5: goto sw0_c5; case 7: goto sw0_c7; default: goto block_16; }
sw0_c1:;
    if ((u32) M2C_FIELD(p0, s32 *, 0) == 0U) {
        goto block_16;
    }
    _dispModuleName((FloorModuleInterface*)((FloorModuleInterface *) p0), (const char*)(_floorStateToStr((FloorState)(p1))));
    ((s32 (*)(s32, s32)) M2C_FIELD(p0, s32 *, 0))(p2, p3);
    goto block_16;
sw0_c2:;
    if (((s32 (*)(s32, s32)) M2C_FIELD(p0, s32 (**)(s32, s32), 4)) == NULL) {
        goto block_16;
    }
    _dispModuleName((FloorModuleInterface*)((FloorModuleInterface *) p0), (const char*)(_floorStateToStr((FloorState)(p1))));
    M2C_FIELD(p0, s32 (**)(s32, s32), 4)(p2, p3);
    goto block_16;
sw0_c4:;
    if ((u8 *) M2C_FIELD(p0, u8 **, 0xC) == NULL) {
        goto block_10;
    }
    if (p4 == 0) {
        goto block_9;
    }
    _dispModuleName((FloorModuleInterface*)((FloorModuleInterface *) p0), (const char*)("NoramlThread"));
    temp_r31 = (GSthread *)(floorCreateThread(1, 0x4000U, 1, (void*)(M2C_FIELD(p0, u8 **, 0xC))));
    GSthreadSetName((GSthread*)(temp_r31), (const char*)(M2C_FIELD(p0, s8 *(**)(), 0x18)()));
    return 1U;
block_9:
    return 0U;
block_10:
    temp_r12 = M2C_FIELD(p0, s32 (**)(s32, s32), 8);
    if (temp_r12 == NULL) {
        goto block_16;
    }
    temp_r12(p2, p3);
    goto block_16;
sw0_c6:;
    if (((s32 (*)(s32, s32)) M2C_FIELD(p0, s32 (**)(s32, s32), 0x10)) == NULL) {
        goto block_16;
    }
    _dispModuleName((FloorModuleInterface*)((FloorModuleInterface *) p0), (const char*)(_floorStateToStr((FloorState)(p1))));
    M2C_FIELD(p0, s32 (**)(s32, s32), 0x10)(p2, p3);
    goto block_16;
sw0_c8:;
    if (((s32 (*)(s32, s32)) M2C_FIELD(p0, s32 (**)(s32, s32), 0x14)) == NULL) {
        goto block_16;
    }
    _dispModuleName((FloorModuleInterface*)((FloorModuleInterface *) p0), (const char*)(_floorStateToStr((FloorState)(p1))));
    M2C_FIELD(p0, s32 (**)(s32, s32), 0x14)(p2, p3);
sw0_c0:;
sw0_c3:;
sw0_c5:;
sw0_c7:;
block_16:
    return 0U;
}
}

}

}

extern "C++" {
u8 FloorScriptModule::isRunning(FloorState state) {
    ScriptTpcNode* node = stateToNode(state);
    if (node != NULL) {
        return node->isRunning();
    }
    return 0;
}

#pragma push
#pragma peephole off
void FloorScriptModule::exec(FloorState state, unsigned char type, unsigned long group, FloorEnterMode mode) {
    ScriptTpcNode* node = stateToNode(state);
    if (node != NULL) {
        node->exec(type, group, mode);
    }
}
#pragma pop
extern "C++" {
void FloorScriptModule::kill() {
    ((ScriptTpcNode*)((ScriptTpcNode *) this))->terminate();
    ((ScriptTpcNode*)((u8*)this + 8))->terminate();
    ((ScriptTpcNode*)((u8*)this + 0x10))->terminate();
}
}

extern "C++" {
void FloorScriptModule::terminate() {
    ((ScriptTpcNode*)((ScriptTpcNode *) this))->terminate();
    ((ScriptTpcNode*)((u8*)this + 8))->terminate();
    ((ScriptTpcNode*)((u8*)this + 0x10))->terminate();
}
}

extern "C++" {
void FloorScriptModule::unblock() {
    ((ScriptTpcNode*)((ScriptTpcNode *) this))->unblock();
    ((ScriptTpcNode*)((u8*)this + 8))->unblock();
    ((ScriptTpcNode*)((u8*)this + 0x10))->unblock();
}
}

extern "C++" {
void FloorScriptModule::block() {
    ((ScriptTpcNode*)((ScriptTpcNode *) this))->block();
    ((ScriptTpcNode*)((u8*)this + 8))->block();
    ((ScriptTpcNode*)((u8*)this + 0x10))->block();
}
}

extern "C++" {
extern "C++" {
ScriptTpcNode* FloorScriptModule::stateToNode(FloorState state) {
    switch (state) {
    case 2:
        return &init;
    case 4:
        return &enter;
    case 6:
        return &exit;
    }
    return NULL;
}
extern "C++" {
#pragma push
#pragma dont_inline on
#pragma push
#pragma peephole off
u8 ScriptTpcNode::isRunning() {
    if (!getScript()->isRunningThread(script)) {
        script = 0;
        return 0;
    }
    return 1;
}
#pragma pop
extern "C++" {
#pragma push
#pragma dont_inline on
#pragma push
#pragma peephole off
void ScriptTpcNode::exec(unsigned char, unsigned long, FloorEnterMode mode) {
    GSscript::tigaVariant args[4];
    args[0].setInteger(mode);
    args[1].setInteger(0);
    args[2].setInteger(0);
    args[3].setInteger(0);
    script = getScript()->runParams(id, args, 4, true);
}
#pragma pop
extern "C++" {
#pragma push
#pragma dont_inline on
void ScriptTpcNode::terminate() {
    getScript()->deleteThread(script);
}
extern "C++" {
#pragma push
#pragma dont_inline on
void ScriptTpcNode::unblock() {
    getScript()->unblockThread(script);
}

void ScriptTpcNode::block() {
    getScript()->blockThread(script);
}
#pragma pop
}
#pragma pop
}
#pragma pop
}
#pragma pop
}

}

}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
void ScriptTpcNode::setID(u32 newID) {
    id = newID;
    script = 0;
}
extern "C" {
extern "C++" {
static void _dispModuleName(FloorModuleInterface* p0, const char* p1) {
}
}

extern "C" {
void FloorModuleInterface_clear(FloorModuleInterface* p0) {
    memset((void*)(p0), 0, 0x2CU);
}
extern "C++" {
#pragma push
#pragma peephole off
void FloorScriptModule::setIDs(unsigned long initID, unsigned long enterID, unsigned long exitID) {
    init.setID(initID);
    enter.setID(enterID);
    exit.setID(exitID);
}
#pragma pop
}

}

extern "C++" {
static const char* _floorTypeToStr(FloorModuleType type) {
    switch (type) {
    case 0:
        return "FloorTypeFunc";
    case 1:
        return "FloorTypeGSvm";
    case 2:
        return "FloorTypeTpc";
    case 3:
        return "FloorTypeSingleGSvm";
    case 4:
        return "FloorTypeSingleTpc";
    case 5:
        return "FloorTypeAny";
    }
    return "FloorUnknown";
}

static const char* _floorStateToStr(FloorState state) {
    switch (state) {
    case 0:
        return "FloorStateUnused";
    case 1:
        return "FloorStateCreate";
    case 2:
        return "FloorStatePre";
    case 3:
        return "FloorStatePreWait";
    case 4:
        return "FloorStateNormal";
    case 5:
        return "FloorStateNormalWait";
    case 6:
        return "FloorStatePost";
    case 7:
        return "FloorStatePostWait";
    case 8:
        return "FloorStateFree";
    }
    return "unknownState";
}
}
}

FloorModuleEntry* FloorModuleEntry::getNext() const {
    return next;
}

bool FloorModuleEntry::isBlock() const {
    return blocked;
}

FloorModuleType FloorModuleEntry::getType() const {
    return type;
}

u32 FloorModuleEntry::getGroupID() const {
    return groupID;
}

FloorModuleEntry* FloorModuleEntry::getPrev() const {
    return prev;
}
extern "C++" {
FloorModuleInterface* FloorModuleEntry::getModuleInterface() {
    if ((s32) M2C_FIELD(this, s32 *, 0x10) == 0) {
        return (FloorModuleInterface*)module;
    }
    return NULL;
}
}

u32 FloorModuleEntry::getHandle() const {
    return handle;
}

void FloorModuleEntry::setHandle(u32 newHandle) {
    handle = newHandle;
}
extern "C++" {
u32 FloorModuleList::getNewHandle() {
    u32 temp_r4;

    M2C_FIELD(this, u32 *, 8) = (u32) (M2C_FIELD(this, u32 *, 8) + 1);
    temp_r4 = M2C_FIELD(this, u32 *, 8);
    if (temp_r4 == 0) {
        M2C_FIELD(this, u32 *, 8) = (u32) (temp_r4 + 1);
    }
    return M2C_FIELD(this, u32 *, 8);
}
}

void FloorModuleEntry::setPrev(FloorModuleEntry* entry) {
    prev = entry;
}

void FloorModuleEntry::setNext(FloorModuleEntry* entry) {
    next = entry;
}

u8 FloorModuleEntry::getPriority() const {
    return priority;
}

bool FloorModuleEntry::isEmpty() const {
    return handle == 0;
}
extern "C++" {
bool FloorModuleEntry::isTpcScript() const {
    return type == 2;
}
}

void GSscript::tigaVariant::setInteger(long value) {
    type = 1;
    this->value = value;
}
