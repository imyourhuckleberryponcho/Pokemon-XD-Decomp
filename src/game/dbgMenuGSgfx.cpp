#include <dolphin/types.h>

#pragma peephole off

extern "C" {

bool menuIsCheck(s32 menuID);
void menuClose(s32 menuID);
void menuOpenCustom(s32 menuID, ...);
void menuSetPosition(s32 menuID, s32 x, s32 y);
bool GSgfxLayerGetStatsRenderMode(void);
void GSgfxLayerSetStatsRenderMode(bool mode);

#pragma force_active on

s32 dbgMenuGSgfxChangeDisp(void) {
    if (menuIsCheck(8)) {
        menuClose(8);
    } else {
        menuOpenCustom(8, 0, 0, 0, 1, 0);
        menuSetPosition(8, 380, 32);
    }
    return 0;
}

s32 dbgMenuLayerFifoDisp(void) {
    if (!GSgfxLayerGetStatsRenderMode()) {
        GSgfxLayerSetStatsRenderMode(true);
    } else {
        GSgfxLayerSetStatsRenderMode(false);
    }
    return 0;
}

#pragma force_active reset

}
