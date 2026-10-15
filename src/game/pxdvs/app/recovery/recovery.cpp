#include <game/pxdvs/app/memcard/savedata.hpp>
#include <game/pxdvs/app/pokemon/pokemonBios.hpp>

// This unit was built optimizing for size (uses stmw/lmw).
#pragma optimize_for_size on

extern "C" {

Pokemon* heroBiosGetPokemonPtr(void* hero, u16 index);
u32 heroGetPokeomCount(void* hero);
bool pokemonCheckValid(Pokemon* pokemon);
void pokemonAllKaihuku(Pokemon* pokemon);

u8 revoceryCatchPokemonBall(u16 index) {
    Pokemon* pokemon = heroBiosGetPokemonPtr(savedataGetStatus(0, 2), index);
    if (pokemonCheckValid(pokemon) == false) {
        return 0;
    }
    return pokemonBiosGetCatchBallId(pokemon);
}

void recoveryPokemon(void) {
    void* hero = savedataGetStatus(0, 2);
    u32 count = heroGetPokeomCount(hero);
    for (u32 i = 0; i <= count; i++) {
        pokemonAllKaihuku(heroBiosGetPokemonPtr(hero, i));
    }
}

}
