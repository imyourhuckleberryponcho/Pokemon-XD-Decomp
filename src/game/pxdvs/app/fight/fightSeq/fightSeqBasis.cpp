// WIP: only the shared-with-Colosseum helpers of this unit are reconstructed so far.
#include <dolphin/types.h>

#pragma optimize_for_size on

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
struct WsConditionCmd {
    u8 opcode;
    u8 side;
    u32 kind;
    void* jump;
};
#pragma pack(pop)

extern "C" {

extern u8 ActionSeqNo;

void* fightSeq_GetWazaSeq(void);
void fightSeq_NextWazaSeq(s32 size);
void fightSeq_JumpWazaSeq(void* target);
void fightSeqTuikaAct(u32, u32);
void fightSeqDamageLoss(u32, u32);
void fightSeqTypeCheck(u32, u32, u32, u32, u32);
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
u32 fightOutPokemon_GetUseWazaDataId(FightOutPokemon*);
u32 figthOutPokemonGetPokemonDataId(FightOutPokemon*);
u16 wazaDB_GetSeqId(u32);
extern s32 fight_waza_critical_data_number;
u8 fightFloor_GetFightKindDoCriticalAttackFlag(u32);
void* fightWazaCriticalDataBiosGetPtr(u32);
u8 fightWazaCriticalDataBiosGetBunbo(void*);
void fightWaza_SetCritical(void*, u32);

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

void WS_TYPE_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeqTypeCheck(1, 1, 1, 0, 1);
}

int _WsWkcActSubJoutaiMigawari(void* pokemon, u16 id, void* user);

}

int _WsWkcActSubJoutaiMigawari(void* pokemon, u16 id, void* user) {
    FightOutPokemon* p = (FightOutPokemon*)pokemon;
    if (fightOutPokemonIsJoutaiDataId(p, 0x14) == 1 && fightOutPokemonGetJoutaiMigawariHp(p) <= 0) {
        fightOutPokemonInitJoutaiDataId(p, 0x14);
    }
    return 1;
}

extern "C" {

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
    u32 finalScore;
    u32 move209Bonus;
    u32 move209Status;
    u8 itemSpeciesBonus2;
    u8 itemSpeciesBonus1;
    u32 move43Bonus;
    u32 item;
    FightOutPokemon* attacker;
    FightOutPokemon* target;
    u32 item41Bonus;
    u32 maximum;
    u32 maximumTemp;
    u16 random;
    void* waza;
    u32 move;
    u32 denominator;

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
        if ((u16)item == 0x3f && (u16)species == 0x71) {
            itemSpeciesBonus1 = 1;
        }
        itemSpeciesBonus2 = 0;
        if ((u16)item == 0x42 && (u16)species == 0x53) {
            itemSpeciesBonus2 = 1;
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
    if (finalScore > maximum) {
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

}
