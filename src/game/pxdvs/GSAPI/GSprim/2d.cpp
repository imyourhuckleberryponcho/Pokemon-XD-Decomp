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
enum GXColor { GXColor_draft_dummy };

extern "C" {
// ---- draft declarations ----
struct GSgfxLayer {
    u8 _draft[1];
    void setRenderStateAndSelect(GSgfxVF*);
    s32 beginSurface(unsigned short);
    s32 endSurface();
};
struct GSgfxVF {
    u8 _draft[1];
};

extern "C" {
GSgfxVF* GSgfxVFGetPredef(s32 id);
void GSprimDraw2DHLine(f32 *p0, f32 p1, f32 p2, f32 p3);
void GSprimDraw2DLine(f32 *p0, f32 *p1, f32 p2, f32 p3, f32 p4, f32 p5);
void GSprimDraw2DLineListC(void *p0, u32 p1, void *p2);
void GSprimDraw2DPixelListC(void *p0, u16 p1, s32 *p2);
void GSprimDraw2DQuadWH(f32 *p0, f32 p1, f32 p2, f32 p3, f32 p4);
void GSprimDraw2DTexQuad(void *p0, f32 *p1, f32 p2, f32 p3, f32 p4, f32 p5);
void GSprimDraw2DVLine(f32 *p0, f32 p1, f32 p2, f32 p3);
extern GSgfxLayer* primData;
extern s32 sp;
}

extern "C" {
extern "C" {

extern "C" {
// ---- draft declarations ----


extern "C" {
void GSprimDraw2DQuad(GXColor color, f32 x, f32 y, f32 w, f32 h);
void GSprimDraw2DQuad4V(void *p0, f32 *p1);
void GSprimDraw2DTexQuad4V(void *p0, void *p1, void *p2, f32 *p3);
void GSprimDraw2DTexQuad4VCA(void *p0, void *p1, void *p2, f32 *p3, void *p4);
}

// ---- draft declarations ----



void GSprimDraw2DTexQuad4VCA(void *p0, void *p1, void *p2, f32 *p3, void *p4) {
    f32 sp18;
    f32 sp1C;
    s32 unksp3A;
    s32 unksp3E;
    u32 sp3C;
    s32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    s32 var_r0;
    s16 var_r0_2;
    s16 var_r0_3;
    s16 var_r0_4;
    s16 var_r0_5;
    s16 var_r0_6;
    s16 var_r0_7;
    s16 var_r0_8;

    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(6)));
    if (((u8 *) M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x1740) != p2) || ((u8 *) M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x17F8) != p2) || ((u8) M2C_FIELD(p2, u8 *, 7) != 0)) {
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x1740) = (unsigned char *)(p2);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x173C) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x173C) | 1);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x17F8) = (unsigned char *)(p2);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x17F4) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x17F4) | 1);
    }
    sp38 = M2C_FIELD(p4, s32 *, 0);
    var_r0 = (s16) sp38;
    sp3C = M2C_FIELD(p4, s32 *, 4);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x13FC) = 1;
    if (var_r0 > -0x400) {

    } else {
        var_r0 = -0x400;
    }
    if (var_r0 < 0x3FF) {
        var_r0_2 = (s16) sp38;
        if (var_r0_2 > -0x400) {

        } else {
            var_r0_2 = -0x400;
        }
    } else {
        var_r0_2 = 0x3FF;
    }
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s16 *, 0x1400) = var_r0_2;
    var_r0_3 = -0x400;
    if (unksp3A > -0x400) {
        var_r0_3 = unksp3A;
    }
    if (var_r0_3 < 0x3FF) {
        var_r0_4 = -0x400;
        if (unksp3A > -0x400) {
            var_r0_4 = unksp3A;
        }
    } else {
        var_r0_4 = 0x3FF;
    }
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s16 *, 0x1402) = var_r0_4;
    var_r0_5 = -0x400;
    if (sp3C > -0x400) {
        var_r0_5 = (s16) sp3C;
    }
    if (var_r0_5 < 0x3FF) {
        var_r0_6 = -0x400;
        if ((s16) sp3C > -0x400) {
            var_r0_6 = (s16) sp3C;
        }
    } else {
        var_r0_6 = 0x3FF;
    }
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s16 *, 0x1404) = var_r0_6;
    var_r0_7 = -0x400;
    if (unksp3E > -0x400) {
        var_r0_7 = unksp3E;
    }
    if (var_r0_7 < 0x3FF) {
        var_r0_8 = -0x400;
        if (unksp3E > -0x400) {
            var_r0_8 = unksp3E;
        }
    } else {
        var_r0_8 = 0x3FF;
    }
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s16 *, 0x1406) = var_r0_8;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16E4) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16E4) | 2);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) | 8);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x179C) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x179C) | 2);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) | 8);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1170) = 0;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1174) = 0;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1178) = 0;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s8 *, 0x117C) = 1;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1180) = 0;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16DC) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16DC) | 1);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) | 8);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1794) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1794) | 1);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) | 8);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0xF70) = 0xF;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0xF74) = 0xA;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0xF78) = 8;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0xF7C) = 2;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16D4) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16D4) | 1);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) | 8);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x178C) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x178C) | 1);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) | 8);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x12B0) = 0;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x12B4) = 0;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x12B8) = 0;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s8 *, 0x12BC) = 1;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x12C0) = 0;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16E0) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16E0) | 1);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) | 8);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1798) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1798) | 1);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) | 8);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1070) = 7;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1074) = 5;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1078) = 4;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x107C) = 1;
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16D8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16D8) | 1);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) | 8);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1790) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1790) | 1);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) | 8);
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface(4U);
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = (s32) M2C_FIELD(&primData, s32 *, 0x14);
    sp30 = M2C_FIELD(p0, f32 *, 0);
    sp34 = M2C_FIELD(p0, f32 *, 4);
    *(f32 *)0xCC008000 = sp30;
    sp14 = (*p3);
    *(f32 *)0xCC008000 = sp34;
    *(f32 *)0xCC008000 = (*p3);
    sp10 = (*p3);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 4);
    sp28 = M2C_FIELD(p0, f32 *, 8);
    sp2C = M2C_FIELD(p0, f32 *, 0xC);
    *(f32 *)0xCC008000 = sp28;
    *(f32 *)0xCC008000 = sp2C;
    *(f32 *)0xCC008000 = (*p3);
    spC = (*p3);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 8);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0xC);
    sp20 = M2C_FIELD(p0, f32 *, 0x10);
    sp24 = M2C_FIELD(p0, f32 *, 0x14);
    *(f32 *)0xCC008000 = sp20;
    *(f32 *)0xCC008000 = sp24;
    *(f32 *)0xCC008000 = (*p3);
    sp8 = (*p3);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0x10);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0x14);
    M2C_STRUCT_COPY(sp - 0x60, p0, 8);
    *(f32 *)0xCC008000 = sp18;
    *(f32 *)0xCC008000 = sp1C;
    *(f32 *)0xCC008000 = (*p3);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0x18);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0x1C);
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
}
}

extern "C" {
void GSprimDraw2DTexQuad4V(void *p0, void *p1, void *p2, f32 *p3) {
    f32 sp18;
    f32 sp1C;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_r5;

    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(6)));
    if (((u8 *) M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x1740) != p2) || ((u8 *) M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x17F8) != p2) || ((u8) M2C_FIELD(p2, u8 *, 7) != 0)) {
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x1740) = (unsigned char *)(p2);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x173C) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x173C) | 1);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x17F8) = (unsigned char *)(p2);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x17F4) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x17F4) | 1);
    }
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = (s32) M2C_FIELD(&primData, s32 *, 0x14);
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface(4U);
    temp_r5 = *p3;
    sp30 = M2C_FIELD(p0, f32 *, 0);
    *(f32 *)0xCC008000 = sp30;
    sp34 = M2C_FIELD(p0, f32 *, 4);
    sp14 = temp_r5;
    *(f32 *)0xCC008000 = sp34;
    *(f32 *)0xCC008000 = temp_r5;
    sp10 = temp_r5;
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 4);
    sp28 = M2C_FIELD(p0, f32 *, 8);
    sp2C = M2C_FIELD(p0, f32 *, 0xC);
    *(f32 *)0xCC008000 = sp28;
    *(f32 *)0xCC008000 = sp2C;
    *(f32 *)0xCC008000 = temp_r5;
    spC = temp_r5;
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 8);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0xC);
    sp20 = M2C_FIELD(p0, f32 *, 0x10);
    sp24 = M2C_FIELD(p0, f32 *, 0x14);
    *(f32 *)0xCC008000 = sp20;
    *(f32 *)0xCC008000 = sp24;
    *(f32 *)0xCC008000 = temp_r5;
    sp8 = temp_r5;
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0x10);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0x14);
    M2C_STRUCT_COPY(sp - 0x50, p0, 8);
    *(f32 *)0xCC008000 = sp18;
    *(f32 *)0xCC008000 = sp1C;
    *(f32 *)0xCC008000 = temp_r5;
    *(f32 *)0xCC008000 = M2C_FIELD((u16)p1, f32 *, 0x18);
    *(f32 *)0xCC008000 = M2C_FIELD(p1, f32 *, 0x1C);
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
}
}
void GSprimDraw2DTexQuad(void *p0, f32 *p1, f32 p2, f32 p3, f32 p4, f32 p5) {
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_r0;

    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(6)));
    if (((u8 *) M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x1740) != p0) || ((u8 *) M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x17F8) != p0) || ((u8) M2C_FIELD(p0, u8 *, 7) != 0)) {
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x1740) = (unsigned char *)(p0);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x173C) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x173C) | 1);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), u8 **, 0x17F8) = (unsigned char *)(p0);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x17F4) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x17F4) | 1);
    }
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = (s32) M2C_FIELD(&primData, s32 *, 0x14);
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface(4U);
    temp_r0 = *p1;
    *(f32 *)0xCC008000 = p2;
    *(f32 *)0xCC008000 = p3;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = 0.0f;
    *(f32 *)0xCC008000 = 0.0f;
    *(f32 *)0xCC008000 = p4;
    *(f32 *)0xCC008000 = p3;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = 1.0f;
    *(f32 *)0xCC008000 = 0.0f;
    *(f32 *)0xCC008000 = p2;
    *(f32 *)0xCC008000 = p5;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = 0.0f;
    *(f32 *)0xCC008000 = 1.0f;
    *(f32 *)0xCC008000 = p4;
    *(f32 *)0xCC008000 = p5;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = 1.0f;
    *(f32 *)0xCC008000 = 1.0f;
    sp14 = temp_r0;
    sp10 = temp_r0;
    spC = temp_r0;
    sp8 = temp_r0;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
}
extern "C" {
void GSprimDraw2DQuad4V(void *p0, f32 *p1) {
    f32 sp18;
    f32 sp1C;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_r5;

    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(2)));
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = (s32) M2C_FIELD(&primData, s32 *, 0x14);
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface(4U);
    temp_r5 = *p1;
    sp30 = M2C_FIELD(p0, f32 *, 0);
    sp34 = M2C_FIELD(p0, f32 *, 4);
    *(f32 *)0xCC008000 = sp30;
    sp14 = temp_r5;
    *(f32 *)0xCC008000 = sp34;
    *(f32 *)0xCC008000 = temp_r5;
    sp28 = M2C_FIELD(p0, f32 *, 8);
    sp2C = M2C_FIELD(p0, f32 *, 0xC);
    *(f32 *)0xCC008000 = sp28;
    *(f32 *)0xCC008000 = sp2C;
    *(f32 *)0xCC008000 = temp_r5;
    sp20 = M2C_FIELD(p0, f32 *, 0x10);
    sp24 = M2C_FIELD(p0, f32 *, 0x14);
    *(f32 *)0xCC008000 = sp20;
    *(f32 *)0xCC008000 = sp24;
    *(f32 *)0xCC008000 = temp_r5;
    M2C_STRUCT_COPY(sp - 0x40, p0, 8);
    *(f32 *)0xCC008000 = sp18;
    *(f32 *)0xCC008000 = sp1C;
    *(f32 *)0xCC008000 = temp_r5;
    sp10 = temp_r5;
    spC = temp_r5;
    sp8 = temp_r5;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
}
}

}

extern "C" {
extern "C" {
void GSprimDraw2DQuadWH(f32 *p0, f32 p1, f32 p2, f32 p3, f32 p4) {
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_r0;

    temp_r0 = *p0;
    sp18 = temp_r0;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(2)));
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = (s32) M2C_FIELD(&primData, s32 *, 0x14);
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface(4U);
    *(f32 *)0xCC008000 = p1;
    temp_f0 = p1 + p3;
    *(f32 *)0xCC008000 = p2;
    temp_f1 = p2 + p4;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = temp_f0;
    *(f32 *)0xCC008000 = p2;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = p1;
    *(f32 *)0xCC008000 = temp_f1;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = temp_f0;
    *(f32 *)0xCC008000 = temp_f1;
    *(f32 *)0xCC008000 = temp_r0;
    sp8 = temp_r0;
    spC = temp_r0;
    sp10 = temp_r0;
    sp14 = temp_r0;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
}
extern "C" {
void GSprimDraw2DQuad(GXColor p0, f32 p1, f32 p2, f32 p3, f32 p4) {
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_r0;

    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(2)));
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = (s32) M2C_FIELD(&primData, s32 *, 0x14);
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface(4U);
    temp_r0 = *(s32 *)p0;
    *(f32 *)0xCC008000 = p1;
    *(f32 *)0xCC008000 = p2;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = p3;
    *(f32 *)0xCC008000 = p2;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = p1;
    *(f32 *)0xCC008000 = p4;
    *(f32 *)0xCC008000 = temp_r0;
    *(f32 *)0xCC008000 = p3;
    *(f32 *)0xCC008000 = p4;
    *(f32 *)0xCC008000 = temp_r0;
    sp14 = temp_r0;
    sp10 = temp_r0;
    spC = temp_r0;
    sp8 = temp_r0;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
}
}


}

extern "C" {
extern "C" {
void GSprimDraw2DPixelListC(void *p0, u16 p1, s32 *p2) {
    s32 temp_r0_2;
    s32 temp_r0_4;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 *var_r31;
    s32 temp_r0_3;
    s32 temp_r0_5;
    s32 var_ctr_2;
    int var_r3;
    u32 temp_r0;
    u32 var_ctr;
    u8 *var_r29;

    var_r31 = p2;
    var_r29 = (unsigned char *)(p0);
    if (p1 != 0) {
        M2C_FIELD(primData, s8 *, 0xD3C) = 6;
        M2C_FIELD(primData, s32 *, 0xD40) = 0;
        M2C_FIELD(primData, s32 *, 0x16AC) = (s32) (M2C_FIELD(primData, s32 *, 0x16AC) | 8);
        M2C_FIELD(primData, s32 *, 0x16A8) = (s32) (M2C_FIELD(primData, s32 *, 0x16A8) | 1);
        M2C_FIELD(primData, s32 *, 0x1764) = (s32) (M2C_FIELD(primData, s32 *, 0x1764) | 8);
        M2C_FIELD(primData, s32 *, 0x1760) = (s32) (M2C_FIELD(primData, s32 *, 0x1760) | 1);
        ((GSgfxLayer*)(primData))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(3)));
        M2C_FIELD(primData, s32 *, 0x1998) = 0xB8;
        ((GSgfxLayer*)(primData))->beginSurface(p1);
        var_r3 = p1;
        if (p1 != 0) {
            temp_r0 = p1 >> 2U;
            var_ctr = temp_r0;
            if (temp_r0 != 0) {
                do {
                    *(s16 *)0xCC008000 = M2C_FIELD(var_r29, s16 *, 0);
                    *(s16 *)0xCC008000 = M2C_FIELD(var_r29, s16 *, 2);
                    *(s16 *)0xCC008000 = (s32) M2C_FIELD(var_r31, s32 *, 0);
                    *(s16 *)0xCC008000 = M2C_FIELD(var_r29, s16 *, 4);
                    *(s16 *)0xCC008000 = M2C_FIELD(var_r29, s16 *, 6);
                    *(s16 *)0xCC008000 = (s32) M2C_FIELD(var_r31, s32 *, 4);
                    *(s16 *)0xCC008000 = M2C_FIELD(var_r29, s16 *, 8);
                    *(s16 *)0xCC008000 = M2C_FIELD(var_r29, s16 *, 0xA);
                    *(s16 *)0xCC008000 = (s32) M2C_FIELD(var_r31, s32 *, 8);
                    temp_r5 = M2C_FIELD(var_r29, s16 *, 0xE);
                    temp_r0_2 = M2C_FIELD(var_r29, s16 *, 0xC);
                    var_r29 += 0x10;
                    *(s16 *)0xCC008000 = temp_r0_2;
                    *(s16 *)0xCC008000 = temp_r5;
                    temp_r0_3 = M2C_FIELD(var_r31, s32 *, 0xC);
                    var_r31 += 0x10;
                    *(s16 *)0xCC008000 = temp_r0_3;
                    var_ctr -= 1;
                } while (var_ctr != 0);
                var_r3 &= 3;
                if (var_r3 != 0) {
                    goto block_5;
                }
            } else {
block_5:
                var_ctr_2 = var_r3;
                do {
                    temp_r5_2 = M2C_FIELD(var_r29, s16 *, 2);
                    temp_r0_4 = M2C_FIELD(var_r29, s16 *, 0);
                    var_r29 += 4;
                    *(s16 *)0xCC008000 = temp_r0_4;
                    *(s16 *)0xCC008000 = temp_r5_2;
                    temp_r0_5 = *var_r31;
                    var_r31 += 4;
                    *(s16 *)0xCC008000 = temp_r0_5;
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
            }
        }
        ((GSgfxLayer*)(primData))->endSurface();
    }
}
}

extern "C" {
void GSprimDraw2DLineListC(void *p0, u32 p1, void *p2) {
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_r0_2;
    f32 temp_r0_3;
    f32 temp_r0_4;
    f32 temp_r0_5;
    f32 temp_r0_6;
    f32 temp_r4;
    f32 temp_r4_2;
    f32 temp_r5;
    f32 temp_r5_2;
    f32 temp_r5_3;
    u32 temp_r0;
    u32 var_ctr;
    u32 var_ctr_2;
    u32 var_r3;
    u8 *var_r29;
    u8 *var_r31;

    var_r31 = (unsigned char *)(p2);
    var_r29 = (unsigned char *)(p0);
    if (p1 >= 1U) {
        if ((s32) M2C_FIELD(&primData, s32 *, 4) != 1) {
            M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s8 *, 0xD34) = (s8) (6.0f * M2C_FIELD(&primData, f32 *, 8));
            M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0xD38) = 0;
            M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16AC) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16AC) | 4);
            M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) | 1);
            M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1764) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1764) | 4);
            M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) | 1);
            M2C_FIELD(&primData, s32 *, 4) = 1;
        }
        ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(2)));
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = 0xA8;
        ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface((p1 * 2) & 0xFFFE);
        var_r3 = p1;
        if (p1 != 0) {
            temp_r0 = p1 >> 1U;
            var_ctr = temp_r0;
            if (temp_r0 != 0) {
                do {
                    sp18 = M2C_FIELD(var_r29, f32 *, 0);
                    sp1C = M2C_FIELD(var_r29, f32 *, 4);
                    *(f32 *)0xCC008000 = sp18;
                    *(f32 *)0xCC008000 = sp1C;
                    temp_r5 = M2C_FIELD(var_r31, f32 *, 0);
                    *(f32 *)0xCC008000 = temp_r5;
                    sp10 = M2C_FIELD(var_r29, f32 *, 8);
                    sp14 = M2C_FIELD(var_r29, f32 *, 0xC);
                    *(f32 *)0xCC008000 = sp10;
                    *(f32 *)0xCC008000 = sp14;
                    temp_r0_2 = M2C_FIELD(var_r31, f32 *, 4);
                    spC = temp_r5;
                    *(f32 *)0xCC008000 = temp_r0_2;
                    sp18 = M2C_FIELD(var_r29, f32 *, 0x10);
                    sp1C = M2C_FIELD(var_r29, f32 *, 0x14);
                    *(f32 *)0xCC008000 = sp18;
                    *(f32 *)0xCC008000 = sp1C;
                    temp_r5_2 = M2C_FIELD(var_r31, f32 *, 8);
                    sp8 = temp_r0_2;
                    *(f32 *)0xCC008000 = temp_r5_2;
                    temp_r4 = M2C_FIELD(var_r29, f32 *, 0x18);
                    temp_r0_3 = M2C_FIELD(var_r29, f32 *, 0x1C);
                    var_r29 += 0x20;
                    sp10 = temp_r4;
                    sp14 = temp_r0_3;
                    *(f32 *)0xCC008000 = sp10;
                    *(f32 *)0xCC008000 = sp14;
                    temp_r0_4 = M2C_FIELD(var_r31, f32 *, 0xC);
                    var_r31 += 0x10;
                    spC = temp_r5_2;
                    sp8 = temp_r0_4;
                    *(f32 *)0xCC008000 = temp_r0_4;
                    var_ctr -= 1;
                } while (var_ctr != 0);
                var_r3 &= 1;
                if (var_r3 != 0) {
                    goto block_7;
                }
            } else {
block_7:
                var_ctr_2 = var_r3;
                do {
                    sp18 = M2C_FIELD(var_r29, f32 *, 0);
                    sp1C = M2C_FIELD(var_r29, f32 *, 4);
                    *(f32 *)0xCC008000 = sp18;
                    *(f32 *)0xCC008000 = sp1C;
                    temp_r5_3 = M2C_FIELD(var_r31, f32 *, 0);
                    *(f32 *)0xCC008000 = temp_r5_3;
                    temp_r4_2 = M2C_FIELD(var_r29, f32 *, 8);
                    temp_r0_5 = M2C_FIELD(var_r29, f32 *, 0xC);
                    var_r29 += 0x10;
                    sp10 = temp_r4_2;
                    sp14 = temp_r0_5;
                    *(f32 *)0xCC008000 = sp10;
                    *(f32 *)0xCC008000 = sp14;
                    temp_r0_6 = M2C_FIELD(var_r31, f32 *, 4);
                    var_r31 += 8;
                    spC = temp_r5_3;
                    sp8 = temp_r0_6;
                    *(f32 *)0xCC008000 = temp_r0_6;
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
            }
        }
        ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
    }
}
}

extern "C" {
void GSprimDraw2DVLine(f32 *p0, f32 p1, f32 p2, f32 p3) {
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_r3;

    temp_r3 = *p0;
    sp8 = temp_r3;
    sp14 = temp_r3;
    if ((s32) M2C_FIELD(&primData, s32 *, 4) != 1) {
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s8 *, 0xD34) = (s8) (6.0f * M2C_FIELD(&primData, f32 *, 8));
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0xD38) = 0;
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16AC) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16AC) | 4);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) | 1);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1764) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1764) | 4);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) | 1);
        M2C_FIELD(&primData, s32 *, 4) = 1;
    }
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(2)));
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = 0xA8;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface(2U);
    *(f32 *)0xCC008000 = p1;
    *(f32 *)0xCC008000 = p2;
    *(f32 *)0xCC008000 = sp8;
    *(f32 *)0xCC008000 = p1;
    *(f32 *)0xCC008000 = p3;
    *(f32 *)0xCC008000 = sp14;
    spC = sp8;
    sp10 = sp14;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
}
}

extern "C" {
void GSprimDraw2DHLine(f32 *p0, f32 p1, f32 p2, f32 p3) {
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_r3;

    temp_r3 = *p0;
    sp8 = temp_r3;
    sp14 = temp_r3;
    if ((s32) M2C_FIELD(&primData, s32 *, 4) != 1) {
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s8 *, 0xD34) = (s8) (6.0f * M2C_FIELD(&primData, f32 *, 8));
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0xD38) = 0;
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16AC) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16AC) | 4);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) | 1);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1764) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1764) | 4);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) | 1);
        M2C_FIELD(&primData, s32 *, 4) = 1;
    }
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(2)));
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = 0xA8;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface(2U);
    *(f32 *)0xCC008000 = p1;
    *(f32 *)0xCC008000 = p3;
    *(f32 *)0xCC008000 = sp8;
    *(f32 *)0xCC008000 = p2;
    *(f32 *)0xCC008000 = p3;
    *(f32 *)0xCC008000 = sp14;
    spC = sp8;
    sp10 = sp14;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
}
}

extern "C" {
void GSprimDraw2DLine(f32 *p0, f32 *p1, f32 p2, f32 p3, f32 p4, f32 p5) {
    f32 spC;
    f32 sp8;
    f32 temp_r0;
    f32 temp_r4;

    if ((s32) M2C_FIELD(&primData, s32 *, 4) != 1) {
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s8 *, 0xD34) = (s8) (6.0f * M2C_FIELD(&primData, f32 *, 8));
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0xD38) = 0;
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16AC) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16AC) | 4);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x16A8) | 1);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1764) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1764) | 4);
        M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) = (s32) (M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1760) | 1);
        M2C_FIELD(&primData, s32 *, 4) = 1;
    }
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(2)));
    M2C_FIELD(M2C_FIELD(&primData, GSgfxLayer **, 0), s32 *, 0x1998) = 0xA8;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->beginSurface(2U);
    temp_r4 = *p0;
    *(f32 *)0xCC008000 = p2;
    temp_r0 = *p1;
    *(f32 *)0xCC008000 = p3;
    *(f32 *)0xCC008000 = temp_r4;
    *(f32 *)0xCC008000 = p4;
    *(f32 *)0xCC008000 = p5;
    *(f32 *)0xCC008000 = temp_r0;
    spC = temp_r4;
    sp8 = temp_r0;
    ((GSgfxLayer*)(M2C_FIELD(&primData, GSgfxLayer **, 0)))->endSurface();
}
}
}
}
}
}
