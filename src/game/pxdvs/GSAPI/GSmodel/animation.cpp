// GSmodel skeletal/texture animation control.
#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
};

struct Quaternion {
    f32 x, y, z, w;
};

typedef f32 Mtx[3][4];

struct _HSD_AObj {
    u32 flags;
    f32 curr_frame;
    f32 rewind_frame;
    f32 end_frame;      // 0x0C
};
typedef _HSD_AObj HSD_AObj;

struct HSD_AObjDesc {
    u32 flags;
    f32 end_frame;      // 0x04
};

struct _HSD_AnimJoint {
    _HSD_AnimJoint* child;  // 0x00
    _HSD_AnimJoint* next;   // 0x04
    HSD_AObjDesc* aobjdesc; // 0x08
    void* robj;             // 0x0C
    u32 flags;              // 0x10
};
typedef _HSD_AnimJoint HSD_AnimJoint;

struct _HSD_MatAnimJoint {
    _HSD_MatAnimJoint* child;
    _HSD_MatAnimJoint* next;
};

struct _HSD_ShapeAnimJoint {
    _HSD_ShapeAnimJoint* child;
    _HSD_ShapeAnimJoint* next;
};

typedef struct _HSD_JObj HSD_JObj;

struct _HSD_JObj {
    u8 unk0[0x8];
    HSD_JObj* next;     // 0x08
    HSD_JObj* parent;   // 0x0C
    HSD_JObj* child;    // 0x10
    u32 flags;          // 0x14
    u8 unk18[0x4];
    GSvec rotate;       // 0x1C
    f32 rotateW;        // 0x28
    GSvec scale;        // 0x2C
    GSvec translate;    // 0x38
    Mtx mtx;            // 0x44
    u8 unk74[0x8];
    HSD_AObj* aobj;     // 0x7C
};

#define JOBJ_MTX_DIRTY (1 << 6)
#define JOBJ_INSTANCE (1 << 12)
#define JOBJ_USE_QUATERNION (1 << 17)
#define JOBJ_USER_DEF_MTX (1 << 23)
#define JOBJ_MTX_INDEP_SRT (1 << 25)

struct _HSD_Joint;

struct _HSD_SceneModelSet {
    _HSD_Joint* joint;
    HSD_AnimJoint** animjoint;
    _HSD_MatAnimJoint** matanim_joint;
    _HSD_ShapeAnimJoint** shapeanim_joint;
};

struct GSpart {
    u8 unk0[0x8];
    HSD_JObj* jobj;     // 0x08
};

struct GSmodelPartMix {
    s32 type;           // 0x00
    u32 index;          // 0x04
    u8 unk8[0x8];
    f32 frame;          // 0x10
    f32 endFrame;       // 0x14
    HSD_AObj* aobj;     // 0x18
};

struct GSmodelPartAnim {
    s32 type;           // 0x00
    s32 partIndex;      // 0x04
    f32 (*callback)(GSpart* part, s32 type, void* arg, GSvec* out); // 0x08
    void* arg;          // 0x0C
    u32 mixFlags;       // 0x10
    GSvec baseTranslate; // 0x14
    GSvec baseRotate;   // 0x20
    GSvec baseScale;    // 0x2C
};

struct _GSmodel {
    u32 flags;                // 0x000
    _GSmodel* next;           // 0x004
    _HSD_SceneModelSet* set;  // 0x008
    HSD_JObj* jobj;           // 0x00C
    HSD_JObj* blendJObj;      // 0x010
    HSD_JObj* blendDest;      // 0x014
    GSvec position;           // 0x018
    GSvec rotation;           // 0x024
    GSvec scale;              // 0x030
    u8 bound[0x20];           // 0x03C
    void* camera;             // 0x05C
    u16 flags2;               // 0x060
    u16 token;                // 0x062
    u8 layers[8];             // 0x064
    u32 animCount;            // 0x06C
    u32 texAnimCount;         // 0x070
    s32 animType;             // 0x074
    u32 animIndex;            // 0x078
    f32 animRate;             // 0x07C
    f32 animFrame;            // 0x080
    f32 animReqFrame;         // 0x084
    f32 animEndFrame;         // 0x088
    HSD_AObj* animAObj;       // 0x08C
    s32 blendAnimType;        // 0x090
    u32 blendAnimIndex;       // 0x094
    f32 blendAnimRate;        // 0x098
    f32 blendAnimFrame;       // 0x09C
    f32 blendAnimReqFrame;    // 0x0A0
    f32 blendAnimEndFrame;    // 0x0A4
    HSD_AObj* blendAnimAObj;  // 0x0A8
    s32 texAnimType;          // 0x0AC
    u32 texAnimIndex;         // 0x0B0
    f32 texAnimRate;          // 0x0B4
    f32 texAnimFrame;         // 0x0B8
    f32 texAnimReqFrame;      // 0x0BC
    f32 texAnimEndFrame;      // 0x0C0
    HSD_AObj* texAnimAObj;    // 0x0C4
    GSmodelPartMix partMix[12]; // 0x0C8
    f32 blendFactor;          // 0x218
    u8 unk21C;                // 0x21C
    u8 texAnimDirty;          // 0x21D
    u8 unk21E[2];
    void* animEndedCallback;  // 0x220
    void* animEndedCallbackArg; // 0x224
    GSmodelPartAnim partAnim[16]; // 0x228
    s32 attachMode;           // 0x5A8
    _GSmodel* attachModel;    // 0x5AC
    u32 attachIndex;          // 0x5B0
    GSvec attachPosition;     // 0x5B4
    GSvec attachRotation;     // 0x5C0
    GSvec attachScale;        // 0x5CC
};

#define MODEL_ROOT_NULL 0x20000
#define MODEL_FLAG(model, flag) (((model)->flags & (flag)) == (flag))

extern "C" {
void __assert(const char* file, s32 line, const char* expr);
extern _GSmodel* _modelTopPtr;

u32 GSgfxPerfbarCPUEntry(u32 id);
u8 GSgfxVideoGetVsyncRate(void);
void EulerToQuat(GSvec* euler, Quaternion* quat);
double fmod(double x, double y);
f32 GSgfxVideoGetLastRenderTime(void);
void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
HSD_JObj* GSpartGetJObjPtr(HSD_JObj* root, s32 index);
void GSvecTransformQuat(GSvec* out, Quaternion* quat, GSvec* in);
void GSpartGetTransform(GSpart* part, GSvec* position, GSvec* rotation, GSvec* scale);
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXTrans(Mtx m, f32 x, f32 y, f32 z);
void PSMTXCopy(const Mtx src, Mtx dst);
void GSmodelDetachFromGSpart(_GSmodel* model, u8 restore);
void GSpartAnimWalkTree(HSD_AnimJoint* joint, void (*callback)(HSD_AnimJoint*, void**, int), void** arg);
GSpart* GSmodelGetPart(_GSmodel* model, s32 index);
void GSpartSetTexAnimIndex(GSpart* part, u32 a, u32 b, u32 c, f32 d);
void GSpartFree(GSpart* part);
void GSpartSetAnimIndex(GSpart* part, u32 a, u32 b, f32 c);
void GSboundSetAnimIndex(void* bound, u32 index);
void GSboundSetAnimFrame(void* bound, f32 frame);
void GSmodelRemoveNull(_GSmodel* model);
void HSD_ForeachAnim(void* object, u32 type, u32 mask, void* func, u32 callback_type, ...);
void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, u32 flags, f32 frame);
void HSD_JObjAddAnimAll(HSD_JObj* jobj, HSD_AnimJoint* animjoint, _HSD_MatAnimJoint* matanim, _HSD_ShapeAnimJoint* shapeanim);
void HSD_JObjRemoveAnim(HSD_JObj* jobj);
void HSD_JObjAddAnim(HSD_JObj* jobj, HSD_AnimJoint* animjoint, _HSD_MatAnimJoint* matanim, _HSD_ShapeAnimJoint* shapeanim);
void HSD_JObjAnimAll(HSD_JObj* jobj);
void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj);
void HSD_JObjSetupMatrixSub(HSD_JObj* jobj);
u32 HSD_AObjGetFlags(HSD_AObj* aobj);
void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags);
void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags);

void GSmodelForceAnimTransformUpdate(_GSmodel* model);
void GSmodelSetAnimFrame(_GSmodel* model, f32 frame);
void _modelGetEndFrame(HSD_AObj* aobj, f32* endFrame);
}

void modelApplyAnimation(_GSmodel* model);
void modelUpdateAttachments(_GSmodel* model);
void modelUpdateTransform(_GSmodel* model);
void modelApplyPartAnimMixes(_GSmodel* model);
void modelCalculateBlendModel(_GSmodel* model, f32 rate);
void modelIntpJObjRotate(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, GSvec* mix, u32 mixFlags);
void modelIntpJObjScale(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, GSvec* mix, u32 mixFlags);
void modelIntpJObjTrans(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, GSvec* mix, u32 mixFlags);
static void _modelResetPartAnimMixes(_GSmodel* model);
void modelUpdateCenterNull(_GSmodel* model);
HSD_JObj* modelGetRenderJObj(_GSmodel* model);
void modelSetPos(_GSmodel* model, GSvec* v);
void modelSetRot(_GSmodel* model, GSvec* v);
void modelSetScl(_GSmodel* model, GSvec* v);
static void _modelRecalcMatrixAll(HSD_JObj* jobj);
static void _modelGetAObjFunc(HSD_AObj* aobj, void* arg);
static void _jobjAddAnimAll(HSD_JObj* jobj, HSD_AnimJoint* animjoint, _HSD_MatAnimJoint* matanim, _HSD_ShapeAnimJoint* shapeanim);
static void _modelSetLoopFlag(HSD_AObj* aobj, u32 loop);

// From MSL's math_api.h.
inline int __fpclassifyf(f32 x) {
    switch ((*(s32*)&x) & 0x7f800000) {
    case 0x7f800000: {
        if ((*(s32*)&x) & 0x007fffff)
            return 1;
        else
            return 2;
        break;
    }
    case 0: {
        if ((*(s32*)&x) & 0x007fffff)
            return 5;
        else
            return 3;
        break;
    }
    }
    return 4;
}

#define isnan(x) (__fpclassifyf(x) == 1)

// Inline helpers from HSD's jobj.h (asserts carry that header's line numbers).
extern "C" {

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj* jobj) {
    u8 result;
    if (!jobj) {
        __assert("jobj.h", 605, "jobj");
    }
    result = false;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY)) {
        result = true;
    }
    return result;
}

static inline void HSD_JObjSetupMatrix(HSD_JObj* jobj) {
    if (!jobj || !HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetupMatrixSub(jobj);
}

}

static inline void HSD_JObjSetMtxDirty(HSD_JObj* jobj) {
    if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetRotationX(HSD_JObj* jobj, f32 x) {
    if (!jobj) {
        __assert("jobj.h", 676, "jobj");
    }
    if (jobj->flags & JOBJ_USE_QUATERNION) {
        __assert("jobj.h", 677, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationY(HSD_JObj* jobj, f32 y) {
    if (!jobj) {
        __assert("jobj.h", 696, "jobj");
    }
    if (jobj->flags & JOBJ_USE_QUATERNION) {
        __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationZ(HSD_JObj* jobj, f32 z) {
    if (!jobj) {
        __assert("jobj.h", 716, "jobj");
    }
    if (jobj->flags & JOBJ_USE_QUATERNION) {
        __assert("jobj.h", 717, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScale(HSD_JObj* jobj, GSvec* scale) {
    if (!jobj) {
        __assert("jobj.h", 790, "jobj");
    }
    if (scale == 0) {
        __assert("jobj.h", 791, "scale");
    }
    jobj->scale.x = scale->x;
    jobj->scale.y = scale->y;
    jobj->scale.z = scale->z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslate(HSD_JObj* jobj, GSvec* translate) {
    if (!jobj) {
        __assert("jobj.h", 937, "jobj");
    }
    if (translate == 0) {
        __assert("jobj.h", 938, "translate");
    }
    jobj->translate.x = translate->x;
    jobj->translate.y = translate->y;
    jobj->translate.z = translate->z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotation(HSD_JObj* jobj, Quaternion* rotate) {
    if (!jobj) {
        __assert("jobj.h", 656, "jobj");
    }
    if (rotate == 0) {
        __assert("jobj.h", 657, "rotate");
    }
    jobj->rotate.x = rotate->x;
    jobj->rotate.y = rotate->y;
    jobj->rotate.z = rotate->z;
    jobj->rotateW = rotate->w;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline f32 HSD_JObjGetRotationX(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 748, "jobj");
    }
    return jobj->rotate.x;
}

static inline void HSD_JObjGetScale(HSD_JObj* jobj, GSvec* scale) {
    if (!jobj) {
        __assert("jobj.h", 849, "jobj");
    }
    if (scale == 0) {
        __assert("jobj.h", 850, "scale");
    }
    scale->x = jobj->scale.x;
    scale->y = jobj->scale.y;
    scale->z = jobj->scale.z;
}

static inline void HSD_JObjGetTranslate(HSD_JObj* jobj, GSvec* translate) {
    if (!jobj) {
        __assert("jobj.h", 996, "jobj");
    }
    if (translate == 0) {
        __assert("jobj.h", 997, "translate");
    }
    translate->x = jobj->translate.x;
    translate->y = jobj->translate.y;
    translate->z = jobj->translate.z;
}

static inline void HSD_JObjCopyMtx(HSD_JObj* jobj, Mtx mtx) {
    if (!jobj) {
        __assert("jobj.h", 1173, "jobj");
    }
    if (mtx == 0) {
        __assert("jobj.h", 1174, "mtx");
    }
    PSMTXCopy(mtx, jobj->mtx);
}

static inline void HSD_JObjGetRotation(HSD_JObj* jobj, Quaternion* rotate) {
    if (!jobj) {
        __assert("jobj.h", 733, "jobj");
    }
    if (rotate == 0) {
        __assert("jobj.h", 734, "rotate");
    }
    rotate->x = jobj->rotate.x;
    rotate->y = jobj->rotate.y;
    rotate->z = jobj->rotate.z;
    rotate->w = jobj->rotateW;
}

static inline void modelMixPartValue(GSvec* value, GSvec* mix, u32 flags) {
    switch ((u8)flags) {
    case 0:
        break;
    case 1:
        value->x = mix->x;
        break;
    case 2:
        value->x += mix->x;
        break;
    }
    switch (flags & 0xFF00) {
    case 0:
        break;
    case 0x100:
        value->y = mix->y;
        break;
    case 0x200:
        value->y += mix->y;
        break;
    }
    switch (flags & 0xFF0000) {
    case 0:
        break;
    case 0x10000:
        value->z = mix->z;
        break;
    case 0x20000:
        value->z += mix->z;
        break;
    }
}

static inline HSD_JObj* modelGetRootJObj(_GSmodel* model) {
    HSD_JObj* jobj = model->jobj;
    if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
        jobj = jobj->child;
    }
    return jobj;
}

// Part animations driven by the model pause while the main animation is retimed.
static inline void modelPausePartAnims(_GSmodel* model) {
    if (model->flags & 0x80000000) {
        for (int i = 0; i < 8; i++) {
            if (model->partMix[i].aobj != 0) {
                HSD_AObjSetFlags(model->partMix[i].aobj, 0x10000);
            }
        }
    }
}

static inline void modelResumePartAnims(_GSmodel* model) {
    if (model->flags & 0x80000000) {
        for (int i = 0; i < 8; i++) {
            if (model->partMix[i].aobj != 0) {
                HSD_AObjClearFlags(model->partMix[i].aobj, 0x10000);
            }
        }
    }
}

static inline u8 modelIsNullAnimation(_GSmodel* model, u32 index) {
    HSD_AnimJoint* joint;

    if (model == 0 || model->set == 0) {
        return 1;
    }
    if (index >= model->animCount) {
        return 1;
    }
    joint = model->set->animjoint[index];
    if (joint->child == 0 && joint->next == 0 && joint->aobjdesc == 0 && joint->robj == 0 && joint->flags == 0) {
        return 1;
    }
    return 0;
}

static inline HSD_AObj* modelGetFirstAObj(HSD_JObj* jobj, u32 mask) {
    HSD_AObj* aobj = 0;
    HSD_ForeachAnim(jobj, 6, mask, _modelGetAObjFunc, 2, &aobj);
    return aobj;
}

static inline void modelSetTexAnimType(_GSmodel* model, s32 type) {
    HSD_JObj* jobj = modelGetRootJObj(model);
    model->texAnimType = type;
    switch (model->texAnimType) {
    case 0:
        HSD_ForeachAnim(jobj, 6, 0x64DB, _modelSetLoopFlag, 3, 0);
        break;
    case 1:
        HSD_ForeachAnim(jobj, 6, 0x64DB, _modelSetLoopFlag, 3, 1);
        break;
    }
}

static inline void modelSetTexAnimFrame(_GSmodel* model, f32 frame) {
    HSD_JObj* jobj = model->jobj;
    if (model->flags & 8) {
        if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
            jobj = jobj->child;
        }
        model->texAnimFrame = frame;
        model->texAnimReqFrame = frame;
        HSD_JObjReqAnimAllByFlags(jobj, 0x634, model->texAnimReqFrame);
        model->flags &= ~0x8000;
    }
}

static inline void modelSetTexAnimRate(_GSmodel* model, f32 rate) {
    if (model->flags & 8) {
        model->texAnimRate = rate;
        if (GSgfxVideoGetVsyncRate() == 50) {
            model->texAnimRate *= 1.2f;
        }
    }
}

static inline void modelSetTexAnimIndex(_GSmodel* model, u32 index) {
    u32 flags = model->flags;
    HSD_JObj* jobj = model->jobj;

    if ((flags & 8) && index < model->texAnimCount) {
        if (index != model->texAnimIndex || model->texAnimDirty == 1) {
            if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
                jobj = jobj->child;
            }
            model->texAnimIndex = index;
            HSD_JObjAddAnimAll(jobj, 0, model->set->matanim_joint[model->texAnimIndex], 0);
            if ((model->flags & 0x20000000) && jobj->aobj != 0) {
                HSD_JObjRemoveAnim(jobj);
            }
            model->texAnimEndFrame = 0.0f;
            HSD_ForeachAnim(jobj, 6, 0x64DB, _modelGetEndFrame, 2, &model->texAnimEndFrame);
            model->texAnimAObj = modelGetFirstAObj(jobj, 0x480);
        }
        modelSetTexAnimFrame(model, 0.0f);
        modelSetTexAnimType(model, model->texAnimType);
        model->partMix[8].aobj = 0;
        model->partMix[9].aobj = 0;
        model->partMix[10].aobj = 0;
        model->partMix[11].aobj = 0;
        model->texAnimDirty = 0;
    }
}

static inline f32 modelGetAnimRate(_GSmodel* model) {
    f32 rate;
    if (model->flags & 0x80) {
        rate = model->blendAnimRate;
    } else {
        rate = model->animRate;
    }
    if (GSgfxVideoGetVsyncRate() == 50) {
        rate /= 1.2f;
    }
    return rate;
}

static inline void modelSetAnimRate(_GSmodel* model, f32 rate) {
    if (rate < 0.0f || isnan(rate)) {
        return;
    }
    if (model->flags & 4) {
        f32 r = rate;
        if (GSgfxVideoGetVsyncRate() == 50) {
            r *= 1.2f;
        }
        if (!(model->flags & 0x80)) {
            model->animRate = r;
        } else {
            f32 ratio = (1.0f + model->animEndFrame) / (1.0f + model->blendAnimEndFrame);
            model->blendAnimRate = r;
            model->animRate = r * ratio;
        }
    }
    if (model->flags & 0x2000) {
        modelSetTexAnimRate(model, rate);
    }
}

static inline void modelSetAnimType(_GSmodel* model, s32 type) {
    if (model->flags & 4) {
        HSD_JObj* jobj = model->jobj;
        HSD_JObj* blend = model->blendJObj;
        if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
            jobj = jobj->child;
        }
        model->animType = type;
        model->blendAnimType = type;
        modelPausePartAnims(model);
        switch (model->animType) {
        case 0:
            HSD_ForeachAnim(jobj, 6, 0x9B2F, _modelSetLoopFlag, 3, 0);
            if (model->flags & 0x80) {
                HSD_ForeachAnim(blend, 6, 0x9B2F, _modelSetLoopFlag, 3, 0);
            }
            break;
        case 1:
            HSD_ForeachAnim(jobj, 6, 0x9B2F, _modelSetLoopFlag, 3, 1);
            if (model->flags & 0x80) {
                HSD_ForeachAnim(blend, 6, 0x9B2F, _modelSetLoopFlag, 3, 1);
            }
            break;
        }
        modelResumePartAnims(model);
    }
    if (model->flags & 0x2000) {
        modelSetTexAnimType(model, type);
    }
}

struct GSmodelAnimEndInfo {
    u32 flags;
    u32 index;
    void* arg;
};

typedef void (*GSmodelAnimEndedCallback)(_GSmodel* model, GSmodelAnimEndInfo* info);

static inline void modelNotifyAnimEnded(_GSmodel* model, u32 kind, s32 type, u32 index, bool part) {
    bool loop = type == 1;
    if (model->animEndedCallback != 0) {
        GSmodelAnimEndInfo info;
        info.flags = 0;
        info.flags |= kind;
        if (loop == true) {
            info.flags |= 4;
        }
        if (part) {
            info.flags |= 8;
        }
        info.index = index;
        info.arg = model->animEndedCallbackArg;
        ((GSmodelAnimEndedCallback)model->animEndedCallback)(model, &info);
    }
}

static inline void modelCheckPartAnimEnded(_GSmodel* model, GSmodelPartMix* mix, u32 kind) {
    if (mix->aobj != 0 && mix->frame >= mix->endFrame - 0.0001f && !(model->flags2 & 0x10)) {
        if (mix->type == 0) {
            mix->aobj = 0;
        }
        modelNotifyAnimEnded(model, kind, mix->type, mix->index, true);
    }
}

static inline void modelAnimEnded(_GSmodel* model, s32 type, u32 stopFlag, u32 loopFlag, u32 kind, u32 index, bool part) {
    switch (type) {
    case 0:
        model->flags &= ~stopFlag;
        break;
    case 1:
        model->flags &= ~loopFlag;
        break;
    }
    modelNotifyAnimEnded(model, kind, type, index, part);
}

static inline void modelAdvanceFrame(_GSmodel* model, f32* frame, f32 step, s32* type, f32* end, u32 endFlag) {
    if (step != 0.0f) {
        *frame += step;
        switch (*type) {
        case 0:
            if (*frame >= *end) {
                *frame = *end;
                model->flags |= endFlag;
            }
            break;
        case 1:
            if (*frame >= *end - 0.001f) {
                *frame = *frame - *end;
                if (*frame < 0.0f) {
                    *frame = 0.0f;
                }
                model->flags |= endFlag;
            }
            break;
        }
    }
}

static void _modelGetAnimFrameCountCB(HSD_AnimJoint* joint, void** arg, int);

extern "C" {

void GSmodelRemoveRootJointAnimation(_GSmodel* model) {
    model->flags |= 0x20000000;
    model->flags &= ~0x400;
}

void GSmodelUseRootJointAnimation(_GSmodel* model, u8 use) {
    if (use) {
        model->flags |= 0x400;
        model->flags &= ~0x20000000;
    } else {
        model->flags &= ~0x400;
    }
}

u8 GSmodelIsNullAnimation(_GSmodel* model, u32 index) {
    return modelIsNullAnimation(model, index);
}

f32 GSmodelGetAnimFrameCount(_GSmodel* model, u32 index) {
    f32 count;

    if (!(model->flags & 4)) {
        return 0.0f;
    }
    count = 0.0f;
    GSpartAnimWalkTree(model->set->animjoint[index], _modelGetAnimFrameCountCB, (void**)&count);
    return 1.0f + count;
}

}

static void _modelGetAnimFrameCountCB(HSD_AnimJoint* joint, void** arg, int) {
    HSD_AObjDesc* desc;

    if (joint == 0 || (desc = joint->aobjdesc) == 0) {
        return;
    }
    if (desc->end_frame > *(f32*)arg) {
        *(f32*)arg = desc->end_frame;
    }
}

extern "C" {

// Never inlined into its callers in the original.
#pragma dont_inline on
void GSmodelForceAnimTransformUpdate(_GSmodel* model) {
    u32 perf;

    model->flags &= ~0x400200;
    perf = GSgfxPerfbarCPUEntry(0xFF0000);
    modelApplyAnimation(model);
    modelUpdateAttachments(model);
    modelUpdateTransform(model);
    modelApplyPartAnimMixes(model);
    GSgfxPerfbarCPUEntry(perf);
}

#pragma dont_inline reset

void GSmodelSetAnimEndedCallback(_GSmodel* model, void* callback, void* arg) {
    model->animEndedCallback = callback;
    model->animEndedCallbackArg = arg;
}

void GSmodelSetForceUseFractionalFramesFlag(_GSmodel* model, u8 enable) {
    if (enable == 1) {
        model->flags2 |= 2;
    } else {
        model->flags2 &= ~2;
    }
}

void GSmodelSetSkipFractionalFramesFlag(_GSmodel* model, u8 enable) {
    if (enable == 1) {
        model->flags2 |= 1;
    } else {
        model->flags2 &= ~1;
    }
}

void GSmodelSet60fpsAnimFlag(_GSmodel* model, u8 enable) {
    if (enable == 1) {
        model->flags |= 0x800;
    } else {
        model->flags &= ~0x800;
    }
}

void GSmodelLinkTexAnimToAnim(_GSmodel* model, u8 link) {
    if (link) {
        model->flags |= 0x2000;
    } else {
        model->flags &= ~0x2000;
    }
}

u32 GSmodelGetMaxTexAnimIndex(_GSmodel* model) {
    return model->texAnimCount;
}

u32 GSmodelGetMaxAnimIndex(_GSmodel* model) {
    return model->animCount;
}

u32 GSmodelCanShapeAnimate(_GSmodel* model) {
    return (model->flags >> 4) & 1;
}

u32 GSmodelCanTexAnimate(_GSmodel* model) {
    return (model->flags >> 3) & 1;
}

u32 GSmodelCanAnimate(_GSmodel* model) {
    return (model->flags >> 2) & 1;
}

u32 GSmodelHasTexAnimationEnded(_GSmodel* model) {
    return (model->flags >> 15) & 1;
}

void GSmodelStopTexAnimation(_GSmodel* model) {
    model->flags &= ~0x40;
}

void GSmodelStartTexAnimation(_GSmodel* model) {
    if (model->flags & 8) {
        model->flags |= 0x40;
        model->flags &= ~0x8000;
    }
}

void GSmodelSetTexAnimType(_GSmodel* model, s32 type) {
    modelSetTexAnimType(model, type);
}

void GSmodelSetTexAnimFrame(_GSmodel* model, f32 frame) {
    modelSetTexAnimFrame(model, frame);
}

f32 fn_800F2298(_GSmodel* model) {
    f32 rate;

    if (!(model->flags & 8)) {
        return 0.0f;
    }
    rate = model->texAnimRate;
    if (GSgfxVideoGetVsyncRate() == 50) {
        rate /= 1.2f;
    }
    return rate;
}

void GSmodelSetTexAnimRate(_GSmodel* model, f32 rate) {
    modelSetTexAnimRate(model, rate);
}

void GSmodelSetTexAnimIndex(_GSmodel* model, u32 index) {
    modelSetTexAnimIndex(model, index);
}

void GSmodelSetPartTexAnimIndex(_GSmodel* model, s32 partIndex, u32 a, u32 b, u32 c, f32 d) {
    GSpart* part = GSmodelGetPart(model, partIndex);
    if (part != 0) {
        GSpartSetTexAnimIndex(part, a, b, c, d);
        GSpartFree(part);
    }
}

void GSmodelGetFrameCount(_GSmodel* model, f32* count, f32* blendCount) {
    if (!(model->flags & 0x80)) {
        if (count != 0) {
            *count = 1.0f + model->animEndFrame;
        }
        if (blendCount != 0) {
            *blendCount = -1.0f;
        }
    } else {
        if (count != 0) {
            *count = 1.0f + model->animEndFrame;
        }
        if (blendCount != 0) {
            *blendCount = 1.0f + model->blendAnimEndFrame;
        }
    }
}

f32 GSmodelGetAnimFrame(_GSmodel* model) {
    if (!(model->flags & 4)) {
        return 0.0f;
    }
    if (model->flags & 0x80) {
        return model->blendAnimFrame;
    }
    return model->animFrame;
}

s32 GSmodelGetAnimType(_GSmodel* model) {
    return model->animType;
}

f32 GSmodelGetAnimRate(_GSmodel* model) {
    return modelGetAnimRate(model);
}

void GSmodelGetAnimIndex(_GSmodel* model, u32* index, u32* blendIndex) {
    if (!(model->flags & 0x80)) {
        if (index != 0) {
            *index = model->animIndex;
        }
        if (blendIndex != 0) {
            *blendIndex = -1;
        }
    } else {
        if (index != 0) {
            *index = model->animIndex;
        }
        if (blendIndex != 0) {
            *blendIndex = model->blendAnimIndex;
        }
    }
}

u32 GSmodelIsBlending(_GSmodel* model) {
    return (model->flags >> 7) & 1;
}

void GSmodelSetBlendFactor(_GSmodel* model, f32 factor) {
    if (!(model->flags & 4) || !(model->flags & 0x80)) {
        return;
    }
    if (factor < 0.0f) {
        factor = 0.0f;
    } else if (factor > 1.0f) {
        factor = 1.0f;
    }
    model->blendFactor = factor;
}

void GSmodelSetAnimBlend(_GSmodel* model, u32 index, u32 blendIndex) {
    if (model->flags & 4) {
        f32 rate;
        u8 isNull;
        u8 blendIsNull;
        GSvec v;

        if (index > model->animCount || blendIndex > model->animCount) {
            return;
        }
        if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
            GSmodelRemoveNull(model);
        }
        isNull = modelIsNullAnimation(model, index);
        blendIsNull = modelIsNullAnimation(model, blendIndex);
        if (isNull == 1 && blendIsNull == 1) {
            return;
        }
        rate = modelGetAnimRate(model);
        model->flags |= 0x80;
        model->animIndex = index;
        model->blendAnimIndex = blendIndex;
        model->blendFactor = 0.0f;
        HSD_JObjAddAnimAll(model->jobj, model->set->animjoint[model->animIndex], 0, 0);
        HSD_JObjAddAnimAll(model->blendJObj, model->set->animjoint[model->blendAnimIndex], 0, 0);
        HSD_JObjReqAnimAllByFlags(model->jobj, 0x1CB, 0.0f);
        HSD_JObjReqAnimAllByFlags(model->blendJObj, 0x1CB, 0.0f);
        HSD_JObjAnimAll(model->jobj);
        HSD_JObjAnimAll(model->blendJObj);
        model->animEndFrame = 0.0f;
        HSD_ForeachAnim(model->jobj, 6, 0x9B2F, _modelGetEndFrame, 2, &model->animEndFrame);
        model->blendAnimEndFrame = 0.0f;
        HSD_ForeachAnim(model->blendJObj, 6, 0x9B2F, _modelGetEndFrame, 2, &model->blendAnimEndFrame);
        model->animAObj = modelGetFirstAObj(model->jobj, 0x20);
        model->blendAnimAObj = modelGetFirstAObj(model->blendJObj, 0x20);
        modelSetAnimRate(model, rate);
        modelSetAnimType(model, model->animType);
        GSmodelSetAnimFrame(model, 0.0f);
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        HSD_JObjSetTranslate(model->jobj, &v);
        HSD_JObjSetRotationX(model->jobj, v.x);
        HSD_JObjSetRotationY(model->jobj, v.y);
        HSD_JObjSetRotationZ(model->jobj, v.z);
        v.x = 1.0f;
        v.y = 1.0f;
        v.z = 1.0f;
        HSD_JObjSetScale(model->jobj, &v);
    }
    if (model->flags & 0x2000) {
        modelSetTexAnimIndex(model, blendIndex);
    }
    GSmodelForceAnimTransformUpdate(model);
}

void GSmodelSetBlendAnimFrameForce(_GSmodel* model, f32 frame, f32 blendFrame) {
    model->animRate = 0.0f;
    model->blendAnimRate = 0.0f;
    model->animFrame = frame;
    model->blendAnimFrame = blendFrame;
    model->animReqFrame = model->animFrame;
    model->blendAnimReqFrame = model->blendAnimFrame;
}

void GSmodelAllUnpauseAnimation(void) {
    _GSmodel* model;
    for (model = _modelTopPtr; model != 0; model = model->next) {
        model->flags &= ~0x100;
    }
}

void GSmodelAllPauseAnimation(void) {
    _GSmodel* model;
    for (model = _modelTopPtr; model != 0; model = model->next) {
        model->flags |= 0x100;
    }
}

u32 GSmodelHasAnimationEnded(_GSmodel* model) {
    return (model->flags >> 14) & 1;
}

u32 GSmodelIsAnimating(_GSmodel* model) {
    return (model->flags >> 5) & 1;
}

void GSmodelStopAnimation(_GSmodel* model) {
    if (model->flags & 4) {
        model->flags &= ~0x20;
    }
    if (model->flags & 0x2000) {
        model->flags &= ~0x40;
    }
}

void GSmodelStartAnimation(_GSmodel* model) {
    if (model->flags & 4) {
        model->flags |= 0x20;
        model->flags &= ~0x4000;
    }
    if (model->flags & 0x2000) {
        if (model->flags & 8) {
            model->flags |= 0x40;
            model->flags &= ~0x8000;
        }
    }
}

void GSmodelSetAnimRate(_GSmodel* model, f32 rate) {
    modelSetAnimRate(model, rate);
}

#pragma auto_inline off
void GSmodelSetAnimFrame(_GSmodel* model, f32 frame) {
    if (!(frame < 0.0f) && !isnan(frame)) {
        if (model->flags & 4) {
            if (!(model->flags & 0x80)) {
                HSD_JObj* jobj = model->jobj;
                if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
                    jobj = jobj->child;
                }
                model->animFrame = frame;
                model->animReqFrame = model->animFrame;
                modelPausePartAnims(model);
                HSD_JObjReqAnimAllByFlags(jobj, 0x1CB, model->animReqFrame);
                HSD_JObjAnimAll(jobj);
                modelResumePartAnims(model);
            } else {
                f32 ratio = model->blendAnimRate != 0.0f ? model->animRate / model->blendAnimRate : 1.0f;
                model->animFrame = frame * ratio;
                model->animReqFrame = model->animFrame;
                model->blendAnimFrame = frame;
                model->blendAnimReqFrame = model->blendAnimFrame;
                HSD_JObjReqAnimAllByFlags(model->jobj, 0x1CB, model->animReqFrame);
                HSD_JObjReqAnimAllByFlags(model->blendJObj, 0x1CB, model->blendAnimReqFrame);
                HSD_JObjAnimAll(model->jobj);
                HSD_JObjAnimAll(model->blendJObj);
            }
        }
        if (model->flags & 0x2000) {
            modelSetTexAnimFrame(model, frame);
        }
        model->flags &= ~0x4000;
    }
}

#pragma auto_inline reset

void GSmodelSetAnimType(_GSmodel* model, s32 type) {
    if (model->flags & 4) {
        HSD_JObj* jobj = model->jobj;
        HSD_JObj* blend = model->blendJObj;
        if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
            jobj = jobj->child;
        }
        model->animType = type;
        model->blendAnimType = type;
        modelPausePartAnims(model);
        switch (model->animType) {
        case 0:
            HSD_ForeachAnim(jobj, 6, 0x9B2F, _modelSetLoopFlag, 3, 0);
            if (model->flags & 0x80) {
                HSD_ForeachAnim(blend, 6, 0x9B2F, _modelSetLoopFlag, 3, 0);
            }
            break;
        case 1:
            HSD_ForeachAnim(jobj, 6, 0x9B2F, _modelSetLoopFlag, 3, 1);
            if (model->flags & 0x80) {
                HSD_ForeachAnim(blend, 6, 0x9B2F, _modelSetLoopFlag, 3, 1);
            }
            break;
        }
        modelResumePartAnims(model);
    }
    if (model->flags & 0x2000) {
        modelSetTexAnimType(model, type);
    }
}

void GSmodelSetAnimIndex(_GSmodel* model, u32 index) {
    if (model->flags & 4) {
        f32 rate;

        if (index >= model->animCount) {
            return;
        }
        if (modelIsNullAnimation(model, index)) {
            return;
        }
        rate = modelGetAnimRate(model);
        if (index != model->animIndex || (model->flags & 0x80) || model->unk21C == 1) {
            HSD_JObj* jobj = model->jobj;
            _HSD_ShapeAnimJoint* shapeanim;

            if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
                jobj = jobj->child;
            }

            model->flags &= ~0x80;
            model->animIndex = index;
            if (model->flags & 0x10) {
                shapeanim = model->set->shapeanim_joint[model->animIndex];
            } else {
                shapeanim = 0;
            }
            modelPausePartAnims(model);
            _jobjAddAnimAll(jobj, model->set->animjoint[model->animIndex], 0, shapeanim);
            if ((model->flags & 0x20000000) && jobj->aobj != 0) {
                HSD_JObjRemoveAnim(jobj);
            }
            model->animEndFrame = 0.0f;
            HSD_ForeachAnim(jobj, 6, 0x9B2F, _modelGetEndFrame, 2, &model->animEndFrame);
            model->animAObj = modelGetFirstAObj(jobj, 0x20);
            modelResumePartAnims(model);
        }
        GSmodelSetAnimFrame(model, 0.0f);
        modelSetAnimType(model, model->animType);
        modelSetAnimRate(model, rate);
        if (!(model->flags & 0x80000000)) {
            for (int i = 0; i < 8; i++) {
                model->partMix[i].aobj = 0;
            }
        }
        GSboundSetAnimIndex(model->bound, index);
    }
    if (model->flags & 0x2000) {
        modelSetTexAnimIndex(model, index);
    }
    GSmodelForceAnimTransformUpdate(model);
}

void GSmodelSetDontResetPartAnimFlag(_GSmodel* model, u8 enable) {
    if (enable) {
        model->flags2 |= 0x10;
    } else {
        model->flags2 &= ~0x10;
    }
}

void GSmodelSetKeepPartAnimFlag(_GSmodel* model, u8 enable) {
    if (enable) {
        model->flags |= 0x80000000;
    } else {
        model->flags &= ~0x80000000;
    }
}

void GSmodelSetPartAnimIndex(_GSmodel* model, s32 partIndex, u32 a, u32 b, f32 c) {
    GSpart* part = GSmodelGetPart(model, partIndex);
    if (part != 0) {
        GSpartSetAnimIndex(part, a, b, c);
        GSpartFree(part);
    }
}

void GSmodelAdvanceAnimation(_GSmodel* model, f32 dt) {
    u32 index;
    s32 type;
    u32 stopFlag;
    u32 loopFlag;

    if (model->flags & 0x100) {
        return;
    }
    if (model->flags & 0x4000) {
        s32 animType;
        u32 animIndex;
        u32 animStopFlag;
        u32 animLoopFlag;

        if (!(model->flags & 0x80)) {
            animIndex = model->animIndex;
            animType = model->animType;
            animStopFlag = 0x20;
            animLoopFlag = 0x4000;
        } else {
            animIndex = model->blendAnimIndex;
            animType = model->blendAnimType;
            animStopFlag = 0x20;
            animLoopFlag = 0x4000;
        }
        modelAnimEnded(model, animType, animStopFlag, animLoopFlag, 1, animIndex, false);
    }
    if (model->flags & 0x8000) {
        if (!(model->flags & 0x80)) {
            index = model->texAnimIndex;
            type = model->texAnimType;
            stopFlag = 0x40;
            loopFlag = 0x8000;
        }
        modelAnimEnded(model, type, stopFlag, loopFlag, 2, index, false);
    }
    if (model->unk21C == 1) {
        for (int i = 0; i < 8; i++) {
            modelCheckPartAnimEnded(model, &model->partMix[i], 1);
        }
    }
    if (model->texAnimDirty == 1) {
        for (int i = 0; i < 4; i++) {
            modelCheckPartAnimEnded(model, &model->partMix[i + 8], 2);
        }
    }
    if (model->flags & 0x20) {
        modelAdvanceFrame(model, &model->animFrame, model->animRate * dt, &model->animType, &model->animEndFrame, 0x4000);
        GSboundSetAnimFrame(model->bound, model->animFrame);
        if (model->flags & 0x80) {
            modelAdvanceFrame(model, &model->blendAnimFrame, model->blendAnimRate * dt, &model->blendAnimType, &model->blendAnimEndFrame, 0x4000);
        }
    }
    if (model->flags & 0x40) {
        modelAdvanceFrame(model, &model->texAnimFrame, model->texAnimRate * dt, &model->texAnimType, &model->texAnimEndFrame, 0x8000);
    }
}

}

static inline void modelClampScale(f32* s) {
    if (*s < 0.00001f && *s > -0.00001f) {
        *s = *s < 0.0f ? -0.00001f : 0.00001f;
    }
}

void modelUpdateTransform(_GSmodel* model) {
    HSD_JObj* jobj;

    if (model->flags & 0x200) {
        return;
    }
    modelUpdateCenterNull(model);
    jobj = modelGetRenderJObj(model);
    modelClampScale(&model->scale.x);
    modelClampScale(&model->scale.y);
    modelClampScale(&model->scale.z);
    if (model->flags & 0x80) {
        Quaternion quat;
        EulerToQuat(&model->rotation, &quat);
        HSD_JObjSetTranslate(jobj, &model->position);
        HSD_JObjSetRotation(jobj, &quat);
        HSD_JObjSetScale(jobj, &model->scale);
        _modelRecalcMatrixAll(jobj);
    } else {
        if (model->flags & 0x400) {
            HSD_JObjGetTranslate(jobj, &model->position);
            model->rotation.x = HSD_JObjGetRotationX(jobj);
            model->rotation.y = HSD_JObjGetRotationX(jobj);
            model->rotation.z = HSD_JObjGetRotationX(jobj);
            HSD_JObjGetScale(jobj, &model->scale);
        } else {
            HSD_JObjSetTranslate(jobj, &model->position);
            HSD_JObjSetRotationX(jobj, model->rotation.x);
            HSD_JObjSetRotationY(jobj, model->rotation.y);
            HSD_JObjSetRotationZ(jobj, model->rotation.z);
            HSD_JObjSetScale(jobj, &model->scale);
        }
        if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
            HSD_JObjSetupMatrix(jobj->child);
        }
        HSD_JObjSetupMatrix(jobj);
    }
    model->flags |= 0x200;
}

void modelUpdateAttachments(_GSmodel* model) {
    Mtx mtx;
    Mtx tmp;
    GSvec pos;
    GSvec rot;
    GSvec scl;
    Quaternion quat;
    GSvec offset;
    GSpart* part;

    if (model->attachMode == 0 || (model->flags & 0x400000)) {
        return;
    }
    model->flags |= 0x800000;
    modelUpdateAttachments(model->attachModel);
    modelUpdateTransform(model->attachModel);
    part = GSmodelGetPart(model->attachModel, model->attachIndex);
    GSpartGetTransform(part, &pos, &rot, &scl);
    GSpartFree(part);
    EulerToQuat(&rot, &quat);
    GSvecTransformQuat(&offset, &quat, &model->attachPosition);
    PSVECAdd(&pos, &offset, &pos);
    PSVECAdd(&rot, &model->attachRotation, &rot);
    scl.x *= model->attachScale.x;
    scl.y *= model->attachScale.y;
    scl.z *= model->attachScale.z;
    modelSetPos(model, &model->attachPosition);
    modelSetRot(model, &model->attachRotation);
    modelSetScl(model, &model->attachScale);
    switch (model->attachMode) {
    case 0:
        break;
    case 1:
        modelSetPos(model, &pos);
        break;
    case 2:
        modelSetRot(model, &rot);
        break;
    case 3:
        modelSetScl(model, &scl);
        break;
    case 4:
        modelSetPos(model, &pos);
        modelSetRot(model, &rot);
        break;
    case 5:
        modelSetRot(model, &rot);
        modelSetScl(model, &scl);
        break;
    case 6:
        modelSetPos(model, &pos);
        modelSetScl(model, &scl);
        break;
    case 7:
        modelSetPos(model, &pos);
        modelSetRot(model, &rot);
        modelSetScl(model, &scl);
        break;
    case 8: {
        HSD_JObj* jobj;
        modelSetPos(model, &pos);
        modelSetRot(model, &rot);
        modelSetScl(model, &scl);
        PSMTXRotRad(mtx, 'Z', rot.z);
        PSMTXRotRad(tmp, 'Y', rot.y);
        PSMTXConcat(tmp, mtx, mtx);
        PSMTXRotRad(tmp, 'X', rot.x);
        PSMTXConcat(tmp, mtx, mtx);
        PSMTXTrans(tmp, pos.x, pos.y, pos.z);
        PSMTXConcat(tmp, mtx, mtx);
        jobj = model->jobj;
        HSD_JObjCopyMtx(jobj, mtx);
        jobj->flags |= 0x3800000;
        HSD_JObjSetMtxDirty(jobj);
        break;
    }
    }
    if (model->flags & 0x40000) {
        GSmodelDetachFromGSpart(model, 0);
    }
    model->flags |= 0x400000;
    model->flags &= ~0x800000;
}

static inline u8 modelRunsAt60fps(_GSmodel* model) {
    if (model->flags2 & 2) {
        return 0;
    }
    if (MODEL_FLAG(model, 0x800) || (model->attachMode != 0 && model->attachModel != 0)) {
        return 1;
    }
    return 0;
}

// Drives the AObjs so they land exactly on the frame computed by GSmodelAdvanceAnimation.
static inline void modelSyncAObjRate(_GSmodel* model, HSD_JObj** jobj, u32 mask, f32* framePtr, f32* reqFramePtr, f32* endPtr, s32* typePtr) {
    u8 is60fps = modelRunsAt60fps(model);
    f32 rate = 0.0f;
    f32 frame;
    f32 end;

    if ((model->flags2 & 1) == 1 && !is60fps) {
        frame = (s32)*framePtr;
    } else {
        frame = *framePtr;
    }
    end = *endPtr;
    if (end > 0.0f) {
        switch (*typePtr) {
        case 0:
            if (frame >= end) {
                frame = end;
            }
            break;
        case 1:
            if (frame >= end - 0.001f) {
                frame = fmod(frame, end);
            }
            break;
        }
    }
    if (frame != *reqFramePtr) {
        if (frame < *reqFramePtr) {
            if (*typePtr == 1) {
                rate = frame + (*endPtr - *reqFramePtr);
            } else {
                rate = 0.0f;
            }
        } else {
            rate = frame - *reqFramePtr;
        }
    }
    if (rate < 0.0f) {
        rate = 0.0f;
    }
    HSD_ForeachAnim(*jobj, 6, mask, HSD_AObjSetRate, 1, rate);
}

void modelApplyAnimation(_GSmodel* model) {
    if (!(model->flags & 0xC)) {
        return;
    }
    if (model->flags & 0x80) {
        if ((model->flags & 4) && model->animAObj != 0 && model->blendAnimAObj != 0) {
            modelSyncAObjRate(model, &model->jobj, 0x9B2F, &model->animFrame, &model->animReqFrame, &model->animEndFrame, &model->animType);
            modelSyncAObjRate(model, &model->blendJObj, 0x9B2F, &model->blendAnimFrame, &model->blendAnimReqFrame, &model->blendAnimEndFrame, &model->blendAnimType);
        }
        HSD_JObjAnimAll(model->jobj);
        HSD_JObjAnimAll(model->blendJObj);
        if ((model->flags & 4) && model->animAObj != 0 && model->blendAnimAObj != 0) {
            model->animReqFrame = model->animAObj->curr_frame;
            model->blendAnimReqFrame = model->blendAnimAObj->curr_frame;
            if (model->unk21C == 1) {
                for (int i = 0; i < 8; i++) {
                    if (model->partMix[i].aobj != 0) {
                        model->partMix[i].frame = model->partMix[i].aobj->curr_frame;
                    }
                }
            }
        }
        f32 rate = modelGetAnimRate(model) * GSgfxVideoGetLastRenderTime();
        rate *= 0.5f;
        modelCalculateBlendModel(model, rate);
    } else {
        HSD_JObj* jobj;

        _modelResetPartAnimMixes(model);
        jobj = model->jobj;
        if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
            jobj = jobj->child;
        }
        if ((model->flags & 4) && model->animAObj != 0) {
            modelSyncAObjRate(model, &jobj, 0x9B2F, &model->animFrame, &model->animReqFrame, &model->animEndFrame, &model->animType);
        }
        if ((model->flags & 8) && model->texAnimAObj != 0) {
            modelSyncAObjRate(model, &jobj, 0x64DB, &model->texAnimFrame, &model->texAnimReqFrame, &model->texAnimEndFrame, &model->texAnimType);
        }
        HSD_JObjAnimAll(jobj);
        if ((model->flags & 4) && model->animAObj != 0) {
            model->animReqFrame = model->animAObj->curr_frame;
            if (model->unk21C == 1) {
                for (int i = 0; i < 8; i++) {
                    if (model->partMix[i].aobj != 0) {
                        model->partMix[i].frame = model->partMix[i].aobj->curr_frame;
                    }
                }
            }
        }
        if ((model->flags & 8) && model->texAnimAObj != 0) {
            model->texAnimReqFrame = model->texAnimAObj->curr_frame;
            if (model->texAnimDirty == 1) {
                for (int i = 0; i < 4; i++) {
                    if (model->partMix[i + 8].aobj != 0) {
                        model->partMix[i + 8].frame = model->partMix[i + 8].aobj->curr_frame;
                    }
                }
            }
        }
    }
}

u8 modelProcessAt60fps(_GSmodel* model) {
    if (model->flags2 & 2) {
        return 0;
    }
    if (MODEL_FLAG(model, 0x800) || (model->attachMode != 0 && model->attachModel != 0)) {
        return 1;
    }
    return 0;
}

static void _jobjAddAnimAll(HSD_JObj* jobj, HSD_AnimJoint* animjoint, _HSD_MatAnimJoint* matanim, _HSD_ShapeAnimJoint* shapeanim) {
    if (jobj != 0) {
    if (jobj->aobj == 0 || !(HSD_AObjGetFlags(jobj->aobj) & 0x10000)) {
        HSD_JObjAddAnim(jobj, animjoint, matanim, shapeanim);
    }
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        HSD_AnimJoint* a = animjoint != 0 ? animjoint->child : 0;
        _HSD_MatAnimJoint* m = matanim != 0 ? matanim->child : 0;
        _HSD_ShapeAnimJoint* sh = shapeanim != 0 ? shapeanim->child : 0;
        for (; child != 0; child = child->next, a = a != 0 ? a->next : 0, m = m != 0 ? m->next : 0, sh = sh != 0 ? sh->next : 0) {
            _jobjAddAnimAll(child, a, m, sh);
        }
    }    }
}


static inline void modelGetPartAnimValue(_GSmodel* model, GSpart* part, GSmodelPartAnim* anim, GSvec* out) {
    GSpart* p = part;
    if (p == 0) {
        p = GSmodelGetPart(model, anim->partIndex);
        if (p == 0) {
            return;
        }
    }
    {
        f32 scale = anim->callback(p, anim->type, anim->arg, out);
        if (scale != 1.0f) {
            PSVECScale(out, out, scale);
        }
    }
    if (part == 0) {
        GSpartFree(p);
    }
}

void modelApplyPartAnimMixes(_GSmodel* model) {
    for (int i = 0; i < 16; i++) {
        GSmodelPartAnim* anim = &model->partAnim[i];
        GSpart* part;
        GSvec vec;
        GSvec value;
        Quaternion rotate;

        if (anim->type == 0) {
            continue;
        }
        part = GSmodelGetPart(model, anim->partIndex);
        if (part == 0) {
            continue;
        }
        modelGetPartAnimValue(model, part, anim, &value);
        if (!(model->flags & 0x80)) {
            switch (anim->type) {
            case 1:
                HSD_JObjGetTranslate(part->jobj, &vec);
                modelMixPartValue(&vec, &value, anim->mixFlags);
                HSD_JObjSetTranslate(part->jobj, &vec);
                break;
            case 2:
                HSD_JObjGetRotation(part->jobj, &rotate);
                modelMixPartValue((GSvec*)&rotate, &value, anim->mixFlags);
                HSD_JObjSetRotation(part->jobj, &rotate);
                break;
            case 3:
                HSD_JObjGetScale(part->jobj, &vec);
                modelMixPartValue(&vec, &value, anim->mixFlags);
                HSD_JObjSetScale(part->jobj, &vec);
                break;
            }
        } else {
            HSD_JObj* a = GSpartGetJObjPtr(model->jobj, anim->partIndex);
            HSD_JObj* b = GSpartGetJObjPtr(model->blendJObj, anim->partIndex);
            if (a != 0 && b != 0) {
                switch (anim->type) {
                case 1:
                    modelIntpJObjTrans(a, b, part->jobj, model->blendFactor, &value, anim->mixFlags);
                    break;
                case 2:
                    modelIntpJObjRotate(a, b, part->jobj, model->blendFactor, &value, anim->mixFlags);
                    break;
                case 3:
                    modelIntpJObjScale(a, b, part->jobj, model->blendFactor, &value, anim->mixFlags);
                    break;
                }
            }
        }
        GSpartFree(part);
    }
}

static void _modelResetPartAnimMixes(_GSmodel* model) {
    for (int i = 0; i < 16; i++) {
        GSmodelPartAnim* anim = &model->partAnim[i];
        GSpart* part;

        if (anim->type == 0) {
            continue;
        }
        part = GSmodelGetPart(model, anim->partIndex);
        if (part == 0) {
            continue;
        }
        switch (anim->type) {
        case 1:
            HSD_JObjSetTranslate(part->jobj, &anim->baseTranslate);
            break;
        case 2: {
            Quaternion rotate;
            f32 x;
            f32 y;
            f32 z;
            z = anim->baseRotate.z;
            y = anim->baseRotate.y;
            x = anim->baseRotate.x;
            rotate.x = x;
            rotate.y = y;
            rotate.z = z;
            rotate.w = 0.0f;
            HSD_JObjSetRotation(part->jobj, &rotate);
            break;
        }
        case 3:
            HSD_JObjSetScale(part->jobj, &anim->baseScale);
            break;
        }
        GSpartFree(part);
    }
}

void modelCalculatePartMix(GSvec* value, GSvec* mix, u32 flags) {
    switch ((u8)flags) {
    case 0:
        break;
    case 1:
        value->x = mix->x;
        break;
    case 2:
        value->x += mix->x;
        break;
    }
    switch (flags & 0xFF00) {
    case 0:
        break;
    case 0x100:
        value->y = mix->y;
        break;
    case 0x200:
        value->y += mix->y;
        break;
    }
    switch (flags & 0xFF0000) {
    case 0:
        break;
    case 0x10000:
        value->z = mix->z;
        break;
    case 0x20000:
        value->z += mix->z;
        break;
    }
}

static void _modelRecalcMatrixAll(HSD_JObj* jobj) {
    HSD_JObj* child;

    if (jobj == 0) {
        return;
    }
    HSD_JObjSetupMatrix(jobj);
    if (jobj->flags & JOBJ_INSTANCE) {
        return;
    }
    for (child = jobj->child; child != 0; child = child->next) {
        _modelRecalcMatrixAll(child);
    }
}

static void _modelGetAObjFunc(HSD_AObj* aobj, void* arg) {
    if (aobj == 0) {
        return;
    }
    if (*(HSD_AObj**)arg == 0) {
        *(HSD_AObj**)arg = aobj;
    }
}

static void _modelSetLoopFlag(HSD_AObj* aobj, u32 loop) {
    if (HSD_AObjGetFlags(aobj) & 0x10000) {
        return;
    }
    if (loop == 0) {
        HSD_AObjClearFlags(aobj, 0x20000000);
    } else {
        HSD_AObjSetFlags(aobj, 0x20000000);
    }
}

extern "C" void _modelGetEndFrame(HSD_AObj* aobj, f32* endFrame) {
    if (aobj == 0) {
        __assert("aobj.h", 172, "aobj");
    }
    if (aobj->end_frame > *endFrame) {
        *endFrame = aobj->end_frame;
    }
}
