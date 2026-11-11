#include <dolphin/types.h>
#include <game/fightfloor.h>
#include <game/pxdvs/app/fight/fightData.h>

#include <game/pxdvs/app/fight/fightSideData.h>

extern "C" {

FightSideData* fightSideDataBiosGetPtr(u16 id);

void fightSide_SetMakibisiCheckFlag(FIGHT_SIDE* side, u8 flag) {
    if (side != NULL) {
        side->makibisiCheckFlag = flag;
    }
}

void fightSide_SetFightSideDataId(FIGHT_SIDE* side, u16 id) {
    if (side != NULL) {
        side->fightSideDataId = id;
    }
}

u8 fightSide_GetMakibisiCheckFlag(FIGHT_SIDE* side) {
    if (side == NULL) {
        return 0;
    }
    return side->makibisiCheckFlag;
}

FIGHT_TRAINER* fightSide_GetFightTrainerPtr(FIGHT_SIDE* side, u16 index) {
    if (side == NULL) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return &side->fightTrainer[index];
}

FightJoutai* fightSide_GetJoutaiPtr(FIGHT_SIDE* side, u16 index) {
    if (side == NULL) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return &side->joutai[index];
}

u16 fightSide_GetFightSideDataId(FIGHT_SIDE* side) {
    if (side == NULL) {
        return 0;
    }
    return side->fightSideDataId;
}

u16 fightSideDB_GetYrot(u16 id) {
    FightSideData* data = fightSideDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->yrot;
}

}
