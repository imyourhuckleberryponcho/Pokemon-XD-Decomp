// DRAFT (2026-10-18, drafter): fixed-action and combo AI. Unit order is asm order; see notes in the report.
#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FIGHT_FLOOR;
struct FightPokemon;
struct Pokemon;
struct DeckTrainer;
struct FightEncountData;

struct FightOutPokemon {
    u32 data[548];
};

// One candidate combo attack: two attackers, their two targets, the moves and the evaluated values.
struct AI_ALLWAZA_VALID_TBL {
    FightOutPokemon* poke[2];
    FightOutPokemon* target[2];
    u16 waza[2];
    u16 unk14;
    u8 mode[2];
    u8 stat[4];
    u16 val[2][2];
    u8 rest[8];
};

struct StatusWazaEntry {
    u16 waza;
    u16 kind;
    u16 limit;
};

struct ComboData {
    u8 type;
    u8 order;
    u8 pad[2];
    u8 (*func)(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, s32, u8);
    u8 (*continueFunc)(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16);
};

struct FixAiShell {
    u8 flag;
    u8* act[2];
};

extern StatusWazaEntry statusUpWazaTbl[];
extern StatusWazaEntry statusDownWazaTbl[];
extern u16 NemuraseWazaTbl[];
extern u16 KonranWazaTbl[];
extern u16 DokuWazaTbl[];
extern u16 MahiWazaTbl[];
extern u16 YakedoWazaTbl[];
extern ComboData comboid[];

extern "C" {
u16 HSD_Rand();
u16 fightFloor_GetEncountDataId(u32);
u32 fightFloor_GetTurnCount(u32);
u32 fightFloor_GetFightType(u32);
u8 fightFloorIsNowEncountVirtualBattle(u32);
FightEncountData* fightEncountDataBiosGetPtr(u16 id);
u16 fightEncountDataBiosGetDiskId(FightEncountData*);
u16 fightEncountDataBiosGetFightTrainerDataId(FightEncountData*, u8);
u16 deckDataVirtualDB_GetEnemyDeck__FUs(u16);
DeckTrainer* getDeckTrainerObj__11DeckTrainerFUl(u32);
u16 getFixedActionID__11DeckTrainerCFv(DeckTrainer*);
u16 getComboID__11DeckTrainerCFUc(DeckTrainer*, u8);
u8 getComboActive__11DeckTrainerCFUc(DeckTrainer*, u8);
u8 getComboFuncId__15FightOutPokemonFv(FightOutPokemon*);
void setComboFuncId__15FightOutPokemonFUc(FightOutPokemon*, u8);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
FightOutPokemon* fightTrainer_GetFightoutPokemonPtr(FIGHT_TRAINER*, u8);
u8 fightOutPokemon_GetFixAiWaza(FightOutPokemon*);
void fightOutPokemon_SetFixAiWaza(FightOutPokemon*, u8);
void fightOutPokemon_SetFixAiDef(FightOutPokemon*, u8);
u8 (*wazaDB_GetFightTrainerAiWazaHitFuncPtr(u16))(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
u8 fightOutPokemonIsHinsi(FightOutPokemon*);
u8 fightAi_CanMoveAppointWaza(FIGHT_TRAINER*, FightOutPokemon*, u16);
void* fightTargetGetPtr(u8, void*, u8);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u16 pokemon_GetPokemonWazaDataId(Pokemon*, u16);
u16 pokemon_GetHp(Pokemon*);
s8 fightAi_getAnotherPokeNo(u8);
u8 fightFloorCmpfightOutPokemonNimbleness(FIGHT_FLOOR*, FightOutPokemon*, FightOutPokemon*, u8);
FIGHT_TRAINER* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(FIGHT_FLOOR*, FightOutPokemon*);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(FIGHT_FLOOR*, FIGHT_TRAINER*, FightOutPokemon**, u8, u8);
s16 fightTrainerAiAddValueByAddsubDataId(s16, FIGHT_TRAINER*, u16);
u8 wazaIsWazaTypeId(u16, u8);
s32 fightAi_ThreatEnemyValue(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon*, s8, u8, s32, s32);
u8 fightAi_HitCheckWazaAboutJoutaiAndType(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER*, FightOutPokemon*, u16);
u32 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonAbiCntAvg(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonAbiCntAvd(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
s32 fightAi_CopyAllWazaValidTable(AI_ALLWAZA_VALID_TBL*, AI_ALLWAZA_VALID_TBL*);
void fightAi_CreateAction_FromAllWazaValid(FIGHT_TRAINER*, AI_ALLWAZA_VALID_TBL*);
}

extern u8 fixAct_v02_1[5];
extern u8 fixAct_v04_1[5];
extern u8 fixAct_v04_2[5];
extern u8 fixAct_v05_1[9];
extern u8 fixAct_v07_1[7];
extern u8 fixAct_v09_1[5];
extern u8 fixAct_v10_1[3];
extern u8 fixAct_v12_1[5];
extern u8 fixAct_v24_1[5];
extern u8 fixAct_v25_1[7];
extern u8 fixAct_v25_2[7];
extern u8 fixAct_v26_1[5];
extern u8 fixAct_v27_1[5];
extern u8 fixAct_v30_1[7];
extern u8 fixAct_v35_1[11];
extern u8 fixAct_v35_2[11];
extern u8 fixAct_v18_1[11];
extern u8 fixAct_t01_1[7];
extern u8 fixAct_oore1[3];

FixAiShell fixAiShell[17] = {
    {0, {0, 0}},
    {0, {fixAct_v02_1, 0}},
    {0, {fixAct_v04_1, fixAct_v04_2}},
    {0, {fixAct_v05_1, 0}},
    {0, {fixAct_v07_1, 0}},
    {0, {fixAct_v10_1, 0}},
    {0, {fixAct_v12_1, 0}},
    {1, {fixAct_v24_1, fixAct_v24_1}},
    {0, {fixAct_v25_1, fixAct_v25_2}},
    {1, {fixAct_v26_1, fixAct_v26_1}},
    {0, {fixAct_v27_1, fixAct_v27_1}},
    {0, {fixAct_v30_1, fixAct_v30_1}},
    {1, {fixAct_v35_1, fixAct_v35_2}},
    {0, {fixAct_v18_1, 0}},
    {0, {fixAct_t01_1, 0}},
    {0, {fixAct_oore1, 0}},
    {0, {fixAct_v09_1, 0}},
};

// Fixed-action script data (indexed by the deck's fixed action id).
u8 fixAct_v02_1[5] = {1, 3, 2, 3, 7};
u8 fixAct_v04_1[5] = {1, 5, 1, 5, 6};
u8 fixAct_v04_2[5] = {1, 5, 2, 5, 6};
u8 fixAct_v05_1[9] = {1, 3, 2, 3, 3, 3, 4, 3, 6};
u8 fixAct_v07_1[7] = {1, 5, 2, 3, 3, 3, 6};
u8 fixAct_v09_1[5] = {1, 4, 2, 3, 6};
u8 fixAct_v10_1[3] = {1, 3, 7};
u8 fixAct_v12_1[5] = {1, 3, 2, 5, 6};
u8 fixAct_v24_1[5] = {1, 5, 2, 5, 7};
u8 fixAct_v25_1[7] = {1, 5, 2, 5, 3, 5, 6};
u8 fixAct_v25_2[7] = {1, 5, 2, 5, 2, 5, 6};
u8 fixAct_v26_1[5] = {1, 5, 2, 5, 7};
u8 fixAct_v27_1[5] = {1, 5, 2, 5, 6};
u8 fixAct_v30_1[7] = {1, 5, 2, 5, 3, 5, 7};
u8 fixAct_v35_1[11] = {4, 4, 3, 5, 2, 5, 4, 5, 4, 5, 6};
u8 fixAct_v35_2[11] = {1, 5, 3, 4, 3, 3, 3, 3, 3, 3, 6};
u8 fixAct_v18_1[11] = {1, 5, 1, 5, 1, 5, 1, 5, 2, 5, 6};
u8 fixAct_t01_1[7] = {1, 5, 2, 5, 3, 5, 7};
u8 fixAct_oore1[3] = {1, 2, 6};

extern "C" {

void fightAi_FixedActIrekaeInit(FightOutPokemon* poke) {
    DeckTrainer* deck;
    deck = getDeckTrainerObj__11DeckTrainerFUl(deckDataVirtualDB_GetEnemyDeck__FUs(fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0)))));
    if (fixAiShell[(u8)getFixedActionID__11DeckTrainerCFv(deck)].flag == 0) {
        fightOutPokemon_SetFixAiWaza(poke, 6);
    }
}

bool fightAi_FixedActCheck(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 waza, FightOutPokemon* target) {
    u8 (*hit)(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*) = wazaDB_GetFightTrainerAiWazaHitFuncPtr(waza);
    if (trainer == 0) {
        return 0;
    }
    if (attacker == 0) {
        return 0;
    }
    if (target == 0) {
        return 0;
    }
    if (hit(trainer, attacker, waza, target) == 0) {
        return 0;
    }
    if (fightOutPokemonIsHinsi(target) == 1) {
        return 0;
    }
    return fightAi_CanMoveAppointWaza(trainer, attacker, waza) != 0;
}

void* fightAi_GetWazaDataIDFromFixActDef(FightOutPokemon* poke, void* trainer, u8 def) {
    u8 fightType = fightFloor_GetFightType(0);
    switch (def) {
    case 1:
        return trainer;
    case 2:
        return fightTargetGetPtr(0xE, trainer, fightType);
    case 3:
        return fightTargetGetPtr(0xF, trainer, fightType);
    case 4:
        return fightTargetGetPtr(0x10, trainer, fightType);
    default:
        return 0;
    }
}

u16 fightAi_GetWazaDataIDFromFixActWaza(FIGHT_TRAINER* trainer, FightOutPokemon* poke, u8 slot) {
    switch (slot) {
    case 1:
    case 2:
    case 3:
    case 4:
        return pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(poke), slot - 1);
    }
    return 0;
}

void fightAi_FixedAct(FIGHT_TRAINER* trainer) {
    s32 n;
    u8 turn = fightFloor_GetTurnCount(0);
    u8 b;
    FightEncountData* enc;
    u32 trainerId;
    DeckTrainer* deck;
    FixAiShell* shell;
    u8 i;
    u8 k;
    s32 t;
    FightOutPokemon* poke;
    u8 idx;
    u8 a;
    u8 cnt[2] = {0, 0};

    enc = fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0));
    if (fightFloorIsNowEncountVirtualBattle(0) == 1) {
        trainerId = deckDataVirtualDB_GetEnemyDeck__FUs(fightEncountDataBiosGetDiskId(enc));
    } else {
        trainerId = fightEncountDataBiosGetFightTrainerDataId(enc, 1);
    }
    deck = getDeckTrainerObj__11DeckTrainerFUl(trainerId);
    shell = &fixAiShell[(u8)getFixedActionID__11DeckTrainerCFv(deck)];
    u8* acts[2] = {0, 0};
    acts[0] = shell->act[0];
    acts[1] = shell->act[1];
    for (i = 0; i < 2; i++) {
        if (acts[i] != 0) {
            for (k = 0; k < 10; k++) {
                u8 v = acts[i][k];
                cnt[i]++;
                if (v == 6) {
                    break;
                }
                if (v == 7) {
                    break;
                }
            }
        }
    }
    t = (turn - 1);
    t *= 2;
    for (i = 0; i < 2; i++) {
        poke = fightTrainer_GetFightoutPokemonPtr(trainer, (u8)i);
        if (fightOutPokemon_GetFixAiWaza(poke) == 6) {
            continue;
        }
        fightOutPokemon_SetFixAiDef(poke, 0);
        if (acts[i] == 0) {
            continue;
        }
        {
            n = cnt[i] - 1;
            if (t < n) {
                idx = t;
            } else if (n == t) {
                idx = t;
                if (acts[i][idx] == 6) {
                    fightOutPokemon_SetFixAiWaza(poke, 6);
                    continue;
                } else if (acts[i][idx] == 7) {
                    idx = t % n;
                }
            } else {
                idx = t % n;
            }
        }
        a = acts[i][idx];
        b = acts[i][idx + 1];
        if (a < 6) {
            if (a) {
                fightOutPokemon_SetFixAiWaza(poke, 6);
            } else if (a >= 0) {
                fightOutPokemon_SetFixAiWaza(poke, a);
            }
        }
        if (b == 0) {
            fightOutPokemon_SetFixAiWaza(poke, 6);
        } else if (b >= 0 && b < 6) {
            fightOutPokemon_SetFixAiDef(poke, b);
        }
    }
}

s32 fightAiCombo_GetValidValue(FightOutPokemon** ary, u16 cnt, FightOutPokemon** oppAry, u16 oppCnt) {
    s32 value = 0x32;
    FightOutPokemon* fastA = 0;
    FightOutPokemon* slowA = 0;
    FightOutPokemon* fastB = 0;
    FightOutPokemon* slowB = 0;
    u8 i;

    for (i = 0; i < cnt; i++) {
        if (ary[i] == 0 && ary[fightAi_getAnotherPokeNo(i)] != 0) {
            fastA = ary[fightAi_getAnotherPokeNo(i)];
            slowA = ary[fightAi_getAnotherPokeNo(i)];
        } else if (ary[i] != 0 && ary[fightAi_getAnotherPokeNo(i)] == 0) {
            fastA = ary[i];
            slowA = ary[i];
        } else if (fightFloorCmpfightOutPokemonNimbleness(0, ary[i], ary[fightAi_getAnotherPokeNo(i)], 0) == 1) {
            fastA = ary[i];
            slowA = ary[fightAi_getAnotherPokeNo(i)];
        } else {
            fastA = ary[fightAi_getAnotherPokeNo(i)];
            slowA = ary[i];
        }
    }
    for (i = 0; i < oppCnt; i++) {
        if (oppAry[i] == 0 || oppAry[fightAi_getAnotherPokeNo(i)] != 0) {
            fastB = oppAry[fightAi_getAnotherPokeNo(i)];
            slowB = oppAry[fightAi_getAnotherPokeNo(i)];
        } else if (oppAry[i] != 0 || oppAry[fightAi_getAnotherPokeNo(i)] == 0) {
            fastB = oppAry[i];
            slowB = oppAry[i];
        } else if (fightFloorCmpfightOutPokemonNimbleness(0, oppAry[i], oppAry[fightAi_getAnotherPokeNo(i)], 0) == 1) {
            fastB = oppAry[i];
            slowB = oppAry[fightAi_getAnotherPokeNo(i)];
        } else {
            fastB = oppAry[fightAi_getAnotherPokeNo(i)];
            slowB = oppAry[i];
        }
    }
    if (fightFloorCmpfightOutPokemonNimbleness(0, slowB, slowA, 0) == 0) {
        value = fightTrainerAiAddValueByAddsubDataId(0x32, fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, slowA), 0x297);
    }
    if (fightFloorCmpfightOutPokemonNimbleness(0, fastB, fastA, 0) == 1) {
        value = fightTrainerAiAddValueByAddsubDataId(value, fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, slowA), 0x298);
    }
    fightFloorCmpfightOutPokemonNimbleness(0, slowA, fastB, 0);
    return value;
}

}

static void _GetAllWazaTableValue_IryokuWaza(FIGHT_TRAINER* t, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* tbl, s16* pval);
static void _GetAllWazaTableValue_JoutaiChangeWaza(FIGHT_TRAINER* t, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* tbl, s16* pval);
static void _GetAllWazaTableValue_JoutaiChangeWazaSub(FIGHT_TRAINER* t, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* tbl, s16* pval, u8 state);
static void _GetAllWazaTableValue_StatusDownWaza(FIGHT_TRAINER* t, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* tbl, s16* pval);
static void _GetAllWazaTableValue_StatusUpWaza(FIGHT_TRAINER* t, AI_ALLWAZA_VALID_TBL* tbl, s16* pval);

extern "C" {
s16 fightAiCombo_GetAllWazaTableDefValue(FIGHT_TRAINER* t, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* tbl, s16 base, s8 mode) {
    FightOutPokemon* ary[6];
    s16 val;
    u16 cnt;
    s32 prod;
    u8 i;
    u8 j;
    s32 sum;

    cnt = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    prod = base * ((tbl->stat[0] + tbl->stat[1]) / 2);
    val = (u8)(prod / 100);
    _GetAllWazaTableValue_IryokuWaza(t, foes, tbl, &val);
    _GetAllWazaTableValue_JoutaiChangeWaza(t, foes, tbl, &val);
    _GetAllWazaTableValue_StatusDownWaza(t, foes, tbl, &val);
    _GetAllWazaTableValue_StatusUpWaza(t, tbl, &val);
    if (val <= 0) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        if (cnt >= 2) {
            if (tbl->poke[i] == 0) {
                continue;
            }
            if ((u8)wazaIsWazaTypeId(tbl->waza[i], 1) == 1) {
                s32 a = fightAi_ThreatEnemyValue(t, tbl->poke[i], ary[0], mode, 0, -1, -1);
                s32 b = fightAi_ThreatEnemyValue(t, tbl->poke[i], ary[1], mode, 0, -1, -1);
                switch (tbl->mode[i]) {
                case 0:
                    val += a - b;
                    break;
                case 1:
                    val += b - a;
                    break;
                }
            }
        }
        sum = 0;
        for (j = 0; j < 2; j++) {
            sum += tbl->val[j][i];
        }
        if (tbl->target[i] != 0) {
            u16 hp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(tbl->target[i]));
            if (hp != 0) {
                val += (sum * 100 / hp) / 10;
            }
        }
    }
    if (val < 0) {
        val = 0;
    }
    return val;
}
}

static void _GetAllWazaTableValue_StatusUpWaza(FIGHT_TRAINER* t, AI_ALLWAZA_VALID_TBL* tbl, s16* pval) {
    s16 val = *pval;
    u8 i;
    u8 j;

    for (i = 0; i < 2; i++) {
        if (tbl->poke[i] != 0) {
            for (j = 0; j < 14; j++) {
                StatusWazaEntry* e = &statusUpWazaTbl[j];
                if (tbl->waza[i] == e->waza && tbl->poke[i] != 0) {
                    int cur;
                    switch (e->kind) {
                    case 1:
                        cur = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, tbl->poke[i]);
                        break;
                    case 2:
                        cur = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, tbl->poke[i]);
                        break;
                    case 3:
                        cur = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, tbl->poke[i]);
                        break;
                    case 4:
                        cur = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(t, tbl->poke[i]);
                        break;
                    case 5:
                        cur = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, tbl->poke[i]);
                        break;
                    case 6:
                        cur = fightTrainerAiGetFightOutPokemonAbiCntAvg(t, tbl->poke[i]);
                        break;
                    case 7:
                        cur = fightTrainerAiGetFightOutPokemonAbiCntAvd(t, tbl->poke[i]);
                        break;
                    }
                    if (cur + e->limit > 12) {
                        val = 0;
                    }
                }
            }
        }
    }
    *pval = val;
}

static void _GetAllWazaTableValue_StatusDownWaza(FIGHT_TRAINER* t, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* tbl, s16* pval) {
    u16 tokusei[3];
    u32 k;
    u8 i;
    u8 j;
    u32 cur;
    u8 m;
    s16 val = *pval;
    u8 num;

    tokusei[0] = 0x1D;
    tokusei[1] = 0x49;
    for (i = 0; i < 2; i++) {
        if (tbl->poke[i] != 0) {
            for (j = 0; j < 18; j++) {
                StatusWazaEntry* e = &statusDownWazaTbl[j];
                if (tbl->waza[i] == e->waza) {
                    switch (tbl->mode[i]) {
                    case 0:
                    case 1:
                        if (tbl->target[i] != 0) {
                            switch (e->kind) {
                            case 1:
                                cur = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, tbl->target[i]);
                                tokusei[2] = 0x34;
                                num = 3;
                                break;
                            case 2:
                                cur = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, tbl->target[i]);
                                num = 2;
                                break;
                            case 3:
                                cur = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, tbl->target[i]);
                                num = 2;
                                break;
                            case 4:
                                cur = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(t, tbl->target[i]);
                                num = 2;
                                break;
                            case 5:
                                cur = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, tbl->target[i]);
                                num = 2;
                                break;
                            case 6:
                                cur = fightTrainerAiGetFightOutPokemonAbiCntAvg(t, tbl->target[i]);
                                tokusei[2] = 0x33;
                                num = 3;
                                break;
                            case 7:
                                cur = fightTrainerAiGetFightOutPokemonAbiCntAvd(t, tbl->target[i]);
                                num = 2;
                                break;
                            }
                            if (cur - (e->limit - 1) > 0) {
                                val = 0;
                            }
                            for (m = 0; m < num; m++) {
                                if (fightAi_GetTokuseiHaveFlag(t, tbl->target[i], tokusei[m]) >= 1) {
                                    val = 0;
                                }
                            }
                        }
                        break;
                    case 2:
                        for (k = 0; k < 2; k++) {
                            if (foes[k] != 0) {
                                switch (e->kind) {
                                case 1:
                                    cur = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, foes[k]);
                                    tokusei[2] = 0x34;
                                    num = 3;
                                    break;
                                case 2:
                                    cur = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(t, foes[k]);
                                    num = 2;
                                    break;
                                case 3:
                                    cur = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, foes[k]);
                                    num = 2;
                                    break;
                                case 4:
                                    cur = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(t, foes[k]);
                                    num = 2;
                                    break;
                                case 5:
                                    cur = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(t, foes[k]);
                                    num = 2;
                                    break;
                                case 6:
                                    cur = fightTrainerAiGetFightOutPokemonAbiCntAvg(t, foes[k]);
                                    tokusei[2] = 0x33;
                                    num = 3;
                                    break;
                                case 7:
                                    cur = fightTrainerAiGetFightOutPokemonAbiCntAvd(t, foes[k]);
                                    num = 2;
                                    break;
                                }
                                if (cur - (e->limit - 1) > 0) {
                                    val = 0;
                                }
                                for (m = 0; m < num; m++) {
                                    if (fightAi_GetTokuseiHaveFlag(t, tbl->target[i], tokusei[m]) >= 1) {
                                        val = 0;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    *pval = val;
}

static void _GetAllWazaTableValue_JoutaiChangeWazaSub(FIGHT_TRAINER* t, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* tbl, s16* pval, u8 state) {
    u8 i;
    u16 wazaList[22];
    u8 j;
    u16 tokusei[2];
    u8 k;
    s16 val = *pval;
    u8 numWaza;
    u8 m;
    u8 n;
    u8 cnt;
    u8 numTokusei;

    switch (state) {
    case 8:
        numWaza = 6;
        for (n = 0; n < 6; n++) {
            wazaList[n] = NemuraseWazaTbl[n];
        }
        tokusei[0] = 0xF;
        tokusei[1] = 0x48;
        numTokusei = 2;
        break;
    case 5:
        numWaza = 3;
        for (n = 0; n < 3; n++) {
            wazaList[n] = MahiWazaTbl[n];
        }
        tokusei[0] = 7;
        numTokusei = 1;
        break;
    case 9:
        numWaza = 5;
        for (n = 0; n < 5; n++) {
            wazaList[n] = KonranWazaTbl[n];
        }
        tokusei[0] = 0x14;
        numTokusei = 1;
        break;
    case 3:
        numWaza = 3;
        for (n = 0; n < 3; n++) {
            wazaList[n] = DokuWazaTbl[n];
        }
        tokusei[0] = 0x11;
        numTokusei = 1;
        break;
    case 6:
        numWaza = 1;
        for (n = 0; n < 1; n++) {
            wazaList[n] = YakedoWazaTbl[n];
        }
        tokusei[0] = 0x29;
        numTokusei = 1;
        break;
    }
    for (i = 0; i < 2; i++) {
        if (tbl->poke[i] != 0) {
            for (j = 0; j < numWaza; j++) {
                if (tbl->waza[i] == wazaList[j]) {
                    switch (tbl->mode[i]) {
                    case 0:
                    case 1:
                        if (tbl->target[i] != 0) {
                            if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, tbl->target[i], state) == 1) {
                                val = 0;
                            }
                            for (m = 0; m < numTokusei; m++) {
                                if (fightAi_GetTokuseiHaveFlag(t, tbl->target[i], tokusei[m]) >= 1) {
                                    val = 0;
                                }
                            }
                        }
                        break;
                    case 2:
                        cnt = 0;
                        for (k = 0; k < 2; k++) {
                            if (foes[k] != 0) {
                                if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, foes[k], state) == 1) {
                                    cnt++;
                                    break;
                                }
                                for (m = 0; m < numTokusei; m++) {
                                    if (fightAi_GetTokuseiHaveFlag(t, foes[i], tokusei[m]) >= 1) {
                                        cnt++;
                                        break;
                                    }
                                }
                            }
                        }
                        if (cnt >= 2) {
                            val = 0;
                        } else if (cnt == 1) {
                            val *= 0.5;
                        }
                        break;
                    }
                }
            }
        }
    }
    *pval = val;
}

static void _GetAllWazaTableValue_JoutaiChangeWaza(FIGHT_TRAINER* t, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* tbl, s16* pval) {
    _GetAllWazaTableValue_JoutaiChangeWazaSub(t, foes, tbl, pval, 8);
    _GetAllWazaTableValue_JoutaiChangeWazaSub(t, foes, tbl, pval, 5);
    _GetAllWazaTableValue_JoutaiChangeWazaSub(t, foes, tbl, pval, 9);
    _GetAllWazaTableValue_JoutaiChangeWazaSub(t, foes, tbl, pval, 3);
    _GetAllWazaTableValue_JoutaiChangeWazaSub(t, foes, tbl, pval, 6);
}

static void _GetAllWazaTableValue_IryokuWaza(FIGHT_TRAINER* t, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* tbl, s16* pval) {
    u8 i;
    u8 k;
    u8 hits;
    s16 val = *pval;

    for (i = 0; i < 2; i++) {
        if (tbl->poke[i] != 0) {
            if ((u16)wazaIsWazaTypeId(tbl->waza[i], 1) == 1) {
                switch (tbl->mode[i]) {
                case 0:
                case 1:
                    if (tbl->target[i] != 0 && (u16)fightAi_HitCheckWazaAboutJoutaiAndType(t, tbl->poke[i], tbl->waza[i]) == 0) {
                        val = 0;
                    }
                    break;
                case 2:
                    hits = 0;
                    for (k = 0; k < 2; k++) {
                        if (foes[k] != 0 && (u16)fightAi_HitCheckWazaAboutJoutaiAndType(t, tbl->poke[i], tbl->waza[i]) == 0) {
                            hits = 1;
                            break;
                        }
                    }
                    if (hits >= 2) {
                        val = 0;
                    } else if (hits == 1) {
                        val *= 0.5;
                    }
                    break;
                }
            }
        }
    }
    *pval = val;
}

extern "C" {
s16 fightAiCombo_GetAllWazaValueTable(AI_ALLWAZA_VALID_TBL* tbl, s16 base, FIGHT_TRAINER* t, FightOutPokemon** unused, FightOutPokemon** foes, s8 mode) {
    return fightAiCombo_GetAllWazaTableDefValue(t, foes, tbl, base, mode);
}

s16 fightAiCombo_GetAllWazaMaxValueTable(AI_ALLWAZA_VALID_TBL* tbls, u8 num, s16 base, FIGHT_TRAINER* t, FightOutPokemon** ary, FightOutPokemon** foes, AI_ALLWAZA_VALID_TBL* out, s8 mode) {
    u8 best[40];
    s16 values[80];
    s16 maxVal = 0;
    u8 i;
    u8 bestNum = 0;

    for (i = 0; i < num; i++) {
        if (tbls != 0) {
            AI_ALLWAZA_VALID_TBL* e = &tbls[i];
            if (((e->poke[0] == ary[0] || e->poke[0] == ary[1]) && e->poke[1] == ary[0]) || e->poke[1] == ary[1]) {
                values[i] = fightAiCombo_GetAllWazaTableDefValue(t, foes, e, base, (u16)mode);
                if (maxVal < values[i]) {
                    best[0] = i;
                    maxVal = values[i];
                    bestNum = 1;
                } else if (maxVal == values[i] && maxVal > 0) {
                    best[bestNum] = i;
                    bestNum++;
                }
            }
            {
                u16 r = HSD_Rand();
                fightAi_CopyAllWazaValidTable(out, &tbls[best[r % bestNum]]);
            }
        }
    }
    return maxVal;
}

s32 fightAiCombo_Act(FIGHT_TRAINER* t, FightOutPokemon** foes, s32 p3) {
    FightOutPokemon* ary[8];
    AI_ALLWAZA_VALID_TBL valid;
    u16 cnt;
    u8 i;

    if (t == 0) {
        return 0;
    }
    cnt = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    for (i = 0; i < 4; i++) {
        DeckTrainer* deck = getDeckTrainerObj__11DeckTrainerFUl(fightTrainer_GetFightTrainerDataId(t));
        ComboData* combo = &comboid[getComboID__11DeckTrainerCFUc(deck, i)];
        u8 (*func)(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, s32, u8) = combo->func;
        u8 active = getComboActive__11DeckTrainerCFUc(deck, i);
        if (active != 0 && func != 0 && func(t, ary, cnt, foes, (u8)p3, 0, active) == 1) {
            fightAi_CreateAction_FromAllWazaValid(t, &valid);
            return 1;
        }
    }
    return 0;
}

s32 fightAiCombo_ActContinue(FIGHT_TRAINER* t, FightOutPokemon* poke) {
    FightOutPokemon* ary[8];
    u16 cnt = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ary, 0, 1);
    u8 id = getComboFuncId__15FightOutPokemonFv(poke);
    u8 (*func)(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16) = comboid[id].continueFunc;
    if (id == 0) {
        return 0;
    }
    if (func == 0) {
        setComboFuncId__15FightOutPokemonFUc(poke, 0);
        return 0;
    }
    if (func(t, poke, ary, cnt) == 0) {
        setComboFuncId__15FightOutPokemonFUc(poke, 0);
        return 0;
    }
    return 1;
}
}
