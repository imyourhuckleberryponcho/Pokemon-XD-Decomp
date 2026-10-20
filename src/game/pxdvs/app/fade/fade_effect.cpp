// STATUS (fadeport): skeleton of the whole unit in asm order. Only the small helpers and the
// *_Init hook installers are real code; every other function is an empty stub (return type guessed).
#pragma pool_strings off
#pragma peephole off
#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
// Non-volatile view of the GX write-gather FIFO: the original kept constants in
// registers and stored narrowed values without re-narrowing, which the volatile GXWGFifo does not.
#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)
#include <dolphin/mtx.h>
#include <libc/string.h>

enum GSgfxLayerID { GS_GFX_LAYER_ID_DUMMY };
enum GSgfxTgenFunc {};
enum GSgfxTgenSrc {};
struct GSmtx;
struct GSgfxVF;
struct GStexture {
    u8 unk0[7];
    u8 unk7;
};
struct GSvec {
    f32 x, y, z;
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
    void tgenFunc(u8 index, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* mtx, bool normalize, GSmtx* post);

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
    GSgfxVF* vf;
    GSlayerCam* cam;
};

struct GSmtx44 {
    f32 m[4][4];
};
extern GSmtx44 mtxIdent;

extern "C" {
void GSmtx44Ortho(f32* mtx, f32, f32, f32, f32, f32, f32);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
GSgfxLayer* GSgfxLayerFindByID(int id);
void GSlerpGetLinearInterpolationVector(GSvec* out, GSvec* a, GSvec* b, f32 t);
u32 timeGetLastFrameTime(void);
void* GSresGetResourceAllGroup(u32 id);
void GSgfxVideoSetLockFrameRate(int);
void fadeFluidInit(u32 columns, u32 rows, f32 cellSize, f32 calcStep, f32 waveLimit, f32 timeStep);
void fadeFluidQuit(void);
void fadeFluidSetShock(GSvec* position, f32 strength);
void fadeFluidSetShockSecond(GSvec* position, f32 strength);
void fadeFluidEvaluate(void);
void fadeFluidEvaluateSecond(void);
void fadeFluidDisp(GStexture* tex, f32 progress, f32 blend);
void fadeFluidDispSecond(int layerID, GStexture* tex, f32 progress, f32 blend);
typedef bool (*GSgfxBackFBCallback)(GStexture* texture, u32 frame, void* user);
bool GSgfxBeginBackFBCapture(GStexture* texture, GSgfxBackFBCallback callback, void* user);
bool GSgfxEndBackFBCapture(GStexture* texture);
}

typedef bool (*FadeHook)(GSgfxLayerID, bool, f32, f32, f32, f32, void*);

extern "C" {
u32 HSD_Rand(void);
void fadeSetFunctionOnly(FadeHook hook);
void GSgfxVFFree(void* vf);
void fadeEffectDokuStop(void);
void GSgfxVFInit(GSgfxVF* vf);
bool GSgfxVFIsUsed(GSgfxVF* vf);
void GSgfxVFCreate(GSgfxVF* vf);
void GSgfxVFSetElement(GSgfxVF* vf, s32, s32, s32, s32);
void GSmemFree(void* ptr);
void* GSmemAllocAlign(u32 size, u32 align);
void GStextureFree(GStexture* tex);
GStexture* GStextureCreate(u16 width, u16 height, s32 format, s32 tlutFormat, u8 mipLevels);
void GStextureSetWrap(GStexture* tex, u32 wrapS, u32 wrapT);
void GStextureSetFilter(GStexture* tex, s32 minFilter, s32 magFilter, u32 mipFilter);
void* GStextureLockImage(GStexture* tex, u8 level);
u32 GStextureUnlockImage(GStexture* tex);
f32 HSD_Randf(void);
}

struct FadeEffectWork {
    GStexture* tex0;
    void* tex1;
    u16 frame;
    u16 unk0A;
    u16 unk0C;
    u16 unk0E;
    f32 step;
    f32 value;
    f32 target;
};

struct FADE_EFFECT_BOUND {
    s16 x;
    s16 y;
    s16 w;
    s16 vx;
    s16 vy;
};

struct FADE_EFFECT_BALL {
    f32 x, y, z;
    f32 w;
    s32 a;
    FADE_EFFECT_BALL() {}
};

extern f32 __float_nan[];

union FadeFloatShape {
    f32 value;
    s32 bits;
};

static inline f32 fadeSqrtf(f32 value) {
    FadeFloatShape shape;
    f64 estimate;
    s32 exponent;
    s32 fpclass;

    if (value > 0.0f) {
        const f64 half = 0.5;
        const f64 three = 3.0;

        estimate = __frsqrte(value);
        estimate = half * estimate * (three - value * (estimate * estimate));
        estimate = half * estimate * (three - value * (estimate * estimate));
        estimate = half * estimate * (three - value * (estimate * estimate));
        return (f32)(value * estimate);
    }
    if ((f64)value < 0.0) {
        return __float_nan[0];
    }

    shape.value = value;
    exponent = shape.bits & 0x7F800000;
    switch (exponent) {
    case 0x7F800000:
        fpclass = (shape.bits & 0x007FFFFF) != 0 ? 1 : 2;
        break;
    case 0:
        fpclass = (shape.bits & 0x007FFFFF) != 0 ? 5 : 3;
        break;
    default:
        fpclass = 4;
        break;
    }
    if (fpclass == 1) {
        return __float_nan[0];
    }
    return value;
}

static inline u32 fadeRandInline(u32 range) {
    u32 lo = HSD_Rand();
    u32 hi = HSD_Rand();
    return ((hi << 16) | lo) % range;
}

#pragma force_active on
static FadeEffectWork _fadeEffectWork;
static FADE_EFFECT_BALL _fadeEffectBall[24];
static u8 _fadeEffectTrainer_vf[0x440];
static u8 _fadeEffectPulse[0xC0];
static u8 _fadeEffectBlock[0x40];
static u8 _fadeEffectLines[0x80];
static FADE_EFFECT_BOUND _fadeEffectBound[16];
struct FadeDistortionWork {
    s32 cols;
    s32 rows;
    s32 width;
    s32 height;
    s16* pos;
    f32* tex;
};
static FadeDistortionWork _fadeDistortionWork;

#pragma force_active reset
struct HexaRibbon {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
};

struct HexaLine {
    f32 x;
    f32 pts[34][2];
    s16 count;
    s16 len;
    u8 dir;
    u8 flag;
};

static HexaLine* _fadeHexaLine[2] = {0, 0};

static u8 _fadeEffectFirstFlag;
static HexaRibbon* _fadeHexaRibbon;
static s32 _fadeHexaRibbonNum;
static GStexture* _fadeHexaTexture;
static GSgfxVF* _fadeHexaNoiseVF;
static f32 _fadeHexaDecayTime;
struct TearOffWork {
    s16 a;
    s16 b;
};
static TearOffWork _fadeTearOffWork;

static bool fadeEffectHookFunction_virtual_hexa_decay(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeVirtualHexaDecayRibbonDraw(GSgfxLayer*, GStexture*, f32);
static void _fadeVirtualHexaDecayNoiseDraw(GSgfxLayer*, GStexture*, f32);
static void _fadeVirtualHexaDecayLineDraw(GSgfxLayer*, f32);
static void _fadeVirtualHexaDecayRibbonUpdate();
static void _fadeVirtualHexaDecayLineUpdate();
static void _fadeVirtualHexaDecayQuit();
static void _fadeVirtualHexaDecayInit();
static bool fadeEffectHookFunction_distortion_strip_yoko(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeDistortionStripDoYoko();
static bool fadeEffectHookFunction_distortion_strip_tate(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeDistortionStripDoTate();
static void _fadeDistortionStripQuit();
static void _fadeDistortionStripInit(int, int);
static bool fadeEffectHookFunction_trainer_second(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeEffectFunction_trainer_second_FirstInit();
static bool fadeEffectHookFunction_tear_off(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeTearOffDraw(GSgfxLayer*, u8, int);
static bool fadeEffectHookFunction_distortion_yoko(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeDistortionDoAverage(u32);
static bool fadeEffectHookFunction_distortion_zoom_out(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool fadeEffectHookFunction_distortion_zoom_in(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool fadeEffectHookFunction_distortion_zoom(GSgfxLayerID, bool, f32, f32, f32, f32, void*, bool);
static void _fadeDistortionDoSecond(u32, bool);
static void _fadeEffectSnapshotRotate(GSgfxLayer*, GStexture*, GSvec*, f32, GSvec*, f32, f32, f32);
static bool fadeEffectHookFunction_distortion(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeDistortionDo(u32);
static void _fadeDistortionQuit();
static void _fadeDistortionInit();
static bool fadeEffectHookFunction_four_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeEffectFourBallInit();
static void _disp_four_ball(GSgfxLayer*, GSvec*, f32, f32, int);
static bool fadeEffectHookFunction_blur_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeBlurBallQuit();
static void _fadeBlurBallInit();
static void _fadeEffectSnapshotTex(GSgfxLayer*, GStexture*, GSvec*, f32, f32, f32, f32, f32, f32, f32, f32);
static void _disp_blur_ball(GSgfxLayer*, GSvec*, f32, f32, int);
static bool fadeEffectHookFunction_dist_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeDistBallQuit();
static void _fadeDistBallInit();
static void _disp_dist_ball(GSgfxLayer*, GSvec*, f32, f32, int);
static bool fadeEffectHookFunction_slide_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeEffectSlideBallInit();
static void _disp_slide_ball(GSgfxLayer*, f32, f32, f32, f32, int);
static bool fadeEffectHookFunction_bound_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeEffectBoundBallInit();
static void _disp_bound_ball(GSgfxLayer*, GSvec*, f32, f32, int);
static bool fadeEffectHookFunction_Doku(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool fadeEffectHookFunction_carde(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool fadeEffectHookFunction_trainer(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeEffectFunction_trainer_FirstInit(GStexture*);
static bool fadeEffectHookFunction_fadein(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool fadeEffectHookFunction_fadeout_in(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool fadeEffectHookFunction_boss_second(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeEffectFunction_boss_FirstInit_second();
static bool fadeEffectHookFunction_boss(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeEffectFunction_boss_FirstInit();
static bool fadeEffectHookFunction_ball_second(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _fadeEffectBallSecondQuit();
static void _fadeEffectBallSecondInit();
static bool fadeEffectHookFunction_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static void _dispball(GSgfxLayer*, GSvec*, f32, f32, int);
static void _fadeEffectFunction_ball_FirstInit();
static bool fadeEffectHookFunction_tate(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool fadeEffectHookFunction_yoko(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool _fadeEffectFunction_UDLR_Main(GSgfxLayer*, bool, f32, f32, f32, f32, GStexture*);
static void _fadeEffectFunction_UDLR_FirstInit(GStexture*, u16);
static bool _myBackFB(GStexture*, u32, void*);
static void _fadeEffectSnapshotFadeFunction(GSgfxLayer*, GStexture*, GSvec*, f32, f32, f32, f32);
static void _fadeEffectMaskFunction(GSgfxLayer*, f32);
static void _fadeEffectEnd(GSgfxLayer*);
static void _fadeEffectStartSprites(GSgfxLayer*);
static void _fadeEffectStartTexture(GSgfxLayer*, GStexture*);
static void _fadeEffect_AdjustParms();
static u32 _fadeEffectGetRandom(u32);

extern "C" void fadeEffectHookFunction_virtual_end_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_virtual_hexa_decay);
}

extern "C" void fadeEffectHookFunction_trainer_second_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_trainer_second);
}

extern "C" void fadeEffectHookFunction_slide_ball_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_slide_ball);
}

extern "C" void fadeEffectHookFunction_four_ball_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_four_ball);
}

extern "C" void fadeEffectHookFunction_distortion_strip_yoko_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_distortion_strip_yoko);
}

extern "C" void fadeEffectHookFunction_distortion_strip_tate_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_distortion_strip_tate);
}

extern "C" void fadeEffectHookFunction_dist_yoko_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_distortion_yoko);
}

extern "C" void fadeEffectHookFunction_dist_zoom_out_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_distortion_zoom_out);
}

extern "C" void fadeEffectHookFunction_dist_zoom_in_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_distortion_zoom_in);
}

extern "C" void fadeEffectHookFunction_blur_ball_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_blur_ball);
}

extern "C" void fadeEffectHookFunction_tear_off_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_tear_off);
}

extern "C" void fadeEffectHookFunction_ball_second_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_ball_second);
}

extern "C" void fadeEffectHookFunction_bound_ball_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_bound_ball);
}

extern "C" void fadeEffectHookFunction_dist_ball_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_dist_ball);
}

extern "C" void fadeEffectHookFunction_boss_second_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_boss_second);
}

extern "C" void fadeEffectHookFunction_distortion_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_distortion);
}

extern "C" void fadeEffectHookFunction_Doku_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_Doku);
}

extern "C" void fadeEffectHookFunction_trainer_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_trainer);
}

extern "C" void fadeEffectHookFunction_fadein_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_fadein);
}

extern "C" void fadeEffectHookFunction_fadeout_in_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_fadeout_in);
}

extern "C" void fadeEffectHookFunction_carde_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_carde);
}

extern "C" void fadeEffectHookFunction_boss_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_boss);
}

extern "C" void fadeEffectHookFunction_yoko_or_tate_or_ball_Init(void) {
    switch (_fadeEffectGetRandom(3)) {
    case 0:
        fadeSetFunctionOnly(fadeEffectHookFunction_yoko);
        break;
    case 1:
        fadeSetFunctionOnly(fadeEffectHookFunction_tate);
        break;
    case 2:
    default:
        fadeSetFunctionOnly(fadeEffectHookFunction_ball);
        break;
    }
}

extern "C" void fadeEffectHookFunction_ball_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_ball);
}

extern "C" void fadeEffectHookFunction_yoko_or_tate_Init(void) {
    switch (_fadeEffectGetRandom(2)) {
    case 0:
        fadeSetFunctionOnly(fadeEffectHookFunction_yoko);
        break;
    case 1:
    default:
        fadeSetFunctionOnly(fadeEffectHookFunction_tate);
        break;
    }
}

extern "C" void fadeEffectHookFunction_tate_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_tate);
}

extern "C" void fadeEffectHookFunction_yoko_Init(void) {
    fadeSetFunctionOnly(fadeEffectHookFunction_yoko);
}

static bool fadeEffectHookFunction_virtual_hexa_decay(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    f32 hp = hookElapsed / hookDuration;
    f32 hp4;
    f32 progress;
    GStexture* t;
    progress = elapsed / duration;
    hp4 = (hp * hp) * (hp * hp);
    _fadeEffectMaskFunction(layer, 0.0f);
    if (tex == 0) {
        return pending;
    }
    t = (GStexture*)tex;
    if (_fadeEffectFirstFlag == 1) {
        GSgfxVideoSetLockFrameRate(1);
        _fadeEffectFirstFlag = 0;
        _fadeEffectWork.unk0C = fadeRandInline(2) != 0 ? 1 : 0;
        _fadeEffectWork.frame = 0;
        _fadeVirtualHexaDecayInit();
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        _fadeVirtualHexaDecayQuit();
        GSgfxEndBackFBCapture(t);
        return pending;
    }
    if (timeGetLastFrameTime() != 0) {
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
    }
    f32 k;
    if (progress <= 0.4f) {
        k = 0.0f;
    } else {
        k = 1.6666666f * (progress - 0.4f);
    }
    f32 inv = (1.0f - k) * (1.0f - hp4);
    f32 level = 1.0f - inv;
    if (level < 0.00001f) {
        level = 0.0f;
    } else if (level > 1.0f) {
        level = 1.0f;
    }
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, level, 0.0f);
    f32 off = 6.0f * hp;
    c.x = 320.0f - off;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, level, 0.5f);
    c.x = 320.0f + off;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, level, 0.666f);
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        _fadeVirtualHexaDecayRibbonUpdate();
        _fadeVirtualHexaDecayLineUpdate();
    }
    _fadeVirtualHexaDecayNoiseDraw(layer, t, 0.2f * (inv * hp));
    _fadeVirtualHexaDecayRibbonDraw(layer, t, inv * (1.8333334f + (0.16666667f * inv * inv - inv)));
    _fadeVirtualHexaDecayLineDraw(layer, inv);
    _fadeHexaDecayTime = hp;
    return pending;
}

static void _fadeVirtualHexaDecayRibbonDraw(GSgfxLayer* layer, GStexture* t, f32 alphaf) {
    int a = (s32)(255.0f * alphaf);
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->primType = 0x80;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 1, 1, 4));
    if (layer->tex1740 != t || layer->tex17f8 != t || t->unk7 != 0) {
        layer->tex1740 = t;
        layer->dirty173c |= 1;
        layer->tex17f8 = t;
        layer->dirty17f4 |= 1;
    }
    if (_fadeHexaRibbonNum > 0) {
        layer->beginSurface((u16)(_fadeHexaRibbonNum * 4));
        HexaRibbon* r = _fadeHexaRibbon;
        int n = _fadeHexaRibbonNum;
        int i;
        for (i = 0; i < n; i++, r++) {
            s16 x0 = r->a;
            s16 y0 = r->b;
            f32 u0 = (f32)(x0 + 21) / 640.0f;
            s16 y1 = y0 + r->d;
            s16 x1 = x0 + r->c;
            f32 v0 = (f32)y0 / 480.0f;
            f32 u1 = (f32)(x1 - 19) / 640.0f;
            f32 v1 = (f32)y1 / 480.0f;
            GXPosition2s16(x0, y0);
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = 0xFF;
            GXPosition2f32(u0, v0);
            GXPosition2s16(x1, y0);
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = 0xFF;
            GXPosition2f32(u1, v0);
            GXPosition2s16(x1, y1);
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = 0xFF;
            GXPosition2f32(u1, v1);
            GXPosition2s16(x0, y1);
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = a;
            GXWGFifo.u8 = 0xFF;
            GXPosition2f32(u0, v1);
        }
        layer->endSurface();
    }
}

static void _fadeVirtualHexaDecayNoiseDraw(GSgfxLayer* layer, GStexture* t, f32 alphaf) {
    if (_fadeHexaTexture != 0 && t != 0) {
        u8 a;
        a = 255.0f * alphaf;
        layer->setRenderStateAndSelect(_fadeHexaNoiseVF);
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
        layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
        layer->tgenFunc(1, (GSgfxTgenFunc)1, (GSgfxTgenSrc)5, 0, false, 0);
    *(u8*)((u8*)layer + 0xeac) = 2;
    *(u32*)((u8*)layer + 0x16cc) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1784) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
        if (layer->tex1740 != t || layer->tex17f8 != t || t->unk7 != 0) {
            layer->tex1740 = t;
            layer->dirty173c |= 1;
            layer->tex17f8 = t;
            layer->dirty17f4 |= 1;
        }
    *(u32*)((u8*)layer + 0xeb0) = 0;
    *(u32*)((u8*)layer + 0xeb4) = 0;
    *(u32*)((u8*)layer + 0xeb8) = 4;
    *(u32*)((u8*)layer + 0x16d0) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1788) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1170) = 0;
    *(u32*)((u8*)layer + 0x1174) = 0;
    *(u32*)((u8*)layer + 0x1178) = 0;
    *(u8*)((u8*)layer + 0x117c) = 0;
    *(u32*)((u8*)layer + 0x1180) = 1;
    *(u32*)((u8*)layer + 0x16dc) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1794) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0xf70) = 15;
    *(u32*)((u8*)layer + 0xf74) = 8;
    *(u32*)((u8*)layer + 0xf78) = 10;
    *(u32*)((u8*)layer + 0xf7c) = 15;
    *(u32*)((u8*)layer + 0x16d4) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x178c) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x12b0) = 0;
    *(u32*)((u8*)layer + 0x12b4) = 0;
    *(u32*)((u8*)layer + 0x12b8) = 0;
    *(u8*)((u8*)layer + 0x12bc) = 0;
    *(u32*)((u8*)layer + 0x12c0) = 1;
    *(u32*)((u8*)layer + 0x16e0) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1798) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1070) = 7;
    *(u32*)((u8*)layer + 0x1074) = 4;
    *(u32*)((u8*)layer + 0x1078) = 5;
    *(u32*)((u8*)layer + 0x107c) = 7;
    *(u32*)((u8*)layer + 0x16d8) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1790) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    GStexture* t = _fadeHexaTexture;
        if (*(void**)((u8*)layer + 0x1744) != t || *(void**)((u8*)layer + 0x17fc) != t || t->unk7 != 0) {
            *(void**)((u8*)layer + 0x1744) = t;
            layer->dirty173c |= 2;
            *(void**)((u8*)layer + 0x17fc) = t;
            layer->dirty17f4 |= 2;
        }
    *(u32*)((u8*)layer + 0xebc) = 1;
    *(u32*)((u8*)layer + 0xec0) = 1;
    *(u32*)((u8*)layer + 0xec4) = 4;
    *(u32*)((u8*)layer + 0x16d0) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1788) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1184) = 0;
    *(u32*)((u8*)layer + 0x1188) = 0;
    *(u32*)((u8*)layer + 0x118c) = 0;
    *(u8*)((u8*)layer + 0x1190) = 0;
    *(u32*)((u8*)layer + 0x1194) = 0;
    *(u32*)((u8*)layer + 0x16dc) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1794) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0xf80) = 15;
    *(u32*)((u8*)layer + 0xf84) = 8;
    *(u32*)((u8*)layer + 0xf88) = 2;
    *(u32*)((u8*)layer + 0xf8c) = 15;
    *(u32*)((u8*)layer + 0x16d4) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x178c) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x12c4) = 0;
    *(u32*)((u8*)layer + 0x12c8) = 0;
    *(u32*)((u8*)layer + 0x12cc) = 0;
    *(u8*)((u8*)layer + 0x12d0) = 0;
    *(u32*)((u8*)layer + 0x12d4) = 0;
    *(u32*)((u8*)layer + 0x16e0) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1798) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1080) = 7;
    *(u32*)((u8*)layer + 0x1084) = 7;
    *(u32*)((u8*)layer + 0x1088) = 7;
    *(u32*)((u8*)layer + 0x108c) = 1;
    *(u32*)((u8*)layer + 0x16d8) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1790) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
        layer->vf = _fadeHexaNoiseVF;
        layer->primType = 0x98;
        layer->beginSurface(4);
        f32 zero = 0.0f;
        f32 w = 641.0f;
        f32 one = 1.0f;
        f32 h = 481.0f;
        f32 k = 15.0f;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = zero;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = a;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = w;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = zero;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = a;
        GXFifoNV.f32 = one;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = one;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = h;
        GXFifoNV.f32 = zero;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = a;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = one;
        GXFifoNV.f32 = zero;
        GXFifoNV.f32 = k;
        GXFifoNV.f32 = w;
        GXFifoNV.f32 = h;
        GXFifoNV.f32 = zero;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = a;
        GXFifoNV.f32 = one;
        GXFifoNV.f32 = one;
        GXFifoNV.f32 = one;
        GXFifoNV.f32 = k;
        layer->endSurface();
    }
}

static void _fadeVirtualHexaDecayLineDraw(GSgfxLayer* layer, f32 alphaf) {
    if (alphaf < 0.00001f) {
        return;
    }
    {
        int a = (s32)(255.0f * alphaf);
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
        layer->f1664 = 7;
        layer->f1670 = 0;
        layer->f1668 = 0;
        layer->f166c = 7;
        layer->f1671 = 0;
        layer->f1672 = 1;
        layer->dirty170c |= 0x10;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 0x10;
        layer->dirty1760 |= 0x40;
        layer->d8c = 0;
        layer->dirty16b8 |= 2;
        layer->dirty16a8 |= 2;
        layer->dirty1770 |= 2;
        layer->dirty1760 |= 2;
        layer->primType = 0xB0;
        layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
        u8 cr[3] = {50, 200, 0};
        u8 cg[3] = {60, 240, 0};
        u8 cb[3] = {255, 255, 0};
        *(u8*)((u8*)layer + 0xd34) = 6;
        *(u32*)((u8*)layer + 0xd38) = 0;
        layer->dirty16ac |= 4;
        layer->dirty16a8 |= 1;
        layer->dirty1764 |= 4;
        layer->dirty1760 |= 1;
        int side;
        int i;
        int j;
        for (side = 0; side < 2; side++) {
            for (i = 0; i < 19; i++) {
                HexaLine* e = &_fadeHexaLine[side][i];
                int count = e->count;
                if (count >= 2) {
                    int half = count / 2;
                    layer->beginSurface((u16)count);
                    f32* p = (f32*)e;
                    for (j = 0; j < (u8)count; j++) {
                        int k;
                        if (j == half) {
                            k = 1;
                        } else if (j < count - 1) {
                            k = 0;
                        } else {
                            k = 2;
                        }
                        f32 px = p[1];
                        f32 py = p[2];
                        p += 2;
                        GXWGFifo.s16 = px;
                        GXWGFifo.s16 = py;
                        GXWGFifo.u8 = a;
                        GXWGFifo.u8 = cr[k];
                        GXWGFifo.u8 = cg[k];
                        GXWGFifo.u8 = cb[k];
                    }
                    layer->endSurface();
                }
            }
        }
        *(u8*)((u8*)layer + 0xd34) = 6;
        *(u32*)((u8*)layer + 0xd38) = 0;
        layer->dirty16ac |= 4;
        layer->dirty16a8 |= 1;
        layer->dirty1764 |= 4;
        layer->dirty1760 |= 1;
    }
}

static void _fadeVirtualHexaDecayRibbonUpdate() {
    int i;
    for (i = 0; i < _fadeHexaRibbonNum; i++) {
        HexaRibbon* q = &_fadeHexaRibbon[i];
        q->b += 1;
        q->c += 2;
    }
    if (_fadeHexaRibbonNum < 16 && _fadeEffectWork.frame % 5 == 0) {
        HexaRibbon* r = &_fadeHexaRibbon[_fadeHexaRibbonNum];
        r->a = 0;
        r->b = fadeRandInline(421) + 30;
        r->c = 640;
        r->d = 10;
        _fadeHexaRibbonNum++;
    }
}

static void _fadeVirtualHexaDecayLineUpdate() {
    int side;
    int i;
    for (side = 0; side < 2; side++) {
        int sgn = side == 0 ? 1 : -1;
        f32 side2 = 0.5f * (f32)sgn;
        for (i = 0; i < 19; i++) {
            HexaLine* e = &_fadeHexaLine[side][i];
            if (e->count < 34) {
                e->len = (f32)e->len + e->x;
                int l = e->len;
                l = l < 20 ? l : 20;
                f32 fl = (f32)l;
                f32* prev = e->pts[e->count - 2];
                f32* next = e->pts[e->count - 1];
                switch (e->dir) {
                case 0:
                    next[1] = (f32)sgn * fl + prev[1];
                    break;
                case 1:
                    f32 kc717 = 0.8660254f;
                    next[0] = fl * kc717 + prev[0];
                    next[1] = fl * side2 + prev[1];
                    break;
                case 2:
                    next[0] = prev[0] - 0.8660254f * fl;
                    next[1] = fl * side2 + prev[1];
                    break;
                }
            }
            while (e->len > 20 && e->count < 34) {
                e->count++;
                e->len -= 20;
                e->dir = e->dir == 0 ? fadeRandInline(2) + 1 : 0;
                f32 fl = (f32)e->len;
                f32* prev = e->pts[e->count - 2];
                f32* next = e->pts[e->count - 1];
                switch (e->dir) {
                case 0:
                    next[0] = prev[0];
                    next[1] = (f32)sgn * fl + prev[1];
                    break;
                case 1:
                    next[0] = 0.8660254f * fl + prev[0];
                    next[1] = fl * side2 + prev[1];
                    break;
                case 2:
                    next[0] = prev[0] - 0.8660254f * fl;
                    next[1] = fl * side2 + prev[1];
                    break;
                }
            }
            if (e->x < 9.0f) {
                e->x += 0.2f;
            }
        }
    }
}

static void _fadeVirtualHexaDecayQuit() {
    GSmemFree(_fadeHexaLine[0]);
    _fadeHexaLine[0] = 0;
    GSmemFree(_fadeHexaLine[1]);
    _fadeHexaLine[1] = 0;
    if (_fadeHexaRibbon != 0) {
        GSmemFree(_fadeHexaRibbon);
        _fadeHexaRibbon = 0;
    }
    _fadeHexaRibbonNum = 0;
    if (_fadeHexaTexture != 0) {
        GStextureFree(_fadeHexaTexture);
        _fadeHexaTexture = 0;
    }
    if (_fadeHexaNoiseVF != 0) {
        GSmemFree(_fadeHexaNoiseVF);
        _fadeHexaNoiseVF = 0;
    }
}

static void _fadeVirtualHexaDecayInit() {
    _fadeHexaLine[0] = (HexaLine*)GSmemAllocAlign(0x1514, 0x20);
    _fadeHexaLine[1] = (HexaLine*)GSmemAllocAlign(0x1514, 0x20);
    int side;
    int i;
    for (side = 0; side < 2; side++) {
        s16 base = side == 0 ? 0 : 490;
        f32 ofs = side == 0 ? 0.0f : 17.320507f;
        for (i = 0; i < 19; i++) {
            HexaLine* e = &_fadeHexaLine[side][i];
            e->x = 4.4f * HSD_Randf() + 0.1f;
            e->count = 2;
            e->pts[0][0] = 34.641014f * (f32)i + ofs;
            e->pts[0][1] = (f32)base;
            e->pts[1][0] = e->pts[0][0];
            e->pts[1][1] = e->pts[0][1];
            e->dir = fadeRandInline(2) + 1;
            e->len = 0;
            e->flag = 1;
        }
    }
    _fadeHexaRibbon = (HexaRibbon*)GSmemAllocAlign(0x80, 0x20);
    _fadeHexaRibbonNum = 0;
    _fadeHexaDecayTime = 0.0f;
    _fadeHexaTexture = GStextureCreate(8, 8, 0x40, 0, 0);
    _fadeHexaNoiseVF = (GSgfxVF*)GSmemAllocAlign(0x440, 0x20);
    if (_fadeHexaTexture != 0) {
        GStextureSetWrap(_fadeHexaTexture, 1, 1);
        GStextureSetFilter(_fadeHexaTexture, 1, 1, 1);
        u16* img = (u16*)GStextureLockImage(_fadeHexaTexture, 0);
        for (i = 0; i < 16; i++) {
            *img++ = (i / 2) % 2 == 0 ? 0xFFFF : 0x2222;
        }
        GStextureUnlockImage(_fadeHexaTexture);
    }
    if (_fadeHexaNoiseVF != 0) {
        GSgfxVFInit(_fadeHexaNoiseVF);
        GSgfxVFCreate(_fadeHexaNoiseVF);
        GSgfxVFSetElement(_fadeHexaNoiseVF, 9, 1, 4, 0);
        GSgfxVFSetElement(_fadeHexaNoiseVF, 11, 1, 5, 0);
        GSgfxVFSetElement(_fadeHexaNoiseVF, 13, 1, 4, 0);
        GSgfxVFSetElement(_fadeHexaNoiseVF, 14, 1, 4, 0);
    }
}

static bool fadeEffectHookFunction_distortion_strip_yoko(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        GSgfxVideoSetLockFrameRate(1);
        _fadeDistortionStripInit(2, 240);
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        _fadeDistortionStripQuit();
        GSgfxEndBackFBCapture(t);
        return pending;
    }
    f32 progress = elapsed / duration;
    _fadeEffectMaskFunction(layer, progress);
    if (timeGetLastFrameTime() != 0) {
        if (progress < 0.00001f) {
            _fadeDistortionStripDoYoko();
        }
        _fadeEffectWork.frame++;
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    layer->primType = 0x98;
    if (layer->tex1740 != t || layer->tex17f8 != t || t->unk7 != 0) {
        layer->tex1740 = t;
        layer->dirty173c |= 1;
        layer->tex17f8 = t;
        layer->dirty17f4 |= 1;
    }
    int cols = _fadeDistortionWork.cols;
    int rows = _fadeDistortionWork.rows;
    s16* pos = _fadeDistortionWork.pos;
    f32* tp = _fadeDistortionWork.tex;
    if (pos == 0 || tp == 0) {
        return false;
    }
    f32 fade;
    if (progress < 0.00001f) {
        f32 kc3557 = 1.0f;
        fade = kc3557 - progress;
    } else {
        f32 kc3631 = 1.0f;
        fade = kc3631 - fadeSqrtf(progress);
    }
    f32 kc3709 = 255.0f;
    f32 fa = kc3709 * fade;
    u8 flag = _fadeEffectWork.unk0C % 2 == 0 ? 1 : 0;
    int alphaA;
    int alphaB;
    if (flag) {
        alphaA = (s32)fa;
        f32 kc3890 = 1.0f;
        alphaB = (s32)(fa * kc3890);
    } else {
        alphaB = (s32)fa;
        f32 kc3993 = 1.0f;
        alphaA = (s32)(fa * kc3993);
    }
    int y;
    int x;
    for (y = 1; y < cols; y++) {
        layer->beginSurface((u16)(rows * 2));
        int idx = 0;
        for (x = 0; x < rows; x++) {
            int a = idx;
            a += y;
            GXPosition3s16(pos[a * 2], pos[a * 2 + 1], 0);
            GXColor4u8(0xFF, 0xFF, 0xFF, alphaA);
            GXPosition2f32(flag ? tp[a * 2] : 1.0f, tp[a * 2 + 1]);
            int b = y;
            b += idx - 1;
            GXPosition3s16(pos[b * 2], pos[b * 2 + 1], 0);
            GXColor4u8(0xFF, 0xFF, 0xFF, alphaB);
            GXPosition2f32(flag ? 0.0f : tp[b * 2], tp[b * 2 + 1]);
            idx += cols;
        }
        layer->endSurface();
    }
    return pending;
}

static void _fadeDistortionStripDoYoko() {
    enum TsE { TsE0 };
    s16* p;
    int cols = _fadeDistortionWork.cols;
    int rows = _fadeDistortionWork.rows;
    s16* pos = _fadeDistortionWork.pos;
    f32* tex = _fadeDistortionWork.tex;
    if (pos == 0 || tex == 0) {
        return;
    }
    {
        u16 mode = _fadeEffectWork.unk0C;
        enum TsE dir = (enum TsE)(mode < 2 ? 1 : 0);
        s16 speed = mode % 2 == 0 ? 5 : -5;
        volatile f32 width = (f32)_fadeDistortionWork.width;
        f32 height = (f32)_fadeDistortionWork.height;
        f32 jitter = 0.5f / height;
        int y;
        int x;
        for (y = 0; y < rows; y++) {
            int odd = y % 2;
            p = pos;
            f32* t = tex;
            for (x = 0; x < cols; x++) {
                if (dir) {
                    if (odd == 0) {
                        if (p[1] < _fadeEffectWork.frame * 18) {
                            p[0] = p[0] + speed;
                        }
                    } else {
                        if (p[1] < _fadeEffectWork.frame * 27) {
                            p[0] = p[0] + speed;
                        }
                    }
                } else {
                    if (odd == 0) {
                        if (p[1] > 480 - _fadeEffectWork.frame * 18) {
                            p[0] = p[0] + speed;
                        }
                    } else {
                        if (p[1] > 480 - _fadeEffectWork.frame * 27) {
                            p[0] = p[0] + speed;
                        }
                    }
                }
                t[0] = (f32)p[0] / width;
                u32 s = fadeRandInline(2) != 0 ? -1 : 1;
                t[1] = (f32)p[1] / height + jitter * (f32)s;
                p = p + 2;
                pos = pos + 2;
                tex = tex + 2;
                t = t + 2;
            }
        }
    }
}

static bool fadeEffectHookFunction_distortion_strip_tate(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        GSgfxVideoSetLockFrameRate(1);
        _fadeDistortionStripInit(320, 2);
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        _fadeDistortionStripQuit();
        GSgfxEndBackFBCapture(t);
        return pending;
    }
    f32 progress = elapsed / duration;
    _fadeEffectMaskFunction(layer, progress);
    if (timeGetLastFrameTime() != 0) {
        if (progress < 0.00001f) {
            _fadeDistortionStripDoTate();
        }
        _fadeEffectWork.frame++;
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    layer->primType = 0x98;
    if (layer->tex1740 != t || layer->tex17f8 != t || t->unk7 != 0) {
        layer->tex1740 = t;
        layer->dirty173c |= 1;
        layer->tex17f8 = t;
        layer->dirty17f4 |= 1;
    }
    int cols = _fadeDistortionWork.cols;
    int rows = _fadeDistortionWork.rows;
    s16* pos = _fadeDistortionWork.pos;
    f32* tp = _fadeDistortionWork.tex;
    if (pos == 0 || tp == 0) {
        return false;
    }
    f32 fade;
    if (progress < 0.00001f) {
        f32 kc3557 = 1.0f;
        fade = kc3557 - progress;
    } else {
        f32 kc3631 = 1.0f;
        fade = kc3631 - fadeSqrtf(progress);
    }
    f32 kc3709 = 255.0f;
    f32 fa = kc3709 * fade;
    u8 flag = _fadeEffectWork.unk0C < 2 ? 1 : 0;
    int alphaA;
    int alphaB;
    if (flag) {
        alphaA = (s32)fa;
        f32 kc3885 = 1.0f;
        alphaB = (s32)(fa * kc3885);
    } else {
        alphaB = (s32)fa;
        f32 kc3988 = 1.0f;
        alphaA = (s32)(fa * kc3988);
    }
    int y;
    int x;
    for (y = 1; y < rows; y++) {
        layer->beginSurface((u16)(cols * 2));
        for (x = 0; x < cols; x++) {
            int a = y * cols + x;
            int b = (y - 1) * cols + x;
            GXPosition3s16(pos[a * 2], pos[a * 2 + 1], 0);
            GXColor4u8(0xFF, 0xFF, 0xFF, alphaA);
            GXPosition2f32(tp[a * 2], flag ? tp[a * 2 + 1] : 1.0f);
            GXPosition3s16(pos[b * 2], pos[b * 2 + 1], 0);
            GXColor4u8(0xFF, 0xFF, 0xFF, alphaB);
            GXPosition2f32(tp[b * 2], flag ? 0.0f : tp[b * 2 + 1]);
        }
        layer->endSurface();
    }
    return pending;
}

static void _fadeDistortionStripDoTate() {
    s16* p;
    int rows = _fadeDistortionWork.rows;
    s16* pos = _fadeDistortionWork.pos;
    f32* tex = _fadeDistortionWork.tex;
    int cols = _fadeDistortionWork.cols;
    if (pos == 0 || tex == 0) {
        return;
    }
    u16 mode = _fadeEffectWork.unk0C;
    u32 dir = mode % 2 == 0 ? 1 : 0;
    s16 speed = mode < 2 ? 5 : -5;
    f32 width = (f32)_fadeDistortionWork.width;
    f32 height = (f32)_fadeDistortionWork.height;
    f32 jitter = 0.5f / width;
    int y;
    int x;
    for (y = 0; y < rows; y++) {
        p = pos;
        f32* t = tex;
        for (x = 0; x < cols; x++) {
            if (dir) {
                if (x % 2 == 0) {
                    if (p[0] < _fadeEffectWork.frame * 16) {
                        p[1] = p[1] + speed;
                    }
                } else {
                    if (p[0] < _fadeEffectWork.frame * 24) {
                        p[1] = p[1] + speed;
                    }
                }
            } else {
                if (x % 2 == 0) {
                    if (p[0] > 640 - _fadeEffectWork.frame * 16) {
                        p[1] = p[1] + speed;
                    }
                } else {
                    if (p[0] > 640 - _fadeEffectWork.frame * 24) {
                        p[1] = p[1] + speed;
                    }
                }
            }
            s32 s = fadeRandInline(2) != 0 ? -1 : 1;
            t[0] = (f32)p[0] / width + jitter * (f32)s;
            t[1] = (f32)p[1] / height;
            p = p + 2;
            pos = pos + 2;
            tex = tex + 2;
            t = t + 2;
        }
    }
}

static void _fadeDistortionStripQuit() {
    if (_fadeDistortionWork.pos != 0) {
        GSmemFree(_fadeDistortionWork.pos);
        _fadeDistortionWork.pos = 0;
    }
    if (_fadeDistortionWork.tex != 0) {
        GSmemFree(_fadeDistortionWork.tex);
        _fadeDistortionWork.tex = 0;
    }
}

static void _fadeDistortionStripInit(int cols, int rows) {
    f32 v;
    int n = cols * rows;
    _fadeDistortionWork.cols = cols;
    _fadeDistortionWork.rows = rows;
    _fadeDistortionWork.width = 640;
    _fadeDistortionWork.height = 480;
    _fadeDistortionWork.pos = (s16*)GSmemAllocAlign(n * 4, 0x20);
    _fadeDistortionWork.tex = (f32*)GSmemAllocAlign(n * 8, 0x20);
    s16* pos = _fadeDistortionWork.pos;
    f32* tex = _fadeDistortionWork.tex;
    f32 stepX = 640.0f / (f32)(cols - 1);
    f32 stepY = 480.0f / (f32)(rows - 1);
    f32 invX = 1.0f / (f32)(cols - 1);
    f32 invY = 1.0f / (f32)(rows - 1);
    if (pos != 0 && tex != 0) {
        int y;
        int x;
        for (y = 0; y < rows; y++) {
            s16* p = pos;
            f32* t = tex;
            int py = (s32)(stepY * (f32)y);
            v = invY * (f32)y;
            for (x = 0; x < cols; x++) {
                p[0] = (stepX * (f32)x);
                p[1] = py;
                if (x == cols - 1 && rows > 2) {
                    p[0] += 1;
                } else if (y == rows - 1 && cols > 2) {
                    p[1] += 1;
                }
                t[0] = invX * (f32)x;
                t[1] = v;
                p += 2;
                pos += 2;
                t += 2;
                tex += 2;
            }
        }
        _fadeEffectWork.unk0C = fadeRandInline(4);
        _fadeEffectWork.unk0E = 0;
        _fadeEffectWork.frame = 0;
    }
}

static bool fadeEffectHookFunction_trainer_second(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    Mtx m;
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_trainer_second_FirstInit();
        _fadeEffectWork.unk0E = 255;
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        GSgfxVFFree(_fadeEffectTrainer_vf);
        GSgfxEndBackFBCapture(t);
        return pending;
    }
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        _fadeEffectWork.value += _fadeEffectWork.step;
        if (_fadeEffectWork.step >= 0.0f) {
            _fadeEffectWork.step += 1.5f * progress;
            if (_fadeEffectWork.value >= _fadeEffectWork.target) {
                _fadeEffectWork.value = _fadeEffectWork.target;
            }
        } else {
            _fadeEffectWork.step -= 1.5f * progress;
            if (_fadeEffectWork.value <= _fadeEffectWork.target) {
                _fadeEffectWork.value = _fadeEffectWork.target;
            }
        }
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
    }
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    f32 value = _fadeEffectWork.value;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, 0.0f);
    c.x = 320.0f + value;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, 0.5f);
    if (GSgfxVFIsUsed((GSgfxVF*)_fadeEffectTrainer_vf)) {
        layer->setRenderStateAndSelect((GSgfxVF*)_fadeEffectTrainer_vf);
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
        layer->f1664 = 7;
        layer->f1670 = 0;
        layer->f1668 = 0;
        layer->f166c = 7;
        layer->f1671 = 0;
        layer->f1672 = 1;
        layer->dirty170c |= 0x10;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 0x10;
        layer->dirty1760 |= 0x40;
        layer->d8c = 0;
        layer->dirty16b8 |= 2;
        layer->dirty16a8 |= 2;
        layer->dirty1770 |= 2;
        layer->dirty1760 |= 2;
    
        layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
        layer->tgenFunc(1, (GSgfxTgenFunc)1, (GSgfxTgenSrc)5, 0, false, 0);
        *(u8*)((u8*)layer + 0xeac) = 3;

        GStexture* t0 = (GStexture*)_fadeEffectWork.tex0;
        if (layer->tex1740 != t0 || layer->tex17f8 != t0 || t0->unk7 != 0) {
    layer->tex1740 = t0;
    *(u32*)((u8*)layer + 0x173c) |= 0x1;
    layer->tex17f8 = t0;
    *(u32*)((u8*)layer + 0x17f4) |= 0x1;
        }
    *(u32*)((u8*)layer + 0xeb0) = 0;
    *(u32*)((u8*)layer + 0xeb4) = 0;
    *(u32*)((u8*)layer + 0xeb8) = 4;
    *(u32*)((u8*)layer + 0x16d0) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1788) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1170) = 8;
    *(u32*)((u8*)layer + 0x1174) = 0;
    *(u32*)((u8*)layer + 0x1178) = 0;
    *(u8*)((u8*)layer + 0x117c) = 0;
    *(u32*)((u8*)layer + 0x1180) = 0;
    *(u32*)((u8*)layer + 0x16dc) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1794) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0xf70) = 8;
    *(u32*)((u8*)layer + 0xf74) = 13;
    *(u32*)((u8*)layer + 0xf78) = 12;
    *(u32*)((u8*)layer + 0xf7c) = 15;
    *(u32*)((u8*)layer + 0x16d4) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x178c) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x12b0) = 0;
    *(u32*)((u8*)layer + 0x12b4) = 0;
    *(u32*)((u8*)layer + 0x12b8) = 0;
    *(u8*)((u8*)layer + 0x12bc) = 0;
    *(u32*)((u8*)layer + 0x12c0) = 0;
    *(u32*)((u8*)layer + 0x16e0) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1798) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1070) = 7;
    *(u32*)((u8*)layer + 0x1074) = 7;
    *(u32*)((u8*)layer + 0x1078) = 7;
    *(u32*)((u8*)layer + 0x107c) = 4;
    *(u32*)((u8*)layer + 0x16d8) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1790) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
        GStexture* t1 = (GStexture*)_fadeEffectWork.tex1;
        if (*(GStexture**)((u8*)layer + 0x1744) != t1 || *(GStexture**)((u8*)layer + 0x17fc) != t1 || t1->unk7 != 0) {
    *(GStexture**)((u8*)layer + 0x1744) = t1;
    *(u32*)((u8*)layer + 0x173c) |= 0x2;
    *(GStexture**)((u8*)layer + 0x17fc) = t1;
    *(u32*)((u8*)layer + 0x17f4) |= 0x2;
        }
    *(u32*)((u8*)layer + 0xebc) = 0;
    *(u32*)((u8*)layer + 0xec0) = 1;
    *(u32*)((u8*)layer + 0xec4) = 4;
    *(u32*)((u8*)layer + 0x16d0) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1788) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1184) = 0;
    *(u32*)((u8*)layer + 0x1188) = 0;
    *(u32*)((u8*)layer + 0x118c) = 0;
    *(u8*)((u8*)layer + 0x1190) = 0;
    *(u32*)((u8*)layer + 0x1194) = 0;
    *(u32*)((u8*)layer + 0x16dc) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1794) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0xf80) = 15;
    *(u32*)((u8*)layer + 0xf84) = 15;
    *(u32*)((u8*)layer + 0xf88) = 15;
    *(u32*)((u8*)layer + 0xf8c) = 0;
    *(u32*)((u8*)layer + 0x16d4) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x178c) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x12c4) = 1;
    *(u32*)((u8*)layer + 0x12c8) = 0;
    *(u32*)((u8*)layer + 0x12cc) = 0;
    *(u8*)((u8*)layer + 0x12d0) = 0;
    *(u32*)((u8*)layer + 0x12d4) = 0;
    *(u32*)((u8*)layer + 0x16e0) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1798) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1080) = 4;
    *(u32*)((u8*)layer + 0x1084) = 7;
    *(u32*)((u8*)layer + 0x1088) = 7;
    *(u32*)((u8*)layer + 0x108c) = 0;
    *(u32*)((u8*)layer + 0x16d8) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1790) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
        if (*(GStexture**)((u8*)layer + 0x1748) != t || *(GStexture**)((u8*)layer + 0x1800) != t || t->unk7 != 0) {
    *(GStexture**)((u8*)layer + 0x1748) = t;
    *(u32*)((u8*)layer + 0x173c) |= 0x4;
    *(GStexture**)((u8*)layer + 0x1800) = t;
    *(u32*)((u8*)layer + 0x17f4) |= 0x4;
        }
    *(u32*)((u8*)layer + 0xec8) = 1;
    *(u32*)((u8*)layer + 0xecc) = 2;
    *(u32*)((u8*)layer + 0xed0) = 4;
    *(u32*)((u8*)layer + 0x16d0) |= 0x4;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1788) |= 0x4;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1198) = 0;
    *(u32*)((u8*)layer + 0x119c) = 0;
    *(u32*)((u8*)layer + 0x11a0) = 0;
    *(u8*)((u8*)layer + 0x11a4) = 0;
    *(u32*)((u8*)layer + 0x11a8) = 0;
    *(u32*)((u8*)layer + 0x16dc) |= 0x4;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1794) |= 0x4;
    *(u32*)((u8*)layer + 0xf90) = 15;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0xf94) = 8;
    *(u32*)((u8*)layer + 0xf98) = 0;
    *(u32*)((u8*)layer + 0xf9c) = 15;
    *(u32*)((u8*)layer + 0x16d4) |= 0x4;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x178c) |= 0x4;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x12d8) = 0;
    *(u32*)((u8*)layer + 0x12dc) = 0;
    *(u32*)((u8*)layer + 0x12e0) = 0;
    *(u8*)((u8*)layer + 0x12e4) = 0;
    *(u32*)((u8*)layer + 0x12e8) = 0;
    *(u32*)((u8*)layer + 0x16e0) |= 0x4;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1798) |= 0x4;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1090) = 7;
    *(u32*)((u8*)layer + 0x1094) = 5;
    *(u32*)((u8*)layer + 0x1098) = 0;
    *(u32*)((u8*)layer + 0x109c) = 7;
    *(u32*)((u8*)layer + 0x16d8) |= 0x4;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1790) |= 0x4;
        layer->primType = 0x98;
        layer->vf = (GSgfxVF*)_fadeEffectTrainer_vf;
        c.x = 320.0f;
        c.y = 240.0f;
        c.z = 0.0f;
        int a = (s32)(255.0f * (1.0f - fadeSqrtf(progress)));
        u8 aa = a;
        if (aa > _fadeEffectWork.unk0E || aa == 0) {
            return pending;
        }
        _fadeEffectWork.unk0E = aa;
        Mtx r;
        GSvec v;
        GSvec out;
        v.z = v.y = v.x = 3.0f;
        PSMTXScale(m, v.x, v.y, v.z);
        PSMTXRotRad(r, 'Z', 0.0f);
        PSMTXConcat(r, m, m);
        PSMTXTransApply(m, m, c.x, c.y, c.z);
        v.x = 128.0f;
        v.y = 128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        out.x = out.x - c.x;
        out.y = out.y - c.y;
        f32 u0 = (320.0f - out.x) / 640.0f;
        f32 u1 = (320.0f + out.x) / 640.0f;
        f32 v0 = (240.0f - out.y) / 480.0f;
        f32 v1 = (240.0f + out.y) / 480.0f;
        layer->beginSurface(4);
        v.x = -128.0f;
        v.y = -128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        GXFifoNV.f32 = out.x;
        GXFifoNV.f32 = out.y;
        GXFifoNV.f32 = out.z;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = a;
        GXFifoNV.f32 = 0.01f;
        GXFifoNV.f32 = 0.01f;
        GXFifoNV.f32 = u0;
        GXFifoNV.f32 = v0;
        v.x = 128.0f;
        v.y = -128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        GXFifoNV.f32 = out.x;
        GXFifoNV.f32 = out.y;
        GXFifoNV.f32 = out.z;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = a;
        GXFifoNV.f32 = 0.99f;
        GXFifoNV.f32 = 0.01f;
        GXFifoNV.f32 = v0;
        GXFifoNV.f32 = u1;
        v.x = -128.0f;
        v.y = 128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        GXFifoNV.f32 = out.x;
        GXFifoNV.f32 = out.y;
        GXFifoNV.f32 = out.z;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = a;
        GXFifoNV.f32 = 0.01f;
        GXFifoNV.f32 = 0.99f;
        GXFifoNV.f32 = u0;
        GXFifoNV.f32 = v1;
        v.x = 128.0f;
        v.y = 128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        GXFifoNV.f32 = out.x;
        GXFifoNV.f32 = out.y;
        GXFifoNV.f32 = out.z;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = a;
        GXFifoNV.f32 = 0.99f;
        GXFifoNV.f32 = 0.99f;
        GXFifoNV.f32 = u1;
        GXFifoNV.f32 = v1;
        layer->endSurface();
    }
    return pending;
}

static void _fadeEffectFunction_trainer_second_FirstInit() {
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.unk0A = 0;
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.unk0E = 0;
    f32 sgn = fadeRandInline(2) != 0 ? 1.0f : -1.0f;
    _fadeEffectWork.step = 0.1f * sgn;
    _fadeEffectWork.target = 24.0f * sgn;
    _fadeEffectWork.value = 0.0f;
    GSgfxVFInit((GSgfxVF*)_fadeEffectTrainer_vf);
    GSgfxVFCreate((GSgfxVF*)_fadeEffectTrainer_vf);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 9, 1, 4, 0);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 11, 1, 5, 0);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 13, 1, 4, 0);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 14, 1, 4, 0);
}

static bool fadeEffectHookFunction_tear_off(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        GSgfxVideoSetLockFrameRate(1);
        _fadeTearOffWork.a = 640;
        _fadeTearOffWork.b = 0;
        _fadeEffectWork.frame = 0;
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        return pending;
    }
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->primType = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    if (layer->tex1740 != t || layer->tex17f8 != t || t->unk7 != 0) {
        layer->tex1740 = t;
        layer->dirty173c |= 1;
        layer->tex17f8 = t;
        layer->dirty17f4 |= 1;
    }
    int alpha = (s32)(255.0f * (1.0f - elapsed / duration));
    if (timeGetLastFrameTime() != 0) {
        _fadeTearOffWork.a -= 10;
        _fadeTearOffWork.b += 10;
    }
    _fadeTearOffDraw(layer, alpha, _fadeEffectWork.frame);
    return pending;
}

static void _fadeTearOffDraw(GSgfxLayer* layer, u8 alpha, int frame) {
    s16 x0 = _fadeTearOffWork.a;
    s16 y0 = _fadeTearOffWork.b;
    f32 fx = (f32)x0 / 640.0f;
    f32 fy = (f32)y0 / 480.0f;
    u8 half = alpha / 2;
    layer->beginSurface(4);
    s16 zero = 0;
    f32 fzero = 0.0f;
    f32 fone = 1.0f;
    GXFifoNV.s16 = zero;
    GXFifoNV.s16 = zero;
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = alpha;
    GXFifoNV.f32 = fzero;
    GXFifoNV.f32 = fzero;
    GXFifoNV.s16 = 640;
    GXFifoNV.s16 = zero;
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = alpha;
    GXFifoNV.f32 = fone;
    GXFifoNV.f32 = fzero;
    GXFifoNV.s16 = zero;
    GXFifoNV.s16 = 480;
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = alpha;
    GXFifoNV.f32 = fzero;
    GXFifoNV.f32 = fone;
    GXFifoNV.s16 = 640;
    GXFifoNV.s16 = 480;
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = alpha;
    GXFifoNV.f32 = fone;
    GXFifoNV.f32 = fone;
    layer->endSurface();
    layer->beginSurface(3);
    GXFifoNV.s16 = x0;
    GXFifoNV.s16 = zero;
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = alpha;
    GXFifoNV.f32 = fx;
    GXFifoNV.f32 = fzero;
    GXFifoNV.s16 = x0;
    GXFifoNV.s16 = y0;
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = alpha;
    GXFifoNV.f32 = fone;
    GXFifoNV.f32 = fzero;
    GXFifoNV.s16 = 640;
    GXFifoNV.s16 = y0;
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = alpha;
    GXFifoNV.f32 = fone;
    GXFifoNV.f32 = fy;
    layer->endSurface();
    layer->beginSurface(3);
    GXFifoNV.s16 = (s16)(x0 + frame);
    GXFifoNV.s16 = (s16)frame;
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = half;
    GXFifoNV.f32 = fx;
    GXFifoNV.f32 = fzero;
    GXFifoNV.s16 = (s16)(frame + 640);
    GXFifoNV.s16 = (s16)frame;
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = half;
    GXFifoNV.f32 = fone;
    GXFifoNV.f32 = fzero;
    GXFifoNV.s16 = (s16)(frame + 640);
    GXFifoNV.s16 = (s16)(y0 + frame);
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = half;
    GXFifoNV.f32 = fone;
    GXFifoNV.f32 = fy;
    layer->endSurface();
    layer->beginSurface(3);
    GXFifoNV.s16 = (s16)(x0 + frame * 2);
    GXFifoNV.s16 = (s16)(frame * 2);
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = half;
    GXFifoNV.f32 = fx;
    GXFifoNV.f32 = fzero;
    GXFifoNV.s16 = (s16)(frame * 2 + 640);
    GXFifoNV.s16 = (s16)(frame * 2);
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = half;
    GXFifoNV.f32 = fone;
    GXFifoNV.f32 = fzero;
    GXFifoNV.s16 = (s16)(frame * 2 + 640);
    GXFifoNV.s16 = (s16)(y0 + frame * 2);
    GXFifoNV.s16 = zero;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = 0xFF;
    GXFifoNV.u8 = half;
    GXFifoNV.f32 = fone;
    GXFifoNV.f32 = fy;
    layer->endSurface();
}

static bool fadeEffectHookFunction_distortion_yoko(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeDistortionInit();
        _fadeEffectWork.value = 0.0f;
        if (fadeRandInline(2) == 0) {
            _fadeEffectWork.step = 0.4f;
            _fadeEffectWork.target = 128.0f;
        } else {
            _fadeEffectWork.step = -0.4f;
            _fadeEffectWork.target = -128.0f;
        }
        _fadeEffectWork.unk0C = fadeRandInline(2) == 0 ? 1 : 2;
        _fadeEffectWork.unk0E = fadeRandInline(2) != 0 ? 1 : 0;
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        _fadeDistortionQuit();
        GSgfxEndBackFBCapture(t);
        return pending;
    }
    f32 progress = elapsed / duration;
    f32 hprogress = hookElapsed / hookDuration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        _fadeEffectWork.value += _fadeEffectWork.step;
        if (_fadeEffectWork.step >= 0.0f) {
            _fadeEffectWork.step += 0.5f * progress;
            if (_fadeEffectWork.value >= _fadeEffectWork.target) {
                _fadeEffectWork.value = _fadeEffectWork.target;
            }
        } else {
            _fadeEffectWork.step -= 0.5f * progress;
            if (_fadeEffectWork.value <= _fadeEffectWork.target) {
                _fadeEffectWork.value = _fadeEffectWork.target;
            }
        }
        _fadeDistortionDoAverage(10);
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
    }
    _fadeEffectMaskFunction(layer, progress);
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->primType = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 1, 1, 4));
    if (layer->tex1740 != t || layer->tex17f8 != t || t->unk7 != 0) {
        layer->tex1740 = t;
        layer->dirty173c |= 1;
        layer->tex17f8 = t;
        layer->dirty17f4 |= 1;
    }
    int cols = _fadeDistortionWork.cols;
    int rows = _fadeDistortionWork.rows;
    s16* pos = _fadeDistortionWork.pos;
    f32* tp = _fadeDistortionWork.tex;
    if (pos == 0 || tp == 0) {
        return false;
    }
    u8 alpha = 255.0f * (1.0f - fadeSqrtf(progress));
    int y;
    int x;
    for (y = 1; y < rows; y++) {
        layer->beginSurface((u16)(cols * 2));
        for (x = 0; x < cols; x++) {
            int a = y * cols + x;
            int b = (y - 1) * cols + x;
            GXPosition3s16(pos[a * 2], pos[a * 2 + 1], 0);
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = alpha;
            GXPosition2f32(tp[a * 2], tp[a * 2 + 1]);
            GXPosition3s16(pos[b * 2], pos[b * 2 + 1], 0);
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = alpha;
            GXPosition2f32(tp[b * 2], tp[b * 2 + 1]);
        }
        layer->endSurface();
    }
    GSvec c;
    switch (_fadeEffectWork.unk0C) {
    case 1:
    case 2:
        c.x = 320.0f + _fadeEffectWork.value;
        c.y = 240.0f;
        break;
    case 4:
    case 8:
        c.x = 320.0f;
        c.y = 240.0f + _fadeEffectWork.value;
        break;
    }
    c.z = 0.0f;
    f32 turn = _fadeEffectWork.unk0E != 0 ? 3.0f : -3.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, turn * ((1.0f - progress) * (1.0f - hprogress)), progress, 0.5f);
    return pending;
}

static void _fadeDistortionDoAverage(u32 amount) {
    f32* p;
    f32* tex = _fadeDistortionWork.tex;
    f32 fy;
    int cols = _fadeDistortionWork.cols;
    int rows = _fadeDistortionWork.rows;
    f32 invX = 1.0f / (f32)(cols - 1);
    f32 invY = 1.0f / (f32)(rows - 1);
    int x;
    if (tex != 0) {
        int y;
        for (y = 0; y < rows; y++) {
            p = tex;
            fy = invY * (f32)y;
            for (x = 0; x < cols; x++) {
                f32 sx;
                f32 sy;
                sx = fadeRandInline(2) == 0 ? 1.0f : -1.0f;
                sy = fadeRandInline(2) == 0 ? 1.0f : -1.0f;
                p[0] = invX * (f32)x + sx * (f32)fadeRandInline(amount) / 1000.0f;
                p[1] = fy + sy * (f32)fadeRandInline(amount) / 1000.0f;
                tex += 2;
                p += 2;
            }
        }
    }
}

static bool fadeEffectHookFunction_distortion_zoom_out(GSgfxLayerID p0, bool p1, f32 p2, f32 p3, f32 p4, f32 p5, void* p6) {
    return fadeEffectHookFunction_distortion_zoom(p0, p1, p2, p3, p4, p5, p6, true);
}

static bool fadeEffectHookFunction_distortion_zoom_in(GSgfxLayerID p0, bool p1, f32 p2, f32 p3, f32 p4, f32 p5, void* p6) {
    return fadeEffectHookFunction_distortion_zoom(p0, p1, p2, p3, p4, p5, p6, false);
}

static bool fadeEffectHookFunction_distortion_zoom(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex, bool zoomOut) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeDistortionInit();
        _fadeEffectWork.unk0C = fadeRandInline(2);
        _fadeEffectWork.unk0E = fadeRandInline(4);
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        _fadeDistortionQuit();
        GSgfxEndBackFBCapture(t);
        return pending;
    }
    f32 progress = elapsed / duration;
    f32 hprogress = hookElapsed / hookDuration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
    }
    _fadeEffectMaskFunction(layer, progress);
    if (timeGetLastFrameTime() != 0) {
        _fadeDistortionDoSecond(10, true);
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->primType = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    if (layer->tex1740 != t || layer->tex17f8 != t || t->unk7 != 0) {
        layer->tex1740 = t;
        layer->dirty173c |= 1;
        layer->tex17f8 = t;
        layer->dirty17f4 |= 1;
    }
    int cols = _fadeDistortionWork.cols;
    int rows = _fadeDistortionWork.rows;
    s16* pos = _fadeDistortionWork.pos;
    f32* tp = _fadeDistortionWork.tex;
    if (pos == 0 || tp == 0) {
        return false;
    }
    u8 alpha = 255.0f * (1.0f - progress);
    int y;
    int x;
    for (y = 1; y < rows; y++) {
        layer->beginSurface((u16)(cols * 2));
        for (x = 0; x < cols; x++) {
            int a = y * cols + x;
            int b = (y - 1) * cols + x;
            GXPosition3s16(pos[a * 2], pos[a * 2 + 1], 0);
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = alpha;
            GXPosition2f32(tp[a * 2], tp[a * 2 + 1]);
            GXPosition3s16(pos[b * 2], pos[b * 2 + 1], 0);
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = alpha;
            GXPosition2f32(tp[b * 2], tp[b * 2 + 1]);
        }
        layer->endSurface();
    }
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    f32 dx = 320.0f / (f32)_fadeDistortionWork.cols;
    f32 dy = 240.0f / (f32)_fadeDistortionWork.rows;
    f32 hh = hprogress * hprogress;
    if (zoomOut) {
        if (_fadeEffectWork.unk0E % 2 == 0) {
            dx = -dx;
        }
        c.x = c.x + dx;
        if (_fadeEffectWork.unk0E <= 1) {
            dy = -dy;
        }
        c.y = c.y + dy;
        f32 scale = 1.0f - 0.4f * hh;
        f32 turn = _fadeEffectWork.unk0C != 0 ? 4.0f : -4.0f;
        if (hprogress < 0.99999f) {
            _fadeEffectSnapshotFadeFunction(layer, t, &c, scale, turn, progress, 0.4f * hprogress + 0.6f);
        }
        if (progress > 0.00001f) {
            c.x = 320.0f;
            c.y = 240.0f;
            _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.01f, 0.0f, progress, 0.8f);
        }
    } else {
        if (_fadeEffectWork.unk0E % 2 == 0) {
            dx = -dx;
        }
        c.x = c.x + dx;
        if (_fadeEffectWork.unk0E <= 1) {
            dy = -dy;
        }
        c.y = c.y + dy;
        f32 scale = 1.0f + 0.4f * hh;
        f32 turn = _fadeEffectWork.unk0C != 0 ? 3.0f : -3.0f;
        if (hprogress < 0.99999f) {
            GSvec sc;
            sc.x = c.x - 320.0f;
            sc.y = c.y - 240.0f;
            sc.z = 0.0f;
            _fadeEffectSnapshotRotate(layer, t, &c, scale, &sc, turn, progress, 0.5f * hprogress + 0.5f);
        }
        if (progress > 0.00001f) {
            c.x = 320.0f;
            c.y = 240.0f;
            _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.01f, 0.0f, progress, 0.8f);
        }
    }
    return pending;
}

static void _fadeDistortionDoSecond(u32 amount, bool flag) {
    int cols = _fadeDistortionWork.cols;
    int rows = _fadeDistortionWork.rows;
    f32 invX = 1.0f / (f32)(cols - 1);
    f32 invY = 1.0f / (f32)(rows - 1);
    f32* tex = _fadeDistortionWork.tex;
    if (tex != 0) {
        int radius2 = rows * rows / 16;
        int cx = cols / 2;
        int cy = rows / 2;
        int y;
        for (y = 0; y < rows; y++) {
            f32* p = tex;
            f32 fy = invY * (f32)y;
            int dy2 = (y - cy) * (y - cy);
            int x;
            for (x = 0; x < cols; x++) {
                f32 sx;
                f32 sy;
                if ((x - cx) * (x - cx) + dy2 < radius2) {
                    sx = fadeRandInline(2) == 0 ? 1.0f : -1.0f;
                    sy = fadeRandInline(2) == 0 ? 1.0f : -1.0f;
                } else if (flag) {
                    if (x < cx) {
                        sx = fadeRandInline(3) == 0 ? -1.0f : 1.0f;
                    } else {
                        sx = fadeRandInline(3) == 0 ? 1.0f : -1.0f;
                    }
                    if (y < cy) {
                        sy = fadeRandInline(3) == 0 ? -1.0f : 1.0f;
                    } else {
                        sy = fadeRandInline(3) == 0 ? 1.0f : -1.0f;
                    }
                } else {
                    if (x < cx) {
                        sx = fadeRandInline(3) != 0 ? -1.0f : 1.0f;
                    } else {
                        sx = fadeRandInline(3) != 0 ? 1.0f : -1.0f;
                    }
                    if (y < cy) {
                        sy = fadeRandInline(3) != 0 ? -1.0f : 1.0f;
                    } else {
                        sy = fadeRandInline(3) != 0 ? 1.0f : -1.0f;
                    }
                }
                p[0] = invX * (f32)x + sx * (f32)fadeRandInline(amount) / 1000.0f;
                p[1] = fy + sy * (f32)fadeRandInline(amount) / 1000.0f;
                tex += 2;
                p += 2;
            }
        }
    }
}

static void _fadeEffectSnapshotRotate(GSgfxLayer* layer, GStexture* tex, GSvec* pos, f32 scale, GSvec* center, f32 angle, f32 progress, f32 blend) {
    Mtx m;
    Mtx r;
    GSvec interp;
    GSvec v;
    GSvec out;
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 x0 = -320.0f;
    f32 y0 = -240.0f;
    f32 x1 = 321.0f;
    f32 y1 = 241.0f;
    s32 alpha;
    _fadeEffectStartTexture(layer, tex);
    v.z = v.y = v.x = 1.0f;
    out.z = out.y = out.x = 0.0f;
    GSlerpGetLinearInterpolationVector(&interp, &v, &out, blend);
    alpha = (s32)(255.0f * interp.x);
    alpha = (s32)((f32)alpha * (1.0f - progress));
    v.z = v.y = v.x = scale;
    PSMTXScale(m, v.x, v.y, v.z);
    PSMTXTransApply(m, m, -center->x, -center->y, zero);
    PSMTXRotRad(r, 'Z', 0.017453292f * angle);
    PSMTXConcat(r, m, m);
    PSMTXTransApply(m, m, pos->x, pos->y, pos->z);
    layer->beginSurface(4);
    v.x = x0;
    v.y = y0;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXWGFifo.f32 = out.x;
    GXWGFifo.f32 = out.y;
    GXWGFifo.f32 = out.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = (u8)alpha;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = zero;
    v.x = x1;
    v.y = y0;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXWGFifo.f32 = out.x;
    GXWGFifo.f32 = out.y;
    GXWGFifo.f32 = out.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = (u8)alpha;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = zero;
    v.x = x0;
    v.y = y1;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXWGFifo.f32 = out.x;
    GXWGFifo.f32 = out.y;
    GXWGFifo.f32 = out.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = (u8)alpha;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = one;
    v.x = x1;
    v.y = y1;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXWGFifo.f32 = out.x;
    GXWGFifo.f32 = out.y;
    GXWGFifo.f32 = out.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = (u8)alpha;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = one;
    layer->endSurface();
    _fadeEffectEnd(layer);
}

static bool fadeEffectHookFunction_distortion(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeDistortionInit();
        _fadeEffectWork.unk0E = fadeRandInline(2);
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        _fadeDistortionQuit();
        GSgfxEndBackFBCapture(t);
        return pending;
    }
    f32 progress = elapsed / duration;
    f32 hprogress = hookElapsed / hookDuration;
    if (timeGetLastFrameTime() != 0) {
        _fadeDistortionDo((u32)(10.0f - 3.0f * hprogress - 6.0f * progress));
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
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
    memcpy(layer->cam->data + 1, &mtxIdent, 0x30);
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->primType = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    if (layer->tex1740 != t || layer->tex17f8 != t || t->unk7 != 0) {
        layer->tex1740 = t;
        layer->dirty173c |= 1;
        layer->tex17f8 = t;
        layer->dirty17f4 |= 1;
    }
    int cols = _fadeDistortionWork.cols;
    int rows = _fadeDistortionWork.rows;
    s16* pos = _fadeDistortionWork.pos;
    f32* tp = _fadeDistortionWork.tex;
    if (pos == 0 || tp == 0) {
        return false;
    }
    u8 alpha = 255.0f * (1.0f - progress * (progress * progress));
    int y;
    int x;
    for (y = 1; y < rows; y++) {
        layer->beginSurface((u16)(cols * 2));
        for (x = 0; x < cols; x++) {
            int a = y * cols + x;
            int b = (y - 1) * cols + x;
            GXPosition3s16(pos[a * 2], pos[a * 2 + 1], 0);
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = alpha;
            GXPosition2f32(tp[a * 2], tp[a * 2 + 1]);
            GXPosition3s16(pos[b * 2], pos[b * 2 + 1], 0);
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = 0xFF;
            GXFifoNV.u8 = alpha;
            GXPosition2f32(tp[b * 2], tp[b * 2 + 1]);
        }
        layer->endSurface();
    }
    return pending;
}

static void _fadeDistortionDo(u32 amount) {
    int cols = _fadeDistortionWork.cols;
    int rows = _fadeDistortionWork.rows;
    f32 invX = 1.0f / (f32)(cols - 1);
    f32 invY = 1.0f / (f32)(rows - 1);
    f32* tex = _fadeDistortionWork.tex;
    if (tex != 0) {
        int radius2 = rows * rows / 16;
        int cx = cols / 2;
        int cy = rows / 2;
        int y;
        for (y = 0; y < rows; y++) {
            f32* p = tex;
            f32 fy = invY * (f32)y;
            int dy2 = (y - cy) * (y - cy);
            int x;
            for (x = 0; x < cols; x++) {
                f32 sx;
                f32 sy;
                if ((x - cx) * (x - cx) + dy2 < radius2) {
                    sx = fadeRandInline(2) == 0 ? 1.0f : -1.0f;
                    sy = fadeRandInline(2) == 0 ? 1.0f : -1.0f;
                } else {
                    if (x < cx) {
                        sx = fadeRandInline(4) == 0 ? -1.0f : 1.0f;
                    } else {
                        sx = fadeRandInline(4) == 0 ? 1.0f : -1.0f;
                    }
                    if (y < cy) {
                        sy = fadeRandInline(4) == 0 ? -1.0f : 1.0f;
                    } else {
                        sy = fadeRandInline(4) == 0 ? 1.0f : -1.0f;
                    }
                }
                p[0] = invX * (f32)x + sx * (f32)fadeRandInline(amount) / 1000.0f;
                p[1] = fy + sy * (f32)fadeRandInline(amount) / 1000.0f;
                tex += 2;
                p += 2;
            }
        }
    }
}

static void _fadeDistortionQuit() {
    if (_fadeDistortionWork.pos != 0) {
        GSmemFree(_fadeDistortionWork.pos);
        _fadeDistortionWork.pos = 0;
    }
    if (_fadeDistortionWork.tex != 0) {
        GSmemFree(_fadeDistortionWork.tex);
        _fadeDistortionWork.tex = 0;
    }
}

static void _fadeDistortionInit() {
    _fadeDistortionWork.cols = 40;
    _fadeDistortionWork.rows = 30;
    _fadeDistortionWork.width = 640;
    _fadeDistortionWork.height = 480;
    _fadeDistortionWork.pos = (s16*)GSmemAllocAlign(0x12C0, 0x20);
    _fadeDistortionWork.tex = (f32*)GSmemAllocAlign(0x2580, 0x20);
    s16* pos = _fadeDistortionWork.pos;
    f32* tex = _fadeDistortionWork.tex;
    if (pos != 0 && tex != 0) {
        int y;
        int x;
        for (y = 0; y < 30; y++) {
            f32 py = 16.551723f;
            py *= (f32)y;
            f32 v = 0.03448276f * (f32)y;
            for (x = 0; x < 40; x++) {
                pos[0] = (16.410257f * (f32)x);
                pos[1] = py;
                if (y == 29) {
                    pos[1] += 1;
                }
                tex[0] = 0.025641026f * (f32)x;
                tex[1] = v;
                pos += 2;
                tex += 2;
            }
        }
    }
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.frame = 0;
}

static bool fadeEffectHookFunction_four_ball(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFourBallInit();
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        return pending;
    }
    f32 progress = elapsed / duration;
    f32 hprogress = hookElapsed / hookDuration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        _fadeEffectWork.value += _fadeEffectWork.step;
        if (_fadeEffectWork.value >= _fadeEffectWork.target) {
            _fadeEffectWork.value = _fadeEffectWork.target;
        }
    }
    _fadeEffectMaskFunction(layer, progress);
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, hprogress);
    _fadeEffectStartTexture(layer, _fadeEffectWork.tex0);
    f32 inv = 1.0f - progress;
    int alpha0 = (s32)(255.0f * inv);
    FADE_EFFECT_BALL* ball = _fadeEffectBall;
    f32 value = _fadeEffectWork.value;
    f32 turn[2];
    f32 move[2];
    turn[0] = 360.0f * (value / 408.40704f);
    turn[1] = -turn[0];
    move[0] = value;
    move[1] = -value;
    GSvec p;
    int g;
    int i;
    for (g = 0; g < 2; g++) {
        for (i = 11; i > 0; i--) {
            FADE_EFFECT_BALL* b = &ball[i];
            if (timeGetLastFrameTime() != 0 && (_fadeEffectWork.frame % 3) == 0) {
                b->x = b[-1].x;
                b->y = b[-1].y;
                b->z = b[-1].z;
                b->w = b[-1].w;
            }
            if (!(b->x > 770.0f) && !(b->x < -130.0f)) {
                int a = (s32)(inv * b->a);
                p.x = b->x;
                p.y = b->y;
                p.z = b->z;
                _disp_four_ball(layer, &p, 1.0f, b->w, a);
                p.y += 235.0f;
                _disp_four_ball(layer, &p, 1.0f, b->w, a);
            }
        }
        f32 w = ball->w;
        if (timeGetLastFrameTime() != 0) {
            w += turn[g];
            if (w <= 0.0f) {
                w += 360.0f;
            } else if (w >= 360.0f) {
                w -= 360.0f;
            }
            ball->w = w;
        }
        f32 x = ball->x;
        if (timeGetLastFrameTime() != 0) {
            x += move[g];
            ball->x = x;
        }
        if (!(x > 770.0f) && !(x < -130.0f)) {
            p.x = ball->x;
            p.y = ball->y;
            p.z = ball->z;
            _disp_four_ball(layer, &p, 1.0f, ball->w, (s32)alpha0);
            p.y += 235.0f;
            _disp_four_ball(layer, &p, 1.0f, ball->w, alpha0);
        }
        ball += 12;
    }
    _fadeEffectEnd(layer);
    return pending;
}

static void _fadeEffectFourBallInit() {
    FADE_EFFECT_BALL (*trails)[12] = (FADE_EFFECT_BALL (*)[12])_fadeEffectBall;
    GSvec start[2];
    int side;
    int point;

    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.unk0A = 0;
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.unk0E = 0;
    _fadeEffectWork.step = 4.0f;
    _fadeEffectWork.value = 0.0f;
    _fadeEffectWork.target = 64.0f;
    start[0].x = -65.0f;
    start[0].y = 65.0f;
    start[0].z = 0.0f;
    start[1].x = 705.0f;
    start[1].y = 181.66666f;
    start[1].z = 0.0f;
    for (side = 0; side < 2; side++) {
        for (point = 0; point < 12; point++) {
            trails[side][point].x = start[side].x;
            trails[side][point].y = start[side].y;
            trails[side][point].z = start[side].z;
            trails[side][point].w = 0.0f;
            trails[side][point].a = 0x82 - point * 10;
        }
        trails[side][0].a = 0xFF;
    }
    _fadeEffect_AdjustParms();
}

static void _disp_four_ball(GSgfxLayer* layer, GSvec* pos, f32 scale, f32 angle, int alpha) {
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 lo = -65.0f;
    f32 hi = 65.0f;
    Mtx m;
    Mtx r;
    GSvec v;
    GSvec out;
    v.z = v.y = v.x = scale;
    PSMTXScale(m, v.x, v.y, v.z);
    PSMTXRotRad(r, 'Z', 0.017453292f * angle);
    PSMTXConcat(r, m, m);
    PSMTXTransApply(m, m, pos->x, pos->y, pos->z);
    layer->beginSurface(4);
    v.x = lo;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, zero);
    v.x = hi;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, zero);
    v.x = lo;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, one);
    v.x = hi;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, one);
    layer->endSurface();
}

static bool fadeEffectHookFunction_blur_ball(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    if (tex == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeBlurBallInit();
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        _fadeBlurBallQuit();
        GSgfxEndBackFBCapture((GStexture*)tex);
        return pending;
    }
    f32 progress = elapsed / duration;
    f32 ang;
    f32 hprogress = hookElapsed / hookDuration;
    if (timeGetLastFrameTime() != 0) {
        ang = 4.0f * hprogress;
        _fadeEffectWork.frame++;
        if (_fadeEffectWork.unk0C == 0) {
            ang *= -1.0f;
        }
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture((GStexture*)tex);
    }
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    _fadeEffectSnapshotTex(layer, (GStexture*)tex, &c, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, ang, progress, 0.0f);
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 1, 1, 4));
    GStexture* t0 = _fadeEffectWork.tex0;
    if (layer->tex1740 != t0 || layer->tex17f8 != t0 || t0->unk7 != 0) {
        layer->tex1740 = t0;
        layer->dirty173c |= 1;
        layer->tex17f8 = t0;
        layer->dirty17f4 |= 1;
    }
    layer->primType = 0x98;
    int alpha = (s32)(0.5f * (255.0f * (1.0f - progress)));
    f32 xpos = 1.4f * (640.0f * hprogress);
    f32 turn = 360.0f * xpos / 376.99112f;
    if (xpos > 753.98224f) {
        xpos = 753.98224f;
    }
    if (xpos > 580.0f) {
        xpos = 580.0f;
    }
    c.x = 640.0f - xpos;
    c.y = _fadeEffectWork.unk0C == 0 ? 72.0f : 408.0f;
    f32 xend = 320.0f + c.x;
    if (xend > 640.0f) {
        xend = 640.0f;
    }
    _disp_blur_ball(layer, &c, xend, -turn, alpha);
    c.x = xpos;
    c.y = _fadeEffectWork.unk0C != 0 ? 72.0f : 408.0f;
    xend = c.x - 320.0f;
    if (xend < 0.0f) {
        xend = 0.0f;
    }
    _disp_blur_ball(layer, &c, xend, turn, alpha);
    return true;
}

static void _fadeBlurBallQuit() {
}

static void _fadeBlurBallInit() {
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.unk0A = 0;
    _fadeEffectWork.unk0C = fadeRandInline(2) != 0 ? 1 : 0;
    _fadeEffectWork.unk0E = fadeRandInline(2) != 0 ? 1 : 0;
    _fadeEffectWork.step = 0.1f;
    _fadeEffectWork.target = 16.0f;
    _fadeEffectWork.value = 0.0f;
    _fadeEffect_AdjustParms();
}

static void _fadeEffectSnapshotTex(GSgfxLayer* layer, GStexture* tex, GSvec* pos, f32 u0, f32 v0, f32 u1, f32 v1, f32 scale, f32 angle, f32 progress, f32 blend) {
    Mtx m;
    Mtx m2;
    Mtx r;
    GSvec v;
    GSvec w;
    GSvec interp;
    s32 alpha;
    _fadeEffectStartTexture(layer, tex);
    v.x = 1.0f;
    v.y = 1.0f;
    v.z = 1.0f;
    w.x = 0.0f;
    w.y = 0.0f;
    w.z = 0.0f;
    GSlerpGetLinearInterpolationVector(&interp, &v, &w, blend);
    alpha = (s32)(255.0f * interp.x);
    alpha = (s32)((f32)alpha * (1.0f - progress));
    v.x = 1.0f;
    v.y = scale;
    v.z = 1.0f;
    PSMTXScale(m, v.x, v.y, v.z);
    PSMTXTransApply(m, m, pos->x, pos->y, pos->z);
    PSMTXTrans(m2, -0.5f, -0.5f, 0.0f);
    PSMTXRotRad(r, 'Z', 0.017453292f * angle);
    PSMTXConcat(r, m2, m2);
    PSMTXTransApply(m2, m2, 0.5f, 0.5f, 0.0f);
    layer->beginSurface(4);
    v.x = -320.0f;
    v.y = -240.0f;
    v.z = 0.0f;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&w);
    GXPosition3f32(w.x, w.y, w.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    v.x = u0;
    v.y = v0;
    v.z = 0.0f;
    PSMTXMultVec(m2, (Vec*)&v, (Vec*)&w);
    GXPosition2f32(w.x, w.y);
    v.x = 321.0f;
    v.y = -240.0f;
    v.z = 0.0f;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&w);
    GXPosition3f32(w.x, w.y, w.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    v.x = u1;
    v.y = v0;
    v.z = 0.0f;
    PSMTXMultVec(m2, (Vec*)&v, (Vec*)&w);
    GXPosition2f32(w.x, w.y);
    v.x = -320.0f;
    v.y = 241.0f;
    v.z = 0.0f;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&w);
    GXPosition3f32(w.x, w.y, w.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    v.x = u0;
    v.y = v1;
    v.z = 0.0f;
    PSMTXMultVec(m2, (Vec*)&v, (Vec*)&w);
    GXPosition2f32(w.x, w.y);
    v.x = 321.0f;
    v.y = 241.0f;
    v.z = 0.0f;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&w);
    GXPosition3f32(w.x, w.y, w.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    v.x = u1;
    v.y = v1;
    v.z = 0.0f;
    PSMTXMultVec(m2, (Vec*)&v, (Vec*)&w);
    GXPosition2f32(w.x, w.y);
    layer->endSurface();
    _fadeEffectEnd(layer);
}

static void _disp_blur_ball(GSgfxLayer* layer, GSvec* pos, f32 xEnd, f32 angle, int alpha) {
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 half = 0.5f;
    f32 lo = -60.0f;
    f32 hi = 60.0f;
    Mtx m;
    Mtx r;
    GSvec v;
    GSvec out;
    v.z = v.y = v.x = 1.0f;
    PSMTXScale(m, v.x, v.y, v.z);
    PSMTXRotRad(r, 'Z', 0.017453292f * angle);
    PSMTXConcat(r, m, m);
    PSMTXTransApply(m, m, pos->x, pos->y, pos->z);
    layer->beginSurface(4);
    GXPosition3f32(pos->x, pos->y - hi, pos->z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)(alpha / 5));
    GXPosition2f32(half, zero);
    GXPosition3f32(pos->x, hi + pos->y, pos->z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)(alpha / 5));
    GXPosition2f32(half, one);
    GXPosition3f32(xEnd, pos->y - hi, pos->z);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0);
    GXPosition2f32(half, zero);
    GXPosition3f32(xEnd, hi + pos->y, pos->z);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0);
    GXPosition2f32(half, one);
    layer->endSurface();
    layer->beginSurface(4);
    v.x = lo;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, zero);
    v.x = hi;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, zero);
    v.x = lo;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, one);
    v.x = hi;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, one);
    layer->endSurface();
}

static bool fadeEffectHookFunction_dist_ball(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer;
    FadeEffectWork* w = &_fadeEffectWork;
    layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeDistBallInit();
        GSgfxBeginBackFBCapture((GStexture*)tex, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        _fadeDistBallQuit();
        GSgfxEndBackFBCapture(t);
        return pending;
    }
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) {
        w->frame++;
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
    }
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, 0.0f);
    c.x = 321.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, 0.5f);
    c.x = 319.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, 0.5f);
    layer->setRenderStateAndSelect((GSgfxVF*)_fadeEffectTrainer_vf);
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
    layer->tgenFunc(1, (GSgfxTgenFunc)1, (GSgfxTgenSrc)5, 0, false, 0);
        *(u8*)((u8*)layer + 0xeac) = 3;
        *(u32*)((u8*)layer + 0x16cc) |= 0x1;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1784) |= 0x1;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
    GStexture* t1 = (GStexture*)w->tex1;
    if (layer->tex1740 != t1 || layer->tex17f8 != t1 || t1->unk7 != 0) {
        layer->tex1740 = t1;
        layer->dirty173c |= 1;
        layer->tex17f8 = t1;
        layer->dirty17f4 |= 1;
    }
        *(u32*)((u8*)layer + 0xeb0) = 0;
        *(u32*)((u8*)layer + 0xeb4) = 0;
        *(u32*)((u8*)layer + 0xeb8) = 4;
        *(u32*)((u8*)layer + 0x16d0) |= 0x1;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1788) |= 0x1;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0x1170) = 8;
        *(u32*)((u8*)layer + 0x1174) = 0;
        *(u32*)((u8*)layer + 0x1178) = 0;
        *(u8*)((u8*)layer + 0x117c) = 0;
        *(u32*)((u8*)layer + 0x1180) = 1;
        *(u32*)((u8*)layer + 0x16dc) |= 0x1;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1794) |= 0x1;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0xf70) = 9;
        *(u32*)((u8*)layer + 0xf74) = 13;
        *(u32*)((u8*)layer + 0xf78) = 12;
        *(u32*)((u8*)layer + 0xf7c) = 15;
        *(u32*)((u8*)layer + 0x16d4) |= 0x1;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x178c) |= 0x1;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0x12b0) = 0;
        *(u32*)((u8*)layer + 0x12b4) = 0;
        *(u32*)((u8*)layer + 0x12b8) = 0;
        *(u8*)((u8*)layer + 0x12bc) = 0;
        *(u32*)((u8*)layer + 0x12c0) = 1;
        *(u32*)((u8*)layer + 0x16e0) |= 0x1;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1798) |= 0x1;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0x1070) = 7;
        *(u32*)((u8*)layer + 0x1074) = 4;
        *(u32*)((u8*)layer + 0x1078) = 5;
        *(u32*)((u8*)layer + 0x107c) = 7;
        *(u32*)((u8*)layer + 0x16d8) |= 0x1;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1790) |= 0x1;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
    if (*(GStexture**)((u8*)layer + 0x1744) != t || *(GStexture**)((u8*)layer + 0x17fc) != t || t->unk7 != 0) {
        *(GStexture**)((u8*)layer + 0x1744) = t;
        *(u32*)((u8*)layer + 0x173c) |= 0x2;
        *(GStexture**)((u8*)layer + 0x17fc) = t;
        *(u32*)((u8*)layer + 0x17f4) |= 0x2;
    }
        *(u32*)((u8*)layer + 0xebc) = 1;
        *(u32*)((u8*)layer + 0xec0) = 1;
        *(u32*)((u8*)layer + 0xec4) = 4;
        *(u32*)((u8*)layer + 0x16d0) |= 0x2;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1788) |= 0x2;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0x1184) = 0;
        *(u32*)((u8*)layer + 0x1188) = 0;
        *(u32*)((u8*)layer + 0x118c) = 0;
        *(u8*)((u8*)layer + 0x1190) = 0;
        *(u32*)((u8*)layer + 0x1194) = 0;
        *(u32*)((u8*)layer + 0x16dc) |= 0x2;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1794) |= 0x2;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0xf80) = 15;
        *(u32*)((u8*)layer + 0xf84) = 8;
        *(u32*)((u8*)layer + 0xf88) = 2;
        *(u32*)((u8*)layer + 0xf8c) = 15;
        *(u32*)((u8*)layer + 0x16d4) |= 0x2;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x178c) |= 0x2;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0x12c4) = 0;
        *(u32*)((u8*)layer + 0x12c8) = 0;
        *(u32*)((u8*)layer + 0x12cc) = 0;
        *(u8*)((u8*)layer + 0x12d0) = 0;
        *(u32*)((u8*)layer + 0x12d4) = 0;
        *(u32*)((u8*)layer + 0x16e0) |= 0x2;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1798) |= 0x2;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0x1080) = 7;
        *(u32*)((u8*)layer + 0x1084) = 7;
        *(u32*)((u8*)layer + 0x1088) = 7;
        *(u32*)((u8*)layer + 0x108c) = 1;
        *(u32*)((u8*)layer + 0x16d8) |= 0x2;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1790) |= 0x2;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
    GStexture* t0 = w->tex0;
    if (*(GStexture**)((u8*)layer + 0x1748) != t0 || *(GStexture**)((u8*)layer + 0x1800) != t0 || t0->unk7 != 0) {
        *(GStexture**)((u8*)layer + 0x1748) = t0;
        *(u32*)((u8*)layer + 0x173c) |= 0x4;
        *(GStexture**)((u8*)layer + 0x1800) = t0;
        *(u32*)((u8*)layer + 0x17f4) |= 0x4;
    }
        *(u32*)((u8*)layer + 0xec8) = 0;
        *(u32*)((u8*)layer + 0xecc) = 2;
        *(u32*)((u8*)layer + 0xed0) = 4;
        *(u32*)((u8*)layer + 0x16d0) |= 0x4;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1788) |= 0x4;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0x1198) = 0;
        *(u32*)((u8*)layer + 0x119c) = 0;
        *(u32*)((u8*)layer + 0x11a0) = 0;
        *(u8*)((u8*)layer + 0x11a4) = 0;
        *(u32*)((u8*)layer + 0x11a8) = 0;
        *(u32*)((u8*)layer + 0x16dc) |= 0x4;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1794) |= 0x4;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0xf90) = 8;
        *(u32*)((u8*)layer + 0xf94) = 15;
        *(u32*)((u8*)layer + 0xf98) = 15;
        *(u32*)((u8*)layer + 0xf9c) = 0;
        *(u32*)((u8*)layer + 0x16d4) |= 0x4;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x178c) |= 0x4;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0x12d8) = 0;
        *(u32*)((u8*)layer + 0x12dc) = 0;
        *(u32*)((u8*)layer + 0x12e0) = 0;
        *(u8*)((u8*)layer + 0x12e4) = 0;
        *(u32*)((u8*)layer + 0x12e8) = 0;
        *(u32*)((u8*)layer + 0x16e0) |= 0x4;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1798) |= 0x4;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
        *(u32*)((u8*)layer + 0x1090) = 7;
        *(u32*)((u8*)layer + 0x1094) = 4;
        *(u32*)((u8*)layer + 0x1098) = 5;
        *(u32*)((u8*)layer + 0x109c) = 4;
        *(u32*)((u8*)layer + 0x16d8) |= 0x4;
        *(u32*)((u8*)layer + 0x16a8) |= 0x8;
        *(u32*)((u8*)layer + 0x1790) |= 0x4;
        *(u32*)((u8*)layer + 0x1760) |= 0x8;
            *(u32*)((u8*)layer + 0x1998) = 152;
    layer->vf = (GSgfxVF*)_fadeEffectTrainer_vf;
    layer->primType = 0x98;
    f32 kc9933 = 0.2f;
    f32 kc9956 = 255.0f;
    f32 kc9981 = 1.0f;
    int alpha = (s32)(kc9933 * (kc9956 * (kc9981 - progress)));
    FADE_EFFECT_BOUND* e = _fadeEffectBound;
    f32 zero = 0.0f;
    int i;
    for (i = 0; i < 12; e++, i++) {
        f32 ang = e->w;
        if (timeGetLastFrameTime() != 0) {
            if ((f32)e->vx < 0.0f) {
                ang += 18.0f;
            } else {
                ang -= 18.0f;
            }
            if (ang <= 0.0f) {
                ang += 360.0f;
            } else if (ang >= 360.0f) {
                ang -= 360.0f;
            }
        }
        e->w = ang;
        if (timeGetLastFrameTime() != 0) {
            f32 x = (f32)e->vx;
            x += (f32)e->x;
            if (x < 32.0f) {
                x = 32.0f;
                e->vx = -e->vx;
            } else if (x > 608.0f) {
                x = 608.0f;
                e->vx = -e->vx;
            }
            e->x = x;
        }
        if (timeGetLastFrameTime() != 0) {
            f32 y = (f32)e->y;
            y += (f32)e->vy;
            if (y < 32.0f) {
                y = 32.0f;
                e->vy = -e->vy;
            } else if (y > 448.0f) {
                e->vy = -e->vy * 8 / 10;
                y = 448.0f;
                if ((f32)e->vy > -1.0f) {
                    if ((f32)e->vy < 1.0f) {
                        e->vy = -7;
                    }
                }
            } else if ((f32)e->vy >= 0.0f) {
                f32 kc11364 = 1.0f;
                e->vy = (f32)e->vy + kc11364;
            } else {
                f32 kc11467 = 1.0f;
                e->vy = (f32)e->vy - kc11467;
            }
            e->y = y;
        }
        GSvec p;
        p.y = e->y;
        p.x = e->x;
        p.z = zero;
        _disp_dist_ball(layer, &p, 1.0f, ang, alpha);
    }
    return pending;
}

static void _fadeDistBallQuit() {
    GSgfxVFFree(_fadeEffectTrainer_vf);
}

static void _fadeDistBallInit() {
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.frame = 1;
    FADE_EFFECT_BOUND* e = _fadeEffectBound;
    int i;
    int sign;
    for (i = 0; i < 12; i++, e++) {
        e->x = fadeRandInline(640);
        e->y = fadeRandInline(240);
        e->w = 0;
        e->vx = fadeRandInline(4) * 4 + 4;
        sign = i % 2 == 0 ? 1 : -1;
        e->vx *= sign;
        e->vy = 0;
    }
    GSgfxVFInit((GSgfxVF*)_fadeEffectTrainer_vf);
    GSgfxVFCreate((GSgfxVF*)_fadeEffectTrainer_vf);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 9, 1, 4, 0);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 11, 1, 5, 0);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 13, 1, 4, 0);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 14, 1, 4, 0);
    _fadeEffect_AdjustParms();
}

static void _disp_dist_ball(GSgfxLayer* layer, GSvec* pos, f32 scale, f32 angle, int alpha) {
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 lo = -32.0f;
    f32 hi = 32.0f;
    Mtx m;
    Mtx r;
    GSvec v;
    GSvec out;
    v.z = v.y = v.x = scale;
    PSMTXScale(m, v.x, v.y, v.z);
    PSMTXRotRad(r, 'Z', 0.017453292f * angle);
    PSMTXConcat(r, m, m);
    PSMTXTransApply(m, m, pos->x, pos->y, pos->z);
    layer->beginSurface(4);
    f32 u0;
    f32 v0;
    f32 u1;
    f32 v1;
    u0 = (pos->x - hi) / 640.0f;
    u1 = (hi + pos->x) / 480.0f;
    v0 = (pos->y - hi) / 640.0f;
    v1 = (hi + pos->y) / 480.0f;
    v.x = lo;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, zero);
    GXPosition2f32(u0, v0);
    v.x = hi;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, zero);
    GXPosition2f32(u1, v0);
    v.x = lo;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, one);
    GXPosition2f32(u0, v1);
    v.x = hi;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, one);
    GXPosition2f32(u1, v1);
    layer->endSurface();
}

static bool fadeEffectHookFunction_slide_ball(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectSlideBallInit();
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        return pending;
    }
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
    }
    _fadeEffectMaskFunction(layer, progress);
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, 0.0f);
    int alpha = (s32)(255.0f * (1.0f - progress));
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 4, 0, 0, 1, 5, 1, 1, 4));
    if (layer->tex1740 != t || layer->tex17f8 != t || t->unk7 != 0) {
        layer->tex1740 = t;
        layer->dirty173c |= 1;
        layer->tex17f8 = t;
        layer->dirty17f4 |= 1;
    }
    layer->primType = 0x80;
    layer->beginSurface(0x30);
    FADE_EFFECT_BOUND* e = _fadeEffectBound;
    int i;
    for (i = 0; i < 12; i++, e++) {
        f32 x0;
        f32 x1;
        f32 u0;
        f32 u1;
        if ((f32)e->vx > 0.0f) {
            x0 = e->x;
            if (x0 < -1.0f) {
                x0 = -1.0f;
            }
            x1 = 641.0f;
            u1 = (641.0f - x0) / 640.0f;
            u0 = 0.0f;
        } else {
            x1 = e->x;
            if (x1 > 641.0f) {
                x1 = 641.0f;
            }
            x0 = -1.0f;
            u1 = 1.0f;
            u0 = (640.0f - x1) / 640.0f;
        }
        f32 y0 = e->y - 26;
        f32 y1 = 53.0f + y0;
        f32 v0 = y0 / 480.0f;
        f32 v1 = y1 / 480.0f;
        GXWGFifo.f32 = x0;
        GXWGFifo.f32 = y0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = alpha;
        GXWGFifo.f32 = u0;
        GXWGFifo.f32 = v0;
        GXWGFifo.f32 = x1;
        GXWGFifo.f32 = y0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = alpha;
        GXWGFifo.f32 = v0;
        GXWGFifo.f32 = u1;
        GXWGFifo.f32 = x1;
        GXWGFifo.f32 = y1;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = alpha;
        GXWGFifo.f32 = u1;
        GXWGFifo.f32 = v1;
        GXWGFifo.f32 = x0;
        GXWGFifo.f32 = y1;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = alpha;
        GXWGFifo.f32 = u0;
        GXWGFifo.f32 = v1;
    }
    layer->endSurface();
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 4, 0, 0, 1, 5, 1, 1, 4));
    GStexture* t0 = (GStexture*)_fadeEffectWork.tex0;
    if (layer->tex1740 != t0 || layer->tex17f8 != t0 || t0->unk7 != 0) {
        layer->tex1740 = t0;
        layer->dirty173c |= 1;
        layer->tex17f8 = t0;
        layer->dirty17f4 |= 1;
    }
    layer->primType = 0x80;
    layer->beginSurface(0x60);
    alpha = (u8)alpha;
    e = _fadeEffectBound;
    for (i = 0; i < 12; e++, i++) {
        f32 xe;
        if (e->vx > 0) {
            xe = e->x - 320.0f;
            if (xe < 0.0f) {
                xe = 0.0f;
            }
        } else {
            xe = 320.0f + e->x;
            if (xe > 641.0f) {
                xe = 641.0f;
            }
        }
        _disp_slide_ball(layer, e->x, e->y, xe, e->w, alpha);
        if (timeGetLastFrameTime() != 0) {
            e->x += e->vx;
            e->w = 360.0f * (f32)e->x / 166.50441f;
            if (e->vx > 0) {
                e->x = e->x + e->x / 80;
            } else {
                e->x = e->x - (640 - e->x) / 80;
            }
        }
    }
    layer->endSurface();
    return pending;
}

static void _fadeEffectSlideBallInit() {
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.frame = 0;
    u32 side = fadeRandInline(2) == 0 ? 1 : 0;
    FADE_EFFECT_BOUND* e = _fadeEffectBound;
    int i;
    for (i = 0; i < 12; e++, i++) {
        if (side == 1) {
            e->x = -(s32)fadeRandInline(160);
            e->y = 26 + i * 53;
            e->w = (s16)(360.0f * (f32)e->x / 166.50441f);
            if (i % 2 == 0) {
                e->vx = fadeRandInline(5) * 2 + 4;
            } else {
                e->vx = fadeRandInline(4) * 2 + 8;
            }
        } else {
            e->x = fadeRandInline(160) + 640;
            e->y = 26 + i * 53;
            e->w = (s16)(360.0f * (f32)e->x / 166.50441f);
            if (i % 2 == 0) {
                e->vx = -(s32)(fadeRandInline(5) * 2 + 4);
            } else {
                e->vx = -(s32)(fadeRandInline(4) * 2 + 8);
            }
        }
    }
}

static void _disp_slide_ball(GSgfxLayer* layer, f32 x, f32 y, f32 xEnd, f32 angle, int alpha) {
    Mtx m;
    Mtx r;
    GSvec v;
    GSvec out;
    f32 hi = 26.0f;
    f32 half = 0.5f;
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 y1;
    f32 x0;
    f32 y0;
    f32 x1;
    y0 = y;
    y0 = y0 - hi;
    y1 = hi + y;
    x0 = x - hi;
    GXPosition2f32(x, y0);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)(alpha / 5));
    GXPosition2f32(half, zero);
    GXPosition2f32(x, y1);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)(alpha / 5));
    GXPosition2f32(half, one);
    GXPosition2f32(xEnd, y1);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0);
    GXPosition2f32(half, one);
    GXPosition2f32(xEnd, y0);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0);
    GXPosition2f32(half, zero);
    v.z = zero;
    x1 = hi + x;
    v.x = -x;
    v.y = -y;
    PSMTXTrans(m, v.x, v.y, v.z);
    PSMTXRotRad(r, 'Z', 0.017453292f * angle);
    PSMTXConcat(r, m, m);
    v.x = x;
    v.y = y;
    v.z = zero;
    PSMTXTransApply(m, m, v.x, v.y, v.z);
    v.x = x0;
    v.y = y0;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition2f32(out.x, out.y);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, zero);
    v.x = x1;
    v.y = y0;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition2f32(out.x, out.y);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, zero);
    v.x = x1;
    v.y = y1;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition2f32(out.x, out.y);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, one);
    v.x = x0;
    v.y = y1;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition2f32(out.x, out.y);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, one);
}

static bool fadeEffectHookFunction_bound_ball(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectBoundBallInit();
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        return pending;
    }
    f32 progress = elapsed / duration;
    f32 hprogress = hookElapsed / hookDuration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
    }
    _fadeEffectMaskFunction(layer, progress);
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, 0.0f);
    c.x = 320.0f + (f32)_fadeEffectWork.frame;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, 0.5f);
    c.x = 320.0f - (f32)_fadeEffectWork.frame;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, 0.5f);
    _fadeEffectStartTexture(layer, _fadeEffectWork.tex0);
    s32 alpha = (s32)(255.0f * (1.0f - progress) * (1.0f - hprogress));
    int i;
    f32 zero = 0.0f;
    for (i = 0; i < 16; i++) {
        FADE_EFFECT_BOUND* e = &_fadeEffectBound[i];
        f32 x;
        f32 y;
        f32 ang;
        ang = e->w;
        if (timeGetLastFrameTime() != 0) {
            if (e->vx > 0) {
                ang += 18.0f;
            } else {
                ang -= 18.0f;
            }
            if (ang <= 0.0f) {
                ang += 360.0f;
            } else if (ang >= 360.0f) {
                ang -= 360.0f;
            }
        }
        e->w = ang;
        x = e->x;
        if (timeGetLastFrameTime() != 0) {
            x += e->vx;
            if (x < 32.0f) {
                x = 32.0f;
                e->vx = -e->vx;
            } else if (x > 608.0f) {
                x = 608.0f;
                e->vx = -e->vx;
            }
        }
        e->x = x;
        y = e->y;
        if (timeGetLastFrameTime() != 0) {
            y += e->vy;
            if (y < 32.0f) {
                y = 32.0f;
                e->vy = -e->vy;
            } else if (y > 448.0f) {
                e->vy = -e->vy;
                y = 448.0f;
                if (e->vy < 0.5f) {
                    e->vy = -13;
                }
            } else if (e->vy >= 0.0f) {
                e->vy += 0.5f;
            } else {
                e->vy -= 0.5f;
            }
        }
        e->y = y;
        GSvec p;
        p.y = e->y;
        p.x = e->x;
        p.z = zero;
        _disp_bound_ball(layer, &p, 1.0f, ang, alpha);
    }
    _fadeEffectEnd(layer);
    return pending;
}

static void _fadeEffectBoundBallInit() {
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.frame = 1;
    int i;
    int odd;
    int sign;
    for (i = 0; i < 16; i++) {
        FADE_EFFECT_BOUND* e = &_fadeEffectBound[i];
        switch (i % 4) {
        case 0:
            e->x = fadeRandInline(320);
            e->y = fadeRandInline(240);
            break;
        case 1:
            e->x = fadeRandInline(320) + 320;
            e->y = fadeRandInline(240) + 240;
            break;
        case 2:
            e->x = fadeRandInline(320) + 320;
            e->y = fadeRandInline(240);
            break;
        case 3:
            e->x = fadeRandInline(320);
            e->y = fadeRandInline(240) + 240;
            break;
        }
        e->w = 0;
        e->vx = fadeRandInline(4) * 3 + 3;
        odd = i % 2;
        sign = odd == 0 ? 1 : -1;
        e->vx *= sign;
        e->vy = fadeRandInline(4) * 3 + 3;
        sign = odd == 0 ? 1 : -1;
        e->vy *= sign;
    }
    _fadeEffect_AdjustParms();
}

static void _disp_bound_ball(GSgfxLayer* layer, GSvec* pos, f32 scale, f32 angle, int alpha) {
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 lo = -32.0f;
    f32 hi = 32.0f;
    Mtx m;
    Mtx r;
    GSvec v;
    GSvec out;
    v.z = v.y = v.x = scale;
    PSMTXScale(m, v.x, v.y, v.z);
    PSMTXRotRad(r, 'Z', 0.017453292f * angle);
    PSMTXConcat(r, m, m);
    PSMTXTransApply(m, m, pos->x, pos->y, pos->z);
    layer->beginSurface(4);
    v.x = lo;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, zero);
    v.x = hi;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, zero);
    v.x = lo;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, one);
    v.x = hi;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, one);
    layer->endSurface();
}

static bool fadeEffectHookFunction_Doku(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GXColor color = {0x1F, 0x08, 0x08, 0xFF};
    int alpha;
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    f32 hp = hookElapsed / hookDuration;
    f32 progress = elapsed / duration;
    GSvec out;
    GSvec to;
    GSvec from;
    f32 t;
    if (hp <= 0.5f) {
        t = 4.0f * hp;
        from.z = from.y = from.x = 1.0f;
        to.z = to.y = to.x = 0.0f;
        if (t >= 1.0f) {
            t = 1.0f;
        }
    } else {
        t = (hp - 0.5f);
        t *= 2.0f;
        to.z = to.y = to.x = 1.0f;
        from.z = from.y = from.x = 0.0f;
        if (t >= 1.0f) {
            t = 1.0f;
        }
    }
    GSlerpGetLinearInterpolationVector(&out, &to, &from, t);
    u8 a0 = 255.0f * out.x;
    alpha = (s32)((f32)a0 * (1.0f - progress));
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0));
    layer->beginSurface(4);
    f32 zero = 0.0f;
    f32 w = 640.0f;
    f32 h = 480.0f;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = zero;
    GXWGFifo.u8 = color.r;
    GXWGFifo.u8 = color.g;
    GXWGFifo.u8 = color.b;
    GXWGFifo.u8 = alpha;
    GXWGFifo.f32 = w;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = zero;
    GXWGFifo.u8 = color.r;
    GXWGFifo.u8 = color.g;
    GXWGFifo.u8 = color.b;
    GXWGFifo.u8 = alpha;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = h;
    GXWGFifo.f32 = zero;
    GXWGFifo.u8 = color.r;
    GXWGFifo.u8 = color.g;
    GXWGFifo.u8 = color.b;
    GXWGFifo.u8 = alpha;
    GXWGFifo.f32 = w;
    GXWGFifo.f32 = h;
    GXWGFifo.f32 = zero;
    GXWGFifo.u8 = color.r;
    GXWGFifo.u8 = color.g;
    GXWGFifo.u8 = color.b;
    GXWGFifo.u8 = alpha;
    layer->endSurface();
    if (hp >= 1.0f) {
        fadeEffectDokuStop();
        return false;
    }
    return pending;
}

static bool fadeEffectHookFunction_carde(GSgfxLayerID p0, bool p1, f32 p2, f32 p3, f32 p4, f32 p5, void* p6) {
    return fadeEffectHookFunction_yoko(p0, p1, p2, p3, p4, p5, p6);
}

static bool fadeEffectHookFunction_trainer(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    Mtx m;
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_trainer_FirstInit((GStexture*)tex);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        GSgfxVFFree(_fadeEffectTrainer_vf);
    }
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        _fadeEffectWork.value += _fadeEffectWork.step;
        if (_fadeEffectWork.step >= 0.0f) {
            _fadeEffectWork.step += 0.5f * progress;
            if (_fadeEffectWork.value >= _fadeEffectWork.target) {
                _fadeEffectWork.value = _fadeEffectWork.target;
            }
        } else {
            _fadeEffectWork.step -= 0.5f * progress;
            if (_fadeEffectWork.value <= _fadeEffectWork.target) {
                _fadeEffectWork.value = _fadeEffectWork.target;
            }
        }
    }
    GSvec cc;
    cc.x = 320.0f;
    cc.y = 240.0f;
    cc.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &cc, 1.0f, 0.0f, progress, 0.0f);
    cc.x = 320.0f + _fadeEffectWork.value;
    _fadeEffectSnapshotFadeFunction(layer, t, &cc, 1.0f, 0.0f, progress, 0.5f);
    cc.x = 320.0f - _fadeEffectWork.value;
    _fadeEffectSnapshotFadeFunction(layer, t, &cc, 1.0f, 0.0f, progress, 0.5f);
    if (GSgfxVFIsUsed((GSgfxVF*)_fadeEffectTrainer_vf)) {
        layer->setRenderStateAndSelect((GSgfxVF*)_fadeEffectTrainer_vf);
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
        layer->f1664 = 7;
        layer->f1670 = 0;
        layer->f1668 = 0;
        layer->f166c = 7;
        layer->f1671 = 0;
        layer->f1672 = 1;
        layer->dirty170c |= 0x10;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 0x10;
        layer->dirty1760 |= 0x40;
        layer->d8c = 0;
        layer->dirty16b8 |= 2;
        layer->dirty16a8 |= 2;
        layer->dirty1770 |= 2;
        layer->dirty1760 |= 2;
    
        layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
        layer->tgenFunc(1, (GSgfxTgenFunc)1, (GSgfxTgenSrc)5, 0, false, 0);
    *(u8*)((u8*)layer + 0xeac) = 2;
    *(u32*)((u8*)layer + 0x16cc) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1784) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
        GStexture* t1 = (GStexture*)_fadeEffectWork.tex1;
        if (layer->tex1740 != t1 || layer->tex17f8 != t1 || t1->unk7 != 0) {
    layer->tex1740 = t1;
    *(u32*)((u8*)layer + 0x173c) |= 0x1;
    layer->tex17f8 = t1;
    *(u32*)((u8*)layer + 0x17f4) |= 0x1;
        }
    *(u32*)((u8*)layer + 0xeb0) = 0;
    *(u32*)((u8*)layer + 0xeb4) = 0;
    *(u32*)((u8*)layer + 0xeb8) = 4;
    *(u32*)((u8*)layer + 0x16d0) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1788) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1170) = 8;
    *(u32*)((u8*)layer + 0x1174) = 0;
    *(u32*)((u8*)layer + 0x1178) = 0;
    *(u8*)((u8*)layer + 0x117c) = 0;
    *(u32*)((u8*)layer + 0x1180) = 1;
    *(u32*)((u8*)layer + 0x16dc) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1794) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0xf70) = 9;
    *(u32*)((u8*)layer + 0xf74) = 13;
    *(u32*)((u8*)layer + 0xf78) = 12;
    *(u32*)((u8*)layer + 0xf7c) = 15;
    *(u32*)((u8*)layer + 0x16d4) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x178c) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x12b0) = 0;
    *(u32*)((u8*)layer + 0x12b4) = 0;
    *(u32*)((u8*)layer + 0x12b8) = 0;
    *(u8*)((u8*)layer + 0x12bc) = 0;
    *(u32*)((u8*)layer + 0x12c0) = 1;
    *(u32*)((u8*)layer + 0x16e0) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1798) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1070) = 7;
    *(u32*)((u8*)layer + 0x1074) = 4;
    *(u32*)((u8*)layer + 0x1078) = 5;
    *(u32*)((u8*)layer + 0x107c) = 7;
    *(u32*)((u8*)layer + 0x16d8) |= 0x1;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1790) |= 0x1;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
        if (*(GStexture**)((u8*)layer + 0x1744) != t || *(GStexture**)((u8*)layer + 0x17fc) != t || t->unk7 != 0) {
    *(GStexture**)((u8*)layer + 0x1744) = t;
    *(u32*)((u8*)layer + 0x173c) |= 0x2;
    *(GStexture**)((u8*)layer + 0x17fc) = t;
    *(u32*)((u8*)layer + 0x17f4) |= 0x2;
        }
    *(u32*)((u8*)layer + 0xebc) = 1;
    *(u32*)((u8*)layer + 0xec0) = 1;
    *(u32*)((u8*)layer + 0xec4) = 4;
    *(u32*)((u8*)layer + 0x16d0) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1788) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1184) = 0;
    *(u32*)((u8*)layer + 0x1188) = 0;
    *(u32*)((u8*)layer + 0x118c) = 0;
    *(u8*)((u8*)layer + 0x1190) = 0;
    *(u32*)((u8*)layer + 0x1194) = 0;
    *(u32*)((u8*)layer + 0x16dc) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1794) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0xf80) = 15;
    *(u32*)((u8*)layer + 0xf84) = 8;
    *(u32*)((u8*)layer + 0xf88) = 2;
    *(u32*)((u8*)layer + 0xf8c) = 15;
    *(u32*)((u8*)layer + 0x16d4) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x178c) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x12c4) = 0;
    *(u32*)((u8*)layer + 0x12c8) = 0;
    *(u32*)((u8*)layer + 0x12cc) = 0;
    *(u8*)((u8*)layer + 0x12d0) = 0;
    *(u32*)((u8*)layer + 0x12d4) = 0;
    *(u32*)((u8*)layer + 0x16e0) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1798) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
    *(u32*)((u8*)layer + 0x1080) = 7;
    *(u32*)((u8*)layer + 0x1084) = 7;
    *(u32*)((u8*)layer + 0x1088) = 7;
    *(u32*)((u8*)layer + 0x108c) = 1;
    *(u32*)((u8*)layer + 0x16d8) |= 0x2;
    *(u32*)((u8*)layer + 0x16a8) |= 0x8;
    *(u32*)((u8*)layer + 0x1790) |= 0x2;
    *(u32*)((u8*)layer + 0x1760) |= 0x8;
        layer->vf = (GSgfxVF*)_fadeEffectTrainer_vf;
        layer->primType = 0x98;
        f32 alphaf = (1.0f - progress);
        alphaf *= 255.0f;
        f32 scale = 1.0f + (f32)_fadeEffectWork.frame / 150.0f;
        Mtx r;
        GSvec cen;
        GSvec v;
        GSvec out;
        cen.x = 320.0f;
        cen.y = 240.0f;
        cen.z = 0.0f;
        v.z = v.y = v.x = scale;
        PSMTXScale(m, v.x, v.y, v.z);
        PSMTXRotRad(r, 'Z', 0.0f);
        PSMTXConcat(r, m, m);
        PSMTXTransApply(m, m, cen.x, cen.y, cen.z);
        v.x = 128.0f;
        v.y = 128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        out.x = out.x - 320.0f;
        out.y = out.y - 240.0f;
        f32 u0 = (320.0f - out.x) / 640.0f;
        f32 u1 = (320.0f + out.x) / 640.0f;
        f32 v0 = (240.0f - out.y) / 480.0f;
        f32 v1 = (240.0f + out.y) / 480.0f;
        layer->beginSurface(4);
        v.x = -128.0f;
        v.y = -128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        GXFifoNV.f32 = out.x;
        GXFifoNV.f32 = out.y;
        GXFifoNV.f32 = out.z;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = alphaf;
        GXFifoNV.f32 = 0.0f;
        GXFifoNV.f32 = 0.0f;
        GXFifoNV.f32 = u0;
        GXFifoNV.f32 = v0;
        v.x = 128.0f;
        v.y = -128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        GXFifoNV.f32 = out.x;
        GXFifoNV.f32 = out.y;
        GXFifoNV.f32 = out.z;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = alphaf;
        GXFifoNV.f32 = 1.0f;
        GXFifoNV.f32 = 0.0f;
        GXFifoNV.f32 = v0;
        GXFifoNV.f32 = u1;
        v.x = -128.0f;
        v.y = 128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        GXFifoNV.f32 = out.x;
        GXFifoNV.f32 = out.y;
        GXFifoNV.f32 = out.z;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = alphaf;
        GXFifoNV.f32 = 0.0f;
        GXFifoNV.f32 = 1.0f;
        GXFifoNV.f32 = u0;
        GXFifoNV.f32 = v1;
        v.x = 128.0f;
        v.y = 128.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
        GXFifoNV.f32 = out.x;
        GXFifoNV.f32 = out.y;
        GXFifoNV.f32 = out.z;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = 0xFF;
        GXFifoNV.u8 = alphaf;
        GXFifoNV.f32 = 1.0f;
        GXFifoNV.f32 = 1.0f;
        GXFifoNV.f32 = u1;
        GXFifoNV.f32 = v1;
        layer->endSurface();
    }
    if (timeGetLastFrameTime() != 0) {
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        GSgfxEndBackFBCapture(t);
    }
    return pending;
}

static void _fadeEffectFunction_trainer_FirstInit(GStexture* tex) {
    GSgfxVideoSetLockFrameRate(0);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.unk0A = 0;
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.unk0E = 0;
    _fadeEffectWork.step = 0.1f;
    _fadeEffectWork.target = 16.0f;
    _fadeEffectWork.value = 0.0f;
    GSgfxBeginBackFBCapture(tex, _myBackFB, 0);
    GSgfxVFInit((GSgfxVF*)_fadeEffectTrainer_vf);
    GSgfxVFCreate((GSgfxVF*)_fadeEffectTrainer_vf);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 9, 1, 4, 0);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 11, 1, 5, 0);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 13, 1, 4, 0);
    GSgfxVFSetElement((GSgfxVF*)_fadeEffectTrainer_vf, 14, 1, 4, 0);
    _fadeEffect_AdjustParms();
}

static bool fadeEffectHookFunction_fadein(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    _fadeEffectMaskFunction(layer, elapsed / duration);
    return pending;
}

static bool fadeEffectHookFunction_fadeout_in(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    f32 progress = elapsed / duration;
    f32 hprogress = hookElapsed / hookDuration;
    _fadeEffectMaskFunction(layer, progress);
    if (tex == 0) {
        return pending;
    }
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, (GStexture*)tex, &c, 1.0f, 0.0f, progress, hprogress);
    return pending;
}

static bool fadeEffectHookFunction_boss_second(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayerID lid;
    GStexture* t;
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    if (tex == 0) {
        return pending;
    }
    t = (GStexture*)tex;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_boss_FirstInit_second();
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        fadeFluidQuit();
        GSgfxEndBackFBCapture(t);
        return pending;
    }
    f32 progress = elapsed / duration;
    f32 hprogress = hookElapsed / hookDuration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        GSgfxBeginBackFBCapture(t, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(t);
    }
    if (pending == 1) {
        GSvec c;
        c.x = 320.0f;
        c.y = 240.0f;
        c.z = 0.0f;
        _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, fadeSqrtf(progress), 0.0f);
        if (timeGetLastFrameTime() != 0) {
            fadeFluidEvaluateSecond();
        }
        progress = progress * progress * progress * progress;
        hprogress = hprogress * hprogress;
        lid = id;
        fadeFluidDispSecond(lid, t, progress, hprogress);
    }
    return pending;
}

static void _fadeEffectFunction_boss_FirstInit_second() {
    GSvec p;
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.unk0A = 0;
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.unk0E = 0;
    fadeFluidInit(0x23, 0x19, 1.0f, 1.0f, 0.5f, 0.01f);
    p.x = 17.5f;
    p.y = 12.5f;
    p.z = 0.0f;
    fadeFluidSetShockSecond(&p, 50.0f);
    p.x = 1.0f;
    p.y = 1.0f;
    p.z = 0.0f;
    fadeFluidSetShockSecond(&p, 0.1f);
    p.x = 34.0f;
    p.y = 1.0f;
    p.z = 0.0f;
    fadeFluidSetShockSecond(&p, 0.1f);
    p.x = 1.0f;
    p.y = 24.0f;
    p.z = 0.0f;
    fadeFluidSetShockSecond(&p, 0.1f);
    p.x = 34.0f;
    p.y = 24.0f;
    p.z = 0.0f;
    fadeFluidSetShockSecond(&p, 0.1f);
    _fadeEffect_AdjustParms();
}

static bool fadeEffectHookFunction_boss(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    if (tex == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_boss_FirstInit();
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        fadeFluidQuit();
    }
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
    }
    if (pending == 1) {
        if (timeGetLastFrameTime() != 0) {
            fadeFluidEvaluate();
        }
        fadeFluidDisp((GStexture*)tex, progress, 0.0f);
    }
    return pending;
}

static void _fadeEffectFunction_boss_FirstInit() {
    GSvec p;
    GSgfxVideoSetLockFrameRate(0);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.unk0A = 0;
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.unk0E = 0;
    fadeFluidInit(0x23, 0x19, 1.0f, 1.0f, 0.4f, 0.01f);
    p.x = 17.5f;
    p.y = 12.499999f;
    p.z = 0.0f;
    fadeFluidSetShock(&p, 16.0f);
    p.x = 5.4687495f;
    p.y = 5.208333f;
    p.z = 0.0f;
    fadeFluidSetShock(&p, 8.0f);
    p.x = 29.531248f;
    p.y = 19.791666f;
    p.z = 0.0f;
    fadeFluidSetShock(&p, 8.0f);
    p.x = 29.531248f;
    p.y = 5.208333f;
    p.z = 0.0f;
    fadeFluidSetShock(&p, 8.0f);
    p.x = 5.4687495f;
    p.y = 19.791666f;
    p.z = 0.0f;
    fadeFluidSetShock(&p, 8.0f);
    _fadeEffect_AdjustParms();
}

static bool fadeEffectHookFunction_ball_second(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    GStexture* t = (GStexture*)tex;
    if (t == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectBallSecondInit();
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        _fadeEffectBallSecondQuit();
        return pending;
    }
    f32 progress = elapsed / duration;
    f32 hprogress = hookElapsed / hookDuration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        _fadeEffectWork.value += _fadeEffectWork.step;
        if (_fadeEffectWork.value >= _fadeEffectWork.target) {
            _fadeEffectWork.value = _fadeEffectWork.target;
        }
    }
    _fadeEffectMaskFunction(layer, progress);
    hprogress = hprogress * hprogress;
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, t, &c, 1.0f, 0.0f, progress, hprogress);
    _fadeEffectStartTexture(layer, _fadeEffectWork.tex0);
    f32 inv = 1.0f - progress;
    FADE_EFFECT_BALL* ball = _fadeEffectBall;
    f32 value = _fadeEffectWork.value;
    f32 turn[2];
    f32 move[2];
    turn[0] = 360.0f * (value / 471.23892f);
    turn[1] = -turn[0];
    move[0] = value;
    move[1] = -value;
    f32 x;
    int alpha;
    int g;
    int i;
    for (g = 0; g < 2; g++) {
        for (i = 11; i > 0; i--) {
            FADE_EFFECT_BALL* b = &ball[i];
            if (timeGetLastFrameTime() != 0 && (_fadeEffectWork.frame & 3) == 0) {
                b->x = b[-1].x;
                b->y = b[-1].y;
                b->z = b[-1].z;
                b->w = b[-1].w;
            }
            if (!(x > 790.0f) && !(x < -150.0f)) {
                alpha = (s32)(inv * b->a);
                _dispball(layer, (GSvec*)b, 0.5f, b->w, alpha);
            }
        }
        f32 w = ball->w;
        w += turn[g];
        if (w <= 0.0f) {
            w += 360.0f;
        } else if (w >= 360.0f) {
            w -= 360.0f;
        }
        if (timeGetLastFrameTime() != 0) {
            ball->w = w;
        }
        x = ball->x;
        x += move[g];
        if (timeGetLastFrameTime() != 0) {
            ball->x = x;
        }
        if (!(x > 790.0f) && !(x < -150.0f)) {
            f32 y = ball->y;
            y -= move[g];
            if (y > 405.0f) {
                y = 405.0f;
            } else if (y < 75.0f) {
                y = 75.0f;
            }
            ball->y = y;
            _dispball(layer, (GSvec*)ball, 0.5f, ball->w, alpha);
        }
        ball += 12;
    }
    _fadeEffectEnd(layer);
    return pending;
}

static void _fadeEffectBallSecondQuit() {
}

static void _fadeEffectBallSecondInit() {
    FADE_EFFECT_BALL (*trails)[12] = (FADE_EFFECT_BALL (*)[12])_fadeEffectBall;
    GSvec start[2];
    int side;
    int point;

    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.unk0A = 0;
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.unk0E = 0;
    _fadeEffectWork.step = 4.0f;
    _fadeEffectWork.value = 0.0f;
    _fadeEffectWork.target = 48.0f;
    start[0].x = -75.0f;
    start[0].y = 165.0f;
    start[0].z = 0.0f;
    start[1].x = 715.0f;
    start[1].y = 315.0f;
    start[1].z = 0.0f;
    for (side = 0; side < 2; side++) {
        for (point = 0; point < 12; point++) {
            trails[side][point].x = start[side].x;
            trails[side][point].y = start[side].y;
            trails[side][point].z = start[side].z;
            trails[side][point].w = 0.0f;
            trails[side][point].a = 0xFF - point * 0x15;
        }
    }
    _fadeEffect_AdjustParms();
}

static bool fadeEffectHookFunction_ball(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_ball_FirstInit();
    }
    f32 progress = elapsed / duration;
    f32 hprogress = hookElapsed / hookDuration;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        _fadeEffectWork.value += _fadeEffectWork.step;
        if (_fadeEffectWork.value >= _fadeEffectWork.target) {
            _fadeEffectWork.value = _fadeEffectWork.target;
        }
    }
    _fadeEffectMaskFunction(layer, progress);
    if (tex == 0) {
        return pending;
    }
    GSvec c;
    c.x = 320.0f;
    c.y = 240.0f;
    c.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, (GStexture*)tex, &c, 1.0f, 0.0f, progress, hprogress);
    _fadeEffectStartTexture(layer, _fadeEffectWork.tex0);
    f32 inv = 1.0f - progress;
    FADE_EFFECT_BALL* ball = _fadeEffectBall;
    f32 value = _fadeEffectWork.value;
    f32 move[2];
    f32 turn[2];
    turn[0] = 360.0f * (value / 804.24774f);
    turn[1] = -turn[0];
    move[0] = value;
    move[1] = -value;
    int g;
    int i;
    for (g = 0; g < 2; g++) {
        for (i = 11; i > 0; i--) {
            FADE_EFFECT_BALL* b = &ball[i];
            if (timeGetLastFrameTime() != 0 && (_fadeEffectWork.frame & 3) == 0) {
                b->x = b[-1].x;
                b->y = b[-1].y;
                b->z = b[-1].z;
                b->w = b[-1].w;
            }
            _dispball(layer, (GSvec*)b, 1.0f, b->w, (s32)(inv * b->a));
        }
        f32 w = ball->w;
        if (timeGetLastFrameTime() != 0) {
            w += turn[g];
            if (w <= 0.0f) {
                w += 360.0f;
            } else if (w >= 360.0f) {
                w -= 360.0f;
            }
            ball->w = w;
        }
        f32 x = ball->x;
        if (timeGetLastFrameTime() != 0) {
            x += move[g];
            if (x > 896.0f) {
                x = 896.0f;
            } else if (x < -256.0f) {
                x = -256.0f;
            }
            ball->x = x;
        }
        _dispball(layer, (GSvec*)ball, 1.0f, ball->w, (s32)(inv * ball->a));
        ball += 12;
    }
    _fadeEffectEnd(layer);
    return pending;
}

static void _dispball(GSgfxLayer* layer, GSvec* pos, f32 scale, f32 angle, int alpha) {
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 lo = -128.0f;
    f32 hi = 128.0f;
    Mtx m;
    Mtx r;
    GSvec v;
    GSvec out;
    v.z = v.y = v.x = scale;
    PSMTXScale(m, v.x, v.y, v.z);
    PSMTXRotRad(r, 'Z', 0.017453292f * angle);
    PSMTXConcat(r, m, m);
    PSMTXTransApply(m, m, pos->x, pos->y, pos->z);
    layer->beginSurface(4);
    v.x = lo;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, zero);
    v.x = hi;
    v.y = lo;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, zero);
    v.x = lo;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(zero, one);
    v.x = hi;
    v.y = hi;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXPosition3f32(out.x, out.y, out.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
    GXPosition2f32(one, one);
    layer->endSurface();
}

static void _fadeEffectFunction_ball_FirstInit() {
    FADE_EFFECT_BALL (*trails)[12] = (FADE_EFFECT_BALL (*)[12])_fadeEffectBall;
    GSvec start[2];
    int side;
    int point;

    GSgfxVideoSetLockFrameRate(0);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.unk0A = 0;
    _fadeEffectWork.unk0C = 0;
    _fadeEffectWork.unk0E = 0;
    _fadeEffectWork.step = 4.0f;
    _fadeEffectWork.value = 0.0f;
    _fadeEffectWork.target = 48.0f;
    start[0].x = -128.0f;
    start[0].y = 364.0f;
    start[0].z = 0.0f;
    start[1].x = 768.0f;
    start[1].y = 116.0f;
    start[1].z = 0.0f;
    for (side = 0; side < 2; side++) {
        for (point = 0; point < 12; point++) {
            trails[side][point].x = start[side].x;
            trails[side][point].y = start[side].y;
            trails[side][point].z = start[side].z;
            trails[side][point].w = 0.0f;
            trails[side][point].a = 0xFF - point * 0x15;
        }
    }
    _fadeEffect_AdjustParms();
}

static bool fadeEffectHookFunction_tate(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GStexture* t;
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    if (tex == 0) {
        return pending;
    }
    t = (GStexture*)tex;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_UDLR_FirstInit(t, 8);
    }
    return _fadeEffectFunction_UDLR_Main(layer, pending, elapsed, duration, hookElapsed, hookDuration, t);
}

static bool fadeEffectHookFunction_yoko(GSgfxLayerID id, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, void* tex) {
    GStexture* t;
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer == 0) {
        return pending;
    }
    if (tex == 0) {
        return pending;
    }
    t = (GStexture*)tex;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_UDLR_FirstInit(t, 2);
    }
    return _fadeEffectFunction_UDLR_Main(layer, pending, elapsed, duration, hookElapsed, hookDuration, t);
}

static bool _fadeEffectFunction_UDLR_Main(GSgfxLayer* layer, bool pending, f32 elapsed, f32 duration, f32 hookElapsed, f32 hookDuration, GStexture* tex) {
    f32 progress = elapsed / duration;
    GSvec v;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        _fadeEffectWork.value += _fadeEffectWork.step;
        if (_fadeEffectWork.step >= 0.0f) {
            _fadeEffectWork.step += 0.5f * progress;
            if (_fadeEffectWork.value >= _fadeEffectWork.target) {
                _fadeEffectWork.value = _fadeEffectWork.target;
            }
        } else {
            _fadeEffectWork.step -= 0.5f * progress;
            if (_fadeEffectWork.value <= _fadeEffectWork.target) {
                _fadeEffectWork.value = _fadeEffectWork.target;
            }
        }
    }
    v.x = 320.0f;
    v.y = 240.0f;
    v.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, tex, &v, 1.0f, 0.0f, progress, 0.0f);
    switch (_fadeEffectWork.unk0C) {
    case 1:
    case 2:
        v.x = 320.0f + _fadeEffectWork.value;
        v.y = 240.0f;
        break;
    case 4:
    case 8:
        v.x = 320.0f;
        v.y = 240.0f + _fadeEffectWork.value;
        break;
    }
    f32 t = (f32)_fadeEffectWork.frame / (45.0f * (1.0f - progress) + 1.0f);
    v.z = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, tex, &v, 1.0f, t, progress, 0.4f);
    switch (_fadeEffectWork.unk0C) {
    case 1:
    case 2:
        v.x = 1.5f * _fadeEffectWork.value + 320.0f;
        break;
    case 4:
    case 8:
        v.y = 1.5f * _fadeEffectWork.value + 240.0f;
        break;
    }
    _fadeEffectSnapshotFadeFunction(layer, tex, &v, 1.0f, t * -1.5f, progress, 0.4f);
    if (timeGetLastFrameTime() != 0) {
        GSgfxBeginBackFBCapture(tex, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(tex);
    }
    if (_fadeEffectFirstFlag == 0 && !pending) {
        GSgfxEndBackFBCapture(tex);
    }
    return pending;
}

static void _fadeEffectFunction_UDLR_FirstInit(GStexture* tex, u16 mode) {
    GSgfxVideoSetLockFrameRate(0);
    _fadeEffectWork.tex0 = (GStexture*)GSresGetResourceAllGroup(0xEBC1200);
    _fadeEffectWork.tex1 = GSresGetResourceAllGroup(0xEBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.unk0A = 0;
    _fadeEffectWork.unk0C = mode;
    _fadeEffectWork.unk0E = 0;
    _fadeEffectWork.step = 0.3f;
    _fadeEffectWork.target = 128.0f;
    _fadeEffectWork.value = 0.0f;
    if (_fadeEffectGetRandom(2) == 0) {
        _fadeEffectWork.step *= -1.0f;
        _fadeEffectWork.target *= -1.0f;
        switch (mode) {
        case 1:
            _fadeEffectWork.unk0C = 2;
            break;
        case 2:
            _fadeEffectWork.unk0C = 1;
            break;
        case 4:
            _fadeEffectWork.unk0C = 8;
            break;
        case 8:
            _fadeEffectWork.unk0C = 4;
            break;
        }
    }
    _fadeEffect_AdjustParms();
    GSgfxBeginBackFBCapture(tex, _myBackFB, 0);
}

static bool _myBackFB(GStexture* p0, u32 p1, void* p2) {
    return true;
}

static void _fadeEffectSnapshotFadeFunction(GSgfxLayer* layer, GStexture* tex, GSvec* pos, f32 scale, f32 angle, f32 progress, f32 blend) {
    Mtx m;
    Mtx r;
    GSvec interp;
    GSvec v;
    GSvec out;
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 x0 = -320.0f;
    f32 y0 = -240.0f;
    f32 x1 = 320.1f;
    f32 y1 = 240.1f;
    s32 alpha;
    _fadeEffectStartTexture(layer, tex);
    v.z = v.y = v.x = 1.0f;
    out.z = out.y = out.x = 0.0f;
    GSlerpGetLinearInterpolationVector(&interp, &v, &out, blend);
    alpha = (s32)(255.0f * interp.x);
    alpha = (s32)((f32)alpha * (1.0f - progress));
    v.z = v.y = v.x = scale;
    PSMTXScale(m, v.x, v.y, v.z);
    PSMTXRotRad(r, 'Z', 0.017453292f * angle);
    PSMTXConcat(r, m, m);
    PSMTXTransApply(m, m, pos->x, pos->y, pos->z);
    layer->beginSurface(4);
    v.x = x0;
    v.y = y0;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXWGFifo.f32 = out.x;
    GXWGFifo.f32 = out.y;
    GXWGFifo.f32 = out.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = (u8)alpha;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = zero;
    v.x = x1;
    v.y = y0;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXWGFifo.f32 = out.x;
    GXWGFifo.f32 = out.y;
    GXWGFifo.f32 = out.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = (u8)alpha;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = zero;
    v.x = x0;
    v.y = y1;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXWGFifo.f32 = out.x;
    GXWGFifo.f32 = out.y;
    GXWGFifo.f32 = out.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = (u8)alpha;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = one;
    v.x = x1;
    v.y = y1;
    v.z = zero;
    PSMTXMultVec(m, (Vec*)&v, (Vec*)&out);
    GXWGFifo.f32 = out.x;
    GXWGFifo.f32 = out.y;
    GXWGFifo.f32 = out.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = (u8)alpha;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = one;
    layer->endSurface();
    _fadeEffectEnd(layer);
}

static void _fadeEffectMaskFunction(GSgfxLayer* layer, f32 progress) {
    _fadeEffectStartSprites(layer);
    s32 alpha = 255 - (s32)(255.0f * progress);
    layer->beginSurface(4);
    f32 zero = 0.0f;
    f32 w = 640.0f;
    f32 h = 480.0f;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = zero;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = alpha;
    GXWGFifo.f32 = w;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = zero;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = alpha;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = h;
    GXWGFifo.f32 = zero;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = alpha;
    GXWGFifo.f32 = w;
    GXWGFifo.f32 = h;
    GXWGFifo.f32 = zero;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = alpha;
    layer->endSurface();
    _fadeEffectEnd(layer);
}

static void _fadeEffectEnd(GSgfxLayer* layer) {
}

static void _fadeEffectStartSprites(GSgfxLayer* layer) {
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->primType = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0));
}

static void _fadeEffectStartTexture(GSgfxLayer* layer, GStexture* tex) {
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
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->primType = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 1, 1, 4));
    if (layer->tex1740 != tex || layer->tex17f8 != tex || tex->unk7 != 0) {
        layer->tex1740 = tex;
        layer->dirty173c |= 1;
        layer->tex17f8 = tex;
        layer->dirty17f4 |= 1;
    }
}

static void _fadeEffect_AdjustParms() {
    f32 scale = 3.0f;
    _fadeEffectWork.step = _fadeEffectWork.step / scale;
    _fadeEffectWork.value = _fadeEffectWork.value / scale;
    _fadeEffectWork.target = _fadeEffectWork.target / scale;
}

static u32 _fadeEffectGetRandom(u32 range) {
    u32 lo = HSD_Rand();
    u32 hi = HSD_Rand();
    return ((hi << 16) | lo) % range;
}

extern "C" void fadeEffectInit(void) {
    _fadeEffectFirstFlag = 1;
}

