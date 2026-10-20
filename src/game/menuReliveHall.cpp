// STATUS (wRelive): 55/103 exact. Added main, init, animationDataReset, drawAll, actionChange, actionPickup, actionPut
// (main/init/animationDataReset/Pickup/Put 78-97%; see markerClear: target emits the 18 sth -1 stores in one run with li r0,-1).
// WIP: Purification Chamber (relive hall) menu.
// Needs extra_cflags=["-inline", "noauto"] (peephole off is set via pragma below).
// NOT yet written: menuPtSpriteDrawArrow, drawStatusPanel, drawMainBG, stateDirChangeProc, getTempoPassion,
// animationStateUpdate, cursorPositionDecideAtStageChange, dancerMoveAnimationKick, resetViewAll, aButtomAction,
// stateMainProc, loop (declared in the class; loop = state.update() + switch on state.current 0..9, jump table).
#include <dolphin/types.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>
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
struct GSgfxVF;
struct GStexture;
struct MenuItem;
struct MenuSprite;
struct MenuSpriteVal;
struct ModelBank;
struct PCBOX;
struct PokemonData;

// Purification Chamber (relive hall) menu. Menu files were built without the peephole optimizer.
#pragma peephole off

enum GSgfxLayerID { GSgfxLayerID0 };

struct GSgfxColAu8 {
    union {
        u32 rgba;
        u8 v[4];
    };
};

struct tagSPRITE_WORK {
    tagSPRITE_WORK* next;
    u8 unk4;
    u8 unk5;
    s16 itemId;
    u8 pad8[0x40];
    u32 hook;
    s32 msgId;
    s16 x, y, w, h;
    s32 unk58;
    s16 sx, sy, sw, sh;
    u32 color;
};

struct tagWINDOW_WORK {
    s8 flags;
    u8 pad1[3];
    s32 menuId;
    u8 pad8[0x14];
    s32 layer;
    u8 pad20[4];
    tagSPRITE_WORK* sprites;
    u8 pad28[0x60];
    s32 cursor;
    s16 x, y;
};

struct MENU_ITEM_dd_ {
    u8 pad0[4];
    s16 spriteId;
    s16 x, y, w, h;
    u8 padE[10];
    s16 next;
};

extern "C" unsigned long __float_nan[];

// ---- draft declarations ----
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
    void* getPointer();
    u8 isPokemonFull();
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
s32 GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32);
void GSgfxVertex2f(f32 x, f32 y);
char* GSmsgGetGSchar(u32 msg);
u32 GSmsgGetRect(s32, s32);
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
extern s32 lbl_804EA7F0;
namespace { u8 rate01ToAlphaFrom50(f32); }
}
namespace {
bool isDirRegionInReverseClockwise(f32 a, f32 b, f32 c);
}
extern "C++" {
f32 dirRefresh2PI(f32 v);
}
static u8 _passion2ColorTbl__28ANONNS[1];
static s32 st_S3117;
static s32 xy_S3116;
// ---- draft declarations ----



// ---- draft declarations ----


extern "C" {
extern s32 _stateDirChangeProcHook;
extern s32 jtbl_2171;
}

// ---- draft declarations ----



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
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x < 0.0) {
        return *(f32*)__float_nan;
    } else if (ptFPClassify(x) == 1) {
        return *(f32*)__float_nan;
    } else {
        return x;
    }
}

class CReliveStage {
public:
    u8 pad[0x3D4];
    s8 hit;
    s32 getTempo();
    s32 getDancerQuantity();
    Pokemon* getDancerPointer(long);
    Pokemon* getVisitorPointer();
    void init();
    s32 getPassion();
    bool isBonusGet();
    void pickupDancer(Pokemon&, long);
    void pickupVisitor(Pokemon&);
    void putVisitor(Pokemon&);
    void insertDancer(Pokemon&, long);
    void exchangeDancer(Pokemon&, long);
    void exchangeVisitor(Pokemon&);
};

class CReliveHall {
public:
    static CReliveHall* getPointer();
    CReliveStage* getStage(long);
    bool isReliveReadyDarkLugiaExist();
    s32 getReliveGiveStageQuantity();
public: // draft
    u8 isReliveReadyPokemonExist();
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
s32 GSresGetResource(s32, s32);
void cameraPlayAnime(s32, u32, s32, f32);
void cameraSetType(s32);
void* memcpy(void*, const void*, u32);
void msgctrlSetValue(u32, u32);
void GSfsysReadWait(s32);
void GSfsysFree(s32);
void GSresFreeGroup(s32);
void menuPokemonStatusOpenFromPcBox(Pokemon*, void (*)(Pokemon*, MENU_POKEMON_CB_TYPE, long), long);
void winMsgOpen(long, u32, long, long);
void winMsgClose(long);
void GSprimSetBlendMode(s32);
void GSprimDraw2DPixelListC(void*, s32, void*);
void* memset(void*, int, u32);
double sin(double);
double cos(double);
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
void menuPtSpriteDraw(u16, long, long);
void menuPtSpriteDrawCenterColor(u16, long, long, u32);
void relivehallDraw9StageNumber(int);
void relivehallDraw9StageInfo(int);
int reliveHallPokemonToAisyou(Pokemon*, Pokemon*);
extern const GSgfxColAu8 GSgfxColAu8_Black;
void menuPtWindowWorkDraw(long);
int degreeSubHalf(long, long);
int xyxy2dirDegree(const PocketVec<short>&, const PocketVec<short>&);
f32 xyxy2distance(const PocketVec<short>&, const PocketVec<short>&);
void menuPtPlaySe(u32);
f32 dirSubHalf(f32, f32);
int degreeRefresh360(long);
void setBitTable(u32*, long, bool);
bool getBitTable(u32*, long);
extern "C" void GSprimDraw2DLine(GSgfxColAu8*, GSgfxColAu8*, PocketVec<f32>, PocketVec<f32>);
MENU_ITEM_dd_* menuPtItemGetByMenuIdAndItemId(long, u32, long);
void menuPtItemDrawOffset(MENU_ITEM_dd_*, long, long);
void menuPtItemDrawOffsetXWColor(MENU_ITEM_dd_*, long, long, u32);
void menuPtItemDrawAlpha(MENU_ITEM_dd_*, u8);
void menuPtSpriteWorkSetSw(tagWINDOW_WORK*, u32, long, bool);
void menuPtWindowWorkDraw(tagWINDOW_WORK*);
void menuPtSpriteWorkSetWidthRateColor(tagWINDOW_WORK*, u32, long, f32, GSgfxColAu8);
tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(tagWINDOW_WORK*, u32, long);
u32 GSgfxColAu8To32(GSgfxColAu8);

extern GSgfxColAu8 relivehallAisyou2ColorTbl[3];
extern s16 lbl_8032E568[10];

GSgfxColAu8 relivehallAisyou2ColorTbl[3] = { { 0x2800FFFF }, { 0x28AAFFFF }, { 0xC8F0FFFF } };
s32 pcReliveHallSoundTbl[5] = { 0x459, 0x45A, 0x45B, 0x14, 0x15 };
s16 lbl_8032E568[10] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 0 };
namespace {
const PocketVec<short> circlePosition = { 320, 280 };
const PocketVec<f32> fcirclePosition = { 320.0f, 280.0f };
u8 blurAlphaTbl[9] = { 0xFF, 0xD7, 0xAF, 0x87, 0x5F, 0x37, 0, 0, 0 };
f32 blurScaleTbl[9] = { 1.0f, 0.85f, 0.7f, 0.55f, 0.4f, 0.25f, 0.0f, 0.0f, 0.0f };
f32 starMasterScaleTbl[10] = { 1.1f, 0.85f, 1.0f, 0.9f, 1.1f, 0.9f, 0.85f, 1.1f, 1.0f, 0.85f };
f32 _markerDancerOnDirTbl[20] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.1415927f, 0.0f, 0.0f, 0.0f, 2.0943952f, 4.1887903f, 0.0f, 5.497787f, 0.7853982f, 2.3561945f, 3.9269907f };
f32 _zokuseiMarkDancerOnDirTbl[20] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.4486233f, 0.0f, 0.0f, 0.0f, 1.4486233f, 1.6929694f, 0.0f, 0.0f, 1.4486233f, 1.9373156f, 4.328417f, 0.0f, 4.82409f, 1.4590952f, 1.6824975f, 4.600688f };
f32 _markerDancerEmptyDirTbl[16] = { 0.0f, 0.0f, 0.0f, 0.0f, 3.1415927f, 0.0f, 0.0f, 0.0f, 1.5707964f, 4.712389f, 0.0f, 0.0f, 1.0471976f, 3.1415927f, 5.235988f, 0.0f };
PocketVec<short> _cursorPositionTblDefault[9] = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { 320, 280 }, { 198, 428 }, { 539, 428 } };
GSgfxColAu8 _passion2ColorTbl[13] = { { 0x2800FFFF }, { 0x2855FFFF }, { 0x28AAFFFF }, { 0x78CDFFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF }, { 0xC8F0FFFF } };
f32 _aisyou2ScaleTbl[3] = { 0.6f, 0.8f, 1.0f };
struct LineWidthEntry { s32 a; f32 b; s32 c; f32 d; };
LineWidthEntry _aisyou2LineWidthHalfTable[3] = { { 1, 0.75f, 1, 0.3f }, { 2, 1.5f, 2, 0.6f }, { 3, 2.25f, 3, 0.9f } };
long localWindowTable[8] = { 0x67, 0x71, 0x72, 0x88, 0x76, 0xCF, 0xE3, 0 };
u32 actionMenuCatchVisitorOnPokemon[6] = { 0x4, 0xd111, 0xd112, 0xd113, 0xd114, 0x0 };
u32 actionMenuCatchDancerOnPokemon[6] = { 0x3, 0xd111, 0xd113, 0xd114, 0x0, 0x0 };
u32 actionMenuCatchVisitorOnNone[6] = { 0x4, 0xd115, 0xd112, 0xd113, 0xd114, 0x0 };
u32 actionMenuCatchDancerOnNone[6] = { 0x3, 0xd115, 0xd113, 0xd114, 0x0, 0x0 };
u32 actionMenuOnVisitor[6] = { 0x4, 0xd116, 0xd112, 0xd113, 0xd114, 0x0 };
u32 actionMenuOnDancer[6] = { 0x3, 0xd116, 0xd113, 0xd114, 0x0, 0x0 };
PocketVec<short> _cursorPositionTblAddPc[2] = { { 336, 428 }, { 379, 428 } };
}

struct CAnt {
    s32 a0, a4, a8;
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
    void setAnimation(long);
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
    u32 value;
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
    void init(long, u32);
    void initTutorialTalk();
    void draw();
public: // draft
    void setMsgCtrlValue(unsigned long, unsigned long);
    void close();
    void open(unsigned long, bool);
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
};

class CMetaMenu {
public:
    s32 fadeTime;
    s32 fadeState;
    s32 pad8;
    u32 seId;
    u8 pad10[0xC];
    s32 windowIds[64];
    void (*windowFuncs[64])(CMetaMenu*, long);
    long* windowTable;
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
    long calcAnimationTimeRate0toX(f32, long);
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
    static long defautlLocalWindowOpenTable[];
    CKeyInfo* getKeyInfo();
    void aButtonWait();
    long actionMenu(u32*, int, long, long, long);
    void localWindowRemove(long);
    void localWindowDrawAll(long, long);
    void localWindowDrawAll();
    void localWindowEntry(long, long, void (*)(CMetaMenu*, long));
    long localWindowSearch(long);
    void localWindowDeleteAll();
    void localWindowCreateAll();
    void localWindowSetTable(long*);
};

namespace {
void _menuDrawReliveMeter(Pokemon*, long, long, long, long, u8, GSgfxLayerID, long);
void _relivehallTempoBarSpriteSetting(tagWINDOW_WORK*, u32, int, u8, bool);
void menuPtSpriteDrawArrow(u16, u32, f32, int);
}
struct CMenuPokemonCursor {
    void setPositionIndex(long);
    u8 active;
    s32 mode;
    f32 t;
    s32 index;
    u8 pad10[4];
    PocketVec<short> pos;
    PocketVec<short>* table;
    u8 pad1C[4];
    Pokemon pokemon;
    u8 padE4[0x68];
    u8 holding;
    u8 pad14D[3];
    bool isCatchPokemon();
    void setPokemon(Pokemon*);
    void draw();
    void setPositionTable(PocketVec<short>*, long);
    void setPositionTableDummy();
public: // draft
    void setAnimationOff();
};

struct GSgfxLayer;
void GSprimSetup2DRender(GSgfxLayer*);
extern "C" int GSgfxLayerFindByID(int);
extern "C" void GSprimSetLineWidth(f32);
extern "C" void menuDrawReliveUpdate();
void menuPtPlaySe(u32);
struct CMenuGlobalState {
    s32 pad0;
    s32 kind;
    u8 pad8[4];
    CMenuPokemonCursor cursor;
    u8 tutorialFlag;
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
    u8 sw[0x2800];
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
    u8 hidden;
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
    void drawStarLightOne(long, f32, f32, long);
    void drawDancerHitEffect();
    void drawDancerStarLight();
    void drawStarHitEffect(f32, f32, f32);
    f32 starTimeFromBorn(f32&, f32&, f32);
    f32 calcStarDir(int, int);
    void infoMessageDisplay3Line(u32);
    void infoMessageDisplay(u32);
    void drawVisitorHitEffect();
    void drawVisitorStarLight(long, SPokemonView*);
    void drawVsitorLine(long, SPokemonView*);
    SPokemonView* getPokemonViewByClockwizePositionWithCatch(int);
    int dancerPositionQuantityWithCatch();
    Pokemon* getVisitorWithCatch();
    f32 getDirToAisyou(f32);
    void setCircleSw();
    void drawStagePokemon();
    void drawMarkers(bool);
    void draw9StageInfo();
    void drawStageCursor();
    Pokemon* getStatusDisplayVisitorGetPointer();
    int getTempo(bool);
    void getCircleColorAisyou(f32&, f32&, int&, int);
    void actionMenuMain();
    void stateDirChangeWinDraw(long);
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
} // namespace

void menuReliveHallExecFromPcBox(CMenuGlobalState& s)
{
    thisExec(s);
}

void relivehallSetLastViewStage(long i)
{
    _lastViewStage = i;
}

long relivehallGetLastViewStage()
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
            long ox = i * 0x42;
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

void relivehallDrawStageInfoCursor(long idx, int tempo, int flag, Pokemon* p, bool b)
{
    long base;
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
        long ox = base + lbl_8032E568[idx];
        MENU_ITEM_dd_* it = menuItemBiosGetPtr(0x71, 0x2B5);
        _menuDrawReliveMeter(p, it->x + ox, it->y, it->w, it->h, 0xFF, (GSgfxLayerID)w->layer, idx);
    }
}

namespace {
void _relivehallTempoBarSpriteSetting(tagWINDOW_WORK* w, u32 id, int tempo, u8 alpha, bool scissor)
{
    f32 rate = relivehallTempoToRate(tempo);
    GSgfxColAu8 c = relivehallAisyou2ColorTbl[relivehallTempoToLevel(tempo)];
    c.v[3] = alpha;
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
    s32 spA;
    u16 sp8;
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
    s8 var_r27_4;
    tagWINDOW_WORK *temp_r31;
    u16 *var_r27;
    u16 var_r28;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r3;
    u32 temp_r5;
    u32 temp_r7;
    u8 var_r0;
    u8 var_r27_3;
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
    temp_r3 = (unsigned long)(((CMenuReliveHall*)(this))->getStatusDisplayVisitorGetPointer());
    if (temp_r3 != 0) {
        temp_r3_2 = (MenuItem *)(menuItemBiosGetPtr(M2C_FIELD(temp_r31, s32 *, 4), 0x289U));
        _menuDrawReliveMeter((Pokemon*)((Pokemon *) temp_r3), (s32) M2C_FIELD(temp_r3_2, s16 *, 6), (s32) M2C_FIELD(temp_r3_2, s16 *, 8), (s32) M2C_FIELD(temp_r3_2, s16 *, 0xA), (s32) M2C_FIELD(temp_r3_2, s16 *, 0xC), 0xFFU, (GSgfxLayerID)(M2C_FIELD(temp_r31, s32 *, 0x1C)), M2C_FIELD(this, s32 *, 0x338));
        var_r27 = &sp8;
        var_r28 = 0;
        do {
            *var_r27 = zokuseiGetPokemonSpriteID((void *)(((Pokemon*)((Pokemon *) temp_r3))->getPokemonDataPtr()), (unsigned short)(0));
            var_r27 += 2;
            var_r28 += 1;
        } while ((s32) var_r28 < 2);
        temp_r27 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x297U, 0));
        temp_r28 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x298U, 0));
        if (sp8 == spA) {
            temp_r7 = M2C_FIELD(temp_r27, s16 *, 0x50) + M2C_FIELD(temp_r28, s16 *, 0x50);
            temp_r5 = M2C_FIELD(temp_r27, s16 *, 0x52) + M2C_FIELD(temp_r28, s16 *, 0x52);
            menuPtSpriteDraw(sp8, (s32) ((temp_r7 >> 0x1FU) + temp_r7) >> 1, (s32) ((temp_r5 >> 0x1FU) + temp_r5) >> 1);
        } else {
            menuPtSpriteDraw(sp8, (s32) M2C_FIELD(temp_r27, s16 *, 0x50), (s32) M2C_FIELD(temp_r27, s16 *, 0x52));
            menuPtSpriteDraw(spA, (s32) M2C_FIELD(temp_r28, s16 *, 0x50), (s32) M2C_FIELD(temp_r28, s16 *, 0x52));
        }
    }
    if (temp_r3 != 0) {
        temp_r3_3 = pokecoloGetCountryCode();
        if (temp_r3_3 != 0) {
            if ((temp_r3_3 >= 0) && (temp_r3_3 < 3)) {
                msgctrlSetValue((unsigned long)(0x37), (unsigned long)(((Pokemon*)((Pokemon *) temp_r3))->getNicknamePtr()));
                temp_r3_4 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x4D3U, 0));
                GSmsgPrint2(M2C_FIELD(temp_r31, s32 *, 0x1C), M2C_FIELD(temp_r3_4, s16 *, 0x50), M2C_FIELD(temp_r3_4, s16 *, 0x52), -1, 0x4279);
            }
        } else {
            temp_r28_2 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x4D3U, 0));
            msgctrlSetValue((unsigned long)(0x37), (unsigned long)(GSmsgGetGSchar((unsigned long)(pokemonDataBiosGetName((PokemonData*)(((Pokemon*)((Pokemon *) temp_r3))->getPokemonDataPtr()))))));
            GSmsgPrint2(M2C_FIELD(temp_r31, s32 *, 0x1C), M2C_FIELD(temp_r28_2, s16 *, 0x50), M2C_FIELD(temp_r28_2, s16 *, 0x52), -1, 0x4278);
        }
        temp_r28_3 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x4D4U, 0));
        msgctrlSetValue(0x34, (u32) ((Pokemon*)((Pokemon *) temp_r3))->getLevel());
        GSmsgPrint2(M2C_FIELD(temp_r31, s32 *, 0x1C), M2C_FIELD(temp_r28_3, s16 *, 0x50), M2C_FIELD(temp_r28_3, s16 *, 0x52), -1, 0x4271);
        temp_r3_5 = pokecoloGetCountryCode();
        if (temp_r3_5 < 3) {
            if (temp_r3_5 < 1) {

            } else {
                temp_r3_6 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x8EEU, 0));
                GSmsgPrint2(M2C_FIELD(temp_r31, s32 *, 0x1C), M2C_FIELD(temp_r3_6, s16 *, 0x50), M2C_FIELD(temp_r3_6, s16 *, 0x52), -1, 0xD15F);
            }
        }
    }
    temp_r30 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x2A5U, 0));
    msgctrlSetValue(0x2F, M2C_FIELD(this, s32 *, 0x338) + 1);
    GSmsgPrint2(M2C_FIELD(temp_r31, s32 *, 0x1C), M2C_FIELD(temp_r30, s16 *, 0x50), M2C_FIELD(temp_r30, s16 *, 0x52), -1, 0xD157);
    temp_r30_2 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x2A6U, 0));
    temp_r0 = GSmsgGetRect(0xD161, 0x10000) >> 0x10U;
    temp_r3_7 = M2C_FIELD(temp_r30_2, s16 *, 0x54);
    GSmsgPrint2(M2C_FIELD(temp_r31, s32 *, 0x1C), M2C_FIELD(temp_r30_2, s16 *, 0x50) + (s16) (((s32) (((u32) temp_r3_7 >> 0x1FU) + temp_r3_7) >> 1) - ((s32) (((u32) (s16) temp_r0 >> 0x1FU) + (s16) temp_r0) >> 1)), M2C_FIELD(temp_r30_2, s16 *, 0x52), -1, 0xD161);
    temp_r30_3 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x2D2U, 0));
    temp_r0_2 = GSmsgGetRect(0xD123, 0x10000) >> 0x10U;
    temp_r3_8 = M2C_FIELD(temp_r30_3, s16 *, 0x54);
    GSmsgPrint2(M2C_FIELD(temp_r31, s32 *, 0x1C), M2C_FIELD(temp_r30_3, s16 *, 0x50) + (s16) (((s32) (((u32) temp_r3_8 >> 0x1FU) + temp_r3_8) >> 1) - ((s32) (((u32) (s16) temp_r0_2 >> 0x1FU) + (s16) temp_r0_2) >> 1)), M2C_FIELD(temp_r30_3, s16 *, 0x52), -1, 0xD123);
    temp_r30_4 = (unsigned char *)(menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x4D0U, 0));
    var_r27_2 = 0xD122;
    if ((u8) lbl_804EA7F0 != 0) {
        var_r27_2 = 0xD15A;
    }
    temp_r0_3 = GSmsgGetRect(var_r27_2, 0x10000) >> 0x10U;
    temp_r4 = M2C_FIELD(temp_r30_4, s16 *, 0x54);
    temp_r8 = M2C_FIELD(temp_r30_4, s16 *, 0x50);
    GSmsgPrint2(M2C_FIELD(temp_r31, s32 *, 0x1C), temp_r8 + (s16) (((s32) (((u32) temp_r4 >> 0x1FU) + temp_r4) >> 1) - ((s32) (((u32) (s16) temp_r0_3 >> 0x1FU) + (s16) temp_r0_3) >> 1)), M2C_FIELD(temp_r30_4, s16 *, 0x52), -1, var_r27_2);
    if ((u8) M2C_FIELD(this, u8 *, 0x81184) != 0) {
        menuPtSpriteWorkSetSw((tagWINDOW_WORK*)(temp_r31), 0x316U, 0, 0U);
        temp_r27_2 = M2C_FIELD(this, s32 *, 0x80FC0);
        _relivehallTempoBarSpriteSetting((tagWINDOW_WORK*)(temp_r31), 0x28BU, (s32) ((M2C_FIELD(this, f32 *, 0x81188) * (f32) (((CMenuReliveHall*)(this))->getTempo(0U) - temp_r27_2)) + (f32) temp_r27_2), 0xFFU, 1U);
        return;
    }
    var_r28_2 = 0;
    var_r30 = 0;
    if (((CMenuPokemonCursor*)(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() != 0) {
        if (((Pokemon*)(((u8*)((temp_r27_3 = M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64))) + 0x20)))->checkValid() != 0) {
            var_r3 = (Pokemon *)(((u8*)(temp_r27_3) + 0x20));
        } else {
            var_r3 = NULL;
        }
        if (((Pokemon*)(var_r3))->isDarkPokemon() == 0) {
            var_r30 = 1;
        }
    }
    if (var_r30 != 0) {
        var_r0 = 0;
        temp_r3_9 = M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), s32 *, 0xC);
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
    var_r27_4 = -1;
    if (var_r28_2 != 0) {
        var_r27_4 = rate01ToAlphaFrom50(((CMetaMenu*)((CMetaMenu *) this))->calcAnimationTimeRate0to1to0(0.6f));
    }
    _relivehallTempoBarSpriteSetting((tagWINDOW_WORK*)(temp_r31), 0x28BU, ((CMenuReliveHall*)(this))->getTempo(0U), (u8) var_r27_4, 1U);
}

}

namespace {
void CMenuReliveHall::drawMainBG() {
    s32 spC;
    s32 sp8;
    f32 temp_f1;
    f32 temp_f30;
    f32 temp_f31;
    s32 *var_r28;
    s32 temp_r0;
    s32 temp_r26;
    s32 temp_r3;
    s32 var_r25;
    s32 var_r27;
    s8 var_r23;
    tagSPRITE_WORK *temp_r24;
    tagWINDOW_WORK *temp_r31;
    u8 temp_r30;

    temp_r31 = (tagWINDOW_WORK *)(windowSearchID(0x67));
    temp_r30 = ((CMenuReliveHall*)(this))->getVisitorWithCatch() != 0;
    temp_r3 = ((CMenuReliveHall*)(this))->getPassion((int*)(&spC));
    if (temp_r3 <= 0) {
        var_r27 = 0;
    } else if (temp_r3 <= 0x1B) {
        var_r27 = 1;
    } else if (temp_r3 <= 0x34) {
        var_r27 = 2;
    } else if (temp_r3 <= 0x5A) {
        var_r27 = 3;
    } else if (temp_r3 < 0xC0) {
        var_r27 = 4;
    } else {
        var_r27 = spC + 4;
    }
    temp_f1 = ((CMetaMenu*)((CMetaMenu *) this))->calcAnimationTimeRate0to1(0.8f);
    var_r28 = (long *)(_passion2ColorTbl);
    var_r25 = 0;
    temp_r26 = (s32) (temp_f1 / 0.03846154f);
    temp_f30 = -(((f32) temp_r26 * 0.03846154f) - temp_f1);
    temp_f30 *= 26.0f;
    temp_f31 = 1.0f - temp_f30;
    do {
        temp_r24 = menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)(temp_r31), 0x28DU, var_r25);
        sp8 = *var_r28;
        M2C_FIELD(temp_r24, u32 *, 0x64) = GSgfxColAu8To32(*(GSgfxColAu8*)&sp8);
        if ((var_r25 < var_r27) && (temp_r30 != 0)) {
            if (temp_r26 < 0xD) {
                if (var_r25 < temp_r26) {
                    var_r23 = -1;
                } else if (var_r25 == temp_r26) {
                    var_r23 = rate01ToAlphaFrom50(temp_f30);
                } else {
                    var_r23 = 0x46;
                }
            } else {
                temp_r0 = temp_r26 - 0xD;
                if (var_r25 < temp_r0) {
                    var_r23 = 0x46;
                } else if (var_r25 == temp_r0) {
                    var_r23 = rate01ToAlphaFrom50(temp_f31);
                } else {
                    var_r23 = -1;
                }
            }
            menuPtSpriteWorkSetSw((tagWINDOW_WORK *)((tagWINDOW_WORK*)(temp_r31)), (unsigned long)((tagSPRITE_WORK*)(temp_r24)), (long)(1U), (bool)(0));
            M2C_FIELD(temp_r24, s8 *, 0x67) = var_r23;
        } else {
            menuPtSpriteWorkSetSw((tagWINDOW_WORK *)((tagWINDOW_WORK*)(temp_r31)), (unsigned long)((tagSPRITE_WORK*)(temp_r24)), (long)(0U), (bool)(0));
        }
        var_r28 += 4;
        var_r25 += 1;
    } while (var_r25 < 0xD);
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
    pMenuReliveHall = new CMenuReliveHall;
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
        col[i].v[3] = 0;
    }
}

void SCircle::setFade(u8 fade)
{
    for (int i = 0; i < count; i++) {
        if (sw[i]) col[i].v[3] = px[i].alpha * fade / 255;
    }
}
void menuPtSpriteDrawArrow(u16 p0, u32 p1, f32 p2, int p3) {
    s32 unksp13;
    s32 unksp12;
    s32 unksp11;
    s32 sp10;                                       /* compiler-managed */
    s32 sp8;
    volatile GStexture *temp_r31;
    GStexture *temp_r3_2;
    s32 *var_r27;
    s32 *var_r29;
    s32 *var_r29_2;
    MenuSpriteVal *temp_r3;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f1;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;
    f32 temp_f3;
    f32 temp_f6;
    f32 temp_f7;
    volatile f32 temp_f8;
    f64 temp_f29_2;
    s32 var_r26;
    s32 var_r28;

    temp_r3 = menuSpriteBiosGetValPtr((MenuSprite*)(menuSpriteBiosGetPtr((u32) p0)));
    temp_r3_2 = (GStexture *)(GSresGetResourceAllGroup(M2C_FIELD(temp_r3, u32 *, 8)));
    temp_f27 = (f32) M2C_FIELD(temp_r3, s16 *, 0);
    temp_r31 = temp_r3_2;
    sp10 = jtbl_3115;
    temp_f31 = (f32) M2C_FIELD(temp_r3, s16 *, 2);
    temp_f30 = (f32) M2C_FIELD(temp_r3, s16 *, 4);
    sp10 = (u8) (p1 >> 0x18U);
    temp_f29 = (f32) M2C_FIELD(temp_r3, s16 *, 6);
    unksp11 = (u8) (p1 >> 0x10U);
    unksp12 = (u8) (p1 >> 8U);
    unksp13 = (u8) p1;
    temp_f0 = temp_f27 / (f32) GStextureGetXsize((GStexture*)(temp_r3_2));
    M2C_FIELD(&st_S3117, f32 *, 8) = temp_f0;
    M2C_FIELD(&st_S3117, f32 *, 0) = temp_f0;
    temp_f0_2 = (temp_f27 + temp_f30) / (f32) GStextureGetXsize((GStexture*)(temp_r31));
    M2C_FIELD(&st_S3117, f32 *, 0x18) = temp_f0_2;
    M2C_FIELD(&st_S3117, f32 *, 0x10) = temp_f0_2;
    temp_f7 = (temp_f31 + temp_f29) / (f32) GStextureGetYsize((GStexture*)(temp_r31));
    temp_f0_3 = temp_f31 / (f32) GStextureGetYsize((GStexture*)((u16)temp_r31));
    M2C_FIELD(&st_S3117, f32 *, 0x14) = temp_f0_3;
    M2C_FIELD(&st_S3117, f32 *, 0xC) = temp_f0_3;
    var_r27 = &xy_S3116;
    temp_f8 = temp_f30 * 0.5f;
    temp_f6 = temp_f29 - temp_f29;
    M2C_FIELD(&xy_S3116, f32 *, 4) = temp_f29;
    temp_f2 = 0.0f - temp_f29;
    M2C_FIELD(&xy_S3116, f32 *, 0x14) = 0.0f;
    temp_f3 = 0.0f - temp_f8;
    M2C_FIELD(&xy_S3116, f32 *, 0xC) = 0.0f;
    M2C_FIELD(&xy_S3116, f32 *, 8) = 0.0f;
    M2C_FIELD(&xy_S3116, f32 *, 0) = 0.0f;
    M2C_FIELD(&xy_S3116, f32 *, 4) = temp_f6;
    M2C_FIELD(&xy_S3116, f32 *, 0xC) = temp_f2;
    M2C_FIELD(&xy_S3116, f32 *, 0x14) = temp_f2;
    M2C_FIELD(&st_S3117, f32 *, 0x1C) = temp_f7;
    M2C_FIELD(&st_S3117, f32 *, 4) = temp_f7;
    M2C_FIELD(&xy_S3116, f32 *, 0x18) = temp_f30;
    M2C_FIELD(&xy_S3116, f32 *, 0x10) = temp_f30;
    M2C_FIELD(&xy_S3116, f32 *, 0x1C) = temp_f29;
    M2C_FIELD(&xy_S3116, f32 *, 4) = (f32) (temp_f6 + (f32) p3);
    M2C_FIELD(&xy_S3116, f32 *, 0) = temp_f3;
    M2C_FIELD(&xy_S3116, f32 *, 0xC) = (f32) (temp_f2 + (f32) p3);
    M2C_FIELD(&xy_S3116, f32 *, 8) = temp_f3;
    M2C_FIELD(&xy_S3116, f32 *, 0x14) = (f32) (temp_f2 + (f32) p3);
    temp_f1 = temp_f30 - temp_f8;
    temp_f29_2 = -p2;
    var_r29 = &xy_S3116;
    var_r28 = 0;
    M2C_FIELD(&xy_S3116, f32 *, 0x1C) = temp_f6;
    M2C_FIELD(&xy_S3116, f32 *, 0x10) = temp_f1;
    M2C_FIELD(&xy_S3116, f32 *, 0x18) = temp_f1;
    M2C_FIELD(&xy_S3116, f32 *, 0x1C) = (f32) (temp_f6 + (f32) p3);
    do {
        temp_f30_2 = M2C_FIELD(var_r29, f32 *, 4);
        temp_f28 = (f32) cos(temp_f29_2);
        M2C_FIELD(var_r29, f32 *, 0) = (f32) ((temp_f30_2 * (f32) sin(temp_f29_2)) + ((M2C_FIELD(var_r29, f32 *, 0)) * temp_f28));
        temp_f28_2 = (f32) sin(temp_f29_2);
        var_r28 += 1;
        M2C_FIELD(var_r29, f32 *, 4) = (f32) ((temp_f30_2 * (f32) cos(temp_f29_2)) - ((M2C_FIELD(var_r29, f32 *, 0)) * temp_f28_2));
        var_r29 += 8;
    } while (var_r28 < 4);
    M2C_FIELD(&xy_S3116, f32 *, 0) = (f32) (M2C_FIELD(&xy_S3116, f32 *, 0) + 320.0f);
    M2C_FIELD(&xy_S3116, f32 *, 4) = (f32) (M2C_FIELD(&xy_S3116, f32 *, 4) + 280.0f);
    M2C_FIELD(&xy_S3116, f32 *, 8) = (f32) (M2C_FIELD(&xy_S3116, f32 *, 8) + 320.0f);
    M2C_FIELD(&xy_S3116, f32 *, 0xC) = (f32) (M2C_FIELD(&xy_S3116, f32 *, 0xC) + 280.0f);
    M2C_FIELD(&xy_S3116, f32 *, 0x10) = (f32) (M2C_FIELD(&xy_S3116, f32 *, 0x10) + 320.0f);
    M2C_FIELD(&xy_S3116, f32 *, 0x14) = (f32) (M2C_FIELD(&xy_S3116, f32 *, 0x14) + 280.0f);
    M2C_FIELD(&xy_S3116, f32 *, 0x18) = (f32) (M2C_FIELD(&xy_S3116, f32 *, 0x18) + 320.0f);
    M2C_FIELD(&xy_S3116, f32 *, 0x1C) = (f32) (M2C_FIELD(&xy_S3116, f32 *, 0x1C) + 280.0f);
    GSprimSetQuadVertexOrder(1);
    GSprimSetBlendMode(1);
    sp8 = 4;
    GSgfxSetupRenderAndSelect((GSgfxVF*)(GSgfxVFBuildTemp(0, 4, 0, 0, 1, 5, 1, 1)));
    GSgfxSetTUnitUserColorArg(0U, 0xAU, 0xFU, 0xFU, 0xFU);
    GSgfxSetTUnitUserColorOp(0U, 0U, 0U, 0U, 1U, 0U);
    GSgfxSetTUnitUserAlphaArg(0U, 7U, 5U, 4U, 7U);
    GSgfxSetTUnitUserAlphaOp(0U, 0U, 0U, 0U, 1U, 0U);
    GSgfxSelectTexture(0U, (GStexture*)(temp_r31));
    GSgfxSetPrimitiveType(0x80U);
    GSgfxBeginSurface(4U);
    var_r29_2 = &st_S3117;
    var_r26 = 0;
    do {
        GSgfxVertex2f(M2C_FIELD(var_r27, f32 *, 0), M2C_FIELD(var_r27, f32 *, 4));
        GSgfxColor4u8(sp10, unksp11, unksp12, unksp13);
        GSgfxTexCoord2f(M2C_FIELD(var_r29_2, f32 *, 0), M2C_FIELD(var_r29_2, f32 *, 4));
        var_r27 += 8;
        var_r29_2 += 8;
        var_r26 += 1;
    } while (var_r26 < 4);
    GSgfxEndSurface();
}


void SCircle::setSwPrime(int from, int to, bool on)
{
    int b = start[to];
    int a = start[from];
    if (on) {
        for (int i = a; i < b; i++) {
            sw[i] = on;
            col[i].v[3] = px[i].alpha;
        }
    } else {
        for (int i = a; i < b; i++) {
            sw[i] = on;
            col[i].v[3] = 0;
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
    memset(this, 0, 0x2ADB8);
    outer = outer_;
    radius = radius_;
    inner = inner_;
    bits = (u32*)GSmemAllocClr(0x7D00);
    count = 0;
    int prevY = -1;
    int prevX = -1;
    s16 prevAngle = -1;
    for (f32 a = 0.0f; a < 6.2831855f; a += 0.008726646f) {
        int x = (int)(90.0f * (f32)sin(a)) + 0x140;
        int y = (int)(90.0f * -(f32)cos(a)) + 0x118;
        s16 angle = degreeRefresh360((s32)(180.0f * a / 3.1415927f));
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
        if (dx <= 0) dx = -dx;
        int dy = px[i].y - 0x118;
        if (dy <= 0) dy = -dy;
        f32 d = (f32)fabs(ptSqrt((f32)(dx * dx + dy * dy)) - 90.0f);
        if (d <= inner) px[i].alpha = 0xFF;
        else if (d < outer) px[i].alpha = (u8)(255.0f * (outer - d) / (outer - inner));
        else px[i].alpha = 0;
    }
    for (int i = 0; i < count; i++) {
        pos[i][0] = px[i].x;
        pos[i][1] = px[i].y;
    }
    for (int i = 0; i < count; i++) {
        col[i] = color;
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
    v.x = (s16)(90.0f * (f32)sin(dir) + 320.0f);
    v.y = (s16) - (90.0f * (f32)cos(dir) - 280.0f);
    return v;
}

void CMenuReliveHall::drawStarLightOne(long colorIdx, f32 x, f32 y, long n)
{
    long t = calcAnimationTimeRate0toX(0.32000002f, 10) + n;
    GSgfxColAu8 c = relivehallAisyou2ColorTbl[colorIdx];
    f32 scale = _aisyou2ScaleTbl[colorIdx];
    c.v[3] = blurAlphaTbl[n] * alphaB / 255;
    f32 star = starMasterScaleTbl[t % 10];
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
                f32 d = -(0.06981317f * (f32)j - dir);
                s = (f32)sin(d);
                c = (f32)cos(d);
                drawStarLightOne(getDirToAisyou(d), 90.0f * s + 320.0f, 90.0f * -c + 280.0f, j);
            }
        }
    }
}

void CMenuReliveHall::drawStarHitEffect(f32 x, f32 y, f32 t)
{
    if (t < 0.5f) {
        f32 r = t / 0.5f;
        u8 a = (s32)(255.0f * (1.0f - r));
        volatile u8 b = (u8)(alphaB * a / 255);
        menuPtSpriteDrawAndRollScale(0x297, b | ~0xFF, x, y, 0.0f, 0.5f + r);
    }
}

f32 CMenuReliveHall::starTimeFromBorn(f32& x, f32& y, f32 dir)
{
    int n = dancerPositionQuantityWithCatch();
    for (s8 i = 0; i < n; i++) {
        SPokemonView* v = getPokemonViewByClockwizePositionWithCatch(i);
        if (isDirRegionIn(dir, v->dir, getPokemonViewByClockwizePositionWithCatch((i + 1) % n)->dir)) {
            x = 90.0f * (f32)sin(v->dir) + 320.0f;
            y = 90.0f * -(f32)cos(v->dir) + 280.0f;
            return 6.0f * (dirSubOne(dir, v->dir) / 6.2831855f);
        }
    }
    return 0.0f;
}

f32 CMenuReliveHall::calcStarDir(int i, int n)
{
    return 2.0f * (3.1415927f * ((f32)i / (f32)n)) + 6.2831855f * calcAnimationTimeRate0to1(6.0f);
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
    PocketVec<short> sp8;
    CKeyInfo *temp_r3;
    u8 var_r27;
    f32 var_f30;
    f32 var_f1;
    f32 var_f29;
    f32 temp_f1;
    s8 temp_r30;
    s8 var_r25;
    s8 var_r26_2;
    s8 var_r31;
    u16 temp_r0;
    u16 temp_r0_2;
    u8 var_r26;
    CMenuReliveHall *var_r28;

    memset((void*)((u8*)this + 0x620), 0, 0xCU);
    *M2C_FIELD((s32)this, s8 **, 0x80F64) = 0;
    M2C_FIELD((s32)this, s8 *, 0x81135) = 0;
    windowSearchID(0x76);
    var_r31 = (s8) M2C_FIELD(M2C_FIELD(this, CReliveStage **, 0x33C), u8 *, 0x3D4);
    temp_r30 = var_r31;
    memset((void*)((u8*)this + 0x620), 0, 0xCU);
    ((CInfoWindow*)(this + 0x80F8C))->setMsgCtrlValue(0x32U, (unsigned long)(((Pokemon*)(((CMenuReliveHall*)(this))->getCurrentPokemonPointer()))->getNicknamePtr()));
    ((CInfoWindow*)(this + 0x80F8C))->open(0xD117U, 0U);
    var_r27 = 0;
    ((CMetaMenu*)((CMetaMenu *) this))->localWindowEntry(0x76, 0, (void (*)(CMetaMenu*, long))(_stateDirChangeProcHook));
    do {
        var_r26 = M2C_FIELD(this, u8 *, 0x621);
        var_f30 = M2C_FIELD(this, f32 *, 0x624);
        temp_r3 = ((CMetaMenu*)((CMetaMenu *) this))->getKeyInfo();
        temp_r0 = M2C_FIELD(temp_r3, u16 *, 4);
        switch ((s32) temp_r0) {                    /* switch 1; irregular */
        case 16:                                    /* switch 1 */
            menuPtPlaySe(0x45AU);
            var_r27 = 1;
            break;
        case 32:                                    /* switch 1 */
            M2C_FIELD(M2C_FIELD(this, CReliveStage **, 0x33C), u8 *, 0x3D4) = (u8) temp_r30;
            menuPtPlaySe(0x45BU);
            var_r27 = 1;
            break;
        }
        if (var_r27 == 0) {
            temp_r0_2 = M2C_FIELD(temp_r3, u16 *, 6);
            switch (temp_r0_2) {                    /* switch 2 */
            case 1:                                 /* switch 2 */
                var_f30 = 0.0f;
                var_r26 = 1;
                break;
            case 8:                                 /* switch 2 */
                var_f30 = 1.5707964f;
                var_r26 = 1;
                break;
            case 2:                                 /* switch 2 */
                var_f30 = 3.1415927f;
                var_r26 = 1;
                break;
            case 4:                                 /* switch 2 */
                var_f30 = 4.712389f;
                var_r26 = 1;
                break;
            case 9:                                 /* switch 2 */
                var_f30 = 0.7853982f;
                var_r26 = 1;
                break;
            case 10:                                /* switch 2 */
                var_f30 = 2.3561945f;
                var_r26 = 1;
                break;
            case 6:                                 /* switch 2 */
                var_f30 = 3.9269907f;
                var_r26 = 1;
                break;
            case 5:                                 /* switch 2 */
                var_r26 = 1;
                var_f30 = 5.497787f;
                break;
            }
            if (var_r26 != 0) {
                var_f29 = 3.1415927f;
                var_r28 = this;
                var_r26_2 = 0;
                var_r25 = 0;
                while (var_r25 < ((CReliveStage*)(M2C_FIELD(this, CReliveStage **, 0x33C)))->getDancerQuantity()) {
                    sp8 = ((SPokemonView*)(((u8*)(var_r28) + 0x340)))->getPosition();
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
                    var_r28 = var_r28 + 0x50;
                    var_r25 += 1;
                }
                if (var_r31 != var_r26_2) {
                    menuPtPlaySe(0x459U);
                }
                var_r31 = var_r26_2;
                M2C_FIELD(M2C_FIELD(this, CReliveStage **, 0x33C), u8 *, 0x3D4) = (u8) var_r26_2;
            }
        }
        updateAll();
    } while (var_r27 == 0);
    ((CMetaMenu*)((CMetaMenu *) this))->localWindowRemove(0x76);
    ((CInfoWindow*)((u8*)this + 0x80F8C))->close();
    *M2C_FIELD(this, s8 **, 0x80F64) = 1;
    M2C_FIELD(this, s8 *, 0x81135) = 0xFF;
}


void CMenuReliveHall::drawVisitorHitEffect()
{
    if (dancerPositionQuantityWithCatch()) {
        if (!getVisitorWithCatch()) return;
        if (stage->hit != -1) {
            drawStarHitEffect(320.0f, 280.0f, 1.5f * calcAnimationTimeRate0to1(1.5f));
        }
    }
}

void CMenuReliveHall::drawVisitorStarLight(long colorIdx, SPokemonView* v)
{
    f32 s;
    f32 r = 90.0f * calcAnimationTimeRate0to1(1.5f);
    PocketVec<short> p = v->getPosition();
    f32 dir = xyxy2dir(p, circlePosition);
    int j = 0;
    int k = 0;
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

void CMenuReliveHall::drawVsitorLine(long ci, SPokemonView* v)
{
    if (!views[6].hidden) {
        f32 ox;
        GSgfxColAu8 c = relivehallAisyou2ColorTbl[ci];
        s32 w = _aisyou2LineWidthHalfTable[ci].a;
        c.v[3] = c.v[3] * alphaA / 255;
        GSgfxColAu8 c1 = c;
        f32 py = v->getPosition().y;
        f32 px = v->getPosition().x;
        f32 dir = 1.5707964f + xy2dir(px - fcirclePosition.x, py - fcirclePosition.y);
        for (f32 k = 0.0f; k < (f32)w; k += 0.5f) {
            f32 o = k - (f32)(w / 2);
            ox = (f32)sin(dir);
            ox *= o;
            GSgfxColAu8 c2 = c;
            f32 oy = o * -(f32)cos(dir);
            PocketVec<f32> a = { fcirclePosition.x + ox, fcirclePosition.y + oy };
            PocketVec<f32> b = { px + ox, py + oy };
            GSprimDraw2DLine(&c2, &c1, a, b);
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
        long cur = cursor->index;
        if (cur >= stage->getDancerQuantity()) {
            long c2 = cursor->index;
            long k = (c2 - stage->getDancerQuantity()) + 1;
            if (i < k) return &views[i];
            if (i == k) return &views[c2];
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
    for (s8 i = 0; i < q; i++) {
        f32 a, b;
        int col;
        getCircleColorAisyou(a, b, col, (u8)i);
        for (int j = 0; j < 3; j++) {
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
        long x2;
        long x = (s32)(81.0f * (f32)sin(v.dir2) + (f32)v.getPosition().x);
        long y = (s32)(81.0f * -(f32)cos(v.dir2) + (f32)v.getPosition().y);
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
    PocketVec<short>* pos = markerPosB[0].x != -1 ? markerPosB : markerPosA;
    for (int i = 0; i <= 6; i++, pos++) {
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
            if (on && pos->x != -1) {
                if (flag) {
                    if (id == 0x294) menuPtSpriteDrawCenterColor(0x2E0, pos->x, pos->y, on | ~0xFF);
                } else {
                    menuPtSpriteDrawCenterColor(id, pos->x, pos->y, on | ~0xFF);
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
void CMenuReliveHall::actionMenuMain()
{
    static s32 yTbl[7] = { 0, 0, 0, 0x79, 0x64, 0, 0 };
    s32* list = actionList;
    s32 n = list[0];
    actionMenu((u32*)(list + 1), n, 0x1D7, yTbl[n], 0);
}
void CMenuReliveHall::animationStateUpdate() {
    CMenuReliveHall *var_r29;
    CMenuReliveHall *var_r29_2;
    u32 var_ctr;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 var_f31;
    f32 var_f31_3;
    f32 var_f31_2;
    f32 var_f0;
    f32 var_f1;
    f32 var_f30;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f29_2;
    s32 temp_r0_3;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r4;
    s32 var_ctr_2;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r28_2;
    s32 var_r6;
    s8 temp_r0_2;
    u32 temp_r0;
    CMenuReliveHall *var_r5;
    u32 var_r28;
    u32 temp_r0_4;
    u8 *var_r4;

    ((CState*)(this + 0x8108C))->update();
    temp_r0 = M2C_FIELD(this, u32 *, 0x8108C);
    switch (temp_r0) {
    case 0:
        if (M2C_FIELD(this, f32 *, 0x8109C) == 0.0f) {
            ((CMenuReliveHall*)(this))->animationDataReset();
            ((CMenuReliveHall*)(this))->resetStatusDisplayVisitor();
            ((CMenuPokemonCursor*)(M2C_FIELD((u16)this, CMenuPokemonCursor **, 0x80F64)))->setAnimationOff();
            ((CMenuReliveHall*)(this))->setCircleSw();
            return;
        }
    default:
        return;
    case 1:
        if (M2C_FIELD((s32)this, f32 *, 0x8109C) == 0.0f) {
            ((CMenuReliveHall*)(this))->animationDataReset();
        }
        var_f31 = 1.0f;
        temp_f0 = M2C_FIELD(this, f32 *, 0x8109C) / 0.6f;
        if (temp_f0 > 1.0f) {

        } else {
            var_f31 = temp_f0;
        }
        var_r29 = this;
        var_r28 = 0U;
        temp_r0_2 = (s8) (255.0f * var_f31);
        M2C_FIELD(this, s8 *, 0x81136) = temp_r0_2;
        M2C_FIELD(this, s8 *, 0x81138) = temp_r0_2;
        M2C_FIELD(this, s8 *, 0x81137) = temp_r0_2;
        M2C_FIELD(this, s8 *, 0x81135) = temp_r0_2;
        M2C_FIELD(this, s8 *, 0x81134) = temp_r0_2;
        do {
            ((SCircle*)(((u8*)(var_r29) + 0x62C)))->setFade((u8) M2C_FIELD(this, s8 *, 0x81134));
            var_r28 += 1;
            var_r29 += 0x2ADB8;
        } while (var_r28 < 3U);
        temp_r0_3 = M2C_FIELD(this, s32 *, 0x338);
        if (temp_r0_3 <= 3) {
            var_f30 = 5.585054f;
        } else if (temp_r0_3 == 4) {
            var_f30 = 0.08726647f;
        } else {
            var_f30 = 0.87266463f;
        }
        temp_r30 = ((CMenuReliveHall*)(this))->getQuantityMarkerDancerOnPlusDancerEmpty();
        temp_f1 = 7.5398235f * var_f31;
        if (temp_f1 < 6.2657323f) {
            temp_f29 = dirRefresh2PI(var_f30 - temp_f1);
            var_r29_2 = this;
            var_r28_2 = 0;
loop_19:
            if (var_r28_2 < temp_r30) {
                M2C_FIELD(var_r29_2, s8 *, 0x341) = (s8) (isDirRegionInReverseClockwise(dirRefresh2PI(M2C_FIELD(var_r29_2, f32 *, 0x344)), var_f30, temp_f29) == 0);
                var_r28_2 += 1;
                var_r29_2 += 0x50;
                goto loop_19;
            }
            M2C_FIELD((u16)this, s8 *, 0x521) = 1;
        } else {
            var_r6 = 0;
            if (temp_r30 > 0) {
                temp_r4 = temp_r30 - 8;
                if (temp_r30 > 8) {
                    var_r5 = this;
                    var_ctr = (u32) (temp_r4 + 7) >> 3U;
                    if (temp_r4 > 0) {
                        do {
                            M2C_FIELD(var_r5, s8 *, 0x341) = 0;
                            var_r6 += 8;
                            M2C_FIELD(var_r5, s8 *, 0x391) = 0;
                            M2C_FIELD(var_r5, s8 *, 0x3E1) = 0;
                            M2C_FIELD(var_r5, s8 *, 0x431) = 0;
                            M2C_FIELD(var_r5, s8 *, 0x481) = 0;
                            M2C_FIELD(var_r5, s8 *, 0x4D1) = 0;
                            M2C_FIELD(var_r5, s8 *, 0x521) = 0;
                            var_r5 += 0x280;
                            M2C_FIELD(var_r5, s8 *, 0x571) = 0;
                            var_ctr -= 1;
                        } while (var_ctr != 0);
                    }
                }
                var_r4 = (unsigned char *)(this + (var_r6 * 0x50));
                var_ctr_2 = temp_r30 - var_r6;
                if (var_r6 < temp_r30) {
                    do {
                        M2C_FIELD(var_r4, s8 *, 0x341) = 0;
                        var_r4 += 0x50;
                        var_ctr_2 -= 1;
                    } while (var_ctr_2 != 0);
                }
            }
        }
        if (var_f31 >= 1.0f) {
            M2C_FIELD(this, s32 *, 0x81090) = 0;
            memset((void*)(this + 0x810A4), 0, 0x40U);
            return;
        }
        break;
    case 2:
        if (M2C_FIELD((s32)this, f32 *, 0x8109C) == 0.0f) {
            M2C_FIELD(this, s8 *, 0x81137) = 0;
            M2C_FIELD(this, s8 *, 0x81184) = 1;
        }
        var_f31_2 = 1.0f;
        temp_f0_2 = M2C_FIELD(this, f32 *, 0x8109C) / 0.2f;
        if (temp_f0_2 < 1.0f) {
            var_f31_2 = temp_f0_2;
        }
        ((CMenuReliveHall*)(this))->dancerMoveAnimationAll(var_f31_2);
        if (var_f31_2 >= 1.0f) {
            M2C_FIELD(this, s32 *, 0x81090) = 3;
            memset((void*)(this + 0x810A4), 0, 0x40U);
        }
        M2C_FIELD(this, f32 *, 0x81188) = var_f31_2;
        return;
    case 3:
        var_r0 = (s32) ((255.0f * M2C_FIELD(this, f32 *, 0x8109C)) / 0.1f);
        if (var_r0 > 0xFF) {
            var_r0 = 0xFF;
        }
        M2C_FIELD(this, s8 *, 0x81137) = (s8) (u8) var_r0;
        if ((u8) M2C_FIELD(this, s8 *, 0x81137) >= 0xFFU) {
            M2C_FIELD(this, s32 *, 0x81090) = 0;
            memset((void*)((u8*)this + 0x810A4), 0, 0x40U);
            return;
        }
        break;
    case 4:
        temp_r3 = (s32) ((255.0f * M2C_FIELD(this, f32 *, 0x8109C)) / 0.1f);
        if (temp_r3 > 0xFF) {
            var_r0_2 = 0xFF;
        } else {
            var_r0_2 = temp_r3;
        }
        M2C_FIELD(this, s8 *, 0x81138) = (s8) (u8) var_r0_2;
        if (temp_r3 >= 0xFF) {
            M2C_FIELD(this, s32 *, 0x81090) = 0;
            memset((void*)((u8*)this + 0x810A4), 0, 0x40U);
            return;
        }
        break;
    case 5:
        if (M2C_FIELD((s32)this, f32 *, 0x8109C) == 0.0f) {
            M2C_FIELD(this, s8 *, 0x81137) = -1;
            M2C_FIELD(this, s8 *, 0x81138) = -1;
        }
        temp_r3_2 = (s32) ((255.0f * M2C_FIELD(this, f32 *, 0x8109C)) / 0.1f);
        if (temp_r3_2 > 0xFF) {
            var_r0_3 = 0xFF;
        } else {
            var_r0_3 = temp_r3_2;
        }
        temp_r0_4 = 0xFF - var_r0_3;
        M2C_FIELD(this, s8 *, 0x81138) = (s8) temp_r0_4;
        M2C_FIELD(this, s8 *, 0x81137) = (s8) temp_r0_4;
        if (temp_r3_2 >= 0xFF) {
            M2C_FIELD((u16)this, s32 *, 0x81090) = 0;
            memset((void*)((u8*)this + 0x810A4), 0, 0x40U);
            return;
        }
        break;
    case 6:
        if (M2C_FIELD((s32)this, f32 *, 0x8109C) == 0.0f) {
            M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), s32 *, 4) = 3;
        }
        var_f0 = 1.0f;
        temp_f29_2 = M2C_FIELD(this, f32 *, 0x8109C) / 0.1f;
        if (temp_f29_2 < 1.0f) {
            var_f0 = temp_f29_2;
        }
        M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), f32 *, 8) = var_f0;
        ((CMenuReliveHall*)(this))->setCircleSw();
        if (temp_f29_2 >= 1.0f) {
            M2C_FIELD(this, s32 *, 0x81090) = 0;
            memset((void*)((u8*)this + 0x810A4), 0, 0x40U);
            return;
        }
        break;
    case 7:
        if (M2C_FIELD((s32)this, f32 *, 0x8109C) == 0.0f) {
            M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), s32 *, 4) = 1;
            *((u8 *)this + ((M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), s32 *, 0xC) * 0x50) + 0x364)) = 1;
            M2C_FIELD(this, s8 *, 0x81184) = 1;
        }
        var_f31_3 = 1.0f;
        temp_f2 = M2C_FIELD(this, f32 *, 0x8109C) / 0.25f;
        if (temp_f2 < 1.0f) {
            var_f31_3 = temp_f2;
        }
        var_f1 = 1.0f;
        if (temp_f2 < 1.0f) {
            var_f1 = temp_f2;
        }
        M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), f32 *, 8) = var_f1;
        if (temp_f2 >= 1.0f) {
            M2C_FIELD(this, s32 *, 0x81090) = 0;
            memset((void*)(this + 0x810A4), 0, 0x40U);
        }
        M2C_FIELD(this, f32 *, 0x81188) = var_f31_3;
        break;
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
    ModelBank *var_r28;
    CReliveStage *temp_r3_4;
    CReliveStage *var_r3_2;
    ModelBank *var_r23;
    CReliveStage *temp_r30;
    ModelBank *var_r29;
    Pokemon *temp_r3_3;
    s32 temp_r24;
    s32 var_r20;
    s32 var_r21;
    s32 var_r3;
    u32 var_r22;
    u32 temp_r3;
    u8 temp_r3_5;
    u8 *temp_r3_2;

    var_r3_2 = ((CReliveHall*)(((CReliveHall*)((CReliveHall *) this))->getPointer(), (M2C_FIELD(this, s32 *, 0x338))))->getStage((long)(0));
    var_r29 = NULL;
    temp_r30 = var_r3_2;
    var_r28 = NULL;
    if (p1 != 0) {
        var_r28 = (ModelBank *)(GSmemAllocClr(0x3D8U));
        var_r29 = (ModelBank *)(GSmemAllocClr(0x3D8U));
        temp_r3 = (unsigned long)(((CReliveStage*)(temp_r30))->getDancerPointer((s32) (u8) M2C_FIELD(temp_r30, u8 *, 0x3D4)));
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
        M2C_FIELD(var_r29, u8 *, 0x3D4) = (u8) var_r21;
        memcpy((void*)(var_r28), (const void*)(temp_r30), 0xC4U);
        memcpy((void*)(((u8*)(var_r28) + 0xC4)), (const void*)(((u8*)((u16)temp_r30) + 0xC4)), 0xC4U);
        memcpy((void*)(((u8*)(var_r28) + 0x188)), (const void*)(((u8*)((u16)temp_r30) + 0x188)), 0xC4U);
        memcpy((void*)(((u8*)(var_r28) + 0x24C)), (const void*)(((u8*)((u16)temp_r30) + 0x24C)), 0xC4U);
        memcpy((void*)(((u8*)(var_r28) + 0x310)), (const void*)(((u8*)((u16)temp_r30) + 0x310)), 0xC4U);
        M2C_FIELD(var_r28, u8 *, 0x3D4) = (u8) M2C_FIELD(temp_r30, u8 *, 0x3D4);
        memcpy((void*)(temp_r30), (const void*)(var_r29), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0xC4)), (const void*)(((u8*)(var_r29) + 0xC4)), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0x188)), (const void*)(((u8*)(var_r29) + 0x188)), 0xC4U);
        memcpy((void*)(((u8*)(temp_r30) + 0x24C)), (const void*)(((u8*)(var_r29) + 0x24C)), 0xC4U);
        var_r3_2 = (CReliveStage *)(memcpy((void*)(((u8*)(temp_r30) + 0x310)), (const void*)(((u8*)(var_r29) + 0x310)), 0xC4U));
        M2C_FIELD(temp_r30, u8 *, 0x3D4) = (u8) M2C_FIELD(var_r29, u8 *, 0x3D4);
    }
    temp_r3_4 = ((CReliveHall*)(((CReliveHall*)((CReliveHall *) var_r3_2))->getPointer(), (M2C_FIELD(this, s32 *, 0x338))))->getStage((long)(0));
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


f32 CMenuReliveHall::getDirToAisyou(f32 dir)
{
    int n = dancerPositionQuantityWithCatch();
    for (s8 i = 0; i < n; i++) {
        SPokemonView* a = getPokemonViewByClockwizePositionWithCatch(i);
        SPokemonView* b = getPokemonViewByClockwizePositionWithCatch((i + 1) % n);
        if (isDirRegionIn(dir, a->dir, b->dir)) {
            return pokemonToAisyou(a->getPokemonWithPickupOverride(), (Pokemon*)(b->getPokemonWithPickupOverride()));
        }
    }
    return -1;
}

void CMenuReliveHall::getCircleColorAisyou(f32& a, f32& b, int& color, int idx)
{
    int n = dancerPositionQuantityWithCatch();
    SPokemonView* va = getPokemonViewByClockwizePositionWithCatch(idx);
    SPokemonView* vb = getPokemonViewByClockwizePositionWithCatch((idx + 1) % n);
    Pokemon* pb = vb->getPokemonWithPickupOverride();
    a = va->dir;
    color = pokemonToAisyou(va->getPokemonWithPickupOverride(), pb);
    volatile GSgfxColAu8 c = relivehallAisyou2ColorTbl[color];
    b = vb->dir;
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
void _cbMenuPokemonStatus(Pokemon*, MENU_POKEMON_CB_TYPE, long);

void CMenuReliveHall::stateDirChangeWinDraw(long win)
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

void _stateDirChangeProcHook(CMetaMenu* m, long win)
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

void _cbMenuPokemonStatus(Pokemon* p, MENU_POKEMON_CB_TYPE t, long n)
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
            int d = degreeSubHalf((u16)dir, xyxy2dirDegree(pos[i], cur));
            if (d <= 0) d = -d;
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
        anim.next = 6;
        memset(anim.work, 0, 0x40);
    }
}


bool CMenuReliveHall::animationProcessButtonInterrupt()
{
    if (anim.current != 0) {
        anim.next = 0;
        memset(anim.work, 0, 0x40);
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
void CMenuReliveHall::cursorPositionDecideAtStageChange(int p0) {
    u8 var_r29_4;
    CMenuPokemonCursor *temp_r30_3;
    CMenuPokemonCursor *temp_r30_2;
    CMenuPokemonCursor *temp_r30_5;
    CMenuReliveHall *temp_r31;
    CMenuReliveHall *var_r3;
    Pokemon *var_r3_2;
    Pokemon *var_r3_3;
    Pokemon *var_r3_4;
    Pokemon *var_r3_5;
    Pokemon *var_r3_6;
    s32 temp_r3;
    s32 var_r28;
    s32 var_r29;
    u8 var_r0;
    u8 var_r29_2;
    u8 var_r29_3;
    CMenuPokemonCursor *temp_r30_4;
    u8 var_r29_5;
    u8 var_r29_6;

    var_r3 = this;
    temp_r31 = var_r3;
    if ((p0 == -1) && (var_r3 = M2C_FIELD(temp_r31, CMenuReliveHall **, 0x328), (((s32) M2C_FIELD(var_r3, s32 *, 4) == 1) != 0))) {
        var_r28 = 7;
    } else {
        var_r29 = -1;
        if (p0 != -1) {
            var_r29 = ((CReliveStage*)(((CReliveHall*)(((CReliveHall*)((CReliveHall *) var_r3))->getPointer(), p0))->getStage((long)(0))))->getDancerQuantity();
        }
        temp_r3 = M2C_FIELD(M2C_FIELD((s32)temp_r31, CMenuPokemonCursor **, 0x80F64), s32 *, 0xC);
        var_r28 = temp_r3;
        if (temp_r3 == 6) {
            if (((CReliveStage*)(M2C_FIELD(temp_r31, CReliveStage **, 0x33C)))->getVisitorPointer() == 0) {
                var_r29_2 = 0;
                if (((CMenuPokemonCursor*)(M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() != 0) {
                    if (((Pokemon*)(((u8*)((M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64))) + 0x20)))->checkValid() != 0) {
                        var_r3_2 = (Pokemon *)(((u8*)((M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64))) + 0x20));
                    } else {
                        var_r3_2 = NULL;
                    }
                    if (((Pokemon*)(var_r3_2))->isDarkPokemon() != 0) {
                        var_r29_2 = 1;
                    }
                }
                if (var_r29_2 == 0) {
                    var_r28 = -1;
                }
            }
        } else {
            var_r0 = 0;
            if ((temp_r3 >= 0) && (temp_r3 <= 5)) {
                var_r0 = 1;
            }
            if ((var_r0 != 0) && (var_r29 != ((CReliveStage*)(M2C_FIELD(temp_r31, CReliveStage **, 0x33C)))->getDancerQuantity())) {
                var_r28 = -1;
            }
        }
        if (var_r28 == -1) {
            var_r29_3 = 0;
            if (((CMenuPokemonCursor*)(M2C_FIELD((u16)temp_r31, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() != 0) {
                temp_r30_2 = M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64);
                if (((Pokemon*)(((u8*)((s32)temp_r30_2) + 0x20)))->checkValid() != 0) {
                    var_r3_3 = (Pokemon *)(((u8*)(temp_r30_2) + 0x20));
                } else {
                    var_r3_3 = NULL;
                }
                if (((Pokemon*)(var_r3_3))->isDarkPokemon() == 0) {
                    var_r29_3 = 1;
                }
            }
            if ((var_r29_3 != 0) || (((CReliveStage*)(M2C_FIELD(temp_r31, CReliveStage **, 0x33C)))->getVisitorPointer() == 0)) {
                var_r29_4 = 0;
                if (((CMenuPokemonCursor*)(M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() != 0) {
                    temp_r30_3 = M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64);
                    if (((Pokemon*)(((u8*)((s32)temp_r30_3) + 0x20)))->checkValid() != 0) {
                        var_r3_4 = (Pokemon *)(((u8*)(temp_r30_3) + 0x20));
                    } else {
                        var_r3_4 = NULL;
                    }
                    if (((Pokemon*)(var_r3_4))->isDarkPokemon() != 0) {
                        var_r29_4 = 1;
                    }
                }
                if (var_r29_4 != 0) {
                    goto block_37;
                }
                var_r29_5 = 0;
                if (((CMenuPokemonCursor*)(M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() != 0) {
                    temp_r30_4 = M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64);
                    if (((Pokemon*)(((u8*)((s32)temp_r30_4) + 0x20)))->checkValid() != 0) {
                        var_r3_5 = (Pokemon *)(((u8*)(temp_r30_4) + 0x20));
                    } else {
                        var_r3_5 = NULL;
                    }
                    if (((Pokemon*)(var_r3_5))->isDarkPokemon() != 0) {
                        var_r29_5 = 1;
                    }
                }
                if ((var_r29_5 != 0) || (((CReliveStage*)(M2C_FIELD(temp_r31, CReliveStage **, 0x33C)))->getDancerQuantity() == 0)) {
                    var_r29_6 = 0;
                    if (((CMenuPokemonCursor*)(M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() != 0) {
                        temp_r30_5 = M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64);
                        if (((Pokemon*)(((u8*)((u16)temp_r30_5) + 0x20)))->checkValid() != 0) {
                            var_r3_6 = (Pokemon *)(((u8*)(temp_r30_5) + 0x20));
                        } else {
                            var_r3_6 = NULL;
                        }
                        if (((Pokemon*)(var_r3_6))->isDarkPokemon() == 0) {
                            var_r29_6 = 1;
                        }
                    }
                    if (var_r29_6 != 0) {
                        goto block_53;
                    }
                    var_r28 = 7;
                } else {
block_53:
                    var_r28 = 0;
                }
            } else {
block_37:
                var_r28 = 6;
            }
        }
    }
    ((CMenuPokemonCursor*)(M2C_FIELD(temp_r31, CMenuPokemonCursor **, 0x80F64)))->setPositionIndex(var_r28);
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
    anim.next = 1;
    memset(anim.work, 0, 0x40);
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
    pokemonInit((u32)statusVisitor);
    statusSet = 0;
}
void CMenuReliveHall::aButtomAction() {
    u8 var_r28;
    CMenuPokemonCursor *temp_r3;
    Pokemon *var_r3;
    Pokemon *var_r3_2;
    s32 temp_r0;
    s32 temp_r28;
    s32 temp_r28_2;
    u8 temp_r30_2;
    u8 var_r27;
    CMenuPokemonCursor *temp_r28_3;
    u8 *var_r0;
    u8 *var_r0_2;
    u8 *var_r0_3;

    memset((void*)(this + 0x614), 0, 0xCU);
    M2C_FIELD(this, s32 *, 0x618) = -1;
    M2C_FIELD(this, s32 *, 0x61C) = -1;
    temp_r3 = M2C_FIELD((s32)this, CMenuPokemonCursor **, 0x80F64);
    temp_r0 = M2C_FIELD(temp_r3, s32 *, 0xC);
    switch (temp_r0) {                              /* irregular */
    default:
        var_r28 = 0;
        if (((CMenuPokemonCursor*)(temp_r3))->isCatchPokemon() != 0) {
            if (((Pokemon*)(((u8*)((M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64))) + 0x20)))->checkValid() != 0) {
                var_r3 = (Pokemon *)(((u8*)((M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64))) + 0x20));
            } else {
                var_r3 = NULL;
            }
            if (((Pokemon*)(var_r3))->isDarkPokemon() == 0) {
                var_r28 = 1;
            }
        }
        if (var_r28 != 0) {
            temp_r28 = M2C_FIELD(M2C_FIELD((u16)this, CMenuPokemonCursor **, 0x80F64), s32 *, 0xC);
            if (temp_r28 < ((CReliveStage*)(M2C_FIELD((u16)this, CReliveStage **, 0x33C)))->getDancerQuantity()) {
                if ((u8) M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), u8 *, 0x14C) != 0) {
                    ((CMenuReliveHall*)(this))->actionChange();
                } else {
                    M2C_FIELD(this, u8 **, 0x614) = (u8 *) (&relivehallAisyou2ColorTbl + 0x238);
                }
            } else if ((u8) M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), u8 *, 0x14C) != 0) {
                ((CMenuReliveHall*)(this))->actionPut();
            } else {
                M2C_FIELD(this, u8 **, 0x614) = (u8 *) (&relivehallAisyou2ColorTbl + 0x268);
            }
        } else {
            temp_r28_2 = M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), s32 *, 0xC);
            if (temp_r28_2 < ((CReliveStage*)(M2C_FIELD(this, CReliveStage **, 0x33C)))->getDancerQuantity()) {
                if ((u8) M2C_FIELD(M2C_FIELD((u16)this, CMenuPokemonCursor **, 0x80F64), u8 *, 0x14C) != 0) {
                    ((CMenuReliveHall*)(this))->actionPickup();
                } else {
                    M2C_FIELD(this, u8 **, 0x614) = (u8 *) (&relivehallAisyou2ColorTbl + 0x298);
                }
            }
        }
        break;
    case 6:
        temp_r30_2 = ((CReliveStage*)(M2C_FIELD(this, CReliveStage **, 0x33C)))->getDancerQuantity() >= 2;
        var_r27 = 0;
        if (((CMenuPokemonCursor*)(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() != 0) {
            temp_r28_3 = M2C_FIELD((u16)this, CMenuPokemonCursor **, 0x80F64);
            if (((Pokemon*)(((u8*)(temp_r28_3) + 0x20)))->checkValid() != 0) {
                var_r3_2 = (Pokemon *)(((u8*)(temp_r28_3) + 0x20));
            } else {
                var_r3_2 = NULL;
            }
            if (((Pokemon*)(var_r3_2))->isDarkPokemon() != 0) {
                var_r27 = 1;
            }
        }
        if (var_r27 != 0) {
            if ((u32) M2C_FIELD(this, u32 *, 0x530) != 0U) {
                if ((u8) M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), u8 *, 0x14C) != 0) {
                    ((CMenuReliveHall*)(this))->actionChange();
                } else {
                    if (temp_r30_2 != 0) {
                        var_r0 = (unsigned char *)(&relivehallAisyou2ColorTbl + 0x220);
                    } else {
                        var_r0 = (unsigned char *)(&relivehallAisyou2ColorTbl + 0x238);
                    }
                    M2C_FIELD(this, u8 **, 0x614) = var_r0;
                }
            } else if ((u8) M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), u8 *, 0x14C) != 0) {
                ((CMenuReliveHall*)(this))->actionPut();
            } else {
                if ((s32) temp_r30_2 != 0) {
                    var_r0_2 = (unsigned char *)(&relivehallAisyou2ColorTbl + 0x250);
                } else {
                    var_r0_2 = (unsigned char *)(&relivehallAisyou2ColorTbl + 0x268);
                }
                M2C_FIELD(this, u8 **, 0x614) = var_r0_2;
            }
        } else if ((u32) M2C_FIELD(this, u32 *, 0x530) != 0U) {
            if ((u8) M2C_FIELD(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64), u8 *, 0x14C) != 0) {
                ((CMenuReliveHall*)(this))->actionPickup();
            } else {
                if ((s32) temp_r30_2 != 0) {
                    var_r0_3 = (unsigned char *)(&relivehallAisyou2ColorTbl + 0x280);
                } else {
                    var_r0_3 = (unsigned char *)(&relivehallAisyou2ColorTbl + 0x298);
                }
                M2C_FIELD(this, u8 **, 0x614) = var_r0_3;
            }
        }
        break;
    case 7:
        M2C_FIELD(this, s32 *, 0x27C) = 6;
        memset((void*)((u8*)this + 0x290), 0, 0x40U);
        break;
    case 8:
        M2C_FIELD(this, s32 *, 0x27C) = 8;
        memset((void*)((u8*)this + 0x290), 0, 0x40U);
        break;
    }
    if ((u8 *) M2C_FIELD(this, u8 **, 0x614) != NULL) {
        M2C_FIELD(this, s32 *, 0x27C) = 3;
        memset((void*)((u8*)this + 0x290), 0, 0x40U);
    }
}
void CMenuReliveHall::stateMainProc() {
    CMenuPokemonCursor *temp_r3_2;
    CReliveHall *temp_r3;
    CReliveHall *temp_r3_3;
    CReliveHall *temp_r3_4;
    u16 temp_r0;
    u16 temp_r0_2;
    u32 temp_r26;
    bool temp_r31;
    u8 var_r26;
    s32 var_r29;
    u8 *temp_r30;

    memset((void*)((u8*)this + 0x620), 0, 0xCU);
    temp_r30 = (unsigned char *)((u8*)this + 0x290);
    var_r29 = 0;
loop_65:
    if (var_r29 == 0) {
        temp_r3 = (CReliveHall *)(((CMetaMenu*)((CMetaMenu *) this))->getKeyInfo());
        temp_r31 = ((CReliveHall*)(((CReliveHall*)(temp_r3))->getPointer()))->isReliveReadyDarkLugiaExist();
        temp_r26 = (M2C_FIELD(temp_r3, u16 *, 4) | M2C_FIELD(temp_r3, u16 *, 6)) != 0;
        if (((temp_r26 == 0) && ((u8) M2C_FIELD((s32)this, u8 *, 0x620) == 0)) || (((CMenuReliveHall*)(this))->animationProcessButtonInterrupt() == 0)) {
            if ((u8) M2C_FIELD((s32)this, u8 *, 0x620) != 0) {
                ((CMenuReliveHall*)(this))->cursorMoveDir((s32) ((180.0f * M2C_FIELD(this, f32 *, 0x624)) / 3.1415927f));
            } else if (((u8) M2C_FIELD(this, u8 *, 0x621) == 0) && (temp_r26 != 0)) {
                temp_r0 = M2C_FIELD(temp_r3, u16 *, 6);
                var_r26 = 0;
                switch ((s32) temp_r0) {            /* switch 1; irregular */
                case 0x1:                           /* switch 1 */
                    ((CMenuReliveHall*)(this))->cursorMoveDir(0);
                    break;
                case 0x8:                           /* switch 1 */
                    ((CMenuReliveHall*)(this))->cursorMoveDir(0x5A);
                    break;
                case 0x2:                           /* switch 1 */
                    ((CMenuReliveHall*)(this))->cursorMoveDir(0xB4);
                    break;
                case 0x4:                           /* switch 1 */
                    ((CMenuReliveHall*)(this))->cursorMoveDir(0x10E);
                    break;
                case 0x9:                           /* switch 1 */
                    ((CMenuReliveHall*)(this))->cursorMoveDir(0x2D);
                    break;
                case 0xA:                           /* switch 1 */
                    ((CMenuReliveHall*)(this))->cursorMoveDir(0x87);
                    break;
                case 0x6:                           /* switch 1 */
                    ((CMenuReliveHall*)(this))->cursorMoveDir(0xE1);
                    break;
                case 0x5:                           /* switch 1 */
                    ((CMenuReliveHall*)(this))->cursorMoveDir(0x13B);
                    break;
                case 0x200:                         /* switch 1 */
                    ((CMenuReliveHall*)(this))->moveStage(-1);
                    break;
                case 0x400:                         /* switch 1 */
                    ((CMenuReliveHall*)(this))->moveStage(1);
                    break;
                default:                            /* switch 1 */
                    var_r26 = 1;
                    break;
                }
                if (var_r26 != 0) {
                    temp_r0_2 = M2C_FIELD(temp_r3, u16 *, 4);
                    switch ((s32) temp_r0_2) {      /* switch 2; irregular */
                    case 0x10:                      /* switch 2 */
                        if (((CMenuPokemonCursor*)(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() == 0) {
                            menuPtPlaySe(0x45AU);
                        }
                        ((CMenuReliveHall*)((s32)this))->aButtomAction();
                        var_r29 = 1;
                        break;
                    case 0x20:                      /* switch 2 */
                        if (((CMenuPokemonCursor*)(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() == 0) {
                            menuPtPlaySe(0x45BU);
                        }
                        M2C_FIELD(this, s32 *, 0x27C) = 8;
                        memset((void*)(temp_r30), 0, 0x40U);
                        var_r29 = 1;
                        break;
                    case 0x40:                      /* switch 2 */
                    case 0x80:                      /* switch 2 */
                        temp_r3_2 = M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64);
                        M2C_FIELD(temp_r3_2, u8 *, 0x14C) = (u8) (M2C_FIELD(temp_r3_2, u8 *, 0x14C) == 0);
                        break;
                    case 0x100:                     /* switch 2 */
                        menuPtPlaySe(0x45AU);
                        M2C_FIELD(this, s32 *, 0x27C) = 6;
                        memset((void*)(temp_r30), 0, 0x40U);
                        break;
                    }
                }
            }
            updateAll();
            if ((temp_r31 == 0) && (CReliveHall::getPointer()->isReliveReadyDarkLugiaExist() != 0)) {
                ((CMenuReliveHall*)(this))->infoMessageDisplay(0xD152U);
            }
            temp_r3_4 = (CReliveHall *)(darkPokemonGetDarkPokemon(0x49U));
            if (((CReliveHall*)(((CReliveHall*)(temp_r3_4))->getPointer()))->isReliveReadyDarkLugiaExist() != 0) {
                ((DarkPokemon*)((DarkPokemon *) temp_r3_4))->setDarkPointDirect(0);
            } else if (((DarkPokemon*)((DarkPokemon *) temp_r3_4))->getStatus() == 4) {
                ((DarkPokemon*)((DarkPokemon *) temp_r3_4))->setDarkPointDirect(0);
            } else {
                ((DarkPokemon*)((DarkPokemon *) temp_r3_4))->setDarkPointDirect(((DarkPokemon*)((DarkPokemon *) temp_r3_4))->getInitDarkPointDirect());
            }
            if ((s32) M2C_FIELD(this, s32 *, 0x27C) == -1) {
                goto loop_65;
            }
        }
    }
}
void CMenuReliveHall::loop() {
    enum TsE { TsE0 };
    goto loop_1;
    s32 spC;
    u32 sp8;
    CReliveHall *temp_r3_2;
    CReliveHall *temp_r3_3;
    CReliveHall *temp_r3_4;
    CReliveHall *temp_r4;
    CReliveHall *temp_r4_2;
    enum TsE temp_r29;
    s32 temp_r29_3;
    s32 temp_r31_2;
    s32 temp_r3;
    s32 var_r29;
    u32 temp_r0;
    u32 var_r4;
    bool temp_r29_2;
    u8 *temp_r31;

    temp_r31 = (unsigned char *)((u8*)this + 0x290);
sw0_c0:;
loop_1:
    ((CState*)(this + 0x278))->update();
    temp_r0 = M2C_FIELD(this, u32 *, 0x278);
    if (temp_r0 > 9U) {
    }
    switch (temp_r0) { case 0: goto sw0_c0; case 1: goto sw0_c1; case 2: goto sw0_c2; case 3: goto sw0_c3; case 4: goto sw0_c4; case 5: goto sw0_c5; case 6: goto sw0_c6; case 7: goto sw0_c7; case 8: goto sw0_c8; case 9: goto sw0_c9; default: break; }                               /* jump table: jtbl_5214 */
sw0_c1:;
    M2C_FIELD(this, s32 *, 0x27C) = 2;
    memset((void*)((s32)temp_r31), 0, 0x40U);
    lbl_804EA7F0 = M2C_FIELD(M2C_FIELD(this, CReliveHall **, 0x328), s32 *, 4) == 3;
    goto loop_1;
sw0_c2:;
    ((CMenuReliveHall*)((s32)this))->stateMainProc();
    goto loop_1;
sw0_c3:;
    ((CInfoWindow*)(this + 0x80F8C))->setMsgCtrlValue(0x32U, (unsigned long)(((Pokemon*)(((CMenuReliveHall*)(this))->getCurrentPokemonPointer()))->getNicknamePtr()));
    ((CInfoWindow*)(this + 0x80F8C))->open(0xD110U, 0U);
    ((CMenuReliveHall*)(this))->actionMenuMain();
    temp_r29 = (enum TsE)(0);
    ((CInfoWindow*)(this + 0x80F8C))->close();
    temp_r29_2 = CReliveHall::getPointer()->isReliveReadyDarkLugiaExist();
    ((CMenuReliveHall*)(this))->actionDecide(*(M2C_FIELD(this, s32 **, 0x614) + ((temp_r29 * 4) + 4)));
    temp_r3 = 0;
    if (temp_r29_2 != 0) {
        goto block_8;
    }
    if (((CReliveHall*)(((CReliveHall*)((CReliveHall *) temp_r3))->getPointer()))->isReliveReadyDarkLugiaExist() == 0) {
        goto block_8;
    }
    ((CMenuReliveHall*)(this))->infoMessageDisplay(0xD152U);
block_8:
    temp_r3_2 = (CReliveHall *)(darkPokemonGetDarkPokemon(0x49U));
    if (((CReliveHall*)(((CReliveHall*)(temp_r3_2))->getPointer()))->isReliveReadyDarkLugiaExist() == 0) {
        goto block_10;
    }
    ((DarkPokemon*)((DarkPokemon *) temp_r3_2))->setDarkPointDirect(0);
    goto loop_1;
block_10:
    if (((DarkPokemon*)((DarkPokemon *) temp_r3_2))->getStatus() != 4) {
        goto block_12;
    }
    ((DarkPokemon*)((DarkPokemon *) temp_r3_2))->setDarkPointDirect(0);
    goto loop_1;
block_12:
    ((DarkPokemon*)((DarkPokemon *) temp_r3_2))->setDarkPointDirect(((DarkPokemon*)((DarkPokemon *) temp_r3_2))->getInitDarkPointDirect());
    goto loop_1;
sw0_c4:;
    ((CMenuReliveHall*)(this))->actionStatus();
    M2C_FIELD(this, s32 *, 0x27C) = 2;
    memset((void*)(temp_r31), 0, 0x40U);
    goto loop_1;
sw0_c5:;
    ((CMenuReliveHall*)(this))->stateDirChangeProc();
    M2C_FIELD(this, s32 *, 0x27C) = 2;
    memset((void*)(temp_r31), 0, 0x40U);
    goto loop_1;
sw0_c6:;
    ((CMetaMenu*)((CMetaMenu *) this))->alphaFadeOutAndWait();
    temp_r4 = M2C_FIELD(this, CReliveHall **, 0x328);
    M2C_FIELD(temp_r4, s32 *, 4) = (s32) M2C_FIELD(temp_r4, s32 *, 8);
    M2C_FIELD(temp_r4, s32 *, 8) = 1;
    return;
sw0_c7:;
    menuPtPlaySe(0x13U);
    ((CMenuReliveHall*)(this))->infoMessageDisplay(0xD11BU);
    M2C_FIELD(this, s32 *, 0x27C) = 2;
    memset((void*)(temp_r31), 0, 0x40U);
    goto loop_1;
sw0_c8:;
    if ((u8) M2C_FIELD(M2C_FIELD(this, CReliveHall **, 0x328), u8 *, 0x15D) == 0) {
        goto block_19;
    }
    M2C_FIELD(this, s32 *, 0x27C) = 9;
    memset((void*)(temp_r31), 0, 0x40U);
    goto loop_1;
block_19:
    if (((CMenuPokemonCursor*)(M2C_FIELD(this, CMenuPokemonCursor **, 0x80F64)))->isCatchPokemon() == 0) {
        goto block_21;
    }
    M2C_FIELD(this, s32 *, 0x27C) = 7;
    memset((void*)(temp_r31), 0, 0x40U);
    goto loop_1;
block_21:
    sp8 = M2C_FIELD(&jtbl_2171, u32 *, 0);
    spC = M2C_FIELD(&jtbl_2171, s32 *, 4);
    if ((s32) M2C_FIELD(M2C_FIELD(this, CReliveHall **, 0x328), s32 *, 4) != 3) {
        goto block_23;
    }
    var_r4 = 0xD15B;
    goto block_24;
block_23:
    var_r4 = 0xD124;
block_24:
    ((CInfoWindow*)(this + 0x80F8C))->open(var_r4, 0U);
    temp_r29_3 = ((CMetaMenu*)((CMetaMenu *) this))->actionMenu((unsigned long*)(&sp8), 2, 0x1FB, 0x8C, 0);
    ((CInfoWindow*)(this + 0x80F8C))->close();
    if (temp_r29_3 != 0) {
        goto block_26;
    }
    M2C_FIELD(this, s32 *, 0x27C) = 2;
    memset((void*)(temp_r31), 0, 0x40U);
    goto loop_1;
block_26:
    M2C_FIELD(this, s32 *, 0x27C) = 9;
    memset((void*)(temp_r31), 0, 0x40U);
    goto loop_1;
sw0_c9:;
    temp_r3_3 = M2C_FIELD(this, CReliveHall **, 0x328);
    var_r29 = 0;
    if ((s32) M2C_FIELD(temp_r3_3, s32 *, 0) == 3) {
        goto block_33;
    }
    if (((CReliveHall*)(((CReliveHall*)(temp_r3_3))->getPointer()))->isReliveReadyPokemonExist() == 0) {
        goto block_33;
    }
    temp_r3_4 = M2C_FIELD(this, CReliveHall **, 0x328);
    temp_r31_2 = M2C_FIELD(temp_r3_4, s32 *, 0);
    if (((PCBOX*)(((PCBOX*)((PCBOX *) temp_r3_4))->getPointer()))->isPokemonFull() == 0) {
        goto block_32;
    }
    ((CMenuReliveHall*)(this))->infoMessageDisplay3Line(0xD12FU);
    if (temp_r31_2 != 2) {
        goto block_33;
    }
    var_r29 = 4;
    goto block_33;
block_32:
    ((CMenuReliveHall*)(this))->infoMessageDisplay3Line(0xD0FDU);
block_33:
    temp_r4_2 = M2C_FIELD(this, CReliveHall **, 0x328);
    M2C_FIELD(temp_r4_2, s32 *, 4) = (s32) M2C_FIELD(temp_r4_2, s32 *, 8);
    M2C_FIELD(temp_r4_2, s32 *, 8) = var_r29;
    ((CMetaMenu*)((CMetaMenu *) this))->systemFadeOutSetAndWait(-1.0f);
    return;
}






void CMenuReliveHall::setStatusDisplayVisitor(Pokemon* p)
{
    statusSet = 1;
    if (p == 0) {
        pokemonInit((u32)statusVisitor);
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
    modelA = GSresGetResource(g, scriptA);
    GSmodelStopTexAnimation(modelA);
    scriptB = scriptModelOpen(0x18041001);
    modelB = GSresGetResource(g, scriptB);
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

void _menuDrawReliveMeter(Pokemon* p, long x, long y, long w, long h, u8 a, GSgfxLayerID layer, long i)
{
    menuDrawReliveMeter3(p, x, y, w, h, a, layer);
}

u8 rate01ToAlphaFrom50(f32 r)
{
    return (u8)(205.0f * r + 50.0f);
}
}

namespace {
void CStick::update()
{
    prev = cur;
    s8 ry = GSinputGetRightStickYData(1, 0);
    s8 lx = GSinputGetLeftStickXData(1, 0);
    s8 ly = GSinputGetLeftStickYData(1, 0);
    s8 rx = GSinputGetRightStickXData(1, 0);
    s8 t;
    dir = 0.0f;
    if (t < 0) t = -t;
    t = lx;
    if (t > 0x20) {
        dir = xy2dir((f32)lx, (f32)ly);
        cur = 1;
    } else {
        if (t < 0) t = -t;
        t = ly;
        if (t > 0x20) {
            dir = xy2dir((f32)lx, (f32)ly);
            cur = 1;
        } else {
            t = rx;
            if (t < 0) t = -t;
            if (t > 0x16) {
                dir = xy2dir((f32)rx, (f32)ry);
                cur = 1;
            } else {
                if (t < ry) t = ry;
                if (t < 0) t = -t;
                if (t > 0x16) {
                    dir = xy2dir((f32)rx, (f32)ry);
                    cur = 1;
                } else {
                    cur = 0;
                }
            }
        }
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
        msgctrlSetValue(0x32, (u32)v->getNicknamePtr());
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
        state.next = 5;
        memset(state.work, 0, 0x40);
        break;
    case 0xD113:
        state.next = 4;
        memset(state.work, 0, 0x40);
        break;
    case 0xD115:
        actionPut();
        break;
    case 0xD116:
        actionPickup();
        break;
    }
    if (state.next == -1) {
        state.next = 2;
        memset(state.work, 0, 0x40);
    }
}

void CMenuReliveHall::dancerMoveAnimationOne(SPokemonView& v, f32 t)
{
    f32 p = t * dirSubHalf(v.dirTo, v.dirFrom);
    v.dir = p + v.dirFrom;
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
    int idx = c->index;
    u8 in = 0;
    if (stage->getDancerQuantity() <= idx && cursor->index <= 5) in = 1;
    if (in) dancerMoveAnimationOne(views[cursor->index], t);
    setCircleSw();
    makeCursorPositionTbl(markerPosA);
}
void CMenuReliveHall::dancerMoveAnimationKick(f32* p0, f32* p1, bool p2, f32 p3) {
    u32 var_ctr;
    CMenuReliveHall *var_r5;
    f32 *var_r6;
    f32 *var_r7;
    f32 temp_f0;
    f32 temp_f0_10;
    f32 temp_f0_11;
    f32 temp_f0_12;
    f32 temp_f0_13;
    f32 temp_f0_14;
    f32 temp_f0_15;
    f32 temp_f0_16;
    f32 temp_f0_17;
    f32 temp_f0_18;
    f32 temp_f0_19;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    s32 temp_r3;
    s32 temp_r4;
    s32 var_ctr_2;
    s32 var_r8;
    u8 *temp_r3_2;
    u8 *var_r4;
    f32 *var_r6_2;
    f32 *var_r5_2;

    temp_r3 = ((CReliveStage*)(M2C_FIELD(this, CReliveStage **, 0x33C)))->getDancerQuantity();
    var_r8 = 0;
    if (temp_r3 > 0) {
        temp_r4 = temp_r3 - 8;
        if (temp_r3 > 8) {
            var_r5 = this;
            var_r6 = p0;
            var_r7 = p1;
            var_ctr = (temp_r4 + 7) >> 3U;
            if (temp_r4 > 0) {
                do {
                    var_r8 += 8;
                    M2C_FIELD(var_r5, f32 *, 0x348) = (f32) M2C_FIELD(var_r5, f32 *, 0x344);
                    temp_f0 = M2C_FIELD(var_r6, f32 *, 0);
                    M2C_FIELD(var_r5, f32 *, 0x34C) = temp_f0;
                    M2C_FIELD(var_r5, f32 *, 0x344) = temp_f0;
                    M2C_FIELD(var_r5, f32 *, 0x388) = (f32) M2C_FIELD(var_r5, f32 *, 0x384);
                    temp_f0_2 = M2C_FIELD(var_r7, f32 *, 0);
                    M2C_FIELD(var_r5, f32 *, 0x38C) = temp_f0_2;
                    M2C_FIELD(var_r5, f32 *, 0x384) = temp_f0_2;
                    M2C_FIELD(var_r5, f32 *, 0x398) = (f32) M2C_FIELD(var_r5, f32 *, 0x394);
                    temp_f0_3 = M2C_FIELD(var_r6, f32 *, 4);
                    M2C_FIELD(var_r5, f32 *, 0x39C) = temp_f0_3;
                    M2C_FIELD(var_r5, f32 *, 0x394) = temp_f0_3;
                    M2C_FIELD(var_r5, f32 *, 0x3D8) = (f32) M2C_FIELD(var_r5, f32 *, 0x3D4);
                    temp_f0_4 = M2C_FIELD(var_r7, f32 *, 4);
                    M2C_FIELD(var_r5, f32 *, 0x3DC) = temp_f0_4;
                    M2C_FIELD(var_r5, f32 *, 0x3D4) = temp_f0_4;
                    M2C_FIELD(var_r5, f32 *, 0x3E8) = (f32) M2C_FIELD(var_r5, f32 *, 0x3E4);
                    temp_f0_5 = M2C_FIELD(var_r6, f32 *, 8);
                    M2C_FIELD(var_r5, f32 *, 0x3EC) = temp_f0_5;
                    M2C_FIELD(var_r5, f32 *, 0x3E4) = temp_f0_5;
                    M2C_FIELD(var_r5, f32 *, 0x428) = (f32) M2C_FIELD(var_r5, f32 *, 0x424);
                    temp_f0_6 = M2C_FIELD(var_r7, f32 *, 8);
                    M2C_FIELD(var_r5, f32 *, 0x42C) = temp_f0_6;
                    M2C_FIELD(var_r5, f32 *, 0x424) = temp_f0_6;
                    M2C_FIELD(var_r5, f32 *, 0x438) = (f32) M2C_FIELD(var_r5, f32 *, 0x434);
                    temp_f0_7 = M2C_FIELD(var_r6, f32 *, 0xC);
                    M2C_FIELD(var_r5, f32 *, 0x43C) = temp_f0_7;
                    M2C_FIELD(var_r5, f32 *, 0x434) = temp_f0_7;
                    M2C_FIELD(var_r5, f32 *, 0x478) = (f32) M2C_FIELD(var_r5, f32 *, 0x474);
                    temp_f0_8 = M2C_FIELD(var_r7, f32 *, 0xC);
                    M2C_FIELD(var_r5, f32 *, 0x47C) = temp_f0_8;
                    M2C_FIELD(var_r5, f32 *, 0x474) = temp_f0_8;
                    M2C_FIELD(var_r5, f32 *, 0x488) = (f32) M2C_FIELD(var_r5, f32 *, 0x484);
                    temp_f0_9 = M2C_FIELD(var_r6, f32 *, 0x10);
                    M2C_FIELD(var_r5, f32 *, 0x48C) = temp_f0_9;
                    M2C_FIELD(var_r5, f32 *, 0x484) = temp_f0_9;
                    M2C_FIELD(var_r5, f32 *, 0x4C8) = (f32) M2C_FIELD(var_r5, f32 *, 0x4C4);
                    temp_f0_10 = M2C_FIELD(var_r7, f32 *, 0x10);
                    M2C_FIELD(var_r5, f32 *, 0x4CC) = temp_f0_10;
                    M2C_FIELD(var_r5, f32 *, 0x4C4) = temp_f0_10;
                    M2C_FIELD(var_r5, f32 *, 0x4D8) = (f32) M2C_FIELD(var_r5, f32 *, 0x4D4);
                    temp_f0_11 = M2C_FIELD(var_r6, f32 *, 0x14);
                    M2C_FIELD(var_r5, f32 *, 0x4DC) = temp_f0_11;
                    M2C_FIELD(var_r5, f32 *, 0x4D4) = temp_f0_11;
                    M2C_FIELD(var_r5, f32 *, 0x518) = (f32) M2C_FIELD(var_r5, f32 *, 0x514);
                    temp_f0_12 = M2C_FIELD(var_r7, f32 *, 0x14);
                    M2C_FIELD(var_r5, f32 *, 0x51C) = temp_f0_12;
                    M2C_FIELD(var_r5, f32 *, 0x514) = temp_f0_12;
                    M2C_FIELD(var_r5, f32 *, 0x528) = (f32) M2C_FIELD(var_r5, f32 *, 0x524);
                    temp_f0_13 = M2C_FIELD(var_r6, f32 *, 0x18);
                    M2C_FIELD(var_r5, f32 *, 0x52C) = temp_f0_13;
                    M2C_FIELD(var_r5, f32 *, 0x524) = temp_f0_13;
                    M2C_FIELD(var_r5, f32 *, 0x568) = (f32) M2C_FIELD(var_r5, f32 *, 0x564);
                    temp_f0_14 = M2C_FIELD(var_r7, f32 *, 0x18);
                    M2C_FIELD(var_r5, f32 *, 0x56C) = temp_f0_14;
                    M2C_FIELD(var_r5, f32 *, 0x564) = temp_f0_14;
                    M2C_FIELD(var_r5, f32 *, 0x578) = (f32) M2C_FIELD(var_r5, f32 *, 0x574);
                    temp_f0_15 = M2C_FIELD(var_r6, f32 *, 0x1C);
                    var_r6 += 0x20;
                    M2C_FIELD(var_r5, f32 *, 0x57C) = temp_f0_15;
                    M2C_FIELD(var_r5, f32 *, 0x574) = temp_f0_15;
                    M2C_FIELD(var_r5, f32 *, 0x5B8) = (f32) M2C_FIELD(var_r5, f32 *, 0x5B4);
                    temp_f0_16 = M2C_FIELD(var_r7, f32 *, 0x1C);
                    var_r7 += 0x20;
                    M2C_FIELD(var_r5, f32 *, 0x5BC) = temp_f0_16;
                    M2C_FIELD(var_r5, f32 *, 0x5B4) = temp_f0_16;
                    var_ctr -= 1;
                    var_r5 += 0x280;
                } while (var_ctr != 0);
            }
        }
        var_r5_2 = &p0[var_r8];
        var_r4 = (unsigned char *)(this + (var_r8 * 0x50));
        var_ctr_2 = temp_r3 - var_r8;
        var_r6_2 = &p1[var_r8];
        if (var_r8 < temp_r3) {
            do {
                M2C_FIELD(var_r4, f32 *, 0x348) = (f32) M2C_FIELD(var_r4, f32 *, 0x344);
                temp_f0_17 = *var_r5_2;
                var_r5_2 += 4;
                M2C_FIELD(var_r4, f32 *, 0x34C) = temp_f0_17;
                M2C_FIELD(var_r4, f32 *, 0x344) = temp_f0_17;
                M2C_FIELD(var_r4, f32 *, 0x388) = (f32) M2C_FIELD(var_r4, f32 *, 0x384);
                temp_f0_18 = *var_r6_2;
                var_r6_2 += 4;
                M2C_FIELD(var_r4, f32 *, 0x38C) = temp_f0_18;
                M2C_FIELD(var_r4, f32 *, 0x384) = temp_f0_18;
                var_r4 += 0x50;
                var_ctr_2 -= 1;
            } while (var_ctr_2 != 0);
        }
    }
    if (p2 != 0) {
        temp_r3_2 = (unsigned char *)(this + ((M2C_FIELD(M2C_FIELD(this, u8 **, 0x80F64), s32 *, 0xC) * 0x50) + 0x340));
        M2C_FIELD(temp_r3_2, f32 *, 8) = (f32) M2C_FIELD(temp_r3_2, f32 *, 4);
        M2C_FIELD(temp_r3_2, f32 *, 0xC) = p3;
        M2C_FIELD(temp_r3_2, f32 *, 4) = p3;
        temp_f0_19 = M2C_FIELD(temp_r3_2, f32 *, 0x44);
        M2C_FIELD(temp_r3_2, f32 *, 0x4C) = temp_f0_19;
        M2C_FIELD(temp_r3_2, f32 *, 0x44) = temp_f0_19;
        M2C_FIELD(temp_r3_2, f32 *, 0x48) = temp_f0_19;
    }
    ((CMenuReliveHall*)(this))->setCircleSw();
    M2C_FIELD(this, s32 *, 0x81090) = 2;
    memset((void*)((u8*)this + 0x810A4), 0, 0x40U);
    ((CMenuReliveHall*)(this))->makeCursorPositionTbl((PocketVec<short>*)((u8*)this + 0x80F68));
}

}

namespace {
void CMenuReliveHall::resetViewAll() {
    CMenuReliveHall *var_r26;
    f32 *var_r24;
    f32 *var_r25;
    f32 *var_r7;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    s32 temp_r0;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r7;
    volatile s32 temp_r8;
    s32 temp_r9;
    s32 var_ctr_2;
    s32 var_r29;
    s32 var_r4;
    s32 var_r5;
    u32 temp_r24;
    u32 temp_r4;
    u32 var_ctr;
    u8 *temp_r10;
    u8 *temp_r24_2;
    u8 *temp_r25;
    u8 *temp_r26;
    u8 *temp_r6_3;
    u8 *temp_r7_2;
    u8 *temp_r8_2;
    u8 *temp_r9_2;
    u8 *var_r12;
    u8 *var_r6;

    memset((void*)((u8*)this + 0x340), 0, 0x2D0U);
    temp_r24 = (unsigned long)(((CReliveStage*)(M2C_FIELD(this, CReliveStage **, 0x33C)))->getVisitorPointer());
    memset((void*)((u8*)this + 0x530), 0, 0x34U);
    if (temp_r24 != 0) {
        ((CAnt*)(this + 0x530))->initByPokemonAndSetColorAnimationInReliveHallVisitor((Pokemon*)((Pokemon *) temp_r24));
        ((CAnt*)(this + 0x530))->setAnimation(0);
    }
    temp_r3 = ((CReliveStage*)(M2C_FIELD(this, CReliveStage **, 0x33C)))->getDancerQuantity();
    temp_r30 = temp_r3 * 0x10;
    var_r26 = this;
    var_r29 = 0;
    var_r25 = (float *)(&relivehallAisyou2ColorTbl + 0x8C + temp_r30);
    var_r24 = (float *)(&relivehallAisyou2ColorTbl + 0xDC + temp_r30);
    while (var_r29 < temp_r3) {
        temp_r4 = (unsigned long)(((CReliveStage*)(M2C_FIELD(this, CReliveStage **, 0x33C)))->getDancerPointer(var_r29));
        M2C_FIELD(var_r26, f32 *, 0x34C) = (*var_r25);
        M2C_FIELD(var_r26, f32 *, 0x348) = (*var_r25);
        M2C_FIELD(var_r26, f32 *, 0x344) = (*var_r25);
        temp_f0_2 = *var_r24;
        M2C_FIELD(var_r26, f32 *, 0x38C) = temp_f0_2;
        M2C_FIELD(var_r26, f32 *, 0x388) = temp_f0_2;
        M2C_FIELD(var_r26, f32 *, 0x384) = temp_f0_2;
        M2C_FIELD(var_r26, s8 *, 0x340) = 0;
        ((CAnt*)(((u8*)((s32)var_r26) + 0x350)))->initByPokemon((Pokemon*)((Pokemon *) temp_r4));
        ((CAnt*)(((u8*)(var_r26) + 0x350)))->setAnimation(1);
        var_r26 += 0x50;
        var_r24 += 4;
        var_r25 += 4;
        var_r29 += 1;
    }
    temp_r3_2 = ((CMenuReliveHall*)(this))->getQuantityMarkerDancerEmpty();
    if (temp_r3_2 != 0) {
        var_r4 = 0;
        if (temp_r3_2 > 0) {
            temp_r6 = temp_r3_2 - 8;
            if (temp_r3_2 > 8) {
                var_r12 = (unsigned char *)(&relivehallAisyou2ColorTbl + 0x12C + temp_r30);
                var_r5 = var_r29 * 0x50;
                var_ctr = (temp_r6 + 7) >> 3U;
                if (temp_r6 > 0) {
                    do {
                        temp_r26 = (unsigned char *)((u8*)this + (var_r5 + 0x340));
                        M2C_FIELD(temp_r26, s8 *, 0) = 1;
                        M2C_FIELD(temp_r26, f32 *, 4) = (f32) M2C_FIELD(var_r12, f32 *, 0);
                        temp_r8 = var_r29 + 4;
                        temp_r7 = var_r29 + 5;
                        M2C_FIELD(temp_r26, f32 *, 8) = (f32) M2C_FIELD(temp_r26, f32 *, 4);
                        temp_r6_2 = var_r29 + 6;
                        temp_r0 = var_r29 + 7;
                        temp_r25 = (unsigned char *)((u8*)this + (((var_r29 + 1) * 0x50) + 0x340));
                        M2C_FIELD(temp_r26, f32 *, 0xC) = (f32) M2C_FIELD(temp_r26, f32 *, 4);
                        temp_r9 = (var_r29 + 3) * 0x50;
                        temp_r24_2 = (unsigned char *)((u8*)this + (((var_r29 + 2) * 0x50) + 0x340));
                        var_r29 += 8;
                        var_r5 += 0x280;
                        M2C_FIELD(temp_r25, s8 *, 0) = 1;
                        temp_r10 = (unsigned char *)((u8*)this + (temp_r9 + 0x340));
                        M2C_FIELD(temp_r25, f32 *, 4) = (f32) M2C_FIELD(var_r12, f32 *, 4);
                        var_r4 += 8;
                        temp_r9_2 = (unsigned char *)((u8*)this + ((temp_r8 * 0x50) + 0x340));
                        M2C_FIELD(temp_r25, f32 *, 8) = (f32) M2C_FIELD(temp_r25, f32 *, 4);
                        temp_r8_2 = (unsigned char *)((u8*)this + ((temp_r7 * 0x50) + 0x340));
                        M2C_FIELD(temp_r25, f32 *, 0xC) = (f32) M2C_FIELD(temp_r25, f32 *, 4);
                        temp_r7_2 = (unsigned char *)((u8*)this + ((temp_r6_2 * 0x50) + 0x340));
                        M2C_FIELD(temp_r24_2, s8 *, 0) = 1;
                        M2C_FIELD(temp_r24_2, f32 *, 4) = (f32) M2C_FIELD(var_r12, f32 *, 8);
                        temp_r6_3 = (unsigned char *)((u8*)this + ((temp_r0 * 0x50) + 0x340));
                        M2C_FIELD(temp_r24_2, f32 *, 8) = (f32) M2C_FIELD(temp_r24_2, f32 *, 4);
                        M2C_FIELD(temp_r24_2, f32 *, 0xC) = (f32) M2C_FIELD(temp_r24_2, f32 *, 4);
                        M2C_FIELD((u16)temp_r10, s8 *, 0) = 1;
                        M2C_FIELD(temp_r10, f32 *, 4) = (f32) M2C_FIELD(var_r12, f32 *, 0xC);
                        M2C_FIELD(temp_r10, f32 *, 8) = (f32) M2C_FIELD(temp_r10, f32 *, 4);
                        M2C_FIELD(temp_r10, f32 *, 0xC) = (f32) M2C_FIELD(temp_r10, f32 *, 4);
                        M2C_FIELD(temp_r9_2, s8 *, 0) = 1;
                        M2C_FIELD(temp_r9_2, f32 *, 4) = (f32) M2C_FIELD(var_r12, f32 *, 0x10);
                        M2C_FIELD(temp_r9_2, f32 *, 8) = (f32) M2C_FIELD(temp_r9_2, f32 *, 4);
                        M2C_FIELD(temp_r9_2, f32 *, 0xC) = (f32) M2C_FIELD(temp_r9_2, f32 *, 4);
                        M2C_FIELD(temp_r8_2, s8 *, 0) = 1;
                        M2C_FIELD(temp_r8_2, f32 *, 4) = (f32) M2C_FIELD(var_r12, f32 *, 0x14);
                        M2C_FIELD(temp_r8_2, f32 *, 8) = (f32) M2C_FIELD(temp_r8_2, f32 *, 4);
                        M2C_FIELD(temp_r8_2, f32 *, 0xC) = (f32) M2C_FIELD(temp_r8_2, f32 *, 4);
                        M2C_FIELD(temp_r7_2, s8 *, 0) = 1;
                        M2C_FIELD(temp_r7_2, f32 *, 4) = (f32) M2C_FIELD(var_r12, f32 *, 0x18);
                        M2C_FIELD(temp_r7_2, f32 *, 8) = (f32) M2C_FIELD(temp_r7_2, f32 *, 4);
                        M2C_FIELD(temp_r7_2, f32 *, 0xC) = (f32) M2C_FIELD(temp_r7_2, f32 *, 4);
                        temp_f0_3 = M2C_FIELD(var_r12, f32 *, 0x1C);
                        var_r12 += 0x20;
                        M2C_FIELD(temp_r6_3, s8 *, 0) = 1;
                        M2C_FIELD(temp_r6_3, f32 *, 4) = temp_f0_3;
                        M2C_FIELD(temp_r6_3, f32 *, 8) = (f32) M2C_FIELD(temp_r6_3, f32 *, 4);
                        M2C_FIELD(temp_r6_3, f32 *, 0xC) = (f32) M2C_FIELD(temp_r6_3, f32 *, 4);
                        var_ctr -= 1;
                    } while (var_ctr != 0);
                }
            }
            var_r6 = (unsigned char *)((u8*)this + (var_r29 * 0x50));
            var_r7 = (float *)(&relivehallAisyou2ColorTbl + 0x12C + (temp_r30 + (var_r4 * 4)));
            var_ctr_2 = temp_r3_2 - var_r4;
            if (var_r4 < temp_r3_2) {
                do {
                    temp_f0_4 = *var_r7;
                    var_r7 += 4;
                    M2C_FIELD(var_r6, s8 *, 0x340) = 1;
                    M2C_FIELD(var_r6, f32 *, 0x344) = temp_f0_4;
                    M2C_FIELD(var_r6, f32 *, 0x348) = (f32) M2C_FIELD(var_r6, f32 *, 0x344);
                    M2C_FIELD(var_r6, f32 *, 0x34C) = (f32) M2C_FIELD(var_r6, f32 *, 0x344);
                    var_r6 += 0x50;
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
            }
        }
    }
    ((CMenuReliveHall*)(this))->setCircleSw();
    ((CMenuReliveHall*)(this))->makeCursorPositionTbl((PocketVec<short>*)((u8*)this + 0x80F68));
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
            PocketVec<short> p = views[i].getPosition();
            out[i].x = p.x;
            out[i].y = p.y;
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
    markerPosB[0].x = -1;
    markerPosB[0].y = -1;
    markerPosB[1].x = -1;
    markerPosB[1].y = -1;
    markerPosB[2].x = -1;
    markerPosB[2].y = -1;
    markerPosB[3].x = -1;
    markerPosB[3].y = -1;
    markerPosB[4].x = -1;
    markerPosB[4].y = -1;
    markerPosB[5].x = -1;
    markerPosB[5].y = -1;
    markerPosB[6].x = -1;
    markerPosB[6].y = -1;
    markerPosB[7].x = -1;
    markerPosB[7].y = -1;
    markerPosB[8].x = -1;
    markerPosB[8].y = -1;
}

void CMenuReliveHall::main(CMenuGlobalState& gs)
{
    PocketVec<short> t;
    PocketVec<short> sel = gs.cursor.table[gs.cursor.index];
    init(gs);
    if (pState->kind == 1) {
        alphaFadeInKick();
        anim.next = 6;
        memset(anim.work, 0, 0x40);
        t = sel;
        CMenuPokemonCursor* c = cursor;
        c->pos.x = t.x;
        c->pos.y = t.y;
    } else {
        systemFadeInKick();
    }
    state.next = 1;
    memset(state.work, 0, 0x40);
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
    memset(windowFuncs, 0, 0x100);
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
    memset(views, 0, 0x2D0);
    savedIndex = 0;
    memset(&actionList, 0, 0xC);
    memset(&stick, 0, 0xC);
    u32 i;
    GSgfxColAu8* col = relivehallAisyou2ColorTbl;
    LineWidthEntry* lw = _aisyou2LineWidthHalfTable;
    SCircle* c = circle;
    for (i = 0; i < 3; i++) {
        c->init(lw->b, lw->c, lw->d, *col);
        col++;
        lw++;
        c++;
    }
    memset(&scriptB, 0, 0x10);
    state.init();
    pState = 0;
    cursor = 0;
    memset(markerPosA, 0, 0x24);
    savedTempo = 0;
    pokemonInit((u32)statusVisitor);
    statusSet = 0;
    if (st.tutorialFlag) {
        tutorialMode = 1;
    }
    pState = &st;
    cursor = &pState->cursor;
    cursor->setPositionTable(markerPosA, 0);
    state.init();
    markerClear();
    anim.init();
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
    memset(&tempoMode, 0, 8);
    markerOnVisitor = 0xFF;
    markerOnDancer = 0xFF;
    markerOnEmpty = 0xFF;
    alphaB = 0xFF;
    alphaA = 0xFF;
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
    anim.next = 7;
    memset(anim.work, 0, 0x40);
    resetViewAll();
    editAfterDp0VisitorCheck();
}

void CMenuReliveHall::actionPickup()
{
    savedTempo = getTempo(false);
    menuPtPlaySe(0x45D);
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
        s8 sel = stage->hit;
        if (sel > cursor->index) sel--;
        if (sel >= stage->getDancerQuantity()) sel = 0;
        stage->hit = sel;
        f32* a = dir2s;
        f32* b = dirs;
        v = views;
        for (int i = 0; i < n; v++, i++) {
            if (i != cursor->index) {
                *a++ = v->dir2;
                *b++ = v->dir;
            }
        }
    } else if (idx == 6) {
        Pokemon visitor;
        memcpy(markerPosB, markerPosA, 0x24);
        stage->pickupVisitor(visitor);
        cursor->setPokemon(&visitor);
    }
    u8 in2 = 0;
    int ci = cursor->index;
    if (ci >= 0 && ci <= 5) in2 = 1;
    if (in2) {
        int pos;
        if (stage->getDancerQuantity() == 3 && ci == 0) {
            pos = 5;
        } else {
            int k = ci - 1;
            if (k < 0) k = 0;
            pos = k + stage->getDancerQuantity();
        }
        cursor->setPositionIndex((u16)pos);
    }
    resetViewAll();
    if (moved) {
        dancerMoveAnimationKick(dirs, dir2s, true, hold);
    } else {
        anim.next = 5;
        memset(anim.work, 0, 0x40);
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
        u8 sel = s->hit;
        if (n != 0 && (s8)sel >= pos) sel++;
        s->hit = sel;
        cursor->setPositionIndex(pos);
        SPokemonView* v = views;
        f32* a = dirs;
        f32* b = dir2s;
        for (int i = 0; i < n + 1; i++) {
            if (i != pos) {
                *a = v->dir;
                *b = v->dir2;
                v++;
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
        anim.next = 4;
        memset(anim.work, 0, 0x40);
    }
    editAfterDp0VisitorCheck();
}
}
