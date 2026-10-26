
#include <dolphin/types.h>

#pragma pool_strings off

struct Vec {
    f32 x, y, z;
};

struct HSD_JObj {
    u8 unk0[0x8];
    HSD_JObj* next;
    HSD_JObj* parent;
    HSD_JObj* child;
    u32 flags;
    u8 unk18[0x4];
    Vec rotate;
    f32 rotateW;
    Vec scale;
    Vec translate;
};

#define JOBJ_MTX_DIRTY (1 << 6)
#define JOBJ_USE_QUATERNION (1 << 17)
#define JOBJ_USER_DEF_MTX (1 << 23)
#define JOBJ_MTX_INDEP_SRT (1 << 25)

struct GStexture;

struct GSmaterial {
    u16 alpha;
    u16 unk2;
    u8 unk4[0xC];
    u8 channel[4];
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u8 unk20[0xC];
    GStexture* tex2C;
    GStexture* tex30;
};

struct GSbound;

struct _GSmodel {
    u32 flags;
    u8 unk4[0x8];
    HSD_JObj* root;
    u8 unk10[0x2C];
    u8 bound[0x20];
    u8 unk5C[0x18];
    s32 animType;
    s32 animIndex;
    u8 unk7C[0x564];
    GSmaterial* materials;
    u32 materialCount;
};

#define MODEL_CENTER_NULL 0x10000
#define MODEL_ROOT_NULL 0x20000
#define MODEL_FLAG(model, flag) (((model)->flags & (flag)) == (flag))

#define GS_TEXTURE_AUTO ((GStexture*)0xFEFEFEFE)

class GSgfxLayer {
public:
    void SetTextureCopy(GStexture* texture, bool, u8*);
    GStexture* GetTextureCopy();
};

extern Vec unitScaleVector;

extern "C" {
void __assert(const char* file, s32 line, const char* expr);
HSD_JObj* HSD_JObjAlloc(void);
HSD_JObj* HSD_JObjRemove(HSD_JObj* jobj);
void HSD_JObjAddChild(HSD_JObj* jobj, HSD_JObj* child);
void HSD_JObjAddNext(HSD_JObj* jobj, HSD_JObj* next);
u32 HSD_JObjGetFlags(HSD_JObj* jobj);
void HSD_JObjSetFlags(HSD_JObj* jobj, u32 flags);
void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj);
void HSD_JObjSetupMatrixSub(HSD_JObj* jobj);

GSgfxLayer* GSgfxLayerFindByID(s32 id);
void GSboundGetMinMax(void* bound, Vec* min, Vec* max, s32, s32, s32, s32);
void GSlerpGetLinearInterpolationVector(Vec* out, Vec* a, Vec* b, f32 t);
u16 GSmodelGetPartCount(_GSmodel* model);
void GSmodelSetAnimIndex(_GSmodel* model, s32 index);
void GSmodelSetAnimType(_GSmodel* model, s32 type);
void GSmodelStartAnimation(_GSmodel* model);

void GSmaterialResetTexture(GSmaterial* mat);
void GSmaterialSetTexture(GSmaterial* mat, void* texture);
u32 GSmaterialGetEnabledExtensions(GSmaterial* mat);
void GSmaterialEnableExtension(GSmaterial* mat, u32 ext);
void GSmaterialDisableExtension(GSmaterial* mat, u32 ext);
void GSmaterialGetModulate(GSmaterial* mat, void* color);
void GSmaterialSetModulate(GSmaterial* mat, void* color);
void GSmaterialSetColorChannels(GSmaterial* mat, void* channels);
void GSmaterialSetEnvMapBlendValue(GSmaterial* mat, f32 value);
void GSmaterialSetEnvMapParams(GSmaterial* mat, u32 a, u32 b, GStexture* tex, f32 blend);
void GSmaterialResetPEdescr(GSmaterial* mat);
void GSmaterialSetPEdescr(GSmaterial* mat, void* pe);
void GSmaterialResetAlpha(GSmaterial* mat);
void GSmaterialStoreAlpha(GSmaterial* mat);
void GSmaterialSetAlpha(GSmaterial* mat, f32 alpha);
void GSmaterialResetFlags(GSmaterial* mat);
u32 GSmaterialGetFlags(GSmaterial* mat);
void GSmaterialSetFlags(GSmaterial* mat, u32 flags);
}

void modelUpdateCenterNull(_GSmodel* model);


static inline HSD_JObj* HSD_JObjGetChild(HSD_JObj* jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->child;
}

static inline HSD_JObj* HSD_JObjGetNext(HSD_JObj* jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->next;
}

static inline bool HSD_JObjMtxIsDirty(HSD_JObj* jobj) {
    bool result;
    if (!jobj) {
        __assert("jobj.h", 605, "jobj");
    }
    result = false;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY)) {
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

static inline void HSD_JObjSetScale(HSD_JObj* jobj, Vec* scale) {
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

static inline void HSD_JObjGetScale(HSD_JObj* jobj, Vec* scale) {
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

static inline void HSD_JObjSetTranslate(HSD_JObj* jobj, Vec* translate) {
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

static inline void HSD_JObjGetTranslate(HSD_JObj* jobj, Vec* translate) {
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

static u8 g_envmap_tex_ref_count;

static inline HSD_JObj* modelGetRootJObj(_GSmodel* model) {
    HSD_JObj* jobj = model->root;
    if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
        jobj = jobj->child;
    }
    return jobj;
}

static inline HSD_JObj* modelGetLastChild(HSD_JObj* jobj) {
    HSD_JObj* cur;
    for (cur = HSD_JObjGetChild(jobj); HSD_JObjGetNext(cur) != 0; cur = HSD_JObjGetNext(cur)) {
    }
    return cur;
}

static inline bool modelIsExtensionEnabled(_GSmodel* model, u32 ext) {
    if (model->materialCount == 0) {
        return false;
    }
    if (model->materials == 0) {
        return false;
    }
    if (GSmaterialGetEnabledExtensions(model->materials) & ext) {
        return true;
    }
    return false;
}

extern "C" {

void GSmodelResetTextureChange(_GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* mat = model->materials;
    count = model->materialCount;
    for (; i < count; i++, mat++) {
        GSmaterialResetTexture(mat);
    }
}

void GSmodelSetTextureChange(_GSmodel* model, void* texture) {
    u32 i = 0;
    u32 count = model->materialCount;
    GSmaterial* mat = model->materials;
    for (; i < count; i++, mat++) {
        GSmaterialSetTexture(mat, texture);
    }
}

bool GSmodelIsModulationEnabled(_GSmodel* model) {
    if (model->materialCount == 0) {
        return false;
    }
    if (model->materials == 0) {
        return false;
    }
    return (GSmaterialGetEnabledExtensions(model->materials) & 1) ? true : false;
}

void GSmodelGetModulationColor(_GSmodel* model, u8* color) {
    if (modelIsExtensionEnabled(model, 1)) {
        GSmaterialGetModulate(model->materials, color);
    } else {
        color[0] = color[1] = color[2] = 0x7F;
        color[3] = 0xFF;
    }
}

void GSmodelDisableModulation(_GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* mat = model->materials;
    count = model->materialCount;
    for (; i < count; i++, mat++) {
        GSmaterialDisableExtension(mat, 1);
    }
}

void GSmodelSetModulationColor(_GSmodel* model, void* color) {
    u32 i = 0;
    u32 count = model->materialCount;
    GSmaterial* mat = model->materials;
    for (; i < count; i++, mat++) {
        GSmaterialSetModulate(mat, color);
    }
}

void GSmodelEnableModulation(_GSmodel* model, void* color) {
    u32 i = 0;
    u32 count = model->materialCount;
    GSmaterial* mat = model->materials;
    for (; i < count; i++, mat++) {
        GSmaterialSetModulate(mat, color);
        GSmaterialEnableExtension(mat, 1);
    }
}

void GSmodelDisableColorSwap(_GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* mat = model->materials;
    count = model->materialCount;
    for (; i < count; i++, mat++) {
        GSmaterialDisableExtension(mat, 2);
    }
}

void GSmodelEnableColorSwap(_GSmodel* model, void* channels) {
    u32 i = 0;
    u32 count = model->materialCount;
    GSmaterial* mat = model->materials;
    for (; i < count; i++, mat++) {
        GSmaterialSetColorChannels(mat, channels);
        GSmaterialEnableExtension(mat, 2);
    }
}

bool GSmodelIsEnvMapEnabled(_GSmodel* model) {
    if (model->materialCount == 0) {
        return false;
    }
    if (model->materials == 0) {
        return false;
    }
    return (GSmaterialGetEnabledExtensions(model->materials) & 4) != 0;
}

void GSmodelDisableEnvMap(_GSmodel* model) {
    if (modelIsExtensionEnabled(model, 4)) {
        u32 i = 0;
        u32 count;
        GSmaterial* mat = model->materials;
        count = model->materialCount;
        GSgfxLayer* layer;
        for (; i < count; i++, mat++) {
            GSmaterialDisableExtension(mat, 4);
        }
        layer = GSgfxLayerFindByID(0);
        if (layer != 0) {
            if (--g_envmap_tex_ref_count == 0) {
                layer->SetTextureCopy(0, false, 0);
            }
        }
    }
}

void GSmodelSetEnvMapBlendValue(_GSmodel* model, f32 value) {
    if (modelIsExtensionEnabled(model, 4)) {
        u32 i = 0;
        u32 count = model->materialCount;
        GSmaterial* mat = model->materials;
        for (; i < count; i++, mat++) {
            GSmaterialSetEnvMapBlendValue(mat, value);
        }
    }
}

void GSmodelEnableEnvMap(_GSmodel* model, u32 a, u32 b, f32 blend) {
    u32 i;
    u32 count;
    GSmaterial* mat;
    GSgfxLayer* layer;
    GStexture* tex;

    if (!modelIsExtensionEnabled(model, 4)) {
        layer = GSgfxLayerFindByID(0);
        if (layer != 0) {
            g_envmap_tex_ref_count++;
            layer->SetTextureCopy(GS_TEXTURE_AUTO, false, 0);
            tex = layer->GetTextureCopy();
            if (tex != 0) {
                i = 0;
                count = model->materialCount;
                mat = model->materials;
                for (; i < count; i++, mat++) {
                    GSmaterialSetEnvMapParams(mat, a, b, tex, blend);
                    GSmaterialEnableExtension(mat, 4);
                }
            }
        }
    }
}

void GSmodelResetPEdescr(_GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* mat = model->materials;
    count = model->materialCount;
    for (; i < count; i++, mat++) {
        GSmaterialResetPEdescr(mat);
    }
}

void GSmodelSetPEdescr(_GSmodel* model, void* pe) {
    u32 i = 0;
    u32 count = model->materialCount;
    GSmaterial* mat = model->materials;
    for (; i < count; i++, mat++) {
        GSmaterialSetPEdescr(mat, pe);
    }
}

void GSmodelResetMaterialAlpha(_GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* mat = model->materials;
    count = model->materialCount;
    for (; i < count; i++, mat++) {
        GSmaterialResetAlpha(mat);
    }
}

void GSmodelInitMaterialAlpha(_GSmodel* model) {
    u32 i = 0;
    u32 count = model->materialCount;
    GSmaterial* mat = model->materials;
    for (; i < count; i++, mat++) {
        GSmaterialStoreAlpha(mat);
    }
}

void GSmodelSetMaterialAlpha(_GSmodel* model, f32 alpha) {
    u32 i = 0;
    u32 count = model->materialCount;
    GSmaterial* mat = model->materials;
    for (; i < count; i++, mat++) {
        GSmaterialSetAlpha(mat, mat->alpha * alpha / 255.0f);
    }
}

void GSmodelResetRenderFlags(_GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* mat = model->materials;
    count = model->materialCount;
    for (; i < count; i++, mat++) {
        GSmaterialResetFlags(mat);
    }
}

void GSmodelSetRenderFlags(_GSmodel* model, u32 flags) {
    u32 i = 0;
    u32 count = model->materialCount;
    GSmaterial* mat = model->materials;
    for (; i < count; i++, mat++) {
        GSmaterialSetFlags(mat, flags | GSmaterialGetFlags(mat));
    }
}

}

void modelRemoveCenterNull(_GSmodel* model) {
    if (MODEL_FLAG(model, MODEL_CENTER_NULL)) {
        HSD_JObjRemove(modelGetLastChild(modelGetRootJObj(model)));
        model->flags &= ~MODEL_CENTER_NULL;
    }
}

extern "C" u16 GSmodelCenterNull(_GSmodel* model) {
    HSD_JObj* jobj;
    HSD_JObj* root;
    HSD_JObj* cur;

    if (MODEL_FLAG(model, MODEL_CENTER_NULL)) {
        return GSmodelGetPartCount(model) - 1;
    }
    jobj = HSD_JObjAlloc();
    if (jobj == 0) {
        return 0;
    }
    root = model->root;
    if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
        root = root->child;
    }
    cur = HSD_JObjGetChild(root);
    if (cur == 0) {
        HSD_JObjAddChild(root, jobj);
    } else {
        for (; HSD_JObjGetNext(cur) != 0; cur = HSD_JObjGetNext(cur)) {
        }
        HSD_JObjAddNext(cur, jobj);
    }
    HSD_JObjSetFlags(jobj, HSD_JObjGetFlags(root));
    model->flags |= MODEL_CENTER_NULL;
    modelUpdateCenterNull(model);
    return GSmodelGetPartCount(model) - 1;
}

void modelUpdateCenterNull(_GSmodel* model) {
    void* bound = model->bound;
    if (MODEL_FLAG(model, MODEL_CENTER_NULL)) {
        HSD_JObj* jobj = modelGetLastChild(modelGetRootJObj(model));
        Vec center;
        Vec min;
        Vec max;
        GSboundGetMinMax(bound, &min, &max, 0, 0, 0, 1);
        GSlerpGetLinearInterpolationVector(&center, &min, &max, 0.5f);
        HSD_JObjSetTranslate(jobj, &center);
        HSD_JObjSetRotationX(jobj, 0.0f);
        HSD_JObjSetRotationY(jobj, 0.0f);
        HSD_JObjSetRotationZ(jobj, 0.0f);
        HSD_JObjSetScale(jobj, &unitScaleVector);
        HSD_JObjSetupMatrix(jobj);
    }
}

extern "C" {

u32 GSmodelIsRootNullAdded(_GSmodel* model) {
    return (model->flags >> 17) & 1;
}

void GSmodelRemoveNull(_GSmodel* model) {
    if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
        HSD_JObj* null = model->root;
        HSD_JObj* root = HSD_JObjGetChild(null);
        Vec translate;
        Vec scale;
        f32 rx, ry, rz;

        HSD_JObjGetTranslate(null, &translate);
        rx = HSD_JObjGetRotationX(null);
        ry = HSD_JObjGetRotationY(null);
        rz = HSD_JObjGetRotationZ(null);
        HSD_JObjGetScale(null, &scale);
        HSD_JObjSetTranslate(root, &translate);
        HSD_JObjSetRotationX(root, rx);
        HSD_JObjSetRotationY(root, ry);
        HSD_JObjSetRotationZ(root, rz);
        HSD_JObjSetScale(root, &scale);
        null = HSD_JObjRemove(null);
        HSD_JObjSetupMatrix(root);
        model->flags &= ~MODEL_ROOT_NULL;
        model->root = null;
    }
}

void GSmodelGetRootScale(_GSmodel* model, Vec* scale) {
    HSD_JObj* jobj = model->root;
    if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
        HSD_JObjGetScale(jobj->child, scale);
    } else {
        scale->x = 1.0f;
        scale->y = 1.0f;
        scale->z = 1.0f;
    }
}

void GSmodelGetRootRotation(_GSmodel* model, Vec* rotation) {
    HSD_JObj* jobj = model->root;
    if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
        jobj = jobj->child;
        rotation->x = HSD_JObjGetRotationX(jobj);
        rotation->y = HSD_JObjGetRotationY(jobj);
        rotation->z = HSD_JObjGetRotationZ(jobj);
    } else {
        rotation->x = 0.0f;
        rotation->y = 0.0f;
        rotation->z = 0.0f;
    }
}

void GSmodelGetRootPosition(_GSmodel* model, Vec* position) {
    HSD_JObj* jobj = model->root;
    if (MODEL_FLAG(model, MODEL_ROOT_NULL)) {
        HSD_JObjGetTranslate(jobj->child, position);
    } else {
        position->x = 0.0f;
        position->y = 0.0f;
        position->z = 0.0f;
    }
}


void GSmodelAddNull(_GSmodel* model, Vec* position, Vec* rotation, Vec* scale) {
    HSD_JObj* root = model->root;
    HSD_JObj* null;
    Vec tmp;

    if (model->flags & 0x80) {
        return;
    }
    if (!MODEL_FLAG(model, MODEL_ROOT_NULL)) {
        Vec oldTranslate;
        Vec oldScale;
        f32 rx, ry, rz;

        null = HSD_JObjAlloc();
        if (null == 0) {
            return;
        }
        HSD_JObjGetTranslate(root, &oldTranslate);
        rx = HSD_JObjGetRotationX(root);
        ry = HSD_JObjGetRotationY(root);
        rz = HSD_JObjGetRotationZ(root);
        HSD_JObjGetScale(root, &oldScale);
        if (position != 0) {
            HSD_JObjSetTranslate(root, position);
        } else {
            tmp.x = 0.0f;
            tmp.y = 0.0f;
            tmp.z = 0.0f;
            HSD_JObjSetTranslate(root, &tmp);
        }
        if (rotation != 0) {
            HSD_JObjSetRotationX(root, rotation->x);
            HSD_JObjSetRotationY(root, rotation->y);
            HSD_JObjSetRotationZ(root, rotation->z);
        } else {
            HSD_JObjSetRotationX(root, 0.0f);
            HSD_JObjSetRotationY(root, 0.0f);
            HSD_JObjSetRotationZ(root, 0.0f);
        }
        if (scale != 0) {
            HSD_JObjSetScale(root, scale);
        } else {
            tmp.x = 1.0f;
            tmp.y = 1.0f;
            tmp.z = 1.0f;
            HSD_JObjSetScale(root, &tmp);
        }
        HSD_JObjSetupMatrix(root);
        HSD_JObjAddChild(null, model->root);
        model->flags |= MODEL_ROOT_NULL;
        model->root = null;
        HSD_JObjSetFlags(null, HSD_JObjGetFlags(root));
        HSD_JObjSetTranslate(null, &oldTranslate);
        HSD_JObjSetRotationX(null, rx);
        HSD_JObjSetRotationY(null, ry);
        HSD_JObjSetRotationZ(null, rz);
        HSD_JObjSetScale(null, &oldScale);
        HSD_JObjSetMtxDirty(root);
        HSD_JObjSetupMatrix(root);
        HSD_JObjSetupMatrix(null);
        GSmodelSetAnimIndex(model, model->animIndex);
        GSmodelSetAnimType(model, model->animType);
        GSmodelStartAnimation(model);
    } else {
        null = HSD_JObjGetChild(root);
        if (position != 0) {
            HSD_JObjSetTranslate(null, position);
        } else {
            tmp.x = 0.0f;
            tmp.y = 0.0f;
            tmp.z = 0.0f;
            HSD_JObjSetTranslate(null, &tmp);
        }
        if (rotation != 0) {
            HSD_JObjSetRotationX(null, rotation->x);
            HSD_JObjSetRotationY(null, rotation->y);
            HSD_JObjSetRotationZ(null, rotation->z);
        } else {
            HSD_JObjSetRotationX(null, 0.0f);
            HSD_JObjSetRotationY(null, 0.0f);
            HSD_JObjSetRotationZ(null, 0.0f);
        }
        if (scale != 0) {
            HSD_JObjSetScale(null, scale);
        } else {
            tmp.x = 1.0f;
            tmp.y = 1.0f;
            tmp.z = 1.0f;
            HSD_JObjSetScale(null, &tmp);
        }
        HSD_JObjSetupMatrix(null);
        GSmodelSetAnimIndex(model, model->animIndex);
        GSmodelSetAnimType(model, model->animType);
        GSmodelStartAnimation(model);
    }
}

}

void modelMaterialFree(GSmaterial* mat) {
    GSmaterialResetPEdescr(mat);
    GSmaterialResetTexture(mat);
    GSmaterialDisableExtension(mat, 0xFFFF);
}

void modelMaterialInit(GSmaterial* mat) {
    if (mat == 0) {
        return;
    }
    mat->tex30 = GS_TEXTURE_AUTO;
    mat->unk2 = 0;
    mat->channel[0] = 0;
    mat->channel[1] = 1;
    mat->channel[2] = 2;
    mat->channel[3] = 3;
    mat->unk1C = 0;
    mat->unk14 = 0;
    mat->unk18 = 0;
    mat->tex2C = GS_TEXTURE_AUTO;
}
