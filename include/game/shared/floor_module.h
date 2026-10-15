#ifndef GAME_SHARED_FLOOR_MODULE_H
#define GAME_SHARED_FLOOR_MODULE_H
// FloorModuleInterface: callback table registered with floorRegisterModule().
// Merged from matched camera.cpp, hero.cpp, light.cpp and floorFieldCamera.cpp. Cleared with
// FloorModuleInterface_clear(); the module fills the callbacks it uses. hero.cpp's copy is 0x30
// (extra word at 0x2C); camera/light/floorFieldCamera use 0x2C.
#include <dolphin/types.h>

enum FloorEnterMode { FLOOR_ENTER_MODE_0, FLOOR_ENTER_MODE_1, FLOOR_ENTER_MODE_2, FLOOR_ENTER_MODE_3 };
enum FloorStateMode { FLOOR_STATE_MODE_0, FLOOR_STATE_MODE_1, FLOOR_STATE_MODE_2, FLOOR_STATE_MODE_3 };

struct FloorModuleInterface {
    u32 unk0;                                                          // 0x00
    void (*enterFloor)(unsigned int groupID, FloorEnterMode mode);     // 0x04 (light: initialize)
    void (*update)(unsigned int groupID, FloorEnterMode mode);         // 0x08
    u32 unkC;                                                          // 0x0C
    void (*exitFloor)(unsigned int groupID, FloorEnterMode mode);      // 0x10 (light: finalize)
    u32 unk14;                                                         // 0x14
    const char* (*getModuleName)(void);                                // 0x18
    void (*makeStateData)(FloorStateMode mode, void* data, unsigned long size);    // 0x1C
    void (*restoreStateData)(FloorStateMode mode, void* data, unsigned long size); // 0x20
    u32 (*getStateSize)(FloorStateMode mode);                          // 0x24
    u32 (*getUID)(void);                                               // 0x28 magic number
};

#endif
