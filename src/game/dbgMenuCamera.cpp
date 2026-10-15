#include <dolphin/types.h>

// Debug menu units were built without the peephole optimizer.
#pragma peephole off

extern "C" {

bool menuIsCheck(s32 menuID);
void menuClose(s32 menuID);
void menuOpenCustom(s32 menuID, ...);
void menuSetPosition(s32 menuID, s32 x, s32 y);
void cameraResetFloor(void);
void cameraSetType(s32 type);

// Nothing references these, but the original link kept them.
#pragma force_active on

s32 dbgMenuCameraResetFloor(void) {
    cameraResetFloor();
    return 0;
}

s32 dbgMenuCameraChangeDisp(void) {
    if (menuIsCheck(6)) {
        menuClose(6);
    } else {
        menuOpenCustom(6, 0, 0, 0, 1, 0);
        menuSetPosition(6, 20, 260);
    }
    return 0;
}

s32 dbgMenuCameraSetType(s32, s32 type) {
    switch (type) {
    case 0:
    default:
        cameraSetType(0);
        break;
    case 1:
        cameraSetType(5);
        break;
    case 2:
        cameraSetType(6);
        break;
    }
    return 0;
}

#pragma force_active reset

}
