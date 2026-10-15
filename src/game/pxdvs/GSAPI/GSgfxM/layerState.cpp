// WIP (NonMatching): GSgfxLayer render state. Not done: SetupRenderState, SetupGPUState and the weak GSgfx_GCSet* helpers.
#include <dolphin/types.h>

struct GSgfxVF;
struct GSgfxLight;
struct GSmtx;
enum GSgfxCunitAlpha {};
enum GSgfxCunitSrc {};
enum GSgfxLightType {};
enum GSgfxDiffuseFunc {};
enum GSgfxTunitFunc {};
enum GSgfxTgenFunc {};
enum GSgfxTgenSrc {};

#define U8_AT(o) (*(u8*)((u8*)this + (o)))
#define U32_AT(o) (*(u32*)((u8*)this + (o)))
struct GSgfxCol {
    u32 v;
};
class GSgfxLayer {
public:
    void FlushState();
    void InvalidateState();
    void setRenderStateAndSelect(GSgfxVF* vf);
    void setRenderState(GSgfxVF* vf);
    void setRenderState(bool color, u8 tex, bool normal);
    void ResetVertexFormat(GSgfxVF* vf);
    void SetupRenderState();
    void LoadHWState();
    void renderState_NL_VC_T(u8 n);
    void renderState_NL_NVC_T(u8 n);
    void renderState_NL_NVC_NT();
    inline void renderState_VC_NT();
    void SetupFifo();
    void SetupGPUState();
    void cunitChannelGen(u8 ch, GSgfxCunitAlpha a, GSgfxCunitSrc s1, GSgfxCunitSrc s2, u32 mask, GSgfxLight** lights,
                         GSgfxLightType lt, GSgfxDiffuseFunc df);
    void tunitFunc(u8 stage, GSgfxTunitFunc func);
    void tgenFunc(u8 idx, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* m, bool norm, GSmtx* post);

    inline void mark(u32 sum, u32 off, u32 bit) {
        U32_AT(off) |= bit;
        U32_AT(0x16a8) |= sum;
        U32_AT(off + 0xb8) |= bit;
        U32_AT(0x1760) |= sum;
    }
    inline void markCommon(u8 vc, u8 tex, u8 mode);
    inline void markStage(u32 i, u32 a, u32 b, u32 c);
    u8 pad0[0x4];
    u32 flags;
    u8 pad8[0x30 - 0x8];
    u8 hwState[0xc40];
    u8 pad_c70[0x1420 - 0xc70];
    struct Stage {
        u32 a;
        u32 pad[8];
    } stages[8];
    u8 pad1540[0x1584 - 0x1540];
    struct TexUnit {
        u32 a, b;
    } texUnits[8];
    u8 pad15c4[0x16a8 - 0x15c4];
    struct DirtyState {
        u8 pad[0x68];
        GSgfxVF* vf[8];
        GSgfxVF* last;
        u8 rest[0x2c];
    } dirty[2];
    u8 pad1818[0x199c - 0x1818];
    GSgfxVF* curVF;
};

u8 GSgfxRenderModuleIsRendering();
extern "C" {
u8 GSgfxVFGetColorCount(GSgfxVF*);
u8 GSgfxVFGetTextureCount(GSgfxVF*);
u8 GSgfxVFHasElement(GSgfxVF*, int);
void GXFlush();
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
}


extern "C" void* gsgfxState;
u8* _layerStateLastHWState;

void GSgfxLayer::FlushState() {
    SetupFifo();
    SetupRenderState();
    extern void GSgfxLayerUpdateActiveFifoStats();
    GSgfxLayerUpdateActiveFifoStats();
}

void GSgfxLayer::InvalidateState() {
    if (GSgfxRenderModuleIsRendering() == 1) {
        GXFlush();
    }
    memset((u8*)this + 0x16a8, 0, 0xb8);
    memset((u8*)this + 0x1760, 0, 0xb8);
    flags |= 0x80000000;
}

void GSgfxLayer::setRenderStateAndSelect(GSgfxVF* vf) {
    setRenderState(vf);
    curVF = vf;
}

void GSgfxLayer::setRenderState(GSgfxVF* vf) {
    u8 colors = GSgfxVFGetColorCount(vf);
    u8 textures = GSgfxVFGetTextureCount(vf);
    bool normal = false;
    if (GSgfxVFHasElement(vf, 10) || GSgfxVFHasElement(vf, 25)) {
        normal = true;
    }
    if (colors == 0) {
        setRenderState(false, textures, normal);
    } else {
        setRenderState(true, textures, normal);
    }
}

void GSgfxLayer::markCommon(u8 vc, u8 tex, u8 mode) {
    (void)mode;
    U8_AT(0xc70) = tex;
    mark(1, 0x16ac, 1);
    U8_AT(0xeac) = vc;
    mark(8, 0x16cc, 1);
    U8_AT(0x14b0) = 0;
    mark(0x80, 0x16ec, 1);
}

void GSgfxLayer::markStage(u32 i, u32 a, u32 b, u32 c) {
    u32 bit = 1 << i;
    stages[i].a = 0;
    U32_AT(0x16e8) |= bit;
    U32_AT(0x16a8) |= 8;
    U32_AT(0x17a0) |= bit;
    U32_AT(0x1760) |= 8;
    u32* t = (u32*)((u8*)this + i * 12);
    t[0xeb0 / 4] = a;
    t[0xeb4 / 4] = b;
    t[0xeb8 / 4] = c;
}

void GSgfxLayer::renderState_NL_VC_T(u8 n) {
    U8_AT(0xdb8) = 1;
    mark(4, 0x16bc, 1);
    markCommon(n, n, 0);
    cunitChannelGen(0, (GSgfxCunitAlpha)2, (GSgfxCunitSrc)0, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2, (GSgfxDiffuseFunc)0);
    for (u8 i = 0; i < n; i++) {
        tgenFunc(i, (GSgfxTgenFunc)1, (GSgfxTgenSrc)(i + 4), 0, 0, 0);
    }
    for (u8 i = 0; i < n; i++) {
        markStage(i, i, i, 4);
        mark(8, 0x16d0, 1 << i);
        if (i == 0) {
            tunitFunc(i, (GSgfxTunitFunc)0);
        } else {
            tunitFunc(i, (GSgfxTunitFunc)7);
        }
        texUnits[i].a = 0;
        texUnits[i].b = 0;
        mark(0x20, 0x1704, 1 << i);
    }
}

void GSgfxLayer::renderState_NL_NVC_T(u8 n) {
    U8_AT(0xdb8) = 0;
    mark(4, 0x16bc, 1);
    markCommon(n, n, 0);
    u8 i;
    for (i = 0; i < n; i++) {
        tgenFunc(i, (GSgfxTgenFunc)1, (GSgfxTgenSrc)(i + 4), 0, 0, 0);
    }
    for (i = 0; i < n; i++) {
        markStage(i, i, i, 0xff);
        mark(8, 0x16d0, 1 << i);
        if (i == 0) {
            tunitFunc(i, (GSgfxTunitFunc)3);
        } else {
            tunitFunc(i, (GSgfxTunitFunc)5);
        }
        texUnits[i].a = 0;
        texUnits[i].b = 0;
        mark(0x20, 0x1704, 1 << i);
    }
}

void GSgfxLayer::renderState_NL_NVC_NT() {
    GSgfxCol g = {0x80808080};
    GSgfxCol a = g;
    GSgfxCol b = g;
    GSgfxCol c = g;
    U8_AT(0xdb8) = 1;
    mark(4, 0x16bc, 1);
    markCommon(1, 0, 0);
    *(GSgfxCol*)((u8*)this + 0xe9c) = a;
    *(GSgfxCol*)((u8*)this + 0xea4) = c;
    U32_AT(0x16c4) |= 1;
    U32_AT(0x16c8) |= 1;
    U32_AT(0x16a8) |= 4;
    U32_AT(0x177c) |= 1;
    U32_AT(0x1780) |= 1;
    U32_AT(0x1760) |= 4;
    cunitChannelGen(0, (GSgfxCunitAlpha)2, (GSgfxCunitSrc)0, (GSgfxCunitSrc)0, 0, 0, (GSgfxLightType)2, (GSgfxDiffuseFunc)0);
    U32_AT(0xeb0) = 0xff;
    U32_AT(0xeb4) = 0xff;
    U32_AT(0xeb8) = 4;
    mark(8, 0x16d0, 1);
    tunitFunc(0, (GSgfxTunitFunc)4);
    texUnits[0].a = 0;
    texUnits[0].b = 0;
    mark(0x20, 0x1704, 1);
}

void GSgfxLayer::LoadHWState() {
    if (_layerStateLastHWState != hwState) {
        if (_layerStateLastHWState != 0) {
            memcpy(_layerStateLastHWState, gsgfxState, 0xc40);
        }
        memcpy(gsgfxState, hwState, 0xc40);
        _layerStateLastHWState = hwState;
    }
}

void GSgfxLayer::ResetVertexFormat(GSgfxVF* vf) {
    DirtyState* d = dirty;
    if (vf == curVF) {
        curVF = 0;
    }
    for (int i = 0; i < 2; i++, d++) {
        if (d->last == vf) d->last = 0;
        for (int j = 0; j < 8; j++) {
            if (d->vf[j] == vf) d->vf[j] = 0;
        }
    }
}

void GSgfxLayer::renderState_VC_NT() {
    U8_AT(0xdb8) = 1;
    mark(4, 0x16bc, 1);
    markCommon(1, 0, 0);
    cunitChannelGen(0, (GSgfxCunitAlpha)2, (GSgfxCunitSrc)0, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2, (GSgfxDiffuseFunc)0);
    U32_AT(0xeb0) = 0xff;
    U32_AT(0xeb4) = 0xff;
    U32_AT(0xeb8) = 4;
    mark(8, 0x16d0, 1);
    tunitFunc(0, (GSgfxTunitFunc)4);
    texUnits[0].a = 0;
    texUnits[0].b = 0;
    mark(0x20, 0x1704, 1);
}

void GSgfxLayer::setRenderState(bool color, u8 tex, bool normal) {
    if (!normal) {
        if (!color) {
            if (!tex) {
                renderState_NL_NVC_NT();
            } else {
                renderState_NL_NVC_T(tex);
            }
        } else {
            if (!tex) {
                renderState_VC_NT();
            } else {
                renderState_NL_VC_T(tex);
            }
        }
    }
}
