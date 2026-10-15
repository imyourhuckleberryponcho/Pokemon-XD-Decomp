#include <dolphin/types.h>

// WIP: this unit remains NonMatching. GSscratchIsPtr, GSscratchWaitForCompletion,
// and GSscratchStore match exactly. GSscratchInit's retail stack switch is not
// reconstructed; this source is not a safe replacement for that behavior.

struct ScratchBlock {
    u8 index;
    u8 count;
    u8 pad[2];
    void (*notify)(u8, void*, u8);
};

static u32 _stackSize;
static s32 _entriesQueued;
static void* _scratchPadBase;
static u32 _scratchInitLR;
static u8 _scratchInvalid;
static u32 _blockMap;
static ScratchBlock _blockTable[32];

extern "C" {
void LCEnable();
u32 LCQueueLength();
void LCQueueWait(s32);
s32 LCStoreData(void*, void*, u32);

void GSscratchSetValid()
{
    if (_scratchInvalid != 0) {
        s32 remaining = 31;
        ScratchBlock* block = _blockTable;
        do {
            if (block->index != 0xFF && block->notify != 0) {
                block->notify(1, (u8*)_scratchPadBase + (block->index << 9), block->count);
            }
            ++block;
        } while (remaining-- != 0);
        _scratchInvalid = 0;
    }
}

void GSscratchSetInvalid()
{
    if (_scratchInvalid != 1) {
        s32 remaining = 31;
        ScratchBlock* block = _blockTable;
        do {
            if (block->index != 0xFF && block->notify != 0) {
                block->notify(0, (u8*)_scratchPadBase + (block->index << 9), block->count);
            }
            ++block;
        } while (remaining-- != 0);
        _scratchInvalid = 1;
    }
}

u8 GSscratchIsPtr(void* ptr)
{
    return ((u32)ptr & 0xF0000000) == ((u32)_scratchPadBase & 0xF0000000);
}

void GSscratchWaitForCompletion()
{
    LCQueueWait(_entriesQueued);
    _entriesQueued = 0;
}

s32 GSscratchStore(void* source, void* destination, u32 size)
{
    if (LCQueueLength() >= 0xF) return 1;
    if (((u32)destination & 0x1F) != 0 || ((u32)source & 0x1F) != 0) return 2;
    if ((size & 0x1F) != 0) return 2;
    _entriesQueued += LCStoreData(source, destination, size);
    return 0;
}

void GSscratchFree(void* ptr)
{
    u8 index = (u8)(((u32)ptr - (u32)_scratchPadBase) >> 9);
    ScratchBlock* block = _blockTable;
    for (s32 i = 0; i < 32; ++i, ++block) {
        if (block->index == index) break;
    }
    if (block == _blockTable + 32) block = 0;
    if (block == 0) return;

    u8 shift = block->index;
    u8 remaining = block->count;
    u32 mask = 0x80000000;
    while (shift != 0) {
        --shift;
        mask >>= 1;
    }
    while (remaining != 0) {
        --remaining;
        _blockMap &= ~mask;
        mask >>= 1;
    }
    block->index = 0xFF;
}

void* GSscratchAlloc(u8 count, void (*notify)(u8, void*, u8))
{
    u8 blocks = count;
    if (_scratchInvalid == 1) return 0;
    if (blocks == 0 || blocks > 0x20) return 0;

    u8 candidate = 0;
    u32 map = _blockMap;
    for (;;) {
        if (candidate >= 0x20) return 0;
        u8 needed = blocks;
        u8 shift = candidate;
        u32 occupied = 0;
        u32 mask = 0x80000000;
        while (shift != 0) {
            --shift;
            mask >>= 1;
        }
        while (needed != 0) {
            --needed;
            occupied <<= 1;
            if (mask != 0) {
                if (map & mask) occupied |= 1;
                mask >>= 1;
            } else {
                occupied |= 1;
            }
        }
        if (occupied == 0) {
            ScratchBlock* entry = _blockTable;
            for (s32 i = 0; i < 32; ++i, ++entry) {
                if (entry->index == 0xFF) {
                    entry->index = candidate;
                    entry->count = blocks;
                    entry->notify = notify;
                    mask = 0x80000000;
                    shift = candidate;
                    while (shift != 0) {
                        --shift;
                        mask >>= 1;
                    }
                    needed = blocks;
                    while (needed != 0) {
                        --needed;
                        _blockMap |= mask;
                        mask >>= 1;
                    }
                    return (u8*)_scratchPadBase + (candidate << 9);
                }
            }
            return 0;
        }
        ++candidate;
    }
}

s32 GSscratchInit(u8 stackSize)
{
    _scratchInitLR = 0;
    _blockMap = 0;
    for (s32 i = 0; i < 32; ++i) _blockTable[i].index = 0xFF;
    LCEnable();
    _stackSize = (stackSize << 9) & 0x1FE00;
    _scratchPadBase = (void*)0xE0000000;
    if (stackSize != 0) {
        _blockMap |= 0xFFFFFFFF << (32 - stackSize);
        _blockTable[0].index = 0;
        _blockTable[0].count = stackSize;
    }
    _scratchInvalid = 0;
    if (stackSize == 0) return 1;
 // TODO: retail switches r1 to the scratch stack and returns through the
 // saved caller LR. That stack-switch behavior is not reconstructed here.
    return 0;
}
}
