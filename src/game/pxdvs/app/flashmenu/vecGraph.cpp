#ifndef __MWERKS__
#include <game/psq.h>
#endif
#include <dolphin/types.h>
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

#pragma pool_strings off
#pragma peephole off

extern "C" {
double sin(double);
double cos(double);
double acos(double);
extern u32 __float_nan[];
}

static inline int vgFPClassify(f32 x) {
    switch ((*(s32*)&x) & 0x7f800000) {
    case 0x7f800000:
        if ((*(s32*)&x) & 0x007fffff) return 1;
        else return 2;
    case 0:
        if ((*(s32*)&x) & 0x007fffff) return 5;
        else return 3;
    }
    return 4;
}

static inline f32 vgSqrtf(f32 x) {
    if (x > 0.0f) {
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x < 0.0) {
        return *(f32*)__float_nan;
    } else if (vgFPClassify(x) == 1) {
        return *(f32*)__float_nan;
    } else {
        return x;
    }
}
static inline f32 vgAcosf(f32 x) { return (f32)acos(x); }

extern "C" {
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
int printf(const char*, ...);
}

struct GSvec2 {
    f32 x, y;
};

static inline f32 __OSs16tof32(register const s16* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 5 }
#else
    ret = PSQ_LOAD(arg, 0, 5);
#endif
    return ret;
}

static inline f32 OSs16tof32(s16 v) {
    return __OSs16tof32(&v);
}

static inline void __OSf32tos16(register f32 arg, volatile register s16* out) {
#ifdef __MWERKS__
    asm { psq_st arg, 0(out), 1, 5 }
#else
    PSQ_STORE(out, 0, arg, 5);
#endif
}

static inline s16 OSf32tos16(f32 in) {
    s16 out;
    __OSf32tos16(in, &out);
    return out;
}
struct GStexture;
struct GSgfxLayer;

struct FLASHMATRIXF {
    f32 a, b, c, d, tx, ty;
};
#include <game/gcdata.h>
#include <game/gcptr.h>
struct FLASHMATRIX {
    gc_bes32 a, b, c, d, tx, ty;
};
struct FLASHCXFORM {
    gc_bes16 ra, rb, ga, gb, ba, bb, aa, ab;
};

struct _SHAPERECORD;
struct _FILLSTYLEARRAY {
    gc_be32 count;
    gc_ptr32(u8) list;
};
struct _LINESTYLEARRAY {
    gc_be32 count;
    gc_ptr32(u8) list;
};

struct SHAPEDATA {
    u8 flags;
    u8 pad01[3];
    gc_bes32 x;
    gc_bes32 y;
    u8 line;
    u8 fill;
    u8 lineWidth;
    u8 pad0F[5];
    gc_be32 newStyles;
};

struct _SHAPERECORD {
    u8 type;
    u8 pad1[3];
    gc_ptr32(void) data;
    gc_ptr32(_SHAPERECORD) next;
};
#ifdef __MWERKS__
typedef s32 vg_s32;
#define VG_VOLATILE volatile
#define VG_STYLES(sd) ((u8*)(sd)->newStyles)
#else
typedef gc_bes32 vg_s32;
#define VG_VOLATILE
#define VG_STYLES(sd) ((u8*)(uintptr_t)(u32)(sd)->newStyles)
#endif

struct VEC_RECT {
    s16 x0, y0, x1, y1;
    s16 dx2, dy2, dx, dy;
};

struct VEC_GRAPH_DATA {
    s32 on[2];
    s32 idx[2];
    s32 width[2];
    s16 minX, minY, maxX, maxY;
    s16 cx, cy, w, h;
    s32 color;
    GCsptr cxform;
    s32 color2;
    u32 numStyles;
    u8* styles;
    s32 f3C;
    u8* grad;
    s32 gx;
    s32 gy;
    f32 gScale;
    f32 gAngle;
    f32 sinA;
    f32 cosA;
    f32 sinB;
    f32 cosB;
    u32 palette[0x100];
    s16 cross[0x100][8];
};

struct LPOINT {
    s8 n;
    u8 pad;
    s16 x[33];
    VEC_GRAPH_DATA d;
};

extern "C" {
struct GSgfxLayer* GSgfxLayerFindByID(GCsint id);
int GSgfxLayerGetActive();
void GSprimDraw2DLineListC(void* verts, u32 count, void* colors);
struct SDCol4 {
    u8 c[4];
};
struct SDAdd4 {
    s16 v[4];
};
void GSprimDraw2DTexQuad4V(GSvec2* pos, GSvec2* uv, GStexture* tex, SDCol4 col);
#ifdef __MWERKS__
void GSprimDraw2DTexQuad4VCA(GSvec2* pos, GSvec2* uv, GStexture* tex, SDCol4 col, SDAdd4 add);
#define VG_ADD4(a) (a)
#else
void GSprimDraw2DTexQuad4VCA(GSvec2* pos, GSvec2* uv, GStexture* tex, SDCol4 col, SDAdd4* add);
#define VG_ADD4(a) (&(a))
#endif
void GSprimSetLineWidth(f32 w);
void GSprimSetQuadVertexOrder(s32 order);
void flcalcBezier3(GSvec2* out, GSvec2* pts, f32 t);
void flcalcMatrix(GSvec2* out, FLASHMATRIXF* m, GSvec2* in);
void flcalcMulMatrixf(FLASHMATRIXF* out, FLASHMATRIXF* a, FLASHMATRIXF* b);
s32 flcalcMultiTransformColor(GCsptr cx, s32 color);
GStexture* FlashSystemGetGStexture(u32 flashId, s32 texId);
}
void GSprimSetup2DRender(GSgfxLayer* layer);

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))
#ifdef __MWERKS__
#define VL(T, l, off, m) AT(T, l, off)
#else
enum GSgfxLayerID { GSgfxLayerID_vecGraph };
enum GSgfxLayerType { GSgfxLayerType_vecGraph };
#include <game/gsgfxlayer.h>
#define VL(T, l, off, m) (*(T*)&((GSgfxLayerData*)(l))->m)
#endif

static s32 bit_value[0x20] = {
    1,          2,          4,          8,          0x10,       0x20,       0x40,       0x80,
    0x100,      0x200,      0x400,      0x800,      0x1000,     0x2000,     0x4000,     0x8000,
    0x10000,    0x20000,    0x40000,    0x80000,    0x100000,   0x200000,   0x400000,   0x800000,
    0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000,
};
static VEC_GRAPH_DATA gVecDat;
static u32 scanline_buffer[0x1E0][0x50];
static VEC_RECT vecRect;
static LPOINT lPoint[4];
static u32 lList[0x601];
static s32 debugstep = 1;
static s32 _type = 1;
static s32 _src = 4;
static s32 _dst = 5;
static s32 _typemask = 1;
static s32 _srcmask = 4;
static s32 _dstmask = 5;

static void SBscan(void);
static void SBdec(u32 mask, s16 x, u32 n);
static void SBline(GSvec2* p0, GSvec2* p1);
static void calcVecRect(VEC_RECT* r, VEC_GRAPH_DATA* d, s32 i);
static void getCrossPoint(s32 a, short b, short c, short d, short e, short f, VEC_GRAPH_DATA* g);
static void gradientline(short x0, short x1, short y, VEC_GRAPH_DATA* d);
static void getUV(GSvec2* a, GSvec2* b, GSvec2* c, FLASHMATRIXF* m, FLASHMATRIXF* n, GStexture* t);
static void SpriteDisp(GStexture* tex, FLASHMATRIXF* mf, FLASHMATRIX* m, GSvec2* pts, VEC_GRAPH_DATA* d, FLASHCXFORM* cx);
static _SHAPERECORD* SpriteCode(u32, _SHAPERECORD* rec, u16 id, FLASHMATRIXF* mf, FLASHMATRIX* m, s32 x, s32 y, VEC_GRAPH_DATA* d, FLASHCXFORM* cx);

static inline void lListPush(u32 color, s16 x, s16 y) {
    if (lList[0] >= 0x200) {
        if (debugstep == 0x1229) {
            lList[0] = 0;
        } else {
            if (lList[0] != 0) GSprimDraw2DLineListC(&lList[0x201], lList[0] >> 1, &lList[1]);
            lList[0] = 0;
        }
    }
    memcpy(&lList[1 + lList[0]], &color, 4);
    f32* v = (f32*)&lList[0x201];
    v[lList[0] * 2] = __OSs16tof32(&x);
    v[lList[0] * 2 + 1] = __OSs16tof32(&y);
    lList[0] += 1;
}

static void SBscan(void) {
    s16 y;
    s16 x;
    if (gVecDat.numStyles > 4) {
        printf("ERROR:style count %d\n", gVecDat.numStyles);
        return;
    }
    if (debugstep != 0x174B) {
        if (debugstep == 0x77F) return;
        lList[0] = 0;
        GSprimSetLineWidth(1.0f);
        for (u32 i = 0; i < gVecDat.numStyles; i++) {
            calcVecRect(&vecRect, &gVecDat, i);
            lPoint[i].d = gVecDat;
        }
        u32* row = scanline_buffer[0];
        y = vecRect.y0;
        row = scanline_buffer[y];
        for (; y <= vecRect.y1; row += 0x50, y++) {
            lPoint[3].n = 0;
            lPoint[2].n = 0;
            lPoint[1].n = 0;
            lPoint[0].n = 0;
            x = (s16)(vecRect.x0 / 8);
            u32* p = row + x;
            for (; x <= vecRect.x1 / 8; p++, x++) {
                if (*p != 0) SBdec(*p, x, gVecDat.numStyles);
            }
            for (u32 i = 0; i < gVecDat.numStyles; i++) {
                LPOINT* lp = &lPoint[i];
                switch (lp->n % 2) {
                case 0:
                        s16* xs = lp->x;
                        for (int j = 0; j < lp->n; j += 2, xs += 2) {
                            s16 x1 = xs[1];
                            if (lp->d.grad != 0) {
                                gradientline(xs[0], x1, y, &lp->d);
                            } else {
                                lListPush(lp->d.color, xs[0], y);
                                lListPush(lp->d.color, x1, y);
                            }
                        }
                    break;
                }
            }
        }
        switch (debugstep) {
        case 0x1229:
                lList[0] = 0;
                return;
            break;
        }
        if (lList[0] != 0) GSprimDraw2DLineListC(&lList[0x201], lList[0] >> 1, &lList[1]);
        lList[0] = 0;
    }
}

static inline void plot(s16 x, s16 y) {
    s16 px = x;
    if (px < 0) px = 0;
    if (px >= 0x280) px = 0x27F;
    if (y >= 0 && y < 0x1E0) {
        u32* word = &scanline_buffer[y][px / 8];
        if (gVecDat.on[0] != 0) {
            u32 bit = bit_value[gVecDat.idx[0] + (px % 8) * 4];
            if ((*word & bit) != 0) *word = *word ^ bit;
            else *word = *word | bit;
        }
        if (gVecDat.on[1] != 0) {
            u32 bit = bit_value[gVecDat.idx[1] + (px % 8) * 4];
            if ((*word & bit) != 0) *word = *word ^ bit;
            else *word = *word | bit;
        }
        if (debugstep == 0) printf("x = %3d\t\ty = %3d\n", y);
    }
}

static inline void buildGradient(VEC_GRAPH_DATA* d) {
    s16 i = 0;
    s32 off = 0;
    for (; i < *d->grad; i++, off += 8) {
        s32 gx = d->gx;
        f32 v = (f32)(d->grad[off + 4] - 0x80);
        getCrossPoint(i, (s16)(gx + (s16)(v * d->gScale + 128.0f)), -0x100, 0x200, (s16)(gx + 0x80), 0x80, d);
    }
    u32 prev;
    memcpy(&prev, d->grad + 8, 4);
    s32 n = 0;
    off = 0;
    for (s32 k = 0; k < *d->grad; k++, off += 8) {
        s32 span = d->grad[off + 4] - n;
        if (span != 0) {
            for (s32 j = 0; j < span; j++) {
                u8* a = (u8*)&prev;
                u8* b = d->grad + off + 8;
                u8 r = (u8)(s32)(((((f32)b[1]) - (f32)a[1]) / (f32)span) * (f32)j + (f32)a[1]);
                u8 g = (u8)(s32)(((((f32)b[2]) - (f32)a[2]) / (f32)span) * (f32)j + (f32)a[2]);
                u8 bl = (u8)(s32)(((((f32)b[3]) - (f32)a[3]) / (f32)span) * (f32)j + (f32)a[3]);
                u8 al = (u8)(s32)(((((f32)b[0]) - (f32)a[0]) / (f32)span) * (f32)j + (f32)a[0]);
                d->palette[j + n] = flcalcMultiTransformColor(d->cxform, r | (g << 8) | (al << 24) | (bl << 16));
            }
        }
        memcpy(&prev, d->grad + off + 8, 4);
        n += span;
    }
    memcpy(&prev, &d->palette[n - 1], 4);
    for (; n < 0x100; n++) memcpy(&d->palette[n], &prev, 4);
}

extern "C++" {
static void SBdec(u32 mask, s16 x, u32 n) {
    if ((u8)mask != 0) {
        s16 base = x;
        base *= 8;
        for (u32 i = 0; i < n; i++) {
            if (mask & bit_value[i]) {
                lPoint[i].x[lPoint[i].n++] = base;
            }
            if (mask & bit_value[i + 4]) {
                lPoint[i].x[lPoint[i].n++] = (s16)(base + 1);
            }
        }
    }
    if ((mask & 0xFF00) != 0) {
        s16 base = x * 8;
        for (u32 i = 0; i < n; i++) {
            if (mask & bit_value[i + 8]) {
                lPoint[i].x[lPoint[i].n++] = (s16)(base + 2);
            }
            if (mask & bit_value[i + 12]) {
                lPoint[i].x[lPoint[i].n++] = (s16)(base + 3);
            }
        }
    }
    if ((mask & 0xFF0000) != 0) {
        s16 base = x * 8;
        for (u32 i = 0; i < n; i++) {
            if (mask & bit_value[i + 16]) {
                lPoint[i].x[lPoint[i].n++] = (s16)(base + 4);
            }
            if (mask & bit_value[i + 20]) {
                lPoint[i].x[lPoint[i].n++] = (s16)(base + 5);
            }
        }
    }
    if ((mask & 0xFF000000) != 0) {
        s16 base = x * 8;
        for (u32 i = 0; i < n; i++) {
            if (mask & bit_value[i + 24]) {
                lPoint[i].x[lPoint[i].n++] = (s16)(base + 6);
            }
            if (mask & bit_value[i + 28]) {
                lPoint[i].x[lPoint[i].n++] = (s16)(base + 7);
            }
        }
    }
}
}

static void SBline(GSvec2* p0, GSvec2* p1) {
    f32 y1;
    s16 last = -1;
    if (debugstep != 0x77F) {
        f32 y0 = p0->y;
        y1 = p1->y;
        if (y0 < y1) {
            vecRect.x0 = (s16)p0->x;
            vecRect.y0 = (s16)p0->y;
            vecRect.x1 = (s16)p1->x;
            vecRect.y1 = (s16)p1->y;
        } else if (y0 > y1) {
            vecRect.x0 = (s16)p1->x;
            vecRect.y0 = (s16)p1->y;
            vecRect.x1 = (s16)p0->x;
            vecRect.y1 = (s16)p0->y;
        } else {
            return;
        }
        vecRect.dy = vecRect.y1 - vecRect.y0;
        if (vecRect.dy != 0) {
            s16 step;
            if (vecRect.x1 > vecRect.x0) step = 1;
            else step = -1;
            s16 dx;
            if (vecRect.x1 > vecRect.x0) dx = vecRect.x1 - vecRect.x0;
            else dx = vecRect.x0 - vecRect.x1;
            vecRect.dx = dx;
            s16 x = vecRect.x0;
            vecRect.dx2 = dx * 2;
            s16 y = vecRect.y0;
            vecRect.dy2 = vecRect.dy * 2;
            if (dx == 0) {
                for (s16 i = 0; i < vecRect.dy; i++) {
                    s16 yy = y;
                    y++;
                    plot(x, yy);
                }
                return;
            }
            if (vecRect.dy < 2) {
                plot(x, y);
                return;
            }
            if (dx >= vecRect.dy) {
                s16 i;
                s16 err;
                for (i = 0, err = -dx; i <= vecRect.dx; i++) {
                    if (y == vecRect.y1) return;
                    if (last != y) {
                        plot(x, y);
                        last = y;
                    }
                    x += step;
                    err += vecRect.dy2;
                    if (err >= 0) {
                        y++;
                        err -= vecRect.dx2;
                    }
                }
                return;
            }
            s16 err = -vecRect.dy;
            for (s16 i = 0; i < vecRect.dy; i++) {
                plot(x, y);
                y++;
                err += vecRect.dx2;
                if (err >= 0) {
                    x += step;
                    err -= vecRect.dy2;
                }
            }
        }
    }
}

static void calcVecRect(VEC_RECT* r, VEC_GRAPH_DATA* d, s32 idx) {
    f32 len;
    u32 tmp = d->maxX + d->minX;
    d->cx = (s16)((s32)((tmp >> 31) + tmp) >> 1);
    tmp = d->maxY + d->minY;
    d->cy = (s16)((s32)((tmp >> 31) + tmp) >> 1);
    d->w = (s16)(d->maxX - d->minX);
    d->h = (s16)(d->maxY - d->minY);
    u8* styles = d->styles;
    if (styles != 0) {
        if (idx != 0) {
            u8* st = styles + (idx << 7);
            switch (st[0]) {
            case 0:
                d->color = flcalcMultiTransformColor(d->cxform, GC_AT(s32, st, 4));
                d->grad = 0;
                return;
            case 16:
                d->grad = st + 0x20;
                if (d->gScale == 0.0f) d->gScale = 1.0f;
                buildGradient(d);
                return;
            }
        } else {
            u8* st = styles + (idx << 7);
            f32 sy = (f32)GC_AT(s32, st, 0xC);
            s32 sx = GC_AT(s32, st, 8);
            d->gx = GC_AT(s32, st, 0x18) / 20 - d->cx;
            f32 fx = (f32)sx;
            len = fx * fx + sy * sy;
            d->gy = GC_AT(s32, d->styles + (idx << 7), 0x1C) / 20 - d->cy;
            if (len > 0.0f) len = vgSqrtf(len);
            d->gAngle = vgAcosf(fx / len);
            if (sy < 0.0f) d->gAngle = -d->gAngle;
            s16 hh = d->h;
            s32 hm = hh - 1;
            if (hm != 0) d->gScale = (1638.4f * (len / 65536.0f)) / (f32)hm;
            else d->gScale = 1638.4f * (len / 65536.0f);
            d->sinA = sin(d->gAngle);
            d->cosA = cos(d->gAngle);
            d->sinB = sin(-d->gAngle);
            d->cosB = cos(-d->gAngle);
            u8* st2 = d->styles + (idx << 7);
            switch (st2[0]) {
            case 0:
                d->color = flcalcMultiTransformColor(d->cxform, GC_AT(s32, st2, 4));
                d->grad = 0;
                break;
            case 16:
                d->grad = st2 + 0x20;
                if (d->gScale == 0.0f) d->gScale = 1.0f;
                buildGradient(d);
                break;
            }
            goto fin;
        }
    } else {
        d->gy = 0;
        d->gx = 0;
        d->gScale = 0.0f;
        d->gAngle = 0.0f;
        d->sinA = sin(d->gAngle);
        d->cosA = cos(d->gAngle);
        d->sinB = sin(-d->gAngle);
        d->cosB = cos(-d->gAngle);
    fin:
        s16 v = d->minY;
        if (v < 0) v = 0;
        r->y0 = v;
        v = d->maxY;
        if (v >= 0x1E0) v = 0x1DF;
        r->y1 = v;
        v = d->minX;
        if (v < 0) v = 0;
        r->x0 = v;
        v = d->maxX;
        if (v >= 0x280) v = 0x27F;
        r->x1 = v;
    }
}

static _SHAPERECORD* SpriteCode(u32 flashId, _SHAPERECORD* rec, u16 id, FLASHMATRIXF* mf, FLASHMATRIX* m, s32 x, s32 y, VEC_GRAPH_DATA* d, FLASHCXFORM* cx) {
    _SHAPERECORD* last = 0;
    u8 more = 1;
    GSvec2 pts[4];
    s32 n = 0;
    do {
        if (rec->type == 2) {
            vg_s32* data = (vg_s32*)rec->data;
            x += data[1];
            y += data[2];
            last = rec;
            rec = rec->next;
            pts[n].x = (f32)x / 20.0f;
            pts[n].y = (f32)y / 20.0f;
            n++;
        } else {
            more = 0;
        }
    } while (more != 0);
    GStexture* tex = FlashSystemGetGStexture(flashId, (u16)id);
    SpriteDisp(tex, mf, m, pts, d, cx);
    return last;
}

static void SpriteDisp(GStexture* tex, FLASHMATRIXF* mf, FLASHMATRIX* m, GSvec2* pts, VEC_GRAPH_DATA* d, FLASHCXFORM* cx) {
    FLASHMATRIXF mm;
    GSvec2 uv[4];
    GSvec2 pos[4];
    SDAdd4 add;
    SDCol4 col;
    if (tex != 0) {
        mm.a = (f32)m->a / 1310720.0f;
        mm.b = (f32)m->b / 1310720.0f;
        mm.c = (f32)m->c / 1310720.0f;
        mm.d = (f32)m->d / 1310720.0f;
        mm.tx = (f32)m->tx / 20.0f;
        mm.ty = (f32)m->ty / 20.0f;
        getUV(pos, uv, pts, mf, &mm, tex);
        s16 a1 = cx->rb;
        s16 a2 = cx->gb;
        s16 a3 = cx->bb;
        s16 a4 = cx->ab;
        u8 c3 = (u8)((cx->ra * 0xFF) >> 8);
        u8 c0 = (u8)((cx->ga * 0xFF) >> 8);
        u8 c1 = (u8)((cx->ba * 0xFF) >> 8);
        u8 c2 = (u8)((cx->aa * 0xFF) >> 8);
        add.v[3] = a1;
        col.c[3] = c3;
        col.c[0] = c0;
        col.c[1] = c1;
        col.c[2] = c2;
        add.v[0] = a2;
        add.v[1] = a3;
        add.v[2] = a4;
        if ((a4 | (a3 | (a1 | a2))) == 0) {
            GSprimDraw2DTexQuad4V(pos, uv, tex, col);
            return;
        }
        GSprimDraw2DTexQuad4VCA(pos, uv, tex, col, VG_ADD4(add));
    }
}

static void getUV(GSvec2* out, GSvec2* uv, GSvec2* pts, FLASHMATRIXF* mat, FLASHMATRIXF* mat2, GStexture* tex) {
    GSvec2 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    flcalcMatrix(uv, mat2, &zero);
    s32 bi = 0;
    f32 ux = uv->x;
    f32 uy = uv->y;
    f32 sx = vgSqrtf(mat2->a * mat2->a + mat2->b * mat2->b);
    f32 sy = vgSqrtf(mat2->c * mat2->c + mat2->d * mat2->d);
    f32 best = 1e9f;
    for (s32 i = 0; i < 4; i++) {
        f32 dx = pts[i].x - ux;
        f32 dy = pts[i].y - uy;
        f32 dist = vgSqrtf(dx * dx + dy * dy);
        if (dist < best) {
            bi = i;
            best = dist;
        }
    }
    GSvec2* o = out;
    GSvec2* u = uv;
    for (s32 i = 0; i < 4; i++, o++, u++) {
        GSvec2* p = &pts[(bi + i) & 3];
        o->x = p->x;
        o->y = p->y;
        u->x = (o->x - ux) / (f32)AT(u16, tex, 0);
        u->x /= sx;
        if (u->x < 0.0f) u->x = -u->x;
        if (u->x > 1.0f) u->x = 1.0f;
        u->y = (o->y - uy) / (f32)AT(u16, tex, 2);
        u->y = u->y / sy;
        if (u->y < 0.0f) u->y = -u->y;
        if (u->y > 1.0f) u->y = 1.0f;
        flcalcMatrix(o, mat, o);
    }
}

extern "C++" {
static inline u32 gradColor(VEC_GRAPH_DATA* d, s16 x, s16 y) {
    s32 gyv = d->gy + ((y - d->minY) << 8) / d->h;
    s32 gxv = ((x - d->minX) << 8) / d->w - d->gx;
    f32 fy = (f32)gyv - 128.0f;
    f32 fx = (f32)gxv - 128.0f;
    s16 idx = OSf32tos16(128.0f + (fx * d->cosB - fy * d->sinB) / d->gScale);
    if (idx < 0) idx = 0;
    if (idx >= 0x100) idx = 0xFF;
    return d->palette[idx % 256];
}

static void gradientline(short p0, short p1, short p2, VEC_GRAPH_DATA* p3) {
    s16 xs[10];
    s32 n = 0;
    s32 cnt = *p3->grad;
    for (s32 i = 0; i < cnt; i++) {
        s16 v = p3->minX + (p3->cross[((p2 - p3->minY) << 8) / p3->h][i] * p3->w) / 256;
        if (p0 < v && p1 > v) {
            xs[n++] = v;
        }
    }
    s16* a = xs;
    for (u16 i = 0; i < n - 1; i++, a++) {
        s16* b = &xs[i + 1];
        for (s32 j = i + 1; j < n; j++, b++) {
            if (*a > *b) {
                s16 t = *a;
                *a = *b;
                *b = t;
            }
        }
    }
    lListPush(gradColor(p3, p0, p2), p0, p2);
    for (s32 i = 0; i < n; i++) {
        u32 c = gradColor(p3, xs[i], p2);
        lListPush(c, xs[i], p2);
        lListPush(c, xs[i], p2);
    }
    lListPush(gradColor(p3, p1, p2), p1, p2);
}
}

extern "C++" {
static void getCrossPoint(s32 p0, short p1, short p2, short p3, short p4, short p5, VEC_GRAPH_DATA* p6) {
    s32 dy0 = p2 - p5;
    s32 dy1 = p3 - p5;
    s32 dx0 = p1 - p4;
    f32 cs = p6->cosA;
    s16 x0 = (s16)(cs * (f32)dx0 - p6->sinA * (f32)dy0);
    s16 x1 = (s16)(cs * (f32)dx0 - p6->sinA * (f32)dy1);
    vecRect.y0 = (s16)(p6->sinA * (f32)dx0 + cs * (f32)dy0);
    vecRect.y1 = (s16)(p6->sinA * (f32)dx0 + cs * (f32)dy1);
    vecRect.x0 = x0;
    vecRect.x1 = x1;
    s32 dx;
    if (x1 > x0) {
        dx = x1 - x0;
    } else {
        dx = x0 - x1;
    }
    vecRect.dx = dx;
    s32 dy;
    if (vecRect.y1 > vecRect.y0) {
        dy = vecRect.y1 - vecRect.y0;
    } else {
        dy = vecRect.y0 - vecRect.y1;
    }
    vecRect.dy = dy;
    if (vecRect.dx == 0 || dy == 0) {
        s16 v = vecRect.x0 + p4;
        for (s32 i = 0; i < 0x100; i++) {
            p6->cross[i][p0] = v;
        }
    } else {
        for (s32 i = 0; i < 0x100; i++) {
            s16 y = (p6->gy + i) - p5;
            s32 d;
            if (y > vecRect.y0) {
                d = y - vecRect.y0;
            } else {
                d = vecRect.y0 - y;
            }
            f32 t = (f32)d / (f32)vecRect.dy;
            s16 r;
            if (vecRect.x0 < vecRect.x1) {
                r = (s16)((f32)vecRect.dx * t + (f32)vecRect.x0);
                if (vecRect.x1 < r) r = vecRect.x1;
            } else {
                r = (s16)(-((f32)vecRect.dx * t - (f32)vecRect.x0));
                if (vecRect.x1 > r) r = vecRect.x1;
            }
            p6->cross[i][p0] = r + p4;
        }
    }
}
}

static void vecExec(u32 a0, _FILLSTYLEARRAY* fills, _LINESTYLEARRAY* lines, _SHAPERECORD* rec, FLASHMATRIXF* parent, FLASHMATRIXF* mat, FLASHCXFORM* cx) {
    GSvec2 bez;
    GSvec2 bezPrev;
    GSvec2 next;
    GSvec2 seg[7];
    GSvec2 cur;
    GSvec2 ctl;
    FLASHMATRIXF m;
    u8 inLine = 0;
    u32 loop = 1;
    switch (fills->count) {
    case 0:
            void* t = fills->list;
            if (t != 0) GC_AT(s32, t, 4) = -1;
        break;
    }
    s32 y = 0;
    s32 x = 0;
    if (parent != 0) {
        flcalcMulMatrixf(&m, mat, parent);
    } else {
        m = *mat;
    }
    do {
        switch (rec->type) {
        case 0:
            loop = 0;
            break;
        case 1: {
            VG_VOLATILE SHAPEDATA* sd = (SHAPEDATA*)rec->data;
            inLine = 0;
            if ((sd->flags & 1) != 0) {
                x = sd->x;
                y = sd->y;
                cur.x = (f32)x / 20.0f;
                cur.y = (f32)y / 20.0f;
                flcalcMatrix(&next, &m, &cur);
            }
            if ((sd->flags & 4) != 0) {
                if (sd->fill != 0) {
                    gVecDat.idx[1] = sd->fill - 1;
                    gVecDat.on[1] = 1;
                } else {
                    gVecDat.on[1] = 0;
                }
            }
            if ((sd->flags & 2) != 0) {
                if (sd->line != 0) {
                    gVecDat.idx[0] = sd->line - 1;
                    gVecDat.on[0] = 1;
                } else {
                    gVecDat.on[0] = 0;
                }
            }
            if ((sd->flags & 8) != 0) {
                if (gVecDat.on[0] != 0) {
                    gVecDat.width[0] = sd->lineWidth;
                    if (sd->lineWidth != 0 && (sd->flags & 6) == 0) inLine = 1;
                }
                if (gVecDat.on[1] != 0) {
                    gVecDat.width[1] = sd->lineWidth;
                    if (sd->lineWidth != 0 && (sd->flags & 6) == 0) inLine = 1;
                }
            }
            if ((sd->flags & 0x10) != 0 && sd->newStyles != 0) {
                SBscan();
                gVecDat.minY = 0x7FFF;
                gVecDat.minX = 0x7FFF;
                gVecDat.maxY = -0x8000;
                gVecDat.maxX = -0x8000;
                memset(scanline_buffer, 0, 0x25800);
                gVecDat.styles = VG_STYLES(sd);
                gVecDat.idx[1] = 0;
                gVecDat.idx[0] = 0;
                gVecDat.on[1] = 0;
                gVecDat.on[0] = 0;
                switch ((sd->flags & 4)) {
                case 0:
                        gVecDat.idx[1] = 0;
                        gVecDat.on[1] = 0;
                    break;
                }
                switch ((sd->flags & 2)) {
                case 0:
                        gVecDat.idx[0] = 0;
                        gVecDat.on[0] = 0;
                    break;
                }
            } else {
                for (s32 i = 0; i < 2; i++) {
                    if (gVecDat.on[i] != 0) {
                        s32 si = gVecDat.idx[i];
                        if ((gVecDat.styles[si << 7] & 0x40) != 0) {
                            switch ((sd->flags & 1)) {
                            case 0:
                                    y = 0;
                                    x = 0;
                                break;
                            }
                            u8* st = gVecDat.styles;
                            st += (si << 7);
                            rec = SpriteCode(a0, rec->next, (u16)GC_AT(u32, st, 0x64), mat, (FLASHMATRIX*)(st + 0x68), x, y, &gVecDat, cx);
                            inLine = 1;
                        }
                    }
                }
            }
            break;
        }
        case 2: {
            vg_s32* data = (vg_s32*)rec->data;
            x += data[1];
            y += data[2];
            cur.x = (f32)x / 20.0f;
            cur.y = (f32)y / 20.0f;
            switch (inLine) {
            case 0:
                    flcalcMatrix(&seg[0], &m, &cur);
                    SBline(&next, &seg[0]);
                    if ((s16)seg[0].x < gVecDat.minX) gVecDat.minX = (s16)seg[0].x;
                    if ((s16)seg[0].x > gVecDat.maxX) gVecDat.maxX = (s16)seg[0].x;
                    if ((s16)seg[0].y < gVecDat.minY) gVecDat.minY = (s16)seg[0].y;
                    if ((s16)seg[0].y > gVecDat.maxY) gVecDat.maxY = (s16)seg[0].y;
                    next = seg[0];
                break;
            }
            break;
        }
        case 3: {
            vg_s32* data = (vg_s32*)rec->data;
            s32 cx_ = x + data[0];
            s32 cy_ = y + data[1];
            cur.x = (f32)cx_ / 20.0f;
            cur.y = (f32)cy_ / 20.0f;
            flcalcMatrix(&ctl, &m, &cur);
            x = cx_ + data[2];
            y = cy_ + data[3];
            cur.x = (f32)x / 20.0f;
            cur.y = (f32)y / 20.0f;
            switch (inLine) {
            case 0:
                    flcalcMatrix(&seg[0], &m, &cur);
                    seg[3] = ctl;
                    f32 t = 0.0f;
                    if (next.y < seg[0].y) {
                        seg[1] = next;
                        seg[2] = seg[0];
                    } else {
                        seg[1] = seg[0];
                        seg[2] = next;
                    }
                    bezPrev = seg[1];
                    for (s32 i = 0; i < 9; i++) {
                        t += 0.1f;
                        flcalcBezier3(&bez, seg + 1, t);
                        SBline(&bezPrev, &bez);
                        bezPrev = bez;
                        if ((s16)bez.x < gVecDat.minX) gVecDat.minX = (s16)bez.x;
                        if ((s16)bez.x > gVecDat.maxX) gVecDat.maxX = (s16)bez.x;
                        if (bez.y < gVecDat.minY) gVecDat.minY = (s16)bez.y;
                        if ((s16)bez.y > gVecDat.maxY) gVecDat.maxY = (s16)bez.y;
                    }
                    bez = seg[2];
                    SBline(&bezPrev, &bez);
                    if ((s16)bez.x < gVecDat.minX) gVecDat.minX = (s16)bez.x;
                    if ((s16)bez.x > gVecDat.maxX) gVecDat.maxX = (s16)bez.x;
                    if ((s16)bez.y < gVecDat.minY) gVecDat.minY = (s16)bez.y;
                    if ((s16)bez.y > gVecDat.maxY) gVecDat.maxY = (s16)bez.y;
                    next = seg[0];
                break;
            }
            break;
        }
        default:
            printf("error flash record!\n");
            break;
        }
        rec = rec->next;
        if (rec->next == 0) loop = 0;
    } while (loop != 0);
    if (inLine == 0) SBscan();
}
static inline void vecLayerSetBlend(u8* l, s32 type, s32 src, s32 dst) {
    if (type == 0) {
        if (VL(s32, l, 0x1994, curPass) != 0) {
            VL(s32, l, 0x1994, curPass) = 0;
#ifdef __MWERKS__
            VL(u8*, l, 0x1990, curFifo) = l + VL(s32, l, 0x1994, curPass) * 0xBC + 0x1818;
#else
            VL(u8*, l, 0x1990, curFifo) = LAYER_CUR_PASS((GSgfxLayerData*)l);
#endif
        }
        VL(s32, l, 0x1644, hw.blend[0]) = 0;
        VL(s32, l, 0x1648, hw.blend[1]) = 1;
        VL(s32, l, 0x164C, hw.blend[2]) = 1;
        VL(s32, l, 0x1650, hw.blend[3]) = 5;
    } else {
        if (VL(s32, l, 0x1994, curPass) != 1) {
            VL(s32, l, 0x1994, curPass) = 1;
#ifdef __MWERKS__
            VL(u8*, l, 0x1990, curFifo) = l + VL(s32, l, 0x1994, curPass) * 0xBC + 0x1818;
#else
            VL(u8*, l, 0x1990, curFifo) = LAYER_CUR_PASS((GSgfxLayerData*)l);
#endif
        }
        VL(s32, l, 0x1644, hw.blend[0]) = type;
        VL(s32, l, 0x1648, hw.blend[1]) = src;
        VL(s32, l, 0x164C, hw.blend[2]) = dst;
        VL(s32, l, 0x1650, hw.blend[3]) = 5;
    }
    VL(s32, l, 0x170C, dirty[0].pe) |= 1;
    VL(s32, l, 0x16A8, dirty[0].groups) |= 0x40;
    VL(s32, l, 0x17C4, dirty[1].pe) |= 1;
    VL(s32, l, 0x1760, dirty[1].groups) |= 0x40;
}

extern "C" void vectorGraph(u32 a0, _FILLSTYLEARRAY* fills, _LINESTYLEARRAY* lines, _SHAPERECORD* rec, FLASHMATRIXF* parent, FLASHMATRIXF* mat, FLASHCXFORM* cx, u8 flags) {
    if (debugstep != 0x18) {
        GSprimSetup2DRender(0);
        u8* l = (u8*)GSgfxLayerFindByID(GSgfxLayerGetActive());
        VL(u8, l, 0x1674, hw.dither) = 1;
        VL(s32, l, 0x170C, dirty[0].pe) |= 0x20;
        VL(s32, l, 0x16A8, dirty[0].groups) |= 0x40;
        VL(s32, l, 0x17C4, dirty[1].pe) |= 0x20;
        VL(s32, l, 0x1760, dirty[1].groups) |= 0x40;
        if ((flags & 0x40) != 0) {
            vecLayerSetBlend(l, _typemask, _srcmask, _dstmask);
        } else {
            vecLayerSetBlend(l, _type, _src, _dst);
        }
        GSprimSetQuadVertexOrder(1);
        gVecDat.on[0] = 0;
        gVecDat.idx[0] = -1;
        gVecDat.width[0] = -1;
        gVecDat.on[1] = 0;
        gVecDat.idx[1] = -1;
        gVecDat.width[1] = -1;
        gVecDat.numStyles = fills->count;
        gVecDat.cxform = (GCsptr)cx;
        gVecDat.color2 = flcalcMultiTransformColor((GCsptr)cx, -1);
        gVecDat.styles = fills->list;
        gVecDat.f3C = GC_AT(s32, lines, 4);
        gVecDat.minY = 0x7FFF;
        gVecDat.minX = 0x7FFF;
        gVecDat.maxY = -0x8000;
        gVecDat.maxX = -0x8000;
        memset(scanline_buffer, 0, 0x25800);
        vecExec(a0, fills, lines, rec, parent, mat, cx);
    }
}

extern "C" void vectroGraphSetBlendMode(s32 src, s32 dst) {
    _src = src;
    _dst = dst;
}
