#ifndef GAME_FLOORDATA_H
#define GAME_FLOORDATA_H

#include <dolphin/types.h>
#include <game/bitfield.h>

struct FloorGfxHolder;
struct FloorCharHolder;
struct FloorPosHolder;
struct FloorFieldCameraHolder;
struct OffscreenHeader;

struct FloorData {
    u8 area;
    u8 kind;
    u16 floorID;
    u32 mapResID;
    FloorGfxHolder* gfx;
    FloorCharHolder* chars;
    FloorPosHolder* positions;
    FloorFieldCameraHolder* fieldCamera;
    u32 placeName;
    u32 preFunc;
    u32 mainFunc;
    u32 postFunc;
    OffscreenHeader** offscreen;
    u32 groupID[5];
};

struct FloorTresure {
    GC_BITS3(u8 kind : 3, u8 type : 3, u8 unk0_6 : 2)
    u8 count;
    s16 angle;
    u16 floorID;
    u16 eventFlag;
    u16 flagB;
    u8 unkA[2];
    u32 item;
    f32 x;
    f32 y;
    f32 z;
};

struct FloorDoor {
    s8 openAnim;
    s8 closeAnim;
    s8 openEndAnim;
    s8 closeEndAnim;
    u8 pad4;
    s8 altAnimA;
    s8 altAnimB;
    u8 doorType;
    u8 partIndex;
    u8 pad9;
    s16 collisionId;
    u16 floorID;
    u16 openFlag;
    u16 closeFlag;
    u8 pad12[2];
    u32 resourceId;
};

#endif
