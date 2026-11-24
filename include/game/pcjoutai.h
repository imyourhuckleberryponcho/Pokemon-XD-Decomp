#ifndef GAME_PCJOUTAI_H
#define GAME_PCJOUTAI_H
#define PC_JOUTAI_SLOTS 0x34
#define PC_JOUTAI_EXTRA_SLOTS 8
#define PC_JOUTAI_CARRIED 0x57

#define PC_JOUTAI_UNTOUCHABLE 0x58

#define PC_JOUTAI_STRONG_WINDS 0x59

#define PC_WEATHER_STRONG_WINDS 6

#if !defined(__MWERKS__) && defined(__cplusplus)
struct FightOutPokemon;
extern "C" void* (*PortXD_CarriedSkipSeq)(FightOutPokemon* p);
extern "C" void (*PortXD_CarriedChanged)(FightOutPokemon* p, int carried);
extern "C" void PortXD_SetCarried(FightOutPokemon* target, FightOutPokemon* carrier);
extern "C" void PortXD_ReleaseCarried(FightOutPokemon* target);
extern "C" void PortXD_SetStrongWinds(int on);
extern "C" void* (*PortXD_StrongWindsBlockSeq)(void);
#endif

#endif
