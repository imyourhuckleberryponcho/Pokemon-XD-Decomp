#ifndef GAME_GSGFXFIFO_H
#define GAME_GSGFXFIFO_H

#include <dolphin/types.h>

struct GSgfx_GCFifoObj {
    void* base;
    void* end;
    u32 size;
    u32 hi;
    u32 lo;
    void* read;
    void* write;
    u32 status;
    u8 bound;
    u8 enable;
#ifdef __MWERKS__
    u8 pad[0x4C - 0x22];
#else
    u8 pad[0x4C - 0x36];
#endif
    u32 breakpointReached;
    u8 pad50[0x30];
};
#ifndef __MWERKS__
static_assert(sizeof(GSgfx_GCFifoObj) == 0x80, "GSgfx_GCFifoObj must fill its 0x80-byte slot");
#endif

#endif
