#include <dolphin/types.h>

class FightPokemon;
class FightOutPokemon;

extern "C" {
void fightOutPokemon_SetComboFuncId(FightOutPokemon* fightOutPokemon, u8 id);
u8 fightOutPokemon_GetComboFuncId(FightOutPokemon* fightOutPokemon);
FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon* fightOutPokemon);
}

class FightOutPokemon {
public:
    void setComboFuncId(u8 id);
    u8 getComboFuncId();
    FightPokemon* getFightPokemonPtr();
};

void FightOutPokemon::setComboFuncId(u8 id) {
    fightOutPokemon_SetComboFuncId(this, id);
}

u8 FightOutPokemon::getComboFuncId() {
    return fightOutPokemon_GetComboFuncId(this);
}

FightPokemon* FightOutPokemon::getFightPokemonPtr() {
    return fightOutPokemon_GetFightPokemonPtr(this);
}
