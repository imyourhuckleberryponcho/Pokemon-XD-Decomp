#ifndef GAME_SYSVARS_H
#define GAME_SYSVARS_H

#include <dolphin/types.h>

struct SystemVars {
    s32 debugSysvars;
    s32 gsMemSize;
    s32 perfbar;
    s32 errorTrap;
    s32 dispMemSize;
    s32 btldbgMenuFlag;
    s32 btldbgDeckGrp;
    s32 btldbgEncountId;
    s32 btldbgStoryEncountId;
    s32 btldbgHundredEncountId;
    s32 btldbgImasuguEncountId;
    s32 btldbgVirtualEncountId;
    s32 btldbgBingoEncountId;
    s32 btldbgColosseumEncountId;
    s32 btldbgItemSet1;
    s32 btldbgAutoEncount;
    s32 flddbgPokedoru;
    s32 flddbgPokecoupon;
    char localIp[16];
    char gamecubeIp[16];
    s32 serverPort;
    s32 outputPort;
    char netmask[16];
    char gateway[16];
    s32 heroColiDisableBut;
};

#endif
