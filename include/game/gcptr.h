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

#ifdef __MWERKS__
#define PC_PTR(T, v) ((T)(v))
#define PC_PTRV(v) (v)
#else
#ifndef PORT_PTR32_HOOK
static inline void* pc_ptr32(u32 v) { return (void*)(uintptr_t)v; }
#endif
#define PC_PTR(T, v) ((T)pc_ptr32((u32)(v)))
#define PC_PTRV(v) pc_ptr32((u32)(v))
#endif
#endif
