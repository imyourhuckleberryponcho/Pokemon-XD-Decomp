// XD's fightFloor goes through named accessors (fightFloor_GetXxx) instead of Colosseum's
// generic fightFloorGetStatus dispatch, so this file is written from the XD asm.
// Needs extra_cflags=["-O4,s", "-inline deferred"] in configure.py. all 87 functions exact.
// Source order is reversed
// (deferred codegen); this also gives the retail .rodata order (table before "fightInput").
#include <dolphin/types.h>

#pragma dont_inline on
#pragma pool_strings off

struct FIGHT_FLOOR;
struct FightOutPokemon;
struct FightPokemon;
struct Pokemon;
struct FightJoutai;
struct FightFloorData;
struct FightAction;
struct FightWaza;
struct FightOutPokemonEnemy {
    u8 data[0xC];
};
struct HeroPtr;
struct GSthread;
struct MenuFightAction {
    u16 name[11];
    u8 nigeru;
};

class FIGHT_TRAINER {
public:
    FIGHT_TRAINER() {}
    u8 data[0x3744];
};

class FIGHT_SIDE {
public:
    u8 data[0x64];
    FIGHT_TRAINER trainers[2];
    u8 pad[4];
};

class FIGHT_FLOOR {
public:
    u8 joutai[0x10];
    u16 turnCount;
    u16 encountDataId;
    FIGHT_SIDE sides[2];
    u8 rest[0x524];
};

typedef u8 (*FightFloorLoopFunc)(void*, u8, void*);

extern "C" {
extern u8 wildPokemonDownFlag;

FIGHT_FLOOR* fightFloorBiosGetFightFloorPtr(void);
FightOutPokemon* fightFloor_GetDefensePokemonPtr(FIGHT_FLOOR*);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
void fightOutPokemon_SetFightActionFlag(FightOutPokemon*, u8);
u16 fightGetFightResultId(void);
void fightSetFightResultId(u16);
u8 fightFloor_GetFightTypeTrainerNum(FIGHT_FLOOR*);
u8 fightFloor_GetFightTypeEntryPokemonNum(FIGHT_FLOOR*);
u8 fightFloor_GetFightTypeFightoutPokemonNum(FIGHT_FLOOR*);
s32 fightFloor_GetFightType(FIGHT_FLOOR*);
s32 fightFloor_GetFightKind(FIGHT_FLOOR*);
u16 fightFloor_GetEncountDataId(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindRegulationFlag(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindNigeruFlag(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindDrawFlag(FIGHT_FLOOR*);
u8 fightFloor_GetFightKindDoBadgeCheckFlag(FIGHT_FLOOR*);
u16 fightFloor_GetFirstAttackRnd(FIGHT_FLOOR*);
FIGHT_SIDE* fightFloor_GetFightSidePtr(FIGHT_FLOOR*, u16);
FightOutPokemon* fightFloor_GetFightOutPokemonPtrAry(FIGHT_FLOOR*, u16);
FightOutPokemon** fightFloor_GetFightOutPokemonPtrAryPtr(FIGHT_FLOOR*);
void fightFloor_SetfightoutPokemonPtrAryPtr(FIGHT_FLOOR*, FightOutPokemon**);
s16 fightFloor_GetFightPokemonEntryCnt(FIGHT_FLOOR*);
void fightFloor_SetfightPokemonEntryCnt(FIGHT_FLOOR*, s16);
u8 fightFloor_GetIsJoutaiDataId(FIGHT_FLOOR*, u16);
FightJoutai* fightFloor_GetJoutaiPtr(FIGHT_FLOOR*, u16);
void fightFloor_SetTurnCount(FIGHT_FLOOR*, u16);
void fightFloor_SetEncountDataId(FIGHT_FLOOR*, u16);
void fightFloor_SetFisstAttackRnd(FIGHT_FLOOR*, u16);
void fightFloor_SetStockPokemonNum(FIGHT_FLOOR*, u8);
void fightFloor_SetStockPokemonPtr(FIGHT_FLOOR*, u8, Pokemon*);
void fightFloor_SetStockPokemonBallID(FIGHT_FLOOR*, u8, u8);
void fightFloor_SetAttackPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloor_SetDefensePokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloor_SetAttackPokemonFightWazaTargetId(FIGHT_FLOOR*, u16);
void fightFloor_SetAppointMsgPtr(FIGHT_FLOOR*, u32);
void fightFloor_SetAttackMsgId(FIGHT_FLOOR*, u32);
void fightFloor_SetCriticakMsgId(FIGHT_FLOOR*, u32);
void fightFloor_SetWazakoukaMsgId(FIGHT_FLOOR*, u32);
void fightFloor_SetAppointPokemonDataId(FIGHT_FLOOR*, u16);
void fightFloor_SetAppointPokemonWazaDataId(FIGHT_FLOOR*, u16);
void fightFloor_SetAppointItemDataId(FIGHT_FLOOR*, u16);
void fightFloor_SetAppointTokuseiDataId(FIGHT_FLOOR*, u16);
u16 fightFloor_GetFightFloorDataId(FIGHT_FLOOR*);

void* fightTargetGetPtrAsNowFightType(u8, void*);
void* fightTargetGetPtr(u8, void*, u8);
u8 fightTargetIsHostSide(FIGHT_TRAINER*, u8);
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u8);
u16 fightSideGetNokoriFightPokemonNum(FIGHT_SIDE*, u8, u8);
u32 fightSideGetFightPokemonNokoriHp(FIGHT_SIDE*, u8, u8);
u32 fightSideGetFightPokemonMaxHp(FIGHT_SIDE*, u8, u8);
u8 fightSideCheckValid(FIGHT_SIDE*);
FIGHT_TRAINER* fightSideGetValidFightTrainerPtr(FIGHT_SIDE*, u16);
FIGHT_TRAINER* fightSide_GetFightTrainerPtr(FIGHT_SIDE*, u16);
void fightSideInitAry(FIGHT_SIDE*, u16);
void fightSideRegistFightSideEnemyPokemonFightAll(FIGHT_SIDE*, FIGHT_TRAINER*, u8, u8, u8);

s32 menuCBRule_GetCommandTimeLimit(void);
s32 menuCBRule_GetBattleTimeLimit(void);

FightOutPokemon* fightTrainer_GetFightoutPokemonPtr(FIGHT_TRAINER*, u16);
FightPokemon* fightTrainer_GetFightPokemonPtr(FIGHT_TRAINER*, u16);
u8 fightTrainerCheckValid(FIGHT_TRAINER*);
u8 fightTrainerIsAllyFightTargetPtr(FIGHT_TRAINER*, void*, u16);

FightPokemon* fightTrainerGetValidFightPokemonPtr(FIGHT_TRAINER*, u16);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FIGHT_TRAINER*, u16);
u8 fightTrainerIsGcHero(FIGHT_TRAINER*);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
u16 fightTrainerDB_GetAiDataId(u16);
u8 fightTrainer_GetControllerId(FIGHT_TRAINER*);
FightPokemon* fightTrainerSearchIrekaeFightPokemon(FIGHT_TRAINER*, s16*);
HeroPtr* fightTrainer_GetHeroPtr(FIGHT_TRAINER*);

u8 fightPokemonCheckFightOut(FightPokemon*);
void fightOutPokemon_SetUsedItemDataId(FightOutPokemon*, u16);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightOutPokemonCheckValid(FightOutPokemon*);
u8 fightOutPokemonIsFightActionAttackWazaOut(FightOutPokemon*, u16, u8);
u8 fightOutPokemonIsAlly(FightOutPokemon*, FightOutPokemon*);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon*, u8);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
FightAction* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon*);
u8 fightActionCheckValid(FightAction*);
u8 fightOutPokemon_GetFightActionFlag(FightOutPokemon*);
u16* fightOutPokemonGetNicknamePtr(FightOutPokemon*);
FightOutPokemonEnemy* fightOutPokemon_GetFightOutPokemonEnemyPtr(FightOutPokemon*, u16);
u8 fightOutPokemonEnemyCheckValid(FightOutPokemonEnemy*);
FightOutPokemon* fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(FightOutPokemonEnemy*);
u16 fightOutPokemonEnemyBiosGetInitHp(FightOutPokemonEnemy*);
u16 fightOutPokemonEnemyBiosGetDamage(FightOutPokemonEnemy*);
u16 fightOutPokemonNowHpWaruValue(FightOutPokemon*, u16);
u16 fightOutPokemonMaxHpWaruValue(FightOutPokemon*, u16);
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
void fightWazaInitJoutai(FightWaza*);
void fightOutPokemonCreateFightPokemonEnemyAryEnemySideAll(FightOutPokemon*, void*);
void fightOutPokemonSetMeetEnemyFightPokemonEnemySideAll(FightOutPokemon*, void*);
s8 fightOutPokemonGetFightActionPri(FightOutPokemon*);
u32 fightOutPokemonGetNowNimbleness(FightOutPokemon*, u8, u8, u16, HeroPtr*);
u16 fightOutPokemonGetCmpNimblenessWazaDataId(FightOutPokemon*);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
s8 wazaDB_GetPri(u16);
s8 pokemonSearchWazaDataId(Pokemon*, u16);

u16 joutaiDataBiosGetStatus(u16);
void joutaiSetNowKaisuuJoutaiDataId(FightJoutai*, u16, s8);
s8 joutaiGetNowKaisuuJoutaiDataId(FightJoutai*, u16);
s8 joutaiGetKaisuuJoutaiDataId(FightJoutai*, u16);
void joutaiWriteJoutaiDataId(FightJoutai*, u16, u16);
u8 joutaiCheckWriteJoutaiDataId(FightJoutai*, u16);
u8 joutaiIsJoutaiDataId(FightJoutai*, u16);
void joutaiInitJoutaiDataId(FightJoutai*, u16);
void joutaiInitAry(FightJoutai*, u16);

void* fightEncountDataBiosGetPtr(u16);
u16 fightEncountDataBiosGetDiskId(void*);
u8 fightEncountDataBiosGetFightKind(void*);
u16 fightGetFightEncountDataId(void);
u32 fightEncountGetBgmSndDataId(u16);

void GScharCpy(u16*, u16*);
u16 HSD_Rand(void);
u32 GSfloorGetCurrentFloorGroupID(void);
GSthread* GSthreadCreate(s32, u32, u32, s32, s32, FightFloorLoopFunc);
void GSthreadSetArgs(GSthread*, s32, ...);
void GSthreadSetName(GSthread*, const char*);
void GSthreadSwitch(void);
u8 GSthreadIsRunning(GSthread*);
void GSthreadClose(GSthread*);

u8 fightFloorLoopValidFightOutPokemon(FIGHT_FLOOR*, FightFloorLoopFunc, void*, u8);
void fightFloorLoopValidFightTrainer(FIGHT_FLOOR*, FightFloorLoopFunc, void*, u8);
u8 fightFloorSetFightResultId(FIGHT_FLOOR*, u16);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(FIGHT_FLOOR*, FIGHT_TRAINER*, FightOutPokemon**, u8, u8);
u8 fightFloorIsGcHeroHostSide(FIGHT_FLOOR*);
FIGHT_TRAINER* fightFloorGetGcHeroFightTrainerPtr(FIGHT_FLOOR*);
FightOutPokemon* fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(FIGHT_FLOOR*, u16, u8, u8, FightOutPokemon*);
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(FIGHT_FLOOR*, u16, u8, FightOutPokemon*);
FIGHT_SIDE* fightFloorGetValidFightSidePtr(FIGHT_FLOOR*, u16);
u8 fightFloorSortFightOutPokemonDefault(FightOutPokemon*, FightOutPokemon*);
void fightFloorSortFightOutPokemonPtrArySub(FIGHT_FLOOR*, FightOutPokemon**, u16, u8);
u8 fightFloorCmpfightOutPokemonNimbleness(FIGHT_FLOOR*, FightOutPokemon*, FightOutPokemon*, u8);
HeroPtr* fightFloorGetFightOutPokemonPtrToHeroPtr(FIGHT_FLOOR*, FightOutPokemon*);
FIGHT_TRAINER* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(FIGHT_FLOOR*, FightOutPokemon*);
FIGHT_TRAINER* fightFloorGetFightPokemonPtrToFightTrainerPtr(FIGHT_FLOOR*, FightPokemon*);
u8 fightFloorGetNowTenkouDataId(FIGHT_FLOOR*, u8);
void fightFloorInitFightOutPokemonPtrAry(FIGHT_FLOOR*);
void fightFloorInit(FIGHT_FLOOR*);
void fightFloorInitFightTarget(FIGHT_FLOOR*);
u32 fightFloorSetStatus(FIGHT_FLOOR*, u16, u16, u16, u32);
u32 fightFloorGetStatus(FIGHT_FLOOR*, u16, u16, u16);
u8 fightFloorIsJoutaiDataId(FightJoutai*, u16);
u8 fightFloorCheckWriteJoutaiDataId(FightJoutai*, u16);
void fightFloorWriteJoutaiDataId(FightJoutai*, u16, u16);
FightOutPokemon* fightFloorGetFightOutBanmeToValidFightOutPokemon(FIGHT_FLOOR*, u16);
}

static u16 _fightFloorCreateFightOutPokemonPtrAry(FIGHT_FLOOR*, FightOutPokemon**, bool, u8, FightOutPokemon*);
static s16 _fightFloorSetFightOutPokemonPtrAry(FightOutPokemon**, FightOutPokemon*);
static void _fightFloorInitFightOutPokemonPtrAry(FightOutPokemon**);
static FightOutPokemon* _fightFloorLoopValidFightOutPokemonSub(FIGHT_FLOOR*, u16, u16, u16);
static u8 _fightFloorSetTuusinErrorFightResultSub(void*, u16, void*);
static u8 _fightFloorGetFightTrainerFightPokemonPtrArySub(void*, u16, void*);
static u8 _fightFloorGetFightTrainerFightOutPokemonPtrArySub(void*, u16, void*);
static u8 _fightFloorCheckHuuinWazaFightOutPokemonSub(void*, u16, void*);
static u8 _fightFloorGetValidFightOutPokemonCountSub(void*, u16, void*);
static u8 _fightFloorInitFightOutPokemonPtrAryFightWazaJoutaiSub(void*, u16, void*);
static u8 _fightFloorIsIrekaeFightOutPokemonSub(void*, u16, void*);
static u8 _fightFloorCheckFightOutPokemonPtrAryJoutaiDataIdSub(void*, u16, void*);
static u8 _fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub(void*, u16, void*);
static u8 _fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataIdSub(void*, u16, void*);

FIGHT_FLOOR fight_floor;

extern "C" {

u8 statusMenuCnt[4] = {0xFF, 0xFF, 0xFF, 0xFF};
u32 encount_floor_id;

}

extern "C" {

struct FightPokemonPtrAryData {
    FIGHT_TRAINER* trainer;
    s32 ally;
    s32 count;
    FightPokemon** ary;
    s32 entryNum;
    s32 fightOut;
};

}

struct FightOutPokemonPtrAryData {
    FIGHT_TRAINER* trainer;
    FightOutPokemon** ary;
    s32 count;
    s32 ally;
    s32 fightOut;
};

extern "C" {

}

extern "C" {

struct HuuinWazaData {
    FightOutPokemon* pokemon;
    s32 wazaId;
    s32 result;
};

}

extern "C" {

struct ValidCountData {
    FightOutPokemon* pokemon;
    s32 count;
    s32 mode;
    s32 fightOut;
};

}

extern "C" {

}

extern "C" {

}

struct JoutaiCountData {
    s32 joutaiId;
    s32 count;
};

extern "C" {

}

struct TokuseiFirstData {
    s32 tokuseiId;
    FightOutPokemon* result;
    s32 mode;
    FightOutPokemon* pokemon;
};

extern "C" {

}

struct TokuseiCountData {
    s32 tokuseiId;
    s32 count;
    s32 mode;
    FightOutPokemon* pokemon;
};

extern "C" {

}

extern "C" {

}

extern "C" {

}

extern "C" {
FightFloorData* fightFloorDataBiosGetPtr(u16);
void fightFloorDataBiosSetName(FightFloorData*, u32);
void fightFloorDataBiosSetFloorDataId(FightFloorData*, u16);
void fightFloorDataBiosSetFightSideDataId(FightFloorData*, u8, u16);
void fightFloorDataBiosSetTikeiDataId(FightFloorData*, u8);
void fightFloorDataBiosSetSyoukaiWzxDataId(FightFloorData*, u32);
void fightFloorDataBiosSetBgmSndId(FightFloorData*, u32);
void fightFloorDataBiosSetEnvSndId(FightFloorData*, u32);
u32 fightFloorDataBiosGetName(FightFloorData*);
u16 fightFloorDataBiosGetFloorDataId(FightFloorData*);
u16 fightFloorDataBiosGetFightSideDataId(FightFloorData*, u8);
u8 fightFloorDataBiosGetTikeiDataId(FightFloorData*);
u32 fightFloorDataBiosGetSyoukaiWzxDataId(FightFloorData*);
u32 fightFloorDataBiosGetBgmSndId(FightFloorData*);
u32 fightFloorDataBiosGetEnvSndId(FightFloorData*);

void fightFloorBiosSetTurnCount(FIGHT_FLOOR*, u16);
void fightFloorBiosSetEncountDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetAttackPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetDefensePokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetEscapePokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetIrekaePokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetKizetuPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetTuikakoukaPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetTokuseiPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetItemPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetEncountFloorId(u32);
void fightFloorBiosSetAppointPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetAppointTrainerPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetAppointWazaPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetAppointSidePtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetAppointItemPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetAppointMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAttackMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetCriticalMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetWazakoukaMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointPokemonDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetAppointWazaDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetAppointItemDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetAppointTokuseiDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetFightPokemonEntryCnt(FIGHT_FLOOR*, s16);
void fightFloorBiosSetFightOutPokemonPtrAry(FIGHT_FLOOR*, u16, void*);
void fightFloorBiosSetFightOutPokemonPtrAryPtr(FIGHT_FLOOR*, void**);
void fightFloorBiosSetFirstAttackRnd(FIGHT_FLOOR*, u16);

FightJoutai* fightFloorBiosGetJoutaiPtr(FIGHT_FLOOR*, u16);
u16 fightFloorBiosGetTurnCount(FIGHT_FLOOR*);
u16 fightFloorBiosGetEncountDataId(FIGHT_FLOOR*);
FIGHT_SIDE* fightFloorBiosGetFightSidePtr(FIGHT_FLOOR*, u16);
FightOutPokemon* fightFloorBiosGetAttackPokemonPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetDefensePokemonPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetEscapePokemonPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetIrekaePokemonPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetKizetuPokemonPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetTuikakoukaPokemonPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetTokuseiPokemonPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetItemPokemonPtr(FIGHT_FLOOR*);
u32 fightFloorBiosGetEncountFloorId(void);
void* fightFloorBiosGetAppointPokemonPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetAppointTrainerPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetAppointWazaPtr(FIGHT_FLOOR*);
void* fightFloorBiosGetAppointSidePtr(FIGHT_FLOOR*);
void* fightFloorBiosGetAppointItemPtr(FIGHT_FLOOR*);
u32 fightFloorBiosGetAppointMsgId(FIGHT_FLOOR*);
u32 fightFloorBiosGetAttackMsgId(FIGHT_FLOOR*);
u32 fightFloorBiosGetCriticalMsgId(FIGHT_FLOOR*);
u32 fightFloorBiosGetWazakoukaMsgId(FIGHT_FLOOR*);
u16 fightFloorBiosGetAppointPokemonDataId(FIGHT_FLOOR*);
u16 fightFloorBiosGetAppointWazaDataId(FIGHT_FLOOR*);
u16 fightFloorBiosGetAppointItemDataId(FIGHT_FLOOR*);
u16 fightFloorBiosGetAppointTokuseiDataId(FIGHT_FLOOR*);
s16 fightFloorBiosGetFightPokemonEntryCnt(FIGHT_FLOOR*);
void* fightFloorBiosGetFightOutPokemonPtrAry(FIGHT_FLOOR*, u16);
void** fightFloorBiosGetFightOutPokemonPtrAryPtr(FIGHT_FLOOR*);
u16 fightFloorBiosGetFirstAttackRnd(FIGHT_FLOOR*);

void fightMsgctrlSetValue(s32, u32);
void* pokemonTokuseiDataBiosGetPtr(u16);
u32 pokemonTokuseiDataBiosGetName(void*);
u32 GSmsgGetGSchar(u32);
u32 itemDB_GetName(u16);
u16 fightOutPokemonGetSoubiItemDataId(FightOutPokemon*);
void pokemonSetStatus(void*, u32, u32, u32, u32);
void fightOutPokemon_SetUseWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetMotoWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaDamageValue(FightOutPokemon*, u8);
void fightOutPokemon_SetWazaCritical(FightOutPokemon*, u8);
void fightOutPokemon_SetWazaJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaInitJoutaiDataId(FightOutPokemon*, u8);
void fightOutPokemon_SetWazaDamage(FightOutPokemon*, u32);
void fightOutPokemon_SetWazaIryoku(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaTargetId(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaHitDamage(FightOutPokemon*, u32);
u16 fightOutPokemonGetUseWazaDataId(FightOutPokemon*);
u16 fightOutPokemonGetMotoWazaDataId(FightOutPokemon*);
u8 fightOutPokemon_GetDamageValue(FightOutPokemon*);
u8 fightOutPokemon_GetCritical(FightOutPokemon*);
u8 fightOutPokemon_GetJoutaiDataId(FightOutPokemon*, u16);
u8 fightOutPokemon_GetIsHit(FightOutPokemon*);
u32 fightOutPokemon_GetDamage(FightOutPokemon*);
u16 fightOutPokemon_GetIryoku(FightOutPokemon*);
u16 fightOutPokemon_GetTargetId(FightOutPokemon*);
u32 fightOutPokemon_GetHitDamage(FightOutPokemon*);

u16 fightEncountDataBiosGetFightFloorDataId(void*);
u8 fightEncountDataBiosGetFightType(void*);
u32 fightEncountGetEnvSndDataId(u16);
u8 fightFloorDB_GetTikeiDataId(u16);
u32 fightFloorDB_GetSyoukaiWzxDataId(u16);
void* fightTypeDataBiosGetPtr(u8);
u32 fightTypeDataBiosGetName(void*);
u8 fightTypeDataBiosGetTrainerNum(void*);
u8 fightTypeDataBiosGetEntryPokemonNum(void*);
u8 fightTypeDataBiosGetFightoutPokemonNum(void*);
u16 fightTypeGetFightSideFightOutPokemonMax(u8);
void* fightKindDataBiosGetPtr(u8);
u32 fightKindDataBiosGetName(void*);
u8 fightKindDataBiosGetBackSaveDataFlag(void*);
u8 fightKindDataBiosGetDoBadgeCheckFlag(void*);
u8 fightKindDataBiosGetDoZukanMitaFlag(void*);
u8 fightKindDataBiosGetDoZukanTukamaetaFlag(void*);
u8 fightKindDataBiosGetUseItemFlag(void*);
u8 fightKindDataBiosGetCallFlag(void*);
u8 fightKindDataBiosGetNigeruFlag(void*);
u8 fightKindDataBiosGetDrawFlag(void*);
u8 fightKindDataBiosGetGetExpFlag(void*);
u8 fightKindDataBiosGetOkanePoolFlag(void*);
u8 fightKindDataBiosGetGetOkaneFlag(void*);
u8 fightKindDataBiosGetGetFriendFlag(void*);
u8 fightKindDataBiosGetGetInfectPokerusFlag(void*);
u8 fightKindDataBiosGetDoCriticalAttackFlag(void*);
u8 fightKindDataBiosGetDoHizukiAiFlag(void*);
u8 fightKindDataBiosGetDoHizukiMiyaburiFlag(void*);
u8 fightKindDataBiosGetDoItemSoubiTokukoutokubouupFlag(void*);
u8 fightKindDataBiosGetKeikentihueruFlag(void*);
u8 fightKindDataBiosGetBossFlag(void*);
u8 fightKindDataBiosGetDorobouFlag(void*);
u8 fightKindDataBiosGetMonohiroiFlag(void*);
u8 fightKindDataBiosGetDarkpokemonHypermodeFlag(void*);
u8 fightKindDataBiosGetPokemonStatusMenuSubbarFlag(void*);
u8 fightKindDataBiosGetHostEnemyMsgFlag(void*);
u8 fightKindDataBiosGetRegulationFlag(void*);

}

extern "C" {
void fightFloor_SetStatusMenuCnt(s32 status, u8 cnt);
s32 fightFloor_GetStatusMenuCnt(s32 status);
Pokemon* fightFloorGetDefPokemonPtr(FIGHT_FLOOR* floor);
void fightFloorSetTuusinErrorFightResult(FIGHT_FLOOR* floor);
void fightFloorSetTimeOutAllFightResult(FIGHT_FLOOR* floor);
u8 fightFloorIsUseFightTimerCommand(FIGHT_FLOOR* floor);
u8 fightFloorIsUseFightTimerAll(FIGHT_FLOOR* floor);
void fightFloorInitFightStart(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountOpeningVirtualBattle(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountVirtualBattle(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountHostPokemonKime(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountHostEnemyPokemonKime(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountSnatchOnly(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountTuusinTaisen(FIGHT_FLOOR* floor);
u32 fightFloorGetBgmSndDataId(FIGHT_FLOOR* floor);
void fightFloorSetMenuFightAction(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, MenuFightAction* action);
void fightFloorSetShadow(void);
u8 fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(FIGHT_FLOOR* floor, FIGHT_TRAINER* trainer, u8 ally, u8 fightOut, u16 wazaId, u8 flag);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(FIGHT_FLOOR* floor, FIGHT_TRAINER* trainer, FightPokemon** ary, u8 ally, u8 fightOut);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(FIGHT_FLOOR* floor, FIGHT_TRAINER* trainer, FightOutPokemon** ary, u8 ally, u8 fightOut);
u16 fightFloorGetFightOutPokemonPtrAry(FIGHT_FLOOR* floor, bool fightOut, u8 mode, FightOutPokemon* pokemon, FightOutPokemon** ary);
u8 fightFloorIsGcHeroWin(FIGHT_FLOOR* floor, u16 result);
u8 fightFloorIsGcHeroHostSide(FIGHT_FLOOR* floor);
u8 fightFloorCheckHuuinWazaFightOutPokemon(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, u16 wazaId);
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, FightOutPokemon** out);
u8 fightFloorIsLastActionFightOutPokemon(FIGHT_FLOOR* floor);
void fightFloorReplaceFightOutPokemonAttackToDefense(FIGHT_FLOOR* floor);
FightOutPokemon* fightFloorGetFightOutBanmeToValidFightOutPokemon(FIGHT_FLOOR* floor, u16 banme);
s32 fightFloorGetEnemyFightSideManyDamageHpRate(FIGHT_FLOOR* floor, FightOutPokemon* pokemon);
s32 fightFloorGetEnemyFightSideLittleNokoriHpRate(FIGHT_FLOOR* floor, FightOutPokemon* pokemon);
FightOutPokemon* fightFloorGetFightOutPokemonPtrRandom(FIGHT_FLOOR* floor, bool fightOut, u8 mode, FightOutPokemon* pokemon);
u16 fightFloorGetValidFightOutPokemonCount(FIGHT_FLOOR* floor, u8 mode, FightOutPokemon* pokemon, u8 fightOut);
void fightFloorInitFightOutPokemonPtrAryFightWazaJoutai(FIGHT_FLOOR* floor);
void fightFloorSetNowKaisuuJoutaiDataId(FightJoutai* joutai, u16 joutaiId, s8 kaisuu);
s8 fightFloorGetNowKaisuuJoutaiDataId(FightJoutai* joutai, u16 joutaiId);
s8 fightFloorGetKaisuuJoutaiDataId(FightJoutai* joutai, u16 joutaiId);
void fightFloorWriteJoutaiDataId(FightJoutai* joutai, u16 joutaiId, u16 value);
u8 fightFloorCheckWriteJoutaiDataId(FightJoutai* joutai, u16 joutaiId);
u8 fightFloorIsJoutaiDataId(FightJoutai* joutai, u16 joutaiId);
void fightFloorInitJoutaiDataId(FightJoutai* joutai, u16 joutaiId);
FIGHT_TRAINER* fightFloorGetGcHeroFightTrainerPtr(FIGHT_FLOOR* floor);
void fightFloorLoopValidFightTrainer(FIGHT_FLOOR* floor, FightFloorLoopFunc func, void* data, u8 thread);
void fightFloorCreateFightPokemonEnemyAryEnemySideAll(FIGHT_FLOOR* floor);
void fightFloorRegistFightTrainerEnemyPokemonFightSideAll(FIGHT_FLOOR* floor);
void fightFloorSetMeetEnemyFightPokemonEnemySideAll(FIGHT_FLOOR* floor);
u8 fightFloorIsIrekaeFightOutPokemon(FIGHT_FLOOR* floor);
u16 fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(FIGHT_FLOOR* floor, u16 joutaiId);
FightOutPokemon* fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(FIGHT_FLOOR* floor, u16 tokuseiId, u8 useAry, u8 mode, FightOutPokemon* pokemon);
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(FIGHT_FLOOR* floor, u16 tokuseiId, u8 mode, FightOutPokemon* pokemon);
u8 fightFloorLoopValidFightOutPokemon(FIGHT_FLOOR* floor, FightFloorLoopFunc func, void* data, u8 useAry);
u8 fightFloorSetFightResultId(FIGHT_FLOOR* floor, u16 resultId);
FightOutPokemon* fightFloor_GetFightOutPokemonFromDefaultSortData(u8 index);
u8 fightFloorSortFightOutPokemonDefault(FightOutPokemon* a, FightOutPokemon* b);
void fightFloorSortFightOutPokemonPtrAry(FIGHT_FLOOR* floor, u8 useAction);
void fightFloorSortFightOutPokemonPtrArySub(FIGHT_FLOOR* floor, FightOutPokemon** ary, u16 count, u8 useAction);
u8 fightFloorCmpfightOutPokemonNimbleness(FIGHT_FLOOR* floor, FightOutPokemon* a, FightOutPokemon* b, u8 useAction);
HeroPtr* fightFloorGetFightOutPokemonPtrToHeroPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon);
FIGHT_TRAINER* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon);
FIGHT_TRAINER* fightFloorGetFightPokemonPtrToFightTrainerPtr(FIGHT_FLOOR* floor, FightPokemon* pokemon);
u8 fightFloorGetNowTenkouDataId(FIGHT_FLOOR* floor, u8 checkTokusei);
u16 fightFloorCreateFightOutPokemonPtrAry(FIGHT_FLOOR* floor);
void fightFloorInitFightOutPokemonPtrAry(FIGHT_FLOOR* floor);
FIGHT_SIDE* fightFloorGetValidFightSidePtr(FIGHT_FLOOR* floor, u16 sideId);
s16 fightFloorGetFightPokemonEntryCntInc(FIGHT_FLOOR* floor);
void fightFloorCreate(FIGHT_FLOOR* floor, u16 encountId);
void fightFloorInit(FIGHT_FLOOR* floor);
void fightFloorInitFightTarget(FIGHT_FLOOR* floor);
u32 fightFloorSetStatus(FIGHT_FLOOR* floor, u16 dataId, u16 status, u16 arg, u32 value);
u32 fightFloorGetStatus(FIGHT_FLOOR* floor, u16 dataId, u16 status, u16 arg);
FIGHT_FLOOR* fightFloorGetNowPtr(void);
}

// Functions are written in reverse order: this unit is built with -inline deferred,
// which emits them in reverse source order.

static void _fightFloorInitFightOutPokemonPtrAry(FightOutPokemon** ary) {
    u16 i;

    for (i = 0; i < 8; i++) {
        ary[i] = 0;
    }
}

static s16 _fightFloorSetFightOutPokemonPtrAry(FightOutPokemon** ary, FightOutPokemon* pokemon) {
    u16 i;

    for (i = 0; i < 8; i++) {
        if (ary[i] == 0) {
            ary[i] = pokemon;
            return i;
        }
    }
    return -1;
}

static u16 _fightFloorCreateFightOutPokemonPtrAry(FIGHT_FLOOR* floor, FightOutPokemon** ary, bool fightOut, u8 mode, FightOutPokemon* pokemon) {
    FIGHT_SIDE* side;
    void* selfSide;
    u16 j;
    u16 k;
    u16 i;
    u32 trainerNum;
    u32 fightoutNum;
    u16 count;
    u8 fightType;
    FIGHT_TRAINER* trainer;
    FightOutPokemon* p;

    _fightFloorInitFightOutPokemonPtrAry(ary);
    count = 0;
    fightType = fightFloor_GetFightType(floor);
    trainerNum = fightFloor_GetFightTypeTrainerNum(floor);
    fightoutNum = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    if (mode != 0) {
        if (!fightOutPokemonCheckValid(pokemon)) {
            return 0;
        }
        selfSide = fightTargetGetPtr(2, pokemon, fightType);
    } else {
        selfSide = 0;
    }
    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(floor, i);
        if (side == 0) {
            continue;
        }
        if (mode == 1) {
            if (selfSide != side) {
                continue;
            }
        } else if (mode == 2) {
            if (selfSide == side) {
                continue;
            }
        }
        for (j = 0; j < trainerNum; j++) {
            trainer = fightSideGetValidFightTrainerPtr(side, j);
            if (trainer == 0) {
                continue;
            }
            for (k = 0; k < fightoutNum; k++) {
                p = fightTrainerGetValidFightOutPokemonPtr(trainer, k);
                if (p == 0) {
                    continue;
                }
                if (fightOut == 1 && !fightOutPokemonCheckFightOut(p)) {
                    continue;
                }
                if (mode == 3 && p == pokemon) {
                    continue;
                }
                if (_fightFloorSetFightOutPokemonPtrAry(ary, p) >= 0) {
                    count++;
                }
            }
        }
    }
    return count;
}

extern "C" {
FIGHT_FLOOR* fightFloorGetNowPtr(void) {
    return (FIGHT_FLOOR*)fightFloorGetStatus(0, 0, 0, 0);
}
}

extern "C" {
u32 fightFloorGetStatus(FIGHT_FLOOR* floor, u16 dataId, u16 status, u16 arg) {
    if (status >= 0x60) {
        return 0;
    }
    if (status == 0) {
        return (u32)fightFloorBiosGetFightFloorPtr();
    }
    if (status < 8) {
        floor = (FIGHT_FLOOR*)fightFloorDataBiosGetPtr(dataId);
        if (floor == 0) {
            return 0;
        }
    } else if (status < 0x5F) {
        if (floor == 0) {
            floor = fightFloorBiosGetFightFloorPtr();
            if (floor == 0) {
                return 0;
            }
        }
    }

    switch (status) {
    case 1:
        return fightFloorDataBiosGetName((FightFloorData*)floor);
    case 2:
        return fightFloorDataBiosGetFloorDataId((FightFloorData*)floor);
    case 3:
        return fightFloorDataBiosGetFightSideDataId((FightFloorData*)floor, arg);
    case 4:
        return fightFloorDataBiosGetTikeiDataId((FightFloorData*)floor);
    case 5:
        return fightFloorDataBiosGetSyoukaiWzxDataId((FightFloorData*)floor);
    case 6:
        return fightFloorDataBiosGetBgmSndId((FightFloorData*)floor);
    case 7:
        return fightFloorDataBiosGetEnvSndId((FightFloorData*)floor);
    case 9:
        return (u32)fightFloorBiosGetJoutaiPtr(floor, arg);
    case 0xA:
        return fightFloorIsJoutaiDataId((FightJoutai*)floor, arg);
    case 0xB:
        return fightFloorCheckWriteJoutaiDataId((FightJoutai*)floor, arg);
    case 0xC:
        return fightFloorBiosGetTurnCount(floor);
    case 0xD:
        return fightFloorBiosGetEncountDataId(floor);
    case 0xE:
        return fightEncountDataBiosGetFightFloorDataId(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
    case 0xF:
        return fightFloorDB_GetTikeiDataId(fightFloor_GetFightFloorDataId(floor));
    case 0x10:
        return fightFloorDB_GetSyoukaiWzxDataId(fightFloor_GetFightFloorDataId(floor));
    case 0x11:
        return fightFloorGetBgmSndDataId(floor);
    case 0x12:
        return fightEncountGetEnvSndDataId(fightFloor_GetEncountDataId(floor));
    case 0x13:
        return fightFloorGetNowTenkouDataId(floor, (u16)arg != 0);
    case 0x14:
        return fightEncountDataBiosGetFightType(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
    case 0x15:
        return fightTypeDataBiosGetName(fightTypeDataBiosGetPtr(fightFloor_GetFightType(floor)));
    case 0x16:
        return fightTypeDataBiosGetTrainerNum(fightTypeDataBiosGetPtr(fightFloor_GetFightType(floor)));
    case 0x17:
        return fightTypeDataBiosGetEntryPokemonNum(fightTypeDataBiosGetPtr(fightFloor_GetFightType(floor)));
    case 0x18:
        return fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(fightFloor_GetFightType(floor)));
    case 0x19:
        return fightTypeGetFightSideFightOutPokemonMax(fightFloor_GetFightType(floor));
    case 0x1A:
        return fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
    case 0x1B:
        return fightKindDataBiosGetName(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x1C:
        return fightKindDataBiosGetBackSaveDataFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x1D:
        return fightKindDataBiosGetDoBadgeCheckFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x1E:
        return fightKindDataBiosGetDoZukanMitaFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x1F:
        return fightKindDataBiosGetDoZukanTukamaetaFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x20:
        return fightKindDataBiosGetUseItemFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x21:
        return fightKindDataBiosGetCallFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x22:
        return fightKindDataBiosGetNigeruFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x23:
        return fightKindDataBiosGetDrawFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x24:
        return fightKindDataBiosGetGetExpFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x26:
        return fightKindDataBiosGetOkanePoolFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x25:
        return fightKindDataBiosGetGetOkaneFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x27:
        return fightKindDataBiosGetGetFriendFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x28:
        return fightKindDataBiosGetGetInfectPokerusFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x29:
        return fightKindDataBiosGetDoCriticalAttackFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x2A:
        return fightKindDataBiosGetDoHizukiAiFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x2B:
        return fightKindDataBiosGetDoHizukiMiyaburiFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x2C:
        return fightKindDataBiosGetDoItemSoubiTokukoutokubouupFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x2D:
        return fightKindDataBiosGetKeikentihueruFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x2E:
        return fightKindDataBiosGetBossFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x2F:
        return fightKindDataBiosGetDorobouFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x30:
        return fightKindDataBiosGetMonohiroiFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x31:
        return fightKindDataBiosGetDarkpokemonHypermodeFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x32:
        return fightKindDataBiosGetPokemonStatusMenuSubbarFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x33:
        return fightKindDataBiosGetHostEnemyMsgFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x34:
        return fightKindDataBiosGetRegulationFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
    case 0x35:
        return (u32)fightFloorBiosGetFightSidePtr(floor, arg);
    case 0x36:
        return (u32)fightFloorBiosGetAttackPokemonPtr(floor);
    case 0x37:
        return fightOutPokemonGetUseWazaDataId(fightFloorBiosGetAttackPokemonPtr(floor));
    case 0x38:
        return fightOutPokemonGetMotoWazaDataId(fightFloorBiosGetAttackPokemonPtr(floor));
    case 0x39:
        return fightOutPokemon_GetDamageValue(fightFloorBiosGetAttackPokemonPtr(floor));
    case 0x3A:
        return fightOutPokemon_GetCritical(fightFloorBiosGetAttackPokemonPtr(floor));
    case 0x3B:
        return fightOutPokemon_GetJoutaiDataId(fightFloorBiosGetAttackPokemonPtr(floor), arg);
    case 0x3D:
        return fightOutPokemon_GetIsHit(fightFloorBiosGetAttackPokemonPtr(floor));
    case 0x3E:
        return fightOutPokemon_GetDamage(fightFloorBiosGetAttackPokemonPtr(floor));
    case 0x3F:
        return fightOutPokemon_GetIryoku(fightFloorBiosGetAttackPokemonPtr(floor));
    case 0x40:
        return fightOutPokemon_GetTargetId(fightFloorBiosGetAttackPokemonPtr(floor));
    case 0x41:
        return fightOutPokemon_GetHitDamage(fightFloorBiosGetAttackPokemonPtr(floor));
    case 0x42:
        return (u32)fightFloorBiosGetDefensePokemonPtr(floor);
    case 0x44:
        return (u32)fightFloorBiosGetEscapePokemonPtr(floor);
    case 0x45:
        return (u32)fightFloorBiosGetIrekaePokemonPtr(floor);
    case 0x46:
        return (u32)fightFloorBiosGetKizetuPokemonPtr(floor);
    case 0x47:
        return (u32)fightFloorBiosGetTuikakoukaPokemonPtr(floor);
    case 0x48:
        return (u32)fightFloorBiosGetTokuseiPokemonPtr(floor);
    case 0x49:
        return (u32)fightFloorBiosGetItemPokemonPtr(floor);
    case 0x4A:
        return fightFloorBiosGetEncountFloorId();
    case 0x4B:
        return (u32)fightFloorBiosGetAppointPokemonPtr(floor);
    case 0x4C:
        return (u32)fightFloorBiosGetAppointTrainerPtr(floor);
    case 0x4D:
        return (u32)fightFloorBiosGetAppointWazaPtr(floor);
    case 0x4E:
        return (u32)fightFloorBiosGetAppointSidePtr(floor);
    case 0x4F:
        return (u32)fightFloorBiosGetAppointItemPtr(floor);
    case 0x50:
        return fightFloorBiosGetAppointMsgId(floor);
    case 0x51:
        return fightFloorBiosGetAttackMsgId(floor);
    case 0x52:
        return fightFloorBiosGetCriticalMsgId(floor);
    case 0x53:
        return fightFloorBiosGetWazakoukaMsgId(floor);
    case 0x54:
        return fightFloorBiosGetAppointPokemonDataId(floor);
    case 0x55:
        return fightFloorBiosGetAppointWazaDataId(floor);
    case 0x56:
        return fightFloorBiosGetAppointItemDataId(floor);
    case 0x57:
        return fightFloorBiosGetAppointTokuseiDataId(floor);
    case 0x58:
        return fightFloorBiosGetFightPokemonEntryCnt(floor);
    case 0x59:
        return (u32)fightFloorBiosGetFightOutPokemonPtrAry(floor, arg);
    case 0x5A:
        return (u32)fightFloorBiosGetFightOutPokemonPtrAryPtr(floor);
    case 0x5B:
        return fightFloorBiosGetFirstAttackRnd(floor);
    case 0x5C:
        return fightGetFightResultId();
    case 0x5D:
        return (u32)fightFloorGetFightOutBanmeToValidFightOutPokemon(floor, arg);
    }
    return 0;
}
}

extern "C" {
u32 fightFloorSetStatus(FIGHT_FLOOR* floor, u16 dataId, u16 status, u16 arg, u32 value) {
    u8 result = 0;
    u8 fightType = fightFloor_GetFightType(floor);

    if (status == 0 || status >= 0x60) {
        return 0;
    }
    if (status < 8) {
        floor = (FIGHT_FLOOR*)fightFloorDataBiosGetPtr(dataId);
        if (floor == 0) {
            return 0;
        }
    } else if (status < 0x5F) {
        if (floor == 0) {
            floor = fightFloorBiosGetFightFloorPtr();
            if (floor == 0) {
                return 0;
            }
        }
    }

    switch (status) {
    case 1:
        fightFloorDataBiosSetName((FightFloorData*)floor, value);
        break;
    case 2:
        fightFloorDataBiosSetFloorDataId((FightFloorData*)floor, value);
        break;
    case 3:
        fightFloorDataBiosSetFightSideDataId((FightFloorData*)floor, arg, value);
        break;
    case 4:
        fightFloorDataBiosSetTikeiDataId((FightFloorData*)floor, value);
        break;
    case 5:
        fightFloorDataBiosSetSyoukaiWzxDataId((FightFloorData*)floor, value);
        break;
    case 6:
        fightFloorDataBiosSetBgmSndId((FightFloorData*)floor, value);
        break;
    case 7:
        fightFloorDataBiosSetEnvSndId((FightFloorData*)floor, value);
        break;
    case 0xA:
        result = fightFloorCheckWriteJoutaiDataId((FightJoutai*)floor, value);
        if (result == 2) {
            fightFloorWriteJoutaiDataId((FightJoutai*)floor, value, arg);
        }
        break;
    case 0xC:
        fightFloorBiosSetTurnCount(floor, value);
        break;
    case 0xD:
        fightFloorBiosSetEncountDataId(floor, value);
        break;
    case 0x36:
        if ((FightOutPokemon*)value != 0) {
            if (fightOutPokemonCheckValid((FightOutPokemon*)value) == 1) {
                fightMsgctrlSetValue(0xF, value);
                fightMsgctrlSetValue(0x1A, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(
                                               pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId((FightOutPokemon*)value)))));
                fightMsgctrlSetValue(0x1F, value);
                fightMsgctrlSetValue(0x21, value);
                fightMsgctrlSetValue(0x20, value);
            } else {
                fightMsgctrlSetValue(0xF, 0);
                fightMsgctrlSetValue(0x1A, 0);
                fightMsgctrlSetValue(0x1F, 0);
                fightMsgctrlSetValue(0x21, 0);
                fightMsgctrlSetValue(0x20, 0);
            }
        } else {
            fightMsgctrlSetValue(0xF, 0);
            fightMsgctrlSetValue(0x1A, 0);
            fightMsgctrlSetValue(0x1F, 0);
            fightMsgctrlSetValue(0x21, 0);
            fightMsgctrlSetValue(0x20, 0);
        }
        fightFloorBiosSetAttackPokemonPtr(floor, (void*)value);
        break;
    case 0x37:
        fightOutPokemon_SetUseWazaDataId(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x38:
        fightOutPokemon_SetMotoWazaDataId(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x39:
        fightOutPokemon_SetWazaDamageValue(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x3A:
        fightOutPokemon_SetWazaCritical(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x3B:
        fightOutPokemon_SetWazaJoutaiDataId(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x3C:
        fightOutPokemon_SetWazaInitJoutaiDataId(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x3D:
        pokemonSetStatus(fightFloorBiosGetAttackPokemonPtr(floor), 0, 0xE0, 0, value);
        break;
    case 0x3E:
        fightOutPokemon_SetWazaDamage(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x3F:
        fightOutPokemon_SetWazaIryoku(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x40:
        fightOutPokemon_SetWazaTargetId(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x41:
        fightOutPokemon_SetWazaHitDamage(fightFloorBiosGetAttackPokemonPtr(floor), value);
        break;
    case 0x42:
        if ((FightOutPokemon*)value != 0) {
            if (fightOutPokemonCheckValid((FightOutPokemon*)value) == 1) {
                fightMsgctrlSetValue(0x10, value);
                fightMsgctrlSetValue(0x1B, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(
                                               pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId((FightOutPokemon*)value)))));
                fightMsgctrlSetValue(0x42, value);
                fightMsgctrlSetValue(0x44, value);
                fightMsgctrlSetValue(0x43, value);
            } else {
                fightMsgctrlSetValue(0x10, 0);
                fightMsgctrlSetValue(0x1B, 0);
                fightMsgctrlSetValue(0x42, 0);
                fightMsgctrlSetValue(0x44, 0);
                fightMsgctrlSetValue(0x43, 0);
            }
        } else {
            fightMsgctrlSetValue(0x10, 0);
            fightMsgctrlSetValue(0x1B, 0);
            fightMsgctrlSetValue(0x42, 0);
            fightMsgctrlSetValue(0x44, 0);
            fightMsgctrlSetValue(0x43, 0);
        }
        fightFloorBiosSetDefensePokemonPtr(floor, (void*)value);
        break;
    case 0x43:
        fightFloor_SetDefensePokemonPtr(floor, (FightOutPokemon*)value);
        fightFloor_SetAttackPokemonFightWazaTargetId(
            floor, fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightOutPokemon*)value, fightType));
        break;
    case 0x44:
        fightFloorBiosSetEscapePokemonPtr(floor, (void*)value);
        break;
    case 0x45:
        fightFloorBiosSetIrekaePokemonPtr(floor, (void*)value);
        break;
    case 0x46:
        fightFloorBiosSetKizetuPokemonPtr(floor, (void*)value);
        break;
    case 0x47:
        if ((FightOutPokemon*)value != 0) {
            if (fightOutPokemonCheckValid((FightOutPokemon*)value) == 1) {
                fightMsgctrlSetValue(0x12, value);
                fightMsgctrlSetValue(0x1D, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(
                                               pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId((FightOutPokemon*)value)))));
            } else {
                fightMsgctrlSetValue(0x12, 0);
                fightMsgctrlSetValue(0x1D, 0);
            }
        } else {
            fightMsgctrlSetValue(0x12, 0);
            fightMsgctrlSetValue(0x1D, 0);
        }
        fightFloorBiosSetTuikakoukaPokemonPtr(floor, (void*)value);
        break;
    case 0x48:
        fightFloorBiosSetTokuseiPokemonPtr(floor, (void*)value);
        break;
    case 0x49:
        if ((FightOutPokemon*)value != 0 && fightOutPokemonCheckValid((FightOutPokemon*)value) == 1) {
            fightFloor_SetAppointItemDataId(floor, fightOutPokemonGetSoubiItemDataId((FightOutPokemon*)value));
        }
        fightFloorBiosSetItemPokemonPtr(floor, (void*)value);
        break;
    case 0x4A:
        fightFloorBiosSetEncountFloorId(value);
        break;
    case 0x4B:
        if ((FightOutPokemon*)value != 0) {
            if (fightOutPokemonCheckValid((FightOutPokemon*)value) == 1) {
                fightMsgctrlSetValue(0x1E, value);
                fightMsgctrlSetValue(0x1C, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(
                                               pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId((FightOutPokemon*)value)))));
            } else {
                fightMsgctrlSetValue(0x1E, 0);
                fightMsgctrlSetValue(0x1C, 0);
            }
        } else {
            fightMsgctrlSetValue(0x1E, 0);
            fightMsgctrlSetValue(0x1C, 0);
        }
        fightFloorBiosSetAppointPokemonPtr(floor, (void*)value);
        break;
    case 0x4C:
        fightFloorBiosSetAppointTrainerPtr(floor, (void*)value);
        break;
    case 0x4D:
        fightFloorBiosSetAppointWazaPtr(floor, (void*)value);
        break;
    case 0x4E:
        fightFloorBiosSetAppointSidePtr(floor, (void*)value);
        break;
    case 0x4F:
        fightFloorBiosSetAppointItemPtr(floor, (void*)value);
        break;
    case 0x50:
        fightFloorBiosSetAppointMsgId(floor, value);
        break;
    case 0x51:
        fightFloorBiosSetAttackMsgId(floor, value);
        break;
    case 0x52:
        fightFloorBiosSetCriticalMsgId(floor, value);
        break;
    case 0x53:
        fightFloorBiosSetWazakoukaMsgId(floor, value);
        break;
    case 0x54:
        fightFloorBiosSetAppointPokemonDataId(floor, value);
        break;
    case 0x55:
        fightFloorBiosSetAppointWazaDataId(floor, value);
        break;
    case 0x56:
        fightMsgctrlSetValue(0x29, GSmsgGetGSchar(itemDB_GetName(value)));
        fightFloorBiosSetAppointItemDataId(floor, value);
        break;
    case 0x57:
        fightMsgctrlSetValue(0x1C, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(value))));
        fightFloorBiosSetAppointTokuseiDataId(floor, value);
        break;
    case 0x58:
        fightFloorBiosSetFightPokemonEntryCnt(floor, value);
        break;
    case 0x59:
        fightFloorBiosSetFightOutPokemonPtrAry(floor, arg, (void*)value);
        break;
    case 0x5A:
        fightFloorBiosSetFightOutPokemonPtrAryPtr(floor, (void**)value);
        break;
    case 0x5B:
        fightFloorBiosSetFirstAttackRnd(floor, value);
        break;
    case 0x5C:
        fightFloorSetFightResultId(floor, value);
        break;
    case 0x5E:
        fightMsgctrlSetValue(0x2F, value);
        break;
    }
    return result;
}
}

extern "C" {
void fightFloorInitFightTarget(FIGHT_FLOOR* floor) {
    u16 statusIds[13] = {0x36, 0x42, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F};
    u16 i;

    for (i = 0; i < 13; i++) {
        fightFloorSetStatus(floor, 0, statusIds[i], 0, 0);
    }
    fightFloor_SetAppointMsgPtr(floor, 0);
    fightFloor_SetAttackMsgId(floor, 0);
    fightFloor_SetCriticakMsgId(floor, 0);
    fightFloor_SetWazakoukaMsgId(floor, 0);
    fightFloor_SetAppointPokemonDataId(floor, 0);
    fightFloor_SetAppointPokemonWazaDataId(floor, 0);
    fightFloor_SetAppointItemDataId(floor, 0);
    fightFloor_SetAppointTokuseiDataId(floor, 0);
}
}

extern "C" {
void fightFloorInit(FIGHT_FLOOR* floor) {
    u8 i;

    joutaiInitAry(fightFloor_GetJoutaiPtr(floor, 0), 1);
    fightFloor_SetTurnCount(floor, 0);
    fightFloor_SetEncountDataId(floor, 0);
    fightSideInitAry(fightFloor_GetFightSidePtr(floor, 0), 2);
    fightFloorInitFightTarget(floor);
    fightFloor_SetfightPokemonEntryCnt(floor, 0);
    fightFloorInitFightOutPokemonPtrAry(floor);
    fightFloor_SetFisstAttackRnd(floor, 0);
    fightFloor_SetStockPokemonNum(floor, 0);
    for (i = 0; i < 6; i++) {
        fightFloor_SetStockPokemonPtr(floor, i, 0);
        fightFloor_SetStockPokemonBallID(floor, i, 0);
    }
    wildPokemonDownFlag = 0;
}
}

extern "C" {
void fightFloorCreate(FIGHT_FLOOR* floor, u16 encountId) {
    if (floor != 0) {
        fightFloorInit(floor);
        fightFloor_SetEncountDataId(floor, encountId);
        fightFloor_SetTurnCount(floor, 1);
    }
}
}

extern "C" {
s16 fightFloorGetFightPokemonEntryCntInc(FIGHT_FLOOR* floor) {
    s16 cnt = fightFloor_GetFightPokemonEntryCnt(floor);

    fightFloor_SetfightPokemonEntryCnt(floor, cnt + 1);
    return cnt;
}
}

extern "C" {
FIGHT_SIDE* fightFloorGetValidFightSidePtr(FIGHT_FLOOR* floor, u16 sideId) {
    FIGHT_SIDE* side = fightFloor_GetFightSidePtr(floor, sideId);

    if (fightSideCheckValid(side) == 0) {
        return 0;
    }
    return side;
}
}

extern "C" {
void fightFloorInitFightOutPokemonPtrAry(FIGHT_FLOOR* floor) {
    FightOutPokemon** ary = fightFloor_GetFightOutPokemonPtrAryPtr(floor);

    if (ary != 0) {
        _fightFloorInitFightOutPokemonPtrAry(ary);
    }
}
}

extern "C" {
u16 fightFloorCreateFightOutPokemonPtrAry(FIGHT_FLOOR* floor) {
    FightOutPokemon** ary;

    fightFloorInitFightOutPokemonPtrAry(floor);
    ary = fightFloor_GetFightOutPokemonPtrAryPtr(floor);
    if (ary == 0) {
        return 0;
    }
    return _fightFloorCreateFightOutPokemonPtrAry(floor, ary, 0, 0, 0);
}
}

extern "C" {
u8 fightFloorGetNowTenkouDataId(FIGHT_FLOOR* floor, u8 checkTokusei) {
    if (checkTokusei == 1) {
        if (fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(floor, 0xD, 0, 0)) {
            return 0;
        }
        if (fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(floor, 0x4D, 0, 0)) {
            return 0;
        }
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x4E) == 1) {
        return 0;
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x4F) == 1) {
        return 1;
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x50) == 1) {
        return 2;
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x51) == 1) {
        return 3;
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x52) == 1) {
        return 5;
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x53) == 1) {
        return 4;
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x54) == 1) {
        return 1;
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x55) == 1) {
        return 2;
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x56) == 1) {
        return 3;
    }
    return 0;
}
}

extern "C" {
FIGHT_TRAINER* fightFloorGetFightPokemonPtrToFightTrainerPtr(FIGHT_FLOOR* floor, FightPokemon* pokemon) {
    FIGHT_SIDE* side;
    u16 j;
    u16 k;
    u16 i;
    FIGHT_TRAINER* trainer;
    FightPokemon* p;

    for (i = 0; i < 2; i++) {
        side = fightFloor_GetFightSidePtr(floor, i);
        if (side == 0) {
            continue;
        }
        for (j = 0; j < 2; j++) {
            trainer = fightSide_GetFightTrainerPtr(side, j);
            if (trainer == 0) {
                continue;
            }
            for (k = 0; k < 6; k++) {
                p = fightTrainer_GetFightPokemonPtr(trainer, k);
                if (p != 0 && pokemon == p) {
                    return trainer;
                }
            }
        }
    }
    return 0;
}
}

extern "C" {
FIGHT_TRAINER* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    FightPokemon* moto;
    FIGHT_TRAINER* trainer;

    moto = fightOutPokemon_GetMotoFightPokemonPtr(pokemon);
    if (moto == 0) {
        return 0;
    }
    trainer = fightFloorGetFightPokemonPtrToFightTrainerPtr(floor, moto);
    if (trainer == 0) {
        return 0;
    }
    return trainer;
}
}

extern "C" {
HeroPtr* fightFloorGetFightOutPokemonPtrToHeroPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    FIGHT_TRAINER* trainer;
    HeroPtr* hero;

    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(floor, pokemon);
    if (trainer == 0) {
        return 0;
    }
    hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == 0) {
        return 0;
    }
    return hero;
}
}

extern "C" {
u8 fightFloorCmpfightOutPokemonNimbleness(FIGHT_FLOOR* floor, FightOutPokemon* a, FightOutPokemon* b, u8 useAction) {
    u8 tenkou;
    u8 badge;
    u16 rnd;
    u32 nimbleA;
    u32 nimbleB;
    u16 wazaA;
    u16 wazaB;
    s8 priA;
    s8 priB;
    HeroPtr* hero;
    u8 result;

    if (a == 0 || b == 0) {
        return 1;
    }
    tenkou = fightFloorGetNowTenkouDataId(floor, 1);
    badge = fightFloor_GetFightKindDoBadgeCheckFlag(floor);
    rnd = fightFloor_GetFirstAttackRnd(floor);
    hero = fightFloorGetFightOutPokemonPtrToHeroPtr(floor, a);
    nimbleA = fightOutPokemonGetNowNimbleness(a, badge, tenkou, rnd, hero);
    nimbleB = fightOutPokemonGetNowNimbleness(b, badge, tenkou, rnd, fightFloorGetFightOutPokemonPtrToHeroPtr(floor, b));
    if (!useAction) {
        wazaA = 0;
        wazaB = 0;
    } else {
        wazaA = fightOutPokemonGetCmpNimblenessWazaDataId(a);
        wazaB = fightOutPokemonGetCmpNimblenessWazaDataId(b);
    }
    priA = wazaDB_GetPri(wazaA);
    priB = wazaDB_GetPri(wazaB);
    if (priA != 0 || priB != 0) {
        if (priA > priB) {
            return 1;
        }
        if (priA < priB) {
            return 0;
        }
    }
    if (nimbleA > nimbleB) {
        result = 1;
    } else if (nimbleA < nimbleB) {
        result = 0;
    } else if (HSD_Rand() & 1) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
}

extern "C" {
void fightFloorSortFightOutPokemonPtrArySub(FIGHT_FLOOR* floor, FightOutPokemon** ary, u16 count, u8 useAction) {
    u16 i;
    u16 j;
    s8 priA;
    s8 priB;
    FightOutPokemon* tmp;

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (ary[i] == 0 && ary[j] == 0) {
                continue;
            }
            if (ary[i] == 0) {
                tmp = ary[i];
                ary[i] = ary[j];
                ary[j] = tmp;
                continue;
            }
            if (ary[j] == 0) {
                continue;
            }
            if (!useAction) {
                priA = 0;
                priB = 0;
            } else {
                priA = fightOutPokemonGetFightActionPri(ary[i]);
                priB = fightOutPokemonGetFightActionPri(ary[j]);
            }
            if (priA < priB) {
                continue;
            }
            if (priA > priB) {
                tmp = ary[i];
                ary[i] = ary[j];
                ary[j] = tmp;
            } else if ((priA == 2 && priB == 2) || (priA == 3 && priB == 3)) {
                if (fightFloorSortFightOutPokemonDefault(ary[i], ary[j])) {
                    tmp = ary[i];
                    ary[i] = ary[j];
                    ary[j] = tmp;
                }
            } else if (!fightFloorCmpfightOutPokemonNimbleness(floor, ary[i], ary[j], useAction)) {
                tmp = ary[i];
                ary[i] = ary[j];
                ary[j] = tmp;
            }
        }
    }
}
}

extern "C" {
void fightFloorSortFightOutPokemonPtrAry(FIGHT_FLOOR* floor, u8 useAction) {
    FightOutPokemon* ary[8];
    u16 i;

    for (i = 0; i < 8; i++) {
        ary[i] = fightFloor_GetFightOutPokemonPtrAry(floor, i);
    }
    fightFloorSortFightOutPokemonPtrArySub(floor, ary, 8, useAction);
    fightFloor_SetfightoutPokemonPtrAryPtr(floor, ary);
}
}

extern "C" {
u8 fightFloorSortFightOutPokemonDefault(FightOutPokemon* a, FightOutPokemon* b) {
    u8 targets[4] = {0xC, 0xF, 0xD, 0x10};
    u8 target;
    void* base;
    u8 i;
    u8 indexA;
    u8 indexB;

    base = fightTargetGetPtrAsNowFightType(0xB, 0);
    for (i = 0; i < 4; i++) {
        target = targets[i];
        if (a == fightTargetGetPtrAsNowFightType(target, base)) {
            indexA = i;
        }
        if (b == fightTargetGetPtrAsNowFightType(target, base)) {
            indexB = i;
        }
    }
    return indexA > indexB;
}
}

extern "C" {
FightOutPokemon* fightFloor_GetFightOutPokemonFromDefaultSortData(u8 index) {
    FightOutPokemon* ary[8];
    u16 i;
    u16 j;
    FightOutPokemon* tmp;
    s32 count = 8;

    fightTargetGetPtrAsNowFightType(0xB, 0);
    for (i = 0; i < count; i++) {
        ary[i] = fightFloor_GetFightOutPokemonPtrAry(0, i);
    }
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (ary[i] == 0 && ary[j] == 0) {
                continue;
            }
            if (ary[i] == 0) {
                tmp = ary[i];
                ary[i] = ary[j];
                ary[j] = tmp;
            } else if (ary[j] != 0 && fightFloorSortFightOutPokemonDefault(ary[i], ary[j])) {
                tmp = ary[i];
                ary[i] = ary[j];
                ary[j] = tmp;
            }
        }
    }
    return ary[index];
}
}

extern "C" {
u8 fightFloorSetFightResultId(FIGHT_FLOOR* floor, u16 resultId) {
    u16 nowId = fightGetFightResultId();
    u8 draw = fightFloor_GetFightKindDrawFlag(floor);

    if (nowId == resultId) {
        return 0;
    }
    if (nowId == 1) {
        return 1;
    }
    if (resultId == 0 || resultId == 1) {
        fightSetFightResultId(resultId);
        return 1;
    }
    if (!draw) {
        if (nowId == 3 || nowId == 5) {
            return 0;
        }
        if (resultId == 7) {
            fightSetFightResultId(3);
            return 1;
        }
        if (resultId == 6) {
            fightSetFightResultId(5);
            return 1;
        }
    } else {
        if (nowId == 7 || nowId == 6) {
            return 0;
        }
        if (nowId == 3 && resultId == 2) {
            fightSetFightResultId(7);
            return 1;
        }
        if (nowId == 2 && resultId == 3) {
            fightSetFightResultId(7);
            return 1;
        }
        if (nowId == 4 && resultId == 5) {
            fightSetFightResultId(6);
            return 1;
        }
        if (nowId == 5 && resultId == 4) {
            fightSetFightResultId(6);
            return 1;
        }
    }
    fightSetFightResultId(resultId);
    return 1;
}
}

static FightOutPokemon* _fightFloorLoopValidFightOutPokemonSub(FIGHT_FLOOR* floor, u16 sideId, u16 trainerId, u16 pokemonId) {
    FIGHT_SIDE* side;
    FIGHT_TRAINER* trainer;
    FightOutPokemon* pokemon;

    side = fightFloorGetValidFightSidePtr(floor, sideId);
    if (side == 0) {
        return 0;
    }
    trainer = fightSideGetValidFightTrainerPtr(side, trainerId);
    if (trainer == 0) {
        return 0;
    }
    pokemon = fightTrainerGetValidFightOutPokemonPtr(trainer, pokemonId);
    if (pokemon == 0) {
        return 0;
    }
    return pokemon;
}

extern "C" {
u8 fightFloorLoopValidFightOutPokemon(FIGHT_FLOOR* floor, FightFloorLoopFunc func, void* data, u8 useAry) {
    u16 j;
    u16 k;
    u16 i;
    u8 fightType;
    u32 trainerNum;
    u32 fightoutNum;
    u8 result;
    FightOutPokemon* pokemon;

    result = 1;
    fightType = fightFloor_GetFightType(floor);
    trainerNum = fightFloor_GetFightTypeTrainerNum(floor);
    fightoutNum = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    if (useAry == 1) {
        u16 n;
        FightOutPokemon* outPokemon;

        for (n = 0; n < 8; n++) {
            outPokemon = fightFloor_GetFightOutPokemonPtrAry(floor, n);
            if (outPokemon == 0) {
                continue;
            }
            if (!fightOutPokemonCheckValid(outPokemon)) {
                continue;
            }
            if (!func(outPokemon, fightType, data)) {
                result = 0;
                break;
            }
        }
    } else {
        for (k = 0; k < fightoutNum; k++) {
            for (j = 0; j < trainerNum; j++) {
                for (i = 0; i < 2; i++) {
                    pokemon = _fightFloorLoopValidFightOutPokemonSub(floor, i, j, k);
                    if (pokemon == 0) {
                        continue;
                    }
                    if (!func(pokemon, fightType, data)) {
                        result = 0;
                        goto end;
                    }
                }
            }
        }
    }
end:
    return result;
}
}

static u8 _fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataIdSub(void* pokemonPtr, u16 fightType, void* dataPtr) {
    TokuseiCountData* data = (TokuseiCountData*)dataPtr;
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;
    FightOutPokemon* self = data->pokemon;
    void* selfSide;
    void* side;

    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    if (self == 0) {
        selfSide = 0;
    } else if (data->mode == 1) {
        selfSide = fightTargetGetPtrAsNowFightType(2, self);
    } else if (data->mode == 2) {
        selfSide = fightTargetGetPtrAsNowFightType(3, self);
    } else {
        selfSide = 0;
    }
    side = fightTargetGetPtrAsNowFightType(2, pokemon);
    if ((data->mode == 1 || data->mode == 2) && selfSide == 0) {
        return 1;
    }
    if (data->mode == 0) {
        if (self != 0 && self == pokemon) {
            return 1;
        }
    } else if (data->mode == 1 || data->mode == 2) {
        if (selfSide != side) {
            return 1;
        }
    } else {
        return 1;
    }
    if ((u16)data->tokuseiId == fightOutPokemonGetTokuseiDataId(pokemon)) {
        data->count++;
    }
    return 1;
}

extern "C" {
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(FIGHT_FLOOR* floor, u16 tokuseiId, u8 mode, FightOutPokemon* pokemon) {
    TokuseiCountData data;

    data.tokuseiId = tokuseiId;
    data.count = 0;
    data.mode = mode;
    data.pokemon = pokemon;
    fightFloorLoopValidFightOutPokemon(floor, (FightFloorLoopFunc)_fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataIdSub, &data, 0);
    return data.count;
}
}

static u8 _fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub(void* pokemonPtr, u16 fightType, void* dataPtr) {
    TokuseiFirstData* data = (TokuseiFirstData*)dataPtr;
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;
    FightOutPokemon* self = data->pokemon;
    void* selfSide;
    void* side;

    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    if (self == 0) {
        selfSide = 0;
    } else if (data->mode == 1) {
        selfSide = fightTargetGetPtrAsNowFightType(2, self);
    } else if (data->mode == 2) {
        selfSide = fightTargetGetPtrAsNowFightType(3, self);
    } else {
        selfSide = 0;
    }
    side = fightTargetGetPtrAsNowFightType(2, pokemon);
    if ((data->mode == 1 || data->mode == 2) && selfSide == 0) {
        return 1;
    }
    if (data->mode == 0) {
        if (self != 0 && self == pokemon) {
            return 1;
        }
    } else if (data->mode == 1 || data->mode == 2) {
        if (selfSide != side) {
            return 1;
        }
    } else {
        return 1;
    }
    if ((u16)data->tokuseiId == fightOutPokemonGetTokuseiDataId(pokemon)) {
        data->result = pokemon;
        return 0;
    }
    return 1;
}

extern "C" {
FightOutPokemon* fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(FIGHT_FLOOR* floor, u16 tokuseiId, u8 useAry, u8 mode, FightOutPokemon* pokemon) {
    TokuseiFirstData data;

    data.tokuseiId = tokuseiId;
    data.result = 0;
    data.mode = mode;
    data.pokemon = pokemon;
    fightFloorLoopValidFightOutPokemon(floor, (FightFloorLoopFunc)_fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub, &data, useAry);
    return data.result;
}
}

static u8 _fightFloorCheckFightOutPokemonPtrAryJoutaiDataIdSub(void* pokemonPtr, u16 fightType, void* dataPtr) {
    JoutaiCountData* data = (JoutaiCountData*)dataPtr;
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;

    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, data->joutaiId) == 1) {
        data->count++;
    }
    return 1;
}

extern "C" {
u16 fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(FIGHT_FLOOR* floor, u16 joutaiId) {
    JoutaiCountData data;

    data.joutaiId = joutaiId;
    data.count = 0;
    fightFloorLoopValidFightOutPokemon(floor, (FightFloorLoopFunc)_fightFloorCheckFightOutPokemonPtrAryJoutaiDataIdSub, &data, 0);
    return data.count;
}
}

static u8 _fightFloorIsIrekaeFightOutPokemonSub(void* trainerPtr, u16 fightType, void* dataPtr) {
    FIGHT_TRAINER* trainer = (FIGHT_TRAINER*)trainerPtr;
    u8* irekae = (u8*)dataPtr;
    s16 index;
    u16 i;
    u32 fightoutNum;
    FightOutPokemon* pokemon;

    if (!fightTrainerCheckValid(trainer)) {
        return 1;
    }
    index = 0;
    if (fightTrainerSearchIrekaeFightPokemon(trainer, &index) == 0) {
        return 1;
    }
    fightoutNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    for (i = 0; i < fightoutNum; i++) {
        pokemon = fightTrainer_GetFightoutPokemonPtr(trainer, i);
        if (pokemon != 0 && !fightOutPokemonCheckFightOut(pokemon) && irekae != 0 && *irekae != 2) {
            if (fightTrainerIsGcHero(trainer) == 1) {
                *irekae = 2;
            } else {
                *irekae = 1;
            }
        }
    }
    return 1;
}

extern "C" {
u8 fightFloorIsIrekaeFightOutPokemon(FIGHT_FLOOR* floor) {
    u8 irekae = 0;

    fightFloorLoopValidFightTrainer(floor, (FightFloorLoopFunc)_fightFloorIsIrekaeFightOutPokemonSub, &irekae, 0);
    return irekae;
}
}

extern "C" {
void fightFloorSetMeetEnemyFightPokemonEnemySideAll(FIGHT_FLOOR* floor) {
    FIGHT_SIDE* side;
    u16 j;
    u16 k;
    u16 i;
    u8 fightType;
    u32 trainerNum;
    u32 fightoutNum;
    FIGHT_TRAINER* trainer;
    FightOutPokemon* pokemon;
    void* target;

    fightType = fightFloor_GetFightType(floor);
    trainerNum = fightFloor_GetFightTypeTrainerNum(floor);
    fightoutNum = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(floor, i);
        if (side == 0) {
            continue;
        }
        for (j = 0; j < trainerNum; j++) {
            trainer = fightSideGetValidFightTrainerPtr(side, j);
            if (trainer == 0) {
                continue;
            }
            for (k = 0; k < fightoutNum; k++) {
                pokemon = fightTrainerGetValidFightOutPokemonPtr(trainer, k);
                if (pokemon != 0 && fightOutPokemonCheckFightOut(pokemon)) {
                    target = fightTargetGetPtr(3, pokemon, fightType);
                    fightOutPokemonSetMeetEnemyFightPokemonEnemySideAll(pokemon, target);
                }
            }
        }
    }
}
}

extern "C" {
void fightFloorRegistFightTrainerEnemyPokemonFightSideAll(FIGHT_FLOOR* floor) {
    FIGHT_SIDE* side;
    u16 j;
    u16 i;
    u8 fightType;
    u32 trainerNum;
    u32 fightoutNum;
    FIGHT_TRAINER* trainer;

    fightType = fightFloor_GetFightType(floor);
    trainerNum = fightFloor_GetFightTypeTrainerNum(floor);
    fightoutNum = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(floor, i);
        if (side == 0) {
            continue;
        }
        for (j = 0; j < trainerNum; j++) {
            trainer = fightSideGetValidFightTrainerPtr(side, j);
            if (trainer != 0) {
                fightSideRegistFightSideEnemyPokemonFightAll((FIGHT_SIDE*)fightTargetGetPtr(3, trainer, fightType), trainer,
                                                             fightType, trainerNum, fightoutNum);
            }
        }
    }
}
}

extern "C" {
void fightFloorCreateFightPokemonEnemyAryEnemySideAll(FIGHT_FLOOR* floor) {
    FIGHT_SIDE* side;
    u16 j;
    u16 k;
    u16 i;
    u8 fightType;
    u32 trainerNum;
    u32 fightoutNum;
    FIGHT_TRAINER* trainer;
    FightOutPokemon* pokemon;
    void* target;

    fightType = fightFloor_GetFightType(floor);
    trainerNum = fightFloor_GetFightTypeTrainerNum(floor);
    fightoutNum = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(floor, i);
        if (side == 0) {
            continue;
        }
        for (j = 0; j < trainerNum; j++) {
            trainer = fightSideGetValidFightTrainerPtr(side, j);
            if (trainer == 0) {
                continue;
            }
            for (k = 0; k < fightoutNum; k++) {
                pokemon = fightTrainerGetValidFightOutPokemonPtr(trainer, k);
                if (pokemon != 0 && fightOutPokemonCheckFightOut(pokemon)) {
                    target = fightTargetGetPtr(3, pokemon, fightType);
                    fightOutPokemonCreateFightPokemonEnemyAryEnemySideAll(pokemon, target);
                }
            }
        }
    }
}
}

extern "C" {
void fightFloorLoopValidFightTrainer(FIGHT_FLOOR* floor, FightFloorLoopFunc func, void* data, u8 thread) {
    FIGHT_SIDE* side;
    u16 j;
    u16 i;
    GSthread* threads[4];
    u16 count;
    u16 aiId;
    u32 trainerNum;
    FIGHT_TRAINER* trainer;
    u8 fightType;

    fightType = fightFloor_GetFightType(0);
    trainerNum = fightFloor_GetFightTypeTrainerNum(0);
    for (i = 0; i < 4; i++) {
        threads[i] = 0;
    }
    if (thread == 1) {
        count = 0;
        for (i = 0; i < 2; i++) {
            side = fightFloorGetValidFightSidePtr(floor, i);
            if (side == 0) {
                continue;
            }
            for (j = 0; j < trainerNum; j++) {
                trainer = fightSideGetValidFightTrainerPtr(side, j);
                if (trainer == 0) {
                    continue;
                }
                aiId = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
                fightTrainer_GetControllerId(trainer);
                if (aiId == 0 && count < 4) {
                    threads[count] = GSthreadCreate(0x12, GSfloorGetCurrentFloorGroupID(), 0x2000, 1, 0, func);
                    if (threads != 0) {
                        GSthreadSetArgs(threads[count], 3, trainer, fightType, data);
                        GSthreadSetName(threads[count], "fightInput");
                        count++;
                    }
                }
            }
        }
        do {
            GSthreadSwitch();
            if (fightGetFightResultId() == 4 || fightGetFightResultId() == 5) {
                return;
            }
            for (i = 0; i < 4; i++) {
                if (threads[i] != 0 && GSthreadIsRunning(threads[i]) == 1) {
                    break;
                }
            }
        } while (i < 4);
        for (i = 0; i < 4; i++) {
            if (threads[i] != 0) {
                GSthreadClose(threads[i]);
                threads[i] = 0;
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            side = fightFloorGetValidFightSidePtr(floor, i);
            if (side == 0) {
                continue;
            }
            for (j = 0; j < trainerNum; j++) {
                trainer = fightSideGetValidFightTrainerPtr(side, j);
                if (trainer == 0) {
                    continue;
                }
                aiId = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
                fightTrainer_GetControllerId(trainer);
                if (aiId == 0) {
                    func(trainer, fightType, data);
                }
            }
        }
    }
    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(floor, i);
        if (side == 0) {
            continue;
        }
        for (j = 0; j < trainerNum; j++) {
            trainer = fightSideGetValidFightTrainerPtr(side, j);
            if (trainer == 0) {
                continue;
            }
            aiId = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
            fightTrainer_GetControllerId(trainer);
            if (aiId != 0) {
                func(trainer, fightType, data);
            }
        }
    }
}
}

extern "C" {
FIGHT_TRAINER* fightFloorGetGcHeroFightTrainerPtr(FIGHT_FLOOR* floor) {
    FIGHT_SIDE* side;
    u16 j;
    u16 i;
    u32 trainerNum;
    FIGHT_TRAINER* trainer;

    fightFloor_GetFightType(floor);
    trainerNum = fightFloor_GetFightTypeTrainerNum(floor);
    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(floor, i);
        if (side == 0) {
            continue;
        }
        for (j = 0; j < trainerNum; j++) {
            trainer = fightSideGetValidFightTrainerPtr(side, j);
            if (trainer != 0 && fightTrainerIsGcHero(trainer) == 1) {
                return trainer;
            }
        }
    }
    return 0;
}
}

extern "C" {
void fightFloorInitJoutaiDataId(FightJoutai* joutai, u16 joutaiId) {
    if (joutaiDataBiosGetStatus(joutaiId) == 9) {
        joutaiInitJoutaiDataId(joutai, joutaiId);
    }
}
}

extern "C" {
u8 fightFloorIsJoutaiDataId(FightJoutai* joutai, u16 joutaiId) {
    if (joutaiDataBiosGetStatus(joutaiId) != 9) {
        return 0;
    }
    return joutaiIsJoutaiDataId(joutai, joutaiId);
}
}

extern "C" {
u8 fightFloorCheckWriteJoutaiDataId(FightJoutai* joutai, u16 joutaiId) {
    if (joutaiDataBiosGetStatus(joutaiId) != 9) {
        return 0;
    }
    return joutaiCheckWriteJoutaiDataId(joutai, joutaiId);
}
}

extern "C" {
void fightFloorWriteJoutaiDataId(FightJoutai* joutai, u16 joutaiId, u16 value) {
    if (joutaiDataBiosGetStatus(joutaiId) == 9) {
        joutaiWriteJoutaiDataId(joutai, joutaiId, value);
    }
}
}

extern "C" {
s8 fightFloorGetKaisuuJoutaiDataId(FightJoutai* joutai, u16 joutaiId) {
    if (joutaiDataBiosGetStatus(joutaiId) != 9) {
        return -1;
    }
    return joutaiGetKaisuuJoutaiDataId(joutai, joutaiId);
}
}

extern "C" {
s8 fightFloorGetNowKaisuuJoutaiDataId(FightJoutai* joutai, u16 joutaiId) {
    if (joutaiDataBiosGetStatus(joutaiId) != 9) {
        return -1;
    }
    return joutaiGetNowKaisuuJoutaiDataId(joutai, joutaiId);
}
}

extern "C" {
void fightFloorSetNowKaisuuJoutaiDataId(FightJoutai* joutai, u16 joutaiId, s8 kaisuu) {
    if (joutaiDataBiosGetStatus(joutaiId) == 9) {
        joutaiSetNowKaisuuJoutaiDataId(joutai, joutaiId, kaisuu);
    }
}
}

static u8 _fightFloorInitFightOutPokemonPtrAryFightWazaJoutaiSub(void* pokemon, u16 fightType, void* data) {
    fightWazaInitJoutai(fightOutPokemon_GetFightWazaPtr((FightOutPokemon*)pokemon));
    return 1;
}

extern "C" {
void fightFloorInitFightOutPokemonPtrAryFightWazaJoutai(FIGHT_FLOOR* floor) {
    fightFloorLoopValidFightOutPokemon(floor, (FightFloorLoopFunc)_fightFloorInitFightOutPokemonPtrAryFightWazaJoutaiSub, 0, 0);
}
}

static u8 _fightFloorGetValidFightOutPokemonCountSub(void* pokemonPtr, u16 fightType, void* dataPtr) {
    ValidCountData* data = (ValidCountData*)dataPtr;
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;
    FightOutPokemon* self = data->pokemon;
    void* selfSide;
    void* side;

    if ((bool)data->fightOut == 1 && !fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    if (self == 0) {
        selfSide = 0;
    } else if (data->mode == 1) {
        selfSide = fightTargetGetPtrAsNowFightType(2, self);
    } else if (data->mode == 2) {
        selfSide = fightTargetGetPtrAsNowFightType(3, self);
    } else {
        selfSide = 0;
    }
    side = fightTargetGetPtrAsNowFightType(2, pokemon);
    if ((data->mode == 1 || data->mode == 2) && selfSide == 0) {
        return 1;
    }
    if (data->mode == 0) {
        if (self != 0 && self == pokemon) {
            return 1;
        }
    } else if (data->mode == 1 || data->mode == 2) {
        if (selfSide != side) {
            return 1;
        }
    } else {
        return 1;
    }
    data->count++;
    return 1;
}

extern "C" {
u16 fightFloorGetValidFightOutPokemonCount(FIGHT_FLOOR* floor, u8 mode, FightOutPokemon* pokemon, u8 fightOut) {
    ValidCountData data;

    data.pokemon = pokemon;
    data.count = 0;
    data.mode = mode;
    data.fightOut = fightOut;
    fightFloorLoopValidFightOutPokemon(floor, (FightFloorLoopFunc)_fightFloorGetValidFightOutPokemonCountSub, &data, 0);
    return data.count;
}
}

extern "C" {
FightOutPokemon* fightFloorGetFightOutPokemonPtrRandom(FIGHT_FLOOR* floor, bool fightOut, u8 mode, FightOutPokemon* pokemon) {
    FightOutPokemon* ary[8];
    u16 count;
    u16 index;

    _fightFloorInitFightOutPokemonPtrAry(ary);
    count = _fightFloorCreateFightOutPokemonPtrAry(floor, ary, fightOut, mode, pokemon);
    if (count == 0) {
        return 0;
    }
    index = HSD_Rand() % count;
    if (index >= 8) {
        return 0;
    }
    if (ary[index] == 0) {
        return 0;
    }
    return ary[index];
}
}

extern "C" {
s32 fightFloorGetEnemyFightSideLittleNokoriHpRate(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    FightOutPokemon* ary[8];
    u16 count;
    u16 i;
    FightOutPokemon* target;
    u16 nowHp;
    u16 maxHp;
    s32 rate;
    s32 minRate;

    if (pokemon == 0) {
        return -1;
    }
    _fightFloorInitFightOutPokemonPtrAry(ary);
    count = _fightFloorCreateFightOutPokemonPtrAry(floor, ary, 1, 2, pokemon);
    if (count == 0) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        target = ary[i];
        if (target != 0) {
            nowHp = fightOutPokemonNowHpWaruValue(target, 1);
            maxHp = fightOutPokemonMaxHpWaruValue(target, 1);
            if (maxHp == 0) {
                maxHp = 1;
            }
            minRate = nowHp * 100 / maxHp;
            break;
        }
    }
    for (i = 0; i < count; i++) {
        target = ary[i];
        if (target != 0) {
            nowHp = fightOutPokemonNowHpWaruValue(target, 1);
            maxHp = fightOutPokemonMaxHpWaruValue(target, 1);
            if (maxHp == 0) {
                maxHp = 1;
            }
            rate = nowHp * 100 / maxHp;
            if (rate < minRate) {
                minRate = rate;
            }
        }
    }
    return minRate;
}
}

extern "C" {
s32 fightFloorGetEnemyFightSideManyDamageHpRate(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    FightOutPokemonEnemy* enemyAry;
    s32 maxRate;
    FightOutPokemonEnemy* enemy;
    u16 i;
    u16 initHp;
    u16 damage;
    s32 rate;
    FightOutPokemon* target;

    if (pokemon == 0) {
        return -1;
    }
    enemyAry = fightOutPokemon_GetFightOutPokemonEnemyPtr(pokemon, 0);
    maxRate = -1;
    for (i = 0; i < 4; i++) {
        enemy = &enemyAry[i];
        if (!fightOutPokemonEnemyCheckValid(enemy)) {
            continue;
        }
        target = fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(enemy);
        if (target == 0) {
            continue;
        }
        if (!fightOutPokemonCheckValid(target)) {
            continue;
        }
        initHp = fightOutPokemonEnemyBiosGetInitHp(enemy);
        damage = fightOutPokemonEnemyBiosGetDamage(enemy);
        if (initHp == 0) {
            initHp = 1;
        }
        rate = damage * 100 / initHp;
        if (rate > maxRate) {
            maxRate = rate;
        }
    }
    return maxRate;
}
}

extern "C" {
FightOutPokemon* fightFloorGetFightOutBanmeToValidFightOutPokemon(FIGHT_FLOOR* floor, u16 banme) {
    u16 j;
    u16 k;
    u16 i;
    u32 trainerNum;
    u32 fightoutNum;
    u16 count;
    FightOutPokemon* pokemon;

    fightFloor_GetFightType(floor);
    trainerNum = fightFloor_GetFightTypeTrainerNum(floor);
    fightoutNum = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    count = 0;
    for (k = 0; k < fightoutNum; k++) {
        for (j = 0; j < trainerNum; j++) {
            for (i = 0; i < 2; i++) {
                pokemon = _fightFloorLoopValidFightOutPokemonSub(floor, i, j, k);
                if (pokemon != 0 && count == banme) {
                    return pokemon;
                }
                count++;
            }
        }
    }
    return 0;
}
}

extern "C" {
void fightFloorReplaceFightOutPokemonAttackToDefense(FIGHT_FLOOR* floor) {
    FightOutPokemon* attack = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, floor);
    FightOutPokemon* defense = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, floor);

    fightFloor_SetAttackPokemonPtr(floor, defense);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(floor, attack);
}
}

extern "C" {
u8 fightFloorIsLastActionFightOutPokemon(FIGHT_FLOOR* floor) {
    FightOutPokemon* pokemon;
    u16 i;
    u8 last;
    FightAction* action;

    last = 1;

    for (i = 0; i < 8; i++) {
        pokemon = fightFloor_GetFightOutPokemonPtrAry(floor, i);
        if (pokemon == 0) {
            continue;
        }
        if (!fightOutPokemonCheckFightOut(pokemon)) {
            continue;
        }
        action = fightOutPokemon_GetFightActionBuffPtr(pokemon);
        if (action == 0) {
            continue;
        }
        if (!fightActionCheckValid(action)) {
            continue;
        }
        if (!fightOutPokemon_GetFightActionFlag(pokemon)) {
            last = 0;
            break;
        }
    }
    return last;
}
}

extern "C" {
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, FightOutPokemon** out) {
    FightOutPokemon* kagefumi;
    FightOutPokemon* arijigoku;
    FightOutPokemon* jiryoku;
    u8 flying;
    u8 steel;

    flying = 0;
    steel = 0;
    if (!fightOutPokemonCheckValid(pokemon)) {
        return 0;
    }
    kagefumi = fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(floor, 0x17, 0, 2, pokemon);
    arijigoku = fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(floor, 0x47, 0, 2, pokemon);
    jiryoku = fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(floor, 0x2A, 0, 0, pokemon);
    if (fightOutPokemonIsZokuseiDataId(pokemon, 2) == 1 || fightOutPokemonGetTokuseiDataId(pokemon) == 0x1A) {
        flying = 1;
    }
    if (fightOutPokemonIsZokuseiDataId(pokemon, 8) == 1) {
        steel = 1;
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x16) == 1 || fightOutPokemonIsJoutaiDataId(pokemon, 0xE) == 1 ||
        fightOutPokemonIsJoutaiDataId(pokemon, 0x25) == 1) {
        return 1;
    }
    if (kagefumi != 0) {
        if (out != 0) {
            *out = kagefumi;
        }
        return 2;
    }
    if (arijigoku != 0 && !flying) {
        if (out != 0) {
            *out = arijigoku;
        }
        return 2;
    }
    if (jiryoku != 0 && steel == 1) {
        if (out != 0) {
            *out = jiryoku;
        }
        return 2;
    }
    return 0;
}
}

static u8 _fightFloorCheckHuuinWazaFightOutPokemonSub(void* pokemonPtr, u16 fightType, void* dataPtr) {
    HuuinWazaData* data = (HuuinWazaData*)dataPtr;
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;
    FightOutPokemon* self = data->pokemon;
    u16 wazaId = data->wazaId;

    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    if (!fightOutPokemonIsAlly(pokemon, self) && fightOutPokemonIsJoutaiDataId(pokemon, 0x27) == 1 &&
        pokemonSearchWazaDataId(fightOutPokemonGetPokemonPtr(pokemon), wazaId) >= 0) {
        data->result = 1;
        return 0;
    }
    return 1;
}

extern "C" {
u8 fightFloorCheckHuuinWazaFightOutPokemon(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, u16 wazaId) {
    HuuinWazaData data;

    data.pokemon = pokemon;
    data.wazaId = wazaId;
    data.result = 0;
    fightFloorLoopValidFightOutPokemon(floor, (FightFloorLoopFunc)_fightFloorCheckHuuinWazaFightOutPokemonSub, &data, 0);
    return data.result != 0;
}
}

extern "C" {
u8 fightFloorIsGcHeroHostSide(FIGHT_FLOOR* floor) {
    u8 fightType = fightFloor_GetFightType(floor);
    FIGHT_TRAINER* trainer = fightFloorGetGcHeroFightTrainerPtr(floor);

    if (trainer != 0 && fightTargetIsHostSide(trainer, fightType) == 1) {
        return 1;
    }
    return 0;
}
}

extern "C" {
u8 fightFloorIsGcHeroWin(FIGHT_FLOOR* floor, u16 result) {
    if (result == 2 || result == 3) {
        if (fightFloorIsGcHeroHostSide(floor) == 1) {
            if (result == 2) {
                return 1;
            }
        } else {
            if (result == 3) {
                return 1;
            }
        }
    }
    return 0;
}
}

extern "C" {
u16 fightFloorGetFightOutPokemonPtrAry(FIGHT_FLOOR* floor, bool fightOut, u8 mode, FightOutPokemon* pokemon, FightOutPokemon** ary) {
    _fightFloorInitFightOutPokemonPtrAry(ary);
    return _fightFloorCreateFightOutPokemonPtrAry(floor, ary, fightOut, mode, pokemon);
}
}

static u8 _fightFloorGetFightTrainerFightOutPokemonPtrArySub(void* pokemonPtr, u16 fightType, void* dataPtr) {
    FightOutPokemonPtrAryData* data = (FightOutPokemonPtrAryData*)dataPtr;
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;
    FIGHT_TRAINER* trainer = data->trainer;
    FightOutPokemon** ary = data->ary;

    if (data->fightOut == 1 && !fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    if (data->ally == 0) {
        if (fightTrainerIsAllyFightTargetPtr(trainer, pokemon, fightType) == 1) {
            return 1;
        }
    } else {
        if (fightTrainerIsAllyFightTargetPtr(trainer, pokemon, fightType) == 0) {
            return 1;
        }
    }
    ary[data->count] = pokemon;
    data->count++;
    return 1;
}

extern "C" {
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(FIGHT_FLOOR* floor, FIGHT_TRAINER* trainer, FightOutPokemon** ary, u8 ally, u8 fightOut) {
    FightOutPokemonPtrAryData data;

    _fightFloorInitFightOutPokemonPtrAry(ary);
    data.trainer = trainer;
    data.ary = ary;
    data.count = 0;
    data.ally = ally;
    data.fightOut = fightOut;
    fightFloorLoopValidFightOutPokemon(floor, (FightFloorLoopFunc)_fightFloorGetFightTrainerFightOutPokemonPtrArySub, &data, 0);
    return data.count;
}
}

static u8 _fightFloorGetFightTrainerFightPokemonPtrArySub(void* trainerPtr, u16 fightType, void* dataPtr) {
    FightPokemonPtrAryData* data = (FightPokemonPtrAryData*)dataPtr;
    FIGHT_TRAINER* trainer = (FIGHT_TRAINER*)trainerPtr;
    FIGHT_TRAINER* target = data->trainer;
    FightPokemon** ary = data->ary;
    u16 i;
    u16 num;
    FightPokemon* pokemon;

    if (!fightTrainerCheckValid(trainer)) {
        return 1;
    }
    if (data->ally == 0) {
        if (fightTrainerIsAllyFightTargetPtr(trainer, target, fightType) == 1) {
            return 1;
        }
    } else {
        if (fightTrainerIsAllyFightTargetPtr(trainer, target, fightType) == 0) {
            return 1;
        }
    }
    num = data->entryNum;
    for (i = 0; i < num; i++) {
        pokemon = fightTrainerGetValidFightPokemonPtr(trainer, i);
        if (pokemon != 0 && (data->fightOut != 1 || fightPokemonCheckFightOut(pokemon))) {
            ary[data->count] = pokemon;
            data->count++;
        }
    }
    return 1;
}

extern "C" {
u16 fightFloorGetFightTrainerFightPokemonPtrAry(FIGHT_FLOOR* floor, FIGHT_TRAINER* trainer, FightPokemon** ary, u8 ally, u8 fightOut) {
    FightPokemonPtrAryData data;
    u16 i;

    for (i = 0; i < 0x18; i++) {
        ary[i] = 0;
    }
    data.trainer = trainer;
    data.ally = ally;
    data.count = 0;
    data.ary = ary;
    data.entryNum = fightFloor_GetFightTypeEntryPokemonNum(0);
    data.fightOut = fightOut;
    fightFloorLoopValidFightTrainer(floor, (FightFloorLoopFunc)_fightFloorGetFightTrainerFightPokemonPtrArySub, &data, 0);
    return data.count;
}
}

extern "C" {
u8 fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(FIGHT_FLOOR* floor, FIGHT_TRAINER* trainer, u8 ally, u8 fightOut, u16 wazaId, u8 flag) {
    FightOutPokemon* ary[8];
    u16 i;
    u16 count;

    count = fightFloorGetFightTrainerFightOutPokemonPtrAry(floor, trainer, ary, ally, fightOut);
    for (i = 0; i < count; i++) {
        if (fightOutPokemonIsFightActionAttackWazaOut(ary[i], wazaId, flag) == 1) {
            return 1;
        }
    }
    return 0;
}
}

extern "C" {
void fightFloorSetShadow(void) {
}
}

extern "C" {
void fightFloorSetMenuFightAction(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, MenuFightAction* action) {
    GScharCpy(action->name, fightOutPokemonGetNicknamePtr(pokemon));
    if (fightFloor_GetFightKindNigeruFlag(floor) == 1) {
        action->nigeru = 0;
    } else {
        action->nigeru = 1;
    }
}
}

extern "C" {
u32 fightFloorGetBgmSndDataId(FIGHT_FLOOR* floor) {
    return fightEncountGetBgmSndDataId(fightFloor_GetEncountDataId(floor));
}
}

extern "C" {
u8 fightFloorIsNowEncountTuusinTaisen(FIGHT_FLOOR* floor) {
    return (u8)fightFloor_GetFightKind(floor) == 0xB;
}
}

extern "C" {
u8 fightFloorIsNowEncountSnatchOnly(FIGHT_FLOOR* floor) {
    return fightFloor_GetEncountDataId(floor) == 0xE0;
}
}

extern "C" {
u8 fightFloorIsNowEncountHostEnemyPokemonKime(FIGHT_FLOOR* floor) {
    u16 encountId = fightFloor_GetEncountDataId(floor);

    switch (fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(encountId))) {
    case 0xC:
    case 0xD:
        return 1;
    }
    if (encountId == 0xD9) {
        return 1;
    }
    return encountId == 0x191;
}
}

extern "C" {
u8 fightFloorIsNowEncountHostPokemonKime(FIGHT_FLOOR* floor) {
    fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor));
    return 0;
}
}

extern "C" {
u8 fightFloorIsNowEncountVirtualBattle(FIGHT_FLOOR* floor) {
    u8 kind = fightFloor_GetFightKind(floor);
    u16 diskId = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightGetFightEncountDataId()));

    if ((kind == 0xF || kind == 0xE) && diskId != 0) {
        return 1;
    }
    return 0;
}
}

extern "C" {
u8 fightFloorIsNowEncountOpeningVirtualBattle(FIGHT_FLOOR* floor) {
    u8 kind = fightFloor_GetFightKind(floor);
    u16 diskId = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightGetFightEncountDataId()));

    if (kind == 0xF && diskId == 0) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void fightFloorInitFightStart(FIGHT_FLOOR* floor) {
    FIGHT_SIDE* side;
    FIGHT_TRAINER* trainer;
    u16 j;
    u16 k;
    u16 i;
    FightOutPokemon* pokemon;

    for (i = 0; i < 2; i++) {
        side = fightFloor_GetFightSidePtr(floor, i);
        if (side == 0) {
            continue;
        }
        for (j = 0; j < 2; j++) {
            trainer = fightSide_GetFightTrainerPtr(side, j);
            if (trainer == 0) {
                continue;
            }
            for (k = 0; k < 2; k++) {
                pokemon = fightTrainer_GetFightoutPokemonPtr(trainer, k);
                if (pokemon != 0) {
                    fightOutPokemon_SetUsedItemDataId(pokemon, 0);
                }
            }
        }
    }
}
}

extern "C" {
u8 fightFloorIsUseFightTimerAll(FIGHT_FLOOR* floor) {
    u8 regulation = fightFloor_GetFightKindRegulationFlag(floor);
    s32 limit = menuCBRule_GetBattleTimeLimit();

    if (regulation == 1 && limit > 0) {
        return 1;
    }
    return 0;
}
}

extern "C" {
u8 fightFloorIsUseFightTimerCommand(FIGHT_FLOOR* floor) {
    u8 regulation = fightFloor_GetFightKindRegulationFlag(floor);
    s32 limit = menuCBRule_GetCommandTimeLimit();

    if (regulation == 1 && limit > 0) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void fightFloorSetTimeOutAllFightResult(FIGHT_FLOOR* floor) {
    u16 nokori2;
    u32 hp2;
    FIGHT_SIDE* side2;
    u32 rate2;
    u32 rate1;
    u32 hp1;
    u16 nokori1;
    u32 trainerNum;
    FIGHT_SIDE* side1;
    u32 entryNum;

    if (fightGetFightResultId() == 1) {
        return;
    }
    trainerNum = fightFloor_GetFightTypeTrainerNum(floor);
    entryNum = fightFloor_GetFightTypeEntryPokemonNum(floor);

    side1 = (FIGHT_SIDE*)fightTargetGetPtrAsNowFightType(4, 0);
    nokori1 = fightSideGetNokoriFightPokemonNum(side1, trainerNum, entryNum);
    hp1 = fightSideGetFightPokemonNokoriHp(side1, trainerNum, entryNum);
    rate1 = hp1 * 100 / fightSideGetFightPokemonMaxHp(side1, trainerNum, entryNum);

    side2 = (FIGHT_SIDE*)fightTargetGetPtrAsNowFightType(5, 0);
    nokori2 = fightSideGetNokoriFightPokemonNum(side2, trainerNum, entryNum);
    hp2 = fightSideGetFightPokemonNokoriHp(side2, trainerNum, entryNum);
    rate2 = hp2 * 100 / fightSideGetFightPokemonMaxHp(side2, trainerNum, entryNum);

    fightFloorSetFightResultId(floor, 0);
    if (nokori1 > nokori2) {
        fightFloorSetFightResultId(floor, 2);
    }
    if (nokori1 < nokori2) {
        fightFloorSetFightResultId(floor, 3);
    }
    if (fightGetFightResultId() == 0) {
        if (rate1 >= rate2) {
            fightFloorSetFightResultId(floor, 2);
        }
        if (rate1 <= rate2) {
            fightFloorSetFightResultId(floor, 3);
        }
    }
}
}

static u8 _fightFloorSetTuusinErrorFightResultSub(void* pokemon, u16 fightType, void* data) {
    fightOutPokemon_SetFightActionFlag((FightOutPokemon*)pokemon, 1);
    return 1;
}

extern "C" {
void fightFloorSetTuusinErrorFightResult(FIGHT_FLOOR* floor) {
    fightFloorLoopValidFightOutPokemon(floor, (FightFloorLoopFunc)_fightFloorSetTuusinErrorFightResultSub, 0, 0);
    fightFloorSetFightResultId(floor, 1);
}
}

extern "C" {
Pokemon* fightFloorGetDefPokemonPtr(FIGHT_FLOOR* floor) {
    FightOutPokemon* defense;

    if (floor == 0) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == 0) {
            return 0;
        }
    }
    defense = fightFloor_GetDefensePokemonPtr(floor);
    if (defense == 0) {
        return 0;
    }
    return fightOutPokemonGetPokemonPtr(defense);
}
}

extern "C" {
s32 fightFloor_GetStatusMenuCnt(s32 status) {
    s32 cnt = -1;
    switch (status) {
    case 0x37:
        cnt = statusMenuCnt[0];
        break;
    case 0x38:
        cnt = statusMenuCnt[1];
        break;
    case 0x40:
        cnt = statusMenuCnt[2];
        break;
    case 0x41:
        cnt = statusMenuCnt[3];
        break;
    }
    return cnt;
}
}

extern "C" {
void fightFloor_SetStatusMenuCnt(s32 status, u8 cnt) {
    switch (status) {
    case 0x37:
        statusMenuCnt[0] = cnt;
        break;
    case 0x38:
        statusMenuCnt[1] = cnt;
        break;
    case 0x40:
        statusMenuCnt[2] = cnt;
        break;
    case 0x41:
        statusMenuCnt[3] = cnt;
        break;
    }
}
}

#pragma dont_inline reset
