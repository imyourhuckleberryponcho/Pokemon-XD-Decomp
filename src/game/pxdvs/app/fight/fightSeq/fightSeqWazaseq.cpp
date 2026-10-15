// WIP: being decompiled (Colosseum shared-function batch).
#include <dolphin/types.h>

#pragma optimize_for_size on

struct FightOutPokemon;

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
u32 pokemon_GetPokemonWazaDataId(void*, s32);
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
u8 fightSeqRendouWazaCheck(u16);
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
FightOutPokemon* fightTargetGetRelativeHostSideFightTargetIdTo(u32, u32);
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
u8 pokemon_GetFriend(void*);
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
    u8 zokusei;
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
void WS_KETAGURI(void) {
    void* waza;
    fightSeq_GetWazaSeq();
    waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    fightWaza_SetIryoku(waza, fightSeqGetKetaguriIryoku(pokemonDB_GetWeight(figthOutPokemonGetPokemonDataId(fightTargetGetPtrAsNowFightType(0x12, 0)))));
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
    WsHuuinCtx* ctx = (WsHuuinCtx*)user;
    FightOutPokemon* target = (FightOutPokemon*)pokemon;
    FightOutPokemon* p = ctx->p;
    void* pk1;
    void* pk2;
    s8 i;
    if (!fightOutPokemonCheckFightOut(target)) {
        return 1;
    }
    if (fightOutPokemonIsAlly(target, p) == 1) {
        return 1;
    }
    pk1 = fightOutPokemonGetPokemonPtr(p);
    pk2 = fightOutPokemonGetPokemonPtr(target);
    for (i = 0; i < 4; i++) {
        s8 slot = i;
        if (pokemonWazaCheckValid(pk1, slot)) {
            if (pokemonSearchWazaDataId(pk2, pokemon_GetPokemonWazaDataId(pk1, slot)) >= 0) {
                ctx->flag = 1;
                return 0;
            }
        }
    }
    return 1;
}

extern "C" {
void WS_HUNKA(void) {
    u16 hp;
    u16 iryoku;
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
    hpA = (u16)pokemon_GetHp(fightOutPokemonGetPokemonPtr(p));
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
s32 fightSeqGetHukuroDatakiDamage(u32 wazaId, u32 atkMon, u16 level, u32 defMon) {
    s32 dmg = (u16)pokemonDB_GetBasisPhyAtk(atkMon);
    s32 def;
    dmg = dmg * (u16)wazaDB_GetIryoku(wazaId) * ((level * 2) / 5 + 2);
    def = (u16)pokemonDB_GetBasisPhyDef(defMon);
    if (def <= 0) {
        def = 1;
    }
    return dmg / def / 50 + 2;
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
void WS_JIKOANJI(void) {
    fightSeq_GetWazaSeq();
    FightOutPokemon* a = fightTargetGetPtrAsNowFightType(0x11, 0);
    FightOutPokemon* b = fightTargetGetPtrAsNowFightType(0x12, 0);
    fightOutPokemonCopyAllAbiCnt(a, b);
    fightSeq_NextWazaSeq(5);
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
void WS_NATSUKI(void) {
    FightOutPokemon* p;
    void* pk;
    void* waza;
    u32 seq;
    u16 power;
    u8 fr;
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
void WS_JITABATA(void) {
    void* waza;
    void* pk;
    u16 hp;
    u8 n;
    fightSeq_GetWazaSeq();
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    pk = fightOutPokemonGetPokemonPtr(p);
    hp = pokemon_GetHp(pk);
    n = fightSeqGetJitabataIryoku(hp, pokemon_GetMaxHp(pk));
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
        id = pokemon_GetPokemonWazaDataId(pk, (u16)sel);
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
u8 fightSeqRendouWazaCheck(u16 id) {
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

extern "C" {
s32 fightSeqIsEncoreNgWazaDataId(u16 move) {
    if (move == 0xa5 || move == 0xe3 || move == 0x77 || move == 0xffff) {
        return 1;
    }
    return 0;
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
    u8 fightType;
    FightOutPokemon* p;
    void* waza;
    u16 atk;
    s16 val;
    FightOutPokemon* t;
    FightOutPokemon* d;
    fightType = fightFloor_GetFightType(0);
    p = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(p);
    atk = pokemonGetStatus(p, 0, idA, 0);
    val = pokemonGetStatus(p, 0, idB, 0);
    if (atk != 0 && val != 0 && (t = fightTargetGetRelativeHostSideFightTargetIdTo(atk, fightType)) != 0 && !fightOutPokemonIsAlly(p, t) &&
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
    s32 level;
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
void WS_KOBAN_CHECK(void) {
    fightSeq_GetWazaSeq();
    if (fightFloor_GetFightKindGetNekoniKobanFlag(0) == 1) {
        void* t = fightFloorGetGcHeroFightTrainerPtr(0);
        if (t) {
            u32 koban = fightTrainer_GetKoban(t);
            if (koban) {
                u32 amount = koban;
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
            n = (u16)HSD_Rand() % 4 + 2;
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
void WS_JIBAKU(void) {
    FightOutPokemon* p = fightTargetGetPtrAsNowFightType(0x11, 0);
    fightSeq_GetWazaSeq();
    pokemon_SetHp(fightOutPokemonGetPokemonPtr(p), 0);
    fightSeqCheckSetHensinBuffToMotoPokemon(p, 0x83);
    fightSeq_NextWazaSeq(1);
}
}

