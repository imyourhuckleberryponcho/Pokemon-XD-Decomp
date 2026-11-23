#ifndef GAME_PORTXD_FORMS_H
#define GAME_PORTXD_FORMS_H

#include <dolphin/types.h>

#ifdef __MWERKS__
#define PC_BASE_SPECIES(id) (id)
#else
#ifdef __cplusplus
extern "C" u16 PortXD_BaseSpecies(u16 id);
#else
u16 PortXD_BaseSpecies(u16 id);
#endif
#define PC_BASE_SPECIES(id) PortXD_BaseSpecies((u16)(id))
#endif

#endif
