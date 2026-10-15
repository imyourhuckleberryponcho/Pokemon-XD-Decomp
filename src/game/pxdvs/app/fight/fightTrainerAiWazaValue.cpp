#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FightPokemon;
struct FightOutPokemon { u32 data[548]; };
struct FightSide;

extern "C" {
u16 HSD_Rand();
s32 fightTrainerGetStatus(u32, u32, u32, u32);
u16 fightFloor_GetTikeiDataId(u32);
u16 tikeiDataBiosGetWazaId(u8);
FightSide* fightTargetGetPtrAsNowFightType(u32, FightOutPokemon*);
u8 fightSideIsJoutaiDataId(FightSide*, u16);
u8 fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(u32, FIGHT_TRAINER*, u8, u8, u16, FightOutPokemon*);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(u32, FIGHT_TRAINER*, FightOutPokemon**, u8, u8);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(u32, FIGHT_TRAINER*, FightPokemon**, u8, u8);
u16 fightTrainerAiCheckOumu(FIGHT_TRAINER*, FightOutPokemon*);
s32 fightTrainerAiWazaDoWazaValueFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*, u8);
s32 fightTrainerAiAddValue(s32, s32);
s32 fightTrainerAiAddValueByAddsubDataId(s32, FIGHT_TRAINER*, u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsFightOutPokemonNokoriHp(FIGHT_TRAINER*, FightOutPokemon*, s32, f32);
u8 fightTrainerAiGetWazaAddKoukaAvg(FIGHT_TRAINER*, u16);
s32 fightTrainerAiCmpFightOutPokemonSubayasa(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonAbiCntAvd(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonAbiCntAvg(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonLastUseWazaDataId(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER*, FightOutPokemon*, u16*, u8, u8);
u8 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER*, u32, u8);
u16 fightTrainerAiGetFightOutPokemonSpeAtk(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonPhyAtk(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonPhyDef(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonSpeDef(FIGHT_TRAINER*, FightOutPokemon*);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
u8 fightTrainerAiIsFightPokemonJoutaiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
extern const u16 KonranWazaTbl[];
extern const u16 joutaiIzyouWazaTbl[];
u16 fightTrainerAiGetFightOutPokemonPokemonDataId(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
u8 fightTrainerAiDB_GetWazaAvgValue(u16);
u8 wazaDB_GetAvg(u16);
u16 fightOutPokemonMaxHpWaruValue(FightOutPokemon*, u16);
u16 fightOutPokemonNowHpWaruValue(FightOutPokemon*, u16);
u8 fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_TRAINER*, u32, FightOutPokemon*, u32);
struct Pokemon;
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
u8 pokemonIsDarkPokemon(Pokemon*);
u16 fightTrainerAiGetFightPokemonPokemonDataId(FIGHT_TRAINER*, FightPokemon*);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonMaxHp(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiWazaDoWazaHitFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
bool fightTrainerAiIsFightOutPokemonPhyAtkCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
bool fightTrainerAiIsFightOutPokemonPhyDefCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
bool fightTrainerAiIsFightOutPokemonSpeAtkCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
bool fightTrainerAiIsFightOutPokemonSpeDefCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
bool fightTrainerAiIsFightOutPokemonNimblenessCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
bool fightTrainerAiIsFightOutPokemonAvoidCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
s32 fightTrainerAiValueAddsubDB_GetValue(u16);
u16 fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonSoubiItemDataId(FIGHT_TRAINER*, FightOutPokemon*);
typedef s32 (*WazaValueFunc)(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
WazaValueFunc wazaDB_GetFightTrainerAiWazaValueFuncPtr(u16);
s32 fightTrainerAiWazaValueJisin(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueJibaku(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueNull(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
extern u32* waza_data_number;
u8 fightTrainerAiIsWazaTypeId(FIGHT_TRAINER*, u16, u8);
u8 fightOutPokemon_GetSuccessCnt(FightOutPokemon*);
s16 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon*, u16);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER*, u16, FightOutPokemon*);
u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER*, FightOutPokemon*, u16);
extern const u16 moukakeiTbl[];
extern const u16 statusUpKinomiTbl[];
u8 fightFloor_GetFightTypeFightoutPokemonNum(u32);
s16 fightSideGetCountAsJoutaiDataId(FightSide*, u16);
u16 fightTrainerAiGetFightOutPokemonUsedItemDataId(FIGHT_TRAINER*, FightOutPokemon*);
s32 fightTrainerAiWazaValueSubayasaDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueKougekiDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueBougyoDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueTokubouDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueMeityuuDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueKaihiDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueKusuguruDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s8 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon*, u16);
s8 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon*, u16);
u16 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(FIGHT_TRAINER*, FightOutPokemon*, u16*);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16, s32);
s32 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER*, u16);
u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetWazaPp(FIGHT_TRAINER*, u16);
void* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon*);
u8 fightActionCheckValid(void*);
u16 fightActionGetKindDataId(void*);
u16 fightOutPokemonGetUseWazaDataId(FightOutPokemon*);
u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon*);
s32 fightTrainerAiGetFightOutPokemonNowHpPercentage(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u8);
u32 fightFloor_GetFightType(u32);
u16 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon*, u16);
u8 zokuseiBiosGetWazaKind(u16);
u8 fightTrainerAiIsFightPokemonJoutaiNormal(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiIsFightPokemonZokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
FIGHT_TRAINER* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(u32, FightOutPokemon*);
u32 fightTrainerSearchIrekaeFightPokemon(FIGHT_TRAINER*, s16*);
u8 tikeiDataBiosGetFightKoukaId(u8);
s32 fightTrainerAiWazaValueTuikaDoku(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueTuikaNemuri(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueTuikouMeityuuDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueTuikouBougyoDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueOororabiimu(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueTuikouSubayasaDaun(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueTuikouKonran(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueTuikaHirumi(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaValueTuikaMahi(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
u8 fightSeqIsDoItemGetWaza(FightOutPokemon*);
u8 itemDataCheckValid(u16);
u8 fightTrainerAiCheckJoutaiKieWazaHitWazaDataId(FIGHT_TRAINER*, u8, u16);
}

typedef bool (*AbiTakaiFunc)(FIGHT_TRAINER*, FightOutPokemon*);
static s32 _fightTrainerAiWazaValueSubNouryokuKyouka(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*, s32, u8, u16, u16, u16, u16, AbiTakaiFunc);
static u8 _fightTrainerAiWazaValueIsAllyHaveWazaDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
static s8 _fightTrainerAiWazaValueIsFightOutPokemonNeoki(FIGHT_TRAINER*, FightOutPokemon*);
static u8 _fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(FIGHT_TRAINER*, FightOutPokemon**, u16, u8, u8);
static u8 _fightTrainerAiWazaValueAbiCntCheck(FIGHT_TRAINER*, FightOutPokemon*, u8, u8);

extern "C" {

#pragma dont_inline on

s32 fightTrainerAiWazaValueMeromero(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xd5, target) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x287);
    return handle;
}

s32 fightTrainerAiWazaValueDarkPanic(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(t, target) <= 5) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x284);
    return handle;
}

s32 fightTrainerAiWazaValueDarkMist(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    u16 wazaAry[8];
    s32 handle = 0;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    u8 avg = fightTrainerAiDB_GetWazaAvgValue(fightTrainer_GetFightTrainerDataId(t));
    u16 i;
    u16 j;
    u8 flag = 0;
    for (i = 0; i < count; i++) {
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 1);
        if (n != 0) {
            for (j = 0; j < n; j++) {
                if (wazaDB_GetAvg(wazaAry[j]) < avg) {
                    flag = 1;
                    break;
                }
            }
        }
    }
    if (flag) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x282);
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(t, target) <= 5) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x283);
    return handle;
}

s32 fightTrainerAiWazaValueDarkHalf(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* aryA[8];
    FightOutPokemon* aryB[8];
    s32 handle;
    u8 i;
    u16 countA = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryA, 1, 1);
    u16 countB = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryB, 0, 1);
    u16 hpB = 0;
    for (i = 0; i < countB; i++) {
        u16 max = fightOutPokemonMaxHpWaruValue(aryB[i], 1);
        u16 now = fightOutPokemonNowHpWaruValue(aryB[i], 2);
        hpB += max * now / 100;
    }
    u16 hpA = 0;
    for (i = 0; i < countA; i++) {
        u16 max = fightOutPokemonMaxHpWaruValue(aryA[i], 1);
        u16 now = fightOutPokemonNowHpWaruValue(aryA[i], 2);
        hpA += max * now / 100;
    }
    handle = fightTrainerAiAddValue(0, (hpB / hpA - 1) * fightTrainerGetStatus(0, 0x27f, 0x3e, 0));
    handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x280);
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(t, target) <= 5) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x281);
    return handle;
}

s32 fightTrainerAiWazaValueDarkEnd(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    u16 hp;
    int now;
    s32 handle;
    u16 damage;
    handle = 0;
    hp = fightOutPokemonMaxHpWaruValue(target, 1);
    damage = hp * fightTrainerAiWazaDoWazaDamageFunc(t, self, waza, target, 1) / 100;
    hp = fightOutPokemonMaxHpWaruValue(self, 1);
    now = fightOutPokemonNowHpWaruValue(self, 2);
    handle = fightTrainerAiAddValue(handle, (damage / (u16)(hp * now / 100) - 1) * fightTrainerGetStatus(0, 0x27d, 0x3e, 0));
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(t, target) <= 5) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x27e);
    return handle;
}

s32 fightTrainerAiWazaValueDarkRemove(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    FightSide* side = fightTargetGetPtrAsNowFightType(2, target);
    if (fightSideIsJoutaiDataId(side, 0x49) == 1 || fightSideIsJoutaiDataId(side, 0x48) == 1 || fightSideIsJoutaiDataId(side, 0x4b) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x26d);
    return handle;
}

s32 fightTrainerAiWazaValueDarkHold(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u8 i;
    u8 irekae = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(t, 0, target, 0);
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x272);
    }
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x273);
    }
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x274);
    }
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 5) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x275);
    }
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x276);
    }
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x277);
    }
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x278);
    }
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x279);
    }
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x27a);
    }
    if (fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1) == 5) {
        for (i = 0; i < count; i++) {
            if (!pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(ary[i]))) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x27b);
        }
    }
    if (irekae) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x27c);
    return handle;
}

s32 fightTrainerAiWazaValueDarkWeather(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* ary[24];
    u16 j;
    u16 i;
    s32 handle = 0;
    u8 tenkou = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 0);
    u16 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, ary, 1, 1);
    if (tenkou != 5) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x19a);
    for (i = 0; i < count; i++) {
        if (pokemonIsDarkPokemon(fightPokemonGetPokemonPtr(ary[i])) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x19b);
            break;
        }
    }
    for (j = 0; j < count; j++) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(t, ary[j]) == 0x181) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x19c);
            break;
        }
    }
    if (tenkou == 5) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x19d);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x16f, 0) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x19e);
    return handle;
}

s32 fightTrainerAiWazaValueHuuin(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    if (fightOutPokemon_GetFightoutTurnCount(self) != 0) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x285);
    while ((s32)count > 0) {
        if (fightOutPokemon_GetFightoutTurnCount(ary[0]) != 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x286);
        break;
    }
    return handle;
}

s32 fightTrainerAiWazaValueMahi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    for (u8 i = 0; i < 0x12; i++) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, joutaiIzyouWazaTbl[i], target) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x18d);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueKonran(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    for (u8 i = 0; i < 5; i++) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, KonranWazaTbl[i], target) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x18d);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueYumekui(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle;
    u16 now = fightTrainerAiGetFightOutPokemonNowHp(t, self);
    u16 max = fightTrainerAiGetFightOutPokemonMaxHp(t, self);
    s32 v = fightTrainerAiWazaDoWazaDamageFunc(t, self, waza, target, 1) / 2 * 100 / max;
    if (v > 100) v = 100;
    handle = fightTrainerAiAddValue(0, v / fightTrainerGetStatus(0, 0x26e, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x26f);
    return handle;
}

s32 fightTrainerAiWazaValueKawarawari(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    FightSide* side = fightTargetGetPtrAsNowFightType(2, target);
    if (fightSideIsJoutaiDataId(side, 0x49) == 1 || fightSideIsJoutaiDataId(side, 0x48) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x26b);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x26c);
    return handle;
}

s32 fightTrainerAiWazaValueTeiryouDameeji(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiGetFightOutPokemonPokemonDataId(t, target) == 0xd5) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x26a);
    return handle;
}

s32 fightTrainerAiWazaValueHikarinokabe(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 spa = fightTrainerAiGetFightOutPokemonSpeAtk(t, target);
    u16 pha = fightTrainerAiGetFightOutPokemonPhyAtk(t, target);
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    if (fightTrainerAiWazaDoWazaHitFunc(t, self, waza, target) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x267);
    if (pha < spa) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x268);
    if (last == 0x118) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x269);
    return handle;
}

s32 fightTrainerAiWazaValueRihurekutaa(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 spa = fightTrainerAiGetFightOutPokemonSpeAtk(t, target);
    u16 pha = fightTrainerAiGetFightOutPokemonPhyAtk(t, target);
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    if (fightTrainerAiWazaDoWazaHitFunc(t, self, waza, target) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x264);
    if (pha > spa) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x265);
    if (last == 0x118) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x266);
    return handle;
}

s32 fightTrainerAiWazaValueOnibi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u16 j;
    u16 spa = fightTrainerAiGetFightOutPokemonSpeAtk(t, target);
    u16 pha = fightTrainerAiGetFightOutPokemonPhyAtk(t, target);
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    for (u16 i = 0; i < count; i++) {
        u16 id = fightTrainerAiGetFightOutPokemonPokemonDataId(t, ary[i]);
        if (id == 0xca || id == 0x168 || id == 0x12f || id == 0xd5) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x260);
            break;
        }
    }
    if (pha > spa) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x261);
    if (last == 0x11f) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x262);
    for (j = 0; j < 0x12; j++) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, joutaiIzyouWazaTbl[j], target) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x263);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueDoku(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u16 j;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    for (u16 i = 0; i < count; i++) {
        u16 id = fightTrainerAiGetFightOutPokemonPokemonDataId(t, ary[i]);
        if (id == 0xca || id == 0x168 || id == 0x12f || id == 0xd5) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x25d);
            break;
        }
    }
    if (last == 0x11f) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x25e);
    for (j = 0; j < 0x12; j++) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, joutaiIzyouWazaTbl[j], target) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x18d);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueBatontatti(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonAllAbiCntTakai(t, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x25c);
    return handle;
}

s32 fightTrainerAiWazaValueHaradaiko(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, 0, 0x258, 0x259, 0x25a, 0, fightTrainerAiIsFightOutPokemonPhyAtkCntTakai);
    if (fightTrainerAiIsFightOutPokemonNokoriHp(t, self, -1, 0.5f) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x25b);
    return handle;
}

s32 fightTrainerAiWazaValueMarukunaru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    u16 wazaAry[8];
    s32 handle;
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, self, wazaAry, 0, 1);
    handle = _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, self), 0x254, 0, 0x256, 0x257, fightTrainerAiIsFightOutPokemonPhyDefCntTakai);
    for (u16 i = 0; i < count; i++) {
        if (wazaAry[i] == 0xcd || wazaAry[i] == 0x12d) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x255);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueMeisou(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, self), 0x250, 0x251, 0x252, 0x253, fightTrainerAiIsFightOutPokemonSpeAtkCntTakai);
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, handle, fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, self), 0x250, 0, 0x252, 0, fightTrainerAiIsFightOutPokemonSpeDefCntTakai);
}

s32 fightTrainerAiWazaValueRyuunomai(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, self), 0x24c, 0x24d, 0x24e, 0x24f, fightTrainerAiIsFightOutPokemonPhyAtkCntTakai);
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, handle, fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, self), 0x24c, 0, 0x24e, 0, fightTrainerAiIsFightOutPokemonNimblenessCntTakai);
}

s32 fightTrainerAiWazaValueBirudoAppu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, self), 0x248, 0x249, 0x24a, 0x24b, fightTrainerAiIsFightOutPokemonPhyAtkCntTakai);
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, handle, fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, self), 0x248, 0, 0x24a, 0, fightTrainerAiIsFightOutPokemonPhyDefCntTakai);
}

s32 fightTrainerAiWazaValueKosumopawaa(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, self), 0x244, 0x245, 0x246, 0x247, fightTrainerAiIsFightOutPokemonPhyDefCntTakai);
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, handle, fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, self), 0x244, 0, 0x246, 0, fightTrainerAiIsFightOutPokemonSpeDefCntTakai);
}

s32 fightTrainerAiWazaValueKaihirituAppu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntAvd(t, self), 0x240, 0x241, 0x242, 0x243, fightTrainerAiIsFightOutPokemonAvoidCntTakai);
}

s32 fightTrainerAiWazaValueDowasure(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, self), 0x23c, 0x23d, 0x23e, 0x23f, fightTrainerAiIsFightOutPokemonSpeDefCntTakai);
}

s32 fightTrainerAiWazaValueTokukouAppu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(t, self), 0x238, 0x239, 0x23a, 0x23b, fightTrainerAiIsFightOutPokemonSpeAtkCntTakai);
}

s32 fightTrainerAiWazaValueKousokuidou(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, self), 0x234, 0x235, 0x236, 0x237, fightTrainerAiIsFightOutPokemonNimblenessCntTakai);
}

s32 fightTrainerAiWazaValueBougyoAppu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, self), 0x230, 0x231, 0x232, 0x233, fightTrainerAiIsFightOutPokemonPhyDefCntTakai);
}

s32 fightTrainerAiWazaValueKougekiAppu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    return _fightTrainerAiWazaValueSubNouryokuKyouka(t, self, waza, target, 0, fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, self), 0x22c, 0x22d, 0x22e, 0x22f, fightTrainerAiIsFightOutPokemonPhyAtkCntTakai);
}

}

static s32 _fightTrainerAiWazaValueSubNouryokuKyouka(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target, s32 handle, u8 abiCnt, u16 id1, u16 id2, u16 id3, u16 id4, AbiTakaiFunc func) {
    if (id1 != 0 && !func(t, self)) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, id1);
    if (id2 != 0 && _fightTrainerAiWazaValueIsAllyHaveWazaDataId(t, self, 0x10a) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, id2);
    if (id3 != 0 && func(t, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, id3);
    if (id4 != 0) {
        s32 n = abiCnt - 6;
        if (n < 0) n = 0;
        handle = fightTrainerAiAddValue(handle, n * fightTrainerAiValueAddsubDB_GetValue(id4));
    }
    return handle;
}

static u8 _fightTrainerAiWazaValueIsAllyHaveWazaDataId(FIGHT_TRAINER* t, FightOutPokemon* self, u16 id) {
    FightOutPokemon* ary[8];
    u16 wazaAry[8];
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    for (u16 i = 0; i < count; i++) {
        if (self == ary[i]) continue;
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 1);
        if (n == 0) continue;
        for (u16 j = 0; j < n; j++) {
            if (id == wazaAry[j]) return 1;
        }
    }
    return 0;
}

extern "C" {

s32 fightTrainerAiWazaValuetorikku(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 item = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, self);
    if (item == 0x1d || item == 0x18) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x22a);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x3c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x22b);
    return handle;
}

s32 fightTrainerAiWazaValueSukirusuwappu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, self, 0x36) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, self, 0x10) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x228);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x36) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x10) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x229);
    return handle;
}

s32 fightTrainerAiWazaValueMamoru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    u16 wazaAry[8];
    u8 allyJisin;
    u8 allyJibaku;
    u8 queuedJisin;
    u8 queuedJibaku;
    s32 handle;
    u16 count;
    u16 i;
    u16 j;
    WazaValueFunc func;
    handle = 0;
    allyJisin = 0;
    allyJibaku = 0;
    queuedJisin = 0;
    queuedJibaku = 0;
    count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, self);
    fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    for (i = 0; i < count; i++) {
        if (self == ary[i]) continue;
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 1);
        if (n == 0) continue;
        for (j = 0; j < n; j++) {
            func = wazaDB_GetFightTrainerAiWazaValueFuncPtr(wazaAry[j]);
            if (func == 0) func = fightTrainerAiWazaValueNull;
            if (func == fightTrainerAiWazaValueJisin) allyJisin = 1;
            if (func == fightTrainerAiWazaValueJibaku) allyJibaku = 1;
        }
    }
    for (i = 0; i < *waza_data_number; i++) {
        func = wazaDB_GetFightTrainerAiWazaValueFuncPtr(i);
        if (func == 0) func = fightTrainerAiWazaValueNull;
        if ((func == fightTrainerAiWazaValueJisin || func == fightTrainerAiWazaValueJibaku) && fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, i, 0) == 1) {
            if (func == fightTrainerAiWazaValueJisin) queuedJisin = 1;
            if (func == fightTrainerAiWazaValueJibaku) queuedJibaku = 1;
        }
    }
    if (allyJisin == 1 || allyJibaku == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x21f);
    if (queuedJisin == 1 || queuedJibaku == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x220);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, self, 3) == 1 && fightTrainerAiIsWazaTypeId(t, last, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x221);
    if ((last == 0xb6 || last == 0xc5) && fightOutPokemon_GetSuccessCnt(self) != 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x222);
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, self, 7) == 1) {
        if (allyJibaku == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x223);
        if (queuedJibaku == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x224);
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, self, 2) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, self, 0x1a) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, self, 0x19) == 1) {
        if (allyJisin == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x225);
        if (queuedJisin == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x226);
    }
    for (i = 0; i < count; i++) {
        if (self == ary[i]) continue;
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 1);
        if (n == 0) continue;
        for (j = 0; j < n; j++) {
            if (wazaAry[j] == 0x10a) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x227);
                break;
            }
        }
        if (j < n) break;
    }
    return handle;
}

s32 fightTrainerAiWazaValueTakuwaeru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s16 count;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x2d) == 1) {
        count = fightOutPokemonGetCountAsJoutaiDataId(self, 0x2d);
    } else {
        count = 0;
    }
    if (count == 0) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x21c);
    } else if (count == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x21d);
    } else if (count == 2) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x21e);
    }
    return handle;
}

s32 fightTrainerAiWazaValueJyuuden(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    u16 wazaAry[8];
    s32 handle = 0;
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, self, wazaAry, 0, 1);
    for (u16 i = 0; i < count; i++) {
        if (wazaAry[i] != 0x10c && fightTrainerAiGetWazaZokuseiDataId(t, wazaAry[i], self) == 0xd) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x21a);
            break;
        }
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x24) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x21b);
    return handle;
}

s32 fightTrainerAiWazaValueNemuriKoudou(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 8) == 1) {
        if (_fightTrainerAiWazaValueIsFightOutPokemonNeoki(t, self) == 0) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x218);
        if (_fightTrainerAiWazaValueIsFightOutPokemonNeoki(t, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x219);
    }
    return handle;
}

s32 fightTrainerAiWazaValueMigawari(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    u16 wazaAry[8];
    s32 handle;
    s32 rest;
    u8 j;
    u8 i;
    u8 k;
    handle = 0;
    u16 max = fightOutPokemonMaxHpWaruValue(self, 1);
    u16 now = fightOutPokemonNowHpWaruValue(self, 1);
    u16 quarter = fightOutPokemonMaxHpWaruValue(self, 4);
    u16 item = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, self);
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, self, wazaAry, 0, 1);
    if (fightTrainerAiIsFightOutPokemonNokoriHp(t, self, 1, 0.8f) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x214);
    for (i = 0; i < 4; i++) {
        if (fightAi_GetTokuseiHaveFlag(t, self, moukakeiTbl[i]) == 1) {
            if (now - quarter <= fightOutPokemonMaxHpWaruValue(self, 3) && now - quarter > 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x215);
            break;
        }
    }
    rest = now - quarter;
    if (rest <= max * 20 / 100 && rest > 0) {
        for (j = 0; j < count; j++) {
            if (wazaAry[j] == 0xaf || wazaAry[j] == 0xb3) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x216);
        }
    }
    if (rest <= fightOutPokemonMaxHpWaruValue(self, 4) && rest > 0) {
        for (k = 0; k < 7; k++) {
            if (item == statusUpKinomiTbl[k]) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x217);
                break;
            }
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueSawagu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    u16 wazaAry[8];
    s32 handle = 0;
    u16 i;
    u16 j;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    for (i = 0; i < count; i++) {
        if (self != ary[i] && _fightTrainerAiWazaValueIsFightOutPokemonNeoki(t, ary[i]) == 0) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x211);
            break;
        }
    }
    for (i = 0; i < count; i++) {
        if (self == ary[i]) continue;
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 1);
        if (n == 0) continue;
        for (j = 0; j < n; j++) {
            if (wazaAry[j] == 0x9c) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x212);
                break;
            }
        }
        if (j < n) break;
    }
    if (_fightTrainerAiWazaValueIsFightOutPokemonNeoki(t, target) == 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x213);
    return handle;
}

s32 fightTrainerAiWazaValueOomugaesi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    u16 id = fightTrainerAiCheckOumu(t, self);
    if (id != waza && id != 0) return fightTrainerAiWazaDoWazaValueFunc(t, self, id, target);
    return 0;
}

s32 fightTrainerAiWazaValueRandamuSentaku(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 status = fightTrainerGetStatus(0, 0x210, 0x3e, 0);
    return fightTrainerAiAddValue(0, HSD_Rand() % (status + 1));
}

s32 fightTrainerAiWazaValueHurahuradansu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    if (fightFloor_GetFightTypeFightoutPokemonNum(0) >= 2) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x20c);
    for (u16 i = 0; i < count; i++) {
        if (self != ary[i]) {
            u16 item = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, ary[i]);
            if (item == 8 || item == 9) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x20d);
                break;
            }
        }
    }
    for (u16 j = 0; j < count; j++) {
        if (self != ary[j] && fightTrainerAiIsFightOutPokemonTokuseiDataId(t, ary[j], 0x14) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x20e);
            break;
        }
    }
    for (u16 k = 0; k < count; k++) {
        if (self != ary[k]) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x20f);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueMakibisi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s16 count;
    FightSide* side = fightTargetGetPtrAsNowFightType(2, target);
    if (fightSideIsJoutaiDataId(side, 0x4a) == 1) {
        count = fightSideGetCountAsJoutaiDataId(side, 0x4a);
    } else {
        count = 0;
    }
    if (count == 0) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x209);
    } else if (count == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x20a);
    } else if (count == 2) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x20b);
    }
    return handle;
}

s32 fightTrainerAiWazaValueRisaikuru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiGetFightOutPokemonUsedItemDataId(t, self) != 0) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x208);
    return handle;
}

s32 fightTrainerAiWazaValueSiroikiri(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    if (last != 0 && last != 0xffff && last != 0x176 && last != 0x163) {
        WazaValueFunc func = wazaDB_GetFightTrainerAiWazaValueFuncPtr(last);
        if (func == 0) func = fightTrainerAiWazaValueNull;
        if (func == fightTrainerAiWazaValueSubayasaDaun || func == fightTrainerAiWazaValueKougekiDaun || func == fightTrainerAiWazaValueBougyoDaun || func == fightTrainerAiWazaValueTokubouDaun || func == fightTrainerAiWazaValueMeityuuDaun || func == fightTrainerAiWazaValueKaihiDaun || func == fightTrainerAiWazaValueKusuguruDaun) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x207);
    }
    return handle;
}

s32 fightTrainerAiWazaValueJikoanji(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (_fightTrainerAiWazaValueAbiCntCheck(t, target, 8, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x203);
    if (_fightTrainerAiWazaValueAbiCntCheck(t, target, 0xa, 0xc) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x204);
    if (_fightTrainerAiWazaValueAbiCntCheck(t, target, 3, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x205);
    if (_fightTrainerAiWazaValueAbiCntCheck(t, target, 0, 2) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x206);
    return handle;
}

s32 fightTrainerAiWazaValueKuroikiri(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* aryA[8];
    FightOutPokemon* aryB[8];
    s32 handle = 0;
    u16 countA = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryA, 1, 1);
    u16 countB = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryB, 0, 1);
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(t, aryB, countB, 8, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1fb);
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(t, aryA, countA, 3, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1fc);
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(t, aryB, countB, 0xa, 0xc) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1fd);
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(t, aryA, countA, 0, 2) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1fe);
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(t, aryA, countA, 8, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ff);
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(t, aryB, countB, 3, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x200);
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(t, aryA, countA, 0xa, 0xc) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x201);
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(t, aryB, countB, 0, 2) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x202);
    return handle;
}

}

static u8 _fightTrainerAiWazaValueKuroikiriSubAbiCntCheck(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 count, u8 lo, u8 hi) {
    for (u16 i = 0; i < count; i++) {
        if (_fightTrainerAiWazaValueAbiCntCheck(t, ary[i], lo, hi) == 1) return 1;
    }
    return 0;
}

extern "C" {

s32 fightTrainerAiWazaValueTedasuke(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    u16 wazaAry[8];
    s32 handle = 0;
    u16 i;
    u16 j;
    u8 flag;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    flag = 0;
    for (i = 0; i < *waza_data_number; i++) {
        if (i != 0 && i != 0x176 && i != 0x163 && fightTrainerAiIsWazaTypeId(t, i, 1) && fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, i, 0) == 1) flag = 1;
    }
    if (flag == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1f5);
    for (i = 0; i < count; i++) {
        if (self == ary[i]) continue;
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 1);
        if (n == 0) continue;
        for (j = 0; j < n; j++) {
            if (fightTrainerAiIsWazaTypeId(t, wazaAry[j], 1)) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1f6);
                break;
            }
        }
    }
    flag = 1;
    for (i = 0; i < count; i++) {
        if (self == ary[i]) continue;
        void* action = fightOutPokemon_GetFightActionBuffPtr(ary[i]);
        if (action == 0) continue;
        if (!fightActionCheckValid(action)) continue;
        if (fightActionGetKindDataId(action) != 0x13) {
            flag = 0;
            break;
        }
        u16 use = fightOutPokemonGetUseWazaDataId(ary[i]);
        if (!fightTrainerAiIsWazaTypeId(t, use, 1)) {
            flag = 0;
            break;
        }
    }
    if (!flag) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1f7);
    for (i = 0; i < count; i++) {
        if (self != ary[i] && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 0x12) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1f8);
            break;
        }
    }
    for (i = 0; i < count; i++) {
        if (self != ary[i] && fightOutPokemon_GetNamakeFlag(ary[i])) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1f9);
            break;
        }
    }
    for (i = 0; i < count; i++) {
        if (self != ary[i] && _fightTrainerAiWazaValueIsFightOutPokemonNeoki(t, ary[i]) == 0) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1fa);
            break;
        }
    }
    return handle;
}

}

static s8 _fightTrainerAiWazaValueIsFightOutPokemonNeoki(FIGHT_TRAINER* t, FightOutPokemon* p) {
    s8 n;
    s8 now;
    if (!fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 8)) return -1;
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, p, 0x30) == 1) {
        n = 2;
    } else {
        n = 1;
    }
    now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 8);
    now += n;
    if (now >= fightOutPokemonGetKaisuuJoutaiDataId(p, 8)) return 1;
    return 0;
}

extern "C" {

s32 fightTrainerAiWazaValueKyouseikoutai(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s16 count;
    FightSide* side = fightTargetGetPtrAsNowFightType(2, target);
    if (fightSideIsJoutaiDataId(side, 0x4a) == 1) {
        count = fightSideGetCountAsJoutaiDataId(side, 0x4a);
    } else {
        count = 0;
    }
    if (_fightTrainerAiWazaValueAbiCntCheck(t, target, 8, 0xc) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1f1);
    if (count == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1f2);
    } else if (count == 2) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1f3);
    } else if (count == 3) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1f4);
    }
    return handle;
}

s32 fightTrainerAiWazaValueYokodori(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle;
    u16 selfLast;
    u16 selfSelect;
    u16 count;
    u16 i;
    u16 last;
    handle = 0;
    selfLast = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, self);
    selfSelect = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(t, self);
    last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    if (last != 0 && last != 0xffff && last != 0x176 && last != 0x163 && fightTrainerAiIsWazaTypeId(t, last, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1ee);
    for (i = 0; i < count; i++) {
        u16 id = fightTrainerAiGetFightOutPokemonPokemonDataId(t, ary[i]);
        if (id == 0x12e || id == 0xd4 || id == 0x177) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ef);
            break;
        }
    }
    if (selfLast == 0x121 || selfSelect == 0x121) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1f0);
    return handle;
}

s32 fightTrainerAiWazaValueKonoyubitomare(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* aryA[8];
    FightOutPokemon* aryB[8];
    u16 zokusei[2];
    s32 handle = 0;
    u8 flag;
    u16 i;
    u16 j;
    u16 k;
    u16 countA = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryA, 1, 1);
    u16 countB = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryB, 0, 1);
    flag = 0;
    for (i = 0; i < countB; i++) {
        u16 n = fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(t, aryB[i], zokusei);
        for (j = 0; j < n; j++) {
            for (k = 0; k < countA; k++) {
                if (self != aryA[k] && fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(t, aryA[k], zokusei[j], fightTrainerAiGetWazaIryoku(t, waza)) == 0x41) flag = 1;
            }
        }
    }
    if (flag == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1eb);
    for (i = 0; i < countA; i++) {
        if (self != aryA[i] && fightTrainerAiGetFightOutPokemonKeyPlayerFlag(t, aryA[i]) == 2) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ec);
            break;
        }
    }
    for (i = 0; i < countB; i++) {
        u16 id = fightTrainerAiGetFightOutPokemonPokemonDataId(t, aryB[i]);
        if (id == 0x12e || id == 0xd4 || id == 0x177) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ed);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueKoukanKinsi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1e1);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1e2);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1e3);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 5) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1e4);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1e5);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1e6);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1e7);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1e8);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1e9);
    if (fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1) == 5 && !pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(target))) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ea);
    return handle;
}

s32 fightTrainerAiWazaValueKanasibari(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    if (fightTrainerAiCmpFightOutPokemonSubayasa(t, self, target) > 0 && last != 0 && last != 0xffff && last != 0x176 && last != 0x163 && fightTrainerAiIsWazaTypeId(t, last, 1) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1e0);
    return handle;
}

s32 fightTrainerAiWazaValueMitizure(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonNokoriHp(t, self, -1, 0.1f) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1df);
    } else if (fightTrainerAiIsFightOutPokemonNokoriHp(t, self, -1, 0.3f) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1de);
    } else if (fightTrainerAiIsFightOutPokemonNokoriHp(t, self, -1, 0.5f) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1dd);
    }
    return handle;
}

s32 fightTrainerAiWazaValueUrami(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    if (last != 0 && last != 0xffff && last != 0x176 && last != 0x163 && fightTrainerAiCmpFightOutPokemonSubayasa(t, self, target) > 0) {
        u8 pp = fightTrainerAiGetWazaPp(t, last);
        if (pp <= 5) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1db);
        } else if (pp <= 10) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1dc);
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueOdareru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 spa = fightTrainerAiGetFightOutPokemonSpeAtk(t, target);
    u16 pha = fightTrainerAiGetFightOutPokemonPhyAtk(t, target);
    u16 phd = fightTrainerAiGetFightOutPokemonPhyDef(t, target);
    if (pha > spa) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1d6);
    if (pha > phd) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1d7);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1d8);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1d9);
    for (u8 i = 0; i < 5; i++) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, KonranWazaTbl[i], target) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1da);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueIbaru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 spa = fightTrainerAiGetFightOutPokemonSpeAtk(t, target);
    u16 pha = fightTrainerAiGetFightOutPokemonPhyAtk(t, target);
    u16 phd = fightTrainerAiGetFightOutPokemonPhyDef(t, target);
    if (spa > pha) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1d1);
    if (pha > phd) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1d2);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1d3);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1d4);
    for (u8 i = 0; i < 5; i++) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, KonranWazaTbl[i], target) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1d5);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueAnkooru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 last = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(t, target);
    if (fightTrainerAiCmpFightOutPokemonSubayasa(t, self, target) > 0 && last != 0 && last != 0xffff && last != 0x176 && last != 0x163 && !fightTrainerAiIsWazaTypeId(t, last, 1)) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1d0);
    return handle;
}

s32 fightTrainerAiWazaValueIkarinomaeba(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonNokoriHp(t, target, 1, 0.5f) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1cf);
    return handle;
}

s32 fightTrainerAiWazaValueKusuguruDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 pha = fightTrainerAiGetFightOutPokemonPhyAtk(t, target);
    u16 spa = fightTrainerAiGetFightOutPokemonSpeAtk(t, target);
    u16 phd = fightTrainerAiGetFightOutPokemonPhyDef(t, target);
    u16 spd = fightTrainerAiGetFightOutPokemonSpeDef(t, target);
    if (pha > spa) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1cc);
    if (phd > spd) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1cd);
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, target) <= 4 && fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, target) <= 4) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ce);
    return handle;
}

s32 fightTrainerAiWazaValueKaihiDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    u16 wazaAry[8];
    s32 handle = 0;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    u8 avg = fightTrainerAiDB_GetWazaAvgValue(fightTrainer_GetFightTrainerDataId(t));
    u16 i;
    u16 j;
    u8 flag;
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(t, target) >= 7) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1ca);
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(t, target) <= 5) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1cb);
    flag = 0;
    for (i = 0; i < count; i++) {
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 1);
        if (n != 0) {
            for (j = 0; j < n; j++) {
                if (wazaDB_GetAvg(wazaAry[j]) < avg) {
                    flag = 1;
                    break;
                }
            }
        }
    }
    if (flag) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1c9);
    return handle;
}

s32 fightTrainerAiWazaValueMeityuuDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiGetFightOutPokemonAbiCntAvg(t, target) <= 4) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1c8);
    return handle;
}

s32 fightTrainerAiWazaValueTokubouDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 phd = fightTrainerAiGetFightOutPokemonPhyDef(t, target);
    u16 spd = fightTrainerAiGetFightOutPokemonSpeDef(t, target);
    if (phd < spd) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1c6);
    if (fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, target) <= 4) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1c7);
    return handle;
}

s32 fightTrainerAiWazaValueBougyoDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u16 phd;
    u16 spd;
    u8 i;
    u8 n;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    n = 0;
    for (i = 0; i < count; i++) {
        phd = fightTrainerAiGetFightOutPokemonPhyDef(t, ary[i]);
        spd = fightTrainerAiGetFightOutPokemonSpeDef(t, ary[i]);
        if (phd > spd) n++;
    }
    if (phd > spd) handle = fightTrainerAiAddValue(handle, n * fightTrainerGetStatus(0, 0x1c4, 0x3e, 0));
    n = 0;
    for (i = 0; i < count; i++) {
        if (fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, ary[i]) <= 4) n++;
    }
    return fightTrainerAiAddValue(handle, n * fightTrainerGetStatus(0, 0x1c5, 0x3e, 0));
}

s32 fightTrainerAiWazaValueKougekiDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 pha = fightTrainerAiGetFightOutPokemonPhyAtk(t, target);
    u16 spa = fightTrainerAiGetFightOutPokemonSpeAtk(t, target);
    if (pha > spa) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1c2);
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, target) <= 4) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1c3);
    return handle;
}

s32 fightTrainerAiWazaValueSubayasaDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle;
    u8 flag = 0;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    for (u16 i = 0; i < count; i++) {
        if (fightTrainerAiCmpFightOutPokemonSubayasa(t, target, ary[i]) > 0) {
            flag = 1;
            break;
        }
    }
    if (flag == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1c0);
    } else {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1c1);
    }
    return handle;
}

s32 fightTrainerAiWazaValueGamusyara(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    u16 selfHp = fightTrainerAiGetFightOutPokemonNowHp(t, self);
    s32 value = fightTrainerAiGetFightOutPokemonNowHp(t, target) / selfHp;
    value *= fightTrainerGetStatus(0, 0x1bf, 0x3e, 0);
    return fightTrainerAiAddValue(0, value);
}

s32 fightTrainerAiWazaValueItamiwake(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s32 selfPct = fightTrainerAiGetFightOutPokemonNowHpPercentage(t, self);
    s32 targetPct = fightTrainerAiGetFightOutPokemonNowHpPercentage(t, target);
    if (selfPct * 3 <= targetPct) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1bc);
    } else if (selfPct * 2 <= targetPct) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1bb);
    } else if (selfPct >= targetPct * 3) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1be);
    } else if (selfPct >= targetPct * 2) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1bd);
    }
    return handle;
}

s32 fightTrainerAiWazaValueAkumu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x17) == 0) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1ba);
    return handle;
}

s32 fightTrainerAiWazaValueRokkuon(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 id = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(self, fightFloor_GetFightType(0));
    if (!fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1d)) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1b8);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1d) == 1 && id == fightOutPokemonGetUserFightTargetIdJoutaiDataId(target, 0x1d)) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1b9);
    return handle;
}

s32 fightTrainerAiWazaValueNoroi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u8 ghost = fightTrainerAiIsFightOutPokemonZokuseiDataId(t, self, 7);
    if (ghost == 1 && fightTrainerAiIsFightOutPokemonNokoriHp(t, self, 1, 0.5f) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1b3);
    } else if (ghost == 1 && fightTrainerAiIsFightOutPokemonNokoriHp(t, self, -1, 0.25f) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1b4);
    }
    if (!ghost && !fightTrainerAiIsFightOutPokemonAllAbiCntTakai(t, self)) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1b5);
    if (ghost == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1b6);
    if (!ghost && fightTrainerAiIsFightOutPokemonAllAbiCntTakai(t, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1b7);
    return handle;
}

s32 fightTrainerAiWazaValueToriaezutukae(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    return fightTrainerAiAddValueByAddsubDataId(0, t, 0x1b2);
}

s32 fightTrainerAiWazaValueKoraeru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    u16 wazaAry[8];
    u16 zokusei[2];
    s32 handle = 0;
    u8 flag;
    u16 i;
    u16 j;
    u8 tenkou = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1);
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    u16 zcount = fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(t, target, zokusei);
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, self);
    u16 item = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, self);
    flag = 0;
    for (i = 0; i < zcount; i++) {
        if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(t, self, zokusei[i], fightTrainerAiGetWazaIryoku(t, waza)) == 0x41) {
            flag = 1;
            break;
        }
    }
    if (flag == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1a9);
    if (fightTrainerAiIsFightOutPokemonNokoriHp(t, self, -1, 0.5f) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1aa);
    for (i = 0; i < count; i++) {
        if (self == ary[i]) continue;
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 1);
        if (n == 0) continue;
        for (j = 0; j < n; j++) {
            WazaValueFunc func = wazaDB_GetFightTrainerAiWazaValueFuncPtr(wazaAry[j]);
            if (func == 0) func = fightTrainerAiWazaValueNull;
            if (func == fightTrainerAiWazaValueJisin || func == fightTrainerAiWazaValueJibaku) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ab);
                break;
            }
        }
        if (j < n) break;
    }
    for (i = 0; i < *waza_data_number; i++) {
        WazaValueFunc func = wazaDB_GetFightTrainerAiWazaValueFuncPtr(i);
        if (func == 0) func = fightTrainerAiWazaValueNull;
        if ((func == fightTrainerAiWazaValueJisin || func == fightTrainerAiWazaValueJibaku) && fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, i, 0) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ac);
            break;
        }
    }
    u8 bad = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 6) == 1) bad = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 3) == 1) bad = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 4) == 1) bad = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 5) == 1) bad = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x18) == 1) bad = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x1c) == 1) bad = 1;
    if (bad == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ad);
    if (last == 0xcb && fightOutPokemon_GetSuccessCnt(self) != 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1ae);
    if (item != 0x11 && item != 0xf) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1af);
    if (fightTrainerAiGetFightOutPokemonNowHp(t, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1b0);
    if (tenkou == 4 || tenkou == 3) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1b1);
    return handle;
}

s32 fightTrainerAiWazaValueMiyaburu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 7) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1a6);
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(t, target) >= 8) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1a7);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x19) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1a8);
    return handle;
}

s32 fightTrainerAiWazaValueMajikkukooto(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightOutPokemon_GetFightoutTurnCount(self) != 0) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1a5);
    return handle;
}

s32 fightTrainerAiWazaValueMiraakooto(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    for (u16 i = 0; i < count; i++) {
        u16 pha = fightTrainerAiGetFightOutPokemonPhyAtk(t, ary[i]);
        u16 spa = fightTrainerAiGetFightOutPokemonSpeAtk(t, ary[i]);
        if (pha < spa) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1a3);
            break;
        }
    }
    if (last != 0 && last != 0xffff && last != 0x176 && last != 0x163 && zokuseiBiosGetWazaKind(fightTrainerAiGetWazaZokuseiDataId(t, last, target)) == 2) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1a4);
    return handle;
}

s32 fightTrainerAiWazaValueKauntaa(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    for (u16 i = 0; i < count; i++) {
        u16 pha = fightTrainerAiGetFightOutPokemonPhyAtk(t, ary[i]);
        u16 spa = fightTrainerAiGetFightOutPokemonSpeAtk(t, ary[i]);
        if (pha > spa) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1a1);
            break;
        }
    }
    if (last != 0 && last != 0xffff && last != 0x176 && last != 0x163 && zokuseiBiosGetWazaKind(fightTrainerAiGetWazaZokuseiDataId(t, last, target)) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x1a2);
    return handle;
}

s32 fightTrainerAiWazaValueAroma(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* ary[24];
    s32 handle = 0;
    u16 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, ary, 1, 1);
    for (u16 i = 0; i < count; i++) {
        if (!fightTrainerAiIsFightPokemonJoutaiNormal(t, ary[i])) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x1a0);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueRihuressyu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, self) == 0) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x19f);
    return handle;
}

s32 fightTrainerAiWazaValueSunaarasi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* ary[24];
    FightOutPokemon* outAry[8];
    s32 handle = 0;
    u16 k;
    u16 j;
    u16 i;
    u8 tenkou = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 0);
    u16 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, ary, 1, 1);
    u16 outCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, outAry, 0, 1);
    if (tenkou != 3) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x194);
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(t, ary[i], 5) == 1 || fightTrainerAiIsFightPokemonZokuseiDataId(t, ary[i], 4) == 1 || fightTrainerAiIsFightPokemonZokuseiDataId(t, ary[i], 8) == 1 || fightTrainerAiIsFightPokemonTokuseiDataId(t, ary[i], 8) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x195);
            break;
        }
    }
    for (j = 0; j < outCount; j++) {
        if (fightTrainerAiGetFightOutPokemonPokemonDataId(t, outAry[j]) == 0x12f) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x196);
            break;
        }
    }
    for (k = 0; k < count; k++) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(t, ary[k]) == 0x181) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x197);
            break;
        }
    }
    if (tenkou == 3) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x198);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xf1, 0) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x199);
    return handle;
}

s32 fightTrainerAiWazaValueArare(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* ary[24];
    FightOutPokemon* outAry[8];
    s32 handle = 0;
    u16 k;
    u16 j;
    u16 i;
    u8 tenkou = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 0);
    u16 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, ary, 1, 1);
    u16 outCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, outAry, 0, 1);
    if (tenkou != 4) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x18e);
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(t, ary[i], 0xf) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x18f);
            break;
        }
    }
    for (j = 0; j < outCount; j++) {
        if (fightTrainerAiGetFightOutPokemonPokemonDataId(t, outAry[j]) == 0x12f) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x190);
            break;
        }
    }
    for (k = 0; k < count; k++) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(t, ary[k]) == 0x181) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x191);
            break;
        }
    }
    if (tenkou == 4) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x192);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xf1, 0) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x193);
    return handle;
}

s32 fightTrainerAiWazaValueNihonbare(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* ary[24];
    s32 handle = 0;
    u16 j;
    u16 i;
    u8 tenkou = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 0);
    u16 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, ary, 1, 1);
    if (tenkou != 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x189);
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(t, ary[i], 0xa) == 1 || fightTrainerAiIsFightPokemonZokuseiDataId(t, ary[i], 0xc) == 1 || fightTrainerAiIsFightPokemonTokuseiDataId(t, ary[i], 0x22) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x18a);
            break;
        }
    }
    for (j = 0; j < count; j++) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(t, ary[j]) == 0x181) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x18b);
            break;
        }
    }
    if (tenkou == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x18c);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xf1, 0) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x18d);
    return handle;
}

s32 fightTrainerAiWazaValueAmagoi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* ary[24];
    s32 handle = 0;
    u16 j;
    u16 i;
    u8 tenkou = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 0);
    u16 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, ary, 1, 1);
    if (tenkou != 2) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x184);
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(t, ary[i], 0xb) == 1 || fightTrainerAiIsFightPokemonTokuseiDataId(t, ary[i], 0x21) == 1 || fightTrainerAiIsFightPokemonTokuseiDataId(t, ary[i], 0x2c) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x185);
            break;
        }
    }
    for (j = 0; j < count; j++) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(t, ary[j]) == 0x181) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x186);
            break;
        }
    }
    if (tenkou == 2) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x187);
    return handle;
}

s32 fightTrainerAiWazaValueNemurare(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* ary[24];
    s32 handle = 0;
    u16 j;
    u16 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, ary, 0, 1);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x181);
    for (u16 i = 0; i < count; i++) {
        if (fightOutPokemon_GetMotoFightPokemonPtr(target) != ary[i] && fightTrainerAiIsFightPokemonJoutaiDataId(t, ary[i], 8) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x182);
            break;
        }
    }
    for (j = 0; j < 0x12; j++) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, joutaiIzyouWazaTbl[j], target) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x183);
            break;
        }
    }
    return handle;
}

s32 fightTrainerAiWazaValueNemuru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 item = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, self);
    if (item == 3 || item == 9) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x17d);
    if (fightTrainerAiIsFightOutPokemonNokoriHp(t, self, -1, 0.55f) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x17e);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, self) == 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x17f);
    return fightTrainerAiAddValueByAddsubDataId(handle, t, 0x180);
}

s32 fightTrainerAiWazaValueKaihuku2(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonNokoriHp(t, self, -1, 0.5f) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x17c);
    return handle;
}

s32 fightTrainerAiWazaValueKaihuku1(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u8 tenkou = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1);
    if (tenkou == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x179);
    if (fightTrainerAiIsFightOutPokemonNokoriHp(t, self, -1, 0.5f) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x17a);
    if (tenkou == 2 || tenkou == 4 || tenkou == 3) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x17b);
    return handle;
}

s32 fightTrainerAiWazaValueKituke(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 5) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x177);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x178);
    return handle;
}

s32 fightTrainerAiWazaValueOiuti(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u8 irekae = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(t, 0, target, 0);
    FIGHT_TRAINER* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, target);
    s16 found = 0;
    if (fightTrainerSearchIrekaeFightPokemon(trainer, &found) == 0) irekae = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x16d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x16e);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x16f);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x170);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x171);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x172);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x173);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x174);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x26) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x175);
    if (irekae) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x176);
    return handle;
}

s32 fightTrainerAiWazaValueUezaabooru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u8 tenkou = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1);
    if (tenkou == 1 || tenkou == 2) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x168);
    if (tenkou == 4) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x169);
    if (tenkou == 3) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x16a);
    if (tenkou == 5) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x16b);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x16c);
    return handle;
}

s32 fightTrainerAiWazaValueSizennotikara(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    u16 id = tikeiDataBiosGetWazaId(fightFloor_GetTikeiDataId(0));
    if (id != waza) return fightTrainerAiWazaDoWazaValueFunc(t, self, id, target);
    return 0;
}

s32 fightTrainerAiWazaValueHimitunotikara(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    switch (tikeiDataBiosGetFightKoukaId(fightFloor_GetTikeiDataId(0))) {
    case 2:
        handle = fightTrainerAiWazaValueTuikaDoku(t, self, waza, target);
        break;
    case 1:
        handle = fightTrainerAiWazaValueTuikaNemuri(t, self, waza, target);
        break;
    case 0x1b:
        handle = fightTrainerAiWazaValueTuikouMeityuuDaun(t, self, waza, target);
        break;
    case 0x17:
        handle = fightTrainerAiWazaValueTuikouBougyoDaun(t, self, waza, target);
        break;
    case 0x16:
        handle = fightTrainerAiWazaValueOororabiimu(t, self, waza, target);
        break;
    case 0x18:
        handle = fightTrainerAiWazaValueTuikouSubayasaDaun(t, self, waza, target);
        break;
    case 7:
        handle = fightTrainerAiWazaValueTuikouKonran(t, self, waza, target);
        break;
    case 8:
        handle = fightTrainerAiWazaValueTuikaHirumi(t, self, waza, target);
        break;
    case 5:
        handle = fightTrainerAiWazaValueTuikaMahi(t, self, waza, target);
        break;
    }
    return handle;
}

s32 fightTrainerAiWazaValueItigekihissatu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x166);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x167);
    return handle;
}

s32 fightTrainerAiWazaValueZennouryokuappu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x164);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x165);
    return handle;
}

s32 fightTrainerAiWazaValueTuikaKougekiAppu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle;
    s32 q;
    q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    handle = fightTrainerAiAddValue(0, q / fightTrainerGetStatus(0, 0x161, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x162);
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, self) >= 0xc) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x163, 0x3e, 0));
    }
    return handle;
}

s32 fightTrainerAiWazaValueHaganenotubasa(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x15e);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x15f);
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, self) >= 0xc) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x160);
    return handle;
}

s32 fightTrainerAiWazaValueSaikobuusuto(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 item = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, self);
    if (item == 0x17) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x159);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x15a);
    handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x15c);
    u8 cnt = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(t, self);
    if (cnt < 6) handle = fightTrainerAiAddValue(handle, (6 - cnt) * fightTrainerGetStatus(0, 0x15d, 0x3e, 0));
    if (item == 0x17) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x15b);
    return handle;
}

s32 fightTrainerAiWazaValueBakadikara(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 item = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, self);
    if (item == 0x17) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x154);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x155);
    handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x157);
    u8 cnt = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, self);
    if (cnt < 6) handle = fightTrainerAiAddValue(handle, (6 - cnt) * fightTrainerGetStatus(0, 0x158, 0x3e, 0));
    if (item == 0x17) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x156);
    return handle;
}

s32 fightTrainerAiWazaValueOobaahiito(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, self) == 0x17) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x150);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x151);
    u8 cnt = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(t, self);
    if (cnt < 6) handle = fightTrainerAiAddValue(handle, (cnt + 6) * fightTrainerGetStatus(0, 0x152, 0x3e, 0));
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 7) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x153);
    return handle;
}

s32 fightTrainerAiWazaValueHatakiotosu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x3d) == 0 && fightTrainerAiGetFightOutPokemonSoubiItemDataId(t, target) != 0) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x14e);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x3c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x14f);
    return handle;
}

s32 fightTrainerAiWazaValueDouguUbau(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle;
    u8 ok;
    u16 selfItem;
    u16 targetItem;
    handle = 0;
    selfItem = fightTrainerAiGetFightOutPokemonSoubiItemDataId(t, self);
    targetItem = fightTrainerAiGetFightOutPokemonSoubiItemDataId(t, target);
    ok = 1;
    if (!fightSeqIsDoItemGetWaza(self)) ok = 0;
    if (selfItem != 0 || targetItem == 0xaf || targetItem == 0 || !itemDataCheckValid(targetItem)) ok = 0;
    if (ok == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x14c);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x3c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x14d);
    return handle;
}

s32 fightTrainerAiWazaValueSooraabiimu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u8 tenkou = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1);
    if (tenkou == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x148);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x149);
    if (tenkou == 2 || tenkou == 4 || tenkou == 3) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x14a);
    if (tenkou == 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x14b);
    return handle;
}

s32 fightTrainerAiWazaValueToraiatakku(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x143);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x144);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x145);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 7) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x29) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x28) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x146);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x147);
    return handle;
}

s32 fightTrainerAiWazaValueDokudokunokiba(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x13f);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x140);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x11) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x141);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x142);
    return handle;
}

s32 fightTrainerAiWazaValuePoizunteeru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightSide* side = fightTargetGetPtrAsNowFightType(2, target);
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x139);
    u8 def = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, target);
    if (def > 6) handle = fightTrainerAiAddValue(handle, (def - 6) * fightTrainerGetStatus(0, 0x13a, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x13b);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x11) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x13d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x13e);
    if (fightSideIsJoutaiDataId(side, 0x48) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x13c);
    return handle;
}

s32 fightTrainerAiWazaValueTuikaDoku(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x135, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x136);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x11) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 3) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x137, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x138, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x138);
    }
    return handle;
}

s32 fightTrainerAiWazaValueHandou(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x132);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, self, 0x36) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x133);
    return fightTrainerAiAddValueByAddsubDataId(handle, t, 0x134);
}

s32 fightTrainerAiWazaValueTuikaNemuri(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* ary[24];
    s32 handle;
    s32 q;
    u16 count;
    u16 i;
    count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, ary, 0, 1);
    q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    handle = fightTrainerAiAddValue(0, q / fightTrainerGetStatus(0, 0x12f, 0x3e, 0));
    for (i = 0; i < count; i++) {
        if (fightOutPokemon_GetMotoFightPokemonPtr(target) != ary[i] && fightTrainerAiIsFightPokemonJoutaiDataId(t, ary[i], 8) == 1) {
            q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
            handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x130, 0x3e, 0));
            break;
        }
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0xf) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x131, 0x3e, 0));
    }
    return handle;
}

s32 fightTrainerAiWazaValueBakuretuPanti(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 id = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(self, fightFloor_GetFightType(0));
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1d) == 1 && id == fightOutPokemonGetUserFightTargetIdJoutaiDataId(target, 0x1d)) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x12a);
    handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x12b);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x12d);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x12c);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x12e);
    return handle;
}

s32 fightTrainerAiWazaValueDenjihou(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle;
    u16 id = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(self, fightFloor_GetFightType(0));
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x125);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1d) == 1 && id == fightOutPokemonGetUserFightTargetIdJoutaiDataId(target, 0x1d)) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x126);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x127);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 7) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x128);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x129);
    return handle;
}

s32 fightTrainerAiWazaValueTuikaMahi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x121, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x122);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 7) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x123, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x124, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x124);
    }
    return handle;
}

s32 fightTrainerAiWazaValueTuikaKoori(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* ary[24];
    FightOutPokemon* outAry[8];
    s32 handle = 0;
    s32 q;
    u16 outCount;
    u16 count;
    u16 j;
    u16 i;
    u8 n;
    outCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, outAry, 0, 1);
    count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, ary, 0, 1);
    n = 0;
    for (i = 0; i < outCount; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, outAry[i]) == 1) n++;
    }
    handle = fightTrainerAiAddValue(handle, n * fightTrainerGetStatus(0, 0x11c, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x11d);
    for (i = 0; i < count; i++) {
        if (fightOutPokemon_GetMotoFightPokemonPtr(target) != ary[i] && fightTrainerAiIsFightPokemonJoutaiDataId(t, ary[i], 7) == 1) {
            q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
            handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x11e, 0x3e, 0));
            break;
        }
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x28) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x11f, 0x3e, 0));
    }
    n = 0;
    for (i = 0; i < outCount; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x28) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 0xf) == 1) n++;
    }
    handle = fightTrainerAiAddValue(handle, n * fightTrainerGetStatus(0, 0x11f, 0x3e, 0));
    for (j = 0; j < outCount; j++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, outAry[j], 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x120);
    }
    return handle;
}

s32 fightTrainerAiWazaValueBureizukikku(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    FightSide* side = fightTargetGetPtrAsNowFightType(2, target);
    u8 def = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, target);
    if (def > 6) handle = fightTrainerAiAddValue(0, (def - 6) * fightTrainerGetStatus(0, 0x115, 0x3e, 0));
    handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x116);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x117);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 7) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x119);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x29) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x11a);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x11b);
    if (fightSideIsJoutaiDataId(side, 0x49) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x118);
    return handle;
}

s32 fightTrainerAiWazaValueJikokaitou(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 7) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x10f);
    s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x110, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x111);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 7) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x112);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x29) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 0xa) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x113, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0x114, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x114);
    }
    return handle;
}

s32 fightTrainerAiWazaValueHonoonouzu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u8 irekae = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(t, 0, target, 0);
    FIGHT_TRAINER* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, target);
    s16 found = 0;
    if (fightTrainerSearchIrekaeFightPokemon(trainer, &found) == 0) irekae = 1;
    if (!irekae) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x104);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x105);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x106);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x107);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x108);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x109);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x10a);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x10b);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x10c);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 7) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x10d);
    if (irekae) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x10e);
    return handle;
}

s32 fightTrainerAiWazaValueIryokuHonoo(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u8 i;
    u8 n;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    n = 0;
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, ary[i]) == 1) n++;
    }
    handle = fightTrainerAiAddValue(handle, n * fightTrainerGetStatus(0, 0xff, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x100);
    n = 0;
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 7) == 1) n++;
    }
    handle = fightTrainerAiAddValue(handle, n * fightTrainerGetStatus(0, 0x101, 0x3e, 0));
    n = 0;
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiNormal(t, target) == 0 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x29) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, target, 0xa) == 1) n++;
    }
    handle = fightTrainerAiAddValue(handle, n * fightTrainerGetStatus(0, 0x102, 0x3e, 0));
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x103);
    }
    return handle;
}

s32 fightTrainerAiWazaValueTuikouKonran(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xfa, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xfb);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xfc, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x14) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xfd, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xfe, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xfe);
    }
    return handle;
}

s32 fightTrainerAiWazaValueDorokake(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0xf5);
    if (fightTrainerAiGetFightOutPokemonAbiCntAvg(t, target) == 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xf6);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x1d) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x49) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x33) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xf7);
    if (fightTrainerAiGetFightOutPokemonAbiCntAvg(t, target) <= 4) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xf8);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xf9);
    return handle;
}

s32 fightTrainerAiWazaValueTuikouMeityuuDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xf0, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xf1);
    if (fightTrainerAiGetFightOutPokemonAbiCntAvg(t, target) == 0) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xf2, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x1d) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x49) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x33) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xf3, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xf4, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xf4);
    }
    return handle;
}

s32 fightTrainerAiWazaValueTuikouTokubouDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xeb, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xec);
    if (fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, target) == 0) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xed, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x1d) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x49) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xee, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xef, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xef);
    }
    return handle;
}

s32 fightTrainerAiWazaValueTuikouTokukouDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0xe6);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xe7);
    if (fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(t, target) == 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xe8);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x1d) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x49) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xe9);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xea);
    return handle;
}

s32 fightTrainerAiWazaValueKogoerukaze(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* aryA[8];
    FightOutPokemon* aryB[8];
    s32 handle = 0;
    u16 k;
    u16 m;
    u16 n;
    u16 i;
    u16 j;
    FightOutPokemon* b;
    u16 countA = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryA, 1, 1);
    u16 countB = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryB, 0, 1);
    for (i = 0; i < countB; i++) {
        b = aryB[i];
        if (b == 0) continue;
        for (j = 0; j < countA; j++) {
            if (aryA[j] != 0 && fightTrainerAiCmpFightOutPokemonSubayasa(t, b, aryA[j]) > 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xe0);
        }
    }
    if (countB >= 2) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xe1);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xe2);
    for (k = 0; k < countA; k++) {
        if (aryA[k] != 0 && fightTrainerAiCmpFightOutPokemonSubayasa(t, target, aryA[k]) < 0) break;
    }
    if (k < countA) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xe3);
    for (m = 0; m < countB; m++) {
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, aryB[m], 0x1d) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, aryB[m], 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, aryB[m], 0x49) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xe4);
    }
    for (n = 0; n < countB; n++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, aryB[n], 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xe5);
    }
    return handle;
}

s32 fightTrainerAiWazaValueKanarazuSubayasaDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* aryA[8];
    FightOutPokemon* aryB[8];
    s32 handle = 0;
    u16 countA = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryA, 1, 1);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, aryB, 0, 1);
    for (u16 i = 0; i < countA; i++) {
        if (aryA[i] != 0 && fightTrainerAiCmpFightOutPokemonSubayasa(t, target, aryA[i]) > 0) {
            handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0xdb);
            break;
        }
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xdc);
    if (fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, target) == 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xdd);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x1d) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x49) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xde);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xdf);
    return handle;
}

s32 fightTrainerAiWazaValueTuikouSubayasaDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 1, 1);
    s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    s32 handle = fightTrainerAiAddValue(0, q / fightTrainerGetStatus(0, 0xd4, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xd5);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 5) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xd6);
    if (fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, target) == 0) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xd7, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x1d) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x49) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xd8, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xd9, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xd9);
    }
    u16 i;
    for (i = 0; i < count; i++) {
        if (ary[i] != 0 && fightTrainerAiCmpFightOutPokemonSubayasa(t, target, ary[i]) > 0) break;
    }
    if (i < count) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xda, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xda);
    }
    return handle;
}

s32 fightTrainerAiWazaValueTuikouBougyoDaun(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
    handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xcf, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xd0);
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, target) == 0) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xd1, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x1d) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x49) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xd2, 0x3e, 0));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
        q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xd3, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xd3);
    }
    return handle;
}

s32 fightTrainerAiWazaValueOororabiimu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0xca);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xcb);
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, target) == 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xcc);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x1d) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x49) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x34) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xcd);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
        s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(handle, q / fightTrainerGetStatus(0, 0xce, 0x3e, 0));
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xce);
    }
    return handle;
}

s32 fightTrainerAiWazaValueNekodamasi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightOutPokemon_GetFightoutTurnCount(self) != 0) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0xc7);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x27) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xc8);
    } else if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x13) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xc8);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xc9);
    return handle;
}

s32 fightTrainerAiWazaValueGoddobaado(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiCmpFightOutPokemonSubayasa(t, self, target) > 0) {
        handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0xc4);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xc6);
    }
    return fightTrainerAiAddValueByAddsubDataId(handle, t, 0xc5);
}

s32 fightTrainerAiWazaValueTuikaHirumi(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiCmpFightOutPokemonSubayasa(t, self, target) > 0) {
        s32 q = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
        handle = fightTrainerAiAddValue(0, q / fightTrainerGetStatus(0, 0xb8, 0x3e, 0));
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb9);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xba);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xbb);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xbc);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xbd);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 5) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xbe);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xbf);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xc0);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xc1);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) {
            s32 q2 = fightTrainerAiGetWazaAddKoukaAvg(t, waza);
            handle = fightTrainerAiAddValue(handle, q2 / fightTrainerGetStatus(0, 0xc6, 0x3e, 0));
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xc3);
        }
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xc2);
    return handle;
}

s32 fightTrainerAiWazaValueJisin(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* pokeAry[24];
    FightOutPokemon* allyAry[8];
    FightOutPokemon* enemyAry[8];
    u16 wazaAry[8];
    s32 handle;
    u16 zokusei;
    u16 count;
    u16 i;
    u16 j;
    handle = 0;
    zokusei = fightTrainerAiGetWazaZokuseiDataId(t, waza, self);
    fightFloorGetFightTrainerFightPokemonPtrAry(0, t, pokeAry, 1, 1);
    count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, allyAry, 1, 1);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, enemyAry, 0, 1);
    for (i = 0; i < count; i++) {
        if (self != allyAry[i] && fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(t, allyAry[i], zokusei, fightTrainerAiGetWazaIryoku(t, waza)) == 0x43) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb0);
    }
    for (i = 0; i < count; i++) {
        if (self != allyAry[i] && fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(t, allyAry[i], zokusei, fightTrainerAiGetWazaIryoku(t, waza)) == 0x42) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb1);
    }
    for (i = 0; i < count; i++) {
        if (self == allyAry[i]) continue;
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, allyAry[i], wazaAry, 0, 1);
        if (n == 0) continue;
        for (j = 0; j < n; j++) {
            if (wazaAry[j] == 0xb6 || wazaAry[j] == 0xc5 || wazaAry[j] == 0xcb) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb2);
                break;
            }
        }
        if (j < n) break;
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xb6, 0) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb3);
    } else if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xc5, 0) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb3);
    } else if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xcb, 0) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb3);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb4);
    for (i = 0; i < count; i++) {
        if (self != allyAry[i]) {
            u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, allyAry[i]);
            if (last == 0xb6 || last == 0xc5 || last == 0xcb) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb6);
        }
    }
    for (i = 0; i < count; i++) {
        if (self != allyAry[i]) {
            u16 hp = fightTrainerAiGetFightOutPokemonNowHp(t, allyAry[i]);
            if (hp <= fightTrainerAiWazaDoWazaDamageFunc(t, self, waza, allyAry[i], 0)) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb7);
        }
    }
    for (i = 0; i < count; i++) {
        if (self != allyAry[i] && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, allyAry[i], 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xb5);
    }
    return handle;
}

s32 fightTrainerAiWazaValueSokubaku(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u8 irekae = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(t, 0, target, 0);
    FIGHT_TRAINER* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, target);
    s16 found = 0;
    if (fightTrainerSearchIrekaeFightPokemon(trainer, &found) == 0) irekae = 1;
    if (!irekae) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0xa6);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xa7);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xa8);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xa9);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xab);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xac);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xad);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xae);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xaa);
    if (irekae) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xaf);
    return handle;
}

s32 fightTrainerAiWazaValueKorogaru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x1a) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0xa3);
    s32 pct = fightTrainerAiGetFightOutPokemonNowHpPercentage(t, self);
    handle = fightTrainerAiAddValue(handle, pct / fightTrainerGetStatus(0, 0xa4, 0x3e, 0));
    return fightTrainerAiAddValueByAddsubDataId(handle, t, 0xa5);
}

s32 fightTrainerAiWazaValueJibaku(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightPokemon* pokeAry[24];
    FightOutPokemon* allyAry[8];
    FightOutPokemon* enemyAry[8];
    u16 wazaAry[8];
    s32 handle;
    u16 zokusei;
    u16 count;
    u16 enemyCount;
    u16 i;
    u16 j;
    handle = 0;
    zokusei = fightTrainerAiGetWazaZokuseiDataId(t, waza, self);
    fightFloorGetFightTrainerFightPokemonPtrAry(0, t, pokeAry, 1, 1);
    count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, allyAry, 1, 1);
    enemyCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, enemyAry, 0, 1);
    for (i = 0; i < count; i++) {
        if (self != allyAry[i] && fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(t, allyAry[i], zokusei, fightTrainerAiGetWazaIryoku(t, waza)) == 0x43) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x9a);
    }
    for (i = 0; i < count; i++) {
        if (self != allyAry[i] && fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(t, allyAry[i], zokusei, fightTrainerAiGetWazaIryoku(t, waza)) == 0x42) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x9b);
    }
    for (i = 0; i < count; i++) {
        if (self == allyAry[i]) continue;
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, allyAry[i], wazaAry, 0, 1);
        if (n == 0) continue;
        for (j = 0; j < n; j++) {
            if (wazaAry[j] == 0xb6 || wazaAry[j] == 0xc5 || wazaAry[j] == 0xcb) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x9c);
                break;
            }
        }
        if (j < n) break;
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xb6, 0) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x9d);
    } else if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xc5, 0) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x9d);
    } else if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0xcb, 0) == 1) {
        handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x9d);
    }
    for (i = 0; i < enemyCount; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, enemyAry[i], 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, i == 0 ? (u16)0x9f : (u16)0xa0);
    }
    for (i = 0; i < count; i++) {
        if (self != allyAry[i]) {
            u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, allyAry[i]);
            if (last == 0xb6 || last == 0xc5 || last == 0xcb) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xa1);
        }
    }
    for (i = 0; i < count; i++) {
        if (self != allyAry[i]) {
            u16 hp = fightTrainerAiGetFightOutPokemonNowHp(t, allyAry[i]);
            if (hp <= fightTrainerAiWazaDoWazaDamageFunc(t, self, waza, allyAry[i], 0)) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0xa2);
        }
    }
    for (i = 0; i < count; i++) {
        if (self != allyAry[i] && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, allyAry[i], 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x9e);
    }
    return handle;
}

s32 fightTrainerAiWazaValueTobihaneru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    u16 wazaAry[8];
    s32 handle = 0;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x83);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x84);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x85);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 5) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x86);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x87);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x88);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x89);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x8a);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x8b);
    if (fightTrainerAiCmpFightOutPokemonSubayasa(t, self, target) > 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x8c);
    handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x8d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x8f);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x90);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x91);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 5) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x92);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x93);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x94);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x95);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x96);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x97);
    for (u16 i = 0; i < count; i++) {
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 0);
        if (n == 0) continue;
        u16 j;
        u8 found = 0;
        for (j = 0; j < n; j++) {
            if (fightTrainerAiCheckJoutaiKieWazaHitWazaDataId(t, 0x1f, wazaAry[j]) == 1) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x98);
                found = 1;
                break;
            }
        }
        if (found == 1) break;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x1d) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x99);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x8e);
    return handle;
}

s32 fightTrainerAiWazaValueSorawotobu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    u16 wazaAry[8];
    s32 handle = 0;
    u8 kie = 0;
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x6e);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x6f);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x70);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 5) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x71);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x72);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x73);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x74);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x75);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x76);
    if (fightTrainerAiCmpFightOutPokemonSubayasa(t, self, target) > 0) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x77);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 3) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x78);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 4) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x79);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 6) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x7a);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 5) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x7b);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 9) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x7c);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0xa) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x7d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x18) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x7e);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x1e) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x7f);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x1c) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x80);
    if (waza == 0x13 || waza == 0x154) {
        kie = 0x1f;
    } else if (waza == 0x5b) {
        kie = 0x20;
    } else if (waza == 0x123) {
        kie = 0x21;
    }
    for (u16 i = 0; i < count; i++) {
        u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, ary[i], wazaAry, 0, 0);
        if (n == 0) continue;
        u16 j;
        u8 found = 0;
        for (j = 0; j < n; j++) {
            if (fightTrainerAiCheckJoutaiKieWazaHitWazaDataId(t, kie, wazaAry[j]) == 1) {
                handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x81);
                found = 1;
                break;
            }
        }
        if (found == 1) break;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, self, 0x1d) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x82);
    return handle;
}

s32 fightTrainerAiWazaValueAbareru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, self, 0x14) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x6a);
    u16 item = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, self);
    if (item == 8 || item == 9) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x6b);
    handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x6d);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x6c);
    return handle;
}

s32 fightTrainerAiWazaValueKyuusyuu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle;
    u16 now = fightTrainerAiGetFightOutPokemonNowHp(t, self);
    s32 damage = fightTrainerAiWazaDoWazaDamageFunc(t, self, waza, target, 1);
    handle = fightTrainerAiAddValue(0, damage / 2 * 100 / now / fightTrainerGetStatus(0, 0x67, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x68);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, target, 0x40) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x69);
    return handle;
}

s32 fightTrainerAiWazaValueRokettoZutuki(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x65);
    return fightTrainerAiAddValueByAddsubDataId(handle, t, 0x66);
}

s32 fightTrainerAiWazaValueKamaitati(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    FightSide* side = fightTargetGetPtrAsNowFightType(2, target);
    u8 def = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, target);
    if (def > 6) handle = fightTrainerAiAddValue(0, (def - 6) * fightTrainerGetStatus(0, 0x62, 0x3e, 0));
    handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x64);
    if (fightSideIsJoutaiDataId(side, 0x48) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x63);
    return handle;
}

s32 fightTrainerAiWazaValueKiaipanti(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    FightOutPokemon* ary[8];
    s32 handle = 0;
    u16 j;
    u16 i;
    u8 irekae = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(t, 0, target, 0);
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    if (fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, self) == 0x117) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x5d);
    for (i = 0; i < count; i++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[i], 8) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x5e);
            break;
        }
    }
    for (j = 0; j < count; j++) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, ary[j], 7) == 1) {
            handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x5f);
            break;
        }
    }
    handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x61);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, target, 0x26) == 1 && irekae) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x60);
    return handle;
}

s32 fightTrainerAiWazaValueAteminage(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u8 avd = fightTrainerAiGetFightOutPokemonAbiCntAvd(t, target);
    if (avd > 6) handle = fightTrainerAiAddValue(0, (avd - 6) * fightTrainerGetStatus(0, 0x5a, 0x3e, 0));
    u8 avg = fightTrainerAiGetFightOutPokemonAbiCntAvg(t, self);
    if (avg < 6) handle = fightTrainerAiAddValue(handle, (6 - avg) * fightTrainerGetStatus(0, 0x5b, 0x3e, 0));
    return fightTrainerAiAddValueByAddsubDataId(handle, t, 0x5c);
}

s32 fightTrainerAiWazaValueRibenji(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u16 last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, target);
    if (last != 0 && last != 0xffff && last != 0x176 && last != 0x163 && fightTrainerAiIsWazaTypeId(t, last, 1) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x58);
    return fightTrainerAiAddValueByAddsubDataId(handle, t, 0x59);
}

s32 fightTrainerAiWazaValueTokubetuYuusen(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    return fightTrainerAiAddValueByAddsubDataId(0, t, 0x57);
}

s32 fightTrainerAiWazaValueKouPuraioritii(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x55);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x56);
    return handle;
}

s32 fightTrainerAiWazaValueSpeKuritikaru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle;
    FightSide* side = fightTargetGetPtrAsNowFightType(2, target);
    handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x51);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x52);
    u8 def = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, target);
    if (def > 6) handle = fightTrainerAiAddValue(handle, (def - 6) * fightTrainerGetStatus(0, 0x53, 0x3e, 0));
    if (fightSideIsJoutaiDataId(side, 0x49) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x54);
    return handle;
}

s32 fightTrainerAiWazaValuePhyKuritikaru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle;
    FightSide* side = fightTargetGetPtrAsNowFightType(2, target);
    handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x4d);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x4e);
    u8 def = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, target);
    if (def > 6) handle = fightTrainerAiAddValue(handle, (def - 6) * fightTrainerGetStatus(0, 0x4f, 0x3e, 0));
    if (fightSideIsJoutaiDataId(side, 0x48) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x50);
    return handle;
}

s32 fightTrainerAiWazaValueHittyuu(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    u8 avd = fightTrainerAiGetFightOutPokemonAbiCntAvd(t, target);
    if (avd > 6) handle = fightTrainerAiAddValue(0, (avd - 6) * fightTrainerGetStatus(0, 0x4a, 0x3e, 0));
    u8 avg = fightTrainerAiGetFightOutPokemonAbiCntAvg(t, self);
    if (avg < 6) handle = fightTrainerAiAddValue(handle, (6 - avg) * fightTrainerGetStatus(0, 0x4b, 0x3e, 0));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(handle, t, 0x4c);
    return handle;
}

s32 fightTrainerAiWazaValueTuujouIryoku(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) {
    s32 handle = 0;
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, t, 1, 1, 0x10e, self) == 1) handle = fightTrainerAiAddValueByAddsubDataId(0, t, 0x49);
    return handle;
}

s32 fightTrainerAiWazaValueNull(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target) { return 0; }

}

static u8 _fightTrainerAiWazaValueAbiCntCheck(FIGHT_TRAINER* t, FightOutPokemon* p, u8 lo, u8 hi) {
    u8 cnt[7];
    cnt[0] = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, p);
    cnt[1] = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, p);
    cnt[2] = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(t, p);
    cnt[3] = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, p);
    cnt[4] = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, p);
    cnt[5] = fightTrainerAiGetFightOutPokemonAbiCntAvg(t, p);
    cnt[6] = fightTrainerAiGetFightOutPokemonAbiCntAvd(t, p);
    for (u8 i = 0; i < 7; i++) {
        if (cnt[i] >= lo && cnt[i] <= hi) return 1;
    }
    return 0;
}
