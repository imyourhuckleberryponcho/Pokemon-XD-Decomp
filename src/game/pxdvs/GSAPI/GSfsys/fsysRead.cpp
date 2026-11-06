#pragma pool_strings off
#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gcdata.h>
#include <game/pxdvs/GSAPI/GSfsys/fsys.h>
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
struct GSdvdFile;

extern "C" {
struct GSdvdFile {
    u8 _draft[1];
};

extern "C" {
void GSdvdClose(GSdvdFile* file);
u32 GSdvdGetLength(u32 file);
GSdvdFile* GSdvdOpen(const char* name);
u8 GSdvdOpenTest(const char* name);
u8 GSdvdReadAsync(u32 file, void* dst, u32 len, s32 a, void* callback);
u8 GSdvdSeekAsync(s32, s32, void*);
asm BOOL OSDisableInterrupts(void);
asm BOOL OSRestoreInterrupts(register BOOL level);
void _fsysAddBGWork(FsysBG* bg);
void _fsysAddBlock(FsysBlockSlot* list, FsysBlock* block);
static u8 _fsysAdjustReadFile(void *p0);
FsysBlock* _fsysAllocBlock(void);
FsysArqTrans* _fsysArq2ArqTrans(void* arq);
u8 _fsysCheckCache(s32, void*);
static u8 _fsysExpandFile(void *p0);
u8 _fsysExpandFileExec(void *p0, void *p1);
BOOL _fsysFreeBlock(FsysBlockSlot* list, u8 first);
s32 _fsysGetActiveTask(s32 mode);
s32* _fsysGetDataType(u32 p0);
FsysHeader* _fsysGetHeader(Fsys* fsys);
FsysBG* _fsysGetNewBGWork(void);
FsysWork* _fsysGetNewWork(void);
FsysResHeader* _fsysGetResHeader(Fsys* fsys, u32 index);
s32 _fsysGetTransLength(s32 p0, s32 p1);
u32 _fsysID2Index(FsysWork* work, u32 id);
FsysWork* _fsysInfo2Work(u32 handle);
void* _fsysMemAllocCache(Fsys* fsys, u32 id, u32 size, u32 arg);
bool _fsysMemAllocHeader(Fsys* fsys);
void _fsysMoveBlock(FsysBlockSlot* from, FsysBlockSlot* to);
static void _fsysReadBlockCacheCallback(u32 request);
static void _fsysReadBlockCacheWriteCallback(u32 request);
static void _fsysReadBlockDvdCallback(s32 p0, s32 p1);
static void _fsysReadBlockHandling(void *p0, void *p1);
u8 _fsysReadCache(void*, void*, void*, s32, u32, void*);
static void* _fsysReadData(void *p0, void *p1, u8 p2, s32 p3, void *p4, void *p5, void *p6, void *p7, GCsptr p8);
void* _fsysReadDataExec(void *p0, void *p1);
static void _fsysReadDataNext(void *p0, void *p1);
static void* _fsysReadFile(void *p0);
static void _fsysReadHeaderCacheCallback(u32 request);
static void _fsysReadHeaderCacheWriteCallback();
static void _fsysReadHeaderCallbackSub(void *p0);
static void _fsysReadHeaderDvdCallback(s32 p0, s32 p1);
void _fsysReadRequest(void *p0);
void _fsysResHeaderSetTaskStatus(FsysResHeader* res, u32 status);
static void _fsysSeekCallback(s32 p0, s32 p1);
void _fsysSeekRequest(void *p0);
s32 _fsysSetLockCacheFlag(s32, void*, s32);
u32 _fsysStreamGetCacheSize(void);
u32 _fsysStreamGetReadBlockFlag(u32 offset);
void _fsysWorkSetTaskStatus(FsysWork* work, u32 status);
void _fsysWriteCache(Fsys* fsys, FsysResHeader* res, void* src, u32 base, u32 size, u32 offset,
                     void (*callback)(u32));
int sprintf(char* s, const char* format, ...);
extern u32 _fsysBlockByteSize;
struct FsysDataType {
    u32 unk0;
    u32 type;
    void* pre;
    void* post;
};
extern FsysDataType fsys_datatype[];
extern u32 fsys_datatype_number;
}

void _fsysSeekRequest(void *p0) {
    if (GSdvdSeekAsync(((FsysWork*)(p0))->file, 0, _fsysSeekCallback) == 0) {
        _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E2U);
    }
}
}

extern "C" {
void _fsysReadRequest(void *p0) {
    void (*sp8)();
    s32 level;
    FsysWork *temp_r3;
    u8 var_r28;

    if (((u8 *) ((FsysWork*)(p0))->header != NULL) && ((u8) ((FsysWork*)(p0))->headerValid == 1)) {
        _fsysReadHeaderCallbackSub(p0);
        return;
    }
loop_4:
    if (_fsysMemAllocHeader((Fsys*)((Fsys *) p0)) != 1) {
        level = OSDisableInterrupts();
        temp_r3 = _fsysGetNewWork();
        if (temp_r3 == NULL) {
            OSRestoreInterrupts(level);
            if (temp_r3 != NULL) {
                _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E4U);
            }
        } else {
            ((FsysWork*)(temp_r3))->status = 0;
            OSRestoreInterrupts(level);
            goto loop_4;
        }
    } else {
        level = OSDisableInterrupts();
        var_r28 = 0;
        if (_fsysCheckCache(((FsysWork*)(p0))->id, (u8 *)0xFFFF) == 1) {
            _fsysSetLockCacheFlag(((FsysWork*)(p0))->id, (u8 *)0xFFFF, 1);
            var_r28 = 1;
        }
        OSRestoreInterrupts(level);
        _fsysReadData(p0, NULL, var_r28, 0xFFFF, ((FsysWork*)(p0))->header, (u8**)(u32)((FsysWork*)(p0))->group->headerSize, NULL,
                      (void*)_fsysReadHeaderDvdCallback, (GCsptr)_fsysReadHeaderCacheCallback);
    }
}
}

extern "C" {
static void* _fsysReadData(void *p0, void *p1, u8 p2, s32 p3, void *p4, void *p5, void *p6, void *p7, GCsptr p8) {
    u32 temp_r3;
    u8 *var_r9;

    var_r9 = (unsigned char *)(p6);
    ((FsysWork*)(p0))->unk4 = p3;
    if (p2 == 1) {
        if (_fsysReadCache(p0, p1, p4, (GCsptr)p5, (u32)p6, (void*)p8) == 0) {
            _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E4U);
            return NULL;
        }
        goto block_11;
    }
    if (p1 != NULL) {
        temp_r3 = (u32)((FsysResHeader*)(p1))->dvdFile;
        if (temp_r3 != 0) {
            if (GSdvdReadAsync(temp_r3, (void*)(p4), (u32) p5, (GCsptr) var_r9, p7) == 0) {
                _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E4U);
                return NULL;
            }
            goto block_11;
        }
    }
    if (p1 != NULL) {
        var_r9 += ((FsysResHeader*)(p1))->unk4;
    }
    if (GSdvdReadAsync(((FsysWork*)(p0))->file, (void*)(p4), (u32) p5, (GCsptr) var_r9, p7) == 0) {
        _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E4U);
        return NULL;
    }
block_11:
    return (u8 *)1;
}
}

extern "C" {
static void _fsysReadHeaderCacheCallback(u32 request) {
    FsysArqTrans *temp_r3;

    temp_r3 = _fsysArq2ArqTrans((void*)request);
    if (temp_r3 != NULL) {
        _fsysReadHeaderCallbackSub(((FsysArqTrans*)(temp_r3))->fsys);
    }
}
}

extern "C" {
static void _fsysReadHeaderDvdCallback(s32 p0, s32 p1) {
    FsysWork *temp_r3;
    u8 *temp_r3_2;

    temp_r3 = _fsysInfo2Work((u32) p1);
    if (temp_r3 != NULL) {
        if (p0 < 0) {
            _fsysWorkSetTaskStatus((FsysWork*)(temp_r3), -0x3E4U);
            return;
        }
        temp_r3_2 = (unsigned char *)(_fsysMemAllocCache((Fsys*)((Fsys *) temp_r3), 0xFFFFU, ((FsysWork*)(temp_r3))->group->headerSize, ((FsysWork*)(temp_r3))->groupId));
        if (temp_r3_2 != NULL) {
            _fsysWriteCache(temp_r3, NULL, ((FsysWork*)(temp_r3))->header, (u32) temp_r3_2, ((FsysWork*)(temp_r3))->group->headerSize, 0, (void (*)(u32))_fsysReadHeaderCacheWriteCallback);
        }
        _fsysReadHeaderCallbackSub(temp_r3);
    }
}
}

extern "C" {
static void _fsysReadHeaderCacheWriteCallback() {
}
}

extern "C" {
static void _fsysReadHeaderCallbackSub(void *p0) {
    s32 temp_r0;
    s32 temp_r31;

    temp_r31 = OSDisableInterrupts();
    ((FsysWork*)(p0))->headerValid = 1;
    temp_r0 = ((FsysWork*)(p0))->mode;
    switch (temp_r0) {
    case 3:
        break;
    case 4:
    case 1:
        if (_fsysID2Index((FsysWork*)((FsysWork *) p0), ((FsysWork*)(p0))->unk8) != 0xFFFF) {
            ((FsysWork*)(p0))->unk24 = _fsysID2Index((FsysWork*)((FsysWork *) p0), ((FsysWork*)(p0))->unk8);
            ((FsysWork*)(p0))->unk28 = (u32) ((FsysWork*)(p0))->unk24;
        }
        _fsysReadFile(p0);
        break;
    case 2:
        if (_fsysID2Index((FsysWork*)((FsysWork *) p0), ((FsysWork*)(p0))->unk8) != 0xFFFF) {
            if (_fsysCheckCache((s32)(((FsysWork*)(p0))->id), (void *)(_fsysID2Index((FsysWork*)((FsysWork *) p0), ((FsysWork*)(p0))->unk8))) == 1) {
                _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), 0xAU);
            } else {
                ((FsysWork*)(p0))->unk24 = _fsysID2Index((FsysWork*)((FsysWork *) p0), ((FsysWork*)(p0))->unk8);
                ((FsysWork*)(p0))->unk28 = (u32) ((FsysWork*)(p0))->unk24;
                _fsysReadFile(p0);
            }
        } else if (_fsysAdjustReadFile(p0) == 1) {
            _fsysReadFile(p0);
        } else {
            _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), 0xAU);
        }
        break;
    }
    OSRestoreInterrupts(temp_r31);
}
}

extern "C" {
static void* _fsysReadFile(void* task) {
    char path[0x80];
    FsysResHeader* res;
    char* name;
    s32 mode;

    if (((FsysWork*)(task))->cancel == 1) {
        _fsysWorkSetTaskStatus((FsysWork*)task, 0xA);
        return NULL;
    }
    res = _fsysGetResHeader((Fsys*)task, ((FsysWork*)(task))->unk24);
    if (res != NULL) {
        name = (char*)((FsysWork*)(task))->header + ((FsysResHeader*)(res))->unk1C;
        ((FsysResHeader*)(res))->pos = 0;
        ((FsysResHeader*)(res))->cache = 0;
        ((FsysResHeader*)(res))->blockA = 0;
        ((FsysResHeader*)(res))->blockB = 0;
        ((FsysResHeader*)(res))->dvdFile = NULL;
        ((FsysResHeader*)(res))->unk3C = 0;
        ((FsysResHeader*)(res))->pending = 0xFFFF;
        ((FsysResHeader*)(res))->flags &= 0xFF70FFF7;
        ((FsysResHeader*)(res))->flags |= 0x800;
        ((FsysResHeader*)(res))->remaining = 0;
        ((FsysResHeader*)(res))->readBlocks = 0;
        ((FsysResHeader*)(res))->unk48 = 0;
        ((FsysResHeader*)(res))->loopPoint = 0;
        ((FsysResHeader*)(res))->loopEnd = ((FsysResHeader*)(res))->size14;
        if (((FsysWork*)(task))->mode == 4 && (((FsysResHeader*)(res))->type == 0x14 || ((FsysResHeader*)(res))->type == 0x16)) {
            ((FsysResHeader*)(res))->flags |= 0x40000;
        }
        if (_fsysGetHeader((Fsys*)task)->flags & 1) {
            sprintf(path, "debug/%s", name);
            if (GSdvdOpenTest(path) == 1) {
                ((FsysResHeader*)(res))->dvdFile = GSdvdOpen(path);
                ((FsysResHeader*)(res))->flags &= 0x7FFFFFFF;
                ((FsysResHeader*)(res))->size14 = GSdvdGetLength((u32)((FsysResHeader*)(res))->dvdFile);
                ((FsysResHeader*)(res))->size8 = ((FsysResHeader*)(res))->size14;
            }
        }
        if (((FsysWork*)(task))->mode != 4 && _fsysCheckCache(((FsysWork*)(task))->id, (u8*)((FsysWork*)(task))->unk24) == 1) {
            ((FsysResHeader*)(res))->flags |= 0x20000;
            _fsysSetLockCacheFlag(((FsysWork*)(task))->id, (u8*)((FsysWork*)(task))->unk24, 1);
        }
        mode = ((FsysWork*)(task))->mode;
        if ((mode == 1 || (mode == 4 && (((FsysResHeader*)(res))->flags & 0x40000))) && _fsysExpandFile(task) == 0) {
            return NULL;
        }
        return _fsysReadDataExec(task, res);
    }
    return res;
}
}

extern "C" {
void* _fsysReadDataExec(void* task, void* resv) {
    s32 level;
    GCsptr pos;
    FsysBlock* block;
    u32 cached;
    FsysResHeader* res = (FsysResHeader*)resv;
    level = OSDisableInterrupts();
    if (((FsysWork*)(task))->mode == 4 && !(res->flags & 0x80000) && res->type != 0x14 && res->type != 0x16) {
        FsysResHeader* parent;
        if (_fsysID2Index((FsysWork*)task, ((FsysWork*)(task))->unk8) != 0xFFFF) {
            parent = _fsysGetResHeader((Fsys*)task, _fsysID2Index((FsysWork*)task, ((FsysWork*)(task))->unk8));
        } else {
            parent = _fsysGetResHeader((Fsys*)task, 0);
        }
        if (parent == NULL) {
            _fsysResHeaderSetTaskStatus(res, 3);
            OSRestoreInterrupts(level);
            return NULL;
        }
        if (!(parent->flags & 8)) {
            _fsysResHeaderSetTaskStatus(res, 3);
            OSRestoreInterrupts(level);
            return NULL;
        }
        s32 (*func)(s32, s32, s32) = (s32 (*)(s32, s32, s32))_fsysGetDataType(res->type)[2];
        if (func != NULL) {
            func(((FsysWork*)(task))->id, res->id, res->size14);
        }
        res->flags |= 0x80000;
    }
    block = _fsysAllocBlock();
    if (block == NULL) {
        _fsysResHeaderSetTaskStatus(res, 3);
        OSRestoreInterrupts(level);
        return NULL;
    }
    _fsysResHeaderSetTaskStatus(res, 1);
    block->unkC = res->pos;
    _fsysAddBlock(&res->blockA, block);
    cached = (res->flags >> 17) & 1;
    pos = res->pos;
    void* result = _fsysReadData(task, res, cached, ((FsysWork*)(task))->unk24, res->blockA->data,
                                 (void*)_fsysGetTransLength(res->size14, pos), (void*)pos, (void*)_fsysReadBlockDvdCallback,
                                 (GCsptr)_fsysReadBlockCacheCallback);
    OSRestoreInterrupts(level);
    return result;
}
}

extern "C" {
static void _fsysReadBlockCacheCallback(u32 request) {
    FsysArqTrans *temp_r3;
    Fsys *temp_r31;
    FsysResHeader *temp_r30;

    temp_r3 = _fsysArq2ArqTrans((void*)request);
    if (temp_r3 != NULL) {
        temp_r30 = ((FsysArqTrans*)(temp_r3))->res;
        temp_r31 = ((FsysArqTrans*)(temp_r3))->fsys;
        _fsysReadBlockHandling(temp_r31, temp_r30);
        _fsysReadDataNext(temp_r31, temp_r30);
    }
}
}

extern "C" {
static void _fsysReadBlockDvdCallback(s32 p0, s32 p1) {
    s32 var_r31;
    FsysWork *temp_r3;
    s32 temp_r3_3;
    FsysResHeader *temp_r3_2;

    temp_r3 = _fsysInfo2Work((u32) p1);
    if (temp_r3 != NULL) {
        if (p0 < 0) {
            _fsysWorkSetTaskStatus((FsysWork*)(temp_r3), -0x3E4U);
            return;
        }
        temp_r3_2 = _fsysGetResHeader((Fsys*)((Fsys *) temp_r3), ((FsysWork*)(temp_r3))->unk24);
        if (temp_r3_2 != NULL) {
            temp_r3_3 = ((FsysResHeader*)(temp_r3_2))->flags;
            if (!(temp_r3_3 & 0x10000)) {
                if ((s32) ((FsysWork*)(temp_r3))->mode == 4) {
                    if (temp_r3_3 & 0x40000) {
                        ((FsysResHeader*)(temp_r3_2))->cache = NULL;
                    } else {
                        ((FsysResHeader*)(temp_r3_2))->cache = (unsigned char *)(_fsysMemAllocCache((Fsys*)((Fsys *) temp_r3), ((FsysWork*)(temp_r3))->unk24, _fsysStreamGetCacheSize(), ((FsysWork*)(temp_r3))->groupId));
                    }
                } else {
                    ((FsysResHeader*)(temp_r3_2))->cache = (unsigned char *)(_fsysMemAllocCache((Fsys*)((Fsys *) temp_r3), ((FsysWork*)(temp_r3))->unk24, ((FsysResHeader*)(temp_r3_2))->size14, ((FsysWork*)(temp_r3))->groupId));
                }
            }
            ((FsysResHeader*)(temp_r3_2))->flags = (s32) (((FsysResHeader*)(temp_r3_2))->flags | 0x10000);
            if ((u8 *) ((FsysResHeader*)(temp_r3_2))->cache != NULL) {
                if ((s32) ((FsysWork*)(temp_r3))->mode == 4) {
                    var_r31 = ((FsysResHeader*)(temp_r3_2))->unk48;
                } else {
                    var_r31 = ((FsysResHeader*)(temp_r3_2))->pos;
                }
                _fsysWriteCache(temp_r3, temp_r3_2, temp_r3_2->blockA->data, (u32) ((FsysResHeader*)(temp_r3_2))->cache, _fsysGetTransLength((s32) ((FsysResHeader*)(temp_r3_2))->size14, ((FsysResHeader*)(temp_r3_2))->pos), var_r31, _fsysReadBlockCacheWriteCallback);
            } else {
                _fsysReadBlockHandling(temp_r3, temp_r3_2);
            }
            _fsysReadDataNext(temp_r3, temp_r3_2);
        }
    }
}
}

extern "C" {
s32 _fsysGetTransLength(s32 p0, s32 p1) {
    u32 var_r3;

    var_r3 = p0 - p1;
    if (var_r3 > (u32) _fsysBlockByteSize) {
        var_r3 = _fsysBlockByteSize;
    }
    return (var_r3 + 0x1F) & 0xFFFFFFE0;
}
}

extern "C" {
static void _fsysReadBlockCacheWriteCallback(u32 request) {
    FsysArqTrans *temp_r3;

    temp_r3 = _fsysArq2ArqTrans((void*)request);
    if (temp_r3 != NULL) {
        _fsysReadBlockHandling(((FsysArqTrans*)(temp_r3))->fsys, ((FsysArqTrans*)(temp_r3))->res);
    }
}
}

extern "C" {
static void _fsysReadBlockHandling(void *p0, void *p1) {
    s32 temp_r0;

    temp_r0 = ((FsysWork*)(p0))->mode;
    if (((temp_r0 == 1) || ((temp_r0 == 4) && (((FsysResHeader*)(p1))->flags & 0x40000))) && ((u8) ((FsysWork*)(p0))->cancel != 1)) {
        _fsysMoveBlock(&((FsysResHeader*)(p1))->blockA, &((FsysResHeader*)(p1))->blockB);
        return;
    }
    _fsysFreeBlock(&((FsysResHeader*)(p1))->blockA, 0U);
}
}

extern "C" {
static void _fsysReadDataNext(void *p0, void *p1) {
    GSdvdFile *temp_r3;
    s32 temp_r4;

    ((FsysResHeader*)(p1))->pos = (u32) (((FsysResHeader*)(p1))->pos + _fsysBlockByteSize);
    if (((s32) ((FsysWork*)(p0))->mode == 4) && !(((FsysResHeader*)(p1))->flags & 0x40000)) {
        ((FsysResHeader*)(p1))->remaining = (u32) (((FsysResHeader*)(p1))->remaining + _fsysBlockByteSize);
        ((FsysResHeader*)(p1))->readBlocks = (s32) (((FsysResHeader*)(p1))->readBlocks | _fsysStreamGetReadBlockFlag(((FsysResHeader*)(p1))->unk48));
        ((FsysResHeader*)(p1))->unk48 = (u32) (((FsysResHeader*)(p1))->unk48 + _fsysBlockByteSize);
        if ((u32) ((FsysResHeader*)(p1))->unk48 >= _fsysStreamGetCacheSize()) {
            ((FsysResHeader*)(p1))->unk48 = 0U;
        }
        if ((u8) ((FsysWork*)(p0))->cancel == 1) {
            _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), 0xAU);
            return;
        }
        if ((u32) ((FsysResHeader*)(p1))->pos >= (u32) ((FsysResHeader*)(p1))->loopEnd) {
            if (((FsysResHeader*)(p1))->flags & 0x800) {
                _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 2U);
                return;
            }
            if ((u32) ((FsysResHeader*)(p1))->pos < _fsysStreamGetCacheSize()) {
                ((FsysResHeader*)(p1))->flags = (s32) (((FsysResHeader*)(p1))->flags | 0x800000);
                _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 2U);
                ((FsysResHeader*)(p1))->readBlocks = -1;
                return;
            }
            ((FsysResHeader*)(p1))->pos = (u32) ((FsysResHeader*)(p1))->loopPoint;
            goto block_12;
        }
block_12:
        if ((u32) ((FsysResHeader*)(p1))->remaining >= _fsysStreamGetCacheSize()) {
            _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 5U);
            return;
        }
        if ((_fsysGetActiveTask(1) + _fsysGetActiveTask(2)) != 0) {
            _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 5U);
            return;
        }
        goto block_28;
    }
    if ((u32) ((FsysResHeader*)(p1))->pos >= (u32) ((FsysResHeader*)(p1))->size14) {
        temp_r3 = ((FsysResHeader*)(p1))->dvdFile;
        if (temp_r3 != NULL) {
            ((FsysResHeader*)(p1))->dvdFile = NULL;
            GSdvdClose((GSdvdFile*)(temp_r3));
        }
        if ((s32) ((FsysWork*)(p0))->mode == 4) {
            temp_r4 = ((FsysWork*)(p0))->cbArg1;
            if (temp_r4 != 0) {
                ((FsysWork*)(p0))->unk24 = _fsysID2Index((FsysWork*)((FsysWork *) p0), (u32) temp_r4);
                goto block_25;
            }
        }
        if (_fsysID2Index((FsysWork*)((FsysWork *) p0), ((FsysWork*)(p0))->unk8) != 0xFFFF) {
            _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), 0xAU);
            return;
        }
        ((FsysWork*)(p0))->unk24 = (u32) (((FsysWork*)(p0))->unk24 + 1);
block_25:
        FsysHeader* h = _fsysGetHeader((Fsys*)p0);
        if ((u32) ((FsysWork*)(p0))->unk24 >= (u32) ((FsysHeader*)(h))->resNum) {
            _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), 0xAU);
            return;
        }
        _fsysReadFile(p0);
        return;
    }
block_28:
    _fsysReadDataExec(p0, p1);
}
}

extern "C" {
FsysResHeader* _fsysGetResHeader(Fsys* fsys, u32 index) {
    FsysHeader* header = _fsysGetHeader(fsys);
    if (header == NULL) {
        return NULL;
    }
    if (index >= header->resNum) {
        return NULL;
    }
    return (FsysResHeader*)((u8*)header + *(gc_be32*)((u8*)header + header->offsetTable + index * 4));
}
extern "C" {
FsysHeader* _fsysGetHeader(Fsys* p0) {
    FsysHeader *temp_r4;

    temp_r4 = ((FsysWork*)(p0))->header;
    if (temp_r4 == NULL) {
        return NULL;
    }
    if ((u8) ((FsysWork*)(p0))->headerValid == 0) {
        return NULL;
    }
    return temp_r4;
}
}

extern "C" {
static u8 _fsysAdjustReadFile(void *p0) {
    FsysHeader* hdr = _fsysGetHeader((Fsys*)p0);
    u16 i;

    for (i = 0; i < ((FsysHeader*)(hdr))->resNum; i++) {
        if (_fsysCheckCache(((FsysWork*)(p0))->id, (u8*)i) == 0) {
            break;
        }
    }
    if (i >= ((FsysHeader*)(hdr))->resNum) {
        return 0;
    }
    ((FsysWork*)(p0))->unk24 = i;
    return 1;
}
}

extern "C" {
#pragma optimize_for_size on
static u8 _fsysExpandFile(void *p0) {
    FsysResHeader *temp_r3;

    void* h = _fsysGetHeader((Fsys*)p0);
    if ((((FsysWork*)(p0))->unk28) >= (u32) ((FsysHeader*)(h))->resNum) {
        return 0U;
    }
    temp_r3 = _fsysGetResHeader((Fsys*)((Fsys *) p0), (((FsysWork*)(p0))->unk28));
    if (temp_r3 == NULL) {
        return 0U;
    }
    ((FsysWork*)(p0))->unk28 = (u32) (((FsysWork*)(p0))->unk28 + 1);
    return _fsysExpandFileExec(p0, temp_r3);
}
#pragma optimize_for_size reset
}

extern "C" {
u8 _fsysExpandFileExec(void *p0, void *p1) {
    s32 temp_r31;
    FsysBG *temp_r3;

    temp_r31 = OSDisableInterrupts();
    temp_r3 = _fsysGetNewBGWork();
    if (temp_r3 == NULL) {
        _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 4U);
        OSRestoreInterrupts(temp_r31);
        return 0U;
    }
    _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 1U);
    ((FsysBG*)(temp_r3))->res = (FsysResHeader*)(p1);
    ((FsysBG*)(temp_r3))->work = (FsysWork*)(p0);
    if (((FsysResHeader*)(p1))->flags & 0x80000000) {
        ((FsysBG*)(temp_r3))->type = 1;
    } else {
        ((FsysBG*)(temp_r3))->type = 0;
    }
    _fsysAddBGWork((FsysBG*)(temp_r3));
    OSRestoreInterrupts(temp_r31);
    return 1U;
}
}

extern "C" {
s32* _fsysGetDataType(u32 type) {
    FsysDataType* entry = fsys_datatype;
    u32 i;
    for (i = 0; i < fsys_datatype_number; i++, entry++) {
        if (entry->type == type) {
            return (s32*)entry;
        }
    }
    return NULL;
}
}

extern "C" {
static void _fsysSeekCallback(s32 p0, s32 p1) {
    FsysWork *temp_r3;

    temp_r3 = _fsysInfo2Work((u32) p1);
    if (temp_r3 != NULL) {
        if (p0 < 0) {
            _fsysWorkSetTaskStatus((FsysWork*)(temp_r3), -0x3E2U);
            return;
        }
        _fsysWorkSetTaskStatus((FsysWork*)(temp_r3), 0xBU);
    }
}
}
}
