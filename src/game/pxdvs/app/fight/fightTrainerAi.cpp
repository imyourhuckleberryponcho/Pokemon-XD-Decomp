// This unit needs extra_cflags=["-O4,s"].
#include <dolphin/types.h>
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct FIGHT_FLOOR;
struct FightTrainer;
struct Hero;
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
s8 pokemonDB_GetTokuseiDataId(u16, u8);
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
void fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon*, u32, u32, u32, void*, u16, s32, u8, u32);
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
    u8 l;
    u8 pad2;
    u16 m;
    u8 pad3[2];
};
static AllWazaValid ai_allwaza_valid_tbl[0x40];
static s8 ai_allwaza_valid_work;
extern "C" void fightAi_InitAllWazaValidSub(AllWazaValid*);
static u8 _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza(u16);


struct ComboIdData {
    u8 kind;
    u8 flag;
    u8 pad[10];
};
class DeckTrainer {
public:
    static DeckTrainer* getDeckTrainerObj(u32 id);
    u8 getComboID(u8 index) const;
};
extern "C" {
extern ComboIdData comboid[];
u8 fightFloor_GetFightTypeFightoutPokemonNum(void* floor);
u8 pokemon_GetComboPartner(Pokemon* poke, u8 idx, u8 kind);

// ---- draft declarations ----
struct FIGHT_FLOOR {
    u8 _draft[1];
};
struct FightTrainer {
    u8 _draft[1];
};
struct Hero {
    u8 _draft[1];
};

extern "C" {
s32 fightAi_AttackResult(FIGHT_TRAINER* t, FightOutPokemon* def, u16 waza1, u16 waza2, u16 damage);
u32 fightAi_CreateAllWazaValid_GetDefense(u16 waza, s32 value);
u8 fightAi_GetWazaCombValue(u32 *p0, u16 *p1, u8 *p2);
void fightAi_InitAllWazaValid();
u8 fightAi_WazaSuccessProbability(FIGHT_TRAINER* t, FightOutPokemon* self, FightOutPokemon** ary, u16 waza);
s16 fightFloorGetFightPokemonEntryCntInc(FIGHT_FLOOR* floor);
void fightPokemonCreate(FightTrainer* trainer, FightPokemon* fp, Pokemon* p, s16 entry);
u8 fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(u16 id);
u8 fightTrainerAiDB_GetPokemonDataOrderOutFlag(u16 id);
u8 fightTrainerAiDB_GetPokemonSelectRandomFlag(u16 id);
void fightTrainerAiSortFirstSelectPokemonAry(s32 p0, s32 p1, s32 p2, u16 p3, u16 p4);
u8 fightTrainerAi_SelComboPartner(Pokemon** party, Pokemon** out, u8 num, FIGHT_TRAINER* t);
void* fightTrainer_GetFightPokemonPtr(u8* t, u16 i);
u32 heroGetStatus(Hero* hero, u32 selector, u16 index);
void* memcpy(void* dst, const void* src, size_t n);
bool pokemonCheckFightOut(Pokemon* pokemon);
bool pokemonCheckValid(Pokemon* pokemon);
void* wazaDB_GetFightTrainerAiWazaHitFuncPtr(u16 id);
extern s32 jtbl_3691;
extern s32 jtbl_3692;
extern s32 jtbl_3693;
}
extern "C++" {
static u16 _fightTrainerAiSortFirstSelectPokemonArySubSelect(FIGHT_TRAINER* p0, Hero* p1, Pokemon** p2, unsigned short p3, unsigned char p4, Pokemon** p5);
}

u8 fightTrainerAi_SelComboPartner(Pokemon** party, Pokemon** out, u8 num, FIGHT_TRAINER* t) {
    volatile s32 x;
    bool order[4] = {0, 1, 2, 3};
    u8 second[8];
    u8 first[8];
    u8 list[16];
    DeckTrainer* deck = DeckTrainer::getDeckTrainerObj(fightTrainer_GetFightTrainerDataId(t));
    u8 max = fightFloor_GetFightTypeFightoutPokemonNum(0);
    u8 i;
    u8 n;
    for (i = 0; i < 20; i++) {
        u16 a = HSD_Rand();
        u16 b = HSD_Rand();
        order[a % 4] = order[b % 4];
        order[b % 4] = order[a % 4];
    }
    n = 0;
    for (i = 0; i < 4; i++) {
        u8 id = deck->getComboID(order[i]);
        if (id != 0) {
            ComboIdData* c = &comboid[id];
            u8 flag = c->flag;
            if (c->kind == 2) {
                u8 nFirst;
                u8 nSecond;
                u8 j;
                if (max == 1) {
                    continue;
                }
                nFirst = 0;
                for (j = 0; j < num; j++) {
                    if (pokemon_GetComboPartner(party[j], order[i], 1) != 0) {
                        first[nFirst++] = j;
                    }
                }
                for (j = 0, nSecond = 0; j < num; j++) {
                    u8 has = pokemon_GetComboPartner(party[j], order[i], 0) != 0;
                    if (flag == 0) {
                        if (has) {
                            second[nSecond] = j;
                            nSecond++;
                        }
                    } else if (has == 1) {
                    } else {
                        second[nSecond] = j;
                        nSecond++;
                    }
                }
                if (nFirst != 0 && nSecond != 0) {
                    u8 tries = 0;
                    s32 y;
                    do {
                        x = (u16)HSD_Rand() % nFirst;
                        y = (u16)HSD_Rand() % nSecond;
                        tries++;
                    } while (tries <= 100 && first[x] == second[y]);
                    out[n] = party[first[x]];
                    out[n + 1] = party[second[y]];
                    return n + 2;
                }
            }
            if (c->kind == 1) {
                u8 count = 0;
                u8 j;
                for (j = 0; j < num; j++) {
                    if (pokemon_GetComboPartner(party[j], order[i], 1) != 0) {
                        list[count++] = j;
                    }
                }
                for (j = 0; j < num; j++) {
                    if (pokemon_GetComboPartner(party[j], order[i], 0) != 0) {
                        list[count++] = j;
                    }
                }
                if (count != 0) {
                    out[n++] = party[list[(u8)(HSD_Rand() % count)]];
                    if (n >= max) {
                        return n;
                    }
                }
            }
        }
    }
    return n;
}
}
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
    fightOutPokemonCreateFightActionAttackWaza(self, 0, 0x13, 0, fight_action_data_waza, (u16)waza, side, index, 0);
    return 1;
}

extern "C" {
u32 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER* t, FightOutPokemon* a);
void fightAi_AllWazaValid_DelListFromSpeed(FIGHT_TRAINER* t, AllWazaValid* list, u8* count, u16 waza, u8 faster) {
    AllWazaValid* e;
    s32 speed[3];
    s32 eff[2];
    u32 cnt[2];
    s8 i;
    s8 k;
    s8 m;
    for (i = 0; i < *count; i++) {
        s32 j;
        u8 del = 0;
        e = &list[i];
        for (j = 0; j < 2; j++) {
            speed[j] = pokemon_GetNimbleness((Pokemon*)fightOutPokemonGetPokemonPtr((FightOutPokemon*)e->a[j]));
            cnt[j] = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, (FightOutPokemon*)e->a[j]);
            if (cnt[j] != 6) {
                eff[j] = fightAbicntDoKakeWaru(cnt[j], speed[j]);
            } else {
                eff[j] = speed[j];
            }
        }
        if (faster == 1) {
            if (waza == e->c[0] && eff[0] < eff[1]) {
                del = 1;
            } else if (waza == e->c[1] && eff[0] > eff[1]) {
                del = 1;
            }
        } else if (waza == e->c[0] && eff[0] > eff[1]) {
            del = 1;
        } else if (waza == e->c[1] && eff[0] < eff[1]) {
            del = 1;
        }
        if (del == 1) {
            fightAi_InitAllWazaValidSub(e);
            i--;
            (*count)--;
            for (k = 0; k < *count; k++) {
                list[k] = list[k + 1];
                fightAi_CopyAllWazaValidTable(&list[k], &list[k + 1]);
            }
        }
    }
    for (m = *count; m < 0x40; m++) {
        fightAi_InitAllWazaValidSub(&list[m]);
    }
}
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
    u8 i;
    s16 best;
    s16 value;
    u8 candidates[8];
    u8 num;
    u8 type = fightFloor_GetFightType(0);
    if (wazaDB_GetRangeId(waza) != 0) {
        return (FightOutPokemon*)fightSeqSelectDefensePokemonPtr(self, waza, type, 0, 1, 1, -1);
    }
    best = -0xff;
    for (i = 0; i < count; i++) {
        value = fightAi_ThreatEnemyValue(t, self, cand[i], (u16)mode, 0, -1, -1);
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

extern "C" {
u8 fightFloor_GetFightTypeTrainerNum(void* floor);
u8 fightFloor_GetFightTypeEntryPokemonNum(void* floor);
u8 pokemon_GetLevel(Pokemon* poke);
u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER* t, FightOutPokemon* a);
s32 fightTrainerAiWazaDoWazaHitFunc(void*, u32, u32, u32);
u8 fightTrainerAiIsWazaTypeId(FIGHT_TRAINER* t, u16 waza, u8 type);
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*, u8);
u32 fightSideGetHikaeFightPokemonNum(void* side, u16 trainerNum, u16 a, u16 b);
s32 fightAi_GetEnemyWazaAndFlag(FIGHT_TRAINER* t, FightPokemon* p, u16* out, u8 idx);
s32 fightTrainerAiAddValueByAddsubDataId(s32 value, FIGHT_TRAINER* t, u16 id);
s16 fightAi_ThreatEnemyValue(FIGHT_TRAINER* t, FightOutPokemon* atk, FightOutPokemon* def, s8 tenkou, u32 unused,
                             s32 hitFlag, s32 killFlag) {
    s8 hit = hitFlag;
    s16 value = 0;
    s16 tenki = tenkou;
    s8 kill = killFlag;
    u8 maxLv = 0;
    u8 trainerNum = fightFloor_GetFightTypeTrainerNum(0);
    u8 entryNum = fightFloor_GetFightTypeEntryPokemonNum(0);
    u8 outNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    FightPokemon* atkFp;
    FightPokemon* defFp;
    Pokemon* atkBuff;
    Pokemon* defBuff;
    FIGHT_TRAINER* defTrainer;
    u8 defLv;
    FightOutPokemon* allies[8];
    volatile u16 atkSpeed;
    u16 defSpeed;
    u16 allyNum;
    u16 hp;
    u16 waza;
    u8 i;
    FightOutPokemon* enemies[8];
    void* side;
    FightPokemon* allyFp[25];
    FightPokemon* enemyFp[24];
    if (atk == 0) {
        return 0;
    }
    if (def == 0) {
        return 0;
    }
    atkFp = fightOutPokemon_GetFightPokemonPtr(atk);
    defFp = fightOutPokemon_GetFightPokemonPtr(def);
    atkBuff = (Pokemon*)fightPokemon_GetPokemonBuffPtr(atkFp);
    defBuff = (Pokemon*)fightPokemon_GetPokemonBuffPtr(defFp);
    fightFloorGetFightPokemonPtrToFightTrainerPtr(0, atkFp);
    defTrainer = (FIGHT_TRAINER*)fightFloorGetFightPokemonPtrToFightTrainerPtr(0, defFp);
    defLv = pokemon_GetLevel(defBuff);
    side = fightTargetGetPtrAsNowFightType(2, (FightOutPokemon*)t);
    atkSpeed = pokemon_GetNimbleness(atkBuff);
    defSpeed = pokemon_GetNimbleness(defBuff);
    allyNum = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, allies, 1, 1);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, enemies, 0, 1);
    fightFloorGetFightTrainerFightPokemonPtrAry(0, t, allyFp, 1, 1);
    fightFloorGetFightTrainerFightPokemonPtrAry(0, t, enemyFp, 0, 1);
    hp = fightTrainerAiGetFightOutPokemonNowHp(t, def);
    for (i = 0; i < 4; i++) {
        waza = pokemon_GetPokemonWazaDataId(atkBuff, i);
        if (waza != 0x176 && waza != 0 && waza != 0x163) {
            u32 res = fightTrainerAiWazaDoWazaHitFunc(t, (u32)atk, (u32)def, waza);
            if (res == 1 && hit == -1) {
                hit = 1;
            }
            if (fightTrainerAiIsWazaTypeId(t, waza, 1) != 0) {
                fightTrainerAiWazaDoWazaDamageFunc(t, atk, waza, def, 1);
                if ((s32)hp < fightTrainerAiWazaDoWazaDamageFunc(t, atk, waza, def, 0) && res == 1 && kill == -1) {
                    kill = 1;
                }
            }
        }
    }
    if (tenki == -1) {
        tenki = fightFloorGetNowTenkouDataId(0, 0);
    }
    for (i = 0; i < allyNum; i++) {
        if (maxLv < pokemon_GetLevel((Pokemon*)fightOutPokemonGetPokemonPtr(allies[i]))) {
            maxLv = pokemon_GetLevel((Pokemon*)fightOutPokemonGetPokemonPtr(allies[i]));
        }
    }
    fightSideGetHikaeFightPokemonNum(side, trainerNum, entryNum, outNum);
    for (i = 0; i < 8; i++) {
        u8 flag = fightAi_GetEnemyWazaAndFlag(t, defFp, &waza, i);
        if (waza != 0 && fightAi_AppointWazaKoukaFlag(atk, def, fightAi_GetWazaZokuseiData_ThinkWeatherBall(waza, tenki)) == 0x41) {
            if (flag == 2) {
                value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x288);
            }
            if (flag == 1) {
                value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x289);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        waza = pokemon_GetPokemonWazaDataId(atkBuff, (u8)i);
        if (waza != 0 && fightAi_AppointWazaKoukaFlag(atk, def, fightAi_GetWazaZokuseiData_ThinkWeatherBall(waza, tenki)) == 0x41) {
            value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x28A);
        }
    }
    value += (s16)((defLv - maxLv) * fightTrainerAiValueAddsubDB_GetValue(0x28B));
    for (i = 3; i < 12; i++) {
        fightAi_GetEnemyWazaAndFlag(t, defFp, &waza, i);
        if (waza == 0x78 || waza == 0x99) {
            value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x28C);
        }
        if (waza == 0x59) {
            value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x28E);
        }
    }
    for (i = 0; i < 12; i++) {
        u8 flag = fightAi_GetEnemyWazaAndFlag(t, defFp, &waza, i);
        if (fightAi_DamageKizetsuFlag(allies, fightTrainerAiWazaDoWazaDamageFunc(t, def, waza, atk, 0)) == 1) {
            if (flag == 2) {
                value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x28F);
            }
            if (flag == 1) {
                value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x290);
            }
        }
    }
    if (atkSpeed < defSpeed) {
        value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x291);
    }
    {
        s32 add = (fightTrainerAiGetFightOutPokemonAllAbiCnt(defTrainer, def) - 0x2A) * fightTrainerAiValueAddsubDB_GetValue(0x292);
        if (add > 0) {
            value += add;
        }
    }
    if (fightAi_PokemonTokuseiMoukaFlag(def) == 2) {
        value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x293);
    }
    if (fightAi_PokemonTokuseiMoukaFlag(def) == 1) {
        value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x294);
    }
    if (hit == 0) {
        value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x295);
    }
    if (kill == 1) {
        value = fightTrainerAiAddValueByAddsubDataId(value, t, 0x296);
    }
    return value;
}
}

extern "C" {
u8 fightAi_HitCheckWazaAboutJoutaiAndType(FIGHT_TRAINER* t, FightOutPokemon* atk, FightOutPokemon* def, u16 waza) {
    FightPokemon* atkFp;
    FightPokemon* defFp;
    u16 defType1;
    u16 defType2;
    u16 zokusei;
    u8 ai;
    FightOutPokemon* ally[8];
    if (t == 0) {
        return 0;
    }
    if (atk == 0) {
        return 0;
    }
    if (def == 0) {
        return 0;
    }
    if (waza == 0) {
        return 0;
    }
    atkFp = fightOutPokemon_GetFightPokemonPtr(atk);
    defFp = fightOutPokemon_GetFightPokemonPtr(def);
    fightPokemon_GetPokemonBuffPtr(atkFp);
    fightPokemon_GetPokemonBuffPtr(defFp);
    defType1 = fightOutPokemonGetZokuseiDataId(def, 0);
    defType2 = fightOutPokemonGetZokuseiDataId(def, 1);
    zokusei = fightTrainerAiGetWazaZokuseiDataId(t, waza, atk);
    ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ally, 1, 1);
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(ai) == 1 && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, def, 0x1D) == 0 &&
        waza != 0xC3 && fightAi_LateDefPokeThanAllyPoke(ally, def) != 1) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, def, 0x1F) == 1 &&
            (waza != 0x57 || waza != 0x147 || waza != 0x10 || waza != 0xEF)) {
            return 0;
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, def, 0x20) == 1) {
            if (waza != 0x59 || waza != 0xDE) {
                return 0;
            }
            if (_fightTrainerAiGetFightPokemonTokuseiDataId(t, defFp) == 0x1A) {
                return 0;
            }
            if (defType1 == 2 || defType2 == 2) {
                return 0;
            }
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, def, 0x21) == 1 && (waza != 0xFA || waza != 0x39)) {
            return 0;
        }
    }
    if (fightTrainerAiDB_GetZokuseiCheckFlag(ai) == 1 &&
        (zokuseiGetWazaJoutai(zokusei, defType1) == 0x43 || zokuseiGetWazaJoutai(zokusei, defType2) == 0x43)) {
        return 0;
    }
    return 1;
}

extern "C" {
void fightAi_AllWazaValid_DelComboList(FIGHT_TRAINER* t, AllWazaValid* list, u8* count, u8 kind0, s32 value0, s8 kind1,
                                       s32 value1, u8 keep) {
    u8 a;
    u8 b;
    AllWazaValid tmp[0x40];
    u8 kind[2];
    s32 value[2];
    u8 n;
    AllWazaValid* e;
    AllWazaValid* pk;
    u8 i;
    u8 j;
    kind[0] = kind0;
    kind[1] = kind1;
    n = 0;
    value[0] = value0;
    value[1] = value1;
    for (i = 0; i < *count; i++) {
        a = 0;
        b = 0;
        fightAi_InitAllWazaValidSub(&tmp[i]);
        pk = &ai_allwaza_valid_tbl[i];
        e = &list[i];
        for (j = 0; j < 2; j++) {
            switch (kind[j]) {
            case 0:
                a++;
                b++;
                break;
            case 1: {
                s32 v = value[j];
                if (v != 0) {
                    if (e->c[0] == v) {
                        if (j == 0) {
                            a++;
                        }
                        if (j == 1) {
                            b++;
                        }
                    }
                    if (e->c[1] == v) {
                        if (j == 0) {
                            b++;
                        }
                        if (j == 1) {
                            a++;
                        }
                    }
                }
                break;
            }
            case 2: {
                s32 v = value[j];
                if (v != 0) {
                    if (wazaIsWazaTypeId(e->c[0], v) == 1) {
                        if (j == 0) {
                            a++;
                        }
                        if (j == 1) {
                            b++;
                        }
                    }
                    if (wazaIsWazaTypeId(e->c[1], v) == 1) {
                        if (j == 0) {
                            b++;
                        }
                        if (j == 1) {
                            a++;
                        }
                    }
                }
                break;
            }
            case 3:
                if (value[j] != -1) {
                    s32 v = value[j];
                    if (v == fightTrainerAiGetWazaZokuseiDataId(t, e->c[0], (FightOutPokemon*)pk->a[0])) {
                        if (j == 0) {
                            a++;
                        }
                        if (j == 1) {
                            b++;
                        }
                    }
                    if (v == fightTrainerAiGetWazaZokuseiDataId(t, e->c[1], (FightOutPokemon*)pk->a[1])) {
                        if (j == 0) {
                            b++;
                        }
                        if (j == 1) {
                            a++;
                        }
                    }
                }
                break;
            }
        }
        if (a == 2 || b == 2) {
            if (keep == 1) {
                fightAi_CopyAllWazaValidTable(&tmp[n], e);
                n++;
            }
        } else if (keep == 0) {
            fightAi_CopyAllWazaValidTable(&tmp[n], e);
            n++;
        }
    }
    *count = n;
    for (i = 0; i < 0x40; i++) {
        fightAi_CopyAllWazaValidTable(&list[i], &tmp[i]);
    }
}

void fightAi_AllWazaValid_AddComboList(FIGHT_TRAINER* t, AllWazaValid* list, u8* count, u8 kind0, s32 value0, s8 kind1,
                                       s32 value1) {
    u8 a;
    u8 b;
    AllWazaValid* e;
    u8 kind[2];
    s32 value[6];
    u8 i;
    u8 n;
    kind[0] = kind0;
    kind[1] = kind1;
    i = 0;
    value[0] = value0;
    value[1] = value1;
    n = *count;
    for (; i < 0x40; i++) {
        a = 0;
        u8 j = 0;
        b = 0;
        e = &ai_allwaza_valid_tbl[i];
        for (; j < 2; j++) {
            switch (kind[j]) {
            case 0:
                a++;
                b++;
                break;
            case 1: {
                s32 v = value[j];
                if (v != 0) {
                    if (e->c[0] == v) {
                        if (j == 0) {
                            a++;
                        }
                        if (j == 1) {
                            b++;
                        }
                    }
                    if (e->c[1] == v) {
                        if (j == 0) {
                            b++;
                        }
                        if (j == 1) {
                            a++;
                        }
                    }
                }
                break;
            }
            case 2: {
                s32 v = value[j];
                if (v != 0) {
                    if (wazaIsWazaTypeId(e->c[0], v) == 1) {
                        if (j == 0) {
                            a++;
                        }
                        if (j == 1) {
                            b++;
                        }
                    }
                    if (wazaIsWazaTypeId(e->c[1], v) == 1) {
                        if (j == 0) {
                            b++;
                        }
                        if (j == 1) {
                            a++;
                        }
                    }
                }
                break;
            }
            case 3:
                if (value[j] != -1) {
                    s32 v = value[j];
                    if (v == fightTrainerAiGetWazaZokuseiDataId(t, e->c[0], (FightOutPokemon*)e->a[0])) {
                        if (j == 0) {
                            a++;
                        }
                        if (j == 1) {
                            b++;
                        }
                    }
                    if (v == fightTrainerAiGetWazaZokuseiDataId(t, e->c[1], (FightOutPokemon*)e->a[1])) {
                        if (j == 0) {
                            b++;
                        }
                        if (j == 1) {
                            a++;
                        }
                    }
                }
                break;
            }
        }
        if (a == 2 || b == 2) {
            fightAi_CopyAllWazaValidTable(&list[n], e);
            n++;
        }
    }
    *count = n;
}
}
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
            void* defender = fightSeqSelectDefensePokemonPtr(self, waza, (u8)type, fightTrainerAiWazaSelectDefensePokemon, 1, 0, -1);
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
extern "C" {
void fightAi_CreateAllWazaValid(FIGHT_TRAINER* p0, FightOutPokemon** p1, u8 p2) {
    u8 sp10[22];
    s32 sp50;
    s32 spD;
    s32 *spA0;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    s32 sp74;
    s32 sp64;
    s32 sp54;
    FightOutPokemon *sp4C;
    FightOutPokemon *sp48;
    FightOutPokemon *sp44;
    s16 sp3C;
    s16 sp34;
    u16 sp2C;
    u16 sp24;
    s32 sp1C;
    u16 sp1A;
    u16 sp18;
    u16 sp16;
    u16 sp14;
    u16 sp12;
    u8 spC;
    u8 sp9;
    u8 sp8;
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_2;
    FightOutPokemon *temp_r6_2;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r18;
    s32 temp_r19;
    s32 temp_r21;
    s32 temp_r24;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r3;
    s32 temp_r4_3;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r7;
    s32 temp_r8;
    s32 temp_r8_2;
    u16 temp_r20_2;
    u16 temp_r3_2;
    u16 temp_r3_4;
    u16 temp_r6;
    u8 (*temp_r14)(s32, FightOutPokemon *, u16);
    u8 (*temp_r18_2)(s32, FightOutPokemon *, u16);
    u8 (*temp_r3_3)(s32, FightOutPokemon *, u16);
    u8 (*temp_r3_5)(s32, FightOutPokemon *, u16);
    u8 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r14_2;
    u8 temp_r20;
    u8 temp_r22;
    u8 temp_r3_6;
    u8 var_r14;
    u8 var_r17;
    u8 var_r17_2;
    u8 var_r18;
    u8 var_r19;
    u8 var_r20;
    u8 var_r21;
    u8 var_r22;
    u8 var_r24;
    u8 var_r25;
    u8 var_r28;
    u8 var_r29;
    u8 var_r30;
    u32 var_r3;
    u8 *temp_r12;
    u8 *temp_r22_2;
    u8 *temp_r23;
    u8 *temp_r23_2;
    u8 *temp_r25;

    if (p0 != 0) {
        fightAi_InitAllWazaValid();
        var_r3 = 0;
        while (var_r3 < 2U) {
            temp_r21 = (var_r3 * 4) & 0x3FC;
            temp_r8 = (var_r3 * 8) & 0x7F8;
            temp_r20 = var_r3;
            var_r24 = 0;
            while (var_r24 < 4U) {
                var_r25 = 0;
                while (var_r25 < 2U) {
                    temp_r0 = (var_r25 * 2) & 0x1FE;
                    temp_r22 = var_r25;
                    *(&sp74 + ((var_r3 * 0x10) & 0xFF0) + ((var_r24 * 4) & 0x3FC) + temp_r0) = 0;
                    var_r25 = var_r25 + 1;
                    *(&sp14 + temp_r21 + temp_r0) = 0;
                    (&sp8)[temp_r22] = 0;
                }
                temp_r8_2 = var_r24 * 2;
                *(&sp1C + temp_r21 + var_r24) = 0;
                var_r24 = var_r24 + 1;
                *(&sp64 + temp_r8 + temp_r8_2) = 0;
                *(&sp54 + temp_r8 + temp_r8_2) = 0;
            }
            temp_r0_2 = temp_r20 * 2;
            *(&sp4C + temp_r21) = 0;
            var_r3 = var_r3 + 1;
            (&spC)[temp_r20] = 0;
            *(&sp10[0] + temp_r0_2) = 0;
            *(&sp44 + temp_r21) = 0;
        }
        temp_r4 = M2C_FIELD(p1, FightOutPokemon **, 0);
        if (temp_r4 != NULL) {
            fightTrainerAiGetFightOutPokemonWazaDataIdAry((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (FightOutPokemon*)(temp_r4), (u16*)(&sp2C), (s16*)(&sp3C), 1U);
        }
        temp_r4_2 = M2C_FIELD(p1, FightOutPokemon **, 4);
        if (temp_r4_2 != NULL) {
            fightTrainerAiGetFightOutPokemonWazaDataIdAry((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (FightOutPokemon*)(temp_r4_2), (u16*)(&sp24), (s16*)(&sp34), 1U);
        }
        temp_r20_2 = fightFloorGetFightTrainerFightOutPokemonPtrAry((unsigned long)((FIGHT_FLOOR*)(NULL)), (FIGHT_TRAINER *)((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0)), (FightOutPokemon **)((FightOutPokemon**)(&sp4C)), (unsigned char)(0U), (unsigned char)(1U));
        var_r28 = 0;
        while (var_r28 < 2U) {
            temp_r19 = (var_r28 * 4) & 0x3FC;
            if ((u32) *(p1 + temp_r19) != 0U) {
                temp_r3 = var_r28 * 8;
                temp_r22_2 = (unsigned char *)(&sp54 + temp_r3);
                temp_r23 = (unsigned char *)(&sp64 + temp_r3);
                var_r29 = 0;
                while (var_r29 < 4U) {
                    if (var_r28 == 0) {
                        temp_r5 = (var_r29 * 2) & 0x1FE;
                        *(temp_r22_2 + temp_r5) = *(&sp2C + temp_r5);
                        *(temp_r23 + temp_r5) = *(&sp3C + temp_r5);
                    } else {
                        temp_r5_2 = (var_r29 * 2) & 0x1FE;
                        *(temp_r22_2 + temp_r5_2) = *(&sp24 + temp_r5_2);
                        *(temp_r23 + temp_r5_2) = *(&sp34 + temp_r5_2);
                    }
                    temp_r18 = (var_r29 * 2) & 0x1FE;
                    temp_r6 = *(temp_r22_2 + temp_r18);
                    if (temp_r6 != 0) {
                        (&spC)[var_r28] = fightAi_WazaSuccessProbability((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (FightOutPokemon*)(*(p1 + temp_r19)), (FightOutPokemon**)(&sp4C), temp_r6);
                        var_r30 = 0;
                        while (var_r30 < 2U) {
                            temp_r6_2 = (FightOutPokemon *)(*(&(u8*)(sp4C) + ((var_r30 * 4) & 0x3FC)));
                            if (temp_r6_2 != NULL) {
                                *(&sp74 + (var_r28 * 0x10) + (var_r29 * 4) + (var_r30 * 2)) = fightTrainerAiWazaDoWazaDamageFunc((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (FightOutPokemon*)(*(p1 + temp_r19)), *(temp_r22_2 + temp_r18), (FightOutPokemon*)(temp_r6_2), 0U);
                            }
                            var_r30 = var_r30 + 1;
                        }
                    }
                    var_r29 = var_r29 + 1;
                }
            }
            var_r28 = var_r28 + 1;
        }
        ai_allwaza_valid_work = p2;
        spA0 = (long *)(&ai_allwaza_valid_tbl);
        var_r22 = 0;
        while (var_r22 < 4U) {
            temp_r25 = (unsigned char *)(&sp74 + ((var_r22 * 4) & 0x3FC));
            temp_r24 = (var_r22 * 2) & 0x1FE;
            sp94 = (var_r22 * 0x10) & 0xFF0;
            var_r20 = 0;
loop_109:
            if (var_r20 < 2U) {
                var_r21 = 0;
                sp98 = ((var_r20 * 8) & 0x7F8) + sp94;
                while (var_r21 < 4U) {
                    temp_r23_2 = (unsigned char *)(&sp74 + ((var_r21 * 4) & 0x3FC));
                    temp_r4_3 = (var_r21 * 2) & 0x1FE;
                    var_r19 = 0;
                    sp9C = temp_r4_3 + sp98;
                    temp_r29 = temp_r4_3 + 8;
                    temp_r28 = var_r21 + 4;
                    while (var_r19 < 2U) {
                        sp16 = 0;
                        sp14 = 0;
                        sp1A = 0;
                        sp18 = 0;
                        sp10[0] = 0;
                        sp12 = 0;
                        if ((FightOutPokemon *) M2C_FIELD(p1, FightOutPokemon **, 0) != NULL) {
                            temp_r3_2 = *(&sp54 + temp_r24);
                            if (temp_r3_2 != 0) {
                                *(&sp1C + var_r22) = fightAi_CreateAllWazaValid_GetDefense(temp_r3_2, (s32) var_r20);
                                temp_r0_3 = *(&sp1C + var_r22);
                                switch ((s32) temp_r0_3) { /* switch 1; irregular */
                                case 0:             /* switch 1 */
                                    sp14 = sp14 + (M2C_FIELD(temp_r25, u16 *, 0));
                                    sp44 = sp4C;
                                    break;
                                case 1:             /* switch 1 */
                                    sp16 = sp16 + (M2C_FIELD(temp_r25, u16 *, 2));
                                    sp44 = (FightOutPokemon *)(sp50);
                                    break;
                                case 2:             /* switch 1 */
                                    sp14 = sp14 + (M2C_FIELD(temp_r25, u16 *, 0));
                                    sp16 = sp16 + (M2C_FIELD(temp_r25, u16 *, 2));
                                    sp44 = sp4C;
                                    break;
                                case 3:             /* switch 1 */
                                    sp44 = sp4C;
                                    break;
                                case 4:             /* switch 1 */
                                    sp44 = M2C_FIELD(p1, FightOutPokemon **, 0);
                                    break;
                                case 5:             /* switch 1 */
                                    sp44 = (&sp4C)[HSD_Rand() % temp_r20_2];
                                    break;
                                }
                                if ((u8) *(&sp1C + var_r22) == 2) {
                                    temp_r14 = (unsigned char (*)(long, FightOutPokemon *, unsigned short))(wazaDB_GetFightTrainerAiWazaHitFuncPtr(*(&sp54 + temp_r24)));
                                    var_r18 = 0;
                                    var_r17 = 0;
                                    if ((sp4C != NULL) && (temp_r14((long)p0, M2C_FIELD(p1, FightOutPokemon **, 0), *(&sp54 + temp_r24)) == 1) && (fightTrainerAiWazaDoWazaHitFunc((void*)((u8 *) p0), (u32) M2C_FIELD(p1, FightOutPokemon **, 0), (u32) *(&sp54 + temp_r24), (u32) sp4C) == 1)) {
                                        var_r18 = 1;
                                    }
                                    if ((sp50 != NULL) && (temp_r14((long)p0, M2C_FIELD(p1, FightOutPokemon **, 0), *(&sp54 + temp_r24)) == 1) && (fightTrainerAiWazaDoWazaHitFunc((void*)((u8 *) p0), (u32) M2C_FIELD(p1, FightOutPokemon **, 0), (u32) *(&sp54 + temp_r24), (u32) sp50) == 1)) {
                                        var_r17 = 1;
                                    }
                                    if ((var_r18 == 1) || (var_r17 == 1)) {
                                        sp10[0] = *(&sp54 + temp_r24);
                                    } else {
                                        sp10[0] = 0;
                                    }
                                } else {
                                    temp_r3_3 = (unsigned char (*)(long, FightOutPokemon *, unsigned short))(wazaDB_GetFightTrainerAiWazaHitFuncPtr(*(&sp54 + temp_r24)));
                                    if ((sp44 != NULL) && (temp_r3_3((long)p0, M2C_FIELD(p1, FightOutPokemon **, 0), *(&sp54 + temp_r24)) == 1) && (fightTrainerAiWazaDoWazaHitFunc((void*)((u8 *) p0), (u32) M2C_FIELD(p1, FightOutPokemon **, 0), (u32) *(&sp54 + temp_r24), (u32) sp44) == 1)) {
                                        sp10[0] = *(&sp54 + temp_r24);
                                    } else {
                                        sp10[0] = 0;
                                    }
                                }
                            }
                        }
                        if ((FightOutPokemon *) M2C_FIELD(p1, FightOutPokemon **, 4) != NULL) {
                            temp_r3_4 = *(&sp54 + temp_r29);
                            if (temp_r3_4 != 0) {
                                *(&sp1C + temp_r28) = fightAi_CreateAllWazaValid_GetDefense(temp_r3_4, (s32) var_r19);
                                temp_r0_4 = *(&sp1C + temp_r28);
                                switch ((s32) temp_r0_4) { /* switch 2; irregular */
                                case 0:             /* switch 2 */
                                    sp18 = sp18 + (M2C_FIELD(temp_r23_2, u16 *, 0x10));
                                    sp48 = sp4C;
                                    break;
                                case 1:             /* switch 2 */
                                    sp1A = sp1A + (M2C_FIELD(temp_r23_2, u16 *, 0x12));
                                    sp48 = (FightOutPokemon *)(sp50);
                                    break;
                                case 3:             /* switch 2 */
                                    sp48 = sp4C;
                                    break;
                                case 4:             /* switch 2 */
                                    sp48 = M2C_FIELD(p1, FightOutPokemon **, 4);
                                    break;
                                case 2:             /* switch 2 */
                                    sp18 = sp18 + (M2C_FIELD(temp_r23_2, u16 *, 0x10));
                                    sp1A = sp1A + (M2C_FIELD(temp_r23_2, u16 *, 0x12));
                                    sp48 = (FightOutPokemon *)(sp50);
                                    break;
                                case 5:             /* switch 2 */
                                    sp48 = (&sp4C)[HSD_Rand() % temp_r20_2];
                                    break;
                                }
                                if ((u8) *(&sp1C + temp_r28) == 2) {
                                    var_r14 = 0;
                                    temp_r18_2 = (unsigned char (*)(long, FightOutPokemon *, unsigned short))(wazaDB_GetFightTrainerAiWazaHitFuncPtr(*(&sp54 + temp_r29)));
                                    var_r17_2 = 0;
                                    if ((sp4C != NULL) && (temp_r18_2((long)p0, M2C_FIELD(p1, FightOutPokemon **, 4), *(&sp54 + temp_r29)) == 1) && (fightTrainerAiWazaDoWazaHitFunc((void*)((u8 *) p0), (u32) M2C_FIELD(p1, FightOutPokemon **, 4), (u32) *(&sp54 + temp_r29), (u32) sp4C) == 1)) {
                                        var_r14 = 1;
                                    }
                                    if ((sp50 != NULL) && (temp_r18_2((long)p0, M2C_FIELD(p1, FightOutPokemon **, 4), *(&sp54 + temp_r29)) == 1) && (fightTrainerAiWazaDoWazaHitFunc((void*)((u8 *) p0), (u32) M2C_FIELD(p1, FightOutPokemon **, 4), (u32) *(&sp54 + temp_r29), (u32) sp50) == 1)) {
                                        var_r17_2 = 1;
                                    }
                                    if ((var_r14 == 1) || (var_r17_2 == 1)) {
                                        sp12 = *(&sp54 + temp_r29);
                                    } else {
                                        sp12 = 0;
                                    }
                                } else {
                                    temp_r3_5 = (unsigned char (*)(long, FightOutPokemon *, unsigned short))(wazaDB_GetFightTrainerAiWazaHitFuncPtr(*(&sp54 + temp_r29)));
                                    if ((sp48 != NULL) && (temp_r3_5((long)p0, M2C_FIELD(p1, FightOutPokemon **, 4), *(&sp54 + temp_r29)) == 1) && (fightTrainerAiWazaDoWazaHitFunc((void*)((u8 *) p0), (u32) M2C_FIELD(p1, FightOutPokemon **, 4), (u32) *(&sp54 + temp_r29), (u32) sp48) == 1)) {
                                        sp12 = *(&sp54 + temp_r29);
                                    } else {
                                        sp12 = 0;
                                    }
                                }
                            }
                        }
                        temp_r14_2 = fightAi_GetWazaCombValue((u32 *) &sp4C, &sp14, &spC);
                        sp8 = fightAi_AttackResult((FIGHT_TRAINER *)(p0), (FightOutPokemon *)((u32) sp4C), (unsigned short)(sp10[0]), (unsigned short)(sp12), (unsigned short)((u16) (sp14 + sp18)));
                        temp_r3_6 = fightAi_AttackResult((FIGHT_TRAINER *)(p0), (FightOutPokemon *)((u32) sp50), (unsigned short)(sp10[0]), (unsigned short)(sp12), (unsigned short)((u16) (sp16 + sp1A)));
                        temp_r7 = (s16) (var_r19 + sp9C) * 0x2C;
                        var_r19 = var_r19 + 1;
                        temp_r12 = (unsigned char *)(spA0 + temp_r7);
                        M2C_FIELD(temp_r12, FightOutPokemon **, 0) = (FightOutPokemon *) M2C_FIELD(p1, FightOutPokemon **, 0);
                        M2C_FIELD(temp_r12, FightOutPokemon **, 4) = (FightOutPokemon *) M2C_FIELD(p1, FightOutPokemon **, 4);
                        M2C_FIELD(temp_r12, FightOutPokemon **, 8) = sp44;
                        M2C_FIELD(temp_r12, FightOutPokemon **, 0xC) = sp48;
                        M2C_FIELD(temp_r12, u16 *, 0x10) = sp10[0];
                        M2C_FIELD(temp_r12, u16 *, 0x12) = sp12;
                        M2C_FIELD(temp_r12, s8 *, 0x14) = (s8) *(&sp64 + temp_r24);
                        M2C_FIELD(temp_r12, s8 *, 0x15) = (s8) *(&sp64 + temp_r29);
                        M2C_FIELD(temp_r12, u8 *, 0x16) = (u8) *(&sp1C + var_r22);
                        M2C_FIELD(temp_r12, u8 *, 0x17) = (u8) *(&sp1C + temp_r28);
                        M2C_FIELD(temp_r12, u8 *, 0x18) = spC;
                        M2C_FIELD(temp_r12, u8 *, 0x19) = spD;
                        M2C_FIELD(temp_r12, u8 *, 0x1A) = temp_r14_2;
                        M2C_FIELD(temp_r12, u16 *, 0x1C) = sp14;
                        M2C_FIELD(temp_r12, u16 *, 0x1E) = sp16;
                        M2C_FIELD(temp_r12, u16 *, 0x20) = sp18;
                        M2C_FIELD(temp_r12, u16 *, 0x22) = sp1A;
                        M2C_FIELD(temp_r12, u8 *, 0x24) = sp8;
                        sp9 = temp_r3_6;
                        M2C_FIELD(temp_r12, u8 *, 0x25) = temp_r3_6;
                    }
                    var_r21 = var_r21 + 1;
                }
                var_r20 = var_r20 + 1;
                goto loop_109;
            }
            var_r22 = var_r22 + 1;
        }
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

extern "C" {
s32 fightAi_AttackResult(FIGHT_TRAINER* t, FightOutPokemon* def, u16 waza1, u16 waza2, u16 damage) {
    FightPokemon* defFp;
    void* buff;
    u16 defType1;
    u16 defType2;
    u16 zokusei1;
    u16 zokusei2;
    u8 ai;
    FightOutPokemon* ally[8];
    if (def == 0) {
        return 0;
    }
    defFp = fightOutPokemon_GetFightPokemonPtr(def);
    buff = fightPokemon_GetPokemonBuffPtr(defFp);
    defType1 = fightOutPokemonGetZokuseiDataId(def, 0);
    defType2 = fightOutPokemonGetZokuseiDataId(def, 1);
    zokusei1 = wazaDB_GetZokuseiDataId(waza1);
    zokusei2 = wazaDB_GetZokuseiDataId(waza2);
    ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, ally, 1, 1);
    if (fightTrainerAiDB_GetZokuseiCheckFlag(ai) == 1 &&
        (zokuseiGetWazaJoutai(zokusei1, defType1) == 0x43 || zokuseiGetWazaJoutai(zokusei1, defType2) == 0x43) &&
        (zokuseiGetWazaJoutai(zokusei2, defType1) == 0x43 || zokuseiGetWazaJoutai(zokusei2, defType2) == 0x43)) {
        return 1;
    }
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(ai) == 1 && fightTrainerAiIsFightOutPokemonJoutaiDataId(t, def, 0x1D) == 0 &&
        waza1 != 0xC3 && waza2 != 0xC3 && fightAi_LateDefPokeThanAllyPoke(ally, def) != 1) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, def, 0x1F) == 1 && waza1 != 0x57 && waza1 != 0x147 &&
            waza1 != 0x10 && waza1 != 0xEF && waza2 != 0x57 && waza2 != 0x147 && waza2 != 0x10 && waza2 != 0xEF) {
            return 2;
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, def, 0x20) == 1) {
            if (waza1 != 0x59 && waza1 != 0xDE && waza2 != 0x59 && waza2 != 0xDE) {
                return 2;
            }
            if (_fightTrainerAiGetFightPokemonTokuseiDataId(t, defFp) == 0x1A) {
                return 2;
            }
            if (defType1 == 2 || defType2 == 2) {
                return 2;
            }
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, def, 0x21) == 1 && waza1 != 0xFA && waza1 != 0x39 &&
            waza2 != 0xFA && waza2 != 0x39) {
            return 2;
        }
    }
    u16 hp = pokemon_GetHp((Pokemon*)buff);
    return hp <= damage ? 3 : 0;
}
extern "C" {
#pragma push
#pragma peephole off
u8 fightAi_GetWazaCombValue(u32 *p0, u16 *p1, u8 *p2) {
    f32 unkspA;
    s32 sp24;
    s32 sp20;
    s32 sp18;
    f32 sp14;
    f32 sp10;
    s32 spC;
    s32 sp8;
    FightOutPokemon *temp_r3;
    Pokemon *temp_r3_2;
    f32 temp_f3;
    s32 temp_r24;
    s32 temp_r31;
    u16 *temp_r25;
    u16 temp_r3_3;
    u16 temp_r3_4;
    u8 var_r29;
    u8 var_r30;

    var_r29 = 0;
    var_r30 = 0;
    spC = jtbl_3691;
    sp10 = M2C_FIELD(&jtbl_3692, f32 *, 0);
    sp14 = M2C_FIELD(&jtbl_3692, f32 *, 4);
    sp8 = jtbl_3693;
    while (var_r30 < 2U) {
        temp_r24 = (var_r30 * 4) & 0x3FC;
        temp_r3 = (FightOutPokemon *)(*(p0 + temp_r24));
        if (temp_r3 != NULL) {
            temp_r31 = var_r30 * 2;
            temp_r25 = &p1[var_r30];
            *(&spC + temp_r31) = M2C_FIELD(temp_r25, u16 *, 4) + M2C_FIELD(temp_r25, u16 *, 0);
            *(&sp18 + temp_r24) = (long)(fightOutPokemonGetPokemonPtr((FightOutPokemon*)(temp_r3)));
            temp_r3_2 = (Pokemon *)(*(&sp18 + temp_r24));
            if (temp_r3_2 != NULL) {
                temp_r3_3 = pokemon_GetHp((Pokemon*)(temp_r3_2));
                sp24 = (s32) temp_r3_3;
                sp20 = 0x43300000;
                temp_f3 = (f32) temp_r3_3;
                if (temp_f3 != 0.0f) {
                    *(&sp10 + temp_r24) = (f32) *(&spC + temp_r31) / temp_f3;
                    if (*(&sp10 + temp_r24) > 1.0f) {
                        *(&sp10 + temp_r24) = 1.0f;
                        var_r29 += 1;
                    }
                    temp_r3_4 = M2C_FIELD(temp_r25, u16 *, 0);
                    *(&sp8 + temp_r31) = 0;
                    if ((temp_r3_4 != 0) && ((u16) M2C_FIELD(temp_r25, u16 *, 4) != 0)) {
                        *(&sp8 + temp_r31) = (s16) ((s32) (M2C_FIELD(p2, u8 *, 0) + M2C_FIELD(p2, u8 *, 1)) / 2);
                    } else if (temp_r3_4 != 0) {
                        *(&sp8 + temp_r31) = (s16) M2C_FIELD(p2, u8 *, 0);
                    } else if ((u16) M2C_FIELD(temp_r25, u16 *, 4) != 0) {
                        *(&sp8 + temp_r31) = (s16) M2C_FIELD(p2, u8 *, 1);
                    }
                }
            }
        }
        var_r30 += 1;
    }
    switch (var_r29) {                              /* irregular */
    case 2:
        return (u8) ((s32) (M2C_FIELD(p2, u8 *, 0) + M2C_FIELD(p2, u8 *, 1)) / 2);
    case 1:
        return (u8) (s32) ((0.5 * (f64) sp10 * (f64) (u16) sp8) + (0.5 * (f64) sp14 * (f64) unkspA));
    default:
        return (u8) (s32) ((0.25 * (f64) sp10 * (f64) (u16) sp8) + (0.25 * (f64) sp14 * (f64) unkspA));
    }
}
#pragma pop
}


extern "C" {
u16 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER* t, u16 waza);
s8 pokemonSearchWazaDataId(Pokemon* pokemon, u16 waza);
s32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
u8 fightTrainerAiIsWazaTypeId(FIGHT_TRAINER* t, u16 waza, u8 type);
u8 fightFloorCheckHuuinWazaFightOutPokemon(void* floor, FightOutPokemon* pokemon, u16 wazaId);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon* fop);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon* fop);
u8 fightTrainerAiIsFightPokemonZokuseiDataId(FIGHT_TRAINER* t, FightPokemon* p, u16 z);
u16 fightOutPokemonNowHpWaruValue(FightOutPokemon* fop, u8 waru);
u8 fightAi_CanMoveAppointWaza(FIGHT_TRAINER* t, FightOutPokemon* p, u16 waza) {
    u8 i;
    u8 found = 0;
    FightPokemon* fp;
    void* buff;
    s8 slot;
    if (p == 0) {
        return 0;
    }
    if (t == 0) {
        return 0;
    }
    if (waza == 0) {
        return 0;
    }
    fightTrainerAiGetWazaIryoku(t, waza);
    fp = fightOutPokemon_GetFightPokemonPtr(p);
    buff = fightPokemon_GetPokemonBuffPtr(fp);
    slot = pokemonSearchWazaDataId((Pokemon*)buff, waza);
    for (i = 0; i < 4; i++) {
        if (waza == fightTrainerAiGetFightPokemonWazaDataId(t, fp, i)) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    if (pokemon_GetPokemonWazaPp((Pokemon*)buff, slot) == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 0x2A) == 1 &&
        waza != pokemon_GetPokemonWazaDataId((Pokemon*)buff, fightOutPokemonGetBuffJoutaiDataId(p, 0x2A))) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 0x29) == 1 && waza == fightOutPokemonGetBuffJoutaiDataId(p, 0x29)) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 0x30) == 1 && fightTrainerAiIsWazaTypeId(t, waza, 1) == 0) {
        return 0;
    }
    if (fightFloorCheckHuuinWazaFightOutPokemon(0, p, waza) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 0x1B) == 1 && waza == fightOutPokemon_GetMotoWazaDataId(p)) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 8) == 1 && waza != 0xD6 && waza != 0xAD) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 7) == 1 && waza != 0xAC && waza != 0xDD) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 0x36) == 1 && waza != fightOutPokemonGetBuffJoutaiDataId(p, 0x36)) {
        return 0;
    }
    if (_fightTrainerAiGetFightPokemonTokuseiDataId(t, fp) == 0x36 && fightOutPokemon_GetNamakeFlag(p) == 1) {
        return 0;
    }
    if (fightOutPokemon_GetFightoutTurnCount(p) >= 2 && waza == 0xFC) {
        return 0;
    }
    switch (waza) {
    case 0x42:
    case 0x26:
    case 0x24:
        return 1;
    case 0xAE:
        if (fightTrainerAiIsFightPokemonZokuseiDataId(t, fp, 7) == 1) {
            if (fightOutPokemonMaxHpWaruValue(p, 2) >= (int)(fightOutPokemonNowHpWaruValue(p, 1))) {
                return 1;
            }
        }
        break;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 9) == 1 || fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 0xA) == 1) {
        return 2;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, p, 5) == 1) {
        return 3;
    }
    return 4;
}
}
}
u8 fightAi_WazaSuccessProbability(FIGHT_TRAINER* t, FightOutPokemon* self, FightOutPokemon** ary, u16 waza) {
    u8 probability;
    u8 i;
    u8 faster = 0;
    u16 selfSpeed;
    u16 speeds[2];
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
    u16 current;
    Pokemon* pokemon;
    FightPokemon* fp;
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
    u32 next;
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
    u8 j;
    u8 i;
    u16 entry;
    if (a != 0 && t != 0) {
        entry = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(a));
        for (i = 0; i < 4; i++) {
            if (waza == fightTrainer_GetEnemyStoreWazaData(t, entry, i)) {
                break;
            }
            if (fightTrainer_GetEnemyStoreWazaData(t, entry, i) == 0) {
                fightTrainer_SetEnemyStoreWazaData(t, entry, i, waza);
                u8 num = fightTrainer_GetEnemyStoreWazaNum(t, entry);
                fightTrainer_SetEnemyStoreWazaNum(t, entry, num + 1);
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
        return *out <= 0x176 ? 1 : 0;
    }
    return 0;
}
u32 fightAi_GetWazaHaveFlag(FIGHT_TRAINER* t, FightPokemon* p, u16 waza) {
    u8 i;
    Pokemon* pokemon;
    u16 entry;
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

extern "C" {
void* fightTargetGetPtr(u16 slotType, void* ptr, u16 type);
u8 fightTrainerAiDB_GetStrokeValue(u16 id);
}
#define AI_STROKE_ISSUE(v, n, type, res)                                                                       \
    {                                                                                                          \
        FightOutPokemon* p_ = (FightOutPokemon*)(v).a[n];                                                      \
        u16 waza_ = (v).c[n];                                                                                  \
        res = 0;                                                                                               \
        if (p_ != 0 && waza_ != 0 && waza_ != 0x176 && waza_ != 0x163) {                                       \
            FightOutPokemon* target_;                                                                          \
            switch ((v).e[n]) {                                                                                \
            case 0:                                                                                            \
                target_ = (FightOutPokemon*)fightTargetGetPtr(0xF, p_, type);                                  \
                break;                                                                                         \
            case 1:                                                                                            \
                target_ = (FightOutPokemon*)fightTargetGetPtr(0x10, p_, type);                                 \
                break;                                                                                         \
            default:                                                                                           \
                target_ = (FightOutPokemon*)fightTargetGetPtr(0xF, p_, type);                                  \
                break;                                                                                         \
            }                                                                                                  \
            fightOutPokemonCreateFightActionAttackWaza(                                                        \
                p_, 0, 0x13, 0, fight_action_data_waza, waza_,                                                 \
                fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target_, type), (v).d[n], 0);           \
            res = 1;                                                                                           \
        }                                                                                                      \
    }
#define AI_STROKE_VALUE(e, sum)                                                                                \
    {                                                                                                          \
        u8 n_ = 0;                                                                                             \
        u8 j_;                                                                                                 \
        sum = 0;                                                                                               \
        for (j_ = 0; j_ < 2; j_++) {                                                                           \
            if ((e)->a[j_] != 0) {                                                                             \
                n_++;                                                                                          \
                sum += (e)->f[j_];                                                                             \
            }                                                                                                  \
        }                                                                                                      \
        if (n_ == (u8)ai_allwaza_valid_work) {                                                                 \
            sum = sum / ai_allwaza_valid_work;                                                                 \
        }                                                                                                      \
    }

extern "C" {
void fightAi_CheckDoFightActionStroke(FIGHT_TRAINER* t) {
    AllWazaValid* x;
    AllWazaValid* e;
    u8 j;
    bool bestValue = 0;
    u8 value;
    u8 type = fightFloor_GetFightType(0);
    bool done = 0;
    u8 stroke;
    u8 i;
    AllWazaValid best;
    void* act1;
    s32 total;
    if (t == 0) {
        return;
    }
    stroke = fightTrainerAiDB_GetStrokeValue(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t)));
    if (stroke == 0) {
        return;
    }
    fightAi_InitAllWazaValidSub(&best);
    for (i = 0; i < 0x3F; i++) {
        for (j = i + 1, x = &ai_allwaza_valid_tbl[i]; j < 0x40; j++) {
            AllWazaValid* y = &ai_allwaza_valid_tbl[j];
            if (x->g < y->g) {
                fightAi_CopyAllWazaValidTable(&best, x);
                fightAi_CopyAllWazaValidTable(x, y);
                fightAi_CopyAllWazaValidTable(y, &best);
            }
        }
    }
    fightAi_InitAllWazaValidSub(&best);
    for (i = 0; i < 0x40; i++) {
        AllWazaValid* e = &ai_allwaza_valid_tbl[i];
        void* act0;
        AI_STROKE_VALUE(e, value);
        act0 = fightOutPokemon_GetFightActionBuffPtr((FightOutPokemon*)e->a[0]);
        if (act0) {
            act1 = fightOutPokemon_GetFightActionBuffPtr((FightOutPokemon*)e->a[1]);
            if (act1 && fightActionCheckValid(act0) != 1 && fightActionCheckValid(act1) != 1 && e->k[0] == 3 && e->k[1] == 3 &&
                _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza(e->c[0]) == 0 &&
                _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza(e->c[1]) == 0) {
                total = value + stroke;
                if (total >= 100 && bestValue < total) {
                    fightAi_CopyAllWazaValidTable(&best, e);
                    bestValue = total;
                }
            }
        }
    }
    {
        u8 res;
        AI_STROKE_ISSUE(best, 0, type, res);
        if (res) {
            done = 1;
        }
        AI_STROKE_ISSUE(best, 1, type, res);
        if (res) {
            done++;
        }
    }
    if (done == 0) {
        fightAi_InitAllWazaValidSub(&best);
        for (i = 0; i < 0x40; i++) {
            e = &ai_allwaza_valid_tbl[i];
            void* act1;
            void* act0;
            u8 value;
            AI_STROKE_VALUE(e, value);
            act0 = fightOutPokemon_GetFightActionBuffPtr((FightOutPokemon*)e->a[0]);
            if (act0 && (act1 = fightOutPokemon_GetFightActionBuffPtr((FightOutPokemon*)e->a[1])) != 0 &&
                fightActionCheckValid(act0) != 1 && fightActionCheckValid(act1) != 1 && (e->k[0] == 3 || e->k[1] == 3) &&
                _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza(e->c[0]) == 0 &&
                _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza(e->c[1]) == 0 && (s32)(value + stroke) >= 100) {
                fightAi_CopyAllWazaValidTable(&best, e);
                u8 res;
                AI_STROKE_ISSUE(best, 0, type, res);
                AI_STROKE_ISSUE(best, 1, type, res);
                break;
            }
        }
    }
}
}
}
static u8 _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza(u16 waza) {
    u16 ignore[3] = {0x11d, 0x78, 0x99};
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
    bool i;
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
            s32 cmpv = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, ary[i]);
            if (cmpv != (u32)t) {
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
extern "C" {
void fightTrainerAiSortFirstSelectPokemonAry(s32 p0, s32 p1, s32 p2, u16 p3, u16 p4) {
    enum TsE { TsE0 };
    s32 sp424;
    u16 sp406;
    enum TsE sp405;
    u8 sp404;
    u8 sp403;
    u8 sp402;
    s16 sp400;
    s32 sp3FC;
    s32 sp3F8;
    s32 sp3F4;
    s32 sp3F0;
    s32 sp32C;
    s32 sp328;
    s32 sp124;
    u16 sp106;
    u8 sp105;
    u8 sp104;
    u8 sp103;
    u8 sp102;
    s16 sp100;
    s32 spFC;
    s32 spF8;
    s32 spF4;
    s32 spF0;
    s32 sp2C;
    s32 sp28;
    Pokemon *sp10;
    s32 sp8;
    DeckTrainer *temp_r18;
    FightPokemon *temp_r3;
    s32 temp_r15;
    s32 temp_r16;
    s32 temp_r19;
    s32 temp_r19_2;
    s32 temp_r20;
    s32 temp_r3_3;
    s32 temp_r3_7;
    s32 temp_r3_9;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r6_3;
    s32 temp_r7;
    u16 temp_r0;
    u16 temp_r29;
    u16 temp_r31;
    u16 temp_r3_10;
    u16 temp_r3_11;
    u16 temp_r3_4;
    u16 temp_r3_6;
    u16 temp_r3_8;
    u16 temp_r6;
    u16 temp_r6_2;
    u16 temp_ret;
    u16 var_r15;
    u16 var_r15_2;
    u16 var_r17;
    u16 var_r17_2;
    u16 var_r19;
    u16 var_r20;
    u16 var_r21;
    u16 var_r21_2;
    u16 var_r5;
    u16 var_r5_2;
    u32 temp_r11;
    u8 temp_r3_5;
    u8 temp_r4_3;
    u8 temp_r5;
    u8 var_r12;
    u8 var_r16;
    u8 var_r29;
    u8 *temp_r3_2;

    temp_r31 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId((FIGHT_TRAINER *)((u8*)((u8 *) p0))));
    var_r16 = 0;
    var_r29 = 0;
    temp_r3 = (FightPokemon *)(fightTrainer_GetFightPokemonPtr((u8*)((u8 *) p0), 0U));
    if (temp_r3 != NULL) {
        temp_r3_2 = (unsigned char *)(fightTrainer_GetFightPokemonPtr((u8*)((u8 *) p0), 1U));
        if (temp_r3_2 != NULL) {
            sp328 = M2C_FIELD(temp_r3, s32 *, 0);
            memcpy((void*)(&sp32C), (const void*)(((u8*)(temp_r3) + 4)), 0xC4U);
            sp3F0 = M2C_FIELD(temp_r3, s32 *, 0xC8);
            sp3F4 = M2C_FIELD(temp_r3, s32 *, 0xCC);
            sp3F8 = M2C_FIELD(temp_r3, s32 *, 0xD0);
            sp3FC = M2C_FIELD(temp_r3, s32 *, 0xD4);
            sp400 = M2C_FIELD(temp_r3, s16 *, 0xD8);
            sp402 = M2C_FIELD(temp_r3, u8 *, 0xDA);
            sp403 = M2C_FIELD(temp_r3, u8 *, 0xDB);
            sp404 = M2C_FIELD(temp_r3, u8 *, 0xDC);
            sp405 = (enum TsE)(M2C_FIELD(temp_r3, u8 *, 0xDD));
            sp406 = M2C_FIELD(temp_r3, u16 *, 0xDE);
            M2C_STRUCT_COPY((s32) &sp404 + 4, (s32) (((u8*)(temp_r3) + 0xDC)) + 4, 0x20);
            M2C_STRUCT_COPY((s32) &sp424 + 4, (s32) (((u8*)(temp_r3) + 0xFC)) + 4, 0x200);
            sp28 = M2C_FIELD(temp_r3_2, s32 *, 0);
            memcpy((void*)(&sp2C), (const void*)(temp_r3_2 + 4), 0xC4U);
            spF0 = M2C_FIELD(temp_r3_2, s32 *, 0xC8);
            spF4 = M2C_FIELD(temp_r3_2, s32 *, 0xCC);
            spF8 = M2C_FIELD(temp_r3_2, s32 *, 0xD0);
            spFC = M2C_FIELD(temp_r3_2, s32 *, 0xD4);
            sp100 = M2C_FIELD(temp_r3_2, s16 *, 0xD8);
            sp102 = M2C_FIELD(temp_r3_2, u8 *, 0xDA);
            sp103 = M2C_FIELD(temp_r3_2, u8 *, 0xDB);
            sp104 = M2C_FIELD(temp_r3_2, u8 *, 0xDC);
            sp105 = M2C_FIELD(temp_r3_2, u8 *, 0xDD);
            sp106 = M2C_FIELD(temp_r3_2, u16 *, 0xDE);
            M2C_STRUCT_COPY((s32) &sp104 + 4, (s32) (temp_r3_2 + 0xDC) + 4, 0x20);
            M2C_STRUCT_COPY((s32) &sp124 + 4, (s32) (temp_r3_2 + 0xFC) + 4, 0x200);
            var_r5 = 0;
            while (var_r5 < p3) {
                temp_r3_3 = (var_r5 * 4) & 0x3FFFC;
                var_r5 += 1;
                *((u8 *)p2 + temp_r3_3) = 0;
            }
            var_r5_2 = 0;
            var_r21 = 0;
            while (var_r5_2 < 6U) {
                temp_r0 = var_r5_2;
                var_r5_2 += 1;
                *(&sp8 + temp_r0) = 0;
            }
            var_r15 = 1;
            if ((s16)fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(temp_r31) != 1) {
                var_r15 = p4;
            }
            temp_ret = fightTrainer_GetFightTrainerDataId((FIGHT_TRAINER *)((u8*)((u8 *) p0)));
            var_r17 = 0;
            temp_r18 = ((DeckTrainer*)((DeckTrainer *) temp_ret))->getDeckTrainerObj((u32) (u64) temp_ret);
loop_14:
            if (var_r17 < 4U) {
                if (((DeckTrainer*)(temp_r18))->getComboID((u8) var_r17) != 0) {
                    var_r16 = 1;
                } else {
                    var_r17 += 1;
                    goto loop_14;
                }
            }
            if (fightTrainerAiDB_GetPokemonSelectRandomFlag(temp_r31) == 1) {
loop_17:
                if (var_r21 < p3) {
                    temp_r3_4 = _fightTrainerAiSortFirstSelectPokemonArySubSelect((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (Hero*)((Hero *) p1), (Pokemon**)((Pokemon **) p2), (u16) (u8) p3, 0U, (Pokemon**)(&sp10));
                    if (temp_r3_4 != 0) {
                        temp_r20 = (var_r21 * 4) & 0x3FFFC;
                        *((u8 *)p2 + temp_r20) = (unsigned char)(*(&(u8*)(sp10) + (((HSD_Rand() % temp_r3_4) * 4) & 0x3FFFC)));
                        fightPokemonCreate((FightTrainer*)((FightTrainer *) p0), (FightPokemon*)(temp_r3), (Pokemon*)(*((u8 *)p2 + temp_r20)), fightFloorGetFightPokemonEntryCntInc((FIGHT_FLOOR*)(NULL)));
                        *(&sp8 + var_r21) = fightTrainerAiGetFightPokemonKeyPlayerFlag((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (FightPokemon*)(temp_r3));
                        var_r21 += 1;
                        goto loop_17;
                    }
                }
            } else {
                if (var_r16 == 1) {
                    temp_r3_5 = fightTrainerAi_SelComboPartner((Pokemon **)((s32 *) &sp10), (Pokemon **)(p2), (unsigned char)(_fightTrainerAiSortFirstSelectPokemonArySubSelect((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (Hero*)((Hero *) p1), (Pokemon**)((Pokemon **) p2), p3, 0U, (Pokemon**)(&sp10))), (FIGHT_TRAINER *)(p0));
                    var_r29 = temp_r3_5;
                    var_r21 = (u16) temp_r3_5;
                }
                var_r19 = 0;
loop_23:
                if (var_r19 < var_r15) {
                    temp_r3_6 = _fightTrainerAiSortFirstSelectPokemonArySubSelect((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (Hero*)((Hero *) p1), (Pokemon**)((Pokemon **) p2), p3, 1U, (Pokemon**)(&sp10));
                    if (temp_r3_6 != 0) {
                        temp_r6 = HSD_Rand();
                        temp_r4 = (s32) temp_r6 / (s32) temp_r3_6;
                        *(&sp8 + var_r21) = 2;
                        temp_r3_7 = (var_r21 * 4) & 0x3FFFC;
                        var_r21 += 1;
                        var_r19 += 1;
                        *((u8 *)p2 + temp_r3_7) = (unsigned char)(*(&(u8*)(sp10) + (((temp_r6 - (temp_r4 * temp_r3_6)) * 4) & 0x3FFFC)));
                        goto loop_23;
                    }
                }
                var_r17_2 = 0;
loop_27:
                if (var_r17_2 < var_r15) {
                    temp_r3_8 = _fightTrainerAiSortFirstSelectPokemonArySubSelect((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (Hero*)((Hero *) p1), (Pokemon**)((Pokemon **) p2), p3, 2U, (Pokemon**)(&sp10));
                    if (temp_r3_8 != 0) {
                        temp_r6_2 = HSD_Rand();
                        temp_r4_2 = (s32) temp_r6_2 / (s32) temp_r3_8;
                        *(&sp8 + var_r21) = 3;
                        temp_r3_9 = (var_r21 * 4) & 0x3FFFC;
                        var_r21 += 1;
                        var_r17_2 += 1;
                        *((u8 *)p2 + temp_r3_9) = (unsigned char)(*(&(u8*)(sp10) + (((temp_r6_2 - (temp_r4_2 * temp_r3_8)) * 4) & 0x3FFFC)));
                        goto loop_27;
                    }
                }
loop_31:
                if (var_r21 < p3) {
                    temp_r3_10 = _fightTrainerAiSortFirstSelectPokemonArySubSelect((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (Hero*)((Hero *) p1), (Pokemon**)((Pokemon **) p2), p3, 3U, (Pokemon**)(&sp10));
                    if (temp_r3_10 != 0) {
                        temp_r19 = (var_r21 * 4) & 0x3FFFC;
                        *((u8 *)p2 + temp_r19) = (unsigned char)(*(&(u8*)(sp10) + (((HSD_Rand() % temp_r3_10) * 4) & 0x3FFFC)));
                        fightPokemonCreate((FightTrainer*)((FightTrainer *) p0), (FightPokemon*)(temp_r3), (Pokemon*)(*((u8 *)p2 + temp_r19)), fightFloorGetFightPokemonEntryCntInc((FIGHT_FLOOR*)(NULL)));
                        *(&sp8 + var_r21) = fightTrainerAiGetFightPokemonKeyPlayerFlag((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (FightPokemon*)(temp_r3));
                        var_r21 += 1;
                        goto loop_31;
                    }
                }
loop_35:
                if (var_r21 < p3) {
                    temp_r3_11 = _fightTrainerAiSortFirstSelectPokemonArySubSelect((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (Hero*)((Hero *) p1), (Pokemon**)((Pokemon **) p2), p3, 0U, (Pokemon**)(&sp10));
                    if (temp_r3_11 != 0) {
                        temp_r19_2 = (var_r21 * 4) & 0x3FFFC;
                        *((u8 *)p2 + temp_r19_2) = (unsigned char)(*(&(u8*)(sp10) + (((HSD_Rand() % temp_r3_11) * 4) & 0x3FFFC)));
                        fightPokemonCreate((FightTrainer*)((FightTrainer *) p0), (FightPokemon*)(temp_r3), (Pokemon*)(*((u8 *)p2 + temp_r19_2)), fightFloorGetFightPokemonEntryCntInc((FIGHT_FLOOR*)(NULL)));
                        *(&sp8 + var_r21) = fightTrainerAiGetFightPokemonKeyPlayerFlag((FIGHT_TRAINER*)((FIGHT_TRAINER *) p0), (FightPokemon*)(temp_r3));
                        if ((u8) *(&sp8 + var_r21) == 2) {
                            *(&sp8 + var_r21) = 3;
                        }
                        var_r21 += 1;
                        goto loop_35;
                    }
                }
            }
            if (fightTrainerAiDB_GetPokemonSelectRandomFlag(temp_r31) != 1) {
                if (fightTrainerAiDB_GetPokemonDataOrderOutFlag(temp_r31) == 1) {
                    var_r20 = 0;
                    while (var_r20 < p3) {
                        temp_r16 = (var_r20 * 4) & 0x3FFFC;
                        if ((u32) *((u8 *)p2 + temp_r16) != 0U) {
                            var_r21_2 = var_r20 + 1;
                            while (var_r21_2 < p3) {
                                temp_r15 = (var_r21_2 * 4) & 0x3FFFC;
                                if ((u32) *((u8 *)p2 + temp_r15) != 0U) {
                                    temp_r29 = pokemon_GetFightTrainerPokemonDataId((Pokemon*)(*((u8 *)p2 + temp_r16)));
                                    if (temp_r29 > pokemon_GetFightTrainerPokemonDataId((Pokemon*)(*((u8 *)p2 + temp_r15)))) {
                                        *((u8 *)p2 + temp_r16) = *((u8 *)p2 + temp_r15);
                                        *(&sp8 + var_r20) = *(&sp8 + var_r21_2);
                                        *((u8 *)p2 + temp_r15) = *((u8 *)p2 + temp_r16);
                                        *(&sp8 + var_r21_2) = *(&sp8 + var_r20);
                                    }
                                }
                                var_r21_2 += 1;
                            }
                        }
                        var_r20 += 1;
                    }
                } else {
                    var_r12 = var_r29;
loop_63:
                    if ((u16) var_r12 < p3) {
                        temp_r7 = (var_r12 * 4) & 0x3FFFC;
                        if ((u32) *((u8 *)p2 + temp_r7) != 0U) {
                            var_r15_2 = 1;
                            var_r15_2 += var_r12;
                            while (var_r15_2 < p3) {
                                temp_r6_3 = (var_r15_2 * 4) & 0x3FFFC;
                                temp_r11 = *((u8 *)p2 + temp_r6_3);
                                if (temp_r11 != 0U) {
                                    temp_r5 = *(&sp8 + (u16) var_r12);
                                    if (temp_r5 != 2) {
                                        temp_r4_3 = *(&sp8 + var_r15_2);
                                        if (temp_r4_3 == 2) {
                                            *(&sp8 + (u16) var_r12) = temp_r4_3;
                                            *((u8 *)p2 + temp_r7) = temp_r11;
                                            *((u8 *)p2 + temp_r6_3) = *((u8 *)p2 + temp_r7);
                                            *(&sp8 + var_r15_2) = temp_r5;
                                        }
                                    }
                                }
                                var_r15_2 += 1;
                            }
                        }
                        var_r12 += 1;
                        goto loop_63;
                    }
                }
            }
            M2C_FIELD(temp_r3, s32 *, 0) = sp328;
            memcpy((void*)(((u8*)(temp_r3) + 4)), (const void*)(&sp32C), 0xC4U);
            M2C_FIELD(temp_r3, s32 *, 0xC8) = sp3F0;
            M2C_FIELD(temp_r3, s32 *, 0xCC) = sp3F4;
            M2C_FIELD(temp_r3, s32 *, 0xD0) = sp3F8;
            M2C_FIELD(temp_r3, s32 *, 0xD4) = sp3FC;
            M2C_FIELD(temp_r3, s16 *, 0xD8) = sp400;
            M2C_FIELD(temp_r3, u8 *, 0xDA) = sp402;
            M2C_FIELD(temp_r3, u8 *, 0xDB) = sp403;
            M2C_FIELD(temp_r3, u8 *, 0xDC) = sp404;
            M2C_FIELD(temp_r3, u8 *, 0xDD) = sp405;
            M2C_FIELD(temp_r3, u16 *, 0xDE) = sp406;
            M2C_STRUCT_COPY((s32) (((u8*)(temp_r3) + 0xDC)) + 4, (s32) &sp404 + 4, 0x20);
            M2C_STRUCT_COPY((s32) (((u8*)(temp_r3) + 0xFC)) + 4, (s32) &sp424 + 4, 0x200);
            M2C_FIELD(temp_r3_2, s32 *, 0) = sp28;
            memcpy((void*)(temp_r3_2 + 4), (const void*)(&sp2C), 0xC4U);
            M2C_FIELD(temp_r3_2, s32 *, 0xC8) = spF0;
            M2C_FIELD(temp_r3_2, s32 *, 0xCC) = spF4;
            M2C_FIELD(temp_r3_2, s32 *, 0xD0) = spF8;
            M2C_FIELD(temp_r3_2, s32 *, 0xD4) = spFC;
            M2C_FIELD(temp_r3_2, s16 *, 0xD8) = sp100;
            M2C_FIELD(temp_r3_2, u8 *, 0xDA) = sp102;
            M2C_FIELD(temp_r3_2, u8 *, 0xDB) = sp103;
            M2C_FIELD(temp_r3_2, u8 *, 0xDC) = sp104;
            M2C_FIELD(temp_r3_2, u8 *, 0xDD) = sp105;
            M2C_FIELD(temp_r3_2, u16 *, 0xDE) = sp106;
            M2C_STRUCT_COPY((s32) (temp_r3_2 + 0xDC) + 4, (s32) &sp104 + 4, 0x20);
            M2C_STRUCT_COPY((s32) (temp_r3_2 + 0xFC) + 4, (s32) &sp124 + 4, 0x200);
        }
    }
}
}

extern "C++" {
static u16 _fightTrainerAiSortFirstSelectPokemonArySubSelect(FIGHT_TRAINER* p0, Hero* p1, Pokemon** p2, unsigned short p3, unsigned char p4, Pokemon** p5) {
    enum TsE { TsE0 };
    s32 sp404;
    u16 sp3E6;
    u8 sp3E5;
    enum TsE sp3E4;
    u8 sp3E3;
    u8 sp3E2;
    s16 sp3E0;
    s32 sp3DC;
    s32 sp3D8;
    s32 sp3D4;
    s32 sp3D0;
    s32 sp30C;
    s32 sp308;
    s32 sp104;
    u16 spE6;
    u8 spE5;
    u8 spE4;
    u8 spE3;
    u8 spE2;
    s16 spE0;
    s32 spDC;
    s32 spD8;
    s32 spD4;
    s32 spD0;
    s32 spC;
    s32 sp8;
    FightPokemon *temp_r3;
    s32 temp_r0;
    s32 temp_r0_2;
    u16 var_r27;
    u16 var_r28;
    u16 var_r4;
    u16 var_r4_2;
    u16 var_r4_3;
    u32 temp_r3_3;
    u32 temp_r3_4;
    u8 *temp_r3_2;

    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId((FIGHT_TRAINER *)((u8*)((u8 *) p0))));
    var_r4 = 0;
    while (var_r4 < 6U) {
        temp_r0 = (var_r4 * 4) & 0x3FFFC;
        var_r4 += 1;
        *(p5 + temp_r0) = 0;
    }
    temp_r3 = (FightPokemon *)(fightTrainer_GetFightPokemonPtr((u8*)((u8 *) p0), 0U));
    if (temp_r3 == NULL) {
        return 0U;
    }
    temp_r3_2 = (unsigned char *)(fightTrainer_GetFightPokemonPtr((u8*)((u8 *) p0), 1U));
    if (temp_r3_2 == NULL) {
        return 0U;
    }
    sp308 = M2C_FIELD(temp_r3, s32 *, 0);
    memcpy((void*)(&sp30C), (const void*)(((u8*)(temp_r3) + 4)), 0xC4U);
    sp3D0 = M2C_FIELD(temp_r3, s32 *, 0xC8);
    sp3D4 = M2C_FIELD(temp_r3, s32 *, 0xCC);
    sp3D8 = M2C_FIELD(temp_r3, s32 *, 0xD0);
    sp3DC = M2C_FIELD(temp_r3, s32 *, 0xD4);
    sp3E0 = M2C_FIELD(temp_r3, s16 *, 0xD8);
    sp3E2 = M2C_FIELD(temp_r3, u8 *, 0xDA);
    sp3E3 = M2C_FIELD(temp_r3, u8 *, 0xDB);
    sp3E4 = (enum TsE)(M2C_FIELD(temp_r3, u8 *, 0xDC));
    sp3E5 = M2C_FIELD(temp_r3, u8 *, 0xDD);
    sp3E6 = M2C_FIELD(temp_r3, u16 *, 0xDE);
    M2C_STRUCT_COPY((s32) &sp3E4 + 4, (s32) (((u8*)(temp_r3) + 0xDC)) + 4, 0x20);
    M2C_STRUCT_COPY((s32) &sp404 + 4, (s32) (((u8*)(temp_r3) + 0xFC)) + 4, 0x200);
    sp8 = M2C_FIELD(temp_r3_2, s32 *, 0);
    memcpy((void*)(&spC), (const void*)(temp_r3_2 + 4), 0xC4U);
    spD0 = M2C_FIELD(temp_r3_2, s32 *, 0xC8);
    spD4 = M2C_FIELD(temp_r3_2, s32 *, 0xCC);
    spD8 = M2C_FIELD(temp_r3_2, s32 *, 0xD0);
    spDC = M2C_FIELD(temp_r3_2, s32 *, 0xD4);
    spE0 = M2C_FIELD(temp_r3_2, s16 *, 0xD8);
    spE2 = M2C_FIELD(temp_r3_2, u8 *, 0xDA);
    spE3 = M2C_FIELD(temp_r3_2, u8 *, 0xDB);
    spE4 = M2C_FIELD(temp_r3_2, u8 *, 0xDC);
    spE5 = M2C_FIELD(temp_r3_2, u8 *, 0xDD);
    spE6 = M2C_FIELD(temp_r3_2, u16 *, 0xDE);
    M2C_STRUCT_COPY((s32) &spE4 + 4, (s32) (temp_r3_2 + 0xDC) + 4, 0x20);
    M2C_STRUCT_COPY((s32) &sp104 + 4, (s32) (temp_r3_2 + 0xFC) + 4, 0x200);
    var_r4_2 = 0;
    while (var_r4_2 < p3) {
        var_r4_2 += 1;
    }
    var_r27 = 0;
    var_r28 = 0;
    while (var_r28 < 6U) {
        temp_r3_3 = heroGetStatus((Hero*)(p1), 3U, var_r28);
        if ((temp_r3_3 != 0) && (pokemonCheckValid((Pokemon*)((Pokemon *) temp_r3_3)) != 0) && (pokemonCheckFightOut((Pokemon*)((Pokemon *) temp_r3_3)) != 0)) {
            var_r4_3 = 0;
loop_18:
            if (var_r4_3 < p3) {
                temp_r3_4 = (unsigned long)(*(p2 + ((var_r4_3 * 4) & 0x3FFFC)));
                if ((temp_r3_4 == 0U) || (temp_r3_4 != temp_r3_3)) {
                    var_r4_3 += 1;
                    goto loop_18;
                }
            }
            if (var_r4_3 >= p3) {
                fightPokemonCreate((FightTrainer*)((FightTrainer *) p0), (FightPokemon*)(temp_r3), (Pokemon*)((Pokemon *) temp_r3_3), fightFloorGetFightPokemonEntryCntInc((FIGHT_FLOOR*)(NULL)));
                switch (p4) {                       /* irregular */
                case 1:
                    s32 cmpv = fightTrainerAiGetFightPokemonKeyPlayerFlag((FIGHT_TRAINER*)(p0), (FightPokemon*)(temp_r3));
                    if (cmpv == 2) {
                    default:
                    case 0:
block_30:
                        temp_r0_2 = (var_r27 * 4) & 0x3FFFC;
                        var_r27 += 1;
                        *(p5 + temp_r0_2) = (Pokemon *)(temp_r3_3);
                    }
                    break;
                case 2:
                    if (fightTrainerAiGetFightPokemonKeyPlayerFlag((FIGHT_TRAINER*)(p0), (FightPokemon*)(temp_r3)) == 3) {
                        goto block_30;
                    }
                    break;
                case 3:
                    if ((fightTrainerAiGetFightPokemonKeyPlayerFlag((FIGHT_TRAINER*)(p0), (FightPokemon*)(temp_r3)) != 2) && (fightTrainerAiGetFightPokemonKeyPlayerFlag((FIGHT_TRAINER*)(p0), (FightPokemon*)(temp_r3)) != 3)) {
                        goto block_30;
                    }
                    break;
                }
            }
        }
        var_r28 += 1;
    }
    M2C_FIELD(temp_r3, s32 *, 0) = sp308;
    memcpy((void*)(((u8*)(temp_r3) + 4)), (const void*)(&sp30C), 0xC4U);
    M2C_FIELD(temp_r3, s32 *, 0xC8) = sp3D0;
    M2C_FIELD(temp_r3, s32 *, 0xCC) = sp3D4;
    M2C_FIELD(temp_r3, s32 *, 0xD0) = sp3D8;
    M2C_FIELD(temp_r3, s32 *, 0xD4) = sp3DC;
    M2C_FIELD(temp_r3, s16 *, 0xD8) = sp3E0;
    M2C_FIELD(temp_r3, u8 *, 0xDA) = sp3E2;
    M2C_FIELD(temp_r3, u8 *, 0xDB) = sp3E3;
    M2C_FIELD(temp_r3, u8 *, 0xDC) = sp3E4;
    M2C_FIELD(temp_r3, u8 *, 0xDD) = sp3E5;
    M2C_FIELD(temp_r3, u16 *, 0xDE) = sp3E6;
    M2C_STRUCT_COPY((s32) (((u8*)(temp_r3) + 0xDC)) + 4, (s32) &sp3E4 + 4, 0x20);
    M2C_STRUCT_COPY((s32) (((u8*)(temp_r3) + 0xFC)) + 4, (s32) &sp404 + 4, 0x200);
    M2C_FIELD(temp_r3_2, s32 *, 0) = sp8;
    memcpy((void*)(temp_r3_2 + 4), (const void*)(&spC), 0xC4U);
    M2C_FIELD(temp_r3_2, s32 *, 0xC8) = spD0;
    M2C_FIELD(temp_r3_2, s32 *, 0xCC) = spD4;
    M2C_FIELD(temp_r3_2, s32 *, 0xD0) = spD8;
    M2C_FIELD(temp_r3_2, s32 *, 0xD4) = spDC;
    M2C_FIELD(temp_r3_2, s16 *, 0xD8) = spE0;
    M2C_FIELD(temp_r3_2, u8 *, 0xDA) = spE2;
    M2C_FIELD(temp_r3_2, u8 *, 0xDB) = spE3;
    M2C_FIELD(temp_r3_2, u8 *, 0xDC) = spE4;
    M2C_FIELD(temp_r3_2, u8 *, 0xDD) = spE5;
    M2C_FIELD(temp_r3_2, u16 *, 0xDE) = spE6;
    M2C_STRUCT_COPY((s32) (temp_r3_2 + 0xDC) + 4, (s32) &spE4 + 4, 0x20);
    M2C_STRUCT_COPY((s32) (temp_r3_2 + 0xFC) + 4, (s32) &sp104 + 4, 0x200);
    return var_r27;
}
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
 // The original saw 32-bit return types here (no masks on the sum), while the BasisPhyDef/SpeDef wrappers below
 // need the u16 prototypes: block-scope declarations reproduce both.
    extern u32 pokemonDB_GetBasisPhyDef(u16);
    extern u32 pokemonDB_GetBasisSpeDef(u16);
    u32 def;
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
    void* refSide;
    TokuseiSearch* search = (TokuseiSearch*)data;
    FightOutPokemon* ref = search->ref;
    FIGHT_TRAINER* trainer = search->trainer;
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
    extern u32 fightTrainerAiCheckFightOutPokemonCanOutOkWazaBanme(FIGHT_TRAINER*, FightOutPokemon*, u8);
    extern u16 fightTrainerAiGetFightOutPokemonWazaDataId(FIGHT_TRAINER*, FightOutPokemon*, u8);
    u16 j;
    u16 count;
    u16 entry;
    u16 i;
    u8 type = fightFloor_GetFightType(0);
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
    extern u8 fightTrainerAiGetFightPokemonWazaNowPp(FIGHT_TRAINER*, FightPokemon*, u8);
    extern u16 fightTrainerAiGetFightPokemonWazaDataId(FIGHT_TRAINER*, FightPokemon*, u8);
    u16 j;
    u16 count;
    u16 entry;
    u16 i;
    u8 type = fightFloor_GetFightType(0);
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
        u32 owner = fightFloorGetFightPokemonPtrToFightTrainerPtr(0, p);
        if (owner != (u32)t) {
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
    if ((s16)fightTrainerAiDB_GetZokuseiCheckFlag(ai) == 1) {
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
    u16 k;
    FightPokemon* pokes[8];
    u16 outCount;
    u16 pokeCount;
    u16 i;
    u16 j;
    s32 damage;
    FightOutPokemon* o;
    FightOutPokemon* outs[8];
    outCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, outs, 0, 1);
    pokeCount = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, pokes, 1, 1);
    for (i = 0; i < pokeCount; i++) {
        FightPokemon* fp = pokes[i];
        if (fp != 0) {
            for (j = 0; j < outCount; j++) {
                o = outs[j];
                if (o != 0 && fightOutPokemonGetFightEntryId(o) >= 0) {
                    u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, o, wazas, 0, 0);
                    u16 maxHp = fightOutPokemonMaxHpWaruValue(o, 1);
                    for (k = 0; k < n; k++) {
                        damage = 0;
                        u16 waza = wazas[k];
                        if (waza != 0 && waza != 0x176 && fightTrainerAiGetWazaZokuseiDataId(t, waza, o) != 9) {
                            u32 index;
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

struct ExpectWazaData {
    u16 mons;
    u16 waza[8];
};
extern "C" {
extern ExpectWazaData expect_waza_data[];
void fightTrainerInitEnemyPokemonFightOutStatus(void* trainer, u8 mode);
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*, u8);
void fightTrainer_SetEnemyExpectWazaNum(u8* t, s16 id, u8 v);
void fightTrainer_SetEnemyNowhp1banhikuiFlag(u8* t, s16 id, u8 v);
void fightTrainer_SetEnemyLv1banhikuiFlag(u8* t, s16 id, u8 v);
void fightTrainer_SetEnemyDefense1banhikuiFlag(u8* t, s16 id, u8 v);
void fightTrainer_SetEnemyBadwazaHaveFlag(u8* t, s16 id, u8 v);
void fightTrainer_SetEnemyParam1bantakaiFlag(u8* t, s16 id, u8 v);
void fightTrainerAiSetEnemyPokemon(FIGHT_TRAINER* t) {
    FightOutPokemon* enemies[8];
    u32 param[8];
    s32 percent[8];
    u16 wazaIds[8];
    FightOutPokemon* allies[8];
    u32 damage[8];
    u16 enemyNum;
    u16 allyNum;
    u16 minHp;
    s32 maxPercent;
    FightOutPokemon* e;
    FightOutPokemon* a;
    s16 entry;
    u16 waza;
    u8 minLv;
    s32 maxParam;
    u16 minDef;
    u32 i;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(t));
    fightTrainerInitEnemyPokemonFightOutStatus(t, 1);
    for (i = 0; i < 8; i++) {
        damage[i] = 0;
        param[i] = 0;
    }
    enemyNum = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, enemies, 0, 1);
    allyNum = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, t, allies, 1, 1);
    minHp = 0xFFFF;
    maxPercent = -0xFFFF;
    minDef = 0xFFFF;
    maxParam = -0xFFFF;
    minLv = 0xFF;
    for (u16 i = 0; i < enemyNum; i++) {
        e = enemies[i];
        if (e) {
            entry = fightOutPokemonGetFightEntryId(e);
            if (entry >= 0) {
                u16 mons = fightTrainerAiGetFightOutPokemonPokemonDataId(t, e);
                u32 k;
                u16 hp;
                u32 j;
                u16 wazaNum = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, e, wazaIds, 0, 0);
                u16 v = fightTrainerAiGetFightOutPokemonNowHpPercentage(t, e);
                if (minHp > v) {
                    minHp = v;
                }
                {
                    u8 lv = fightTrainerAiGetFightOutPokemonLevel(t, e);
                    if (minLv > lv) {
                        minLv = lv;
                    }
                }
                v = fightTrainerAiGetPokemonDataDefense(t, mons);
                if (minDef > v) {
                    minDef = v;
                }
                param[i] += fightTrainerAiGetFightOutPokemonBasisMaxHp(t, e);
                param[i] += fightTrainerAiGetFightOutPokemonBasisPhyAtk(t, e);
                param[i] += fightTrainerAiGetFightOutPokemonBasisPhyDef(t, e);
                param[i] += fightTrainerAiGetFightOutPokemonBasisSpeAtk(t, e);
                param[i] += fightTrainerAiGetFightOutPokemonBasisSpeDef(t, e);
                param[i] += fightTrainerAiGetFightOutPokemonBasisSubayasa(t, e);
                param[i] *= fightTrainerAiGetFightOutPokemonLevel(t, e);
                if (maxParam < (s32)param[i]) {
                    maxParam = param[i];
                }
                fightAi_AddStoreTokusei(e, t);
                hp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(e));
                for (u16 j = 0; j < allyNum; j++) {
                    a = allies[j];
                    if (a) {
                        for (u16 k = 0; k < wazaNum; k++) {
                            waza = wazaIds[k];
                            if (waza != 0 && waza != 0x176 && fightTrainerAiGetWazaZokuseiDataId(t, waza, e) != 9 &&
                                fightTrainerAiIsWazaTypeId(t, waza, 1) != 0) {
                                damage[i] += fightTrainerAiWazaDoWazaDamageFunc(t, e, waza, a, 0);
                                percent[i] = (s32)(damage[i] * 100) / (s32)hp;
                            }
                        }
                    }
                }
                if (maxPercent < percent[i]) {
                    maxPercent = percent[i];
                }
                for (j = 0; j < 0x96; j++) {
                    ExpectWazaData* d = &expect_waza_data[j];
                    if (d->mons == pokemon_GetPokemonDataId(fightOutPokemonGetPokemonPtr(e))) {
                        for (k = 0; k < 8; k++) {
                            u16 waza = d->waza[k];
                            if (waza == 0 || fightTrainer_GetEnemyExpectWazaData(t, entry, k) != 0) {
                                break;
                            }
                            fightTrainer_SetEnemyExpectWazaData(t, entry, k, waza);
                            fightTrainer_SetEnemyExpectWazaNum((u8*)t, entry, enemyNum);
                        }
                    }
                }
            }
        }
    }
    for (u16 i = 0; i < enemyNum; i++) {
        FightOutPokemon* e = enemies[i];
        if (e) {
            s16 entry = fightOutPokemonGetFightEntryId(e);
            if (entry >= 0) {
                u32 mons = fightTrainerAiGetFightOutPokemonPokemonDataId(t, e);
                if ((s32)minHp >= fightTrainerAiGetFightOutPokemonNowHpPercentage(t, e)) {
                    fightTrainer_SetEnemyNowhp1banhikuiFlag((u8*)t, entry, 1);
                }
                if (minLv >= fightTrainerAiGetFightOutPokemonLevel(t, e)) {
                    fightTrainer_SetEnemyLv1banhikuiFlag((u8*)t, entry, 1);
                }
                u16 cmpv = fightTrainerAiGetPokemonDataDefense(t, mons);
                if (minDef >= cmpv) {
                    fightTrainer_SetEnemyDefense1banhikuiFlag((u8*)t, entry, 1);
                }
                if (maxPercent <= percent[i]) {
                    fightTrainer_SetEnemyBadwazaHaveFlag((u8*)t, entry, 1);
                }
                if (maxParam <= (s32)param[i]) {
                    fightTrainer_SetEnemyParam1bantakaiFlag((u8*)t, entry, 1);
                }
            }
        }
    }
}
}

extern "C" {
void* fightTypeDataBiosGetPtr(u32 id);
u8 fightTypeDataBiosGetFightoutPokemonNum(void* data);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(void* trainer, u16 index);
u8 fightOutPokemonCheckFightActionSelect(FightOutPokemon* fop, u8 create);
void fightOutPokemonInitFightActionBuff(FightOutPokemon* fop);
FightOutPokemon* fightTrainerGetNoActionFightOutPokemonPtr(void* trainer, u16 index);
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(void* floor, FightOutPokemon* pokemon, FightOutPokemon** out);
s32 fightTrainerAiSelectFightActionIrekae(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, void* target);
u8 fightFloor_GetFightKindUseItemFlag(void* floor);
u8 fightTrainerAiSelectFightActionItem(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, void* target);
u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon* fop, u8 create);
void fightFloorSortFightOutPokemonPtrArySub(void* floor, FightOutPokemon** ary, u16 count, u8 useAction);
void fightTrainerAiSetEnemyPokemon(FIGHT_TRAINER* t);
void fightAi_FixedAct(FIGHT_TRAINER* trainer, void* target);
void fightAi_CreateAllWazaValid(FIGHT_TRAINER* trainer, FightOutPokemon** move, u8 count);
void fightAiCombo_ActContinue(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, void* target);
void fightAi_CheckDoFightActionStroke(FIGHT_TRAINER* trainer);
void fightAiCombo_Act(FIGHT_TRAINER* trainer, FightOutPokemon** ary, u8 count, void* target);
void fightTrainerAiSelectFightActionWaza(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, void* target);

void fightTrainerAiSelectFightAction(FIGHT_TRAINER* trainer, void* target) {
    FightOutPokemon* p;
    int num;
    u8 i;
    u8 count;
    FightOutPokemon* list[8];
    u16 found;
    fightTrainerAiSetEnemyPokemon(trainer);
    fightTrainerAiSetAllyPokemon(trainer);
    num = fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr((u32)target));
    for (i = 0; i < num; i++) {
        p = fightTrainerGetValidFightOutPokemonPtr(trainer, i);
        if (p && fightOutPokemonCheckFightActionSelect(p, 1) != 0) {
            fightOutPokemonInitFightActionBuff(p);
        }
    }
    fightAi_FixedAct(trainer, target);
    found = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, list, 1, 1);
    fightAi_CreateAllWazaValid(trainer, fightAi_JudgeMoveFightOutPokemon(trainer, list, &found), found);
    for (i = 0; i < num; i++) {
        FightOutPokemon* p = fightTrainerGetNoActionFightOutPokemonPtr(trainer, i);
        if (p) {
            fightAiCombo_ActContinue(trainer, p, target);
        }
    }
    fightAi_CheckDoFightActionStroke(trainer);
    if (fightTrainerAiCheckDoFightActionIrekae(trainer) == 1) {
        for (i = 0; i < num; i++) {
            FightOutPokemon* p = fightTrainerGetNoActionFightOutPokemonPtr(trainer, i);
            if (p && fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, p, 0) == 0) {
                fightTrainerAiSelectFightActionIrekae(trainer, p, target);
            }
        }
    }
    if (fightFloor_GetFightKindUseItemFlag(0) == 1 && fightTrainerAiCheckDoFightActionItem(trainer) == 1) {
        for (i = 0; i < num; i++) {
            FightOutPokemon* p = fightTrainerGetNoActionFightOutPokemonPtr(trainer, i);
            if (p) {
                fightTrainerAiSelectFightActionItem(trainer, p, target);
            }
        }
    }
    for (i = 0; i < 8; i++) {
        list[i] = 0;
    }
    for (i = 0, count = 0; i < num; i++) {
        FightOutPokemon* p = fightTrainerGetNoActionFightOutPokemonPtr(trainer, i);
        if (p) {
            list[count++] = p;
        }
    }
    if (count) {
        fightAiCombo_Act(trainer, list, (u16)count, target);
    }
    for (i = 0; i < 8; i++) {
        list[i] = 0;
    }
    for (i = 0, count = 0; i < num; i++) {
        FightOutPokemon* p = fightTrainerGetNoActionFightOutPokemonPtr(trainer, i);
        if (p && fightOutPokemonCheckFightActionWazaSelect(p, 1) == 0) {
            list[count++] = p;
        }
    }
    if (count) {
        fightFloorSortFightOutPokemonPtrArySub(0, list, 8, 0);
        for (i = 0; i < count; i++) {
            if (list[i]) {
                fightTrainerAiSelectFightActionWaza(trainer, list[i], target);
            }
        }
    }
}
}
}
