#ifndef GAME_SNDSTREAM_H
#define GAME_SNDSTREAM_H

#include <dolphin/types.h>

struct SndStreamCh {
    u8 adpcm[0x2E];
    u8 busy[2];
    u32 filled[2];
    u32 x38;
    s32 state;
};
struct SndStream {
    SndStream* master;
    SndStream* child;
    s32 state;
    s32 stid;
    u8* buf;
    u32 bufSize;
    u32 x18;
    u32 pos;
    u32 played;
    u32 dataOfs;
    u32 gid;
    u32 fid;
    u32 sndId;
    u16 fadeTime;
    u8 unk36;
    u8 vol;
    u8 targetVol;
    u8 fadeFrame;
    u8 startVol;
    u8 right;
    u8 done;
    u8 mute;
    u8 pause;
    u8 half;
    u8 unk40[8];
    s32 frq;
    u32 dataSize;
    u32 cacheEnd;
    u8 unk54[8];
    s32 loop;
    u32 headerOfs;
    u8 unk64[0xD];
    u8 looped;
    u8 updated[2];
    u32 loopStart;
    u32 loopEnd;
    u32 endPos;
    SndStreamCh ch[2];
};

#endif
