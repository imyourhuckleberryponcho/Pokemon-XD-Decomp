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

struct RegBlend { u32 id : 8; u32 pad : 8; u32 pad2 : 3; u32 lop : 1; u32 sub : 1; u32 src : 3; u32 dst : 3; u32 alphaUpd : 1; u32 colorUpd : 1; u32 dither : 1; u32 logic : 1; u32 blend : 1; };
struct RegSS { u32 id : 8; u32 pad : 8; u32 t1 : 4; u32 s1 : 4; u32 t0 : 4; u32 s0 : 4; };
struct RegAlphaCmp { u32 id : 8; u32 op : 2; u32 comp1 : 3; u32 comp0 : 3; u32 ref1 : 8; u32 ref0 : 8; };
struct AlphaCache { s32 comp0, op, comp1; u8 ref0, ref1; };
struct W5 { u32 w[5]; };
struct RegScis { u32 id : 8; u32 x : 12; u32 y : 12; };
struct RegFogRange { u32 id : 8; u32 pad : 13; u32 en : 1; u32 center : 10; };
struct RegRangeAdj { u32 id : 8; u32 k : 12; u32 r : 12; };
struct RegTevC { u32 id : 8; u32 reg : 2; u32 scale : 2; u32 clamp : 1; u32 op : 1; u32 bias : 2; u32 a : 4; u32 b : 4; u32 c : 4; u32 d : 4; };
struct RegTevA { u32 id : 8; u32 reg : 2; u32 scale : 2; u32 clamp : 1; u32 op : 1; u32 bias : 2; u32 a : 3; u32 b : 3; u32 c : 3; u32 d : 3; u32 tswap : 2; u32 rswap : 2; };
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
struct RegCMode1 { u32 id : 8; u32 pad : 13; u32 f9 : 2; u32 en : 1; u32 alpha : 8; };
struct Reg { u32 id : 8; u32 v : 24; };
struct RegKcol { u32 id : 8; u32 pad : 1; u32 hi : 11; u32 pad2 : 1; u32 lo : 11; };
struct RegKsel { u32 id : 8; u32 kasel1 : 5; u32 kcsel1 : 5; u32 kasel0 : 5; u32 kcsel0 : 5; u32 hi : 2; u32 lo : 2; };
struct RegTlutLoad0 { u32 id : 8; u32 pad : 3; u32 a : 21; };
struct RegTlutLoad1 { u32 id : 8; u32 pad : 3; u32 b : 11; u32 c : 10; };
struct RegSu { u32 id : 8; u32 pad : 4; u32 pf : 1; u32 lf : 1; u32 pad2 : 2; u32 half : 16; };
struct RegFogCol { u32 id : 8; u32 r : 8; u32 g : 8; u32 b : 8; };
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
    RegFogCol r2f4;
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
    s32 c_fogType;
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
union GSWGPipe {
    u8 u8;
    u16 u16;
    u32 u32;
    f32 f32;
};
volatile GSWGPipe GSWGFifo : 0xCC008000;
#define GX_WGPIPE GSWGFifo

extern "C" {
struct GXFogAdjTable {
    u8 _draft[1];
};

extern "C" {
f32* GSgfxVideoGetViewport(void);
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
inline void GSgfx_GCSetTevIndBumpXYZ(s32 stage, u8 indId, s32 mtx);
inline void GSgfx_GCSetTevIndRepeat(s32 stage);
inline void GSgfx_GCSetTevIndWarp(s32 stage, u8 indId, u8 signMod, u8 wrap, s32 mtx);
inline void GSgfx_GCSetTevIndirect(s32 stage, u8 indId, s32 fmt, s32 bias, s32 mtx, s32 ws, s32 wt, u8 addPrev, u8 utc, s32 alpha);
inline void GSgfx_GCSetTevKColor(u32 i, GSColor c);
inline void GSgfx_GCSetTevOrder(s32 stage, s32 coord, s32 map, s32 color);
inline void GSgfx_GCSetTevSwapModeTable(s32 t, s32 r, s32 g, s32 b, s32 a);
void GSgfx_GCWriteFog(u32 type, f32 startz, f32 endz, f32 nearz, f32 farz);
void GSgfx_GCWriteTevIndBumpST(unsigned int stage, u8 indId, s32 mtx);
void GSgfx_GCWriteTevIndTile(u32 stage, u8 indId, u16 sizeS, u16 sizeT, u16 spaceS, u16 spaceT, u32 fmt, s32 mtx, u32 bias, u32 alpha);
void GSgfx_GCWriteTexCoordGen(u32 coord, s32 func, s32 src, u32 mtxIdx, u8 normalize, u32 postMtx);
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
struct GSgfxLayerTexGen {
    s32 func;
    s32 src;
    u32 mtx;
    u8 norm;
    u32 post;
    u8* tex;
};
struct GSgfxLayerChan {
    u8 enable;
    s32 amb;
    s32 mat;
    u32 lightMask;
    s32 diff;
    s32 attn;
    u8* lights[8];
};
struct GSgfxLayerTevColor {
    u32 type;
    union {
        GSColor c;
        s16 s10[4];
    };
};
struct GSgfxLayerInd {
    u32 type;
    union {
        struct {
            u8 indId;
            u8 pad[3];
            s32 fmt, bias, mtx, ws, wt, alpha;
            u8 addPrev, utc;
        } ind;
        struct {
            u8 indId, signMod, wrap;
            u8 pad;
            s32 mtx;
        } warp;
        struct {
            u8 indId;
            u8 pad;
            u16 sizeS, sizeT, spaceS, spaceT;
            u16 pad2;
            s32 fmt, mtx, bias, alpha;
        } tile;
        struct {
            u8 indId;
            u8 pad[3];
            s32 mtx;
        } bump;
    };
};
struct GSgfxLayerHW {
    u8 nTexGens;
    GSgfxLayerTexGen texGen[8];
    u8 lineWidth;
    s32 lineOffset;
    u8 pointSize;
    s32 pointOffset;
    u8 texOffsets[8][2];
    s32 projType;
    f32 proj[6];
    u16 scissor[4];
    f32 viewport[4];
    u8 coPlanar;
    s32 cullMode;
    s32 clipMode;
    u8 lightCount;
    u8* lights[8];
    u8 nChans;
    GSgfxLayerChan chan[4];
    GSColor amb[2];
    GSColor mat[2];
    u8 nTevStages;
    s32 tevOrder[16][3];
    s32 colorIn[16][4];
    s32 alphaIn[16][4];
    TevOpCache colorOp[16];
    TevOpCache alphaOp[16];
    GSgfxLayerTevColor tevColor[4];
    GSgfxLayerInd ind[4];
    u8 nIndStages;
    s32 indOrder[4][2];
    s32 indScale[4][2];
    GSColor kcolor[4];
    s32 kcsel[16];
    s32 kasel[16];
    s32 swapSel[16][2];
    s32 swapTab[4][4];
    s32 blend[4];
    u8 dstAlphaEnable;
    u8 dstAlpha;
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 zUpdate;
    u8 pad9e9[3];
    u8 zEnable;
    s32 zFunc;
    s32 alphaComp0;
    s32 alphaCmpOp;
    s32 alphaComp1;
    u8 alphaRef0;
    u8 alphaRef1;
    u8 zCompLoc;
    u8 pada03;
    u8 dither;
    s32 fogType;
    f32 fogStart;
    f32 fogEnd;
    f32 fogNear;
    f32 fogFar;
    GSColor fogColor;
    u16 fogTable[10];
    u16 fogCenter;
    u8 fogRangeEnable;
    u8 fogEnable;
};
struct GSgfxLayerDirty {
    u32 groups;
    u32 geom;
    u32 texGen;
    u32 texOffsets;
    u32 raster;
    u32 light;
    u32 chanCtrl;
    u32 amb;
    u32 mat;
    u32 tev;
    u32 tevOrder;
    u32 colorIn;
    u32 alphaIn;
    u32 colorOp;
    u32 alphaOp;
    u32 tevColor;
    u32 ind;
    u32 indStage;
    u32 indOrder;
    u32 indScale;
    u32 kcolor;
    u32 kcsel;
    u32 kasel;
    u32 swapSel;
    u32 swapTab;
    u32 pe;
};

extern "C" {

inline void GSgfx_GCSetNumTexGens(u8 n) {
    if (gsgfxState->c3f8 != n) {
        gsgfxState->genMode.nTex = n;
        gsgfxState->dirty |= 0x2000001;
        gsgfxState->c3f8 = n;
    }
}

inline void GSgfx_GCSetLineWidth(u8 width, s32 offset) {
    if (gsgfxState->sizeW0 != width || gsgfxState->sizeOff0 != offset) {
        gsgfxState->r1ec.lw = width;
        gsgfxState->r1ec.f16 = offset;
        gsgfxState->dirty |= 0x400;
        gsgfxState->sizeW0 = width;
        gsgfxState->sizeOff0 = offset;
    }
}

inline void GSgfx_GCSetPointSize(u8 size, s32 offset) {
    if (gsgfxState->sizeW1 != size || gsgfxState->sizeOff1 != offset) {
        gsgfxState->r1ec.pw = size;
        gsgfxState->r1ec.f19 = offset;
        gsgfxState->dirty |= 0x400;
        gsgfxState->sizeW1 = size;
        gsgfxState->sizeOff1 = offset;
    }
}

inline void GSgfx_GCSetTexOffsets(s32 coord, u8 line, u8 point) {
    if (gsgfxState->coordScale[coord * 2] != line || gsgfxState->coordScale[coord * 2 + 1] != point) {
        gsgfxState->suS[coord].lf = line;
        gsgfxState->suS[coord].pf = point;
        gsgfxState->d0c |= 1 << coord;
        gsgfxState->coordScale[coord * 2] = line;
        gsgfxState->coordScale[coord * 2 + 1] = point;
    }
}

inline void GSgfx_GCSetCoPlanar(u8 enable) {
    if (gsgfxState->c438 != enable) {
        gsgfxState->genMode.b19 = enable;
        gsgfxState->dirty |= 1;
        gsgfxState->c438 = enable;
    }
}

inline void GSgfx_GCWriteCullMode(s32 mode) {
    static const u8 cm2hw[4] = {0, 2, 1, 3};
    gsgfxState->genMode.cull = cm2hw[mode];
    gsgfxState->dirty |= 1;
    gsgfxState->c43c = mode;
}

inline void GSgfx_GCSetCullMode(s32 mode) {
    if (gsgfxState->c43c != mode) {
        GSgfx_GCWriteCullMode(mode);
    }
}

inline void GSgfx_GCSetTexCoordGen(u32 coord, s32 func, s32 src, u32 mtx, u8 norm, u32 post) {
    if (gsgfxState->texGen[coord].func != func || gsgfxState->texGen[coord].src != src ||
        gsgfxState->texGen[coord].mtx != mtx || gsgfxState->texGen[coord].norm != norm ||
        gsgfxState->texGen[coord].post != post) {
        GSgfx_GCWriteTexCoordGen(coord, func, src, mtx, norm, post);
    }
}

inline void GSgfx_GCSetClipMode(s32 mode) {
    if (gsgfxState->c440 != mode) {
        gsgfxState->xf1005 = mode;
        gsgfxState->dirty |= 0x4000000;
        gsgfxState->c440 = mode;
    }
}

inline void GSgfx_GCSetNumChans(u8 n) {
    if (gsgfxState->c454 != n) {
        gsgfxState->genMode.nChan = n;
        gsgfxState->dirty |= 0x1000001;
        gsgfxState->c454 = n;
    }
}

inline void GSgfx_GCSetNumTevStages(u8 n) {
    if (gsgfxState->c58c[0] != n) {
        gsgfxState->genMode.nTev = n - 1;
        gsgfxState->dirty |= 1;
        gsgfxState->c58c[0] = n;
    }
}

inline void GSgfx_GCSetNumIndStages(u8 n) {
    if (gsgfxState->c58c[1] != n) {
        gsgfxState->genMode.nInd = n;
        gsgfxState->dirty |= 1;
        gsgfxState->c58c[1] = n;
    }
}

inline void GSgfx_GCSetTevColor(s32 id, GSColor c) {
    gsgfxState->kcolA0[id].lo = c.r;
    gsgfxState->kcolA0[id].hi = c.a;
    gsgfxState->kcolA1[id].lo = c.b;
    gsgfxState->kcolA1[id].hi = c.g;
    gsgfxState->dKcolA |= 1 << id;
}

}

struct GSColorS10 { s16 r, g, b, a; };
inline void GSgfx_GCSetTevColorS10(s32 id, GSColorS10 c) {
    gsgfxState->kcolA0[id].lo = c.r & 0x7ff;
    gsgfxState->kcolA0[id].hi = c.a & 0x7ff;
    gsgfxState->kcolA1[id].lo = c.b & 0x7ff;
    gsgfxState->kcolA1[id].hi = c.g & 0x7ff;
    gsgfxState->dKcolA |= 1 << id;
}

inline void GSgfx_GCSetTevKColorSel(s32 stage, s32 sel) {
    if (gsgfxState->cA24[stage] != sel) {
        int pair = stage >> 1;
        if (stage & 1) {
            gsgfxState->ksel[pair].kcsel1 = sel;
        } else {
            gsgfxState->ksel[pair].kcsel0 = sel;
        }
        gsgfxState->dKsel |= 1 << pair;
        gsgfxState->cA24[stage] = sel;
    }
}

inline void GSgfx_GCSetTevKAlphaSel(s32 stage, s32 sel) {
    if (gsgfxState->cA24[stage + 16] != sel) {
        int pair = stage >> 1;
        if (stage & 1) {
            gsgfxState->ksel[pair].kasel1 = sel;
        } else {
            gsgfxState->ksel[pair].kasel0 = sel;
        }
        gsgfxState->dKsel |= 1 << pair;
        gsgfxState->cA24[stage + 16] = sel;
    }
}

inline void GSgfx_GCSetTevSwapMode(s32 stage, s32 ras, s32 tex) {
    if (gsgfxState->cA24[32 + stage * 2] != ras || gsgfxState->cA24[33 + stage * 2] != tex) {
        gsgfxState->teva[stage].rswap = ras;
        gsgfxState->teva[stage].tswap = tex;
        gsgfxState->dTeva |= 1 << stage;
        gsgfxState->cA24[32 + stage * 2] = ras;
        gsgfxState->cA24[33 + stage * 2] = tex;
    }
}

inline void GSgfx_GCSetDstAlpha(u8 enable, u8 alpha) {
    if (gsgfxState->cBF1[1] != enable || gsgfxState->cBF1[2] != alpha) {
        gsgfxState->cmode1.en = enable;
        gsgfxState->cmode1.alpha = alpha;
        gsgfxState->dirty |= 8;
        gsgfxState->cBF1[1] = enable;
        gsgfxState->cBF1[2] = alpha;
    }
}

inline void GSgfx_GCSetColorUpdate(u8 enable) {
    if (gsgfxState->cBC4[0] != enable) {
        gsgfxState->cmode0.colorUpd = enable;
        gsgfxState->dirty |= 4;
        gsgfxState->cBC4[0] = enable;
    }
}

inline void GSgfx_GCSetAlphaUpdate(u8 enable) {
    if (gsgfxState->cBC4[1] != enable) {
        gsgfxState->cmode0.alphaUpd = enable;
        gsgfxState->dirty |= 4;
        gsgfxState->cBC4[1] = enable;
    }
}

inline void GSgfx_GCSetZMode(u8 enable, s32 func, u8 update) {
    if (gsgfxState->cBE4 != enable || gsgfxState->cBE8 != func || gsgfxState->cBEC != update) {
        gsgfxState->zmode.enable = enable;
        gsgfxState->zmode.func = func;
        gsgfxState->zmode.update = update;
        gsgfxState->dirty |= 2;
        gsgfxState->cBE4 = enable;
        gsgfxState->cBE8 = func;
        gsgfxState->cBEC = update;
    }
}

inline void GSgfx_GCSetZCompLoc(u8 beforeTex) {
    if (gsgfxState->c_bf0 != beforeTex) {
        gsgfxState->peCtrl.zcomploc = beforeTex;
        gsgfxState->dirty |= 0x10;
        gsgfxState->c_bf0 = beforeTex;
    }
}

inline void GSgfx_GCSetDither(u8 dither) {
    if (gsgfxState->cBF1[0] != dither) {
        gsgfxState->cmode0.dither = dither;
        gsgfxState->dirty |= 4;
        gsgfxState->cBF1[0] = dither;
    }
}

inline void GSgfx_GCSetFogColor(GSColor c) {
    if (*(u32*)gsgfxState->padc09 != *(u32*)&c || gsgfxState->cC08 == 1) {
        gsgfxState->r2f4.r = c.r;
        gsgfxState->r2f4.g = c.g;
        gsgfxState->r2f4.b = c.b;
        gsgfxState->dirty |= 0x20000;
        *(u32*)gsgfxState->padc09 = *(u32*)&c;
        gsgfxState->cC08 = 0;
    }
}

extern "C" inline void GSgfx_GCSetFog(s32 type, f32 start, f32 end, f32 nearz, f32 farz) {
    if (gsgfxState->c_fogType != type || gsgfxState->c_fogStart != start || gsgfxState->c_fogEnd != end ||
        gsgfxState->c_fogNear != nearz || gsgfxState->c_fogFar != farz) {
        GSgfx_GCWriteFog(type, start, end, nearz, farz);
    }
}

static inline u16 __OSf32tou16(register f32 inF) {
    u16 out;
    u16* outP = &out;
    register u16* ptr = outP;
    asm { psq_st inF, 0(ptr), 1, 3 }
    return *ptr;
}

void GSgfxLayer::SetupGPUState() {
    GSgfxLayerHW* hw;
    GSgfxLayerDirty* d = (GSgfxLayerDirty*)((u8*)this + 0x16a8 + *(u32*)((u8*)this + 0x1994) * 0xb8);
    if (d->groups != 0) {
        hw = (GSgfxLayerHW*)&rs;
        if (d->groups & 1) {
            if (d->geom & 1) {
                GSgfx_GCSetNumTexGens(hw->nTexGens);
            }
            if (d->texGen != 0) {
                for (int i = 0; i < hw->nTexGens; i++) {
                    if (d->texGen & (1 << i)) {
                        GSgfxLayerTexGen* tg = &hw->texGen[i];
                        if (tg->tex != NULL) {
                            s16 rf_t = tg->tex[0x7c];
                            tg->func = rf_t + 2;
                        }
                        GSgfx_GCSetTexCoordGen(i, tg->func, tg->src, tg->mtx, tg->norm, tg->post);
                    }
                }
                d->texGen = 0;
            }
            if (d->geom & 4) {
                GSgfx_GCSetLineWidth(hw->lineWidth, hw->lineOffset);
            }
            if (d->geom & 8) {
                GSgfx_GCSetPointSize(hw->pointSize, hw->pointOffset);
            }
            if (d->texOffsets != 0) {
                for (int i = 0; i < hw->nTexGens; i++) {
                    if (d->texOffsets & (1 << i)) {
                        GSgfx_GCSetTexOffsets(i, hw->texOffsets[i][0], hw->texOffsets[i][1]);
                    }
                }
                d->texOffsets = 0;
            }
            if (d->geom & 0x20) {
                GSgfx_GCSetProjection(hw->projType, (u32*)hw->proj);
            }
            d->geom = 0;
        }
        if (d->groups & 2) {
            if (d->raster & 8) {
                GSgfx_GCSetCoPlanar(hw->coPlanar);
            }
            if (d->raster & 2) {
                GSgfx_GCSetCullMode(hw->cullMode);
            }
            if (d->raster & 4) {
                GSgfx_GCSetClipMode(hw->clipMode);
            }
            if (d->raster & 1) {
                GSgfx_GCSetScissor(hw->scissor[0], hw->scissor[1], hw->scissor[2], hw->scissor[3], 0, 0);
            }
            if (d->raster & 0x10) {
                GSgfxVideoSetViewport(hw->viewport[0], hw->viewport[1], hw->viewport[2], hw->viewport[3], false);
            }
            d->raster = 0;
        }
        if (d->groups & 4) {
            if (d->light & 1) {
                GSgfx_GCSetNumChans(hw->nChans);
            }
            if (d->chanCtrl != 0) {
                for (int i = 0; i < 4; i++) {
                    if (d->chanCtrl & (1 << i)) {
                        GSgfxLayerChan* ch = &hw->chan[i];
                        if (ch->enable != 0) {
                            s32 attn = ch->attn;
                            u8** lp;
                            u32 mask;
                            for (lp = ch->lights, mask = 0; *lp != NULL; lp++) {
                                u8* light = *lp;
                                for (u8 j = 0; j < 8; j++) {
                                    s32 type = *(s32*)(light + 4);
                                    if (attn == type || (attn == 2 && type == 1)) {
                                        mask |= 1 << light[0x7c];
                                    }
                                }
                            }
                            ch->lightMask = mask;
                        } else {
                            ch->lightMask = 0;
                        }
                        GSgfx_GCSetChanCtrl(i, ch->enable, ch->amb, ch->mat, ch->lightMask, ch->diff, ch->attn);
                    }
                }
                d->chanCtrl = 0;
            }
            if (d->amb != 0) {
                for (int i = 0; i < hw->nChans; i++) {
                    if (d->amb & (1 << i)) {
                        GSgfx_GCSetAmbColor(i + 4, hw->amb[i]);
                    }
                }
                d->amb = 0;
            }
            if (d->mat != 0) {
                for (int i = 0; i < hw->nChans; i++) {
                    if (d->mat & (1 << i)) {
                        GSgfx_GCSetMatColor(i + 4, hw->mat[i]);
                    }
                }
                d->mat = 0;
            }
            d->light = 0;
        }
        if (d->groups & 8) {
            if (d->tev & 1) {
                GSgfx_GCSetNumTevStages(hw->nTevStages);
            }
            if (d->tevOrder != 0) {
                for (int i = 0; i < hw->nTevStages; i++) {
                    if (d->tevOrder & (1 << i)) {
                        GSgfx_GCSetTevOrder(i, hw->tevOrder[i][0], hw->tevOrder[i][1], hw->tevOrder[i][2]);
                    }
                }
                d->tevOrder = 0;
            }
            if (d->colorIn != 0) {
                for (int i = 0; i < hw->nTevStages; i++) {
                    if (d->colorIn & (1 << i)) {
                        GSgfx_GCSetTevColorIn(i, hw->colorIn[i][0], hw->colorIn[i][1], hw->colorIn[i][2],
                                              hw->colorIn[i][3]);
                    }
                }
                d->colorIn = 0;
            }
            if (d->alphaIn != 0) {
                for (int i = 0; i < hw->nTevStages; i++) {
                    if (d->alphaIn & (1 << i)) {
                        GSgfx_GCSetTevAlphaIn(i, hw->alphaIn[i][0], hw->alphaIn[i][1], hw->alphaIn[i][2],
                                              hw->alphaIn[i][3]);
                    }
                }
                d->alphaIn = 0;
            }
            if (d->colorOp != 0) {
                for (int i = 0; i < hw->nTevStages; i++) {
                    if (d->colorOp & (1 << i)) {
                        GSgfx_GCSetTevColorOp(i, hw->colorOp[i].op, hw->colorOp[i].bias, hw->colorOp[i].scale,
                                              hw->colorOp[i].clamp, hw->colorOp[i].reg);
                    }
                }
                d->colorOp = 0;
            }
            if (d->alphaOp != 0) {
                for (int i = 0; i < hw->nTevStages; i++) {
                    if (d->alphaOp & (1 << i)) {
                        GSgfx_GCSetTevAlphaOp(i, hw->alphaOp[i].op, hw->alphaOp[i].bias, hw->alphaOp[i].scale,
                                              hw->alphaOp[i].clamp, hw->alphaOp[i].reg);
                    }
                }
                d->alphaOp = 0;
            }
            if (d->tevColor != 0) {
                for (int i = 0; i < 4; i++) {
                    if (d->tevColor & (1 << i)) {
                        if (hw->tevColor[i].type == 0) {
                            GSgfx_GCSetTevColor(i, hw->tevColor[i].c);
                        } else {
                            GSgfx_GCSetTevColorS10(i, *(GSColorS10*)hw->tevColor[i].s10);
                        }
                    }
                }
                d->tevColor = 0;
            }
            if (d->ind != 0) {
                for (int i = 0; i < 4; i++) {
                    if (d->ind & (1 << i)) {
                        GSgfxLayerInd* ind = &hw->ind[i];
                        switch (ind->type) {
                        case 0:
                            GSgfx_GCSetTevDirect(i);
                            break;
                        case 1:
                            GSgfx_GCSetTevIndirect(i, ind->ind.indId, ind->ind.fmt, ind->ind.bias, ind->ind.mtx,
                                                   ind->ind.ws, ind->ind.wt, ind->ind.addPrev, ind->ind.utc,
                                                   ind->ind.alpha);
                            break;
                        case 2:
                            s32 rf_t = ind->warp.signMod;
                            GSgfx_GCSetTevIndWarp(i, ind->warp.indId, rf_t, ind->warp.wrap,
                                                  ind->warp.mtx);
                            break;
                        case 3:
                            GSgfx_GCWriteTevIndTile(i, ind->tile.indId, ind->tile.sizeS, ind->tile.sizeT,
                                                    ind->tile.spaceS, ind->tile.spaceT, ind->tile.fmt, ind->tile.mtx,
                                                    ind->tile.bias, ind->tile.alpha);
                            break;
                        case 4:
                            GSgfx_GCWriteTevIndBumpST(i, ind->bump.indId, ind->bump.mtx);
                            break;
                        case 5:
                            GSgfx_GCSetTevIndBumpXYZ(i, ind->bump.indId, ind->bump.mtx);
                            break;
                        case 6:
                            GSgfx_GCSetTevIndRepeat(i);
                            break;
                        }
                    }
                }
                d->ind = 0;
            }
            d->tev = 0;
        }
        if (d->groups & 0x80) {
            if (d->indStage & 1) {
                GSgfx_GCSetNumIndStages(hw->nIndStages);
            }
            if (d->indOrder != 0) {
                for (int i = 0; i < 4; i++) {
                    if (d->indOrder & (1 << i)) {
                        GSgfx_GCSetIndTexOrder(i, hw->indOrder[i][0], hw->indOrder[i][1]);
                    }
                }
                d->indOrder = 0;
            }
            if (d->indScale != 0) {
                for (int i = 0; i < 4; i++) {
                    if (d->indScale & (1 << i)) {
                        GSgfx_GCSetIndTexCoordScale(i, hw->indScale[i][0], hw->indScale[i][1]);
                    }
                }
                d->indScale = 0;
            }
            d->indStage = 0;
        }
        if (d->groups & 0x10) {
            if (d->kcolor != 0) {
                for (int i = 0; i < 4; i++) {
                    if (d->kcolor & (1 << i)) {
                        GSgfx_GCSetTevKColor(i, hw->kcolor[i]);
                    }
                }
                d->kcolor = 0;
            }
            if (d->kcsel != 0) {
                for (int i = 0; i < hw->nTevStages; i++) {
                    if (d->kcsel & (1 << i)) {
                        GSgfx_GCSetTevKColorSel(i, hw->kcsel[i]);
                    }
                }
                d->kcsel = 0;
            }
            if (d->kasel != 0) {
                for (int i = 0; i < hw->nTevStages; i++) {
                    if (d->kasel & (1 << i)) {
                        s16 rf_t = hw->kasel[i];
                        GSgfx_GCSetTevKAlphaSel(i, rf_t);
                    }
                }
                d->kasel = 0;
            }
        }
        if (d->groups & 0x20) {
            if (d->swapSel != 0) {
                for (int i = 0; i < hw->nTevStages; i++) {
                    if (d->swapSel & (1 << i)) {
                        GSgfx_GCSetTevSwapMode(i, hw->swapSel[i][0], hw->swapSel[i][1]);
                    }
                }
                d->swapSel = 0;
            }
            if (d->swapTab != 0) {
                for (int i = 0; i < 4; i++) {
                    if (d->swapTab & (1 << i)) {
                        GSgfx_GCSetTevSwapModeTable(i, hw->swapTab[i][0], hw->swapTab[i][1], hw->swapTab[i][2],
                                                    hw->swapTab[i][3]);
                    }
                }
                d->swapTab = 0;
            }
        }
        if (d->groups & 0x40) {
            int zEnable = hw->zEnable != 0;
            s32 zFunc = hw->zFunc;
            if (hw->zUpdate == 1 && zEnable == 0) {
                zEnable = 1;
                zFunc = 7;
            }
            if (d->pe & 1) {
                GSgfx_GCSetBlendMode(hw->blend[0], hw->blend[1], hw->blend[2], hw->blend[3]);
            }
            if (d->pe & 2) {
                GSgfx_GCSetDstAlpha(hw->dstAlphaEnable, hw->dstAlpha);
            }
            if (d->pe & 4) {
                GSgfx_GCSetColorUpdate(hw->colorUpdate);
                GSgfx_GCSetAlphaUpdate(hw->alphaUpdate);
                GSgfx_GCSetZMode(zEnable, zFunc, hw->zUpdate);
            }
            if (d->pe & 8) {
                GSgfx_GCSetZMode(zEnable, zFunc, hw->zUpdate);
            }
            if (d->pe & 0x10) {
                GSgfx_GCSetAlphaCompare(hw->alphaComp0, hw->alphaRef0, hw->alphaCmpOp, hw->alphaComp1, hw->alphaRef1);
                GSgfx_GCSetZCompLoc(hw->zCompLoc);
            }
            if (d->pe & 0x20) {
                GSgfx_GCSetDither(hw->dither);
            }
            if (d->pe & 0x40) {
                s32 fogType;
                if (hw->fogEnable == 1) {
                    fogType = hw->fogType;
                    if (fogType == 0) {
                        hw->fogEnable = 0;
                    }
                } else {
                    fogType = 0;
                }
                GSgfx_GCSetFog(fogType, hw->fogStart, hw->fogEnd, hw->fogNear, hw->fogFar);
                if (fogType != 0) {
                    GSgfx_GCSetFogColor(hw->fogColor);
                }
            } else if (d->pe & 0x80) {
                GSgfx_GCSetFogColor(hw->fogColor);
            }
            if (d->pe & 0x100) {
                f32 m[4][4] = {0};
                f32* vp = GSgfxVideoGetViewport();
                if (hw->projType == 0) {
                    m[0][0] = hw->proj[0];
                    m[0][2] = hw->proj[1];
                    m[0][3] = 0.0f;
                    m[1][1] = hw->proj[2];
                    m[1][2] = hw->proj[3];
                    m[1][3] = 0.0f;
                    m[2][2] = hw->proj[4];
                    m[2][3] = hw->proj[5];
                    m[3][2] = -1.0f;
                    m[3][3] = 0.0f;
                } else {
                    m[0][0] = hw->proj[0];
                    m[0][2] = 0.0f;
                    m[0][3] = hw->proj[1];
                    m[1][1] = hw->proj[2];
                    m[1][2] = 0.0f;
                    m[1][3] = hw->proj[3];
                    m[2][2] = hw->proj[4];
                    m[2][3] = hw->proj[5];
                    m[3][2] = -1.0f;
                    m[3][3] = 0.0f;
                }
                GXInitFogAdjTable((GXFogAdjTable*)hw->fogTable, __OSf32tou16(vp[2]), m);
            }
            if (d->pe & 0x200) {
                GSgfx_GCSetFogRangeAdj(hw->fogRangeEnable, hw->fogCenter, (u32*)hw->fogTable);
            }
            d->pe = 0;
        }
        d->groups = 0;
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

inline void GSgfx_GCSetTevKColor(u32 i, GSColor c) {
    if (*(u32*)&gsgfxState->kcolFlag[i][1] != *(u32*)&c || gsgfxState->kcolFlag[i][0] == 1) {
        u32 v = *(u32*)&c;
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

inline void GSgfx_GCSetTevIndBumpXYZ(s32 stage, u8 indId, s32 mtx) {
    GSIndSet(stage, (u16)indId, 0, 7, (u16)mtx, 0, 0, 0, 0, 0);
}

#pragma push
#pragma optimize_for_size on
inline void GSgfx_GCSetTevIndWarp(s32 stage, u8 indId, u8 signMod, u8 wrap, s32 mtx) {
    int w = 0;
    if (wrap) {
        w = 6;
    }
    int bias = 0;
    bias = !(signMod) ? bias : 7;
    GSIndSet(stage, indId, 0, (u16)bias, mtx, w, w, 0, 0, 0);
}
#pragma pop

inline void GSgfx_GCSetTevIndirect(s32 stage, u8 indId, s32 fmt, s32 bias, s32 mtx, s32 ws, s32 wt, u8 addPrev, u8 utc, s32 alpha) {
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
