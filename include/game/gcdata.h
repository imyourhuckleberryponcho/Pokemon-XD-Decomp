#ifndef GAME_GCDATA_H
#define GAME_GCDATA_H

#include <dolphin/types.h>















#ifdef __MWERKS__

typedef u16 gc_be16;
typedef s16 gc_bes16;
typedef u32 gc_be32;
typedef s32 gc_bes32;
typedef f32 gc_bef32;
#define gc_ptr32(T) T*
#define GC_ADDR32(p) ((u32)(p))
#define GC_BE32(x) (x)
#define GC_ADDBE32(lv, v) ((lv) += (v))
#define GC_BE16(x) (x)
#define GC_BES16(x) (x)
#define GC_BES32(x) (x)
#define GC_BEF32(x) (x)
#define GC_PTR(T, x) (x)
#define gc_vec(T) T
#define GC_VEC3(dst, src) ((dst) = (src))
#define GC_MTXCOPY(dst, src) memcpy((dst), (src), sizeof(Mtx))
#define gc_mtxptr32 MtxPtr
#define gc_enum32(T) T
#define GC_SETBE16(lv, v) ((lv) = (v))
#define GC_SETBE32(lv, v) ((lv) = (v))
#define GC_SETBEF32(lv, v) ((lv) = (v))
#define GC_SETPTR(lv, v) ((lv) = (v))
#define GC_FIXF32(lv) ((void)0)
#define GC_FIXF32N(p, n) ((void)0)
#define GC_VEC3P(T, pv) (pv)
#define GC_VEC3AP(T, pv, n) (pv)
#define GC_BYTE4(i) (i)
#define GC_RAW32(x) (x)
#define GC_BYTES32(p) (*(u32*)(p))
#define GC_SETBYTES32(p, v) (*(u32*)(p) = (v))


#define M2C_NAMED(expr, type_ptr, offset, path) M2C_FIELD(expr, type_ptr, offset)
#define gc_s16x4(T) T
#define GC_S16X4P(T, p) (p)
#define GC_BEC32(v) v
#define GC_BECF32_ZERO 0.0F
#define GC_FIX32(lv) ((void)0)
#define GC_FIX16(lv) ((void)0)

#else

#ifdef __cplusplus
extern "C" void OSPanic(const char* file, int line, const char* msg, ...);
#else
void OSPanic(const char* file, int line, const char* msg, ...);
#endif

static inline u16 gc_rd16(const u8* b) { return (u16)((b[0] << 8) | b[1]); }
static inline u32 gc_rd32(const u8* b) { return ((u32)b[0] << 24) | ((u32)b[1] << 16) | ((u32)b[2] << 8) | b[3]; }
static inline void gc_wr16(u8* b, u16 v) { b[0] = (u8)(v >> 8); b[1] = (u8)v; }
static inline void gc_wr32(u8* b, u32 v) { b[0] = (u8)(v >> 24); b[1] = (u8)(v >> 16); b[2] = (u8)(v >> 8); b[3] = (u8)v; }


static inline u32 gc_addr32(const void* p) {
    uintptr_t v = (uintptr_t)p;
    if (v > 0xFFFFFFFFu) {
        OSPanic(__FILE__, __LINE__, "gc_addr32: address above 4 GB stored in a 4-byte GameCube slot");
    }
    return (u32)v;
}
#define GC_ADDR32(p) gc_addr32(p)

#define GC_BYTES32(p) gc_rd32((const u8*)(p))

#define GC_SETBYTES32(p, v) gc_wr32((u8*)(p), (u32)(v))
#define M2C_NAMED(expr, type_ptr, offset, path) (*(type_ptr)&(expr)->path)


#define GC_BYTE4(i) (3 - (i))

#ifndef __cplusplus


typedef union gc_be16 { u16 raw; } gc_be16;
typedef union gc_bes16 { u16 raw; } gc_bes16;
typedef union gc_be32 { u32 raw; } gc_be32;
typedef union gc_bes32 { u32 raw; } gc_bes32;
typedef union gc_bef32 { u32 raw; } gc_bef32;
typedef union gc_ptr32_c { u32 raw; } gc_ptr32_c;
#define gc_ptr32(T) gc_ptr32_c
#define GC_BE32(x) gc_rd32((const u8*)&(x))
#define GC_ADDBE32(lv, v) gc_wr32((u8*)&(lv), gc_rd32((const u8*)&(lv)) + (u32)(v))
#define GC_BE16(x) gc_rd16((const u8*)&(x))
#define GC_BES16(x) ((s16)gc_rd16((const u8*)&(x)))
#define GC_BES32(x) ((s32)gc_rd32((const u8*)&(x)))
#define GC_BEF32(x) gc_rdf32((const u8*)&(x))
#define GC_PTR(T, x) ((T)(uintptr_t)gc_rd32((const u8*)&(x)))
#define GC_RAW32(x) gc_rd32((const u8*)&(x))
#define GC_SETBE16(lv, v) gc_wr16((u8*)&(lv), (u16)(v))
#define GC_SETBE32(lv, v) gc_wr32((u8*)&(lv), (u32)(v))
#define GC_SETBEF32(lv, v) gc_wrf32((u8*)&(lv), (v))
#define GC_SETPTR(lv, v) gc_wr32((u8*)&(lv), gc_addr32(v))

#define GC_BSWAP32C(v) ((((u32)(v) & 0xFF) << 24) | (((u32)(v) & 0xFF00) << 8) | (((u32)(v) >> 8) & 0xFF00) | ((u32)(v) >> 24))
#define GC_BEC32(v) { GC_BSWAP32C(v) }
#define GC_BECF32_ZERO { 0 }
#else
#define GC_BE32(x) ((u32)(x))
#define GC_ADDBE32(lv, v) ((lv) += (u32)(v))
#define GC_BE16(x) ((u16)(x))
#define GC_BES16(x) ((s16)(x))
#define GC_BES32(x) ((s32)(x))
#define GC_BEF32(x) ((f32)(x))
#define GC_PTR(T, x) ((T)(x))
#define GC_RAW32(x) ((x).gc())
#define GC_SETBE16(lv, v) ((lv) = (v))
#define GC_SETBE32(lv, v) ((lv) = (v))
#define GC_SETBEF32(lv, v) ((lv) = (v))
#define GC_SETPTR(lv, v) ((lv) = (v))
#endif


static inline f32 gc_rdf32(const u8* b) { union { u32 u; f32 f; } c; c.u = gc_rd32(b); return c.f; }
static inline void gc_wrf32(u8* b, f32 v) { union { u32 u; f32 f; } c; c.f = v; gc_wr32(b, c.u); }
static inline void gc_mtxcopy(f32 (*dst)[4], const void* src) {
    const u8* p = (const u8*)src;
    int i;
    for (i = 0; i < 12; i++) {
        dst[i / 4][i % 4] = gc_rdf32(p + i * 4);
    }
}
#define GC_MTXCOPY(dst, src) gc_mtxcopy((dst), (src))

#define GC_FIXF32(lv) ((lv) = gc_rdf32((const u8*)&(lv)))
static inline void gc_fixf32n(f32* p, int n) { int i; for (i = 0; i < n; i++) { p[i] = gc_rdf32((const u8*)&p[i]); } }
#define GC_FIXF32N(p, n) gc_fixf32n((f32*)(p), (n))
#define GC_FIX32(lv) ((lv) = gc_rd32((const u8*)&(lv)))
#define GC_FIX16(lv) ((lv) = gc_rd16((const u8*)&(lv)))
#define gc_mtxptr32 gc_ptr32(void)
#define gc_enum32(T) gc_bes32

#ifdef __cplusplus


#define GC_BE_OPS(NAME, V)                                                                 \
    operator V() const { return get(); }                                                   \
    NAME& operator=(V x) { set(x); return *this; }                                         \
    NAME& operator+=(V x) { set((V)(get() + x)); return *this; }                           \
    NAME& operator-=(V x) { set((V)(get() - x)); return *this; }                           \
    NAME& operator*=(V x) { set((V)(get() * x)); return *this; }
#define GC_BE_INTOPS(NAME, V)                                                              \
    NAME& operator|=(V x) { set((V)(get() | x)); return *this; }                           \
    NAME& operator&=(V x) { set((V)(get() & x)); return *this; }                           \
    NAME& operator^=(V x) { set((V)(get() ^ x)); return *this; }                           \
    NAME& operator++() { set((V)(get() + 1)); return *this; }                              \
    NAME& operator--() { set((V)(get() - 1)); return *this; }                              \
    V operator++(int) { V o = get(); set((V)(o + 1)); return o; }                          \
    V operator--(int) { V o = get(); set((V)(o - 1)); return o; }

template <class V> struct alignas(2) gc_be_num16 {
    u8 b[2];
    V get() const { return (V)gc_rd16(b); }
    void set(V x) { gc_wr16(b, (u16)x); }
    GC_BE_OPS(gc_be_num16, V)
    GC_BE_INTOPS(gc_be_num16, V)
};
template <class V> struct alignas(4) gc_be_num32 {
    u8 b[4];
    V get() const { return (V)gc_rd32(b); }
    void set(V x) { gc_wr32(b, (u32)x); }
    GC_BE_OPS(gc_be_num32, V)
    GC_BE_INTOPS(gc_be_num32, V)
};
struct alignas(4) gc_bef32_t {
    u8 b[4];
    f32 get() const { union { u32 u; f32 f; } c; c.u = gc_rd32(b); return c.f; }
    void set(f32 x) { union { u32 u; f32 f; } c; c.f = x; gc_wr32(b, c.u); }
    GC_BE_OPS(gc_bef32_t, f32)
};
#undef GC_BE_OPS
#undef GC_BE_INTOPS
typedef gc_be_num16<u16> gc_be16;
typedef gc_be_num16<s16> gc_bes16;
typedef gc_be_num32<u32> gc_be32;
typedef gc_be_num32<s32> gc_bes32;
typedef gc_bef32_t gc_bef32;


template <class T> struct alignas(4) gc_ptr32_t {
    u8 b[4];
    T* get() const { return (T*)(uintptr_t)gc_rd32(b); }
    void set(const void* p) {
        uintptr_t v = (uintptr_t)p;
        if (v > 0xFFFFFFFFu) {
            OSPanic(__FILE__, __LINE__, "gc_ptr32: address above 4 GB stored in a 4-byte GameCube slot");
        }
        gc_wr32(b, (u32)v);
    }
    operator T*() const { return get(); }
    template <class U> explicit operator U*() const { return (U*)get(); }
    T* operator->() const { return get(); }
    gc_ptr32_t& operator=(T* p) { set(p); return *this; }
    u32 gc() const { return gc_rd32(b); }
    explicit operator u32() const { return gc(); }
};
#define gc_ptr32(T) gc_ptr32_t<T>


static_assert(sizeof(gc_be16) == 2 && alignof(gc_be16) == 2, "gc_be16");
static_assert(sizeof(gc_be32) == 4 && alignof(gc_be32) == 4, "gc_be32");
static_assert(sizeof(gc_ptr32(void)) == 4 && alignof(gc_ptr32(void)) == 4, "gc_ptr32");


template <class T> struct gc_field { typedef T type; };
template <> struct gc_field<u16> { typedef gc_be16 type; };
template <> struct gc_field<s16> { typedef gc_bes16 type; };
template <> struct gc_field<u32> { typedef gc_be32 type; };
template <> struct gc_field<s32> { typedef gc_bes32 type; };
template <> struct gc_field<f32> { typedef gc_bef32 type; };
template <class T> struct gc_field<T*> { typedef gc_ptr32_t<T> type; };
#endif


typedef struct gc_vec3 { gc_bef32 x, y, z; } gc_vec3;
#define gc_vec(T) gc_vec3
#define GC_VEC3(dst, src) ((dst).x = GC_BEF32((src).x), (dst).y = GC_BEF32((src).y), (dst).z = GC_BEF32((src).z))
#ifndef __MWERKS__


static inline f32* gc_vec3tmpn(const gc_vec3* v, int n) {
    static f32 ring[8][4][3];
    static int next;
    f32 (*d)[3] = ring[next++ & 7];
    int i;
    for (i = 0; i < n && i < 4; i++) {
        d[i][0] = GC_BEF32(v[i].x); d[i][1] = GC_BEF32(v[i].y); d[i][2] = GC_BEF32(v[i].z);
    }
    return d[0];
}
#define GC_VEC3P(T, pv) ((T*)gc_vec3tmpn((pv), 1))

#define GC_VEC3AP(T, pv, n) ((T*)gc_vec3tmpn((pv), (n)))

typedef struct gc_s16x4 { gc_be16 v[4]; } gc_s16x4;
#define gc_s16x4(T) gc_s16x4
static inline u16* gc_s16x4tmp(const gc_s16x4* p) {
    static u16 ring[8][4];
    static int next;
    u16* d = ring[next++ & 7];
    int i;
    for (i = 0; i < 4; i++) {
        d[i] = GC_BE16(p->v[i]);
    }
    return d;
}
#define GC_S16X4P(T, p) ((T*)gc_s16x4tmp(p))
#endif

#endif



#ifdef __MWERKS__
#define GC_AT(T, p, o) (*(T*)((u8*)(p) + (o)))
#else
#define GC_AT(T, p, o) (*(typename gc_field<T>::type*)((u8*)(p) + (o)))
#endif

#endif
