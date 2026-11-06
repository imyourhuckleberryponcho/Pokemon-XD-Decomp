#include <dolphin/types.h>

struct Pokemon;
struct FightPokemon;

extern "C" Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon* fightPokemon);

struct FightPokemon {
public:
    Pokemon* getPokemonBuffPtr();
};

Pokemon* FightPokemon::getPokemonBuffPtr() {
    return fightPokemon_GetPokemonBuffPtr(this);
}
