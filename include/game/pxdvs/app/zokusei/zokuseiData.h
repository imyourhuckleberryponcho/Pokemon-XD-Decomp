#ifndef GAME_ZOKUSEIDATA_H
#define GAME_ZOKUSEIDATA_H

#include <dolphin/types.h>

struct ZokuseiData {
    u8 wazaKind;
    u8 unk1;
    u16 spriteID;
    u16 smallSpriteID;
    u8 unk6[2];
    u32 name;
    u16 wazaJoutai[18];
};

#endif
