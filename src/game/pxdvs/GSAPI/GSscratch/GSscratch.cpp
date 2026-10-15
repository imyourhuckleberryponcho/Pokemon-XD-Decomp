#include <dolphin/types.h>

// WIP: NonMatching. All exact except GSscratchAlloc (99%, free-slot pointer in r6 vs r7)
// and GSscratchInit (hand-written asm in the original: it switches r1 to the
// scratch stack; the C version here does not reconstruct that).

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

static inline ScratchBlock* scratchFindBlock(u8 index)
{
    ScratchBlock* block;
    u32 i;

    block = _blockTable;
    for (i = 0; i < 32; block++, i++) {
        if (block->index == index) {
            return block;
        }
    }
    return 0;
}

static inline ScratchBlock* scratchFindFreeBlock()
{
    ScratchBlock* block;
    u32 i;

    block = _blockTable;
    for (i = 0; i < 32; block++, i++) {
        if (block->index == 0xFF) {
            return block;
        }
    }
    return 0;
}

extern "C" {
void LCEnable();
u32 LCQueueLength();
void LCQueueWait(s32);
s32 LCStoreData(void*, void*, u32);

void GSscratchSetValid()
{
    s32 count;
    ScratchBlock* block;

    if (_scratchInvalid != 0) {
        block = _blockTable;
        count = 32;
        while (count-- != 0) {
            if (block->index != 0xFF && block->notify != 0) {
                block->notify(1, (u8*)_scratchPadBase + block->index * 0x200, block->count);
            }
            block++;
        }
        _scratchInvalid = 0;
    }
}

void GSscratchSetInvalid()
{
    s32 count;
    ScratchBlock* block;

    if (_scratchInvalid != 1) {
        block = _blockTable;
        count = 32;
        while (count-- != 0) {
            if (block->index != 0xFF && block->notify != 0) {
                block->notify(0, (u8*)_scratchPadBase + block->index * 0x200, block->count);
            }
            block++;
        }
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
    ScratchBlock* block;
    u32 mask;
    u8 shift;
    u8 remaining;
    u32 map;

    block = scratchFindBlock(((u32)ptr - (u32)_scratchPadBase) >> 9);
    if (block == 0) {
        return;
    }

    remaining = block->count;
    shift = block->index;
    mask = 0x80000000;
    while (shift-- != 0) {
        mask >>= 1;
    }

    map = _blockMap;
    while (remaining-- != 0) {
        map &= ~mask;
        mask >>= 1;
    }
    _blockMap = map;
    block->index = 0xFF;
}

void* GSscratchAlloc(u8 count, void (*notify)(u8, void*, u8))
{
    u32 scanMask;
    u32 occupied;
    u8 shift;
    u8 remaining;
    u32 map;
    u8 candidate;
    ScratchBlock* entry;

    if (_scratchInvalid == 1) {
        return 0;
    }
    if (count == 0 || count > 32) {
        return 0;
    }

    map = _blockMap;
    for (candidate = 0; candidate < 32; candidate++) {
        remaining = count;
        shift = candidate;
        occupied = 0;
        scanMask = 0x80000000;
        while (shift-- != 0) {
            scanMask >>= 1;
        }
        while (remaining-- != 0) {
            occupied <<= 1;
            if (scanMask != 0) {
                if ((map & scanMask) != 0) {
                    occupied |= 1;
                }
                scanMask >>= 1;
            } else {
                occupied |= 1;
            }
        }
        if (occupied == 0) {
            if ((entry = scratchFindFreeBlock()) == 0) {
                return 0;
            }

            {
                u32 entryMask;
                u8 entryShift;

                entry->index = candidate;
                entryShift = candidate;
                entryMask = 0x80000000;
                entry->count = count;
                entry->notify = notify;
                while (entryShift-- != 0) {
                    entryMask >>= 1;
                }
                map = _blockMap;
                remaining = count;
                while (remaining-- != 0) {
                    map |= entryMask;
                    entryMask >>= 1;
                }
                _blockMap = map;
                return (u8*)_scratchPadBase + entry->index * 0x200;
            }
        }
    }
    return 0;
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
