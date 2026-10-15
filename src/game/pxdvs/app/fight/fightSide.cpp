// STATUS: 24/24 exact, LAYOUT+CONST OK with extra_cflags=["-O4,s"] (needs configure.py flag; link it).
#include <dolphin/types.h>

class FIGHT_SIDE {
public:
    u8 data[0x6EF0];
};
struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightPokemon;
struct Pokemon;
struct FightJoutai;

extern "C" {
u16 joutaiDataBiosGetStatus(u16);
u8 joutaiGetUserFightTargetId(FIGHT_SIDE*, u16);
void joutaiSetNowKaisuuJoutaiDataId(FIGHT_SIDE*, u16, u16);
s32 joutaiGetNowKaisuuJoutaiDataId(FIGHT_SIDE*, u16);
s32 joutaiGetKaisuuJoutaiDataId(FIGHT_SIDE*, u16);
s32 joutaiGetCountAsJoutaiDataId(FIGHT_SIDE*, u16);
void joutaiWriteJoutaiDataId(FIGHT_SIDE*, u16, u16);
u8 joutaiCheckWriteJoutaiDataId(FIGHT_SIDE*, u16);
u8 joutaiIsJoutaiDataId(FIGHT_SIDE*, u16);
void joutaiInitJoutaiDataId(FIGHT_SIDE*, u16);
void joutaiInitAry(FightJoutai*, u16);

FIGHT_TRAINER* fightSide_GetFightTrainerPtr(FIGHT_SIDE*, u16);
FightJoutai* fightSide_GetJoutaiPtr(FIGHT_SIDE*, u16);
u16 fightSide_GetFightSideDataId(FIGHT_SIDE*);
void fightSide_SetFightSideDataId(FIGHT_SIDE*, u16);
void fightSide_SetMakibisiCheckFlag(FIGHT_SIDE*, u8);
u8 fightSide_GetMakibisiCheckFlag(FIGHT_SIDE*);
u16 fightGetFightResultId(void);

u8 fightTrainerCheckValid(FIGHT_TRAINER*);
u8 fightTrainerCheckDoFight(FIGHT_TRAINER*);
void fightTrainerInitAry(FIGHT_TRAINER*, u16);
FightOutPokemon* fightTrainer_GetFightoutPokemonPtr(FIGHT_TRAINER*, u16);
void fightTrainer_SetEnemyPokemonRegist(FIGHT_TRAINER*, s16);
u32 fightTrainerGetHikaeFightPokemonNum(FIGHT_TRAINER*, u16, u16);
FightPokemon* fightTrainerGetValidFightPokemonPtr(FIGHT_TRAINER*, u16);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
s16 fightPokemon_GetEntryId(FightPokemon*);
u8 fightPokemonCheckFightOut(FightPokemon*);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
u16 pokemon_GetMaxHp(Pokemon*);
u16 pokemon_GetHp(Pokemon*);

u16 fightSideDB_GetYrot(FIGHT_SIDE*);
FIGHT_SIDE* fightSideDataBiosGetPtr(u32);
void fightSideDataBiosSetYrot(FIGHT_SIDE*, u16);
void fightSideDataBiosSetFightTrainerStatusMenuDataId(FIGHT_SIDE*, u8, u32);
void fightSideDataBiosSetFightoutPokemonStatusMenuDataId(FIGHT_SIDE*, u8, u32);
u16 fightSideDataBiosGetYrot(FIGHT_SIDE*);
s32 fightSideDataBiosGetFightTrainerStatusMenuDataId(FIGHT_SIDE*, u8);
s32 fightSideDataBiosGetFightoutPokemonStatusMenuDataId(FIGHT_SIDE*, u8);
void fightSideBiosSetFightSideDataId(FIGHT_SIDE*, u16);
void fightSideBiosSetMakibisiCheckFlag(FIGHT_SIDE*, u8);
u16 fightSideBiosGetFightSideDataId(FIGHT_SIDE*);
FightJoutai* fightSideBiosGetJoutaiPtr(FIGHT_SIDE*, u32);
FIGHT_TRAINER* fightSideBiosGetFightTrainerPtr(FIGHT_SIDE*, u32);
u8 fightSideBiosGetMakibisiCheckFlag(FIGHT_SIDE*);

void fightSideInit(FIGHT_SIDE*);
u32 fightSideGetFightPokemonNum(FIGHT_SIDE*, u16, u16, u8);

void fightSideRegistFightSideEnemyPokemonFightAll(FIGHT_SIDE* side, FIGHT_TRAINER* enemy, u8 unused, u16 trainerNum,
                                                  u16 pokemonNum) {
    FIGHT_TRAINER* trainer;
    FightOutPokemon* out;
    u16 i;
    u16 j;
    for (i = 0; i < trainerNum; i++) {
        trainer = fightSide_GetFightTrainerPtr(side, i);
        if (fightTrainerCheckValid(trainer)) {
            for (j = 0; j < pokemonNum; j++) {
                out = fightTrainer_GetFightoutPokemonPtr(trainer, j);
                if (fightOutPokemonCheckFightOut(out)) {
                    s16 id = fightPokemon_GetEntryId(fightOutPokemon_GetMotoFightPokemonPtr(out));
                    if (id >= 0) {
                        fightTrainer_SetEnemyPokemonRegist(enemy, id);
                    }
                }
            }
        }
    }
}

u8 fightSideGetJoutaiUserFightTargetId(FIGHT_SIDE* side, u16 id) {
    if (joutaiDataBiosGetStatus(id) != 6) {
        return 0;
    }
    return joutaiGetUserFightTargetId(side, id);
}

void fightSideSetNowKaisuuJoutaiDataId(FIGHT_SIDE* side, u16 id, u16 value) {
    if (joutaiDataBiosGetStatus(id) == 6) {
        joutaiSetNowKaisuuJoutaiDataId(side, id, value);
    }
}

s32 fightSideGetNowKaisuuJoutaiDataId(FIGHT_SIDE* side, u16 id) {
    if (joutaiDataBiosGetStatus(id) != 6) {
        return -1;
    }
    return joutaiGetNowKaisuuJoutaiDataId(side, id);
}

s32 fightSideGetKaisuuJoutaiDataId(FIGHT_SIDE* side, u16 id) {
    if (joutaiDataBiosGetStatus(id) != 6) {
        return -1;
    }
    return joutaiGetKaisuuJoutaiDataId(side, id);
}

s32 fightSideGetCountAsJoutaiDataId(FIGHT_SIDE* side, u16 id) {
    if (joutaiDataBiosGetStatus(id) != 6) {
        return -1;
    }
    return joutaiGetCountAsJoutaiDataId(side, id);
}

void fightSideWriteJoutaiDataId(FIGHT_SIDE* side, u16 id, u16 value) {
    if (joutaiDataBiosGetStatus(id) == 6) {
        joutaiWriteJoutaiDataId(side, id, value);
    }
}

u8 fightSideCheckWriteJoutaiDataId(FIGHT_SIDE* side, u16 id) {
    if (joutaiDataBiosGetStatus(id) != 6) {
        return 0;
    }
    return joutaiCheckWriteJoutaiDataId(side, id);
}

u8 fightSideIsJoutaiDataId(FIGHT_SIDE* side, u16 id) {
    if (joutaiDataBiosGetStatus(id) != 6) {
        return 0;
    }
    return joutaiIsJoutaiDataId(side, id);
}

void fightSideInitJoutaiDataId(FIGHT_SIDE* side, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 6) {
        joutaiInitJoutaiDataId(side, id);
    }
}

u32 fightSideGetHikaeFightPokemonNum(FIGHT_SIDE* side, u16 trainerNum, u16 a, u16 b) {
    FIGHT_TRAINER* trainer;
    u16 i;
    u32 total = 0;
    for (i = 0; i < trainerNum; i++) {
        trainer = fightSide_GetFightTrainerPtr(side, i);
        if (fightTrainerCheckValid(trainer)) {
            total += fightTrainerGetHikaeFightPokemonNum(trainer, a, b);
        }
    }
    return total;
}

u32 fightSideGetNokoriFightPokemonNum(FIGHT_SIDE* side, u16 trainerNum, u16 pokemonNum) {
    return fightSideGetFightPokemonNum(side, trainerNum, pokemonNum, 1);
}

u32 fightSideGetFightPokemonNum(FIGHT_SIDE* side, u16 trainerNum, u16 pokemonNum, u8 checkFightOut) {
    FIGHT_TRAINER* trainer;
    FightPokemon* fp;
    u16 i;
    u16 j;
    u32 total = 0;
    for (i = 0; i < trainerNum; i++) {
        trainer = fightSide_GetFightTrainerPtr(side, i);
        if (fightTrainerCheckValid(trainer)) {
            for (j = 0; j < pokemonNum; j++) {
                fp = fightTrainerGetValidFightPokemonPtr(trainer, j);
                if (fp) {
                    if (checkFightOut == 1 && !fightPokemonCheckFightOut(fp)) {
                        continue;
                    }
                    total++;
                }
            }
        }
    }
    return total;
}

u32 fightSideGetFightPokemonMaxHp(FIGHT_SIDE* side, u16 trainerNum, u16 pokemonNum) {
    FIGHT_TRAINER* trainer;
    FightPokemon* fp;
    Pokemon* p;
    u16 i;
    u16 j;
    u32 total = 0;
    for (i = 0; i < trainerNum; i++) {
        trainer = fightSide_GetFightTrainerPtr(side, i);
        if (fightTrainerCheckValid(trainer)) {
            for (j = 0; j < pokemonNum; j++) {
                fp = fightTrainerGetValidFightPokemonPtr(trainer, j);
                if (fp) {
                    p = fightPokemonGetPokemonPtr(fp);
                    if (p && fightPokemonCheckFightOut(fp)) {
                        total += pokemon_GetMaxHp(p);
                    }
                }
            }
        }
    }
    return total;
}

u32 fightSideGetFightPokemonNokoriHp(FIGHT_SIDE* side, u16 trainerNum, u16 pokemonNum) {
    FIGHT_TRAINER* trainer;
    FightPokemon* fp;
    Pokemon* p;
    u16 i;
    u16 j;
    u32 total = 0;
    for (i = 0; i < trainerNum; i++) {
        trainer = fightSide_GetFightTrainerPtr(side, i);
        if (fightTrainerCheckValid(trainer)) {
            for (j = 0; j < pokemonNum; j++) {
                fp = fightTrainerGetValidFightPokemonPtr(trainer, j);
                if (fp) {
                    p = fightPokemonGetPokemonPtr(fp);
                    if (p && fightPokemonCheckFightOut(fp)) {
                        total += pokemon_GetHp(p);
                    }
                }
            }
        }
    }
    return total;
}

FIGHT_TRAINER* fightSideGetValidFightTrainerPtr(FIGHT_SIDE* side, u16 idx) {
    FIGHT_TRAINER* trainer = fightSide_GetFightTrainerPtr(side, idx);
    return !fightTrainerCheckValid(trainer) ? 0 : trainer;
}

void fightSideGetFightTrainerGridParam(FIGHT_SIDE* side, u16 mode, u16 pos, u8* outA, s8* outB) {
    if (outA == 0) {
        return;
    }
    if (outB == 0) {
        return;
    }
    *outA = fightSideDB_GetYrot(side) != 0;
    *outB = 0;
    if (mode == 1) {
        return;
    }
    if (mode != 2) {
        return;
    }
    if (*outA == 1) {
        if (pos == 0) {
            *outB = 1;
        } else if (pos == 1) {
            *outB = -1;
        } else {
            return;
        }
    } else {
        if (pos == 0) {
            *outB = -1;
        } else if (pos == 1) {
            *outB = 1;
        }
    }
}

u32 fightSideGetDoFightTrainerCount(FIGHT_SIDE* side) {
    u8 i;
    int count = 0;
    for (i = 0; i < 2; i++) {
        if (fightTrainerCheckDoFight(fightSide_GetFightTrainerPtr(side, i))) {
            count++;
        }
    }
    return count;
}

bool fightSideCheckValid(FIGHT_SIDE* side) {
    if (!side) {
        return 0;
    }
    if (fightGetFightResultId() == 1) {
        return 0;
    }
    return fightSide_GetFightSideDataId(side) != 0;
}

void fightSideCreate(FIGHT_SIDE* side, u16 id) {
    if (side) {
        fightSideInit(side);
        fightSide_SetFightSideDataId(side, id);
    }
}

void fightSideInitAry(FIGHT_SIDE* side, u16 num) {
    if (side) {
        u16 i;
        for (i = 0; i < num; i++) {
            fightSideInit(side + i);
        }
    }
}

void fightSideInit(FIGHT_SIDE* side) {
    if (side) {
        fightSide_SetFightSideDataId(side, 0);
        joutaiInitAry(fightSide_GetJoutaiPtr(side, 0), 6);
        fightTrainerInitAry(fightSide_GetFightTrainerPtr(side, 0), 2);
        fightSide_SetMakibisiCheckFlag(side, 0);
    }
}

void fightSideSetStatus(FIGHT_SIDE* side, FIGHT_SIDE* dataIdx, u16 kind, u32 param, u32 value) {
    if (kind == 0 || kind >= 10) {
        return;
    }
    if (kind < 4) {
        side = fightSideDataBiosGetPtr((u32)dataIdx);
    }
    if (!side) {
        return;
    }
    switch (kind) {
    case 1:
        fightSideDataBiosSetYrot(side, value);
        break;
    case 2:
        fightSideDataBiosSetFightTrainerStatusMenuDataId(side, param, value);
        break;
    case 3:
        fightSideDataBiosSetFightoutPokemonStatusMenuDataId(side, param, value);
        break;
    case 5:
        fightSideBiosSetFightSideDataId(side, value);
        break;
    case 8:
        fightSideBiosSetMakibisiCheckFlag(side, value != 0);
        break;
    }
}

s32 fightSideGetStatus(FIGHT_SIDE* side, FIGHT_SIDE* dataIdx, u16 kind, u32 param) {
    if (kind == 0 || kind >= 10) {
        return 0;
    }
    if (kind < 4) {
        side = fightSideDataBiosGetPtr((u32)dataIdx);
    }
    if (!side) {
        return 0;
    }
    switch (kind) {
    case 1:
        return fightSideDataBiosGetYrot(side);
    case 2:
        return fightSideDataBiosGetFightTrainerStatusMenuDataId(side, param);
    case 3:
        return fightSideDataBiosGetFightoutPokemonStatusMenuDataId(side, param);
    case 5:
        return fightSideBiosGetFightSideDataId(side);
    case 6:
        return (s32)fightSideBiosGetJoutaiPtr(side, param);
    case 7:
        return (s32)fightSideBiosGetFightTrainerPtr(side, param);
    case 8:
        return fightSideBiosGetMakibisiCheckFlag(side);
    default:
        return 0;
    }
}
}
