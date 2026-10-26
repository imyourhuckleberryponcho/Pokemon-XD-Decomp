#include <dolphin/types.h>
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

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct FIGHT_FLOOR;
struct FIGHT_SIDE;
struct FIGHT_TRAINER;
struct FightAction;
struct FightActionData;
struct FightEncountData;
struct FightOutPokemon;
struct FightPokemon;
struct FightSide;
struct FightTrainer;
struct GSchar;
struct Hero;
struct NullSequence;
struct Pokemon;
struct Sequence;
struct WazaSequence;

#pragma pool_strings off

struct FightActionData {
    u16 kind;
    u8 unk2[2];
    u32 buff;
};
struct FightActionDispBuff {
    u32 buff[4];
};
struct FightAction {
    u16 kind;
    u32 buff;
    FightActionData* fightActionData;
    void* buffDataPtr;
    u32 buffDataId;
    void* actorFightTarget;
    FightActionData* motoFightActionData;
    u32 fifoBanme;
    FightActionDispBuff disp;
    FightAction() {}
};
struct FIGHT_FLOOR;
struct FIGHT_SIDE;
struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightWaza;
struct FightItem;
struct FightPokemon;
struct WazaSequence;
struct Sequence;
struct FightEncountData;
enum darkPokemonStatus {
    darkPokemonStatus0,
    darkPokemonStatus1,
    darkPokemonStatus2,
    darkPokemonStatus3
};
class DarkPokemon {
public:
    s32 getStatus() const;
    u16 getCatchFloorId() const;
    u16 getDarkPokemonID() const;
    void setStatus(darkPokemonStatus);
    void setEscapeTime(u32);
    void setSnatchTime(u32);
    void setOrgTrainer(u16);
    void setTrainerName(const u16*);
    void setCatchBallID(u16);
    void setCatchFloorId(u16);
};
class DeckDarkPokemon {
public:
    static DeckDarkPokemon* getDeckDarkPokemonObj(u32);
    u8 getWorth() const;
    u8 getUnderTakerFlag() const;
};
struct Pokemon {
    DarkPokemon* getDarkPokemon();
    u16 getDarkpokemonDataID() const;
public:
    void setCondition(unsigned char);
};
struct Hero {
    static Hero* getHeroPtr();
    u32 getFootStep() const;
};
struct POKEMON_EVOLUTION_INFO {
    u8 kind;
    u8 reserved;
    u16 parameter;
};

extern "C" {
extern FightActionData fight_action_data_kaisi[];
extern u8 WAZA_FieldWeather[];
}

extern WazaSequence* fightEnemyTrainerWazaSeqHdl;
extern "C" {
u16 _fight_kaisi_pre_trainer_intr_wzx_data_id_ary[5] = { 0x90, 0x91, 0x92, 0x93, 0x94 };
u8 _fight_kaisi_pre_trainer_intr_wzx_data_id_num = 5;
u8 wildPokemonDownFlag;
}
static void* _gSoundThread;
extern "C" {
u8 introBossFlag;
WazaSequence* fightEnemyTrainerWazaSeqHdl;
u8 WildPokemonCatchFlag;
u16 _fight_kaisi_pre_trainer_intr_wzx_data_id;
}

typedef u8 (*FightFloorLoopFunc)(void*, u16, void*);

extern "C" {
void* fightActionBiosGetActorFightTargetPtr(FightAction*);
void* fightActionBiosGetBuffDataPtr(FightAction*);
s32 fightActionBiosGetBuffDataId(FightAction*);
u8 fightActionCheckValid(FightAction*);
u16 fightActionGetKindDataId(FightAction*);
void fightActionFlowFifo(FightAction*);
void fightSeqExec(FightAction*, void*, u8);
void fightSeqWazaExec(FightAction*, u16);
void fightSeqItemExec(FightAction*, u16);
void fightSeqCallExec(FightAction*);
void fightSeqIrekaeExec(FightAction*);
void fightSeqPre(FightAction*);
void fightSeqPost(FightAction*);
void fightSeqSpecificationActionCounterInit(FightOutPokemon*);
s32 fightSeqCheckDarkPokemonJoutaiHyperAct(FightOutPokemon*, u8);
FightOutPokemon* fightSeqSelectDefensePokemonPtr(FightOutPokemon*, u16, u8, u32, u32, u32, s32);
void fightMainWaitFrame(u32);
u16 fightGetFightResultId(void);
u8 dbgMenuFightGetAllFightTrainerOperateFlag(void);

void fightFloor_SetAttackPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloor_SetDefensePokemonPtr(FIGHT_FLOOR*, void*);
void fightFloor_SetEscapePokemonPtr(FIGHT_FLOOR*, void*);
void fightFloor_SetIrekaePokemonPtr(FIGHT_FLOOR*, void*);
void fightFloor_SetAppointMsgPtr(FIGHT_FLOOR*, u32);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(FIGHT_FLOOR*, void*);
s32 fightFloor_GetFightType(FIGHT_FLOOR*);
s32 fightFloor_GetFightTypeTrainerNum(FIGHT_FLOOR*);
u32 fightFloor_GetEnvSndId(FIGHT_FLOOR*);
FightOutPokemon* fightFloor_GetFightOutPokemonPtrAry(FIGHT_FLOOR*, u32);
u32 fightFloorGetNowTenkouDataId(FIGHT_FLOOR*, u8);
u8 fightFloorLoopValidFightOutPokemon(FIGHT_FLOOR*, FightFloorLoopFunc, void*, u8);
void fightFloorLoopValidFightTrainer(FIGHT_FLOOR*, FightFloorLoopFunc, void*, u8);
void fightFloorCreateFightOutPokemonPtrAry(FIGHT_FLOOR*);
void fightFloorSortFightOutPokemonPtrAry(FIGHT_FLOOR*, u8);
void fightFloorInitFightTarget(FIGHT_FLOOR*);
u8 fightFloorSetFightResultId(FIGHT_FLOOR*, u16);
void fightFloorSetTuusinErrorFightResult(FIGHT_FLOOR*);
FIGHT_SIDE* fightFloorGetValidFightSidePtr(FIGHT_FLOOR*, u32);
FIGHT_TRAINER* fightSideGetValidFightTrainerPtr(FIGHT_SIDE*, u32);
u8 fightMenuFightTrainerGcHeroOpenMenu(FIGHT_TRAINER*, u16, u8);
u8 fightTrainerSelectFightAction(FIGHT_TRAINER*, u16);

void fightSeqInit(void);
void fightSeqFightActionCreateAndFlowFifo(void*, FightOutPokemon*, u8, u8, void*, void*);
void fightSeqFightOutPokemonTokuseiCheckIkaku(u8);
void fightSeqFightOutPokemonTokuseiCheckTrace(void);
void fightSeqFightOutPokemonTokuseiCheckAppear(FightOutPokemon*);
void fightSeqFightOutPokemonDarkCheckAppear(FightOutPokemon*, u8);
u8 fightSeqPokemonSoubiItemCheckAppear(FightOutPokemon*);
FightActionData* fightActionBiosGetFightActionDataPtr(FightAction*);
void fightFloorSetMeetEnemyFightPokemonEnemySideAll(FIGHT_FLOOR*);
void fightFloorRegistFightTrainerEnemyPokemonFightSideAll(FIGHT_FLOOR*);
void fightFloorCreateFightPokemonEnemyAryEnemySideAll(FIGHT_FLOOR*);
void fightFloor_SetFisstAttackRnd(FIGHT_FLOOR*, u16);
u32 HSD_Rand(void);
void wazaSequenceSysFreeAllWaza(void);
u32 heroGetStatus(Hero*, u32, u16);
void heroCheckSetMonohiroiAllTemotiPokemon(Hero*);
void heroBiosCopy(Hero*, Hero*);
u8 heroBiosGetMeetDarkPokemonCount(Hero*);
void heroBiosSetMeetDarkPokemonCount(Hero*, u8);
Hero* savedataGetStatus(void*, s32);
Hero* menuCBBios_GetHeroImmediately(u8);
u8 menuCBBios_CurrentlyWorkingToolBattle(void);
Hero* fightGetMenuCtrlHero(void);
Hero* fightTrainer_GetHeroPtr(FIGHT_TRAINER*);
FIGHT_TRAINER* fightFloorGetGcHeroFightTrainerPtr(FIGHT_FLOOR*);
u8 fightFloorIsGcHeroWin(FIGHT_FLOOR*, u16);
void fightTrainerBackFightPokemonToTemotiPokemon(FIGHT_TRAINER*, u8);
u8 fightTrainerCheckCanGetExp(FIGHT_TRAINER*);
u8 fightTrainerIsGcHero(FIGHT_TRAINER*);
FightPokemon* fightTrainerCheckTemotiPokemonFightEntry(FIGHT_TRAINER*, Pokemon*);
bool fightPokemonCheckFightOut(FightPokemon*);
u8 fightPokemon_GetLevelUpFlag(FightPokemon*);
bool pokemonCheckFightOut(Pokemon*);
u8 pokemonIsDarkPokemon(Pokemon*);
u16 pokemonEvolutionCheck(Pokemon*, s32, u16, u16*, POKEMON_EVOLUTION_INFO*);
s32 pokemonEvolutionAll(Pokemon*, u16, u16, POKEMON_EVOLUTION_INFO*, Hero*, s32, s32, s32);
void fightMainWaitFrameEffect(u32);
u8 fightFloor_GetFightKindGetExpFlag(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindMonohiroiFlag(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindGetInfectPokerusFlag(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindBackSaveDataFlag(FIGHT_FLOOR*);
s32 fightFloor_GetFightKind(FIGHT_FLOOR*);
void WazaSequence_Free(WazaSequence*);
FightEncountData* fightEncountDataBiosGetPtr(u16);
u16 fightEncountDataBiosGetDiskId(FightEncountData*);
u8 fightEncountDataBiosGetFightKind(FightEncountData*);
u16 fightGetFightEncountDataId(void);
void* fightTargetGetPtrAsNowFightType(u16, void*);
void fightMainAllCamera(u32, u32);
u32 battleCameraIsSimple(void);
void battleCameraStop(void);
void Sequence_Talk(Sequence*);
void* Sequence_LoadWaza(Sequence*, u16, u8, s32);
WazaSequence* Sequence_GetWaza(Sequence*, u16, u32);
void WazaSequence_Start(WazaSequence*, s32);
u8 wazaSequenceSysLastWazaIsImpactPoint(u32);
void soundOpenPlayME(void);
void* GSthreadCreate(s32, s32, s32, s32, s32, void (*)(void));
void GSthreadSetArgs(void*, s32, ...);
void GSthreadSetName(void*, const char*);
u8 GSthreadIsRunning(void*);
void GSthreadSwitch(void);
u8 GSsndPlayVolume(u32, s32, u8, u32);
void GSflagSet(u32, u32);
u16* GSmsgGetGSchar(u32);
u32 floorGetCurrentGroupID(void);
u8 menuCBBios_CurrentlyWorkingToolBattle(void);
u32 fightFloor_GetEncountDataId(FIGHT_FLOOR*);
u32 fightFloor_GetEncountFloorId(FIGHT_FLOOR*);
u8 fightFloor_GetTrainer(FIGHT_FLOOR*);
u16 fightFloor_GetTurnCount(FIGHT_FLOOR*);
u8 fightFloor_GetStockPokemonNum(FIGHT_FLOOR*);
Pokemon* fightFloor_GetStockPokemonPtr(FIGHT_FLOOR*, u8);
u8 fightFloor_GetStockPokemonBallID(FIGHT_FLOOR*, u8);
void fightFloor_SetStockPokemonNum(FIGHT_FLOOR*, u8);
u8 fightFloor_GetFightKindGetOkaneFlag(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindGetNekoniKobanFlag(FIGHT_FLOOR*);
u8 fightFloorIsNowEncountVirtualBattle(FIGHT_FLOOR*);
u8 fightFloorIsNowEncountOpeningVirtualBattle(FIGHT_FLOOR*);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(FIGHT_FLOOR*, FIGHT_TRAINER*, FightPokemon**, u8, u8);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
u8 fightKind_CheckFightKind(u8);
void heroMovePoolCounter(s32, u32);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
void* fightTrainer_GetFightPokemonPtr(FIGHT_TRAINER*, u16);
Sequence* fightTrainer_GetSequencePtr(FIGHT_TRAINER*);
u8 fightTrainer_GetNigeruCount(FIGHT_TRAINER*);
u16* fightTrainerGetPrefixNamePtr(FIGHT_TRAINER*);
u32 fightTrainerGetNamePtr(FIGHT_TRAINER*);
u16 fightTrainerDB_GetPkxDataId(u16);
u16 fightTrainerDB_GetName(u16);
u32 fightTrainerDB_GetSerihuMsgId(u16, u8);
u32 fightActionDataBiosGetBuff(FightActionData*);
void fightMsgctrlSetValue(s32, u32);
u32 fightMenuOpenMsg(u32);
u32 fightMenuOpenTrainerMsg(u32);
void fightMenuCloseMsg(void);
void fightCloseAllMenu(void);
char* pokemon_GetNicknamePtr(Pokemon*);
u32 darkpokemonBiosGetScenarioNum(void);
s32 darkPokemonGetSnatchSuccessNum(void);
extern u8 WAZA_OkodukaiCheck[];
extern u8 WAZA_KobanCheck[];
void menuGetKeyInfo(void*, u32);
s8 fadeCheck(s32);
u32 GSflagGet(u32);
u32 fightFloorGetStatus(FIGHT_FLOOR*, u16, u16, u16);
void fightFloorCreate(FIGHT_FLOOR*, u16);
void fightFloorInitFightStart(FIGHT_FLOOR*);
u16 fightEncountDataBiosGetFightFloorDataId(FightEncountData*);
u16 fightFloorDB_GetFightSideDataId(u16, u8);
void fightSideCreate(FIGHT_SIDE*, u16);
void* fightTargetGetPtr(u16, void*, u16);
u16 fightFloor_GetFightFloorDataId(FIGHT_FLOOR*);
u32 fightFloor_GetSyoukaiWzxDataId(FIGHT_FLOOR*);
u32 fightEncountDataBiosGetSyoukaiWzxDataId(FightEncountData*);
u16 fightTrainerDB_GetSyoukaiWzxDataId(u16);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FIGHT_TRAINER*, u16);
u8 fightFloorIsNowEncountHostEnemyPokemonKime(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindHostEnemyMsgFlag(FIGHT_FLOOR*);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon*);
u8 fightFloorIsNowEncountTuusinTaisen(FIGHT_FLOOR*);
u8 fightKoukaDoFightKoukaJoukenAndKouka(void*, u16);
u32 tenkouDataBiosGetFightInitMsgId(u16);
void* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u16, u16);
bool fightTargetIsHostSide(void*, u16);

FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
FightItem* fightOutPokemon_GetFightItemPtr(FightOutPokemon*);
FightAction* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon*);
void* fightOutPokemon_GetSequencePtr(FightOutPokemon*);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon*);
u8 fightOutPokemon_GetFightActionFlag(FightOutPokemon*);
void fightOutPokemon_SetFightActionFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetIrekaeTargetEntryId(FightOutPokemon*, s16);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
bool fightWazaCheckValid(FightWaza*);
void fightWazaSetUseWazaStatus(FightWaza*, u16);
void fightWaza_SetMotoWazaDataId(FightWaza*, u16);
u16 fightWaza_GetTargetDataId(FightWaza*);
u8 fightWaza_GetWazaBanme(FightWaza*);
u8 fightWaza_GetAutoMakeFlag(FightWaza*);
u16 fightItem_GetItemDataId(FightItem*);
u16 fightItem_GetTargetDataId(FightItem*);
u8 itemDB_GetKind(u16);
u16 pokemon_GetPokemonWazaDataId(Pokemon*, u32);
void soundOpenPlayFadeOutIn(s32, s32, s32, s32);
}

void deckDataVirtualDB_SetFlagData(u16, bool);
u32 deckDataVirtualDB_GetFlag(u16);
u8 deckDataVirtualDB_GetTurnLimit(u16);
u8 fightSeqItemSeq_AddPoke(Pokemon*, u8, FIGHT_TRAINER*, Hero*);
void _darkPokemonSetUnderTaker(DeckDarkPokemon*, Pokemon*, u16);

static u8 _fightActionFlowTenkouInitSubGetSeqFightOutPokemonPtr(void*, u16, void*);
static u32 _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(FIGHT_FLOOR*, u8);
static u8 _fightActionFlowFightTrainerSelectFightAction(void*, u16, void*);
static bool _fightActionFlowKaisiPreSubCheckVirtualDiskCancel(u16);
static bool _fightActionFlowKaisiPreSubCheckCancel(bool*);
static u8 _fightActionFlowKaisiPostSubFightOutPokemonSoubiItemCheckAppear(void*, u16, void*);
static u8 _fightActionFlowKaisiPostSubFightOutPokemonTokuseiCheckAppear(void*, u16, void*);
static u8 _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear(void*, u16, void*);

extern "C" {

struct FightSide {
    u8 _draft[1];
};
struct FightTrainer {
    u8 _draft[1];
};
struct GSchar {
    u8 _draft[1];
};
struct NullSequence {
    u8 _draft[1];
};

extern "C" {
s32 GSmsgGetLength(u16);
s32 Sequence_SetVisibility(u32, s32);
bool WazaSequence_IsActive(WazaSequence* sequence);
s32 WazaSequence_Stop();
s32 battleCameraStartRandom(s32);
void battleGridAddPokemon(NullSequence* slotSeq, NullSequence* pokemonSeq);
void battleGridAddTrainer(NullSequence* seq, u8 arg1, u8 arg2);
void battleGridStoreModelVisibilityFlags(void);
void battleGridUpdate(void);
void darkPokemonBiosSetFightFlag(u16 id);
void fadeSet(s32 type, f32 time);
s32 fightActionFlowKaisiNyuujouPokemon(FightAction* action);
s32 fightActionFlowKaisiNyuujouTrainer(FightAction* action);
s32 fightActionFlowKaisiPre();
u16 fightEncountDataBiosGetFightTrainerDataId(FightEncountData* data, u8 index);
u32 fightEncountDataBiosGetGSInputDevice(FightEncountData* data, u8 index);
s16 fightFloorGetFightPokemonEntryCntInc(FIGHT_FLOOR* floor);
FightOutPokemon* fightFloor_GetAttackPokemonPtr(FIGHT_FLOOR* floor);
u32 fightFloor_GetBgmSndId(FIGHT_FLOOR* floor);
u8 fightFloor_GetFightKindBossFlag(FIGHT_FLOOR* floor);
u8 fightFloor_GetFightKindDoZukanMitaFlag(FIGHT_FLOOR* floor);
u8 fightFloor_GetFightKindGetFriendFlag(FIGHT_FLOOR* floor);
u8 fightFloor_GetFightTypeEntryPokemonNum(FIGHT_FLOOR* floor);
u8 fightFloor_GetFightTypeFightoutPokemonNum(FIGHT_FLOOR* floor);
s32 fightMainSetAllDispFlag(s32);
void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon* p, u16 id, bool flag);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(u8 menuId, FightOutPokemon* p, u16 id, s32 wait, bool flag);
void fightMenuFightOutPokemonOpenStatusMenuStart(FightOutPokemon* p, u16 id, bool flag);
void fightOutPokemonCreate(FightOutPokemon* fop, FightPokemon* fp, Sequence* seq);
void fightOutPokemonDasuEffect(FightTrainer* trainer, FightOutPokemon* fop, u8 mode);
GSchar* fightOutPokemonGetNamePtr(FightOutPokemon* fop);
u32 fightOutPokemonGetVoiceSndId(FightOutPokemon* fop);
void fightOutPokemonRegWzxLoad(FightOutPokemon* fop);
void fightOutPokemonSetOnZukanFlag(FightOutPokemon* fop, u8 flag);
u16 fightOutPokemon_GetKanseiSndId(FightOutPokemon* fightOutPokemon);
void fightPokemonCreate(FightTrainer* trainer, FightPokemon* fp, Pokemon* p, s16 entry);
void fightPokemonGetFriendFormPokemonFriendFilterId(FightPokemon* fp, void* out);
void fightSeqVanishOff(FightOutPokemon* p);
bool fightSideCheckValid(FIGHT_SIDE* side);
u32 fightSideGetDoFightTrainerCount(FIGHT_SIDE* side);
void fightSideGetFightTrainerGridParam(FIGHT_SIDE* side, u16 mode, u16 pos, u8* outA, s8* outB);
u16 fightSide_GetFightSideDataId(FightSide* side);
FightTrainer* fightSide_GetFightTrainerPtr(FightSide* side, u16 index);
void fightTrainerBallThrowEffect(FightTrainer* trainer, FightOutPokemon* fo, u8 mode);
u8 fightTrainerCheckTrainerDataIdValid(u16 id, s32 allowNoAi);
bool fightTrainerCheckValid(FightTrainer* trainer);
void fightTrainerCreate(FightTrainer* trainer, Hero* src, u16 id, u32 controllerId, u32 seq);
void fightTrainerCreateFightTrainerDataIdToHero(u16 id, s32 allowNoAi, Hero* hero, u16 encountId);
u32 fightTrainerCreateSequence(u16 id);
u8 fightTrainerDB_GetKindDataId(u16 id);
int fightTrainerGetDoFightOutFightOutPokemonCount(FightTrainer* trainer);
void fightTrainerSortFightTrainerDataIdToHeroTemotiPokemon(FightTrainer* trainer, u16 num, u32 mode);
void* fightTrainer_GetFightoutPokemonPtr(u8* t, u16 i);
s32 menuFaceLoadFightPokemon(s32, s32, s32);
bool pokemonCheckValid(Pokemon* pokemon);
u32 pokemonCreateSequence(FightPokemon* fightPokemon);
u16 pokemon_GetDarkpokemonDataId(Pokemon* poke);
void soundOpenPlay(s32, s32, s32);
}
extern "C++" {
static void _fightActionFlowKaisiNyuujouPokemonSubAppearMsg(FIGHT_TRAINER* trainer, FightOutPokemon* fop, u16 trainerCount, u16 fightOutCount, u16 unused, u16 index, u8 mode);
u8 deckDataVirtualDB_GetAllyJoutai(u16 id, u8 index);
u8 deckDataVirtualDB_GetEnemyJoutai(u16 id, u8 index);
}

u32 fightActionFlowWazaKiaipantiPre(FightAction* action) {
    fightFloor_SetAttackPokemonPtr(0, fightActionBiosGetActorFightTargetPtr(action));
    fightSeqExec(action, fightActionBiosGetBuffDataPtr(action), 0);
    return 1;
}

u32 fightActionFlowTenkouInit(FightAction* action) {
    fightKoukaDoFightKoukaJoukenAndKouka(0, 1);
    u8 id = fightFloorGetNowTenkouDataId(0, 0);
    void* pokemon = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowTenkouInitSubGetSeqFightOutPokemonPtr, &pokemon, 0);
    if (id != 0) {
        fightFloor_SetAttackPokemonPtr(0, pokemon);
        u32 msg = tenkouDataBiosGetFightInitMsgId(id);
        fightFloor_SetAppointMsgPtr(0, msg);
        fightSeqExec(action, fightActionBiosGetBuffDataPtr(action), 0);
    }
    return 1;
}

}

static u8 _fightActionFlowTenkouInitSubGetSeqFightOutPokemonPtr(void* fop, u16 index, void* out) {
    if (fightOutPokemon_GetSequencePtr((FightOutPokemon*)fop) != 0) {
        if (out != 0) {
            *(void**)out = fop;
        }
        return 0;
    }
    return 1;
}

extern "C" {

u32 fightActionFlowHeijou(FightAction* action) {
    return 1;
}

u32 fightActionFlowSyuuryouPost(FightAction* action) {
    u16 evoItem;
    POKEMON_EVOLUTION_INFO info;
    FIGHT_TRAINER* trainer;
    Hero* hero;
    u32 trainerNum;
    u16 evo;
    FightPokemon* fightPokemon;
    Pokemon* pokemon;
    u16 j;
    Hero* save;
    trainerNum = (u8)fightFloor_GetFightTypeTrainerNum(0);
    if (fightGetFightResultId() == 1) {
        return 1;
    }
    trainer = fightFloorGetGcHeroFightTrainerPtr(0);
    if (trainer != 0 && (hero = fightTrainer_GetHeroPtr(trainer)) != 0) {
        fightTrainerBackFightPokemonToTemotiPokemon(trainer, 0);
        if (fightFloorIsGcHeroWin(0, fightGetFightResultId()) == 1) {
            if (fightFloor_GetFightKindGetExpFlag(0) == 1 && fightTrainerCheckCanGetExp(trainer) == 1) {
                for (j = 0; j < 6; j++) {
                    pokemon = (Pokemon*)heroGetStatus(hero, 3, j);
                    if (!pokemonCheckFightOut(pokemon)) {
                        continue;
                    }
                    if (pokemonIsDarkPokemon(pokemon) == 1) {
                        continue;
                    }
                    fightPokemon = fightTrainerCheckTemotiPokemonFightEntry(trainer, pokemon);
                    if (fightPokemon == 0) {
                        continue;
                    }
                    if (!fightPokemonCheckFightOut(fightPokemon)) {
                        continue;
                    }
                    if (!fightPokemon_GetLevelUpFlag(fightPokemon)) {
                        continue;
                    }
                    evo = pokemonEvolutionCheck(pokemon, 0, 0, &evoItem, &info);
                    if (evo == 0) {
                        continue;
                    }
                    pokemonEvolutionAll(pokemon, evo, evoItem, &info, hero, 1, 1, 0);
                    fightMainWaitFrameEffect(10);
                }
            }
            if (fightFloor_GetFightKindMonohiroiFlag(0) == 1) {
                heroCheckSetMonohiroiAllTemotiPokemon(hero);
            }
            fightFloor_GetFightKindGetInfectPokerusFlag(0);
        }
        if (fightFloor_GetFightKindBackSaveDataFlag(0) == 1) {
            save = savedataGetStatus(0, 2);
            if (save != 0) {
                u8 count = heroBiosGetMeetDarkPokemonCount(save);
                heroBiosCopy(save, hero);
                heroBiosSetMeetDarkPokemonCount(save, count);
            }
        }
    }
    if (menuCBBios_CurrentlyWorkingToolBattle() == 1) {
        FIGHT_TRAINER* t;
        Hero* src;
        u32 k;
        s32 base;
        u32 i;
        FIGHT_SIDE* side;
        for (i = 0; (u16)i < 2; i++) {
            side = fightFloorGetValidFightSidePtr(0, i);
            if (side == 0) {
                continue;
            }
            base = (u16)i * trainerNum;
            for (k = 0; (u16)k < trainerNum; k++) {
                t = fightSideGetValidFightTrainerPtr(side, k);
                if (t == 0) {
                    continue;
                }
                fightTrainerBackFightPokemonToTemotiPokemon(t, 0);
                src = menuCBBios_GetHeroImmediately(k + base);
                if (src == 0) {
                    continue;
                }
                Hero* hero2 = fightTrainer_GetHeroPtr(t);
                if (hero2 == 0) {
                    continue;
                }
                heroBiosCopy(src, hero2);
            }
        }
    }
    if ((u8)fightFloor_GetFightKind(0) == 6 || (u8)fightFloor_GetFightKind(0) == 7) {
        FIGHT_SIDE* side;
        Hero* dst;
        FIGHT_TRAINER* t;
        u32 k;
        Hero* src;
        u32 i;
        for (i = 0; (u16)i < 2; i++) {
            side = fightFloorGetValidFightSidePtr(0, i);
            if (side == 0) {
                continue;
            }
            for (k = 0; (u16)k < trainerNum; k++) {
                t = fightSideGetValidFightTrainerPtr(side, k);
                if (t == 0) {
                    continue;
                }
                if ((u8)fightFloor_GetFightKind(0) == 6 || (u8)fightFloor_GetFightKind(0) == 7) {
                    if (!fightTrainerIsGcHero(t)) {
                        continue;
                    }
                }
                fightTrainerBackFightPokemonToTemotiPokemon(t, 0);
                dst = fightGetMenuCtrlHero();
                if (dst == 0) {
                    continue;
                }
                src = fightTrainer_GetHeroPtr(t);
                if (src == 0) {
                    continue;
                }
                heroBiosCopy(dst, src);
            }
        }
    }
    if (fightEnemyTrainerWazaSeqHdl != 0) {
        WazaSequence_Free(fightEnemyTrainerWazaSeqHdl);
    }
    return 1;
}

}

extern "C" {

u32 fightActionFlowSyuuryou(FightAction* action) {
    FightEncountData* encount;
    u16 diskId;
    u16 wazaId;
    FIGHT_TRAINER* hostTrainer;
    FIGHT_TRAINER* trainer;
    u16 trainerId;
    u16 pkxId;
    u16 name;
    Sequence* seq;
    u16 kind;
    u16 msgA;
    u16 msgB;
    u32 openMsg;
    u32 camera;
    WazaSequence* waza;
    u32 wazaFlag;
    FightPokemon* ary[24];
    wazaFlag = 0;
    encount = fightEncountDataBiosGetPtr(fightGetFightEncountDataId());
    diskId = fightEncountDataBiosGetDiskId(encount);
    kind = fightActionDataBiosGetBuff(fightActionBiosGetFightActionDataPtr(action));
    hostTrainer = (FIGHT_TRAINER*)fightTargetGetPtrAsNowFightType(0xb, 0);
    trainer = (FIGHT_TRAINER*)fightTargetGetPtrAsNowFightType(9, hostTrainer);
    trainerId = fightTrainer_GetFightTrainerDataId(trainer);
    pkxId = fightTrainerDB_GetPkxDataId(trainerId);
    name = fightTrainerDB_GetName(trainerId);
    fightTrainer_GetFightPokemonPtr(trainer, 0);
    seq = fightTrainer_GetSequencePtr(trainer);
    if (pkxId == 0x2a) {
        wazaId = 0x13d;
    } else {
        wazaId = 0x5a;
    }
    msgA = fightTrainerDB_GetSerihuMsgId(trainerId, 1);
    if (fightTrainer_GetNigeruCount(trainer) == 0) {
        msgB = fightTrainerDB_GetSerihuMsgId(trainerId, 2);
    } else {
        msgB = fightTrainerDB_GetSerihuMsgId(trainerId, 3);
        if (msgB == 0) {
            msgB = fightTrainerDB_GetSerihuMsgId(trainerId, 2);
        }
    }
    switch ((u16)fightFloor_GetEncountDataId(0)) {
    case 0xd9:
        openMsg = 0x5006;
        break;
    case 0x15e:
        openMsg = 0x5007;
        break;
    default:
        openMsg = 0x4f4c;
        break;
    }
    fightMsgctrlSetValue(0x22, (u32)fightTrainerGetPrefixNamePtr(trainer));
    fightMsgctrlSetValue(0x23, fightTrainerGetNamePtr(trainer));
    fightMsgctrlSetValue(0x13, fightTrainerGetNamePtr(hostTrainer));
    fightMsgctrlSetValue(0x25, fightTrainerGetNamePtr(trainer));
    if (!menuCBBios_CurrentlyWorkingToolBattle() || fightKind_CheckFightKind(0x11)) {
        if (kind == 2) {
            if (!fightFloor_GetTrainer(0)) {
                fightMainAllCamera(battleCameraIsSimple(), 0);
                fightMenuCloseMsg();
            } else {
                Sequence_LoadWaza(seq, wazaId, 4, 0);
                camera = battleCameraIsSimple();
                fightMsgctrlSetValue(0x5d, 0);
                _gSoundThread = GSthreadCreate(0x15, floorGetCurrentGroupID(), 0x2000, 1, 1, soundOpenPlayME);
                if (_gSoundThread) {
                    GSthreadSetArgs(_gSoundThread, 3, 0x36a, 0, 0xff);
                    GSthreadSetName(_gSoundThread, "fightME");
                }
                if (fightFloor_GetEnvSndId(0)) {
                    GSsndPlayVolume(0x549, 0, 0xff, 0);
                }
                fightMainWaitFrame(0x32);
                fightMenuOpenMsg(openMsg);
                fightMenuCloseMsg();
                if (_gSoundThread) {
                    while (GSthreadIsRunning(_gSoundThread)) {
                        GSthreadSwitch();
                    }
                }
                waza = Sequence_GetWaza(seq, wazaId, 4);
                wazaFlag = 1;
                WazaSequence_Start(waza, 1);
                Sequence_Talk(seq);
                fightMenuOpenTrainerMsg(msgB);
                fightMainWaitFrame(0);
                fightMenuCloseMsg();
                while (1) {
                    if (wazaSequenceSysLastWazaIsImpactPoint(2) == 1) {
                        break;
                    }
                    GSthreadSwitch();
                }
                battleCameraStop();
                fightMainAllCamera((u16)camera, 0);
            }
            if (fightFloorIsNowEncountVirtualBattle(0) == 1 || fightFloorIsNowEncountOpeningVirtualBattle(0) == 1) {
                if (deckDataVirtualDB_GetTurnLimit(diskId)) {
                    int limit = deckDataVirtualDB_GetTurnLimit(diskId);
                    if (fightFloor_GetTurnCount(0) > limit) {
                        fightFloorSetFightResultId(0, 3);
                    }
                }
            }
        } else if (kind == 3) {
            waza = 0;
            if (fightFloor_GetTrainer(0)) {
                waza = (WazaSequence*)Sequence_LoadWaza(seq, 0x59, 4, 0);
                wazaFlag = 1;
                camera = battleCameraIsSimple();
            }
            if (fightFloor_GetEnvSndId(0)) {
                GSsndPlayVolume(0x54a, 0, 0xff, 0);
            }
            fightMenuOpenMsg(0x4e38);
            fightMenuCloseMsg();
            if (fightFloor_GetTrainer(0)) {
                WazaSequence_Start(waza, 1);
                Sequence_Talk(seq);
                fightMenuOpenTrainerMsg(msgA);
                fightMainWaitFrame(0);
                fightMenuCloseMsg();
                while (1) {
                    if (wazaSequenceSysLastWazaIsImpactPoint(2) == 1) {
                        break;
                    }
                    GSthreadSwitch();
                }
                battleCameraStop();
                fightMainAllCamera(camera, 0);
            }
            fightMenuOpenMsg(0x4e39);
            fightMenuCloseMsg();
        } else if ((u16)(kind - 4) > 1 && (kind == 7 || kind == 6)) {
            if (fightFloor_GetEnvSndId(0)) {
                GSsndPlayVolume(0x54b, 0, 0xff, 0);
            }
            fightMenuOpenMsg(0x4f26);
            fightMainWaitFrame(0x40);
            fightMenuCloseMsg();
        }
    }
    if (fightFloorIsGcHeroWin(0, fightGetFightResultId()) == 1) {
        u8 turn = fightFloor_GetTurnCount(0);
        if (turn > 8) {
            turn = 8;
        }
        heroMovePoolCounter(1, turn * 30);
        if (fightFloor_GetFightKindGetOkaneFlag(0) == 1) {
            fightSeqExec(action, WAZA_OkodukaiCheck, 0);
        }
        if (fightFloor_GetFightKindGetNekoniKobanFlag(0) == 1) {
            if (fightEncountDataBiosGetFightKind(encount) != 0xc || WildPokemonCatchFlag != 1) {
                fightSeqExec(action, WAZA_KobanCheck, 0);
            }
        }
        if (fightFloorIsNowEncountVirtualBattle(0) == 1) {
            deckDataVirtualDB_SetFlagData(diskId, 1);
        }
        u8 remain = fightFloor_GetStockPokemonNum(0);
        u8 i;
        u32 count;
        for (i = 0, count = remain; i < count; i++) {
            Pokemon* pokemon = fightFloor_GetStockPokemonPtr(0, i);
            if (pokemon == 0) {
                continue;
            }
            DarkPokemon* dark = pokemon->getDarkPokemon();
            u8 ball = fightFloor_GetStockPokemonBallID(0, i);
            dark->setStatus(darkPokemonStatus3);
            dark->setSnatchTime(Hero::getHeroPtr()->getFootStep());
            dark->setOrgTrainer(trainerId);
            dark->setTrainerName(GSmsgGetGSchar(name));
            dark->setCatchBallID(ball);
            u16 catchFloor = dark->getCatchFloorId();
            if (catchFloor == 0xb5 || catchFloor == 0) {
                dark->setCatchFloorId(fightFloor_GetEncountFloorId(0));
            }
            u32 msg = 0x5002;
            msg = fightSeqItemSeq_AddPoke(pokemon, ball, trainer, fightTrainer_GetHeroPtr(trainer)) != 1 ? msg : 0x4f86;
            char* nick = pokemon_GetNicknamePtr(pokemon);
            fightMsgctrlSetValue(0x16, (u32)nick);
            fightMenuOpenMsg(msg);
            fightMenuCloseMsg();
            remain--;
            if (remain == 0) {
                break;
            }
        }
        fightFloor_SetStockPokemonNum(0, 0);
        if (darkPokemonGetSnatchSuccessNum() == (s32)((u16)darkpokemonBiosGetScenarioNum() - 1)) {
            GSflagSet(0x4a7, 0);
        }
    } else {
        if ((u8)fightFloor_GetFightKind(0) == 0x10 || (u16)fightFloor_GetEncountDataId(0) == 0x73) {
            GSflagSet(0x5aa, 0);
            GSflagSet(0x5ac, 0);
            GSflagSet(0x5ab, 0);
        }
        if ((u16)fightFloor_GetEncountDataId(0) != 0x15d) {
            u8 count = fightFloor_GetStockPokemonNum(0);
            for (u8 i = 0; i < count; i++) {
                Pokemon* pokemon = fightFloor_GetStockPokemonPtr(0, i);
                if (pokemon != 0) {
                    u16 id = pokemon->getDarkPokemon()->getDarkPokemonID();
                    if (id != 0) {
                        _darkPokemonSetUnderTaker(DeckDarkPokemon::getDeckDarkPokemonObj(id), pokemon, name);
                    }
                }
            }
        }
    }
    u8 num = fightFloorGetFightTrainerFightPokemonPtrAry(0, trainer, ary, 1, 0);
    if ((u16)fightFloor_GetEncountDataId(0) != 0x15d) {
        for (u8 i = 0; i < num; i++) {
            Pokemon* pokemon = fightPokemonGetPokemonPtr(ary[i]);
            u16 id = pokemon->getDarkpokemonDataID();
            if (id != 0) {
                _darkPokemonSetUnderTaker(DeckDarkPokemon::getDeckDarkPokemonObj(id), pokemon, name);
            }
        }
    }
    fightEnemyTrainerWazaSeqHdl = (wazaFlag == 1) ? waza : 0;
    fightCloseAllMenu();
    return 1;
}

}

void _darkPokemonSetUnderTaker(DeckDarkPokemon* deck, Pokemon* pokemon, u16 name) {
    u32 step;
    DarkPokemon* dark;
    dark = pokemon->getDarkPokemon();
    if (deck->getWorth()) {
        step = Hero::getHeroPtr()->getFootStep();
        if (deck->getUnderTakerFlag() || fightFloorIsGcHeroWin(0, fightGetFightResultId())) {
            if (dark->getStatus() < 2) {
                dark->setStatus(darkPokemonStatus2);
                dark->setEscapeTime(step);
                if (name != 0x17d7) {
                    char* nick = pokemon_GetNicknamePtr(pokemon);
                    fightMsgctrlSetValue(0x16, (u32)nick);
                    fightMenuOpenMsg(0x500b);
                    fightMenuCloseMsg();
                }
            }
        }
    }
}

extern "C" {

u32 fightActionFlowSyuuryouPre(FightAction* action) {
    if (fightFloor_GetEnvSndId(0) != 0) {
        soundOpenPlayFadeOutIn(8, 1000, 1000, 255);
        fightMainWaitFrame(60);
    }
    return 1;
}

u32 fightActionFlowFightOutPokemonOutWaza(FightAction* action) {
    FightOutPokemon* actor;
    FightOutPokemon* target;
    FightWaza* waza;
    u16 moto;
    u8 slot;
    FightWaza* actionWaza;
    u8 type;
    Pokemon* pokemon;
    type = fightFloor_GetFightType(0);
    actor = (FightOutPokemon*)fightActionBiosGetActorFightTargetPtr(action);
    actionWaza = fightOutPokemon_GetFightWazaPtr(actor);
    if (!fightWazaCheckValid(actionWaza)) {
        return 0;
    }
    target = (FightOutPokemon*)fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightWaza_GetTargetDataId(actionWaza), type);
    fightFloor_SetAttackPokemonPtr(0, actor);
    fightFloor_SetDefensePokemonPtr(0, target);
    pokemon = fightOutPokemonGetPokemonPtr(actor);
    waza = fightOutPokemon_GetFightWazaPtr(actor);
    moto = fightOutPokemon_GetMotoWazaDataId(actor);
    slot = fightWaza_GetWazaBanme(waza);
    if (!fightWaza_GetAutoMakeFlag(waza)) {
        if (moto != pokemon_GetPokemonWazaDataId(pokemon, slot)) {
            moto = pokemon_GetPokemonWazaDataId(pokemon, slot);
            fightWaza_SetMotoWazaDataId(waza, moto);
            fightWazaSetUseWazaStatus(waza, moto);
            FightOutPokemon* def = fightSeqSelectDefensePokemonPtr(actor, moto, type, 0, 1, 0, -1);
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, def);
        }
    }
    fightSeqWazaExec(action, moto);
    if (!fightOutPokemonIsJoutaiDataId(actor, 0x3E)) {
        fightSeqCheckDarkPokemonJoutaiHyperAct(actor, 0);
    }
    return 1;
}

u32 fightActionFlowFightTrainerUseItem(FightAction* action) {
    FightOutPokemon* actor;
    FightItem* item;
    u16 itemId;
    u8 type;
    void* target;
    type = fightFloor_GetFightType(0);
    actor = (FightOutPokemon*)fightActionBiosGetActorFightTargetPtr(action);
    fightFloor_SetAttackPokemonPtr(0, actor);
    item = fightOutPokemon_GetFightItemPtr(actor);
    itemId = fightItem_GetItemDataId(item);
    if (itemDB_GetKind(itemId) == 1) {
        target = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightItem_GetTargetDataId(item), type);
    } else {
        target = actor;
    }
    fightFloor_SetDefensePokemonPtr(0, target);
    fightSeqItemExec(action, itemId);
    return 1;
}

u32 fightActionFlowFightTrainerCall(FightAction* action) {
    fightFloor_GetFightType(0);
    void* actor = fightActionBiosGetActorFightTargetPtr(action);
    fightFloor_SetAttackPokemonPtr(0, actor);
    fightSeqCallExec(action);
    return 1;
}

u32 fightActionFlowFightOutPokemonIrekae(FightAction* action) {
    FightOutPokemon* actor = (FightOutPokemon*)fightActionBiosGetActorFightTargetPtr(action);
    fightFloor_SetIrekaePokemonPtr(0, actor);
    fightOutPokemon_SetIrekaeTargetEntryId(actor, fightActionBiosGetBuffDataId(action));
    fightSeqIrekaeExec(action);
    return 1;
}

u32 fightActionFlowFightNigeru(FightAction* action) {
    FightOutPokemon* actor;
    u8 type = fightFloor_GetFightType(0);
    actor = (FightOutPokemon*)fightActionBiosGetActorFightTargetPtr(action);
    fightSeqSpecificationActionCounterInit(actor);
    u8 result;
    if (fightTargetIsHostSide(actor, type) == 1) {
        result = fightFloorSetFightResultId(0, 4);
    } else {
        result = fightFloorSetFightResultId(0, 5);
    }
    if (result == 1) {
        fightFloor_SetEscapePokemonPtr(0, actor);
    }
    return 1;
}

u32 fightActionFlowOneTurnPost(FightAction* action) {
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    fightSeqPost(action);
    fightMainWaitFrame(5);
    fightFloorInitFightTarget(0);
    return 1;
}

u32 fightActionFlowAllFightOutPokemonDoFightAction(FightAction* action) {
    fightFloorCreateFightOutPokemonPtrAry(0);
    fightFloorSortFightOutPokemonPtrAry(0, 1);
    u32 r = _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(0, 0);
    if ((u8)r != 1) {
        return r;
    }
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    fightSeqPre(action);
    r = _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(0, 1);
    u32 ret = 1;
    if ((u8)r != 1) {
        ret = r;
    }
    return ret;
}

}

#pragma optimize_for_size off
static u32 _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(FIGHT_FLOOR* floor, u8 phase) {
    FightAction* action;
    u32 i;
    FightOutPokemon* fop;
    for (i = 0; (u16)i < 8; i++) {
        fop = fightFloor_GetFightOutPokemonPtrAry(floor, i);
        if (fop == 0) {
            continue;
        }
        if (!fightOutPokemonCheckFightOut(fop)) {
            fightOutPokemon_SetFightActionFlag(fop, 1);
            continue;
        }
        action = fightOutPokemon_GetFightActionBuffPtr(fop);
        if (action == 0) {
            fightOutPokemon_SetFightActionFlag(fop, 1);
            continue;
        }
        if (!fightActionCheckValid(action)) {
            fightOutPokemon_SetFightActionFlag(fop, 1);
            continue;
        }
        if (phase == 0) {
            if (fightActionGetKindDataId(action) != 8) {
                continue;
            }
        } else {
            if (fightActionGetKindDataId(action) == 8) {
                continue;
            }
        }
        if (fightOutPokemon_GetFightActionFlag(fop) == 1) {
            continue;
        }
        fightOutPokemon_SetFightActionFlag(fop, 1);
        FightAction copy = *action;
        fightActionFlowFifo(&copy);
        if (phase != 0) {
            fightFloorInitFightTarget(0);
            if (fightGetFightResultId() != 0) {
                fightGetFightResultId();
                return 1;
            }
        }
    }
    return 1;
}
#pragma optimize_for_size reset

extern "C" {

u32 fightActionFlowAllFightTrainerSelectFightAction(FightAction* action) {
    u8 type;
    u32 trainerNum;
    FIGHT_SIDE* side;
    u8 flag;
    u32 j;
    u32 i;
    flag = dbgMenuFightGetAllFightTrainerOperateFlag();
    if (flag == 1) {
        type = fightFloor_GetFightType(0);
        trainerNum = (u8)fightFloor_GetFightTypeTrainerNum(0);
        for (i = 0; (u16)i < 2; i++) {
        retrySide:
            side = fightFloorGetValidFightSidePtr(0, i);
            if (side == 0) {
                continue;
            }
            for (j = 0; (u16)j < trainerNum; j++) {
            retryTrainer:
                FIGHT_TRAINER* trainer = fightSideGetValidFightTrainerPtr(side, j);
                if (trainer == 0) {
                    continue;
                }
                if (fightMenuFightTrainerGcHeroOpenMenu(trainer, type, flag) != 0) {
                    continue;
                }
                if ((u16)i == 0) {
                    goto retryTrainer;
                }
                i--;
                goto retrySide;
            }
        }
    } else {
        fightFloorLoopValidFightTrainer(0, _fightActionFlowFightTrainerSelectFightAction, 0, 1);
    }
    return 1;
}

}

static u8 _fightActionFlowFightTrainerSelectFightAction(void* trainer, u16 side, void* data) {
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    if (!fightTrainerSelectFightAction((FIGHT_TRAINER*)trainer, side)) {
        fightFloorSetTuusinErrorFightResult(0);
    }
    return 1;
}

extern "C" {

u32 fightActionFlowKaisiPost(FightAction* action) {
    u8 flag;
    fightFloorCreateFightOutPokemonPtrAry(0);
    fightFloorSortFightOutPokemonPtrAry(0, 0);
    fightSeqInit();
    flag = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear, &flag, 0);
    fightSeqFightActionCreateAndFlowFifo(fightActionBiosGetFightActionDataPtr(action), 0, 6, 0, fight_action_data_kaisi, WAZA_FieldWeather);
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonTokuseiCheckAppear, 0, 1);
    fightSeqFightOutPokemonTokuseiCheckIkaku(1);
    fightSeqFightOutPokemonTokuseiCheckTrace();
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonSoubiItemCheckAppear, 0, 1);
    flag = 1;
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear, &flag, 0);
    fightFloorSetMeetEnemyFightPokemonEnemySideAll(0);
    fightFloorRegistFightTrainerEnemyPokemonFightSideAll(0);
    fightFloorCreateFightPokemonEnemyAryEnemySideAll(0);
    fightFloor_SetFisstAttackRnd(0, HSD_Rand());
    wazaSequenceSysFreeAllWaza();
    return 1;
}

}

static u8 _fightActionFlowKaisiPostSubFightOutPokemonSoubiItemCheckAppear(void* fop, u16 index, void* data) {
    fightSeqPokemonSoubiItemCheckAppear((FightOutPokemon*)fop);
    return 1;
}

static u8 _fightActionFlowKaisiPostSubFightOutPokemonTokuseiCheckAppear(void* fop, u16 index, void* data) {
    fightSeqFightOutPokemonTokuseiCheckAppear((FightOutPokemon*)fop);
    return 1;
}

static u8 _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear(void* fop, u16 index, void* data) {
    if (data != 0) {
        fightSeqFightOutPokemonDarkCheckAppear((FightOutPokemon*)fop, *(u8*)data);
    } else {
        fightSeqFightOutPokemonDarkCheckAppear((FightOutPokemon*)fop, 0);
        fightSeqFightOutPokemonDarkCheckAppear((FightOutPokemon*)fop, 1);
    }
    return 1;
}

extern "C" {
s32 fightActionFlowKaisiPre() {
    enum TsE { TsE0 };
    u16 temp_r3_3;
    u32 temp_r22;
    FightEncountData *temp_r3_4;
    enum TsE var_r22;
    void * temp_r3_12;
    Sequence *var_r25;
    WazaSequence *temp_r20_2;
    WazaSequence *temp_r20_3;
    WazaSequence *temp_r3_10;
    WazaSequence *temp_r3_14;
    WazaSequence *temp_r3_16;
    WazaSequence *temp_r3_5;
    WazaSequence *temp_r3_6;
    WazaSequence *temp_r3_7;
    WazaSequence *temp_r3_9;
    s32 temp_r21_2;
    u16 temp_r20;
    u16 temp_r21;
    volatile s32 saved_reg_r25;
    u16 var_r27;
    u32 var_r28;
    u8 sp8;
    u32 temp_r26;
    u32 temp_r29;
    u32 temp_r31;
    u32 temp_r3_13;
    u32 temp_r3_15;
    u32 temp_r3_8;
    FightOutPokemon *temp_r3_11;
    u8 *temp_r3;
    u8 *temp_r3_2;
    u32 var_r20;
    u8 var_r20_2;
    u32 var_r24;

    var_r25 = (Sequence *)(saved_reg_r25);
    var_r24 = 0;
    sp8 = 0;
    fightFloor_GetFightFloorDataId((FIGHT_FLOOR*)(NULL));
    temp_r3 = (unsigned char *)(fightTargetGetPtrAsNowFightType(0xBU, (void*)(NULL)));
    temp_r22 = (unsigned long)(fightTrainer_GetSequencePtr((FIGHT_TRAINER *)((u8*)(temp_r3))));
    temp_r3_2 = (unsigned char *)(fightTargetGetPtrAsNowFightType(9U, (void*)(temp_r3)));
    temp_r31 = (unsigned long)(fightTrainer_GetSequencePtr((FIGHT_TRAINER *)((u8*)(temp_r3_2))));
    temp_r21 = fightTrainer_GetFightTrainerDataId((FIGHT_TRAINER *)((u8*)(temp_r3_2)));
    temp_r26 = fightFloor_GetSyoukaiWzxDataId((FIGHT_FLOOR*)(NULL));
    temp_r3_3 = fightFloor_GetEncountDataId((FIGHT_FLOOR*)(NULL));
    temp_r3_4 = fightEncountDataBiosGetPtr(temp_r3_3);
    temp_r20 = fightEncountDataBiosGetDiskId((FightEncountData*)(temp_r3_4));
    temp_r29 = fightEncountDataBiosGetSyoukaiWzxDataId((FightEncountData*)(temp_r3_4));
    var_r28 = fightTrainerDB_GetSyoukaiWzxDataId(temp_r21);
    if (var_r28 == 0) {
        var_r28 = 0x5F;
    }
    var_r27 = fightTrainerDB_GetSerihuMsgId(temp_r21, 0U);
    temp_r21_2 = GSmsgGetLength(var_r27) * 5;
    if (fightKind_CheckFightKind(0xAU) != 0) {
        var_r27 = 0;
    }
    if (fightFloorIsNowEncountOpeningVirtualBattle((FIGHT_FLOOR*)(NULL)) != 1) {
        if (fightFloorIsNowEncountVirtualBattle((FIGHT_FLOOR*)(NULL)) == 1) {
            Sequence_SetVisibility((s32) temp_r31, 0);
            battleGridStoreModelVisibilityFlags();
            temp_r3_5 = Sequence_GetWaza((Sequence*)((Sequence *) temp_r22), 0x54U, 4U);
            WazaSequence_Start((WazaSequence*)(temp_r3_5), 1);
            Sequence_SetVisibility((s32) temp_r22, 1);
loop_10:
            if (WazaSequence_IsActive((WazaSequence*)((s32)temp_r3_5)) == 0) {
                Sequence_SetVisibility((s32) temp_r31, 1);
                battleGridStoreModelVisibilityFlags();
                temp_r3_6 = Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), 0x55U, 4U);
                WazaSequence_Start((WazaSequence*)(temp_r3_6), 1);
                if (fightFloor_GetFightKindHostEnemyMsgFlag((FIGHT_FLOOR*)(NULL)) == 1) {
                    fightMsgctrlSetValue((long)(0x22), (unsigned long)(fightTrainerGetPrefixNamePtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_2)))));
                    s32 tmp1 = fightTrainerGetNamePtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_2)));
                    fightMenuOpenTrainerMsg(0x4F4DU);
                    fightMsgctrlSetValue(0x23, tmp1);
                }
loop_16:
                if (WazaSequence_IsActive((WazaSequence*)((s32)temp_r3_6)) == 0) {
                    if (fightFloor_GetFightKindHostEnemyMsgFlag((FIGHT_FLOOR*)(NULL)) == 1) {
                        fightMenuCloseMsg();
                    }
                    fightMainSetAllDispFlag(1);
                    battleGridStoreModelVisibilityFlags();
                    temp_r3_7 = Sequence_GetWaza((Sequence*)((Sequence *) temp_r22), 0x56U, 4U);
                    WazaSequence_Start((WazaSequence*)(temp_r3_7), 1);
loop_23:
                    if (WazaSequence_IsActive((WazaSequence*)(temp_r3_7)) != 0) {
                        if (_fightActionFlowKaisiPreSubCheckVirtualDiskCancel(temp_r20) != 0) {
                            var_r24 = 1;
                        } else {
                            GSthreadSwitch();
                            goto loop_23;
                        }
                    }
                } else if (_fightActionFlowKaisiPreSubCheckVirtualDiskCancel((u16)temp_r20) != 0) {
                    fightMenuCloseMsg();
                    var_r24 = 1;
                } else {
                    GSthreadSwitch();
                    goto loop_16;
                }
            } else if (_fightActionFlowKaisiPreSubCheckVirtualDiskCancel((s32)temp_r20) != 0) {
                var_r24 = 1;
            } else {
                GSthreadSwitch();
                goto loop_10;
            }
            if (var_r24 == 1) {
                fadeSet(3, 0.5f);
                fadeCheck(1);
                fightMainSetAllDispFlag(1);
                battleGridStoreModelVisibilityFlags();
                Sequence_GetWaza((Sequence*)((Sequence *) temp_r22), 0x54U, 4U);
                WazaSequence_Stop();
                Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), 0x55U, 4U);
                WazaSequence_Stop();
                Sequence_GetWaza((Sequence*)((Sequence *) temp_r22), 0x56U, 4U);
                WazaSequence_Stop();
                battleCameraStartRandom(1);
                fadeSet(2, 0.5f);
                sp8 = 0;
            }
            WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)((Sequence *) temp_r22), 0x54U, 4U)));
            WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), 0x55U, 4U)));
            WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)((Sequence *) temp_r22), 0x56U, 4U)));
            temp_r3_8 = fightFloor_GetBgmSndId((FIGHT_FLOOR*)(NULL));
            if (temp_r3_8 != 0) {
                soundOpenPlay((s32) temp_r3_8, 0, 0xFF);
            }
        } else {
            if (temp_r26 != 0) {
                if (temp_r29 != 0) {
                    WazaSequence_Start((WazaSequence*)(Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), (u16) temp_r29, 4U)), 1);
                }
                temp_r3_9 = Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), (u16) temp_r26, 4U);
                WazaSequence_Start((WazaSequence*)(temp_r3_9), 1);
loop_32:
                if (_fightActionFlowKaisiPreSubCheckCancel((bool*)(&sp8)) != 1) {
                    if (WazaSequence_IsActive((WazaSequence*)(temp_r3_9)) != 0) {
                        GSthreadSwitch();
                        goto loop_32;
                    }
                    if (fightFloor_GetFightKindHostEnemyMsgFlag((FIGHT_FLOOR*)(NULL)) == 1) {
                        temp_r3_10 = Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), _fight_kaisi_pre_trainer_intr_wzx_data_id, 4U);
                        WazaSequence_Start((WazaSequence*)(temp_r3_10), 1);
loop_37:
                        if (_fightActionFlowKaisiPreSubCheckCancel((bool*)(&sp8)) != 1) {
                            if (WazaSequence_IsActive((WazaSequence*)(temp_r3_10)) != 0) {
                                GSthreadSwitch();
                                goto loop_37;
                            }
                            goto block_40;
                        }
                    } else {
block_40:
                        if (temp_r29 != 0) {
                            temp_r20_2 = Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), (u16) temp_r29, 4U);
loop_42:
                            if ((_fightActionFlowKaisiPreSubCheckCancel((bool*)(&sp8)) != 1) && (WazaSequence_IsActive((WazaSequence*)(temp_r20_2)) != 0)) {
                                GSthreadSwitch();
                                goto loop_42;
                            }
                        }
                    }
                }
            }
            if ((fightFloorIsNowEncountHostEnemyPokemonKime((FIGHT_FLOOR*)(NULL)) == 1) && (fightTargetIsHostSide((void*)(temp_r3_2), (u16) fightFloor_GetFightType((FIGHT_FLOOR*)(NULL))) == 0)) {
                u8 cmpv = fightFloor_GetFightKind((FIGHT_FLOOR*)(NULL));
                if (cmpv == 0xC) {
                    var_r22 = (enum TsE)(0x4FF6);
                    WildPokemonCatchFlag = 0;
                } else {
                    var_r22 = (enum TsE)(0x4FFD);
                }
                if ((temp_r3_3 == 0xD9) || (temp_r3_3 == 0x191)) {
                    var_r22 = (enum TsE)(0);
                }
                var_r20 = 0;
loop_67:
                if (var_r20 >= 2U) {

                } else {
                    temp_r3_11 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_2)), (unsigned short)((u16) var_r20));
                    if ((temp_r3_11 != NULL) && (temp_r3_12 = fightOutPokemon_GetSequencePtr((FightOutPokemon*)(temp_r3_11)), var_r25 = (Sequence *)temp_r3_12, ((var_r25 == NULL) == 0))) {
                        temp_r20_3 = Sequence_GetWaza((Sequence*)(temp_r3_12), 0x9FU, 4U);
                        if (var_r22 != 0) {
                            fightMsgctrlSetValue((long)(0x16), (unsigned long)(fightOutPokemonGetNamePtr((FightOutPokemon*)(temp_r3_11))));
                            fightMenuOpenMsg(var_r22);
                        }
                        temp_r3_13 = fightFloor_GetBgmSndId((FIGHT_FLOOR*)(NULL));
                        if (temp_r3_13 != 0) {
                            soundOpenPlay((s32) temp_r3_13, 0, 0xFF);
                        }
                        WazaSequence_Start((WazaSequence*)((s32)temp_r20_3), 1);
                        GSsndPlayVolume((u32) fightOutPokemonGetVoiceSndId((FightOutPokemon*)(temp_r3_11)), 0, 0xFFU, 0U);
                        if (fightFloor_GetEnvSndId((FIGHT_FLOOR*)(NULL)) != 0) {
                            GSsndPlayVolume(fightOutPokemon_GetKanseiSndId((FightOutPokemon*)(temp_r3_11)), 0, 0x7FU, 0U);
                        }
                        while (WazaSequence_IsActive((WazaSequence*)((s32)temp_r20_3)) != 0) {
                            GSthreadSwitch();
                        }
                        if (var_r22 != 0) {
                            fightMenuCloseMsg();
                        }
                    } else {
                        var_r20 = var_r20 + 1;
                        goto loop_67;
                    }
                }
            } else {
                if (sp8 == 1) {
                    fadeSet(3, 0.5f);
                    fadeCheck(1);
                    if (temp_r29 != 0) {
                        Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), (u16) temp_r29, 4U);
                        WazaSequence_Stop();
                    }
                    Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), (u16) temp_r26, 4U);
                    WazaSequence_Stop();
                    if (fightFloor_GetFightKindHostEnemyMsgFlag((FIGHT_FLOOR*)(NULL)) == 1) {
                        Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), _fight_kaisi_pre_trainer_intr_wzx_data_id, 4U);
                        WazaSequence_Stop();
                    }
                }
                if (var_r27 != 0) {
                    temp_r3_14 = Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), 0x5FU, 4U);
                    WazaSequence_Start((WazaSequence*)(temp_r3_14), 1);
                    if (sp8 == 1) {
                        fadeSet(2, 0.5f);
                        sp8 = 0;
                    }
                    Sequence_Talk((Sequence *)((s32) temp_r31));
                    fightMenuOpenTrainerMsg((u32) var_r27);
                    fightMainWaitFrame(temp_r21_2);
                    fightMenuCloseMsg();
                    while (WazaSequence_IsActive((WazaSequence*)(temp_r3_14)) != 0) {
                        GSthreadSwitch();
                    }
                }
                temp_r3_15 = fightFloor_GetBgmSndId((FIGHT_FLOOR*)(NULL));
                if (temp_r3_15 != 0) {
                    soundOpenPlay((s32) temp_r3_15, 0, 0xFF);
                }
                if (fightFloor_GetFightKindHostEnemyMsgFlag((FIGHT_FLOOR*)(NULL)) == 1) {
                    fightMsgctrlSetValue((long)(0x22), (unsigned long)(fightTrainerGetPrefixNamePtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_2)))));
                    fightMsgctrlSetValue(0x23, fightTrainerGetNamePtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_2))));
                    temp_r3_16 = Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), var_r28, 4U);
                    WazaSequence_Start((WazaSequence*)(temp_r3_16), 1);
                    if (sp8 == 1) {
                        fadeSet(2, 0.5f);
                        sp8 = 0;
                    }
                    fightMenuOpenTrainerMsg(0x4F4DU);
                    if (var_r28 == 0x5F) {
                        while (WazaSequence_IsActive((WazaSequence*)(temp_r3_16)) != 0) {
                            GSthreadSwitch();
                        }
                        introBossFlag = 0;
                        fightMenuCloseMsg();
                    } else {
                        introBossFlag = 1;
                    }
                }
            }
            if (sp8 == 1) {
                fadeSet(2, 0.5f);
            }
            if (temp_r26 != 0) {
                if (temp_r29 != 0) {
                    WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), (u16) temp_r29, 4U)));
                }
                WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), (u16) temp_r26, 4U)));
                if (fightFloor_GetFightKindHostEnemyMsgFlag((FIGHT_FLOOR*)(NULL)) == 1) {
                    WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), _fight_kaisi_pre_trainer_intr_wzx_data_id, 4U)));
                }
            }
            if (var_r27 != 0) {
                WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), 0x5FU, 4U)));
            }
            if ((fightFloor_GetFightKindHostEnemyMsgFlag((FIGHT_FLOOR*)(NULL)) == 1) && (var_r28 == 0x5F)) {
                WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)((Sequence *) temp_r31), var_r28, 4U)));
            }
            if ((fightFloorIsNowEncountHostEnemyPokemonKime((FIGHT_FLOOR*)(NULL)) == 1) && (fightTargetIsHostSide((void*)(temp_r3_2), (u16) fightFloor_GetFightType((FIGHT_FLOOR*)(NULL))) == 0)) {
                var_r20_2 = 0;
                while (var_r20_2 < 2U) {
                    WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)(var_r25), 0x9FU, 4U)));
                    var_r20_2 += 1;
                }
            }
        }
    }
    return 1;
}
}

extern "C" {

}

static bool _fightActionFlowKaisiPreSubCheckVirtualDiskCancel(u16 diskId) {
    u8 kind = fightFloor_GetFightKind(0);
    u16 key[16];
    menuGetKeyInfo(key, 1);
    if ((key[0] & 0x20) && kind == 0xf) {
        if (GSflagGet(0x8f5) == 1 || GSflagGet(deckDataVirtualDB_GetFlag(diskId)) == 1) {
            return true;
        }
    }
    return false;
}

static bool _fightActionFlowKaisiPreSubCheckCancel(bool* cancel) {
    if (cancel == 0) {
        return false;
    }
    u16 key[16];
    menuGetKeyInfo(key, 1);
    u16 pressed = key[0];
    if (fadeCheck(0) == 0 && (pressed & 0x20)) {
        *cancel = true;
    }
    return *cancel;
}

extern "C" {

void fightActionFlowKaisiPreSubLoad(void) {
    FIGHT_TRAINER* hostTrainer;
    u32 msgA;
    u32 msgB;
    FIGHT_TRAINER* trainer;
    Sequence* seq;
    u16 trainerId;
    u32 wzx;
    u32 wzx2;
    Sequence* hostSeq;
    u8 type;
    fightFloor_GetFightFloorDataId(0);
    hostTrainer = (FIGHT_TRAINER*)fightTargetGetPtrAsNowFightType(0xb, 0);
    hostSeq = fightTrainer_GetSequencePtr(hostTrainer);
    trainer = (FIGHT_TRAINER*)fightTargetGetPtrAsNowFightType(9, hostTrainer);
    seq = fightTrainer_GetSequencePtr(trainer);
    trainerId = fightTrainer_GetFightTrainerDataId(trainer);
    wzx = fightFloor_GetSyoukaiWzxDataId(0);
    wzx2 = fightEncountDataBiosGetSyoukaiWzxDataId(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0)));
    msgA = fightTrainerDB_GetSyoukaiWzxDataId(trainerId);
    if (msgA == 0) {
        msgA = 0x5f;
    }
    extern u16 fightTrainerDB_GetSerihuMsgId(u16, u8);
    msgB = fightTrainerDB_GetSerihuMsgId(trainerId, 0);
    if (fightKind_CheckFightKind(10)) {
        msgB = 0;
    }
    if (fightFloorIsNowEncountVirtualBattle(0) == 1) {
        Sequence_LoadWaza(hostSeq, 0x54, 4, 0);
        Sequence_LoadWaza(seq, 0x55, 4, 0);
        Sequence_LoadWaza(hostSeq, 0x56, 4, 0);
    } else {
        fightFloorIsNowEncountOpeningVirtualBattle(0);
    }
    if (fightFloorIsNowEncountHostEnemyPokemonKime(0) == 1 && !fightTargetIsHostSide(trainer, type = fightFloor_GetFightType(0))) {
        for (u8 i = 0; i < 2; i++) {
            FightOutPokemon* fop = fightTrainerGetValidFightOutPokemonPtr(trainer, i);
            Sequence* fseq;
            if (fop != 0 && (fseq = (Sequence*)fightOutPokemon_GetSequencePtr(fop)) != 0) {
                Sequence_LoadWaza(fseq, 0x9f, 4, 0);
            }
        }
    } else {
        if (wzx != 0) {
            if (wzx2 != 0) {
                Sequence_LoadWaza(seq, wzx2, 4, 0);
            }
            Sequence_LoadWaza(seq, wzx, 4, 0);
            if (fightFloor_GetFightKindHostEnemyMsgFlag(0) == 1) {
                u16 idx = (u16)HSD_Rand() % _fight_kaisi_pre_trainer_intr_wzx_data_id_num;
                _fight_kaisi_pre_trainer_intr_wzx_data_id = idx;
                _fight_kaisi_pre_trainer_intr_wzx_data_id = _fight_kaisi_pre_trainer_intr_wzx_data_id_ary[idx];
                Sequence_LoadWaza(seq, _fight_kaisi_pre_trainer_intr_wzx_data_id, 4, 0);
            } else {
                _fight_kaisi_pre_trainer_intr_wzx_data_id = 0;
            }
        }
        if (msgB != 0) {
            Sequence_LoadWaza(seq, 0x5f, 4, 0);
        }
        if (fightFloor_GetFightKindHostEnemyMsgFlag(0) == 1) {
            Sequence_LoadWaza(seq, msgA, 4, 0);
        }
    }
}
extern "C" {
s32 fightActionFlowKaisiNyuujouPokemon(FightAction* action) {
    enum TsE { TsE0 };
    u32 var_r17_6;
    u16 var_r17_3;
    s32 saved_reg_r27;
    FIGHT_SIDE *temp_r3;
    FIGHT_TRAINER *temp_r3_10;
    enum TsE temp_r28;
    s32 var_r18_2;
    FIGHT_TRAINER *temp_r3_8;
    FIGHT_TRAINER *temp_r3_9;
    s32 var_r22;
    u8 temp_r25;
    u16 var_r21;
    FightOutPokemon *temp_r3_6;
    FightOutPokemon *var_r27;
    FIGHT_TRAINER *var_r23;
    u32 var_r20;
    FightPokemon *temp_r3_3;
    WazaSequence *temp_r17_3;
    u16 temp_r17;
    s32 temp_r19;
    u32 temp_r24;
    u16 var_r17;
    u16 var_r17_2;
    s32 saved_reg_r26;
    u16 var_r17_5;
    s32 saved_reg_r23;
    s32 var_r18;
    FIGHT_TRAINER *temp_r3_5;
    s32 var_r19;
    u16 var_r19_2;
    u32 var_r19_3;
    u16 var_r19_4;
    FightOutPokemon *temp_r18_3;
    FightOutPokemon *temp_r3_4;
    Sequence *temp_r3_7;
    u16 var_r22_2;
    u16 var_r24;
    u32 temp_r18;
    u32 var_r26;
    u8 temp_r18_2;
    Pokemon *temp_r17_2;
    FIGHT_TRAINER *temp_r3_2;
    u8 temp_r30;
    u32 temp_r31;
    u16 var_r17_4;

    var_r26 = saved_reg_r26;
    var_r27 = (FightOutPokemon *)(saved_reg_r27);
    temp_r17 = fightActionDataBiosGetBuff((FightActionData*)(fightActionBiosGetFightActionDataPtr(action)));
    temp_r30 = fightFloor_GetFightType((FIGHT_FLOOR*)(NULL));
    temp_r31 = fightFloor_GetFightTypeFightoutPokemonNum((FIGHT_FLOOR*)(NULL));
    var_r23 = (FIGHT_TRAINER *)(saved_reg_r23);
    temp_r28 = (enum TsE)(fightFloor_GetFightTypeTrainerNum((FIGHT_FLOOR*)(NULL)));
    temp_r24 = fightFloor_GetEncountDataId((FIGHT_FLOOR*)(NULL));
    temp_r3 = (FIGHT_SIDE *)(fightTargetGetPtr(temp_r17, (void*)(NULL), (u16) temp_r30));
    if (fightSideCheckValid((FIGHT_SIDE*)(temp_r3)) == 0) {
        return 0;
    }
    temp_r25 = fightSideGetDoFightTrainerCount((FIGHT_SIDE*)(temp_r3));
    var_r21 = 0;
    while (var_r21 < temp_r28) {
        temp_r3_2 = fightSideGetValidFightTrainerPtr((FIGHT_SIDE*)(temp_r3), var_r21);
        var_r23 = temp_r3_2;
        if (var_r23 != NULL) {
            var_r26 = (unsigned long)(fightTrainer_GetSequencePtr((FIGHT_TRAINER *)((u8*)((u8 *) temp_r3_2))));
            if (var_r26 != 0) {
                fightTrainerGetDoFightOutFightOutPokemonCount((FightTrainer*)((FightTrainer *) var_r23));
                var_r22 = 0;
                var_r20 = 0;
loop_17:
                if (var_r20 < 6U) {
                    if ((var_r22 < temp_r31) && (var_r22 < 2U)) {
                        temp_r3_3 = (FightPokemon *)(fightTrainer_GetFightPokemonPtr((FIGHT_TRAINER *)((u8*)((u8 *) var_r23)), (unsigned short)(var_r20)));
                        if (fightPokemonCheckFightOut((FightPokemon*)(temp_r3_3)) != 0) {
                            menuFaceLoadFightPokemon((s32) temp_r3_3, 0, 0);
                            temp_r18 = pokemonCreateSequence((FightPokemon*)(temp_r3_3));
                            var_r27 = (FightOutPokemon *)(fightTrainer_GetFightoutPokemonPtr((u8*)((u8 *) var_r23), (u16)var_r20));
                            temp_r17_2 = fightPokemonGetPokemonPtr((FightPokemon*)(temp_r3_3));
                            fightOutPokemonCreate((FightOutPokemon*)(var_r27), (FightPokemon*)(temp_r3_3), (Sequence*)((Sequence *) temp_r18));
                            var_r22 += 1;
                            fightOutPokemonRegWzxLoad((FightOutPokemon*)(var_r27));
                            if ((fightFloor_GetFightKindDoZukanMitaFlag((FIGHT_FLOOR*)(NULL)) == 1) && (fightOutPokemonIsGcHeroFightOutPokemon((FightOutPokemon*)(var_r27)) == 0)) {
                                fightOutPokemonSetOnZukanFlag((FightOutPokemon*)(var_r27), 0U);
                                if ((temp_r24 != 0xD9) && (temp_r24 != 0x15E) && (pokemonIsDarkPokemon((Pokemon*)(temp_r17_2)) == 1)) {
                                    darkPokemonBiosSetFightFlag(pokemon_GetDarkpokemonDataId((Pokemon*)(temp_r17_2)));
                                }
                            }
                            battleGridAddPokemon((NullSequence*)((NullSequence *) var_r26), (NullSequence*)((NullSequence *) temp_r18));
                        }
                        var_r20 += 1;
                        goto loop_17;
                    }
                }
            }
        }
        var_r21 += 1;
    }
    if ((fightFloorIsNowEncountHostEnemyPokemonKime((FIGHT_FLOOR*)(NULL)) == 1) && (fightTargetIsHostSide((void*)(var_r23), (u16) fightFloor_GetFightType((FIGHT_FLOOR*)(NULL))) == 0)) {
        var_r17 = 0;
        while (var_r17 < temp_r28) {
            var_r18 = 0;
            while (var_r18 < temp_r31) {
                temp_r3_4 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) var_r23)), (unsigned short)(var_r18));
                if (temp_r3_4 != NULL) {
                    fightSeqVanishOff((FightOutPokemon*)(temp_r3_4));
                    battleGridUpdate();
                }
                var_r18 += 1;
            }
            var_r17 += 1;
        }
    } else if (fightFloorIsNowEncountOpeningVirtualBattle((FIGHT_FLOOR*)(NULL)) == 1) {
        var_r17_2 = 0;
        while (var_r17_2 < temp_r28) {
            temp_r3_5 = fightSideGetValidFightTrainerPtr((FIGHT_SIDE*)(temp_r3), var_r17_2);
            if (temp_r3_5 != NULL) {
                var_r18_2 = 0;
                while (var_r18_2 < temp_r31) {
                    temp_r3_6 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_5)), (unsigned short)(var_r18_2));
                    if (temp_r3_6 != NULL) {
                        fightOutPokemonDasuEffect((FightTrainer*)((FightTrainer *) temp_r3_5), (FightOutPokemon*)(temp_r3_6), 0U);
                        temp_r3_7 = (Sequence *)(fightOutPokemon_GetSequencePtr((FightOutPokemon*)(temp_r3_6)));
                        if (temp_r3_7 != NULL) {
                            Sequence_SetVisibility((u32) temp_r3_7, 1);
                            battleGridStoreModelVisibilityFlags();
                            battleGridUpdate();
                        }
                    }
                    var_r18_2 += 1;
                }
            }
            var_r17_2 = var_r17_2 + 1;
        }
    } else {
        var_r17_3 = 0;
        while (var_r17_3 < temp_r28) {
            temp_r3_8 = fightSideGetValidFightTrainerPtr((FIGHT_SIDE*)(temp_r3), (u8)var_r17_3);
            if (temp_r3_8 != NULL) {
                var_r19 = 0;
loop_48:
                if (var_r19 < temp_r31) {
                    var_r27 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_8)), (unsigned short)(var_r19));
                    if (var_r27 == NULL) {
                        var_r19 += 1;
                        goto loop_48;
                    }
                }
                fightTrainerBallThrowEffect((FightTrainer*)((FightTrainer *) temp_r3_8), (FightOutPokemon*)(var_r27), 0U);
                var_r19_2 = 0;
                while (var_r19_2 < temp_r31) {
                    var_r27 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_8)), (unsigned short)(var_r19_2));
                    if (var_r27 != NULL) {
                        fightOutPokemonDasuEffect((FightTrainer*)((FightTrainer *) temp_r3_8), (FightOutPokemon*)(var_r27), 0U);
                    }
                    var_r19_2 += 1;
                }
            }
            var_r17_3 += 1;
        }
        var_r24 = 0;
        while (var_r24 < temp_r28) {
            temp_r3_9 = fightSideGetValidFightTrainerPtr((FIGHT_SIDE*)((s32)temp_r3), (u16)var_r24);
            if (temp_r3_9 != NULL) {
                temp_r19 = fightTrainerDB_GetSyoukaiWzxDataId(fightTrainer_GetFightTrainerDataId((FIGHT_TRAINER *)((u8*)((u8 *) temp_r3_9))));
                temp_r18_2 = fightTrainerGetDoFightOutFightOutPokemonCount((FightTrainer*)((FightTrainer *) temp_r3_9));
                var_r17_4 = 0;
                while (var_r17_4 < temp_r31) {
                    var_r27 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_9)), (unsigned short)(var_r17_4));
                    if (var_r27 != NULL) {
                        _fightActionFlowKaisiNyuujouPokemonSubAppearMsg((FIGHT_TRAINER*)(temp_r3_9), (FightOutPokemon*)(var_r27), (u16) temp_r25, (u16) temp_r18_2, var_r24, (u16)var_r17_4, 0U);
                    }
                    var_r17_4 += 1;
                }
                var_r22_2 = 0;
loop_66:
                if (var_r22_2 < temp_r31) {
                    var_r27 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_9)), (unsigned short)(var_r22_2));
                    if (var_r27 == NULL) {
                        var_r22_2 += 1;
                        goto loop_66;
                    }
                }
                if ((u8) introBossFlag == 1) {
                    temp_r17_3 = Sequence_GetWaza((Sequence*)((Sequence *) var_r26), temp_r19, 4U);
                    while (WazaSequence_IsActive((WazaSequence*)(temp_r17_3)) != 0) {
                        GSthreadSwitch();
                    }
                    WazaSequence_Free((WazaSequence*)(temp_r17_3));
                    introBossFlag = 0;
                    fightMenuCloseMsg();
                }
                battleGridUpdate();
                fightTrainerBallThrowEffect((FightTrainer*)((FightTrainer *) temp_r3_9), (FightOutPokemon*)(var_r27), 1U);
                fightMsgctrlSetValue((long)(0x22), (unsigned long)(fightTrainerGetPrefixNamePtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_9)))));
                fightMsgctrlSetValue(0x23, fightTrainerGetNamePtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_9))));
                fightMsgctrlSetValue(0x25, fightTrainerGetNamePtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_9))));
                _fightActionFlowKaisiNyuujouPokemonSubAppearMsg((FIGHT_TRAINER*)(temp_r3_9), (FightOutPokemon*)(var_r27), (u16) temp_r25, (u16) temp_r18_2, var_r24, var_r22_2, 1U);
                fightTrainerBallThrowEffect((FightTrainer*)((FightTrainer *) temp_r3_9), (FightOutPokemon*)(var_r27), 2U);
                fightOutPokemonDasuEffect((FightTrainer*)((FightTrainer *) temp_r3_9), (FightOutPokemon*)(var_r27), 1U);
                fightOutPokemonDasuEffect((FightTrainer*)((FightTrainer *) temp_r3_9), (FightOutPokemon*)(var_r27), 2U);
                var_r17_5 = 0;
                while (var_r17_5 < temp_r31) {
                    var_r27 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_9)), (unsigned short)(var_r17_5));
                    if (var_r27 != NULL) {
                        temp_r18_3 = fightFloor_GetAttackPokemonPtr((FIGHT_FLOOR*)(NULL));
                        fightFloor_SetAttackPokemonPtr((FIGHT_FLOOR*)(NULL), (FightOutPokemon*)(var_r27));
                        if (fightOutPokemonIsGcHeroFightOutPokemon((FightOutPokemon*)(var_r27)) == 0) {
                            fightMenuFightOutPokemonOpenStatusMenuStart((FightOutPokemon*)(var_r27), (u16) temp_r30, 0U);
                            fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0U, (FightOutPokemon*)(var_r27), (u16) temp_r30, 0, 1U);
                        } else {
                            fightMenuFightOutPokemonOpenStatusMenuStart((FightOutPokemon*)(var_r27), (u16) temp_r30, 1U);
                            fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0U, (FightOutPokemon*)(var_r27), (u16) temp_r30, 0, 1U);
                        }
                        fightOutPokemonDasuEffect((FightTrainer*)((FightTrainer *) temp_r3_9), (FightOutPokemon*)(var_r27), 3U);
                        fightOutPokemonDasuEffect((FightTrainer*)((FightTrainer *) temp_r3_9), (FightOutPokemon*)(var_r27), 4U);
                        fightMenuFightOutPokemonCloseStatusMenu((FightOutPokemon*)(var_r27), (u16) temp_r30, 0U);
                        fightFloor_SetAttackPokemonPtr((FIGHT_FLOOR*)(NULL), (FightOutPokemon*)(temp_r18_3));
                    }
                    var_r17_5 += 1;
                }
            }
            var_r24 += 1;
        }
        fightMenuCloseMsg();
        var_r17_6 = 0;
        while (var_r17_6 < temp_r28) {
            temp_r3_10 = fightSideGetValidFightTrainerPtr((FIGHT_SIDE*)(temp_r3), var_r17_6);
            if (temp_r3_10 != NULL) {
                var_r19_3 = 0;
loop_87:
                if (var_r19_3 < temp_r31) {
                    var_r27 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_10)), (unsigned short)(var_r19_3));
                    if (var_r27 == NULL) {
                        var_r19_3 += 1;
                        goto loop_87;
                    }
                }
                fightTrainerBallThrowEffect((FightTrainer*)((FightTrainer *) temp_r3_10), (FightOutPokemon*)(var_r27), 3U);
                var_r19_4 = 0;
                while (var_r19_4 < temp_r31) {
                    var_r27 = fightTrainerGetValidFightOutPokemonPtr((FIGHT_TRAINER *)((FightTrainer*)((FightTrainer *) temp_r3_10)), (unsigned short)(var_r19_4));
                    if (var_r27 != NULL) {
                        fightOutPokemonDasuEffect((FightTrainer*)((FightTrainer *) temp_r3_10), (FightOutPokemon*)(var_r27), 5U);
                    }
                    var_r19_4 += 1;
                }
            }
            var_r17_6 += 1;
        }
    }
    return 1;
}
}

}

static void _fightActionFlowKaisiNyuujouPokemonSubAppearMsg(FIGHT_TRAINER* trainer, FightOutPokemon* fop, u16 trainerCount, u16 fightOutCount, u16 unused, u16 index, u8 mode) {
    u32 new_var;
    bool isHero;
    bool tuusin;
    isHero = fightOutPokemonIsGcHeroFightOutPokemon(fop) == 1;
    tuusin = fightFloorIsNowEncountTuusinTaisen(0) == 1;
    if ((fightTrainerGetPrefixNamePtr(trainer) == 0) && (!isHero)) {
        tuusin = 1;
    }
    new_var = (u32)pokemon_GetNicknamePtr(fightOutPokemonGetPokemonPtr(fop));
    u32 nick = new_var;
    if (mode == 0) {
        if (tuusin == 1) {
            if (index == 0) {
                fightMsgctrlSetValue(0x14, nick);
                fightMsgctrlSetValue(0x16, nick);
            } else {
                fightMsgctrlSetValue(0x15, nick);
                fightMsgctrlSetValue(0x17, nick);
            }
        } else if (isHero == 1) {
            if (index == 0) {
                fightMsgctrlSetValue(0x15, nick);
                fightMsgctrlSetValue(0x17, nick);
            } else {
                fightMsgctrlSetValue(0x14, nick);
                fightMsgctrlSetValue(0x16, nick);
            }
        } else if (index == 0) {
            fightMsgctrlSetValue(0x14, nick);
            fightMsgctrlSetValue(0x16, nick);
        } else {
            fightMsgctrlSetValue(0x15, nick);
            fightMsgctrlSetValue(0x17, nick);
        }
    } else if (mode == 1) {
        u32 msg;
        if ((trainerCount <= 1) && (fightOutCount > 1)) {
            if (tuusin == 1) {
                msg = 0x4f54;
            } else if (isHero == 1) {
                msg = 0x4f59;
            } else {
                msg = 0x4f51;
            }
        } else {
            fightMsgctrlSetValue(0x14, nick);
            fightMsgctrlSetValue(0x16, nick);
            if (tuusin == 1) {
                msg = 0x4f53;
            } else if (isHero == 1) {
                msg = 0x4f58;
            } else {
                msg = 0x4f50;
            }
        }
        fightMenuOpenMsg(msg);
    }
}
extern "C" {
s32 fightActionFlowKaisiNyuujouTrainer(FightAction* action) {
    s32 temp_r3_2;
    u8 sp9;
    s8 sp8;
    FIGHT_SIDE *temp_r3;
    FIGHT_TRAINER *temp_r3_5;
    FightEncountData *temp_r20;
    FightPokemon *temp_r17_4;
    FightPokemon *temp_r17_6;
    FightTrainer *temp_r31;
    Hero *temp_r25;
    Pokemon *temp_r3_3;
    Pokemon *temp_r3_4;
    u8 var_r20;
    s8 var_r29;
    u16 temp_r17;
    u16 temp_r17_2;
    u16 temp_r17_3;
    s32 temp_r17_5;
    s32 temp_r19;
    u32 temp_r3_6;
    u8 temp_r0;
    u8 temp_r18;
    s32 temp_r21;
    u8 temp_r21_2;
    u8 temp_r26;
    u8 unkspC[sizeof(s32) + 2424];
    s32 var_r22;
    u8 var_r23;
    s32 var_r27;
    u8 var_r30;
    u8 var_r4;
    u8 var_r4_2;

    temp_r17 = fightActionDataBiosGetBuff((FightActionData*)(fightActionBiosGetFightActionDataPtr(action)));
    temp_r20 = fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId((FIGHT_FLOOR*)(NULL)));
    temp_r18 = fightFloor_GetFightType((FIGHT_FLOOR*)(NULL));
    temp_r26 = fightFloor_GetFightTypeTrainerNum((FIGHT_FLOOR*)(NULL));
    var_r27 = fightFloor_GetFightTypeEntryPokemonNum((FIGHT_FLOOR*)(NULL));
    temp_r21 = fightFloor_GetFightTypeFightoutPokemonNum((FIGHT_FLOOR*)(NULL));
    temp_r3 = (FIGHT_SIDE *)(fightTargetGetPtr(temp_r17, (void*)(NULL), (u16) temp_r18));
    if (fightSideCheckValid((FIGHT_SIDE*)(temp_r3)) == 0) {
        return 0;
    }
    temp_r19 = fightSide_GetFightSideDataId((FightSide*)((FightSide *) temp_r3));
    var_r30 = 0;
    while (var_r30 < (s32) temp_r26) {
        temp_r31 = fightSide_GetFightTrainerPtr((FightSide*)((FightSide *) temp_r3), (u16) var_r30);
        temp_r0 = var_r30 + ((temp_r17 != 4) * temp_r26);
        temp_r17_2 = fightEncountDataBiosGetFightTrainerDataId((FightEncountData*)(temp_r20), temp_r0);
        temp_r3_2 = fightEncountDataBiosGetGSInputDevice((FightEncountData*)(temp_r20), temp_r0);
        if (fightTrainerCheckTrainerDataIdValid(temp_r17_2, temp_r3_2) != 0) {
            if (menuCBBios_CurrentlyWorkingToolBattle() == 1) {
                heroBiosCopy((Hero*)(&unkspC), (Hero*)(menuCBBios_GetHeroImmediately(temp_r0)));
            } else if (((fightFloor_GetFightKind((FIGHT_FLOOR*)(NULL)) == 6) || (fightFloor_GetFightKind((FIGHT_FLOOR*)(NULL)) == 7)) && (fightTrainerDB_GetKindDataId(temp_r17_2) == 1)) {
                heroBiosCopy((Hero*)(&unkspC), (Hero*)(fightGetMenuCtrlHero()));
            } else {
                fightTrainerCreateFightTrainerDataIdToHero(temp_r17_2, temp_r3_2, (Hero*)(&unkspC), 0U);
            }
            fightTrainerCreate((FightTrainer*)(temp_r31), (Hero*)(&unkspC), temp_r17_2, (u32) temp_r3_2, fightTrainerCreateSequence(temp_r17_2));
            temp_r25 = fightTrainer_GetHeroPtr((FIGHT_TRAINER *)((u8*)((u8 *) temp_r31)));
            if (fightTrainerCheckValid((FightTrainer*)(temp_r31)) != 0) {
                fightTrainerSortFightTrainerDataIdToHeroTemotiPokemon((FightTrainer*)(temp_r31), (u16) var_r27, (u32) temp_r21);
                if ((fightFloor_GetTrainer((FIGHT_FLOOR*)(NULL)) == 0) && (fightTrainerIsGcHero((FIGHT_TRAINER *)((FightTrainer*)(temp_r31))) == 0)) {
                    var_r27 = 1;
                }
                var_r29 = 0;
                var_r22 = 0;
loop_33:
                if (var_r22 < 6U) {
                    if ((var_r29 < (s32) temp_r21) && (var_r29 < (s32) (u16) var_r27) && (var_r29 < 6)) {
                        temp_r3_3 = (Pokemon *)(heroGetStatus((Hero*)(temp_r25), 3U, (u16) var_r22));
                        if ((pokemonCheckFightOut((Pokemon*)(temp_r3_3)) != 0) && (fightTrainerCheckTemotiPokemonFightEntry((FIGHT_TRAINER *)((FightTrainer*)(temp_r31)), (Pokemon *)((Pokemon*)(temp_r3_3))) == NULL)) {
                            if ((fightFloorIsNowEncountVirtualBattle((FIGHT_FLOOR*)(NULL)) == 1) || (fightFloorIsNowEncountOpeningVirtualBattle((FIGHT_FLOOR*)(NULL)) == 1)) {
                                temp_r17_3 = fightEncountDataBiosGetDiskId((FightEncountData*)(fightEncountDataBiosGetPtr(fightGetFightEncountDataId())));
                                if (fightTargetIsHostSide((void*)(temp_r31), (u16) fightFloor_GetFightType((FIGHT_FLOOR*)(NULL))) == 1) {
                                    var_r4 = deckDataVirtualDB_GetAllyJoutai(temp_r17_3, var_r22);
                                } else {
                                    var_r4 = deckDataVirtualDB_GetEnemyJoutai(temp_r17_3, var_r22);
                                }
                                ((Pokemon*)(temp_r3_3))->setCondition(var_r4);
                            }
                            temp_r17_4 = (FightPokemon *)(fightTrainer_GetFightPokemonPtr((FIGHT_TRAINER *)((u8*)((u8 *) temp_r31)), (unsigned short)((u16) var_r29)));
                            fightPokemonCreate((FightTrainer*)(temp_r31), (FightPokemon*)(temp_r17_4), (Pokemon*)(temp_r3_3), fightFloorGetFightPokemonEntryCntInc((FIGHT_FLOOR*)(NULL)));
                            if ((fightFloor_GetFightKindGetFriendFlag((FIGHT_FLOOR*)(NULL)) == 1) && (fightFloor_GetFightKindBossFlag((FIGHT_FLOOR*)(NULL)) == 1) && (fightTrainerIsGcHero((FIGHT_TRAINER *)((FightTrainer*)(temp_r31))) == 1)) {
                                fightPokemonGetFriendFormPokemonFriendFilterId((FightPokemon*)(temp_r17_4), (void*)((u8 *)3));
                            }
                            var_r29 += 1;
                        }
                        var_r22 += 1;
                        goto loop_33;
                    }
                }
                var_r23 = 0;
loop_51:
                if (var_r23 < 6U) {
                    if ((var_r29 < (s32) (u16) var_r27) && (var_r29 < 6)) {
                        temp_r3_4 = (Pokemon *)(heroGetStatus((Hero*)(temp_r25), 3U, (u16) var_r23));
                        if ((pokemonCheckValid((Pokemon*)(temp_r3_4)) != 0) && (fightTrainerCheckTemotiPokemonFightEntry((FIGHT_TRAINER *)((FightTrainer*)(temp_r31)), (Pokemon *)((Pokemon*)(temp_r3_4))) == NULL)) {
                            if ((fightFloorIsNowEncountVirtualBattle((FIGHT_FLOOR*)(NULL)) == 1) || (fightFloorIsNowEncountOpeningVirtualBattle((FIGHT_FLOOR*)(NULL)) == 1)) {
                                temp_r17_5 = fightEncountDataBiosGetDiskId((FightEncountData*)(fightEncountDataBiosGetPtr(fightGetFightEncountDataId())));
                                if (fightTargetIsHostSide((void*)(temp_r31), (u16) fightFloor_GetFightType((FIGHT_FLOOR*)(NULL))) == 1) {
                                    var_r4_2 = deckDataVirtualDB_GetAllyJoutai((u8)temp_r17_5, var_r23);
                                } else {
                                    var_r4_2 = deckDataVirtualDB_GetEnemyJoutai(temp_r17_5, var_r23);
                                }
                                ((Pokemon*)(temp_r3_4))->setCondition(var_r4_2);
                            }
                            temp_r17_6 = (FightPokemon *)(fightTrainer_GetFightPokemonPtr((FIGHT_TRAINER *)((u8*)((u8 *) temp_r31)), (unsigned short)((u16) var_r29)));
                            fightPokemonCreate((FightTrainer*)(temp_r31), (FightPokemon*)(temp_r17_6), (Pokemon*)(temp_r3_4), fightFloorGetFightPokemonEntryCntInc((FIGHT_FLOOR*)(NULL)));
                            if ((fightFloor_GetFightKindGetFriendFlag((FIGHT_FLOOR*)(NULL)) == 1) && (fightFloor_GetFightKindBossFlag((FIGHT_FLOOR*)(NULL)) == 1) && (fightTrainerIsGcHero((FIGHT_TRAINER *)((FightTrainer*)(temp_r31))) == 1)) {
                                fightPokemonGetFriendFormPokemonFriendFilterId((FightPokemon*)(temp_r17_6), (void*)((u8 *)3));
                            }
                            var_r29 += 1;
                        }
                        var_r23 += 1;
                        goto loop_51;
                    }
                }
            }
        }
        var_r30 += 1;
    }
    temp_r21_2 = fightSideGetDoFightTrainerCount((FIGHT_SIDE*)(temp_r3));
    var_r20 = 0;
    while ((s32) var_r20 < (s32) temp_r26) {
        temp_r3_5 = fightSideGetValidFightTrainerPtr((FIGHT_SIDE*)(temp_r3), (u16) var_r20);
        if (temp_r3_5 != NULL) {
            temp_r3_6 = (unsigned long)(fightTrainer_GetSequencePtr((FIGHT_TRAINER *)((u8*)((u8 *) temp_r3_5))));
            if (temp_r3_6 != 0) {
                fightSideGetFightTrainerGridParam((FIGHT_SIDE*)((FIGHT_SIDE *) temp_r19), (u16) temp_r21_2, (u16) var_r20, (u8*)(&sp9), (s8*)(&sp8));
                battleGridAddTrainer((NullSequence*)((NullSequence *) temp_r3_6), (u16)sp9, (u8) sp8);
                battleGridUpdate();
                Sequence_SetVisibility(temp_r3_6, 1);
                battleGridStoreModelVisibilityFlags();
            }
        }
        var_r20 += 1;
    }
    return 1;
}
}

extern "C" {

u32 fightActionFlowKaijou(FightAction* action) {
    FightEncountData* encount;
    u16 floorData;
    FIGHT_SIDE* side;
    u8 type;
    u16 encountId;
    encountId = fightGetFightEncountDataId();
    encount = fightEncountDataBiosGetPtr(encountId);
    fightFloorCreate((FIGHT_FLOOR*)fightFloorGetStatus(0, 0, 0, 0), encountId);
    fightFloorInitFightStart(0);
    type = fightFloor_GetFightType(0);
    floorData = fightEncountDataBiosGetFightFloorDataId(encount);
    side = (FIGHT_SIDE*)fightTargetGetPtr(4, 0, type);
    u16 sideData = fightFloorDB_GetFightSideDataId(floorData, 0);
    fightSideCreate(side, sideData);
    side = (FIGHT_SIDE*)fightTargetGetPtr(5, 0, type);
    fightSideCreate(side, fightFloorDB_GetFightSideDataId(floorData, 1));
    return 1;
}

u32 fightActionFlowNullFunc(FightAction* action) {
    return 1;
}

}
