#include <dolphin/types.h>
#include <game/fightfloor.h>
#include <game/pxdvs/app/fight/fightData.h>

#include <game/pxdvs/app/fight/fightSideData.h>

extern "C" {

extern u32* fight_side_data_number;
extern FightSideData* fight_side_data;

void fightSideDataBiosSetFightoutPokemonStatusMenuDataId(FightSideData* data, u8 index, u32 id) {
    if (data != NULL && index < 2) {
        data->fightoutPokemonStatusMenuDataId[index] = id;
    }
}

void fightSideDataBiosSetFightTrainerStatusMenuDataId(FightSideData* data, u8 index, u32 id) {
    if (data != NULL && index < 2) {
        data->fightTrainerStatusMenuDataId[index] = id;
    }
}

void fightSideDataBiosSetYrot(FightSideData* data, u16 yrot) {
    if (data != NULL) {
        data->yrot = yrot;
    }
}

u32 fightSideDataBiosGetFightoutPokemonStatusMenuDataId(FightSideData* data, u8 index) {
    if (data == NULL) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return data->fightoutPokemonStatusMenuDataId[index];
}

u32 fightSideDataBiosGetFightTrainerStatusMenuDataId(FightSideData* data, u8 index) {
    if (data == NULL) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return data->fightTrainerStatusMenuDataId[index];
}

u16 fightSideDataBiosGetYrot(FightSideData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->yrot;
}

FightSideData* fightSideDataBiosGetPtr(u16 id) {
    if (id >= *fight_side_data_number) {
        return 0;
    }
    return &fight_side_data[id];
}

void fightSideBiosSetMakibisiCheckFlag(FIGHT_SIDE* side, u8 flag) {
    if (side != NULL) {
        side->makibisiCheckFlag = flag;
    }
}

void fightSideBiosSetFightSideDataId(FIGHT_SIDE* side, u16 id) {
    if (side != NULL) {
        side->fightSideDataId = id;
    }
}

u8 fightSideBiosGetMakibisiCheckFlag(FIGHT_SIDE* side) {
    if (side == NULL) {
        return 0;
    }
    return side->makibisiCheckFlag;
}

FIGHT_TRAINER* fightSideBiosGetFightTrainerPtr(FIGHT_SIDE* side, u16 index) {
    if (side == NULL) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return &side->fightTrainer[index];
}

FightJoutai* fightSideBiosGetJoutaiPtr(FIGHT_SIDE* side, u16 index) {
    if (side == NULL) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return &side->joutai[index];
}

u16 fightSideBiosGetFightSideDataId(FIGHT_SIDE* side) {
    if (side == NULL) {
        return 0;
    }
    return side->fightSideDataId;
}

}
