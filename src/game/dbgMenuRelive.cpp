#include <game/pxdvs/app/pokemon/pokemon.hpp>

// Debug menu units were built without the peephole optimizer.
#pragma peephole off

extern "C" {

Pokemon* heroGetStatus(s32, s32, s32);
bool pokemonIsDarkPokemon(Pokemon*);
void preReliveSetParameter(s32, s32, s32);

// Nothing references this, but the original link kept it.
#pragma force_active on
s32 dbgMenuRelive(void) {
    Pokemon* pokemon = heroGetStatus(0, 3, 0);
    if (!pokemonIsDarkPokemon(pokemon)) {
        return 0;
    }
    pokemonSetDp(pokemon, 0.0f);
    preReliveSetParameter(0, 0, 1);
    return 0;
}
#pragma force_active reset

}
