#include <dolphin/types.h>
#include <game/gcptr.h>
#include <dolphin/gx/GXVert.h>
#ifdef __MWERKS__
#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)
#else
#define GXFifoNV GXWGFifo
#endif

#pragma peephole off

struct GStexture {
    u8 unk0[7];
    u8 dirty;
};

struct GSgfxVF;

struct GSgfxLayerViewState {
    u32 flags;
    f32 mtx[3][4];
};

struct GSgfxLayerView {
    u8 unk0[4];
    GSgfxLayerViewState* state;
};

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

};

typedef bool (*GSgfxBackFBCallback)(GStexture* texture, u32 frame, void* user);

extern "C" {
bool GSgfxBeginBackFBCapture(GStexture* texture, GSgfxBackFBCallback callback, void* user);
GStexture* GStextureCreate(u16 width, u16 height, s32 format, s32 tlutFormat, u8 mipLevels);
void GStextureFree(GStexture* tex);
void GSthreadSwitch(void);
GSgfxLayer* GSgfxLayerFindByID(GCsptr id);
GSgfxVF* GSgfxVFGetPredef(s32 id);
f32 GSgfxVideoGetLastRenderTime(void);
u8 GSgfxVideoGetVsyncRate(void);
void GSmtx44Ortho(f32* m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void* memcpy(void* dst, const void* src, u32 n);
extern f32 mtxIdent[3][4];
}

static bool _menuCBOffScreen(GStexture* texture, u32 frame, void* user);

static u8 _menuOffScreenEnable;
static u8 _menuOffScreenUsing;
static u8 _menuOffScreenDisp;
static u8 _menuOffScreenType;
static GStexture* _menuOffScreenTex;
static f32 _menuOffScreenStartRate;
static f32 _menuOffScreenCurrRate;
static f32 _menuOffScreenEndRate;
static f32 _menuOffScreenTime;
static f32 _menuOffScreenCnt;
static u8 _menuOffScreenPrio = 1;
static u8 _onoff = 1;

extern "C" {

void menuOffScreenDraw(void) {
    u8 alpha;
    GSgfxLayer* layer;
    f32 rate;
    f32 ortho[4][4];

    if (_onoff != 0) {
        if (_menuOffScreenType != 0) {
            _menuOffScreenCnt += GSgfxVideoGetLastRenderTime() / (f32)GSgfxVideoGetVsyncRate();
            if (_menuOffScreenCnt >= _menuOffScreenTime) {
                _menuOffScreenCnt = _menuOffScreenTime;
                _menuOffScreenType = 0;
            }
        }
        if (_menuOffScreenDisp != 0 && _menuOffScreenEnable != 0) {
            rate = _menuOffScreenCnt / _menuOffScreenTime * (_menuOffScreenEndRate - _menuOffScreenStartRate) +
                   _menuOffScreenStartRate;
            _menuOffScreenCurrRate = rate;
            alpha = 255.0f - 255.0f * rate / 100.0f;

            layer = GSgfxLayerFindByID(_menuOffScreenPrio ? 7 : 0);
            if (layer != 0) {
                if ((*(s32*)&layer->id) == 0) {
                    if ((*(s32*)&layer->curPass) != 0) {
                        (*(s32*)&layer->curPass) = 0;
                        layer->curFifo = &layer->passes[layer->curPass];
                    }
                    (*(s32*)&layer->hw.blend[0]) = 0;
                    (*(s32*)&layer->hw.blend[1]) = 1;
                    (*(s32*)&layer->hw.blend[2]) = 1;
                    (*(s32*)&layer->hw.blend[3]) = 5;
                    (*(u32*)&layer->dirty[0].pe) |= 1;
                    (*(u32*)&layer->dirty[0].groups) |= 0x40;
                    (*(u32*)&layer->dirty[1].pe) |= 1;
                    (*(u32*)&layer->dirty[1].groups) |= 0x40;
                } else {
                    if ((*(s32*)&layer->curPass) != 1) {
                        (*(s32*)&layer->curPass) = 1;
                        layer->curFifo = &layer->passes[layer->curPass];
                    }
                    (*(s32*)&layer->hw.blend[0]) = 1;
                    (*(s32*)&layer->hw.blend[1]) = 1;
                    (*(s32*)&layer->hw.blend[2]) = 0;
                    (*(s32*)&layer->hw.blend[3]) = 5;
                    (*(u32*)&layer->dirty[0].pe) |= 1;
                    (*(u32*)&layer->dirty[0].groups) |= 0x40;
                    (*(u32*)&layer->dirty[1].pe) |= 1;
                    (*(u32*)&layer->dirty[1].groups) |= 0x40;
                }

                GSmtx44Ortho(ortho[0], 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
                (*(s32*)&layer->hw.projType) = 1;
                ((f32*)layer->hw.proj)[0] = ortho[0][0];
                ((f32*)layer->hw.proj)[1] = ortho[0][3];
                ((f32*)layer->hw.proj)[2] = ortho[1][1];
                ((f32*)layer->hw.proj)[3] = ortho[1][3];
                ((f32*)layer->hw.proj)[4] = ortho[2][2];
                ((f32*)layer->hw.proj)[5] = ortho[2][3];
                {
                    GSgfxLayerView* view = (*(GSgfxLayerView**)&layer->matrixStack);
                    memcpy(view->state->mtx, mtxIdent, sizeof(view->state->mtx));
                    view->state->flags |= 1;
                }
                (*(f32*)&layer->hw.fogNear) = 0.0f;
                (*(f32*)&layer->hw.fogFar) = 30000.0f;
                if ((*(u8*)&layer->hw.fogEnable) != 0) {
                    if ((*(u8*)&layer->hw.fogRangeEnable) != 0) {
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
                (*(u8*)&layer->hw.colorUpdate) = 1;
                (*(u8*)&layer->hw.alphaUpdate) = 1;
                (*(u8*)&layer->hw.zUpdate) = 0;
                (*(u32*)&layer->dirty[0].pe) |= 4;
                (*(u32*)&layer->dirty[0].groups) |= 0x40;
                (*(u32*)&layer->dirty[1].pe) |= 4;
                (*(u32*)&layer->dirty[1].groups) |= 0x40;
                (*(u8*)&layer->hw.zEnable) = 0;
                (*(s32*)&layer->hw.zFunc) = 3;
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
                layer->setRenderStateAndSelect(GSgfxVFGetPredef(7));
                {
                    GStexture* tex = _menuOffScreenTex;
                    if ((*(GStexture**)&layer->dirty[0].tex[0]) != tex || (*(GStexture**)&layer->dirty[1].tex[0]) != tex || tex->dirty != 0) {
                        (*(GStexture**)&layer->dirty[0].tex[0]) = tex;
                        (*(u32*)&layer->dirty[0].texMask) |= 1;
                        (*(GStexture**)&layer->dirty[1].tex[0]) = tex;
                        (*(u32*)&layer->dirty[1].texMask) |= 1;
                    }
                }
                layer->beginSurface(4);
                GXFifoNV.s16 = 0;
                GXFifoNV.s16 = 0;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = 0xFF;
                GXFifoNV.f32 = 0.0f;
                GXFifoNV.f32 = 0.0f;
                GXFifoNV.s16 = 640;
                GXFifoNV.s16 = 0;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = 0xFF;
                GXFifoNV.f32 = 1.0f;
                GXFifoNV.f32 = 0.0f;
                GXFifoNV.s16 = 0;
                GXFifoNV.s16 = 480;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = 0xFF;
                GXFifoNV.f32 = 0.0f;
                GXFifoNV.f32 = 1.0f;
                GXFifoNV.s16 = 640;
                GXFifoNV.s16 = 480;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = alpha;
                GXFifoNV.u8 = 0xFF;
                GXFifoNV.f32 = 1.0f;
                GXFifoNV.f32 = 1.0f;
                layer->endSurface();
            }
        }
    }
}

bool menuOffScreenFadeSync(u8 wait) {
    while (wait) {
        if (_menuOffScreenType == 0) {
            break;
        }
        GSthreadSwitch();
    }
    return _menuOffScreenType != 0;
}

void menuOffScreenFadeSet(f32 target, f32 time) {
    _menuOffScreenType = 1;
    _menuOffScreenStartRate = _menuOffScreenCurrRate;
    _menuOffScreenEndRate = target;
    _menuOffScreenCurrRate = 0.0f;
    _menuOffScreenTime = time;
    _menuOffScreenCnt = 0.0f;
    if (time == 0.0f) {
        _menuOffScreenCnt = _menuOffScreenTime = 1.0f;
    }
}

u8 menuOffScreenSetPriority(u8 val) {
    u8 old = _menuOffScreenPrio;
    _menuOffScreenPrio = val;
    return old;
}

u8 menuOffScreenSetDisp(u8 val) {
    u8 old = _menuOffScreenDisp;
    _menuOffScreenDisp = val;
    return old;
}

u8 menuOffScreenIsDoing(void) {
    return _menuOffScreenUsing;
}

GStexture* menuOffScreenGetPtr(void) {
    return _menuOffScreenTex;
}

u8 menuOffScreenCheckEnable(u8 wait) {
    while (wait) {
        if (_menuOffScreenEnable != 0) {
            break;
        }
        GSthreadSwitch();
    }
    return _menuOffScreenEnable;
}

void menuOffScreenRelease(void) {
    _menuOffScreenType = 0;
    _menuOffScreenUsing = 0;
    _menuOffScreenEnable = 0;
    _menuOffScreenDisp = 0;
    if (_menuOffScreenTex != 0) {
        GStextureFree(_menuOffScreenTex);
        _menuOffScreenTex = 0;
    }
}

u8 menuOffScreenCreate(u8 wait) {
    _menuOffScreenType = 0;
    _menuOffScreenUsing = 1;
    _menuOffScreenEnable = 0;
    _menuOffScreenDisp = 0;
    _menuOffScreenStartRate = 0.0f;
    _menuOffScreenCurrRate = 0.0f;
    _menuOffScreenEndRate = 0.0f;
    _menuOffScreenTime = 0.0f;
    _menuOffScreenCnt = 0.0f;
    if (_menuOffScreenTex == 0) {
        _menuOffScreenTex = GStextureCreate(0, 0, 0x44, 0, 0);
    }
    GSgfxBeginBackFBCapture(_menuOffScreenTex, _menuCBOffScreen, 0);
    return menuOffScreenCheckEnable(wait);
}

void menuOffScreenInit(void) {
    _menuOffScreenUsing = 0;
    _menuOffScreenEnable = 0;
    _menuOffScreenDisp = 0;
    _menuOffScreenPrio = 1;
    _menuOffScreenType = 0;
    _menuOffScreenTime = 0.0f;
    _menuOffScreenCnt = 0.0f;
    _menuOffScreenStartRate = 0.0f;
    _menuOffScreenCurrRate = 0.0f;
    _menuOffScreenEndRate = 0.0f;
}

}

static bool _menuCBOffScreen(GStexture* texture, u32 frame, void* user) {
    _menuOffScreenEnable = 1;
    return false;
}
