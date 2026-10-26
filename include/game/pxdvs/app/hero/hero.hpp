#ifndef HERO_MEMBER_FUNCTIONS_H
#define HERO_MEMBER_FUNCTIONS_H

#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
#include <game/pxdvs/app/hero/heroPokemonGet.hpp>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

class Item;

class Hero {
private:
  char16 heroName[11];
  char16 heroNameCopy[11];
  u32 heroRnd;
  Pokemon partyPokemon[6];
  Item *items[30];
  Item *keyItems[43];
  Item *ballItems[16];
  Item *TMHMItems[64];
  Item *berryItems[46];
  Item *cologneItems[3];
  Item *battleCDItems[60];
  u8 sexDataID;
  u8 homePlace;
  u16 x8e2;
  u32 pokedollars;
  u32 pokecoupons;
  u32 pokecouponsAll;
  u8 badge01Flag;
  u8 badge02Flag;
  u8 badge03Flag;
  u8 badge04Flag;
  u8 badge05Flag;
  u8 badge06Flag;
  u8 badge07Flag;
  u8 badge08Flag;
  u8 hizukiFlag;
  u8 x8f9;
  Item *hizukiItems[10];
  u8 x922[20];
  u8 meetShadowPokemonCount;
  u8 followerID;
  s16 restartPosUnknownHalfWord;
  f32 restartPosGSvecParam1;
  f32 restartPosGSvecParam2;
  f32 restartPosGSvecParam3;
  u32 footStep;
  u32 followerResID;
  u32 followerGrpID;
  u32 followerObjID;
  u8 followerModelLevel;
  u8 heroStyle;
  u16 battleResumeFloorID;
  u8 battleResumeFloorIndex;

public:
  bool itemSort(u8);
  void setBattleResumeFloorIndex(u8);
  u8 getBattleResumeFloorIndex() const;
  void setBattleResumeFloorID(uint);
  u16 getBattleResumeFloorID() const;
  u32 getHeroObjID(s32, s32);
  void setHeroStyle(u8, bool);
  u8 getHeroStyle() const;
  s16 pokemonGet(HeroPokemonGetParam *, bool);
  u32 getLegendPokemonSize() const;
  u16 itemQuantity(u16);
  Hero *getHeroPtr();
  void getRestertPos(GSvec *, short &) const;
  void setRestertPos();
  bool deletePokemon(s32);
  bool setPokemon(const Pokemon *, s32);
  u32 addPokemon(const Pokemon *);
  Pokemon *getPokemon(s32, bool &);
  const Pokemon *getPokemon(s32) const;
  Pokemon *getPokemon(s32);
  void setMeetDarkPokemonCount(u8);
  u8 getMeetDarkPokemonCount() const;
  Item **getDisk();
  void addFootStep(u32);
  u32 getFootStep() const;
  u8 getFollowerModelLevel();
  void setFollowerModelLevel(u8);
  u8 getFollowerID();
  void setFollowerID(u8);
  u32 getFollowerGrpID();
  u32 getFollowerResID();
  void setFollowerObjID(u32);
  void setFollowerGrpID(u32);
  void setFollowerResID(u32);
  u32 getHeroRnd() const;
};

#endif
