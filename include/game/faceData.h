#ifndef GAME_FACEDATA_H
#define GAME_FACEDATA_H

#include <dolphin/types.h>
#include <game/bitfield.h>

struct MenuFaceData {
    GC_BITS2(u8 rareFlag : 1, u8 unk0 : 7)
    u8 unk1[3];
    u32 texID;
};

struct ToolentryFaceData {
    u16 id;
    u8 unk2[2];
    u32 bigFace[2];
    u32 smallFace[2];
};

#endif
