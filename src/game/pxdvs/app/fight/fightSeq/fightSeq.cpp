#include <dolphin/types.h>

struct FightOutPokemon {
    u8 pad[1];
};
struct FightPokemon;
struct FightTrainer;
struct Pokemon;
struct FIGHT_WAZA;
struct FIGHT_FLOOR;
struct FightWaza;
struct FightJoutai;
struct WazaSequence;
struct Sequence;
struct FIGHT_TRAINER;
struct TasteData;
struct HeroPtr;
struct FightTarget;

extern "C" {
void* GSmsgGetGSchar(void*);
void GSthreadSwitch(void);
u16 HSD_Rand(void);
void Sequence_Free(Sequence*);
void Sequence_GetPosition(Sequence*, void*);
void Sequence_GetRotation(Sequence*, void*);
WazaSequence* Sequence_GetWaza(Sequence* seq, u16 id, s32 kind);
Sequence* Sequence_LoadTrainer(u8);
void Sequence_LoadWaza(Sequence* seq, u16 id, u16 kind, u8 flag);
void Sequence_SetPosition(Sequence*, void*);
void Sequence_SetRotation(Sequence*, void*);
void Sequence_SetVisibility(Sequence* seq, u8 visible);
void WazaSequence_Free(WazaSequence* waza);
u8 WazaSequence_IsActive(WazaSequence* waza);
void WazaSequence_Start(WazaSequence* waza, s32 flag);
void battleGridBackupModelVisibilityFlags(void);
void battleGridResetModelVisibilityFlags();
void battleGridRestoreModelVisibilityFlags(void);
void battleGridStoreModelVisibilityFlags(void);
u32 fightAbicntDoKakeWaru(u16 id, u32 value);
void fightAi_FixedActIrekaeInit(FightOutPokemon*);
u16 fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(FIGHT_FLOOR* floor, u16 joutaiId);
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(FIGHT_FLOOR*, u16, u8, FightOutPokemon*);
u8 fightFloorCheckWriteJoutaiDataId(u32, u32);
u16 fightFloorCreateFightOutPokemonPtrAry(FIGHT_FLOOR* floor);
FightOutPokemon* fightFloorGetFightOutPokemonPtrRandom(FIGHT_FLOOR* floor, bool fightOut, u8 mode, FightOutPokemon* pokemon);
FightTrainer* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*, FightOutPokemon*);
HeroPtr* fightFloorGetFightOutPokemonPtrToHeroPtr(FIGHT_FLOOR*, FightOutPokemon*);
u32 fightFloorGetFightPokemonPtrToFightTrainerPtr(u32, FightPokemon*);
FightTrainer* fightFloorGetGcHeroFightTrainerPtr(s32);
s8 fightFloorGetKaisuuJoutaiDataId(FightJoutai* joutai, u16 joutaiId);
s8 fightFloorGetNowKaisuuJoutaiDataId(FightJoutai* joutai, u16 joutaiId);
u32 fightFloorGetNowTenkouDataId(u32, u32);
u16 fightFloorGetValidFightOutPokemonCount(FIGHT_FLOOR* floor, u8 mode, FightOutPokemon* pokemon, u8 fightOut);
void* fightFloorGetValidFightSidePtr(void*, u16);
void fightFloorInitJoutaiDataId(FightJoutai* joutai, u16 joutaiId);
u8 fightFloorIsJoutaiDataId(FightJoutai*, u16);
u8 fightFloorLoopValidFightOutPokemon(u8, s32 (*)(void*, u16, void*), void*, u8);
void fightFloorSetNowKaisuuJoutaiDataId(FightJoutai* joutai, u16 joutaiId, s8 kaisuu);
void fightFloorSortFightOutPokemonPtrAry(FIGHT_FLOOR* floor, u8 useAction);
void fightFloorWriteJoutaiDataId(u32, u32, u32);
FightOutPokemon* fightFloor_GetAttackPokemonPtr(u32);
u32 fightFloor_GetEncountDataId(s32);
u8 fightFloor_GetFightKindDarkpokemonHypermodeFlag(u32);
u8 fightFloor_GetFightKindDoBadgeCheckFlag(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindDoHizukiMiyaburiFlag(u32);
s32 fightFloor_GetFightKindDoItemSoubiTokukoutokubouupFlag(u32);
u16 fightFloor_GetFightSideFightOutPokemonSideMax(u32);
u32 fightFloor_GetFightType(u32);
void fightFloor_SetAppointItemDataId(u32 floor, s32 id);
void fightFloor_SetAppointPokemonPtr(s32, FightOutPokemon*);
void fightFloor_SetAttackPokemonPtr(s32, FightOutPokemon*);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(s32, FightOutPokemon*);
void fightFloor_SetDefensePokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon);
void fightFloor_SetItemPokemonPtr(u32, FightOutPokemon*);
void fightFloor_SetKizetuPokemonPtr(u32, FightOutPokemon*);
void fightFloor_SetTuikakoukaPokemonPtr(s32, FightOutPokemon*);
u16 fightGetFightResultId(void);
void fightMenuCloseMsg(void);
void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon*, u8, u32);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(s32, FightOutPokemon*, u8, u32, u32);
void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon*, u8, u32);
void fightMenuFightOutPokemonRenewStatusMenu(FightOutPokemon* fop, u8 type, s32 flag);
u8 fightMenuOpenMsg(u32);
void fightMsgctrlSetValue(s32 id, u32 value);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightOutPokemonCheckNoAttackFlag(FightOutPokemon* fop);
u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonCopyAllAbiCnt(FightOutPokemon* dst, FightOutPokemon* src);
void fightOutPokemonCopyJoutaiDataId(FightOutPokemon* dst, FightOutPokemon* src, u16 id);
void fightOutPokemonDarkPokemonEffect(FightOutPokemon* fop, u8 openMenu, u8 kind, u8 mode);
void fightOutPokemonDarkPokemonKaijoEffect(FightOutPokemon*, u8, u8, u8, u16, u8);
s32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
s16 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon*, u16);
u16 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
s8 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon*, u16);
void* fightOutPokemonGetNicknamePtr(FightOutPokemon*);
s8 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon*, u16);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
s32 fightOutPokemonGetSoubiItemDataId(FightOutPokemon*);
u16 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon*);
s8 fightOutPokemonGetTasteLike(FightOutPokemon*, u16);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
u16 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon*, u16);
u16 fightOutPokemonGetWazaZokuseiDataId(FightOutPokemon* fop);
void fightOutPokemonInitFightPokemonEnemyAry(FightOutPokemon* fop, FightOutPokemon* target);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonInitJoutaiKeep(FightOutPokemon*);
u8 fightOutPokemonIsAlly(FightOutPokemon* fop, FightOutPokemon* other);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon*);
u8 fightOutPokemonIsHpMantan(FightOutPokemon* fop);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u8 fightOutPokemonIsJoutaiNormal(FightOutPokemon*);
u8 fightOutPokemonIsNokoriHpFollowing(FightOutPokemon* fop, u16 waru);
u8 fightOutPokemonIsUseHensinBuff(FightOutPokemon* fop);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon*, u32);
u16 fightOutPokemonMaxHpWaruValue(FightOutPokemon*, u16);
void fightOutPokemonResetSeqStatus(FightOutPokemon* fop, u16 id);
void fightOutPokemonSetHensinFightPokemonStatusId(FightOutPokemon* fop, u16 id, u8 toBuff);
void fightOutPokemonSetHensinPokemonStatusId(FightOutPokemon* fop, u16 id, s32 sub, u8 toBuff);
void fightOutPokemonSetNowKaisuuJoutaiDataId(FightOutPokemon*, u16, s8);
void fightOutPokemonSetOumuWazaDataId(FightOutPokemon* fop, FightOutPokemon* target, u16 waza);
void fightOutPokemonSetTokuseiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonSetZokuseiDataId(FightOutPokemon* fop, u8 idx, u16 zokusei);
void fightOutPokemonWriteJoutaiDataId(FightOutPokemon* fop, u16 id, u32 value);
u32 fightOutPokemon_GetAbicntPhyAtk(FightOutPokemon*);
u32 fightOutPokemon_GetAbicntPhyDef(FightOutPokemon*);
u32 fightOutPokemon_GetAbicntSpeAtk(FightOutPokemon*);
u32 fightOutPokemon_GetAbicntSpeDef(FightOutPokemon*);
u8 fightOutPokemon_GetDoIkakuFlag(FightOutPokemon*);
u8 fightOutPokemon_GetDoTraceFlag(FightOutPokemon*);
FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon*);
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon*);
s32 fightOutPokemon_GetKaigaraDamageValue(FightOutPokemon*);
u8 fightOutPokemon_GetKizetuFlag(FightOutPokemon*);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon*);
s16 fightOutPokemon_GetMyselfDamageAtkValue(FightOutPokemon*);
s16 fightOutPokemon_GetMyselfDamageSpeValue(FightOutPokemon*);
u32 fightOutPokemon_GetNamakeFlag(FightOutPokemon*);
u8 fightOutPokemon_GetPassPpdecFlag(FightOutPokemon*);
Sequence* fightOutPokemon_GetSequencePtr(FightOutPokemon*);
u32 fightOutPokemon_GetUseWazaDataId(FightOutPokemon*);
void fightOutPokemon_SetComboFuncId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetDoIkakuFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetDoTraceFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetKaigaraDamageValue(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetNamakeFlag(FightOutPokemon*, s32);
void fightOutPokemon_SetOumuWazaAllyDataId(FightTarget*, u16);
u8 fightPokemon_GetDarkOutFlag(FightPokemon*);
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon*);
void fightPokemon_SetDarkOutFlag(FightPokemon* fp, s32 value);
s32 fightSeqCondChgActTypeToPokemonStatusId(u8);
void fightSeqExec(void*, void*, u32);
void fightSeqPpdecMonomane(FightOutPokemon*, u8, u32);
u8 fightSeqRegulationOverTwoCheck(u32, FightOutPokemon*);
bool fightSeqSawaguCheck(FightOutPokemon*);
void fightSeqTuikaAct(u32, u32);
s8 fightSideGetKaisuuJoutaiDataId(FightOutPokemon*, u32);
s8 fightSideGetNowKaisuuJoutaiDataId(FightOutPokemon*, u32);
void fightSideInitJoutaiDataId(void*, u16);
u8 fightSideIsJoutaiDataId(void*, u32);
void fightSideSetNowKaisuuJoutaiDataId(FightOutPokemon*, u32, s8);
FightTarget* fightTargetGetPtr(u16 targetDataId, void* fightPokemon, u16 fightType);
FightOutPokemon* fightTargetGetPtrAsNowFightType(u32, FightOutPokemon*);
FightOutPokemon* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u16 targetId, u16 type);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u16);
u16 fightTrainer_GetFightTrainerDataId(FightTrainer*);
void* fightTrainer_GetHeroPtr(void*);
Sequence* fightTrainer_GetSequencePtr();
void fightTrainer_SetOkaneBai(FightTrainer* trainer, u8 value);
void fightWazaBiosCopy(void*, void*);
void fightWazaCreate(FightWaza*, u32, u16, u32, u32);
u8 fightWazaIsHit(FightWaza*);
u8 fightWaza_GetCritical(FightWaza*);
s32 fightWaza_GetDamage(FightWaza*);
void fightWaza_SetDamage(void*, s32);
s32 figthOutPokemonGetLevel(FightOutPokemon* fop);
u16 figthOutPokemonGetPokemonDataId(FightOutPokemon*);
s32 figthOutPokemonGetSoubiItemBuff(FightOutPokemon* fop);
u8 getHeroStyle__4HeroCFv(HeroPtr*);
u32 heroGetStatus(void*, u32, u32);
void* joutaiDataBiosGetName(u32);
void* memset(void*, int, u32);
void pokemonAddDpFormPokemonDpFilterId(Pokemon*, u32, u32);
u8 pokemonDB_GetTokuseiDataId(u16, u8);
u8 pokemonGetDarkPokemonHyperJoutaiKakuritu(Pokemon*);
void* pokemonGetJoutaiMsgId(Pokemon*);
u16 pokemonGetSoubiItemBuff(Pokemon* p);
u16 pokemonGetSoubiItemSoubiDataId(Pokemon*);
s32 pokemonGetStatus(void*, s32, s32, s32);
void pokemonInitJoutai(Pokemon*);
u8 pokemonIsDarkPokemon(Pokemon*);
u8 pokemonIsJoutaiNormal(Pokemon* p);
s8 pokemonSearchWazaDataId(Pokemon*, u16);
void pokemonSetStatus(void*, s32, s32, s32, u32);
void* pokemonTokuseiDataBiosGetName(void*);
void* pokemonTokuseiDataBiosGetPtr(u16);
u16 pokemon_GetHp(Pokemon*);
u16 pokemon_GetMaxHp(Pokemon*);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
u16 pokemon_GetPhyAtk(Pokemon* p);
u16 pokemon_GetPhyDef(Pokemon* p);
u16 pokemon_GetPokemonDataId(Pokemon*);
u16 pokemon_GetPokemonWazaDataId(Pokemon*, u16);
u8 pokemon_GetPokemonWazaPp(Pokemon* p, u16 banme);
u16 pokemon_GetSpeAtk(Pokemon* p);
u16 pokemon_GetSpeDef(Pokemon* p);
s32 pokemon_GetTokuseiFlag(Pokemon*);
void pokemon_SetPokemonWazaPp(Pokemon* p, u16 banme, u8 pp);
HeroPtr* savedataGetStatus(s32, s32);
void* tasteDataGetNigateMsgDataId(TasteData*);
TasteData* tasteDataGetPtr(u16);
u8 tenkouDataBiosGetSolarFlag(u8);
u8 wazaCheckDarkWaza(u16);
u8 wazaDB_GetBouon(s32);
s32 wazaDB_GetIryoku(u32 waza);
void* wazaDB_GetName(u16);
u8 wazaDB_GetOujanosirusi(s32);
s32 wazaDB_GetRangeId(u16);
u16 wazaDB_GetSeqId(u32);
u8 wazaDB_GetZokuseiDataId(u16);
void wazaSequenceSysFreeAllWaza(void);
s32 waza_GetZokuseiKindData(u16);
s32 zokuseiBiosGetWazaKind(u16);
extern u8 WAZA_Hensyoku[];
extern u8 WAZA_Samehada[];
extern u8 WAZA_Honoonokarada[];
extern u8 WAZA_MeromeroBody[];
u8 wazaDB_GetDageki(u16 id);
u8 fightOutPokemon_GetKonranMyselfAttackFlag(FightOutPokemon* fop);
u8 fightOutPokemonGetSex(FightOutPokemon* fop);
u32 zokuseiBiosGetName(u16 id);
extern u8 WAZA_AbareruEnd[];
extern u8 WAZA_AddNemuri2[];
extern u8 WAZA_Akumu[];
extern u8 WAZA_Amefuri[];
extern u8 WAZA_Amehurashi[];
extern u8 WAZA_Ameukezara[];
extern u8 WAZA_Bouon[];
extern u8 WAZA_Dappi[];
extern u8 WAZA_Dokudoku[];
extern u8 WAZA_EncoreEnd[];
extern u8 WAZA_GetEXP[];
extern u8 WAZA_Hare[];
extern u8 WAZA_HareEnd[];
extern u8 WAZA_Hideri[];
extern u8 WAZA_Horobinouta[];
extern u8 WAZA_Horobinoutaing[];
extern u8 WAZA_Ikaku[];
extern u8 WAZA_IkakuAct[];
extern u8 WAZA_ItemAbiKaifuku[];
extern u8 WAZA_ItemCondUp[];
extern u8 WAZA_ItemHPKaifuku[];
extern u8 WAZA_ItemHPKaifukuEveryTurn2[];
extern u8 WAZA_ItemHPKaifukuKonran[];
extern u8 WAZA_KanashibariEnd[];
extern u8 WAZA_Kasokusouti[];
extern u8 WAZA_Miraiyochi[];
extern u8 WAZA_Moraibi[];
extern u8 WAZA_MoraibiPPDec[];
extern u8 WAZA_NOKaifuku[];
extern u8 WAZA_NOKaifukuPPDec[];
extern u8 WAZA_Negaigoto[];
extern u8 WAZA_Newoharu[];
extern u8 WAZA_Noroi[];
extern u8 WAZA_Null[];
extern u8 WAZA_ReflecEnd[];
extern u8 WAZA_Revers[];
extern u8 WAZA_Sawagu[];
extern u8 WAZA_SawaguMezame[];
extern u8 WAZA_Shime[];
extern u8 WAZA_ShimeEnd[];
extern u8 WAZA_ShinpiEnd[];
extern u8 WAZA_Sinkuro[];
extern u8 WAZA_SpeabiNoJoutaiijou[];
extern u8 WAZA_Sunaokosi[];
extern u8 WAZA_Tenkiya[];
extern u8 WAZA_Trace[];
extern u8 WAZA_Tyosui[];
extern u8 WAZA_TyosuiPPDec[];
extern u8 WAZA_WeatherDamage[];
extern u8 WAZA_WeatherDamageEnd[];
extern u8 WAZA_Yadorigi[];
extern u8 WAZA_Yakedo[];
extern u8 WAZA_Zenmetsu[];
extern u32 ServerStatusFlag;
extern u8* UserWork;
extern u8* TSUIKASeqTbl[];
extern u8 ServerWork[8];
extern const u16 fight_seq_status_id[];
extern const u8 SoubiItemWazaTypePowUpTbl[];
extern u8 fight_seq_tuika_param;
extern s32 kureinSequencePtr;
extern Sequence* miyaburiSequencePtr;
extern u8* _wazaSeqAdrs;
extern s32 fight_seq_now_fight_action_ptr;
void fightSeq_CallWazaSeq(void*);
void fightSeqCheckSetHensinBuffToMotoFightPokemon(FightOutPokemon*, u16);
void fightSeqCheckSetHensinBuffToMotoPokemon(FightOutPokemon*, u16);
void fightSeqCheckZenmetu(void);
u8 fightSeqFightOutPokemonTokuseiCheckTenkiya(void);
u8 fightSeqSoubiItemCheckTurn(FightOutPokemon*, u8);
}

static s32 _fightSeqSoubiItemCheckWazaHitAfterAllSub(void*, u16, void*);
static s32 _fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAllSub(void*, u16, void*);
static s32 _fightSeqFightOutPokemonTokuseiCheckTraceSub(void*, u16, void*);
static s32 _fightSeqFightOutPokemonTokuseiCheckIkakuSub(void*, u16, void*);
static s32 _fightSeqFightOutPokemonTokuseiCheckTenkiyaSub(void*, u16, void*);
u8 fightSeqTokuseiTenkiyaAct(FightOutPokemon*);
static s32 _fightSeqGetExpCheckSubSoubiItemCheckTurn(void*, u16, void*);
static s32 _fightSeqGetExpCheckSub(void*, u16, void*);
static s32 _SideConditionCheck2SubHorobinouta(void*, u16, void*);
static s32 _SideConditionCheck2SubMiraiyoti(void*, u16, void*);
struct IrekaeArg {
    FightOutPokemon* p;
    s32 mode;
};
static s32 _fightSeqIrekaeInitSub(void*, u16, void*);
static s32 _fightSeqKizetuInitSub(void*, u16, void*);
static u8 _fightSeqInitFightOutPokemonJoutaiUserFightTargetId(FightOutPokemon*, FightOutPokemon*, u16, u16);
static u8 _fightSeqCheckFightOutPokemonJoutaiUserFightTargetId(FightOutPokemon*, FightOutPokemon*, u16, u16);
static s32 _fightSeqSideJoutaiCheckSub(void*, u16, void*);
static s32 _fightSeqSideJoutaiCheckSubSawagu(void*, u16, void*);

extern "C" {
void fightSeq_ClearUserWork(void) {
    memset(UserWork, 0, 1);
}
}

extern "C" {
void* fightSeq_GetWazaSeqPtr_u8(u8 idx) {
    return *(void**)(_wazaSeqAdrs + idx);
}
}

extern "C" {
void fightSeq_CallWazaSeqCustom(void* a, void* b, u32 c) {
    fightSeqExec(a, b, c);
}
}

extern "C" {
void fightSeq_CallWazaSeq(void* seq) {
    fightSeqExec((void*)fight_seq_now_fight_action_ptr, seq, 0);
}
}

extern "C" {
void fightSeq_JumpWazaSeq(void* target) {
    _wazaSeqAdrs = (u8*)target;
}
}

extern "C" {
void fightSeq_NextWazaSeq(s32 size) {
    _wazaSeqAdrs += size;
}
}

extern "C" {
void* fightSeq_GetWazaSeqAdr(s32 off) {
    return _wazaSeqAdrs + off;
}
}

extern "C" {
void* fightSeq_GetWazaSeq(void) {
    return _wazaSeqAdrs;
}
}

extern "C" {
void fightSeqSoubiItemCheckWazaHitAfterAll(void) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqSoubiItemCheckWazaHitAfterAllSub, 0, 0);
}
}

extern u8 WAZA_ItemNoMahi2[];
extern u8 WAZA_ItemNoDoku2[];
extern u8 WAZA_ItemNoYakedo2[];
extern u8 WAZA_ItemNoKoori2[];
extern u8 WAZA_ItemNoNemuri2[];
extern u8 WAZA_ItemNoKonran2[];
extern u8 WAZA_ItemNoJoutaiijou2[];
extern u8 WAZA_ItemAbiKaifuku2[];
static s32 _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(FightOutPokemon* p, u16 joutai, u8* ret);

static s32 _fightSeqSoubiItemCheckWazaHitAfterAllSub(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    u8 result;
    Pokemon* pokemon;
    u8* seq;
    u16 soubi;
    s32 itemId;
    u16 i;

    result = 0;
    pokemon = fightOutPokemonGetPokemonPtr(p);
    itemId = fightOutPokemonGetSoubiItemDataId(p);
    soubi = fightOutPokemonGetSoubiItemSoubiDataId(p);
    figthOutPokemonGetSoubiItemBuff(p);
    seq = 0;
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    fightFloor_SetAppointItemDataId(0, itemId);
    switch (soubi) {
    case 2:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 5, WAZA_ItemNoMahi2);
        if (seq) {
            result = 1;
        }
        break;
    case 4:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 3, WAZA_ItemNoDoku2);
        if (seq) {
            result = 1;
        } else {
            seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 4, WAZA_ItemNoDoku2);
            if (seq) {
                result = 1;
            }
        }
        break;
    case 5:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 6, WAZA_ItemNoYakedo2);
        if (seq) {
            result = 1;
        }
        break;
    case 6:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 7, WAZA_ItemNoKoori2);
        if (seq) {
            result = 1;
        }
        break;
    case 3:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 8, WAZA_ItemNoNemuri2);
        if (seq) {
            result = 1;
        }
        break;
    case 8:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 9, WAZA_ItemNoKonran2);
        if (seq) {
            result = 2;
        }
        break;
    case 28:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 0xA, WAZA_ItemNoJoutaiijou2);
        if (seq) {
            fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(0xA)));
            ServerWork[5] = 0;
            result = 2;
        }
        break;
    case 9:
        if (fightOutPokemonIsJoutaiNormal(p) == 0 || fightOutPokemonIsJoutaiDataId(p, 9) == 1) {
            ServerWork[5] = 0;
            if (fightOutPokemonIsJoutaiDataId(p, 3) == 1 || fightOutPokemonIsJoutaiDataId(p, 4) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(3)));
            }
            if (fightOutPokemonIsJoutaiDataId(p, 8) == 1) {
                fightOutPokemonInitJoutaiDataId(p, 0x17);
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(8)));
            }
            if (fightOutPokemonIsJoutaiDataId(p, 5) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(5)));
            }
            if (fightOutPokemonIsJoutaiDataId(p, 6) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(6)));
            }
            if (fightOutPokemonIsJoutaiDataId(p, 7) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(7)));
            }
            if (fightOutPokemonIsJoutaiDataId(p, 9) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(9)));
            }
            pokemonInitJoutai(pokemon);
            fightOutPokemonInitJoutaiDataId(p, 9);
            fightOutPokemonResetSeqStatus(p, 0);
            result = 1;
            seq = WAZA_ItemNoJoutaiijou2;
        }
        break;
    case 23:
        for (i = 0; i < 7; i++) {
            if (pokemonGetStatus(p, 0, fight_seq_status_id[i], 0) < 6) {
                pokemonSetStatus(p, 0, fight_seq_status_id[i], 0, 6);
                result = 5;
            }
        }
        if (result) {
            seq = WAZA_ItemAbiKaifuku2;
        }
        break;
    }
    if (result) {
        fightFloor_SetAppointPokemonPtr(0, p);
        fightFloor_SetItemPokemonPtr(0, p);
        if (result == 1) {
            fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
        }
        if (seq) {
            fightSeq_CallWazaSeq(seq);
        }
    }
    return 1;
}

extern "C" {
s32 fightSeqSoubiItemCheckWazaHitAfter(FightOutPokemon* attacker, FightOutPokemon* defender) {
    FightWaza* fw = fightOutPokemon_GetFightWazaPtr(attacker);
    s32 itemId = fightOutPokemonGetSoubiItemDataId(attacker);
    u16 soubi = fightOutPokemonGetSoubiItemSoubiDataId(attacker);
    s32 buff = figthOutPokemonGetSoubiItemBuff(attacker);
    s32 result;
    s32 waza;
    u8 hit;
    u8 oujano;
    s16 atkDamage;
    s16 speDamage;
    s32 kaigara;
    fightOutPokemonGetSoubiItemDataId(defender);
    fightOutPokemonGetSoubiItemSoubiDataId(defender);
    figthOutPokemonGetSoubiItemBuff(defender);
    result = 0;

    if (fightWaza_GetDamage(fw) == 0) {
        return 0;
    }
    waza = fightOutPokemon_GetUseWazaDataId(attacker);
    hit = fightWazaIsHit(fw);
    oujano = wazaDB_GetOujanosirusi(waza);
    atkDamage = fightOutPokemon_GetMyselfDamageAtkValue(defender);
    speDamage = fightOutPokemon_GetMyselfDamageSpeValue(defender);
    kaigara = fightOutPokemon_GetKaigaraDamageValue(defender);
    switch (soubi) {
    case 0x1E:
        if (hit == 1 && (atkDamage != 0 || speDamage != 0) && oujano == 1 && (s32)(HSD_Rand() % 100) < buff &&
            fightOutPokemonCheckFightOut(defender) == 1) {
            void* seq;
            ServerWork[3] = 8;
            seq = fightSeq_GetWazaSeq();
            fightSeqTuikaAct(0, 0);
            fightSeq_JumpWazaSeq(seq);
        }
        break;
    case 0x3E:
        if (hit == 1 && kaigara != 0 && kaigara != 0xFFFF && attacker != defender && fightOutPokemonIsHpMantan(attacker) == 0 &&
            fightOutPokemonCheckFightOut(attacker) == 1) {
            s32 damage;
            fightFloor_SetAppointItemDataId(0, itemId);
            fightFloor_SetItemPokemonPtr(0, attacker);
            fightFloor_SetAppointPokemonPtr(0, attacker);
            damage = -(kaigara / buff);
            if (damage == 0) {
                damage = -1;
            }
            fightWaza_SetDamage(fw, damage);
            fightOutPokemon_SetKaigaraDamageValue(defender, 0);
            fightSeq_CallWazaSeq(WAZA_ItemHPKaifukuEveryTurn2);
            result = 1;
        }
        break;
    }
    return result;
}
}

extern u8 WAZA_ItemNoMahi[];
extern u8 WAZA_ItemNoDoku[];
extern u8 WAZA_ItemNoYakedo[];
extern u8 WAZA_ItemNoKoori[];
extern u8 WAZA_ItemNoNemuri[];
extern u8 WAZA_ItemNoKonran[];
extern u8 WAZA_ItemNoJoutaiijou[];
extern u8 WAZA_ItemPPKaifuku[];
extern u8 WAZA_ItemCriticalUp[];
extern u8 WAZA_ItemHPKaifukuEveryTurn[];
extern "C" {
u8 pokemonWazaGetMaxPP(Pokemon* pokemon, u16 wazaNum);
bool pokemonWazaCheckValid(Pokemon* pokemon, u16 wazaNum);
}
static u8* _fightSeqSoubiItemCheckTurnSubAbiCntUp(FightOutPokemon* p, u8 mode, s32 hpFollow, u8 kind, u8 amount, u8 type);

static u8* _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku(FightOutPokemon* p, u16 taste, u8 mode, u16 hp, u16 maxHp, s32 div, FIGHT_WAZA* waza);

extern "C" {
u8 fightSeqSoubiItemCheckTurn(FightOutPokemon* p, u8 mode) {
    u8 kinds[5] = {1, 2, 3, 4, 5};
    u16 hp;
    u8 result = 0;
    FIGHT_WAZA* fw;
    s32 itemId;
    u16 soubi;
    s32 buff;
    u8* seq = 0;
    u16 maxHp;
    s32 list[5] = {-1, -1, -1, -1, -1};
    Pokemon* pokemon;
    u16 count;

    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 0;
    }
    itemId = fightOutPokemonGetSoubiItemDataId(p);
    soubi = fightOutPokemonGetSoubiItemSoubiDataId(p);
    buff = figthOutPokemonGetSoubiItemBuff(p);
    fw = (FIGHT_WAZA*)fightOutPokemon_GetFightWazaPtr(p);
    pokemon = fightOutPokemonGetPokemonPtr(p);
    hp = pokemon_GetHp(pokemon);
    maxHp = pokemon_GetMaxHp(pokemon);
    fightFloor_SetAppointItemDataId(0, itemId);
    switch (soubi) {
    case 1:
        if ((fightOutPokemonIsNokoriHpFollowing(p, 2) != 0 && mode == 0) || (fightOutPokemonIsHpMantan(p) == 0 && mode == 2)) {
            u32 heal = buff;
            if ((s32)(hp + heal) > maxHp) {
                heal = maxHp - hp;
            }
            fightWaza_SetDamage(fw, -(s32)heal);
            result = 4;
            seq = WAZA_ItemHPKaifuku;
        }
        break;
    case 7:
        if (mode == 0 || mode == 2) {
            Pokemon* moto = fightPokemonGetPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(p));
            u16 i;
            u16 waza;
            u8 pp;
            for (i = 0; i < 4; i++) {
                if (pokemonWazaCheckValid(moto, i)) {
                    waza = pokemon_GetPokemonWazaDataId(moto, i);
                    pp = pokemon_GetPokemonWazaPp(moto, i);
                    if (pp == 0) {
                        break;
                    }
                }
            }
            if (i != 4) {
                u8 maxPP = pokemonWazaGetMaxPP(moto, i);
                u8 newPP = pp + buff;
                if (pp + buff > maxPP) {
                    newPP = maxPP;
                }
                pokemon_SetPokemonWazaPp(moto, i, newPP);
                fightSeqPpdecMonomane(p, i, 1);
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(waza)));
                result = 3;
                seq = WAZA_ItemPPKaifuku;
            }
        }
        break;
    case 23: {
        u16 i;
        for (i = 0; i < 7; i++) {
            if (pokemonGetStatus(p, 0, fight_seq_status_id[i], 0) < 6) {
                pokemonSetStatus(p, 0, fight_seq_status_id[i], 0, 6);
                result = 5;
            }
        }
        if (result) {
            seq = WAZA_ItemAbiKaifuku;
        }
        break;
    }
    case 43:
        if ((fightOutPokemonIsHpMantan(p) == 0 && mode == 0) || (fightOutPokemonIsHpMantan(p) == 0 && mode == 2)) {
            u32 heal = fightOutPokemonMaxHpWaruValue(p, 0x10);
            if ((s32)(hp + heal) > maxHp) {
                heal = maxHp - hp;
            }
            fightWaza_SetDamage(fw, -(s32)heal);
            result = 4;
            seq = WAZA_ItemHPKaifukuEveryTurn;
        }
        break;
    case 10:
        seq = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku(p, 0, mode, hp, maxHp, buff, fw);
        if (seq) {
            result = 4;
        }
        break;
    case 11:
        seq = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku(p, 1, mode, hp, maxHp, buff, fw);
        if (seq) {
            result = 4;
        }
        break;
    case 12:
        seq = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku(p, 2, mode, hp, maxHp, buff, fw);
        if (seq) {
            result = 4;
        }
        break;
    case 13:
        seq = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku(p, 3, mode, hp, maxHp, buff, fw);
        if (seq) {
            result = 4;
        }
        break;
    case 14:
        seq = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku(p, 4, mode, hp, maxHp, buff, fw);
        if (seq) {
            result = 4;
        }
        break;
    case 15:
        seq = _fightSeqSoubiItemCheckTurnSubAbiCntUp(p, mode, buff, 1, 0x10, 0xF);
        if (seq) {
            result = 5;
        }
        break;
    case 16:
        seq = _fightSeqSoubiItemCheckTurnSubAbiCntUp(p, mode, buff, 2, 0x10, 0x10);
        if (seq) {
            result = 5;
        }
        break;
    case 17:
        seq = _fightSeqSoubiItemCheckTurnSubAbiCntUp(p, mode, buff, 3, 0x10, 0x11);
        if (seq) {
            result = 5;
        }
        break;
    case 18:
        seq = _fightSeqSoubiItemCheckTurnSubAbiCntUp(p, mode, buff, 4, 0x10, 0x12);
        if (seq) {
            result = 5;
        }
        break;
    case 19:
        seq = _fightSeqSoubiItemCheckTurnSubAbiCntUp(p, mode, buff, 5, 0x10, 0x13);
        if (seq) {
            result = 5;
        }
        break;
    case 20:
        if ((mode == 0 || mode == 2) && fightOutPokemonIsNokoriHpFollowing(p, buff) != 0 &&
            fightOutPokemonCheckWriteJoutaiDataId(p, 0xF) == 2) {
            fightOutPokemonWriteJoutaiDataId(p, 0xF, 0);
            result = 2;
            seq = WAZA_ItemCriticalUp;
        }
        break;
    case 21:
        if ((mode == 0 || mode == 2) && fightOutPokemonIsNokoriHpFollowing(p, buff) != 0) {
            count = 0;
            u16 i;
            for (i = 0; i < 5; i++) {
                list[i] = -1;
            }
            for (i = 0; i < 5; i++) {
                u8 kind = kinds[i];
                if ((u8)pokemonGetStatus(p, 0, fightSeqCondChgActTypeToPokemonStatusId((s32)kind), 0) < 12) {
                    list[count++] = kind;
                }
            }
            if (count >= 1) {
                s32 pick = list[(u16)((u16)HSD_Rand() % count)];
                if (pick != -1) {
                    seq = _fightSeqSoubiItemCheckTurnSubAbiCntUp(p, mode, buff, pick, 0x20, pick + 0x26);
                    if (seq) {
                        result = 5;
                    }
                }
            }
        }
        break;
    case 2:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 5, WAZA_ItemNoMahi);
        if (seq) {
            result = 1;
        }
        break;
    case 4:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 3, WAZA_ItemNoDoku);
        if (seq) {
            result = 1;
        } else {
            seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 4, WAZA_ItemNoDoku);
            if (seq) {
                result = 1;
            }
        }
        break;
    case 5:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 6, WAZA_ItemNoYakedo);
        if (seq) {
            result = 1;
        }
        break;
    case 6:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 7, WAZA_ItemNoKoori);
        if (seq) {
            result = 1;
        }
        break;
    case 3:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 8, WAZA_ItemNoNemuri);
        if (seq) {
            result = 1;
        }
        break;
    case 8:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 9, WAZA_ItemNoKonran);
        if (seq) {
            result = 2;
        }
        break;
    case 9:
        if (fightOutPokemonIsJoutaiNormal(p) == 0 || fightOutPokemonIsJoutaiDataId(p, 9) == 1) {
            u16 cured = 0;
            ServerWork[5] = 0;
            if (fightOutPokemonIsJoutaiDataId(p, 3) == 1 || fightOutPokemonIsJoutaiDataId(p, 4) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(3)));
                cured = 1;
            }
            u32 cmpv = fightOutPokemonIsJoutaiDataId(p, 8);
            if (cmpv == 1) {
                fightOutPokemonInitJoutaiDataId(p, 0x17);
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(8)));
                cured++;
            }
            if (fightOutPokemonIsJoutaiDataId(p, 5) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(5)));
                cured++;
            }
            if (fightOutPokemonIsJoutaiDataId(p, 6) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(6)));
                cured++;
            }
            if (fightOutPokemonIsJoutaiDataId(p, 7) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(7)));
                cured++;
            }
            if (fightOutPokemonIsJoutaiDataId(p, 9) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(9)));
                cured++;
            }
            if (cured >= 2) {
                ServerWork[5] = 1;
            }
            pokemonInitJoutai(pokemon);
            fightOutPokemonInitJoutaiDataId(p, 9);
            fightOutPokemonResetSeqStatus(p, 0);
            result = 1;
            seq = WAZA_ItemNoJoutaiijou;
        }
        break;
    case 28:
        seq = (u8*)_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(p, 0xA, WAZA_ItemNoJoutaiijou);
        if (seq) {
            fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(0xA)));
            ServerWork[5] = 0;
            result = 2;
        }
        break;
    }
    if (result) {
        fightFloor_SetAppointPokemonPtr(0, p);
        fightFloor_SetAttackPokemonPtr(0, p);
        fightFloor_SetItemPokemonPtr(0, p);
        switch (result) {
        case 2:
            break;
        case 1:
            fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
            break;
        }
        if (seq) {
            fightSeq_CallWazaSeq(seq);
        }
    }
    return result;
}
}

static s32 _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku(FightOutPokemon* p, u16 joutai, u8* ret) {
    s32 result = 0;
    if (fightOutPokemonIsJoutaiDataId(p, joutai) == 1) {
        fightOutPokemonInitJoutaiDataId(p, joutai);
        if (joutai == 8) {
            fightOutPokemonInitJoutaiDataId(p, 0x17);
        } else if (joutai == 4) {
            fightOutPokemonInitJoutaiDataId(p, 3);
        } else if (joutai == 3) {
            fightOutPokemonInitJoutaiDataId(p, 4);
        }
        result = (s32)ret;
    }
    return result;
}

static u8* _fightSeqSoubiItemCheckTurnSubAbiCntUp(FightOutPokemon* p, u8 mode, s32 hpFollow, u8 kind, u8 amount, u8 type) {
    u8* seq = 0;
    if (mode == 0 || mode == 2) {
        u32 id = fightSeqCondChgActTypeToPokemonStatusId(kind);
        u8 cur = pokemonGetStatus(p, 0, id, 0);
        if (fightOutPokemonIsNokoriHpFollowing(p, hpFollow) != 0 && cur < 12) {
            UserWork[0x1601E] = kind + amount;
            UserWork[0x160A4] = type;
            UserWork[0x160A5] = 0;
            seq = WAZA_ItemCondUp;
        }
    }
    return seq;
}

static u8* _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku(FightOutPokemon* p, u16 taste, u8 mode, u16 hp, u16 maxHp, s32 div, FIGHT_WAZA* waza) {
    u8* seq = 0;
    if ((fightOutPokemonIsNokoriHpFollowing(p, 2) != 0 && mode == 0) || (fightOutPokemonIsHpMantan(p) == 0 && mode == 2)) {
        u32 heal;
        fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(tasteDataGetNigateMsgDataId(tasteDataGetPtr(taste))));
        heal = fightOutPokemonMaxHpWaruValue(p, div);
        if ((s32)(hp + heal) > maxHp) {
            heal = maxHp - hp;
        }
        fightWaza_SetDamage(waza, -(s32)heal);
        if (fightOutPokemonGetTasteLike(p, taste) == -1) {
            seq = WAZA_ItemHPKaifukuKonran;
        } else {
            seq = WAZA_ItemHPKaifuku;
        }
    }
    return seq;
}

extern "C" {
u8 fightSeqPokemonSoubiItemCheckAppear(FightOutPokemon* p) {
    u8 result = 0;
    s32 item = fightOutPokemonGetSoubiItemDataId(p);
    u16 kind = fightOutPokemonGetSoubiItemSoubiDataId(p);
    FightTrainer* trainer;
    figthOutPokemonGetSoubiItemBuff(p);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, p);
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 0;
    }
    fightFloor_SetAppointItemDataId(0, item);
    switch (kind) {
    case 32:
        fightTrainer_SetOkaneBai(trainer, 2);
        break;
    case 23: {
        u8 i;
        for (i = 0; i < 7; i++) {
            if (pokemonGetStatus(p, 0, fight_seq_status_id[i], 0) < 6) {
                pokemonSetStatus(p, 0, fight_seq_status_id[i], 0, 6);
                result = 5;
            }
        }
        if (result != 0) {
            fightFloor_SetAppointPokemonPtr(0, p);
            fightFloor_SetAttackPokemonPtr(0, p);
            fightFloor_SetItemPokemonPtr(0, p);
            fightSeq_CallWazaSeq(WAZA_ItemAbiKaifuku);
        }
        break;
    }
    }
    return result;
}
}

extern "C" {
void fightSeqFightOutPokemonTokuseiCheckSinkuroAtk(FightOutPokemon* p) {
    u16 tokusei = fightOutPokemonGetTokuseiDataId(p);
    if (fightOutPokemonCheckFightOut(p) != 0 && tokusei == 0x1C && (ServerStatusFlag & 0x4000)) {
        ServerStatusFlag &= ~0x4000;
        fight_seq_tuika_param &= 0x3F;
        if (fight_seq_tuika_param == 6) {
            fight_seq_tuika_param = 2;
        }
        ServerWork[3] = fight_seq_tuika_param;
        fightFloor_SetAppointPokemonPtr(0, p);
        ServerStatusFlag |= 0x2000;
        fightSeq_CallWazaSeq(WAZA_Sinkuro);
    }
}
}

extern "C" {
void fightSeqFightOutPokemonTokuseiCheckSinkuroDef(void* unused, FightOutPokemon* p) {
    u16 tokusei = fightOutPokemonGetTokuseiDataId(p);
    if (fightOutPokemonCheckFightOut(p) != 0 && tokusei == 0x1C && (ServerStatusFlag & 0x4000)) {
        ServerStatusFlag &= ~0x4000;
        fight_seq_tuika_param &= 0x3F;
        if (fight_seq_tuika_param == 6) {
            fight_seq_tuika_param = 2;
        }
        ServerWork[3] = fight_seq_tuika_param + 0x40;
        fightFloor_SetAppointPokemonPtr(0, p);
        ServerStatusFlag |= 0x2000;
        fightSeq_CallWazaSeq(WAZA_Sinkuro);
    }
}
}

extern "C" {
void fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAll(void) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAllSub, 0, 0);
}
}

static s32 _fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAllSub(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    while (1) {
        u16 tokusei;
        u8 kind;
        Pokemon* pokemon;
        if (fightOutPokemonCheckFightOut(p) == 0) {
            return 1;
        }
        tokusei = fightOutPokemonGetTokuseiDataId(p);
        pokemon = fightOutPokemonGetPokemonPtr(p);
        kind = 0;
        switch (tokusei) {
        case 0x11:
            if (fightOutPokemonIsJoutaiDataId(p, 3) == 1 || fightOutPokemonIsJoutaiDataId(p, 4) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(3)));
                kind = 1;
            }
            break;
        case 0x14:
            if (fightOutPokemonIsJoutaiDataId(p, 9) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(9)));
                kind = 2;
            }
            break;
        case 0x7:
            if (fightOutPokemonIsJoutaiDataId(p, 5) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(5)));
                kind = 1;
            }
            break;
        case 0x48:
        case 0xF:
            if (fightOutPokemonIsJoutaiDataId(p, 8) == 1) {
                fightOutPokemonInitJoutaiDataId(p, 0x17);
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(8)));
                kind = 1;
            }
            break;
        case 0x29:
            if (fightOutPokemonIsJoutaiDataId(p, 6) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(6)));
                kind = 1;
            }
            break;
        case 0x28:
            if (fightOutPokemonIsJoutaiDataId(p, 7) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(7)));
                kind = 1;
            }
            break;
        case 0xC:
            if (fightOutPokemonIsJoutaiDataId(p, 0xA) == 1) {
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(joutaiDataBiosGetName(0xA)));
                kind = 3;
            }
            break;
        }
        if (kind == 0) {
            break;
        }
        switch (kind) {
        case 1:
            pokemonInitJoutai(pokemon);
            fightOutPokemonResetSeqStatus(p, 0);
            break;
        case 2:
            fightOutPokemonInitJoutaiDataId(p, 9);
            break;
        case 3:
            fightOutPokemonInitJoutaiDataId(p, 0xA);
            break;
        }
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
        fightFloor_SetAppointPokemonPtr(0, p);
        fightSeq_CallWazaSeq(WAZA_SpeabiNoJoutaiijou);
    }
    return 1;
}

extern "C" {
s32 fightSeqFightOutPokemonTokuseiCheckWazaHitAfter(FightOutPokemon* attacker, FightOutPokemon* defender) {
    s16 atkDamage;
    s16 speDamage;
    u16 attackerTokusei;
    u16 defenderTokusei;
    u16 waza;
    u16 iryoku;
    u32 zokusei;
    u8 dageki;
    FightWaza* fightWaza;
    u8 hit;
    u8 konran;
    s32 result;
    u8 attackerSex;
    u8 defenderSex;
    u32 target;

    atkDamage = fightOutPokemon_GetMyselfDamageAtkValue(defender);
    speDamage = fightOutPokemon_GetMyselfDamageSpeValue(defender);
    attackerTokusei = fightOutPokemonGetTokuseiDataId(attacker);
    defenderTokusei = fightOutPokemonGetTokuseiDataId(defender);
    waza = fightOutPokemon_GetUseWazaDataId(attacker);
    iryoku = wazaDB_GetIryoku(waza);
    zokusei = fightOutPokemonGetWazaZokuseiDataId(attacker);
    dageki = wazaDB_GetDageki((u8)waza);
    fightWaza = fightOutPokemon_GetFightWazaPtr(attacker);
    hit = fightWazaIsHit(fightWaza);
    konran = fightOutPokemon_GetKonranMyselfAttackFlag(attacker);
    u8 values[3] = {1, 2, 5};
    result = 0;
    attackerSex = fightOutPokemonGetSex(attacker);
    defenderSex = fightOutPokemonGetSex(defender);
    u8 tmp1 = fightFloor_GetFightType(0);
    target = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(defender, tmp1);
    switch (defenderTokusei) {
    case 0x10:
        if (hit == 1 && waza != 0xA5 && iryoku != 0 && wazaCheckDarkWaza(waza) == 0 &&
            (atkDamage != 0 || speDamage != 0) && fightOutPokemonIsZokuseiDataId(defender, zokusei) == 0 &&
            fightOutPokemonCheckFightOut(defender) == 1) {
            u8 i;
            for (i = 0; i < 2; i++) {
                fightOutPokemonSetZokuseiDataId(defender, i, zokusei);
            }
            fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar((void*)zokuseiBiosGetName(zokusei)));
            fightSeq_CallWazaSeq(WAZA_Hensyoku);
            result = 1;
        }
        break;
    case 0x18:
        if (hit == 1 && fightOutPokemonCheckFightOut(attacker) == 1 && konran == 0 &&
            (atkDamage != 0 || speDamage != 0) && dageki != 0) {
            fightWaza_SetDamage(fightWaza, fightOutPokemonMaxHpWaruValue(attacker, 0x10));
            fightSeq_CallWazaSeq(WAZA_Samehada);
            result = 1;
        }
        break;
    case 0x1B:
        if (hit == 1 && fightOutPokemonCheckFightOut(attacker) == 1 && konran == 0 &&
            (atkDamage != 0 || speDamage != 0) && dageki != 0 && HSD_Rand() % 10 == 0) {
            ServerWork[3] = values[(u8)(HSD_Rand() % 3)];
            ServerStatusFlag |= 0x2000;
            ServerWork[3] += 0x40;
            fightSeq_CallWazaSeq(WAZA_Honoonokarada);
            result = 1;
        }
        break;
    case 0x26:
        if (hit == 1 && fightOutPokemonCheckFightOut(attacker) == 1 && konran == 0 &&
            (atkDamage != 0 || speDamage != 0) && dageki != 0 && HSD_Rand() % 3 == 0) {
            ServerWork[3] = 0x42;
            ServerStatusFlag |= 0x2000;
            fightSeq_CallWazaSeq(WAZA_Honoonokarada);
            result = 1;
        }
        break;
    case 9:
        if (hit == 1 && fightOutPokemonCheckFightOut(attacker) == 1 && konran == 0 &&
            (atkDamage != 0 || speDamage != 0) && dageki != 0 && HSD_Rand() % 3 == 0) {
            ServerWork[3] = 0x45;
            ServerStatusFlag |= 0x2000;
            fightSeq_CallWazaSeq(WAZA_Honoonokarada);
            result = 1;
        }
        break;
    case 0x31:
        if (hit == 1 && fightOutPokemonCheckFightOut(attacker) == 1 && konran == 0 && dageki != 0 &&
            (atkDamage != 0 || speDamage != 0) && HSD_Rand() % 3 == 0) {
            ServerWork[3] = 0x43;
            ServerStatusFlag |= 0x2000;
            fightSeq_CallWazaSeq(WAZA_Honoonokarada);
            result = 1;
        }
        break;
    case 0x38:
        if (hit == 1 && fightOutPokemonCheckFightOut(attacker) == 1 && konran == 0 && dageki != 0 &&
            (atkDamage != 0 || speDamage != 0) && fightOutPokemonCheckFightOut(defender) == 1 &&
            HSD_Rand() % 3 == 0 && attackerTokusei != 0xC && attackerSex != defenderSex &&
            fightOutPokemonCheckWriteJoutaiDataId(attacker, 0xA) == 2 && attackerSex != 2 && defenderSex != 2) {
            fightOutPokemonWriteJoutaiDataId(attacker, 0xA, target);
            fightSeq_CallWazaSeq(WAZA_MeromeroBody);
            result = 1;
        }
        break;
    }
    return result;
}

extern u8 WAZA_TyosuiPPDec[];
extern u8 WAZA_MoraibiPPDec[];
extern u8 WAZA_NOKaifukuPPDec[];

u8 fightSeqFightOutPokemonTokuseiCheckWazaHit(FightOutPokemon* attacker, FightOutPokemon* defender, u32 waza) {
    u16 tokusei = fightOutPokemonGetTokuseiDataId(defender);
    u16 iryoku = wazaDB_GetIryoku(waza);
    u16 zokusei = fightOutPokemonGetWazaZokuseiDataId(attacker);
    u8 pass = fightOutPokemon_GetPassPpdecFlag(attacker);
    u8 result = 0;
    FightWaza* fw = fightOutPokemon_GetFightWazaPtr(attacker);

    if (fightOutPokemonCheckFightOut(defender) == 0) {
        return 0;
    }
    if ((u16)waza != 0 && (u16)waza != 0x176) {
        switch (tokusei) {
        case 10:
            if (zokusei == 0xD && iryoku != 0) {
                if (pass) {
                    fightSeq_JumpWazaSeq(WAZA_Tyosui);
                } else {
                    fightSeq_JumpWazaSeq(WAZA_TyosuiPPDec);
                }
                result = 1;
            }
            break;
        case 11:
            if (zokusei == 0xB && iryoku != 0) {
                if (pass) {
                    fightSeq_JumpWazaSeq(WAZA_Tyosui);
                } else {
                    fightSeq_JumpWazaSeq(WAZA_TyosuiPPDec);
                }
                result = 1;
            }
            break;
        case 18:
            if (zokusei == 0xA && fightOutPokemonIsJoutaiDataId(defender, 7) == 0) {
                if (fightOutPokemonCheckWriteJoutaiDataId(defender, 0x3A) == 2) {
                    fightOutPokemonWriteJoutaiDataId(defender, 0x3A, 0);
                    ServerWork[5] = 0;
                } else {
                    ServerWork[5] = 1;
                }
                if (pass) {
                    fightSeq_JumpWazaSeq(WAZA_Moraibi);
                } else {
                    fightSeq_JumpWazaSeq(WAZA_MoraibiPPDec);
                }
                result = 2;
            }
            break;
        }
        if (result == 1) {
            if (fightOutPokemonIsHpMantan(defender) == 1) {
                if (pass) {
                    fightSeq_JumpWazaSeq(WAZA_NOKaifuku);
                } else {
                    fightSeq_JumpWazaSeq(WAZA_NOKaifukuPPDec);
                }
            } else {
                fightWaza_SetDamage(fw, -fightOutPokemonMaxHpWaruValue(defender, 4));
            }
        }
    }
    return result;
}

s32 fightSeqFightOutPokemonTokuseiCheckWazaHitBefore(FightOutPokemon* atk, FightOutPokemon* def) {
    s32 waza;
    s32 result;
    u16 tok;
    fightOutPokemonGetTokuseiDataId(atk);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    tok = fightOutPokemonGetTokuseiDataId(def);
    result = 0;
    switch (tok) {
    case 0x2B:
        if (fightOutPokemonCheckFightOut(def) != 0 && wazaDB_GetBouon(waza) == 1) {
            if (fightOutPokemonIsJoutaiDataId(atk, 0x22) == 1) {
                ServerStatusFlag |= 0x800;
            }
            fightSeq_JumpWazaSeq(WAZA_Bouon);
            result = 1;
        }
        break;
    }
    return result;
}
}

void fightSeqFightOutPokemonTokuseiCheckTurn(FightOutPokemon* p) {
    Pokemon* pokemon = (Pokemon*)fightOutPokemonGetPokemonPtr(p);
    u8 weather = fightFloorGetNowTenkouDataId(0, 1);
    if (p != 0 && fightOutPokemonCheckFightOut(p) != 0) {
        u16 tokusei = fightOutPokemonGetTokuseiDataId(p);
        FightWaza* waza;
        fightFloor_SetAttackPokemonPtr(0, p);
        waza = fightOutPokemon_GetFightWazaPtr(p);
        switch (tokusei) {
        case 0x2C:
            if (weather == 2 && fightOutPokemonIsHpMantan(p) == 0) {
                fightWaza_SetDamage(waza, -(s32)fightOutPokemonMaxHpWaruValue(p, 0x10));
                fightSeq_CallWazaSeq(WAZA_Ameukezara);
                return;
            }
            break;
        case 0x3D:
            if (fightOutPokemonIsJoutaiNormal(p) == 0 && HSD_Rand() % 3 == 0) {
                fightFloor_SetAppointPokemonPtr(0, p);
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(pokemonGetJoutaiMsgId(pokemon)));
                pokemonInitJoutai(pokemon);
                fightOutPokemonInitJoutaiDataId(p, 0x17);
                fightOutPokemonResetSeqStatus(p, 0);
                fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
                fightSeq_CallWazaSeq(WAZA_Dappi);
                return;
            }
            break;
        case 0x3: {
            s8 cur;
            s32 id = fightSeqCondChgActTypeToPokemonStatusId(3);
            cur = pokemonGetStatus(p, 0, (u16)id, 0);
            if (cur < 12 && fightOutPokemon_GetFightoutTurnCount(p) != 2) {
                fightFloor_SetAppointPokemonPtr(0, p);
                pokemonSetStatus(p, 0, id, 0, (s8)(cur + 1));
                UserWork[0x160A4] = 0x11;
                UserWork[0x160A5] = 0;
                fightSeq_CallWazaSeq(WAZA_Kasokusouti);
                return;
            }
            break;
        }
        case 0x36:
            fightOutPokemon_SetNamakeFlag(p, (s32)((u8)fightOutPokemon_GetNamakeFlag(p) == 0));
            break;
        }
    }
}

extern "C" {
void fightSeqFightOutPokemonTokuseiCheckTrace(void) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqFightOutPokemonTokuseiCheckTraceSub, 0, 0);
}
}

static s32 _fightSeqFightOutPokemonTokuseiCheckTraceSub(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    u16 tokusei = fightOutPokemonGetTokuseiDataId(p);
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    if (tokusei == 0x24 && fightOutPokemonIsJoutaiDataId(p, 0x3C) == 1) {
        FightOutPokemon* target = fightFloorGetFightOutPokemonPtrRandom(0, 1, 2, p);
        if (fightOutPokemonCheckFightOut(target) == 1) {
            u16 newTokusei;
            fightOutPokemonInitJoutaiDataId(p, 0x3C);
            newTokusei = fightOutPokemonGetTokuseiDataId(target);
            fightOutPokemonSetTokuseiDataId(p, newTokusei);
            fightFloor_SetAppointPokemonPtr(0, p);
            fightMsgctrlSetValue(0xD, (u32)fightOutPokemonGetNicknamePtr(target));
            fightMsgctrlSetValue(0xE, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(newTokusei))));
            fightSeq_CallWazaSeq(WAZA_Trace);
        }
    }
    return 1;
}

extern "C" {
void fightSeqFightOutPokemonTokuseiCheckIkaku(u8 flag) {
    u8 local = flag;
    fightFloorLoopValidFightOutPokemon(0, _fightSeqFightOutPokemonTokuseiCheckIkakuSub, &local, 0);
}
}

static s32 _fightSeqFightOutPokemonTokuseiCheckIkakuSub(void* arg, u16 id, void* userData) {
    u8* seq = (u8*)userData;
    u16 tokusei;
    FightOutPokemon* p = (FightOutPokemon*)arg;
    tokusei = fightOutPokemonGetTokuseiDataId(p);
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    if (*seq == 1) {
        seq = WAZA_Ikaku;
    } else {
        seq = WAZA_IkakuAct;
    }
    if (tokusei == 0x16 && fightOutPokemonIsJoutaiDataId(p, 0x3B) == 1) {
        fightOutPokemonInitJoutaiDataId(p, 0x3B);
        fightFloor_SetAppointPokemonPtr(0, p);
        fightSeq_CallWazaSeq(seq);
    }
    return 1;
}

extern "C" {
void fightSeqFightOutPokemonTokuseiCheckAppear(FightOutPokemon* p) {
    if (p != 0 && fightOutPokemonCheckFightOut(p) != 0) {
        u16 tokusei = fightOutPokemonGetTokuseiDataId(p);
        switch (tokusei) {
        case 0x2:
            if (fightFloorCheckWriteJoutaiDataId(0, 0x50) == 2) {
                fightFloorWriteJoutaiDataId(0, 0x50, 0);
                fightFloor_SetAppointPokemonPtr(0, p);
                fightSeq_CallWazaSeq(WAZA_Amehurashi);
                return;
            }
            break;
        case 0x2D:
            if (fightFloorCheckWriteJoutaiDataId(0, 0x51) == 2) {
                fightFloorWriteJoutaiDataId(0, 0x51, 0);
                fightFloor_SetAppointPokemonPtr(0, p);
                fightSeq_CallWazaSeq(WAZA_Sunaokosi);
                return;
            }
            break;
        case 0x46:
            if (fightFloorCheckWriteJoutaiDataId(0, 0x4F) == 2) {
                fightFloorWriteJoutaiDataId(0, 0x4F, 0);
                fightFloor_SetAppointPokemonPtr(0, p);
                fightSeq_CallWazaSeq(WAZA_Hideri);
                return;
            }
            break;
        case 0x16:
            if (fightOutPokemon_GetDoIkakuFlag(p) == 0) {
                if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x3B) == 2) {
                    fightOutPokemonWriteJoutaiDataId(p, 0x3B, 0);
                }
                fightOutPokemon_SetDoIkakuFlag(p, 1);
                return;
            }
            break;
        case 0x24:
            if (fightOutPokemon_GetDoTraceFlag(p) == 0) {
                if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x3C) == 2) {
                    fightOutPokemonWriteJoutaiDataId(p, 0x3C, 0);
                }
                fightOutPokemon_SetDoTraceFlag(p, 1);
                return;
            }
            break;
        case 0x3B: {
            u8 form = fightSeqTokuseiTenkiyaAct(p);
            if (form != 0) {
                UserWork[0x1609B] = form - 1;
                fightFloor_SetAppointPokemonPtr(0, p);
                fightSeq_CallWazaSeq(WAZA_Tenkiya);
                return;
            }
            break;
        }
        case 0x4D:
        case 0xD:
            fightSeqFightOutPokemonTokuseiCheckTenkiya();
            break;
        }
    }
}
}

extern "C" {
void fightMainAllCamera(u8 a, u8 b);
void fightMainSetAllDispFlag(u8 flag);

void fightSeqEventKurein(u8 event) {
    WazaSequence* wazaSeq;
    switch (event) {
    case 0:
        kureinSequencePtr = (s32)Sequence_LoadTrainer(0x40);
        break;
    case 1: {
        f32 pos[3];
        f32 rot[3];
        pos[0] = 78.0f;
        pos[1] = 0.0f;
        pos[2] = 20.0f;
        rot[0] = 0.0f;
        rot[1] = -1.5707964f;
        rot[2] = 0.0f;
        Sequence_SetPosition((Sequence*)kureinSequencePtr, pos);
        Sequence_SetRotation((Sequence*)kureinSequencePtr, rot);
        Sequence_SetVisibility((Sequence*)kureinSequencePtr, 1);
        break;
    }
    case 3:
        Sequence_LoadWaza((Sequence*)kureinSequencePtr, 0xF9, 4, 0);
        WazaSequence_Start(Sequence_GetWaza((Sequence*)kureinSequencePtr, 0xF9, 4), 1);
        break;
    case 4:
        wazaSeq = Sequence_GetWaza((Sequence*)kureinSequencePtr, 0xF9, 4);
        battleGridStoreModelVisibilityFlags();
        while (WazaSequence_IsActive(wazaSeq) != 0) {
            GSthreadSwitch();
        }
        fightMainSetAllDispFlag(1);
        WazaSequence_Free(wazaSeq);
        break;
    case 6:
        Sequence_LoadWaza((Sequence*)kureinSequencePtr, 0x13C, 4, 0);
        WazaSequence_Start(Sequence_GetWaza((Sequence*)kureinSequencePtr, 0x13C, 4), 1);
        break;
    case 7:
        wazaSeq = Sequence_GetWaza((Sequence*)kureinSequencePtr, 0x13C, 4);
        battleGridStoreModelVisibilityFlags();
        while (WazaSequence_IsActive(wazaSeq) != 0) {
            GSthreadSwitch();
        }
        fightMainSetAllDispFlag(1);
        WazaSequence_Free(wazaSeq);
        fightMainAllCamera(0, 0);
        break;
    case 5:
        Sequence_LoadWaza((Sequence*)kureinSequencePtr, 0x13C, 4, 0);
        wazaSeq = Sequence_GetWaza((Sequence*)kureinSequencePtr, 0x13C, 4);
        battleGridStoreModelVisibilityFlags();
        WazaSequence_Start(wazaSeq, 1);
        fightMenuOpenMsg(0x5004);
        while (WazaSequence_IsActive(wazaSeq) != 0) {
            GSthreadSwitch();
        }
        fightMenuCloseMsg();
        WazaSequence_Free(wazaSeq);
        fightMainAllCamera(0, 0);
        break;
    }
}
}

extern "C" {
void fightEvtSetSequence(s32 seq) {
    kureinSequencePtr = seq;
}
}

extern "C" {
s32 fightEvtGetSequence(void) {
    return kureinSequencePtr;
}
}

extern "C" {
void fightSeqFightOutPokemonDarkCheckAppear(FightOutPokemon* p, u8 flag) {
    u8 fightType = fightFloor_GetFightType(0);
    Sequence* trainerSeq;
    if (p != 0 && fightOutPokemonCheckFightOut(p) != 0 && pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(p)) != 0) {
        FightPokemon* fightPokemon = fightOutPokemon_GetFightPokemonPtr(p);
        if (fightOutPokemonIsGcHeroFightOutPokemon(p) == 1) {
            if (fightPokemon_GetDarkOutFlag(fightPokemon) == 0) {
                if (pokemon_GetPokemonDataId(fightOutPokemonGetPokemonPtr(p)) != 0xF9) {
                    pokemonAddDpFormPokemonDpFilterId(fightOutPokemonGetPokemonPtr(p), 0, 0);
                }
                fightSeqCheckSetHensinBuffToMotoPokemon(p, 0xC5);
                fightMenuFightOutPokemonRenewStatusMenu(p, fightFloor_GetFightType(0), 1);
                fightPokemon_SetDarkOutFlag(fightPokemon, 1);
                fightSeqCheckSetHensinBuffToMotoFightPokemon(p, 0xD1);
            }
        } else if (flag == 0) {
            FightTrainer* trainer = fightFloorGetGcHeroFightTrainerPtr(0);
            trainerSeq = fightTrainer_GetSequencePtr();
            u32 model = 0x41;
            WazaSequence* wazaSeq;
            u32 encount;
            HeroPtr* hero;
            f32 pos[3];
            f32 rot[3];
            fightTrainer_GetFightTrainerDataId(trainer);
            hero = savedataGetStatus(0, 2);
            if (hero != 0) {
                if (getHeroStyle__4HeroCFv(hero) == 2) {
                    model = 0x42;
                }
                if (getHeroStyle__4HeroCFv(hero) == 1) {
                    model = 0x43;
                }
            }
            if (fightPokemon_GetDarkOutFlag(fightPokemon) == 0 && fightFloor_GetFightKindDoHizukiMiyaburiFlag(0) == 1 && trainerSeq != 0) {
                miyaburiSequencePtr = Sequence_LoadTrainer(model);
                Sequence_GetPosition(trainerSeq, pos);
                Sequence_GetRotation(trainerSeq, rot);
                Sequence_SetPosition(miyaburiSequencePtr, pos);
                Sequence_SetRotation(miyaburiSequencePtr, rot);
                encount = fightFloor_GetEncountDataId(0);
                fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, p, fightType, 0, 1);
                Sequence_LoadWaza(miyaburiSequencePtr, 0xA0, 4, 0);
                fightOutPokemonDarkPokemonEffect(p, 0, 0, 0);
                wazaSeq = Sequence_GetWaza(miyaburiSequencePtr, 0xA0, 4);
                battleGridBackupModelVisibilityFlags();
                Sequence_SetVisibility(trainerSeq, 0);
                battleGridStoreModelVisibilityFlags();
                Sequence_SetVisibility(miyaburiSequencePtr, 1);
                WazaSequence_Start(wazaSeq, 1);
                while (WazaSequence_IsActive(wazaSeq) != 0) {
                    GSthreadSwitch();
                }
                fightOutPokemonDarkPokemonEffect(p, 0, 0, 1);
                u32 msg;
                if (encount == 0xE0) {
                    msg = 0x4FCF;
                } else if (encount == 0x191) {
                    msg = 0x5010;
                } else {
                    msg = 0x4FCE;
                }
                fightMenuOpenMsg(msg);
                fightOutPokemonDarkPokemonEffect(p, 0, 0, 2);
                fightMenuCloseMsg();
                fightPokemon_SetDarkOutFlag(fightPokemon, 1);
                fightSeqCheckSetHensinBuffToMotoFightPokemon(p, 0xD1);
                fightOutPokemonDarkPokemonEffect(p, 0, 0, 3);
                WazaSequence_Free(wazaSeq);
                Sequence_SetVisibility(miyaburiSequencePtr, 0);
                battleGridResetModelVisibilityFlags();
                Sequence_SetVisibility(trainerSeq, 1);
                Sequence_Free(miyaburiSequencePtr);
                battleGridRestoreModelVisibilityFlags();
            }
        }
    }
}
}

extern "C" {
u8 fightSeqFightOutPokemonTokuseiCheckTenkiya(void) {
    u8 result = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightSeqFightOutPokemonTokuseiCheckTenkiyaSub, &result, 0);
    return result;
}
}

static s32 _fightSeqFightOutPokemonTokuseiCheckTenkiyaSub(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    u8* out = (u8*)userData;
    u8 form;
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    form = fightSeqTokuseiTenkiyaAct(p);
    if (form != 0) {
        UserWork[0x1609B] = form - 1;
        fightFloor_SetAppointPokemonPtr(0, p);
        fightSeq_CallWazaSeq(WAZA_Tenkiya);
        if (out != 0) {
            *out = 1;
        }
    }
    return 1;
}

u8 fightSeqTokuseiTenkiyaAct(FightOutPokemon* p) {
    u16 pokemonId;
    u16 tokusei;
    u8 weather;
    u8 result;
    u8 i;
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 0;
    }
    pokemonId = figthOutPokemonGetPokemonDataId(p);
    tokusei = fightOutPokemonGetTokuseiDataId(p);
    if (pokemonId != 0x181 || tokusei != 0x3B) {
        return 0;
    }
    weather = fightFloorGetNowTenkouDataId(0, 1);
    result = 0;
    if ((weather == 0 || weather == 3 || weather == 5) && fightOutPokemonIsZokuseiDataId(p, 0) == 0) {
        for (i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(p, i, 0);
        }
        result = 1;
    }
    if (weather == 1 && fightOutPokemonIsZokuseiDataId(p, 0xA) == 0) {
        for (i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(p, i, 0xA);
        }
        result = 2;
    }
    if (weather == 2 && fightOutPokemonIsZokuseiDataId(p, 0xB) == 0) {
        for (i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(p, i, 0xB);
        }
        result = 3;
    }
    if (weather == 4 && fightOutPokemonIsZokuseiDataId(p, 0xF) == 0) {
        for (i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(p, i, 0xF);
        }
        result = 4;
    }
    return result;
}

extern "C" {
s32 fightSeqCheckDarkPokemonJoutaiHyperAct(FightOutPokemon* p, u32 mode) {
    u8 fightType = fightFloor_GetFightType(0);
    if (p == 0) {
        return 0;
    }
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 0;
    }
    if (fightOutPokemonIsGcHeroFightOutPokemon(p) == 0) {
        return 0;
    }
    if (fightFloor_GetFightKindDarkpokemonHypermodeFlag(0) == 0) {
        return 0;
    }
    if (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(p)) == 0) {
        return 0;
    }
    fightOutPokemon_GetSequencePtr(p);
    switch (mode) {
    case 0: {
        u8 chance;
        FightOutPokemon* prev;
        if (fightOutPokemonIsJoutaiDataId(p, 0x3E) == 1) {
            return 0;
        }
        if (fightOutPokemonIsJoutaiDataId(p, 8) == 1) {
            return 0;
        }
        chance = pokemonGetDarkPokemonHyperJoutaiKakuritu(fightOutPokemonGetPokemonPtr(p));
        fightOutPokemon_GetUseWazaDataId(p);
        if ((s32)(HSD_Rand() % 100) < (s32)chance) {
            fightOutPokemonDarkPokemonEffect(p, 1, 1, 0);
            prev = fightFloor_GetAttackPokemonPtr(0);
            fightFloor_SetAttackPokemonPtr(0, p);
            if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x3E) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, 0x3E, 0);
            }
            fightSeqCheckSetHensinBuffToMotoPokemon(p, 0xC8);
            fightOutPokemonDarkPokemonEffect(p, 1, 1, 1);
            fightMenuFightOutPokemonRenewStatusMenu(p, fightType, 1);
            fightMenuOpenMsg(0x4FE2);
            fightOutPokemonDarkPokemonEffect(p, 1, 1, 2);
            fightMenuCloseMsg();
            fightMenuFightOutPokemonCloseStatusMenu(p, fightType, 0);
            fightFloor_SetAttackPokemonPtr(0, prev);
            fightOutPokemonDarkPokemonEffect(p, 1, 1, 3);
            return 1;
        }
        return 0;
    }
    case 1: {
        FightOutPokemon* prev;
        if (fightOutPokemonIsJoutaiDataId(p, 0x3E) == 0) {
            return 0;
        }
        fightOutPokemonDarkPokemonEffect(p, 0, 2, 0);
        prev = fightFloor_GetAttackPokemonPtr(0);
        fightFloor_SetAttackPokemonPtr(0, p);
        fightOutPokemonDarkPokemonEffect(p, 0, 2, 1);
        fightMenuFightOutPokemonOpenStatusMenu(p, fightType, 1);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, p, fightType, 0, 1);
        fightMenuOpenMsg(0x4FE3);
        fightOutPokemonDarkPokemonEffect(p, 0, 2, 2);
        fightMenuCloseMsg();
        fightMenuFightOutPokemonCloseStatusMenu(p, fightType, 0);
        fightFloor_SetAttackPokemonPtr(0, prev);
        fightOutPokemonDarkPokemonEffect(p, 0, 2, 3);
        return 1;
    }
    case 2: {
        FightOutPokemon* prev;
        if (fightOutPokemonIsJoutaiDataId(p, 0x3E) == 0) {
            return 0;
        }
        if (HSD_Rand() % 256 != 0) {
            return 0;
        }
        fightOutPokemonIsJoutaiDataId(p, 8);
        fightOutPokemonDarkPokemonKaijoEffect(p, 1, 1, 0, 0, 0);
        prev = fightFloor_GetAttackPokemonPtr(0);
        fightFloor_SetAttackPokemonPtr(0, p);
        fightOutPokemonInitJoutaiDataId(p, 0x3E);
        fightOutPokemonInitJoutaiDataId(p, 8);
        fightOutPokemonInitJoutaiDataId(p, 0x17);
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0xC8);
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
        fightOutPokemonDarkPokemonKaijoEffect(p, 1, 1, 0, 0x4FD7, 1);
        fightOutPokemonDarkPokemonKaijoEffect(p, 1, 1, 0, 0, 2);
        fightMenuCloseMsg();
        fightMenuFightOutPokemonCloseStatusMenu(p, fightType, 0);
        fightFloor_SetAttackPokemonPtr(0, prev);
        fightOutPokemonDarkPokemonKaijoEffect(p, 1, 1, 0, 0, 3);
        return 1;
    }
    }
    return 0;
}

extern "C" {
u8 fightWazaCheckWriteJoutaiDataId(FightWaza* waza, u16 id);
void fightWazaWriteJoutaiDataId(FightWaza* waza, u16 id, u32 value);
void fightOutPokemon_SetHirumuNoAttackFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetKanashibariNoAttackFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetChouhatsuNoAttackFlag(FightOutPokemon* fop, u8 value);
u8 fightFloorCheckHuuinWazaFightOutPokemon(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, u16 wazaId);
void fightOutPokemon_SetHuuinNoAttackFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetKonranMyselfAttackFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetMahiNoAttackFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetMeroMeroNoAttackFlag(FightOutPokemon* fop, u8 value);
s16 fightOutPokemon_GetGamanDamageValue(FightOutPokemon* fop);
u16 fightOutPokemon_GetGamanDamageTargetId(FightOutPokemon* fop);
void fightWazaSetUseWazaStatus(FightWaza* waza, u16 id);
FightOutPokemon* fightSeqSelectDefensePokemonPtr(FightOutPokemon* p, u16 waza, u32 type, void* select, u8 random, u8 special, s8 rangeOverride);
extern u8 fightseq_attack_pokemon_joutai_check_buff;
extern u8 WAZA_Mezame[];
extern u8 WAZA_Nemuru[];
extern u8 WAZA_Koori[];
extern u8 WAZA_Melt[];
extern u8 WAZA_Namakeru[];
extern u8 WAZA_Handou[];
extern u8 WAZA_Hirumu[];
extern u8 WAZA_Kanashibari[];
extern u8 WAZA_Chouhatsu2[];
extern u8 WAZA_Huuin[];
extern u8 WAZA_KonranEnd[];
extern u8 WAZA_Konran[];
extern u8 WAZA_Mahi[];
extern u8 WAZA_Meromero[];
extern u8 WAZA_MeromeroNext[];
extern s32 fight_seq_gaman_damage;
extern u8 WAZA_GamanOff[];
extern u8 WAZA_GamanFaild[];
extern u8 WAZA_Gaman[];
}

extern "C" {
s32 fightSeqWazaDamageCalc(FightOutPokemon* attacker, FightOutPokemon* defender, void* attackSide, u16 waza, u16 iryoku, s32 zokusei);
u8 fightSeqAttackPokemonJoutaiCheck(void) {
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    FightWaza* fw = fightOutPokemon_GetFightWazaPtr(p);
    void* side = fightTargetGetPtrAsNowFightType(2, p);
    u16 tokusei = fightOutPokemonGetTokuseiDataId(p);
    u32 waza = fightOutPokemon_GetUseWazaDataId(p);
    u16 iryoku = wazaDB_GetIryoku(waza);
    u16 seqId = wazaDB_GetSeqId(waza);
    u8 result = 0;
    u8 type = fightFloor_GetFightType(0);
    do {
    enum TsE { TsE0 };
        switch (fightseq_attack_pokemon_joutai_check_buff) {
        case 0:
            fightOutPokemonInitJoutaiDataId(p, 0x15);
            fightOutPokemonInitJoutaiDataId(p, 0x28);
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 1:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 8) == 1) {
                if ((u16)fightSeqSawaguCheck(p) != 0) {
                    fightOutPokemonInitJoutaiDataId(p, 8);
                    fightOutPokemonInitJoutaiDataId(p, 0x17);
                    ServerWork[5] = 1;
                    fightSeq_CallWazaSeq(WAZA_Mezame);
                    result = 2;
                } else {
                    s8 now;
                    if (tokusei == 0x30) {
                        now = 2;
                    } else {
                        now = 1;
                    }
                    now += fightOutPokemonGetNowKaisuuJoutaiDataId(p, 8);
                    enum TsE cmpv = (enum TsE)(fightOutPokemonGetKaisuuJoutaiDataId(p, 8));
                    if (now >= cmpv) {
                        fightOutPokemonInitJoutaiDataId(p, 8);
                        fightOutPokemonInitJoutaiDataId(p, 0x17);
                    } else {
                        fightOutPokemonSetNowKaisuuJoutaiDataId(p, 8, now);
                    }
                    if ((u16)fightOutPokemonIsJoutaiDataId(p, 8) == 1) {
                        if (waza != 0xAD && waza != 0xD6) {
                            ServerStatusFlag |= 0x80000;
                            fightSeq_JumpWazaSeq(WAZA_Nemuru);
                            result = 2;
                        }
                    } else {
                        ServerWork[5] = 0;
                        fightSeq_CallWazaSeq(WAZA_Mezame);
                        result = 2;
                    }
                }
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 2:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 7) == 1) {
                if (HSD_Rand() % 5 != 0) {
                    if (seqId != 0x7D) {
                        ServerStatusFlag |= 0x80000;
                        fightSeq_JumpWazaSeq(WAZA_Koori);
                        result = 2;
                    }
                } else {
                    fightOutPokemonInitJoutaiDataId(p, 7);
                    ServerWork[5] = 0;
                    fightSeq_CallWazaSeq(WAZA_Melt);
                    result = 2;
                }
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 3:
            if (tokusei == 0x36 && (u16)fightOutPokemon_GetNamakeFlag(p) != 0) {
                if ((u16)fightWazaCheckWriteJoutaiDataId(fw, 0x40) == 2) {
                    fightWazaWriteJoutaiDataId(fw, 0x40, 0);
                }
                fightOutPokemonInitJoutaiKeep(p);
                ServerStatusFlag |= 0x80000;
                ServerWork[5] = 0;
                fightSeq_JumpWazaSeq(WAZA_Namakeru);
                result = 1;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 4:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 0x12) == 1) {
                fightOutPokemonInitJoutaiDataId(p, 0x12);
                fightOutPokemonInitJoutaiKeep(p);
                ServerStatusFlag |= 0x80000;
                fightSeq_JumpWazaSeq(WAZA_Handou);
                result = 1;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 5:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 0x11) == 1) {
                fightOutPokemonInitJoutaiDataId(p, 0x11);
                fightOutPokemon_SetHirumuNoAttackFlag(p, 1);
                fightOutPokemonInitJoutaiKeep(p);
                ServerStatusFlag |= 0x80000;
                fightSeq_JumpWazaSeq(WAZA_Hirumu);
                result = 1;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 6:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 0x29) == 1 && fightOutPokemonGetIdBuffJoutaiDataId(p, 0x29) == waza &&
                waza != 0 && waza != 0x176) {
                fightOutPokemonInitJoutaiKeep(p);
                fightOutPokemon_SetKanashibariNoAttackFlag(p, 1);
                ServerStatusFlag |= 0x80000;
                fightMsgctrlSetValue(0x11, waza);
                fightSeq_JumpWazaSeq(WAZA_Kanashibari);
                result = 1;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 7:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 0x30) == 1 && iryoku == 0) {
                fightOutPokemonInitJoutaiKeep(p);
                fightOutPokemon_SetChouhatsuNoAttackFlag(p, 1);
                ServerStatusFlag |= 0x80000;
                fightMsgctrlSetValue(0x11, waza);
                fightSeq_JumpWazaSeq(WAZA_Chouhatsu2);
                result = 1;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 8:
            if ((u16)fightFloorCheckHuuinWazaFightOutPokemon(0, p, waza) == 1) {
                fightOutPokemonInitJoutaiKeep(p);
                fightOutPokemon_SetHuuinNoAttackFlag(p, 1);
                ServerStatusFlag |= 0x80000;
                fightMsgctrlSetValue(0x11, waza);
                fightSeq_JumpWazaSeq(WAZA_Huuin);
                result = 1;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 9:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 9) == 1) {
                s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 9);
                if (now >= fightOutPokemonGetKaisuuJoutaiDataId(p, 9)) {
                    fightOutPokemonInitJoutaiDataId(p, 9);
                    fightSeq_CallWazaSeq(WAZA_KonranEnd);
                } else {
                    fightOutPokemonSetNowKaisuuJoutaiDataId(p, 9, now + 1);
                    if (HSD_Rand() & 1) {
                        ServerWork[5] = 0;
                        fightSeq_CallWazaSeq(WAZA_Konran);
                    } else {
                        ServerWork[5] = 1;
                        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, p);
                        s32 tmp1 = fightSeqWazaDamageCalc(p, p, side, 1, 0x28, -1);
                        fightWaza_SetDamage(fw, tmp1);
                        fightOutPokemon_SetKonranMyselfAttackFlag(p, 1);
                        ServerStatusFlag |= 0x80000;
                        fightSeq_JumpWazaSeq(WAZA_Konran);
                    }
                }
                result = 1;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 10:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 5) == 1) {
                if (HSD_Rand() % 4 == 0) {
                    fightOutPokemon_SetMahiNoAttackFlag(p, 1);
                    fightOutPokemonInitJoutaiKeep(p);
                    ServerStatusFlag |= 0x80000;
                    fightSeq_JumpWazaSeq(WAZA_Mahi);
                    result = 1;
                }
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 11:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 0xA) == 1) {
                fightFloor_SetAppointPokemonPtr(0, fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(
                                                       fightOutPokemonGetUserFightTargetIdJoutaiDataId(p, 0xA), (s32)type));
                if (HSD_Rand() & 1) {
                    fightSeq_CallWazaSeq(WAZA_Meromero);
                } else {
                    fightOutPokemonInitJoutaiKeep(p);
                    fightOutPokemon_SetMeroMeroNoAttackFlag(p, 1);
                    ServerStatusFlag |= 0x80000;
                    fightSeq_CallWazaSeq(WAZA_Meromero);
                    fightSeq_JumpWazaSeq(WAZA_MeromeroNext);
                }
                result = 1;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 12:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 0xC) == 1) {
                s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0xC);
                if ((s8)(now + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0xC)) {
                    FightOutPokemon* target;
                    s16 damage;
                    fightOutPokemonInitJoutaiDataId(p, 0xC);
                    fightOutPokemonInitJoutaiDataId(p, 0x22);
                    ServerStatusFlag |= 0x02000000;
                    damage = fightOutPokemon_GetGamanDamageValue(p);
                    target = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightOutPokemon_GetGamanDamageTargetId(p), (s32)type);
                    if ((damage != 0 && (fightWazaSetUseWazaStatus(fw, 0x75), waza = fightOutPokemon_GetUseWazaDataId(p),
                                         fight_seq_gaman_damage = damage * 2, (u16)fightOutPokemonCheckFightOut(target) != 0)) ||
                        (target = fightSeqSelectDefensePokemonPtr(p, waza, type, 0, 1, 1, 0), (u16)fightOutPokemonCheckFightOut(target) != 0)) {
                        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, target);
                        fightSeq_JumpWazaSeq(WAZA_GamanOff);
                    } else {
                        fightSeq_JumpWazaSeq(WAZA_GamanFaild);
                    }
                } else {
                    fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0xC, now + 1);
                    fightSeq_JumpWazaSeq(WAZA_Gaman);
                }
                result = 1;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 13:
            if ((u16)fightOutPokemonIsJoutaiDataId(p, 7) == 1) {
                if (seqId == 0x7D) {
                    fightOutPokemonInitJoutaiDataId(p, 7);
                    ServerWork[5] = 1;
                    fightSeq_CallWazaSeq(WAZA_Melt);
                }
                result = 2;
            }
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 14:
            fightseq_attack_pokemon_joutai_check_buff++;
            break;
        case 15:
            break;
        }
    } while (fightseq_attack_pokemon_joutai_check_buff != 15 && result == 0);
    if (result == 2) {
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
    }
    return result;
}
}
}

extern "C" {
s32 fightSeqWazaOutBeforeCheckSub(FightOutPokemon* p) {
    if (fightOutPokemonIsJoutaiDataId(p, 0x13) == 1 && fightOutPokemon_GetMotoWazaDataId(p) != 0x63) {
        fightOutPokemonInitJoutaiDataId(p, 0x13);
    }
    return 1;
}
}

extern "C" {
void fightSeqGetExpCheck(void) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqGetExpCheckSub, 0, 0);
    fightSeqCheckZenmetu();
}
}

extern "C" {
void fightSeqCheckZenmetu(void) {
    fightSeq_CallWazaSeq(WAZA_Zenmetsu);
    fightSeqFightOutPokemonTokuseiCheckIkaku(1);
    fightSeqFightOutPokemonTokuseiCheckTrace();
    fightFloorLoopValidFightOutPokemon(0, _fightSeqGetExpCheckSubSoubiItemCheckTurn, 0, 0);
    fightSeqFightOutPokemonTokuseiCheckTenkiya();
}
}

static s32 _fightSeqGetExpCheckSubSoubiItemCheckTurn(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    FightOutPokemon* prev;
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    prev = fightFloor_GetAttackPokemonPtr(0);
    fightFloor_SetAttackPokemonPtr(0, p);
    fightSeqSoubiItemCheckTurn(p, 1);
    fightFloor_SetAttackPokemonPtr(0, prev);
    return 1;
}

static s32 _fightSeqGetExpCheckSub(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    if (fightOutPokemon_GetKizetuFlag(p) == 1) {
        fightFloor_SetKizetuPokemonPtr(0, p);
        fightFloor_SetDefensePokemonPtr(0, p);
        fightSeq_CallWazaSeq(WAZA_GetEXP);
    }
    return 1;
}

extern "C" {
void fightSeqSideJoutaiCheck2(void) {
    fightFloorLoopValidFightOutPokemon(0, _SideConditionCheck2SubMiraiyoti, 0, 0);
    wazaSequenceSysFreeAllWaza();
    fightFloorLoopValidFightOutPokemon(0, _SideConditionCheck2SubHorobinouta, 0, 1);
    wazaSequenceSysFreeAllWaza();
}
}

static s32 _SideConditionCheck2SubHorobinouta(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    FightWaza* waza;
    u8* seq;
    s8 total;
    s8 now;
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(p, 0x1E) == 1) {
        total = fightOutPokemonGetKaisuuJoutaiDataId(p, 0x1E);
        now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x1E);
        fightFloor_SetAttackPokemonPtr(0, p);
        waza = fightOutPokemon_GetFightWazaPtr(p);
        fightMsgctrlSetValue(0x2F, total - now);
        if (now >= total) {
            fightWaza_SetDamage(waza, (s32)pokemon_GetHp((Pokemon*)fightOutPokemonGetPokemonPtr(p)));
            fightOutPokemonInitJoutaiDataId(p, 0x1E);
            seq = WAZA_Horobinouta;
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x1E, now + 1);
            seq = WAZA_Horobinoutaing;
        }
        fightSeq_CallWazaSeq(seq);
        fightSeqGetExpCheck();
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    return 1;
}

static s32 _SideConditionCheck2SubMiraiyoti(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    FightOutPokemon* target;
    u8 buf[0xB0];
    FightWaza* waza;
    s32 damage;
    s8 total;
    s8 now;
    u16 wazaId;
    u32 targetId;
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(p, 0x34) == 1) {
        total = fightOutPokemonGetKaisuuJoutaiDataId(p, 0x34);
        now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x34);
        if (now >= total) {
            damage = fightOutPokemonGetBuffJoutaiDataId(p, 0x34);
            wazaId = fightOutPokemonGetIdBuffJoutaiDataId(p, 0x34);
            target = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightOutPokemonGetUserFightTargetIdJoutaiDataId(p, 0x34), id);
            if (fightOutPokemonCheckFightOut(target) == 0) {
                target = fightTargetGetPtrAsNowFightType(0xE, target);
            }
            if (wazaId == 0xF8) {
                ServerWork[5] = 0;
            } else {
                ServerWork[5] = 1;
            }
            fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(wazaId)));
            fightFloor_SetDefensePokemonPtr(0, p);
            targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(p, id);
            fightFloor_SetAttackPokemonPtr(0, target);
            waza = fightOutPokemon_GetFightWazaPtr(target);
            fightWazaBiosCopy(buf, waza);
            fightWazaCreate(waza, -1, wazaId, targetId, 0);
            fightWaza_SetDamage(waza, damage);
            fightOutPokemon_SetKaigaraDamageValue(p, 0xFFFF);
            fightOutPokemonInitJoutaiDataId(p, 0x34);
            fightSeq_CallWazaSeq(WAZA_Miraiyochi);
            fightWazaBiosCopy(waza, buf);
            fightSeqGetExpCheck();
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x34, now + 1);
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    return 1;
}

extern "C" {
void fightSeqSideJoutaiCheck(void) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqSideJoutaiCheckSub, 0, 1);
}
}

#define SIDE_BEGIN                                    \
    if (fightOutPokemonCheckFightOut(p) == 0) {       \
        return 1;                                     \
    }                                                 \
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
#define SIDE_END                    \
    ServerStatusFlag &= 0xFEFFFFDF; \
    wazaSequenceSysFreeAllWaza();
static s32 _fightSeqSideJoutaiCheckSub(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    Pokemon* pokemon;
    FightWaza* waza;
    u16 tokusei;
    if (fightGetFightResultId() != 0) {
        return 0;
    }
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    fightFloor_SetAttackPokemonPtr(0, p);
    pokemon = fightOutPokemonGetPokemonPtr(p);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    tokusei = fightOutPokemonGetTokuseiDataId(p);
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x25) == 1 && fightOutPokemonIsHpMantan(p) == 0) {
        fightWaza_SetDamage(waza, -(s32)fightOutPokemonMaxHpWaruValue(p, 0x10));
        fightSeq_CallWazaSeq(WAZA_Newoharu);
    }
    SIDE_END
    SIDE_BEGIN
    fightSeqFightOutPokemonTokuseiCheckTurn(p);
    SIDE_END
    SIDE_BEGIN
    fightSeqSoubiItemCheckTurn(p, 0);
    SIDE_END
    SIDE_BEGIN
    fightSeqSoubiItemCheckTurn(p, 1);
    SIDE_END
    SIDE_BEGIN
    {
    u16 tid;
    if (fightOutPokemonIsJoutaiDataId(p, 0x1C) == 1 && (tid = fightOutPokemonGetUserFightTargetIdJoutaiDataId(p, 0x1C)) != 0) {
        FightOutPokemon* target = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(tid, id);
        if (target != 0 && fightOutPokemonCheckFightOut(target) == 1) {
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, target);
            fightWaza_SetDamage(waza, (s32)fightOutPokemonMaxHpWaruValue(p, 8));
            UserWork[0x160A4] = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, id);
            UserWork[0x160A5] = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(p, id);
            fightSeq_CallWazaSeq(WAZA_Yadorigi);
        }
    }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 3) == 1) {
        fightWaza_SetDamage(waza, (s32)fightOutPokemonMaxHpWaruValue(p, 8));
        fightSeq_CallWazaSeq(WAZA_Dokudoku);
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 4) == 1) {
        s16 count = fightOutPokemonGetCountAsJoutaiDataId(p, 4);
        s32 m = fightOutPokemonMaxHpWaruValue(p, 0x10);
        m = m * count;
        fightWaza_SetDamage(waza, m);
        fightOutPokemonWriteJoutaiDataId(p, 4, 0);
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
        fightSeq_CallWazaSeq(WAZA_Dokudoku);
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 6) == 1) {
        fightWaza_SetDamage(waza, (s32)fightOutPokemonMaxHpWaruValue(p, 8));
        fightSeq_CallWazaSeq(WAZA_Yakedo);
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x17) == 1) {
        if (fightOutPokemonIsJoutaiDataId(p, 8) == 1) {
            fightWaza_SetDamage(waza, (s32)fightOutPokemonMaxHpWaruValue(p, 4));
            fightSeq_CallWazaSeq(WAZA_Akumu);
        } else {
            fightOutPokemonInitJoutaiDataId(p, 0x17);
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x18) == 1) {
        fightWaza_SetDamage(waza, (s32)fightOutPokemonMaxHpWaruValue(p, 4));
        fightSeq_CallWazaSeq(WAZA_Noroi);
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0xE) == 1) {
        u16 wazaId;
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0xE);
        wazaId = fightOutPokemonGetIdBuffJoutaiDataId(p, 0xE);
        u8* seq;
        fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(wazaId)));
        if (now >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0xE)) {
            fightOutPokemonInitJoutaiDataId(p, 0xE);
            seq = WAZA_ShimeEnd;
        } else {
            UserWork[0x160A4] = (u8)wazaId;
            UserWork[0x160A5] = (u8)(wazaId >> 8);
            fightWaza_SetDamage(waza, (s32)fightOutPokemonMaxHpWaruValue(p, 0x10));
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0xE, now + 1);
            seq = WAZA_Shime;
        }
        fightSeq_CallWazaSeq(seq);
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x3E) == 1) {
        s32 damage = fightOutPokemonMaxHpWaruValue(p, 0x10);
        damage = (HSD_Rand() % 3) + damage;
        damage = damage - 1;
        if (damage <= 0) {
            damage = 1;
        }
        fightWaza_SetDamage(waza, damage);
        fightSeq_CallWazaSeq(WAZA_Revers);
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0xB) == 1) {
        s8 now;
        fightFloorLoopValidFightOutPokemon(0, _fightSeqSideJoutaiCheckSubSawagu, 0, 0);
        fightFloor_SetAttackPokemonPtr(0, p);
        now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0xB);
        s32 cmpv = fightOutPokemonGetKaisuuJoutaiDataId(p, 0xB);
        if ((s8)(now + 1) >= cmpv) {
            fightOutPokemonInitJoutaiDataId(p, 0xB);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0xB, now + 1);
        }
        if (fightOutPokemonCheckNoAttackFlag(p) == 1) {
            fightOutPokemonInitJoutaiKeep(p);
            ServerWork[5] = 1;
        } else if (fightOutPokemonIsJoutaiDataId(p, 0xB) != 1) {
            fightOutPokemonInitJoutaiKeep(p);
            ServerWork[5] = 1;
        } else {
            fightOutPokemonWriteJoutaiDataId(p, 0x22, 0);
            ServerWork[5] = 0;
        }
        fightSeq_CallWazaSeq(WAZA_Sawagu);
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0xD) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0xD);
        s32 cmpv = fightOutPokemonGetKaisuuJoutaiDataId(p, 0xD);
        if ((s8)(now + 1) >= cmpv) {
            fightOutPokemonInitJoutaiDataId(p, 0xD);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0xD, now + 1);
        }
        if (fightOutPokemonCheckNoAttackFlag(p) == 1) {
            fightOutPokemonInitJoutaiKeep(p);
        } else if (fightOutPokemonIsJoutaiDataId(p, 0xD) == 0 && fightOutPokemonIsJoutaiDataId(p, 0x22) == 1) {
            fightOutPokemonInitJoutaiDataId(p, 0x22);
            if (fightOutPokemonIsJoutaiDataId(p, 9) == 0) {
                u8* saved = (u8*)TSUIKASeqTbl[7];
                void* seq;
                ServerWork[3] = 0x47;
                TSUIKASeqTbl[7] = WAZA_Null;
                seq = fightSeq_GetWazaSeq();
                fightSeqTuikaAct(1, 0);
                fightSeq_JumpWazaSeq(seq);
                TSUIKASeqTbl[7] = saved;
                if (fightOutPokemonIsJoutaiDataId(p, 9) == 1) {
                    fightSeq_CallWazaSeq(WAZA_AbareruEnd);
                }
            }
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x29) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x29);
        u16 wazaId = fightOutPokemonGetIdBuffJoutaiDataId(p, 0x29);
        fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x29, now + 1);
        if (pokemonSearchWazaDataId(pokemon, wazaId) < 0) {
            fightOutPokemonInitJoutaiDataId(p, 0x29);
        } else if ((s8)(now + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0x29)) {
            fightOutPokemonInitJoutaiDataId(p, 0x29);
            fightSeq_CallWazaSeq(WAZA_KanashibariEnd);
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x2A) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x2A);
        u16 wazaId = fightOutPokemonGetIdBuffJoutaiDataId(p, 0x2A);
        u32 slot = fightOutPokemonGetBuffJoutaiDataId(p, 0x2A);
        u16 cur = pokemon_GetPokemonWazaDataId(pokemon, slot);
        fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x2A, now + 1);
        if (cur != wazaId) {
            fightOutPokemonInitJoutaiDataId(p, 0x2A);
        } else if ((s8)(now + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0x2A) || pokemon_GetPokemonWazaPp(pokemon, slot) == 0) {
            fightOutPokemonInitJoutaiDataId(p, 0x2A);
            fightSeq_CallWazaSeq(WAZA_EncoreEnd);
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x1D) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x1D);
        s32 cmpv = fightOutPokemonGetKaisuuJoutaiDataId(p, 0x1D);
        if ((s8)(now + 1) >= cmpv) {
            fightOutPokemonInitJoutaiDataId(p, 0x1D);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x1D, now + 1);
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x24) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x24);
        s32 cmpv = fightOutPokemonGetKaisuuJoutaiDataId(p, 0x24);
        if ((s8)(now + 1) >= cmpv) {
            fightOutPokemonInitJoutaiDataId(p, 0x24);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x24, now + 1);
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x30) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x30);
        s32 cmpv = fightOutPokemonGetKaisuuJoutaiDataId(p, 0x30);
        if ((s8)(now + 1) >= cmpv) {
            fightOutPokemonInitJoutaiDataId(p, 0x30);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x30, now + 1);
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x26) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x26);
        s32 cmpv = fightOutPokemonGetKaisuuJoutaiDataId(p, 0x26);
        if ((s8)(now + 1) >= cmpv) {
            fightOutPokemonInitJoutaiDataId(p, 0x26);
            if (fightOutPokemonIsJoutaiNormal(p) == 1 && tokusei != 0x48 && tokusei != 0xF && fightSeqSawaguCheck(p) == 0 && fightSeqRegulationOverTwoCheck(8, p) != 1 && fightOutPokemonCheckWriteJoutaiDataId(p, 8) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, 8, 0);
                fightOutPokemonInitJoutaiKeep(p);
                fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
                fightFloor_SetTuikakoukaPokemonPtr(0, p);
                fightSeq_CallWazaSeq(WAZA_AddNemuri2);
            }
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x26, now + 1);
        }
    }
    SIDE_END
    SIDE_BEGIN
    fightSeqCheckDarkPokemonJoutaiHyperAct(p, 1);
    SIDE_END
    return 1;
}
#undef SIDE_BEGIN
#undef SIDE_END

static s32 _fightSeqSideJoutaiCheckSubSawagu(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    u16 tokusei = fightOutPokemonGetTokuseiDataId(p);
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    if (fightOutPokemonIsJoutaiDataId(p, 8) == 1 && tokusei != 0x2B) {
        fightOutPokemonInitJoutaiDataId(p, 8);
        fightOutPokemonInitJoutaiDataId(p, 0x17);
        ServerWork[5] = 1;
        fightFloor_SetAttackPokemonPtr(0, p);
        fightSeq_CallWazaSeq(WAZA_SawaguMezame);
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
    }
    return 1;
}

static s32 _fightSeqFloorJoutaiCheckSubGetSeqFightOutPokemonPtr(void* arg, u16 id, void* userData);
static s32 _fightSeqFloorJoutaiCheckSubNegaigoto(void* arg, u16 id, void* userData);

extern "C" {
void fightSeqFloorJoutaiCheck(void) {
    enum TsE { TsE0 };
    void* side;
    u8 tenkou;
    FightOutPokemon* weatherPokemon;
    u8 i;
    if (fightGetFightResultId() != 0) {
        return;
    }
    tenkou = fightFloorGetNowTenkouDataId(0, 0);
    fightFloorCreateFightOutPokemonPtrAry(0);
    fightFloorSortFightOutPokemonPtrAry(0, 1);
    weatherPokemon = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightSeqFloorJoutaiCheckSubGetSeqFightOutPokemonPtr, &weatherPokemon, 0);

    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(0, i);
        if (side) {
            FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0xC, (FightOutPokemon*)side);
            if (fightOutPokemonCheckFightOut(p) == 0) {
                p = fightTargetGetPtrAsNowFightType(0xD, (FightOutPokemon*)side);
            }
            fightFloor_SetAttackPokemonPtr(0, p);
            if (fightSideIsJoutaiDataId(side, 0x48) == 1) {
                s8 max = fightSideGetKaisuuJoutaiDataId((FightOutPokemon*)side, 0x48);
                enum TsE now = (enum TsE)(fightSideGetNowKaisuuJoutaiDataId((FightOutPokemon*)side, 0x48) + 1);
                if (now - 48 < max) {
                    fightSideSetNowKaisuuJoutaiDataId((FightOutPokemon*)side, 0x48, now);
                } else {
                    fightSideInitJoutaiDataId(side, 0x48);
                    u16 tmp1 = (u32)GSmsgGetGSchar(wazaDB_GetName(0x73));
                    fightMsgctrlSetValue(0xD, tmp1);
                    fightSeq_CallWazaSeq(WAZA_ReflecEnd);
                }
            }
        }
    }
    wazaSequenceSysFreeAllWaza();
    for (i = 0; i < 2; i++) {
        void* side = fightFloorGetValidFightSidePtr(0, i);
        if (side) {
            FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0xC, (FightOutPokemon*)side);
            if (fightOutPokemonCheckFightOut(p) == 0) {
                p = fightTargetGetPtrAsNowFightType(0xD, (FightOutPokemon*)side);
            }
            fightFloor_SetAttackPokemonPtr(0, p);
            if (fightSideIsJoutaiDataId(side, 0x49) == 1) {
                s8 max = fightSideGetKaisuuJoutaiDataId((FightOutPokemon*)side, 0x49);
                s8 now = (enum TsE)(fightSideGetNowKaisuuJoutaiDataId((FightOutPokemon*)side, 0x49) + 1);
                if (now < max) {
                    fightSideSetNowKaisuuJoutaiDataId((FightOutPokemon*)side, 0x49, now);
                } else {
                    fightSideInitJoutaiDataId(side, 0x49);
                    fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(0x71)));
                    ServerWork[5] = i;
                    fightSeq_CallWazaSeq(WAZA_ReflecEnd);
                }
            }
        }
    }
    wazaSequenceSysFreeAllWaza();
    for (i = 0; i < 2; i++) {
        void* side = fightFloorGetValidFightSidePtr(0, i);
        if (side) {
            FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0xC, (FightOutPokemon*)side);
            if (fightOutPokemonCheckFightOut(p) == 0) {
                p = fightTargetGetPtrAsNowFightType(0xD, (FightOutPokemon*)side);
            }
            fightFloor_SetAttackPokemonPtr(0, p);
            if (fightSideIsJoutaiDataId(side, 0x4C) == 1) {
                s8 max = fightSideGetKaisuuJoutaiDataId((FightOutPokemon*)side, 0x4C);
                s8 now = (enum TsE)(fightSideGetNowKaisuuJoutaiDataId((FightOutPokemon*)side, 0x4C) + 1);
                if (now < max) {
                    fightSideSetNowKaisuuJoutaiDataId((FightOutPokemon*)side, 0x4C, now);
                } else {
                    fightSideInitJoutaiDataId(side, 0x4C);
                    fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(0x36)));
                    fightSeq_CallWazaSeq(WAZA_ReflecEnd);
                }
            }
        }
    }
    wazaSequenceSysFreeAllWaza();
    for (i = 0; i < 2; i++) {
        void* side = fightFloorGetValidFightSidePtr(0, i);
        if (side) {
            FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0xC, (FightOutPokemon*)side);
            if (fightOutPokemonCheckFightOut(p) == 0) {
                p = fightTargetGetPtrAsNowFightType(0xD, (FightOutPokemon*)side);
            }
            fightFloor_SetAttackPokemonPtr(0, p);
            if (fightSideIsJoutaiDataId(side, 0x4B) == 1) {
                s8 max = fightSideGetKaisuuJoutaiDataId((FightOutPokemon*)side, 0x4B);
                s8 now = (enum TsE)(fightSideGetNowKaisuuJoutaiDataId((FightOutPokemon*)side, 0x4B) + 1);
                if (now < max) {
                    fightSideSetNowKaisuuJoutaiDataId((FightOutPokemon*)side, 0x4B, now);
                } else {
                    fightSideInitJoutaiDataId(side, 0x4B);
                    fightSeq_CallWazaSeq(WAZA_ShinpiEnd);
                }
            }
        }
    }
    wazaSequenceSysFreeAllWaza();
    fightFloorLoopValidFightOutPokemon(0, _fightSeqFloorJoutaiCheckSubNegaigoto, 0, 1);
    wazaSequenceSysFreeAllWaza();

    if (tenkou == 2) {
        fightFloor_SetAttackPokemonPtr(0, weatherPokemon);
        if (fightFloorIsJoutaiDataId(0, 0x50) == 0) {
            s8 max = fightFloorGetKaisuuJoutaiDataId(0, 0x55);
            s8 now = (enum TsE)(fightFloorGetNowKaisuuJoutaiDataId(0, 0x55) + 1);
            if (now < max) {
                fightFloorSetNowKaisuuJoutaiDataId(0, 0x55, now);
                ServerWork[5] = 0;
            } else {
                fightFloorInitJoutaiDataId(0, 0x55);
                ServerWork[5] = 2;
            }
        } else {
            ServerWork[5] = 0;
        }
        fightSeq_CallWazaSeq(WAZA_Amefuri);
    }
    wazaSequenceSysFreeAllWaza();
    if (fightGetFightResultId() != 0) {
        return;
    }
    if (tenkou == 3) {
        u8* seq;
        fightFloor_SetAttackPokemonPtr(0, weatherPokemon);
        if (fightFloorIsJoutaiDataId(0, 0x51) == 1) {
            seq = WAZA_WeatherDamage;
        } else {
            s8 max = fightFloorGetKaisuuJoutaiDataId(0, 0x56);
            s8 now = (enum TsE)(fightFloorGetNowKaisuuJoutaiDataId(0, 0x56) + 1);
            if (now < max) {
                fightFloorSetNowKaisuuJoutaiDataId(0, 0x56, now);
                seq = WAZA_WeatherDamage;
            } else {
                fightFloorInitJoutaiDataId(0, 0x56);
                seq = WAZA_WeatherDamageEnd;
            }
        }
        UserWork[0x160A4] = 0xC;
        ServerWork[5] = 0;
        fightSeq_CallWazaSeq(seq);
    }
    wazaSequenceSysFreeAllWaza();
    if (fightGetFightResultId() != 0) {
        return;
    }
    if (tenkou == 1) {
        u8* seq;
        fightFloor_SetAttackPokemonPtr(0, weatherPokemon);
        if (fightFloorIsJoutaiDataId(0, 0x4F) == 1) {
            seq = WAZA_Hare;
        } else {
            s8 max = fightFloorGetKaisuuJoutaiDataId(0, 0x54);
            s8 now = (enum TsE)(fightFloorGetNowKaisuuJoutaiDataId(0, 0x54) + 1);
            if (now < max) {
                fightFloorSetNowKaisuuJoutaiDataId(0, 0x54, now);
                seq = WAZA_Hare;
            } else {
                fightFloorInitJoutaiDataId(0, 0x54);
                seq = WAZA_HareEnd;
            }
        }
        fightSeq_CallWazaSeq(seq);
    }
    wazaSequenceSysFreeAllWaza();
    if (fightGetFightResultId() != 0) {
        return;
    }
    if (tenkou == 4) {
        u8* seq;
        fightFloor_SetAttackPokemonPtr(0, weatherPokemon);
        {
            s8 max = fightFloorGetKaisuuJoutaiDataId(0, 0x53);
            s8 now = (enum TsE)(fightFloorGetNowKaisuuJoutaiDataId(0, 0x53) + 1);
            if (now < max) {
                fightFloorSetNowKaisuuJoutaiDataId(0, 0x53, now);
                seq = WAZA_WeatherDamage;
            } else {
                fightFloorInitJoutaiDataId(0, 0x53);
                seq = WAZA_WeatherDamageEnd;
            }
        }
        UserWork[0x160A4] = 0xD;
        ServerWork[5] = 1;
        fightSeq_CallWazaSeq(seq);
    }
    wazaSequenceSysFreeAllWaza();
    if (fightGetFightResultId() != 0) {
        return;
    }
    if (tenkou == 5) {
        u8* seq;
        fightFloor_SetAttackPokemonPtr(0, weatherPokemon);
        {
            s8 max = fightFloorGetKaisuuJoutaiDataId(0, 0x52);
            s8 now = (enum TsE)(fightFloorGetNowKaisuuJoutaiDataId(0, 0x52) + 1);
            if (now < max) {
                fightFloorSetNowKaisuuJoutaiDataId(0, 0x52, now);
                seq = WAZA_WeatherDamage;
            } else {
                fightFloorInitJoutaiDataId(0, 0x52);
                seq = WAZA_WeatherDamageEnd;
            }
        }
        UserWork[0x160A4] = 0x25;
        ServerWork[5] = 2;
        fightSeq_CallWazaSeq(seq);
    }
    wazaSequenceSysFreeAllWaza();
    if (fightGetFightResultId() != 0) {
        return;
    }
}
}

static s32 _fightSeqFloorJoutaiCheckSubGetSeqFightOutPokemonPtr(void* arg, u16 id, void* userData) {
    if (fightOutPokemon_GetSequencePtr((FightOutPokemon*)arg) != 0) {
        if (userData != 0) {
            *(void**)userData = arg;
        }
        return 0;
    }
    return 1;
}

static s32 _fightSeqFloorJoutaiCheckSubNegaigoto(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    s8 count;
    s8 now;
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    if (fightOutPokemonIsJoutaiDataId(p, 0x35) == 1) {
        count = fightOutPokemonGetKaisuuJoutaiDataId(p, 0x35);
        now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x35);
        if ((s8)(now + 1) < count) {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x35, now + 1);
        } else {
            fightFloor_SetAttackPokemonPtr(0, p);
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, p);
            fightSeq_CallWazaSeq(WAZA_Negaigoto);
            fightOutPokemonInitJoutaiDataId(p, 0x35);
        }
    }
    return 1;
}

extern "C" {
void fightSeqPressurePpdecCheckHorobinouta(FightOutPokemon* p) {
    Pokemon* pokemon;
    u8 count;
    s8 slot;
    if (p != 0) {
        count = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(0, 0x2E, 0, p);
        if (count != 0) {
            pokemon = fightOutPokemonGetPokemonPtr(p);
            slot = pokemonSearchWazaDataId(pokemon, 0xC3);
            if (slot >= 0) {
                u8 pp = pokemon_GetPokemonWazaPp(pokemon, slot);
                if (pp > count) {
                    pp -= count;
                } else {
                    pp = 0;
                }
                pokemon_SetPokemonWazaPp(pokemon, slot, pp);
                fightSeqPpdecMonomane(p, slot, 0);
            }
        }
    }
}
}

extern "C" {
void fightSeqPressurePpdecCheckHuuin(FightOutPokemon* p) {
    Pokemon* pokemon;
    u8 count;
    s8 slot;
    if (p != 0) {
        count = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(0, 0x2E, 2, p);
        if (count != 0) {
            pokemon = fightOutPokemonGetPokemonPtr(p);
            slot = pokemonSearchWazaDataId(pokemon, 0x11E);
            if (slot >= 0) {
                u8 pp = pokemon_GetPokemonWazaPp(pokemon, slot);
                if (pp > count) {
                    pp -= count;
                } else {
                    pp = 0;
                }
                pokemon_SetPokemonWazaPp(pokemon, slot, pp);
                fightSeqPpdecMonomane(p, slot, 0);
            }
        }
    }
}
}

extern "C" {
void fightSeqPressurePpdecCheck(FightOutPokemon* p, FightOutPokemon* q, u16 waza) {
    Pokemon* pokemon;
    s8 slot;
    if (p != 0 && q != 0) {
        if (fightOutPokemonGetTokuseiDataId(p) == 0x2E) {
            pokemon = fightOutPokemonGetPokemonPtr(q);
            slot = pokemonSearchWazaDataId(pokemon, waza);
            if (slot >= 0) {
                u8 pp = pokemon_GetPokemonWazaPp(pokemon, slot);
                if (pp != 0) {
                    pp--;
                }
                pokemon_SetPokemonWazaPp(pokemon, slot, pp);
                fightSeqPpdecMonomane(q, slot, 0);
            }
        }
    }
}
}

extern "C" {
s32 fightSeqWazaDamageCalcHikaePokemon(FightOutPokemon* attacker, FightPokemon* defender, void* attackSide, u16 waza,
                           u16 iryoku, s32 zokusei) {
    u32 tenkou;
    u8 badgeCheck;
    s32 itemFlag;
    u16 power;
    u16 type;
    s32 kind;
    s32 range;
    u8 critical;
    u16 attackerTokusei;
    u16 attackerItem;
    s32 attackerItemBuff;
    u16 attackerPokemonId;
    Pokemon* attackerPokemon;
    u16 attack;
    u16 specialAttack;
    HeroPtr* attackerHero;
    u32 attackBuff;
    u32 specialAttackBuff;
    u32 level;
    u16 defenderTokusei;
    u16 defenderItem;
    u16 defenderPokemonId;
    u16 defense;
    u16 specialDefense;
    HeroPtr* defenderHero;
    u32 defenseBuff;
    u32 specialDefenseBuff;
    u16 activeCount;
    u32 i;
    s32 offset;
    u32 atkValue;
    u32 defValue;
    s32 damage;

    tenkou = fightFloorGetNowTenkouDataId(0, 1);
    badgeCheck = fightFloor_GetFightKindDoBadgeCheckFlag(0);
    itemFlag = fightFloor_GetFightKindDoItemSoubiTokukoutokubouupFlag(0);
    if (iryoku == 0) {
        power = wazaDB_GetIryoku(waza);
    } else {
        power = iryoku;
    }
    if (zokusei < 0) {
        type = wazaDB_GetZokuseiDataId(waza);
    } else {
        type = zokusei;
    }
    if (wazaCheckDarkWaza(waza) == 1) {
        kind = waza_GetZokuseiKindData(waza);
    } else {
        kind = zokuseiBiosGetWazaKind(type);
    }
    range = wazaDB_GetRangeId(waza);
    critical = fightWaza_GetCritical(fightOutPokemon_GetFightWazaPtr(attacker));

    attackerTokusei = fightOutPokemonGetTokuseiDataId(attacker);
    attackerItem = fightOutPokemonGetSoubiItemSoubiDataId(attacker);
    attackerItemBuff = figthOutPokemonGetSoubiItemBuff(attacker);
    attackerPokemonId = figthOutPokemonGetPokemonDataId(attacker);
    attackerPokemon = fightOutPokemonGetPokemonPtr(attacker);
    attack = pokemon_GetPhyAtk(attackerPokemon);
    specialAttack = pokemon_GetSpeAtk(attackerPokemon);
    attackerHero = fightFloorGetFightOutPokemonPtrToHeroPtr(0, attacker);
    attackBuff = fightOutPokemon_GetAbicntPhyAtk(attacker);
    specialAttackBuff = fightOutPokemon_GetAbicntSpeAtk(attacker);
    level = figthOutPokemonGetLevel(attacker);

    defenderPokemonId = pokemon_GetPokemonDataId(fightPokemon_GetPokemonBuffPtr(defender));
    defenderTokusei = pokemonDB_GetTokuseiDataId(defenderPokemonId,
                                                 pokemon_GetTokuseiFlag(fightPokemon_GetPokemonBuffPtr(defender)));
    defenderItem = pokemonGetSoubiItemSoubiDataId(fightPokemon_GetPokemonBuffPtr(defender));
    pokemonGetSoubiItemBuff(fightPokemon_GetPokemonBuffPtr(defender));
    defense = pokemon_GetPhyDef(fightPokemon_GetPokemonBuffPtr(defender));
    specialDefense = pokemon_GetSpeDef(fightPokemon_GetPokemonBuffPtr(defender));
    defenderHero = (HeroPtr*)fightTrainer_GetHeroPtr((void*)fightFloorGetFightPokemonPtrToFightTrainerPtr(0, defender));
    defenseBuff = 6;
    specialDefenseBuff = 6;
    activeCount = 1;

    if (attackerTokusei == 0x25 || attackerTokusei == 0x4A) {
        attack *= 2;
    }
    if (badgeCheck == 1 && (bool)heroGetStatus(attackerHero, 0xF, 0) == 1) {
        attack = (attack * 0x6E) / 100;
    }
    if (badgeCheck == 1 && (bool)heroGetStatus(defenderHero, 0x13, 0) == 1) {
        defense = (defense * 0x6E) / 100;
    }
    if (badgeCheck == 1 && (bool)heroGetStatus(attackerHero, 0x15, 0) == 1) {
        specialAttack = (specialAttack * 0x6E) / 100;
    }
    if (badgeCheck == 1 && (bool)heroGetStatus(defenderHero, 0x15, 0) == 1) {
        specialDefense = (specialDefense * 0x6E) / 100;
    }

    for (i = 0, offset = 0; i < 0x11; i++, offset += 2) {
        if (attackerItem == SoubiItemWazaTypePowUpTbl[offset] && type == SoubiItemWazaTypePowUpTbl[offset + 1]) {
            switch ((u8)kind) {
            case 1:
                attack = (attack * (attackerItemBuff + 100)) / 100;
                break;
            case 2:
                specialAttack = (specialAttack * (attackerItemBuff + 100)) / 100;
                break;
            }
        }
    }

    if (attackerItem == 0x1D) {
        attack = (attack * 0x96) / 100;
    }
    if ((u8)itemFlag == 1 && attackerItem == 0x22 && (attackerPokemonId == 0x198 || attackerPokemonId == 0x197)) {
        specialAttack = (specialAttack * 0x96) / 100;
    }
    if ((u8)itemFlag == 1 && defenderItem == 0x22 && (defenderPokemonId == 0x198 || defenderPokemonId == 0x197)) {
        specialDefense = (specialDefense * 0x96) / 100;
    }
    if (attackerItem == 0x23 && attackerPokemonId == 0x175) {
        specialAttack *= 2;
    }
    if (defenderItem == 0x24 && defenderPokemonId == 0x175) {
        specialDefense *= 2;
    }
    if (attackerItem == 0x2D && attackerPokemonId == 0x19) {
        specialAttack *= 2;
    }
    if (defenderItem == 0x40 && defenderPokemonId == 0x84) {
        defense *= 2;
    }
    if (attackerItem == 0x41 && (attackerPokemonId == 0x68 || attackerPokemonId == 0x69)) {
        attack *= 2;
    }
    if ((u16)defenderTokusei == 0x2F && (type == 10 || type == 0xF)) {
        specialAttack /= 2;
    }
    if (attackerTokusei == 0x37) {
        attack = (attack * 0x96) / 100;
    }
    if (attackerTokusei == 0x39 && fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(0, 0x3A, 0, 0) != 0) {
        specialAttack = (specialAttack * 0x96) / 100;
    }
    if (attackerTokusei == 0x3A && fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(0, 0x39, 0, 0) != 0) {
        specialAttack = (specialAttack * 0x96) / 100;
    }
    if (attackerTokusei == 0x3E && fightOutPokemonIsJoutaiNormal(attacker) == 0) {
        attack = (attack * 0x96) / 100;
    }
    if ((u16)defenderTokusei == 0x3F && pokemonIsJoutaiNormal(fightPokemon_GetPokemonBuffPtr(defender)) == 0) {
        defense = (defense * 0x96) / 100;
    }
    if (type == 0xD && fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(0, 0x38) != 0) {
        power /= 2;
    }
    if (type == 10 && fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(0, 0x39) != 0) {
        power /= 2;
    }
    if (type == 0xC && attackerTokusei == 0x41 && fightOutPokemonIsNokoriHpFollowing(attacker, 3) != 0) {
        power = (power * 0x96) / 100;
    }
    if (type == 10 && attackerTokusei == 0x42 && fightOutPokemonIsNokoriHpFollowing(attacker, 3) != 0) {
        power = (power * 0x96) / 100;
    }
    if (type == 0xB && attackerTokusei == 0x43 && fightOutPokemonIsNokoriHpFollowing(attacker, 3) != 0) {
        power = (power * 0x96) / 100;
    }
    if (type == 6 && attackerTokusei == 0x44 && fightOutPokemonIsNokoriHpFollowing(attacker, 3) != 0) {
        power = (power * 0x96) / 100;
    }

    if (wazaDB_GetSeqId(waza) == 7) {
        defense /= 2;
    }

    switch ((u8)kind) {
    case 1:
        if (critical == 2) {
            if ((u8)attackBuff > 6) {
                atkValue = fightAbicntDoKakeWaru((u8)attackBuff, attack);
            } else {
                atkValue = attack;
            }
        } else {
            atkValue = fightAbicntDoKakeWaru((u8)attackBuff, attack);
        }
        if (critical == 2) {
            if ((u8)defenseBuff < 6) {
                defValue = fightAbicntDoKakeWaru((u8)defenseBuff, defense);
            } else {
                defValue = defense;
            }
        } else {
            defValue = fightAbicntDoKakeWaru((u8)defenseBuff, defense);
        }
        damage = atkValue * power * ((u8)level * 2 / 5 + 2) / defValue;
        damage /= 50;
        if (fightOutPokemonIsJoutaiDataId(attacker, 6) == 1 && attackerTokusei != 0x3E) {
            damage /= 2;
        }
        if (fightSideIsJoutaiDataId(attackSide, 0x48) == 1 && critical == 1) {
            if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && activeCount >= 2) {
                damage = (damage / 3) * 2;
            } else {
                damage /= 2;
            }
        }
        if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && (u8)range == 4 && activeCount >= 2) {
            damage /= 2;
        }
        if (damage == 0) {
            damage = 1;
        }
        break;
    case 2:
        if (critical == 2) {
            if ((u8)specialAttackBuff > 6) {
                atkValue = fightAbicntDoKakeWaru((u8)specialAttackBuff, specialAttack);
            } else {
                atkValue = specialAttack;
            }
        } else {
            atkValue = fightAbicntDoKakeWaru((u8)specialAttackBuff, specialAttack);
        }
        if (critical == 2) {
            if ((u8)specialDefenseBuff < 6) {
                defValue = fightAbicntDoKakeWaru((u8)specialDefenseBuff, specialDefense);
            } else {
                defValue = specialDefense;
            }
        } else {
            defValue = fightAbicntDoKakeWaru((u8)specialDefenseBuff, specialDefense);
        }
        damage = atkValue * power * ((u8)level * 2 / 5 + 2) / defValue;
        damage /= 50;
        if (fightSideIsJoutaiDataId(attackSide, 0x49) == 1 && critical == 1) {
            if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && activeCount >= 2) {
                damage = (damage / 3) * 2;
            } else {
                damage /= 2;
            }
        }
        if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && (u8)range == 4 && activeCount >= 2) {
            damage /= 2;
        }
        if ((u8)tenkou == 2) {
            switch (type) {
            case 10:
                damage /= 2;
                break;
            case 11:
                damage = (damage * 0xF) / 10;
                break;
            }
        }
        if (tenkouDataBiosGetSolarFlag((u8)tenkou) == 0 && waza == 0x4C) {
            damage /= 2;
        }
        if ((u8)tenkou == 1) {
            switch (type) {
            case 10:
                damage = (damage * 0xF) / 10;
                break;
            case 11:
                damage /= 2;
                break;
            }
        }
        if (fightOutPokemonIsJoutaiDataId(attacker, 0x3A) == 1 && type == 10) {
            damage = (damage * 0xF) / 10;
        }
        break;
    default:
        damage = 0;
        break;
    }
    return damage + 2;
}

s32 fightSeqWazaDamageCalc(FightOutPokemon* attacker, FightOutPokemon* defender, void* attackSide, u16 waza,
                           u16 iryoku, s32 zokusei) {
    u32 tenkou;
    u8 badgeCheck;
    s32 itemFlag;
    u16 power;
    u16 type;
    s32 kind;
    s32 range;
    u8 critical;
    u16 attackerTokusei;
    u16 attackerItem;
    s32 attackerItemBuff;
    u16 attackerPokemonId;
    Pokemon* attackerPokemon;
    u16 attack;
    u16 specialAttack;
    HeroPtr* attackerHero;
    u32 attackBuff;
    u32 specialAttackBuff;
    u32 level;
    u32 defenderTokusei;
    u16 defenderItem;
    u16 defenderPokemonId;
    Pokemon* defenderPokemon;
    u16 defense;
    u16 specialDefense;
    HeroPtr* defenderHero;
    u32 defenseBuff;
    u32 specialDefenseBuff;
    u16 activeCount;
    u32 i;
    s32 offset;
    u32 atkValue;
    u32 defValue;
    s32 damage;

    tenkou = fightFloorGetNowTenkouDataId(0, 1);
    badgeCheck = fightFloor_GetFightKindDoBadgeCheckFlag(0);
    itemFlag = fightFloor_GetFightKindDoItemSoubiTokukoutokubouupFlag(0);
    if (iryoku == 0) {
        power = wazaDB_GetIryoku(waza);
    } else {
        power = iryoku;
    }
    if (zokusei < 0) {
        type = wazaDB_GetZokuseiDataId(waza);
    } else {
        type = zokusei;
    }
    if (wazaCheckDarkWaza(waza) == 1) {
        kind = waza_GetZokuseiKindData(waza);
    } else {
        kind = zokuseiBiosGetWazaKind(type);
    }
    range = wazaDB_GetRangeId(waza);
    critical = fightWaza_GetCritical(fightOutPokemon_GetFightWazaPtr(attacker));

    attackerTokusei = fightOutPokemonGetTokuseiDataId(attacker);
    attackerItem = fightOutPokemonGetSoubiItemSoubiDataId(attacker);
    attackerItemBuff = figthOutPokemonGetSoubiItemBuff(attacker);
    attackerPokemonId = figthOutPokemonGetPokemonDataId(attacker);
    attackerPokemon = fightOutPokemonGetPokemonPtr(attacker);
    attack = pokemon_GetPhyAtk(attackerPokemon);
    specialAttack = pokemon_GetSpeAtk(attackerPokemon);
    attackerHero = fightFloorGetFightOutPokemonPtrToHeroPtr(0, attacker);
    attackBuff = fightOutPokemon_GetAbicntPhyAtk(attacker);
    specialAttackBuff = fightOutPokemon_GetAbicntSpeAtk(attacker);
    level = figthOutPokemonGetLevel(attacker);

    defenderTokusei = fightOutPokemonGetTokuseiDataId(defender);
    defenderItem = fightOutPokemonGetSoubiItemSoubiDataId(defender);
    figthOutPokemonGetSoubiItemBuff(defender);
    defenderPokemonId = figthOutPokemonGetPokemonDataId(defender);
    defenderPokemon = fightOutPokemonGetPokemonPtr(defender);
    defense = pokemon_GetPhyDef(defenderPokemon);
    specialDefense = pokemon_GetSpeDef(defenderPokemon);
    defenderHero = fightFloorGetFightOutPokemonPtrToHeroPtr(0, defender);
    defenseBuff = fightOutPokemon_GetAbicntPhyDef(defender);
    specialDefenseBuff = fightOutPokemon_GetAbicntSpeDef(defender);
    activeCount = fightFloorGetValidFightOutPokemonCount(0, 1, defender, 0);

    if (attackerTokusei == 0x25 || attackerTokusei == 0x4A) {
        attack *= 2;
    }
    if (badgeCheck == 1 && (bool)heroGetStatus(attackerHero, 0xF, 0) == 1) {
        attack = (attack * 0x6E) / 100;
    }
    if (badgeCheck == 1 && (bool)heroGetStatus(defenderHero, 0x13, 0) == 1) {
        defense = (defense * 0x6E) / 100;
    }
    if (badgeCheck == 1 && (bool)heroGetStatus(attackerHero, 0x15, 0) == 1) {
        specialAttack = (specialAttack * 0x6E) / 100;
    }
    if (badgeCheck == 1 && (bool)heroGetStatus(defenderHero, 0x15, 0) == 1) {
        specialDefense = (specialDefense * 0x6E) / 100;
    }

    for (i = 0, offset = 0; i < 0x11; i++, offset += 2) {
        if (attackerItem == SoubiItemWazaTypePowUpTbl[offset] && type == SoubiItemWazaTypePowUpTbl[offset + 1]) {
            switch ((u8)kind) {
            case 1:
                attack = (attack * (attackerItemBuff + 100)) / 100;
                break;
            case 2:
                specialAttack = (specialAttack * (attackerItemBuff + 100)) / 100;
                break;
            }
        }
    }

    if (attackerItem == 0x1D) {
        attack = (attack * 0x96) / 100;
    }
    if ((u8)itemFlag == 1 && attackerItem == 0x22 && (attackerPokemonId == 0x198 || attackerPokemonId == 0x197)) {
        specialAttack = (specialAttack * 0x96) / 100;
    }
    if ((u8)itemFlag == 1 && defenderItem == 0x22 && (defenderPokemonId == 0x198 || defenderPokemonId == 0x197)) {
        specialDefense = (specialDefense * 0x96) / 100;
    }
    if (attackerItem == 0x23 && attackerPokemonId == 0x175) {
        specialAttack *= 2;
    }
    if (defenderItem == 0x24 && defenderPokemonId == 0x175) {
        specialDefense *= 2;
    }
    if (attackerItem == 0x2D && attackerPokemonId == 0x19) {
        specialAttack *= 2;
    }
    if (defenderItem == 0x40 && defenderPokemonId == 0x84) {
        defense *= 2;
    }
    if (attackerItem == 0x41 && (attackerPokemonId == 0x68 || attackerPokemonId == 0x69)) {
        attack *= 2;
    }
    if ((u16)defenderTokusei == 0x2F && (type == 10 || type == 0xF)) {
        specialAttack /= 2;
    }
    if (attackerTokusei == 0x37) {
        attack = (attack * 0x96) / 100;
    }
    if (attackerTokusei == 0x39 && fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(0, 0x3A, 0, 0) != 0) {
        specialAttack = (specialAttack * 0x96) / 100;
    }
    if (attackerTokusei == 0x3A && fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(0, 0x39, 0, 0) != 0) {
        specialAttack = (specialAttack * 0x96) / 100;
    }
    if (attackerTokusei == 0x3E && fightOutPokemonIsJoutaiNormal(attacker) == 0) {
        attack = (attack * 0x96) / 100;
    }
    if ((u16)defenderTokusei == 0x3F && fightOutPokemonIsJoutaiNormal(defender) == 0) {
        defense = (defense * 0x96) / 100;
    }
    if (type == 0xD && fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(0, 0x38) != 0) {
        power /= 2;
    }
    if (type == 10 && fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(0, 0x39) != 0) {
        power /= 2;
    }
    if (type == 0xC && attackerTokusei == 0x41 && fightOutPokemonIsNokoriHpFollowing(attacker, 3) != 0) {
        power = (power * 0x96) / 100;
    }
    if (type == 10 && attackerTokusei == 0x42 && fightOutPokemonIsNokoriHpFollowing(attacker, 3) != 0) {
        power = (power * 0x96) / 100;
    }
    if (type == 0xB && attackerTokusei == 0x43 && fightOutPokemonIsNokoriHpFollowing(attacker, 3) != 0) {
        power = (power * 0x96) / 100;
    }
    if (type == 6 && attackerTokusei == 0x44 && fightOutPokemonIsNokoriHpFollowing(attacker, 3) != 0) {
        power = (power * 0x96) / 100;
    }

    if (wazaDB_GetSeqId(waza) == 7) {
        defense /= 2;
    }

    switch ((u8)kind) {
    case 1:
        if (critical == 2) {
            if ((u8)attackBuff > 6) {
                atkValue = fightAbicntDoKakeWaru((u8)attackBuff, attack);
            } else {
                atkValue = attack;
            }
        } else {
            atkValue = fightAbicntDoKakeWaru((u8)attackBuff, attack);
        }
        if (critical == 2) {
            if ((u8)defenseBuff < 6) {
                defValue = fightAbicntDoKakeWaru((u8)defenseBuff, defense);
            } else {
                defValue = defense;
            }
        } else {
            defValue = fightAbicntDoKakeWaru((u8)defenseBuff, defense);
        }
        damage = atkValue * power * ((u8)level * 2 / 5 + 2) / defValue;
        damage /= 50;
        if (fightOutPokemonIsJoutaiDataId(attacker, 6) == 1 && attackerTokusei != 0x3E) {
            damage /= 2;
        }
        if (fightSideIsJoutaiDataId(attackSide, 0x48) == 1 && critical == 1) {
            if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && activeCount >= 2) {
                damage = (damage / 3) * 2;
            } else {
                damage /= 2;
            }
        }
        if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && (u8)range == 4 && activeCount >= 2) {
            damage /= 2;
        }
        if (damage == 0) {
            damage = 1;
        }
        break;
    case 2:
        if (critical == 2) {
            if ((u8)specialAttackBuff > 6) {
                atkValue = fightAbicntDoKakeWaru((u8)specialAttackBuff, specialAttack);
            } else {
                atkValue = specialAttack;
            }
        } else {
            atkValue = fightAbicntDoKakeWaru((u8)specialAttackBuff, specialAttack);
        }
        if (critical == 2) {
            if ((u8)specialDefenseBuff < 6) {
                defValue = fightAbicntDoKakeWaru((u8)specialDefenseBuff, specialDefense);
            } else {
                defValue = specialDefense;
            }
        } else {
            defValue = fightAbicntDoKakeWaru((u8)specialDefenseBuff, specialDefense);
        }
        damage = atkValue * power * ((u8)level * 2 / 5 + 2) / defValue;
        damage /= 50;
        if (fightSideIsJoutaiDataId(attackSide, 0x49) == 1 && critical == 1) {
            if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && activeCount >= 2) {
                damage = (damage / 3) * 2;
            } else {
                damage /= 2;
            }
        }
        if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && (u8)range == 4 && activeCount >= 2) {
            damage /= 2;
        }
        if ((u8)tenkou == 2) {
            switch (type) {
            case 10:
                damage /= 2;
                break;
            case 11:
                damage = (damage * 0xF) / 10;
                break;
            }
        }
        if (tenkouDataBiosGetSolarFlag((u8)tenkou) == 0 && waza == 0x4C) {
            damage /= 2;
        }
        if ((u8)tenkou == 1) {
            switch (type) {
            case 10:
                damage = (damage * 0xF) / 10;
                break;
            case 11:
                damage /= 2;
                break;
            }
        }
        if (fightOutPokemonIsJoutaiDataId(attacker, 0x3A) == 1 && type == 10) {
            damage = (damage * 0xF) / 10;
        }
        break;
    default:
        damage = 0;
        break;
    }
    if ((u8)tenkou == 5 && wazaCheckDarkWaza(waza) == 1) {
        damage = (damage * 0xF) / 10;
    }
    return damage + 2;
}

void fightSeqIrekaeInit(FightOutPokemon* newP, FightOutPokemon* oldP, u8 kind) {
    u16 ids[11] = {0xF, 0x16, 9, 0x18, 0x14, 0x1C, 0x1D, 0x1E, 0x25, 0x38, 0x39};
    IrekaeArg arg;
    u16 id;
    u8 i;
    u16 mode = 0;
    if (kind == 1) {
        mode = 0x7F;
    }
    if (mode == 0x7F) {
        fightOutPokemonCopyAllAbiCnt(newP, oldP);
        for (i = 0; i < 11; i++) {
            id = ids[i];
            if (fightOutPokemonIsJoutaiDataId(oldP, id) == 1) {
                fightOutPokemonCopyJoutaiDataId(newP, oldP, id);
            }
        }
    }
    arg.p = newP;
    arg.mode = mode;
    fightFloorLoopValidFightOutPokemon(0, _fightSeqIrekaeInitSub, &arg, 0);
    if (fightOutPokemonIsJoutaiDataId(oldP, 0x34) == 1) {
        fightOutPokemonCopyJoutaiDataId(newP, oldP, 0x34);
    }
    if (fightOutPokemonIsJoutaiDataId(oldP, 0x35) == 1) {
        fightOutPokemonCopyJoutaiDataId(newP, oldP, 0x35);
    }
}
}

static s32 _fightSeqIrekaeInitSub(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    IrekaeArg* a = (IrekaeArg*)userData;
    FightOutPokemon* other = a->p;
    u16 mode = a->mode;
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    if (p == other) {
        return 1;
    }
    if (mode == 0x7F) {
        if (fightOutPokemonIsAlly(other, p) == 0 && _fightSeqCheckFightOutPokemonJoutaiUserFightTargetId(p, other, 0x1D, id) == 1) {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x1D, 0);
        }
    } else {
        _fightSeqInitFightOutPokemonJoutaiUserFightTargetId(p, other, 0x16, id);
        _fightSeqInitFightOutPokemonJoutaiUserFightTargetId(p, other, 0x1D, id);
    }
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId(p, other, 0xA, id);
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId(p, other, 0xE, id);
    if (fightOutPokemonIsAlly(p, other) == 0) {
        fightOutPokemonSetOumuWazaDataId(p, other, 0);
        fightOutPokemonInitFightPokemonEnemyAry(p, other);
    }
    FightTarget* t = fightTargetGetPtr(0xE, other, id);
    if (t != 0) {
        fightOutPokemon_SetOumuWazaAllyDataId(t, 0);
    }
    fightOutPokemon_SetComboFuncId(other, 0);
    fightAi_FixedActIrekaeInit(other);
    return 1;
}

extern "C" {
void fightSeqKizetuInit(FightOutPokemon* p) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqKizetuInitSub, p, 0);
    pokemonInitJoutai(fightOutPokemonGetPokemonPtr(p));
    fightOutPokemonResetSeqStatus(p, 0);
    fightOutPokemonInitJoutaiDataId(p, 0x17);
    fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
    if (fightOutPokemonIsJoutaiDataId(p, 0x3E) == 1) {
        fightOutPokemonInitJoutaiDataId(p, 0x3E);
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0xC8);
    }
    fightOutPokemon_SetComboFuncId(p, 0);
    fightAi_FixedActIrekaeInit(p);
}
}

static s32 _fightSeqKizetuInitSub(void* arg, u16 id, void* userData) {
    FightOutPokemon* p = (FightOutPokemon*)arg;
    FightOutPokemon* other = (FightOutPokemon*)userData;
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    if (p == other) {
        return 1;
    }
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId(p, other, 0x16, id);
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId(p, other, 0xA, id);
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId(p, other, 0xE, id);
    if (fightOutPokemonIsAlly(p, other) == 0) {
        fightOutPokemonSetOumuWazaDataId(p, other, 0);
        fightOutPokemonInitFightPokemonEnemyAry(p, other);
    }
    FightTarget* t = fightTargetGetPtr(0xE, other, id);
    if (t != 0) {
        fightOutPokemon_SetOumuWazaAllyDataId(t, 0);
    }
    return 1;
}

static u8 _fightSeqInitFightOutPokemonJoutaiUserFightTargetId(FightOutPokemon* p, FightOutPokemon* other, u16 joutai, u16 id) {
    u8 r = _fightSeqCheckFightOutPokemonJoutaiUserFightTargetId(p, other, joutai, id);
    if (r == 1) {
        fightOutPokemonInitJoutaiDataId(p, joutai);
    }
    return r;
}

static u8 _fightSeqCheckFightOutPokemonJoutaiUserFightTargetId(FightOutPokemon* p, FightOutPokemon* other, u16 joutai, u16 id) {
    u16 tid;
    if (fightOutPokemonIsJoutaiDataId(p, joutai) == 1 && (tid = fightOutPokemonGetUserFightTargetIdJoutaiDataId(p, joutai)) != 0) {
        FightOutPokemon* target = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(tid, id);
        if (target != 0 && target == other) {
            return 1;
        }
    }
    return 0;
}

extern "C" {
void fightSeqCheckSetHensinBuffToMotoFightPokemon(FightOutPokemon* p, u16 id) {
    if (fightOutPokemonIsUseHensinBuff(p) == 1) {
        fightOutPokemonSetHensinFightPokemonStatusId(p, id, 0);
    }
}
}

extern "C" {
void fightSeqCheckSetHensinBuffToMotoPokemon2(FightOutPokemon* p, u16 a, s32 b, u8 c) {
    if (fightOutPokemonIsUseHensinBuff(p) == 1) {
        fightOutPokemonSetHensinPokemonStatusId(p, a, b, c);
    }
}
}

extern "C" {
void fightSeqCheckSetMotoPokemonToHensinBuff(FightOutPokemon* p, u16 id) {
    if (fightOutPokemonIsUseHensinBuff(p) == 1) {
        fightOutPokemonSetHensinPokemonStatusId(p, id, 0, 1);
    }
}
}

extern "C" {
void fightSeqCheckSetHensinBuffToMotoPokemon(FightOutPokemon* p, u16 id) {
    if (fightOutPokemonIsUseHensinBuff(p) == 1) {
        fightOutPokemonSetHensinPokemonStatusId(p, id, 0, 0);
    }
}
}
