// WIP (NonMatching): game's own GX register writers (BP/CP/XF commands built with bitfield structs).
// Game's own GX register writer (Dolphin GX BP/CP/XF commands built from bitfield structs).
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


extern "C" void* memset(void* dst, int c, unsigned long n);

struct GlobalRegState {
    u8 b0, b1, b2, b3, b4;
};

struct CopyReq {
    u16 left;     // 0x00
    u16 top;      // 0x02
    u16 width;    // 0x04
    u16 height;   // 0x06
    u16 dstWidth; // 0x08
    u16 pad0a;
    u32 clamp;    // 0x0c
    u32 f10;
    u32 f14;
    f32 gamma;    // 0x18
    u8 clear;     // 0x1c
    u8 r, g, b, a; // 0x1d..0x20
    u8 pad21[3];
    u32 z; // 0x24
};

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
struct RegSrc {  // 0x49 / 0x4a
    u32 id : 8;
    u32 pad : 4;
    u32 y : 10;
    u32 x : 10;
};
struct RegYScale {  // 0x4e
    u32 id : 8;
    u32 pad : 15;
    u32 scale : 9;
};
struct RegStride {  // 0x4d
    u32 id : 8;
    u32 pad : 14;
    u32 stride : 10;
};
struct RegDest {  // 0x4b
    u32 id : 8;
    u32 pad : 3;
    u32 addr : 21;
};
struct RegCopyCmd {  // 0x52
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
struct RegMsLoc {  // 0x01..0x04
    u32 id : 8;
    u32 y2 : 4;
    u32 x2 : 4;
    u32 y1 : 4;
    u32 x1 : 4;
    u32 y0 : 4;
    u32 x0 : 4;
};
struct RegCoeff {  // 0x53 / 0x54
    u32 id : 8;
    u32 c3 : 6;
    u32 c2 : 6;
    u32 c1 : 6;
    u32 c0 : 6;
};
struct RegCopyTexCmd {  // 0x52 as built by the texture copy
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
    s32 fmt;     // 0x0c
    u32 clamp;   // 0x10
    u8 mip;      // 0x14
    u8 clear;    // 0x15
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
extern GSState* gsgfxState;

struct RegX22 { u32 id : 8; u32 pad23 : 1; u32 b22 : 1; u32 f19 : 3; u32 f16 : 3; u32 pw : 8; u32 lw : 8; };
struct RegX68 { u32 id : 8; u32 pad : 23; u32 b0 : 1; };
struct RegCMode1 { u32 id : 8; u32 pad : 13; u32 f9 : 2; u32 pad2 : 9; };
struct Reg { u32 id : 8; u32 v : 24; };
struct RegKcol { u32 id : 8; u32 f : 1; u32 rest : 23; };
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
    u32 dirty;            // 0x00
    u32 dTref;            // 0x04
    u32 dIref;            // 0x08
    u32 d0c;              // 0x0c  coord size dirty
    u32 d10;              // 0x10  texture dirty
    u32 d14;              // 0x14  tlut dirty
    u32 dKsel;            // 0x18
    u32 dTevc;            // 0x1c
    u32 dTeva;            // 0x20
    u32 dKcolA;           // 0x24
    u32 dKcolB;           // 0x28
    u32 indDirty;         // 0x2c
    RegGenMode genMode;   // 0x30
    RegZMode zmode;       // 0x34
    RegCMode0 cmode0;     // 0x38
    RegCMode1 cmode1;     // 0x3c
    RegPeCtrl peCtrl;     // 0x40
    Reg r44;              // 0x44
    Reg r48;              // 0x48
    Reg scis0;            // 0x4c
    Reg scis1;            // 0x50
    u32 xf1005;           // 0x54
    RegTref tref[8];      // 0x58
    RegIref iref;         // 0x78
    Reg ras1ss0;          // 0x7c
    Reg ras1ss1;          // 0x80
    RegId24 texMode0[8];  // 0x84
    RegId24 texMode1[8];  // 0xa4
    RegTexImg0 texImg0[8]; // 0xc4
    RegTexImg texImg1[8]; // 0xe4
    RegTexImg texImg2[8]; // 0x104
    RegId24 texImg3[8];   // 0x124
    RegTlutW texTlut[8];  // 0x144
    TlutCache tlutCache[8]; // 0x164
    RegTlutLoad0 tlutLoad0; // 0x1a4
    RegTlutLoad1 tlutLoad1; // 0x1a8
    RegSu suS[8];         // 0x1ac
    RegSu suT[8];         // 0x1cc
    RegX22 r1ec;          // 0x1ec
    RegMatIdxA matIdxA;   // 0x1f0
    RegMatIdxB matIdxB;   // 0x1f4
    Reg r1f8;             // 0x1f8
    Reg r1fc;             // 0x1fc
    Reg r200;             // 0x200
    RegKsel ksel[8];      // 0x204
    Reg tevc[16];         // 0x224
    Reg teva[16];         // 0x264
    RegKcol kcolA0[4];        // 0x2a4
    RegKcol kcolA1[4];        // 0x2b4
    RegKcol kcolB0[4];        // 0x2c4
    RegKcol kcolB1[4];        // 0x2d4
    RegFog0 fog0;         // 0x2e4
    RegFog1 fog1;         // 0x2e8
    RegFog2 fog2;         // 0x2ec
    RegFog3 fog3;         // 0x2f0
    Reg r2f4;             // 0x2f4
    Reg r2f8;             // 0x2f8
    Reg rangeAdj[5];      // 0x2fc
    RegIndCmd indCmd[16]; // 0x310
    Reg r350;             // 0x350
    RegX68 r354;          // 0x354
    TexGenCache texGen[8]; // 0x358
    u8 c3f8;              // 0x3f8
    u8 pad3f9[3];
    u8 sizeW0;            // 0x3fc
    u8 pad3fd[3];
    s32 sizeOff0;         // 0x400
    u8 sizeW1;            // 0x404
    u8 pad405[3];
    s32 sizeOff1;         // 0x408
    u8 coordScale[16];    // 0x40c
    s32 c41c;             // 0x41c
    u8 pad420[0x438 - 0x420];
    u8 c438;              // 0x438
    u8 pad439[3];
    s32 c43c;             // 0x43c
    s32 c440;             // 0x440
    u16 scis[4];          // 0x444
    s32 scisOff[2];       // 0x44c
    u8 c454;              // 0x454
    u8 pad455[3];
    ChanCache chan[4];    // 0x458
    u8 ambMat[4][5];      // 0x4b8
    TevOrderCache tevOrder[16]; // 0x4cc
    u8 c58c[2];           // 0x58c
    u8 pad58e[2];
    TevInCache colorIn[16]; // 0x590
    TevInCache alphaIn[16]; // 0x690
    TevOpCache colorOp[16]; // 0x790
    TevOpCache alphaOp[16]; // 0x8d0
    u8 kcolFlag[4][5];    // 0xa10
    s32 cA24[80];         // 0xa24
    u8 indStatus[16];     // 0xb64
    s32 cB74[20];         // 0xb74
    u8 cBC4[2];           // 0xbc4
    u8 padbc6[2];
    s32 cBC8[3];          // 0xbc8
    u8 cBD4[2];           // 0xbd4
    u8 padbd6[2];
    s32 cBD8[3];          // 0xbd8
    u8 cBE4;              // 0xbe4
    u8 padbe5[3];
    s32 cBE8;             // 0xbe8
    u8 cBEC;              // 0xbec
    u8 padbed[3];
    u8 c_bf0;             // 0xbf0
    u8 cBF1[3];
    u32 c_fogType;        // 0xbf4
    f32 c_fogStart;       // 0xbf8
    f32 c_fogEnd;         // 0xbfc
    f32 c_fogNear;        // 0xc00
    f32 c_fogFar;         // 0xc04
    u8 cC08;              // 0xc08
    u8 padc09[4];
    u8 cC0D;              // 0xc0d
    u16 cC0E;             // 0xc0e
    u8 padc10[0xc24 - 0xc10];
    f32 vp[6];            // 0xc24
    s32 cC3C;             // 0xc3c
};
#define RAW(r) (*(u32*)&(r))

extern "C" {


u32 GSgfx_GCTmemRegions[16] = {0x00000000, 0x00080000, 0x00010000, 0x00088000, 0x00020000, 0x00090000, 0x00030000, 0x00098000,
                               0x00040000, 0x000A0000, 0x00050000, 0x000A8000, 0x00060000, 0x000B0000, 0x00070000, 0x000B8000};
u32 GSgfx_GCTlutRegions[20] = {0x000C0000, 0x000C2000, 0x000C4000, 0x000C6000, 0x000C8000, 0x000CA000, 0x000CC000,
                               0x000CE000, 0x000D0000, 0x000D2000, 0x000D4000, 0x000D6000, 0x000D8000, 0x000DA000,
                               0x000DC000, 0x000DE000, 0x000E0000, 0x000E8000, 0x000F0000, 0x000F8000};
static u8 _gcDefaultAASample[24] = {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};
u8 GSgfx_GCTexMode0Ids[8] = {0x80, 0x81, 0x82, 0x83, 0xA0, 0xA1, 0xA2, 0xA3};
u8 GSgfx_GCTexMode1Ids[8] = {0x84, 0x85, 0x86, 0x87, 0xA4, 0xA5, 0xA6, 0xA7};
u8 GSgfx_GCTexImage0Ids[8] = {0x88, 0x89, 0x8A, 0x8B, 0xA8, 0xA9, 0xAA, 0xAB};
u8 GSgfx_GCTexImage1Ids[8] = {0x8C, 0x8D, 0x8E, 0x8F, 0xAC, 0xAD, 0xAE, 0xAF};
u8 GSgfx_GCTexImage2Ids[8] = {0x90, 0x91, 0x92, 0x93, 0xB0, 0xB1, 0xB2, 0xB3};
u8 GSgfx_GCTexImage3Ids[8] = {0x94, 0x95, 0x96, 0x97, 0xB4, 0xB5, 0xB6, 0xB7};
u8 GSgfx_GCTexTlutIds[8] = {0x98, 0x99, 0x9A, 0x9B, 0xB8, 0xB9, 0xBA, 0xBB};
static u8 _gcDefaultVFilt[7] = {0, 0, 0x15, 0x16, 0x15, 0, 0};
static void* _gcLastTlutObj;
static s32 _gcLastTlutName;
GlobalRegState _gcGlobalRegState;

// ---- draft declarations ----


extern "C" {
void GSgfxVideoGetEFBSize(u16* w, u16* h);
void GSgfx_GCFlushState(void);
void GSgfx_GCWriteFog(u32 type, f32 startz, f32 endz, f32 nearz, f32 farz);
void GSgfx_GCWriteTexCoordGen(u32 coord, s32 func, s32 src, u32 mtxIdx, u8 normalize, u32 postMtx);
extern s32 jtbl_1414;
extern s32 jtbl_1415;
extern s32 cm2hw_localstatic3_GSgfx_GCWriteCullMode;
extern s32 c2r_localstatic3_GSgfx_GCWriteTevOrder;
}

static inline void WrBP(u8*& p, u32 v) {
    *p = 0x61;
    *(u32*)(p + 1) = v;
    p += 5;
}

u8* GSgfx_GCWriteCopyDispDirect(u8* p, CopyReq* req, u32 dest, u8 colorUpd, u8 alphaUpd, u8 clear) {
    RegClearAR car; RegClearZ cz; RegCMode0 cm; RegZMode zm; RegPeCtrl pe;
    RegYScale ys; RegSrc src; RegSrc size; RegStride st; RegDest dst; RegCopyCmd cmd;
    if (req->clear == 1) {
        RAW(pe) = 0;
        RAW(zm) = 0;
        RAW(cm) = 0;
        cm.blend = 0;
        pe.pixfmt = _gcGlobalRegState.b2;
        pe.zfmt = _gcGlobalRegState.b3;
        cm.colorUpd = colorUpd;
        pe.zcomploc = 0;
        cm.alphaUpd = alphaUpd;
        cm.id = 0x41;
        zm.id = 0x40;
        pe.id = 0x43;
        if (clear == 1) {
            zm.enable = 1;
            zm.func = 7;
            zm.update = 1;
        } else {
            zm.enable = 0;
            zm.update = 0;
        }
        WrBP(p, RAW(cm));
        WrBP(p, RAW(zm));
        WrBP(p, RAW(pe));
    }
    RAW(car) = 0;
    car.id = 0x4f;
    car.a = req->a;
    car.r = req->r;
    WrBP(p, RAW(car));
    car.id = 0x50;
    car.a = req->g;
    car.r = req->b;
    WrBP(p, RAW(car));
    cz.id = 0x51;
    cz.z = req->z;
    WrBP(p, RAW(cz));
    RAW(ys) = 0; RAW(src) = 0; RAW(size) = 0; RAW(st) = 0; RAW(dst) = 0; RAW(cmd) = 0;
    ys.id = 0x4e; src.id = 0x49; size.id = 0x4a; st.id = 0x4d; dst.id = 0x4b; cmd.id = 0x52;
    ys.scale = (u32)(256.0f / req->gamma);
    cmd.f14 = 1;
    cmd.clamp = req->clamp;
    cmd.f7_8 = req->f14;
    size.x = req->width - 1;
    src.x = req->left;
    size.y = req->height - 1;
    cmd.f12_13 = req->f10;
    st.stride = req->dstWidth >> 4;
    dst.addr = dest >> 5;
    src.y = req->top;
    cmd.f11 = req->clear;
    if (ys.scale == 0x100) cmd.f10 = 0; else cmd.f10 = 1;
    WrBP(p, RAW(ys));
    WrBP(p, RAW(src));
    WrBP(p, RAW(size));
    WrBP(p, RAW(st));
    WrBP(p, RAW(dst));
    WrBP(p, RAW(cmd));
    return p;
}

#define FIFO8 (*(volatile u8*)0xCC008000)
#define FIFO16 (*(volatile u16*)0xCC008000)
#define FIFO32 (*(volatile u32*)0xCC008000)
static inline void WrFifo(u32 v) {
    FIFO8 = 0x61;
    FIFO32 = v;
}

u8* GSgfx_GCWriteCopyFilterDirect(u8* p, u8 aa, u8* pat, u8 vf, u8* vfilt) {
    RegMsLoc ms;
    RegCoeff co;
    int i, j;
    if (!aa) pat = _gcDefaultAASample;
    if (!vf) vfilt = _gcDefaultVFilt;
    for (i = 0, j = 0; i < 4; i++, j += 6) {
        ms.x0 = pat[j];
        ms.x1 = pat[j + 2];
        ms.x2 = pat[j + 4];
        ms.y0 = pat[j + 1];
        ms.y1 = pat[j + 2];
        ms.y2 = pat[j + 4];
        ms.id = i + 1;
        WrBP(p, RAW(ms));
    }
    co.c0 = vfilt[0];
    co.c1 = vfilt[1];
    co.id = 0x53;
    co.c2 = vfilt[2];
    co.c3 = vfilt[3];
    WrBP(p, RAW(co));
    co.c0 = vfilt[4];
    co.c1 = vfilt[5];
    co.id = 0x54;
    co.c2 = vfilt[6];
    co.c3 = 0;
    WrBP(p, RAW(co));
    return p;
}
void GSgfx_GCWriteCopyDisp(CopyReq* req, u32 dest, u8 colorUpd, u8 alphaUpd, u8 clear) {
    RegClearAR car; RegClearZ cz; RegCMode0 cm; RegZMode zm; RegPeCtrl pe;
    RegYScale ys; RegSrc src; RegSrc size; RegStride st; RegDest dst; RegCopyCmd cmd;
    if (req->clear == 1) {
        RAW(pe) = 0;
        RAW(zm) = 0;
        RAW(cm) = 0;
        cm.blend = 0;
        pe.pixfmt = _gcGlobalRegState.b2;
        pe.zfmt = _gcGlobalRegState.b3;
        cm.colorUpd = colorUpd;
        pe.zcomploc = 0;
        cm.alphaUpd = alphaUpd;
        cm.id = 0x41;
        zm.id = 0x40;
        pe.id = 0x43;
        if (clear == 1) {
            zm.enable = 1;
            zm.func = 7;
            zm.update = 1;
        } else {
            zm.enable = 0;
            zm.update = 0;
        }
        WrFifo(RAW(cm));
        WrFifo(RAW(zm));
        WrFifo(RAW(pe));
    }
    RAW(car) = 0;
    car.id = 0x4f;
    car.a = req->a;
    car.r = req->r;
    WrFifo(RAW(car));
    car.id = 0x50;
    car.a = req->g;
    car.r = req->b;
    WrFifo(RAW(car));
    cz.id = 0x51;
    cz.z = req->z;
    WrFifo(RAW(cz));
    RAW(ys) = 0; RAW(src) = 0; RAW(size) = 0; RAW(st) = 0; RAW(dst) = 0; RAW(cmd) = 0;
    ys.id = 0x4e; src.id = 0x49; size.id = 0x4a; st.id = 0x4d; dst.id = 0x4b; cmd.id = 0x52;
    ys.scale = (u32)(256.0f / req->gamma);
    size.x = req->width - 1;
    src.x = req->left;
    size.y = req->height - 1;
    st.stride = req->dstWidth >> 4;
    dst.addr = dest >> 5;
    src.y = req->top;
    cmd.f12_13 = req->f10;
    WrFifo(RAW(ys));
    WrFifo(RAW(src));
    cmd.clamp = req->clamp;
    WrFifo(RAW(size));
    WrFifo(RAW(st));
    WrFifo(RAW(dst));
    cmd.f14 = 1;
    cmd.f7_8 = req->f14;
    cmd.f11 = req->clear;
    if (ys.scale == 0x100) cmd.f10 = 0; else cmd.f10 = 1;
    WrFifo(RAW(cmd));
}

static inline void FlushPE() {
    GSState* st = gsgfxState;
    if (st->dirty & 0x10) WrFifo(*(u32*)&st->peCtrl);
    if (st->dirty & 0x04) WrFifo(*(u32*)&st->cmode0);
    st->dirty &= ~0x14;
}

void GSgfx_GCWriteCopyTex(CopyTexReq* req, u32 dest) {
    u8 oldPix;
    u8 savedZ = 0xfe;
    u32 savedBlend = 0xfefefefe;
    RegSrc src, size; RegStride st2; RegDest dst; RegCopyTexCmd cmd;
    if (req->fmt & 0x10) {
        oldPix = gsgfxState->peCtrl.pixfmt;
        gsgfxState->peCtrl.pixfmt = 3;
        gsgfxState->dirty |= 0x10;
    }
    if (req->clear == 1) {
        u8 z = gsgfxState->c_bf0;
        if (z != 0) {
            gsgfxState->peCtrl.zcomploc = 0;
            savedZ = z;
            gsgfxState->dirty |= 0x10;
        }
        s32 b = gsgfxState->cB74[16];
        if (b != 0) {
            gsgfxState->cmode0.blend = 0;
            savedBlend = b;
            gsgfxState->dirty |= 0x04;
        }
        FlushPE();
    }
    RAW(src) = 0; RAW(size) = 0; RAW(st2) = 0; RAW(dst) = 0; RAW(cmd) = 0;
    src.id = 0x49; size.id = 0x4a; st2.id = 0x4d; dst.id = 0x4b; cmd.id = 0x52;
    size.x = req->width - 1;
    src.x = req->left;
    src.y = req->top;
    size.y = req->height - 1;
    int sh;
    switch (req->fmt) {
    case 0: case 1: case 2: case 14: case 17: case 32: case 34: case 39: case 40: case 41: case 42: case 48: case 57: case 58:
        sh = 8;
        break;
    case 3: case 4: case 5: case 19: case 35: case 43: case 44: case 60:
        sh = 4;
        break;
    case 6: case 22: case 38:
        sh = 2;
        break;
    default:
        sh = 0;
        break;
    }
    switch (sh) {
    case 2: st2.stride = req->dstWidth >> 1; break;
    case 4: st2.stride = req->dstWidth >> 2; break;
    case 8: st2.stride = req->dstWidth >> 3; break;
    }
    cmd.clamp = req->clamp;
    cmd.fmt3 = (req->fmt >> 3) & 1;
    dst.addr = (dest & 0x3fffffff) >> 5;
    cmd.fmt = req->fmt;
    cmd.b16 = 1;
    cmd.mip = req->mip;
    cmd.clear = req->clear;
    if (req->fmt < 4 && req->fmt >= 0) cmd.b15 = 1; else cmd.b15 = 0;
    WrFifo(RAW(src));
    WrFifo(RAW(size));
    WrFifo(RAW(st2));
    WrFifo(RAW(dst));
    WrFifo(RAW(cmd));
    if (req->fmt & 0x10) {
        gsgfxState->peCtrl.pixfmt = oldPix;
        gsgfxState->dirty |= 0x10;
    }
    if (req->clear == 1) {
        if (savedZ != 0xfe) {
            gsgfxState->peCtrl.zcomploc = savedZ;
            gsgfxState->dirty |= 0x10;
        }
        if (savedBlend != 0xfefefefe) {
            gsgfxState->cmode0.blend = 1;
            gsgfxState->dirty |= 0x04;
        }
        FlushPE();
    }
}

void GSgfx_GCWriteCopyFilter(u8 aa, u8* pat, u8 vf, u8* vfilt) {
    RegMsLoc ms;
    RegCoeff co;
    int i, j;
    if (!aa) pat = _gcDefaultAASample;
    if (!vf) vfilt = _gcDefaultVFilt;
    for (i = 0, j = 0; i < 4; i++, j += 6) {
        ms.id = i + 1;
        ms.x0 = pat[j];
        ms.y0 = pat[j + 1];
        ms.x1 = pat[j + 2];
        ms.x2 = pat[j + 4];
        ms.y1 = pat[j + 2];
        ms.y2 = pat[j + 4];
        WrFifo(RAW(ms));
    }
    co.c0 = vfilt[0];
    co.id = 0x53;
    co.c1 = vfilt[1];
    co.c2 = vfilt[2];
    co.c3 = vfilt[3];
    WrFifo(RAW(co));
    co.c0 = vfilt[4];
    co.c1 = vfilt[5];
    co.id = 0x54;
    co.c2 = vfilt[6];
    co.c3 = 0;
    WrFifo(RAW(co));
}

void GSgfx_GCWriteFog(u32 type, f32 startz, f32 endz, f32 nearz, f32 farz) {
    f32 c, a, A, B, Bm;
    u32 bs, bm;
    u32 fsel = type & 7;
    u32 proj = (type >> 3) & 1;
    if (fsel != 0) {
        if (proj) {
            if (farz == nearz || endz == startz) {
                a = 0.0f;
                c = 0.0f;
            } else {
                A = 1.0f / (endz - startz);
                a = A * (farz - nearz);
                c = A * (startz - nearz);
            }
            bs = 0;
            bm = 0;
        } else {
            if (farz == nearz || endz == startz) {
                A = 0.0f;
                B = 0.5f;
                c = 0.0f;
            } else {
                A = (farz * nearz) / ((farz - nearz) * (endz - startz));
                B = farz / (farz - nearz);
                c = startz / (endz - startz);
            }
            Bm = B;
            bs = 1;
            while (Bm > 1.0f) {
                Bm *= 0.5f;
                bs++;
            }
            while (Bm > 0.0f && Bm < 0.5f) {
                Bm *= 2.0f;
                bs--;
            }
            a = A / (f32)(1 << bs);
            bm = (u32)(8388638.0f * Bm);
        }
        u32 a_hex = *(u32*)&a;
        u32 c_hex = *(u32*)&c;
        gsgfxState->fog0.a = a_hex >> 12;
        gsgfxState->fog1.bm = bm;
        gsgfxState->fog2.bs = bs;
        gsgfxState->fog3.c = c_hex >> 12;
        gsgfxState->fog3.proj = proj;
        gsgfxState->dirty |= 0x8000;
    }
    gsgfxState->fog3.fsel = fsel;
    gsgfxState->dirty |= 0x10000;
    gsgfxState->c_fogType = type;
    gsgfxState->c_fogStart = startz;
    gsgfxState->c_fogEnd = endz;
    gsgfxState->c_fogNear = nearz;
    gsgfxState->c_fogFar = farz;
}

static inline void SetTevIndirect(u32 stage, u8 indId, u8 fmt, u8 bias, u8 mtx, u8 ws, u8 wt, u8 addPrev, u8 utc,
                                  u8 alpha) {
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

void GSgfx_GCWriteTevIndBumpST(unsigned int stage, bool indId, s32 mtx) {
    int selS, selT;
    switch (mtx) {
    case 1:
        selS = 5;
        selT = 9;
        break;
    case 2:
        selS = 6;
        selT = 10;
        break;
    case 3:
        selS = 7;
        selT = 11;
        break;
    default:
        return;
    }
    SetTevIndirect(stage, (u16)indId, 0, 3, selS, 6, 6, 0, 0, 0);
    SetTevIndirect(stage + 1, indId, 0, 3, selT, 6, 6, 1, 0, 0);
    SetTevIndirect(stage + 2, indId, 0, 0, 0, 0, 0, 1, 0, 0);
}

#define SETF(reg, size, shift, val)     ((reg) = (u32)__rlwimi((u32)(reg), (val), (shift), 32 - (shift) - (size), 31 - (shift)))

static inline void WrIndTexMtx(u32 id, f32* m, s8 scale) {
    s32 mtx[6];
    u32 reg;
    mtx[0] = (int)(1024.0f * m[0]) & 0x7FF;
    mtx[1] = (int)(1024.0f * m[3]) & 0x7FF;
    mtx[2] = (int)(1024.0f * m[1]) & 0x7FF;
    mtx[3] = (int)(1024.0f * m[4]) & 0x7FF;
    mtx[4] = (int)(1024.0f * m[2]) & 0x7FF;
    mtx[5] = (int)(1024.0f * m[5]) & 0x7FF;
    scale = scale + 17;
    reg = 0;
    SETF(reg, 11, 0, mtx[0]);
    SETF(reg, 11, 11, mtx[1]);
    SETF(reg, 2, 22, scale & 3);
    SETF(reg, 8, 24, id + 6);
    WrFifo(reg);
    reg = 0;
    SETF(reg, 11, 0, mtx[2]);
    SETF(reg, 11, 11, mtx[3]);
    SETF(reg, 2, 22, (scale >> 2) & 3);
    SETF(reg, 8, 24, id + 7);
    WrFifo(reg);
    reg = 0;
    SETF(reg, 11, 0, mtx[4]);
    SETF(reg, 11, 11, mtx[5]);
    SETF(reg, 2, 22, (scale >> 4) & 3);
    SETF(reg, 8, 24, id + 8);
    WrFifo(reg);
}

void GSgfx_GCWriteTevIndTile(u32 stage, u8 indId, u16 sizeS, u16 sizeT, u16 spaceS, u16 spaceT, u32 fmt, s32 mtx,
                             u8 bias, u32 alpha) {
    u32 ws, wt, id;
    f32 m[6];
    switch (sizeS) {
    case 0x100: ws = 1; break;
    case 0x80: ws = 2; break;
    case 0x40: ws = 3; break;
    case 0x20: ws = 4; break;
    case 0x10: ws = 5; break;
    default: return;
    }
    switch (sizeT) {
    case 0x100: wt = 1; break;
    case 0x80: wt = 2; break;
    case 0x40: wt = 3; break;
    case 0x20: wt = 4; break;
    case 0x10: wt = 5; break;
    default: return;
    }
    m[0] = spaceS * (1.0f / 1024.0f);
    m[4] = spaceT * (1.0f / 1024.0f);
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[5] = 0.0f;
    switch (mtx) {
    case 1: id = 0; break;
    case 2: id = 3; break;
    case 3: id = 6; break;
    }
    WrIndTexMtx(id, m, 10);
    SetTevIndirect(stage, indId, fmt, bias, mtx, ws, wt, 0, 1, alpha);
}


void GSgfx_GCWriteIndTexMtx(u32 mtx, f32* m, s32 scale) {
    switch (mtx) {
    case 1: mtx = 0; break;
    case 2: mtx = 3; break;
    case 3: mtx = 6; break;
    }
    WrIndTexMtx(mtx, m, scale);
}

void GSgfx_GCWriteTexCoordGen(u32 coord, s32 func, s32 src, u32 mtxIdx, u8 normalize, u32 postMtx) {
    u32 form = 0;
    s32 type;
    u32 proj = 0;
    s32 row = 5;
    s32 light = 5;
    s32 esrc = 0;
    switch (src) {
    case 0: row = 0; form = 1; break;
    case 1: row = 1; form = 1; break;
    case 2: row = 3; form = 1; break;
    case 3: row = 4; form = 1; break;
    case 19: row = 2; break;
    case 20: row = 2; break;
    case 4: row = 5; break;
    case 5: row = 6; break;
    case 6: row = 7; break;
    case 7: row = 8; break;
    case 8: row = 9; break;
    case 9: row = 10; break;
    case 10: row = 11; break;
    case 11: row = 12; break;
    case 12: light = 0; break;
    case 13: light = 1; break;
    case 14: light = 2; break;
    case 15: light = 3; break;
    case 16: light = 4; break;
    case 17: light = 5; break;
    case 18: light = 6; break;
    }
    switch (func) {
    case 1:
        type = 0;
        break;
    case 0:
        type = 0;
        proj = 1;
        break;
    case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        esrc = func - 2;
        type = 1;
        break;
    case 10:
        if (src == 0x13) type = 2; else type = 3;
        break;
    }
    switch (coord) {
    case 0: gsgfxState->matIdxA.t0 = mtxIdx; gsgfxState->dirty |= 0x40; break;
    case 1: gsgfxState->matIdxA.t1 = mtxIdx; gsgfxState->dirty |= 0x40; break;
    case 2: gsgfxState->matIdxA.t2 = mtxIdx; gsgfxState->dirty |= 0x40; break;
    case 3: gsgfxState->matIdxA.t3 = mtxIdx; gsgfxState->dirty |= 0x40; break;
    case 4: gsgfxState->matIdxB.t4 = mtxIdx; gsgfxState->dirty |= 0x80; break;
    case 5: gsgfxState->matIdxB.t5 = mtxIdx; gsgfxState->dirty |= 0x80; break;
    case 6: gsgfxState->matIdxB.t6 = mtxIdx; gsgfxState->dirty |= 0x80; break;
    case 7: gsgfxState->matIdxB.t7 = mtxIdx; gsgfxState->dirty |= 0x80; break;
    }
    FIFO8 = 0x10;
    FIFO16 = 0;
    FIFO16 = 0x1040 + coord;
    FIFO32 = (proj << 1) | (form << 2) | (type << 4) | (row << 7) | (light << 12) | (esrc << 15);
    FIFO8 = 0x10;
    FIFO16 = 0;
    FIFO16 = 0x1050 + coord;
    FIFO32 = (postMtx - 0x40) | (normalize << 8);
    gsgfxState->texGen[coord].func = func;
    gsgfxState->texGen[coord].src = src;
    gsgfxState->texGen[coord].mtx = mtxIdx;
    gsgfxState->texGen[coord].norm = normalize;
    gsgfxState->texGen[coord].post = postMtx;
}

void GSgfx_GCWriteLoadTexObj(TexObj* obj, s32 id) {
    u32 w0 = obj->w0;
    u32 w1 = obj->w1;
    gsgfxState->texMode0[id].v = w0;
    gsgfxState->texMode1[id].v = w1;
    gsgfxState->texImg0[id].a.v = obj->w2;
    gsgfxState->texImg1[id].b21 = 0;
    gsgfxState->texImg1[id].addr = GSgfx_GCTmemRegions[id * 2] >> 5;
    gsgfxState->texImg1[id].cw = 3;
    gsgfxState->texImg1[id].ch = 3;
    gsgfxState->texImg2[id].addr = GSgfx_GCTmemRegions[id * 2 + 1] >> 5;
    gsgfxState->texImg2[id].cw = 3;
    gsgfxState->texImg2[id].ch = 3;
    gsgfxState->texImg3[id].v = obj->w3;
    s32 fmt = gsgfxState->texImg0[id].b.fmt;
    switch (fmt) {
    case 8:
    case 9:
    case 10: {
        u32 region = GSgfx_GCTlutRegions[_gcLastTlutName];
        TlutObj* tl = (TlutObj*)_gcLastTlutObj;
        gsgfxState->texTlut[id].a.v = tl->w0;
        u32 tm = ((region - 0x80000) >> 9) & 0xffff;
        gsgfxState->texTlut[id].b.tmem = tm;
        gsgfxState->tlutCache[id].a = ((TlutObj*)_gcLastTlutObj)->w1 & 0xffffff;
        gsgfxState->tlutCache[id].b = ((TlutObj*)_gcLastTlutObj)->h8 >> 4;
        gsgfxState->tlutCache[id].c = tm;
        gsgfxState->d14 |= 1 << id;
        break;
    }
    }
    switch (gsgfxState->genMode.nInd) {
    case 4:
        if (gsgfxState->iref.m3 == id) gsgfxState->d0c |= 1 << gsgfxState->iref.c3;
    case 3:
        if (gsgfxState->iref.m2 == id) gsgfxState->d0c |= 1 << gsgfxState->iref.c2;
    case 2:
        if (gsgfxState->iref.m1 == id) gsgfxState->d0c |= 1 << gsgfxState->iref.c1;
    case 1:
        if (gsgfxState->iref.m0 == id) gsgfxState->d0c |= 1 << gsgfxState->iref.c0;
    }
    for (int i = 0; i <= (gsgfxState->genMode.nTev >> 1); i++) {
        if (gsgfxState->tref[i].m0 == id) gsgfxState->d0c |= 1 << gsgfxState->tref[i].c0;
        if (gsgfxState->tref[i].m1 == id) gsgfxState->d0c |= 1 << gsgfxState->tref[i].c1;
    }
    gsgfxState->d10 |= 1 << id;
}

struct VtxAttrEntry {
    s32 attr;
    s32 cnt;
    s32 type;
    u8 frac;
};
struct VtxDescEntry {
    s32 attr;
    s32 type;
};

void GSgfx_GCWriteLoadTlut(void* obj, s32 name) {
    _gcLastTlutObj = obj;
    _gcLastTlutName = name;
}

void GSgfx_GCWriteVtxAttrFmt(u32 fmt, VtxAttrEntry* list) {
    u32 attr;
    s32 nrmType = 4, nrmCnt = 1, nrmFlag = 0;
    s32 posCnt = 1, posType = 4, posFrac = 0;
    s32 c0Cnt = 1, c0Type = 5;
    s32 c1Cnt = 1, c1Type = 5;
    s32 t0Cnt = 1, t0Type = 4, t0Frac = 0;
    s32 t1Cnt = 1, t1Type = 4, t1Frac = 0;
    s32 t5Cnt = 1, t5Type = 4, t5Frac = 0;
    s32 t3Cnt = 1, t3Type = 4, t3Frac = 0;
    s32 t4Cnt = 1, t4Type = 4, t4Frac = 0;
    s32 t2Cnt = 1, t2Type = 4, t2Frac = 0;
    s32 t6Cnt = 1, t6Type = 4, t6Frac = 0;
    s32 t7Cnt = 1, t7Type = 4, t7Frac = 0;
    for (; (attr = list->attr) != 0xff; list++) {
        switch (attr) {
        case 9:
            posCnt = list->cnt;
            posType = list->type;
            posFrac = list->frac;
            break;
        case 10:
        case 25: {
            s32 cnt = list->cnt;
            nrmType = list->type;
            if (cnt == 2) {
                nrmCnt = 1;
                nrmFlag = 1;
            } else {
                nrmCnt = cnt;
                nrmFlag = 0;
            }
            break;
        }
        case 11:
            c0Cnt = list->cnt;
            c0Type = list->type;
            break;
        case 12:
            c1Cnt = list->cnt;
            c1Type = list->type;
            break;
        case 13:
            t0Cnt = list->cnt;
            t0Type = list->type;
            t0Frac = list->frac;
            break;
        case 14:
            t1Cnt = list->cnt;
            t1Type = list->type;
            t1Frac = list->frac;
            break;
        case 15:
            t2Cnt = list->cnt;
            t2Type = list->type;
            t2Frac = list->frac;
            break;
        case 16:
            t3Cnt = list->cnt;
            t3Type = list->type;
            t3Frac = list->frac;
            break;
        case 17:
            t4Cnt = list->cnt;
            t4Type = list->type;
            t4Frac = list->frac;
            break;
        case 18:
            t5Cnt = list->cnt;
            t5Type = list->type;
            t5Frac = list->frac;
            break;
        case 19:
            t6Cnt = list->cnt;
            t6Type = list->type;
            t6Frac = list->frac;
            break;
        case 20:
            t7Cnt = list->cnt;
            t7Type = list->type;
            t7Frac = list->frac;
            break;
        }
    }
    FIFO8 = 8;
    FIFO8 = 0x70 + fmt;
    FIFO32 = (posCnt | (posType << 1) | (posFrac << 4) | (nrmCnt << 9) | (nrmType << 10) | (c0Cnt << 13) |
              (c0Type << 14) | (c1Cnt << 17) | (c1Type << 18) | (t0Cnt << 21) | (t0Type << 22) | (t0Frac << 25) |
              (nrmFlag << 31) | 0x40000000);
    FIFO8 = 8;
    FIFO8 = 0x80 + fmt;
    FIFO32 = (t1Cnt | (t1Type << 1) | (t1Frac << 4) | (t2Cnt << 9) | (t2Type << 10) | (t2Frac << 13) |
              (t3Cnt << 18) | (t3Type << 19) | (t3Frac << 22) | (t4Cnt << 27) | (t4Type << 28) | 0x80000000);
    FIFO8 = 8;
    FIFO8 = 0x90 + fmt;
    FIFO32 = (t4Frac | (t5Cnt << 5) | (t5Type << 6) | (t5Frac << 9) | (t6Cnt << 14) | (t6Type << 15) |
              (t6Frac << 18) | (t7Cnt << 23) | (t7Type << 24) | (t7Frac << 27));
}

void GSgfx_GCWriteArray(s32 attr, u32 base, u8 stride) {
    s32 idx = 1;
    if (attr != 0x19) idx = attr - 9;
    FIFO8 = 8;
    FIFO8 = 0xa0 + idx;
    FIFO32 = base & 0x3fffffff;
    FIFO8 = 8;
    FIFO8 = 0xb0 + idx;
    FIFO32 = stride;
}

void GSgfx_GCWriteVtxDesc(VtxDescEntry* list) {
    s32 nrm = 0, col = 0, tex = 0;
    u32 pmIdx = 0, tmIdx = 0, pos = 1, nrmType = 0, c0 = 0, c1 = 0;
    u32 t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, t7 = 0;
    s32 attr;
    for (; (attr = list->attr) != 0xff; list++) {
        switch (attr) {
        case 0: pmIdx = list->type; break;
        case 1: tmIdx = (tmIdx & ~1) | list->type; break;
        case 2: tmIdx = (tmIdx & ~2) | (list->type << 1); break;
        case 3: tmIdx = (tmIdx & ~4) | (list->type << 2); break;
        case 4: tmIdx = (tmIdx & ~8) | (list->type << 3); break;
        case 5: tmIdx = (tmIdx & ~0x10) | (list->type << 4); break;
        case 6: tmIdx = (tmIdx & ~0x20) | (list->type << 5); break;
        case 7: tmIdx = (tmIdx & ~0x40) | (list->type << 6); break;
        case 8: tmIdx = (tmIdx & ~0x80) | (list->type << 7); break;
        case 9: pos = list->type; break;
        case 10: {
            s32 t = list->type;
            if (t != 0) {
                nrmType = t;
                nrm = 1;
            }
            break;
        }
        case 25: {
            s32 t = list->type;
            if (t != 0) {
                nrmType = t;
                nrm = 2;
            }
            break;
        }
        case 11: c0 = list->type; col += (c0 != 0); break;
        case 12: c1 = list->type; col += (c1 != 0); break;
        case 13: t0 = list->type; tex += (t0 != 0); break;
        case 14: t1 = list->type; tex += (t1 != 0); break;
        case 15: t2 = list->type; tex += (t2 != 0); break;
        case 16: t3 = list->type; tex += (t3 != 0); break;
        case 17: t4 = list->type; tex += (t4 != 0); break;
        case 18: t5 = list->type; tex += (t5 != 0); break;
        case 19: t6 = list->type; tex += (t6 != 0); break;
        case 20: t7 = list->type; tex += (t7 != 0); break;
        }
    }
    FIFO8 = 8;
    FIFO8 = 0x50;
    FIFO32 = pmIdx | (tmIdx << 1) | (pos << 9) | (nrmType << 11) | (c0 << 13) | (c1 << 15);
    FIFO8 = 8;
    FIFO8 = 0x60;
    FIFO32 = t0 | (t1 << 2) | (t2 << 4) | (t3 << 6) | (t4 << 8) | (t5 << 10) | (t6 << 12) | (t7 << 14);
    FIFO8 = 0x10;
    FIFO16 = 0;
    FIFO16 = 0x1008;
    FIFO32 = col | (nrm << 2) | (tex << 4);
}

#define ST8(o) (*(u8*)((u8*)gsgfxState + (o)))
#define ST16(o) (*(u16*)((u8*)gsgfxState + (o)))
#define ST32(o) (*(u32*)((u8*)gsgfxState + (o)))
#define STF(o) (*(f32*)((u8*)gsgfxState + (o)))


// Copy the width/height of texture map `map` into the scale registers of coord `coord`.
static inline void UpdateCoordSize(u32 coord, u32 map) {
    gsgfxState->suS[coord].half = *(u16*)((u8*)&gsgfxState->texImg0[map & 7] + 2) & 0x3ff;
    gsgfxState->suT[coord].half = (*(u32*)&gsgfxState->texImg0[map & 7] >> 10) & 0x3ff;
}

// Write every dirty shadow register to the GX FIFO.
void GSgfx_GCFlushState(void) {
    int i, j;
    gsgfxState->r1ec.b22 = _gcGlobalRegState.b0;
    gsgfxState->r354.b0 = _gcGlobalRegState.b1;
    gsgfxState->peCtrl.pixfmt = _gcGlobalRegState.b2;
    gsgfxState->peCtrl.zfmt = _gcGlobalRegState.b3;
    gsgfxState->cmode1.f9 = _gcGlobalRegState.b4;
    {
        volatile GSState* st = gsgfxState;
        if (st->dirty & 0x1000) WrFifo(RAW(st->r354));
        if (st->d10 != 0) {
            for (s32 i = 0; i < 8; i++) {
                if (st->d10 & (1 << i)) {
                    s32 fmt = st->texImg0[i].b.fmt;
                    switch (fmt) {
                    case 8:
                    case 9:
                    case 10:
                        WrFifo(RAW(st->texTlut[i]));
                    }
                    WrFifo(RAW(st->texMode0[i]));
                    WrFifo(RAW(st->texMode1[i]));
                    WrFifo(RAW(st->texImg0[i]));
                    WrFifo(RAW(st->texImg1[i]));
                    WrFifo(RAW(st->texImg2[i]));
                    WrFifo(RAW(st->texImg3[i]));
                }
            }
            st->d10 = 0;
        }
    }
    {
        GSState* st = gsgfxState;
        if (st->d0c != 0) {
            for (i = 0, j = 0; i < st->genMode.nInd; i++, j += 8) {
                if (st->d0c & (1 << *(s32*)((u8*)gsgfxState + 0xb74 + j))) {
                    s32 coord = *(s32*)((u8*)gsgfxState + 0xb74 + j);
                    UpdateCoordSize(coord, *(u32*)((u8*)gsgfxState + 0xb78 + j));
                }
            }
            for (i = 0, j = 0; i < st->genMode.nTev + 1; i++, j += 12) {
                s32 coord = *(s32*)((u8*)gsgfxState + 0x4cc + j);
                if (coord != 0xff && (st->d0c & (1 << coord))) {
                    UpdateCoordSize(coord, *(u32*)((u8*)gsgfxState + 0x4d0 + j));
                }
            }
            for (i = 0; i < 8; i++) {
                if (st->d0c & (1 << i)) {
                    WrFifo(RAW(st->suS[i]));
                    WrFifo(RAW(st->suT[i]));
                }
            }
            st->d0c = 0;
        }
    }
    if (gsgfxState->d14 != 0) {
        WrFifo(RAW(gsgfxState->r350));
        for (i = 0; i < 8; i++) {
            if (gsgfxState->d14 & (1 << i)) {
                gsgfxState->tlutLoad0.a = gsgfxState->tlutCache[i].a;
                gsgfxState->tlutLoad1.b = gsgfxState->tlutCache[i].b;
                gsgfxState->tlutLoad1.c = gsgfxState->tlutCache[i].c;
                WrFifo(RAW(gsgfxState->tlutLoad0));
                WrFifo(RAW(gsgfxState->tlutLoad1));
                WrFifo(RAW(gsgfxState->r350));
            }
        }
        gsgfxState->dirty &= ~0x800;
        gsgfxState->d14 = 0;
    }
    {
        GSState* st = gsgfxState;
        if (st->dirty & 0x01) WrFifo(RAW(st->genMode));
        if (st->dirty & 0x02) WrFifo(RAW(st->zmode));
        if (st->dirty & 0x04) WrFifo(RAW(st->cmode0));
        if (st->dirty & 0x08) WrFifo(RAW(st->cmode1));
        if (st->dirty & 0x10) WrFifo(RAW(st->peCtrl));
        if (st->dirty & 0x20) {
            WrFifo(RAW(st->r48));
            WrFifo(RAW(st->r44));
        }
        if (st->dirty & 0x100) WrFifo(RAW(st->r1f8));
        if (st->dirty & 0x200) {
            WrFifo(RAW(st->r1fc));
            WrFifo(RAW(st->r200));
        }
        if (st->dirty & 0x400) WrFifo(RAW(st->r1ec));
        if (st->dTref != 0) {
            for (i = 0; i < 8; i++) {
                if (st->dTref & (1 << i)) WrFifo(RAW(st->tref[i]));
            }
            st->dTref = 0;
        }
    }
    {
        GSState* st = gsgfxState;
        if (st->dirty & 0x2000) WrFifo(RAW(st->iref));
        if (st->dIref != 0) {
            if (st->dIref & (1 << 0)) WrFifo(RAW(st->ras1ss0));
            if (st->dIref & (1 << 1)) WrFifo(RAW(st->ras1ss1));
            st->dIref = 0;
        }
    }
    {
        GSState* st = gsgfxState;
        if (st->dTevc != 0) {
            for (i = 0; i < 16; i++) {
                if (st->dTevc & (1 << i)) WrFifo(RAW(st->tevc[i]));
            }
            st->dTevc = 0;
        }
    }
    {
        GSState* st = gsgfxState;
        if (st->dTeva != 0) {
            for (i = 0; i < 16; i++) {
                if (st->dTeva & (1 << i)) WrFifo(RAW(st->teva[i]));
            }
            st->dTeva = 0;
        }
    }
    {
        GSState* st = gsgfxState;
        if (st->dKcolA != 0) {
            for (i = 0; i < 8; i++) {
                if (st->dKcolA & (1 << i)) {
                    WrFifo(RAW(st->kcolA0[i]));
                    WrFifo(RAW(st->kcolA1[i]));
                    WrFifo(RAW(st->kcolA1[i]));
                    WrFifo(RAW(st->kcolA1[i]));
                }
            }
            st->dKcolA = 0;
        }
    }
    {
        GSState* st = gsgfxState;
        if (st->dKcolB != 0) {
            for (i = 0; i < 4; i++) {
                if (st->dKcolB & (1 << i)) {
                    WrFifo(RAW(st->kcolB0[i]));
                    WrFifo(RAW(st->kcolB1[i]));
                }
            }
            st->dKcolB = 0;
        }
    }
    {
        GSState* st = gsgfxState;
        if (st->dKsel != 0) {
            for (i = 0; i < 8; i++) {
                if (st->dKsel & (1 << i)) WrFifo(RAW(st->ksel[i]));
            }
            st->dKsel = 0;
        }
    }
    {
        GSState* st = gsgfxState;
        if (st->indDirty != 0) {
            for (i = 0; i < 16; i++) {
                if (st->indDirty & (1 << i)) WrFifo(RAW(st->indCmd[i]));
            }
            st->indDirty = 0;
        }
    }
    {
        GSState* st = gsgfxState;
        if (st->dirty & 0x8000) {
            WrFifo(RAW(st->fog0));
            WrFifo(RAW(st->fog1));
            WrFifo(RAW(st->fog2));
        }
        if (st->dirty & 0x10000) WrFifo(RAW(st->fog3));
        if (st->dirty & 0x20000) WrFifo(RAW(st->r2f4));
        if (st->dirty & 0x80000) {
            for (i = 0; i < 5; i++) WrFifo(RAW(st->rangeAdj[i]));
        }
        if (st->dirty & 0x40000) WrFifo(RAW(st->r2f8));
        if (st->dirty & 0x4000) {
            WrFifo(RAW(st->scis0));
            WrFifo(RAW(st->scis1));
        }
        if (st->dirty & 0x800) WrFifo(RAW(st->r350));
        if (st->dirty & 0x1000000) {
            FIFO8 = 0x10;
            FIFO16 = 0x1009;
            FIFO16 = 0;
            FIFO32 = st->genMode.nChan;
        }
        if (st->dirty & 0x2000000) {
            FIFO8 = 0x10;
            FIFO16 = 0;
            FIFO16 = 0x103f;
            FIFO32 = st->genMode.nTex;
        }
        if (st->dirty & 0x4000000) {
            FIFO16 = 0;
            FIFO8 = 0x10;
            FIFO16 = 0x1005;
            FIFO32 = st->xf1005;
        }
        if (st->dirty & 0xc0) {
            if (st->dirty & 0x40) {
                FIFO8 = 8;
                FIFO8 = 0x30;
                FIFO32 = RAW(st->matIdxA);
            }
            if (st->dirty & 0x80) {
                FIFO8 = 8;
                FIFO8 = 0x40;
                FIFO32 = RAW(st->matIdxB);
            }
            if ((st->dirty & 0xc0) == 0xc0) {
                FIFO16 = 1;
                FIFO8 = 0x10;
                FIFO16 = 0x1018;
                FIFO32 = RAW(st->matIdxA);
                FIFO32 = RAW(st->matIdxB);
            } else if (st->dirty & 0x40) {
                FIFO8 = 0x10;
                FIFO16 = 0;
                FIFO16 = 0x1018;
                FIFO32 = RAW(st->matIdxA);
            } else {
                FIFO8 = 0x10;
                FIFO16 = 0;
                FIFO16 = 0x1019;
                FIFO32 = RAW(st->matIdxB);
            }
        }
    }
    gsgfxState->dirty = 0;
}

// Mark every cached hardware-state value as unknown (0xFE fill) so the next set always writes.
void GSgfx_GCInvalidateState(void) {
    int i;
    for (i = 0; i < 8; i++) {
        gsgfxState->texGen[i].func = 0xFEFEFEFE;
        gsgfxState->texGen[i].src = 0xFEFEFEFE;
        gsgfxState->texGen[i].mtx = 0xFEFEFEFE;
        gsgfxState->texGen[i].norm = 0xFE;
        gsgfxState->texGen[i].post = 0xFEFEFEFE;
    }
    gsgfxState->c3f8 = 0xFE;
    gsgfxState->sizeW0 = 0;
    gsgfxState->sizeOff0 = 0xFEFEFEFE;
    gsgfxState->sizeW1 = 0;
    gsgfxState->sizeOff1 = 0xFEFEFEFE;
    for (i = 0; i < 16; i++) gsgfxState->coordScale[i] = 0xFE;
    gsgfxState->c41c = 0xFEFEFEFE;
    gsgfxState->c438 = 0xFE;
    gsgfxState->c43c = 0xFEFEFEFE;
    gsgfxState->c440 = 0xFEFEFEFE;
    gsgfxState->scis[0] = 0xFEFE;
    gsgfxState->scis[1] = 0xFEFE;
    gsgfxState->scis[2] = 0xFEFE;
    gsgfxState->scis[3] = 0xFEFE;
    gsgfxState->scisOff[0] = 0xFEFEFEFE;
    gsgfxState->scisOff[1] = 0xFEFEFEFE;
    gsgfxState->vp[0] = -1.0f;
    gsgfxState->vp[1] = -1.0f;
    gsgfxState->vp[2] = -1.0f;
    gsgfxState->vp[3] = -1.0f;
    gsgfxState->vp[4] = 0.0f;
    gsgfxState->vp[5] = 1.0f;
    gsgfxState->cC3C = 0xFEFEFEFE;
    gsgfxState->c454 = 0xFE;
    for (i = 0; i < 4; i++) {
        gsgfxState->chan[i].a = 0xFE;
        gsgfxState->chan[i].w[0] = 0xFEFEFEFE;
        gsgfxState->chan[i].w[1] = 0xFEFEFEFE;
        gsgfxState->chan[i].w[2] = 0xFEFEFEFE;
        gsgfxState->chan[i].w[3] = 0xFEFEFEFE;
        gsgfxState->chan[i].w[4] = 0xFEFEFEFE;
    }
    for (i = 0; i < 4; i++) gsgfxState->ambMat[i][0] = 1;
    for (i = 0; i < 16; i++) {
        gsgfxState->tevOrder[i].a = 0xFEFEFEFE;
        gsgfxState->tevOrder[i].b = 0xFEFEFEFE;
        gsgfxState->tevOrder[i].c = 0xFEFEFEFE;
    }
    gsgfxState->c58c[0] = 0xFE;
    gsgfxState->c58c[1] = 0xFE;
    for (i = 0; i < 16; i++) {
        gsgfxState->colorIn[i].a = 0xFEFEFEFE;
        gsgfxState->colorIn[i].b = 0xFEFEFEFE;
        gsgfxState->colorIn[i].c = 0xFEFEFEFE;
        gsgfxState->colorIn[i].d = 0xFEFEFEFE;
    }
    for (i = 0; i < 16; i++) {
        gsgfxState->alphaIn[i].a = 0xFEFEFEFE;
        gsgfxState->alphaIn[i].b = 0xFEFEFEFE;
        gsgfxState->alphaIn[i].c = 0xFEFEFEFE;
        gsgfxState->alphaIn[i].d = 0xFEFEFEFE;
    }
    for (i = 0; i < 16; i++) {
        gsgfxState->colorOp[i].op = 0xFEFEFEFE;
        gsgfxState->colorOp[i].bias = 0xFEFEFEFE;
        gsgfxState->colorOp[i].scale = 0xFEFEFEFE;
        gsgfxState->colorOp[i].clamp = 0xFE;
        gsgfxState->colorOp[i].reg = 0xFEFEFEFE;
    }
    for (i = 0; i < 16; i++) {
        gsgfxState->alphaOp[i].op = 0xFEFEFEFE;
        gsgfxState->alphaOp[i].bias = 0xFEFEFEFE;
        gsgfxState->alphaOp[i].scale = 0xFEFEFEFE;
        gsgfxState->alphaOp[i].clamp = 0xFE;
        gsgfxState->alphaOp[i].reg = 0xFEFEFEFE;
    }
    for (i = 0; i < 4; i++) gsgfxState->kcolFlag[i][0] = 1;
    for (i = 0; i < 16; i++) gsgfxState->indStatus[i] = 0xFE;
    for (i = 0; i < 80; i++) gsgfxState->cA24[i] = 0xFEFEFEFE;
    for (i = 0; i < 20; i++) gsgfxState->cB74[i] = 0xFEFEFEFE;
    gsgfxState->cBC4[0] = 0xFE;
    gsgfxState->cBC4[1] = 0xFE;
    for (i = 0; i < 3; i++) gsgfxState->cBC8[i] = 0xFEFEFEFE;
    gsgfxState->cBD4[0] = 0xFE;
    gsgfxState->cBD4[1] = 0xFE;
    for (i = 0; i < 3; i++) gsgfxState->cBD8[i] = 0xFEFEFEFE;
    gsgfxState->cBE4 = 0xFE;
    gsgfxState->cBE8 = 0xFEFEFEFE;
    gsgfxState->cBEC = 0xFE;
    gsgfxState->c_bf0 = 0xFE;
    gsgfxState->cBF1[0] = 0xFE;
    gsgfxState->cBF1[1] = 0xFE;
    gsgfxState->cBF1[2] = 0xFE;
    gsgfxState->c_fogType = 0xFEFEFEFE;
    gsgfxState->c_fogStart = (f32)0xFEFEFEFEu;
    gsgfxState->c_fogEnd = (f32)0xFEFEFEFEu;
    gsgfxState->c_fogNear = (f32)0xFEFEFEFEu;
    gsgfxState->c_fogFar = (f32)0xFEFEFEFEu;
    gsgfxState->cC08 = 1;
    gsgfxState->cC0E = 0xFEFE;
    gsgfxState->cC0D = 0xFE;
}


static inline void GSgfx_GCWriteCullMode(s32 mode) {
    static const u8 cm2hw[4] = {0, 2, 1, 3};
    gsgfxState->c43c = mode;
    gsgfxState->genMode.cull = cm2hw[mode];
    gsgfxState->dirty |= 1;
    gsgfxState->c43c = mode;
}

// Resets the GX state to its defaults (GXInit-like). Sections reconstructed so far: texgen defaults, tex-gen count,
// line width / point size, texcoord scale, coplanar / cull / clip mode, channel count.
// TODO: scissor + viewport, channel controls and colors, TEV order / stages / swap tables / konsts, indirect setup,
// fog, blend/alpha/z-mode (large inlined GCWrite* helpers; see the asm).
void GSgfx_GCReset() {
    s32 unksp11;
    s32 unksp12;
    s32 unksp13;
    s32 unksp15;
    s32 unksp16;
    s32 unksp17;
    s32 unksp19;
    s32 unksp1A;
    s32 unksp1B;
    s32 unkspD;
    s32 unkspE;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    u16 spA;
    u16 sp8;
    f32 temp_f10;
    f32 temp_f11;
    f32 temp_f12;
    f32 temp_f1;
    f32 temp_f5;
    f32 temp_f6;
    f32 temp_f7;
    f32 temp_f9;
    f32 var_f8;
    s16 temp_r17;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_6;
    s32 temp_r0_7;
    s32 temp_r0_8;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r10_3;
    s32 temp_r10_4;
    s32 temp_r10_5;
    s32 temp_r10_6;
    s32 temp_r10_7;
    s32 temp_r10_8;
    s32 temp_r10_9;
    s32 temp_r11;
    s32 temp_r11_10;
    s32 temp_r11_2;
    s32 temp_r11_3;
    s32 temp_r11_4;
    s32 temp_r11_5;
    s32 temp_r11_6;
    s32 temp_r11_7;
    s32 temp_r11_8;
    s32 temp_r11_9;
    s32 temp_r12;
    s32 temp_r12_2;
    s32 temp_r12_3;
    s32 temp_r12_4;
    s32 temp_r12_5;
    s32 temp_r12_6;
    s32 temp_r12_7;
    s32 temp_r12_8;
    s32 temp_r12_9;
    s32 temp_r16;
    s32 temp_r16_2;
    s32 temp_r17_2;
    s32 temp_r17_3;
    s32 temp_r17_4;
    s32 temp_r18;
    s32 temp_r18_2;
    s32 temp_r19;
    s32 temp_r19_2;
    s32 temp_r19_3;
    s32 temp_r19_4;
    s32 temp_r20;
    s32 temp_r20_2;
    s32 temp_r20_3;
    s32 temp_r21;
    s32 temp_r22;
    s32 temp_r22_2;
    s32 temp_r22_3;
    s32 temp_r23;
    s32 temp_r23_2;
    s32 temp_r24;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r7;
    s32 temp_r7_2;
    s32 temp_r7_3;
    s32 temp_r7_4;
    s32 temp_r7_5;
    s32 temp_r7_6;
    s32 temp_r7_7;
    s32 temp_r8_10;
    s32 temp_r8_11;
    s32 temp_r8_12;
    s32 temp_r8_13;
    s32 temp_r8_14;
    s32 temp_r8_3;
    s32 temp_r8_4;
    s32 temp_r8_5;
    s32 temp_r8_6;
    s32 temp_r8_7;
    s32 temp_r8_8;
    s32 temp_r8_9;
    s32 temp_r9_2;
    s32 temp_r9_3;
    s32 temp_r9_4;
    s32 temp_r9_5;
    s32 temp_r9_6;
    s32 temp_r9_7;
    s32 var_ctr;
    s32 var_ctr_10;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_ctr_5;
    s32 var_ctr_6;
    s32 var_ctr_7;
    s32 var_ctr_8;
    s32 var_ctr_9;
    s32 var_r10;
    s32 var_r10_2;
    s32 var_r17;
    s32 var_r18;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_4;
    s32 var_r4_5;
    s32 var_r4_6;
    s32 var_r5;
    s32 var_r5_2;
    s32 var_r5_3;
    s32 var_r5_4;
    s32 var_r5_5;
    s32 var_r6;
    s32 var_r6_2;
    s32 var_r6_3;
    s32 var_r6_4;
    s32 var_r6_5;
    s32 var_r6_6;
    s32 var_r7;
    s32 var_r7_2;
    s32 var_r7_3;
    s32 var_r7_4;
    s32 var_r8_2;
    s32 var_r8_3;
    s32 var_r8_4;
    s32 var_r9;
    s32 var_r9_2;
    s32 var_r9_3;
    s8 temp_r9_8;
    u16 temp_r8;
    u16 temp_r9;
    u32 temp_r8_2;
    u8 var_r8;

    var_r18 = 0;
    var_r17 = 0;
    sp20 = jtbl_1414;
    sp1C = jtbl_1415;
    do {
        temp_r5 = var_r18 + 4;
        *((u8*)(gsgfxState) + (var_r17 + 0x358)) = 1;
        *((u8*)(gsgfxState) + (var_r17 + 0x35C)) = temp_r5;
        *((u8*)(gsgfxState) + (var_r17 + 0x360)) = 0x3C;
        *((u8*)(gsgfxState) + (var_r17 + 0x364)) = 0;
        *((u8*)(gsgfxState) + (var_r17 + 0x368)) = 0x7D;
        GSgfx_GCWriteTexCoordGen((unsigned long)(var_r18), (long)(1), (long)(temp_r5), (unsigned long)(0x3C), (unsigned char)(0), (unsigned long)(0x7D));
        var_r18 += 1;
        var_r17 += 0x14;
    } while (var_r18 < 8);
    M2C_FIELD(gsgfxState, s8 *, 0x3F8) = 1;
    M2C_FIELD(gsgfxState, u8 *, 0x33) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x33) & ~0xF) | 1);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x02000000 | 1);
    M2C_FIELD(gsgfxState, s8 *, 0x3F8) = 1;
    M2C_FIELD(gsgfxState, s8 *, 0x3FC) = 6;
    M2C_FIELD(gsgfxState, s32 *, 0x400) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x1EF) = 6;
    M2C_FIELD(gsgfxState, u8 *, 0x1ED) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1ED) & ~7);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x400);
    M2C_FIELD(gsgfxState, s8 *, 0x3FC) = 6;
    M2C_FIELD(gsgfxState, s32 *, 0x400) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x404) = 6;
    M2C_FIELD(gsgfxState, s32 *, 0x408) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x1EE) = 6;
    M2C_FIELD(gsgfxState, u8 *, 0x1ED) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1ED) & ~0x38);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x400);
    M2C_FIELD(gsgfxState, s8 *, 0x404) = 6;
    M2C_FIELD(gsgfxState, s32 *, 0x408) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x40C) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x40D) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x1AD) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1AD) & ~4);
    M2C_FIELD(gsgfxState, u8 *, 0x1AD) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1AD) & ~8);
    M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | 1);
    M2C_FIELD(gsgfxState, s8 *, 0x40C) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x40D) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x40E) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x40F) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x1B1) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1B1) & ~4);
    M2C_FIELD(gsgfxState, u8 *, 0x1B1) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1B1) & ~8);
    M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | 2);
    M2C_FIELD(gsgfxState, s8 *, 0x40E) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x40F) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x410) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x411) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x1B5) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1B5) & ~4);
    M2C_FIELD(gsgfxState, u8 *, 0x1B5) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1B5) & ~8);
    M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | 4);
    M2C_FIELD(gsgfxState, s8 *, 0x410) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x411) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x412) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x413) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x1B9) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1B9) & ~4);
    M2C_FIELD(gsgfxState, u8 *, 0x1B9) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1B9) & ~8);
    M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | 8);
    M2C_FIELD(gsgfxState, s8 *, 0x412) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x413) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x414) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x415) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x1BD) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1BD) & ~4);
    M2C_FIELD(gsgfxState, u8 *, 0x1BD) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1BD) & ~8);
    M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | 0x10);
    M2C_FIELD(gsgfxState, s8 *, 0x414) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x415) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x416) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x417) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x1C1) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1C1) & ~4);
    M2C_FIELD(gsgfxState, u8 *, 0x1C1) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1C1) & ~8);
    M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | 0x20);
    M2C_FIELD(gsgfxState, s8 *, 0x416) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x417) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x418) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x419) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x1C5) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1C5) & ~4);
    M2C_FIELD(gsgfxState, u8 *, 0x1C5) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1C5) & ~8);
    M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | 0x40);
    M2C_FIELD(gsgfxState, s8 *, 0x418) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x419) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x41A) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x41B) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x1C9) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1C9) & ~4);
    M2C_FIELD(gsgfxState, u8 *, 0x1C9) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1C9) & ~8);
    M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | 0x80);
    M2C_FIELD(gsgfxState, s8 *, 0x41A) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x41B) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x438) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x31) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x31) & ~8);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 1);
    M2C_FIELD(gsgfxState, s8 *, 0x438) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0x43C) = 2;
    M2C_FIELD(gsgfxState, u8 *, 0x32) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x32) & ~0xC0) | ((M2C_FIELD(&cm2hw_localstatic3_GSgfx_GCWriteCullMode, u8 *, 2) << 6) & 0xC0));
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 1);
    M2C_FIELD(gsgfxState, s32 *, 0x43C) = 2;
    M2C_FIELD(gsgfxState, s32 *, 0x440) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0x54) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x04000000);
    M2C_FIELD(gsgfxState, s32 *, 0x440) = 0;
    M2C_FIELD(gsgfxState, s16 *, 0x444) = 0;
    M2C_FIELD(gsgfxState, s16 *, 0x446) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0x44C) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0x450) = 0;
    GSgfxVideoGetEFBSize((u16*)(((u8*)(gsgfxState) + 0x448)), (u16*)(((u8*)(gsgfxState) + 0x44A)));
    temp_r9 = M2C_FIELD(gsgfxState, u16 *, 0x44A);
    temp_r8 = M2C_FIELD(gsgfxState, u16 *, 0x448);
    M2C_FIELD(gsgfxState, u32 *, 0x4C) = (u32) ((M2C_FIELD(gsgfxState, u32 *, 0x4C) & ~0xFFF000) | 0x156000);
    M2C_FIELD(gsgfxState, u16 *, 0x4E) = (u16) ((M2C_FIELD(gsgfxState, u16 *, 0x4E) & ~0xFFF) | 0x156);
    M2C_FIELD(gsgfxState, s32 *, 0x50) = (s32) ((M2C_FIELD(gsgfxState, s32 *, 0x50) & ~0xFFF000) | ((((((u32) M2C_FIELD(gsgfxState, u32 *, 0x4C) >> 0xCU) & 0xFFF) + (temp_r8 - 1)) << 0xC) & 0xFFF000));
    M2C_FIELD(gsgfxState, u16 *, 0x52) = (u16) ((M2C_FIELD(gsgfxState, u16 *, 0x52) & ~0xFFF) | (((M2C_FIELD(gsgfxState, u16 *, 0x4E) & 0xFFF) + (temp_r9 - 1)) & 0xFFF));
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x4000);
    M2C_FIELD(gsgfxState, s16 *, 0x444) = 0;
    M2C_FIELD(gsgfxState, s16 *, 0x446) = 0;
    M2C_FIELD(gsgfxState, u16 *, 0x448) = temp_r8;
    M2C_FIELD(gsgfxState, u16 *, 0x44A) = temp_r9;
    M2C_FIELD(gsgfxState, s32 *, 0x44C) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0x450) = 0;
    M2C_FIELD(gsgfxState, f32 *, 0xC24) = 0.0f;
    M2C_FIELD(gsgfxState, f32 *, 0xC28) = 0.0f;
    spA = M2C_FIELD(gsgfxState, u16 *, 0x448);
    M2C_FIELD(gsgfxState, f32 *, 0xC2C) = (f32) M2C_ERROR(/* psq_l unimplemented */);
    sp8 = M2C_FIELD(gsgfxState, u16 *, 0x44A);
    M2C_FIELD(gsgfxState, f32 *, 0xC30) = (f32) M2C_ERROR(/* psq_l unimplemented */);
    M2C_FIELD(gsgfxState, f32 *, 0xC34) = 0.0f;
    M2C_FIELD(gsgfxState, f32 *, 0xC38) = 1.0f;
    M2C_FIELD(gsgfxState, u32 *, 0xC3C) = 1U;
    temp_r8_2 = M2C_FIELD(gsgfxState, u32 *, 0xC3C);
    temp_f12 = M2C_FIELD(gsgfxState, f32 *, 0xC38);
    temp_f11 = M2C_FIELD(gsgfxState, f32 *, 0xC34);
    temp_f10 = M2C_FIELD(gsgfxState, f32 *, 0xC30);
    temp_f9 = M2C_FIELD(gsgfxState, f32 *, 0xC2C);
    var_f8 = M2C_FIELD(gsgfxState, f32 *, 0xC28);
    temp_f7 = M2C_FIELD(gsgfxState, f32 *, 0xC24);
    if (temp_r8_2 == 0U) {
        var_f8 -= 0.5f;
    }
    var_r6 = 0;
    *(s8 *)0xCC008000 = 0x10;
    temp_f1 = temp_f10 / 2.0f;
    temp_f6 = temp_f9 * 0.5f;
    *(s8 *)0xCC008000 = 5;
    temp_f5 = temp_f12 * 1.6777216e7f;
    *(s8 *)0xCC008000 = 0x101A;
    *(s8 *)0xCC008000 = temp_f6;
    *(s8 *)0xCC008000 = (f32) -temp_f1;
    var_r7 = 0;
    *(s8 *)0xCC008000 = (f32) -((temp_f11 * 1.6777216e7f) - temp_f5);
    var_r4 = 0;
    *(s8 *)0xCC008000 = (f32) (342.0f + (temp_f7 + temp_f6));
    *(s8 *)0xCC008000 = (f32) (342.0f + (var_f8 + temp_f1));
    *(s8 *)0xCC008000 = (f32) (temp_f5 + 0.0f);
    M2C_FIELD(gsgfxState, f32 *, 0xC24) = temp_f7;
    M2C_FIELD(gsgfxState, f32 *, 0xC28) = var_f8;
    M2C_FIELD(gsgfxState, f32 *, 0xC2C) = temp_f9;
    M2C_FIELD(gsgfxState, f32 *, 0xC30) = temp_f10;
    M2C_FIELD(gsgfxState, f32 *, 0xC34) = temp_f11;
    M2C_FIELD(gsgfxState, f32 *, 0xC38) = temp_f12;
    M2C_FIELD(gsgfxState, u32 *, 0xC3C) = temp_r8_2;
    M2C_FIELD(gsgfxState, s8 *, 0x454) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x33) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x33) & ~0x30);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x01000000 | 1);
    M2C_FIELD(gsgfxState, s8 *, 0x454) = 0;
    var_ctr = 4;
    do {
        var_r5 = 0;
        *((u8*)(gsgfxState) + (var_r4 + 0x458)) = 0;
        temp_r17 = (var_r6 & 3) + 0x100E;
        temp_r22 = var_r4 + 0x464;
        temp_r20 = var_r4 + 0x468;
        *((u8*)(gsgfxState) + (var_r4 + 0x45C)) = 0;
        temp_r19 = var_r4 + 0x46C;
        temp_r12 = var_r7 + 0x458;
        temp_r11 = var_r7 + 0x45C;
        *((u8*)(gsgfxState) + (var_r4 + 0x460)) = 1;
        temp_r10 = var_r7 + 0x460;
        temp_r9_2 = var_r7 + 0x464;
        temp_r8_3 = var_r7 + 0x468;
        temp_r0 = var_r7 + 0x46C;
        var_r4 += 0x18;
        var_r6 += 1;
        *((u8 *)gsgfxState + temp_r22) = 0;
        var_r7 += 0x18;
        *((u8 *)gsgfxState + temp_r20) = 0;
        *((u8 *)gsgfxState + temp_r19) = 2;
        *(s8 *)0xCC008000 = 0x10;
        *(s8 *)0xCC008000 = 0;
        *(s8 *)0xCC008000 = temp_r17;
        *(s8 *)0xCC008000 = 0x401;
        *((u8 *)gsgfxState + temp_r12) = 0;
        *((u8 *)gsgfxState + temp_r11) = 0;
        *((u8 *)gsgfxState + temp_r10) = 1;
        *((u8 *)gsgfxState + temp_r9_2) = 0;
        *((u8 *)gsgfxState + temp_r8_3) = 0;
        *((u8 *)gsgfxState + temp_r0) = 2;
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_r10 = 0;
    var_ctr_2 = 4;
    do {
        temp_r4 = var_r5 + 4;
        sp18 = sp20;
        *((u8*)((u16)gsgfxState) + (var_r10 + 0x4B9)) = sp20;
        temp_r11_2 = (temp_r4 - 4) * 5;
        *(u8 *)0xCC008000 = 0x10;
        var_r3 = 0;
        *(u8 *)0xCC008000 = 0;
        *(u8 *)0xCC008000 = (s16) ((temp_r4 & 1) + 0x100A);
        *(u8 *)0xCC008000 = (s32) (unksp1B | (((((unksp19 << 0x10) & ~0xFF000000) | ((u8) sp18 << 0x18)) & ~0xFF00) | ((unksp1A << 8) & 0xFF00)));
        var_r10 += 5;
        var_r5 += 1;
        *((u8*)(gsgfxState) + (temp_r11_2 + 0x4B9)) = sp20;
        *((u8*)(gsgfxState) + (temp_r11_2 + 0x4B8)) = 0;
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    var_r10_2 = 0;
    var_ctr_3 = 4;
    do {
        temp_r5_2 = var_r3 + 4;
        sp14 = sp1C;
        *((u8*)(gsgfxState) + (var_r10_2 + 0x4C3)) = sp1C;
        temp_r11_3 = (temp_r5_2 - 4) * 5;
        *(u8 *)0xCC008000 = 0x10;
        var_r5_2 = 0;
        *(u8 *)0xCC008000 = 0;
        *(u8 *)0xCC008000 = (s16) ((temp_r5_2 & 1) + 0x100C);
        *(u8 *)0xCC008000 = (s32) (unksp17 | (((((unksp15 << 0x10) & ~0xFF000000) | ((u8) sp14 << 0x18)) & ~0xFF00) | ((unksp16 << 8) & 0xFF00)));
        var_r10_2 += 5;
        var_r3 += 1;
        *((u8*)(gsgfxState) + (temp_r11_3 + 0x4C3)) = sp1C;
        *((u8*)(gsgfxState) + (temp_r11_3 + 0x4C2)) = 0;
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    var_r4_2 = 0;
    var_r6_2 = 0;
    var_ctr_4 = 0x10;
    do {
        if (var_r5_2 < 8) {
            *((u8*)(gsgfxState) + (var_r4_2 + 0x4CC)) = var_r5_2;
            temp_r0_2 = var_r5_2 >> 1;
            *((u8*)(gsgfxState) + (var_r4_2 + 0x4D0)) = var_r5_2;
            *((u8*)(gsgfxState) + (var_r4_2 + 0x4D4)) = 4;
            if (var_r5_2 & 1) {
                temp_r12_2 = temp_r0_2 * 4;
                temp_r9_3 = temp_r12_2 + 0x5A;
                temp_r8_4 = temp_r12_2 + 0x58;
                *((u8 *)gsgfxState + temp_r9_3) = (*((u8 *)gsgfxState + temp_r9_3) & ~0x70) | ((var_r5_2 << 4) & 0x70);
                var_r9 = 0;
                *((u8 *)gsgfxState + temp_r8_4) = (*((u8 *)gsgfxState + temp_r8_4) & ~0x38000) | ((var_r5_2 << 0xF) & 0x38000);
                if ((var_r5_2 != 0xFF) && !(var_r5_2 & 0x100)) {
                    var_r9 = 1;
                }
                temp_r10_2 = temp_r12_2 + 0x59;
                *((u8 *)gsgfxState + temp_r10_2) = (*((u8 *)gsgfxState + temp_r10_2) & ~4) | ((var_r9 << 2) & 4);
                *((u8 *)gsgfxState + temp_r10_2) = (*((u8 *)gsgfxState + temp_r10_2) & ~0x38) | ((M2C_FIELD(&c2r_localstatic3_GSgfx_GCWriteTevOrder, u8 *, 4) << 3) & 0x38);
            } else {
                temp_r12_3 = temp_r0_2 * 4;
                temp_r10_3 = temp_r12_3 + 0x5B;
                var_r8 = 0;
                *((u8 *)gsgfxState + temp_r10_3) = (*((u8 *)gsgfxState + temp_r10_3) & ~7) | (var_r5_2 & 7);
                *((u8 *)gsgfxState + temp_r10_3) = (*((u8 *)gsgfxState + temp_r10_3) & ~0x38) | ((var_r5_2 << 3) & 0x38);
                if ((var_r5_2 != 0xFF) && !(var_r5_2 & 0x100)) {
                    var_r8 = 1;
                }
                temp_r9_4 = temp_r12_3 + 0x5B;
                temp_r8_5 = temp_r12_3 + 0x5A;
                *((u8 *)gsgfxState + temp_r9_4) = (*((u8 *)gsgfxState + temp_r9_4) & ~0x40) | ((var_r8 << 6) & 0x40);
                *((u8 *)gsgfxState + temp_r8_5) = (*((u8 *)gsgfxState + temp_r8_5) & ~0x380) | ((M2C_FIELD(&c2r_localstatic3_GSgfx_GCWriteTevOrder, u8 *, 4) << 7) & 0x380);
            }
            M2C_FIELD(gsgfxState, s32 *, 4) = (s32) (M2C_FIELD(gsgfxState, s32 *, 4) | (1 << temp_r0_2));
            if (var_r5_2 != 0xFF) {
                M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | (1 << var_r5_2));
            }
            *((u8*)(gsgfxState) + (var_r6_2 + 0x4CC)) = var_r5_2;
            *((u8*)(gsgfxState) + (var_r6_2 + 0x4D0)) = var_r5_2;
            *((u8*)(gsgfxState) + (var_r6_2 + 0x4D4)) = 4;
        } else {
            *((u8*)(gsgfxState) + (var_r4_2 + 0x4CC)) = 0xFF;
            temp_r0_3 = var_r5_2 >> 1;
            *((u8*)(gsgfxState) + (var_r4_2 + 0x4D0)) = 0xFF;
            *((u8*)(gsgfxState) + (var_r4_2 + 0x4D4)) = 0xFF;
            if (var_r5_2 & 1) {
                temp_r10_4 = temp_r0_3 * 4;
                temp_r9_5 = temp_r10_4 + 0x5A;
                temp_r8_6 = temp_r10_4 + 0x58;
                temp_r10_5 = temp_r10_4 + 0x59;
                *((u8 *)gsgfxState + temp_r9_5) = *((u8 *)gsgfxState + temp_r9_5) | 0x70;
                *((u8 *)gsgfxState + temp_r8_6) = *((u8 *)gsgfxState + temp_r8_6) | 0x38000;
                *((u8 *)gsgfxState + temp_r10_5) = *((u8 *)gsgfxState + temp_r10_5) & ~4;
                *((u8 *)gsgfxState + temp_r10_5) = (*((u8 *)gsgfxState + temp_r10_5) & ~0x38) | ((M2C_FIELD(&c2r_localstatic3_GSgfx_GCWriteTevOrder, u8 *, 0xF) << 3) & 0x38);
            } else {
                temp_r8_7 = temp_r0_3 * 4;
                temp_r11_4 = temp_r8_7 + 0x5B;
                temp_r8_8 = temp_r8_7 + 0x5A;
                *((u8 *)gsgfxState + temp_r11_4) = *((u8 *)gsgfxState + temp_r11_4) | 7;
                *((u8 *)gsgfxState + temp_r11_4) = *((u8 *)gsgfxState + temp_r11_4) | 0x38;
                *((u8 *)gsgfxState + temp_r11_4) = *((u8 *)gsgfxState + temp_r11_4) & ~0x40;
                *((u8 *)gsgfxState + temp_r8_8) = (*((u8 *)gsgfxState + temp_r8_8) & ~0x380) | ((M2C_FIELD(&c2r_localstatic3_GSgfx_GCWriteTevOrder, u8 *, 0xF) << 7) & 0x380);
            }
            M2C_FIELD(gsgfxState, s32 *, 4) = (s32) (M2C_FIELD(gsgfxState, s32 *, 4) | (1 << temp_r0_3));
            *((u8*)(gsgfxState) + (var_r6_2 + 0x4CC)) = 0xFF;
            *((u8*)(gsgfxState) + (var_r6_2 + 0x4D0)) = 0xFF;
            *((u8*)(gsgfxState) + (var_r6_2 + 0x4D4)) = 0xFF;
        }
        var_r4_2 += 0xC;
        var_r5_2 += 1;
        var_r6_2 += 0xC;
        var_ctr_4 -= 1;
    } while (var_ctr_4 != 0);
    var_r6_3 = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x58C) = 1;
    var_r3_2 = 0;
    var_r4_3 = 0;
    var_r7_2 = 0;
    var_r8_2 = 0;
    var_r9_2 = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x32) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x32) & ~0x3C);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 1);
    M2C_FIELD(gsgfxState, s8 *, 0x58C) = 1;
    var_ctr_5 = 0x10;
    do {
        *((u8*)(gsgfxState) + (var_r3_2 + 0x590)) = 0xF;
        temp_r31 = var_r9_2 + 0x226;
        *((u8*)(gsgfxState) + (var_r3_2 + 0x594)) = 0xA;
        temp_r30 = var_r9_2 + 0x227;
        temp_r18 = 1 << var_r6_3;
        *((u8*)(gsgfxState) + (var_r3_2 + 0x598)) = 8;
        *((u8*)(gsgfxState) + (var_r3_2 + 0x59C)) = 0xF;
        temp_r11_5 = var_r9_2 + 0x266;
        *((u8 *)gsgfxState + temp_r31) = *((u8 *)gsgfxState + temp_r31) | 0xF0;
        *((u8 *)gsgfxState + temp_r31) = (*((u8 *)gsgfxState + temp_r31) & ~0xF) | 0xA;
        *((u8 *)gsgfxState + temp_r30) = (*((u8 *)gsgfxState + temp_r30) & ~0xF0) | 0x80;
        *((u8 *)gsgfxState + temp_r30) = *((u8 *)gsgfxState + temp_r30) | 0xF;
        M2C_FIELD(gsgfxState, s32 *, 0x1C) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x1C) | temp_r18);
        *((u8*)(gsgfxState) + (var_r8_2 + 0x590)) = 0xF;
        *((u8*)(gsgfxState) + (var_r8_2 + 0x594)) = 0xA;
        *((u8*)(gsgfxState) + (var_r8_2 + 0x598)) = 8;
        *((u8*)(gsgfxState) + (var_r8_2 + 0x59C)) = 0xF;
        *((u8*)(gsgfxState) + (var_r3_2 + 0x690)) = 7;
        *((u8*)(gsgfxState) + (var_r3_2 + 0x694)) = 5;
        *((u8*)(gsgfxState) + (var_r3_2 + 0x698)) = 4;
        *((u8*)(gsgfxState) + (var_r3_2 + 0x69C)) = 7;
        *((u8 *)gsgfxState + temp_r11_5) = *((u8 *)gsgfxState + temp_r11_5) | 0xE0;
        *((u8 *)gsgfxState + temp_r11_5) = (*((u8 *)gsgfxState + temp_r11_5) & ~0x1C) | 0x14;
        *((u8 *)gsgfxState + temp_r11_5) = (*((u8 *)gsgfxState + temp_r11_5) & ~0x380) | 0x200;
        temp_r5_3 = var_r9_2 + 0x267;
        *((u8 *)gsgfxState + temp_r5_3) = *((u8 *)gsgfxState + temp_r5_3) | 0x70;
        var_r5_3 = 0;
        temp_r12_4 = var_r9_2 + 0x225;
        M2C_FIELD(gsgfxState, s32 *, 0x20) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x20) | temp_r18);
        *((u8*)(gsgfxState) + (var_r8_2 + 0x690)) = 7;
        *((u8*)(gsgfxState) + (var_r8_2 + 0x694)) = 5;
        *((u8*)(gsgfxState) + (var_r8_2 + 0x698)) = 4;
        *((u8*)(gsgfxState) + (var_r8_2 + 0x69C)) = 7;
        *((u8*)(gsgfxState) + (var_r4_3 + 0x790)) = 0;
        *((u8*)(gsgfxState) + (var_r4_3 + 0x794)) = 0;
        *((u8*)(gsgfxState) + (var_r4_3 + 0x798)) = 0;
        *((u8*)(gsgfxState) + (var_r4_3 + 0x79C)) = 1;
        *((u8*)(gsgfxState) + (var_r4_3 + 0x7A0)) = 0;
        *((u8 *)gsgfxState + temp_r12_4) = *((u8 *)gsgfxState + temp_r12_4) & ~3;
        *((u8 *)gsgfxState + temp_r12_4) = *((u8 *)gsgfxState + temp_r12_4) & ~4;
        *((u8 *)gsgfxState + temp_r12_4) = *((u8 *)gsgfxState + temp_r12_4) | 8;
        *((u8 *)gsgfxState + temp_r12_4) = *((u8 *)gsgfxState + temp_r12_4) & ~0x30;
        *((u8 *)gsgfxState + temp_r12_4) = *((u8 *)gsgfxState + temp_r12_4) & ~0xC0;
        M2C_FIELD(gsgfxState, s32 *, 0x1C) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x1C) | temp_r18);
        *((u8*)(gsgfxState) + (var_r7_2 + 0x790)) = 0;
        *((u8*)(gsgfxState) + (var_r7_2 + 0x794)) = 0;
        *((u8*)(gsgfxState) + (var_r7_2 + 0x798)) = 0;
        *((u8*)(gsgfxState) + (var_r7_2 + 0x79C)) = 1;
        temp_r22_2 = var_r9_2 + 0x265;
        *((u8*)(gsgfxState) + (var_r7_2 + 0x7A0)) = 0;
        temp_r24 = var_r4_3 + 0x8D4;
        temp_r23 = var_r4_3 + 0x8D8;
        temp_r21 = var_r4_3 + 0x8DC;
        temp_r20_2 = var_r4_3 + 0x8E0;
        temp_r19_2 = var_r7_2 + 0x8D0;
        temp_r12_5 = var_r7_2 + 0x8D4;
        *((u8*)(gsgfxState) + (var_r4_3 + 0x8D0)) = 0;
        temp_r11_6 = var_r7_2 + 0x8D8;
        temp_r10_6 = var_r7_2 + 0x8DC;
        temp_r0_4 = var_r7_2 + 0x8E0;
        var_r3_2 += 0x10;
        var_r4_3 += 0x14;
        var_r6_3 += 1;
        *((u8 *)gsgfxState + temp_r24) = 0;
        var_r7_2 += 0x14;
        var_r8_2 += 0x10;
        var_r9_2 += 4;
        *((u8 *)gsgfxState + temp_r23) = 0;
        *((u8 *)gsgfxState + temp_r21) = 1;
        *((u8 *)gsgfxState + temp_r20_2) = 0;
        *((u8 *)gsgfxState + temp_r22_2) = *((u8 *)gsgfxState + temp_r22_2) & ~3;
        *((u8 *)gsgfxState + temp_r22_2) = *((u8 *)gsgfxState + temp_r22_2) & ~4;
        *((u8 *)gsgfxState + temp_r22_2) = *((u8 *)gsgfxState + temp_r22_2) | 8;
        *((u8 *)gsgfxState + temp_r22_2) = *((u8 *)gsgfxState + temp_r22_2) & ~0x30;
        *((u8 *)gsgfxState + temp_r22_2) = *((u8 *)gsgfxState + temp_r22_2) & ~0xC0;
        M2C_FIELD(gsgfxState, s32 *, 0x20) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x20) | temp_r18);
        *((u8 *)gsgfxState + temp_r19_2) = 0;
        *((u8 *)gsgfxState + temp_r12_5) = 0;
        *((u8 *)gsgfxState + temp_r11_6) = 0;
        *((u8 *)gsgfxState + temp_r10_6) = 1;
        *((u8 *)gsgfxState + temp_r0_4) = 0;
        var_ctr_5 -= 1;
    } while (var_ctr_5 != 0);
    var_r3_3 = 0;
    var_r7_3 = 0;
    var_r8_3 = 0;
    var_ctr_6 = 4;
    do {
        sp10 = sp20;
        temp_r10_7 = 1 << var_r5_3;
        temp_r11_7 = var_r8_3 + 0x2C6;
        *((u8*)(gsgfxState) + (var_r3_3 + 0xA11)) = sp20;
        temp_r19_3 = var_r8_3 + 0x2C4;
        temp_r17_2 = var_r8_3 + 0x2D6;
        temp_r12_6 = var_r8_3 + 0x2D4;
        temp_r9_6 = var_r7_3 + 0xA11;
        temp_r4_2 = var_r7_3 + 0xA10;
        /* draft: crashed mwcc */ // *((u8 *)gsgfxState + temp_r11_7) = (*((u8 *)gsgfxState + temp_r11_7) & ~0x7FF) | ((u8) sp10 & 0x7FF);
        var_r6_4 = 0;
        var_r3_3 += 5;
        var_r5_3 += 1;
        var_r7_3 += 5;
        var_r8_3 += 4;
        *((u8 *)gsgfxState + temp_r19_3) = (*((u8 *)gsgfxState + temp_r19_3) & ~0x7FF000) | ((unksp13 << 0xC) & 0x7FF000);
        /* draft: crashed mwcc */ // *((u8 *)gsgfxState + temp_r17_2) = (*((u8 *)gsgfxState + temp_r17_2) & ~0x7FF) | (unksp12 & 0x7FF);
        *((u8 *)gsgfxState + temp_r12_6) = (*((u8 *)gsgfxState + temp_r12_6) & ~0x7FF000) | ((unksp11 << 0xC) & 0x7FF000);
        M2C_FIELD(gsgfxState, s32 *, 0x28) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x28) | temp_r10_7);
        *((u8 *)gsgfxState + temp_r9_6) = sp20;
        *((u8 *)gsgfxState + temp_r4_2) = 0;
        var_ctr_6 -= 1;
    } while (var_ctr_6 != 0);
    var_r3_4 = 0;
    var_r4_4 = 0;
    var_ctr_7 = 0x10;
    do {
        temp_r12_7 = var_r6_4 & 1;
        *((u8*)(gsgfxState) + (var_r3_4 + 0xA24)) = 0xC;
        temp_r0_5 = var_r6_4 >> 1;
        if (temp_r12_7 != 0) {
            temp_r7 = (temp_r0_5 * 4) + 0x204;
            *((u8 *)gsgfxState + temp_r7) = (*((u8 *)gsgfxState + temp_r7) & ~0x7C000) | 0x30000;
        } else {
            temp_r7_2 = (temp_r0_5 * 4) + 0x206;
            *((u8 *)gsgfxState + temp_r7_2) = (*((u8 *)gsgfxState + temp_r7_2) & ~0x1F0) | 0xC0;
        }
        temp_r5_4 = var_r6_4 * 4;
        M2C_FIELD(gsgfxState, s32 *, 0x18) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x18) | (1 << temp_r0_5));
        *((u8*)(gsgfxState) + (temp_r5_4 + 0xA24)) = 0xC;
        *((u8*)(gsgfxState) + (var_r3_4 + 0xA64)) = 0x1C;
        if (temp_r12_7 != 0) {
            temp_r8_9 = (temp_r0_5 * 4) + 0x205;
            *((u8 *)gsgfxState + temp_r8_9) = (*((u8 *)gsgfxState + temp_r8_9) & ~0xF8) | 0xE0;
        } else {
            temp_r8_10 = (temp_r0_5 * 4) + 0x206;
            *((u8 *)gsgfxState + temp_r8_10) = (*((u8 *)gsgfxState + temp_r8_10) & ~0x3E) | 0x38;
        }
        var_r5_4 = 0;
        temp_r9_7 = var_r4_4 + 0xAA8;
        M2C_FIELD(gsgfxState, s32 *, 0x18) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x18) | (1 << temp_r0_5));
        temp_r10_8 = var_r4_4 + 0xAA4;
        temp_r16 = var_r6_4 * 8;
        temp_r8_11 = 1 << var_r6_4;
        temp_r11_8 = (var_r6_4 * 4) + 0x267;
        temp_r7_3 = temp_r16 + 0xAA4;
        temp_r0_6 = temp_r16 + 0xAA8;
        *((u8*)(gsgfxState) + (temp_r5_4 + 0xA64)) = 0x1C;
        var_r3_4 += 4;
        var_r4_4 += 8;
        var_r6_4 += 1;
        *((u8 *)gsgfxState + temp_r10_8) = 0;
        *((u8 *)gsgfxState + temp_r9_7) = 0;
        *((u8 *)gsgfxState + temp_r11_8) = *((u8 *)gsgfxState + temp_r11_8) & ~3;
        *((u8 *)gsgfxState + temp_r11_8) = *((u8 *)gsgfxState + temp_r11_8) & ~0xC;
        M2C_FIELD(gsgfxState, s32 *, 0x20) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x20) | temp_r8_11);
        *((u8 *)gsgfxState + temp_r7_3) = 0;
        *((u8 *)gsgfxState + temp_r0_6) = 0;
        var_ctr_7 -= 1;
    } while (var_ctr_7 != 0);
    var_r7_4 = 0;
    var_r8_4 = 0;
    var_r9_3 = 0;
    var_ctr_8 = 4;
    do {
        var_r6_5 = 0;
        *((u8*)(gsgfxState) + (var_r5_4 + 0xB24)) = 0;
        temp_r16_2 = var_r8_4 + 1;
        temp_r23_2 = var_r9_3 + 0x207;
        temp_r19_4 = 1 << var_r8_4;
        *((u8*)(gsgfxState) + (var_r5_4 + 0xB28)) = 1;
        temp_r20_3 = var_r5_4 + 0xB30;
        temp_r22_3 = (temp_r16_2 * 4) + 0x207;
        temp_r18_2 = 1 << temp_r16_2;
        temp_r17_3 = var_r7_4 + 0xB24;
        *((u8*)(gsgfxState) + (var_r5_4 + 0xB2C)) = 2;
        temp_r12_8 = var_r7_4 + 0xB28;
        temp_r11_9 = var_r7_4 + 0xB2C;
        temp_r10_9 = var_r7_4 + 0xB30;
        var_r5_4 += 0x10;
        var_r7_4 += 0x10;
        var_r8_4 += 2;
        *((u8 *)gsgfxState + temp_r20_3) = 3;
        var_r9_3 += 8;
        *((u8 *)gsgfxState + temp_r23_2) = *((u8 *)gsgfxState + temp_r23_2) & ~3;
        *((u8 *)gsgfxState + temp_r23_2) = (*((u8 *)gsgfxState + temp_r23_2) & ~0xC) | 4;
        *((u8 *)gsgfxState + temp_r22_3) = (*((u8 *)gsgfxState + temp_r22_3) & ~3) | 2;
        *((u8 *)gsgfxState + temp_r22_3) = *((u8 *)gsgfxState + temp_r22_3) | 0xC;
        M2C_FIELD(gsgfxState, s32 *, 0x18) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x18) | temp_r19_4);
        M2C_FIELD(gsgfxState, s32 *, 0x18) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x18) | temp_r18_2);
        *((u8 *)gsgfxState + temp_r17_3) = 0;
        *((u8 *)gsgfxState + temp_r12_8) = 1;
        *((u8 *)gsgfxState + temp_r11_9) = 2;
        *((u8 *)gsgfxState + temp_r10_9) = 3;
        var_ctr_8 -= 1;
    } while (var_ctr_8 != 0);
    var_r4_5 = 0;
    var_ctr_9 = 0x10;
    do {
        temp_r0_7 = var_r6_5 + 0xB64;
        temp_r17_4 = var_r4_5 + 0x313;
        *((u8 *)gsgfxState + temp_r0_7) = 1;
        temp_r7_4 = 1 << var_r6_5;
        var_r5_5 = 0;
        temp_r12_9 = var_r4_5 + 0x312;
        temp_r11_10 = var_r4_5 + 0x311;
        var_r6_5 += 1;
        temp_r9_8 = *((u8 *)gsgfxState + temp_r17_4) & ~3;
        var_r4_5 += 4;
        *((u8 *)gsgfxState + temp_r17_4) = temp_r9_8;
        *((u8 *)gsgfxState + temp_r17_4) = *((u8 *)gsgfxState + temp_r17_4) & ~0xC;
        *((u8 *)gsgfxState + temp_r17_4) = *((u8 *)gsgfxState + temp_r17_4) & ~0x70;
        *((u8 *)gsgfxState + temp_r12_9) = *((u8 *)gsgfxState + temp_r12_9) & ~0x180;
        *((u8 *)gsgfxState + temp_r12_9) = *((u8 *)gsgfxState + temp_r12_9) & ~0x1E;
        *((u8 *)gsgfxState + temp_r12_9) = *((u8 *)gsgfxState + temp_r12_9) & ~0xE0;
        *((u8 *)gsgfxState + temp_r11_10) = *((u8 *)gsgfxState + temp_r11_10) & ~7;
        *((u8 *)gsgfxState + temp_r11_10) = *((u8 *)gsgfxState + temp_r11_10) & ~8;
        *((u8 *)gsgfxState + temp_r11_10) = *((u8 *)gsgfxState + temp_r11_10) & ~0x10;
        M2C_FIELD(gsgfxState, s32 *, 0x2C) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x2C) | temp_r7_4);
        *((u8 *)gsgfxState + temp_r0_7) = 2;
        *((u8 *)gsgfxState + temp_r0_7) = 1;
        var_ctr_9 -= 1;
    } while (var_ctr_9 != 0);
    var_r4_6 = 0;
    var_r6_6 = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x58D) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x31) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x31) & ~7);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 1);
    M2C_FIELD(gsgfxState, s8 *, 0x58D) = 0;
    var_ctr_10 = 4;
    do {
        *((u8*)(gsgfxState) + (var_r4_6 + 0xB74)) = var_r5_5;
        *((u8*)(gsgfxState) + (var_r4_6 + 0xB78)) = var_r5_5;
        switch (var_r5_5) {                         /* irregular */
        case 0:
            M2C_FIELD(gsgfxState, u8 *, 0x7B) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x7B) & ~7) | (var_r5_5 & 7));
            M2C_FIELD(gsgfxState, u8 *, 0x7B) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x7B) & ~0x38) | ((var_r5_5 << 3) & 0x38));
            break;
        case 1:
            M2C_FIELD(gsgfxState, u16 *, 0x7A) = (u16) ((M2C_FIELD(gsgfxState, u16 *, 0x7A) & ~0x1C0) | ((var_r5_5 << 6) & 0x1C0));
            M2C_FIELD(gsgfxState, u16 *, 0x7A) = (s8) (((u8) M2C_FIELD(gsgfxState, u16 *, 0x7A) & ~0xE) | ((var_r5_5 << 1) & 0xE));
            break;
        case 2:
            M2C_FIELD(gsgfxState, u16 *, 0x7A) = (s8) (((u8) M2C_FIELD(gsgfxState, u16 *, 0x7A) & ~0x70) | ((var_r5_5 << 4) & 0x70));
            M2C_FIELD(gsgfxState, s32 *, 0x78) = (s32) ((M2C_FIELD(gsgfxState, s32 *, 0x78) & ~0x38000) | ((var_r5_5 << 0xF) & 0x38000));
            break;
        case 3:
            M2C_FIELD(gsgfxState, u8 *, 0x79) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x79) & ~0x1C) | ((var_r5_5 << 2) & 0x1C));
            M2C_FIELD(gsgfxState, u8 *, 0x79) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x79) & ~0xE0) | ((var_r5_5 << 5) & 0xE0));
            break;
        }
        M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x2000);
        temp_r0_8 = var_r5_5 >> 1;
        M2C_FIELD(gsgfxState, s32 *, 0xC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0xC) | (1 << var_r5_5));
        *((u8*)(gsgfxState) + (var_r6_6 + 0xB74)) = var_r5_5;
        *((u8*)(gsgfxState) + (var_r6_6 + 0xB78)) = var_r5_5;
        *((u8*)(gsgfxState) + (var_r4_6 + 0xB94)) = 0;
        *((u8*)(gsgfxState) + (var_r4_6 + 0xB98)) = 0;
        if (var_r5_5 & 1) {
            temp_r8_12 = (temp_r0_8 * 4) + 0x7E;
            *((u8 *)gsgfxState + temp_r8_12) = *((u8 *)gsgfxState + temp_r8_12) & ~0xF;
            *((u8 *)gsgfxState + temp_r8_12) = *((u8 *)gsgfxState + temp_r8_12) & ~0xF0;
        } else {
            temp_r7_5 = temp_r0_8 * 4;
            temp_r8_13 = temp_r7_5 + 0x7F;
            temp_r7_6 = temp_r7_5 + 0x7E;
            *((u8 *)gsgfxState + temp_r8_13) = *((u8 *)gsgfxState + temp_r8_13) & ~0xF;
            *((u8 *)gsgfxState + temp_r7_6) = *((u8 *)gsgfxState + temp_r7_6) & ~0xF0;
        }
        temp_r8_14 = var_r6_6 + 0xB94;
        temp_r7_7 = var_r6_6 + 0xB98;
        var_r4_6 += 8;
        var_r5_5 += 1;
        M2C_FIELD(gsgfxState, s32 *, 8) = (s32) (M2C_FIELD(gsgfxState, s32 *, 8) | (1 << temp_r0_8));
        var_r6_6 += 8;
        *((u8 *)gsgfxState + temp_r8_14) = 0;
        *((u8 *)gsgfxState + temp_r7_7) = 0;
        var_ctr_10 -= 1;
    } while (var_ctr_10 != 0);
    M2C_FIELD(gsgfxState, s32 *, 0xBB4) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBB8) = 4;
    M2C_FIELD(gsgfxState, s32 *, 0xBBC) = 5;
    M2C_FIELD(gsgfxState, s32 *, 0xBC0) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x3B) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x3B) & ~1);
    M2C_FIELD(gsgfxState, u8 *, 0x3B) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x3B) & ~2);
    M2C_FIELD(gsgfxState, u8 *, 0x3A) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x3A) & ~7) | 4);
    M2C_FIELD(gsgfxState, u8 *, 0x3B) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x3B) & ~0xE0) | 0xA0);
    M2C_FIELD(gsgfxState, u8 *, 0x3A) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x3A) & ~8);
    M2C_FIELD(gsgfxState, u8 *, 0x3A) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x3A) & ~0x10);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 4);
    M2C_FIELD(gsgfxState, s32 *, 0xBB4) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBB8) = 4;
    M2C_FIELD(gsgfxState, s32 *, 0xBBC) = 5;
    M2C_FIELD(gsgfxState, s32 *, 0xBC0) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0xBC4) = 1;
    M2C_FIELD(gsgfxState, u8 *, 0x3B) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x3B) | 8);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 4);
    M2C_FIELD(gsgfxState, s8 *, 0xBC4) = 1;
    M2C_FIELD(gsgfxState, s8 *, 0xBC5) = 1;
    M2C_FIELD(gsgfxState, u8 *, 0x3B) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x3B) | 0x10);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 4);
    M2C_FIELD(gsgfxState, s8 *, 0xBC5) = 1;
    M2C_FIELD(gsgfxState, s8 *, 0xBE4) = 1;
    M2C_FIELD(gsgfxState, s32 *, 0xBE8) = 3;
    M2C_FIELD(gsgfxState, s8 *, 0xBEC) = 1;
    M2C_FIELD(gsgfxState, u8 *, 0x37) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x37) | 1);
    M2C_FIELD(gsgfxState, u8 *, 0x37) = (u8) ((M2C_FIELD(gsgfxState, u8 *, 0x37) & ~0xE) | 6);
    M2C_FIELD(gsgfxState, u8 *, 0x37) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x37) | 0x10);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 2);
    M2C_FIELD(gsgfxState, s8 *, 0xBE4) = 1;
    M2C_FIELD(gsgfxState, s32 *, 0xBE8) = 3;
    M2C_FIELD(gsgfxState, s8 *, 0xBEC) = 1;
    M2C_FIELD(gsgfxState, s8 *, 0xBF0) = 1;
    M2C_FIELD(gsgfxState, u8 *, 0x43) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x43) | 0x40);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x10);
    M2C_FIELD(gsgfxState, s8 *, 0xBF0) = 1;
    M2C_FIELD(gsgfxState, s8 *, 0xBF1) = 1;
    M2C_FIELD(gsgfxState, u8 *, 0x3B) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x3B) | 4);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 4);
    M2C_FIELD(gsgfxState, s8 *, 0xBF1) = 1;
    M2C_FIELD(gsgfxState, s8 *, 0xBF2) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0xBF3) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x3E) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x3E) & ~1);
    M2C_FIELD(gsgfxState, s8 *, 0x3F) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 8);
    M2C_FIELD(gsgfxState, s8 *, 0xBF2) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0xBF3) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBC8) = 7;
    M2C_FIELD(gsgfxState, s8 *, 0xBD4) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBCC) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBD0) = 7;
    M2C_FIELD(gsgfxState, s8 *, 0xBD5) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x1FB) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0x1FA) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x1F9) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1F9) | 7);
    M2C_FIELD(gsgfxState, u8 *, 0x1F9) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1F9) | 0x38);
    M2C_FIELD(gsgfxState, u8 *, 0x1F9) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x1F9) & ~0xC0);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x100);
    M2C_FIELD(gsgfxState, s32 *, 0xBC8) = 7;
    M2C_FIELD(gsgfxState, s8 *, 0xBD4) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBCC) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBD0) = 7;
    M2C_FIELD(gsgfxState, s8 *, 0xBD5) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBD8) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBDC) = 0x11;
    M2C_FIELD(gsgfxState, s32 *, 0xBE0) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0x1FC) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0x1FC) & ~0xFFFFFF);
    M2C_FIELD(gsgfxState, u8 *, 0x203) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x203) & ~3);
    M2C_FIELD(gsgfxState, u8 *, 0x203) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x203) & ~0xC);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x200);
    M2C_FIELD(gsgfxState, s32 *, 0xBD8) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBDC) = 0x11;
    M2C_FIELD(gsgfxState, s32 *, 0xBE0) = 0;
    M2C_FIELD(gsgfxState, s32 *, 0xBF4) = 0;
    M2C_FIELD(gsgfxState, f32 *, 0xBF8) = 0.0f;
    M2C_FIELD(gsgfxState, f32 *, 0xBFC) = 1000.0f;
    M2C_FIELD(gsgfxState, f32 *, 0xC00) = 0.0f;
    M2C_FIELD(gsgfxState, f32 *, 0xC04) = 1000.0f;
    M2C_FIELD(gsgfxState, s32 *, 0xC09) = sp20;
    GSgfx_GCWriteFog((unsigned long)(0), (float)(u32)(gsgfxState), (float)(sp20), (float)(u32)(gsgfxState), (float)(0x11));
    spC = sp20;
    M2C_FIELD(gsgfxState, u8 *, 0x2F5) = (u8) spC;
    M2C_FIELD(gsgfxState, u8 *, 0x2F6) = unkspD;
    M2C_FIELD(gsgfxState, u8 *, 0x2F7) = unkspE;
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x20000);
    M2C_FIELD(gsgfxState, s32 *, 0xC09) = sp20;
    M2C_FIELD(gsgfxState, s8 *, 0xC08) = 0;
    M2C_FIELD(gsgfxState, s16 *, 0xC0E) = 0;
    M2C_FIELD(gsgfxState, s8 *, 0xC0D) = 0;
    M2C_FIELD(gsgfxState, u8 *, 0x2FA) = (u8) (M2C_FIELD(gsgfxState, u8 *, 0x2FA) & ~4);
    M2C_FIELD(gsgfxState, u8 *, 0x2FA) = (s16) (((u16) M2C_FIELD(gsgfxState, u8 *, 0x2FA) & ~0x3FF) | 0x156);
    M2C_FIELD(gsgfxState, s32 *, 0) = (s32) (M2C_FIELD(gsgfxState, s32 *, 0) | 0x40000);
    M2C_FIELD(gsgfxState, s8 *, 0xC0D) = 0;
    M2C_FIELD(gsgfxState, s16 *, 0xC0E) = 0;
    GSgfx_GCFlushState();
}

void GSgfx_GCInitState(void) {
    int i;
    RAW(gsgfxState->genMode) = 0;
    gsgfxState->genMode.id = 0x00;
    RAW(gsgfxState->zmode) = 0;
    gsgfxState->zmode.id = 0x40;
    RAW(gsgfxState->cmode0) = 0;
    gsgfxState->cmode0.id = 0x41;
    RAW(gsgfxState->cmode1) = 0;
    gsgfxState->cmode1.id = 0x42;
    RAW(gsgfxState->peCtrl) = 0;
    gsgfxState->peCtrl.id = 0x43;
    RAW(gsgfxState->r44) = 0;
    gsgfxState->r44.id = 0x47;
    RAW(gsgfxState->r48) = 0;
    gsgfxState->r48.id = 0x48;
    RAW(gsgfxState->tref[0]) = 0;
    gsgfxState->tref[0].id = 0x28;
    RAW(gsgfxState->tref[1]) = 0;
    gsgfxState->tref[1].id = 0x29;
    RAW(gsgfxState->tref[2]) = 0;
    gsgfxState->tref[2].id = 0x2a;
    RAW(gsgfxState->tref[3]) = 0;
    gsgfxState->tref[3].id = 0x2b;
    RAW(gsgfxState->tref[4]) = 0;
    gsgfxState->tref[4].id = 0x2c;
    RAW(gsgfxState->tref[5]) = 0;
    gsgfxState->tref[5].id = 0x2d;
    RAW(gsgfxState->tref[6]) = 0;
    gsgfxState->tref[6].id = 0x2e;
    RAW(gsgfxState->tref[7]) = 0;
    gsgfxState->tref[7].id = 0x2f;
    RAW(gsgfxState->iref) = 0;
    gsgfxState->iref.id = 0x27;
    RAW(gsgfxState->ras1ss0) = 0;
    gsgfxState->ras1ss0.id = 0x25;
    RAW(gsgfxState->ras1ss1) = 0;
    gsgfxState->ras1ss1.id = 0x26;
    for (s32 i = 0; i < 8; i++) {
        RAW(gsgfxState->texMode0[i]) = 0;
        RAW(gsgfxState->texMode1[i]) = 0;
        RAW(gsgfxState->texImg0[i]) = 0;
        RAW(gsgfxState->texImg1[i]) = 0;
        RAW(gsgfxState->texImg2[i]) = 0;
        RAW(gsgfxState->texImg3[i]) = 0;
        RAW(gsgfxState->texTlut[i]) = 0;
        gsgfxState->texMode0[i].id = GSgfx_GCTexMode0Ids[i];
        gsgfxState->texMode1[i].id = GSgfx_GCTexMode1Ids[i];
        gsgfxState->texImg0[i].a.id = GSgfx_GCTexImage0Ids[i];
        gsgfxState->texImg1[i].id = GSgfx_GCTexImage1Ids[i];
        gsgfxState->texImg2[i].id = GSgfx_GCTexImage2Ids[i];
        gsgfxState->texImg3[i].id = GSgfx_GCTexImage3Ids[i];
        gsgfxState->texTlut[i].a.id = GSgfx_GCTexTlutIds[i];
    }
    RAW(gsgfxState->tlutLoad0) = 0;
    gsgfxState->tlutLoad0.id = 0x64;
    RAW(gsgfxState->tlutLoad1) = 0;
    gsgfxState->tlutLoad1.id = 0x65;
    RAW(gsgfxState->suS[0]) = 0;
    RAW(gsgfxState->suT[0]) = 0;
    gsgfxState->suS[0].id = 0x30;
    gsgfxState->suT[0].id = 0x31;
    RAW(gsgfxState->suS[1]) = 0;
    RAW(gsgfxState->suT[1]) = 0;
    gsgfxState->suS[1].id = 0x32;
    gsgfxState->suT[1].id = 0x33;
    RAW(gsgfxState->suS[2]) = 0;
    RAW(gsgfxState->suT[2]) = 0;
    gsgfxState->suS[2].id = 0x34;
    gsgfxState->suT[2].id = 0x35;
    RAW(gsgfxState->suS[3]) = 0;
    RAW(gsgfxState->suT[3]) = 0;
    gsgfxState->suS[3].id = 0x36;
    gsgfxState->suT[3].id = 0x37;
    RAW(gsgfxState->suS[4]) = 0;
    RAW(gsgfxState->suT[4]) = 0;
    gsgfxState->suS[4].id = 0x38;
    gsgfxState->suT[4].id = 0x39;
    RAW(gsgfxState->suS[5]) = 0;
    RAW(gsgfxState->suT[5]) = 0;
    gsgfxState->suS[5].id = 0x3a;
    gsgfxState->suT[5].id = 0x3b;
    RAW(gsgfxState->suS[6]) = 0;
    RAW(gsgfxState->suT[6]) = 0;
    gsgfxState->suS[6].id = 0x3c;
    gsgfxState->suT[6].id = 0x3d;
    RAW(gsgfxState->suS[7]) = 0;
    RAW(gsgfxState->suT[7]) = 0;
    gsgfxState->suS[7].id = 0x3e;
    RAW(gsgfxState->r1ec) = 0;
    gsgfxState->suT[7].id = 0x3f;
    gsgfxState->r1ec.id = 0x22;
    RAW(gsgfxState->matIdxA) = 0;
    RAW(gsgfxState->matIdxB) = 0;
    RAW(gsgfxState->r1f8) = 0;
    gsgfxState->r1f8.id = 0xf3;
    RAW(gsgfxState->kcolA0[0]) = 0;
    RAW(gsgfxState->kcolA1[0]) = 0;
    gsgfxState->kcolA0[0].id = 0xe0;
    gsgfxState->kcolA1[0].id = 0xe1;
    gsgfxState->kcolA0[0].f = 0;
    gsgfxState->kcolA1[0].f = 0;
    RAW(gsgfxState->kcolA0[1]) = 0;
    RAW(gsgfxState->kcolA1[1]) = 0;
    gsgfxState->kcolA0[1].id = 0xe2;
    gsgfxState->kcolA1[1].id = 0xe3;
    gsgfxState->kcolA0[1].f = 0;
    gsgfxState->kcolA1[1].f = 0;
    RAW(gsgfxState->kcolA0[2]) = 0;
    RAW(gsgfxState->kcolA1[2]) = 0;
    gsgfxState->kcolA0[2].id = 0xe4;
    gsgfxState->kcolA1[2].id = 0xe5;
    gsgfxState->kcolA0[2].f = 0;
    gsgfxState->kcolA1[2].f = 0;
    RAW(gsgfxState->kcolA0[3]) = 0;
    RAW(gsgfxState->kcolA1[3]) = 0;
    gsgfxState->kcolA0[3].id = 0xe6;
    gsgfxState->kcolA1[3].id = 0xe7;
    gsgfxState->kcolA0[3].f = 0;
    gsgfxState->kcolA1[3].f = 0;
    RAW(gsgfxState->kcolB0[0]) = 0;
    RAW(gsgfxState->kcolB1[0]) = 0;
    gsgfxState->kcolB0[0].id = 0xe0;
    gsgfxState->kcolB1[0].id = 0xe1;
    gsgfxState->kcolB0[0].f = 1;
    gsgfxState->kcolB1[0].f = 1;
    RAW(gsgfxState->kcolB0[1]) = 0;
    RAW(gsgfxState->kcolB1[1]) = 0;
    gsgfxState->kcolB0[1].id = 0xe2;
    gsgfxState->kcolB1[1].id = 0xe3;
    gsgfxState->kcolB0[1].f = 1;
    gsgfxState->kcolB1[1].f = 1;
    RAW(gsgfxState->kcolB0[2]) = 0;
    RAW(gsgfxState->kcolB1[2]) = 0;
    gsgfxState->kcolB0[2].id = 0xe4;
    gsgfxState->kcolB1[2].id = 0xe5;
    gsgfxState->kcolB0[2].f = 1;
    gsgfxState->kcolB1[2].f = 1;
    RAW(gsgfxState->kcolB0[3]) = 0;
    RAW(gsgfxState->kcolB1[3]) = 0;
    gsgfxState->kcolB0[3].id = 0xe6;
    gsgfxState->kcolB1[3].id = 0xe7;
    gsgfxState->kcolB0[3].f = 1;
    gsgfxState->kcolB1[3].f = 1;
    RAW(gsgfxState->r1fc) = 0;
    gsgfxState->r1fc.id = 0xf4;
    RAW(gsgfxState->r200) = 0;
    gsgfxState->r200.id = 0xf5;
    for (i = 0; i < 8; i++) {
        RAW(gsgfxState->ksel[i]) = 0;
        gsgfxState->ksel[i].id = 0xf6 + i;
    }
    for (i = 0; i < 4; i++) {
        gsgfxState->ksel[i * 2].lo = 0;
        gsgfxState->ksel[i * 2].hi = 1;
        gsgfxState->ksel[i * 2 + 1].lo = 2;
        gsgfxState->ksel[i * 2 + 1].hi = 3;
    }
    for (i = 0; i < 16; i++) {
        RAW(gsgfxState->tevc[i]) = 0;
        RAW(gsgfxState->teva[i]) = 0;
        gsgfxState->teva[i].id = 0xc1 + i * 2;
        gsgfxState->tevc[i].id = 0xc0 + i * 2;
    }
    for (i = 0; i < 16; i++) {
        RAW(gsgfxState->indCmd[i]) = 0;
        gsgfxState->indCmd[i].id = 0x10 + i;
    }
    RAW(gsgfxState->r350) = 0;
    gsgfxState->r350.id = 0x0f;
    RAW(gsgfxState->fog0) = 0;
    RAW(gsgfxState->fog1) = 0;
    RAW(gsgfxState->fog2) = 0;
    RAW(gsgfxState->fog3) = 0;
    gsgfxState->fog0.id = 0xee;
    gsgfxState->fog1.id = 0xef;
    gsgfxState->fog2.id = 0xf0;
    gsgfxState->fog3.id = 0xf1;
    RAW(gsgfxState->r2f4) = 0;
    gsgfxState->r2f4.id = 0xf2;
    RAW(gsgfxState->r2f8) = 0;
    gsgfxState->r2f8.id = 0xe8;
    RAW(gsgfxState->rangeAdj[0]) = 0;
    gsgfxState->rangeAdj[0].id = 0xe9;
    RAW(gsgfxState->rangeAdj[1]) = 0;
    gsgfxState->rangeAdj[1].id = 0xea;
    RAW(gsgfxState->rangeAdj[2]) = 0;
    gsgfxState->rangeAdj[2].id = 0xeb;
    RAW(gsgfxState->rangeAdj[3]) = 0;
    gsgfxState->rangeAdj[3].id = 0xec;
    RAW(gsgfxState->rangeAdj[4]) = 0;
    gsgfxState->rangeAdj[4].id = 0xed;
    RAW(gsgfxState->r354) = 0;
    gsgfxState->r354.id = 0x68;
    RAW(gsgfxState->scis0) = 0;
    gsgfxState->scis0.id = 0x20;
    RAW(gsgfxState->scis1) = 0;
    gsgfxState->scis1.id = 0x21;
    gsgfxState->dirty = 0;
    gsgfxState->dTref = 0;
    gsgfxState->dIref = 0;
    gsgfxState->d0c = 0;
    gsgfxState->d10 = 0;
    gsgfxState->d14 = 0;
    gsgfxState->dTevc = 0;
    gsgfxState->dTeva = 0;
    gsgfxState->dKcolA = 0;
    gsgfxState->dKcolB = 0;
    gsgfxState->dKsel = 0;
    gsgfxState->indDirty = 0;
}

void GSgfx_GCFirstInit(void) {
    memset(&_gcGlobalRegState, 0, 5);
    _gcGlobalRegState.b0 = 0;
    _gcGlobalRegState.b1 = 0;
    _gcGlobalRegState.b2 = 0;
    _gcGlobalRegState.b3 = 0;
    _gcGlobalRegState.b4 = 0;
}
} // extern C
