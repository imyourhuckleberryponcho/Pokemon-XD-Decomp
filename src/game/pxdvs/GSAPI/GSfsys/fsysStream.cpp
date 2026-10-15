#include <dolphin/types.h>

struct FsysResHeader {
    u8 unk0[0xC];
    u32 flags;
    u8 unk10[4];
    u32 size;
    u8 unk18[0x14];
    void* cache;
    u8 unk30[0x14];
    u32 remaining;
    u8 unk48[4];
    u32 readBlocks;
};

struct FsysHeader {
    u8 unk0[0xC];
    u32 resNum;
};

struct Fsys {
    u8 unk0[0x10];
    s32 state;
};

struct FsysReadRequest {
    u8 unk0[0x10];
    void* data;
};

typedef void (*FsysStreamCallback)(void* data, u32 arg0, u32 arg1);

struct FsysArqTrans {
    u8 unk0[0x30];
    FsysReadRequest* request;
    FsysResHeader* res;
    FsysStreamCallback callback;
    u32 arg0;
    u32 arg1;
};

extern "C" {

extern u32 _fsysBlockByteSize;

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
FsysResHeader* _fsysGetResHeader(Fsys* fsys, u32 index);
u32 _fsysID2Index(Fsys* fsys, u32 id);
FsysHeader* _fsysGetHeader(Fsys* fsys);
u8 _fsysReadCacheEX(Fsys* fsys, FsysResHeader* res, void* dst, u32 size, u32 offset, void (*callback)(void*),
                    u32, u32, u32);
FsysArqTrans* _fsysArq2ArqTrans(void* arq);
void _fsysMemSet(void* dst, s32 c, u32 size);
void _fsysMemFreeCache(void* cache);

static void _fsysStreamGetDataCallback(void* arq);

u32 _fsysStreamGetReadBlockFlag(u32 offset) {
    return 1 << (offset / _fsysBlockByteSize);
}

#pragma dont_inline on
BOOL _fsysStreamGetData(Fsys* fsys, u32 id, void* dst, u32 size, u32 offset, u32 arg5, u32 arg6, u32 arg7) {
    FsysResHeader* res;
    BOOL intr = OSDisableInterrupts();

    if (id == 0) {
        res = _fsysGetResHeader(fsys, 1);
    } else {
        res = _fsysGetResHeader(fsys, _fsysID2Index(fsys, id));
    }
    if (res != NULL && (res->readBlocks & _fsysStreamGetReadBlockFlag(offset))) {
        res->flags &= ~0x08000000;
        if (_fsysReadCacheEX(fsys, res, dst, size, offset, _fsysStreamGetDataCallback, arg5, arg6, arg7) == 1) {
            if (res->flags & 0x00800000) {
                res->remaining = res->size;
            } else {
                res->remaining -= size;
                res->readBlocks &= ~_fsysStreamGetReadBlockFlag(offset);
            }
            OSRestoreInterrupts(intr);
            return TRUE;
        }
    }
    OSRestoreInterrupts(intr);
    _fsysMemSet(dst, 0, size);
    return FALSE;
}
#pragma dont_inline reset

static void _fsysStreamGetDataCallback(void* arq) {
    FsysArqTrans* trans = _fsysArq2ArqTrans(arq);
 // The doubled check reproduces the original branch layout (likely a stripped debug check).
    if (trans == NULL) {
        if (trans == NULL) {
            return;
        }
        return;
    }
    {
        FsysReadRequest* request = trans->request;
        trans->res->flags |= 0x08000000;
        if (trans->callback != NULL) {
            trans->callback(request->data, trans->arg0, trans->arg1);
        }
        trans->callback = NULL;
    }
}

void _fsysStreamFreeCacheAll(Fsys* fsys) {
    BOOL intr;
    FsysHeader* header;
    FsysResHeader* res;
    s32 i;

    if (fsys != NULL && fsys->state == 4) {
        intr = OSDisableInterrupts();
        header = _fsysGetHeader(fsys);
        if (header != NULL) {
            for (i = 0; i < header->resNum; i++) {
                res = _fsysGetResHeader(fsys, i);
                if (res != NULL) {
                    if (res->cache != NULL) {
                        _fsysMemFreeCache(res->cache);
                        res->cache = NULL;
                    }
                }
            }
        }
        OSRestoreInterrupts(intr);
    }
}

u32 _fsysStreamGetMinimumCacheSize(void) {
    return _fsysBlockByteSize;
}

u32 _fsysStreamGetNormalCacheSize(void) {
    return _fsysBlockByteSize * 4;
}

u32 _fsysStreamGetCacheSize(void) {
    return _fsysBlockByteSize * 8;
}

}
