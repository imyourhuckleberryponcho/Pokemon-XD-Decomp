#include <dolphin/types.h>
#pragma pool_strings off
#include <dolphin/os.h>

extern "C" {
void* memcpy(void* dst, const void* src, unsigned long n);
void* memset(void* dst, int c, unsigned long n);
}

typedef f32 Mtx44[4][4];

struct GSgfxCol {
    u8 r, g, b, a;
};

struct PrimCol {
    u8 r, g, b, a;
};

struct GSgfxDirty {
    u32 groups;
    u32 words[36];
    u32 textureMask;
    void* textures[8];
};

struct GSgfxMtxEntry {
    u32 flags;
    f32 mtx[3][4];
    f32 invXpose[3][4];
};

struct GSgfxMtxStack {
    u32 unk0;
    GSgfxMtxEntry* top;
};

class GSgfxLayer {
public:
    void FlushState();
    void InvalidateState();
    u16 tokenMark();

    u8 unk0[0xD54];
    u32 projType;
    f32 proj[6];
    u8 unkD70[0x1C];
    u32 cullMode;
    u32 unkD90;
    u8 unkD94[0x1644 - 0xD94];
    u32 blendType;
    u32 blendSrc;
    u32 blendDst;
    u32 blendLogicOp;
    u8 unk1654[2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 dither;
    u8 unk1659[3];
    u8 zEnable;
    u8 unk165D[3];
    u32 zFunc;
    u32 alphaComp0;
    u32 alphaOp;
    u32 alphaComp1;
    u8 alphaRef0;
    u8 alphaRef1;
    u8 alphaCompareOff;
    u8 unk1673[0x11];
    f32 clipNear;
    f32 clipFar;
    u8 unk168C[0x1A];
    u8 unk16A6;
    u8 unk16A7;
    GSgfxDirty dirty[2];
    u8 unk1818[0x19A0 - 0x1818];
    GSgfxMtxStack* mtxStack;
};

#define GFX_DIRTY(l, word, bits, group) \
    (l)->dirty[0].words[word] |= (bits); \
    (l)->dirty[0].groups |= (group);     \
    (l)->dirty[1].words[word] |= (bits); \
    (l)->dirty[1].groups |= (group);

struct PerfFrame {
    OSTime cpuStart;
    f32 cpuTotal;
    u32 cpuCount;
    f32 cpuTimes[0x400];
    u32 cpuColors[0x400];
    OSTime gpuStart;
    f32 gpuTotal;
    u32 gpuCount;
    f32 gpuTimes[0x40];
    u32 gpuColors[0x40];
    f32 renderTime;
};

extern "C" {
extern int __float_epsilon[];
extern f32 mtxIdent[3][4];
double GSgfxVideoGetLastRenderTime(void);
u8 GSgfxVideoGetVsyncRate(void);
s32 GSgfxVideoGetLockFrameRate(void);
void GSprimSetQuadVertexOrder(s32 order);
void GSprimSetLineWidth(f32 w);
void GSprimSetTextSize(f32 x, f32 y);
void GSprimSetTextWidth(f32 w);
void GSprimDraw2DQuadWH(GSgfxCol color, f32 x, f32 y, f32 w, f32 h);
void GSprimDraw2DHLine(PrimCol color, f32 x0, f32 x1, f32 y);
void GSprimDraw2DVLine(PrimCol color, f32 x, f32 y0, f32 y1);
void GSprimWriteStr(f32 x, f32 y, char* fmt, ...);
void GSmtx44Ortho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void GXSetProjection(const f32 mtx[4][4], u32 type);
void GXCallDisplayList(void* list, u32 nbytes);
void GXBeginDisplayList(void* list, u32 size);
u32 GXEndDisplayList(void);
void GXFlush(void);
void GXResetWriteGatherPipe(void);
void DCFlushRange(void* addr, u32 nBytes);
void* GSmemAlloc(u32 size);
void GSmemFree(void* p);
void* GSmemAllocAlign(u32 size, u32 align);
void GSgfxTokenWaitForClearAndReset(u16* token);
void PERFInit(u32 samples, u32 history, u32 types, void* (*alloc)(u32), void (*dealloc)(void*), void (*initDraw)());
void PERFSetDrawBWBarKey(u32 on);
void PERFSetDrawSyncCallback(void (*cb)(u16));
void PERFStartFrame(void);
void PERFEndFrame(void);
void PERFStartAutoSampling(f32 rate);
void PERFStopAutoSampling(void);
void PERFPreDraw(void);
void PERFPostDraw(void);
void PERFDumpScreen(void);
}

void GSprimSetRenderLayer(GSgfxLayer* layer);
void GSgfxTokenSetDrawSyncCBFunc(void (*func)(void (*)(u16)));
void GSgfxGPUGetBPTick(s32* a, s32* b);

static PerfFrame _perfLastFrame;
static PerfFrame _perfCurFrame;
static f32 _perfPERFMtx[4][4];

static s32 _perfRenderMode = 1;
static GSgfxCol _perfBkgnd = {0x20, 0x20, 0x20, 0xC0};

static u8 _perfFrameCount;
static f32 _perfPixelSkip;
static f32 _perfPeakCPU;
static f32 _perfPeakGPU;
static s32 _perfPeakCPUTimer;
static s32 _perfPeakGPUTimer;
static s32 _perfUpdateCount;
static f32 _perfUpdateTime;
static f32 _perfUpdateFPS;
static void* _perfDisplayList;
static u32 _perfDListSize;
static u8 _perfFullStarted;
static u16 _perfDListToken;

static void _perfRestoreGPU();
static inline PerfFrame* perfLast() {
    return &_perfLastFrame;
}

extern "C" {
inline GSgfxCol* GSgfxPerfColorToGSgfxCol(u32 color) {
    static GSgfxCol c;
    c.b = color;
    c.g = color >> 8;
    c.r = color >> 16;
    c.a = 0xFF;
    return &c;
}
}

void GSgfxPerfbarRender(GSgfxLayer* layer) {
    if (_perfRenderMode == 0) {
        return;
    }
    u32 j;
    f32 next;
    OSTime start = OSGetTime();
    PerfFrame* last = &_perfLastFrame;
    f32 cpuTime = last->cpuTotal + last->renderTime;
    last->cpuTotal = cpuTime;
    if (cpuTime > _perfPeakCPU || _perfPeakCPUTimer-- < 0) {
        _perfPeakCPU = cpuTime;
        _perfPeakCPUTimer = 60;
    }
    PerfFrame* lastGpu = &_perfLastFrame;
    f32 gpuTime = lastGpu->gpuTotal;
    if (gpuTime > _perfPeakGPU || _perfPeakGPUTimer-- < 0) {
        _perfPeakGPU = gpuTime;
        _perfPeakGPUTimer = 60;
    }
    if (_perfUpdateCount-- < 0) {
        double t = GSgfxVideoGetLastRenderTime();
        _perfUpdateTime = t;
        if ((f32)t > *(f32*)__float_epsilon) {
            _perfUpdateFPS = 0.1f + GSgfxVideoGetVsyncRate() / _perfUpdateTime;
            if (_perfUpdateFPS > 60.0f) {
                _perfUpdateFPS = 60.0f;
            }
        } else {
            _perfUpdateFPS = 0.0f;
        }
        _perfUpdateCount = 6;
    }
    GSprimSetRenderLayer(layer);
    GSprimSetQuadVertexOrder(0);
    GSprimSetLineWidth(1.0f);
    GSprimSetTextSize(10.0f, 10.0f);
    GSprimSetTextWidth(1.0f);

    layer->blendType = 1;
    layer->blendSrc = 4;
    layer->blendDst = 5;
    layer->blendLogicOp = 5;
    GFX_DIRTY(layer, 24, 1, 0x40)

    Mtx44 ortho;
    GSmtx44Ortho(ortho, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    layer->projType = 1;
    layer->proj[0] = ortho[0][0];
    layer->proj[1] = ortho[0][3];
    layer->proj[2] = ortho[1][1];
    layer->proj[3] = ortho[1][3];
    layer->proj[4] = ortho[2][2];
    layer->proj[5] = ortho[2][3];
    GSgfxMtxStack* stack = layer->mtxStack;
    memcpy(stack->top->mtx, mtxIdent, 0x30);
    stack->top->flags |= 1;
    layer->clipNear = 0.0f;
    layer->clipFar = 30000.0f;
    if (layer->unk16A7) {
        if (layer->unk16A6) {
            layer->dirty[0].words[24] |= 0x100;
            layer->dirty[1].words[24] |= 0x100;
        }
        GFX_DIRTY(layer, 24, 0x40, 0x40)
    }
    GFX_DIRTY(layer, 0, 0x20, 1)

    layer->colorUpdate = 1;
    layer->alphaUpdate = 0;
    layer->dither = 0;
    GFX_DIRTY(layer, 24, 4, 0x40)
    layer->zEnable = 0;
    layer->zFunc = 3;
    GFX_DIRTY(layer, 24, 8, 0x40)
    layer->alphaComp0 = 7;
    layer->alphaRef0 = 0;
    layer->alphaOp = 0;
    layer->alphaComp1 = 7;
    layer->alphaRef1 = 0;
    layer->alphaCompareOff = 1;
    GFX_DIRTY(layer, 24, 0x10, 0x40)
    layer->cullMode = 0;
    GFX_DIRTY(layer, 3, 2, 2)
    layer->unkD90 = 1;
    GFX_DIRTY(layer, 3, 4, 2)

    GSprimDraw2DQuadWH(_perfBkgnd, 10.0f, 420.0f, 620.0f, 40.0f);

    f32 x = 20.0f;
    s32 i;
    for (i = 0; i < _perfFrameCount; i++) {
        u32 rgb;
        if ((u32)i < (u32)(GSgfxVideoGetLockFrameRate() + 1)) {
            rgb = 0xFF00;
        } else if (i >= 3) {
            rgb = 0xFF0000;
        } else {
            rgb = 0xFFFF00;
        }
        PrimCol pc;
        GSgfxCol col = *GSgfxPerfColorToGSgfxCol(rgb);
        pc.r = col.r;
        pc.g = col.g;
        pc.b = col.b;
        pc.a = col.a;
        next = x + _perfPixelSkip;
        GSprimDraw2DHLine(pc, x, next, 455.0f);
        GSprimDraw2DVLine(pc, x, 450.0f, 455.0f);
        GSprimDraw2DVLine(pc, next, 450.0f, 455.0f);
        x = next;
    }

    f32 worst = last->cpuTotal;
    if (lastGpu->gpuTotal > worst) {
        worst = lastGpu->gpuTotal;
    }
    GSprimDraw2DQuadWH(*GSgfxPerfColorToGSgfxCol(0x008080), 20.0f, 446.0f, _perfPixelSkip * (s32)(0.9999f + worst), 5.0f);
    GSprimDraw2DQuadWH(*GSgfxPerfColorToGSgfxCol(0x00FFFF), 20.0f, 446.0f, _perfPixelSkip * lastGpu->gpuTotal, 5.0f);
    {
        u32 j;
        PerfFrame* f = perfLast();
        f32 prev = _perfPixelSkip * f->gpuTimes[0];
        for (j = 1; j < f->gpuCount; j++) {
            f32 cur = _perfPixelSkip * f->gpuTimes[j];
            f32 w = cur - prev;
            if ((s32)w >= 1) {
                GSprimDraw2DQuadWH(*GSgfxPerfColorToGSgfxCol(f->gpuColors[j - 1]), 20.0f + prev, 446.0f, w, 5.0f);
            }
            prev = cur;
            if (cur > 640.0f) {
                break;
            }
        }
    }
    GSprimDraw2DQuadWH(*GSgfxPerfColorToGSgfxCol(0xFFFFFF), 20.0f, 440.0f, _perfPixelSkip * last->cpuTotal, 5.0f);
    {
        PerfFrame* f = perfLast();
        f32 prev = _perfPixelSkip * f->cpuTimes[0];
        for (j = 1; j < f->cpuCount; j++) {
            f32 cur = _perfPixelSkip * f->cpuTimes[j];
            f32 w = cur - prev;
            if ((s32)w >= 1) {
                GSprimDraw2DQuadWH(*GSgfxPerfColorToGSgfxCol(f->cpuColors[j - 1]), 20.0f + prev, 440.0f, w, 5.0f);
            }
            prev = cur;
            if (cur > 640.0f) {
                break;
            }
        }
    }

    s32 bpB;
    s32 bpA;
    GSgfxGPUGetBPTick(&bpA, &bpB);
    if (bpA == -1 && bpB == -1) {
        GSprimWriteStr(30.0f, 425.0f,
                       "|00ff00CUR: |ffffff%2.3f |00ffff%2.3f  |00ff00PK: |ffffff%2.3f |00ffff%2.3f  |00ff00VUPD: |ffffff%1.3f  |ffff00%2.1f FPS",
                       last->cpuTotal, lastGpu->gpuTotal, _perfPeakCPU, _perfPeakGPU, _perfUpdateTime, _perfUpdateFPS);
    } else {
        GSprimWriteStr(30.0f, 425.0f, "|ffffff%d    |ffff00%d", OSTicksToMicroseconds((u32)bpA), OSTicksToMicroseconds((u32)bpB));
    }
    if (_perfRenderMode == 2 && _perfDListSize != 0) {
        layer->FlushState();
        PERFPreDraw();
        GXSetProjection(_perfPERFMtx, 1);
        GXCallDisplayList(_perfDisplayList, _perfDListSize);
        PERFPostDraw();
        layer->InvalidateState();
        _perfDListToken = layer->tokenMark();
    }
    f32 t = (f32)(OSGetTime() - start) / (f32)(OS_TIMER_CLOCK / 60);
    _perfCurFrame.renderTime = t;
    last->renderTime = t;
}

u32 GSgfxPerfbarGPUEntry(u32 color) {
    PerfFrame* cur = &_perfCurFrame;
    u32 prev;
    if (cur->gpuCount >= 0x40) {
        return 0;
    }
    if (cur->cpuCount == 0) {
        prev = 0xFFFF;
    } else {
        prev = cur->gpuColors[cur->gpuCount - 1];
    }
    _perfCurFrame.gpuTimes[cur->gpuCount] = (f32)(OSGetTime() - _perfCurFrame.gpuStart) / (f32)(OS_TIMER_CLOCK / 60);
    _perfCurFrame.gpuColors[cur->gpuCount] = color;
    cur->gpuCount++;
    return prev;
}

extern "C" u32 GSgfxPerfbarCPUEntry(u32 color) {
    PerfFrame* cur = &_perfCurFrame;
    u32 prev;
    if (cur->cpuCount >= 0x400) {
        return 0;
    }
    if (cur->cpuCount == 0) {
        prev = 0xFFFFFF;
    } else {
        prev = cur->cpuColors[cur->cpuCount - 1];
    }
    _perfCurFrame.cpuTimes[cur->cpuCount] = (f32)(OSGetTime() - _perfCurFrame.cpuStart) / (f32)(OS_TIMER_CLOCK / 60);
    _perfCurFrame.cpuColors[cur->cpuCount] = color;
    cur->cpuCount++;
    return prev;
}

void GSgfxPerfbarGPUEnd() {
    PerfFrame* cur = &_perfCurFrame;
    if (cur->gpuCount < 0x40) {
        _perfCurFrame.gpuTimes[cur->gpuCount] = (f32)(OSGetTime() - _perfCurFrame.gpuStart) / (f32)(OS_TIMER_CLOCK / 60);
        _perfCurFrame.gpuColors[cur->gpuCount] = 0;
        cur->gpuCount++;
    }
    _perfCurFrame.gpuTotal = (f32)(OSGetTime() - _perfCurFrame.gpuStart) / (f32)(OS_TIMER_CLOCK / 60);
    memcpy(&_perfLastFrame.gpuStart, &_perfCurFrame.gpuStart, 0x210);
    memset(&_perfCurFrame.gpuStart, 0, 0x210);
}

void GSgfxPerfbarGPUStart() {
    _perfCurFrame.gpuStart = OSGetTime();
    _perfCurFrame.gpuCount = 0;
}

void GSgfxPerfbarCPUEnd() {
    PerfFrame* cur = &_perfCurFrame;
    if (cur->cpuCount < 0x400) {
        _perfCurFrame.cpuTimes[cur->cpuCount] = (f32)(OSGetTime() - _perfCurFrame.cpuStart) / (f32)(OS_TIMER_CLOCK / 60);
        _perfCurFrame.cpuColors[cur->cpuCount] = 0;
        cur->cpuCount++;
    }
    _perfCurFrame.cpuTotal = (f32)(OSGetTime() - _perfCurFrame.cpuStart) / (f32)(OS_TIMER_CLOCK / 60);
    memcpy(&_perfLastFrame, &_perfCurFrame, 0x2010);
    memset(&_perfCurFrame, 0, 0x2010);
    _perfDListSize = 0;
    if (_perfFullStarted == 1) {
        PERFEndFrame();
        PERFStopAutoSampling();
        _perfFullStarted = 0;
        if (_perfRenderMode == 2) {
            GSgfxTokenWaitForClearAndReset(&_perfDListToken);
            if (_perfDisplayList == 0) {
                _perfDisplayList = GSmemAllocAlign(0x8000, 0x20);
                DCFlushRange(_perfDisplayList, 0x8000);
            }
            GXBeginDisplayList(_perfDisplayList, 0x8000);
            GXResetWriteGatherPipe();
            PERFDumpScreen();
            GXFlush();
            _perfDListSize = GXEndDisplayList();
        }
    }
}

void GSgfxPerfbarCPUStart() {
    _perfCurFrame.cpuStart = OSGetTime();
    _perfCurFrame.cpuCount = 0;
    if (_perfRenderMode == 2) {
        PERFStartFrame();
        PERFStartAutoSampling(1.0f);
        _perfFullStarted = 1;
    }
}

extern "C" s32 GSgfxPerfbarGetRenderMode() {
    return _perfRenderMode;
}

extern "C" void GSgfxPerfbarSetRenderMode(s32 mode) {
    _perfRenderMode = mode;
}

static inline void zeroMtx44(f32 (*m)[4]) {
    f32* p = &m[0][0];
    p[0] = 0.0f;
    p[1] = 0.0f;
    p[2] = 0.0f;
    p[3] = 0.0f;
    p[4] = 0.0f;
    p[5] = 0.0f;
    p[6] = 0.0f;
    p[7] = 0.0f;
    p[8] = 0.0f;
    p[9] = 0.0f;
    p[10] = 0.0f;
    p[11] = 0.0f;
    p[12] = 0.0f;
    p[13] = 0.0f;
    p[14] = 0.0f;
    p[15] = 0.0f;
}

void GSgfxPerfbarInit(u8 frameCount) {
    _perfFrameCount = frameCount;
    if (frameCount == 0) {
        _perfFrameCount = 1;
    }
    _perfPixelSkip = 600.0f / _perfFrameCount;
    memset(&_perfLastFrame, 0, sizeof(PerfFrame));
    memset(&_perfCurFrame, 0, sizeof(PerfFrame));
    _perfPeakCPU = 0.0f;
    _perfPeakCPUTimer = 0;
    _perfPeakGPUTimer = 0;
    _perfUpdateTime = 0.0f;
    _perfUpdateFPS = 0.0f;
    _perfUpdateCount = 0;
    PERFInit(60, 1, 1, GSmemAlloc, GSmemFree, _perfRestoreGPU);
    PERFSetDrawBWBarKey(1);
    GSgfxTokenSetDrawSyncCBFunc(PERFSetDrawSyncCallback);
    zeroMtx44(_perfPERFMtx);
    _perfPERFMtx[0][0] = 0.003125f;
    _perfPERFMtx[1][1] = 0.00416667f;
    _perfPERFMtx[2][2] = 1.0f;
    _perfPERFMtx[3][3] = 1.0f;
    _perfPERFMtx[0][3] = -0.95f;
    _perfPERFMtx[1][3] = -0.6250007f;
    _perfDisplayList = 0;
    _perfDListSize = 0;
    _perfFullStarted = 0;
    _perfDListToken = 0;
    _perfCurFrame.cpuStart = OSGetTime();
    _perfCurFrame.cpuCount = 0;
    if (_perfRenderMode == 2) {
        PERFStartFrame();
        PERFStartAutoSampling(1.0f);
        _perfFullStarted = 1;
    }
    _perfCurFrame.gpuStart = OSGetTime();
    _perfCurFrame.gpuCount = 0;
}

static void _perfRestoreGPU() {
}
