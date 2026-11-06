#include <game/pcret.h>
#ifndef GS_FLAG_H
#define GS_FLAG_H

#include <global.h>

extern "C" bool GSflagGet(u32);
extern "C" void GSflagSet(u32, PCARG(bool, u32));

#endif
