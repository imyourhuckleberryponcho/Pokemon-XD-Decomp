// DRAFT (dr_movie): all functions written, not yet exact. GSgfxLayer is accessed by raw offsets (W/B/H macros)
// for now; the original used the GSgfxLayer inline state setters (tevOrder/tevColorIn/... style).
#pragma pool_strings off
#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>

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

    u8 pad0[0x4];
    u32 flags;
    u8 pad8[0xd54 - 0x8];
    u32 projType;
    f32 proj[6];
    u8 padD6C[0x1656 - 0xd6c];
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
    GStextureCreateFromMemory(&texY, texW, texH, yData, 0x42, 0, 0);
    bindTexture(0, &texY);
    GStextureCreateFromMemory(&texU, (u16)((s16)texW >> 1), (u16)((s16)texH >> 1), uData, 0x42, 0, 0);
    bindTexture(1, &texU);
    GStextureCreateFromMemory(&texV, (u16)((s16)texW >> 1), (u16)((s16)texH >> 1), vData, 0x42, 0, 0);
    bindTexture(2, &texV);
    thpLayer->vf = GSgfxVFGetPredef(8);
    thpLayer->primType = 0x80;
    thpLayer->beginSurface(4);
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.s16 = x + polyW;
    GXWGFifo.s16 = y;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 0;
    GXWGFifo.s16 = x + polyW;
    GXWGFifo.s16 = y + polyH;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y + polyH;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 1;
    thpLayer->endSurface();
    return thpLayer->tokenMark();
}

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
    thpLayer->colorUpdate = 1;
    thpLayer->alphaUpdate = 0;
    thpLayer->zUpdate = 0;
    thpLayer->mark(0x40, 0x170C, 4);
    W(0x165C) = 1;
    W(0x1660) = 7;
    thpLayer->mark(0x40, 0x170C, 8);
    if (thpLayer->blendIdx != 0) {
        thpLayer->blendIdx = 0;
        thpLayer->curBlend = (u8*)thpLayer + thpLayer->blendIdx * 0xBC + 0x1818;
    }
    W(0x1644) = 0;
    W(0x1648) = 1;
    W(0x164C) = 1;
    W(0x1650) = 5;
    thpLayer->mark(0x40, 0x170C, 1);
    W(0xDB8) = 0;
    thpLayer->mark(4, 0x16BC, 1);
    W(0xC70) = 2;
    thpLayer->mark(1, 0x16AC, 1);
    thpLayer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
    thpLayer->tgenFunc(1, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
    thpLayer->flags |= 0x10000000;
    W(0xEAC) = 4;
    thpLayer->mark(8, 0x16CC, 1);
    W(0xEB0) = 1;
    W(0xEB4) = 1;
    W(0xEB8) = 0xFF;
    thpLayer->mark(8, 0x16D0, 1);
    W(0xF70) = 0xF;
    W(0xF74) = 8;
    W(0xF78) = 0xE;
    W(0xF7C) = 2;
    thpLayer->mark(8, 0x16D4, 1);
    W(0x1170) = 0;
    W(0x1174) = 0;
    W(0x1178) = 0;
    W(0x117C) = 0;
    W(0x1180) = 0;
    thpLayer->mark(8, 0x16DC, 1);
    W(0x1070) = 7;
    W(0x1074) = 4;
    W(0x1078) = 6;
    W(0x107C) = 1;
    thpLayer->mark(8, 0x16D8, 1);
    W(0x12B0) = 1;
    W(0x12B4) = 0;
    W(0x12B8) = 0;
    W(0x12BC) = 0;
    W(0x12C0) = 0;
    thpLayer->mark(8, 0x16E0, 1);
    thpLayer->tunitKRegSel(0, (GSgfxTunitKReg)0);
    W(0x1584) = 0;
    W(0x1588) = 0;
    thpLayer->mark(0x20, 0x1704, 1);
    W(0xEBC) = 1;
    W(0xEC0) = 2;
    W(0xEC4) = 0xFF;
    thpLayer->mark(8, 0x16D0, 2);
    W(0xF80) = 0xF;
    W(0xF84) = 8;
    W(0xF88) = 0xE;
    W(0xF8C) = 0;
    thpLayer->mark(8, 0x16D4, 2);
    W(0x1184) = 0;
    W(0x1188) = 0;
    W(0x118C) = 1;
    W(0x1190) = 0;
    W(0x1194) = 0;
    thpLayer->mark(8, 0x16DC, 2);
    W(0x1080) = 7;
    W(0x1084) = 4;
    W(0x1088) = 6;
    W(0x108C) = 0;
    thpLayer->mark(8, 0x16D8, 2);
    W(0x12C4) = 1;
    W(0x12C8) = 0;
    W(0x12CC) = 0;
    W(0x12D0) = 0;
    W(0x12D4) = 0;
    thpLayer->mark(8, 0x16E0, 2);
    thpLayer->tunitKRegSel(1, (GSgfxTunitKReg)1);
    W(0x158C) = 0;
    W(0x1590) = 0;
    thpLayer->mark(0x20, 0x1704, 2);
    W(0xEC8) = 0;
    W(0xECC) = 0;
    W(0xED0) = 0xFF;
    thpLayer->mark(8, 0x16D0, 4);
    W(0xF90) = 0xF;
    W(0xF94) = 8;
    W(0xF98) = 0xC;
    W(0xF9C) = 0;
    thpLayer->mark(8, 0x16D4, 4);
    W(0x1198) = 0;
    W(0x119C) = 0;
    W(0x11A0) = 0;
    W(0x11A4) = 1;
    W(0x11A8) = 0;
    thpLayer->mark(8, 0x16DC, 4);
    W(0x1090) = 4;
    W(0x1094) = 7;
    W(0x1098) = 7;
    W(0x109C) = 0;
    thpLayer->mark(8, 0x16D8, 4);
    W(0x12D8) = 0;
    W(0x12DC) = 0;
    W(0x12E0) = 0;
    W(0x12E4) = 1;
    W(0x12E8) = 0;
    thpLayer->mark(8, 0x16E0, 4);
    W(0x1594) = 0;
    W(0x1598) = 0;
    thpLayer->mark(0x20, 0x1704, 4);
    W(0xED4) = 0xFF;
    W(0xED8) = 0xFF;
    W(0xEDC) = 0xFF;
    thpLayer->mark(8, 0x16D0, 8);
    W(0xFA0) = 1;
    W(0xFA4) = 0;
    W(0xFA8) = 0xE;
    W(0xFAC) = 0xF;
    thpLayer->mark(8, 0x16D4, 8);
    W(0x11AC) = 0;
    W(0x11B0) = 0;
    W(0x11B4) = 0;
    W(0x11B8) = 1;
    W(0x11BC) = 0;
    thpLayer->mark(8, 0x16DC, 8);
    W(0x10A0) = 7;
    W(0x10A4) = 7;
    W(0x10A8) = 7;
    W(0x10AC) = 7;
    thpLayer->mark(8, 0x16D8, 8);
    W(0x12EC) = 0;
    W(0x12F0) = 0;
    W(0x12F4) = 0;
    W(0x12F8) = 1;
    W(0x12FC) = 0;
    thpLayer->mark(8, 0x16E0, 8);
    W(0x159C) = 0;
    W(0x15A0) = 0;
    thpLayer->mark(0x20, 0x1704, 8);
    W(0x1510) = 0xE;
    thpLayer->mark(0x10, 0x16FC, 8);
    {
        TevColorS10 c = {-90, 0, -114, 135};
        W(0x13fc) = 1;
        H(0x1400) = clampS10(c.r);
        H(0x1402) = clampS10(c.g);
        H(0x1404) = clampS10(c.b);
        H(0x1406) = clampS10(c.a);
    }
    thpLayer->mark(8, 0x16E4, 2);
    {
        TevKColor k = {0, 0, 226, 88};
        W(0x14F4) = *(u32*)&k;
    }
    thpLayer->mark(0x10, 0x16F8, 1);
    {
        TevKColor k = {179, 0, 0, 182};
        W(0x14F8) = *(u32*)&k;
    }
    thpLayer->mark(0x10, 0x16F8, 2);
    {
        TevKColor k = {255, 0, 255, 128};
        W(0x14FC) = *(u32*)&k;
    }
    thpLayer->mark(0x10, 0x16F8, 4);
    W(0x1604) = 0;
    W(0x1608) = 1;
    W(0x160C) = 2;
    W(0x1610) = 3;
    thpLayer->mark(0x20, 0x1708, 1);
}

void THPGXRestore(void) {
}

void THPGXSetRenderLayer(GSgfxLayer* layer) {
    thpLayer = layer;
}

}
