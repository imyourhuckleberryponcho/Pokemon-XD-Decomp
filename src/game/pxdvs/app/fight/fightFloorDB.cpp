#include <dolphin/types.h>

struct FightOutPokemon;
struct FightJoutai {
    u8 data[0x10];
};

struct Pokemon {
    u8 data[0xC4];
};

class FIGHT_TRAINER {
public:
    u8 data[0x3744];
};

class FIGHT_SIDE {
public:
    u8 data[0x64];
    FIGHT_TRAINER trainers[2];
    u8 pad[4];
};

struct FightFloorStock {
    Pokemon pokemon;
    u8 ballID;
    u8 pad[3];
};

class FIGHT_FLOOR {
public:
    u16 getTurnCount() const {
        if (this == 0) {
            return 0;
        }
        return turnCount;
    }

    FightJoutai joutai[1];
    u16 turnCount;
    u16 encountDataId;
    FIGHT_SIDE sides[2];
    FightOutPokemon* attackPokemon;
    FightOutPokemon* defensePokemon;
    FightOutPokemon* escapePokemon;
    FightOutPokemon* irekaePokemon;
    FightOutPokemon* kizetuPokemon;
    FightOutPokemon* tuikakoukaPokemon;
    FightOutPokemon* tokuseiPokemon;
    FightOutPokemon* itemPokemon;
    FightOutPokemon* appointPokemon;
    void* appointTrainer;
    void* appointWaza;
    void* appointSide;
    void* appointItem;
    u32 wazakoukaMsgId;
    u32 criticalMsgId;
    u32 attackMsgId;
    u32 appointMsgId;
    u16 appointDataIds[4];
    s16 fightPokemonEntryCnt;
    FightOutPokemon* fightOutPokemon[8];
    u16 firstAttackRnd;
    u8 stockPokemonNum;
    u8 padDE67;
    FightFloorStock stock[6];
};

struct FightFloorData {
    u8 tikeiDataId;
    u16 floorDataId;
    u8 unk4[4];
    u32 syoukaiWzxDataId;
    u32 bgmSndId;
    u32 envSndId;
    u16 fightSideDataId[2];
};

extern "C" {

void* memcpy(void* dst, const void* src, u32 n);
FIGHT_FLOOR* fightFloorBiosGetFightFloorPtr(void);
void fightFloorBiosSetFirstAttackRnd(FIGHT_FLOOR*, u16);
void fightFloorBiosSetFightOutPokemonPtrAryPtr(FIGHT_FLOOR*, FightOutPokemon**);
void fightFloorBiosSetFightPokemonEntryCnt(FIGHT_FLOOR*, s16);
void fightFloorBiosSetAppointTokuseiDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetAppointItemDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetAppointWazaDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetAppointPokemonDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetWazakoukaMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetCriticalMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAttackMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetEncountFloorId(u32);
u32 fightFloorBiosGetEncountFloorId(void);
void fightFloorBiosSetItemPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetTokuseiPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetTuikakoukaPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetKizetuPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetIrekaePokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetEscapePokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetDefensePokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetAttackPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
FightOutPokemon* fightFloorBiosGetAttackPokemonPtr(FIGHT_FLOOR*);
void fightFloorBiosSetEncountDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetTurnCount(FIGHT_FLOOR*, u16);

void pokemonBiosCopy(Pokemon* dst, Pokemon* src);
void fightMsgctrlSetValue(s32 id, u32 value);
u32 GSmsgGetGSchar(u32 id);
void* pokemonTokuseiDataBiosGetPtr(u16 id);
u32 pokemonTokuseiDataBiosGetName(void* data);
u32 itemDB_GetName(u16 id);
u8 fightOutPokemonCheckValid(FightOutPokemon*);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
u16 fightOutPokemonGetSoubiItemDataId(FightOutPokemon*);
void fightOutPokemon_SetWazaTargetId(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaJoutaiDataId(FightOutPokemon*, u16);
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u8);

void* fightKindDataBiosGetPtr(u8 id);
u8 fightKindDataBiosGetRegulationFlag(void*);
u8 fightKindDataBiosGetHostEnemyMsgFlag(void*);
u8 fightKindDataBiosGetPokemonStatusMenuSubbarFlag(void*);
u8 fightKindDataBiosGetDarkpokemonHypermodeFlag(void*);
u8 fightKindDataBiosGetMonohiroiFlag(void*);
u8 fightKindDataBiosGetDorobouFlag(void*);
u8 fightKindDataBiosGetBossFlag(void*);
u8 fightKindDataBiosGetKeikentihueruFlag(void*);
u8 fightKindDataBiosGetDoItemSoubiTokukoutokubouupFlag(void*);
u8 fightKindDataBiosGetDoHizukiMiyaburiFlag(void*);
u8 fightKindDataBiosGetDoCriticalAttackFlag(void*);
u8 fightKindDataBiosGetGetInfectPokerusFlag(void*);
u8 fightKindDataBiosGetGetFriendFlag(void*);
u8 fightKindDataBiosGetGetNekoniKobanFlag(void*);
u8 fightKindDataBiosGetGetOkaneFlag(void*);
u8 fightKindDataBiosGetOkanePoolFlag(void*);
u8 fightKindDataBiosGetGetExpFlag(void*);
u8 fightKindDataBiosGetDrawFlag(void*);
u8 fightKindDataBiosGetNigeruFlag(void*);
u8 fightKindDataBiosGetUseItemFlag(void*);
u8 fightKindDataBiosGetDoZukanTukamaetaFlag(void*);
u8 fightKindDataBiosGetDoZukanMitaFlag(void*);
u8 fightKindDataBiosGetDoBadgeCheckFlag(void*);
u8 fightKindDataBiosGetBackSaveDataFlag(void*);
u16 fightTypeGetFightSideFightOutPokemonMax(u8);
void* fightTypeDataBiosGetPtr(u8 id);
u8 fightTypeDataBiosGetFightoutPokemonNum(void*);
u8 fightTypeDataBiosGetEntryPokemonNum(void*);
u8 fightTypeDataBiosGetTrainerNum(void*);
u32 fightEncountGetEnvSndDataId(u16);
u32 fightFloorGetBgmSndDataId(FIGHT_FLOOR*);
void* fightEncountDataBiosGetPtr(u16);
u16 fightEncountDataBiosGetFightFloorDataId(void*);
u32 fightEncountDataBiosGetTrainer(void*);
s32 fightEncountDataBiosGetFightType(void*);
s32 fightEncountDataBiosGetFightKind(void*);
u8 fightFloorIsJoutaiDataId(FightJoutai*, u16);
FightFloorData* fightFloorDataBiosGetPtr(u16);

void fightFloor_SetAppointItemDataId(FIGHT_FLOOR* floor, u16 id);
void fightFloor_SetDefensePokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon);
void fightFloor_SetAttackPokemonFightWazaTargetId(FIGHT_FLOOR* floor, u16 id);
s32 fightFloor_GetFightType(FIGHT_FLOOR* floor);
s32 fightFloor_GetFightKind(FIGHT_FLOOR* floor);
u16 fightFloor_GetEncountDataId(FIGHT_FLOOR* floor);
u16 fightFloor_GetFightFloorDataId(FIGHT_FLOOR* floor);
u32 fightFloorDB_GetSyoukaiWzxDataId(u16 id);
u8 fightFloorDB_GetTikeiDataId(u16 id);

void fightFloor_SetStockPokemonBallID(FIGHT_FLOOR* floor, u8 index, u8 ballID) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return;
        }
    }
    if (index < 6) {
        floor->stock[index].ballID = ballID;
    }
}

u8 fightFloor_GetStockPokemonBallID(FIGHT_FLOOR* floor, u8 index) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    if (index >= 6) {
        return 0;
    }
    return floor->stock[index].ballID;
}

void fightFloor_SetStockPokemonPtr(FIGHT_FLOOR* floor, u8 index, Pokemon* pokemon) {
    Pokemon copy;

    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return;
        }
    }
    if (index < 6) {
        pokemonBiosCopy(&copy, pokemon);
        memcpy(&floor->stock[index].pokemon, &copy, sizeof(Pokemon));
    }
}

Pokemon* fightFloor_GetStockPokemonPtr(FIGHT_FLOOR* floor, u8 index) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    if (index >= 6) {
        return 0;
    }
    return &floor->stock[index].pokemon;
}

void fightFloor_SetStockPokemonNum(FIGHT_FLOOR* floor, u8 num) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return;
        }
    }
    floor->stockPokemonNum = num;
}

u8 fightFloor_GetStockPokemonNum(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->stockPokemonNum;
}

void fightFloor_SetFisstAttackRnd(FIGHT_FLOOR* floor, u16 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetFirstAttackRnd(floor, value);
}

void fightFloor_SetfightoutPokemonPtrAryPtr(FIGHT_FLOOR* floor, FightOutPokemon** value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetFightOutPokemonPtrAryPtr(floor, value);
}

void fightFloor_SetfightPokemonEntryCnt(FIGHT_FLOOR* floor, s16 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetFightPokemonEntryCnt(floor, value);
}

void fightFloor_SetAppointTokuseiDataId(FIGHT_FLOOR* floor, u16 id) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightMsgctrlSetValue(0x1C, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(id))));
    fightFloorBiosSetAppointTokuseiDataId(floor, id);
}

void fightFloor_SetAppointItemDataId(FIGHT_FLOOR* floor, u16 id) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightMsgctrlSetValue(0x29, GSmsgGetGSchar(itemDB_GetName(id)));
    fightFloorBiosSetAppointItemDataId(floor, id);
}

void fightFloor_SetAppointPokemonWazaDataId(FIGHT_FLOOR* floor, u16 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetAppointWazaDataId(floor, value);
}

void fightFloor_SetAppointPokemonDataId(FIGHT_FLOOR* floor, u16 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetAppointPokemonDataId(floor, value);
}

void fightFloor_SetWazakoukaMsgId(FIGHT_FLOOR* floor, u32 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetWazakoukaMsgId(floor, value);
}

void fightFloor_SetCriticakMsgId(FIGHT_FLOOR* floor, u32 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetCriticalMsgId(floor, value);
}

void fightFloor_SetAttackMsgId(FIGHT_FLOOR* floor, u32 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetAttackMsgId(floor, value);
}

void fightFloor_SetAppointMsgPtr(FIGHT_FLOOR* floor, u32 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetAppointMsgId(floor, value);
}

void fightFloor_SetAppointPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    if (pokemon != 0) {
        if (fightOutPokemonCheckValid(pokemon) == 1) {
            fightMsgctrlSetValue(0x1E, (u32)pokemon);
            fightMsgctrlSetValue(0x1C, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(pokemon)))));
        } else {
            fightMsgctrlSetValue(0x1E, 0);
            fightMsgctrlSetValue(0x1C, 0);
        }
    } else {
        fightMsgctrlSetValue(0x1E, 0);
        fightMsgctrlSetValue(0x1C, 0);
    }
    fightFloorBiosSetAppointPokemonPtr(floor, pokemon);
}

void fightFloor_SetEncountFloorId(FIGHT_FLOOR* floor, u32 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetEncountFloorId(value);
}

void fightFloor_SetItemPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    if (pokemon != 0 && fightOutPokemonCheckValid(pokemon) == 1) {
        u16 item = fightOutPokemonGetSoubiItemDataId(pokemon);
        fightFloor_SetAppointItemDataId(floor, item);
    }
    fightFloorBiosSetItemPokemonPtr(floor, pokemon);
}

void fightFloor_SetTokuseiPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetTokuseiPokemonPtr(floor, value);
}

void fightFloor_SetTuikakoukaPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    if (pokemon != 0) {
        if (fightOutPokemonCheckValid(pokemon) == 1) {
            fightMsgctrlSetValue(0x12, (u32)pokemon);
            fightMsgctrlSetValue(0x1D, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(pokemon)))));
        } else {
            fightMsgctrlSetValue(0x12, 0);
            fightMsgctrlSetValue(0x1D, 0);
        }
    } else {
        fightMsgctrlSetValue(0x12, 0);
        fightMsgctrlSetValue(0x1D, 0);
    }
    fightFloorBiosSetTuikakoukaPokemonPtr(floor, pokemon);
}

void fightFloor_SetKizetuPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetKizetuPokemonPtr(floor, value);
}

void fightFloor_SetIrekaePokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetIrekaePokemonPtr(floor, value);
}

void fightFloor_SetEscapePokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetEscapePokemonPtr(floor, value);
}

void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    u8 fightType = fightFloor_GetFightType(floor);

    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloor_SetDefensePokemonPtr(floor, pokemon);
    u16 target = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(pokemon, fightType);
    fightFloor_SetAttackPokemonFightWazaTargetId(floor, target);
}

void fightFloor_SetDefensePokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    if (pokemon != 0) {
        if (fightOutPokemonCheckValid(pokemon) == 1) {
            fightMsgctrlSetValue(0x10, (u32)pokemon);
            fightMsgctrlSetValue(0x1B, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(pokemon)))));
            fightMsgctrlSetValue(0x42, (u32)pokemon);
            fightMsgctrlSetValue(0x44, (u32)pokemon);
            fightMsgctrlSetValue(0x43, (u32)pokemon);
        } else {
            fightMsgctrlSetValue(0x10, 0);
            fightMsgctrlSetValue(0x1B, 0);
            fightMsgctrlSetValue(0x42, 0);
            fightMsgctrlSetValue(0x44, 0);
            fightMsgctrlSetValue(0x43, 0);
        }
    } else {
        fightMsgctrlSetValue(0x10, 0);
        fightMsgctrlSetValue(0x1B, 0);
        fightMsgctrlSetValue(0x42, 0);
        fightMsgctrlSetValue(0x44, 0);
        fightMsgctrlSetValue(0x43, 0);
    }
    fightFloorBiosSetDefensePokemonPtr(floor, pokemon);
}

void fightFloor_SetAttackPokemonFightWazaTargetId(FIGHT_FLOOR* floor, u16 id) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightOutPokemon_SetWazaTargetId(fightFloorBiosGetAttackPokemonPtr(floor), id);
}

void fightFloor_SetAttackPokemonFightWazaJoutaiDataId(FIGHT_FLOOR* floor, u16 id) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightOutPokemon_SetWazaJoutaiDataId(fightFloorBiosGetAttackPokemonPtr(floor), id);
}

void fightFloor_SetAttackPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    if (pokemon != 0) {
        if (fightOutPokemonCheckValid(pokemon) == 1) {
            fightMsgctrlSetValue(0xF, (u32)pokemon);
            fightMsgctrlSetValue(0x1A, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(pokemon)))));
            fightMsgctrlSetValue(0x1F, (u32)pokemon);
            fightMsgctrlSetValue(0x21, (u32)pokemon);
            fightMsgctrlSetValue(0x20, (u32)pokemon);
        } else {
            fightMsgctrlSetValue(0xF, 0);
            fightMsgctrlSetValue(0x1A, 0);
            fightMsgctrlSetValue(0x1F, 0);
            fightMsgctrlSetValue(0x21, 0);
            fightMsgctrlSetValue(0x20, 0);
        }
    } else {
        fightMsgctrlSetValue(0xF, 0);
        fightMsgctrlSetValue(0x1A, 0);
        fightMsgctrlSetValue(0x1F, 0);
        fightMsgctrlSetValue(0x21, 0);
        fightMsgctrlSetValue(0x20, 0);
    }
    fightFloorBiosSetAttackPokemonPtr(floor, pokemon);
}

void fightFloor_SetEncountDataId(FIGHT_FLOOR* floor, u16 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetEncountDataId(floor, value);
}

void fightFloor_SetTurnCount(FIGHT_FLOOR* floor, u16 value) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
    }
    fightFloorBiosSetTurnCount(floor, value);
}

u32 fightFloor_GetEncountFloorId(FIGHT_FLOOR* floor) {
    return fightFloorBiosGetEncountFloorId();
}

FIGHT_SIDE* fightFloor_GetFightSidePtr(FIGHT_FLOOR* floor, u16 index) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    if (index >= 2) {
        return 0;
    }
    return &floor->sides[index];
}

u8 fightFloor_GetFightKindRegulationFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetRegulationFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindHostEnemyMsgFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetHostEnemyMsgFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindPokemonStatusMenuSubbarFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetPokemonStatusMenuSubbarFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindDarkpokemonHypermodeFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetDarkpokemonHypermodeFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindMonohiroiFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetMonohiroiFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindDorobouFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetDorobouFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindBossFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetBossFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindKeikentihueruFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetKeikentihueruFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindDoItemSoubiTokukoutokubouupFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetDoItemSoubiTokukoutokubouupFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindDoHizukiMiyaburiFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetDoHizukiMiyaburiFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindDoCriticalAttackFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetDoCriticalAttackFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindGetInfectPokerusFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetGetInfectPokerusFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindGetFriendFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetGetFriendFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindGetNekoniKobanFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetGetNekoniKobanFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindGetOkaneFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetGetOkaneFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindOkanePoolFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetOkanePoolFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindGetExpFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetGetExpFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindDrawFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetDrawFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindNigeruFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetNigeruFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindUseItemFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetUseItemFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindDoZukanTukamaetaFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetDoZukanTukamaetaFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindDoZukanMitaFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetDoZukanMitaFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindDoBadgeCheckFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetDoBadgeCheckFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u8 fightFloor_GetFightKindBackSaveDataFlag(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightKindDataBiosGetBackSaveDataFlag(fightKindDataBiosGetPtr((u8)fightFloor_GetFightKind(floor)));
}

u16 fightFloor_GetFightSideFightOutPokemonSideMax(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightTypeGetFightSideFightOutPokemonMax(fightFloor_GetFightType(floor));
}

u8 fightFloor_GetFightTypeFightoutPokemonNum(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr((u8)fightFloor_GetFightType(floor)));
}

u8 fightFloor_GetFightTypeEntryPokemonNum(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightTypeDataBiosGetEntryPokemonNum(fightTypeDataBiosGetPtr((u8)fightFloor_GetFightType(floor)));
}

u8 fightFloor_GetFightTypeTrainerNum(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightTypeDataBiosGetTrainerNum(fightTypeDataBiosGetPtr((u8)fightFloor_GetFightType(floor)));
}

u32 fightFloor_GetEnvSndId(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightEncountGetEnvSndDataId(fightFloor_GetEncountDataId(floor));
}

u32 fightFloor_GetBgmSndId(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightFloorGetBgmSndDataId(floor);
}

u32 fightFloor_GetSyoukaiWzxDataId(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightFloorDB_GetSyoukaiWzxDataId(fightFloor_GetFightFloorDataId(floor));
}

u8 fightFloor_GetTikeiDataId(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightFloorDB_GetTikeiDataId(fightFloor_GetFightFloorDataId(floor));
}

u16 fightFloor_GetFightFloorDataId(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightEncountDataBiosGetFightFloorDataId(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
}

u32 fightFloor_GetTrainer(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightEncountDataBiosGetTrainer(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
}

s32 fightFloor_GetFightType(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightEncountDataBiosGetFightType(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
}

s32 fightFloor_GetFightKind(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
}

u16 fightFloor_GetFirstAttackRnd(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->firstAttackRnd;
}

FightOutPokemon** fightFloor_GetFightOutPokemonPtrAryPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->fightOutPokemon;
}

FightOutPokemon* fightFloor_GetFightOutPokemonPtrAry(FIGHT_FLOOR* floor, u16 index) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    if (index >= 8) {
        return 0;
    }
    return floor->fightOutPokemon[index];
}

s16 fightFloor_GetFightPokemonEntryCnt(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->fightPokemonEntryCnt;
}

u32 fightFloor_GetAppointMsgId(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->appointMsgId;
}

void* fightFloor_GetAppointItemPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->appointItem;
}

void* fightFloor_GetAppointSidePtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->appointSide;
}

void* fightFloor_GetAppointWazaPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->appointWaza;
}

void* fightFloor_GetAppointTrainerPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->appointTrainer;
}

FightOutPokemon* fightFloor_GetAppointPokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->appointPokemon;
}

FightOutPokemon* fightFloor_GetItemPokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->itemPokemon;
}

FightOutPokemon* fightFloor_GetTokuseiPokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->tokuseiPokemon;
}

FightOutPokemon* fightFloor_GetTuikakoukaPokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->tuikakoukaPokemon;
}

FightOutPokemon* fightFloor_GetKizetuPokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->kizetuPokemon;
}

FightOutPokemon* fightFloor_GetIrekaePokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->irekaePokemon;
}

FightOutPokemon* fightFloor_GetEscapePokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->escapePokemon;
}

FightOutPokemon* fightFloor_GetDefensePokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->defensePokemon;
}

FightOutPokemon* fightFloor_GetAttackPokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->attackPokemon;
}

u16 fightFloor_GetEncountDataId(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->encountDataId;
}

u16 fightFloor_GetTurnCount(FIGHT_FLOOR* floor) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return floor->getTurnCount();
}

u8 fightFloor_GetIsJoutaiDataId(FIGHT_FLOOR* floor, u16 id) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    return fightFloorIsJoutaiDataId((FightJoutai*)floor, id);
}

FightJoutai* fightFloor_GetJoutaiPtr(FIGHT_FLOOR* floor, u16 index) {
    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    if (index >= 1) {
        return 0;
    }
    return &floor->joutai[index];
}

u32 fightFloorDB_GetEnvSndId(u16 id) {
    FightFloorData* data = fightFloorDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->envSndId;
}

u32 fightFloorDB_GetBgmSndId(u16 id) {
    FightFloorData* data = fightFloorDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->bgmSndId;
}

u32 fightFloorDB_GetSyoukaiWzxDataId(u16 id) {
    FightFloorData* data = fightFloorDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->syoukaiWzxDataId;
}

u8 fightFloorDB_GetTikeiDataId(u16 id) {
    FightFloorData* data = fightFloorDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->tikeiDataId;
}

u16 fightFloorDB_GetFightSideDataId(u16 id, u8 index) {
    FightFloorData* data = fightFloorDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return data->fightSideDataId[index];
}

u16 fightFloorDB_GetFloorDataId(u16 id) {
    FightFloorData* data = fightFloorDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->floorDataId;
}

}
