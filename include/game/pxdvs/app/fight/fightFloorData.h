#ifndef GAME_FIGHTFLOORDATA_H
#define GAME_FIGHTFLOORDATA_H
#include <dolphin/types.h>
#include <game/fightfloor.h>
#include <game/pxdvs/app/fight/fightJoutaiData.h>
#include <game/pxdvs/app/fight/fightSideData.h>

struct FightOutPokemon;

#ifndef FIGHT_FLOOR_POKEMON
struct FightFloorPokemonBytes {
    u8 data[0xC4];
};
#define FIGHT_FLOOR_POKEMON FightFloorPokemonBytes
#endif

struct FightFloorStock {
    FIGHT_FLOOR_POKEMON pokemon;
    u8 ballID;
    u8 padC5[3];
};

class FIGHT_FLOOR {
public:

    FightJoutai joutai[1];
    u16 turnCount;
    u16 encountDataId;
    FIGHT_SIDE sides[2];
    FightOutPokemon* attackPokemon;
    FightOutPokemon* defensePokemon;
    FightOutPokemon* escapePokemon;
    FightOutPokemon* irekaePokemon;
    FightOutPokemon* kizetuPokemon;
    FightOutPokemon* tuikakoukaPokemon;
    FightOutPokemon* tokuseiPokemon;
    FightOutPokemon* itemPokemon;
    FightOutPokemon* appointPokemon;
    void* appointTrainer;
    void* appointWaza;
    void* appointSide;
    void* appointItem;
    u32 attackMsgId;
    u32 criticalMsgId;
    u32 wazakoukaMsgId;
    u32 appointMsgId;
    u16 appointPokemonDataId;
    u16 appointWazaDataId;
    u16 appointItemDataId;
    u16 appointTokuseiDataId;
    s16 fightPokemonEntryCnt;
    u8 unkDE42[2];
    FightOutPokemon* fightOutPokemon[8];
    u16 firstAttackRnd;
    u8 stockPokemonNum;
    u8 unkDE67;
    FightFloorStock stock[6];
};

#define FIGHT_FLOOR_OFFSET_OF(f) ((u32)&((FIGHT_FLOOR*)0)->f)
#define FIGHT_FLOOR_CHECK(name, cond) typedef char name[(cond) ? 1 : -1]
FIGHT_FLOOR_CHECK(FightFloorCheckSize, sizeof(FIGHT_FLOOR) == FIGHT_FLOOR_SIZE);
FIGHT_FLOOR_CHECK(FightFloorCheckStock, sizeof(FightFloorStock) == 0xC8);
#ifndef __MWERKS__
#include <stddef.h>
static_assert(offsetof(FIGHT_FLOOR, sides) == 0x14, "FIGHT_FLOOR layout");
static_assert(offsetof(FIGHT_FLOOR, attackPokemon) == 0xE288, "FIGHT_FLOOR layout (PC)");
static_assert(offsetof(FIGHT_FLOOR, attackMsgId) == 0xE2F0, "FIGHT_FLOOR layout (PC)");
static_assert(offsetof(FIGHT_FLOOR, fightPokemonEntryCnt) == 0xE308, "FIGHT_FLOOR layout (PC)");
static_assert(offsetof(FIGHT_FLOOR, fightOutPokemon) == 0xE310, "FIGHT_FLOOR layout (PC)");
static_assert(offsetof(FIGHT_FLOOR, firstAttackRnd) == 0xE350, "FIGHT_FLOOR layout (PC)");
static_assert(offsetof(FIGHT_FLOOR, stock) == 0xE354, "FIGHT_FLOOR layout (PC)");
#else
FIGHT_FLOOR_CHECK(FightFloorCheckSides, FIGHT_FLOOR_OFFSET_OF(sides) == 0x14);
FIGHT_FLOOR_CHECK(FightFloorCheckAttack, FIGHT_FLOOR_OFFSET_OF(attackPokemon) == FIGHT_FLOOR_SIDES_END);
FIGHT_FLOOR_CHECK(FightFloorCheckMsg, FIGHT_FLOOR_OFFSET_OF(attackMsgId) == 0xDE28);
FIGHT_FLOOR_CHECK(FightFloorCheckEntry, FIGHT_FLOOR_OFFSET_OF(fightPokemonEntryCnt) == 0xDE40);
FIGHT_FLOOR_CHECK(FightFloorCheckOut, FIGHT_FLOOR_OFFSET_OF(fightOutPokemon) == 0xDE44);
FIGHT_FLOOR_CHECK(FightFloorCheckRnd, FIGHT_FLOOR_OFFSET_OF(firstAttackRnd) == 0xDE64);
FIGHT_FLOOR_CHECK(FightFloorCheckStockOff, FIGHT_FLOOR_OFFSET_OF(stock) == 0xDE68);
#endif

#endif
