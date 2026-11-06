#include <game/pcret.h>
#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <global.h>

struct savedata {};

extern "C" void *savedataGetStatus(savedata *, PCARG(u16, s32));

#endif
