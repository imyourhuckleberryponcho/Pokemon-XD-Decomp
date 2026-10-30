#include <dolphin/types.h>
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct GScamera;
enum GSgfxCunitAlpha { GSgfxCunitAlpha_draft_dummy };
enum GSgfxCunitSrc { GSgfxCunitSrc_draft_dummy };
enum GSgfxDiffuseFunc { GSgfxDiffuseFunc_draft_dummy };
struct GSgfxLayer;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
struct GSgfxLight;
enum GSgfxLightType { GSgfxLightType_draft_dummy };
enum GSgfxTgenFunc { GSgfxTgenFunc_draft_dummy };
enum GSgfxTgenSrc { GSgfxTgenSrc_draft_dummy };
struct GSgfxVF;
struct GSmtx;
struct GStexture;
enum Mtx { Mtx_draft_dummy };
enum MtxPtr { MtxPtr_draft_dummy };
struct Vec;

struct BlendState {
    u8 pad[0xbc];
};

class GSgfxLayer {
public:
    u8 pad0[0xd88];
    u8 fd88;
    s32 fd8c;
    s32 fd90;
    u8 pad_d94[0x1644 - 0xd94];
    s32 blendOp;
    s32 blendSrc;
    s32 blendDst;
    s32 blendLogic;
    u8 f1654;
    u8 f1655;
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
    u8 pad_1673;
    u8 f1674;
    u8 pad_1675[0x16a8 - 0x1675];
    u32 dirty16a8;
    u8 pad_16ac[0x16b8 - 0x16ac];
    u32 dirty16b8;
    u8 pad_16bc[0x170c - 0x16bc];
    u32 dirty170c;
    u8 pad_1710[0x1760 - 0x1710];
    u32 dirty1760;
    u8 pad_1764[0x1770 - 0x1764];
    u32 dirty1770;
    u8 pad_1774[0x17c4 - 0x1774];
    u32 dirty17c4;

    inline void dirtyPE(u32 bit) {
        dirty170c |= bit;
        dirty16a8 |= 0x40;
        dirty17c4 |= bit;
        dirty1760 |= 0x40;
    }
    inline void dirtyRaster(u32 bit) {
        dirty16b8 |= bit;
        dirty16a8 |= 2;
        dirty1770 |= bit;
        dirty1760 |= 2;
    }
    inline void setColorUpdate(u8 color, u8 alpha, u8 z) {
        colorUpdate = color;
        alphaUpdate = alpha;
        zUpdate = z;
        dirtyPE(4);
    }
    inline void setZMode(u8 enable, s32 func) {
        zEnable = enable;
        zFunc = func;
        dirtyPE(8);
    }
    inline void setAlphaCompare(s32 comp0, u8 ref0, s32 op, s32 comp1, u8 ref1, u8 flag) {
        f1664 = comp0;
        f1670 = ref0;
        f1668 = op;
        f166c = comp1;
        f1671 = ref1;
        f1672 = flag;
        dirtyPE(0x10);
    }
    inline void setDstAlpha(u8 enable, u8 alpha) {
        f1654 = enable;
        f1655 = alpha;
        dirtyPE(2);
    }
    inline void setDither(u8 dither) {
        f1674 = dither;
        dirtyPE(0x20);
    }
    inline void setCullMode(s32 mode) {
        fd8c = mode;
        dirtyRaster(2);
    }
    inline void setFd90(s32 v) {
        fd90 = v;
        dirtyRaster(4);
    }
    inline void setFd88(u8 v) {
        fd88 = v;
        dirtyRaster(8);
    }
    u8 pad_17c8[0x1818 - 0x17c8];
    BlendState blendTable[2];
    BlendState* curBlend;
    s32 curBlendIdx;
public:
    s32 cunitChannelGen(unsigned char, GSgfxCunitAlpha, GSgfxCunitSrc, GSgfxCunitSrc, unsigned long, GSgfxLight**, GSgfxLightType, GSgfxDiffuseFunc);
    s32 tgenFunc(unsigned char, GSgfxTgenFunc, GSgfxTgenSrc, GSmtx*, bool, GSmtx*);
};

extern "C" {

extern GSgfxLayer* g_current_layer;

extern "C" {
struct GScamera {
    u8 _draft[1];
};
struct GSgfxLight {
    u8 _draft[1];
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSmtx {
    u8 _draft[1];
};
struct GStexture {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
};

extern "C" {
GScamera* GScameraGetActiveCamera(void);
MtxPtr GScameraGetMatrixPtr(GScamera* camera);
void GScameraGetPosition(GScamera* camera, f32* position);
u8 GScameraIsValid(GScamera* camera);
void GScameraLoadActiveCameraMatrix(GSgfxLayerID id);
void GScameraLoadCameraMatrix(GScamera* camera, GSgfxLayerID id);
void GSgfxProjectSetupCameraParameters(GScamera* camera);
void GSgfxVFCreate(GSgfxVF* vf);
void GSgfxVFInit(GSgfxVF* vf);
void GSgfxVFSetArray(GSgfxVF* vf, s32, s32, void*, s32, s32);
void GSgfxVFSetElement(GSgfxVF* vf, s32, s32, s32, s32);
void GStextureSetFilter(GStexture* tex, s32 minFilter, s32 magFilter, u32 mipFilter);
void GStextureSetWrap(GStexture* tex, u32 wrapS, u32 wrapT);
asm void PSMTXCopy(const register Mtx src, register Mtx dst);
void PSMTXTranspose(const register Mtx src, register Mtx xPose);
asm void PSVECCrossProduct(const register Vec* a, const register Vec* b, register Vec* axb);
void PSVECNormalize(const register Vec* src, register Vec* unit);
static void __sinit_particleEngine_cpp();
void* memset(void* dst, int val, size_t n);
void particleEngineInit();
void particleEnginePostUpdate();
void particleEngineRender(void *p0);
void particleEngineSetDefaultRenderState(u8 tev);
void particleEngineUpdate(f32 p0);
s32 peBankRender(void*);
s32 peBankUpdate(void*, f32);
extern s32 init;
}
void* g_particleBanks;
GScamera* g_Camera;
s32 g_CameraMatrix;
s32 g_render_pass;
s32 g_particle_debug_stats;
static s8 g_afterZWriteState;
extern "C" {

extern "C" {

extern "C" {
s32 particleEnginePrepareRender(u32 p0);
s32 particleEnginePrepareUpdate(u32 p0);
void particleEngineSetupTevStages(u8 p0, u8 p1, u8 p2);
void particleEngineSetupTexture(u8 p0, void *p1, s32 p2, s32 p3, s32 p4, s32 p5);
}

void particleEngineSetupTexture(u8 slot, void* texture, s32 wrapS, s32 wrapT, s32 minFilter, s32 magFilter) {
    GStexture* tex = (GStexture*)texture;
    GStextureSetWrap(tex, wrapS, wrapT);
    GStextureSetFilter(tex, minFilter, magFilter, 0);
    u8* layer = (u8*)g_current_layer;
    u8* entry = layer + slot * 4;
    if (*(GStexture**)(entry + 0x1740) != tex || *(GStexture**)(entry + 0x17F8) != tex || M2C_FIELD(tex, u8 *, 7) != 0) {
        *(GStexture**)(entry + 0x1740) = tex;
        M2C_FIELD(layer, u32 *, 0x173C) |= 1 << slot;
        entry = layer + slot * 4;
        *(GStexture**)(entry + 0x17F8) = tex;
        M2C_FIELD(layer, u32 *, 0x17F4) |= 1 << slot;
    }
}

}
void particleEngineSetDefaultRenderState(u8 tev) {
    g_current_layer->setColorUpdate(1, 1, 0);
    g_current_layer->setZMode(1, 1);
    g_current_layer->setAlphaCompare(7, 0, 0, 7, 0, 1);
    g_current_layer->setDstAlpha(0, 0xFF);
    g_current_layer->setDither(1);
    g_current_layer->setCullMode(2);
    g_current_layer->setFd90(0);
    g_current_layer->setFd88(0);
    particleEngineSetupTevStages(tev, 0, 0);
    g_afterZWriteState = 0;
}
}
}
void particleEngineSetupBlendMode(u32 mode) {
    switch (mode) {
    case 1: {
        GSgfxLayer* l = g_current_layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 3;
        l->blendSrc = 4;
        l->blendDst = 1;
        l->blendLogic = 5;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 2: {
        GSgfxLayer* l = g_current_layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 1;
        l->blendSrc = 4;
        l->blendDst = 5;
        l->blendLogic = 5;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 3: {
        GSgfxLayer* l = g_current_layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 1;
        l->blendSrc = 1;
        l->blendDst = 0;
        l->blendLogic = 5;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 4: {
        GSgfxLayer* l = g_current_layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 2;
        l->blendSrc = 1;
        l->blendDst = 1;
        l->blendLogic = 4;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 5: {
        GSgfxLayer* l = g_current_layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 2;
        l->blendSrc = 1;
        l->blendDst = 1;
        l->blendLogic = 7;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 6: {
        GSgfxLayer* l = g_current_layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 2;
        l->blendSrc = 1;
        l->blendDst = 1;
        l->blendLogic = 1;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 7: {
        GSgfxLayer* l = g_current_layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 2;
        l->blendSrc = 1;
        l->blendDst = 1;
        l->blendLogic = 6;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 0:
    default: {
        GSgfxLayer* l = g_current_layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 1;
        l->blendSrc = 4;
        l->blendDst = 1;
        l->blendLogic = 5;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    }
}

#define LAYER_FIELD(l, T, off) (*(T*)((u8*)(l) + (off)))
static inline void layerMark(GSgfxLayer* l, u32 sum, u32 off, u32 bit) {
    LAYER_FIELD(l, u32, off) |= bit;
    LAYER_FIELD(l, u32, 0x16A8) |= sum;
    LAYER_FIELD(l, u32, off + 0xB8) |= bit;
    LAYER_FIELD(l, u32, 0x1760) |= sum;
}

extern "C" {
void particleEngineSetupTevStages(u8 p0, u8 p1, u8 p2) {
    s32 sp8;

    static u8 extensionSetup = 0;
    static u8 blendedTexturesSetup = 0;

    if ((p0 != 0) || ((u8) extensionSetup != p1) || ((u8) blendedTexturesSetup != p2)) {
        extensionSetup = p1;
        blendedTexturesSetup = p2;
        {
            GSgfxLayer* l = g_current_layer;
            LAYER_FIELD(l, s8, 0xC70) = 1;
            layerMark(l, 1, 0x16AC, 1);
        }
        ((GSgfxLayer*)(g_current_layer))->tgenFunc(0U, (GSgfxTgenFunc)(1), (GSgfxTgenSrc)(4), (GSmtx*)(NULL), 0U, (GSmtx*)(NULL));
        {
            GSgfxLayer* l = g_current_layer;
            LAYER_FIELD(l, s8, 0x14B0) = 0;
            layerMark(l, 0x80, 0x16EC, 1);
        }
        {
            GSgfxLayer* l = g_current_layer;
            LAYER_FIELD(l, s32, 0x1420) = 0;
            layerMark(l, 8, 0x16E8, 1);
        }
        {
            GSgfxLayer* l = g_current_layer;
            LAYER_FIELD(l, s8, 0xDB8) = 1;
            layerMark(l, 4, 0x16BC, 1);
        }
        sp8 = 0;
        ((GSgfxLayer*)(g_current_layer))->cunitChannelGen(0U, (GSgfxCunitAlpha)(2), (GSgfxCunitSrc)(1), (GSgfxCunitSrc)(1), 0U, (GSgfxLight**)(NULL), (GSgfxLightType)(2), (GSgfxDiffuseFunc)(M2C_ERROR( )));
        if (p2 != 0) {
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s8, 0xEAC) = 3;
                layerMark(l, 8, 0x16CC, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1584) = 0;
                LAYER_FIELD(l, s32, 0x1588) = 0;
                layerMark(l, 0x20, 0x1704, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0xEB0) = 0;
                LAYER_FIELD(l, s32, 0xEB4) = 0;
                LAYER_FIELD(l, s32, 0xEB8) = 4;
                layerMark(l, 8, 0x16D0, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1170) = 0;
                LAYER_FIELD(l, s32, 0x1174) = 0;
                LAYER_FIELD(l, s32, 0x1178) = 0;
                LAYER_FIELD(l, s8, 0x117C) = 0;
                LAYER_FIELD(l, s32, 0x1180) = 1;
                layerMark(l, 8, 0x16DC, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x12B0) = 0;
                LAYER_FIELD(l, s32, 0x12B4) = 0;
                LAYER_FIELD(l, s32, 0x12B8) = 0;
                LAYER_FIELD(l, s8, 0x12BC) = 0;
                LAYER_FIELD(l, s32, 0x12C0) = 1;
                layerMark(l, 8, 0x16E0, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0xF70) = 0xF;
                LAYER_FIELD(l, s32, 0xF74) = 0xA;
                LAYER_FIELD(l, s32, 0xF78) = 8;
                LAYER_FIELD(l, s32, 0xF7C) = 0xF;
                layerMark(l, 8, 0x16D4, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1070) = 7;
                LAYER_FIELD(l, s32, 0x1074) = 5;
                LAYER_FIELD(l, s32, 0x1078) = 4;
                LAYER_FIELD(l, s32, 0x107C) = 7;
                layerMark(l, 8, 0x16D8, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x158C) = 0;
                LAYER_FIELD(l, s32, 0x1590) = 0;
                layerMark(l, 0x20, 0x1704, 2);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0xEBC) = 0;
                LAYER_FIELD(l, s32, 0xEC0) = 1;
                LAYER_FIELD(l, s32, 0xEC4) = 4;
                layerMark(l, 8, 0x16D0, 2);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1184) = 0;
                LAYER_FIELD(l, s32, 0x1188) = 0;
                LAYER_FIELD(l, s32, 0x118C) = 0;
                LAYER_FIELD(l, s8, 0x1190) = 0;
                LAYER_FIELD(l, s32, 0x1194) = 2;
                layerMark(l, 8, 0x16DC, 2);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x12C4) = 0;
                LAYER_FIELD(l, s32, 0x12C8) = 0;
                LAYER_FIELD(l, s32, 0x12CC) = 0;
                LAYER_FIELD(l, s8, 0x12D0) = 0;
                LAYER_FIELD(l, s32, 0x12D4) = 2;
                layerMark(l, 8, 0x16E0, 2);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0xF80) = 0xF;
                LAYER_FIELD(l, s32, 0xF84) = 0xA;
                LAYER_FIELD(l, s32, 0xF88) = 8;
                LAYER_FIELD(l, s32, 0xF8C) = 0xF;
                layerMark(l, 8, 0x16D4, 2);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1080) = 7;
                LAYER_FIELD(l, s32, 0x1084) = 5;
                LAYER_FIELD(l, s32, 0x1088) = 4;
                LAYER_FIELD(l, s32, 0x108C) = 7;
                layerMark(l, 8, 0x16D8, 2);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1594) = 0;
                LAYER_FIELD(l, s32, 0x1598) = 0;
                layerMark(l, 0x20, 0x1704, 4);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0xEC8) = 0xFF;
                LAYER_FIELD(l, s32, 0xECC) = 0xFF;
                LAYER_FIELD(l, s32, 0xED0) = 0xFF;
                layerMark(l, 8, 0x16D0, 4);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1198) = 0;
                LAYER_FIELD(l, s32, 0x119C) = 0;
                LAYER_FIELD(l, s32, 0x11A0) = 0;
                LAYER_FIELD(l, s8, 0x11A4) = 1;
                LAYER_FIELD(l, s32, 0x11A8) = 0;
                layerMark(l, 8, 0x16DC, 4);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x12D8) = 0;
                LAYER_FIELD(l, s32, 0x12DC) = 0;
                LAYER_FIELD(l, s32, 0x12E0) = 0;
                LAYER_FIELD(l, s8, 0x12E4) = 1;
                LAYER_FIELD(l, s32, 0x12E8) = 0;
                layerMark(l, 8, 0x16E0, 4);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x150C) = 0xC;
                layerMark(l, 0x10, 0x16FC, 4);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x154C) = 0x1C;
                layerMark(l, 0x10, 0x1700, 4);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0xF90) = 2;
                LAYER_FIELD(l, s32, 0xF94) = 4;
                LAYER_FIELD(l, s32, 0xF98) = 0xE;
                LAYER_FIELD(l, s32, 0xF9C) = 0xF;
                layerMark(l, 8, 0x16D4, 4);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1090) = 1;
                LAYER_FIELD(l, s32, 0x1094) = 2;
                LAYER_FIELD(l, s32, 0x1098) = 6;
                LAYER_FIELD(l, s32, 0x109C) = 7;
                layerMark(l, 8, 0x16D8, 4);
            }
            if (p1 != 0) {
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1504) = 0xD;
                    layerMark(l, 0x10, 0x16FC, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xF70) = 0xE;
                    LAYER_FIELD(l, s32, 0xF74) = 0xA;
                    LAYER_FIELD(l, s32, 0xF78) = 8;
                    LAYER_FIELD(l, s32, 0xF7C) = 0xF;
                    layerMark(l, 8, 0x16D4, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1508) = 0xD;
                    layerMark(l, 0x10, 0x16FC, 2);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xF80) = 0xE;
                    LAYER_FIELD(l, s32, 0xF84) = 0xA;
                    LAYER_FIELD(l, s32, 0xF88) = 8;
                    LAYER_FIELD(l, s32, 0xF8C) = 0xF;
                    layerMark(l, 8, 0x16D4, 2);
                }
            }
        } else {
            if (p1 != 0) {
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s8, 0xDB8) = 2;
                    layerMark(l, 4, 0x16BC, 1);
                }
                sp8 = 0;
                ((GSgfxLayer*)(g_current_layer))->cunitChannelGen(1U, (GSgfxCunitAlpha)(2), (GSgfxCunitSrc)(1), (GSgfxCunitSrc)(1), 0U, (GSgfxLight**)(NULL), (GSgfxLightType)(2), (GSgfxDiffuseFunc)(M2C_ERROR( )));
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s8, 0xEAC) = 2;
                    layerMark(l, 8, 0x16CC, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1070) = 7;
                    LAYER_FIELD(l, s32, 0x1074) = 7;
                    LAYER_FIELD(l, s32, 0x1078) = 7;
                    LAYER_FIELD(l, s32, 0x107C) = 7;
                    layerMark(l, 8, 0x16D8, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1584) = 0;
                    LAYER_FIELD(l, s32, 0x1588) = 0;
                    layerMark(l, 0x20, 0x1704, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xEB0) = 0;
                    LAYER_FIELD(l, s32, 0xEB4) = 0;
                    LAYER_FIELD(l, s32, 0xEB8) = 4;
                    layerMark(l, 8, 0x16D0, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1170) = 0;
                    LAYER_FIELD(l, s32, 0x1174) = 0;
                    LAYER_FIELD(l, s32, 0x1178) = 0;
                    LAYER_FIELD(l, s8, 0x117C) = 0;
                    LAYER_FIELD(l, s32, 0x1180) = 1;
                    layerMark(l, 8, 0x16DC, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x12B4) = 0;
                    LAYER_FIELD(l, s32, 0x12B8) = 0;
                    LAYER_FIELD(l, s32, 0x12B0) = 0;
                    LAYER_FIELD(l, s8, 0x12BC) = 0;
                    LAYER_FIELD(l, s32, 0x12C0) = 1;
                    layerMark(l, 8, 0x16E0, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xF70) = 0xF;
                    LAYER_FIELD(l, s32, 0xF74) = 0xA;
                    LAYER_FIELD(l, s32, 0xF78) = 8;
                    LAYER_FIELD(l, s32, 0xF7C) = 0xF;
                    layerMark(l, 8, 0x16D4, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1070) = 7;
                    LAYER_FIELD(l, s32, 0x1074) = 5;
                    LAYER_FIELD(l, s32, 0x1078) = 4;
                    LAYER_FIELD(l, s32, 0x107C) = 7;
                    layerMark(l, 8, 0x16D8, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x158C) = 0;
                    LAYER_FIELD(l, s32, 0x1590) = 0;
                    layerMark(l, 0x20, 0x1704, 2);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xEBC) = 0;
                    LAYER_FIELD(l, s32, 0xEC0) = 0;
                    LAYER_FIELD(l, s32, 0xEC4) = 5;
                    layerMark(l, 8, 0x16D0, 2);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1184) = 0;
                    LAYER_FIELD(l, s32, 0x1188) = 0;
                    LAYER_FIELD(l, s32, 0x118C) = 0;
                    LAYER_FIELD(l, s8, 0x1190) = 1;
                    LAYER_FIELD(l, s32, 0x1194) = 0;
                    layerMark(l, 8, 0x16DC, 2);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x12C4) = 0;
                    LAYER_FIELD(l, s32, 0x12C8) = 0;
                    LAYER_FIELD(l, s32, 0x12CC) = 0;
                    LAYER_FIELD(l, s8, 0x12D0) = 1;
                    LAYER_FIELD(l, s32, 0x12D4) = 0;
                    layerMark(l, 8, 0x16E0, 2);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xF80) = 0xA;
                    LAYER_FIELD(l, s32, 0xF84) = 0xF;
                    LAYER_FIELD(l, s32, 0xF88) = 8;
                    LAYER_FIELD(l, s32, 0xF8C) = 2;
                    layerMark(l, 8, 0x16D4, 2);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1080) = 7;
                    LAYER_FIELD(l, s32, 0x1084) = 5;
                    LAYER_FIELD(l, s32, 0x1088) = 4;
                    LAYER_FIELD(l, s32, 0x108C) = 7;
                    layerMark(l, 8, 0x16D8, 2);
                }
                return;
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s8, 0xEAC) = 1;
                layerMark(l, 8, 0x16CC, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1584) = 0;
                LAYER_FIELD(l, s32, 0x1588) = 0;
                layerMark(l, 0x20, 0x1704, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0xEB0) = 0;
                LAYER_FIELD(l, s32, 0xEB4) = 0;
                LAYER_FIELD(l, s32, 0xEB8) = 4;
                layerMark(l, 8, 0x16D0, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1170) = 0;
                LAYER_FIELD(l, s32, 0x1174) = 0;
                LAYER_FIELD(l, s32, 0x1178) = 0;
                LAYER_FIELD(l, s8, 0x117C) = 1;
                LAYER_FIELD(l, s32, 0x1180) = 0;
                layerMark(l, 8, 0x16DC, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x12B0) = 0;
                LAYER_FIELD(l, s32, 0x12B4) = 0;
                LAYER_FIELD(l, s32, 0x12B8) = 0;
                LAYER_FIELD(l, s8, 0x12BC) = 1;
                LAYER_FIELD(l, s32, 0x12C0) = 0;
                layerMark(l, 8, 0x16E0, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0xF70) = 0xF;
                LAYER_FIELD(l, s32, 0xF74) = 0xA;
                LAYER_FIELD(l, s32, 0xF78) = 8;
                LAYER_FIELD(l, s32, 0xF7C) = 0xF;
                layerMark(l, 8, 0x16D4, 1);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1070) = 7;
                LAYER_FIELD(l, s32, 0x1074) = 5;
                LAYER_FIELD(l, s32, 0x1078) = 4;
                LAYER_FIELD(l, s32, 0x107C) = 7;
                layerMark(l, 8, 0x16D8, 1);
            }
        }
    }
}
}

extern "C" {
extern "C" {
void particleEngineRender(void *p0) {
    u8 *var_r31;

    var_r31 = (unsigned char *)(g_particleBanks);
    if ((u8 *) g_particleBanks != NULL) {
        g_current_layer = (GSgfxLayer *) p0;
        g_Camera = NULL;
        g_render_pass = M2C_FIELD(p0, s32 *, 0x1994);
        particleEngineSetDefaultRenderState(1);
        while (var_r31 != NULL) {
            peBankRender(var_r31);
            var_r31 = M2C_FIELD(var_r31, u8 **, 0x164);
        }
        if (((GScamera *) g_Camera != NULL) && ((GScamera *) g_Camera != GScameraGetActiveCamera())) {
            GScameraLoadActiveCameraMatrix((GSgfxLayerID)(M2C_FIELD(p0, s32 *, 0x28)));
        }
    }
}
extern "C" {
s32 particleEnginePrepareRender(u32 p0) {
    u32 var_r31;

    var_r31 = p0;
    if (GScameraIsValid((GScamera*)((GScamera *) p0)) == 0) {
        var_r31 = (unsigned long)(GScameraGetActiveCamera());
        if (var_r31 == 0) {
            g_CameraMatrix = 0;
            return 0;
        }
    }
    if ((u32)(g_Camera) == (u32)(var_r31)) {
        return 1;
    }
    g_Camera = (GScamera *) var_r31;
    g_CameraMatrix = GScameraGetMatrixPtr((GScamera*)((GScamera *) var_r31));
    if ((GSgfxLayer *) g_current_layer != NULL) {
        GScameraLoadCameraMatrix((GScamera*)((GScamera *) var_r31), (GSgfxLayerID)(M2C_FIELD(g_current_layer, s32 *, 0x28)));
    } else {
        GScameraLoadCameraMatrix((GScamera*)((GScamera *) var_r31), (GSgfxLayerID)(-1));
    }
    return 1;
}
}

}

extern "C" {
extern "C" {
void particleEnginePostUpdate() {
    u8 *var_r3;

    var_r3 = (unsigned char *)(g_particleBanks);
    while (var_r3 != NULL) {
        if (var_r3 != NULL) {
            M2C_FIELD(var_r3, s32 *, 0x138) = 0;
        }
        var_r3 = M2C_FIELD(var_r3, u8 **, 0x164);
    }
    g_Camera = NULL;
}
}

extern "C" {
void particleEngineUpdate(f32 p0) {
    u8 *var_r31;

    g_Camera = NULL;
    var_r31 = (unsigned char *)(g_particleBanks);
    while (var_r31 != NULL) {
        peBankUpdate(var_r31, p0);
        var_r31 = M2C_FIELD(var_r31, u8 **, 0x164);
    }
}
extern "C" {
s32 particleEnginePrepareUpdate(u32 p0) {
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    f32 sp78;
    f32 sp84;
    f32 sp88;
    f32 sp94;
    f32 sp98;
    f32 spC;
    u8 *temp_r4;
    f32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    f32 sp10;
    Vec *temp_r28;
    Vec *temp_r3;
    u32 var_r28;
    f32 unksp8;

    var_r28 = p0;
    if (GScameraIsValid((GScamera*)((GScamera *) p0)) == 0) {
        var_r28 = (unsigned long)(GScameraGetActiveCamera());
        if (var_r28 == 0) {
            g_CameraMatrix = 0;
            return 0;
        }
    }
    if ((u32)(g_Camera) == (u32)(var_r28)) {
        return 1;
    }
    g_Camera = (GScamera *) var_r28;
    g_CameraMatrix = GScameraGetMatrixPtr((GScamera*)((GScamera *) var_r28));
    GScameraLoadCameraMatrix((GScamera*)((GScamera *) var_r28), (GSgfxLayerID)(-1));
    GSgfxProjectSetupCameraParameters((GScamera*)((GScamera *) var_r28));
    GScameraGetPosition((GScamera*)((GScamera *) var_r28), (f32*)(&g_particle_debug_stats + 0x24));
    PSMTXTranspose((const Mtx)(g_CameraMatrix), (Mtx)((s32) &sp14));
    sp44 = sp14;
    sp48 = sp18;
    sp4C = sp1C;
    sp50 = sp20;
    sp54 = sp24;
    sp58 = sp28;
    sp5C = sp2C;
    sp60 = sp30;
    sp64 = sp34;
    sp68 = sp38;
    sp6C = sp3C;
    sp70 = sp40;
    temp_r3 = (Vec *)(&g_particle_debug_stats + 0x3C);
    temp_r28 = (Vec *)(&g_particle_debug_stats + 0x48);
    PSMTXCopy((const Mtx)((s32) &sp44), (Mtx)((s32) &sp74));
    M2C_FIELD(&g_particle_debug_stats, f32 *, 0x48) = sp74;
    M2C_FIELD(temp_r28, f32 *, 4) = sp84;
    M2C_FIELD(temp_r28, f32 *, 8) = sp94;
    M2C_FIELD(&g_particle_debug_stats, f32 *, 0x3C) = sp78;
    M2C_FIELD((u16)temp_r3, f32 *, 4) = sp88;
    M2C_FIELD((u16)temp_r3, f32 *, 8) = sp98;
    PSVECNormalize((const register Vec*)((u16)temp_r3), (register Vec*)(temp_r3));
    PSVECNormalize((const register Vec*)(temp_r28), (register Vec*)(temp_r28));
    M2C_FIELD(&g_particle_debug_stats, f32 *, 0x48) = (f32) -M2C_FIELD(&g_particle_debug_stats, f32 *, 0x48);
    M2C_FIELD(temp_r28, f32 *, 8) = (f32) -M2C_FIELD(temp_r28, f32 *, 8);
    M2C_FIELD(temp_r28, f32 *, 4) = (f32) -M2C_FIELD(temp_r28, f32 *, 4);
    M2C_FIELD(temp_r4, f32 *, 4) = spC;
    PSVECCrossProduct((const register Vec*)(temp_r28), (const register Vec*)(&g_particle_debug_stats + 0x3C), (register Vec*)(&unksp8));
    temp_r4 = (unsigned char *)(&g_particle_debug_stats + 0x30);
    M2C_FIELD(&g_particle_debug_stats, f32 *, 0x30) = unksp8;
    M2C_FIELD(temp_r4, f32 *, 8) = sp10;
    return 1;
}
}

}

extern "C" {
extern "C" {
void particleEngineInit() {
    GSgfxVFInit((GSgfxVF*)(&g_particle_debug_stats + 0x494));
    GSgfxVFCreate((GSgfxVF*)(&g_particle_debug_stats + 0x494));
    GSgfxVFSetElement((GSgfxVF*)(&g_particle_debug_stats + 0x494), 9, 1, 4, 0);
    GSgfxVFSetElement((GSgfxVF*)(&g_particle_debug_stats + 0x494), 0xB, 1, 5, 0);
    GSgfxVFSetElement((GSgfxVF*)(&g_particle_debug_stats + 0x494), 0xC, 1, 5, 0);
    GSgfxVFSetElement((GSgfxVF*)(&g_particle_debug_stats + 0x494), 0xD, 1, 4, 0);
    GSgfxVFSetArray((GSgfxVF*)(&g_particle_debug_stats + 0x494), 9, 3, (void*)(NULL), 0, -1);
    GSgfxVFSetArray((GSgfxVF*)(&g_particle_debug_stats + 0x494), 0xB, 3, (void*)(NULL), 0, -1);
    GSgfxVFSetArray((GSgfxVF*)(&g_particle_debug_stats + 0x494), 0xC, 3, (void*)(NULL), 0, -1);
    GSgfxVFSetArray((GSgfxVF*)(&g_particle_debug_stats + 0x494), 0xD, 3, (void*)(NULL), 0, -1);
    GSgfxVFInit((GSgfxVF*)(&g_particle_debug_stats + 0x54));
    GSgfxVFCreate((GSgfxVF*)(&g_particle_debug_stats + 0x54));
    GSgfxVFSetElement((GSgfxVF*)(&g_particle_debug_stats + 0x54), 9, 1, 4, 0);
    GSgfxVFSetElement((GSgfxVF*)(&g_particle_debug_stats + 0x54), 0xB, 1, 5, 0);
    GSgfxVFSetElement((GSgfxVF*)(&g_particle_debug_stats + 0x54), 0xD, 1, 4, 0);
    GSgfxVFSetArray((GSgfxVF*)(&g_particle_debug_stats + 0x54), 9, 3, (void*)(NULL), 0, -1);
    GSgfxVFSetArray((GSgfxVF*)(&g_particle_debug_stats + 0x54), 0xB, 3, (void*)(NULL), 0, -1);
    GSgfxVFSetArray((GSgfxVF*)(&g_particle_debug_stats + 0x54), 0xD, 3, (void*)(NULL), 0, -1);
    memset((void*)(&g_particle_debug_stats), 0, 0x24U);
}
}

extern "C" {
static void __sinit_particleEngine_cpp() {
}
}
}
}
}

}
