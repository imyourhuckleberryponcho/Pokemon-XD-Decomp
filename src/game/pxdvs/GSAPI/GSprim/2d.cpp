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
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
#include <dolphin/gx/GXVert.h>
extern s32 sp;
struct GSgfxVF;

struct GStexture {
    u8 pad[7];
    u8 dirty;
};

class GSgfxLayer {
public:
    u8 pad0[0xd34];
    u8 lineWidth;
    u8 pad_d35[3];
    s32 lineTexOffset;
    u8 pointSize;
    u8 pad_d3d[3];
    s32 pointTexOffset;
    u8 pad_d44[0x16a8 - 0xd44];
    u32 dirty16a8;
    u32 dirty16ac;
    u8 pad_16b0[0x173c - 0x16b0];
    u32 dirty173c;
    GStexture* tex1740;
    u8 pad_1744[0x1760 - 0x1744];
    u32 dirty1760;
    u32 dirty1764;
    u8 pad_1768[0x17f4 - 0x1768];
    u32 dirty17f4;
    GStexture* tex17f8;
    u8 pad_17fc[0x1998 - 0x17fc];
    s32 primitive;
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

struct PrimData {
    GSgfxLayer* layer;
    s32 f4;
    f32 lineWidth;
    s32 fc;
    s32 quadOrder;
    s32 quadVtx;
};

extern "C" {
extern PrimData primData;
GSgfxVF* GSgfxVFGetPredef(s32 id);
}

struct GSvec2 {
    f32 x, y;
};

static inline void primPosV2(GSvec2 p) {
    GXWGFifo.f32 = p.x;
    GXWGFifo.f32 = p.y;
}

static inline void primPos2(f32 x, f32 y) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
}

static inline void primColor(GXColor c) {
    GXWGFifo.u32 = *(u32*)&c;
}

static inline void primVtx2DC(f32 x, f32 y, GXColor c) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.u32 = *(u32*)&c;
}

static inline void primQuad2D(GXColor color, f32 x0, f32 y0, f32 x1, f32 y1) {
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(2));
    primData.layer->primitive = primData.quadVtx;
    primData.layer->beginSurface(4);
    primVtx2DC(x0, y0, color);
    primVtx2DC(x1, y0, color);
    primVtx2DC(x0, y1, color);
    primVtx2DC(x1, y1, color);
    primData.layer->endSurface();
}

static inline void primUpdateLineWidth() {
    if (primData.f4 != 1) {
        GSgfxLayer* l = primData.layer;
        l->lineWidth = 6.0f * primData.lineWidth;
        l->lineTexOffset = 0;
        l->dirty16ac |= 4;
        l->dirty16a8 |= 1;
        l->dirty1764 |= 4;
        l->dirty1760 |= 1;
        primData.f4 = 1;
    }
}

static inline void primLine2D(GXColor c0, GXColor c1, f32 x0, f32 y0, f32 x1, f32 y1) {
    primUpdateLineWidth();
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(2));
    primData.layer->primitive = 0xA8;
    primData.layer->beginSurface(2);
    primPos2(x0, y0);
    primColor(c0);
    primPos2(x1, y1);
    primColor(c1);
    primData.layer->endSurface();
}

static inline void primVtxV2C(GSvec2 p, GXColor c) {
    GXWGFifo.f32 = p.x;
    GXWGFifo.f32 = p.y;
    GXWGFifo.u32 = *(u32*)&c;
}

static inline void primVtx2DCT(f32 x, f32 y, GXColor c, f32 s, f32 t) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.u32 = *(u32*)&c;
    GXWGFifo.f32 = s;
    GXWGFifo.f32 = t;
}

static inline void primVtxV2CT(GSvec2 p, GXColor c, f32 s, f32 t) {
    GXWGFifo.f32 = p.x;
    GXWGFifo.f32 = p.y;
    GXWGFifo.u32 = *(u32*)&c;
    GXWGFifo.f32 = s;
    GXWGFifo.f32 = t;
}

static inline void primSetTexture(GStexture* tex) {
    GSgfxLayer* l = primData.layer;
    if (l->tex1740 != tex || l->tex17f8 != tex || tex->dirty != 0) {
        l->tex1740 = tex;
        l->dirty173c |= 1;
        l->tex17f8 = tex;
        l->dirty17f4 |= 1;
    }
}

#define PRIM_U32(l, o) (*(u32*)((u8*)(l) + (o)))
#define PRIM_S16(l, o) (*(s16*)((u8*)(l) + (o)))
#define PRIM_U8(l, o) (*(u8*)((u8*)(l) + (o)))
#define PRIM_MAX(a, b) ((a) > (b) ? (a) : (b))
#define PRIM_MIN(a, b) ((a) < (b) ? (a) : (b))
#define PRIM_CLAMP_S10(x) PRIM_MIN(PRIM_MAX(x, -0x400), 0x3FF)

static inline void primMark(GSgfxLayer* l, u32 sum, u32 off, u32 bit) {
    PRIM_U32(l, off) |= bit;
    l->dirty16a8 |= sum;
    PRIM_U32(l, off + 0xB8) |= bit;
    l->dirty1760 |= sum;
}

static inline void primSetTevColorS10(GXColorS10 c) {
    GSgfxLayer* l = primData.layer;
    PRIM_U32(l, 0x13FC) = 1;
    PRIM_S16(l, 0x1400) = PRIM_CLAMP_S10(c.r);
    PRIM_S16(l, 0x1402) = PRIM_CLAMP_S10(c.g);
    PRIM_S16(l, 0x1404) = PRIM_CLAMP_S10(c.b);
    PRIM_S16(l, 0x1406) = PRIM_CLAMP_S10(c.a);
    primMark(l, 8, 0x16E4, 2);
}

static inline void primSetTevColorOp(u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
    GSgfxLayer* l = primData.layer;
    PRIM_U32(l, 0x1170) = op;
    PRIM_U32(l, 0x1174) = bias;
    PRIM_U32(l, 0x1178) = scale;
    PRIM_U8(l, 0x117C) = clamp;
    PRIM_U32(l, 0x1180) = reg;
    primMark(l, 8, 0x16DC, 1);
}

static inline void primSetTevColorIn(u32 a, u32 b, u32 c, u32 d) {
    GSgfxLayer* l = primData.layer;
    PRIM_U32(l, 0xF70) = a;
    PRIM_U32(l, 0xF74) = b;
    PRIM_U32(l, 0xF78) = c;
    PRIM_U32(l, 0xF7C) = d;
    primMark(l, 8, 0x16D4, 1);
}

static inline void primSetTevAlphaOp(u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
    GSgfxLayer* l = primData.layer;
    PRIM_U32(l, 0x12B0) = op;
    PRIM_U32(l, 0x12B4) = bias;
    PRIM_U32(l, 0x12B8) = scale;
    PRIM_U8(l, 0x12BC) = clamp;
    PRIM_U32(l, 0x12C0) = reg;
    primMark(l, 8, 0x16E0, 1);
}

static inline void primSetTevAlphaIn(u32 a, u32 b, u32 c, u32 d) {
    GSgfxLayer* l = primData.layer;
    PRIM_U32(l, 0x1070) = a;
    PRIM_U32(l, 0x1074) = b;
    PRIM_U32(l, 0x1078) = c;
    PRIM_U32(l, 0x107C) = d;
    primMark(l, 8, 0x16D8, 1);
}

extern "C" {

void GSprimDraw2DTexQuad4VCA(GSvec2* v, GSvec2* uv, GStexture* tex, GXColor color, GXColorS10* tevColor) {
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(6));
    primSetTexture(tex);
    primSetTevColorS10(*tevColor);
    primSetTevColorOp(0, 0, 0, 1, 0);
    primSetTevColorIn(0xF, 0xA, 8, 2);
    primSetTevAlphaOp(0, 0, 0, 1, 0);
    primSetTevAlphaIn(7, 5, 4, 1);
    primData.layer->primitive = primData.quadVtx;
    primData.layer->beginSurface(4);
    primPosV2(v[0]);
    primColor(color);
    GXTexCoord2f32(uv[0].x, uv[0].y);
    primPosV2(v[1]);
    primColor(color);
    GXTexCoord2f32(uv[1].x, uv[1].y);
    primPosV2(v[2]);
    primColor(color);
    GXTexCoord2f32(uv[2].x, uv[2].y);
    primPosV2(v[3]);
    primColor(color);
    GXTexCoord2f32(uv[3].x, uv[3].y);
    primData.layer->endSurface();
}

void GSprimDraw2DTexQuad4V(GSvec2* v, GSvec2* uv, GStexture* tex, GXColor color) {
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(6));
    primSetTexture(tex);
    primData.layer->primitive = primData.quadVtx;
    primData.layer->beginSurface(4);
    primPosV2(v[0]);
    primColor(color);
    GXTexCoord2f32(uv[0].x, uv[0].y);
    primPosV2(v[1]);
    primColor(color);
    GXTexCoord2f32(uv[1].x, uv[1].y);
    primPosV2(v[2]);
    primColor(color);
    GXTexCoord2f32(uv[2].x, uv[2].y);
    primPosV2(v[3]);
    primColor(color);
    GXTexCoord2f32(uv[3].x, uv[3].y);
    primData.layer->endSurface();
}

void GSprimDraw2DTexQuad(GStexture* tex, GXColor color, f32 x0, f32 y0, f32 x1, f32 y1) {
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(6));
    primSetTexture(tex);
    primData.layer->primitive = primData.quadVtx;
    primData.layer->beginSurface(4);
    f32 zero = 0.0f;
    f32 one = 1.0f;
    primVtx2DCT(x0, y0, color, zero, zero);
    primVtx2DCT(x1, y0, color, one, zero);
    primVtx2DCT(x0, y1, color, zero, one);
    primVtx2DCT(x1, y1, color, one, one);
    primData.layer->endSurface();
}

void GSprimDraw2DQuad4V(GSvec2* v, GXColor color) {
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(2));
    primData.layer->primitive = primData.quadVtx;
    primData.layer->beginSurface(4);
    primPosV2(v[0]);
    primColor(color);
    primPosV2(v[1]);
    primColor(color);
    primPosV2(v[2]);
    primColor(color);
    primPosV2(v[3]);
    primColor(color);
    primData.layer->endSurface();
}

void GSprimDraw2DQuadWH(GXColor color, f32 x, f32 y, f32 w, f32 h) {
    primQuad2D(color, x, y, x + w, y + h);
}

void GSprimDraw2DQuad(GXColor color, f32 x0, f32 y0, f32 x1, f32 y1) {
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(2));
    primData.layer->primitive = primData.quadVtx;
    primData.layer->beginSurface(4);
    primVtx2DC(x0, y0, color);
    primVtx2DC(x1, y0, color);
    primVtx2DC(x0, y1, color);
    primVtx2DC(x1, y1, color);
    primData.layer->endSurface();
}

void GSprimDraw2DPixelListC(s16* pts, u32 n, u32* colors) {
    if (n == 0) {
        return;
    }
    GSgfxLayer* l = primData.layer;
    l->pointSize = 6;
    l->pointTexOffset = 0;
    l->dirty16ac |= 8;
    l->dirty16a8 |= 1;
    l->dirty1764 |= 8;
    l->dirty1760 |= 1;
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(3));
    primData.layer->primitive = 0xB8;
    primData.layer->beginSurface(n);
    while (n--) {
        GXPosition2s16(pts[0], pts[1]);
        GXColor1u32(colors[0]);
        pts += 2;
        colors++;
    }
    primData.layer->endSurface();
}

void GSprimDraw2DLineListC(GSvec2* pts, u32 n, GXColor* colors) {
    if (n < 1) {
        return;
    }
    primUpdateLineWidth();
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(2));
    primData.layer->primitive = 0xA8;
    primData.layer->beginSurface(n * 2);
    while (n--) {
        primPosV2(pts[0]);
        primColor(colors[0]);
        primPosV2(pts[1]);
        primColor(colors[1]);
        pts += 2;
        colors += 2;
    }
    primData.layer->endSurface();
}

void GSprimDraw2DVLine(GXColor color, f32 x, f32 y0, f32 y1) {
    primLine2D(color, color, x, y0, x, y1);
}

void GSprimDraw2DHLine(GXColor color, f32 x0, f32 x1, f32 y) {
    primLine2D(color, color, x0, y, x1, y);
}

void GSprimDraw2DLine(GXColor c0, GXColor c1, f32 x0, f32 y0, f32 x1, f32 y1) {
    primUpdateLineWidth();
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(2));
    primData.layer->primitive = 0xA8;
    primData.layer->beginSurface(2);
    primPos2(x0, y0);
    primColor(c0);
    primPos2(x1, y1);
    primColor(c1);
    primData.layer->endSurface();
}

}
