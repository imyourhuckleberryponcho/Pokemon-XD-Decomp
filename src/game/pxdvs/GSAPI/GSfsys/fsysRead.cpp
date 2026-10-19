// Not yet decompiled.
#include <dolphin/types.h>
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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
struct Fsys;
struct FsysArqTrans;
struct FsysBG;
struct FsysBlock;
struct FsysHeader;
struct FsysResHeader;
struct FsysWork;
struct GSdvdFile;

extern "C" {
// ---- draft declarations ----
struct Fsys {
    u8 _draft[1];
};
struct FsysArqTrans {
    u8 _draft[1];
};
struct FsysBG {
    u8 _draft[1];
};
struct FsysBlock {
    u8 _draft[1];
};
struct FsysHeader {
    u8 _draft[1];
};
struct FsysResHeader {
    u8 _draft[1];
};
struct FsysWork {
    u8 _draft[1];
};
struct GSdvdFile {
    u8 _draft[1];
};

extern "C" {
void GSdvdClose(GSdvdFile* file);
u32 GSdvdGetLength(u32 file);
GSdvdFile* GSdvdOpen(const char* name);
u8 GSdvdOpenTest(const char* name);
u8 GSdvdReadAsync(u32 file, void* dst, u32 len, s32 a, s32 b);
u8 GSdvdSeekAsync(s32, s32, void*);
asm BOOL OSDisableInterrupts(void);
asm BOOL OSRestoreInterrupts(register BOOL level);
void _fsysAddBGWork(FsysBG* bg);
void _fsysAddBlock(FsysBlock** list, FsysBlock* block);
static u8 _fsysAdjustReadFile(void *p0);
FsysBlock* _fsysAllocBlock(void);
FsysArqTrans* _fsysArq2ArqTrans(void* arq);
u8 _fsysCheckCache(s32, void*);
static u8 _fsysExpandFile(void *p0);
u8 _fsysExpandFileExec(void *p0, void *p1);
BOOL _fsysFreeBlock(FsysBlock** list, u8 first);
s32 _fsysGetActiveTask(s32 mode);
s32* _fsysGetDataType(u32 p0);
FsysHeader* _fsysGetHeader(Fsys* fsys);
FsysBG* _fsysGetNewBGWork(void);
static FsysWork* _fsysGetNewWork(void);
FsysResHeader* _fsysGetResHeader(Fsys* fsys, u32 index);
s32 _fsysGetTransLength(s32 p0, s32 p1);
u32 _fsysID2Index(FsysWork* work, u32 id);
FsysWork* _fsysInfo2Work(u32 handle);
void* _fsysMemAllocCache(Fsys* fsys, u32 id, u32 size, u32 arg);
bool _fsysMemAllocHeader(Fsys* fsys);
void _fsysMoveBlock(FsysBlock** from, FsysBlock** to);
static void _fsysReadBlockCacheCallback();
static void _fsysReadBlockCacheWriteCallback();
static void _fsysReadBlockDvdCallback(s32 p0, s32 p1);
static void _fsysReadBlockHandling(void *p0, void *p1);
u8 _fsysReadCache(void*, void*, void*, s32);
static void* _fsysReadData(void *p0, void *p1, u8 p2, s32 p3, void *p4, void *p5, void *p6, void *p7, s32 p8, s32 arg_sp8);
void* _fsysReadDataExec(void *p0, void *p1);
static void _fsysReadDataNext(void *p0, void *p1);
static void* _fsysReadFile(void *p0);
static void _fsysReadHeaderCacheCallback();
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
s32 _fsysWriteCache(void*, void*, s32, u32, void*, void*, void*);
int sprintf(char* s, const char* format, ...);
extern u32 _fsysBlockByteSize;
extern s32 fsys_datatype;
extern u32 fsys_datatype_number;
}

void _fsysSeekRequest(void *p0) {
    if (GSdvdSeekAsync(M2C_FIELD(p0, s32 *, 0xC), 0, _fsysSeekCallback) == 0) {
        _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E2U);
    }
}
}

extern "C" {
void _fsysReadRequest(void *p0) {
    void (*sp8)();
    FsysWork *temp_r3;
    s32 temp_r28;
    s32 temp_r29;
    u8 var_r28;

    if (((u8 *) M2C_FIELD(p0, u8 **, 0x20) != NULL) && ((u8) M2C_FIELD(p0, u8 *, 0x2E) == 1)) {
        _fsysReadHeaderCallbackSub(p0);
        return;
    }
loop_4:
    if (_fsysMemAllocHeader((Fsys*)((Fsys *) p0)) != 1) {
        temp_r28 = OSDisableInterrupts();
        temp_r3 = _fsysGetNewWork();
        if (temp_r3 == NULL) {
            OSRestoreInterrupts(temp_r28);
            if (temp_r3 != NULL) {
                _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E4U);
            }
        } else {
            M2C_FIELD(temp_r3, s32 *, 0x14) = 0;
            OSRestoreInterrupts(temp_r28);
            goto loop_4;
        }
    } else {
        temp_r29 = OSDisableInterrupts();
        var_r28 = 0;
        if (_fsysCheckCache(M2C_FIELD(p0, s32 *, 0), (u8 *)0xFFFF) == 1) {
            _fsysSetLockCacheFlag(M2C_FIELD(p0, s32 *, 0), (u8 *)0xFFFF, 1);
            var_r28 = 1;
        }
        OSRestoreInterrupts(temp_r29);
        sp8 = _fsysReadHeaderCacheCallback;
        _fsysReadData((void *)(p0), (void *)(NULL), (unsigned char)(var_r28), (long)(0xFFFF), (void *)(M2C_FIELD(p0, u8 **, 0x20)), (void *)(M2C_FIELD(M2C_FIELD(p0, u8 **, 0x1C), u8 **, 8)), (void *)(NULL), (void *)(_fsysReadHeaderDvdCallback), (long)(M2C_ERROR(/* Unable to find stack arg 0x0 in block */)), (long)(0));
    }
}
}

extern "C" {
static void* _fsysReadData(void *p0, void *p1, u8 p2, s32 p3, void *p4, void *p5, void *p6, void *p7, s32 p8, s32 arg_sp8) {
    u32 temp_r3;
    u8 *var_r9;

    var_r9 = (unsigned char *)(p6);
    M2C_FIELD(p0, s32 *, 4) = p3;
    if (p2 == 1) {
        if (_fsysReadCache(p0, p1, p4, (s32) p5) == 0) {
            _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E4U);
            return NULL;
        }
        goto block_11;
    }
    if (p1 != NULL) {
        temp_r3 = M2C_FIELD(p1, u32 *, 0x38);
        if (temp_r3 != 0) {
            if (GSdvdReadAsync(temp_r3, (void*)(p4), (u32) p5, (s32) var_r9, (s32) p7) == 0) {
                _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E4U);
                return NULL;
            }
            goto block_11;
        }
    }
    if (p1 != NULL) {
        var_r9 += M2C_FIELD(p1, s32 *, 4);
    }
    if (GSdvdReadAsync(M2C_FIELD(p0, u32 *, 0xC), (void*)(p4), (u32) p5, (s32) var_r9, (s32) p7) == 0) {
        _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), -0x3E4U);
        return NULL;
    }
block_11:
    return (u8 *)1;
}
}

extern "C" {
static void _fsysReadHeaderCacheCallback() {
    FsysArqTrans *temp_r3;

    temp_r3 = _fsysArq2ArqTrans((void*)(M2C_ERROR(/* Read from unset register $r3 */)));
    if (temp_r3 != NULL) {
        _fsysReadHeaderCallbackSub(M2C_FIELD(temp_r3, u8 **, 0x30));
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
        temp_r3_2 = (unsigned char *)(_fsysMemAllocCache((Fsys*)((Fsys *) temp_r3), 0xFFFFU, M2C_FIELD(M2C_FIELD(temp_r3, u8 **, 0x1C), u32 *, 8), M2C_FIELD(temp_r3, u32 *, 0x3C)));
        if (temp_r3_2 != NULL) {
            _fsysWriteCache(temp_r3, NULL, M2C_FIELD(temp_r3, s32 *, 0x20), (u32) temp_r3_2, (u8 *) M2C_FIELD(M2C_FIELD(temp_r3, u8 **, 0x1C), u32 *, 8), NULL, _fsysReadHeaderCacheWriteCallback);
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
    M2C_FIELD(p0, s8 *, 0x2E) = 1;
    temp_r0 = M2C_FIELD(p0, s32 *, 0x10);
    switch (temp_r0) {                              /* irregular */
    case 3:
        break;
    case 4:
    case 1:
        if (_fsysID2Index((FsysWork*)((FsysWork *) p0), M2C_FIELD(p0, u32 *, 8)) != -1U) {
            M2C_FIELD(p0, u32 *, 0x24) = _fsysID2Index((FsysWork*)((FsysWork *) p0), M2C_FIELD(p0, u32 *, 8));
            M2C_FIELD(p0, u32 *, 0x28) = (u32) M2C_FIELD(p0, u32 *, 0x24);
        }
        _fsysReadFile(p0);
        break;
    case 2:
        if (_fsysID2Index((FsysWork*)((FsysWork *) p0), M2C_FIELD(p0, u32 *, 8)) != -1U) {
            if (_fsysCheckCache((long)(M2C_FIELD(p0, s32 *, 0)), (void *)(_fsysID2Index((FsysWork*)((FsysWork *) p0), M2C_FIELD(p0, u32 *, 8)))) == 1) {
                _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), 0xAU);
            } else {
                M2C_FIELD(p0, u32 *, 0x24) = _fsysID2Index((FsysWork*)((FsysWork *) p0), M2C_FIELD(p0, u32 *, 8));
                M2C_FIELD(p0, u32 *, 0x28) = (u32) M2C_FIELD(p0, u32 *, 0x24);
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
static void* _fsysReadFile(void *p0) {
    s8 sp8;
    FsysHeader *temp_ret;
    FsysResHeader *var_r3;
    s32 temp_r0_2;
    s32 temp_r30;
    u32 temp_r0;

    if ((u8) M2C_FIELD(p0, u8 *, 0x2C) == 1) {
        _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), 0xAU);
        return NULL;
    }
    var_r3 = _fsysGetResHeader((Fsys*)((Fsys *) p0), M2C_FIELD(p0, u32 *, 0x24));
    if (var_r3 != NULL) {
        M2C_FIELD(var_r3, s32 *, 0x28) = 0;
        temp_r30 = M2C_FIELD(p0, s32 *, 0x20) + M2C_FIELD(var_r3, s32 *, 0x1C);
        M2C_FIELD(var_r3, s32 *, 0x2C) = 0;
        M2C_FIELD(var_r3, s32 *, 0x30) = 0;
        M2C_FIELD(var_r3, s32 *, 0x34) = 0;
        M2C_FIELD(var_r3, GSdvdFile **, 0x38) = NULL;
        M2C_FIELD(var_r3, s32 *, 0x3C) = 0;
        M2C_FIELD(var_r3, s32 *, 0x40) = 0xFFFF;
        M2C_FIELD(var_r3, s32 *, 0xC) = (s32) (M2C_FIELD(var_r3, s32 *, 0xC) & 0xFF70FFF7);
        M2C_FIELD(var_r3, s32 *, 0xC) = (s32) (M2C_FIELD(var_r3, s32 *, 0xC) | 0x800);
        M2C_FIELD(var_r3, s32 *, 0x44) = 0;
        M2C_FIELD(var_r3, s32 *, 0x4C) = 0;
        M2C_FIELD(var_r3, s32 *, 0x48) = 0;
        M2C_FIELD(var_r3, s32 *, 0x50) = 0;
        M2C_FIELD(var_r3, u32 *, 0x54) = (u32) M2C_FIELD(var_r3, u32 *, 0x14);
        if (((s32) M2C_FIELD(p0, s32 *, 0x10) == 4) && ((temp_r0 = M2C_FIELD(var_r3, u32 *, 0x20), ((temp_r0 == 0x14U) != 0)) || (temp_r0 == 0x16U))) {
            M2C_FIELD(var_r3, s32 *, 0xC) = (s32) (M2C_FIELD(var_r3, s32 *, 0xC) | 0x40000);
        }
        temp_ret = _fsysGetHeader((Fsys*)((Fsys *) p0));
        if (M2C_FIELD(temp_ret, s32 *, 0x10) & 1) {
            sprintf((char*)(&sp8), (const char*)("debug/%s"), temp_r30, M2C_BITWISE(f32, temp_ret));
            if (GSdvdOpenTest((const char*)(&sp8)) == 1) {
                M2C_FIELD(var_r3, GSdvdFile **, 0x38) = GSdvdOpen((const char*)(&sp8));
                M2C_FIELD(var_r3, s32 *, 0xC) = (s32) (M2C_FIELD(var_r3, s32 *, 0xC) & 0x7FFFFFFF);
                M2C_FIELD(var_r3, u32 *, 0x14) = GSdvdGetLength((u32) M2C_FIELD(var_r3, GSdvdFile **, 0x38));
                M2C_FIELD(var_r3, u32 *, 8) = (u32) M2C_FIELD(var_r3, u32 *, 0x14);
            }
        }
        if (((s32) M2C_FIELD(p0, s32 *, 0x10) != 4) && (_fsysCheckCache(M2C_FIELD(p0, s32 *, 0), (u8 *) M2C_FIELD(p0, u32 *, 0x24)) == 1)) {
            M2C_FIELD(var_r3, s32 *, 0xC) = (s32) (M2C_FIELD(var_r3, s32 *, 0xC) | 0x20000);
            _fsysSetLockCacheFlag(M2C_FIELD(p0, s32 *, 0), (u8 *) M2C_FIELD(p0, u32 *, 0x24), 1);
        }
        temp_r0_2 = M2C_FIELD(p0, s32 *, 0x10);
        if (((temp_r0_2 == 1) || ((temp_r0_2 == 4) && (M2C_FIELD(var_r3, s32 *, 0xC) & 0x40000))) && (_fsysExpandFile(p0) == 0)) {
            return NULL;
        }
        var_r3 = (FsysResHeader *)(_fsysReadDataExec(p0, var_r3));
        /* Duplicate return node #19. Try simplifying control flow for better match */
        return var_r3;
    }
    return var_r3;
}
}

extern "C" {
void* _fsysReadDataExec(void *p0, void *p1) {
    void (*sp8)();
    FsysBlock *temp_r3;
    FsysResHeader *var_r3;
    s32 (*temp_r12)(s32, s32, s32);
    s32 temp_r28;
    s32 temp_r31;
    s32 temp_r8;
    u32 temp_r0;
    s8 temp_r27_2;
    u8 *temp_r27;

    temp_r31 = OSDisableInterrupts();
    if (((s32) M2C_FIELD(p0, s32 *, 0x10) == 4) && !(M2C_FIELD(p1, u32 *, 0xC) & 0x80000)) {
        temp_r0 = M2C_FIELD(p1, u32 *, 0x20);
        if ((temp_r0 != 0x14) && (temp_r0 != 0x16)) {
            if (_fsysID2Index((FsysWork*)((FsysWork *) p0), M2C_FIELD(p0, u32 *, 8)) != -1U) {
                var_r3 = _fsysGetResHeader((Fsys*)((Fsys *) p0), _fsysID2Index((FsysWork*)((FsysWork *) p0), M2C_FIELD(p0, u32 *, 8)));
            } else {
                var_r3 = _fsysGetResHeader((Fsys*)((Fsys *) p0), 0U);
            }
            if (var_r3 == NULL) {
                _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 3U);
                OSRestoreInterrupts(temp_r31);
                return NULL;
            }
            if (!(M2C_FIELD(var_r3, s32 *, 0xC) & 8)) {
                _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 3U);
                OSRestoreInterrupts(temp_r31);
                return NULL;
            }
            temp_r12 = M2C_FIELD(_fsysGetDataType(M2C_FIELD(p1, u32 *, 0x20)), s32 (**)(s32, s32, s32), 8);
            if (temp_r12 != NULL) {
                temp_r12(M2C_FIELD(p0, s32 *, 0), M2C_FIELD(p1, s32 *, 0), M2C_FIELD(p1, s32 *, 0x14));
            }
            M2C_FIELD(p1, u32 *, 0xC) = (u32) (M2C_FIELD(p1, u32 *, 0xC) | 0x80000);
            goto block_14;
        }
    }
block_14:
    temp_r3 = _fsysAllocBlock();
    if (temp_r3 == NULL) {
        _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 3U);
        OSRestoreInterrupts(temp_r31);
        return NULL;
    }
    _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 1U);
    M2C_FIELD(temp_r3, s32 *, 0xC) = (s32) M2C_FIELD(p1, s32 *, 0x28);
    _fsysAddBlock((FsysBlock**)(((u8*)(p1) + 0x30)), (FsysBlock*)(temp_r3));
    temp_r28 = M2C_FIELD(p1, s32 *, 0x28);
    temp_r27_2 = ((u32) M2C_FIELD(p1, u32 *, 0xC) >> 0x11U) & 1;
    temp_r8 = _fsysGetTransLength(M2C_FIELD(p1, s32 *, 0x14), temp_r28);
    sp8 = _fsysReadBlockCacheCallback;
    temp_r27 = (unsigned char *)(_fsysReadData((void *)(p0), (void *)(p1), (unsigned char)(temp_r27_2), (long)(M2C_FIELD(p0, s32 *, 0x24)), (void *)(M2C_FIELD(M2C_FIELD(p1, s8 **, 0x30), u8 **, 8)), (void *)((u8 *) temp_r8), (void *)((u8 *) temp_r28), (void *)(_fsysReadBlockDvdCallback), (long)(M2C_ERROR(/* Unable to find stack arg 0x0 in block */)), (long)(0)));
    OSRestoreInterrupts(temp_r31);
    return temp_r27;
}
}

extern "C" {
static void _fsysReadBlockCacheCallback() {
    FsysArqTrans *temp_r3;
    u8 *temp_r30;
    u8 *temp_r31;

    temp_r3 = _fsysArq2ArqTrans((void*)(M2C_ERROR(/* Read from unset register $r3 */)));
    if (temp_r3 != NULL) {
        temp_r30 = M2C_FIELD(temp_r3, u8 **, 0x34);
        temp_r31 = M2C_FIELD(temp_r3, u8 **, 0x30);
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
        temp_r3_2 = _fsysGetResHeader((Fsys*)((Fsys *) temp_r3), M2C_FIELD(temp_r3, u32 *, 0x24));
        if (temp_r3_2 != NULL) {
            temp_r3_3 = M2C_FIELD(temp_r3_2, s32 *, 0xC);
            if (!(temp_r3_3 & 0x10000)) {
                if ((s32) M2C_FIELD(temp_r3, s32 *, 0x10) == 4) {
                    if (temp_r3_3 & 0x40000) {
                        M2C_FIELD(temp_r3_2, u8 **, 0x2C) = NULL;
                    } else {
                        M2C_FIELD(temp_r3_2, u8 **, 0x2C) = (unsigned char *)(_fsysMemAllocCache((Fsys*)((Fsys *) temp_r3), M2C_FIELD(temp_r3, u32 *, 0x24), _fsysStreamGetCacheSize(), M2C_FIELD(temp_r3, u32 *, 0x3C)));
                    }
                } else {
                    M2C_FIELD(temp_r3_2, u8 **, 0x2C) = (unsigned char *)(_fsysMemAllocCache((Fsys*)((Fsys *) temp_r3), M2C_FIELD(temp_r3, u32 *, 0x24), M2C_FIELD(temp_r3_2, u32 *, 0x14), M2C_FIELD(temp_r3, u32 *, 0x3C)));
                }
            }
            M2C_FIELD(temp_r3_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_r3_2, s32 *, 0xC) | 0x10000);
            if ((u8 *) M2C_FIELD(temp_r3_2, u8 **, 0x2C) != NULL) {
                if ((s32) M2C_FIELD(temp_r3, s32 *, 0x10) == 4) {
                    var_r31 = M2C_FIELD(temp_r3_2, s32 *, 0x48);
                } else {
                    var_r31 = M2C_FIELD(temp_r3_2, s32 *, 0x28);
                }
                _fsysWriteCache((void *)(temp_r3), (void *)(temp_r3_2), (long)(M2C_FIELD(M2C_FIELD(temp_r3_2, u8 **, 0x30), s32 *, 8)), (unsigned long)((u32) M2C_FIELD(temp_r3_2, u8 **, 0x2C)), (void *)(_fsysGetTransLength((s32) M2C_FIELD(temp_r3_2, u32 *, 0x14), M2C_FIELD(temp_r3_2, s32 *, 0x28))), (void *)((u8 *) var_r31), (void *)(_fsysReadBlockCacheWriteCallback));
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
static void _fsysReadBlockCacheWriteCallback() {
    FsysArqTrans *temp_r3;

    temp_r3 = _fsysArq2ArqTrans((void*)(M2C_ERROR(/* Read from unset register $r3 */)));
    if (temp_r3 != NULL) {
        _fsysReadBlockHandling(M2C_FIELD(temp_r3, u8 **, 0x30), M2C_FIELD(temp_r3, u8 **, 0x34));
    }
}
}

extern "C" {
static void _fsysReadBlockHandling(void *p0, void *p1) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(p0, s32 *, 0x10);
    if (((temp_r0 == 1) || ((temp_r0 == 4) && (M2C_FIELD(p1, s32 *, 0xC) & 0x40000))) && ((u8) M2C_FIELD(p0, u8 *, 0x2C) != 1)) {
        _fsysMoveBlock((FsysBlock**)(((u8*)(p1) + 0x30)), (FsysBlock**)(((u8*)(p1) + 0x34)));
        return;
    }
    _fsysFreeBlock((FsysBlock**)(((u8*)(p1) + 0x30)), 0U);
}
}

extern "C" {
static void _fsysReadDataNext(void *p0, void *p1) {
    GSdvdFile *temp_r3;
    s32 temp_r4;

    M2C_FIELD(p1, u32 *, 0x28) = (u32) (M2C_FIELD(p1, u32 *, 0x28) + _fsysBlockByteSize);
    if (((s32) M2C_FIELD(p0, s32 *, 0x10) == 4) && !(M2C_FIELD(p1, s32 *, 0xC) & 0x40000)) {
        M2C_FIELD(p1, u32 *, 0x44) = (u32) (M2C_FIELD(p1, u32 *, 0x44) + _fsysBlockByteSize);
        M2C_FIELD(p1, s32 *, 0x4C) = (s32) (M2C_FIELD(p1, s32 *, 0x4C) | _fsysStreamGetReadBlockFlag(M2C_FIELD(p1, u32 *, 0x48)));
        M2C_FIELD(p1, u32 *, 0x48) = (u32) (M2C_FIELD(p1, u32 *, 0x48) + _fsysBlockByteSize);
        if ((u32) M2C_FIELD(p1, u32 *, 0x48) >= _fsysStreamGetCacheSize()) {
            M2C_FIELD(p1, u32 *, 0x48) = 0U;
        }
        if ((u8) M2C_FIELD(p0, u8 *, 0x2C) == 1) {
            _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), 0xAU);
            return;
        }
        if ((u32) M2C_FIELD(p1, u32 *, 0x28) >= (u32) M2C_FIELD(p1, u32 *, 0x54)) {
            if (M2C_FIELD(p1, s32 *, 0xC) & 0x800) {
                _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 2U);
                return;
            }
            if ((u32) M2C_FIELD(p1, u32 *, 0x28) < _fsysStreamGetCacheSize()) {
                M2C_FIELD(p1, s32 *, 0xC) = (s32) (M2C_FIELD(p1, s32 *, 0xC) | 0x800000);
                _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 2U);
                M2C_FIELD(p1, s32 *, 0x4C) = -1;
                return;
            }
            M2C_FIELD(p1, u32 *, 0x28) = (u32) M2C_FIELD(p1, u32 *, 0x50);
            goto block_12;
        }
block_12:
        if ((u32) M2C_FIELD(p1, u32 *, 0x44) >= _fsysStreamGetCacheSize()) {
            _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 5U);
            return;
        }
        if ((_fsysGetActiveTask(1) + _fsysGetActiveTask(2)) != 0) {
            _fsysResHeaderSetTaskStatus((FsysResHeader*)((FsysResHeader *) p1), 5U);
            return;
        }
        goto block_28;
    }
    if ((u32) M2C_FIELD(p1, u32 *, 0x28) >= (u32) M2C_FIELD(p1, u32 *, 0x14)) {
        temp_r3 = M2C_FIELD(p1, GSdvdFile **, 0x38);
        if (temp_r3 != NULL) {
            M2C_FIELD(p1, GSdvdFile **, 0x38) = NULL;
            GSdvdClose((GSdvdFile*)(temp_r3));
        }
        if ((s32) M2C_FIELD(p0, s32 *, 0x10) == 4) {
            temp_r4 = M2C_FIELD(p0, s32 *, 0x38);
            if (temp_r4 != 0) {
                M2C_FIELD(p0, u32 *, 0x24) = _fsysID2Index((FsysWork*)((FsysWork *) p0), (u32) temp_r4);
                goto block_25;
            }
        }
        if (_fsysID2Index((FsysWork*)((FsysWork *) p0), M2C_FIELD(p0, u32 *, 8)) != -1U) {
            _fsysWorkSetTaskStatus((FsysWork*)((FsysWork *) p0), 0xAU);
            return;
        }
        M2C_FIELD(p0, u32 *, 0x24) = (u32) (M2C_FIELD(p0, u32 *, 0x24) + 1);
block_25:
        if ((u32) M2C_FIELD(p0, u32 *, 0x24) >= (u32) M2C_FIELD(_fsysGetHeader((Fsys*)((Fsys *) p0)), u32 *, 0xC)) {
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
FsysResHeader* _fsysGetResHeader(Fsys* p0, u32 p1) { return 0; }
extern "C" {
FsysHeader* _fsysGetHeader(Fsys* p0) {
    FsysHeader *temp_r4;

    temp_r4 = M2C_FIELD(p0, FsysHeader **, 0x20);
    if (temp_r4 == NULL) {
        return NULL;
    }
    if ((u8) M2C_FIELD(p0, u8 *, 0x2E) == 0) {
        return NULL;
    }
    return temp_r4;
}
}

extern "C" {
static u8 _fsysAdjustReadFile(void *p0) {
    FsysHeader *temp_r31;
    u16 var_r29;

    temp_r31 = _fsysGetHeader((Fsys*)((Fsys *) p0));
    var_r29 = 0;
loop_3:
    if (var_r29 < (u32) M2C_FIELD(temp_r31, u32 *, 0xC)) {
        if (_fsysCheckCache(M2C_FIELD(p0, s32 *, 0), (u8 *) var_r29) != 0) {
            var_r29 += 1;
            goto loop_3;
        }
    }
    if (var_r29 >= (u32) M2C_FIELD(temp_r31, u32 *, 0xC)) {
        return 0U;
    }
    M2C_FIELD(p0, s32 *, 0x24) = (s32) var_r29;
    return 1U;
}
}

extern "C" {
#pragma optimize_for_size on
static u8 _fsysExpandFile(void *p0) {
    FsysResHeader *temp_r3;

    if ((M2C_FIELD(p0, u32 *, 0x28)) >= (u32) M2C_FIELD(_fsysGetHeader((Fsys*)((Fsys *) p0)), u32 *, 0xC)) {
        return 0U;
    }
    temp_r3 = _fsysGetResHeader((Fsys*)((Fsys *) p0), (M2C_FIELD(p0, u32 *, 0x28)));
    if (temp_r3 == NULL) {
        return 0U;
    }
    M2C_FIELD(p0, u32 *, 0x28) = (u32) (M2C_FIELD(p0, u32 *, 0x28) + 1);
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
    M2C_FIELD(temp_r3, u8 **, 0x10) = (unsigned char *)(p1);
    M2C_FIELD(temp_r3, u8 **, 0xC) = (unsigned char *)(p0);
    if (M2C_FIELD(p1, s32 *, 0xC) & 0x80000000) {
        M2C_FIELD(temp_r3, s8 *, 0xA) = 1;
    } else {
        M2C_FIELD(temp_r3, s8 *, 0xA) = 0;
    }
    _fsysAddBGWork((FsysBG*)(temp_r3));
    OSRestoreInterrupts(temp_r31);
    return 1U;
}
}

extern "C" {
s32* _fsysGetDataType(u32 p0) {
    s32 *var_r4;
    u32 var_ctr;

    var_r4 = &fsys_datatype;
    var_ctr = fsys_datatype_number;
    if (fsys_datatype_number > 0U) {
loop_1:
        if ((u32) M2C_FIELD(var_r4, u32 *, 4) == p0) {
            return var_r4;
        }
        var_r4 += 0x10;
        var_ctr -= 1;
        if (var_ctr == 0U) {
            /* Duplicate return node #4. Try simplifying control flow for better match */
            return NULL;
        }
        goto loop_1;
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
