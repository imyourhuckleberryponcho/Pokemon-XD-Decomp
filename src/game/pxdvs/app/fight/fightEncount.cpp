// Draft (first pass), not yet matching.
#include <dolphin/types.h>

#pragma dont_inline on

struct Pokemon {
    u8 getLevel() const;
};
class Hero {
public:
    static Hero* getHeroPtr();
    u32 getBattleResumeFloorID() const;
    u32 getBattleResumeFloorIndex() const;
};
struct FIGHT_FLOOR;
struct FightEncountData;
struct FightEncountWipeData;
struct FightTrainerKindData;

class FIGHT_ENCOUNT {
public:
    void setDirtyFlag(bool);
    u8 getDirtyFlag() const;
    void setRoundNo(u32);
    u32 getRoundNo() const;
    void setDestroyFlag(u8);
    u8 getDestroyFlag() const;
    void setTrainerKind(u8);
    u8 getTrainerKind() const;
    void setFightMode(u8);
    u8 getFightMode() const;
    void setSwapDeckNO(u16);
    u16 getSwapDeckNO() const;
    void setSwapMode(u8);
    u8 getSwapMode() const;
    void setAddID(u8);
    u8 getAddID() const;
    void setAddPlace(u8);
    u8 getAddPlace() const;
    void setAddMode(u8);
    u8 getAddMode() const;
    void setMsg(u8, u16);
    u16 getMsg(u8) const;
    void setField(u16);
    u16 getField() const;
    void clear();

    u16 field;      // 0x0
    u16 msg[4];     // 0x2
    u8 addMode;     // 0xA
    u8 addPlace;    // 0xB
    u8 addID;       // 0xC
    u8 swapMode;    // 0xD
    u16 swapDeckNO; // 0xE
    u8 fightMode;   // 0x10
    u8 trainerKind; // 0x11
    u8 destroyFlag; // 0x12
    u32 roundNo;    // 0x14
    u8 dirtyFlag;   // 0x18
};

extern s8 underTakerDeckRand;

extern "C" {
u32 heroGetStatus(Hero* hero, u32 selector, u16 index);
void heroDecPokedoru(Hero* hero, u32 offset);
void recoveryPokemon(void);
u16 fightGetFightEncountDataId(void);
FightEncountData* fightEncountDataBiosGetPtr(u16 id);
u8 fightEncountDataBiosGetZenmetuFlag(FightEncountData* data);
u8 fightEncountDataBiosGetFightKind(FightEncountData* data);
u16 fightEncountDataBiosGetFightFloorDataId(FightEncountData* data);
u32 fightEncountDataBiosGetBgmSndId(FightEncountData* data);
u16 fightEncountDataBiosGetDiskId(FightEncountData* data);
u32 fightEncountDataBiosGetWipeId(FightEncountData* data);
u16 fightEncountDataBiosGetFightTrainerDataId(FightEncountData* data, u8 index);
u8 fightEncountDataBiosGetWipeSnapshotUse(FightEncountWipeData* data);
void* fightEncountDataBiosGetWipeFunction(FightEncountWipeData* data);
f32 fightEncountDataBiosGetWipeEffectTime(FightEncountWipeData* data);
u16 fightEncountDataBiosGetWipeEffectSndID(FightEncountWipeData* data);
FightEncountWipeData* fightEncountWipeDataBiosGetPtr(u32 id);
u8 fightFloorIsGcHeroWin(FIGHT_FLOOR* floor, u16 result);
u16 fightGetFightResultId(void);
void fightSetFightResultId(u16);
void fightSetFightEncountDataId(u16);
void fightReadDeck(u16);
void fightFreeDeck(u16);
void fightDataRewrite(void);
void fightFloor_SetEncountFloorId(FIGHT_FLOOR* floor, u32 value);
u16 fightFloorDB_GetFloorDataId(u16 id);
u32 fightFloorDB_GetEnvSndId(u16 id);
u32 fightFloorDB_GetBgmSndId(u16 id);
u8 fightTrainerDB_GetKindDataId(u16 id);
FightTrainerKindData* fightTrainerKindDataBiosGetPtr(u16 id);
u32 fightTrainerKindDataBiosGetBgmSndId(FightTrainerKindData* data);
u32 fightFloorSetStatus(FIGHT_FLOOR* floor, u16 dataId, u16 status, u16 arg, u32 value);
void fightTrainerSetNameHearFlag(u16 encountId);
void fightSoundOpenPlayInit(void);
void GSfsysFree(u32 id);
void GSflagOff(u32 id);
void GSflagOn(u32 id);
bool GSflagTest(u32 id);
s32 GSfloorGetCurrent(void);
u8 GSfloorPush(u32 id);
u8 GSsndPlay(u32 id, s32 time, u32 flag);
void peopleAllBlockMoveScript(void);
void floorSetFloorChangeInfo(u32 floorID, u32 posIndex);
u8 floorPopAndChange(u32 id);
void floorSetFadeScript(u32 out, u32 in);
void floorWaitForChange(void);
void floorSetPrevFloorID(u32 id);
void floorLinkWithSE(u32 floorID, u32 posIndex, u32 se);
void floorExecSoundScript();
void floorClearReturnPoint();
void mailMainReceiveTerminate(void);
u32 soundGetBGMID(void);
u32 soundGetEnvID(void);
void soundOpenPlay(s32, s32, s32);
void soundOpenPlayEnv(u16 id, s32, s32 volume);
void soundStopEnv(s32);
void fadeSet(s32 type, f32 time);
void fadeSetEX(u16 type, void (*init)(void), bool snapshot, f32 time, f32 hookDuration);
void fadeCheck(s32);
}

extern "C" FIGHT_ENCOUNT* fightEncountGetStrObj(void);
extern "C" u32 fightEncountGetBgmSndDataId(u16 id);

static FIGHT_ENCOUNT _fightEncount;

extern "C" {

void fightEncountAnnihilationRecovery(void) {
    u16 i;
    u8 maxLevel = 0;
    for (i = 0; i < 6; i++) {
        u8 lv = ((Pokemon*)heroGetStatus(0, 3, i))->getLevel();
        if (maxLevel < lv) {
            maxLevel = lv;
        }
    }
    heroDecPokedoru(0, (u8)maxLevel << 4);
    recoveryPokemon();
}

FIGHT_ENCOUNT* fightEncountGetStrObj(void) {
    return &_fightEncount;
}

u8 fightEncountCheckZenmetu(void) {
    FightEncountData* data = fightEncountDataBiosGetPtr(fightGetFightEncountDataId());
    Hero* hero = Hero::getHeroPtr();
    if (hero->getBattleResumeFloorID() == 0) {
        return 0;
    }
    if (fightEncountDataBiosGetZenmetuFlag(data) == 0) {
        return 0;
    }
    if (fightFloorIsGcHeroWin(0, fightGetFightResultId()) == 1) {
        return 0;
    }
    GSfsysFree(0x842);
    FIGHT_ENCOUNT* enc = fightEncountGetStrObj();
    enc->clear();
    enc->setDirtyFlag(true);
    GSflagOff(0x323);
    fightEncountAnnihilationRecovery();
    peopleAllBlockMoveScript();
    u8 index = hero->getBattleResumeFloorIndex();
    floorSetFloorChangeInfo(hero->getBattleResumeFloorID(), index);
    floorPopAndChange(hero->getBattleResumeFloorID());
    floorSetFadeScript(0, 0x5960008);
    floorWaitForChange();
    return 1;
}

u32 fightEncount(u16 id) {
    FIGHT_ENCOUNT* enc = fightEncountGetStrObj();
    FightEncountData* data;
    u8 i;
    void* fn;
    u16 floorId;
    u32 env;
    u32 bgm;
    u8 kind;
    s32 cur;
    FightEncountWipeData* wipe;
    u8 snapshot;
    u32 snd;
    u16 sndId;
    Hero* hero;
    u8 index;

    enc->getField();
    enc->getFightMode();
    enc->getDestroyFlag();
    for (i = 0; i < 4; i++) {
        enc->getMsg(i);
    }
    if (id == 0) {
        return 0;
    }
    fightReadDeck(id);
    data = fightEncountDataBiosGetPtr(id);
    kind = fightEncountDataBiosGetFightKind(data);
    fightSetFightResultId(0);
    GSflagOff(0x30E);
    fightSetFightEncountDataId(id);
    underTakerDeckRand = -1;
    fightDataRewrite();
    cur = GSfloorGetCurrent();
    fightFloor_SetEncountFloorId(0, cur);
    floorId = fightFloorDB_GetFloorDataId(fightEncountDataBiosGetFightFloorDataId(data));
    mailMainReceiveTerminate();
    fightTrainerSetNameHearFlag(id);
    bgm = soundGetBGMID();
    env = soundGetEnvID();
    soundOpenPlay(8, 1000, 0xFF);
    soundStopEnv(1000);
    if (kind == 15 && fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(id)) == 0) {
        fadeSet(3, 0.5f);
        snd = fightEncountGetBgmSndDataId(id);
        if (snd != 0) {
            soundOpenPlay(snd, 0, 0xFF);
        }
    } else {
        wipe = fightEncountWipeDataBiosGetPtr(fightEncountDataBiosGetWipeId(data));
        snapshot = fightEncountDataBiosGetWipeSnapshotUse(wipe);
        fn = fightEncountDataBiosGetWipeFunction(wipe);
        fadeSetEX(9, (void (*)(void))fn, snapshot, 1.0f, fightEncountDataBiosGetWipeEffectTime(wipe));
        sndId = fightEncountDataBiosGetWipeEffectSndID(wipe);
        if (sndId != 0) {
            GSsndPlay(sndId, 0, 0);
        }
    }
    fightSoundOpenPlayInit();
    fightFreeDeck(id);
    GSfloorPush(floorId);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    floorSetPrevFloorID(floorId);
    GSfsysFree(0x842);
    enc->clear();
    enc->setDirtyFlag(true);
    if (fightEncountDataBiosGetZenmetuFlag(data) != 0 && fightFloorIsGcHeroWin(0, fightGetFightResultId()) == 0) {
        fightSetFightEncountDataId(0);
        GSflagOff(0x323);
        fightEncountAnnihilationRecovery();
        peopleAllBlockMoveScript();
        hero = Hero::getHeroPtr();
        index = hero->getBattleResumeFloorIndex();
        floorLinkWithSE(hero->getBattleResumeFloorID(), index, 0);
        floorSetFadeScript(0, 0x5960008);
        floorWaitForChange();
        fightFloorSetStatus(0, 0, 13, 0, 0);
        return fightGetFightResultId();
    }
    soundOpenPlay(bgm, 1000, 0x7F);
    soundOpenPlayEnv(env, 1000, 0x7F);
    GSflagOn(0x30E);
    floorExecSoundScript();
    floorClearReturnPoint();
    if (!GSflagTest(0x323)) {
        fadeSet(2, 0.5f);
        fadeCheck(1);
    }
    fightFloorSetStatus(0, 0, 13, 0, 0);
    return fightGetFightResultId();
}

u32 fightEncountGetEnvSndDataId(u16 id) {
    return fightFloorDB_GetEnvSndId(fightEncountDataBiosGetFightFloorDataId(fightEncountDataBiosGetPtr(id)));
}

u32 fightEncountGetBgmSndDataId(u16 id) {
    FightEncountData* data = fightEncountDataBiosGetPtr(id);
    u32 snd = fightEncountDataBiosGetBgmSndId(data);
    if (snd != 0) {
        return snd;
    }
    snd = fightFloorDB_GetBgmSndId(fightEncountDataBiosGetFightFloorDataId(fightEncountDataBiosGetPtr(id)));
    if (snd != 0) {
        return snd;
    }
    u16 i;
    for (i = 0; i < 4; i++) {
        u16 tid = fightEncountDataBiosGetFightTrainerDataId(data, i);
        if (tid != 0) {
            u8 k = fightTrainerDB_GetKindDataId(tid);
            if (k != 0) {
                snd = fightTrainerKindDataBiosGetBgmSndId(fightTrainerKindDataBiosGetPtr(k));
                if (snd != 0) {
                    return snd;
                }
            }
        }
    }
    return 8;
}

}

void FIGHT_ENCOUNT::setDirtyFlag(bool v) { if (this != 0) dirtyFlag = v; }
u8 FIGHT_ENCOUNT::getDirtyFlag() const { if (this == 0) return 0; return dirtyFlag; }
void FIGHT_ENCOUNT::setRoundNo(u32 v) { if (this != 0) roundNo = v; }
u32 FIGHT_ENCOUNT::getRoundNo() const { if (this == 0) return 0; return roundNo; }
void FIGHT_ENCOUNT::setDestroyFlag(u8 v) { if (this != 0) destroyFlag = v; }
u8 FIGHT_ENCOUNT::getDestroyFlag() const { if (this == 0) return 0; return destroyFlag; }
void FIGHT_ENCOUNT::setTrainerKind(u8 v) { if (this != 0) trainerKind = v; }
u8 FIGHT_ENCOUNT::getTrainerKind() const { if (this == 0) return 0; return trainerKind; }
void FIGHT_ENCOUNT::setFightMode(u8 v) { if (this != 0) fightMode = v; }
u8 FIGHT_ENCOUNT::getFightMode() const { if (this == 0) return 0; return fightMode; }
void FIGHT_ENCOUNT::setSwapDeckNO(u16 v) { if (this != 0) swapDeckNO = v; }
u16 FIGHT_ENCOUNT::getSwapDeckNO() const { if (this == 0) return 0; return swapDeckNO; }
void FIGHT_ENCOUNT::setSwapMode(u8 v) { if (this != 0) swapMode = v; }
u8 FIGHT_ENCOUNT::getSwapMode() const { if (this == 0) return 0; return swapMode; }
void FIGHT_ENCOUNT::setAddID(u8 v) { if (this != 0) addID = v; }
u8 FIGHT_ENCOUNT::getAddID() const { if (this == 0) return 0; return addID; }
void FIGHT_ENCOUNT::setAddPlace(u8 v) { if (this != 0) addPlace = v; }
u8 FIGHT_ENCOUNT::getAddPlace() const { if (this == 0) return 0; return addPlace; }
void FIGHT_ENCOUNT::setAddMode(u8 v) { if (this != 0) addMode = v; }
u8 FIGHT_ENCOUNT::getAddMode() const { if (this == 0) return 0; return addMode; }
void FIGHT_ENCOUNT::setMsg(u8 i, u16 v) { if (this != 0) msg[i] = v; }
u16 FIGHT_ENCOUNT::getMsg(u8 i) const { if (this == 0) return 0; return msg[i]; }
void FIGHT_ENCOUNT::setField(u16 v) { if (this != 0) field = v; }
u16 FIGHT_ENCOUNT::getField() const { if (this == 0) return 0; return field; }

void FIGHT_ENCOUNT::clear() {
    u8 i;
    field = 0;
    addMode = 0;
    addPlace = 0;
    addID = 0;
    swapMode = 0;
    swapDeckNO = 0;
    fightMode = 0;
    trainerKind = 0;
    for (i = 0; i < 4; i++) {
        msg[i] = 0;
    }
    destroyFlag = 0;
    roundNo = 0;
    dirtyFlag = 0;
}
