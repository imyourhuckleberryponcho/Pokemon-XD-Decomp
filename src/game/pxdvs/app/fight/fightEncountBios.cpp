#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/pxdvs/app/deck/deckDataVirtual.h>
#include <game/pxdvs/app/fight/fightData.h>

struct FightEncountWipeData {
    u8 snapshotUse;
    u8 unk1;
    u16 effectSndID;
    f32 effectTime;
    void* function;
};

DeckDataVirtual* deckDataVirtual_GetPtr(u16 id);

extern "C" {

extern FightEncountWipeData fight_encount_wipe_data[];
extern u32 fight_encount_wipe_data_number;
extern u32* fight_encount_data_number;
extern FightEncountData* fight_encount_data;
extern u32* fight_type_data_number;

FightTypeData* fightTypeDataBiosGetPtr(u16 id);
u8 fightTypeDataBiosGetFightoutPokemonNum(FightTypeData* data);
u8 fightTypeDataBiosGetEntryPokemonNum(FightTypeData* data);
FightTrainerInfo* fightEncountDataBiosGetFightTrainerInfoPtr(FightEncountData* data, u8 index);

void fightEncountDataBiosSetDiskId(FightEncountData* data, u16 value) {
    if (data != NULL) {
        data->diskId = value;
    }
}

u16 fightEncountDataBiosGetDiskId(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->diskId;
}

u16 fightEncountDataBiosGetWipeEffectSndID(FightEncountWipeData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->effectSndID;
}

f32 fightEncountDataBiosGetWipeEffectTime(FightEncountWipeData* data) {
    if (data == NULL) {
        return 0.0f;
    }
    return data->effectTime;
}

u8 fightEncountDataBiosGetWipeSnapshotUse(FightEncountWipeData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->snapshotUse ? 1 : 0;
}

void* fightEncountDataBiosGetWipeFunction(FightEncountWipeData* data) {
    if (data == NULL) {
        return NULL;
    }
    return data->function;
}

FightEncountWipeData* fightEncountWipeDataBiosGetPtr(u32 id) {
    if (id >= fight_encount_wipe_data_number) {
        return 0;
    }
    return &fight_encount_wipe_data[id];
}

u32 fightEncountDataBiosGetFightName(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->fightName;
}

void fightEncountDataBiosSetSyoukaiWzxDataId(FightEncountData* data, u32 value) {
    if (data != NULL) {
        data->syoukaiWzxDataId = value;
    }
}

void fightEncountDataBiosSetZenmetuFlag(FightEncountData* data, u8 value) {
    if (data != NULL) {
        data->zenmetuFlag = value;
    }
}

void fightEncountDataBiosSetBgmSndId(FightEncountData* data, u32 value) {
    if (data != NULL) {
        data->bgmSndId = value;
    }
}

void fightEncountDataBiosSetGSInputDevice(FightEncountData* data, u8 index, u32 device) {
    FightTrainerInfo* info = fightEncountDataBiosGetFightTrainerInfoPtr(data, index);
    if (info != NULL) {
        info->gsInputDevice = device;
    }
}

void fightEncountDataBiosSetFightTrainerDataId(FightEncountData* data, u8 index, u16 id) {
    FightTrainerInfo* info = fightEncountDataBiosGetFightTrainerInfoPtr(data, index);
    if (info != NULL) {
        info->ids = (info->ids & 0xFFFF0000) | id;
    }
}

void fightEncountDataBiosSetFightFloorDataId(FightEncountData* data, u16 value) {
    if (data != NULL) {
        data->fightFloorDataId = value;
    }
}

void fightEncountDataBiosSetEntry(FightEncountData* data, u8 value) {
    if (data != NULL) {
        data->entry = value;
    }
}

void fightEncountDataBiosSetPokemon(FightEncountData* data, u8 value) {
    if (data != NULL) {
        data->pokemon = value;
    }
}

void fightEncountDataBiosSetTrainer(FightEncountData* data, u8 value) {
    if (data != NULL) {
        data->trainer = value;
    }
}

void fightEncountDataBiosSetFightType(FightEncountData* data, u8) {
    if (data == NULL) {
        return;
    }
}

void fightEncountDataBiosSetFightKind(FightEncountData* data, u8 value) {
    if (data != NULL) {
        data->fightKind = value;
    }
}

u32 fightEncountDataBiosGetSyoukaiWzxDataId(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->syoukaiWzxDataId;
}

u8 fightEncountDataBiosGetZenmetuFlag(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->zenmetuFlag;
}

u32 fightEncountDataBiosGetWipeId(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->wipeId;
}

u32 fightEncountDataBiosGetBgmSndId(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->bgmSndId;
}

u32 fightEncountDataBiosGetGSInputDevice(FightEncountData* data, u8 index) {
    FightTrainerInfo* info = fightEncountDataBiosGetFightTrainerInfoPtr(data, index);
    if (info == NULL) {
        return 0;
    }
    return info->gsInputDevice;
}

u16 fightEncountDataBiosGetFightDeckGrpId(FightEncountData* data, u8 index) {
    FightTrainerInfo* info = fightEncountDataBiosGetFightTrainerInfoPtr(data, index);
    if (info == NULL) {
        return 0;
    }
    if (data->diskId == 0) {
        return info->ids >> 16;
    }
    return 4;
}

u16 fightEncountDataBiosGetFightTrainerDataId(FightEncountData* data, u8 index) {
    FightTrainerInfo* info = fightEncountDataBiosGetFightTrainerInfoPtr(data, index);
    if (info == NULL) {
        return 0;
    }
    if (data->diskId == 0) {
        return info->ids & 0xFFFF;
    }
    DeckDataVirtual* deck = deckDataVirtual_GetPtr(data->diskId);
    if (deck == NULL) {
        return 0;
    }
    switch (index) {
    case 0:
        return deck->allyDeck;
    case 1:
        return deck->enemyDeck;
    }
    return 0;
}

FightTrainerInfo* fightEncountDataBiosGetFightTrainerInfoPtr(FightEncountData* data, u8 index) {
    if (data == NULL) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return &data->trainerInfo[index];
}

u16 fightEncountDataBiosGetFightFloorDataId(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->fightFloorDataId;
}

PCRET(u8) fightEncountDataBiosGetEntry(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->entry;
}

PCRET(u8) fightEncountDataBiosGetPokemon(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    if (data->diskId == 0) {
        return data->pokemon;
    }
    DeckDataVirtual* deck = deckDataVirtual_GetPtr(data->diskId);
    if (deck == NULL) {
        return 0;
    }
    return deck->pokemonNum;
}

PCRET(u8) fightEncountDataBiosGetTrainer(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->trainer;
}

PCRET(u8) fightEncountDataBiosGetFightType(FightEncountData* data) {
    FightTypeData* type;
    u8 i;
    if (data == NULL) {
        return 0;
    }
    for (i = 0; i < *fight_type_data_number; i++) {
        type = fightTypeDataBiosGetPtr(i);
        if (data->trainer == type->type && data->pokemon == fightTypeDataBiosGetFightoutPokemonNum(type) &&
            data->entry == fightTypeDataBiosGetEntryPokemonNum(type)) {
            return i;
        }
    }
    return 3;
}

PCRET(u8) fightEncountDataBiosGetFightKind(FightEncountData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->fightKind;
}

FightEncountData* fightEncountDataBiosGetPtr(u16 id) {
    if (id >= *fight_encount_data_number) {
        return 0;
    }
    return &fight_encount_data[id];
}

}
