#ifndef GAME_GCPTR_H
#define GAME_GCPTR_H
#ifdef __MWERKS__
typedef u32 GCuptr;
typedef s32 GCsptr;
typedef int GCsint;
#else
#include <stdint.h>
typedef uintptr_t GCuptr;
typedef intptr_t GCsptr;
typedef intptr_t GCsint;
#endif
#endif
