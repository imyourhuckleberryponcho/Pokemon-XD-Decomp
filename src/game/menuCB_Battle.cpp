#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/menuCBWork.h>

#pragma peephole off

struct Hero {
    u8 data[0x978];
};

extern "C" {
extern _MENUCBWORK _CB;

void GSflagOff(s32);
s32 soundGetBGMID(void);
void soundStop(s32, s32);
void menuTitleBattleSelectFree(void);
void menuTitleReadWazaSelectMenu(void);
void menuCB_SetToolBattleModeFlag(s32);
s32 fightEncount(s32);
s32 HSD_Rand(void);
void* fightEncountDataBiosGetPtr(s32);
void fightEncountDataBiosSetBgmSndId(void*, u32);
void fightEncountDataBiosSetFightFloorDataId(void*, u32);
void fightEncountDataBiosSetFightKind(void*, u32);
void fightEncountDataBiosSetSyoukaiWzxDataId(void*, u32);
void fightEncountDataBiosSetFightType(void*, u32);
void fightEncountDataBiosSetFightTrainerDataId(void*, s32, u16);
void fightEncountDataBiosSetGSInputDevice(void*, s32, s32);
void menuCBBios_InitTrainerFromDataID(MenuCBTrainer*, u16, s32);
void menuCBBios_InitTrainerFromHero(MenuCBTrainer*, Hero*, u16);
void menuCBBios_CopyTrainer(MenuCBTrainer*, MenuCBTrainer*);
void menuCBTrainerBios_SetControlerID(MenuCBTrainer*, s32);
void menuCBTrainerBios_SetHomePlace(MenuCBTrainer*, s32);
s32 menuCBBios_PortIDtoControlerID(s32);
void fightTrainerCreateFightTrainerDataIdToHero(u16, s32, Hero*, s32);
void heroBiosSetNamePtr(Hero*, u16*);
u16* GSmsgGetGSchar(u32);
}

static void _menuCBBattle_DeleteAllItem(Hero* hero);

static const u16 VS_TRAINER_RANK_NUMBER[40] = {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
};
static const s8 VS_TRAINER_RANK_SELECT_TBL[4][2][3] = {
    {{5, 30, 35}, {5, 30, 30}},
    {{5, 20, 25}, {5, 20, 20}},
    {{5, 10, 15}, {5, 10, 10}},
    {{5, 0, 5}, {5, 0, 0}},
};
static const u16 VS_TRAINER_RANK_ENCOUNT_DATA[40] = {
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
    35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
};
static const u32 staBGM_imasugu[3] = {0x4F2, 0x4F2, 0x4F2};
static const u32 staBGM_tunaide[3] = {0x4F3, 0x4F3, 0x4F3};
static const u16 staColosseum[6] = {0x24, 0x26, 0x25, 0x3C, 0x3D, 0x3E};
static const u16 staColosseum_imasugu[6] = {0x24, 0x26, 0x25, 0x3C, 0x3D, 0x3E};

extern "C" {

PCRET(u16) menuCB_Battle(_MENUCBWORK* work) {
    s32 id;
    u16 result;
    if (_CB.mode == 1) {
        id = VS_TRAINER_RANK_ENCOUNT_DATA[work->trainer[1].rank];
    } else {
        switch (work->state) {
        case 0:
            id = 5;
            break;
        case 1:
            id = 7;
            break;
        case 2:
            id = 8;
            break;
        }
    }
    GSflagOff(0x323);
    soundStop(soundGetBGMID(), 0);
    menuTitleBattleSelectFree();
    menuCB_SetToolBattleModeFlag(1);
    result = fightEncount(id);
    menuCB_SetToolBattleModeFlag(0);
    menuTitleReadWazaSelectMenu();
    return result;
}

s32 menuCB_InitBattle(_MENUCBWORK* work) {
    void* encounter;
    s32 encId = 0;
    u16 count;
    int baseA;
    u16 baseB;
    u32 bgm;
    u32 floorId;
    Hero hero;

    if (_CB.nameIndex == -1) {
        count = VS_TRAINER_RANK_SELECT_TBL[work->row][work->col][0];
        baseA = VS_TRAINER_RANK_SELECT_TBL[work->row][work->col][1];
        baseB = VS_TRAINER_RANK_SELECT_TBL[work->row][work->col][2];
        if (work->col == 0) {
            work->trainer[0].rank = baseA + (u16)HSD_Rand() % count;
            work->trainer[1].rank = baseB + (u16)HSD_Rand() % count;
        } else {
            u16 b = baseB;
            work->trainer[0].rank = baseA + (u16)HSD_Rand() % count;
            do {
                work->trainer[1].rank = b + (u16)HSD_Rand() % count;
            } while (work->trainer[0].rank == work->trainer[1].rank);
            if ((u16)HSD_Rand() & 0x80) {
                work->trainer[0].rank += 5;
                work->trainer[1].rank += 5;
            }
        }
    }
    if (_CB.mode == 1) {
        encId = VS_TRAINER_RANK_ENCOUNT_DATA[work->trainer[1].rank];
    } else {
        switch (work->state) {
        case 0:
            encId = 5;
            break;
        case 1:
            encId = 7;
            break;
        case 2:
            encId = 8;
            break;
        }
    }
    encounter = fightEncountDataBiosGetPtr(encId);
    work->bgmCounter++;
    if (_CB.mode == 1) {
        work->bgmCounter = work->bgmCounter % 3;
        bgm = staBGM_imasugu[work->bgmCounter];
        if (work->row == 0) {
            bgm = 0x5CD;
        }
    } else {
        work->bgmCounter = work->bgmCounter % 3;
        bgm = staBGM_tunaide[work->bgmCounter];
    }
    fightEncountDataBiosSetBgmSndId(encounter, bgm);
    if (_CB.mode != 1) {
        if (_CB.floorSelect == 6) {
            work->selection = (u16)HSD_Rand() % 6;
        }
        floorId = staColosseum[work->selection];
    } else {
        work->selection = (u16)HSD_Rand() % 6;
        floorId = staColosseum_imasugu[work->selection];
    }
    fightEncountDataBiosSetFightFloorDataId(encounter, floorId);
    switch (work->mode) {
    case 0:
        fightEncountDataBiosSetFightKind(encounter, 0xB);
        fightEncountDataBiosSetSyoukaiWzxDataId(encounter, 0);
        break;
    case 1:
    default:
        if (work->col == 0) {
            fightEncountDataBiosSetFightKind(encounter, 0x11);
        } else {
            fightEncountDataBiosSetFightKind(encounter, 0xA);
        }
        fightEncountDataBiosSetSyoukaiWzxDataId(encounter, 0);
        break;
    }
    switch (work->mode) {
    case 0:
        switch (work->state) {
        case 1:
            fightEncountDataBiosSetFightType(encounter, 0x18);
            break;
        case 2:
            fightEncountDataBiosSetFightType(encounter, 0x24);
            break;
        case 0:
        default:
            fightEncountDataBiosSetFightType(encounter, 0x17);
            break;
        }
        break;
    case 1:
    default:
        fightEncountDataBiosSetFightType(encounter, 0x10);
        break;
    }
    switch (work->mode) {
    case 1: {
        u16 rankB = work->trainer[1].rank;
        u16 rankA = work->trainer[0].rank;
        u32 idA = VS_TRAINER_RANK_NUMBER[rankA];
        u32 idB = VS_TRAINER_RANK_NUMBER[rankB];
        menuCBBios_InitTrainerFromDataID(&work->trainer[1], idB, encId);
        work->trainer[1].dataId = idB;
        work->trainer[1].rank = rankB;
        menuCBTrainerBios_SetControlerID(&work->trainer[1], _CB.controlerId);
        _menuCBBattle_DeleteAllItem((Hero*)work->trainer[1].entryHero);
        _menuCBBattle_DeleteAllItem((Hero*)work->trainer[1].hero);
        if (_CB.nameIndex == -1) {
            static const u16 staDefaultNameID[3] = {0x3B20, 0x3B21, 0x3B22};
            u16* src;
            u16* dst;
            _CB.nameIndex = (u32)(u16)HSD_Rand() % 3;
            src = GSmsgGetGSchar(staDefaultNameID[_CB.nameIndex]);
            dst = _CB.name;
            while (*src != 0) {
                *dst = *src;
                src++;
                dst++;
            }
            *dst = 0;
        }
        fightTrainerCreateFightTrainerDataIdToHero(idA, menuCBBios_PortIDtoControlerID(0), &hero, encId);
        if (_CB.controlerId == 0) {
            heroBiosSetNamePtr(&hero, _CB.name);
        }
        _menuCBBattle_DeleteAllItem(&hero);
        {
            u16 rank = work->trainer[0].rank;
            menuCBBios_InitTrainerFromHero(&work->trainer[0], &hero, 0x1388);
            work->trainer[0].rank = rank;
        }
        if (_CB.controlerId != 0) {
            work->trainer[0].dataId = idA;
        }
        menuCBTrainerBios_SetControlerID(&work->trainer[0], menuCBBios_PortIDtoControlerID(0));
        menuCBTrainerBios_SetHomePlace(&work->trainer[0], 0);
        break;
    }
    case 0:
        switch (work->state) {
        case 0:
        case 1:
            work->trainerOrg[0].versusId = 0;
            work->trainerOrg[1].versusId = 1;
            work->trainerOrg[2].versusId = 2;
            work->trainerOrg[3].versusId = 3;
            menuCBBios_CopyTrainer(&work->trainer[0], &work->trainerOrg[0]);
            menuCBBios_CopyTrainer(&work->trainer[1], &work->trainerOrg[1]);
            break;
        case 2:
            menuCBBios_CopyTrainer(&work->trainer[0], &work->trainerOrg[work->trainerOrg[0].versusId]);
            menuCBBios_CopyTrainer(&work->trainer[1], &work->trainerOrg[work->trainerOrg[1].versusId]);
            menuCBBios_CopyTrainer(&work->trainer[2], &work->trainerOrg[work->trainerOrg[2].versusId]);
            menuCBBios_CopyTrainer(&work->trainer[3], &work->trainerOrg[work->trainerOrg[3].versusId]);
            break;
        }
        break;
    }
    switch (work->state) {
    case 2:
        fightEncountDataBiosSetFightTrainerDataId(encounter, 2, work->trainer[2].dataId);
        fightEncountDataBiosSetFightTrainerDataId(encounter, 3, work->trainer[3].dataId);
        fightEncountDataBiosSetGSInputDevice(encounter, 2, work->trainer[2].controllerId);
        fightEncountDataBiosSetGSInputDevice(encounter, 3, work->trainer[3].controllerId);
    case 0:
    case 1:
        fightEncountDataBiosSetFightTrainerDataId(encounter, 0, work->trainer[0].dataId);
        fightEncountDataBiosSetFightTrainerDataId(encounter, 1, work->trainer[1].dataId);
        fightEncountDataBiosSetGSInputDevice(encounter, 0, work->trainer[0].controllerId);
        fightEncountDataBiosSetGSInputDevice(encounter, 1, work->trainer[1].controllerId);
        break;
    }
    return 0;
}

}

static void _menuCBBattle_DeleteAllItem(Hero* hero) {
}

#ifndef __MWERKS__
#include <game/portxd_vs.h>
extern "C" void menuCBBios_CurrentlyWorkingToolBattleSet(s8 v);
extern "C" u8 menuCBBios_CurrentlyWorkingToolBattle(void);
extern "C" s32 PortXD_StartVsBattle(const PortXD_VsSetup* s)
{
    s32 id;
    s32 i;
    s32 n;
    s32 result;
    u8 working;
    void* encounter;

    if (s == 0) {
        return 0;
    }
    n = s->trainerCount == 4 ? 4 : 2;
    id = s->encountId;
    if (id == 0) {
        id = (n == 4) ? 8 : 5;
    }
    encounter = fightEncountDataBiosGetPtr(id);
    if (encounter == 0) {
        return 0;
    }
    _CB.mode = (s->fightKind == 0xB) ? 0 : 1;
    _CB.state = s->state;
    for (i = 0; i < n; i++) {
        if (s->hero[i] != 0) {
            menuCBBios_InitTrainerFromHero(&_CB.trainer[i], (Hero*)s->hero[i], s->dataId[i]);
        }
        menuCBTrainerBios_SetControlerID(&_CB.trainer[i], s->controller[i]);
        fightEncountDataBiosSetFightTrainerDataId(encounter, i, s->dataId[i]);
        fightEncountDataBiosSetGSInputDevice(encounter, i, s->controller[i]);
    }
    if (s->bgm != 0) {
        fightEncountDataBiosSetBgmSndId(encounter, s->bgm);
    }
    fightEncountDataBiosSetFightFloorDataId(encounter, s->floorId);
    fightEncountDataBiosSetFightKind(encounter, s->fightKind);
    fightEncountDataBiosSetSyoukaiWzxDataId(encounter, 0);
    fightEncountDataBiosSetFightType(encounter, s->fightType);

    working = menuCBBios_CurrentlyWorkingToolBattle();
    menuCBBios_CurrentlyWorkingToolBattleSet(1);
    GSflagOff(0x323);
    soundStop(soundGetBGMID(), 0);
    if (s->freeTitle) {
        menuTitleBattleSelectFree();
    }
    menuCB_SetToolBattleModeFlag(1);
    _CB.battleActive = 1;
    result = fightEncount(id);
    _CB.battleActive = 0;
    menuCB_SetToolBattleModeFlag(0);
    if (s->freeTitle) {
        menuTitleReadWazaSelectMenu();
    }
    menuCBBios_CurrentlyWorkingToolBattleSet((s8)working);
    return result;
}
#endif
