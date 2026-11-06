#ifndef GAME_WORLDMAPDATA_H
#define GAME_WORLDMAPDATA_H

#include <dolphin/types.h>

struct WorldMapData {
    s16 camera;
    u16 npc;
    u32 flag;
    u32 selectIndex;
    u32 model;
    u32 snap;
    u32 motion;
    u32 pad18;
    u32 floorID;
    u32 msgID;
};

struct WorldMapMsgData {
    s32 etc;
    s32 msg[18];
};

struct WorldMapCameraPos {
    f32 x, y, z;
};
struct WorldMapCameraData {
    WorldMapCameraPos pos;
    f32 a, b, c;
    f32 fov;
};

#endif
