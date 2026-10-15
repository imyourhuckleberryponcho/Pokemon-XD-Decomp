#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemonBios.hpp>
#include <game/pxdvs/app/pokemon/pokemonDB.hpp>
#include <game/pxdvs/GSAPI/GSflag/GSflag.h>

struct FightJoutai {
    u8 data[0x10];
};
struct FightWaza {
    u8 data[0xAC];
};
struct FightItem {
    u8 data[0xC];
};
struct FightAction {
    u8 data[0x30];
};
struct WazaMenuCur {
    u8 data[4];
};
struct FightOutPokemonEnemy {
    u8 data[0xC];
};
struct Sequence;
struct FightOutPokemon;

extern "C" {
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon* fop);
void fightWaza_SetHitDamage(FightWaza*, s32);
void fightWaza_SetTargetDataId(FightWaza*, u16);
void fightWaza_SetIryoku(FightWaza*, u16);
void fightWaza_SetDamage(FightWaza*, s32);
void fightWaza_SetCritical(FightWaza*, u8);
void fightWaza_SetDamageValue(FightWaza*, u8);
void fightWaza_SetMotoWazaDataId(FightWaza*, u16);
void fightWaza_SetUseWazaDataId(FightWaza*, u16);
s32 fightWaza_GetHitDamage(FightWaza*);
u16 fightWaza_GetTargetDataId(FightWaza*);
u16 fightWaza_GetIryoku(FightWaza*);
s32 fightWaza_GetDamage(FightWaza*);
u8 fightWaza_GetCritical(FightWaza*);
u8 fightWaza_GetDamageValue(FightWaza*);
u16 fightWaza_GetMotoWazaDataId(FightWaza*);
u16 fightWaza_GetUseWazaDataId(FightWaza*);
u8 fightWazaIsHit(FightWaza*);
u8 fightWazaIsJoutaiDataId(FightWaza*, u16);
u8 fightWazaCheckWriteJoutaiDataId(FightWaza*, u16);
void fightWazaWriteJoutaiDataId(FightWaza*, u16, u32);
void fightWazaInitJoutaiDataId(FightWaza*, u16);
void fightWazaInitJoutai(FightWaza*);
}

struct ComboPartnerBits {
    u8 b10 : 1; // 0x80
    u8 b00 : 1; // 0x40
    u8 b11 : 1; // 0x20
    u8 b01 : 1; // 0x10
    u8 b12 : 1; // 0x08
    u8 b02 : 1; // 0x04
    u8 b13 : 1; // 0x02
    u8 b03 : 1; // 0x01
};

extern "C" {
void* wazaDataBiosGetPtr(u16 id);
u8 wazaDataBiosGetPp(void* data);
u8 pokemonWazaCheckValid(Pokemon* poke, u32 wazaNum);
void GScharLenCpy(void* dst, const void* src, s32 len);
}


struct FightPokemon {
    Pokemon* motoPokemon; // 0x0
    Pokemon pokemonBuff; // 0x4
    FightJoutai fightJoutai[1]; // 0xC8
    s16 entryId; // 0xD8
    u8 catchEntryFlag; // 0xDA
    u8 levelUpFlag; // 0xDB
    u8 darkOutFlag; // 0xDC
    u8 hokakuFlag; // 0xDD
    u8 unkDE[0x22];
    u32 aiDamage[0x40][2]; // 0x100
};

struct FightOutPokemon {
    FightPokemon* motoFightPokemon; // 0x0
    FightPokemon* fightPokemon; // 0x4
    FightPokemon fightPokemonHensinBuff; // 0x8
    FightJoutai fightoutJoutai[0x34]; // 0x308
    FightWaza fightWaza; // 0x648
    FightWaza keepFightWaza; // 0x6F4
    FightItem fightItem; // 0x7A0
    Sequence* sequence; // 0x7AC
    u8 abicntPhyAtk; // 0x7B0
    u8 abicntPhyDef; // 0x7B1
    u8 abicntSpeAtk; // 0x7B2
    u8 abicntSpeDef; // 0x7B3
    u8 abicntNimbleness; // 0x7B4
    u8 abicntAverage; // 0x7B5
    u8 abicntAvoid; // 0x7B6
    u8 unk7B7[0x5];
    u16 fightoutTurnCount; // 0x7BC
    s16 meetEnemyFightPokemonEntryId[12]; // 0x7BE
    u8 unk7D6[0x2];
    FightAction fightActionBuff; // 0x7D8
    u16 zokuseiDataId[2]; // 0x808
    u16 tokuseiDataId; // 0x80C
    u8 unk80E[0x2];
    WazaMenuCur wazaMenuCur; // 0x810
    u8 comboFuncId; // 0x814
    u8 fixAiWaza; // 0x815
    u8 fixAiDef; // 0x816
    u8 unk817[0x1];
    u16 sketchWazaDataId; // 0x818
    u16 lastSelectWazaDataId; // 0x81A
    u16 lastUseWazaDataId; // 0x81C
    u16 lastReceiveWazaTargetDataId; // 0x81E
    u16 hitWazaDataId; // 0x820
    u16 hitWazaZokuseiDataId; // 0x822
    s16 gamanDamageValue; // 0x824
    u16 gamanDamageTargetId; // 0x826
    u16 oumuWazaDataId; // 0x828
    u16 oumuWazaAllyDataId; // 0x82A
    u8 namakeFlag; // 0x82C
    u8 successCnt; // 0x82D
    u16 usedItemDataId; // 0x82E
    u16 stockItemDataId; // 0x830
    u8 unk832[0x2];
    s16 damageAtkValue; // 0x834
    u16 damageAtkTargetId; // 0x836
    s16 damageSpeValue; // 0x838
    u16 damageSpeTargetId; // 0x83A
    u8 mahiNoAttackFlag; // 0x83C
    u8 konranMyselfAttackFlag; // 0x83D
    u8 outWazaKoukanaiFlag; // 0x83E
    u8 tameWazaFlag; // 0x83F
    u8 itemNigeruFlag; // 0x840
    u8 huuinNoAttackFlag; // 0x841
    u8 meroMeroNoAttackFlag; // 0x842
    u8 kanashibariNoAttackFlag; // 0x843
    u8 chouhatsuNoAttackFlag; // 0x844
    u8 ichamonNoAttackFlag; // 0x845
    u8 hirumuNoAttackFlag; // 0x846
    u8 passPpdecFlag; // 0x847
    u8 fightActionFlag; // 0x848
    u8 doClearbodyFlag; // 0x849
    u8 receivesWazaHiraishinFlag; // 0x84A
    u8 vanishoffFlag; // 0x84B
    u8 doIkakuFlag; // 0x84C
    u8 doTraceFlag; // 0x84D
    u8 noPressureFlag; // 0x84E
    u8 irekaetaFlag; // 0x84F
    u8 itemKoraetaFlag; // 0x850
    u8 unk851[0x3];
    u32 kaigaraDamageValue; // 0x854
    s16 myselfDamageAtkValue; // 0x858
    u16 myselfDamageAtkTargetId; // 0x85A
    s16 myselfDamageSpeValue; // 0x85C
    u16 myselfDamageSpeTargetId; // 0x85E
    u8 kizetuFlag; // 0x860
    u8 unk861; // 0x861
    s16 irekaeTargetEntryId; // 0x862
    FightOutPokemonEnemy enemy[4]; // 0x864
};

extern "C" {

void fightOutPokemon_SetFixAiDef(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->fixAiDef = value;
    }
}

void fightOutPokemon_SetFixAiWaza(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->fixAiWaza = value;
    }
}

void fightOutPokemon_SetComboFuncId(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->comboFuncId = value;
    }
}

void fightOutPokemon_SetOumuWazaAllyDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->oumuWazaAllyDataId = value;
    }
}

void fightOutPokemon_SetIrekaeTargetEntryId(FightOutPokemon* fop, s16 value) {
    if (fop != nullptr) {
        fop->irekaeTargetEntryId = value;
    }
}

void fn_8014718C(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->unk861 = value;
    }
}

void fightOutPokemon_SetKizetuFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->kizetuFlag = value;
    }
}

void fightOutPokemon_SetMyselfDamageSpeTargetId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->myselfDamageSpeTargetId = value;
    }
}

void fightOutPokemon_SetMyselfDamageSpeValue(FightOutPokemon* fop, s16 value) {
    if (fop != nullptr) {
        fop->myselfDamageSpeValue = value;
    }
}

void fightOutPokemon_SetMyselfDamageAtkTargetId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->myselfDamageAtkTargetId = value;
    }
}

void fightOutPokemon_SetMyselfDamageAtkValue(FightOutPokemon* fop, s16 value) {
    if (fop != nullptr) {
        fop->myselfDamageAtkValue = value;
    }
}

void fightOutPokemon_SetKaigaraDamageValue(FightOutPokemon* fop, u32 value) {
    if (fop != nullptr) {
        fop->kaigaraDamageValue = value;
    }
}

void fightOutPokemon_SetItemKoraetaFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->itemKoraetaFlag = value;
    }
}

void fightOutPokemon_SetIrekaetaFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->irekaetaFlag = value;
    }
}

void fightOutPokemon_SetNoPressureFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->noPressureFlag = value;
    }
}

void fightOutPokemon_SetDoTraceFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->doTraceFlag = value;
    }
}

void fightOutPokemon_SetDoIkakuFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->doIkakuFlag = value;
    }
}

void fightOutPokemon_SetVanishoffFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->vanishoffFlag = value;
    }
}

void fightOutPokemon_SetReceivesWazaHiraishinFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->receivesWazaHiraishinFlag = value;
    }
}

void fightOutPokemon_SetDoClearbodyFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->doClearbodyFlag = value;
    }
}

void fightOutPokemon_SetFightActionFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->fightActionFlag = value;
    }
}

void fightOutPokemon_SetPassPpdecFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->passPpdecFlag = value;
    }
}

void fightOutPokemon_SetHirumuNoAttackFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->hirumuNoAttackFlag = value;
    }
}

void fightOutPokemon_SetIchamonNoAttackFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->ichamonNoAttackFlag = value;
    }
}

void fightOutPokemon_SetChouhatsuNoAttackFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->chouhatsuNoAttackFlag = value;
    }
}

void fightOutPokemon_SetKanashibariNoAttackFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->kanashibariNoAttackFlag = value;
    }
}

void fightOutPokemon_SetMeroMeroNoAttackFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->meroMeroNoAttackFlag = value;
    }
}

void fightOutPokemon_SetHuuinNoAttackFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->huuinNoAttackFlag = value;
    }
}

void fightOutPokemon_SetItemNigeruFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->itemNigeruFlag = value;
    }
}

void fightOutPokemon_SetTameWazaFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->tameWazaFlag = value;
    }
}

void fightOutPokemon_SetOutWazaKoukanaiFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->outWazaKoukanaiFlag = value;
    }
}

void fightOutPokemon_SetKonranMyselfAttackFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->konranMyselfAttackFlag = value;
    }
}

void fightOutPokemon_SetMahiNoAttackFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->mahiNoAttackFlag = value;
    }
}

void fightOutPokemon_SetDamageSpeTargetId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->damageSpeTargetId = value;
    }
}

void fightOutPokemon_SetDamageSpeValue(FightOutPokemon* fop, s16 value) {
    if (fop != nullptr) {
        fop->damageSpeValue = value;
    }
}

void fightOutPokemon_SetDamageAtkTargetId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->damageAtkTargetId = value;
    }
}

void fightOutPokemon_SetDamageAtkValue(FightOutPokemon* fop, s16 value) {
    if (fop != nullptr) {
        fop->damageAtkValue = value;
    }
}

void fightOutPokemon_SetTokuseiDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->tokuseiDataId = value;
    }
}

void fightOutPokemon_SetZokuseiDataId(FightOutPokemon* fop, u8 idx, u16 value) {
    if (fop == nullptr) {
        return;
    }
    if (idx >= 2) {
        return;
    }
    fop->zokuseiDataId[idx] = value;
}

void fightOutPokemon_SetMeetEnemyFightPokemonEntryId(FightOutPokemon* fop, u8 idx, s16 value) {
    if (fop == nullptr) {
        return;
    }
    if (idx >= 12) {
        return;
    }
    fop->meetEnemyFightPokemonEntryId[idx] = value;
}

void fightOutPokemon_SetSuccessCnt(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->successCnt = value;
    }
}

void fightOutPokemon_SetStockItemDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->stockItemDataId = value;
    }
}

void fightOutPokemon_SetUsedItemDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->usedItemDataId = value;
    }
}

void fightOutPokemon_SetNamakeFlag(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->namakeFlag = value;
    }
}

void fightOutPokemon_SetOumuWazaDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->oumuWazaDataId = value;
    }
}

void fightOutPokemon_SetGamanDamageTargetId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->gamanDamageTargetId = value;
    }
}

void fightOutPokemon_SetGamanDamageValue(FightOutPokemon* fop, s16 value) {
    if (fop != nullptr) {
        fop->gamanDamageValue = value;
    }
}

void fightOutPokemon_SetHitWazaZokuseiDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->hitWazaZokuseiDataId = value;
    }
}

void fightOutPokemon_SetHitWazaDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->hitWazaDataId = value;
    }
}

void fightOutPokemon_SetLastReceiveWazaTargetDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->lastReceiveWazaTargetDataId = value;
    }
}

void fightOutPokemon_SetLastUseWazaDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->lastUseWazaDataId = value;
    }
}

void fightOutPokemon_SetLastSelectWazaDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->lastSelectWazaDataId = value;
    }
}

void fightOutPokemon_SetSketchWazaDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->sketchWazaDataId = value;
    }
}

void fightOutPokemon_SetSequencePtr(FightOutPokemon* fop, Sequence* value) {
    if (fop != nullptr) {
        fop->sequence = value;
    }
}

void fightOutPokemon_SetFightoutTurnCount(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fop->fightoutTurnCount = value;
    }
}

void fightOutPokemon_SetAbicntAverage(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fop->abicntAverage = value;
    }
}

void fightOutPokemon_SetWazaHitDamage(FightOutPokemon* fop, s32 value) {
    if (fop != nullptr) {
        fightWaza_SetHitDamage(fightOutPokemon_GetFightWazaPtr(fop), value);
    }
}

void fightOutPokemon_SetWazaTargetId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fightWaza_SetTargetDataId(fightOutPokemon_GetFightWazaPtr(fop), value);
    }
}

void fightOutPokemon_SetWazaIryoku(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(fop), value);
    }
}

void fightOutPokemon_SetWazaDamage(FightOutPokemon* fop, s32 value) {
    if (fop != nullptr) {
        fightWaza_SetDamage(fightOutPokemon_GetFightWazaPtr(fop), value);
    }
}

void fightOutPokemon_SetWazaInitJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (fop != nullptr) {
        FightWaza* waza = fightOutPokemon_GetFightWazaPtr(fop);
        if (id != 0) {
            if (fightWazaIsJoutaiDataId(waza, id) == 1) {
                fightWazaInitJoutaiDataId(waza, id);
            }
        } else {
            fightWazaInitJoutai(waza);
        }
    }
}

void fightOutPokemon_SetWazaJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (fop != nullptr) {
        FightWaza* waza = fightOutPokemon_GetFightWazaPtr(fop);
        if (fightWazaCheckWriteJoutaiDataId(waza, id) == 2) {
            fightWazaWriteJoutaiDataId(waza, id, 0);
        }
    }
}

void fightOutPokemon_SetWazaCritical(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fightWaza_SetCritical(fightOutPokemon_GetFightWazaPtr(fop), value);
    }
}

void fightOutPokemon_SetWazaDamageValue(FightOutPokemon* fop, u8 value) {
    if (fop != nullptr) {
        fightWaza_SetDamageValue(fightOutPokemon_GetFightWazaPtr(fop), value);
    }
}

void fightOutPokemon_SetMotoWazaDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fightWaza_SetMotoWazaDataId(fightOutPokemon_GetFightWazaPtr(fop), value);
    }
}

void fightOutPokemon_SetUseWazaDataId(FightOutPokemon* fop, u16 value) {
    if (fop != nullptr) {
        fightWaza_SetUseWazaDataId(fightOutPokemon_GetFightWazaPtr(fop), value);
    }
}

void fightOutPokemon_SetFightPokemonPtr(FightOutPokemon* fop, FightPokemon* value) {
    if (fop != nullptr) {
        fop->fightPokemon = value;
    }
}

void fightOutPokemon_SetMotoFightPokemonPtr(FightOutPokemon* fop, FightPokemon* value) {
    if (fop != nullptr) {
        fop->motoFightPokemon = value;
    }
}

void fightPokemon_SetAiDamage(FightPokemon* fp, u16 a, u16 b, u32 value) {
    if (fp == nullptr) {
        return;
    }
    if (a >= 0x40) {
        return;
    }
    fp->aiDamage[a][b] = value;
}

void fightPokemon_SetHokakuFlag(FightPokemon* fp, u8 value) {
    if (fp != nullptr) {
        fp->hokakuFlag = value;
    }
}

void fightPokemon_SetDarkOutFlag(FightPokemon* fp, u8 value) {
    if (fp != nullptr) {
        fp->darkOutFlag = value;
    }
}

void fightPokemon_SetLevelUpFlag(FightPokemon* fp, u8 value) {
    if (fp != nullptr) {
        fp->levelUpFlag = value;
    }
}

void fightPokemon_SetCatchEntryFlag(FightPokemon* fp, u8 value) {
    if (fp != nullptr) {
        fp->catchEntryFlag = value;
    }
}

void fightPokemon_SetEntryId(FightPokemon* fp, s16 value) {
    if (fp != nullptr) {
        fp->entryId = value;
    }
}

void fightPokemon_SetMotoPokemonPtr(FightPokemon* fp, Pokemon* value) {
    if (fp != nullptr) {
        fp->motoPokemon = value;
    }
}

void pokemon_SetComboPartnerAll(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->comboPartnerAll = data;
    }
}

void pokemon_SetPoolFriend(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        if (data > 0xFF) {
            data = 0xFF;
        }
        poke->setPoolFriendLevel(data);
    }
}

void pokemon_SetPoolExp(Pokemon* poke, u32 data) {
    if (poke != nullptr)
    {
        poke->setPoolExp(data);
    }
}

void pokemon_SetDarkpokemonDataId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->darkPokemonDataID = data;
    }
}

void pokemon_SetFightTrainerPokemonDataId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->fightTrainerPokemonDataId = data;
    }
}

void pokemon_SetAmari(Pokemon* poke, u16 data) {
    pokemonBiosSetAmari(poke, data);
}

void pokemon_SetPara1Amari(Pokemon* poke, u16 data) {
    pokemonBiosSetPara1Amari(poke, data);
}

void pokemon_SetMailId(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->mailId = data;
    }
}

void pokemon_SetPcboxMark(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->pcboxMark = data;
    }
}

void pokemon_SetFlagAmari(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->flagAmari = data;
    }
}

void pokemon_SetFuseiFlag(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->flags.bits.fusei = data;
    }
}

void pokemon_SetTokuseiFlag(Pokemon* poke, u32 value) {
    if (poke != nullptr) {
        if (pokemonDataBiosGetTokuseiDataId(pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(poke)), 1) == 0) {
            value = 0;
        }
        poke->flags.bits.tokusei = value;
    }
}

void pokemon_SetTamagoFlag(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->flags.bits.tamago = data;
    }
}

void pokemon_SetPokerus(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->pokerus = data;
    }
}

void pokemon_SetStrongMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->strong = data;
        }
    }
}

void pokemon_SetCleverMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->clever = data;
        }
    }
}

void pokemon_SetCuteMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->cute = data;
        }
    }
}

void pokemon_SetBeautifulMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->beautiful = data;
        }
    }
}

void pokemon_SetStyleMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->style = data;
        }
    }
}

void pokemon_SetAmariRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.amari = data;
        }
    }
}

void pokemon_SetWorldRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.world = data;
        }
    }
}

void pokemon_SetEarthRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.earth = data;
        }
    }
}

void pokemon_SetNationalRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.national = data;
        }
    }
}

void pokemon_SetCountryRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.country = data;
        }
    }
}

void pokemon_SetSkyRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.sky = data;
        }
    }
}

void pokemon_SetLandRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.land = data;
        }
    }
}

void pokemon_SetMarineRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.marine = data;
        }
    }
}

void pokemon_SetGanbaRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.ganba = data;
        }
    }
}

void pokemon_SetBromideRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.bromide = data;
        }
    }
}

void pokemon_SetVictoryRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.victory = data;
        }
    }
}

void pokemon_SetWinningRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.winning = data;
        }
    }
}

void pokemon_SetChampRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.champ = data;
        }
    }
}

void pokemon_SetFur(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->fur = data;
    }
}

void pokemon_SetStrong(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->strong = data;
        }
    }
}

void pokemon_SetClever(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->clever = data;
        }
    }
}

void pokemon_SetCute(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->cute = data;
        }
    }
}

void pokemon_SetBeautiful(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->beautiful = data;
        }
    }
}

void pokemon_SetStyle(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->style = data;
        }
    }
}

void pokemon_SetFriend(Pokemon* poke, u16 data) {
    if (poke) {
        if (data > 0xFF) {
            data = 0xFF;
        }
        poke->friendLevel = data;
    }
}

void pokemon_SetNimblenessRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetNimblenessRnd(poke, data);
}

void pokemon_SetSpeDefRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeDefRnd(poke, data);
}

void pokemon_SetSpeAtkRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeAtkRnd(poke, data);
}

void pokemon_SetPhyDefRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyDefRnd(poke, data);
}

void pokemon_SetPhyAtkRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyAtkRnd(poke, data);
}

void pokemon_SetMaxHpRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetMaxHpRnd(poke, data);
}

void pokemon_SetNimblenessEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetNimblenessEffort(poke, data);
}

void pokemon_SetSpeDefEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeDefEffort(poke, data);
}

void pokemon_SetSpeAtkEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeAtkEffort(poke, data);
}

void pokemon_SetPhyDefEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyDefEffort(poke, data);
}

void pokemon_SetPhyAtkEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyAtkEffort(poke, data);
}

void pokemon_SetMaxHpEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetMaxHpEffort(poke, data);
}

void pokemon_SetNimbleness(Pokemon* poke, u16 data) {
    pokemonBiosSetNimbleness(poke, data);
}

void pokemon_SetSpeDef(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeDef(poke, data);
}

void pokemon_SetSpeAtk(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeAtk(poke, data);
}

void pokemon_SetPhyDef(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyDef(poke, data);
}

void pokemon_SetPhyAtk(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyAtk(poke, data);
}

void pokemon_SetMaxHp(Pokemon* poke, u16 data) {
    pokemonBiosSetMaxHp(poke, data);
}

void pokemon_SetHp(Pokemon* poke, u16 data) {
    if (poke) {
        poke->hp = data;
        u16 maxHp = pokemonBiosGetMaxHp(poke);
        if (maxHp < poke->hp) {
            poke->hp = maxHp;
        }
    }
}

void pokemon_SetItemDataId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->itemDataID = data;
    }
}

void pokemon_SetPokemonWazaPpCount(Pokemon* poke, u32 wazaNum, u8 count) {
    if (poke != nullptr) {
        PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 0);
        if (waza != nullptr) {
            if (count > 3) {
                count = 3;
            }
            if (pokemonWazaCheckValid(poke, wazaNum) == 1) {
                if (wazaDataBiosGetPp(wazaDataBiosGetPtr(pokemonBiosGetPokemonWazaDataId(poke, wazaNum))) <= 4) {
                    return;
                }
            }
            waza->ppCount = count;
        }
    }
}

void pokemon_SetPokemonWazaPp(Pokemon* poke, u32 wazaNum, u8 data) {
    if (poke != nullptr)
    {
        PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 0);
        if (waza)
        {
            u8 maxPp = pokemonWazaGetMaxPP(poke, wazaNum);
            if (maxPp < data) {
                data = maxPp;
            }

            waza->pp = data;
        }
    }
}

void pokemon_SetPokemonWazaDataId(Pokemon* poke, u32 wazaNum, u16 data) {
    if (poke != nullptr)
    {
        PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 0);
        if (waza)
        {
            waza->dataId = data;
        }
    }
}

void pokemon_SetConditionAmari(Pokemon* poke, u32 data) {
    if (poke != nullptr)
    {
        poke->conditionAmari = data;
    }
}

void pokemon_SetLevel(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        if (data <= 100)
        {
            poke->level = data;
        }
    }
}

void pokemon_SetExp(Pokemon* poke, u32 data) {
    if (poke != nullptr)
    {
        poke->exp = data;
    }
}

void pokemon_SetNicknamePtr(Pokemon* poke, char* name) {
    if (poke == nullptr || name == nullptr) {
        return;
    }
    GScharLenCpy(&poke->nickname[0], name, 11);
    pokemonBiosSetNicknameOrgPtr(poke, name);
}

void pokemon_SetCatchTrainerNamePtr(Pokemon* poke, const char* name) {
    if (poke == nullptr || name == nullptr) {
        return;
    }
    GScharLenCpy(&poke->catchTrainerName[0], name, 11);
}

void pokemon_SetCatchTrainerRnd(Pokemon* poke, u32 data) {
    if (poke != nullptr) {
        poke->catchTrainerRnd = data;
    }
}

void pokemon_SetCatchTrainerSex(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->catchTrainerSex = data;
    }
}

void pokemon_SetCatchBallId(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->catchBallId = data;
    }
}

void pokemon_SetCatchLevel(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->catchLevel = data;
    }
}

void pokemon_SetCatchFloorId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->catchFloorId = data;
    }
}

void pokemon_SetRnd(Pokemon* poke, u32 data) {
    if (poke != nullptr)
    {
        poke->rnd = data;
    }
}

void pokemon_SetPokemonDataId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->dataID = data;
    }
}

void pokemonDB_SetTukamaetaFlag(u16 id, bool value) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data != nullptr) {
        GSflagSet(data->tukamaetaFlag, value);
    }
}

void pokemonDB_SetMitaFlag(u16 id, bool value) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data != nullptr) {
        GSflagSet(data->mitaFlag, value);
    }
}

u8 fightOutPokemon_GetFixAiDef(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->fixAiDef;
}

u8 fightOutPokemon_GetFixAiWaza(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->fixAiWaza;
}

u8 fightOutPokemon_GetComboFuncId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->comboFuncId;
}

u16 fightOutPokemon_GetOumuWazaAllyDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->oumuWazaAllyDataId;
}

FightOutPokemonEnemy* fightOutPokemon_GetFightOutPokemonEnemyPtr(FightOutPokemon* fop, u16 idx) {
    if (fop == nullptr) {
        return nullptr;
    }
    if (idx >= 4) {
        return nullptr;
    }
    return &fop->enemy[idx];
}

s16 fightOutPokemon_GetIrekaeTargetEntryId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return -1;
    }
    return fop->irekaeTargetEntryId;
}

u8 fn_80148688(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->unk861;
}

u8 fightOutPokemon_GetKizetuFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->kizetuFlag;
}

s16 fightOutPokemon_GetMyselfDamageSpeValue(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->myselfDamageSpeValue;
}

s16 fightOutPokemon_GetMyselfDamageAtkValue(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->myselfDamageAtkValue;
}

u32 fightOutPokemon_GetKaigaraDamageValue(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->kaigaraDamageValue;
}

u8 fightOutPokemon_GetItemKoraetaFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->itemKoraetaFlag;
}

u8 fightOutPokemon_GetIrekaetaFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->irekaetaFlag;
}

u8 fightOutPokemon_GetNoPressureFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->noPressureFlag;
}

u8 fightOutPokemon_GetDoTraceFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->doTraceFlag;
}

u8 fightOutPokemon_GetDoIkakuFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->doIkakuFlag;
}

u8 fightOutPokemon_GetVanishoffFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->vanishoffFlag;
}

u8 fightOutPokemon_GetReceivesWazaHiraishinFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->receivesWazaHiraishinFlag;
}

u8 fightOutPokemon_GetDoClearbodyFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->doClearbodyFlag;
}

u8 fightOutPokemon_GetFightActionFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->fightActionFlag;
}

u8 fightOutPokemon_GetPassPpdecFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->passPpdecFlag;
}

u8 fightOutPokemon_GetTameWazaFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->tameWazaFlag;
}

u8 fightOutPokemon_GetKonranMyselfAttackFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->konranMyselfAttackFlag;
}

u16 fightOutPokemon_GetDamageSpeTargetId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->damageSpeTargetId;
}

s16 fightOutPokemon_GetDamageSpeValue(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->damageSpeValue;
}

u16 fightOutPokemon_GetDamageAtkTargetId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->damageAtkTargetId;
}

s16 fightOutPokemon_GetDamageAtkValue(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->damageAtkValue;
}

WazaMenuCur* fightOutPokemon_GetWazaMenuCurPtr(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return nullptr;
    }
    return &fop->wazaMenuCur;
}

u16 fightOutPokemon_GetTokuseiDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->tokuseiDataId;
}

u16 fightOutPokemon_GetZokuseiDataId(FightOutPokemon* fop, u8 idx) {
    if (fop == nullptr) {
        return 0;
    }
    if (idx >= 2) {
        return 0;
    }
    return fop->zokuseiDataId[idx];
}

FightAction* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return nullptr;
    }
    return &fop->fightActionBuff;
}

s16 fightOutPokemon_GetMeetEnemyFightPokemonEntryId(FightOutPokemon* fop, u8 idx) {
    if (fop == nullptr) {
        return -1;
    }
    if (idx >= 12) {
        return -1;
    }
    return fop->meetEnemyFightPokemonEntryId[idx];
}

u8 fightOutPokemon_GetSuccessCnt(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->successCnt;
}

u16 fightOutPokemon_GetStockItemDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->stockItemDataId;
}

u16 fightOutPokemon_GetUsedItemDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->usedItemDataId;
}

u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->namakeFlag;
}

FightWaza* fightOutPokemon_GetKeepFightWazaPtr(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return nullptr;
    }
    return &fop->keepFightWaza;
}

u16 fightOutPokemon_GetOumuWazaDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->oumuWazaDataId;
}

u16 fightOutPokemon_GetGamanDamageTargetId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->gamanDamageTargetId;
}

s16 fightOutPokemon_GetGamanDamageValue(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->gamanDamageValue;
}

u16 fightOutPokemon_GetHitWazaZokuseiDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 9;
    }
    return fop->hitWazaZokuseiDataId;
}

u16 fightOutPokemon_GetHitWazaDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->hitWazaDataId;
}

u16 fightOutPokemon_GetLastReceiveWazaTargetDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->lastReceiveWazaTargetDataId;
}

u16 fightOutPokemon_GetLastUseWazaDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->lastUseWazaDataId;
}

u16 fightOutPokemon_GetLastSelectWazaDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->lastSelectWazaDataId;
}

u16 fightOutPokemon_GetSketchWazaDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->sketchWazaDataId;
}

Sequence* fightOutPokemon_GetSequencePtr(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return nullptr;
    }
    return fop->sequence;
}

u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->fightoutTurnCount;
}

u8 fightOutPokemon_GetAbicntAvoid(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->abicntAvoid;
}

u8 fightOutPokemon_GetAbicntAverage(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->abicntAverage;
}

u8 fightOutPokemon_GetAbicntNimbleness(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->abicntNimbleness;
}

u8 fightOutPokemon_GetAbicntSpeDef(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->abicntSpeDef;
}

u8 fightOutPokemon_GetAbicntSpeAtk(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->abicntSpeAtk;
}

u8 fightOutPokemon_GetAbicntPhyDef(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->abicntPhyDef;
}

u8 fightOutPokemon_GetAbicntPhyAtk(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fop->abicntPhyAtk;
}

FightItem* fightOutPokemon_GetFightItemPtr(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return nullptr;
    }
    return &fop->fightItem;
}

s32 fightOutPokemon_GetHitDamage(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fightWaza_GetHitDamage(fightOutPokemon_GetFightWazaPtr(fop));
}

u16 fightOutPokemon_GetTargetId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fightWaza_GetTargetDataId(fightOutPokemon_GetFightWazaPtr(fop));
}

u16 fightOutPokemon_GetIryoku(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(fop));
}

s32 fightOutPokemon_GetDamage(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fightWaza_GetDamage(fightOutPokemon_GetFightWazaPtr(fop));
}

u8 fightOutPokemon_GetIsHit(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fightWazaIsHit(fightOutPokemon_GetFightWazaPtr(fop));
}

u8 fightOutPokemon_GetJoutaiDataId(FightOutPokemon* fop, u16 id) {
    if (fop == nullptr) {
        return 0;
    }
    return fightWazaIsJoutaiDataId(fightOutPokemon_GetFightWazaPtr(fop), id);
}

u8 fightOutPokemon_GetCritical(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fightWaza_GetCritical(fightOutPokemon_GetFightWazaPtr(fop));
}

u8 fightOutPokemon_GetDamageValue(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    return fightWaza_GetDamageValue(fightOutPokemon_GetFightWazaPtr(fop));
}

u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(fop);
    if (waza == nullptr) {
        return 0;
    }
    return fightWaza_GetMotoWazaDataId(waza);
}

u16 fightOutPokemon_GetUseWazaDataId(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return 0;
    }
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(fop);
    if (waza == nullptr) {
        return 0;
    }
    return fightWaza_GetUseWazaDataId(waza);
}

FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return nullptr;
    }
    return &fop->fightWaza;
}

FightJoutai* fightOutPokemon_GetFightoutJoutaiPtr(FightOutPokemon* fop, u16 idx) {
    if (fop == nullptr) {
        return nullptr;
    }
    if (idx >= 0x34) {
        return nullptr;
    }
    return &fop->fightoutJoutai[idx];
}

FightPokemon* fightOutPokemon_GetFightPokemonHensinBuffPtr(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return nullptr;
    }
    return &fop->fightPokemonHensinBuff;
}

FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return nullptr;
    }
    return fop->fightPokemon;
}

FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon* fop) {
    if (fop == nullptr) {
        return nullptr;
    }
    return fop->motoFightPokemon;
}

u8 fightPokemon_GetHokakuFlag(FightPokemon* fp) {
    if (fp == nullptr) {
        return 0;
    }
    return fp->hokakuFlag;
}

u8 fightPokemon_GetDarkOutFlag(FightPokemon* fp) {
    if (fp == nullptr) {
        return 0;
    }
    return fp->darkOutFlag;
}

u8 fightPokemon_GetLevelUpFlag(FightPokemon* fp) {
    if (fp == nullptr) {
        return 0;
    }
    return fp->levelUpFlag;
}

u8 fightPokemon_GetCatchEntryFlag(FightPokemon* fp) {
    if (fp == nullptr) {
        return 0;
    }
    return fp->catchEntryFlag;
}

s16 fightPokemon_GetEntryId(FightPokemon* fp) {
    if (fp == nullptr) {
        return -1;
    }
    return fp->entryId;
}

FightJoutai* fightPokemon_GetFightJoutaiPtr(FightPokemon* fp, u16 idx) {
    if (fp == nullptr) {
        return nullptr;
    }
    if (idx >= 1) {
        return nullptr;
    }
    return &fp->fightJoutai[idx];
}

Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon* fp) {
    if (fp == nullptr) {
        return nullptr;
    }
    return &fp->pokemonBuff;
}

Pokemon* fightPokemon_GetMotoPokemonPtr(FightPokemon* fp) {
    if (fp == nullptr) {
        return nullptr;
    }
    return fp->motoPokemon;
}

u8 pokemon_GetComboPartner(Pokemon* poke, u8 idx, u8 kind) {
    if (poke == nullptr) {
        return 0;
    }
    ComboPartnerBits* bits = (ComboPartnerBits*)&poke->comboPartnerAll;
    switch (kind) {
    case 0:
        switch (idx) {
        case 0: return bits->b00;
        case 1: return bits->b01;
        case 2: return bits->b02;
        case 3: return bits->b03;
        default: return 0;
        }
    case 1:
        switch (idx) {
        case 0: return bits->b10;
        case 1: return bits->b11;
        case 2: return bits->b12;
        case 3: return bits->b13;
        default: return 0;
        }
    default:
        return 0;
    }
}

bool pokemon_GetDarkFlag(Pokemon* poke) {
    if (poke == nullptr) {
        return false;
    }
    return poke->isDarkPokemon();
}

u32 pokemon_GetPoolFriend(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPoolFriendLevel();
}

u32 pokemon_GetPoolExp(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPoolExp();
}

u32 pokemon_GetInitDp(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    u16 id = pokemonBiosGetDarkpokemonDataId(poke);
    if (id == 0) {
        return 0;
    }
    return darkPokemonBiosGetDarkPoint(id);
}

u16 pokemon_GetDarkpokemonDataId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->darkPokemonDataID;
}

u16 pokemon_GetFightTrainerPokemonDataId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->fightTrainerPokemonDataId;
}

u8 pokemon_GetNowExpToLevel(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    u8 grow = pokemonDB_GetGrowDataId(pokemon_GetPokemonDataId(poke));
    u32 exp = pokemon_GetExp(poke);
    return pokemonGetExpToLevel(grow, exp);
}

u8 pokemon_GetSeikaku(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return pokemonGetSeikakuAsRnd(pokemon_GetRnd(poke));
}

bool pokemon_GetFuseiFlag(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->flags.bits.fusei;
}

u8 pokemon_GetTokuseiFlag(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    if (pokemonDataBiosGetTokuseiDataId(pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(poke)), 1) == 0) {
        return 0;
    }
    return poke->flags.bits.tokusei != 0;
}

bool pokemon_GetTamagoFlag(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->flags.bits.tamago;
}

u8 pokemon_GetPokerus(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->pokerus;
}

u16 pokemon_GetFriend(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->friendLevel;
}

u8 pokemon_GetNimblenessRnd(Pokemon* poke) {
    return pokemonBiosGetNimblenessRnd(poke);
}

u8 pokemon_GetSpeDefRnd(Pokemon* poke) {
    return pokemonBiosGetSpeDefRnd(poke);
}

u8 pokemon_GetSpeAtkRnd(Pokemon* poke) {
    return pokemonBiosGetSpeAtkRnd(poke);
}

u8 pokemon_GetPhyDefRnd(Pokemon* poke) {
    return pokemonBiosGetPhyDefRnd(poke);
}

u8 pokemon_GetPhyAtkRnd(Pokemon* poke) {
    return pokemonBiosGetPhyAtkRnd(poke);
}

u8 pokemon_GetMaxHpRnd(Pokemon* poke) {
    return pokemonBiosGetMaxHpRnd(poke);
}

u16 pokemon_GetNimbleness(Pokemon* poke) {
    return pokemonBiosGetNimbleness(poke);
}

u16 pokemon_GetSpeDef(Pokemon* poke) {
    return pokemonBiosGetSpeDef(poke);
}

u16 pokemon_GetSpeAtk(Pokemon* poke) {
    return pokemonBiosGetSpeAtk(poke);
}

u16 pokemon_GetPhyDef(Pokemon* poke) {
    return pokemonBiosGetPhyDef(poke);
}

u16 pokemon_GetPhyAtk(Pokemon* poke) {
    return pokemonBiosGetPhyAtk(poke);
}

u16 pokemon_GetMaxHp(Pokemon* poke) {
    return pokemonBiosGetMaxHp(poke);
}

u16 pokemon_GetHp(Pokemon* poke) {
    if (poke == 0) {
        return 0;
    }
    return poke->hp;
}

u16 pokemon_GetItemDataId(Pokemon* poke) {
    if (poke == 0) {
        return 0;
    }
    return poke->itemDataID;
}

u8 pokemon_GetPokemonWazaPpCount(Pokemon* poke, u32 wazaNum) {
    if (poke == nullptr) {
        return 0;
    }

    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 1);
    if (waza == nullptr) {
        return 0;
    }
    return waza->ppCount;
}

u8 pokemon_GetPokemonWazaPp(Pokemon* poke, u32 wazaNum) {
    if (poke == nullptr) {
        return 0;
    }

    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 1);
    if (waza == nullptr) {
        return 0;
    }
    return waza->pp;
}

u16 pokemon_GetPokemonWazaDataId(Pokemon* poke, u32 wazaNum) {
    if (poke == nullptr) {
        return 0;
    }

    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 1);
    if (waza == nullptr) {
        return 0;
    }
    return waza->dataId;
}

u16 pokemon_GetHinsi(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return pokemon_GetHp(poke) == 0;
}

u8 pokemon_GetLevel(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->level;
}

u32 pokemon_GetExp(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->exp;
}

char* pokemon_GetNicknamePtr(Pokemon* poke) {
    if (poke == nullptr)
    {
        return nullptr;
    }
    return &poke->nickname[0];
}

u32 pokemon_GetCatchTrainerRnd(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->catchTrainerRnd;
}

u8 pokemon_GetCatchBallId(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->catchBallId;
}

Attest* pokemon_GetAttest(Pokemon* poke) {
    if (poke == nullptr)
    {
        return nullptr;
    }
    return &poke->attest;
}

u32 pokemon_GetRnd(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->rnd;
}

u16 pokemon_GetPokemonDataId(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->dataID;
}

u32 pokemonDB_GetPkxDataId(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->pkxDataId;
}

bool pokemonDB_GetTukamaetaFlag(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return GSflagGet(data->tukamaetaFlag);
}

u16 pokemonDB_GetShout(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->shout;
}

u16 pokemonDB_GetVoice(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->voice;
}

u16 pokemonDB_GetWeight(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->weight;
}

u32 pokemonDB_GetPokebodyId(u16 id, u16 idx) {
    PokemonDataCgData* cg = pokemonDataBiosGetCgDataPtr(pokemonDataBiosGetPtr(id), idx);
    if (cg == nullptr) {
        return 0;
    }
    return cg->pokebodyId;
}

u8 pokemonDB_GetTeachWaza(u16 id, u16 idx) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    if (!(idx < 12 && idx > -1)) {
        return 0;
    }
    return data->teachWaza[idx] != 0;
}

u16 pokemonDB_GetGetWazaDataId(u16 id, u16 idx) {
    PokemonDataWaza* waza = pokemonDataBiosGetGetWazaPtr(pokemonDataBiosGetPtr(id), idx);
    if (waza == nullptr) {
        return 0;
    }
    return waza->dataId;
}

u8 pokemonDB_GetGetWazaLevel(u16 id, u16 idx) {
    PokemonDataWaza* waza = pokemonDataBiosGetGetWazaPtr(pokemonDataBiosGetPtr(id), idx);
    if (waza == nullptr) {
        return 0;
    }
    return waza->level;
}

u8 pokemonDB_GetTokuseiDataId(u16 id, u16 idx) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    if (idx >= 2) {
        return 0;
    }
    return data->tokuseiDataId[idx];
}

u8 pokemonDB_GetZokuseiDataId(u16 id, u16 idx) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    if (idx >= 2) {
        return 0;
    }
    return data->zokuseiDataId[idx];
}

u16 pokemonDB_GetItemDataId(u16 id, u16 idx) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    if (idx >= 2) {
        return 0;
    }
    return data->itemDataId[idx];
}

u16 pokemonDB_GetInitFriend(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->initFriend;
}

u8 pokemonDB_GetSexRatio(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->sexRatio;
}

u8 pokemonDB_GetGet(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->get;
}

u8 pokemonDB_GetGrowDataId(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->growDataId;
}

u16 pokemonDB_GetGiveExp(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->giveExp;
}

u16 pokemonDB_GetBasisNimbleness(u16 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id), 0);
    if (status == nullptr) {
        return 0;
    }
    return status->nimbleness;
}

u16 pokemonDB_GetBasisSpeDef(u16 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id), 0);
    if (status == nullptr) {
        return 0;
    }
    return status->speDef;
}

u16 pokemonDB_GetBasisSpeAtk(u16 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id), 0);
    if (status == nullptr) {
        return 0;
    }
    return status->speAtk;
}

u16 pokemonDB_GetBasisPhyDef(u16 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id), 0);
    if (status == nullptr) {
        return 0;
    }
    return status->phyDef;
}

u16 pokemonDB_GetBasisPhyAtk(u16 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id), 0);
    if (status == nullptr) {
        return 0;
    }
    return status->phyAtk;
}

u16 pokemonDB_GetBasisMaxHp(u16 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id), 0);
    if (status == nullptr) {
        return 0;
    }
    return status->maxHp;
}

const char* pokemonDB_GetName(u16 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) {
        return 0;
    }
    return data->name;
}

}
