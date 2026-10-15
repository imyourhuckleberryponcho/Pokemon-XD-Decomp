#include "__gba.h"

#include "__os.h"

static void __GBAHandler(s32 chan, u32 error, OSContext* context)
{
    GBAControl* gba = &__GBA[chan];
    GBATransferCallback proc;
    GBACallback callback;
    OSContext exceptionContext;

    if (__GBAReset) {
        return;
    }
    if (error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)) {
        gba->ret = GBA_NOT_READY;
    } else {
        gba->ret = GBA_READY;
    }
    if (gba->proc != NULL) {
        proc = gba->proc;
        gba->proc = NULL;
        proc(chan);
    }
    if (gba->callback != NULL) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        callback = gba->callback;
        gba->callback = NULL;
        callback(chan, gba->ret);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

void __GBASyncCallback(s32 chan, s32 ret)
{
    OSWakeupThread(&__GBA[chan].threadQueue);
}

s32 __GBASync(s32 chan)
{
    GBAControl* gba = &__GBA[chan];
    BOOL enabled;
    s32 ret;

    enabled = OSDisableInterrupts();
    while (gba->callback != NULL) {
        OSSleepThread(&gba->threadQueue);
    }
    ret = gba->ret;
    OSRestoreInterrupts(enabled);
    return ret;
}

static void TypeAndStatusCallback(s32 chan, u32 type)
{
    GBAControl* gba = &__GBA[chan];
    GBATransferCallback proc;
    GBACallback callback;
    OSContext* context;
    OSContext exceptionContext;

    if (__GBAReset) {
        return;
    }
    if ((type & 0xFF) != 0 || (type & 0xFFFF0000) != SI_GBA) {
        gba->ret = GBA_NOT_READY;
    } else {
        if (SITransfer(chan, gba->output, gba->outputBytes, gba->input, gba->inputBytes, __GBAHandler, gba->delay)) {
            return;
        }
        gba->ret = GBA_BUSY;
    }
    if (gba->proc != NULL) {
        proc = gba->proc;
        gba->proc = NULL;
        proc(chan);
    }
    if (gba->callback != NULL) {
        context = OSGetCurrentContext();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        callback = gba->callback;
        gba->callback = NULL;
        callback(chan, gba->ret);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
        __OSReschedule();
    }
}

s32 __GBATransfer(s32 chan, s32 w1, s32 w2, GBATransferCallback callback)
{
    BOOL enabled;
    GBAControl* gba = &__GBA[chan];

    enabled = OSDisableInterrupts();
    gba->proc = callback;
    gba->outputBytes = w1;
    gba->inputBytes = w2;
    SIGetTypeAsync(chan, TypeAndStatusCallback);
    OSRestoreInterrupts(enabled);
    return GBA_READY;
}
