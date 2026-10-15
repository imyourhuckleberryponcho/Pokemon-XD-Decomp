#include <dolphin/types.h>

struct FightSideData {
    u16 yrot;
    u8 unk2[2];
    u32 fightTrainerStatusMenuDataId[2];
    u32 fightoutPokemonStatusMenuDataId[2];
};

struct Joutai {
    u8 unk0[0x10];
};

struct FightTrainer {
    u8 unk0[0x3744];
};

struct FightSide {
    u16 fightSideDataId;
    u8 unk2[2];
    Joutai joutai[6];
    FightTrainer fightTrainer[2];
    u8 makibisiCheckFlag;
};

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

void fightSideBiosSetMakibisiCheckFlag(FightSide* side, u8 flag) {
    if (side != NULL) {
        side->makibisiCheckFlag = flag;
    }
}

void fightSideBiosSetFightSideDataId(FightSide* side, u16 id) {
    if (side != NULL) {
        side->fightSideDataId = id;
    }
}

u8 fightSideBiosGetMakibisiCheckFlag(FightSide* side) {
    if (side == NULL) {
        return 0;
    }
    return side->makibisiCheckFlag;
}

FightTrainer* fightSideBiosGetFightTrainerPtr(FightSide* side, u16 index) {
    if (side == NULL) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return &side->fightTrainer[index];
}

Joutai* fightSideBiosGetJoutaiPtr(FightSide* side, u16 index) {
    if (side == NULL) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return &side->joutai[index];
}

u16 fightSideBiosGetFightSideDataId(FightSide* side) {
    if (side == NULL) {
        return 0;
    }
    return side->fightSideDataId;
}

}
