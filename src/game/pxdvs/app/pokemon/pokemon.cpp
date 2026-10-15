// pokemon.cpp was built with "-inline deferred" (extra_cflags in configure.py): MWCC then emits
// functions in REVERSE source order, so the definitions below are written last-to-first and
// .rodata comes out in parse order (matching the retail layout).
#include <global.h>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

// NOTE: pokemon.hpp / pokemonBios.hpp / pokemonDB.hpp are not included here: several of their
// prototypes (pokemonInit(u32), pokemonBiosSetHp(Pokemon*, s16), pokemon_GetPokemonDataId -> u32,
// pokemonGetStatus -> u16, ...) disagree with the types the retail code was compiled with.

struct PokemonData;
struct ItemData;
struct FightPokemon;
struct FightOutPokemon;
struct FightWaza;
struct Attest;
struct PokemonWaza {
    u16 dataId;
    u8 pp;
    u8 ppCount;
};
typedef struct PokemonGrowDataBios PokemonGrowDataBios;
typedef struct PokemonSeikakuDataBios PokemonSeikakuDataBios;
typedef struct PokemonSeikakuRateBios PokemonSeikakuRateBios;
typedef struct PokemonDpFilterData PokemonDpFilterData;
typedef struct PokemonFriendFilterData PokemonFriendFilterData;
typedef struct TasteData TasteData;

struct Pokemon {
    u8 data[0xC4];

    u16 getPokemonDataId() const;
    u8 getCondition() const;
    u8 getConditionCount() const;
    s8 getConditionTurn() const;
    s8 getConditionTurnNow() const;
    void initCondition();
    void setCondition(u8);
    void setConditionCount(u8);
    void setConditionTurn(u8);
    void setConditionTurnNow(u8);
    void copyCondition(const Pokemon*);
    bool isReversMode() const;
    void setReversMode(bool);
    DarkPokemon* getDarkPokemon();
};

struct FightJoutai {
    u16 joutaiDataId;
    u16 waza;
    u8 count;
    u8 turn;
    u8 turnNow;
    u8 target;
    u32 value;
    u16 kind;
};

struct MenuPokemonStatus {
    char16 name[11]; // 0x0
    u8 pad16;
    u8 level; // 0x17
    u16 maxHp; // 0x18
    u16 hp; // 0x1a
    union {
        u32 exp;
        f32 dp;
    } barMax; // 0x1c
    union {
        u32 exp;
        f32 dp;
    } barNow; // 0x20
    u16 joutaiSpriteId; // 0x24
    u16 faceId; // 0x26
    u8 sex; // 0x28
    u8 dark; // 0x29
    u16 itemDataId; // 0x2a
};

struct EffortEntry {
    u16 effortKind;
    u16 giveKind;
    u16 value;
};

struct MenuWazaStatusEntry {
    char16* name; // 0x0
    char16* zokuseiName; // 0x4
    u16 zokusei; // 0x8
    u8 maxPp; // 0xa
    u8 pp; // 0xb
};

struct MenuWazaStatus {
    char16* nickname; // 0x0
    MenuWazaStatusEntry waza[4]; // 0x4
    u8 pad[0x48 - 0x34];
};

extern "C" {
// pokemonDB accessors
u16 figthOutPokemonGetPokemonDataId(FightOutPokemon*);
u32 pokemonDB_GetShout(u16);
u16 pokemon_GetPokemonDataId(Pokemon*);
u32 pokemon_GetRnd(Pokemon*);
u32 pokemon_GetCatchTrainerRnd(Pokemon*);
u8 pokemon_GetCatchBallId(Pokemon*);
Attest* pokemon_GetAttest(Pokemon*);
u32 pokemon_GetExp(Pokemon*);
u8 pokemon_GetLevel(Pokemon*);
char16* pokemon_GetNicknamePtr(Pokemon*);
u8 pokemon_GetHinsi(Pokemon*);
u16 pokemon_GetPokemonWazaDataId(Pokemon*, u16);
u8 pokemon_GetPokemonWazaPp(Pokemon*, u16);
u8 pokemon_GetPokemonWazaPpCount(Pokemon*, u16);
u16 pokemon_GetItemDataId(Pokemon*);
u16 pokemon_GetHp(Pokemon*);
u16 pokemon_GetMaxHp(Pokemon*);
u8 pokemon_GetMaxHpRnd(Pokemon*);
u8 pokemon_GetPhyAtkRnd(Pokemon*);
u8 pokemon_GetPhyDefRnd(Pokemon*);
u8 pokemon_GetSpeAtkRnd(Pokemon*);
u8 pokemon_GetSpeDefRnd(Pokemon*);
u8 pokemon_GetNimblenessRnd(Pokemon*);
u16 pokemon_GetFriend(Pokemon*);
u8 pokemon_GetPokerus(Pokemon*);
u8 pokemon_GetTamagoFlag(Pokemon*);
u8 pokemon_GetTokuseiFlag(Pokemon*);
u8 pokemon_GetFuseiFlag(Pokemon*);
u32 pokemon_GetSeikaku(Pokemon*);
u8 pokemon_GetNowExpToLevel(Pokemon*);
u16 pokemon_GetDarkpokemonDataId(Pokemon*);
u16 pokemon_GetInitDp(Pokemon*);
u16 pokemon_GetPoolFriend(Pokemon*);
u8 pokemon_GetDarkFlag(Pokemon*);
void pokemon_SetPokemonDataId(Pokemon*, u16);
void pokemon_SetRnd(Pokemon*, u32);
void pokemon_SetCatchFloorId(Pokemon*, u16);
void pokemon_SetCatchLevel(Pokemon*, u8);
void pokemon_SetCatchBallId(Pokemon*, u8);
void pokemon_SetCatchTrainerSex(Pokemon*, u8);
void pokemon_SetCatchTrainerRnd(Pokemon*, u32);
void pokemon_SetCatchTrainerNamePtr(Pokemon*, char16*);
void pokemon_SetNicknamePtr(Pokemon*, char16*);
void pokemon_SetExp(Pokemon*, u32);
void pokemon_SetLevel(Pokemon*, u8);
void pokemon_SetConditionAmari(Pokemon*, u32);
void pokemon_SetPokemonWazaDataId(Pokemon*, u16, u16);
void pokemon_SetPokemonWazaPp(Pokemon*, u16, u8);
void pokemon_SetPokemonWazaPpCount(Pokemon*, u16, u8);
void pokemon_SetItemDataId(Pokemon*, u16);
void pokemon_SetHp(Pokemon*, u16);
void pokemon_SetMaxHp(Pokemon*, u16);
void pokemon_SetPhyAtk(Pokemon*, u16);
void pokemon_SetPhyDef(Pokemon*, u16);
void pokemon_SetSpeAtk(Pokemon*, u16);
void pokemon_SetSpeDef(Pokemon*, u16);
void pokemon_SetNimbleness(Pokemon*, u16);
void pokemon_SetMaxHpEffort(Pokemon*, u16);
void pokemon_SetPhyAtkEffort(Pokemon*, u16);
void pokemon_SetPhyDefEffort(Pokemon*, u16);
void pokemon_SetSpeAtkEffort(Pokemon*, u16);
void pokemon_SetSpeDefEffort(Pokemon*, u16);
void pokemon_SetNimblenessEffort(Pokemon*, u16);
void pokemon_SetMaxHpRnd(Pokemon*, u16);
void pokemon_SetPhyAtkRnd(Pokemon*, u16);
void pokemon_SetPhyDefRnd(Pokemon*, u16);
void pokemon_SetSpeAtkRnd(Pokemon*, u16);
void pokemon_SetSpeDefRnd(Pokemon*, u16);
void pokemon_SetNimblenessRnd(Pokemon*, u16);
void pokemon_SetFriend(Pokemon*, u16);
void pokemon_SetStyle(Pokemon*, u8);
void pokemon_SetBeautiful(Pokemon*, u8);
void pokemon_SetCute(Pokemon*, u8);
void pokemon_SetClever(Pokemon*, u8);
void pokemon_SetStrong(Pokemon*, u8);
void pokemon_SetFur(Pokemon*, u8);
void pokemon_SetChampRibbon(Pokemon*, bool);
void pokemon_SetWinningRibbon(Pokemon*, bool);
void pokemon_SetVictoryRibbon(Pokemon*, bool);
void pokemon_SetBromideRibbon(Pokemon*, bool);
void pokemon_SetGanbaRibbon(Pokemon*, bool);
void pokemon_SetMarineRibbon(Pokemon*, bool);
void pokemon_SetLandRibbon(Pokemon*, bool);
void pokemon_SetSkyRibbon(Pokemon*, bool);
void pokemon_SetCountryRibbon(Pokemon*, bool);
void pokemon_SetNationalRibbon(Pokemon*, bool);
void pokemon_SetEarthRibbon(Pokemon*, bool);
void pokemon_SetWorldRibbon(Pokemon*, bool);
void pokemon_SetAmariRibbon(Pokemon*, u8);
void pokemon_SetStyleMedal(Pokemon*, u8);
void pokemon_SetBeautifulMedal(Pokemon*, u8);
void pokemon_SetCuteMedal(Pokemon*, u8);
void pokemon_SetCleverMedal(Pokemon*, u8);
void pokemon_SetStrongMedal(Pokemon*, u8);
void pokemon_SetPokerus(Pokemon*, u8);
void pokemon_SetTamagoFlag(Pokemon*, bool);
void pokemon_SetTokuseiFlag(Pokemon*, u32);
void pokemon_SetFuseiFlag(Pokemon*, bool);
void pokemon_SetFlagAmari(Pokemon*, u8);
void pokemon_SetPcboxMark(Pokemon*, u8);
void pokemon_SetMailId(Pokemon*, u8);
void pokemon_SetPara1Amari(Pokemon*, u16);
void pokemon_SetAmari(Pokemon*, u16);
void pokemon_SetFightTrainerPokemonDataId(Pokemon*, u16);
void pokemon_SetDarkpokemonDataId(Pokemon*, u16);
void pokemon_SetPoolExp(Pokemon*, u32);
void pokemon_SetPoolFriend(Pokemon*, u16);
const char* pokemonDB_GetName(u16);
u32 pokemonDB_GetPkxDataId(u16);
u8 pokemonDB_GetGrowDataId(u16);
u8 pokemonDB_GetSexRatio(u16);
u32 pokemonDB_GetInitFriend(u16);
u8 pokemonDB_GetTokuseiDataId(u16, u16);
u8 pokemonDB_GetGetWazaLevel(u16, u16);
u16 pokemonDB_GetGetWazaDataId(u16, u16);
void pokemonDB_SetMitaFlag(u16, bool);
void pokemonDB_SetTukamaetaFlag(u16, bool);

// other systems
u32 HSD_Rand(void);
void* memset(void*, int, u32);
void GScharCpy(char16*, const char16*);
char16* GSmsgGetGSchar(u32);
void GSsndPlay(u16, u32, u32);
u16 menuFaceGetID(Pokemon*);
u16 menuFaceGetID3(Pokemon*, u8, u8);
u8 menuSubGetPokemonSexForFightDisp(Pokemon*);
u8 menuCBRule_DEOKISISUCamouflage(void);
u16 menuGBACGetRomVer(u16);
u8 fightFloor_GetFightKindRegulationFlag(void*);
void* fightFloorGetFightPokemonPtrToFightTrainerPtr(void*, FightPokemon*);
u8 fightTrainer_GetControllerId(void*);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
u8 dbgMenuFightGetSoubikoukaFlag(void);
u16 itemDB_GetItemSoubiDataId(u16);
u32 itemDB_GetBuff(u16);
ItemData* itemDataBiosGetPtr(u16);
u8 itemDataBiosGetKind(ItemData*);
u32 itemDataBiosGetBuff(ItemData*);
u16 joutaiDataBiosGetStatus(u16);
u32 joutaiDataBiosGetName(u32);
u8 joutaiDataBiosGetKaisuuDataId(u16);
u8 joutaiDataBiosGetMaxCount(u16);
s32 kaisuuGetKaisuu(u32);
u16 darkPokemonBiosGetDarkPoint(u16);
u16 darkPokemonBiosGetTemotiDarkWaza(u16, u16);
PokemonSeikakuDataBios* pokemonSeikakuDataBiosGetPtr(u32);
s8 pokemonSeikakuDataBiosGetReliveFightout(PokemonSeikakuDataBios*);
s8 pokemonSeikakuDataBiosGetReliveWalk(PokemonSeikakuDataBios*);
s8 pokemonSeikakuDataBiosGetReliveSodateya(PokemonSeikakuDataBios*);
s8 pokemonSeikakuDataBiosGetReliveNadenade(PokemonSeikakuDataBios*);
s8 pokemonSeikakuDataBiosGetReliveCall(PokemonSeikakuDataBios*);
u32 pokemonSeikakuDataBiosGetPhyAtkRateDataId(PokemonSeikakuDataBios*);
u32 pokemonSeikakuDataBiosGetPhyDefRateDataId(PokemonSeikakuDataBios*);
u32 pokemonSeikakuDataBiosGetSpeAtkRateDataId(PokemonSeikakuDataBios*);
u32 pokemonSeikakuDataBiosGetSpeDefRateDataId(PokemonSeikakuDataBios*);
u32 pokemonSeikakuDataBiosGetNimblenessRateDataId(PokemonSeikakuDataBios*);
PokemonSeikakuRateBios* pokemonSeikakuRateDataBiosGetPtr(u32);
u8 pokemonSeikakuRateDataBiosGetKake(PokemonSeikakuRateBios*);
u8 pokemonSeikakuRateDataBiosGetWaru(PokemonSeikakuRateBios*);
PokemonDpFilterData* pokemonDpFilterDataBiosGetPtr(u16);
s8 pokemonDpFilterDataBiosGetValue(PokemonDpFilterData*);
PokemonFriendFilterData* pokemonFriendFilterDataBiosGetPtr(u16);
s8 pokemonFriendFilterDataBiosGetValue(PokemonFriendFilterData*, u8);
PokemonGrowDataBios* pokemonGrowDataBiosGetPtr(u8);
u32 pokemonGrowDataBiosGetExp(PokemonGrowDataBios*, u8);
TasteData* tasteDataGetPtr(u32);
s32 tasteDataGetAisyou(TasteData*, u8);
u32 wazaDB_GetName(u16);
u32 wazaDB_GetZokuseiDataId(u16);
u8 wazaGetMaxPP(u16, u8);
u32 zokuseiBiosGetName(u8);
u8 sexGetPokemonSexRaitoKotei(u32);
void memoDataSet(u32, Pokemon*);
u32 Sequence_LoadPokemon(u16, u32, u32);
void Sequence_SetStatus(u32, u32);
void Sequence_ResetStatus(u32, u32);
void gamedataAttestInit(Attest*);
bool gamedataAttestCheckValid(Attest*);
void gamedataAttestBiosCopy(Attest*, Attest*);
PokemonWaza* pokemonBiosGetPokemonWazaPtr(Pokemon*, u16, u8);
void pokemonWazaBiosCopy(PokemonWaza*, const PokemonWaza*);
void pokemonBiosCopy(Pokemon*, const Pokemon*);
PokemonData* pokemonDataBiosGetPtr(u16);
FightJoutai* fightPokemon_GetFightJoutaiPtr(FightPokemon*, u16);
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
void fightWaza_SetUseWazaDataId(FightWaza*, u16);
void fightWaza_SetMotoWazaDataId(FightWaza*, u16);
void fightWaza_SetDamageValue(FightWaza*, u8);
void fightWaza_SetCritical(FightWaza*, u8);
u8 fightWazaCheckWriteJoutaiDataId(FightWaza*, u16);
void fightWazaWriteJoutaiDataId(FightWaza*, u16, u32);
u8 fightWazaIsJoutaiDataId(FightWaza*, u16);
void fightWazaInitJoutaiDataId(FightWaza*, u16);
void fightWazaInitJoutai(FightWaza*);
void fightWaza_SetDamage(FightWaza*, u32);
void fightWaza_SetIryoku(FightWaza*, u16);
void fightWaza_SetTargetDataId(FightWaza*, u16);
void fightWaza_SetHitDamage(FightWaza*, u32);
u8 fightWaza_GetDamageValue(FightWaza*);
u8 fightWaza_GetCritical(FightWaza*);
u8 fightWazaIsHit(FightWaza*);
u32 fightWaza_GetDamage(FightWaza*);
u16 fightWaza_GetIryoku(FightWaza*);
u16 fightWaza_GetTargetDataId(FightWaza*);
u32 fightWaza_GetHitDamage(FightWaza*);

extern u32* pokemon_data_number;
extern u16 spriteTbl[][2];

// generated accessor prototypes (types taken from the retail call sites)
s16 fightOutPokemonBiosGetDamageAtkValue(FightOutPokemon*);
s16 fightOutPokemonBiosGetDamageSpeValue(FightOutPokemon*);
s16 fightOutPokemonBiosGetGamanDamageValue(FightOutPokemon*);
s16 fightOutPokemonBiosGetIrekaeTargetEntryId(FightOutPokemon*);
s16 fightOutPokemonBiosGetMeetEnemyFightPokemonEntryId(FightOutPokemon*, u8);
s16 fightOutPokemonBiosGetMyselfDamageAtkValue(FightOutPokemon*);
s16 fightOutPokemonBiosGetMyselfDamageSpeValue(FightOutPokemon*);
s16 fightPokemonBiosGetEntryId(FightPokemon*);
u16 fightOutPokemonBiosGetDamageAtkTargetId(FightOutPokemon*);
u16 fightOutPokemonBiosGetDamageSpeTargetId(FightOutPokemon*);
u16 fightOutPokemonBiosGetFightoutTurnCount(FightOutPokemon*);
u16 fightOutPokemonBiosGetGamanDamageTargetId(FightOutPokemon*);
u16 fightOutPokemonBiosGetHitWazaDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetHitWazaZokuseiDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetLastReceiveWazaTargetDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetLastSelectWazaDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetLastUseWazaDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetMyselfDamageAtkTargetId(FightOutPokemon*);
u16 fightOutPokemonBiosGetMyselfDamageSpeTargetId(FightOutPokemon*);
u16 fightOutPokemonBiosGetOumuWazaDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetSketchWazaDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetStockItemDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetTokuseiDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetUsedItemDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetZokuseiDataId(FightOutPokemon*, u8);
u16 fightOutPokemonGetMotoWazaDataId(FightOutPokemon*);
u16 fightOutPokemonGetUseWazaDataId(FightOutPokemon*);
u16 pokemonBiosGetAmari(Pokemon*);
u16 pokemonBiosGetCatchFloorId(Pokemon*);
u16 pokemonBiosGetDarkpokemonDataId(Pokemon*);
u16 pokemonBiosGetFightTrainerPokemonDataId(Pokemon*);
u16 pokemonBiosGetFriend(Pokemon*);
u16 pokemonBiosGetHp(Pokemon*);
u16 pokemonBiosGetInitDp(Pokemon*);
u16 pokemonBiosGetItemDataId(Pokemon*);
u16 pokemonBiosGetMaxHp(Pokemon*);
u16 pokemonBiosGetMaxHpEffort(Pokemon*);
u16 pokemonBiosGetMaxHpRnd(Pokemon*);
u16 pokemonBiosGetNimbleness(Pokemon*);
u16 pokemonBiosGetNimblenessEffort(Pokemon*);
u16 pokemonBiosGetNimblenessRnd(Pokemon*);
u16 pokemonBiosGetPara1Amari(Pokemon*);
u16 pokemonBiosGetPhyAtk(Pokemon*);
u16 pokemonBiosGetPhyAtkEffort(Pokemon*);
u16 pokemonBiosGetPhyAtkRnd(Pokemon*);
u16 pokemonBiosGetPhyDef(Pokemon*);
u16 pokemonBiosGetPhyDefEffort(Pokemon*);
u16 pokemonBiosGetPhyDefRnd(Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon*, u16);
u16 pokemonBiosGetPoolFriend(Pokemon*);
u16 pokemonBiosGetSpeAtk(Pokemon*);
u16 pokemonBiosGetSpeAtkEffort(Pokemon*);
u16 pokemonBiosGetSpeAtkRnd(Pokemon*);
u16 pokemonBiosGetSpeDef(Pokemon*);
u16 pokemonBiosGetSpeDefEffort(Pokemon*);
u16 pokemonBiosGetSpeDefRnd(Pokemon*);
u16 pokemonDataBiosGetBasisMaxHp(PokemonData*);
u16 pokemonDataBiosGetBasisNimbleness(PokemonData*);
u16 pokemonDataBiosGetBasisPhyAtk(PokemonData*);
u16 pokemonDataBiosGetBasisPhyDef(PokemonData*);
u16 pokemonDataBiosGetBasisSpeAtk(PokemonData*);
u16 pokemonDataBiosGetBasisSpeDef(PokemonData*);
u16 pokemonDataBiosGetGetWazaDataId(PokemonData*, u16);
u16 pokemonDataBiosGetGiveExp(PokemonData*);
u16 pokemonDataBiosGetGiveMaxHpEffort(PokemonData*);
u16 pokemonDataBiosGetGiveNimblenessEffort(PokemonData*);
u16 pokemonDataBiosGetGivePhyAtkEffort(PokemonData*);
u16 pokemonDataBiosGetGivePhyDefEffort(PokemonData*);
u16 pokemonDataBiosGetGiveSpeAtkEffort(PokemonData*);
u16 pokemonDataBiosGetGiveSpeDefEffort(PokemonData*);
u16 pokemonDataBiosGetHeight(PokemonData*);
u16 pokemonDataBiosGetInitFriend(PokemonData*);
u16 pokemonDataBiosGetItemDataId(PokemonData*, u16);
u16 pokemonDataBiosGetKowaza(PokemonData*, u16);
u16 pokemonDataBiosGetNumPokemon(PokemonData*);
u16 pokemonDataBiosGetNumZukan(PokemonData*);
u16 pokemonDataBiosGetSinkaBuff(PokemonData*, u16);
u16 pokemonDataBiosGetSinkaPokemonDataId(PokemonData*, u16);
u32 pokemonDataBiosGetVoice(PokemonData*);
u16 pokemonDataBiosGetWeight(PokemonData*);
u32 fightOutPokemonBiosGetKaigaraDamageValue(FightOutPokemon*);
u32 pokemonBiosGetCatchTrainerRnd(Pokemon*);
u32 pokemonBiosGetConditionAmari(Pokemon*);
s32 pokemonBiosGetDp(Pokemon*);
u32 pokemonBiosGetExp(Pokemon*);
u32 pokemonBiosGetPoolExp(Pokemon*);
u32 pokemonBiosGetRnd(Pokemon*);
u32 pokemonDataBiosGetDoc(PokemonData*);
u32 pokemonDataBiosGetMitaFlag(PokemonData*);
u32 pokemonDataBiosGetPkxDataId(PokemonData*);
u32 pokemonDataBiosGetPokebodyId(PokemonData*, u16);
u32 pokemonDataBiosGetStatusFaceMenuSpriteId(PokemonData*, u16);
u32 pokemonDataBiosGetTukamaetaFlag(PokemonData*);
u32 pokemonDataBiosGetTypeName(PokemonData*);
u8 fightOutPokemonBiosGetAbicntAverage(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntAvoid(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntNimbleness(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntPhyAtk(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntPhyDef(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntSpeAtk(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntSpeDef(FightOutPokemon*);
u8 fightOutPokemonBiosGetChouhatsuNoAttackFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetDoClearbodyFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetDoIkakuFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetDoTraceFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetFightActionFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetHirumuNoAttackFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetHuuinNoAttackFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetIchamonNoAttackFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetIrekaetaFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetItemKoraetaFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetItemNigeruFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetKanashibariNoAttackFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetKizetuFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetKonranMyselfAttackFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetMahiNoAttackFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetMeroMeroNoAttackFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetNamakeFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetNoPressureFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetOutWazaKoukanaiFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetPassPpdecFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetReceivesWazaHiraishinFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetSuccessCnt(FightOutPokemon*);
u8 fightOutPokemonBiosGetTameWazaFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetVanishoffFlag(FightOutPokemon*);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightPokemonBiosGetCatchEntryFlag(FightPokemon*);
u8 fightPokemonBiosGetDarkOutFlag(FightPokemon*);
u8 fightPokemonBiosGetHokakuFlag(FightPokemon*);
u8 fightPokemonBiosGetLevelUpFlag(FightPokemon*);
u8 pokemonBiosGetAmariRibbon(Pokemon*);
u8 pokemonBiosGetBeautiful(Pokemon*);
u8 pokemonBiosGetBeautifulMedal(Pokemon*);
u8 pokemonBiosGetBromideRibbon(Pokemon*);
u8 pokemonBiosGetCatchBallId(Pokemon*);
u8 pokemonBiosGetCatchLevel(Pokemon*);
u8 pokemonBiosGetCatchTrainerSex(Pokemon*);
u8 pokemonBiosGetChampRibbon(Pokemon*);
u8 pokemonBiosGetClever(Pokemon*);
u8 pokemonBiosGetCleverMedal(Pokemon*);
u8 pokemonBiosGetCountryRibbon(Pokemon*);
u8 pokemonBiosGetCute(Pokemon*);
u8 pokemonBiosGetCuteMedal(Pokemon*);
u8 pokemonBiosGetDarkFlag(Pokemon*);
u8 pokemonBiosGetEarthRibbon(Pokemon*);
u8 pokemonBiosGetFlagAmari(Pokemon*);
u8 pokemonBiosGetFur(Pokemon*);
u8 pokemonBiosGetFuseiFlag(Pokemon*);
u8 pokemonBiosGetGanbaRibbon(Pokemon*);
u8 pokemonBiosGetLandRibbon(Pokemon*);
u8 pokemonBiosGetLevel(Pokemon*);
u8 pokemonBiosGetMailId(Pokemon*);
u8 pokemonBiosGetMarineRibbon(Pokemon*);
u8 pokemonBiosGetNationalRibbon(Pokemon*);
u8 pokemonBiosGetPcboxMark(Pokemon*);
u8 pokemonBiosGetPokemonWazaPp(Pokemon*, u16);
u8 pokemonBiosGetPokemonWazaPpCount(Pokemon*, u16);
u8 pokemonBiosGetPokerus(Pokemon*);
u8 pokemonBiosGetSkyRibbon(Pokemon*);
u8 pokemonBiosGetStrong(Pokemon*);
u8 pokemonBiosGetStrongMedal(Pokemon*);
u8 pokemonBiosGetStyle(Pokemon*);
u8 pokemonBiosGetStyleMedal(Pokemon*);
u8 pokemonBiosGetTamagoFlag(Pokemon*);
u8 pokemonBiosGetTokuseiFlag(Pokemon*);
u8 pokemonBiosGetVictoryRibbon(Pokemon*);
u8 pokemonBiosGetWinningRibbon(Pokemon*);
u8 pokemonBiosGetWorldRibbon(Pokemon*);
u8 pokemonDataBiosGetColor(PokemonData*, u16);
u8 pokemonDataBiosGetGet(PokemonData*);
u8 pokemonDataBiosGetGetWazaLevel(PokemonData*, u16);
u8 pokemonDataBiosGetGrowDataId(PokemonData*);
u8 pokemonDataBiosGetSexRatio(PokemonData*);
u8 pokemonDataBiosGetSinkaKind(PokemonData*, u16);
u8 pokemonDataBiosGetTokuseiDataId(PokemonData*, u16);
u8 pokemonDataBiosGetWazaMcn(PokemonData*, u16);
u8 pokemonDataBiosGetZokuseiDataId(PokemonData*, u16);
void fightOutPokemonBiosSetAbicntAverage(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntAvoid(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntNimbleness(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntPhyAtk(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntPhyDef(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntSpeAtk(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntSpeDef(FightOutPokemon*, u8);
void fightOutPokemonBiosSetChouhatsuNoAttackFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetDamageAtkTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetDamageAtkValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetDamageSpeTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetDamageSpeValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetDoClearbodyFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetDoIkakuFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetDoTraceFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetFightActionFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetFightPokemonPtr(FightOutPokemon*, void*);
void fightOutPokemonBiosSetFightoutTurnCount(FightOutPokemon*, u16);
void fightOutPokemonBiosSetGamanDamageTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetGamanDamageValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetHirumuNoAttackFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetHitWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetHitWazaZokuseiDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetHuuinNoAttackFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetIchamonNoAttackFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetIrekaeTargetEntryId(FightOutPokemon*, s16);
void fightOutPokemonBiosSetIrekaetaFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetItemKoraetaFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetItemNigeruFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetKaigaraDamageValue(FightOutPokemon*, u32);
void fightOutPokemonBiosSetKanashibariNoAttackFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetKizetuFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetKonranMyselfAttackFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetLastReceiveWazaTargetDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetLastSelectWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetLastUseWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetMahiNoAttackFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetMeetEnemyFightPokemonEntryId(FightOutPokemon*, u8, s16);
void fightOutPokemonBiosSetMeroMeroNoAttackFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetMotoFightPokemonPtr(FightOutPokemon*, void*);
void fightOutPokemonBiosSetMyselfDamageAtkTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetMyselfDamageAtkValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetMyselfDamageSpeTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetMyselfDamageSpeValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetNamakeFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetNoPressureFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetOumuWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetOutWazaKoukanaiFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetPassPpdecFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetReceivesWazaHiraishinFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetSequencePtr(FightOutPokemon*, void*);
void fightOutPokemonBiosSetSketchWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetStockItemDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetSuccessCnt(FightOutPokemon*, u8);
void fightOutPokemonBiosSetTameWazaFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetTokuseiDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetUsedItemDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetVanishoffFlag(FightOutPokemon*, bool);
void fightOutPokemonBiosSetZokuseiDataId(FightOutPokemon*, u8, u16);
void fightPokemonBiosSetCatchEntryFlag(FightPokemon*, bool);
void fightPokemonBiosSetDarkOutFlag(FightPokemon*, bool);
void fightPokemonBiosSetEntryId(FightPokemon*, s16);
void fightPokemonBiosSetHokakuFlag(FightPokemon*, bool);
void fightPokemonBiosSetLevelUpFlag(FightPokemon*, bool);
void fightPokemonBiosSetMotoPokemonPtr(FightPokemon*, void*);
void pokemonBiosSetAmari(Pokemon*, u16);
void pokemonBiosSetAmariRibbon(Pokemon*, u8);
void pokemonBiosSetBeautiful(Pokemon*, u8);
void pokemonBiosSetBeautifulMedal(Pokemon*, u8);
void pokemonBiosSetBromideRibbon(Pokemon*, bool);
void pokemonBiosSetCatchBallId(Pokemon*, u8);
void pokemonBiosSetCatchFloorId(Pokemon*, u16);
void pokemonBiosSetCatchLevel(Pokemon*, u8);
void pokemonBiosSetCatchTrainerNamePtr(Pokemon*, void*);
void pokemonBiosSetCatchTrainerRnd(Pokemon*, u32);
void pokemonBiosSetCatchTrainerSex(Pokemon*, u8);
void pokemonBiosSetChampRibbon(Pokemon*, bool);
void pokemonBiosSetClever(Pokemon*, u8);
void pokemonBiosSetCleverMedal(Pokemon*, u8);
void pokemonBiosSetConditionAmari(Pokemon*, u32);
void pokemonBiosSetCountryRibbon(Pokemon*, bool);
void pokemonBiosSetCute(Pokemon*, u8);
void pokemonBiosSetCuteMedal(Pokemon*, u8);
void pokemonBiosSetDarkpokemonDataId(Pokemon*, u16);
void pokemonBiosSetDp(Pokemon*, s32);
void pokemonBiosSetEarthRibbon(Pokemon*, bool);
void pokemonBiosSetExp(Pokemon*, u32);
void pokemonBiosSetFightTrainerPokemonDataId(Pokemon*, u16);
void pokemonBiosSetFlagAmari(Pokemon*, u8);
void pokemonBiosSetFriend(Pokemon*, u16);
void pokemonBiosSetFur(Pokemon*, u8);
void pokemonBiosSetFuseiFlag(Pokemon*, bool);
void pokemonBiosSetGanbaRibbon(Pokemon*, bool);
void pokemonBiosSetHp(Pokemon*, u16);
void pokemonBiosSetItemDataId(Pokemon*, u16);
void pokemonBiosSetLandRibbon(Pokemon*, bool);
void pokemonBiosSetLevel(Pokemon*, u8);
void pokemonBiosSetMailId(Pokemon*, u8);
void pokemonBiosSetMarineRibbon(Pokemon*, bool);
void pokemonBiosSetMaxHp(Pokemon*, u16);
void pokemonBiosSetMaxHpEffort(Pokemon*, u16);
void pokemonBiosSetMaxHpRnd(Pokemon*, u16);
void pokemonBiosSetNationalRibbon(Pokemon*, bool);
void pokemonBiosSetNicknameOrgPtr(Pokemon*, void*);
void pokemonBiosSetNicknamePtr(Pokemon*, void*);
void pokemonBiosSetNimbleness(Pokemon*, u16);
void pokemonBiosSetNimblenessEffort(Pokemon*, u16);
void pokemonBiosSetNimblenessRnd(Pokemon*, u16);
void pokemonBiosSetPara1Amari(Pokemon*, u16);
void pokemonBiosSetPcboxMark(Pokemon*, u8);
void pokemonBiosSetPhyAtk(Pokemon*, u16);
void pokemonBiosSetPhyAtkEffort(Pokemon*, u16);
void pokemonBiosSetPhyAtkRnd(Pokemon*, u16);
void pokemonBiosSetPhyDef(Pokemon*, u16);
void pokemonBiosSetPhyDefEffort(Pokemon*, u16);
void pokemonBiosSetPhyDefRnd(Pokemon*, u16);
void pokemonBiosSetPokemonDataId(Pokemon*, u16);
void pokemonBiosSetPokemonWazaDataId(Pokemon*, u16, u16);
void pokemonBiosSetPokemonWazaPp(Pokemon*, u16, u8);
void pokemonBiosSetPokemonWazaPpCount(Pokemon*, u16, u8);
void pokemonBiosSetPokerus(Pokemon*, u8);
void pokemonBiosSetPoolExp(Pokemon*, u32);
void pokemonBiosSetPoolFriend(Pokemon*, u16);
void pokemonBiosSetRnd(Pokemon*, u32);
void pokemonBiosSetSkyRibbon(Pokemon*, bool);
void pokemonBiosSetSpeAtk(Pokemon*, u16);
void pokemonBiosSetSpeAtkEffort(Pokemon*, u16);
void pokemonBiosSetSpeAtkRnd(Pokemon*, u16);
void pokemonBiosSetSpeDef(Pokemon*, u16);
void pokemonBiosSetSpeDefEffort(Pokemon*, u16);
void pokemonBiosSetSpeDefRnd(Pokemon*, u16);
void pokemonBiosSetStrong(Pokemon*, u8);
void pokemonBiosSetStrongMedal(Pokemon*, u8);
void pokemonBiosSetStyle(Pokemon*, u8);
void pokemonBiosSetStyleMedal(Pokemon*, u8);
void pokemonBiosSetTamagoFlag(Pokemon*, bool);
void pokemonBiosSetTokuseiFlag(Pokemon*, bool);
void pokemonBiosSetVictoryRibbon(Pokemon*, bool);
void pokemonBiosSetWinningRibbon(Pokemon*, bool);
void pokemonBiosSetWorldRibbon(Pokemon*, bool);
void pokemonDataBiosSetBasisMaxHp(PokemonData*, u16);
void pokemonDataBiosSetBasisNimbleness(PokemonData*, u16);
void pokemonDataBiosSetBasisPhyAtk(PokemonData*, u16);
void pokemonDataBiosSetBasisPhyDef(PokemonData*, u16);
void pokemonDataBiosSetBasisSpeAtk(PokemonData*, u16);
void pokemonDataBiosSetBasisSpeDef(PokemonData*, u16);
void pokemonDataBiosSetColor(PokemonData*, u16, u8);
void pokemonDataBiosSetDoc(PokemonData*, u32);
void pokemonDataBiosSetGet(PokemonData*, u8);
void pokemonDataBiosSetGetWazaDataId(PokemonData*, u16, u16);
void pokemonDataBiosSetGetWazaLevel(PokemonData*, u16, u8);
void pokemonDataBiosSetGiveExp(PokemonData*, u16);
void pokemonDataBiosSetGiveMaxHpEffort(PokemonData*, u16);
void pokemonDataBiosSetGiveNimblenessEffort(PokemonData*, u16);
void pokemonDataBiosSetGivePhyAtkEffort(PokemonData*, u16);
void pokemonDataBiosSetGivePhyDefEffort(PokemonData*, u16);
void pokemonDataBiosSetGiveSpeAtkEffort(PokemonData*, u16);
void pokemonDataBiosSetGiveSpeDefEffort(PokemonData*, u16);
void pokemonDataBiosSetGrowDataId(PokemonData*, u8);
void pokemonDataBiosSetHeight(PokemonData*, u16);
void pokemonDataBiosSetInitFriend(PokemonData*, u16);
void pokemonDataBiosSetItemDataId(PokemonData*, u16, u16);
void pokemonDataBiosSetKowaza(PokemonData*, u16, u16);
void pokemonDataBiosSetMitaFlag(PokemonData*, u32);
void pokemonDataBiosSetName(PokemonData*, const char*);
void pokemonDataBiosSetNumPokemon(PokemonData*, u16);
void pokemonDataBiosSetNumZukan(PokemonData*, u16);
void pokemonDataBiosSetPkxDataId(PokemonData*, u32);
void pokemonDataBiosSetPokebodyId(PokemonData*, u16, u32);
void pokemonDataBiosSetSexRatio(PokemonData*, u8);
void pokemonDataBiosSetSinkaBuff(PokemonData*, u16, u16);
void pokemonDataBiosSetSinkaKind(PokemonData*, u16, u8);
void pokemonDataBiosSetSinkaPokemonDataId(PokemonData*, u16, u16);
void pokemonDataBiosSetStatusFaceMenuSpriteId(PokemonData*, u16, u16);
void pokemonDataBiosSetTokuseiDataId(PokemonData*, u16, u8);
void pokemonDataBiosSetTukamaetaFlag(PokemonData*, u32);
void pokemonDataBiosSetTypeName(PokemonData*, u32);
void pokemonDataBiosSetVoice(PokemonData*, u16);
void pokemonDataBiosSetWazaMcn(PokemonData*, u16, bool);
void pokemonDataBiosSetWeight(PokemonData*, u16);
void pokemonDataBiosSetZokuseiDataId(PokemonData*, u16, u8);
void* fightOutPokemonBiosGetFightActionBuffPtr(FightOutPokemon*);
void* fightOutPokemonBiosGetFightItemPtr(FightOutPokemon*);
void* fightOutPokemonBiosGetFightOutPokemonEnemyPtr(FightOutPokemon*, u16);
void* fightOutPokemonBiosGetFightPokemonHensinBuffPtr(FightOutPokemon*);
void* fightOutPokemonBiosGetFightPokemonPtr(FightOutPokemon*);
void* fightOutPokemonBiosGetFightWazaPtr(FightOutPokemon*);
void* fightOutPokemonBiosGetFightoutJoutaiPtr(FightOutPokemon*, u16);
void* fightOutPokemonBiosGetKeepFightWazaPtr(FightOutPokemon*);
void* fightOutPokemonBiosGetMotoFightPokemonPtr(FightOutPokemon*);
void* fightOutPokemonBiosGetSequencePtr(FightOutPokemon*);
void* fightOutPokemonBiosGetWazaMenuCurPtr(FightOutPokemon*);
void* fightPokemonBiosGetFightJoutaiPtr(FightPokemon*, u16);
void* fightPokemonBiosGetMotoPokemonPtr(FightPokemon*);
void* fightPokemonBiosGetPokemonBuffPtr(FightPokemon*);
void* pokemonBiosGetAttest(Pokemon*);
void* pokemonBiosGetCatchTrainerNamePtr(Pokemon*);
void* pokemonBiosGetNicknameOrgPtr(Pokemon*);
void* pokemonBiosGetNicknamePtr(Pokemon*);
void* pokemonDataBiosGetName(PokemonData*);


// this unit
u16 fightOutPokemon_GetKanseiSndId(FightOutPokemon*);
s32 pokemonGetWazaCount(Pokemon*);
void pokemonWazaForget(Pokemon*, u32);
void pokemonWazaCopy(Pokemon*, u16, u16);
void pokemonPlayVoice(Pokemon*);
u8 pokemonGetDarkPokemonCallKakuritu(Pokemon*);
u8 pokemonGetDarkPokemonHyperJoutaiKakuritu(Pokemon*);
u8 pokemonGetDarkPokemonLevel(Pokemon*);
void pokemonAddDpFormPokemonDpFilterId(Pokemon*, u16, u16);
void pokemonAddDp(Pokemon*, f32);
void pokemonSetDp(Pokemon*, f32);
f32 pokemonGetDp(Pokemon*);
u8 pokemonIsDarkPokemon(Pokemon*);
void pokemonSetDarkPokemonStatus(Pokemon*, u16);
void pokemonToMenuPokemonStatus(Pokemon*, FightPokemon*, MenuPokemonStatus*, u8);
void pokemonToMenuPokemonStatusSubBar(Pokemon*, MenuPokemonStatus*);
void pokemonToMenuWazaStatus(Pokemon*, MenuWazaStatus*);
u8 pokemonCheckSetMonohiroi(Pokemon*);
void pokemonAllKaihuku(Pokemon*);
void pokemonGetMezamerupower(Pokemon*, u16*, u16*);
bool pokemonDataCheckValid(Pokemon*, u16);
u32 pokemonGetNowLevelToExp(Pokemon*);
s32 pokemonGetTasteLike(Pokemon*, u32);
u32 pokemonGetJoutaiMsgId(Pokemon*);
u16 pokemonGetJoutaiMenuSpriteId(Pokemon*);
u32 pokemonGetJoutaiDataId(Pokemon*);
u8 pokemonIsHpMantan(Pokemon*);
void pokemonCopyJoutaiDataId(Pokemon*, Pokemon*, u16);
void pokemonSetKaisuuJoutaiDataId(Pokemon*, u16, u32);
void pokemonSetNowKaisuuJoutaiDataId(Pokemon*, u16, u32);
s32 pokemonGetNowKaisuuJoutaiDataId(Pokemon*, u16);
s32 pokemonGetKaisuuJoutaiDataId(Pokemon*, u16);
void pokemonSetCountAsJoutaiDataId(Pokemon*, u16, u32);
s32 pokemonGetCountAsJoutaiDataId(Pokemon*, u16);
void pokemonWriteJoutaiDataId(Pokemon*, u16);
u8 pokemonCheckWriteJoutaiDataId(Pokemon*, u16);
bool pokemonIsJoutaiDataId(Pokemon*, u16);
void pokemonInitJoutaiDataId(Pokemon*, u16);
u8 pokemonCheckInfectPokerus(Pokemon*, u8);
void pokemonReplace(Pokemon*, Pokemon*);
u32 pokemonCreateSequence(FightPokemon*);
void pokemonSetSequenceStatus(Pokemon*, u32);
u8 pokemonGetFightPokemonDeoxysSel(FightPokemon*);
u8 pokemonGetDeoxysSel(u8);
u8 pokemonGetAnnonKatati(u32);
void pokemonGetFriendFormPokemonFriendFilterId(Pokemon*, u16, u16);
u8 pokemonCheckCanGetFriend(Pokemon*, u16);
void pokemonGetEffortFromPokemon(Pokemon*, u16, u8, u16);
u32 pokemonGetLevelToExp(Pokemon*, u8);
s32 pokemonGetNowHpPercentage(Pokemon*);
u16 pokemonGetNowHpWaruValue(Pokemon*, u16, u16);
u16 pokemonGetMaxHpWaruValue(Pokemon*, u16);
u8 pokemonIsNokoriHpFollowing(Pokemon*, u16);
u8 pokemonIsJoutaiKaragenki(Pokemon*);
bool pokemonIsJoutaiNormal(Pokemon*);
u16 pokemonGetSoubiItemBuff(Pokemon*);
u16 pokemonGetSoubiItemSoubiDataId(Pokemon*);
u16 pokemonGetSoubiItemDataId(Pokemon*);
u16 pokemonDoItemSoubi(Pokemon*, u16, u8);
u8 pokemonGetSex(Pokemon*);
s8 pokemonCheckSexKotei(Pokemon*);
void pokemonSetOnDarkPokemonFlag(Pokemon*, u8);
void pokemonSetOnZukanFlag(Pokemon*, u8);
bool pokemonCheckFightOut(Pokemon*);
u8 pokemonGetOboeWazaDataBanme(Pokemon*, u8);
s8 pokemonOboeWaza(Pokemon*, u8, u8, u8*);
u16 pokemonGetOboeWazaDataId(Pokemon*, u8, u8*);
s8 pokemonSetWazaStatus(Pokemon*, u16, u8);
s8 pokemonSearchWazaDataId(Pokemon*, u16);
void pokemonWazaReplace(Pokemon*, u16, u16);
bool pokemonWazaCheckValid(Pokemon*, u16);
void pokemonWazaCreate(Pokemon*, u16, u16);
u8 pokemonWazaGetMaxPP(Pokemon*, u16);
u32 pokemonWazaGetZokusei(Pokemon*, u16);
void pokemonSetCatchStatus(Pokemon*, u32, u8, u32, u8, u32, char16*);
bool pokemonCheckValid(Pokemon*);
void pokemonCreate(Pokemon*, u16, u8, Attest*);
u32 pokemonCreateRndFit(Pokemon*, s8, s8, s8, u32);
u32 pokemonCreateRnd(void);
u16 pokemonGetTokuseiDataId(Pokemon*);
void pokemonSetTokuseiFlag(Pokemon*, u32);
void pokemonInitAry(Pokemon*, u16);
void pokemonInit(Pokemon*);
void pokemonInitDarkPokemon(Pokemon*);
void pokemonInitJoutai(Pokemon*);
void pokemonWazaInitAry(Pokemon*, u16);
void pokemonWazaInit(Pokemon*, u16);
u32 pokemonCheckRare(Pokemon*);
void pokemonGrowBasisStatus(Pokemon*, u32);
void pokemonResetBasisStatus(Pokemon*);
void pokemonSetStatus(void*, u16, u16, u16, u32);
u32 pokemonGetStatus(void*, u16, u16, u16);
u32 pokemonAdjustValueBySeikaku(u32, u16, u32);
u8 pokemonGetSeikakuAsRnd(u32);
u16 pokemonCreateBasisStatus(u16, u8, u16, u8, s32);
u8 pokemonGetExpToLevel(u8, u32);
int pokemonCheckRareRnd(u32, u32);
}

static u8 _pokemonGetSexSub(Pokemon*, u32);
static void _pokemonWazaCopy(Pokemon*, u16, u16);
static u8 _pokemonGetSeikaku(Pokemon*);
static u8 _pokemonGetHinsi(Pokemon*);
static void _pokemonSetLevelBasisStatus(Pokemon*, u8);
static u16 _pokemonGetLevelOneStatus(Pokemon*, u8, u16, u16, u16, u16, long);
static u8 _pokemonGetNowExpToLevel(Pokemon*);
static u32 _pokemonGetLevelToExp(u8, u8);
static int _pokemonCheckRare(u32, u32);
static int _pokemonCheckRare(u32 a, u32 b)
{
    int x = 8 > (a >> 0x10 ^ a & 0xFFFF ^ b >> 0x10 ^ b & 0xFFFF);
    int y = x ? -1 : 0;
    return -y;
}

extern "C" {

int pokemonCheckRareRnd(u32 a, u32 b)
{
    return _pokemonCheckRare(a, b);
}

}

static u32 _pokemonGetLevelToExp(u8 growDataId, u8 level)
{
    PokemonGrowDataBios* ptr = pokemonGrowDataBiosGetPtr(growDataId);
    if (ptr == 0) {
        return 0;
    }
    return pokemonGrowDataBiosGetExp(ptr, level);
}

extern "C" {

u8 pokemonGetExpToLevel(u8 growDataId, u32 exp)
{
    s32 level = 0;

    PokemonGrowDataBios* ptr = pokemonGrowDataBiosGetPtr(growDataId);
    if (ptr == 0)
        return level;

    for (level = 1; level < 101; level++) {
        if (pokemonGrowDataBiosGetExp(ptr, level) > exp)
            break;
    }

    return (level - 1);
}

}

static u8 _pokemonGetNowExpToLevel(Pokemon* pokemon)
{
    u8 growDataId;
    u32 exp;

    growDataId = pokemonDB_GetGrowDataId(pokemon_GetPokemonDataId(pokemon));
    exp = pokemon_GetExp(pokemon);
    return pokemonGetExpToLevel(growDataId, exp);
}

extern "C" {

u16 pokemonCreateBasisStatus(u16 a, u8 b, u16 c, u8 d, s32 e)
{
    return e + (s32)((d & 0xff) * ((b & 0xff) + (a & 0xffff) * 2 + (c >> 2 & 0x3fff))) / 100 & 0xffff;
}

}

static u16 _pokemonGetLevelOneStatus(Pokemon* pokemon, u8 level, u16 kind, u16 basisKind, u16 rndKind, u16 effortKind, long add)
{
    u16 basis;
    u16 rnd;
    u32 seikaku;

    basis = pokemon_GetPokemonDataId(pokemon);
    seikaku = pokemon_GetSeikaku(pokemon);
    basis = pokemonGetStatus(0, basis, basisKind, 0);
    rnd = pokemonGetStatus(pokemon, 0, rndKind, 0);
    u16 effort = pokemonGetStatus(pokemon, 0, effortKind, 0);
    u32 value = pokemonCreateBasisStatus(basis, rnd, effort, level, add);
    value = pokemonAdjustValueBySeikaku(seikaku, kind, value);
    pokemonSetStatus(pokemon, 0, kind, 0, value);
    return value;
}

static void _pokemonSetLevelBasisStatus(Pokemon* a, u8 b)
{
    u16 sVar1;
    u16 sVar2;
    u16 sVar3;
    u16 sVar4;
    u16 sVar5;

    sVar2 = pokemon_GetPokemonDataId(a);
    sVar3 = pokemon_GetMaxHp(a);
    pokemon_SetLevel(a, b);
    if (sVar2 == 0x12f) {
        sVar4 = 1;
        pokemon_SetMaxHp(a, 1);
    } else {
        sVar4 = _pokemonGetLevelOneStatus(a, b, 0x87, 3, 0x93, 0x8d, (b & 0xff) + 10);
    }
    _pokemonGetLevelOneStatus(a, b, 0x88, 4, 0x94, 0x8e, 5);
    _pokemonGetLevelOneStatus(a, b, 0x89, 5, 0x95, 0x8f, 5);
    _pokemonGetLevelOneStatus(a, b, 0x8c, 8, 0x98, 0x92, 5);
    _pokemonGetLevelOneStatus(a, b, 0x8a, 6, 0x96, 0x90, 5);
    _pokemonGetLevelOneStatus(a, b, 0x8b, 7, 0x97, 0x91, 5);
    sVar5 = pokemon_GetHp(a);
    if ((sVar5 != 0) || (sVar3 == 0)) {
        sVar1 = 1;
        if (sVar2 != 0x12f) {
            sVar1 = sVar5 + (sVar4 - sVar3);
        }
        pokemon_SetHp(a, sVar1);
    }
}

static u8 _pokemonGetHinsi(Pokemon* pokemon)
{
    return pokemon_GetHp(pokemon) == 0;
}

extern "C" {

u8 pokemonGetSeikakuAsRnd(u32 rnd)
{
    return rnd % 25;
}

}

static u8 _pokemonGetSeikaku(Pokemon* pokemon)
{
    return pokemonGetSeikakuAsRnd(pokemon_GetRnd(pokemon));
}

extern "C" {

u32 pokemonAdjustValueBySeikaku(u32 seikaku, u16 kind, u32 value)
{
    PokemonSeikakuDataBios* seikakuPtr;
    PokemonSeikakuRateBios* ratePtr;
    u32 rateId;
    s32 result;
    u32 stat;
    u8 kake;
    u8 waru;

    seikakuPtr = pokemonSeikakuDataBiosGetPtr(seikaku);

    if (seikakuPtr == 0)
        return value;

    stat = kind;

    switch (stat) {
    case 0x88:
        rateId = pokemonSeikakuDataBiosGetPhyAtkRateDataId(seikakuPtr);
        break;
    case 0x89:
        rateId = pokemonSeikakuDataBiosGetPhyDefRateDataId(seikakuPtr);
        break;
    case 0x8A:
        rateId = pokemonSeikakuDataBiosGetSpeAtkRateDataId(seikakuPtr);
        break;
    case 0x8B:
        rateId = pokemonSeikakuDataBiosGetSpeDefRateDataId(seikakuPtr);
        break;
    case 0x8C:
        rateId = pokemonSeikakuDataBiosGetNimblenessRateDataId(seikakuPtr);
        break;
    default:
        return value;
    }

    ratePtr = pokemonSeikakuRateDataBiosGetPtr(rateId);
    if (ratePtr == 0)
        return 0;

    kake = pokemonSeikakuRateDataBiosGetKake(ratePtr);
    waru = pokemonSeikakuRateDataBiosGetWaru(ratePtr);

    result = value * kake;

    if (waru != 0)
        result = result / waru;

    return result;
}

u32 pokemonGetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index)
{
    if (kind == 0 || kind >= 0x124) {
        return 0;
    }
    if (kind < 0x6D) {
        ptr = pokemonDataBiosGetPtr(pokemonDataId);
        if (ptr == 0) {
            return 0;
        }
    } else if (ptr == 0) {
        return 0;
    }
    switch (kind) {
	case 0x1:
		return (u32)pokemonDataBiosGetName((PokemonData*)ptr);
	case 0x3:
		return pokemonDataBiosGetBasisMaxHp((PokemonData*)ptr);
	case 0x4:
		return pokemonDataBiosGetBasisPhyAtk((PokemonData*)ptr);
	case 0x5:
		return pokemonDataBiosGetBasisPhyDef((PokemonData*)ptr);
	case 0x6:
		return pokemonDataBiosGetBasisSpeAtk((PokemonData*)ptr);
	case 0x7:
		return pokemonDataBiosGetBasisSpeDef((PokemonData*)ptr);
	case 0x8:
		return pokemonDataBiosGetBasisNimbleness((PokemonData*)ptr);
	case 0xa:
		return pokemonDataBiosGetGiveMaxHpEffort((PokemonData*)ptr);
	case 0xb:
		return pokemonDataBiosGetGivePhyAtkEffort((PokemonData*)ptr);
	case 0xc:
		return pokemonDataBiosGetGivePhyDefEffort((PokemonData*)ptr);
	case 0xd:
		return pokemonDataBiosGetGiveSpeAtkEffort((PokemonData*)ptr);
	case 0xe:
		return pokemonDataBiosGetGiveSpeDefEffort((PokemonData*)ptr);
	case 0xf:
		return pokemonDataBiosGetGiveNimblenessEffort((PokemonData*)ptr);
	case 0x10:
		return pokemonDataBiosGetGiveExp((PokemonData*)ptr);
	case 0x11:
		return pokemonDataBiosGetGrowDataId((PokemonData*)ptr);
	case 0x12:
		return pokemonDataBiosGetGet((PokemonData*)ptr);
	case 0x13:
		return pokemonDataBiosGetSexRatio((PokemonData*)ptr);
	case 0x14:
		return pokemonDataBiosGetInitFriend((PokemonData*)ptr);
	case 0x15:
		return pokemonDataBiosGetItemDataId((PokemonData*)ptr, index);
	case 0x16:
		return pokemonDataBiosGetZokuseiDataId((PokemonData*)ptr, index);
	case 0x17:
		return pokemonDataBiosGetTokuseiDataId((PokemonData*)ptr, index);
	case 0x19:
		return pokemonDataBiosGetSinkaKind((PokemonData*)ptr, index);
	case 0x1a:
		return pokemonDataBiosGetSinkaBuff((PokemonData*)ptr, index);
	case 0x1b:
		return pokemonDataBiosGetSinkaPokemonDataId((PokemonData*)ptr, index);
	case 0x1d:
		return pokemonDataBiosGetGetWazaLevel((PokemonData*)ptr, index);
	case 0x1e:
		return pokemonDataBiosGetGetWazaDataId((PokemonData*)ptr, index);
	case 0x20:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 0);
	case 0x21:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 1);
	case 0x22:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 2);
	case 0x23:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 3);
	case 0x24:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 4);
	case 0x25:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 5);
	case 0x26:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 6);
	case 0x27:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 7);
	case 0x28:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 8);
	case 0x29:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 9);
	case 0x2a:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 10);
	case 0x2b:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 11);
	case 0x2c:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 12);
	case 0x2d:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 13);
	case 0x2e:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 14);
	case 0x2f:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 15);
	case 0x30:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 16);
	case 0x31:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 17);
	case 0x32:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 18);
	case 0x33:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 19);
	case 0x34:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 20);
	case 0x35:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 21);
	case 0x36:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 22);
	case 0x37:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 23);
	case 0x38:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 24);
	case 0x39:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 26);
	case 0x3a:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 27);
	case 0x3b:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 28);
	case 0x3c:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 29);
	case 0x3d:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 30);
	case 0x3e:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 31);
	case 0x3f:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 32);
	case 0x40:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 33);
	case 0x41:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 34);
	case 0x42:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 35);
	case 0x43:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 36);
	case 0x44:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 37);
	case 0x45:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 38);
	case 0x46:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 39);
	case 0x47:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 40);
	case 0x48:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 41);
	case 0x49:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 42);
	case 0x4a:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 43);
	case 0x4b:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 44);
	case 0x4c:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 45);
	case 0x4d:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 46);
	case 0x4e:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 47);
	case 0x4f:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 48);
	case 0x50:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 49);
	case 0x51:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 50);
	case 0x52:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 51);
	case 0x53:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 52);
	case 0x54:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 53);
	case 0x55:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 54);
	case 0x56:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 55);
	case 0x57:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 56);
	case 0x58:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 57);
	case 0x59:
		return pokemonDataBiosGetWazaMcn((PokemonData*)ptr, 58);
	case 0x5a:
		return pokemonDataBiosGetPokebodyId((PokemonData*)ptr, index);
	case 0x5b:
		return pokemonDataBiosGetStatusFaceMenuSpriteId((PokemonData*)ptr, index);
	case 0x5c:
		return pokemonDataBiosGetColor((PokemonData*)ptr, index);
	case 0x5d:
		return pokemonDataBiosGetTypeName((PokemonData*)ptr);
	case 0x5e:
		return pokemonDataBiosGetHeight((PokemonData*)ptr);
	case 0x5f:
		return pokemonDataBiosGetWeight((PokemonData*)ptr);
	case 0x60:
		return pokemonDataBiosGetDoc((PokemonData*)ptr);
	case 0x61:
		return (u16)pokemonDataBiosGetVoice((PokemonData*)ptr);
	case 0x62:
		return pokemonDataBiosGetMitaFlag((PokemonData*)ptr);
	case 0x63:
		return pokemonDataBiosGetTukamaetaFlag((PokemonData*)ptr);
	case 0x64:
		return pokemonDataBiosGetNumZukan((PokemonData*)ptr);
	case 0x65:
		return pokemonDataBiosGetNumPokemon((PokemonData*)ptr);
	case 0x66:
		return pokemonDataBiosGetPkxDataId((PokemonData*)ptr);
	case 0x68:
		return pokemonDataBiosGetKowaza((PokemonData*)ptr, index);
	case 0x69:
	case 0x6a:
	case 0x6b:
	case 0x6c:
	case 0x6e:
		return pokemonBiosGetPokemonDataId((Pokemon*)ptr);
	case 0x6f:
		return pokemonBiosGetRnd((Pokemon*)ptr);
	case 0x70:
		return (u32)pokemonBiosGetAttest((Pokemon*)ptr);
	case 0x71:
		return pokemonBiosGetCatchFloorId((Pokemon*)ptr);
	case 0x72:
		return pokemonBiosGetCatchLevel((Pokemon*)ptr);
	case 0x73:
		return pokemonBiosGetCatchBallId((Pokemon*)ptr);
	case 0x74:
		return pokemonBiosGetCatchTrainerSex((Pokemon*)ptr);
	case 0x75:
		return pokemonBiosGetCatchTrainerRnd((Pokemon*)ptr);
	case 0x76:
		return (u32)pokemonBiosGetCatchTrainerNamePtr((Pokemon*)ptr);
	case 0x77:
		return (u32)pokemonBiosGetNicknamePtr((Pokemon*)ptr);
	case 0x78:
		return (u32)pokemonBiosGetNicknameOrgPtr((Pokemon*)ptr);
	case 0x79:
		return pokemonBiosGetExp((Pokemon*)ptr);
	case 0x7a:
		return pokemonBiosGetLevel((Pokemon*)ptr);
	case 0x7b:
		return _pokemonGetHinsi((Pokemon*)ptr);
	case 0x7c:
		return 0;
	case 0x7d:
		return pokemonBiosGetConditionAmari((Pokemon*)ptr);
	case 0x7f:
		return pokemonBiosGetPokemonWazaDataId((Pokemon*)ptr, index);
	case 0x80:
		return pokemonBiosGetPokemonWazaPp((Pokemon*)ptr, index);
	case 0x81:
		return pokemonBiosGetPokemonWazaPpCount((Pokemon*)ptr, index);
	case 0x82:
		return pokemonBiosGetItemDataId((Pokemon*)ptr);
	case 0x83:
		return pokemonBiosGetHp((Pokemon*)ptr);
	case 0x87:
		return pokemonBiosGetMaxHp((Pokemon*)ptr);
	case 0x88:
		return pokemonBiosGetPhyAtk((Pokemon*)ptr);
	case 0x89:
		return pokemonBiosGetPhyDef((Pokemon*)ptr);
	case 0x8a:
		return pokemonBiosGetSpeAtk((Pokemon*)ptr);
	case 0x8b:
		return pokemonBiosGetSpeDef((Pokemon*)ptr);
	case 0x8c:
		return pokemonBiosGetNimbleness((Pokemon*)ptr);
	case 0x8d:
		return pokemonBiosGetMaxHpEffort((Pokemon*)ptr);
	case 0x8e:
		return pokemonBiosGetPhyAtkEffort((Pokemon*)ptr);
	case 0x8f:
		return pokemonBiosGetPhyDefEffort((Pokemon*)ptr);
	case 0x90:
		return pokemonBiosGetSpeAtkEffort((Pokemon*)ptr);
	case 0x91:
		return pokemonBiosGetSpeDefEffort((Pokemon*)ptr);
	case 0x92:
		return pokemonBiosGetNimblenessEffort((Pokemon*)ptr);
	case 0x93:
		return pokemonBiosGetMaxHpRnd((Pokemon*)ptr);
	case 0x94:
		return pokemonBiosGetPhyAtkRnd((Pokemon*)ptr);
	case 0x95:
		return pokemonBiosGetPhyDefRnd((Pokemon*)ptr);
	case 0x96:
		return pokemonBiosGetSpeAtkRnd((Pokemon*)ptr);
	case 0x97:
		return pokemonBiosGetSpeDefRnd((Pokemon*)ptr);
	case 0x98:
		return pokemonBiosGetNimblenessRnd((Pokemon*)ptr);
	case 0x99:
		return pokemonBiosGetFriend((Pokemon*)ptr);
	case 0x9c:
		return pokemonBiosGetStyle((Pokemon*)ptr);
	case 0x9d:
		return pokemonBiosGetBeautiful((Pokemon*)ptr);
	case 0x9e:
		return pokemonBiosGetCute((Pokemon*)ptr);
	case 0x9f:
		return pokemonBiosGetClever((Pokemon*)ptr);
	case 0xa0:
		return pokemonBiosGetStrong((Pokemon*)ptr);
	case 0xa1:
		return pokemonBiosGetFur((Pokemon*)ptr);
	case 0xa3:
		return pokemonBiosGetChampRibbon((Pokemon*)ptr);
	case 0xa4:
		return pokemonBiosGetWinningRibbon((Pokemon*)ptr);
	case 0xa5:
		return pokemonBiosGetVictoryRibbon((Pokemon*)ptr);
	case 0xa6:
		return pokemonBiosGetBromideRibbon((Pokemon*)ptr);
	case 0xa7:
		return pokemonBiosGetGanbaRibbon((Pokemon*)ptr);
	case 0xa8:
		return pokemonBiosGetMarineRibbon((Pokemon*)ptr);
	case 0xa9:
		return pokemonBiosGetLandRibbon((Pokemon*)ptr);
	case 0xaa:
		return pokemonBiosGetSkyRibbon((Pokemon*)ptr);
	case 0xab:
		return pokemonBiosGetCountryRibbon((Pokemon*)ptr);
	case 0xac:
		return pokemonBiosGetNationalRibbon((Pokemon*)ptr);
	case 0xad:
		return pokemonBiosGetEarthRibbon((Pokemon*)ptr);
	case 0xae:
		return pokemonBiosGetWorldRibbon((Pokemon*)ptr);
	case 0xaf:
		return pokemonBiosGetAmariRibbon((Pokemon*)ptr);
	case 0xb0:
		return pokemonBiosGetStyleMedal((Pokemon*)ptr);
	case 0xb1:
		return pokemonBiosGetBeautifulMedal((Pokemon*)ptr);
	case 0xb2:
		return pokemonBiosGetCuteMedal((Pokemon*)ptr);
	case 0xb3:
		return pokemonBiosGetCleverMedal((Pokemon*)ptr);
	case 0xb4:
		return pokemonBiosGetStrongMedal((Pokemon*)ptr);
	case 0xb5:
		return pokemonBiosGetPokerus((Pokemon*)ptr);
	case 0xb6:
		return pokemonBiosGetTamagoFlag((Pokemon*)ptr);
	case 0xb7:
		return pokemonBiosGetTokuseiFlag((Pokemon*)ptr);
	case 0xb8:
		return pokemonBiosGetFuseiFlag((Pokemon*)ptr);
	case 0xb9:
		return pokemonBiosGetFlagAmari((Pokemon*)ptr);
	case 0xba:
		return pokemonGetSex((Pokemon*)ptr);
	case 0xbb:
		return pokemonBiosGetPcboxMark((Pokemon*)ptr);
	case 0xbc:
		return pokemonBiosGetMailId((Pokemon*)ptr);
	case 0xbd:
		return pokemonBiosGetPara1Amari((Pokemon*)ptr);
	case 0xbe:
		return pokemonBiosGetAmari((Pokemon*)ptr);
	case 0xbf:
		return _pokemonGetSeikaku((Pokemon*)ptr);
	case 0xc0:
		return _pokemonGetNowExpToLevel((Pokemon*)ptr);
	case 0xc1:
		return (u8)pokemonCheckRare((Pokemon*)ptr);
	case 0xc9:
		return pokemonBiosGetFightTrainerPokemonDataId((Pokemon*)ptr);
	case 0xc3:
		return pokemonBiosGetDarkpokemonDataId((Pokemon*)ptr);
	case 0xc4:
		return pokemonBiosGetInitDp((Pokemon*)ptr);
	case 0xc5:
		return pokemonBiosGetDp((Pokemon*)ptr);
	case 0xc6:
		return pokemonBiosGetPoolExp((Pokemon*)ptr);
	case 0xc7:
		return pokemonBiosGetPoolFriend((Pokemon*)ptr);
	case 0xc2:
		return pokemonBiosGetDarkFlag((Pokemon*)ptr);
	case 0xc8:
		return 0;
	case 0xcb:
		return (u32)fightPokemonBiosGetMotoPokemonPtr((FightPokemon*)ptr);
	case 0xcc:
		return (u32)fightPokemonBiosGetPokemonBuffPtr((FightPokemon*)ptr);
	case 0xcd:
		return (u32)fightPokemonBiosGetFightJoutaiPtr((FightPokemon*)ptr, index);
	case 0xce:
		return fightPokemonBiosGetEntryId((FightPokemon*)ptr);
	case 0xcf:
		return fightPokemonBiosGetCatchEntryFlag((FightPokemon*)ptr);
	case 0xd0:
		return fightPokemonBiosGetLevelUpFlag((FightPokemon*)ptr);
	case 0xd1:
		return fightPokemonBiosGetDarkOutFlag((FightPokemon*)ptr);
	case 0xd2:
		return fightPokemonBiosGetHokakuFlag((FightPokemon*)ptr);
	case 0xd5:
		return (u32)fightOutPokemonBiosGetMotoFightPokemonPtr((FightOutPokemon*)ptr);
	case 0xd6:
		return (u32)fightOutPokemonBiosGetFightPokemonPtr((FightOutPokemon*)ptr);
	case 0xd7:
		return (u32)fightOutPokemonBiosGetFightPokemonHensinBuffPtr((FightOutPokemon*)ptr);
	case 0xd8:
		return (u32)fightOutPokemonBiosGetFightoutJoutaiPtr((FightOutPokemon*)ptr, index);
	case 0xd9:
		return (u32)fightOutPokemonBiosGetFightWazaPtr((FightOutPokemon*)ptr);
	case 0xda:
		return fightOutPokemonGetUseWazaDataId((FightOutPokemon*)ptr);
	case 0xdb:
		return fightOutPokemonGetMotoWazaDataId((FightOutPokemon*)ptr);
	case 0xdc:
		return fightWaza_GetDamageValue(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr));
	case 0xdd:
		return fightWaza_GetCritical(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr));
	case 0xde:
		return fightWazaIsJoutaiDataId(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr), index);
	case 0xe0:
		return fightWazaIsHit(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr));
	case 0xe1:
		return fightWaza_GetDamage(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr));
	case 0xe2:
		return fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr));
	case 0xe3:
		return fightWaza_GetTargetDataId(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr));
	case 0xe4:
		return fightWaza_GetHitDamage(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr));
	case 0xe5:
		return (u32)fightOutPokemonBiosGetFightItemPtr((FightOutPokemon*)ptr);
	case 0xe6:
		return fightOutPokemonBiosGetAbicntPhyAtk((FightOutPokemon*)ptr);
	case 0xe7:
		return fightOutPokemonBiosGetAbicntPhyDef((FightOutPokemon*)ptr);
	case 0xe8:
		return fightOutPokemonBiosGetAbicntSpeAtk((FightOutPokemon*)ptr);
	case 0xe9:
		return fightOutPokemonBiosGetAbicntSpeDef((FightOutPokemon*)ptr);
	case 0xea:
		return fightOutPokemonBiosGetAbicntNimbleness((FightOutPokemon*)ptr);
	case 0xeb:
		return fightOutPokemonBiosGetAbicntAverage((FightOutPokemon*)ptr);
	case 0xec:
		return fightOutPokemonBiosGetAbicntAvoid((FightOutPokemon*)ptr);
	case 0xed:
		return fightOutPokemonBiosGetFightoutTurnCount((FightOutPokemon*)ptr);
	case 0xee:
		return (u32)fightOutPokemonBiosGetSequencePtr((FightOutPokemon*)ptr);
	case 0xef:
		return fightOutPokemonBiosGetSketchWazaDataId((FightOutPokemon*)ptr);
	case 0xf0:
		return fightOutPokemonBiosGetLastSelectWazaDataId((FightOutPokemon*)ptr);
	case 0xf1:
		return fightOutPokemonBiosGetLastUseWazaDataId((FightOutPokemon*)ptr);
	case 0xf2:
		return fightOutPokemonBiosGetLastReceiveWazaTargetDataId((FightOutPokemon*)ptr);
	case 0xf3:
		return fightOutPokemonBiosGetHitWazaDataId((FightOutPokemon*)ptr);
	case 0xf4:
		return fightOutPokemonBiosGetHitWazaZokuseiDataId((FightOutPokemon*)ptr);
	case 0xf5:
		return fightOutPokemonBiosGetGamanDamageValue((FightOutPokemon*)ptr);
	case 0xf6:
		return fightOutPokemonBiosGetGamanDamageTargetId((FightOutPokemon*)ptr);
	case 0xf7:
		return fightOutPokemonBiosGetOumuWazaDataId((FightOutPokemon*)ptr);
	case 0xf8:
		return (u32)fightOutPokemonBiosGetKeepFightWazaPtr((FightOutPokemon*)ptr);
	case 0xf9:
		return fightOutPokemonBiosGetNamakeFlag((FightOutPokemon*)ptr);
	case 0xfa:
		return fightOutPokemonBiosGetUsedItemDataId((FightOutPokemon*)ptr);
	case 0xfb:
		return fightOutPokemonBiosGetStockItemDataId((FightOutPokemon*)ptr);
	case 0xfc:
		return fightOutPokemonBiosGetSuccessCnt((FightOutPokemon*)ptr);
	case 0xfd:
		return fightOutPokemonBiosGetMeetEnemyFightPokemonEntryId((FightOutPokemon*)ptr, index);
	case 0xfe:
		return (u32)fightOutPokemonBiosGetFightActionBuffPtr((FightOutPokemon*)ptr);
	case 0xff:
		return fightOutPokemonBiosGetZokuseiDataId((FightOutPokemon*)ptr, index);
	case 0x100:
		return fightOutPokemonBiosGetTokuseiDataId((FightOutPokemon*)ptr);
	case 0x101:
		return (u32)fightOutPokemonBiosGetWazaMenuCurPtr((FightOutPokemon*)ptr);
	case 0x102:
		return fightOutPokemonBiosGetDamageAtkValue((FightOutPokemon*)ptr);
	case 0x103:
		return fightOutPokemonBiosGetDamageAtkTargetId((FightOutPokemon*)ptr);
	case 0x104:
		return fightOutPokemonBiosGetDamageSpeValue((FightOutPokemon*)ptr);
	case 0x105:
		return fightOutPokemonBiosGetDamageSpeTargetId((FightOutPokemon*)ptr);
	case 0x106:
		return fightOutPokemonBiosGetMahiNoAttackFlag((FightOutPokemon*)ptr);
	case 0x107:
		return fightOutPokemonBiosGetKonranMyselfAttackFlag((FightOutPokemon*)ptr);
	case 0x108:
		return fightOutPokemonBiosGetOutWazaKoukanaiFlag((FightOutPokemon*)ptr);
	case 0x109:
		return fightOutPokemonBiosGetTameWazaFlag((FightOutPokemon*)ptr);
	case 0x10a:
		return fightOutPokemonBiosGetItemNigeruFlag((FightOutPokemon*)ptr);
	case 0x10b:
		return fightOutPokemonBiosGetHuuinNoAttackFlag((FightOutPokemon*)ptr);
	case 0x10c:
		return fightOutPokemonBiosGetMeroMeroNoAttackFlag((FightOutPokemon*)ptr);
	case 0x10d:
		return fightOutPokemonBiosGetKanashibariNoAttackFlag((FightOutPokemon*)ptr);
	case 0x10e:
		return fightOutPokemonBiosGetChouhatsuNoAttackFlag((FightOutPokemon*)ptr);
	case 0x10f:
		return fightOutPokemonBiosGetIchamonNoAttackFlag((FightOutPokemon*)ptr);
	case 0x110:
		return fightOutPokemonBiosGetHirumuNoAttackFlag((FightOutPokemon*)ptr);
	case 0x111:
		return fightOutPokemonBiosGetPassPpdecFlag((FightOutPokemon*)ptr);
	case 0x112:
		return fightOutPokemonBiosGetFightActionFlag((FightOutPokemon*)ptr);
	case 0x113:
		return fightOutPokemonBiosGetDoClearbodyFlag((FightOutPokemon*)ptr);
	case 0x114:
		return fightOutPokemonBiosGetReceivesWazaHiraishinFlag((FightOutPokemon*)ptr);
	case 0x115:
		return fightOutPokemonBiosGetVanishoffFlag((FightOutPokemon*)ptr);
	case 0x116:
		return fightOutPokemonBiosGetDoIkakuFlag((FightOutPokemon*)ptr);
	case 0x117:
		return fightOutPokemonBiosGetDoTraceFlag((FightOutPokemon*)ptr);
	case 0x118:
		return fightOutPokemonBiosGetNoPressureFlag((FightOutPokemon*)ptr);
	case 0x119:
		return fightOutPokemonBiosGetIrekaetaFlag((FightOutPokemon*)ptr);
	case 0x11a:
		return fightOutPokemonBiosGetItemKoraetaFlag((FightOutPokemon*)ptr);
	case 0x11b:
		return fightOutPokemonBiosGetKaigaraDamageValue((FightOutPokemon*)ptr);
	case 0x11c:
		return fightOutPokemonBiosGetMyselfDamageAtkValue((FightOutPokemon*)ptr);
	case 0x11d:
		return fightOutPokemonBiosGetMyselfDamageAtkTargetId((FightOutPokemon*)ptr);
	case 0x11e:
		return fightOutPokemonBiosGetMyselfDamageSpeValue((FightOutPokemon*)ptr);
	case 0x11f:
		return fightOutPokemonBiosGetMyselfDamageSpeTargetId((FightOutPokemon*)ptr);
	case 0x120:
		return fightOutPokemonBiosGetKizetuFlag((FightOutPokemon*)ptr);
	case 0x121:
		return fightOutPokemonBiosGetIrekaeTargetEntryId((FightOutPokemon*)ptr);
	case 0x122:
		return (u32)fightOutPokemonBiosGetFightOutPokemonEnemyPtr((FightOutPokemon*)ptr, index);
	case 0x123:
		return fightOutPokemonCheckFightOut((FightOutPokemon*)ptr);
    }
    return 0;
}

void pokemonSetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index, u32 value)
{
    FightJoutai* joutai;
    FightJoutai* src;
    FightWaza* waza;
    u8 i;

    if (kind == 0 || kind >= 0x124) {
        return;
    }
    if (kind < 0x6D) {
        pokemonDataBiosGetPtr(pokemonDataId);
        ptr = pokemonDataBiosGetPtr(pokemonDataId);
        if (ptr == 0) {
            return;
        }
    } else if (ptr == 0) {
        return;
    }
    switch (kind) {
	case 0x1:
		pokemonDataBiosSetName((PokemonData*)ptr, (const char*)value);
		break;
	case 0x3:
		pokemonDataBiosSetBasisMaxHp((PokemonData*)ptr, value);
		break;
	case 0x4:
		pokemonDataBiosSetBasisPhyAtk((PokemonData*)ptr, value);
		break;
	case 0x5:
		pokemonDataBiosSetBasisPhyDef((PokemonData*)ptr, value);
		break;
	case 0x6:
		pokemonDataBiosSetBasisSpeAtk((PokemonData*)ptr, value);
		break;
	case 0x7:
		pokemonDataBiosSetBasisSpeDef((PokemonData*)ptr, value);
		break;
	case 0x8:
		pokemonDataBiosSetBasisNimbleness((PokemonData*)ptr, value);
		break;
	case 0xa:
		pokemonDataBiosSetGiveMaxHpEffort((PokemonData*)ptr, value);
		break;
	case 0xb:
		pokemonDataBiosSetGivePhyAtkEffort((PokemonData*)ptr, value);
		break;
	case 0xc:
		pokemonDataBiosSetGivePhyDefEffort((PokemonData*)ptr, value);
		break;
	case 0xd:
		pokemonDataBiosSetGiveSpeAtkEffort((PokemonData*)ptr, value);
		break;
	case 0xe:
		pokemonDataBiosSetGiveSpeDefEffort((PokemonData*)ptr, value);
		break;
	case 0xf:
		pokemonDataBiosSetGiveNimblenessEffort((PokemonData*)ptr, value);
		break;
	case 0x10:
		pokemonDataBiosSetGiveExp((PokemonData*)ptr, value);
		break;
	case 0x11:
		pokemonDataBiosSetGrowDataId((PokemonData*)ptr, value);
		break;
	case 0x12:
		pokemonDataBiosSetGet((PokemonData*)ptr, value);
		break;
	case 0x13:
		pokemonDataBiosSetSexRatio((PokemonData*)ptr, value);
		break;
	case 0x14:
		pokemonDataBiosSetInitFriend((PokemonData*)ptr, value);
		break;
	case 0x15:
		pokemonDataBiosSetItemDataId((PokemonData*)ptr, index, value);
		break;
	case 0x16:
		pokemonDataBiosSetZokuseiDataId((PokemonData*)ptr, index, value);
		break;
	case 0x17:
		pokemonDataBiosSetTokuseiDataId((PokemonData*)ptr, index, value);
		break;
	case 0x19:
		pokemonDataBiosSetSinkaKind((PokemonData*)ptr, index, value);
		break;
	case 0x1a:
		pokemonDataBiosSetSinkaBuff((PokemonData*)ptr, index, value);
		break;
	case 0x1b:
		pokemonDataBiosSetSinkaPokemonDataId((PokemonData*)ptr, index, value);
		break;
	case 0x1d:
		pokemonDataBiosSetGetWazaLevel((PokemonData*)ptr, index, value);
		break;
	case 0x1e:
		pokemonDataBiosSetGetWazaDataId((PokemonData*)ptr, index, value);
		break;
	case 0x20:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 0, value);
		break;
	case 0x21:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 1, value);
		break;
	case 0x22:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 2, value);
		break;
	case 0x23:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 3, value);
		break;
	case 0x24:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 4, value);
		break;
	case 0x25:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 5, value);
		break;
	case 0x26:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 6, value);
		break;
	case 0x27:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 7, value);
		break;
	case 0x28:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 8, value);
		break;
	case 0x29:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 9, value);
		break;
	case 0x2a:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 10, value);
		break;
	case 0x2b:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 11, value);
		break;
	case 0x2c:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 12, value);
		break;
	case 0x2d:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 13, value);
		break;
	case 0x2e:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 14, value);
		break;
	case 0x2f:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 15, value);
		break;
	case 0x30:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 16, value);
		break;
	case 0x31:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 17, value);
		break;
	case 0x32:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 18, value);
		break;
	case 0x33:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 19, value);
		break;
	case 0x34:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 20, value);
		break;
	case 0x35:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 21, value);
		break;
	case 0x36:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 22, value);
		break;
	case 0x37:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 23, value);
		break;
	case 0x38:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 24, value);
		break;
	case 0x39:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 26, value);
		break;
	case 0x3a:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 27, value);
		break;
	case 0x3b:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 28, value);
		break;
	case 0x3c:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 29, value);
		break;
	case 0x3d:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 30, value);
		break;
	case 0x3e:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 31, value);
		break;
	case 0x3f:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 32, value);
		break;
	case 0x40:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 33, value);
		break;
	case 0x41:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 34, value);
		break;
	case 0x42:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 35, value);
		break;
	case 0x43:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 36, value);
		break;
	case 0x44:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 37, value);
		break;
	case 0x45:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 38, value);
		break;
	case 0x46:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 39, value);
		break;
	case 0x47:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 40, value);
		break;
	case 0x48:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 41, value);
		break;
	case 0x49:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 42, value);
		break;
	case 0x4a:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 43, value);
		break;
	case 0x4b:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 44, value);
		break;
	case 0x4c:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 45, value);
		break;
	case 0x4d:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 46, value);
		break;
	case 0x4e:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 47, value);
		break;
	case 0x4f:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 48, value);
		break;
	case 0x50:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 49, value);
		break;
	case 0x51:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 50, value);
		break;
	case 0x52:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 51, value);
		break;
	case 0x53:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 52, value);
		break;
	case 0x54:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 53, value);
		break;
	case 0x55:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 54, value);
		break;
	case 0x56:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 55, value);
		break;
	case 0x57:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 56, value);
		break;
	case 0x58:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 57, value);
		break;
	case 0x59:
		pokemonDataBiosSetWazaMcn((PokemonData*)ptr, 58, value);
		break;
	case 0x5a:
		pokemonDataBiosSetPokebodyId((PokemonData*)ptr, index, value);
		break;
	case 0x5b:
		pokemonDataBiosSetStatusFaceMenuSpriteId((PokemonData*)ptr, index, value);
		break;
	case 0x5c:
		pokemonDataBiosSetColor((PokemonData*)ptr, index, value);
		break;
	case 0x5d:
		pokemonDataBiosSetTypeName((PokemonData*)ptr, value);
		break;
	case 0x5e:
		pokemonDataBiosSetHeight((PokemonData*)ptr, value);
		break;
	case 0x5f:
		pokemonDataBiosSetWeight((PokemonData*)ptr, value);
		break;
	case 0x60:
		pokemonDataBiosSetDoc((PokemonData*)ptr, value);
		break;
	case 0x61:
		pokemonDataBiosSetVoice((PokemonData*)ptr, value);
		break;
	case 0x62:
		pokemonDataBiosSetMitaFlag((PokemonData*)ptr, value);
		break;
	case 0x63:
		pokemonDataBiosSetTukamaetaFlag((PokemonData*)ptr, value);
		break;
	case 0x64:
		pokemonDataBiosSetNumZukan((PokemonData*)ptr, value);
		break;
	case 0x65:
		pokemonDataBiosSetNumPokemon((PokemonData*)ptr, value);
		break;
	case 0x66:
		pokemonDataBiosSetPkxDataId((PokemonData*)ptr, value);
		break;
	case 0x68:
		pokemonDataBiosSetKowaza((PokemonData*)ptr, index, value);
		break;
	case 0x6e:
		pokemonBiosSetPokemonDataId((Pokemon*)ptr, value);
		break;
	case 0x6f:
		pokemonBiosSetRnd((Pokemon*)ptr, value);
		break;
	case 0x71:
		pokemonBiosSetCatchFloorId((Pokemon*)ptr, value);
		break;
	case 0x72:
		pokemonBiosSetCatchLevel((Pokemon*)ptr, value);
		break;
	case 0x73:
		pokemonBiosSetCatchBallId((Pokemon*)ptr, value);
		break;
	case 0x74:
		pokemonBiosSetCatchTrainerSex((Pokemon*)ptr, value);
		break;
	case 0x75:
		pokemonBiosSetCatchTrainerRnd((Pokemon*)ptr, value);
		break;
	case 0x76:
		pokemonBiosSetCatchTrainerNamePtr((Pokemon*)ptr, (void*)value);
		break;
	case 0x77:
		pokemonBiosSetNicknamePtr((Pokemon*)ptr, (void*)value);
		break;
	case 0x78:
		pokemonBiosSetNicknameOrgPtr((Pokemon*)ptr, (void*)value);
		break;
	case 0x79:
		pokemonBiosSetExp((Pokemon*)ptr, value);
		break;
	case 0x7a:
		pokemonBiosSetLevel((Pokemon*)ptr, value);
		break;
	case 0x7d:
		pokemonBiosSetConditionAmari((Pokemon*)ptr, value);
		break;
	case 0x7f:
		pokemonBiosSetPokemonWazaDataId((Pokemon*)ptr, index, value);
		break;
	case 0x80:
		pokemonBiosSetPokemonWazaPp((Pokemon*)ptr, index, value);
		break;
	case 0x81:
		pokemonBiosSetPokemonWazaPpCount((Pokemon*)ptr, index, value);
		break;
	case 0x82:
		pokemonBiosSetItemDataId((Pokemon*)ptr, value);
		break;
	case 0x83:
		pokemonBiosSetHp((Pokemon*)ptr, value);
		break;
	case 0x87:
		pokemonBiosSetMaxHp((Pokemon*)ptr, value);
		break;
	case 0x88:
		pokemonBiosSetPhyAtk((Pokemon*)ptr, value);
		break;
	case 0x89:
		pokemonBiosSetPhyDef((Pokemon*)ptr, value);
		break;
	case 0x8a:
		pokemonBiosSetSpeAtk((Pokemon*)ptr, value);
		break;
	case 0x8b:
		pokemonBiosSetSpeDef((Pokemon*)ptr, value);
		break;
	case 0x8c:
		pokemonBiosSetNimbleness((Pokemon*)ptr, value);
		break;
	case 0x8d:
		pokemonBiosSetMaxHpEffort((Pokemon*)ptr, value);
		break;
	case 0x8e:
		pokemonBiosSetPhyAtkEffort((Pokemon*)ptr, value);
		break;
	case 0x8f:
		pokemonBiosSetPhyDefEffort((Pokemon*)ptr, value);
		break;
	case 0x90:
		pokemonBiosSetSpeAtkEffort((Pokemon*)ptr, value);
		break;
	case 0x91:
		pokemonBiosSetSpeDefEffort((Pokemon*)ptr, value);
		break;
	case 0x92:
		pokemonBiosSetNimblenessEffort((Pokemon*)ptr, value);
		break;
	case 0x93:
		pokemonBiosSetMaxHpRnd((Pokemon*)ptr, value);
		break;
	case 0x94:
		pokemonBiosSetPhyAtkRnd((Pokemon*)ptr, value);
		break;
	case 0x95:
		pokemonBiosSetPhyDefRnd((Pokemon*)ptr, value);
		break;
	case 0x96:
		pokemonBiosSetSpeAtkRnd((Pokemon*)ptr, value);
		break;
	case 0x97:
		pokemonBiosSetSpeDefRnd((Pokemon*)ptr, value);
		break;
	case 0x98:
		pokemonBiosSetNimblenessRnd((Pokemon*)ptr, value);
		break;
	case 0x99:
		pokemonBiosSetFriend((Pokemon*)ptr, value);
		break;
	case 0x9c:
		pokemonBiosSetStyle((Pokemon*)ptr, value);
		break;
	case 0x9d:
		pokemonBiosSetBeautiful((Pokemon*)ptr, value);
		break;
	case 0x9e:
		pokemonBiosSetCute((Pokemon*)ptr, value);
		break;
	case 0x9f:
		pokemonBiosSetClever((Pokemon*)ptr, value);
		break;
	case 0xa0:
		pokemonBiosSetStrong((Pokemon*)ptr, value);
		break;
	case 0xa1:
		pokemonBiosSetFur((Pokemon*)ptr, value);
		break;
	case 0xa3:
		pokemonBiosSetChampRibbon((Pokemon*)ptr, value);
		break;
	case 0xa4:
		pokemonBiosSetWinningRibbon((Pokemon*)ptr, value);
		break;
	case 0xa5:
		pokemonBiosSetVictoryRibbon((Pokemon*)ptr, value);
		break;
	case 0xa6:
		pokemonBiosSetBromideRibbon((Pokemon*)ptr, value);
		break;
	case 0xa7:
		pokemonBiosSetGanbaRibbon((Pokemon*)ptr, value);
		break;
	case 0xa8:
		pokemonBiosSetMarineRibbon((Pokemon*)ptr, value);
		break;
	case 0xa9:
		pokemonBiosSetLandRibbon((Pokemon*)ptr, value);
		break;
	case 0xaa:
		pokemonBiosSetSkyRibbon((Pokemon*)ptr, value);
		break;
	case 0xab:
		pokemonBiosSetCountryRibbon((Pokemon*)ptr, value);
		break;
	case 0xac:
		pokemonBiosSetNationalRibbon((Pokemon*)ptr, value);
		break;
	case 0xad:
		pokemonBiosSetEarthRibbon((Pokemon*)ptr, value);
		break;
	case 0xae:
		pokemonBiosSetWorldRibbon((Pokemon*)ptr, value);
		break;
	case 0xaf:
		pokemonBiosSetAmariRibbon((Pokemon*)ptr, value);
		break;
	case 0xb0:
		pokemonBiosSetStyleMedal((Pokemon*)ptr, value);
		break;
	case 0xb1:
		pokemonBiosSetBeautifulMedal((Pokemon*)ptr, value);
		break;
	case 0xb2:
		pokemonBiosSetCuteMedal((Pokemon*)ptr, value);
		break;
	case 0xb3:
		pokemonBiosSetCleverMedal((Pokemon*)ptr, value);
		break;
	case 0xb4:
		pokemonBiosSetStrongMedal((Pokemon*)ptr, value);
		break;
	case 0xb5:
		pokemonBiosSetPokerus((Pokemon*)ptr, value);
		break;
	case 0xb6:
		pokemonBiosSetTamagoFlag((Pokemon*)ptr, value);
		break;
	case 0xb7:
		pokemonBiosSetTokuseiFlag((Pokemon*)ptr, value);
		break;
	case 0xb8:
		pokemonBiosSetFuseiFlag((Pokemon*)ptr, value);
		break;
	case 0xb9:
		pokemonBiosSetFlagAmari((Pokemon*)ptr, value);
		break;
	case 0xbb:
		pokemonBiosSetPcboxMark((Pokemon*)ptr, value);
		break;
	case 0xbc:
		pokemonBiosSetMailId((Pokemon*)ptr, value);
		break;
	case 0xbd:
		pokemonBiosSetPara1Amari((Pokemon*)ptr, value);
		break;
	case 0xbe:
		pokemonBiosSetAmari((Pokemon*)ptr, value);
		break;
	case 0xc9:
		pokemonBiosSetFightTrainerPokemonDataId((Pokemon*)ptr, value);
		break;
	case 0xc3:
		pokemonBiosSetDarkpokemonDataId((Pokemon*)ptr, value);
		break;
	case 0xc5:
		pokemonBiosSetDp((Pokemon*)ptr, value);
		break;
	case 0xc6:
		pokemonBiosSetPoolExp((Pokemon*)ptr, value);
		break;
	case 0xc7:
		pokemonBiosSetPoolFriend((Pokemon*)ptr, value);
		break;
	case 0xcb:
		fightPokemonBiosSetMotoPokemonPtr((FightPokemon*)ptr, (void*)value);
		break;
	case 0xcd:
		joutai = fightPokemon_GetFightJoutaiPtr((FightPokemon*)ptr, 0);
		if (joutai) {
			src = (FightJoutai*)value;
			for (i = 0; i < 1; i++) {
				joutai[i].joutaiDataId = src[i].joutaiDataId;
				joutai[i].waza = src[i].waza;
				joutai[i].count = src[i].count;
				joutai[i].turn = src[i].turn;
				joutai[i].turnNow = src[i].turnNow;
				joutai[i].target = src[i].target;
				joutai[i].value = src[i].value;
				joutai[i].kind = src[i].kind;
			}
		}
		break;
	case 0xce:
		fightPokemonBiosSetEntryId((FightPokemon*)ptr, value);
		break;
	case 0xcf:
		fightPokemonBiosSetCatchEntryFlag((FightPokemon*)ptr, value);
		break;
	case 0xd0:
		fightPokemonBiosSetLevelUpFlag((FightPokemon*)ptr, value);
		break;
	case 0xd1:
		fightPokemonBiosSetDarkOutFlag((FightPokemon*)ptr, value);
		break;
	case 0xd2:
		fightPokemonBiosSetHokakuFlag((FightPokemon*)ptr, value);
		break;
	case 0xd5:
		fightOutPokemonBiosSetMotoFightPokemonPtr((FightOutPokemon*)ptr, (void*)value);
		break;
	case 0xd6:
		fightOutPokemonBiosSetFightPokemonPtr((FightOutPokemon*)ptr, (void*)value);
		break;
	case 0xda:
		fightWaza_SetUseWazaDataId(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr), value);
		break;
	case 0xdb:
		fightWaza_SetMotoWazaDataId(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr), value);
		break;
	case 0xdc:
		fightWaza_SetDamageValue(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr), value);
		break;
	case 0xdd:
		fightWaza_SetCritical(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr), value);
		break;
	case 0xde:
		waza = fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr);
		if (fightWazaCheckWriteJoutaiDataId(waza, value) == 2) {
			fightWazaWriteJoutaiDataId(waza, value, 0);
		}
		break;
	case 0xdf:
		waza = fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr);
		if ((u16)value != 0) {
			if (fightWazaIsJoutaiDataId(waza, value) == 1) {
				fightWazaInitJoutaiDataId(waza, value);
			}
		} else {
			fightWazaInitJoutai(waza);
		}
		break;
	case 0xe1:
		fightWaza_SetDamage(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr), value);
		break;
	case 0xe2:
		fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr), value);
		break;
	case 0xe3:
		fightWaza_SetTargetDataId(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr), value);
		break;
	case 0xe4:
		fightWaza_SetHitDamage(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)ptr), value);
		break;
	case 0xe6:
		fightOutPokemonBiosSetAbicntPhyAtk((FightOutPokemon*)ptr, value);
		break;
	case 0xe7:
		fightOutPokemonBiosSetAbicntPhyDef((FightOutPokemon*)ptr, value);
		break;
	case 0xe8:
		fightOutPokemonBiosSetAbicntSpeAtk((FightOutPokemon*)ptr, value);
		break;
	case 0xe9:
		fightOutPokemonBiosSetAbicntSpeDef((FightOutPokemon*)ptr, value);
		break;
	case 0xea:
		fightOutPokemonBiosSetAbicntNimbleness((FightOutPokemon*)ptr, value);
		break;
	case 0xeb:
		fightOutPokemonBiosSetAbicntAverage((FightOutPokemon*)ptr, value);
		break;
	case 0xec:
		fightOutPokemonBiosSetAbicntAvoid((FightOutPokemon*)ptr, value);
		break;
	case 0xed:
		fightOutPokemonBiosSetFightoutTurnCount((FightOutPokemon*)ptr, value);
		break;
	case 0xee:
		fightOutPokemonBiosSetSequencePtr((FightOutPokemon*)ptr, (void*)value);
		break;
	case 0xef:
		fightOutPokemonBiosSetSketchWazaDataId((FightOutPokemon*)ptr, value);
		break;
	case 0xf0:
		fightOutPokemonBiosSetLastSelectWazaDataId((FightOutPokemon*)ptr, value);
		break;
	case 0xf1:
		fightOutPokemonBiosSetLastUseWazaDataId((FightOutPokemon*)ptr, value);
		break;
	case 0xf2:
		fightOutPokemonBiosSetLastReceiveWazaTargetDataId((FightOutPokemon*)ptr, value);
		break;
	case 0xf3:
		fightOutPokemonBiosSetHitWazaDataId((FightOutPokemon*)ptr, value);
		break;
	case 0xf4:
		fightOutPokemonBiosSetHitWazaZokuseiDataId((FightOutPokemon*)ptr, value);
		break;
	case 0xf5:
		fightOutPokemonBiosSetGamanDamageValue((FightOutPokemon*)ptr, value);
		break;
	case 0xf6:
		fightOutPokemonBiosSetGamanDamageTargetId((FightOutPokemon*)ptr, value);
		break;
	case 0xf7:
		fightOutPokemonBiosSetOumuWazaDataId((FightOutPokemon*)ptr, value);
		break;
	case 0xf9:
		fightOutPokemonBiosSetNamakeFlag((FightOutPokemon*)ptr, value);
		break;
	case 0xfa:
		fightOutPokemonBiosSetUsedItemDataId((FightOutPokemon*)ptr, value);
		break;
	case 0xfb:
		fightOutPokemonBiosSetStockItemDataId((FightOutPokemon*)ptr, value);
		break;
	case 0xfc:
		fightOutPokemonBiosSetSuccessCnt((FightOutPokemon*)ptr, value);
		break;
	case 0xfd:
		fightOutPokemonBiosSetMeetEnemyFightPokemonEntryId((FightOutPokemon*)ptr, index, (s8)value);
		break;
	case 0xff:
		fightOutPokemonBiosSetZokuseiDataId((FightOutPokemon*)ptr, index, value);
		break;
	case 0x100:
		fightOutPokemonBiosSetTokuseiDataId((FightOutPokemon*)ptr, value);
		break;
	case 0x102:
		fightOutPokemonBiosSetDamageAtkValue((FightOutPokemon*)ptr, value);
		break;
	case 0x103:
		fightOutPokemonBiosSetDamageAtkTargetId((FightOutPokemon*)ptr, value);
		break;
	case 0x104:
		fightOutPokemonBiosSetDamageSpeValue((FightOutPokemon*)ptr, value);
		break;
	case 0x105:
		fightOutPokemonBiosSetDamageSpeTargetId((FightOutPokemon*)ptr, value);
		break;
	case 0x106:
		fightOutPokemonBiosSetMahiNoAttackFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x107:
		fightOutPokemonBiosSetKonranMyselfAttackFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x108:
		fightOutPokemonBiosSetOutWazaKoukanaiFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x109:
		fightOutPokemonBiosSetTameWazaFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x10a:
		fightOutPokemonBiosSetItemNigeruFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x10b:
		fightOutPokemonBiosSetHuuinNoAttackFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x10c:
		fightOutPokemonBiosSetMeroMeroNoAttackFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x10d:
		fightOutPokemonBiosSetKanashibariNoAttackFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x10e:
		fightOutPokemonBiosSetChouhatsuNoAttackFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x10f:
		fightOutPokemonBiosSetIchamonNoAttackFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x110:
		fightOutPokemonBiosSetHirumuNoAttackFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x111:
		fightOutPokemonBiosSetPassPpdecFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x112:
		fightOutPokemonBiosSetFightActionFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x113:
		fightOutPokemonBiosSetDoClearbodyFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x114:
		fightOutPokemonBiosSetReceivesWazaHiraishinFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x115:
		fightOutPokemonBiosSetVanishoffFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x116:
		fightOutPokemonBiosSetDoIkakuFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x117:
		fightOutPokemonBiosSetDoTraceFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x118:
		fightOutPokemonBiosSetNoPressureFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x119:
		fightOutPokemonBiosSetIrekaetaFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x11a:
		fightOutPokemonBiosSetItemKoraetaFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x11b:
		fightOutPokemonBiosSetKaigaraDamageValue((FightOutPokemon*)ptr, value);
		break;
	case 0x11c:
		fightOutPokemonBiosSetMyselfDamageAtkValue((FightOutPokemon*)ptr, value);
		break;
	case 0x11d:
		fightOutPokemonBiosSetMyselfDamageAtkTargetId((FightOutPokemon*)ptr, value);
		break;
	case 0x11e:
		fightOutPokemonBiosSetMyselfDamageSpeValue((FightOutPokemon*)ptr, value);
		break;
	case 0x11f:
		fightOutPokemonBiosSetMyselfDamageSpeTargetId((FightOutPokemon*)ptr, value);
		break;
	case 0x120:
		fightOutPokemonBiosSetKizetuFlag((FightOutPokemon*)ptr, value);
		break;
	case 0x121:
		fightOutPokemonBiosSetIrekaeTargetEntryId((FightOutPokemon*)ptr, value);
		break;
    }
}

void pokemonResetBasisStatus(Pokemon* pokemon)
{
    u8 level;

    if (pokemon != 0) {
        level = pokemon_GetNowExpToLevel(pokemon);
        _pokemonSetLevelBasisStatus(pokemon, level);
    }
}

void pokemonGrowBasisStatus(Pokemon* pokemon, u32 exp)
{
    if (pokemon) {
        pokemon_SetExp(pokemon, exp);
        pokemonResetBasisStatus(pokemon);
    }
}

u32 pokemonCheckRare(Pokemon* pokemon)
{
    u32 trainerRnd;
    u32 rnd;

    if (pokemon == 0) {
        return 0;
    }
    trainerRnd = pokemon_GetCatchTrainerRnd(pokemon);
    rnd = pokemon_GetRnd(pokemon);
    return _pokemonCheckRare(trainerRnd, rnd);
}

void pokemonWazaInit(Pokemon* pokemon, u16 wazaNum)
{
    if (pokemon) {
        pokemon_SetPokemonWazaDataId(pokemon, wazaNum, 0);
        pokemon_SetPokemonWazaPp(pokemon, wazaNum, 0);
        pokemon_SetPokemonWazaPpCount(pokemon, wazaNum, 0);
    }
}

void pokemonWazaInitAry(Pokemon* pokemon, u16 wazaCount)
{
    if (pokemon) {
        for (u16 wazaNum = 0; wazaNum < wazaCount; wazaNum++) {
            pokemonWazaInit(pokemon, wazaNum);
        }
    }
}

void pokemonInitJoutai(Pokemon* pokemon)
{
    pokemon->initCondition();
}

void pokemonInitDarkPokemon(Pokemon* pokemon)
{
    pokemon_SetDarkpokemonDataId(pokemon, 0);
    pokemonSetDp(pokemon, -1.0f);
    pokemon_SetPoolExp(pokemon, 0);
    pokemon_SetPoolFriend(pokemon, 0);
}

void pokemonInit(Pokemon* pokemon)
{
    char16 empty = 0;

    if (pokemon) {
        pokemon_SetFightTrainerPokemonDataId(pokemon, 0);
        pokemonInitDarkPokemon(pokemon);
        pokemon_SetPokemonDataId(pokemon, 0);
        pokemon_SetRnd(pokemon, 0);
        gamedataAttestInit(pokemon_GetAttest(pokemon));
        pokemonSetCatchStatus(pokemon, 0, 0, 0, 2, 0, &empty);
        pokemon_SetNicknamePtr(pokemon, &empty);
        pokemon_SetExp(pokemon, 0);
        pokemon_SetLevel(pokemon, 0);
        pokemonInitJoutai(pokemon);
        pokemon_SetConditionAmari(pokemon, 0);
        pokemonWazaInitAry(pokemon, 4);
        pokemonDoItemSoubi(pokemon, 0, 0);
        pokemon_SetHp(pokemon, 0);
        pokemon_SetMaxHp(pokemon, 0);
        pokemon_SetPhyAtk(pokemon, 0);
        pokemon_SetPhyDef(pokemon, 0);
        pokemon_SetSpeAtk(pokemon, 0);
        pokemon_SetSpeDef(pokemon, 0);
        pokemon_SetNimbleness(pokemon, 0);
        pokemon_SetMaxHpEffort(pokemon, 0);
        pokemon_SetPhyAtkEffort(pokemon, 0);
        pokemon_SetPhyDefEffort(pokemon, 0);
        pokemon_SetSpeAtkEffort(pokemon, 0);
        pokemon_SetSpeDefEffort(pokemon, 0);
        pokemon_SetNimblenessEffort(pokemon, 0);
        pokemon_SetMaxHpRnd(pokemon, 0);
        pokemon_SetPhyAtkRnd(pokemon, 0);
        pokemon_SetPhyDefRnd(pokemon, 0);
        pokemon_SetSpeAtkRnd(pokemon, 0);
        pokemon_SetSpeDefRnd(pokemon, 0);
        pokemon_SetNimblenessRnd(pokemon, 0);
        pokemon_SetFriend(pokemon, 0);
        pokemon_SetStyle(pokemon, 0);
        pokemon_SetBeautiful(pokemon, 0);
        pokemon_SetCute(pokemon, 0);
        pokemon_SetClever(pokemon, 0);
        pokemon_SetStrong(pokemon, 0);
        pokemon_SetFur(pokemon, 0);
        pokemon_SetChampRibbon(pokemon, false);
        pokemon_SetWinningRibbon(pokemon, false);
        pokemon_SetVictoryRibbon(pokemon, false);
        pokemon_SetBromideRibbon(pokemon, false);
        pokemon_SetGanbaRibbon(pokemon, false);
        pokemon_SetMarineRibbon(pokemon, false);
        pokemon_SetLandRibbon(pokemon, false);
        pokemon_SetSkyRibbon(pokemon, false);
        pokemon_SetCountryRibbon(pokemon, false);
        pokemon_SetNationalRibbon(pokemon, false);
        pokemon_SetEarthRibbon(pokemon, false);
        pokemon_SetWorldRibbon(pokemon, false);
        pokemon_SetAmariRibbon(pokemon, 0);
        pokemon_SetStyleMedal(pokemon, 0);
        pokemon_SetBeautifulMedal(pokemon, 0);
        pokemon_SetCuteMedal(pokemon, 0);
        pokemon_SetCleverMedal(pokemon, 0);
        pokemon_SetStrongMedal(pokemon, 0);
        pokemon_SetPokerus(pokemon, 0);
        pokemon_SetTamagoFlag(pokemon, false);
        pokemon_SetTokuseiFlag(pokemon, 0);
        pokemon_SetFuseiFlag(pokemon, false);
        pokemon_SetFlagAmari(pokemon, 0);
        pokemon_SetPcboxMark(pokemon, 0);
        pokemon_SetMailId(pokemon, 0xFF);
        pokemon_SetPara1Amari(pokemon, 0);
        pokemon_SetAmari(pokemon, 0);
    }
}

void pokemonInitAry(Pokemon* pokemon, u16 count)
{
    u16 i;

    if (pokemon) {
        for (i = 0; i < count; i++) {
            pokemonInit(&pokemon[i]);
        }
    }
}

void pokemonSetTokuseiFlag(Pokemon* pokemon, u32 flag)
{
    if (pokemon) {
        if (pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(pokemon), 1) == 0) {
            flag = 0;
        }
        pokemon_SetTokuseiFlag(pokemon, flag);
    }
}

u16 pokemonGetTokuseiDataId(Pokemon* pokemon)
{
    u16 pokemonDataId;
    u8 flag;

    if (pokemon == 0) {
        return 0;
    }
    pokemonDataId = pokemon_GetPokemonDataId(pokemon);
    if (pokemonDB_GetTokuseiDataId(pokemonDataId, 1) == 0) {
        return pokemonDB_GetTokuseiDataId(pokemonDataId, 0);
    }
    flag = pokemon_GetTokuseiFlag(pokemon);
    return pokemonDB_GetTokuseiDataId(pokemonDataId, flag);
}

u32 pokemonCreateRnd(void)
{
    u16 hi = HSD_Rand();
    return (hi << 16) | (u16)HSD_Rand();
}

u32 pokemonCreateRndFit(Pokemon* pokemon, s8 sex, s8 seikaku, s8 rare, u32 trainerRnd)
{
    u32 rnd;
    s32 tries = 0x300000;

    if (pokemon == 0) {
        return pokemonCreateRnd();
    }
    do {
        rnd = pokemonCreateRnd();
        tries--;
        if (sex >= 0 && pokemonCheckSexKotei(pokemon) < 0) {
            if (sex != 2) {
                if (sex != _pokemonGetSexSub(pokemon, rnd)) {
                    continue;
                }
            } else {
                if (pokemonGetSex(pokemon) != _pokemonGetSexSub(pokemon, rnd)) { continue; }
            }
        }
        if (seikaku >= 0 && seikaku != pokemonGetSeikakuAsRnd(rnd)) {
            continue;
        }
        if (rare < 0) {
            break;
        }
        if (rare != 0) {
            if ((u8)_pokemonCheckRare(trainerRnd, rnd) == 0) {
                continue;
            }
            break;
        } else {
            if ((u8)_pokemonCheckRare(trainerRnd, rnd) != 1) {
                break;
            }
        }
    } while (tries > 0);
    return rnd;
}

void pokemonCreate(Pokemon* pokemon, u16 pokemonDataId, u8 level, Attest* attest)
{
    u16 rnd;
    u8 cursor;
    u32 i;
    u32 exp;

    if (pokemon && pokemonDataCheckValid(0, pokemonDataId) && attest) {
        pokemonInit(pokemon);
        pokemon_SetPokemonDataId(pokemon, pokemonDataId);
        pokemon_SetRnd(pokemon, pokemonCreateRnd());
        gamedataAttestBiosCopy(pokemon_GetAttest(pokemon), attest);
        pokemon_SetNicknamePtr(pokemon, GSmsgGetGSchar((u32)pokemonDB_GetName(pokemonDataId)));
        pokemon_SetLevel(pokemon, level);
        pokemon_SetMaxHpRnd(pokemon, (rnd = HSD_Rand()) & 0x1F);
        pokemon_SetPhyAtkRnd(pokemon, (rnd >> 5) & 0x1F);
        pokemon_SetPhyDefRnd(pokemon, (rnd >> 10) & 0x1F);
        pokemon_SetNimblenessRnd(pokemon, (rnd = HSD_Rand()) & 0x1F);
        pokemon_SetSpeAtkRnd(pokemon, (rnd >> 5) & 0x1F);
        pokemon_SetSpeDefRnd(pokemon, (rnd >> 10) & 0x1F);
        exp = pokemonGetNowLevelToExp(pokemon);
        pokemon_SetExp(pokemon, exp);
        pokemon_SetFriend(pokemon, pokemonDB_GetInitFriend(pokemonDataId));
        if (HSD_Rand() & 1) {
            pokemonSetTokuseiFlag(pokemon, 1);
        }
        for (i = 1; i <= level; i++) {
            cursor = 0; while (1) { if (pokemonOboeWaza(pokemon, i, 1, &cursor) == -3) { break; } cursor++; }
        }
        pokemonResetBasisStatus(pokemon);
    }
}

bool pokemonCheckValid(Pokemon* pokemon)
{
    u16 pokemonDataId;

    if (pokemon == 0) {
        return 0;
    }
    pokemonDataId = pokemon_GetPokemonDataId(pokemon);
    if (pokemonDataId == 0) {
        return 0;
    }
    if (pokemonDataCheckValid(0, pokemonDataId) == 0) {
        return 0;
    }
    if (gamedataAttestCheckValid(pokemon_GetAttest(pokemon)) == 0) {
        return 0;
    }
    return pokemon_GetFuseiFlag(pokemon) != 1;
}

void pokemonSetCatchStatus(Pokemon* pokemon, u32 floorId, u8 level, u32 ballId, u8 trainerSex, u32 trainerRnd, char16* trainerName)
{
    if (pokemon) {
        pokemon_SetCatchFloorId(pokemon, floorId);
        pokemon_SetCatchLevel(pokemon, level);
        pokemon_SetCatchBallId(pokemon, ballId);
        pokemon_SetCatchTrainerSex(pokemon, trainerSex);
        pokemon_SetCatchTrainerRnd(pokemon, trainerRnd);
        pokemon_SetCatchTrainerNamePtr(pokemon, trainerName);
    }
}

u32 pokemonWazaGetZokusei(Pokemon* pokemon, u16 wazaNum)
{
    if (pokemon == 0) {
        return 0;
    }
    return wazaDB_GetZokuseiDataId(pokemon_GetPokemonWazaDataId(pokemon, wazaNum + 4));
}

u8 pokemonWazaGetMaxPP(Pokemon* pokemon, u16 wazaNum)
{
    u16 waza;
    u8 ppCount;

    if (pokemon == 0) {
        return 0;
    }
    waza = pokemon_GetPokemonWazaDataId(pokemon, wazaNum + 4);
    ppCount = pokemon_GetPokemonWazaPpCount(pokemon, wazaNum + 4);
    return wazaGetMaxPP(waza, ppCount);
}

void pokemonWazaCreate(Pokemon* pokemon, u16 wazaNum, u16 waza)
{
    u8 maxPp;

    if (pokemon) {
        pokemonWazaInit(pokemon, wazaNum);
        pokemon_SetPokemonWazaDataId(pokemon, wazaNum, waza);
        maxPp = pokemonWazaGetMaxPP(pokemon, wazaNum);
        pokemon_SetPokemonWazaPp(pokemon, wazaNum, maxPp);
    }
}

bool pokemonWazaCheckValid(Pokemon* pokemon, u16 wazaNum)
{
    if (pokemon == 0) {
        return 0;
    }
    if (pokemon_GetPokemonWazaDataId(pokemon, wazaNum) == 0) {
        return 0;
    }
    return pokemon_GetPokemonWazaDataId(pokemon, wazaNum) != 0x163;
}

}

static void _pokemonWazaCopy(Pokemon* pokemon, u16 dst, u16 src)
{
    PokemonWaza* dstWaza;
    PokemonWaza* srcWaza;

    if (pokemon) {
        dstWaza = pokemonBiosGetPokemonWazaPtr(pokemon, dst, 0);
        srcWaza = pokemonBiosGetPokemonWazaPtr(pokemon, src, 0);
        pokemonWazaBiosCopy(dstWaza, srcWaza);
    }
}

extern "C" {

void pokemonWazaReplace(Pokemon* pokemon, u16 a, u16 b)
{
    PokemonWaza tmp;
    PokemonWaza* wazaA;
    PokemonWaza* wazaB;

    if (pokemon) {
        wazaA = pokemonBiosGetPokemonWazaPtr(pokemon, a, 0);
        wazaB = pokemonBiosGetPokemonWazaPtr(pokemon, b, 0);
        pokemonWazaBiosCopy(&tmp, wazaA);
        pokemonWazaBiosCopy(wazaA, wazaB);
        pokemonWazaBiosCopy(wazaB, &tmp);
    }
}

s8 pokemonSearchWazaDataId(Pokemon* pokemon, u16 waza)
{
    s8 i;

    if (pokemon == 0) {
        return -1;
    }
    for (i = 0; i < 4; i++) {
        if (pokemonWazaCheckValid(pokemon, i) && waza == pokemon_GetPokemonWazaDataId(pokemon, i)) {
            return i;
        }
    }
    return -1;
}

s8 pokemonSetWazaStatus(Pokemon* pokemon, u16 waza, u8 replace)
{
    s8 i;

    if (pokemon == 0) {
        return -2;
    }
    if (pokemonSearchWazaDataId(pokemon, waza) >= 0) {
        return -2;
    }
    for (i = 0; i < 4; i++) {
        if (pokemonWazaCheckValid(pokemon, i) == 0) {
            pokemonWazaCreate(pokemon, i, waza);
            return i;
        }
    }
    if (replace == 0) {
        return -1;
    }
    for (i = 1; i < 4; i++) {
        _pokemonWazaCopy(pokemon, i - 1, i);
    }
    pokemonWazaCreate(pokemon, 3, waza);
    return 3;
}

u16 pokemonGetOboeWazaDataId(Pokemon* pokemon, u8 level, u8* cursor)
{
    u16 pokemonDataId;

    if (!pokemon || !cursor) {
        return 0;
    }
    pokemonDataId = pokemon_GetPokemonDataId(pokemon);
    for (; *cursor < 20; (*cursor)++) {
        if (level == pokemonDB_GetGetWazaLevel(pokemonDataId, *cursor)) {
            return pokemonDB_GetGetWazaDataId(pokemonDataId, *cursor);
        }
    }
    return 0;
}

s8 pokemonOboeWaza(Pokemon* pokemon, u8 level, u8 replace, u8* cursor)
{
    u16 waza;

    if (pokemon == 0) {
        return -2;
    }
    waza = pokemonGetOboeWazaDataId(pokemon, level, cursor);
    if (waza == 0) {
        return -3;
    }
    return pokemonSetWazaStatus(pokemon, waza, replace);
}

u8 pokemonGetOboeWazaDataBanme(Pokemon* pokemon, u8 level)
{
    u16 pokemonDataId;
    u8 i;

    if (pokemon == 0) {
        return 0;
    }
    pokemonDataId = pokemon_GetPokemonDataId(pokemon);
    for (i = 0; i < 20; i++) {
        if (level == pokemonDB_GetGetWazaLevel(pokemonDataId, i)) {
            break;
        }
    }
    return i;
}

bool pokemonCheckFightOut(Pokemon* pokemon)
{
    if (pokemonCheckValid(pokemon) == 0) {
        return 0;
    }
    if (pokemon_GetPokemonDataId(pokemon) == 0x19C) {
        return 0;
    }
    if (pokemon_GetTamagoFlag(pokemon) == 1) {
        return 0;
    }
    return pokemon_GetHinsi(pokemon) != 1;
}

void pokemonSetOnZukanFlag(Pokemon* pokemon, u8 caught)
{
    if (pokemon) {
        pokemon_GetPokemonDataId(pokemon);
        memoDataSet(0, pokemon);
        pokemonDB_SetMitaFlag(0, true);
        if (caught) {
            pokemonDB_SetTukamaetaFlag(0, true);
        }
    }
}

void pokemonSetOnDarkPokemonFlag(Pokemon* pokemon, u8 snatched)
{
    DarkPokemon* darkPokemon;

    if (pokemon && pokemonIsDarkPokemon(pokemon)) {
        darkPokemon = darkPokemonGetDarkPokemon(pokemon_GetDarkpokemonDataId(pokemon));
        if (darkPokemon) {
            if (snatched) {
                darkPokemon->addStatus(darkPokemonStatus3);
            } else {
                darkPokemon->addStatus(darkPokemonStatus1);
            }
        }
    }
}

s8 pokemonCheckSexKotei(Pokemon* pokemon)
{
    int ratio;

    if (pokemon == 0) {
        return 2;
    }
    ratio = pokemonDB_GetSexRatio(pokemon_GetPokemonDataId(pokemon));
    if (ratio == sexGetPokemonSexRaitoKotei(0)) {
        return 0;
    }
    if (ratio == sexGetPokemonSexRaitoKotei(1)) {
        return 1;
    }
    if (ratio == sexGetPokemonSexRaitoKotei(2)) {
        return 2;
    }
    return -1;
}

}

static u8 _pokemonGetSexSub(Pokemon* pokemon, u32 rnd)
{
    u32 ratio;
    s8 sex;

    ratio = pokemonDB_GetSexRatio(pokemon->getPokemonDataId());
    sex = pokemonCheckSexKotei(pokemon);
    if (sex < 0) {
        if (ratio > (u8)rnd) {
            sex = 1;
        } else {
            sex = 0;
        }
    }
    return sex;
}

extern "C" {

u8 pokemonGetSex(Pokemon* pokemon)
{
    u32 rnd;

    if (pokemon == 0) {
        return 2;
    }
    rnd = pokemon_GetRnd(pokemon);
    return _pokemonGetSexSub(pokemon, rnd);
}

u16 pokemonDoItemSoubi(Pokemon* pokemon, u16 itemDataId, u8 equip)
{
    if (pokemon == 0) {
        return 0;
    }
    if (equip == 0) {
        itemDataId = pokemonGetSoubiItemDataId(pokemon);
        pokemon_SetItemDataId(pokemon, 0);
    } else {
        pokemon_SetItemDataId(pokemon, itemDataId);
    }
    return itemDataId;
}

u16 pokemonGetSoubiItemDataId(Pokemon* pokemon)
{
    return pokemon_GetItemDataId(pokemon);
}

u16 pokemonGetSoubiItemSoubiDataId(Pokemon* pokemon)
{
    u16 item = pokemonGetSoubiItemDataId(pokemon);
    if (item == 0) {
        return 0;
    }
    return itemDB_GetItemSoubiDataId(item);
}

u16 pokemonGetSoubiItemBuff(Pokemon* pokemon)
{
    u16 item;
    u16 soubi;

    item = pokemonGetSoubiItemDataId(pokemon);
    if (item == 0) {
        return 0;
    }
    if (dbgMenuFightGetSoubikoukaFlag() == 1) {
        soubi = itemDB_GetItemSoubiDataId(item);
        if (soubi == 0x1A || soubi == 0x1E) {
            return 99;
        }
    }
    return itemDB_GetBuff(item);
}

bool pokemonIsJoutaiNormal(Pokemon* pokemon)
{
    if (pokemon == 0) {
        return 0;
    }
    if (pokemonIsJoutaiDataId(pokemon, 3) == 1) {
        return 0;
    }
    if (pokemonIsJoutaiDataId(pokemon, 4) == 1) {
        return 0;
    }
    if (pokemonIsJoutaiDataId(pokemon, 5) == 1) {
        return 0;
    }
    if (pokemonIsJoutaiDataId(pokemon, 6) == 1) {
        return 0;
    }
    if (pokemonIsJoutaiDataId(pokemon, 7) == 1) {
        return 0;
    }
    return pokemonIsJoutaiDataId(pokemon, 8) != 1;
}

u8 pokemonIsJoutaiKaragenki(Pokemon* pokemon)
{
    if (pokemon == 0) {
        return 0;
    }
    if (pokemonIsJoutaiDataId(pokemon, 3) == 1) {
        return 1;
    }
    if (pokemonIsJoutaiDataId(pokemon, 5) == 1) {
        return 1;
    }
    if (pokemonIsJoutaiDataId(pokemon, 6) == 1) {
        return 1;
    }
    return pokemonIsJoutaiDataId(pokemon, 4) == 1;
}

u8 pokemonIsNokoriHpFollowing(Pokemon* pokemon, u16 waru)
{
    u16 hp;
    u16 maxHp;

    if (waru == 0) {
        return 0;
    }
    if (pokemon == 0) {
        return 0;
    }
    hp = pokemon_GetHp(pokemon);
    maxHp = pokemon_GetMaxHp(pokemon);
    return hp <= maxHp / waru;
}

u16 pokemonGetMaxHpWaruValue(Pokemon* pokemon, u16 waru)
{
    u16 value;

    if (pokemon == 0) {
        return 0;
    }
    if (waru == 0) {
        return 0;
    }
    value = pokemon_GetMaxHp(pokemon) / waru;
    if (value == 0) {
        value = 1;
    }
    return value;
}

u16 pokemonGetNowHpWaruValue(Pokemon* pokemon, u16 waru, u16 wazaDataId)
{
    u16 value;

    if (pokemon == 0) {
        return 0;
    }
    if (waru == 0) {
        return 0;
    }
    value = pokemon_GetHp(pokemon) / waru;
    if (value == 0 && wazaDataId != 0x175 && wazaDataId != 0x167) {
        value = 1;
    }
    return value;
}

s32 pokemonGetNowHpPercentage(Pokemon* pokemon)
{
    u16 hp;
    u16 maxHp;

    if (pokemon == 0) {
        return 0;
    }
    hp = pokemon_GetHp(pokemon);
    maxHp = pokemon_GetMaxHp(pokemon);
    return hp * 100 / maxHp;
}

u32 pokemonGetLevelToExp(Pokemon* pokemon, u8 level)
{
    if (pokemon == 0) {
        return 0;
    }
    return _pokemonGetLevelToExp(pokemonDB_GetGrowDataId(pokemon_GetPokemonDataId(pokemon)), level);
}

void pokemonGetEffortFromPokemon(Pokemon* pokemon, u16 itemSoubiDataId, u8 machoBrace, u16 enemyDataId)
{
    EffortEntry table[6] = {
        { 0x8D, 0x0A, 0 },
        { 0x8E, 0x0B, 0 },
        { 0x8F, 0x0C, 0 },
        { 0x90, 0x0D, 0 },
        { 0x91, 0x0E, 0 },
        { 0x92, 0x0F, 0 },
    };
    u8 i;
    u16 give;
    u16 total;
    u8 mult;

    if (pokemon && pokemonCheckFightOut(pokemon)) {
        mult = 1;
        total = 0;
        for (i = 0; i < 6; i++) {
            table[i].value = pokemonGetStatus(pokemon, 0, table[i].effortKind, 0);
            total += table[i].value;
        }
        if (machoBrace == 1) {
            mult = 2;
        }
        for (i = 0; i < 6; i++) {
            if (total >= 0x1FE) {
                break;
            }
            give = mult * (u16)pokemonGetStatus(0, enemyDataId, table[i].giveKind, 0);
            if (itemSoubiDataId == 0x18) {
                give *= 2;
            }
            if (total + give > 0x1FE) {
                give -= total + give - 0x1FE;
            }
            if (table[i].value + give > 0xFF) {
                give -= table[i].value + give - 0xFF;
            }
            total += give;
            table[i].value += give;
            pokemonSetStatus(pokemon, 0, table[i].effortKind, 0, table[i].value);
        }
    }
}

u8 pokemonCheckCanGetFriend(Pokemon* pokemon, u16 filterId)
{
    if (pokemonCheckValid(pokemon) == 0) {
        return 0;
    }
    if (pokemon_GetPokemonDataId(pokemon) == 0x19C) {
        return 0;
    }
    if (pokemon_GetTamagoFlag(pokemon) == 1) {
        return 0;
    }
    if (filterId != 6 && filterId != 7 && filterId != 8 && pokemon_GetHinsi(pokemon) == 1) {
        return 0;
    }
    return 1;
}

void pokemonGetFriendFormPokemonFriendFilterId(Pokemon* pokemon, u16 itemDataId, u16 filterId)
{
    int friendLevel;
    int value;
    int pool;
    u8 rank;

    if (pokemon && pokemonCheckCanGetFriend(pokemon, filterId)) {
        friendLevel = pokemon_GetFriend(pokemon);
        if (pokemonIsDarkPokemon(pokemon) == 1) {
            friendLevel += pokemon_GetPoolFriend(pokemon);
        }
        rank = 0;
        if (friendLevel >= 100) {
            rank = 1;
        }
        if (friendLevel >= 200) {
            rank++;
        }
        if (filterId == 5 && (HSD_Rand() & 1)) {
            return;
        }
        value = pokemonFriendFilterDataBiosGetValue(pokemonFriendFilterDataBiosGetPtr(filterId), rank);
        if (value > 0 && itemDataId == 0x1B) {
            value = value * 150 / 100;
        }
        if (value > 0 && pokemon_GetCatchBallId(pokemon) == 0xB) {
            value++;
        }
        if (pokemonIsDarkPokemon(pokemon) == 1) {
            if (pokemonGetDarkPokemonLevel(pokemon) >= 2) {
                pool = pokemon_GetPoolFriend(pokemon);
                pool += value * 80 / 100;
                if (pool < 0) {
                    pool = 0;
                }
                if (pool > 255) {
                    pool = 255;
                }
                pokemon_SetPoolFriend(pokemon, pool);
            }
        } else {
            friendLevel += value;
            if (friendLevel < 0) {
                friendLevel = 0;
            }
            if (friendLevel > 255) {
                friendLevel = 255;
            }
            pokemon_SetFriend(pokemon, friendLevel);
        }
    }
}

u8 pokemonGetAnnonKatati(u32 rnd)
{
    return ((rnd >> 18 & 0xC0) | (rnd >> 12 & 0x30) | (rnd >> 6 & 0xC) | (rnd & 3)) % 28;
}

u8 pokemonGetDeoxysSel(u8 controllerId)
{
    if (fightFloor_GetFightKindRegulationFlag(0) == 0) {
        return 0;
    }
    if (menuCBRule_DEOKISISUCamouflage() == 0) {
        return 0;
    }
    switch (menuGBACGetRomVer(controllerId - 1)) {
    case 1:
    case 2:
        return 0;
    case 3:
        return 1;
    case 4:
        return 2;
    case 5:
        return 3;
    default:
        return 0;
    }
}

u8 pokemonGetFightPokemonDeoxysSel(FightPokemon* fightPokemon)
{
    return pokemonGetDeoxysSel(fightTrainer_GetControllerId(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fightPokemon)));
}

void pokemonSetSequenceStatus(Pokemon* pokemon, u32 sequence)
{
    if (pokemonIsJoutaiDataId(pokemon, 8) == 1) {
        Sequence_SetStatus(sequence, 1);
    }
    if (pokemonIsJoutaiDataId(pokemon, 7) == 1) {
        Sequence_SetStatus(sequence, 2);
    }
    if (pokemonIsJoutaiNormal(pokemon) == 1) {
        Sequence_ResetStatus(sequence, 1);
        Sequence_ResetStatus(sequence, 2);
    }
}

u32 pokemonCreateSequence(FightPokemon* fightPokemon)
{
    u32 sequence;
    u16 dataId;
    Pokemon* pokemon;
    u32 rnd;
    u32 pkx;

    pokemon = fightPokemonGetPokemonPtr(fightPokemon);
    rnd = pokemon_GetRnd(pokemon);
    dataId = pokemon_GetPokemonDataId(pokemon);
    if (pokemonDataCheckValid(0, dataId) == 0) {
        return 0;
    }
    pkx = pokemonDB_GetPkxDataId(dataId);
    switch (pkx) {
    case 0xC9:
        rnd = pokemonGetAnnonKatati(rnd);
        break;
    case 0x19A:
        rnd = pokemonGetFightPokemonDeoxysSel(fightPokemon);
        break;
    case 0xF9:
        if (pokemonIsDarkPokemon(pokemon) == 1) {
            pkx = 0x1A1;
        }
        break;
    }
    sequence = Sequence_LoadPokemon(pkx, rnd, pokemonCheckRare(pokemon));
    pokemonSetSequenceStatus(pokemon, sequence);
    return sequence;
}

void pokemonReplace(Pokemon* a, Pokemon* b)
{
    Pokemon tmp;

    if (a && b) {
        pokemonBiosCopy(&tmp, a);
        pokemonBiosCopy(a, b);
        pokemonBiosCopy(b, &tmp);
    }
}

u8 pokemonCheckInfectPokerus(Pokemon* pokemon, u8 checkCured)
{
    u8 pokerus;

    if (checkCured == 0) {
        pokerus = pokemon_GetPokerus(pokemon);
    } else {
        pokerus = pokemon_GetPokerus(pokemon) & 0xF;
    }
    if (pokerus) {
        return 1;
    }
    return 0;
}

void pokemonInitJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId)
{
    u16 status;

    if (pokemon) {
        status = joutaiDataBiosGetStatus(joutaiDataId);
        if (status == 0xC8) {
            pokemon->setReversMode(false);
        } else if (status == 0x7C) {
            pokemon->initCondition();
        }
    }
}

bool pokemonIsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId)
{
    u16 status;

    if (pokemon == 0) {
        return 0;
    }
    status = joutaiDataBiosGetStatus(joutaiDataId);
    if (status == 0xC8) {
        if (joutaiDataId == (u16)(pokemon->isReversMode() ? 0x3E : 0)) {
            return 1;
        }
        return 0;
    }
    if (status == 0x7C) {
        return pokemon->getCondition() == joutaiDataId;
    }
    return 0;
}

u8 pokemonCheckWriteJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId)
{
    static const u8 table[] = { 0x00, 0x3E, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF };
    const u8* p;

    if (pokemon == 0) {
        return 1;
    }
    for (p = table; *p != 0xFF; p++) {
        if (joutaiDataId == *p) {
            return 2;
        }
    }
    return 1;
}

void pokemonWriteJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId)
{
    u16 status;
    u8 count;

    if (pokemon) {
        status = joutaiDataBiosGetStatus(joutaiDataId);
        if (status == 0xC8) {
            pokemon->setReversMode(joutaiDataId == 0x3E);
        }
        if (status == 0x7C) {
            count = 0;
            if (joutaiDataId == 4) {
                count = pokemon->getConditionCount();
            }
            pokemon->initCondition();
            pokemon->setCondition(joutaiDataId);
            if (joutaiDataId == 8) {
                pokemon->setConditionTurn(kaisuuGetKaisuu(joutaiDataBiosGetKaisuuDataId(joutaiDataId)));
            }
            if (joutaiDataId == 4) {
                pokemon->setConditionCount(joutaiDataBiosGetMaxCount(joutaiDataId) < count + 1 ? joutaiDataBiosGetMaxCount(joutaiDataId) : count + 1);
            }
        }
    }
}

s32 pokemonGetCountAsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId)
{
    if (pokemon == 0) {
        return -1;
    }
    if (joutaiDataBiosGetStatus(joutaiDataId) == 0x7C) {
        return pokemon->getConditionCount();
    }
    return -1;
}

void pokemonSetCountAsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId, u32 value)
{
    if (pokemon && joutaiDataBiosGetStatus(joutaiDataId) == 0x7C) {
        pokemon->setConditionCount(value);
    }
}

s32 pokemonGetKaisuuJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId)
{
    if (pokemon == 0) {
        return 0;
    }
    if (joutaiDataBiosGetStatus(joutaiDataId) == 0x7C) {
        return pokemon->getConditionTurn();
    }
    return -1;
}

s32 pokemonGetNowKaisuuJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId)
{
    if (pokemon == 0) {
        return -1;
    }
    if (joutaiDataBiosGetStatus(joutaiDataId) == 0x7C) {
        return pokemon->getConditionTurnNow();
    }
    return -1;
}

void pokemonSetNowKaisuuJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId, u32 value)
{
    if (pokemon && joutaiDataBiosGetStatus(joutaiDataId) == 0x7C) {
        pokemon->setConditionTurnNow(value);
    }
}

void pokemonSetKaisuuJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId, u32 value)
{
    if (pokemon && joutaiDataBiosGetStatus(joutaiDataId) == 0x7C) {
        pokemon->setConditionTurn(value);
    }
}

void pokemonCopyJoutaiDataId(Pokemon* dst, Pokemon* src, u16 joutaiDataId)
{
    u16 status;

    if (dst == 0 || src == 0) {
        return;
    }
    status = joutaiDataBiosGetStatus(joutaiDataId);
    if (status == 0xC8) {
        dst->setReversMode(src->isReversMode());
    } else if (status == 0x7C) {
        dst->copyCondition(src);
    }
}

u8 pokemonIsHpMantan(Pokemon* pokemon)
{
    u16 hp;
    u16 maxHp;

    if (pokemon == 0) {
        return 0;
    }
    hp = pokemon_GetHp(pokemon);
    maxHp = pokemon_GetMaxHp(pokemon);
    return hp == maxHp;
}

u32 pokemonGetJoutaiDataId(Pokemon* pokemon)
{
    if (pokemon == 0) {
        return 0;
    }
    return pokemon->getCondition();
}

u16 pokemonGetJoutaiMenuSpriteId(Pokemon* pokemon)
{
    int i;

    if (pokemon == 0) {
        return 0;
    }
    for (i = 0; spriteTbl[i][0] != 0; i++) {
        if (spriteTbl[i][0] == pokemon->getCondition()) {
            return spriteTbl[i][1];
        }
    }
    return 0;
}

u32 pokemonGetJoutaiMsgId(Pokemon* pokemon)
{
    if (pokemon == 0) {
        return 0;
    }
    if (pokemon->getCondition() == 0) {
        return 0;
    }
    return joutaiDataBiosGetName(pokemon->getCondition());
}

s32 pokemonGetTasteLike(Pokemon* pokemon, u32 taste)
{
    u32 seikaku;

    if (pokemon == 0) {
        return -1;
    }
    seikaku = pokemon_GetSeikaku(pokemon);
    return tasteDataGetAisyou(tasteDataGetPtr(taste), seikaku);
}

u32 pokemonGetNowLevelToExp(Pokemon* pokemon)
{
    u8 growDataId;
    u8 level;

    growDataId = pokemonDB_GetGrowDataId(pokemon_GetPokemonDataId(pokemon));
    level = pokemon_GetLevel(pokemon);
    return _pokemonGetLevelToExp(growDataId, level);
}

bool pokemonDataCheckValid(Pokemon* pokemon, u16 pokemonDataId)
{
    if (pokemonDataId == 0) {
        return 0;
    }
    if (pokemonDB_GetName(pokemonDataId) == 0) {
        return 0;
    }
    return pokemonDataId < *pokemon_data_number;
}

void pokemonGetMezamerupower(Pokemon* pokemon, u16* power, u16* zokusei)
{
    u8 hp = pokemon_GetMaxHpRnd(pokemon);
    u8 atk = pokemon_GetPhyAtkRnd(pokemon);
    u8 def = pokemon_GetPhyDefRnd(pokemon);
    u8 spa = pokemon_GetSpeAtkRnd(pokemon);
    u8 spd = pokemon_GetSpeDefRnd(pokemon);
    u8 spe = pokemon_GetNimblenessRnd(pokemon);
    u8 typeBits;
    u8 powerBits;
    u16 type;
    u16 pow;

    typeBits = (hp & 1) | ((atk & 1) << 1) | ((def & 1) << 2) | ((spe & 1) << 3) | ((spa & 1) << 4) | ((spd & 1) << 5);
    powerBits = ((hp >> 1) & 1) | (atk & 2) | ((def & 2) << 1) | ((spe & 2) << 2) | ((spa & 2) << 3) | ((spd & 2) << 4);
    pow = powerBits * 40 / 63 + 30;
    type = (u8)(typeBits * 15 / 63 + 1);
    if (type >= 9) {
        type++;
    }
    if (power) {
        *power = pow;
    }
    if (zokusei) {
        *zokusei = type;
    }
}

void pokemonAllKaihuku(Pokemon* pokemon)
{
    u8 i;

    u16 maxHp;
    u8 maxPp;

    if (pokemon) {
        maxHp = pokemon_GetMaxHp(pokemon);
        pokemon_SetHp(pokemon, maxHp);
        for (i = 0; i < 4; i++) {
            if (pokemonWazaCheckValid(pokemon, i) == 1) {
                maxPp = pokemonWazaGetMaxPP(pokemon, i);
                pokemon_SetPokemonWazaPp(pokemon, i, maxPp);
            }
        }
        pokemonInitJoutaiDataId(pokemon, 3);
        pokemonInitJoutaiDataId(pokemon, 4);
        pokemonInitJoutaiDataId(pokemon, 5);
        pokemonInitJoutaiDataId(pokemon, 6);
        pokemonInitJoutaiDataId(pokemon, 7);
        pokemonInitJoutaiDataId(pokemon, 8);
    }
}

u8 pokemonCheckSetMonohiroi(Pokemon* pokemon)
{
    u16 items[18] = {
        0x0D, 0x0E, 0x16, 0x03, 0x12, 0x0F, 0x4B, 0x17, 0x02,
        0x15, 0x44, 0x40, 0x18, 0x3F, 0x13, 0x19, 0x45, 0x25,
    };
    u16 rareItems[11] = {
        0x15, 0x6E, 0xBB, 0x13, 0x22, 0xB4, 0x14C, 0x24, 0x121, 0xC8, 0x13A,
    };
    u8 rates[9] = { 30, 40, 50, 60, 70, 80, 90, 94, 98 };
    u32 rnd;
    u16 item;
    u16 i;
    u8 index;

    if (pokemonGetTokuseiDataId(pokemon) == 0x35 && pokemonGetSoubiItemDataId(pokemon) == 0 && (u16)HSD_Rand() % 10 == 0) {
        rnd = (u16)HSD_Rand() % 100;
        item = 0;
        index = (pokemon_GetLevel(pokemon) - 1) / 10;
        if (index >= 10) {
            index = 9;
        }
        for (i = 0; i < 9; i++) {
            if (rates[i] > rnd) {
                item = items[index + i];
                break;
            }
            if (rnd >= 98 && rnd <= 99) {
                item = rareItems[index + (99 - rnd)];
                break;
            }
        }
        if (item) {
            pokemonDoItemSoubi(pokemon, item, 1);
            return 1;
        }
    }
    return 0;
}

void pokemonToMenuWazaStatus(Pokemon* pokemon, MenuWazaStatus* status)
{
    u16 waza;
    u8 zokusei;
    u8 i;
    MenuWazaStatusEntry* entry;

    memset(status, 0, sizeof(MenuWazaStatus));
    status->nickname = pokemon_GetNicknamePtr(pokemon);
    for (i = 0; i < 4; i++) {
        entry = &status->waza[i];
        if (pokemonWazaCheckValid(pokemon, i) == 0) {
            entry->name = 0;
            entry->zokuseiName = 0;
            entry->zokusei = 0;
            entry->maxPp = 0;
            entry->pp = 0;
        } else {
            waza = pokemon_GetPokemonWazaDataId(pokemon, i);
            zokusei = wazaDB_GetZokuseiDataId(waza);
            entry->name = GSmsgGetGSchar(wazaDB_GetName(waza));
            entry->zokuseiName = GSmsgGetGSchar(zokuseiBiosGetName(zokusei));
            entry->zokusei = (u8)pokemonWazaGetZokusei(pokemon, i);
            entry->maxPp = pokemonWazaGetMaxPP(pokemon, i);
            entry->pp = pokemon_GetPokemonWazaPp(pokemon, i);
        }
    }
}

void pokemonToMenuPokemonStatusSubBar(Pokemon* pokemon, MenuPokemonStatus* status)
{
    u8 level;
    u32 baseExp;

    level = pokemon_GetLevel(pokemon);
    baseExp = pokemonGetLevelToExp(pokemon, level);
    if (pokemonIsDarkPokemon(pokemon) == 0) {
        status->barMax.exp = pokemonGetLevelToExp(pokemon, level + 1) - baseExp;
        status->barNow.exp = pokemon_GetExp(pokemon) - baseExp;
    } else {
        status->barMax.dp = darkPokemonBiosGetDarkPoint(pokemon_GetDarkpokemonDataId(pokemon));
        status->barNow.dp = pokemonGetDp(pokemon);
    }
}

void pokemonToMenuPokemonStatus(Pokemon* pokemon, FightPokemon* fightPokemon, MenuPokemonStatus* status, u8 param_4)
{
    pokemon_GetPokemonDataId(pokemon);
    GScharCpy(status->name, pokemon_GetNicknamePtr(pokemon));
    status->level = pokemon_GetLevel(pokemon);
    status->maxHp = pokemon_GetMaxHp(pokemon);
    status->hp = pokemon_GetHp(pokemon);
    pokemonToMenuPokemonStatusSubBar(pokemon, status);
    status->joutaiSpriteId = pokemonGetJoutaiMenuSpriteId(pokemon);
    if (fightPokemon == 0) {
        status->faceId = menuFaceGetID(pokemon);
    } else {
        status->faceId = menuFaceGetID3(pokemon, pokemonGetFightPokemonDeoxysSel(fightPokemon), param_4);
    }
    status->sex = menuSubGetPokemonSexForFightDisp(pokemon);
    if (pokemonIsDarkPokemon(pokemon) == 0) {
        status->dark = 0;
    } else if (pokemonIsJoutaiDataId(pokemon, 0x3E) == 0) {
        status->dark = 1;
    } else {
        status->dark = 2;
    }
    status->itemDataId = pokemon_GetItemDataId(pokemon);
}

void pokemonSetDarkPokemonStatus(Pokemon* pokemon, u16 darkPokemonDataId)
{
    u8 i;
    u16 waza;
    DarkPokemon* darkPokemon;

    if (pokemon) {
        pokemonInitDarkPokemon(pokemon);
        pokemon_SetDarkpokemonDataId(pokemon, darkPokemonDataId);
        pokemonSetDp(pokemon, darkPokemonBiosGetDarkPoint(darkPokemonDataId));
        for (i = 0; i < 4; i++) {
            pokemonWazaCreate(pokemon, i, 0x176);
            waza = darkPokemonBiosGetTemotiDarkWaza(darkPokemonDataId, i);
            if (waza != 0 && waza != 0x176) {
                pokemonWazaCreate(pokemon, i, waza);
            }
        }
        pokemon->setReversMode(false);
        darkPokemon = pokemon->getDarkPokemon();
        if (darkPokemon) {
            darkPokemon->setDarkPokemonID(darkPokemonDataId);
        }
    }
}

u8 pokemonIsDarkPokemon(Pokemon* pokemon)
{
    return pokemon_GetDarkFlag(pokemon);
}

f32 pokemonGetDp(Pokemon* pokemon)
{
    if (pokemon == 0) {
        return 0.0f;
    }
    return pokemonBiosGetDp(pokemon);
}

void pokemonSetDp(Pokemon* pokemon, f32 value)
{
    if (pokemon) {
        pokemonBiosSetDp(pokemon, value);
    }
}

void pokemonAddDp(Pokemon* pokemon, f32 value)
{
    f32 dp;

    if (pokemon) {
        dp = pokemonGetDp(pokemon);
        dp += value;
        if (dp < 0.0f) {
            dp = 0.0f;
        }
        pokemonSetDp(pokemon, dp);
    }
}

void pokemonAddDpFormPokemonDpFilterId(Pokemon* pokemon, u16 itemDataId, u16 filterId)
{
    PokemonSeikakuDataBios* seikaku;
    s8 rateId = 0;
    PokemonSeikakuRateBios* rate;
    ItemData* item;
    u8 kake;
    u8 waru;
    f32 dp;

    if (pokemonIsDarkPokemon(pokemon) == 0) {
        return;
    }
    seikaku = pokemonSeikakuDataBiosGetPtr(pokemon_GetSeikaku(pokemon));
    if (seikaku == 0) {
        return;
    }
    dp = pokemonDpFilterDataBiosGetValue(pokemonDpFilterDataBiosGetPtr(filterId));
    if (filterId == 4) {
        item = itemDataBiosGetPtr(itemDataId);
        if (item == 0) {
            return;
        }
        if (itemDataBiosGetKind(item) != 6) {
            return;
        }
        dp *= itemDataBiosGetBuff(item);
    }
    if (filterId == 5) {
        dp = -1.0f * pokemonGetDp(pokemon);
    }
    if (filterId == 0) {
        rateId = pokemonSeikakuDataBiosGetReliveFightout(seikaku);
    } else if (filterId == 1) {
        rateId = pokemonSeikakuDataBiosGetReliveWalk(seikaku);
    } else if (filterId == 3) {
        rateId = pokemonSeikakuDataBiosGetReliveSodateya(seikaku);
    } else if (filterId == 4) {
        rateId = pokemonSeikakuDataBiosGetReliveNadenade(seikaku);
    } else if (filterId == 2) {
        dp = -3.0f;
        rateId = pokemonSeikakuDataBiosGetReliveCall(seikaku);
    }
    if (rateId != 0) {
        rate = pokemonSeikakuRateDataBiosGetPtr((u8)rateId);
        if (rate == 0) {
            return;
        }
        kake = pokemonSeikakuRateDataBiosGetKake(rate);
        waru = pokemonSeikakuRateDataBiosGetWaru(rate);
        if (waru != 0) {
            dp *= kake;
            dp /= waru;
        } else {
            return;
        }
    }
    dp *= 100.0f;
    pokemonAddDp(pokemon, dp);
}

u8 pokemonGetDarkPokemonLevel(Pokemon* pokemon)
{
    u16 initDp;
    f32 dp;
    f32 percent;

    if (pokemon == 0) {
        return 7;
    }
    if (pokemonIsDarkPokemon(pokemon) == 1) {
        initDp = pokemon_GetInitDp(pokemon);
        if (initDp == 0) {
            initDp = 1;
        }
        dp = pokemonGetDp(pokemon);
        if (dp < 0.0f) {
            percent = 0.0f;
        } else {
            percent = 100.0f * dp / initDp;
        }
        if (percent >= 99.9f) {
            return 0;
        }
        if (percent >= 80.0f) {
            return 1;
        }
        if (percent >= 60.0f) {
            return 2;
        }
        if (percent >= 40.0f) {
            return 3;
        }
        if (percent >= 20.0f) {
            return 4;
        }
        if (percent > 0.0f) {
            return 5;
        }
        if (percent == 0.0f) {
            return 6;
        }
        return 7;
    }
    return 7;
}

u8 pokemonGetDarkPokemonHyperJoutaiKakuritu(Pokemon* pokemon)
{
    u8 table[5][5] = {
        { 0, 0, 0, 0, 0 },
        { 10, 10, 10, 5, 2 },
        { 20, 15, 15, 10, 5 },
        { 35, 25, 20, 15, 10 },
        { 50, 40, 30, 20, 15 },
    };
    u8 level;
    u8 pattern;

    pattern = darkPokemonGetDarkPokemon(pokemon_GetDarkpokemonDataId(pokemon))->getReversPattern();
    level = pokemonGetDarkPokemonLevel(pokemon);
    if (pokemon == 0) {
        return 0;
    }
    if (pokemonIsDarkPokemon(pokemon) == 0) {
        return 0;
    }
    if (level > 4) {
        level = 4;
    }
    if (pattern > 4) {
        pattern = 4;
    }
    if (level <= 4 && pattern < 5) {
        return table[level][pattern];
    }
    return 0;
}

u8 pokemonGetDarkPokemonCallKakuritu(Pokemon* pokemon)
{
    return 100;
}

void pokemonPlayVoice(Pokemon* pokemon)
{
    PokemonData* data;

    if (pokemon) {
        data = pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(pokemon));
        if (data) {
            GSsndPlay(pokemonDataBiosGetVoice(data), 0, 0);
        }
    }
}

void pokemonWazaCopy(Pokemon* pokemon, u16 dst, u16 src)
{
    PokemonWaza* dstWaza;
    PokemonWaza* srcWaza;

    if (pokemon) {
        dstWaza = pokemonBiosGetPokemonWazaPtr(pokemon, dst, 0);
        srcWaza = pokemonBiosGetPokemonWazaPtr(pokemon, src, 0);
        pokemonWazaBiosCopy(dstWaza, srcWaza);
    }
}

void pokemonWazaForget(Pokemon* pokemon, u32 wazaNum)
{
    u16 i;

    pokemonWazaInit(pokemon, wazaNum);
    for (i = wazaNum; i < 3; i++) {
        if (pokemonWazaCheckValid(pokemon, i + 1) == 0) {
            break;
        }
        pokemonWazaCopy(pokemon, i, i + 1);
    }
    pokemonWazaInit(pokemon, i);
}

s32 pokemonGetWazaCount(Pokemon* pokemon)
{
    int i;
    s32 count = 0;

    if (pokemonCheckValid(pokemon) == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (pokemonWazaCheckValid(pokemon, i)) {
            count++;
        }
    }
    return count;
}

u16 fightOutPokemon_GetKanseiSndId(FightOutPokemon* fightOutPokemon)
{
    return pokemonDB_GetShout(figthOutPokemonGetPokemonDataId(fightOutPokemon));
}

}
