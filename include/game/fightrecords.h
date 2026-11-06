#ifndef GAME_FIGHTRECORDS_H
#define GAME_FIGHTRECORDS_H
#include <dolphin/types.h>

struct FightOutPokemonEnemy {
    void* target;
    u16 oumuWaza;
    u16 initHp;
    u16 damage;
    u16 padA;
};

#ifdef __MWERKS__
#define FIGHT_OUT_POKEMON_SIZE 0x894
#else
#define FIGHT_OUT_POKEMON_SIZE 0x8D8
#endif

#endif
