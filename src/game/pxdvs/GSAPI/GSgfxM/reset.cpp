// STATUS (dGfx): 8/9 exact. Default flags (pool_strings off). _resetDoFade (98.7%): only the lwz placement/register numbers of the fade-alpha load in the vertex writes
// and the fmadds operand order differ.
#include <dolphin/types.h>

#pragma pool_strings off

extern "C" {
void* memcpy(void* dst, const void* src, unsigned long n);
}

typedef f32 Mtx44[4][4];

struct GSgfxVF;


struct GSgfxCol {
    u8 r, g, b, a;
};

struct GSgfxDirty {
    u32 groups;
    u32 words[36];
    u32 textureMask;
    void* textures[8];
};

struct GSgfxBlendSet {
    u8 unk0[0xBC];
};

struct GSgfxMtxEntry {
    u32 flags;
    f32 mtx[3][4];
    f32 invXpose[3][4];
};

struct GSgfxMtxStack {
    u32 unk0;
    GSgfxMtxEntry* top;
};

class GSgfxLayer {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void endSurface();
    void beginSurface(unsigned short num);

    u8 unk0[0xD54];
    u32 projType;
    f32 proj[6];
    u8 unkD70[0x1C];
    u32 cullMode;
    u32 unkD90;
    u8 unkD94[0x1644 - 0xD94];
    u32 blendType;
    u32 blendSrc;
    u32 blendDst;
    u32 blendLogicOp;
    u8 unk1654[2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 dither;
    u8 unk1659[3];
    u8 zEnable;
    u8 unk165D[3];
    u32 zFunc;
    u32 alphaComp0;
    u32 alphaOp;
    u32 alphaComp1;
    u8 alphaRef0;
    u8 alphaRef1;
    u8 alphaCompareOff;
    u8 unk1673[0x11];
    f32 clipNear;
    f32 clipFar;
    u8 unk168C[0x1A];
    u8 unk16A6;
    u8 unk16A7;
    GSgfxDirty dirty[2];
    GSgfxBlendSet blendSets[2];
    GSgfxBlendSet* blendSet;
    s32 blendIndex;
    u32 primType;
    u8 unk199C[4];
    GSgfxMtxStack* mtxStack;
};

#define GFX_DIRTY(l, word, bits, group) \
    (l)->dirty[0].words[word] |= (bits); \
    (l)->dirty[0].groups |= (group);     \
    (l)->dirty[1].words[word] |= (bits); \
    (l)->dirty[1].groups |= (group);


// The write-gather pipe vertex data is sent through.
#define GX_WGPIPE (*(volatile union { u8 u8; s16 s16; f32 f32; }*)0xCC008000)

static inline void GSgfxVertex3f(f32 x, f32 y, f32 z) {
    GX_WGPIPE.f32 = x;
    GX_WGPIPE.f32 = y;
    GX_WGPIPE.f32 = z;
}

static inline void GSgfxColor4u8(u8 r, u8 g, u8 b, u8 a) {
    GX_WGPIPE.u8 = r;
    GX_WGPIPE.u8 = g;
    GX_WGPIPE.u8 = b;
    GX_WGPIPE.u8 = a;
}

extern "C" {
extern f32 mtxIdent[3][4];
int GSgfxLayerFindByID(int id);
GSgfxVF* GSgfxVFGetPredef(s32 id);
f32 GSgfxVideoGetLastRealRenderTime(void);
u8 GSgfxVideoGetVsyncRate(void);
void GSmtx44Ortho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
s32 OSGetResetButtonState(void);
s32 DBIsDebuggerPresent(void);
u32 PADRecalibrate(u32 mask);
void* OSSetIdleFunction(void (*func)(void*), void* param, void* stack, u32 stackSize);
void OSResetSystem(s32 reset, u32 resetCode, s32 forceMenu);
}

void GSgfxShutdown();

static s32 _resetState;
static u8 _resetEnable;
static s32 _resetType;
static u8 (*_resetRenderCBFunc)(void*);
static void* _resetRenderCBArg;
static void (*_resetShutdownCBFunc)();
static s32 _resetFadeAlpha;

static u8 _resetDoFade(void* arg);

void GSgfxResetUpdate() {
    switch (_resetState) {
    case 0:
        if (_resetEnable != 0 && OSGetResetButtonState() == 1) {
            _resetState = 1;
        }
        break;
    case 1:
        if (_resetEnable != 0 && OSGetResetButtonState() == 0) {
            _resetState = 2;
            _resetType = 0;
        }
        break;
    case 2:
        if (_resetRenderCBFunc(_resetRenderCBArg) == 1) {
            _resetState = 3;
        }
        break;
    case 3:
        if (DBIsDebuggerPresent() == 1) {
            _resetState = 0;
            break;
        }
        if (_resetShutdownCBFunc != 0) {
            _resetShutdownCBFunc();
        }
        PADRecalibrate(0xF0000000);
        OSSetIdleFunction(0, 0, 0, 0);
        GSgfxShutdown();
        switch (_resetType) {
        case 0:
            OSResetSystem(0, 0, 0);
            break;
        case 1:
            OSResetSystem(1, 0, 0);
            break;
        case 2:
            OSResetSystem(1, 0, 1);
            break;
        }
        break;
    }
}

extern "C" void GSgfxReset(s32 type) {
    if (_resetState != 0) {
        return;
    }
    _resetType = type;
    _resetState = 2;
}

extern "C" u8 GSgfxResetGetStatus() {
    return _resetEnable;
}

extern "C" u8 GSgfxResetRestore(u8 enable) {
    u8 old = _resetEnable;
    _resetEnable = enable;
    return old;
}

extern "C" u8 GSgfxResetDisable() {
    u8 old = _resetEnable;
    _resetEnable = 0;
    return old;
}

extern "C" u8 GSgfxResetEnable() {
    u8 old = _resetEnable;
    _resetEnable = 1;
    return old;
}

extern "C" void GSgfxResetSetShutdownCallback(void (*cb)()) {
    if (_resetState != 0) {
        return;
    }
    _resetShutdownCBFunc = cb;
}

void GSgfxResetInit() {
    _resetEnable = 0;
    _resetState = 0;
    _resetRenderCBFunc = _resetDoFade;
    _resetRenderCBArg = 0;
    _resetShutdownCBFunc = 0;
}

static u8 _resetDoFade(void* arg) {
    GSgfxLayer* layer = (GSgfxLayer*)GSgfxLayerFindByID(7);
    if (layer == 0) {
        return 1;
    }

 // pixel mode
    layer->colorUpdate = 1;
    layer->alphaUpdate = 0;
    layer->dither = 0;
    GFX_DIRTY(layer, 24, 4, 0x40)

 // orthographic projection
    Mtx44 ortho;
    GSmtx44Ortho(ortho, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    layer->projType = 1;
    layer->proj[0] = ortho[0][0];
    layer->proj[1] = ortho[0][3];
    layer->proj[2] = ortho[1][1];
    layer->proj[3] = ortho[1][3];
    layer->proj[4] = ortho[2][2];
    layer->proj[5] = ortho[2][3];
    GSgfxMtxStack* stack = layer->mtxStack;
    memcpy(stack->top->mtx, mtxIdent, 0x30);
    stack->top->flags |= 1;
    layer->clipNear = 0.0f;
    layer->clipFar = 30000.0f;
    if (layer->unk16A7) {
        if (layer->unk16A6) {
            layer->dirty[0].words[24] |= 0x100;
            layer->dirty[1].words[24] |= 0x100;
        }
        GFX_DIRTY(layer, 24, 0x40, 0x40)
    }
    GFX_DIRTY(layer, 0, 0x20, 1)

 // blend mode
    if (layer->blendIndex != 1) {
        layer->blendIndex = 1;
        layer->blendSet = &layer->blendSets[layer->blendIndex];
    }
    layer->blendType = 1;
    layer->blendSrc = 4;
    layer->blendDst = 5;
    layer->blendLogicOp = 5;
    GFX_DIRTY(layer, 24, 1, 0x40)
 // z compare
    layer->zEnable = 0;
    layer->zFunc = 3;
    GFX_DIRTY(layer, 24, 8, 0x40)
 // alpha compare
    layer->alphaComp0 = 7;
    layer->alphaRef0 = 0;
    layer->alphaOp = 0;
    layer->alphaComp1 = 7;
    layer->alphaRef1 = 0;
    layer->alphaCompareOff = 1;
    GFX_DIRTY(layer, 24, 0x10, 0x40)
 // cull mode
    layer->cullMode = 0;
    GFX_DIRTY(layer, 3, 2, 2)
    layer->unkD90 = 1;
    GFX_DIRTY(layer, 3, 4, 2)

    layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
    layer->primType = 0x98;
    layer->beginSurface(4);

    f32 zero = 0.0f;
    f32 w = 640.0f;
    f32 h = 480.0f;
    GSgfxVertex3f(zero, zero, zero);
    GSgfxColor4u8(0, 0, 0, _resetFadeAlpha);
    GSgfxVertex3f(w, zero, zero);
    GSgfxColor4u8(0, 0, 0, _resetFadeAlpha);
    GSgfxVertex3f(zero, h, zero);
    GSgfxColor4u8(0, 0, 0, _resetFadeAlpha);
    GSgfxVertex3f(w, h, zero);
    GSgfxColor4u8(0, 0, 0, _resetFadeAlpha);
    layer->endSurface();

    if (_resetFadeAlpha == 0xFF) {
        _resetFadeAlpha = 0;
        return 1;
    }
    f32 dt = GSgfxVideoGetLastRealRenderTime();
    _resetFadeAlpha = (s32)(dt * (f32)(256 / GSgfxVideoGetVsyncRate()) + (f32)_resetFadeAlpha);
    if (_resetFadeAlpha > 0xFF) {
        _resetFadeAlpha = 0xFF;
    }
    return 0;
}
