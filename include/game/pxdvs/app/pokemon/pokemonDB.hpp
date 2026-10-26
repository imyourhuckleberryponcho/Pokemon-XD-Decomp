#ifndef POKEMONDB_H
#define POKEMONDB_H

#include <global.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

struct BasisStatus {
    u16 maxHp;
    u16 phyAtk;
    u16 phyDef;
    u16 speAtk;
    u16 speDef;
    u16 nimbleness;
};

struct Sinka {
    u8 kind;
    u16 buff;
    u16 pokemonDataId;
};

struct PokemonDataWaza {
    u8 level;
    u16 dataId;
};

struct PokemonDataCgData {
    u8 color;
    u16 spriteId;
    u32 pokebodyId;
};

struct PokemonData {
    u8 growDataId;
    u8 get;
    u8 sexRatio;
    u8 unk0[1];
    u16 giveExp;
    u16 initFriend;
    u16 height;
    u16 weight;
    u16 voice;
    u8 unk1[2];
    u16 shout;
    u16 numPokemon;
    u16 numZukan;
    u8 unk2[2];
    const char* name;
    u32 typeName;
    u32 doc;
    u32 mitaFlag;
    u32 tukamaetaFlag;
    u32 pkxDataId;
    u8 zokuseiDataId[2];
    u8 tokuseiDataId[2];
    u8 wazaMcn[58];
    u8 teachWaza[12];
    u16 itemDataId[2];
    u16 kowaza[8];
    BasisStatus basisStatus[2];
    Sinka sinka[5];
    PokemonDataWaza waza[20];
    PokemonDataCgData cgData[2];
};

extern "C" void pokemon_SetPoolFriend(Pokemon*, u16);
extern "C" void pokemon_SetPoolExp(Pokemon*, u32);
extern "C" void pokemon_SetDarkpokemonDataId(Pokemon*, u16);
extern "C" void pokemon_SetTokuseiFlag(Pokemon* , u32);
extern "C" void pokemon_SetMaxHp(Pokemon*, u16);
extern "C" void pokemon_SetHp(Pokemon*, u16);
extern "C" void pokemon_SetPokemonWazaPpCount(Pokemon*, u32, u8);
extern "C" void pokemon_SetPokemonWazaPp(Pokemon*, u32, u8);
extern "C" void pokemon_SetPokemonWazaDataId(Pokemon*, u32, u16);
extern "C" void pokemon_SetLevel(Pokemon*, u8);
extern "C" void pokemon_SetExp(Pokemon*, u32);
extern "C" u8 pokemon_GetNowExpToLevel(Pokemon*);
extern "C" u8 pokemon_GetSeikaku(Pokemon*);
extern "C" u16 pokemon_GetMaxHp(Pokemon*);
extern "C" u16 pokemon_GetHp(Pokemon*);
extern "C" u32 pokemon_GetExp(Pokemon*);
extern "C" u32 pokemon_GetCatchTrainerRnd(Pokemon*);
extern "C" u32 pokemon_GetRnd(Pokemon*);
extern "C" u16 pokemon_GetPokemonDataId(Pokemon*);
extern "C" u8 pokemonDB_GetTokuseiDataId(u16, u16);
extern "C" u8 pokemonDB_GetGrowDataId(u16);
#endif
