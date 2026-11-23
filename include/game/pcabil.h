#ifndef GAME_PCABIL_H
#define GAME_PCABIL_H

#include <dolphin/types.h>

#ifdef __MWERKS__
#define PC_ABIL(T) T
#else
#define PC_ABIL(T) u16
#ifdef __cplusplus
extern "C" u16 (*PortXD_SpeciesAbility)(u16 species, u16 slot);
#else
extern u16 (*PortXD_SpeciesAbility)(u16 species, u16 slot);
#endif
#endif

#endif
