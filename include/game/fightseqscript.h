#ifndef GAME_FIGHTSEQSCRIPT_H
#define GAME_FIGHTSEQSCRIPT_H

#include <dolphin/types.h>

#ifdef __MWERKS__

typedef u16 ws_u16;
typedef s16 ws_s16;
typedef u32 ws_u32;
typedef s32 ws_s32;
typedef void* ws_ptr;
#define ws_ptrto(T) T*

#define WS_RDPTR(p) (*(void**)(p))
#define WS_RD16(p) (*(u16*)(p))
#define WS_RD32(p) (*(u32*)(p))

#else

extern "C" void* PortXD_GameAddress(u32 gcAddress);
extern "C" u32 PortXD_GameAddressOf(const void* p);

static inline u16 ws_be16(const u8* b) { return (u16)((b[0] << 8) | b[1]); }
static inline u32 ws_be32(const u8* b) { return ((u32)b[0] << 24) | ((u32)b[1] << 16) | ((u32)b[2] << 8) | b[3]; }
static inline void ws_setbe32(u8* b, u32 v) { b[0] = (u8)(v >> 24); b[1] = (u8)(v >> 16); b[2] = (u8)(v >> 8); b[3] = (u8)v; }

struct ws_u16 {
    u8 b[2];
    operator u16() const { return ws_be16(b); }
};
struct ws_s16 {
    u8 b[2];
    operator s16() const { return (s16)ws_be16(b); }
};
struct ws_u32 {
    u8 b[4];
    operator u32() const { return ws_be32(b); }
    template <class T> explicit operator T*() const { return (T*)PortXD_GameAddress(ws_be32(b)); }
};
struct ws_s32 {
    u8 b[4];
    operator s32() const { return (s32)ws_be32(b); }
};
struct ws_ptr {
    u8 b[4];
    u32 gc() const { return ws_be32(b); }
    operator void*() const { return PortXD_GameAddress(gc()); }
    template <class T> operator T*() const { return (T*)PortXD_GameAddress(gc()); }
    ws_ptr& operator=(const void* p) { ws_setbe32(b, PortXD_GameAddressOf(p)); return *this; }
};

template <class T> struct ws_tptr {
    u8 b[4];
    u32 gc() const { return ws_be32(b); }
    T* get() const { return (T*)PortXD_GameAddress(ws_be32(b)); }
    operator T*() const { return get(); }
    template <class U> operator U*() const { return (U*)get(); }
    T& operator*() const { return *get(); }
    T* operator->() const { return get(); }
    T& operator[](int i) const { return get()[i]; }
};
#define ws_ptrto(T) ws_tptr<T>

#define WS_U16(p) ws_be16((const u8*)(p))
#define WS_U32(p) ws_be32((const u8*)(p))
#define WS_PTR(p) PortXD_GameAddress(ws_be32((const u8*)(p)))
#define WS_RDPTR(p) WS_PTR(p)
#define WS_RD16(p) WS_U16(p)
#define WS_RD32(p) WS_U32(p)

#include <game/fightseqscript_addrs.h>

#endif

#endif
