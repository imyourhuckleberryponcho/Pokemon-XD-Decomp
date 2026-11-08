#include <dolphin/types.h>
#include <game/ppcops.h>

#pragma peephole off

extern "C" {

bool pauseIsPause(void);
f32 GSgfxVideoGetLastRenderTime(void);
u8 GSgfxVideoGetVsyncRate(void);

f32 timeGetVsyncRate(void) {
    if (pauseIsPause()) {
        return 0.0f;
    }
    return GSgfxVideoGetVsyncRate();
}

u32 timeGetLastFrameTime(void) {
    if (pauseIsPause()) {
        return 0;
    }
    return GC_F2U32(GSgfxVideoGetLastRenderTime() + 0.5f);
}

f32 timeGetLastFrameSec(void) {
    if (pauseIsPause()) {
        return 0.0f;
    }
    f32 rate = GSgfxVideoGetVsyncRate();
    return GSgfxVideoGetLastRenderTime() / rate;
}

}
