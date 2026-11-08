#ifndef GAME_PPCOPS_H
#define GAME_PPCOPS_H
#include <dolphin/types.h>

#ifdef __MWERKS__
#define GC_DIVU(a, b) ((a) / (b))
#define GC_MODU(a, b) ((a) % (b))
#define GC_DIVS(a, b) ((a) / (b))
#define GC_MODS(a, b) ((a) % (b))
#define GC_SHL(x, n) ((x) << (n))
#define GC_SHRU(x, n) ((x) >> (n))
#define GC_SHRS(x, n) ((x) >> (n))
#else
static inline u32 gc_divu(u32 a, u32 b) { return b != 0 ? a / b : 0; }
static inline u32 gc_modu(u32 a, u32 b) { return a - gc_divu(a, b) * b; }
static inline s32 gc_divs(s32 a, s32 b) {
    if (b == 0 || (a == (s32)0x80000000 && b == -1)) {
        return a < 0 ? -1 : 0;
    }
    return a / b;
}
static inline s32 gc_mods(s32 a, s32 b) { return (s32)((u32)a - (u32)gc_divs(a, b) * (u32)b); }
static inline u32 gc_shl(u32 x, u32 n) { n &= 0x3F; return n >= 32 ? 0 : x << n; }
static inline u32 gc_shru(u32 x, u32 n) { n &= 0x3F; return n >= 32 ? 0 : x >> n; }
static inline s32 gc_shrs(s32 x, u32 n) { n &= 0x3F; return n >= 32 ? (x < 0 ? -1 : 0) : x >> n; }
#define GC_DIVU(a, b) gc_divu((u32)(a), (u32)(b))
#define GC_MODU(a, b) gc_modu((u32)(a), (u32)(b))
#define GC_DIVS(a, b) gc_divs((s32)(a), (s32)(b))
#define GC_MODS(a, b) gc_mods((s32)(a), (s32)(b))
#define GC_SHL(x, n) gc_shl((u32)(x), (u32)(n))
#define GC_SHRU(x, n) gc_shru((u32)(x), (u32)(n))
#define GC_SHRS(x, n) gc_shrs((s32)(x), (u32)(n))
#endif

#ifdef __MWERKS__
#define GC_F2U32(x) ((u32)(x))
#define GC_F2S32(x) ((s32)(x))
#else
static inline u32 gc_f2u32(double x) {
    if (x != x) {
        return 0xFFFFFFFFu;
    }
    if (x < 0.0) {
        return 0;
    }
    if (x >= 4294967296.0) {
        return 0xFFFFFFFFu;
    }
    return (u32)(unsigned long long)x;
}
static inline s32 gc_f2s32(double x) {
    if (x != x) {
        return (s32)0x80000000;
    }
    if (x >= 2147483648.0) {
        return 0x7FFFFFFF;
    }
    if (x <= -2147483649.0) {
        return (s32)0x80000000;
    }
    return (s32)x;
}
#define GC_F2U32(x) gc_f2u32((double)(x))
#define GC_F2S32(x) gc_f2s32((double)(x))
#endif

#endif
