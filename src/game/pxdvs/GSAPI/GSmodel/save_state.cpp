#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gsmodelview.h>

#pragma pool_strings off

struct Vec {
    f32 x, y, z;
};

#ifdef __MWERKS__
struct HSD_JObj {
    u8 unk0[0x1C];
    Vec rotate;
    f32 rotateW;
    Vec scale;
    Vec translate;
};
#else
struct HSD_JObj {
    void* pcObject[2];
    HSD_JObj* next;
    HSD_JObj* parent;
    HSD_JObj* child;
    u32 flags;
    void* dobj;
    Vec rotate;
    f32 rotateW;
    Vec scale;
    Vec translate;
    f32 mtx[3][4];
    void* scl;
    void* envelopemtx;
    void* aobj;
    void* robj;
    u32 id;
};
#endif

struct GSmodelNull {
    u8 unk0[0x10];
    HSD_JObj* jobj;
};

struct _GSmodel {
    u32 flags;
    _GSmodel* next;
    void* set;
    GSmodelNull* null;
    void* blendJObj;
    void* blendDest;
    f32 position[3];
    f32 rotation[3];
    f32 scale[3];
    GSmodelBoundView bound;
    void* camera;
    u16 flags2;
    u16 token;
    u8 layers[8];
    u32 animCount;
    u32 texAnimCount;
    s32 animType;
    s32 animIndex;
    f32 animRate;
    f32 animFrame;
    f32 animReqFrame;
    f32 animEndFrame;
    void* animAObj;
    s32 blendAnimType;
    u32 blendAnimIndex;
    f32 blendAnimRate;
    f32 blendAnimFrame;
    f32 blendAnimReqFrame;
    f32 blendAnimEndFrame;
    void* blendAnimAObj;
    s32 texAnimType;
    s32 texAnimIndex;
    f32 texAnimRate;
    f32 texAnimFrame;
    f32 texAnimReqFrame;
    f32 texAnimEndFrame;
    void* texAnimAObj;
    GSmodelPartMixView partMix[12];
    f32 blendFactor;
    u8 animDirty;
    u8 texAnimDirty;
    u8 unk21E[2];
    void* animEndedCallback;
    void* animEndedCallbackArg;
    GSmodelPartAnimView partAnim[16];
    s32 attachMode;
    _GSmodel* attachModel;
    u32 attachIndex;
    f32 attachPosition[3];
    f32 attachRotation[3];
    f32 attachScale[3];
    void* particleBank;
    u32 particleAttachMode;
    void* materials;
    u32 materialCount;
    u32 shadowSurfaceCount;
    void* shadowSurfaces;
    void* shadowLight;
    f32 groundPlane;
    GCuptr unk5F8;
    f32 unk5FC;
    u8 unk600[4];
    f32 unk604;
    u8 unk608[4];
    f32 unk60C;
    u16 unk610;
    u8 unk612;
    u8 unk613;
    GCuptr unk614;
    GCuptr unk618;
    GCuptr unk61C;
    s32 vertexCount;
    s32 polygonCount;
};

struct GSmodelState {
    u32 flags;
    Vec position;
    Vec rotation;
    Vec scale;
    s32 animIndex;
    s32 texAnimIndex;
    f32 animFrame;
    f32 animRate;
    f32 texAnimFrame;
    f32 texAnimRate;
    s32 animType;
    s32 texAnimType;
    Vec nullTranslate;
    Vec nullRotate;
    Vec nullScale;
};

#define GS_MODEL_STATE_FLAGS 0x322962

void modelApplyAnimation(_GSmodel* model);

extern "C" {
void __assert(const char* file, s32 line, const char* expr);
void GSmodelSetPosition(_GSmodel* model, Vec* pos);
void GSmodelSetRotation(_GSmodel* model, Vec* rot);
void GSmodelSetScale(_GSmodel* model, Vec* scale);
void GSmodelAddNull(_GSmodel* model, Vec* translate, Vec* rotate, Vec* scale);
void GSmodelSetAnimIndex(_GSmodel* model, s32 index);
void GSmodelSetAnimFrame(_GSmodel* model, f32 frame);
void GSmodelSetAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetAnimType(_GSmodel* model, s32 type);
void GSmodelSetTexAnimIndex(_GSmodel* model, s32 index);
void GSmodelSetTexAnimFrame(_GSmodel* model, f32 frame);
void GSmodelSetTexAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetTexAnimType(_GSmodel* model, s32 type);
void GSmodelStartAnimation(_GSmodel* model);
void GSmodelStartTexAnimation(_GSmodel* model);
Vec* GSmodelGetPositionPtr(_GSmodel* model);
Vec* GSmodelGetRotationPtr(_GSmodel* model);
Vec* GSmodelGetScalePtr(_GSmodel* model);
f32 GSmodelGetAnimRate(_GSmodel* model);
f32 fn_800F2298(_GSmodel* model);
}


static inline f32 HSD_JObjGetRotationX(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 748, "jobj");
    }
    return jobj->rotate.x;
}

static inline f32 HSD_JObjGetRotationY(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 762, "jobj");
    }
    return jobj->rotate.y;
}

static inline f32 HSD_JObjGetRotationZ(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 776, "jobj");
    }
    return jobj->rotate.z;
}

static inline void HSD_JObjGetScale(HSD_JObj* jobj, Vec* scale) {
    if (!jobj) {
        __assert("jobj.h", 849, "jobj");
    }
    if (!scale) {
        __assert("jobj.h", 850, "scale");
    }
    scale->x = jobj->scale.x;
    scale->y = jobj->scale.y;
    scale->z = jobj->scale.z;
}

static inline void HSD_JObjGetTranslation(HSD_JObj* jobj, Vec* translate) {
    if (!jobj) {
        __assert("jobj.h", 996, "jobj");
    }
    if (!translate) {
        __assert("jobj.h", 997, "translate");
    }
    translate->x = jobj->translate.x;
    translate->y = jobj->translate.y;
    translate->z = jobj->translate.z;
}

extern "C" {

void GSmodelPopState(_GSmodel* model, GSmodelState* state) {
    model->flags &= ~GS_MODEL_STATE_FLAGS;
    model->flags |= state->flags;
    GSmodelSetPosition(model, &state->position);
    GSmodelSetRotation(model, &state->rotation);
    GSmodelSetScale(model, &state->scale);
    if (state->flags & 0x20000) {
        model->flags ^= 0x20000;
        GSmodelAddNull(model, &state->nullTranslate, &state->nullRotate, &state->nullScale);
    }
    model->animIndex = -1;
    model->texAnimIndex = -1;
    GSmodelSetAnimIndex(model, state->animIndex);
    GSmodelSetAnimFrame(model, state->animFrame);
    GSmodelSetAnimRate(model, state->animRate);
    GSmodelSetAnimType(model, state->animType);
    GSmodelSetTexAnimIndex(model, state->texAnimIndex);
    GSmodelSetTexAnimFrame(model, state->texAnimFrame);
    GSmodelSetTexAnimRate(model, state->texAnimRate);
    GSmodelSetTexAnimType(model, state->texAnimType);
    if (state->flags & 0x20) {
        GSmodelStartAnimation(model);
    }
    if (state->flags & 0x40) {
        GSmodelStartTexAnimation(model);
    }
    modelApplyAnimation(model);
}

void GSmodelPushState(_GSmodel* model, GSmodelState* state) {
    Vec* v;

    state->flags = model->flags & GS_MODEL_STATE_FLAGS;
    v = GSmodelGetPositionPtr(model);
    state->position.x = v->x;
    state->position.y = v->y;
    state->position.z = v->z;
    v = GSmodelGetRotationPtr(model);
    state->rotation.x = v->x;
    state->rotation.y = v->y;
    state->rotation.z = v->z;
    v = GSmodelGetScalePtr(model);
    state->scale.x = v->x;
    state->scale.y = v->y;
    state->scale.z = v->z;
    state->animIndex = model->animIndex;
    state->texAnimIndex = model->texAnimIndex;
    state->animFrame = model->animFrame;
    state->animRate = GSmodelGetAnimRate(model);
    state->animType = model->animType;
    state->texAnimFrame = model->texAnimFrame;
    state->texAnimRate = fn_800F2298(model);
    state->texAnimType = model->texAnimType;
    if (state->flags & 0x20000) {
        HSD_JObj* jobj = model->null->jobj;
        HSD_JObjGetTranslation(jobj, &state->nullTranslate);
        state->nullRotate.x = HSD_JObjGetRotationX(jobj);
        state->nullRotate.y = HSD_JObjGetRotationY(jobj);
        state->nullRotate.z = HSD_JObjGetRotationZ(jobj);
        HSD_JObjGetScale(jobj, &state->nullScale);
    }
}

}
