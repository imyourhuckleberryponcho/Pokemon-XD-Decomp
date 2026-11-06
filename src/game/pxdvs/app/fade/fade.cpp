#pragma peephole off
#include <dolphin/types.h>
#include <game/gcptr.h>
#include <dolphin/gx/GXVert.h>
#ifdef __MWERKS__
#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)
#else
#define GXFifoNV GXWGFifo
#endif
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

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderStateAndSelect(struct GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

};

struct GSmtx44 {
    f32 m[4][4];
};

extern "C" GSmtx44 mtxIdent;

extern "C" {
void GSmtx44Ortho(f32* mtx, f32, f32, f32, f32, f32, f32);
GSgfxLayer* GSgfxLayerFindByID(GCsint id);
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
    FadeColor white = {255, 255, 255, 255};
    FadeColor black = {0, 0, 0, 255};
    u8 r, g, b;
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
        if (!hook((*(s32*)&layer->id), _fadeWork.pending, _fadeWork.elapsed, _fadeWork.duration,
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
        (*(s32*)&layer->hw.projType) = 1;
        ((f32*)layer->hw.proj)[0] = mtx[0];
        ((f32*)layer->hw.proj)[1] = mtx[3];
        ((f32*)layer->hw.proj)[2] = mtx[5];
        ((f32*)layer->hw.proj)[3] = mtx[7];
        ((f32*)layer->hw.proj)[4] = mtx[10];
        ((f32*)layer->hw.proj)[5] = mtx[11];
        GSlayerCam* cam = (*(GSlayerCam**)&layer->matrixStack);
        memcpy(cam->data + 1, &mtxIdent, 0x30);
        cam->data[0] |= 1;
        (*(f32*)&layer->hw.fogNear) = 0.0f;
        (*(f32*)&layer->hw.fogFar) = 30000.0f;
        if ((*(u8*)&layer->hw.fogEnable)) {
            if ((*(u8*)&layer->hw.fogRangeEnable)) {
                (*(u32*)&layer->dirty[0].pe) |= 0x100;
                (*(u32*)&layer->dirty[1].pe) |= 0x100;
            }
            (*(u32*)&layer->dirty[0].pe) |= 0x40;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 0x40;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
        }
        (*(u32*)&layer->dirty[0].geom) |= 0x20;
        (*(u32*)&layer->dirty[0].groups) |= 1;
        (*(u32*)&layer->dirty[1].geom) |= 0x20;
        (*(u32*)&layer->dirty[1].groups) |= 1;
        if ((*(s32*)&layer->curPass) != 1) {
            (*(s32*)&layer->curPass) = 1;
            layer->curFifo = &layer->passes[layer->curPass];
        }
        (*(s32*)&layer->hw.blend[0]) = 1;
        (*(s32*)&layer->hw.blend[1]) = 4;
        (*(s32*)&layer->hw.blend[2]) = 5;
        (*(s32*)&layer->hw.blend[3]) = 5;
        (*(u32*)&layer->dirty[0].pe) |= 1;
        (*(u32*)&layer->dirty[0].groups) |= 0x40;
        (*(u32*)&layer->dirty[1].pe) |= 1;
        (*(u32*)&layer->dirty[1].groups) |= 0x40;
        (*(u8*)&layer->hw.colorUpdate) = 1;
        (*(u8*)&layer->hw.alphaUpdate) = 1;
        (*(u8*)&layer->hw.zUpdate) = 0;
        (*(u32*)&layer->dirty[0].pe) |= 4;
        (*(u32*)&layer->dirty[0].groups) |= 0x40;
        (*(u32*)&layer->dirty[1].pe) |= 4;
        (*(u32*)&layer->dirty[1].groups) |= 0x40;
        (*(u8*)&layer->hw.zEnable) = 0;
        (*(s32*)&layer->hw.zFunc) = 1;
        (*(u32*)&layer->dirty[0].pe) |= 8;
        (*(u32*)&layer->dirty[0].groups) |= 0x40;
        (*(u32*)&layer->dirty[1].pe) |= 8;
        (*(u32*)&layer->dirty[1].groups) |= 0x40;
        (*(s32*)&layer->hw.cullMode) = 0;
        (*(u32*)&layer->dirty[0].raster) |= 2;
        (*(u32*)&layer->dirty[0].groups) |= 2;
        (*(u32*)&layer->dirty[1].raster) |= 2;
        (*(u32*)&layer->dirty[1].groups) |= 2;
        (*(u32*)&layer->unk1998) = 0x98;
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
void fadeSetToBlackOutIfNotBlack(f32 time) {
    if (_fadeWork.mode != 2) {
        fadeSet(3, time);
    }
}
}

extern "C" {
void fadeSetToBlackInIfBlack(f32 time) {
    if (_fadeWork.mode == 2) {
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

