#include <dolphin/types.h>
#pragma peephole off
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

extern "C" {
void flcalcBezier3(void *p0, void *p1, f32 p2);
s32 flcalcBlend(s32 p0, s32 p1, f32 p2);
s32 flcalcBlendColor(u32 from, u32 to, f32 t);
void flcalcConvFlashMatrix(void *p0, void *p1);
void flcalcCreateCxform(void *p0, u32 color);
void flcalcMatrix(void *p0, void *p1, void *p2);
void flcalcMatrixCopy(void *p0, void *p1);
void flcalcMatrixScale(void *p0, void *p1, void *p2);
void flcalcMatrixTranslate(void *p0, void *p1, void *p2);
void flcalcMulCxform(void *p0, void *p1, void *p2);
void flcalcMulMatrixf(void *p0, void *p1, void *p2);
s32 flcalcMultiTransformColor(void* ct, u32 color);
void flcalcUnitCxform(void *p0);
void flcalcUnitMatrix(void *p0);
void flcalcUnitMatrix2(void *p0);
}

struct FlMatrix {
    f32 a, b, c, d;
    f32 tx, ty;
};
struct FlPoint {
    f32 x, y;
};

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
void flcalcConvFlashMatrix(void* dst, void* src) {
    FlMatrix* out = (FlMatrix*)dst;
    s32* in = (s32*)src;
    f32 a = in[0] / 65536.0f;
    f32 b = in[1] / 65536.0f;
    f32 c = in[2] / 65536.0f;
    f32 d = in[3] / 65536.0f;
    f32 tx = in[4] / 20.0f;
    f32 ty = in[5] / 20.0f;
    out->a = a;
    out->b = b;
    out->c = c;
    out->d = d;
    out->tx = tx;
    out->ty = ty;
}
}

extern "C" {
s32 flcalcBlendColor(u32 from, u32 to, f32 t) {
    f32 a = from & 0xFF;
    f32 r = from >> 24;
    f32 g = (from >> 16) & 0xFF;
    f32 b = (from >> 8) & 0xFF;
    u32 rr = t * ((f32)(to >> 24) - r) + r;
    u32 ra = t * ((f32)(to & 0xFF) - a) + a;
    u32 rg = t * ((f32)((to >> 16) & 0xFF) - g) + g;
    u32 rb = t * ((f32)((to >> 8) & 0xFF) - b) + b;
    return ra | (rr << 24) | (rg << 16) | (rb << 8);
}
}

extern "C" {
s32 flcalcBlend(s32 p0, s32 p1, f32 p2) {
    return (s32) ((p2 * (f32) (p1 - p0)) + (f32) p0);
}
}

extern "C" {
struct FlCxform {
    s16 aMul, aAdd;
    s16 rMul, rAdd;
    s16 gMul, gAdd;
    s16 bMul, bAdd;
};

void flcalcCreateCxform(void* p0, u32 color) {
    FlCxform* cx = (FlCxform*)p0;
    cx->rMul = 0x100;
    cx->gMul = 0x100;
    cx->bMul = 0x100;
    cx->aMul = 0x100;
    cx->rAdd = 0;
    cx->gAdd = 0;
    cx->bAdd = 0;
    cx->aAdd = 0;
    cx->rMul = (s16)((color >> 24) & 0xFF);
    cx->gMul = (s16)((color >> 16) & 0xFF);
    cx->bMul = (s16)((color >> 8) & 0xFF);
    cx->aMul = (s16)(color & 0xFF);
}
}

extern "C" {
#define FLCALC_CLAMP(x) ((x) < 0xFF ? (x) : 0xFF)
s32 flcalcMultiTransformColor(void* ct, u32 color) {
    u32 cr = color >> 24;
    u32 cg = (color >> 16) & 0xFF;
    u32 cb = (color >> 8) & 0xFF;
    u32 ca = color & 0xFF;
    u32 r = FLCALC_CLAMP(((cr * M2C_FIELD(ct, s16 *, 4)) >> 8) + M2C_FIELD(ct, s16 *, 6));
    u32 g = FLCALC_CLAMP(((cg * M2C_FIELD(ct, s16 *, 8)) >> 8) + M2C_FIELD(ct, s16 *, 0xA));
    u32 b = FLCALC_CLAMP(((cb * M2C_FIELD(ct, s16 *, 0xC)) >> 8) + M2C_FIELD(ct, s16 *, 0xE));
    u32 a = FLCALC_CLAMP(((ca * M2C_FIELD(ct, s16 *, 0)) >> 8) + M2C_FIELD(ct, s16 *, 2));
    return a | (r << 24) | (g << 16) | (b << 8);
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
static inline void flcalcMulMatrixElems(FlMatrix* out, const FlMatrix* in, f32 a, f32 b, f32 c, f32 d, f32 tx, f32 ty) {
    out->a = in->a * a + in->b * c;
    out->b = in->a * b + in->b * d;
    out->c = in->c * a + in->d * c;
    out->d = in->c * b + in->d * d;
    out->tx = tx + (in->tx * a + in->ty * c);
    out->ty = ty + (in->tx * b + in->ty * d);
}

void flcalcMatrixTranslate(void* out, void* in, void* pos) {
    f32 x = ((FlPoint*)pos)->x;
    f32 y = ((FlPoint*)pos)->y;
    flcalcMulMatrixElems((FlMatrix*)out, (FlMatrix*)in, 1.0f, 0.0f, 0.0f, 1.0f, x, y);
}
}

extern "C" {
static inline void flcalcMulMatrix2x2(FlMatrix* out, const FlMatrix* in, f32 a, f32 b, f32 c, f32 d) {
    out->a = in->a * a + in->b * c;
    out->b = in->a * b + in->b * d;
    out->c = in->c * a + in->d * c;
    out->d = in->c * b + in->d * d;
    out->tx = in->tx;
    out->ty = in->ty;
}

void flcalcMatrixScale(void* out, void* in, void* scale) {
    f32 x = ((FlPoint*)scale)->x;
    f32 y = ((FlPoint*)scale)->y;
    flcalcMulMatrix2x2((FlMatrix*)out, (FlMatrix*)in, x, 0.0f, 0.0f, y);
}
}

extern "C" {

void flcalcMatrix(void* p0, void* p1, void* p2) {
    FlPoint* out = (FlPoint*)p0;
    FlMatrix* m = (FlMatrix*)p1;
    FlPoint p = *(FlPoint*)p2;
    f32 x = m->a * p.x + m->c * p.y;
    f32 y = m->b * p.x + m->d * p.y;
    out->x = x + m->tx;
    out->y = y + m->ty;
}
}
