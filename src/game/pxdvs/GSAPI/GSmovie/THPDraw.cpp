#pragma pool_strings off
#include <dolphin/types.h>
#include <game/pcret.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXStruct.h>
#define THP_MAX(a, b) ((a) > (b) ? (a) : (b))
#define THP_MIN(a, b) ((a) < (b) ? (a) : (b))
#ifdef __MWERKS__
#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)
#else
#define GXFifoNV GXWGFifo
#endif

struct GStexture {
    u16 width;
    u16 height;
    u8 bitsPerPixel;
    u8 mipLevels;
    u8 inUse;
    u8 dirty;
    s32 format;
    u32 tlutFormat;
    u32 wrapS;
    u32 wrapT;
    s32 minFilter;
    s32 magFilter;
    u32 mipFilter;
    void* memHandle;
    void* mipData[8];
    void* tlutData;
    u32 totalSize;
    u16 refCount;
    u16 pad52;
    GXTexObj texObj;
    GXTlutObj tlutObj;
#ifndef __MWERKS__
    void* pcDisc;
#endif
};

struct GSmtx;
struct GSgfxVF;
enum GSgfxTgenFunc {};
enum GSgfxTgenSrc {};
enum GSgfxTunitKReg {};

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void beginSurface(u16 count);
    void endSurface();
    u16 tokenMark();
    void tgenFunc(u8 idx, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* m, bool norm, GSmtx* post);
    void tunitKRegSel(u8 stage, GSgfxTunitKReg reg);

    inline void markWord(u32 sum, u32 word, u32 bit) {
#ifdef __MWERKS__
        *(u32*)((u8*)this + 0x16a8 + word * 4) |= bit;
        *(u32*)((u8*)this + 0x16a8) |= sum;
        *(u32*)((u8*)this + 0x1760 + word * 4) |= bit;
        *(u32*)((u8*)this + 0x1760) |= sum;
#else
        (&dirty[0].groups)[word] |= bit;
        dirty[0].groups |= sum;
        (&dirty[1].groups)[word] |= bit;
        dirty[1].groups |= sum;
#endif
    }

    inline void pixelUpdate(u8 color, u8 alpha, u8 z) {
        (*(u8*)&this->hw.colorUpdate) = color;
        (*(u8*)&this->hw.alphaUpdate) = alpha;
        (*(u8*)&this->hw.zUpdate) = z;
        markWord(0x40, 0x19, 4);
    }
    inline void zMode(u8 enable, u32 func) {
        hw.zEnable = enable;
        hw.zFunc = func;
        markWord(0x40, 0x19, 8);
    }
    inline void blendMode(int idx, u32 type, u32 src, u32 dst, u32 op) {
        if ((*(s32*)&this->curPass) != idx) {
            (*(s32*)&this->curPass) = idx;
#ifdef __MWERKS__
            (*(u8**)&this->curFifo) = (u8*)this + (*(s32*)&this->curPass) * 0xBC + 0x1818;
#else
            (*(u8**)&this->curFifo) = LAYER_CUR_PASS(this);
#endif
        }
        hw.blend[0] = type;
        hw.blend[1] = src;
        hw.blend[2] = dst;
        hw.blend[3] = op;
        markWord(0x40, 0x19, 1);
    }
    inline void numChans(u8 n) {
        hw.nChans = n;
        markWord(4, 0x5, 1);
    }
    inline void numTexGens(u8 n) {
        hw.nTexGens = n;
        markWord(1, 0x1, 1);
    }
    inline void tevColorS10(u32 id, GXColorS10 c) {
        hw.tevColor[1].type = id;
        hw.tevColor[1].v.s10[0] = THP_MIN(THP_MAX(c.r, -0x400), 0x3FF);
        hw.tevColor[1].v.s10[1] = THP_MIN(THP_MAX(c.g, -0x400), 0x3FF);
        hw.tevColor[1].v.s10[2] = THP_MIN(THP_MAX(c.b, -0x400), 0x3FF);
        hw.tevColor[1].v.s10[3] = THP_MIN(THP_MAX(c.a, -0x400), 0x3FF);
        markWord(8, 0xF, 2);
    }
    inline void tevKColor(int id, GXColor c) {
        *(u32*)&hw.kcolor[id] = *(u32*)&c;
        markWord(0x10, 0x14, 1 << id);
    }
    inline void tevSwapTable(int table, u32 r, u32 g, u32 b, u32 a) {
        u32* p = (u32*)hw.swapTab[table];
        p[0] = r;
        p[1] = g;
        p[2] = b;
        p[3] = a;
        markWord(0x20, 0x18, 1 << table);
    }
    inline void tevNumStages(u8 n) {
        hw.nTevStages = n;
        markWord(8, 0x9, 1);
    }
    inline void tevOrder(int stage, u32 coord, u32 map, u32 color) {
        u32* p = (u32*)hw.tevOrder[stage];
        p[0] = coord;
        p[1] = map;
        p[2] = color;
        markWord(8, 0xA, 1 << stage);
    }
    inline void tevColorIn(int stage, u32 a, u32 b, u32 c, u32 d) {
        u32* p = (u32*)hw.colorIn[stage];
        p[0] = a;
        p[1] = b;
        p[2] = c;
        p[3] = d;
        markWord(8, 0xB, 1 << stage);
    }
    inline void tevAlphaIn(int stage, u32 a, u32 b, u32 c, u32 d) {
        u32* p = (u32*)((u8*)hw.alphaIn + stage * 0x10);
        p[0] = a;
        p[1] = b;
        p[2] = c;
        p[3] = d;
        markWord(8, 0xC, 1 << stage);
    }
    inline void tevColorOp(int stage, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
        u8* p = (u8*)&hw.colorOp[stage];
        *(u32*)(p + 0x0) = op;
        *(u32*)(p + 0x4) = bias;
        *(u32*)(p + 0x8) = scale;
        *(u8*)(p + 0xC) = clamp;
        *(u32*)(p + 0x10) = reg;
        markWord(8, 0xD, 1 << stage);
    }
    inline void tevAlphaOp(int stage, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
        u8* p = (u8*)&hw.alphaOp[stage];
        *(u32*)(p + 0x0) = op;
        *(u32*)(p + 0x4) = bias;
        *(u32*)(p + 0x8) = scale;
        *(u8*)(p + 0xC) = clamp;
        *(u32*)(p + 0x10) = reg;
        markWord(8, 0xE, 1 << stage);
    }
    inline void tevKColorSel(int stage, u32 sel) {
        hw.kcsel[stage] = sel;
        markWord(0x10, 0x15, 1 << stage);
    }
    inline void tevSwapMode(int stage, u32 ras, u32 tex) {
        u32* p = (u32*)hw.swapSel[stage];
        p[0] = ras;
        p[1] = tex;
        markWord(0x20, 0x17, 1 << stage);
    }

};

extern "C" {
void GSgfxVideoGetEFBSize(u16* w, u16* h);
void GSmtx44Ortho(f32* m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
GStexture* GStextureCreateFromMemory(GStexture*, u16, PCARG(u16, u32), void*, s32, void*, PCARG(u8, u32));
GSgfxVF* GSgfxVFGetPredef(s32 id);
void* memcpy(void* dst, const void* src, u32 n);
extern u8 mtxIdent[0x30];
}

GSgfxLayer* thpLayer;

struct THPMatrixEntry {
    u32 flags;
    f32 mtx[3][4];
};
struct THPMatrixStack {
    THPMatrixEntry* base;
    THPMatrixEntry* top;
};

#define W(o) (*(u32*)((u8*)thpLayer + (o)))
#define B(o) (*(u8*)((u8*)thpLayer + (o)))
#define H(o) (*(s16*)((u8*)thpLayer + (o)))
#define LW(l, o) (*(u32*)((u8*)(l) + (o)))
#define LB(l, o) (*(u8*)((u8*)(l) + (o)))
#define LH(l, o) (*(s16*)((u8*)(l) + (o)))
#define LF(l, o) (*(f32*)((u8*)(l) + (o)))
#define F(o) (*(f32*)((u8*)thpLayer + (o)))

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
    GSgfxLayer* l = thpLayer;
    if ((GStexture*)l->dirty[0].tex[slot] != t || (GStexture*)l->dirty[1].tex[slot] != t || t->dirty != 0) {
        l->dirty[0].tex[slot] = (GSgfxTex*)t;
        l->dirty[0].texMask |= 1 << slot;
        l->dirty[1].tex[slot] = (GSgfxTex*)t;
        l->dirty[1].texMask |= 1 << slot;
    }
}

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
    (*(GSgfxVF**)&thpLayer->curVF) = GSgfxVFGetPredef(8);
    (*(u32*)&thpLayer->unk1998) = 0x80;
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
    (*(u32*)&l->hw.projType) = 1;
    ((f32*)l->hw.proj)[0] = m[0];
    ((f32*)l->hw.proj)[1] = m[3];
    ((f32*)l->hw.proj)[2] = m[5];
    ((f32*)l->hw.proj)[3] = m[7];
    ((f32*)l->hw.proj)[4] = m[10];
    ((f32*)l->hw.proj)[5] = m[11];
    {
        THPMatrixStack* ms = (*(THPMatrixStack**)&l->matrixStack);
        memcpy(ms->top->mtx, mtxIdent, 0x30);
        ms->top->flags |= 1;
    }
    l->hw.fogNear = 0.0f;
    l->hw.fogFar = 30000.0f;
    if ((*(u8*)&l->hw.fogEnable) != 0) {
        if ((*(u8*)&l->hw.fogRangeEnable) != 0) {
            l->dirty[0].pe |= 0x100;
            l->dirty[1].pe |= 0x100;
        }
        l->dirty[0].pe |= 0x40;
        l->dirty[0].groups |= 0x40;
        l->dirty[1].pe |= 0x40;
        l->dirty[1].groups |= 0x40;
    }
    l->markWord(1, 0x1, 0x20);
    l = thpLayer;
    l->hw.scissor[0] = 0;
    l->hw.scissor[1] = 0;
    GSgfxVideoGetEFBSize(&l->hw.scissor[2], &l->hw.scissor[3]);
    l->markWord(2, 0x4, 1);
    thpLayer->pixelUpdate(1, 0, 0);
    thpLayer->zMode(1, 7);
    thpLayer->blendMode(0, 0, 1, 1, 5);
    thpLayer->numChans(0);
    thpLayer->numTexGens(2);
    thpLayer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
    thpLayer->tgenFunc(1, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
    (*(u32*)&thpLayer->flags) |= 0x10000000;
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
        GXColorS10 c = {-90, 0, -114, 135};
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
