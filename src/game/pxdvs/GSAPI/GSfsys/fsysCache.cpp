#include <dolphin/types.h>
#include <dolphin/arq.h>

struct FsysTag {
    FsysTag* prev;
    FsysTag* next;
    u8 used;
};

struct FsysCacheManage {
    FsysCacheManage* prev;
    FsysCacheManage* next;
    u8 used;
    u8 type;
    u8 locked;
    u8 pad0B;
    void* addr;
    u32 size;
    u32 prio;
    u32 uniqueID;
    u32 group;
    u32 id;
};

struct Fsys {
    u32 group;
    u32 id;
    u8 unk8[8];
    u32 flags;
};

struct FsysResHeader;

struct FsysArqTrans {
    FsysArqTrans* prev;
    FsysArqTrans* next;
    u8 used;
    u8 pad9[3];
    ARQRequest request;
    void (*callback)(u32);
    Fsys* fsys;
    FsysResHeader* res;
    u32 arg0;
    u32 arg1;
    u32 arg2;
    void* dst;
    u32 size;
};

extern "C" {

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void DCFlushRange(void* addr, u32 size);
void DCInvalidateRange(void* addr, u32 size);
s32 GSmemCreateExternalHeap(u32 top, u32 size, void* cell, u32 count);
void* GSmemAllocHeap(s32 heap, u32 size);
void GSmemFreeHeap(s32 heap, void* ptr);
void* _fsysDoMalloc(u32 size);
void _fsysAddTAG(FsysTag* tag, FsysTag** root);
void _fsysDelTAG(FsysTag* tag, FsysTag** root);

static u8 _fsysReadCacheExec(Fsys* fsys, FsysResHeader* res, void* dst, u32 size, u32 offset, void (*callback)(u32),
                      u32 arg0, u32 arg1, u32 arg2);
FsysArqTrans* _fsysArq2ArqTrans(u32 request);
FsysCacheManage* _fsysGetCacheManage(u32 group, u32 id);
static void _fsysARQCallbackWrite(u32 request);
static void _fsysARQCallbackRead(u32 request);
static u8 _fsysInitCacheHeap(u32 size);
static void _fsysAddCacheManage(FsysCacheManage* manage);
static void _fsysDelARQTrans(FsysArqTrans* trans);
static FsysArqTrans* _fsysGetNewArq(void);
static void _fsysAddArq(FsysArqTrans* trans);

static u8 _fsysAmemCell[0x2800];
static FsysCacheManage* _fsysCACHEManage;
static FsysCacheManage* _fsysCACHEManageRoot;
static FsysArqTrans* _fsysARQTrans;
static FsysArqTrans* _fsysARQTransRoot;
static u32 _fsysAmemTopAddr;
static s32 _fsysAmemHeap;
static u32 _fsysARQTransIndex;
static u32 _fsysARQTransSize;
static u32 _fsysCACHEFreeBytes;
static u32 _fsysCACHEuniqueID;
static u32 _fsysCACHEuniqueGroupID;
static u32 _fsysCACHEManageIndex;
static u32 _fsysCACHEManageSize;
static u32 _fsysCACHESize;

void _fsysWriteCache(Fsys* fsys, FsysResHeader* res, void* src, u32 base, u32 size, u32 offset,
                     void (*callback)(u32)) {
    FsysArqTrans* trans;
    trans = _fsysGetNewArq();
    if (trans == 0) {
        if (trans == 0) {
            return;
        }
        return;
    }
    trans->fsys = fsys;
    trans->res = res;
    trans->callback = callback;
    u32 priority = (fsys->flags == 4) ? 1 : 0;
    DCFlushRange(src, size);
    ARQPostRequest(&trans->request, fsys->group, 0, priority, (u32)src, base + offset, size,
                   _fsysARQCallbackWrite);
}

u8 _fsysReadCacheEX(Fsys* fsys, FsysResHeader* res, void* dst, u32 size, u32 offset, void (*callback)(u32),
                    u32 arg0, u32 arg1, u32 arg2) {
    return _fsysReadCacheExec(fsys, res, dst, size, offset, callback, arg0, arg1, arg2);
}

u8 _fsysReadCache(Fsys* fsys, FsysResHeader* res, void* dst, u32 size, u32 offset, void (*callback)(u32)) {
    return _fsysReadCacheExec(fsys, res, dst, size, offset, callback, 0, 0, 0);
}

static u8 _fsysReadCacheExec(Fsys* fsys, FsysResHeader* res, void* dst, u32 size, u32 offset, void (*callback)(u32),
                      u32 arg0, u32 arg1, u32 arg2) {
    FsysCacheManage* manage;
    FsysArqTrans* trans;
    u32 priority;

    manage = _fsysGetCacheManage(fsys->group, fsys->id);
    if (manage == 0) {
        if (manage == 0) {
            return;
        }
        return 0;
    }
    trans = _fsysGetNewArq();
    if (trans == 0) {
        if (trans == 0) {
            return;
        }
        return 0;
    }
    trans->fsys = fsys;
    trans->res = res;
    trans->callback = callback;
    trans->arg0 = arg0;
    trans->arg1 = arg1;
    trans->arg2 = arg2;
    priority = (fsys->flags == 4) ? 1 : 0;
    if (offset + size > manage->size) {
        size = manage->size - offset;
    }
    if (((u32)dst & 0x1F) == 0 && (size & 0x1F) == 0) {
        DCInvalidateRange(dst, size);
        trans->dst = dst;
        trans->size = size;
        ARQPostRequest(&trans->request, fsys->group, 1, priority, (u32)manage->addr + offset, (u32)dst, size,
                       _fsysARQCallbackRead);
        return 1;
    }
}

static void _fsysARQCallbackWrite(u32 request) {
    FsysArqTrans* trans;
    trans = _fsysArq2ArqTrans(request);
    if (trans == 0) {
        if (trans == 0) {
            return;
        }
        return;
    }
    if (trans->callback != 0) {
        trans->callback(request);
    }
    _fsysDelARQTrans(trans);
}

static void _fsysARQCallbackRead(u32 request) {
    FsysArqTrans* trans;
    trans = _fsysArq2ArqTrans(request);
    if (trans == 0) {
        if (trans == 0) {
            return;
        }
        return;
    }
    DCInvalidateRange(trans->dst, trans->size);
    if (trans->callback != 0) {
        trans->callback(request);
    }
    _fsysDelARQTrans(trans);
}

s32 _fsysCheckCache(u32 group, u32 id) {
    return _fsysGetCacheManage(group, id) != 0;
}

s32 _fsysIncCacheUniqueGroupID(void) {
    return _fsysCACHEuniqueGroupID++;
}

u8 _fsysInitCache(u32 cacheSize, u32 manageSize) {
    u32 i;
    u32 off;

    _fsysCACHEManageRoot = 0;
    _fsysCACHEManageIndex = 0;
    _fsysCACHEuniqueGroupID = 0;
    _fsysCACHEuniqueID = 0;
    _fsysCACHEFreeBytes = 0;
    _fsysARQTransRoot = 0;
    _fsysARQTransIndex = 0;
    _fsysCACHESize = cacheSize;
    if (cacheSize == 0) {
        _fsysCACHESize = 0xA00000;
    }
    _fsysCACHEManageSize = manageSize;
    _fsysCACHESize = (_fsysCACHESize + 31) & ~31;
    if (manageSize == 0) {
        _fsysCACHEManageSize = 0x200;
    }
    _fsysARQTransSize = 8;
    if (!_fsysInitCacheHeap(_fsysCACHESize)) {
        return 0;
    }
    _fsysCACHEManage = (FsysCacheManage*)_fsysDoMalloc(_fsysCACHEManageSize * sizeof(FsysCacheManage));
    if (_fsysCACHEManage == 0) {
        return 0;
    }
    _fsysARQTrans = (FsysArqTrans*)_fsysDoMalloc(_fsysARQTransSize * sizeof(FsysArqTrans));
    if (_fsysARQTrans == 0) {
        return 0;
    }
    for (i = 0; i < _fsysCACHEManageSize; i++) {
        _fsysCACHEManage[i].used = 0;
        _fsysCACHEManage[i].type = 0;
        _fsysCACHEManage[i].locked = 0;
    }
    for (i = 0; i < _fsysARQTransSize; i++) {
        _fsysARQTrans[i].used = 0;
    }
    return 1;
}

u32 _fsysGetFreeCacheHeapSize(void) {
    return 0xA00000 - _fsysCACHEFreeBytes;
}

void _fsysFreeCacheFromHeap(void* addr, u32 size) {
    GSmemFreeHeap(_fsysAmemHeap, addr);
    _fsysCACHEFreeBytes -= size;
}

void* _fsysAllocCacheFromHeap(u32 size) {
    void* p = GSmemAllocHeap(_fsysAmemHeap, size);
    if (p != 0) {
        _fsysCACHEFreeBytes += size;
    }
    return p;
}

static u8 _fsysInitCacheHeap(u32 size) {
    return size <= 0xA00000;
}

u8 GSfsysCreateCacheHeap(void) {
    _fsysAmemTopAddr = 0x600000;
    _fsysAmemHeap = GSmemCreateExternalHeap(0x600000, 0x1000000, _fsysAmemCell, 0x200);
    return _fsysAmemHeap != -1;
}

void _fsysSetLockCacheFlagGroup(u32 group, u8 flag) {
    FsysCacheManage* manage;
    BOOL intr = OSDisableInterrupts();

    for (manage = _fsysCACHEManageRoot; manage != 0; manage = manage->next) {
        if (manage->group == group) {
            manage->locked = flag;
        }
    }
    OSRestoreInterrupts(intr);
}

void _fsysSetLockCacheFlag(u32 group, u32 id, u8 flag) {
    FsysCacheManage* manage;
    BOOL intr = OSDisableInterrupts();

    manage = _fsysGetCacheManage(group, id);
    if (manage != 0) {
        manage->locked = flag;
    }
    OSRestoreInterrupts(intr);
}

FsysCacheManage* _fsysGetFreshCacheManage(u32 group, u8 flag) {
    FsysCacheManage* manage;
    FsysCacheManage* best = 0;

    for (manage = _fsysCACHEManageRoot; manage != 0; manage = manage->next) {
        if (manage->type == 1) {
            continue;
        }
        if (manage->locked == 1) {
            continue;
        }
        if (manage->group == group) {
            continue;
        }
        if (best == 0) {
            best = manage;
            continue;
        }
        if (best->prio < manage->prio) {
            continue;
        }
        if (flag == 0) {
            if (best->uniqueID < manage->uniqueID) {
                best = manage;
            }
        } else {
            best = manage;
        }
    }
    return best;
}

FsysCacheManage* _fsysGetCacheManageAddr(void* addr) {
    FsysCacheManage* manage;
    BOOL intr = OSDisableInterrupts();

    for (manage = _fsysCACHEManageRoot; manage != 0; manage = manage->next) {
        if (manage->addr == addr) {
            break;
        }
    }
    OSRestoreInterrupts(intr);
    return manage;
}

FsysCacheManage* _fsysGetCacheManageGroup(u32 group) {
    FsysCacheManage* manage;
    BOOL intr = OSDisableInterrupts();

    for (manage = _fsysCACHEManageRoot; manage != 0; manage = manage->next) {
        if (manage->group == group) {
            break;
        }
    }
    OSRestoreInterrupts(intr);
    return manage;
}

FsysCacheManage* _fsysGetCacheManage(u32 group, u32 id) {
    FsysCacheManage* manage;
    BOOL intr = OSDisableInterrupts();

    for (manage = _fsysCACHEManageRoot; manage != 0; manage = manage->next) {
        if (manage->group == group && manage->id == id) {
            break;
        }
    }
    OSRestoreInterrupts(intr);
    return manage;
}

void _fsysDelCacheManage(FsysCacheManage* manage) {
    _fsysDelTAG((FsysTag*)manage, (FsysTag**)&_fsysCACHEManageRoot);
}

FsysCacheManage* _fsysGetNewCacheManage(u32 group, u32 id, u8 type, u8 locked, u32 prio) {
    BOOL intr;
    FsysCacheManage* entry;
    u32 i;
    FsysCacheManage* manage = 0;
    intr = OSDisableInterrupts();

    i = _fsysCACHEManageIndex;
    while (manage == 0) {
        entry = &_fsysCACHEManage[i];
        if (entry->used == 0) {
            entry->prev = 0;
            entry->next = 0;
            entry->used = 1;
            entry->type = type;
            entry->locked = locked;
            entry->group = group;
            entry->id = id;
            entry->addr = 0;
            entry->size = 0;
            entry->prio = prio;
            entry->uniqueID = _fsysCACHEuniqueID;
            _fsysCACHEuniqueID++;
            manage = entry;
        }
        i++;
        if (i >= _fsysCACHEManageSize) {
            i = 0;
        }
        if (i == _fsysCACHEManageIndex) {
            if (i == _fsysCACHEManageIndex) {
                return;
            }
        }
    }
    _fsysCACHEManageIndex = i;
    _fsysAddCacheManage(manage);
    OSRestoreInterrupts(intr);
    return manage;
}

static void _fsysAddCacheManage(FsysCacheManage* manage) {
    _fsysAddTAG((FsysTag*)manage, (FsysTag**)&_fsysCACHEManageRoot);
}

FsysArqTrans* _fsysArq2ArqTrans(u32 request) {
    FsysArqTrans* trans;

    for (trans = _fsysARQTransRoot; trans != 0; trans = trans->next) {
        if ((u32)&trans->request == request) {
            return trans;
        }
    }
    return 0;
}

static void _fsysDelARQTrans(FsysArqTrans* trans) {
    _fsysDelTAG((FsysTag*)trans, (FsysTag**)&_fsysARQTransRoot);
}

static FsysArqTrans* _fsysGetNewArq(void) {
    BOOL intr;
    FsysArqTrans* trans = 0;
    FsysArqTrans* entry;
    u32 i;
    intr = OSDisableInterrupts();

    i = _fsysARQTransIndex;
    while (trans == 0) {
        entry = &_fsysARQTrans[i];
        if (entry->used == 0) {
            entry->prev = 0;
            entry->next = 0;
            entry->used = 1;
            entry->callback = 0;
            entry->fsys = 0;
            entry->res = 0;
            entry->arg0 = 0;
            entry->arg1 = 0;
            entry->arg2 = 0;
            entry->dst = 0;
            entry->size = 0;
            trans = entry;
        }
        i++;
        if (i >= _fsysARQTransSize) {
            i = 0;
        }
        if (i == _fsysARQTransIndex) {
            break;
        }
    }
    _fsysARQTransIndex = i;
    _fsysAddArq(trans);
    OSRestoreInterrupts(intr);
    return trans;
}

static void _fsysAddArq(FsysArqTrans* trans) {
    _fsysAddTAG((FsysTag*)trans, (FsysTag**)&_fsysARQTransRoot);
}

}
