#include <dolphin/types.h>

struct FightJoutai {
    u8 unk0[0x10];
};

struct FightSide {
    u8 unk0[0x6EF0];
};

struct FightFloorData {
    u8 tikeiDataId;
    u8 unk1[0x1];
    u16 floorDataId;
    u32 name;
    u32 syoukaiWzxDataId;
    u32 bgmSndId;
    u32 envSndId;
    u16 fightSideDataIds[2];
};

struct FightFloor {
    FightJoutai joutai[1];
    u16 turnCount;
    u16 encountDataId;
    FightSide sides[2];
    void* attackPokemonPtr;
    void* defensePokemonPtr;
    void* escapePokemonPtr;
    void* irekaePokemonPtr;
    void* kizetuPokemonPtr;
    void* tuikakoukaPokemonPtr;
    void* tokuseiPokemonPtr;
    void* itemPokemonPtr;
    void* appointPokemonPtr;
    void* appointTrainerPtr;
    void* appointWazaPtr;
    void* appointSidePtr;
    void* appointItemPtr;
    u32 attackMsgId;
    u32 criticalMsgId;
    u32 wazakoukaMsgId;
    u32 appointMsgId;
    u16 appointPokemonDataId;
    u16 appointWazaDataId;
    u16 appointItemDataId;
    u16 appointTokuseiDataId;
    s16 fightPokemonEntryCnt;
    u8 unkDE42[0x2];
    void* fightOutPokemonPtrAry[8];
    u16 firstAttackRnd;
    u8 unkDE66[0x4B2];
};

extern "C" {

extern u32 encount_floor_id;
extern u32* fight_floor_data_number;
extern FightFloorData* fight_floor_data;
extern FightFloor fight_floor;

void fightFloorBiosSetEncountFloorId(u32 id) {
    encount_floor_id = id;
}

u32 fightFloorBiosGetEncountFloorId(void) {
    return encount_floor_id;
}

void fightFloorBiosSetItemPokemonPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->itemPokemonPtr = value;
    }
}

void* fightFloorBiosGetItemPokemonPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->itemPokemonPtr;
}

void fightFloorBiosSetTokuseiPokemonPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->tokuseiPokemonPtr = value;
    }
}

void* fightFloorBiosGetTokuseiPokemonPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->tokuseiPokemonPtr;
}

void fightFloorBiosSetTuikakoukaPokemonPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->tuikakoukaPokemonPtr = value;
    }
}

void* fightFloorBiosGetTuikakoukaPokemonPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->tuikakoukaPokemonPtr;
}

void fightFloorBiosSetKizetuPokemonPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->kizetuPokemonPtr = value;
    }
}

void* fightFloorBiosGetKizetuPokemonPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->kizetuPokemonPtr;
}

void fightFloorBiosSetFirstAttackRnd(FightFloor* p, u16 value) {
    if (p != NULL) {
        p->firstAttackRnd = value;
    }
}

u16 fightFloorBiosGetFirstAttackRnd(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->firstAttackRnd;
}

void fightFloorBiosSetFightOutPokemonPtrAryPtr(FightFloor* p, void** ary) {
    u16 i;
    if (p == NULL) {
        return;
    }
    for (i = 0; i < 8; i++) {
        p->fightOutPokemonPtrAry[i] = ary[i];
    }
}

void** fightFloorBiosGetFightOutPokemonPtrAryPtr(FightFloor* p) {
    if (p == NULL) {
        return NULL;
    }
    return p->fightOutPokemonPtrAry;
}

void fightFloorBiosSetFightOutPokemonPtrAry(FightFloor* p, u16 index, void* pokemon) {
    if (p == NULL) {
        return;
    }
    if (index >= 8) {
        return;
    }
    p->fightOutPokemonPtrAry[index] = pokemon;
}

void* fightFloorBiosGetFightOutPokemonPtrAry(FightFloor* p, u16 index) {
    if (p == NULL) {
        return NULL;
    }
    if (index >= 8) {
        return NULL;
    }
    return p->fightOutPokemonPtrAry[index];
}

void fightFloorBiosSetFightPokemonEntryCnt(FightFloor* p, s16 value) {
    if (p != NULL) {
        p->fightPokemonEntryCnt = value;
    }
}

s16 fightFloorBiosGetFightPokemonEntryCnt(FightFloor* p) {
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
    p->fightSideDataIds[index] = id;
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
    return p->fightSideDataIds[index];
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

void fightFloorBiosSetAppointTokuseiDataId(FightFloor* p, u16 value) {
    if (p != NULL) {
        p->appointTokuseiDataId = value;
    }
}

void fightFloorBiosSetAppointItemDataId(FightFloor* p, u16 value) {
    if (p != NULL) {
        p->appointItemDataId = value;
    }
}

void fightFloorBiosSetAppointWazaDataId(FightFloor* p, u16 value) {
    if (p != NULL) {
        p->appointWazaDataId = value;
    }
}

void fightFloorBiosSetAppointPokemonDataId(FightFloor* p, u16 value) {
    if (p != NULL) {
        p->appointPokemonDataId = value;
    }
}

void fightFloorBiosSetWazakoukaMsgId(FightFloor* p, u32 value) {
    if (p != NULL) {
        p->wazakoukaMsgId = value;
    }
}

void fightFloorBiosSetCriticalMsgId(FightFloor* p, u32 value) {
    if (p != NULL) {
        p->criticalMsgId = value;
    }
}

void fightFloorBiosSetAttackMsgId(FightFloor* p, u32 value) {
    if (p != NULL) {
        p->attackMsgId = value;
    }
}

void fightFloorBiosSetAppointMsgId(FightFloor* p, u32 value) {
    if (p != NULL) {
        p->appointMsgId = value;
    }
}

void fightFloorBiosSetAppointItemPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->appointItemPtr = value;
    }
}

void fightFloorBiosSetAppointSidePtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->appointSidePtr = value;
    }
}

void fightFloorBiosSetAppointWazaPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->appointWazaPtr = value;
    }
}

void fightFloorBiosSetAppointTrainerPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->appointTrainerPtr = value;
    }
}

void fightFloorBiosSetAppointPokemonPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->appointPokemonPtr = value;
    }
}

void fightFloorBiosSetIrekaePokemonPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->irekaePokemonPtr = value;
    }
}

void fightFloorBiosSetEscapePokemonPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->escapePokemonPtr = value;
    }
}

void fightFloorBiosSetDefensePokemonPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->defensePokemonPtr = value;
    }
}

void fightFloorBiosSetAttackPokemonPtr(FightFloor* p, void* value) {
    if (p != NULL) {
        p->attackPokemonPtr = value;
    }
}

void fightFloorBiosSetEncountDataId(FightFloor* p, u16 value) {
    if (p != NULL) {
        p->encountDataId = value;
    }
}

void fightFloorBiosSetTurnCount(FightFloor* p, u16 value) {
    if (p != NULL) {
        p->turnCount = value;
    }
}

u16 fightFloorBiosGetAppointTokuseiDataId(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointTokuseiDataId;
}

u16 fightFloorBiosGetAppointItemDataId(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointItemDataId;
}

u16 fightFloorBiosGetAppointWazaDataId(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointWazaDataId;
}

u16 fightFloorBiosGetAppointPokemonDataId(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointPokemonDataId;
}

u32 fightFloorBiosGetWazakoukaMsgId(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->wazakoukaMsgId;
}

u32 fightFloorBiosGetCriticalMsgId(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->criticalMsgId;
}

u32 fightFloorBiosGetAttackMsgId(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->attackMsgId;
}

u32 fightFloorBiosGetAppointMsgId(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointMsgId;
}

void* fightFloorBiosGetAppointItemPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointItemPtr;
}

void* fightFloorBiosGetAppointSidePtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointSidePtr;
}

void* fightFloorBiosGetAppointWazaPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointWazaPtr;
}

void* fightFloorBiosGetAppointTrainerPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointTrainerPtr;
}

void* fightFloorBiosGetAppointPokemonPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->appointPokemonPtr;
}

void* fightFloorBiosGetIrekaePokemonPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->irekaePokemonPtr;
}

void* fightFloorBiosGetEscapePokemonPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->escapePokemonPtr;
}

void* fightFloorBiosGetDefensePokemonPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->defensePokemonPtr;
}

void* fightFloorBiosGetAttackPokemonPtr(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->attackPokemonPtr;
}

FightSide* fightFloorBiosGetFightSidePtr(FightFloor* p, u16 index) {
    if (p == NULL) {
        return NULL;
    }
    if (index >= 2) {
        return NULL;
    }
    return &p->sides[index];
}

u16 fightFloorBiosGetEncountDataId(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->encountDataId;
}

u16 fightFloorBiosGetTurnCount(FightFloor* p) {
    if (p == NULL) {
        return 0;
    }
    return p->turnCount;
}

FightJoutai* fightFloorBiosGetJoutaiPtr(FightFloor* p, u16 index) {
    if (p == NULL) {
        return NULL;
    }
    if (index >= 1) {
        return NULL;
    }
    return &p->joutai[index];
}

FightFloor* fightFloorBiosGetFightFloorPtr(void) {
    return &fight_floor;
}

}
