#include <dolphin/types.h>

extern "C" void* memcpy(void* dst, const void* src, u32 n);

class Pokemon {
public:
    u8 data[0xC4];

    Pokemon() {}
    Pokemon(const Pokemon& other) {
        memcpy(this, &other, sizeof(Pokemon));
    }
    Pokemon& operator=(const Pokemon& other) {
        memcpy(this, &other, sizeof(Pokemon));
        return *this;
    }

    void copyCondition(const Pokemon* other);
    bool isReversMode() const;
    void setReversMode(bool mode);
};

struct FightPokemonStatus10 {
    u32 data[4];
};

struct FightPokemonJoutai {
    u32 data[8];
};

struct FightPokemonBuff {
    u32 data[0x80];
};

struct FightPokemon {
    u32 unk0;
    Pokemon pokemon;
    FightPokemonStatus10 unkC8;
    s16 unkD8;
    u8 unkDA;
    u8 unkDB;
    u8 unkDC;
    u8 unkDD;
    u16 unkDE;
    FightPokemonJoutai joutai;
    FightPokemonBuff buff;
};

struct FightOutPokemon;
struct FightOutPokemonEnemy;

struct Sequence {
    u8 unk0[8];
    s32 kind;
};

class ModelSequence {
public:
    u8 unk0[0x61];
    u8 lookFlag;
    u8 unk62[0x78 - 0x62];
    Sequence* lookSeq;

    void DoModelAnimation(int anim);
};
u16 wazaSequenceSysGetResourceID(ModelSequence* seq, u16 wzx, u16 kind, u8 flag);

struct RegWzxWork {
    FightOutPokemon* fop;
    u32 wzx;
    s32 count;
};

struct WazaResourceData {
    u32 groupId;
    u32 unk4;
};

static u8 _fightOutPokemonRegWzxFreeSub(void* fop, u16 idx, void* data);
static u32 _fightOutPokemonGetTenkiyaPkxDataId(u16 tenki);
static FightOutPokemon* _fightOutPokemonCheckFightActionSelectSub(FightOutPokemon* fop, u16 waza, u16 type);
struct FightWaza;
struct FightTrainer;
struct FightAction;
struct FightItem;

struct MenuPokemonStatus {
    u8 unk0[0x16];
    u8 unk16;
    u8 unk17[0x28 - 0x17];
    u8 sex;
    u8 unk29[0x2D - 0x29];
    u8 unk2D;
};

struct MenuWazaStatus {
    u8 unk0[0x40];
    FightOutPokemon* fightOutPokemon;
};

struct MenuLvupStatus {
    u8 unk0;
    u8 pad1;
    u16 maxHp;
    u16 phyAtk;
    u16 phyDef;
    u16 nimbleness;
    u16 speAtk;
    u16 speDef;
};

class FightOutPokemon {
public:
    u8 data[0x894];

    void setComboFuncId(u8 id);
};

extern "C" {

extern u8 fight_action_data_waza[];

// fightPokemonBios / fightOutPokemonBios accessors
FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon* fop);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon* fop);
FightPokemon* fightOutPokemon_GetFightPokemonHensinBuffPtr(FightOutPokemon* fop);
void fightOutPokemon_SetFightPokemonPtr(FightOutPokemon* fop, FightPokemon* fp);
FightOutPokemonEnemy* fightOutPokemon_GetFightOutPokemonEnemyPtr(FightOutPokemon* fop, u8 idx);
u16 fightOutPokemon_GetLastSelectWazaDataId(FightOutPokemon* fop);
void fightOutPokemon_SetOumuWazaAllyDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemon_SetOumuWazaDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemon_SetUsedItemDataId(FightOutPokemon* fop, u16 id);

FightOutPokemonEnemy* fightOutPokemonEnemySearchAry(FightOutPokemonEnemy* ary, u16 count, FightOutPokemon* target);
u8 fightOutPokemonEnemyCheckValid(FightOutPokemonEnemy* enemy);
s32 fightOutPokemonEnemyBiosGetDamage(FightOutPokemonEnemy* enemy);
void fightOutPokemonEnemyBiosSetDamage(FightOutPokemonEnemy* enemy, s32 damage);
u16 fightOutPokemonEnemyBiosGetOumuWazaDataId(FightOutPokemonEnemy* enemy);
void fightOutPokemonEnemyBiosSetOumuWazaDataId(FightOutPokemonEnemy* enemy, u16 id);

// pokemon
s32 pokemonGetStatus(void* p, s32 a, u16 id, s32 b);
void pokemonSetStatus(void* p, s32 a, u16 id, s32 b, s32 value);
void pokemonBiosCopy(Pokemon* dst, Pokemon* src);
u32 pokemon_GetRnd(Pokemon* p);
void pokemon_SetRnd(Pokemon* p, u32 rnd);
u32 pokemon_GetCatchTrainerRnd(Pokemon* p);
void pokemon_SetCatchTrainerRnd(Pokemon* p, u32 rnd);
u8 pokemonCheckRare(Pokemon* p);
void pokemonToMenuPokemonStatus(Pokemon* p, FightPokemon* fp, MenuPokemonStatus* menu, s8 rare);
void pokemonToMenuPokemonStatusSubBar(Pokemon* p, MenuPokemonStatus* menu);
u8 menuSubGetPokemonSexForFightDisp(Pokemon* p);
void pokemonToMenuWazaStatus(Pokemon* p, MenuWazaStatus* menu);
u16 pokemon_GetMaxHp(Pokemon* p);
u16 pokemon_GetPhyAtk(Pokemon* p);
u16 pokemon_GetPhyDef(Pokemon* p);
u16 pokemon_GetSpeAtk(Pokemon* p);
u16 pokemon_GetSpeDef(Pokemon* p);
u16 pokemon_GetNimbleness(Pokemon* p);
u16 pokemon_GetPokemonWazaDataId(Pokemon* p, u16 banme);
void pokemon_SetPokemonWazaDataId(Pokemon* p, u16 banme, u16 id);
u8 pokemon_GetPokemonWazaPp(Pokemon* p, u16 banme);
void pokemon_SetPokemonWazaPp(Pokemon* p, u16 banme, u8 pp);
u8 pokemonWazaCheckValid(Pokemon* p, u16 banme);
s32 pokemonGetTasteLike(Pokemon* p, s32 taste);
u16 pokemonDoItemSoubi(Pokemon* p, u16 item, u8 mode);
u8 pokemonGetSex(Pokemon* p);
u8 pokemonIsHpMantan(Pokemon* p);

u8 wazaDB_GetPp(u16 waza);
s32 wazaDB_GetIryoku(u16 waza);
s8 wazaDB_GetPri(u16 waza);

s32 fightFloor_GetFightType(s32 a);
u8 fightFloor_GetFightKindPokemonStatusMenuSubbarFlag(s32 a);
u8 fightFloorCheckHuuinWazaFightOutPokemon(s32 a, FightOutPokemon* fop, u16 waza);
typedef FightOutPokemon* (*FightSelectDefenseFunc)(FightOutPokemon* fop, u16 waza, u16 type);
FightOutPokemon* fightSeqSelectDefensePokemonPtr(FightOutPokemon* fop, u16 waza, u8 type, FightSelectDefenseFunc func, s32 b, s32 c, s32 d);
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon* target, u8 type);

u16 joutaiDataBiosGetStatus(u16 id);
void joutaiSetBuff(void* obj, u16 id, s32 value);
s32 joutaiGetBuff(void* obj, u16 id);
void joutaiCopy(void* dst, void* src, u16 id);
void joutaiSetIdBuff(void* obj, u16 id, u16 value);
u16 joutaiGetIdBuff(void* obj, u16 id);
u8 joutaiGetUserFightTargetId(void* obj, u16 id);
void joutaiSetKaisuuJoutaiDataId(void* obj, u16 id, u8 value);
void joutaiSetNowKaisuuJoutaiDataId(void* obj, u16 id, u8 value);
s32 joutaiGetNowKaisuuJoutaiDataId(void* obj, u16 id);
s32 joutaiGetKaisuuJoutaiDataId(void* obj, u16 id);
void joutaiSetCountAsJoutaiDataId(void* obj, u16 id, s32 value);
s32 joutaiGetCountAsJoutaiDataId(void* obj, u16 id);
void joutaiWriteJoutaiDataId(void* obj, u16 id, u32 value);
u8 joutaiCheckWriteJoutaiDataId(void* obj, u16 id);
u8 joutaiIsJoutaiDataId(void* obj, u16 id);
void joutaiInitJoutaiDataId(void* obj, u16 id);
void pokemonCopyJoutaiDataId(Pokemon* dst, Pokemon* src, u16 id);
void pokemonSetKaisuuJoutaiDataId(Pokemon* p, u16 id, u8 value);
void pokemonSetNowKaisuuJoutaiDataId(Pokemon* p, u16 id, u8 value);
s32 pokemonGetNowKaisuuJoutaiDataId(Pokemon* p, u16 id);
s32 pokemonGetKaisuuJoutaiDataId(Pokemon* p, u16 id);
void pokemonSetCountAsJoutaiDataId(Pokemon* p, u16 id, s32 value);
s32 pokemonGetCountAsJoutaiDataId(Pokemon* p, u16 id);
void pokemonWriteJoutaiDataId(Pokemon* p, u16 id, u32 value);
u8 pokemonCheckWriteJoutaiDataId(Pokemon* p, u16 id);
u8 pokemonIsJoutaiDataId(Pokemon* p, u16 id);
void pokemonInitJoutaiDataId(Pokemon* p, u16 id);
Sequence* fightOutPokemon_GetSequencePtr(FightOutPokemon* fop);
void Sequence_ResetStatus(Sequence* seq, s32 flag);

struct FightSide;
typedef u16 GSchar;
void* fightTargetGetPtr(s32 kind, FightOutPokemon* fop, u8 type);
u8 fightFloor_GetFightTypeTrainerNum(s32 a);
u8 fightFloor_GetFightTypeFightoutPokemonNum(s32 a);
FightTrainer* fightSide_GetFightTrainerPtr(FightSide* side, u16 idx);
u8 fightTrainerCheckValid(FightTrainer* trainer);
FightOutPokemon* fightTrainer_GetFightoutPokemonPtr(FightTrainer* trainer, u16 idx);
bool fightOutPokemonCheckValid(FightOutPokemon* fop);
void fightOutPokemonEnemyInit(FightOutPokemonEnemy* enemy);
void fightOutPokemonEnemyCreate(FightOutPokemonEnemy* enemy, FightOutPokemon* target);
u16 fightOutPokemon_GetOumuWazaDataId(FightOutPokemon* fop);
u16 fightPokemonGetSoubiItemSoubiDataId(FightPokemon* fp);
void pokemonGetFriendFormPokemonFriendFilterId(Pokemon* p, u16 item, void* out);
void pokemonGetEffortFromPokemon(Pokemon* p, u16 item, Pokemon* from, u8 mode);
u32 pokemonGetLevelToExp(Pokemon* p, u8 level);
void pokemon_SetExp(Pokemon* p, u32 exp);
u32 pokemon_GetExp(Pokemon* p);
void pokemonGrowBasisStatus(Pokemon* p, u8 level);
u16 pokemon_GetPokemonDataId(Pokemon* p);
u32 pokemonDB_GetVoice(u16 id);
u32 pokemonDB_GetName(u16 id);
GSchar* GSmsgGetGSchar(u32 msgId);
GSchar* pokemon_GetNicknamePtr(Pokemon* p);

u8 pokemon_GetHinsi(Pokemon* p);
u8 pokemonGetNowHpPercentage(Pokemon* p);
u16 fightOutPokemon_GetUseWazaDataId(FightOutPokemon* fop);
u16 pokemonGetNowHpWaruValue(Pokemon* p, u8 waru, u16 waza);
u16 pokemonGetMaxHpWaruValue(Pokemon* p, u8 waru);
u8 pokemonIsNokoriHpFollowing(Pokemon* p, u8 waru);
u8 pokemonIsJoutaiKaragenki(Pokemon* p);
u8 pokemonIsJoutaiNormal(Pokemon* p);
u8 pokemon_GetLevel(Pokemon* p);
u16 pokemonGetSoubiItemBuff(Pokemon* p);
u16 pokemonGetSoubiItemSoubiDataId(Pokemon* p);
u16 pokemonGetSoubiItemDataId(Pokemon* p);
u8 fightOutPokemon_GetAbicntNimbleness(FightOutPokemon* fop);
s32 heroGetStatus(void* hero, s32 id, s32 a);
u32 fightAbicntDoKakeWaru(u16 id, u32 value);
s16 fightPokemon_GetEntryId(FightPokemon* fp);
s16 fightOutPokemon_GetIrekaeTargetEntryId(FightOutPokemon* fop);
FightAction* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon* fop);
u8 fightActionCheckValid(FightAction* action);
u16 fightActionBiosGetKind(FightAction* action);
s16 fightActionBiosGetBuffDataId(FightAction* action);

struct GSmodel;
GSmodel* Sequence_GetGSmodel(Sequence* seq);
void fightOutPokemon_SetSequencePtr(FightOutPokemon* fop, Sequence* seq);
void battleGridRemovePokemon(Sequence* seq);
void Sequence_Free(Sequence* seq);
FightTrainer* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(s32 a, FightOutPokemon* fop);
u8 fightTrainerIsGcHero(FightTrainer* trainer);
extern u32* item_data_index_number;
u8 itemDataCheckValid(u16 item);
u8 itemDB_GetKind(u16 item);
u16 fightActionGetKindDataId(FightAction* action);
FightItem* fightOutPokemon_GetFightItemPtr(FightOutPokemon* fop);
u16 fightItem_GetItemDataId(FightItem* fi);
u16 fightItem_GetTargetDataId(FightItem* fi);
void fightItemCreate(FightItem* fi, u16 item, u16 target, u8 banme);
void fightItem_SetBuff(FightItem* fi, u8 buff);
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon* fop);
u16 fightWaza_GetMotoWazaDataId(FightWaza* fw);
u16 wazaDB_GetSeqId(u16 waza);
u16 fightWaza_GetTargetDataId(FightWaza* fw);
FightOutPokemon* fightTargetGetPtrAsNowFightType(s32 kind, FightOutPokemon* fop);
void fightWazaCreate(FightWaza* fw, s8 banme, u16 moto, u16 target, u8 autoMake);
u8 fightActionCreate(FightAction* action, s32 a, FightOutPokemon* fop, s32 kind, s32 c, void* data);
void fightActionBiosSetBuffDataId(FightAction* action, s32 id);
s8 fightActionGetPri(FightAction* action);
u8 fightWaza_GetZokusei(FightWaza* fw);
u16 fightWaza_GetUseWazaDataId(FightWaza* fw);

s16 fightOutPokemon_GetMeetEnemyFightPokemonEntryId(FightOutPokemon* fop, u8 idx);
void fightOutPokemon_SetMeetEnemyFightPokemonEntryId(FightOutPokemon* fop, u8 idx, s16 entry);
bool fightPokemonCheckValid(FightPokemon* fp);
Pokemon* fightPokemon_GetMotoPokemonPtr(FightPokemon* fp);
void pokemonSetOnZukanFlag(Pokemon* p, u8 flag);
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon* fp);
FightWaza* fightOutPokemon_GetKeepFightWazaPtr(FightOutPokemon* fop);
u8 fightWazaCheckValid(FightWaza* fw);
s8 fightWaza_GetWazaBanme(FightWaza* fw);
FightOutPokemon* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u16 targetId, u16 type);
u8 fightOutPokemon_GetKizetuFlag(FightOutPokemon* fop);
u8 fightPokemon_GetHokakuFlag(FightPokemon* fp);
u8 pokemonCheckFightOut(Pokemon* p);
u16 fightGetFightResultId(void);
void fightOutPokemon_SetMotoFightPokemonPtr(FightOutPokemon* fop, FightPokemon* fp);
void fightFloorSetShadow(void);
u8 pokemonDB_GetZokuseiDataId(u16 id, u16 idx);
u16 pokemonGetTokuseiDataId(Pokemon* p);
void fightOutPokemonInit(FightOutPokemon* fop);

void fightOutPokemon_SetSketchWazaDataId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetLastSelectWazaDataId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetLastUseWazaDataId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetLastReceiveWazaTargetDataId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetHitWazaDataId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetHitWazaZokuseiDataId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetGamanDamageValue(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetGamanDamageTargetId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetComboFuncId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetFixAiWaza(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetFixAiDef(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetNamakeFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetSuccessCnt(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetStockItemDataId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetKizetuFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetIrekaeTargetEntryId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetFightoutTurnCount(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetDoClearbodyFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetReceivesWazaHiraishinFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetVanishoffFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetDoIkakuFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetDoTraceFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetNoPressureFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetIrekaetaFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetItemKoraetaFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetKaigaraDamageValue(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetMyselfDamageAtkValue(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetMyselfDamageAtkTargetId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetMyselfDamageSpeValue(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetMyselfDamageSpeTargetId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetDamageAtkValue(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetDamageAtkTargetId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetDamageSpeValue(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetDamageSpeTargetId(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetMahiNoAttackFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetKonranMyselfAttackFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetOutWazaKoukanaiFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetTameWazaFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetItemNigeruFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetHuuinNoAttackFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetMeroMeroNoAttackFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetKanashibariNoAttackFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetChouhatsuNoAttackFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetIchamonNoAttackFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetHirumuNoAttackFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetPassPpdecFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemon_SetFightActionFlag(FightOutPokemon* fop, s32 value);
void fightOutPokemonBiosSetHensinMotoPkxId(FightOutPokemon* fop, s32 value);
void fn_8014718C(FightOutPokemon* fop, s32 value);
struct Joutai;
Joutai* fightOutPokemon_GetFightoutJoutaiPtr(FightOutPokemon* fop, s32 idx);
Joutai* fightPokemon_GetFightJoutaiPtr(FightPokemon* fp, s32 idx);
void joutaiInitAry(Joutai* ary, s32 count);
void fightWazaInit(FightWaza* fw);
u32* fightOutPokemon_GetWazaMenuCurPtr(FightOutPokemon* fop);
void fightOutPokemonEnemyInitAry(FightOutPokemonEnemy* ary, u16 count);
void fightActionInit(FightAction* action);
void fightItemInit(FightItem* fi);
void fightPokemon_SetMotoPokemonPtr(FightPokemon* fp, Pokemon* p);
void fightPokemon_SetEntryId(FightPokemon* fp, s16 entry);
void pokemonInit(Pokemon* p);
void fightPokemon_SetCatchEntryFlag(FightPokemon* fp, s32 value);
void fightPokemon_SetLevelUpFlag(FightPokemon* fp, s32 value);
void fightPokemon_SetDarkOutFlag(FightPokemon* fp, s32 value);
void fightPokemon_SetHokakuFlag(FightPokemon* fp, s32 value);
void fightPokemon_SetAiDamage(FightPokemon* fp, s32 idx, s32 kind, s32 value);
u8 pokemonCheckValid(Pokemon* p);
u16 zokuseiGetWazaJoutai(u16 waza, u16 zokusei);
void fightOutPokemon_SetZokuseiDataId(FightOutPokemon* fop, u8 idx, u16 zokusei);
u16 fightOutPokemon_GetZokuseiDataId(FightOutPokemon* fop, u8 idx);
void fightOutPokemon_SetTokuseiDataId(FightOutPokemon* fop, u16 tokusei);
u16 fightOutPokemon_GetTokuseiDataId(FightOutPokemon* fop);
void Sequence_SetDownFlag(Sequence* seq, u8 flag);

struct WazaSequence;
extern WazaResourceData waza_resource_data[];
extern u32 dbgEffLoadFsysGroupID;
s32 pokemonDB_GetPkxDataId(u16 id);
u8 pokemonGetAnnonKatati(u32 rnd);
u8 pokemonGetFightPokemonDeoxysSel(FightPokemon* fp);
u8 pokemonIsDarkPokemon(Pokemon* p);
Sequence* Sequence_LoadPokemon(u16 pkx, u32 form, u8 rare);
void pokemonSetSequenceStatus(Pokemon* p, Sequence* seq);
u32 itemBallDB_GetDowninWzxDataId(u8 ball);
s32 pokemon_GetCatchBallId(Pokemon* p);
typedef u8 (*FightOutPokemonLoopFunc)(void* fop, u16 idx, void* data);
void fightFloorLoopValidFightOutPokemon(s32 a, FightOutPokemonLoopFunc func, void* data, s32 b);
void Sequence_LoadWaza(Sequence* seq, u16 id, u16 kind, u8 flag);
WazaSequence* Sequence_GetWaza(Sequence* seq, u16 id, s32 kind);
void WazaSequence_Start(WazaSequence* waza, s32 flag);
u8 WazaSequence_IsActive(WazaSequence* waza);
void WazaSequence_Free(WazaSequence* waza);
void WazaSequence_Stop(WazaSequence* waza);
void GSthreadSwitch(void);
void GSsndPlayVolume(u16 snd, s32 a, s32 vol, s32 b);
void fightMenuOpenMsg(void* msg);
void fightMenuFightOutPokemonRenewStatusMenu(FightOutPokemon* fop, u8 type, s32 flag);
void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon* fop, u8 type, s32 flag);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(s32 menuId, FightOutPokemon* fop, u8 type, s32 a, s32 b);
s32 fightMenuGetFightOutPokemonPtrToStatusMenuId(FightOutPokemon* fop, u8 type, s32 flag);
u8 dbgMenuFightGetFightPokeStMenuOpenFlag(void);
void menuOpenCustom(s32 menuId, ...);
void fightFloor_SetStatusMenuCnt(s32 menuId, s32 cnt);
void fightWazaDoEffect(Sequence* seq, s32 a, s32 b, u8 close);
void fightMenuCloseCustom(s32 menuId, s32 a, s32 b);
void Sequence_FreeAllWaza(Sequence* seq);
s32 wazaDB_GetWazawzxdataId(u16 waza);

u32 itemBallDB_GetSnatchSnatchWzxDataId(u8 ball);
u32 itemBallDB_GetSnatchBalllandWzxDataId(u8 ball);
u32 itemBallDB_GetSnatchShakeWzxDataId(u8 ball);
u32 itemBallDB_GetSnatchMissWzxDataId(u8 ball);
u32 itemBallDB_GetSnatchPokeoutWzxDataId(u8 ball);
u32 itemBallDB_GetYaseiGetWzxDataId(u8 ball);
u32 itemBallDB_GetYaseiPokeoutWzxDataId(u8 ball);
u32 itemBallDB_GetYaseiBallLandWzxDataId(u8 ball);
u32 itemBallDB_GetYaseiShakeWzxDataId(u8 ball);
u32 itemBallDB_GetInWzxDataId(u8 ball);
u32 itemBallDB_GetOpenWzxDataId(u8 ball);
u32 itemBallDB_GetOutWzxDataId(u8 ball);
u8 fightFloor_GetTrainer(s32 a);
u8 fightFloor_GetFightKind(s32 a);
u16 fightFloor_GetEncountDataId(s32 a);
u32 fightFloor_GetEnvSndId(s32 a);
u8 Sequence_GetFlags(Sequence* seq);
void Sequence_SetDefaultFlags(Sequence* seq);
void Sequence_SetFlags(Sequence* seq, u8 flags);
void Sequence_SetLookTarget(Sequence* seq, Sequence* target);
void Sequence_SetVisibility(Sequence* seq, u8 visible);
void battleGridRestoreModelVisibilityFlags(void);
void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon* fop, u8 type, s32 flag);
u8 wazaSequenceSysLastWazaIsImpactPoint(s32 kind);
void wazaSequenceSysFreeAllWazaExcept(Sequence* seq, WazaSequence* waza);
u16 fightOutPokemon_GetKanseiSndId(FightOutPokemon* fop);
Sequence* fightTrainer_GetSequencePtr(FightTrainer* trainer);
void fadeSet(s32 kind, f32 time);
void fadeCheck(s32 kind);
void fightMainAllCamera(s32 a, s32 b);
void fightMsgctrlSetValue(s32 id, GSchar* str);
void fightMenuOpenMsg2(u32 msg, s32 flag);
extern u8 wildPokemonDownFlag;
void fightMenuCloseMsg(void);
u8 GSmodelGetVisibility(GSmodel* model);
void GSmodelSetVisibility(GSmodel* model, u8 visible);
void fightMainWaitFrame(s32 frames);

// this unit
void fightOutPokemonRegWzxFree(FightOutPokemon* fop);
void fightOutPokemonSetVisibility(FightOutPokemon* fop, u8 visible);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon* fop, u16 id);
s32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonSetBuffJoutaiDataId(FightOutPokemon* fop, u16 id, s32 buff);
u16 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
s32 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id);
s32 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon* fop, u16 id);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon* fop);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon* fp);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon* fop);
bool fightOutPokemonCheckFightOut(FightOutPokemon* fop);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon* fop);
void fightOutPokemonSetTokuseiDataId(FightOutPokemon* fop, u16 id);
u16 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon* fop);
u8 fightOutPokemonIsAlly(FightOutPokemon* fop, FightOutPokemon* other);

}

extern "C" {

u8 nonTrainerPokemonisActive;

void fightPokemonSetNonTrainerPokemonIsActiveFlag(u8 flag);
u8 fightPokemonGetNonTrainerPokemonIsActiveFlag(void);
void fightOutPokemonGetRndStatus(FightOutPokemon* fop, u32* rnd, u32* catchRnd);
void fightOutPokemonToMenuPokemonStatus(FightOutPokemon* fop, MenuPokemonStatus* menu);
void fightOutPokemonToMenuWazaStatus(FightOutPokemon* fop, MenuWazaStatus* menu);
void fightPokemonToMenuWazaStatus(FightPokemon* fp, MenuWazaStatus* menu);
void fightPokemonToMenuLvupStatus(FightPokemon* fp, MenuLvupStatus* lvup);
void fightOutPokemonAddFightOutPokemonEnemyDamage(FightOutPokemon* fop, FightOutPokemon* target, s32 damage);
void fightOutPokemonSetHensinStatusAfterLevelUp(FightOutPokemon* fop);
void fightOutPokemonSetHensinFightPokemonStatusId(FightOutPokemon* fop, u16 id, u8 toBuff);
void fightOutPokemonSetHensinPokemonStatusId(FightOutPokemon* fop, u16 id, s32 sub, u8 toBuff);
void fightOutPokemonCopyHensinStatus(FightOutPokemon* src, FightOutPokemon* dst);
u8 fightOutPokemonUseHensinBuff(FightOutPokemon* fop);
u8 fightOutPokemonIsUseHensinBuff(FightOutPokemon* fop);
void fightOutPokemonSetJoutaiMigawariHp(FightOutPokemon* fop, s32 hp);
s32 fightOutPokemonGetJoutaiMigawariHp(FightOutPokemon* fop);
u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon* fop, u8 create);
u8 fightOutPokemonCheckWaruagaki(FightOutPokemon* fop);
u8 fightOutPokemonGetOutOkWazaBanmeAry(FightOutPokemon* fop, s16* ary);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon* fop, u16 banme, u8 initKeep, u16* outItemWaza);
u8 fightOutPokemonCheckNoAttackFlag(FightOutPokemon* fop);
void fightOutPokemonInitJoutaiKeep(FightOutPokemon* fop);
void fightOutPokemonInitJoutaiKie(FightOutPokemon* fop);
u16 fightOutPokemonIsJoutaiKie(FightOutPokemon* fop);
u8 fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(FightOutPokemon* fop, u16* ary);
void fightOutPokemonSetOumuWazaDataId(FightOutPokemon* fop, FightOutPokemon* target, u16 waza);
s32 fightOutPokemonGetTasteLike(FightOutPokemon* fop, s32 taste);
s32 fightPokemonGetTasteLike(FightPokemon* fp, s32 taste);
u16 fightOutPokemonDoItemSoubi(FightOutPokemon* fop, u16 item, u8 mode, u8 update);
u16 fightPokemonDoItemSoubi(FightPokemon* fp, u16 item, u8 mode);
u16 fightOutPokemonGetAllAbiCnt(FightOutPokemon* fop);
void fightOutPokemonCopyAllAbiCnt(FightOutPokemon* dst, FightOutPokemon* src);
void fightOutPokemonCopyStatus(FightOutPokemon* dst, FightOutPokemon* src, u16 id);
u8 fightOutPokemonGetSex(FightOutPokemon* fop);
u8 fightPokemonGetSex(FightPokemon* fp);
u8 fightOutPokemonIsHpMantan(FightOutPokemon* fop);
u8 fightPokemonIsHpMantan(FightPokemon* fp);
void fightOutPokemonSetBuffJoutaiDataId(FightOutPokemon* fop, u16 id, s32 value);
s32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonCopyJoutaiDataId(FightOutPokemon* dst, FightOutPokemon* src, u16 id);
void fightOutPokemonSetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id, u16 value);
u16 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
u8 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonSetKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id, u8 value);
void fightOutPokemonSetNowKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id, u8 value);
s32 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id);
s32 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id);
s32 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonWriteJoutaiDataId(FightOutPokemon* fop, u16 id, u32 value);
u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon* fop, u16 id);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonResetSeqStatus(FightOutPokemon* fop, u16 id);
void fightPokemonSetBuffJoutaiDataId(FightPokemon* fp, u16 id, s32 value);
s32 fightPokemonGetBuffJoutaiDataId(FightPokemon* fp, u16 id);
void fightPokemonCopyJoutaiDataId(FightPokemon* dst, FightPokemon* src, u16 id);
void fightPokemonSetIdBuffJoutaiDataId(FightPokemon* fp, u16 id, u16 value);
u16 fightPokemonGetIdBuffJoutaiDataId(FightPokemon* fp, u16 id);
u8 fightPokemonGetUserFightTargetIdJoutaiDataId(FightPokemon* fp, u16 id);
void fightPokemonSetKaisuuJoutaiDataId(FightPokemon* fp, u16 id, u8 value);
void fightPokemonSetNowKaisuuJoutaiDataId(FightPokemon* fp, u16 id, u8 value);
s32 fightPokemonGetNowKaisuuJoutaiDataId(FightPokemon* fp, u16 id);
s32 fightPokemonGetKaisuuJoutaiDataId(FightPokemon* fp, u16 id);
void fightPokemonSetCountAsJoutaiDataId(FightPokemon* fp, u16 id, s32 value);
s32 fightPokemonGetCountAsJoutaiDataId(FightPokemon* fp, u16 id);
void fightPokemonWriteJoutaiDataId(FightPokemon* fp, u16 id, u32 value);
u8 fightPokemonCheckWriteJoutaiDataId(FightPokemon* fp, u16 id);
u8 fightPokemonIsJoutaiDataId(FightPokemon* fp, u16 id);
void fightPokemonInitJoutaiDataId(FightPokemon* fp, u16 id);
u8 fightOutPokemonIsAlly(FightOutPokemon* fop, FightOutPokemon* other);
void fightOutPokemonCreateFightPokemonEnemyAryEnemySideAll(FightOutPokemon* fop, FightSide* side);
void fightOutPokemonInitFightPokemonEnemyAry(FightOutPokemon* fop, FightOutPokemon* target);
FightOutPokemonEnemy* fightOutPokemonCreateFightPokemonEnemyAry(FightOutPokemon* fop, FightOutPokemon* target);
void fightPokemonGetFriendFormPokemonFriendFilterId(FightPokemon* fp, void* out);
void fightPokemonGetEffortFromPokemon(FightPokemon* fp, Pokemon* from, u8 mode);
u32 fightPokemonGetLevelToExp(FightPokemon* fp, u8 level);
void figthPokemonSetExp(FightPokemon* fp, u32 exp);
u32 figthPokemonGetExp(FightPokemon* fp);
void fightPokemonGrowBasisStatus(FightPokemon* fp, u8 level);
u32 fightOutPokemonGetVoiceSndId(FightOutPokemon* fop);
GSchar* fightOutPokemonGetNamePtr(FightOutPokemon* fop);
GSchar* fightPokemonGetNamePtr(FightPokemon* fp);
GSchar* fightOutPokemonGetNicknamePtr(FightOutPokemon* fop);
GSchar* fightPokemonGetNicknamePtr(FightPokemon* fp);
u8 fightOutPokemonIsHinsi(FightOutPokemon* fop);
u8 fightOutPokemonGetNowHpPercentage(FightOutPokemon* fop);
u16 fightOutPokemonNowHpWaruValue(FightOutPokemon* fop, u8 waru);
u16 fightOutPokemonMaxHpWaruValue(FightOutPokemon* fop, u8 waru);
u8 fightOutPokemonIsNokoriHpFollowing(FightOutPokemon* fop, u8 waru);
u8 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon* fop);
u8 fightOutPokemonIsJoutaiNormal(FightOutPokemon* fop);
u16 figthOutPokemonGetPokemonDataId(FightOutPokemon* fop);
u16 figthPokemonGetPokemonDataId(FightPokemon* fp);
u8 figthOutPokemonGetLevel(FightOutPokemon* fop);
u8 figthPokemonGetLevel(FightPokemon* fp);
s32 figthOutPokemonGetSoubiItemBuff(FightOutPokemon* fop);
u16 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon* fop);
u16 fightOutPokemonGetSoubiItemDataId(FightOutPokemon* fop);
s32 fightPokemonGetSoubiItemBuff(FightPokemon* fp);
u16 fightPokemonGetSoubiItemSoubiDataId(FightPokemon* fp);
u16 fightPokemonGetSoubiItemDataId(FightPokemon* fp);
u32 fightOutPokemonGetNowNimbleness(FightOutPokemon* fop, u8 useBadge, u8 tenki, u16 hp, void* hero);
u8 fightOutPokemonCheckIrekaeReserveFightPokemon(FightOutPokemon* fop, FightPokemon* fp);
u8 fightPokemonCheckMotoFightPokemon(FightPokemon* fp, FightOutPokemon* fop);
void fightPokemonReplace(FightPokemon* a, FightPokemon* b);
GSmodel* fightOutPokemonGetGsmodelPtr(FightOutPokemon* fop);
void fightOutPokemonFreeSequence(FightOutPokemon* fop);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon* fop);
u8 fightOutPokemonIsFightActionUseItemKind(FightOutPokemon* fop, u8 kind, u8 match);
u8 fightOutPokemonIsFightActionUseItem(FightOutPokemon* fop, u16 item, FightOutPokemon* targetFop);
u16 fightOutPokemonGetFightActionUseItemDataId(FightOutPokemon* fop);
FightAction* fightOutPokemonCreateFightActionUseItem(FightOutPokemon* fop, s32 a, s32 kind, s32 c, void* data, s32 item, u16 target, u8 itemBanme, u8 buff);
u8 fightOutPokemonIsFightActionAttackWazaOut(FightOutPokemon* fop, u16 waza, FightOutPokemon* targetFop);
FightAction* fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon* fop, s32 a, s32 kind, s32 c, void* data, s32 waza, u16 target, s8 banme, u8 autoMake);
FightAction* fightOutPokemonCreateFightAction(FightOutPokemon* fop, s32 a, s32 kind, s32 c, void* data, s32 buffId);
s8 fightOutPokemonGetFightActionPri(FightOutPokemon* fop);
u8 fightOutPokemonGetWazaZokuseiDataId(FightOutPokemon* fop);
u16 fightOutPokemonGetUseWazaDataId(FightOutPokemon* fop);
u16 fightOutPokemonGetCmpNimblenessWazaDataId(FightOutPokemon* fop);
u16 fightOutPokemonGetMotoWazaDataId(FightOutPokemon* fop);
void fightOutPokemonSetMeetEnemyFightPokemonEnemySideAll(FightOutPokemon* fop, FightSide* side);
s8 fightOutPokemonSetMeetEnemyFightPokemon(FightOutPokemon* fop, FightPokemon* fp);
u8 fightOutPokemonCheckMeetEnemyFightPokemon(FightOutPokemon* fop, FightPokemon* fp);
void fightOutPokemonSetOnZukanFlag(FightOutPokemon* fop, u8 flag);
s16 fightOutPokemonGetFightEntryId(FightOutPokemon* fop);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon* fop);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon* fp);
u8 fightOutPokemonCheckFightActionSelect(FightOutPokemon* fop, u8 create);
bool fightOutPokemonCheckFightOut(FightOutPokemon* fop);
bool fightPokemonCheckFightOut(FightPokemon* fp);
bool fightOutPokemonCheckValid(FightOutPokemon* fop);
void fightOutPokemonCreate(FightOutPokemon* fop, FightPokemon* fp, Sequence* seq);
bool fightPokemonCheckValid(FightPokemon* fp);
void fightPokemonCreate(FightTrainer* trainer, FightPokemon* fp, Pokemon* p, s16 entry);
void fightOutPokemonInitAry(FightOutPokemon* ary, u16 count);
void fightOutPokemonInit(FightOutPokemon* fop);
void fightOutPokemonInitAbiCntAll(FightOutPokemon* fop);
void fightOutPokemonInitFightOutPokemonEnemyAry(FightOutPokemon* fop);
void fightOutPokemonInitOneSelfTurn(FightOutPokemon* fop);
void fightOutPokemonInitOneTurn(FightOutPokemon* fop);
void fightOutPokemonInitFightActionBuff(FightOutPokemon* fop);
void fightPokemonInitAry(FightPokemon* ary, u16 count);
void fightPokemonInit(FightPokemon* fp);
u16 fightOutPokemonGetTeikouZokuseiDataIdAry(FightOutPokemon* fop, u16 waza, s32* ary);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon* fop, u16 zokusei);
void fightOutPokemonSetZokuseiDataId(FightOutPokemon* fop, u8 idx, u16 zokusei);
u16 fightOutPokemonGetZokuseiDataId(FightOutPokemon* fop, u8 idx);
void fightOutPokemonSetTokuseiDataId(FightOutPokemon* fop, u16 tokusei);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon* fop);
void fightOutPokemonSetWazaEffectDownFlag(FightOutPokemon* fop, u8 flag);
Sequence* fightOutPokemonCreateSequence(FightOutPokemon* fop, u16 tenki, s8 rare);
void fightOutPokemonRegWzxFree(FightOutPokemon* fop);
void fightOutPokemonRegWzxLoad(FightOutPokemon* fop);
void fightOutPokemonDarkPokemonKaijoEffect(FightOutPokemon* fop, u8 hp, u8 joutai, u8 kioku, void* msg, u8 mode);
void fightOutPokemonDarkPokemonEffect(FightOutPokemon* fop, u8 openMenu, u8 kind, u8 mode);
void fightOutPokemonWazaEffect(FightOutPokemon* fop, s32 a, s32 b, u8 close, s32 menuId);
void fightOutPokemonFreeAllSequenceWaza(FightOutPokemon* fop);
void fightOutPokemonFreeWazaEffect(FightOutPokemon* fop, u16 waza, s32 kind);
void fightOutPokemonLoadWazaEffect(FightOutPokemon* fop, u16 waza, u8 kind, u8 flag);
void fightOutPokemonHokakuEffect(FightOutPokemon* fop, u8 shakes, u8 ball, u8 mode, u8* flags);
void fightOutPokemonDasuEffect(FightTrainer* trainer, FightOutPokemon* fop, u8 mode);
void fightOutPokemonModosuEffect(FightOutPokemon* fop, u8 mode);
void fightOutPokemonKizetuEffect(FightOutPokemon* fop, u8 mode);
void fightOutPokemonDamageEffect(FightOutPokemon* fop);
void fightOutPokemonSetVisibility(FightOutPokemon* fop, u8 visible);

void fightOutPokemonSetVisibility(FightOutPokemon* fop, u8 visible) {
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        Sequence_SetVisibility(seq, visible);
    }
}

void fightOutPokemonDamageEffect(FightOutPokemon* fop) {
    GSmodel* model = fightOutPokemonGetGsmodelPtr(fop);
    if (model != 0 && GSmodelGetVisibility(model)) {
        for (u8 i = 0; i < 8; i++) {
            fightOutPokemonSetVisibility(fop, 1);
            GSmodelSetVisibility(model, 1);
            fightMainWaitFrame(3);
            fightOutPokemonSetVisibility(fop, 0);
            fightMainWaitFrame(2);
        }
        fightOutPokemonSetVisibility(fop, 1);
    }
}

void fightOutPokemonKizetuEffect(FightOutPokemon* fop, u8 mode) {
    Sequence* seq;
    u32 downWzx;
    u8 wild;
    u32 msg;
    WazaSequence* waza;
    Sequence* mySeq;
    FightTrainer* trainer;
    ModelSequence* model;
    wild = 0;
    seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq == 0) {
        return;
    }
    downWzx = itemBallDB_GetDowninWzxDataId(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(fop)));
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, fop);
    model = (ModelSequence*)fightTrainer_GetSequencePtr(trainer);
    mySeq = fightOutPokemon_GetSequencePtr(fop);
    if (!fightTrainerIsGcHero(trainer)) {
        if (!fightFloor_GetTrainer(0) || fightFloor_GetEncountDataId(0) == 0x191) {
            wild = 1;
            downWzx = 0xDB;
        }
    }
    if (mode == 0) {
        Sequence_LoadWaza(seq, downWzx, 4, 0);
    } else if (mode == 1) {
        waza = Sequence_GetWaza(seq, downWzx, 4);
        wazaSequenceSysFreeAllWazaExcept(seq, waza);
        WazaSequence_Start(waza, 1);
        if (model != 0) {
            if (model->lookFlag != 0) {
                model->lookSeq = mySeq;
            }
            model->DoModelAnimation(4);
        }
    } else if (mode == 2) {
        Sequence_GetWaza(seq, downWzx, 4);
        if (wild == 1) {
            while (true) {
                if (wazaSequenceSysLastWazaIsImpactPoint(2) == 1) {
                    break;
                }
                GSthreadSwitch();
            }
            fightMenuFightOutPokemonCloseStatusMenu(fop, fightFloor_GetFightType(0), 1);
            fightPokemonSetNonTrainerPokemonIsActiveFlag(0);
            fadeSet(3, 0.5f);
            fadeCheck(1);
            waza = Sequence_GetWaza(seq, downWzx, 4);
            while (WazaSequence_IsActive(waza)) {
                waza = Sequence_GetWaza(seq, downWzx, 4);
                GSthreadSwitch();
            }
            if (fightFloor_GetEncountDataId(0) == 0x191) {
                fightMainAllCamera(1, 0);
                fadeSet(2, 0.5f);
            } else {
                GSsndPlayVolume(0x4A6, 0, 0x7F, 0);
                fightMainAllCamera(1, 0);
                fadeSet(2, 0.5f);
                if (fightFloor_GetFightKind(0) == 0xC) {
                    msg = 0x4FF7;
                }
                if (fightFloor_GetFightKind(0) == 0xD) {
                    msg = 0x4FFE;
                }
                fightMsgctrlSetValue(0x16, fightOutPokemonGetNamePtr(fop));
                fightMenuOpenMsg2(msg, 1);
            }
        } else {
            waza = Sequence_GetWaza(seq, downWzx, 4);
            while (WazaSequence_IsActive(waza)) {
                waza = Sequence_GetWaza(seq, downWzx, 4);
                GSthreadSwitch();
            }
        }
        WazaSequence_Free(waza);
        if (!wild) {
            fightMenuFightOutPokemonCloseStatusMenu(fop, fightFloor_GetFightType(0), 1);
        }
        if (wild == 1) {
            wildPokemonDownFlag = 1;
            fightMenuCloseMsg();
        }
    } else if (mode == 3) {
        if (model != 0 && model->lookFlag != 0) {
            model->lookSeq = 0;
        }
        fightOutPokemonFreeSequence(fop);
    }
}

void fightOutPokemonModosuEffect(FightOutPokemon* fop, u8 mode) {
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        u32 inWzx = itemBallDB_GetInWzxDataId(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(fop)));
        if (mode == 0) {
            Sequence_LoadWaza(seq, inWzx, 4, 0);
        } else if (mode == 1) {
            WazaSequence* waza = Sequence_GetWaza(seq, inWzx, 4);
            Sequence_SetDefaultFlags(seq);
            WazaSequence_Start(waza, 1);
        } else if (mode == 2) {
            WazaSequence* waza = Sequence_GetWaza(seq, inWzx, 4);
            while (WazaSequence_IsActive(waza)) {
                GSthreadSwitch();
            }
        } else if (mode == 3) {
            WazaSequence_Free(Sequence_GetWaza(seq, inWzx, 4));
        } else if (mode == 4) {
            fightOutPokemonFreeSequence(fop);
            fightMenuFightOutPokemonCloseStatusMenu(fop, fightFloor_GetFightType(0), 1);
        }
    }
}

void fightOutPokemonDasuEffect(FightTrainer* trainer, FightOutPokemon* fop, u8 mode) {
    WazaSequence* waza;
    Sequence* trainerSeq = fightTrainer_GetSequencePtr(trainer);
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq == 0) {
        return;
    }
    fightOutPokemonGetPokemonPtr(fop);
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    u8 ball = pokemon_GetCatchBallId(p);
    u32 openWzx = itemBallDB_GetOpenWzxDataId(ball);
    u32 outWzx = itemBallDB_GetOutWzxDataId(ball);
    ModelSequence* model = (ModelSequence*)fightTrainer_GetSequencePtr(trainer);
    Sequence* mySeq = fightOutPokemon_GetSequencePtr(fop);
    if (mode == 0) {
        Sequence_LoadWaza(trainerSeq, openWzx, 4, 0);
        Sequence_LoadWaza(seq, outWzx, 4, 0);
        if (pokemonCheckRare(fightOutPokemonGetPokemonPtr(fop)) == 1) {
            Sequence_LoadWaza(seq, 0x67, 4, 0);
        }
    } else if (mode == 1) {
        WazaSequence_Start(Sequence_GetWaza(trainerSeq, openWzx, 4), 1);
    } else if (mode == 2) {
        waza = Sequence_GetWaza(trainerSeq, openWzx, 4);
        while (WazaSequence_IsActive(waza)) {
            GSthreadSwitch();
        }
    } else if (mode == 3) {
        WazaSequence_Start(Sequence_GetWaza(seq, outWzx, 4), 1);
        if (model != 0 && model->lookFlag != 0) {
            model->lookSeq = mySeq;
        }
    } else if (mode == 4) {
        if (trainerSeq != 0) {
            Sequence_SetLookTarget(trainerSeq, seq);
        }
        Sequence_GetWaza(seq, outWzx, 4);
        while (true) {
            if (wazaSequenceSysLastWazaIsImpactPoint(0) == 1) {
                break;
            }
            GSthreadSwitch();
        }
        GSsndPlayVolume(fightOutPokemonGetVoiceSndId(fop), 0, 0xFF, 0);
        if (fightFloor_GetEnvSndId(0) != 0) {
            GSsndPlayVolume(fightOutPokemon_GetKanseiSndId(fop), 0, 0x7F, 0);
        }
        waza = Sequence_GetWaza(seq, outWzx, 4);
        while (WazaSequence_IsActive(waza)) {
            GSthreadSwitch();
        }
        if (trainerSeq != 0) {
            Sequence_SetLookTarget(trainerSeq, 0);
        }
        if (pokemonCheckRare(p) == 1) {
            waza = Sequence_GetWaza(seq, 0x67, 4);
            WazaSequence_Start(waza, 1);
            while (WazaSequence_IsActive(waza)) {
                GSthreadSwitch();
            }
        }
    } else if (mode == 5) {
        if (model != 0 && model->lookFlag != 0) {
            model->lookSeq = 0;
        }
        WazaSequence_Free(Sequence_GetWaza(trainerSeq, openWzx, 4));
        WazaSequence_Free(Sequence_GetWaza(seq, outWzx, 4));
        WazaSequence_Free(Sequence_GetWaza(seq, 0x67, 4));
    }
}

void fightOutPokemonHokakuEffect(FightOutPokemon* fop, u8 shakes, u8 ball, u8 mode, u8* flags) {
    Sequence* seq;
    u32 getWzx;
    u32 landWzx;
    u32 shakeWzx;
    u32 missWzx;
    u32 outWzx;
    WazaSequence* shakeWaza;
    u8 i;
    WazaSequence* waza;
    seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq == 0) {
        return;
    }
    getWzx = itemBallDB_GetSnatchSnatchWzxDataId(ball);
    landWzx = itemBallDB_GetSnatchBalllandWzxDataId(ball);
    shakeWzx = itemBallDB_GetSnatchShakeWzxDataId(ball);
    missWzx = itemBallDB_GetSnatchMissWzxDataId(ball);
    outWzx = itemBallDB_GetSnatchPokeoutWzxDataId(ball);
    if (!fightFloor_GetTrainer(0)) {
        getWzx = itemBallDB_GetYaseiGetWzxDataId(ball);
        outWzx = itemBallDB_GetYaseiPokeoutWzxDataId(ball);
        landWzx = itemBallDB_GetYaseiBallLandWzxDataId(ball);
        shakeWzx = itemBallDB_GetYaseiShakeWzxDataId(ball);
        missWzx = 0;
    }
    if (fightFloor_GetFightKind(0) == 0xD) {
        shakeWzx = 0;
    }
    if (!fightFloor_GetTrainer(0)) {
        if (mode == 0) {
            if (outWzx != 0) {
                Sequence_LoadWaza(seq, outWzx, 4, 0);
            }
            if (getWzx != 0) {
                Sequence_LoadWaza(seq, getWzx, 4, 0);
            }
            if (landWzx != 0) {
                Sequence_LoadWaza(seq, landWzx, 4, 0);
            }
            if (shakeWzx != 0) {
                Sequence_LoadWaza(seq, shakeWzx, 4, 0);
            }
            if (missWzx != 0) {
                Sequence_LoadWaza(seq, missWzx, 4, 0);
            }
            if (flags != 0) {
                *flags = Sequence_GetFlags(seq);
                Sequence_SetDefaultFlags(seq);
            }
        } else if (mode == 1) {
            if (getWzx != 0) {
                waza = Sequence_GetWaza(seq, getWzx, 4);
                WazaSequence_Start(waza, 1);
                while (WazaSequence_IsActive(waza)) {
                    GSthreadSwitch();
                }
            }
            if (shakeWzx != 0) {
                waza = Sequence_GetWaza(seq, landWzx, 4);
                WazaSequence_Start(waza, 1);
                while (WazaSequence_IsActive(waza)) {
                    GSthreadSwitch();
                }
                i = 0;
                do {
                    shakeWaza = Sequence_GetWaza(seq, shakeWzx, 4);
                    WazaSequence_Start(shakeWaza, 1);
                    while (WazaSequence_IsActive(shakeWaza)) {
                        GSthreadSwitch();
                    }
                    i++;
                } while (i < 3 && i < shakes);
                WazaSequence_Free(shakeWaza);
            }
            if (shakes < 4 && missWzx != 0) {
                waza = Sequence_GetWaza(seq, missWzx, 4);
                WazaSequence_Start(waza, 1);
                while (WazaSequence_IsActive(waza)) {
                    GSthreadSwitch();
                }
            }
        } else if (mode == 2) {
            if (shakes < 4 && outWzx != 0) {
                WazaSequence_Start(Sequence_GetWaza(seq, outWzx, 4), 1);
            }
        } else if (mode == 3) {
            if (shakes < 4) {
                if (flags != 0) {
                    Sequence_SetFlags(seq, *flags);
                }
                if (outWzx != 0) {
                    waza = Sequence_GetWaza(seq, outWzx, 4);
                    while (WazaSequence_IsActive(waza)) {
                        GSthreadSwitch();
                    }
                }
            }
        } else if (mode == 4) {
            if (outWzx != 0) {
                WazaSequence_Free(Sequence_GetWaza(seq, outWzx, 4));
            }
            if (getWzx != 0) {
                WazaSequence_Free(Sequence_GetWaza(seq, getWzx, 4));
            }
            if (landWzx != 0) {
                WazaSequence_Free(Sequence_GetWaza(seq, landWzx, 4));
            }
            if (shakeWzx != 0) {
                WazaSequence_Free(Sequence_GetWaza(seq, shakeWzx, 4));
            }
            if (missWzx != 0) {
                WazaSequence_Free(Sequence_GetWaza(seq, missWzx, 4));
            }
            if (shakes >= 4) {
                fightOutPokemonFreeSequence(fop);
                fightMenuFightOutPokemonCloseStatusMenu(fop, fightFloor_GetFightType(0), 1);
            } else if (flags != 0) {
                Sequence_SetFlags(seq, *flags);
            }
        }
    } else {
        if (mode == 0) {
            if (outWzx != 0) {
                Sequence_LoadWaza(seq, outWzx, 4, 0);
            }
            if (getWzx != 0) {
                Sequence_LoadWaza(seq, getWzx, 4, 0);
            }
            if (landWzx != 0) {
                Sequence_LoadWaza(seq, landWzx, 4, 0);
            }
            if (shakeWzx != 0) {
                Sequence_LoadWaza(seq, shakeWzx, 4, 0);
            }
            if (missWzx != 0) {
                Sequence_LoadWaza(seq, missWzx, 4, 0);
            }
            if (flags != 0) {
                *flags = Sequence_GetFlags(seq);
                Sequence_SetDefaultFlags(seq);
            }
        } else if (mode == 1) {
            if (getWzx != 0) {
                Sequence_LoadWaza(seq, getWzx, 4, 0);
                waza = Sequence_GetWaza(seq, getWzx, 4);
                WazaSequence_Start(waza, 1);
                battleGridRestoreModelVisibilityFlags();
                while (WazaSequence_IsActive(waza)) {
                    GSthreadSwitch();
                }
                WazaSequence_Free(waza);
            }
            if (landWzx != 0) {
                Sequence_LoadWaza(seq, landWzx, 4, 0);
            }
            if (shakeWzx != 0) {
                Sequence_LoadWaza(seq, shakeWzx, 4, 0);
                waza = Sequence_GetWaza(seq, landWzx, 4);
                WazaSequence_Start(waza, 1);
                while (WazaSequence_IsActive(waza)) {
                    GSthreadSwitch();
                }
                WazaSequence_Free(waza);
                u8 j = 0;
                do {
                    shakeWaza = Sequence_GetWaza(seq, shakeWzx, 4);
                    WazaSequence_Start(shakeWaza, 1);
                    while (WazaSequence_IsActive(shakeWaza)) {
                        GSthreadSwitch();
                    }
                    j++;
                } while (j < 3 && j < shakes);
                WazaSequence_Free(shakeWaza);
            }
            if (shakes < 4 && missWzx != 0) {
                Sequence_LoadWaza(seq, missWzx, 4, 0);
                waza = Sequence_GetWaza(seq, missWzx, 4);
                WazaSequence_Start(waza, 1);
                while (WazaSequence_IsActive(waza)) {
                    GSthreadSwitch();
                }
                WazaSequence_Free(waza);
            }
        } else if (mode == 2) {
            if (shakes < 4 && outWzx != 0) {
                WazaSequence_Start(Sequence_GetWaza(seq, outWzx, 4), 1);
            }
        } else if (mode == 3) {
            if (shakes < 4) {
                if (flags != 0) {
                    Sequence_SetFlags(seq, *flags);
                }
                if (outWzx != 0) {
                    waza = Sequence_GetWaza(seq, outWzx, 4);
                    while (WazaSequence_IsActive(waza)) {
                        GSthreadSwitch();
                    }
                }
            }
        } else if (mode == 4) {
            if (outWzx != 0) {
                WazaSequence_Free(Sequence_GetWaza(seq, outWzx, 4));
            }
            if (shakes >= 4) {
                fightOutPokemonFreeSequence(fop);
                fightMenuFightOutPokemonCloseStatusMenu(fop, fightFloor_GetFightType(0), 1);
            } else if (flags != 0) {
                Sequence_SetFlags(seq, *flags);
            }
        }
    }
}

void fightOutPokemonLoadWazaEffect(FightOutPokemon* fop, u16 waza, u8 kind, u8 flag) {
    s32 wzx = wazaDB_GetWazawzxdataId(waza);
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        Sequence_LoadWaza(seq, wzx, kind, flag);
        u16 res = wazaSequenceSysGetResourceID(seq->kind == 1 ? (ModelSequence*)seq : 0, wzx, kind & 0xFFFF, flag);
        if (res != 0) {
            dbgEffLoadFsysGroupID = waza_resource_data[res].groupId;
        }
    }
}

void fightOutPokemonFreeWazaEffect(FightOutPokemon* fop, u16 waza, s32 kind) {
    s32 wzx = wazaDB_GetWazawzxdataId(waza);
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        WazaSequence_Free(Sequence_GetWaza(seq, wzx, kind));
    }
}

void fightOutPokemonFreeAllSequenceWaza(FightOutPokemon* fop) {
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        Sequence_FreeAllWaza(seq);
    }
}

void fightOutPokemonWazaEffect(FightOutPokemon* fop, s32 a, s32 b, u8 close, s32 menuId) {
    Sequence* seq;
    u8 type = fightFloor_GetFightType(0);
    seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        MenuPokemonStatus status;
        fightOutPokemonToMenuPokemonStatus(fop, &status);
        if (menuId >= 0) {
            menuId = fightMenuGetFightOutPokemonPtrToStatusMenuId(fop, type, 1);
            if (dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
                menuOpenCustom(menuId, 0, 0, 0, 0, 1, &status);
                fightMenuFightOutPokemonCloseStatusMenuAnotherMine(menuId, fop, type, 0, 1);
                fightFloor_SetStatusMenuCnt(menuId, -1);
            }
        }
        fightWazaDoEffect(seq, a, b, close);
        if (close == 1 && menuId >= 0) {
            fightMenuCloseCustom(menuId, 0, 0);
        }
    }
}

void fightOutPokemonDarkPokemonEffect(FightOutPokemon* fop, u8 openMenu, u8 kind, u8 mode) {
    u8 type = fightFloor_GetFightType(0);
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        u16 id;
        if (kind == 0) {
            id = 0x3A;
        } else if (kind == 1) {
            id = 0x88;
        } else if (kind == 2) {
            id = 0x57;
        } else {
            id = 0xD9;
        }
        if (mode == 0) {
            Sequence_LoadWaza(seq, id, 4, 0);
        } else if (mode == 1) {
            WazaSequence_Start(Sequence_GetWaza(seq, id, 4), 1);
            if (openMenu == 1) {
                fightMenuFightOutPokemonOpenStatusMenu(fop, type, 1);
                fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, fop, type, 0, 1);
            }
        } else if (mode == 2) {
            WazaSequence* waza = Sequence_GetWaza(seq, id, 4);
            while (WazaSequence_IsActive(waza)) {
                GSthreadSwitch();
            }
        } else if (mode == 3) {
            WazaSequence_Free(Sequence_GetWaza(seq, id, 4));
        } else if (mode == 4) {
            WazaSequence_Stop(Sequence_GetWaza(seq, id, 4));
        }
    }
}

void fightOutPokemonDarkPokemonKaijoEffect(FightOutPokemon* fop, u8 hp, u8 joutai, u8 kioku, void* msg, u8 mode) {
    Sequence* seq;
    WazaSequence* waza;
    u16 id;
    u8 type = fightFloor_GetFightType(0);
    seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq == 0) {
        return;
    }
    if (mode == 0) {
        if (hp == 1) {
            Sequence_LoadWaza(seq, 0xA3, 4, 0);
        }
        if (joutai == 1) {
            Sequence_LoadWaza(seq, 0x9F, 4, 0);
        }
        if (kioku == 1) {
            Sequence_LoadWaza(seq, 0x9F, 4, 0);
            Sequence_LoadWaza(seq, 0x2C, 4, 0);
        }
        if (!hp && !joutai && !kioku) {
            Sequence_LoadWaza(seq, 0x57, 4, 0);
        }
    } else if (mode == 1) {
        if (hp == 1) {
            WazaSequence_Start(Sequence_GetWaza(seq, 0xA3, 4), 1);
            GSsndPlayVolume(fightOutPokemonGetVoiceSndId(fop), 0, 0xFF, 0);
            fightMenuOpenMsg(msg);
            if (!joutai) {
                fightMenuFightOutPokemonRenewStatusMenu(fop, type, 1);
            }
        }
        if (joutai == 1) {
            if (hp == 1) {
                WazaSequence* waza = Sequence_GetWaza(seq, 0xA3, 4);
                while (WazaSequence_IsActive(waza)) {
                    GSthreadSwitch();
                }
            }
            WazaSequence_Start(Sequence_GetWaza(seq, 0x9F, 4), 1);
            if (!hp) {
                GSsndPlayVolume(fightOutPokemonGetVoiceSndId(fop), 0, 0xFF, 0);
                fightMenuOpenMsg(msg);
            }
            fightMenuFightOutPokemonRenewStatusMenu(fop, type, 1);
        }
        if (kioku == 1) {
            WazaSequence_Start(Sequence_GetWaza(seq, 0x2C, 4), 1);
            fightMenuOpenMsg(msg);
            if (!joutai) {
                fightMenuFightOutPokemonRenewStatusMenu(fop, type, 1);
            }
        }
        if (!hp && !joutai && !kioku) {
            WazaSequence_Start(Sequence_GetWaza(seq, 0x57, 4), 1);
            fightMenuOpenMsg(msg);
        }
    } else if (mode == 2) {
        if (hp == 1) {
            id = 0xA3;
        }
        if (joutai == 1) {
            id = 0x9F;
        }
        if (kioku == 1) {
            id = 0x2C;
        }
        if (!hp && !joutai && !kioku) {
            id = 0x57;
        }
        waza = Sequence_GetWaza(seq, id, 4);
        while (WazaSequence_IsActive(waza)) {
            GSthreadSwitch();
        }
    } else if (mode == 3) {
        if (hp == 1) {
            WazaSequence_Free(Sequence_GetWaza(seq, 0xA3, 4));
        }
        if (joutai == 1) {
            WazaSequence_Free(Sequence_GetWaza(seq, 0x9F, 4));
        }
        if (kioku == 1) {
            WazaSequence_Free(Sequence_GetWaza(seq, 0x2C, 4));
        }
        if (!hp && !joutai && !kioku) {
            WazaSequence_Free(Sequence_GetWaza(seq, 0x57, 4));
        }
    }
}

}

static u32 _fightOutPokemonGetTenkiyaPkxDataId(u16 tenki) {
    switch (tenki) {
    case 1:
        return 0x19F;
    case 2:
        return 0x19E;
    case 4:
        return 0x1A0;
    default:
        return 0x181;
    }
}

extern "C" {

void fightOutPokemonRegWzxLoad(FightOutPokemon* fop) {
    itemBallDB_GetDowninWzxDataId(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(fop)));
}

}

static u8 _fightOutPokemonRegWzxFreeSub(void* fop, u16 idx, void* data) {
    RegWzxWork* work = (RegWzxWork*)data;
    FightOutPokemon* self = work->fop;
    Pokemon* p = fightOutPokemonGetPokemonPtr((FightOutPokemon*)fop);
    if (fop == self) {
        return 1;
    }
    u32 wzx = itemBallDB_GetDowninWzxDataId(pokemon_GetCatchBallId(p));
    if (wzx == 0) {
        return 1;
    }
    if (work->wzx == wzx) {
        work->count++;
    }
    return 1;
}

extern "C" {

void fightOutPokemonRegWzxFree(FightOutPokemon* fop) {
    RegWzxWork work;
    u32 wzx = itemBallDB_GetDowninWzxDataId(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(fop)));
    if (wzx != 0) {
        work.fop = fop;
        work.wzx = wzx;
        work.count = 0;
        fightFloorLoopValidFightOutPokemon(0, _fightOutPokemonRegWzxFreeSub, &work, 0);
    }
}

Sequence* fightOutPokemonCreateSequence(FightOutPokemon* fop, u16 tenki, s8 rare) {
    Pokemon pokemon;
    u32 rnd;
    u32 catchRnd;
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    FightPokemon* fp = fightOutPokemon_GetFightPokemonPtr(fop);
    pokemonBiosCopy(&pokemon, p);
    u16 dataId = pokemon_GetPokemonDataId(&pokemon);
    u32 pkx = pokemonDB_GetPkxDataId(dataId);
    if (dataId == 0x181) {
        pkx = _fightOutPokemonGetTenkiyaPkxDataId(tenki);
    }
    if (fightOutPokemonIsJoutaiDataId(fop, 0x14) == 1) {
        pkx = 0x19D;
    }
    if (pkx == 0) {
        return 0;
    }
    fightOutPokemonGetRndStatus(fop, &rnd, &catchRnd);
    pokemon_SetRnd(&pokemon, rnd);
    pokemon_SetCatchTrainerRnd(&pokemon, catchRnd);
    if (rare == -1) {
        rare = pokemonCheckRare(&pokemon);
    }
    u32 form;
    switch (pkx) {
    case 0xC9:
        form = pokemonGetAnnonKatati(rnd);
        break;
    case 0x19A:
        form = pokemonGetFightPokemonDeoxysSel(fp);
        break;
    case 0xF9:
        if (pokemonIsDarkPokemon(p) == 1) {
            pkx = 0x1A1;
        }
        form = rnd;
        break;
    default:
        form = rnd;
        break;
    }
    Sequence* seq = Sequence_LoadPokemon(pkx, form, rare != 0);
    pokemonSetSequenceStatus(&pokemon, seq);
    fightOutPokemonRegWzxLoad(fop);
    return seq;
}

void fightOutPokemonSetWazaEffectDownFlag(FightOutPokemon* fop, u8 flag) {
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        Sequence_SetDownFlag(seq, flag);
    }
}

u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon* fop) {
    return fightOutPokemon_GetTokuseiDataId(fop);
}

void fightOutPokemonSetTokuseiDataId(FightOutPokemon* fop, u16 tokusei) {
    fightOutPokemon_SetTokuseiDataId(fop, tokusei);
}

u16 fightOutPokemonGetZokuseiDataId(FightOutPokemon* fop, u8 idx) {
    return fightOutPokemon_GetZokuseiDataId(fop, idx);
}

void fightOutPokemonSetZokuseiDataId(FightOutPokemon* fop, u8 idx, u16 zokusei) {
    fightOutPokemon_SetZokuseiDataId(fop, idx, zokusei);
}

u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon* fop, u16 zokusei) {
    if (zokusei == fightOutPokemonGetZokuseiDataId(fop, 0) || zokusei == fightOutPokemonGetZokuseiDataId(fop, 1)) {
        return 1;
    }
    return 0;
}

u16 fightOutPokemonGetTeikouZokuseiDataIdAry(FightOutPokemon* fop, u16 waza, s32* ary) {
    u16 i;
    for (i = 0; i < 18; i++) {
        ary[i] = -1;
    }
    u16 count = 0;
    for (i = 0; i < 18; i++) {
        if (fightOutPokemonIsZokuseiDataId(fop, i) != 1) {
            u16 joutai = zokuseiGetWazaJoutai(waza, i);
            if (joutai == 0x42 || joutai == 0x43) {
                ary[count] = i;
                count++;
            }
        }
    }
    return count;
}

void fightPokemonInit(FightPokemon* fp) {
    if (fp != 0) {
        fightPokemon_SetMotoPokemonPtr(fp, 0);
        pokemonInit(fightPokemon_GetPokemonBuffPtr(fp));
        joutaiInitAry(fightPokemon_GetFightJoutaiPtr(fp, 0), 1);
        fightPokemon_SetEntryId(fp, -1);
        fightPokemon_SetCatchEntryFlag(fp, 0);
        fightPokemon_SetLevelUpFlag(fp, 0);
        fightPokemon_SetDarkOutFlag(fp, 0);
        fightPokemon_SetHokakuFlag(fp, 0);
        for (u8 i = 0; i < 0x40; i++) {
            fightPokemon_SetAiDamage(fp, i, 0, 0);
            fightPokemon_SetAiDamage(fp, i, 1, 0);
        }
    }
}

void fightPokemonInitAry(FightPokemon* ary, u16 count) {
    if (ary != 0) {
        for (u16 i = 0; i < count; i++) {
            fightPokemonInit(&ary[i]);
        }
    }
}

void fightOutPokemonInitFightActionBuff(FightOutPokemon* fop) {
    FightAction* action = fightOutPokemon_GetFightActionBuffPtr(fop);
    if (action != 0) {
        fightActionInit(action);
        fightWazaInit(fightOutPokemon_GetFightWazaPtr(fop));
        fightItemInit(fightOutPokemon_GetFightItemPtr(fop));
    }
}

void fightOutPokemonInitOneTurn(FightOutPokemon* fop) {
    fightOutPokemon_SetDamageAtkValue(fop, 0);
    fightOutPokemon_SetDamageAtkTargetId(fop, 0);
    fightOutPokemon_SetDamageSpeValue(fop, 0);
    fightOutPokemon_SetDamageSpeTargetId(fop, 0);
    fightOutPokemon_SetMahiNoAttackFlag(fop, 0);
    fightOutPokemon_SetKonranMyselfAttackFlag(fop, 0);
    fightOutPokemon_SetOutWazaKoukanaiFlag(fop, 0);
    fightOutPokemon_SetTameWazaFlag(fop, 0);
    fightOutPokemon_SetItemNigeruFlag(fop, 0);
    fightOutPokemon_SetHuuinNoAttackFlag(fop, 0);
    fightOutPokemon_SetMeroMeroNoAttackFlag(fop, 0);
    fightOutPokemon_SetKanashibariNoAttackFlag(fop, 0);
    fightOutPokemon_SetChouhatsuNoAttackFlag(fop, 0);
    fightOutPokemon_SetIchamonNoAttackFlag(fop, 0);
    fightOutPokemon_SetHirumuNoAttackFlag(fop, 0);
    fightOutPokemon_SetPassPpdecFlag(fop, 0);
    fightOutPokemon_SetFightActionFlag(fop, 0);
}

void fightOutPokemonInitOneSelfTurn(FightOutPokemon* fop) {
    fightOutPokemon_SetDoClearbodyFlag(fop, 0);
    fightOutPokemon_SetReceivesWazaHiraishinFlag(fop, 0);
    fightOutPokemon_SetVanishoffFlag(fop, 0);
    fightOutPokemon_SetDoIkakuFlag(fop, 0);
    fightOutPokemon_SetDoTraceFlag(fop, 0);
    fightOutPokemon_SetNoPressureFlag(fop, 0);
    fightOutPokemon_SetIrekaetaFlag(fop, 0);
    fightOutPokemon_SetItemKoraetaFlag(fop, 0);
    fightOutPokemon_SetKaigaraDamageValue(fop, 0);
    fightOutPokemon_SetMyselfDamageAtkValue(fop, 0);
    fightOutPokemon_SetMyselfDamageAtkTargetId(fop, 0);
    fightOutPokemon_SetMyselfDamageSpeValue(fop, 0);
    fightOutPokemon_SetMyselfDamageSpeTargetId(fop, 0);
}

void fightOutPokemonInitFightOutPokemonEnemyAry(FightOutPokemon* fop) {
    fightOutPokemonEnemyInitAry(fightOutPokemon_GetFightOutPokemonEnemyPtr(fop, 0), 4);
}

void fightOutPokemonInitAbiCntAll(FightOutPokemon* fop) {
    u16 ids[7] = {0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC};
    for (u8 i = 0; i < 7; i++) {
        pokemonSetStatus(fop, 0, ids[i], 0, 6);
    }
}

void fightOutPokemonInit(FightOutPokemon* fop) {
    u8 i;

    if (fop != 0) {
        fightOutPokemon_SetMotoFightPokemonPtr(fop, 0);
        fightOutPokemon_SetFightPokemonPtr(fop, 0);
        fightPokemonInit(fightOutPokemon_GetFightPokemonHensinBuffPtr(fop));
        joutaiInitAry(fightOutPokemon_GetFightoutJoutaiPtr(fop, 0), 0x34);
        fightOutPokemonInitAbiCntAll(fop);
        fightOutPokemonBiosSetHensinMotoPkxId(fop, 0);
        fightOutPokemon_SetFightoutTurnCount(fop, 2);
        fightOutPokemon_SetSequencePtr(fop, 0);
        for (i = 0; i < 12; i++) {
            fightOutPokemon_SetMeetEnemyFightPokemonEntryId(fop, i, -1);
        }
        fightOutPokemonInitFightActionBuff(fop);
        fightWazaInit(fightOutPokemon_GetKeepFightWazaPtr(fop));
        for (i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(fop, i, 9);
        }
        fightOutPokemonSetTokuseiDataId(fop, 0);
        u32* cur = fightOutPokemon_GetWazaMenuCurPtr(fop);
        if (cur != 0) {
            *cur = 0;
        }
        fightOutPokemon_SetSketchWazaDataId(fop, 0);
        fightOutPokemon_SetLastSelectWazaDataId(fop, 0);
        fightOutPokemon_SetLastUseWazaDataId(fop, 0);
        fightOutPokemon_SetLastReceiveWazaTargetDataId(fop, 0);
        fightOutPokemon_SetHitWazaDataId(fop, 0);
        fightOutPokemon_SetHitWazaZokuseiDataId(fop, 9);
        fightOutPokemon_SetGamanDamageValue(fop, 0);
        fightOutPokemon_SetGamanDamageTargetId(fop, 0);
        fightOutPokemon_SetOumuWazaDataId(fop, 0);
        fightOutPokemon_SetOumuWazaAllyDataId(fop, 0);
        fightOutPokemon_SetComboFuncId(fop, 0);
        fightOutPokemon_SetFixAiWaza(fop, 0);
        fightOutPokemon_SetFixAiDef(fop, 0);
        fop->setComboFuncId(0);
        fightOutPokemon_SetNamakeFlag(fop, 0);
        fightOutPokemon_SetSuccessCnt(fop, 0);
        fightOutPokemon_SetStockItemDataId(fop, 0);
        fightOutPokemonInitOneTurn(fop);
        fightOutPokemonInitOneSelfTurn(fop);
        fightOutPokemon_SetKizetuFlag(fop, 0);
        fn_8014718C(fop, 0);
        fightOutPokemon_SetIrekaeTargetEntryId(fop, -1);
        fightOutPokemonInitFightOutPokemonEnemyAry(fop);
    }
}

void fightOutPokemonInitAry(FightOutPokemon* ary, u16 count) {
    if (ary != 0) {
        for (u16 i = 0; i < count; i++) {
            fightOutPokemonInit(&ary[i]);
        }
    }
}

void fightPokemonCreate(FightTrainer* trainer, FightPokemon* fp, Pokemon* p, s16 entry) {
    if (fp != 0 && p != 0) {
        fightPokemonInit(fp);
        fightPokemon_SetMotoPokemonPtr(fp, p);
        pokemonBiosCopy(fightPokemon_GetPokemonBuffPtr(fp), p);
        fightPokemon_SetEntryId(fp, entry);
    }
}

bool fightPokemonCheckValid(FightPokemon* fp) {
    if (fp == 0) {
        return 0;
    }
    if (fightGetFightResultId() == 1) {
        return 0;
    }
    Pokemon* moto = fightPokemon_GetMotoPokemonPtr(fp);
    if (moto == 0) {
        return 0;
    }
    if (!pokemonCheckValid(moto)) {
        return 0;
    }
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    if (!pokemonCheckValid(p)) {
        return 0;
    }
    s16 entry = fightPokemon_GetEntryId(fp);
    return entry >= 0;
}

void fightOutPokemonCreate(FightOutPokemon* fop, FightPokemon* fp, Sequence* seq) {
    if (fop != 0 && fp != 0) {
        Pokemon* p = fightPokemonGetPokemonPtr(fp);
        fightOutPokemonInit(fop);
        fightOutPokemon_SetMotoFightPokemonPtr(fop, fp);
        fightOutPokemon_SetFightPokemonPtr(fop, fp);
        if (seq != 0) {
            fightOutPokemon_SetSequencePtr(fop, seq);
            fightFloorSetShadow();
        }
        u16 id = pokemon_GetPokemonDataId(p);
        for (u16 i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(fop, i, pokemonDB_GetZokuseiDataId(id, i));
        }
        u16 tokusei = pokemonGetTokuseiDataId(p);
        fightOutPokemonSetTokuseiDataId(fop, tokusei);
    }
}

bool fightOutPokemonCheckValid(FightOutPokemon* fop) {
    if (fop == 0) {
        return 0;
    }
    if (fightGetFightResultId() == 1) {
        return 0;
    }
    FightPokemon* fp = fightOutPokemon_GetFightPokemonPtr(fop);
    if (fp == 0) {
        return 0;
    }
    return fightPokemonCheckValid(fp) != 0;
}

bool fightPokemonCheckFightOut(FightPokemon* fp) {
    if (fp == 0) {
        return 0;
    }
    if (!fightPokemonCheckValid(fp)) {
        return 0;
    }
    if (fightPokemon_GetHokakuFlag(fp) == 1) {
        return 0;
    }
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return pokemonCheckFightOut(p) != 0;
}

bool fightOutPokemonCheckFightOut(FightOutPokemon* fop) {
    if (fop == 0) {
        return 0;
    }
    if (!fightOutPokemonCheckValid(fop)) {
        return 0;
    }
    if (fightOutPokemon_GetKizetuFlag(fop) == 1) {
        return 0;
    }
    return fightPokemonCheckFightOut(fightOutPokemon_GetFightPokemonPtr(fop)) != 0;
}

}

static FightOutPokemon* _fightOutPokemonCheckFightActionSelectSub(FightOutPokemon* fop, u16 waza, u16 type) {
    return fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(
        fightWaza_GetTargetDataId(fightOutPokemon_GetKeepFightWazaPtr(fop)), type);
}

extern "C" {

u8 fightOutPokemonCheckFightActionSelect(FightOutPokemon* fop, u8 create) {
    u8 type = fightFloor_GetFightType(0);
    if (fop == 0) {
        return 0;
    }
    if (!fightOutPokemonCheckFightOut(fop)) {
        return 0;
    }
    if (fightOutPokemonIsJoutaiDataId(fop, 0x12) == 1 || fightOutPokemonIsJoutaiDataId(fop, 0x22) == 1) {
        if (create) {
            FightWaza* keep = fightOutPokemon_GetKeepFightWazaPtr(fop);
            if (fightWazaCheckValid(keep)) {
                u16 waza = fightWaza_GetUseWazaDataId(keep);
                s8 banme = fightWaza_GetWazaBanme(keep);
                fightOutPokemonCreateFightActionAttackWaza(
                    fop, 0, 0x13, 0, fight_action_data_waza, waza,
                    fightTargetGetTragetPtrToRelativeHostSideFightTargetId(
                        fightSeqSelectDefensePokemonPtr(fop, waza, type, _fightOutPokemonCheckFightActionSelectSub,
                                                        1, 0, -1),
                        type),
                    banme, 1);
            }
        }
        return 0;
    }
    return 1;
}

Pokemon* fightPokemonGetPokemonPtr(FightPokemon* fp) {
    if (fp == 0) {
        return 0;
    }
    return fightPokemon_GetPokemonBuffPtr(fp);
}

Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon* fop) {
    if (fop == 0) {
        return 0;
    }
    return fightPokemonGetPokemonPtr(fightOutPokemon_GetFightPokemonPtr(fop));
}

s16 fightOutPokemonGetFightEntryId(FightOutPokemon* fop) {
    if (fop == 0) {
        return -1;
    }
    FightPokemon* moto = fightOutPokemon_GetMotoFightPokemonPtr(fop);
    if (moto == 0) {
        return -1;
    }
    return fightPokemon_GetEntryId(moto);
}

void fightOutPokemonSetOnZukanFlag(FightOutPokemon* fop, u8 flag) {
    if (fop != 0) {
        pokemonSetOnZukanFlag(fightPokemon_GetMotoPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(fop)), flag);
    }
}

u8 fightOutPokemonCheckMeetEnemyFightPokemon(FightOutPokemon* fop, FightPokemon* fp) {
    if (fop == 0) {
        return 0;
    }
    if (!fightPokemonCheckValid(fp)) {
        return 0;
    }
    s16 entry = fightPokemon_GetEntryId(fp);
    for (u8 i = 0; i < 12; i++) {
        s16 meet = fightOutPokemon_GetMeetEnemyFightPokemonEntryId(fop, i);
        if (meet >= 0 && meet == entry) {
            return 1;
        }
    }
    return 0;
}

s8 fightOutPokemonSetMeetEnemyFightPokemon(FightOutPokemon* fop, FightPokemon* fp) {
    if (fop == 0) {
        return -1;
    }
    if (!fightPokemonCheckValid(fp)) {
        return -1;
    }
    if (fightOutPokemonCheckMeetEnemyFightPokemon(fop, fp) == 1) {
        return -1;
    }
    s16 entry = fightPokemon_GetEntryId(fp);
    for (u8 i = 0; i < 12; i++) {
        if (fightOutPokemon_GetMeetEnemyFightPokemonEntryId(fop, i) < 0) {
            fightOutPokemon_SetMeetEnemyFightPokemonEntryId(fop, i, entry);
            return i;
        }
    }
    return -1;
}

void fightOutPokemonSetMeetEnemyFightPokemonEnemySideAll(FightOutPokemon* fop, FightSide* side) {
    FightTrainer* trainer;
    FightOutPokemon* enemy;
    u16 i;
    u16 j;
    u16 trainerNum;
    u16 pokemonNum;

    fightFloor_GetFightType(0);
    trainerNum = fightFloor_GetFightTypeTrainerNum(0);
    pokemonNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    for (i = 0; i < trainerNum; i++) {
        trainer = fightSide_GetFightTrainerPtr(side, i);
        if (fightTrainerCheckValid(trainer)) {
            for (j = 0; j < pokemonNum; j++) {
                enemy = fightTrainer_GetFightoutPokemonPtr(trainer, j);
                if (fightOutPokemonCheckFightOut(enemy)) {
                    FightPokemon* moto = fightOutPokemon_GetMotoFightPokemonPtr(enemy);
                    fightOutPokemonSetMeetEnemyFightPokemon(fop, moto);
                }
            }
        }
    }
}

u16 fightOutPokemonGetMotoWazaDataId(FightOutPokemon* fop) {
    FightWaza* fightWaza = fightOutPokemon_GetFightWazaPtr(fop);
    if (fightWaza == 0) {
        return 0;
    }
    return fightWaza_GetMotoWazaDataId(fightWaza);
}

u16 fightOutPokemonGetCmpNimblenessWazaDataId(FightOutPokemon* fop) {
    return fightOutPokemonGetMotoWazaDataId(fop);
}

u16 fightOutPokemonGetUseWazaDataId(FightOutPokemon* fop) {
    FightWaza* fightWaza = fightOutPokemon_GetFightWazaPtr(fop);
    if (fightWaza == 0) {
        return 0;
    }
    return fightWaza_GetUseWazaDataId(fightWaza);
}

u8 fightOutPokemonGetWazaZokuseiDataId(FightOutPokemon* fop) {
    FightWaza* fightWaza = fightOutPokemon_GetFightWazaPtr(fop);
    if (fightWaza == 0) {
        return 9;
    }
    return fightWaza_GetZokusei(fightWaza);
}

s8 fightOutPokemonGetFightActionPri(FightOutPokemon* fop) {
    FightAction* action = fightOutPokemon_GetFightActionBuffPtr(fop);
    if (action == 0) {
        return -0x80;
    }
    return fightActionGetPri(action);
}

FightAction* fightOutPokemonCreateFightAction(FightOutPokemon* fop, s32 a, s32 kind, s32 c, void* data, s32 buffId) {
    FightAction* action = fightOutPokemon_GetFightActionBuffPtr(fop);
    if (action == 0) {
        return 0;
    }
    if (fightActionCreate(action, a, fop, kind, c, data) == 1) {
        fightActionBiosSetBuffDataId(action, buffId);
        return action;
    }
    return 0;
}

FightAction* fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon* fop, s32 a, s32 kind, s32 c, void* data,
                                                        s32 waza, u16 target, s8 banme, u8 autoMake) {
    u16 wazaId = waza;
    FightWaza* fightWaza = fightOutPokemon_GetFightWazaPtr(fop);
    if (fightWaza == 0) {
        return 0;
    }
    fightWazaCreate(fightWaza, banme, wazaId, target, autoMake);
    FightAction* action = fightOutPokemonCreateFightAction(fop, a, kind, c, data, waza);
    if (action == 0) {
        return 0;
    }
    return action;
}

u8 fightOutPokemonIsFightActionAttackWazaOut(FightOutPokemon* fop, u16 waza, FightOutPokemon* targetFop) {
    FightAction* action;
    FightWaza* fightWaza;
    u8 type = fightFloor_GetFightType(0);
    u16 target;
    if (fop == 0) {
        return 0;
    }
    if (targetFop == 0) {
        target = 0;
    } else {
        target = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(targetFop, type);
    }
    action = fightOutPokemon_GetFightActionBuffPtr(fop);
    if (action == 0) {
        return 0;
    }
    if (!fightActionCheckValid(action)) {
        return 0;
    }
    if (fightActionGetKindDataId(action) != 0x13) {
        return 0;
    }
    fightWaza = fightOutPokemon_GetFightWazaPtr(fop);
    if (fightWaza == 0) {
        return 0;
    }
    u16 moto = fightWaza_GetMotoWazaDataId(fightWaza);
    u16 seq = wazaDB_GetSeqId(moto);
    if (waza != 0 && moto != waza) {
        return 0;
    }
    u16 wazaTarget = fightWaza_GetTargetDataId(fightWaza);
    if (seq == 0xB0) {
        wazaTarget = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(
            fightTargetGetPtrAsNowFightType(0xE, fop), type);
    }
    if (target != 0 && wazaTarget != target) {
        return 0;
    }
    return 1;
}

FightAction* fightOutPokemonCreateFightActionUseItem(FightOutPokemon* fop, s32 a, s32 kind, s32 c, void* data,
                                                     s32 item, u16 target, u8 itemBanme, u8 buff) {
    FightItem* fightItem;
    u16 itemId = item;
    fightItem = fightOutPokemon_GetFightItemPtr(fop);
    if (fightItem == 0) {
        return 0;
    }
    fightItemCreate(fightItem, itemId, target, itemBanme);
    fightItem_SetBuff(fightItem, buff);
    FightAction* action = fightOutPokemonCreateFightAction(fop, a, kind, c, data, item);
    if (action == 0) {
        return 0;
    }
    return action;
}

u16 fightOutPokemonGetFightActionUseItemDataId(FightOutPokemon* fop) {
    fightFloor_GetFightType(0);
    if (fop == 0) {
        return 0;
    }
    FightAction* action = fightOutPokemon_GetFightActionBuffPtr(fop);
    if (action == 0) {
        return 0;
    }
    if (!fightActionCheckValid(action)) {
        return 0;
    }
    if (fightActionGetKindDataId(action) != 0x12) {
        return 0;
    }
    FightItem* fightItem = fightOutPokemon_GetFightItemPtr(fop);
    if (fightItem == 0) {
        return 0;
    }
    return fightItem_GetItemDataId(fightItem);
}

u8 fightOutPokemonIsFightActionUseItem(FightOutPokemon* fop, u16 item, FightOutPokemon* targetFop) {
    u8 type = fightFloor_GetFightType(0);
    u16 target;
    if (fop == 0) {
        return 0;
    }
    if (targetFop == 0) {
        target = 0;
    } else {
        target = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(targetFop, type);
    }
    FightAction* action = fightOutPokemon_GetFightActionBuffPtr(fop);
    if (action == 0) {
        return 0;
    }
    if (!fightActionCheckValid(action)) {
        return 0;
    }
    if (fightActionGetKindDataId(action) != 0x12) {
        return 0;
    }
    FightItem* fightItem = fightOutPokemon_GetFightItemPtr(fop);
    if (fightItem == 0) {
        return 0;
    }
    u16 itemId = fightItem_GetItemDataId(fightItem);
    u16 itemTarget = fightItem_GetTargetDataId(fightItem);
    if (item != 0 && itemId != item) {
        return 0;
    }
    if (target != 0 && itemTarget != target) {
        return 0;
    }
    return 1;
}

u8 fightOutPokemonIsFightActionUseItemKind(FightOutPokemon* fop, u8 kind, u8 match) {
    for (u16 i = 0; i < *item_data_index_number; i++) {
        if (itemDataCheckValid(i)) {
            if (match == 1) {
                if (kind != itemDB_GetKind(i)) {
                    continue;
                }
            } else {
                if (kind == itemDB_GetKind(i)) {
                    continue;
                }
            }
            if (fightOutPokemonIsFightActionUseItem(fop, i, 0) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon* fop) {
    FightTrainer* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, fop);
    if (trainer == 0) {
        return 0;
    }
    return fightTrainerIsGcHero(trainer) == 1;
}

void fightOutPokemonFreeSequence(FightOutPokemon* fop) {
    fightOutPokemonRegWzxFree(fop);
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq != 0) {
        fightOutPokemonSetVisibility(fop, 0);
        fightOutPokemon_SetSequencePtr(fop, 0);
        battleGridRemovePokemon(seq);
        Sequence_Free(seq);
    }
}

GSmodel* fightOutPokemonGetGsmodelPtr(FightOutPokemon* fop) {
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (seq == 0) {
        return 0;
    }
    return Sequence_GetGSmodel(seq);
}

void fightPokemonReplace(FightPokemon* a, FightPokemon* b) {
    if (a != 0 && b != 0) {
        FightPokemon tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

u8 fightPokemonCheckMotoFightPokemon(FightPokemon* fp, FightOutPokemon* fop) {
    return fightOutPokemon_GetMotoFightPokemonPtr(fop) == fp;
}

u8 fightOutPokemonCheckIrekaeReserveFightPokemon(FightOutPokemon* fop, FightPokemon* fp) {
    s16 entry = fightPokemon_GetEntryId(fp);
    if (entry < 0) {
        return 0;
    }
    if (entry == fightOutPokemon_GetIrekaeTargetEntryId(fop)) {
        return 1;
    }
    FightAction* action = fightOutPokemon_GetFightActionBuffPtr(fop);
    if (action != 0 && fightActionCheckValid(action) == 1 && fightActionBiosGetKind(action) == 9 &&
        entry == fightActionBiosGetBuffDataId(action)) {
        return 1;
    }
    return 0;
}

u32 fightOutPokemonGetNowNimbleness(FightOutPokemon* fop, u8 useBadge, u8 tenki, u16 hp, void* hero) {
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    if (p == 0) {
        return 0;
    }
    u8 abicnt = fightOutPokemon_GetAbicntNimbleness(fop);
    u16 item = fightOutPokemonGetSoubiItemSoubiDataId(fop);
    s32 itemBuff = figthOutPokemonGetSoubiItemBuff(fop);
    u16 tokusei = fightOutPokemonGetTokuseiDataId(fop);
    u8 badge;
    if (hero != 0) {
        badge = heroGetStatus(hero, 0x11, 0) != 0;
    } else {
        badge = 0;
    }
    u32 nimble = pokemon_GetNimbleness(p);
    if (tokusei == 0x21 && tenki == 2) {
        nimble *= 2;
    } else if (tokusei == 0x22 && tenki == 1) {
        nimble *= 2;
    }
    u32 speed = fightAbicntDoKakeWaru(abicnt, nimble);
    if (useBadge == 1 && badge == 1) {
        speed = speed * 110 / 100;
    }
    if (item == 0x18) {
        speed /= 2;
    }
    if (fightOutPokemonIsJoutaiDataId(fop, 5) == 1) {
        speed /= 4;
    }
    if (item == 0x1A && hp < itemBuff * 0xFFFF / 100) {
        speed = -1;
    }
    return speed;
}

u16 fightPokemonGetSoubiItemDataId(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    if (fightPokemonIsJoutaiDataId(fp, 0x3D) == 1) {
        return 0;
    }
    return pokemonGetSoubiItemDataId(p);
}

u16 fightPokemonGetSoubiItemSoubiDataId(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    if (fightPokemonIsJoutaiDataId(fp, 0x3D) == 1) {
        return 0;
    }
    return pokemonGetSoubiItemSoubiDataId(p);
}

s32 fightPokemonGetSoubiItemBuff(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    if (fightPokemonIsJoutaiDataId(fp, 0x3D) == 1) {
        return 0;
    }
    return pokemonGetSoubiItemBuff(p);
}

u16 fightOutPokemonGetSoubiItemDataId(FightOutPokemon* fop) {
    return fightPokemonGetSoubiItemDataId(fightOutPokemon_GetFightPokemonPtr(fop));
}

u16 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon* fop) {
    return fightPokemonGetSoubiItemSoubiDataId(fightOutPokemon_GetFightPokemonPtr(fop));
}

s32 figthOutPokemonGetSoubiItemBuff(FightOutPokemon* fop) {
    return fightPokemonGetSoubiItemBuff(fightOutPokemon_GetFightPokemonPtr(fop));
}

u8 figthPokemonGetLevel(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return pokemon_GetLevel(p);
}

u8 figthOutPokemonGetLevel(FightOutPokemon* fop) {
    return figthPokemonGetLevel(fightOutPokemon_GetFightPokemonPtr(fop));
}

u16 figthPokemonGetPokemonDataId(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return pokemon_GetPokemonDataId(p);
}

u16 figthOutPokemonGetPokemonDataId(FightOutPokemon* fop) {
    return figthPokemonGetPokemonDataId(fightOutPokemon_GetFightPokemonPtr(fop));
}

u8 fightOutPokemonIsJoutaiNormal(FightOutPokemon* fop) {
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    if (p == 0) {
        return 0;
    }
    return pokemonIsJoutaiNormal(p);
}

u8 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon* fop) {
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    if (p == 0) {
        return 0;
    }
    return pokemonIsJoutaiKaragenki(p);
}

u8 fightOutPokemonIsNokoriHpFollowing(FightOutPokemon* fop, u8 waru) {
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    if (p == 0) {
        return 0;
    }
    return pokemonIsNokoriHpFollowing(p, waru);
}

u16 fightOutPokemonMaxHpWaruValue(FightOutPokemon* fop, u8 waru) {
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    if (p == 0) {
        return 0;
    }
    return pokemonGetMaxHpWaruValue(p, waru);
}

u16 fightOutPokemonNowHpWaruValue(FightOutPokemon* fop, u8 waru) {
    u16 waza = fightOutPokemon_GetUseWazaDataId(fop);
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    if (p == 0) {
        return 0;
    }
    return pokemonGetNowHpWaruValue(p, waru, waza);
}

u8 fightOutPokemonGetNowHpPercentage(FightOutPokemon* fop) {
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    if (p == 0) {
        return 0;
    }
    return pokemonGetNowHpPercentage(p);
}

u8 fightOutPokemonIsHinsi(FightOutPokemon* fop) {
    if (!fightOutPokemonCheckValid(fop)) {
        return 1;
    }
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    if (p == 0) {
        return 1;
    }
    return pokemon_GetHinsi(p);
}

GSchar* fightPokemonGetNicknamePtr(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return pokemon_GetNicknamePtr(p);
}

GSchar* fightOutPokemonGetNicknamePtr(FightOutPokemon* fop) {
    return fightPokemonGetNicknamePtr(fightOutPokemon_GetFightPokemonPtr(fop));
}

GSchar* fightPokemonGetNamePtr(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return GSmsgGetGSchar(pokemonDB_GetName(pokemon_GetPokemonDataId(p)));
}

GSchar* fightOutPokemonGetNamePtr(FightOutPokemon* fop) {
    return fightPokemonGetNamePtr(fightOutPokemon_GetFightPokemonPtr(fop));
}

u32 fightOutPokemonGetVoiceSndId(FightOutPokemon* fop) {
    return pokemonDB_GetVoice(pokemon_GetPokemonDataId(fightOutPokemonGetPokemonPtr(fop)));
}

void fightPokemonGrowBasisStatus(FightPokemon* fp, u8 level) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p != 0) {
        pokemonGrowBasisStatus(p, level);
    }
}

u32 figthPokemonGetExp(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return pokemon_GetExp(p);
}

void figthPokemonSetExp(FightPokemon* fp, u32 exp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p != 0) {
        pokemon_SetExp(p, exp);
    }
}

u32 fightPokemonGetLevelToExp(FightPokemon* fp, u8 level) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return pokemonGetLevelToExp(p, level);
}

void fightPokemonGetEffortFromPokemon(FightPokemon* fp, Pokemon* from, u8 mode) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p != 0) {
        u16 item = fightPokemonGetSoubiItemSoubiDataId(fp);
        pokemonGetEffortFromPokemon(p, item, from, mode);
    }
}

void fightPokemonGetFriendFormPokemonFriendFilterId(FightPokemon* fp, void* out) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p != 0) {
        u16 item = fightPokemonGetSoubiItemSoubiDataId(fp);
        pokemonGetFriendFormPokemonFriendFilterId(p, item, out);
    }
}

FightOutPokemonEnemy* fightOutPokemonCreateFightPokemonEnemyAry(FightOutPokemon* fop, FightOutPokemon* target) {
    FightOutPokemonEnemy* enemy;
    u16 i;

    if (fop == 0) {
        return 0;
    }
    if (!fightOutPokemonCheckValid(target)) {
        return 0;
    }
    FightOutPokemonEnemy* enemies = fightOutPokemon_GetFightOutPokemonEnemyPtr(fop, 0);
    FightOutPokemonEnemy* found = fightOutPokemonEnemySearchAry(enemies, 4, target);
    if (found != 0) {
        return found;
    }
    for (i = 0; i < 4; i++) {
        enemy = (FightOutPokemonEnemy*)((u8*)enemies + i * 0xC);
        if (!fightOutPokemonEnemyCheckValid(enemy)) {
            fightOutPokemonEnemyCreate(enemy, target);
            return enemy;
        }
    }
    return 0;
}

void fightOutPokemonInitFightPokemonEnemyAry(FightOutPokemon* fop, FightOutPokemon* target) {
    if (fop != 0) {
        FightOutPokemonEnemy* enemy =
            fightOutPokemonEnemySearchAry(fightOutPokemon_GetFightOutPokemonEnemyPtr(fop, 0), 4, target);
        if (enemy != 0) {
            u16 oumu = fightOutPokemonEnemyBiosGetOumuWazaDataId(enemy);
            fightOutPokemonEnemyInit(enemy);
            if (oumu != 0 && oumu != 0x176 && oumu != 0xFFFF && fightOutPokemon_GetOumuWazaDataId(fop) == 0 &&
                fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(fop, 0) == 0) {
                fightOutPokemon_SetOumuWazaDataId(fop, oumu);
            }
        }
    }
}

void fightOutPokemonCreateFightPokemonEnemyAryEnemySideAll(FightOutPokemon* fop, FightSide* side) {
    FightTrainer* trainer;
    FightOutPokemon* enemy;
    u16 i;
    u16 j;
    u16 trainerNum;
    u16 pokemonNum;

    fightFloor_GetFightType(0);
    trainerNum = fightFloor_GetFightTypeTrainerNum(0);
    pokemonNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    for (i = 0; i < trainerNum; i++) {
        trainer = fightSide_GetFightTrainerPtr(side, i);
        if (fightTrainerCheckValid(trainer)) {
            for (j = 0; j < pokemonNum; j++) {
                enemy = fightTrainer_GetFightoutPokemonPtr(trainer, j);
                if (fightOutPokemonCheckFightOut(enemy)) {
                    fightOutPokemonCreateFightPokemonEnemyAry(fop, enemy);
                }
            }
        }
    }
}

u8 fightOutPokemonIsAlly(FightOutPokemon* fop, FightOutPokemon* other) {
    u8 type = fightFloor_GetFightType(0);
    if (fop == 0) {
        return 0;
    }
    if (other == 0) {
        return 0;
    }
    void* side = fightTargetGetPtr(2, fop, type);
    return side == fightTargetGetPtr(2, other, type);
}

void fightPokemonInitJoutaiDataId(FightPokemon* fp, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        pokemonInitJoutaiDataId(fightPokemonGetPokemonPtr(fp), id);
    } else if (joutaiDataBiosGetStatus(id) == 0xCD) {
        joutaiInitJoutaiDataId(fp, id);
    }
}

u8 fightPokemonIsJoutaiDataId(FightPokemon* fp, u16 id) {
    if (fp == 0) {
        return 0;
    }
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        return pokemonIsJoutaiDataId(fightPokemonGetPokemonPtr(fp), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xCD) {
        return 0;
    }
    return joutaiIsJoutaiDataId(fp, id);
}

u8 fightPokemonCheckWriteJoutaiDataId(FightPokemon* fp, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        return pokemonCheckWriteJoutaiDataId(fightPokemonGetPokemonPtr(fp), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xCD) {
        return 0;
    }
    return joutaiCheckWriteJoutaiDataId(fp, id);
}

void fightPokemonWriteJoutaiDataId(FightPokemon* fp, u16 id, u32 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        pokemonWriteJoutaiDataId(fightPokemonGetPokemonPtr(fp), id, value);
    } else if (joutaiDataBiosGetStatus(id) == 0xCD) {
        joutaiWriteJoutaiDataId(fp, id, value);
    }
}

s32 fightPokemonGetCountAsJoutaiDataId(FightPokemon* fp, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        return pokemonGetCountAsJoutaiDataId(fightPokemonGetPokemonPtr(fp), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xCD) {
        return -1;
    }
    return joutaiGetCountAsJoutaiDataId(fp, id);
}

void fightPokemonSetCountAsJoutaiDataId(FightPokemon* fp, u16 id, s32 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        pokemonSetCountAsJoutaiDataId(fightPokemonGetPokemonPtr(fp), id, value);
    } else if (joutaiDataBiosGetStatus(id) == 0xCD) {
        joutaiSetCountAsJoutaiDataId(fp, id, value);
    }
}

s32 fightPokemonGetKaisuuJoutaiDataId(FightPokemon* fp, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        return pokemonGetKaisuuJoutaiDataId(fightPokemonGetPokemonPtr(fp), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xCD) {
        return -1;
    }
    return joutaiGetKaisuuJoutaiDataId(fp, id);
}

s32 fightPokemonGetNowKaisuuJoutaiDataId(FightPokemon* fp, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        return pokemonGetNowKaisuuJoutaiDataId(fightPokemonGetPokemonPtr(fp), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xCD) {
        return -1;
    }
    return joutaiGetNowKaisuuJoutaiDataId(fp, id);
}

void fightPokemonSetNowKaisuuJoutaiDataId(FightPokemon* fp, u16 id, u8 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        pokemonSetNowKaisuuJoutaiDataId(fightPokemonGetPokemonPtr(fp), id, value);
    } else if (joutaiDataBiosGetStatus(id) == 0xCD) {
        joutaiSetNowKaisuuJoutaiDataId(fp, id, value);
    }
}

void fightPokemonSetKaisuuJoutaiDataId(FightPokemon* fp, u16 id, u8 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        pokemonSetKaisuuJoutaiDataId(fightPokemonGetPokemonPtr(fp), id, value);
    } else if (joutaiDataBiosGetStatus(id) == 0xCD) {
        joutaiSetKaisuuJoutaiDataId(fp, id, value);
    }
}

u8 fightPokemonGetUserFightTargetIdJoutaiDataId(FightPokemon* fp, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
    }
    if (joutaiDataBiosGetStatus(id) != 0xCD) {
        return 0;
    }
    return joutaiGetUserFightTargetId(fp, id);
}

u16 fightPokemonGetIdBuffJoutaiDataId(FightPokemon* fp, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
    }
    if (joutaiDataBiosGetStatus(id) != 0xCD) {
        return 0;
    }
    return joutaiGetIdBuff(fp, id);
}

void fightPokemonSetIdBuffJoutaiDataId(FightPokemon* fp, u16 id, u16 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        return;
    }
    if (joutaiDataBiosGetStatus(id) == 0xCD) {
        joutaiSetIdBuff(fp, id, value);
    }
}

void fightPokemonCopyJoutaiDataId(FightPokemon* dst, FightPokemon* src, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        pokemonCopyJoutaiDataId(fightPokemonGetPokemonPtr(dst), fightPokemonGetPokemonPtr(src), id);
    } else if (joutaiDataBiosGetStatus(id) == 0xCD) {
        joutaiCopy(dst, src, id);
    }
}

s32 fightPokemonGetBuffJoutaiDataId(FightPokemon* fp, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
    }
    if (joutaiDataBiosGetStatus(id) != 0xCD) {
        return 0;
    }
    return joutaiGetBuff(fp, id);
}

void fightPokemonSetBuffJoutaiDataId(FightPokemon* fp, u16 id, s32 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8) {
        return;
    }
    if (joutaiDataBiosGetStatus(id) == 0xCD) {
        joutaiSetBuff(fp, id, value);
    }
}

void fightOutPokemonResetSeqStatus(FightOutPokemon* fop, u16 id) {
    Sequence* seq = fightOutPokemon_GetSequencePtr(fop);
    if (id == 0) {
        if (seq != 0) {
            Sequence_ResetStatus(seq, 1);
            Sequence_ResetStatus(seq, 2);
        }
    } else if (seq != 0) {
        if (id == 8) {
            Sequence_ResetStatus(seq, 1);
        }
        if (id == 7) {
            Sequence_ResetStatus(seq, 2);
        }
    }
}

void fightOutPokemonInitJoutaiDataId(FightOutPokemon* fop, u16 id) {
    fightOutPokemonResetSeqStatus(fop, id);
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        fightPokemonInitJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id);
    } else if (joutaiDataBiosGetStatus(id) == 0xD8) {
        joutaiInitJoutaiDataId(fop, id);
    }
}

u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (fop == 0) {
        return 0;
    }
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        return fightPokemonIsJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xD8) {
        return 0;
    }
    return joutaiIsJoutaiDataId(fop, id);
}

u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        return fightPokemonCheckWriteJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xD8) {
        return 0;
    }
    return joutaiCheckWriteJoutaiDataId(fop, id);
}

void fightOutPokemonWriteJoutaiDataId(FightOutPokemon* fop, u16 id, u32 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        fightPokemonWriteJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id, value);
    } else if (joutaiDataBiosGetStatus(id) == 0xD8) {
        joutaiWriteJoutaiDataId(fop, id, value);
    }
}

s32 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        return fightPokemonGetCountAsJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xD8) {
        return -1;
    }
    return joutaiGetCountAsJoutaiDataId(fop, id);
}

s32 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        return fightPokemonGetKaisuuJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xD8) {
        return -1;
    }
    return joutaiGetKaisuuJoutaiDataId(fop, id);
}

s32 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        return fightPokemonGetNowKaisuuJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xD8) {
        return -1;
    }
    return joutaiGetNowKaisuuJoutaiDataId(fop, id);
}

void fightOutPokemonSetNowKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id, u8 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        fightPokemonSetNowKaisuuJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id, value);
    } else if (joutaiDataBiosGetStatus(id) == 0xD8) {
        joutaiSetNowKaisuuJoutaiDataId(fop, id, value);
    }
}

void fightOutPokemonSetKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id, u8 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        fightPokemonSetKaisuuJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id, value);
    } else if (joutaiDataBiosGetStatus(id) == 0xD8) {
        joutaiSetKaisuuJoutaiDataId(fop, id, value);
    }
}

u8 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        return fightPokemonGetUserFightTargetIdJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xD8) {
        return 0;
    }
    return joutaiGetUserFightTargetId(fop, id);
}

u16 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        return fightPokemonGetIdBuffJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xD8) {
        return 0;
    }
    return joutaiGetIdBuff(fop, id);
}

void fightOutPokemonSetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id, u16 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        fightPokemonSetIdBuffJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id, value);
    } else if (joutaiDataBiosGetStatus(id) == 0xD8) {
        joutaiSetIdBuff(fop, id, value);
    }
}

void fightOutPokemonCopyJoutaiDataId(FightOutPokemon* dst, FightOutPokemon* src, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        fightPokemonCopyJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(dst), fightOutPokemon_GetFightPokemonPtr(src), id);
    } else if (joutaiDataBiosGetStatus(id) == 0xD8) {
        joutaiCopy(dst, src, id);
    }
}

s32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        return fightPokemonGetBuffJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id);
    }
    if (joutaiDataBiosGetStatus(id) != 0xD8) {
        return 0;
    }
    return joutaiGetBuff(fop, id);
}

void fightOutPokemonSetBuffJoutaiDataId(FightOutPokemon* fop, u16 id, s32 value) {
    if (joutaiDataBiosGetStatus(id) == 0x7C || joutaiDataBiosGetStatus(id) == 0xC8 ||
        joutaiDataBiosGetStatus(id) == 0xCD) {
        fightPokemonSetBuffJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(fop), id, value);
    } else if (joutaiDataBiosGetStatus(id) == 0xD8) {
        joutaiSetBuff(fop, id, value);
    }
}

u8 fightPokemonIsHpMantan(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return pokemonIsHpMantan(p);
}

u8 fightOutPokemonIsHpMantan(FightOutPokemon* fop) {
    return fightPokemonIsHpMantan(fightOutPokemon_GetFightPokemonPtr(fop));
}

u8 fightPokemonGetSex(FightPokemon* fp) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return pokemonGetSex(p);
}

u8 fightOutPokemonGetSex(FightOutPokemon* fop) {
    return fightPokemonGetSex(fightOutPokemon_GetFightPokemonPtr(fop));
}

void fightOutPokemonCopyStatus(FightOutPokemon* dst, FightOutPokemon* src, u16 id) {
    s32 value = pokemonGetStatus(src, 0, id, 0);
    pokemonSetStatus(dst, 0, id, 0, value);
}

void fightOutPokemonCopyAllAbiCnt(FightOutPokemon* dst, FightOutPokemon* src) {
    u16 ids[7] = {0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC};
    for (u8 i = 0; i < 7; i++) {
        fightOutPokemonCopyStatus(dst, src, ids[i]);
    }
}

u16 fightOutPokemonGetAllAbiCnt(FightOutPokemon* fop) {
    u16 ids[7] = {0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC};
    u8 i;
    u16 sum = 0;
    for (i = 0; i < 7; i++) {
        sum += pokemonGetStatus(fop, 0, ids[i], 0);
    }
    return sum;
}

u16 fightPokemonDoItemSoubi(FightPokemon* fp, u16 item, u8 mode) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return 0;
    }
    return pokemonDoItemSoubi(p, item, mode);
}

u16 fightOutPokemonDoItemSoubi(FightOutPokemon* fop, u16 item, u8 mode, u8 update) {
    FightPokemon* fp = fightOutPokemon_GetFightPokemonPtr(fop);
    if (fp == 0) {
        return 0;
    }
    u16 result = fightPokemonDoItemSoubi(fp, item, mode);
    if (update == 1) {
        if (mode == 0 && result != 0) {
            fightOutPokemon_SetUsedItemDataId(fop, result);
        }
        if (mode == 1 && item != 0) {
            fightOutPokemon_SetUsedItemDataId(fop, 0);
        }
    }
    return result;
}

s32 fightPokemonGetTasteLike(FightPokemon* fp, s32 taste) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p == 0) {
        return -1;
    }
    return pokemonGetTasteLike(p, taste);
}

s32 fightOutPokemonGetTasteLike(FightOutPokemon* fop, s32 taste) {
    FightPokemon* fp = fightOutPokemon_GetFightPokemonPtr(fop);
    if (fp == 0) {
        return -1;
    }
    return fightPokemonGetTasteLike(fp, taste);
}

void fightOutPokemonSetOumuWazaDataId(FightOutPokemon* fop, FightOutPokemon* target, u16 waza) {
    FightOutPokemonEnemy* enemy;
    fightFloor_GetFightType(0);
    if (fop == 0) {
        return;
    }
    if (fightOutPokemonIsAlly(fop, target) && target != fop) {
        fightOutPokemon_SetOumuWazaAllyDataId(fop, waza);
        fightOutPokemon_SetOumuWazaDataId(fop, waza);
    } else {
        fightOutPokemon_SetOumuWazaDataId(fop, waza);
    }
    FightOutPokemonEnemy* enemies = fightOutPokemon_GetFightOutPokemonEnemyPtr(fop, 0);
    if (target != 0) {
        enemy = fightOutPokemonEnemySearchAry(enemies, 4, target);
        if (enemy != 0) {
            fightOutPokemonEnemyBiosSetOumuWazaDataId(enemy, waza);
        }
    } else {
        for (u32 i = 0; i < 4; i++) {
            enemy = (FightOutPokemonEnemy*)((u8*)enemies + i * 0xC);
            if (fightOutPokemonEnemyCheckValid(enemy)) {
                fightOutPokemonEnemyBiosSetOumuWazaDataId(enemy, waza);
            }
        }
    }
}

u8 fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(FightOutPokemon* fop, u16* ary) {
    FightOutPokemonEnemy* enemy;
    u8 i;
    u8 count;

    if (fop == 0) {
        return 0;
    }
    FightOutPokemonEnemy* enemies = fightOutPokemon_GetFightOutPokemonEnemyPtr(fop, 0);
    for (i = 0; i < 4; i++) {
        if (ary != 0) {
            ary[i] = 0;
        }
    }
    count = 0;
    for (i = 0; i < 4; i++) {
        enemy = (FightOutPokemonEnemy*)((u8*)enemies + i * 0xC);
        if (fightOutPokemonEnemyCheckValid(enemy)) {
            u16 waza = fightOutPokemonEnemyBiosGetOumuWazaDataId(enemy);
            if (waza != 0 && waza != 0x176) {
                if (ary != 0) {
                    ary[count] = waza;
                }
                count++;
            }
        }
    }
    return count;
}

u16 fightOutPokemonIsJoutaiKie(FightOutPokemon* fop) {
    u16 ids[3] = {0x1F, 0x20, 0x21};
    u16 id;
    u8 i;
    if (fop == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        id = ids[i];
        if (fightOutPokemonIsJoutaiDataId(fop, id) == 1) {
            return id;
        }
    }
    return 0;
}

void fightOutPokemonInitJoutaiKie(FightOutPokemon* fop) {
    u16 ids[3] = {0x1F, 0x20, 0x21};
    u16 id;
    u8 i;
    if (fop != 0) {
        for (i = 0; i < 3; i++) {
            id = ids[i];
            if (fightOutPokemonIsJoutaiDataId(fop, id) == 1) {
                fightOutPokemonInitJoutaiDataId(fop, id);
            }
        }
    }
}

void fightOutPokemonInitJoutaiKeep(FightOutPokemon* fop) {
    u16 ids[9] = {0x22, 0x0D, 0x0B, 0x0C, 0x1F, 0x20, 0x21, 0x2E, 0x2F};
    u16 id;
    u8 i;
    if (fop != 0) {
        for (i = 0; i < 9; i++) {
            id = ids[i];
            if (fightOutPokemonIsJoutaiDataId(fop, id) == 1) {
                fightOutPokemonInitJoutaiDataId(fop, id);
            }
        }
    }
}

u8 fightOutPokemonCheckNoAttackFlag(FightOutPokemon* fop) {
    u16 ids[9] = {0x106, 0x108, 0x10B, 0x10C, 0x10D, 0x10E, 0x10F, 0x110, 0x107};
    if (fop == 0) {
        return 0;
    }
    for (u8 i = 0; i < 9; i++) {
        if (pokemonGetStatus(fop, 0, ids[i], 0) == 1) {
            return 1;
        }
    }
    return 0;
}

u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon* fop, u16 banme, u8 initKeep, u16* outItemWaza) {
    u16 item;
    u8 pp;
    Pokemon* p;
    u16 waza;
    u16 iryoku;
    u8 result = 0;
    u16 lastSelect;

    if (fop == 0) {
        return 6;
    }
    p = fightOutPokemonGetPokemonPtr(fop);
    waza = pokemon_GetPokemonWazaDataId(p, banme);
    iryoku = wazaDB_GetIryoku(waza);
    pp = pokemon_GetPokemonWazaPp(p, banme);
    item = fightOutPokemonGetSoubiItemSoubiDataId(fop);
    lastSelect = fightOutPokemon_GetLastSelectWazaDataId(fop);

    if (fightOutPokemonIsJoutaiDataId(fop, 0x29) == 1) {
        u16 kanashibari = fightOutPokemonGetIdBuffJoutaiDataId(fop, 0x29);
        if (kanashibari != 0 && kanashibari == waza && kanashibari != 0x176) {
            result = 1;
        }
    }
    if (fightOutPokemonIsJoutaiDataId(fop, 0x1B) == 1 && waza == lastSelect && waza != 0xA5) {
        if (initKeep == 1) {
            fightOutPokemonInitJoutaiKeep(fop);
        }
        result = 2;
    }
    if (fightOutPokemonIsJoutaiDataId(fop, 0x30) == 1 && iryoku == 0) {
        result = 3;
    }
    if (fightFloorCheckHuuinWazaFightOutPokemon(0, fop, waza) == 1) {
        result = 4;
    }
    if (item == 0x1D) {
        u16 kodawari;
        if (fightOutPokemonIsJoutaiDataId(fop, 0x36) == 1) {
            kodawari = fightOutPokemonGetIdBuffJoutaiDataId(fop, 0x36);
        } else {
            kodawari = 0;
        }
        if (kodawari != 0 && kodawari != 0x176 && kodawari != 0xFFFF && kodawari != waza) {
            result = 5;
        }
        if (outItemWaza != 0) {
            *outItemWaza = kodawari;
        }
    }
    if (!pokemonWazaCheckValid(p, banme) || pp == 0) {
        result = 6;
    }
    return result;
}

u8 fightOutPokemonGetOutOkWazaBanmeAry(FightOutPokemon* fop, s16* ary) {
    u8 i;
    u8 count;

    if (fop == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (ary != 0) {
            ary[i] = -1;
        }
    }
    count = 0;
    for (i = 0; i < 4; i++) {
        if (pokemonWazaCheckValid(fightOutPokemonGetPokemonPtr(fop), i)) {
            u16 waza = pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(fop), i);
            if (waza != 0 && waza != 0x176 && waza != 0x163 &&
                !fightOutPokemonCheckCanOutOkWazaBanme(fop, i, 0, 0)) {
                if (ary != 0) {
                    ary[count] = i;
                }
                count++;
            }
        }
    }
    return count;
}

u8 fightOutPokemonCheckWaruagaki(FightOutPokemon* fop) {
    if (!fightOutPokemonGetOutOkWazaBanmeAry(fop, 0)) {
        return 1;
    }
    if (fightOutPokemonIsJoutaiDataId(fop, 0x2A) == 1) {
        s32 banme = fightOutPokemonGetBuffJoutaiDataId(fop, 0x2A);
        if (fightOutPokemonCheckCanOutOkWazaBanme(fop, banme, 0, 0)) {
            return 1;
        }
    }
    return 0;
}

u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon* fop, u8 create) {
    u8 type = fightFloor_GetFightType(0);
    if (fop == 0) {
        return 0;
    }
    if (!fightOutPokemonCheckFightOut(fop)) {
        return 0;
    }
    Pokemon* p = fightOutPokemonGetPokemonPtr(fop);
    if (fightOutPokemonCheckWaruagaki(fop) == 1) {
        if (create) {
            fightOutPokemonCreateFightActionAttackWaza(
                fop, 0, 0x13, 0, fight_action_data_waza, 0xA5,
                fightTargetGetTragetPtrToRelativeHostSideFightTargetId(
                    fightSeqSelectDefensePokemonPtr(fop, 0xA5, type, 0, 1, 1, -1), type),
                -1, 1);
        }
        return 1;
    }
    if (fightOutPokemonIsJoutaiDataId(fop, 0x2A) == 1) {
        u16 keepId = fightOutPokemonGetIdBuffJoutaiDataId(fop, 0x2A);
        s32 banme = fightOutPokemonGetBuffJoutaiDataId(fop, 0x2A);
        u16 waza = pokemon_GetPokemonWazaDataId(p, banme);
        wazaDB_GetPri(waza);
        if (create) {
            if (keepId != waza) {
                fightOutPokemonInitJoutaiDataId(fop, 0x2A);
            }
            fightOutPokemonCreateFightActionAttackWaza(
                fop, 0, 0x13, 0, fight_action_data_waza, waza,
                fightTargetGetTragetPtrToRelativeHostSideFightTargetId(
                    fightSeqSelectDefensePokemonPtr(fop, waza, type, 0, 1, 1, -1), type),
                banme, 1);
        }
        return 2;
    }
    return 0;
}

s32 fightOutPokemonGetJoutaiMigawariHp(FightOutPokemon* fop) {
    if (fop == 0) {
        return 0;
    }
    if (fightOutPokemonIsJoutaiDataId(fop, 0x14) == 1) {
        return fightOutPokemonGetBuffJoutaiDataId(fop, 0x14);
    }
    return 0;
}

void fightOutPokemonSetJoutaiMigawariHp(FightOutPokemon* fop, s32 hp) {
    if (fop != 0 && fightOutPokemonIsJoutaiDataId(fop, 0x14) == 1) {
        fightOutPokemonSetBuffJoutaiDataId(fop, 0x14, hp);
    }
}

u8 fightOutPokemonIsUseHensinBuff(FightOutPokemon* fop) {
    if (fop == 0) {
        return 0;
    }
    FightPokemon* fp = fightOutPokemon_GetFightPokemonPtr(fop);
    return fp == fightOutPokemon_GetFightPokemonHensinBuffPtr(fop);
}

u8 fightOutPokemonUseHensinBuff(FightOutPokemon* fop) {
    if (fop == 0) {
        return 0;
    }
    FightPokemon* moto = fightOutPokemon_GetMotoFightPokemonPtr(fop);
    FightPokemon* buff = fightOutPokemon_GetFightPokemonHensinBuffPtr(fop);
    if (moto == 0) {
        return 0;
    }
    if (buff == 0) {
        return 0;
    }
    *buff = *moto;
    fightOutPokemon_SetFightPokemonPtr(fop, buff);
    return 1;
}

static inline u16 getId(u16* ids, u8 i) {
    return ids[i];
}

void fightOutPokemonCopyHensinStatus(FightOutPokemon* src, FightOutPokemon* dst) {
    u16 statusIds[14] = {
        0x6E, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0xB6, 0xB7,
    };
    u16 abiIds[7] = {0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC};
    u16 waza;
    u8 i;
    if (src != 0 && dst != 0) {
        Pokemon* srcP = fightOutPokemonGetPokemonPtr(src);
        Pokemon* dstP = fightOutPokemonGetPokemonPtr(dst);
        for (i = 0; i < 14; i++) {
            u16 id = getId(statusIds, i);
            s32 value = pokemonGetStatus(srcP, 0, id, 0);
            pokemonSetStatus(dstP, 0, id, 0, value);
        }
        for (i = 0; i < 4; i++) {
            waza = (u16)pokemon_GetPokemonWazaDataId(srcP, i);
            pokemon_SetPokemonWazaDataId(dstP, i, waza);
            if (wazaDB_GetPp(waza) < 5) {
                pokemon_SetPokemonWazaPp(dstP, i, wazaDB_GetPp(waza));
            } else {
                pokemon_SetPokemonWazaPp(dstP, i, 5);
            }
        }
        for (i = 0; i < 7; i++) {
            u16 id = getId(abiIds, i);
            pokemonSetStatus(dst, 0, id, 0, pokemonGetStatus(src, 0, id, 0));
        }
        fightOutPokemonSetTokuseiDataId(dst, fightOutPokemonGetTokuseiDataId(src));
        for (i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(dst, i, fightOutPokemonGetZokuseiDataId(src, i));
        }
    }
}

void fightOutPokemonSetHensinPokemonStatusId(FightOutPokemon* fop, u16 id, s32 sub, u8 toBuff) {
    FightPokemon* src;
    FightPokemon* dst;

    if (toBuff == 1) {
        src = fightOutPokemon_GetMotoFightPokemonPtr(fop);
        dst = fightOutPokemon_GetFightPokemonHensinBuffPtr(fop);
    } else {
        src = fightOutPokemon_GetFightPokemonHensinBuffPtr(fop);
        dst = fightOutPokemon_GetMotoFightPokemonPtr(fop);
    }
    if (src != 0 && dst != 0) {
        Pokemon* srcP = fightPokemonGetPokemonPtr(src);
        Pokemon* dstP = fightPokemonGetPokemonPtr(dst);
        if (id == 0x7C) {
            dstP->copyCondition(srcP);
        } else if (id == 0xC8) {
            dstP->setReversMode(srcP->isReversMode());
        } else {
            s32 value = pokemonGetStatus(srcP, 0, id, sub);
            pokemonSetStatus(dstP, 0, id, sub, value);
        }
    }
}

void fightOutPokemonSetHensinFightPokemonStatusId(FightOutPokemon* fop, u16 id, u8 toBuff) {
    FightPokemon* src;
    FightPokemon* dst;

    if (toBuff == 1) {
        src = fightOutPokemon_GetMotoFightPokemonPtr(fop);
        dst = fightOutPokemon_GetFightPokemonHensinBuffPtr(fop);
    } else {
        src = fightOutPokemon_GetFightPokemonHensinBuffPtr(fop);
        dst = fightOutPokemon_GetMotoFightPokemonPtr(fop);
    }
    if (src != 0 && dst != 0) {
        s32 value = pokemonGetStatus(src, 0, id, 0);
        pokemonSetStatus(dst, 0, id, 0, value);
    }
}

void fightOutPokemonSetHensinStatusAfterLevelUp(FightOutPokemon* fop) {
    u16 ids[18] = {
        0x7A, 0x83, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D,
        0x8E, 0x8F, 0x90, 0x91, 0x92, 0x99, 0xC7, 0x79, 0xC6,
    };
    for (u8 i = 0; i < 18; i++) {
        fightOutPokemonSetHensinPokemonStatusId(fop, ids[i], 0, 1);
    }
}

void fightOutPokemonAddFightOutPokemonEnemyDamage(FightOutPokemon* fop, FightOutPokemon* target, s32 damage) {
    if (fop != 0 && target != 0 && fop != target) {
        FightOutPokemonEnemy* enemy =
            fightOutPokemonEnemySearchAry(fightOutPokemon_GetFightOutPokemonEnemyPtr(target, 0), 4, fop);
        if (enemy != 0) {
            s32 total = fightOutPokemonEnemyBiosGetDamage(enemy);
            total += damage;
            fightOutPokemonEnemyBiosSetDamage(enemy, total);
        }
    }
}

void fightPokemonToMenuLvupStatus(FightPokemon* fp, MenuLvupStatus* lvup) {
    if (fp != 0 && lvup != 0) {
        Pokemon* p = fightPokemonGetPokemonPtr(fp);
        lvup->maxHp = pokemon_GetMaxHp(p);
        lvup->phyAtk = pokemon_GetPhyAtk(p);
        lvup->phyDef = pokemon_GetPhyDef(p);
        lvup->speAtk = pokemon_GetSpeAtk(p);
        lvup->speDef = pokemon_GetSpeDef(p);
        lvup->nimbleness = pokemon_GetNimbleness(p);
        lvup->unk0 = 0;
    }
}

void fightPokemonToMenuWazaStatus(FightPokemon* fp, MenuWazaStatus* menu) {
    Pokemon* p = fightPokemonGetPokemonPtr(fp);
    if (p != 0) {
        pokemonToMenuWazaStatus(p, menu);
    }
}

void fightOutPokemonToMenuWazaStatus(FightOutPokemon* fop, MenuWazaStatus* menu) {
    fightPokemonToMenuWazaStatus(fightOutPokemon_GetFightPokemonPtr(fop), menu);
    menu->fightOutPokemon = fop;
}

void fightOutPokemonToMenuPokemonStatus(FightOutPokemon* fop, MenuPokemonStatus* menu) {
    Pokemon* moto;
    FightPokemon* fp;
    s8 rare;
    Pokemon pokemon;
    u32 rnd;
    u32 catchRnd;

    rare = -1;
    fp = fightOutPokemon_GetFightPokemonPtr(fop);

    pokemonBiosCopy(&pokemon, fightPokemonGetPokemonPtr(fp));
    if (fightOutPokemonIsJoutaiDataId(fop, 0x10) == 1) {
        fightOutPokemonGetRndStatus(fop, &rnd, &catchRnd);
        pokemon_SetRnd(&pokemon, rnd);
        pokemon_SetCatchTrainerRnd(&pokemon, catchRnd);
        rare = pokemonCheckRare(fightPokemonGetPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(fop)));
    }
    pokemonToMenuPokemonStatus(&pokemon, fp, menu, rare);
    moto = fightPokemonGetPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(fop));
    if (moto != 0) {
        pokemonToMenuPokemonStatusSubBar(moto, menu);
        menu->sex = menuSubGetPokemonSexForFightDisp(moto);
    }
    menu->unk16 = 1;
    if (fightOutPokemonIsGcHeroFightOutPokemon(fop) == 1) {
        menu->unk16 = 0;
    }
    if (!fightFloor_GetFightKindPokemonStatusMenuSubbarFlag(0)) {
        menu->unk16 = 1;
    }
    menu->unk2D = 0;
}

void fightOutPokemonGetRndStatus(FightOutPokemon* fop, u32* rnd, u32* catchRnd) {
    Pokemon* p;
    u32 r;
    u32 c;

    if (fightOutPokemonIsJoutaiDataId(fop, 0x10) == 1) {
        r = fightOutPokemonGetBuffJoutaiDataId(fop, 0x10);
        u8 kaisuu = fightOutPokemonGetKaisuuJoutaiDataId(fop, 0x10);
        u8 now = fightOutPokemonGetNowKaisuuJoutaiDataId(fop, 0x10);
        c = kaisuu | (now << 8) | (fightOutPokemonGetIdBuffJoutaiDataId(fop, 0x10) << 16);
    } else {
        p = fightOutPokemonGetPokemonPtr(fop);
        c = pokemon_GetCatchTrainerRnd(p);
        r = pokemon_GetRnd(p);
    }
    if (rnd != 0) {
        *rnd = r;
    }
    if (catchRnd != 0) {
        *catchRnd = c;
    }
}

u8 fightPokemonGetNonTrainerPokemonIsActiveFlag(void) {
    return nonTrainerPokemonisActive;
}

void fightPokemonSetNonTrainerPokemonIsActiveFlag(u8 flag) {
    nonTrainerPokemonisActive = flag;
}

}
