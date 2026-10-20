// Trainer AI: waza (move) selection, move/defender scoring and the damage/hit/value dispatchers.
#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FIGHT_SIDE;
struct FightActionData;
struct Pokemon;
struct FightOutPokemon {
    u32 data[548];
};

typedef s32 (*FightWazaDamageFunc)(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
typedef u8 (*FightWazaHitFunc)(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
typedef s32 (*FightWazaValueFunc)(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);

extern "C" {
u16 HSD_Rand();
u8 dbgMenuFightGetFightTrainerAiLastValueReviseFlag();
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
u16 fightTrainerDB_GetAiDataId(u16);
u8 fightAi_FixedActCheck(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
u16 fightAi_GetWazaDataIDFromFixActWaza(FIGHT_TRAINER*, FightOutPokemon*, u8);
FightOutPokemon* fightAi_GetWazaDataIDFromFixActDef(FIGHT_TRAINER*, FightOutPokemon*, u8);
s16 fightAi_ThreatEnemyValue(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon*, s16, u8, s8, s8);
FIGHT_TRAINER* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*, FightOutPokemon*);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void*, FIGHT_TRAINER*, FightOutPokemon**, u8, u8);
u16 fightFloorGetValidFightOutPokemonCount(void*, u8, FightOutPokemon*, u8);
u8 fightFloor_GetFightTypeEntryPokemonNum(void*);
u8 fightFloor_GetFightTypeFightoutPokemonNum(void*);
u8 fightFloor_GetFightTypeTrainerNum(void*);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
void fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon*, u8, u8, u8, FightActionData*, u32, u32, s8, u32);
s16 fightOutPokemonGetFightEntryId(FightOutPokemon*);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u8 fightOutPokemon_GetFixAiDef(FightOutPokemon*);
u8 fightOutPokemon_GetFixAiWaza(FightOutPokemon*);
void fightOutPokemon_SetFixAiWaza(FightOutPokemon*, u8);
FightOutPokemon* fightSeqSelectDefensePokemonPtr(FightOutPokemon*, u16, u16, FightOutPokemon* (*)(), u8, u8, s32);
u32 fightSideGetHikaeFightPokemonNum(FIGHT_SIDE*, u8, u8, u8);
FightOutPokemon* fightTargetGetPtr(u16, FightOutPokemon*, u16);
FIGHT_SIDE* fightTargetGetPtrAsNowFightType(u16, FIGHT_TRAINER*);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u16);
s32 fightTrainerAiAddValue(s32, s32);
s32 fightTrainerAiAddValueByAddsubDataId(s32, FIGHT_TRAINER*, u16);
u8 fightTrainerAiCheckHaveFightOutPokemonWazaDataId(FIGHT_TRAINER*, FightOutPokemon*, u16, s16*, u8);
u8 fightTrainerAiDB_GetDefensePokemonRndSelectFlag(u16);
u8 fightTrainerAiDB_GetLastValueRevise(u16);
u8 fightTrainerAiDB_GetWazaDamageFlag(u16);
u8 fightTrainerAiDB_GetWazaHitFlag(u16);
u8 fightTrainerAiDB_GetWazaInitValueFlag(u16);
u8 fightTrainerAiDB_GetWazaRndSelectFlag(u16);
u8 fightTrainerAiDB_GetWazaTypeReviseTypeDataId(u16, u8);
s32 fightTrainerAiDB_GetWazaTypeReviseValue(u16, u8);
s32 fightTrainerAiDB_GetZokuseiReviseValue(u16, u8);
u8 fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(u16, u8);
u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonPartDataId(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonWazaDataId(FIGHT_TRAINER*, FightOutPokemon*, u8);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER*, FightOutPokemon*, u16*, s16*, u8);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16, s16);
s32 fightTrainerAiGetValueAryMaxBanme(s32*, u16, u8);
u8 fightTrainerAiGetWazaAvg(FIGHT_TRAINER*, u16);
s16 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER*, u16);
u8 fightTrainerAiGetWazaRangeId(FIGHT_TRAINER*, u16);
u8 fightTrainerAiGetWazaRiskFlag(FIGHT_TRAINER*, u16);
u8 fightTrainerAiGetWazaTypeId(FIGHT_TRAINER*, u16, u8);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER*, u16, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonNokoriWazaPpHikui(FIGHT_TRAINER*, FightOutPokemon*, u8);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsWazaAvgTakai(FIGHT_TRAINER*, u16);
u8 fightTrainerAiIsWazaTypeId(FIGHT_TRAINER*, u16, u8);
s32 fightTrainerAiReviseValueByAddsubDataId(s32, s32, FIGHT_TRAINER*, u16);
s32 fightTrainerAiWazaDamageNull(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaDamageFightPokemonNull(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
u8 fightTrainerAiWazaHitNull(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueNull(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueToriaezutukae(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
u8 fightTrainerPokemonPartDB_GetWazaTypeRevise(u16, u8);
void pokemonGetMezamerupower(Pokemon*, u16*, u16*);
u8 wazaDB_GetBouon(u16);
void* wazaDB_GetFightTrainerAiWazaDamageFightPokemonFuncPtr(u16);
void* wazaDB_GetFightTrainerAiWazaDamageFuncPtr(u16);
void* wazaDB_GetFightTrainerAiWazaHitFuncPtr(u16);
void* wazaDB_GetFightTrainerAiWazaValueFuncPtr(u16);
u8 wazaDB_GetRangeId(u16);
extern FightActionData fight_action_data_waza;

FightOutPokemon* fightTrainerAiWazaSelectDefensePokemon();
s32 fightTrainerAiWazaDoWazaDamageFightPokemonFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*, u8);
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*, u8);
u8 fightTrainerAiWazaDoWazaHitFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaDoWazaValueFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
}

static s32 _fightTrainerAiWazaSubWaza(FIGHT_TRAINER*, FightOutPokemon*, u16, u16*, s16*, FightOutPokemon*, u16);
static s32 _fightTrainerAiWazaSubDefensePokemon(FIGHT_TRAINER*, FightOutPokemon*, u16, u16*, u16, FightOutPokemon**, FightOutPokemon**, s16*);
static u8 _fightTrainerAiWazaDoWazaHitFuncPre(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);

extern "C" {

s32 fightTrainerAiSelectFightActionWaza(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, u16 targetType) {
    u16 wazaId[8];
    FightOutPokemon* defender;
    FightOutPokemon* party[8];
    FightOutPokemon* defTarget;
    s16 defSlot;
    u16 aiId;
    u16 partyCount;
    u16 wazaCount;
    u8 fixWaza;
    u8 fixDef;
    u16 fixWazaId;
    FightOutPokemon* fixTarget;
    s16 wazaSlot[8];
    u16 waza;
    s32 slot;
    s32 pick;

    aiId = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    fixWaza = fightOutPokemon_GetFixAiWaza(pokemon);
    fixDef = fightOutPokemon_GetFixAiDef(pokemon);
    fixWazaId = fightAi_GetWazaDataIDFromFixActWaza(trainer, pokemon, fixWaza);
    fixTarget = fightAi_GetWazaDataIDFromFixActDef(trainer, pokemon, fixDef);
    wazaCount = fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer, pokemon, wazaId, wazaSlot, 1);
    if (wazaCount == 0) {
        return 0;
    }
    partyCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, party, 0, 1);
    if (partyCount == 0) {
        return 0;
    }
    if (fixWaza != 6 && fixWazaId != 0 && fixWazaId != 0x176 && fixTarget != 0) {
        if (fightAi_FixedActCheck(trainer, pokemon, fixWazaId, fixTarget) == 1) {
            waza = fixWazaId;
            defender = fixTarget;
            slot = fixWaza - 1;
            goto attack;
        }
        fightOutPokemon_SetFixAiWaza(pokemon, 6);
        fixWaza = 6;
    }
    if (fightTrainerAiDB_GetDefensePokemonRndSelectFlag(aiId) == 1) {
        pick = HSD_Rand() % partyCount;
    } else {
        defTarget = 0;
        defSlot = -1;
        pick = _fightTrainerAiWazaSubDefensePokemon(trainer, pokemon, wazaCount, wazaId, partyCount, party, &defTarget, &defSlot);
    }
    if (pick < 0) {
        if (defTarget != 0 && defSlot >= 0) {
            u32 target = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(defTarget, targetType);
            waza = fightTrainerAiGetFightOutPokemonWazaDataId(trainer, pokemon, defSlot);
            if (waza != 0) {
                fightOutPokemonCreateFightActionAttackWaza(pokemon, 0, 0x13, 0, &fight_action_data_waza, (u16)waza, target, defSlot, 0);
                return 1;
            }
            return 0;
        }
        return 0;
    }
    defender = party[pick];
    if (defender == 0) {
        return 0;
    }
    if (fixWaza != 6) {
        if (fixWazaId != 0 && fixWazaId != 0x176 && fixTarget == 0) {
            fixTarget = defender;
            if (wazaDB_GetRangeId(fixWazaId) == 5) {
                fixTarget = pokemon;
            }
            if (fightAi_FixedActCheck(trainer, pokemon, fixWazaId, fixTarget) == 1) {
                waza = fixWazaId;
                defender = fixTarget;
                slot = fixWaza - 1;
                goto attack;
            }
            if (fixTarget == fightTargetGetPtr(8, pokemon, targetType)) {
                fightOutPokemon_SetFixAiWaza(pokemon, 6);
            } else {
                FightOutPokemon* alt = fightTargetGetPtr(0xE, fixTarget, targetType);
                if (alt != 0 && fightAi_FixedActCheck(trainer, pokemon, fixWazaId, alt) == 1) {
                    waza = fixWazaId;
                    defender = alt;
                    slot = fixWaza - 1;
                    goto attack;
                }
                fightOutPokemon_SetFixAiWaza(pokemon, 6);
            }
        }
        if ((fixWazaId == 0 || fixWazaId == 0x176) && fixTarget != 0) {
            defender = fixTarget;
        }
    }
    if (fightTrainerAiDB_GetWazaRndSelectFlag(aiId) == 1) {
        pick = HSD_Rand() % wazaCount;
    } else {
        pick = _fightTrainerAiWazaSubWaza(trainer, pokemon, wazaCount, wazaId, wazaSlot, defender, targetType);
    }
    if (pick < 0) {
        return 0;
    }
    waza = wazaId[pick];
    if (waza == 0) {
        return 0;
    }
    slot = wazaSlot[pick];
    if (slot < 0) {
        return 0;
    }
attack:
    {
        FightOutPokemon* sel = fightSeqSelectDefensePokemonPtr(pokemon, waza, targetType, fightTrainerAiWazaSelectDefensePokemon, 1, 0, -1);
        if (sel != 0) {
            defender = sel;
        }
    }
    if (defender == 0) {
        return 0;
    }
    fightOutPokemonCreateFightActionAttackWaza(pokemon, 0, 0x13, 0, &fight_action_data_waza, waza,
                                               fightTargetGetTragetPtrToRelativeHostSideFightTargetId(defender, targetType), slot, 0);
    return 1;
}

}

static s32 _fightTrainerAiWazaSubWaza(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, u16 count, u16* wazaId, s16* wazaSlot,
                                      FightOutPokemon* defender, u16 targetType) {
    s32 values[8];
    s32 damage[8];
    u16 aiId;
    s32 maxDamage;
    FIGHT_SIDE* side;
    int fightOutNum;
    int entryNum;
    int trainerNum;
    s32 remain[8];
    u8 revise;
    u8 partDataId;
    u16 i;
    u16 j;
    u16 k;
    u16 hp;
    s32 avg[8];
    s32 maxRemain;
    s32 maxAvg;
    u16 waza;
    u16 zokusei;
    u8 rangeId;
    FightWazaValueFunc valueFunc;
    s32 pick;
    u8 type;

    side = fightTargetGetPtrAsNowFightType(3, trainer);
    trainerNum = fightFloor_GetFightTypeTrainerNum(0);
    entryNum = fightFloor_GetFightTypeEntryPokemonNum(0);
    fightOutNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    aiId = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    revise = fightTrainerAiDB_GetLastValueRevise(aiId);
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    partDataId = fightTrainerAiGetFightOutPokemonPartDataId(trainer, pokemon);
    fightSideGetHikaeFightPokemonNum(side, trainerNum, entryNum, fightOutNum);
    for (i = 0; i < 8; i++) {
        values[i] = 0;
        damage[i] = 0;
        remain[i] = 0;
        avg[i] = 0;
    }
    hp = fightTrainerAiGetFightOutPokemonNowHp(trainer, defender);
    maxDamage = -0xFFFF;
    maxRemain = -0xFFFF;
    maxAvg = 0;
    for (i = 0; i < count; i++) {
        waza = wazaId[i];
        if (waza != 0 && waza != 0x176) {
            damage[i] = fightTrainerAiWazaDoWazaDamageFunc(trainer, pokemon, waza, defender, 0);
            remain[i] = hp - damage[i];
            if (fightTrainerAiIsWazaTypeId(trainer, waza, 1) == 1) {
                if (maxDamage < damage[i] && damage[i] != 0) {
                    maxDamage = damage[i];
                }
                if (remain[i] <= 0) {
                    if (maxRemain < remain[i]) {
                        maxRemain = remain[i];
                    }
                    avg[i] = fightTrainerAiGetWazaAvg(trainer, waza);
                    if (maxAvg < avg[i]) {
                        maxAvg = avg[i];
                    }
                }
            }
        }
    }
    for (u16 i = 0; i < count; i++) {
        waza = wazaId[i];
        if (waza == 0) {
            continue;
        }
        if (wazaSlot[i] < 0) {
            continue;
        }
        zokusei = fightTrainerAiGetWazaZokuseiDataId(trainer, waza, pokemon);
        rangeId = fightTrainerAiGetWazaRangeId(trainer, waza);
        valueFunc = (FightWazaValueFunc)wazaDB_GetFightTrainerAiWazaValueFuncPtr(waza);
        values[i] = fightTrainerAiWazaDoWazaValueFunc(trainer, pokemon, waza, defender);
        if (fightTrainerAiWazaDoWazaHitFunc(trainer, pokemon, waza, defender) == 1) {
            if (valueFunc == fightTrainerAiWazaValueToriaezutukae) {
                values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x3A);
            } else {
                values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x38);
            }
        } else {
            values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x39);
        }
        if (zokusei != 9 && fightTrainerAiIsWazaTypeId(trainer, waza, 1) == 1) {
            if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(trainer, defender, zokusei, fightTrainerAiGetWazaIryoku(trainer, waza)) == 0x42) {
                values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x3B);
            }
            if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(trainer, defender, zokusei, fightTrainerAiGetWazaIryoku(trainer, waza)) == 0x43) {
                values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x3C);
            }
        }
        for (j = 0; j < 3; j++) {
            type = fightTrainerAiGetWazaTypeId(trainer, waza, j);
            if (type != 0) {
                values[i] = fightTrainerAiReviseValueByAddsubDataId(values[i], fightTrainerPokemonPartDB_GetWazaTypeRevise(partDataId, type), trainer, 0x3D);
            }
        }
        if (zokusei != 9) {
            for (j = 0; j < 2; j++) {
                u32 revZokusei = fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(aiId, j);
                if (revZokusei != 9 && zokusei == revZokusei) {
                    s32 tmp1 = fightTrainerAiDB_GetZokuseiReviseValue(aiId, j);
                    values[i] = fightTrainerAiReviseValueByAddsubDataId(values[i], tmp1, trainer, 0x3E);
                }
            }
        }
        for (j = 0; j < 3; j++) {
            type = fightTrainerAiGetWazaTypeId(trainer, waza, j);
            if (type != 0) {
                for (k = 0; k < 2; k++) {
                    u8 revType = fightTrainerAiDB_GetWazaTypeReviseTypeDataId(aiId, k);
                    if (revType != 0 && type == revType) {
                        s32 tmp1 = fightTrainerAiDB_GetWazaTypeReviseValue(aiId, k);
                        values[i] = fightTrainerAiReviseValueByAddsubDataId(values[i], tmp1, trainer, 0x3F);
                    }
                }
            }
        }
        if (fightTrainerAiIsWazaTypeId(trainer, waza, 1) == 1) {
            if (maxDamage <= damage[i]) {
                values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x40);
            }
            s32 left = remain[i];
            if (left < 0) {
                values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x41);
            }
            if (left <= 0) {
                values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x42);
            }
            if (left <= 0 && maxAvg <= avg[i]) {
                values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x43);
            }
        }
        if (fightTrainerAiIsWazaTypeId(trainer, waza, 2) == 1 && fightTrainerAiIsFightOutPokemonNokoriHpHikui(trainer, pokemon) == 1) {
            values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x44);
        }
        if (fightTrainerAiIsWazaAvgTakai(trainer, waza) == 1) {
            values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x45);
        }
        if (rangeId == 4 && fightFloorGetValidFightOutPokemonCount(0, 1, defender, 1) >= 2) {
            values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x46);
        }
        if (fightTrainerAiIsFightOutPokemonNokoriWazaPpHikui(trainer, pokemon, wazaSlot[i]) == 1) {
            values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x47);
        }
        if (fightTrainerAiGetWazaRiskFlag(trainer, waza) == 1) {
            values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x48);
        }
        if (dbgMenuFightGetFightTrainerAiLastValueReviseFlag() == 1) {
            values[i] = fightTrainerAiAddValue(values[i], HSD_Rand() % (revise * 2 + 1) - revise);
        }
    }
    pick = fightTrainerAiGetValueAryMaxBanme(values, (u16)count, 1);
    if (pick < 0) {
        return -1;
    }
    return pick;
}

static s32 _fightTrainerAiWazaSubDefensePokemon(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, u16 wazaCount, u16* wazaId,
                                                u16 partyCount, FightOutPokemon** party, FightOutPokemon** outTarget, s16* outSlot) {
    u16 waza;
    s32 maxDamage[8];
    FightOutPokemon* enemies[8];
    s16 slots[6];
    u8 canKo[8];
    u8 hitAny[8];
    s16 slot;
    u16 mezamePower;
    u16 mezameType;
    u16 aiId;
    u8 revise;
    u8 fixWaza;
    u16 enemyCount;
    u16 i;
    u16 j;
    u8 flag;
    FightOutPokemon* enemy;
    s32 threat[8];

    aiId = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    revise = fightTrainerAiDB_GetLastValueRevise(aiId);
    u16 list1[11] = {0x34, 0x53, 0xAC, 0x35, 0x7E, 0x12B, 7, 0x13B, 0x133, 0xDD, 0xED};
    u16 list2[4] = {0x5C, 0x105, 0x4D, 0x8B};
    fixWaza = fightOutPokemon_GetFixAiWaza(pokemon);
    enemyCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, enemies, 1, 1);
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    if (fixWaza == 6) {
        for (u16 i = 0; i < enemyCount; i++) {
            enemy = enemies[i];
            if (enemy != 0 && fightOutPokemonCheckFightOut(enemy) != 0 && pokemon != enemy) {
                if (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, enemy, 0x12) == 1 &&
                    fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, enemy, 0x3A) == 0) {
                    u16 j;
                    s16 count = 0;
                    for (j = 0; j < 11; j++) {
                        waza = list1[j];
                        if ((waza != 0xED || (pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(pokemon), &mezamePower, &mezameType), mezameType == 0xA)) &&
                            fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer, pokemon, waza, &slot, 1) != 0 && slot >= 0) {
                            slots[count++] = slot;
                        }
                    }
                    if (count > 0) {
                        slot = slots[HSD_Rand() % count];
                        if (outTarget != 0) {
                            *outTarget = enemy;
                        }
                        if (outSlot != 0) {
                            *outSlot = slot;
                        }
                        return -1;
                    }
                }
                if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, enemy, 0x3E) == 1 ||
                     fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, enemy, 0x3F) == 1) &&
                    fightTrainerAiIsFightOutPokemonJoutaiNormal(trainer, enemy) == 1) {
                    s16 count = 0;
                    u16 j;
                    for (j = 0; j < 4; j++) {
                        if (fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer, pokemon, list2[j], &slot, 1) != 0 && slot >= 0) {
                            slots[count++] = slot;
                        }
                    }
                    if (count > 0) {
                        slot = slots[HSD_Rand() % count];
                        if (outTarget != 0) {
                            *outTarget = enemy;
                        }
                        if (outSlot != 0) {
                            *outSlot = slot;
                        }
                        return -1;
                    }
                }
                flag = 0;
                if (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, enemy, 0x36) == 1) {
                    flag = 1;
                }
                if (fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer, enemy) == 2 &&
                    (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, enemy, 0x25) == 1 ||
                     fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, enemy, 0x4A) == 1)) {
                    flag = 1;
                }
                if (fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer, enemy) == 3 &&
                    (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, pokemon, 0x25) == 1 ||
                     fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, pokemon, 0x4A) == 1)) {
                    flag = 1;
                }
                if (flag == 1 && fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer, pokemon, 0x11D, &slot, 1) != 0 && slot >= 0) {
                    if (outTarget != 0) {
                        *outTarget = enemy;
                    }
                    if (outSlot != 0) {
                        *outSlot = slot;
                    }
                    return -1;
                }
                flag = 0;
                if (fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer, enemy) == 0) {
                    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, enemy, 0x14) == 1) {
                        flag = 1;
                    }
                    waza = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(trainer, enemy);
                    if (waza == 8 || waza == 9) {
                        flag = 1;
                    }
                }
                if (flag == 1 && fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer, pokemon, 0xCF, &slot, 1) != 0 && slot >= 0) {
                    if (outTarget != 0) {
                        *outTarget = enemy;
                    }
                    if (outSlot != 0) {
                        *outSlot = slot;
                    }
                    return -1;
                }
                if (fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer, enemy) == 1 &&
                    fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer, pokemon) == 0 &&
                    fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer, pokemon, 0xF4, &slot, 1) != 0 && slot >= 0) {
                    if (outTarget != 0) {
                        *outTarget = enemy;
                    }
                    if (outSlot != 0) {
                        *outSlot = slot;
                    }
                    return -1;
                }
            }
        }
    }
    for (i = 0; i < 8; i++) {
        threat[i] = 0;
        maxDamage[i] = 0;
        hitAny[i] = 0;
        canKo[i] = 0;
    }
    {
        s32 best = 0;
        for (i = 0; i < partyCount; i++) {
            FightOutPokemon* target = party[i];
            if (target != 0 && fightOutPokemonGetFightEntryId(target) >= 0) {
                u16 hp = fightTrainerAiGetFightOutPokemonNowHp(trainer, target);
                s32 top = 0;
                for (j = 0; j < wazaCount; j++) {
                    waza = wazaId[j];
                    if (waza != 0 && waza != 0x176) {
                        u8 hit = fightTrainerAiWazaDoWazaHitFunc(trainer, pokemon, waza, target);
                        if (hit == 1) {
                            hitAny[i] = 1;
                        }
                        if (fightTrainerAiIsWazaTypeId(trainer, waza, 1) != 0) {
                            s32 dmg = fightTrainerAiWazaDoWazaDamageFunc(trainer, pokemon, waza, target, 1);
                            if (top < dmg) {
                                top = dmg;
                            }
                            if (hp < fightTrainerAiWazaDoWazaDamageFunc(trainer, pokemon, waza, target, 0) && hit == 1) {
                                canKo[i] = 1;
                            }
                        }
                    }
                }
                maxDamage[i] = top;
                if (best < maxDamage[i]) {
                    best = maxDamage[i];
                }
            }
        }
    }
    for (i = 0; i < partyCount; i++) {
        FightOutPokemon* target = party[i];
        if (target != 0 && fightOutPokemonGetFightEntryId(target) >= 0) {
            fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, target);
            threat[i] = fightAi_ThreatEnemyValue(trainer, pokemon, target, -1, 1, hitAny[i], canKo[i]);
            if (dbgMenuFightGetFightTrainerAiLastValueReviseFlag() == 1) {
                threat[i] = fightTrainerAiAddValue(threat[i], HSD_Rand() % (revise * 2 + 1) - revise);
            }
        }
    }
    s32 count = fightTrainerAiGetValueAryMaxBanme(threat, partyCount, 1);
    if (count < 0) {
        return -1;
    }
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, party[count]);
    return count;
}

extern "C" {

FightOutPokemon* fightTrainerAiWazaSelectDefensePokemon() {
    return 0;
}

s32 fightTrainerAiWazaDoWazaDamageFightPokemonFunc(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, u16 waza, FightOutPokemon* target, u8 dispatch) {
    FightOutPokemon* party[8];
    FightWazaDamageFunc func;
    u16 partyCount;
    u8 range;
    u16 i;
    s32 result;

    if (fightTrainerAiDB_GetWazaDamageFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer))) == 1) {
        func = (FightWazaDamageFunc)wazaDB_GetFightTrainerAiWazaDamageFightPokemonFuncPtr(waza);
        if (func == 0) {
            func = fightTrainerAiWazaDamageFightPokemonNull;
        }
    } else {
        return 0;
    }
    partyCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, party, 0, 1);
    range = wazaDB_GetRangeId(waza);
    result = 0;
    if (dispatch == 1) {
        switch (range) {
        case 0:
        case 3:
            result = func(trainer, pokemon, waza, target);
            break;
        case 2:
        case 4:
        case 6:
            for (i = 0; i < partyCount; i++) {
                result += func(trainer, pokemon, waza, target);
            }
            break;
        case 1:
        case 5:
        case 7:
            result = func(trainer, pokemon, waza, target);
            break;
        }
    } else {
        result = func(trainer, pokemon, waza, target);
    }
    return result;
}

s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, u16 waza, FightOutPokemon* target, u8 dispatch) {
    FightOutPokemon* party[8];
    FightWazaDamageFunc func;
    u16 partyCount;
    u8 range;
    u16 i;
    s32 result;

    if (fightTrainerAiDB_GetWazaDamageFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer))) == 1) {
        func = (FightWazaDamageFunc)wazaDB_GetFightTrainerAiWazaDamageFuncPtr(waza);
        if (func == 0) {
            func = fightTrainerAiWazaDamageNull;
        }
    } else {
        return 0;
    }
    partyCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, party, 0, 1);
    range = wazaDB_GetRangeId(waza);
    result = 0;
    if (dispatch == 1) {
        switch (range) {
        case 0:
        case 3:
            result = func(trainer, pokemon, waza, target);
            break;
        case 2:
        case 4:
        case 6:
            for (i = 0; i < partyCount; i++) {
                result += func(trainer, pokemon, waza, target);
            }
            break;
        case 1:
        case 5:
        case 7:
            result = func(trainer, pokemon, waza, target);
            break;
        }
    } else {
        result = func(trainer, pokemon, waza, target);
    }
    return result;
}

u8 fightTrainerAiWazaDoWazaHitFunc(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* party[8];
    FightWazaHitFunc func;
    u16 partyCount;
    u8 range;
    u8 result;
    u16 i;

    if (fightTrainerAiDB_GetWazaHitFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer))) == 1) {
        func = (FightWazaHitFunc)wazaDB_GetFightTrainerAiWazaHitFuncPtr(waza);
        if (func == 0) {
            func = fightTrainerAiWazaHitNull;
        }
    } else {
        return 1;
    }
    partyCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, party, 0, 1);
    range = wazaDB_GetRangeId(waza);
    result = 0;
    switch (range) {
    case 0:
    case 3:
        if (_fightTrainerAiWazaDoWazaHitFuncPre(trainer, pokemon, waza, target) == 0) {
            return 0;
        }
        return func(trainer, pokemon, waza, target);
    case 2:
    case 4:
    case 6:
        for (i = 0; i < partyCount; i++) {
            if (_fightTrainerAiWazaDoWazaHitFuncPre(trainer, pokemon, waza, target) == 0) {
                result = 0;
            } else {
                result = func(trainer, pokemon, waza, party[i]);
            }
            if (result == 1) {
                return result;
            }
        }
        return result;
    case 1:
    case 5:
    case 7:
        if (_fightTrainerAiWazaDoWazaHitFuncPre(trainer, pokemon, waza, target) == 0) {
            result = 0;
            break;
        }
        result = func(trainer, pokemon, waza, target);
        break;
    }
    return result;
}

}

static u8 _fightTrainerAiWazaDoWazaHitFuncPre(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, u16 waza, FightOutPokemon* target) {
    s16 power = fightTrainerAiGetWazaIryoku(trainer, waza);
    u16 zokusei = fightTrainerAiGetWazaZokuseiDataId(trainer, waza, pokemon);
    u8 rangeId = fightTrainerAiGetWazaRangeId(trainer, waza);
    u8 result = 1;

    if (fightOutPokemonCheckFightOut(target) == 0) {
        return 0;
    }
    if (waza != 0 && waza != 0x176 && rangeId != 7 && rangeId != 5) {
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, target, 0xA) == 1 && zokusei == 0xD && power != 0) {
            result = 0;
        }
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, target, 0xB) == 1 && zokusei == 0xB && power != 0) {
            result = 0;
        }
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, target, 0x12) == 1 && zokusei == 0xA &&
            fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, target, 7) == 0) {
            result = 0;
        }
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, target, 0x2B) == 1 && wazaDB_GetBouon(waza) == 1) {
            result = 0;
        }
    }
    return result;
}

extern "C" {

s32 fightTrainerAiWazaDoWazaValueFunc(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, u16 waza, FightOutPokemon* target) {
    FightWazaValueFunc func;

    if (fightTrainerAiDB_GetWazaInitValueFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer))) == 1) {
        func = (FightWazaValueFunc)wazaDB_GetFightTrainerAiWazaValueFuncPtr(waza);
        if (func == 0) {
            func = fightTrainerAiWazaValueNull;
        }
    } else {
        return 0;
    }
    return func(trainer, pokemon, waza, target);
}

}
