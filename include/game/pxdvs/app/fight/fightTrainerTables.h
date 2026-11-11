#ifndef GAME_FIGHT_TRAINER_TABLES_H
#define GAME_FIGHT_TRAINER_TABLES_H

#include <dolphin/types.h>

struct FightTrainerAiValueAddsubData {
    u32 value;
    u32 koudouName;
    u32 prefixName;
    u32 name;
    u32 unk10;
};

struct FightTrainerPokemonPartData {
    u32 name;
    u8 unk4[4];
    u8 wazaTypeRevise[14];
    u8 unk16[2];
};

#endif
