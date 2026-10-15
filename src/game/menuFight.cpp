#pragma defer_codegen on
// Work in progress: pokemon XD menuFight.
#include <dolphin/types.h>
#include "game/shared/menu_work.h"

#pragma peephole off

static inline s32 targetSecretSpriteID(s32 menuID)
{
    s32 id;
    switch (menuID) {
    case 0x37:
        id = 0x42;
        break;
    case 0x40:
        id = 0x41;
        break;
    case 0x38:
        id = 0x40;
        break;
    case 0x41:
        id = 0x3f;
        break;
    default:
        id = 0;
        break;
    }
    return id;
}

static inline s32 targetSecretCursor(s32 menuID)
{
    s32 id;
    switch (menuID) {
    case 0x37:
        id = 2;
        break;
    case 0x40:
        id = 3;
        break;
    case 0x38:
        id = 0;
        break;
    case 0x41:
        id = 1;
        break;
    default:
        id = -1;
        break;
    }
    return id;
}

static inline s32 targetItemID(s32 menuID)
{
    switch (menuID) {
    case 0x37:
        return 0x138;
    case 0x40:
        return 0x139;
    case 0x38:
        return 0x13a;
    case 0x41:
        return 0x13b;
    }
    return 0;
}

static inline s32 targetCursor1p(s32 menuID)
{
    switch (menuID) {
    case 0x37:
        return 0;
    case 0x40:
        return 1;
    case 0x38:
        return 2;
    case 0x41:
        return 3;
    }
    return -1;
}

static inline s32 targetCursor1pB(s32 menuID)
{
    switch (menuID) {
    case 0x37:
        return 3;
    case 0x40:
        return 2;
    case 0x38:
        return 0;
    case 0x41:
        return 1;
    }
    return -1;
}


enum GSinputDevice { GSINPUT_DUMMY = 0, GSINPUT_1 = 1 };
class DarkPokemon {
public:
    bool isWazaNew(u8 index) const;
    void setWazaNew(u8 index, bool isNew);
};

class Pokemon {
public:
    bool isDarkPokemon() const;
    DarkPokemon* getDarkPokemon();
    void* getPokemonDataPtr() const;
};
struct FIGHT_TRAINER;
struct MENU_WAZA_STATUS {
    u8 unk0[0x40];
    void* fightOut;
    u8 tuusin;
};

static Pokemon* _menuFightGetPokemonPtr(FIGHT_TRAINER* trainer, unsigned long index);
static u32 _menuFightIsUse(MENU_WAZA_STATUS* status, u16 idx);

static bool _menuFightCheckTimeOut(void);
static void _menuFightKeyWait(GSinputDevice dev);
static bool isImasugu(void);
static s32 getKane(void);
static u16 _menuFightGetRightStickInfo(long port, bool update);
static u16 _menuFightGetLeftKeyInfo(long port);
static void menuFightDrawIwaitStatusWaza(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, Pokemon* pokemon, u8 index, unsigned long color);
void menuFightSetSeqOut(void);

struct Cursor {
    s16 x;
    s16 y;
};

struct MenuItemPos {
    u8 unk0[0xA];
    s16 x;
    s16 y;
};

struct WazaRow {
    u32 name;
    u32 unk4;
    u16 type;
    u8 ppMax;
    u8 pp;
};

struct WazaAlloc {
    u32 unk0;
    WazaRow rows[4];
    u8 unk34[0xC];
    void* fightOut;
};

struct WazaRow2 {
    u32 unk0;
    u32 name;
    u32 unk8;
    u16 type;
    u8 ppMax;
    u8 pp;
};

struct WazaWork {
    u8 state;
    u8 unk1;
    s8 sel;
};

static s32 chkWazaNew(MENU_WAZA_STATUS* status, u8 index);
extern "C" {
s32 lbl_804E7EB8 = 0x3C;
s32 lbl_804E7EBC = 0xD;
}
static u16 oldKeyInfo[2] = {0, 0};

extern "C" {
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(void*, void*, void**);
void* fightOutPokemonGetNicknamePtr(void*);
void* fightPokemonGetNicknamePtr(void*);
u16 fightOutPokemonGetTokuseiDataId(void*);
u8 fightTrainerCheckCanIrekaeFightPokemon(void*, void*);
s32 winMsgOpen(s8, u32, bool, bool);
void winMsgClose(bool);
void GSlogWrite(const char*, ...);
s32 gbaCommandRequestAction(u32, FIGHT_TRAINER*, u16, s32);
s8 GSinputGetRightStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
double atan2(double, double);
void menuItemBiosSetSelectFlag(s32, u32, bool);
tagSPRITE_WORK* windowSearchItemID(tagWINDOW_WORK*, u32);
Cursor windowGetCursor(s32);
u16 zokuseiBiosGetSpriteID(u16);
void windowDrawSprite(s16 x, s16 y, void* ctx, u16 key, u32 flags, s32 layer);
void menuSubDrawCursorBack2(s32, s32, s32, s32, s32, u8, u8, s32);
void* menuItemBiosGetPtr(s32, u32);
u8 fightFloor_GetStockPokemonNum(void*);
s32 GSmsgPrintRight(s32 layer, s32 x, s32 y, s16 w, s16 h, u32 color, u32 msg);
s32 menuGetCursor(s32);
s32 menuGetSelectItemNum(s32);
s32 fightFloorGetStatus(void*, u16, u16, u16);
void windowCreateCursorSprite(tagWINDOW_WORK*);
void pokemonWazaReplace(void*, s8, u16);
void pokemonToMenuWazaStatus(void*, void*);
}

extern "C" {
u16 fightFloor_GetTurnCount(void*);
void msgctrlSetValue(s32, u32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
s32 GSmsgPrint2(s32 layer, s32 x, s32 y, u32 color, u32 msg);
s32 GSmsgPrintRect(s32 layer, s32 x, s32 y, s16 w, s16 h, u32 color, u32 msg);
u32 GSmsgGetRect(u32);
void menuSubDrawCursorBack(s32, s32, s32, s32, s32, u8, u8);
void winSpriteSetDisp(tagSPRITE_WORK*, bool);
u32 heroGetStatus(void*, u32, u16);
u8 fightFloor_GetFightTypeFightoutPokemonNum(void*);
u8 fightFloor_GetFightKindGetOkaneFlag(void*);
u8 fightFloor_GetFightKindOkanePoolFlag(void*);
void* fightFloorGetGcHeroFightTrainerPtr(void*);
void* fightTrainer_GetHeroPtr(void*);
u8 fightTrainer_GetOkaneBai(void*);
void* fightTargetGetPtrAsNowFightType(u16, void*);
u16 fightTrainer_GetFightTrainerDataId(void*);
u8 fightTrainerDB_GetKindDataId(u16);
void* fightTrainerKindDataBiosGetPtr(u16);
u16 fightTrainerKindDataBiosGetSyoukinBairitu(void*);
void* fightTrainer_GetFightPokemonPtr(void*, u16);
bool fightPokemonCheckValid(void*);
u8 figthPokemonGetLevel(void*);
u8 fightPokemon_GetCatchEntryFlag(void*);
f32 menuGetTotalTime(void);
u32 windowGetParam(tagWINDOW_WORK*, u32);
void windowSetParam(tagWINDOW_WORK*, u32, u32);
tagWINDOW_WORK* windowSearchID(s32);
u32 menuSubCalcColor(tagWINDOW_WORK*, tagSPRITE_WORK*);
f32 fightTimerAllGetNokoriTime(void);
f32 fightTimerCommandGetNokoriTime(void);
bool menuIsCheck(s32);
void menuCloseCustom(s32, s32, s32);
s32 menuOpen(s32, s32);
void menuButtonNormal(tagWINDOW_WORK*);
u8 GSsndPlayNow(u32);
u8 fightFloorIsNowEncountTuusinTaisen(void*);
u8 fightFloorIsUseFightTimerCommand(void*);
bool fightTimerCommandIsOver(void);
u16 fightGetFightResultId(void);
u8 fightKind_CheckFightKind(u8);
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
f32 timeGetLastFrameSec(void);
void GSthreadSwitch(void);
u32 fightMenuGetFightTrainerPtrToStatusMenuId();
void winSeqSetMenu(s32, u32);
bool winSeqCheckMove(s32);
void menuFightSetStatus(s32);
}

struct TargetSecretEntry {
    s32 unk0;
    s32 idA;
    s32 unk8[2];
    s32 idB;
    s32 unk14;
};

struct WindowKeyInfo {
    u16 press;
    u16 unk2;
    u16 trigger;
};

extern "C" {
void* fightFloorGetGcHeroFightTrainerPtr(void*);
void* fightTrainerGetValidFightPokemonPtr(FIGHT_TRAINER*, u16);
s32 pokemonGetStatus(void*, u16, u16, u16);
bool pokemonCheckValid(void*);
bool pokemonWazaCheckValid(void*, u16);
void* windowAllocMemory(tagWINDOW_WORK*, s32);
void* windowGetAllocPtr(tagWINDOW_WORK*);
void* windowGetFreeWork(tagWINDOW_WORK*);
void* memcpy(void*, const void*, u32);
void* fightOutPokemonGetPokemonPtr(void*);
u8 fightOutPokemonCheckCanOutOkWazaBanme(void*, u16, u8, u16*);
u32 wazaGetStatus(void*, u16, u16, u32);
u32 GSmsgGetGSchar(u32);
u16 fightOutPokemonGetSoubiItemDataId(void*);
u32 fightFloorSetStatus(void*, u16, u16, u16, u32);
WindowKeyInfo* windowGetKeyInfo(void);
bool menuItemBiosGetSelectFlag(s32, u32);
s32 menuGetCursorItemID(s32);
}

struct TargetEntry {
    u32 unk0;
    u32 menuId;
    u32 unk8;
};

struct TargetArg {
    TargetEntry entry[4];
    u8 count;
    u8 tuusin;
    u8 pad[2];
    u32 user;
};

extern "C" {
void* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*, void*);
void* fightFloorGetNowPtr(void);
s32 menuOpenCustom(s32, ...);
void menuClose(s32);
s32 menuGetCursorFromItemID(s32, s32);
u8 fightTypeDataBiosGetFightoutPokemonNum(void*);
void* fightTypeDataBiosGetPtr(u16);
u8 fightTypeDataBiosGetTrainerNum(void*);
s32 menuPokemonOpenFight(u8, u8, FIGHT_TRAINER*, void*);
void* fightTargetGetPtr(u16, void*, u16);
bool fightOutPokemonCheckFightOut(void*);
u32 fightMenuGetFightOutPokemonPtrToStatusMenuId(void*, u16, bool);
s32 menuFightCloseTarget(s32);
s32 menuPokemonCheckPokemonChange(void*, FIGHT_TRAINER*, u32);
s32 menuCB_GetBattleController2P(void);
bool fightTargetIsHostSide(void*, u16);
u8 fightFloor_GetFightType(void*);
s32 winMsgOpenFight(u32, bool, bool);
void winMsgCloseFight(bool);
}

static s32 menuFightStatus;

extern "C" {
void menuFightDrawTurn(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawKane(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawTimer(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlTimer(tagWINDOW_WORK* window);
void menuFightButtonTimeOutCheck(tagWINDOW_WORK* window);
bool menuFightCloseCheckTotalTimer(void);
void menuFightCloseTotalTimer(void);
void menuFightOpenTotalTimer(void);
bool menuFightCloseCheckCountDown(void);
void menuFightCloseCountDown(void);
void menuFightOpenCountDown(void);
void menuFightButtonSecretKousan(tagWINDOW_WORK* window);
void menuFightOpenTimeup(void);
void menuFightDrawTargetSecret(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightButtonTargetSecret(tagWINDOW_WORK* window);
void menuFightDrawTargetCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightCtrlTarget(void);
s32 menuFightCtrlSecretPokemonTop(tagWINDOW_WORK* window);
void menuFightDrawSecretSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlSecretWazaTop(tagWINDOW_WORK* window);
void menuFightButtonSecretMain(tagWINDOW_WORK* window);
s32 menuFightCtrlSecretMain(tagWINDOW_WORK* window);
void menuFightDrawBall(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlBall(tagWINDOW_WORK* window);
void menuFightDrawPP(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawType(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawWaza(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawNew(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawCmdMsg(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightWazaButton(tagWINDOW_WORK* window);
s32 menuFightWazaCtrl(tagWINDOW_WORK* window);
s32 menuFightMainCtrl(tagWINDOW_WORK* window);
s32 menuPokemonCheckPokemonChange(void* fop, FIGHT_TRAINER* trainer, u32 index);
s32 menuFightOpenGBAMain(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightOpenGBAIrekae(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightCloseTarget(s32 arg);
s32 menuFightOpenTarget(TargetArg* arg, s32 b, s32 c);
s32 menuFightOpenPokemon(FIGHT_TRAINER* trainer, void* fop, u16 type, u8 cancel, u8 tuusin);
s32 menuFightCloseWaza(s32 arg);
s32 menuFightOpenWaza(FIGHT_TRAINER* trainer, MENU_WAZA_STATUS* status, s32 b, s32 c);
u8 menuFightGetKeyWaitMenuId(void);
void menuFightCloseAll(void);
void menuFightSetSeq(void);
bool menuFightChkSeq(void);
void menuFightSetStatus(s32 v);
s32 menuFightGetStatus(void);
bool menuFightChkOpenBall(s32 id);
}

class bingo_bios {
public:
    static u8 getStaticBall();
};

extern "C" {
void fightMenuCloseInfoMenu(u8);
void fightMenuOpenInfoMenu(s8);
void* fightEncountDataBiosGetPtr(u16);
u16 fightEncountDataBiosGetDiskId(void*);
s32 menuBattleDiskOpenDocPush(u8);
void fightSeqEventKurein(s32);
u8 GSgfxVideoGetVsyncRate(void);
void menuCreateOffScreen(f32, f32);
u8 menuOffScreenSetPriority(u8);
void menuOffScreenFadeSync(u8);
void menuReleaseOffScreen(f32);
u8 GSfloorPush(u32);
void floorSetFadeScript(u32, u32);
void floorWaitForChange(void);
u8 fightFloorIsNowEncountSnatchOnly(void*);
}

extern "C" {
void menuFightDrawTurn(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawKane(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawTimer(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlTimer(tagWINDOW_WORK* window);
void menuFightButtonTimeOutCheck(tagWINDOW_WORK* window);
bool menuFightCloseCheckTotalTimer(void);
void menuFightCloseTotalTimer(void);
void menuFightOpenTotalTimer(void);
bool menuFightCloseCheckCountDown(void);
void menuFightCloseCountDown(void);
void menuFightOpenCountDown(void);
void menuFightButtonSecretKousan(tagWINDOW_WORK* window);
void menuFightOpenTimeup(void);
void menuFightDrawTargetSecret(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightButtonTargetSecret(tagWINDOW_WORK* window);
void menuFightDrawTargetCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightCtrlTarget(void);
s32 menuFightCtrlSecretPokemonTop(tagWINDOW_WORK* window);
void menuFightDrawSecretSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlSecretWazaTop(tagWINDOW_WORK* window);
void menuFightButtonSecretMain(tagWINDOW_WORK* window);
s32 menuFightCtrlSecretMain(tagWINDOW_WORK* window);
void menuFightDrawBall(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlBall(tagWINDOW_WORK* window);
void menuFightDrawPP(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawType(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawWaza(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawNew(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawCmdMsg(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightWazaButton(tagWINDOW_WORK* window);
s32 menuFightWazaCtrl(tagWINDOW_WORK* window);
s32 menuFightMainCtrl(tagWINDOW_WORK* window);
s32 menuPokemonCheckPokemonChange(void* fop, FIGHT_TRAINER* trainer, u32 index);
s32 menuFightOpenGBAMain(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightOpenGBAIrekae(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightCloseTarget(s32 arg);
s32 menuFightOpenTarget(TargetArg* arg, s32 b, s32 c);
s32 menuFightOpenPokemon(FIGHT_TRAINER* trainer, void* fop, u16 type, u8 cancel, u8 tuusin);
s32 menuFightCloseWaza(s32 arg);
s32 menuFightOpenWaza(FIGHT_TRAINER* trainer, MENU_WAZA_STATUS* status, s32 b, s32 c);
s32 menuFightCloseTop(s32 arg);
s32 menuFightOpenTop(FIGHT_TRAINER* trainer, u8* work, s32* cursor, s32 d);
u8 menuFightGetKeyWaitMenuId(void);
void menuFightCloseAll(void);
void menuFightSetSeq(void);
bool menuFightChkSeq(void);
void menuFightSetStatus(s32 v);
s32 menuFightGetStatus(void);
bool menuFightChkOpenBall(s32 id);
}

extern "C" {
void menuFightDrawTurn(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawKane(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawTimer(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlTimer(tagWINDOW_WORK* window);
void menuFightButtonTimeOutCheck(tagWINDOW_WORK* window);
bool menuFightCloseCheckTotalTimer(void);
void menuFightCloseTotalTimer(void);
void menuFightOpenTotalTimer(void);
bool menuFightCloseCheckCountDown(void);
void menuFightCloseCountDown(void);
void menuFightOpenCountDown(void);
void menuFightButtonSecretKousan(tagWINDOW_WORK* window);
void menuFightOpenTimeup(void);
void menuFightDrawTargetSecret(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightButtonTargetSecret(tagWINDOW_WORK* window);
void menuFightDrawTargetCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightCtrlTarget(void);
void menuFightDrawTargetI(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlSecretPokemonTop(tagWINDOW_WORK* window);
void menuFightDrawSecretSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlSecretWazaTop(tagWINDOW_WORK* window);
void menuFightButtonSecretMain(tagWINDOW_WORK* window);
s32 menuFightCtrlSecretMain(tagWINDOW_WORK* window);
void menuFightDrawBall(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlBall(tagWINDOW_WORK* window);
void menuFightDrawPP(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawType(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawWaza(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawNew(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawCmdMsg(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightWazaButton(tagWINDOW_WORK* window);
s32 menuFightWazaCtrl(tagWINDOW_WORK* window);
s32 menuFightMainCtrl(tagWINDOW_WORK* window);
s32 menuPokemonCheckPokemonChange(void* fop, FIGHT_TRAINER* trainer, u32 index);
s32 menuFightOpenGBAMain(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightOpenGBAIrekae(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightCloseTarget(s32 arg);
s32 menuFightOpenTarget(TargetArg* arg, s32 b, s32 c);
s32 menuFightOpenPokemon(FIGHT_TRAINER* trainer, void* fop, u16 type, u8 cancel, u8 tuusin);
s32 menuFightCloseWaza(s32 arg);
s32 menuFightOpenWaza(FIGHT_TRAINER* trainer, MENU_WAZA_STATUS* status, s32 b, s32 c);
s32 menuFightCloseTop(s32 arg);
s32 menuFightOpenTop(FIGHT_TRAINER* trainer, u8* work, s32* cursor, s32 d);
u8 menuFightGetKeyWaitMenuId(void);
void menuFightCloseAll(void);
void menuFightSetSeq(void);
bool menuFightChkSeq(void);
void menuFightSetStatus(s32 v);
s32 menuFightGetStatus(void);
bool menuFightChkOpenBall(s32 id);
}

struct CURSOR {
    s16 top;
    s16 pos;
};

extern "C" {
u8 menuCursorCmp(CURSOR, CURSOR);
void menuPlaySe(s32, s32);
WindowKeyInfo* windowGetPortKeyInfo(u8);
}

extern "C" {
void menuFightDrawTurn(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawKane(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawTimer(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlTimer(tagWINDOW_WORK* window);
void menuFightButtonTimeOutCheck(tagWINDOW_WORK* window);
bool menuFightCloseCheckTotalTimer(void);
void menuFightCloseTotalTimer(void);
void menuFightOpenTotalTimer(void);
bool menuFightCloseCheckCountDown(void);
void menuFightCloseCountDown(void);
void menuFightOpenCountDown(void);
void menuFightButtonSecretKousan(tagWINDOW_WORK* window);
void menuFightOpenTimeup(void);
void menuFightDrawTargetSecret(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightButtonTargetSecret(tagWINDOW_WORK* window);
void menuFightDrawTargetCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightCtrlTarget(void);
void menuFightDrawTargetI(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlSecretPokemonTop(tagWINDOW_WORK* window);
void menuFightDrawSecretSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawSecretWazaSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightCurIkousan(void);
s32 menuFightCtrlSecretWazaTop(tagWINDOW_WORK* window);
void menuFightButtonSecretMain(tagWINDOW_WORK* window);
s32 menuFightCtrlSecretMain(tagWINDOW_WORK* window);
void menuFightDrawBall(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlBall(tagWINDOW_WORK* window);
void menuFightDrawPP(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawType(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawWaza(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawNew(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawCmdMsg(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightWazaButton(tagWINDOW_WORK* window);
s32 menuFightWazaCtrl(tagWINDOW_WORK* window);
s32 menuFightMainCtrl(tagWINDOW_WORK* window);
s32 menuPokemonCheckPokemonChange(void* fop, FIGHT_TRAINER* trainer, u32 index);
s32 menuFightOpenGBAMain(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightOpenGBAIrekae(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightCloseTarget(s32 arg);
s32 menuFightOpenTarget(TargetArg* arg, s32 b, s32 c);
s32 menuFightOpenPokemon(FIGHT_TRAINER* trainer, void* fop, u16 type, u8 cancel, u8 tuusin);
s32 menuFightCloseWaza(s32 arg);
s32 menuFightOpenWaza(FIGHT_TRAINER* trainer, MENU_WAZA_STATUS* status, s32 b, s32 c);
s32 menuFightCloseTop(s32 arg);
s32 menuFightOpenTop(FIGHT_TRAINER* trainer, u8* work, s32* cursor, s32 d);
u8 menuFightGetKeyWaitMenuId(void);
void menuFightCloseAll(void);
void menuFightSetSeq(void);
bool menuFightChkSeq(void);
void menuFightSetStatus(s32 v);
s32 menuFightGetStatus(void);
bool menuFightChkOpenBall(s32 id);
}

extern "C" {
void menuSetDisp(s32, s32);
u16 menuPokemonGetJoutaiSpriteID(void*, s32);
s32 menuSubGetPokemonSexForFightDisp(void*);
}

extern "C" {
void menuFightDrawTurn(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawKane(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawTimer(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlTimer(tagWINDOW_WORK* window);
void menuFightButtonTimeOutCheck(tagWINDOW_WORK* window);
bool menuFightCloseCheckTotalTimer(void);
void menuFightCloseTotalTimer(void);
void menuFightOpenTotalTimer(void);
bool menuFightCloseCheckCountDown(void);
void menuFightCloseCountDown(void);
void menuFightOpenCountDown(void);
void menuFightButtonSecretKousan(tagWINDOW_WORK* window);
void menuFightOpenTimeup(void);
void menuFightDrawTargetSecret(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightButtonTargetSecret(tagWINDOW_WORK* window);
void menuFightDrawTargetCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightCtrlTarget(void);
void menuFightDrawTargetI(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawSecretPokemon(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightButtonSecretPokemonTop(tagWINDOW_WORK* window);
s32 menuFightCtrlSecretPokemonTop(tagWINDOW_WORK* window);
void menuFightDrawSecretSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawSecretWazaSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightButtonSecretWazaTop(tagWINDOW_WORK* window);
void menuFightCurIkousan(void);
s32 menuFightCtrlSecretWazaTop(tagWINDOW_WORK* window);
void menuFightButtonSecretMain(tagWINDOW_WORK* window);
s32 menuFightCtrlSecretMain(tagWINDOW_WORK* window);
void menuFightDrawBall(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightCtrlBall(tagWINDOW_WORK* window);
void menuFightDrawPP(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawType(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawWaza(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawNew(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuFightDrawCmdMsg(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuFightWazaButton(tagWINDOW_WORK* window);
s32 menuFightWazaCtrl(tagWINDOW_WORK* window);
s32 menuFightMainCtrl(tagWINDOW_WORK* window);
s32 menuPokemonCheckPokemonChange(void* fop, FIGHT_TRAINER* trainer, u32 index);
s32 menuFightOpenGBAMain(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightOpenGBAIrekae(u32 a, FIGHT_TRAINER* b, u16 c, u16 d);
s32 menuFightCloseTarget(s32 arg);
s32 menuFightOpenTarget(TargetArg* arg, s32 b, s32 c);
s32 menuFightOpenPokemon(FIGHT_TRAINER* trainer, void* fop, u16 type, u8 cancel, u8 tuusin);
s32 menuFightCloseWaza(s32 arg);
s32 menuFightOpenWaza(FIGHT_TRAINER* trainer, MENU_WAZA_STATUS* status, s32 b, s32 c);
s32 menuFightCloseTop(s32 arg);
s32 menuFightOpenTop(FIGHT_TRAINER* trainer, u8* work, s32* cursor, s32 d);
u8 menuFightGetKeyWaitMenuId(void);
void menuFightCloseAll(void);
void menuFightSetSeq(void);
bool menuFightChkSeq(void);
void menuFightSetStatus(s32 v);
s32 menuFightGetStatus(void);
bool menuFightChkOpenBall(s32 id);
}









static inline u8 zokuseiOf(void* data);

struct StatusAlloc {
    u8 unk0[0x40];
    void* fightOut;
};

extern "C" {
void* pokemonDataBiosGetPtr(u16);
u8 pokemonDataBiosGetZokuseiDataId(void*, u16);
u32 fightOutPokemon_GetTokuseiDataId(void*);
u32 pokemonTokuseiDataBiosGetPtr(u16);
u32 pokemonTokuseiDataBiosGetName(u32);
u8 pokemonWazaGetMaxPP(void*, u16);
u16 pokemonGetSoubiItemDataId(void*);
u8* itemDataBiosGetPtr(u16);
u32 itemDataBiosGetName(u8*);
}

static inline u8 zokuseiOf(void* data)
{
    return (u8)pokemonDataBiosGetZokuseiDataId(data, 0);
}

extern "C" void menuFightDrawIPokemonStatus(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);

extern "C" {
void* fightFloorGetValidFightSidePtr(void*, u16);
void* fightSideGetValidFightTrainerPtr(void*, u16);
void* fightTrainerGetValidFightOutPokemonPtr(void*, u16);
u32 zokuseiGetPokemonSpriteID(void*, u16);
void windowDrawSprite2(s16 x, s16 y, s16 w, s16 h, u32 color, void* ctx, u16 key, u32 flags, s32 layer);
}

extern "C" void menuFightDrawIwaitStatus(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);

struct SecretStatusArg {
    s32 sel;
};

extern "C" {
u32 pokemonGetTokuseiDataId(void*);
u32 pokemonDataBiosGetName(void*);
s32 menuSubGetPokemonSexForDisp(void*);
}

extern "C" void menuFightDrawSecretPokemonStatus(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);

extern "C" {
s32 GSmsgPrintRight(s32 layer, s32 x, s32 y, s16 w, s16 h, u32 color, u32 msg);
}

struct WazaDocArg {
    s32 sel;
};

extern "C" void menuFightDrawSecretWazaDoc(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);

extern "C" void menuFightButtonIwaza1p(tagWINDOW_WORK* window);

bool menuFightChkOpenBall(s32 id)
{
    if (id == 0x44 || id == 0x45) {
        if (fightKind_CheckFightKind(0xc)) {
            return false;
        }
    }
    return true;
}

s32 menuFightGetStatus(void) { return menuFightStatus; }

void menuFightSetStatus(s32 v) { menuFightStatus = v; }

bool menuFightChkSeq(void)
{
    if (winSeqCheckMove(0x37)) {
        return true;
    }
    if (winSeqCheckMove(0x40)) {
        return true;
    }
    if (winSeqCheckMove(0x38)) {
        return true;
    }
    return winSeqCheckMove(0x41) != 0;
}

void menuFightSetSeq(void)
{
    winSeqSetMenu(0x37, 0x1a5);
    winSeqSetMenu(0x40, 0x1a5);
    winSeqSetMenu(0x38, 0x1a9);
    winSeqSetMenu(0x41, 0x1a9);
}

void menuFightSetSeqOut(void)
{
    winSeqSetMenu(0x37, 0x19d);
    winSeqSetMenu(0x40, 0x19d);
    winSeqSetMenu(0x38, 0x1a1);
    winSeqSetMenu(0x41, 0x1a1);
    menuFightSetStatus(1);
}

void menuFightCloseAll(void)
{
    const s32 menus[28] = {0x37, 0x40, 0x38, 0x41, 0x69,  0x6A,  0x39,  0x3A,  0x42,  0x43,  0x44,  0x45,  0x98, 0x99,
                           0x9A, 0x9B, 0x9D, 0xB5, 0x9C, 0x10B, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0x11C, 0x11D};
    s32 id;
    u8 i;
    for (i = 0; i < 28; i++) {
        id = menus[i];
        if (menuIsCheck(id) == 1) {
            menuCloseCustom(id, 0, 0);
        }
    }
}

u8 menuFightGetKeyWaitMenuId(void)
{
    u8 id = 0x98;
    switch (fightMenuGetFightTrainerPtrToStatusMenuId()) {
    case 0x42:
        id = 0x98;
        break;
    case 0x43:
        id = 0x99;
        break;
    case 0x44:
        id = 0x9a;
        break;
    case 0x45:
        id = 0x9b;
        break;
    }
    return id;
}

static bool isImasugu(void)
{
    if (fightKind_CheckFightKind(10)) {
        return true;
    }
    return fightKind_CheckFightKind(0x11) != 0;
}

static bool _menuFightCheckTimeOut(void)
{
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
            return true;
        }
        if (fightGetFightResultId() == 1) {
            return true;
        }
    }
    return false;
}

static void _menuFightKeyWait(GSinputDevice dev)
{
    f32 t = 0.0f;
    if (isImasugu()) {
        while (t < 2.5f) {
            t += timeGetLastFrameSec();
            GSthreadSwitch();
        }
    } else {
        while (!(GSinputButtonsPressed(dev) & GSinputButtonsChanged(dev) & 0x300)) {
            if (_menuFightCheckTimeOut()) {
                break;
            }
            GSthreadSwitch();
        }
    }
}

s32 menuFightOpenTop(FIGHT_TRAINER* trainer, u8* work, s32* cursor, s32 d)
{
    s32 result;
    s32 r27;
    menuFightSetStatus(0);
    if (isImasugu()) {
        return 0;
    }
    while (1) {
        if (fightKind_CheckFightKind(0xf)) {
            menuOpen(0xb5, 0);
        }
        switch (work[0x17]) {
        case 0:
            result = menuOpenCustom(0x3a, 0, cursor, 0, d, 1, work);
            break;
        case 1:
            result = menuOpenCustom(0x8e, 0, cursor, 0, d, 1, work);
            break;
        }
        if (work[0x16] == 0 || fightKind_CheckFightKind(0xd) || fightKind_CheckFightKind(0xf) || fightKind_CheckFightKind(0xe) ||
            fightKind_CheckFightKind(6) || fightKind_CheckFightKind(7)) {
            if (result == 3) {
                s32 zero = 0;
                menuFightSetSeqOut();
                menuFightCloseTop(1);
                if (fightKind_CheckFightKind(0xf)) {
                    menuClose(0xb5);
                }
                fightMenuCloseInfoMenu(1);
                if (fightKind_CheckFightKind(0xf)) {
                    r27 = menuBattleDiskOpenDocPush(fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(0xe)));
                } else if (fightKind_CheckFightKind(0xe)) {
                    r27 = menuBattleDiskOpenDocPush(fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(0xd)));
                } else {
                    r27 = menuOpenCustom(0x8f, 0, &zero, 0, 1, 0);
                    menuCloseCustom(0x8f, 0, 1);
                }
                if (r27 != 0x31) {
                    fightMenuOpenInfoMenu(-1);
                    if (fightKind_CheckFightKind(0xf)) {
                        menuOpen(0xb5, 0);
                    }
                    continue;
                }
            }
        } else {
            if (work[0x16] != 0) {
                if (result == 1 || result == 2) {
                    menuFightSetSeqOut();
                }
            }
        }
        if (fightKind_CheckFightKind(0xf)) {
            if (result == 1 || result == 2) {
                menuClose(0xb5);
            }
        }
        if (fightKind_CheckFightKind(0xd)) {
            if (!bingo_bios::getStaticBall() && result == 1) {
                menuFightCloseTop(1);
                winMsgOpen(4, 0x5012, 1, 0);
                winMsgClose(1);
                continue;
            } else if (result == 0x7f) {
                menuFightSetSeqOut();
                menuFightCloseTop(1);
                fightMenuCloseInfoMenu(1);
                menuCreateOffScreen(8.0f / (f32)GSgfxVideoGetVsyncRate(), 50.0f);
                menuOffScreenSetPriority(0);
                menuOffScreenFadeSync(1);
                GSfloorPush(0x38b);
                floorSetFadeScript(0, 0);
                floorWaitForChange();
                menuReleaseOffScreen(8.0f / (f32)GSgfxVideoGetVsyncRate());
                fightMenuOpenInfoMenu(-1);
            }
        }
        if (fightFloorIsNowEncountSnatchOnly(0)) {
            if (result == 0 || result == 3) {
                menuFightCloseTop(1);
                fightSeqEventKurein(6);
                winMsgOpen(2, 0x5005, 1, 1);
                winMsgClose(1);
                fightSeqEventKurein(7);
                continue;
            }
        }
        return result;
    }
}

s32 menuFightCloseTop(s32 arg)
{
    if (menuIsCheck(0x3a)) {
        menuCloseCustom(0x3a, 0, arg);
    }
    if (menuIsCheck(0x8e)) {
        menuCloseCustom(0x8e, 0, arg);
    }
    return 0;
}

static s32 chkWazaNew(MENU_WAZA_STATUS* status, u8 index)
{
    Pokemon* pk = (Pokemon*)fightOutPokemonGetPokemonPtr(status->fightOut);
    if (index == 0) {
        return -1;
    }
    if (pk != 0 && pk->isDarkPokemon()) {
        DarkPokemon* dark = pk->getDarkPokemon();
        if (dark != 0) {
            u16 waza = pokemonGetStatus(pk, 0, 0x7f, index);
            switch (waza) {
            case 0:
        case 0x164: case 0x165: case 0x166: case 0x167: case 0x168: case 0x169: case 0x16a: case 0x16b:
        case 0x16c: case 0x16d: case 0x16e: case 0x16f: case 0x170: case 0x171: case 0x172: case 0x173:
        case 0x174: case 0x175: case 0x176:
                break;
            default:
                return dark->isWazaNew(index - 1);
            }
        }
    }
    return -1;
}

s32 menuFightOpenWaza(FIGHT_TRAINER* trainer, MENU_WAZA_STATUS* status, s32 b, s32 c)
{
    u8 flag = 1;
    s32 result;
    s32 id;
    s32 id25 = 0;
    s32 id24 = 0;
    int i;
    u32 use;
    switch (status->tuusin) {
    case 0:
        if (isImasugu()) {
            result = menuCB_GetBattleController2P();
            if (fightTargetIsHostSide(trainer, fightFloor_GetFightType(0))) {
                id = 0x9e;
                id25 = 0x11c;
                id24 = 0xa2;
            } else {
                id = 0xa1;
                id25 = 0x11d;
                id24 = 0x9f;
            }
        } else {
            id = 0x39;
        }
        break;
    case 1:
        id = 0x90;
        break;
    }
    while (1) {
        winSeqSetMenu(id, 0x20);
        if (isImasugu()) {
            if (id24 != 0) {
                menuOpen(id24, 0);
            }
            while (flag) {
                result = menuOpenCustom(id, 0, b, 0, c, 1, status);
                if (result != -1) {
                    menuCloseCustom(id, 2, c);
                }
                if (result == 5) {
                    if (menuOpen(id25, 1) == 1) {
                        flag = 0;
                    }
                    menuCloseCustom(id25, 2, 1);
                } else {
                    flag = 0;
                }
            }
            if (result == 5) {
                break;
            }
        } else {
            result = menuOpenCustom(id, 0, b, 0, c, 1, status);
            if (id == 0x90) {
                menuClose(id);
            }
        }
        if (result >= 0) {
            use = _menuFightIsUse(status, (u16)result);
            if (use != 0) {
                menuFightCloseWaza(1);
                if (isImasugu() && id24 != 0) {
                    menuClose(id24);
                }
                winMsgOpenFight(use, 1, 1);
                _menuFightKeyWait((GSinputDevice)1);
                winMsgCloseFight(1);
                flag = 1;
                continue;
            }
        }
        break;
    }
    winSeqSetMenu(id, 0x22);
    for (i = 0; i < 4; i++) {
        if (chkWazaNew(status, i) != -1) {
            ((Pokemon*)fightOutPokemonGetPokemonPtr(status->fightOut))->getDarkPokemon()->setWazaNew(i - 1, true);
        }
    }
    return result;
}

s32 menuFightCloseWaza(s32 arg)
{
    if (menuIsCheck(0x39)) {
        menuCloseCustom(0x39, 0, arg);
    }
    if (menuIsCheck(0x94)) {
        menuCloseCustom(0x94, 0, arg);
    }
    if (menuIsCheck(0x93)) {
        menuCloseCustom(0x93, 0, arg);
    }
    if (menuIsCheck(0x90)) {
        menuCloseCustom(0x90, 0, arg);
    }
    return 0;
}

s32 menuFightOpenPokemon(FIGHT_TRAINER* trainer, void* fop, u16 type, u8 cancel, u8 tuusin)
{
    s32 target;
    void* p;
    u8 num;
    s32 result;
    num = fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(type));
    if (tuusin == 0) {
        if (fightKind_CheckFightKind(0xf)) {
            menuClose(0xb5);
        }
        result = menuPokemonOpenFight(num, cancel, trainer, fop);
        if (fightKind_CheckFightKind(0xf)) {
            menuOpen(0xb5, 0);
        }
    } else {
        u8 c8 = cancel;
        while (1) {
            winSeqSetMenu(0x92, 0x20);
            result = menuOpenCustom(0x92, 0, 0, 0, 1, 3, trainer, fop, c8);
            winSeqSetMenu(0x92, 0x22);
            if (result == -1) {
                menuCloseCustom(0x92, 0, 1);
                GSthreadSwitch();
                GSthreadSwitch();
                GSthreadSwitch();
                GSthreadSwitch();
                GSthreadSwitch();
                GSthreadSwitch();
                GSthreadSwitch();
                GSthreadSwitch();
                return -1;
            }
            if (!(u8)menuPokemonCheckPokemonChange(fop, trainer, result)) {
                continue;
            }
            if (cancel != 0) {
                if (num >= 2 || fightTypeDataBiosGetTrainerNum(fightTypeDataBiosGetPtr(type)) == 2) {
                    TargetArg arg;
                    p = fightTargetGetPtr(0xf, fop, type);
                    arg.entry[0].menuId = fightOutPokemonCheckFightOut(p) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(p, type, false) : 0;
                    p = fightTargetGetPtr(0x10, fop, type);
                    arg.entry[1].menuId = fightOutPokemonCheckFightOut(p) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(p, type, false) : 0;
                    p = fightTargetGetPtr(0xe, fop, type);
                    arg.entry[2].menuId = fightOutPokemonCheckFightOut(p) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(p, type, false) : 0;
                    arg.entry[3].menuId = 0;
                    arg.tuusin = tuusin;
                    target = menuFightOpenTarget(&arg, 0, 1);
                    menuFightCloseTarget(1);
                    if (target == -1) {
                        continue;
                    }
                }
            }
            break;
        }
        menuCloseCustom(0x92, 0, 1);
    }
    return result;
}

s32 menuFightOpenTarget(TargetArg* arg, s32 b, s32 c)
{
    s32 result;
    s32 id;
    s32 other;
    s32 i;
    if (arg->tuusin == 0) {
        if (fightKind_CheckFightKind(0xd)) {
            result = 0;
        } else if (isImasugu()) {
            u32 base = fightFloorGetStatus(0, 0, 0x35, 0);
            if (fightFloorGetFightOutPokemonPtrToFightTrainerPtr(fightFloorGetNowPtr(), (void*)arg->user) == (void*)(base + 0x64)) {
                id = 0xa0;
                other = 0xa2;
            } else {
                id = 0xa3;
                other = 0x9f;
            }
            result = menuOpenCustom(id, 0, b, 0, c, 1, arg);
            menuCloseCustom(id, 2, c);
            if (menuIsCheck(other)) {
                menuClose(other);
            }
        } else {
            s32 cursor;
            TargetEntry* e;
            menuItemBiosSetSelectFlag(0x5c, 0x138, false);
            menuItemBiosSetSelectFlag(0x5c, 0x139, false);
            menuItemBiosSetSelectFlag(0x5c, 0x13a, false);
            menuItemBiosSetSelectFlag(0x5c, 0x13b, false);
            e = arg->entry;
            for (i = 0; i < 4; e++, i++) {
                s32 item = targetItemID(e->menuId);
                if (item != 0) {
                    menuItemBiosSetSelectFlag(0x5c, item, true);
                }
            }
            cursor = menuGetCursorFromItemID(0x5c, 0x13a);
            if (cursor == -1) {
                cursor = menuGetCursorFromItemID(0x5c, 0x13b);
                if (cursor == -1) {
                    cursor = 0;
                }
            }
            result = menuOpenCustom(0x5c, 0, &cursor, 0, c, 1, arg);
            s32 want;
            switch (result) {
            case 0x13a:
                want = 0x38;
                break;
            case 0x13b:
                want = 0x41;
                break;
            case 0x138:
                want = 0x37;
                break;
            case 0x139:
                want = 0x40;
                break;
            default:
                want = -1;
                break;
            }
            result = -1;
            e = arg->entry;
            for (i = 0; i < 4; e++, i++) {
                if (want == e->menuId) {
                    result = i;
                    if (fightKind_CheckFightKind(0xf)) {
                        menuClose(0xb5);
                    }
                    break;
                }
            }
        }
    } else if (arg->tuusin == 1) {
        if (menuIsCheck(0x92)) {
            menuCloseCustom(0x92, 0, 1);
        }
        result = menuOpenCustom(0x91, 0, b, 0, c, 1, arg);
    }
    return result;
}

s32 menuFightCloseTarget(s32 arg)
{
    if (menuIsCheck(0x5c)) {
        menuCloseCustom(0x5c, 0, arg);
    }
    if (menuIsCheck(0x91)) {
        menuCloseCustom(0x91, 0, arg);
    }
    return 0;
}

s32 menuFightOpenGBAIrekae(u32 a, FIGHT_TRAINER* b, u16 c, u16 d)
{
    return gbaCommandRequestAction(a, b, c, 1);
}

s32 menuFightOpenGBAMain(u32 a, FIGHT_TRAINER* b, u16 c, u16 d)
{
    return gbaCommandRequestAction(a, b, c, 0);
}

s32 menuPokemonCheckPokemonChange(void* fop, FIGHT_TRAINER* trainer, u32 index)
{
    void* out;
    u8 r = fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, fop, &out);
    if (r == 1) {
        msgctrlSetValue(0xd, (u32)fightOutPokemonGetNicknamePtr(fop));
        winMsgOpen(1, 0x4fc8, 1, 0);
        _menuFightKeyWait((GSinputDevice)1);
        winMsgClose(1);
        return 0;
    } else if (r == 2) {
        fightFloorSetStatus(0, 0, 0x57, 0, fightOutPokemonGetTokuseiDataId(out));
        msgctrlSetValue(0xd, (u32)fightOutPokemonGetNicknamePtr(out));
        msgctrlSetValue(0xe, (u32)fightOutPokemonGetNicknamePtr(fop));
        winMsgOpen(1, 0x4f08, 1, 0);
        _menuFightKeyWait((GSinputDevice)1);
        winMsgClose(1);
        return 0;
    }
    if (trainer == 0) {
        trainer = (FIGHT_TRAINER*)fightFloorGetGcHeroFightTrainerPtr(0);
    }
    if (trainer == 0) {
        return 0;
    }
    void* fp = fightTrainerGetValidFightPokemonPtr(trainer, (u16)index);
    if (fp == 0) {
        return 0;
    }
    r = fightTrainerCheckCanIrekaeFightPokemon(trainer, fp);
    if (r == 1) {
        msgctrlSetValue(0xd, (u32)fightPokemonGetNicknamePtr(fp));
        winMsgOpen(1, 0x4fcb, 1, 0);
        _menuFightKeyWait((GSinputDevice)1);
        winMsgClose(1);
        return 0;
    } else if (r == 2) {
        msgctrlSetValue(0xd, (u32)fightPokemonGetNicknamePtr(fp));
        winMsgOpen(1, 0x4fc9, 1, 0);
        _menuFightKeyWait((GSinputDevice)1);
        winMsgClose(1);
        return 0;
    } else if (r == 3) {
        msgctrlSetValue(0xd, (u32)fightPokemonGetNicknamePtr(fp));
        winMsgOpen(1, 0x4fca, 1, 0);
        _menuFightKeyWait((GSinputDevice)1);
        winMsgClose(1);
        return 0;
    } else if (r == 0) {
        return 1;
    }
    GSlogWrite("%s: 予定外の条件が帰ってきています\n", __FUNCTION__);
    return 0;
}

static u16 _menuFightGetLeftKeyInfo(long port)
{
    u16 ret = 0;
    int idx;
    if (port != 0) {
        idx = 1;
    } else {
        idx = 0;
    }
    u32 keys;
    if (idx != 0) {
        keys = GSinputButtonsPressed(2);
    } else {
        keys = GSinputButtonsPressed(1);
    }
    if (keys & 8) {
        ret |= 1;
    }
    if (keys & 4) {
        ret |= 2;
    }
    if (keys & 1) {
        ret |= 4;
    }
    if (keys & 2) {
        ret |= 8;
    }
    if (ret == oldKeyInfo[idx]) {
        ret = 0;
    } else {
        oldKeyInfo[idx] = ret;
    }
    return ret;
}

static u16 _menuFightGetRightStickInfo(long port, bool update)
{
    u16 ret = 0;
    int idx;
    if (port != 0) {
        idx = 1;
    } else {
        idx = 0;
    }
    s8 y;
    s8 x;
    if (idx == 0) {
        y = GSinputGetRightStickYData(1, 0);
        x = GSinputGetRightStickXData(1, 0);
    } else {
        y = GSinputGetRightStickYData(2, 0);
        x = GSinputGetRightStickXData(2, 0);
    }
    if ((x < 0 ? -x : x) > 0x20 || (y < 0 ? -y : y) > 0x20) {
        f32 ang = atan2((double)x, (double)y);
        if ((ang > 0.0f ? ang : -ang) < 0.7853982f) {
            ret |= 2;
        } else if ((ang > 0.0f ? ang : -ang) > 2.3561945f) {
            ret |= 1;
        }
        if (0.7853982f < (ang > 0.0f ? ang : -ang) && (ang > 0.0f ? ang : -ang) < 2.3561945f) {
            if (ang < 0.0f) {
                ret |= 4;
            } else {
                ret |= 8;
            }
        }
        if (update) {
            if (ret == oldKeyInfo[idx]) {
                ret = 0;
            } else {
                oldKeyInfo[idx] = ret;
            }
        }
    } else {
        oldKeyInfo[idx] = 0;
    }
    return ret;
}

s32 menuFightMainCtrl(tagWINDOW_WORK* window)
{
    u8* d;
    tagSPRITE_WORK* item;
    if (window->state == 0) {
        d = (u8*)windowAllocMemory(window, 0x18);
        if (d != 0) {
            memcpy(d, (void*)window->params[0], 0x18);
        }
        if (fightKind_CheckFightKind(0xf) || fightKind_CheckFightKind(0xe)) {
            item = windowSearchItemID(window, 0x136);
            item->msgID = 0x429f;
            menuItemBiosSetSelectFlag(window->menuID, 0x132, true);
        } else if (fightKind_CheckFightKind(0xd)) {
            item = windowSearchItemID(window, 0x135);
            item->msgID = 0x429f;
            item = windowSearchItemID(window, 0x134);
            item->msgID = 0x1389;
            item = windowSearchItemID(window, 0x136);
            item->msgID = 0x443c;
            menuItemBiosSetSelectFlag(window->menuID, 0x132, true);
        } else if (fightKind_CheckFightKind(6) || fightKind_CheckFightKind(7)) {
            item = windowSearchItemID(window, 0x135);
            item->msgID = 0x429f;
            item = windowSearchItemID(window, 0x136);
            item->msgID = 0;
            menuItemBiosSetSelectFlag(window->menuID, 0x132, false);
        } else if (d[0x16] != 0) {
            item = windowSearchItemID(window, 0x135);
            item->msgID = 0x429d;
            item = windowSearchItemID(window, 0x136);
            item->msgID = 0x42a0;
            menuItemBiosSetSelectFlag(window->menuID, 0x132, true);
        } else {
            item = windowSearchItemID(window, 0x135);
            item->msgID = 0x429f;
            item = windowSearchItemID(window, 0x136);
            item->msgID = 0;
            menuItemBiosSetSelectFlag(window->menuID, 0x132, false);
        }
    }
    d = (u8*)windowGetAllocPtr(window);
    switch (menuGetCursorItemID(window->menuID)) {
    case 0x12c:
        window->cursor88 = 0;
        break;
    case 0x12e:
        if ((fightKind_CheckFightKind(0xd) || d[0x16] == 0) && !fightKind_CheckFightKind(0xf) && !fightKind_CheckFightKind(0xe)) {
            window->cursor88 = 3;
        } else {
            window->cursor88 = 1;
        }
        break;
    case 0x130:
        if (fightKind_CheckFightKind(0xd)) {
            window->cursor88 = 1;
        } else {
            window->cursor88 = 2;
        }
        break;
    case 0x132:
        window->cursor88 = 3;
        if (fightKind_CheckFightKind(0xd)) {
            window->cursor88 = 0x7f;
        }
        break;
    default:
        window->cursor88 = -1;
        break;
    }
    return 0;
}

s32 menuFightWazaCtrl(tagWINDOW_WORK* window)
{
    static u16 menu_item_waza_tbl[4] = {0x110, 0x112, 0x114, 0x116};
    s8 state = window->state;
    void* d;
    if (state == 0) {
        d = windowAllocMemory(window, 0x48);
        if (d != 0) {
            memcpy(d, (void*)windowGetParam(window, 0), 0x48);
        }
        WazaWork* work = (WazaWork*)windowGetFreeWork(window);
        work->state = 0;
        work->unk1 = 0;
        work->sel = -1;
    } else if (state == 3) {
        d = windowGetAllocPtr(window);
        if (d != 0) {
            memcpy((void*)windowGetParam(window, 0), d, 0x48);
        }
    }
    WazaAlloc* alloc = (WazaAlloc*)windowGetAllocPtr(window);
    int i;
    if (window->state == 5) {
        for (i = 0; i < 4; i++) {
            menuItemBiosSetSelectFlag(window->menuID, menu_item_waza_tbl[i], true);
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (alloc->rows[i].name != 0) {
                menuItemBiosSetSelectFlag(window->menuID, menu_item_waza_tbl[i], true);
            } else {
                menuItemBiosSetSelectFlag(window->menuID, menu_item_waza_tbl[i], false);
            }
        }
    }
    switch (menuGetCursorItemID(window->menuID)) {
    case 0x110:
        window->cursor88 = 0;
        break;
    case 0x112:
        window->cursor88 = 1;
        break;
    case 0x114:
        window->cursor88 = 2;
        break;
    case 0x116:
        window->cursor88 = 3;
        break;
    default:
        window->cursor88 = -1;
        break;
    }
    return 0;
}

s32 menuFightWazaButton(tagWINDOW_WORK* window)
{
    WazaAlloc* alloc = (WazaAlloc*)windowGetAllocPtr(window);
    WazaWork* work = (WazaWork*)windowGetFreeWork(window);
    Pokemon* pk = (Pokemon*)fightOutPokemonGetPokemonPtr(alloc->fightOut);
    u16 trig = windowGetKeyInfo()->trigger;
    switch (work->state) {
    case 0:
        if (trig & 0xc0) {
            if (pokemonGetStatus(pk, 0, 0xc2, 0) != 0 || fightKind_CheckFightKind(0xd)) {
                GSsndPlayNow(0x13);
            } else if (fightFloorGetStatus(0, 0, 0x32, 0) != 0 || fightKind_CheckFightKind(0xf)) {
                work->sel = window->cursor;
                if (work->sel == 0) {
                    window->cursor = 1;
                } else {
                    window->cursor = 0;
                }
                if (menuGetSelectItemNum(window->menuID) <= 1) {
                    window->cursor = 0;
                }
                windowCreateCursorSprite(window);
                work->state = 1;
            }
        } else if (pk != 0 && (u16)pokemonGetStatus(pk, 0, 0x7f, window->cursor) == 0x176) {
            if (windowGetKeyInfo()->trigger & 0x20) {
                window->done = 1;
                window->cancel = 1;
            }
        } else {
            menuButtonNormal(window);
        }
        break;
    case 1:
        if (trig & 0xd0) {
            if (pk != 0) {
                s32 sel = work->sel;
                pokemonWazaReplace(pk, sel, window->cursor);
                void* saved = alloc->fightOut;
                pokemonToMenuWazaStatus(pk, alloc);
                alloc->fightOut = saved;
            }
            work->sel = -1;
            work->state = 0;
        } else if (trig & 0x20) {
            work->sel = -1;
            work->state = 0;
        }
        break;
    }
    return 0;
}

void menuFightDrawCmdMsg(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    u32 msg = 0;
    switch (sprite->id) {
    case 0x137: {
        void* a = windowGetAllocPtr(window);
        msgctrlSetValue(0x36, (u32)a);
        msg = 0x42c3;
        break;
    }
    case 0x11d: {
        u32* alloc = (u32*)windowGetAllocPtr(window);
        WazaWork* work = (WazaWork*)windowGetFreeWork(window);
        switch (work->state) {
        case 0:
            msgctrlSetValue(0x36, alloc[0]);
            msg = 0x42c3;
            break;
        case 1:
            msg = 0x42c6;
            break;
        }
        break;
    }
    case 0x12b:
        if (menuGetCursor(0x3a) == 0) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x12d:
        if (menuGetCursor(0x3a) == 1) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x12f:
        if (menuGetCursor(0x3a) == 2) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x131:
        if (menuGetCursor(0x3a) == 3) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    if (msg != 0) {
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, -2, menuSubCalcColor(window, sprite), msg);
    }
}

void menuFightDrawNew(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    MENU_WAZA_STATUS* alloc = (MENU_WAZA_STATUS*)windowGetAllocPtr(window);
    u8 n;
    winSpriteSetDisp(sprite, 0);
    n = 0;
    switch (sprite->id) {
    case 0x10e:
        n = 1;
    case 0x10c:
        n++;
    case 0x10d:
        n++;
    case 0x10b:
        break;
    }
    s32 r = chkWazaNew(alloc, n);
    if (r != -1) {
        if (r == 0) {
            winSpriteSetDisp(sprite, 1);
        }
    }
}

void menuFightDrawWaza(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    WazaAlloc* alloc = (WazaAlloc*)windowGetAllocPtr(window);
    WazaWork* work = (WazaWork*)windowGetFreeWork(window);
    s32 n = 0;
    switch (sprite->id) {
    case 0x110:
        n = 0;
        break;
    case 0x112:
        n = 1;
        break;
    case 0x114:
        n = 2;
        break;
    case 0x116:
        n = 3;
        break;
    case 0x10f:
        n = 4;
        break;
    case 0x111:
        n = 5;
        break;
    case 0x113:
        n = 6;
        break;
    case 0x115:
        n = 7;
        break;
    }
    if (n < 4) {
        u32 name = alloc->rows[n].name;
        if (name != 0) {
            msgctrlSetValue(0x37, name);
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0x17, 0, menuSubCalcColor(window, sprite), 0x4277);
        }
    } else {
        s32 m = n - 4;
        if (window->cursor == m) {
            winSpriteSetDisp(sprite, 1);
            menuSubDrawCursorBack(winSpriteGetLayerID(window, sprite), sprite->x, sprite->y, sprite->w, sprite->h, 0xff, 1);
        } else if (work->sel == m) {
            winSpriteSetDisp(sprite, 0);
            MenuItemPos* item = (MenuItemPos*)menuItemBiosGetPtr(window->menuID, sprite->id);
            menuSubDrawCursorBack2(winSpriteGetLayerID(window, sprite), 0, 0, item->x, item->y, 0xff, 1, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
    }
}

void menuFightDrawType(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    WazaAlloc* alloc = (WazaAlloc*)windowGetAllocPtr(window);
    Cursor cursor = windowGetCursor(window->menuID);
    s32 y = cursor.y;
    if (y >= 0 && y < 4 && alloc->rows[y].name != 0) {
        Pokemon* pk = (Pokemon*)fightOutPokemonGetPokemonPtr(alloc->fightOut);
        u16 waza = pk ? (u16)pokemonGetStatus(pk, 0, 0x7f, window->cursor) : 0;
        switch (waza) {
        case 0:
        case 0x164: case 0x165: case 0x166: case 0x167: case 0x168: case 0x169: case 0x16a: case 0x16b:
        case 0x16c: case 0x16d: case 0x16e: case 0x16f: case 0x170: case 0x171: case 0x172: case 0x173:
        case 0x174: case 0x175: case 0x176:
            return;
        }
        u16 type = alloc->rows[y].type;
        windowDrawSprite(0, 2, window, zokuseiBiosGetSpriteID(type), 0, winSpriteGetLayerID(window, sprite));
    }
}

void menuFightDrawPP(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    WazaAlloc* alloc = (WazaAlloc*)windowGetAllocPtr(window);
    u32 color = menuSubCalcColor(window, sprite);
    Cursor cursor = windowGetCursor(window->menuID);
    s32 y = cursor.y;
    s32 rect = (s16)(GSmsgGetRect(0x42c4) >> 16);
    s16 x = sprite->w - rect * 5;
    GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x42c4);
    if (y >= 0 && y < 4 && alloc->rows[y].name != 0) {
        Pokemon* pk = (Pokemon*)fightOutPokemonGetPokemonPtr(alloc->fightOut);
        u16 waza = pk ? (u16)pokemonGetStatus(pk, 0, 0x7f, window->cursor) : 0;
        switch (waza) {
        case 0:
        case 0x164: case 0x165: case 0x166: case 0x167: case 0x168: case 0x169: case 0x16a: case 0x16b:
        case 0x16c: case 0x16d: case 0x16e: case 0x16f: case 0x170: case 0x171: case 0x172: case 0x173:
        case 0x174: case 0x175:
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->h, color, 0x3af5);
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x3af5);
            break;
        case 0x176:
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->h, color, 0x3ad1);
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x3ad1);
            break;
        default:
            msgctrlSetValue(0x5f, alloc->rows[y].pp);
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->h, color, 0x4351);
            msgctrlSetValue(0x5f, alloc->rows[y].ppMax);
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4351);
            break;
        }
    }
}

static u32 _menuFightIsUse(MENU_WAZA_STATUS* status, u16 idx)
{
    void* fop = status->fightOut;
    Pokemon* pk = (Pokemon*)fightOutPokemonGetPokemonPtr(fop);
    u16 outWaza;
    u8 ret = fightOutPokemonCheckCanOutOkWazaBanme(fop, idx, 1, &outWaza);
    u16 wazaId = pokemonGetStatus(pk, 0, 0x7f, idx);
    u32 msg;
    if (ret) {
        msgctrlSetValue(0x11, (u32)fop);
        msg = wazaGetStatus(0, wazaId, 1, 0);
        msgctrlSetValue(0x28, GSmsgGetGSchar(msg));
        u16 item = fightOutPokemonGetSoubiItemDataId(fop);
        fightFloorSetStatus(0, 0, 0x56, 0, item);
    }
    if (ret == 6) {
        msg = 0x4f42;
    } else if (ret == 5) {
        msgctrlSetValue(0x28, GSmsgGetGSchar(wazaGetStatus(0, outWaza, 1, 0)));
        msg = 0x4f9a;
    } else if (ret == 4) {
        msg = 0x4ee9;
    } else if (ret == 3) {
        msg = 0x4ee8;
    } else if (ret == 2) {
        msg = 0x4ee7;
    } else if (ret == 1) {
        msg = 0x4ee6;
    }
    return ret ? msg : 0;
}

s32 menuFightCtrlBall(tagWINDOW_WORK* window)
{
    void* work = windowGetFreeWork(window);
    if (window->state == 0) {
        memcpy(work, (void*)windowGetParam(window, 0), 6);
    }
    return 0;
}

void menuFightDrawBall(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    u16 key = 0;
    s32 n = -1;
    u8* work = (u8*)windowGetFreeWork(window);
    switch (sprite->id) {
    case 0xb1:
    case 0xbe:
    case 0xc4:
    case 0xca:
        n = 0;
        break;
    case 0xb2:
    case 0xbf:
    case 0xc5:
    case 0xcb:
        n = 1;
        break;
    case 0xb3:
    case 0xc0:
    case 0xc6:
    case 0xcc:
        n = 2;
        break;
    case 0xb4:
    case 0xc1:
    case 0xc7:
    case 0xcd:
        n = 3;
        break;
    case 0xb5:
    case 0xc2:
    case 0xc8:
    case 0xce:
        n = 4;
        break;
    case 0xb6:
    case 0xc3:
    case 0xc9:
    case 0xcf:
        n = 5;
        break;
    case 0xb7:
        winSpriteSetDisp(sprite, 0);
        if (fightFloor_GetStockPokemonNum(0) != 0) {
            winSpriteSetDisp(sprite, 1);
        }
        return;
    case 0xbd:
        n = 0;
    case 0xbc:
        n++;
    case 0xbb:
        n++;
    case 0xba:
        n++;
    case 0xb9:
        n++;
    case 0xb8:
        winSpriteSetDisp(sprite, 0);
        if (n + 2 <= fightFloor_GetStockPokemonNum(0)) {
            winSpriteSetDisp(sprite, 1);
        }
        return;
    }
    if (n >= 0) {
        switch (work[n]) {
        case 0:
            key = 0x8c;
            break;
        case 1:
            key = 0x8d;
            break;
        case 2:
            key = 0x8e;
            break;
        case 3:
            key = 0x8f;
            break;
        }
        if (key != 0) {
            windowDrawSprite(0, 0, window, key, 0, winSpriteGetLayerID(window, sprite));
        }
    }
}

s32 menuFightCtrlSecretMain(tagWINDOW_WORK* window)
{
    if (window->state == 0) {
        void* d = windowAllocMemory(window, 0x18);
        if (d != 0) {
            memcpy(d, (void*)window->params[0], 0x18);
        }
    }
    return 0;
}

void menuFightButtonSecretMain(tagWINDOW_WORK* window)
{
    u16 trig = windowGetKeyInfo()->trigger;
    s32 sel = -1;
    if (trig & 0x10) {
        sel = 0;
    } else if (trig & 0x20) {
        sel = 2;
    } else if (trig & 0x800) {
        sel = 3;
    } else if (trig & 0x200) {
        window->done = 1;
        window->cancel = 1;
        window->cursor88 = -1;
    }
    if (sel >= 0) {
        window->done = 1;
        window->cursor88 = sel;
    }
    menuFightButtonTimeOutCheck(window);
}

s32 menuFightCtrlSecretWazaTop(tagWINDOW_WORK* window)
{
    if (window->state == 0) {
        void* d = windowAllocMemory(window, 0x48);
        if (d != 0) {
            memcpy(d, (void*)window->params[0], 0x48);
        }
    }
    windowGetAllocPtr(window);
    return 0;
}

void menuFightCurIkousan(void)
{
    tagWINDOW_WORK* w;
    if (menuIsCheck(0x11d)) {
        WindowKeyInfo* info;
        w = windowSearchID(0x11d);
        if (menuCB_GetBattleController2P() == 1) {
            info = windowGetPortKeyInfo(1);
        } else {
            info = windowGetPortKeyInfo(2);
        }
        u16 key = info->trigger;
        if (key & 1) {
            if (w->cursor != 0) {
                w->cursor--;
                menuPlaySe(w->menuID, 1);
            }
        } else if (key & 2) {
            if (w->cursor == 0) {
                w->cursor++;
                menuPlaySe(w->menuID, 1);
            }
        }
        if (menuCursorCmp(*(CURSOR*)&w->unkA0, *(CURSOR*)&w->top)) {
            windowCreateCursorSprite(w);
            menuPlaySe(w->menuID, 1);
        }
        w->unkA0 = w->top;
        w->prevCursor = w->cursor;
    }
    if (menuIsCheck(0x11c)) {
        u16 key;
        w = windowSearchID(0x11c);
        key = windowGetPortKeyInfo(1)->trigger;
        if (key & 1) {
            if (w->cursor != 0) {
                w->cursor--;
                menuPlaySe(w->menuID, 1);
            }
        } else if (key & 2) {
            if (w->cursor == 0) {
                w->cursor++;
                menuPlaySe(w->menuID, 1);
            }
        }
        if (menuCursorCmp(*(CURSOR*)&w->unkA0, *(CURSOR*)&w->top)) {
            windowCreateCursorSprite(w);
            menuPlaySe(w->menuID, 1);
        }
        w->unkA0 = w->top;
        w->prevCursor = w->cursor;
    }
}

void menuFightButtonIwaza1p(tagWINDOW_WORK* window)
{
    static s32 waza_no[2] = { -1, -1 };
    tagWINDOW_WORK* w1;
    tagWINDOW_WORK* w2;
    {
        WindowKeyInfo* key;
        u16 trig;
        if (menuIsCheck(0x11d)) {
            if (menuIsCheck(0x115)) {
                menuClose(0x115);
            }
            if (menuIsCheck(0xa2)) {
                menuClose(0xa2);
            }
            w1 = windowSearchID(0x11d);
            if (menuCB_GetBattleController2P() == 1) {
                key = windowGetPortKeyInfo(1);
            } else {
                key = windowGetPortKeyInfo(2);
            }
            trig = key->trigger;
            if (trig & 0x10) {
                w1->done = 1;
                w1->cursor88 = w1->cursor;
                menuPlaySe(w1->menuID, 2);
                return;
            } else if (trig & 0x20) {
                w1->cancel = 1;
                w1->cursor88 = -1;
                menuPlaySe(w1->menuID, 3);
                return;
            }
            menuFightButtonTimeOutCheck(w1);
        }
    }
    {
        WindowKeyInfo* key;
        u16 trig;
        if (menuIsCheck(0x11c)) {
            if (menuIsCheck(0x114)) {
                menuClose(0x114);
            }
            if (menuIsCheck(0x9f)) {
                menuClose(0x9f);
            }
            w2 = windowSearchID(0x11c);
            key = windowGetPortKeyInfo(1);
            trig = key->trigger;
            if (trig & 0x10) {
                w2->done = 1;
                w2->cursor88 = w2->cursor;
                menuPlaySe(w2->menuID, 2);
            } else if (trig & 0x20) {
                w2->cancel = 1;
                w2->cursor88 = -1;
                menuPlaySe(w2->menuID, 3);
            }
            menuFightButtonTimeOutCheck(w2);
        }
    }
    {
        WazaAlloc* alloc;
        WindowKeyInfo* key;
        s32 sel;
        void* pk;
        u16 stick2;
        u16 stick;
        sel = -1;
        if (menuIsCheck(0xa1)) {
            w2 = windowSearchID(0xa1);
            alloc = (WazaAlloc*)windowGetAllocPtr(w2);
            pk = fightOutPokemonGetPokemonPtr(alloc->fightOut);
            if (menuCB_GetBattleController2P() == 1) {
                key = windowGetPortKeyInfo(1);
                stick = _menuFightGetRightStickInfo(0, 1);
                stick2 = _menuFightGetRightStickInfo(0, 0);
            } else {
                key = windowGetPortKeyInfo(2);
                stick = _menuFightGetRightStickInfo(1, 1);
                stick2 = _menuFightGetRightStickInfo(1, 0);
            }
            if (menuIsCheck(0xa2)) {
                if (!(key->press & 0x40)) {
                    menuClose(0xa2);
                    menuSetDisp(0xa1, 1);
                }
            } else if (stick != 0) {
                if (stick & 1) {
                    sel = 0;
                } else if (stick & 8) {
                    sel = 1;
                } else if (stick & 2) {
                    sel = 2;
                } else if (stick & 4) {
                    sel = 3;
                } else if (stick & 0x200) {
                    sel = -1;
                }
                if (key->press & 0x400) {
                    waza_no[1] = sel;
                    if (menuIsCheck(0x115)) {
                        menuClose(0x115);
                    }
                    if (alloc->rows[waza_no[1]].name != 0) {
                        menuOpenCustom(0x115, w2->menuID, 0, 0, 0, 2, w2->menuID, &waza_no[1]);
                    }
                } else {
                    if (menuIsCheck(0x115)) {
                        menuClose(0x115);
                    }
                    if (!pokemonWazaCheckValid(pk, (u16)sel)) {
                        sel = -1;
                    }
                    if (sel >= 0) {
                        w2->done = 1;
                        w2->cursor88 = sel;
                    }
                }
            } else if (menuIsCheck(0x115)) {
                if (!(key->press & 0x400) || stick2 == 0) {
                    menuClose(0x115);
                }
            } else if (key->press & 0x40) {
                menuSetDisp(0xa1, 0);
                menuOpen(0xa2, 0);
            } else if (key->trigger & 0x200) {
                w2->cancel = 1;
                w2->cursor88 = -1;
            } else if (key->trigger & 0x800) {
                w2->done = 1;
                w2->cursor88 = 5;
            }
            menuFightButtonTimeOutCheck(w2);
        }
    }
    {
        WindowKeyInfo* key;
        s32 sel;
        u16 stick;
        u16 stick2;
        WazaAlloc* alloc;
        void* pk;
        sel = -1;
        if (menuIsCheck(0x9e)) {
            w2 = windowSearchID(0x9e);
            alloc = (WazaAlloc*)windowGetAllocPtr(w2);
            pk = fightOutPokemonGetPokemonPtr(alloc->fightOut);
            key = windowGetPortKeyInfo(1);
            stick = _menuFightGetRightStickInfo(0, 1);
            stick2 = _menuFightGetRightStickInfo(0, 0);
            if (menuIsCheck(0x9f)) {
                if (!(key->press & 0x40)) {
                    menuClose(0x9f);
                    menuSetDisp(0x9e, 1);
                }
            } else if (stick != 0) {
                if (stick & 1) {
                    sel = 0;
                } else if (stick & 8) {
                    sel = 1;
                } else if (stick & 2) {
                    sel = 2;
                } else if (stick & 4) {
                    sel = 3;
                }
                if (key->press & 0x400) {
                    waza_no[0] = sel;
                    if (menuIsCheck(0x114)) {
                        menuClose(0x114);
                    }
                    if (alloc->rows[waza_no[0]].name != 0) {
                        menuOpenCustom(0x114, w2->menuID, 0, 0, 0, 2, w2->menuID, &waza_no[0]);
                    }
                } else {
                    if (menuIsCheck(0x114)) {
                        menuClose(0x114);
                    }
                    if (!pokemonWazaCheckValid(pk, (u16)sel)) {
                        sel = -1;
                    }
                    if (sel >= 0) {
                        w2->done = 1;
                        w2->cursor88 = sel;
                    }
                }
            } else if (menuIsCheck(0x114)) {
                if (!(key->press & 0x400) || stick2 == 0) {
                    menuClose(0x114);
                }
            } else if (key->press & 0x40) {
                menuSetDisp(0x9e, 0);
                menuOpen(0x9f, 0);
            } else if (key->trigger & 0x200) {
                w2->cancel = 1;
                w2->cursor88 = -1;
            } else if (key->trigger & 0x800) {
                w2->done = 1;
                w2->cursor88 = 5;
            }
            menuFightButtonTimeOutCheck(w2);
        }
    }
    {
        s32 sel;
        WindowKeyInfo* key;
        u16 left;
        TargetArg* arg;
        sel = -1;
        if (menuIsCheck(0xa3)) {
            w2 = windowSearchID(0xa3);
            windowGetParam(w2, 0);
            if (menuCB_GetBattleController2P() == 1) {
                key = windowGetPortKeyInfo(1);
                left = _menuFightGetLeftKeyInfo(0);
            } else {
                key = windowGetPortKeyInfo(2);
                left = _menuFightGetLeftKeyInfo(1);
            }
            arg = (TargetArg*)windowGetParam(w2, 0);
            if (key->trigger != 0) {
                if (left & 1) {
                    sel = 2;
                } else if (left & 8) {
                    sel = 3;
                } else if (left & 4) {
                    sel = 0;
                } else if (left & 2) {
                    sel = 1;
                } else if (key->trigger & 0x200) {
                    w2->done = 1;
                    w2->cancel = 1;
                    w2->cursor88 = -1;
                }
            }
            if (sel >= 0) {
                int i;
                for (i = 0; i < 4; i++) {
                    if (sel == targetCursor1p(arg->entry[i].menuId)) {
                        if (sel > 2) {
                            sel = 2;
                        }
                        w2->done = 1;
                        w2->cursor88 = sel;
                        return;
                    }
                }
            }
            menuFightButtonTimeOutCheck(w2);
        }
    }
    {
        s32 sel;
        u16 left;
        tagWINDOW_WORK* w;
        TargetArg* arg;
        WindowKeyInfo* key;
        sel = -1;
        if (menuIsCheck(0xa0)) {
            w = windowSearchID(0xa0);
            arg = (TargetArg*)windowGetParam(w, 0);
            _menuFightGetRightStickInfo(0, 1);
            left = _menuFightGetLeftKeyInfo(0);
            key = windowGetPortKeyInfo(1);
            if (key->trigger != 0) {
                if (left & 1) {
                    sel = 0;
                } else if (left & 8) {
                    sel = 1;
                } else if (left & 2) {
                    sel = 2;
                } else if (left & 4) {
                    sel = 3;
                } else if (key->trigger & 0x200) {
                    w->done = 1;
                    w->cancel = 1;
                    w->cursor88 = -1;
                }
            }
            if (sel >= 0) {
                int i;
                for (i = 0; i < 4; i++) {
                    if (sel == targetCursor1pB(arg->entry[i].menuId)) {
                        if (sel > 2) {
                            sel = 2;
                        }
                        w->done = 1;
                        w->cursor88 = sel;
                        return;
                    }
                }
            }
            menuFightButtonTimeOutCheck(w);
        }
    }
}

void menuFightButtonSecretWazaTop(tagWINDOW_WORK* window)
{
    static s32 waza_no = -1;
    WindowKeyInfo* key = windowGetKeyInfo();
    WazaAlloc* alloc = (WazaAlloc*)windowGetAllocPtr(window);
    s32 sel = -1;
    s32 closeID = 0;
    s32 openID = 0;
    u16 stick;
    menuSetDisp(window->menuID, 1);
    if (menuIsCheck(0x94)) {
        closeID = 0x94;
    } else if (menuIsCheck(0x93)) {
        closeID = 0x93;
    }
    stick = _menuFightGetRightStickInfo(0, 1);
    if (stick != 0) {
        if (stick & 1) {
            sel = 0;
        } else if (stick & 8) {
            sel = 1;
        } else if (stick & 2) {
            sel = 2;
        } else if (stick & 4) {
            sel = 3;
        }
        if (alloc->rows[sel].name == 0) {
            sel = -1;
        }
        if (sel >= 0) {
            window->done = 1;
            window->cursor88 = sel;
        }
    } else if (key->trigger & 0x200) {
        window->done = 1;
        window->cancel = 1;
        window->cursor88 = -1;
    } else if (key->press & 0x400) {
        menuSetDisp(window->menuID, 0);
        if (key->press & 1) {
            waza_no = 0;
        } else if (key->press & 8) {
            waza_no = 1;
        } else if (key->press & 2) {
            waza_no = 2;
        } else if (key->press & 4) {
            waza_no = 3;
        } else {
            waza_no = -1;
        }
        if (alloc->rows[waza_no].name == 0) {
            waza_no = -1;
        }
        if (waza_no < 0) {
            openID = 0x94;
        } else {
            openID = 0x93;
        }
    }
    menuFightButtonTimeOutCheck(window);
    if (closeID != openID) {
        if (closeID != 0) {
            menuClose(closeID);
        }
        if (window->done == 0) {
            if (openID == 0x94) {
                menuOpenCustom(0x94, window->menuID, 0, 0, 0, 1, window->menuID);
                menuSetDisp(0x94, 1);
                menuSetDisp(0x93, 0);
            } else if (openID == 0x93) {
                menuOpenCustom(0x93, window->menuID, 0, 0, 0, 2, window->menuID, &waza_no);
                menuSetDisp(0x93, 1);
                menuSetDisp(0x94, 0);
            }
        }
    }
}

void menuFightDrawSecretWazaSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    s32 off;
    WazaRow2* row;
    u8* alloc;
    s32 idx;
    u32 color;
    idx = -1;
    tagWINDOW_WORK* parent = windowSearchID(windowGetParam(window, 0));
    if (parent != 0) {
        alloc = (u8*)windowGetAllocPtr(parent);
        if (alloc != 0) {
            color = menuSubCalcColor(window, sprite);
            switch (sprite->id) {
            case 0x57:
            case 0x5c:
            case 0x60:
            case 0x64:
                idx = 0;
                break;
            case 0x58:
            case 0x5d:
            case 0x61:
            case 0x65:
                idx = 1;
                break;
            case 0x59:
            case 0x5e:
            case 0x62:
            case 0x66:
                idx = 2;
                break;
            case 0x5a:
            case 0x5f:
            case 0x63:
            case 0x67:
                idx = 3;
                break;
            }
            if (idx >= 0) {
                off = idx * 12;
                row = (WazaRow2*)(alloc + off);
                if (row->name != 0) {
                    winSpriteSetDisp(sprite, 1);
                } else {
                    winSpriteSetDisp(sprite, 0);
                    return;
                }
                switch (sprite->id) {
                case 0x5c:
                case 0x5d:
                case 0x5e:
                case 0x5f: {
                    u16 type = row->type;
                    windowDrawSprite(0, 0, window, zokuseiBiosGetSpriteID(type), 0, winSpriteGetLayerID(window, sprite));
                    break;
                }
                case 0x60:
                case 0x61:
                case 0x62:
                case 0x63: {
                    s32 rect = (s16)(GSmsgGetRect(0x42c4) >> 16);
                    s16 x = (sprite->w - rect) / 2;
                    GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x42c4);
                    msgctrlSetValue(0x5f, alloc[off + 0xf]);
                    GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->h, color, 0x4357);
                    msgctrlSetValue(0x5f, alloc[off + 0xe]);
                    GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4357);
                    break;
                }
                case 0x57:
                case 0x58:
                case 0x59:
                case 0x5a:
                    msgctrlSetValue(0x37, row->name);
                    GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x4277);
                    break;
                case 0x5b:
                case 0x64:
                case 0x65:
                case 0x66:
                case 0x67:
                    break;
                }
            }
        }
    }
}

void menuFightDrawSecretWazaDoc(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    WazaDocArg* arg;
    WazaAlloc* alloc;
    u32 color;
    u16 waza;
    void* pk;
    int slot = -1;
    tagWINDOW_WORK* target = windowSearchID(windowGetParam(window, 0));
    if (target != 0) {
        alloc = (WazaAlloc*)windowGetAllocPtr(target);
        if (alloc != 0) {
            arg = (WazaDocArg*)windowGetParam(window, 1);
            if (arg->sel >= 0) {
                pk = fightOutPokemonGetPokemonPtr(alloc->fightOut);
                if (pk != 0) {
                    waza = pokemonGetStatus(pk, 0, 0x7f, (u16)arg->sel);
                    color = menuSubCalcColor(window, sprite);
                    switch (sprite->id) {
                    case 0x7a:
                    case 0x7b:
                    case 0x7c:
                    case 0x7d:
                        switch (sprite->id) {
                        case 0x7a:
                            slot = 0;
                            break;
                        case 0x7b:
                            slot = 1;
                            break;
                        case 0x7d:
                            slot = 2;
                            break;
                        case 0x7c:
                            slot = 3;
                            break;
                        }
                        if (slot == arg->sel) {
                            winSpriteSetDisp(sprite, 1);
                        } else {
                            winSpriteSetDisp(sprite, 0);
                        }
                        break;
                    case 0x253:
                    case 0x254:
                    case 0x255:
                    case 0x256:
                        switch (sprite->id) {
                        case 0x253:
                            slot = 0;
                            break;
                        case 0x254:
                            slot = 1;
                            break;
                        case 0x256:
                            slot = 2;
                            break;
                        case 0x255:
                            slot = 3;
                            break;
                        }
                        if (slot == arg->sel) {
                            winSpriteSetDisp(sprite, 1);
                        } else {
                            winSpriteSetDisp(sprite, 0);
                        }
                        break;
                    case 0x269:
                    case 0x26a:
                    case 0x26b:
                    case 0x26c:
                        switch (sprite->id) {
                        case 0x269:
                            slot = 0;
                            break;
                        case 0x26a:
                            slot = 1;
                            break;
                        case 0x26c:
                            slot = 2;
                            break;
                        case 0x26b:
                            slot = 3;
                            break;
                        }
                        if (slot == arg->sel) {
                            winSpriteSetDisp(sprite, 1);
                        } else {
                            winSpriteSetDisp(sprite, 0);
                        }
                        break;
                    case 0x79:
                    case 0x252:
                    case 0x268: {
                        u16 type = alloc->rows[arg->sel].type;
                        windowDrawSprite(0, 0, window, zokuseiBiosGetSpriteID(type), 0, winSpriteGetLayerID(window, sprite));
                        break;
                    }
                    case 0x81:
                    case 0x25b:
                    case 0x271: {
                        u32 msg = wazaGetStatus(0, waza, 0x22, 0);
                        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, msg);
                        break;
                    }
                    case 0x7f:
                    case 0x25a:
                    case 0x270: {
                        u32 v = wazaGetStatus(0, waza, 6, 0);
                        if (v <= 1) {
                            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x3af6);
                        } else {
                            msgctrlSetValue(0x5f, v);
                            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4351);
                        }
                        break;
                    }
                    case 0x7e:
                    case 0x259:
                    case 0x26f: {
                        u32 v = wazaGetStatus(0, waza, 7, 0);
                        if (v <= 1) {
                            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x3af6);
                        } else {
                            msgctrlSetValue(0x5f, v);
                            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4351);
                        }
                        break;
                    }
                    case 0x80:
                    case 0x257:
                    case 0x26d:
                        msgctrlSetValue(0x37, alloc->rows[arg->sel].name);
                        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x4276);
                        break;
                    case 0x82:
                    case 0x258:
                    case 0x26e: {
                        s16 x = (s16)(GSmsgGetRect(0x42d1) >> 16);
                        s16 w = sprite->w - x;
                        s16 half;
                        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x42d1);
                        half = (w - (s16)(GSmsgGetRect(0x42c4) >> 16)) / 2;
                        GSmsgPrint2(winSpriteGetLayerID(window, sprite), x + half, 0, color, 0x42c4);
                        msgctrlSetValue(0x5f, alloc->rows[arg->sel].pp);
                        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), x, 0, half, sprite->h, color, 0x4357);
                        msgctrlSetValue(0x5f, alloc->rows[arg->sel].ppMax);
                        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), x, 0, w, sprite->h, color, 0x4357);
                        break;
                    }
                    }
                }
            }
        }
    }
}

static Pokemon* _menuFightGetPokemonPtr(FIGHT_TRAINER* trainer, unsigned long index)
{
    if (index >= 6) {
        return 0;
    }
    if (trainer == 0) {
        trainer = (FIGHT_TRAINER*)fightFloorGetGcHeroFightTrainerPtr(0);
    }
    if (trainer == 0) {
        return 0;
    }
    void* fp = fightTrainerGetValidFightPokemonPtr(trainer, (u16)index);
    if (fp == 0) {
        return 0;
    }
    Pokemon* pk = (Pokemon*)pokemonGetStatus(fp, 0, 0xcc, 0);
    if (pokemonCheckValid(pk) == 0) {
        return 0;
    }
    return pk;
}

void menuFightDrawSecretSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    bool disp = true;
    if (window->menuID == 0x92) {
        bool has = windowGetParam(window, 2);
        if (!has) {
            disp = false;
        }
    }
    switch (sprite->id) {
    case 0x21:
    case 0x23:
        winSpriteSetDisp(sprite, disp);
        break;
    case 0x22:
        break;
    }
}

s32 menuFightCtrlSecretPokemonTop(tagWINDOW_WORK* window)
{
    windowGetParam(window, 0);
    windowGetParam(window, 1);
    windowGetParam(window, 2);
    return 0;
}

void menuFightButtonSecretPokemonTop(tagWINDOW_WORK* window)
{
    static s32 pokemon_no = -1;
    WindowKeyInfo* key = windowGetKeyInfo();
    s32 sel = -1;
    s32 closeID = 0;
    s32 openID = 0;
    FIGHT_TRAINER* trainer = (FIGHT_TRAINER*)windowGetParam(window, 0);
    bool cancelOK;
    windowGetParam(window, 1);
    cancelOK = windowGetParam(window, 2);
    menuSetDisp(window->menuID, 1);
    if (menuIsCheck(0x95)) {
        closeID = 0x95;
    } else if (menuIsCheck(0x96)) {
        closeID = 0x96;
    }
    {
        u16 stick = _menuFightGetRightStickInfo(0, 1);
        if (stick & 1) {
            sel = 0;
        } else if (stick & 8) {
            sel = 1;
        } else if (stick & 2) {
            sel = 2;
        } else if (stick & 4) {
            sel = 3;
        } else {
            u16 trig = key->trigger;
            if (trig & 0x80) {
                sel = 4;
            } else if (trig & 0x40) {
                sel = 5;
            }
        }
    }
    if (sel >= 0) {
        if (_menuFightGetPokemonPtr(trainer, (u16)sel) == 0) {
            sel = -1;
        }
        if (sel >= 0) {
            window->done = 1;
            window->cursor88 = sel;
        }
    }
    if (sel < 0) {
        if (key->trigger & 0x200) {
            if (cancelOK) {
                window->done = 1;
                window->cancel = 1;
                window->cursor88 = -1;
            }
        } else if (key->press & 0x400) {
            menuSetDisp(window->menuID, 0);
            pokemon_no = -1;
            u16 k = key->press;
            if (k & 1) {
                if (k & 8) {
                    pokemon_no = 5;
                } else if (k & 4) {
                    pokemon_no = 4;
                } else {
                    pokemon_no = 0;
                }
            } else if (k & 2) {
                pokemon_no = 2;
            } else if (k & 8) {
                pokemon_no = 1;
            } else if (k & 4) {
                pokemon_no = 3;
            }
            if (pokemon_no >= 0) {
                if (_menuFightGetPokemonPtr(trainer, (u16)pokemon_no) == 0) {
                    pokemon_no = -1;
                }
            }
            if (pokemon_no < 0) {
                openID = 0x95;
            } else {
                openID = 0x96;
            }
        }
    }
    menuFightButtonTimeOutCheck(window);
    if (closeID != openID) {
        if (closeID != 0) {
            menuClose(closeID);
        }
        if (window->done == 0) {
            if (openID == 0x95) {
                menuOpenCustom(0x95, window->menuID, 0, 0, 0, 1, trainer);
                menuSetDisp(0x95, 1);
                menuSetDisp(0x96, 0);
            } else if (openID == 0x96) {
                menuOpenCustom(0x96, window->menuID, 0, 0, 0, 2, trainer, &pokemon_no);
                menuSetDisp(0x96, 1);
                menuSetDisp(0x95, 0);
            }
        }
    }
}

void menuFightDrawSecretPokemon(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    s32 idx = -1;
    FIGHT_TRAINER* trainer = (FIGHT_TRAINER*)windowGetParam(window, 0);
    switch (sprite->id) {
    case 0x8d:
    case 0x94:
    case 0x9a:
        idx = 0;
        break;
    case 0x8e:
    case 0x95:
    case 0x9b:
        idx = 1;
        break;
    case 0x8f:
    case 0x96:
    case 0x9c:
        idx = 2;
        break;
    case 0x90:
    case 0x97:
    case 0x9d:
        idx = 3;
        break;
    case 0x91:
    case 0x98:
    case 0x9e:
        idx = 4;
        break;
    case 0x92:
    case 0x99:
    case 0x9f:
        idx = 5;
        break;
    }
    if (idx >= 0) {
        Pokemon* pk = _menuFightGetPokemonPtr(trainer, (u16)idx);
        if (pk != 0) {
            u32 color = menuSubCalcColor(window, sprite);
            switch (sprite->id) {
            case 0x9a:
            case 0x9b:
            case 0x9c:
            case 0x9d:
            case 0x9e:
            case 0x9f: {
                u16 spr = menuPokemonGetJoutaiSpriteID(pk, 1);
                windowDrawSprite(0, 0, window, spr, 0, winSpriteGetLayerID(window, sprite));
                break;
            }
            case 0x94:
            case 0x95:
            case 0x96:
            case 0x97:
            case 0x98:
            case 0x99: {
                s16 half;
                s16 base = (GSmsgGetRect(0x42d5) >> 16) + 2;
                s32 rect;
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x42d5);
                rect = (s16)(GSmsgGetRect(0x42c4) >> 16);
                half = (sprite->w - base - rect) / 2;
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), base + half, 0, color, 0x42c4);
                msgctrlSetValue(0x5f, (s16)pokemonGetStatus(pk, 0, 0x83, 0));
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, base + half, sprite->h, color, 0x4357);
                msgctrlSetValue(0x5f, (s16)pokemonGetStatus(pk, 0, 0x87, 0));
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4357);
                break;
            }
            case 0x93:
                break;
            case 0x8d:
            case 0x8e:
            case 0x8f:
            case 0x90:
            case 0x91:
            case 0x92: {
                u32 msg;
                u32 name = pokemonGetStatus(pk, 0, 0x77, 0);
                msgctrlSetValue(0x37, name);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
                switch ((u8)menuSubGetPokemonSexForFightDisp(pk)) {
                case 0:
                    msg = 0x9c5;
                    break;
                case 1:
                    msg = 0x9c6;
                    break;
                case 2:
                default:
                    msg = 0;
                    break;
                }
                if (msg != 0) {
                    msgctrlSetValue(0x37, GSmsgGetGSchar(msg));
                    GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0x7e, 0, color, 0x4276);
                }
                break;
            }
            }
        }
    }
}

void menuFightDrawSecretPokemonStatus(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    u32 color;
    Pokemon* pk;
    int slot = -1;
    SecretStatusArg* arg;
    FIGHT_TRAINER* trainer = (FIGHT_TRAINER*)windowGetParam(window, 0);
    arg = (SecretStatusArg*)windowGetParam(window, 1);
    if (arg->sel >= 0) {
        pk = _menuFightGetPokemonPtr(trainer, (u16)arg->sel);
        if (pk != 0) {
            color = menuSubCalcColor(window, sprite);
            switch (sprite->id) {
            case 0x2cd:
                if (pokemonGetSoubiItemDataId(pk) != 0) {
                    msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(pokemonGetSoubiItemDataId(pk)))));
                    GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4276);
                }
                break;
            case 0x2ce:
                winSpriteSetDisp(sprite, 0);
                if (pokemonGetSoubiItemDataId(pk) != 0) {
                    winSpriteSetDisp(sprite, 1);
                }
                break;
            case 0x2ca:
            {
                u16 x;
                u32 lbl = GSmsgGetGSchar(0x435a);
                msgctrlSetValue(0x37, lbl);
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x4276);
                x = GSmsgGetRect(0x4276) >> 16;
                msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(pokemonGetTokuseiDataId(pk)))));
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), x, 0, sprite->w, sprite->h, color, 0x4276);
                break;
            }
            case 0x2c2:
            case 0x2c3:
            case 0x2c4:
            case 0x2c5:
            case 0x2c6:
            case 0x2c7:
            {
                switch (sprite->id) {
                case 0x2c2:
                    slot = 0;
                    break;
                case 0x2c3:
                    slot = 1;
                    break;
                case 0x2c4:
                    slot = 3;
                    break;
                case 0x2c5:
                    slot = 2;
                    break;
                case 0x2c7:
                    slot = 4;
                    break;
                case 0x2c6:
                    slot = 5;
                    break;
                }
                if (slot == arg->sel) {
                    winSpriteSetDisp(sprite, 1);
                } else {
                    winSpriteSetDisp(sprite, 0);
                }
                break;
            }
            case 0x2c0:
            {
                void* data = pokemonDataBiosGetPtr(pokemonGetStatus(pk, 0, 0x6e, 0));
                u16 spr = (u16)zokuseiBiosGetSpriteID(pokemonDataBiosGetZokuseiDataId(data, 0));
                windowDrawSprite(0, 0, window, spr, 0, winSpriteGetLayerID(window, sprite));
                break;
            }
            case 0x2c1:
            {
                void* data = pokemonDataBiosGetPtr(pokemonGetStatus(pk, 0, 0x6e, 0));
                u8 z0 = zokuseiOf(data);
                u8 z1 = (u8)pokemonDataBiosGetZokuseiDataId(data, 1);
                if (z0 != z1) {
                    u16 spr = (u16)zokuseiBiosGetSpriteID(z1);
                    windowDrawSprite(0, 0, window, spr, 0, winSpriteGetLayerID(window, sprite));
                }
                break;
            }
            case 0x2b8:
            case 0x2b9:
            case 0x2ba:
            case 0x2bb:
            {
                switch (sprite->id) {
                case 0x2bb:
                    slot = 3;
                    break;
                case 0x2ba:
                    slot = 2;
                    break;
                case 0x2b9:
                    slot = 1;
                    break;
                case 0x2b8:
                    slot = 0;
                    break;
                }
                u16 waza = pokemonGetStatus(pk, 0, 0x7f, slot);
                if (waza != 0) {
                    u16 spr = (u16)zokuseiBiosGetSpriteID(wazaGetStatus(0, waza, 3, 0));
                    windowDrawSprite(0, 0, window, spr, 0, winSpriteGetLayerID(window, sprite));
                }
                break;
            }
            case 0x2cf:
            case 0x2d0:
            case 0x2d1:
            case 0x2d2:
            {
                switch (sprite->id) {
                case 0x2d2:
                    slot = 3;
                    break;
                case 0x2d1:
                    slot = 2;
                    break;
                case 0x2d0:
                    slot = 1;
                    break;
                case 0x2cf:
                    slot = 0;
                    break;
                }
                winSpriteSetDisp(sprite, 0);
                if ((u16)pokemonGetStatus(pk, 0, 0x7f, slot) != 0) {
                    winSpriteSetDisp(sprite, 1);
                }
                break;
            }
            case 0x2bc:
            case 0x2bd:
            case 0x2be:
            case 0x2bf:
            {
                switch (sprite->id) {
                case 0x2bf:
                    slot = 3;
                    break;
                case 0x2be:
                    slot = 2;
                    break;
                case 0x2bd:
                    slot = 1;
                    break;
                case 0x2bc:
                    slot = 0;
                    break;
                }
                if ((u16)pokemonGetStatus(pk, 0, 0x7f, slot) != 0) {
                    s16 x = (sprite->w - (s16)(GSmsgGetRect(0x42c4) >> 16)) / 2;
                    GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x42c4);
                    msgctrlSetValue(0x5f, pokemonGetStatus(pk, 0, 0x80, slot));
                    GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->h, color, 0x4357);
                    msgctrlSetValue(0x5f, pokemonWazaGetMaxPP(pk, slot));
                    GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4357);
                }
                break;
            }
            case 0x2b4:
            case 0x2b5:
            case 0x2b6:
            case 0x2b7:
            {
                switch (sprite->id) {
                case 0x2b7:
                    slot = 3;
                    break;
                case 0x2b6:
                    slot = 2;
                    break;
                case 0x2b5:
                    slot = 1;
                    break;
                case 0x2b4:
                    slot = 0;
                    break;
                }
                u16 waza = pokemonGetStatus(pk, 0, 0x7f, slot);
                if (waza != 0) {
                    u32 name = wazaGetStatus(0, waza, 1, 0);
                    if (name != 0) {
                        msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
                    }
                }
                break;
            }
            case 0x2cb:
            {
                s16 half;
                s16 base = (GSmsgGetRect(0x42d5) >> 16) + 2;
                s32 rect;
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x42d5);
                rect = (s16)(GSmsgGetRect(0x42c4) >> 16);
                half = (sprite->w - base - rect) / 2;
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), base + half, 0, color, 0x42c4);
                msgctrlSetValue(0x5f, (s16)pokemonGetStatus(pk, 0, 0x83, 0));
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, base + half, sprite->h, color, 0x4357);
                msgctrlSetValue(0x5f, (s16)pokemonGetStatus(pk, 0, 0x87, 0));
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4357);
                break;
            }
            case 0x2cc:
            {
                s16 x = GSmsgGetRect(0x42d4) >> 16;
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x42d4);
                msgctrlSetValue(0x5f, (u8)pokemonGetStatus(pk, 0, 0x7a, 0));
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), x, 0, sprite->w, sprite->h, color, 0x4351);
                break;
            }
            case 0x2c9:
            {
                s16 x = 0;
                void* pdata = pokemonDataBiosGetPtr(pokemonGetStatus(pk, 0, 0x6e, 0));
                if (pdata != 0) {
                    u32 name = pokemonDataBiosGetName(pdata);
                    u32 msg;
                    if (name != 0) {
                        msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x4277);
                        x = GSmsgGetRect(0x4277) >> 16;
                    }
                    switch ((u8)menuSubGetPokemonSexForDisp(pk)) {
                    case 0:
                        msg = 0x9c5;
                        break;
                    case 1:
                        msg = 0x9c6;
                        break;
                    case 2:
                    default:
                        msg = 0;
                        break;
                    }
                    if (msg != 0) {
                        msgctrlSetValue(0x37, GSmsgGetGSchar(msg));
                        GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x4276);
                    }
                }
                break;
            }
            case 0x2c8:
            {
                u32 name = pokemonGetStatus(pk, 0, 0x77, 0);
                msgctrlSetValue(0x37, name);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
                break;
            }
            }
        }
    }
}

void menuFightDrawTargetI(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    TargetArg* arg = (TargetArg*)windowGetParam(window, 0);
    s32 want;
    u32 color = menuSubCalcColor(window, sprite);
    int i;
    for (i = 0; i < 4; i++) {
        switch (arg->entry[i].menuId) {
        case 0x37:
            switch (window->menuID) {
            case 0xa0:
                want = 0x210;
                break;
            case 0xa3:
                want = 0x233;
                break;
            }
            switch (sprite->id) {
            case 0x238:
            case 0x215:
                msgctrlSetValue(0x37, arg->entry[i].unk8);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
                return;
            }
            break;
        case 0x40:
            switch (window->menuID) {
            case 0xa0:
                want = 0x212;
                break;
            case 0xa3:
                want = 0x235;
                break;
            }
            switch (sprite->id) {
            case 0x23a:
            case 0x217:
                msgctrlSetValue(0x37, arg->entry[i].unk8);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
                return;
            }
            break;
        case 0x38:
            switch (window->menuID) {
            case 0xa0:
                want = 0x211;
                break;
            case 0xa3:
                want = 0x234;
                break;
            }
            switch (sprite->id) {
            case 0x239:
            case 0x216:
                msgctrlSetValue(0x37, arg->entry[i].unk8);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
                return;
            }
            break;
        case 0x41:
            switch (window->menuID) {
            case 0xa0:
                want = 0x213;
                break;
            case 0xa3:
                want = 0x236;
                break;
            }
            switch (sprite->id) {
            case 0x23b:
            case 0x218:
                msgctrlSetValue(0x37, arg->entry[i].unk8);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
                return;
            }
            break;
        default:
            want = 0;
            break;
        }
        if (want == sprite->id) {
            winSpriteSetDisp(sprite, 1);
            return;
        }
    }
    winSpriteSetDisp(sprite, 0);
}

static void menuFightDrawIwaitStatusWaza(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, Pokemon* pokemon, u8 index, unsigned long color)
{
    if (pokemon != 0 && pokemonWazaCheckValid(pokemon, index)) {
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7f, index);
        u32 name = wazaGetStatus(0, waza, 1, 0);
        if (name != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(name));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4279);
        }
    }
}

void menuFightDrawIwaitStatus(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    u32 color;
    void* fop0;
    void* fop1;
    Pokemon* pk0;
    Pokemon* pk1;
    void* trainer;
    if (window->menuID == 0xa2) {
        trainer = fightSideGetValidFightTrainerPtr(fightFloorGetValidFightSidePtr(fightFloorGetNowPtr(), 1), 0);
    } else {
        trainer = fightSideGetValidFightTrainerPtr(fightFloorGetValidFightSidePtr(fightFloorGetNowPtr(), 0), 0);
    }
    fop0 = fightTrainerGetValidFightOutPokemonPtr(trainer, 0);
    fop1 = fightTrainerGetValidFightOutPokemonPtr(trainer, 1);
    pk0 = fop0 ? (Pokemon*)fightOutPokemonGetPokemonPtr(fightTrainerGetValidFightOutPokemonPtr(trainer, 0)) : 0;
    pk1 = fop1 ? (Pokemon*)fightOutPokemonGetPokemonPtr(fightTrainerGetValidFightOutPokemonPtr(trainer, 1)) : 0;
    color = menuSubCalcColor(window, sprite);
    switch (sprite->id) {
    case 0x1d3:
        if (fightKind_CheckFightKind(0x11)) {
            windowDrawSprite2(0, 0, sprite->w, sprite->h, *(u32*)window->color, window, 0x3f7, 0, winSpriteGetLayerID(window, sprite));
        } else {
            windowDrawSprite2(0, 0, sprite->w, sprite->h, *(u32*)window->color, window, 0x1ea, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    case 0x1bf:
    case 0x1ec:
        if (pk0 != 0) {
            u16 spr = zokuseiGetPokemonSpriteID(pk0->getPokemonDataPtr(), 0);
            if (spr != 0) {
                windowDrawSprite2(0, 0, sprite->w, sprite->h, *(u32*)window->color, window, spr, 0, winSpriteGetLayerID(window, sprite));
            }
        }
        break;
    case 0x1c0:
    case 0x1ed:
        if (pk0 != 0) {
            u8 z0 = (u8)pokemonDataBiosGetZokuseiDataId(pk0->getPokemonDataPtr(), 0);
            if (z0 != (u8)pokemonDataBiosGetZokuseiDataId(pk0->getPokemonDataPtr(), 1)) {
                u16 spr = zokuseiGetPokemonSpriteID(pk0->getPokemonDataPtr(), 1);
                windowDrawSprite2(0, 0, sprite->w, sprite->h, *(u32*)window->color, window, spr, 0, winSpriteGetLayerID(window, sprite));
            }
        }
        break;
    case 0x1c2:
    case 0x1ef:
        if (pk0 != 0) {
            msgctrlSetValue(0x37, pokemonGetStatus(pk0, 0, 0x77, 0));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
        }
        break;
    case 0x1c3:
    case 0x1f0:
        if (pk0 != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemon_GetTokuseiDataId(fop0)))));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4279);
        }
        break;
    case 0x1c5:
    case 0x1f2:
        menuFightDrawIwaitStatusWaza(window, sprite, pk0, 0, color);
        break;
    case 0x1c6:
    case 0x1f3:
        menuFightDrawIwaitStatusWaza(window, sprite, pk0, 1, color);
        break;
    case 0x1c7:
    case 0x1f4:
        menuFightDrawIwaitStatusWaza(window, sprite, pk0, 2, color);
        break;
    case 0x1c8:
    case 0x1f5:
        menuFightDrawIwaitStatusWaza(window, sprite, pk0, 3, color);
        break;
    case 0x1c9:
    case 0x1f6:
        if (pk1 != 0) {
            u16 spr = zokuseiGetPokemonSpriteID(pk1->getPokemonDataPtr(), 0);
            if (spr != 0) {
                windowDrawSprite2(0, 0, sprite->w, sprite->h, color, window, spr, 0, winSpriteGetLayerID(window, sprite));
            }
        }
        break;
    case 0x1ca:
    case 0x1f7:
        if (pk1 != 0) {
            u8 z0 = (u8)pokemonDataBiosGetZokuseiDataId(pk1->getPokemonDataPtr(), 0);
            if (z0 != (u8)pokemonDataBiosGetZokuseiDataId(pk1->getPokemonDataPtr(), 1)) {
                u16 spr = zokuseiGetPokemonSpriteID(pk1->getPokemonDataPtr(), 1);
                windowDrawSprite2(0, 0, sprite->w, sprite->h, color, window, spr, 0, winSpriteGetLayerID(window, sprite));
            }
        }
        break;
    case 0x1cc:
    case 0x1f9:
        if (pk1 != 0) {
            msgctrlSetValue(0x37, pokemonGetStatus(pk1, 0, 0x77, 0));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
        }
        break;
    case 0x1cd:
    case 0x1fa:
        if (pk1 != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemon_GetTokuseiDataId(fop1)))));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4279);
        }
        break;
    case 0x1cf:
    case 0x1fc:
        if (pk1 != 0) {
            menuFightDrawIwaitStatusWaza(window, sprite, pk1, 0, color);
        }
        break;
    case 0x1d0:
    case 0x1fd:
        if (pk1 != 0) {
            menuFightDrawIwaitStatusWaza(window, sprite, pk1, 1, color);
        }
        break;
    case 0x1d1:
    case 0x1fe:
        if (pk1 != 0) {
            menuFightDrawIwaitStatusWaza(window, sprite, pk1, 2, color);
        }
        break;
    case 0x1d2:
    case 0x1ff:
        if (pk1 != 0) {
            menuFightDrawIwaitStatusWaza(window, sprite, pk1, 3, color);
        }
        break;
    case 0x1c1:
    case 0x1ee:
        winSpriteSetDisp(sprite, 0);
        if (pk0 != 0) {
            if (pokemonGetSoubiItemDataId(pk0) != 0) {
                winSpriteSetDisp(sprite, 1);
            }
        }
        break;
    case 0x1cb:
    case 0x1f8:
        winSpriteSetDisp(sprite, 0);
        if (pk1 != 0) {
            if (pokemonGetSoubiItemDataId(pk1) != 0) {
                winSpriteSetDisp(sprite, 1);
            }
        }
        break;
    case 0x1c4:
    case 0x1f1:
        if (pk0 != 0) {
            if (pokemonGetSoubiItemDataId(pk0) != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(pokemonGetSoubiItemDataId(pk0)))));
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4279);
            }
        }
        break;
    case 0x1ce:
    case 0x1fb:
        if (pk1 != 0) {
            if (pokemonGetSoubiItemDataId(pk1) != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(pokemonGetSoubiItemDataId(pk1)))));
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4279);
            }
        }
        break;
    }
}

void menuFightDrawIPokemonStatus(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    u32 color;
    void* pk;
    int idx = 0;
    StatusAlloc* alloc = (StatusAlloc*)windowGetAllocPtr(window);
    pk = fightOutPokemonGetPokemonPtr(alloc->fightOut);
    color = menuSubCalcColor(window, sprite);
    switch (sprite->id) {
    case 0x14c:
    case 0x181: {
        u32 name = pokemonGetStatus(pk, 0, 0x77, 0);
        msgctrlSetValue(0x37, name);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
        break;
    }
    case 0x15f:
    case 0x194: {
        void* data = pokemonDataBiosGetPtr(pokemonGetStatus(pk, 0, 0x6e, 0));
        u16 spr = (u16)zokuseiBiosGetSpriteID(pokemonDataBiosGetZokuseiDataId(data, 0));
        windowDrawSprite(0, 0, window, spr, 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0x160:
    case 0x195: {
        void* data = pokemonDataBiosGetPtr(pokemonGetStatus(pk, 0, 0x6e, 0));
        u8 z0 = zokuseiOf(data);
        u8 z1 = (u8)pokemonDataBiosGetZokuseiDataId(data, 1);
        if (z0 != z1) {
            u16 spr = (u16)zokuseiBiosGetSpriteID(z1);
            windowDrawSprite(0, 0, window, spr, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    }
    case 0x14d:
    case 0x182: {
        s16 x;
        u32 tok;
        msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemon_GetTokuseiDataId(alloc->fightOut)))));
        x = GSmsgGetRect(0x435a) >> 16;
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), x, 0, sprite->w, sprite->h, color, 0x4277);
        break;
    }
    case 0x164:
        idx++;
    case 0x163:
        idx++;
    case 0x162:
        idx++;
    case 0x161: {
        u16 waza = pokemonGetStatus(pk, 0, 0x7f, idx);
        if (waza != 0) {
            u16 spr = (u16)zokuseiBiosGetSpriteID(wazaGetStatus(0, waza, 3, 0));
            windowDrawSprite(0, 0, window, spr, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    }
    case 0x156:
        idx++;
    case 0x154:
        idx++;
    case 0x152:
        idx++;
    case 0x150:
        if ((u16)pokemonGetStatus(pk, 0, 0x7f, idx) != 0) {
            s16 x = (sprite->w - (s16)(GSmsgGetRect(0x42c2) >> 16)) / 2;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x42c2);
            msgctrlSetValue(0x5f, pokemonGetStatus(pk, 0, 0x80, idx));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->h, color, 0x4358);
            msgctrlSetValue(0x5f, pokemonWazaGetMaxPP(pk, idx));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4358);
        }
        break;
    case 0x155:
        idx++;
    case 0x153:
        idx++;
    case 0x151:
        idx++;
    case 0x14f: {
        u16 waza = pokemonGetStatus(pk, 0, 0x7f, idx);
        if (waza != 0) {
            u32 name = wazaGetStatus(0, waza, 1, 0);
            if (name != 0) {
                s16 h;
                s16 th;
                msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                th = (u16)GSmsgGetRect(0x4277);
                h = sprite->h;
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, (s16)(h / 2 - th / 2), sprite->w, h, color, 0x4277);
            }
        }
        break;
    }
    case 0x199:
        idx++;
    case 0x198:
        idx++;
    case 0x197:
        idx++;
    case 0x196: {
        u16 waza = pokemonGetStatus(pk, 0, 0x7f, idx);
        if (waza != 0) {
            u16 spr = (u16)zokuseiBiosGetSpriteID(wazaGetStatus(0, waza, 3, 0));
            windowDrawSprite(0, 0, window, spr, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    }
    case 0x18b:
        idx++;
    case 0x189:
        idx++;
    case 0x187:
        idx++;
    case 0x185:
        if ((u16)pokemonGetStatus(pk, 0, 0x7f, idx) != 0) {
            s16 x = (sprite->w - (s16)(GSmsgGetRect(0x42c2) >> 16)) / 2;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x42c2);
            msgctrlSetValue(0x5f, pokemonGetStatus(pk, 0, 0x80, idx));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->h, color, 0x4358);
            msgctrlSetValue(0x5f, pokemonWazaGetMaxPP(pk, idx));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4358);
        }
        break;
    case 0x18a:
        idx++;
    case 0x188:
        idx++;
    case 0x186:
        idx++;
    case 0x184: {
        u16 waza = pokemonGetStatus(pk, 0, 0x7f, idx);
        if (waza != 0) {
            u32 name = wazaGetStatus(0, waza, 1, 0);
            if (name != 0) {
                s16 h;
                s16 th;
                msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                th = (u16)GSmsgGetRect(0x4277);
                h = sprite->h;
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, (s16)(h / 2 - th / 2), sprite->w, h, color, 0x4277);
            }
        }
        break;
    }
    case 0x14e:
    case 0x183:
        if (pokemonGetSoubiItemDataId(pk) != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(pokemonGetSoubiItemDataId(pk)))));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
        }
        break;
    case 0x15e:
    case 0x193:
        if (pokemonGetSoubiItemDataId(pk) != 0) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x158:
    case 0x15d:
    case 0x18d:
    case 0x192:
        if (alloc->fightOut != fightTargetGetPtr(0xc, alloc->fightOut, fightFloor_GetFightType(0))) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
}

void menuFightCtrlTarget(void) {}

void menuFightDrawTargetCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    if (menuItemBiosGetSelectFlag(window->menuID, sprite->id)) {
        if (sprite->id == menuGetCursorItemID(window->menuID)) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}

void menuFightButtonTargetSecret(tagWINDOW_WORK* window)
{
    WindowKeyInfo* key = windowGetKeyInfo();
    s32 sel = -1;
    TargetSecretEntry* p = (TargetSecretEntry*)windowGetParam(window, 0);
    u16 trig = key->trigger;
    if (trig & 1) {
        sel = 0;
    } else if (trig & 8) {
        sel = 1;
    } else if (trig & 4) {
        sel = 2;
    } else if (trig & 2) {
        sel = 3;
    } else if (trig & 0x200) {
        window->done = 1;
        window->cancel = 1;
        window->cursor88 = -1;
    }
    if (sel >= 0) {
        int i;
        for (i = 0; i < 2; i++, p++) {
            if (sel == targetSecretCursor(p->idA)) {
                if (sel > 2) {
                    sel = 2;
                }
                window->done = 1;
                window->cursor88 = sel;
                return;
            }
            if (sel == targetSecretCursor(p->idB)) {
                if (sel > 2) {
                    sel = 2;
                }
                window->done = 1;
                window->cursor88 = sel;
                return;
            }
        }
    }
    menuFightButtonTimeOutCheck(window);
}

void menuFightDrawTargetSecret(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    TargetSecretEntry* p = (TargetSecretEntry*)windowGetParam(window, 0);
    int i;
    for (i = 0; i < 2; i++, p++) {
        if (sprite->id == targetSecretSpriteID(p->idA)) {
            winSpriteSetDisp(sprite, 1);
            return;
        }
        if (sprite->id == targetSecretSpriteID(p->idB)) {
            winSpriteSetDisp(sprite, 1);
            return;
        }
    }
    winSpriteSetDisp(sprite, 0);
}

void menuFightOpenTimeup(void) { menuOpen(0x10b, 0); }

void menuFightButtonSecretKousan(tagWINDOW_WORK* window)
{
    menuButtonNormal(window);
    menuFightButtonTimeOutCheck(window);
}

void menuFightOpenCountDown(void) { menuOpenCustom(0x9d, -1, 0, 0, 0, 0); }

void menuFightCloseCountDown(void) { menuCloseCustom(0x9d, 0, 0); }

bool menuFightCloseCheckCountDown(void) { return menuIsCheck(0x9d); }

void menuFightOpenTotalTimer(void) { menuOpenCustom(0x9c, -1, 0, 0, 0, 0); }

void menuFightCloseTotalTimer(void) { menuCloseCustom(0x9c, 0, 0); }

bool menuFightCloseCheckTotalTimer(void) { return menuIsCheck(0x9c); }

void menuFightButtonTimeOutCheck(tagWINDOW_WORK* window)
{
    if (_menuFightCheckTimeOut()) {
        window->done = 1;
        window->cancel = 1;
    }
}

s32 menuFightCtrlTimer(tagWINDOW_WORK* window)
{
    static s32 oldTime = 0;
    if (window->state == 0) {
        oldTime = 0;
        if (window->menuID == 0x9c) {
            windowSetParam(window, 0, (s32)fightTimerAllGetNokoriTime());
        }
    }
    switch (window->menuID) {
    case 0x9c:
        if (!menuIsCheck(0x9d)) {
            windowSetParam(window, 0, (s32)fightTimerAllGetNokoriTime());
        }
        break;
    case 0x9d: {
        s32 t = (s32)fightTimerCommandGetNokoriTime();
        windowSetParam(window, 0, t);
        if (oldTime != t) {
            if (t <= 5) {
                if (t != 0) {
                    GSsndPlayNow(0x441);
                } else if (oldTime == 1) {
                    GSsndPlayNow(0x13);
                }
            }
            oldTime = t;
            if (menuIsCheck(0x9c)) {
                windowSetParam(windowSearchID(0x9c), 0, (s32)fightTimerAllGetNokoriTime());
            }
        }
        break;
    }
    }
    return 0;
}

void menuFightDrawTimer(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    static u16 half_digit_code[16] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                                      0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46};
    static u16 buff[8];
    switch (sprite->id) {
    case 0xa7:
    case 0xa8:
    case 0xa9:
    case 0xaa:
        winSpriteSetDisp(sprite, 0);
        if (0.5f <= menuGetTotalTime()) {
            winSpriteSetDisp(sprite, 1);
        }
        break;
    case 0xab:
        break;
    case 0xac: {
        s32 sec = windowGetParam(window, 0);
        s32 min = sec / 60;
        buff[2] = 0;
        buff[0] = half_digit_code[min / 10];
        buff[1] = half_digit_code[min % 10];
        msgctrlSetValue(0x37, (u32)buff);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, menuSubCalcColor(window, sprite), 0x4276);
        break;
    }
    case 0xad: {
        s32 sec = windowGetParam(window, 0);
        s32 s = sec % 60;
        buff[2] = 0;
        buff[0] = half_digit_code[s / 10];
        buff[1] = half_digit_code[s % 10];
        msgctrlSetValue(0x37, (u32)buff);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, menuSubCalcColor(window, sprite), 0x4276);
        break;
    }
    case 0xaf: {
        msgctrlSetValue(0x5f, windowGetParam(window, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, menuSubCalcColor(window, sprite), 0x4357);
        break;
    }
    }
}

static s32 getKane(void)
{
    u16 bairitu;
    u8 okane;
    void* hero;
    u8 level;
    u32 num;
    void* enemy;
    void* p;
    int i;
    num = fightFloor_GetFightTypeFightoutPokemonNum(0);
    if (!fightFloor_GetFightKindGetOkaneFlag(0)) {
        return -1;
    }
    hero = fightFloorGetGcHeroFightTrainerPtr(0);
    if (hero == 0) {
        return -1;
    }
    if (fightTrainer_GetHeroPtr(hero) == 0) {
        return -1;
    }
    okane = fightTrainer_GetOkaneBai(hero);
    enemy = fightTargetGetPtrAsNowFightType(9, hero);
    bairitu = fightTrainerKindDataBiosGetSyoukinBairitu(
        fightTrainerKindDataBiosGetPtr(fightTrainerDB_GetKindDataId(fightTrainer_GetFightTrainerDataId(enemy))));
    level = 0;
    for (i = 0; i < 6; i++) {
        p = fightTrainer_GetFightPokemonPtr(enemy, (u16)i);
        if (fightPokemonCheckValid(p)) {
            u8 l = figthPokemonGetLevel(p);
            if (level < l) {
                level = l;
            }
        }
    }
    for (i = 0; i < 6; i++) {
        p = fightTrainer_GetFightPokemonPtr(hero, (u16)i);
        if (fightPokemonCheckValid(p) && fightPokemon_GetCatchEntryFlag(p) == 1) {
            u8 l = figthPokemonGetLevel(p);
            if (level < l) {
                level = l;
            }
        }
    }
    u16 mult;
    if (!fightFloor_GetFightKindOkanePoolFlag(0)) {
        if (num <= 1) {
            mult = 1;
        } else {
            mult = 2;
        }
    } else {
        mult = 4;
    }
    return mult * (bairitu * (level * okane));
}

void menuFightDrawKane(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    s32 kane = getKane();
    winSpriteSetDisp(sprite, 0);
    if (kane != -1) {
        if (sprite->id == 6) {
            msgctrlSetValue(0x50, kane + heroGetStatus(0, 0xc, 0));
            s16 rect = GSmsgGetRect(0x434e) >> 16;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), sprite->w - rect, 0, -1, 0x434e);
        }
        winSpriteSetDisp(sprite, 1);
    }
}

void menuFightDrawTurn(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    switch (sprite->id) {
    case 2:
        msgctrlSetValue(0x5f, fightFloor_GetTurnCount(0));
        if (fightFloor_GetTurnCount(0) > 9) {
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, -1, 0x4351);
        } else {
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 8, 0, -1, 0x4351);
        }
        break;
    case 0x27c:
    case 0x295:
    case 0x2d3:
        if (window->cursor == 0) {
            menuSubDrawCursorBack(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, 0xff, 1);
        }
        break;
    case 0x27d:
    case 0x296:
    case 0x2d4:
        if (window->cursor == 1) {
            menuSubDrawCursorBack(winSpriteGetLayerID(window, sprite), 0, 0, sprite->w, sprite->h, 0xff, 1);
        }
        break;
    }
}
