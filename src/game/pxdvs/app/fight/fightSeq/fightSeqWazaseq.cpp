// WIP: being decompiled (Colosseum shared-function batch).
#include <dolphin/types.h>

#pragma optimize_for_size on

struct FightOutPokemon;
static u8 _fightSeqHukitobashiCheck(FightOutPokemon*, FightOutPokemon*, u32);
static s32 _fightOutPokemonGetFightOutPokemonAllyOumuWazaDataIdAry(FightOutPokemon*);
static s32 _fightSeqWsHorobinoutaSub(void*, u16, void*);

static s32 _fightSeqWsKuroikiriSub(void*, u16, void*);
static s32 _fightSeqWsIkakuSub(void*, u16, void*);
static s32 _WsHuuinSub(void*, u16, void*);
static void _fightSeqDamageHanekaesi(u16, u16, u8, u32);
static u8 fightSeqGetNumDotto(u16, u16, u8);
static s32 _fightSeqSawaguCheckSub(void*, u16, void*);
static u8 _fightSeq_IsTrickCheck(FightOutPokemon*, FightOutPokemon*);
struct WsHuuinCtx {
    FightOutPokemon* p;
    s32 flag;
};

extern "C" {
u16 fightSeqGetKetaguriIryoku(u16);

extern u32 ServerStatusFlag;

void* fightSeq_GetWazaSeq(void);
void fightSeq_NextWazaSeq(s32 size);
void fightSeq_JumpWazaSeq(void* target);
FightOutPokemon* fightTargetGetPtrAsNowFightType(u32, u32);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u32);
u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon*, u32);
void fightOutPokemonWriteJoutaiDataId(FightOutPokemon*, u32, u32);
void fightOutPokemonSetKaisuuJoutaiDataId(FightOutPokemon*, u32, u32);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon*, u32);
u8 fightOutPokemonIsJoutaiNormal(FightOutPokemon*);
u32 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
void fightOutPokemonSetTokuseiDataId(FightOutPokemon*, u32);
u32 fightOutPokemon_GetUseWazaDataId(FightOutPokemon*);
void fightOutPokemonCopyAllAbiCnt(FightOutPokemon*, FightOutPokemon*);
u32 fightFloor_GetTikeiDataId(u32);
u8 tikeiDataBiosGetFightKoukaId(u32);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
void fightOutPokemonInitAbiCntAll(FightOutPokemon*);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon*);
u8 fightSeqRegulationCheck(u32, FightOutPokemon*, FightOutPokemon*);
u8 fightFloorCheckWriteJoutaiDataId(u32, u32);
void fightFloorWriteJoutaiDataId(u32, u32, u32);
void fightFloor_SetAttackPokemonFightWazaJoutaiDataId(u32, u32);
u8 fightFloorLoopValidFightOutPokemon(u8, s32 (*)(void*, u16, void*), void*, u8);
extern u16 KetaguriTbl[];
extern u16 YubihuriNGTbl[];


extern u8 ServerWork[8];

#pragma pack(push, 1)
struct WsJumpCmd {
    u8 opcode;
    void* jump;
};
#pragma pack(pop)
extern u8* UserWork;
void* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void* floor, FightOutPokemon* pokemon);
u8 fightFloor_GetFightTypeTrainerNum(void* floor);
void fightFloor_SetItemPokemonPtr(void* floor, FightOutPokemon* pokemon);
bool fightOutPokemonCheckValid(FightOutPokemon* fop);
void fightOutPokemonCopyHensinStatus(FightOutPokemon* src, FightOutPokemon* dst);
void* fightOutPokemonGetNamePtr(FightOutPokemon* fop);
u16 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon* fop);
u16 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon* fop, u16 id);
u16 fightOutPokemonIsJoutaiKie(FightOutPokemon* fop);
u8 fightOutPokemonIsUseHensinBuff(FightOutPokemon* fop);
void fightOutPokemonSetBuffJoutaiDataId(FightOutPokemon* fop, u16 id, s32 value);
void fightOutPokemonSetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id, u32 value);
void fightOutPokemonSetNowKaisuuJoutaiDataId(FightOutPokemon* fop, u16 id, s8 value);
u8 fightOutPokemonUseHensinBuff(FightOutPokemon* fop);
u8 fightOutPokemon_GetItemKoraetaFlag(FightOutPokemon* fop);
void* fightOutPokemon_GetWazaMenuCurPtr(FightOutPokemon* fop);
void fightOutPokemon_SetItemKoraetaFlag(FightOutPokemon* fop, u8 value);
void fightOutPokemon_SetStockItemDataId(FightOutPokemon* fop, u16 value);
bool fightPokemonCheckValid(void* fp);
void* fightPokemonGetPokemonPtr(void* fp);
u8 fightSeqIsDoItemGetWaza(FightOutPokemon* p);
void* fightSeq_GetWazaSeqAdr(s32 off);
void* fightSideGetValidFightTrainerPtr(void* side, u16 idx);
void fightSideInitJoutaiDataId(void* side, u16 id);
void* fightTrainerCheckTemotiPokemonFightEntry(void* trainer, void* pokemon);
void fightWaza_SetMotoWazaDataId(void* waza, u16 value);
s32 figthOutPokemonGetSoubiItemBuff(FightOutPokemon* fop);
void* itemDB_GetName(u16);
bool itemDataCheckValid(u16 id);
bool pokemonCheckFightOut(void* pokemon);
u16 pokemonGetTokuseiDataId(void* pokemon);
u8 pokemonIsDarkPokemon(void* pokemon);
bool pokemonIsJoutaiNormal(void* pokemon);
u32 pokemon_GetCatchTrainerRnd(void* poke);
u8 pokemon_GetLevel(void* poke);
char* pokemon_GetNicknamePtr(void* poke);
u16 pokemon_GetPokemonDataId(void* poke);
u32 pokemon_GetRnd(void* poke);
u8 wazaDB_GetAvg(u16 id);
void* wazaGetStatus(void*, u16, u16, u32);
extern u8 WAZA_Ganzyou[];
extern u8 WAZA_Nentyaku[];
u8 fightActionCheckValid(void*);
u16 fightActionGetKindDataId(void*);
FightOutPokemon* fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(void* floor, u16 tokuseiId, u8 useAry, u8 mode, FightOutPokemon* pokemon);
FightOutPokemon* fightFloor_GetFightOutPokemonFromDefaultSortData(u8 index);
u32 fightMenuGetFightOutPokemonPtrToStatusMenuId(FightOutPokemon* p, u16 id, bool flag);
s32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonInitJoutaiKeep(FightOutPokemon* fop);
void* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon* fop);
u16 fightOutPokemon_GetLastSelectWazaDataId(FightOutPokemon* fop);
u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon* fop);
void fightOutPokemon_SetFightActionFlag(FightOutPokemon* fop, u8 value);
u32 fightSeqMonomaneNGCheck(u16 id);
u16 fightWaza_GetTargetDataId(void* waza);
u8 fightWaza_GetWazaBanme(void* waza);
void menuFightStatusSetHP(s32 id, s16 hp);
void pokemonWazaCreate(void* pokemon, u16 wazaNum, u16 waza);
u8 pokemon_GetPokemonWazaPp(void* poke, u32 wazaNum);
void pokemon_SetPokemonWazaPp(void* poke, u32 wazaNum, u8 data);
void* wazaDB_GetName(u16 id);
u8 wazaDB_GetPp(u16 id);
extern u8 WAZA_Shimerike[];
extern u8 fight_seq_banme_buff;
extern u8 fight_seq_banme_max;
void fightSeqPpdecMonomane(FightOutPokemon*, u8, u32);
s16 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon* fop, u16 id);
u16 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon* fop, u16 id);
u16 fightOutPokemonGetTeikouZokuseiDataIdAry(FightOutPokemon* fop, u16 waza, s32* ary);
void* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon* fop);
u16 fightOutPokemon_GetHitWazaDataId(FightOutPokemon* fop);
u16 fightOutPokemon_GetHitWazaZokuseiDataId(FightOutPokemon* fop);
u16 fightOutPokemon_GetLastReceiveWazaTargetDataId(FightOutPokemon* fop);
u16 fightOutPokemon_GetLastUseWazaDataId(FightOutPokemon* fop);
void* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon* fop);
u16 fightOutPokemon_GetSketchWazaDataId(FightOutPokemon* fop);
u8 fightOutPokemon_GetSuccessCnt(FightOutPokemon* fop);
void fightOutPokemon_SetSuccessCnt(FightOutPokemon* fop, u8 value);
u8 fightSeqIsSketchNgWazaDataId(u32 id);
s32 fightSeqWazaDamageCalc(FightOutPokemon*, FightOutPokemon*, FightOutPokemon*, u16, u16, u16);
void* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u16 slotType, u16 type);
bool fightWazaIsHit(void* waza);
u16 fightWaza_GetZokusei(void* waza);
u8 joutaiDataBiosGetMaxCount(u16 id);
extern u8 WAZA_MakibishiEscape[];
extern u8 WAZA_NormalNohitWait[];
extern u8 WAZA_ShimeEscape[];
extern u8 WAZA_YadorigiEscape[];
extern u16 KakuritsuTable[];
extern u8 WAZA_ShimeEscape[];
u16 dbgMenuFightGetYubiwohuruWazaDataId(void);
void fightFloor_SetIrekaePokemonPtr(void* floor, FightOutPokemon* value);
void fightOutPokemon_SetIrekaeTargetEntryId(FightOutPokemon* fop, s16 value);
void fightOutPokemon_SetIrekaetaFlag(FightOutPokemon* fop, u8 value);
s16 fightPokemon_GetEntryId(void* fp);
void* fightPokemon_GetMotoPokemonPtr(void* fp);
u32 fightSeqCheckYubiwohuruWazaDataId(u16 move_id);
s32 fightSeqIsEncoreNgWazaDataId(u16 move);
u16 fightTrainerGetIrekaeFightPokemonAry(void* trainer, void** ary);
void fightWazaSetUseWazaStatus(void* waza, u16 id);
extern u8 WAZA_HukitobashiFightEnd[];
extern void* WazaEffectTbl[];
extern u8 WAZA_HukitobashiFightEnd[];
u8 fightOutPokemonGetSex(FightOutPokemon* fop);
void fightWazaInitJoutaiDataId(void* waza, u16 id);
u8 wazaDB_GetZokuseiDataId(u32 id);
extern u8 WAZA_Donkan[];
extern u8 WAZA_HitCalcOnly[];
extern u8 WAZA_Kaifuku[];
extern u8 WAZA_Mantan[];
u16 fightFloorGetValidFightOutPokemonCount(void* floor, u8 mode, FightOutPokemon* pokemon, u8 fightOut);
u16 fightFloor_GetFightSideFightOutPokemonSideMax(void* floor);
s32 fightSeqGetTemotiPokemonNekonoteWazaDataAry(void*, u16*, u16, FightOutPokemon*);
s32 fightSideGetCountAsJoutaiDataId(void* side, u16 id);
u16 tikeiDataBiosGetWazaId(u8 id);
extern u8 WAZA_ShizennochikaraHitMsg[];
extern u8 WAZA_ShizennochikaraHitMsg[];
void fightOutPokemonFreeWazaEffect(FightOutPokemon* fop, u16 waza, s32 kind);
u8 fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(FightOutPokemon* fop, u16* ary);
void fightOutPokemonLoadWazaEffect(FightOutPokemon* fop, u16 waza, u8 kind, u8 flag);
void fightOutPokemonWazaEffect(FightOutPokemon* fop, s32 a, s32 b, u8 close, s32 menuId);
u16 fightOutPokemon_GetOumuWazaAllyDataId(FightOutPokemon* fop);
u16 fightOutPokemon_GetOumuWazaDataId(FightOutPokemon* fop);
void fightOutPokemon_SetKaigaraDamageValue(FightOutPokemon* fop, u32 value);
s32 fightSeqGetTextureZokuseiAry(FightOutPokemon*, s32*);
void* fightTargetDataBiosGetBuff(void* data);
void* fightTargetDataBiosGetPtr(u16 index);
extern u8 WAZA_Hukitobashi[];
extern u32 WazaDamage;
extern u8 WAZA_Hukitobashi[];
void fightSeqPressurePpdecCheckHorobinouta(FightOutPokemon*);
u32 fightFloor_GetEncountDataId(s32);
void* fightEncountDataBiosGetPtr(u32);
u8 fightEncountDataBiosGetFightKind(void*);
void fightFloorSetFightResultId(s32, u32);
void fightSeqFightOutPokemonTokuseiCheckTenkiya(void);
void* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
void pokemonInitJoutai(void*);
void fightOutPokemonResetSeqStatus(FightOutPokemon*, u32);
void fightSeqCheckSetHensinBuffToMotoPokemon(FightOutPokemon*, u32);
u8 fightOutPokemonIsAlly(FightOutPokemon*, FightOutPokemon*);
void fightFloor_SetDefensePokemonPtr(s32, FightOutPokemon*);
void* pokemonTokuseiDataBiosGetPtr(u32);
void* pokemonTokuseiDataBiosGetName(void*);
void* GSmsgGetGSchar(void*);
void fightMsgctrlSetValue(u32, u32);
extern u8 WAZA_IkakuLoop[];
void fightSeq_CallWazaSeq(void*);
void fightFloor_SetTuikakoukaPokemonPtr(s32, FightOutPokemon*);
void fightFloor_SetAppointPokemonPtr(s32, FightOutPokemon*);
void fightFloor_SetAttackPokemonPtr(s32, FightOutPokemon*);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(s32, FightOutPokemon*);
u32 tikeiDataBiosGetZokuseiDataId(u32);
void fightOutPokemonSetZokuseiDataId(FightOutPokemon*, u8, u8);
void* zokuseiBiosGetName(u32);
u32 fightOutPokemonGetSoubiItemDataId(FightOutPokemon*);
u32 fightOutPokemon_GetUsedItemDataId(FightOutPokemon*);
void fightFloor_SetAppointItemDataId(s32, u32);
void fightOutPokemonDoItemSoubi(FightOutPokemon*, u32, u32, u32);
u32 fightFloorGetNowTenkouDataId(s32, u32);
void* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
void fightWaza_SetZokusei(void*, u32);
void fightWaza_SetDamageValue(void*, u32);
u32 wazaDB_GetSeqId(u32);
void fightOutPokemon_SetNoPressureFlag(FightOutPokemon*, u32);
u8 fightFloorIsLastActionFightOutPokemon(s32);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon*, u32);
u32 figthOutPokemonGetPokemonDataId(FightOutPokemon*);
u16 pokemonDB_GetWeight(u32);
void fightWaza_SetIryoku(void*, u16);
u32 fightWaza_GetIryoku(void*);
void fightSeqPressurePpdecCheckHuuin(FightOutPokemon*);
u8 pokemonWazaCheckValid(void*, s32);
u32 pokemon_GetPokemonWazaDataId(void*, u16);
s8 pokemonSearchWazaDataId(void*, u32);
u16 pokemon_GetHp(void*);
u16 pokemon_GetMaxHp(void*);
void fightWaza_SetDamage(void*, s32);
u32 fightFloor_GetFightType(s32);
s16 fightOutPokemon_GetDamageAtkValue(FightOutPokemon*);
u16 fightOutPokemon_GetDamageAtkTargetId(FightOutPokemon*);
s16 fightOutPokemon_GetDamageSpeValue(FightOutPokemon*);
u16 fightOutPokemon_GetDamageSpeTargetId(FightOutPokemon*);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u8);
u8 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon*);
s32 fightSeqCondChgActParaIdToValue(u8);
s32 fightSeqCondChgActTypeToPokemonStatusId(u8);
extern u32 AbiCntMsgTbl[];
extern u8 WAZA_Shiroikiri[];
extern u8 WAZA_Umakukimaran[];
extern u8 WAZA_ClearBody[];
extern u8 WAZA_Kairikibasami[];
u8 fightSeqGuardCheck(u32, u32);
u8 fightSideIsJoutaiDataId(void*, u32);
u8 fightOutPokemon_GetDoClearbodyFlag(FightOutPokemon*);
void fightOutPokemon_SetDoClearbodyFlag(FightOutPokemon*, u32);
u8 fightFloorIsNowEncountOpeningVirtualBattle(s32);
s16 pokemonGetStatus(FightOutPokemon*, u32, s32, u32);
void pokemonSetStatus(FightOutPokemon*, u32, u16, u32, s8);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon*, u16, u32, u32);
u8 fightSeqRendouWazaCheck(u32);
u8 fightSeqTameWazaCheck(u32);
u32 HSD_Rand(void);
extern u16 PushWazaNo;
void fightWaza_SetWazaBanme(void*, s8);
FightOutPokemon* fightSeqSelectDefensePokemonPtr(FightOutPokemon*, u32, u32, u32, u32, u32, s32);
extern u8 fight_seq_renzoku_count;
extern u8 JitabataTbl[];
void fightSeqMichidureCheckAct(void*);
void fightMenuFightOutPokemonRenewStatusMenu(FightOutPokemon*, u8, u32);
u32 figthOutPokemonGetLevel(FightOutPokemon*);
u32 fightWaza_GetDamage(void*);
s32 fightWaza_GetHitDamage(void*);
u8 fightSeqCondChgAct(u8, u8, s32, void*);
FightOutPokemon* fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(FightOutPokemon*);
void pokemon_SetHp(void*, u32);
u8 wazaCheckDarkWaza(u32);
void pokemonGetMezamerupower(void*, u16*, u16*);
u8 fightFloor_GetFightKindDorobouFlag(s32);
s32 fightFloorGetStatus(s32, s32, u32, u32);
u32 pokemonDB_GetBasisPhyAtk(u32);
u32 pokemonDB_GetBasisPhyDef(u32);
u32 wazaDB_GetIryoku(u32);
s32 fightSeqGetHukuroDatakiDamage(u32, u32, u16, u32);
u8 fightSeqGetJitabataIryoku(u16, u16);
u8 fightSideCheckWriteJoutaiDataId(void*, u32);
void fightSideWriteJoutaiDataId(void*, u32, u32);
u16 pokemon_GetFriend(void*);
u16 fightSeqGetOngaesiIryoku(u16);
u16 fightSeqGetYatuatariIryoku(u16);
bool fightSeqSawaguCheck(FightOutPokemon*);
void* fightOutPokemon_GetKeepFightWazaPtr(FightOutPokemon*);
void fightOutPokemon_SetGamanDamageValue(FightOutPokemon*, u32);
void fightWazaBiosCopy(void*, void*);
u32 fightOutPokemonMaxHpWaruValue(FightOutPokemon*, u32);
u32 fightOutPokemonNowHpWaruValue(FightOutPokemon*, u32);
u8 fightOutPokemonIsHpMantan(FightOutPokemon*);
void fightWaza_SetKaisuu(void*, u8);
u8 fightFloor_GetFightKindGetNekoniKobanFlag(s32);
void* fightFloorGetGcHeroFightTrainerPtr(s32);
u32 fightTrainer_GetKoban(void*);
u8 fightTrainer_GetOkaneBai(void*);
void* fightTrainer_GetHeroPtr(void*);
void heroAddPokedoru(void*, u32);
u32 heroGetStatus(void*, u32, u32);
extern u8 WAZA_Nekonikoban[];
}

extern "C" {
void WS_TELEPORT(void) {
    void* encount = fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0));
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    if (fightEncountDataBiosGetFightKind(encount) != 0xc) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    } else {
        fightFloorSetFightResultId(0, 2);
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_DARKREMOVE(void) {
    FightOutPokemon* atk;
    void* side;
    void* name;
    u8 n;
    n = 0;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(3, (u32)atk);
    if (fightSideIsJoutaiDataId(side, 0x49) == 1) {
        name = GSmsgGetGSchar(wazaGetStatus(0, 0x71, 1, 0));
        fightMsgctrlSetValue(0x28, (u32)name);
        n = 1;
    }
    if (fightSideIsJoutaiDataId(side, 0x48) == 1) {
        name = GSmsgGetGSchar(wazaGetStatus(0, 0x73, 1, 0));
        switch (n) {
        case 0:
            fightMsgctrlSetValue(0x28, (u32)name);
            break;
        case 1:
            fightMsgctrlSetValue(0xD, (u32)name);
            break;
        }
        n++;
    }
    if (fightSideIsJoutaiDataId(side, 0x4B) == 1) {
        name = GSmsgGetGSchar(wazaGetStatus(0, 0xDB, 1, 0));
        switch (n) {
        case 0:
            fightMsgctrlSetValue(0x28, (u32)name);
            break;
        case 1:
            fightMsgctrlSetValue(0xD, (u32)name);
            break;
        case 2:
            fightMsgctrlSetValue(0xE, (u32)name);
            break;
        }
        n++;
    }
    if (n == 0) {
        fightSeq_JumpWazaSeq(WAZA_Umakukimaran);
        return;
    }
    switch (n) {
    case 1:
        ServerWork[5] = 0;
        break;
    case 2:
        ServerWork[5] = 1;
        break;
    case 3:
        ServerWork[5] = 2;
        break;
    }
    fightSideInitJoutaiDataId(side, 0x49);
    fightSideInitJoutaiDataId(side, 0x48);
    fightSideInitJoutaiDataId(side, 0x4B);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KAWARAWARI(void) {
    void* side;
    FightOutPokemon* atk;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(3, (u32)atk);
    if (fightSideIsJoutaiDataId(side, 0x49) == 1 || fightSideIsJoutaiDataId(side, 0x48) == 1) {
        if (fightSideIsJoutaiDataId(side, 0x49) == 1 && fightSideIsJoutaiDataId(side, 0x48) == 1) {
            fightSideInitJoutaiDataId(side, 0x49);
            fightSideInitJoutaiDataId(side, 0x48);
            UserWork[0x16002] = 3;
            UserWork[0x160A1] = 3;
        } else if (fightSideIsJoutaiDataId(side, 0x49) == 1) {
            fightSideInitJoutaiDataId(side, 0x49);
            UserWork[0x16002] = 1;
            UserWork[0x160A1] = 1;
        } else if (fightSideIsJoutaiDataId(side, 0x48) == 1) {
            fightSideInitJoutaiDataId(side, 0x48);
            UserWork[0x16002] = 2;
            UserWork[0x160A1] = 2;
        }
    } else {
        UserWork[0x16002] = 0;
        UserWork[0x160A1] = 0;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_YOKODORI_CLIENT_SET(void) {
    FightOutPokemon* b;
    FightOutPokemon* def;
    FightOutPokemon* attack;
    FightOutPokemon* appoint;
    FightOutPokemon* c;
    bool same;
    fightSeq_GetWazaSeq();
    attack = fightTargetGetPtrAsNowFightType(0x11, 0);
    b = fightTargetGetPtrAsNowFightType(0x12, 0);
    c = fightTargetGetPtrAsNowFightType(0x19, 0);
    appoint = attack;
    fightFloor_SetTuikakoukaPokemonPtr(0, attack);
    same = attack == b;
    if (same) {
        def = c;
        attack = c;
    }
    if (!same) {
        def = c;
    }
    fightFloor_SetAppointPokemonPtr(0, appoint);
    fightFloor_SetAttackPokemonPtr(0, attack);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, def);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HUKITOBASHI_OIUCHI(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_HOGOSYOKU(void) {
    u8* cmd;
    u32 zokusei;
    FightOutPokemon* p;
    u8 i;
    zokusei = fightFloor_GetTikeiDataId(0);
    cmd = (u8*)fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (!fightOutPokemonIsZokuseiDataId(p, zokusei = tikeiDataBiosGetZokuseiDataId(zokusei))) {
        for (i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(p, i, zokusei);
        }
        fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(zokuseiBiosGetName(zokusei)));
        fightSeq_NextWazaSeq(5);
    } else {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    }
}
}

extern "C" {
void WS_RECYCLE(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    u32 soubi = fightOutPokemonGetSoubiItemDataId(p);
    u32 used = fightOutPokemon_GetUsedItemDataId(p);
    if ((u16)used != 0 && (u16)soubi == 0) {
        fightFloor_SetAppointItemDataId(0, used);
        fightOutPokemonDoItemSoubi(p, used, 1, 1);
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x82);
        fightSeq_NextWazaSeq(5);
    } else {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    }
}
}

extern "C" {
void WS_WEATHER_BALL(void) {
    void* waza;
    u8 tenkou;
    fightSeq_GetWazaSeq();
    tenkou = fightFloorGetNowTenkouDataId(0, 1);
    waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    if (tenkou == 2) {
        fightWaza_SetZokusei(waza, 0xb);
        fightWaza_SetDamageValue(waza, 2);
    } else if (tenkou == 3) {
        fightWaza_SetZokusei(waza, 5);
        fightWaza_SetDamageValue(waza, 2);
    } else if (tenkou == 1) {
        fightWaza_SetZokusei(waza, 0xa);
        fightWaza_SetDamageValue(waza, 2);
    } else if (tenkou == 4) {
        fightWaza_SetZokusei(waza, 0xf);
        fightWaza_SetDamageValue(waza, 2);
    } else if (tenkou == 5) {
        fightWaza_SetZokusei(waza, 0);
        fightWaza_SetDamageValue(waza, 2);
    } else {
        fightWaza_SetZokusei(waza, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_ASOBI(void) {
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    u32 seqId;
    u8 done;
    u8* cmd;
    fightOutPokemonGetTokuseiDataId(p);
    seqId = wazaDB_GetSeqId(fightOutPokemon_GetUseWazaDataId(p));
    done = 0;
    cmd = (u8*)fightSeq_GetWazaSeq();
    if ((u16)seqId == 0xc9) {
        if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x38) == 2) {
            fightOutPokemonWriteJoutaiDataId(p, 0x38, 0);
            ServerWork[5] = 0;
            done = 1;
        }
    } else if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x39) == 2) {
        fightOutPokemonWriteJoutaiDataId(p, 0x39, 0);
        ServerWork[5] = 1;
        done = 1;
    }
    if (done) {
        fightSeq_NextWazaSeq(5);
    } else {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    }
}
}

extern "C" {
void WS_TENKIYA_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeqFightOutPokemonTokuseiCheckTenkiya();
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_TENKIYA(void) {
    fightSeq_GetWazaSeq();
    if (!fightOutPokemonIsJoutaiDataId(fightTargetGetPtrAsNowFightType(0x19, 0), 0x14)) {
        UserWork[0x1609b] |= 0x80;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_MONOHIROI(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HIMITUNOTIKARA(void) {
    u8 tikei = fightFloor_GetTikeiDataId(0);
    fightSeq_GetWazaSeq();
    u8* work = ServerWork;
    work[3] = tikeiDataBiosGetFightKoukaId(tikei);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HP_CHECK(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    if (!fightOutPokemonCheckFightOut(fightTargetGetPtrAsNowFightType(cmd[1], 0))) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 2));
    } else {
        fightSeq_NextWazaSeq(6);
    }
}
}

extern "C" {
void WS_SIZENKAIHUKU(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(cmd[1], 0);
    void* pokemon = fightOutPokemonGetPokemonPtr(p);
    if ((u16)fightOutPokemonGetTokuseiDataId(p) == 0x1e) {
        pokemonInitJoutai(pokemon);
        fightOutPokemonResetSeqStatus(p, 0);
        fightOutPokemonInitJoutaiDataId(p, 0x17);
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7c);
    }
    fightSeq_NextWazaSeq(2);
}
}

extern "C" {
void WS_IKAKU(void) {
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x19, 0);
    fightSeq_GetWazaSeq();
    fightFloorLoopValidFightOutPokemon(0, _fightSeqWsIkakuSub, p, 0);
    fightSeq_NextWazaSeq(5);
}
}

static s32 _fightSeqWsIkakuSub(void* pokemon, u16 id, void* user) {
    FightOutPokemon* p = (FightOutPokemon*)pokemon;
    FightOutPokemon* target = (FightOutPokemon*)user;
    u32 tokusei = fightOutPokemonGetTokuseiDataId(target);
    if (!fightOutPokemonCheckFightOut(p)) {
        return 1;
    }
    if (!fightOutPokemonIsAlly(p, target)) {
        fightFloor_SetDefensePokemonPtr(0, p);
        fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(tokusei))));
        fightSeq_CallWazaSeq(WAZA_IkakuLoop);
    }
    return 1;
}

extern "C" {
void WS_YOKODORI(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemon_SetNoPressureFlag(p, 1);
    if (fightFloorIsLastActionFightOutPokemon(0) == 1) {
    jump:
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    } else {
        if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x33) != 2) {
            goto jump;
        }
        fightOutPokemonWriteJoutaiDataId(p, 0x33, 0);
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_MAGICCORT(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, p);
    fightOutPokemon_SetNoPressureFlag(p, 1);
    if (fightFloorIsLastActionFightOutPokemon(0) == 1) {
    jump:
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    } else {
        if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x37) != 2) {
            goto jump;
        }
        fightOutPokemonWriteJoutaiDataId(p, 0x37, 0);
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_NEKONOTE(void) {
    FightOutPokemon* atk;
    u8 type;
    u8* cmd;
    u16 ary[24];
    s32 n;
    u16 r;
    u16 waza;
    type = fightFloor_GetFightType(0);
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    n = fightSeqGetTemotiPokemonNekonoteWazaDataAry(fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, atk), ary, 0x18, atk);
    if (n != 0) {
        r = HSD_Rand();
        waza = ary[r % n];
        ServerStatusFlag &= ~0x400;
        PushWazaNo = waza;
        FightOutPokemon* def = fightSeqSelectDefensePokemonPtr(atk, waza, type, 0, 1, 1, -1);
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, def);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
s32 fightSeqGetTemotiPokemonNekonoteWazaDataAry(void* trainer, u16* ary, u16 n, FightOutPokemon* p) {
    enum TsE { TsE0 };
    void* hero;
    u32 moto;
    s32 count;
    u16 i;
    u16 j;
    u16 k;
    u16 m;
    void* fp;
    void* pk;
    enum TsE waza;
    hero = fightTrainer_GetHeroPtr(trainer);
    moto = (u32)fightOutPokemon_GetMotoFightPokemonPtr(p);
    for (i = 0; i < n; i++) {
        ary[i] = 0;
    }
    count = 0;
    for (j = 0; j < 6; j++) {
        fp = fightTrainerCheckTemotiPokemonFightEntry(trainer, (void*)heroGetStatus(hero, 3, j));
        if (fp != 0 && moto != (u32)fp) {
            pk = fightPokemonGetPokemonPtr(fp);
            for (k = 0; k < 4; k++) {
                if (pokemonWazaCheckValid(pk, k) != 0) {
                    waza = (enum TsE)(pokemon_GetPokemonWazaDataId(pk, k));
                    if (fightSeqRendouWazaCheck(waza) == 0) {
                        for (m = 0; YubihuriNGTbl[m] != 0xFFFF; m++) {
                            if (waza == YubihuriNGTbl[m]) {
                                break;
                            }
                        }
                        if (YubihuriNGTbl[m] == 0xFFFF && waza != 0 && waza != 0x176 && count < n) {
                            ary[count] = waza;
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
}
}

extern "C" {
void WS_KETAGURI(void) {
    void* waza;
    fightSeq_GetWazaSeq();
    waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    u16 power = fightSeqGetKetaguriIryoku(pokemonDB_GetWeight(figthOutPokemonGetPokemonDataId(fightTargetGetPtrAsNowFightType(0x12, 0))));
    fightWaza_SetIryoku(waza, power);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
u16 fightSeqGetKetaguriIryoku(u16 weight) {
    u16 i;
    u16 thr;
    for (i = 0; (thr = KetaguriTbl[i]) != 0xFFFF; i += 2) {
        if (thr > weight) break;
    }
    if (thr != 0xFFFF) return KetaguriTbl[i + 1];
    return 0x78;
}
}

extern "C" {
void WS_ONNEN(void) {
    WsJumpCmd* cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x28) == 2) {
        fightOutPokemonWriteJoutaiDataId(p, 0x28, 0);
        fightSeq_NextWazaSeq(5);
    } else {
        fightSeq_JumpWazaSeq(cmd->jump);
    }
}
}

extern "C" {
void WS_HUUIN(void) {
    WsHuuinCtx ctx;
    u8* cmd;
    FightOutPokemon* p;
    cmd = (u8*)fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x27) != 2) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    fightSeqPressurePpdecCheckHuuin(p);
    ctx.p = p;
    ctx.flag = 0;
    fightFloorLoopValidFightOutPokemon(0, _WsHuuinSub, &ctx, 0);
    if (ctx.flag == 0) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(p, 0x27, 0);
    fightSeq_NextWazaSeq(5);
}
}

static s32 _WsHuuinSub(void* pokemon, u16 id, void* user) {
    u32 other;
    u32 value;
    void* pk;
    s8 slot;
    WsHuuinCtx* ctx = (WsHuuinCtx*)user;

    other = (u32)ctx->p;
    value = (u32)pokemon;
    if (fightOutPokemonCheckFightOut((FightOutPokemon*)value) == 0) {
        return 1;
    }
    if (fightOutPokemonIsAlly((FightOutPokemon*)value, (FightOutPokemon*)other) == 1) {
        return 1;
    }
    pk = fightOutPokemonGetPokemonPtr((FightOutPokemon*)value);
    other = (u32)fightOutPokemonGetPokemonPtr((FightOutPokemon*)other);
    for (slot = 0; slot < 4; slot++) {
        value = slot;
        if (pokemonWazaCheckValid((void*)other, value) == 0) {
            continue;
        }
        if (pokemonSearchWazaDataId(pk, pokemon_GetPokemonWazaDataId((void*)other, (s32)value)) < 0) {
            continue;
        }
        ctx->flag = 1;
        return 0;
    }
    return 1;
}

extern "C" {
void WS_SKILLSWAP(void) {
    u8* cmd;
    FightOutPokemon* atk;
    void* fw;
    FightOutPokemon* def;
    u32 atkTok;
    u32 defTok;
    u32 waza;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    atkTok = fightOutPokemonGetTokuseiDataId(atk);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    defTok = fightOutPokemonGetTokuseiDataId(def);
    if (((u16)atkTok == 0 && (u16)defTok == 0) || (u16)atkTok == 0x19 || (u16)defTok == 0x19 || fightWazaIsHit(fw) == 0 || fightSeqRegulationCheck(waza, atk, def) == 1) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    fightOutPokemonSetTokuseiDataId(atk, defTok);
    fightOutPokemonSetTokuseiDataId(def, atkTok);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_HUNKA(void) {
    u16 hp;
    int iryoku;
    FightOutPokemon* p;
    void* waza;
    fightSeq_GetWazaSeq();
    if (!(ServerStatusFlag & 0x200)) {
        u16 v;
        p = fightTargetGetPtrAsNowFightType(0x11, 0);
        waza = fightOutPokemon_GetFightWazaPtr(p);
        fightOutPokemon_GetUseWazaDataId(p);
        iryoku = fightWaza_GetIryoku(waza);
        hp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(p));
        v = iryoku * hp / pokemon_GetMaxHp(fightOutPokemonGetPokemonPtr(p));
        if (v == 0) {
            v = 1;
        }
        fightWaza_SetIryoku(waza, v);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_GAMUSYARA(void) {
    u8* cmd;
    void* waza;
    FightOutPokemon* p;
    s32 hpA;
    s32 hpB;
    cmd = (u8*)fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    hpA = pokemon_GetHp(fightOutPokemonGetPokemonPtr(p));
    hpB = (u16)pokemon_GetHp(fightOutPokemonGetPokemonPtr(fightTargetGetPtrAsNowFightType(0x12, 0)));
    if (hpB <= hpA) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    } else {
        fightWaza_SetDamage(waza, hpB - hpA);
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_AKUBI(void) {
    WsJumpCmd* cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x26) != 2 || !fightOutPokemonIsJoutaiNormal(p)) {
        fightSeq_JumpWazaSeq(cmd->jump);
    } else {
        fightOutPokemonWriteJoutaiDataId(p, 0x26, 0);
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_REVENGE(void) {
    u16 speTarget; // @decl
    void* waza; // @decl
    s16 speValue; // @decl
    FightOutPokemon* p; // @decl
    u8 fightType; // @decl
    s16 atkValue; // @decl
    u16 atkTarget; // @decl
    u32 tid;
    fightType = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    atkValue = fightOutPokemon_GetDamageAtkValue(p);
    atkTarget = fightOutPokemon_GetDamageAtkTargetId(p);
    speValue = fightOutPokemon_GetDamageSpeValue(p);
    speTarget = fightOutPokemon_GetDamageSpeTargetId(p);
    tid = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(fightTargetGetPtrAsNowFightType(0x12, 0), fightType);
    if ((atkValue != 0 && atkTarget == (u16)tid) || (speValue != 0 && speTarget == (u16)tid)) {
        fightWaza_SetDamageValue(waza, 2);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_NEWOHARU(void) {
    WsJumpCmd* cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x25) != 2) {
        fightSeq_JumpWazaSeq(cmd->jump);
    } else {
        fightOutPokemonWriteJoutaiDataId(p, 0x25, 0);
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_NEGAIGOTO(void) {
    u8* cmd;
    FightOutPokemon* atk;
    FightOutPokemon* def;
    void* fw;
    void* nick;
    cmd = (u8*)fightSeq_GetWazaSeq();
    switch (cmd[1]) {
    case 0:
        atk = fightTargetGetPtrAsNowFightType(0x11, 0);
        nick = pokemon_GetNicknamePtr(fightPokemon_GetMotoPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(atk)));
        if (fightOutPokemonCheckWriteJoutaiDataId(atk, 0x35) != 2) {
            fightSeq_JumpWazaSeq(*(void**)(cmd + 2));
            return;
        }
        fightOutPokemonWriteJoutaiDataId(atk, 0x35, 0);
        fightOutPokemonSetBuffJoutaiDataId(atk, 0x35, (s32)nick);
        fightSeq_NextWazaSeq(6);
        return;
    case 1:
        atk = fightTargetGetPtrAsNowFightType(0x11, 0);
        fw = fightOutPokemon_GetFightWazaPtr(atk);
        def = fightTargetGetPtrAsNowFightType(0x12, 0);
        fightMsgctrlSetValue(0xD, fightOutPokemonGetBuffJoutaiDataId(atk, 0x35));
        fightWaza_SetDamage(fw, -(s32)fightOutPokemonMaxHpWaruValue(def, 2));
        if (fightOutPokemonIsHpMantan(def) == 1) {
            fightSeq_JumpWazaSeq(*(void**)(cmd + 2));
            return;
        }
        fightSeq_NextWazaSeq(6);
        return;
    }
}
}

extern "C" {
void WS_NARIKIRI(void) {
    WsJumpCmd* cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* self = fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemonGetTokuseiDataId(self);
    u32 tokusei = fightOutPokemonGetTokuseiDataId(fightTargetGetPtrAsNowFightType(0x12, 0));
    if ((u16)tokusei == 0 || (u16)tokusei == 0x19) {
        goto jump;
    }
    fightOutPokemonSetTokuseiDataId(self, tokusei);
    fightSeq_NextWazaSeq(5);
    return;
jump:
    fightSeq_JumpWazaSeq(cmd->jump);
}
}

extern "C" {
void WS_TRICK(void) {
    u8* cmd;
    FightOutPokemon* atk;
    FightOutPokemon* def;
    u32 atkItem;
    u16 defItem;
    volatile u16 tok;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    atkItem = fightOutPokemonGetSoubiItemDataId(atk);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    tok = fightOutPokemonGetTokuseiDataId(def);
    defItem = fightOutPokemonGetSoubiItemDataId(def);
    if (fightSeqIsDoItemGetWaza(atk) == 0) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    if (_fightSeq_IsTrickCheck(atk, def) == 0) {
        fightSeq_JumpWazaSeq(fightSeq_GetWazaSeqAdr(1));
        return;
    }
    if ((atkItem == 0 && defItem == 0) || atkItem == 0xAF || defItem == 0xAF || (atkItem != 0 && itemDataCheckValid(atkItem) == 0) || (defItem != 0 && itemDataCheckValid(defItem) == 0)) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    if (tok == 0x3C) {
        fightSeq_JumpWazaSeq(WAZA_Nentyaku);
        return;
    }
    if (atkItem != 0) {
        fightOutPokemonDoItemSoubi(atk, 0, 0, 0);
    }
    if (defItem != 0) {
        fightOutPokemonDoItemSoubi(def, 0, 0, 0);
    }
    if (atkItem != 0) {
        fightOutPokemonDoItemSoubi(def, atkItem, 1, 0);
    }
    if (defItem != 0) {
        fightOutPokemon_SetStockItemDataId(atk, defItem);
    }
    fightSeqCheckSetHensinBuffToMotoPokemon(atk, 0x82);
    fightSeqCheckSetHensinBuffToMotoPokemon(def, 0x82);
    fightOutPokemonInitJoutaiDataId(atk, 0x36);
    fightOutPokemonInitJoutaiDataId(def, 0x36);
    fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(itemDB_GetName(defItem)));
    fightMsgctrlSetValue(0xE, (u32)GSmsgGetGSchar(itemDB_GetName(atkItem)));
    if (atkItem != 0 && defItem != 0) {
        ServerWork[5] = 2;
    } else if (defItem != 0) {
        ServerWork[5] = 0;
    } else {
        ServerWork[5] = 1;
    }
    fightSeq_NextWazaSeq(5);
}
}

static u8 _fightSeq_IsTrickCheck(FightOutPokemon* a, FightOutPokemon* b) {
    if (fightFloorGetStatus(0, 0, 0x2f, 0) != 0 && (fightOutPokemonIsJoutaiDataId(a, 0x3d) || fightOutPokemonIsJoutaiDataId(b, 0x3d))) {
        return 0;
    }
    return 1;
}

extern "C" {
u8 fightSeqIsDoItemGetWaza(FightOutPokemon* p) {
    if (fightFloor_GetFightKindDorobouFlag(0) == 1) {
        return 0;
    }
    if (!fightFloor_GetFightKindDorobouFlag(0) && fightOutPokemonIsJoutaiDataId(p, 0x3d) == 1) {
        return 0;
    }
    return 1;
}
}

extern "C" {
void WS_TEDASUKE(void) {
    u8* cmd;
    FightOutPokemon* atk;
    FightOutPokemon* ally;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    ally = fightTargetGetPtrAsNowFightType(0xE, (u32)atk);
    if (ally != 0 && fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && fightOutPokemonCheckFightOut(ally) == 1 && fightOutPokemonIsJoutaiDataId(atk, 0x32) == 0 && fightOutPokemonIsJoutaiDataId(ally, 0x32) == 0) {
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, ally);
        if (fightOutPokemonCheckWriteJoutaiDataId(ally, 0x32) == 2) {
            fightOutPokemonWriteJoutaiDataId(ally, 0x32, 0);
        }
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
void WS_CHOUHATSU(void) {
    WsJumpCmd* cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x30) != 2) {
        fightSeq_JumpWazaSeq(cmd->jump);
    } else {
        fightOutPokemonWriteJoutaiDataId(p, 0x30, 0);
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_KIAIPUNCH(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    s16 atk = fightOutPokemon_GetDamageAtkValue(p);
    s16 spe = fightOutPokemon_GetDamageSpeValue(p);
    if (atk != 0 || spe != 0) {
        fightSeq_NextWazaSeq(5);
    } else {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    }
}
}

extern "C" {
void WS_ICHAMON(void) {
    WsJumpCmd* cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x1b) != 2) {
        fightSeq_JumpWazaSeq(cmd->jump);
    } else {
        fightOutPokemonWriteJoutaiDataId(p, 0x1b, 0);
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_REFLESH(void) {
    u8* cmd;
    FightOutPokemon* p;
    void* pokemon;
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    pokemon = fightOutPokemonGetPokemonPtr(p);
    cmd = (u8*)fightSeq_GetWazaSeq();
    if (fightOutPokemonIsJoutaiKaragenki(p) == 1) {
        pokemonInitJoutai(pokemon);
        fightOutPokemonResetSeqStatus(p, 0);
        fightSeq_NextWazaSeq(5);
        fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7c);
    } else {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    }
}
}

extern "C" {
void WS_SHIZENNOCHIKARA(void) {
    u8 type;
    FightOutPokemon* atk;
    void* fw;
    u32 waza;
    u32 seq;
    type = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    waza = tikeiDataBiosGetWazaId(fightFloor_GetTikeiDataId(0));
    seq = wazaDB_GetSeqId(waza);
    fightWazaSetUseWazaStatus(fw, waza);
    fightMsgctrlSetValue(0x28, (u32)GSmsgGetGSchar(wazaDB_GetName(waza)));
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, fightSeqSelectDefensePokemonPtr(atk, waza, type, 0, 1, 1, -1));
    ServerStatusFlag &= ~0x400;
    fightSeq_CallWazaSeq(WAZA_ShizennochikaraHitMsg);
    fightSeq_JumpWazaSeq(WazaEffectTbl[seq]);
}
}

extern "C" {
void WS_JUUDEN(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x24) == 2) {
        fightOutPokemonWriteJoutaiDataId(p, 0x24, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KONOYUBITOMARE(void) {
    FightOutPokemon* p;
    void* side;
    u32 rel;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(2, (u32)p);
    if (fightSideCheckWriteJoutaiDataId(side, 0x4d) == 2) {
        rel = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(p, fightFloor_GetFightType(0));
        fightSideWriteJoutaiDataId(side, 0x4d, rel);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_OKIMIYAGE(void) {
    u8 b;
    u8* cmd;
    FightOutPokemon* atk;
    void* fw;
    FightOutPokemon* def;
    u8 a;
    s32 menu;
    u8 type;
    type = fightFloor_GetFightType(0);
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    menu = fightMenuGetFightOutPokemonPtrToStatusMenuId(atk, type, true);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    a = pokemonGetStatus(def, 0, fightSeqCondChgActTypeToPokemonStatusId(1), 0);
    b = pokemonGetStatus(def, 0, fightSeqCondChgActTypeToPokemonStatusId(4), 0);
    if (a == 0 && b == 0 && ServerWork[6] != 1) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    fightWaza_SetDamage(fw, pokemon_GetHp(fightOutPokemonGetPokemonPtr(atk)));
    menuFightStatusSetHP(menu, 0);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_CHIISAKUNARU(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (ServerStatusFlag & 0x2000000) {
        if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x23) == 2) {
            fightOutPokemonWriteJoutaiDataId(p, 0x23, 0);
        }
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KIERUTAME_AFTAR(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    u16 moveId = fightOutPokemon_GetUseWazaDataId(p);
    switch (moveId) {
    case 0x13:
    case 0x154:
        if (fightOutPokemonIsJoutaiDataId(p, 0x1f) == 1) {
            fightOutPokemonInitJoutaiDataId(p, 0x1f);
        }
        break;
    case 0x5b:
        if (fightOutPokemonIsJoutaiDataId(p, 0x20) == 1) {
            fightOutPokemonInitJoutaiDataId(p, 0x20);
        }
        break;
    case 0x123:
        if (fightOutPokemonIsJoutaiDataId(p, 0x21) == 1) {
            fightOutPokemonInitJoutaiDataId(p, 0x21);
        }
        break;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KIERUTAME(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    u16 moveId = fightOutPokemon_GetUseWazaDataId(p);
    switch (moveId) {
    case 0x13:
    case 0x154:
        if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x1f) == 2) {
            fightOutPokemonWriteJoutaiDataId(p, 0x1f, 0);
        }
        break;
    case 0x5b:
        if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x20) == 2) {
            fightOutPokemonWriteJoutaiDataId(p, 0x20, 0);
        }
        break;
    case 0x123:
        if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x21) == 2) {
            fightOutPokemonWriteJoutaiDataId(p, 0x21, 0);
        }
        break;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HUKURODATAKI(void) {
    u8* cmd;
    FightOutPokemon* atk;
    FightOutPokemon* def;
    void* trainer;
    void* pk;
    void* hero;
    u32 waza;
    void* fp;
    u8 start;
    s32 dmg;
    void* fw;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, atk);
    hero = fightTrainer_GetHeroPtr(trainer);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckFightOut(atk) == 0) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    start = ServerWork[0];
    pk = 0;
    while (ServerWork[0] < 6) {
        pk = (void*)heroGetStatus(hero, 3, ServerWork[0]);
        fp = fightTrainerCheckTemotiPokemonFightEntry(trainer, pk);
        if (fp != 0 && fightPokemonCheckValid(fp) != 0 && (pk = fightPokemonGetPokemonPtr(fp), pokemonCheckFightOut(pk) == 1) && pokemonIsJoutaiNormal(pk) == 1) {
            break;
        }
        ServerWork[0]++;
    }
    if (ServerWork[0] < 6) {
        u32 pid = pokemon_GetPokemonDataId(pk);
        u8 lv = pokemon_GetLevel(pk);
        u32 did = figthOutPokemonGetPokemonDataId(def);
        u8 dlv = figthOutPokemonGetLevel(def);
        fightMsgctrlSetValue(0xD, (u32)pokemon_GetNicknamePtr(pk));
        dmg = fightSeqGetHukuroDatakiDamage(waza, pid, lv, did);
        if (fightOutPokemonIsJoutaiDataId(atk, 0x32) == 1) {
            dmg = (dmg * 15) / 10;
        }
        fightWaza_SetDamage(fw, dmg);
        ServerWork[0]++;
        fightSeq_NextWazaSeq(9);
        return;
    }
    if (start != 0) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 5));
}
}

extern "C" {
s32 fightSeqGetHukuroDatakiDamage(u32 wazaId, u32 atkMon, u16 level, u32 defMon) {
    s32 dmg = (u16)pokemonDB_GetBasisPhyAtk(atkMon);
    s32 def;
    dmg *= (u16)wazaDB_GetIryoku(wazaId);
    dmg *= (level * 2) / 5 + 2;
    def = (u16)pokemonDB_GetBasisPhyDef(defMon);
    if (def <= 0) {
        def = 1;
    }
    dmg /= def;
    return dmg / 50 + 2;
}
}

extern "C" {
void WS_MIRAIYOCHI(void) {
    enum TsE { TsE0 };
    u8 type;
    u8* cmd;
    FightOutPokemon* atk;
    enum TsE tid;
    void* fw;
    u16 waza;
    s32 power;
    u16 zokusei;
    FightOutPokemon* def;
    void* side;
    type = fightFloor_GetFightType(0);
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    tid = (enum TsE)(fightTargetGetTragetPtrToRelativeHostSideFightTargetId(atk, type));
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    power = fightWaza_GetIryoku(fw);
    zokusei = fightWaza_GetZokusei(fw);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    side = fightTargetGetPtrAsNowFightType(2, (u32)def);
    if (fightOutPokemonCheckWriteJoutaiDataId(def, 0x34) != 2) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(def, 0x34, tid);
    fightOutPokemonSetIdBuffJoutaiDataId(def, 0x34, waza);
    power = fightSeqWazaDamageCalc(atk, def, (FightOutPokemon*)side, waza, power, zokusei);
    if (fightOutPokemonIsJoutaiDataId(atk, 0x32) == 1) {
        power = (power * 15) / 10;
    }
    fightOutPokemonSetBuffJoutaiDataId(def, 0x34, power);
    if (waza == 0x161) {
        ServerWork[5] = 1;
    } else {
        ServerWork[5] = 0;
    }
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_JISIN(void) {
    FightOutPokemon* atk;
    FightOutPokemon* p;
    FightOutPokemon* found;
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fightSeq_GetWazaSeq();
    fight_seq_banme_max = 8;
    found = 0;
    fight_seq_banme_buff = 0;
    for (; fight_seq_banme_buff < fight_seq_banme_max; fight_seq_banme_buff++) {
        p = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData(fight_seq_banme_buff);
        if (p != 0 && fightOutPokemonCheckFightOut(p) != 0 && atk != p) {
            found = p;
            break;
        }
    }
    if (found != 0) {
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, found);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_MEZAMERUPOWER(void) {
    u16 power;
    u16 zokusei;
    FightOutPokemon* p;
    void* waza;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(p), &power, &zokusei);
    fightWaza_SetIryoku(waza, power);
    fightWaza_SetZokusei(waza, zokusei);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_WEATHERKAIFUKU(void) {
    u8* cmd;
    FightOutPokemon* atk;
    void* fw;
    u8 weather;
    u16 heal;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, atk);
    weather = fightFloorGetNowTenkouDataId(0, 1);
    if (fightOutPokemonIsHpMantan(atk) == 0) {
        if (weather == 0) {
            heal = fightOutPokemonMaxHpWaruValue(atk, 2);
        } else if (weather == 1) {
            heal = (u16)((s32)(fightOutPokemonMaxHpWaruValue(atk, 1) * 20) / 30);
        } else {
            heal = fightOutPokemonMaxHpWaruValue(atk, 4);
        }
        fightWaza_SetDamage(fw, -(s32)heal);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
void WS_MARUKUNARU(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x1a) == 2) {
        fightOutPokemonWriteJoutaiDataId(p, 0x1a, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KOUSOKUSPIN(void) {
    u8 type;
    FightOutPokemon* atk;
    void* side;
    FightOutPokemon* def;
    FightOutPokemon* t;
    u16 tid;
    type = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(2, (u32)atk);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonIsJoutaiDataId(atk, 0xE) == 1 && (tid = fightOutPokemonGetUserFightTargetIdJoutaiDataId(atk, 0xE)) != 0) {
        t = (FightOutPokemon*)fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(tid, type);
        if (t != 0) {
            fightFloor_SetDefensePokemonPtr(0, t);
            fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(fightOutPokemonGetIdBuffJoutaiDataId(atk, 0xE))));
            fightOutPokemonInitJoutaiDataId(atk, 0xE);
            fightSeq_CallWazaSeq(WAZA_ShimeEscape);
            fightFloor_SetDefensePokemonPtr(0, def);
        }
    }
    if (fightOutPokemonIsJoutaiDataId(atk, 0x1C) == 1) {
        fightOutPokemonInitJoutaiDataId(atk, 0x1C);
        fightSeq_CallWazaSeq(WAZA_YadorigiEscape);
    }
    if (fightSideIsJoutaiDataId(side, 0x4A) == 1) {
        fightSideInitJoutaiDataId(side, 0x4A);
        fightSeq_CallWazaSeq(WAZA_MakibishiEscape);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_JIKOANJI(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* a = fightTargetGetPtrAsNowFightType(0x11, 0);
    FightOutPokemon* b = fightTargetGetPtrAsNowFightType(0x12, 0);
    fightOutPokemonCopyAllAbiCnt(a, b);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_HARADAIKO(void) {
    u16 half;
    FightOutPokemon* atk;
    void* fw;
    u16 hp;
    u8* cmd;
    s32 st;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    hp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(atk));
    half = fightOutPokemonMaxHpWaruValue(atk, 2);
    st = fightSeqCondChgActTypeToPokemonStatusId(1);
    if (pokemonGetStatus(atk, 0, st, 0) < 0xC && hp > half) {
        pokemonSetStatus(atk, 0, st, 0, 0xC);
        fightWaza_SetDamage(fw, half);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
void WS_OIUCHI_CHECK(void) {
    u8* cmd;
    FightOutPokemon* atk;
    FightOutPokemon* p;
    FightOutPokemon* found;
    u32 tid;
    void* act;
    void* fw;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x14, 0);
    tid = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(atk, fightFloor_GetFightType(0));
    if ((u16)fightOutPokemonCheckFightOut(atk) == 0) {
        fight_seq_banme_buff = fight_seq_banme_max;
    } else {
        p = 0;
        found = 0;
        for (; fight_seq_banme_buff < fight_seq_banme_max; fight_seq_banme_buff++) {
            p = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData(fight_seq_banme_buff);
            if (p != 0 && (u16)fightOutPokemonCheckFightOut(p) != 0 && atk != p && (u16)fightOutPokemonIsAlly(atk, p) != 1 && (act = fightOutPokemon_GetFightActionBuffPtr(p), act != 0) && (u16)fightActionCheckValid(act) != 0 && (u16)fightActionGetKindDataId(act) == 0x13 && (fw = fightOutPokemon_GetFightWazaPtr(p), (u16)fightOutPokemon_GetUseWazaDataId(p) == 0xE4) && (u16)tid == fightWaza_GetTargetDataId(fw) && (u16)fightOutPokemonIsJoutaiDataId(p, 8) != 1 && (u16)fightOutPokemonIsJoutaiDataId(p, 7) != 1 && (u16)fightOutPokemon_GetNamakeFlag(p) != 1) {
                found = p;
                break;
            }
        }
        if (found != 0) {
            fightFloor_SetDefensePokemonPtr(0, found);
            UserWork[0x16002] = 1;
            ServerStatusFlag &= ~0x400;
            fightOutPokemon_SetFightActionFlag(p, 1);
            fightSeq_NextWazaSeq(5);
            return;
        }
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
void WS_MAGNITUDE(void) {
    u8 mag;
    u8 r;
    void* fw;
    u16 power;
    fightSeq_GetWazaSeq();
    fw = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    r = (u16)HSD_Rand() % 100;
    if (r < 5) {
        power = 10;
        mag = 4;
    } else if (r < 15) {
        power = 30;
        mag = 5;
    } else if (r < 35) {
        power = 50;
        mag = 6;
    } else if (r < 65) {
        power = 70;
        mag = 7;
    } else if (r < 85) {
        power = 90;
        mag = 8;
    } else if (r < 95) {
        power = 110;
        mag = 9;
    } else {
        power = 150;
        mag = 10;
    }
    fightWaza_SetIryoku(fw, power);
    fightMsgctrlSetValue(0x2F, mag);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_SHINPINOMAMORI(void) {
    void* side;
    FightOutPokemon* p;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(2, (u32)p);
    if (fightSideCheckWriteJoutaiDataId(side, 0x4b) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork[5] = 0;
    } else {
        fightSideWriteJoutaiDataId(side, 0x4b, 0);
        ServerWork[5] = 5;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_PRESENT(void) {
    FightOutPokemon* def;
    void* fw;
    u8 r;
    fightSeq_GetWazaSeq();
    fw = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    r = HSD_Rand();
    if (r < 0x66) {
        fightWaza_SetIryoku(fw, 0x28);
    } else if (r < 0xB2) {
        fightWaza_SetIryoku(fw, 0x50);
    } else if (r < 0xCC) {
        fightWaza_SetIryoku(fw, 0x78);
    } else {
        fightWaza_SetDamage(fw, -(s32)fightOutPokemonMaxHpWaruValue(def, 4));
    }
    if (r < 0xCC) {
        fightSeq_JumpWazaSeq(WAZA_HitCalcOnly);
        return;
    }
    if (fightOutPokemonIsHpMantan(def) == 1) {
        fightSeq_JumpWazaSeq(WAZA_Mantan);
        return;
    }
    fightWazaInitJoutaiDataId(fw, 0x43);
    fightSeq_JumpWazaSeq(WAZA_Kaifuku);
}
}

extern "C" {
void WS_NATSUKI(void) {
    FightOutPokemon* p;
    void* waza;
    void* pk;
    u32 seq;
    u16 power;
    u16 fr;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    pk = fightOutPokemonGetPokemonPtr(p);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    seq = wazaDB_GetSeqId(fightOutPokemon_GetUseWazaDataId(p));
    fr = pokemon_GetFriend(pk);
    if ((u16)seq == 0x79) {
        power = fightSeqGetOngaesiIryoku(fr);
    } else {
        power = fightSeqGetYatuatariIryoku(fr);
    }
    fightWaza_SetIryoku(waza, power);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
u16 fightSeqGetYatuatariIryoku(u16 x) {
    return (255 - x) * 10 / 25;
}
}

extern "C" {
u16 fightSeqGetOngaesiIryoku(u16 x) {
    return x * 10 / 25;
}
}

extern "C" {
void WS_RENZOKUGIRI(void) {
    FightOutPokemon* atk;
    void* fw;
    u32 waza;
    s16 cnt;
    u16 power;
    int i;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    if (fightWazaIsHit(fw) == 0) {
        if (fightOutPokemonIsJoutaiDataId(atk, 0x2E) == 1) {
            fightOutPokemonInitJoutaiDataId(atk, 0x2E);
        }
        fightSeq_JumpWazaSeq(WAZA_NormalNohitWait);
        return;
    }
    if (fightOutPokemonCheckWriteJoutaiDataId(atk, 0x2E) == 2) {
        fightOutPokemonWriteJoutaiDataId(atk, 0x2E, 0);
    }
    cnt = fightOutPokemonGetCountAsJoutaiDataId(atk, 0x2E);
    power = wazaDB_GetIryoku(waza);
    for (i = 1; i < cnt; i++) {
        power *= 2;
    }
    fightWaza_SetIryoku(fw, (u16)power);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_IBARU(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    u8 type = cmd[1];
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x12, 0);
    s32 id = fightSeqCondChgActTypeToPokemonStatusId(type);
    s8 st = pokemonGetStatus(p, 0, id, 0);
    if (fightOutPokemonIsJoutaiDataId(p, 9) == 1 && st >= 12) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 2));
    } else {
        fightSeq_NextWazaSeq(6);
    }
}
}

extern "C" {
void WS_KOROGARU(void) {
    enum TsE { TsE0 };
    FightOutPokemon* atk;
    void* fw;
    void* keep;
    u32 waza;
    s16 cnt;
    enum TsE max;
    u16 power;
    u16 i;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    keep = fightOutPokemon_GetKeepFightWazaPtr(atk);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    if (fightWazaIsHit(fw) == 0) {
        fightOutPokemonInitJoutaiKeep(atk);
        fightSeq_JumpWazaSeq(WAZA_NormalNohitWait);
        return;
    }
    if (fightOutPokemonCheckWriteJoutaiDataId(atk, 0x2F) == 2) {
        fightOutPokemonWriteJoutaiDataId(atk, 0x2F, 0);
        if (fightOutPokemonIsJoutaiDataId(atk, 0x22) == 0) {
            fightOutPokemonWriteJoutaiDataId(atk, 0x22, 0);
            fightWazaBiosCopy(keep, fw);
        }
    }
    cnt = 1;
    if (fightOutPokemonIsJoutaiDataId(atk, 0x2F) == 1) {
        max = (enum TsE)(joutaiDataBiosGetMaxCount(0x2F));
        if ((cnt = fightOutPokemonGetCountAsJoutaiDataId(atk, 0x2F)) == max) {
            fightOutPokemonInitJoutaiDataId(atk, 0x2F);
            fightOutPokemonInitJoutaiDataId(atk, 0x22);
        }
    }
    power = wazaDB_GetIryoku(waza);
    for (i = 1; i < cnt; i++) {
        power *= 2;
    }
    fightWaza_SetIryoku(fw, power);
    if (fightOutPokemonIsJoutaiDataId(atk, 0x1A) == 1) {
        fightWaza_SetIryoku(fw, (fightWaza_GetIryoku(fw) * 2) & 0xFFFE);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HOROBINOUTA(void) {
    s32 flag;
    u8* cmd;
    FightOutPokemon* atk;
    FightOutPokemon* def;
    u32 waza;
    flag = 0;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightSeqRegulationCheck(waza, atk, def) == 1) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    fightFloorLoopValidFightOutPokemon(0, _fightSeqWsHorobinoutaSub, &flag, 0);
    fightSeqPressurePpdecCheckHorobinouta(atk);
    if (flag == 0) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    fightSeq_NextWazaSeq(5);
}
}

static s32 _fightSeqWsHorobinoutaSub(void* pokemon, u16 id, void* user) {
    FightOutPokemon* p = (FightOutPokemon*)pokemon;
    int* count = (int*)user;
    if (!fightOutPokemonCheckFightOut(p)) {
        return 1;
    }
    u32 tokusei = fightOutPokemonGetTokuseiDataId(p);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x1e) != 2 || (u16)tokusei == 0x2b) {
        return 1;
    }
    fightOutPokemonWriteJoutaiDataId(p, 0x1e, 0);
    *count = *count + 1;
    return 1;
}

extern "C" {
void WS_MIYABURU(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0x19) == 2) {
        fightOutPokemonWriteJoutaiDataId(p, 0x19, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_MAKIBISHI(void) {
    s16 cnt;
    u8* cmd;
    FightOutPokemon* atk;
    void* side;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(3, (u32)atk);
    if (fightSideCheckWriteJoutaiDataId(side, 0x4A) == 2) {
        if (fightSideIsJoutaiDataId(side, 0x4A) == 1) {
            cnt = fightSideGetCountAsJoutaiDataId(side, 0x4A);
        } else {
            cnt = 0;
        }
        if (cnt != joutaiDataBiosGetMaxCount(0x4A)) {
            fightSideWriteJoutaiDataId(side, 0x4A, 0);
            fightSeq_NextWazaSeq(5);
            return;
        }
    }
    fightOutPokemon_SetNoPressureFlag(atk, 1);
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
void WS_NOROI(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    FightOutPokemon* d; // @decl
    void* waza; // @decl
    waza = fightOutPokemon_GetFightWazaPtr(p);
    d = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(d, 0x18) != 2) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    } else {
        fightOutPokemonWriteJoutaiDataId(d, 0x18, 0);
        fightWaza_SetDamage(waza, (u16)fightOutPokemonMaxHpWaruValue(p, 2));
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_IYASHINOSUZU(void) {
    u32 n;
    FightOutPokemon* atk;
    void* hero;
    FightOutPokemon* ally;
    volatile u16 waza;
    u32 i;
    u32 j;
    void* trainer;
    void* side;
    void* fp;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    ally = fightTargetGetPtrAsNowFightType(0xE, (u32)atk);
    side = fightTargetGetPtrAsNowFightType(2, (u32)atk);
    n = fightFloor_GetFightTypeTrainerNum(0);
    if (waza == 0xD7) {
        ServerWork[5] = 0;
        if ((u16)fightOutPokemonGetTokuseiDataId(atk) != 0x2B) {
            pokemonInitJoutai(fightOutPokemonGetPokemonPtr(atk));
            fightOutPokemonResetSeqStatus(atk, 0);
            fightOutPokemonInitJoutaiDataId(atk, 0x17);
            fightSeqCheckSetHensinBuffToMotoPokemon(atk, 0x7C);
        } else {
            ServerWork[5] |= 1;
        }
        if (ally != 0 && (u16)fightOutPokemonCheckValid(ally) == 1) {
            fightFloor_SetAppointPokemonPtr(0, ally);
            if ((u16)fightOutPokemonGetTokuseiDataId(ally) != 0x2B) {
                pokemonInitJoutai(fightOutPokemonGetPokemonPtr(ally));
                fightOutPokemonResetSeqStatus(ally, 0);
                fightOutPokemonInitJoutaiDataId(ally, 0x17);
                fightSeqCheckSetHensinBuffToMotoPokemon(ally, 0x7C);
            } else {
                ServerWork[5] |= 2;
            }
        }
        for (i = 0; i < n; i++) {
            trainer = fightSideGetValidFightTrainerPtr(side, i);
            if (trainer != 0) {
                hero = fightTrainer_GetHeroPtr(trainer);
                for (j = 0; j < 6; j++) {
                    fp = fightTrainerCheckTemotiPokemonFightEntry(trainer, (void*)heroGetStatus(hero, 3, j));
                    if (fp != 0 && (u16)fightPokemonCheckValid(fp) != 0) {
                        void* pk = fightPokemonGetPokemonPtr(fp);
                        if ((u16)pokemonGetTokuseiDataId(pk) != 0x2B) {
                            pokemonInitJoutai(pk);
                        }
                    }
                }
            }
        }
    } else {
        ServerWork[5] = 4;
        pokemonInitJoutai(fightOutPokemonGetPokemonPtr(atk));
        fightOutPokemonInitJoutaiDataId(atk, 0x17);
        fightSeqCheckSetHensinBuffToMotoPokemon(atk, 0x7C);
        if (ally != 0 && (u16)fightOutPokemonCheckValid(ally) == 1) {
            fightFloor_SetAppointPokemonPtr(0, ally);
            pokemonInitJoutai(fightOutPokemonGetPokemonPtr(ally));
            fightOutPokemonResetSeqStatus(ally, 0);
            fightOutPokemonInitJoutaiDataId(ally, 0x17);
            fightSeqCheckSetHensinBuffToMotoPokemon(ally, 0x7C);
        }
        for (i = 0; i < n; i++) {
            trainer = fightSideGetValidFightTrainerPtr(side, i);
            if (trainer != 0) {
                hero = fightTrainer_GetHeroPtr(trainer);
                for (j = 0; j < 6; j++) {
                    fp = fightTrainerCheckTemotiPokemonFightEntry(trainer, (void*)heroGetStatus(hero, 3, j));
                    if (fp != 0 && (u16)fightPokemonCheckValid(fp) != 0) {
                        pokemonInitJoutai(fightPokemonGetPokemonPtr(fp));
                    }
                }
            }
        }
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_URAMI(void) {
    u8* cmd;
    FightOutPokemon* def;
    void* pk;
    u16 waza;
    u8 pp;
    u8 slot;
    u8 dec;
    u8 left;
    cmd = (u8*)fightSeq_GetWazaSeq();
    fightTargetGetPtrAsNowFightType(0x11, 0);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    pk = fightOutPokemonGetPokemonPtr(def);
    waza = fightOutPokemon_GetLastSelectWazaDataId(def);
    if (waza != 0 && waza != 0x176 && waza != 0xFFFF && wazaCheckDarkWaza((u8)waza) == 0) {
        pp = 0;
        for (slot = 0; slot < 4; slot++) {
            if (pokemonWazaCheckValid(pk, (u16)slot) != 0 && waza == pokemon_GetPokemonWazaDataId(pk, slot)) {
                pp = pokemon_GetPokemonWazaPp(pk, slot);
                break;
            }
        }
        if (slot >= 4) {
            fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
            return;
        }
        if (pp < 2) {
            fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
            return;
        }
        dec = HSD_Rand() % 4 + 2;
        if (pp < dec) {
            dec = pp;
        }
        fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(waza)));
        fightMsgctrlSetValue(0x2F, dec);
        pokemon_SetPokemonWazaPp(pk, slot, left);
        left = pp - dec;
        fightSeqPpdecMonomane(def, slot, 0);
        if (left == 0) {
            fightOutPokemonInitJoutaiKeep(def);
        }
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
void WS_JITABATA(void) {
    FightOutPokemon* p;
    void* waza;
    void* pk;
    u16 hp;
    u8 n;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    pk = fightOutPokemonGetPokemonPtr(p);
    hp = pokemon_GetHp(pk);
    u16 max = pokemon_GetMaxHp(pk);
    n = fightSeqGetJitabataIryoku(hp, max);
    fightWaza_SetIryoku(waza, n);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
u8 fightSeqGetJitabataIryoku(u16 hp, u16 max) {
    u8 n = fightSeqGetNumDotto(hp, max, 0x30);
    u32 i;
    for (i = 0; i < 12; i += 2) {
        if (n <= JitabataTbl[i]) {
            break;
        }
    }
    return JitabataTbl[i + 1];
}
}

static u8 fightSeqGetNumDotto(u16 a, u16 b, u8 c) {
    u8 r = a * c / b;
    if (r == 0 && a != 0) {
        r = 1;
    }
    return r;
}

extern "C" {
void WS_MICHIDURE_CHECK(void) {
    fightSeqMichidureCheckAct(fightSeq_GetWazaSeq());
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void fightSeqMichidureCheckAct(void* cmd) {
    void* sideA;
    FightOutPokemon* atk;
    FightOutPokemon* def;
    void* sideB;
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    sideA = fightTargetGetPtrAsNowFightType(2, (u32)atk);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    sideB = fightTargetGetPtrAsNowFightType(2, (u32)def);
    if (fightOutPokemonIsJoutaiDataId(def, 0x15) == 1 && sideA != sideB && !(ServerStatusFlag & 0x1000000)) {
        ServerStatusFlag |= 0x40;
    }
}
}

extern "C" {
void WS_MICHIDURE(void) {
    WsJumpCmd* cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* self = fightTargetGetPtrAsNowFightType(0x11, 0);
    u32 move = fightOutPokemon_GetUseWazaDataId(self);
    FightOutPokemon* target = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightSeqRegulationCheck(move, self, target) == 1) {
        fightSeq_JumpWazaSeq(cmd->jump);
    } else {
        if (fightOutPokemonCheckWriteJoutaiDataId(self, 0x15) == 2) {
            fightOutPokemonWriteJoutaiDataId(self, 0x15, 0);
        }
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
void WS_NEGOTO(void) {
    u8* cmd; // @decl
    u8 fightType; // @decl
    FightOutPokemon* p; // @decl
    u8 count; // @decl
    s16 j; // @decl
    void* waza; // @decl
    void* pk; // @decl
    u32 id; // @decl
    s16 sel;
    FightOutPokemon* def;
    s16 list[4];
    u8 i;
    fightType = fightFloor_GetFightType(0);
    cmd = (u8*)fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    pk = fightOutPokemonGetPokemonPtr(p);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    for (i = 0; i < 4;) {
        list[i++] = -1;
    }
    count = 0;
    for (j = 0; j < 4; j++) {
        id = (u16)j;
        if (pokemonWazaCheckValid(pk, id)) {
            u8 ok = fightOutPokemonCheckCanOutOkWazaBanme(p, id, 0, 0);
            if (ok == 0 || ok == 6) {
                id = pokemon_GetPokemonWazaDataId(pk, id);
                if ((u16)id != 0 && (u16)id != 0x176 && (u16)id != 0x163 && !fightSeqRendouWazaCheck(id) && (u16)id != 0x108 &&
                    (u16)id != 0xfd && !fightSeqTameWazaCheck(id)) {
                    list[count++] = j;
                }
            }
        }
    }
    if (count == 0) {
    fail:
        fightSeq_NextWazaSeq(5);
    } else {
        sel = list[(u8)((u16)HSD_Rand() % count)];
        if (sel < 0) {
            goto fail;
        }
        id = pokemon_GetPokemonWazaDataId(pk, sel);
        if ((u16)id == 0 || (u16)id == 0x176 || (u16)id == 0x163) {
            goto fail;
        }
        PushWazaNo = id;
        fightWaza_SetWazaBanme(waza, sel);
        ServerStatusFlag &= ~0x400;
        def = fightSeqSelectDefensePokemonPtr(p, PushWazaNo, fightType, 0, 1, 1, -1);
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, def);
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
    }
}
}

extern "C" {
s32 fightSeqTameWazaTurnCheck(u32 waza) {
    u32 seq;
    seq = wazaDB_GetSeqId((u16)waza);
    if (seq == 0x97 && (u16)fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 2;
    }
    if (seq == 0x91 || seq == 0x27 || seq == 0x4B || seq == 0x97 || seq == 0x9B || seq == 0x1A) {
        return 2 - ((ServerStatusFlag >> 27) & 1);
    }
    return 2;
}
}

extern "C" {
u8 fightSeqRendouWazaCheck(u32 waza) {
    u16 id = waza;
    if (id == 0 || id == 0x176 || id == 0xd6 || id == 0x112 || id == 0x77 || id == 0x76) {
        return 1;
    }
    return 0;
}
}

extern "C" {
u8 fightSeqTameWazaCheck(u32 id) {
    u32 seq = wazaDB_GetSeqId(id);
    if ((u16)seq == 0x91 || (u16)seq == 0x27 || (u16)seq == 0x4b || (u16)seq == 0x97 || (u16)seq == 0x9b || (u16)seq == 0x1a) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void WS_SKETCH(void) {
    enum TsE { TsE0 };
    u8* cmd;
    FightOutPokemon* atk;
    void* fw;
    enum TsE waza;
    void* motoPk;
    void* curPk;
    void* motoFp;
    void* curFp;
    s8 slot;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    fightTargetGetPtrAsNowFightType(0x12, 0);
    waza = (enum TsE)(fightOutPokemon_GetSketchWazaDataId(atk));
    fightWaza_SetMotoWazaDataId(fw, 0xFFFF);
    if (!(fightOutPokemonIsJoutaiDataId(atk, 0x10) == 1 || fightSeqIsSketchNgWazaDataId(waza) == 1)) {
        motoFp = fightOutPokemon_GetMotoFightPokemonPtr(atk);
        curFp = fightOutPokemon_GetFightPokemonPtr(atk);
        motoPk = fightPokemonGetPokemonPtr(motoFp);
        curPk = fightPokemonGetPokemonPtr(curFp);
        if (pokemonSearchWazaDataId(motoPk, waza) < 0) {
            slot = fightWaza_GetWazaBanme(fw);
            if (slot >= 0) {
                pokemonWazaCreate(motoPk, slot, waza);
                if (fightOutPokemonIsUseHensinBuff(atk) == 1) {
                    pokemonWazaCreate(curPk, slot, waza);
                }
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(waza)));
                fightSeq_NextWazaSeq(5);
                return;
            }
        }
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
u8 fightSeqIsSketchNgWazaDataId(u32 id) {
    if ((u16)id == 0xa5 || wazaCheckDarkWaza(id) == 1 || (u16)id == 0xa6 || (u16)id == 0xffff || (u16)id == 0 || (u16)id == 0x176) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void WS_LOCKON(void) {
    FightOutPokemon* p;
    FightOutPokemon* t;
    u32 rel;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    rel = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(p, fightFloor_GetFightType(0));
    t = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(t, 0x1d) == 2) {
        fightOutPokemonWriteJoutaiDataId(t, 0x1d, rel);
    }
    fightSeq_NextWazaSeq(1);
}
}

#pragma push
#pragma dont_inline on
extern "C" {
void WS_TEXTURE2(void) {
    s32 ary[18];
    u8 type;
    u8* cmd;
    FightOutPokemon* atk;
    u16 hit;
    s32 zok;
    FightOutPokemon* t;
    u16 n;
    s32 pick;
    u16 i;
    type = fightFloor_GetFightType(0);
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemon_GetFightWazaPtr(atk);
    hit = fightOutPokemon_GetHitWazaDataId(atk);
    fightOutPokemon_GetDamageAtkValue(atk);
    fightOutPokemon_GetDamageSpeValue(atk);
    zok = fightOutPokemon_GetHitWazaZokuseiDataId(atk);
    t = (FightOutPokemon*)fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightOutPokemon_GetLastReceiveWazaTargetDataId(atk), type);
    if (hit == 0 || hit == 0x176 || hit == 0xFFFF || wazaCheckDarkWaza(hit) == 1) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    if (t != 0 && fightSeqTameWazaCheck((u16)hit) != 0 && fightOutPokemonIsJoutaiDataId(t, 0x22) == 1) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    n = fightOutPokemonGetTeikouZokuseiDataIdAry(atk, zok, ary);
    if (n == 0) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    pick = ary[HSD_Rand() % n];
    if (pick < 0) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    for (i = 0; i < 2; i++) {
        fightOutPokemonSetZokuseiDataId(atk, i, (u16)pick);
    }
    fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(zokuseiBiosGetName(pick)));
    fightSeq_NextWazaSeq(5);
}
}
#pragma pop

extern "C" {
void WS_ITAMIWAKE(void) {
    FightOutPokemon* def;
    FightOutPokemon* atk;
    void* fw;
    u32 atkHp;
    u8* cmd;
    u32 defHp;
    s32 avg;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    atkHp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(atk));
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    defHp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(def));
    if (fightOutPokemonIsJoutaiDataId(def, 0x14) == 0) {
        avg = (s32)(atkHp + defHp) / 2;
        WazaDamage = defHp - avg;
        fightWaza_SetDamage(fw, atkHp - avg);
        fightOutPokemon_SetKaigaraDamageValue(def, 0xFFFF);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
void WS_ENCORE(void) {
    extern s8 pokemonSearchWazaDataId(void*, u16);
    u8* cmd;
    FightOutPokemon* def;
    void* pk;
    u16 waza;
    s8 slot;
    u8 pp;
    cmd = (u8*)fightSeq_GetWazaSeq();
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    pk = fightOutPokemonGetPokemonPtr(def);
    waza = fightOutPokemon_GetLastSelectWazaDataId(def);
    slot = pokemonSearchWazaDataId(pk, waza);
    if (slot < 0) {
        pp = 0;
    } else {
        pp = pokemon_GetPokemonWazaPp(pk, slot);
    }
    u8 cmpv = (u16)fightSeqIsEncoreNgWazaDataId(waza);
    if (cmpv == 1) {
        pp = 0;
        slot = -1;
    }
    if ((u16)fightOutPokemonCheckWriteJoutaiDataId(def, 0x2A) == 2 && slot >= 0 && pp != 0) {
        fightOutPokemonWriteJoutaiDataId(def, 0x2A, 0);
        s32 tmp2 = pokemon_GetPokemonWazaDataId(pk, slot);
        fightOutPokemonSetIdBuffJoutaiDataId(def, 0x2A, tmp2);
        fightOutPokemonSetBuffJoutaiDataId(def, 0x2A, slot);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
s32 fightSeqIsEncoreNgWazaDataId(u16 move) {
    if (move == 0xa5 || move == 0xe3 || move == 0x77 || move == 0xffff) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void WS_KANASHIBARI(void) {
    extern s8 pokemonSearchWazaDataId(void*, u16);
    extern void* wazaDB_GetName(u32 id);
    u8* cmd;
    FightOutPokemon* def;
    void* pk;
    s8 slot;
    u8 pp;
    u32 waza;
    cmd = (u8*)fightSeq_GetWazaSeq();
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    pk = fightOutPokemonGetPokemonPtr(def);
    u16 tmp1 = fightOutPokemon_GetLastSelectWazaDataId(def);
    slot = pokemonSearchWazaDataId(pk, tmp1);
    if (slot < 0) {
        pp = 0;
    } else {
        pp = pokemon_GetPokemonWazaPp(pk, slot);
    }
    if (fightOutPokemonCheckWriteJoutaiDataId(def, 0x29) == 2 && slot >= 0 && pp != 0) {
        waza = pokemon_GetPokemonWazaDataId(pk, slot);
        fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(waza)));
        fightOutPokemonWriteJoutaiDataId(def, 0x29, 0);
        fightOutPokemonSetIdBuffJoutaiDataId(def, 0x29, waza);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
void WS_MIRRORCOAT(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    _fightSeqDamageHanekaesi(0x105, 0x104, 5, *(u32*)(cmd + 1));
}
}

extern "C" {
void WS_COUNTER(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    _fightSeqDamageHanekaesi(0x103, 0x102, 5, *(u32*)(cmd + 1));
}
}

static void _fightSeqDamageHanekaesi(u16 idA, u16 idB, u8 next, u32 jump) {
    enum TsE { TsE0 };
    u8 fightType;
    FightOutPokemon* p;
    void* waza;
    u16 atk;
    enum TsE val;
    FightOutPokemon* t;
    FightOutPokemon* d;
    fightType = fightFloor_GetFightType(0);
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    atk = pokemonGetStatus(p, 0, idA, 0);
    val = (enum TsE)(pokemonGetStatus(p, 0, idB, 0));
    if (atk != 0 && val != 0 && (t = (FightOutPokemon*)fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(atk, fightType)) != 0 && !fightOutPokemonIsAlly(p, t) &&
        fightOutPokemonCheckFightOut(t) == 1) {
        fightWaza_SetDamage(waza, val * 2);
        d = fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(p);
        if (d != 0) {
            t = d;
        }
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, t);
        fightSeq_NextWazaSeq(next);
    } else {
        fightOutPokemon_SetNoPressureFlag(p, 1);
        fightSeq_JumpWazaSeq((void*)jump);
    }
}

extern "C" {
void WS_PSYCHOWAVE(void) {
    FightOutPokemon* p;
    void* waza;
    u8 level;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    level = (u8)figthOutPokemonGetLevel(p);
    fightWaza_SetDamage(waza, level * ((u16)HSD_Rand() % 11 * 10 + 50) / 100);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_CHIKYUUNAGE(void) {
    FightOutPokemon* p;
    void* waza;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    fightWaza_SetDamage(waza, (u8)figthOutPokemonGetLevel(p));
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_YUBIWOHURU(void) {
    u16 ary[400];
    u8 type;
    FightOutPokemon* atk;
    void* fw;
    u16 dbg;
    u32 i;
    u16 waza;
    u32 n;
    u16 r;
    int z;
    type = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    for (z = 0; z < 400; z++) {
        ary[z] = 0;
    }
    n = 0;
    for (i = 0; i < 0x163; i++) {
        if (i != 0 && (u16)fightSeqCheckYubiwohuruWazaDataId(i) != 0) {
            ary[n] = i;
            n++;
        }
    }
    r = HSD_Rand();
    waza = ary[r % n];
    dbg = dbgMenuFightGetYubiwohuruWazaDataId();
    if (dbg != 0) {
        waza = dbg;
    }
    ServerStatusFlag &= ~0x400;
    fightWazaSetUseWazaStatus(fw, waza);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, fightSeqSelectDefensePokemonPtr(atk, waza, type, 0, 1, 1, -1));
    fightSeq_JumpWazaSeq(WazaEffectTbl[wazaDB_GetSeqId(waza)]);
}
}

extern "C" {
u32 fightSeqCheckYubiwohuruWazaDataId(u16 move_id) {
    u16 entry;
    s32 index;
    if (move_id == 0) {
        return 0;
    }
    if (move_id == 0x176) {
        return 0;
    }
    if (move_id == 0x163) {
        return 0;
    }
    index = 0;
    while (1) {
        entry = YubihuriNGTbl[index];
        if (entry == 0xffff) {
            break;
        }
        if (move_id == entry) {
            break;
        }
        index = index + 1;
    }
    if (entry != 0xffff) {
        return 0;
    }
    return 1;
}
}

extern "C" {
void WS_MONOMANE(void) {
    u8* cmd;
    FightOutPokemon* atk;
    void* fw;
    void* pk;
    u16 waza;
    s8 slot;
    FightOutPokemon* def;
    u8 pp;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    waza = fightOutPokemon_GetLastSelectWazaDataId(def);
    fightWaza_SetMotoWazaDataId(fw, 0xFFFF);
    if (!((u16)fightOutPokemonIsJoutaiDataId(atk, 0x10) == 1 || (u16)fightSeqMonomaneNGCheck(waza) != 0 || waza == 0 || waza == 0xFFFF || waza == 0x176 || waza == 0x163)) {
        if (pokemonSearchWazaDataId(fightOutPokemonGetPokemonPtr(atk), waza) < 0) {
            slot = fightWaza_GetWazaBanme(fw);
            if (slot >= 0 && ((u16)fightOutPokemonIsUseHensinBuff(atk) != 0 || (u16)fightOutPokemonUseHensinBuff(atk) != 0)) {
                if ((u16)fightOutPokemonIsJoutaiDataId(atk, 0x31) == 0) {
                    fightOutPokemonWriteJoutaiDataId(atk, 0x31, 0);
                }
                pk = fightOutPokemonGetPokemonPtr(atk);
                pokemonWazaCreate(pk, slot, waza);
                pp = wazaDB_GetPp(waza);
                if (pp > 5) {
                    pp = 5;
                }
                pokemon_SetPokemonWazaPp(pk, slot, pp);
                fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(waza)));
                fightOutPokemonSetBuffJoutaiDataId(atk, 0x31, fightOutPokemonGetBuffJoutaiDataId(atk, 0x31) | (1 << slot));
                fightSeq_NextWazaSeq(5);
                return;
            }
        }
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
u32 fightSeqMonomaneNGCheck(u16 id) {
    u16 entry;
    int i;
    if (id == 0) {
        return 1;
    }
    if (id == 0x176) {
        return 1;
    }
    if (id == 0x163) {
        return 1;
    }
    i = 0;
    while ((entry = YubihuriNGTbl[i]) != 0xfffe) {
        if (id == entry) {
            break;
        }
        i = i + 1;
    }
    return (u8)(entry != 0xfffe);
}
}

extern "C" {
void WS_MIGAWARI(void) {
    FightOutPokemon* atk;
    u16 hp;
    void* fw;
    u16 quarter;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    hp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(atk));
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    quarter = fightOutPokemonMaxHpWaruValue(atk, 4);
    if (hp > quarter && fightOutPokemonCheckWriteJoutaiDataId(atk, 0x14) == 2) {
        fightWaza_SetDamage(fw, quarter);
        fightOutPokemonWriteJoutaiDataId(atk, 0x14, 0);
        fightOutPokemonSetBuffJoutaiDataId(atk, 0x14, quarter);
        if (fightOutPokemonIsJoutaiDataId(atk, 0xE) == 1) {
            fightOutPokemonInitJoutaiDataId(atk, 0xE);
        }
        ServerWork[5] = 0;
        ServerStatusFlag |= 0x100;
    } else {
        fightWaza_SetDamage(fw, 0);
        ServerWork[5] = 1;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HENSHIN(void) {
    FightOutPokemon* atk;
    void* fw;
    FightOutPokemon* def;
    u32 rnd;
    u32 crnd;
    s32* cur;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    rnd = pokemon_GetRnd(fightOutPokemonGetPokemonPtr(def));
    crnd = pokemon_GetCatchTrainerRnd(fightOutPokemonGetPokemonPtr(def));
    fightWaza_SetMotoWazaDataId(fw, 0xFFFF);
    if (fightOutPokemonIsJoutaiDataId(def, 0x10) == 1 || fightOutPokemonIsJoutaiKie(def) != 0 ||
        pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(def)) == 1) {
    failed:
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x45);
        ServerWork[5] = 1;
        fightSeq_NextWazaSeq(1);
        return;
    }
    if (fightOutPokemonIsUseHensinBuff(atk) == 0 && fightOutPokemonUseHensinBuff(atk) == 0) {
        goto failed;
    }
    if (fightOutPokemonIsJoutaiDataId(atk, 0x10) == 0) {
        fightOutPokemonWriteJoutaiDataId(atk, 0x10, 0);
    }
    fightOutPokemonSetBuffJoutaiDataId(atk, 0x10, rnd);
    fightOutPokemonSetKaisuuJoutaiDataId(atk, 0x10, (s8)(u8)crnd);
    fightOutPokemonSetNowKaisuuJoutaiDataId(atk, 0x10, (s8)(u8)(crnd >> 8));
    fightOutPokemonSetIdBuffJoutaiDataId(atk, 0x10, (u16)(crnd >> 16));
    if (fightOutPokemonIsJoutaiDataId(atk, 0x29) == 1) {
        fightOutPokemonInitJoutaiDataId(atk, 0x29);
    }
    if (fightOutPokemonIsJoutaiDataId(atk, 0x31) == 1) {
        fightOutPokemonInitJoutaiDataId(atk, 0x31);
    }
    fightMsgctrlSetValue(0xD, (u32)fightOutPokemonGetNamePtr(def));
    ServerWork[5] = 0;
    fightOutPokemonCopyHensinStatus(def, atk);
    cur = (s32*)fightOutPokemon_GetWazaMenuCurPtr(atk);
    if (cur != 0) {
        *cur = 0;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KIAIDAME(void) {
    FightOutPokemon* p;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0xf) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x45);
        ServerWork[5] = 1;
    } else {
        fightOutPokemonWriteJoutaiDataId(p, 0xf, 0);
        ServerWork[5] = 0;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_SHIROIKIRI(void) {
    void* side;
    FightOutPokemon* p;
    fightSeq_GetWazaSeq();
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(2, (u32)p);
    if (fightSideCheckWriteJoutaiDataId(side, 0x4c) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x45);
        ServerWork[5] = 1;
    } else {
        fightSideWriteJoutaiDataId(side, 0x4c, 0);
        ServerWork[5] = 0;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_CONDITION_GAUGE(void) {
    u8 fightType = fightFloor_GetFightType(0);
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(cmd[1], 0);
    if (p) {
        fightMenuFightOutPokemonRenewStatusMenu(p, fightType, 1);
    }
    fightSeq_NextWazaSeq(2);
}
}

extern "C" {
void WS_MEROMERO(void) {
    u8* cmd;
    FightOutPokemon* atk;
    FightOutPokemon* def;
    u32 tid;
    u8 atkSex;
    u8 defSex;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    atkSex = fightOutPokemonGetSex(atk);
    tid = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(atk, fightFloor_GetFightType(0));
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    defSex = fightOutPokemonGetSex(def);
    if ((u16)fightOutPokemonGetTokuseiDataId(def) == 0xC) {
        fightSeq_JumpWazaSeq(WAZA_Donkan);
        return;
    }
    if (atkSex == defSex || fightOutPokemonCheckWriteJoutaiDataId(def, 0xA) != 2 || atkSex == 2 || defSex == 2) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(def, 0xA, tid);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_WEATHER_KEEP(void) {
    u16 tok;
    u16 dmg;
    u8 weather;
    void* pk;
    void* fw;
    FightOutPokemon* atk;
    dmg = 0;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    tok = fightOutPokemonGetTokuseiDataId(atk);
    pk = fightOutPokemonGetPokemonPtr(atk);
    weather = fightFloorGetNowTenkouDataId(0, 1);
    if (fightOutPokemonCheckFightOut(atk) == 0) {
        dmg = 0;
    } else {
        if (weather == 3) {
            if (fightOutPokemonIsZokuseiDataId(atk, 5) == 0 && fightOutPokemonIsZokuseiDataId(atk, 8) == 0 && fightOutPokemonIsZokuseiDataId(atk, 4) == 0 && tok != 8 && fightOutPokemonIsJoutaiDataId(atk, 0x20) == 0 && fightOutPokemonIsJoutaiDataId(atk, 0x21) == 0) {
                dmg = fightOutPokemonMaxHpWaruValue(atk, 0x10);
            } else {
                dmg = 0;
            }
        }
        if (weather == 4) {
            if (fightOutPokemonIsZokuseiDataId(atk, 0xF) == 0 && fightOutPokemonIsJoutaiDataId(atk, 0x20) == 0 && fightOutPokemonIsJoutaiDataId(atk, 0x21) == 0) {
                dmg = fightOutPokemonMaxHpWaruValue(atk, 0x10);
            } else {
                dmg = 0;
            }
        }
        if (weather == 5) {
            if (pokemonIsDarkPokemon(pk) == 0 && fightOutPokemonIsJoutaiDataId(atk, 0x20) == 0 && fightOutPokemonIsJoutaiDataId(atk, 0x21) == 0) {
                dmg = fightOutPokemonMaxHpWaruValue(atk, 0x10);
            } else {
                dmg = 0;
            }
        }
    }
    fightWaza_SetDamage(fw, dmg);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_WEATHER_CHANGE(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    if (fightFloorCheckWriteJoutaiDataId(0, cmd[1]) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork[5] = 2;
    } else {
        fightFloorWriteJoutaiDataId(0, cmd[1], 0);
        ServerWork[5] = cmd[2];
    }
    fightSeq_NextWazaSeq(3);
}
}

extern "C" {
void WS_HPHALF(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    u32 move = fightOutPokemon_GetUseWazaDataId(p);
    FightOutPokemon* d; 
    void* waza; 
    waza = fightOutPokemon_GetFightWazaPtr(p);
    d = fightTargetGetPtrAsNowFightType(0x12, 0);
    u32 a = fightOutPokemonNowHpWaruValue(d, 1);
    s32 b = fightOutPokemonNowHpWaruValue(d, 2) & 0xffff;
    if ((u16)move == 0x175 && (u16)a == b) {
        b = 0;
    }
    fightWaza_SetDamage(waza, b);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_ICHIGEKI(void) {
    u8* cmd;
    FightOutPokemon* atk;
    FightOutPokemon* def;
    u32 tid;
    u32 waza;
    void* fw;
    u8 alv;
    u32 dlv;
    u32 item;
    u16 soubi;
    s32 buff;
    u16 hp;
    u32 tok;
    u16 hit;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    tid = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(atk, fightFloor_GetFightType(0));
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    alv = figthOutPokemonGetLevel(atk);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    item = fightOutPokemonGetSoubiItemDataId(atk);
    soubi = fightOutPokemonGetSoubiItemSoubiDataId(def);
    buff = figthOutPokemonGetSoubiItemBuff(def);
    hp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(def));
    tok = fightOutPokemonGetTokuseiDataId(def);
    dlv = figthOutPokemonGetLevel(def);
    fightFloor_SetItemPokemonPtr(0, def);
    if (soubi == 0x27 && (s32)(HSD_Rand() % 100) < buff) {
        fightOutPokemon_SetItemKoraetaFlag(def, 1);
    }
    if (tok == 5) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeq_JumpWazaSeq(WAZA_Ganzyou);
        return;
    }
    if ((s16)fightOutPokemonIsJoutaiDataId(def, 0x1D) == 1 && tid == fightOutPokemonGetUserFightTargetIdJoutaiDataId(def, 0x1D)) {
        if (alv >= dlv) {
            hit = 1;
        } else {
            hit = 0;
        }
    } else {
        if ((s32)((HSD_Rand() % 100) + 1) < (s32)(u16)((alv - dlv) + (u8)(wazaDB_GetAvg(waza))) && alv >= dlv) {
            hit = 1;
        } else {
            hit = 0;
        }
    }
    if (hit != 0) {
        if (fightOutPokemonIsJoutaiDataId(def, 0x2C) != 0) {
            fightWaza_SetDamage(fw, hp - 1);
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x46);
        } else if (fightOutPokemon_GetItemKoraetaFlag(def) != 0) {
            fightWaza_SetDamage(fw, hp - 1);
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x47);
            fightFloor_SetAppointItemDataId(0, item);
        } else {
            fightWaza_SetDamage(fw, hp);
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x44);
        }
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
    if (alv >= dlv) {
        ServerWork[5] = 0;
    } else {
        ServerWork[5] = 1;
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
void WS_HIKARINOKABE(void) {
    FightOutPokemon* atk;
    void* side;
    u16 cnt;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(2, (u32)atk);
    cnt = fightFloorGetValidFightOutPokemonCount(0, 1, atk, 1);
    if (fightSideCheckWriteJoutaiDataId(side, 0x49) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork[5] = 0;
    } else {
        fightSideWriteJoutaiDataId(side, 0x49, 0);
        if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && cnt >= 2) {
            ServerWork[5] = 4;
        } else {
            ServerWork[5] = 3;
        }
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KOBAN_CHECK(void) {
    fightSeq_GetWazaSeq();
    if (fightFloor_GetFightKindGetNekoniKobanFlag(0) == 1) {
        u32 amount;
        void* t = fightFloorGetGcHeroFightTrainerPtr(0);
        if (t) {
            u32 koban = fightTrainer_GetKoban(t);
            if (koban) {
                amount = koban;
                amount *= fightTrainer_GetOkaneBai(t);
                void* hero = fightTrainer_GetHeroPtr(t);
                if (hero) {
                    heroAddPokedoru(hero, amount);
                    fightMsgctrlSetValue(0x2f, amount);
                    fightMsgctrlSetValue(0x13, heroGetStatus(hero, 1, 0));
                    fightSeq_CallWazaSeq(WAZA_Nekonikoban);
                }
            }
        }
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_TEXTURE(void) {
    s32 ary[4];
    u8* cmd;
    FightOutPokemon* atk;
    s32 n;
    s32 pick;
    u8 i;
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    n = fightSeqGetTextureZokuseiAry(atk, ary);
    if (n != 0) {
        pick = ary[HSD_Rand() % n];
        if (pick >= 0) {
            for (i = 0; i < 2; i++) {
                fightOutPokemonSetZokuseiDataId(atk, i, (u16)pick);
            }
            fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(zokuseiBiosGetName(pick)));
            fightSeq_NextWazaSeq(5);
            return;
        }
    }
    fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
}
}

extern "C" {
s32 fightSeqGetTextureZokuseiAry(FightOutPokemon* p, s32* ary) {
    u32 waza;
    void* pk;
    u32 count;
    u32 zok;
    int i;

    pk = fightOutPokemonGetPokemonPtr(p);
    for (i = 0; (u8)i < 4; i++) {
        ary[(u8)i] = -1;
    }
    count = 0;
    for (i = 0; (u8)i < 4; i++) {
        u8 slot = i;
        if (pokemonWazaCheckValid(pk, slot) == 1) {
            waza = pokemon_GetPokemonWazaDataId(pk, slot);
            if ((u16)waza != 0xA5 && wazaCheckDarkWaza(waza) != 1) {
                zok = wazaDB_GetZokuseiDataId(waza);
                if (zok == 9) {
                    if (fightOutPokemonIsZokuseiDataId(p, 7) == 1) {
                        zok = 7;
                    } else {
                        zok = 0;
                    }
                }
                if (fightOutPokemonIsZokuseiDataId(p, zok) == 0) {
                    count++;
                    ary[count & 0xFF] = zok;
                }
            }
        }
    }
    return count;
}
}

extern "C" {
void WS_HUKITOBASHI(void) {
    void* ary[8];
    s32 id;
    u8* cmd;
    FightOutPokemon* atk;
    FightOutPokemon* def;
    u16 n;
    void* enc;
    u32 dc_oor_GetEncountDataId = fightFloor_GetEncountDataId(0);
    dc_oor_GetEncountDataId;
    enc = fightEncountDataBiosGetPtr(dc_oor_GetEncountDataId);
    cmd = (u8*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    n = fightTrainerGetIrekaeFightPokemonAry(fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, def), ary);
    if (fightEncountDataBiosGetFightKind(enc) == 0xC) {
        fightFloorSetFightResultId(0, 2);
        fightSeq_JumpWazaSeq(WAZA_HukitobashiFightEnd);
        return;
    }
    if (n == 0) {
        fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        return;
    }
    if (_fightSeqHukitobashiCheck(atk, def, (u32)((WsJumpCmd*)cmd)->jump) != 0) {
        if (ary[HSD_Rand() % n] != 0 && (id = fightPokemon_GetEntryId(ary[HSD_Rand() % n]), id >= 0)) {
            fightFloor_SetIrekaePokemonPtr(0, def);
            fightOutPokemon_SetIrekaeTargetEntryId(def, id);
            fightOutPokemon_SetIrekaetaFlag(def, 1);
        } else {
            fightSeq_JumpWazaSeq(*(void**)(cmd + 1));
        }
    }
}
}

static u8 _fightSeqHukitobashiCheck(FightOutPokemon* a, FightOutPokemon* b, u32 jump) {
    enum TsE { TsE0 };
    enum TsE la;
    u8 lb;
    la = (enum TsE)(figthOutPokemonGetLevel(a));
    lb = figthOutPokemonGetLevel(b);
    if (la < lb) {
        if ((s32)(u16)((((la + lb) * HSD_Rand()) >> 8) + 1) <= (lb >> 2)) {
            fightSeq_JumpWazaSeq((void*)jump);
            return 0;
        }
    }
    fightSeq_JumpWazaSeq(WAZA_Hukitobashi);
    return 1;
}

extern "C" {
void WS_RENZOKU_NUM_INIT(void) {
    fightSeq_GetWazaSeq();
    fight_seq_renzoku_count = 0;
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_RENZOKU(void) {
    void* waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    u8 n = cmd[1];
    if (n != 0) {
        fightWaza_SetKaisuu(waza, n);
    } else {
        n = (u16)HSD_Rand() % 4;
        if (n < 2) {
            n += 2;
        } else {
            n = 2;
            n += (u16)HSD_Rand() % 4;
        }
        fightWaza_SetKaisuu(waza, n);
    }
    fightSeq_NextWazaSeq(2);
}
}

extern "C" {
void WS_ABARERU(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0xd) == 2) {
        ServerWork[3] = 0x75;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_GAMAN(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    void* waza = fightOutPokemon_GetFightWazaPtr(p);
    void* keep = fightOutPokemon_GetKeepFightWazaPtr(p);
    if (fightOutPokemonCheckWriteJoutaiDataId(p, 0xc) == 2) {
        fightOutPokemonWriteJoutaiDataId(p, 0xc, 0);
        fightOutPokemonWriteJoutaiDataId(p, 0x22, 0);
    }
    fightWazaBiosCopy(keep, waza);
    fightOutPokemon_SetGamanDamageValue(p, 0);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KUROIKIRI(void) {
    fightSeq_GetWazaSeq();
    fightFloorLoopValidFightOutPokemon(0, _fightSeqWsKuroikiriSub, 0, 0);
    fightSeq_NextWazaSeq(1);
}
}

static s32 _fightSeqWsKuroikiriSub(void* pokemon, u16 id, void* user) {
    FightOutPokemon* p = (FightOutPokemon*)pokemon;
    if (!fightOutPokemonCheckFightOut(p)) {
        return 0;
    }
    fightOutPokemonInitAbiCntAll(p);
    return 1;
}

extern "C" {
void WS_CONDCHG(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    u8 packed = UserWork[0x1601e];
    if (!fightSeqCondChgAct(packed & 0xf0, packed & 0xf, cmd[1], *(void**)(cmd + 2))) {
        fightSeq_NextWazaSeq(6);
    }
}
}

extern "C" {
u8 fightSeqCondChgAct(u8 paraId, u8 type, s32 flags, void* jump) {
    u8 a = 0;
    u8 b = 0;
    u8 side;
    FightOutPokemon* p;
    void* sidePtr;
    u32 tokusei;
    u32 move;
    u16 statusId;
    s8 cur;
    s8 delta;
    if (flags & 0x40) {
        side = 0;
        p = fightTargetGetPtrAsNowFightType(0x11, 0);
    } else {
        side = 1;
        p = fightTargetGetPtrAsNowFightType(0x12, 0);
    }
    sidePtr = fightTargetGetPtrAsNowFightType(2, (u32)p);
    tokusei = fightOutPokemonGetTokuseiDataId(p);
    move = fightOutPokemon_GetUseWazaDataId(p);
    if (((u8)flags & 0xbf) & 0x80) {
        a = 1;
    }
    if ((u8)flags & 0x20) {
        b = 1;
    }
    statusId = fightSeqCondChgActTypeToPokemonStatusId(type);
    cur = pokemonGetStatus(p, 0, statusId, 0);
    fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar((void*)AbiCntMsgTbl[type]));
    delta = fightSeqCondChgActParaIdToValue(paraId);
    if (delta < 0) {
        if (fightSideIsJoutaiDataId(sidePtr, 0x4c) == 1 && !a && (u16)move != 0xae) {
            if (((u8)flags & 0x1f) == 1) {
                if (fightOutPokemon_GetDoClearbodyFlag(p)) {
                    fightSeq_JumpWazaSeq(jump);
                } else {
                    fightFloor_SetAppointPokemonPtr(0, p);
                    fightOutPokemon_SetDoClearbodyFlag(p, 1);
                    fightSeq_CallWazaSeq(WAZA_Shiroikiri);
                    fightSeq_JumpWazaSeq(jump);
                }
            }
            return 1;
        }
        if ((u16)move != 0xae && b != 1 && fightSeqGuardCheck(0, 0)) {
            fightSeq_JumpWazaSeq(WAZA_Umakukimaran);
            return 1;
        }
        if (((u16)tokusei == 0x1d || (u16)tokusei == 0x49) && !a && (u16)move != 0xae) {
            if (((u8)flags & 0x1f) == 1) {
                if (fightOutPokemon_GetDoClearbodyFlag(p)) {
                    fightSeq_JumpWazaSeq(jump);
                } else {
                    fightFloor_SetAppointPokemonPtr(0, p);
                    fightOutPokemon_SetDoClearbodyFlag(p, 1);
                    if (!fightFloorIsNowEncountOpeningVirtualBattle(0)) {
                        fightSeq_CallWazaSeq(WAZA_ClearBody);
                        fightSeq_JumpWazaSeq(jump);
                    }
                }
            }
            return 1;
        }
        if ((u16)tokusei == 0x33 && !a && statusId == 0xeb) {
            if (((u8)flags & 0x1f) == 1) {
                fightFloor_SetAppointPokemonPtr(0, p);
                fightSeq_CallWazaSeq(WAZA_Kairikibasami);
                fightSeq_JumpWazaSeq(jump);
            }
            return 1;
        }
        if ((u16)tokusei == 0x34 && !a && statusId == 0xe6) {
            if (((u8)flags & 0x1f) == 1) {
                fightFloor_SetAppointPokemonPtr(0, p);
                fightSeq_CallWazaSeq(WAZA_Kairikibasami);
                fightSeq_JumpWazaSeq(jump);
            }
            return 1;
        }
        if ((u16)tokusei == 0x13 && !((u8)flags & 0x1f)) {
            return 1;
        }
        if (delta <= -2) {
            fightMsgctrlSetValue(0xe, (u32)GSmsgGetGSchar((void*)0x4f11));
        } else {
            fightMsgctrlSetValue(0xe, (u32)GSmsgGetGSchar((void*)0x4f9c));
        }
        fightMsgctrlSetValue(0x41, (u32)GSmsgGetGSchar((void*)0x4f12));
        if (cur <= 0) {
            ServerWork[5] = 2;
        } else {
            ServerWork[5] = side;
        }
    } else {
        if (delta >= 2) {
            fightMsgctrlSetValue(0xe, (u32)GSmsgGetGSchar((void*)0x4f0f));
        } else {
            fightMsgctrlSetValue(0xe, (u32)GSmsgGetGSchar((void*)0x4f9c));
        }
        fightMsgctrlSetValue(0x41, (u32)GSmsgGetGSchar((void*)0x4f10));
        if (cur >= 0xc) {
            ServerWork[5] = 2;
        } else {
            ServerWork[5] = side;
        }
    }
    cur += delta;
    if (cur < 0) {
        cur = 0;
    }
    if (cur > 0xc) {
        cur = 0xc;
    }
    pokemonSetStatus(p, 0, statusId, 0, cur);
    if (ServerWork[5] == 2 && ((u8)flags & 1)) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
    }
    if (ServerWork[5] == 2 && !((u8)flags & 1)) {
        return 1;
    }
    return 0;
}
}

extern "C" {
s32 fightSeqCondChgActParaIdToValue(u8 para_id) {
    switch (para_id) {
    case 0x10:
        return 1;
    case 0x20:
        return 2;
    case 0x90:
        return -1;
    case 0xA0:
        return -2;
    default:
        return 0;
    }
}
}

extern "C" {
s32 fightSeqCondChgActTypeToPokemonStatusId(u8 type) {
    switch (type) {
    case 1:
        return 0xE6;
    case 2:
        return 0xE7;
    case 3:
        return 0xEA;
    case 4:
        return 0xE8;
    case 5:
        return 0xE9;
    case 6:
        return 0xEB;
    case 7:
        return 0xEC;
    default:
        return 0;
    }
}
}

extern "C" {
void WS_SUITORI(void) {
    void* waza;
    s32 d;
    fightSeq_GetWazaSeq();
    waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    fightWaza_GetDamage(waza);
    d = -(fightWaza_GetHitDamage(waza) / 2);
    if (d == 0) {
        d = -1;
    }
    fightWaza_SetDamage(waza, d);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_NOMIKOMU(void) {
    void* fw;
    FightOutPokemon* atk;
    WsJumpCmd* cmd;
    s16 cnt;
    s16 sh;
    cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    if (fightOutPokemonIsJoutaiDataId(atk, 0x2D) == 0) {
        cnt = 0;
    } else {
        cnt = fightOutPokemonGetCountAsJoutaiDataId(atk, 0x2D);
    }
    if (cnt <= 0) {
        ServerWork[5] = 0;
        fightSeq_JumpWazaSeq(cmd->jump);
        return;
    }
    if (fightOutPokemonIsHpMantan(atk) == 1) {
        fightOutPokemonInitJoutaiDataId(atk, 0x2D);
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, atk);
        ServerWork[5] = 1;
        fightSeq_JumpWazaSeq(cmd->jump);
        return;
    }
    sh = joutaiDataBiosGetMaxCount(0x2D) - cnt;
    if (sh < 0) {
        sh = 0;
    }
    fightWaza_SetDamage(fw, -(s32)fightOutPokemonMaxHpWaruValue(atk, (u16)(1 << sh)));
    UserWork[0x16002] = (s8)cnt;
    fightOutPokemonInitJoutaiDataId(atk, 0x2D);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, atk);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_HAKIDASU(void) {
    enum TsE { TsE0 };
    WsJumpCmd* cmd;
    FightOutPokemon* atk;
    void* fw;
    u32 waza;
    s32 power;
    enum TsE zokusei;
    s16 cnt;
    FightOutPokemon* def;
    void* side;
    s32 dmg;
    cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    waza = fightOutPokemon_GetUseWazaDataId(atk);
    power = fightWaza_GetIryoku(fw);
    zokusei = (enum TsE)(fightWaza_GetZokusei(fw));
    if (fightOutPokemonIsJoutaiDataId(atk, 0x2D) == 0) {
        cnt = 0;
    } else {
        cnt = fightOutPokemonGetCountAsJoutaiDataId(atk, 0x2D);
    }
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    side = fightTargetGetPtrAsNowFightType(2, (u32)def);
    if (cnt <= 0) {
        fightSeq_JumpWazaSeq(cmd->jump);
        return;
    }
    if (ServerWork[6] != 1) {
        dmg = cnt * fightSeqWazaDamageCalc(atk, def, (FightOutPokemon*)side, (u8)waza, power, (u8)zokusei);
        UserWork[0x16002] = cnt;
        if (fightOutPokemonIsJoutaiDataId(atk, 0x32) == 1) {
            dmg = (dmg * 15) / 10;
        }
        fightWaza_SetDamage(fw, dmg);
    }
    fightOutPokemonInitJoutaiDataId(atk, 0x2D);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_TAKUWAERU(void) {
    s16 cnt;
    FightOutPokemon* atk;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonIsJoutaiDataId(atk, 0x2D) == 0) {
        cnt = 0;
    } else {
        cnt = fightOutPokemonGetCountAsJoutaiDataId(atk, 0x2D);
    }
    if (cnt == joutaiDataBiosGetMaxCount(0x2D)) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork[5] = 1;
    } else {
        if (fightOutPokemonCheckWriteJoutaiDataId(atk, 0x2D) == 2) {
            fightOutPokemonWriteJoutaiDataId(atk, 0x2D, 0);
        }
        s16 tmp1 = fightOutPokemonGetCountAsJoutaiDataId(atk, 0x2D);
        fightMsgctrlSetValue(0x2F, tmp1);
        ServerWork[5] = 0;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_SAWAGU_CHECK(void) {
    FightOutPokemon* t;
    u32 tokusei;
    void* jump;
    t = fightTargetGetPtrAsNowFightType(0x12, 0);
    tokusei = fightOutPokemonGetTokuseiDataId(t);
    jump = *(void**)((u8*)fightSeq_GetWazaSeq() + 1);
    if (fightSeqSawaguCheck(t)) {
        fightSeq_JumpWazaSeq(jump);
    } else if ((u16)tokusei == 0xf || (u16)tokusei == 0x48) {
        ServerWork[5] = 2;
        fightSeq_JumpWazaSeq(jump);
    } else {
        fightSeq_NextWazaSeq(5);
    }
}
}

extern "C" {
bool fightSeqSawaguCheck(FightOutPokemon* p) {
    return fightFloorLoopValidFightOutPokemon(0, _fightSeqSawaguCheckSub, p, 1) != 1;
}
}

static s32 _fightSeqSawaguCheckSub(void* pokemon, u16 id, void* user) {
    FightOutPokemon* self = (FightOutPokemon*)pokemon;
    FightOutPokemon* target = (FightOutPokemon*)user;
    u32 tokusei = fightOutPokemonGetTokuseiDataId(target);
    if (!fightOutPokemonCheckFightOut(self)) {
        return 1;
    }
    if (fightOutPokemonIsJoutaiDataId(self, 0xb) == 1 && (u16)tokusei != 0x2b) {
        fightFloor_SetAppointPokemonPtr(0, self);
        if (self == target) {
            ServerWork[5] = 0;
        } else {
            ServerWork[5] = 1;
        }
        return 0;
    }
    return 1;
}

extern "C" {
void WS_SAWAGU(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_NEKODAMASHI(void) {
    WsJumpCmd* cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemon_GetFightoutTurnCount(p) != 0) {
        fightSeq_NextWazaSeq(5);
    } else {
        fightSeq_JumpWazaSeq(cmd->jump);
    }
}
}

extern "C" {
void WS_NEMURU(void) {
    WsJumpCmd* cmd = (WsJumpCmd*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    void* waza = fightOutPokemon_GetFightWazaPtr(p);
    fightTargetGetPtrAsNowFightType(0x12, 0);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, p);
    fightWaza_SetDamage(waza, -(u16)fightOutPokemonMaxHpWaruValue(p, 1));
    if (fightOutPokemonIsHpMantan(p) == 1) {
        fightSeq_JumpWazaSeq(cmd->jump);
        return;
    }
    if (fightOutPokemonIsJoutaiDataId(p, 3) == 1 || fightOutPokemonIsJoutaiDataId(p, 4) == 1 ||
        fightOutPokemonIsJoutaiDataId(p, 5) == 1 || fightOutPokemonIsJoutaiDataId(p, 6) == 1 ||
        fightOutPokemonIsJoutaiDataId(p, 7) == 1) {
        ServerWork[5] = 1;
    } else {
        ServerWork[5] = 0;
    }
    fightOutPokemonWriteJoutaiDataId(p, 8, 0);
    fightOutPokemonSetKaisuuJoutaiDataId(p, 8, 3);
    fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x7C);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_DAMAGE_CHG(void) {
    u8* cmd;
    void* fw;
    s32 dmg;
    FightOutPokemon* def;
    void* pk;
    u32 maxHp;
    s32 half;
    cmd = (u8*)fightSeq_GetWazaSeq();
    fw = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    dmg = fightWaza_GetDamage(fw);
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    pk = fightOutPokemonGetPokemonPtr(def);
    maxHp = pokemon_GetMaxHp(pk);
    switch (cmd[1]) {
    case 0:
        dmg *= -1;
        break;
    case 1:
        dmg = dmg / 2;
        if (dmg == 0) {
            dmg = 1;
        }
        half = (s32)maxHp / 2;
        if (half < dmg) {
            dmg = half;
        }
        break;
    case 2:
        dmg *= 2;
        break;
    }
    fightWaza_SetDamage(fw, dmg);
    fightSeq_NextWazaSeq(2);
}
}

extern "C" {
void WS_YADORIGI(void) {
    FightOutPokemon* def;
    FightOutPokemon* atk;
    void* fw;
    u32 tid;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    tid = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(atk, fightFloor_GetFightType(0));
    def = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightWazaIsHit(fw) == 0 || fightOutPokemonCheckWriteJoutaiDataId(def, 0x1C) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork[5] = 1;
        fightSeq_NextWazaSeq(1);
        return;
    }
    if (fightOutPokemonIsZokuseiDataId(def, 0xC) == 1) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork[5] = 2;
        fightSeq_NextWazaSeq(1);
        return;
    }
    fightOutPokemonWriteJoutaiDataId(def, 0x1C, tid);
    ServerWork[5] = 0;
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_REFLEC(void) {
    FightOutPokemon* atk;
    void* side;
    u16 cnt;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(2, (u32)atk);
    cnt = fightFloorGetValidFightOutPokemonCount(0, 1, atk, 1);
    if (fightSideCheckWriteJoutaiDataId(side, 0x48) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork[5] = 0;
    } else {
        fightSideWriteJoutaiDataId(side, 0x48, 0);
        if (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2 && cnt >= 2) {
            ServerWork[5] = 2;
        } else {
            ServerWork[5] = 1;
        }
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_OUMU_CHECK(void) {
    u16 ary[8];
    u8 type;
    FightOutPokemon* atk;
    void* fw;
    u16 waza;
    u16 aw;
    u8 n;
    type = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    waza = fightOutPokemon_GetOumuWazaDataId(atk);
    switch (waza == 0 || waza == 0x176 || waza) {
    case 0xFFFF:
            n = (s32)(fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(atk, ary)) + _fightOutPokemonGetFightOutPokemonAllyOumuWazaDataIdAry(atk);
            if (n == 0 || ((((waza = ary[HSD_Rand() % n]) == 0) || waza == 0x176) && (((aw = fightOutPokemon_GetOumuWazaAllyDataId(atk)), waza = aw, aw == 0) || aw == 0x176))) {
                fightOutPokemon_SetNoPressureFlag(atk, 1);
                fightSeq_NextWazaSeq(1);
                return;
            }
        break;
    }
    fightOutPokemonLoadWazaEffect(atk, 0x77, 1, 0);
    fightOutPokemonWazaEffect(atk, 0x77, 1, 1, (s32)fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
    fightOutPokemonFreeWazaEffect(atk, 0x77, 1);
    ServerStatusFlag &= ~0x400;
    fightWazaSetUseWazaStatus(fw, waza);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, fightSeqSelectDefensePokemonPtr(atk, waza, type, 0, 1, 1, -1));
    fightSeq_JumpWazaSeq(WazaEffectTbl[wazaDB_GetSeqId(waza)]);
}
}

static s32 _fightOutPokemonGetFightOutPokemonAllyOumuWazaDataIdAry(FightOutPokemon* p) {
    u16 w;
    w = fightOutPokemon_GetOumuWazaAllyDataId(p);
    if (w != 0 && w != 0x176) {
        return 1;
    }
    return 0;
}

extern "C" {
void WS_KAIFUKU(void) {
    u8* cmd = (u8*)fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    void* waza = fightOutPokemon_GetFightWazaPtr(p);
    FightOutPokemon* t = fightTargetGetPtrAsNowFightType(0x12, 0);
    void* jump = *(void**)(cmd + 1);
    if (cmd[5] == 0x11) {
        t = p;
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, p);
    }
    fightWaza_SetDamage(waza, -(u16)fightOutPokemonMaxHpWaruValue(t, 2));
    if (fightOutPokemonIsHpMantan(t) == 1) {
        fightSeq_JumpWazaSeq(jump);
    } else {
        fightSeq_NextWazaSeq(6);
    }
}
}

extern "C" {
void WS_JIBAKU_LOOP(void) {
    FightOutPokemon* atk;
    FightOutPokemon* p;
    FightOutPokemon* found;
    void* jump;
    u8 mode;
    u8* cmd;
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    cmd = (u8*)fightSeq_GetWazaSeq();
    found = 0;
    mode = cmd[5];
    jump = *(void**)(cmd + 1);
    fight_seq_banme_buff += 1;
    for (; fight_seq_banme_buff < fight_seq_banme_max; fight_seq_banme_buff++) {
        p = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData(fight_seq_banme_buff);
        if (p != 0 && fightOutPokemonCheckFightOut(p) != 0 && (mode != 1 || atk != p)) {
            found = p;
            break;
        }
    }
    if (found != 0) {
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, found);
        fightSeq_JumpWazaSeq(jump);
        return;
    }
    fightSeq_NextWazaSeq(6);
}
}

extern "C" {
void WS_JIBAKU(void) {
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    fightSeq_GetWazaSeq();
    pokemon_SetHp(fightOutPokemonGetPokemonPtr(p), 0);
    fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x83);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_JIBAKU_INIT(void) {
    u8 type;
    void* fw;
    FightOutPokemon* atk;
    FightOutPokemon* found;
    FightOutPokemon* p;
    s32 menu;
    FightOutPokemon* r;
    type = fightFloor_GetFightType(0);
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    fw = fightOutPokemon_GetFightWazaPtr(atk);
    menu = fightMenuGetFightOutPokemonPtrToStatusMenuId(atk, type, true);
    switch (((u8*)fightSeq_GetWazaSeq())[1]) {
    case 1:
        r = (FightOutPokemon*)fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(0, 6, 0, 0, 0);
        if (r == 0) {
            fightWaza_SetDamage(fw, pokemon_GetHp(fightOutPokemonGetPokemonPtr(atk)));
            menuFightStatusSetHP(menu, 0);
            fight_seq_banme_max = 8;
            found = 0;
            fight_seq_banme_buff = 0;
            for (; fight_seq_banme_buff < fight_seq_banme_max; fight_seq_banme_buff++) {
                p = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData(fight_seq_banme_buff);
                if (p != 0 && fightOutPokemonCheckFightOut(p) != 0 && atk != p) {
                    found = p;
                    break;
                }
            }
            if (found != 0) {
                fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, found);
            }
            fightSeq_NextWazaSeq(2);
            return;
        }
        fightFloor_SetDefensePokemonPtr(0, r);
        fightSeq_JumpWazaSeq(WAZA_Shimerike);
        return;
    case 0:
        fight_seq_banme_max = 8;
        found = 0;
        fight_seq_banme_buff = 0;
        for (; fight_seq_banme_buff < fight_seq_banme_max; fight_seq_banme_buff++) {
            p = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData(fight_seq_banme_buff);
            if (p != 0 && fightOutPokemonCheckFightOut(p) != 0) {
                found = p;
                break;
            }
        }
        if (found != 0) {
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, found);
        }
        fightSeq_NextWazaSeq(2);
        return;
    }
}
}

extern "C" {
void WS_GUARD_SUCCESS_CHECK(void) {
    enum TsE { TsE0 };
    u8 ok;
    FightOutPokemon* atk;
    enum TsE seq;
    u16 last;
    s32 cnt;
    u8 next;
    ok = 1;
    fightSeq_GetWazaSeq();
    atk = fightTargetGetPtrAsNowFightType(0x11, 0);
    seq = (enum TsE)(wazaDB_GetSeqId(fightOutPokemon_GetUseWazaDataId(atk)));
    last = fightOutPokemon_GetLastUseWazaDataId(atk);
    cnt = fightOutPokemon_GetSuccessCnt(atk);
    if (last != 0xB6 && last != 0xC5 && last != 0xCB) {
        cnt = 0;
        fightOutPokemon_SetSuccessCnt(atk, 0);
    }
    if (fightFloorIsLastActionFightOutPokemon(0) == 1) {
        ok = 0;
    }
    if (KakuritsuTable[cnt] > HSD_Rand() && ok != 0) {
        if (seq == 0x6F) {
            if (fightOutPokemonCheckWriteJoutaiDataId(atk, 0x2B) == 2) {
                fightOutPokemonWriteJoutaiDataId(atk, 0x2B, 0);
            }
            ServerWork[5] = 0;
        }
        if (seq == 0x74) {
            if (fightOutPokemonCheckWriteJoutaiDataId(atk, 0x2C) == 2) {
                fightOutPokemonWriteJoutaiDataId(atk, 0x2C, 0);
            }
            ServerWork[5] = 1;
        }
        next = cnt + 1;
        if (next > 3) {
            next = 3;
        }
        fightOutPokemon_SetSuccessCnt(atk, next);
    } else {
        fightOutPokemon_SetSuccessCnt(atk, 0);
        ServerWork[5] = 2;
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
    }
    fightSeq_NextWazaSeq(1);
}
}

