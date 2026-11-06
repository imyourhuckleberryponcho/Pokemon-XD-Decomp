#ifndef GAME_BINGODATA_H
#define GAME_BINGODATA_H

#include <dolphin/types.h>

struct BINGO_PANEL_dd_ {
    u8 type;
    u8 tokusei;
    u8 seikaku;
    u8 sex;
    u16 no;
    u16 waza;
    u16 hosei;
};

struct BINGO_GRID_dd_ {
    u8 grid;
    u8 pos;
};

struct BINGO_DATA_dd_ {
    u8 no;
    u8 unk1[2];
    u8 level;
    u8 unk4;
    u8 ball;
    u8 unk6[0x10 - 6];
    u16 score[10];
    BINGO_PANEL_dd_ panel[14];
    BINGO_GRID_dd_ grid[3];
    u8 unkB6[2];
};

#endif
