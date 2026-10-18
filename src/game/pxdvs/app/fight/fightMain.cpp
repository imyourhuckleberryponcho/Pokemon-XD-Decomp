#include <dolphin/types.h>

class FightEncountData;
class FIGHT_FLOOR;
class FIGHT_SIDE;
class FIGHT_TRAINER;
class FightOutPokemon;
class Sequence;

struct FightActionWork {
    u8 raw[0x30];
};

extern "C" {

s32 wazaSequenceSysGetWazaGroupID(u32 id, u32 arg);
u8 GSfsysPreReadKeepCache(void);
s32 GSfsysGetStatus(s32 id);
void GSthreadSwitch(void);
u16 fightGetFightEncountDataId(void);
u32 fightEncountGetEnvSndDataId(u16 id);
u32 fightEncountGetBgmSndDataId(u16 id);
void soundOpenPlayEnv(u32 snd, s32 id, s32 volume);
void soundOpenPlay(u32 snd, s32 b, s32 volume);
void soundStop(u32 snd, s32 id);
void soundOpenPlayFadeOutIn(s32 a, s32 b, s32 c, s32 d);

s32 fightFloor_GetFightType(FIGHT_FLOOR* floor);
u8 fightFloor_GetFightTypeTrainerNum(FIGHT_FLOOR* floor);
u8 fightFloor_GetFightTypeFightoutPokemonNum(FIGHT_FLOOR* floor);
FIGHT_SIDE* fightFloorGetValidFightSidePtr(FIGHT_FLOOR* floor, u16 sideId);
FIGHT_TRAINER* fightSideGetValidFightTrainerPtr(FIGHT_SIDE* side, u16 idx);
u32 fightTrainer_GetSequencePtr(FIGHT_TRAINER* t);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FIGHT_TRAINER* trainer, u16 index);
u32 fightOutPokemon_GetSequencePtr(FightOutPokemon* fop);
void Sequence_SetVisibility(u32 seq, s32 visible);
void battleGridStoreModelVisibilityFlags(void);
void battleGridUpdate(void);

u8 battleCameraIsSimple(void);
void battleCameraDoSimple(void);
void battleCameraDoFull(void);
void battleCameraStop(void);
void battleCameraDisable(void);
void battleCameraStartRandom(u8 simple);

u8 dbgMenuGetEnable(void);
void dbgMenuSetEnable(u8 enable);
u8 dbgMenuFightGetFightDebugMenuOpenFlag(void);
u8 dbgMenuFightGetFightPokeStMenuOpenFlag(void);
u32 dbgMenuFightGetMsgSpeedToFrame(u32 frames);
void dbgMenuMain(u8 mode);
void menuGetKeyInfo(u16* info, s32 port);
f32 GSgfxVideoGetLastRenderTime(void);

FightEncountData* fightEncountDataBiosGetPtr(u16 id);
u16 fightEncountDataBiosGetDiskId(FightEncountData* data);

u32 fightFloor_GetEnvSndId(FIGHT_FLOOR* floor);
u16 fightFloor_GetEncountDataId(FIGHT_FLOOR* floor);
u16 fightFloor_GetTurnCount(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountOpeningVirtualBattle(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountSnatchOnly(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountHostEnemyPokemonKime(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountHostPokemonKime(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountVirtualBattle(FIGHT_FLOOR* floor);
u8 fightFloorIsUseFightTimerAll(FIGHT_FLOOR* floor);
u8 fightFloorIsUseFightTimerCommand(FIGHT_FLOOR* floor);
void fightFloorSetTimeOutAllFightResult(FIGHT_FLOOR* floor);

void fightActionFlowKaisiPreSubLoad(void);
void fightActionCreateAndFlowFifo(void* work, u16 a, u16 b, u16 kind, u32 index, void* table);
void fightActionDispFifoAll(void);
extern u8 fight_action_data_kaisi[];
extern u8 fight_action_data_turn[];
extern u8 fight_action_data_syuuryou[];

void fadeSet(s32 type, f32 time);
void fadeCheck(s32 wait);
void fadeSetEX(u16 type, void (*init)(void), bool snapshot, f32 time, f32 hookDuration);
void fadeEffectHookFunction_virtual_end_Init(void);
void floorSetFadeScript(u32 out, u32 in);
u8 GSfloorPop(void);

void fightSeqEventKurein(s32 kind);
void fightSeqCheckZenmetu(void);
void fightEncountCheckZenmetu(void);
u16 fightGetFightResultId(void);
void fightSetFightResultId(u16 id);
void fightCloseAllMenu(void);
void fightMenuOpenInfoMenu(s8 flag);
void fightMenuCloseInfoMenu(u8 wait);
s32 menuFightChkSeq(void);
void menuFightOpenTimeup(void);
void fightTimerAllInit(void);
void fightTimerAllStart(void);
bool fightTimerAllIsOver(void);
bool fightTimerAllBlock(void);
void fightTimerAllTerminate(void);
void fightTimerCommandInit(void);
void fightTimerCommandStart(void);
bool fightTimerCommandBlock(void);
void fightTimerCommandTerminate(void);
s32 winMsgOpen(s8 type, void* msg, bool a, bool b);
void winMsgClose(bool flag);

void fightMainWaitFrame(u32 frames);
void fightMainWaitFrameEffect(u32 frames);
s32 fightRegWzxLoadGenric(u32 id);

}

u8 deckDataVirtualDB_GetTurnLimit(u16 id);
static void _fightMainWaitFrameSub(u32 frames);

static u16 _fight_reg_wzx_generic_data_id_ary[] = {
    0x0057, 0x0000, 0x009E, 0x0000, 0x0026, 0x0000, 0x0027, 0x0000, 0x0028, 0x0000, 0x0029, 0x0000, 0x002A, 0x0000,
    0x002B, 0x0000, 0x002C, 0x0000, 0x002D, 0x0000, 0x003C, 0x0000, 0x002E, 0x0003, 0x002F, 0x0003, 0x0030, 0x0003,
    0x0031, 0x0003, 0x0032, 0x0003, 0x0033, 0x0003, 0x0034, 0x0003, 0x0037, 0x0003, 0x0039, 0x0003, 0x0058, 0x0003,
};

static FightActionWork fight_action;

static u16 _fight_reg_wzx_generic_data_id_ary_num = 0x2A;

static u8 _fightSoundOpenPlayStart;
static u8 _fightSoundOpenPlayEnvStart;

extern "C" {

void fightRegWzxLoadAll(s8 group) {
    u16 i;
    for (i = 0; i < _fight_reg_wzx_generic_data_id_ary_num; i += 2) {
        if (group < 0 || group == _fight_reg_wzx_generic_data_id_ary[i + 1]) {
            fightRegWzxLoadGenric(_fight_reg_wzx_generic_data_id_ary[i]);
        }
    }
}

s32 fightRegWzxLoadGenric(u32 id) {
    s32 group = wazaSequenceSysGetWazaGroupID(id, 4);
    if (GSfsysPreReadKeepCache() == 0) {
        return 0;
    }
    while (1) {
        s32 st = GSfsysGetStatus(group);
        if (st == 0 || st < 0) {
            break;
        }
        GSthreadSwitch();
    }
    return 1;
}

void fightSoundOpenPlayEnv(u8 flag) {
    u16 id;
    if (_fightSoundOpenPlayEnvStart != 1 && flag != 0 && (id = fightGetFightEncountDataId()) != 0) {
        u32 snd = fightEncountGetEnvSndDataId(id);
        if (snd != 0) {
            soundOpenPlayEnv(snd, 0x3E8, 0xFF);
        }
        _fightSoundOpenPlayEnvStart = 1;
    }
}

void fightSoundOpenPlay(u8 flag) {
    u16 id;
    if (_fightSoundOpenPlayStart != 1 && flag != 0 && (id = fightGetFightEncountDataId()) != 0) {
        u32 snd = fightEncountGetBgmSndDataId(id);
        if (snd != 0) {
            soundOpenPlay(snd, 0, 0xFF);
        }
        _fightSoundOpenPlayStart = 1;
    }
}

void fightSoundOpenPlayInit(void) {
    _fightSoundOpenPlayStart = 0;
    _fightSoundOpenPlayEnvStart = 0;
}

void fightMainSetAllDispFlag(s32 visible) {
    FIGHT_SIDE* s;
    u16 trainer;
    u16 poke;
    u16 side;
    u32 trainerNum;
    u32 pokeNum;
    FIGHT_TRAINER* t;
    fightFloor_GetFightType(0);
    trainerNum = fightFloor_GetFightTypeTrainerNum(0);
    pokeNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    for (side = 0; side < 2; side++) {
        s = fightFloorGetValidFightSidePtr(0, side);
        if (s != 0) {
            for (trainer = 0; trainer < trainerNum; trainer++) {
                t = fightSideGetValidFightTrainerPtr(s, trainer);
                if (t != 0) {
                    u32 seq = fightTrainer_GetSequencePtr(t);
                    if (seq != 0) {
                        Sequence_SetVisibility(seq, visible);
                        for (poke = 0; poke < pokeNum; poke++) {
                            FightOutPokemon* p = fightTrainerGetValidFightOutPokemonPtr(t, poke);
                            if (p != 0) {
                                u32 pseq = fightOutPokemon_GetSequencePtr(p);
                                if (pseq != 0) {
                                    Sequence_SetVisibility(pseq, visible);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    battleGridStoreModelVisibilityFlags();
}

u8 fightMainAllCamera(u8 simple, u8 stop) {
    u8 prev = battleCameraIsSimple();
    if (simple == 1) {
        battleCameraDoSimple();
    } else {
        battleCameraDoFull();
    }
    if (stop != 0) {
        battleCameraStop();
    }
    battleCameraStartRandom(1);
    return prev;
}

void fightMainDebugMenu(void) {
    u16 keys[16];
    u8 ticks;
    u8 enable = dbgMenuGetEnable();
    dbgMenuSetEnable(1);
    if (dbgMenuFightGetFightDebugMenuOpenFlag() == 1) {
        dbgMenuMain(1);
    } else {
        ticks = 0;
        while (ticks < 4) {
            menuGetKeyInfo(keys, 1);
            if (keys[0] & 0x800) {
                break;
            }
            GSthreadSwitch();
            ticks = (u8)((f32)ticks + GSgfxVideoGetLastRenderTime());
        }
        if (ticks < 4) {
            dbgMenuMain(1);
        }
    }
    dbgMenuSetEnable(enable);
}

void fightMain(void) {
    u16 diskId;
    s32 limit;
    diskId = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightGetFightEncountDataId()));
    u32 envSnd = fightFloor_GetEnvSndId(0);
    if (envSnd != 0) {
        soundOpenPlayEnv(envSnd, 0x3E8, 0xFF);
    }
    fightActionFlowKaisiPreSubLoad();
    if (fightFloorIsNowEncountOpeningVirtualBattle(0) == 0) {
        fadeSet(8, 1.0f);
    }
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 2, 0, fight_action_data_kaisi);
    if (fightFloorIsNowEncountOpeningVirtualBattle(0) == 0) {
        fadeCheck(1);
    }
    fightMainDebugMenu();
    if (fightGetFightResultId() == 0) {
        if (fightFloorIsNowEncountSnatchOnly(0) == 1) {
            fightSeqEventKurein(3);
            fightSeqEventKurein(4);
        }
        if (fightFloorIsNowEncountHostEnemyPokemonKime(0) == 0) {
            fightActionCreateAndFlowFifo(&fight_action, 0, 0, 4, 5, fight_action_data_kaisi);
        }
        if (fightFloorIsNowEncountHostPokemonKime(0) == 0) {
            fightActionCreateAndFlowFifo(&fight_action, 0, 0, 4, 4, fight_action_data_kaisi);
        }
        if (fightFloorIsNowEncountOpeningVirtualBattle(0) == 1) {
            fadeSet(2, 0.5f);
            fadeCheck(1);
            fightMainWaitFrame(0x64);
        }
        fightActionCreateAndFlowFifo(&fight_action, 0, 0, 5, 0, fight_action_data_kaisi);
        if (fightFloorIsNowEncountSnatchOnly(0) == 1) {
            fightSeqEventKurein(5);
        }
        fightActionDispFifoAll();
        if (fightFloorIsUseFightTimerAll(0) == 1) {
            fightTimerAllInit();
            fightTimerAllStart();
        }
        while (fightGetFightResultId() == 0) {
            fightMainDebugMenu();
            if (fightGetFightResultId() == 0) {
                if (fightFloorIsUseFightTimerAll(0) == 1 && fightTimerAllIsOver() == 1) {
                    menuFightOpenTimeup();
                    if (fightFloorIsNowEncountHostEnemyPokemonKime(0) == 0 &&
                        fightFloorIsNowEncountOpeningVirtualBattle(0) == 0) {
                        fightMainAllCamera(1, 0);
                    }
                    if (fightFloor_GetEncountDataId(0) != 0xD9) {
                        fightMenuOpenInfoMenu(0);
                    }
                    fightFloorSetTimeOutAllFightResult(0);
                    fightMainWaitFrame(0xB4);
                } else if (deckDataVirtualDB_GetTurnLimit(diskId) != 0 &&
                           ((limit = deckDataVirtualDB_GetTurnLimit(diskId)),
                            (s32)fightFloor_GetTurnCount(0) > limit)) {
                    fightMainAllCamera(1, 0);
                    fightMenuOpenInfoMenu(0);
                    fightSetFightResultId(7);
                    fightMainWaitFrame(0x64);
                } else {
                    if (fightFloorIsUseFightTimerCommand(0) == 1) {
                        fightTimerCommandInit();
                        fightTimerCommandStart();
                    }
                    battleGridUpdate();
                    fightMainAllCamera(0, 1);
                    if (fightFloor_GetEncountDataId(0) != 0xD9) {
                        fightMenuOpenInfoMenu(-1);
                    }
                    if (dbgMenuFightGetFightPokeStMenuOpenFlag() == 0) {
                        fightMainWaitFrame(0x258);
                    }
                    fightActionDispFifoAll();
                    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 7, 0, fight_action_data_turn);
                    while (1) {
                        if (menuFightChkSeq() == 0) {
                            break;
                        }
                        GSthreadSwitch();
                    }
                    GSthreadSwitch();
                    GSthreadSwitch();
                    fightActionDispFifoAll();
                    fightMenuCloseInfoMenu(0);
                    battleCameraDoSimple();
                    if (fightFloorIsUseFightTimerCommand(0) == 1) {
                        fightTimerCommandBlock();
                        fightTimerCommandTerminate();
                    }
                    fightSeqCheckZenmetu();
                    if (fightGetFightResultId() == 0) {
                        fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0xB, 0, fight_action_data_turn);
                        if (fightGetFightResultId() == 0) {
                            fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0xD, 0, fight_action_data_turn);
                        }
                    }
                }
            }
        }
        fightActionDispFifoAll();
    }
    fightMainAllCamera(1, 0);
    fightCloseAllMenu();
    if (fightFloorIsUseFightTimerAll(0) == 1) {
        fightTimerAllBlock();
        fightTimerAllTerminate();
    }
    if (fightGetFightResultId() == 1) {
        winMsgOpen(2, (void*)0x5011, 1, 1);
        fightMainWaitFrame(0x64);
        winMsgClose(1);
    }
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0xE, 0, fight_action_data_syuuryou);
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0xF, fightGetFightResultId(), fight_action_data_syuuryou);
    fightActionDispFifoAll();
    u32 stopSnd = fightFloor_GetEnvSndId(0);
    if (stopSnd != 0) {
        soundStop(stopSnd, 0x3E8);
    }
    if (fightFloor_GetEnvSndId(0) == 0) {
        soundOpenPlayFadeOutIn(8, 0x3E8, 0x3E8, 0xFF);
    }
    battleCameraDisable();
    if (fightFloorIsNowEncountVirtualBattle(0) == 1 || fightFloorIsNowEncountOpeningVirtualBattle(0) == 1) {
        fadeSetEX(0x18, fadeEffectHookFunction_virtual_end_Init, 1, 2.5f, 2.5f);
    } else {
        fadeSet(3, 1.0f);
    }
    fadeCheck(1);
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0x10, 0, fight_action_data_syuuryou);
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0x11, 0, fight_action_data_syuuryou);
    fightEncountCheckZenmetu();
    GSfloorPop();
    floorSetFadeScript(0, 0);
}

void fightMainWaitFrameEffect(u32 frames) {
    _fightMainWaitFrameSub(frames);
}

void fightMainWaitFrame(u32 frames) {
    _fightMainWaitFrameSub(dbgMenuFightGetMsgSpeedToFrame(frames));
}

}

static void _fightMainWaitFrameSub(u32 frames) {
    if (frames != 0) {
        u32 t = 0;
        while (t < frames) {
            GSthreadSwitch();
            t = (u32)((f32)t + GSgfxVideoGetLastRenderTime());
        }
    }
}
