// DRAFT (dr_movie): all functions written, not yet exact. GSgfxLayer is accessed by raw offsets (W/B/H macros)
// for now; the original used the GSgfxLayer inline state setters (tevOrder/tevColorIn/... style).
#pragma pool_strings off
#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXStruct.h>
#define THP_MAX(a, b) ((a) > (b) ? (a) : (b))
#define THP_MIN(a, b) ((a) < (b) ? (a) : (b))
// Non-volatile view of the GX write-gather FIFO: the original kept constants in
// registers and stored narrowed values without re-narrowing, which the volatile GXWGFifo does not.
#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)

struct GStexture {
    u8 pad[7];
    u8 dirty;
    u8 rest[0x78];
};

struct GSmtx;
struct GSgfxVF;
enum GSgfxTgenFunc {};
enum GSgfxTgenSrc {};
enum GSgfxTunitKReg {};

class GSgfxLayer {
public:
    void beginSurface(u16 count);
    void endSurface();
    u16 tokenMark();
    void tgenFunc(u8 idx, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* m, bool norm, GSmtx* post);
    void tunitKRegSel(u8 stage, GSgfxTunitKReg reg);

    inline void mark(u32 sum, u32 off, u32 bit) {
        *(u32*)((u8*)this + off) |= bit;
        *(u32*)((u8*)this + 0x16a8) |= sum;
        *(u32*)((u8*)this + off + 0xb8) |= bit;
        *(u32*)((u8*)this + 0x1760) |= sum;
    }

    inline void pixelUpdate(u8 color, u8 alpha, u8 z) {
        colorUpdate = color;
        alphaUpdate = alpha;
        zUpdate = z;
        mark(0x40, 0x170C, 4);
    }
    inline void zMode(u8 enable, u32 func) {
        *((u8*)this + 0x165C) = enable;
        *(u32*)((u8*)this + 0x1660) = func;
        mark(0x40, 0x170C, 8);
    }
    inline void blendMode(int idx, u32 type, u32 src, u32 dst, u32 op) {
        if (blendIdx != idx) {
            blendIdx = idx;
            curBlend = (u8*)this + blendIdx * 0xBC + 0x1818;
        }
        *(u32*)((u8*)this + 0x1644) = type;
        *(u32*)((u8*)this + 0x1648) = src;
        *(u32*)((u8*)this + 0x164C) = dst;
        *(u32*)((u8*)this + 0x1650) = op;
        mark(0x40, 0x170C, 1);
    }
    inline void numChans(u8 n) {
        *((u8*)this + 0xDB8) = n;
        mark(4, 0x16BC, 1);
    }
    inline void numTexGens(u8 n) {
        *((u8*)this + 0xC70) = n;
        mark(1, 0x16AC, 1);
    }
    inline void tevColorS10(u32 id, GXColorS10 c) {
        *(u32*)((u8*)this + 0x13FC) = id;
        *(s16*)((u8*)this + 0x1400) = THP_MIN(THP_MAX(c.r, -0x400), 0x3FF);
        *(s16*)((u8*)this + 0x1402) = THP_MIN(THP_MAX(c.g, -0x400), 0x3FF);
        *(s16*)((u8*)this + 0x1404) = THP_MIN(THP_MAX(c.b, -0x400), 0x3FF);
        *(s16*)((u8*)this + 0x1406) = THP_MIN(THP_MAX(c.a, -0x400), 0x3FF);
        mark(8, 0x16E4, 2);
    }
    inline void tevKColor(int id, GXColor c) {
        *(GXColor*)((u8*)this + 0x14F4 + id * 4) = c;
        mark(0x10, 0x16F8, 1 << id);
    }
    inline void tevSwapTable(int table, u32 r, u32 g, u32 b, u32 a) {
        u32* p = (u32*)((u8*)this + 0x1604 + table * 0x10);
        p[0] = r;
        p[1] = g;
        p[2] = b;
        p[3] = a;
        mark(0x20, 0x1708, 1 << table);
    }
 // TEV state setters (XD's GSgfxLayer keeps a shadow of the GX TEV state; one dirty bit per stage)
    inline void tevNumStages(u8 n) {
        *((u8*)this + 0xEAC) = n;
        mark(8, 0x16CC, 1);
    }
    inline void tevOrder(int stage, u32 coord, u32 map, u32 color) {
        u32* p = (u32*)((u8*)this + 0xEB0 + stage * 0xC);
        p[0] = coord;
        p[1] = map;
        p[2] = color;
        mark(8, 0x16D0, 1 << stage);
    }
    inline void tevColorIn(int stage, u32 a, u32 b, u32 c, u32 d) {
        u32* p = (u32*)((u8*)this + 0xF70 + stage * 0x10);
        p[0] = a;
        p[1] = b;
        p[2] = c;
        p[3] = d;
        mark(8, 0x16D4, 1 << stage);
    }
    inline void tevAlphaIn(int stage, u32 a, u32 b, u32 c, u32 d) {
        u32* p = (u32*)((u8*)this + 0x1070 + stage * 0x10);
        p[0] = a;
        p[1] = b;
        p[2] = c;
        p[3] = d;
        mark(8, 0x16D8, 1 << stage);
    }
    inline void tevColorOp(int stage, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
        u8* p = (u8*)this + 0x1170 + stage * 0x14;
        *(u32*)(p + 0x0) = op;
        *(u32*)(p + 0x4) = bias;
        *(u32*)(p + 0x8) = scale;
        *(u8*)(p + 0xC) = clamp;
        *(u32*)(p + 0x10) = reg;
        mark(8, 0x16DC, 1 << stage);
    }
    inline void tevAlphaOp(int stage, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
        u8* p = (u8*)this + 0x12B0 + stage * 0x14;
        *(u32*)(p + 0x0) = op;
        *(u32*)(p + 0x4) = bias;
        *(u32*)(p + 0x8) = scale;
        *(u8*)(p + 0xC) = clamp;
        *(u32*)(p + 0x10) = reg;
        mark(8, 0x16E0, 1 << stage);
    }
    inline void tevKColorSel(int stage, u32 sel) {
        *(u32*)((u8*)this + 0x1504 + stage * 4) = sel;
        mark(0x10, 0x16FC, 1 << stage);
    }
    inline void tevSwapMode(int stage, u32 ras, u32 tex) {
        u32* p = (u32*)((u8*)this + 0x1584 + stage * 8);
        p[0] = ras;
        p[1] = tex;
        mark(0x20, 0x1704, 1 << stage);
    }

    u8 pad0[0x4];
    u32 flags;
    u8 pad8[0xd54 - 0x8];
    u32 projType;
    f32 proj[6];
    u8 padD70[0x1656 - 0xd70];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 zUpdate;
    u8 pad1659[0x16a6 - 0x1659];
    u8 f16a6;
    u8 f16a7;
    u8 pad16a8[0x1990 - 0x16a8];
    u8* curBlend;
    s32 blendIdx;
    GSgfxVF* vf;
    u32 primType;
    u8* hwMtx;
    u8 pad19A4[0x4];
};

extern "C" {
void GSgfxVideoGetEFBSize(u16* w, u16* h);
void GSmtx44Ortho(f32* m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
GStexture* GStextureCreateFromMemory(GStexture*, u16, u16, void*, s32, void*, u8);
GSgfxVF* GSgfxVFGetPredef(s32 id);
void* memcpy(void* dst, const void* src, u32 n);
extern u8 mtxIdent[0x30];
}

GSgfxLayer* thpLayer;

#define W(o) (*(u32*)((u8*)thpLayer + (o)))
#define B(o) (*(u8*)((u8*)thpLayer + (o)))
#define H(o) (*(s16*)((u8*)thpLayer + (o)))
#define LW(l, o) (*(u32*)((u8*)(l) + (o)))
#define LB(l, o) (*(u8*)((u8*)(l) + (o)))
#define LH(l, o) (*(s16*)((u8*)(l) + (o)))
#define LF(l, o) (*(f32*)((u8*)(l) + (o)))
#define F(o) (*(f32*)((u8*)thpLayer + (o)))

// TEV S10 colour register: components are clamped to [-0x400, 0x3ff].
static inline s16 clampS10(s16 v) {
    if (v < -0x400) {
        v = -0x400;
    }
    if (v > 0x3ff) {
        v = 0x3ff;
    }
    return v;
}

struct TevColorS10 {
    s16 r, g, b, a;
};
struct TevKColor {
    u8 r, g, b, a;
};

static inline void bindTexture(int slot, GStexture* t) {
    u32 off = 0x1740 + slot * 4;
    if (*(GStexture**)((u8*)thpLayer + off) != t || *(GStexture**)((u8*)thpLayer + off + 0xb8) != t || t->dirty != 0) {
        *(GStexture**)((u8*)thpLayer + off) = t;
        W(0x173c) |= 1 << slot;
        *(GStexture**)((u8*)thpLayer + off + 0xb8) = t;
        W(0x17f4) |= 1 << slot;
    }
}

// ---------------------------------------------------------------- functions
extern "C" {

u16 THPGXYuv2RgbDraw(u8* yData, u8* uData, u8* vData, s16 x, s16 y, u16 texW, u16 texH, s16 polyW, s16 polyH) {
    GStexture texY;
    GStexture texU;
    GStexture texV;
    GStextureCreateFromMemory(&texY, (u16)texW, (u16)texH, yData, 0x42, 0, 0);
    bindTexture(0, &texY);
    GStextureCreateFromMemory(&texU, (u16)((s16)texW >> 1), (u16)((s16)texH >> 1), uData, 0x42, 0, 0);
    bindTexture(1, &texU);
    GStextureCreateFromMemory(&texV, (u16)((s16)texW >> 1), (u16)((s16)texH >> 1), vData, 0x42, 0, 0);
    bindTexture(2, &texV);
    thpLayer->vf = GSgfxVFGetPredef(8);
    thpLayer->primType = 0x80;
    thpLayer->beginSurface(4);
    GXFifoNV.s16 = x;
    GXFifoNV.s16 = y;
    GXFifoNV.u8 = 0;
    GXFifoNV.u8 = 0;
    GXFifoNV.s16 = x + polyW;
    GXFifoNV.s16 = y;
    GXFifoNV.u8 = 1;
    GXFifoNV.u8 = 0;
    GXFifoNV.s16 = x + polyW;
    GXFifoNV.s16 = y + polyH;
    GXFifoNV.u8 = 1;
    GXFifoNV.u8 = 1;
    GXFifoNV.s16 = x;
    GXFifoNV.s16 = y + polyH;
    GXFifoNV.u8 = 0;
    GXFifoNV.u8 = 1;
    thpLayer->endSurface();
    return thpLayer->tokenMark();
}

#pragma optimize_for_size on
void THPGXYuv2RgbSetup(void) {
    u16 w, h;
    f32 m[16];
    GSgfxLayer* l;
    GSgfxVideoGetEFBSize(&w, &h);
    l = thpLayer;
    GSmtx44Ortho(m, 0.0f, (f32)(s32)h, 0.0f, (f32)(s32)w, 0.0f, -30000.0f);
    l->projType = 1;
    l->proj[0] = m[0];
    l->proj[1] = m[3];
    l->proj[2] = m[5];
    l->proj[3] = m[7];
    l->proj[4] = m[10];
    l->proj[5] = m[11];
    {
        u8* hw = l->hwMtx;
        memcpy(*(u8**)(hw + 4) + 4, mtxIdent, 0x30);
        **(u32**)(hw + 4) |= 1;
    }
    LF(l, 0x1684) = 0.0f;
    LF(l, 0x1688) = 30000.0f;
    if (l->f16a7 != 0) {
        if (l->f16a6 != 0) {
            LW(l, 0x170c) |= 0x100;
            LW(l, 0x17c4) |= 0x100;
        }
        LW(l, 0x170c) |= 0x40;
        LW(l, 0x16a8) |= 0x40;
        LW(l, 0x17c4) |= 0x40;
        LW(l, 0x1760) |= 0x40;
    }
    l->mark(1, 0x16ac, 0x20);
    l = thpLayer;
    LH(l, 0xd70) = 0;
    LH(l, 0xd72) = 0;
    GSgfxVideoGetEFBSize((u16*)((u8*)l + 0xd74), (u16*)((u8*)l + 0xd76));
    l->mark(2, 0x16b8, 1);
    thpLayer->pixelUpdate(1, 0, 0);
    thpLayer->zMode(1, 7);
    thpLayer->blendMode(0, 0, 1, 1, 5);
    thpLayer->numChans(0);
    thpLayer->numTexGens(2);
    thpLayer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
    thpLayer->tgenFunc(1, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
    thpLayer->flags |= 0x10000000;
    thpLayer->tevNumStages(4);
    thpLayer->tevOrder(0, 1, 1, 0xFF);
    thpLayer->tevColorIn(0, 0xF, 8, 0xE, 2);
    thpLayer->tevColorOp(0, 0, 0, 0, 0, 0);
    thpLayer->tevAlphaIn(0, 7, 4, 6, 1);
    thpLayer->tevAlphaOp(0, 1, 0, 0, 0, 0);
    thpLayer->tunitKRegSel(0, (GSgfxTunitKReg)0);
    thpLayer->tevSwapMode(0, 0, 0);
    thpLayer->tevOrder(1, 1, 2, 0xFF);
    thpLayer->tevColorIn(1, 0xF, 8, 0xE, 0);
    thpLayer->tevColorOp(1, 0, 0, 1, 0, 0);
    thpLayer->tevAlphaIn(1, 7, 4, 6, 0);
    thpLayer->tevAlphaOp(1, 1, 0, 0, 0, 0);
    thpLayer->tunitKRegSel(1, (GSgfxTunitKReg)1);
    thpLayer->tevSwapMode(1, 0, 0);
    thpLayer->tevOrder(2, 0, 0, 0xFF);
    thpLayer->tevColorIn(2, 0xF, 8, 0xC, 0);
    thpLayer->tevColorOp(2, 0, 0, 0, 1, 0);
    thpLayer->tevAlphaIn(2, 4, 7, 7, 0);
    thpLayer->tevAlphaOp(2, 0, 0, 0, 1, 0);
    thpLayer->tevSwapMode(2, 0, 0);
    thpLayer->tevOrder(3, 0xFF, 0xFF, 0xFF);
    thpLayer->tevColorIn(3, 1, 0, 0xE, 0xF);
    thpLayer->tevColorOp(3, 0, 0, 0, 1, 0);
    thpLayer->tevAlphaIn(3, 7, 7, 7, 7);
    thpLayer->tevAlphaOp(3, 0, 0, 0, 1, 0);
    thpLayer->tevSwapMode(3, 0, 0);
    thpLayer->tevKColorSel(3, 0xE);
    {
        volatile GXColorS10 c = {-90, 0, -114, 135};
        thpLayer->tevColorS10(1, c);
    }
    {
        GXColor k = {0, 0, 226, 88};
        thpLayer->tevKColor(0, k);
    }
    {
        GXColor k = {179, 0, 0, 182};
        thpLayer->tevKColor(1, k);
    }
    {
        GXColor k = {255, 0, 255, 128};
        thpLayer->tevKColor(2, k);
    }
    thpLayer->tevSwapTable(0, 0, 1, 2, 3);
}

#pragma optimize_for_size reset
void THPGXRestore(void) {
}

void THPGXSetRenderLayer(GSgfxLayer* layer) {
    thpLayer = layer;
}

}
