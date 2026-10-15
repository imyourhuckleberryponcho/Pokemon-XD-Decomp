// This unit needs extra_cflags=["-O4,s"].
#include <dolphin/types.h>
#pragma dont_inline on

struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightPokemon;
struct Pokemon;

extern "C" {
u16 HSD_Rand();
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
u8 fightTrainerDB_GetAiDataId(u16);
FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon*);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u16 fightOutPokemonGetAllAbiCnt(FightOutPokemon*);
u32 fightOutPokemon_GetAbicntAverage(FightOutPokemon*);
u32 fightOutPokemon_GetAbicntNimbleness(FightOutPokemon*);
u32 fightOutPokemon_GetAbicntSpeDef(FightOutPokemon*);
u32 fightOutPokemon_GetAbicntSpeAtk(FightOutPokemon*);
u32 fightOutPokemon_GetAbicntPhyDef(FightOutPokemon*);
u32 fightOutPokemon_GetAbicntPhyAtk(FightOutPokemon*);
u16 fightOutPokemon_GetSketchWazaDataId(FightOutPokemon*);
u16 fightOutPokemon_GetLastSelectWazaDataId(FightOutPokemon*);
u16 fightOutPokemon_GetLastUseWazaDataId(FightOutPokemon*);
u16 fightOutPokemon_GetUsedItemDataId(FightOutPokemon*);
u8 fightTrainerAiGetFightPokemonPartDataId(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonBasisSubayasa(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonBasisSpeDef(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonBasisSpeAtk(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonBasisPhyDef(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonBasisPhyAtk(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonBasisMaxHp(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiIsFightPokemonJoutaiNormal(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiIsFightPokemonNokoriHpHikui(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonMaxHp(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonNowHp(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiGetFightPokemonLevel(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonPokemonDataId(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiGetFightPokemonKeyPlayerFlag(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightPokemonSoubiItemDataId(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiGetFightPokemonFriend(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiIsFightPokemonNokoriWazaPpHikui(FIGHT_TRAINER*, FightPokemon*, u32);
u8 fightTrainerAiGetFightPokemonWazaNowPp(FIGHT_TRAINER*, FightPokemon*, u32);
u16 fightTrainerAiGetFightPokemonWazaDataId(FIGHT_TRAINER*, FightPokemon*, u32);

u16 pokemon_GetPokemonDataId(Pokemon*);
u16 pokemonDB_GetBasisNimbleness(u16);
u16 pokemonDB_GetBasisSpeDef(u16);
u16 pokemonDB_GetBasisSpeAtk(u16);
u16 pokemonDB_GetBasisPhyDef(u16);
u16 pokemonDB_GetBasisPhyAtk(u16);
u16 pokemonDB_GetBasisMaxHp(u16);
u32 pokemon_GetNimbleness(Pokemon*);
u16 pokemon_GetSpeDef(Pokemon*);
u16 pokemon_GetSpeAtk(Pokemon*);
u16 pokemon_GetPhyDef(Pokemon*);
u16 pokemon_GetPhyAtk(Pokemon*);
u32 fightFloor_GetFightType(u32);
u8 fightTrainerAiDB_GetPokemonJoutaiFlag(u8);
u8 pokemonIsJoutaiNormal(Pokemon*);
u8 fightTrainerAiDB_GetNokoriHpValue(u8);
u8 fightTrainerAiDB_GetWazaNokoriPpValue(u8);
u8 fightTrainerAiDB_GetWazaRiskFlag(u8);
u8 fightTrainerAiDB_GetWazaAvgValue(u8);
u8 fightTrainerAiDB_GetPartFlag(u8);
u8 fightTrainerAiDB_GetKeyPlayerFlag(u8);
u16 pokemon_GetFightTrainerPokemonDataId(Pokemon*);
u8 fightTrainerPokemonDB_GetPartDataId(u16);
u8 fightTrainerPokemonDB_GetKeyPlayerFlag(u16);
u8 fightPokemonIsJoutaiDataId(FightPokemon*, u16);
u16 fightPokemonGetSoubiItemSoubiDataId(FightPokemon*);
u16 fightPokemonGetSoubiItemDataId(FightPokemon*);
u8 pokemonWazaGetMaxPP(Pokemon*, u8);
u8 pokemon_GetPokemonWazaPp(Pokemon*, u8);
u16 pokemon_GetPokemonWazaDataId(Pokemon*, u8);
u16 fightTrainerAiGetFightPokemonZokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u8);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*, u8);
u8 fightTrainerAiGetFightPokemonWazaMaxPp(FIGHT_TRAINER*, FightPokemon*, u32);
s32 zokuseiGetAisyouValue(u16, u16, u8);
u8 fightSeqIsTenkouHit(u16);
u8 fightSeqIsAllwaysHit(u16);
u8 wazaDB_GetRiskFlag(u16);
u8 wazaDB_GetAvg(u16);
u8 fightTrainerAiGetWazaAvg(FIGHT_TRAINER*, u16);
s32 fightTrainerAiValueAddsubDB_GetValue(u16);
s32 fightTrainerAiAddValue(s32, s32);
s32 fightTrainerAiReviseValue(s32, s32, s32);
u16 fightOutPokemonGetNowHpPercentage(FightOutPokemon*);
u8 figthPokemonGetLevel(FightPokemon*);
u16 figthPokemonGetPokemonDataId(FightPokemon*);
u8 pokemon_GetFriend(Pokemon*);
u16 pokemon_GetMaxHp(Pokemon*);
u16 pokemon_GetHp(Pokemon*);
u8 wazaDB_GetAddFightKoukaAvg(u16);
u16 wazaDB_GetIryoku(u16);
u8 wazaDB_GetPp(u16);
u8 wazaDB_GetRangeId(u16);
u8 wazaDB_GetTypeId(u16, u8);
u8 wazaIsWazaTypeId(u16, u8);
u8 fightTrainerAiIsFightPokemonNokoriHp(FIGHT_TRAINER*, FightPokemon*, s8, f32);
u16 fightOutPokemon_GetAbicntAvoid(FightOutPokemon*);
u8 fightTrainerAiDB_GetAvoidMinValue(u8);
u8 fightTrainerAiDB_GetAvoidMaxValue(u8);
u8 fightTrainerAiDB_GetNimblenessMaxValue(u8);
u8 fightTrainerAiDB_GetSpeDefMaxValue(u8);
u8 fightTrainerAiDB_GetSpeAtkMaxValue(u8);
u8 fightTrainerAiDB_GetPhyDefMaxValue(u8);
u8 fightTrainerAiDB_GetPhyAtkMaxValue(u8);
u8 fightTrainerAiDB_GetAbicntMinValue(u8);
u8 fightTrainerAiDB_GetAbicntMaxValue(u8);
u8 fightTrainerAiDB_GetItemValue(u8);
u8 fightTrainerAiDB_GetIrekaeValue(u8);
u8 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon*);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u16 fightOutPokemonIsJoutaiKie(FightOutPokemon*);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon*, u8, u8, u8);
u16 fightAbicntDoKakeWaru(u8, u16);
u16 pokemonDB_GetBasisPhyDef(u16);
u16 pokemonDB_GetBasisSpeDef(u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u16 fightTrainerAiGetFightOutPokemonAllAbiCnt(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightPokemon_GetEntryId(FightPokemon*);
u8 fightTrainerAiDB_GetTokuseiCheckFlag(u8);
u8 fightTrainerAiDB_GetZokuseiCheckFlag(u8);
u32 fightFloorGetFightPokemonPtrToFightTrainerPtr(u32, FightPokemon*);
u16 fightTrainer_GetEnemyStoreTokuseiData(FIGHT_TRAINER*, u16);
u16 pokemonGetTokuseiDataId(Pokemon*);
u8 pokemonDB_GetTokuseiDataId(u16, u8);
u8 pokemonDB_GetZokuseiDataId(u16, u32);
u8 fightTrainerIsAllyFightTargetPtr(FIGHT_TRAINER*, void*, u8);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
u16 fightOutPokemon_GetTokuseiDataId(FightOutPokemon*);
u16 fightOutPokemonGetZokuseiDataId(FightOutPokemon*, u8);
u8 fightOutPokemonCheckFightOut(void*);
void* fightTargetGetPtrAsNowFightType(u32, void*);
u32 fightFloorLoopValidFightOutPokemon(u32, s32 (*)(void*, u16, void*), void*);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u32 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER*, u32, u8);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER*, u16, FightOutPokemon*);
u8 wazaCheckDarkWaza(u16);
u8 wazaDB_GetZokuseiDataId(u16);
void pokemonGetMezamerupower(Pokemon*, u16*, u16*);
extern u16 expect_tokusei_data_0[];
extern u16 expect_tokusei_data_2[];
void fightOutPokemonCreateFightAction(FightOutPokemon*, u32, u32, u32, void*, s32);
extern u8 fight_action_data_turn[];
u8 fightSeqRendouWazaCheck(u32);
u16 fightTrainerAiGetFightOutPokemonWazaDataId(FIGHT_TRAINER*, FightOutPokemon*, u32);
u16 fightTrainer_GetEnemyStoreWazaData(FIGHT_TRAINER*, u16, u8);
u32 fightTrainerAiCheckFightOutPokemonCanOutOkWazaBanme(FIGHT_TRAINER*, FightOutPokemon*, u32);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER*, FightOutPokemon*, u16*, s16*, u8);
u16 fightTrainer_GetEnemyExpectWazaData(FIGHT_TRAINER*, u16, u8);
u8 fightTrainerAiGetFightPokemonWazaNowPp(FIGHT_TRAINER*, FightPokemon*, u32);
u16 fightTrainerAiGetFightPokemonWazaDataIdAry(FIGHT_TRAINER*, FightPokemon*, u16*, s16*, u8);
u32 fightFloorGetNowTenkouDataId(u32, u32);
FightOutPokemon* fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(FIGHT_TRAINER*, u32, u16, u32, u8, FightOutPokemon*);
u16 zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16, u16*, u16);
u16 fightTrainerAiGetFightPokemonZokuseiDataIdAry(FIGHT_TRAINER*, FightPokemon*, u16*);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(FIGHT_TRAINER*, FightOutPokemon*, u16*);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
u16 fightTrainer_GetEnemyStoreWazaData2(FIGHT_TRAINER*, u16, u8);
u8 fightTrainer_GetEnemyTokuseiFlag(FIGHT_TRAINER*, u16);
void fightTrainer_SetEnemyTokuseiFlag(FIGHT_TRAINER*, u16, u8);
void fightTrainer_SetEnemyStoreTokuseiData(FIGHT_TRAINER*, u16, u16);
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon*);
u8 fightFloorCmpfightOutPokemonNimbleness(u32, FightOutPokemon*, FightOutPokemon*, u8);
void* fightSeqSelectDefensePokemonPtr(FightOutPokemon*, u16, u8, void*, u32, u32, s32);
s32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(void*, u8);
void fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon*, u32, u32, u32, void*, u16, s32, s8, u32);
extern u8 fightTrainerAiWazaSelectDefensePokemon[];
extern u8 fight_action_data_waza[];
u8 fightTrainer_GetEnemyStoreWazaNum(FIGHT_TRAINER*, u16);
void fightTrainer_SetEnemyStoreWazaData(FIGHT_TRAINER*, u16, u8, u16);
void fightTrainer_SetEnemyStoreWazaNum(FIGHT_TRAINER*, u16, u8);
void fightTrainer_SetEnemyExpectWazaData(FIGHT_TRAINER*, u16, u8, u16);
void* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon*);
u8 fightActionCheckValid(void*);
s16 fightAi_ThreatEnemyValue(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon*, s8, u32, s32, s32);
u32 fightFloorGetFightPokemonPtrToFightTrainerPtr(u32, FightPokemon*);
u8 fightOutPokemonIsNokoriHpFollowing(FightOutPokemon*, u8);
u8 fightAi_GetTokuseiHaveFlag(u32, FightOutPokemon*, u16);
u32 fightFloorGetStatus(u32, u32, u32, u32);
u32 fightPokemon_GetEntryId2(FightPokemon*);
u8 pokemonWazaCheckValid(Pokemon*, u8);
u16 zokuseiGetWazaJoutai(u16, u16);
u16 fightOutPokemon_GetZokuseiDataId(FightOutPokemon*, u8);
u8 fightTrainerIsAllyFightTargetPtr2(u32, FightOutPokemon*, u32);
u8 fightAi_CanMoveAppointWaza(FIGHT_TRAINER*, FightOutPokemon*, u16);
u32 fightFloorGetFightOutPokemonPtrToFightTrainerPtr(u32, FightOutPokemon*);
u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon*);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(u32, FIGHT_TRAINER*, FightOutPokemon**, u8, u8);
s16 fightOutPokemonGetFightEntryId(FightOutPokemon*);
u16 fightOutPokemonMaxHpWaruValue(FightOutPokemon*, u8);
void fightPokemon_SetAiDamage(FightPokemon*, u16, u8, s32);
s32 fightTrainerAiWazaDoWazaDamageFightPokemonFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightPokemon*, u8);
u8 fightOutPokemonCheckValid(FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(u32, FIGHT_TRAINER*, FightPokemon**, u8, u8);
}

struct TokuseiSearch {
    u32 tokusei;
    FightOutPokemon* result;
    s32 mode;
    FightOutPokemon* ref;
    FIGHT_TRAINER* trainer;
};

static u16 _fightTrainerAiGetFightPokemonTokuseiDataId(FIGHT_TRAINER*, FightPokemon*);
static u16 _fightTrainerAiGetFightOutPokemonTokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*);
static s32 _fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub(void*, u16, void*);

struct AllWazaValid {
    u32 a[2];
    u32 b[2];
    u16 c[2];
    u8 d[2];
    u8 e[2];
    u8 f[2];
    u8 g;
    u8 pad;
    u16 h[2][2];
    u8 k[2];
    u8 rest[6];
};
static AllWazaValid ai_allwaza_valid_tbl[0x40];
static s8 ai_allwaza_valid_work;
extern "C" void fightAi_InitAllWazaValidSub(AllWazaValid*);
static u8 _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza(u16);

extern "C" {
s32 fightAi_CopyAllWazaValidTable(AllWazaValid* dst, AllWazaValid* src) {
    u8 i;
    u8 j;
    if (dst == 0 || src == 0) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            dst->a[i] = src->a[i];
            dst->b[i] = src->b[i];
            dst->c[i] = src->c[i];
            dst->d[i] = src->d[i];
            dst->e[i] = src->e[i];
            dst->f[i] = src->f[i];
            dst->g = src->g;
            dst->h[i][j] = src->h[i][j];
            dst->k[j] = src->k[j];
        }
    }
    return 1;
}
u8 fightAi_CreateFightActionAttckIrekae(FightOutPokemon* a, s16 index) {
    if (a == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    fightOutPokemonCreateFightAction(a, 0, 9, 0, fight_action_data_turn, index);
    return 1;
}
u8 fightAi_CreateFightActionAttckWaza(FightOutPokemon* self, FightOutPokemon* target, u16 waza, s16 index) {
    u8 type;
    void* defender;
    s32 side;
    type = fightFloor_GetFightType(0);
    if (self == 0) {
        return 0;
    }
    if (target == 0) {
        return 0;
    }
    if (waza == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    defender = fightSeqSelectDefensePokemonPtr(self, waza, type, fightTrainerAiWazaSelectDefensePokemon, 1, 0, -1);
    if (defender != 0) {
        target = (FightOutPokemon*)defender;
    }
    if (target == 0) {
        return 0;
    }
    side = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, type);
    fightOutPokemonCreateFightActionAttackWaza(self, 0, 0x13, 0, fight_action_data_waza, waza, side, index, 0);
    return 1;
}
u8 fightAi_LateDefPokeThanAllyPoke(FightOutPokemon** ary, FightOutPokemon* self) {
    FightOutPokemon* first = ary[0];
    if (first != 0 || ary[1] != 0) {
        if (first != 0 && ary[1] != 0) {
            if (fightFloorCmpfightOutPokemonNimbleness(0, first, self, 1) == 1 && fightFloorCmpfightOutPokemonNimbleness(0, ary[1], self, 1) == 1) {
                return 1;
            }
        } else if (first != 0) {
            if (fightFloorCmpfightOutPokemonNimbleness(0, first, self, 1) == 1) {
                return 1;
            }
        } else if (ary[1] != 0) {
            if (fightFloorCmpfightOutPokemonNimbleness(0, ary[1], self, 1) == 1) {
                return 1;
            }
        }
    }
    return 0;
}
u32 fightAi_AppointWazaKoukaFlag(FightOutPokemon* a, FightOutPokemon* b, u16 zokusei) {
    u16 ownZ[2];
    u16 otherZ[2];
    u16 r1;
    u16 r2;
    u8 i;
    if (a == 0) {
        return 0;
    }
    if (b == 0) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        ownZ[i] = fightOutPokemon_GetZokuseiDataId(a, i);
        otherZ[i] = fightOutPokemon_GetZokuseiDataId(b, i);
    }
    if (otherZ[0] == zokusei || otherZ[1] == zokusei) {
        r1 = zokuseiGetWazaJoutai(zokusei, ownZ[0]);
        r2 = zokuseiGetWazaJoutai(zokusei, ownZ[1]);
        if (r1 == 0x43 || r2 == 0x43) {
            return 0x43;
        }
        switch (r1) {
        case 0x42:
            switch (r2) {
            case 0x3f:
            case 0x42:
                return 0x42;
            case 0x41:
                return 0x3f;
            }
            break;
        case 0x3f:
            switch (r2) {
            case 0x3f:
                return 0x3f;
            case 0x41:
                return 0x41;
            case 0x42:
                return 0x42;
            }
            break;
        case 0x41:
            switch (r2) {
            case 0x41:
            case 0x3f:
                return 0x41;
            case 0x42:
                return 0x3f;
            }
            break;
        }
    }
    return 0;
}
u8 fightAi_DamageKizetsuFlag(FightOutPokemon** ary, s32 damage) {
    u8 i;
    for (i = 0; i < 8; i++) {
        if (ary[i] != 0) {
            if (damage >= pokemon_GetHp(fightOutPokemonGetPokemonPtr(ary[i]))) {
                return 1;
            }
        }
    }
    return 0;
}
u8 fightAi_PokemonTokuseiMoukaFlag(FightOutPokemon* a) {
    FightPokemon* fp = fightOutPokemon_GetFightPokemonPtr(a);
    u32 trainer = fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fp);
    if (fightOutPokemonIsNokoriHpFollowing(a, 3) == 1) {
        if (fightAi_GetTokuseiHaveFlag(trainer, a, 0x42) == 2 || fightAi_GetTokuseiHaveFlag(trainer, a, 0x44) == 2 || fightAi_GetTokuseiHaveFlag(trainer, a, 0x41) == 2 || fightAi_GetTokuseiHaveFlag(trainer, a, 0x43) == 2) {
            return 2;
        }
        if (fightAi_GetTokuseiHaveFlag(trainer, a, 0x42) == 1 || fightAi_GetTokuseiHaveFlag(trainer, a, 0x44) == 1 || fightAi_GetTokuseiHaveFlag(trainer, a, 0x41) == 1 || fightAi_GetTokuseiHaveFlag(trainer, a, 0x43) == 1) {
            return 1;
        }
    }
    return 0;
}
u8 fightAi_GetWazaZokuseiData_ThinkWeatherBall(u16 waza, u16 weather) {
    u8 zokusei = (u8)wazaDB_GetZokuseiDataId(waza);
    if (waza == 0x137) {
        switch (weather) {
        case 1:
            return 0xa;
        case 2:
            return 0xb;
        case 3:
            return 5;
        case 5:
            return 0;
        case 4:
            return 0xf;
        }
    }
    return zokusei;
}
FightOutPokemon* fightAi_SelectDefPoke(FIGHT_TRAINER* t, FightOutPokemon* self, FightOutPokemon** cand, u16 count, u16 waza, s8 mode) {
    u8 candidates[8];
    s16 best;
    s16 value;
    u8 i;
    u8 num;
    u8 type = fightFloor_GetFightType(0);
    if (wazaDB_GetRangeId(waza) != 0) {
        return (FightOutPokemon*)fightSeqSelectDefensePokemonPtr(self, waza, type, 0, 1, 1, -1);
    }
    best = -0xff;
    for (i = 0; i < count; i++) {
        value = fightAi_ThreatEnemyValue(t, self, cand[i], mode, 0, -1, -1);
        if (best < value) {
            candidates[0] = i;
            best = value;
            num = 1;
        } else if (best == value && best > -0xff) {
            candidates[num] = i;
            num++;
        }
    }
    return cand[candidates[HSD_Rand() % num]];
}
void fightAi_CreateAction_FromAllWazaValid(FIGHT_TRAINER* t, AllWazaValid* v) {
    u8 type = fightFloor_GetFightType(0);
    u8 i;
    for (i = 0; i < 2; i++) {
        FightOutPokemon* self = (FightOutPokemon*)v->a[i];
        u16 waza = v->c[i];
        u8 index = v->d[i];
        FightOutPokemon* target = (FightOutPokemon*)v->b[i];
        if (self != 0 && target != 0 && fightActionCheckValid(fightOutPokemon_GetFightActionBuffPtr(self)) != 1) {
            void* defender = fightSeqSelectDefensePokemonPtr(self, waza, type, fightTrainerAiWazaSelectDefensePokemon, 1, 0, -1);
            s32 side;
            if (defender != 0) {
                target = (FightOutPokemon*)defender;
            }
            if (target == 0) {
                break;
            }
            side = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, type);
            fightOutPokemonCreateFightActionAttackWaza(self, 0, 0x13, 0, fight_action_data_waza, waza, side, index, 0);
        }
    }
}
u32 fightAi_CreateAllWazaValid_GetDefense(u16 waza, s32 value) {
    switch (wazaDB_GetRangeId(waza)) {
    case 0:
        return value;
    case 2:
    case 4:
    case 6:
        return 2;
    case 1:
    case 7:
        return 3;
    case 5:
        return 4;
    case 3:
        return 5;
    default:
        return 0;
    }
}
u8 fightAi_WazaSuccessProbability(FIGHT_TRAINER* t, FightOutPokemon* self, FightOutPokemon** ary, u16 waza) {
    u16 speeds[2];
    u8 faster = 0;
    u8 probability;
    u16 selfSpeed;
    u8 i;
    if (self == 0) {
        return 0;
    }
    if (t == 0) {
        return 0;
    }
    if (waza == 0) {
        return 0;
    }
    probability = wazaDB_GetAvg(waza);
    selfSpeed = pokemon_GetNimbleness(fightPokemon_GetPokemonBuffPtr(fightOutPokemon_GetFightPokemonPtr(self)));
    for (i = 0; i < 2; i++) {
        if (ary[i] != 0) {
            speeds[i] = pokemon_GetNimbleness(fightPokemon_GetPokemonBuffPtr(fightOutPokemon_GetFightPokemonPtr(ary[i])));
        } else {
            speeds[i] = 0;
        }
        if (selfSpeed < speeds[i]) {
            faster = faster + 1;
        }
    }
    if (faster == 1) {
        probability = (u8)(probability * 0x4b / 100);
    } else if (faster == 2) {
        probability = (u8)(probability * 0x32 / 100);
    }
    switch (fightAi_CanMoveAppointWaza(t, self, waza)) {
    case 0:
        probability = 0;
        break;
    default:
        probability = (u8)(probability * 0x32 / 100);
        break;
    case 3:
        probability = (u8)(probability * 0x4b / 100);
        break;
    }
    return probability;
}
void fightAi_InitAllWazaValid() {
    u8 i = 0;
    ai_allwaza_valid_work = 0;
    for (; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&ai_allwaza_valid_tbl[i]);
    }
}
void fightAi_InitAllWazaValidSub(AllWazaValid* v) {
    u8 i;
    u8 j;
    if (v != 0) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                v->a[i] = 0;
                v->b[i] = 0;
                v->c[i] = 0;
                v->d[i] = 0;
                v->e[i] = 0;
                v->f[i] = 0;
                v->g = 0;
                v->h[i][j] = 0;
                v->k[j] = 0;
            }
        }
    }
}
void fightAi_AddStoreTokusei(FightOutPokemon* a, FIGHT_TRAINER* t) {
    u16 entry;
    u8 tokusei0;
    u8 tokusei1;
    FightPokemon* fp;
    Pokemon* pokemon;
    u16 current;
    if (a != 0 && t != 0) {
        fp = fightOutPokemon_GetFightPokemonPtr(a);
        pokemon = fightPokemon_GetPokemonBuffPtr(fp);
        entry = fightPokemon_GetEntryId(fp);
        tokusei0 = (u8)pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(pokemon), 0);
        tokusei1 = (u8)pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(pokemon), 1);
        current = fightOutPokemon_GetTokuseiDataId(a);
        if (fightTrainer_GetEnemyTokuseiFlag(t, entry) == 0 && (tokusei1 == 0 || tokusei0 == tokusei1)) {
            fightTrainer_SetEnemyTokuseiFlag(t, entry, 1);
            fightTrainer_SetEnemyStoreTokuseiData(t, entry, current);
        }
    }
}
u8 fightAi_GetTokuseiHaveFlag(u32 trainer, FightOutPokemon* a, u16 tokusei) {
    u8 type = fightFloor_GetFightType(0);
    Pokemon* pokemon;
    u8 tokusei0;
    u8 tokusei1;
    u8 result;
    u8 i;
    if (a == 0) {
        return 0;
    }
    if (trainer == 0) {
        return 0;
    }
    pokemon = fightPokemon_GetPokemonBuffPtr(fightOutPokemon_GetFightPokemonPtr(a));
    tokusei0 = pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(pokemon), 0);
    tokusei1 = pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(pokemon), 1);
    fightOutPokemon_GetTokuseiDataId(a);
    result = 0;
    for (i = 0; i < 0x44; i++) {
        if (expect_tokusei_data_2[i] == pokemon_GetPokemonDataId(pokemon)) {
            result = tokusei1;
            break;
        }
    }
    if (result == 0) {
        result = tokusei0;
    }
    for (i = 0; i < 8; i++) {
        if (expect_tokusei_data_0[i] == pokemon_GetPokemonDataId(pokemon)) {
            result = 0;
            break;
        }
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId((FIGHT_TRAINER*)trainer, a, tokusei) == 1) {
        return 2;
    }
    if (fightTrainerIsAllyFightTargetPtr((FIGHT_TRAINER*)trainer, a, type) == 0 && result == tokusei) {
        return 1;
    }
    return 0;
}
void fightAi_DereteExpectWaza(FightOutPokemon* a, FIGHT_TRAINER* t, u16 waza) {
    u8 i;
    u16 entry;
    u8 next;
    if (a != 0 && t != 0) {
        entry = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(a));
        for (i = 0; i < 8; i++) {
            if (waza == fightTrainer_GetEnemyExpectWazaData(t, entry, i)) {
                fightTrainer_SetEnemyExpectWazaData(t, entry, i, 0);
            }
        }
        for (i = 0; i < 7; i++) {
            if (fightTrainer_GetEnemyExpectWazaData(t, entry, i) == 0) {
                next = i + 1;
                fightTrainer_SetEnemyExpectWazaData(t, entry, i, fightTrainer_GetEnemyExpectWazaData(t, entry, next));
                fightTrainer_SetEnemyExpectWazaData(t, entry, next, 0);
            }
        }
    }
}
void fightAi_AddStoreWaza(FightOutPokemon* a, FIGHT_TRAINER* t, u16 waza) {
    u8 i;
    u16 entry;
    u8 j;
    if (a != 0 && t != 0) {
        entry = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(a));
        for (i = 0; i < 4; i++) {
            if (waza == fightTrainer_GetEnemyStoreWazaData(t, entry, i)) {
                break;
            }
            if (fightTrainer_GetEnemyStoreWazaData(t, entry, i) == 0) {
                fightTrainer_SetEnemyStoreWazaData(t, entry, i, waza);
                fightTrainer_SetEnemyStoreWazaNum(t, entry, fightTrainer_GetEnemyStoreWazaNum(t, entry) + 1);
                break;
            }
        }
        if (fightTrainer_GetEnemyStoreWazaNum(t, entry) >= 4) {
            for (j = 0; j < 8; j++) {
                fightTrainer_SetEnemyExpectWazaData(t, entry, j, 0);
            }
        }
    }
}
s32 fightAi_GetEnemyWazaAndFlag(FIGHT_TRAINER* t, FightPokemon* p, u16* out, u8 idx) {
    u16 entry;
    if (p == 0) {
        return 0;
    }
    if (out == 0) {
        return 0;
    }
    entry = fightPokemon_GetEntryId(p);
    if (idx < 4) {
        *out = fightTrainer_GetEnemyStoreWazaData(t, entry, idx);
        if (*out == 0) {
            return 0;
        }
        return *out <= 0x176 ? 2 : 0;
    }
    if (idx >= 4 && idx < 0xc) {
        *out = fightTrainer_GetEnemyExpectWazaData(t, entry, idx - 4);
        if (*out == 0) {
            return 0;
        }
        return *out <= 0x176;
    }
    return 0;
}
u32 fightAi_GetWazaHaveFlag(FIGHT_TRAINER* t, FightPokemon* p, u16 waza) {
    u16 entry;
    Pokemon* pokemon;
    u8 i;
    u8 j;
    if (t == 0) {
        return 0;
    }
    if (p == 0) {
        return 0;
    }
    if (waza == 0) {
        return 0;
    }
    entry = fightPokemon_GetEntryId(p);
    pokemon = fightPokemon_GetPokemonBuffPtr(p);
    if (fightTrainerIsAllyFightTargetPtr(t, p, fightFloorGetStatus(0, 0, 0x14, 0)) == 0) {
        for (i = 0; i < 4; i++) {
            if (waza == fightTrainer_GetEnemyStoreWazaData(t, entry, i)) {
                return 2;
            }
        }
        for (j = 0; j < 8; j++) {
            if (waza == fightTrainer_GetEnemyExpectWazaData(t, entry, j)) {
                return 1;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (pokemonWazaCheckValid(pokemon, i) != 0 && waza == pokemon_GetPokemonWazaDataId(pokemon, i)) {
                return 2;
            }
        }
    }
    return 0;
}
}
static u8 _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza(u16 waza) {
    u16 ignore[3] = {0x78, 0x11d, 0x99};
    u8 i;
    for (i = 0; i < 3; i++) {
        if (waza == ignore[i]) {
            return 1;
        }
    }
    return 0;
}
extern "C" {
FightOutPokemon** fightAi_JudgeMoveFightOutPokemon(FIGHT_TRAINER* t, FightOutPokemon** ary, u16* count) {
    u8 i;
    u8 j;
    u16 n = *count;
    for (i = 0; i < n; i++) {
        if (ary[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 0x12) == 1 || fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 0x22) == 1) {
                ary[i] = 0;
                *count -= 1;
            }
            if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 8) == 1 || fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 7) == 1) {
                ary[i] = 0;
                *count -= 1;
            }
            if (fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, ary[i]) != (u32)t) {
                ary[i] = 0;
                *count -= 1;
            }
            if (fightAi_GetTokuseiHaveFlag((u32)t, ary[i], 0x36) == 2 && fightOutPokemon_GetNamakeFlag(ary[i]) == 1) {
                ary[i] = 0;
                *count -= 1;
            }
        }
    }
    for (j = 0; j < n; j++) {
        if (ary[j] == 0 && j + 1 < n) {
            FightOutPokemon* next = ary[j + 1];
            if (next != 0) {
                ary[j] = next;
                ary[j + 1] = 0;
            }
        }
    }
    return ary;
}
u8 fightTrainerAiCheckDoFightActionItem(FIGHT_TRAINER* t) {
    u8 value = fightTrainerAiDB_GetItemValue(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t)));
    s32 rnd = HSD_Rand() % 100;
    u32 result = rnd < value;
    return result;
}
u8 fightTrainerAiCheckDoFightActionIrekae(FIGHT_TRAINER* t) {
    u8 value = fightTrainerAiDB_GetIrekaeValue(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t)));
    s32 rnd = HSD_Rand() % 100;
    u32 result = rnd < value;
    return result;
}
u32 fightTrainerAiGetPokemonDataDefense(FIGHT_TRAINER* t, u16 id) {
    u16 def;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    def = pokemonDB_GetBasisPhyDef(id);
    return def + pokemonDB_GetBasisSpeDef(id);
}
u8 fightTrainerAiIsFightOutPokemonAvoidCntHikui(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u8 cnt = fightOutPokemon_GetAbicntAvoid(a);
    s32 value = fightTrainerAiDB_GetAvoidMinValue(ai);
    u32 result = cnt <= value;
    return result;
}
u8 fightTrainerAiIsFightOutPokemonAvoidCntTakai(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u8 cnt = fightOutPokemon_GetAbicntAvoid(a);
    s32 value = fightTrainerAiDB_GetAvoidMaxValue(ai);
    u32 result = cnt >= value;
    return result;
}
u8 fightTrainerAiIsFightOutPokemonNimblenessCntTakai(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u8 cnt = (u8)fightOutPokemon_GetAbicntNimbleness(a);
    s32 value = fightTrainerAiDB_GetNimblenessMaxValue(ai);
    u32 result = cnt >= value;
    return result;
}
u8 fightTrainerAiIsFightOutPokemonSpeDefCntTakai(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u8 cnt = (u8)fightOutPokemon_GetAbicntSpeDef(a);
    s32 value = fightTrainerAiDB_GetSpeDefMaxValue(ai);
    u32 result = cnt >= value;
    return result;
}
u8 fightTrainerAiIsFightOutPokemonSpeAtkCntTakai(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u8 cnt = (u8)fightOutPokemon_GetAbicntSpeAtk(a);
    s32 value = fightTrainerAiDB_GetSpeAtkMaxValue(ai);
    u32 result = cnt >= value;
    return result;
}
u8 fightTrainerAiIsFightOutPokemonPhyDefCntTakai(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u8 cnt = (u8)fightOutPokemon_GetAbicntPhyDef(a);
    s32 value = fightTrainerAiDB_GetPhyDefMaxValue(ai);
    u32 result = cnt >= value;
    return result;
}
u8 fightTrainerAiIsFightOutPokemonPhyAtkCntTakai(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u8 cnt = (u8)fightOutPokemon_GetAbicntPhyAtk(a);
    s32 value = fightTrainerAiDB_GetPhyAtkMaxValue(ai);
    u32 result = cnt >= value;
    return result;
}
u8 fightTrainerAiIsFightOutPokemonAllAbiCntHikui(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u16 cnt = fightTrainerAiGetFightOutPokemonAllAbiCnt(t, a);
    s32 value = fightTrainerAiDB_GetAbicntMinValue(ai);
    u32 result = cnt <= value;
    return result;
}
u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u16 cnt = fightTrainerAiGetFightOutPokemonAllAbiCnt(t, a);
    s32 value = fightTrainerAiDB_GetAbicntMaxValue(ai);
    u32 result = cnt >= value;
    return result;
}
u16 fightTrainerAiGetFightOutPokemonAllAbiCnt(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemonGetAllAbiCnt(a);
}
u16 fightTrainerAiGetFightOutPokemonAbiCntAvd(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u16 cnt;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    cnt = fightOutPokemon_GetAbicntAvoid(a);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, a, 0x19) == 1 && (u8)cnt > 6) {
        cnt = 6;
    }
    return cnt;
}
u32 fightTrainerAiGetFightOutPokemonAbiCntAvg(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetAbicntAverage(a);
}
u32 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetAbicntNimbleness(a);
}
u32 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetAbicntSpeDef(a);
}
u32 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetAbicntSpeAtk(a);
}
u32 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetAbicntPhyDef(a);
}
u32 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetAbicntPhyAtk(a);
}
u32 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER* t, u32 floor, u8 check) {
    s32 weather = fightFloorGetNowTenkouDataId(floor, 0);
    if (check == 1) {
        if (fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(t, floor, 0xd, 0, 0, 0) != 0) {
            return 0;
        }
        if (fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(t, floor, 0x4d, 0, 0, 0) != 0) {
            return 0;
        }
    }
    return weather;
}
u32 fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_TRAINER* t, u32 floor, FightOutPokemon* target, FightOutPokemon** out) {
    FightOutPokemon* first;
    FightOutPokemon* second;
    FightOutPokemon* third;
    u8 flagA = 0;
    u8 flagB = 0;
    if (fightOutPokemonCheckValid(target) == 0) {
        return 0;
    }
    first = fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(t, floor, 0x17, 0, 2, target);
    second = fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(t, floor, 0x47, 0, 2, target);
    third = fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(t, floor, 0x2a, 0, 0, target);
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 2) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x1a) == 1) {
        flagA = 1;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 8) == 1) {
        flagB = 1;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x16) == 1 || fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0xe) == 1 || fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x25) == 1) {
        return 1;
    }
    if (first != 0) {
        if (out != 0) {
            *out = first;
        }
        return 2;
    }
    if (second != 0 && flagA == 0) {
        if (out != 0) {
            *out = second;
        }
        return 2;
    }
    if (third != 0 && flagB == 1) {
        if (out != 0) {
            *out = third;
        }
        return 2;
    }
    return 0;
}
FightOutPokemon* fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(FIGHT_TRAINER* t, u32 floor, u16 tokusei, u32 unused, u8 mode, FightOutPokemon* ref) {
    TokuseiSearch search;
    search.trainer = t;
    search.tokusei = tokusei;
    search.result = 0;
    search.mode = mode;
    search.ref = ref;
    fightFloorLoopValidFightOutPokemon(floor, _fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub, &search);
    return search.result;
}
}
static s32 _fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub(void* mon, u16 index, void* data) {
    TokuseiSearch* search = (TokuseiSearch*)data;
    FightOutPokemon* ref = search->ref;
    FIGHT_TRAINER* trainer = search->trainer;
    void* refSide;
    void* monSide;
    if (fightOutPokemonCheckFightOut(mon) == 0) {
        return 1;
    }
    if (ref == 0) {
        refSide = 0;
    } else if (search->mode == 1) {
        refSide = fightTargetGetPtrAsNowFightType(2, ref);
    } else if (search->mode == 2) {
        refSide = fightTargetGetPtrAsNowFightType(3, ref);
    } else {
        refSide = 0;
    }
    monSide = fightTargetGetPtrAsNowFightType(2, mon);
    if ((search->mode == 1 || search->mode == 2) && refSide == 0) {
        return 1;
    }
    if (search->mode == 0) {
        if (ref != 0 && (void*)ref == mon) {
            return 1;
        }
    } else if (search->mode == 1 || search->mode == 2) {
        if (refSide != monSide) {
            return 1;
        }
    } else {
        return 1;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, (FightOutPokemon*)mon, (u16)search->tokusei) == 1) {
        search->result = (FightOutPokemon*)mon;
        return 0;
    }
    return 1;
}
extern "C" {
u16 fightTrainerAiGetFightOutPokemonSketchWazaDataId(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetSketchWazaDataId(a);
}
u16 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetLastSelectWazaDataId(a);
}
u16 fightTrainerAiGetFightOutPokemonLastUseWazaDataId(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetLastUseWazaDataId(a);
}
u8 fightTrainerAiCheckHaveFightOutPokemonWazaDataId(FIGHT_TRAINER* t, FightOutPokemon* a, u16 waza, s16* index, u8 check) {
    u16 ids[8];
    s16 indices[8];
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, a, ids, indices, check);
    u16 i;
    for (i = 0; i < count; i++) {
        if (waza == ids[i]) {
            if (index != 0) {
                *index = indices[i];
            }
            return 1;
        }
    }
    return 0;
}
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER* t, FightOutPokemon* a, u16* ids, s16* indices, u8 check) {
    u8 type = fightFloor_GetFightType(0);
    u16 count;
    u16 entry;
    u16 i;
    u16 j;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    entry = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(a));
    if (a == 0) {
        return 0;
    }
    if (fightTrainerIsAllyFightTargetPtr(t, a, type) == 0) {
        count = 0;
        for (i = 0; i < 8; i++) {
            if (ids != 0) {
                ids[i] = 0;
            }
            if (indices != 0) {
                indices[i] = -1;
            }
        }
        for (j = 0; j < 4; j++) {
            u16 waza = fightTrainer_GetEnemyStoreWazaData(t, entry, (u8)j);
            if (waza != 0 && waza != 0x176 && waza != 0x163 && (check != 1 || (u8)fightTrainerAiCheckFightOutPokemonCanOutOkWazaBanme(t, a, (u8)j) != 0)) {
                if (ids != 0) {
                    ids[count] = waza;
                }
                if (indices != 0) {
                    indices[count] = j;
                }
                count++;
            }
        }
    } else {
        count = 0;
        for (i = 0; i < 4; i++) {
            if (ids != 0) {
                ids[i] = 0;
            }
            if (indices != 0) {
                indices[i] = -1;
            }
        }
        for (j = 0; j < 4; j++) {
            u16 waza = fightTrainerAiGetFightOutPokemonWazaDataId(t, a, (u8)j);
            if (waza != 0 && waza != 0x176 && waza != 0x163 && (check != 1 || (u8)fightTrainerAiCheckFightOutPokemonCanOutOkWazaBanme(t, a, (u8)j) != 0)) {
                if (ids != 0) {
                    ids[count] = waza;
                }
                if (indices != 0) {
                    indices[count] = j;
                }
                count++;
            }
        }
    }
    return count;
}
u16 fightTrainerAiGetFightPokemonWazaDataIdAry(FIGHT_TRAINER* t, FightPokemon* p, u16* ids, s16* indices, u8 check) {
    u8 type = fightFloor_GetFightType(0);
    u16 count;
    u16 entry;
    u16 i;
    u16 j;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    entry = fightPokemon_GetEntryId(p);
    if (p == 0) {
        return 0;
    }
    if (fightTrainerIsAllyFightTargetPtr(t, p, type) == 0) {
        count = 0;
        for (i = 0; i < 8; i++) {
            if (ids != 0) {
                ids[i] = 0;
            }
            if (indices != 0) {
                indices[i] = -1;
            }
        }
        for (j = 0; j < 8; j++) {
            u16 waza = fightTrainer_GetEnemyExpectWazaData(t, entry, (u8)j);
            if (waza != 0 && waza != 0x176 && waza != 0x163 && (check != 1 || fightTrainerAiGetFightPokemonWazaNowPp(t, p, (u8)j) != 0)) {
                if (ids != 0) {
                    ids[count] = waza;
                }
                if (indices != 0) {
                    indices[count] = j;
                }
                count++;
            }
        }
    } else {
        count = 0;
        for (i = 0; i < 4; i++) {
            if (ids != 0) {
                ids[i] = 0;
            }
            if (indices != 0) {
                indices[i] = -1;
            }
        }
        for (j = 0; j < 4; j++) {
            u16 waza = fightTrainerAiGetFightPokemonWazaDataId(t, p, (u8)j);
            if (waza != 0 && waza != 0x176 && waza != 0x163 && (check != 1 || fightTrainerAiGetFightPokemonWazaNowPp(t, p, (u8)j) != 0)) {
                if (ids != 0) {
                    ids[count] = waza;
                }
                if (indices != 0) {
                    indices[count] = j;
                }
                count++;
            }
        }
    }
    return count;
}
u32 fightTrainerAiCheckFightOutPokemonCanOutOkWazaBanme(FIGHT_TRAINER* t, FightOutPokemon* a, u32 banme) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemonCheckCanOutOkWazaBanme(a, banme, 0, 0) ? 0 : 1;
}
u16 fightTrainerAiGetFightOutPokemonUsedItemDataId(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemon_GetUsedItemDataId(a);
}
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER* t, FightOutPokemon* a, u16 id) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t))) == 1) {
        return fightOutPokemonIsJoutaiDataId(a, id);
    }
    return 0;
}
u8 fightTrainerAiGetFightOutPokemonPartDataId(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonPartDataId(t, p);
}
s32 fightTrainerAiCmpFightOutPokemonSubayasa(FIGHT_TRAINER* t, FightOutPokemon* a, FightOutPokemon* b) {
    u32 speedA = pokemon_GetNimbleness(fightOutPokemonGetPokemonPtr(a));
    u32 speedB = pokemon_GetNimbleness(fightOutPokemonGetPokemonPtr(b));
    u32 cntA = fightOutPokemon_GetAbicntNimbleness(a);
    u32 cntB = fightOutPokemon_GetAbicntNimbleness(b);
    return fightAbicntDoKakeWaru(cntA, speedA) - fightAbicntDoKakeWaru(cntB, speedB);
}
u16 fightTrainerAiGetFightOutPokemonBasisSubayasa(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonBasisSubayasa(t, p);
}
u16 fightTrainerAiGetFightOutPokemonBasisSpeDef(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonBasisSpeDef(t, p);
}
u16 fightTrainerAiGetFightOutPokemonBasisSpeAtk(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonBasisSpeAtk(t, p);
}
u16 fightTrainerAiGetFightOutPokemonBasisPhyDef(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonBasisPhyDef(t, p);
}
u16 fightTrainerAiGetFightOutPokemonBasisPhyAtk(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonBasisPhyAtk(t, p);
}
u16 fightTrainerAiGetFightOutPokemonBasisMaxHp(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonBasisMaxHp(t, p);
}
u8 fightTrainerAiIsFightOutPokemonJoutaiKaragenki(FIGHT_TRAINER* t, FightOutPokemon* a) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t))) == 1) {
        return fightOutPokemonIsJoutaiKaragenki(a);
    }
    return 0;
}
bool fightTrainerAiIsFightOutPokemonJoutaiKie(FIGHT_TRAINER* t, FightOutPokemon* a) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t))) == 1) {
        return fightOutPokemonIsJoutaiKie(a) != 0;
    }
    return 0;
}
u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiIsFightPokemonJoutaiNormal(t, p);
}
u8 fightTrainerAiIsFightOutPokemonNokoriHp(FIGHT_TRAINER* t, FightOutPokemon* a, s8 x, f32 rate) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiIsFightPokemonNokoriHp(t, p, x, rate);
}
u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiIsFightPokemonNokoriHpHikui(t, p);
}
u16 fightTrainerAiGetFightOutPokemonMaxHp(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonMaxHp(t, p);
}
u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonNowHp(t, p);
}
u8 fightTrainerAiGetFightOutPokemonLevel(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonLevel(t, p);
}
u16 fightTrainerAiGetFightOutPokemonPokemonDataId(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonPokemonDataId(t, p);
}
u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonKeyPlayerFlag(t, p);
}
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER* t, FightOutPokemon* a, u16 zokusei, s16 hit) {
    u16 ary[2];
    u16 count;
    u16 result;
    u16 i;
    if (zokusei == 9) {
        return 0x3f;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, a, 0x1a) == 1 && zokusei == 4) {
        return 0x43;
    }
    count = fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(t, a, ary);
    if (count == 0) {
        return 0x3f;
    }
    result = zokuseiGetWazaJoutaiAsDefenseZokuseiAry(zokusei, ary, count);
    if ((zokusei == 0 || zokusei == 1) && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, a, 0x19) == 1) {
        for (i = 0; i < count; i++) {
            u16 z = ary[i];
            if (z != 9 && z == 7) {
                result = 0x3f;
            }
        }
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, a, 0x19) == 1 && result != 0x41 && hit > 0) {
        return 0x43;
    }
    return result;
}
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(FIGHT_TRAINER* t, FightOutPokemon* a, u16* out) {
    u16 count = 0;
    u8 i;
    for (i = 0; i < 2; i++) {
        u16 z = fightTrainerAiGetFightOutPokemonZokuseiDataId(t, a, i);
        if (z != 9) {
            out[count++] = z;
        }
    }
    return count;
}
u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(FIGHT_TRAINER* t, FightOutPokemon* a, u16 z) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    if (z == (u16)fightTrainerAiGetFightOutPokemonZokuseiDataId(t, a, 0) || z == (u16)fightTrainerAiGetFightOutPokemonZokuseiDataId(t, a, 1)) {
        return 1;
    }
    return 0;
}
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER* t, FightOutPokemon* a, u16 tokusei) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    if (tokusei == 0) {
        return 0;
    }
    return (u16)_fightTrainerAiGetFightOutPokemonTokuseiDataId(t, a) == tokusei;
}
}
static u16 _fightTrainerAiGetFightOutPokemonTokuseiDataId(FIGHT_TRAINER* t, FightOutPokemon* a) {
    u8 type = fightFloor_GetFightType(0);
    u8 ai;
    u16 entry;
    Pokemon* pokemon;
    u8 tokusei0;
    u8 tokusei1;
    ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    entry = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(a));
    pokemon = fightOutPokemonGetPokemonPtr(a);
    tokusei0 = pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(pokemon), 0);
    tokusei1 = pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(pokemon), 1);
    if (fightTrainerAiDB_GetTokuseiCheckFlag(ai) == 1) {
        if (fightTrainerIsAllyFightTargetPtr(t, a, type) == 0) {
            u16 stored = fightTrainer_GetEnemyStoreTokuseiData(t, entry);
            u16 result;
            u8 i;
            if (stored != 0) {
                return stored;
            }
            result = 0;
            for (i = 0; i < 0x44; i++) {
                if (expect_tokusei_data_2[i] == pokemon_GetPokemonDataId(pokemon)) {
                    result = tokusei1;
                    break;
                }
            }
            if (result == 0) {
                result = tokusei0;
            }
            for (i = 0; i < 8; i++) {
                if (expect_tokusei_data_0[i] == pokemon_GetPokemonDataId(pokemon)) {
                    result = 0;
                    break;
                }
            }
            return result;
        }
        return fightOutPokemonGetTokuseiDataId(a);
    }
    return 0;
}
extern "C" {
u16 fightTrainerAiGetFightOutPokemonZokuseiDataId(FIGHT_TRAINER* t, FightOutPokemon* a, u8 idx) {
    u8 type = fightFloor_GetFightType(0);
    if (fightTrainerAiDB_GetZokuseiCheckFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t))) == 1) {
        if (fightTrainerIsAllyFightTargetPtr(t, a, type) == 0) {
            return fightOutPokemonGetZokuseiDataId(a, idx);
        }
        return fightOutPokemonGetZokuseiDataId(a, idx);
    }
    return 9;
}
u8 fightTrainerAiIsFightOutPokemonNokoriWazaPpHikui(FIGHT_TRAINER* t, FightOutPokemon* a, u32 idx) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiIsFightPokemonNokoriWazaPpHikui(t, p, idx);
}
u8 fightTrainerAiGetFightOutPokemonWazaNowPp(FIGHT_TRAINER* t, FightOutPokemon* a, u32 idx) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonWazaNowPp(t, p, idx);
}
u16 fightTrainerAiGetFightOutPokemonWazaDataId(FIGHT_TRAINER* t, FightOutPokemon* a, u32 idx) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonWazaDataId(t, p, idx);
}
u16 fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(t, p);
}
u16 fightTrainerAiGetFightOutPokemonSoubiItemDataId(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonSoubiItemDataId(t, p);
}
u8 fightTrainerAiGetFightOutPokemonFriend(FIGHT_TRAINER* t, FightOutPokemon* a) {
    FightPokemon* p = fightOutPokemon_GetFightPokemonPtr(a);
    return fightTrainerAiGetFightPokemonFriend(t, p);
}
u8 fightTrainerAiIsFightPokemonJoutaiDataId(FIGHT_TRAINER* t, FightPokemon* p, u16 id) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t))) == 1) {
        return fightPokemonIsJoutaiDataId(p, id);
    }
    return 0;
}
u8 fightTrainerAiGetFightPokemonPartDataId(FIGHT_TRAINER* t, FightPokemon* p) {
    u8 ai;
    u16 id;
    fightFloor_GetFightType(0);
    ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    id = pokemon_GetFightTrainerPokemonDataId(fightPokemonGetPokemonPtr(p));
    if (fightTrainerAiDB_GetPartFlag(ai) == 1) {
        return fightTrainerPokemonDB_GetPartDataId(id);
    }
    return 1;
}
u8 fightTrainerAiGetFightPokemonKeyPlayerFlag(FIGHT_TRAINER* t, FightPokemon* p) {
    u8 ai;
    u16 id;
    fightFloor_GetFightType(0);
    ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    id = pokemon_GetFightTrainerPokemonDataId(fightPokemonGetPokemonPtr(p));
    if (fightTrainerAiDB_GetKeyPlayerFlag(ai) == 1) {
        return fightTrainerPokemonDB_GetKeyPlayerFlag(id);
    }
    return 0;
}
u16 fightTrainerAiGetFightPokemonBasisSubayasa(FIGHT_TRAINER* t, FightPokemon* p) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemonDB_GetBasisNimbleness(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(p)));
}
u16 fightTrainerAiGetFightPokemonBasisSpeDef(FIGHT_TRAINER* t, FightPokemon* p) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemonDB_GetBasisSpeDef(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(p)));
}
u16 fightTrainerAiGetFightPokemonBasisSpeAtk(FIGHT_TRAINER* t, FightPokemon* p) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemonDB_GetBasisSpeAtk(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(p)));
}
u16 fightTrainerAiGetFightPokemonBasisPhyDef(FIGHT_TRAINER* t, FightPokemon* p) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemonDB_GetBasisPhyDef(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(p)));
}
u16 fightTrainerAiGetFightPokemonBasisPhyAtk(FIGHT_TRAINER* t, FightPokemon* p) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemonDB_GetBasisPhyAtk(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(p)));
}
u16 fightTrainerAiGetFightPokemonBasisMaxHp(FIGHT_TRAINER* t, FightPokemon* p) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemonDB_GetBasisMaxHp(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(p)));
}
u32 fightTrainerAiGetFightPokemonSubayasa(FIGHT_TRAINER* t, FightPokemon* p) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemon_GetNimbleness(fightPokemonGetPokemonPtr(p));
}
u16 fightTrainerAiGetFightOutPokemonSpeDef(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemon_GetSpeDef(fightOutPokemonGetPokemonPtr(a));
}
u16 fightTrainerAiGetFightOutPokemonSpeAtk(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemon_GetSpeAtk(fightOutPokemonGetPokemonPtr(a));
}
u16 fightTrainerAiGetFightOutPokemonPhyDef(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemon_GetPhyDef(fightOutPokemonGetPokemonPtr(a));
}
u16 fightTrainerAiGetFightOutPokemonPhyAtk(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemon_GetPhyAtk(fightOutPokemonGetPokemonPtr(a));
}
u8 fightTrainerAiIsFightPokemonJoutaiNormal(FIGHT_TRAINER* t, FightPokemon* p) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t))) == 1) {
        return pokemonIsJoutaiNormal(fightPokemonGetPokemonPtr(p));
    }
    return 1;
}
u16 fightTrainerAiGetFightOutPokemonNowHpPercentage(FIGHT_TRAINER* t, FightOutPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightOutPokemonGetNowHpPercentage(a);
}
u8 fightTrainerAiIsFightPokemonNokoriHp(FIGHT_TRAINER* t, FightPokemon* p, s8 mode, f32 rate) {
    u16 now;
    u16 max;
    s32 threshold;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    now = fightTrainerAiGetFightPokemonNowHp(t, p);
    max = fightTrainerAiGetFightPokemonMaxHp(t, p);
    if (rate == 0.0f) {
        rate = 1.0f;
    }
    threshold = (s32)(max * rate);
    if (mode == 0) {
        if (now == threshold) {
            return 1;
        }
    } else if (mode > 0) {
        if (now >= threshold) {
            return 1;
        }
    } else if (mode < 0 && now <= threshold) {
        return 1;
    }
    return 0;
}
u8 fightTrainerAiIsFightPokemonNokoriHpHikui(FIGHT_TRAINER* t, FightPokemon* p) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u16 nowHp = fightTrainerAiGetFightPokemonNowHp(t, p);
    u16 maxHp = fightTrainerAiGetFightPokemonMaxHp(t, p);
    u8 value = fightTrainerAiDB_GetNokoriHpValue(ai);
    s32 percent = nowHp * 100 / maxHp;
    u32 result = percent <= value;
    return result;
}
u16 fightTrainerAiGetFightPokemonMaxHp(FIGHT_TRAINER* t, FightPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemon_GetMaxHp(fightPokemonGetPokemonPtr(a));
}
u16 fightTrainerAiGetFightPokemonNowHp(FIGHT_TRAINER* t, FightPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemon_GetHp(fightPokemonGetPokemonPtr(a));
}
u8 fightTrainerAiGetFightPokemonLevel(FIGHT_TRAINER* t, FightPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return figthPokemonGetLevel(a);
}
u16 fightTrainerAiGetFightPokemonPokemonDataId(FIGHT_TRAINER* t, FightPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return figthPokemonGetPokemonDataId(a);
}
s32 fightTrainerAiGetFightPokemonZokuseiAisyouValue(FIGHT_TRAINER* t, FightPokemon* p, u8 x) {
    u8 i;
    s32 sum;
    u16 prev = 9;
    sum = 0;
    for (i = 0; i < 2; i++) {
        u16 z = fightTrainerAiGetFightPokemonZokuseiDataId(t, p, i);
        if (z == 9) {
            continue;
        }
        if (prev == z) {
            break;
        }
        prev = z;
        sum += zokuseiGetAisyouValue(z, 0, x);
    }
    return sum;
}
u16 fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER* t, FightPokemon* p, u16 zokusei, s16 hit) {
    u16 ary[2];
    u16 count;
    u16 result;
    if (zokusei == 9) {
        return 0x3f;
    }
    if (fightTrainerAiIsFightPokemonTokuseiDataId(t, p, 0x1a) == 1 && zokusei == 4) {
        return 0x43;
    }
    count = fightTrainerAiGetFightPokemonZokuseiDataIdAry(t, p, ary);
    if (count == 0) {
        return 0x3f;
    }
    result = zokuseiGetWazaJoutaiAsDefenseZokuseiAry(zokusei, ary, count);
    if (fightTrainerAiIsFightPokemonTokuseiDataId(t, p, 0x19) == 1 && result != 0x41 && hit > 0) {
        return 0x43;
    }
    return result;
}
u16 fightTrainerAiGetFightPokemonZokuseiDataIdAry(FIGHT_TRAINER* t, FightPokemon* p, u16* out) {
    u16 count = 0;
    u8 i;
    for (i = 0; i < 2; i++) {
        u16 z = fightTrainerAiGetFightPokemonZokuseiDataId(t, p, i);
        if (z != 9) {
            out[count++] = z;
        }
    }
    return count;
}
u8 fightTrainerAiIsFightPokemonZokuseiDataId(FIGHT_TRAINER* t, FightPokemon* p, u16 z) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    if (z == (u16)fightTrainerAiGetFightPokemonZokuseiDataId(t, p, 0) || z == (u16)fightTrainerAiGetFightPokemonZokuseiDataId(t, p, 1)) {
        return 1;
    }
    return 0;
}
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER* t, FightPokemon* p, u16 tokusei) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    if (tokusei == 0) {
        return 0;
    }
    return (u16)_fightTrainerAiGetFightPokemonTokuseiDataId(t, p) == tokusei;
}
}
static u16 _fightTrainerAiGetFightPokemonTokuseiDataId(FIGHT_TRAINER* t, FightPokemon* p) {
    u8 ai;
    Pokemon* pokemon;
    u16 entry;
    fightFloor_GetFightType(0);
    ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    pokemon = fightPokemonGetPokemonPtr(p);
    entry = fightPokemon_GetEntryId(p);
    if (fightTrainerAiDB_GetTokuseiCheckFlag(ai) == 1) {
        if ((u32)t != fightFloorGetFightPokemonPtrToFightTrainerPtr(0, p)) {
            return fightTrainer_GetEnemyStoreTokuseiData(t, entry);
        }
        return pokemonGetTokuseiDataId(pokemon);
    }
    return 0;
}
extern "C" {
u16 fightTrainerAiGetFightPokemonZokuseiDataId(FIGHT_TRAINER* t, FightPokemon* p, u8 idx) {
    u8 type = fightFloor_GetFightType(0);
    u8 ai;
    u16 id;
    ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    id = pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(p));
    if (fightTrainerAiDB_GetZokuseiCheckFlag(ai) == 1) {
        if (fightTrainerIsAllyFightTargetPtr(t, p, type) == 0) {
            return pokemonDB_GetZokuseiDataId(id, idx);
        }
        return pokemonDB_GetZokuseiDataId(id, idx);
    }
    return 9;
}
u8 fightTrainerAiIsFightPokemonNokoriWazaPpHikui(FIGHT_TRAINER* t, FightPokemon* p, u32 idx) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u8 nowPp = fightTrainerAiGetFightPokemonWazaNowPp(t, p, idx);
    u8 maxPp = fightTrainerAiGetFightPokemonWazaMaxPp(t, p, idx);
    u8 value = fightTrainerAiDB_GetWazaNokoriPpValue(ai);
    s32 percent = nowPp * 100 / maxPp;
    u32 result = percent <= value;
    return result;
}
u8 fightTrainerAiGetFightPokemonWazaMaxPp(FIGHT_TRAINER* t, FightPokemon* p, u32 idx) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    fightPokemonGetPokemonPtr(p);
    return pokemonWazaGetMaxPP(fightPokemonGetPokemonPtr(p), idx);
}
u8 fightTrainerAiGetFightPokemonWazaNowPp(FIGHT_TRAINER* t, FightPokemon* p, u32 idx) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    fightPokemonGetPokemonPtr(p);
    return pokemon_GetPokemonWazaPp(fightPokemonGetPokemonPtr(p), idx);
}
u16 fightTrainerAiGetFightPokemonWazaDataId(FIGHT_TRAINER* t, FightPokemon* p, u32 idx) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    fightPokemonGetPokemonPtr(p);
    return pokemon_GetPokemonWazaDataId(fightPokemonGetPokemonPtr(p), idx);
}
u16 fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(FIGHT_TRAINER* t, FightPokemon* p) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightPokemonGetSoubiItemSoubiDataId(p);
}
u16 fightTrainerAiGetFightPokemonSoubiItemDataId(FIGHT_TRAINER* t, FightPokemon* p) {
    fightFloor_GetFightType(0);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return fightPokemonGetSoubiItemDataId(p);
}
u8 fightTrainerAiGetFightPokemonFriend(FIGHT_TRAINER* t, FightPokemon* a) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return pokemon_GetFriend(fightPokemonGetPokemonPtr(a));
}
u8 fightTrainerAiGetWazaRiskFlag(FIGHT_TRAINER* t, u16 waza) {
    if (fightTrainerAiDB_GetWazaRiskFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t))) == 1) {
        return wazaDB_GetRiskFlag(waza);
    }
    return 0;
}
u8 fightTrainerAiGetWazaPp(FIGHT_TRAINER* t, u16 waza) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return wazaDB_GetPp(waza);
}
u8 fightTrainerAiGetWazaRangeId(FIGHT_TRAINER* t, u16 waza) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return wazaDB_GetRangeId(waza);
}
u8 fightTrainerAiIsWazaAvgTakai(FIGHT_TRAINER* t, u16 waza) {
    u8 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    u8 avg = fightTrainerAiGetWazaAvg(t, waza);
    u8 value = fightTrainerAiDB_GetWazaAvgValue(ai);
    u32 result = avg >= value;
    return result;
}
u8 fightTrainerAiGetWazaAvg(FIGHT_TRAINER* t, u16 waza) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    if (fightSeqIsTenkouHit(waza) == 1) {
        return 100;
    }
    if (fightSeqIsAllwaysHit(waza) == 1) {
        return 100;
    }
    return wazaDB_GetAvg(waza);
}
u8 fightTrainerAiIsWazaTypeId(FIGHT_TRAINER* t, u16 waza, u8 type) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return wazaIsWazaTypeId(waza, type);
}
u8 fightTrainerAiGetWazaTypeId(FIGHT_TRAINER* t, u16 waza, u32 idx) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return wazaDB_GetTypeId(waza, idx);
}
u16 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER* t, u16 waza) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return wazaDB_GetIryoku(waza);
}
u8 fightTrainerAiGetWazaAddKoukaAvg(FIGHT_TRAINER* t, u16 waza) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    return wazaDB_GetAddFightKoukaAvg(waza);
}
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER* t, u16 waza, FightOutPokemon* a) {
    u16 hidden;
    u8 ai;
    u8 weather;
    fightTrainer_GetFightTrainerDataId(t);
    ai = fightTrainerDB_GetAiDataId(0);
    weather = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1);
    if (fightTrainerAiDB_GetZokuseiCheckFlag(ai) == 1) {
        if (waza == 0xa5 || wazaCheckDarkWaza(waza) == 1 || waza == 0xf8 || waza == 0x161) {
            return 9;
        }
        if (waza == 0xed) {
            pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(a), 0, &hidden);
            return hidden;
        } else if (waza == 0x137) {
            if (weather == 2) {
                hidden = 0xb;
            } else if (weather == 3) {
                hidden = 5;
            } else if (weather == 1) {
                hidden = 0xa;
            } else if (weather == 4) {
                hidden = 0xf;
            } else if (weather == 5) {
                hidden = 0;
            } else {
                hidden = 0;
            }
            return hidden;
        }
        return wazaDB_GetZokuseiDataId(waza);
    }
    return 9;
}
s32 fightTrainerAiGetValueAryMaxBanme(s32* valueAry, u16 count, u8 useRandom)
{
    s32 banmeAry[16];
    s32 max = -200;
    u16 tieCount = 0;
    u16 i;
    u16 idx;

    for (i = 0; i < 16; i++) {
        banmeAry[i] = -1;
    }
    for (i = 0; i < count; i++) {
        if (max < valueAry[i]) {
            max = valueAry[i];
        }
    }
    for (i = 0; i < count; i++) {
        if (max <= valueAry[i]) {
            banmeAry[tieCount] = i;
            tieCount++;
        }
        if (tieCount >= 16) {
            break;
        }
    }
    if (tieCount == 0) {
        return -1;
    }
    if (tieCount == 1) {
        idx = 0;
    } else if (useRandom == 1) {
        idx = HSD_Rand() % tieCount;
    } else {
        idx = 0;
    }
    return banmeAry[idx];
}
s32 fightTrainerAiReviseValueByAddsubDataId(s32 value, s32 x, FIGHT_TRAINER* t, u16 id) {
    return fightTrainerAiReviseValue(value, x, fightTrainerAiValueAddsubDB_GetValue(id));
}
s32 fightTrainerAiAddValueByAddsubDataId(s32 value, FIGHT_TRAINER* t, u16 id) {
    return fightTrainerAiAddValue(value, fightTrainerAiValueAddsubDB_GetValue(id));
}
s32 fightTrainerAiReviseValue(s32 value, s32 a, s32 b) {
    s16 ratio = (u8)a * 100 / 100;
    s16 delta = (ratio - 50) * b / 50;
    return fightTrainerAiAddValue(value, delta);
}
#pragma push
#pragma optimization_level 2
#pragma opt_common_subs off
s32 fightTrainerAiAddValue(s32 value, s32 delta)
{
    if (delta > 0) {
        if (value + delta > 200) {
            return 200;
        }
        value += delta;
        return value;
    } else {
        if (delta >= 0) {
            return value;
        }
        if (value + delta < -200) {
            return -200;
        }
        value += delta;
        return value;
    }
}
#pragma pop
void fightTrainerAiSetAllyPokemon(FIGHT_TRAINER* t) {
    u16 wazas[8];
    FightOutPokemon* outs[8];
    FightPokemon* pokes[8];
    u16 outCount;
    u16 pokeCount;
    u16 i;
    u16 j;
    u16 k;
    outCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, outs, 0, 1);
    pokeCount = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, pokes, 1, 1);
    for (i = 0; i < pokeCount; i++) {
        FightPokemon* fp = pokes[i];
        if (fp != 0) {
            for (j = 0; j < outCount; j++) {
                FightOutPokemon* o = outs[j];
                if (o != 0 && fightOutPokemonGetFightEntryId(o) >= 0) {
                    u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, o, wazas, 0, 0);
                    u16 maxHp = fightOutPokemonMaxHpWaruValue(o, 1);
                    for (k = 0; k < n; k++) {
                        s32 damage = 0;
                        u16 waza = wazas[k];
                        if (waza != 0 && waza != 0x176 && fightTrainerAiGetWazaZokuseiDataId(t, waza, o) != 9) {
                            u16 index;
                            if (fightTrainerAiIsWazaTypeId(t, waza, 1) == 1) {
                                damage = fightTrainerAiWazaDoWazaDamageFightPokemonFunc(t, o, waza, fp, 0);
                            }
                            index = j + k;
                            fightPokemon_SetAiDamage(fp, index, 0, damage * 100 / maxHp);
                            fightPokemon_SetAiDamage(fp, index, 1, waza);
                        }
                    }
                }
            }
        }
    }
}
}
