#include <dolphin/types.h>

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

struct FightSideData {
    u16 yrot;
};

extern "C" {

FightSideData* fightSideDataBiosGetPtr(u16 id);

void fightSide_SetMakibisiCheckFlag(FightSide* side, u8 flag) {
    if (side != NULL) {
        side->makibisiCheckFlag = flag;
    }
}

void fightSide_SetFightSideDataId(FightSide* side, u16 id) {
    if (side != NULL) {
        side->fightSideDataId = id;
    }
}

u8 fightSide_GetMakibisiCheckFlag(FightSide* side) {
    if (side == NULL) {
        return 0;
    }
    return side->makibisiCheckFlag;
}

FightTrainer* fightSide_GetFightTrainerPtr(FightSide* side, u16 index) {
    if (side == NULL) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return &side->fightTrainer[index];
}

Joutai* fightSide_GetJoutaiPtr(FightSide* side, u16 index) {
    if (side == NULL) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return &side->joutai[index];
}

u16 fightSide_GetFightSideDataId(FightSide* side) {
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
