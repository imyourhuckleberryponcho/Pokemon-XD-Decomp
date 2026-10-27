#include <dolphin/types.h>

#pragma optimize_for_size on
#pragma pool_strings off

struct FightOutPokemon;

#pragma pack(push, 1)
struct WsCheckTypeCmd {
    u8 opcode;
    u8 side;
    u8 type;
    void* jump;
};
struct WsSideCondCmd {
    u8 opcode;
    u8 side;
    u16 id;
    void* jump;
};
struct WsWazaKoukaCmd {
    u8 opcode;
    u8 side;
    u32 id;
    u8 expect;
    void* jump;
};
struct WsArg32Cmd {
    u8 opcode;
    u32 arg;
};
struct WsArg16Cmd {
    u8 opcode;
    u16 arg;
};
struct WsBit8Cmd {
    u8 opcode;
    u8* addr;
    u8 value;
};
struct WsBit16Cmd {
    u8 opcode;
    u16* addr;
    u16 value;
};
struct WsBit32Cmd {
    u8 opcode;
    u32* addr;
    u32 value;
};
struct WsSetWorkCmd {
    u8 opcode;
    u8* dst;
    u8* src;
    u8 count;
};
struct WsSetWorkOfsCmd {
    u8 opcode;
    u8* dst;
    u8* table;
    u8* ofs;
    u8 count;
};
struct WsConditionCmd {
    u8 opcode;
    u8 side;
    u32 kind;
    void* jump;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct WsIf8Cmd { u8 opcode; u8 kind; u8* addr; u8 value; void* jump; };
struct WsIf16Cmd { u8 opcode; u8 kind; u16* addr; u16 value; void* jump; };
struct WsIf32Cmd { u8 opcode; u8 kind; u32* addr; u32 value; void* jump; };
struct WsIfwCmd { u8 opcode; u8* a; u8* b; u8 count; void* jump; };
struct WsMonsCmd { u8 opcode; u8 side; u8 type; void* jump; };
struct WsSpeabiHaveCmd { u8 opcode; u8 side; void* jump; };
struct WsSpeabiCmd { u8 opcode; u8 side; u8 tokusei; void* jump; };
struct WsSideCmd { u8 opcode; u8 side; };
struct WsFightEffectCmd { u8 opcode; u8 side; u8 effect; u16* arg; };
struct WsFightEffect2Cmd { u8 opcode; u8 side; u8* effect; u16* arg; };
struct WsLoopCmd { u8 opcode; void* jump; };
struct WsZenmetuCheckCmd { u8 opcode; u32 flag; };
#pragma pack(pop)
extern u8 fight_seq_server_work3_temp;
extern u16 TSUIKATbl[];
extern "C" {
u8 menuCBRule_ProhibitionSuicide(void);
void fightSeqFightEffect(u8 side, u8 effect, u16 arg);
u8 menuCBRule_EnableSbToSleep(void);
u8 menuCBRule_EnableSbToIceed(void);
u8 menuCBRule_EnableSkillSwap(void);
u8 menuCBRule_EnableSkill_Michidure(void);
u8 menuCBRule_EnableSkill_SonicBoom(void);
void fightSeqWazaSeqSet(u8 arg, s32 flag);
u8 fightSeqMichidureCheckAct(void);
u8 fightSeqFightOutPokemonTokuseiCheckWazaHit(FightOutPokemon* a, FightOutPokemon* d, s32 f);
u8 fightSeqIsGuard(FightOutPokemon* p, u16 waza);
u16 fightSeqRegulationGetJoutaiCount(u16 id, u32 arg);
}
struct WsFightEffCmd { u8 opcode; u8 side; u8 effect; void* arg; };
extern "C" {
u8 wazaSequenceSysLastWazaIsImpactPoint(u32 id);
extern u8 WAZA_Wait[];
extern u8 WAZA_MigawariKizetsu[];
}
#pragma pack(push, 1)
struct WsCondChgCmd { u8 opcode; u8 side; u8 kind; u8 type; u8 value; void* jump; };
#pragma pack(pop)
extern "C" {
extern u8 WAZA_Yokodori[];
extern u8 lbl_804EB918;
void fightSeqPressurePpdecCheck(FightOutPokemon* attacker, FightOutPokemon* target, u32 msg);
}
struct YokodoriData { FightOutPokemon* attacker; FightOutPokemon* found; };
static void fightSeqWsBadgeCheckYokodori(FightOutPokemon* p);
static s32 _fightSeqWsBadgecheckSubYokodori(void* p, u16 idx, void* data);
extern "C" {
void fightMainDebugMenu(void);
void fightMainAllCamera(u32 a, u32 b);
extern u8 WAZA_MineReshuffleStart[];

}
static s32 _fightSeqZenmetuCheckSubFightTrainer(void* p, u16 idx, void* data);
static s32 _fightSeqZenmetuCheckSubFightOutPokemon(void* p, u16 idx, void* data);
struct ModelSequence { void DoModelAnimation(int); };
static void _fightSeqTuikaActSub(u8 a, u8 b, u8* out);
extern "C" {
u8 fightSeqWazaFloorJoutaiCheck(void* side, FightOutPokemon* target, u16 waza);
void figthSeqZokuseiCheckCalc(void* waza, u16 type, u16 wazaId, u8 apply);
}

extern "C" {

struct Sequence;
struct WazaSequence;
Sequence* fightOutPokemon_GetSequencePtr(FightOutPokemon* fop);
WazaSequence* Sequence_LoadWaza(Sequence* seq, u16 id, u16 kind, u8 flag);
void WazaSequence_Start(WazaSequence* waza, s32 flag);
u8 WazaSequence_IsActive(WazaSequence* waza);
void WazaSequence_Free(WazaSequence* waza);
void GSthreadSwitch(void);
void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon* fop, u8 type, s32 flag);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(s32 menuId, FightOutPokemon* fop, u8 type, s32 a, s32 b);
void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon* fop, u8 type, s32 flag);
s32 fightFloor_GetFightType(void* floor);

extern u8 ActionSeqNo;

void* fightSeq_GetWazaSeq(void);
void fightSeq_NextWazaSeq(s32 size);
void fightSeq_JumpWazaSeq(void* target);
void fightSeqTuikaAct(u8, u8);
void fightSeqLoopInitAct(void* waza);
void WS_CONDITION_CHECK(void);
void fightSeqDamageLoss(u8, u8);
void fightSeqTypeCheck(u8, u8, u8, u8, u8);
void fightWazaInitLoop(void* waza);
void fightWaza_SetKaisuu(void* waza, u8 value);
void fightMenuCloseMsg(void);
u32 fightFloor_GetAppointMsgId(void* floor);
extern u32 ServerStatusFlag;
extern u8* UserWork;
extern u8 ServerWork[8];
void fightSeq_CallWazaSeq(void* seq);
void fightSeqOpenMsg(u32 msg);
void fightMainWaitFrame(u32 frames);
FightOutPokemon* fightTargetGetPtrAsNowFightType(u32, u32);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u32);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon*, u32);
u8 fightOutPokemonIsJoutaiNormal(FightOutPokemon*);
u8 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon*);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightSideIsJoutaiDataId(void*, u32);
s32 fightOutPokemonGetJoutaiMigawariHp(FightOutPokemon*);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon*, u32);

u32 HSD_Rand(void);
u32 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
u32 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon*);
void* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
u16 fightOutPokemon_GetUseWazaDataId(FightOutPokemon*);
u32 figthOutPokemonGetPokemonDataId(FightOutPokemon*);
u16 wazaDB_GetSeqId(u16);
extern s32 fight_waza_critical_data_number;
u8 fightFloor_GetFightKindDoCriticalAttackFlag(u32);
void* fightWazaCriticalDataBiosGetPtr(u32);
u8 fightWazaCriticalDataBiosGetBunbo(void*);
void fightWaza_SetCritical(void*, u32);

char* GSmsgGetGSchar(u32 msg);
void GSprint(s32 layer, s32 x, s32 y, s32 color, const char* fmt, ...);
u8 GSsndPlayVolume(u32 id, s32 time, u8 vol, u32 flag);
void* Sequence_GetWaza(void* sequence, u16 wzxID, u32 kind);
u8 dbgMenuFightGetTuikakoukaFlag(void);
s32 dbgMenuGetLayerID(void);
s32 fightAbicntFitMinMax(s32 value);
void fightAi_AddStoreWaza(FightOutPokemon* a, void* t, u16 waza);
void fightAi_DereteExpectWaza(FightOutPokemon* a, void* t, u16 waza);
void* fightFloorBiosGetFightFloorPtr(void);
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(void* floor, u16 tokuseiId, u8 mode, FightOutPokemon* pokemon);
u16 fightFloorGetFightOutPokemonPtrAry(void* floor, bool fightOut, u8 mode, FightOutPokemon* pokemon, FightOutPokemon** ary);
FightOutPokemon* fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(void* floor, u16 tokuseiId, u8 useAry, u8 mode, FightOutPokemon* pokemon);
FightOutPokemon* fightFloorGetFightOutPokemonPtrRandom(void* floor, bool fightOut, u8 mode, FightOutPokemon* pokemon);
void* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void* floor, FightOutPokemon* pokemon);
void* fightFloorGetFightOutPokemonPtrToHeroPtr(void* floor, FightOutPokemon* pokemon);
u8 fightFloorGetNowTenkouDataId(void* floor, u8 checkTokusei);
u32 fightFloorGetStatus(void* floor, u16 dataId, u16 status, u16 arg);
u16 fightFloorGetValidFightOutPokemonCount(void* floor, u8 mode, FightOutPokemon* pokemon, u8 fightOut);
u8 fightFloorIsIrekaeFightOutPokemon(void* floor);
u8 fightFloorIsNowEncountOpeningVirtualBattle(void* floor);
u8 fightFloorIsUseFightTimerCommand(void* floor);
u8 fightFloorLoopValidFightOutPokemon(void* floor, void* func, void* data, u8 useAry);
void fightFloorLoopValidFightTrainer(void* floor, void* func, void* data, u8 thread);
u8 fightFloorSetFightResultId(void* floor, u16 resultId);
void fightFloorSetTuusinErrorFightResult(void* floor);
FightOutPokemon* fightFloor_GetAppointPokemonPtr(void* floor);
u32 fightFloor_GetEnvSndId(void* floor);
s32 fightFloor_GetFightKind(void* floor);
u8 fightFloor_GetFightKindGetExpFlag(void* floor);
u8 fightFloor_GetFightKindGetFriendFlag(void* floor);
u8 fightFloor_GetFightKindKeikentihueruFlag(void* floor);
u8 fightFloor_GetFightKindRegulationFlag(void* floor);
u16 fightFloor_GetFightSideFightOutPokemonSideMax(void* floor);
u8 fightFloor_GetFightTypeEntryPokemonNum(void* floor);
u8 fightFloor_GetFightTypeFightoutPokemonNum(void* floor);
u8 fightFloor_GetFightTypeTrainerNum(void* floor);
void fightFloor_SetAppointItemDataId(void* floor, u16 id);
void fightFloor_SetAppointPokemonPtr(void* floor, FightOutPokemon* pokemon);
void fightFloor_SetAttackPokemonFightWazaJoutaiDataId(void* floor, u16 id);
void fightFloor_SetCriticakMsgId(void* floor, u32 value);
void fightFloor_SetIrekaePokemonPtr(void* floor, FightOutPokemon* value);
void fightFloor_SetItemPokemonPtr(void* floor, FightOutPokemon* pokemon);
void fightFloor_SetKizetuPokemonPtr(void* floor, FightOutPokemon* value);
void fightFloor_SetTokuseiPokemonPtr(void* floor, FightOutPokemon* value);
void fightFloor_SetWazakoukaMsgId(void* floor, u32 value);
u16 fightGetFightResultId(void);
void fightMenuAllFightOutPokemonCloseStatusMenu(u8 wait);
void fightMenuAllFightTrainerCloseStatusMenu(u8 wait);
void fightMenuCloseInfoMenu(u8 wait);
void fightMenuFightOutPokemonRenewStatusMenu(FightOutPokemon* p, u16 id, bool flag);
void fightMenuFightStatusStartAnimHP(u32 menu, s32 hp);
u32 fightMenuGetFightOutPokemonPtrToStatusMenuId(FightOutPokemon* p, u16 id, bool flag);
u32 fightMenuOpenMsg(u32 msg);
u8 fightMenuWazaKoukaMsg(u32 msg, u32 value, u16 item);
u8 fightMenuWazaOutMsg(u32 value, u16 waza);
void fightMsgctrlSetValue(s32 id, u32 value);
void fightOutPokemonAddFightOutPokemonEnemyDamage(FightOutPokemon* fop, FightOutPokemon* target, s32 damage);
u8 fightOutPokemonCheckMeetEnemyFightPokemon(FightOutPokemon* fop, void* fp);
bool fightOutPokemonCheckValid(FightOutPokemon* fop);
u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonCreate(FightOutPokemon* fop, void* fp, void* seq);
u16 fightOutPokemonDoItemSoubi(FightOutPokemon* fop, u16 item, u8 mode, u8 update);
void fightOutPokemonFreeAllSequenceWaza(FightOutPokemon* fop);
s32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
void* fightOutPokemonGetNicknamePtr(FightOutPokemon* fop);
void* fightOutPokemonGetPokemonPtr(FightOutPokemon* fop);
u16 fightOutPokemonGetSoubiItemDataId(FightOutPokemon* fop);
u16 fightOutPokemonGetUseWazaDataId(FightOutPokemon* fop);
u16 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon* fop, u16 id);
u8 fightOutPokemonGetWazaZokuseiDataId(FightOutPokemon* fop);
u16 fightOutPokemonGetZokuseiDataId(FightOutPokemon* fop, u8 idx);
void fightOutPokemonInit(FightOutPokemon* fop);
void fightOutPokemonInitJoutaiKeep(FightOutPokemon* fop);
u8 fightOutPokemonIsAlly(FightOutPokemon* fop, FightOutPokemon* other);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon* fop);
u8 fightOutPokemonIsHinsi(FightOutPokemon* fop);
u16 fightOutPokemonIsJoutaiKie(FightOutPokemon* fop);
u8 fightOutPokemonIsUseHensinBuff(FightOutPokemon* fop);
void fightOutPokemonKizetuEffect(FightOutPokemon* fop, u8 mode);
void fightOutPokemonSetBuffJoutaiDataId(FightOutPokemon* fop, u16 id, s32 value);
void fightOutPokemonSetHensinStatusAfterLevelUp(FightOutPokemon* fop);
void fightOutPokemonSetJoutaiMigawariHp(FightOutPokemon* fop, s32 hp);
void fightOutPokemonSetWazaEffectDownFlag(FightOutPokemon* fop, u8 flag);
void fightOutPokemonWriteJoutaiDataId(FightOutPokemon* fop, u16 id, u32 value);
u8 fightOutPokemon_GetAbicntAverage(FightOutPokemon* fop);
u8 fightOutPokemon_GetAbicntAvoid(FightOutPokemon* fop);
void* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon* fop);
s16 fightOutPokemon_GetGamanDamageValue(FightOutPokemon* fop);
s16 fightOutPokemon_GetIrekaeTargetEntryId(FightOutPokemon* fop);
u8 fightOutPokemon_GetIrekaetaFlag(FightOutPokemon* fop);
u8 fightOutPokemon_GetItemKoraetaFlag(FightOutPokemon* fop);
u32 fightOutPokemon_GetKaigaraDamageValue(FightOutPokemon* fop);
u8 fightOutPokemon_GetKizetuFlag(FightOutPokemon* fop);
void* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon* fop);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon* fop);
u8 fightOutPokemon_GetNoPressureFlag(FightOutPokemon* fop);
u8 fightOutPokemon_GetReceivesWazaHiraishinFlag(FightOutPokemon* fop);
u16 fightOutPokemon_GetStockItemDataId(FightOutPokemon* fop);
void fightOutPokemon_SetDamageAtkTargetId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetDamageAtkValue(FightOutPokemon* fop, s16 value);
void fightOutPokemon_SetDamageSpeTargetId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetDamageSpeValue(FightOutPokemon* fop, s16 value);
void fightOutPokemon_SetGamanDamageTargetId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetGamanDamageValue(FightOutPokemon* fop, s16 value);
void fightOutPokemon_SetHitWazaDataId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetHitWazaZokuseiDataId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetIrekaeTargetEntryId(FightOutPokemon* fop, s16 value);
void fightOutPokemon_SetIrekaetaFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetItemKoraetaFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetKaigaraDamageValue(FightOutPokemon* fop, u32 value);
void fightOutPokemon_SetKizetuFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetMyselfDamageAtkTargetId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetMyselfDamageAtkValue(FightOutPokemon* fop, s16 value);
void fightOutPokemon_SetMyselfDamageSpeTargetId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetMyselfDamageSpeValue(FightOutPokemon* fop, s16 value);
void fightOutPokemon_SetOutWazaKoukanaiFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetPassPpdecFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetReceivesWazaHiraishinFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetStockItemDataId(FightOutPokemon* fop, u16 value);
bool fightPokemonCheckFightOut(void* fp);
void fightPokemonGetEffortFromPokemon(void* fp, void* from, u8 mode);
void fightPokemonGetFriendFormPokemonFriendFilterId(void* fp, void* out);
u32 fightPokemonGetLevelToExp(void* fp, u8 level);
void* fightPokemonGetNicknamePtr(void* fp);
void* fightPokemonGetPokemonPtr(void* fp);
u16 fightPokemonGetSoubiItemSoubiDataId(void* fp);
void fightPokemonGrowBasisStatus(void* fp, u8 level);
void fightPokemonInit(void* fp);
u8 fightPokemonIsJoutaiDataId(void* fp, u16 id);
void fightPokemonToMenuLvupStatus(void* fp, void* lvup);
s16 fightPokemon_GetEntryId(void* fp);
u8 fightPokemon_GetHokakuFlag(void* fp);
void* fightPokemon_GetMotoPokemonPtr(void* fp);
void* fightPokemon_GetPokemonBuffPtr(void* fp);
void fightPokemon_SetLevelUpFlag(void* fp, u8 value);
void fightSeqCheckSetHensinBuffToMotoFightPokemon(FightOutPokemon* p, u16 id);
void fightSeqCheckSetHensinBuffToMotoPokemon(FightOutPokemon* p, u16 id);
void fightSeqCheckSetHensinBuffToMotoPokemon2(FightOutPokemon* p, u16 a, s32 b, u8 c);
s32 fightSeqCondChgActTypeToPokemonStatusId(u8 type);
u8 fightSeqFightOutPokemonTokuseiCheckWazaHitBefore(FightOutPokemon* atk, FightOutPokemon* def);
u8 fightSeqIsTenkouHit(u16);
void fightSeqKizetuInit(FightOutPokemon* p);
u8 fightSeqRegulationCheck(u32 param2, u32 param1, u32 param3);
u8 fightSeqRegulationOverTwoCheck(u16 type, u32 elem);
u8 fightSeqRegulationZenmetuCheck(u16 param2);
u8 fightSeqTameWazaCheck(u32 id);
s32 fightSeqWazaDamageCalc(FightOutPokemon*, FightOutPokemon*, FightOutPokemon*, u16, u16, u16);
void* fightSeq_GetWazaSeqPtr_u8(u8 idx);
bool fightSideCheckValid(void* side);
u32 fightSideGetFightPokemonNokoriHp(void* side, u16 trainerNum, u16 pokemonNum);
u16 fightSideGetJoutaiUserFightTargetId(void* side, u16 id);
u32 fightSideGetNokoriFightPokemonNum(void* side, u16 trainerNum, u16 pokemonNum);
void* fightSideGetValidFightTrainerPtr(void* side, u16 idx);
void* fightSide_GetFightTrainerPtr(void* side, u16 index);
void fightSide_SetMakibisiCheckFlag(void* side, u8 flag);
void* fightTargetGetPtr(u16 slotType, void* ptr, u8 type);
void* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u16 slotType, u16 type);
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(void* target, u16 type);
bool fightTimerCommandBlock(void);
void fightTimerCommandInit(void);
void fightTimerCommandStart(void);
void fightTimerCommandTerminate(void);
u8 fightTrainerAiDB_GetParamStoreFlag(u16 id);
u8 fightTrainerCheckCanGetExp(void* trainer);
FightOutPokemon* fightTrainerCheckFightPokemonFightOut(void* trainer, void* fp);
void* fightTrainerCheckTemotiPokemonFightEntry(void* trainer, void* pokemon);
bool fightTrainerCheckValid(void* trainer);
u16 fightTrainerDB_GetAiDataId(u16 id);
void* fightTrainerGetEntryIdToFightPokemonPtr(void* trainer, s16 entryId);
s16 fightTrainerGetFightOutPokemonToTemotiBanme(void* trainer, FightOutPokemon* fo);
void* fightTrainerGetValidFightPokemonPtr(void* trainer, u16 index);
u8 fightTrainerIsGcHero(void* trainer);
u8 fightTrainerIsMineFightPokemon(void* trainer, void* fp);
void* fightTrainerSearchIrekaeFightPokemon(void* trainer, u16* index);
s16 fightTrainerSelectIrekaeFightPokemon(void* trainer, u32 a, u32 b, u32 c);
void* fightTrainer_GetFightPokemonPtr(u8* t, u16 i);
u16 fightTrainer_GetFightTrainerDataId(u8* t);
void* fightTrainer_GetFightoutPokemonPtr(u8* t, u16 i);
void* fightTrainer_GetHeroPtr(u8* t);
u32 fightTrainer_GetSequencePtr(u8* t);
void fightWazaBiosCopy(void* dst, void* src);
u8 fightWazaCheckWriteJoutaiDataId(void* waza, u16 id);
u32 fightWazaDoEffectFunc(u32 wazaID, u32 a, u32 b, u32 c);
u8 fightWazaHitKakurituDataBiosGetKake(void* data);
void* fightWazaHitKakurituDataBiosGetPtr(u16 id);
u8 fightWazaHitKakurituDataBiosGetWaru(void* data);
void fightWazaInitJoutai(void* waza);
void fightWazaInitJoutaiDataId(void* waza, u16 id);
bool fightWazaIsHit(void* waza);
u8 fightWazaIsJoutaiDataId(void* waza, u16 id);
u8 fightWazaIsJoutaiSousai(void* waza);
u8 fightWazaIsMix(void* waza);
void fightWazaWriteJoutaiDataId(void* waza, u16 id, u32 value);
void fightWazaWzxTypeFuncMigawari(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u32 a, u32 b);
u8 fightWaza_GetCritical(void* waza);
s32 fightWaza_GetDamage(void* waza);
u8 fightWaza_GetDamageValue(void* waza);
s32 fightWaza_GetHitDamage(void* waza);
u16 fightWaza_GetIryoku(void* waza);
u8 fightWaza_GetKaisuu(void* waza);
u16 fightWaza_GetUseWazaDataId(void* waza);
u8 fightWaza_GetWazaBanme(void* waza);
u16 fightWaza_GetZokusei(void* waza);
void fightWaza_SetDamage(void* waza, s32 value);
void fightWaza_SetHitDamage(void* waza, s32 value);
void fightWaza_SetMotoWazaDataId(void* waza, u16 value);
u8 figthOutPokemonGetLevel(FightOutPokemon* fop);
s32 figthOutPokemonGetSoubiItemBuff(FightOutPokemon* fop);
u32 figthPokemonGetExp(void* fp);
u8 figthPokemonGetLevel(void* fp);
void figthPokemonSetExp(void* fp, u32 exp);
void fn_8014718C(FightOutPokemon* fop, u8 value);
u8 fn_80148688(FightOutPokemon* fop);
u32 heroGetStatus(void* hero, u32 selector, u16 index);
void menuFightStatusStartAnimEXP(s32 id, u32 exp);
s32 menuFightStatusWaitAnimeEXP(s32 id, u8 wait);
s32 menuFightStatusWaitAnimeHP(s32 id, u8 wait);
bool menuIsCheck(s32 menuID);
u8 pokemonCheckInfectPokerus(void* pokemon, u8 checkCured);
u16 pokemonDB_GetGiveExp(u16 id);
u8 pokemonDB_GetTokuseiDataId(u16 id, u16 idx);
u8 pokemonDB_GetZokuseiDataId(u16 id, u16 idx);
u8 pokemonGetDarkPokemonLevel(void* pokemon);
u32 pokemonGetStatus(void* ptr, u16 pokemonDataId, u32 kind, u16 index);
void pokemonInit(void* pokemon);
u8 pokemonIsDarkPokemon(void* pokemon);
s8 pokemonSearchWazaDataId(void* pokemon, u16 waza);
u16 pokemon_GetHp(void* poke);
u16 pokemon_GetMaxHp(void* poke);
u16 pokemon_GetPokemonDataId(void* poke);
u16 pokemon_GetPokemonWazaDataId(void* poke, u32 wazaNum);
u8 pokemon_GetPokemonWazaPp(void* poke, u32 wazaNum);
u32 pokemon_GetPoolExp(void* poke);
u8 pokemon_GetSeikaku(void* poke);
u8 pokemon_GetTokuseiFlag(void* poke);
void pokemon_SetHp(void* poke, u16 data);
void pokemon_SetPokemonWazaPp(void* poke, u32 wazaNum, u8 data);
void pokemon_SetPoolExp(void* poke, u32 data);
void soundContinueBGMEX(u32 bgm, u32 time, s32);
u32 soundPauseBGMEX(u32 time, s32);
u8 wazaCheckDarkWaza(u16 wazaID);
u8 wazaDB_GetAddFightKoukaAvg(u16 id);
u8 wazaDB_GetAvg(u16 id);
s16 wazaDB_GetIryoku(u16 id);
u8 wazaDB_GetMajikku(u16 id);
u8 wazaDB_GetMamoru(u16 id);
u32 wazaDB_GetName(u16 id);
u8 wazaDB_GetRangeId(u16 id);
u8 wazaDB_GetYokodori(u16 id);
u8 wazaDB_GetZokuseiDataId(u16 id);
u8 waza_GetZokuseiKindData(u16 id);
u8 zokuseiBiosGetWazaKind(u16 id);

void WS_ALERTEND(void) { ActionSeqNo = 2; }
void WS_SEQEND(void) { ActionSeqNo = 1; }
void WS_SEQRET(void) { ActionSeqNo = 2; }
void WS_SPEABIEND(void) { ActionSeqNo = 2; }
void WS_WAZAEND(void) { ActionSeqNo = 1; }

void WS_TSUIKA_DIRECT_ACT(void) { fightSeqTuikaAct(1, 0); }
void WS_TSUIKA_INDIRECT_ACT(void) { fightSeqTuikaAct(0, 0); }

void WS_DAMAGE_LOSS(void) {
    fightSeq_GetWazaSeq();
    fightSeqDamageLoss(1, 1);
    fightSeq_NextWazaSeq(1);
}

void WS_DAMAGE_LOSS_ONLY(void) {
    fightSeq_GetWazaSeq();
    fightSeqDamageLoss(0, 1);
    fightSeq_NextWazaSeq(1);
}

static inline void wsCopyBytes(u8* dst, u8* src, int count) {
    int i;
    for (i = 0; i < count; i++) {
        *dst++ = *src++;
    }
}

void fightSeqFightOutPokemonEffect(u16 id, FightOutPokemon* fop, u8 wait, u8 openMenu) {
    WazaSequence* waza;
    u8 type = fightFloor_GetFightType(0);
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        waza = Sequence_LoadWaza(seq, id, 4, 0);
        if (waza != 0) {
            WazaSequence_Start(waza, 1);
            if (openMenu == 1) {
                fightMenuFightOutPokemonOpenStatusMenu(fop, type, 1);
                fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, fop, type, 0, 1);
            }
            if (wait == 1) {
                while (WazaSequence_IsActive(waza)) {
                    GSthreadSwitch();
                }
                WazaSequence_Free(waza);
                if (openMenu == 1) {
                    fightMenuFightOutPokemonCloseStatusMenu(fop, type, 0);
                }
            }
        }
    }
}

void WS_CLIENT_BIT_WAIT(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_HP_GAUGE_REDRAW(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(2);
}

void WS_JUMP(void) {
    fightSeq_JumpWazaSeq((void*)((WsArg32Cmd*)fightSeq_GetWazaSeq())->arg);
}

void WS_SET8BIT(void) {
    WsBit8Cmd* cmd = (WsBit8Cmd*)fightSeq_GetWazaSeq();
    *cmd->addr |= cmd->value;
    fightSeq_NextWazaSeq(6);
}

void WS_SET16BIT(void) {
    WsBit16Cmd* cmd = (WsBit16Cmd*)fightSeq_GetWazaSeq();
    *cmd->addr |= cmd->value;
    fightSeq_NextWazaSeq(7);
}

void WS_SET32BIT(void) {
    WsBit32Cmd* cmd = (WsBit32Cmd*)fightSeq_GetWazaSeq();
    *cmd->addr |= cmd->value;
    fightSeq_NextWazaSeq(9);
}

void WS_RESET8BIT(void) {
    WsBit8Cmd* cmd = (WsBit8Cmd*)fightSeq_GetWazaSeq();
    *cmd->addr &= cmd->value ^ 0xFF;
    fightSeq_NextWazaSeq(6);
}

void WS_RESET16BIT(void) {
    WsBit16Cmd* cmd = (WsBit16Cmd*)fightSeq_GetWazaSeq();
    *cmd->addr &= cmd->value ^ 0xFFFF;
    fightSeq_NextWazaSeq(7);
}

void WS_RESET32BIT(void) {
    WsBit32Cmd* cmd = (WsBit32Cmd*)fightSeq_GetWazaSeq();
    *cmd->addr &= cmd->value ^ 0xFFFFFFFF;
    fightSeq_NextWazaSeq(9);
}

void WS_ADDVALUE(void) {
    WsBit8Cmd* cmd = (WsBit8Cmd*)fightSeq_GetWazaSeq();
    *cmd->addr += cmd->value;
    fightSeq_NextWazaSeq(6);
}

void WS_SUBVALUE(void) {
    WsBit8Cmd* cmd = (WsBit8Cmd*)fightSeq_GetWazaSeq();
    *cmd->addr -= cmd->value;
    fightSeq_NextWazaSeq(6);
}

void WS_SETVALUE(void) {
    WsBit8Cmd* cmd = (WsBit8Cmd*)fightSeq_GetWazaSeq();
    u8* addr = cmd->addr;
    u8* p;
    if (((u32)addr & 0xFF000000) == 0xFF000000) {
        p = UserWork + ((u32)addr & 0xFFFFFF);
    } else {
        p = addr;
    }
    *p = cmd->value;
    fightSeq_NextWazaSeq(6);
}

void WS_SETWORK(void) {
    WsSetWorkCmd* cmd = (WsSetWorkCmd*)fightSeq_GetWazaSeq();
    wsCopyBytes(cmd->dst, cmd->src, cmd->count);
    fightSeq_NextWazaSeq(10);
}

void WS_SETWORKOFS(void) {
    WsSetWorkOfsCmd* cmd = (WsSetWorkOfsCmd*)fightSeq_GetWazaSeq();
    int count = cmd->count;
    u8* dst = cmd->dst;
    int i;
    u8* table = cmd->table;
    u8* ofs = cmd->ofs;
    for (i = 0; i < count; i++) {
        *dst++ = table[i + *ofs];
    }
    fightSeq_NextWazaSeq(14);
}

void WS_MESSAGE_TBL(void) {
    u32* tbl = (u32*)((WsArg32Cmd*)fightSeq_GetWazaSeq())->arg;
    u32 msg;
    if (tbl != 0) {
        msg = tbl[ServerWork[5]];
    } else {
        msg = fightFloor_GetAppointMsgId(0);
    }
    fightSeqOpenMsg(msg);
    fightSeq_NextWazaSeq(5);
}

void WS_ALERT_MESSAGE_TBL(void) {
    u32* tbl = (u32*)((WsArg32Cmd*)fightSeq_GetWazaSeq())->arg;
    u32 msg;
    if (tbl != 0) {
        msg = tbl[ServerWork[5]];
    } else {
        msg = fightFloor_GetAppointMsgId(0);
    }
    fightSeqOpenMsg(msg);
    fightSeq_NextWazaSeq(5);
}

void WS_MESSAGE_WAIT(void) {
    WsArg16Cmd* cmd = (WsArg16Cmd*)fightSeq_GetWazaSeq();
    if (ServerWork[7] == 1) {
        fightMainWaitFrame(cmd->arg);
        fightMenuCloseMsg();
        ServerWork[7] = 0;
    }
    fightSeq_NextWazaSeq(3);
}

void WS_LOOP_INIT(void) {
    void* waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    fightSeq_GetWazaSeq();
    fightSeqLoopInitAct(waza);
    fightSeq_NextWazaSeq(1);
}

void fightSeqLoopInitAct(void* waza) {
    fightWazaInitLoop(waza);
    ServerWork[3] = 0;
    ServerStatusFlag &= ~0x40;
    ServerWork[6] = 0;
    ServerStatusFlag &= ~0x4000;
}

void WS_LOOPCNT(void) {
    void* waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    fightWaza_SetKaisuu(waza, cmd[1]);
    fightSeq_NextWazaSeq(2);
}

u8 fightSeqIsAllwaysHit(u16 waza) {
    u16 seq = wazaDB_GetSeqId(waza);
    if (seq == 0x11 || seq == 0x4E) {
        return 1;
    }
    return 0;
}

void WS_TYPE_CHECK_NO_HIT(void) {
    fightSeq_GetWazaSeq();
    fightSeqTypeCheck(0, 1, 1, 0, 1);
}

extern u8 fight_seq_wkc_work;
extern u8 WAZA_Ikari[];
extern u8 WAZA_Melt2[];
extern u8 WAZA_BlankMsg[];
extern u8* WazaEffectTbl[];
extern "C++" {
static s32 _WsWkcActSubSetStockItem(void* arg, u16 id, void* userData);
static s32 _WsWkcActSubJoutaiMigawari(void* arg, u16 id, void* userData);
}

#define WKC_LOAD_TARGETS()                                                        \
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);                          \
    if (attacker) {                                                               \
        soubi = fightOutPokemonGetSoubiItemSoubiDataId(attacker);                 \
        fw = fightOutPokemon_GetFightWazaPtr(attacker);                           \
        hit = fightWazaIsHit(fw);                                                 \
        waza = fightOutPokemon_GetUseWazaDataId(attacker);                        \
        moto = fightOutPokemon_GetMotoWazaDataId(attacker);                       \
        seqWaza = moto == 0xFFFF ? 0 : moto;                                      \
        zokusei = fightWaza_GetZokusei(fw);                                       \
        range = wazaDB_GetRangeId(waza);                                          \
        seqId = wazaDB_GetSeqId(waza);                                            \
        iryoku = wazaDB_GetIryoku(waza);                                          \
    } else {                                                                      \
        soubi = 0;                                                                \
        fw = 0;                                                                   \
        hit = 0;                                                                  \
        waza = 0;                                                                 \
        moto = 0;                                                                 \
        seqWaza = 0;                                                              \
        zokusei = 9;                                                              \
        range = 1;                                                                \
        seqId = 0;                                                                \
        iryoku = 0;                                                               \
    }                                                                             \
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);                          \
    if (defender) {                                                               \
        atkDamage = fightOutPokemon_GetMyselfDamageAtkValue(defender);            \
        speDamage = fightOutPokemon_GetMyselfDamageSpeValue(defender);            \
    } else {                                                                      \
        atkDamage = 0;                                                            \
        speDamage = 0;                                                            \
    }

extern "C" {
s16 fightOutPokemon_GetMyselfDamageAtkValue(FightOutPokemon* fop);
s16 fightOutPokemon_GetMyselfDamageSpeValue(FightOutPokemon* fop);
void pokemonSetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index, u32 value);
void fightSeqFightOutPokemonTokuseiCheckSinkuroDef(void* unused, FightOutPokemon* p);
s32 fightSeqFightOutPokemonTokuseiCheckWazaHitAfter(FightOutPokemon* attacker, FightOutPokemon* defender);
void fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAll(void);
void fightSeqFightOutPokemonTokuseiCheckSinkuroAtk(FightOutPokemon* p, FightOutPokemon* q);
void fightOutPokemonSetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id, u16 value);
void fightSeqSoubiItemCheckWazaHitAfterAll(void);
s32 fightSeqSoubiItemCheckWazaHitAfter(FightOutPokemon* attacker, FightOutPokemon* defender);
void fightOutPokemonSetVisibility(FightOutPokemon* fop, u8 visible);
void Sequence_SetStatus(Sequence* seq, u32 status);
u8 fightOutPokemonCheckNoAttackFlag(FightOutPokemon* fop);
void fightOutPokemonInitJoutaiKie(FightOutPokemon* fop);
void fightOutPokemon_SetVanishoffFlag(FightOutPokemon* fop, u8 value);
void fightSeqVanishOff(FightOutPokemon* p);
u8 fightOutPokemon_GetVanishoffFlag(FightOutPokemon* fop);
void fightFloorReplaceFightOutPokemonAttackToDefense(void* floor);
void fightOutPokemon_SetSketchWazaDataId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetLastSelectWazaDataId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetLastUseWazaDataId(FightOutPokemon* fop, u16 value);
void fightOutPokemon_SetLastReceiveWazaTargetDataId(FightOutPokemon* fop, u16 value);
u8 wazaDB_GetOumugaesi(u16 id);
void fightOutPokemonSetOumuWazaDataId(FightOutPokemon* fop, FightOutPokemon* target, u16 waza);
u8 fightOutPokemon_GetTameWazaFlag(FightOutPokemon* fop);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(void* floor, FightOutPokemon* pokemon);

u16 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
void WS_WKC_ACT(void) {
    u16 type = fightFloor_GetFightType(0);
    u8 done = 0;
    u8* seq = (u8*)fightSeq_GetWazaSeq();
    u16 zokusei;
    u16 waza;
    u16 seqId;
    u16 moto;
    void* fw;
    u8 mode = seq[1];
    u8 range;
    u32 soubi;
    bool hit;
    s16 atkDamage;
    s16 speDamage;
    u16 iryoku;
    u16 seqWaza;
    FightOutPokemon* attacker;
    FightOutPokemon* defender;
    u8 stopAt = seq[2];

    WKC_LOAD_TARGETS();
    for (;;) {
        switch (fight_seq_wkc_work) {
        case 0:
            if (fightOutPokemonIsJoutaiDataId(defender, 0x13) == 1 && fightOutPokemonCheckFightOut(defender) == 1 &&
                attacker != defender && fightOutPokemonIsAlly(attacker, defender) == 0 && hit == 1 &&
                (atkDamage != 0 || speDamage != 0) && iryoku != 0) {
                s32 id = fightSeqCondChgActTypeToPokemonStatusId(1);
                s8 stat = pokemonGetStatus(defender, 0, id, 0);
                if (stat < 12) {
                    pokemonSetStatus(defender, 0, (u8)id, 0, stat + 1);
                    fightSeq_CallWazaSeq(WAZA_Ikari);
                    done = 1;
                }
            }
            fight_seq_wkc_work++;
            break;
        case 1:
            if (fightOutPokemonIsJoutaiDataId(defender, 7) == 1 && fightOutPokemonCheckFightOut(defender) == 1 &&
                attacker != defender && fightOutPokemon_GetMyselfDamageSpeValue(defender) != 0 && fightWazaIsHit(fw) == 1 &&
                wazaDB_GetZokuseiDataId(waza) == 0xA) {
                fightOutPokemonInitJoutaiDataId(defender, 7);
                fightSeqCheckSetHensinBuffToMotoPokemon(defender, 0x7C);
                fightSeq_CallWazaSeq(WAZA_Melt2);
                done = 1;
            }
            fight_seq_wkc_work++;
            break;
        case 2:
            fightSeqFightOutPokemonTokuseiCheckSinkuroDef(attacker, defender);
            fight_seq_wkc_work++;
            break;
        case 3:
            if ((u8)fightSeqFightOutPokemonTokuseiCheckWazaHitAfter(attacker, defender) != 0) {
                done = 1;
            }
            fight_seq_wkc_work++;
            break;
        case 4:
            fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAll();
            fight_seq_wkc_work++;
            break;
        case 5:
            fightSeqFightOutPokemonTokuseiCheckSinkuroAtk(attacker, defender);
            fight_seq_wkc_work++;
            break;
        case 6:
            if ((ServerStatusFlag & 0x02000000) && soubi == 0x1D && moto != 0xA5 &&
                fightOutPokemonCheckWriteJoutaiDataId(attacker, 0x36) == 2) {
                if (moto == 0xE2 && fightWazaIsJoutaiDataId(fw, 0x45) == 1) {
                    fight_seq_wkc_work++;
                    break;
                }
                fightOutPokemonWriteJoutaiDataId(attacker, 0x36, 0);
                fightOutPokemonSetIdBuffJoutaiDataId(attacker, 0x36, moto);
            }
            if (fightOutPokemonIsJoutaiDataId(attacker, 0x36) == 1) {
                u16 lock = fightOutPokemonGetIdBuffJoutaiDataId(attacker, 0x36);
                if (pokemonSearchWazaDataId(fightOutPokemonGetPokemonPtr(attacker), lock) < 0) {
                    fightOutPokemonInitJoutaiDataId(attacker, 0x36);
                }
            }
            fight_seq_wkc_work++;
            break;
        case 7:
            fightFloorLoopValidFightOutPokemon(0, _WsWkcActSubSetStockItem, 0, 0);
            fight_seq_wkc_work++;
            break;
        case 8:
            fightSeqSoubiItemCheckWazaHitAfterAll();
            fight_seq_wkc_work++;
            break;
        case 9:
            fightSeqSoubiItemCheckWazaHitAfter(attacker, defender);
            fight_seq_wkc_work++;
            break;
        case 10:
            if (fightOutPokemonCheckFightOut(attacker) == 1) {
                u16 kie = fightOutPokemonIsJoutaiKie(attacker);
                if (kie != 0) {
                    if (kie != 0x1F) {
                        fightOutPokemonSetVisibility(attacker, 0);
                    } else {
                        Sequence_SetStatus(fightOutPokemon_GetSequencePtr(attacker), 3);
                    }
                }
            }
            fight_seq_wkc_work++;
            break;
        case 11:
            if (fightOutPokemonCheckFightOut(attacker) == 1 &&
                (hit == 0 || fightOutPokemonIsJoutaiKie(attacker) == 0 || fightOutPokemonCheckNoAttackFlag(attacker) == 1)) {
                fightOutPokemonInitJoutaiKie(attacker);
                if (waza != 0x39 && waza != 0x14A) {
                    fightOutPokemon_SetVanishoffFlag(attacker, 1);
                    fightSeqVanishOff(attacker);
                }
            }
            fight_seq_wkc_work++;
            break;
        case 12:
            if (fightOutPokemonCheckFightOut(defender) == 1 && fightOutPokemon_GetVanishoffFlag(defender) == 0 &&
                fightOutPokemonIsJoutaiKie(defender) == 0) {
                fightSeqVanishOff(defender);
            }
            fight_seq_wkc_work++;
            break;
        case 13:
            fightFloorLoopValidFightOutPokemon(0, _WsWkcActSubJoutaiMigawari, 0, 0);
            fight_seq_wkc_work++;
            break;
        case 14:
            if (ServerStatusFlag & 0x1000) {
                fightFloorReplaceFightOutPokemonAttackToDefense(0);
                ServerStatusFlag &= ~0x1000;
                WKC_LOAD_TARGETS();
            }
            if (wazaDB_GetSeqId(seqWaza) != 0x7F || (wazaDB_GetSeqId(seqWaza) == 0x7F && hit == 0)) {
                fightOutPokemon_SetSketchWazaDataId(attacker, moto);
            }
            if (fightOutPokemonCheckFightOut(attacker) == 1 && wazaDB_GetSeqId(seqWaza) != 0x7F) {
                if (ServerStatusFlag & 0x02000000) {
                    fightOutPokemon_SetLastSelectWazaDataId(attacker, moto);
                    fightOutPokemon_SetLastUseWazaDataId(attacker, waza);
                } else {
                    fightOutPokemon_SetLastSelectWazaDataId(attacker, 0xFFFF);
                    fightOutPokemon_SetLastUseWazaDataId(attacker, 0xFFFF);
                }
                if (fightOutPokemonCheckFightOut(defender) == 1) {
                    fightOutPokemon_SetLastReceiveWazaTargetDataId(
                        defender, fightTargetGetTragetPtrToRelativeHostSideFightTargetId(attacker, type));
                }
                if ((ServerStatusFlag & 0x02000000) && hit == 1) {
                    if (moto == 0xFFFF) {
                        fightOutPokemon_SetHitWazaDataId(defender, moto);
                    } else {
                        fightOutPokemon_SetHitWazaDataId(defender, waza);
                        fightOutPokemon_SetHitWazaZokuseiDataId(defender, zokusei);
                    }
                } else {
                    fightOutPokemon_SetHitWazaDataId(defender, 0xFFFF);
                }
            }
            fight_seq_wkc_work++;
            break;
        case 15:
            if (fightOutPokemonCheckValid(attacker) == 1 && wazaDB_GetOumugaesi(seqWaza) == 1 &&
                (ServerStatusFlag & 0x02000000) && attacker != defender && fightOutPokemonCheckValid(defender) == 1 && hit == 1) {
                fightOutPokemonSetOumuWazaDataId(defender, attacker, moto);
            }
            fight_seq_wkc_work++;
            break;
        case 16:
            if (!(ServerStatusFlag & 0x80000) && fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 &&
                fightOutPokemon_GetTameWazaFlag(attacker) == 0 && range == 4 && !(ServerStatusFlag & 0x200)) {
                FightOutPokemon* next = fightTargetGetPtrAsNowFightType(0xE, (u32)defender);
                if (fightOutPokemonCheckFightOut(next) == 1) {
                    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, next);
                    fightSeqLoopInitAct(fw);
                    ServerStatusFlag |= 0x200;
                    fight_seq_wkc_work = 0;
                    fightSeq_CallWazaSeq(WAZA_BlankMsg);
                    fightSeq_JumpWazaSeq(WazaEffectTbl[seqId]);
                    return;
                }
                ServerStatusFlag |= 0x200;
            }
            fight_seq_wkc_work++;
            break;
        case 17:
            if (mode == 0) {
                fightMenuAllFightTrainerCloseStatusMenu(0);
                fightMenuAllFightOutPokemonCloseStatusMenu(0);
                fightMenuCloseMsg();
            }
            break;
        }
        if (mode == 1 && done == 0) {
            fight_seq_wkc_work = 0x11;
        }
        if (mode == 2 && stopAt == fight_seq_wkc_work) {
            fight_seq_wkc_work = 0x11;
        }
        if (fight_seq_wkc_work == 0x11 || done != 0) {
            break;
        }
    }
    if (fight_seq_wkc_work == 0x11 && done == 0) {
        fightSeq_NextWazaSeq(3);
    }
}
}
#undef WKC_LOAD_TARGETS

void WS_GOSUB(void) {
    fightSeq_CallWazaSeq((void*)((WsArg32Cmd*)fightSeq_GetWazaSeq())->arg);
    fightSeq_NextWazaSeq(5);
}

void WS_WAIT(void) {
    fightMainWaitFrame(((WsArg16Cmd*)fightSeq_GetWazaSeq())->arg);
    fightSeq_NextWazaSeq(3);
}

void WS_ALERT_MESSAGE(void) {
    fightSeqOpenMsg(((WsArg16Cmd*)fightSeq_GetWazaSeq())->arg);
    fightSeq_NextWazaSeq(3);
}

void WS_MESSAGE(void) {
    fightSeqOpenMsg(((WsArg32Cmd*)fightSeq_GetWazaSeq())->arg);
    fightSeq_NextWazaSeq(5);
}

extern u32 NoHitMsgTbl[];
extern u8 WAZA_ItemKoraeta[];
extern u8 WAZA_Ichigeki[];
extern u8 WAZA_Koraeta[];

void WS_WAZAKOUKA_MESSAGE(void) {
    FightOutPokemon* defender;
    void* fw;
    u32 msg;
    u16 item;

    fightSeq_GetWazaSeq();
    fw = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    fightOutPokemonGetNicknamePtr(defender);
    item = fightOutPokemonGetSoubiItemDataId(defender);
    ServerWork[7] = 0;
    msg = 0;
    if ((fightWazaIsJoutaiDataId(fw, 0x40) == 1 && fightWazaIsJoutaiDataId(fw, 0x43) == 0) ||
        (fightWazaIsJoutaiDataId(fw, 0x40) == 1 && ServerWork[6] >= 3)) {
        msg = NoHitMsgTbl[ServerWork[6]];
    } else if (fightWazaIsMix(fw) == 0) {
        if (fightWazaIsJoutaiDataId(fw, 0x41) == 1) {
            msg = 0x4F20;
        } else if (fightWazaIsJoutaiDataId(fw, 0x42) == 1) {
            msg = 0x4F1F;
        } else if (fightWazaIsJoutaiDataId(fw, 0x43) == 1) {
            msg = 0x4E34;
        } else if (fightWazaIsJoutaiDataId(fw, 0x44) == 1) {
            msg = 0x4F1B;
        } else if (fightWazaIsJoutaiDataId(fw, 0x45) == 1) {
            msg = 0x4F29;
        } else if (fightWazaIsJoutaiDataId(fw, 0x46) == 1) {
            msg = 0x4EB4;
        } else if (fightWazaIsJoutaiDataId(fw, 0x47) == 1) {
            fightWazaInitJoutaiDataId(fw, 0x46);
            fightWazaInitJoutaiDataId(fw, 0x47);
            fightFloor_SetAppointItemDataId(0, item);
            fightFloor_SetItemPokemonPtr(0, defender);
            fightSeq_CallWazaSeq(WAZA_ItemKoraeta);
            return;
        }
    } else if (fightWazaIsJoutaiDataId(fw, 0x43) == 1) {
        msg = 0x4E34;
    } else if (fightWazaIsJoutaiDataId(fw, 0x44) == 1) {
        fightWazaInitJoutaiDataId(fw, 0x44);
        fightWazaInitJoutaiDataId(fw, 0x41);
        fightWazaInitJoutaiDataId(fw, 0x42);
        fightSeq_CallWazaSeq(WAZA_Ichigeki);
        return;
    } else if (fightWazaIsJoutaiDataId(fw, 0x46) == 1) {
        fightWazaInitJoutaiDataId(fw, 0x46);
        fightWazaInitJoutaiDataId(fw, 0x47);
        fightSeq_CallWazaSeq(WAZA_Koraeta);
        return;
    } else if (fightWazaIsJoutaiDataId(fw, 0x47) == 1) {
        fightWazaInitJoutaiDataId(fw, 0x46);
        fightWazaInitJoutaiDataId(fw, 0x47);
        fightFloor_SetAppointItemDataId(0, item);
        fightFloor_SetItemPokemonPtr(0, defender);
        fightSeq_CallWazaSeq(WAZA_ItemKoraeta);
        return;
    } else if (fightWazaIsJoutaiDataId(fw, 0x45) == 1) {
        msg = 0x4F29;
    }
    if (msg) {
        fightFloor_SetWazakoukaMsgId(0, msg);
        if (fightMenuWazaKoukaMsg(msg, (u32)defender, item) == 1) {
            ServerWork[7] = 1;
        }
    }
    fightSeq_NextWazaSeq(1);
}

void WS_TYPE_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeqTypeCheck(1, 1, 1, 0, 1);
}

struct FightWazaJoutaiCopy {
    u8 data[0x10];
};

struct FightWazaCopy {
    u8 wazaBanme;
    u16 motoWazaDataId;
    u16 useWazaDataId;
    u16 targetDataId;
    FightWazaJoutaiCopy joutai[9];
    u8 critical;
    u8 damageValue;
    s32 damage;
    s32 hitDamage;
    u16 iryoku;
    u16 zokusei;
    u8 kaisuu;
    u8 autoMakeFlag;
};

u16 zokuseiGetWazaJoutai(u16 wazaZokusei, u16 defZokusei);
u8 fightSeqTameWazaTurnCheck(FightOutPokemon* p, u16 waza);

void fightSeqTypeCheckHikaePokemon(void* fp, u8 apply, u8 setFlags, u8 needPower) {
    u8 noHit = 0;
    u8 noEffect = 0;
    FightOutPokemon* attacker;
    void* buff;
    buff = fightPokemon_GetPokemonBuffPtr(fp);
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    u16 atkType1 = fightOutPokemonGetZokuseiDataId(attacker, 0);
    u16 atkType2 = fightOutPokemonGetZokuseiDataId(attacker, 1);
    fightOutPokemonGetTokuseiDataId(attacker);
    u16 wazaType;
    u16 iryoku;
    u16 waza;
    waza = fightOutPokemon_GetUseWazaDataId(attacker);
    iryoku = wazaDB_GetIryoku(waza);
    FightWazaCopy* fw;
    fw = (FightWazaCopy*)fightOutPokemon_GetFightWazaPtr(attacker);
    wazaType = fightWaza_GetZokusei(fw);
    u16 mons = pokemon_GetPokemonDataId(buff);
    u16 defType1 = pokemonDB_GetZokuseiDataId(mons, 0);
    u16 defType2 = pokemonDB_GetZokuseiDataId(mons, 1);
    u16 tokusei = pokemonDB_GetTokuseiDataId(mons, pokemon_GetTokuseiFlag(buff));
    FightWazaCopy backup;

    if (fw) {
        backup = *fw;
    }
    if (waza != 0xA5 && wazaCheckDarkWaza(waza) != 1 && (needPower != 1 || iryoku != 0)) {
        if (apply == 1 && (atkType1 == wazaType || atkType2 == wazaType)) {
            fightWaza_SetDamage(fw, (fightWaza_GetDamage(fw) * 15) / 10);
        }
        if (tokusei == 0x1A && wazaType == 4) {
            if (setFlags == 1) {
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x43);
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
            }
            ServerWork[6] = 4;
        } else {
            figthSeqZokuseiCheckCalc(fw, zokuseiGetWazaJoutai(wazaType, defType1), waza, apply);
            if (defType1 != defType2) {
                u16 tmp1 = zokuseiGetWazaJoutai(wazaType, defType2);
                figthSeqZokuseiCheckCalc(fw, tmp1, waza, apply);
            }
        }
        if (tokusei == 0x19 && fightSeqTameWazaTurnCheck(attacker, waza) == 2 &&
            (fightWazaIsJoutaiDataId(fw, 0x41) == 0 || fightWazaIsJoutaiSousai(fw) == 1) && iryoku != 0) {
            if (setFlags == 1) {
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
            }
            ServerWork[6] = 3;
        }
        if (fightWazaIsJoutaiDataId(fw, 0x43) == 1) {
            fightOutPokemon_SetOutWazaKoukanaiFlag(attacker, 1);
        }
    }
    if (apply == 0) {
        if (fightWazaIsJoutaiDataId(fw, 0x40) == 1) {
            noHit = 1;
        }
        if (fightWazaIsJoutaiDataId(fw, 0x43) == 1) {
            noEffect = 1;
        }
        if (fw) {
            *fw = backup;
        }
        if (noHit == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        }
        if (noEffect == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x43);
        }
    }
}
void fightSeqTypeCheck(u8 apply, u8 next, u8 setFlags, u8 needPower, u8 size) {
    u8 noHit = 0;
    u8 noEffect = 0;
    FightOutPokemon* attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    u16 atkType1 = fightOutPokemonGetZokuseiDataId(attacker, 0);
    u16 atkType2 = fightOutPokemonGetZokuseiDataId(attacker, 1);
    fightOutPokemonGetTokuseiDataId(attacker);
    u16 waza = fightOutPokemon_GetUseWazaDataId(attacker);
    u16 iryoku = wazaDB_GetIryoku(waza);
    FightWazaCopy* fw = (FightWazaCopy*)fightOutPokemon_GetFightWazaPtr(attacker);
    u16 wazaType = fightWaza_GetZokusei(fw);
    FightOutPokemon* defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    u16 defType1 = fightOutPokemonGetZokuseiDataId(defender, 0);
    u16 defType2 = fightOutPokemonGetZokuseiDataId(defender, 1);
    FightWazaCopy backup;
    u32 tokusei = fightOutPokemonGetTokuseiDataId(defender);

    if (fw) {
        backup = *fw;
    }
    if (waza != 0xA5 && wazaCheckDarkWaza(waza) != 1 && (waza != 0x137 || fightFloorGetNowTenkouDataId(0, 1) != 5) &&
        (needPower != 1 || iryoku != 0)) {
        if (apply == 1 && (atkType1 == wazaType || atkType2 == wazaType)) {
            fightWaza_SetDamage(fw, (fightWaza_GetDamage(fw) * 15) / 10);
        }
        if (tokusei == 0x1A && wazaType == 4) {
            if (setFlags == 1) {
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x43);
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
                fightOutPokemon_SetHitWazaDataId(defender, 0);
                fightOutPokemon_SetHitWazaZokuseiDataId(defender, 9);
            }
            ServerWork[6] = 4;
        } else if (fightOutPokemonIsJoutaiDataId(defender, 0x19) != 1 || (defType1 != 7 && defType2 != 7) || wazaType > 1) {
            u16 tmp1 = zokuseiGetWazaJoutai(wazaType, (u16)defType1);
            figthSeqZokuseiCheckCalc(fw, tmp1, waza, apply);
            if (defType1 != defType2) {
                figthSeqZokuseiCheckCalc(fw, zokuseiGetWazaJoutai((u16)wazaType, (u8)defType2), waza, apply);
            }
        }
        if (tokusei == 0x19 && fightSeqTameWazaTurnCheck(attacker, waza) == 2 &&
            (fightWazaIsJoutaiDataId(fw, 0x41) == 0 || fightWazaIsJoutaiSousai(fw) == 1) && iryoku != 0) {
            if (setFlags == 1) {
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
                fightOutPokemon_SetHitWazaDataId(defender, 0);
                fightOutPokemon_SetHitWazaZokuseiDataId(defender, 9);
            }
            ServerWork[6] = 3;
        }
        if (fightWazaIsJoutaiDataId(fw, 0x43) == 1) {
            fightOutPokemon_SetOutWazaKoukanaiFlag(attacker, 1);
        }
    }
    if (apply == 0) {
        if (fightWazaIsJoutaiDataId(fw, 0x40) == 1) {
            noHit = 1;
        }
        if (fightWazaIsJoutaiDataId(fw, 0x43) == 1) {
            noEffect = 1;
        }
        if (fw) {
            *fw = backup;
        }
        if (noHit == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        }
        if (noEffect == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x43);
        }
    }
    if (next == 1) {
        fightSeq_NextWazaSeq(size);
    }
}

void WS_CHECK_TYPE(void) {
    WsCheckTypeCmd* cmd = (WsCheckTypeCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(cmd->side, 0);
    void* jump = cmd->jump;
    if (fightOutPokemonIsZokuseiDataId(pokemon, cmd->type) == 1) {
        fightSeq_JumpWazaSeq(jump);
    } else {
        fightSeq_NextWazaSeq(7);
    }
}

void WS_SIDECONDITION_CHECK(void) {
    WsSideCondCmd* cmd = (WsSideCondCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(cmd->side, 0);
    void* side = fightTargetGetPtrAsNowFightType(2, (u32)pokemon);
    void* jump = cmd->jump;
    if (fightSideIsJoutaiDataId(side, cmd->id) == 1) {
        fightSeq_JumpWazaSeq(jump);
    } else {
        fightSeq_NextWazaSeq(8);
    }
}

void WS_WAZAKOUKA_CHECK(void) {
    WsWazaKoukaCmd* cmd = (WsWazaKoukaCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(cmd->side, 0);
    void* jump = cmd->jump;
    u8 has = fightOutPokemonIsJoutaiDataId(pokemon, (u16)cmd->id);
    if (cmd->expect == has) {
        fightSeq_JumpWazaSeq(jump);
    } else {
        fightSeq_NextWazaSeq(11);
    }
}

void WS_CONDITION2_CHECK(void) {
    WS_CONDITION_CHECK();
}

void WS_CONDITION_CHECK(void) {
    WsConditionCmd* cmd = (WsConditionCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(cmd->side, 0);
    u16 kind = cmd->kind;
    void* jump = cmd->jump;
    if (kind == 1) {
        if (!fightOutPokemonIsJoutaiNormal(pokemon)) {
            fightSeq_JumpWazaSeq(jump);
        } else {
            fightSeq_NextWazaSeq(10);
        }
    } else if (kind == 2) {
        if (fightOutPokemonIsJoutaiKaragenki(pokemon) == 1) {
            fightSeq_JumpWazaSeq(jump);
        } else {
            fightSeq_NextWazaSeq(10);
        }
    } else {
        if (fightOutPokemonIsJoutaiDataId(pokemon, kind) == 1 && fightOutPokemonCheckFightOut(pokemon) == 1) {
            fightSeq_JumpWazaSeq(jump);
        } else {
            fightSeq_NextWazaSeq(10);
        }
    }
}

void WS_CRITICAL_CHECK(void) {
    u16 targetAbility;
    u32 score;
    u32 scoreTemp;
    u32 move209Bonus;
    s16 move209Status;
    u8 itemSpeciesBonus2;
    u8 itemSpeciesBonus1;
    u32 denominator;
    s8 item;
    FightOutPokemon* attacker;
    FightOutPokemon* target;
    u32 item41Bonus;
    u32 maximum;
    u32 maximumTemp;
    u16 random;
    void* waza;
    u16 move;
    u32 move43Bonus;
    u32 finalScore;

    fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemonGetTokuseiDataId(attacker);
    item = fightOutPokemonGetSoubiItemSoubiDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    move = fightOutPokemon_GetUseWazaDataId(attacker);
    {
        u32 species;
        species = figthOutPokemonGetPokemonDataId(attacker);
        target = fightTargetGetPtrAsNowFightType(0x12, 0);
        itemSpeciesBonus1 = 0;
        if ((u16)item == 0x3f) {
            if ((u16)species == 0x71) {
                itemSpeciesBonus1 = 1;
            }
        }
        itemSpeciesBonus2 = 0;
        if ((u16)item == 0x42) {
            if ((u16)species == 0x53) {
                itemSpeciesBonus2 = 1;
            }
        }
    }
    score = (u8)fightOutPokemonIsJoutaiDataId(attacker, 0xf);
    scoreTemp = __cntlzw(1 - score);
    score = scoreTemp >> 4;
    score = score & 0x1fe;
    move43Bonus = wazaDB_GetSeqId(move) == 0x2b;
    score += wazaDB_GetSeqId(move) == 0x4b;
    score += wazaDB_GetSeqId(move) == 200;
    move209Status = wazaDB_GetSeqId(move);
    maximumTemp = fight_waza_critical_data_number;
    maximum = maximumTemp - 1;
    score = move43Bonus + ((((score + ((u16)move209Status == 0xd1)) + ((u16)item == 0x29)) + itemSpeciesBonus1 * 2) + itemSpeciesBonus2 * 2);
    finalScore = score & 0xffff;
    if (finalScore <= maximum) {
        finalScore = finalScore;
    } else {
        finalScore = maximum & 0xffff;
    }
    if ((u16)fightOutPokemonGetTokuseiDataId(target) != 4 && (u16)fightOutPokemonGetTokuseiDataId(target) != 0x4b &&
        fightFloor_GetFightKindDoCriticalAttackFlag(0) == 1) {
        random = HSD_Rand();
        denominator = fightWazaCriticalDataBiosGetBunbo(fightWazaCriticalDataBiosGetPtr(finalScore));
        if (random % (u8)denominator == 0) {
            fightWaza_SetCritical(waza, 2);
        } else {
            fightWaza_SetCritical(waza, 1);
        }
    } else {
        fightWaza_SetCritical(waza, 1);
    }
    fightSeq_NextWazaSeq(1);
}

static inline void* wsResolve(void* a) {
    u32 v = (u32)a;
    if ((v & 0xFF000000) == 0xFF000000) {
        return UserWork + (v & 0xFFFFFF);
    }
    return a;
}

void WS_IF8(void) {
    WsIf8Cmd* cmd = (WsIf8Cmd*)fightSeq_GetWazaSeq();
    void* jump;
    u8 value;
    u8 kind;
    u8* addr = (u8*)wsResolve(cmd->addr);
    kind = cmd->kind;
    value = cmd->value;
    jump = cmd->jump;
    fightSeq_NextWazaSeq(11);
    switch (kind) {
    case 0:
        if (*addr == value) fightSeq_JumpWazaSeq(jump);
        break;
    case 1:
        if (*addr != value) fightSeq_JumpWazaSeq(jump);
        break;
    case 2:
        if (*addr > value) fightSeq_JumpWazaSeq(jump);
        break;
    case 3:
        if (*addr < value) fightSeq_JumpWazaSeq(jump);
        break;
    case 4:
        if (*addr & value) fightSeq_JumpWazaSeq(jump);
        break;
    case 5:
        if (!(*addr & value)) fightSeq_JumpWazaSeq(jump);
        break;
    }
}

void WS_IF16(void) {
    WsIf16Cmd* cmd = (WsIf16Cmd*)fightSeq_GetWazaSeq();
    void* jump;
    u16 value;
    u8 kind;
    u16* addr = (u16*)wsResolve(cmd->addr);
    kind = cmd->kind;
    value = cmd->value;
    jump = cmd->jump;
    fightSeq_NextWazaSeq(12);
    switch (kind) {
    case 0:
        if (*addr == value) fightSeq_JumpWazaSeq(jump);
        break;
    case 1:
        if (*addr != value) fightSeq_JumpWazaSeq(jump);
        break;
    case 2:
        if (*addr > value) fightSeq_JumpWazaSeq(jump);
        break;
    case 3:
        if (*addr < value) fightSeq_JumpWazaSeq(jump);
        break;
    case 4:
        if (*addr & value) fightSeq_JumpWazaSeq(jump);
        break;
    case 5:
        if (!(*addr & value)) fightSeq_JumpWazaSeq(jump);
        break;
    }
}

void WS_IF32(void) {
    WsIf32Cmd* cmd = (WsIf32Cmd*)fightSeq_GetWazaSeq();
    void* jump;
    u32 value;
    u8 kind;
    u32* addr = (u32*)wsResolve(cmd->addr);
    kind = cmd->kind;
    value = cmd->value;
    jump = cmd->jump;
    fightSeq_NextWazaSeq(14);
    switch (kind) {
    case 0:
        if (*addr == value) fightSeq_JumpWazaSeq(jump);
        break;
    case 1:
        if (*addr != value) fightSeq_JumpWazaSeq(jump);
        break;
    case 2:
        if (*addr > value) fightSeq_JumpWazaSeq(jump);
        break;
    case 3:
        if (*addr < value) fightSeq_JumpWazaSeq(jump);
        break;
    case 4:
        if (*addr & value) fightSeq_JumpWazaSeq(jump);
        break;
    case 5:
        if (!(*addr & value)) fightSeq_JumpWazaSeq(jump);
        break;
    }
}

void WS_IFWEQ(void) {
    WsIfwCmd* cmd = (WsIfwCmd*)fightSeq_GetWazaSeq();
    void* jump;
    u8 count;
    u8 i;
    u8* a = cmd->a;
    i = 0;
    u8* b = cmd->b;
    count = cmd->count;
    jump = cmd->jump;
    for (; i < count; a++, b++, i++) {
        if (*a != *b) {
            fightSeq_NextWazaSeq(14);
            break;
        }
    }
    if (i == count) {
        fightSeq_JumpWazaSeq(jump);
    }
}

void WS_IFWNE(void) {
    u8 same = 0;
    WsIfwCmd* cmd = (WsIfwCmd*)fightSeq_GetWazaSeq();
    u8* a;
    u8* b;
    u8 count;
    u8 i;
    a = cmd->a;
    i = 0;
    b = cmd->b;
    count = cmd->count;
    void* jump = cmd->jump;
    for (; i < count; a++, b++, i++) {
        if (*a == *b) same++;
    }
    if (same != count) {
        fightSeq_JumpWazaSeq(jump);
        return;
    }
    fightSeq_NextWazaSeq(14);
}

void WS_MONS_TYPE(void) {
    WsMonsCmd* cmd = (WsMonsCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(cmd->side, 0);
    if (fightOutPokemonIsZokuseiDataId(pokemon, cmd->type) == 1) {
        fightSeq_JumpWazaSeq(cmd->jump);
        return;
    }
    fightSeq_NextWazaSeq(7);
}

void WS_SPEABI_HAVE_CHECK(void) {
    WsSpeabiHaveCmd* cmd = (WsSpeabiHaveCmd*)fightSeq_GetWazaSeq();
    if (fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(0, cmd->side, 0, 0, 0) != 0) {
        fightSeq_JumpWazaSeq(cmd->jump);
        return;
    }
    fightSeq_NextWazaSeq(6);
}

void WS_SPEABI_CHECK(void) {
    WsSpeabiCmd* cmd = (WsSpeabiCmd*)fightSeq_GetWazaSeq();
    u32 tokusei;
    void* jump;
    jump = cmd->jump;
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(cmd->side, 0);
    tokusei = fightOutPokemonGetTokuseiDataId(pokemon);
    if ((u16)tokusei == ((WsSpeabiCmd*)fightSeq_GetWazaSeq())->tokusei && fightFloorIsNowEncountOpeningVirtualBattle(0) == 0) {
        fightFloor_SetTokuseiPokemonPtr(0, pokemon);
        fightSeq_JumpWazaSeq(jump);
        return;
    }
    fightSeq_NextWazaSeq(7);
}

void WS_KIZETSU_WAIT(void) {
    FightOutPokemon* pokemon;
    u8 type = fightFloor_GetFightType(0);
    pokemon = fightTargetGetPtrAsNowFightType(((WsSideCmd*)fightSeq_GetWazaSeq())->side, 0);
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    fightOutPokemonKizetuEffect(pokemon, 2);
    fightMenuFightOutPokemonCloseStatusMenu(pokemon, type, 0);
    fightOutPokemonKizetuEffect(pokemon, 3);
    fightSeqKizetuInit(pokemon);
    fightSeq_NextWazaSeq(2);
}

void WS_SAKUJO(void) {
    FightOutPokemon* pokemon;
    u32 id;
    pokemon = fightTargetGetPtrAsNowFightType(((WsSideCmd*)fightSeq_GetWazaSeq())->side, 0);
    id = TSUIKATbl[ServerWork[3]];
    if (id != 0 && fightOutPokemonIsJoutaiDataId(pokemon, id) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, id);
    }
    ServerWork[3] = 0;
    fight_seq_server_work3_temp = 0;
    fightSeq_NextWazaSeq(2);
}

void WS_LOOP(void) {
    FightOutPokemon* attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    void* waza = fightOutPokemon_GetFightWazaPtr(attacker);
    WsLoopCmd* cmd = (WsLoopCmd*)fightSeq_GetWazaSeq();
    s16 n;
    n = fightWaza_GetKaisuu(waza);
    n--;
    if (n < 0) n = 0;
    if (n == 0) {
        fightSeq_NextWazaSeq(5);
    } else {
        fightSeq_JumpWazaSeq(cmd->jump);
    }
    fightWaza_SetKaisuu(waza, n);
}

u8 fightSeqIsTenkouHit(u16 waza) {
    u16 seq = wazaDB_GetSeqId(waza);
    if (fightFloorGetNowTenkouDataId(0, 1) == 2 && seq == 0x98) {
        return 1;
    }
    return 0;
}

u8 fightSeqRegulationZenmetuCheck(u16 waza) {
    u8 flag = fightFloor_GetFightKindRegulationFlag(0);
    u8 suicide = menuCBRule_ProhibitionSuicide();
    u16 seq = wazaDB_GetSeqId(waza);
    if (flag == 1 && suicide == 1 && seq == 7) {
        return 1;
    }
    return 0;
}

u8 fightSeqRegulationOverTwoCheck(u16 type, u32 arg) {
    u8 flag = fightFloor_GetFightKindRegulationFlag(0);
    u8 sleep = menuCBRule_EnableSbToSleep();
    u8 ice = menuCBRule_EnableSbToIceed();
    if (flag == 1) {
        if (type == 8) {
            if (sleep != 1 && fightSeqRegulationGetJoutaiCount(type, arg) >= 1) {
                return 1;
            }
        } else if (type == 7 && ice != 1 && fightSeqRegulationGetJoutaiCount(7, arg) >= 1) {
            return 1;
        }
    }
    return 0;
}

u16 fightSeqRegulationGetJoutaiCount(u16 id, u32 arg) {
    enum TsE { TsE0 };
    u16 count = 0;
    void* side = fightTargetGetPtrAsNowFightType(2, arg);
    enum TsE trainerNum = (enum TsE)(fightFloor_GetFightTypeTrainerNum(0));
    u16 i;
    fightFloor_GetFightTypeEntryPokemonNum(0);
    for (i = 0; i < trainerNum; i++) {
        void* trainer = fightSideGetValidFightTrainerPtr(side, i);
        if (trainer != 0) {
            u16 j;
            for (j = 0; j < 6; j++) {
                void* pokemon = fightTrainerGetValidFightPokemonPtr(trainer, j);
                if (pokemon != 0 && fightPokemonCheckFightOut(pokemon) != 0 && fightPokemonIsJoutaiDataId(pokemon, id) == 1) {
                    count++;
                }
            }
        }
    }
    return count;
}

u8 fightSeqGuardCheck(u8 arg, s32 flag) {
    FightOutPokemon* attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    u16 waza = fightOutPokemon_GetUseWazaDataId(attacker);
    FightOutPokemon* defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    u8 result = 0;
    if (fightSeqIsGuard(defender, waza) == 1) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeqWazaSeqSet(arg, flag);
        ServerWork[6] = 1;
        result = 1;
    }
    return result;
}

u8 fightSeqIsGuard(FightOutPokemon* p, u16 waza) {
    u8 mamoru = wazaDB_GetMamoru(waza);
    if (fightOutPokemonIsJoutaiDataId(p, 0x2B) == 1 && mamoru == 1) {
        return 1;
    }
    return 0;
}

void WS_GUARDCHECK(void) {
    FightOutPokemon* attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    u8 mamoru = wazaDB_GetMamoru(fightOutPokemon_GetUseWazaDataId(attacker));
    FightOutPokemon* defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    fightSeq_GetWazaSeq();
    if (fightOutPokemonIsJoutaiDataId(defender, 0x2B) == 1 && mamoru == 1) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeqWazaSeqSet(5, 0);
        ServerWork[6] = 1;
        return;
    }
    fightSeq_NextWazaSeq(5);
}

void WS_CRITICAL_MESSAGE(void) {
    FightOutPokemon* attacker;
    void* waza;
    fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    if (fightWaza_GetCritical(waza) == 2 && fightWazaIsHit(waza) == 1) {
        fightFloor_SetCriticakMsgId(0, 0x4F1A);
        fightSeqOpenMsg(0x4F1A);
    }
    fightSeq_NextWazaSeq(1);
}

void fightSeqPpdecMonomane(FightOutPokemon* p, u8 bit, u8 arg) {
    if (fightOutPokemonIsJoutaiDataId(p, 0x10) == 0 && fightOutPokemonIsJoutaiDataId(p, 0x31) == 1) {
        u32 buff = fightOutPokemonGetBuffJoutaiDataId(p, 0x31);
        if (!(buff & (1 << bit))) {
            fightSeqCheckSetHensinBuffToMotoPokemon2(p, 0x80, bit, arg);
        }
    }
}

extern "C" {
extern s16 msgFrame;

void WS_ATTACK_MESSAGE(void) {
    FightOutPokemon* p;
    u8 type = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    if (!(ServerStatusFlag & 0x600)) {
        p = fightTargetGetPtrAsNowFightType(0x11, 0);
        u8* trainer = (u8*)fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, p);
        u8* ai1 = (u8*)fightTargetGetPtr(9, trainer, fightFloor_GetFightType(0));
        u8* ai2 = (u8*)fightTargetGetPtr(0xA, trainer, fightFloor_GetFightType(0));
        u16 waza;
        Sequence* seq;
        fightOutPokemonGetNicknamePtr(p);
        waza = fightOutPokemon_GetUseWazaDataId(p);
        seq = fightOutPokemon_GetSequencePtr(p);
        fightOutPokemon_GetFightPokemonPtr(p);
        fightSeqFightOutPokemonEffect(0x9E, p, 0, 1);
        fightMenuFightOutPokemonOpenStatusMenu(p, type, 1);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, p, type, 0, 1);
        if (fightMenuWazaOutMsg((u32)p, waza) == 1) {
            ServerWork[7] = 2;
            msgFrame = 0x50;
        }
        if (ai1) {
            if (fightTrainerAiDB_GetParamStoreFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(ai1))) == 1) {
                fightAi_AddStoreWaza(p, ai1, waza);
                fightAi_DereteExpectWaza(p, ai1, waza);
            }
        }
        if (ai2) {
            if (fightTrainerAiDB_GetParamStoreFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(ai2))) == 1) {
                fightAi_AddStoreWaza(p, ai1, waza);
                fightAi_DereteExpectWaza(p, ai1, waza);
            }
        }
        if (seq) {
            WazaSequence* ws = (WazaSequence*)Sequence_GetWaza(seq, 0x9E, 4);
            s16 timeout = 0x120;
            while (WazaSequence_IsActive(ws)) {
                GSthreadSwitch();
                if (timeout-- <= 0) {
                    GSprint(dbgMenuGetLayerID(), 0x1E, 0x1E, 0xA000FF, "Attack Msg Eff Play");
                    timeout = 0;
                }
            }
            WazaSequence_Free(ws);
        } else {
            fightSeq_CallWazaSeq(WAZA_Wait);
        }
        fightMenuFightOutPokemonCloseStatusMenu(p, type, 0);
        ServerStatusFlag |= 0x400;
    }
    fightSeq_NextWazaSeq(1);
}
}

void WS_FIGHT_EFFECT(void) {
    WsFightEffectCmd* cmd = (WsFightEffectCmd*)fightSeq_GetWazaSeq();
    u16* p;
    u32 v;
    fightTargetGetPtrAsNowFightType(cmd->side, 0);
    p = (u16*)wsResolve(cmd->arg);
    if (p != 0) {
        v = *p;
    } else {
        v = 0;
    }
    fightSeqFightEffect(cmd->side, cmd->effect, v);
    fightSeq_NextWazaSeq(7);
}

void WS_FIGHT_EFFECT2(void) {
    WsFightEffect2Cmd* cmd = (WsFightEffect2Cmd*)fightSeq_GetWazaSeq();
    u8* e;
    u32 effect;
    volatile u16* a;
    u32 arg;
    fightTargetGetPtrAsNowFightType(cmd->side, 0);
    e = (u8*)wsResolve(cmd->effect);
    if (e != 0) {
        effect = *e;
    } else {
        effect = 0;
    }
    a = cmd->arg;
    if (a != 0) {
        arg = *a;
    } else {
        arg = 0;
    }
    fightSeqFightEffect(cmd->side, effect, arg);
    fightSeq_NextWazaSeq(10);
}

void WS_COND_CHG_WORK_SET(void) {
    s32 base = 0;
    u8 packed;
    int v;
    fightSeq_GetWazaSeq();
    packed = UserWork[0x1601e];
    switch (packed & 0xF0) {
    case 0x10:
        base = 0xF;
        break;
    case 0x20:
        base = 0x27;
        break;
    case 0x90:
        base = 0x16;
        break;
    case 0xA0:
        base = 0x2E;
        break;
    }
    s32 low = (packed & 0xF) - 1;
    v = low;
    v = base + v;
    UserWork[0x160a4] = v;
    UserWork[0x160a5] = 0;
    fightSeq_NextWazaSeq(1);
}

extern "C++" { static u8 _fightSeqFightEffectStatusUpDown(u8 amount, u8 kind); }
struct FightTargetData;
extern "C" {
void fightOutPokemonLoadWazaEffect(FightOutPokemon* fop, u16 waza, u8 kind, u8 flag);
void fightOutPokemonWazaEffect(FightOutPokemon* fop, s32 a, s32 b, u8 close, void* buff);
u16 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
void battleGridReplacePokemon(Sequence* oldSeq, Sequence* newSeq);
void battleGridUpdate(void);
void fightOutPokemon_SetSequencePtr(FightOutPokemon* fop, Sequence* value);
void Sequence_Free(void*);
FightTargetData* fightTargetDataBiosGetPtr(u16 index);
void* fightTargetDataBiosGetBuff(FightTargetData* data);
Sequence* fightOutPokemonCreateSequence(FightOutPokemon* fop, u16 tenki, s8 rare);

void fightSeqFightEffect(u8 side, u8 effect, u16 arg) {
    Sequence* oldSeq;
    u8 type = fightFloor_GetFightType(0);
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(side, 0);
    FightOutPokemon* defender;
    FightOutPokemon* attacker;
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    u8 kind = UserWork[0x1601E] & 0xF;
    u8 amount = UserWork[0x1601E] & 0xF0;
    if (effect == 0x11 || (u32)(effect - 1) <= 1 || effect == 0x1A) {
        if (effect == 1) {
            u16 id;
            if (ServerWork) {
                volatile s16 rf_t = ServerWork[3];
                switch (rf_t) {
                case 15:
                case 18:
                    id = 0x26;
                    break;
                case 16:
                case 19:
                case 21:
                    id = 0x28;
                    break;
                case 17:
                    id = 0x2A;
                    break;
                case 20:
                    id = 0x2C;
                    break;
                case 22:
                case 25:
                    id = 0x27;
                    break;
                case 23:
                case 26:
                case 28:
                    id = 0x29;
                    break;
                case 24:
                    id = 0x2B;
                    break;
                case 27:
                    id = 0x3C;
                    break;
                    id = _fightSeqFightEffectStatusUpDown(amount, kind);
                    break;
                default:
                    id = _fightSeqFightEffectStatusUpDown(amount, kind);
                    break;
                }
            } else {
                id = _fightSeqFightEffectStatusUpDown(amount, kind);
            }
            fightSeqFightOutPokemonEffect(id, p, 0, 1);
        }
        if (effect == 0x1A) {
            fightSeqFightOutPokemonEffect(0x2D, p, 0, 1);
        }
        if (effect == 0x11) {
            fightOutPokemonLoadWazaEffect(p, 0x121, 1, 0);
            fightOutPokemonLoadWazaEffect(attacker, 0x121, 2, 0);
            fightOutPokemonWazaEffect(p, 0x121, 1, 1, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            fightOutPokemonWazaEffect(attacker, 0x121, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
        }
        if (effect == 2) {
            fightWazaWzxTypeFuncMigawari(0xA4, p, p, 0, 0);
        }
        return;
    }
    if (ServerStatusFlag & 0x80) {
        fightSeq_CallWazaSeq(WAZA_Wait);
        return;
    }
    if ((effect - 0xA) <= 3 || effect == 0x25 || (u32)(effect - 0x20) <= 2 || effect == 0x1E) {
        if (effect == 0xA) {
            fightOutPokemonLoadWazaEffect(p, 0xF0, 1, 0);
            fightOutPokemonWazaEffect(p, 0xF0, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
        if (effect == 0xB) {
            fightOutPokemonLoadWazaEffect(p, 0xF1, 1, 0);
            fightOutPokemonWazaEffect(p, 0xF1, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
        if (effect == 0xC) {
            fightOutPokemonLoadWazaEffect(p, 0xC9, 2, 0);
            fightOutPokemonWazaEffect(p, 0xC9, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
        if (effect == 0xD) {
            fightOutPokemonLoadWazaEffect(p, 0x102, 2, 0);
            fightOutPokemonWazaEffect(p, 0x102, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
        if (effect == 0x25) {
            fightOutPokemonLoadWazaEffect(p, 0x16F, 2, 0);
            fightOutPokemonWazaEffect(p, 0x16F, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
        if (effect == 0x20) {
            fightOutPokemonLoadWazaEffect(p, 0xF0, 1, 0);
            fightOutPokemonWazaEffect(p, 0xF0, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
        if (effect == 0x22) {
            fightOutPokemonLoadWazaEffect(p, 0xC9, 1, 0);
            fightOutPokemonWazaEffect(p, 0xC9, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
        if (effect == 0x21) {
            fightOutPokemonLoadWazaEffect(p, 0xF1, 1, 0);
            fightOutPokemonWazaEffect(p, 0xF1, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
        if (effect == 0x1E) {
            if (fightFloorGetNowTenkouDataId(0, 0) == 2) {
                fightSeqFightOutPokemonEffect(0x80, p, 0, 0);
            } else if (fightFloorGetNowTenkouDataId(0, 0) == 1) {
                fightSeqFightOutPokemonEffect(0x7F, p, 0, 0);
            } else if (fightFloorGetNowTenkouDataId(0, 0) == 3) {
                fightSeqFightOutPokemonEffect(0x7E, p, 0, 0);
            } else if (fightFloorGetNowTenkouDataId(0, 0) == 4) {
                fightSeqFightOutPokemonEffect(0x7D, p, 0, 0);
            } else if (fightFloorGetNowTenkouDataId(0, 0) == 5) {
                fightSeqFightOutPokemonEffect(0xDC, p, 0, 0);
            } else {
                fightSeqFightOutPokemonEffect(0x9D, p, 0, 0);
            }
        }
        return;
    }
    if (effect == 0x17) {
        fightSeqFightOutPokemonEffect(0x57, p, 0, 1);
    }
    if (effect == 0x1F) {
        fightSeqFightOutPokemonEffect(0x9D, p, 0, 0);
    }
    if (effect == 0x18) {
        fightSeqFightOutPokemonEffect(0x58, p, 0, 1);
    }
    if (effect == 0x23) {
        fightSeqFightOutPokemonEffect(0xA3, p, 0, 1);
    }
    if (effect == 0x24) {
        fightSeqFightOutPokemonEffect(0xD8, p, 0, 1);
    }
    if (effect == 0x19) {
        fightOutPokemonLoadWazaEffect(p, 1, 2, 0);
        fightOutPokemonWazaEffect(p, 1, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
    }
    if (effect == 0xE) {
        fightSeqFightOutPokemonEffect(0x38, p, 0, 1);
    }
    if (effect == 0x16) {
        fightOutPokemonLoadWazaEffect(p, 0x111, 3, 0);
        fightOutPokemonWazaEffect(p, 0x111, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
    }
    if (effect == 0x12) {
        fightOutPokemonLoadWazaEffect(p, 0xF8, 2, 0);
        fightOutPokemonWazaEffect(p, 0xF8, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
    }
    if (effect == 0x13) {
        fightOutPokemonLoadWazaEffect(defender, 0x161, 2, 0);
        fightOutPokemonWazaEffect(defender, 0x161, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
    }
    if (effect == 0x15) {
        fightSeqFightOutPokemonEffect(0x3B, p, 0, 1);
    }
    if (effect == 0x7) {
        fightSeqFightOutPokemonEffect(0x39, p, 0, 1);
    }
    if (effect == 0x1B) {
        fightSeqFightOutPokemonEffect(0x32, p, 0, 1);
    }
    if (effect == 0x1C) {
        fightOutPokemonLoadWazaEffect(p, 0x36, 3, 0);
        fightOutPokemonWazaEffect(p, 0x36, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
    }
    if (effect == 0x1D) {
        fightOutPokemonLoadWazaEffect(p, 0x74, 3, 0);
        fightOutPokemonWazaEffect(p, 0x74, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
    }
    if (effect == 9) {
        fightSeqFightOutPokemonEffect(0x86, p, 0, 1);
    }
    if (effect == 6) {
        u16 id = fightOutPokemonGetIdBuffJoutaiDataId(p, 0xE);
        fightOutPokemonLoadWazaEffect(p, id, 2, 0);
        fightOutPokemonWazaEffect(p, id, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
    }
    if (effect == 0x10) {
        if (fightOutPokemon_GetUseWazaDataId(p) == 0x157) {
            fightOutPokemonLoadWazaEffect(p, 0x157, 3, 0);
            fightOutPokemonWazaEffect(p, 0x157, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
        if (fightOutPokemon_GetUseWazaDataId(p) == 0xA8) {
            fightOutPokemonLoadWazaEffect(p, 0xA8, 3, 0);
            fightOutPokemonWazaEffect(p, 0xA8, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        }
    }
    if (effect == 0) {
        u32 tenki = fightFloorGetNowTenkouDataId(0, 1);
        oldSeq = fightOutPokemon_GetSequencePtr(p);
        Sequence* newSeq = fightOutPokemonCreateSequence(p, tenki, -1);
        u16 id;
        switch (tenki) {
        case 1:
            id = 0x84;
            break;
        case 2:
            id = 0x85;
            break;
        case 4:
            id = 0x82;
            break;
        case 3:
        default:
            id = 0x83;
            break;
        }
        Sequence_LoadWaza(oldSeq, 0x81, 4, 0);
        Sequence_LoadWaza(newSeq, id, 4, 0);
        fightMenuFightOutPokemonOpenStatusMenu(p, type, 1);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, p, type, 0, 1);
        fightSeqFightOutPokemonEffect(0x81, p, 1, 0);
        battleGridReplacePokemon(oldSeq, newSeq);
        battleGridUpdate();
        fightOutPokemon_SetSequencePtr(p, newSeq);
        fightSeqFightOutPokemonEffect(id, p, 0, 0);
        Sequence_Free(oldSeq);
    }
    if (effect == 0x14) {
        fightOutPokemonLoadWazaEffect(p, 0x75, 3, 0);
        fightOutPokemonWazaEffect(p, 0x75, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
    }
    if (effect == 0x26) {
        fightOutPokemonLoadWazaEffect(p, 0x164, 2, 0);
        fightOutPokemonWazaEffect(p, 0x164, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
    }
}
}

void WS_WAZA_EFFECT(void) {
    FightOutPokemon* attacker;
    FightOutPokemon* defender;
    void* waza;
    u32 wazaId;
    u8 counter;
    fightSeq_GetWazaSeq();
    fightFloor_GetFightType(0);
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    wazaId = fightOutPokemon_GetUseWazaDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightWazaIsHit(waza) == 1) {
        if ((ServerStatusFlag & 0x80) && wazaId != 0x90 && wazaId != 0xA4) {
            fightSeq_CallWazaSeq(WAZA_Wait);
        } else {
            fightWazaDoEffectFunc(wazaId, (u32)attacker, (u32)defender, UserWork[0x160a1]);
        }
        UserWork[0x16002] = UserWork[0x16002] + 1;
        counter = UserWork[0x160a1];
        UserWork[0x160a1] = counter + 1;
        fightSeq_NextWazaSeq(1);
        return;
    }
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightSeqFightOutPokemonEffect(0x57, defender, 0, 1);
    fightSeq_NextWazaSeq(1);
}

void WS_CONDCHG_CHECK(void) {
    WsCondChgCmd* cmd;
    FightOutPokemon* pokemon;
    u8 kind;
    u8 result;
    u8 status;
    result = 0;
    cmd = (WsCondChgCmd*)fightSeq_GetWazaSeq();
    pokemon = fightTargetGetPtrAsNowFightType(cmd->side, 0);
    kind = cmd->kind;
    s32 tmp2 = fightSeqCondChgActTypeToPokemonStatusId(cmd->type);
    status = pokemonGetStatus(pokemon, 0, tmp2, 0);
    {
    s8 rf_t = cmd->value;
    u8 value = rf_t;
    switch (kind) {
    case 0:
        if (status == value) result = 1;
        break;
    case 1:
        if (status != value) result = 1;
        break;
    case 2:
        if (status > value) result = 1;
        break;
    case 3:
        if (status < value) result = 1;
        break;
    case 4:
        if (status & value) result = 1;
        break;
    case 5:
        if (!(status & value)) result = 1;
        break;
    }
    }
    if (result != 0) {
        fightSeq_JumpWazaSeq(cmd->jump);
        return;
    }
    fightSeq_NextWazaSeq(9);
}

void WS_HP_DEC_WAIT(void) {
    s32 menu;
    FightOutPokemon* pokemon;
    u8 type = fightFloor_GetFightType(0);
    pokemon = fightTargetGetPtrAsNowFightType(((WsSideCmd*)fightSeq_GetWazaSeq())->side, 0);
    menu = fightMenuGetFightOutPokemonPtrToStatusMenuId(pokemon, type, 1);
    if (menuIsCheck(menu) == 1) {
        menuFightStatusWaitAnimeHP(menu, 1);
    }
    if (fightOutPokemonIsHinsi(pokemon) == 1) {
        fightOutPokemonSetWazaEffectDownFlag(pokemon, 1);
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x14) == 1 && fightOutPokemonGetJoutaiMigawariHp(pokemon) <= 0) {
        while (1) {
            if (wazaSequenceSysLastWazaIsImpactPoint(4) == 1) break;
            GSthreadSwitch();
        }
        fightOutPokemonInitJoutaiDataId(pokemon, 0x14);
        fightSeq_CallWazaSeq(WAZA_MigawariKizetsu);
        fightOutPokemonWriteJoutaiDataId(pokemon, 0x14, 0);
        fightOutPokemonSetBuffJoutaiDataId(pokemon, 0x14, 0);
    }
    fightSeq_NextWazaSeq(2);
}

extern "C" {
void WS_HP_DEC(void) {
    u8* seq = (u8*)fightSeq_GetWazaSeq();
    void* fw;
    FightOutPokemon* p;
    u8 type = fightFloor_GetFightType(0);
    u16 waza;
    FightOutPokemon* attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetUseWazaDataId(attacker);
    fw = fightOutPokemon_GetFightWazaPtr(attacker);
    int damage = fightWaza_GetDamage(fw);
    s32 hp;
    u32 hitDamage = fightWaza_GetHitDamage(fw);
    u16 zokusei = fightWaza_GetZokusei(fw);
    FightOutPokemon* defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    u8 kind;
    if (wazaCheckDarkWaza(waza) == 1) {
        kind = waza_GetZokuseiKindData(waza);
    } else {
        kind = zokuseiBiosGetWazaKind(zokusei);
        if (waza == 0xED) {
            kind = 1;
        }
    }
    if (fightWazaIsHit(fw) == 1) {
        p = fightTargetGetPtrAsNowFightType(seq[1], 0);
        void* pokemon = fightOutPokemonGetPokemonPtr(p);
        hp = pokemon_GetHp(pokemon);
        u32 maxHp = pokemon_GetMaxHp(pokemon);
        u16 migawari = fightOutPokemonGetJoutaiMigawariHp(p);
        if (migawari != 0 && !(ServerStatusFlag & 0x100)) {
            u32 left;
            if (migawari >= damage) {
                left = migawari - damage;
            } else {
                damage = migawari;
                left = 0;
            }
            s32 cmpv = fightOutPokemon_GetKaigaraDamageValue(p);
            if (cmpv == 0) {
                fightOutPokemon_SetKaigaraDamageValue(p, damage);
            }
            fightWaza_SetHitDamage(fw, damage);
            fightOutPokemonSetJoutaiMigawariHp(p, left);
            fightMenuOpenMsg(0x4E9C);
            fightMainWaitFrame(0x40);
            fightMenuCloseMsg();
        } else {
            u32 menu;
            ServerStatusFlag &= ~0x100;
            if (damage < 0) {
                hp = hp - damage;
                if (hp > (s32)maxHp) {
                    hp = maxHp;
                }
            } else {
                if (hp > damage) {
                    hitDamage = damage;
                    hp = hp - damage;
                } else {
                    hitDamage = hp;
                    hp = 0;
                }
                if (ServerStatusFlag & 0x20) {
                    ServerStatusFlag &= ~0x20;
                } else {
                    fightOutPokemon_SetGamanDamageValue(p, fightOutPokemon_GetGamanDamageValue(p) + damage);
                    if (seq[1] == 0x12) {
                        u16 tmp1 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(attacker, type);
                        fightOutPokemon_SetGamanDamageTargetId(p, tmp1);
                    } else {
                        fightOutPokemon_SetGamanDamageTargetId(p, fightTargetGetTragetPtrToRelativeHostSideFightTargetId(defender, type));
                    }
                    fightOutPokemonAddFightOutPokemonEnemyDamage(p, attacker, hitDamage);
                }
                if (fightOutPokemon_GetKaigaraDamageValue(p) == 0 && !(ServerStatusFlag & 0x100000)) {
                    fightOutPokemon_SetKaigaraDamageValue(p, hitDamage);
                }
                switch (kind) {
                case 1:
                    if (!(ServerStatusFlag & 0x100000) && waza != 0xDC) {
                        fightOutPokemon_SetDamageAtkValue(p, hitDamage);
                        fightOutPokemon_SetMyselfDamageAtkValue(p, hitDamage);
                        if (seq[1] == 0x12) {
                            u32 id = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(attacker, type);
                            fightOutPokemon_SetDamageAtkTargetId(p, id);
                            fightOutPokemon_SetMyselfDamageAtkTargetId(p, id);
                        } else {
                            u32 id = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(defender, type);
                            fightOutPokemon_SetDamageAtkTargetId(p, id);
                            fightOutPokemon_SetMyselfDamageAtkTargetId(p, id);
                        }
                    }
                    break;
                case 2:
                    if (!(ServerStatusFlag & 0x100000)) {
                        fightOutPokemon_SetDamageSpeValue(p, hitDamage);
                        fightOutPokemon_SetMyselfDamageSpeValue(p, hitDamage);
                        if (seq[1] == 0x12) {
                            u32 id = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(attacker, type);
                            fightOutPokemon_SetDamageSpeTargetId(p, id);
                            fightOutPokemon_SetMyselfDamageSpeTargetId(p, id);
                        } else {
                            u32 id = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(defender, type);
                            fightOutPokemon_SetDamageSpeTargetId(p, id);
                            fightOutPokemon_SetMyselfDamageSpeTargetId(p, id);
                        }
                    }
                    break;
                }
            }
            ServerStatusFlag &= ~0x100000;
            fightWaza_SetHitDamage(fw, hitDamage);
            pokemon_SetHp(pokemon, hp);
            fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x83);
            menu = fightMenuGetFightOutPokemonPtrToStatusMenuId(p, type, 1);
            if (menuIsCheck(menu) == 0) {
                fightMenuFightOutPokemonOpenStatusMenu(p, type, 1);
                fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, p, type, 0, 1);
            }
            fightMenuFightStatusStartAnimHP(menu, hp);
        }
    } else {
        FightOutPokemon* p = fightTargetGetPtrAsNowFightType(seq[1], 0);
        s32 cmpv = fightOutPokemon_GetKaigaraDamageValue(p);
        if (cmpv == 0) {
            fightOutPokemon_SetKaigaraDamageValue(p, 0xFFFF);
        }
    }
    fightSeq_NextWazaSeq(2);
}
}

void WS_WAZAKOUKA_SE(void) {
    void* waza;
    FightOutPokemon* attacker;
    u16 se = 0;
    fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    if (fightWazaIsJoutaiDataId(waza, 0x40) == 0) {
        if (fightFloor_GetEnvSndId(0) != 0) {
            if (fightWazaIsJoutaiDataId(waza, 0x41) == 1) {
                se = 0x540;
            } else if (fightWazaIsJoutaiDataId(waza, 0x42) == 1) {
                se = 0x541;
            } else if (fightWazaIsJoutaiDataId(waza, 0x43) == 1) {
                se = 0x542;
            } else if (fightWazaIsJoutaiDataId(waza, 0x45) == 1) {
                se = 0x543;
            } else {
                se = 0x544;
            }
        }
        if (se != 0) {
            GSsndPlayVolume(se, 0, 0xFF, 0);
        }
    }
    fightSeq_NextWazaSeq(1);
}

void WS_KIZETSU(void) {
    FightOutPokemon* pokemon;
    u8 type = fightFloor_GetFightType(0);
    pokemon = fightTargetGetPtrAsNowFightType(((WsSideCmd*)fightSeq_GetWazaSeq())->side, 0);
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x14) == 1 && fightOutPokemonGetJoutaiMigawariHp(pokemon) > 0) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x14);
        fightOutPokemonFreeAllSequenceWaza(pokemon);
        fightWazaWzxTypeFuncMigawari(0xA4, pokemon, pokemon, 0, 0);
        while (1) {
            if (wazaSequenceSysLastWazaIsImpactPoint(4) == 1) break;
            GSthreadSwitch();
        }
    }
    fightOutPokemonFreeAllSequenceWaza(pokemon);
    fightOutPokemonKizetuEffect(pokemon, 0);
    fightOutPokemonKizetuEffect(pokemon, 1);
    fightMenuFightOutPokemonOpenStatusMenu(pokemon, type, 1);
    fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, pokemon, type, 0, 1);
    fightSeq_NextWazaSeq(2);
}

extern u8 WAZA_KizetsuA[];
extern u8 WAZA_KizetsuD[];
extern u8 WAZA_KizetsuK[];
extern u8 WAZA_Onnen[];
extern u8 WAZA_Michidure[];
extern "C++" { static void _fightSeqHinshiFriendCalc(FightOutPokemon* p); }

extern "C" {
void WS_KIZETSU_CHECK(void) {
    void* pokemon;
    FightOutPokemon* attacker;
    void* fw;
    FightOutPokemon* fainted;
    u8* kizetsuSeq;
    FightOutPokemon* other;
    u8* seq = (u8*)fightSeq_GetWazaSeq();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
    if (seq[2] != 0) {
        FightOutPokemon* p = fightTargetGetPtrAsNowFightType(seq[1], 0);
        void* side = fightTargetGetPtrAsNowFightType(2, (u32)p);
        if (fightOutPokemonIsHinsi(p) == 1) {
            fightSide_SetMakibisiCheckFlag(side, 0);
            fightSeq_JumpWazaSeq(*(void**)(seq + 3));
            return;
        }
    } else {
        switch (seq[1]) {
        case 0x11:
            fainted = fightTargetGetPtrAsNowFightType(0x11, 0);
            fightOutPokemon_GetMotoFightPokemonPtr(fainted);
            other = fightTargetGetPtrAsNowFightType(0x12, 0);
            kizetsuSeq = WAZA_KizetsuA;
            break;
        case 0x12:
            fainted = fightTargetGetPtrAsNowFightType(0x12, 0);
            fightOutPokemon_GetMotoFightPokemonPtr(fainted);
            other = fightTargetGetPtrAsNowFightType(0x11, 0);
            kizetsuSeq = WAZA_KizetsuD;
            break;
        case 0x15:
            fainted = fightTargetGetPtrAsNowFightType(0x15, 0);
            fightOutPokemon_GetMotoFightPokemonPtr(fainted);
            other = fightTargetGetPtrAsNowFightType(0x11, 0);
            kizetsuSeq = WAZA_KizetsuK;
            break;
        default:
            fainted = 0;
            other = 0;
            kizetsuSeq = WAZA_KizetsuD;
            break;
        }
        if (fightOutPokemonIsHinsi(fainted) == 1) {
            FightOutPokemon* appoint;
            fightOutPokemon_SetKizetuFlag(fainted, 1);
            if (fightOutPokemonIsGcHeroFightOutPokemon(fainted) == 1) {
                ServerStatusFlag |= 0x400000;
                if (fightFloor_GetFightKindGetFriendFlag(0) == 1) {
                    _fightSeqHinshiFriendCalc(fainted);
                }
            }
            if (!(ServerStatusFlag & 0x01000000)) {
                FightOutPokemon* defender = fightTargetGetPtrAsNowFightType(0x12, 0);
                if (fightOutPokemonCheckWriteJoutaiDataId(defender, 0x28) == 1) {
                    FightOutPokemon* attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
                    pokemon = fightOutPokemonGetPokemonPtr(attacker);
                    void* fw = fightOutPokemon_GetFightWazaPtr(attacker);
                    u16 use;
                    u16 moto;
                    moto = fightOutPokemon_GetMotoWazaDataId(attacker);
                    use = fightOutPokemon_GetUseWazaDataId(attacker);
                    if (fightOutPokemonIsAlly(attacker, defender) == 0 && fightOutPokemonCheckFightOut(attacker) == 1 &&
                        use != 0xA5 && wazaCheckDarkWaza(use) == 0) {
                        s8 slot = pokemonSearchWazaDataId(pokemon, moto);
                        if (slot < 0) {
                            slot = fightWaza_GetWazaBanme(fw);
                        }
                        pokemon_SetPokemonWazaPp(pokemon, slot, 0);
                        fightSeqPpdecMonomane(attacker, slot, 0);
                        fightSeqCheckSetHensinBuffToMotoPokemon2(attacker, 0x80, slot, 0);
                        fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(pokemon_GetPokemonWazaDataId(pokemon, slot))));
                        fightSeq_CallWazaSeq(WAZA_Onnen);
                    }
                }
            }
            if (ServerStatusFlag & 0x40) {
                attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
                if (fightOutPokemonCheckFightOut(attacker) == 1) {
                    FightWazaCopy backup;
                    fw = fightOutPokemon_GetFightWazaPtr(attacker);
                    fightWazaBiosCopy(&backup, fw);
                    fightWaza_SetDamage(fw, pokemon_GetHp(fightOutPokemonGetPokemonPtr(other)));
                    fightWazaInitJoutai(fw);
                    fightSeq_CallWazaSeq(WAZA_Michidure);
                    fightWazaBiosCopy(fw, &backup);
                }
                ServerStatusFlag &= ~0x40;
            }
            appoint = (FightOutPokemon*)fightFloor_GetAppointPokemonPtr(0);
            fightFloor_SetAppointPokemonPtr(0, fainted);
            fightSeq_CallWazaSeq(kizetsuSeq);
            fightFloor_SetAppointPokemonPtr(0, appoint);
        }
    }
    fightSeq_NextWazaSeq(7);
}
}

void WS_TSUIKA_CHECK(void) {
    extern u32 wazaDB_GetAddFightKoukaAvg(u16 id);
    extern u16 HSD_Rand(void);
    enum TsE { TsE0 };
    FightOutPokemon* attacker;
    void* waza;
    u16 wazaId;
    enum TsE chance;
    u32 base;
    fightSeq_GetWazaSeq();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    wazaId = fightOutPokemon_GetUseWazaDataId(attacker);
    if ((u16)fightOutPokemonGetTokuseiDataId(attacker) == 0x20) {
        base = (u8)wazaDB_GetAddFightKoukaAvg(wazaId) * 2;
    } else {
        base = (u8)wazaDB_GetAddFightKoukaAvg(wazaId);
    }
    chance = (enum TsE)(base);
    if ((u16)dbgMenuFightGetTuikakoukaFlag() == 1) {
        chance = (enum TsE)(0x63);
    }
    if ((ServerWork[3] & 0x80) && (u16)fightWazaIsHit(waza) == 1) {
        ServerWork[3] &= 0x7F;
        fightSeqTuikaAct(0, 0x80);
    } else if ((ServerWork[3] & 0x80) && wazaId == 0x175 && lbl_804EB918 != 0) {
        ServerWork[3] &= 0x7F;
        fightSeqTuikaAct(0, 0x80);
    } else if ((s32)(HSD_Rand() % 100) < (s32)(u16)chance && ServerWork[3] != 0 && (u16)fightWazaIsHit(waza) == 1) {
        if ((u16)chance >= 100) {
            fightSeqTuikaAct(0, 0x80);
        } else {
            fightSeqTuikaAct(0, 0);
        }
    } else {
        fightSeq_NextWazaSeq(1);
    }
    ServerWork[3] = 0;
    fight_seq_server_work3_temp = 0;
}

void WS_PP_DEC(void) {
    enum TsE { TsE0 };
    void* waza;
    void* pokemon;
    u8 dec = 1;
    FightOutPokemon* attacker;
    FightOutPokemon* defender;
    enum TsE tokusei;
    u8 range;
    s8 slot;
    u8 pp;
    fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    pokemon = fightOutPokemonGetPokemonPtr(attacker);
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    tokusei = (enum TsE)(fightOutPokemonGetTokuseiDataId(defender));
    if (!(ServerStatusFlag & 0xA00)) {
        range = wazaDB_GetRangeId(fightOutPokemon_GetUseWazaDataId(attacker));
        slot = fightWaza_GetWazaBanme(waza);
        pp = pokemon_GetPokemonWazaPp(pokemon, slot);
        if (fightOutPokemon_GetNoPressureFlag(attacker) == 0) {
            switch (range) {
            case 6:
                dec = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(0, 0x2E, 0, attacker) + 1;
                break;
            case 7:
            case 4:
                dec = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(0, 0x2E, 2, attacker) + 1;
                break;
            default:
                if (attacker != defender && tokusei == 0x2E) {
                    dec = 2;
                }
                break;
            }
        }
        if (pp != 0) {
            fightOutPokemon_SetPassPpdecFlag(attacker, 1);
            pokemon_SetPokemonWazaPp(pokemon, slot, pp > dec ? pp - dec : 0);
            fightSeqPpdecMonomane(attacker, slot, 0);
        }
    }
    ServerStatusFlag &= 0xFFFFF7FF;
    fightSeq_NextWazaSeq(1);
}

void WS_ATTACK_MESSAGE2(void) {
    enum TsE { TsE0 };
    enum TsE type = (enum TsE)(fightFloorGetStatus(0, 0, 0x14, 0));
    int seq;
    u16 waza;
    FightOutPokemon* attacker;
    void* active;
    u8 msg;
    fightSeq_GetWazaSeq();
    if (!(ServerStatusFlag & 0x600)) {
        attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
        fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, attacker);
        fightOutPokemonGetNicknamePtr(attacker);
        waza = fightOutPokemonGetUseWazaDataId(attacker);
        seq = pokemonGetStatus(attacker, 0, 0xEE, 0);
        fightSeqFightOutPokemonEffect(0x9E, attacker, 0, 1);
        fightMenuFightOutPokemonOpenStatusMenu(attacker, type, 1);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, attacker, type, 0, 1);
        msg = fightMenuWazaOutMsg((u32)attacker, waza);
        if (seq != 0) {
            active = Sequence_GetWaza((void*)seq, 0x9E, 4);
            while (WazaSequence_IsActive((WazaSequence*)active) != 0) {
                GSthreadSwitch();
            }
            WazaSequence_Free((WazaSequence*)active);
        } else {
            fightSeq_CallWazaSeq(WAZA_Wait);
        }
        if (msg == 1) {
            fightMenuCloseMsg();
        }
        fightMenuFightOutPokemonCloseStatusMenu(attacker, type, 0);
        ServerStatusFlag |= 0x400;
    }
    fightSeq_NextWazaSeq(1);
    ServerWork[7] = 0;
}

extern u8 lbl_804EB918;

extern "C" {
void WS_HITCHECK(void) {
    u8 type = fightFloor_GetFightType(0);
    u8* seq = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* attacker;
    u16 waza;
    waza = *(u16*)(seq + 5);
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    u16 targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(attacker, type);
    void* fw = fightOutPokemon_GetFightWazaPtr(attacker);
    volatile u32 atkTokusei = fightOutPokemonGetTokuseiDataId(attacker);
    FightOutPokemon* defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    u32 defTokusei = fightOutPokemonGetTokuseiDataId(defender);
    u32 soubi = fightOutPokemonGetSoubiItemSoubiDataId(defender);
    s32 buff = figthOutPokemonGetSoubiItemBuff(defender);
    u8 tenkou = fightFloorGetNowTenkouDataId(0, 1);
    if (waza == 0xFFFF || waza == 0xFFFE) {
        if (waza == 0xFFFF && fightOutPokemonIsJoutaiDataId(defender, 0x1D) == 1 &&
            targetId == fightOutPokemonGetUserFightTargetIdJoutaiDataId(defender, 0x1D)) {
            fightSeq_NextWazaSeq(7);
        } else if (fightOutPokemonIsJoutaiKie(defender) != 0) {
            fightSeq_JumpWazaSeq(*(void**)(seq + 1));
        } else if (fightSeqGuardCheck(7, 0) == 0) {
            fightSeq_NextWazaSeq(7);
        }
    } else {
        u16 zokusei;
        u8 kind;
        u8 range;
        if (waza == 0) {
            waza = fightOutPokemon_GetUseWazaDataId(attacker);
            zokusei = fightOutPokemonGetWazaZokuseiDataId(attacker);
        } else {
            zokusei = wazaDB_GetZokuseiDataId(waza);
        }
        if (wazaCheckDarkWaza(waza) == 1) {
            kind = waza_GetZokuseiKindData(waza);
        } else {
            kind = zokuseiBiosGetWazaKind(zokusei);
        }
        range = wazaDB_GetRangeId(waza);
        if (fightSeqRegulationCheck((s32)waza, (u32)attacker, (u32)defender) == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x45);
            fightSeq_JumpWazaSeq(*(void**)(seq + 1));
        } else if (fightSeqGuardCheck(7, (u16)waza) == 0 && fightSeqWazaFloorJoutaiCheck(attacker, defender, waza) == 0) {
            s8 average = fightOutPokemon_GetAbicntAverage(attacker);
            volatile s8 avoid = fightOutPokemon_GetAbicntAvoid(defender);
            volatile s8 cnt = average + (12 - avoid) - 6;
            s8 abicnt;
            u16 avg;
            u16 hit;
            if (fightOutPokemonIsJoutaiDataId(defender, 0x19) == 1) {
                cnt = average;
            }
            abicnt = fightAbicntFitMinMax(cnt);
            avg = wazaDB_GetAvg((s32)waza);
            if (tenkou == 1 && wazaDB_GetSeqId(waza) == 0x98) {
                avg = 50;
            }
            hit = avg * fightWazaHitKakurituDataBiosGetKake(fightWazaHitKakurituDataBiosGetPtr(abicnt));
            hit /= fightWazaHitKakurituDataBiosGetWaru(fightWazaHitKakurituDataBiosGetPtr(abicnt));
            if (atkTokusei == 0xE) {
                hit = (hit * 130) / 100;
            }
            if (tenkou == 3 && defTokusei == 8) {
                hit = (hit * 80) / 100;
            }
            if (atkTokusei == 0x37 && kind == 1) {
                hit = (hit * 80) / 100;
            }
            if (soubi == 0x16) {
                hit = (hit * (100 - buff)) / 100;
            }
            if ((s32)((u16)HSD_Rand() % 100 + 1) > (s32)hit) {
                u8 prev;
                if (fightWazaCheckWriteJoutaiDataId(fw, 0x40) == 2) {
                    fightWazaWriteJoutaiDataId(fw, 0x40, 0);
                }
                if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && (range == 4 || range == 6 || range == 2)) {
                    ServerWork[6] = 2;
                } else {
                    ServerWork[6] = 0;
                }
                prev = ServerWork[6];
                fightSeqTypeCheck(0, 0, 0, 1, 7);
                if (ServerWork[6] == 3 && (prev == 2 || prev == 0) && fightWazaIsJoutaiDataId(fw, 0x43) == 0) {
                    ServerWork[6] = prev;
                }
            } else if (waza == 0x175) {
                lbl_804EB918 = 1;
            }
            fightSeqWazaSeqSet(7, waza);
        }
    }
}
}

u8 fightSeqBadgeCheck(FightOutPokemon* p) {
    void* trainer;
    fightFloor_GetFightType(0);
    fightOutPokemonGetPokemonPtr(p);
    fightTargetGetPtrAsNowFightType(2, (u32)p);
    fightOutPokemon_GetFightWazaPtr(p);
    figthOutPokemonGetLevel(p);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, p);
    if (trainer == 0) {
        return 0;
    }
    fightTargetGetPtrAsNowFightType(9, (u32)trainer);
    fightTrainer_GetHeroPtr((u8*)trainer);
    fightOutPokemon_GetUseWazaDataId(p);
    fightOutPokemonGetSoubiItemDataId(p);
    fightOutPokemonGetSoubiItemSoubiDataId(p);
    pokemon_GetSeikaku(fightOutPokemonGetPokemonPtr(p));
    return 0;
}

extern "C" {
FightOutPokemon* fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(FightOutPokemon* p);
FightOutPokemon* fightSeqSelectDefensePokemonPtr(FightOutPokemon* p, u16 waza, u32 type,
                                                 FightOutPokemon* (*select)(FightOutPokemon*, u16, u32), u8 random,
                                                 u8 special, s8 rangeOverride) {
    u8 count;
    u8 range;
    u32 zokusei;
    FightOutPokemon* result = 0;
    u16 hiraishin;
    if (rangeOverride < 0) {
        range = wazaDB_GetRangeId(waza);
    } else {
        range = rangeOverride;
    }
    if (waza == 0xAE && fightOutPokemonIsZokuseiDataId(p, 7) == 0) {
        range = 5;
    }
    zokusei = wazaDB_GetZokuseiDataId(waza);
    count = fightFloorGetValidFightOutPokemonCount(0, 0, p, 1);
    hiraishin = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(0, 0x1F, 2, p);
    switch (range) {
    case 0:
        if (count >= 2) {
            if (random == 1) {
                if (select) {
                    result = select(p, waza, type);
                } else {
                    result = fightFloorGetFightOutPokemonPtrRandom(0, 1, 2, p);
                }
            } else {
                result = fightTargetGetPtrAsNowFightType(0x12, 0);
            }
            if (special == 1) {
                volatile u16 tokusei = fightOutPokemonGetTokuseiDataId(result);
                FightOutPokemon* konoyubi = fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(p);
                if (konoyubi) {
                    result = konoyubi;
                } else if (tokusei != 0x1F && zokusei == 0xD && hiraishin != 0) {
                    result = fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(0, 0x1F, 1, 2, p);
                    fightOutPokemon_SetReceivesWazaHiraishinFlag(result, 1);
                }
            }
        } else if (random == 1) {
            result = fightFloorGetFightOutPokemonPtrRandom(0, 1, 3, p);
        }
        break;
    case 1:
    case 4:
    case 6:
    case 7:
        if (random == 1) {
            result = (FightOutPokemon*)fightTargetGetPtr(0xF, p, type);
            if (fightOutPokemonCheckFightOut(result) == 0) {
                result = fightTargetGetPtrAsNowFightType(0xE, (u32)result);
            }
        }
        break;
    case 5:
        result = random != 1 ? result : p;
        break;
    default:
        if (random == 1) {
            result = fightFloorGetFightOutPokemonPtrRandom(0, 1, 2, p);
        }
        break;
    }
    return result;
}
}

FightOutPokemon* fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(FightOutPokemon* p) {
    FightOutPokemon* t;
    void* side = fightTargetGetPtrAsNowFightType(3, (u32)p);
    FightOutPokemon* result;
    u8 type;
    u16 id;
    type = fightFloor_GetFightType(0);
    result = 0;
    if (fightSideIsJoutaiDataId(side, 0x4D) == 1 && (id = fightSideGetJoutaiUserFightTargetId(side, 0x4D)) != 0) {
        t = (FightOutPokemon*)fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(id, type);
        if (t != 0 && fightOutPokemonCheckFightOut(t) == 1) {
            result = t;
        }
    }
    return result;
}

}

static void fightSeqWsBadgeCheckYokodori(FightOutPokemon* p) {
    YokodoriData data;
    data.attacker = p;
    data.found = 0;
    fightFloorLoopValidFightOutPokemon(0, (void*)_fightSeqWsBadgecheckSubYokodori, &data, 1);
    FightOutPokemon* found = data.found;
    if (found != 0) {
        void* mine = fightOutPokemon_GetFightWazaPtr(p);
        void* theirs = fightOutPokemon_GetFightWazaPtr(found);
        if (theirs != 0 && mine != 0) {
            u16 moto = fightWaza_GetUseWazaDataId(theirs);
            fightWazaBiosCopy(theirs, mine);
            fightWaza_SetMotoWazaDataId(theirs, moto);
        }
    }
}

static s32 _fightSeqWsBadgecheckSubYokodori(void* p, u16 idx, void* data) {
    FightOutPokemon* target = (FightOutPokemon*)p;
    YokodoriData* d = (YokodoriData*)data;
    FightOutPokemon* attacker = d->attacker;
    u8 yokodori = wazaDB_GetYokodori(fightOutPokemon_GetUseWazaDataId(attacker));
    if (fightOutPokemonCheckFightOut(target) == 0) {
        return 1;
    }
    if (fightOutPokemonIsJoutaiDataId(target, 0x33) == 1 && yokodori == 1) {
        fightSeqPressurePpdecCheck(attacker, target, 0x121);
        fightOutPokemonInitJoutaiDataId(target, 0x33);
        fightFloor_SetAppointPokemonPtr(0, target);
        fightSeq_CallWazaSeq(WAZA_Yokodori);
        d->found = target;
    }
    return 1;
}

extern "C" {

void WS_EFFECT_WAIT(void) {
    void* waza;
    u32 impact;
    void* cmd;
    FightOutPokemon* attacker;
    u16 wazaId;
    FightOutPokemon* defender;
    u32 defTrainer;
    u8* seqTrainer;
    Sequence* seq;
    cmd = fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    wazaId = fightOutPokemon_GetUseWazaDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    defTrainer = (u32)fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, defender);
    seqTrainer = (u8*)fightTrainer_GetSequencePtr((u8*)defTrainer);
    seq = fightOutPokemon_GetSequencePtr(defender);
    if (!(ServerStatusFlag & 0x80) || wazaId == 0x90 || wazaId == 0xA4) {
        impact = ((u8*)cmd)[1];
        while (1) {
            if (wazaSequenceSysLastWazaIsImpactPoint(impact) == 1) break;
            GSthreadSwitch();
        }
        if (impact == 0 && fightWaza_GetDamage(waza) > 0 && fightWazaIsHit(waza) == 1 &&
            defTrainer != (u32)fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, attacker) && seqTrainer != 0) {
            if (seqTrainer[0x61] != 0) {
                *(Sequence**)(seqTrainer + 0x78) = seq;
            }
            ((ModelSequence*)seqTrainer)->DoModelAnimation(4);
        }
    }
    if (impact == 3 || impact == 4) {
        fightMenuAllFightOutPokemonCloseStatusMenu(0);
        if (seqTrainer != 0 && seqTrainer[0x61] != 0) {
            *(Sequence**)(seqTrainer + 0x78) = 0;
        }
    }
    if (fightOutPokemon_GetUseWazaDataId(attacker) == 0xE2 && fightFloorIsUseFightTimerCommand(0) == 1) {
        fightTimerCommandInit();
        fightTimerCommandStart();
    }
    fightSeq_NextWazaSeq(2);
}

void WS_DAMAGE_CALC(void) {
    FightOutPokemon* attacker;
    FightOutPokemon* defender;
    void* side;
    u16 wazaId;
    void* waza;
    u16 power;
    u16 type;
    s32 damage;
    fightFloorBiosGetFightFloorPtr();
    fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    side = fightTargetGetPtrAsNowFightType(2, (u32)defender);
    wazaId = fightOutPokemon_GetUseWazaDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    power = fightWaza_GetIryoku(waza);
    type = fightWaza_GetZokusei(waza);
    damage = fightSeqWazaDamageCalc(attacker, defender, (FightOutPokemon*)side, wazaId, power, (u16)type);
    damage = damage * fightWaza_GetCritical(waza);
    damage = damage * fightWaza_GetDamageValue(waza);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x24) == 1 && type == 0xD) {
        damage *= 2;
    }
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x32) == 1) {
        damage = damage * 15 / 10;
    }
    if (wazaCheckDarkWaza(wazaId) == 1) {
        if (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(defender)) == 1) {
            damage = damage * 5 / 10;
            if (fightWazaCheckWriteJoutaiDataId(waza, 0x42) == 2) {
                fightWazaWriteJoutaiDataId(waza, 0x42, 0);
            }
        } else {
            damage *= 2;
            if (fightWazaCheckWriteJoutaiDataId(waza, 0x41) == 2) {
                fightWazaWriteJoutaiDataId(waza, 0x41, 0);
            }
        }
    }
    fightWaza_SetDamage(waza, damage);
    fightSeq_NextWazaSeq(1);
}

void WS_ZENMETSU_CHECK(void) {
    bool flag = ((WsZenmetuCheckCmd*)fightSeq_GetWazaSeq())->flag;
    FightOutPokemon* attacker;
    void* side;
    u32 trainerNum;
    u32 entryNum;
    u16 wazaId;
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    wazaId = fightOutPokemon_GetUseWazaDataId(attacker);
    trainerNum = fightFloor_GetFightTypeTrainerNum(0);
    entryNum = fightFloor_GetFightTypeEntryPokemonNum(0);
    side = fightTargetGetPtrAsNowFightType(5, 0);
    if (fightSideGetFightPokemonNokoriHp(side, trainerNum, entryNum) == 0) {
        fightFloorSetFightResultId(0, 2);
    }
    side = fightTargetGetPtrAsNowFightType(4, 0);
    if (fightSideGetFightPokemonNokoriHp(side, trainerNum, entryNum) == 0) {
        fightFloorSetFightResultId(0, 3);
    }
    if (fightGetFightResultId() != 0) {
        if (fightSeqRegulationZenmetuCheck(wazaId) == 1 && fightGetFightResultId() == 7) {
            void* mine;
            fightFloorSetFightResultId(0, 0);
            mine = fightTargetGetPtrAsNowFightType(2, (u32)attacker);
            if (fightTargetGetPtrAsNowFightType(4, 0) == mine) {
                fightFloorSetFightResultId(0, 3);
            } else {
                fightFloorSetFightResultId(0, 2);
            }
        }
    } else if (flag == 1) {
        if (fightFloorIsIrekaeFightOutPokemon(0) != 0) {
            fightMainDebugMenu();
            if (fightGetFightResultId() != 0) {
                fightSeq_NextWazaSeq(5);
                return;
            }
            if (fightFloorIsUseFightTimerCommand(0) == 1) {
                fightTimerCommandInit();
                fightTimerCommandStart();
            }
            fightMainAllCamera(0, 0);
            fightFloorLoopValidFightTrainer(0, (void*)_fightSeqZenmetuCheckSubFightTrainer, 0, 1);
            fightMenuCloseInfoMenu(0);
            if (fightFloorIsUseFightTimerCommand(0) == 1) {
                fightTimerCommandBlock();
                fightTimerCommandTerminate();
            }
            if (fightGetFightResultId() != 0) {
                fightSeq_NextWazaSeq(5);
                return;
            }
        }
        fightFloorLoopValidFightOutPokemon(0, (void*)_fightSeqZenmetuCheckSubFightOutPokemon, 0, 0);
    }
    fightSeq_NextWazaSeq(5);
}

u8 fightSeqRegulationCheck(u32 waza, u32 arg1, u32 arg2) {
    u8 flag = fightFloor_GetFightKindRegulationFlag(0);
    u8 swap = menuCBRule_EnableSkillSwap();
    u8 michidure = menuCBRule_EnableSkill_Michidure();
    u8 sonic = menuCBRule_EnableSkill_SonicBoom();
    u8 sleep = menuCBRule_EnableSbToSleep();
    menuCBRule_EnableSbToIceed();
    if (flag == 1) {
        switch ((u16)waza) {
        case 0x11D:
            if (swap != 1) {
                return 1;
            }
            break;
        case 0xC3:
        case 0xC2: {
            void* side = fightTargetGetPtrAsNowFightType(2, arg1);
            u8 trainerNum = fightFloor_GetFightTypeTrainerNum(0);
            if (fightSideGetNokoriFightPokemonNum(side, trainerNum, fightFloor_GetFightTypeEntryPokemonNum(0)) <= 1 && michidure != 1) {
                return 1;
            }
            break;
        }
        case 0x52:
        case 0x31:
            if (sonic != 1) {
                return 1;
            }
            break;
        default:
            if ((s16)wazaDB_GetSeqId(waza) == 1) {
                u16 count = fightSeqRegulationGetJoutaiCount(8, arg2);
                if (sleep != 1 && count >= 1) {
                    return 1;
                }
            }
            break;
        }
    }
    return 0;
}

}

static s32 _fightSeqZenmetuCheckSubFightOutPokemon(void* p, u16 idx, void* data) {
    FightOutPokemon* pokemon = (FightOutPokemon*)p;
    void* motoFight;
    void* fight;
    void* motoPoke;
    void* buff;
    u8 kizetu;
    u8 hokaku;
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    fightFloorGetFightOutPokemonPtrToHeroPtr(0, pokemon);
    motoFight = fightOutPokemon_GetMotoFightPokemonPtr(pokemon);
    fight = fightOutPokemon_GetFightPokemonPtr(pokemon);
    motoPoke = fightPokemon_GetMotoPokemonPtr(motoFight);
    buff = fightPokemon_GetPokemonBuffPtr(motoFight);
    kizetu = fightOutPokemon_GetKizetuFlag(pokemon);
    hokaku = fightPokemon_GetHokakuFlag(fight);
    if (fightOutPokemonCheckFightOut(pokemon) == 0) {
        if (fightOutPokemon_GetIrekaeTargetEntryId(pokemon) < 0) {
            if (kizetu == 1) {
                fightOutPokemonInit(pokemon);
            }
            if (hokaku == 1) {
                pokemonInit(motoPoke);
                pokemonInit(buff);
                fightPokemonInit(motoFight);
                fightPokemonInit(fight);
                fightOutPokemonInit(pokemon);
            }
        } else {
            fightFloor_SetIrekaePokemonPtr(0, pokemon);
            fightFloor_SetKizetuPokemonPtr(0, pokemon);
            if (hokaku == 1) {
                pokemonInit(motoPoke);
                pokemonInit(buff);
                fightPokemonInit(motoFight);
                fightPokemonInit(fight);
            }
            fightSeq_CallWazaSeq(WAZA_MineReshuffleStart);
        }
    }
    return 1;
}

static s32 _fightSeqZenmetuCheckSubFightTrainer(void* p, u16 idx, void* data) {
    enum TsE { TsE0 };
    u8* trainer = (u8*)p;
    FightOutPokemon* fop;
    enum TsE num;
    u16 i;
    if ((u16)fightGetFightResultId() != 0) {
        return 1;
    }
    if ((u16)fightTrainerCheckValid(trainer) == 0) {
        return 1;
    }
    num = (enum TsE)(fightFloor_GetFightTypeFightoutPokemonNum(0));
    for (i = 0; i < num;) {
        fop = (FightOutPokemon*)fightTrainer_GetFightoutPokemonPtr(trainer, i);
        if (fop != 0 && (u16)fightOutPokemonCheckFightOut(fop) != 1 && (u16)fightOutPokemon_GetIrekaetaFlag(fop) != 1) {
            u16 found = 0;
            if ((u16)fightTrainerSearchIrekaeFightPokemon(trainer, &found) != 0) {
                s16 entry = -1;
                void* fp = 0;
                if ((u16)fightOutPokemonCheckValid(fop) == 0) {
                    void* cand = fightTrainer_GetFightPokemonPtr(trainer, fightTrainerGetFightOutPokemonToTemotiBanme(trainer, fop));
                    if ((u16)fightPokemonCheckFightOut(cand) == 1) {
                        fp = cand;
                        entry = fightPokemon_GetEntryId(cand);
                    }
                }
                if (fp == 0) {
                    entry = fightTrainerSelectIrekaeFightPokemon(trainer, idx, 0, (u32)fop);
                    if (entry < 0) {
                        if (entry == -2) {
                            fightFloorSetTuusinErrorFightResult(0);
                        }
                        continue;
                    }
                    fightTrainerGetEntryIdToFightPokemonPtr(trainer, entry);
                }
                if ((u16)fightOutPokemonCheckValid(fop) == 0) {
                    fightOutPokemonCreate(fop, fightTrainer_GetFightPokemonPtr(trainer, fightTrainerGetFightOutPokemonToTemotiBanme(trainer, fop)), 0);
                    fightOutPokemon_SetKizetuFlag(fop, 1);
                }
                fightOutPokemon_SetIrekaeTargetEntryId(fop, (u8)entry);
                fightOutPokemon_SetIrekaetaFlag(fop, 1);
            }
        }
        i++;
    }
    return 1;
}

extern void* get_exp_fight_pokemon_ptr;
extern u8 old_menu_lvup_status[];
extern u8 WAZA_LevelUp[];
extern "C" {
void soundPlayWait(u32 id);

void WS_GET_EXP(void) {
    u32 bgm;
    void* hero;
    u8 fightType = fightFloor_GetFightType(0);
    u8 cameraSet = 0;
    u32 exp;
    FightOutPokemon* target = fightTargetGetPtrAsNowFightType(((u8*)fightSeq_GetWazaSeq())[1], 0);
    volatile u16 monsId = figthOutPokemonGetPokemonDataId(target);
    u16 giveExp = pokemonDB_GetGiveExp(monsId);
    u8 level = figthOutPokemonGetLevel(target);

    if ((u16)fightOutPokemonIsGcHeroFightOutPokemon(target) != 1 && (u16)fightFloor_GetFightKindGetExpFlag(0) != 0) {
        void* side = fightTargetGetPtrAsNowFightType(3, (u32)target);
        if (fightSideCheckValid(side) && (u16)fn_80148688(target) != 1) {
            s32 metCount = 0;
            s32 shareCount = 0;
            u8 trainerNum = fightFloor_GetFightTypeTrainerNum(0);
            s32 i;
            s32 j;
            for (i = 0; i < trainerNum; i++) {
                void* trainer = fightSideGetValidFightTrainerPtr(side, i);
                if (trainer != 0 && fightTrainerCheckCanGetExp(trainer)) {
                    hero = fightTrainer_GetHeroPtr((u8*)trainer);
                    j = 0;
                    do {
                        void* fp = fightTrainerCheckTemotiPokemonFightEntry(trainer, (void*)heroGetStatus(hero, 3, j));
                        if (fp != 0 && fightPokemonCheckFightOut(fp)) {
                            if ((u16)fightOutPokemonCheckMeetEnemyFightPokemon(target, fp) == 1) {
                                metCount++;
                            }
                            if ((u16)fightPokemonGetSoubiItemSoubiDataId(fp) == 0x19) {
                                shareCount++;
                            }
                        }
                        j++;
                    } while (j < 6);
                }
            }

            if (metCount != 0 || shareCount != 0) {
                u32 expMet;
                u16 expShare;
                volatile u32 metExp;
                if (shareCount != 0) {
                    u16 half = ((giveExp * level) / 7) >> 1;
                    expMet = half / metCount;
                    expMet = expMet != 0 ? expMet : 1;
                    expShare = half / shareCount;
                    if (expShare == 0) {
                        expShare = 1;
                    }
                } else {
                    expMet = ((giveExp * level) / 7) / metCount;
                    if (expMet == 0) {
                        expMet = 1;
                    }
                    expShare = 0;
                }
                if ((u16)fightFloor_GetFightKind(0) == 0xC || (u16)fightFloor_GetFightKind(0) == 0xD) {
                    bgm = soundPauseBGMEX(0x32, 1);
                    GSsndPlayVolume(0x36A, 0, 0xFF, 0);
                    soundPlayWait(0x36A);
                    if (bgm) {
                        soundContinueBGMEX(bgm, 0x1F4, 1);
                    }
                }
                fn_8014718C(target, 1);
                metExp = expMet;

                for (s32 i_loop = 0; i_loop < trainerNum; i_loop++) {
                    void* trainer = fightSide_GetFightTrainerPtr(side, i_loop);
                    if (fightTrainerCheckCanGetExp(trainer)) {
                        void* hero = fightTrainer_GetHeroPtr((u8*)trainer);
                        j = 0;
                        do {
                            exp = 0;
                            void* fp = fightTrainerCheckTemotiPokemonFightEntry(trainer, (void*)heroGetStatus(hero, 3, j));
                            if (fp != 0 && fightPokemonCheckFightOut(fp) && (u16)figthPokemonGetLevel(fp) < 100) {
                                if ((u16)fightOutPokemonCheckMeetEnemyFightPokemon(target, fp) == 1) {
                                    exp = metExp;
                                }
                                if ((u16)fightPokemonGetSoubiItemSoubiDataId(fp) == 0x19) {
                                    exp += expShare;
                                }
                                if (exp != 0) {
                                    u32 msg;
                                    void* pokemon;
                                    if ((u16)fightPokemonGetSoubiItemSoubiDataId(fp) == 0x28) {
                                        exp = (exp * 150) / 100;
                                    }
                                    if ((u16)fightFloor_GetFightKindKeikentihueruFlag(0) == 1) {
                                        exp = (exp * 150) / 100;
                                    }
                                    if ((u16)fightTrainerIsMineFightPokemon(trainer, fp) == 0) {
                                        exp = (exp * 150) / 100;
                                        msg = 0x4E25;
                                    } else {
                                        msg = 0x4E24;
                                    }
                                    void* dc_PokemonGetPokemonPtr = fightPokemonGetPokemonPtr(fp);
                                    pokemon = dc_PokemonGetPokemonPtr;
                                    if ((u16)pokemonIsDarkPokemon(pokemon) == 1) {
                                        FightOutPokemon* fop;
                                        pokemonGetDarkPokemonLevel(pokemon);
                                        pokemon_SetPoolExp(pokemon, pokemon_GetPoolExp(pokemon) + (exp * 80) / 100);
                                        fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                        if (fop) {
                                            fightSeqCheckSetHensinBuffToMotoPokemon(fop, 0xC6);
                                        }
                                    } else {
                                        FightOutPokemon* fop;
                                        u32 opened;
                                        if (cameraSet == 0) {
                                            fightMainAllCamera(1, 0);
                                            cameraSet = 1;
                                        }
                                        fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                        if (fop) {
                                            fightMenuFightOutPokemonOpenStatusMenu(fop, fightType, 1);
                                            fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, fop, fightType, 0, 1);
                                        }
                                        fightMsgctrlSetValue(0xD, (u32)fightPokemonGetNicknamePtr(fp));
                                        fightMsgctrlSetValue(0xE, (u32)GSmsgGetGSchar(msg));
                                        fightMsgctrlSetValue(0x2F, exp);
                                        opened = fightMenuOpenMsg(0x4E23);
                                        fightMenuCloseMsg();
                                        fightPokemonGetEffortFromPokemon(fp, (void*)pokemonCheckInfectPokerus(dc_PokemonGetPokemonPtr, 0), monsId);
                                        while (1) {
                                            if (!(exp != 0 && fightPokemonCheckFightOut(fp))) {
                                                break;
                                            }
                                            u32 total;
                                            u32 now;
                                            u32 next;
                                            u8 lv = figthPokemonGetLevel(fp);
                                            if (lv >= 100) {
                                                break;
                                            }
                                            fightPokemonToMenuLvupStatus(fp, old_menu_lvup_status);
                                            get_exp_fight_pokemon_ptr = fp;
                                            now = figthPokemonGetExp(fp);
                                            next = fightPokemonGetLevelToExp(fp, lv + 1);
                                            total = now + exp;
                                            if (total - 24 >= next) {
                                                exp = total - next;
                                                fightPokemonGrowBasisStatus(fp, next);
                                                fightMsgctrlSetValue(0xD, (u32)fightPokemonGetNicknamePtr(fp));
                                                fightMsgctrlSetValue(0x2F, figthPokemonGetLevel(fp));
                                                if ((u16)fightFloor_GetFightKindGetFriendFlag(0) == 1 && (u16)fightTrainerIsGcHero(trainer) == 1) {
                                                    fightPokemonGetFriendFormPokemonFriendFilterId(fp, 0);
                                                }
                                                fightPokemon_SetLevelUpFlag(fp, 1);
                                                fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                                if (fop) {
                                                    if ((u16)fightOutPokemonIsUseHensinBuff(fop) == 1) {
                                                        fightOutPokemonSetHensinStatusAfterLevelUp(fop);
                                                    }
                                                    fightSeqCheckSetHensinBuffToMotoFightPokemon(fop, 0xD0);
                                                }
                                                fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                                if (fop) {
                                                    s32 menu = fightMenuGetFightOutPokemonPtrToStatusMenuId(fop, fightType, 0);
                                                    menuFightStatusStartAnimEXP(menu, next - fightPokemonGetLevelToExp(fp, lv));
                                                    menuFightStatusWaitAnimeEXP(menu, 1);
                                                    fightMenuFightOutPokemonRenewStatusMenu(fop, fightType, 1);
                                                }
                                                fightSeq_CallWazaSeq(WAZA_LevelUp);
                                                opened = 0;
                                            } else {
                                                exp = 0;
                                                figthPokemonSetExp(fp, total);
                                                fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                                if (fop) {
                                                    s16 menu = fightMenuGetFightOutPokemonPtrToStatusMenuId(fop, fightType, 0);
                                                    menuFightStatusStartAnimEXP(menu, total - fightPokemonGetLevelToExp(fp, lv));
                                                    fightMainWaitFrame(0x40);
                                                    menuFightStatusWaitAnimeEXP(menu, 1);
                                                    fightMenuFightOutPokemonRenewStatusMenu(fop, fightType, 1);
                                                }
                                            }
                                            get_exp_fight_pokemon_ptr = 0;
                                        }
                                        if ((u8)opened != 1) {
                                            fightMenuCloseMsg();
                                        }
                                        if (fightTrainerCheckFightPokemonFightOut(trainer, fp)) {
                                            fightMenuFightOutPokemonCloseStatusMenu(fop, fightType, 0);
                                        }
                                    }
                                }
                            }
                            j++;
                        } while (j < 6);
                    }
                }
            }
        }
    }
    fightSeq_NextWazaSeq(2);
}
}

extern "C" {

void fightSeqTuikaAct(u8 a, u8 b) {
    u8 out;
    _fightSeqTuikaActSub(a, b, &out);
    fightSeq_NextWazaSeq(out);
}

extern "C" {
u8 fightSeqWazaFloorJoutaiCheck(void* side, FightOutPokemon* target, u16 waza) {
    s32 waza_c = (s32)waza;
    u8 type = fightFloor_GetFightType(0);
    u16 id;
    wazaDB_GetSeqId(waza_c);
    fightFloorGetNowTenkouDataId(0, 1);
    id = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(side, type);
    if (fightOutPokemonIsJoutaiDataId(target, 0x1D) == 1 && fightOutPokemonGetUserFightTargetIdJoutaiDataId(target, 0x1D) == id) {
        fightSeqWazaSeqSet(7, waza);
        return 1;
    }
    if (!(ServerStatusFlag & 0x10000) && fightOutPokemonIsJoutaiDataId(target, 0x1F) == 1) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeqWazaSeqSet(7, waza);
        return 1;
    }
    {
        ServerStatusFlag &= 0xFFFEFFFF;
        u32 set = ServerStatusFlag & 0x20000;
        if (!set && fightOutPokemonIsJoutaiDataId(target, 0x20) == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
            fightSeqWazaSeqSet(7, waza);
            return 1;
        }
    }
    {
        ServerStatusFlag &= 0xFFFDFFFF;
        u32 set = ServerStatusFlag & 0x40000;
        if (!set && fightOutPokemonIsJoutaiDataId(target, 0x21) == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
            fightSeqWazaSeqSet(7, waza);
            return 1;
        }
    }
    ServerStatusFlag &= 0xFFFBFFFF;
    if (fightSeqIsTenkouHit(waza_c) == 1) {
        fightSeqWazaSeqSet(7, waza);
        return 1;
    }
    if (fightSeqIsAllwaysHit(waza_c) == 1) {
        fightSeqWazaSeqSet(7, waza);
        return 1;
    }
    return 0;
}
}

extern "C" {
void fightSeqWazaSeqSet(u8 arg, s32 flag) {
    FightOutPokemon* attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    void* waza = fightOutPokemon_GetFightWazaPtr(attacker);
    FightOutPokemon* defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightWazaIsHit(waza) == 0) {
        fightOutPokemon_SetHitWazaDataId(defender, 0);
        fightOutPokemon_SetHitWazaZokuseiDataId(defender, 9);
        fightSeq_JumpWazaSeq(fightSeq_GetWazaSeqPtr_u8(1));
        return;
    }
    fightSeqMichidureCheckAct();
    if (fightSeqFightOutPokemonTokuseiCheckWazaHit(attacker, defender, flag) == 0) {
        fightSeq_NextWazaSeq(arg);
    }
}

extern u8 WAZA_WazaEnd[];
extern u8 WAZA_PPNoneAttack[];
extern u8 WAZA_MagicCort[];
extern u8 WAZA_Hiraishin[];

extern "C" {
u8 fightSeqAttackPokemonJoutaiCheck(void);

#pragma dont_inline on
void WS_BADGECHECK(void) {
    FightOutPokemon* attacker;
    void* pokemon;
    FightOutPokemon* defender;
    u16 waza;
    fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    pokemon = fightOutPokemonGetPokemonPtr(attacker);
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightGetFightResultId() != 0) {
        ActionSeqNo = 2;
        return;
    }
    if (fightOutPokemonCheckFightOut(attacker) == 0 && !(ServerStatusFlag & 0x200)) {
        ServerStatusFlag |= 0x80000;
        fightSeq_JumpWazaSeq(WAZA_WazaEnd);
        return;
    }
    if (fightSeqAttackPokemonJoutaiCheck() == 0 && fightSeqFightOutPokemonTokuseiCheckWazaHitBefore(attacker, defender) == 0) {
        void* fw = fightOutPokemon_GetFightWazaPtr(attacker);
        waza = fightOutPokemon_GetUseWazaDataId(attacker);
        u8 mamoru = wazaDB_GetMamoru(waza);
        u8 majikku = wazaDB_GetMajikku(waza);
        s8 banme = fightWaza_GetWazaBanme(fw);
        u8 pp;
        u32 done;
        if (banme < 0 || waza == 0xA5 || wazaCheckDarkWaza(waza) == 1) {
            pp = 0;
        } else {
            pp = pokemon_GetPokemonWazaPp(pokemon, banme);
        }
        if (pp == 0 && waza != 0xA5 && wazaCheckDarkWaza(waza) == 0 && fightOutPokemonIsJoutaiDataId(attacker, 0x22) == 0 &&
            !(ServerStatusFlag & 0x800200)) {
            if (fightWazaCheckWriteJoutaiDataId(fw, 0x40) == 2) {
                fightWazaWriteJoutaiDataId(fw, 0x40, 0);
            }
            ServerStatusFlag |= 0x80000;
            fightSeq_JumpWazaSeq(WAZA_PPNoneAttack);
            return;
        }
        ServerStatusFlag &= ~0x800000;
        done = ServerStatusFlag & 0x02000000;
        if (!done && fightOutPokemonIsJoutaiDataId(attacker, 0x22) == 0) {
            int badge = fightSeqBadgeCheck(attacker);
            if (badge != 0) {
                if (badge == 2) {
                    ServerStatusFlag |= 0x02000000;
                    return;
                }
                if (fightWazaCheckWriteJoutaiDataId(fw, 0x40) == 2) {
                    fightWazaWriteJoutaiDataId(fw, 0x40, 0);
                }
                return;
            }
        }
        ServerStatusFlag |= 0x02000000;
        if (fightOutPokemonIsJoutaiDataId(defender, 0x37) == 1 && majikku == 1) {
            void* defFw;
            fightSeqPressurePpdecCheck(attacker, defender, 0x115);
            fightOutPokemonInitJoutaiDataId(defender, 0x37);
            defFw = fightOutPokemon_GetFightWazaPtr(defender);
            fightSeq_CallWazaSeq(WAZA_MagicCort);
            if (fw && defFw) {
                fightWazaBiosCopy(defFw, fw);
                fightWaza_SetMotoWazaDataId(defFw, waza);
            }
        } else {
            fightSeqWsBadgeCheckYokodori(attacker);
            if (fightOutPokemon_GetReceivesWazaHiraishinFlag(defender) == 1) {
                fightOutPokemon_SetReceivesWazaHiraishinFlag(defender, 0);
                fightSeq_CallWazaSeq(WAZA_Hiraishin);
            }
            if (fightOutPokemonIsJoutaiDataId(defender, 0x2B) == 1 && mamoru == 1) {
                if (waza == 0xAE && fightOutPokemonIsZokuseiDataId(attacker, 7) == 0) {
                    fightSeq_NextWazaSeq(1);
                    return;
                }
                if (fightSeqTameWazaCheck(waza) == 0 || fightOutPokemonIsJoutaiDataId(attacker, 0x22) == 1) {
                    fightOutPokemonInitJoutaiKeep(attacker);
                    fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
                    fightOutPokemon_SetHitWazaDataId(defender, 0);
                    fightOutPokemon_SetHitWazaZokuseiDataId(defender, 9);
                    ServerWork[6] = 1;
                    fightSeq_NextWazaSeq(1);
                    return;
                }
            }
        }
    }
    fightSeq_NextWazaSeq(1);
}
#pragma dont_inline reset
}
}

void figthSeqZokuseiCheckCalc(void* waza, u16 type, u16 wazaId, u8 apply) {
    s32 damage;
    u8 rate;
    u16 power;
    damage = fightWaza_GetDamage(waza);
    power = wazaDB_GetIryoku(wazaId);
    if ((fightWazaIsJoutaiDataId(waza, 0x43) != 1 || apply != 0) && type != 0x3F) {
        if (type == 0x43) {
            rate = 0;
        } else if (type == 0x42) {
            rate = 5;
        } else if (type == 0x41) {
            rate = 0x14;
        } else {
            return;
        }
        if (apply == 1) {
            s32 v = damage * rate / 10;
            if (v == 0 && rate != 0) {
                v = 1;
            }
            fightWaza_SetDamage(waza, v);
        }
        switch (rate) {
        case 0:
            if (fightWazaCheckWriteJoutaiDataId(waza, type) == 2) {
                fightWazaWriteJoutaiDataId(waza, type, 0);
            }
            fightWazaInitJoutaiDataId(waza, 0x42);
            fightWazaInitJoutaiDataId(waza, 0x41);
            break;
        case 5:
            if (power != 0 && fightWazaIsHit(waza) == 1) {
                if (fightWazaIsJoutaiDataId(waza, 0x41) == 1) {
                    fightWazaInitJoutaiDataId(waza, 0x41);
                } else if (fightWazaCheckWriteJoutaiDataId(waza, type) == 2) {
                    fightWazaWriteJoutaiDataId(waza, type, 0);
                }
            }
            break;
        case 20:
            if (power != 0 && fightWazaIsHit(waza) == 1) {
                if (fightWazaIsJoutaiDataId(waza, 0x42) == 1) {
                    fightWazaInitJoutaiDataId(waza, 0x42);
                } else if (fightWazaCheckWriteJoutaiDataId(waza, type) == 2) {
                    fightWazaWriteJoutaiDataId(waza, type, 0);
                }
            }
            break;
        }
    }
}

void fightSeqDamageLoss(u8 kind, u8 randomize) {
    extern u16 HSD_Rand(void);
    FightOutPokemon* defender;
    u16 wazaId;
    u16 item;
    void* waza;
    FightOutPokemon* attacker;
    s32 damage;
    u32 itemSoubi;
    s32 buff;
    u16 hp;
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    wazaId = fightOutPokemon_GetUseWazaDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    damage = fightWaza_GetDamage(waza);
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    item = fightOutPokemonGetSoubiItemDataId(defender);
    itemSoubi = fightOutPokemonGetSoubiItemSoubiDataId(defender);
    buff = figthOutPokemonGetSoubiItemBuff(defender);
    hp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(defender));
    if (randomize == 1) {
        u16 r = HSD_Rand();
        u16 mult = 100 - r % 16;
        if (damage != 0) {
            damage *= mult;
            damage /= 100;
            if (damage == 0) {
                damage = 1;
            }
            fightWaza_SetDamage(waza, damage);
        }
    }
    if ((u16)itemSoubi == 0x27 && (s32)(HSD_Rand() % 100) < buff) {
        fightOutPokemon_SetItemKoraetaFlag(defender, 1);
    }
    if (fightOutPokemonIsJoutaiDataId(defender, 0x14) == 0 &&
        ((wazaDB_GetSeqId(wazaId) == 0x65 && kind == 1) || fightOutPokemonIsJoutaiDataId(defender, 0x2C) != 0 ||
         fightOutPokemon_GetItemKoraetaFlag(defender) != 0) &&
        !((s32)pokemon_GetHp(fightOutPokemonGetPokemonPtr(defender)) > damage)) {
        fightWaza_SetDamage(waza, hp - 1);
        if (fightOutPokemonIsJoutaiDataId(defender, 0x2C) != 0) {
            if (fightWazaCheckWriteJoutaiDataId(waza, 0x46) == 2) {
                fightWazaWriteJoutaiDataId(waza, 0x46, 0);
            }
        } else if (fightOutPokemon_GetItemKoraetaFlag(defender) != 0) {
            if (fightWazaCheckWriteJoutaiDataId(waza, 0x47) == 2) {
                fightWazaWriteJoutaiDataId(waza, 0x47, 0);
            }
            fightFloor_SetAppointItemDataId(0, item);
        }
    }
}

}

extern "C++" {
static void _fightSeqHinshiFriendCalc(FightOutPokemon* p) {
    u16 i;
    u8 level;
    u16 count;
    u8 maxLevel;
    void* moto;
    FightOutPokemon* ary[8];
    if (p != 0) {
        moto = fightOutPokemon_GetMotoFightPokemonPtr(p);
        level = figthOutPokemonGetLevel(p);
        count = fightFloorGetFightOutPokemonPtrAry(0, 0, 2, p, ary);
        maxLevel = 0;
        for (i = 0; i < count; i++) {
            if (ary[i] != 0 && maxLevel < figthOutPokemonGetLevel(ary[i])) {
                maxLevel = figthOutPokemonGetLevel(ary[i]);
            }
        }
        if (maxLevel > level) {
            if ((s32)(maxLevel - level) >= 30) {
                fightPokemonGetFriendFormPokemonFriendFilterId(moto, (void*)8);
                return;
            }
            fightPokemonGetFriendFormPokemonFriendFilterId(moto, (void*)6);
            return;
        }
        fightPokemonGetFriendFormPokemonFriendFilterId(moto, (void*)6);
    }
}
}

static s32 _WsWkcActSubJoutaiMigawari(void* pokemon, u16 id, void* user) {
    FightOutPokemon* p = (FightOutPokemon*)pokemon;
    if (fightOutPokemonIsJoutaiDataId(p, 0x14) == 1 && fightOutPokemonGetJoutaiMigawariHp(p) <= 0) {
        fightOutPokemonInitJoutaiDataId(p, 0x14);
    }
    return 1;
}

static s32 _WsWkcActSubSetStockItem(void* pokemon, u16 id, void* user) {
    FightOutPokemon* p = (FightOutPokemon*)pokemon;
    u16 item = fightOutPokemon_GetStockItemDataId(p);
    if (item != 0) {
        fightOutPokemonDoItemSoubi(p, item, 1, 0);
        fightOutPokemon_SetStockItemDataId(p, 0);
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x82);
    }
    return 1;
}

static void _fightSeqStatusUpDownEffect(u16 kind, u8 target);
extern u8 fight_seq_cond_chg_multi;

extern "C" {
void WS_COND_CHG_BIT_CHECK(void) {
    enum TsE { TsE0 };
    int big;
    u16 effect = 0;
    int hits = 0;
    u8 kind = 0;
    u8* seq = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(seq[1], 0);
    void* side = fightTargetGetPtrAsNowFightType(2, (u32)p);
    u32 tokusei = fightOutPokemonGetTokuseiDataId(p);
    u8 flags = seq[3];
    bool bits = seq[2];
    enum TsE multi;
    if (flags & 1) {
        big = flags & 2;
        u16 base = 0x15;
        if (big) {
            base = 0x2D;
        }
        for (; bits != 0; kind++, bits >>= 1) {
            if (bits & 1) {
                u8 stat;
                u32 id;
                id = fightSeqCondChgActTypeToPokemonStatusId(kind);
                stat = pokemonGetStatus(p, 0, id, 0);
                if (flags & 8) {
                    if (stat != 0) {
                        hits++;
                        effect = base + kind;
                    }
                } else if (fightSideIsJoutaiDataId(side, 0x4C) == 0 && tokusei != 0x1D && tokusei != 0x49 &&
                           (tokusei != 0x33 || id != 0xEB) && (tokusei != 0x34 || id != 0xE6) && stat != 0) {
                    hits++;
                    effect = kind;
                    effect = base + effect;
                }
            }
        }
        if (hits > 1) {
            if (big) {
                effect = 0x3A;
            } else {
                effect = 0x39;
            }
        }
    } else {
        int big = flags & 2;
        u16 base = 0xE;
        if (big) {
            base = 0x26;
        }
        for (; bits != 0; kind++, bits >>= 1) {
            if ((bits & 1) && (u32)pokemonGetStatus(p, 0, fightSeqCondChgActTypeToPokemonStatusId(kind), 0) < 12) {
                hits++;
                effect = base + kind;
            }
        }
        if (hits > 1) {
            if (big) {
                effect = 0x38;
            } else {
                effect = 0x37;
            }
        }
    }
    multi = (enum TsE)(flags & 4);
    if (multi && hits < 2) {
        fightSeq_NextWazaSeq(4);
        return;
    }
    if (hits != 0 && fight_seq_cond_chg_multi == 0) {
        _fightSeqStatusUpDownEffect(effect, seq[1]);
        if (multi && hits > 1) {
            fight_seq_cond_chg_multi = 1;
        }
        fightSeq_NextWazaSeq(4);
        return;
    }
    fightSeq_NextWazaSeq(4);
}
}

#pragma dont_inline on
extern "C++" {
static void _fightSeqStatusUpDownEffect(u16 kind, u8 target) {
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(target, 0);
    switch (kind) {
    case 0x14:
    case 0x2C:
        fightSeqFightOutPokemonEffect(0x2C, p, 0, 1);
        break;
        fightSeqFightOutPokemonEffect(0x3C, p, 0, 1);
        break;
    case 0xF:
    case 0x12:
    case 0x27:
    case 0x2A:
        fightSeqFightOutPokemonEffect(0x26, p, 0, 1);
        break;
    case 0x10:
    case 0x13:
    case 0x15:
    case 0x28:
    case 0x2B:
    case 0x2D:
        fightSeqFightOutPokemonEffect(0x28, p, 0, 1);
        break;
    case 0x11:
    case 0x29:
        fightSeqFightOutPokemonEffect(0x2A, p, 0, 1);
        break;
        fightSeqFightOutPokemonEffect(0x2C, p, 0, 1);
        break;
    case 0x16:
    case 0x19:
    case 0x2E:
    case 0x31:
        fightSeqFightOutPokemonEffect(0x27, p, 0, 1);
        break;
    case 0x17:
    case 0x1A:
    case 0x1C:
    case 0x2F:
    case 0x32:
    case 0x34:
        fightSeqFightOutPokemonEffect(0x29, p, 0, 1);
        break;
    case 0x18:
    case 0x30:
        fightSeqFightOutPokemonEffect(0x2B, p, 0, 1);
        break;
    case 0x1B:
    case 0x33:
        fightSeqFightOutPokemonEffect(0x3C, p, 0, 1);
        break;
    }
}
}
#pragma dont_inline reset

static u8 _fightSeqFightEffectStatusUpDown(u8 effect, u8 kind) {
    u8 dir;
    u8 result = effect;
    switch (effect) {
    case 0x10:
        dir = 1;
        break;
    case 0x20:
        dir = 1;
        break;
    case 0x90:
        dir = 0;
        break;
    case 0xA0:
        dir = 0;
        break;
    }
    if (kind == 1 || kind == 4) {
        if (dir == 1) {
            result = 0x26;
        } else {
            result = 0x27;
        }
    }
    if (kind == 2 || kind == 5 || kind == 7) {
        if (dir == 1) {
            result = 0x28;
        } else {
            result = 0x29;
        }
    }
    if (kind == 3) {
        if (dir == 1) {
            result = 0x2A;
        } else {
            result = 0x2B;
        }
    }
    if (kind == 6) {
        if (dir == 1) {
            result = 0x2C;
        } else {
            result = 0x3C;
        }
    }
    return result;
}

extern "C" {
}
extern "C" {
extern u8* TSUIKASeqTbl[];
extern u16 ShimeWazaNo[];
void* fightOutPokemon_GetKeepFightWazaPtr(FightOutPokemon* fop);
u16 fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(void* floor, u16 joutaiId);
extern u8 WAZA_Meneki[];
extern u8 WAZA_Mizunobeeru[];
extern u8 WAZA_Juunan[];
extern u8 WAZA_Seisinryoku[];
u8 fightOutPokemon_GetFightActionFlag(FightOutPokemon* fop);
u32 fightTrainer_GetKoban(u8* t);
void fightTrainer_SetKoban(u8* t, u32 v);
void fightOutPokemon_SetTameWazaFlag(FightOutPokemon* fop, u8 value);
u16 fightOutPokemonNowHpWaruValue(FightOutPokemon* fop, u8 waru);
u8 fightSeqCondChgAct(u8 paraId, u8 type, s32 flags, void* jump);
extern u8 WAZA_CondUpTsuikaMsg[];
extern u8 WAZA_CondDownTsuikaMsg[];
u8 fightSeqIsDoItemGetWaza(FightOutPokemon* p);
extern u8 WAZA_Nentyaku2[];
bool itemDataCheckValid(u16 id);
extern u8 WAZA_AddDorobou[];
extern u8 WAZA_Genshinochikara[];
extern u8 WAZA_Kousokuspin[];
extern u8 WAZA_NoMahi[];
extern u8 WAZA_Bakadikara[];
extern u8 WAZA_Nentyaku[];
extern u8 WAZA_Hatakiotosu[];
extern u8 WAZA_OverHeat[];
extern u8 fight_seq_tuika_param;
void fightFloor_SetTuikakoukaPokemonPtr(void* floor, FightOutPokemon* pokemon);

}
static void _fightSeqTuikaActSub(u8 direct, u8 flag, u8* out) {
    u8 ok = 0;
    u8 self = 0;
    u8 type = fightFloor_GetFightType(0);
    u8 tenkou;
    FightOutPokemon* attacker;
    FightOutPokemon* defender;
    u16 waza;
    FightOutPokemon* p;
    FightOutPokemon* other;
    u32 targetId;
    u32 tokusei;
    u16 item;
    void* side;
    void* fw;
    void* keep;
    *out = 1;
    tenkou = fightFloorGetNowTenkouDataId(0, 1);
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetUseWazaDataId(attacker);
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (ServerWork[3] & 0x40) {
        p = attacker;
        fightFloor_SetTuikakoukaPokemonPtr(0, attacker);
        fightFloor_SetAppointPokemonPtr(0, defender);
        other = defender;
        self = 0x40;
        ServerWork[3] &= 0xBF;
    } else {
        p = defender;
        fightFloor_SetTuikakoukaPokemonPtr(0, defender);
        other = attacker;
        fightFloor_SetAppointPokemonPtr(0, attacker);
    }
    targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(other, (u8)type);
    tokusei = fightOutPokemonGetTokuseiDataId(p);
    item = fightOutPokemonGetSoubiItemDataId(p);
    side = fightTargetGetPtrAsNowFightType(2, (u32)p);
    fw = fightOutPokemon_GetFightWazaPtr(p);
    keep = fightOutPokemon_GetKeepFightWazaPtr(p);

    if ((u16)tokusei == 0x13 && !(ServerStatusFlag & 0x2000) && direct == 0 && ServerWork[3] < 10) {
        ServerWork[3] = 0;
        return;
    }
    if (fightSideIsJoutaiDataId(side, 0x4B) == 1 && !(ServerStatusFlag & 0x2000) && direct == 0 && ServerWork[3] < 8) {
        return;
    }
    if (fightOutPokemonCheckFightOut(p) == 0 && ServerWork[3] != 0xB && ServerWork[3] != 0x1F) {
        ServerWork[3] = 0;
        return;
    }
    if (fightOutPokemonIsJoutaiDataId(p, 0x14) == 1 && self != 0x40) {
        ServerWork[3] = 0;
        return;
    }

    if (ServerWork[3] < 7) {
        switch (TSUIKATbl[ServerWork[3]]) {
        case 8: {
            u8 sleepOk = 1;
            if ((u16)tokusei != 0x2B && fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(0, 0xB) != 0) {
                sleepOk = 0;
            }
            if (fightOutPokemonIsJoutaiNormal(p) == 1 && fightOutPokemonCheckWriteJoutaiDataId(p, TSUIKATbl[ServerWork[3]]) == 2 &&
                sleepOk == 1 && (u16)tokusei != 0x48 && (u16)tokusei != 0xF && fightSeqRegulationOverTwoCheck(8, (u32)p) != 1) {
                fightOutPokemonInitJoutaiKeep(p);
                ok = 1;
            }
            break;
        }
        case 3:
            if ((u16)tokusei == 0x11 && (direct == 1 || flag == 0x80)) {
                if (ServerStatusFlag & 0x2000) {
                    ServerStatusFlag &= ~0x2000;
                    ServerWork[5] = 1;
                } else {
                    ServerWork[5] = 0;
                }
                fightSeq_CallWazaSeq(WAZA_Meneki);
                ServerWork[3] = 0;
                return;
            }
            if ((fightOutPokemonIsZokuseiDataId(p, 3) == 1 || fightOutPokemonIsZokuseiDataId(p, 8) == 1) &&
                (ServerStatusFlag & 0x2000) && (direct == 1 || flag == 0x80)) {
                ServerWork[5] = 2;
                fightSeq_CallWazaSeq(WAZA_Meneki);
                ServerWork[3] = 0;
                return;
            }
            if (fightOutPokemonIsZokuseiDataId(p, 3) == 0 && fightOutPokemonIsZokuseiDataId(p, 8) == 0 &&
                fightOutPokemonIsJoutaiNormal(p) == 1 && (u16)tokusei != 0x11) {
                ok = 1;
            }
            break;
        case 6:
            if ((u16)tokusei == 0x29 && (direct == 1 || flag == 0x80)) {
                if (ServerStatusFlag & 0x2000) {
                    ServerStatusFlag &= ~0x2000;
                    ServerWork[5] = 1;
                } else {
                    ServerWork[5] = 0;
                }
                fightSeq_CallWazaSeq(WAZA_Mizunobeeru);
                ServerWork[3] = 0;
                return;
            }
            if (fightOutPokemonIsZokuseiDataId(p, 0xA) == 1 && (ServerStatusFlag & 0x2000) && (direct == 1 || flag == 0x80)) {
                ServerWork[5] = 2;
                fightSeq_CallWazaSeq(WAZA_Mizunobeeru);
                ServerWork[3] = 0;
                return;
            }
            if (fightOutPokemonIsZokuseiDataId(p, 0xA) == 0 && (u16)tokusei != 0x29 && fightOutPokemonIsJoutaiNormal(p) == 1) {
                ok = 1;
            }
            break;
        case 7:
            if (fightOutPokemonIsZokuseiDataId(p, 0xF) == 0 && fightOutPokemonIsJoutaiNormal(p) == 1 && tenkou != 1 &&
                (u16)tokusei != 0x28 && fightSeqRegulationOverTwoCheck(7, (u32)p) != 1) {
                fightOutPokemonInitJoutaiKeep(p);
                ok = 1;
            }
            break;
        case 5:
            if ((u16)tokusei == 7 && (direct == 1 || flag == 0x80)) {
                if (ServerStatusFlag & 0x2000) {
                    ServerStatusFlag &= ~0x2000;
                    ServerWork[5] = 1;
                } else {
                    ServerWork[5] = 0;
                }
                fightSeq_CallWazaSeq(WAZA_Juunan);
                ServerWork[3] = 0;
                return;
            }
            if ((u16)tokusei != 7 && fightOutPokemonIsJoutaiNormal(p) == 1) {
                ok = 1;
            }
            break;
        case 4:
            if ((u16)tokusei == 0x11 && (direct == 1 || flag == 0x80)) {
                if (ServerStatusFlag & 0x2000) {
                    ServerStatusFlag &= ~0x2000;
                    ServerWork[5] = 1;
                } else {
                    ServerWork[5] = 0;
                }
                fightSeq_CallWazaSeq(WAZA_Meneki);
                ServerWork[3] = 0;
                return;
            }
            if ((fightOutPokemonIsZokuseiDataId(p, 3) == 1 || fightOutPokemonIsZokuseiDataId(p, 8) == 1) &&
                (ServerStatusFlag & 0x2000) && (direct == 1 || flag == 0x80)) {
                ServerWork[5] = 2;
                fightSeq_CallWazaSeq(WAZA_Meneki);
                ServerWork[3] = 0;
                return;
            }
            if (fightOutPokemonIsJoutaiNormal(p) == 1) {
                if (fightOutPokemonIsZokuseiDataId(p, 3) == 0 && fightOutPokemonIsZokuseiDataId(p, 8) == 0) {
                    if ((u16)tokusei != 0x11) {
                        ok = 1;
                    }
                } else if (fightWazaCheckWriteJoutaiDataId(fw, 0x43) == 2) {
                    fightWazaWriteJoutaiDataId(fw, 0x43, 0);
                }
            }
            break;
        }
        if (ok) {
            if (fightOutPokemonCheckWriteJoutaiDataId(p, TSUIKATbl[ServerWork[3]]) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, TSUIKATbl[ServerWork[3]], 0);
            }
            fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
            if (ServerStatusFlag & 0x2000) {
                ServerStatusFlag &= ~0x2000;
                ServerWork[5] = 1;
            } else {
                ServerWork[5] = 0;
            }
            if (ServerWork[3] == 2 || (u8)(ServerWork[3] - 5) <= 1 || ServerWork[3] == 3) {
                fight_seq_tuika_param = ServerWork[3];
                ServerStatusFlag |= 0x4000;
            }
            fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork[3]]);
            return;
        }
        ServerWork[3] = 0;
        return;
    }

    if (TSUIKATbl[ServerWork[3]] == 0 || fightOutPokemonIsJoutaiDataId(p, TSUIKATbl[ServerWork[3]]) != 1) {
        switch (ServerWork[3]) {
        case 7:
            if ((u16)tokusei != 0x14 && fightOutPokemonIsJoutaiDataId(p, 9) == 0) {
                if (fightOutPokemonCheckWriteJoutaiDataId(p, 9) == 2) {
                    fightOutPokemonWriteJoutaiDataId(p, 9, 0);
                }
                fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork[3]]);
            }
            break;
        case 8:
            if ((u16)tokusei == 0x27 && (direct == 1 || flag == 0x80)) {
                fightSeq_JumpWazaSeq(WAZA_Seisinryoku);
                ServerWork[3] = 0;
                *out = 0;
                return;
            }
            if ((u16)tokusei != 0x27 && fightOutPokemon_GetFightActionFlag(p) == 0 &&
                fightOutPokemonCheckWriteJoutaiDataId(p, TSUIKATbl[ServerWork[3]]) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, TSUIKATbl[ServerWork[3]], 0);
            }
            break;
        case 0xA:
            if (fightOutPokemonCheckWriteJoutaiDataId(p, 0xB) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, 0xB, 0);
                fightOutPokemonWriteJoutaiDataId(attacker, 0x22, 0);
                fightWazaBiosCopy(keep, fw);
                fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork[3]]);
            }
            break;
        case 0xB: {
            u8* trainer = (u8*)fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, attacker);
            if (trainer) {
                u32 value;
                u32 koban = fightTrainer_GetKoban(trainer);
                koban += figthOutPokemonGetLevel(attacker) * 5;
                value = 0xFFFF;
                if (koban <= 0xFFFF) {
                    value = koban;
                }
                fightTrainer_SetKoban(trainer, value);
                fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork[3]]);
            }
            break;
        }
        case 9:
            if (fightOutPokemonIsJoutaiNormal(p) == 1) {
                ServerWork[3] = (int)(u16)HSD_Rand() % 3 + 3;
                fightSeqTuikaAct(0, 0);
                fightSeq_NextWazaSeq(-1);
            }
            break;
        case 0xC:
            fightOutPokemonWriteJoutaiDataId(p, 0x22, 0);
            fightWazaBiosCopy(keep, fw);
            fightOutPokemon_SetTameWazaFlag(p, 1);
            break;
        case 0xD:
            if (fightOutPokemonCheckWriteJoutaiDataId(p, 0xE) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, 0xE, (u16)targetId);
                fightOutPokemonSetIdBuffJoutaiDataId(p, 0xE, waza);
                for (ServerWork[5] = 0; ServerWork[5] < 5; ServerWork[5]++) {
                    if (waza == ShimeWazaNo[ServerWork[5]]) {
                        break;
                    }
                }
                fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork[3]]);
            }
            break;
        case 0xE: {
            int damage;
            if (waza == 0x167) {
                u16 half = fightOutPokemonNowHpWaruValue(p, 1);
                damage = fightOutPokemonNowHpWaruValue(p, 2);
                if (half == damage) {
                    damage = 0;
                }
            } else {
                damage = fightWaza_GetHitDamage(fw) / 4;
            }
            if (waza != 0x167 && damage == 0) {
                damage = 1;
            }
            fightWaza_SetDamage(fw, damage);
            fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork[3]]);
            break;
        }
        case 0xF:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
            if (fightSeqCondChgAct(0x10, ServerWork[3] - 0xE, (u16)self, 0) == 0) {
                UserWork[0x160A4] = ServerWork[3] & 0x3F;
                UserWork[0x160A5] = 0;
                fightSeq_CallWazaSeq(WAZA_CondUpTsuikaMsg);
            }
            break;
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
            if (fightSeqCondChgAct(0x90, ServerWork[3] - 0x15, (u16)self, 0) == 0) {
                UserWork[0x160A4] = ServerWork[3] & 0x3F;
                UserWork[0x160A5] = 0;
                fightSeq_CallWazaSeq(WAZA_CondDownTsuikaMsg);
            }
            break;
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
            if (fightSeqCondChgAct(0x20, ServerWork[3] - 0x26, (u16)self, 0) == 0) {
                UserWork[0x160A4] = ServerWork[3] & 0x3F;
                UserWork[0x160A5] = 0;
                fightSeq_CallWazaSeq(WAZA_CondUpTsuikaMsg);
            }
            break;
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
            if (fightSeqCondChgAct(0xA0, ServerWork[3] - 0x2D, (u16)self, 0) == 0) {
                UserWork[0x160A4] = ServerWork[3] & 0x3F;
                UserWork[0x160A5] = 0;
                fightSeq_CallWazaSeq(WAZA_CondDownTsuikaMsg);
            }
            break;
        case 0x1D:
            if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x12) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, 0x12, 0);
            }
            fightWazaBiosCopy(keep, fw);
            break;
        case 0x1E:
            if (fightOutPokemonCheckWriteJoutaiDataId(attacker, 0x13) == 2) {
                fightOutPokemonWriteJoutaiDataId(attacker, 0x13, 0);
            }
            break;
        case 0x1F:
            if (fightSeqIsDoItemGetWaza(attacker) != 0) {
                u16 atkItem = fightOutPokemonGetSoubiItemDataId(attacker);
                u32 defTokusei = fightOutPokemonGetTokuseiDataId(defender);
                u16 defItem = fightOutPokemonGetSoubiItemDataId(defender);
                if ((u16)defTokusei == 0x3C && defItem != 0) {
                    fightSeq_CallWazaSeq(WAZA_Nentyaku2);
                } else if (atkItem == 0 && defItem != 0xAF && defItem != 0 && itemDataCheckValid(defItem) == 1) {
                    fightOutPokemonDoItemSoubi(defender, 0, 0, 0);
                    fightOutPokemon_SetStockItemDataId(attacker, defItem);
                    fightSeqCheckSetHensinBuffToMotoPokemon(attacker, 0x82);
                    fightSeqCheckSetHensinBuffToMotoPokemon(defender, 0x82);
                    fightOutPokemonInitJoutaiDataId(defender, 0x36);
                    fightFloor_SetAppointItemDataId(0, defItem);
                    fightSeq_CallWazaSeq(WAZA_AddDorobou);
                }
            }
            break;
        case 0x20:
            if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x16) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, 0x16, fightTargetGetTragetPtrToRelativeHostSideFightTargetId(attacker, type));
            }
            break;
        case 0x21:
            if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x17) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, 0x17, 0);
            }
            break;
        case 0x22:
            fightMsgctrlSetValue(0x10, (u32)p);
            fightSeq_CallWazaSeq(WAZA_Genshinochikara);
            fightMsgctrlSetValue(0x10, (u32)defender);
            break;
        case 0x23:
            fightSeq_CallWazaSeq(WAZA_Kousokuspin);
            break;
        case 0x24:
            if (fightOutPokemonIsJoutaiDataId(defender, 5) == 1) {
                fightOutPokemonInitJoutaiDataId(defender, 5);
                fightSeqCheckSetHensinBuffToMotoPokemon(defender, 0x7C);
                fightSeq_CallWazaSeq(WAZA_NoMahi);
            }
            break;
        case 0x25:
            fightSeq_CallWazaSeq(WAZA_Bakadikara);
            break;
        case 0x26: {
            s32 damage = fightWaza_GetHitDamage(fw) / 3;
            if (damage == 0) {
                damage = 1;
            }
            fightWaza_SetDamage(fw, damage);
            fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork[3]]);
            break;
        }
        case 0x35:
            if (fightOutPokemonCheckWriteJoutaiDataId(p, 0xD) == 2) {
                fightOutPokemonWriteJoutaiDataId(p, 0xD, 0);
                fightOutPokemonWriteJoutaiDataId(p, 0x22, 0);
                fightWazaBiosCopy(keep, fw);
                *out = 0;
            }
            break;
        case 0x36:
            if ((u16)tokusei == 0x3C && item != 0) {
                fightSeq_JumpWazaSeq(WAZA_Nentyaku);
                *out = 0;
            } else if (item != 0 && fightOutPokemonCheckWriteJoutaiDataId(p, 0x3D) == 2) {
                fightFloor_SetAppointItemDataId(0, item);
                fightOutPokemonWriteJoutaiDataId(p, 0x3D, 0);
                fightSeqCheckSetHensinBuffToMotoFightPokemon(p, 0xCD);
                fightOutPokemonInitJoutaiDataId(p, 0x36);
                fightSeq_CallWazaSeq(WAZA_Hatakiotosu);
            }
            break;
        case 0x3B:
            fightSeq_CallWazaSeq(WAZA_OverHeat);
            break;
        }
    }
    ServerWork[3] = 0;
}

extern "C" {

}
