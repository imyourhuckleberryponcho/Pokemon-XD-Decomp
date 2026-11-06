#ifndef GAME_FLAGDATA_H
#define GAME_FLAGDATA_H

#include <dolphin/types.h>
#include <game/bitfield.h>

struct FlagData {
    GC_BITS2(u8 level : 2, u8 length : 6)
    u8 unk1;
    u16 pos;
    s16 next;
};

struct FlagLevel {
    u32 numWords;
    u32* bits;
};

struct FlagEtc {
    u8 type;
    u8 unk1;
    u16 floor;
    u16 pokedoru;
    u8 unk6[2];
    u32 flagValue;
    u32 script;
    f32 x;
    f32 y;
    f32 z;
    u32 msg;
};

#endif
