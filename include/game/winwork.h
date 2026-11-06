#ifndef GAME_WINWORK_H
#define GAME_WINWORK_H
#include <dolphin/types.h>
#include <game/gcptr.h>

struct WinSeqLayout {
    void* cmds;
    u8 rest[0x38];
};

struct SpriteWorkLayout {
    void* next;
    s8 kind;
    u8 flags;
    s16 id;
    u32 tex;
    WinSeqLayout seq;
    GCuptr callback;
    GCuptr msg;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    u32 tex2;
    s16 u;
    s16 v;
    s16 uw;
    s16 uh;
    u8 color[4];
    f32 sx;
    f32 sy;
    f32 rot;
    u8 b74;
    u8 b75;
    u8 b76;
    u8 pad77;
};

struct WinWorkLayout {
    u8 used;
    u8 state;
    s8 seqSet;
    u8 pad3;
    s32 menuID;
    u8 pad8;
    s8 priority;
    u8 closeFlag;
    u8 enablePort;
    void* parent;
    void* next;
    void* prev;
    u8 flag18;
    u8 itemNum;
    u8 flags1a;
    u8 closeFlags;
    s32 layerID;
    u8 flags20;
    u8 pad_21[3];
    void* itemSprites;
    void* cursorSprites;
    void* slot2C;
    u8 pad30[0x38];
    GCuptr params[8];
    u8 pad_88[4];
    s16 offX;
    s16 offY;
    s32 pad_90;
    f32 f94;
    f32 f98;
    s16 cursorX;
    s16 cursor;
    u8 pad_a0[4];
    u8 pad_a4;
    u8 pad_a5;
    u8 pad_a6[2];
    u8 freeWork[0x10];
    void* alloc;
};
#endif
