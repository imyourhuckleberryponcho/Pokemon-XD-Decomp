// Menu off-screen layer: captures the back framebuffer into a texture and draws it back with a fade.
#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
// The original wrote this quad through a NON-volatile view of the GX FIFO: the 0.0f/1.0f texcoords stay in
// registers and the u8 alpha is stored without re-narrowing (the volatile GXWGFifo reloads/narrows each write).
#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)

#pragma peephole off

struct GStexture {
    u8 unk0[7];
    u8 dirty; // 0x07
};

struct GSgfxVF;

struct GSgfxLayerViewState {
    u32 flags;
    f32 mtx[3][4];
};

struct GSgfxLayerView {
    u8 unk0[4];
    GSgfxLayerViewState* state; // 0x04
};

// Only the render-state fields this file touches; the inline state setters are written out.
class GSgfxLayer {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

    u8 unk0[0x28];
    s32 renderMode;       // 0x28
    u8 unk2C[0xD54 - 0x2C];
    s32 projType;         // 0xD54
    f32 proj[6];          // 0xD58
    u8 unkD70[0xD8C - 0xD70];
    s32 fogType;          // 0xD8C
    u8 unkD90[0x1644 - 0xD90];
    s32 blendType;        // 0x1644
    s32 blendSrc;         // 0x1648
    s32 blendDst;         // 0x164C
    s32 blendOp;          // 0x1650
    u8 unk1654[2];
    u8 zCompare;          // 0x1656
    u8 zWrite;            // 0x1657
    u8 zFunc;             // 0x1658
    u8 unk1659[3];
    u8 alphaCompare;      // 0x165C
    u8 unk165D[3];
    s32 cullMode;         // 0x1660
    u8 unk1664[0x1684 - 0x1664];
    f32 zNear;            // 0x1684
    f32 zFar;             // 0x1688
    u8 unk168C[0x16A6 - 0x168C];
    u8 zUpdate;           // 0x16A6
    u8 zEnable;           // 0x16A7
    u32 dirty16A8;        // 0x16A8
    u32 dirty16AC;        // 0x16AC
    u8 unk16B0[0x16B8 - 0x16B0];
    u32 dirty16B8;        // 0x16B8
    u8 unk16BC[0x170C - 0x16BC];
    u32 dirty170C;        // 0x170C
    u8 unk1710[0x173C - 0x1710];
    u32 texDirty;         // 0x173C
    GStexture* texture;   // 0x1740
    u8 unk1744[0x1760 - 0x1744];
    u32 dirty1760;        // 0x1760
    u32 dirty1764;        // 0x1764
    u8 unk1768[0x1770 - 0x1768];
    u32 dirty1770;        // 0x1770
    u8 unk1774[0x17C4 - 0x1774];
    u32 dirty17C4;        // 0x17C4
    u8 unk17C8[0x17F4 - 0x17C8];
    u32 texDirty2;        // 0x17F4
    GStexture* texture2;  // 0x17F8
    u8 unk17FC[0x1818 - 0x17FC];
    u8 surfaces[2][0xBC]; // 0x1818
    void* curSurface;     // 0x1990
    s32 curSurfaceIdx;    // 0x1994
    u32 vtxFlags;         // 0x1998
    u8 unk199C[4];
    GSgfxLayerView* view; // 0x19A0
};

typedef bool (*GSgfxBackFBCallback)(GStexture* texture, u32 frame, void* user);

extern "C" {
bool GSgfxBeginBackFBCapture(GStexture* texture, GSgfxBackFBCallback callback, void* user);
GStexture* GStextureCreate(u16 width, u16 height, s32 format, s32 tlutFormat, u8 mipLevels);
void GStextureFree(GStexture* tex);
void GSthreadSwitch(void);
GSgfxLayer* GSgfxLayerFindByID(s32 id);
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
                if (layer->renderMode == 0) {
                    if (layer->curSurfaceIdx != 0) {
                        layer->curSurfaceIdx = 0;
                        layer->curSurface = layer->surfaces[layer->curSurfaceIdx];
                    }
                    layer->blendType = 0;
                    layer->blendSrc = 1;
                    layer->blendDst = 1;
                    layer->blendOp = 5;
                    layer->dirty170C |= 1;
                    layer->dirty16A8 |= 0x40;
                    layer->dirty17C4 |= 1;
                    layer->dirty1760 |= 0x40;
                } else {
                    if (layer->curSurfaceIdx != 1) {
                        layer->curSurfaceIdx = 1;
                        layer->curSurface = layer->surfaces[layer->curSurfaceIdx];
                    }
                    layer->blendType = 1;
                    layer->blendSrc = 1;
                    layer->blendDst = 0;
                    layer->blendOp = 5;
                    layer->dirty170C |= 1;
                    layer->dirty16A8 |= 0x40;
                    layer->dirty17C4 |= 1;
                    layer->dirty1760 |= 0x40;
                }

                GSmtx44Ortho(ortho[0], 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
                layer->projType = 1;
                layer->proj[0] = ortho[0][0];
                layer->proj[1] = ortho[0][3];
                layer->proj[2] = ortho[1][1];
                layer->proj[3] = ortho[1][3];
                layer->proj[4] = ortho[2][2];
                layer->proj[5] = ortho[2][3];
                {
                    GSgfxLayerView* view = layer->view;
                    memcpy(view->state->mtx, mtxIdent, sizeof(view->state->mtx));
                    view->state->flags |= 1;
                }
                layer->zNear = 0.0f;
                layer->zFar = 30000.0f;
                if (layer->zEnable != 0) {
                    if (layer->zUpdate != 0) {
                        layer->dirty170C |= 0x100;
                        layer->dirty17C4 |= 0x100;
                    }
                    layer->dirty170C |= 0x40;
                    layer->dirty16A8 |= 0x40;
                    layer->dirty17C4 |= 0x40;
                    layer->dirty1760 |= 0x40;
                }
                layer->dirty16AC |= 0x20;
                layer->dirty16A8 |= 1;
                layer->dirty1764 |= 0x20;
                layer->dirty1760 |= 1;
                layer->zCompare = 1;
                layer->zWrite = 1;
                layer->zFunc = 0;
                layer->dirty170C |= 4;
                layer->dirty16A8 |= 0x40;
                layer->dirty17C4 |= 4;
                layer->dirty1760 |= 0x40;
                layer->alphaCompare = 0;
                layer->cullMode = 3;
                layer->dirty170C |= 8;
                layer->dirty16A8 |= 0x40;
                layer->dirty17C4 |= 8;
                layer->dirty1760 |= 0x40;
                layer->fogType = 0;
                layer->dirty16B8 |= 2;
                layer->dirty16A8 |= 2;
                layer->dirty1770 |= 2;
                layer->dirty1760 |= 2;
                layer->vtxFlags = 0x98;
                layer->setRenderStateAndSelect(GSgfxVFGetPredef(7));
                {
                    GStexture* tex = _menuOffScreenTex;
                    if (layer->texture != tex || layer->texture2 != tex || tex->dirty != 0) {
                        layer->texture = tex;
                        layer->texDirty |= 1;
                        layer->texture2 = tex;
                        layer->texDirty2 |= 1;
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
