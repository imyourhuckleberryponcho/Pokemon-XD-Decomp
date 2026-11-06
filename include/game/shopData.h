#ifndef GAME_SHOPDATA_H
#define GAME_SHOPDATA_H

#include <dolphin/types.h>

struct SHOP_DATA {
    u8 unk0;
    u8 mode;
    u16 goodsIdx;
};

struct SHOP_EXCHANGER {
    u8 se;
    u8 pad[3];
    u32 msg[18];
};

struct SHOP_SALESMAN {
    u8 se;
    u8 pad[3];
    u32 msg[14];
};

#endif
