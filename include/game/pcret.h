#ifndef GAME_PCRET_H
#define GAME_PCRET_H
#ifdef __MWERKS__
#define PCRET(T) T
#else
#define PCRET(T) PCRET_##T
#define PCRET_bool int
#define PCRET_BOOL int
#define PCRET_u8 u32
#define PCRET_s8 s32
#define PCRET_u16 u32
#define PCRET_s16 s32
#define PCRET_char s32
#endif

#ifdef __MWERKS__
#define PCARG(GC, PC) GC
#else
#define PCARG(GC, PC) PC
#endif
#endif
