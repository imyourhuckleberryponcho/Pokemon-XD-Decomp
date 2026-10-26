#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FightPokemon;
struct FIGHT_FLOOR;
struct FightSide;
struct Pokemon {
    u16 getHp() const;
};
class FightPokemon {
public:
    Pokemon* getPokemonBuffPtr();
};
class FightOutPokemon {
public:
    void setComboFuncId(u8 id);
    FightPokemon* getFightPokemonPtr();
};

struct AllWazaValid {
    u32 a[4];
    u16 waza[2];
    u16 unk14;
    u8 mode[2];
    u8 data[0x14];
};

extern "C" {
extern s8 ai_allwaza_valid_work;
u16 HSD_Rand();
void fightAi_InitAllWazaValidSub(AllWazaValid*);
void fightAi_AllWazaValid_AddComboList(FIGHT_TRAINER*, AllWazaValid*, u8*, u8, u32, u8, u32);
s32 fightAiCombo_GetValidValue(FightOutPokemon**, u16, FightOutPokemon**, u16);
s16 fightAiCombo_GetAllWazaMaxValueTable(AllWazaValid*, u8, s32, FIGHT_TRAINER*, FightOutPokemon**, FightOutPokemon**, s32, s32);
s32 fightFloor_GetFightType(FIGHT_FLOOR*);
s32 fightFloor_GetFightTypeTrainerNum(FIGHT_FLOOR*);
s32 fightFloor_GetFightTypeEntryPokemonNum(FIGHT_FLOOR*);
s32 fightFloor_GetFightTypeFightoutPokemonNum(FIGHT_FLOOR*);
FightSide* fightTargetGetPtr(u8, FIGHT_TRAINER*, u8);
u8 fightSideIsJoutaiDataId(FightSide*, u16);
u16 fightSideGetHikaeFightPokemonNum(FightSide*, u8, u8, u8);
void fightAi_AllWazaValid_DelListFromSpeed(FIGHT_TRAINER*, AllWazaValid*, u8*, u16, u8);
u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightFloor_GetFightKindDorobouFlag(FIGHT_FLOOR*);
s16 fightAiCombo_GetAllWazaValueTable(AllWazaValid*, s32, FIGHT_TRAINER*, FightOutPokemon**, FightOutPokemon**, s32);
s32 fightAi_CopyAllWazaValidTable(AllWazaValid*, AllWazaValid*);
s8 fightAi_getAnotherPokeNo(u8);
void fightAi_CreateAction_FromAllWazaValid(FIGHT_TRAINER*, AllWazaValid*);
u8 fightFloorGetNowTenkouDataId(FIGHT_FLOOR*, u8);
u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsFightPokemonZokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
s16 fightTrainerAiAddValueByAddsubDataId(s16, FIGHT_TRAINER*, u16);
struct Pokemon;
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u8 pokemonIsDarkPokemon(Pokemon*);
u8 wazaCheckDarkWaza(u16);
u16 fightTrainer_GetEnemyExpectWazaData(u8* t, s16 id, u8 index);
u16 fightTrainer_GetEnemyStoreWazaData(u8* t, s16 id, u8 index);
FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon* fop);
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*, u8);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER* t, FightOutPokemon* a, u16* ids, s16* indices, u8 check);
u16 figthOutPokemonGetPokemonDataId(FightOutPokemon* fop);
u16 zokuseiGetWazaJoutai(u16 waza, u16 def);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataId(FIGHT_TRAINER* t, FightOutPokemon* a, u8 idx);
u8 fightAi_GetWazaZokuseiData_ThinkWeatherBall(u16 waza, u16 weather);
u16 fightTrainerAiGetFightPokemonWazaDataIdAry(FIGHT_TRAINER* t, FightPokemon* p, u16* ids, s16* indices, u8 check);
u16 fightOutPokemon_GetLastUseWazaDataId(FightOutPokemon* fop);
u8 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon* fop);
u8 fightOutPokemonGetNowHpPercentage(FightOutPokemon* fop);
u8 fightOutPokemon_GetAbicntPhyAtk(FightOutPokemon* fop);
u8 fightFloorCmpfightOutPokemonNimbleness(FIGHT_FLOOR*, FightOutPokemon*, FightOutPokemon*, u8);
u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(FIGHT_TRAINER*, FightOutPokemon*);
u8 wazaDB_GetZokuseiDataId(u16 id);
void fightAi_AllWazaValid_DelComboList(FIGHT_TRAINER*, AllWazaValid*, u8*, u8, u16, u8, u8, u8);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);

u16 fightTrainerGetIrekaeFightPokemonAry(FIGHT_TRAINER*, FightPokemon**);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER*, u16, FightOutPokemon*);
u8 wazaIsWazaTypeId(u16, s32);
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_FLOOR*, FightOutPokemon*, s32);
void* fightOutPokemonCreateFightAction(FightOutPokemon*, s32, s32, s32, void*, s32);
s16 fightPokemon_GetEntryId(FightPokemon*);
extern u8 fight_action_data_turn[];

u8 (*wazaDB_GetFightTrainerAiWazaHitFuncPtr(u16))(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(FIGHT_TRAINER*, FightPokemon*);

struct StatusUpWazaEntry { u16 waza; u16 pad[2]; };
extern StatusUpWazaEntry statusUpWazaTbl[];
extern const u16 NemuraseWazaTbl[6];
u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER*, FightOutPokemon*);

u8 fightAi_GetWazaHaveFlag(FIGHT_TRAINER*, FightPokemon*, u16);
u8 fightTrainerAiIsFightOutPokemonAvoidCntHikui(FIGHT_TRAINER*, FightOutPokemon*);
extern u16 moukakeiTbl[];
extern u16 statusUpKinomiTbl[];
s32 fightAiCombo_Darkdown_PhyatkIryoku_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 j;
    u8 k;
    u8 num;
    u8 found;
    FightSide* side;
    AllWazaValid tbl[0x40];
    s16 best;
    u8 i;
    u8 fightType;
    s32 val;
    u8 buf[0x40];
    s16 cur;
    u8 n;
    int rnd;
    u8 pct;

    num = 0;
    fightType = fightFloor_GetFightType(0);
    n = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    side = fightTargetGetPtr(3, t, fightType);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(side, 0x4C) == 1) {
        return 0;
    }
    found = 0;
    for (j = 0; j < oppCnt; j++) {
        if (oppAry[j] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[j], 0x1D) < 1 && fightAi_GetTokuseiHaveFlag(t, oppAry[j], 0x49) < 1) {
            found++;
        }
    }
    if (found == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x173, 2, 1);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x173, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] != 0x173 && wazaDB_GetZokuseiDataId(tbl[k].waza[j]) != 1) {
                cur = 0;
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Darkmist_Darkend_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    u8 j;
    s16 val;
    u8 num;
    u8 found;
    int r;
    FightSide* side;
    AllWazaValid tbl[0x40];
    u8 fightType;
    u8 i;

    num = 0;
    fightType = fightFloor_GetFightType(0);
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    side = fightTargetGetPtr(3, t, fightType);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(side, 0x4C) == 1) {
        return 0;
    }
    found = 0;
    for (j = 0; j < oppCnt; j++) {
        if (oppAry[j] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[j], 0x1D) < 1 && fightAi_GetTokuseiHaveFlag(t, oppAry[j], 0x49) < 1) {
            found++;
        }
    }
    if (found == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x171, 1, 0x167);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x171, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt), t, ary, oppAry, p5, -1);
    if (val > 0) {
        r = HSD_Rand();
        if (val + bonus > (u8)(r % 100)) {
            for (j = 0; j < cnt; j++) {
                ary[j]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Darkmist_Darkhold_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    u8 j;
    s16 val;
    u8 num;
    u8 found;
    int r;
    FightSide* side;
    AllWazaValid tbl[0x40];
    u8 fightType;
    u8 i;

    num = 0;
    fightType = fightFloor_GetFightType(0);
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    side = fightTargetGetPtr(3, t, fightType);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(side, 0x4C) == 1) {
        return 0;
    }
    found = 0;
    for (j = 0; j < oppCnt; j++) {
        if (oppAry[j] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[j], 0x1D) < 1 && fightAi_GetTokuseiHaveFlag(t, oppAry[j], 0x49) < 1) {
            found++;
        }
    }
    if (found == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x171, 1, 0x170);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x171, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt), t, ary, oppAry, p5, -1);
    if (val > 0) {
        r = HSD_Rand();
        if (val + bonus > (u8)(r % 100)) {
            for (j = 0; j < cnt; j++) {
                ary[j]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Darkmist_Darkpanic_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    u8 j;
    s16 val;
    u8 num;
    u8 found;
    int r;
    FightSide* side;
    AllWazaValid tbl[0x40];
    u8 fightType;
    u8 i;

    num = 0;
    fightType = fightFloor_GetFightType(0);
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    side = fightTargetGetPtr(3, t, fightType);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(side, 0x4C) == 1) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(side, 0x4B) == 1) {
        return 0;
    }
    found = 0;
    for (j = 0; j < oppCnt; j++) {
        if (oppAry[j] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[j], 0x1D) < 1 && fightAi_GetTokuseiHaveFlag(t, oppAry[j], 0x49) < 1 && fightAi_GetTokuseiHaveFlag(t, oppAry[j], 0x14) < 1) {
            found++;
        }
    }
    if (found == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x171, 1, 0x172);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x171, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt), t, ary, oppAry, p5, -1);
    if (val > 0) {
        r = HSD_Rand();
        if (val + bonus > (u8)(r % 100)) {
            for (j = 0; j < cnt; j++) {
                ary[j]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Darkweather_DarkIryoku_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    u8 num;
    u8 i;
    u8 k;
    u8 j;
    s16 best;
    s32 val;
    s16 cur;
    u8 n;
    u16 rnd;
    u8 pct;

    n = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 5) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x16F, 2, 1);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x16F, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(ary[i])) == 1) {
            val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2C5);
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(oppAry[i])) == 1) {
            val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2C4);
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] != 0x16F && wazaCheckDarkWaza(tbl[k].waza[j]) == 0) {
                cur = 0;
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Batontatti_Zikoanzi_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    FightPokemon* irekae[6];
    u16 wazaIds[8];
    u16 oppWaza[8];
    FightOutPokemon* target;
    FightOutPokemon* other;
    s32 fightType;
    u16 irekaeNum;
    u8 wazaNum;
    u16 oppWazaNum;
    u8 total;
    u8 noEffect;
    u8 count;
    s32 dmg;
    s32 bestDmg;
    u8 zok;
    u16 zok0;
    u16 zok1;
    u8 num;
    u8 i;
    u8 j;
    u8 k;
    u8 m;
    u8 n;
    s32 val;
    s16 best;
    s16 cur;
    u16 rnd;
    u8 pct;
    u32* p;

    target = 0;
    total = 0;
    noEffect = 0;
    bestDmg = 0;
    fightType = fightFloor_GetFightType(0);
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    switch (irekaeNum) {
    case 0:
            return 0;
        break;
    }
    for (i = 0; i < irekaeNum; i++) {
        wazaNum = fightTrainerAiGetFightPokemonWazaDataIdAry(t, irekae[i], wazaIds, 0, 1);
        for (j = 0; j < wazaNum; j++) {
            for (m = 0; m < oppCnt; m++) {
                total++;
                zok = fightAi_GetWazaZokuseiData_ThinkWeatherBall(wazaIds[j], 0);
                zok0 = fightTrainerAiGetFightOutPokemonZokuseiDataId(t, oppAry[m], 0);
                zok1 = fightTrainerAiGetFightOutPokemonZokuseiDataId(t, oppAry[m], 1);
                if (zokuseiGetWazaJoutai(zok, zok0) == 0x43 || zokuseiGetWazaJoutai(zok, zok1) == 0x43) {
                    noEffect++;
                }
            }
        }
    }
    if (noEffect >= total) {
        return 0;
    }
    count = 0;
    for (i = 0; i < oppCnt; i++) {
        if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x27) >= 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 7) == 1) {
            count++;
        }
    }
    for (i = 0; i < cnt; i++) {
        if (figthOutPokemonGetPokemonDataId(ary[i]) == 0x12E) {
            for (m = 0; m < oppCnt; m++) {
                oppWazaNum = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, oppAry[m], oppWaza, 0, 0);
                for (j = 0; j < oppWazaNum; j++) {
                    dmg = fightTrainerAiWazaDoWazaDamageFunc(t, oppAry[m], oppWaza[j], ary[i], 0);
                    if (bestDmg < dmg && fightAi_GetTokuseiHaveFlag(t, oppAry[m], 0x27) == 0
                        && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 7) == 0) {
                        bestDmg = dmg;
                        target = oppAry[m];
                    }
                }
            }
        }
    }
    if (count >= oppCnt) {
        val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
        for (i = 0; i < cnt; i++) {
            for (k = 0; k < 0x40; k++) {
                fightAi_InitAllWazaValidSub(&tbl[k]);
            }
            num = 0;
            fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xB6, 0, 0);
            if (num == 0) {
                return 0;
            }
            best = 0;
            for (k = 0; k < num; k++) {
                tbl[k].a[(s8)fightAi_getAnotherPokeNo(i)] = 0;
                if (tbl[k].waza[i] == 0xB6) {
                    tbl[k].a[2 + i] = tbl[k].a[i];
                }
                cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
                if (tbl[k].waza[i] == 0xB6) {
                    if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(tbl[k].waza[i])(t, (FightOutPokemon*)(p = &tbl[k].a[i])[0], tbl[k].waza[i], (FightOutPokemon*)p[2]) == 0) {
                        cur = 0;
                    }
                    if (fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)p[0])->getFightPokemonPtr(), 0xE2) != 2) {
                        cur = 0;
                    }
                }
                if (best < cur) {
                    buf[0] = k;
                    best = cur;
                    n = 1;
                } else if (best == cur && best > 0) {
                    buf[n] = k;
                    n++;
                }
            }
            rnd = HSD_Rand();
            fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
            pct = HSD_Rand() % 100;
            if (best != 0 && best + bonus > pct) {
                ary[i]->setComboFuncId(0x15);
                fightAi_CreateAction_FromAllWazaValid(t, out);
            }
        }
        return 0;
    }
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xFC, 1, 0xE);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xFC) {
                if (target != 0) {
                    tbl[k].a[2 + j] = (u32)target;
                }
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[2 + j], 0x27) >= 1
                    || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[j], 7) == 1) {
                    other = (FightOutPokemon*)fightTargetGetPtr(0xE, (FIGHT_TRAINER*)tbl[k].a[2 + j], (u8)fightType);
                    if (other != 0 && fightAi_GetTokuseiHaveFlag(t, other, 0x27) == 0
                        && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, other, 7) == 0) {
                        tbl[k].a[2 + j] = (u32)other;
                    }
                }
            }
        }
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xE && fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)tbl[k].a[j])->getFightPokemonPtr(), 0xE2) != 2) {
                cur = 0;
            }
            if (tbl[k].waza[j] == 0xFC) {
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(tbl[k].waza[j])(t, (FightOutPokemon*)(p = &tbl[k].a[j])[0], tbl[k].waza[j], (FightOutPokemon*)p[2]) == 0) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0x15);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Batontatti_Nekodamasi_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    FightPokemon* irekae[6];
    u16 wazaIds[8];
    FightOutPokemon* target;
    FightOutPokemon* other;
    s32 fightType;
    u16 irekaeNum;
    u8 wazaNum;
    s16 entry;
    u8 total;
    u8 noEffect;
    u8 count;
    s32 dmg;
    s32 bestDmg;
    u8 zok;
    u16 zok0;
    u16 zok1;
    u8 num;
    u8 i;
    u8 j;
    u8 k;
    u8 m;
    u8 n;
    s32 val;
    s16 best;
    s16 cur;
    u16 rnd;
    u8 pct;
    u32* p;

    target = 0;
    total = 0;
    noEffect = 0;
    bestDmg = 0;
    fightType = fightFloor_GetFightType(0);
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    switch (irekaeNum) {
    case 0:
            return 0;
        break;
    }
    for (i = 0; i < irekaeNum; i++) {
        wazaNum = fightTrainerAiGetFightPokemonWazaDataIdAry(t, irekae[i], wazaIds, 0, 1);
        for (j = 0; j < wazaNum; j++) {
            for (m = 0; m < oppCnt; m++) {
                total++;
                zok = fightAi_GetWazaZokuseiData_ThinkWeatherBall(wazaIds[j], 0);
                zok0 = fightTrainerAiGetFightOutPokemonZokuseiDataId(t, oppAry[m], 0);
                zok1 = fightTrainerAiGetFightOutPokemonZokuseiDataId(t, oppAry[m], 1);
                if (zokuseiGetWazaJoutai(zok, zok0) == 0x43 || zokuseiGetWazaJoutai(zok, zok1) == 0x43) {
                    noEffect++;
                }
            }
        }
    }
    if (noEffect >= total) {
        return 0;
    }
    count = 0;
    for (i = 0; i < oppCnt; i++) {
        if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x27) >= 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 7) == 1) {
            count++;
        }
    }
    for (i = 0; i < cnt; i++) {
        if (figthOutPokemonGetPokemonDataId(ary[i]) == 0x12E) {
            for (m = 0; m < oppCnt; m++) {
                entry = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(oppAry[m]));
                for (j = 0; j < 4; j++) {
                    dmg = fightTrainerAiWazaDoWazaDamageFunc(t, oppAry[m], fightTrainer_GetEnemyStoreWazaData((u8*)t, entry, j), ary[i], 0);
                    if (bestDmg < dmg && fightAi_GetTokuseiHaveFlag(t, oppAry[m], 0x27) == 0
                        && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 7) == 0) {
                        bestDmg = dmg;
                        target = oppAry[m];
                    }
                }
                for (j = 0; j < 8; j++) {
                    dmg = fightTrainerAiWazaDoWazaDamageFunc(t, oppAry[m], fightTrainer_GetEnemyExpectWazaData((u8*)t, entry, j), ary[i], 0);
                    if (bestDmg < dmg && fightAi_GetTokuseiHaveFlag(t, oppAry[m], 0x27) == 0
                        && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 7) == 0) {
                        bestDmg = dmg;
                        target = oppAry[m];
                    }
                }
            }
        }
    }
    if (count >= oppCnt) {
        val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
        for (i = 0; i < cnt; i++) {
            for (k = 0; k < 0x40; k++) {
                fightAi_InitAllWazaValidSub(&tbl[k]);
            }
            num = 0;
            fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xB6, 0, 0);
            if (num == 0) {
                return 0;
            }
            best = 0;
            for (k = 0; k < num; k++) {
                tbl[k].a[(s8)fightAi_getAnotherPokeNo(i)] = 0;
                if (tbl[k].waza[i] == 0xB6) {
                    tbl[k].a[2 + i] = tbl[k].a[i];
                }
                cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
                if (tbl[k].waza[i] == 0xB6) {
                    if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(tbl[k].waza[i])(t, (FightOutPokemon*)(p = &tbl[k].a[i])[0], tbl[k].waza[i], (FightOutPokemon*)p[2]) == 0) {
                        cur = 0;
                    }
                    if (fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)p[0])->getFightPokemonPtr(), 0xE2) != 2) {
                        cur = 0;
                    }
                }
                if (best < cur) {
                    buf[0] = k;
                    best = cur;
                    n = 1;
                } else if (best == cur && best > 0) {
                    buf[n] = k;
                    n++;
                }
            }
            rnd = HSD_Rand();
            fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
            pct = HSD_Rand() % 100;
            if (best != 0 && best + bonus > pct) {
                ary[i]->setComboFuncId(0x14);
                fightAi_CreateAction_FromAllWazaValid(t, out);
            }
        }
        return 0;
    }
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xFC, 1, 0xE);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xFC) {
                if (target != 0) {
                    tbl[k].a[2 + j] = (u32)target;
                }
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[2 + j], 0x27) >= 1
                    || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[j], 7) == 1) {
                    other = (FightOutPokemon*)fightTargetGetPtr(0xE, (FIGHT_TRAINER*)tbl[k].a[2 + j], (u8)fightType);
                    if (other != 0 && fightAi_GetTokuseiHaveFlag(t, other, 0x27) == 0
                        && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, other, 7) == 0) {
                        tbl[k].a[2 + j] = (u32)other;
                    }
                }
            }
        }
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xE && fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)tbl[k].a[j])->getFightPokemonPtr(), 0xE2) != 2) {
                cur = 0;
            }
            if (tbl[k].waza[j] == 0xFC) {
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(tbl[k].waza[j])(t, (FightOutPokemon*)(p = &tbl[k].a[j])[0], tbl[k].waza[j], (FightOutPokemon*)p[2]) == 0) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0x14);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Torikku_Kodawarihatimaki_1(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid* e;
    u8 buf[0x40];
    u8 k;
    u8 i;
    s16 best;
    s32 value;
    s16 cur;
    u8 pct;
    u8 j;
    AllWazaValid tbl[0x40];
    u16 rnd;
    u8 n;
    u8 num;

    num = 0;
    value = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    if (fightFloor_GetFightKindDorobouFlag(0) == 1) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        for (k = 0; k < 0x40; k++) {
            fightAi_InitAllWazaValidSub(&tbl[k]);
        }
        num = 0;
        fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x10F, 0, 0);
        if (num == 0) {
            return 0;
        }
        best = 0;
        for (k = 0; k < num; k++) {
            e = &tbl[k];
            cur = fightAiCombo_GetAllWazaValueTable(e, value, t, ary, oppAry, -1);
            tbl[k].a[(s8)fightAi_getAnotherPokeNo(i)] = 0;
            if (best < cur) {
                buf[0] = k;
                best = cur;
                n = 1;
            } else if (best == cur && best > 0) {
                buf[n] = k;
                n++;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
        pct = HSD_Rand() % 100;
        if (best != 0 && best + bonus > pct) {
            ary[i]->setComboFuncId(0);
            fightAi_CreateAction_FromAllWazaValid(t, out);
        }
    }
    return 0;
}

s32 fightAiCombo_Migawari_Kisikaisei_1(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid* e;
    u8 buf[0x40];
    u8 k;
    u8 i;
    s16 best;
    s32 value;
    s16 cur;
    u8 pct;
    AllWazaValid tbl[0x40];
    u16 rnd;
    u8 n;
    u8 num;
    u8 m;

    num = 0;
    value = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < cnt; i++) {
        for (k = 0; k < 0x40; k++) {
            fightAi_InitAllWazaValidSub(&tbl[k]);
        }
        num = 0;
        fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xA4, 0, 0);
        if (num == 0) {
            return 0;
        }
        best = 0;
        for (k = 0; k < num; k++) {
            e = &tbl[k];
            cur = fightAiCombo_GetAllWazaValueTable(e, value, t, ary, oppAry, -1);
            tbl[k].a[(s8)fightAi_getAnotherPokeNo(i)] = 0;
            if (tbl[k].waza[i] == 0xA4) {
                if (fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)tbl[k].a[i])->getFightPokemonPtr(), 0xB3) != 2
                    && fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)tbl[k].a[i])->getFightPokemonPtr(), 0xAF) != 2) {
                    cur = 0;
                }
                for (m = 0; m < 4; m++) {
                    if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[i], moukakeiTbl[m]) == 2) {
                        cur += 0xA;
                    }
                }
                for (m = 0; m < 7; m++) {
                    if (statusUpKinomiTbl[m] == fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, (FightOutPokemon*)tbl[k].a[i])) {
                        cur += 0xA;
                    }
                }
                if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, (FightOutPokemon*)tbl[k].a[i], 0x14) == 1) {
                    cur = 0;
                }
            }
            if (best < cur) {
                buf[0] = k;
                best = cur;
                n = 1;
            } else if (best == cur && best > 0) {
                buf[n] = k;
                n++;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
        pct = HSD_Rand() % 100;
        if (best != 0 && best + bonus > pct) {
            ary[i]->setComboFuncId(0);
            fightAi_CreateAction_FromAllWazaValid(t, out);
        }
    }
    return 0;
}

s32 fightAiCombo_Daibakuhatu_Horobinouta_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 k;
    u8 num;
    u8 j;
    u8 buf[0x40];
    s16 best;
    u8 i;
    s32 val;
    s16 cur;
    u8 n;
    int rnd;
    u8 pct;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && fightAi_GetTokuseiHaveFlag(t, ary[i], 6) >= 1) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 6) >= 1) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x99, 1, 0xC3);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x78, 1, 0xC3);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xC3, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xC3) {
                if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[j], 7) == 0
                    && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[j], 5) == 0
                    && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[j], 8) == 0) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Hakaikousen_Hoeru_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid* e;
    u8 buf[0x40];
    u8 num;
    u8 k;
    s16 cur;
    FightPokemon* irekae[6];
    u16 irekaeNum;
    u8 found;
    u8 j;
    s16 best;
    s32 val;
    u8 n;
    u16 rnd;
    u8 pct;
    AllWazaValid tbl[0x40];
    volatile u32* p;
    u8 i;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (irekaeNum == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x3F, 1, 0x2E);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x152, 1, 0x2E);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x134, 1, 0x2E);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x133, 1, 0x2E);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x3F, 1, 0x12);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x152, 1, 0x12);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x134, 1, 0x12);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x133, 1, 0x12);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    found = 0;
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x16) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2C3);
    }
    best = 0;
    for (k = 0; k < num; k++) {
        e = &tbl[k];
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (e->waza[j] == 0x2E || e->waza[j] == 0x12) {
                e->a[2 + j] = e->a[(s8)fightAi_getAnotherPokeNo((u16)j)];
            }
        }
        cur = fightAiCombo_GetAllWazaValueTable(e, val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (e->waza[j] == 0x2E || e->waza[j] == 0x12) {
                p = &e->a[j];
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(e->waza[j])(t, (FightOutPokemon*)p[0], e->waza[j], (FightOutPokemon*)p[2]) == 0) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Ibaru_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 num;
    u16 rnd;
    u16 irekaeNum;
    u8 j;
    u8 k;
    u8 buf[0x40];
    u8 i;
    u8 found;
    s16 best;
    s32 val;
    s8 another;
    s16 cur;
    u8 n;
    u8 flagA;
    FightPokemon* irekae[6];
    u8 flagB;
    u8 pct;
    AllWazaValid tbl[0x40];

    found = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x14) == 1 || fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(t, irekae[i]) == 8) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xCF, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xCF) {
                another = fightAi_getAnotherPokeNo(j);
                tbl[k].a[2 + j] = tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)];
            }
        }
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xCF) {
                s16 rf_t = tbl[k].a[j];
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(tbl[k].waza[j])(t, (FightOutPokemon*)rf_t, tbl[k].waza[j], (FightOutPokemon*)tbl[k].a[2 + j]) == 0) {
                    cur = 0;
                }
                if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, (FightOutPokemon*)tbl[k].a[2 + (s8)fightAi_getAnotherPokeNo(j)], 0x14) == 1
                    || fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, (FightOutPokemon*)tbl[k].a[2 + (s8)fightAi_getAnotherPokeNo(j)]) == 8) {
                    cur = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x14) != 0 || fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(t, irekae[i]) == 8) {
                s16 id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Horobinouta_Irekae2_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    s16 best;
    u8 found;
    AllWazaValid tbl[0x40];
    u8 pct;
    u8 n;
    u8 j;
    s16 id;
    u16 irekaeNum;
    s32 val;
    u8 num;
    u8 i;
    s8 another;
    u8 k;
    s16 cur;
    u8 buf[0x40];
    u8 flagA;
    u16 rnd;
    u8 flagB;
    FightPokemon* irekae[6];

    found = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x2B) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xC3, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xC3) {
                another = fightAi_getAnotherPokeNo(j);
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x2B) != 0) {
                id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Honoo_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid tbl[0x40];
    FightPokemon* irekae[6];
    u8 buf[0x40];
    u8 num;
    u8 i;
    u8 k;
    u8 j;
    s16 best;
    s16 cur;
    u8 ok;
    u8 n;
    u8 flagA;
    u8 flagB;
    u8 found;
    u16 irekaeNum;
    s8 another;
    s32 val;
    u16 rnd;
    u8 pct;

    found = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x12) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 3, 0xA, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        ok = 0;
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (fightTrainerAiGetWazaZokuseiDataId(t, tbl[k].waza[j], (FightOutPokemon*)tbl[k].a[j]) == 0xA) {
                another = fightAi_getAnotherPokeNo(j);
                if (wazaIsWazaTypeId(tbl[k].waza[j], 1) == 1) {
                    ok = 1;
                }
                if (fightTrainerAiGetWazaZokuseiDataId(t, tbl[k].waza[(s8)fightAi_getAnotherPokeNo(j)], (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)]) == 0xA
                    && wazaIsWazaTypeId(tbl[k].waza[(s8)fightAi_getAnotherPokeNo(j)], 1) == 1) {
                    ok = 1;
                }
                if (ok == 0) {
                    cur = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x12) != 0) {
                s16 id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Dokudoku_Karagenki_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 k;
    AllWazaValid* e;
    s16 best;
    u8 num;
    u8 i;
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    s32 val;
    u8 j;
    u8 n;
    int rnd;
    u8 pct;
    s16 cur;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x5C, 1, 0x107);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x105, 1, 0x107);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x5C, 1);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x105, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        e = &tbl[k];
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (e->waza[j] == 0x107) {
                e->a[2 + (s8)fightAi_getAnotherPokeNo(j)] = e->a[j];
            }
        }
        cur = fightAiCombo_GetAllWazaValueTable(e, val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (e->waza[j] == 0x107) {
                if (fightOutPokemonIsJoutaiKaragenki((FightOutPokemon*)e->a[j]) == 1) {
                    cur = 0;
                }
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)e->a[j], 0x3E) == 2 || fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)e->a[j], 0x3F) == 2) {
                    cur += 10;
                }
                s8 rf_t = e->waza[(s8)fightAi_getAnotherPokeNo(j)];
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(rf_t)(t, (FightOutPokemon*)e->a[(s8)fightAi_getAnotherPokeNo(j)],
                        e->waza[(s8)fightAi_getAnotherPokeNo(j)], (FightOutPokemon*)e->a[2 + (s8)fightAi_getAnotherPokeNo(j)]) == 0) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Horobinouta_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    s16 best;
    u8 j;
    u8 buf[0x40];
    s16 id;
    u8 flagA;
    u8 k;
    u8 i;
    s8 another;
    u8 num;
    AllWazaValid tbl[0x40];
    u8 n;
    s32 val;
    s16 cur;
    u16 irekaeNum;
    FightPokemon* irekae[6];
    u16 rnd;
    u8 flagB;
    u8 pct;
    u8 found;

    found = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && fightAi_GetTokuseiHaveFlag(t, ary[i], 0x17) == 2) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x17) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xC3, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xC3) {
                another = fightAi_getAnotherPokeNo(j);
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x17) != 0) {
                id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Konoyubitomare_Kiaipanti_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s16 val;
    u8 i;
    u8 j;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x10A, 1, 0x108);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetAllWazaMaxValueTable(tbl, (u16)num, fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt), t, ary, oppAry, p5, -1);
    if (val > 0) {
        int r = HSD_Rand();
        if (val + bonus > (u8)(r % 100)) {
            for (j = 0; j < cnt; j++) {
                ary[j]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Konoyubitomare_StatusUp_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 k;
    u8 j;
    u8 num;
    u8 i;
    u8 m;
    AllWazaValid tbl[0x40];
    s16 best;
    s32 val;
    u8 buf[0x40];
    u8 n;
    u16 rnd;
    u8 pct;
    s16 cur;
    AllWazaValid* e;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x10A, 2, 4);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        e = &tbl[k];
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            for (m = 0; m < 0xE; m++) {
                if (e->waza[j] == statusUpWazaTbl[m].waza && fightTrainerAiIsFightOutPokemonAllAbiCntTakai(t, (FightOutPokemon*)e->a[j]) == 1) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Sukirusuwappu_Irekae_1(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid* e;
    u8 buf[0x40];
    u8 k;
    u8 i;
    s16 best;
    s32 value;
    s16 cur;
    u8 pct;
    AllWazaValid tbl[0x40];
    u16 rnd;
    u8 n;
    u8 num;

    num = 0;
    value = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < cnt; i++) {
        for (k = 0; k < 0x40; k++) {
            fightAi_InitAllWazaValidSub(&tbl[k]);
        }
        num = 0;
        fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x11D, 0, 0);
        if (num == 0) {
            return 0;
        }
        best = 0;
        for (k = 0; k < num; k++) {
            e = &tbl[k];
            cur = fightAiCombo_GetAllWazaValueTable(e, value, t, ary, oppAry, -1);
            tbl[k].a[(s8)fightAi_getAnotherPokeNo(i)] = 0;
            if (tbl[k].waza[i] == 0x11D && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[i], 0x36) != 2) {
                cur = 0;
            }
            if (best < cur) {
                buf[0] = k;
                best = cur;
                n = 1;
            } else if (best == cur && best > 0) {
                buf[n] = k;
                n++;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
        pct = HSD_Rand() % 100;
        if (best != 0 && best + bonus > pct) {
            ary[i]->setComboFuncId(0);
            fightAi_CreateAction_FromAllWazaValid(t, out);
        }
    }
    return 0;
}

s32 fightAiCombo_Sukirusuwappu_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 n;
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    u8 num;
    u8 i;
    u8 j;
    u8 k;
    s16 best;
    s16 cur;
    s32 val;
    u16 rnd;
    u8 pct;
    u32* p;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x11D, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0x11D) {
                tbl[k].a[2 + j] = tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)];
            }
        }
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] != 0x11D) {
                p = &tbl[k].a[j];
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)p[0], 0x36) != 2) {
                    cur = 0;
                }
                if (fightTrainerAiIsFightPokemonTokuseiDataId(t, ((FightOutPokemon*)p[0])->getFightPokemonPtr(), 0x36) == 0) {
                    cur = 0;
                }
            }
            switch (tbl[k].waza[j]) {
            case 0x11D:
                    if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(tbl[k].waza[j])(t, (FightOutPokemon*)(p = &tbl[k].a[j])[0], tbl[k].waza[j], (FightOutPokemon*)p[2]) == 0) {
                        cur = 0;
                    }
                    if (tbl[k].waza[(s8)fightAi_getAnotherPokeNo(j)] == 0x11D) {
                        cur = 0;
                    }
                break;
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0x1D);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Sunaarasi_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 num;
    int rnd;
    u16 irekaeNum;
    u8 j;
    u8 k;
    s16 best;
    u8 i;
    s32 val;
    u8 flagA;
    u8 found;
    u8 flagB;
    s8 another;
    u8 n;
    s16 cur;
    FightPokemon* irekae[6];
    u8 buf[0x40];
    u8 pct;
    AllWazaValid tbl[0x40];

    found = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 3) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x8) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xC9, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 5) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 8) == 1
                || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 4) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2C1);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x8) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2C2);
            }
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xC9) {
                another = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x8) == 0) {
                    cur = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x8) != 0) {
                s16 id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Amagoi_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 num;
    int rnd;
    u16 irekaeNum;
    u8 j;
    u8 k;
    s16 best;
    u8 i;
    s32 val;
    u8 flagA;
    u8 found;
    u8 flagB;
    s8 another;
    u8 n;
    s16 cur;
    FightPokemon* irekae[6];
    u8 buf[0x40];
    u8 pct;
    AllWazaValid tbl[0x40];

    found = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 2) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x21) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF0, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 0xB) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2BE);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2C) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2BF);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x21) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2C0);
            }
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xF0) {
                another = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x21) == 0) {
                    cur = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x21) != 0) {
                s16 id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 num;
    int rnd;
    u16 irekaeNum;
    u8 j;
    u8 k;
    s16 best;
    u8 i;
    s32 val;
    u8 flagA;
    u8 found;
    u8 flagB;
    s8 another;
    u8 n;
    s16 cur;
    FightPokemon* irekae[6];
    u8 buf[0x40];
    u8 pct;
    AllWazaValid tbl[0x40];

    found = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x22) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF1, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 0xA) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2BC);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x22) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2BD);
            }
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0xF1) {
                another = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x22) == 0) {
                    cur = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x22) != 0) {
                s16 id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Asanohizasi_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    u8 num;
    u8 k;
    s16 best;
    u8 i;
    u8 j;
    s16 cur;
    s32 val;
    u8 n;
    u16 rnd;
    u8 pct;
    u32* p;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if ((s16)fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF1, 1, 0xEA);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF1, 1, 0xEC);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF1, 1, 0xEB);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xF1, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 10) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2BA);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 34) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2BB);
            }
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            tbl[k].a[2 + j] = tbl[k].a[j];
        }
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            p = &tbl[k].a[j];
            if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(tbl[k].waza[j])(t, (FightOutPokemon*)p[0], tbl[k].waza[j], (FightOutPokemon*)p[2]) == 0) {
                cur = 0;
            }
            if (tbl[k].waza[j] == 0xF1 && fightTrainerAiIsFightOutPokemonNokoriHpHikui(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)]) == 0) {
                cur = 0;
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Amaikaori_Hubuki_1(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid* e;
    u8 buf[0x40];
    u8 k;
    u8 i;
    s16 best;
    s32 value;
    s16 cur;
    u8 pct;
    AllWazaValid tbl[0x40];
    u16 rnd;
    u8 n;
    u8 num;

    num = 0;
    value = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < cnt; i++) {
        for (k = 0; k < 0x40; k++) {
            fightAi_InitAllWazaValidSub(&tbl[k]);
        }
        num = 0;
        fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xE6, 0, 0);
        fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x171, 0, 0);
        if (num == 0) {
            return 0;
        }
        best = 0;
        for (k = 0; k < num; k++) {
            e = &tbl[k];
            cur = fightAiCombo_GetAllWazaValueTable(e, value, t, ary, oppAry, -1);
            tbl[k].a[(s8)fightAi_getAnotherPokeNo(i)] = 0;
            if ((tbl[k].waza[i] == 0xE6 || tbl[k].waza[i] == 0x171) && fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)tbl[k].a[i])->getFightPokemonPtr(), 0x3B) != 2
                && fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)tbl[k].a[i])->getFightPokemonPtr(), 0x9D) != 2) {
                cur = 0;
            }
            if (best < cur) {
                buf[0] = k;
                best = cur;
                n = 1;
            } else if (best == cur && best > 0) {
                buf[n] = k;
                n++;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
        pct = HSD_Rand() % 100;
        if (best != 0 && best + bonus > pct) {
            ary[i]->setComboFuncId(0x2A);
            fightAi_CreateAction_FromAllWazaValid(t, out);
        }
    }
    return 0;
}

s32 fightAiCombo_Amaikaori_Hubuki_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    u8 num;
    u8 i;
    u8 k;
    u8 j;
    s16 best;
    s32 val;
    s16 cur;
    u8 n;
    u16 rnd;
    u8 pct;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xE6, 1, 0x3B);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xE6, 1, 0x9D);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x171, 1, 0x3B);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x171, 1, 0x9D);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xE6, 1);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x171, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].a[2 + j] != tbl[k].a[2 + (s8)fightAi_getAnotherPokeNo(j)] && tbl[k].mode[j] != 2 && tbl[k].mode[(s8)fightAi_getAnotherPokeNo(j)] != 2) {
                cur = 0;
            }
            if (fightTrainerAiIsFightOutPokemonAvoidCntHikui(t, (FightOutPokemon*)tbl[k].a[2 + j]) == 1) {
                cur = 0;
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0x18);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Konran_DefDown_1(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid* e;
    u8 buf[0x40];
    u8 k;
    u8 i;
    s16 best;
    s32 value;
    s16 cur;
    u8 pct;
    AllWazaValid tbl[0x40];
    u16 rnd;
    u8 n;
    u8 num;
    u8 m;
    u8 count;

    num = 0;
    value = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    count = 0;
    for (m = 0; m < oppCnt; m++) {
        if (oppAry[m] != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, oppAry[m], 9) == 0) {
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        for (k = 0; k < 0x40; k++) {
            fightAi_InitAllWazaValidSub(&tbl[k]);
        }
        num = 0;
        fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x12A, 0, 0);
        fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xCF, 0, 0);
        fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x6D, 0, 0);
        if (num == 0) {
            return 0;
        }
        best = 0;
        for (k = 0; k < num; k++) {
            e = &tbl[k];
            cur = fightAiCombo_GetAllWazaValueTable(e, value, t, ary, oppAry, -1);
            tbl[k].a[(s8)fightAi_getAnotherPokeNo(i)] = 0;
            if ((tbl[k].waza[i] == 0x12A || tbl[k].waza[i] == 0xCF || tbl[k].waza[i] == 0x6D) && fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)tbl[k].a[i])->getFightPokemonPtr(), 0x27) != 2
                && fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)tbl[k].a[i])->getFightPokemonPtr(), 0x2B) != 2
                && fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)tbl[k].a[i])->getFightPokemonPtr(), 0x67) != 2) {
                cur = 0;
            }
            if (best < cur) {
                buf[0] = k;
                best = cur;
                n = 1;
            } else if (best == cur && best > 0) {
                buf[n] = k;
                n++;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
        pct = HSD_Rand() % 100;
        if (best != 0 && best + bonus > pct) {
            ary[i]->setComboFuncId(0);
            fightAi_CreateAction_FromAllWazaValid(t, out);
        }
    }
    return 0;
}

s32 fightAiCombo_Konran_DefDown_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid* e;
    u8 buf[0x40];
    u8 num;
    u8 m;
    u8 count;
    u8 i;
    u8 k;
    AllWazaValid tbl[0x40];
    u8 j;
    s16 best;
    s32 val;
    u8 n;
    u16 rnd;
    u8 pct;
    s16 cur;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    count = 0;
    for (m = 0; m < oppCnt; m++) {
        if (oppAry[m] != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, oppAry[m], 9) == 0) {
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x12A, 1, 0x27);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x12A, 1, 0x2B);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x12A, 1, 0x67);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xCF, 1, 0x27);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xCF, 1, 0x2B);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xCF, 1, 0x67);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x6D, 1, 0x27);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x6D, 1, 0x2B);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x6D, 1, 0x67);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        e = &tbl[k];
        cur = fightAiCombo_GetAllWazaValueTable(e, val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (e->waza[j] == 0x12A && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)e->a[(s8)fightAi_getAnotherPokeNo(j)], 0x14) != 2
                && fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, (FightOutPokemon*)e->a[(s8)fightAi_getAnotherPokeNo(j)]) != 8) {
                cur = 0;
            }
            if ((e->waza[j] == 0xCF || e->waza[j] == 0x6D) && e->a[2 + j] != e->a[2 + (s8)fightAi_getAnotherPokeNo(j)]
                && e->mode[j] != 2 && e->mode[(s8)fightAi_getAnotherPokeNo(j)] != 2) {
                cur = 0;
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Makibisi_Hoeru_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    u8 j;
    u8 i;
    u8 trainerNum;
    u8 entryNum;
    u8 fightoutNum;
    AllWazaValid tbl[0x40];
    FightSide* side;
    u8 num;
    s16 val;
    u8 fightType;

    num = 0;
    fightType = fightFloor_GetFightType(0);
    trainerNum = fightFloor_GetFightTypeTrainerNum(0);
    entryNum = fightFloor_GetFightTypeEntryPokemonNum(0);
    fightoutNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    side = fightTargetGetPtr(3, t, fightType);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(side, 0x4A) == 1) {
        return 0;
    }
    if (fightSideGetHikaeFightPokemonNum(side, trainerNum, entryNum, fightoutNum) == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xBF, 1, 0x2E);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xBF, 1, 0x12);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xBF, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt), t, ary, oppAry, p5, -1);
    if (val > 0) {
        int r = HSD_Rand();
        if (val + bonus > (u8)(r % 100)) {
            for (j = 0; j < cnt; j++) {
                ary[j]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_StatusUp_Batontatti_1(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 fightType;
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    u8 num;
    u8 k;
    u8 m;
    u8 none;
    u32* p;
    s16 best;
    s16 cur;
    s32 value;
    u8 n;
    u16 rnd;
    u8 pct;
    bool m2;
    u8 i;
    FightSide* side;
    u8 trainerNum;
    u8 entryNum;
    u8 fightoutNum;

    num = 0;
    fightType = fightFloor_GetFightType(0);
    trainerNum = fightFloor_GetFightTypeTrainerNum(0);
    entryNum = fightFloor_GetFightTypeEntryPokemonNum(0);
    fightoutNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    side = fightTargetGetPtr(2, t, fightType);
    if (fightSideGetHikaeFightPokemonNum(side, trainerNum, entryNum, fightoutNum) == 0) {
        return 0;
    }
    value = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < cnt; i++) {
        for (k = 0; k < 0x40; k++) {
            fightAi_InitAllWazaValidSub(&tbl[k]);
        }
        num;
        m = 0;
        for (m = 0; m < 0xE; m++) {
            fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, statusUpWazaTbl[m].waza, 0, 0);
        }
        if (num == 0) {
            return 0;
        }
        best = 0;
        for (k = 0; k < num; k++) {
            none = 1;
            p = &tbl[k].a[i];
            for (m = 0; m < 0xE; m++) {
                if (tbl[k].waza[i] == statusUpWazaTbl[m].waza) {
                    p[2] = p[0];
                }
            }
            cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], value, t, ary, oppAry, -1);
            tbl[k].a[(s8)fightAi_getAnotherPokeNo(i)] = 0;
            for (m2 = 0; m2 < 0xE; m2++) {
                if (tbl[k].waza[i] == statusUpWazaTbl[m2].waza) {
                    if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(tbl[k].waza[i])(t, (FightOutPokemon*)p[0], tbl[k].waza[i], (FightOutPokemon*)p[2]) == 0) {
                        cur = 0;
                    }
                    none = 0;
                    if (fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)p[0])->getFightPokemonPtr(), 0xE2) != 2) {
                        cur = 0;
                    }
                }
            }
            if (none == 1) {
                cur = 0;
            }
            if (best < cur) {
                buf[0] = k;
                best = cur;
                n = 1;
            } else if (best == cur && best > 0) {
                buf[n] = k;
                n++;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
        pct = HSD_Rand() % 100;
        if (best != 0 && best + bonus > pct) {
            ary[i]->setComboFuncId(0);
            fightAi_CreateAction_FromAllWazaValid(t, out);
        }
    }
    return 0;
}

s32 fightAiCombo_Daibakuhatu_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 num;
    int rnd;
    u16 irekaeNum;
    u8 j;
    u8 k;
    s16 best;
    u8 i;
    s32 val;
    u8 flagA;
    u8 found;
    u8 flagB;
    s8 another;
    u8 n;
    s16 cur;
    FightPokemon* irekae[6];
    u8 buf[0x40];
    u8 pct;
    AllWazaValid tbl[0x40];

    found = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(t, irekae[i], 7) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && fightAi_GetTokuseiHaveFlag(t, ary[i], 6) == 2) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 6) >= 1) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x99, 0, 0);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x78, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 7) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2B6);
            }
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 5) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 8) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2B7);
            }
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0x99 || tbl[k].waza[j] == 0x78) {
                another = fightAi_getAnotherPokeNo(j);
                if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 7) == 1) {
                    cur = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonZokuseiDataId(t, irekae[i], 7) != 0) {
                s16 id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Zisin_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    s16 best;
    s8 another;
    u8 n;
    u8 num;
    u16 rnd;
    u16 irekaeNum;
    u8 j;
    u8 k;
    u8 buf[0x40];
    u8 i;
    s32 val;
    u8 flagA;
    u8 found;
    u8 flagB;
    s16 cur;
    FightPokemon* irekae[6];
    u8 pct;
    AllWazaValid tbl[0x40];

    found = 0;
    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(t, irekae[i], 2) == 1 || fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x1A) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x59, 0, 0);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xDE, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 2) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2B4);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x1A) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2B5);
            }
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0x59 || tbl[k].waza[j] == 0xDE) {
                another = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) == 2) {
                    cur = 0;
                }
                if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 1) {
                    cur = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x1A) != 0 || fightTrainerAiIsFightPokemonZokuseiDataId(t, irekae[i], 2) != 0) {
                s16 id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Hurahuradansu_Irekae_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 k;
    int rnd;
    u16 irekaeNum;
    u8 j;
    u8 num;
    s16 best;
    u8 i;
    s32 val;
    u8 flagA;
    u8 n;
    u8 count;
    u8 flagB;
    s8 another;
    u8 found;
    s16 cur;
    FightPokemon* irekae[6];
    u8 buf[0x40];
    u8 pct;
    AllWazaValid tbl[0x40];

    found = 0;
    num = 0;
    fightFloor_GetFightType(0);
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(t, irekae);
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x14) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, oppAry[i], 9) == 0) {
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x17) >= 1) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x2A) >= 1) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x47) >= 1) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x12A, 0, 0);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x14) >= 1) {
            val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2B3);
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0x12A) {
                another = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x14) == 2) {
                    cur = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 8) == 1) {
                    cur = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 0
                    && fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) != 2) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(t, irekae[i], 0x14) != 0) {
                s16 id = fightPokemon_GetEntryId(irekae[i]);
                if (id >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, (FightOutPokemon*)out->a[(s8)another], 0) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction((FightOutPokemon*)out->a[(s8)another], 0, 9, 0, fight_action_data_turn, id);
                    for (i = 0; i < cnt; i++) {
                        ary[i]->setComboFuncId(0);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Daibakuhatu_Daibakuhatu_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    s16 cur;
    u8 k;
    u8 n;
    u16 rnd;
    u8 pct;
    u32* p;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && fightAi_GetTokuseiHaveFlag(t, ary[i], 6) == 2) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightAi_GetTokuseiHaveFlag(t, oppAry[i], 6) >= 1) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x99, 1, 0x99);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x78, 1, 0x99);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x78, 1, 0x78);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 7) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2B1);
            }
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 5) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 8) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2B2);
            }
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            p = &tbl[k].a[j];
            if (fightFloorCmpfightOutPokemonNimbleness(0, (FightOutPokemon*)p[0], (FightOutPokemon*)tbl[k].a[(s8)fightAi_getAnotherPokeNo(j)], 0) == 0
                && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)p[0], 7) == 0
                && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)p[0], 5) == 0
                && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)p[0], 8) == 0) {
                cur = 0;
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Haradaiko_Zikoanzi_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid* e;
    s16 best;
    u8 num;
    u8 i;
    AllWazaValid tbl[0x40];
    u8 j;
    u8 buf[0x40];
    s32 val;
    s16 cur;
    u8 k;
    u8 n;
    int rnd;
    u8 pct;
    volatile u32* p;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < (u8)ai_allwaza_valid_work; i++) {
        if (ary[i] != 0 && fightOutPokemon_GetAbicntPhyAtk(ary[i]) >= 12) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xBB, 1, 0xF4);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xBB, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        e = &tbl[k];
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (e->waza[j] == 0xF4) {
                e->a[2 + j] = e->a[(s8)fightAi_getAnotherPokeNo(j)];
            }
        }
        cur = fightAiCombo_GetAllWazaValueTable(e, val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            switch (e->waza[j]) {
            case 0xF4:
                    p = &e->a[j];
                    if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(e->waza[j])(t, (FightOutPokemon*)p[0], e->waza[j], (FightOutPokemon*)p[2]) == 0) {
                        cur = 0;
                    }
                break;
            }
            if (e->waza[j] == 0xBB && fightOutPokemonGetNowHpPercentage((FightOutPokemon*)e->a[j]) <= 50) {
                cur = 0;
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Zisin_Mamoru_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 buf[0x40];
    u8 num;
    u8 i;
    u8 k;
    AllWazaValid tbl[0x40];
    u8 j;
    u8 m;
    s16 best;
    AllWazaValid* e;
    s16 cur;
    u8 n;
    s32 val;
    u16 rnd;
    u8 pct;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x99, 1, 0xB6);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x78, 1, 0xB6);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x59, 1, 0xB6);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xDE, 1, 0xB6);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        e = &tbl[k];
        cur = fightAiCombo_GetAllWazaValueTable(e, (u16)val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (e->waza[j] == 0xB6 && fightOutPokemon_GetLastUseWazaDataId((FightOutPokemon*)e->a[j]) == 0xB6) {
                cur = 0;
            }
            if (e->waza[j] == 0x59 || e->waza[j] == 0xDE) {
                for (m = 0; m < oppCnt; m++) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 2) == 1) {
                        cur -= 10;
                    }
                }
                if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, (FightOutPokemon*)e->a[(s8)fightAi_getAnotherPokeNo(j)], 2) == 1) {
                    cur = 0;
                }
                if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)e->a[(s8)fightAi_getAnotherPokeNo(j)], 0x1A) == 2) {
                    cur = 0;
                }
            }
            if (e->waza[j] == 0x99 || e->waza[j] == 0x78) {
                if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, (FightOutPokemon*)e->a[j], 6) == 1
                    || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, (FightOutPokemon*)e->a[j], 6) == 1) {
                    cur = 0;
                }
                for (m = 0; m < oppCnt; m++) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 7) == 1) {
                        cur -= 30;
                    }
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 5) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 8) == 1) {
                        cur -= 10;
                    }
                    if (fightAi_GetTokuseiHaveFlag(t, oppAry[m], 6) >= 1) {
                        cur = 0;
                    }
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Tedasuke_Iryoku_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 buf[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    s16 cur;
    u8 k;
    u8 n;
    u16 rnd;
    u8 pct;
    u32* p;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x10E, 2, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (k = 0; k < num; k++) {
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] == 0x10E) {
                p = &tbl[k].a[j];
                if (fightFloorCmpfightOutPokemonNimbleness(0, (FightOutPokemon*)p[0], (FightOutPokemon*)p[2], 1) == 1
                    && fightFloorCmpfightOutPokemonNimbleness(0, (FightOutPokemon*)tbl[k].a[fightAi_getAnotherPokeNo(j)], (FightOutPokemon*)p[2], 1) == 0) {
                    val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2B0);
                }
            }
        }
    }
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].waza[j] != 0x10E) {
                p = &tbl[k].a[j];
                if (fightTrainerAiWazaDoWazaDamageFunc(t, (FightOutPokemon*)p[0], tbl[k].waza[j], (FightOutPokemon*)p[2], 0)
                    > ((FightOutPokemon*)p[2])->getFightPokemonPtr()->getPokemonBuffPtr()->getHp()) {
                    cur = 0;
                }
                if (fightTrainerAiWazaDoWazaDamageFunc(t, (FightOutPokemon*)p[0], tbl[k].waza[j], (FightOutPokemon*)p[2], 0) * 150 / 100
                    < ((FightOutPokemon*)p[2])->getFightPokemonPtr()->getPokemonBuffPtr()->getHp()) {
                    cur = 0;
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Daibakuhatu_Koraeru_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 j;
    s16 best;
    s16 cur;
    u8 num;
    u8 i;
    AllWazaValid tbl[0x40];
    u8 m;
    u8 buf[0x40];
    s32 val;
    u8 n;
    AllWazaValid* e;
    u8 k;
    int rnd;
    u8 pct;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x99, 1, 0xCB);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x78, 1, 0xCB);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x59, 1, 0xCB);
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xDE, 1, 0xCB);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        e = &tbl[k];
        cur = fightAiCombo_GetAllWazaValueTable(e, val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (e->waza[j] == 0xCB) {
                for (m = 0; m < 4; m++) {
                    if (fightAi_GetTokuseiHaveFlag(t, (FightOutPokemon*)e->a[j], moukakeiTbl[m]) == 2) {
                        cur += 10;
                    }
                }
                if (fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)e->a[j])->getFightPokemonPtr(), 0xB3) == 2
                    || fightAi_GetWazaHaveFlag(t, ((FightOutPokemon*)e->a[j])->getFightPokemonPtr(), 0xAF) == 2) {
                    cur += 10;
                }
                for (m = 0; m < 7; m++) {
                    if (statusUpKinomiTbl[m] == fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(t, (FightOutPokemon*)e->a[j])) {
                        cur += 10;
                    }
                }
                if (fightOutPokemon_GetLastUseWazaDataId((FightOutPokemon*)e->a[j]) == 0xCB) {
                    cur = 0;
                }
            }
            if (e->waza[j] == 0x59 || e->waza[j] == 0xDE) {
                for (m = 0; m < oppCnt; m++) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 2) == 1) {
                        cur -= 10;
                    }
                }
            }
            if (e->waza[j] == 0x99 || e->waza[j] == 0x78) {
                if (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, (FightOutPokemon*)e->a[j], 6) == 1
                    || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, (FightOutPokemon*)e->a[j], 6) == 1) {
                    cur = 0;
                }
                for (m = 0; m < oppCnt; m++) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 7) == 1) {
                        cur -= 30;
                    }
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 5) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[m], 8) == 1) {
                        cur -= 10;
                    }
                    if (fightAi_GetTokuseiHaveFlag(t, oppAry[m], 6) >= 1) {
                        cur = 0;
                    }
                }
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Nemurase_Yumekui_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, AllWazaValid* out, u8 bonus) {
    u8 count;
    u8 buf[0x40];
    u8 num;
    u8 i;
    u8 k;
    u8 j;
    u8 n;
    s16 best;
    s32 val;
    s16 cur;
    AllWazaValid tbl[0x40];
    u16 rnd;
    u8 pct;

    num = 0;
    count = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, oppAry[i], 8) == 0) {
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, NemuraseWazaTbl[i], 1, 0x8A);
        fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, NemuraseWazaTbl[i], 1);
    }
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    best = 0;
    for (k = 0; k < num; k++) {
        cur = fightAiCombo_GetAllWazaValueTable(&tbl[k], val, t, ary, oppAry, -1);
        for (j = 0; j < (u8)ai_allwaza_valid_work; j++) {
            if (tbl[k].a[2 + j] != tbl[k].a[2 + (s8)fightAi_getAnotherPokeNo(j)] && tbl[k].mode[j] != 2 && tbl[k].mode[(s8)fightAi_getAnotherPokeNo(j)] != 2) {
                cur = 0;
            }
        }
        if (best < cur) {
            buf[0] = k;
            best = cur;
            n = 1;
        } else if (best == cur && best > 0) {
            buf[n] = k;
            n++;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(out, &tbl[buf[rnd % n]]);
    pct = HSD_Rand() % 100;
    if (best != 0 && best + bonus > pct) {
        for (i = 0; i < cnt; i++) {
            ary[i]->setComboFuncId(0);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Kinokonohousi_Kiaipanti_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    s16 val;
    AllWazaValid tbl[0x40];
    u8 j;
    u8 i;
    u8 found;
    u8 num;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    found = 0;
    for (j = 0; j < oppCnt; j++) {
        if (oppAry[j] != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, oppAry[j], 8) == 0) {
            found++;
        }
    }
    if (found == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x93, 1, 0x108);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt), t, ary, oppAry, p5, -1);
    if (val > 0) {
        int r = HSD_Rand();
        if (val + bonus > (u8)(r % 100)) {
            for (j = 0; j < cnt; j++) {
                ary[j]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_DarkWeather_Whezaabooru_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    u8 k;
    int r;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x16F, 1, 0x137);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x16F, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(ary[i])) == 1) {
            val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2AF);
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(oppAry[i])) == 1) {
            val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2AE);
        }
    }
    best = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, val, t, ary, oppAry, p5, 5);
    if (best > 0) {
        r = HSD_Rand();
        if (best + bonus > (u8)(r % 100)) {
            for (i = 0; i < cnt; i++) {
                ary[i]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Arare_Whezaabooru_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    u8 k;
    int r;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0x102, 1, 0x137);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0x102, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 15) == 1) {
            val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2AD);
        }
    }
    best = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, val, t, ary, oppAry, p5, 4);
    if (best > 0) {
        r = HSD_Rand();
        if (best + bonus > (u8)(r % 100)) {
            for (i = 0; i < cnt; i++) {
                ary[i]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Sunaarasi_Whezaabooru_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    u8 k;
    int r;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xC9, 1, 0x137);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xC9, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 5) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 8) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 4) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2AB);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 8) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2AC);
            }
        }
    }
    best = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, val, t, ary, oppAry, p5, 3);
    if (best > 0) {
        r = HSD_Rand();
        if (best + bonus > (u8)(r % 100)) {
            for (i = 0; i < cnt; i++) {
                ary[i]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Amagoi_Whezaabooru_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    u8 k;
    int r;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 2) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF0, 1, 0x137);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xF0, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 11) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A8);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 44) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A9);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 33) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2AA);
            }
        }
    }
    best = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, val, t, ary, oppAry, p5, 2);
    if (best > 0) {
        r = HSD_Rand();
        if (best + bonus > (u8)(r % 100)) {
            for (i = 0; i < cnt; i++) {
                ary[i]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Whezaabooru_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    u8 k;
    int r;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF1, 1, 0x137);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xF1, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 10) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A6);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 34) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A7);
            }
        }
    }
    best = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, val, t, ary, oppAry, p5, 1);
    if (best > 0) {
        r = HSD_Rand();
        if (best + bonus > (u8)(r % 100)) {
            for (i = 0; i < cnt; i++) {
                ary[i]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Amagoi_Mizu_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    u8 k;
    int r;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 2) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF0, 3, 0xB);
    fightAi_AllWazaValid_DelComboList(t, tbl, &num, 1, 0xF0, 2, 1, 1);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xF0, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 11) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A3);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 44) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A4);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 33) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A5);
            }
        }
    }
    best = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, val, t, ary, oppAry, p5, 2);
    if (best > 0) {
        r = HSD_Rand();
        if (best + bonus > (u8)(r % 100)) {
            for (i = 0; i < cnt; i++) {
                ary[i]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Amagoi_Kaminari_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    u8 k;
    int r;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 2) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF0, 1, 0x57);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xF0, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 11) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A0);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 44) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A1);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 33) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x2A2);
            }
        }
    }
    best = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, val, t, ary, oppAry, p5, 2);
    if (best > 0) {
        r = HSD_Rand();
        if (best + bonus > (u8)(r % 100)) {
            for (i = 0; i < cnt; i++) {
                ary[i]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Honoo_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    u8 k;
    int r;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, ary[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(t, ary[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF1, 3, 0xA);
    fightAi_AllWazaValid_DelComboList(t, tbl, &num, 1, 0xF1, 2, 1, 1);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xF1, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 10) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x29E);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 34) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x29F);
            }
        }
    }
    best = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, val, t, ary, oppAry, p5, 1);
    if (best > 0) {
        r = HSD_Rand();
        if (best + bonus > (u8)(r % 100)) {
            for (i = 0; i < cnt; i++) {
                ary[i]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Sooraabiimu_2(FIGHT_TRAINER* t, FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt, s32 p5, u8 bonus) {
    AllWazaValid tbl[0x40];
    u8 num;
    s32 val;
    s16 best;
    u8 i;
    u8 j;
    u8 k;
    int r;

    num = 0;
    for (i = 0; i < 0x40; i++) {
        fightAi_InitAllWazaValidSub(&tbl[i]);
    }
    if ((u8)ai_allwaza_valid_work < 2) {
        return 0;
    }
    if (cnt < 2) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 0;
    }
    for (i = 0; i < cnt; i++) {
        if (ary[i] != 0 && (fightTrainerAiIsFightOutPokemonTokuseiDataId(t, ary[i], 0x4D) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(t, ary[i], 0xD) == 1)) {
            return 0;
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0 && (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0x4D) >= 1 || fightAi_GetTokuseiHaveFlag(t, oppAry[i], 0xD) >= 1)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(t, tbl, &num, 1, 0xF1, 1, 0x4C);
    fightAi_AllWazaValid_DelListFromSpeed(t, tbl, &num, 0xF1, 1);
    if (num == 0) {
        return 0;
    }
    val = fightAiCombo_GetValidValue(ary, cnt, oppAry, oppCnt);
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(t, oppAry[i], 10) == 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x29C);
            }
            if (fightAi_GetTokuseiHaveFlag(t, oppAry[i], 34) >= 1) {
                val = fightTrainerAiAddValueByAddsubDataId(val, t, 0x29D);
            }
        }
    }
    best = fightAiCombo_GetAllWazaMaxValueTable(tbl, num, val, t, ary, oppAry, p5, 1);
    if (best > 0) {
        r = HSD_Rand();
        if (best + bonus > (u8)(r % 100)) {
            for (i = 0; i < cnt; i++) {
                ary[i]->setComboFuncId(0);
            }
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_null(void) {
    return 0;
}

s8 fightAi_getAnotherPokeNo(u8 n) {
    if (n == 0) {
        return 1;
    }
    return (n != 1) ? (s8)-1 : (s8)0;
}

}
