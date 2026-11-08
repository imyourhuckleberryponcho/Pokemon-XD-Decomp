#ifndef GAME_MENUCB_BATTLESTARTWORK_H
#define GAME_MENUCB_BATTLESTARTWORK_H
#include <dolphin/types.h>

struct MenuCBBattleStartTrainerTexture {
    void* texture;
    u32 resource;
};

struct MenuCBBattleStartWork {
    u32 unk0;
    s32 status;
    u8 unk8[4];
    MenuCBBattleStartTrainerTexture entries[4];
    s32 current;
    s32 count;
    s8 loading;
    u8 unk35[0x148 - 0x35];
};
#ifdef __MWERKS__
typedef char MenuCBBattleStartWorkSize[sizeof(MenuCBBattleStartWork) == 0x148 ? 1 : -1];
#endif

#endif
