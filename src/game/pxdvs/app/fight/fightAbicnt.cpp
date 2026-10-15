#include <dolphin/types.h>

// This unit was built optimizing for size (uses stmw/lmw).
#pragma optimize_for_size on

struct FightAbicntData {
    u8 kake;
    u8 waru;
};

extern "C" {

extern FightAbicntData fight_abicnt_data[];
extern u32 fight_abicnt_data_number;

u8 fightAbicntGetWaru(u16 id);
u8 fightAbicntGetKake(u16 id);
FightAbicntData* fightAbicntDataBiosGetPtr(u16 id);
u8 fightAbicntDataBiosGetWaru(FightAbicntData* data);
u8 fightAbicntDataBiosGetKake(FightAbicntData* data);

s32 fightAbicntFitMinMax(s32 value) {
    if (value < 0) {
        value = 0;
    }
    if (value > 12) {
        value = 12;
    }
    return value;
}

u32 fightAbicntDoKakeWaru(u16 id, u32 value) {
    u32 waru = fightAbicntGetWaru(id);
    return value * fightAbicntGetKake(id) / waru;
}

u8 fightAbicntGetWaru(u16 id) {
    FightAbicntData* data = fightAbicntDataBiosGetPtr(id);
    if (data == NULL) {
        return 1;
    }
    return fightAbicntDataBiosGetWaru(data);
}

u8 fightAbicntGetKake(u16 id) {
    FightAbicntData* data = fightAbicntDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return fightAbicntDataBiosGetKake(data);
}

u8 fightAbicntDataBiosGetWaru(FightAbicntData* data) {
    if (data == NULL) {
        return 1;
    }
    return data->waru;
}

u8 fightAbicntDataBiosGetKake(FightAbicntData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->kake;
}

FightAbicntData* fightAbicntDataBiosGetPtr(u16 id) {
    FightAbicntData* data = &fight_abicnt_data[id];
    if (id < fight_abicnt_data_number) {
        return data;
    }
    return 0;
}

}
