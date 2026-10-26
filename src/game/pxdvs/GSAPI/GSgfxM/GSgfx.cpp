#include <dolphin/types.h>

#pragma pool_strings off

enum GSgfxVideoMode {
    GS_GFX_VIDEO_MODE_0
};

enum GSgfxLayerID {
    GS_GFX_LAYER_ID_0
};

enum GSgfxLayerType {
    GS_GFX_LAYER_TYPE_0
};

enum GSscratchNotify {
    GS_SCRATCH_NOTIFY_RELEASE,
    GS_SCRATCH_NOTIFY_ACQUIRE,
};

struct _GSgfxInitParms {
    u8 halt;
    u8 unk1[3];
    u8 videoFlags;
    u8 unk5;
    u16 efbHeight;
    GSgfxVideoMode videoMode;
    u32 layerWidth;
    u32 layerHeight;
    u32 layerFlags;
};

struct GSgfxState {
    u8 unk0[0xC64];
};

class GSgfxLayer {
public:
    GSgfxLayer(GSgfxLayerID id, char* name, u32 width, u32 height, u32 flags, GSgfxLayerType type);

private:
    u8 unk0[0x1A14];
};

void GSgfxVideoShutdown();
void GSgfxGPUShutdown();
void GSgfxVideoInit(u8 flags, u16 efbHeight, GSgfxVideoMode mode);
void GSgfxGPUInit();
void GSgfxVideoSecondInit();
void GSgfxHaltInit();
void GSgfxRenderInit();
void GSgfxVFInit();
void GSgfxLayerInit();
void GSgfxTokenInit();
void GSgfxPerfbarInit(u8);
void GSgfxBackFBInit();
void GSgfxResetInit();
void GSgfxRenderSetupFirstFrame();

extern "C" {
void* memcpy(void* dst, const void* src, unsigned long n);
void* memset(void* dst, int c, unsigned long n);
void* GSscratchAlloc(s32 id, void (*notify)(GSscratchNotify, void*, unsigned char));
void GSgfx_GCFirstInit(void);
void GSgfx_GCInitState(void);
void GSmathInit(void);
void HSD_Init(void);
void GSlogWrite(const char* fmt, ...);
}

static GSgfxState _gfxMemoryState;
extern "C" GSgfxState* gsgfxState;
GSgfxState* gsgfxState;

static void _gfxScratchNotify(GSscratchNotify notify, void* mem, unsigned char);

extern "C" void GSgfxRelocToScratch(void) {
    GSgfxState* state = (GSgfxState*)GSscratchAlloc(0xC, _gfxScratchNotify);
    memcpy(state, gsgfxState, sizeof(GSgfxState));
    gsgfxState = state;
}

void GSgfxShutdown() {
    GSgfxVideoShutdown();
    GSgfxGPUShutdown();
}

void GSgfxInit(_GSgfxInitParms* parms) {
    gsgfxState = &_gfxMemoryState;
    memset(&_gfxMemoryState, 0, sizeof(GSgfxState));
    GSgfx_GCFirstInit();
    GSgfx_GCInitState();
    GSgfxVideoInit(parms->videoFlags, parms->efbHeight, parms->videoMode);
    GSgfxGPUInit();
    GSgfxVideoSecondInit();
    if (parms->halt == 1) {
        GSgfxHaltInit();
    }
    GSmathInit();
    GSgfxRenderInit();
    GSgfxVFInit();
    GSgfxLayerInit();
    GSgfxTokenInit();
    GSgfxPerfbarInit(4);
    GSgfxBackFBInit();
    GSgfxResetInit();
    HSD_Init();
    new GSgfxLayer((GSgfxLayerID)2, "main", parms->layerWidth, parms->layerHeight, parms->layerFlags,
                   (GSgfxLayerType)0);
    GSgfxRenderSetupFirstFrame();
    GSlogWrite("GSgfx: Init OK, state located at %08Xh (size=%d)\n", gsgfxState, sizeof(GSgfxState));
}

static void _gfxScratchNotify(GSscratchNotify notify, void* mem, unsigned char) {
    switch (notify) {
    case GS_SCRATCH_NOTIFY_RELEASE:
        memcpy(&_gfxMemoryState, mem, sizeof(GSgfxState));
        gsgfxState = &_gfxMemoryState;
        break;
    case GS_SCRATCH_NOTIFY_ACQUIRE:
        memcpy(mem, &_gfxMemoryState, sizeof(GSgfxState));
        gsgfxState = (GSgfxState*)mem;
        break;
    }
}
