#ifndef GAME_FIGHTTRAINERDATA_H
#define GAME_FIGHTTRAINERDATA_H
#include <dolphin/types.h>
#include <game/fightfloor.h>
#ifndef FIGHT_TRAINER_OPAQUE_RECORDS
#include <game/pxdvs/app/fight/fightPokemonData.h>
#else
struct Sequence;
struct FightPokemon {
    void* motoPokemon;
    u8 rest[FIGHT_TRAINER_FIGHT_POKEMON_SIZE - sizeof(void*)];
};
struct FightOutPokemon {
    void* motoFightPokemon;
    u8 rest[FIGHT_TRAINER_FIGHTOUT_POKEMON_SIZE - sizeof(void*)];
};
struct FightAction {
    void* slot0;
    u8 rest[FIGHT_TRAINER_ENEMY_POKEMON - FIGHT_TRAINER_FIGHT_ACTION_BUFF - sizeof(void*)];
};
#endif

struct FightTrainerEnemyPokemon {
    s16 fightEntryId;
    u8 storeWazaNum;
    u8 expectWazaNum;
    u16 storeWaza[4];
    u16 expectWaza[8];
    u8 tokuseiFlag;
    u8 unk1D;
    u16 storeTokuseiData;
    u8 nowhp1banhikuiFlag;
    u8 lv1banhikuiFlag;
    u8 defense1banhikuiFlag;
    u8 badwazaHaveFlag;
    u8 param1bantakaiFlag;
    u8 unk25;
};

struct FightTrainer {
    u16 fightTrainerDataId;
    u8 unk2[2];
    u8 hero[0x978];
    FightPokemon fightPokemon[6];
    FightOutPokemon fightoutPokemon[2];
    FightOutPokemon fightoutPokemonBuff;
    u8 okaneBai;
    u8 nigeruCount;
    u8 unk353A[2];
    u32 koban;
    u8 controllerId;
    u8 unk3541[3];
    Sequence* sequence;
    FightAction fightActionBuff;
    FightTrainerEnemyPokemon enemyPokemon[12];
    u8 unk3740[4];
};

#define FIGHT_TRAINER_OFFSET_OF(f) ((u32)&((FightTrainer*)0)->f)
#define FIGHT_TRAINER_CHECK(name, cond) typedef char name[(cond) ? 1 : -1]
FIGHT_TRAINER_CHECK(FightTrainerCheckSize, sizeof(FightTrainer) == FIGHT_TRAINER_SIZE);
FIGHT_TRAINER_CHECK(FightTrainerCheckPokemon, sizeof(FightPokemon) == FIGHT_TRAINER_FIGHT_POKEMON_SIZE);
FIGHT_TRAINER_CHECK(FightTrainerCheckOutPokemon, sizeof(FightOutPokemon) == FIGHT_TRAINER_FIGHTOUT_POKEMON_SIZE);
FIGHT_TRAINER_CHECK(FightTrainerCheckEnemy, sizeof(FightTrainerEnemyPokemon) == 0x26);
#ifndef __MWERKS__
#include <stddef.h>
static_assert(offsetof(FightTrainer, fightPokemon) == FIGHT_TRAINER_FIGHT_POKEMON, "fightfloor.h");
static_assert(offsetof(FightTrainer, fightoutPokemon) == FIGHT_TRAINER_FIGHTOUT_POKEMON, "fightfloor.h");
static_assert(offsetof(FightTrainer, fightoutPokemonBuff) == FIGHT_TRAINER_FIGHTOUT_BUFF, "fightfloor.h");
static_assert(offsetof(FightTrainer, okaneBai) == FIGHT_TRAINER_OKANE_BAI, "fightfloor.h");
static_assert(offsetof(FightTrainer, nigeruCount) == FIGHT_TRAINER_NIGERU_COUNT, "fightfloor.h");
static_assert(offsetof(FightTrainer, koban) == FIGHT_TRAINER_KOBAN, "fightfloor.h");
static_assert(offsetof(FightTrainer, controllerId) == FIGHT_TRAINER_CONTROLLER_ID, "fightfloor.h");
static_assert(offsetof(FightTrainer, sequence) == FIGHT_TRAINER_SEQUENCE, "fightfloor.h");
static_assert(offsetof(FightTrainer, fightActionBuff) == FIGHT_TRAINER_FIGHT_ACTION_BUFF, "fightfloor.h");
static_assert(offsetof(FightTrainer, enemyPokemon) == FIGHT_TRAINER_ENEMY_POKEMON, "fightfloor.h");
#else
FIGHT_TRAINER_CHECK(FightTrainerCheckFP, FIGHT_TRAINER_OFFSET_OF(fightPokemon) == FIGHT_TRAINER_FIGHT_POKEMON);
FIGHT_TRAINER_CHECK(FightTrainerCheckFOP, FIGHT_TRAINER_OFFSET_OF(fightoutPokemon) == FIGHT_TRAINER_FIGHTOUT_POKEMON);
FIGHT_TRAINER_CHECK(FightTrainerCheckBuff, FIGHT_TRAINER_OFFSET_OF(fightoutPokemonBuff) == FIGHT_TRAINER_FIGHTOUT_BUFF);
FIGHT_TRAINER_CHECK(FightTrainerCheckOkane, FIGHT_TRAINER_OFFSET_OF(okaneBai) == FIGHT_TRAINER_OKANE_BAI);
FIGHT_TRAINER_CHECK(FightTrainerCheckNigeru, FIGHT_TRAINER_OFFSET_OF(nigeruCount) == FIGHT_TRAINER_NIGERU_COUNT);
FIGHT_TRAINER_CHECK(FightTrainerCheckKoban, FIGHT_TRAINER_OFFSET_OF(koban) == FIGHT_TRAINER_KOBAN);
FIGHT_TRAINER_CHECK(FightTrainerCheckCtrl, FIGHT_TRAINER_OFFSET_OF(controllerId) == FIGHT_TRAINER_CONTROLLER_ID);
FIGHT_TRAINER_CHECK(FightTrainerCheckSeq, FIGHT_TRAINER_OFFSET_OF(sequence) == FIGHT_TRAINER_SEQUENCE);
FIGHT_TRAINER_CHECK(FightTrainerCheckAction, FIGHT_TRAINER_OFFSET_OF(fightActionBuff) == FIGHT_TRAINER_FIGHT_ACTION_BUFF);
FIGHT_TRAINER_CHECK(FightTrainerCheckEnemyOff, FIGHT_TRAINER_OFFSET_OF(enemyPokemon) == FIGHT_TRAINER_ENEMY_POKEMON);
#endif

#endif
