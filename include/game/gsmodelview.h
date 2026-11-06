#ifndef GAME_GSMODELVIEW_H
#define GAME_GSMODELVIEW_H
#include <dolphin/types.h>

struct GSmodelBoundAnimView {
    s32 animIndex;
    f32 animFrame;
    void* anim;
    void* animTable;
};
union GSmodelBoundDataView {
    f32 box[6];
    GSmodelBoundAnimView anim;
};
struct GSmodelBoundView {
    u16 flags;
    u16 type;
    void* data;
    GSmodelBoundDataView u;
};

struct GSmodelPartMixView {
    s32 type;
    u32 index;
    u8 unk8[0x8];
    f32 frame;
    f32 endFrame;
    void* aobj;
};

struct GSmodelPartAnimView {
    s32 type;
    s32 partIndex;
    void* callback;
    void* arg;
    u32 mixFlags;
    f32 baseTranslate[3];
    f32 baseRotate[3];
    f32 baseScale[3];
};

#endif
