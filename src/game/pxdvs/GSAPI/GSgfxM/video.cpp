// STATUS (cVid): 25/32 exact with extra_cflags=["-inline noauto"]. `#pragma opt_common_subs off` (= -opt nocse) is needed
// (target recomputes &_videoState after calls). Volatile hints that match: xfbCount, cur, lockRate, lockCount, vsyncCount,
// vsyncCB, efbHeightParam, _videoOneShotPostCB (ISR-shared). Not exact: SetupNextFrame 96.9 (register order), CopyEFBToXFB 96.5,
// FindFree/SetXFBReady 98.6 (unused findXFBByState result keeps `bne;b` in target; e/now register order), GetClearColor 94.6
// (target loads r,g,b,a ascending), Init 90.9 (i/st/ptr register order), UpdateViewport 89.3 (load scheduling). LAYOUT: the weak
// pixel-format statics (GSgfx_GCWritePixelFmt) duplicate layer.cpp's, so .sdata differs in fcheck until the linker dedupes them.
#include <dolphin/types.h>
#include <dolphin/os.h>

#pragma pool_strings off
#pragma opt_common_subs off

enum GSgfxVideoMode {
    GS_GFX_VIDEO_MODE_0,
    GS_GFX_VIDEO_MODE_1,
    GS_GFX_VIDEO_MODE_2,
    GS_GFX_VIDEO_MODE_3
};

enum GSgfxVideoFrame {
    GS_GFX_VIDEO_FRAME_0,
    GS_GFX_VIDEO_FRAME_1,
    GS_GFX_VIDEO_FRAME_2
};

enum GSgfxVideoFilter {
    GS_GFX_VIDEO_FILTER_0,
    GS_GFX_VIDEO_FILTER_1,
    GS_GFX_VIDEO_FILTER_2
};

struct GSgfxCol {
    u8 r, g, b, a;
};

struct GSgfxRenderWaitData {
    s32 lastVsync;
    s32 perfEntry;
};

// Request block for the EFB -> XFB copy (layout shared with gamecube.cpp).
#pragma pack(push, 1)
struct CopyReq {
    u16 left;
    u16 top;
    u16 width;
    u16 height;
    u16 dstWidth;
    u16 pad0a;
    u32 clamp;
    u32 f10;
    u32 f14;
    f32 gamma;
    u8 clear;
    u32 color;
    u8 pad21[3];
    u32 z;
};
#pragma pack(pop)

struct GSgfxXFB {
    s32 state;
    void* buf;
};

// The first 0x3C bytes are a GXRenderModeObj (copied from the mode list).
struct GSgfxVideoState {
    u32 viTVmode;
    u16 fbWidth;
    u16 efbHeight;
    u16 xfbHeight;
    u16 viXOrigin;
    u16 viYOrigin;
    u16 viWidth;
    u16 viHeight;
    u16 pad12;
    u32 xFBmode;
    u8 fieldRendering;
    u8 aa;
    u8 samplePattern[24];
    u8 vfilter[7];
    u8 pad39[3];
    GSgfxXFB xfb[3];
    GSgfxXFB* volatile cur;
    volatile u8 xfbCount;
    u8 vsyncRate;
    u8 nextField;
    u8 pad5b;
    volatile u16 efbHeightParam;
    u16 xfbHeightMax;
    volatile s32 vsyncCount;
    GSgfxVideoMode mode;
    void (* volatile vsyncCB)(u32);
    s32 dropCount;
    s32 flipCount;
    f32 renderTime;
    f32 realTime;
    u8 pad7c[4];
    OSTime lastTime;
    volatile s32 lockRate;
    volatile u8 lockCount;
    u8 lockActive;
    u8 pad8e[2];
    u32 f90;
    s32 f94;
    f32 yScale;
    GSgfxCol clear;
    u32 clearZ;
    u8 padA4[4];
};

struct GSgfxViewport {
    f32 x, y, w, h, nearZ, farZ;
};

struct GSgfxVideoModeEntry {
    s32 id;
    const void* modes[4];
};

struct GSgfxVideoGlobals {
    u8 unk0[0xC24];
    f32 vp[6];
    s32 vpField;
    u8 unkC40[4];
};

struct GlobalRegState {
    u8 b0, b1, b2, b3, b4;
};

extern "C" {
extern GSgfxVideoGlobals* gsgfxState;
extern GlobalRegState _gcGlobalRegState;
void* memcpy(void* dst, const void* src, unsigned long n);
void* memset(void* dst, int c, unsigned long n);
void DCFlushRange(void* addr, u32 nBytes);
void* GSmemAlloc(u32 size);
void VIInit(void);
void VISetPreRetraceCallback(void (*cb)(u32));
void VISetPostRetraceCallback(void (*cb)(u32));
void VISetBlack(u32 black);
void VIConfigure(const void* rm);
void VIFlush(void);
void VIWaitForRetrace(void);
void VISetNextFrameBuffer(void* fb);
u32 VIGetNextField(void);
void GXDrawDone(void);
f32 GXGetYScaleFactor(u16 efbHeight, u16 xfbHeight);
bool GSgfxRenderIsPaused(void);
u8* GSgfx_GCWriteCopyFilterDirect(u8* p, u8 aa, u8* pat, u8 vf, u8* vfilt);
u8* GSgfx_GCWriteCopyDispDirect(u8* p, CopyReq* req, u32 dest, u8 colorUpd, u8 alphaUpd, u8 clear);
void GSgfx_GCWriteCopyDisp(CopyReq* req, u32 dest, u8 colorUpd, u8 alphaUpd, u8 clear);
void GSgfx_GCWriteCopyFilter(u8 aa, u8* pat, u8 vf, u8* vfilt);
void GSgfx_GCFlushState(void);

extern u8 GXNtsc240Ds[], GXPal264Ds[], GXEurgb60Hz240Ds[], GXMpal240Ds[];
extern u8 GXNtsc240DsAa[], GXPal264DsAa[], GXEurgb60Hz240DsAa[], GXMpal240DsAa[];
extern u8 GXNtsc240Int[], GXPal264Int[], GXEurgb60Hz240Int[], GXMpal240Int[];
extern u8 GXNtsc240IntAa[], GXPal264IntAa[], GXEurgb60Hz240IntAa[], GXMpal240IntAa[];
extern u8 GXNtsc480Int[], GXPal528Int[], GXEurgb60Hz480Int[], GXMpal480Int[];
extern u8 GXNtsc480IntDf[], GXPal528IntDf[], GXEurgb60Hz480IntDf[], GXMpal480IntDf[];
extern u8 GXNtsc480IntAa[], GXPal524IntAa[], GXEurgb60Hz480IntAa[], GXMpal480IntAa[];
extern u8 GXNtsc480Prog[], GXNtsc480ProgSoft[], GXNtsc480ProgAa[];
}

void GSgfxSSGetViewportOffset(f32* x, f32* y);
void GSgfxRenderWaitInit(GSgfxRenderWaitData* d);
void GSgfxRenderWaitTick(GSgfxRenderWaitData* d);
void GSgfxRenderWaitExit(GSgfxRenderWaitData* d);
void GSgfxVideoSetViewport(f32 x, f32 y, f32 x2, f32 y2, bool b);
void GSgfxVideoResetViewport(bool b);

static void _videoUpdateViewport(bool b);
static bool _videoSetupRenderMode(GSgfxVideoMode mode, GSgfxVideoFrame frame, bool b1, GSgfxVideoFilter filter, bool b2);
static void _videoPostRetraceFunc(u32 count);
static void _videoPreRetraceFunc(u32 count);

// The write-gather pipe vertex data is sent through.
#define GX_WGPIPE (*(volatile union { u8 u8; u16 u16; f32 f32; }*)0xCC008000)

extern "C" {
// From the precompiled GS header (only the function-local statics are emitted here; the real ones live in layer.cpp).
inline void GSgfx_GCWritePixelFmt(int fmt) {
    static u8 pxf2hw[8] = {0, 1, 2, 3, 4, 4, 4, 5};
    static u8 yuvmap[4] = {0, 1, 2, 2};
    _gcGlobalRegState.b3 = 0;
    _gcGlobalRegState.b2 = pxf2hw[fmt];
    if (fmt < 4) {
        _gcGlobalRegState.b4 = 0;
    } else {
        _gcGlobalRegState.b4 = yuvmap[fmt - 4];
    }
    *(u32*)gsgfxState |= 0x18;
}
}

static GSgfxVideoModeEntry _videoModeList[] = {
    {1, {GXNtsc240Ds, GXPal264Ds, GXEurgb60Hz240Ds, GXMpal240Ds}},
    {2, {GXNtsc240DsAa, GXPal264DsAa, GXEurgb60Hz240DsAa, GXMpal240DsAa}},
    {3, {GXNtsc240Int, GXPal264Int, GXEurgb60Hz240Int, GXMpal240Int}},
    {4, {GXNtsc240IntAa, GXPal264IntAa, GXEurgb60Hz240IntAa, GXMpal240IntAa}},
    {5, {GXNtsc480Int, GXPal528Int, GXEurgb60Hz480Int, GXMpal480Int}},
    {6, {GXNtsc480IntDf, GXPal528IntDf, GXEurgb60Hz480IntDf, GXMpal480IntDf}},
    {7, {GXNtsc480IntAa, GXPal524IntAa, GXEurgb60Hz480IntAa, GXMpal480IntAa}},
    {8, {GXNtsc480Prog, 0, 0, 0}},
    {9, {GXNtsc480ProgSoft, 0, 0, 0}},
    {10, {GXNtsc480ProgAa, 0, 0, 0}},
    {0, {0, 0, 0, 0}},
};

static GSgfxVideoState _videoState;
static GSgfxViewport _viewport;
static u8 _videoDefaultFilter[7] = {8, 8, 10, 12, 10, 8, 8};
static void (* volatile _videoOneShotPostCB)(void*);

static inline GSgfxXFB* findXFBByBuf(void* buf) {
    s32 i;
    for (i = 0; i < _videoState.xfbCount; i++) {
        if (_videoState.xfb[i].buf == buf) {
            return &_videoState.xfb[i];
        }
    }
    return 0;
}

static inline GSgfxXFB* findXFBByState(s32 state) {
    s32 i;
    for (i = 0; i < _videoState.xfbCount; i++) {
        if (_videoState.xfb[i].state == state) {
            return &_videoState.xfb[i];
        }
    }
    return 0;
}

static inline void initCopyReq(CopyReq* req) {
    req->left = 0;
    req->top = 0;
    req->width = 640;
    req->height = 480;
    req->dstWidth = 640;
    req->clamp = 3;
    req->f10 = 0;
    req->f14 = _videoState.f90;
    req->gamma = _videoState.yScale;
    req->clear = 1;
    req->color = *(u32*)&_videoState.clear;
    req->z = _videoState.clearZ;
}

static inline GSgfxXFB* findFreeRaw(bool wait) {
    GSgfxXFB* e;
    if (_videoState.xfbCount == 1) {
        e = 0;
    } else {
        GSgfxRenderWaitData w;
        GSgfxRenderWaitInit(&w);
        while (1) {
            s32 level = OSDisableInterrupts();
            e = findXFBByState(3);
            OSRestoreInterrupts(level);
            if (e != 0) {
                GSgfxRenderWaitExit(&w);
                break;
            }
            if (!wait) {
                GSgfxRenderWaitExit(&w);
                e = 0;
                break;
            }
            GSgfxRenderWaitTick(&w);
        }
    }
    return e;
}

static inline GSgfxXFB* findFreeEntry(bool wait) {
    if (_videoState.xfbCount == 3) {
        findXFBByState(4);
    }
    return findFreeRaw(wait);
}

static inline bool setXFBReadyImpl(void* xfb) {
    s32 level = OSDisableInterrupts();
    GSgfxXFB* e;
    if (_videoState.xfbCount == 1) {
        e = _videoState.cur;
    } else {
        e = findXFBByBuf(xfb);
        if (e == 0) {
            OSRestoreInterrupts(level);
            return 0;
        }
        if (_videoState.xfbCount == 3) {
            GSgfxXFB* old = findXFBByState(2);
            if (old != 0) {
                old->state = 3;
            }
        }
        OSTime now = OSGetTime();
        _videoState.renderTime = (f32)(now - _videoState.lastTime) / (f32)(OS_TIMER_CLOCK / _videoState.vsyncRate);
        _videoState.lastTime = now;
    }
    e->state = 2;
    OSRestoreInterrupts(level);
    return 1;
}

u32 GSgfxVideoBuildEFB2XFBCopy(void* cmd, void* xfb) {
    GSgfxXFB* e = findXFBByBuf(xfb);
    e->state = 4;
    CopyReq req;
    initCopyReq(&req);
    u8* p = GSgfx_GCWriteCopyFilterDirect((u8*)cmd, _videoState.aa, _videoState.samplePattern, 1, _videoState.vfilter);
    p = GSgfx_GCWriteCopyDispDirect(p, &req, (u32)e->buf, 1, 1, 1);
    u32 size = p - (u8*)cmd;
    u32 rounded = (size + 31) & ~31;
    u32 pad = rounded - size;
    if (pad != 0) {
        memset(p, 0, pad);
    }
    DCFlushRange(cmd, rounded);
    return rounded;
}

GSgfxVideoState* GSgfxVideoGetRenderMode() {
    return &_videoState;
}

extern "C" {
GSgfxViewport* GSgfxVideoGetViewport() {
    return &_viewport;
}
}

void GSgfxVideoResetViewport(bool b) {
    GSgfxVideoSetViewport(0.0f, 0.0f, 0.5f * _videoState.fbWidth, 0.5f * _videoState.efbHeight, b);
}

void GSgfxVideoSetViewport(f32 x, f32 y, f32 x2, f32 y2, bool b) {
    _viewport.x = x;
    _viewport.y = y;
    _viewport.w = 2.0f * (x2 - x);
    _viewport.h = 2.0f * (y2 - y);
    _viewport.nearZ = 0.0f;
    _viewport.farZ = 1.0f;
    _videoUpdateViewport(b);
}

void GSgfxVideoSetupNextFrame() {
    _videoState.realTime = _videoState.renderTime;
    _gcGlobalRegState.b0 = _videoState.viHeight >= _videoState.xfbHeight * 2;
    _gcGlobalRegState.b1 = _videoState.fieldRendering;
    *(u32*)gsgfxState |= 0x1400;
    if (_videoState.aa == 1) {
        GSgfx_GCWritePixelFmt(2);
    } else {
        GSgfx_GCWritePixelFmt(_videoState.f94);
    }
    _videoState.nextField = VIGetNextField();
    GSgfxVideoResetViewport(0);
    GSgfx_GCFlushState();
}

void* GSgfxVideoCopyEFBToXFB() {
    GSgfxXFB* e;
    if (_videoState.xfbCount == 1) {
        setXFBReadyImpl(0);
        VIWaitForRetrace();
        return 0;
    }
    e = findFreeEntry(1);
    e->state = 4;
    CopyReq req;
    initCopyReq(&req);
    GSgfx_GCWriteCopyFilter(_videoState.aa, _videoState.samplePattern, 1, _videoState.vfilter);
    GSgfx_GCWriteCopyDisp(&req, (u32)e->buf, 1, 1, 1);
    return e->buf;
}

extern "C" {
void GSgfxVideoGetEFBSize(u16* w, u16* h) {
    if (w != 0) {
        *w = _videoState.fbWidth;
    }
    if (h != 0) {
        *h = _videoState.efbHeight;
    }
}
}

extern "C" {
f32 GSgfxVideoGetLastRealRenderTime() {
    return _videoState.realTime;
}
}

extern "C" {
f32 GSgfxVideoGetLastRenderTime() {
    if (GSgfxRenderIsPaused() == 1) {
        return 0.0f;
    }
    if (_videoState.lockActive == 1) {
        return _videoState.realTime;
    }
    return (u32)(_videoState.lockRate + 1);
}
}

extern "C" {
s32 GSgfxVideoGetVsyncCount() {
    return _videoState.vsyncCount;
}
}

extern "C" {
u8 GSgfxVideoGetVsyncRate() {
    return _videoState.vsyncRate;
}
}

bool GSgfxVideoSetXFBReady(void* xfb) {
    return setXFBReadyImpl(xfb);
}

void* GSgfxVideoFindFreeXFB(bool wait) {
    GSgfxXFB* e = findFreeEntry(wait);
    if (e == 0) {
        return 0;
    }
    return e->buf;
}

extern "C" {
u8 GSgfxVideoGetXFBCount() {
    return _videoState.xfbCount;
}
}

extern "C" {
u8 GSgfxVideoGetLockFrameActive() {
    return _videoState.lockActive;
}
}

extern "C" {
s32 GSgfxVideoGetLockFrameRate() {
    return _videoState.lockRate;
}
}

extern "C" {
void GSgfxVideoSetLockFrameActive(u8 active) {
    _videoState.lockActive = active;
}
}

extern "C" {
void GSgfxVideoSetLockFrameRate(int rate) {
    GSgfxVideoState* st = &_videoState;
    if (st->lockRate == rate) {
        return;
    }
    st->lockRate = rate;
    st->lockCount = st->lockRate;
}
}

extern "C" {
void GSgfxVideoSetFilter(u8* filter) {
    GSgfxVideoState* st = &_videoState;
    if (filter == 0) {
        memcpy(st->vfilter, _videoDefaultFilter, 7);
    } else {
        memcpy(st->vfilter, filter, 7);
    }
}
}

static inline void colorSet(GSgfxCol* d, u8 r, u8 g, u8 b, u8 a) {
    d->r = r;
    d->g = g;
    d->b = b;
    d->a = a;
}

extern "C" {
void GSgfxVideoGetClearColor(GSgfxCol* out) {
    enum TsE { TsE0 };
    enum TsE r = (enum TsE)(_videoState.clear.r);
    u8 g = _videoState.clear.g;
    u8 a = _videoState.clear.a;
    u8 b = _videoState.clear.b;
    colorSet(out, r, g, b, a);
}
}

extern "C" {
void GSgfxVideoSetClearColor(GSgfxCol* in) {
    _videoState.clear = *in;
}
}

extern "C" {
void (*GSgfxVideoSetVSyncCallback(void (*cb)(u32)))(u32) {
    void (*old)(u32) = _videoState.vsyncCB;
    _videoState.vsyncCB = cb;
    return old;
}
}

void GSgfxVideoSetOneShotPostCallback(void (*cb)(void*)) {
    _videoOneShotPostCB = cb;
}

extern "C" {
bool GSgfxVideoSetMode(GSgfxVideoMode mode, GSgfxVideoFrame frame, bool b1, GSgfxVideoFilter filter, bool b2) {
    if (b2 == 1) {
        if (mode != 0) {
            return 0;
        }
        if (frame != 1) {
            return 0;
        }
    }
    if (mode == 1 && _videoState.xfbHeightMax != 0x210) {
        return 0;
    }
    if (!_videoSetupRenderMode(mode, frame, b1, filter, b2)) {
        return 0;
    }
    VISetBlack(1);
    VIConfigure(&_videoState);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
    VISetBlack(0);
    VIFlush();
    return 1;
}
}

void GSgfxVideoShutdown() {
    VISetPreRetraceCallback(0);
    VISetPostRetraceCallback(0);
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();
}

static inline void secondInitCopy() {
    CopyReq req;
    void* buf = _videoState.cur->buf;
    initCopyReq(&req);
    GSgfx_GCWriteCopyFilter(_videoState.aa, _videoState.samplePattern, 1, _videoState.vfilter);
    GSgfx_GCWriteCopyDisp(&req, (u32)buf, 1, 1, 1);
}

void GSgfxVideoSecondInit() {
    CopyReq req;
    void* buf = _videoState.cur->buf;
    initCopyReq(&req);
    GSgfx_GCWriteCopyFilter(_videoState.aa, _videoState.samplePattern, 1, _videoState.vfilter);
    GSgfx_GCWriteCopyDisp(&req, (u32)buf, 1, 1, 1);
    secondInitCopy();
    GXDrawDone();
    VISetBlack(0);
    VIFlush();
}

void GSgfxVideoInit(u8 count, u16 efbHeight, GSgfxVideoMode mode) {
    s32 i;
    GSgfxVideoState* st;
    u32 words;
    u32 bytes;
    if (count != 0 && count <= 3 && efbHeight <= 0x210) {
        VIInit();
        _videoState.xfbCount = count;
        _videoState.efbHeightParam = efbHeight;
        _videoState.vsyncCB = 0;
        _videoState.vsyncCount = 0;
        _videoOneShotPostCB = 0;
        _videoSetupRenderMode(mode, GS_GFX_VIDEO_FRAME_1, 0, GS_GFX_VIDEO_FILTER_1, 0);
        switch (mode) {
        case GS_GFX_VIDEO_MODE_0:
            _videoState.xfbHeightMax = 0x1E0;
            break;
        case GS_GFX_VIDEO_MODE_1:
        case GS_GFX_VIDEO_MODE_2:
            _videoState.xfbHeightMax = 0x210;
            break;
        case GS_GFX_VIDEO_MODE_3:
            _videoState.xfbHeightMax = 0x1E0;
            break;
        }
        st = &_videoState;
        u32 stride = ((st->fbWidth + 15) & 0xFFF0) * st->xfbHeightMax;
        bytes = stride * 2;
        words = bytes >> 2;
        for (i = 0; i < 3; i++) {
            if (i < st->xfbCount) {
                st->xfb[i].buf = GSmemAlloc(bytes);
                st->xfb[i].state = 3;
                u32* p = (u32*)st->xfb[i].buf;
                u32 n = words;
                while (n != 0) {
                    *p++ = 0x10801080;
                    n--;
                }
                DCFlushRange(st->xfb[i].buf, bytes);
            } else {
                st->xfb[i].buf = 0;
                st->xfb[i].state = 0;
            }
        }
        VISetPreRetraceCallback(_videoPreRetraceFunc);
        VISetPostRetraceCallback(_videoPostRetraceFunc);
        _videoState.xfb[0].state = 1;
        VISetNextFrameBuffer(_videoState.xfb[0].buf);
        _videoState.cur = &_videoState.xfb[0];
        _videoState.f90 = 0;
        _videoState.clear.r = 0;
        _videoState.clear.g = 0;
        _videoState.clear.b = 0;
        _videoState.clear.a = 0;
        _videoState.clearZ = 0xFFFFFF;
        _videoState.f94 = 0;
        _videoState.dropCount = 0;
        _videoState.flipCount = 0;
        _videoState.lockActive = 0;
        _videoState.renderTime = 0.0f;
        _videoState.realTime = 0.0f;
        _videoState.lastTime = OSGetTime();
        _videoState.lockRate = 0;
        _videoState.lockCount = 0;
        VISetBlack(1);
        VIConfigure(&_videoState);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
    }
}

static void _videoUpdateViewport(bool b) {
    GSgfxVideoState* st = &_videoState;
    f32 offX;
    f32 offY;
    if (!b) {
        GSgfxSSGetViewportOffset(&offX, &offY);
    } else {
        offX = 0.0f;
        offY = 0.0f;
    }
    if (st->fieldRendering != 0) {
        f32 x = _viewport.x + offX;
        f32 w = _viewport.w;
        f32 h = _viewport.h;
        f32 nz = _viewport.nearZ;
        f32 fz = _viewport.farZ;
        f32 y = _viewport.y + offY;
        GSgfxVideoGlobals* g = gsgfxState;
        u32 field = st->nextField;
        if (g->vp[0] == x && g->vp[1] == y && g->vp[2] == w && g->vp[3] == h && g->vp[4] == nz && g->vp[5] == fz &&
            (u32)g->vpField == field) {
            return;
        }
        if (field == 0) {
            y -= 0.5f;
        }
        GX_WGPIPE.u8 = 0x10;
        GX_WGPIPE.u16 = 5;
        GX_WGPIPE.u16 = 0x101A;
        f32 half = 0.5f;
        f32 zs = 16777216.0f;
        f32 halfH = h * half;
        f32 halfW = w * half;
        f32 farScaled = fz * zs;
        GX_WGPIPE.f32 = halfW;
        GX_WGPIPE.f32 = -halfH;
        GX_WGPIPE.f32 = farScaled - nz * zs;
        f32 kc1133 = 342.0f;
        GX_WGPIPE.f32 = kc1133 + (x + halfW);
        f32 kc1208 = 342.0f;
        GX_WGPIPE.f32 = kc1208 + (y + halfH);
        f32 kc1283 = 0.0f;
        GX_WGPIPE.f32 = farScaled + kc1283;
        g->vp[0] = x;
        gsgfxState->vp[1] = y;
        gsgfxState->vp[2] = w;
        gsgfxState->vp[3] = h;
        gsgfxState->vp[4] = nz;
        gsgfxState->vp[5] = fz;
        gsgfxState->vpField = field;
    } else {
        f32 x = _viewport.x + offX;
        f32 w = _viewport.w;
        f32 h = _viewport.h;
        f32 nz = _viewport.nearZ;
        f32 fz = _viewport.farZ;
        f32 y = _viewport.y + offY;
        GSgfxVideoGlobals* g = gsgfxState;
        if (g->vp[0] == x && g->vp[1] == y && g->vp[2] == w && g->vp[3] == h && g->vp[4] == nz && g->vp[5] == fz &&
            (u32)g->vpField == 1) {
            return;
        }
        GX_WGPIPE.u8 = 0x10;
        GX_WGPIPE.u16 = 5;
        GX_WGPIPE.u16 = 0x101A;
        f32 half = 0.5f;
        f32 zs = 16777216.0f;
        f32 halfH = h * half;
        f32 halfW = w * half;
        f32 farScaled = fz * zs;
        GX_WGPIPE.f32 = halfW;
        GX_WGPIPE.f32 = -halfH;
        GX_WGPIPE.f32 = farScaled - nz * zs;
        f32 kc2349 = 342.0f;
        GX_WGPIPE.f32 = kc2349 + (x + halfW);
        f32 kc2424 = 342.0f;
        GX_WGPIPE.f32 = kc2424 + (y + halfH);
        f32 kc2499 = 0.0f;
        GX_WGPIPE.f32 = farScaled + kc2499;
        g->vp[0] = x;
        gsgfxState->vp[1] = y;
        gsgfxState->vp[2] = w;
        gsgfxState->vp[3] = h;
        gsgfxState->vp[4] = nz;
        gsgfxState->vp[5] = fz;
        gsgfxState->vpField = 1;
    }
}

static bool _videoSetupRenderMode(GSgfxVideoMode mode, GSgfxVideoFrame frame, bool b1, GSgfxVideoFilter filter, bool b2) {
    s32 idx = 0;
    if (frame == GS_GFX_VIDEO_FRAME_0) {
        if (!b1) {
            if (filter != GS_GFX_VIDEO_FILTER_2) {
                idx = 1;
            } else {
                idx = 2;
            }
        } else {
            if (filter != GS_GFX_VIDEO_FILTER_2) {
                idx = 3;
            } else {
                idx = 4;
            }
        }
    } else {
        if (!b2) {
            switch (filter) {
            case GS_GFX_VIDEO_FILTER_0:
                idx = 5;
                break;
            case GS_GFX_VIDEO_FILTER_1:
                idx = 6;
                break;
            case GS_GFX_VIDEO_FILTER_2:
                idx = 7;
                break;
            }
        } else {
            switch (filter) {
            case GS_GFX_VIDEO_FILTER_0:
                idx = 8;
                break;
            case GS_GFX_VIDEO_FILTER_1:
                idx = 9;
                break;
            case GS_GFX_VIDEO_FILTER_2:
                idx = 10;
                break;
            }
        }
    }
    if (idx == 0) {
        return 0;
    }
    const void* rm = 0;
    GSgfxVideoModeEntry* ent = _videoModeList;
    s32 id;
    while ((id = ent->id) != 0) {
        if (id == idx) {
            switch (mode) {
            case GS_GFX_VIDEO_MODE_0:
                rm = ent->modes[0];
                break;
            case GS_GFX_VIDEO_MODE_1:
                rm = ent->modes[1];
                break;
            case GS_GFX_VIDEO_MODE_2:
                rm = ent->modes[2];
                break;
            case GS_GFX_VIDEO_MODE_3:
                rm = ent->modes[3];
                break;
            }
            break;
        }
        ent++;
    }
    if (rm == 0) {
        return 0;
    }
    GSgfxVideoState* st = &_videoState;
    memcpy(st, rm, 0x3C);
    if (_videoState.efbHeightParam != 0) {
        st->efbHeight = _videoState.efbHeightParam;
    }
    st->viXOrigin = 30;
    st->viWidth = 0x294;
    _videoState.mode = mode;
    if (mode == GS_GFX_VIDEO_MODE_1) {
        _videoState.vsyncRate = 50;
    } else {
        _videoState.vsyncRate = 60;
    }
    _videoState.yScale = GXGetYScaleFactor(st->efbHeight, st->xfbHeight);
    return 1;
}

static void _videoPostRetraceFunc(u32 count) {
    _videoState.vsyncCount++;
    if (_videoState.xfbCount == 1) {
        GSgfxXFB* x = _videoState.cur;
    } else if (_videoOneShotPostCB != 0) {
        GSgfxXFB* e = findFreeRaw(0);
        if (e != 0) {
            void (*cb)(void*) = _videoOneShotPostCB;
            _videoOneShotPostCB = 0;
            cb(e->buf);
        }
    }
    if (_videoState.vsyncCB != 0) {
        _videoState.vsyncCB(count);
    }
}

static void _videoPreRetraceFunc(u32 count) {
    if (_videoState.xfbCount == 1) {
        return;
    }
    if (_videoState.lockActive == 1 && _videoState.lockCount != 0) {
        _videoState.lockCount--;
        return;
    }
    GSgfxXFB* e = findXFBByState(2);
    if (e == 0) {
        _videoState.dropCount++;
        return;
    }
    _videoState.flipCount++;
    VISetNextFrameBuffer(e->buf);
    VIFlush();
    e->state = 1;
    _videoState.cur->state = 3;
    _videoState.cur = e;
    _videoState.lockCount = _videoState.lockRate;
}
