#ifndef GAME_ITEMDATA_H
#define GAME_ITEMDATA_H

#include <dolphin/types.h>

typedef struct ItemDataBiosRef {
    u8 kind;
    u8 important;
    u8 useful;
    u8 field_03;
    u8 itemEffectParam;
    u8 padding_05;
    u16 price;
    u16 coupon;
    u16 itemSoubiDataId;
    u16 fightUseKoukaDataId;
    u16 padding_0E;
    u32 name;
    u32 doc;
    u32 buff;
    u32 fieldUseFunc;
    u32 battleUseFunc;
    s8 useFriend[3];
    u8 padding_27;
} ItemDataBiosRef;

#endif
