#include <dolphin/types.h>
#include <game/fightfloor.h>
#include <game/pxdvs/app/fight/fightData.h>

#include <game/pxdvs/app/fight/fightFloorData.h>

extern "C" {

extern u32 encount_floor_id;
extern u32* fight_floor_data_number;
extern FightFloorData* fight_floor_data;
extern FIGHT_FLOOR fight_floor;

void fightFloorBiosSetEncountFloorId(u32 id) {
    encount_floor_id = id;
}

u32 fightFloorBiosGetEncountFloorId(void) {
    return encount_floor_id;
}

void fightFloorBiosSetItemPokemonPtr(FIGHT_FLOOR* p, FightOutPokemon* value) {
    if (p != NULL) {
        p->itemPokemon = value;
    }
}

FightOutPokemon* fightFloorBiosGetItemPokemonPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->itemPokemon;
}

void fightFloorBiosSetTokuseiPokemonPtr(FIGHT_FLOOR* p, FightOutPokemon* value) {
    if (p != NULL) {
        p->tokuseiPokemon = value;
    }
}

FightOutPokemon* fightFloorBiosGetTokuseiPokemonPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->tokuseiPokemon;
}

void fightFloorBiosSetTuikakoukaPokemonPtr(FIGHT_FLOOR* p, FightOutPokemon* value) {
    if (p != NULL) {
        p->tuikakoukaPokemon = value;
    }
}

FightOutPokemon* fightFloorBiosGetTuikakoukaPokemonPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->tuikakoukaPokemon;
}

void fightFloorBiosSetKizetuPokemonPtr(FIGHT_FLOOR* p, FightOutPokemon* value) {
    if (p != NULL) {
        p->kizetuPokemon = value;
    }
}

FightOutPokemon* fightFloorBiosGetKizetuPokemonPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->kizetuPokemon;
}

void fightFloorBiosSetFirstAttackRnd(FIGHT_FLOOR* p, u16 value) {
    if (p != NULL) {
        p->firstAttackRnd = value;
    }
}

u16 fightFloorBiosGetFirstAttackRnd(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->firstAttackRnd;
}

void fightFloorBiosSetFightOutPokemonPtrAryPtr(FIGHT_FLOOR* p, FightOutPokemon** ary) {
    u16 i;
    if (p == NULL) {
        return;
    }
    for (i = 0; i < 8; i++) {
        p->fightOutPokemon[i] = ary[i];
    }
}

FightOutPokemon** fightFloorBiosGetFightOutPokemonPtrAryPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return NULL;
    }
    return p->fightOutPokemon;
}

void fightFloorBiosSetFightOutPokemonPtrAry(FIGHT_FLOOR* p, u16 index, FightOutPokemon* pokemon) {
    if (p == NULL) {
        return;
    }
    if (index >= 8) {
        return;
    }
    p->fightOutPokemon[index] = pokemon;
}

FightOutPokemon* fightFloorBiosGetFightOutPokemonPtrAry(FIGHT_FLOOR* p, u16 index) {
    if (p == NULL) {
        return NULL;
    }
    if (index >= 8) {
        return NULL;
    }
    return p->fightOutPokemon[index];
}

void fightFloorBiosSetFightPokemonEntryCnt(FIGHT_FLOOR* p, s16 value) {
    if (p != NULL) {
        p->fightPokemonEntryCnt = value;
    }
}

s16 fightFloorBiosGetFightPokemonEntryCnt(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->fightPokemonEntryCnt;
}

void fightFloorDataBiosSetName(FightFloorData* p, u32 value) {
    if (p != NULL) {
        p->name = value;
    }
}

u32 fightFloorDataBiosGetName(FightFloorData* p) {
    if (p == NULL) {
        return 0;
    }
    return p->name;
}

void fightFloorDataBiosSetEnvSndId(FightFloorData* p, u32 value) {
    if (p != NULL) {
        p->envSndId = value;
    }
}

void fightFloorDataBiosSetBgmSndId(FightFloorData* p, u32 value) {
    if (p != NULL) {
        p->bgmSndId = value;
    }
}

void fightFloorDataBiosSetSyoukaiWzxDataId(FightFloorData* p, u32 value) {
    if (p != NULL) {
        p->syoukaiWzxDataId = value;
    }
}

void fightFloorDataBiosSetTikeiDataId(FightFloorData* p, u8 value) {
    if (p != NULL) {
        p->tikeiDataId = value;
    }
}

void fightFloorDataBiosSetFightSideDataId(FightFloorData* p, u8 index, u16 id) {
    if (p == NULL) {
        return;
    }
    if (index >= 2) {
        return;
    }
    p->fightSideDataId[index] = id;
}

void fightFloorDataBiosSetFloorDataId(FightFloorData* p, u16 value) {
    if (p != NULL) {
        p->floorDataId = value;
    }
}

u32 fightFloorDataBiosGetEnvSndId(FightFloorData* p) {
    if (p == NULL) {
        return 0;
    }
    return p->envSndId;
}

u32 fightFloorDataBiosGetBgmSndId(FightFloorData* p) {
    if (p == NULL) {
        return 0;
    }
    return p->bgmSndId;
}

u32 fightFloorDataBiosGetSyoukaiWzxDataId(FightFloorData* p) {
    if (p == NULL) {
        return 0;
    }
    return p->syoukaiWzxDataId;
}

u8 fightFloorDataBiosGetTikeiDataId(FightFloorData* p) {
    if (p == NULL) {
        return 0;
    }
    return p->tikeiDataId;
}

u16 fightFloorDataBiosGetFightSideDataId(FightFloorData* p, u8 index) {
    if (p == NULL) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return p->fightSideDataId[index];
}

u16 fightFloorDataBiosGetFloorDataId(FightFloorData* p) {
    if (p == NULL) {
        return 0;
    }
    return p->floorDataId;
}

FightFloorData* fightFloorDataBiosGetPtr(u16 id) {
    if (id >= *fight_floor_data_number) {
        return NULL;
    }
    return &fight_floor_data[id];
}

void fightFloorBiosSetAppointTokuseiDataId(FIGHT_FLOOR* p, u16 value) {
    if (p != NULL) {
        p->appointTokuseiDataId = value;
    }
}

void fightFloorBiosSetAppointItemDataId(FIGHT_FLOOR* p, u16 value) {
    if (p != NULL) {
        p->appointItemDataId = value;
    }
}

void fightFloorBiosSetAppointWazaDataId(FIGHT_FLOOR* p, u16 value) {
    if (p != NULL) {
        p->appointWazaDataId = value;
    }
}

void fightFloorBiosSetAppointPokemonDataId(FIGHT_FLOOR* p, u16 value) {
    if (p != NULL) {
        p->appointPokemonDataId = value;
    }
}

void fightFloorBiosSetWazakoukaMsgId(FIGHT_FLOOR* p, u32 value) {
    if (p != NULL) {
        p->wazakoukaMsgId = value;
    }
}

void fightFloorBiosSetCriticalMsgId(FIGHT_FLOOR* p, u32 value) {
    if (p != NULL) {
        p->criticalMsgId = value;
    }
}

void fightFloorBiosSetAttackMsgId(FIGHT_FLOOR* p, u32 value) {
    if (p != NULL) {
        p->attackMsgId = value;
    }
}

void fightFloorBiosSetAppointMsgId(FIGHT_FLOOR* p, u32 value) {
    if (p != NULL) {
        p->appointMsgId = value;
    }
}

void fightFloorBiosSetAppointItemPtr(FIGHT_FLOOR* p, void* value) {
    if (p != NULL) {
        p->appointItem = value;
    }
}

void fightFloorBiosSetAppointSidePtr(FIGHT_FLOOR* p, void* value) {
    if (p != NULL) {
        p->appointSide = value;
    }
}

void fightFloorBiosSetAppointWazaPtr(FIGHT_FLOOR* p, void* value) {
    if (p != NULL) {
        p->appointWaza = value;
    }
}

void fightFloorBiosSetAppointTrainerPtr(FIGHT_FLOOR* p, void* value) {
    if (p != NULL) {
        p->appointTrainer = value;
    }
}

void fightFloorBiosSetAppointPokemonPtr(FIGHT_FLOOR* p, FightOutPokemon* value) {
    if (p != NULL) {
        p->appointPokemon = value;
    }
}

void fightFloorBiosSetIrekaePokemonPtr(FIGHT_FLOOR* p, FightOutPokemon* value) {
    if (p != NULL) {
        p->irekaePokemon = value;
    }
}

void fightFloorBiosSetEscapePokemonPtr(FIGHT_FLOOR* p, FightOutPokemon* value) {
    if (p != NULL) {
        p->escapePokemon = value;
    }
}

void fightFloorBiosSetDefensePokemonPtr(FIGHT_FLOOR* p, FightOutPokemon* value) {
    if (p != NULL) {
        p->defensePokemon = value;
    }
}

void fightFloorBiosSetAttackPokemonPtr(FIGHT_FLOOR* p, FightOutPokemon* value) {
    if (p != NULL) {
        p->attackPokemon = value;
    }
}

void fightFloorBiosSetEncountDataId(FIGHT_FLOOR* p, u16 value) {
    if (p != NULL) {
        p->encountDataId = value;
    }
}

void fightFloorBiosSetTurnCount(FIGHT_FLOOR* p, u16 value) {
    if (p != NULL) {
        p->turnCount = value;
    }
}

u16 fightFloorBiosGetAppointTokuseiDataId(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointTokuseiDataId;
}

u16 fightFloorBiosGetAppointItemDataId(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointItemDataId;
}

u16 fightFloorBiosGetAppointWazaDataId(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointWazaDataId;
}

u16 fightFloorBiosGetAppointPokemonDataId(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointPokemonDataId;
}

u32 fightFloorBiosGetWazakoukaMsgId(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->wazakoukaMsgId;
}

u32 fightFloorBiosGetCriticalMsgId(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->criticalMsgId;
}

u32 fightFloorBiosGetAttackMsgId(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->attackMsgId;
}

u32 fightFloorBiosGetAppointMsgId(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointMsgId;
}

void* fightFloorBiosGetAppointItemPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointItem;
}

void* fightFloorBiosGetAppointSidePtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointSide;
}

void* fightFloorBiosGetAppointWazaPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointWaza;
}

void* fightFloorBiosGetAppointTrainerPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointTrainer;
}

FightOutPokemon* fightFloorBiosGetAppointPokemonPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointPokemon;
}

FightOutPokemon* fightFloorBiosGetIrekaePokemonPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->irekaePokemon;
}

FightOutPokemon* fightFloorBiosGetEscapePokemonPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->escapePokemon;
}

FightOutPokemon* fightFloorBiosGetDefensePokemonPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->defensePokemon;
}

FightOutPokemon* fightFloorBiosGetAttackPokemonPtr(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->attackPokemon;
}

FIGHT_SIDE* fightFloorBiosGetFightSidePtr(FIGHT_FLOOR* p, u16 index) {
    if (p == NULL) {
        return NULL;
    }
    if (index >= 2) {
        return NULL;
    }
    return &p->sides[index];
}

u16 fightFloorBiosGetEncountDataId(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->encountDataId;
}

u16 fightFloorBiosGetTurnCount(FIGHT_FLOOR* p) {
    if (p == NULL) {
        return 0;
    }
    return p->turnCount;
}

FightJoutai* fightFloorBiosGetJoutaiPtr(FIGHT_FLOOR* p, u16 index) {
    if (p == NULL) {
        return NULL;
    }
    if (index >= 1) {
        return NULL;
    }
    return &p->joutai[index];
}

FIGHT_FLOOR* fightFloorBiosGetFightFloorPtr(void) {
    return &fight_floor;
}

}
