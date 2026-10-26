#include <dolphin/types.h>

#pragma optimize_for_size on

struct FightTypeData {
    u8 type;
    u8 entryPokemonNum;
    u8 fightoutPokemonNum;
    u8 unk3;
    u32 name;
};

extern "C" {

extern u32* fight_type_data_number;
extern FightTypeData* fight_type_data;

FightTypeData* fightTypeDataBiosGetPtr(u16 id);
u8 fightTypeDataBiosGetTrainerNum(FightTypeData* data);
u8 fightTypeDataBiosGetFightoutPokemonNum(FightTypeData* data);

u16 fightTypeGetFightSideFightOutPokemonMax(u16 id) {
    u8 trainerNum = fightTypeDataBiosGetTrainerNum(fightTypeDataBiosGetPtr(id));
    u8 fightoutPokemonNum = fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(id));
    return trainerNum * fightoutPokemonNum;
}

u8 fightTypeDataBiosGetFightoutPokemonNum(FightTypeData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->fightoutPokemonNum;
}

u8 fightTypeDataBiosGetEntryPokemonNum(FightTypeData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->entryPokemonNum;
}

u8 fightTypeDataBiosGetTrainerNum(FightTypeData* data) {
    if (data == NULL) {
        return 0;
    }
    switch (data->type) {
    case 0:
        return 1;
    case 1:
        return 1;
    case 2:
        return 2;
    }
    return 0;
}

u32 fightTypeDataBiosGetName(FightTypeData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->name;
}

FightTypeData* fightTypeDataBiosGetPtr(u16 id) {
    if (id > *fight_type_data_number) {
        return 0;
    }
    return &fight_type_data[id];
}

}
