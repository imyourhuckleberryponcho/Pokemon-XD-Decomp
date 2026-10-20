#pragma peephole off
#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
// Non-volatile view of the GX write-gather FIFO: the original kept constants in
// registers and stored narrowed values without re-narrowing, which the volatile GXWGFifo does not.
#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)
#include <libc/string.h>

struct GSgfxVF;
struct GStexture {
    u8 unk0[7];
    u8 unk7;
};

struct BlendState {
    u8 pad[0xbc];
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};

class GSgfxLayer {
public:
    void setRenderStateAndSelect(struct GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

    u8 pad0[0x28];
    s32 id;
    u8 pad2c[0xd54 - 0x2c];
    s32 projType;
    f32 proj[6];
    u8 pad_d70[0xd8c - 0xd70];
    s32 d8c;
    u8 pad_d90[0x1644 - 0xd90];
    s32 blendOp;
    s32 blendSrc;
    s32 blendDst;
    s32 blendLogic;
    u8 pad_1654[2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 zUpdate;
    u8 pad_1659[3];
    u8 zEnable;
    u8 pad_165d[3];
    s32 zFunc;
    s32 f1664;
    s32 f1668;
    s32 f166c;
    u8 f1670;
    u8 f1671;
    u8 f1672;
    u8 pad_1673[0x1684 - 0x1673];
    f32 nearZ;
    f32 farZ;
    u8 pad_168c[0x16a6 - 0x168c];
    u8 f16a6;
    u8 f16a7;
    u32 dirty16a8;
    u32 dirty16ac;
    u8 pad_16b0[8];
    u32 dirty16b8;
    u8 pad_16bc[0x170c - 0x16bc];
    u32 dirty170c;
    u8 pad_1710[0x173c - 0x1710];
    u32 dirty173c;
    void* tex1740;
    u8 pad_1744[0x1760 - 0x1744];
    u32 dirty1760;
    u32 dirty1764;
    u8 pad_1768[8];
    u32 dirty1770;
    u8 pad_1774[0x17c4 - 0x1774];
    u32 dirty17c4;
    u8 pad_17c8[0x17f4 - 0x17c8];
    u32 dirty17f4;
    void* tex17f8;
    u8 pad_17fc[0x1818 - 0x17fc];
    BlendState blendTable[2];
    BlendState* curBlend;
    s32 curBlendIdx;
    u32 primType;
    u8 pad_199c[0x19a0 - 0x199c];
    GSlayerCam* cam;
};

struct GSmtx44 {
    f32 m[4][4];
};

extern GSmtx44 mtxIdent;

extern "C" {
void GSmtx44Ortho(f32* mtx, f32, f32, f32, f32, f32, f32);
GSgfxLayer* GSgfxLayerFindByID(int id);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef bool (*GSgfxBackFBCallback)(GStexture* texture, u32 frame, void* user);
bool GSgfxBeginBackFBCapture(GStexture* texture, GSgfxBackFBCallback callback, void* user);
GStexture* GStextureCreate(u16 width, u16 height, s32 format, s32 tlutFormat, u8 mipLevels);
void GStextureFree(GStexture* tex);
void* menuOffScreenGetPtr(void);
u8 menuOffScreenIsDoing(void);
void GSthreadSwitch(void);
u8 GSsndPlayNow(u32 id);
u8 GSgfxVideoGetVsyncRate(void);
u32 timeGetLastFrameTime(void);
void fadeEffectInit(void);
s32 GSmemGetCurrentHeap();
s32 GSmemSetAllocMethodHeap(s32 heap, s32 method);
void fadeEffectHookFunction_Doku_Init(void);
}

typedef u8 (*FadeHook)(int layerID, int pending, f32 elapsed, f32 duration, f32 hookElapsed,
                       f32 hookDuration, void* texture);

struct FadeColor {
    u8 r, g, b, a;
};

struct FadeWork {
    u8 mode;
    bool pending;
    u16 type;
    f32 duration;
    f32 elapsed;
    FadeHook hook;
    GStexture* texture;
    f32 hookDuration;
    f32 hookElapsed;
};

static volatile FadeWork _fadeWork;
static u8 _complete;

extern "C" FadeHook fadeSetEX(u16 type, void (*init)(void), bool snapshot, f32 time, f32 hookDuration);
extern "C" void fadeSet(u16 type, f32 time);
static FadeHook fadeSetFunction(void (*init)(void), bool snapshot, u16 type, f32 hookDuration);
static void _fadeSnapshot();
static bool myBackFB(GStexture* texture, u32 frame, void* user);

extern "C" {
void fadeInit(void) {
    _fadeWork.mode = 0;
    _fadeWork.pending = 0;
    _fadeWork.type = 0;
    _fadeWork.duration = 0.0f;
    _fadeWork.elapsed = 0.0f;
    _fadeWork.hook = 0;
    _fadeWork.texture = 0;
    _fadeWork.hookDuration = 0.0f;
    _fadeWork.hookElapsed = 0.0f;
}
}

extern "C" {
void fadeDaemon(void) {
    const FadeColor white = {255, 255, 255, 255};
    const FadeColor black = {0, 0, 0, 255};
    int r, g, b;
    u8 a;
    GSgfxLayer* layer = GSgfxLayerFindByID(7);
    if (layer == 0) {
        return;
    }
    u32 pend = _fadeWork.pending;
    u32 prev = _fadeWork.pending;
    if (pend == 1) {
        switch (_fadeWork.mode) {
        case 0:
        case 4:
            break;
        case 1:
        case 2:
        case 3: {
            f32 fps = (f32)GSgfxVideoGetVsyncRate();
            _fadeWork.elapsed += (f32)timeGetLastFrameTime() / fps;
            if (_fadeWork.elapsed >= _fadeWork.duration) {
                _fadeWork.elapsed = _fadeWork.duration;
                _fadeWork.pending = 0;
                if (_fadeWork.type & 1) {
                    _fadeWork.mode = 2;
                } else {
                    _fadeWork.mode = 0;
                }
            }
            break;
        }
        }
    }
    if (_fadeWork.hook != 0) {
        f32 fps = (f32)GSgfxVideoGetVsyncRate();
        _fadeWork.hookElapsed += (f32)timeGetLastFrameTime() / fps;
        if (_fadeWork.hookElapsed >= _fadeWork.hookDuration) {
            _fadeWork.hookElapsed = _fadeWork.hookDuration;
        }
        void* tex = _fadeWork.texture;
        FadeHook hook = _fadeWork.hook;
        if (!hook(layer->id, _fadeWork.pending, _fadeWork.elapsed, _fadeWork.duration,
                  _fadeWork.hookElapsed, _fadeWork.hookDuration, tex)) {
            _fadeWork.hook = 0;
            if (_fadeWork.texture != 0) {
                if (_fadeWork.texture != menuOffScreenGetPtr()) {
                    GStextureFree(_fadeWork.texture);
                }
                _fadeWork.texture = 0;
            }
        }
    } else if (_fadeWork.type & 0x10) {
        if (prev == 0) {
            _fadeWork.mode = 5;
        }
    }

    switch (_fadeWork.mode) {
    case 0:
    case 3:
    case 4:
        break;
    case 1:
    case 2:
    case 5: {
        f32 progress;
        if (_fadeWork.duration == 0.0f) {
            progress = 1.0f;
        } else {
            progress = _fadeWork.elapsed / _fadeWork.duration;
        }
        if (_fadeWork.type & 1) {
            a = 255.0f * progress;
        } else {
            a = 255 - (s32)(255.0f * progress);
        }
        if (_fadeWork.type & 2) {
            r = black.r;
            g = black.g;
            b = black.b;
        } else {
            r = white.r;
            g = white.g;
            b = white.b;
        }
        if (_fadeWork.mode == 5) {
            r = black.r;
            g = black.g;
            b = black.b;
            a = 255.0f * progress;
        }
        f32 mtx[16];
        GSmtx44Ortho(mtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
        layer->projType = 1;
        layer->proj[0] = mtx[0];
        layer->proj[1] = mtx[3];
        layer->proj[2] = mtx[5];
        layer->proj[3] = mtx[7];
        layer->proj[4] = mtx[10];
        layer->proj[5] = mtx[11];
        GSlayerCam* cam = layer->cam;
        memcpy(cam->data + 1, &mtxIdent, 0x30);
        cam->data[0] |= 1;
        layer->nearZ = 0.0f;
        layer->farZ = 30000.0f;
        if (layer->f16a7) {
            if (layer->f16a6) {
                layer->dirty170c |= 0x100;
                layer->dirty17c4 |= 0x100;
            }
            layer->dirty170c |= 0x40;
            layer->dirty16a8 |= 0x40;
            layer->dirty17c4 |= 0x40;
            layer->dirty1760 |= 0x40;
        }
        layer->dirty16ac |= 0x20;
        layer->dirty16a8 |= 1;
        layer->dirty1764 |= 0x20;
        layer->dirty1760 |= 1;
        if (layer->curBlendIdx != 1) {
            layer->curBlendIdx = 1;
            layer->curBlend = &layer->blendTable[layer->curBlendIdx];
        }
        layer->blendOp = 1;
        layer->blendSrc = 4;
        layer->blendDst = 5;
        layer->blendLogic = 5;
        layer->dirty170c |= 1;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 1;
        layer->dirty1760 |= 0x40;
        layer->colorUpdate = 1;
        layer->alphaUpdate = 1;
        layer->zUpdate = 0;
        layer->dirty170c |= 4;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 4;
        layer->dirty1760 |= 0x40;
        layer->zEnable = 0;
        layer->zFunc = 1;
        layer->dirty170c |= 8;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 8;
        layer->dirty1760 |= 0x40;
        layer->d8c = 0;
        layer->dirty16b8 |= 2;
        layer->dirty16a8 |= 2;
        layer->dirty1770 |= 2;
        layer->dirty1760 |= 2;
        layer->primType = 0x98;
        layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0));
        layer->beginSurface(4);
        {
            f32 zero = 0.0f;
            f32 w = 640.0f;
            f32 h = 480.0f;
            GXFifoNV.f32 = zero;
            GXFifoNV.f32 = zero;
            GXFifoNV.f32 = zero;
            GXFifoNV.u8 = r;
            GXFifoNV.u8 = g;
            GXFifoNV.u8 = b;
            GXFifoNV.u8 = a;
            GXFifoNV.f32 = w;
            GXFifoNV.f32 = zero;
            GXFifoNV.f32 = zero;
            GXFifoNV.u8 = r;
            GXFifoNV.u8 = g;
            GXFifoNV.u8 = b;
            GXFifoNV.u8 = a;
            GXFifoNV.f32 = zero;
            GXFifoNV.f32 = h;
            GXFifoNV.f32 = zero;
            GXFifoNV.u8 = r;
            GXFifoNV.u8 = g;
            GXFifoNV.u8 = b;
            GXFifoNV.u8 = a;
            GXFifoNV.f32 = w;
            GXFifoNV.f32 = h;
            GXFifoNV.f32 = zero;
            GXFifoNV.u8 = r;
            GXFifoNV.u8 = g;
            GXFifoNV.u8 = b;
            GXFifoNV.u8 = a;
        }
        layer->endSurface();
        break;
    }
    }
}
}

static bool myBackFB(GStexture* texture, u32 frame, void* user) {
    _complete = 1;
    return false;
}

static void _fadeSnapshot() {
    GStexture* tex = (GStexture*)_fadeWork.texture;
    _fadeWork.texture = 0;
    if (!menuOffScreenIsDoing()) {
        tex = (GStexture*)menuOffScreenGetPtr();
    }
    if (tex == 0) {
        s32 old = GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(), 3);
        tex = GStextureCreate(0, 0, 0x44, 0, 0);
        GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(), old);
    }
    if (tex != 0) {
        _complete = 0;
        GSgfxBeginBackFBCapture(tex, myBackFB, 0);
        while (_complete == 0) {
            GSthreadSwitch();
        }
        _fadeWork.texture = tex;
    }
}

extern "C" {
void fadeSetFunctionOnly(FadeHook hook) {
    _fadeWork.hook = hook;
}
}

// The original passes the type through a small inline here (found by the permuter): with a plain
// `_fadeWork.type = type;` MWCC masks the parameter in place (r3) instead of into a new register.
static inline u16 _fadeType(u16 type) {
    return type;
}

static FadeHook fadeSetFunction(void (*init)(void), bool snapshot, u16 type, f32 hookDuration) {
    FadeHook prev;
    if (init == 0) {
        return _fadeWork.hook;
    }
    _fadeWork.pending = 1;
    _fadeWork.type = _fadeType(type);
    _fadeWork.hookDuration = hookDuration;
    _fadeWork.hookElapsed = 0.0f;
    _fadeWork.mode = 0;
    prev = _fadeWork.hook;
    _fadeWork.hook = 0;
    if (snapshot == 1) {
        _fadeSnapshot();
    } else if (_fadeWork.texture != 0) {
        if (_fadeWork.texture != menuOffScreenGetPtr()) {
            GStextureFree(_fadeWork.texture);
        }
        _fadeWork.texture = 0;
    }
    fadeEffectInit();
    init();
    return prev;
}

extern "C" {

void fadeSet(u16 type, f32 time) {
    _fadeWork.pending = 1;
    _fadeWork.type = _fadeType(type);
    _fadeWork.duration = time;
    _fadeWork.elapsed = 0.0f;
    if (type & 8) {
        if (type & 1) {
            _fadeWork.mode = 4;
        } else {
            _fadeWork.mode = 3;
        }
    } else {
        if (type & 1) {
            _fadeWork.mode = 2;
        } else {
            _fadeWork.mode = 1;
        }
    }
}
}

extern "C" {
void fadeSetToBlackOutIfNotBlack(void) {
    if (_fadeWork.mode != 2) {
        f32 time;
        fadeSet(3, time);
    }
}
}

extern "C" {
void fadeSetToBlackInIfBlack(void) {
    if (_fadeWork.mode == 2) {
        f32 time;
        fadeSet(2, time);
    }
}
}

extern "C" {
FadeHook fadeSetEX(u16 type, void (*init)(void), bool snapshot, f32 time, f32 hookDuration) {
    FadeHook prev = fadeSetFunction(init, snapshot, type, hookDuration);
    fadeSet(type, time);
    return prev;
}
}

extern "C" {
s8 fadeCheck(bool wait) {
    if (!wait) {
        return _fadeWork.pending;
    }
    volatile FadeWork* work = &_fadeWork;
    while (work->pending == 1) {
        GSthreadSwitch();
    }
    GSthreadSwitch();
    return _fadeWork.pending;
}
}

extern "C" {
u32 fadeGetType(void) {
    return _fadeWork.type;
}
}

extern "C" {
void fadeEffectDokuStart(void) {
    if (_fadeWork.mode == 0) {
        fadeSetEX(9, fadeEffectHookFunction_Doku_Init, 0, 1.0f, 0.5f);
        GSsndPlayNow(0x18);
    }
}
}

extern "C" {
void fadeEffectDokuStop(void) {
    if (_fadeWork.mode == 4) {
        _fadeWork.pending = 0;
        _fadeWork.mode = 0;
    }
}
}

