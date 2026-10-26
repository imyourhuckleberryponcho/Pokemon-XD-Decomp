#ifndef HERO_POKEMON_GET_H
#define HERO_POKEMON_GET_H

#include <global.h>

struct HeroPokemonGetParam {
  u8 trainerSexID;
  u8 catchLevel;
  u16 pokemonDataID;
  u16 shadowPokemonDataID;
  u16 friendLevel;
  u16 moves[4];
  u32 trainerRnd;
  char16 *trainerNamePtr;
  char16 *nicknamePtr;
  u32 catchFloorID;
  u32 exp;
};

#endif
