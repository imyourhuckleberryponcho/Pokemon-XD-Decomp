#ifndef GAME_SHARED_FLOOR_MODULE_H
#define GAME_SHARED_FLOOR_MODULE_H
#include <dolphin/types.h>

enum FloorEnterMode { FLOOR_ENTER_MODE_0, FLOOR_ENTER_MODE_1, FLOOR_ENTER_MODE_2, FLOOR_ENTER_MODE_3 };
enum FloorStateMode { FLOOR_STATE_MODE_0, FLOOR_STATE_MODE_1, FLOOR_STATE_MODE_2, FLOOR_STATE_MODE_3 };

struct FloorModuleInterface {
    void (*unk0)(unsigned int groupID, FloorEnterMode mode);
    void (*enterFloor)(unsigned int groupID, FloorEnterMode mode);
    void (*update)(unsigned int groupID, FloorEnterMode mode);
    void* unkC;
    void (*exitFloor)(unsigned int groupID, FloorEnterMode mode);
    void (*unk14)(unsigned int groupID, FloorEnterMode mode);
    const char* (*getModuleName)(void);
    void (*makeStateData)(FloorStateMode mode, void* data, u32 size);
    void (*restoreStateData)(FloorStateMode mode, void* data, u32 size);
    u32 (*getStateSize)(FloorStateMode mode);
    u32 (*getUID)(void);
};

#endif
