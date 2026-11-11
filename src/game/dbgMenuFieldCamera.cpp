#include <dolphin/types.h>

#pragma peephole off

extern "C" {

bool menuIsCheck(s32 menuID);
#ifdef __MWERKS__
void menuOpenCustom(s32 menuID, ...);
#else
s32 menuOpenCustom(s32 menu_id, s32 parent_id, s32* cursor_out, u32 close_flags, u8 check_cursor, s32 open_param, ...);
#endif
void menuSetPosition(s32 menuID, s32 x, s32 y);
u32 GSfloorGetCurrent(void);
u32 floorFieldCameraEditorGetFloorID(void);
void floorInitFieldCameraEditor(u32 floorID);

static s32 gSelected_row;
static s32 gSelected_column;
static s32 gSelectedMenu_column;
static u8 gSaveResult;

#pragma force_active on
s32 dbgMenuFieldCameraChangeDisp(void) {
    if (!menuIsCheck(0x23)) {
        u32 floorID = GSfloorGetCurrent();
        if (floorID != floorFieldCameraEditorGetFloorID()) {
            floorInitFieldCameraEditor(floorID);
            gSelected_row = 0;
            gSelected_column = 0;
            gSelectedMenu_column = 0;
        }
        gSaveResult = 0;
        menuOpenCustom(0x23, 0, 0, 0, 1, 0);
        menuSetPosition(0x23, 12, 10);
    }
    return 0;
}
#pragma force_active reset

}
