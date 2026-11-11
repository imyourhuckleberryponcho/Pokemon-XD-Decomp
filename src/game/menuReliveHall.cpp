#include <dolphin/types.h>
#include "game/gc_fused.h"
#include <game/gcdata.h>
#include <game/winwork.h>
#include <game/gcptr.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>
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
struct GSgfxVF;
struct GStexture;
struct MenuItem;
struct MenuSprite;
struct MenuSpriteVal;
struct ModelBank;
struct PCBOX;
struct PokemonData;

#pragma peephole off

enum GSgfxLayerID { GSgfxLayerID0 };

struct GSgfxColAu8 {
    union {
        u32 rgba;
        u8 v[4];
    };
};
#define RH_A 3

struct tagSPRITE_WORK {
    tagSPRITE_WORK* next;
    u8 unk4;
    u8 unk5;
    s16 itemId;
    u8 pad8[0x4];
    void* slotC;
    u8 pad10[0x38];
    GCuptr hook;
    GCsptr msgId;
    s16 x, y, w, h;
    s32 unk58;
    s16 sx, sy, sw, sh;
    gc_be32 color;
};

struct tagWINDOW_WORK {
    s8 flags;
    u8 pad1[3];
    s32 menuId;
    u8 pad8[0x4];
    void* slotC;
    void* slot10;
    void* slot14;
    u8 pad18[0x4];
    s32 layer;
    u8 pad20[4];
    tagSPRITE_WORK* sprites;
    void* slot28;
    void* slot2C;
    u8 pad30[0x38];
    void* slot68;
    void* slot6C;
    void* slot70;
    void* slot74;
    void* slot78;
    void* slot7C;
    void* slot80;
    void* slot84;
    s32 cursor;
    s16 x, y;
};

struct MENU_ITEM_dd_ {
    u8 pad0[4];
    s16 spriteId;
    s16 x, y, w, h;
    s16 cursorSprite;
    void* msg;
    void* callback;
    s16 next;
};

extern "C" u32 __float_nan[];

struct GSgfxVF {
    u8 _draft[1];
};
struct GStexture {
    u8 _draft[1];
};
struct MenuItem {
    u8 _draft[1];
};
struct MenuSprite {
    u8 _draft[1];
};
struct MenuSpriteVal {
    u8 _draft[1];
};
struct ModelBank {
    u8 _draft[1];
};
struct PCBOX {
    u8 _draft[1];
    static PCBOX* getPointer();
#ifdef __MWERKS__
    u8 isPokemonFull();
#else
    bool isPokemonFull();
#endif
};
struct PokemonData {
    u8 _draft[1];
};

extern "C" {
void GSgfxBeginSurface(unsigned short num);
void GSgfxColor4u8(u8 r, u8 g, u8 b, u8 a);
void GSgfxEndSurface(void);
void GSgfxSelectTexture(u8 map, GStexture* texture);
void GSgfxSetPrimitiveType(u32 type);
void GSgfxSetTUnitUserAlphaArg(u8 unit, u32 a, u32 b, u32 c, u32 d);
void GSgfxSetTUnitUserAlphaOp(u8 unit, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg);
void GSgfxSetTUnitUserColorArg(u8 unit, u32 a, u32 b, u32 c, u32 d);
void GSgfxSetTUnitUserColorOp(u8 unit, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg);
void GSgfxSetupRenderAndSelect(GSgfxVF* vf);
void GSgfxTexCoord2f(f32 s, f32 t);
GSgfxVF * GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void GSgfxVertex2f(f32 x, f32 y);
char* GSmsgGetGSchar(u32 msg);
u32 GSmsgGetRect(s32);
s32 GSmsgPrint2(s32 layer, s32 x, s32 y, u32 color, u32 msg);
void GSprimSetQuadVertexOrder(s32 order);
void* GSresGetResourceAllGroup(u32 id);
u16 GStextureGetXsize(GStexture* tex);
u16 GStextureGetYsize(GStexture* tex);
DarkPokemon* darkPokemonGetDarkPokemon(u32);
MenuSprite* menuSpriteBiosGetPtr(u32 id);
MenuSpriteVal* menuSpriteBiosGetValPtr(MenuSprite* sprite);
s32 pokecoloGetCountryCode(void);
const char* pokemonDataBiosGetName(PokemonData* pdata);
extern s32 jtbl_3115;
extern bool lbl_804EA7F0;
bool lbl_804EA7F0;
namespace { u8 rate01ToAlphaFrom50(f32); }
}
namespace {
bool isDirRegionInReverseClockwise(f32 a, f32 b, f32 c);
}
extern "C++" {
f32 dirRefresh2PI(f32 v);
}

class CMetaMenu;
namespace {
void _stateDirChangeProcHook(CMetaMenu* m, s32 win);
}

static inline int ptFPClassify(f32 x)
{
    switch ((*(s32*)&x) & 0x7f800000) {
    case 0x7f800000:
        if ((*(s32*)&x) & 0x007fffff) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(s32*)&x) & 0x007fffff) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

static inline f32 ptSqrt(f32 x)
{
    if (x > 0.0f) {
        f32 y = x;
        f64 guess = __frsqrte(y);
        guess = 0.5 * guess * (3.0 - guess * guess * y);
        guess = 0.5 * guess * (3.0 - guess * guess * y);
        guess = 0.5 * guess * (3.0 - guess * guess * y);
        return y * guess;
    } else if (x < 0.0) {
        return *(f32*)__float_nan;
    } else if (ptFPClassify(x) == 1) {
        return *(f32*)__float_nan;
    } else {
        return x;
    }
}

struct CReliveStage {
public:
    u8 pad[0x3D4];
    s8 hit;
    s32 getTempo();
    s32 getDancerQuantity();
    Pokemon* getDancerPointer(s32);
    Pokemon* getVisitorPointer();
    void init();
    s32 getPassion();
    bool isBonusGet();
    void pickupDancer(Pokemon&, s32);
    void pickupVisitor(Pokemon&);
    void putVisitor(Pokemon&);
    void insertDancer(Pokemon&, s32);
    void exchangeDancer(Pokemon&, s32);
    void exchangeVisitor(Pokemon&);
};

struct CReliveHall {
public:
    static CReliveHall* getPointer();
    CReliveStage* getStage(s32);
    bool isReliveReadyDarkLugiaExist();
    s32 getReliveGiveStageQuantity();
public:
#ifdef __MWERKS__
    u8 isReliveReadyPokemonExist();
#else
    bool isReliveReadyPokemonExist();
#endif
};

enum MENU_POKEMON_CB_TYPE { MPCB0 };
extern "C" {
s8 GSinputGetLeftStickXData(s32, s32);
s8 GSinputGetLeftStickYData(s32, s32);
s8 GSinputGetRightStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
bool pokemonCheckValid(Pokemon*);
void GSmodelSetTexAnimIndex(s32, s32);
void GSmodelSetTexAnimType(s32, s32);
void GSmodelStartTexAnimation(s32);
void GSmodelStopTexAnimation(s32);
void GSmodelSetVisibility(s32, bool);
void scriptModelClose(s32);
s32 scriptModelOpen(u32);
s32 floorGetCurrentGroupID();
void * GSresGetResource(s32, s32);
void cameraPlayAnime(s32, u32, s32, f32);
void cameraSetType(s32);
void* memcpy(void*, const void*, u32);
void msgctrlSetValue(u32, GCuptr);
void GSfsysReadWait(s32);
void GSfsysFree(s32);
void GSresFreeGroup(s32);
void menuPokemonStatusOpenFromPcBox(Pokemon*, void (*)(Pokemon*, MENU_POKEMON_CB_TYPE, s32), s32);
void winMsgOpen(s32, u32, s32, s32);
void winMsgClose(s32);
void GSprimSetBlendMode(s32);
void GSprimDraw2DPixelListC(void*, s32, void*);
void* memset(void*, int, u32);
double sin(double);
double cos(double);
#ifndef __MWERKS__
static
#endif
inline double fabs(double x) { return __fabs(x); }
void* GSmemAllocClr(u32);
void GSmemFree(void*);
void* windowSearchID(s32);
void menuDrawReliveMeter3(Pokemon*, s32, s32, s32, s32, u8, s32);
void spriteSetScissor(s32, s32, s32, s32, s32);
void spriteSetOffset(s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void winSpriteDraw(void*, void*);
MENU_ITEM_dd_* menuItemBiosGetPtr(s32, s32);
}
template <typename T>
struct PocketVec {
    T x, y;
};
f32 xyxy2dir(const PocketVec<short>&, const PocketVec<short>&);
f32 xy2dir(f32, f32);
bool isDirRegionIn(f32, f32, f32);
f32 dirSubOne(f32, f32);
void menuPtSpriteDrawAndRollScale(u16, u32, f32, f32, f32, f32);
struct PocketVecF { f32 x, y; };
extern "C" u16 zokuseiGetPokemonSpriteID(void*, u16);
void menuPtSpriteDraw(u16, s32, s32);
void menuPtSpriteDrawCenterColor(u16, s32, s32, u32);
void relivehallDraw9StageNumber(int);
void relivehallDraw9StageInfo(int);
int reliveHallPokemonToAisyou(Pokemon*, Pokemon*);
extern GC_CONST GSgfxColAu8 GSgfxColAu8_Black;
void menuPtWindowWorkDraw(s32);
int degreeSubHalf(s32, s32);
int xyxy2dirDegree(const PocketVec<short>&, const PocketVec<short>&);
f32 xyxy2distance(const PocketVec<short>&, const PocketVec<short>&);
void menuPtPlaySe(u32);
f32 dirSubHalf(f32, f32);
int degreeRefresh360(s32);
void setBitTable(u32*, s32, bool);
bool getBitTable(u32*, s32);
extern "C" void GSprimDraw2DLine(GSgfxColAu8 c0, GSgfxColAu8 c1, f32 x0, f32 y0, f32 x1, f32 y1);
inline void reliveLine2D(GSgfxColAu8* c0, GSgfxColAu8* c1, PocketVec<f32> a, PocketVec<f32> b)
{
    GSprimDraw2DLine(*c0, *c1, a.x, a.y, b.x, b.y);
}
MENU_ITEM_dd_* menuPtItemGetByMenuIdAndItemId(s32, u32, s32);
void menuPtItemDrawOffset(MENU_ITEM_dd_*, s32, s32);
void menuPtItemDrawOffsetXWColor(MENU_ITEM_dd_*, s32, s32, u32);
void menuPtItemDrawAlpha(MENU_ITEM_dd_*, u8);
void menuPtSpriteWorkSetSw(tagWINDOW_WORK*, u32, s32, bool);
void menuPtSpriteWorkSetSw(tagWINDOW_WORK*, tagSPRITE_WORK*, bool);
void menuPtWindowWorkDraw(tagWINDOW_WORK*);
void menuPtSpriteWorkSetWidthRateColor(tagWINDOW_WORK*, u32, s32, f32, GSgfxColAu8);
tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(tagWINDOW_WORK*, u32, s32);
u32 GSgfxColAu8To32(GSgfxColAu8);

extern GSgfxColAu8 relivehallAisyou2ColorTbl[3];
extern s16 lbl_8032E568[10];

#ifdef __MWERKS__
GSgfxColAu8 relivehallAisyou2ColorTbl[3] = { { 0x2800FFFF }, { 0x28AAFFFF }, { 0xC8F0FFFF } };
#else
GSgfxColAu8 relivehallAisyou2ColorTbl[3] = { { 0xFFFF0028 }, { 0xFFFFAA28 }, { 0xFFFFF0C8 } };
#endif
extern "C" {
s32 pcReliveHallSoundTbl[5] = { 0x459, 0x45A, 0x45B, 0x14, 0x15 };
}
s16 lbl_8032E568[10] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 0 };
namespace {
const PocketVec<short> circlePosition = { 320, 280 };
const PocketVec<f32> fcirclePosition = { 320.0f, 280.0f };
u8 blurAlphaTbl[9] = { 0xFF, 0xD7, 0xAF, 0x87, 0x5F, 0x37, 0, 0, 0 };
f32 blurScaleTbl[9] = { 1.0f, 0.85f, 0.7f, 0.55f, 0.4f, 0.25f, 0.0f, 0.0f, 0.0f };
f32 starMasterScaleTbl[10] = { 1.1f, 0.85f, 1.0f, 0.9f, 1.1f, 0.9f, 0.85f, 1.1f, 1.0f, 0.85f };
f32 _markerDancerOnDirTbl[5][4] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.1415927f, 0.0f, 0.0f, 0.0f, 2.0943952f, 4.1887903f, 0.0f, 5.497787f, 0.7853982f, 2.3561945f, 3.9269907f };
f32 _zokuseiMarkDancerOnDirTbl[5][4] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.4486233f, 0.0f, 0.0f, 0.0f, 1.4486233f, 1.6929694f, 0.0f, 0.0f, 1.4486233f, 1.9373156f, 4.328417f, 0.0f, 4.82409f, 1.4590952f, 1.6824975f, 4.600688f };
f32 _markerDancerEmptyDirTbl[4][4] = { 0.0f, 0.0f, 0.0f, 0.0f, 3.1415927f, 0.0f, 0.0f, 0.0f, 1.5707964f, 4.712389f, 0.0f, 0.0f, 1.0471976f, 3.1415927f, 5.235988f, 0.0f };
PocketVec<short> _cursorPositionTblDefault[9] = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { 320, 280 }, { 198, 428 }, { 539, 428 } };
#ifdef __MWERKS__
GSgfxColAu8 _passion2ColorTbl[13] = { { 0x2800FFFF }, { 0x2855FFFF }, { 0x28AAFFFF }, { 0x78CDFFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF } };
#else
GSgfxColAu8 _passion2ColorTbl[13] = { { 0xFFFF0028 }, { 0xFFFF5528 }, { 0xFFFFAA28 }, { 0xFFFFCD78 }, { 0xFFFFF0C8 }, { 0xFFFFF0C8 }, { 0xFFFFF0C8 }, { 0xFFFFF0C8 }, { 0xFFFFF0C8 }, { 0xFFFFF0C8 }, { 0xFFFFF0C8 }, { 0xFFFFF0C8 }, { 0xFFFFF0C8 } };
#endif
f32 _aisyou2ScaleTbl[3] = { 0.6f, 0.8f, 1.0f };
struct LineWidthEntry { s32 a; f32 b; s32 c; f32 d; };
LineWidthEntry _aisyou2LineWidthHalfTable[3] = { { 1, 0.75f, 1, 0.3f }, { 2, 1.5f, 2, 0.6f }, { 3, 2.25f, 3, 0.9f } };
s32 localWindowTable[8] = { 0x67, 0x71, 0x72, 0x88, 0x76, 0xCF, 0xE3, 0 };
u32 actionMenuCatchVisitorOnPokemon[6] = { 0x4, 0xd111, 0xd112, 0xd113, 0xd114, 0x0 };
u32 actionMenuCatchDancerOnPokemon[6] = { 0x3, 0xd111, 0xd113, 0xd114, 0x0, 0x0 };
u32 actionMenuCatchVisitorOnNone[6] = { 0x4, 0xd115, 0xd112, 0xd113, 0xd114, 0x0 };
u32 actionMenuCatchDancerOnNone[6] = { 0x3, 0xd115, 0xd113, 0xd114, 0x0, 0x0 };
u32 actionMenuOnVisitor[6] = { 0x4, 0xd116, 0xd112, 0xd113, 0xd114, 0x0 };
u32 actionMenuOnDancer[6] = { 0x3, 0xd116, 0xd113, 0xd114, 0x0, 0x0 };

#ifdef __MWERKS__
#define RH_ACTION_LIST(tbl, off) (s32*)(tbl + off)
#define RH_ACTION_LIST2(c, tbl, a, b) (s32*)(c ? tbl + a : tbl + b)
#else
static s32* rh_action_list(u32 off) {
    switch (off) {
    case 0x220: return (s32*)actionMenuCatchVisitorOnPokemon;
    case 0x238: return (s32*)actionMenuCatchDancerOnPokemon;
    case 0x250: return (s32*)actionMenuCatchVisitorOnNone;
    case 0x268: return (s32*)actionMenuCatchDancerOnNone;
    case 0x280: return (s32*)actionMenuOnVisitor;
    case 0x298: return (s32*)actionMenuOnDancer;
    }
    return 0;
}
#define RH_ACTION_LIST(tbl, off) rh_action_list(off)
#define RH_ACTION_LIST2(c, tbl, a, b) ((c) ? rh_action_list(a) : rh_action_list(b))
#endif
PocketVec<short> _cursorPositionTblAddPc[2] = { { 336, 428 }, { 379, 428 } };
}

struct CAnt {
    GCsptr a0, a4;
    s32 a8;
    f32 aC;
    u8 a10;
    s32 a14;
    s16 a18, a1A;
    f32 a1C;
    s32 a20, a24, a28;
    f32 a2C;
    s32 a30;
    void drawAndUpdate(PocketVec<short>);
    void initByPokemon(Pokemon*);
    void initByPokemonAndSetColorAnimationInReliveHallVisitor(Pokemon*);
    void setAnimation(s32);
    static void systemUpdate(bool);
    static void allRequestCancel();
    static void waitEndOfReading();
};
class CMetaMenu;
struct CMenuGlobalState;
struct CKeyInfo {
    u8 pad0[4];
    u16 trg;
    u16 rep;
    u8 pad8[0x12];
};

struct VP {
    u32 id;
    GCuptr value;
};

struct CInfoWindow {
    s32 windowId;
    s32 itemId;
    u8 opened;
    bool isMsg;
    s32 msgId;
    VP values[4];
    u16 buttons;
    void exec(CMetaMenu&, u32, bool);
    void init(s32, u32);
    void initTutorialTalk();
    void draw();
public:
    void setMsgCtrlValue(u32, GCuptr);
    void close();
    void open(u32, bool);
};

class CState {
public:
    s32 current, next, prev, count;
    f32 time;
    f32 dt;
    u8 work[0x40];
    u8 work2[0x40];
    s32 w98, w9c, wa0;
    u8 padA4[4];
    void update();
    void addTime();
    void init();
    inline void change(s32 n)
    {
        next = n;
        memset(work, 0, 0x40);
    }
};

class CMetaMenu {
public:
    s32 fadeTime;
    s32 fadeState;
    s32 pad8;
    u32 seId;
    u8 pad10[0xC];
    s32 windowIds[64];
    void (*windowFuncs[64])(CMetaMenu*, s32);
    s32* windowTable;
    CKeyInfo keyInfo;
    s32 repeat;
    u16 lastOn;
    u8 tutorialMode;
    CInfoWindow info;
    CState state;
    u64 time;
    CMenuGlobalState* pState;
    u8 updated;
    u8 pad32D;
    u16 cachedInput;

    virtual void drawAll() = 0;
    virtual bool isAnimationStateNone();
    virtual void updateAll();
    virtual void tutorialExitKick();
    s32 calcAnimationTimeRate0toX(f32, s32);
    f32 calcAnimationTimeRate0to1to0(f32);
    f32 calcAnimationTimeRate0to1(f32);
    void waitAtTime(f32);
    void drawHook();
    void vsyncUpdate();
    void systemFadeWaitToEnd();
    void systemFadeOutSetAndWait(f32);
    void systemFadeOutKick(f32);
    static void systemFadeInKick();
    void systemFadeOutKeepAfterFloorPush();
    void alphaFadeDraw();
    void alphaFadeOutAndWait();
    void alphaFadeUpdate();
    void alphaFadeOutKick();
    void alphaFadeInKick();
    static s32 defautlLocalWindowOpenTable[];
    CKeyInfo* getKeyInfo();
    void aButtonWait();
    s32 actionMenu(u32*, int, s32, s32, s32);
    void localWindowRemove(s32);
    void localWindowDrawAll(s32, s32);
    void localWindowDrawAll();
    void localWindowEntry(s32, s32, void (*)(CMetaMenu*, s32));
    s32 localWindowSearch(s32);
    void localWindowDeleteAll();
    void localWindowCreateAll();
    void localWindowSetTable(s32*);
};

namespace {
void _menuDrawReliveMeter(Pokemon*, s32, s32, s32, s32, u8, GSgfxLayerID, s32);
void _relivehallTempoBarSpriteSetting(tagWINDOW_WORK*, u32, int, u8, bool);
void menuPtSpriteDrawArrow(u16, u32, f32, int);
}
struct CMenuPokemonCursor {
    void setPositionIndex(s32);
    void setPosition(PocketVec<short> p) {
        pos.x = p.x;
        pos.y = p.y;
    }
    u8 active;
    s32 mode;
    f32 t;
    s32 index;
    u8 pad10[4];
    PocketVec<short> pos;
    PocketVec<short>* table;
    u8 pad1C[4];
    Pokemon pokemon;
    CAnt ant;
    CAnt before;
    bool holding;
    u8 pad14D[3];
    bool isCatchPokemon();
    void setPokemon(Pokemon*);
    void draw();
    void setPositionTable(PocketVec<short>*, s32);
    void setPositionTableDummy();
public:
    void setAnimationOff();
};

struct GSgfxLayer;
void GSprimSetup2DRender(GSgfxLayer*);
extern "C" GSgfxLayer* GSgfxLayerFindByID(GCsint);
extern "C" void GSprimSetLineWidth(f32);
extern "C" void menuDrawReliveUpdate();
void menuPtPlaySe(u32);
struct CMenuGlobalState {
    s32 f0;
    s32 kind;
    s32 next;
    CMenuPokemonCursor cursor;
    u8 tutorialFlag;
    u8 tutorialFinished;
};

namespace {

struct SCircle {
    f32 outer;
    s32 radius;
    f32 inner;
    struct Px {
        s16 angle;
        u16 x, y;
        u8 alpha;
        u8 pad;
    } px[0x2800];
    s32 count;
    s16 pos[0x2800][2];
    GSgfxColAu8 col[0x2800];
    bool sw[0x2800];
    u32* bits;
    s32 start[361];
    void draw();
    void allSwOff();
    void setFade(u8);
    void setSwPrime(int, int, bool);
    void setSw(f32, f32, bool);
    void drawPixelAll(int, int, int);
    void drawPixelOne(int, int, int);
    void init(f32, int, f32, GSgfxColAu8);
};

struct SPokemonView {
    u8 pad0;
    bool hidden;
    u8 pad2[2];
    f32 dir;
    f32 dirTo;
    f32 dirFrom;
    CAnt ant;
    f32 dir2;
    f32 dir2From;
    f32 dir2To;
    PocketVec<short> getPosition();
    Pokemon* getPokemonWithPickupOverride();
    Pokemon* getPokemon();
};

struct CStick {
    u8 edge, cur, prev;
    u8 pad3;
    f32 dir;
    u32 count;
    void update();
};

class CMenuReliveHall : public CMetaMenu {
public:
    s32 stageIndex;
    CReliveStage* stage;
    SPokemonView views[9];
    s32 savedIndex;
    s32* actionList;
    s32 actionSel;
    s32 actionCancel;
    CStick stick;
    SCircle circle[3];
    s32 scriptB;
    s32 scriptA;
    s32 modelB;
    s32 modelA;
    CMenuPokemonCursor* cursor;
    PocketVec<short> markerPosA[9];
    CInfoWindow infoWin;
    s32 savedTempo;
    u8 statusVisitor[0xC4];
    u8 statusSet;
    u8 pad81089[0x3];
    CState anim;
    u8 alphaA;
    u8 alphaB;
    u8 markerOnVisitor;
    u8 markerOnEmpty;
    u8 markerOnDancer;
    u8 pad81139[0x1];
    PocketVec<short> markerPosB[9];
    u8 pad8115E[0x26];
    u8 tempoMode;
    u8 pad81185[3];
    f32 tempoRate;
    u8 pad8118C[4];
    virtual void drawAll();
    virtual bool isAnimationStateNone() { return anim.current == 0; }
    virtual void updateAll() { if (!tutorialMode) stick.update(); CMetaMenu::updateAll(); }
    static void* operator new(size_t n) { return GSmemAllocClr(n); }
    void drawStarLightOne(s32, f32, f32, s32);
    void drawDancerHitEffect();
    void drawDancerStarLight();
    void drawStarHitEffect(f32, f32, f32);
    f32 starTimeFromBorn(f32&, f32&, f32);
    f32 calcStarDir(int, int);
    void infoMessageDisplay3Line(u32);
    void infoMessageDisplay(u32);
    void drawVisitorHitEffect();
    void drawVisitorStarLight(s32, SPokemonView*);
    void drawVsitorLine(s32, SPokemonView*);
    SPokemonView* getPokemonViewByClockwizePositionWithCatch(int);
    int dancerPositionQuantityWithCatch();
    Pokemon* getVisitorWithCatch();
    int getDirToAisyou(f32);
    void setCircleSw();
    void drawStagePokemon();
    void drawMarkers(bool);
    void draw9StageInfo();
    void drawStageCursor();
    Pokemon* getStatusDisplayVisitorGetPointer();
    int getTempo(bool);
    GSgfxColAu8 getCircleColorAisyou(f32&, f32&, int&, int);
    s32 actionMenuMain();
    void stateDirChangeWinDraw(s32);
    void actionStatus();
    Pokemon* actionStatusCallback(Pokemon*, MENU_POKEMON_CB_TYPE);
    int cursorMoveDirSearch(PocketVec<short>*, int, int);
    void cursorMoveDir(int);
    bool animationProcessButtonInterrupt();
    int getQuantityMarkerDancerEmpty();
    int getQuantityMarkerDancerOnPlusDancerEmpty();
    void setStage(int);
    void moveStage(int);
    Pokemon* getCurrentPokemonPointer();
    void resetStatusDisplayVisitor();
    void setStatusDisplayVisitor(Pokemon*);
    void animationStateUpdate();
    void unloadDatas();
    void loadDatas();
    void actionChange();
    void actionPut();
    void actionPickup();
    void editAfterDp0VisitorCheck();
    void actionDecide(u32);
    void dancerMoveAnimationOne(SPokemonView&, f32);
    void dancerMoveAnimationAll(f32);
    void resetViewAll();
    void cursorPositionDecideAtStageChange(int);
    void makeCursorPositionTbl(PocketVec<short>*);
    int getPassion(int*);
    int getTempoPassion(int*, bool, bool);
    GSgfxColAu8 positionToAisyouColor(int, int);
    GSgfxColAu8 pokemonToAisyouColor(Pokemon*, Pokemon*);
    int pokemonToAisyou(Pokemon*, Pokemon*);
    Pokemon* getPokemonFromPositionWithCatch(int);
    void main(CMenuGlobalState&);
    void init(CMenuGlobalState&);
    void markerClear();
    void drawStatusPanel();
    void drawMainBG();
    void stateDirChangeProc();
    void animationDataReset();
    void dancerMoveAnimationKick(f32*, f32*, bool, f32);
    void aButtomAction();
    void stateMainProc();
    void loop();
};

CMenuReliveHall* pMenuReliveHall;
s32 _lastViewStage;

void thisExec(CMenuGlobalState&);
void thisFree();
void thisNew();
}

void menuReliveHallExecFromPcBox(CMenuGlobalState& s)
{
    thisExec(s);
}

void relivehallSetLastViewStage(s32 i)
{
    _lastViewStage = i;
}

s32 relivehallGetLastViewStage()
{
    return _lastViewStage;
}

int relivehallTempoToLevel(int t)
{
    if (t <= 0x1A) return 0;
    if (t <= 0x35) return 1;
    return 2;
}

f32 relivehallTempoToRate(int t)
{
    return (f32)t / 96.0f;
}

void relivehallDraw9StageInfo(int cur)
{
    for (int i = 0; i < 9; i++) {
        if (i != cur) {
            MENU_ITEM_dd_* it;
            s32 ox = i * 0x42;
            ox += lbl_8032E568[i];
            CReliveStage* stage = CReliveHall::getPointer()->getStage(i);
            Pokemon* v = CReliveHall::getPointer()->getStage(i)->getVisitorPointer();
            if (v) {
                it = menuItemBiosGetPtr(0x72, 0x2B2);
                _menuDrawReliveMeter(v, it->x + ox, it->y, it->w, it->h, 0xFF, (GSgfxLayerID)((tagWINDOW_WORK*)windowSearchID(0x72))->layer, i);
            }
            if (stage->getDancerQuantity()) {
                menuPtItemDrawOffset(menuItemBiosGetPtr(0x72, 0x2B0), ox, 0);
                int tempo = stage->getTempo();
                u32 color = GSgfxColAu8To32(relivehallAisyou2ColorTbl[relivehallTempoToLevel(tempo)]);
                it = menuItemBiosGetPtr(0x72, 0x2B1);
                menuPtItemDrawOffsetXWColor(it, ox, (s32)((f32)it->w * relivehallTempoToRate(tempo)), color);
            }
        }
    }
}

void relivehallDraw9StageNumber(int cur)
{
    for (int i = 0; i < 9; i++) {
        MENU_ITEM_dd_* it = menuPtItemGetByMenuIdAndItemId(0x72, 0x2A7, i);
        u8 a;
        if (i == cur) a = 0xFF; else a = 0x3C;
        menuPtItemDrawAlpha(it, a);
    }
}

void relivehallDrawStageInfoCursor(s32 idx, int tempo, int flag, Pokemon* p, bool b)
{
    s32 base;
    tagWINDOW_WORK* w = (tagWINDOW_WORK*)windowSearchID(0x71);
    base = idx * 0x42;
    w->x = base;
    w->x += lbl_8032E568[idx];
    _relivehallTempoBarSpriteSetting(w, 0x2B4, tempo, 0xFF, 0);
    menuPtSpriteWorkSetSw(w, 0x2B3, 0, flag != 0);
    menuPtSpriteWorkSetSw(w, 0x2BA, 0, b);
    menuPtSpriteWorkSetSw(w, 0x8E9, 0, b == 0);
    menuPtWindowWorkDraw(w);
    if (p) {
        s32 ox = base + lbl_8032E568[idx];
        MENU_ITEM_dd_* it = menuItemBiosGetPtr(0x71, 0x2B5);
        _menuDrawReliveMeter(p, it->x + ox, it->y, it->w, it->h, 0xFF, (GSgfxLayerID)w->layer, idx);
    }
}

#ifdef __MWERKS__
#define RH_NAMED(gcexpr, pcobj, type_ptr, offset, path) M2C_FIELD(gcexpr, type_ptr, offset)
#define RH_PTR(gc, pc) gc
#define RH_POKE(gc, pc) (((u8*)(gc)) + 0x20)
#define RH_VIEWS_ADJ 0
#else
#include <stddef.h>
#define RH_NAMED(gcexpr, pcobj, type_ptr, offset, path) (*(type_ptr)&((CMenuReliveHall*)(pcobj))->path)
#define RH_PTR(gc, pc) pc
#define RH_POKE(gc, pc) ((void)(gc), (u8*)&((CMenuPokemonCursor*)(pc))->pokemon)
#define RH_VIEWS_ADJ ((s32)offsetof(CMenuReliveHall, views) - 0x340)
#endif

namespace {
void _relivehallTempoBarSpriteSetting(tagWINDOW_WORK* w, u32 id, int tempo, u8 alpha, bool scissor)
{
    f32 rate = relivehallTempoToRate(tempo);
    GSgfxColAu8 c = relivehallAisyou2ColorTbl[relivehallTempoToLevel(tempo)];
    c.v[RH_A] = alpha;
    if (scissor) {
        tagSPRITE_WORK* spr = menuPtSpriteWorkGetByItemID(w, id, 0);
        menuPtSpriteWorkSetWidthRateColor(w, id, 0, 1.0f, c);
        spriteSetScissor(w->layer, spr->x, spr->y, (s32)((f32)spr->w * rate), spr->h);
        spriteSetEnv(w->layer);
        winSpriteDraw(w, spr);
        spriteSetOffset(w->layer, 0, 0);
        spriteClearScissor(w->layer);
        spriteSetEnv(w->layer);
        return;
    }
    menuPtSpriteWorkSetWidthRateColor(w, id, 0, rate, c);
}
void CMenuReliveHall::drawStatusPanel() {
    u16 ids[2];
    CMenuPokemonCursor *temp_r27_3;
    MenuItem *temp_r3_2;
    Pokemon *var_r3;
    s16 temp_r3_7;
    s16 temp_r3_8;
    s16 temp_r4;
    s16 temp_r8;
    s32 temp_r27_2;
    s32 temp_r3_3;
    s32 temp_r3_5;
    s32 temp_r3_9;
    s32 var_r27_2;
    u8 var_r27_4;
    tagWINDOW_WORK *temp_r31;
    u16 *var_r27;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;
    GCuptr temp_r3;
    u32 temp_r5;
    u32 temp_r7;
    u8 var_r0;
    u8 var_r27_3;
    u16 var_r28;
    u8 var_r28_2;
    u8 var_r30;
    u8 *temp_r27;
    u8 *temp_r28;
    u8 *temp_r28_2;
    u8 *temp_r28_3;
    u8 *temp_r30;
    u8 *temp_r30_2;
    u8 *temp_r30_3;
    u8 *temp_r30_4;
    u8 *temp_r3_4;
    u8 *temp_r3_6;

    temp_r31 = (tagWINDOW_WORK *)(windowSearchID(0x67));
    temp_r3 = (GCuptr)(((CMenuReliveHall*)(this))->getStatusDisplayVisitorGetPointer());
    if (temp_r3 != 0) {
        temp_r3_2 = (MenuItem *)(menuItemBiosGetPtr(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x4, menuID), 0x289U));
        _menuDrawReliveMeter((Pokemon*)((Pokemon *) temp_r3), (s32) M2C_FIELD(temp_r3_2, s16 *, 6), (s32) M2C_FIELD(temp_r3_2, s16 *, 8), (s32) M2C_FIELD(temp_r3_2, s16 *, 0xA), (s32) M2C_FIELD(temp_r3_2, s16 *, 0xC), 0xFFU, (GSgfxLayerID)(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x1C, layerID)), RH_NAMED(this, this, s32 *, 0x338, stageIndex));
        for (int i = 0; i < 2; i++) {
            ids[i] = zokuseiGetPokemonSpriteID((void *)(((Pokemon*)((Pokemon *) temp_r3))->getPokemonDataPtr()), i);
        }
        temp_r27 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x297U, 0));
        temp_r28 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x298U, 0));
        if (ids[0] == ids[1]) {
            menuPtSpriteDraw(ids[0], (M2C_NAMED(((tagSPRITE_WORK*)(temp_r27)), s16 *, 0x50, x) + M2C_NAMED(((tagSPRITE_WORK*)(temp_r28)), s16 *, 0x50, x)) / 2,
                             (M2C_NAMED(((tagSPRITE_WORK*)(temp_r27)), s16 *, 0x52, y) + M2C_NAMED(((tagSPRITE_WORK*)(temp_r28)), s16 *, 0x52, y)) / 2);
        } else {
            menuPtSpriteDraw(ids[0], M2C_NAMED(((tagSPRITE_WORK*)(temp_r27)), s16 *, 0x50, x), M2C_NAMED(((tagSPRITE_WORK*)(temp_r27)), s16 *, 0x52, y));
            menuPtSpriteDraw(ids[1], M2C_NAMED(((tagSPRITE_WORK*)(temp_r28)), s16 *, 0x50, x), M2C_NAMED(((tagSPRITE_WORK*)(temp_r28)), s16 *, 0x52, y));
        }
    }
    if (temp_r3 != 0) {
        switch (pokecoloGetCountryCode()) {
        case 0:
            temp_r28_2 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x4D3U, 0));
            msgctrlSetValue((u32)(0x37), (GCuptr)(GSmsgGetGSchar((u32)(pokemonDataBiosGetName((PokemonData*)(((Pokemon*)((Pokemon *) temp_r3))->getPokemonDataPtr()))))));
            GSmsgPrint2(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x1C, layerID), M2C_NAMED(((tagSPRITE_WORK*)(temp_r28_2)), s16 *, 0x50, x), M2C_NAMED(((tagSPRITE_WORK*)(temp_r28_2)), s16 *, 0x52, y), -1, 0x4278);
            break;
        case 1:
        case 2:
            msgctrlSetValue((u32)(0x37), (GCuptr)(((Pokemon*)((Pokemon *) temp_r3))->getNicknamePtr()));
            temp_r3_4 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x4D3U, 0));
            GSmsgPrint2(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x1C, layerID), M2C_NAMED(((tagSPRITE_WORK*)(temp_r3_4)), s16 *, 0x50, x), M2C_NAMED(((tagSPRITE_WORK*)(temp_r3_4)), s16 *, 0x52, y), -1, 0x4279);
            break;
        }
        temp_r28_3 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x4D4U, 0));
        msgctrlSetValue(0x34, (GCuptr) ((Pokemon*)((Pokemon *) temp_r3))->getLevel());
        GSmsgPrint2(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x1C, layerID), M2C_NAMED(((tagSPRITE_WORK*)(temp_r28_3)), s16 *, 0x50, x), M2C_NAMED(((tagSPRITE_WORK*)(temp_r28_3)), s16 *, 0x52, y), -1, 0x4271);
        switch (pokecoloGetCountryCode()) {
        case 1:
        case 2:
            temp_r3_6 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x8EEU, 0));
            GSmsgPrint2(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x1C, layerID), M2C_NAMED(((tagSPRITE_WORK*)(temp_r3_6)), s16 *, 0x50, x), M2C_NAMED(((tagSPRITE_WORK*)(temp_r3_6)), s16 *, 0x52, y), -1, 0xD15F);
            break;
        }
    }
    temp_r30 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x2A5U, 0));
    msgctrlSetValue(0x2F, RH_NAMED(this, this, s32 *, 0x338, stageIndex) + 1);
    GSmsgPrint2(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x1C, layerID), M2C_NAMED(((tagSPRITE_WORK*)(temp_r30)), s16 *, 0x50, x), M2C_NAMED(((tagSPRITE_WORK*)(temp_r30)), s16 *, 0x52, y), -1, 0xD157);
    temp_r30_2 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x2A6U, 0));
    s16 tw = GSmsgGetRect(0xD161) >> 16;
    GSmsgPrint2(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x1C, layerID), M2C_NAMED(((tagSPRITE_WORK*)(temp_r30_2)), s16 *, 0x50, x) + (s16)(M2C_NAMED(((tagSPRITE_WORK*)(temp_r30_2)), s16 *, 0x54, w) / 2 - tw / 2), M2C_NAMED(((tagSPRITE_WORK*)(temp_r30_2)), s16 *, 0x52, y), -1, 0xD161);
    temp_r30_3 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x2D2U, 0));
    tw = GSmsgGetRect(0xD123) >> 16;
    GSmsgPrint2(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x1C, layerID), M2C_NAMED(((tagSPRITE_WORK*)(temp_r30_3)), s16 *, 0x50, x) + (s16)(M2C_NAMED(((tagSPRITE_WORK*)(temp_r30_3)), s16 *, 0x54, w) / 2 - tw / 2), M2C_NAMED(((tagSPRITE_WORK*)(temp_r30_3)), s16 *, 0x52, y), -1, 0xD123);
    temp_r30_4 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x4D0U, 0));
    var_r27_2 = 0xD122;
    if (lbl_804EA7F0) {
        var_r27_2 = 0xD15A;
    }
    tw = GSmsgGetRect(var_r27_2) >> 16;
    GSmsgPrint2(M2C_NAMED(((WinWorkLayout*)(temp_r31)), s32 *, 0x1C, layerID), M2C_NAMED(((tagSPRITE_WORK*)(temp_r30_4)), s16 *, 0x50, x) + (s16)(M2C_NAMED(((tagSPRITE_WORK*)(temp_r30_4)), s16 *, 0x54, w) / 2 - tw / 2), M2C_NAMED(((tagSPRITE_WORK*)(temp_r30_4)), s16 *, 0x52, y), -1, var_r27_2);
    if ((u8) RH_NAMED(this, this, u8 *, 0x81184, tempoMode) != 0) {
        menuPtSpriteWorkSetSw((tagWINDOW_WORK*)(temp_r31), 0x316U, 0, 0U);
        temp_r27_2 = RH_NAMED(this, this, s32 *, 0x80FC0, savedTempo);
        _relivehallTempoBarSpriteSetting(RH_PTR((tagWINDOW_WORK*)(temp_r31), (tagWINDOW_WORK*)(temp_r31)), 0x28BU, (s32) ((RH_NAMED(this, this, f32 *, 0x81188, tempoRate) * (f32) (((CMenuReliveHall*)(this))->getTempo(0U) - temp_r27_2)) + (f32) temp_r27_2), 0xFFU, 1U);
        return;
    }
    var_r28_2 = 0;
    var_r30 = 0;
    if (((CMenuPokemonCursor*)(RH_NAMED(this, this, CMenuPokemonCursor **, 0x80F64, cursor)))->isCatchPokemon() != 0) {
        if (((Pokemon*)RH_POKE((temp_r27_3 = RH_NAMED(this, this, CMenuPokemonCursor **, 0x80F64, cursor)), temp_r27_3))->checkValid() != 0) {
            var_r3 = (Pokemon *)RH_POKE(temp_r27_3, temp_r27_3);
        } else {
            var_r3 = NULL;
        }
        if (((Pokemon*)(var_r3))->isDarkPokemon() == 0) {
            var_r30 = 1;
        }
    }
    if (var_r30 != 0) {
        var_r0 = 0;
        temp_r3_9 = M2C_FIELD(RH_NAMED((GCsptr)this, this, CMenuPokemonCursor **, 0x80F64, cursor), s32 *, 0xC);
        var_r0 = !((temp_r3_9 >= 0) && (temp_r3_9 <= 5)) ? var_r0 : 1;
        if (var_r0 != 0) {
            var_r28_2 = 1;
        }
    }
    var_r27_3 = 0;
    if (var_r28_2 != 0) {
        var_r27_3 = 0xFF;
    }
    _relivehallTempoBarSpriteSetting((tagWINDOW_WORK*)(temp_r31), 0x316U, ((CMenuReliveHall*)(this))->getTempo(1U), var_r27_3, 1U);
    var_r27_4 = 0xFF;
    if (var_r28_2 != 0) {
        var_r27_4 = rate01ToAlphaFrom50(((CMetaMenu*)((CMetaMenu *) this))->calcAnimationTimeRate0to1to0(0.6f));
    }
    _relivehallTempoBarSpriteSetting((tagWINDOW_WORK*)(temp_r31), 0x28BU, ((CMenuReliveHall*)(this))->getTempo(0U), var_r27_4, 1U);
}

}

namespace {
void CMenuReliveHall::drawMainBG() {
    tagWINDOW_WORK* temp_r31 = (tagWINDOW_WORK*)windowSearchID(0x67);
    bool temp_r30 = getVisitorWithCatch() != 0;
    int bonus;
    s32 passion = getPassion(&bonus);
    s32 level;
    if (passion <= 0) {
        level = 0;
    } else if (passion <= 0x1B) {
        level = 1;
    } else if (passion <= 0x34) {
        level = 2;
    } else if (passion <= 0x5A) {
        level = 3;
    } else if (passion < 0xC0) {
        level = 4;
    } else {
        level = bonus + 4;
    }
    f32 rate = calcAnimationTimeRate0to1(0.8f);
    GSgfxColAu8* col = _passion2ColorTbl;
    s32 step = (s32)(rate / 0.03846154f);
    f32 oneOver26 = 0.03846154f;
    f32 fadeIn = rate - step * oneOver26;
    fadeIn = fadeIn * 26.0f;
    f32 fadeOut = 1.0f - fadeIn;
    for (s32 i = 0; i < 13; i++) {
        tagSPRITE_WORK* sp = menuPtSpriteWorkGetByItemID(temp_r31, 0x28D, i);
        sp->color = GSgfxColAu8To32(*col);
        if (i < level && temp_r30) {
            u8 alpha;
            if (step < 13) {
                if (i < step) {
                    alpha = 0xFF;
                } else if (i == step) {
                    alpha = rate01ToAlphaFrom50(fadeIn);
                } else {
                    alpha = 0x46;
                }
            } else {
                s32 back = step - 13;
                if (i < back) {
                    alpha = 0x46;
                } else if (i == back) {
                    alpha = rate01ToAlphaFrom50(fadeOut);
                } else {
                    alpha = 0xFF;
                }
            }
            menuPtSpriteWorkSetSw(temp_r31, sp, true);
            M2C_NAMED(((SpriteWorkLayout*)(sp)), u8 *, 0x67, color[3]) = alpha;
        } else {
            menuPtSpriteWorkSetSw(temp_r31, sp, false);
        }
        col++;
    }
    menuPtSpriteWorkSetSw((tagWINDOW_WORK*)(temp_r31), 0x28CU, 0, temp_r30);
    menuPtSpriteWorkSetSw((tagWINDOW_WORK*)(temp_r31), 0x316U, 0, 0U);
    menuPtSpriteWorkSetSw((tagWINDOW_WORK*)(temp_r31), 0x28BU, 0, 0U);
    menuPtSpriteWorkSetSw((tagWINDOW_WORK*)(temp_r31), 0x28AU, 0, ((CMenuReliveHall*)(this))->dancerPositionQuantityWithCatch() != 0);
    menuPtSpriteWorkSetSw((tagWINDOW_WORK*)(temp_r31), 0x4D1U, 0, ((CMenuReliveHall*)(this))->dancerPositionQuantityWithCatch() != 0);
    menuPtSpriteWorkSetSw((tagWINDOW_WORK*)(temp_r31), 0x8EEU, 0, temp_r30);
    menuPtSpriteWorkSetSw((tagWINDOW_WORK*)(temp_r31), 0x4D2U, 0, temp_r30);
    menuPtWindowWorkDraw((tagWINDOW_WORK*)(temp_r31));
}
}

namespace {
void thisExec(CMenuGlobalState& s)
{
    thisNew();
    pMenuReliveHall->main(s);
    thisFree();
}

void thisFree()
{
    if (pMenuReliveHall) {
        GSmemFree(pMenuReliveHall);
        pMenuReliveHall = 0;
    }
}

void thisNew()
{
    pMenuReliveHall = (GC_NEW_NOTE(sizeof(CMenuReliveHall), 528784) new CMenuReliveHall);
}
}

namespace {
void SCircle::draw()
{
    GSprimSetBlendMode(1);
    GSprimDraw2DPixelListC(pos, count, col);
}

void SCircle::allSwOff()
{
    for (int i = 0; i < count; i++) {
        sw[i] = 0;
        col[i].v[RH_A] = 0;
    }
}

void SCircle::setFade(u8 fade)
{
    for (int i = 0; i < count; i++) {
        if (sw[i]) col[i].v[RH_A] = px[i].alpha * fade / 255;
    }
}
struct ArrowSpriteVal {
    s16 l;
    s16 t;
    s16 w;
    s16 h;
    u32 res;
};
void menuPtSpriteDrawArrow(u16 id, u32 color, f32 angle, int yofs)
{
    static f32 xy[8];
    static f32 st[8];
    ArrowSpriteVal* v = (ArrowSpriteVal*)menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(id));
    GStexture* tex = (GStexture*)GSresGetResourceAllGroup(v->res);
    f32 l = v->l;
    f32 t = v->t;
    f32 w = v->w;
    f32 h = v->h;
    GSgfxColAu8 c = {0};
    c.v[0] = color >> 24;
    c.v[1] = color >> 16;
    c.v[2] = color >> 8;
    c.v[3] = color;
    st[0] = st[2] = l / GStextureGetXsize(tex);
    st[4] = st[6] = (l + w) / GStextureGetXsize(tex);
    st[3] = st[5] = t / GStextureGetYsize(tex);
    st[1] = st[7] = (t + h) / GStextureGetYsize(tex);
    f32* p = xy;
    f32 half = w * 0.5f;
    p[0] = 0.0f;
    p[1] = h;
    p[2] = 0.0f;
    p[3] = 0.0f;
    p[4] = w;
    p[5] = 0.0f;
    p[6] = w;
    p[7] = h;
    p[0] = p[0] - half;
    p[2] = p[2] - half;
    p[4] = p[4] - half;
    p[6] = p[6] - half;
    p[1] = p[1] - h;
    p[3] = p[3] - h;
    p[5] = p[5] - h;
    p[7] = p[7] - h;
    p[1] = p[1] + (f32)yofs;
    p[3] = p[3] + (f32)yofs;
    p[5] = p[5] + (f32)yofs;
    p[7] = p[7] + (f32)yofs;
    double na = -angle;
    f32* rp = xy;
    for (int i = 0; i < 4; i++) {
        f32 x = rp[0];
        f32 y = rp[1];
        f32 cs = (f32)cos(na);
        f32 sn1 = (f32)sin(na);
        rp[0] = x * cs + y * sn1;
        f32 sn = (f32)sin(na);
        rp[1] = y * (f32)cos(na) - x * sn;
        rp += 2;
    }
    p[0] = p[0] + 320.0f;
    p[2] = p[2] + 320.0f;
    p[4] = p[4] + 320.0f;
    p[6] = p[6] + 320.0f;
    p[1] = p[1] + 280.0f;
    p[3] = p[3] + 280.0f;
    p[5] = p[5] + 280.0f;
    p[7] = p[7] + 280.0f;
    GSprimSetQuadVertexOrder(1);
    GSprimSetBlendMode(1);
    GSgfxSetupRenderAndSelect((GSgfxVF*)(GSgfxVFBuildTemp(0, 4, 0, 0, 1, 5, 1, 1, 4)));
    GSgfxSetTUnitUserColorArg(0U, 0xAU, 0xFU, 0xFU, 0xFU);
    GSgfxSetTUnitUserColorOp(0U, 0U, 0U, 0U, 1U, 0U);
    GSgfxSetTUnitUserAlphaArg(0U, 7U, 5U, 4U, 7U);
    GSgfxSetTUnitUserAlphaOp(0U, 0U, 0U, 0U, 1U, 0U);
    GSgfxSelectTexture(0U, tex);
    GSgfxSetPrimitiveType(0x80U);
    GSgfxBeginSurface(4U);
    f32* tp = st;
    for (int i = 0; i < 4; i++) {
        GSgfxVertex2f(p[0], p[1]);
        GSgfxColor4u8(c.v[0], c.v[1], c.v[2], c.v[3]);
        GSgfxTexCoord2f(tp[0], tp[1]);
        p += 2;
        tp += 2;
    }
    GSgfxEndSurface();
}

void SCircle::setSwPrime(int from, int to, bool on)
{
    int b = start[to];

    for (int i = start[from]; i < b; i++) {
        sw[i] = on;
        if (on) {
            col[i].v[RH_A] = px[i].alpha;
        } else {
            col[i].v[RH_A] = 0;
        }
    }
}

void SCircle::setSw(f32 from, f32 to, bool on)
{
    int a = degreeRefresh360((s32)(180.0f * from / 3.1415927f));
    int b = degreeRefresh360((s32)(180.0f * to / 3.1415927f));
    if (b == 0) b = 360;
    if (a > b) {
        setSwPrime(a, 360, on);
        setSwPrime(0, b, on);
    } else {
        setSwPrime(a, b, on);
    }
}

void SCircle::drawPixelAll(int x, int y, int angle)
{
    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            drawPixelOne(x + dx, y + dy, angle);
        }
    }
}

void SCircle::drawPixelOne(int x, int y, int angle)
{
    if (!getBitTable(bits, x + y * 0x280)) {
        Px* p = &px[count++];
        p->x = x;
        p->y = y;
        p->alpha = 0xFF;
        p->angle = angle;
        setBitTable(bits, p->x + p->y * 0x280, 1);
    }
}

void SCircle::init(f32 outer_, int radius_, f32 inner_, GSgfxColAu8 color)
{
    memset(this, 0, sizeof(*this));
    outer = outer_;
    radius = radius_;
    inner = inner_;
    bits = (u32*)GSmemAllocClr(0x7D00);
    count = 0;
    int prevX = -1;
    int prevY = -1;
    int prevAngle = -1;
    for (f32 a = 0.0f; a < 6.2831855f; a += 0.008726646f) {
        int x = (int)(90.0f * (f32)sin(a)) + 0x140;
        int y = (int)(90.0f * -(f32)cos(a)) + 0x118;
        int angle = degreeRefresh360((s32)(180.0f * a / 3.1415927f));
        if (angle != prevAngle) start[angle] = count;
        if (x != prevX || y != prevY) {
            drawPixelAll(x, y, angle);
            prevX = x;
            prevY = y;
        }
        prevAngle = angle;
    }
    start[360] = count;
    for (int i = 0; i < count; i++) {
        int dx = px[i].x - 0x140;
        dx = dx > 0 ? dx : -dx;
        int dy = px[i].y;
        dy -= 0x118;
        dy = dy > 0 ? dy : -dy;
        int sq = dx * dx + dy * dy;
        f32 d = (f32)fabs(ptSqrt((f32)sq) - 90.0f);
        if (d <= inner) px[i].alpha = 0xFF;
        else if (d < outer) px[i].alpha = (u8)(255.0f * (outer - d) / (outer - inner));
        else px[i].alpha = 0;
    }
    for (int i = 0; i < count; i++) {
        pos[i][0] = px[i].x;
        pos[i][1] = px[i].y;
    }
    for (int i = 0; i < count; i++) {
        col[i].v[0] = color.v[0];
        col[i].v[1] = color.v[1];
        col[i].v[2] = color.v[2];
        col[i].v[3] = color.v[3];
    }
    memset(sw, 0, 0x2800);
    if (bits) {
        GSmemFree(bits);
        bits = 0;
    }
}
}

namespace {
PocketVec<short> _circleDirToPosition(f32 dir)
{
    PocketVec<short> v;
    v.x = (s16)(GC_FUSED(90.0f, (f32)sin(dir)) + 320.0f);
    v.y = (s16) - (GC_FUSED(90.0f, (f32)cos(dir)) - 280.0f);
    return v;
}

void CMenuReliveHall::drawStarLightOne(s32 colorIdx, f32 x, f32 y, s32 n)
{
    f32 star;
    u32 t = calcAnimationTimeRate0toX(0.32000002f, 10);
    t += n;
    GSgfxColAu8 c = relivehallAisyou2ColorTbl[colorIdx];
    f32 scale = _aisyou2ScaleTbl[colorIdx];
    star = starMasterScaleTbl[t % 10];
    c.v[RH_A] = blurAlphaTbl[n] * alphaB / 255;
    menuPtSpriteDrawAndRollScale(0x140, GSgfxColAu8To32(c), x, y, 0.0f, star * (scale * blurScaleTbl[n]));
}

void CMenuReliveHall::drawDancerHitEffect()
{
    int q = dancerPositionQuantityWithCatch();
    if (q) {
        int n = stage->getDancerQuantity();
        if (n == 0 && q == 1) n = 1;
        for (int i = 0; i < n; i++) {
            f32 x, y;
            f32 t = starTimeFromBorn(x, y, calcStarDir(i, n));
            drawStarHitEffect(x, y, t);
        }
    }
}

void CMenuReliveHall::drawDancerStarLight()
{
    f32 s;
    f32 c;
    int q = dancerPositionQuantityWithCatch();
    if (q) {
        int n = stage->getDancerQuantity();
        if (n == 0 && q == 1) n = 1;
        for (int i = 0; i < n; i++) {
            f32 dir = calcStarDir(i, n);
            for (int j = 0; j < 6; j++) {
                f32 d = -(GC_FUSED(0.06981317f, (f32)j) - dir);
                s = (f32)sin(d);
                c = (f32)cos(d);
                drawStarLightOne(getDirToAisyou(d), GC_FUSED(90.0f, s) + 320.0f, GC_FUSED(90.0f, -c) + 280.0f, j);
            }
        }
    }
}

void CMenuReliveHall::drawStarHitEffect(f32 x, f32 y, f32 t)
{
    if (t < 0.5f) {
        f32 r = t / 0.5f;
        u8 a = (255.0f * (1.0f - r));
        a = a * alphaB / 255;
        menuPtSpriteDrawAndRollScale(0x297, a | ~0xFF, x, y, 0.0f, 0.5f + r);
    }
}

#ifndef __MWERKS__
static
#endif
inline f32 sinf(f32 x) { return (f32)sin(x); }
#ifndef __MWERKS__
static
#endif
inline f32 cosf(f32 x) { return (f32)cos(x); }

f32 CMenuReliveHall::starTimeFromBorn(f32& x, f32& y, f32 dir)
{
    int n = dancerPositionQuantityWithCatch();
    for (int i = 0; i < n; i++) {
        SPokemonView* v = getPokemonViewByClockwizePositionWithCatch(i);
        if (isDirRegionIn(dir, v->dir, getPokemonViewByClockwizePositionWithCatch((i + 1) % n)->dir)) {
            x = GC_FUSED(90.0f, sinf(v->dir)) + 320.0f;
            y = GC_FUSED(90.0f, -cosf(v->dir)) + 280.0f;
            f32 t = dirSubOne(dir, v->dir);
            return 6.0f * (t / 6.2831855f);
        }
    }
    return 0.0f;
}

static inline f32 _starRate(CMenuReliveHall* self) {
    return self->calcAnimationTimeRate0to1(6.0f);
}

f32 CMenuReliveHall::calcStarDir(int i, int n)
{
    return 2.0f * (3.1415927f * ((f32)i / (f32)n)) + 6.2831855f * _starRate(this);
}

void CMenuReliveHall::infoMessageDisplay3Line(u32 msg)
{
    winMsgOpen(2, msg, 1, 0);
    winMsgClose(1);
}

void CMenuReliveHall::infoMessageDisplay(u32 msg)
{
    infoWin.exec(*this, msg, 1);
}
void CMenuReliveHall::stateDirChangeProc() {
    CKeyInfo *temp_r3;
    u8 var_r27;
    f32 var_f30;
    f32 var_f1;
    f32 var_f29;
    f32 temp_f1;
    s32 var_r31;
    s32 var_r26_2;
    int temp_r30;
    s32 temp_r0;
    s32 temp_r0_2;
    u8 var_r26;
    s32 var_r25;

    memset(&stick, 0, 0xCU);
    *RH_NAMED((GCsptr)this, this, s8 **, 0x80F64, cursor) = 0;
    alphaB = 0;
    windowSearchID(0x76);
    var_r31 = RH_NAMED(this, this, CReliveStage **, 0x33C, stage)->hit;
    temp_r30 = var_r31;
    memset(&stick, 0, 0xCU);
    infoWin.setMsgCtrlValue(0x32U, (GCuptr)getCurrentPokemonPointer()->getNicknamePtr());
    infoWin.open(0xD117U, 0U);
    ((CMetaMenu*)((CMetaMenu *) this))->localWindowEntry(0x76, 0, 
        _stateDirChangeProcHook);
    var_r27 = 0;
    do {
        var_r26 = RH_NAMED(this, this, u8 *, 0x621, stick.cur);
        var_f30 = RH_NAMED(this, this, f32 *, 0x624, stick.dir);
        temp_r3 = ((CMetaMenu*)((CMetaMenu *) this))->getKeyInfo();
        temp_r0 = M2C_FIELD(temp_r3, u16 *, 4);
        switch ((s32) temp_r0) {
        case 16:
            menuPtPlaySe(0x45AU);
            var_r27 = 1;
            break;
        case 32:
            RH_NAMED(this, this, CReliveStage **, 0x33C, stage)->hit = temp_r30;
            menuPtPlaySe(0x45BU);
            var_r27 = 1;
            break;
        }
        if (var_r27 == 0) {
            temp_r0_2 = M2C_FIELD(temp_r3, u16 *, 6);
            switch (temp_r0_2) {
            case 1:
                var_f30 = 0.0f;
                var_r26 = 1;
                break;
            case 8:
                var_f30 = 1.5707964f;
                var_r26 = 1;
                break;
            case 2:
                var_f30 = 3.1415927f;
                var_r26 = 1;
                break;
            case 4:
                var_f30 = 4.712389f;
                var_r26 = 1;
                break;
            case 9:
                var_f30 = 0.7853982f;
                var_r26 = 1;
                break;
            case 10:
                var_f30 = 2.3561945f;
                var_r26 = 1;
                break;
            case 6:
                var_f30 = 3.9269907f;
                var_r26 = 1;
                break;
            case 5:
                var_r26 = 1;
                var_f30 = 5.497787f;
                break;
            }
            if (var_r26 != 0) {
                var_f29 = 3.1415927f;
                var_r26_2 = 0;
                var_r25 = 0;
                while (var_r25 < ((CReliveStage*)(RH_NAMED(this, this, CReliveStage **, 0x33C, stage)))->getDancerQuantity()) {
                    PocketVec<short> sp8 = views[var_r25].getPosition();
                    temp_f1 = xyxy2dir(*(const PocketVec<short>*)((PocketVec<short> *) &sp8), *(const PocketVec<short>*)(&circlePosition));
                    if (dirSubHalf(temp_f1, var_f30) < 0.0f) {
                        var_f1 = -dirSubHalf(temp_f1, var_f30);
                    } else {
                        var_f1 = dirSubHalf(temp_f1, var_f30);
                    }
                    if (var_f29 > var_f1) {
                        var_f29 = var_f1;
                        var_r26_2 = var_r25;
                    }
                    var_r25 += 1;
                }
                if (var_r31 != var_r26_2) {
                    menuPtPlaySe(0x459U);
                }
                var_r31 = var_r26_2;
                M2C_FIELD(RH_NAMED(this, this, CReliveStage **, 0x33C, stage), s8 *, 0x3D4) = (s8) var_r26_2;
            }
        }
        updateAll();
    } while (var_r27 == 0);
    ((CMetaMenu*)((CMetaMenu *) this))->localWindowRemove(0x76);
    infoWin.close();
    *RH_NAMED(this, this, s8 **, 0x80F64, cursor) = 1;
    alphaB = 0xFF;
}

void CMenuReliveHall::drawVisitorHitEffect()
{
    if (!dancerPositionQuantityWithCatch() || !getVisitorWithCatch()) {
        return;
    }
    if (stage->hit != -1) {
        f32 r = calcAnimationTimeRate0to1(1.5f);
        drawStarHitEffect(320.0f, 280.0f, 1.5f * r);
    }
}

void CMenuReliveHall::drawVisitorStarLight(s32 colorIdx, SPokemonView* v)
{
    f32 s;
    f32 r = 90.0f * calcAnimationTimeRate0to1(1.5f);
    PocketVec<short> p = v->getPosition();
    f32 dir = xyxy2dir(p, circlePosition);
    int j;
    int k = 0;
    j = 0;
    do {
        f32 d = r - (f32)k;
        if (!(d < 0.0f)) {
            s = (f32)sin(dir);
            drawStarLightOne(colorIdx, d * s + 320.0f, d * -(f32)cos(dir) + 280.0f, j);
        }
        k += 5;
        j++;
    } while (j < 6);
}

void CMenuReliveHall::drawVsitorLine(s32 ci, SPokemonView* v)
{
    if (!views[6].hidden) {
        f32 ox;
        GSgfxColAu8 c = relivehallAisyou2ColorTbl[ci];
        c.v[RH_A] = c.v[RH_A] * alphaA / 255;
        s32 w = _aisyou2LineWidthHalfTable[ci].a;
        f32 px;
        f32 py;
        py = v->getPosition().y;
        px = v->getPosition().x;
        f32 dir = 1.5707964f + xy2dir(px - fcirclePosition.x, py - fcirclePosition.y);
        for (f32 k = 0.0f; k < (f32)w; k += 0.5f) {
            f32 o = k - (f32)(w / 2);
            ox = (f32)sin(dir);
            ox *= o;
            GSgfxColAu8 c1 = c;
            GSgfxColAu8 c2 = c;
            f32 oy = o * -(f32)cos(dir);
            PocketVec<f32> a;
            PocketVec<f32> b;
            a.x = fcirclePosition.x + ox;
            a.y = fcirclePosition.y + oy;
            b.x = px + ox;
            b.y = py + oy;
            reliveLine2D(&c2, &c1, a, b);
        }
    }
}

SPokemonView* CMenuReliveHall::getPokemonViewByClockwizePositionWithCatch(int i)
{
    if (i == 6) return &views[6];
    CMenuPokemonCursor* c;
    u8 catching = 0;
    if (cursor->isCatchPokemon()) {
        c = cursor;
        Pokemon* p = c->pokemon.checkValid() ? &c->pokemon : 0;
        if (!p->isDarkPokemon()) catching = 1;
    }
    if (catching) {
        s32 cur = cursor->index;
        if (cur >= stage->getDancerQuantity()) {

            s32 k = (cursor->index - stage->getDancerQuantity());
            k += 1;
            if (i < k) return &views[i];
            if (i == k) return &views[cursor->index];
            return &views[i - 1];
        }
    }
    return &views[i];
}
}

namespace {
void CMenuReliveHall::setCircleSw()
{
    int q = dancerPositionQuantityWithCatch();
    if (q == 0) {
        for (u32 i = 0; i < 3; i++) circle[i].allSwOff();
        return;
    }
    for (int i = 0; i < q; i++) {
        f32 a, b;
        int col;
        getCircleColorAisyou(a, b, col, i);
        for (int j = 0; j < sizeof(circle) / sizeof(circle[0]); j++) {
            if (j == col) circle[j].setSw(a, b, 1);
            else circle[j].setSw(a, b, 0);
        }
    }
}

void _antZokuseiDraw(SPokemonView&);
void _antDraw(SPokemonView&);
void _antDraw(SPokemonView&, PocketVec<short>);

void CMenuReliveHall::drawStagePokemon()
{
    int n = stage->getDancerQuantity();
    for (int i = 0; i < n; i++) {
        SPokemonView* v = &views[i];
        _antZokuseiDraw(*v);
        _antDraw(*v);
    }
    PocketVec<short> p = circlePosition;
    _antDraw(views[6], p);
}

void _antZokuseiDraw(SPokemonView& v)
{
    if (!v.hidden) {
        s32 x2;
        s32 x = (s32)(GC_FUSED(81.0f, sinf(v.dir2)) + (f32)v.getPosition().x);
        s32 y = (s32)(GC_FUSED(81.0f, -cosf(v.dir2)) + (f32)v.getPosition().y);
        u16 ids[2];
        for (int i = 0; i < 2; i++) {
            ids[i] = zokuseiGetPokemonSpriteID(v.getPokemon()->getPokemonDataPtr(), i);
        }
        if (ids[0] == ids[1]) {
            menuPtSpriteDraw(ids[0], x - 0x24, y - 9);
        } else {
            x2 = x - 0x24;
            menuPtSpriteDraw(ids[0], x2, y - 0x14);
            menuPtSpriteDraw(ids[1], x2, y + 2);
        }
    }
}

void _antDraw(SPokemonView& v)
{
    if (!v.hidden) {
        v.ant.drawAndUpdate(v.getPosition());
    }
}

void _antDraw(SPokemonView& v, PocketVec<short> p)
{
    if (!v.hidden) {
        v.ant.drawAndUpdate(p);
    }
}

void CMenuReliveHall::drawMarkers(bool flag)
{
    PocketVec<short>* pos;
    if (markerPosB[0].x != -1) {
        pos = markerPosB;
    } else {
        pos = markerPosA;
    }
    for (int i = 0; i <= 6; i++) {
        if (!views[i].hidden) {
            u16 id = 0x294;
            u8 on;
            if (i == 6) {
                on = markerOnVisitor;
            } else if (i >= stage->getDancerQuantity()) {
                id = 0x296;
                on = markerOnEmpty;
            } else {
                on = markerOnDancer;
            }
            if (on && pos[i].x != -1) {
                u32 c = on | ~0xFF;
                if (flag) {
                    if (id == 0x294) menuPtSpriteDrawCenterColor(0x2E0, pos[i].x, pos[i].y, c);
                } else {
                    menuPtSpriteDrawCenterColor(id, pos[i].x, pos[i].y, c);
                }
            }
        }
    }
}

void CMenuReliveHall::draw9StageInfo()
{
    relivehallDraw9StageNumber(stageIndex);
    relivehallDraw9StageInfo(stageIndex);
}

void CMenuReliveHall::drawStageCursor()
{
    relivehallDrawStageInfoCursor(stageIndex, getTempo(1), dancerPositionQuantityWithCatch(), getStatusDisplayVisitorGetPointer(), 1);
}
}

namespace {
s32 CMenuReliveHall::actionMenuMain()
{
    static s32 yTbl[7] = { 0, 0, 0, 0x79, 0x64, 0, 0 };
    s32* list = actionList;
    s32 n = list[0];
    return actionMenu((u32*)(list + 1), n, 0x1D7, yTbl[n], 0);
}
void CMenuReliveHall::animationStateUpdate() {
    f32 r;
    anim.update();
    switch (anim.current) {
    case 0:
        if (!anim.time) {
            animationDataReset();
            resetStatusDisplayVisitor();
            cursor->setAnimationOff();
            setCircleSw();
        }
    default:
        return;
    case 1: {
        if (!anim.time) {
            animationDataReset();
        }
        f32 t = anim.time / 0.6f;
        r = 1.0f < t ? 1.0f : t;
        u8 a = (u8)(255.0f * r);
        markerOnVisitor = a;
        markerOnDancer = a;
        markerOnEmpty = a;
        alphaB = a;
        alphaA = a;
        for (u32 i = 0; i < 3; i++) {
            circle[i].setFade(alphaA);
        }
        f32 start;
        if (stageIndex <= 3) {
            start = 5.585054f;
        } else if (stageIndex == 4) {
            start = 0.08726647f;
        } else {
            start = 0.87266463f;
        }
        s32 n = getQuantityMarkerDancerOnPlusDancerEmpty();
        f32 x = 7.5398235f * r;
        if (x < 6.2657323f) {
            f32 e = dirRefresh2PI(start - x);
            for (s32 i = 0; i < n; i++) {
                views[i].hidden = !isDirRegionInReverseClockwise(dirRefresh2PI(views[i].dir), start, e);
            }
            views[6].hidden = 1;
        } else {
            for (s32 i = 0; i < n; i++) {
                views[i].hidden = 0;
            }
        }
        if (r >= 1.0f) {
            anim.change(0);
            return;
        }
        break;
    }
    case 2: {
        if (!anim.time) {
            markerOnEmpty = 0;
            tempoMode = 1;
        }
        r = 1.0f;
        f32 t = anim.time / 0.2f;
        if (t < 1.0f) {
            r = t;
        }
        dancerMoveAnimationAll(r);
        if (r >= 1.0f) {
            anim.change(3);
        }
        tempoRate = r;
        return;
    }
    case 3: {
        s32 v = (s32)((255.0f * anim.time) / 0.1f);
        if (v > 0xFF) {
            v = 0xFF;
        }
        markerOnEmpty = (u8)v;
        if (markerOnEmpty >= 0xFF) {
            anim.change(0);
            return;
        }
        break;
    }
    case 4: {
        s32 v = (s32)((255.0f * anim.time) / 0.1f);
        s32 c;
        if (v > 0xFF) {
            c = 0xFF;
        } else {
            c = v;
        }
        markerOnDancer = (u8)c;
        if (v >= 0xFF) {
            anim.change(0);
            return;
        }
        break;
    }
    case 5: {
        if (!anim.time) {
            markerOnEmpty = -1;
            markerOnDancer = -1;
        }
        s32 v = (s32)((255.0f * anim.time) / 0.1f);
        s32 c;
        if (v > 0xFF) {
            c = 0xFF;
        } else {
            c = v;
        }
        u32 inv = 0xFF - c;
        markerOnDancer = (u8)inv;
        markerOnEmpty = (u8)inv;
        if (v >= 0xFF) {
            anim.change(0);
            return;
        }
        break;
    }
    case 6: {
        if (!anim.time) {
            cursor->mode = 3;
        }
        f32 t = anim.time / 0.1f;
        cursor->t = t < 1.0f ? t : 1.0f;
        setCircleSw();
        if (t >= 1.0f) {
            anim.change(0);
            return;
        }
        break;
    }
    case 7: {
        if (!anim.time) {
            cursor->mode = 1;
            SPokemonView* v = &views[cursor->index];
            v->ant.a14 = 1;
            tempoMode = 1;
        }
        r = 1.0f;
        f32 t = anim.time / 0.25f;
        if (t < 1.0f) {
            r = t;
        }
        cursor->t = t < 1.0f ? t : 1.0f;
        if (t >= 1.0f) {
            anim.change(0);
        }
        tempoRate = r;
        break;
    }
    }
}

int CMenuReliveHall::getPassion(int* out)
{
    return getTempoPassion(out, 1, 0);
}

int CMenuReliveHall::getTempo(bool b)
{
    return getTempoPassion(0, b, 1);
}
int CMenuReliveHall::getTempoPassion(int* p0, bool p1, bool p2) {
    CReliveStage *var_r3_2;
    ModelBank *var_r23;
    s32 var_r3;
    ModelBank *var_r29;
    CReliveStage *temp_r3_4;
    s32 temp_r24;
    u32 var_r22;
    s32 var_r21;
    CReliveStage *temp_r30;
    s32 var_r20;
    GCuptr temp_r3;
    u8 temp_r3_5;
    u8 *temp_r3_2;
    Pokemon *temp_r3_3;
    ModelBank *var_r28;

    int stageIdx = RH_NAMED(this, this, s32 *, 0x338, stageIndex);
    var_r3_2 = CReliveHall::getPointer()->getStage(stageIdx);
    var_r29 = NULL;
    temp_r30 = var_r3_2;
    var_r28 = NULL;
    if (p1 != 0) {
        var_r28 = (ModelBank *)(GSmemAllocClr(0x3D8U));
        var_r29 = (ModelBank *)(GSmemAllocClr(0x3D8U));
        temp_r3 = (GCuptr)(((CReliveStage*)(temp_r30))->getDancerPointer((s32) M2C_FIELD(temp_r30, s8 *, 0x3D4)));
        var_r22 = 0;
        if (temp_r3 != 0) {
            var_r22 = ((Pokemon*)((Pokemon *) temp_r3))->getPokemonDataId();
        }
        ((CReliveStage*)((CReliveStage *) var_r29))->init();
        temp_r3_2 = (unsigned char *)(((CMenuReliveHall*)(this))->getStatusDisplayVisitorGetPointer());
        if (temp_r3_2 != NULL) {
            memcpy((void*)(((u8*)(var_r29) + 0x310)), (const void*)(temp_r3_2), 0xC4U);
        }
        var_r21 = 0;
        temp_r24 = ((CMenuReliveHall*)(this))->dancerPositionQuantityWithCatch();
        var_r23 = var_r29;
        var_r20 = 0;
        while (var_r20 < temp_r24) {
            temp_r3_3 = ((SPokemonView*)(((CMenuReliveHall*)(this))->getPokemonViewByClockwizePositionWithCatch(var_r20)))->getPokemonWithPickupOverride();
            memcpy((void*)(var_r23), (const void*)(temp_r3_3), 0xC4U);
            if (var_r22 == ((Pokemon*)(temp_r3_3))->getPokemonDataId()) {
                var_r21 = var_r20;
            }
            var_r23 += 0xC4;
            var_r20 += 1;
        }
        M2C_FIELD(var_r29, s8 *, 0x3D4) = (s8) var_r21;
        memcpy((void*)(var_r28), (const void*)(temp_r30), 0xC4U);
#ifdef __MWERKS__
        memcpy((void*)(((u8*)(var_r28) + 0xC4)), (const void*)(((u8*)((s32)temp_r30) + 0xC4)), 0xC4U);
#else
        memcpy((void*)(((u8*)(var_r28) + 0xC4)), (const void*)(((u8*)(temp_r30) + 0xC4)), 0xC4U);
#endif
        memcpy((void*)(((u8*)(var_r28) + 0x188)), (const void*)(((u8*)(temp_r30) + 0x188)), 0xC4U);
        memcpy((void*)(((u8*)(var_r28) + 0x24C)), (const void*)(((u8*)(temp_r30) + 0x24C)), 0xC4U);
        memcpy((void*)(((u8*)(var_r28) + 0x310)), (const void*)(((u8*)(temp_r30) + 0x310)), 0xC4U);
        M2C_FIELD(var_r28, s8 *, 0x3D4) = M2C_FIELD(temp_r30, s8 *, 0x3D4);
        memcpy((void*)(temp_r30), (const void*)(var_r29), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0xC4)), (const void*)(((u8*)(var_r29) + 0xC4)), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0x188)), (const void*)(((u8*)(var_r29) + 0x188)), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0x24C)), (const void*)(((u8*)(var_r29) + 0x24C)), 0xC4U);
        var_r3_2 = (CReliveStage *)(memcpy((void*)(((u8*)(temp_r30) + 0x310)), (const void*)(((u8*)(var_r29) + 0x310)), 0xC4U));
        M2C_FIELD(temp_r30, s8 *, 0x3D4) = M2C_FIELD(var_r29, s8 *, 0x3D4);
    }
    temp_r3_4 = CReliveHall::getPointer()->getStage(stageIdx);
    if (p2 != 0) {
        var_r3 = ((CReliveStage*)(temp_r3_4))->getTempo();
    } else {
        var_r3 = ((CReliveStage*)(temp_r3_4))->getPassion();
    }
    if (p0 != NULL) {
        *p0 = 0;
        temp_r3_5 = ((CReliveStage*)(temp_r30))->isBonusGet();
        if (temp_r3_5 != 0) {
            *p0 = ((CReliveHall*)(((CReliveHall*)((CReliveHall *) temp_r3_5))->getPointer()))->getReliveGiveStageQuantity();
        }
    }
    if (var_r29 != NULL) {
        memcpy((void*)(temp_r30), (const void*)(var_r28), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0xC4)), (const void*)(((u8*)(var_r28) + 0xC4)), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0x188)), (const void*)(((u8*)(var_r28) + 0x188)), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0x24C)), (const void*)(((u8*)(var_r28) + 0x24C)), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0x310)), (const void*)(((u8*)(var_r28) + 0x310)), 0xC4U);
        M2C_FIELD(temp_r30, u8 *, 0x3D4) = (u8) M2C_FIELD(var_r28, u8 *, 0x3D4);
        if (var_r29 != NULL) {
            GSmemFree((void*)(var_r29));
        }
        if (var_r28 != NULL) {
            GSmemFree((void*)(var_r28));
        }
    }
    return var_r3;
}

int CMenuReliveHall::getDirToAisyou(f32 dir)
{
    int n = dancerPositionQuantityWithCatch();
    for (int i = 0; i < n; i++) {
        SPokemonView* a = getPokemonViewByClockwizePositionWithCatch(i);
        SPokemonView* b = getPokemonViewByClockwizePositionWithCatch((i + 1) % n);
        if (isDirRegionIn(dir, a->dir, b->dir)) {
            return pokemonToAisyou(a->getPokemonWithPickupOverride(), (Pokemon*)(b->getPokemonWithPickupOverride()));
        }
    }
    return -1;
}

GSgfxColAu8 CMenuReliveHall::getCircleColorAisyou(f32& a, f32& b, int& color, int idx)
{
    int n = dancerPositionQuantityWithCatch();
    SPokemonView* va = getPokemonViewByClockwizePositionWithCatch(idx);
    SPokemonView* vb = getPokemonViewByClockwizePositionWithCatch((idx + 1) % n);
    color = pokemonToAisyou(va->getPokemonWithPickupOverride(), vb->getPokemonWithPickupOverride());
    GSgfxColAu8 c = relivehallAisyou2ColorTbl[color];
    a = va->dir;
    b = vb->dir;
    return c;
}

GSgfxColAu8 CMenuReliveHall::positionToAisyouColor(int i, int j)
{
    Pokemon* a = getPokemonFromPositionWithCatch(i);
    Pokemon* b = getPokemonFromPositionWithCatch(j);
    return pokemonToAisyouColor(a, b);
}

GSgfxColAu8 CMenuReliveHall::pokemonToAisyouColor(Pokemon* a, Pokemon* b)
{
    int r = reliveHallPokemonToAisyou(a, b);
    if (r == -1) return GSgfxColAu8_Black;
    return relivehallAisyou2ColorTbl[r];
}

int CMenuReliveHall::pokemonToAisyou(Pokemon* a, Pokemon* b)
{
    int r = reliveHallPokemonToAisyou(a, b);
    if (r == -1) r = 0;
    return r;
}

int CMenuReliveHall::dancerPositionQuantityWithCatch()
{
    CMenuPokemonCursor* c;
    Pokemon* p;
    int idx;
    u8 in;
    int n = stage->getDancerQuantity();
    u8 catching = 0;
    if (cursor->isCatchPokemon()) {
        c = cursor;
        p = c->pokemon.checkValid() ? &c->pokemon : 0;
        if (!p->isDarkPokemon()) catching = 1;
    }
    if (catching) {
        CMenuPokemonCursor* c = cursor;
        in = 0;
        idx = c->index;
        if (stage->getDancerQuantity() <= idx && cursor->index <= 5) in = 1;
        if (in) n += 1;
    }
    return n;
}

Pokemon* CMenuReliveHall::getVisitorWithCatch()
{
    return getPokemonFromPositionWithCatch(6);
}

Pokemon* CMenuReliveHall::getPokemonFromPositionWithCatch(int i)
{
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor* c = cursor;
        if (i == c->index) {
            if (c->pokemon.checkValid()) return &c->pokemon;
            return 0;
        }
    }
    if (i < stage->getDancerQuantity()) return stage->getDancerPointer(i);
    if (i == 6) return stage->getVisitorPointer();
    return 0;
}
}

namespace {
u8 rate01ToAlphaFrom50(f32);
void _cbMenuPokemonStatus(Pokemon*, MENU_POKEMON_CB_TYPE, s32);

void CMenuReliveHall::stateDirChangeWinDraw(s32 win)
{
    menuPtWindowWorkDraw(win);
    u32 a;
    int hit = stage->hit;
    a = rate01ToAlphaFrom50((f32)sin(3.1415927f * calcAnimationTimeRate0to1(0.5f))) | ~0xFF;
    for (int i = 0; i < stage->getDancerQuantity(); i++) {
        PocketVec<short> p = views[i].getPosition();
        f32 dir = xyxy2dir(p, circlePosition);
        if (i == hit) menuPtSpriteDrawArrow(0x13F, a, dir, 0);
        menuPtSpriteDrawArrow(0x183, GSgfxColAu8To32(positionToAisyouColor(6, i)), dir, -0xC);
    }
}

void _stateDirChangeProcHook(CMetaMenu* m, s32 win)
{
    ((CMenuReliveHall*)m)->stateDirChangeWinDraw(win);
}

void CMenuReliveHall::actionStatus()
{
    systemFadeOutSetAndWait(-1.0f);
    unloadDatas();
    GSfsysReadWait(0x66F);
    Pokemon* p = getCurrentPokemonPointer();
    savedIndex = cursor->index;
    menuPokemonStatusOpenFromPcBox(p, _cbMenuPokemonStatus, 0);
    cursor->setPositionIndex(savedIndex);
    GSfsysFree(0x66F);
    GSresFreeGroup(0x66F);
    loadDatas();
    systemFadeInKick();
}

void _cbMenuPokemonStatus(Pokemon* p, MENU_POKEMON_CB_TYPE t, s32 n)
{
    pMenuReliveHall->actionStatusCallback(p, t);
}

Pokemon* CMenuReliveHall::actionStatusCallback(Pokemon* p, MENU_POKEMON_CB_TYPE type)
{
    if (cursor->isCatchPokemon()) return p;
    int n = stage->getDancerQuantity();
    if (type == 1) {
        if (savedIndex == 6) {
            if (n != 0) savedIndex = n - 1;
        } else if (savedIndex > 0) {
            savedIndex = savedIndex - 1;
        }
    } else if (type == 2) {
        if (savedIndex < n) {
            savedIndex = savedIndex + 1;
            if (savedIndex >= n) {
                if (stage->getVisitorPointer()) savedIndex = 6;
                else savedIndex = n - 1;
            }
        }
    }
    int idx = savedIndex;
    if (idx < n) p = stage->getDancerPointer(idx);
    else if (idx == 6) p = stage->getVisitorPointer();
    return p;
}
}

namespace {
int CMenuReliveHall::cursorMoveDirSearch(PocketVec<short>* tbl, int dir, int range)
{
    int curIdx = cursor->index;
    int found = -1;
    f32 best = 1000.0f;
    PocketVec<short> cur = tbl[curIdx];
    PocketVec<short> pos[11];
    memcpy(pos, tbl, 36);
    memcpy(&pos[9], _cursorPositionTblAddPc, 8);
    for (int i = 0; i < 11; i++) {
        if (curIdx == 7 && i >= 9) break;
        if (i != cursor->index && pos[i].x != -1) {
            int deg = xyxy2dirDegree(pos[i], cur);
            int d = degreeSubHalf(dir, deg);
            d = (d > 0) ? d : -d;
            if (d <= range) {
                f32 dist = xyxy2distance(pos[i], cur);
                if (best > dist) {
                    best = dist;
                    found = i;
                }
            }
        }
    }
    if (found >= 9) found = 7;
    return found;
}

void CMenuReliveHall::cursorMoveDir(int dir)
{
    int r;
    int range = 0xF;
    do {
        r = cursorMoveDirSearch(markerPosA, dir, range + 1);
        if (r != -1) break;
        range += 0xF;
    } while (range <= 0x3C);
    if (r != -1) {
        menuPtPlaySe(0x459);
        cursor->setPositionIndex(r);
        anim.change(6);
    }
}

bool CMenuReliveHall::animationProcessButtonInterrupt()
{
    if (anim.current != 0) {
        anim.change(0);
        animationStateUpdate();
    }
    return 0;
}

bool isDirRegionInReverseClockwise(f32 a, f32 b, f32 c)
{
    bool r;
    if (c > b) {
        r = 0;
        if (c <= a || a <= b) r = 1;
        return r;
    }
    r = 0;
    if (c <= a && a <= b) r = 1;
    return r;
}

int CMenuReliveHall::getQuantityMarkerDancerEmpty()
{
    static s32 tbl[5] = { 1, 1, 2, 3, 0 };
    if (cursor->isCatchPokemon() == 0) return 0;
    return tbl[stage->getDancerQuantity()];
}

int CMenuReliveHall::getQuantityMarkerDancerOnPlusDancerEmpty()
{
    int n = stage->getDancerQuantity();
    return n + getQuantityMarkerDancerEmpty();
}
static inline u8 catchIsDark(CMenuReliveHall* m) {
    CMenuPokemonCursor* c;
    Pokemon* p;
    u8 flag = 0;
    if (m->cursor->isCatchPokemon()) {
        c = m->cursor;
        p = c->pokemon.checkValid() ? &c->pokemon : 0;
        if (p->isDarkPokemon()) flag = 1;
    }
    return flag;
}

static inline u8 catchIsLive(CMenuReliveHall* m) {
    CMenuPokemonCursor* c;
    Pokemon* p;
    u8 flag = 0;
    if (m->cursor->isCatchPokemon()) {
        c = m->cursor;
        p = c->pokemon.checkValid() ? &c->pokemon : 0;
        if (!p->isDarkPokemon()) flag = 1;
    }
    return flag;
}

void CMenuReliveHall::cursorPositionDecideAtStageChange(int old) {
    CMenuPokemonCursor* c;
    Pokemon* p;
    s32 pos;
    s32 quantity;
    u8 flag;
    if (old == -1 && pState->kind == 1) {
        pos = 7;
    } else {
        quantity = -1;
        if (old != -1) {
            quantity = CReliveHall::getPointer()->getStage(old)->getDancerQuantity();
        }
        int idx = cursor->index;
        pos = idx;
        if (idx == 6) {
            if (stage->getVisitorPointer() == 0) {
                if (!catchIsDark(this)) pos = -1;
            }
        } else {
            flag = 0;
            if (idx >= 0 && idx <= 5) flag = 1;
            if (flag != 0 && quantity != stage->getDancerQuantity()) pos = -1;
        }
        if (pos == -1) {
            flag = 0;
            if (cursor->isCatchPokemon()) {
                c = cursor;
                p = c->pokemon.checkValid() ? &c->pokemon : 0;
                if (!p->isDarkPokemon()) flag = 1;
            }
            if (!(flag != 0 || stage->getVisitorPointer() == 0) || catchIsDark(this)) {
                pos = 6;
            } else if (!(catchIsDark(this) || stage->getDancerQuantity() == 0) || catchIsLive(this)) {
                pos = 0;
            } else {
                pos = 7;
            }
        }
    }
    cursor->setPositionIndex(pos);
}

void CMenuReliveHall::setStage(int idx)
{
    int old = stageIndex;
    stageIndex = idx;
    stage = CReliveHall::getPointer()->getStage(stageIndex);
    GSmodelSetTexAnimIndex(modelB, stageIndex);
    GSmodelSetTexAnimType(modelB, 0);
    GSmodelStartTexAnimation(modelB);
    cursorPositionDecideAtStageChange(old);
    resetViewAll();
    anim.change(1);
}

void CMenuReliveHall::moveStage(int d)
{
    menuPtPlaySe(0x45F);
    int n = stageIndex + d;
    if (n < 0) n = 8;
    else if (n >= 9) n = 0;
    setStage(n);
}

Pokemon* CMenuReliveHall::getCurrentPokemonPointer()
{
    Pokemon* r = 0;
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor* c = cursor;
        r = c->pokemon.checkValid() ? &c->pokemon : 0;
    } else {
        u8 in = 0;
        int idx = cursor->index;
        if (idx >= 0 && idx <= 5) in = 1;
        if (in) r = stage->getDancerPointer(idx);
        else if (idx == 6) r = stage->getVisitorPointer();
    }
    return r;
}

Pokemon* CMenuReliveHall::getStatusDisplayVisitorGetPointer()
{
    if (cursor->index == 6 && statusSet) {
        if (pokemonCheckValid((Pokemon*)statusVisitor)) return (Pokemon*)statusVisitor;
        return 0;
    }
    return getVisitorWithCatch();
}

void CMenuReliveHall::resetStatusDisplayVisitor()
{
    pokemonInit((GCuptr)statusVisitor);
    statusSet = 0;
}
void CMenuReliveHall::aButtomAction()
{
    CMenuPokemonCursor* c;
    u8* tbl = (u8*)relivehallAisyou2ColorTbl;
#ifdef __MWERKS__
    memset(&actionList, 0, 0xC);
#else
    memset(&actionList, 0, (u8*)(&actionCancel + 1) - (u8*)&actionList);
#endif
    actionSel = -1;
    actionCancel = -1;
    switch (cursor->index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5: {
        u8 catching = 0;
        if (cursor->isCatchPokemon()) {
            CMenuPokemonCursor* c = cursor;
            Pokemon* p = c->pokemon.checkValid() ? &c->pokemon : 0;
            if (!p->isDarkPokemon()) catching = 1;
        }
        if (catching) {
            int idx = cursor->index;
            if (idx < stage->getDancerQuantity()) {
                if (cursor->holding) actionChange();
                else actionList = RH_ACTION_LIST(tbl, 0x238);
            } else if (cursor->holding) {
                actionPut();
            } else {
                actionList = RH_ACTION_LIST(tbl, 0x268);
            }
        } else {
            int idx = cursor->index;
            if (idx < stage->getDancerQuantity()) {
                if (cursor->holding) actionPickup();
                else actionList = RH_ACTION_LIST(tbl, 0x298);
            }
        }
        break;
    }
    case 6: {
        int two = stage->getDancerQuantity() >= 2;
        u8 dark = 0;
        if (cursor->isCatchPokemon()) {
            c = cursor;
            Pokemon* p = c->pokemon.checkValid() ? &c->pokemon : 0;
            if (p->isDarkPokemon()) dark = 1;
        }
        if (dark) {
            if (RH_NAMED(this, this, u32 *, 0x530, views[6].ant.a0) != 0) {
                if (cursor->holding) actionChange();
                else actionList = RH_ACTION_LIST2(two, tbl, 0x220, 0x238);
            } else if (cursor->holding) {
                actionPut();
            } else {
                actionList = RH_ACTION_LIST2(two, tbl, 0x250, 0x268);
            }
        } else if (RH_NAMED(this, this, u32 *, 0x530, views[6].ant.a0) != 0) {
            if (cursor->holding) actionPickup();
            else actionList = RH_ACTION_LIST2(two, tbl, 0x280, 0x298);
        }
        break;
    }
    case 7:
        state.change(6);
        break;
    case 8:
        state.change(8);
        break;
    }
    if (actionList != 0) {
        state.change(3);
    }
}
static inline void updateDarkLugia()
{
    DarkPokemon* dp = darkPokemonGetDarkPokemon(0x49);
    if (CReliveHall::getPointer()->isReliveReadyDarkLugiaExist()) {
        dp->setDarkPointDirect(0);
    } else if (dp->getStatus() == 4) {
        dp->setDarkPointDirect(0);
    } else {
        dp->setDarkPointDirect(dp->getInitDarkPointDirect());
    }
}

void CMenuReliveHall::stateMainProc()
{
    memset(&stick, 0, sizeof(CStick));
    bool done = false;
    while (!done) {
        CKeyInfo* key = getKeyInfo();
        bool lugia = CReliveHall::getPointer()->isReliveReadyDarkLugiaExist();
        bool pressed = (key->trg | key->rep) != 0;
        if ((pressed || stick.edge) && animationProcessButtonInterrupt()) {
            return;
        }
        if (stick.edge) {
            cursorMoveDir((s32)((180.0f * stick.dir) / 3.1415927f));
        } else if (!stick.cur && pressed) {
            bool other = false;
            switch (key->rep) {
            case 0x1:
                cursorMoveDir(0);
                break;
            case 0x8:
                cursorMoveDir(0x5A);
                break;
            case 0x2:
                cursorMoveDir(0xB4);
                break;
            case 0x4:
                cursorMoveDir(0x10E);
                break;
            case 0x9:
                cursorMoveDir(0x2D);
                break;
            case 0xA:
                cursorMoveDir(0x87);
                break;
            case 0x6:
                cursorMoveDir(0xE1);
                break;
            case 0x5:
                cursorMoveDir(0x13B);
                break;
            case 0x200:
                moveStage(-1);
                break;
            case 0x400:
                moveStage(1);
                break;
            default:
                other = true;
                break;
            }
            if (other) {
                switch (key->trg) {
                case 0x10:
                    if (!cursor->isCatchPokemon()) {
                        menuPtPlaySe(0x45A);
                    }
                    aButtomAction();
                    done = true;
                    break;
                case 0x20:
                    if (!cursor->isCatchPokemon()) {
                        menuPtPlaySe(0x45B);
                    }
                    state.change(8);
                    done = true;
                    break;
                case 0x40:
                case 0x80:
                    cursor->holding = cursor->holding == 0;
                    break;
                case 0x100:
                    menuPtPlaySe(0x45A);
                    state.change(6);
                    break;
                }
            }
        }
        updateAll();
        if (!lugia && CReliveHall::getPointer()->isReliveReadyDarkLugiaExist()) {
            infoMessageDisplay(0xD152);
        }
        updateDarkLugia();
        if (state.next != -1) {
            return;
        }
    }
}
void CMenuReliveHall::loop()
{
    while (true) {
        state.update();
        switch (state.current) {
        case 0:
            break;
        case 1:
            state.change(2);
            lbl_804EA7F0 = pState->kind == 3;
            break;
        case 2:
            stateMainProc();
            break;
        case 3: {
            infoWin.setMsgCtrlValue(0x32, (GCuptr)getCurrentPokemonPointer()->getNicknamePtr());
            infoWin.open(0xD110, 0);
            s32 sel = actionMenuMain();
            infoWin.close();
            bool lugia = CReliveHall::getPointer()->isReliveReadyDarkLugiaExist();
            actionDecide(actionList[sel + 1]);
            if (!lugia && CReliveHall::getPointer()->isReliveReadyDarkLugiaExist()) {
                infoMessageDisplay(0xD152);
            }
            updateDarkLugia();
            break;
        }
        case 4:
            actionStatus();
            state.change(2);
            break;
        case 5:
            stateDirChangeProc();
            state.change(2);
            break;
        case 6: {
            alphaFadeOutAndWait();
            CMenuGlobalState* g = pState;
            g->kind = g->next;
            g->next = 1;
            return;
        }
        case 7:
            menuPtPlaySe(0x13);
            infoMessageDisplay(0xD11B);
            state.change(2);
            break;
        case 8: {
            if (pState->tutorialFinished) {
                state.change(9);
                break;
            }
            if (cursor->isCatchPokemon()) {
                state.change(7);
                break;
            }
            u32 items[2] = { 0x426A, 0x426B };
            infoWin.open(pState->kind == 3 ? 0xD15B : 0xD124, 0);
            s32 r = actionMenu(items, 2, 0x1FB, 0x8C, 0);
            infoWin.close();
            if (r == 0) {
                state.change(2);
            } else {
                state.change(9);
            }
            break;
        }
        case 9: {
            s32 next = 0;
            if (pState->f0 != 3 && CReliveHall::getPointer()->isReliveReadyPokemonExist()) {
                s32 f0 = pState->f0;
                if (PCBOX::getPointer()->isPokemonFull()) {
                    infoMessageDisplay3Line(0xD12F);
                    if (f0 == 2) {
                        next = 4;
                    }
                } else {
                    infoMessageDisplay3Line(0xD0FD);
                }
            }
            CMenuGlobalState* g = pState;
            g->kind = g->next;
            g->next = next;
            systemFadeOutSetAndWait(-1.0f);
            return;
        }
        }
    }
}

void CMenuReliveHall::setStatusDisplayVisitor(Pokemon* p)
{
    statusSet = 1;
    if (p == 0) {
        pokemonInit((GCuptr)statusVisitor);
        return;
    }
    memcpy(statusVisitor, p, 0xC4);
}

void CMenuReliveHall::unloadDatas()
{
    localWindowDeleteAll();
    GSmodelSetVisibility(modelA, 0);
    GSmodelSetVisibility(modelB, 0);
    scriptModelClose(scriptA);
    scriptModelClose(scriptB);
}

void CMenuReliveHall::loadDatas()
{
    s32 g = floorGetCurrentGroupID();
    scriptA = scriptModelOpen(0x18041000);
    modelA = GC_ADDR32(GSresGetResource(g, scriptA));
    GSmodelStopTexAnimation(modelA);
    scriptB = scriptModelOpen(0x18041001);
    modelB = GC_ADDR32(GSresGetResource(g, scriptB));
    GSmodelStopTexAnimation(modelB);
    cameraPlayAnime(g, 0x18031800, 1, 0.0f);
    cameraSetType(4);
    GSmodelSetVisibility(modelA, 1);
    GSmodelSetVisibility(modelB, 1);
    localWindowCreateAll();
}

PocketVec<short> SPokemonView::getPosition()
{
    return _circleDirToPosition(dir);
}

Pokemon* SPokemonView::getPokemonWithPickupOverride()
{
    if (pMenuReliveHall->cursor->isCatchPokemon()) {
        CMenuPokemonCursor* c = pMenuReliveHall->cursor;
        if (c->index == ((u8*)this - (u8*)pMenuReliveHall->views) / 0x50) {
            if (c->pokemon.checkValid()) return &c->pokemon;
            return 0;
        }
    }
    return getPokemon();
}

Pokemon* SPokemonView::getPokemon()
{
    int i = ((u8*)this - (u8*)pMenuReliveHall->views) / 0x50;
    if (i < pMenuReliveHall->stage->getDancerQuantity()) return pMenuReliveHall->stage->getDancerPointer(i);
    if (i == 6) return pMenuReliveHall->stage->getVisitorPointer();
    return 0;
}

void _menuDrawReliveMeter(Pokemon* p, s32 x, s32 y, s32 w, s32 h, u8 a, GSgfxLayerID layer, s32 i)
{
    menuDrawReliveMeter3(p, x, y, w, h, a, layer);
}

u8 rate01ToAlphaFrom50(f32 r)
{
    return (u8)(GC_FUSED(205.0f, r) + 50.0f);
}
}

namespace {
void CStick::update()
{
    prev = cur;
    s8 ly = GSinputGetLeftStickYData(1, 0);
    s8 lx = GSinputGetLeftStickXData(1, 0);
    s8 ry = GSinputGetRightStickYData(1, 0);
    s8 rx = GSinputGetRightStickXData(1, 0);
    dir = 0.0f;
    if ((lx < 0 ? -lx : lx) > 0x20 || (ly < 0 ? -ly : ly) > 0x20) {
        dir = xy2dir((f32)lx, (f32)ly);
        cur = 1;
    } else if ((rx < 0 ? -rx : rx) > 0x16 || (ry < 0 ? -ry : ry) > 0x16) {
        dir = xy2dir((f32)rx, (f32)ry);
        cur = 1;
    } else {
        cur = 0;
    }
    u8 wait = 0;
    edge = 0;
    if (cur != 0 && prev == 0) {
        edge = 1;
    } else if (cur != 0 && cur == prev) {
        if (count >= 0xC) edge = cur;
        else wait = 1;
    }
    if (wait) {
        count = count + 1;
        return;
    }
    count = 0;
}
}

namespace {
void CMenuReliveHall::editAfterDp0VisitorCheck()
{
    Pokemon* v = stage->getVisitorPointer();
    if (v && !v->getDarkPoint() && stage->getDancerQuantity() == 0) {
        msgctrlSetValue(0x32, (GCuptr)v->getNicknamePtr());
        infoMessageDisplay3Line(0xD15D);
    }
}

void CMenuReliveHall::actionDecide(u32 id)
{
    switch (id) {
    case 0xD111:
        actionChange();
        break;
    case 0xD112:
        state.change(5);
        break;
    case 0xD113:
        state.change(4);
        break;
    case 0xD115:
        actionPut();
        break;
    case 0xD116:
        actionPickup();
        break;
    }
    if (state.next == -1) {
        state.change(2);
    }
}

void CMenuReliveHall::dancerMoveAnimationOne(SPokemonView& v, f32 t)
{
    f32 s = dirSubHalf(v.dirTo, v.dirFrom);
    f32 p = t * s;
    v.dir = v.dirFrom + p;
    f32 d = dirSubHalf(v.dir2From, v.dir2To);
    f32 a;
    if (d < 0.0f) a = -d;
    else a = d;
    if (a > 1.5707964f) {
        v.dir2 = v.dir2To;
        return;
    }
    f32 q = t * d;
    v.dir2 = v.dir2To + q;
}

void CMenuReliveHall::dancerMoveAnimationAll(f32 t)
{
    int n = stage->getDancerQuantity();
    for (int i = 0; i < n; i++) {
        dancerMoveAnimationOne(views[i], t);
    }
    CMenuPokemonCursor* c = cursor;
    n = c->index;
    u8 in = 0;
    if (stage->getDancerQuantity() <= n && cursor->index <= 5) in = 1;
    if (in) dancerMoveAnimationOne(views[cursor->index], t);
    setCircleSw();
    makeCursorPositionTbl(markerPosA);
}
void CMenuReliveHall::dancerMoveAnimationKick(f32* p0, f32* p1, bool p2, f32 p3) {
    s32 n = ((CReliveStage*)(RH_NAMED(this, this, CReliveStage **, 0x33C, stage)))->getDancerQuantity();
    s32 i;
    for (i = 0; i < n; i++) {
        SPokemonView* v = &views[i];
        v->dirTo = v->dir;
        v->dir = v->dirFrom = p0[i];
        v->dir2From = v->dir2;
        v->dir2 = v->dir2To = p1[i];
    }
    if (p2 != 0) {
        SPokemonView* v = &views[RH_NAMED(this, this, CMenuPokemonCursor **, 0x80F64, cursor)->index];
        v->dirTo = v->dir;
        v->dir = v->dirFrom = p3;
        v->dir2From = v->dir2 = v->dir2To = v->dir2;
    }
    ((CMenuReliveHall*)(this))->setCircleSw();
    RH_NAMED(this, this, s32 *, 0x81090, anim.next) = 2;
    memset(RH_PTR((void*)((u8*)this + 0x810A4), (void*)anim.work), 0, 0x40U);
    ((CMenuReliveHall*)(this))->makeCursorPositionTbl(RH_PTR((PocketVec<short>*)((u8*)this + 0x80F68), (PocketVec<short>*)markerPosA));
}

}

namespace {
void CMenuReliveHall::resetViewAll() {
    memset(views, 0, sizeof(views));
    Pokemon* visitor = stage->getVisitorPointer();
    memset(&views[6].ant, 0, sizeof(CAnt));
    if (visitor != 0) {
        views[6].ant.initByPokemonAndSetColorAnimationInReliveHallVisitor(visitor);
        views[6].ant.setAnimation(0);
    }
    s32 n = stage->getDancerQuantity();
    s32 i;
    for (i = 0; i < n; i++) {
        Pokemon* p = stage->getDancerPointer(i);
        SPokemonView* v = &views[i];
        v->dir = v->dirTo = v->dirFrom = _markerDancerOnDirTbl[n][i];
        v->dir2 = v->dir2From = v->dir2To = _zokuseiMarkDancerOnDirTbl[n][i];
        v->pad0 = 0;
        v->ant.initByPokemon(p);
        v->ant.setAnimation(1);
    }
    s32 m = getQuantityMarkerDancerEmpty();
    if (m != 0) {
        s32 j;
        for (j = 0; j < m; j++) {
            SPokemonView* v = &views[i];
            v->dir = _markerDancerEmptyDirTbl[n][j];
            v->pad0 = 1;
            v->dirTo = v->dir;
            v->dirFrom = v->dir;
            i++;
        }
    }
    setCircleSw();
    makeCursorPositionTbl(RH_PTR((PocketVec<short>*)((u8*)this + 0x80F68), (PocketVec<short>*)markerPosA));
}
}

namespace {
void CMenuReliveHall::makeCursorPositionTbl(PocketVec<short>* out)
{
    memcpy(out, _cursorPositionTblDefault, 0x24);
    u8 dark = 0;
    CMenuPokemonCursor* c;
    if (cursor->isCatchPokemon()) {
        c = cursor;
        Pokemon* p = c->pokemon.checkValid() ? &c->pokemon : 0;
        if (p->isDarkPokemon()) dark = 1;
    }
    if (dark == 0) {
        for (int i = 0; i < getQuantityMarkerDancerOnPlusDancerEmpty(); i++) {
            PocketVec<short>& o = out[i];
            PocketVec<short> p = views[i].getPosition();
            o.x = p.x;
            o.y = p.y;
        }
    }
    u8 live = 0;
    if (cursor->isCatchPokemon()) {
        c = cursor;
        Pokemon* p = c->pokemon.checkValid() ? &c->pokemon : 0;
        if (!p->isDarkPokemon()) live = 1;
    }
    if (live || (cursor->isCatchPokemon() == 0 && stage->getVisitorPointer() == 0)) {
        out[6].x = -1;
        out[6].y = -1;
    }
}
}

namespace {
inline void CMenuReliveHall::markerClear()
{
    PocketVec<short>* p = markerPosB;
    for (int i = 0; i < 9; i++, p++) {
        p->x = -1;
        p->y = -1;
    }
}

void CMenuReliveHall::main(CMenuGlobalState& gs)
{
    PocketVec<short> sel = gs.cursor.table[gs.cursor.index];
    init(gs);
    if (pState->kind == 1) {
        alphaFadeInKick();
        anim.change(6);
        cursor->setPosition(sel);
    } else {
        systemFadeInKick();
    }
    state.change(1);
    loop();
    unloadDatas();
    cursor->setPositionTableDummy();
    relivehallSetLastViewStage(stageIndex);
    CAnt::allRequestCancel();
    CAnt::waitEndOfReading();
}

void CMenuReliveHall::init(CMenuGlobalState& st)
{
    time = 0;
    state.init();
    fadeTime = 0;
    fadeState = 0;
    memset(windowIds, 0, 0x100);
    memset(windowFuncs, 0, sizeof(windowFuncs));
    windowTable = CMetaMenu::defautlLocalWindowOpenTable;
    if (pcReliveHallSoundTbl != 0) {
        memcpy(&pad8, pcReliveHallSoundTbl, 0x14);
    }
    tutorialMode = 0;
    updated = 0;
    cachedInput = 0;
    memset(&keyInfo, 0, 0x1A);
    repeat = 0;
    lastOn = 0;
    stageIndex = -1;
    stage = 0;
#ifdef __MWERKS__
    memset(views, 0, 0x2D0);
#else
    memset(views, 0, sizeof(views));
#endif
    savedIndex = 0;
#ifdef __MWERKS__
    memset(&actionList, 0, 0xC);
#else
    memset(&actionList, 0, (u8*)(&actionCancel + 1) - (u8*)&actionList);
#endif
    memset(&stick, 0, 0xC);
    GSgfxColAu8* col = relivehallAisyou2ColorTbl;
    LineWidthEntry* lw = _aisyou2LineWidthHalfTable;
    u32 i;
    for (i = 0; i < 3; i++) {
        circle[i].init(lw->b, lw->c, lw->d, *col);
        col++;
        lw++;
    }
    memset(&scriptB, 0, 0x10);
    state.init();
    pState = 0;
    cursor = 0;
    memset(markerPosA, 0, 0x24);
    savedTempo = 0;
    pokemonInit((GCuptr)statusVisitor);
    statusSet = 0;
    if (st.tutorialFlag) {
        tutorialMode = 1;
    }
    pState = &st;
    cursor = &pState->cursor;
    cursor->setPositionTable(markerPosA, 0);
    state.init();
    anim.init();
    markerClear();
    markerOnVisitor = 0xFF;
    markerOnDancer = 0xFF;
    markerOnEmpty = 0xFF;
    alphaB = 0xFF;
    alphaA = 0xFF;
    memset(&tempoMode, 0, 8);
    localWindowSetTable(localWindowTable);
    loadDatas();
    infoWin.init(0xCF, 0x5D0);
    info.initTutorialTalk();
    setStage(relivehallGetLastViewStage());
}

void CMenuReliveHall::animationDataReset()
{
    for (int i = 0; i < 9; i++) {
        SPokemonView* v = &views[i];
        v->hidden = 0;
        v->ant.a14 = 0;
        f32 a = v->dirTo;
        v->dir = a;
        v->dirFrom = a;
        f32 b = v->dir2From;
        v->dir2 = b;
        v->dir2To = b;
    }
    makeCursorPositionTbl(markerPosA);
    markerClear();
    markerOnVisitor = 0xFF;
    markerOnDancer = 0xFF;
    markerOnEmpty = 0xFF;
    alphaB = 0xFF;
    alphaA = 0xFF;
    memset(&tempoMode, 0, 8);
}

void CMenuReliveHall::drawAll()
{
    animationStateUpdate();
    drawMainBG();
    drawStageCursor();
    GSprimSetup2DRender((GSgfxLayer*)GSgfxLayerFindByID(7));
    GSprimSetLineWidth(1.0f);
    GSprimSetBlendMode(1);
    SPokemonView* v = 0;
    int ai = -1;
    if (dancerPositionQuantityWithCatch() != 0 && getVisitorWithCatch() != 0) {
        s8 sel = stage->hit;
        if (sel != -1) {
            v = &views[sel];
            Pokemon* d = getPokemonFromPositionWithCatch(sel);
            ai = pokemonToAisyou(getStatusDisplayVisitorGetPointer(), d);
        }
    }
    if (ai != -1) {
        drawVisitorStarLight(ai, v);
    }
    drawDancerStarLight();
    drawMarkers(true);
    for (u32 i = 0; i < 3; i++) {
        circle[i].draw();
    }
    if (ai != -1) {
        drawVsitorLine(ai, v);
    }
    drawStatusPanel();
    draw9StageInfo();
    drawMarkers(false);
    drawVisitorHitEffect();
    drawDancerHitEffect();
    drawStagePokemon();
    alphaFadeDraw();
    cursor->draw();
    localWindowDrawAll();
    CAnt::systemUpdate(true);
    menuDrawReliveUpdate();
    infoWin.draw();
    info.draw();
}

void CMenuReliveHall::actionChange()
{
    savedTempo = getTempo(false);
    CMenuPokemonCursor* c = cursor;
    if (c->index == 6) {
        setStatusDisplayVisitor(c->pokemon.checkValid() ? &c->pokemon : 0);
    }
    c = cursor;
    Pokemon* p = c->pokemon.checkValid() ? &c->pokemon : 0;
    Pokemon tmp = *p;
    u8 in = 0;
    int idx = cursor->index;
    if (idx >= 0 && idx <= 5) in = 1;
    if (in) {
        stage->exchangeDancer(tmp, idx);
    } else {
        stage->exchangeVisitor(tmp);
    }
    cursor->setPokemon(&tmp);
    anim.change(7);
    resetViewAll();
    editAfterDp0VisitorCheck();
}

void CMenuReliveHall::actionPickup()
{
    savedTempo = getTempo(false);
    menuPtPlaySe(0x45D);
    int ci;
    SPokemonView* v;
    u8 moved = 0;
    u8 in = 0;
    int idx = cursor->index;
    f32 hold = views[idx].dir;
    f32 dirs[4];
    f32 dir2s[4];
    if (idx >= 0 && idx <= 5) in = 1;
    if (in) {
        moved = 1;
        int n = stage->getDancerQuantity();
        Pokemon picked;
        stage->pickupDancer(picked, cursor->index);
        cursor->setPokemon(&picked);
        s8 rf_t = stage->hit;
        s8 sel = rf_t;
        if (sel > cursor->index) sel--;
        if (sel >= stage->getDancerQuantity()) sel = 0;
        stage->hit = sel;
        f32* a = dir2s;
        f32* b = dirs;
        for (int i = 0; i < n; i++) {
            if (i != cursor->index) {
                *a++ = views[i].dir2;
                *b++ = views[i].dir;
            }
        }
    } else if (idx == 6) {
        Pokemon visitor;
        memcpy(markerPosB, markerPosA, 0x24);
        stage->pickupVisitor(visitor);
        cursor->setPokemon(&visitor);
    }
    u8 in2 = 0;
    ci = cursor->index;
    if (ci >= 0 && ci <= 5) in2 = 1;
    if (in2) {
        int pos;
        if (stage->getDancerQuantity() == 3 && ci == 0) {
            pos = 5;
        } else {
            pos = ci - 1;
            if (pos < 0) pos = 0;
            pos += stage->getDancerQuantity();
        }
        cursor->setPositionIndex(pos);
    }
    resetViewAll();
    if (moved) {
        dancerMoveAnimationKick(dirs, dir2s, true, hold);
    } else {
        anim.change(5);
    }
    editAfterDp0VisitorCheck();
}

void CMenuReliveHall::actionPut()
{
    savedTempo = getTempo(false);
    menuPtPlaySe(0x45E);
    f32 dirs[4];
    CMenuPokemonCursor* c = cursor;
    f32 dir2s[4];
    int idx = c->index;
    int pos = -1;
    u8 in = 0;
    if (idx >= 0 && idx <= 5) in = 1;
    if (in) {
        int n = stage->getDancerQuantity();
        if (n == 0) {
            pos = 0;
        } else if (n == 3 && cursor->index == 5) {
            pos = 0;
        } else {
            CMenuPokemonCursor* c2 = cursor;
            int i2 = c2->index;
            pos = (i2 - stage->getDancerQuantity());
            pos += 1;
        }
        c = cursor;
        stage->insertDancer(*(c->pokemon.checkValid() ? &c->pokemon : 0), pos);
        CReliveStage* s = stage;
        s8 sel = s->hit;
        if (n != 0 && (s8)sel >= pos) sel++;
        s->hit = sel;
        cursor->setPositionIndex(pos);
        SPokemonView* v;
        f32* a = dirs;
        f32* b = dir2s;
        int j = 0;
        for (int i = 0; i < n + 1; i++) {
            if (i != pos) {
                *a = views[j].dir;
                *b = views[j].dir2;
                j++;
            } else {
                *a = views[idx].dir;
                *b = 0.0f;
            }
            a++;
            b++;
        }
    } else if (idx == 6) {
        stage->putVisitor(*(c->pokemon.checkValid() ? &c->pokemon : 0));
    }
    resetViewAll();
    if (pos != -1) {
        dancerMoveAnimationKick(dirs, dir2s, false, -1.0f);
        SPokemonView* v = &views[cursor->index];
        f32 t = v->dir2From;
        v->dir2To = t;
        v->dir2 = t;
    } else {
        anim.change(4);
    }
    editAfterDp0VisitorCheck();
}
}
