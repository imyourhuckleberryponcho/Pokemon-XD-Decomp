#ifndef GAME_GSMATERIALVIEW_H
#define GAME_GSMATERIALVIEW_H
#include <dolphin/types.h>
typedef struct GSmaterialLayout {
    u16 savedAlpha;
    u16 extensions;
    u32 savedFlags;
    void* mobj;
    u8 modulate[4];
    u8 channels[4];
    void* envTObj;
    void* envImage;
    void* envTexture;
    s32 envType;
    s32 envMode;
    f32 envBlend;
    void* savedImage;
    void* savedPE;
} GSmaterialLayout;
#ifdef __MWERKS__
#define GSMATERIAL_SIZE 0x34
#else
#define GSMATERIAL_SIZE sizeof(GSmaterialLayout)
#endif
#endif
