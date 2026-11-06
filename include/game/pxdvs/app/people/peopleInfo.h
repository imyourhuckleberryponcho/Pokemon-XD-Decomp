#ifndef GAME_PEOPLEINFO_H
#define GAME_PEOPLEINFO_H

#include <dolphin/types.h>
#include <game/bitfield.h>

struct PeopleInfo {
    GC_BITS5(u8 talkSe : 3, u8 boundCheck : 1, u8 colType : 2, u8 noWalkStart : 1, u8 unk0_7 : 1)
    u8 neckIndex;
    u8 chestIndex;
    u8 unk3;
    u32 modelResID;
    f32 walkLength;
    f32 runLength;
    f32 colBallSize;
    f32 neckLeftLimit;
    f32 neckRightLimit;
    f32 neckUpLimit;
    f32 neckDownLimit;
    f32 talkDistance;
    char speakParts[7];
    char blinkParts[4];
    u8 unk33;
};

#endif
