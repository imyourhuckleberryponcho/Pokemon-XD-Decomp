#include <dolphin/types.h>

#pragma peephole off

extern "C" {

bool pauseIsPause(void);
f32 GSgfxVideoGetLastRenderTime(void);
u8 GSgfxVideoGetVsyncRate(void);

// Unknown function that was dead-stripped from the final link. Its float
// constants are shared with timeGetLastFrameSec, which fixes their order in .sdata2.
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
    return GSgfxVideoGetLastRenderTime() + 0.5f;
}

f32 timeGetLastFrameSec(void) {
    if (pauseIsPause()) {
        return 0.0f;
    }
    f32 rate = GSgfxVideoGetVsyncRate();
    return GSgfxVideoGetLastRenderTime() / rate;
}

}
