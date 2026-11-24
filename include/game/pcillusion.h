#ifndef GAME_PCILLUSION_H
#define GAME_PCILLUSION_H
#if !defined(__MWERKS__) && defined(__cplusplus)
struct FightOutPokemon;
struct Pokemon;
extern "C" void PortXD_SetShownAs(FightOutPokemon* fop, Pokemon* shownAs);
extern "C" Pokemon* PortXD_GetShownAs(FightOutPokemon* fop);
extern "C" void (*PortXD_IllusionBroken)(FightOutPokemon* fop);
extern "C" void PortXD_RebuildBattlerModel(FightOutPokemon* fop);
#endif

#endif
