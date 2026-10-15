#include "__gba.h"

static void WriteProc(s32 chan)
{
    GBAControl* gba = &__GBA[chan];

    if (gba->ret != GBA_READY) {
        return;
    }
    gba->status[0] = gba->input[0] & GBA_JSTAT_MASK;
}

s32 GBAWriteAsync(s32 chan, u8* src, u8* status, GBACallback callback)
{
    GBAControl* gba = &__GBA[chan];

    if (gba->callback != NULL) {
        return GBA_BUSY;
    }
    gba->output[0] = 0x15;
    memcpy(&gba->output[1], src, 4);
    gba->ptr = src;
    gba->status = status;
    gba->callback = callback;
    return __GBATransfer(chan, 5, 1, WriteProc);
}

s32 GBAWrite(s32 chan, u8* src, u8* status)
{
    GBAControl* gba = &__GBA[chan];
    u8* buffer = src; // unused; keeps the retail stack frame size
    s32 ret;

    ret = GBAWriteAsync(chan, src, status, __GBASyncCallback);
    if (ret != GBA_READY) {
        return ret;
    }
    return __GBASync(chan);
}
