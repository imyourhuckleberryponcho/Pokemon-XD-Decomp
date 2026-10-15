#include <dolphin/types.h>

// Debug menu units were built without the peephole optimizer.
#pragma peephole off

extern "C" {

bool menuIsCheck(s32 menuID);
void menuClose(s32 menuID);
void menuOpenCustom(s32 menuID, ...);
void menuSetPosition(s32 menuID, s32 x, s32 y);
u32 GSfloorGetCurrent(void);
void* floorDataBiosGetPtr(u32 floorID);
bool floorFieldCameraDataExist(void);
void floorFieldCameraEnable(void);
void floorFieldCameraDisable(void);
void floorBlockMainScript(void);
void floorUnblockMainScript(void);

// Nothing references these, but the original link kept them.
#pragma force_active on

s32 dbgMenuDispChangePartyInfo(void) {
    if (menuIsCheck(12)) {
        menuClose(12);
    } else {
        menuOpenCustom(12, 0, 0, 0, 1, 0);
        menuSetPosition(12, 400, 40);
    }
    return 0;
}

s32 dbgMenuPeopleOpenEdit(void) {
    floorDataBiosGetPtr(GSfloorGetCurrent());
    if (menuIsCheck(10)) {
        if (floorFieldCameraDataExist()) {
            floorFieldCameraEnable();
        }
        menuClose(10);
        floorUnblockMainScript();
    } else {
        floorFieldCameraDisable();
        menuOpenCustom(10, 0, 0, 0, 0, 0);
        floorBlockMainScript();
    }
    return 0;
}

#pragma force_active reset

}
