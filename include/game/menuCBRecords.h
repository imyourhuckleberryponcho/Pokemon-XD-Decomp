#ifndef GAME_MENUCBRECORDS_H
#define GAME_MENUCBRECORDS_H
#include <dolphin/types.h>

struct MenuCBTrainer {
    u16 dataId;
    u16 playerId;
    s32 homePlace;
    s32 order[6];
    s32 orderNum;
    s32 controllerId;
    s32 versusId;
    u8 entryHero[0x978];
    u8 hero[0x978];
    u16 rank;
    u8 unk131E[2];
};

#pragma pack(push, 1)
struct MenuCBRuleWords {
    s32 a;
    s32 b;
};
struct MenuCBRule {
    s16 level[3];
    s16 a6;
    s32 a8;
    u8 aC;
    u8 aD;
    u8 sbToSleep;
    u8 sbToIceed;
    u8 skillSwap;
    u8 prohibitionSuicide;
    u8 michidure;
    u8 sonicBoom;
    s16 battleTimeLimit;
    s16 commandTimeLimit;
    u8 a18;
    u8 deoxysCamouflage;
    s16 a1A;
    s16 a1C;
    u16 name[21];
    MenuCBRuleWords a48;
    u16 a50;
    u8 f[0x3C];
    u16 a8E;
};
#pragma pack(pop)

struct MenuCBErr {
    u8 a;
    u8 b;
    u8 pad[2];
};

#endif
