#include <dolphin/types.h>
#include <game/pcret.h>
#ifdef __MWERKS__
typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
    s8 s8;
    s16 s16;
    s32 s32;
    f32 f32;
} PPCWGPipe;
volatile PPCWGPipe GXWGFifo : 0xCC008000;
#endif

#ifndef __MWERKS__
extern "C" void GXCallDisplayList(const void* list, u32 nbytes);
#endif
static inline void _layerCallDisplayList(u8* list, u32 size)
{
#ifdef __MWERKS__
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u32 = (u32)list;
    GXWGFifo.u32 = size;
#else
    GXCallDisplayList(list, size);
#endif
}
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
enum GSgfxCunitAlpha { GSgfxCunitAlpha_draft_dummy };
enum GSgfxCunitSrc { GSgfxCunitSrc_draft_dummy };
struct GSgfxDL;
enum GSgfxDiffuseFunc { GSgfxDiffuseFunc_draft_dummy };
enum GSgfxIndTexMtxID { GSgfxIndTexMtxID_draft_dummy };
struct GSgfxLayer;
struct GSgfxLight;
enum GSgfxLightType { GSgfxLightType_draft_dummy };
enum GSgfxTgenFunc { GSgfxTgenFunc_draft_dummy };
enum GSgfxTgenSrc { GSgfxTgenSrc_draft_dummy };
enum GSgfxTunitFunc { GSgfxTunitFunc_draft_dummy };
struct GSmtx;
enum GXTexMtxType { GXTexMtxType_draft_dummy };
struct GXVtxDescList;

extern "C" u8 gsgfx_layer_inPrimitive;

enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxLayerType { GSgfxLayerType_draft_dummy };
struct GSgfxVF;
#include <game/gsgfxlayer.h>

#ifdef __MWERKS__
struct GSgfxLayer {
#else
struct GSgfxLayer : public GSgfxLayerData {
#endif
public:
    void endSurface();
public:
    u16 tokenMark();
    void tunitIndTexMtx(GSgfxIndTexMtxID, float(*)[3], signed char);
    void drawOctahedron();
    void dlDraw(GSgfxDL*);
    void drawDodecaedron();
    void tgenFunc(unsigned char, GSgfxTgenFunc, GSgfxTgenSrc, GSmtx*, bool, GSmtx*);
    void cunitChannelGen(unsigned char, GSgfxCunitAlpha, GSgfxCunitSrc, GSgfxCunitSrc, u32, GSgfxLight**, GSgfxLightType, GSgfxDiffuseFunc);
    void drawIcosahedron();
    void SetDistortionParams(float(*)[3], signed char);
    void beginSurface(unsigned short);
    void drawCube();
    void drawSphere(unsigned char, unsigned char);
    void InvalidateState();
    void drawCylinder(unsigned char);
#ifdef __MWERKS__
    s32 SetupFifo();
#else
    void SetupFifo();
#endif
    void drawSphere(unsigned char);
    void FlushState();
    void tunitFunc(unsigned char, GSgfxTunitFunc);
    void drawTorus(float, unsigned char, unsigned char);
    void dlDrawExt(unsigned char*, u32);
};

#ifdef __MWERKS__
struct GSgfxDL {
    u8 _draft[1];
};
#define DL_F(d, T, off, member) M2C_FIELD(d, T, off)
#define DL_VF(d) ((s32) M2C_FIELD(d, s32 *, 0xC))
typedef s32 LAYER_VF_SAVE;
#define LAYER_VF_ADDR(l) M2C_FIELD(l, s32 *, 0x199C)
#define LAYER_VF_GET(l) M2C_FIELD(l, s32 *, 0x199C)
#define LAYER_VF_SET(l, v) (M2C_FIELD(l, s32 *, 0x199C) = (v))
#define LAYER_PASS_DATA(l, i) ((GSgfxPassFifo*)((u8*)(l) + 0x1818))[i].data
#else
struct GSgfxDL {
    u16 flags;
    u16 stride;
    u8* data;
    u32 size;
    GSgfxVF* vf;
};
#define DL_F(d, T, off, member) (*(T)&(d)->member)
#define DL_VF(d) ((d)->vf)
typedef GSgfxVF* LAYER_VF_SAVE;
#define LAYER_VF_ADDR(l) ((u8*)(l)->curVF)
#define LAYER_VF_GET(l) ((l)->curVF)
#define LAYER_VF_SET(l, v) ((l)->curVF = (v))
#define LAYER_PASS_DATA(l, i) ((l)->passes[i].data)
#endif
struct GSgfxLight {
    u8 _draft[1];
};
struct GSmtx {
    u8 _draft[1];
};
struct GXVtxDescList {
    u8 _draft[1];
};

extern "C" {
asm void DCStoreRange(register void* addr, register u32 nBytes);
s32 GSgfx_GCWriteIndTexMtx(GSgfxIndTexMtxID, f32 (*)[3], PCARG(s8, s32));
void GXDrawCube(void);
void GXDrawCylinder(u8 numEdges);
void GXDrawDodeca(void);
void GXDrawIcosahedron(void);
void GXDrawOctahedron(void);
void GXDrawSphere(u8 numMajor, u8 numMinor);
void GXDrawSphere1(u8 depth);
void GXDrawTorus(f32 rc, u8 numc, u8 numt);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXSetVtxDescv(const GXVtxDescList *attrPtr);
void* memset(void* dst, int val, size_t n);
extern s32 this_;
}
extern "C++" {
u16 GSgfxTokenMark_Sub();
}

extern "C++" {
void GSgfxLayer::SetDistortionParams(float(*p0)[3], signed char p1) {
    LAYER_F(this, f32 *, 0x19BC, distParams[0]) = (f32) M2C_FIELD(p0, f32 *, 0);
    LAYER_F(this, f32 *, 0x19C0, distParams[1]) = (f32) M2C_FIELD(p0, f32 *, 4);
    LAYER_F(this, f32 *, 0x19C4, distParams[2]) = (f32) M2C_FIELD(p0, f32 *, 8);
    LAYER_F(this, f32 *, 0x19C8, distParams[3]) = (f32) M2C_FIELD(p0, f32 *, 0xC);
    LAYER_F(this, f32 *, 0x19CC, distParams[4]) = (f32) M2C_FIELD(p0, f32 *, 0x10);
    LAYER_F(this, f32 *, 0x19D0, distParams[5]) = (f32) M2C_FIELD(p0, f32 *, 0x14);
    LAYER_F(this, s8 *, 0x19B8, distFlag) = p1;
}
}

extern "C++" {
u16 GSgfxLayer::tokenMark() {
    ((GSgfxLayer*)(this))->SetupFifo();
    return GSgfxTokenMark_Sub();
}
}

extern "C++" {
struct GSgfxPassFifo {
    void* data;
    u8 rest[0xB8];
};

void GSgfxLayer::tunitIndTexMtx(GSgfxIndTexMtxID id, float (*mtx)[3], signed char scale) {
    s32 cur;
    s32 other;

    SetupFifo();
    GSgfx_GCWriteIndTexMtx(id, mtx, scale);
    cur = LAYER_F(this, s32*, 0x1994, curPass);
    other = cur == 0;
    if (LAYER_PASS_DATA(this, other) != 0) {
        if (cur != other) {
            LAYER_F(this, s32*, 0x1994, curPass) = other;
            LAYER_F(this, u8**, 0x1990, curFifo) = LAYER_CUR_PASS(this);
        }
        SetupFifo();
        GSgfx_GCWriteIndTexMtx(id, mtx, scale);
        if (LAYER_F(this, s32*, 0x1994, curPass) != cur) {
            LAYER_F(this, s32*, 0x1994, curPass) = cur;
            LAYER_F(this, u8**, 0x1990, curFifo) = LAYER_CUR_PASS(this);
        }
        SetupFifo();
    }
}
}

extern "C++" {
struct GSgfxTgenState {
    s32 func;
    s32 src;
    s32 mtxId;
    u8 normalize;
    s32 postMtxId;
#ifdef __MWERKS__
    s32 unk14;
#else
    u8* unk14;
#endif
};

struct GSgfxLayerTgenView {
#ifdef __MWERKS__
    u8 unk0[0xC74];
#endif
    GSgfxTgenState tgen[8];
};

#ifdef __MWERKS__
#define TGEN_VIEW(l) ((GSgfxLayerTgenView*)(l))
#else
#define TGEN_VIEW(l) ((GSgfxLayerTgenView*)(l)->hw.texGen)
#endif
#define TGEN(id) (TGEN_VIEW(this)->tgen[id])
#define FIFO_INDEX LAYER_F(this, s32*, 0x1994, curPass)

static inline void tgenLoadMtx(GSgfxLayer* layer, u8 id, GSgfxTgenFunc func, GSmtx* mtx, GSmtx* postMtx) {
    GSgfxLayerTgenView* view = TGEN_VIEW(layer);
    if (mtx != NULL) {
        if (func == 1) {
            GXLoadTexMtxImm((const f32(*)[4])mtx, view->tgen[id].mtxId, (GXTexMtxType)1);
        } else {
            GXLoadTexMtxImm((const f32(*)[4])mtx, view->tgen[id].mtxId, (GXTexMtxType)0);
        }
    }
    if (postMtx != NULL) {
        GXLoadTexMtxImm((const f32(*)[4])mtx, view->tgen[id].postMtxId, (GXTexMtxType)0);
    }
}

void GSgfxLayer::tgenFunc(unsigned char id, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* mtx, bool normalize, GSmtx* postMtx) {
    u8 load = 0;
    s32 cur;
    s32 other;

    TGEN(id).func = func;
    TGEN(id).src = src;
    TGEN(id).normalize = normalize;
    TGEN(id).unk14 = 0;
    if (mtx == NULL) {
        TGEN(id).mtxId = 0x3C;
    } else {
        load = 1;
        TGEN(id).mtxId = id * 3 + 0x1E;
    }
    if (postMtx == NULL) {
        TGEN(id).postMtxId = 0x7D;
    } else {
        load = 1;
        TGEN(id).postMtxId = id * 3 + 0x40;
    }
    if (load == 1) {
        SetupFifo();
        tgenLoadMtx(this, id, func, mtx, postMtx);
        cur = FIFO_INDEX;
        other = cur == 0;
        if (LAYER_PASS_DATA(this, other) != 0) {
            if (cur != other) {
                FIFO_INDEX = other;
                LAYER_F(this, u8**, 0x1990, curFifo) = LAYER_CUR_PASS(this);
            }
            SetupFifo();
            tgenLoadMtx(this, id, func, mtx, postMtx);
            if (FIFO_INDEX != cur) {
                FIFO_INDEX = cur;
                LAYER_F(this, u8**, 0x1990, curFifo) = LAYER_CUR_PASS(this);
            }
            SetupFifo();
        }
    }
    LAYER_F(this, u32*, 0x16B0, dirty[0].texGen) |= 1 << id;
    LAYER_F(this, u32*, 0x16A8, dirty[0].groups) |= 1;
    LAYER_F(this, u32*, 0x1768, dirty[1].texGen) |= 1 << id;
    LAYER_F(this, u32*, 0x1760, dirty[1].groups) |= 1;
}

#undef TGEN
#undef FIFO_INDEX
}

extern "C++" {
struct GSgfxTevColorOpState {
    s32 op;
    s32 bias;
    s32 scale;
    u8 clamp;
    s32 outReg;
};

struct GSgfxTevInState {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
};

struct GSgfxLayerTevView {
#ifdef __MWERKS__
    u8 unk0[0xF70];
#endif
    GSgfxTevInState colorIn[16];
    GSgfxTevInState alphaIn[16];
    GSgfxTevColorOpState colorOp[16];
    GSgfxTevColorOpState alphaOp[16];
};

#ifdef __MWERKS__
#define TEV (((GSgfxLayerTevView*)layer))
#else
#define TEV (((GSgfxLayerTevView*)layer->hw.colorIn))
#endif

static inline void tevColorOp(GSgfxLayer* layer, u8 id, s32 op, s32 bias, s32 scale, u8 clamp, s32 outReg) {
    TEV->colorOp[id].op = op;
    TEV->colorOp[id].bias = bias;
    TEV->colorOp[id].scale = scale;
    TEV->colorOp[id].clamp = clamp;
    TEV->colorOp[id].outReg = outReg;
    LAYER_F(layer, u32*, 0x16DC, dirty[0].colorOp) |= 1 << id;
    LAYER_F(layer, u32*, 0x16A8, dirty[0].groups) |= 8;
    LAYER_F(layer, u32*, 0x1794, dirty[1].colorOp) |= 1 << id;
    LAYER_F(layer, u32*, 0x1760, dirty[1].groups) |= 8;
}

static inline void tevColorIn(GSgfxLayer* layer, u8 id, s32 a, s32 b, s32 c, s32 d) {
    TEV->colorIn[id].a = a;
    TEV->colorIn[id].b = b;
    TEV->colorIn[id].c = c;
    TEV->colorIn[id].d = d;
    LAYER_F(layer, u32*, 0x16D4, dirty[0].colorIn) |= 1 << id;
    LAYER_F(layer, u32*, 0x16A8, dirty[0].groups) |= 8;
    LAYER_F(layer, u32*, 0x178C, dirty[1].colorIn) |= 1 << id;
    LAYER_F(layer, u32*, 0x1760, dirty[1].groups) |= 8;
}

static inline void tevAlphaOp(GSgfxLayer* layer, u8 id, s32 op, s32 bias, s32 scale, u8 clamp, s32 outReg) {
    TEV->alphaOp[id].op = op;
    TEV->alphaOp[id].bias = bias;
    TEV->alphaOp[id].scale = scale;
    TEV->alphaOp[id].clamp = clamp;
    TEV->alphaOp[id].outReg = outReg;
    LAYER_F(layer, u32*, 0x16E0, dirty[0].alphaOp) |= 1 << id;
    LAYER_F(layer, u32*, 0x16A8, dirty[0].groups) |= 8;
    LAYER_F(layer, u32*, 0x1798, dirty[1].alphaOp) |= 1 << id;
    LAYER_F(layer, u32*, 0x1760, dirty[1].groups) |= 8;
}

static inline void tevAlphaIn(GSgfxLayer* layer, u8 id, s32 a, s32 b, s32 c, s32 d) {
    TEV->alphaIn[id].a = a;
    TEV->alphaIn[id].b = b;
    TEV->alphaIn[id].c = c;
    TEV->alphaIn[id].d = d;
    LAYER_F(layer, u32*, 0x16D8, dirty[0].alphaIn) |= 1 << id;
    LAYER_F(layer, u32*, 0x16A8, dirty[0].groups) |= 8;
    LAYER_F(layer, u32*, 0x1790, dirty[1].alphaIn) |= 1 << id;
    LAYER_F(layer, u32*, 0x1760, dirty[1].groups) |= 8;
}

#undef TEV

void GSgfxLayer::tunitFunc(unsigned char id, GSgfxTunitFunc func) {
    switch (func) {
    case 0:
        tevColorOp(this, id, 0, 0, 0, 1, 0);
        tevColorIn(this, id, 0xf, 0xa, 8, 0xf);
        tevAlphaOp(this, id, 0, 0, 0, 1, 0);
        tevAlphaIn(this, id, 7, 5, 4, 7);
        break;
    case 1:
        tevColorOp(this, id, 0, 0, 0, 1, 0);
        tevColorIn(this, id, 0xa, 8, 9, 0xf);
        tevAlphaOp(this, id, 0, 0, 0, 1, 0);
        tevAlphaIn(this, id, 7, 7, 7, 5);
        break;
    case 2:
        tevColorOp(this, id, 0, 0, 0, 1, 0);
        tevColorIn(this, id, 0xa, 0xc, 8, 0xf);
        tevAlphaOp(this, id, 0, 0, 0, 1, 0);
        tevAlphaIn(this, id, 7, 5, 4, 7);
        break;
    case 3:
        tevColorOp(this, id, 0, 0, 0, 1, 0);
        tevColorIn(this, id, 8, 0xf, 0xf, 0xf);
        tevAlphaOp(this, id, 0, 0, 0, 1, 0);
        tevAlphaIn(this, id, 4, 7, 7, 7);
        break;
    case 4:
        tevColorOp(this, id, 0, 0, 0, 1, 0);
        tevColorIn(this, id, 0xa, 0xf, 0xf, 0xf);
        tevAlphaOp(this, id, 0, 0, 0, 1, 0);
        tevAlphaIn(this, id, 5, 7, 7, 7);
        break;
    case 5:
        tevColorOp(this, id, 0, 0, 0, 1, 0);
        tevColorIn(this, id, 8, 0xf, 0xf, 0);
        tevAlphaOp(this, id, 0, 0, 0, 1, 0);
        tevAlphaIn(this, id, 4, 7, 7, 0);
        break;
    case 6:
        tevColorOp(this, id, 0, 0, 0, 1, 0);
        tevColorIn(this, id, 0xa, 0xf, 0xf, 0);
        tevAlphaOp(this, id, 0, 0, 0, 1, 0);
        tevAlphaIn(this, id, 5, 7, 7, 0);
        break;
    case 7:
        tevColorOp(this, id, 0, 0, 0, 1, 0);
        tevColorIn(this, id, 0xf, 0xa, 8, 0);
        tevAlphaOp(this, id, 0, 0, 0, 1, 0);
        tevAlphaIn(this, id, 7, 5, 4, 0);
        break;
    }
}
}

extern "C++" {
struct GSgfxChanState {
    u8 enable;
    s32 ambSrc;
    s32 matSrc;
    s32 unkC;
    s32 diffuse;
    s32 attn;
    GSgfxLight* lights[8];
};

struct GSgfxLayerChans {
#ifdef __MWERKS__
    u8 pad[0xDBC];
#endif
    GSgfxChanState chans[4];
};
#ifdef __MWERKS__
#define CHANS (((GSgfxLayerChans*)this)->chans)
#else
#define CHANS (((GSgfxLayerChans*)this->hw.chan)->chans)
#endif

void GSgfxLayer::cunitChannelGen(unsigned char chan, GSgfxCunitAlpha alpha, GSgfxCunitSrc amb, GSgfxCunitSrc mat,
                                 u32 numLights, GSgfxLight** lights, GSgfxLightType type,
                                 GSgfxDiffuseFunc diffuse) {
    u32 colorChan = chan;
    u32 alphaChan = chan + 2;
    u8 enable = 0;
    u32 i;

    if (lights != NULL && numLights != 0) {
        enable = 1;
    }
    if (enable == 0) {
        type = (GSgfxLightType)2;
        diffuse = (GSgfxDiffuseFunc)0;
    } else if (type == 0) {
        diffuse = (GSgfxDiffuseFunc)0;
    }
    if (alpha == 0 || alpha == 2) {
        CHANS[chan].enable = enable;
        CHANS[chan].ambSrc = amb;
        CHANS[chan].matSrc = mat;
        CHANS[chan].unkC = 0;
        CHANS[chan].diffuse = diffuse;
        CHANS[chan].attn = type;
        if (enable) {
            for (i = 0; i < 8; i++) {
                if (i < numLights) {
                    CHANS[chan].lights[i] = lights[i];
                } else {
                    CHANS[chan].lights[i] = NULL;
                }
            }
        } else {
            memset(CHANS[colorChan].lights, 0, sizeof(CHANS[colorChan].lights));
        }
        LAYER_F(this, u32 *, 0x16C0, dirty[0].chanCtrl) |= 1 << colorChan;
        LAYER_F(this, u32 *, 0x1778, dirty[1].chanCtrl) |= 1 << colorChan;
    }
    if (alpha == 1 || alpha == 2) {
        CHANS[alphaChan].enable = enable;
        CHANS[alphaChan].ambSrc = amb;
        CHANS[alphaChan].matSrc = mat;
        CHANS[alphaChan].unkC = 0;
        CHANS[alphaChan].diffuse = diffuse;
        CHANS[alphaChan].attn = type;
        if (enable) {
            for (i = 0; i < 8; i++) {
                if (i < numLights) {
                    CHANS[colorChan].lights[i] = lights[i];
                } else {
                    CHANS[colorChan].lights[i] = NULL;
                }
            }
        } else {
            memset(CHANS[colorChan].lights, 0, sizeof(CHANS[colorChan].lights));
        }
        LAYER_F(this, u32 *, 0x16C0, dirty[0].chanCtrl) |= 1 << alphaChan;
        LAYER_F(this, u32 *, 0x1778, dirty[1].chanCtrl) |= 1 << alphaChan;
    }
    LAYER_F(this, u32 *, 0x16A8, dirty[0].groups) |= 4;
    LAYER_F(this, u32 *, 0x1760, dirty[1].groups) |= 4;
}
}

extern "C++" {

extern "C++" {
void GSgfxLayer::drawSphere(unsigned char p0) {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(LAYER_VF_ADDR(this) + 0x1B8));
    GXDrawSphere1(p0);
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawSphere(unsigned char p0, unsigned char p1) {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(LAYER_VF_ADDR(this) + 0x1B8));
    GXDrawSphere(p1, p0);
    ((GSgfxLayer*)(this))->InvalidateState();
}
}
}

extern "C++" {
void GSgfxLayer::drawTorus(float p0, unsigned char p1, unsigned char p2) {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(LAYER_VF_ADDR(this) + 0x1B8));
    GXDrawTorus(p0, p1, p2);
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawOctahedron() {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(LAYER_VF_ADDR(this) + 0x1B8));
    GXDrawOctahedron();
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawIcosahedron() {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(LAYER_VF_ADDR(this) + 0x1B8));
    GXDrawIcosahedron();
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawDodecaedron() {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(LAYER_VF_ADDR(this) + 0x1B8));
    GXDrawDodeca();
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawCylinder(unsigned char p0) {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(LAYER_VF_ADDR(this) + 0x1B8));
    GXDrawCylinder(p0);
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawCube() {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(LAYER_VF_ADDR(this) + 0x1B8));
    GXDrawCube();
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::dlDraw(GSgfxDL* p0) {
    LAYER_VF_SAVE temp_r31;

    if (DL_F(p0, u16 *, 0, flags) & 2) {
        DCStoreRange((register void*)(DL_F(p0, u8 **, 4, data)), DL_F(p0, u32 *, 8, size));
        DL_F(p0, u16 *, 0, flags) = (u16) (DL_F(p0, u16 *, 0, flags) & 0xFFFFFFFD);
    }
    temp_r31 = LAYER_VF_GET(this);
    LAYER_VF_SET(this, DL_VF(p0));
    ((GSgfxLayer*)(this))->FlushState();
    _layerCallDisplayList(DL_F(p0, u8 **, 4, data), DL_F(p0, u32 *, 8, size));
    LAYER_VF_SET(this, temp_r31);
}
}

extern "C++" {
void GSgfxLayer::dlDrawExt(unsigned char* p0, u32 p1) {
    M2C_FIELD(LAYER_F(this, u8 **, 0x199C, curVF), s32 *, 4) = 0;
    ((GSgfxLayer*)(this))->FlushState();
    _layerCallDisplayList(p0, p1);
}
}

void GSgfxLayer::endSurface() {
    gsgfx_layer_inPrimitive = 0;
}

extern "C++" {
void GSgfxLayer::beginSurface(unsigned short p0) {
    ((GSgfxLayer*)(this))->FlushState();
    GXWGFifo.u8 = LAYER_F(this, s32 *, 0x1998, unk1998) | M2C_FIELD(LAYER_F(this, u8 **, 0x199C, curVF), s32 *, 4);
    GXWGFifo.u16 = p0;
    gsgfx_layer_inPrimitive = 1;
}
}

#ifndef __MWERKS__
#include <stddef.h>
static_assert(sizeof(GSgfxTgenState) == sizeof(GSgfxLayerTexGen), "texgen view");
static_assert(offsetof(GSgfxTgenState, unk14) == offsetof(GSgfxLayerTexGen, tex), "texgen view");
static_assert(sizeof(GSgfxChanState) == sizeof(GSgfxLayerChan), "chan view");
static_assert(offsetof(GSgfxChanState, lights) == offsetof(GSgfxLayerChan, lights), "chan view");
static_assert(sizeof(GSgfxTevColorOpState) == sizeof(GSgfxLayerTevOp), "tev op view");
static_assert(offsetof(GSgfxLayerTevView, alphaOp) ==
              offsetof(GSgfxLayerHW, alphaOp) - offsetof(GSgfxLayerHW, colorIn), "tev view");
#endif
