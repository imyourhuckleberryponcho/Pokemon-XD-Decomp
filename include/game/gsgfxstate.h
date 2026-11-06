#ifndef GAME_GSGFXSTATE_H
#define GAME_GSGFXSTATE_H

#include <dolphin/types.h>

struct GSgfxLayer;
struct GSgfx_GCFifoObj;
struct GSgfxRenderFifoItem;

struct GSgfxState {
    u8 settings[0xC40];
    GSgfxLayer* layer;
    void* xfb;
    s32 phase;
    GSgfxRenderFifoItem* fifoList;
    GSgfx_GCFifoObj* fifo;
    GSgfx_GCFifoObj* spare;
    void* buffer;
    void* write;
    u8 breakpt;
    u8 drawdone;
};

#endif
