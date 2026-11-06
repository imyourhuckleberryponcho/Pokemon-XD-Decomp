#ifndef GAME_FIGHTDATA_H
#define GAME_FIGHTDATA_H

#include <dolphin/types.h>

struct FightTrainerInfo {
    u32 ids;
    u32 gsInputDevice;
};

struct FightEncountData {
    u8 fightKind;
    u8 trainer;
    u8 pokemon;
    u8 entry;
    u8 zenmetuFlag;
    u8 unk5;
    u16 fightFloorDataId;
    u16 diskId;
    u8 unkA[2];
    u32 fightName;
    u32 bgmSndId;
    u32 wipeId;
    u32 syoukaiWzxDataId;
    FightTrainerInfo trainerInfo[4];
};

struct FightFloorData {
    u8 tikeiDataId;
    u8 unk1;
    u16 floorDataId;
    u32 name;
    u32 syoukaiWzxDataId;
    u32 bgmSndId;
    u32 envSndId;
    u16 fightSideDataId[2];
};

struct FightKindData {
    u8 backSaveDataFlag;
    u8 doBadgeCheckFlag;
    u8 doZukanMitaFlag;
    u8 doZukanTukamaetaFlag;
    u8 useItemFlag;
    u8 callFlag;
    u8 nigeruFlag;
    u8 drawFlag;
    u8 getExpFlag;
    u8 getOkaneFlag;
    u8 okanePoolFlag;
    u8 getNekoniKobanFlag;
    u8 getFriendFlag;
    u8 getInfectPokerusFlag;
    u8 doCriticalAttackFlag;
    u8 doHizukiAiFlag;
    u8 doHizukiMiyaburiFlag;
    u8 doItemSoubiTokukoutokubouupFlag;
    u8 keikentihueruFlag;
    u8 bossFlag;
    u8 dorobouFlag;
    u8 monohiroiFlag;
    u8 darkpokemonHypermodeFlag;
    u8 pokemonStatusMenuSubbarFlag;
    u8 hostEnemyMsgFlag;
    u8 regulationFlag;
    u8 unk1A[2];
    u32 name;
};

struct FightSideData {
    u16 yrot;
    u8 unk2[2];
    u32 fightTrainerStatusMenuDataId[2];
    u32 fightoutPokemonStatusMenuDataId[2];
};

struct FightTrainerKindData {
    u16 syoukinBairitu;
    u8 unk2[2];
    u32 prefixName;
    u32 bgmSndId;
};

struct FightTypeData {
    u8 type;
    u8 entryPokemonNum;
    u8 fightoutPokemonNum;
    u8 unk3;
    u32 name;
};

#endif
