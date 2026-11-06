#include <dolphin/types.h>
#include <game/pxdvs/GSAPI/GSfsys/fsys.h>

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
                res->remaining = res->size14;
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
    if (trans == NULL) {
        if (trans == NULL) {
            return;
        }
        return;
    }
    {
        FsysReadRequest* request = (FsysReadRequest*)trans->fsys;
        trans->res->flags |= 0x08000000;
        if (trans->arg0 != 0) {
            FSYS_U32_TO_PTR(FsysStreamCallback, trans->arg0)(request->data, trans->arg1, trans->arg2);
        }
        trans->arg0 = 0;
    }
}

void _fsysStreamFreeCacheAll(Fsys* fsys) {
    BOOL intr;
    FsysHeader* header;
    FsysResHeader* res;
    s32 i;

    if (fsys != NULL && fsys->mode == 4) {
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
