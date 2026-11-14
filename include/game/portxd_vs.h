#ifndef GAME_PORTXD_VS_H
#define GAME_PORTXD_VS_H

#include <dolphin/types.h>

typedef struct PortXD_VsSetup {
    s32 encountId;
    u32 fightKind;
    u32 fightType;

    u32 floorId;
    u32 bgm;
    s32 state;
    s32 trainerCount;
    u16 dataId[4];
    s32 controller[4];
    const void* hero[4];
    s32 freeTitle;
} PortXD_VsSetup;

#ifdef __cplusplus
extern "C" {
#endif
s32 PortXD_StartVsBattle(const PortXD_VsSetup* setup);
#ifdef __cplusplus
}
#endif

#endif
