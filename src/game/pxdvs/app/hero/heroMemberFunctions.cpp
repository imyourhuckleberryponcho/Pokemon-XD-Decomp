#include <game/pxdvs/app/hero/hero.hpp>
#include <game/pxdvs/app/hero/heroMove.hpp>
#include <game/pxdvs/app/memcard/savedata.hpp>
#include <game/pxdvs/app/gamedata/gamedata.hpp>
#include <game/pxdvs/app/people/people.hpp>
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemonBios.hpp>

const f32 unkFloat = 57.29578;

extern "C" {
void* heroItemGetItemKindToItemAryPtr(Hero*, u8, u16*, u16*, u8*, u8*);
void* heroItemGetItemDataIdToItemAryPtr(Hero*, u16, u16*, u16*, u8*, u8*);
void itemSortAryByPriority(void*, u16, u32);
u16 itemGetQuantityInAry(void*, u16, u16, u16);
s32 gamedataGetStatus(s32, s32);
void pokemonCreate(Pokemon*, u16, u8, s32);
void pokemonWazaCreate(Pokemon*, u16, u16);
u32 pokemonCreateRndFit(Pokemon*, s32, s32, s32, u32);
void pokemonSetDarkPokemonStatus(Pokemon*, u16);
void memoDataSet(s32, Pokemon*);
s16 heroGetPokemon(Hero*, Pokemon*, bool);
}

bool Hero::itemSort(u8 kind) {
  u16 count;
  void* items = heroItemGetItemKindToItemAryPtr(this, kind, &count, 0, 0, 0);

  if ((u8)(kind - 1) > 1) {
    return false;
  }
  itemSortAryByPriority(items, count, kind);
  return true;
}

void Hero::setBattleResumeFloorIndex(u8 floorIndex) {
  battleResumeFloorIndex = floorIndex;
}

u8 Hero::getBattleResumeFloorIndex() const { return battleResumeFloorIndex; }

void Hero::setBattleResumeFloorID(uint floorID) {
  battleResumeFloorID = floorID;
}

u16 Hero::getBattleResumeFloorID() const { return battleResumeFloorID; }

u32 Hero::getHeroObjID(s32 followerModelLevel, s32 heroStyle) {
  u32 heroObjID = 0x16c90400;

  if (heroStyle < 0) {
    heroStyle = getHeroStyle();
  }
  if (followerModelLevel < 0) {
    followerModelLevel = getFollowerModelLevel();
  }

  if (followerModelLevel == 1) {
    switch (heroStyle) {
      case 0:
        heroObjID = 0x169e0400;
        break;
      case 1:
        heroObjID = 0x1ee20400;
        break;
      case 2:
        heroObjID = 0x16a00400;
        break;
    }
  }
  else {
    switch (heroStyle) {
      case 0:
        heroObjID = 0x16c90400;
        break;
      case 1:
        heroObjID = 0x20250400;
        break;
      case 2:
        heroObjID = 0x169f0400;
        break;
    }
  }

  return heroObjID;
}

void Hero::setHeroStyle(u8 newHeroStyle, bool unkBool) {
  u32 heroObjID;

  if (heroStyle != newHeroStyle) {
    heroStyle = newHeroStyle;

    if (unkBool) {
      heroObjID = 0x16c90400;

      switch (newHeroStyle) {
        case 0:
          heroObjID = 0x16c90400;
          break;
        case 1:
          heroObjID = 0x20250400;
          break;
        case 2:
          heroObjID = 0x169f0400;
          break;
      }

      peopleReadObject(0, 100, heroObjID);
    }
  }
}

u8 Hero::getHeroStyle() const { return heroStyle; }

s16 Hero::pokemonGet(HeroPokemonGetParam * param, bool flag) {
  Pokemon pokemon;
  u16 i;
  s16 slot;
  u32 rndFit;
  DarkPokemon * darkPokemon;

  pokemonCreate(&pokemon, param->pokemonDataID, param->catchLevel, gamedataGetStatus(0, 1));
  pokemon.setFriendLevel(param->friendLevel);
  pokemon.setCatchFloorId(param->catchFloorID);
  pokemon.setCatchLevel(param->catchLevel);
  pokemon.setCatchBallId(4);
  pokemon.setCatchTrainerSex(param->trainerSexID);
  pokemon.setCatchTrainerRnd(param->trainerRnd);
  pokemon.setCatchTrainerNamePtr(param->trainerNamePtr);
  if (param->nicknamePtr != 0) {
    pokemon.setNicknamePtr(param->nicknamePtr);
  }
  pokemon.setExp(param->exp);
  for (i = 0; i < 4; i++) {
    u16 move = param->moves[i];
    if (move != 0 && move != 0x176) {
      pokemonWazaCreate(&pokemon, i, move);
    }
  }
  if (param->shadowPokemonDataID != 0) {
    rndFit = pokemonCreateRndFit(&pokemon, -1, -1, 0, param->trainerRnd);
  } else {
    rndFit = pokemonCreateRndFit(&pokemon, -1, -1, -1, param->trainerRnd);
  }
  pokemonSetStatus(&pokemon, 0, 0x6F, 0, rndFit);
  if (param->shadowPokemonDataID != 0) {
    pokemonSetDarkPokemonStatus(&pokemon, param->shadowPokemonDataID);
  }
  pokemonResetBasisStatus(&pokemon);
  memoDataSet(0, &pokemon);
  slot = heroGetPokemon(this, &pokemon, flag);
  if (param->shadowPokemonDataID != 0 && slot >= 0) {
    darkPokemon = pokemon.getDarkPokemon();
    if (darkPokemon != 0) {
      darkPokemon->setPlace((darkPokemonWhere)1, slot);
      darkPokemon->addStatus((darkPokemonStatus)3);
      if (darkPokemon->getSnatchFromWho() == 0) {
        darkPokemon->setSnatchFromWho((darkPokemonSnatchWho)1);
      }
    }
  }
  return slot;
}

u32 Hero::getLegendPokemonSize() const {
  s32 partySlot = 0;
  u32 legendPokemonSize = 0;
  const Pokemon * pokemonDestAddr;

  do {
    pokemonDestAddr = getPokemon(partySlot);
    if (pokemonDestAddr->checkValid() && pokemonDestAddr->isLegend()) {
      legendPokemonSize++;
    }
    partySlot++;
  }
  while (partySlot < 6);

  return legendPokemonSize;
}

u16 Hero::itemQuantity(u16 itemID) {
  u16 count = 0;
  u16 max = 0;
  u8 flag;
  void* items = heroItemGetItemDataIdToItemAryPtr(this, itemID, &count, &max, &flag, 0);

  if (items == 0) {
    return 0;
  }
  return itemGetQuantityInAry(items, count, itemID, max);
}

Hero *Hero::getHeroPtr() {
  Hero *heroPtr;

  heroPtr = (Hero *)savedataGetStatus(0, 2);
  return heroPtr;
}

void Hero::getRestertPos(GSvec *gsVec, short &unkShortAddr) const {
  gsVec->param1 = restartPosGSvecParam1;
  gsVec->param2 = restartPosGSvecParam2;
  gsVec->param3 = restartPosGSvecParam3;
  unkShortAddr = restartPosUnknownHalfWord;
  return;
}

void Hero::setRestertPos() {
  GSvec heroPosVector;
  GSvec heroRotVector;

  heroMoveGetHeroPos(&heroPosVector);
  heroMoveGetHeroRot(&heroRotVector);
  restartPosGSvecParam1 = heroPosVector.param1;
  restartPosGSvecParam2 = heroPosVector.param2;
  restartPosGSvecParam3 = heroPosVector.param3;
  restartPosUnknownHalfWord = unkFloat * heroRotVector.param2;
  return;
}

bool Hero::deletePokemon(s32 partySlot) {
  Pokemon * pokemonAtSlot;
  bool isPokemonDeleted;

  pokemonAtSlot = getPokemon(partySlot);
  if (!pokemonAtSlot || !pokemonAtSlot->checkValid()) {
    isPokemonDeleted = false;
  }
  else {
    pokemonAtSlot->clear();
    isPokemonDeleted = true;
  }

  return isPokemonDeleted;
}

bool Hero::setPokemon(const Pokemon * pokemonSrcAddr, s32 partySlot) {
  bool isPokemonSet;

  Pokemon * pokemonDestAddr = getPokemon(partySlot);
  if (!pokemonDestAddr || pokemonDestAddr->checkValid()) {
    isPokemonSet = false;
  }
  else {
    pokemonBiosCopy(pokemonDestAddr, pokemonSrcAddr);
    DarkPokemon * darkPokemon = pokemonDestAddr->getDarkPokemon();
    if (darkPokemon) {
      darkPokemon->setPlace(place1, 0);
    }
    isPokemonSet = true;
  }

  return isPokemonSet;
}

u32 Hero::addPokemon(const Pokemon * pokemon) {
  u8 partySlot;

  for (partySlot = 0; partySlot < 6; partySlot++) {
    if (!getPokemon(partySlot)->checkValid()) {
      setPokemon(pokemon, partySlot);
      return partySlot;
    }
  }
  return -1;
}

Pokemon * Hero::getPokemon(s32 partySlot, bool &isHatena) {
  Pokemon * pokemon;
  u16 pokemonDataID;
  bool isValidPokemon;

  pokemon = getPokemon(partySlot);
  isHatena = false;

  if (!pokemon) {
    return nullptr;
  }

  pokemonDataID = pokemon->getPokemonDataId();
  if (!pokemonDataID) {
    return nullptr;
  }

  isValidPokemon = gamedataAttestCheckValid(pokemon->getAttest());
  if (!isValidPokemon) {
    return nullptr;
  }

  if (pokemon->isFuseiFlag()) {
    return nullptr;
  }

  isHatena = pokemon->isHatena();
  return pokemon;
}

const Pokemon *Hero::getPokemon(s32 partySlot) const {
  if (partySlot < 0 || partySlot >= 6) {
    return nullptr;
  }

  return &partyPokemon[partySlot];
}

Pokemon *Hero::getPokemon(s32 partySlot) {
  if (partySlot < 0 || partySlot >= 6) {
    return nullptr;
  }

  return &partyPokemon[partySlot];
}

void Hero::setMeetDarkPokemonCount(u8 shadowPokemonCount) {
  meetShadowPokemonCount = shadowPokemonCount;
}

u8 Hero::getMeetDarkPokemonCount() const { return meetShadowPokemonCount; }

Item **Hero::getDisk() { return battleCDItems; }

void Hero::addFootStep(u32 footstepsToAdd) {
  u32 newFootStepAmount;
  u32 currFootStepAmount;
  u32 sum;

  currFootStepAmount = footStep;
  newFootStepAmount = -1;
  sum = currFootStepAmount + footstepsToAdd;
  if (currFootStepAmount <= sum) {
    newFootStepAmount = sum;
  }
  footStep = newFootStepAmount;
}

u32 Hero::getFootStep() const { return footStep; }

u8 Hero::getFollowerModelLevel() { return followerModelLevel; }

void Hero::setFollowerModelLevel(u8 followModelLvl) {
  followerModelLevel = followModelLvl;
}

u8 Hero::getFollowerID() { return followerID; }

void Hero::setFollowerID(u8 followID) { followerID = followID; }

u32 Hero::getFollowerGrpID() { return followerGrpID; }

u32 Hero::getFollowerResID() { return followerResID; }

void Hero::setFollowerObjID(u32 objID) { followerObjID = objID; }

void Hero::setFollowerGrpID(u32 grpID) { followerGrpID = grpID; }

void Hero::setFollowerResID(u32 resID) { followerResID = resID; }

u32 Hero::getHeroRnd() const { return heroRnd; }
