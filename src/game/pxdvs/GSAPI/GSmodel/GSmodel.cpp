// GSmodel core: model list, render module, transforms and loading.
#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
};

struct Quaternion {
    f32 x, y, z, w;
};

typedef f32 Mtx[3][4];

struct HSD_JObj {
    u8 unk0[0x14];
    u32 flags;        // 0x14
    u8 unk18[0x4];
    GSvec rotate;     // 0x1C
    f32 rotateW;      // 0x28
    GSvec scale;      // 0x2C
    GSvec translate;  // 0x38
    Mtx mtx;          // 0x44
};

struct _HSD_Joint {
    char* class_name;
    u32 flags;
    _HSD_Joint* child;
    _HSD_Joint* next;
    void* dobj;
    GSvec rotation;
    GSvec scale;
    GSvec position;
    void* envelopemtx;
    void* robj;
};

struct _HSD_SceneModelSet {
    _HSD_Joint* joint;
    void** animjoint;
    void** matanim_joint;
    void** shapeanim_joint;
};

struct GSboundAnimHeader;

struct GSbound {
    u8 unk0[0x10];
    GSboundAnimHeader* animHeader; // 0x10
    u8 unk14[0xC];
};

struct HSD_CObj;

struct GScamera {
    u8 unk0[0x8];
    HSD_CObj* cobj;   // 0x08
    u8 unkC[0x60];
    GSvec position;   // 0x6C
};

struct GSmaterial {
    u8 unk0[0x34];
};

struct GSpart {
    u8 unk0[2];
    u16 index;
    struct _GSmodel* model;
};

struct _GSmodel {
    u32 flags;                // 0x000
    _GSmodel* next;           // 0x004
    _HSD_SceneModelSet* set;  // 0x008
    HSD_JObj* jobj;           // 0x00C
    HSD_JObj* jobj10;         // 0x010
    HSD_JObj* jobj14;         // 0x014
    GSvec position;           // 0x018
    GSvec rotation;           // 0x024
    GSvec scale;              // 0x030
    GSbound bound;            // 0x03C
    GScamera* camera;         // 0x05C
    u16 flags2;               // 0x060
    u16 token;                // 0x062
    u8 layers[8];             // 0x064
    u32 animCount;            // 0x06C
    u32 texAnimCount;         // 0x070
    s32 animType;             // 0x074
    s32 animIndex;            // 0x078
    u8 unk7C[4];
    f32 animFrame;            // 0x080
    u8 unk84[0x2C];
    s32 texAnimIndex;         // 0x0B0
    u8 unkB4[0x14];
    struct {
        u8 unk0[0x18];
        u32 unk18;
    } mixA[12];               // 0x0C8
    u8 unk218[4];
    u8 unk21C;                // 0x21C
    u8 unk21D;                // 0x21D
    u8 unk21E[2];
    u32 unk220;               // 0x220
    u8 unk224[4];
    struct {
        u32 unk0;
        u8 unk4[0x34];
    } mixB[16];               // 0x228
    s32 attachMode;           // 0x5A8
    _GSmodel* attachModel;    // 0x5AC
    u32 attachIndex;          // 0x5B0
    GSvec attachPosition;     // 0x5B4
    GSvec attachRotation;     // 0x5C0
    GSvec attachScale;        // 0x5CC
    void* particleBank;       // 0x5D8
    u32 particleAttachMode;   // 0x5DC
    GSmaterial* materials;    // 0x5E0
    u32 materialCount;        // 0x5E4
    u32 unk5E8;               // 0x5E8
    u32 unk5EC;               // 0x5EC
    u32 unk5F0;               // 0x5F0
    f32 unk5F4;               // 0x5F4
    u32 unk5F8;               // 0x5F8
    f32 unk5FC;               // 0x5FC
    u8 unk600[4];             // 0x600
    f32 unk604;               // 0x604
    u8 unk608[4];             // 0x608
    f32 unk60C;               // 0x60C
    u16 unk610;               // 0x610
    u8 unk612;                // 0x612
    u8 unk613;                // 0x613
    u32 unk614;               // 0x614
    u32 unk618;               // 0x618
    u32 unk61C;               // 0x61C
    s32 vertexCount;          // 0x620
    s32 polygonCount;         // 0x624
};

static inline bool MODEL_FLAG(struct _GSmodel* model, u32 flag);

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_OPA,
    GS_GFX_LAYER_PASS_XLU
};

struct GSgfxLayerState {
    u32 dirty;        // 0x00
    u8 unk4[0xC];
    u32 dirty10;      // 0x10
    u8 unk14[0x50];
    u32 dirty64;      // 0x64
    u8 unk68[0x50];
};

class GSgfxLayer {
public:
    void FlushState();
    void InvalidateState();
    u16 tokenMark();

    inline void SetViewport(f32 x, f32 y, f32 w, f32 h) {
        m_viewportX = x;
        m_viewportY = y;
        m_viewportW = w;
        m_viewportH = h;
        m_state[0].dirty10 |= 0x10;
        m_state[0].dirty |= 0x2;
        m_state[1].dirty10 |= 0x10;
        m_state[1].dirty |= 0x2;
    }

    inline void SetZCompare(u8 enable) {
        m_zCompare = enable;
        m_state[0].dirty64 |= 0x40;
        m_state[1].dirty64 |= 0x40;
        if (enable) {
            m_state[0].dirty64 |= 0x200;
            m_state[1].dirty64 |= 0x200;
            if (m_zUpdate) {
                m_state[0].dirty64 |= 0x100;
                m_state[1].dirty64 |= 0x100;
            }
        }
        m_state[0].dirty |= 0x40;
        m_state[1].dirty |= 0x40;
    }

    u8 unk0[0x4];
    u32 m_flags;            // 0x04
    u8 unk8[0x20];
    s32 m_id;               // 0x28
    s32 m_mode;             // 0x2C
    u8 unk30[0xD40];
    u16 m_scissorX;         // 0xD70
    u16 m_scissorY;         // 0xD72
    u16 m_scissorW;         // 0xD74
    u16 m_scissorH;         // 0xD76
    f32 m_viewportX;        // 0xD78
    f32 m_viewportY;        // 0xD7C
    f32 m_viewportW;        // 0xD80
    f32 m_viewportH;        // 0xD84
    u8 unkD88[0x8];
    u32 m_unkD90;           // 0xD90
    u8 unkD94[0x912];
    u8 m_zUpdate;           // 0x16A6
    u8 m_zCompare;          // 0x16A7
    GSgfxLayerState m_state[2]; // 0x16A8
};

struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(GSgfxLayer* layer, GSgfxLayerPass pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 unk18;
};

void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);
void GSgfxRenderWaitForDrawComplete();

void modelShadowRenderDebug();
void modelDistortionRender();
void modelShadowRender(GSgfxLayer* layer);
void modelUpdateTransform(_GSmodel* model);
void modelShadowPrepare(_GSmodel* model, bool enable);
void modelShadowRenderMarukage(_GSmodel* model, GSgfxLayer* layer);
void GSboundDraw(GSbound* bound, GSgfxLayer* layer);
void modelApplyAnimation(_GSmodel* model);
void modelUpdateAttachments(_GSmodel* model);
void modelApplyPartAnimMixes(_GSmodel* model);
void modelShadowUpdate();
u8 modelProcessAt60fps(_GSmodel* model);
void modelDustUpdate(_GSmodel* model);
void modelShadowFreeModelList(_GSmodel* model);
void modelMaterialFree(GSmaterial* material);
void modelMaterialInit(GSmaterial* material);
void modelRemoveCenterNull(_GSmodel* model);
void modelBankReleaseModel(_GSmodel* model);
_GSmodel* modelBankGetFreeModel();
void modelBankInit();
void modelShadowInit();

extern "C" {
void __assert(const char* file, s32 line, const char* expr);
extern _GSmodel* _modelTopPtr;
extern s32 modelShadowLayerID;

u32 GSgfxPerfbarCPUEntry(u32 id);
void GSgfxVideoGetEFBSize(u16* width, u16* height);
void GSgfxTokenIfClearedReset(u16* token);
void GSgfxProjectSetupParameters(void);
void HSD_InitColorSwapTable(s32 id, s32 r, s32 g, s32 b, s32 a);
void HSD_ResetColorSwapTables(void);
void HSD_StateInvalidate(s32 state);
void HSD_JObjDispAll(HSD_JObj* jobj, Mtx* vmtx, u32 flags, u32 rendermode);
void HSD_JObjSetupMatrixSub(HSD_JObj* jobj);
void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj);
void HSD_JObjUnref(HSD_JObj* jobj);
HSD_JObj* HSD_JObjLoadJoint(_HSD_Joint* joint);
void HSD_JObjCountVertices(HSD_JObj* jobj, s32* vertices, s32* polygons);
void HSD_SetVertexBuffer(void* buffer, s32 count);
void HSD_SetNormalBuffer(void* buffer, s32 count);
void HSD_SetExpArgBuffer(void* buffer, s32 count);
void GScameraLoadActiveCameraMatrix(s32 layerID);
GScamera* GScameraGetActiveCamera(void);
void GScameraLoadProjection(GScamera* camera, GSgfxLayer* layer);
void GSlightSetupLights(HSD_CObj* cobj);
void GSboundGetWorldPosition(GSbound* bound, GSvec* pos);
s32 GSboundIsInViewFast(GSbound* bound);
u8 GSboundHasAnimData(GSbound* bound);
void GSboundCreate(GSbound* bound, GSboundAnimHeader* header);
void GSboundSetDataPtr(GSbound* bound, s32 type, void* data);
void GSboundFree(GSbound* bound);
f32 PSVECDistance(const GSvec* a, const GSvec* b);
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* ab);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
void PSMTXCopy(const Mtx src, Mtx dst);
void EulerToQuat(GSvec* euler, Quaternion* quat);
void GSvecTransformQuat(GSvec* out, Quaternion* quat, GSvec* in);
void GSpartGetTransform(GSpart* part, GSvec* position, GSvec* rotation, GSvec* scale);
GSpart* GSmodelGetPart(_GSmodel* model, s32 index);
u32 GSmodelGetPartCount(_GSmodel* model);
u32 GSpartGetMaterialCount(GSpart* part);
void GSpartInitMaterial(GSmaterial* material, GSpart* part, u32 index);
void GSpartFree(GSpart* part);
void GSparticleDestroyAllGenerators(void* bank, s32 children);
void GSparticleSetBankVisibility(void* bank, s32 visible);
void GSmodelAdvanceAnimation(_GSmodel* model, f32 frames);
void GSmodelSetAnimFrame(_GSmodel* model, f32 frame);
void GSmodelForceAnimTransformUpdate(_GSmodel* model);
void GSmodelSetAnimIndex(_GSmodel* model, s32 index);
void GSmodelSetAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetAnimType(_GSmodel* model, s32 type);
void GSmodelSetTexAnimIndex(_GSmodel* model, s32 index);
void GSmodelSetTexAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetTexAnimType(_GSmodel* model, s32 type);
void GSmodelRecalculateBound(_GSmodel* model);
void GSmodelRemoveNull(_GSmodel* model);
void GSmodelDisableAnimBlend(_GSmodel* model);
void GSmodelFreeDistortion(_GSmodel* model);
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
}

static s32 _modelInUseCount;
static s32 _modelMaxUsedCount;
static u8 _modelShadowShowDebug;
static u8 _invalidateVtxTex;

static _GSmodel* _modelLoad(_HSD_SceneModelSet* set, _HSD_Joint* joint, GSboundAnimHeader* header);

// Inline helpers from HSD's jobj.h (asserts carry that header's line numbers).
static inline bool HSD_JObjMtxIsDirty(HSD_JObj* jobj) {
    bool result;
    if (!jobj) {
        __assert("jobj.h", 605, "jobj");
    }
    result = false;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) {
        result = true;
    }
    return result;
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj* jobj) {
    if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetupMatrix(HSD_JObj* jobj) {
    if (!jobj || !HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetupMatrixSub(jobj);
}

static inline void HSD_JObjCopyMtx(HSD_JObj* jobj, Mtx mtx) {
    if (!jobj) {
        __assert("jobj.h", 1173, "jobj");
    }
    if (!mtx) {
        __assert("jobj.h", 1174, "mtx");
    }
    PSMTXCopy(mtx, jobj->mtx);
}

static inline void HSD_JObjClearFlags(HSD_JObj* jobj, u32 flags) {
    if (!jobj) {
        __assert("jobj.h", 1199, "jobj");
    }
    jobj->flags &= ~flags;
}

static inline bool MODEL_FLAG(_GSmodel* model, u32 flag) {
    return (model->flags & flag) == flag;
}

static inline HSD_JObj* _getRenderJObj(_GSmodel* model) {
    if (model->flags & 0x80) {
        return model->jobj14;
    }
    return model->jobj;
}

static inline void _setScl(_GSmodel* model, GSvec* v) {
    if (!(model->flags & 0x400)) {
        model->scale.x = v->x;
        model->scale.y = v->y;
        model->scale.z = v->z;
    }
}

static inline void _setRot(_GSmodel* model, GSvec* v) {
    if (!(model->flags & 0x400)) {
        model->rotation.x = v->x;
        model->rotation.y = v->y;
        model->rotation.z = v->z;
    }
}

static inline void _setPos(_GSmodel* model, GSvec* v) {
    if (!(model->flags & 0x400)) {
        model->position.x = v->x;
        model->position.y = v->y;
        model->position.z = v->z;
    }
}

static inline void _setScale(_GSmodel* model, GSvec* v) {
    if (model->attachMode == 0) {
        _setScl(model, v);
    } else {
        model->attachScale.x = v->x;
        model->attachScale.y = v->y;
        model->attachScale.z = v->z;
    }
    model->flags &= ~0x200;
}

static inline void _setRotation(_GSmodel* model, GSvec* v) {
    if (model->attachMode == 0) {
        _setRot(model, v);
    } else {
        model->attachRotation.x = v->x;
        model->attachRotation.y = v->y;
        model->attachRotation.z = v->z;
    }
    model->flags &= ~0x200;
}

static inline void _setPosition(_GSmodel* model, GSvec* v) {
    if (model->attachMode == 0) {
        _setPos(model, v);
    } else {
        model->attachPosition.x = v->x;
        model->attachPosition.y = v->y;
        model->attachPosition.z = v->z;
    }
    model->flags &= ~0x200;
}

static inline void _destroyLinkedParticles(_GSmodel* model) {
    if (model->particleBank) {
        GSparticleDestroyAllGenerators(model->particleBank, 1);
    }
}

// From the Dolphin SDK's OSFastCast.h (GQR3 is set up for u16 conversion).
static inline f32 __OSu16tof32(register const u16* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 3 }
    return ret;
}

static inline void OSu16tof32(const u16* in, f32* out) {
    *out = __OSu16tof32(in);
}

static inline void _initColorSwapTables(GSgfxLayer* layer) {
    if (layer->m_mode == 1) {
        HSD_InitColorSwapTable(0, 2, 2, 2, 3);
    } else {
        HSD_InitColorSwapTable(0, 0, 1, 2, 3);
    }
    HSD_InitColorSwapTable(1, 0, 1, 2, 3);
    HSD_InitColorSwapTable(2, 0, 1, 2, 3);
    HSD_InitColorSwapTable(3, 0, 1, 2, 3);
}

static void _modelRenderModelSub(GSgfxLayer* layer, GSgfxLayerPass pass, _GSmodel* model);

static void _modelFastRender() {
    if (_modelShadowShowDebug == 1) {
        modelShadowRenderDebug();
    }
    modelDistortionRender();
}

static void _modelRender(GSgfxLayer* layer, GSgfxLayerPass pass) {
    u32 perf;
    u8 layerID;
    u8 zCompare;
    _GSmodel* model;
    u8 drawn;

    layerID = layer->m_id;
    if (_invalidateVtxTex == 1) {
        layer->m_flags |= 0x8000000;
        layer->m_flags |= 0x10000000;
        _invalidateVtxTex = 0;
    }
    if (layerID == modelShadowLayerID) {
        f32 w;
        f32 x;
        f32 h;

        perf = GSgfxPerfbarCPUEntry(0xFF8000);
        modelShadowRender(layer);
        h = 240.0f;
        x = 0.0f;
        w = 320.0f;
        if (pass == GS_GFX_LAYER_PASS_OPA) {
            u16 efbH;
            u16 efbW;
            u16 halfW;
            u16 halfH;
            GSgfxVideoGetEFBSize(&efbW, &efbH);
            x = 0.0f;
            halfW = efbW >> 1;
            OSu16tof32(&halfW, &w);
            halfH = efbH >> 1;
            OSu16tof32(&halfH, &h);
        }
        layer->SetViewport(x, x, w, h);
        layer->m_scissorX = 0;
        layer->m_scissorY = 0;
        GSgfxVideoGetEFBSize(&layer->m_scissorW, &layer->m_scissorH);
        layer->m_state[0].dirty10 |= 0x1;
        layer->m_state[0].dirty |= 0x2;
        layer->m_state[1].dirty10 |= 0x1;
        layer->m_state[1].dirty |= 0x2;
        layer->FlushState();
    } else {
        drawn = 0;
        perf = GSgfxPerfbarCPUEntry(0xFF);
        _initColorSwapTables(layer);
        zCompare = layer->m_zCompare != 0;
        for (model = _modelTopPtr; model != 0; model = model->next) {
            GSgfxTokenIfClearedReset(&model->token);
            if (model->flags & 0x4000000) {
                for (int i = 0; i < 8; i++) {
                    if (model->layers[i] == layerID) {
                        _modelRenderModelSub(layer, pass, model);
                        drawn = 1;
                        break;
                    }
                }
            }
        }
        if (drawn) {
            HSD_ResetColorSwapTables();
            GScameraLoadActiveCameraMatrix(layer->m_id);
        }
        layer->SetZCompare(zCompare);
    }
    GSgfxPerfbarCPUEntry(perf);
}

extern "C" {

void GSmodelDrawModel(_GSmodel* model, GSgfxLayer* layer, GSgfxLayerPass pass) {
    u8 zCompare;

    if (model != 0 && (model->flags & 1)) {
        zCompare = layer->m_zCompare != 0;
        _initColorSwapTables(layer);
        _modelRenderModelSub(layer, pass, model);
        HSD_ResetColorSwapTables();
        layer->SetZCompare(zCompare);
    }
}

}

static void _modelRenderModelSub(GSgfxLayer* layer, GSgfxLayerPass pass, _GSmodel* model) {
    GScamera* camera;
    u8 zCompare;

    modelUpdateTransform(model);
    zCompare = layer->m_zCompare != 0;
    if (layer->m_mode != 0) {
        return;
    }
    switch (pass) {
    case GS_GFX_LAYER_PASS_OPA:
        if (zCompare != MODEL_FLAG(model, 0x1000000)) {
            layer->SetZCompare(MODEL_FLAG(model, 0x1000000));
        }
        break;
    case GS_GFX_LAYER_PASS_XLU:
        if (zCompare != MODEL_FLAG(model, 0x2000000)) {
            layer->SetZCompare(MODEL_FLAG(model, 0x2000000));
        }
        break;
    }
    camera = model->camera;
    if (camera == 0) {
        camera = GScameraGetActiveCamera();
    }
    if (camera != 0 && camera->cobj != 0) {
        HSD_JObj* jobj;

        GScameraLoadProjection(camera, layer);
        layer->m_unkD90 = 0;
        layer->m_state[0].dirty10 |= 0x4;
        layer->m_state[0].dirty |= 0x2;
        layer->m_state[1].dirty10 |= 0x4;
        layer->m_state[1].dirty |= 0x2;
        layer->FlushState();
        HSD_StateInvalidate(-1);
        GSlightSetupLights(camera->cobj);
        modelShadowPrepare(model, true);
        jobj = _getRenderJObj(model);
        switch (pass) {
        case GS_GFX_LAYER_PASS_OPA:
            HSD_JObjDispAll(jobj, 0, 1, 0);
            break;
        case GS_GFX_LAYER_PASS_XLU:
            HSD_JObjDispAll(jobj, 0, 6, 0);
            break;
        }
        *(volatile u8*)0xCC008000 = 0x10;
        *(volatile u16*)0xCC008000 = 0;
        *(volatile u16*)0xCC008000 = 0x1005;
        *(volatile u32*)0xCC008000 = 0;
        modelShadowPrepare(model, false);
        layer->InvalidateState();
        model->token = layer->tokenMark();
    }
    if (pass == GS_GFX_LAYER_PASS_XLU) {
        if (model->flags & 0x8000000) {
            modelShadowRenderMarukage(model, layer);
        }
        if (model->flags & 0x200000) {
            GSboundDraw(&model->bound, layer);
        }
    }
}

extern "C" {

f32 GSmodelGetDistanceFromCamera(_GSmodel* model) {
    GScamera* camera;
    GSvec pos;

    camera = model->camera;
    if (camera == 0) {
        camera = GScameraGetActiveCamera();
    }
    if (camera == 0) {
        return 0.0f;
    }
    GSboundGetWorldPosition(&model->bound, &pos);
    return PSVECDistance(&pos, &camera->position);
}

void GSmodelSetRenderCamera(_GSmodel* model, GScamera* camera) {
    model->camera = camera;
}

void GSmodelSetRenderLayer(_GSmodel* model, s32 count, s32* layers) {
    for (int i = 0; i < 8; i++) {
        if (i < count) {
            model->layers[i] = layers[i];
        } else {
            model->layers[i] = 0xFF;
        }
    }
}

}

static void _modelPostUpdate60fps() {
    u32 perf;
    _GSmodel* model;

    perf = GSgfxPerfbarCPUEntry(0x80);
    for (model = _modelTopPtr; model != 0; model = model->next) {
        if (modelProcessAt60fps(model) == 1) {
            GSmodelAdvanceAnimation(model, 1.0f);
        }
    }
    GSgfxPerfbarCPUEntry(perf);
}

static void _modelPostUpdate(f32 dt) {
    u32 perf;
    _GSmodel* model;

    perf = GSgfxPerfbarCPUEntry(0x80);
    for (model = _modelTopPtr; model != 0; model = model->next) {
        if (!modelProcessAt60fps(model)) {
            GSmodelAdvanceAnimation(model, dt);
        }
        modelDustUpdate(model);
    }
    GSgfxPerfbarCPUEntry(perf);
}

static void _modelPreUpdate(f32 dt) {
    u32 perf;
    _GSmodel* model;

    GSgfxProjectSetupParameters();
    perf = GSgfxPerfbarCPUEntry(0x80);
    for (model = _modelTopPtr; model != 0; model = model->next) {
        model->flags &= ~0x4400200;
        if (model->flags & 2) {
            if (model->camera == 0 && (model->flags & 0x100000)) {
                if (GSboundIsInViewFast(&model->bound) != 0) {
                    model->flags |= 0x4000000;
                }
            } else {
                model->flags |= 0x4000000;
            }
            if ((model->flags & 0x4000000) || (model->flags2 & 0x8)) {
                modelApplyAnimation(model);
            }
        }
    }
    for (model = _modelTopPtr; model != 0; model = model->next) {
        if (model->flags & 2) {
            modelUpdateAttachments(model);
            modelUpdateTransform(model);
        }
    }
    for (model = _modelTopPtr; model != 0; model = model->next) {
        if (model->flags & 0x4000000) {
            modelApplyPartAnimMixes(model);
        }
    }
    modelShadowUpdate();
    GSgfxPerfbarCPUEntry(perf);
}

extern "C" {

void GSmodelIterateList(void (*callback)(_GSmodel*, void*), void* arg) {
    _GSmodel* model;

    for (model = _modelTopPtr; model != 0; model = model->next) {
        callback(model, arg);
    }
}

_GSmodel* GSmodelSearchModelList(HSD_JObj* jobj) {
    _GSmodel* model;

    for (model = _modelTopPtr; model != 0; model = model->next) {
        if (_getRenderJObj(model) == jobj) {
            return model;
        }
    }
    return 0;
}

void GSmodelDestroyLinkedParticles(_GSmodel* model) {
    _destroyLinkedParticles(model);
}

u32 GSmodelGetGSparticleLinkAttachMode(_GSmodel* model) {
    return model->particleAttachMode;
}

void* GSmodelGetLinkedGSparticleBank(_GSmodel* model) {
    return model->particleBank;
}

void GSmodelSetGSparticleLinkAttachMode(_GSmodel* model, u32 mode) {
    model->particleAttachMode = mode;
}

void GSmodelLinkToGSparticleBank(_GSmodel* model, void* bank) {
    if (model->particleBank != bank) {
        model->particleBank = bank;
        if (model->particleBank) {
            model->flags2 |= 0x8;
            GSmodelSetAnimFrame(model, model->animFrame);
            GSmodelForceAnimTransformUpdate(model);
        } else {
            model->flags2 &= ~0x8;
        }
    }
}

GSbound* GSmodelGetBound(_GSmodel* model) {
    return &model->bound;
}

void GSmodelSetBoundCheck(_GSmodel* model, u8 enable) {
    if (enable) {
        model->flags |= 0x100000;
    } else {
        model->flags &= ~0x100000;
    }
}

void GSmodelSetFogState(_GSmodel* model, u8 opa, u8 xlu) {
    if (opa) {
        model->flags |= 0x1000000;
    } else {
        model->flags &= ~0x1000000;
    }
    if (xlu) {
        model->flags |= 0x2000000;
    } else {
        model->flags &= ~0x2000000;
    }
}

GSvec* GSmodelGetScalePtr(_GSmodel* model) {
    return &model->scale;
}

GSvec* GSmodelGetRotationPtr(_GSmodel* model) {
    return &model->rotation;
}

GSvec* GSmodelGetPositionPtr(_GSmodel* model) {
    return &model->position;
}

void GSmodelUpdate(_GSmodel* model) {
    u32 perf;

    perf = GSgfxPerfbarCPUEntry(0xFF0000);
    modelUpdateAttachments(model);
    modelUpdateTransform(model);
    GSgfxPerfbarCPUEntry(perf);
}

u32 GSmodelGetVisibility(_GSmodel* model) {
    return (model->flags >> 1) & 1;
}

void GSmodelGetScale(_GSmodel* model, GSvec* scale) {
    scale->x = model->scale.x;
    scale->y = model->scale.y;
    scale->z = model->scale.z;
}

void GSmodelGetRotation(_GSmodel* model, GSvec* rotation) {
    rotation->x = model->rotation.x;
    rotation->y = model->rotation.y;
    rotation->z = model->rotation.z;
}

void GSmodelGetPosition(_GSmodel* model, GSvec* position) {
    position->x = model->position.x;
    position->y = model->position.y;
    position->z = model->position.z;
}

void GSmodelAddPosition(_GSmodel* model, GSvec* delta) {
    GSvec pos;

    if (model->attachMode == 0) {
        pos.x = model->position.x;
        pos.y = model->position.y;
        pos.z = model->position.z;
    } else {
        pos.x = model->attachPosition.x;
        pos.y = model->attachPosition.y;
        pos.z = model->attachPosition.z;
    }
    PSVECAdd(&pos, delta, &pos);
    _setPosition(model, &pos);
}

void GSmodelSetVisibility(_GSmodel* model, u8 visible) {
    if (visible) {
        model->flags |= 2;
        if (model->particleBank) {
            GSparticleSetBankVisibility(model->particleBank, 1);
        }
    } else {
        model->flags &= ~2;
        if (model->particleBank) {
            GSparticleSetBankVisibility(model->particleBank, 0);
        }
    }
}

void GSmodelSetScale(_GSmodel* model, GSvec* scale) {
    _setScale(model, scale);
}

void GSmodelSetRotation(_GSmodel* model, GSvec* rotation) {
    _setRotation(model, rotation);
}

void GSmodelSetPosition(_GSmodel* model, GSvec* position) {
    _setPosition(model, position);
}

Mtx* GSmodelGetMatrixPtr(_GSmodel* model) {
    HSD_JObjSetupMatrix(model->jobj);
    return &model->jobj->mtx;
}

void GSmodelSetMatrix(_GSmodel* model, Mtx mtx) {
    HSD_JObj* jobj = model->jobj;
    HSD_JObjCopyMtx(jobj, mtx);
    jobj->flags |= 0x3800000;
    HSD_JObjSetMtxDirty(jobj);
}

void GSmodelDetachFromGSpart(_GSmodel* model, u8 restore) {
    if (model->attachMode != 0) {
        HSD_JObj* jobj = model->jobj;
        HSD_JObjClearFlags(jobj, 0x3800000);
        HSD_JObjSetMtxDirty(jobj);
        model->attachModel = 0;
        model->attachIndex = 0;
        model->flags &= ~0x40000;
        model->attachMode = 0;
        if (restore) {
            _setPosition(model, &model->attachPosition);
            _setRotation(model, &model->attachRotation);
            _setScale(model, &model->attachScale);
        }
    }
}

void GSmodelAttachToGSpart(_GSmodel* model, GSpart* part, s32 mode, u8 inherit, u8 identity) {
    GSvec partPos;
    GSvec partRot;
    GSvec partScale;
    GSvec diff;
    GSvec invRot;
    Quaternion quat;

    if (model->attachMode == 0 && mode != 0) {
    model->attachModel = part->model;
    model->attachIndex = part->index;
    if (identity == 1) {
        model->attachPosition.x = 0.0f;
        model->attachPosition.y = 0.0f;
        model->attachPosition.z = 0.0f;
        model->attachRotation.x = 0.0f;
        model->attachRotation.y = 0.0f;
        model->attachRotation.z = 0.0f;
        model->attachScale.x = 1.0f;
        model->attachScale.y = 1.0f;
        model->attachScale.z = 1.0f;
    } else {
        GSpartGetTransform(part, &partPos, &partRot, &partScale);
        PSVECSubtract(&model->position, &partPos, &diff);
        PSVECScale(&partRot, &invRot, -1.0f);
        EulerToQuat(&invRot, &quat);
        GSvecTransformQuat(&model->attachPosition, &quat, &diff);
        PSVECSubtract(&model->rotation, &partRot, &model->attachRotation);
        model->attachScale.x = model->scale.x * partScale.x;
        model->attachScale.y = model->scale.y * partScale.y;
        model->attachScale.z = model->scale.z * partScale.z;
    }
    model->attachMode = mode;
    if (inherit) {
        model->flags |= 0x40000;
    }
    model->flags &= ~0x400000;
    model->flags &= ~0x200;
    }
}

void GSmodelFree(_GSmodel* model) {
    GSmaterial* material;
    u32 count;

    GSgfxRenderWaitForDrawComplete();
    modelShadowFreeModelList(model);
    count = model->materialCount;
    material = model->materials;
    if (count != 0 && material != 0) {
        for (u32 i = 0; i < count; i++, material++) {
            modelMaterialFree(material);
        }
        GSmemFree(model->materials);
        model->materialCount = 0;
        model->materials = 0;
    }
    GSmodelRemoveNull(model);
    modelRemoveCenterNull(model);
    GSmodelDisableAnimBlend(model);
    HSD_JObjUnref(model->jobj);
    _destroyLinkedParticles(model);
    GSmodelFreeDistortion(model);
    GSboundFree(&model->bound);
    _modelInUseCount--;
    modelBankReleaseModel(model);
}

_GSmodel* GSmodelClone(_GSmodel* model) {
    _HSD_Joint joint;

    joint.class_name = 0;
    joint.flags = model->set->joint->flags | 0x1000;
    joint.child = model->set->joint;
    joint.next = 0;
    joint.dobj = 0;
    joint.rotation.x = 0.0f;
    joint.rotation.y = 0.0f;
    joint.rotation.z = 0.0f;
    joint.scale.x = 1.0f;
    joint.scale.y = 1.0f;
    joint.scale.z = 1.0f;
    joint.position.x = 0.0f;
    joint.position.y = 0.0f;
    joint.position.z = 0.0f;
    joint.envelopemtx = 0;
    joint.robj = 0;
    if (GSboundHasAnimData(&model->bound) == 0) {
        return _modelLoad(model->set, &joint, 0);
    } else {
        return _modelLoad(model->set, &joint, model->bound.animHeader);
    }
}

_GSmodel* GSmodelLoad(_HSD_SceneModelSet* set, GSboundAnimHeader* header) {
    _invalidateVtxTex = 1;
    return _modelLoad(set, set->joint, header);
}

void GSmodelInit(void) {
    GSgfxRenderModule module = { 0, _modelPreUpdate, _modelRender, _modelFastRender, _modelPostUpdate, _modelPostUpdate60fps, 0xB29A48E1 };

    modelBankInit();
    modelShadowInit();
    GSgfxRenderModuleRegister(0x20, &module, 0);
    HSD_SetVertexBuffer(GSmemAlloc(0x5DC0), 2000);
    HSD_SetNormalBuffer(GSmemAlloc(0x5DC0), 2000);
    HSD_SetExpArgBuffer(GSmemAlloc(400), 100);
}

}

void modelSetScl(_GSmodel* model, GSvec* v) {
    _setScl(model, v);
}

void modelSetRot(_GSmodel* model, GSvec* v) {
    _setRot(model, v);
}

void modelSetPos(_GSmodel* model, GSvec* v) {
    _setPos(model, v);
}

HSD_JObj* modelGetRenderJObj(_GSmodel* model) {
    return _getRenderJObj(model);
}

static inline void _vecSet(GSvec* v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

static _GSmodel* _modelLoad(_HSD_SceneModelSet* set, _HSD_Joint* joint, GSboundAnimHeader* header) {
    _GSmodel* model;
    u32 i;
    u32 j;
    GSpart* part;
    u32 total;
    GSmaterial* material;
    u32 count;
    u32 k;
    u32 n;
    GSpart* part2;

    model = modelBankGetFreeModel();
    if (model == 0) {
        return 0;
    }
    model->flags |= 0x2000;
    model->camera = 0;
    model->animCount = 0;
    model->texAnimCount = 0;
    model->unk220 = 0;
    model->materialCount = 0;
    model->materials = 0;
    for (i = 0; i < 8; i++) {
        model->layers[i] = 0xFF;
    }
    model->layers[0] = 2;
    model->unk5F8 = 0;
    model->unk60C = 1.0f;
    model->unk5FC = 0.0f;
    model->unk600[1] = 0;
    model->unk600[0] = 0;
    model->unk600[2] = 0;
    model->unk600[3] = 0;
    model->unk604 = 0.0f;
    model->unk608[1] = 0;
    model->unk608[0] = 0;
    model->unk608[2] = 0;
    model->unk608[3] = 0;
    model->unk613 = 0;
    model->unk610 = 0;
    model->unk612 = 0;
    model->unk614 = 0;
    model->unk618 = 0;
    model->unk61C = 0;
    model->unk5E8 = 0;
    model->unk5EC = 0;
    model->unk5F0 = 0;
    model->unk5F4 = 0.0f;
    model->attachMode = 0;
    model->attachModel = 0;
    model->attachIndex = 0;
    model->particleBank = 0;
    model->particleAttachMode = 1;
    model->set = set;
    model->jobj = HSD_JObjLoadJoint(joint);
    model->jobj10 = 0;
    model->jobj14 = 0;
    _vecSet(&model->position, model->jobj->translate.x, model->jobj->translate.y, model->jobj->translate.z);
    _vecSet(&model->rotation, model->jobj->rotate.x, model->jobj->rotate.y, model->jobj->rotate.z);
    _vecSet(&model->scale, model->jobj->scale.x, model->jobj->scale.y, model->jobj->scale.z);
    for (i = 0; i < 16; i++) {
        model->mixB[i].unk0 = 0;
    }
    for (i = 0; i < 12; i++) {
        model->mixA[i].unk18 = 0;
    }
    model->unk21C = 0;
    model->unk21D = 0;
    if (model->set->shapeanim_joint) {
        model->flags |= 0x10;
    }
    if (model->set->animjoint) {
        model->flags |= 4;
        model->animIndex = -1;
        while (model->set->animjoint[model->animCount]) {
            model->animCount++;
        }
        GSmodelSetAnimIndex(model, 0);
        GSmodelSetAnimRate(model, 0.5f);
        GSmodelSetAnimType(model, 1);
    }
    if (model->set->matanim_joint) {
        model->flags |= 8;
        model->texAnimIndex = -1;
        while (model->set->matanim_joint[model->texAnimCount]) {
            model->texAnimCount++;
        }
        GSmodelSetTexAnimIndex(model, 0);
        GSmodelSetTexAnimRate(model, 0.5f);
        GSmodelSetTexAnimType(model, 1);
    }
    GSboundCreate(&model->bound, header);
    GSboundSetDataPtr(&model->bound, 1, model);
    GSmodelRecalculateBound(model);
    total = 0;
    count = GSmodelGetPartCount(model);
    for (i = 0; i < count; i++) {
        part = GSmodelGetPart(model, i);
        total += GSpartGetMaterialCount(part);
        GSpartFree(part);
    }
    if (total != 0) {
        material = (GSmaterial*)GSmemAlloc(total * sizeof(GSmaterial));
        if (material != 0) {
            model->materials = material;
            model->materialCount = total;
            for (k = 0; k < count; k++) {
                part2 = GSmodelGetPart(model, k);
                n = GSpartGetMaterialCount(part2);
                for (j = 0; j < n; j++, material++) {
                    modelMaterialInit(material);
                    GSpartInitMaterial(material, part2, j);
                }
                GSpartFree(part2);
            }
        }
    }
    HSD_JObjCountVertices(model->jobj, &model->vertexCount, &model->polygonCount);
    _modelInUseCount++;
    if (_modelInUseCount > _modelMaxUsedCount) {
        _modelMaxUsedCount = _modelInUseCount;
    }
    return model;
}
