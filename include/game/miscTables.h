#ifndef GAME_MISCTABLES_H
#define GAME_MISCTABLES_H

#include <dolphin/types.h>

struct UnderTakerPlace {
    u16 weight;
    u16 id;
    u32 msgID;
};
struct UnderTakerData {
    u16 threshold;
    u16 lowChance;
    u16 midChance;
    u16 randMod;
    u16 maxCount;
    u16 limit;
    u32 flagStart;
    u32 flagCounter;
    u32 flagLevel;
    u32 flagID;
    u32 flagAway;
    u32 flagDisable;
    u32 unk24;
    u32 etcLow;
    u32 etcHigh;
    u32 flagSide;
    UnderTakerPlace places[7];
};

struct ReliveHallData {
    u8 alpha;
    u8 unk1;
    u16 steps;
    u16 scale;
};

struct CharName {
    u16 hearFlag;
    u8 unk2[2];
    u32 nameID;
};

struct FloorEventEntry {
    u8 type;
    u8 pad1;
    u16 floorID;
    u32 arg;
    u32 script;
    u32 args[4];
};

struct MsgSE {
    u16 a;
    u16 b;
};

struct PokemonMenuAnim {
    u8 id;
    u8 pad;
    u16 index;
};

struct RibbonData {
    u32 unk0;
    u32 msgID;
};

struct floorsound_dd_ {
    u8 kind;
    u8 volume;
    u16 floorId;
    u16 sndId;
    u16 time;
    u16 envFade;
    u16 flagId;
};

#endif
