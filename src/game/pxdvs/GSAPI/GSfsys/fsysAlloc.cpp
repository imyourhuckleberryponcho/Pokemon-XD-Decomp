#include <dolphin/types.h>

#pragma pool_strings off

#define ALIGN32(x) (((x) + 0x1F) & ~0x1F)

struct FsysCacheManage {
    u8 unk0[0xC];
    void* addr;
    u32 size;
    u32 group;
};

struct FsysHeader {
    u8 unk0[0x10];
    u32 flags;
};

struct FsysFileInfo {
    u8 unk0[8];
    u32 headerSize;
};

struct Fsys {
    u32 group;
    u8 unk4[0x18];
    FsysFileInfo* info;
    void* header;
    u8 unk24[9];
    u8 cacheType;
    u8 headerValid;
};

extern "C" {

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void* OSGetArenaLo(void);
void OSSetArenaLo(void* lo);
s32 GSmemCreateHeap(void* lo, void* hi);
void GSmemFreeHeap(s32 heap, void* ptr);
void* GSmemAllocHeap(s32 heap, u32 size);
void* memset(void* dst, int c, unsigned long n);
void* memcpy(void* dst, const void* src, unsigned long n);
void DCFlushRange(void* addr, u32 size);
void* GSresAllocResourceAlign(u32 group, u32 align, u32 id, u32 size, s32);
FsysCacheManage* _fsysGetCacheManageGroup(u32 group);
FsysCacheManage* _fsysGetCacheManageAddr(void* addr);
FsysCacheManage* _fsysGetCacheManage(u32 group, u32 id);
FsysCacheManage* _fsysGetFreshCacheManage(u32 group, s32);
FsysCacheManage* _fsysGetNewCacheManage(u32 group, u32 id, u8 type, s32, u32);
void _fsysDelCacheManage(FsysCacheManage* manage);
u32 _fsysGetFreeCacheHeapSize(void);
void _fsysFreeCacheFromHeap(void* addr, u32 size);
void* _fsysAllocCacheFromHeap(u32 size);
FsysHeader* _fsysGetHeader(Fsys* fsys);
void* _fsysAlloc(u32 size);
BOOL _fsysFree(void* ptr);

static bool _fsysFreeFreshCacheGroup(u32 group);
static bool _fsysFreeFreshCache(u32 group, u32 size);
static bool _fsysFreeCacheAddr(void* addr);
static bool _fsysFreeCache(FsysCacheManage* manage);
static void* _fsysAllocCache(Fsys* fsys, u32 id, u32 size, u32 arg);

static s32 _fsysLocalHeap;

void* _fsysGetResource(u32 group, u32 id, u32 size) {
    return GSresAllocResourceAlign(group, 0x20, id, size, 0);
}

bool _fsysMemFreeCacheGroup(u32 group) {
    FsysCacheManage* manage = _fsysGetCacheManageGroup(group);
    if (manage == NULL) {
        return false;
    }
    return _fsysFreeCache(manage);
}

bool _fsysMemFreeCache(void* addr) {
    return _fsysFreeCacheAddr(addr);
}

void* _fsysMemAllocCache(Fsys* fsys, u32 id, u32 size, u32 arg) {
    u32 alignedSize = ALIGN32(size);
    void* addr;
    _fsysFreeFreshCache(fsys->group, alignedSize);
    for (;;) {
        addr = _fsysAllocCache(fsys, id, alignedSize, arg);
        if (addr != NULL) {
            break;
        }
        if (!_fsysFreeFreshCacheGroup(fsys->group)) {
            addr = NULL;
            break;
        }
    }
    return addr;
}

static bool _fsysFreeFreshCacheGroup(u32 group) {
    u32 lastGroup;
    bool freed = false;
    FsysCacheManage* manage;

    for (;;) {
        manage = _fsysGetFreshCacheManage(group, 1);
        if (manage == NULL) {
            return freed;
        }
        if (freed == true && lastGroup != manage->group) {
            break;
        }
        lastGroup = manage->group;
        freed = true;
        if (!_fsysFreeCache(manage)) {
            return false;
        }
    }
    return freed;
}

static bool _fsysFreeFreshCache(u32 group, u32 size) {
    FsysCacheManage* manage;
    for (;;) {
        if (size < _fsysGetFreeCacheHeapSize() - 0x80000) {
            break;
        }
        manage = _fsysGetFreshCacheManage(group, 0);
        if (manage == NULL) {
            return false;
        }
        if (!_fsysFreeCache(manage)) {
            return false;
        }
    }
    return true;
}

static bool _fsysFreeCacheAddr(void* addr) {
    FsysCacheManage* manage = _fsysGetCacheManageAddr(addr);
    if (manage == NULL) {
        return false;
    }
    return _fsysFreeCache(manage);
}

static bool _fsysFreeCache(FsysCacheManage* manage) {
    void* addr = manage->addr;
    u32 size = manage->size;
    _fsysDelCacheManage(manage);
    _fsysFreeCacheFromHeap(addr, size);
    return true;
}

static void* _fsysAllocCache(Fsys* fsys, u32 id, u32 size, u32 arg) {
    FsysCacheManage* manage = _fsysGetCacheManage(fsys->group, id);
    if (manage == NULL) {
        u8 type = fsys->cacheType;
        FsysHeader* header = _fsysGetHeader(fsys);
        if (header != NULL && (header->flags & 0x40000000)) {
            type = 1;
        }
        manage = _fsysGetNewCacheManage(fsys->group, id, type, 1, arg);
        if (manage == NULL) {
            return NULL;
        }
        manage->size = size;
        manage->addr = _fsysAllocCacheFromHeap(manage->size);
        if (manage->addr == NULL) {
            _fsysDelCacheManage(manage);
            return NULL;
        }
    }
    return manage->addr;
}

void _fsysMemFreeHeader(Fsys* fsys) {
    void* header;
    BOOL intr = OSDisableInterrupts();
    header = fsys->header;
    fsys->header = NULL;
    fsys->headerValid = 0;
    OSRestoreInterrupts(intr);
    _fsysFree(header);
}

bool _fsysMemAllocHeader(Fsys* fsys) {
    if (fsys->header != NULL) {
        return false;
    }
    fsys->headerValid = 0;
    fsys->header = _fsysAlloc(ALIGN32(fsys->info->headerSize));
    if (fsys->header == NULL) {
        return false;
    }
    memset(fsys->header, 0, 0x60);
    memcpy(fsys->header, "INVA", 4);
    DCFlushRange(fsys->header, 0x60);
    return true;
}

bool GSfsysCreateLocalHeap(void) {
    u8* lo = (u8*)OSGetArenaLo();
    u8* hi = lo + 0x50000;
    _fsysLocalHeap = GSmemCreateHeap(lo, hi);
    if (_fsysLocalHeap == -1) {
        return false;
    }
    OSSetArenaLo(hi);
    return true;
}

BOOL _fsysFree(void* ptr) {
    GSmemFreeHeap(_fsysLocalHeap, ptr);
    return TRUE;
}

void* _fsysAlloc(u32 size) {
    return GSmemAllocHeap(_fsysLocalHeap, size);
}

}
