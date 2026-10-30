#include <dolphin/types.h>

class GSgfxLayer;
struct GSgfx_GCFifoObj;
struct GXFifoObj;

struct GSgfxRenderFifoItem {
    GSgfx_GCFifoObj* fifo;
    void* start;
    void* end;
    u32 color;
    void (*callback)(void*);
    void* callbackArg;
};

struct GSgfxRenderState {
    u8 unk0[0xC40];
    GSgfxLayer* layer;
    void* xfb;
    s32 phase;
    GSgfxRenderFifoItem* fifoList;
};

struct GSgfxRenderWaitData {
    s32 lastVsync;
    s32 perfEntry;
};

struct GXColor {
    u8 r, g, b, a;
};

extern "C" {
extern GSgfxRenderState* gsgfxState;
extern s32 gsgfx_gpu_mode;
extern u8 gsgfx_layer_inPrimitive;
extern u8* gsgfx_layer_activeFifo;
extern f32 mtxIdent[3][4];
f32 GSgfxVideoGetLastRenderTime(void);
u8 GSgfxVideoGetXFBCount(void);
s32 GSgfxVideoGetVsyncCount(void);
u8 GSgfxVideoGetVsyncRate(void);
s32 GSgfxPerfbarCPUEntry(u32 color);
bool GSgfxTokenCleared(u16 token);
void OSYieldThread(void);
s32 OSEnableInterrupts(void);
void OSRestoreInterrupts(s32 level);
void GSgfx_GCReset(void);

void PSMTXIdentity(f32 (*m)[4]);
void GXAbortFrame(void);
void GXSetDrawDone(void);
void GXSetCPUFifo(GXFifoObj* fifo);
void GXSaveCPUFifo(GXFifoObj* fifo);
void GXGetFifoPtrs(GXFifoObj* fifo, void** readPtr, void** writePtr);
void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr);
void GXSetTexCoordGen2(u32 dst, u32 func, u32 src, u32 mtx, u8 normalize, u32 ptMtx);
void GXSetNumTexGens(u8 n);
void GXClearVtxDesc(void);
void GXInvalidateVtxCache(void);
void GXSetLineWidth(u8 width, u32 offsets);
void GXSetPointSize(u8 size, u32 offsets);
void GXEnableTexOffsets(u32 coord, u8 lineOfs, u8 pointOfs);
void GXLoadPosMtxImm(f32 (*m)[4], u32 id);
void GXLoadNrmMtxImm(f32 (*m)[4], u32 id);
void GXLoadTexMtxImm(f32 (*m)[4], u32 id, u32 type);
void GXSetCurrentMtx(u32 id);
void GXSetCoPlanar(u8 enable);
void GXSetCullMode(u32 mode);
void GXSetClipMode(u32 mode);
void GXSetScissorBoxOffset(s32 x, s32 y);
void GXSetNumChans(u8 n);
void GXSetChanCtrl(u32 chan, u8 enable, u32 amb, u32 mat, u32 lightMask, u32 diff, u32 attn);
void GXInvalidateTexAll(void);
void GXSetTevOrder(u32 stage, u32 coord, u32 map, u32 color);
void GXSetNumTevStages(u8 n);
void GXSetTevOp(u32 stage, u32 mode);
void GXSetAlphaCompare(u32 comp0, u8 ref0, u32 op, u32 comp1, u8 ref1);
void GXSetZTexture(u32 op, u32 fmt, u32 bias);
void GXSetTevKColorSel(u32 stage, u32 sel);
void GXSetTevKAlphaSel(u32 stage, u32 sel);
void GXSetTevSwapMode(u32 stage, u32 ras, u32 tex);
void GXSetTevSwapModeTable(u32 table, u32 r, u32 g, u32 b, u32 a);
void GXSetTevDirect(u32 stage);
void GXSetNumIndStages(u8 n);
void GXSetIndTexCoordScale(u32 stage, u32 scaleS, u32 scaleT);
void GXSetFog(u32 type, f32 start, f32 end, f32 nearZ, f32 farZ, GXColor color);
void GXSetFogRangeAdj(u8 enable, u16 center, void* table);
void GXSetBlendMode(u32 type, u32 src, u32 dst, u32 op);
void GXSetColorUpdate(u8 enable);
void GXSetAlphaUpdate(u8 enable);
void GXSetZMode(u8 enable, u32 func, u8 update);
void GXSetZCompLoc(u8 beforeTex);
void GXSetDither(u8 enable);
void GXSetDstAlpha(u8 enable, u8 alpha);
void GXSetPixelFmt(u32 pixelFmt, u32 zFmt);
void GXSetFieldMask(u8 even, u8 odd);
void GXPokeColorUpdate(u8 enable);
void GXPokeAlphaUpdate(u8 enable);
void GXPokeDither(u8 enable);
void GXPokeBlendMode(u32 type, u32 src, u32 dst, u32 op);
void GXPokeAlphaMode(u32 comp, u8 ref);
void GXPokeAlphaRead(u32 mode);
void GXPokeDstAlpha(u8 enable, u8 alpha);
void GXPokeZMode(u8 enable, u32 func, u8 update);
void GXSetGPMetric(u32 perf0, u32 perf1);
void GXClearGPMetric(void);
}

void GSgfxRenderModuleDoPreUpdate(f32 dt);
void GSgfxRenderModuleDoPostUpdate(f32 dt);
void GSgfxRenderModuleInit();
u16 GSgfxTokenMark_Sub();
void GSgfxTokenMarkFrame();
void GSgfxTokenAbortFrame();
void GSgfxPerfbarCPUEnd();
void GSgfxPerfbarGPUEnd();
void GSgfxPerfbarCPUStart();
void GSgfxPerfbarGPUStart();
void GSgfxPerfbarGPUEntry(u32 color);
void GSgfxPerfbarRender(GSgfxLayer* layer);
bool GSgfxGPUIsIdle();
GSgfx_GCFifoObj* GSgfxGPUGetImmediateFifo();
void GSgfxGPUProcessBlock(GSgfx_GCFifoObj* fifo, void* start, void* end);
void GSgfxGPUInitFifoBase(GSgfx_GCFifoObj* fifo, void* base, u32 size);
void GSgfxGPUSetDrawDoneCallback(void (*cb)());
void GSgfxGPUSetBreakpointCallback(void (*cb)());
void GSgfxVideoSetOneShotPostCallback(void (*cb)(void*));
void GSgfxVideoSetXFBReady(void* xfb);
void* GSgfxVideoFindFreeXFB(bool);
void GSgfxVideoBuildEFB2XFBCopy(void* buf, void* xfb);
void* GSgfxVideoCopyEFBToXFB();
void GSgfxVideoSetupNextFrame();
void GSgfxResetUpdate();
void GSgfxSSUpdate();
void GSgfxCaptureUpdate(void* xfb);
void GSgfxCaptureRenderFrameNumber(GSgfxLayer* layer);
void GSgfxBackFBDoFrame(GSgfxLayer* layer);
GSgfxLayer* GSgfxLayerPrerender();
void GSgfxLayerRenderStats(GSgfxLayer* layer);
void GSgfxLayerInvalidateAll();
void GSgfxLayerBuildRenderList();
void GSgfxLayerPrepareNextFrame();
void GSgfxLayerUpdateActiveFifoStats();

static u8 _renderXFBCommandBuf[0x60];
static u8 _renderXFBCommandFifo[0x80];
static GSgfxRenderFifoItem _renderFifoList[64];
static GXFifoObj* _renderPrepareFrameStart;
static GXFifoObj* _renderPrepareFrameEnd;
static void* _renderLastXFBPtr;
static u32 _renderPauseCount;
static u16 _renderXFBCopyToken;

static void _renderResetGX();
static void _renderBreakpointCallback();
static void _renderCopyEFB(void* xfb);
static void _renderDrawDoneCallback();

static inline void abortFrameImpl() {
    gsgfx_layer_inPrimitive = 0;
    GSgfxVideoSetOneShotPostCallback(0);
    GXAbortFrame();
    GSgfxTokenAbortFrame();
    void* xfb = gsgfxState->xfb;
    if (xfb != 0 && (u32)xfb != 0xFEFEFEFE) {
        GSgfxVideoSetXFBReady(xfb);
    }
    gsgfxState->phase = 0;
    gsgfxState->xfb = 0;
    GSgfxLayerInvalidateAll();
    _renderResetGX();
}

static inline void waitInit(GSgfxRenderWaitData* d) {
    d->perfEntry = GSgfxPerfbarCPUEntry(0xFFFF00);
    d->lastVsync = GSgfxVideoGetVsyncCount();
}

static inline void waitTick(GSgfxRenderWaitData* d) {
    OSYieldThread();
    if (GSgfxGPUIsIdle() != 1) {
        s32 now = GSgfxVideoGetVsyncCount();
        u32 limit = GSgfxVideoGetVsyncRate() * 3;
        s32 diff = now - d->lastVsync;
        if (diff < 0) {
            d->lastVsync = now;
        } else if ((u32)diff > limit) {
            abortFrameImpl();
        }
    }
}

static inline void waitExit(GSgfxRenderWaitData* d) {
    GSgfxPerfbarCPUEntry(d->perfEntry);
}

static inline void waitForDrawCompleteImpl() {
    GSgfxRenderWaitData d;
    waitInit(&d);
    while (gsgfxState->xfb != 0) {
        waitTick(&d);
    }
    waitExit(&d);
}

static inline void setupFirstFrameImpl() {
    GXFifoObj* fifo;
    void* tmp;
    if (gsgfx_gpu_mode == 2) {
        GSgfxLayerPrepareNextFrame();
        GSgfxLayerUpdateActiveFifoStats();
        fifo = (GXFifoObj*)GSgfxGPUGetImmediateFifo();
        GXSetCPUFifo(fifo);
        GXGetFifoPtrs(fifo, &tmp, (void**)&_renderPrepareFrameStart);
    }
    GSgfxVideoSetupNextFrame();
    if (gsgfx_gpu_mode == 2) {
        GXSaveCPUFifo(fifo);
        GXGetFifoPtrs(fifo, &tmp, (void**)&_renderPrepareFrameEnd);
        GXSetCPUFifo((GXFifoObj*)(gsgfx_layer_activeFifo + 8));
    }
    GSgfxTokenMarkFrame();
}

extern "C" void GSgfxRender(void) {
    f32 dt = GSgfxVideoGetLastRenderTime();
    GSgfxRenderModuleDoPreUpdate(dt);
    switch (gsgfx_gpu_mode) {
    case 1: {
        GSgfxTokenMark_Sub();
        GSgfxPerfbarCPUEnd();
        GSgfxPerfbarGPUEnd();
        GSgfxPerfbarRender(gsgfxState->layer);
        if (GSgfxVideoGetXFBCount() > 1) {
            waitForDrawCompleteImpl();
        }
        GSgfxResetUpdate();
        GSgfxSSUpdate();
        GSgfxCaptureUpdate(_renderLastXFBPtr);
        void* xfb = GSgfxVideoCopyEFBToXFB();
        if (GSgfxVideoGetXFBCount() > 1) {
            gsgfxState->xfb = xfb;
            GXSetDrawDone();
        }
        GSgfxPerfbarCPUStart();
        GSgfxPerfbarGPUStart();
        GSgfxLayerInvalidateAll();
        break;
    }
    case 2: {
        GSgfxLayer* layer = GSgfxLayerPrerender();
        GSgfxCaptureRenderFrameNumber(layer);
        GSgfxBackFBDoFrame(layer);
        GSgfxPerfbarCPUEnd();
        GSgfxPerfbarRender(layer);
        GSgfxLayerRenderStats(layer);
        if (GSgfxVideoGetXFBCount() > 1) {
            waitForDrawCompleteImpl();
        }
        _renderXFBCopyToken = GSgfxTokenMark_Sub();
        GSgfxResetUpdate();
        GSgfxSSUpdate();
        GSgfxCaptureUpdate(_renderLastXFBPtr);
        gsgfxState->xfb = (void*)0xFEFEFEFE;
        GSgfxRenderFifoItem* list = _renderFifoList;
        list->fifo = GSgfxGPUGetImmediateFifo();
        list->start = _renderPrepareFrameStart;
        list->end = _renderPrepareFrameEnd;
        list->color = 0x808080;
        list++;
        list->fifo = 0;
        gsgfxState->fifoList = list;
        GSgfxLayerBuildRenderList();
        GSgfxPerfbarGPUStart();
        gsgfxState->fifoList = &_renderFifoList[0];
        GSgfxRenderFifoItem* item = gsgfxState->fifoList;
        GSgfxPerfbarGPUEntry(item->color);
        GSgfxGPUProcessBlock(item->fifo, item->start, item->end);
        GSgfxPerfbarCPUStart();
        break;
    }
    }
    setupFirstFrameImpl();
    if (_renderPauseCount != 0) {
        dt = 0.0f;
    }
    GSgfxRenderModuleDoPostUpdate(dt);
}

extern "C" bool GSgfxRenderIsPaused(void) {
    return _renderPauseCount != 0;
}

extern "C" void GSgfxRenderUnpause(void) {
    if (_renderPauseCount != 0) {
        _renderPauseCount--;
    }
}

extern "C" void GSgfxRenderPause(void) {
    _renderPauseCount++;
}

void GSgfxRenderSetupFirstFrame() {
    setupFirstFrameImpl();
}

void GSgfxRenderAddToFifoList(GSgfx_GCFifoObj* fifo, void* start, void* end, u32 color, void (*cb)(void*), void* arg) {
    if (start != end) {
        *(u32*)((u8*)fifo + 0x4C) = 0;
        gsgfxState->fifoList->fifo = fifo;
        gsgfxState->fifoList->start = start;
        gsgfxState->fifoList->end = end;
        gsgfxState->fifoList->color = color;
        gsgfxState->fifoList->callback = cb;
        gsgfxState->fifoList->callbackArg = arg;
        gsgfxState->fifoList++;
        gsgfxState->fifoList->fifo = 0;
    }
}

void GSgfxRenderWaitForDrawComplete() {
    waitForDrawCompleteImpl();
}

void GSgfxRenderWaitExit(GSgfxRenderWaitData* d) {
    waitExit(d);
}

void GSgfxRenderWaitTick(GSgfxRenderWaitData* d) {
    waitTick(d);
}

void GSgfxRenderWaitInit(GSgfxRenderWaitData* d) {
    waitInit(d);
}

void GSgfxRenderAbortFrame() {
    abortFrameImpl();
}

void GSgfxRenderInit() {
    gsgfxState->xfb = 0;
    gsgfxState->phase = 0;
    GSgfxGPUInitFifoBase((GSgfx_GCFifoObj*)_renderXFBCommandFifo, _renderXFBCommandBuf, 0x10000);
    GXInitFifoPtrs((GXFifoObj*)_renderXFBCommandFifo, _renderXFBCommandBuf, _renderXFBCommandBuf);
    GSgfxGPUSetDrawDoneCallback(_renderDrawDoneCallback);
    GSgfxGPUSetBreakpointCallback(_renderBreakpointCallback);
    GXLoadPosMtxImm(mtxIdent, 0);
    GXSetCurrentMtx(0);
    GSgfx_GCReset();
    GSgfxRenderModuleInit();
}

static void _renderResetGX() {
    GXColor fogColor = {0, 0, 0, 0};
    f32 mtx[3][4];
    s32 i;
    PSMTXIdentity(mtx);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(1, 1, 5, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(2, 1, 6, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(3, 1, 7, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(4, 1, 8, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(5, 1, 9, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(6, 1, 10, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(7, 1, 11, 0x3C, 0, 0x7D);
    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXSetLineWidth(6, 0);
    GXSetPointSize(6, 0);
    GXEnableTexOffsets(0, 0, 0);
    GXEnableTexOffsets(1, 0, 0);
    GXEnableTexOffsets(2, 0, 0);
    GXEnableTexOffsets(3, 0, 0);
    GXEnableTexOffsets(4, 0, 0);
    GXEnableTexOffsets(5, 0, 0);
    GXEnableTexOffsets(6, 0, 0);
    GXEnableTexOffsets(7, 0, 0);
    GXLoadPosMtxImm(mtx, 0);
    GXLoadNrmMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
    GXLoadTexMtxImm(mtx, 0x3C, 0);
    GXLoadTexMtxImm(mtx, 0x7D, 0);
    GXSetCoPlanar(0);
    GXSetCullMode(2);
    GXSetClipMode(0);
    GXSetScissorBoxOffset(0, 0);
    GXSetNumChans(0);
    GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
    GXSetChanCtrl(5, 0, 0, 1, 0, 0, 2);
    GXInvalidateTexAll();
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOrder(1, 1, 1, 4);
    GXSetTevOrder(2, 2, 2, 4);
    GXSetTevOrder(3, 3, 3, 4);
    GXSetTevOrder(4, 4, 4, 4);
    GXSetTevOrder(5, 5, 5, 4);
    GXSetTevOrder(6, 6, 6, 4);
    GXSetTevOrder(7, 7, 7, 4);
    GXSetTevOrder(8, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(9, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(10, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(11, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(12, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(13, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(14, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(15, 0xFF, 0xFF, 0xFF);
    GXSetNumTevStages(1);
    GXSetTevOp(0, 3);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZTexture(0, 0x11, 0);
    for (i = 0; i < 16; i++) {
        GXSetTevKColorSel(i, 6);
        GXSetTevKAlphaSel(i, 0);
        GXSetTevSwapMode(i, 0, 0);
    }
    GXSetTevSwapModeTable(0, 0, 1, 2, 3);
    GXSetTevSwapModeTable(1, 0, 0, 0, 3);
    GXSetTevSwapModeTable(2, 1, 1, 1, 3);
    GXSetTevSwapModeTable(3, 2, 2, 2, 3);
    for (i = 0; i < 16; i++) {
        GXSetTevDirect(i);
    }
    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(0, 0, 0);
    GXSetIndTexCoordScale(1, 0, 0);
    GXSetIndTexCoordScale(2, 0, 0);
    GXSetIndTexCoordScale(3, 0, 0);
    GXSetFog(0, 0.0f, 1.0f, 0.1f, 1.0f, fogColor);
    GXSetFogRangeAdj(0, 0, 0);
    GXSetBlendMode(0, 4, 5, 0);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    GXSetZMode(1, 3, 1);
    GXSetZCompLoc(1);
    GXSetDither(1);
    GXSetDstAlpha(0, 0);
    GXSetPixelFmt(0, 0);
    GXSetFieldMask(1, 1);
    GXPokeColorUpdate(1);
    GXPokeAlphaUpdate(1);
    GXPokeDither(0);
    GXPokeBlendMode(0, 0, 1, 0xF);
    GXPokeAlphaMode(7, 0);
    GXPokeAlphaRead(1);
    GXPokeDstAlpha(0, 0);
    GXPokeZMode(1, 7, 1);
    GXSetGPMetric(0x23, 0x16);
    GXClearGPMetric();
}

static inline void copyEFBImpl(void* xfb) {
    gsgfxState->xfb = xfb;
    gsgfxState->phase = 1;
    GSgfxVideoBuildEFB2XFBCopy(_renderXFBCommandBuf, gsgfxState->xfb);
    if (!GSgfxTokenCleared(_renderXFBCopyToken)) {
        GSgfxVideoGetVsyncCount();
        while (!GSgfxTokenCleared(_renderXFBCopyToken)) {
        }
    }
    GSgfxGPUProcessBlock((GSgfx_GCFifoObj*)_renderXFBCommandFifo, _renderXFBCommandBuf, _renderXFBCommandBuf + 0x60);
}

static void _renderBreakpointCallback() {
    switch (gsgfxState->phase) {
    case 0: {
        {
            s32 level;
            GSgfxRenderFifoItem* cur = gsgfxState->fifoList;
            if (cur->callback != 0) {
                level = OSEnableInterrupts();
                cur->callback(cur->callbackArg);
                OSRestoreInterrupts(level);
            }
        }
        gsgfxState->fifoList++;
        GSgfxRenderFifoItem* item = gsgfxState->fifoList;
        if (item->fifo != 0) {
            GSgfxPerfbarGPUEntry(item->color);
            GSgfxGPUProcessBlock(item->fifo, item->start, item->end);
        } else {
            GSgfxPerfbarGPUEnd();
            void* xfb = GSgfxVideoFindFreeXFB(false);
            if (xfb == 0) {
                GSgfxVideoSetOneShotPostCallback(_renderCopyEFB);
            } else {
                copyEFBImpl(xfb);
            }
        }
        break;
    }
    case 1:
        void* xfb = gsgfxState->xfb;
        _renderLastXFBPtr = xfb;
        GSgfxVideoSetXFBReady(xfb);
        gsgfxState->phase = 0;
        gsgfxState->xfb = 0;
        break;
    }
}

static void _renderCopyEFB(void* xfb) {
    copyEFBImpl(xfb);
}

static void _renderDrawDoneCallback() {
    if (GSgfxVideoGetXFBCount() != 1) {
        void* xfb = gsgfxState->xfb;
        _renderLastXFBPtr = xfb;
        GSgfxVideoSetXFBReady(xfb);
        gsgfxState->xfb = 0;
    }
}
