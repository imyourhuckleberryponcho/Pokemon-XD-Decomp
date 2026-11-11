#include <dolphin/types.h>
#include <game/fightfloor.h>
#define FIGHT_TRAINER_OPAQUE_RECORDS
#include <game/pxdvs/app/fight/fightTrainerData.h>
#include <game/pxdvs/app/fight/fightData.h>

#include <game/pxdvs/app/fight/fightTrainerTables.h>

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
        pokemon->expectWaza[index] = id;
    }
}

void fightTrainerEnemyPokemonBiosSetStoreWazaDataId(FightTrainerEnemyPokemon* pokemon, u8 index, u16 id) {
    if (pokemon != NULL && index <= 4) {
        pokemon->storeWaza[index] = id;
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
        pokemon->fightEntryId = value;
    }
}

s16 fightTrainerEnemyPokemonBiosGetFightEntryeId(FightTrainerEnemyPokemon* pokemon) {
    if (pokemon == NULL) {
        return 0;
    }
    return pokemon->fightEntryId;
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
