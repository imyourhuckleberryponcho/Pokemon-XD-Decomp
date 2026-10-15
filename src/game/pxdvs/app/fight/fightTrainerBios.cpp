#include <dolphin/types.h>

struct FightTrainerKindData {
    u16 syoukinBairitu;
    u8 unk2[2];
    u32 prefixName;
    u32 bgmSndId;
};

struct FightTrainerAiValueAddsubData {
    u8 unk0[0x14];
};

struct FightTrainerPokemonPartData {
    u8 unk0[0x18];
};

struct FightTrainerEnemyPokemon {
    s16 fightEntryeId;
    u8 storeWazaNum;
    u8 expectWazaNum;
    u16 storeWazaDataId[4];
    u16 expectWazaDataId[8];
    u8 tokuseiFlag;
    u8 unk1D;
    u16 storeTokuseiData;
    u8 nowhp1banhikuiFlag;
    u8 lv1banhikuiFlag;
    u8 defense1banhikuiFlag;
    u8 badwazaHaveFlag;
    u8 param1bantakaiFlag;
};

struct FightPokemon {
    u8 unk0[0x300];
};

struct FightTrainer {
    u8 unk0[4];
    u8 hero[0x97C - 4];
    FightPokemon fightPokemon[6];
    u8 unk1A7C[0x3540 - 0x97C - 6 * 0x300];
    u8 controllerId;
};

class DeckTrainer {
public:
    static DeckTrainer* getDeckTrainerObj(u32 id);
};

class DeckTrainerAI {
public:
    static DeckTrainerAI* getDeckTrainerAIObj(u32 id);
};

extern "C" {

extern u32* fight_trainer_kind_data_number;
extern FightTrainerKindData* fight_trainer_kind_data;
extern u32* fight_trainer_ai_value_addsub_data_number;
extern FightTrainerAiValueAddsubData* fight_trainer_ai_value_addsub_data;
extern u32* fight_trainer_pokemon_part_data_number;
extern FightTrainerPokemonPartData* fight_trainer_pokemon_part_data;

u32 fightTrainerKindDataBiosGetBgmSndId(FightTrainerKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->bgmSndId;
}

u32 fightTrainerKindDataBiosGetPrefixName(FightTrainerKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->prefixName;
}

u16 fightTrainerKindDataBiosGetSyoukinBairitu(FightTrainerKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->syoukinBairitu;
}

FightTrainerKindData* fightTrainerKindDataBiosGetPtr(u16 id) {
    if (id >= *fight_trainer_kind_data_number) {
        return 0;
    }
    return &fight_trainer_kind_data[id];
}

void fightTrainerEnemyPokemonBiosSetParam1bantakaiFlag(FightTrainerEnemyPokemon* pokemon, u8 value) {
    if (pokemon != NULL) {
        pokemon->param1bantakaiFlag = value;
    }
}

void fightTrainerEnemyPokemonBiosSetBadwazaHaveFlag(FightTrainerEnemyPokemon* pokemon, u8 value) {
    if (pokemon != NULL) {
        pokemon->badwazaHaveFlag = value;
    }
}

void fightTrainerEnemyPokemonBiosSetDefense1banhikuiFlag(FightTrainerEnemyPokemon* pokemon, u8 value) {
    if (pokemon != NULL) {
        pokemon->defense1banhikuiFlag = value;
    }
}

void fightTrainerEnemyPokemonBiosSetLv1banhikuiFlag(FightTrainerEnemyPokemon* pokemon, u8 value) {
    if (pokemon != NULL) {
        pokemon->lv1banhikuiFlag = value;
    }
}

void fightTrainerEnemyPokemonBiosSetNowhp1banhikuiFlag(FightTrainerEnemyPokemon* pokemon, u8 value) {
    if (pokemon != NULL) {
        pokemon->nowhp1banhikuiFlag = value;
    }
}

void fightTrainerEnemyPokemonBiosSetStoreTokuseiData(FightTrainerEnemyPokemon* pokemon, u16 value) {
    if (pokemon != NULL) {
        pokemon->storeTokuseiData = value;
    }
}

void fightTrainerEnemyPokemonBiosSetTokuseiFlag(FightTrainerEnemyPokemon* pokemon, u8 value) {
    if (pokemon != NULL) {
        pokemon->tokuseiFlag = value;
    }
}

void fightTrainerEnemyPokemonBiosSetExpectWazaDataId(FightTrainerEnemyPokemon* pokemon, u8 index, u16 id) {
    if (pokemon != NULL && index <= 8) {
        pokemon->expectWazaDataId[index] = id;
    }
}

void fightTrainerEnemyPokemonBiosSetStoreWazaDataId(FightTrainerEnemyPokemon* pokemon, u8 index, u16 id) {
    if (pokemon != NULL && index <= 4) {
        pokemon->storeWazaDataId[index] = id;
    }
}

void fightTrainerEnemyPokemonBiosSetExpectWazaNum(FightTrainerEnemyPokemon* pokemon, u8 value) {
    if (pokemon != NULL) {
        pokemon->expectWazaNum = value;
    }
}

void fightTrainerEnemyPokemonBiosSetStoreWazaNum(FightTrainerEnemyPokemon* pokemon, u8 value) {
    if (pokemon != NULL) {
        pokemon->storeWazaNum = value;
    }
}

void fightTrainerEnemyPokemonBiosSetFightEntryeId(FightTrainerEnemyPokemon* pokemon, s16 value) {
    if (pokemon != NULL) {
        pokemon->fightEntryeId = value;
    }
}

s16 fightTrainerEnemyPokemonBiosGetFightEntryeId(FightTrainerEnemyPokemon* pokemon) {
    if (pokemon == NULL) {
        return 0;
    }
    return pokemon->fightEntryeId;
}

FightTrainerAiValueAddsubData* fightTrainerAiValueAddsubDataBiosGetPtr(u16 id) {
    if (id >= *fight_trainer_ai_value_addsub_data_number) {
        return 0;
    }
    return &fight_trainer_ai_value_addsub_data[id];
}

FightTrainerPokemonPartData* fightTrainerPokemonPartDataBiosGetPtr(u16 id) {
    if (id >= *fight_trainer_pokemon_part_data_number) {
        return 0;
    }
    return &fight_trainer_pokemon_part_data[id];
}

DeckTrainerAI* fightTrainerAiDataBiosGetPtr(u16 id) { return DeckTrainerAI::getDeckTrainerAIObj(id); }

DeckTrainer* fightTrainerDataBiosGetPtr(u16 id) {
    switch (id) {
    case 5000:
        id = 1;
        break;
    case 5001:
    case 5003:
    case 5005:
        id = 2;
        break;
    case 5002:
    case 5004:
    case 5006:
        id = 3;
        break;
    }
    return DeckTrainer::getDeckTrainerObj(id);
}

u8 fightTrainerBiosGetControllerId(FightTrainer* trainer) {
    if (trainer == NULL) {
        return 0;
    }
    return trainer->controllerId;
}

FightPokemon* fightTrainerBiosGetFightPokemonPtr(FightTrainer* trainer, u16 index) {
    if (trainer == NULL) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return &trainer->fightPokemon[index];
}

void* fightTrainerBiosGetHeroPtr(FightTrainer* trainer) {
    if (trainer == NULL) {
        return NULL;
    }
    return trainer->hero;
}

}
