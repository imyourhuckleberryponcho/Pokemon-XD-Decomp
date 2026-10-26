#ifndef POKEMON_H
#define POKEMON_H

#include <global.h>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

class Hero;

struct PokemonStatusRnd {
  u8 maxHp;
  u8 phyAtk;
  u8 phyDef;
  u8 speAtk;
  u8 speDef;
  u8 nimbleness;

  void setNimbleness(u8 data);
  void setSpeDef(u8 data);
  void setSpeAtk(u8 data);
  void setPhyDef(u8 data);
  void setPhyAtk(u8 data);
  void setMaxHp(u8 data);
  u32 getNimbleness() const;
  u32 getSpeDef() const;
  u32 getSpeAtk() const;
  u32 getPhyDef() const;
  u32 getPhyAtk() const;
  u32 getMaxHp() const;
};

union Ribbon {
  struct {
    u32 champ : 1;
    u32 winning : 1;
    u32 victory : 1;
    u32 bromide : 1;
    u32 ganba : 1;
    u32 marine : 1;
    u32 land : 1;
    u32 sky : 1;
    u32 country : 1;
    u32 national : 1;
    u32 earth: 1;
    u32 world : 1;
    u32 amari : 8;
    u32 unk2 : 8;
  } bits;
  u32 allBits;
};
struct Attest {
  u8 unk[4];
};

#define MAX_EXPAND_STATUS 2
struct ExpandStatus {
  u8 style;
  u8 beautiful;
  u8 cute;
  u8 clever;
  u8 strong;
};

union PokemonFlags {
  struct {
    u8 tamago: 1;
    u8 tokusei: 1;
    u8 fusei : 1;
    u8 unk : 5;
  } bits;
  u8 allBits;
};

#define MAX_WAZA 4
struct PokemonWaza {
  u16 dataId;
  u8 pp;
  u8 ppCount;
};

struct Pokemon {
  u16 dataID;
  u16 itemDataID;
  u16 hp;
  u16 friendLevel;
  u16 catchFloorId;
  u16 amari;
  u16 para1Amari;
  u8 catchLevel;
  u8 catchBallId;
  u8 catchTrainerSex;
  u8 level;
  u8 fur;
  u8 pokerus;
  u8 pcboxMark;
  u8 mailId;
  u8 condition;
  u8 conditionCount;
  u8 conditionTurn;
  u8 conditionTurnNow;
  u8 flagAmari;
  s8 unk1[2];
  PokemonFlags flags;
  u32 exp;
  u32 catchTrainerRnd;
  u32 rnd;
  u32 conditionAmari;

  u32 eventGetFlag;
  Attest attest;

  char catchTrainerName[11];
  s8 unk2[11];
  char nickname[11];
  s8 unk3[11];
  char nicknameOrg[11];
  s8 unk4[11];

  Ribbon ribbon;
  PokemonWaza wazas[MAX_WAZA];
  u16 maxHp;
  u16 phyAtk;
  u16 phyDef;
  u16 speAtk;
  u16 speDef;
  u16 nimbleness;
  u16 maxHpEffort;
  u16 phyAtkEffort;
  u16 phyDefEffort;
  u16 speAtkEffort;
  u16 speDefEffort;
  u16 nimblenessEffort;
  PokemonStatusRnd statusRnd;
  ExpandStatus expandStatus[MAX_EXPAND_STATUS];
  u16 fightTrainerPokemonDataId;
  u16 darkPokemonDataID;
  u8 comboPartnerAll;
  s8 unk5[7];

  u16 getAmari() const;
  u8 getPcboxMark() const;
  u16 getPara1Amari() const;
  u16 getDarkPokemonDataId() const;
  u16 getDarkpokemonDataID() const;
  u16 getItemDataId() const;
  u16 getPokemonDataId() const;
  u16 getHp() const;
  u16 getMaxHp() const;
  u16 getFriendLevel() const;
  u8  getLevel() const;
  u8  getCondition() const;
  u8  getConditionCount() const;
  u8  getConditionTurn() const;
  u8  getConditionTurnNow() const;
  u16 getNimbleness() const;
  u16 getSpeDef() const;
  u16 getSpeAtk() const;
  u16 getPhyDef() const;
  u16 getPhyAtk() const;
  u16 getMaxHpEffort() const;
  u16 getNimblenessEffort() const;
  u16 getSpeDefEffort() const;
  u16 getSpeAtkEffort() const;
  u16 getPhyDefEffort() const;
  u16 getPhyAtkEffort() const;
  u32 getRnd() const;
  u32 getCatchTrainerRnd() const;
  const Ribbon* getRibbon() const;
  Ribbon* getRibbon();
  Attest* getAttest();
  char* getNicknamePtr();
  bool isFuseiFlag() const;
  PokemonWaza* getPokemonWaza(u16);
  u8 getSpeDefRnd() const;
  u8 getSpeAtkRnd() const;
  u8 getPhyDefRnd() const;
  u8 getPhyAtkRnd() const;
  u8 getMaxHpRnd() const;
  u8 getNimblenessRnd() const;
  u32 getPoolFriendLevel() const;
  u32 getPoolExp() const;
  s32 getDarkPointDirect() const;

  void setPara1Amari(u16);
  void setAmari(u16);
  void setFriendLevel(u16);
  void setPoolFriendLevel(u16);
  void setPoolExp(u32);
  void setNimbleness(u16);
  void setSpeDef(u16);
  void setSpeAtk(u16);
  void setPhyDef(u16);
  void setPhyAtk(u16);
  void setMaxHp(u16);
  void setHp(u16);
  void setMaxHpEffort(u16);
  void setNimblenessEffort(u16);
  void setSpeDefEffort(u16);
  void setSpeAtkEffort(u16);
  void setPhyDefEffort(u16);
  void setPhyAtkEffort(u16);
  void setSpeDefRnd(u16);
  void setSpeAtkRnd(u16);
  void setPhyDefRnd(u16);
  void setPhyAtkRnd(u16);
  void setMaxHpRnd(u16);
  void setNimblenessRnd(u16);
  void setDarkPointDirect(s32);
  void setConditionTurnNow(u8);
  void setConditionTurn(u8);
  void setConditionCount(u8);
  void setCondition(u8);
  void setPcboxMark(u8);
  void setItemDataId(u16);
  void setExp(u32);
  void setCatchTrainerRnd(u32);
  void setCatchTrainerSex(u8);
  void setCatchBallId(u8);
  void setCatchLevel(u8);
  void setCatchFloorId(u16);
  void setCatchTrainerNamePtr(u16*);
  void setNicknamePtr(u16*);
  void setRnd(u32);
  void setNicknameOrgPtr(u16*);
  void setReversMode(bool);
  bool isReversMode() const;
  void setDarkPoint(f32);
  f32 getDarkPoint() const;
  u8 getSex() const;
  bool isTokuseiFlag() const;
  static bool isRareParam(u32, u32);
  bool isRare() const;
  u8 getSeikaku() const;

  bool isHatena() const;
  Pokemon * getPokemon(Hero *, s32);
  DarkPokemon * getDarkPokemon();
  DarkPokemon * getDarkPokemon() const;
  bool checkValid() const;
  void clear();
  bool isLegend() const;
  bool isDarkPokemon() const;
  void initCondition();
  void copyCondition(const Pokemon*);
  void* getPokemonDataPtr() const;
};

extern "C" void pokemonSetDp(Pokemon*, f32);

extern "C" void pokemonSetTokuseiFlag(Pokemon* , u32);
extern "C" void pokemonInitAry(u32, u16);
extern "C" void pokemonInit(u32);
extern "C" void pokemonInitDarkPokemon(Pokemon*);
extern "C" void pokemonInitJoutai(Pokemon*);
extern "C" void pokemonWazaInitAry(Pokemon* ,u16);
extern "C" void pokemonWazaInit(Pokemon* ,u32);
extern "C" u8 pokemonWazaGetMaxPP(Pokemon*, u32);
extern "C" u32 pokemonCheckRare(Pokemon*);
extern "C" void pokemonGrowBasisStatus(Pokemon*,u32);
extern "C" void pokemonResetBasisStatus(Pokemon*);
extern "C" void pokemonSetStatus(Pokemon*, u32, u16, u32, u32);
extern "C" u16 pokemonGetStatus(Pokemon*, u32, u16, u32);
extern "C" u32 pokemonAdjustValueBySeikaku(u32, u16, u32);
static u8 _pokemonGetSeikaku(Pokemon*);
extern "C" u8 pokemonGetSeikakuAsRnd(u32);
static u8 _pokemonGetHinsi(Pokemon*);
static void _pokemonSetLevelBasisStatus(Pokemon*, u8);
static u16 _pokemonGetLevelOneStatus(Pokemon*, u8, u16, u16, u16, u16, long);
extern "C" u16 pokemonCreateBasisStatus(u16, u8, u16, u8, s32);
static u8 _pokemonGetNowExpToLevel(Pokemon*);
extern "C" u8 pokemonGetExpToLevel(u8, u32);
static int _pokemonGetLevelToExp(u8, u8);
extern "C" int pokemonCheckRareRnd(unsigned long, unsigned long);
static int _pokemonCheckRare(unsigned long, unsigned long);

#endif
