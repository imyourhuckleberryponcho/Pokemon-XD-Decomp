#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightPokemon;
struct FightSide;
struct Pokemon;
struct FightActionData;

typedef bool (*FightLoopFunc)(void*, u16, void*);

struct MenuPokemonStatusArg {
    u32 data[12];
};

struct MenuPokemonStatusWork {
    u32 pad;
    MenuPokemonStatusArg arg;
};

struct MenuBallStatusArg {
    u32 balls;
    u16 flags;
};

struct MenuTargetEntry {
    u32 unk0;
    u32 menuId;
    void* name;
};

struct MenuTargetArg {
    MenuTargetEntry entry[4];
    u8 count;
    u8 tuusin;
    u32 user;
};

struct MenuWazaStatus {
    u8 data[0x44];
    u8 tuusin;
};

extern "C" {
s8 fightFloor_GetStatusMenuCnt(u8);
void fightFloor_SetStatusMenuCnt(u8, s8);
u8 fightFloorIsUseFightTimerCommand(s32);
u8 fightFloorIsUseFightTimerAll(s32);
u8 fightFloorLoopValidFightTrainer(s32, FightLoopFunc, void*, s32);
u8 fightFloorLoopValidFightOutPokemon(s32, FightLoopFunc, void*, s32);
u8 fightFloorIsNowEncountTuusinTaisen(s32);
u8 fightFloorIsNowEncountSnatchOnly(s32);
u32 fightFloorGetStatus(s32, s32, s32, s32);
void fightFloorSetStatus(s32, s32, s32, s32, u32);
FightSide* fightFloorGetValidFightSidePtr(s32, u16);
void fightFloorSetMenuFightAction(s32, FightOutPokemon*, void*);
u8 fightFloor_GetFightKind(s32);
u8 fightFloor_GetFightKindNigeruFlag(s32);
u8 fightKind_CheckFightKind(s32);
void menuFightCloseCountDown(void);
void menuFightCloseTotalTimer(void);
u8 menuFightCloseCheckCountDown(void);
u8 menuFightCloseCheckTotalTimer(void);
void menuFightOpenCountDown(void);
void menuFightOpenTotalTimer(void);
void GSthreadSwitch(void);
u8 menuIsCheck(u32);
void menuCloseCustom(u8, s32, s32);
void menuOpenCustom(u8, s32, s32, s32, s32, s32, ...);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
void winMsgOpenLevelUpStatus(u8*, s32);
void winMsgCloseLevelUpStatus(s32);
void fadeSet(s32, f32);
void fadeCheck(s32);
s32 menuPokemonStatusOpenWazaLearn(void*, void*);
s8 menuSubOpenYesNoField(void);
u32 itemGetStatus(s32, u16, s32, s32);
u32 wazaGetStatus(s32, u16, s32, s32);
u32 GSmsgGetGSchar(u32);
void msgctrlSetValue(s32, u32);
void winMsgCloseFight(s32);
u8 dbgMenuFightGetFightPokeStMenuOpenFlag(void);
void winMsgOpenFightNoWait(u32, s32, s32);
void winMsgOpenFight2(u32, s32, s32, u32);
void winMsgOpenFight(u32, s32, s32);
void fightMainWaitFrame(s16);
void fightMainWaitFrameEffect(s32);
u32 fightTrainerGetStatus(FIGHT_TRAINER*, s32, s32, u16);
void fightTypeDataBiosGetPtr(u16);
u8 fightTypeDataBiosGetFightoutPokemonNum(void);
u8 fightTypeDataBiosGetTrainerNum(void);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FIGHT_TRAINER*, u16);
u8 fightOutPokemonCheckFightActionSelect(FightOutPokemon*, s32);
u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon*, s32);
void fightOutPokemonInitFightActionBuff(FightOutPokemon*);
u16 fightGetFightResultId(void);
void fightSetFightResultId(s32);
u8 fightTimerCommandIsOver(void);
s32 menuFightOpenGBAMain(u32, FIGHT_TRAINER*, u16, u16);
s32 menuFightOpenGBAIrekae(u32, FIGHT_TRAINER*, u16, u16);
s32 gbaCommandGetAction(void);
s8 gbaCommandGetWazaDataId(s32);
u16 gbaCommandGetWazaTarget(s32);
u16 gbaCommandGetGBAChangePokemon(s32);
void fightOutPokemonCreateFightAction(FightOutPokemon*, s32, s32, s32, FightActionData*, s32);
void fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon*, s32, s32, s32, FightActionData*, u16, u16, s8, s32);
void fightOutPokemonCreateFightActionUseItem(FightOutPokemon*, s32, s32, s32, FightActionData*, u16, u16, u16, s32);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u32 pokemonGetStatus(void*, s32, s32, u16);
void pokemonSetStatus(void*, s32, s32, s32, s32);
u8 pokemonIsDarkPokemon(Pokemon*);
FightOutPokemon* fightSeqSelectDefensePokemonPtr(FightOutPokemon*, u16, u16, FightOutPokemon* (*)(FightOutPokemon*, u16, u16), s32, s32, s32);
FIGHT_TRAINER* fightSideGetValidFightTrainerPtr(FightSide*, u16);
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u16);
void fightTrainerTimeOutSelectFightAction(FIGHT_TRAINER*, FightOutPokemon*, u16);
s16 fightTrainerTimeOutSelectIrekaeFightPokemon(FIGHT_TRAINER*, FightOutPokemon*, u16);
void fightTrainerAllInitFightActionBuff(FIGHT_TRAINER*);
s16 fightTrainerAiSelectIrekaeDasuFightPokemon(FIGHT_TRAINER*, FightOutPokemon*, u16, u32);
u8 fightTrainerIsUsedItem(FIGHT_TRAINER*);
u8 fightTrainerIsSelectedItemBall(FIGHT_TRAINER*);
u16 fightTrainerGetFightOutPokemonToTemotiBanme(FIGHT_TRAINER*, FightOutPokemon*);
s16 fightTrainerGetFightPokemonToTemotiBanme(FIGHT_TRAINER*, u32);
u8 fightPokemonCheckFightOut(void*);
u8 fightPokemonCheckValid(void*);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, s32);
void Sequence_ResetStatus(u16, s32);
u8 getStaticBall__10bingo_biosFv(void);
void decStaticBall__10bingo_biosFv(void);
u8 GSgfxVideoGetVsyncRate(void);
void menuCreateOffScreen(f32, f32);
void menuOffScreenFadeSync(s32);
void menuReleaseOffScreen(f32);
u16 menuPocket2Open(s32, s32*, FIGHT_TRAINER*);
u8 menuPocket2GetLastSlotID(void);
void menuFightSetSeqOut__Fv(void);
s32 menuFightOpenPokemon(FIGHT_TRAINER*, FightOutPokemon*, u16, u8, u8);
s32 menuFightOpenTop(FIGHT_TRAINER*, void*, s32*, s32);
void menuFightCloseTop(s32);
s32 menuFightOpenWaza(FIGHT_TRAINER*, MenuWazaStatus*, u16, s32);
void menuFightCloseWaza(s32);
s32 menuFightOpenTarget(MenuTargetArg*, s32, s32);
void menuFightCloseTarget(s32);
u8 menuFightGetKeyWaitMenuId(void);
void menuFightStatusStartAnimHP(void*, void*);
void menuFightStatusSetActive(u32, s32);
s32 menuFightChkOpenBall(u8);
void* fightTargetGetPtr(s32, void*, u16);
u32 fightSideGetStatus(void*, s32, s32, u16);
void* fightTargetDataBiosGetPtr(u16);
s32 fightTargetDataBiosGetBuff(void*);
u8 fightTargetIsHostSide(FightOutPokemon*, u16);
void* fightOutPokemonGetNicknamePtr(FightOutPokemon*);
void fightOutPokemonToMenuPokemonStatus(FightOutPokemon*, MenuPokemonStatusArg*);
void fightOutPokemonToMenuWazaStatus(FightOutPokemon*, MenuWazaStatus*);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon*, u16, s32, u16*);
u16 fightOutPokemonGetSoubiItemDataId(FightOutPokemon*);
void fightTrainerToMenuBallStatus(FIGHT_TRAINER*, MenuBallStatusArg*);

extern u8 ServerWork[8];
extern s16 msgFrame;
extern u32* waza_data_number;
extern FightActionData fight_action_data_turn;
extern FightActionData fight_action_data_waza;
extern FightActionData fight_action_data_item;

u32 msgCtrlVal[4] = {0, 0, 0, 0};
}

static u8 bCharSkip;
static u8 _fightMenuGcHeroDefenseFlag;

static bool _fightMenuAllFightTrainerCloseStatusMenuSubCloseCheck(void*, u16, void*);
static bool _fightMenuAllFightTrainerCloseStatusMenuSub(void*, u16, void*);
static bool _fightMenuAllFightTrainerOpenStatusMenuSub(void*, u16, void*);
static bool _fightMenuAllFightOutPokemonCloseStatusMenuSubCloseCheck(void*, u16, void*);
static bool _fightMenuAllFightOutPokemonCloseStatusMenuSub(void*, u16, void*);
static bool _fightMenuAllFightOutPokemonOpenStatusMenuSub(void*, u16, void*);
static FightOutPokemon* _fightMenuFightTrainerAgbHeroSelectDefensePokemon(FightOutPokemon*, u16, u16);
static u8 _fightMenuFightTrainerGcHeroOpenMenuSubMain(FIGHT_TRAINER*, FightOutPokemon*, u16, s32);
static u8 _fightMenuFightTrainerGcHeroOpenMenuSubIrekae(FIGHT_TRAINER*, FightOutPokemon*, u16);
static u8 _fightMenuFightTrainerGcHeroOpenMenuSubItem(FIGHT_TRAINER*, FightOutPokemon*, u16);
static FightOutPokemon* _fightMenuFightTrainerGcHeroOpenMenuSubBallSelectTargetPokemon(FightOutPokemon*, u16, u16);
static u8 _fightMenuFightTrainerGcHeroOpenMenuSubWaza(FIGHT_TRAINER*, FightOutPokemon*, u16);
static FightOutPokemon* _fightMenuFightTrainerGcHeroOpenMenuSubWazaSelectDefensePokemon(FightOutPokemon*, u16, u16);
static void _fightMenuFightOutPokemonCloseStatusMenuSub(FightOutPokemon*, u16, bool, bool);
static void _fightMenuFightOutPokemonOpenStatusMenuSub(FightOutPokemon*, u16, bool, bool, bool);

extern "C" {
void fightMenuAllFightTrainerCloseStatusMenu(u8 wait);
void fightMenuAllFightTrainerOpenStatusMenu(void);
void fightMenuAllFightOutPokemonCloseStatusMenu(u8 wait);
void fightMenuAllFightOutPokemonOpenStatusMenu(u8 flag);
u32 fightMenuGetFightOutPokemonPtrToStatusMenuId(FightOutPokemon* p, u16 id, bool flag);
u32 fightMenuGetFightTrainerPtrToStatusMenuId(FIGHT_TRAINER* p, u16 id);
u8 fightMenuGetFightTrainerPtrToKeyWaitMenuId(FIGHT_TRAINER* p, u16 id);
void fightMenuFightTrainerCloseStatusMenu(FIGHT_TRAINER* p, u16 id, s32 wait);
void fightMenuFightTrainerOpenStatusMenu(FIGHT_TRAINER* p, u16 id);
void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon* p, u16 id, bool flag);
void fightMenuFightOutPokemonSetStatusMenuActiveFlag(FightOutPokemon* p, u16 id, s32 active);
void fightMsgctrlSetValue(s32 id, u32 value);
u32 fightMenuOpenMsg(u32 msg);
void fightMenuCloseMsg(void);
void fightMenuCloseInfoMenu(u8 wait);
void fightMenuOpenInfoMenu(s8 flag);
s16 fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(FIGHT_TRAINER* trainer, FightOutPokemon* p, u16 id, u8 cancel, u8 nested);

static inline void fightMenuCloseCustomBody(u8 menuId)
{
    if (fightFloor_GetStatusMenuCnt(menuId) == -1) {
        fightFloor_SetStatusMenuCnt(menuId, 15);
    }
}

u32 fightMenuCloseCustom(u8 menuId)
{
    fightMenuCloseCustomBody(menuId);
    return 0;
}

void fightMenuCloseInfoMenu(u8 wait)
{
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    if (fightFloorIsUseFightTimerCommand(0) == 1) {
        menuFightCloseCountDown();
    }
    if (fightFloorIsUseFightTimerAll(0) == 1) {
        menuFightCloseTotalTimer();
    }
    if (wait == 1) {
        fightMenuAllFightTrainerCloseStatusMenu(1);
        fightMenuAllFightOutPokemonCloseStatusMenu(1);
        if (fightFloorIsUseFightTimerCommand(0) == 1) {
            while (menuFightCloseCheckCountDown()) {
                GSthreadSwitch();
            }
        }
        if (fightFloorIsUseFightTimerAll(0) == 1) {
            while (menuFightCloseCheckTotalTimer()) {
                GSthreadSwitch();
            }
        }
    }
}

void fightMenuOpenInfoMenu(s8 flag)
{
    fightMenuAllFightTrainerOpenStatusMenu();
    fightMenuAllFightOutPokemonOpenStatusMenu(1);
    if (flag < 0) {
        if (fightFloorIsUseFightTimerCommand(0) == 1) {
            menuFightOpenCountDown();
        }
    }
    if (fightFloorIsUseFightTimerAll(0) == 1) {
        menuFightOpenTotalTimer();
    }
}

void fightMenuAllFightTrainerCloseStatusMenu(u8 wait)
{
    u8 closed;

    fightFloorLoopValidFightTrainer(0, _fightMenuAllFightTrainerCloseStatusMenuSub, 0, 0);
    if (wait == 1) {
        while (true) {
            closed = 1;
            fightFloorLoopValidFightTrainer(0, _fightMenuAllFightTrainerCloseStatusMenuSubCloseCheck, &closed, 0);
            if (closed == 1) {
                break;
            }
            GSthreadSwitch();
        }
    }
}
}

static bool _fightMenuAllFightTrainerCloseStatusMenuSubCloseCheck(void* trainer, u16 id, void* work)
{
    if (menuIsCheck(fightMenuGetFightTrainerPtrToStatusMenuId((FIGHT_TRAINER*)trainer, id)) == 1) {
        if (work != 0) {
            *(u8*)work = 0;
        }
    }
    return 1;
}

static bool _fightMenuAllFightTrainerCloseStatusMenuSub(void* trainer, u16 id, void* work)
{
    fightMenuFightTrainerCloseStatusMenu((FIGHT_TRAINER*)trainer, id, 0);
    return 1;
}

extern "C" {
void fightMenuAllFightTrainerOpenStatusMenu(void)
{
    fightFloorLoopValidFightTrainer(0, _fightMenuAllFightTrainerOpenStatusMenuSub, 0, 0);
}
}

static bool _fightMenuAllFightTrainerOpenStatusMenuSub(void* trainer, u16 id, void* work)
{
    fightMenuFightTrainerOpenStatusMenu((FIGHT_TRAINER*)trainer, id);
    return 1;
}

extern "C" {
void fightMenuAllFightOutPokemonCloseStatusMenu(u8 wait)
{
    fightFloorLoopValidFightOutPokemon(0, _fightMenuAllFightOutPokemonCloseStatusMenuSub, 0, 0);
    if (wait == 1) {
        while (fightFloorLoopValidFightOutPokemon(0, _fightMenuAllFightOutPokemonCloseStatusMenuSubCloseCheck, 0, 0) != 1) {
            GSthreadSwitch();
        }
    }
}
}

static bool _fightMenuAllFightOutPokemonCloseStatusMenuSubCloseCheck(void* p, u16 id, void* work)
{
    return menuIsCheck(fightMenuGetFightOutPokemonPtrToStatusMenuId((FightOutPokemon*)p, id, false)) != 1;
}

static bool _fightMenuAllFightOutPokemonCloseStatusMenuSub(void* p, u16 id, void* work)
{
    _fightMenuFightOutPokemonCloseStatusMenuSub((FightOutPokemon*)p, id, false, false);
    return 1;
}

extern "C" {
void fightMenuAllFightOutPokemonOpenStatusMenu(u8 flag)
{
    u8 work = flag;
    fightFloorLoopValidFightOutPokemon(0, _fightMenuAllFightOutPokemonOpenStatusMenuSub, &work, 0);
}
}

static bool _fightMenuAllFightOutPokemonOpenStatusMenuSub(void* p, u16 id, void* work)
{
    FightOutPokemon* pokemon = (FightOutPokemon*)p;
    bool flag;

    if (work == 0) {
        flag = true;
    } else {
        flag = *(bool*)work;
    }
    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    _fightMenuFightOutPokemonOpenStatusMenuSub(pokemon, id, flag, false, false);
    return 1;
}

extern "C" {
void fightMenuOpenLevelUpStatusMenu(u8* work, u8 value)
{
    if (work != 0) {
        *work = value;
        winMsgOpenLevelUpStatus(work, 1);
    }
}

void fightMenuSubMenuLvupStatus(s16* now, s16* old, s16* diff)
{
    if (now != 0 && old != 0 && diff != 0) {
        diff[1] = now[1] - old[1];
        diff[2] = now[2] - old[2];
        diff[3] = now[3] - old[3];
        diff[5] = now[5] - old[5];
        diff[6] = now[6] - old[6];
        diff[4] = now[4] - old[4];
    }
}

s32 fightMenuWazaWasure(void* pokemon, void* waza)
{
    s32 result;

    fadeSet(3, 0.5f);
    fadeCheck(1);
    result = menuPokemonStatusOpenWazaLearn(pokemon, waza);
    if (result == 4) {
        result = -1;
    }
    fadeSet(2, 0.5f);
    fadeCheck(1);
    return result;
}

void fightMenuCloseLevelUpStatusMenu(void)
{
    winMsgCloseLevelUpStatus(1);
}

u8 fightMenuYesNo(void)
{
    return menuSubOpenYesNoField() == 0;
}

void fightMenuWazaKoukaMsg(u32 msg, u32 value, u16 item)
{
    u32 name;

    fightMsgctrlSetValue(0x10, value);
    name = GSmsgGetGSchar(itemGetStatus(0, item, 1, 0));
    fightMsgctrlSetValue(0x29, name);
    fightMenuOpenMsg(msg);
}

void fightMenuWazaOutMsg(u32 value, u16 waza)
{
    u32 type;

    fightMsgctrlSetValue(0xF, value);
    type = GSmsgGetGSchar(wazaGetStatus(0, waza, 0xA, 0));
    fightMsgctrlSetValue(0xD, type);
    fightMsgctrlSetValue(0x28, GSmsgGetGSchar(wazaGetStatus(0, waza, 1, 0)));
    fightMsgctrlSetValue(0xE, GSmsgGetGSchar(wazaGetStatus(0, waza, 0xB, 0)));
    fightMenuOpenMsg(0x4F6D);
}

void fightMsgctrlSetValue(s32 id, u32 value)
{
    if (ServerWork[7] == 2) {
        switch (id) {
        case 0xF:
            msgCtrlVal[0] = value;
            break;
        case 0xD:
            msgCtrlVal[1] = value;
            break;
        case 0x28:
            msgCtrlVal[2] = value;
            break;
        case 0xE:
            msgCtrlVal[3] = value;
            break;
        default:
            msgctrlSetValue(id, value);
            break;
        }
    } else {
        msgctrlSetValue(id, value);
    }
}

void fightMenuCloseMsg(void)
{
    winMsgCloseFight(0);
}

u32 fightMenuOpenTrainerMsg(u32 msg)
{
    if (msg != 0 && dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        winMsgOpenFightNoWait(msg, 1, 1);
        return 1;
    }
    return 0;
}

u32 fightMenuOpenMsg2(u32 msg, u32 arg)
{
    if (msg != 0 && dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        winMsgOpenFight2(msg, 1, 1, arg);
        return 1;
    }
    return 0;
}

u32 fightMenuOpenMsg(u32 msg)
{
    if (ServerWork[7] == 2) {
        fightMainWaitFrame(msgFrame);
        ServerWork[7] = 0;
        fightMenuCloseMsg();
    }
    if (msgCtrlVal[0] != 0) {
        msgctrlSetValue(0xF, msgCtrlVal[0]);
        msgCtrlVal[0] = 0;
    }
    if (msgCtrlVal[1] != 0) {
        msgctrlSetValue(0xD, msgCtrlVal[1]);
        msgCtrlVal[1] = 0;
    }
    if (msgCtrlVal[2] != 0) {
        msgctrlSetValue(0x28, msgCtrlVal[2]);
        msgCtrlVal[2] = 0;
    }
    if (msgCtrlVal[3] != 0) {
        msgctrlSetValue(0xE, msgCtrlVal[3]);
        msgCtrlVal[3] = 0;
    }
    if (msg != 0 && dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        winMsgOpenFight(msg, 1, 1);
        return 1;
    }
    return 0;
}

u32 fightMenuFightTrainerAgbHeroOpenMenu(FIGHT_TRAINER* trainer, u16 id)
{
    FightOutPokemon* p;
    FightOutPokemon* target;
    u16 i;
    u32 num;
    s8 wazaIdx;
    u32 gbaWork;
    u16 waza;
    s32 action;
    u16 prev;
    u16 side;
    u16 t;
    u32 wazaTarget;
    u16 cnt;
    u16 k;
    s32 gba;
    u16 trainerNum;
    FIGHT_TRAINER* tr;
    FightSide* s;
    u8 found;
    s16 change;

    gbaWork = fightTrainerGetStatus(trainer, 0, 0x4B, 0);
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        menuOpenCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id), 0, 0, 0, 0, 0);
    }
    trainerNum = fightFloorGetStatus(0, 0, 0x16, 0);
    fightTypeDataBiosGetPtr(id);
    num = fightTypeDataBiosGetFightoutPokemonNum();
    prev = 0;
    for (i = 0; i < num; i++) {
    retry:
        p = fightTrainerGetValidFightOutPokemonPtr(trainer, i);
        if (p == 0) {
            prev = i;
            continue;
        }
        if (!fightOutPokemonCheckFightActionSelect(p, 1)) {
            prev = i;
            continue;
        }
        while (true) {
            fightOutPokemonInitFightActionBuff(p);
            if (fightGetFightResultId() == 1) {
                action = 5;
            } else if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
                action = 4;
            } else {
                gba = menuFightOpenGBAMain(gbaWork, trainer, i, id);
                action = gbaCommandGetAction();
                if (fightGetFightResultId() == 1) {
                    action = 5;
                }
            }
            if (action == 3) {
                fightOutPokemonCreateFightAction(p, 0, 8, 0, &fight_action_data_turn, 0);
                goto end;
            } else if (action == 1) {
                if (fightOutPokemonCheckFightActionWazaSelect(p, 1)) {
                    prev = i;
                    break;
                }
                wazaIdx = gbaCommandGetWazaDataId(gba);
                if (wazaIdx < 0) {
                    continue;
                }
                waza = pokemonGetStatus(fightOutPokemonGetPokemonPtr(p), 0, 0x7F, wazaIdx);
                if (waza == 0 || waza >= *waza_data_number || waza == 0x176) {
                    continue;
                }
                target = 0;
                FightOutPokemon* sel = fightSeqSelectDefensePokemonPtr(p, waza, id, _fightMenuFightTrainerAgbHeroSelectDefensePokemon, 1, 0, -1);
                if (sel != 0) {
                    target = sel;
                } else {
                    wazaTarget = gbaCommandGetWazaTarget(gba);
                    cnt = 0;
                    found = 0;
                    for (side = 0; side < 2; side++) {
                        s = fightFloorGetValidFightSidePtr(0, side);
                        if (s == 0) {
                            continue;
                        }
                        for (t = 0; t < trainerNum; t++) {
                            tr = fightSideGetValidFightTrainerPtr(s, t);
                            if (tr == 0) {
                                continue;
                            }
                            for (k = 0; k < num; k++) {
                                target = (FightOutPokemon*)fightTrainerGetStatus(tr, 0, 0x46, k);
                                if (cnt == wazaTarget) {
                                    found = 1;
                                    break;
                                }
                                cnt++;
                            }
                            if (found == 1) {
                                break;
                            }
                        }
                        if (found == 1) {
                            break;
                        }
                    }
                }
                if (target == 0) {
                    continue;
                }
                fightOutPokemonCreateFightActionAttackWaza(p, 0, 0x13, 0, &fight_action_data_waza, waza,
                    fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, id), wazaIdx, 0);
                prev = i;
                break;
            } else if (action == 2) {
                change = pokemonGetStatus((void*)fightTrainerGetStatus(trainer, 0, 0x45, gbaCommandGetGBAChangePokemon(gba)), 0, 0xCE, 0);
                if (change < 0) {
                    continue;
                }
                fightOutPokemonCreateFightAction(p, 0, 9, 0, &fight_action_data_turn, change);
                if (prev < i) prev = i;
                break;
            } else if (action == 5) {
                fightTrainerAllInitFightActionBuff(trainer);
                if (fightFloorIsNowEncountTuusinTaisen(0)) {
                    if (menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id))) {
                        menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id), 0, 1);
                    }
                }
                return 0;
            } else if (action == 0) {
                if (i != 0) {
                    i = prev;
                }
                goto retry;
            } else {
                prev = i;
                fightTrainerTimeOutSelectFightAction(trainer, p, id);
                break;
            }
        }
    }
end:
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        if (menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id))) {
            menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id), 0, 1);
        }
    }
    return 1;
}
}

static FightOutPokemon* _fightMenuFightTrainerAgbHeroSelectDefensePokemon(FightOutPokemon*, u16, u16)
{
    return 0;
}

extern "C" {
s16 fightMenuFightTrainerAgbHeroSelectIrekaeFightPokemon(FIGHT_TRAINER* trainer, FightOutPokemon* p, u16 id, u32 target)
{
    u32 gbaWork;
    u32 num;
    u16 i;
    s32 gba;
    s32 action;
    s16 result;

    gbaWork = fightTrainerGetStatus(trainer, 0, 0x4B, 0);
    fightTypeDataBiosGetPtr(id);
    num = fightTypeDataBiosGetFightoutPokemonNum();
    for (i = 0; i < num; i++) {
        if (fightTrainerGetStatus(trainer, 0, 0x46, i) == target) {
            break;
        }
    }
    if ((u32)i < num) {
        return fightTrainerAiSelectIrekaeDasuFightPokemon(trainer, p, id, target);
    }
    if (fightGetFightResultId() == 1) {
        action = 5;
    } else if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
        action = 4;
    } else {
        if (fightFloorIsNowEncountTuusinTaisen(0)) {
            menuOpenCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id), 0, 0, 0, 0, 0);
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1) {
            menuFightOpenCountDown();
        }
        if (fightFloorIsUseFightTimerAll(0) == 1) {
            menuFightOpenTotalTimer();
        }
        gba = menuFightOpenGBAIrekae(gbaWork, trainer, (u16)i, id);
        action = gbaCommandGetAction();
        if (fightGetFightResultId() == 1) {
            action = 5;
        }
    }
    switch (action) {
    case 2:
        result = pokemonGetStatus((void*)fightTrainerGetStatus(trainer, 0, 0x45, gbaCommandGetGBAChangePokemon(gba)), 0, 0xCE, 0);
        break;
    case 4:
        result = fightTrainerTimeOutSelectIrekaeFightPokemon(trainer, (FightOutPokemon*)target, id);
        break;
    case 5:
        result = -2;
        break;
    }
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        if (menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id))) {
            menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id), 0, 1);
        }
    }
    return result;
}

u32 fightMenuFightTrainerGcHeroOpenMenu(FIGHT_TRAINER* trainer, u16 id, u8 cancel)
{
    u16 j;
    u16 i;
    FightOutPokemon* p;
    u32 num;
    u16 prev;
    s32 cursor;
    s32 top;
    u8 result;
    u8 work[0x18];

    fightTypeDataBiosGetPtr(id);
    num = fightTypeDataBiosGetFightoutPokemonNum();
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        menuOpenCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id), 0, 0, 0, 0, 0);
    }
    prev = 0;
    i = 0;
    cursor = 0;
    bCharSkip = 0;
    for (; i < num; i++) {
    retry:
        p = fightTrainerGetValidFightOutPokemonPtr(trainer, i);
        if (p == 0) {
            prev = i;
            continue;
        }
        if (!fightOutPokemonCheckFightActionSelect(p, 1)) {
            prev = i;
            continue;
        }
        if (fightGetFightResultId() == 1) {
            goto result;
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
            goto timeout;
        }
        fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 1);
        cursor = 0;
        while (true) {
            fightOutPokemonInitFightActionBuff(p);
            fightFloorSetMenuFightAction(0, p, work);
            work[0x17] = fightFloorIsNowEncountTuusinTaisen(0);
            top = menuFightOpenTop(trainer, work, &cursor, 1);
            if (fightGetFightResultId() == 1) {
                fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 0);
                menuFightCloseTop(1);
                goto result;
            }
            if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1 && top < 0) {
                fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 0);
                menuFightCloseTop(1);
                goto timeout;
            }
            if (top >= 0) {
                menuFightCloseTop(1);
            }
            result = _fightMenuFightTrainerGcHeroOpenMenuSubMain(trainer, p, id, top);
            if (fightGetFightResultId() == 1) {
                fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 0);
                menuFightCloseTop(1);
            result:
                fightTrainerAllInitFightActionBuff(trainer);
                goto end;
            }
            if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1 && result != 0) {
                fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 0);
                menuFightCloseTop(1);
            timeout:
                fightOutPokemonInitFightActionBuff(p);
                fightTrainerTimeOutSelectFightAction(trainer, p, id);
                prev = i;
                break;
            }
            if (result == 1) {
                if (bCharSkip) {
                    bCharSkip = 0;
                    goto end;
                }
                if (fightTrainerIsUsedItem(trainer) != 1) {
                    if (i != 0) {
                        i = prev;
                        fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 0);
                        menuFightCloseTop(1);
                        goto retry;
                    }
                    if (cancel == 1 && i == 0) {
                        fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 0);
                        menuFightCloseTop(1);
                        for (j = 0; j < num; j++) {
                            if (fightTrainerGetValidFightOutPokemonPtr(trainer, j) != 0) {
                                pokemonSetStatus(fightTrainerGetValidFightOutPokemonPtr(trainer, j), 0, 0x120, 0, 0);
                            }
                        }
                        return 0;
                    }
                }
            } else if (result != 2) {
                fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 0);
                prev = i;
                if (top == 3 && fightFloor_GetFightKindNigeruFlag(0)) {
                    goto end;
                }
                break;
            }
        }
    }
end:
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        if (menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id))) {
            menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id), 0, 1);
        }
    }
    for (j = 0; j < num; j++) {
        if (fightTrainerGetValidFightOutPokemonPtr(trainer, j) != 0) {
            pokemonSetStatus(fightTrainerGetValidFightOutPokemonPtr(trainer, j), 0, 0x120, 0, 0);
        }
    }
    return 1;
}
}

static u8 _fightMenuFightTrainerGcHeroOpenMenuSubMain(FIGHT_TRAINER* trainer, FightOutPokemon* p, u16 id, s32 top)
{
    u8 result = 0;
    u8 check;

    switch (top) {
    case 0:
        check = fightOutPokemonCheckFightActionWazaSelect(p, 1);
        if (check == 1) {
            fightMsgctrlSetValue(0x11, (u32)p);
            fightMenuOpenMsg(0x4EE5);
            fightMainWaitFrame(0x40);
            fightMenuCloseMsg();
        }
        if (check == 0) {
            if (!_fightMenuFightTrainerGcHeroOpenMenuSubWaza(trainer, p, id)) {
                result = 2;
                if (fightKind_CheckFightKind(0xA) || fightKind_CheckFightKind(0x11)) {
                    result = 1;
                }
            }
        }
        break;
    case 1:
        s32 cmpv = fightFloorGetStatus(0, 0, 0x20, 0);
        if (cmpv == 0) {
            fightMenuOpenMsg(0x4EDE);
            fightMainWaitFrame(0x40);
            fightMenuCloseMsg();
            result = 2;
        } else if (!_fightMenuFightTrainerGcHeroOpenMenuSubItem(trainer, p, id)) {
            result = 2;
        }
        break;
    case 2:
        if (!_fightMenuFightTrainerGcHeroOpenMenuSubIrekae(trainer, p, id)) {
            result = 2;
        }
        break;
    case 3:
        if ((fightFloorGetStatus(0, 0, 0x22, 0) != 0) == 1) {
            fightOutPokemonCreateFightAction(p, 0, 8, 0, &fight_action_data_turn, 0);
        } else if ((fightFloorGetStatus(0, 0, 0x21, 0) != 0) == 1) {
            fightOutPokemonCreateFightAction(p, 0, 0xA, 0, &fight_action_data_turn, 0);
        } else {
            result = 2;
        }
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

static u8 _fightMenuFightTrainerGcHeroOpenMenuSubIrekae(FIGHT_TRAINER* trainer, FightOutPokemon* p, u16 id)
{
    s16 change = fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(trainer, p, id, 1, 1);
    if (change < 0) {
        return 0;
    }
    fightOutPokemonCreateFightAction(p, 0, 9, 0, &fight_action_data_turn, change);
    return 1;
}

extern "C" {
s16 fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(FIGHT_TRAINER* trainer, FightOutPokemon* p, u16 id, u8 cancel, u8 nested)
{
    s32 sel;
    void* pokemon;

    while (true) {
        if (fightGetFightResultId() == 1) {
            return -2;
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
            goto timeout;
        }
        if (fightFloorIsNowEncountTuusinTaisen(0) && nested == 0) {
            menuOpenCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id), 0, 0, 0, 0, 0);
        }
        if (!fightFloorIsNowEncountTuusinTaisen(0)) {
            menuFightSetSeqOut__Fv();
            fightMenuCloseInfoMenu(1);
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1) {
            menuFightOpenCountDown();
        }
        if (fightFloorIsUseFightTimerAll(0) == 1) {
            menuFightOpenTotalTimer();
        }
        sel = menuFightOpenPokemon(trainer, p, id, cancel, fightFloorIsNowEncountTuusinTaisen(0));
        fightMainWaitFrameEffect(0xA);
        if (!fightFloorIsNowEncountTuusinTaisen(0) && nested == 1) {
            fightMenuOpenInfoMenu(-1);
            if (p != 0) {
                fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 1);
            }
        }
        if (fightFloorIsNowEncountTuusinTaisen(0) && nested == 0) {
            if (menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id))) {
                menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer, id), 0, 1);
            }
        }
        if (fightGetFightResultId() == 1) {
            return -2;
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1 && sel < 0) {
        timeout:
            if (nested == 0) {
                return fightTrainerTimeOutSelectIrekaeFightPokemon(trainer, p, id);
            }
        } else if (sel >= 0) {
            pokemon = (void*)fightTrainerGetStatus(trainer, 0, 0x45, sel);
            if (fightPokemonCheckValid(pokemon) && (pokemonGetStatus(pokemon, 0, 0xD2, 0) != 0) != 1) {
                return pokemonGetStatus(pokemon, 0, 0xCE, 0);
            }
            continue;
        }
        if (cancel != 0) {
            return -1;
        }
    }
}
}

static u8 _fightMenuFightTrainerGcHeroOpenMenuSubItem(FIGHT_TRAINER* trainer, FightOutPokemon* p, u16 id)
{
    u16 item;
    u32 slot;
    u16 i;
    FightOutPokemon* op;
    u16 seq;
    u8 out[2];
    u8 joutai8[2];
    u8 joutai7[2];
    s32 target;
    u16 relId;
    s32 flag;

    target = 0;
    slot = 0xFF;
    for (i = 0; i < 2; i++) {
        out[i] = 0;
        joutai8[i] = 0;
        joutai7[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        op = (FightOutPokemon*)fightTrainerGetStatus(trainer, 0, 0x46, i);
        if (op != 0) {
            out[i] = fightPokemonCheckFightOut((void*)fightTrainerGetStatus(trainer, 0, 0x45, fightTrainerGetFightOutPokemonToTemotiBanme(trainer, op)));
            joutai8[i] = fightOutPokemonIsJoutaiDataId(op, 8);
            joutai7[i] = fightOutPokemonIsJoutaiDataId(op, 7);
        }
    }
    if (fightTrainerGetStatus(trainer, 0, 0x44, 0) == 0) {
        return 0;
    }
    s32 tmp1 = pokemonGetStatus(p, 0, 0xD5, 0);
    target = fightTrainerGetFightPokemonToTemotiBanme(trainer, tmp1);
    while (true) {
        if (fightKind_CheckFightKind(0xD)) {
            if (getStaticBall__10bingo_biosFv()) {
                item = 1;
                decStaticBall__10bingo_biosFv();
            }
        } else {
            menuFightSetSeqOut__Fv();
            fightMenuCloseInfoMenu(1);
            menuCreateOffScreen(8.0f / GSgfxVideoGetVsyncRate(), 50.0f);
            menuOffScreenFadeSync(1);
            if (fightFloorIsNowEncountSnatchOnly(0)) {
                item = menuPocket2Open(6, &target, trainer);
            } else {
                item = menuPocket2Open(1, &target, trainer);
            }
            fightMainWaitFrameEffect(0xA);
            slot = menuPocket2GetLastSlotID();
        }
        if (item != 0 && (u8)itemGetStatus(0, item, 2, 0) == 2) {
            for (i = 0; i < 2; i++) {
                op = (FightOutPokemon*)fightTrainerGetStatus(trainer, 0, 0x46, i);
                if (op != 0) {
                    seq = pokemonGetStatus(op, 0, 0xEE, 0);
                    if (seq != 0) {
                        if (joutai8[i] == 1 && !fightOutPokemonIsJoutaiDataId(op, 8)) {
                            Sequence_ResetStatus(seq, 1);
                        }
                        if (joutai7[i] == 1 && !fightOutPokemonIsJoutaiDataId(op, 7)) {
                            Sequence_ResetStatus(seq, 2);
                        }
                    }
                }
            }
        }
        if (!fightKind_CheckFightKind(0xD)) {
            fightMenuOpenInfoMenu(-1);
            if (p != 0) {
                fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, id, 1);
            }
        }
        menuReleaseOffScreen(8.0f / GSgfxVideoGetVsyncRate());
        fightMainWaitFrameEffect(0xA);
        if (item == 0) {
            return 0;
        }
        if ((u8)itemGetStatus(0, item, 2, 0) == 1) {
            if (fightTrainerIsSelectedItemBall(trainer) != 1) {
                FightOutPokemon* sel = _fightMenuFightTrainerGcHeroOpenMenuSubBallSelectTargetPokemon(p, item, id);
                if (sel != 0) {
                    relId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(sel, id);
                    flag = 0;
                    break;
                }
            }
        } else {
            if ((u8)itemGetStatus(0, item, 2, 0) == 2) {
                for (i = 0; i < 2; i++) {
                    op = (FightOutPokemon*)fightTrainerGetStatus(trainer, 0, 0x46, i);
                    if (op != 0 && out[i] == 0 && fightOutPokemonCheckFightOut(op) == 1) {
                        pokemonSetStatus(op, 0, 0x120, 0, 1);
                    }
                }
            }
            flag = 1;
            relId = target;
            break;
        }
    }
    fightOutPokemonCreateFightActionUseItem(p, 0, 0x12, 0, &fight_action_data_item, item, relId, slot, flag);
    return 1;
}

static FightOutPokemon* _fightMenuFightTrainerGcHeroOpenMenuSubBallSelectTargetPokemon(FightOutPokemon* p, u16 item, u16 id)
{
    MenuTargetArg arg;
    FightOutPokemon* target;
    s32 sel;

    while (true) {
        target = (FightOutPokemon*)fightTargetGetPtr(0xF, p, id);
        arg.entry[0].menuId = fightOutPokemonCheckFightOut(target) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(target, id, false) : 0;
        arg.entry[0].name = fightOutPokemonGetNicknamePtr(target);
        target = (FightOutPokemon*)fightTargetGetPtr(0x10, p, id);
        arg.entry[1].menuId = fightOutPokemonCheckFightOut(target) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(target, id, false) : 0;
        arg.entry[1].name = fightOutPokemonGetNicknamePtr(target);
        arg.entry[2].name = 0;
        arg.entry[3].menuId = 0;
        arg.count = 2;
        arg.tuusin = fightFloorIsNowEncountTuusinTaisen(0);
        arg.user = (u32)p;
        sel = menuFightOpenTarget(&arg, 0, 1);
        if (sel == 0) {
            target = (FightOutPokemon*)fightTargetGetPtr(0xF, p, id);
        } else if (sel == 1) {
            target = (FightOutPokemon*)fightTargetGetPtr(0x10, p, id);
        } else {
            menuFightCloseTarget(1);
            return 0;
        }
        if (fightOutPokemonCheckFightOut(target)) {
            if (!pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(target)) && fightFloor_GetFightKind(0) != 0xC && fightFloor_GetFightKind(0) != 0xD) {
                fightMenuOpenMsg(0x5001);
                fightMenuCloseMsg();
            } else {
                menuFightCloseTarget(1);
                return target;
            }
        }
    }
}

static u8 _fightMenuFightTrainerGcHeroOpenMenuSubWaza(FIGHT_TRAINER* trainer, FightOutPokemon* p, u16 id)
{
    u8 num;
    MenuWazaStatus status;
    Pokemon* pokemon;
    s32 sel;
    u8 check;
    u16 waza;
    u16 other;
    u32 msg;
    FightOutPokemon* target;

    fightTypeDataBiosGetPtr(id);
    num = fightTypeDataBiosGetFightoutPokemonNum();
    while (true) {
        fightOutPokemonToMenuWazaStatus(p, &status);
        status.tuusin = fightFloorIsNowEncountTuusinTaisen(0);
        pokemon = fightOutPokemonGetPokemonPtr(p);
        sel = menuFightOpenWaza(trainer, &status, pokemonGetStatus(p, 0, 0x101, 0), 1);
        if (sel < 0) {
            menuFightCloseWaza(1);
            return 0;
        }
        if (sel > 4) {
            if ((fightFloorGetStatus(0, 0, 0x22, 0) != 0) == 1) {
                fightOutPokemonCreateFightAction(p, 0, 8, 0, &fight_action_data_turn, 0);
                bCharSkip = 1;
                if (fightGetFightResultId() == 0) {
                    if (fightTargetIsHostSide(p, id) == 1) {
                        fightSetFightResultId(4);
                    } else {
                        fightSetFightResultId(5);
                    }
                }
            }
            return 0;
        }
        check = fightOutPokemonCheckCanOutOkWazaBanme(p, sel, 1, &other);
        waza = pokemonGetStatus(pokemon, 0, 0x7F, sel);
        if (check != 0) {
            fightMsgctrlSetValue(0x11, (u32)p);
            fightMsgctrlSetValue(0x28, GSmsgGetGSchar(wazaGetStatus(0, waza, 1, 0)));
            fightFloorSetStatus(0, 0, 0x56, 0, fightOutPokemonGetSoubiItemDataId(p));
        }
        switch (check) {
        case 6:
            msg = 0x4F42;
            break;
        case 5:
            fightMsgctrlSetValue(0x28, GSmsgGetGSchar(wazaGetStatus(0, other, 1, 0)));
            msg = 0x4F9A;
            break;
        case 4:
            msg = 0x4EE9;
            break;
        case 3:
            msg = 0x4EE8;
            break;
        case 2:
            msg = 0x4EE7;
            break;
        case 1:
            msg = 0x4EE6;
            break;
        }
        if (check != 0) {
            fightMenuOpenMsg(msg);
            fightMainWaitFrame(0x40);
            fightMenuCloseMsg();
            continue;
        }
        waza = pokemonGetStatus(pokemon, 0, 0x7F, sel);
        if (waza == 0 || waza >= *waza_data_number || waza == 0x176) {
            continue;
        }
        _fightMenuGcHeroDefenseFlag = 0;
        target = fightSeqSelectDefensePokemonPtr(p, waza, id, _fightMenuFightTrainerGcHeroOpenMenuSubWazaSelectDefensePokemon, 1, 0, -1);
        if ((fightFloorIsNowEncountTuusinTaisen(0) == 1) == 0 && !fightKind_CheckFightKind(0xA) && !fightKind_CheckFightKind(0x11)) {
        } else if (!_fightMenuGcHeroDefenseFlag) {
            if (num < 2) {
                fightTypeDataBiosGetPtr(id);
                if ((fightTypeDataBiosGetTrainerNum() == 2) == 0) {
                    goto ok;
                }
            }
            if (_fightMenuFightTrainerGcHeroOpenMenuSubWazaSelectDefensePokemon(p, waza, id) == 0) {
                continue;
            }
        }
    ok:
        if (target == 0) {
            continue;
        }
        menuFightCloseWaza(1);
        fightOutPokemonCreateFightActionAttackWaza(p, 0, 0x13, 0, &fight_action_data_waza, waza,
            fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, id), sel, 0);
        return 1;
    }
}

static FightOutPokemon* _fightMenuFightTrainerGcHeroOpenMenuSubWazaSelectDefensePokemon(FightOutPokemon* p, u16 waza, u16 id)
{
    MenuTargetArg arg;
    FightOutPokemon* target;
    s32 sel;

    while (true) {
        target = (FightOutPokemon*)fightTargetGetPtr(0xF, p, id);
        arg.entry[0].menuId = fightOutPokemonCheckFightOut(target) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(target, id, false) : 0;
        arg.entry[0].name = fightOutPokemonGetNicknamePtr(target);
        target = (FightOutPokemon*)fightTargetGetPtr(0x10, p, id);
        arg.entry[1].menuId = fightOutPokemonCheckFightOut(target) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(target, id, false) : 0;
        arg.entry[1].name = fightOutPokemonGetNicknamePtr(target);
        target = (FightOutPokemon*)fightTargetGetPtr(0xE, p, id);
        arg.entry[2].menuId = fightOutPokemonCheckFightOut(target) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(target, id, false) : 0;
        arg.entry[2].name = fightOutPokemonGetNicknamePtr(target);
        arg.entry[3].menuId = 0;
        arg.count = 3;
        arg.tuusin = fightFloorIsNowEncountTuusinTaisen(0);
        arg.user = (u32)p;
        sel = menuFightOpenTarget(&arg, 0, 1);
        _fightMenuGcHeroDefenseFlag = 1;
        if (sel < 0) {
            menuFightCloseTarget(1);
            return 0;
        }
        if (sel == 0) {
            target = (FightOutPokemon*)fightTargetGetPtr(0xF, p, id);
        } else if (sel == 1) {
            target = (FightOutPokemon*)fightTargetGetPtr(0x10, p, id);
        } else if (sel == 2) {
            target = (FightOutPokemon*)fightTargetGetPtr(0xE, p, id);
        } else {
            continue;
        }
        if (fightOutPokemonCheckFightOut(target)) {
            menuFightCloseTarget(1);
            return target;
        }
    }
}

extern "C" {
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(u32 menuId, FightOutPokemon* p, u16 id, s32 wait, bool flag)
{
    u8 ids[4] = {0x37, 0x38, 0x40, 0x41};
    enum TsE { TsE0 };
    enum TsE mine;
    u8 m;
    u8 i;

    if (menuId != 0) {
        mine = (enum TsE)(menuId);
    } else {
        mine = (enum TsE)(fightMenuGetFightOutPokemonPtrToStatusMenuId(p, id, flag));
    }
    for (i = 0; i < 4; i++) {
        m = ids[i];
        if (mine != m && menuIsCheck(m)) {
            fightMenuCloseCustom(m);
            menuCloseCustom(m, 2, wait);
        }
    }
}

void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon* p, u16 id, bool flag)
{
    _fightMenuFightOutPokemonCloseStatusMenuSub(p, id, flag, true);
}
}

static void _fightMenuFightOutPokemonCloseStatusMenuSub(FightOutPokemon* p, u16 id, bool flag, bool wait)
{
    u8 menuId = fightMenuGetFightOutPokemonPtrToStatusMenuId(p, id, wait);
    if (menuIsCheck(menuId)) {
        fightMenuCloseCustomBody(menuId);
    }
}

extern "C" {
void fightMenuFightOutPokemonRenewStatusMenu(FightOutPokemon* p, u16 id, bool flag)
{
    extern void fightFloor_SetStatusMenuCnt(u32, s8);
    u32 menuId = fightMenuGetFightOutPokemonPtrToStatusMenuId(p, id, true);
    if (menuIsCheck(menuId)) {
        fightMenuFightOutPokemonOpenStatusMenu(p, id, flag);
        fightFloor_SetStatusMenuCnt(menuId, -1);
    }
}

void fightMenuFightStatusStartAnimHP(void* a, void* b)
{
    if (dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        menuFightStatusStartAnimHP(a, b);
    }
}

void fightMenuFightOutPokemonOpenStatusMenuStart(FightOutPokemon* p, u16 id, bool flag)
{
    _fightMenuFightOutPokemonOpenStatusMenuSub(p, id, flag, true, true);
}

void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon* p, u16 id, bool flag)
{
    _fightMenuFightOutPokemonOpenStatusMenuSub(p, id, flag, true, false);
}
}

static void _fightMenuFightOutPokemonOpenStatusMenuSub(FightOutPokemon* p, u16 id, bool flag, bool open, bool start)
{
    MenuPokemonStatusArg status;
    u8 menuId = fightMenuGetFightOutPokemonPtrToStatusMenuId(p, id, open);

    fightOutPokemonToMenuPokemonStatus(p, &status);
    if (!flag) {
        ((u8*)&status)[0x29] = 0;
    }
    if (start) {
        ((u8*)&status)[0x2D] = 1;
    } else {
        ((u8*)&status)[0x2D] = 0;
    }
    if (dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        menuOpenCustom(menuId, -1, 0, 0, 0, 1, status);
        fightFloor_SetStatusMenuCnt(menuId, -1);
    }
}

extern "C" {
void fightMenuFightOutPokemonSetStatusMenuActiveFlag(FightOutPokemon* p, u16 id, s32 active)
{
    if (fightFloorIsNowEncountTuusinTaisen(0) != 1) {
        menuFightStatusSetActive(fightMenuGetFightOutPokemonPtrToStatusMenuId(p, id, true), active);
    }
}

u32 fightMenuGetFightOutPokemonPtrToStatusMenuId(FightOutPokemon* p, u16 id, bool flag)
{
    void* side;
    u16 sideId;
    u16 rel;
    s32 buff;

    side = fightTargetGetPtr(2, p, id);
    if (side == 0) {
        return 0;
    }
    sideId = fightSideGetStatus(side, 0, 5, 0);
    rel = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(p, id);
    if (rel == 0) {
        return 0;
    }
    buff = fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(rel));
    if (buff < 0) {
        return 0;
    }
    return fightSideGetStatus(0, sideId, 3, buff);
}

void fightMenuFightTrainerCloseStatusMenu(FIGHT_TRAINER* p, u16 id, s32 wait)
{
    extern void menuCloseCustom(u32, s32, s32);
    u32 menuId = fightMenuGetFightTrainerPtrToStatusMenuId(p, id);
    if (menuIsCheck(menuId)) {
        menuCloseCustom(menuId, 0, wait);
    }
}

void fightMenuFightTrainerRenewStatusMenu(FIGHT_TRAINER* p, u16 id)
{
    if (menuIsCheck(fightMenuGetFightTrainerPtrToStatusMenuId(p, id))) {
        fightMenuFightTrainerOpenStatusMenu(p, id);
    }
}

void fightMenuFightTrainerOpenStatusMenu(FIGHT_TRAINER* p, u16 id)
{    MenuBallStatusArg status;
    u8 menuId = fightMenuGetFightTrainerPtrToStatusMenuId(p, id);

    fightTrainerToMenuBallStatus(p, &status);
    if (dbgMenuFightGetFightPokeStMenuOpenFlag() == 1 && menuFightChkOpenBall(menuId)) {
        menuOpenCustom(menuId, 0, 0, 0, 0, 1, (MenuBallStatusArg)(status));
    }
}

u32 fightMenuGetFightTrainerPtrToStatusMenuId(FIGHT_TRAINER* p, u16 id)
{
    void* side;
    u16 sideId;
    u16 rel;
    s32 buff;

    side = fightTargetGetPtr(2, p, id);
    if (side == 0) {
        return 0;
    }
    sideId = fightSideGetStatus(side, 0, 5, 0);
    rel = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightOutPokemon*)p, id);
    if (rel == 0) {
        return 0;
    }
    buff = fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(rel));
    if (buff < 0) {
        return 0;
    }
    return fightSideGetStatus(0, sideId, 2, buff);
}

u8 fightMenuGetFightTrainerPtrToKeyWaitMenuId(FIGHT_TRAINER* p, u16 id)
{
    return menuFightGetKeyWaitMenuId();
}
}
