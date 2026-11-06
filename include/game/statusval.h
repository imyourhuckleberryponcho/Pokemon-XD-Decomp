#ifndef GAME_STATUSVAL_H
#define GAME_STATUSVAL_H
#ifdef __MWERKS__
typedef u32 StatusU32;
typedef s32 StatusS32;
#else
#include <stdint.h>
typedef uintptr_t StatusU32;
typedef intptr_t StatusS32;
#endif
#endif
