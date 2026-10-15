// WIP: Purification Chamber (relive hall) menu. ~55 of 103 functions written, 49 exact/near-exact.
// Needs extra_cflags=["-inline", "noauto"] (peephole off is set via pragma below).
// NOT yet written: menuPtSpriteDrawArrow, drawStatusPanel, drawMainBG, drawAll, stateDirChangeProc,
// actionPut/Pickup/Change, getTempoPassion, animationStateUpdate/DataReset, cursorPositionDecideAtStageChange,
// dancerMoveAnimationKick, resetViewAll, aButtomAction, stateMainProc, loop, main, init.
#include <dolphin/types.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

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
};

class CReliveHall {
public:
    static CReliveHall* getPointer();
    CReliveStage* getStage(long);
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
double fabs(double);
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

class CMetaMenu;
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
    void* tutorial;
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

struct CMenuGlobalState;

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
    u8 pad10[0x10];
    Pokemon pokemon;
    bool isCatchPokemon();
};

namespace {

struct SCircle {
    f32 outer;
    s32 radius;
    f32 inner;
    struct Px {
        s16 angle;
        u16 x, y;
        u8 pad;
        u8 alpha;
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
    SPokemonView views[7];
    u8 pad570[0xA0];
    s32 savedIndex;
    s32* actionList;
    u8 pad618[0x8];
    CStick stick;
    SCircle circle[3];
    s32 scriptB;
    s32 scriptA;
    s32 modelB;
    s32 modelA;
    CMenuPokemonCursor* cursor;
    PocketVec<short> markerPosA[7];
    u8 pad80F84[0x8];
    CInfoWindow infoWin;
    u8 pad80FC0[0x4];
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
    PocketVec<short> markerPosB[7];
    u8 pad81156[0x3A];
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
            long ox = lbl_8032E568[i] + i * 0x42;
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
        spriteSetScissor(w->layer, spr->sx, spr->sy, (s32)((f32)spr->sw * rate), spr->sh);
        spriteSetEnv(w->layer);
        winSpriteDraw(w, spr);
        spriteSetOffset(w->layer, 0, 0);
        spriteClearScissor(w->layer);
        spriteSetEnv(w->layer);
        return;
    }
    menuPtSpriteWorkSetWidthRateColor(w, id, 0, rate, c);
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

void SCircle::setSwPrime(int from, int to, bool on)
{
    int a = start[from];
    int b = start[to];
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
    int prevX = -1;
    int prevY = -1;
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
    int q = dancerPositionQuantityWithCatch();
    if (q) {
        int n = stage->getDancerQuantity();
        if (n == 0 && q == 1) n = 1;
        for (int i = 0; i < n; i++) {
            f32 dir = calcStarDir(i, n);
            for (int j = 0; j < 6; j++) {
                f32 d = -(0.06981317f * (f32)j - dir);
                f32 s = (f32)sin(d);
                f32 c = (f32)cos(d);
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
        u8 b = (u8)(alphaB * a / 255);
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
    f32 r = 90.0f * calcAnimationTimeRate0to1(1.5f);
    PocketVec<short> p = v->getPosition();
    f32 dir = xyxy2dir(p, circlePosition);
    int j = 0;
    int k = 0;
    do {
        f32 d = r - (f32)k;
        if (!(d < 0.0f)) {
            f32 s = (f32)sin(dir);
            drawStarLightOne(colorIdx, d * s + 320.0f, d * -(f32)cos(dir) + 280.0f, j);
        }
        k += 5;
        j++;
    } while (j < 6);
}

void CMenuReliveHall::drawVsitorLine(long ci, SPokemonView* v)
{
    if (!views[6].hidden) {
        GSgfxColAu8 c = relivehallAisyou2ColorTbl[ci];
        s32 w = _aisyou2LineWidthHalfTable[ci].a;
        c.v[3] = c.v[3] * alphaA / 255;
        f32 py = v->getPosition().y;
        f32 px = v->getPosition().x;
        f32 dir = 1.5707964f + xy2dir(px - fcirclePosition.x, py - fcirclePosition.y);
        GSgfxColAu8 c1 = c;
        for (f32 k = 0.0f; k < (f32)w; k += 0.5f) {
            f32 o = k - (f32)(w / 2);
            f32 ox = o * (f32)sin(dir);
            f32 oy = o * -(f32)cos(dir);
            GSgfxColAu8 c2 = c;
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
        getCircleColorAisyou(a, b, col, i);
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
        long x = (s32)(81.0f * (f32)sin(v.dir2) + (f32)v.getPosition().x);
        long y = (s32)(81.0f * -(f32)cos(v.dir2) + (f32)v.getPosition().y);
        u16 ids[2];
        for (u16 i = 0; i < 2; i++) {
            ids[i] = zokuseiGetPokemonSpriteID(v.getPokemon()->getPokemonDataPtr(), i);
        }
        if (ids[0] == ids[1]) {
            menuPtSpriteDraw(ids[0], x - 0x24, y - 9);
        } else {
            long x2 = x - 0x24;
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

int CMenuReliveHall::getPassion(int* out)
{
    return getTempoPassion(out, 1, 0);
}

int CMenuReliveHall::getTempo(bool b)
{
    return getTempoPassion(0, b, 1);
}

f32 CMenuReliveHall::getDirToAisyou(f32 dir)
{
    int n = dancerPositionQuantityWithCatch();
    for (s8 i = 0; i < n; i++) {
        SPokemonView* a = getPokemonViewByClockwizePositionWithCatch(i);
        SPokemonView* b = getPokemonViewByClockwizePositionWithCatch((i + 1) % n);
        if (isDirRegionIn(dir, a->dir, b->dir)) {
            Pokemon* pb = b->getPokemonWithPickupOverride();
            return pokemonToAisyou(a->getPokemonWithPickupOverride(), pb);
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
    color = pokemonToAisyou(va->getPokemonWithPickupOverride(), pb);
    a = va->dir;
    GSgfxColAu8 c = relivehallAisyou2ColorTbl[color];
    b = vb->dir;
}

GSgfxColAu8 CMenuReliveHall::positionToAisyouColor(int i, int j)
{
    Pokemon* a = getPokemonFromPositionWithCatch(i);
    return pokemonToAisyouColor(a, getPokemonFromPositionWithCatch(j));
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
    int n = stage->getDancerQuantity();
    u8 catching = 0;
    if (cursor->isCatchPokemon()) {
        c = cursor;
        Pokemon* p = c->pokemon.checkValid() ? &c->pokemon : 0;
        if (!p->isDarkPokemon()) catching = 1;
    }
    if (catching) {
        CMenuPokemonCursor* c = cursor;
        u8 in = 0;
        int idx = c->index;
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
    f32 best = 1000.0f;
    int found = -1;
    int curIdx = cursor->index;
    PocketVec<short> cur = tbl[curIdx];
    PocketVec<short> pos[11];
    memcpy(pos, tbl, 36);
    memcpy(&pos[9], _cursorPositionTblAddPc, 8);
    for (int i = 0; i < 11; i++) {
        if (curIdx == 7 && i >= 9) break;
        if (i != cursor->index && pos[i].x != -1) {
            int d = degreeSubHalf(dir, xyxy2dirDegree(pos[i], cur));
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
    int range = 0xF;
    int r;
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
    s8 ly = GSinputGetLeftStickYData(1, 0);
    s8 lx = GSinputGetLeftStickXData(1, 0);
    s8 ry = GSinputGetRightStickYData(1, 0);
    s8 rx = GSinputGetRightStickXData(1, 0);
    s8 t;
    dir = 0.0f;
    t = lx;
    if (t < 0) t = -t;
    if (t > 0x20) {
        dir = xy2dir((f32)lx, (f32)ly);
        cur = 1;
    } else {
        t = ly;
        if (t < 0) t = -t;
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
                t = ry;
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
    if (v && v->getDarkPoint() == 0.0f && stage->getDancerQuantity() == 0) {
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
    v.dir2 = q + v.dir2To;
}

void CMenuReliveHall::dancerMoveAnimationAll(f32 t)
{
    int n = stage->getDancerQuantity();
    for (int i = 0; i < n; i++) {
        dancerMoveAnimationOne(views[i], t);
    }
    CMenuPokemonCursor* c = cursor;
    u8 in = 0;
    int idx = c->index;
    if (stage->getDancerQuantity() <= idx && cursor->index <= 5) in = 1;
    if (in) dancerMoveAnimationOne(views[cursor->index], t);
    setCircleSw();
    makeCursorPositionTbl(markerPosA);
}
}

namespace {
void CMenuReliveHall::makeCursorPositionTbl(PocketVec<short>* out)
{
    memcpy(out, _cursorPositionTblDefault, 0x24);
    CMenuPokemonCursor* c;
    u8 dark = 0;
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
