#include <game/pxdvs/app/memcard/savedata.hpp>
#include <game/pxdvs/app/pokemon/pokemonBios.hpp>

// This unit was built optimizing for size (uses stmw/lmw).
#pragma optimize_for_size on

extern "C" {


BOOL exribbonSetEarthRibbon(Pokemon* pokemon) {
    pokemonBiosSetEarthRibbon(pokemon, 1);
    u8* exribbon = (u8*)savedataGetStatus(0, 16);
    if (exribbon[5] == 0) {
        exribbon[5] = 45;
    }
    return TRUE;
}

BOOL exribbonSetNarionalRibbon(Pokemon* pokemon) {
    pokemonBiosSetNationalRibbon(pokemon, 1);
    u8* exribbon = (u8*)savedataGetStatus(0, 16);
    if (exribbon[4] == 0) {
        exribbon[4] = 44;
    }
    return TRUE;
}

void exribbonSetNo(u32 index, u8 no) {
    u8* exribbon = (u8*)savedataGetStatus(0, 16);
    if (exribbon[index] == 0 && no != 0) {
        exribbon[index] = no;
    }
}

u8 exribbonGetNo(u32 index) {
    u8* exribbon = (u8*)savedataGetStatus(0, 16);
    return exribbon[index];
}

void exribbonInit(u8* exribbon) {
    if (exribbon == NULL) {
        exribbon = (u8*)savedataGetStatus(0, 16);
    }
    for (s32 i = 0; i < 11; i++) {
        exribbon[i] = 0;
    }
}

}
