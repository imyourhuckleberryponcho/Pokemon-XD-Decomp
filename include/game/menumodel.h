#ifndef GAME_MENUMODEL_H
#define GAME_MENUMODEL_H
#include <dolphin/types.h>
#include <game/gcptr.h>

struct GSlight;

#ifdef MENU_MODEL_FULL_LOAD
struct MENU_MODEL_LOAD {
    u8 kind;
    union {
        u32 id;
        struct {
            u16 form;
            u16 waza;
        } pk;
    };
    s32 rnd;
    u16 c;
    u8 shadow;
    u8 anim;
};
#define MENU_MODEL_LOAD_T MENU_MODEL_LOAD
#else
struct MENU_MODEL_LOAD_RAW {
    u8 kind;
    u8 pad1[3];
    u16 form;
    u16 waza;
    s32 rnd;
    u16 c;
    u8 shadow;
    u8 anim;
};
#define MENU_MODEL_LOAD_T MENU_MODEL_LOAD_RAW
#endif
#ifndef __MWERKS__
static_assert(sizeof(MENU_MODEL_LOAD_T) == 0x10 && alignof(MENU_MODEL_LOAD_T) == 4, "MENU_MODEL_LOAD layout");
#endif

struct MENU_MODEL {
#ifndef MENU_MODEL_NO_CTOR
    MENU_MODEL() {}
#endif
    u8 state;
    u8 loading;
    u8 inited;
    u8 visible;
    u8 clip;
    u8 pad5[7];
    f32 progress;
    MENU_MODEL_LOAD_T pending;
    MENU_MODEL_LOAD_T cur;
    GCuptr model;
    GCuptr wazaSeq;
    GCuptr nextModel;
    GCuptr nextWaza;
    f32 angle[3];
    f32 offset[3];
    void* thread;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    GCuptr camera;
    GSlight* light[3];
    f32 zoom;
    s32 waitCount;
    u8 f84;
    u8 pad85[3];
    f32 camRot[3];
    u8 mtx[0x30];
    u8 sizeValid;
    u8 pad[3];
    f32 size[3];
    f32 min[3];
    f32 max[3];
};

#endif
