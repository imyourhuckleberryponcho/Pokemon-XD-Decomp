#ifndef GAME_FIGHTPOKEMONDATA_H
#define GAME_FIGHTPOKEMONDATA_H
#include <dolphin/types.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

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
    u8 data[0x8];
    void* slot8;
    void* slotC;
    u8 pad10[0x4];
    void* slot14;
    void* slot18;
    u8 pad1C[0x14];
};
struct WazaMenuCur {
    u8 data[4];
};
#include <game/fightrecords.h>
struct Sequence;
struct FightOutPokemon;

struct FightPokemon {
    Pokemon* motoPokemon;
    Pokemon pokemonBuff;
    FightJoutai fightJoutai[1];
    s16 entryId;
    u8 catchEntryFlag;
    u8 levelUpFlag;
    u8 darkOutFlag;
    u8 hokakuFlag;
    u8 unkDE[0x22];
    u32 aiDamage[0x40][2];
};

struct FightOutPokemon {
    FightPokemon* motoFightPokemon;
    FightPokemon* fightPokemon;
    FightPokemon fightPokemonHensinBuff;
    FightJoutai fightoutJoutai[0x34];
    FightWaza fightWaza;
    FightWaza keepFightWaza;
    FightItem fightItem;
    Sequence* sequence;
    u8 abicntPhyAtk;
    u8 abicntPhyDef;
    u8 abicntSpeAtk;
    u8 abicntSpeDef;
    u8 abicntNimbleness;
    u8 abicntAverage;
    u8 abicntAvoid;
    u8 unk7B7[0x5];
    u16 fightoutTurnCount;
    s16 meetEnemyFightPokemonEntryId[12];
    u8 unk7D6[0x2];
    FightAction fightActionBuff;
    u16 zokuseiDataId[2];
    u16 tokuseiDataId;
    u8 unk80E[0x2];
    WazaMenuCur wazaMenuCur;
    u8 comboFuncId;
    u8 fixAiWaza;
    u8 fixAiDef;
    u8 unk817[0x1];
    u16 sketchWazaDataId;
    u16 lastSelectWazaDataId;
    u16 lastUseWazaDataId;
    u16 lastReceiveWazaTargetDataId;
    u16 hitWazaDataId;
    u16 hitWazaZokuseiDataId;
    s16 gamanDamageValue;
    u16 gamanDamageTargetId;
    u16 oumuWazaDataId;
    u16 oumuWazaAllyDataId;
    u8 namakeFlag;
    u8 successCnt;
    u16 usedItemDataId;
    u16 stockItemDataId;
    u8 unk832[0x2];
    s16 damageAtkValue;
    u16 damageAtkTargetId;
    s16 damageSpeValue;
    u16 damageSpeTargetId;
    u8 mahiNoAttackFlag;
    u8 konranMyselfAttackFlag;
    u8 outWazaKoukanaiFlag;
    u8 tameWazaFlag;
    u8 itemNigeruFlag;
    u8 huuinNoAttackFlag;
    u8 meroMeroNoAttackFlag;
    u8 kanashibariNoAttackFlag;
    u8 chouhatsuNoAttackFlag;
    u8 ichamonNoAttackFlag;
    u8 hirumuNoAttackFlag;
    u8 passPpdecFlag;
    u8 fightActionFlag;
    u8 doClearbodyFlag;
    u8 receivesWazaHiraishinFlag;
    u8 vanishoffFlag;
    u8 doIkakuFlag;
    u8 doTraceFlag;
    u8 noPressureFlag;
    u8 irekaetaFlag;
    u8 itemKoraetaFlag;
    u8 unk851[0x3];
    u32 kaigaraDamageValue;
    s16 myselfDamageAtkValue;
    u16 myselfDamageAtkTargetId;
    s16 myselfDamageSpeValue;
    u16 myselfDamageSpeTargetId;
    u8 kizetuFlag;
    u8 unk861;
    s16 irekaeTargetEntryId;
    FightOutPokemonEnemy enemy[4];
};

#endif
