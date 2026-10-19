// Partial: particleEngineSetupBlendMode (stitched from GSprimSetBlendMode); the rest is not written yet.
#include <dolphin/types.h>
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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

// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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
    u8 pad0[0x1644];
    s32 blendOp;          // 0x1644
    s32 blendSrc;         // 0x1648
    s32 blendDst;         // 0x164C
    s32 blendLogic;       // 0x1650
    u8 pad_1654[0x16a8 - 0x1654];
    u32 dirty16a8;
    u8 pad_16ac[0x170c - 0x16ac];
    u32 dirty170c;
    u8 pad_1710[0x1760 - 0x1710];
    u32 dirty1760;
    u8 pad_1764[0x17c4 - 0x1764];
    u32 dirty17c4;
    u8 pad_17c8[0x1818 - 0x17c8];
    BlendState blendTable[2];
    BlendState* curBlend;  // 0x1990
    s32 curBlendIdx;       // 0x1994
public: // draft
    s32 cunitChannelGen(unsigned char, GSgfxCunitAlpha, GSgfxCunitSrc, GSgfxCunitSrc, unsigned long, GSgfxLight**, GSgfxLightType, GSgfxDiffuseFunc);
    s32 tgenFunc(unsigned char, GSgfxTgenFunc, GSgfxTgenSrc, GSmtx*, bool, GSmtx*);
};

extern "C" {

extern GSgfxLayer* g_current_layer;


extern "C" {
// ---- draft declarations ----
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
void particleEngineSetDefaultRenderState();
void particleEngineUpdate(f32 p0);
s32 peBankRender(void*);
s32 peBankUpdate(void*, f32);
extern s32 init;
}
GScamera* g_Camera;
s32 g_CameraMatrix;
static s8 g_afterZWriteState;
void* g_particleBanks;
s32 g_particle_debug_stats;
s32 g_render_pass;
extern "C" {

extern "C" {
// ---- draft declarations ----


extern "C" {
s32 particleEnginePrepareRender(u32 p0);
s32 particleEnginePrepareUpdate(u32 p0);
void particleEngineSetupTevStages(u8 p0, u8 p1, u8 p2);
void particleEngineSetupTexture(u8 p0, void *p1, s32 p2, s32 p3, s32 p4, s32 p5);
}
static u8 blendedTexturesSetup_S1951;
static u8 extensionSetup_S1948;
static u8 init_S1949;
static u8 init_S1952;
void particleEngineSetupTexture(u8 p0, void *p1, s32 p2, s32 p3, s32 p4, s32 p5) {
    s32 temp_r3_2;
    s32 temp_r4;
    u8 *temp_r3;
    u8 *temp_r4_2;

    GStextureSetWrap((GStexture*)((GStexture *) p1), (u32) p2, (u32) p3);
    GStextureSetFilter((GStexture*)((GStexture *) p1), p4, p5, 0U);
    temp_r4 = (p0 * 4) & 0x3FC;
    temp_r3 = (unsigned char *)(g_current_layer + temp_r4);
    if (((u32) M2C_FIELD(temp_r3, u32 *, 0x1740) != (u32)(p1)) || ((u32) M2C_FIELD(temp_r3, u32 *, 0x17F8) != (u32)(p1)) || ((u8) M2C_FIELD(p1, u8 *, 7) != 0)) {
        temp_r4_2 = (unsigned char *)(g_current_layer + temp_r4);
        M2C_FIELD(temp_r4_2, u8 **, 0x1740) = (unsigned char *)(p1);
        temp_r3_2 = 1 << p0;
        M2C_FIELD(g_current_layer, s32 *, 0x173C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x173C) | temp_r3_2);
        M2C_FIELD(temp_r4_2, u8 **, 0x17F8) = (unsigned char *)(p1);
        M2C_FIELD(g_current_layer, s32 *, 0x17F4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17F4) | temp_r3_2);
    }
}
}
void particleEngineSetDefaultRenderState() {
    M2C_FIELD(g_current_layer, u8 *, 0x1656) = 1;
    M2C_FIELD(g_current_layer, u8 *, 0x1657) = 1;
    M2C_FIELD(g_current_layer, u8 *, 0x1658) = 0;
    M2C_FIELD(g_current_layer, s32 *, 0x170C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x170C) | 4);
    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(g_current_layer, s32 *, 0x17C4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17C4) | 4);
    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x40);
    M2C_FIELD(g_current_layer, u8 *, 0x165C) = 1;
    M2C_FIELD(g_current_layer, s32 *, 0x1660) = 1;
    M2C_FIELD(g_current_layer, s32 *, 0x170C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x170C) | 8);
    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(g_current_layer, s32 *, 0x17C4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17C4) | 8);
    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x40);
    M2C_FIELD(g_current_layer, s32 *, 0x1664) = 7;
    M2C_FIELD(g_current_layer, u8 *, 0x1670) = 0;
    M2C_FIELD(g_current_layer, s32 *, 0x1668) = 0;
    M2C_FIELD(g_current_layer, s32 *, 0x166C) = 7;
    M2C_FIELD(g_current_layer, u8 *, 0x1671) = 0;
    M2C_FIELD(g_current_layer, u8 *, 0x1672) = 1;
    M2C_FIELD(g_current_layer, s32 *, 0x170C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x170C) | 0x10);
    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(g_current_layer, s32 *, 0x17C4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17C4) | 0x10);
    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x40);
    M2C_FIELD(g_current_layer, u8 *, 0x1654) = 0;
    M2C_FIELD(g_current_layer, u8 *, 0x1655) = 0xFF;
    M2C_FIELD(g_current_layer, s32 *, 0x170C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x170C) | 2);
    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(g_current_layer, s32 *, 0x17C4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17C4) | 2);
    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x40);
    M2C_FIELD(g_current_layer, u8 *, 0x1674) = 1;
    M2C_FIELD(g_current_layer, s32 *, 0x170C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x170C) | 0x20);
    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(g_current_layer, s32 *, 0x17C4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17C4) | 0x20);
    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x40);
    M2C_FIELD(g_current_layer, s32 *, 0xD8C) = 2;
    M2C_FIELD(g_current_layer, s32 *, 0x16B8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16B8) | 2);
    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 2);
    M2C_FIELD(g_current_layer, s32 *, 0x1770) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1770) | 2);
    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 2);
    M2C_FIELD(g_current_layer, s32 *, 0xD90) = 0;
    M2C_FIELD(g_current_layer, s32 *, 0x16B8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16B8) | 4);
    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 2);
    M2C_FIELD(g_current_layer, s32 *, 0x1770) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1770) | 4);
    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 2);
    M2C_FIELD(g_current_layer, u8 *, 0xD88) = 0;
    M2C_FIELD(g_current_layer, s32 *, 0x16B8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16B8) | 8);
    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 2);
    M2C_FIELD(g_current_layer, s32 *, 0x1770) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1770) | 8);
    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 2);
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
extern "C" {
void particleEngineSetupTevStages(u8 p0, u8 p1, u8 p2) {
    s32 sp8;

    if ((s8) init_S1949 == 0) {
        extensionSetup_S1948 = 0;
        init_S1949 = 1;
    }
    if ((s8) init_S1952 == 0) {
        blendedTexturesSetup_S1951 = 0;
        init_S1952 = 1;
    }
    if ((p0 != 0) || ((u8) extensionSetup_S1948 != p1) || ((u8) blendedTexturesSetup_S1951 != p2)) {
        extensionSetup_S1948 = p1;
        blendedTexturesSetup_S1951 = p2;
        M2C_FIELD(g_current_layer, s8 *, 0xC70) = 1;
        M2C_FIELD(g_current_layer, s32 *, 0x16AC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16AC) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x1764) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1764) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 1);
        ((GSgfxLayer*)(g_current_layer))->tgenFunc(0U, (GSgfxTgenFunc)(1), (GSgfxTgenSrc)(4), (GSmtx*)(NULL), 0U, (GSmtx*)(NULL));
        M2C_FIELD(g_current_layer, s8 *, 0x14B0) = 0;
        M2C_FIELD(g_current_layer, s32 *, 0x16EC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16EC) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x80);
        M2C_FIELD(g_current_layer, s32 *, 0x17A4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17A4) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x80);
        M2C_FIELD(g_current_layer, s32 *, 0x1420) = 0;
        M2C_FIELD(g_current_layer, s32 *, 0x16E8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E8) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
        M2C_FIELD(g_current_layer, s32 *, 0x17A0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17A0) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
        M2C_FIELD(g_current_layer, s8 *, 0xDB8) = 1;
        M2C_FIELD(g_current_layer, s32 *, 0x16BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16BC) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 4);
        M2C_FIELD(g_current_layer, s32 *, 0x1774) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1774) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 4);
        sp8 = 0;
        ((GSgfxLayer*)(g_current_layer))->cunitChannelGen(0U, (GSgfxCunitAlpha)(2), (GSgfxCunitSrc)(1), (GSgfxCunitSrc)(1), 0U, (GSgfxLight**)(NULL), (GSgfxLightType)(2), (GSgfxDiffuseFunc)(M2C_ERROR(/* Unable to find stack arg 0x0 in block */)));
        if (p2 != 0) {
            M2C_FIELD(g_current_layer, s8 *, 0xEAC) = 3;
            M2C_FIELD(g_current_layer, s32 *, 0x16CC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16CC) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1784) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1784) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1584) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1588) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1704) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1704) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x20);
            M2C_FIELD(g_current_layer, s32 *, 0x17BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17BC) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x20);
            M2C_FIELD(g_current_layer, s32 *, 0xEB0) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0xEB4) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0xEB8) = 4;
            M2C_FIELD(g_current_layer, s32 *, 0x16D0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D0) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1788) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1788) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1170) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1174) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1178) = 0;
            M2C_FIELD(g_current_layer, s8 *, 0x117C) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1180) = 1;
            M2C_FIELD(g_current_layer, s32 *, 0x16DC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16DC) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1794) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1794) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x12B0) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12B4) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12B8) = 0;
            M2C_FIELD(g_current_layer, s8 *, 0x12BC) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12C0) = 1;
            M2C_FIELD(g_current_layer, s32 *, 0x16E0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E0) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1798) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1798) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0xF70) = 0xF;
            M2C_FIELD(g_current_layer, s32 *, 0xF74) = 0xA;
            M2C_FIELD(g_current_layer, s32 *, 0xF78) = 8;
            M2C_FIELD(g_current_layer, s32 *, 0xF7C) = 0xF;
            M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1070) = 7;
            M2C_FIELD(g_current_layer, s32 *, 0x1074) = 5;
            M2C_FIELD(g_current_layer, s32 *, 0x1078) = 4;
            M2C_FIELD(g_current_layer, s32 *, 0x107C) = 7;
            M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x158C) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1590) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1704) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1704) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x20);
            M2C_FIELD(g_current_layer, s32 *, 0x17BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17BC) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x20);
            M2C_FIELD(g_current_layer, s32 *, 0xEBC) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0xEC0) = 1;
            M2C_FIELD(g_current_layer, s32 *, 0xEC4) = 4;
            M2C_FIELD(g_current_layer, s32 *, 0x16D0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D0) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1788) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1788) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1184) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1188) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x118C) = 0;
            M2C_FIELD(g_current_layer, s8 *, 0x1190) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1194) = 2;
            M2C_FIELD(g_current_layer, s32 *, 0x16DC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16DC) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1794) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1794) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x12C4) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12C8) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12CC) = 0;
            M2C_FIELD(g_current_layer, s8 *, 0x12D0) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12D4) = 2;
            M2C_FIELD(g_current_layer, s32 *, 0x16E0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E0) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1798) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1798) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0xF80) = 0xF;
            M2C_FIELD(g_current_layer, s32 *, 0xF84) = 0xA;
            M2C_FIELD(g_current_layer, s32 *, 0xF88) = 8;
            M2C_FIELD(g_current_layer, s32 *, 0xF8C) = 0xF;
            M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1080) = 7;
            M2C_FIELD(g_current_layer, s32 *, 0x1084) = 5;
            M2C_FIELD(g_current_layer, s32 *, 0x1088) = 4;
            M2C_FIELD(g_current_layer, s32 *, 0x108C) = 7;
            M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1594) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1598) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1704) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1704) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x20);
            M2C_FIELD(g_current_layer, s32 *, 0x17BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17BC) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x20);
            M2C_FIELD(g_current_layer, s32 *, 0xEC8) = 0xFF;
            M2C_FIELD(g_current_layer, s32 *, 0xECC) = 0xFF;
            M2C_FIELD(g_current_layer, s32 *, 0xED0) = 0xFF;
            M2C_FIELD(g_current_layer, s32 *, 0x16D0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D0) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1788) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1788) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1198) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x119C) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x11A0) = 0;
            M2C_FIELD(g_current_layer, s8 *, 0x11A4) = 1;
            M2C_FIELD(g_current_layer, s32 *, 0x11A8) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x16DC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16DC) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1794) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1794) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x12D8) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12DC) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12E0) = 0;
            M2C_FIELD(g_current_layer, s8 *, 0x12E4) = 1;
            M2C_FIELD(g_current_layer, s32 *, 0x12E8) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x16E0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E0) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1798) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1798) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x150C) = 0xC;
            M2C_FIELD(g_current_layer, s32 *, 0x16FC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16FC) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x10);
            M2C_FIELD(g_current_layer, s32 *, 0x17B4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17B4) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x10);
            M2C_FIELD(g_current_layer, s32 *, 0x154C) = 0x1C;
            M2C_FIELD(g_current_layer, s32 *, 0x1700) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1700) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x10);
            M2C_FIELD(g_current_layer, s32 *, 0x17B8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17B8) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x10);
            M2C_FIELD(g_current_layer, s32 *, 0xF90) = 2;
            M2C_FIELD(g_current_layer, s32 *, 0xF94) = 4;
            M2C_FIELD(g_current_layer, s32 *, 0xF98) = 0xE;
            M2C_FIELD(g_current_layer, s32 *, 0xF9C) = 0xF;
            M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD((u8)g_current_layer, s32 *, 0x178C) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1090) = 1;
            M2C_FIELD(g_current_layer, s32 *, 0x1094) = 2;
            M2C_FIELD(g_current_layer, s32 *, 0x1098) = 6;
            M2C_FIELD(g_current_layer, s32 *, 0x109C) = 7;
            M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            if (p1 != 0) {
                M2C_FIELD(g_current_layer, s32 *, 0x1504) = 0xD;
                M2C_FIELD(g_current_layer, s32 *, 0x16FC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16FC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x10);
                M2C_FIELD(g_current_layer, s32 *, 0x17B4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17B4) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x10);
                M2C_FIELD(g_current_layer, s32 *, 0xF70) = 0xE;
                M2C_FIELD(g_current_layer, s32 *, 0xF74) = 0xA;
                M2C_FIELD(g_current_layer, s32 *, 0xF78) = 8;
                M2C_FIELD(g_current_layer, s32 *, 0xF7C) = 0xF;
                M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1508) = 0xD;
                M2C_FIELD(g_current_layer, s32 *, 0x16FC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16FC) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x10);
                M2C_FIELD(g_current_layer, s32 *, 0x17B4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17B4) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x10);
                M2C_FIELD(g_current_layer, s32 *, 0xF80) = 0xE;
                M2C_FIELD(g_current_layer, s32 *, 0xF84) = 0xA;
                M2C_FIELD(g_current_layer, s32 *, 0xF88) = 8;
                M2C_FIELD(g_current_layer, s32 *, 0xF8C) = 0xF;
                M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            }
        } else {
            if (p1 != 0) {
                M2C_FIELD(g_current_layer, s8 *, 0xDB8) = 2;
                M2C_FIELD(g_current_layer, s32 *, 0x16BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16BC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 4);
                M2C_FIELD(g_current_layer, s32 *, 0x1774) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1774) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 4);
                sp8 = 0;
                ((GSgfxLayer*)(g_current_layer))->cunitChannelGen(1U, (GSgfxCunitAlpha)(2), (GSgfxCunitSrc)(1), (GSgfxCunitSrc)(1), 0U, (GSgfxLight**)(NULL), (GSgfxLightType)(2), (GSgfxDiffuseFunc)(M2C_ERROR(/* Unable to find stack arg 0x0 in block */)));
                M2C_FIELD(g_current_layer, s8 *, 0xEAC) = 2;
                M2C_FIELD(g_current_layer, s32 *, 0x16CC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16CC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1784) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1784) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1070) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x1074) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x1078) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x107C) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1584) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1588) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1704) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1704) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x20);
                M2C_FIELD(g_current_layer, s32 *, 0x17BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17BC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x20);
                M2C_FIELD(g_current_layer, s32 *, 0xEB0) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0xEB4) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0xEB8) = 4;
                M2C_FIELD(g_current_layer, s32 *, 0x16D0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D0) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1788) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1788) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1170) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1174) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1178) = 0;
                M2C_FIELD(g_current_layer, s8 *, 0x117C) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1180) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x16DC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16DC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1794) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1794) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x12B0) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x12B4) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x12B8) = 0;
                M2C_FIELD(g_current_layer, s8 *, 0x12BC) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x12C0) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x16E0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E0) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1798) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1798) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0xF70) = 0xF;
                M2C_FIELD(g_current_layer, s32 *, 0xF74) = 0xA;
                M2C_FIELD(g_current_layer, s32 *, 0xF78) = 8;
                M2C_FIELD(g_current_layer, s32 *, 0xF7C) = 0xF;
                M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1070) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x1074) = 5;
                M2C_FIELD(g_current_layer, s32 *, 0x1078) = 4;
                M2C_FIELD(g_current_layer, s32 *, 0x107C) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x158C) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1590) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1704) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1704) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x20);
                M2C_FIELD(g_current_layer, s32 *, 0x17BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17BC) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x20);
                M2C_FIELD(g_current_layer, s32 *, 0xEBC) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0xEC0) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0xEC4) = 5;
                M2C_FIELD(g_current_layer, s32 *, 0x16D0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D0) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1788) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1788) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1184) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1188) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x118C) = 0;
                M2C_FIELD(g_current_layer, s8 *, 0x1190) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x1194) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x16DC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16DC) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1794) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1794) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x12C4) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x12C8) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x12CC) = 0;
                M2C_FIELD(g_current_layer, s8 *, 0x12D0) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x12D4) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x16E0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E0) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1798) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1798) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0xF80) = 0xA;
                M2C_FIELD(g_current_layer, s32 *, 0xF84) = 0xF;
                M2C_FIELD(g_current_layer, s32 *, 0xF88) = 8;
                M2C_FIELD(g_current_layer, s32 *, 0xF8C) = 2;
                M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1080) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x1084) = 5;
                M2C_FIELD(g_current_layer, s32 *, 0x1088) = 4;
                M2C_FIELD(g_current_layer, s32 *, 0x108C) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                return;
            }
            M2C_FIELD(g_current_layer, s8 *, 0xEAC) = 1;
            M2C_FIELD(g_current_layer, s32 *, 0x16CC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16CC) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1784) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1784) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1584) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1588) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1704) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1704) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x20);
            M2C_FIELD(g_current_layer, s32 *, 0x17BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17BC) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x20);
            M2C_FIELD(g_current_layer, s32 *, 0xEB0) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0xEB4) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0xEB8) = 4;
            M2C_FIELD(g_current_layer, s32 *, 0x16D0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D0) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1788) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1788) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1170) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1174) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x1178) = 0;
            M2C_FIELD(g_current_layer, s8 *, 0x117C) = 1;
            M2C_FIELD(g_current_layer, s32 *, 0x1180) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x16DC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16DC) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1794) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1794) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x12B0) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12B4) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x12B8) = 0;
            M2C_FIELD(g_current_layer, s8 *, 0x12BC) = 1;
            M2C_FIELD(g_current_layer, s32 *, 0x12C0) = 0;
            M2C_FIELD(g_current_layer, s32 *, 0x16E0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E0) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1798) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1798) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0xF70) = 0xF;
            M2C_FIELD(g_current_layer, s32 *, 0xF74) = 0xA;
            M2C_FIELD(g_current_layer, s32 *, 0xF78) = 8;
            M2C_FIELD(g_current_layer, s32 *, 0xF7C) = 0xF;
            M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1070) = 7;
            M2C_FIELD(g_current_layer, s32 *, 0x1074) = 5;
            M2C_FIELD(g_current_layer, s32 *, 0x1078) = 4;
            M2C_FIELD(g_current_layer, s32 *, 0x107C) = 7;
            M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
            M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 1);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
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
        g_render_pass = M2C_FIELD((u16)p0, s32 *, 0x1994);
        particleEngineSetDefaultRenderState();
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
    f32 sp10;
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
    f32 unksp8;
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
    s32 sp14;
    Vec *temp_r28;
    Vec *temp_r3;
    u32 var_r28;
    u8 *temp_r4;

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
    PSMTXCopy((const Mtx)((s32) &sp44), (Mtx)((s32) &sp74));
    temp_r3 = (Vec *)(&g_particle_debug_stats + 0x3C);
    temp_r28 = (Vec *)(&g_particle_debug_stats + 0x48);
    M2C_FIELD(&g_particle_debug_stats, f32 *, 0x48) = sp74;
    M2C_FIELD(temp_r28, f32 *, 4) = sp84;
    M2C_FIELD(temp_r28, f32 *, 8) = sp94;
    M2C_FIELD(&g_particle_debug_stats, f32 *, 0x3C) = sp78;
    M2C_FIELD(temp_r3, f32 *, 4) = sp88;
    M2C_FIELD(temp_r3, f32 *, 8) = sp98;
    PSVECNormalize((const register Vec*)(temp_r3), (register Vec*)(temp_r3));
    PSVECNormalize((const register Vec*)(temp_r28), (register Vec*)(temp_r28));
    M2C_FIELD(&g_particle_debug_stats, f32 *, 0x48) = (f32) -M2C_FIELD(&g_particle_debug_stats, f32 *, 0x48);
    M2C_FIELD(temp_r28, f32 *, 4) = (f32) -M2C_FIELD(temp_r28, f32 *, 4);
    M2C_FIELD(temp_r28, f32 *, 8) = (f32) -M2C_FIELD(temp_r28, f32 *, 8);
    PSVECCrossProduct((const register Vec*)(temp_r28), (const register Vec*)(&g_particle_debug_stats + 0x3C), (register Vec*)(&unksp8));
    temp_r4 = (unsigned char *)(&g_particle_debug_stats + 0x30);
    M2C_FIELD(&g_particle_debug_stats, f32 *, 0x30) = unksp8;
    M2C_FIELD(temp_r4, f32 *, 4) = spC;
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
