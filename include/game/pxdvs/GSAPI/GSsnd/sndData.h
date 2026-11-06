#ifndef GAME_SNDDATA_H
#define GAME_SNDDATA_H

#include <dolphin/types.h>
#include <game/bitfield.h>

struct SndWork;

struct SndData {
    GC_BITS2(u8 group : 4, u8 reverb : 4)
    u8 vol;
    GC_BITS7(u8 env : 1, u8 stream : 1, u8 se : 1, u8 f3 : 1, u8 open : 1, u8 paused : 1, u8 f6 : 2)
    u8 b3;
    u16 fxid;
    u16 file;
    SndWork* work;

};

struct SndFile {
    u32 a;
    u32 b;
    u32 c;
};

struct SndWaveData {
    u8 b0;
    u8 loaded;
    u16 gid;
    u32 pad[5];

};

struct SndRevData {
    f32 coloration;
    f32 mix;
    f32 time;
    f32 damping;
    f32 preDelay;
    f32 crosstalk;
};

#endif
