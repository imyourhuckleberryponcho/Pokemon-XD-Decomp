// Not yet decompiled.
#include <dolphin/types.h>
#pragma peephole off
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
enum ASM { ASM_draft_dummy };

extern "C" {
// ---- draft declarations ----


extern "C" {
void flcalcBezier3(void *p0, void *p1, f32 p2);
s32 flcalcBlend(s32 p0, s32 p1, f32 p2);
s32 flcalcBlendColor(u8 p0, u8 p1, f32 p2);
void flcalcConvFlashMatrix(void *p0, void *p1);
void flcalcCreateCxform(void *p0, u8 p1);
void flcalcMatrix(void *p0, void *p1, void *p2);
void flcalcMatrixCopy(void *p0, void *p1);
void flcalcMatrixScale(void *p0, void *p1, void *p2);
void flcalcMatrixTranslate(void *p0, void *p1, void *p2);
void flcalcMulCxform(void *p0, void *p1, void *p2);
void flcalcMulMatrixf(void *p0, void *p1, void *p2);
s32 flcalcMultiTransformColor(void *p0, u8 p1);
void flcalcUnitCxform(void *p0);
void flcalcUnitMatrix(void *p0);
void flcalcUnitMatrix2(void *p0);
}

void flcalcBezier3(void *p0, void *p1, f32 p2) {
    f32 temp_f5;
    f32 temp_f6;
    f32 temp_f7;

    temp_f7 = p2 * p2;
    temp_f5 = 1.0f - p2;
    temp_f6 = temp_f5 * temp_f5;
    M2C_FIELD(p0, f32 *, 0) = (f32) ((M2C_FIELD(p1, f32 *, 0x10) * temp_f7) + ((M2C_FIELD(p1, f32 *, 0) * temp_f6) + (p2 * (2.0f * M2C_FIELD(p1, f32 *, 8) * temp_f5))));
    M2C_FIELD(p0, f32 *, 4) = (f32) ((M2C_FIELD(p1, f32 *, 0x14) * temp_f7) + ((M2C_FIELD(p1, f32 *, 4) * temp_f6) + (p2 * (2.0f * M2C_FIELD(p1, f32 *, 0xC) * temp_f5))));
}
}

extern "C" {
void flcalcConvFlashMatrix(void *p0, void *p1) {
    M2C_FIELD(p0, f32 *, 0) = (f32) ((f32) M2C_FIELD(p1, s32 *, 0) / 65536.0f);
    M2C_FIELD(p0, f32 *, 4) = (f32) ((f32) M2C_FIELD(p1, s32 *, 4) / 65536.0f);
    M2C_FIELD(p0, f32 *, 8) = (f32) ((f32) M2C_FIELD(p1, s32 *, 8) / 65536.0f);
    M2C_FIELD(p0, f32 *, 0xC) = (f32) ((f32) M2C_FIELD(p1, s32 *, 0xC) / 65536.0f);
    M2C_FIELD(p0, f32 *, 0x10) = (f32) ((f32) M2C_FIELD(p1, s32 *, 0x10) / 20.0f);
    M2C_FIELD(p0, f32 *, 0x14) = (f32) ((f32) M2C_FIELD(p1, s32 *, 0x14) / 20.0f);
}
}

extern "C" {
s32 flcalcBlendColor(u8 p0, u8 p1, f32 p2) {
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f3;

    temp_f3 = (f32) (p0 >> 0x18U);
    temp_f30 = (f32) p0;
    temp_f29 = (f32) (u8) (p0 >> 0x10U);
    temp_f28 = (f32) (u8) (p0 >> 8U);
    return ((u32) ((p2 * ((f32) (u8) (p1 >> 8U) - temp_f28)) + temp_f28) << 8) | (((u32) ((p2 * ((f32) (u8) (p1 >> 0x10U) - temp_f29)) + temp_f29) << 0x10) | ((u32) ((p2 * ((f32) p1 - temp_f30)) + temp_f30) | ((u32) ((p2 * ((f32) (p1 >> 0x18U) - temp_f3)) + temp_f3) << 0x18)));
}
}

extern "C" {
s32 flcalcBlend(s32 p0, s32 p1, f32 p2) {
    return (s32) ((p2 * (f32) (p1 - p0)) + (f32) p0);
}
}

extern "C" {
void flcalcCreateCxform(void *p0, u8 p1) {
    M2C_FIELD(p0, s16 *, 4) = 0x100;
    M2C_FIELD(p0, s16 *, 8) = 0x100;
    M2C_FIELD(p0, s16 *, 0xC) = 0x100;
    M2C_FIELD(p0, s16 *, 0) = 0x100;
    M2C_FIELD(p0, s16 *, 6) = 0;
    M2C_FIELD(p0, s16 *, 0xA) = 0;
    M2C_FIELD(p0, s16 *, 0xE) = 0;
    M2C_FIELD(p0, s16 *, 2) = 0;
    M2C_FIELD(p0, s16 *, 4) = (s16) (p1 >> 0x18U);
    M2C_FIELD(p0, s16 *, 8) = (s16) (u8) (p1 >> 0x10U);
    M2C_FIELD(p0, s16 *, 0xC) = (s16) (u8) (p1 >> 8U);
    M2C_FIELD(p0, s16 *, 0) = (s16) p1;
}
}

extern "C" {
s32 flcalcMultiTransformColor(void *p0, u8 p1) {
    u32 var_r4;
    u32 var_r5;
    u32 var_r6;
    u32 var_r7;

    var_r5 = M2C_FIELD(p0, s16 *, 6) + ((u32) ((p1 >> 0x18U) * M2C_FIELD(p0, s16 *, 4)) >> 8U);
    if (var_r5 < 0xFFU) {

    } else {
        var_r5 = 0xFF;
    }
    var_r6 = M2C_FIELD(p0, s16 *, 0xA) + ((u32) ((u8) (p1 >> 0x10U) * M2C_FIELD(p0, s16 *, 8)) >> 8U);
    if (var_r6 < 0xFFU) {

    } else {
        var_r6 = 0xFF;
    }
    var_r4 = M2C_FIELD(p0, s16 *, 0xE) + ((u32) ((u8) (p1 >> 8U) * M2C_FIELD(p0, s16 *, 0xC)) >> 8U);
    if (var_r4 < 0xFFU) {

    } else {
        var_r4 = 0xFF;
    }
    var_r7 = M2C_FIELD(p0, s16 *, 2) + ((u32) (p1 * M2C_FIELD(p0, s16 *, 0)) >> 8U);
    if (var_r7 < 0xFFU) {

    } else {
        var_r7 = 0xFF;
    }
    return (var_r4 << 8) | ((var_r6 << 0x10) | (var_r7 | (var_r5 << 0x18)));
}
}

extern "C" {
void flcalcUnitCxform(void *p0) {
    M2C_FIELD(p0, s16 *, 4) = 0x100;
    M2C_FIELD(p0, s16 *, 8) = 0x100;
    M2C_FIELD(p0, s16 *, 0xC) = 0x100;
    M2C_FIELD(p0, s16 *, 0) = 0x100;
    M2C_FIELD(p0, s16 *, 6) = 0;
    M2C_FIELD(p0, s16 *, 0xA) = 0;
    M2C_FIELD(p0, s16 *, 0xE) = 0;
    M2C_FIELD(p0, s16 *, 2) = 0;
}
}

extern "C" {
void flcalcMulCxform(void *p0, void *p1, void *p2) {
    M2C_FIELD(p0, s16 *, 4) = (s16) ((s32) (M2C_FIELD(p1, s16 *, 4) * M2C_FIELD(p2, s16 *, 4)) / 256);
    M2C_FIELD(p0, s16 *, 8) = (s16) ((s32) (M2C_FIELD(p1, s16 *, 8) * M2C_FIELD(p2, s16 *, 8)) / 256);
    M2C_FIELD(p0, s16 *, 0xC) = (s16) ((s32) (M2C_FIELD(p1, s16 *, 0xC) * M2C_FIELD(p2, s16 *, 0xC)) / 256);
    M2C_FIELD(p0, s16 *, 0) = (s16) ((s32) (M2C_FIELD(p1, s16 *, 0) * M2C_FIELD(p2, s16 *, 0)) / 256);
    M2C_FIELD(p0, s16 *, 6) = (s16) (M2C_FIELD(p1, s16 *, 6) + M2C_FIELD(p2, s16 *, 6));
    M2C_FIELD(p0, s16 *, 0xA) = (s16) (M2C_FIELD(p1, s16 *, 0xA) + M2C_FIELD(p2, s16 *, 0xA));
    M2C_FIELD(p0, s16 *, 0xE) = (s16) (M2C_FIELD(p1, s16 *, 0xE) + M2C_FIELD(p2, s16 *, 0xE));
    M2C_FIELD(p0, s16 *, 2) = (s16) (M2C_FIELD(p1, s16 *, 2) + M2C_FIELD(p2, s16 *, 2));
}
}

extern "C" {
void flcalcMulMatrixf(void *p0, void *p1, void *p2) {
    M2C_FIELD(p0, f32 *, 0) = (f32) ((M2C_FIELD(p1, f32 *, 0) * M2C_FIELD(p2, f32 *, 0)) + (M2C_FIELD(p1, f32 *, 4) * M2C_FIELD(p2, f32 *, 8)));
    M2C_FIELD(p0, f32 *, 4) = (f32) ((M2C_FIELD(p1, f32 *, 0) * M2C_FIELD(p2, f32 *, 4)) + (M2C_FIELD(p1, f32 *, 4) * M2C_FIELD(p2, f32 *, 0xC)));
    M2C_FIELD(p0, f32 *, 8) = (f32) ((M2C_FIELD(p1, f32 *, 8) * M2C_FIELD(p2, f32 *, 0)) + (M2C_FIELD(p1, f32 *, 0xC) * M2C_FIELD(p2, f32 *, 8)));
    M2C_FIELD(p0, f32 *, 0xC) = (f32) ((M2C_FIELD(p1, f32 *, 8) * M2C_FIELD(p2, f32 *, 4)) + (M2C_FIELD(p1, f32 *, 0xC) * M2C_FIELD(p2, f32 *, 0xC)));
    M2C_FIELD(p0, f32 *, 0x10) = (f32) (M2C_FIELD(p2, f32 *, 0x10) + ((M2C_FIELD(p1, f32 *, 0x10) * M2C_FIELD(p2, f32 *, 0)) + (M2C_FIELD(p1, f32 *, 0x14) * M2C_FIELD(p2, f32 *, 8))));
    M2C_FIELD(p0, f32 *, 0x14) = (f32) (M2C_FIELD(p2, f32 *, 0x14) + ((M2C_FIELD(p1, f32 *, 0x10) * M2C_FIELD(p2, f32 *, 4)) + (M2C_FIELD(p1, f32 *, 0x14) * M2C_FIELD(p2, f32 *, 0xC))));
}
}

extern "C" {
void flcalcUnitMatrix2(void *p0) {
    M2C_FIELD(p0, s32 *, 0) = 0x10000;
    M2C_FIELD(p0, s32 *, 4) = 0;
    M2C_FIELD(p0, s32 *, 8) = 0;
    M2C_FIELD(p0, s32 *, 0xC) = 0x10000;
    M2C_FIELD(p0, s32 *, 0x10) = 0;
    M2C_FIELD(p0, s32 *, 0x14) = 0;
}
}

extern "C" {
void flcalcUnitMatrix(void *p0) {
    M2C_FIELD(p0, f32 *, 0) = 1.0f;
    M2C_FIELD(p0, f32 *, 4) = 0.0f;
    M2C_FIELD(p0, f32 *, 8) = 0.0f;
    M2C_FIELD(p0, f32 *, 0xC) = 1.0f;
    M2C_FIELD(p0, f32 *, 0x10) = 0.0f;
    M2C_FIELD(p0, f32 *, 0x14) = 0.0f;
}
}

extern "C" {
void flcalcMatrixCopy(void *p0, void *p1) {
    M2C_FIELD(p0, f32 *, 0) = (f32) M2C_FIELD(p1, f32 *, 0);
    M2C_FIELD(p0, f32 *, 4) = (f32) M2C_FIELD(p1, f32 *, 4);
    M2C_FIELD(p0, f32 *, 8) = (f32) M2C_FIELD(p1, f32 *, 8);
    M2C_FIELD(p0, f32 *, 0xC) = (f32) M2C_FIELD(p1, f32 *, 0xC);
    M2C_FIELD(p0, f32 *, 0x10) = (f32) M2C_FIELD(p1, f32 *, 0x10);
    M2C_FIELD(p0, f32 *, 0x14) = (f32) M2C_FIELD(p1, f32 *, 0x14);
}
}

extern "C" {
void flcalcMatrixTranslate(void *p0, void *p1, void *p2) {
    M2C_FIELD(p0, f32 *, 0) = (f32) ((M2C_FIELD(p1, f32 *, 0) * 1.0f) + (M2C_FIELD(p1, f32 *, 4) * 0.0f));
    M2C_FIELD(p0, f32 *, 4) = (f32) ((M2C_FIELD(p1, f32 *, 0) * 0.0f) + (M2C_FIELD(p1, f32 *, 4) * 1.0f));
    M2C_FIELD(p0, f32 *, 8) = (f32) ((M2C_FIELD(p1, f32 *, 8) * 1.0f) + (M2C_FIELD(p1, f32 *, 0xC) * 0.0f));
    M2C_FIELD(p0, f32 *, 0xC) = (f32) ((M2C_FIELD(p1, f32 *, 8) * 0.0f) + (M2C_FIELD(p1, f32 *, 0xC) * 1.0f));
    M2C_FIELD(p0, f32 *, 0x10) = (f32) (M2C_FIELD(p2, f32 *, 0) + ((M2C_FIELD(p1, f32 *, 0x10) * 1.0f) + (M2C_FIELD(p1, f32 *, 0x14) * 0.0f)));
    M2C_FIELD(p0, f32 *, 0x14) = (f32) (M2C_FIELD(p2, f32 *, 4) + ((M2C_FIELD(p1, f32 *, 0x10) * 0.0f) + (M2C_FIELD(p1, f32 *, 0x14) * 1.0f)));
}
}

extern "C" {
void flcalcMatrixScale(void *p0, void *p1, void *p2) {

    M2C_FIELD(p0, f32 *, 0) = (f32) ((M2C_FIELD(p1, f32 *, 0) * (M2C_FIELD(p2, f32 *, 0))) + (M2C_FIELD(p1, f32 *, 4) * 0.0f));
    M2C_FIELD(p0, f32 *, 4) = (f32) ((M2C_FIELD(p1, f32 *, 0) * 0.0f) + (M2C_FIELD(p1, f32 *, 4) * (M2C_FIELD(p2, f32 *, 4))));
    M2C_FIELD(p0, f32 *, 8) = (f32) ((M2C_FIELD(p1, f32 *, 8) * (M2C_FIELD(p2, f32 *, 0))) + (M2C_FIELD(p1, f32 *, 0xC) * 0.0f));
    M2C_FIELD(p0, f32 *, 0xC) = (f32) ((M2C_FIELD(p1, f32 *, 8) * 0.0f) + (M2C_FIELD(p1, f32 *, 0xC) * (M2C_FIELD(p2, f32 *, 4))));
    M2C_FIELD(p0, f32 *, 0x10) = (f32) M2C_FIELD(p1, f32 *, 0x10);
    M2C_FIELD(p0, f32 *, 0x14) = (f32) M2C_FIELD(p1, f32 *, 0x14);
}
}

extern "C" {
void flcalcMatrix(void *p0, void *p1, void *p2) {
    f32 spC;
    f32 sp8;

    spC = M2C_FIELD(p2, f32 *, 4);
    sp8 = M2C_FIELD(p2, f32 *, 0);
    M2C_FIELD(p0, f32 *, 0) = (f32) (M2C_FIELD(p1, f32 *, 0x10) + ((M2C_FIELD(p1, f32 *, 0) * sp8) + (M2C_FIELD(p1, f32 *, 8) * spC)));
    M2C_FIELD(p0, f32 *, 4) = (f32) (M2C_FIELD(p1, f32 *, 0x14) + ((M2C_FIELD(p1, f32 *, 4) * sp8) + (M2C_FIELD(p1, f32 *, 0xC) * spC)));
}
}
