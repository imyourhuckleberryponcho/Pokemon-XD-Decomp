// Partial: only the small vertex-format getters are written so far.
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
struct GSgfxLayer;
struct GSgfxVF;

struct GSgfxVF {
    u16 flags;        // 0x00
    u8 colorCount;    // 0x02
    u8 textureCount;  // 0x03
};

extern "C" {

// ---- draft declarations ----
struct GSgfxLayer {
    u8 _draft[1];
    void ResetVertexFormat(GSgfxVF*);
};
struct _struct__vfPredefFmt_0x440 {
     GSgfxVF unk0;                       
     char pad0[0x440 - sizeof(GSgfxVF)];
};
extern "C" {
GSgfxLayer* GSgfxLayerGetLayerList();
s32* GSgfxVFBuildTemp(s32 p0, s32 p1, u8 p2, s32 p3, u8 p4, s32 p5, u8 p6, s32 p7, s32 p8, s32 arg_sp8);
void GSgfxVFCreate(GSgfxVF* vf);
void GSgfxVFFree(GSgfxVF* vf);
GSgfxVF* GSgfxVFGetPredef(s32 id);
s32 GSgfxVFHasElement(s32 p0, s32 p1);
void GSgfxVFInit(GSgfxVF* vf);
void GSgfxVFSetArray(GSgfxVF* vf, s32, s32, void*, s32, s32);
void GSgfxVFSetElement(GSgfxVF* vf, s32, s32, s32, s32);
void* memset(void* dst, int val, size_t n);
}
extern "C++" {
void GSgfxVFInit();
}
static u32 _vfAllocIndex;
static u8 _vfElemTable[1];
static s32 _vfLocal[0x110];
static struct _struct__vfPredefFmt_0x440 _vfPredefFmt[9];
// ---- draft declarations ----


extern "C" {
void GSgfxVFRemoveElement(void *p0, s32 p1);
}

u8 GSgfxVFGetTextureCount(GSgfxVF* vf) {
    return vf->textureCount;
}

u8 GSgfxVFGetColorCount(GSgfxVF* vf) {
    return vf->colorCount;
}
extern "C" {
void GSgfxVFSetArray(GSgfxVF* p0, s32 p1, s32 p2, void* p3, s32 p4, s32 p5) {
    s32 *var_r5_2;
    s32 *var_r9;
    s32 *var_r9_2;
    s32 temp_r0;
    s32 temp_r0_3;
    s32 temp_r0_4;
    u32 temp_r11;
    u32 temp_r0_5;
    u32 var_ctr;
    u8 *var_r9_3;
    u32 var_r10;
    u32 var_r5_4;
    u8 *var_r10_2;
    u8 *var_r5;
    u8 *var_r5_3;
    u32 var_ctr_2;

    if ((p3 != NULL) || ((u32) (p5 + 0x10000) == -1U) || ((p3 != NULL) && ((u32) p5 != 0U))) {
        var_r9 = (long *)(((u8*)(p0) + 0x1B8));
loop_8:
        temp_r0 = *var_r9;
        if (temp_r0 == 0xFF) {
            var_r9 = NULL;
        } else if (temp_r0 == p1) {

        } else {
            var_r9 += 8;
            goto loop_8;
        }
        M2C_FIELD(var_r9, s32 *, 4) = p2;
        var_r5 = ((u8*)(p0) + 0x290);
loop_14:
        if ((M2C_FIELD(var_r5, s32 *, 4)) == 0xFF) {
            var_r5 = NULL;
        } else if ((M2C_FIELD(var_r5, s32 *, 4)) == p1) {

        } else {
            var_r5 += 0x10;
            goto loop_14;
        }
        if (var_r5 == NULL) {
            var_r10 = 0;
            var_r5_2 = (long *)(_vfElemTable);
loop_21:
            temp_r0_3 = *var_r5_2;
            if (temp_r0_3 == 0xFF) {
                var_r10 = 0;
            } else if (p1 == temp_r0_3) {

            } else {
                var_r5_2 += 4;
                var_r10 += 1;
                goto loop_21;
            }
            var_r9_2 = (long *)(&_vfElemTable[var_r10]);
loop_32:
            if (var_r10 == 0) {
                var_r10_2 = NULL;
            } else {
                temp_r0_4 = M2C_FIELD(var_r9_2, s32 *, -4);
                var_r9_2 -= 4;
                var_r5_3 = ((u8*)(p0) + 0x290);
                var_r10 -= 1;
loop_28:
                temp_r11 = M2C_FIELD(var_r5_3, s32 *, 4);
                if (temp_r11 == 0xFF) {
                    var_r5_3 = NULL;
                } else if (temp_r11 == temp_r0_4) {

                } else {
                    var_r5_3 += 0x10;
                    goto loop_28;
                }
                if (var_r5_3 != NULL) {
                    var_r10_2 = var_r5_3 + 0x10;
                } else {
                    goto loop_32;
                }
            }
            if (var_r10_2 == NULL) {
                var_r10_2 = ((u8*)(p0) + 0x290);
            }
            var_r9_3 = var_r10_2;
            while ((s32) M2C_FIELD(var_r9_3, s32 *, 4) != 0xFF) {
                var_r9_3 += 0x10;
            }
            var_r5_4 = (u32) ((var_r9_3 + 0x10) - var_r10_2) >> 4U;
            if (var_r9_3 >= var_r10_2) {
                temp_r0_5 = var_r5_4 >> 3U;
                var_ctr = temp_r0_5;
                if (temp_r0_5 != 0) {
                    do {
                        M2C_FIELD(var_r9_3, s32 *, 0x14) = (s32) M2C_FIELD(var_r9_3, s32 *, 4);
                        M2C_FIELD(var_r9_3, s32 *, 0x18) = (s32) M2C_FIELD(var_r9_3, s32 *, 8);
                        M2C_FIELD(var_r9_3, u8 *, 0x12) = (u8) M2C_FIELD(var_r9_3, u8 *, 2);
                        M2C_FIELD(var_r9_3, s32 *, 4) = (s32) M2C_FIELD(var_r9_3, s32 *, -0xC);
                        M2C_FIELD(var_r9_3, s32 *, 8) = (s32) M2C_FIELD(var_r9_3, s32 *, -8);
                        M2C_FIELD(var_r9_3, u8 *, 2) = (u8) M2C_FIELD(var_r9_3, u8 *, -0xE);
                        M2C_FIELD(var_r9_3, s32 *, -0xC) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x1C);
                        M2C_FIELD(var_r9_3, s32 *, -8) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x18);
                        M2C_FIELD(var_r9_3, u8 *, -0xE) = (u8) M2C_FIELD(var_r9_3, u8 *, -0x1E);
                        M2C_FIELD(var_r9_3, s32 *, -0x1C) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x2C);
                        M2C_FIELD(var_r9_3, s32 *, -0x18) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x28);
                        M2C_FIELD(var_r9_3, u8 *, -0x1E) = (u8) M2C_FIELD(var_r9_3, u8 *, -0x2E);
                        M2C_FIELD(var_r9_3, s32 *, -0x2C) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x3C);
                        M2C_FIELD(var_r9_3, s32 *, -0x28) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x38);
                        M2C_FIELD(var_r9_3, u8 *, -0x2E) = (u8) M2C_FIELD(var_r9_3, u8 *, -0x3E);
                        M2C_FIELD(var_r9_3, s32 *, -0x3C) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x4C);
                        M2C_FIELD(var_r9_3, s32 *, -0x38) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x48);
                        M2C_FIELD(var_r9_3, u8 *, -0x3E) = (u8) M2C_FIELD(var_r9_3, u8 *, -0x4E);
                        M2C_FIELD(var_r9_3, s32 *, -0x4C) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x5C);
                        M2C_FIELD(var_r9_3, s32 *, -0x48) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x58);
                        M2C_FIELD(var_r9_3, u8 *, -0x4E) = (u8) M2C_FIELD(var_r9_3, u8 *, -0x5E);
                        M2C_FIELD(var_r9_3, s32 *, -0x5C) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x6C);
                        M2C_FIELD(var_r9_3, s32 *, -0x58) = (s32) M2C_FIELD(var_r9_3, s32 *, -0x68);
                        M2C_FIELD(var_r9_3, u8 *, -0x5E) = (u8) M2C_FIELD(var_r9_3, u8 *, -0x6E);
                        var_r9_3 -= 0x80;
                        var_ctr -= 1;
                    } while (var_ctr != 0);
                    var_r5_4 &= 7;
                    if (var_r5_4 != 0) {
                        goto block_43;
                    }
                } else {
block_43:
                    var_ctr_2 = var_r5_4;
                    do {
                        M2C_FIELD(var_r9_3, s32 *, 0x14) = (s32) M2C_FIELD(var_r9_3, s32 *, 4);
                        M2C_FIELD(var_r9_3, s32 *, 0x18) = (s32) M2C_FIELD(var_r9_3, s32 *, 8);
                        M2C_FIELD(var_r9_3, u8 *, 0x12) = (u8) M2C_FIELD(var_r9_3, u8 *, 2);
                        var_r9_3 -= 0x10;
                        var_ctr_2 -= 1;
                    } while (var_ctr_2 != 0);
                }
            }
            var_r5 = var_r10_2;
        }
        M2C_FIELD(var_r5, u16 *, 0) = 0U;
        M2C_FIELD(var_r5, s32 *, 4) = p1;
        M2C_FIELD(var_r5, u8 **, 8) = (unsigned char *)(p3);
        M2C_FIELD(var_r5, s8 *, 2) = (s8) p4;
        M2C_FIELD(var_r5, s32 *, 0xC) = p5;
        if ((u32) (((s32) M2C_FIELD(var_r5, u8 **, 8) & 0xC0000000) + 0x80000000) == 0U) {
            M2C_FIELD(var_r5, u16 *, 0) = (u16) (M2C_FIELD(var_r5, u16 *, 0) | 1);
        }
        (*(s32*)(p0)) = ((*(s32*)(p0)) | 0xC);
    }
}
extern "C" {
void GSgfxVFRemoveElement(void *p0, s32 p1) {
    u8 *var_r5_2;
    u8 *var_r5_3;
    s32 *var_r6_2;
    s32 *var_r6_3;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_5;
    s32 temp_r0_7;
    s32 temp_r4;
    s32 temp_r4_2;
    u8 temp_r0_4;
    u8 temp_r0_6;
    bool var_r4_2;
    u8 var_r5_4;
    u8 var_r6_4;
    u8 var_r7;
    u8 *temp_r5;
    u8 *var_r4;
    u8 *var_r5;
    s32 *var_r5_5;
    s32 *var_r6;

    var_r6 = (long *)(((u8*)(p0) + 0x1B8));
    var_r7 = 0;
loop_4:
    temp_r0 = *var_r6;
    if (temp_r0 == 0xFF) {
        var_r6 = NULL;
    } else if (temp_r0 == p1) {

    } else {
        var_r6 += 8;
        goto loop_4;
    }
    if (var_r6 != NULL) {
        var_r5 = (unsigned char *)(var_r6 + 8);
loop_9:
        if ((s32) M2C_FIELD(var_r6, s32 *, 0) != 0xFF) {
            M2C_FIELD(var_r6, s32 *, 0) = M2C_FIELD(var_r5, s32 *, 0);
            temp_r0_2 = M2C_FIELD(var_r5, s32 *, 4);
            var_r5 += 8;
            M2C_FIELD(var_r6, s32 *, 4) = temp_r0_2;
            var_r6 += 8;
            goto loop_9;
        }
        var_r7 = 1;
    }
    if ((p1 >= 9) || (p1 < 0)) {
        var_r6_2 = (long *)(((u8*)(p0) + 8));
loop_17:
        temp_r0_3 = *var_r6_2;
        if (temp_r0_3 == 0xFF) {
            var_r6_2 = NULL;
        } else if (temp_r0_3 == p1) {

        } else {
            var_r6_2 += 0x10;
            goto loop_17;
        }
        if (var_r6_2 != NULL) {
            var_r5_2 = (unsigned char *)(var_r6_2 + 0x10);
            while ((s32) M2C_FIELD(var_r6_2, s32 *, 0) != 0xFF) {
                M2C_FIELD(var_r6_2, s32 *, 0) = M2C_FIELD(var_r5_2, s32 *, 0);
                M2C_FIELD(var_r6_2, s32 *, 4) = (s32) M2C_FIELD(var_r5_2, s32 *, 4);
                M2C_FIELD(var_r6_2, s32 *, 8) = (s32) M2C_FIELD(var_r5_2, s32 *, 8);
                temp_r0_4 = M2C_FIELD(var_r5_2, u8 *, 0xC);
                var_r5_2 += 0x10;
                M2C_FIELD(var_r6_2, u8 *, 0xC) = temp_r0_4;
                var_r6_2 += 0x10;
            }
            var_r7 = 1;
        }
        var_r5_3 = ((u8*)(p0) + 0x290);
loop_28:
        temp_r0_5 = M2C_FIELD(var_r5_3, s32 *, 4);
        if (temp_r0_5 == 0xFF) {
            var_r5_3 = NULL;
        } else if (temp_r0_5 == p1) {

        } else {
            var_r5_3 += 0x10;
            goto loop_28;
        }
        if (var_r5_3 != NULL) {
            var_r4 = var_r5_3 + 0x10;
            while ((s32) M2C_FIELD(var_r5_3, s32 *, 4) != 0xFF) {
                M2C_FIELD(var_r5_3, s32 *, 4) = (s32) M2C_FIELD(var_r4, s32 *, 4);
                M2C_FIELD(var_r5_3, s32 *, 8) = (s32) M2C_FIELD(var_r4, s32 *, 8);
                temp_r0_6 = M2C_FIELD(var_r4, u8 *, 2);
                var_r4 += 0x10;
                M2C_FIELD(var_r5_3, u8 *, 2) = temp_r0_6;
                var_r5_3 += 0x10;
            }
            var_r7 = 1;
        }
    }
    if (var_r7 == 1) {
        var_r5_4 = 0;
        M2C_FIELD(p0, u8 *, 2) = 0U;
        M2C_FIELD(p0, u8 *, 3) = 0U;
        M2C_FIELD(p0, u16 *, 0) = (u16) (M2C_FIELD(p0, u16 *, 0) & 0xFFFFFFF7);
loop_45:
        if (var_r5_4 < 2U) {
            var_r6_3 = (long *)(((u8*)(p0) + 8));
loop_41:
            temp_r4 = *var_r6_3;
            if (temp_r4 == 0xFF) {
                var_r6_3 = NULL;
            } else if (temp_r4 == (s32) (var_r5_4 + 0xB)) {

            } else {
                var_r6_3 += 0x10;
                goto loop_41;
            }
            if (var_r6_3 != NULL) {
                var_r5_4 += 1;
                M2C_FIELD(p0, u8 *, 2) = (u8) (M2C_FIELD(p0, u8 *, 2) + 1);
                goto loop_45;
            }
        }
        var_r6_4 = 0;
loop_55:
        if (var_r6_4 < 8U) {
            var_r5_5 = (long *)(((u8*)((u8)p0) + 8));
loop_51:
            temp_r4_2 = *var_r5_5;
            if (temp_r4_2 == 0xFF) {
                var_r5_5 = NULL;
            } else if (temp_r4_2 == (s32) (var_r6_4 + 0xD)) {

            } else {
                var_r5_5 += 0x10;
                goto loop_51;
            }
            if (var_r5_5 != NULL) {
                var_r6_4 += 1;
                M2C_FIELD(p0, u8 *, 3) = (u8) (M2C_FIELD(p0, u8 *, 3) + 1);
                goto loop_55;
            }
        }
        var_r4_2 = 0;
loop_62:
        if (var_r4_2 < 0x1BU) {
            temp_r5 = (u8*)(p0) + ((var_r4_2 * 8) & 0x7F8);
            if ((s32) M2C_FIELD(temp_r5, s32 *, 0x1B8) != 0xFF) {
                temp_r0_7 = M2C_FIELD(temp_r5, s32 *, 0x1BC);
                if ((temp_r0_7 == 2) || (temp_r0_7 == 3)) {
                    M2C_FIELD(p0, u16 *, 0) = (u16) (M2C_FIELD(p0, u16 *, 0) | 8);
                } else {
                    var_r4_2 += 1;
                    goto loop_62;
                }
            }
        }
        M2C_FIELD(p0, u16 *, 0) = (u16) (M2C_FIELD(p0, u16 *, 0) | 6);
    }
}
}

}

extern "C" {
extern "C" {
void GSgfxVFSetElement(GSgfxVF* p0, s32 p1, s32 p2, s32 p3, s32 p4) {
    goto loop_4;
    s32 *var_r3;
    s32 *var_r3_2;
    s32 *var_r4;
    s32 *var_r4_2;
    s32 *var_r4_4;
    s32 *var_r4_5;
    s32 *var_r4_7;
    s32 *var_r5;
    s32 *var_r5_2;
    s32 *var_r5_4;
    s32 *var_r5_5;
    s32 *var_r6_2;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_7;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r6;
    s32 temp_r7;
    u32 temp_r0_3;
    u32 temp_r0_6;
    u32 var_ctr;
    u32 var_ctr_2;
    u32 var_ctr_3;
    u32 var_ctr_4;
    u32 var_r3_3;
    u32 var_r4_3;
    u32 var_r5_3;
    u32 var_r6;
    u8 var_r3_4;
    u8 var_r4_6;
    u8 var_r5_6;
    u8 *temp_r4;

    var_r6 = 0;
    var_r3 = (long *)(_vfElemTable);
    var_r4 = (long *)(_vfElemTable);
loop_4:
    temp_r0 = *var_r4;
    if (temp_r0 == 0xFF) {
        var_r6 = 0;
    } else if (p1 == temp_r0) {

    } else {
        var_r4 += 4;
        var_r6 += 1;
    }
    var_r5 = (long *)(&_vfElemTable[var_r6]);
loop_15:
    if (var_r6 == 0) {
        var_r6_2 = NULL;
    } else {
        temp_r0_2 = M2C_FIELD(var_r5, s32 *, -4);
        var_r5 -= 4;
        var_r4_2 = (long *)(((u8*)((u16)p0) + 0x1B8));
        var_r6 -= 1;
loop_11:
        temp_r7 = *var_r4_2;
        if (temp_r7 == 0xFF) {
            var_r4_2 = NULL;
        } else if (temp_r7 == temp_r0_2) {

        } else {
            var_r4_2 += 8;
            goto loop_11;
        }
        if (var_r4_2 != NULL) {
            var_r6_2 = var_r4_2 + 8;
        } else {
            goto loop_15;
        }
    }
    if (var_r6_2 == NULL) {
        var_r6_2 = (long *)(((u8*)(p0) + 0x1B8));
    }
    var_r5_2 = var_r6_2;
    while ((s32) *var_r5_2 != 0xFF) {
        var_r5_2 += 8;
    }
    var_r4_3 = (u32) ((var_r5_2 + 8) - var_r6_2) >> 3U;
    if (var_r5_2 >= var_r6_2) {
        temp_r0_3 = var_r4_3 >> 3U;
        var_ctr = temp_r0_3;
        if (temp_r0_3 != 0) {
            do {
                M2C_FIELD(var_r5_2, s32 *, 8) = (s32) M2C_FIELD(var_r5_2, s32 *, 0);
                M2C_FIELD(var_r5_2, s32 *, 0xC) = (s32) M2C_FIELD(var_r5_2, s32 *, 4);
                M2C_FIELD(var_r5_2, s32 *, 0) = M2C_FIELD(var_r5_2, s32 *, -8);
                M2C_FIELD(var_r5_2, s32 *, 4) = (s32) M2C_FIELD(var_r5_2, s32 *, -4);
                M2C_FIELD(var_r5_2, s32 *, -8) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x10);
                M2C_FIELD(var_r5_2, s32 *, -4) = (s32) M2C_FIELD(var_r5_2, s32 *, -0xC);
                M2C_FIELD(var_r5_2, s32 *, -0x10) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x18);
                M2C_FIELD(var_r5_2, s32 *, -0xC) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x14);
                M2C_FIELD(var_r5_2, s32 *, -0x18) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x20);
                M2C_FIELD(var_r5_2, s32 *, -0x14) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x1C);
                M2C_FIELD(var_r5_2, s32 *, -0x20) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x28);
                M2C_FIELD(var_r5_2, s32 *, -0x1C) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x24);
                M2C_FIELD(var_r5_2, s32 *, -0x28) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x30);
                M2C_FIELD(var_r5_2, s32 *, -0x24) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x2C);
                M2C_FIELD(var_r5_2, s32 *, -0x30) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x38);
                M2C_FIELD(var_r5_2, s32 *, -0x2C) = (s32) M2C_FIELD(var_r5_2, s32 *, -0x34);
                var_r5_2 -= 0x40;
                var_ctr -= 1;
            } while (var_ctr != 0);
            var_r4_3 &= 7;
            if (var_r4_3 != 0) {
                goto block_26;
            }
        } else {
block_26:
            var_ctr_2 = var_r4_3;
            do {
                M2C_FIELD(var_r5_2, s32 *, 8) = (s32) M2C_FIELD(var_r5_2, s32 *, 0);
                M2C_FIELD(var_r5_2, s32 *, 0xC) = (s32) M2C_FIELD(var_r5_2, s32 *, 4);
                var_r5_2 -= 8;
                var_ctr_2 -= 1;
            } while (var_ctr_2 != 0);
        }
    }
    M2C_FIELD(var_r6_2, s32 *, 0) = p1;
    M2C_FIELD(var_r6_2, s32 *, 4) = 1;
    if ((p1 >= 9) || (p1 < 0)) {
        var_r5_3 = 0;
loop_34:
        temp_r0_4 = *var_r3;
        if (temp_r0_4 == 0xFF) {
            var_r5_3 = 0;
        } else if (p1 == temp_r0_4) {

        } else {
            var_r3 += 4;
            var_r5_3 += 1;
            goto loop_34;
        }
        var_r4_4 = (long *)(&_vfElemTable[var_r5_3]);
loop_45:
        if (var_r5_3 == 0) {
            var_r5_4 = NULL;
        } else {
            temp_r0_5 = M2C_FIELD(var_r4_4, s32 *, -4);
            var_r4_4 -= 4;
            var_r3_2 = (long *)(((u8*)(p0) + 8));
            var_r5_3 -= 1;
loop_41:
            temp_r6 = *var_r3_2;
            if (temp_r6 == 0xFF) {
                var_r3_2 = NULL;
            } else if (temp_r6 == temp_r0_5) {

            } else {
                var_r3_2 += 0x10;
                goto loop_41;
            }
            if (var_r3_2 != NULL) {
                var_r5_4 = var_r3_2 + 0x10;
            } else {
                goto loop_45;
            }
        }
        if (var_r5_4 == NULL) {
            var_r5_4 = (long *)(((u8*)(p0) + 8));
        }
        var_r4_5 = var_r5_4;
loop_51:
        if ((s32) *var_r4_5 != 0xFF) {
            var_r4_5 += 0x10;
            goto loop_51;
        }
        var_r3_3 = ((var_r4_5 + 0x10) - var_r5_4) >> 4U;
        if (var_r4_5 >= var_r5_4) {
            temp_r0_6 = var_r3_3 >> 2U;
            var_ctr_3 = temp_r0_6;
            if (temp_r0_6 != 0) {
                do {
                    M2C_FIELD(var_r4_5, s32 *, 0x10) = (s32) M2C_FIELD(var_r4_5, s32 *, 0);
                    M2C_FIELD(var_r4_5, s32 *, 0x14) = (s32) M2C_FIELD(var_r4_5, s32 *, 4);
                    M2C_FIELD(var_r4_5, s32 *, 0x18) = (s32) M2C_FIELD(var_r4_5, s32 *, 8);
                    M2C_FIELD(var_r4_5, u8 *, 0x1C) = (u8) M2C_FIELD(var_r4_5, u8 *, 0xC);
                    M2C_FIELD(var_r4_5, s32 *, 0) = M2C_FIELD(var_r4_5, s32 *, -0x10);
                    M2C_FIELD(var_r4_5, s32 *, 4) = (s32) M2C_FIELD(var_r4_5, s32 *, -0xC);
                    M2C_FIELD(var_r4_5, s32 *, 8) = (s32) M2C_FIELD(var_r4_5, s32 *, -8);
                    M2C_FIELD(var_r4_5, u8 *, 0xC) = (u8) M2C_FIELD(var_r4_5, u8 *, -4);
                    M2C_FIELD(var_r4_5, s32 *, -0x10) = (s32) M2C_FIELD(var_r4_5, s32 *, -0x20);
                    M2C_FIELD(var_r4_5, s32 *, -0xC) = (s32) M2C_FIELD(var_r4_5, s32 *, -0x1C);
                    M2C_FIELD(var_r4_5, s32 *, -8) = (s32) M2C_FIELD(var_r4_5, s32 *, -0x18);
                    M2C_FIELD(var_r4_5, u8 *, -4) = (u8) M2C_FIELD(var_r4_5, u8 *, -0x14);
                    M2C_FIELD(var_r4_5, s32 *, -0x20) = (s32) M2C_FIELD(var_r4_5, s32 *, -0x30);
                    M2C_FIELD(var_r4_5, s32 *, -0x1C) = (s32) M2C_FIELD(var_r4_5, s32 *, -0x2C);
                    M2C_FIELD(var_r4_5, s32 *, -0x18) = (s32) M2C_FIELD(var_r4_5, s32 *, -0x28);
                    M2C_FIELD(var_r4_5, u8 *, -0x14) = (u8) M2C_FIELD(var_r4_5, u8 *, -0x24);
                    var_r4_5 -= 0x40;
                    var_ctr_3 -= 1;
                } while (var_ctr_3 != 0);
                var_r3_3 &= 3;
                if (var_r3_3 != 0) {
                    goto block_56;
                }
            } else {
block_56:
                var_ctr_4 = var_r3_3;
                do {
                    M2C_FIELD(var_r4_5, s32 *, 0x10) = (s32) M2C_FIELD(var_r4_5, s32 *, 0);
                    M2C_FIELD(var_r4_5, s32 *, 0x14) = (s32) M2C_FIELD(var_r4_5, s32 *, 4);
                    M2C_FIELD(var_r4_5, s32 *, 0x18) = (s32) M2C_FIELD(var_r4_5, s32 *, 8);
                    M2C_FIELD(var_r4_5, u8 *, 0x1C) = (u8) M2C_FIELD(var_r4_5, u8 *, 0xC);
                    var_r4_5 -= 0x10;
                    var_ctr_4 -= 1;
                } while (var_ctr_4 != 0);
            }
        }
        M2C_FIELD(var_r5_4, s32 *, 0) = p1;
        M2C_FIELD(var_r5_4, s32 *, 4) = p2;
        M2C_FIELD(var_r5_4, s32 *, 8) = p3;
        M2C_FIELD(var_r5_4, s8 *, 0xC) = (s8) p4;
    }
    var_r4_6 = 0;
    M2C_FIELD(p0, u8 *, 2) = 0U;
    M2C_FIELD(p0, u8 *, 3) = 0U;
    M2C_FIELD(p0, u16 *, 0) = (u16) (M2C_FIELD(p0, u16 *, 0) & 0xFFFFFFF7);
loop_68:
    if (var_r4_6 < 2U) {
        var_r5_5 = (long *)(((u8*)(p0) + 8));
loop_64:
        temp_r3 = *var_r5_5;
        if (temp_r3 == 0xFF) {
            var_r5_5 = NULL;
        } else if (temp_r3 == (s32) (var_r4_6 + 0xB)) {

        } else {
            var_r5_5 += 0x10;
            goto loop_64;
        }
        if (var_r5_5 != NULL) {
            var_r4_6 += 1;
            M2C_FIELD(p0, u8 *, 2) = (u8) (M2C_FIELD(p0, u8 *, 2) + 1);
            goto loop_68;
        }
    }
    var_r5_6 = 0;
loop_78:
    if (var_r5_6 < 8U) {
        var_r4_7 = (long *)(((u8*)(p0) + 8));
loop_74:
        temp_r3_2 = *var_r4_7;
        if (temp_r3_2 == 0xFF) {
            var_r4_7 = NULL;
        } else if (temp_r3_2 == (s32) (var_r5_6 + 0xD)) {

        } else {
            var_r4_7 += 0x10;
            goto loop_74;
        }
        if (var_r4_7 != NULL) {
            var_r5_6 += 1;
            M2C_FIELD(p0, u8 *, 3) = (u8) (M2C_FIELD(p0, u8 *, 3) + 1);
            goto loop_78;
        }
    }
    var_r3_4 = 0;
loop_85:
    if (var_r3_4 < 0x1BU) {
        temp_r4 = (unsigned char *)((u8*)p0 + ((var_r3_4 * 8) & 0x7F8));
        if ((s32) M2C_FIELD(temp_r4, s32 *, 0x1B8) != 0xFF) {
            temp_r0_7 = M2C_FIELD(temp_r4, s32 *, 0x1BC);
            if ((temp_r0_7 == 2) || (temp_r0_7 == 3)) {
                M2C_FIELD(p0, u16 *, 0) = (u16) (M2C_FIELD(p0, u16 *, 0) | 8);
            } else {
                var_r3_4 += 1;
                goto loop_85;
            }
        }
    }
    M2C_FIELD(p0, u16 *, 0) = (u16) (M2C_FIELD(p0, u16 *, 0) | 6);
}
}

extern "C" {
// vertex format elements: 8-byte {type, data} entries at +0x1B8, terminated by type 0xFF
struct GSgfxVFElement {
    s32 type;
    s32 data;
};

static inline GSgfxVFElement* vfFindElement(GSgfxVF* vf, s32 type) {
    GSgfxVFElement* e;
    s32 t;
    for (e = (GSgfxVFElement*)((u8*)vf + 0x1B8); (t = e->type) != 0xFF; e++) {
        if (t == type) {
            return e;
        }
    }
    return NULL;
}

s32 GSgfxVFHasElement(s32 vf, s32 type) {
    if (vfFindElement((GSgfxVF*)vf, type) != NULL) {
        return 1;
    }
    return 0;
}

void GSgfxVFFree(GSgfxVF* vf) {
    GSgfxLayer* layer;
    if (vf != (GSgfxVF*)_vfLocal && (vf->flags & 1)) {
        vf->flags &= ~1;
        for (layer = GSgfxLayerGetLayerList(); layer != NULL; layer = *(GSgfxLayer**)layer) {
            layer->ResetVertexFormat(vf);
        }
    }
}

}

}


u32 GSgfxVFIsUsed(GSgfxVF* vf) {
    return vf->flags & 1;
}
extern "C" {
GSgfxVF* GSgfxVFGetPredef(s32 p0) {
    return (GSgfxVF *) &_vfPredefFmt[p0];
}
}

extern "C" {
void GSgfxVFCreate(GSgfxVF* p0) {
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    u32 temp_r6;
    u32 var_r0;
    u8 *var_r4;
    u8 *var_r4_2;
    u8 *var_r6;

    temp_r6 = _vfAllocIndex;
    var_r0 = temp_r6 + 1;
    if (var_r0 >= 8U) {
        var_r0 = 0U;
    }
    _vfAllocIndex = var_r0;
    M2C_FIELD(p0, u32 *, 4) = temp_r6;
    var_r6 = ((u8*)(p0) + 0x180);
    M2C_FIELD(p0, u16 *, 0) = (u16) (M2C_FIELD((u16)p0, u16 *, 0) | 1);
    M2C_FIELD(p0, s32 *, 8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x18) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x28) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x38) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x48) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x58) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x68) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x78) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x88) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x98) = 0xFF;
    M2C_FIELD(p0, s32 *, 0xA8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0xB8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0xC8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0xD8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0xE8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0xF8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x108) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x118) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x128) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x138) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x148) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x158) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x168) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x178) = 0xFF;
    var_ctr = 0x1B - 0x18;
    if (0x18 < 0x1B) {
        do {
            M2C_FIELD(var_r6, s32 *, 8) = 0xFF;
            var_r6 += 0x10;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    M2C_FIELD(p0, s32 *, 0x1B8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x1C0) = 0xFF;
    var_r4 = ((u8*)(p0) + 0xC0);
    M2C_FIELD(p0, s32 *, 0x1C8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x1D0) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x1D8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x1E0) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x1E8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x1F0) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x1F8) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x200) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x208) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x210) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x218) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x220) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x228) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x230) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x238) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x240) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x248) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x250) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x258) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x260) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x268) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x270) = 0xFF;
    var_ctr_2 = 0x1B - 0x18;
    if (0x18 < 0x1B) {
        do {
            M2C_FIELD((u16)var_r4, s32 *, 0x1B8) = 0xFF;
            var_r4 += 8;
            var_ctr_2 -= 1;
        } while (var_ctr_2 != 0);
    }
    M2C_FIELD(p0, s32 *, 0x294) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x2A4) = 0xFF;
    var_r4_2 = ((u8*)(p0) + 0x180);
    M2C_FIELD(p0, s32 *, 0x2B4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x2C4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x2D4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x2E4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x2F4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x304) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x314) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x324) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x334) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x344) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x354) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x364) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x374) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x384) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x394) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x3A4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x3B4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x3C4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x3D4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x3E4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x3F4) = 0xFF;
    M2C_FIELD(p0, s32 *, 0x404) = 0xFF;
    var_ctr_3 = 0x1B - 0x18;
    if (0x18 < 0x1B) {
        do {
            M2C_FIELD((u16)var_r4_2, s32 *, 0x294) = 0xFF;
            var_r4_2 += 0x10;
            var_ctr_3 -= 1;
        } while (var_ctr_3 != 0);
    }
    M2C_FIELD(p0, u16 *, 0) = (u16) (M2C_FIELD(p0, u16 *, 0) | 6);
}
}

extern "C" {
void GSgfxVFInit(GSgfxVF* p0) {
    memset((void*)(p0), 0, 0x440U);
}
}

extern "C" {
s32* GSgfxVFBuildTemp(s32 p0, s32 p1, u8 p2, s32 p3, u8 p4, s32 p5, u8 p6, s32 p7, s32 p8, s32 arg_sp8) {
    u32 var_ctr_2;
    s32 *var_r12;
    s32 temp_r26;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r6;
    s32 temp_r8;
    s32 var_ctr_3;
    s32 var_r24;
    s32 var_r24_2;
    s32 *var_r11;
    s8 var_ctr;

    if (p3 == 2) {
        return NULL;
    }
    if (p4 > 2U) {
        return NULL;
    }
    if (p6 > 8U) {
        return NULL;
    }
    if (p5 < 0) {
        return NULL;
    }
    if (arg_sp8 > 4) {
        return NULL;
    }
    _vfLocal[2] = 9;
    var_r11 = &_vfLocal[6];
    var_r12 = &_vfLocal[0x70];
    _vfLocal[3] = p0;
    _vfLocal[4] = p1;
    M2C_FIELD(_vfLocal, s8 *, 0x14) = 0;
    _vfLocal[0x6E] = 9;
    _vfLocal[0x6F] = 1;
    if (p2 == 1) {
        switch (p3) {                               /* irregular */
        case 0:
            _vfLocal[7] = 0;
            _vfLocal[6] = 0xA;
            _vfLocal[0x70] = 0xA;
            break;
        case 1:
            _vfLocal[7] = 1;
            _vfLocal[6] = 0x19;
            _vfLocal[0x70] = 0x19;
            break;
        }
        _vfLocal[8] = 4;
        var_r11 += 0x10;
        _vfLocal[0x71] = 1;
        var_r12 += 8;
        M2C_FIELD(_vfLocal, s8 *, 0x24) = 0;
    }
    var_r24 = 0;
    var_ctr = p4;
    if (p4 > 0) {
        do {
            if (p5 < 2) {
                if (p5 < 0) {

                } else {
                    M2C_FIELD(var_r11, s32 *, 4) = 0;
                }
            } else if (p5 < 6) {
                M2C_FIELD(var_r11, s32 *, 4) = 1;
            }
            temp_r3 = var_r24 + 0xB;
            var_r24 += 1;
            M2C_FIELD(var_r11, s32 *, 8) = p5;
            M2C_FIELD(var_r11, s32 *, 0) = temp_r3;
            M2C_FIELD(var_r11, s8 *, 0xC) = 0;
            var_r11 += 0x10;
            M2C_FIELD(var_r12, s32 *, 0) = temp_r3;
            M2C_FIELD(var_r12, s32 *, 4) = 1;
            var_r12 += 8;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    var_r24_2 = 0;
    if (p6 > 0) {
        temp_r4 = p6 - 8;
        if (p6 > 8) {
            var_ctr_2 = (u32) (temp_r4 + 7) >> 3U;
            if (temp_r4 > 0) {
                do {
                    temp_r26 = var_r24_2 + 0xD;
                    M2C_FIELD(var_r11, s32 *, 0) = temp_r26;
                    temp_r29 = var_r24_2 + 0xE;
                    temp_r30 = var_r24_2 + 0xF;
                    M2C_FIELD(var_r11, s32 *, 4) = p7;
                    temp_r31 = var_r24_2 + 0x10;
                    temp_r8 = var_r24_2 + 0x11;
                    temp_r6 = var_r24_2 + 0x12;
                    M2C_FIELD(var_r11, s32 *, 8) = arg_sp8;
                    temp_r4_2 = var_r24_2 + 0x13;
                    temp_r3_2 = var_r24_2 + 0x14;
                    var_r24_2 += 8;
                    M2C_FIELD(var_r11, s8 *, 0xC) = 0;
                    M2C_FIELD(var_r12, s32 *, 0) = temp_r26;
                    M2C_FIELD(var_r12, s32 *, 4) = 1;
                    M2C_FIELD(var_r11, s32 *, 0x10) = temp_r29;
                    M2C_FIELD(var_r11, s32 *, 0x14) = p7;
                    M2C_FIELD(var_r11, s32 *, 0x18) = arg_sp8;
                    M2C_FIELD(var_r11, s8 *, 0x1C) = 0;
                    M2C_FIELD(var_r12, s32 *, 8) = temp_r29;
                    M2C_FIELD(var_r12, s32 *, 0xC) = 1;
                    M2C_FIELD(var_r11, s32 *, 0x20) = temp_r30;
                    M2C_FIELD(var_r11, s32 *, 0x24) = p7;
                    M2C_FIELD(var_r11, s32 *, 0x28) = arg_sp8;
                    M2C_FIELD(var_r11, s8 *, 0x2C) = 0;
                    M2C_FIELD(var_r12, s32 *, 0x10) = temp_r30;
                    M2C_FIELD(var_r12, s32 *, 0x14) = 1;
                    M2C_FIELD(var_r11, s32 *, 0x30) = temp_r31;
                    M2C_FIELD(var_r11, s32 *, 0x34) = p7;
                    M2C_FIELD(var_r11, s32 *, 0x38) = arg_sp8;
                    M2C_FIELD(var_r11, s8 *, 0x3C) = 0;
                    M2C_FIELD(var_r12, s32 *, 0x18) = temp_r31;
                    M2C_FIELD(var_r12, s32 *, 0x1C) = 1;
                    M2C_FIELD(var_r11, s32 *, 0x40) = temp_r8;
                    M2C_FIELD(var_r11, s32 *, 0x44) = p7;
                    M2C_FIELD(var_r11, s32 *, 0x48) = arg_sp8;
                    M2C_FIELD(var_r11, s8 *, 0x4C) = 0;
                    M2C_FIELD(var_r12, s32 *, 0x20) = temp_r8;
                    M2C_FIELD(var_r12, s32 *, 0x24) = 1;
                    M2C_FIELD(var_r11, s32 *, 0x50) = temp_r6;
                    M2C_FIELD(var_r11, s32 *, 0x54) = p7;
                    M2C_FIELD(var_r11, s32 *, 0x58) = arg_sp8;
                    M2C_FIELD(var_r11, s8 *, 0x5C) = 0;
                    M2C_FIELD(var_r12, s32 *, 0x28) = temp_r6;
                    M2C_FIELD(var_r12, s32 *, 0x2C) = 1;
                    M2C_FIELD(var_r11, s32 *, 0x60) = temp_r4_2;
                    M2C_FIELD(var_r11, s32 *, 0x64) = p7;
                    M2C_FIELD(var_r11, s32 *, 0x68) = arg_sp8;
                    M2C_FIELD(var_r11, s8 *, 0x6C) = 0;
                    M2C_FIELD(var_r12, s32 *, 0x30) = temp_r4_2;
                    M2C_FIELD(var_r12, s32 *, 0x34) = 1;
                    M2C_FIELD(var_r11, s32 *, 0x70) = temp_r3_2;
                    M2C_FIELD(var_r11, s32 *, 0x74) = p7;
                    M2C_FIELD(var_r11, s32 *, 0x78) = arg_sp8;
                    M2C_FIELD(var_r11, s8 *, 0x7C) = 0;
                    var_r11 += 0x80;
                    M2C_FIELD(var_r12, s32 *, 0x38) = temp_r3_2;
                    M2C_FIELD(var_r12, s32 *, 0x3C) = 1;
                    var_r12 += 0x40;
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
            }
        }
        var_ctr_3 = p6 - var_r24_2;
        if (var_r24_2 < (s32) p6) {
            do {
                temp_r3_3 = var_r24_2 + 0xD;
                var_r24_2 += 1;
                M2C_FIELD(var_r11, s32 *, 0) = temp_r3_3;
                M2C_FIELD(var_r11, s32 *, 4) = p7;
                M2C_FIELD(var_r11, s32 *, 8) = arg_sp8;
                M2C_FIELD(var_r11, s8 *, 0xC) = 0;
                var_r11 += 0x10;
                M2C_FIELD(var_r12, s32 *, 0) = temp_r3_3;
                M2C_FIELD(var_r12, s32 *, 4) = 1;
                var_r12 += 8;
                var_ctr_3 -= 1;
            } while (var_ctr_3 != 0);
        }
    }
    *var_r11 = 0xFF;
    *var_r12 = 0xFF;
    _vfLocal[0xA5] = 0xFF;
    M2C_FIELD(_vfLocal, s8 *, 2) = p4;
    M2C_FIELD(_vfLocal, s8 *, 3) = p6;
    M2C_FIELD(_vfLocal, u16 *, 0) = (u16) (M2C_FIELD(_vfLocal, u16 *, 0) | 6);
    return _vfLocal;
}
}

extern "C++" {
void GSgfxVFInit() {
    s32 *var_r3;
    s32 *var_r3_2;
    s32 *var_r3_3;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    u32 var_r6;

    var_r6 = 1U;
    _vfAllocIndex = 0U;
    if (1U >= 8U) {
        var_r6 = 0U;
    }
    _vfLocal[1] = 0;
    var_r3 = &_vfLocal[0x60];
    M2C_FIELD(_vfLocal, s16 *, 0) = (s16) (M2C_FIELD(_vfLocal, s16 *, 0) | 1);
    _vfLocal[2] = 0xFF;
    _vfLocal[6] = 0xFF;
    _vfLocal[0xA] = 0xFF;
    _vfLocal[0xE] = 0xFF;
    _vfLocal[0x12] = 0xFF;
    _vfLocal[0x16] = 0xFF;
    _vfLocal[0x1A] = 0xFF;
    _vfLocal[0x1E] = 0xFF;
    _vfLocal[0x22] = 0xFF;
    _vfLocal[0x26] = 0xFF;
    _vfLocal[0x2A] = 0xFF;
    _vfLocal[0x2E] = 0xFF;
    _vfLocal[0x32] = 0xFF;
    _vfLocal[0x36] = 0xFF;
    _vfLocal[0x3A] = 0xFF;
    _vfLocal[0x3E] = 0xFF;
    _vfLocal[0x42] = 0xFF;
    _vfLocal[0x46] = 0xFF;
    _vfLocal[0x4A] = 0xFF;
    _vfLocal[0x4E] = 0xFF;
    _vfLocal[0x52] = 0xFF;
    _vfLocal[0x56] = 0xFF;
    _vfLocal[0x5A] = 0xFF;
    _vfLocal[0x5E] = 0xFF;
    _vfAllocIndex = var_r6;
    var_ctr = 0x1B - 0x18;
    if (0x18 < 0x1B) {
        do {
            M2C_FIELD(var_r3, s32 *, 8) = 0xFF;
            var_r3 += 0x10;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    _vfLocal[0x6E] = 0xFF;
    _vfLocal[0x70] = 0xFF;
    var_r3_2 = &_vfLocal[0x30];
    _vfLocal[0x72] = 0xFF;
    _vfLocal[0x74] = 0xFF;
    _vfLocal[0x76] = 0xFF;
    _vfLocal[0x78] = 0xFF;
    _vfLocal[0x7A] = 0xFF;
    _vfLocal[0x7C] = 0xFF;
    _vfLocal[0x7E] = 0xFF;
    _vfLocal[0x80] = 0xFF;
    _vfLocal[0x82] = 0xFF;
    _vfLocal[0x84] = 0xFF;
    _vfLocal[0x86] = 0xFF;
    _vfLocal[0x88] = 0xFF;
    _vfLocal[0x8A] = 0xFF;
    _vfLocal[0x8C] = 0xFF;
    _vfLocal[0x8E] = 0xFF;
    _vfLocal[0x90] = 0xFF;
    _vfLocal[0x92] = 0xFF;
    _vfLocal[0x94] = 0xFF;
    _vfLocal[0x96] = 0xFF;
    _vfLocal[0x98] = 0xFF;
    _vfLocal[0x9A] = 0xFF;
    _vfLocal[0x9C] = 0xFF;
    var_ctr_2 = 0x1B - 0x18;
    if (0x18 < 0x1B) {
        do {
            M2C_FIELD(var_r3_2, s32 *, 0x1B8) = 0xFF;
            var_r3_2 += 8;
            var_ctr_2 -= 1;
        } while (var_ctr_2 != 0);
    }
    _vfLocal[0xA5] = 0xFF;
    _vfLocal[0xA9] = 0xFF;
    var_r3_3 = &_vfLocal[0x60];
    _vfLocal[0xAD] = 0xFF;
    _vfLocal[0xB1] = 0xFF;
    _vfLocal[0xB5] = 0xFF;
    _vfLocal[0xB9] = 0xFF;
    _vfLocal[0xBD] = 0xFF;
    _vfLocal[0xC1] = 0xFF;
    _vfLocal[0xC5] = 0xFF;
    _vfLocal[0xC9] = 0xFF;
    _vfLocal[0xCD] = 0xFF;
    _vfLocal[0xD1] = 0xFF;
    _vfLocal[0xD5] = 0xFF;
    _vfLocal[0xD9] = 0xFF;
    _vfLocal[0xDD] = 0xFF;
    _vfLocal[0xE1] = 0xFF;
    _vfLocal[0xE5] = 0xFF;
    _vfLocal[0xE9] = 0xFF;
    _vfLocal[0xED] = 0xFF;
    _vfLocal[0xF1] = 0xFF;
    _vfLocal[0xF5] = 0xFF;
    _vfLocal[0xF9] = 0xFF;
    _vfLocal[0xFD] = 0xFF;
    _vfLocal[0x101] = 0xFF;
    var_ctr_3 = 0x1B - 0x18;
    if (0x18 < 0x1B) {
        do {
            M2C_FIELD(var_r3_3, s32 *, 0x294) = 0xFF;
            var_r3_3 += 0x10;
            var_ctr_3 -= 1;
        } while (var_ctr_3 != 0);
    }
    M2C_FIELD(_vfLocal, s16 *, 0) = (s16) (M2C_FIELD(_vfLocal, s16 *, 0) | 6);
}
}


}
