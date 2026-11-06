#ifndef GAME_POKEMONSEIKAKU_H
#define GAME_POKEMONSEIKAKU_H

#include <dolphin/types.h>

struct PokemonSeikakuDataBios {
    s8 reliveFightout;
    s8 reliveWalk;
    s8 reliveCall;
    s8 reliveSodateya;
    s8 reliveNadenade;
    u8 phyAtkRateDataId;
    u8 phyDefRateDataId;
    u8 speAtkRateDataId;
    u8 speDefRateDataId;
    u8 nimblenessRateDataId;
    u8 unk0A[0x14 - 0x0A];
    u32 name;
    u8 unk18[0x28 - 0x18];
};

struct PokemonSeikakuRateBios {
    u8 kake;
    u8 waru;
};

#endif
