// STATUS (rough draft, rd_vecg): 12/12 functions, 1 exact, byte-weighted ~62%, default flags (+pool_strings off).
// Weakest: vecExec 36% (target frame 0x140 vs ours 0x180: fewer GSvec2 temporaries), gradientline 44%,
// SBscan 67% (target pushes line vertices via psq_l of an s16 pair -> f32 pair; we convert via ints),
// calcVecRect 69%, SBline 84%, getUV 89%. Flash struct types reconstructed from offsets only.
// LAYOUT: .sdata2 constants differ (psq_l scale constants missing), .data/.bss names OK.
#include <dolphin/types.h>
#pragma pool_strings off

extern "C" {
double sin(double);
double cos(double);
double acos(double);
extern unsigned long __float_nan[];
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
struct GStexture;
struct GSgfxLayer;

struct FLASHMATRIXF {
    f32 a, b, c, d, tx, ty;
};
struct FLASHMATRIX {
    s32 a, b, c, d, tx, ty;
};
struct FLASHCXFORM {
    s32 ra, rb, ga, gb, ba, bb, aa, ab;
};

struct _SHAPERECORD;
struct _FILLSTYLEARRAY {
    u32 count;
    u8* list;
};
struct _LINESTYLEARRAY {
    u32 count;
    u8* list;
};

struct SHAPEDATA {
    u8 flags;        // 0x00
    u8 pad01[3];
    s32 x;           // 0x04
    s32 y;           // 0x08
    u8 line;         // 0x0C
    u8 fill;         // 0x0D
    u8 lineWidth;    // 0x0E
    u8 pad0F[5];
    u32 newStyles;   // 0x14
};

struct _SHAPERECORD {
    u8 type;
    u8 pad1[3];
    void* data;
    _SHAPERECORD* next;
};

struct VEC_RECT {
    s16 x0, y0, x1, y1;
    s16 dx2, dy2, dx, dy;
};

struct VEC_GRAPH_DATA {
    s32 on[2];        // 0x00 fill / line enabled
    s32 idx[2];       // 0x08
    s32 width[2];     // 0x10
    s16 minX, minY, maxX, maxY; // 0x18
    s16 cx, cy, w, h; // 0x20
    s32 color;        // 0x28
    s32 cxform;       // 0x2C
    s32 color2;       // 0x30
    u32 numStyles;    // 0x34
    u8* styles;       // 0x38
    s32 f3C;          // 0x3C
    u8* grad;         // 0x40
    s32 gx;           // 0x44
    s32 gy;           // 0x48
    f32 gScale;       // 0x4C
    f32 gAngle;       // 0x50
    f32 sinA;         // 0x54
    f32 cosA;         // 0x58
    f32 sinB;         // 0x5C
    f32 cosB;         // 0x60
    u32 palette[0x100]; // 0x64
    s16 cross[0x800];   // 0x464
};

struct LPOINT {
    s8 n;
    u8 pad;
    s16 x[33];
    VEC_GRAPH_DATA d;
};

extern "C" {
int GSgfxLayerFindByID(int id);
int GSgfxLayerGetActive();
void GSprimDraw2DLineListC(void* verts, u32 count, void* colors);
void GSprimDraw2DTexQuad4V(GSvec2* pos, GSvec2* uv, GStexture* tex, void* col);
void GSprimDraw2DTexQuad4VCA(GSvec2* pos, GSvec2* uv, GStexture* tex, void* col, void* add, s32 addA);
void GSprimSetLineWidth(f32 w);
void GSprimSetQuadVertexOrder(s32 order);
void flcalcBezier3(GSvec2* out, GSvec2* pts, f32 t);
void flcalcMatrix(GSvec2* out, FLASHMATRIXF* m, GSvec2* in);
void flcalcMulMatrixf(FLASHMATRIXF* out, FLASHMATRIXF* a, FLASHMATRIXF* b);
s32 flcalcMultiTransformColor(s32 cx, s32 color, u8 a, u8 b);
GStexture* FlashSystemGetGStexture(u16 id);
}
void GSprimSetup2DRender(GSgfxLayer* layer);

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))

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
static void calcVecRect(VEC_RECT* r, VEC_GRAPH_DATA* d, long i);
static void getCrossPoint(long a, short b, short c, short d, short e, short f, VEC_GRAPH_DATA* g);
static void gradientline(short x0, short x1, short y, VEC_GRAPH_DATA* d);
static void getUV(GSvec2* a, GSvec2* b, GSvec2* c, FLASHMATRIXF* m, FLASHMATRIXF* n, GStexture* t);
static void SpriteDisp(GStexture* tex, FLASHMATRIXF* mf, FLASHMATRIX* m, GSvec2* pts, VEC_GRAPH_DATA* d, FLASHCXFORM* cx);
static _SHAPERECORD* SpriteCode(u32, _SHAPERECORD* rec, u16 id, FLASHMATRIXF* mf, FLASHMATRIX* m, long x, long y, VEC_GRAPH_DATA* d, FLASHCXFORM* cx);

// push one line vertex (color + x,y) into the batch list
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
    v[lList[0] * 2] = (f32)x;
    v[lList[0] * 2 + 1] = (f32)y;
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
        GSprimSetLineWidth(1.0f);
        lList[0] = 0;
        for (u32 i = 0; i < gVecDat.numStyles; i++) {
            calcVecRect(&vecRect, &gVecDat, i);
            lPoint[i].d = gVecDat;
        }
        u32* row = scanline_buffer[0];
        y = vecRect.y0;
        row = scanline_buffer[y];
        for (; y <= vecRect.y1; y++, row += 0x50) {
            lPoint[3].n = 0;
            lPoint[2].n = 0;
            lPoint[1].n = 0;
            lPoint[0].n = 0;
            x = (s16)(vecRect.x0 / 8);
            u32* p = row + x;
            for (; x <= vecRect.x1 / 8; x++, p++) {
                if (*p != 0) SBdec(*p, x, gVecDat.numStyles);
            }
            for (u32 i = 0; i < gVecDat.numStyles; i++) {
                LPOINT* lp = &lPoint[i];
                if (lp->n % 2 == 0) {
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
                }
            }
        }
        if (debugstep == 0x1229) {
            lList[0] = 0;
            return;
        }
        if (lList[0] != 0) GSprimDraw2DLineListC(&lList[0x201], lList[0] >> 1, &lList[1]);
        lList[0] = 0;
    }
}

static void SBdec(u32 mask, s16 x, u32 n) {
    for (int g = 0; g < 4; g++) {
        if ((mask & (0xFFu << (g * 8))) != 0) {
            s16 base = x * 8;
            LPOINT* lp = lPoint;
            s32* bv = bit_value;
            for (u32 i = 0; i < n; i++, bv++, lp++) {
                if ((mask & bv[g * 8]) != 0) {
                    s8 c = lp->n;
                    lp->n = c + 1;
                    lp->x[c] = (s16)(base + g * 2);
                }
                if ((mask & bv[g * 8 + 4]) != 0) {
                    s8 c = lp->n;
                    lp->n = c + 1;
                    lp->x[c] = (s16)(base + g * 2 + 1);
                }
            }
        }
    }
}

// toggle/set the coverage bit(s) of pixel (x, y) in the scanline buffer
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

static void SBline(GSvec2* p0, GSvec2* p1) {
    s16 last = -1;
    if (debugstep != 0x77F) {
        f32 y0 = p0->y;
        f32 y1 = p1->y;
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
                s16 err = -dx;
                for (s16 i = 0; i <= vecRect.dx; i++) {
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

// build the gradient palette between control points
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
                d->palette[j + n] = flcalcMultiTransformColor(d->cxform, r | (g << 8) | (al << 24) | (bl << 16), a[2], a[3]);
            }
        }
        memcpy(&prev, d->grad + off + 8, 4);
        n += span;
    }
    memcpy(&prev, &d->palette[n - 1], 4);
    for (; n < 0x100; n++) memcpy(&d->palette[n], &prev, 4);
}

static void calcVecRect(VEC_RECT* r, VEC_GRAPH_DATA* d, long idx) {
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
                d->color = flcalcMultiTransformColor(d->cxform, AT(s32, st, 4), 0, 0);
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
            s32 sx = AT(s32, st, 8);
            f32 sy = (f32)AT(s32, st, 0xC);
            d->gx = AT(s32, st, 0x18) / 20 - d->cx;
            f32 fx = (f32)sx;
            f32 len = fx * fx + sy * sy;
            d->gy = AT(s32, d->styles + (idx << 7), 0x1C) / 20 - d->cy;
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
                d->color = flcalcMultiTransformColor(d->cxform, AT(s32, st2, 4), 0, 0);
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

static _SHAPERECORD* SpriteCode(u32, _SHAPERECORD* rec, u16 id, FLASHMATRIXF* mf, FLASHMATRIX* m, long x, long y, VEC_GRAPH_DATA* d, FLASHCXFORM* cx) {
    GSvec2 pts[4];
    u8 more = 1;
    _SHAPERECORD* last = 0;
    s32 n = 0;
    do {
        if (rec->type == 2) {
            s32* data = (s32*)rec->data;
            x += data[1];
            y += data[2];
            last = rec;
            pts[n].x = (f32)x / 20.0f;
            pts[n].y = (f32)y / 20.0f;
            n++;
            rec = rec->next;
        } else {
            more = 0;
        }
    } while (more != 0);
    GStexture* tex = FlashSystemGetGStexture(id);
    SpriteDisp(tex, mf, m, pts, d, cx);
    return last;
}

static void SpriteDisp(GStexture* tex, FLASHMATRIXF* mf, FLASHMATRIX* m, GSvec2* pts, VEC_GRAPH_DATA* d, FLASHCXFORM* cx) {
    GSvec2 pos[4];
    GSvec2 uv[4];
    FLASHMATRIXF mm;
    s16 add[4];
    u8 col[4];
    if (tex != 0) {
        mm.a = (f32)m->a / 1310720.0f;
        mm.b = (f32)m->b / 1310720.0f;
        mm.c = (f32)m->c / 1310720.0f;
        mm.d = (f32)m->d / 1310720.0f;
        mm.tx = (f32)m->tx / 20.0f;
        mm.ty = (f32)m->ty / 20.0f;
        getUV(pos, uv, pts, mf, &mm, tex);
        s16 a1 = (s16)cx->rb;
        s16 a2 = (s16)cx->gb;
        s16 a3 = (s16)cx->bb;
        s16 a4 = (s16)cx->ab;
        col[3] = (u8)((cx->ra * 0xFF) >> 8);
        col[0] = (u8)((cx->ga * 0xFF) >> 8);
        col[1] = (u8)((cx->ba * 0xFF) >> 8);
        col[2] = (u8)((cx->aa * 0xFF) >> 8);
        add[0] = a1;
        add[1] = a2;
        add[2] = a3;
        add[3] = a4;
        if ((a4 | (a3 | (a1 | a2))) == 0) {
            s32 c = *(s32*)col;
            GSprimDraw2DTexQuad4V(pos, uv, tex, &c);
            return;
        }
        s32 c = *(s32*)col;
        GSprimDraw2DTexQuad4VCA(pos, uv, tex, &c, add, a4);
    }
}

// pick the quad corner that is closest to the origin, then compute normalized UVs
static void getUV(GSvec2* out, GSvec2* uv, GSvec2* pts, FLASHMATRIXF* mat, FLASHMATRIXF* mat2, GStexture* tex) {
    GSvec2 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    flcalcMatrix(uv, mat2, &zero);
    f32 ux = uv->x;
    f32 uy = uv->y;
    f32 sx = vgSqrtf(mat2->a * mat2->a + mat2->b * mat2->b);
    f32 sy = vgSqrtf(mat2->c * mat2->c + mat2->d * mat2->d);
    f32 best = 1e9f;
    s32 bi = 0;
    for (s32 i = 0; i < 4; i++) {
        f32 dy = pts[i].y - uy;
        f32 dx = pts[i].x - ux;
        f32 dist = vgSqrtf(dx * dx + dy * dy);
        if (best > dist) {
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

static void gradientline(short x0, short x1, short y, VEC_GRAPH_DATA* d) {
    s16 xs[4];
    s32 n = 0;
    s32 off = 0;
    u8 cnt = *d->grad;
    if ((s32)cnt > 0) {
        do {
            s16 v = d->minX + ((s32)(d->cross[((((y - d->minY) << 8) / d->h) * 8) + off / 2]) * d->w) / 256;
            if (x0 < v && x1 > v) {
                xs[n] = v;
                n++;
            }
            off += 2;
            cnt--;
        } while (cnt != 0);
    }
    for (s32 i = 0; i < n - 1; i++) {
        for (s32 j = i + 1; j < n; j++) {
            if (xs[i] > xs[j]) {
                s16 t = xs[i];
                xs[i] = xs[j];
                xs[j] = t;
            }
        }
    }
    s16 a = x0;
    if (a < 0) a = 0;
    if (a >= 0x100) a = 0xFF;
    lListPush(d->palette[a & 0xFF], x0, y);
    for (s32 i = 0; i < n; i++) {
        s16 c = xs[i];
        if (c < 0) c = 0;
        if (c >= 0x100) c = 0xFF;
        u32 col = d->palette[c & 0xFF];
        lListPush(col, xs[i], y);
        lListPush(col, xs[i], y);
    }
    s16 b = x1;
    if (b < 0) b = 0;
    if (b >= 0x100) b = 0xFF;
    lListPush(d->palette[b & 0xFF], x1, y);
}

static void getCrossPoint(long idx, short ya, short yb, short yc, short x0, short y0, VEC_GRAPH_DATA* d) {
    s32 dy0 = yb - y0;
    s32 dy1 = yc - y0;
    s32 dx = ya - x0;
    f32 s = d->sinA;
    f32 c = d->cosA;
    s16 rx0 = (s16)(c * (f32)dx - s * (f32)dy0);
    s16 rx1 = (s16)(c * (f32)dx - s * (f32)dy1);
    vecRect.x0 = rx0;
    vecRect.y0 = (s16)(s * (f32)dx + c * (f32)dy0);
    vecRect.x1 = rx1;
    vecRect.y1 = (s16)(s * (f32)dx + c * (f32)dy1);
    s16 adx;
    if (rx1 > rx0) adx = rx1 - rx0;
    else adx = rx0 - rx1;
    vecRect.dx = adx;
    s16 ady;
    if (vecRect.y1 > vecRect.y0) ady = vecRect.y1 - vecRect.y0;
    else ady = vecRect.y0 - vecRect.y1;
    vecRect.dy = ady;
    if (vecRect.dx == 0 || ady == 0) {
        s16 v = vecRect.x0 + x0;
        for (s32 i = 0; i < 0x100; i++) d->cross[idx * 2 + i * 8] = v;
    } else {
        for (s32 i = 0; i < 0x100; i++) {
            s16 yy = (i + d->gy) - y0;
            s16 ddy;
            if (yy > vecRect.y0) ddy = yy - vecRect.y0;
            else ddy = vecRect.y0 - yy;
            f32 t = (f32)ddy / (f32)vecRect.dy;
            s16 vx;
            if (vecRect.x0 < vecRect.x1) {
                f32 fx = ((f32)vecRect.dx * t) + (f32)vecRect.x0;
                vx = (s16)fx;
                if (vecRect.x1 < (s16)fx) vx = vecRect.x1;
            } else {
                f32 fx = -(((f32)vecRect.dx * t) - (f32)vecRect.x0);
                vx = (s16)fx;
                if (vecRect.x1 > (s16)fx) vx = vecRect.x1;
            }
            d->cross[idx * 2 + i * 8] = (s16)(vx + x0);
        }
    }
}

static void vecExec(u32 a0, _FILLSTYLEARRAY* fills, _LINESTYLEARRAY* lines, _SHAPERECORD* rec, FLASHMATRIXF* parent, FLASHMATRIXF* mat, FLASHCXFORM* cx) {
    GSvec2 cur;
    GSvec2 next;
    GSvec2 ctl;
    GSvec2 seg[4];
    GSvec2 bez;
    GSvec2 bezPrev;
    FLASHMATRIXF m;
    u8 inLine = 0;
    u8 loop = 1;
    if (fills->count == 0) {
        void* t = fills->list;
        if (t != 0) AT(s32, t, 4) = -1;
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
            SHAPEDATA* sd = (SHAPEDATA*)rec->data;
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
                gVecDat.styles = (u8*)sd->newStyles;
                gVecDat.idx[1] = 0;
                gVecDat.idx[0] = 0;
                gVecDat.on[1] = 0;
                gVecDat.on[0] = 0;
                if ((sd->flags & 4) == 0) {
                    gVecDat.idx[1] = 0;
                    gVecDat.on[1] = 0;
                }
                if ((sd->flags & 2) == 0) {
                    gVecDat.idx[0] = 0;
                    gVecDat.on[0] = 0;
                }
            } else {
                for (s32 i = 0; i < 2; i++) {
                    if (gVecDat.on[i] != 0) {
                        s32 si = gVecDat.idx[i];
                        if ((gVecDat.styles[si << 7] & 0x40) != 0) {
                            if ((sd->flags & 1) == 0) {
                                y = 0;
                                x = 0;
                            }
                            u8* st = gVecDat.styles + (si << 7);
                            inLine = 1;
                            rec = SpriteCode(a0, rec, (u16)((u16*)rec)[4], mat, (FLASHMATRIX*)(st + 0x68), x, y, &gVecDat, cx);
                        }
                    }
                }
            }
            break;
        }
        case 2: {
            s32* data = (s32*)rec->data;
            x += data[1];
            y += data[2];
            cur.x = (f32)x / 20.0f;
            cur.y = (f32)y / 20.0f;
            if (inLine == 0) {
                flcalcMatrix(&seg[0], &m, &cur);
                SBline(&next, &seg[0]);
                if ((s16)seg[0].x < gVecDat.minX) gVecDat.minX = (s16)seg[0].x;
                if ((s16)seg[0].x > gVecDat.maxX) gVecDat.maxX = (s16)seg[0].x;
                if ((s16)seg[0].y < gVecDat.minY) gVecDat.minY = (s16)seg[0].y;
                if ((s16)seg[0].y > gVecDat.maxY) gVecDat.maxY = (s16)seg[0].y;
                next = seg[0];
            }
            break;
        }
        case 3: {
            s32* data = (s32*)rec->data;
            s32 cx_ = x + data[0];
            s32 cy_ = y + data[1];
            cur.x = (f32)cx_ / 20.0f;
            cur.y = (f32)cy_ / 20.0f;
            flcalcMatrix(&ctl, &m, &cur);
            x = cx_ + data[2];
            y = cy_ + data[3];
            cur.x = (f32)x / 20.0f;
            cur.y = (f32)y / 20.0f;
            if (inLine == 0) {
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
                    if ((s16)bez.y < gVecDat.minY) gVecDat.minY = (s16)bez.y;
                    if ((s16)bez.y > gVecDat.maxY) gVecDat.maxY = (s16)bez.y;
                }
                bez = seg[2];
                SBline(&bezPrev, &bez);
                if ((s16)bez.x < gVecDat.minX) gVecDat.minX = (s16)bez.x;
                if ((s16)bez.x > gVecDat.maxX) gVecDat.maxX = (s16)bez.x;
                if ((s16)bez.y < gVecDat.minY) gVecDat.minY = (s16)bez.y;
                if ((s16)bez.y > gVecDat.maxY) gVecDat.maxY = (s16)bez.y;
                next = seg[0];
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

extern "C" void vectorGraph(u32 a0, _FILLSTYLEARRAY* fills, _LINESTYLEARRAY* lines, _SHAPERECORD* rec, FLASHMATRIXF* parent, FLASHMATRIXF* mat, FLASHCXFORM* cx, u8 flags) {
    if (debugstep != 0x18) {
        GSprimSetup2DRender(0);
        GSgfxLayerGetActive();
        u8* l = (u8*)GSgfxLayerFindByID(0);
        AT(s32, l, 0x1674) = 1;
        AT(s32, l, 0x170C) |= 0x20;
        AT(s32, l, 0x16A8) |= 0x40;
        AT(s32, l, 0x17C4) |= 0x20;
        AT(s32, l, 0x1760) |= 0x40;
        if ((flags & 0x40) != 0) {
            if (_typemask == 0) {
                if (AT(s32, l, 0x1994) != 0) {
                    AT(s32, l, 0x1994) = 0;
                    AT(u8*, l, 0x1990) = l + AT(s32, l, 0x1994) * 0xBC + 0x1818;
                }
                AT(s32, l, 0x1644) = 0;
                AT(s32, l, 0x1648) = 1;
                AT(s32, l, 0x164C) = 1;
                AT(s32, l, 0x1650) = 5;
            } else {
                if (AT(s32, l, 0x1994) != 1) {
                    AT(s32, l, 0x1994) = 1;
                    AT(u8*, l, 0x1990) = l + AT(s32, l, 0x1994) * 0xBC + 0x1818;
                }
                AT(s32, l, 0x1644) = _typemask;
                AT(s32, l, 0x1648) = _srcmask;
                AT(s32, l, 0x164C) = _dstmask;
                AT(s32, l, 0x1650) = 5;
            }
            AT(s32, l, 0x170C) |= 1;
            AT(s32, l, 0x16A8) |= 0x40;
            AT(s32, l, 0x17C4) |= 1;
            AT(s32, l, 0x1760) |= 0x40;
        } else {
            if (_type == 0) {
                if (AT(s32, l, 0x1994) != 0) {
                    AT(s32, l, 0x1994) = 0;
                    AT(u8*, l, 0x1990) = l + AT(s32, l, 0x1994) * 0xBC + 0x1818;
                }
                AT(s32, l, 0x1644) = 0;
                AT(s32, l, 0x1648) = 1;
                AT(s32, l, 0x164C) = 1;
                AT(s32, l, 0x1650) = 5;
            } else {
                if (AT(s32, l, 0x1994) != 1) {
                    AT(s32, l, 0x1994) = 1;
                    AT(u8*, l, 0x1990) = l + AT(s32, l, 0x1994) * 0xBC + 0x1818;
                }
                AT(s32, l, 0x1644) = _type;
                AT(s32, l, 0x1648) = _src;
                AT(s32, l, 0x164C) = _dst;
                AT(s32, l, 0x1650) = 5;
            }
            AT(s32, l, 0x170C) |= 1;
            AT(s32, l, 0x16A8) |= 0x40;
            AT(s32, l, 0x17C4) |= 1;
            AT(s32, l, 0x1760) |= 0x40;
        }
        GSprimSetQuadVertexOrder(1);
        gVecDat.on[0] = 0;
        gVecDat.idx[0] = -1;
        gVecDat.width[0] = -1;
        gVecDat.on[1] = 0;
        gVecDat.idx[1] = -1;
        gVecDat.width[1] = -1;
        gVecDat.numStyles = fills->count;
        gVecDat.cxform = (s32)cx;
        gVecDat.color2 = flcalcMultiTransformColor((s32)cx, -1, (u8)(u32)&gVecDat, 0);
        gVecDat.styles = fills->list;
        gVecDat.f3C = ((s32*)lines)[1];
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
