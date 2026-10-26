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
struct GXFogAdjTable;

struct GSgfxVFArray {
    u16 flags;
    u8 stride;
    u8 pad3;
    s32 id;
    void* addr;
    u32 size;
};
struct GSgfxVF {
    u16 flags;
    u8 pad2[2];
    s32 fmt;
    u8 attrFmt[0x1b8 - 8];
    u8 vtxDesc[0x290 - 0x1b8];
    GSgfxVFArray arrays[1];
};
struct GSgfxTex {
    u16 w;
    u16 h;
    u8 pad4[3];
    u8 reload;
    u8 pad8[0x48 - 8];
    u32 tlut;
    u8 pad4c[0x54 - 0x4c];
    u8 texObj[0x74 - 0x54];
    u8 tlutObj[8];
};
struct GSgfxLight {
    void Load(u8 idx);
};
typedef f32 Mtx[3][4];
struct GSgfxMtxEntry {
    u32 flags;
    Mtx mtx;
    Mtx invXpose;
};
struct GSgfxMtxStack {
    u32 unk0;
    GSgfxMtxEntry* top;
};
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
    struct RS {
        u8 texCount;
        u8 pad1[0x124 - 1];
        u8 lightCount;
        u8 pad125[3];
        GSgfxLight* lights[8];
    } rs;
    u8 pad_db8[0x1420 - 0xdb8];
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
        u32 groups;
        u8 pad4[0x10];
        u32 lightDirty;
        u8 pad18[0x68 - 0x18];
        GSgfxVF* vf[8];
        GSgfxVF* last;
        GSgfxMtxEntry* mtx;
        u8 mtxValid;
        u8 pad91[3];
        u32 texMask;
        GSgfxTex* tex[8];
    } dirty[2];
    u8 pad1818[0x1994 - 0x1818];
    int dirtyIdx;
    u8 pad1998[4];
    GSgfxVF* curVF;
    GSgfxMtxStack* mtxStack;
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

struct RegBlend { u32 id : 8; u32 pad : 8; u32 pad2 : 3; u32 lop : 1; u32 sub : 1; u32 src : 3; u32 dst : 3; u32 pad3 : 3; u32 logic : 1; u32 blend : 1; };
struct RegSS { u32 id : 8; u32 pad : 8; u32 t1 : 4; u32 s1 : 4; u32 t0 : 4; u32 s0 : 4; };
struct RegAlphaCmp { u32 id : 8; u32 op : 2; u32 comp1 : 3; u32 comp0 : 3; u32 ref1 : 8; u32 ref0 : 8; };
struct AlphaCache { s32 comp0, op, comp1; u8 ref0, ref1; };
struct W5 { u32 w[5]; };
struct RegScis { u32 id : 8; u32 x : 12; u32 y : 12; };
struct RegFogRange { u32 id : 8; u32 pad : 13; u32 en : 1; u32 center : 10; };
struct RegRangeAdj { u32 id : 8; u32 k : 12; u32 r : 12; };
struct RegTevC { u32 id : 8; u32 reg : 2; u32 scale : 2; u32 clamp : 1; u32 op : 1; u32 bias : 2; u32 a : 4; u32 b : 4; u32 c : 4; u32 d : 4; };
struct RegTevA { u32 id : 8; u32 reg : 2; u32 scale : 2; u32 clamp : 1; u32 op : 1; u32 bias : 2; u32 a : 3; u32 b : 3; u32 c : 3; u32 d : 3; u32 pad : 4; };
struct RegPeCtrl {
    u32 id : 8;
    u32 pad : 17;
    u32 zcomploc : 1;
    u32 b5 : 1;
    u32 zfmt : 2;
    u32 pixfmt : 3;
};
struct RegZMode {
    u32 id : 8;
    u32 pad : 19;
    u32 update : 1;
    u32 func : 3;
    u32 enable : 1;
};
struct RegCMode0 {
    u32 id : 8;
    u32 pad : 19;
    u32 alphaUpd : 1;
    u32 colorUpd : 1;
    u32 dither : 1;
    u32 logic : 1;
    u32 blend : 1;
};
struct RegClearAR {
    u32 id : 8;
    u32 pad : 8;
    u32 a : 8;
    u32 r : 8;
};
struct RegClearZ {
    u32 id : 8;
    u32 z : 24;
};
struct RegSrc {
    u32 id : 8;
    u32 pad : 4;
    u32 y : 10;
    u32 x : 10;
};
struct RegYScale {
    u32 id : 8;
    u32 pad : 15;
    u32 scale : 9;
};
struct RegStride {
    u32 id : 8;
    u32 pad : 14;
    u32 stride : 10;
};
struct RegDest {
    u32 id : 8;
    u32 pad : 3;
    u32 addr : 21;
};
struct RegCopyCmd {
    u32 id : 8;
    u32 pad : 9;
    u32 f14 : 1;
    u32 f12_13 : 2;
    u32 f11 : 1;
    u32 f10 : 1;
    u32 pad9 : 1;
    u32 f7_8 : 2;
    u32 pad2 : 5;
    u32 clamp : 2;
};
struct RegMsLoc {
    u32 id : 8;
    u32 y2 : 4;
    u32 x2 : 4;
    u32 y1 : 4;
    u32 x1 : 4;
    u32 y0 : 4;
    u32 x0 : 4;
};
struct RegCoeff {
    u32 id : 8;
    u32 c3 : 6;
    u32 c2 : 6;
    u32 c1 : 6;
    u32 c0 : 6;
};
struct RegCopyTexCmd {
    u32 id : 8;
    u32 pad23 : 7;
    u32 b16 : 1;
    u32 b15 : 1;
    u32 pad12 : 3;
    u32 clear : 1;
    u32 pad10 : 1;
    u32 mip : 1;
    u32 pad7 : 2;
    u32 fmt : 3;
    u32 fmt3 : 1;
    u32 pad2 : 1;
    u32 clamp : 2;
};
struct CopyTexReq {
    u16 left, top, width, height, dstWidth;
    u16 pad;
    s32 fmt;
    u32 clamp;
    u8 mip;
    u8 clear;
};
struct RegFog0 { u32 id : 8; u32 pad : 4; u32 a : 20; };
struct RegFog1 { u32 id : 8; u32 bm : 24; };
struct RegFog2 { u32 id : 8; u32 bs : 24; };
struct RegFog3 { u32 id : 8; u32 fsel : 3; u32 proj : 1; u32 c : 20; };
struct RegIndCmd {
    u32 id : 8;
    u32 pad : 3;
    u32 addPrev : 1;
    u32 utcLod : 1;
    u32 wrapT : 3;
    u32 wrapS : 3;
    u32 matrix : 4;
    u32 alpha : 2;
    u32 bias : 3;
    u32 fmt : 2;
    u32 indId : 2;
};
struct RegIndMtx {
    u32 id : 8;
    u32 scale : 2;
    u32 hi : 11;
    u32 lo : 11;
};
struct RegMatIdxA { u32 pad : 2; u32 t3 : 6; u32 t2 : 6; u32 t1 : 6; u32 t0 : 6; u32 pn : 6; };
struct RegMatIdxB { u32 pad : 8; u32 t7 : 6; u32 t6 : 6; u32 t5 : 6; u32 t4 : 6; };
struct TexGenCache { s32 func; s32 src; u32 mtx; u8 norm; s32 post; };
struct RegId24 { u32 id : 8; u32 v : 24; };
struct RegTexImg { u32 id : 8; u32 pad : 2; u32 b21 : 1; u32 ch : 3; u32 cw : 3; u32 addr : 15; };
union RegTlutW { RegId24 a; struct { u32 id : 8; u32 pad : 14; u32 tmem : 10; } b; };
struct TlutCache { u32 a; s16 b; s16 c; };
struct TexObj { u32 w0, w1, w2, w3; };
struct TlutObj { u32 w0, w1; u16 h8; };
struct RegIref { u32 id : 8; u32 c3 : 3; u32 m3 : 3; u32 c2 : 3; u32 m2 : 3; u32 c1 : 3; u32 m1 : 3; u32 c0 : 3; u32 m0 : 3; };
struct RegTref { u32 id : 8; u32 pad2 : 2; u32 col1 : 3; u32 en1 : 1; u32 c1 : 3; u32 m1 : 3; u32 pad1 : 2; u32 col0 : 3; u32 en0 : 1; u32 c0 : 3; u32 m0 : 3; };
struct RegGenMode { u32 id : 8; u32 pad23 : 4; u32 b19 : 1; u32 nInd : 3; u32 cull : 2; u32 nTev : 4; u32 pad6 : 4; u32 nChan : 2; u32 nTex : 4; };
union RegTexImg0 { RegId24 a; struct { u32 id : 8; u32 fmt : 4; u32 rest : 20; } b; };
struct GSState;

struct RegX22 { u32 id : 8; u32 pad23 : 1; u32 b22 : 1; u32 f19 : 3; u32 f16 : 3; u32 pw : 8; u32 lw : 8; };
struct RegX68 { u32 id : 8; u32 pad : 23; u32 b0 : 1; };
struct RegCMode1 { u32 id : 8; u32 pad : 13; u32 f9 : 2; u32 pad2 : 9; };
struct Reg { u32 id : 8; u32 v : 24; };
struct RegKcol { u32 id : 8; u32 pad : 1; u32 hi : 11; u32 pad2 : 1; u32 lo : 11; };
struct RegKsel { u32 id : 8; u32 pad : 20; u32 hi : 2; u32 lo : 2; };
struct RegTlutLoad0 { u32 id : 8; u32 pad : 3; u32 a : 21; };
struct RegTlutLoad1 { u32 id : 8; u32 pad : 3; u32 b : 11; u32 c : 10; };
struct RegSu { u32 id : 8; u32 pad : 8; u32 half : 16; };
struct RegSuBits { u32 id : 8; u32 pad : 8; u32 hi : 4; u32 f11 : 1; u32 f10 : 1; u32 sz : 10; };
struct ChanCache { u8 a; s32 w[5]; };
struct TevOrderCache { s32 a, b, c; };
struct TevInCache { s32 a, b, c, d; };
struct TevOpCache { s32 op, bias, scale; u8 clamp; s32 reg; };
struct GSState {
    u32 dirty;
    u32 dTref;
    u32 dIref;
    u32 d0c;
    u32 d10;
    u32 d14;
    u32 dKsel;
    u32 dTevc;
    u32 dTeva;
    u32 dKcolA;
    u32 dKcolB;
    u32 indDirty;
    RegGenMode genMode;
    RegZMode zmode;
    RegBlend cmode0;
    RegCMode1 cmode1;
    RegPeCtrl peCtrl;
    Reg r44;
    Reg r48;
    RegScis scis0;
    RegScis scis1;
    u32 xf1005;
    RegTref tref[8];
    RegIref iref;
    RegSS ras1ss[2];
    RegId24 texMode0[8];
    RegId24 texMode1[8];
    RegTexImg0 texImg0[8];
    RegTexImg texImg1[8];
    RegTexImg texImg2[8];
    RegId24 texImg3[8];
    RegTlutW texTlut[8];
    TlutCache tlutCache[8];
    RegTlutLoad0 tlutLoad0;
    RegTlutLoad1 tlutLoad1;
    RegSu suS[8];
    RegSu suT[8];
    RegX22 r1ec;
    RegMatIdxA matIdxA;
    RegMatIdxB matIdxB;
    RegAlphaCmp alphaCmp;
    Reg r1fc;
    Reg r200;
    RegKsel ksel[8];
    RegTevC tevc[16];
    RegTevA teva[16];
    RegKcol kcolA0[4];
    RegKcol kcolA1[4];
    RegKcol kcolB0[4];
    RegKcol kcolB1[4];
    RegFog0 fog0;
    RegFog1 fog1;
    RegFog2 fog2;
    RegFog3 fog3;
    Reg r2f4;
    RegFogRange fogRange;
    RegRangeAdj rangeAdj[5];
    RegIndCmd indCmd[16];
    Reg r350;
    RegX68 r354;
    TexGenCache texGen[8];
    u8 c3f8;
    u8 pad3f9[3];
    u8 sizeW0;
    u8 pad3fd[3];
    s32 sizeOff0;
    u8 sizeW1;
    u8 pad405[3];
    s32 sizeOff1;
    u8 coordScale[16];
    s32 c41c;
    u32 projCache[6];
    u8 c438;
    u8 pad439[3];
    s32 c43c;
    s32 c440;
    u16 scis[4];
    s32 scisOff[2];
    u8 c454;
    u8 pad455[3];
    ChanCache chan[4];
    u8 ambMat[4][5];
    TevOrderCache tevOrder[16];
    u8 c58c[2];
    u8 pad58e[2];
    TevInCache colorIn[16];
    TevInCache alphaIn[16];
    TevOpCache colorOp[16];
    TevOpCache alphaOp[16];
    u8 kcolFlag[4][5];
    s32 cA24[64];
    s32 swapCache[4][4];
    u8 indStatus[16];
    s32 indOrder[4][2];
    s32 indScale[4][2];
    s32 blendCache[4];
    u8 cBC4[2];
    u8 padbc6[2];
    AlphaCache alphaCache;

    s32 cBD8[3];
    u8 cBE4;
    u8 padbe5[3];
    s32 cBE8;
    u8 cBEC;
    u8 padbed[3];
    u8 c_bf0;
    u8 cBF1[3];
    u32 c_fogType;
    f32 c_fogStart;
    f32 c_fogEnd;
    f32 c_fogNear;
    f32 c_fogFar;
    u8 cC08;
    u8 padc09[4];
    u8 cC0D;
    u16 cC0E;
    W5 rangeCache;
    f32 vp[6];
    s32 cC3C;
};

#define RAW(r) (*(u32*)&(r))
extern "C" GSState* gsgfxState;
u8* _layerStateLastHWState;
#define GX_WGPIPE (*(volatile union { u8 u8; u16 u16; u32 u32; f32 f32; }*)0xCC008000)

extern "C" {
struct GXFogAdjTable {
    u8 _draft[1];
};

extern "C" {
void* GSgfxVideoGetViewport(f32, s32, s32, f32, f32, s32, s32, f32);
inline void GSgfx_GCSetAlphaCompare(s32 comp0, u8 ref0, s32 op, s32 comp1, u8 ref1);
struct GSColor { u8 r; u8 g; u8 b; u8 a; };
inline void GSgfx_GCSetAmbColor(s32 ch, GSColor c);
inline void GSgfx_GCSetBlendMode(s32 type, s32 src, s32 dst, s32 lop);
inline void GSgfx_GCSetChanCtrl(s32 chan, u8 enable, s32 amb, s32 mat, s32 lights, s32 diff, s32 attn);
inline void GSgfx_GCSetFogRangeAdj(u8 en, u16 center, u32* adj);
inline void GSgfx_GCSetIndTexCoordScale(s32 stage, s32 s, s32 t);
inline void GSgfx_GCSetIndTexOrder(s32 stage, s32 coord, s32 map);
inline void GSgfx_GCSetMatColor(s32 ch, GSColor c);
inline void GSgfx_GCSetProjection(s32 type, u32* p);
inline void GSgfx_GCSetScissor(u16 x, u16 y, u16 w, u16 h, s32 xo, s32 yo);
inline void GSgfx_GCSetTevAlphaIn(s32 stage, s32 a, s32 b, s32 c, s32 d);
inline void GSgfx_GCSetTevAlphaOp(s32 stage, s32 op, s32 bias, s32 scale, u8 clamp, s32 reg);
inline void GSgfx_GCSetTevColorIn(s32 stage, s32 a, s32 b, s32 c, s32 d);
inline void GSgfx_GCSetTevColorOp(s32 stage, s32 op, s32 bias, s32 scale, u8 clamp, s32 reg);
inline void GSgfx_GCSetTevDirect(s32 stage);
inline void GSgfx_GCSetTevIndBumpXYZ(s32 stage, u8 indId, u8 mtx);
inline void GSgfx_GCSetTevIndRepeat(s32 stage);
inline void GSgfx_GCSetTevIndWarp(s32 stage, u8 indId, u8 signMod, u8 wrap, u8 mtx);
inline void GSgfx_GCSetTevIndirect(s32 stage, u8 indId, u8 fmt, u8 bias, u8 mtx, u8 ws, u8 wt, s32 addPrev, u8 utc, s32 alpha);
inline void GSgfx_GCSetTevKColor(u32 i, u32* c);
inline void GSgfx_GCSetTevOrder(s32 stage, s32 coord, s32 map, s32 color);
inline void GSgfx_GCSetTevSwapModeTable(s32 t, s32 r, s32 g, s32 b, s32 a);
s32 GSgfx_GCWriteFog(s32);
s32 GSgfx_GCWriteTevIndBumpST(s32, u8, s32);
s32 GSgfx_GCWriteTevIndTile(s32, u8, u16, u16, u16, u16, s32, s32);
s32 GSgfx_GCWriteTexCoordGen(s32);
void GXInitFogAdjTable(GXFogAdjTable *table, u16 width, const f32 projmtx[4][4]);
extern s32 cm2hw_localstatic3_GSgfx_GCWriteCullMode;
extern s32 jtbl_1693;
}
extern "C++" {
s32 GSgfxVideoSetViewport(float, float, float, float, bool);
}

inline void GSIndSet(s32 stage, u8 indId, u8 fmt, u8 bias, u8 mtx, u8 ws, u8 wt, s32 addPrev, u8 utc, s32 alpha) {
    gsgfxState->indCmd[stage].indId = indId;
    gsgfxState->indCmd[stage].fmt = fmt;
    gsgfxState->indCmd[stage].bias = bias;
    gsgfxState->indCmd[stage].alpha = alpha;
    gsgfxState->indCmd[stage].matrix = mtx;
    gsgfxState->indCmd[stage].wrapS = ws;
    gsgfxState->indCmd[stage].wrapT = wt;
    gsgfxState->indCmd[stage].utcLod = utc;
    gsgfxState->indCmd[stage].addPrev = addPrev;
    gsgfxState->indDirty |= 1 << stage;
    gsgfxState->indStatus[stage] = 2;
}
struct XfCol { u32 r : 8; u32 g : 8; u32 b : 8; u32 a : 8; };
inline void GSWriteXfColor(u32 reg, u32 v) {
    u8* p = (u8*)&v;
    GX_WGPIPE.u8 = 0x10;
    GX_WGPIPE.u16 = 0;
    GX_WGPIPE.u16 = reg;
    GX_WGPIPE.u32 = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}
}

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

extern "C" {

extern "C++" {
void GSgfxLayer::SetupGPUState() {
    f32 sp10;
    s32 unksp15;
    s32 unksp16;
    s32 unksp19;
    s32 unksp1A;
    s32 unksp1D;
    s32 unksp1E;
    s32 unksp1F;
    s32 unksp36;
    s32 unksp3A;
    f32 sp78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    u8 *var_r29;
    u8 temp_r5;
    u8 *var_r3_3;
    u8 *var_r25_2;
    volatile f32 sp54;
    f32 sp50;
    s32 sp4C;
    f32 sp48;
    volatile f32 sp44;
    s32 sp40;
    volatile f32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    u32 sp24;
    u32 sp20;
    s32 sp1C;
    u32 sp18;
    u32 sp14;
    s32 spC;
    s32 sp8;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r10_3;
    s32 temp_r10_4;
    s32 temp_r11;
    s32 temp_r12_2;
    s32 temp_r12_3;
    u8 *var_r3_4;
    s32 temp_r25;
    s32 temp_r3_3;
    s32 temp_r4_3;
    s32 temp_r4_4;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r6_3;
    s32 temp_r6_4;
    s32 temp_r6_5;
    s32 temp_r6_6;
    s32 temp_r7_2;
    s32 temp_r7_3;
    s32 temp_r8;
    s32 temp_r8_2;
    s32 temp_r8_3;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 temp_r9_3;
    s32 var_ctr;
    s32 var_r24_2;
    s32 var_r25;
    s32 var_r26;
    s32 var_r26_10;
    s32 var_r26_11;
    s32 var_r26_2;
    s32 var_r26_3;
    s32 var_r26_4;
    s32 var_r26_5;
    s32 var_r26_6;
    s32 var_r26_7;
    s32 var_r26_8;
    s32 var_r26_9;
    s32 var_r27;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29_3;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_4;
    s32 var_r4_5;
    s32 var_r5;
    s32 var_r5_3;
    s32 var_r5_4;
    s32 var_r5_5;
    s32 var_r5_6;
    s32 var_r6;
    s32 var_r6_3;
    s32 var_r7;
    u32 temp_r0;
    u32 temp_r0_4;
    u32 temp_r3_4;
    u32 temp_r3_5;
    u8 temp_r0_5;
    u8 temp_r12;
    u8 temp_r24;
    u8 temp_r4;
    u8 temp_r4_10;
    u8 temp_r4_11;
    u8 temp_r4_12;
    u8 temp_r4_13;
    u8 temp_r4_2;
    u8 temp_r4_5;
    u8 temp_r4_7;
    u8 temp_r4_8;
    u8 temp_r4_9;
    s32 sp60;
    u8 temp_r5_2;
    u8 temp_r5_3;
    u8 temp_r5_4;
    u8 temp_r5_5;
    u8 var_r28_3;
    u8 var_r5_2;
    u8 **var_r6_2;
    u8 *temp_r30;
    u8 *temp_r31;
    u8 *temp_r3;
    u8 *temp_r3_2;
    u8 *temp_r3_6;
    u8 *temp_r4_6;
    GSState * temp_r7;
    GSState * temp_r7_4;
    u8 *var_r24;
    u8 *var_r25_10;
    u8 *var_r25_11;
    u8 *var_r25_12;
    f32 sp58;
    u8 *var_r25_3;
    u8 *var_r25_4;
    u8 *var_r25_5;
    u8 *var_r25_6;
    u8 *var_r25_7;
    u8 *var_r25_8;
    u8 *var_r25_9;
    f32 sp64;
    u8 *var_r29_2;
    u8 *var_r3;
    u8 *var_r3_2;
    s32 sp5C;
    s32 temp_r24_2;
    u8 *var_r3_5;

    temp_r30 = ((u8*)this + ((M2C_FIELD(this, s32 *, 0x1994) * 0xB8) + 0x16A8));
    temp_r0 = M2C_FIELD(temp_r30, u32 *, 0);
    if (temp_r0 != 0) {
        temp_r31 = (unsigned char *)(this + 0xC70);
        if (temp_r0 & 1) {
            if (M2C_FIELD(temp_r30, s32 *, 4) & 1) {
                temp_r4 = M2C_FIELD(this, u8 *, 0xC70);
                if ((u8) M2C_FIELD(gsgfxState, u8 *, 0x3F8) != temp_r4) {
                    M2C_FIELD(gsgfxState, u8 *, 0x33) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x33) & ~0xF) | (temp_r4 & 0xF));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x02000000 | 1);
                    M2C_FIELD(gsgfxState, u8 *, 0x3F8) = temp_r4;
                }
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 8) != 0) {
                var_r29 = temp_r31;
                var_r28 = 0;
                var_r27 = 0;
                while (var_r28 < (s32) M2C_FIELD(this, u8 *, 0xC70)) {
                    if (M2C_FIELD(temp_r30, u32 *, 8) & (1 << var_r28)) {
                        temp_r3 = M2C_FIELD(var_r29, u8 **, 0x18);
                        if (temp_r3 != NULL) {
                            M2C_FIELD(var_r29, s32 *, 4) = (s32) (M2C_FIELD(temp_r3, u8 *, 0x7C) + 2);
                        }
                        if (((s32) M2C_FIELD((temp_r3_2 = (unsigned char *)(gsgfxState + var_r27)), s32 *, 0x358) != (s32) M2C_FIELD(var_r29, s32 *, 4)) || ((s32) M2C_FIELD(temp_r3_2, s32 *, 0x35C) != (s32) M2C_FIELD(var_r29, s32 *, 8)) || ((u32) M2C_FIELD(temp_r3_2, u32 *, 0x360) != (u32) M2C_FIELD(var_r29, u32 *, 0xC)) || ((u8) M2C_FIELD(temp_r3_2, u8 *, 0x364) != (u8) M2C_FIELD(var_r29, u8 *, 0x10)) || ((u32) M2C_FIELD(temp_r3_2, u32 *, 0x368) != (u32) M2C_FIELD(var_r29, u32 *, 0x14))) {
                            GSgfx_GCWriteTexCoordGen(var_r28);
                        }
                    }
                    var_r29 += 0x18;
                    var_r28 += 1;
                    var_r27 += 0x14;
                }
                M2C_FIELD(temp_r30, u32 *, 8) = 0U;
            }
            if ((M2C_FIELD(temp_r30, s32 *, 4) & 4) && ((temp_r5 = M2C_FIELD(temp_r31, u8 *, 0xC4), temp_r6 = M2C_FIELD(temp_r31, s32 *, 0xC8), (((u8) M2C_FIELD(gsgfxState, u8 *, 0x3FC) == temp_r5) == 0)) || ((s32) M2C_FIELD(gsgfxState, s32 *, 0x400) != temp_r6))) {
                M2C_FIELD(gsgfxState, u8 *, 0x1EF) = temp_r5;
                M2C_FIELD(gsgfxState, u8 *, 0x1ED) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x1ED) & ~7) | (temp_r6 & 7));
                M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x400);
                M2C_FIELD(gsgfxState, u8 *, 0x3FC) = temp_r5;
                M2C_FIELD(gsgfxState, s32 *, 0x400) = temp_r6;
            }
            if ((M2C_FIELD(temp_r30, s32 *, 4) & 8) && ((temp_r5_2 = M2C_FIELD(temp_r31, u8 *, 0xCC), temp_r6_2 = M2C_FIELD(temp_r31, s32 *, 0xD0), (((u8) M2C_FIELD(gsgfxState, u8 *, 0x404) == temp_r5_2) == 0)) || ((s32) M2C_FIELD(gsgfxState, s32 *, 0x408) != temp_r6_2))) {
                M2C_FIELD(gsgfxState, u8 *, 0x1EE) = temp_r5_2;
                M2C_FIELD(gsgfxState, u8 *, 0x1ED) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x1ED) & ~0x38) | ((temp_r6_2 << 3) & 0x38));
                M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x400);
                M2C_FIELD(gsgfxState, u8 *, 0x404) = temp_r5_2;
                M2C_FIELD(gsgfxState, s32 *, 0x408) = temp_r6_2;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0xC) != 0) {
                var_r3 = temp_r31;
                var_r4 = 0;
                var_r5 = 0;
                var_r6 = 0;
                while (var_r4 < (s32) M2C_FIELD(this, u8 *, 0xC70)) {
                    if ((M2C_FIELD(temp_r30, u32 *, 0xC) & (1 << var_r4)) && ((temp_r12 = M2C_FIELD(var_r3, u8 *, 0xD4), temp_r7 = gsgfxState + var_r6, temp_r24 = M2C_FIELD(var_r3, u8 *, 0xD5), (((u8) M2C_FIELD(temp_r7, u8 *, 0x40C) == temp_r12) == 0)) || ((u8) M2C_FIELD(temp_r7, u8 *, 0x40D) != temp_r24))) {
                        *((u8 *)gsgfxState + temp_r11) = (*((u8 *)gsgfxState + temp_r11) & ~4) | ((temp_r12 << 2) & 4);
                        temp_r11 = var_r5;
                        temp_r11 += 0x1AD;
                        *((u8 *)gsgfxState + temp_r11) = (*((u8 *)gsgfxState + temp_r11) & ~8) | ((temp_r24 << 3) & 8);
                        M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | (1 << var_r4));
                        *((u8*)(gsgfxState) + (var_r6 + 0x40C)) = temp_r12;
                        *((u8*)(gsgfxState) + (var_r6 + 0x40D)) = temp_r24;
                    }
                    var_r3 += 2;
                    var_r4 += 1;
                    var_r5 += 4;
                    var_r6 += 2;
                }
                M2C_FIELD(temp_r30, u32 *, 0xC) = 0U;
            }
            if (M2C_FIELD(temp_r30, s32 *, 4) & 0x20) {
                GSgfx_GCSetProjection((long)(M2C_FIELD(temp_r31, s32 *, 0xE4)), (unsigned long *)(temp_r31 + 0xE8));
            }
            M2C_FIELD(temp_r30, s32 *, 4) = 0;
        }
        if (M2C_FIELD(temp_r30, u32 *, 0) & 2) {
            if (M2C_FIELD(temp_r30, s32 *, 0x10) & 8) {
                temp_r4_2 = M2C_FIELD(temp_r31, u8 *, 0x118);
                if ((u8) M2C_FIELD(gsgfxState, u8 *, 0x438) != temp_r4_2) {
                    M2C_FIELD(gsgfxState, u8 *, 0x31) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x31) & ~8) | ((temp_r4_2 << 3) & 8));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 1);
                    M2C_FIELD(gsgfxState, u8 *, 0x438) = temp_r4_2;
                }
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x10) & 2) {
                temp_r4_3 = M2C_FIELD(temp_r31, s32 *, 0x11C);
                if ((s32) M2C_FIELD(gsgfxState, s32 *, 0x43C) != temp_r4_3) {
                    M2C_FIELD(gsgfxState, u8 *, 0x32) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x32) & ~0xC0) | ((*(&cm2hw_localstatic3_GSgfx_GCWriteCullMode + temp_r4_3) << 6) & 0xC0));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 1);
                    M2C_FIELD(gsgfxState, s32 *, 0x43C) = temp_r4_3;
                }
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x10) & 4) {
                temp_r4_4 = M2C_FIELD(temp_r31, s32 *, 0x120);
                if ((s32) M2C_FIELD(gsgfxState, s32 *, 0x440) != temp_r4_4) {
                    M2C_FIELD(gsgfxState, s32 *, 0x54) = temp_r4_4;
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x04000000);
                    M2C_FIELD(gsgfxState, s32 *, 0x440) = temp_r4_4;
                }
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x10) & 1) {
                GSgfx_GCSetScissor(M2C_FIELD(temp_r31, u16 *, 0x100), M2C_FIELD(temp_r31, u16 *, 0x102), M2C_FIELD(temp_r31, u16 *, 0x104), M2C_FIELD(temp_r31, u16 *, 0x106), 0, 0);
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x10) & 0x10) {
                GSgfxVideoSetViewport(M2C_FIELD(temp_r31, f32 *, 0x108), M2C_FIELD(temp_r31, f32 *, 0x10C), M2C_FIELD(temp_r31, f32 *, 0x110), M2C_FIELD(temp_r31, f32 *, 0x114), 0U);
            }
            M2C_FIELD(temp_r30, s32 *, 0x10) = 0;
        }
        if (M2C_FIELD(temp_r30, u32 *, 0) & 4) {
            if (M2C_FIELD(temp_r30, s32 *, 0x14) & 1) {
                temp_r4_5 = M2C_FIELD(temp_r31, u8 *, 0x148);
                if ((u8) M2C_FIELD(gsgfxState, u8 *, 0x454) != temp_r4_5) {
                    M2C_FIELD(gsgfxState, u8 *, 0x33) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x33) & ~0x30) | ((temp_r4_5 << 4) & 0x30));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x01000000 | 1);
                    M2C_FIELD(gsgfxState, u8 *, 0x454) = temp_r4_5;
                }
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x18) != 0) {
                var_r25 = 0;
                var_r24 = temp_r31;
                do {
                    if (M2C_FIELD(temp_r30, u32 *, 0x18) & (1 << var_r25)) {
                        if ((u8) M2C_FIELD(var_r24, u8 *, 0x14C) != 0) {
                            temp_r8 = M2C_FIELD(var_r24, s32 *, 0x160);
                            var_r6_2 = (unsigned char **)(var_r24 + 0x164);
                            var_r7 = 0;
loop_71:
                            temp_r4_6 = *var_r6_2;
                            if (temp_r4_6 != NULL) {
                                var_r5_2 = 0;
                                while (var_r5_2 < 8U) {
                                    temp_r0_2 = M2C_FIELD(temp_r4_6, s32 *, 4);
                                    if ((temp_r8 == temp_r0_2) || ((temp_r8 == 2) && (temp_r0_2 == 1))) {
                                        var_r7 |= 1 << M2C_FIELD(temp_r4_6, u8 *, 0x7C);
                                    }
                                    var_r5_2 += 1;
                                }
                                var_r6_2 += 4;
                                goto loop_71;
                            }
                            M2C_FIELD(var_r24, s32 *, 0x158) = var_r7;
                        } else {
                            M2C_FIELD(var_r24, s32 *, 0x158) = 0;
                        }
                        GSgfx_GCSetChanCtrl(var_r25, M2C_FIELD(var_r24, u8 *, 0x14C), M2C_FIELD(var_r24, s32 *, 0x150), M2C_FIELD(var_r24, s32 *, 0x154), M2C_FIELD(var_r24, s32 *, 0x158), M2C_FIELD(var_r24, s32 *, 0x15C), M2C_FIELD(var_r24, s32 *, 0x160));
                    }
                    var_r25 += 1;
                    var_r24 += 0x38;
                } while (var_r25 < 4);
                M2C_FIELD(temp_r30, u32 *, 0x18) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x1C) != 0) {
                var_r25_2 = temp_r31;
                var_r26 = 0;
                while (var_r26 < (s32) M2C_FIELD(temp_r31, u8 *, 0x148)) {
                    if (M2C_FIELD(temp_r30, u32 *, 0x1C) & (1 << var_r26)) {
                        sp30 = M2C_FIELD(var_r25_2, s32 *, 0x22C);
                        GSgfx_GCSetAmbColor((long)(var_r26 + 4), *(GSColor*)&sp30);
                    }
                    var_r25_2 += 4;
                    var_r26 += 1;
                }
                M2C_FIELD(temp_r30, u32 *, 0x1C) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x20) != 0) {
                var_r25_3 = temp_r31;
                var_r26_2 = 0;
                while (var_r26_2 < (s32) M2C_FIELD(temp_r31, u8 *, 0x148)) {
                    if (M2C_FIELD(temp_r30, u32 *, 0x20) & (1 << var_r26_2)) {
                        sp2C = M2C_FIELD(var_r25_3, s32 *, 0x234);
                        GSgfx_GCSetMatColor((long)(var_r26_2 + 4), *(GSColor*)&sp2C);
                    }
                    var_r25_3 += 4;
                    var_r26_2 += 1;
                }
                M2C_FIELD(temp_r30, u32 *, 0x20) = 0U;
            }
            M2C_FIELD(temp_r30, s32 *, 0x14) = 0;
        }
        if (M2C_FIELD(temp_r30, u32 *, 0) & 8) {
            if (M2C_FIELD(temp_r30, s32 *, 0x24) & 1) {
                temp_r4_7 = M2C_FIELD(temp_r31, u8 *, 0x23C);
                if ((u8) M2C_FIELD(gsgfxState, u8 *, 0x58C) != temp_r4_7) {
                    M2C_FIELD(gsgfxState, u8 *, 0x32) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x32) & ~0x3C) | (((temp_r4_7 - 1) << 2) & 0x3C));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 1);
                    M2C_FIELD(gsgfxState, u8 *, 0x58C) = temp_r4_7;
                }
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x28) != 0) {
                var_r25_4 = temp_r31;
                var_r26_3 = 0;
                while (var_r26_3 < (s32) M2C_FIELD(temp_r31, u8 *, 0x23C)) {
                    if (M2C_FIELD(temp_r30, u32 *, 0x28) & (1 << var_r26_3)) {
                        GSgfx_GCSetTevOrder(var_r26_3, M2C_FIELD(var_r25_4, s32 *, 0x240), M2C_FIELD(var_r25_4, s32 *, 0x244), M2C_FIELD(var_r25_4, s32 *, 0x248));
                    }
                    var_r25_4 += 0xC;
                    var_r26_3 += 1;
                }
                M2C_FIELD(temp_r30, u32 *, 0x28) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x2C) != 0) {
                var_r25_5 = temp_r31;
                var_r26_4 = 0;
                while (var_r26_4 < (s32) M2C_FIELD(temp_r31, u8 *, 0x23C)) {
                    if (M2C_FIELD(temp_r30, u32 *, 0x2C) & (1 << var_r26_4)) {
                        GSgfx_GCSetTevColorIn(var_r26_4, M2C_FIELD(var_r25_5, s32 *, 0x300), M2C_FIELD(var_r25_5, s32 *, 0x304), M2C_FIELD(var_r25_5, s32 *, 0x308), M2C_FIELD(var_r25_5, s32 *, 0x30C));
                    }
                    var_r25_5 += 0x10;
                    var_r26_4 += 1;
                }
                M2C_FIELD(temp_r30, u32 *, 0x2C) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x30) != 0) {
                var_r25_6 = temp_r31;
                var_r26_5 = 0;
                while (var_r26_5 < (s32) M2C_FIELD(temp_r31, u8 *, 0x23C)) {
                    if (M2C_FIELD(temp_r30, u32 *, 0x30) & (1 << var_r26_5)) {
                        GSgfx_GCSetTevAlphaIn(var_r26_5, M2C_FIELD(var_r25_6, s32 *, 0x400), M2C_FIELD(var_r25_6, s32 *, 0x404), M2C_FIELD(var_r25_6, s32 *, 0x408), M2C_FIELD(var_r25_6, s32 *, 0x40C));
                    }
                    var_r25_6 += 0x10;
                    var_r26_5 += 1;
                }
                M2C_FIELD(temp_r30, u32 *, 0x30) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x34) != 0) {
                var_r25_7 = temp_r31;
                var_r26_6 = 0;
                while (var_r26_6 < (s32) M2C_FIELD(temp_r31, u8 *, 0x23C)) {
                    if (M2C_FIELD(temp_r30, u32 *, 0x34) & (1 << var_r26_6)) {
                        GSgfx_GCSetTevColorOp(var_r26_6, M2C_FIELD(var_r25_7, s32 *, 0x500), M2C_FIELD(var_r25_7, s32 *, 0x504), M2C_FIELD(var_r25_7, s32 *, 0x508), M2C_FIELD(var_r25_7, u8 *, 0x50C), M2C_FIELD(var_r25_7, s32 *, 0x510));
                    }
                    var_r25_7 += 0x14;
                    var_r26_6 += 1;
                }
                M2C_FIELD(temp_r30, u32 *, 0x34) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x38) != 0) {
                var_r25_8 = temp_r31;
                var_r26_7 = 0;
                while (var_r26_7 < (s32) M2C_FIELD(temp_r31, u8 *, 0x23C)) {
                    if (M2C_FIELD(temp_r30, u32 *, 0x38) & (1 << var_r26_7)) {
                        GSgfx_GCSetTevAlphaOp(var_r26_7, M2C_FIELD(var_r25_8, s32 *, 0x640), M2C_FIELD(var_r25_8, s32 *, 0x644), M2C_FIELD(var_r25_8, s32 *, 0x648), M2C_FIELD(var_r25_8, u8 *, 0x64C), M2C_FIELD(var_r25_8, s32 *, 0x650));
                    }
                    var_r25_8 += 0x14;
                    var_r26_7 += 1;
                }
                M2C_FIELD(temp_r30, u32 *, 0x38) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x3C) != 0) {
                var_r3_2 = temp_r31;
                var_r4_2 = 0;
                var_r5_3 = 0;
                var_ctr = 4;
                do {
                    temp_r0_3 = 1 << var_r4_2;
                    if (M2C_FIELD(temp_r30, u32 *, 0x3C) & temp_r0_3) {
                        if ((u32) M2C_FIELD(var_r3_2, u32 *, 0x780) == 0U) {
                            temp_r9 = 0x2A6;
                            temp_r9 += var_r5_3;
                            temp_r10 = 0x2A4;
                            temp_r10 += var_r5_3;
                            sp1C = M2C_FIELD(var_r3_2, s32 *, 0x784);
                            temp_r8_2 = 0x2B6;
                            temp_r8_2 += var_r5_3;
                            temp_r7_2 = 0x2B4;
                            temp_r7_2 += var_r5_3;
                            *((u8 *)gsgfxState + temp_r9) = (*((u8 *)gsgfxState + temp_r9) & ~0x7FF) | ((u8) sp1C & 0x7FF);
                            *((u8 *)gsgfxState + temp_r10) = (*((u8 *)gsgfxState + temp_r10) & ~0x7FF000) | ((unksp1F << 0xC) & 0x7FF000);

                            *((u8 *)gsgfxState + temp_r7_2) = (*((u8 *)gsgfxState + temp_r7_2) & ~0x7FF000) | ((unksp1D << 0xC) & 0x7FF000);
                            M2C_FIELD(gsgfxState, s32 *, 0x24) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x24) | temp_r0_3);
                        } else {
                            temp_r10_2 = 0x2A6;
                            temp_r10_2 += var_r5_3;
                            temp_r12_2 = 0x2A4;
                            temp_r12_2 += var_r5_3;
                            sp34 = M2C_FIELD(var_r3_2, s32 *, 0x784);
                            temp_r8_3 = 0x2B6;
                            temp_r8_3 += var_r5_3;
                            temp_r7_3 = 0x2B4;
                            temp_r7_3 += var_r5_3;
                            sp38 = M2C_FIELD(var_r3_2, s32 *, 0x788);
                            *((u8 *)gsgfxState + temp_r10_2) = (*((u8 *)gsgfxState + temp_r10_2) & ~0x7FF) | ((s16) sp34 & 0x7FF);
                            *((u8 *)gsgfxState + temp_r12_2) = (*((u8 *)gsgfxState + temp_r12_2) & ~0x7FF000) | (((unksp3A & 0x7FF) << 0xC) & 0x7FF000);
                            *((u8 *)gsgfxState + temp_r8_3) = (*((u8 *)gsgfxState + temp_r8_3) & ~0x7FF) | ((s16) sp38 & 0x7FF & 0x7FF);
                            *((u8 *)gsgfxState + temp_r7_3) = (*((u8 *)gsgfxState + temp_r7_3) & ~0x7FF000) | (((unksp36 & 0x7FF) << 0xC) & 0x7FF000);
                            M2C_FIELD(gsgfxState, s32 *, 0x24) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x24) | temp_r0_3);
                        }
                    }
                    var_r3_2 += 0xC;
                    var_r4_2 += 1;
                    var_r5_3 += 4;
                    var_ctr -= 1;
                } while (var_ctr != 0);
                M2C_FIELD(temp_r30, u32 *, 0x3C) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x40) != 0) {
                var_r28_2 = 0;
                var_r29_2 = temp_r31;
                do {
                    if (M2C_FIELD(temp_r30, u32 *, 0x40) & (1 << var_r28_2)) {
                        temp_r0_4 = M2C_FIELD(var_r29_2, u32 *, 0x7B0);
                        switch (temp_r0_4) {
                        case 0:
                            GSgfx_GCSetTevDirect(var_r28_2);
                            break;
                        case 1:
                            sp8 = (s32) M2C_FIELD(var_r29_2, u8 *, 0x7D1);
                            spC = M2C_FIELD(var_r29_2, s32 *, 0x7CC);
                            GSgfx_GCSetTevIndirect((long)(var_r28_2), (unsigned char)(M2C_FIELD(var_r29_2, u8 *, 0x7B4)), (unsigned char)(M2C_FIELD(var_r29_2, s32 *, 0x7B8)), (unsigned char)(M2C_FIELD(var_r29_2, s32 *, 0x7BC)), (unsigned char)(M2C_FIELD(var_r29_2, s32 *, 0x7C0)), (unsigned char)(M2C_FIELD(var_r29_2, s32 *, 0x7C4)), (unsigned char)(M2C_FIELD(var_r29_2, s32 *, 0x7C8)), (long)(M2C_FIELD(var_r29_2, u8 *, 0x7D0)), (unsigned char)(0), (long)(0));
                            break;
                        case 2:
                            GSgfx_GCSetTevIndWarp(var_r28_2, M2C_FIELD(var_r29_2, u8 *, 0x7B4), M2C_FIELD(var_r29_2, u8 *, 0x7B5), M2C_FIELD(var_r29_2, u8 *, 0x7B6), M2C_FIELD(var_r29_2, s32 *, 0x7B8));
                            break;
                        case 3:
                            sp8 = M2C_FIELD(var_r29_2, s32 *, 0x7C8);
                            spC = M2C_FIELD(var_r29_2, s32 *, 0x7CC);
                            GSgfx_GCWriteTevIndTile(var_r28_2, M2C_FIELD(var_r29_2, u8 *, 0x7B4), (u16) M2C_FIELD(var_r29_2, u8 *, 0x7B6), (u16) M2C_FIELD(var_r29_2, s32 *, 0x7B8), M2C_FIELD(var_r29_2, u16 *, 0x7BA), (u16) M2C_FIELD(var_r29_2, s32 *, 0x7BC), M2C_FIELD(var_r29_2, s32 *, 0x7C0), M2C_FIELD(var_r29_2, s32 *, 0x7C4));
                            break;
                        case 4:
                            GSgfx_GCWriteTevIndBumpST(var_r28_2, M2C_FIELD(var_r29_2, u8 *, 0x7B4), M2C_FIELD(var_r29_2, s32 *, 0x7B8));
                            break;
                        case 5:
                            GSgfx_GCSetTevIndBumpXYZ(var_r28_2, M2C_FIELD(var_r29_2, u8 *, 0x7B4), M2C_FIELD(var_r29_2, s32 *, 0x7B8));
                            break;
                        case 6:
                            GSgfx_GCSetTevIndRepeat(var_r28_2);
                            break;
                        }
                    }
                    var_r28_2 += 1;
                    var_r29_2 += 0x24;
                } while (var_r28_2 < 4);
                M2C_FIELD(temp_r30, u32 *, 0x40) = 0U;
            }
            M2C_FIELD(temp_r30, s32 *, 0x24) = 0;
        }
        if (M2C_FIELD(temp_r30, u32 *, 0) & 0x80) {
            if (M2C_FIELD(temp_r30, s32 *, 0x44) & 1) {
                temp_r4_8 = M2C_FIELD(temp_r31, u8 *, 0x840);
                if ((u8) M2C_FIELD(gsgfxState, u8 *, 0x58D) != temp_r4_8) {
                    M2C_FIELD(gsgfxState, u8 *, 0x31) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x31) & ~7) | (temp_r4_8 & 7));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 1);
                    M2C_FIELD(gsgfxState, u8 *, 0x58D) = temp_r4_8;
                }
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x48) != 0) {
                var_r25_9 = temp_r31;
                var_r26_8 = 0;
                do {
                    if (M2C_FIELD(temp_r30, u32 *, 0x48) & (1 << var_r26_8)) {
                        GSgfx_GCSetIndTexOrder(var_r26_8, M2C_FIELD(var_r25_9, s32 *, 0x844), M2C_FIELD(var_r25_9, s32 *, 0x848));
                    }
                    var_r26_8 += 1;
                    var_r25_9 += 8;
                } while (var_r26_8 < 4);
                M2C_FIELD(temp_r30, u32 *, 0x48) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x4C) != 0) {
                var_r25_10 = temp_r31;
                var_r26_9 = 0;
                do {
                    if (M2C_FIELD(temp_r30, u32 *, 0x4C) & (1 << var_r26_9)) {
                        GSgfx_GCSetIndTexCoordScale(var_r26_9, M2C_FIELD(var_r25_10, s32 *, 0x864), M2C_FIELD(var_r25_10, s32 *, 0x868));
                    }
                    var_r26_9 += 1;
                    var_r25_10 += 8;
                } while (var_r26_9 < 4);
                M2C_FIELD(temp_r30, u32 *, 0x4C) = 0U;
            }
            M2C_FIELD(temp_r30, s32 *, 0x44) = 0;
        }
        if (M2C_FIELD(temp_r30, u32 *, 0) & 0x10) {
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x50) != 0) {
                var_r25_11 = temp_r31;
                var_r26_10 = 0;
                do {
                    if (M2C_FIELD(temp_r30, u32 *, 0x50) & (1 << var_r26_10)) {
                        sp28 = M2C_FIELD(var_r25_11, s32 *, 0x884);
                        GSgfx_GCSetTevKColor((unsigned long)(var_r26_10), (unsigned long *)(&sp28));
                    }
                    var_r26_10 += 1;
                    var_r25_11 += 4;
                } while (var_r26_10 < 4);
                M2C_FIELD(temp_r30, u32 *, 0x50) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x54) != 0) {
                var_r3_3 = temp_r31;
                var_r4_3 = 0;
                var_r5_4 = 0;
                while (var_r4_3 < (s32) M2C_FIELD(temp_r31, u8 *, 0x23C)) {
                    if (M2C_FIELD(temp_r30, u32 *, 0x54) & (1 << var_r4_3)) {
                        temp_r9_2 = M2C_FIELD(var_r3_3, s32 *, 0x894);
                        if ((s32) *((u8*)(gsgfxState) + (var_r5_4 + 0xA24)) != temp_r9_2) {
                            temp_r10_3 = var_r4_3 >> 1;
                            if (var_r4_3 & 1) {
                                temp_r6_3 = 0x204;
                                temp_r6_3 += (temp_r10_3 * 4);
                                *((u8 *)gsgfxState + temp_r6_3) = (*((u8 *)gsgfxState + temp_r6_3) & ~0x7C000) | ((temp_r9_2 << 0xE) & 0x7C000);
                            } else {
                                temp_r6_4 = 0x206;
                                temp_r6_4 += (temp_r10_3 * 4);
                                *((u8 *)gsgfxState + temp_r6_4) = (*((u8 *)gsgfxState + temp_r6_4) & ~0x1F0) | ((temp_r9_2 << 4) & 0x1F0);
                            }
                            M2C_FIELD(gsgfxState, s32 *, 0x18) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x18) | (1 << temp_r10_3));
                            *((u8*)(gsgfxState) + (var_r5_4 + 0xA24)) = temp_r9_2;
                        }
                    }
                    var_r3_3 += 4;
                    var_r4_3 += 1;
                    var_r5_4 += 4;
                }
                M2C_FIELD(temp_r30, u32 *, 0x54) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x58) != 0) {
                var_r3_4 = temp_r31;
                var_r4_4 = 0;
                var_r5_5 = 0;
                while (var_r4_4 < (s32) M2C_FIELD(temp_r31, u8 *, 0x23C)) {
                    if (M2C_FIELD(temp_r30, u32 *, 0x58) & (1 << var_r4_4)) {
                        temp_r9_3 = M2C_FIELD(var_r3_4, s32 *, 0x8D4);
                        if ((s32) *((u8*)(gsgfxState) + (var_r5_5 + 0xA64)) != temp_r9_3) {
                            temp_r10_4 = var_r4_4 >> 1;
                            if (var_r4_4 & 1) {
                                temp_r6_5 = 0x205;
                                temp_r6_5 += (temp_r10_4 * 4);
                                *((u8 *)gsgfxState + temp_r6_5) = (*((u8 *)gsgfxState + temp_r6_5) & ~0xF8) | ((temp_r9_3 << 3) & 0xF8);
                            } else {
                                temp_r6_6 = 0x206;
                                temp_r6_6 += (temp_r10_4 * 4);
                                *((u8 *)gsgfxState + temp_r6_6) = (*((u8 *)gsgfxState + temp_r6_6) & ~0x3E) | ((temp_r9_3 << 1) & 0x3E);
                            }
                            M2C_FIELD(gsgfxState, s32 *, 0x18) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x18) | (1 << temp_r10_4));
                            *((u8*)(gsgfxState) + (var_r5_5 + 0xA64)) = temp_r9_3;
                        }
                    }
                    var_r3_4 += 4;
                    var_r4_4 += 1;
                    var_r5_5 += 4;
                }
                M2C_FIELD(temp_r30, u32 *, 0x58) = 0U;
            }
        }
        if (M2C_FIELD(temp_r30, u32 *, 0) & 0x20) {
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x5C) != 0) {
                var_r3_5 = temp_r31;
                var_r4_5 = 0;
                var_r5_6 = 0;
                var_r6_3 = 0;
                while (var_r4_5 < (s32) M2C_FIELD(temp_r31, u8 *, 0x23C)) {
                    if ((M2C_FIELD(temp_r30, u32 *, 0x5C) & (1 << var_r4_5)) && ((temp_r24_2 = M2C_FIELD(var_r3_5, s32 *, 0x914), temp_r7_4 = gsgfxState + var_r6_3, temp_r25 = M2C_FIELD(var_r3_5, s32 *, 0x918), (((s32) M2C_FIELD(temp_r7_4, s32 *, 0xAA4) == temp_r24_2) == 0)) || ((s32) M2C_FIELD(temp_r7_4, s32 *, 0xAA8) != temp_r25))) {
                        temp_r12_3 = 0x267;
                        temp_r12_3 += var_r5_6;
                        *((u8 *)gsgfxState + temp_r12_3) = (*((u8 *)gsgfxState + temp_r12_3) & ~3) | (temp_r24_2 & 3);
                        *((u8 *)gsgfxState + temp_r12_3) = (*((u8 *)gsgfxState + temp_r12_3) & ~0xC) | ((temp_r25 << 2) & 0xC);
                        M2C_FIELD(gsgfxState, s32 *, 0x20) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x20) | (1 << var_r4_5));
                        *((u8*)(gsgfxState) + (var_r6_3 + 0xAA4)) = temp_r24_2;
                        *((u8*)(gsgfxState) + (var_r6_3 + 0xAA8)) = temp_r25;
                    }
                    var_r3_5 += 8;
                    var_r4_5 += 1;
                    var_r5_6 += 4;
                    var_r6_3 += 8;
                }
                M2C_FIELD(temp_r30, u32 *, 0x5C) = 0U;
            }
            if ((u32) M2C_FIELD(temp_r30, u32 *, 0x60) != 0) {
                var_r25_12 = temp_r31;
                var_r26_11 = 0;
                do {
                    if (M2C_FIELD(temp_r30, u32 *, 0x60) & (1 << var_r26_11)) {
                        GSgfx_GCSetTevSwapModeTable(var_r26_11, M2C_FIELD(var_r25_12, s32 *, 0x994), M2C_FIELD(var_r25_12, s32 *, 0x998), M2C_FIELD(var_r25_12, s32 *, 0x99C), M2C_FIELD(var_r25_12, s32 *, 0x9A0));
                    }
                    var_r26_11 += 1;
                    var_r25_12 += 0x10;
                } while (var_r26_11 < 4);
                M2C_FIELD(temp_r30, u32 *, 0x60) = 0U;
            }
        }
        if (M2C_FIELD(temp_r30, u32 *, 0) & 0x40) {
            var_r29_3 = M2C_FIELD(temp_r31, s32 *, 0x9F0);
            temp_r0_5 = M2C_FIELD(temp_r31, u8 *, 0x9EC) != 0;
            var_r28_3 = temp_r0_5;
            if (((u8) M2C_FIELD(temp_r31, u8 *, 0x9E8) == 1) && (temp_r0_5 == 0)) {
                var_r28_3 = 1;
                var_r29_3 = 7;
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x64) & 1) {
                GSgfx_GCSetBlendMode(M2C_FIELD(temp_r31, s32 *, 0x9D4), M2C_FIELD(temp_r31, s32 *, 0x9D8), M2C_FIELD(temp_r31, s32 *, 0x9DC), M2C_FIELD(temp_r31, s32 *, 0x9E0));
            }
            if ((M2C_FIELD(temp_r30, s32 *, 0x64) & 2) && ((temp_r4_9 = M2C_FIELD(temp_r31, u8 *, 0x9E4), temp_r5_3 = M2C_FIELD(temp_r31, u8 *, 0x9E5), (((u8) M2C_FIELD(gsgfxState, u8 *, 0xBF2) == temp_r4_9) == 0)) || ((u8) M2C_FIELD(gsgfxState, u8 *, 0xBF3) != temp_r5_3))) {
                M2C_FIELD(gsgfxState, u8 *, 0x3E) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x3E) & ~1) | (temp_r4_9 & 1));
                M2C_FIELD(gsgfxState, u8 *, 0x3F) = temp_r5_3;
                M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 8);
                M2C_FIELD(gsgfxState, u8 *, 0xBF2) = temp_r4_9;
                M2C_FIELD(gsgfxState, u8 *, 0xBF3) = temp_r5_3;
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x64) & 4) {
                temp_r4_10 = M2C_FIELD(temp_r31, u8 *, 0x9E6);
                if ((u8) M2C_FIELD(gsgfxState, u8 *, 0xBC4) != temp_r4_10) {
                    M2C_FIELD(gsgfxState, u8 *, 0x3B) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x3B) & ~8) | ((temp_r4_10 << 3) & 8));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 4);
                    M2C_FIELD(gsgfxState, u8 *, 0xBC4) = temp_r4_10;
                }
                temp_r4_11 = M2C_FIELD(temp_r31, u8 *, 0x9E7);
                if ((u8) M2C_FIELD(gsgfxState, u8 *, 0xBC5) != temp_r4_11) {
                    M2C_FIELD(gsgfxState, u8 *, 0x3B) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x3B) & ~0x10) | ((temp_r4_11 << 4) & 0x10));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 4);
                    M2C_FIELD(gsgfxState, u8 *, 0xBC5) = temp_r4_11;
                }
                temp_r5_4 = M2C_FIELD(temp_r31, u8 *, 0x9E8);
                if (((u8) M2C_FIELD(gsgfxState, u8 *, 0xBE4) != var_r28_3) || ((s32) M2C_FIELD(gsgfxState, s32 *, 0xBE8) != var_r29_3) || ((u8) M2C_FIELD(gsgfxState, u8 *, 0xBEC) != temp_r5_4)) {
                    M2C_FIELD(gsgfxState, u8 *, 0x37) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x37) & ~1) | (var_r28_3 & 1));
                    M2C_FIELD(gsgfxState, u8 *, 0x37) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x37) & ~0xE) | ((var_r29_3 << 1) & 0xE));
                    M2C_FIELD(gsgfxState, u8 *, 0x37) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x37) & ~0x10) | ((temp_r5_4 << 4) & 0x10));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 2);
                    M2C_FIELD(gsgfxState, u8 *, 0xBE4) = var_r28_3;
                    M2C_FIELD(gsgfxState, s32 *, 0xBE8) = var_r29_3;
                    M2C_FIELD(gsgfxState, u8 *, 0xBEC) = temp_r5_4;
                }
            }
            if ((M2C_FIELD(temp_r30, s32 *, 0x64) & 8) && ((temp_r5_5 = M2C_FIELD(temp_r31, u8 *, 0x9E8), (((u8) M2C_FIELD(gsgfxState, u8 *, 0xBE4) == var_r28_3) == 0)) || ((s32) M2C_FIELD(gsgfxState, s32 *, 0xBE8) != var_r29_3) || ((u8) M2C_FIELD(gsgfxState, u8 *, 0xBEC) != temp_r5_5))) {
                M2C_FIELD(gsgfxState, u8 *, 0x37) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x37) & ~1) | (var_r28_3 & 1));
                M2C_FIELD(gsgfxState, u8 *, 0x37) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x37) & ~0xE) | ((var_r29_3 << 1) & 0xE));
                M2C_FIELD(gsgfxState, u8 *, 0x37) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x37) & ~0x10) | ((temp_r5_5 << 4) & 0x10));
                M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 2);
                M2C_FIELD(gsgfxState, u8 *, 0xBE4) = var_r28_3;
                M2C_FIELD(gsgfxState, s32 *, 0xBE8) = var_r29_3;
                M2C_FIELD(gsgfxState, u8 *, 0xBEC) = temp_r5_5;
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x64) & 0x10) {
                GSgfx_GCSetAlphaCompare(M2C_FIELD(temp_r31, s32 *, 0x9F4), M2C_FIELD(temp_r31, u8 *, 0xA00), M2C_FIELD(temp_r31, s32 *, 0x9F8), M2C_FIELD(temp_r31, s32 *, 0x9FC), M2C_FIELD(temp_r31, u8 *, 0xA01));
                temp_r4_12 = M2C_FIELD(temp_r31, u8 *, 0xA02);
                if ((u8) M2C_FIELD(gsgfxState, u8 *, 0xBF0) != temp_r4_12) {
                    M2C_FIELD(gsgfxState, u8 *, 0x43) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x43) & ~0x40) | ((temp_r4_12 << 6) & 0x40));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x10);
                    M2C_FIELD(gsgfxState, u8 *, 0xBF0) = temp_r4_12;
                }
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x64) & 0x20) {
                temp_r4_13 = M2C_FIELD(temp_r31, u8 *, 0xA04);
                if ((u8) M2C_FIELD(gsgfxState, u8 *, 0xBF1) != temp_r4_13) {
                    M2C_FIELD(gsgfxState, u8 *, 0x3B) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x3B) & ~4) | ((temp_r4_13 << 2) & 4));
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 4);
                    M2C_FIELD(gsgfxState, u8 *, 0xBF1) = temp_r4_13;
                }
            }
            temp_r3_3 = M2C_FIELD(temp_r30, s32 *, 0x64);
            if (temp_r3_3 & 0x40) {
                if ((u8) M2C_FIELD(temp_r31, u8 *, 0xA37) == 1) {
                    var_r24_2 = M2C_FIELD(temp_r31, s32 *, 0xA08);
                    switch (var_r24_2) {
                    case 0:
                            M2C_FIELD(temp_r31, u8 *, 0xA37) = 0U;
                        break;
                    }
                } else {
                    var_r24_2 = 0;
                }
                if (((s32) M2C_FIELD(gsgfxState, s32 *, 0xBF4) != var_r24_2) || (M2C_FIELD(gsgfxState, f32 *, 0xBF8) != M2C_FIELD(temp_r31, f32 *, 0xA0C)) || (M2C_FIELD(gsgfxState, f32 *, 0xBFC) != M2C_FIELD(temp_r31, f32 *, 0xA10)) || (M2C_FIELD(gsgfxState, f32 *, 0xC00) != M2C_FIELD(temp_r31, f32 *, 0xA14)) || (M2C_FIELD(gsgfxState, f32 *, 0xC04) != M2C_FIELD(temp_r31, f32 *, 0xA18))) {
                    GSgfx_GCWriteFog(var_r24_2);
                }
                if ((var_r24_2 != 0) && ((temp_r3_4 = M2C_FIELD(temp_r31, u32 *, 0xA1C), sp24 = temp_r3_4, (((u32) M2C_FIELD(gsgfxState, u32 *, 0xC09) == temp_r3_4) == 0)) || ((u8) M2C_FIELD(gsgfxState, u8 *, 0xC08) == 1))) {
                    sp18 = sp24;
                    M2C_FIELD(gsgfxState, u8 *, 0x2F5) = (u8) sp18;
                    M2C_FIELD(gsgfxState, u8 *, 0x2F6) = unksp19;
                    M2C_FIELD(gsgfxState, u8 *, 0x2F7) = unksp1A;
                    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x20000);
                    M2C_FIELD(gsgfxState, u32 *, 0xC09) = sp24;
                    M2C_FIELD(gsgfxState, u8 *, 0xC08) = 0U;
                }
            } else if ((temp_r3_3 & 0x80) && ((temp_r3_5 = M2C_FIELD(temp_r31, u32 *, 0xA1C), sp20 = temp_r3_5, (((u32) M2C_FIELD(gsgfxState, u32 *, 0xC09) == temp_r3_5) == 0)) || ((u8) M2C_FIELD(gsgfxState, u8 *, 0xC08) == 1))) {
                sp14 = sp20;
                M2C_FIELD(gsgfxState, u8 *, 0x2F5) = (u8) sp14;
                M2C_FIELD(gsgfxState, u8 *, 0x2F6) = unksp15;
                M2C_FIELD(gsgfxState, u8 *, 0x2F7) = unksp16;
                M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x20000);
                M2C_FIELD(gsgfxState, u32 *, 0xC09) = sp20;
                M2C_FIELD(gsgfxState, u8 *, 0xC08) = 0U;
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x64) & 0x100) {
                sp3C = M2C_FIELD(&jtbl_1693, f32 *, 0);
                sp40 = M2C_FIELD(&jtbl_1693, s32 *, 4);
                sp44 = M2C_FIELD(&jtbl_1693, f32 *, 8);
                sp48 = M2C_FIELD(&jtbl_1693, f32 *, 0xC);
                sp4C = M2C_FIELD(&jtbl_1693, s32 *, 0x10);
                sp50 = M2C_FIELD(&jtbl_1693, f32 *, 0x14);
                sp54 = M2C_FIELD(&jtbl_1693, f32 *, 0x18);
                sp58 = M2C_FIELD(&jtbl_1693, f32 *, 0x1C);
                sp5C = M2C_FIELD(&jtbl_1693, s32 *, 0x20);
                sp60 = M2C_FIELD(&jtbl_1693, s32 *, 0x24);
                sp64 = M2C_FIELD(&jtbl_1693, f32 *, 0x28);
                sp68 = M2C_FIELD(&jtbl_1693, s32 *, 0x2C);
                sp6C = M2C_FIELD(&jtbl_1693, s32 *, 0x30);
                sp70 = M2C_FIELD(&jtbl_1693, s32 *, 0x34);
                sp74 = M2C_FIELD(&jtbl_1693, s32 *, 0x38);
                sp78 = M2C_FIELD(&jtbl_1693, f32 *, 0x3C);
                temp_r3_6 = (unsigned char *)(GSgfxVideoGetViewport(M2C_ERROR( ), M2C_FIELD(&jtbl_1693, s32 *, 0x38), M2C_FIELD(&jtbl_1693, s32 *, 0x34), M2C_ERROR( ), M2C_ERROR( ), M2C_FIELD(&jtbl_1693, s32 *, 0x30), M2C_FIELD(&jtbl_1693, s32 *, 0x2C), M2C_ERROR( )));
                if ((s32) M2C_FIELD(temp_r31, s32 *, 0xE4) == 0) {
                    sp3C = M2C_FIELD(temp_r31, f32 *, 0xE8);
                    sp44 = M2C_FIELD(temp_r31, f32 *, 0xEC);
                    sp48 = 0.0f;
                    sp50 = M2C_FIELD(temp_r31, f32 *, 0xF0);
                    sp54 = M2C_FIELD(temp_r31, f32 *, 0xF4);
                    sp58 = 0.0f;
                    sp64 = M2C_FIELD(temp_r31, f32 *, 0xF8);
                    sp68 = M2C_FIELD(temp_r31, f32 *, 0xFC);
                    sp74 = -1.0f;
                    sp78 = 0.0f;
                } else {
                    sp3C = M2C_FIELD(temp_r31, f32 *, 0xE8);
                    sp44 = 0.0f;
                    sp48 = M2C_FIELD(temp_r31, f32 *, 0xEC);
                    sp50 = M2C_FIELD(temp_r31, f32 *, 0xF0);
                    sp54 = 0.0f;
                    sp58 = M2C_FIELD(temp_r31, f32 *, 0xF4);
                    sp64 = M2C_FIELD(temp_r31, f32 *, 0xF8);
                    sp68 = M2C_FIELD(temp_r31, f32 *, 0xFC);
                    sp74 = -1.0f;
                    sp78 = 0.0f;
                }
                GXInitFogAdjTable((GXFogAdjTable *)(temp_r31 + 0xA20), (unsigned short)(sp10), (const float (*)[4])&(M2C_FIELD(temp_r31, f32 *, 0xFC)));
            }
            if (M2C_FIELD(temp_r30, s32 *, 0x64) & 0x200) {
                GSgfx_GCSetFogRangeAdj((unsigned char)(M2C_FIELD(temp_r31, u8 *, 0xA36)), (unsigned short)(M2C_FIELD(temp_r31, u16 *, 0xA34)), (unsigned long *)(temp_r31 + 0xA20));
            }
            M2C_FIELD(temp_r30, s32 *, 0x64) = 0;
        }
        M2C_FIELD(temp_r30, u32 *, 0) = 0U;
    }
}
}
inline void GSgfx_GCSetFogRangeAdj(u8 en, u16 center, u32* adj) {
    u8 diff;
    if (gsgfxState->cC0D != en || gsgfxState->cC0E != center) {
        diff = 1;
    } else {
        diff = 0;
        if (gsgfxState->rangeCache.w[0] != adj[0]) {
            diff = 1;
        } else if (gsgfxState->rangeCache.w[1] != adj[1]) {
            diff = 1;
        } else if (gsgfxState->rangeCache.w[2] != adj[2]) {
            diff = 1;
        } else if (gsgfxState->rangeCache.w[3] != adj[3]) {
            diff = 1;
        } else if (gsgfxState->rangeCache.w[4] != adj[4]) {
            diff = 1;
        }
    }
    if (diff == 1) {
#define H ((u16*)adj)
        gsgfxState->fogRange.en = en;
        gsgfxState->fogRange.center = center + 0x156;
        gsgfxState->dirty |= 0x40000;
        gsgfxState->cC0D = en;
        gsgfxState->cC0E = center;
        if (en == 1) {
            gsgfxState->rangeAdj[0].r = H[0];
            gsgfxState->rangeAdj[0].k = H[1];
            gsgfxState->rangeAdj[1].r = H[2];
            gsgfxState->rangeAdj[1].k = H[3];
            gsgfxState->rangeAdj[2].r = H[4];
            gsgfxState->rangeAdj[2].k = H[5];
            gsgfxState->rangeAdj[3].r = H[6];
            gsgfxState->rangeAdj[3].k = H[7];
            gsgfxState->rangeAdj[4].r = H[8];
            gsgfxState->rangeAdj[4].k = H[9];
            gsgfxState->dirty |= 0x80000;
            u32* rc = gsgfxState->rangeCache.w;
            rc[0] = adj[0];
            rc[1] = adj[1];
            rc[2] = adj[2];
            rc[3] = adj[3];
            rc[4] = adj[4];
        }
    }
}

inline void GSgfx_GCSetAlphaCompare(s32 comp0, u8 ref0, s32 op, s32 comp1, u8 ref1) {
    if (gsgfxState->alphaCache.comp0 != comp0 || gsgfxState->alphaCache.ref0 != ref0 || gsgfxState->alphaCache.op != op ||
        gsgfxState->alphaCache.comp1 != comp1 || gsgfxState->alphaCache.ref1 != ref1) {
        gsgfxState->alphaCmp.ref0 = ref0;
        gsgfxState->alphaCmp.ref1 = ref1;
        gsgfxState->alphaCmp.comp0 = comp0;
        gsgfxState->alphaCmp.comp1 = comp1;
        gsgfxState->alphaCmp.op = op;
        gsgfxState->dirty |= 0x100;
        gsgfxState->alphaCache.comp0 = comp0;
        gsgfxState->alphaCache.ref0 = ref0;
        gsgfxState->alphaCache.op = op;
        gsgfxState->alphaCache.comp1 = comp1;
        gsgfxState->alphaCache.ref1 = ref1;
    }
}

inline void GSgfx_GCSetBlendMode(s32 type, s32 src, s32 dst, s32 lop) {
    if (gsgfxState->blendCache[0] != type || gsgfxState->blendCache[1] != src || gsgfxState->blendCache[2] != dst ||
        gsgfxState->blendCache[3] != lop) {
        int blend = 0;
        if (type == 1 || type == 3) {
            blend = 1;
        }
        gsgfxState->cmode0.blend = blend;
        gsgfxState->cmode0.logic = (type == 2);
        gsgfxState->cmode0.src = src;
        gsgfxState->cmode0.dst = dst;
        gsgfxState->cmode0.sub = (type == 3);
        gsgfxState->cmode0.lop = lop;
        gsgfxState->dirty |= 4;
        gsgfxState->blendCache[0] = type;
        gsgfxState->blendCache[1] = src;
        gsgfxState->blendCache[2] = dst;
        gsgfxState->blendCache[3] = lop;
    }
}

inline void GSgfx_GCSetTevSwapModeTable(s32 t, s32 r, s32 g, s32 b, s32 a) {
    u32 ss = t;
    if (gsgfxState->swapCache[ss][0] != r || gsgfxState->swapCache[ss][1] != g || gsgfxState->swapCache[ss][2] != b ||
        gsgfxState->swapCache[ss][3] != a) {
        int i1;
        int i0 = t * 2;
        i1 = i0 + 1;
        gsgfxState->ksel[i0].lo = r;
        gsgfxState->ksel[i0].hi = g;
        gsgfxState->ksel[i1].lo = b;
        gsgfxState->ksel[i1].hi = a;
        gsgfxState->dKsel |= 1 << i0;
        gsgfxState->dKsel |= 1 << i1;
        gsgfxState->swapCache[t][0] = r;
        gsgfxState->swapCache[t][1] = g;
        gsgfxState->swapCache[t][2] = b;
        gsgfxState->swapCache[t][3] = a;
    }
}

inline void GSgfx_GCSetTevKColor(u32 i, u32* c) {
    if (*(u32*)&gsgfxState->kcolFlag[i][1] != *c || gsgfxState->kcolFlag[i][0] == 1) {
        u32 v = *c;
        u8* b = (u8*)&v;
        gsgfxState->kcolB0[i].lo = b[0];
        gsgfxState->kcolB0[i].hi = b[3];
        gsgfxState->kcolB1[i].lo = b[2];
        gsgfxState->kcolB1[i].hi = b[1];
        gsgfxState->dKcolB |= 1 << i;
        *(u32*)&gsgfxState->kcolFlag[i][1] = v;
        gsgfxState->kcolFlag[i][0] = 0;
    }
}

inline void GSgfx_GCSetIndTexCoordScale(s32 stage, s32 s, s32 t) {
    int pair;
    u32 ss = stage;
    if (gsgfxState->indScale[ss][0] != s || gsgfxState->indScale[ss][1] != t) {
        pair = stage >> 1;
        if (stage & 1) {
            gsgfxState->ras1ss[pair].s1 = s;
            gsgfxState->ras1ss[pair].t1 = t;
        } else {
            gsgfxState->ras1ss[pair].s0 = s;
            gsgfxState->ras1ss[pair].t1 = t;
        }
        gsgfxState->dIref |= 1 << pair;
        gsgfxState->indScale[stage][0] = s;
        gsgfxState->indScale[stage][1] = t;
    }
}

inline void GSgfx_GCSetIndTexOrder(s32 stage, s32 coord, s32 map) {
    u32 ss = stage;
    if (gsgfxState->indOrder[ss][0] != coord || gsgfxState->indOrder[ss][1] != map) {
        switch (stage) {
        case 0:
            gsgfxState->iref.m0 = map;
            gsgfxState->iref.c0 = coord;
            break;
        case 1:
            gsgfxState->iref.m1 = map;
            gsgfxState->iref.c1 = coord;
            break;
        case 2:
            gsgfxState->iref.m2 = map;
            gsgfxState->iref.c2 = coord;
            break;
        case 3:
            gsgfxState->iref.m3 = map;
            gsgfxState->iref.c3 = coord;
            break;
        }
        gsgfxState->dirty |= 0x2000;
        gsgfxState->d0c |= 1 << coord;
        gsgfxState->indOrder[stage][0] = coord;
        gsgfxState->indOrder[stage][1] = map;
    }
}

inline void GSgfx_GCSetTevIndRepeat(s32 stage) {
    GSIndSet(stage, 0, 0, 0, 0, 6, 6, 1, 0, 0);
}

inline void GSgfx_GCSetTevIndBumpXYZ(s32 stage, u8 indId, u8 mtx) {
    GSIndSet(stage, (u16)indId, 0, 7, (u16)mtx, 0, 0, 0, 0, 0);
}

inline void GSgfx_GCSetTevIndWarp(s32 stage, u8 indId, u8 signMod, u8 wrap, u8 mtx) {
    int w = 0;
    if (wrap) {
        w = 6;
    }
    int bias = 0;
    bias = !(signMod) ? bias : 7;
    GSIndSet(stage, (u16)indId, 0, bias, mtx, w, w, 0, 0, 0);
}

inline void GSgfx_GCSetTevIndirect(s32 stage, u8 indId, u8 fmt, u8 bias, u8 mtx, u8 ws, u8 wt, s32 addPrev, u8 utc, s32 alpha) {
    GSIndSet(stage, indId, fmt, bias, mtx, ws, wt, addPrev, utc, alpha);
}

inline void GSgfx_GCSetTevDirect(s32 stage) {
    if (gsgfxState->indStatus[stage] != 1) {
        GSIndSet(stage, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        gsgfxState->indStatus[stage] = 1;
    }
}

inline void GSgfx_GCSetTevAlphaOp(s32 stage, s32 op, s32 bias, s32 scale, u8 clamp, s32 reg) {
    u32 ss = stage;
    if (gsgfxState->alphaOp[ss].op != op || gsgfxState->alphaOp[ss].bias != bias ||
        gsgfxState->alphaOp[ss].scale != scale || gsgfxState->alphaOp[ss].clamp != clamp ||
        gsgfxState->alphaOp[ss].reg != reg) {
        if (op <= 1) {
            gsgfxState->teva[stage].bias = bias;
            gsgfxState->teva[stage].op = op;
            gsgfxState->teva[stage].clamp = clamp;
            gsgfxState->teva[stage].scale = scale;
            gsgfxState->teva[stage].reg = reg;
        } else {
            gsgfxState->teva[stage].bias = 3;
            gsgfxState->teva[stage].op = op;
            gsgfxState->teva[stage].clamp = clamp;
            gsgfxState->teva[stage].scale = (u32)op >> 1;
            gsgfxState->teva[stage].reg = reg;
        }
        gsgfxState->dTeva |= 1 << stage;
        gsgfxState->alphaOp[stage].op = op;
        gsgfxState->alphaOp[stage].bias = bias;
        gsgfxState->alphaOp[stage].scale = scale;
        gsgfxState->alphaOp[stage].clamp = clamp;
        gsgfxState->alphaOp[stage].reg = reg;
    }
}

inline void GSgfx_GCSetTevColorOp(s32 stage, s32 op, s32 bias, s32 scale, u8 clamp, s32 reg) {
    u32 ss = stage;
    if (gsgfxState->colorOp[ss].op != op || gsgfxState->colorOp[ss].bias != bias ||
        gsgfxState->colorOp[ss].scale != scale || gsgfxState->colorOp[ss].clamp != clamp ||
        gsgfxState->colorOp[ss].reg != reg) {
        if (op <= 1) {
            gsgfxState->tevc[stage].bias = bias;
            gsgfxState->tevc[stage].op = op;
            gsgfxState->tevc[stage].clamp = clamp;
            gsgfxState->tevc[stage].scale = scale;
            gsgfxState->tevc[stage].reg = reg;
        } else {
            gsgfxState->tevc[stage].bias = 3;
            gsgfxState->tevc[stage].op = op;
            gsgfxState->tevc[stage].clamp = clamp;
            gsgfxState->tevc[stage].scale = (u32)op >> 1;
            gsgfxState->tevc[stage].reg = reg;
        }
        gsgfxState->dTevc |= 1 << stage;
        gsgfxState->colorOp[stage].op = op;
        gsgfxState->colorOp[stage].bias = bias;
        gsgfxState->colorOp[stage].scale = scale;
        gsgfxState->colorOp[stage].clamp = clamp;
        gsgfxState->colorOp[stage].reg = reg;
    }
}

inline void GSgfx_GCSetTevAlphaIn(s32 stage, s32 a, s32 b, s32 c, s32 d) {
    u32 ss = stage;
    if (gsgfxState->alphaIn[ss].a != a || gsgfxState->alphaIn[ss].b != b || gsgfxState->alphaIn[ss].c != c ||
        gsgfxState->alphaIn[ss].d != d) {
        gsgfxState->teva[stage].a = a;
        gsgfxState->teva[stage].b = b;
        gsgfxState->teva[stage].c = c;
        gsgfxState->teva[stage].d = d;
        gsgfxState->dTeva |= 1 << stage;
        gsgfxState->alphaIn[stage].a = a;
        gsgfxState->alphaIn[stage].b = b;
        gsgfxState->alphaIn[stage].c = c;
        gsgfxState->alphaIn[stage].d = d;
    }
}

inline void GSgfx_GCSetTevColorIn(s32 stage, s32 a, s32 b, s32 c, s32 d) {
    u32 ss = stage;
    if (gsgfxState->colorIn[ss].a != a || gsgfxState->colorIn[ss].b != b || gsgfxState->colorIn[ss].c != c ||
        gsgfxState->colorIn[ss].d != d) {
        gsgfxState->tevc[stage].a = a;
        gsgfxState->tevc[stage].b = b;
        gsgfxState->tevc[stage].c = c;
        gsgfxState->tevc[stage].d = d;
        gsgfxState->dTevc |= 1 << stage;
        gsgfxState->colorIn[stage].a = a;
        gsgfxState->colorIn[stage].b = b;
        gsgfxState->colorIn[stage].c = c;
        gsgfxState->colorIn[stage].d = d;
    }
}

inline void GSgfx_GCWriteTevOrder(s32 stage, s32 coord, s32 map, s32 color) {
    static u8 c2r[16] = {0, 1, 0, 1, 0, 1, 7, 5, 6, 0, 0, 0, 0, 0, 0, 7};
    int pair = stage >> 1;
    if (stage & 1) {
        gsgfxState->tref[pair].m1 = map;
        gsgfxState->tref[pair].c1 = coord;
        gsgfxState->tref[pair].en1 = (map != 0xff) && !(map & 0x100);
        gsgfxState->tref[pair].col1 = c2r[color & 0xf];
    } else {
        gsgfxState->tref[pair].m0 = map;
        gsgfxState->tref[pair].c0 = coord;
        gsgfxState->tref[pair].en0 = (map != 0xff) && !(map & 0x100);
        gsgfxState->tref[pair].col0 = c2r[color & 0xf];
    }
    gsgfxState->dTref |= 1 << pair;
    if (coord != 0xff) {
        gsgfxState->d0c |= 1 << coord;
    }
}

inline void GSgfx_GCSetTevOrder(s32 stage, s32 coord, s32 map, s32 color) {
    u32 ss = stage;
    if (gsgfxState->tevOrder[ss].a != coord || gsgfxState->tevOrder[ss].b != map ||
        gsgfxState->tevOrder[ss].c != color) {
        GSgfx_GCWriteTevOrder(stage, coord, map, color);
        gsgfxState->tevOrder[stage].a = coord;
        gsgfxState->tevOrder[stage].b = map;
        gsgfxState->tevOrder[stage].c = color;
    }
}

inline void GSgfx_GCSetMatColor(s32 ch, GSColor c) {
    int idx = (ch - 4) * 5;
    if (*(u32*)((u8*)gsgfxState + idx + 0x4c3) != RAW(c) || *((u8*)gsgfxState + idx + 0x4c2) == 1) {
        u32 v = RAW(c);
        u8* s = (u8*)gsgfxState;
        *(u32*)(s + idx + 0x4c3) = v;
        GSWriteXfColor(0x100c + (ch & 1), v);
        *((u8*)gsgfxState + idx + 0x4c2) = 0;
    }
}

inline void GSgfx_GCSetAmbColor(s32 ch, GSColor c) {
    int idx = (ch - 4) * 5;
    if (*(u32*)((u8*)gsgfxState + idx + 0x4b9) != RAW(c) || *((u8*)gsgfxState + idx + 0x4b8) == 1) {
        u32 v = RAW(c);
        u8* s = (u8*)gsgfxState;
        *(u32*)(s + idx + 0x4b9) = v;
        GSWriteXfColor(0x100a + (ch & 1), v);
        *((u8*)gsgfxState + idx + 0x4b8) = 0;
    }
}

void GSgfx_GCSetChanCtrl(s32 p0, u8 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6) {
    s32 temp_r11;
    s32 temp_r12;
    s32 temp_r12_2;
    s32 var_r27;
    u8 *temp_r10;

    temp_r12 = p0 * 0x18;
    temp_r11 = (long)(((u8*)(gsgfxState) + 0x458));
    if (((u8) *((u8 *)temp_r11 + temp_r12) != p1) || (temp_r10 = (unsigned char *)gsgfxState + temp_r12, (((s32) M2C_FIELD(temp_r10, s32 *, 0x45C) == p2) == 0)) || ((s32) M2C_FIELD(temp_r10, s32 *, 0x460) != p3) || ((s32) M2C_FIELD(temp_r10, s32 *, 0x464) != p4) || ((s32) M2C_FIELD(temp_r10, s32 *, 0x468) != p5) || ((s32) M2C_FIELD(temp_r10, s32 *, 0x46C) != p6)) {
        var_r27 = p5;
        if (p6 == 0) {
            var_r27 = 0;
        }
        *(s8 *)0xCC008000 = 0x10;
        *((u8 *)temp_r11 + temp_r12_2) = p1;
        *(s8 *)0xCC008000 = 0;
        *(s8 *)0xCC008000 = (s16) ((p0 & 3) + 0x100E);
        temp_r12_2 = p0 * 0x18;
        *(s8 *)0xCC008000 = (s32) (((p4 << 7) & 0x7800) | ((((u32) (-p6 | p6) >> 0x15U) & 0x400) | ((((u32) ((2 - p6) | (p6 - 2)) >> 0x16U) & 0x200) | ((p2 << 6) | (((p4 * 4) & 0x3C) | (p3 | ((p1 * 2) & 0x1FE))) | (var_r27 << 7)))));
        M2C_FIELD((gsgfxState + temp_r12_2), s32 *, 0x45C) = p2;
        M2C_FIELD((gsgfxState + temp_r12_2), s32 *, 0x460) = p3;
        M2C_FIELD((gsgfxState + temp_r12_2), s32 *, 0x464) = p4;
        M2C_FIELD((gsgfxState + temp_r12_2), s32 *, 0x468) = p5;
        M2C_FIELD((gsgfxState + temp_r12_2), s32 *, 0x46C) = p6;
    }
}

inline void GSgfx_GCSetScissor(u16 x, u16 y, u16 w, u16 h, s32 xo, s32 yo) {
    if (gsgfxState->scis[0] != x || gsgfxState->scis[1] != y || gsgfxState->scis[2] != w || gsgfxState->scis[3] != h ||
        gsgfxState->scisOff[0] != xo || gsgfxState->scisOff[1] != yo) {
        gsgfxState->scis0.x = x + (xo + 0x156);
        gsgfxState->scis[2] = w;
        gsgfxState->scis0.y = y + (yo + 0x156);
        gsgfxState->scis1.x = gsgfxState->scis0.x + (w - 1);
        gsgfxState->scis1.y = gsgfxState->scis0.y + (h - 1);
        gsgfxState->dirty |= 0x4000;
        gsgfxState->scis[0] = x;
        gsgfxState->scis[1] = y;
        gsgfxState->scis[3] = h;
        gsgfxState->scisOff[0] = xo;
        gsgfxState->scisOff[1] = yo;
    }
}

inline void GSgfx_GCSetProjection(s32 type, u32* p) {
    u8 diff;
    if (gsgfxState->c41c != type) {
        diff = 1;
    } else {
        diff = 0;
        if (gsgfxState->projCache[0] != p[0]) {
            diff = 1;
        } else if (p[1] != gsgfxState->projCache[1]) {
            diff = 1;
        } else if (gsgfxState->projCache[2] != p[2]) {
            diff = 1;
        } else if (gsgfxState->projCache[3] != p[3]) {
            diff = 1;
        } else if (gsgfxState->projCache[4] != p[4]) {
            diff = 1;
        } else if (gsgfxState->projCache[5] != p[5]) {
            diff = 1;
        }
    }
    if (diff == 1) {
        f32* f = (f32*)p;
        GX_WGPIPE.u8 = 0x10;
        GX_WGPIPE.u16 = 6;
        GX_WGPIPE.u16 = 0x1020;
        GX_WGPIPE.f32 = f[0];
        GX_WGPIPE.f32 = f[1];
        GX_WGPIPE.f32 = f[2];
        GX_WGPIPE.f32 = f[3];
        GX_WGPIPE.f32 = f[4];
        GX_WGPIPE.f32 = f[5];
        GX_WGPIPE.u32 = type;
        gsgfxState->c41c = type;
        gsgfxState->projCache[0] = p[0];
        gsgfxState->projCache[1] = p[1];
        gsgfxState->projCache[2] = p[2];
        gsgfxState->projCache[3] = p[3];
        gsgfxState->projCache[4] = p[4];
        gsgfxState->projCache[5] = p[5];
    }
}

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

extern "C" {
void GSgfx_GCInvalidateState();
void GSgfx_GCWriteVtxDesc(void*);
void GSgfx_GCWriteArray(s32 id, void* addr, u8 stride);
void GSgfx_GCWriteVtxAttrFmt(u32 idx, void* fmt);
void DCStoreRangeNoSync(void*, u32);
void PPCSync();
void GXLoadPosMtxImm(Mtx, u32);
void GXLoadNrmMtxImm(Mtx, u32);
void PSMTXInvXpose(const Mtx, Mtx);
void GSgfx_GCFlushState();
void GXInitTexObjTlut(void*, u32);
void GSgfx_GCWriteLoadTlut(void*, u32);
void GSgfx_GCWriteLoadTexObj(void*, u32);
}
int _foo;

static inline void LoadLayerMtx(GSgfxLayer* l) {
    GSgfxMtxEntry* m = l->mtxStack->top;
    GSgfxLayer::DirtyState* d = &l->dirty[l->dirtyIdx];
    if ((m->flags & 1) || m != d->mtx) {
        GXLoadPosMtxImm(m->mtx, 0x1b);
        GSgfxMtxStack* st = l->mtxStack;
        m = st->top;
        if (m->flags & 1) {
            PSMTXInvXpose(m->mtx, m->invXpose);
            st->top->flags &= ~1;
        }
        GXLoadNrmMtxImm(st->top->invXpose, 0x1b);
        d->mtx = l->mtxStack->top;
    }
    if (d->mtxValid == 0) {
        gsgfxState->matIdxA.pn = 0x1b;
        gsgfxState->dirty |= 0x40;
        d->mtxValid = 1;
    }
}

void GSgfxLayer::SetupRenderState() {
    LoadHWState();
    if (flags & 0x80000000) {
        GSgfx_GCInvalidateState();
        flags &= ~0x80000000;
    }
    if (flags & 0x20000000) {
        gsgfxState->dirty |= 0x10;
        flags &= ~0x20000000;
    }
    if (flags & 0x08000000) {
        GX_WGPIPE.u8 = 0x48;
        flags &= ~0x08000000;
    }
    if (flags & 0x10000000) {
        Reg b;
        Reg a;
        RAW(a) = 0;
        a.id = 0xf;
        RAW(b) = 0;
        GX_WGPIPE.u8 = 0x61;
        GX_WGPIPE.u32 = RAW(a);
        b.id = 0x66;
        b.v = 0x1000;
        GX_WGPIPE.u8 = 0x61;
        GX_WGPIPE.u32 = RAW(b);
        b.v = 0x1100;
        GX_WGPIPE.u8 = 0x61;
        GX_WGPIPE.u32 = RAW(b);
        gsgfxState->dirty |= 0x800;
        flags &= ~0x10000000;
    }
    if (flags & 0x40000000) {
        Reg c;
        c.id = 0x63;
        c.v = 0;
        GX_WGPIPE.u8 = 0x61;
        GX_WGPIPE.u32 = RAW(c);
        flags &= ~0x40000000;
    }
    u8 i;
    u8 n;
    DirtyState* d;
    RS* r;
    r = &rs;
    d = &dirty[dirtyIdx];
    if ((d->groups & 4) && (d->lightDirty & 0x10)) {
        for (i = 0, n = r->lightCount; i < n; i++) {
            r->lights[i]->Load(i);
        }
        d->lightDirty &= ~0x10;
    }
    SetupGPUState();
    int j;
    GSgfxTex* t;
    DirtyState* dd;
    GSgfxTex** tp;
    dd = &dirty[dirtyIdx];
    if (dd->texMask != 0 && rs.texCount != 0) {
        for (j = 0, tp = (GSgfxTex**)dd; j < 8; j++, tp++) {
            if (dd->texMask & (1 << j)) {
                t = tp[0x98 / 4];
                if (t->w == 0 || t->h == 0) {
                    _foo++;
                }
                if (t->tlut != 0) {
                    GXInitTexObjTlut(t->texObj, j);
                    GSgfx_GCWriteLoadTlut(t->tlutObj, j);
                }
                GSgfx_GCWriteLoadTexObj(t->texObj, j);
                t->reload = 0;
            }
        }
        dd->texMask = 0;
    }
    GSgfxVF* vf = curVF;
    if (vf != 0) {
        DirtyState* v = &dirty[dirtyIdx];
        if (v->last != vf || (vf->flags & 4)) {
            GSgfx_GCWriteVtxDesc(vf->vtxDesc);
            GSgfxVFArray* a = vf->arrays;
            while (a->id != 0xff) {
                GSgfx_GCWriteArray(a->id, a->addr, a->stride);
                a++;
            }
            v->last = vf;
        }
        if (v->vf[vf->fmt] != vf || (vf->flags & 2)) {
            s16 rf_t = vf->fmt;
            GSgfx_GCWriteVtxAttrFmt(rf_t, vf->attrFmt);
            v->vf[vf->fmt] = vf;
        }
        GSgfxVFArray* a = vf->arrays;
        u8 sync = 0;
        while (a->id != 0xff) {
            if (a->flags & 1) {
                DCStoreRangeNoSync(a->addr, a->size);
                sync = 1;
                a->flags &= ~1;
            }
            a++;
        }
        if (sync == 1) {
            PPCSync();
        }
        if (vf->flags & 8) {
            GX_WGPIPE.u8 = 0x48;
        }
        vf->flags &= ~6;
        if (GSgfxVFHasElement(curVF, 0) == 0) {
            LoadLayerMtx(this);
        }
    } else {
        LoadLayerMtx(this);
    }
    GSgfx_GCFlushState();
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

extern "C" { void* _emitTbl[] = {(void*)GSgfx_GCSetFogRangeAdj,(void*)GSgfx_GCSetAlphaCompare,(void*)GSgfx_GCSetBlendMode,(void*)GSgfx_GCSetTevSwapModeTable,(void*)GSgfx_GCSetTevKColor,(void*)GSgfx_GCSetIndTexCoordScale,(void*)GSgfx_GCSetIndTexOrder,(void*)GSgfx_GCSetTevIndRepeat,(void*)GSgfx_GCSetTevIndBumpXYZ,(void*)GSgfx_GCSetTevIndWarp,(void*)GSgfx_GCSetTevIndirect,(void*)GSgfx_GCSetTevDirect,(void*)GSgfx_GCSetTevAlphaOp,(void*)GSgfx_GCSetTevColorOp,(void*)GSgfx_GCSetTevAlphaIn,(void*)GSgfx_GCSetTevColorIn,(void*)GSgfx_GCSetTevOrder,(void*)GSgfx_GCSetMatColor,(void*)GSgfx_GCSetAmbColor,(void*)GSgfx_GCSetChanCtrl,(void*)GSgfx_GCSetScissor,(void*)GSgfx_GCSetProjection}; }
