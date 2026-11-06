#ifndef GAME_GSGFXLAYER_H
#define GAME_GSGFXLAYER_H

#include <dolphin/types.h>

struct GSgfxLayer;
struct GSgfxLight;
struct GSgfxVF;
struct GSgfxMtxEntry;
struct GSgfxTex;
struct GStexture;
class GSgfxMatrixStack;
struct _gsgfxLayerFifo;

struct GSgfxLayerRGBA {
    u8 r, g, b, a;
};
struct GSgfxLayerTevOp {
    s32 op, bias, scale;
    u8 clamp;
    s32 reg;
};
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
union GSgfxLayerTevColorValue {
    GSgfxLayerRGBA c;
    s16 s10[4];
};
struct GSgfxLayerTevColor {
    u32 type;
    GSgfxLayerTevColorValue v;
};
struct GSgfxLayerIndInd {
    u8 indId;
    u8 pad[3];
    s32 fmt, bias, mtx, ws, wt, alpha;
    u8 addPrev, utc;
};
struct GSgfxLayerIndWarp {
    u8 indId, signMod, wrap;
    u8 pad;
    s32 mtx;
};
struct GSgfxLayerIndTile {
    u8 indId;
    u8 pad;
    u16 sizeS, sizeT, spaceS, spaceT;
    u16 pad2;
    s32 fmt, mtx, bias, alpha;
};
struct GSgfxLayerIndBump {
    u8 indId;
    u8 pad[3];
    s32 mtx;
};
union GSgfxLayerIndValue {
    GSgfxLayerIndInd ind;
    GSgfxLayerIndWarp warp;
    GSgfxLayerIndTile tile;
    GSgfxLayerIndBump bump;
};
struct GSgfxLayerInd {
    u32 type;
    GSgfxLayerIndValue v;
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
    GSgfxLayerRGBA amb[2];
    GSgfxLayerRGBA mat[2];
    u8 nTevStages;
    s32 tevOrder[16][3];
    s32 colorIn[16][4];
    s32 alphaIn[16][4];
    GSgfxLayerTevOp colorOp[16];
    GSgfxLayerTevOp alphaOp[16];
    GSgfxLayerTevColor tevColor[4];
    GSgfxLayerInd ind[4];
    u8 nIndStages;
    s32 indOrder[4][2];
    s32 indScale[4][2];
    GSgfxLayerRGBA kcolor[4];
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
    GSgfxLayerRGBA fogColor;
    u16 fogTable[10];
    u16 fogCenter;
    u8 fogRangeEnable;
    u8 fogEnable;
};

struct GSgfxLayerData {
    GSgfxLayer* next;
    u32 flags;
    char name[0x20];
    GSgfxLayerID id;
    GSgfxLayerType type;
    u8 hwState[0xC40];
    GSgfxLayerHW hw;
    struct DirtyState {
        u32 groups;
        u32 geom;
        u32 texGen;
        u32 texOffsets;
        u32 raster;
        u32 lightDirty;
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
        GSgfxVF* vf[8];
        GSgfxVF* last;
        GSgfxMtxEntry* mtx;
        u8 mtxValid;
        u8 pad91[3];
        u32 texMask;
        GSgfxTex* tex[8];
    } dirty[2];
    struct PassFifo {
        void* data;
        u32 size;
        u8 gxFifo[0x80];
        u32 unk88;
        u32 unk8c;
        u32 color;
        u8 flag;
        int redirectId;
        int redirectPass;
        int redirectOffset;
        _gsgfxLayerFifo* pre;
        _gsgfxLayerFifo* post;
        u16 unkAC;
        u16 unkAE;
        u32 unkB0;
        u32 unkB4;
        u32 unkB8;
    } passes[2];
    PassFifo* curFifo;
    int curPass;
    u32 unk1998;
    GSgfxVF* curVF;
    GSgfxMatrixStack* matrixStack;
    GStexture* texCopy;
    u32 texCopyMode;
    u8 texCopyData[7];
    u8 visCount;
    u8 pad19b4[4];
    u8 distFlag;
    u8 pad19b9[3];
    f32 distParams[6];
    struct RenderHook {
        int pass;
        void* end;
        void (*callback)(void*);
        void* arg;
    } hooks[4];
};

#define GSL_HWSTATE(l, T, off) (*(T*)((u8*)(l)->hwState + ((off) - 0x30)))
#define GSL_IN(l, T, member, memberOff, off) (*(T*)((u8*)&(l)->member + ((off) - (memberOff))))
#ifdef __MWERKS__
#define LAYER_F(l, T, off, member) (*(T)((s8 *)(l) + (off)))
#define LAYER_FI(l, T, off, add, member) (*(T)((s8 *)(l) + ((off) + (add))))
#define LAYER_HW(l, T, off) (*(T)((s8 *)(l) + (off)))
#define LAYER_CUR_PASS(l) ((u8 *)(l) + 0x1818 + LAYER_F(l, s32 *, 0x1994, curPass) * 0xBC)
#else
#define LAYER_F(l, T, off, member) (*(T)&(l)->member)
#define LAYER_FI(l, T, off, add, member) (*(T)&(l)->member)
#define LAYER_HW(l, T, off) (*(T)((u8*)(l)->hwState + ((off) - 0x30)))
#define LAYER_CUR_PASS(l) ((u8*)&(l)->passes[(l)->curPass])
#endif
#endif
