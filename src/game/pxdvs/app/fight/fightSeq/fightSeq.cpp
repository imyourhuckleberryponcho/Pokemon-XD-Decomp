// WIP: 44/67 exact. GENERATED from build/scratch/son-fseq/ pieces by assemble.py
// (edit the pieces or regenerate deliberately). Missing: 4 jump-table functions, damage calcs, data tables.
// WIP: battle sequence helpers (Colosseum shared-function batch).
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
u8 fightOutPokemonGetWazaZokuseiDataId(FightOutPokemon* fop);
void fightOutPokemonInitFightPokemonEnemyAry(FightOutPokemon* fop, FightOutPokemon* target);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonInitJoutaiKeep(FightOutPokemon*);
u8 fightOutPokemonIsAlly(FightOutPokemon* fop, FightOutPokemon* other);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon*);
u8 fightOutPokemonIsHpMantan(FightOutPokemon* fop);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u8 fightOutPokemonIsJoutaiNormal(FightOutPokemon*);
u8 fightOutPokemonIsNokoriHpFollowing(FightOutPokemon* fop, u8 waru);
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
void fightSideSetNowKaisuuJoutaiDataId(FightOutPokemon*, u32);
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
u8 figthOutPokemonGetLevel(FightOutPokemon* fop);
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
void pokemonSetStatus(void*, s32, s32, s32, s8);
void* pokemonTokuseiDataBiosGetName(void*);
void* pokemonTokuseiDataBiosGetPtr(u16);
u16 pokemon_GetHp(Pokemon*);
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
s32 wazaDB_GetIryoku(u16 waza);
void* wazaDB_GetName(u16);
u8 wazaDB_GetOujanosirusi(s32);
u8 wazaDB_GetRangeId(u16);
u16 wazaDB_GetSeqId(u32);
u8 wazaDB_GetZokuseiDataId(u16);
void wazaSequenceSysFreeAllWaza(void);
s32 waza_GetZokuseiKindData(u16);
u8 zokuseiBiosGetWazaKind(u16);
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
extern u8 fight_seq_tuika_param;
extern s32 kureinSequencePtr;
extern Sequence* miyaburiSequencePtr;
extern u8* _wazaSeqAdrs;
extern s32 fight_seq_now_fight_action_ptr;
void fightSeq_CallWazaSeq(void*);
static u8* _fightSeqSoubiItemCheckTurnSubAbiCntUp(FightOutPokemon*, u8, s32, u8, u8, u8);
void fightSeqCheckSetHensinBuffToMotoFightPokemon(FightOutPokemon*, u16);
void fightSeqCheckSetHensinBuffToMotoPokemon(FightOutPokemon*, u16);
void fightSeqCheckZenmetu(void);
u8 fightSeqFightOutPokemonTokuseiCheckTenkiya(void);
void fightSeqSoubiItemCheckTurn(FightOutPokemon*, u32);
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
        u8 cur = pokemonGetStatus(p, 0, fightSeqCondChgActTypeToPokemonStatusId(kind), 0);
        if (fightOutPokemonIsNokoriHpFollowing(p, hpFollow) != 0 && cur < 12) {
            UserWork[0x1601E] = kind + amount;
            seq = WAZA_ItemCondUp;
            UserWork[0x160A4] = type;
            UserWork[0x160A5] = 0;
        }
    }
    return seq;
}

static u8* _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku(FightOutPokemon* p, u16 taste, u8 mode, u16 hp, u16 maxHp, s32 div, FIGHT_WAZA* waza) {
    u8* seq = 0;
    if ((fightOutPokemonIsNokoriHpFollowing(p, 2) != 0 && mode == 0) || (fightOutPokemonIsHpMantan(p) == 0 && mode == 2)) {
        u16 heal;
        fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(tasteDataGetNigateMsgDataId(tasteDataGetPtr(taste))));
        heal = fightOutPokemonMaxHpWaruValue(p, div);
        if ((s32)(hp + heal) > (s32)maxHp) {
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
s32 fightSeqFightOutPokemonTokuseiCheckWazaHitBefore(FightOutPokemon* atk, FightOutPokemon* def) {
    s32 waza;
    s32 result;
    fightOutPokemonGetTokuseiDataId(atk);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    result = 0;
    if ((s32)fightOutPokemonGetTokuseiDataId(def) != 0x2B) {
    } else if (fightOutPokemonCheckFightOut(def) != 0 && wazaDB_GetBouon(waza) == 1) {
        if (fightOutPokemonIsJoutaiDataId(atk, 0x22) == 1) {
            ServerStatusFlag |= 0x800;
        }
        fightSeq_JumpWazaSeq(WAZA_Bouon);
        result = 1;
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
            cur = pokemonGetStatus(p, 0, id, 0);
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
    u8* flag = (u8*)userData;
    u16 tokusei;
    FightOutPokemon* p = (FightOutPokemon*)arg;
    u8* seq;
    tokusei = fightOutPokemonGetTokuseiDataId(p);
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    seq = WAZA_IkakuAct;
    if (*flag == 1) {
        seq = WAZA_Ikaku;
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
            Sequence* trainerSeq = fightTrainer_GetSequencePtr();
            u8 model = 0x41;
            HeroPtr* hero;
            u16 encount;
            WazaSequence* wazaSeq;
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
                if (encount == 0xE0) {
                    fightMenuOpenMsg(0x4FCF);
                } else if (encount == 0x191) {
                    fightMenuOpenMsg(0x5010);
                } else {
                    fightMenuOpenMsg(0x4FCE);
                }
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
s32 fightSeqCheckDarkPokemonJoutaiHyperAct(FightOutPokemon* p, u8 mode) {
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
        fightWaza_SetDamage(waza, count * (s32)fightOutPokemonMaxHpWaruValue(p, 0x10));
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
        damage = ((HSD_Rand() % 3) + damage) - 1;
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
        if ((s8)(now + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0xB)) {
            fightOutPokemonInitJoutaiDataId(p, 0xB);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0xB, now + 1);
        }
        if (fightOutPokemonCheckNoAttackFlag(p) != 1 && fightOutPokemonIsJoutaiDataId(p, 0xB) == 1) {
            fightOutPokemonWriteJoutaiDataId(p, 0x22, 0);
            ServerWork[5] = 0;
        } else {
            fightOutPokemonInitJoutaiKeep(p);
            ServerWork[5] = 1;
        }
        fightSeq_CallWazaSeq(WAZA_Sawagu);
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0xD) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0xD);
        if ((s8)(now + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0xD)) {
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
        u16 slot = fightOutPokemonGetBuffJoutaiDataId(p, 0x2A);
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
        if ((s8)(now + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0x1D)) {
            fightOutPokemonInitJoutaiDataId(p, 0x1D);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x1D, now + 1);
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x24) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x24);
        if ((s8)(now + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0x24)) {
            fightOutPokemonInitJoutaiDataId(p, 0x24);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x24, now + 1);
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x30) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x30);
        if ((s8)(now + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0x30)) {
            fightOutPokemonInitJoutaiDataId(p, 0x30);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(p, 0x30, now + 1);
        }
    }
    SIDE_END
    SIDE_BEGIN
    if (fightOutPokemonIsJoutaiDataId(p, 0x26) == 1) {
        s8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(p, 0x26);
        if ((s8)(now + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(p, 0x26)) {
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

extern "C" {
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
