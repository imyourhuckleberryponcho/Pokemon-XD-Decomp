#include <dolphin/types.h>

#pragma peephole off

struct Pokemon {
    u8 unk0[0xC4];
};

extern "C" {

void menuDbgItemCreate(void);
s32 menuOpen(s32 menuID, s32);
void heroAddPokecoupon(void* hero, s32 amount);
void heroAddPokedoru(void* hero, s32 amount);
bool fightIsFight(void);
void pokemonInit(Pokemon* pokemon);
s32 dbgMenuPokemonEditSub(Pokemon* pokemon, s32, s32, s32, s32, s32);
void heroCatchPokemon(void* hero, Pokemon* pokemon, s32, s32, s32);
Pokemon* heroGetStatus(void* hero, s32, s32);

static Pokemon pokemon;
static u8 firstFlag = 1;

#pragma force_active on

s32 dbgMenuHeroCreateItem(void) {
    menuDbgItemCreate();
    return 0;
}

s32 dbgMenuHeroIncCoupon(void) {
    s32 amount = menuOpen(2, 1);
    if (amount == -1) {
        return 0;
    }
    heroAddPokecoupon(0, amount);
    return 0;
}

s32 dbgMenuHeroIncMoney(void) {
    s32 amount = menuOpen(2, 1);
    if (amount == -1) {
        return 0;
    }
    heroAddPokedoru(0, amount);
    return 0;
}

s32 dbgMenuHeroPokemonAdd(void) {
    if (fightIsFight() == 1) {
        return -1;
    }
    if (firstFlag) {
        pokemonInit(&pokemon);
        firstFlag = 0;
    }
    if (dbgMenuPokemonEditSub(&pokemon, 0, 0, 0, 0, 0) < 0) {
        return -1;
    }
    heroCatchPokemon(0, &pokemon, 0, 4, 1);
    return -1;
}

s32 dbgMenuHeroPokemonSelect5(void) {
    Pokemon* pokemon;
    if (fightIsFight() == 1) {
        return -1;
    }
    pokemon = heroGetStatus(0, 3, 5);
    if (pokemon == NULL) {
        return -1;
    }
    return dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
}

s32 dbgMenuHeroPokemonSelect4(void) {
    Pokemon* pokemon;
    if (fightIsFight() == 1) {
        return -1;
    }
    pokemon = heroGetStatus(0, 3, 4);
    if (pokemon == NULL) {
        return -1;
    }
    return dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
}

s32 dbgMenuHeroPokemonSelect3(void) {
    Pokemon* pokemon;
    if (fightIsFight() == 1) {
        return -1;
    }
    pokemon = heroGetStatus(0, 3, 3);
    if (pokemon == NULL) {
        return -1;
    }
    return dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
}

s32 dbgMenuHeroPokemonSelect2(void) {
    Pokemon* pokemon;
    if (fightIsFight() == 1) {
        return -1;
    }
    pokemon = heroGetStatus(0, 3, 2);
    if (pokemon == NULL) {
        return -1;
    }
    return dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
}

s32 dbgMenuHeroPokemonSelect1(void) {
    Pokemon* pokemon;
    if (fightIsFight() == 1) {
        return -1;
    }
    pokemon = heroGetStatus(0, 3, 1);
    if (pokemon == NULL) {
        return -1;
    }
    return dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
}

s32 dbgMenuHeroPokemonSelect0(void) {
    Pokemon* pokemon;
    if (fightIsFight() == 1) {
        return -1;
    }
    pokemon = heroGetStatus(0, 3, 0);
    if (pokemon == NULL) {
        return -1;
    }
    return dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
}

#pragma force_active reset

}
