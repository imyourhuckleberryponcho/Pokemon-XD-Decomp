#include <dolphin/types.h>

class Pokemon;
class FightPokemon;

extern "C" Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon* fightPokemon);

class FightPokemon {
public:
    Pokemon* getPokemonBuffPtr();
};

Pokemon* FightPokemon::getPokemonBuffPtr() {
    return fightPokemon_GetPokemonBuffPtr(this);
}
