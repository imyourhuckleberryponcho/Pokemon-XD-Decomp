#include <dolphin/types.h>
#pragma pool_strings off
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
enum ASM { ASM_draft_dummy };
struct GSbezier;
class GSeffect;
struct GSmaterial;
struct HSD_Archive;
struct ModelBank;
typedef f32 Mtx[3][4];
struct Quaternion;
struct Vec;
struct _GSmodel;
struct leafData;
class leafEffect;

extern "C++" {
struct GSbezier {
    u8 _draft[1];
};
struct GSgfxLayer;
enum GSgfxLayerPass { GSgfxLayerPass_dummy };
class GSeffect {
public:
    bool m_active;
    bool m_visible;
    GSeffect* m_next;

    GSeffect();
    bool Start();
    void Stop();

    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32 dt);
    virtual void _render(GSgfxLayer* layer, GSgfxLayerPass pass);
    virtual void _fastRender();
    virtual ~GSeffect();
};
struct GSmaterial {
    u8 _draft[1];
};
struct HSD_Archive {
    u8 _draft[1];
};
struct ModelBank {
    u8 _draft[1];
};
struct Quaternion {
    f32 x, y, z, w;
};
struct Vec {
    f32 x, y, z;
};
struct _GSmodel {
    u8 _draft[1];
};
struct leafData {
    Vec p0;
    Vec p1;
    Vec p2;
    Vec p3;
    Quaternion q0;
    Quaternion q1;
    f32 scale;
    f32 t;
    _GSmodel* model;
};
class leafEffect : public GSeffect {
public:
    s32 unkC;
    _GSmodel* model;
    f32 unk14;
    f32 params[10];
    f32 unk40;
    f32 unk44;
    f32 unk48;
    s32 unk4C;
    u32 resID;
    f32 unk54;
    f32 unk58;
    f32 unk5C;

    leafEffect(unsigned char**, float);
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(float);
    virtual ~leafEffect();
    s32 GenerateLeafData(leafData*);
    void UpdateLeafData(leafData*);
};

extern "C" {
void C_QUATRotAxisRad(Quaternion* r, const Vec* axis, f32 rad);
void C_QUATSlerp(const Quaternion* p, const Quaternion* q, Quaternion* r, f32 t);
void GSbezierCalculateVector(Vec* out, GSbezier* bezier, f32 t);
u8 GSgfxVideoGetVsyncRate(void);
void GSlogWrite(const char*, ...);
void GSmaterialSetAlpha(GSmaterial* material, f32 alpha);
ModelBank* GSmemAllocClr(u32 size);
void GSmemFree(void* ptr);
_GSmodel* GSmodelClone(_GSmodel* model);
void GSmodelFree(_GSmodel* model);
void GSmodelSetMatrix(_GSmodel* model, Mtx mtx);
void GSmodelSetVisibility(_GSmodel* model, u8 visible);
void GSresFreeResource(u32 grp, u32 id);
void* GSresGetResource(u32 grp, u32 id);
void GSresIsUniqueID(u32 grp, u32 id, u8 unique);
f32 HSD_Randf(void);
void PSMTXQuat(register Mtx m, const register Quaternion* q);
asm void PSMTXScaleApply(const register Mtx src, register Mtx dst, register f32 xS, register f32 yS, register f32 zS);
asm void PSMTXTransApply(const register Mtx src, register Mtx dst, register f32 xT, register f32 yT, register f32 zT);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
void PSVECNormalize(const register Vec* src, register Vec* unit);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double cos(double x);
void loadModel(HSD_Archive* archive, u32 arg1, u32 index, u32 arg2);
double sin(double x);
s32 wazaSequenceSysGetResID(void);
}
leafEffect::~leafEffect() {
    Stop();
    if (resID != 0) {
        GSresFreeResource(0x4E20, resID);
    }
}
}

extern "C++" {
void leafEffect::_stop() {
    u8 *var_r30;
    GSmaterial *var_r30_2;
    _GSmodel *temp_r3;
    u32 var_r29;
    u32 var_r29_2;
    u32 var_r31;
    u8 *temp_r0;
    u8 *temp_r3_2;

    temp_r0 = M2C_FIELD(this, u8 **, 0xC);
    if (temp_r0 != NULL) {
        var_r30 = temp_r0;
        var_r29 = 0U;
        while (var_r29 < (u32) M2C_FIELD(this, u32 *, 0x4C)) {
            temp_r3 = M2C_FIELD(var_r30, _GSmodel **, 0x58);
            if (temp_r3 != NULL) {
                GSmodelSetVisibility((_GSmodel*)(temp_r3), 0U);
                GSmodelFree((_GSmodel*)(M2C_FIELD(var_r30, _GSmodel **, 0x58)));
                M2C_FIELD(var_r30, _GSmodel **, 0x58) = NULL;
            }
            var_r29 += 1;
            var_r30 += 0x5C;
        }
        temp_r3_2 = M2C_FIELD(this, u8 **, 0x10);
        if (temp_r3_2 != NULL) {
            var_r29_2 = M2C_FIELD(temp_r3_2, u32 *, 0x5E4);
        } else {
            var_r29_2 = 0U;
        }
        if (temp_r3_2 != NULL) {
            var_r30_2 = M2C_FIELD(temp_r3_2, GSmaterial **, 0x5E0);
        } else {
            var_r30_2 = NULL;
        }
        var_r31 = 0U;
        while (var_r31 < var_r29_2) {
            GSmaterialSetAlpha((GSmaterial*)(var_r30_2), 1.0f);
            var_r31 += 1;
            var_r30_2 += 0x34;
        }
        GSmemFree((void*)(M2C_FIELD(this, u8 **, 0xC)));
    }
}
}

extern "C++" {
bool leafEffect::_update(float dt) {
    if (model == NULL) {
        return 0;
    }
    unk44 = unk44 + dt;
    if (unk44 >= unk48) {
        return 0;
    }
    f32 step = params[7] * (f32)(u32)(dt * (f32)GSgfxVideoGetVsyncRate());
    f32 t = unk44;
    f32 start = unk40;
    if (t < start) {
        step *= 2.0f - (t / start);
    } else {
        f32 alpha = 1.0f - ((t - start) / (unk48 - start));
        u32 i;
        GSmaterial* mat;
        u32 n;
        if (model != NULL) {
            n = M2C_FIELD(model, u32*, 0x5E4);
        } else {
            n = 0U;
        }
        if (model != NULL) {
            mat = M2C_FIELD(model, GSmaterial**, 0x5E0);
        } else {
            mat = NULL;
        }
        for (i = 0; i < n; i++, mat = (GSmaterial*)((u8*)mat + 0x34)) {
            GSmaterialSetAlpha(mat, alpha);
        }
    }
    u32 j;
    leafData* d = (leafData*)unkC;
    for (j = 0; j < (u32)unk4C; j++, d++) {
        if (d->model != NULL) {
            d->t = d->t + step;
            if (d->t >= 1.0f) {
                UpdateLeafData(d);
            }
            Vec pos;
            GSbezierCalculateVector(&pos, (GSbezier*)d, d->t);
            if (pos.y < 0.0f) {
                GSmodelSetVisibility(d->model, 0U);
                GSmodelFree(d->model);
                d->model = NULL;
            } else {
                _GSmodel* m = d->model;
                f32 scale = d->scale;
                Quaternion q;
                Mtx mtx;
                C_QUATSlerp(&d->q0, &d->q1, &q, d->t);
                PSMTXQuat(mtx, &q);
                PSMTXScaleApply(mtx, mtx, scale, scale, scale);
                PSMTXTransApply(mtx, mtx, pos.x, pos.y, pos.z);
                GSmodelSetMatrix(m, mtx);
            }
        }
    }
    return 1;
}
}

extern "C++" {
bool leafEffect::_start() {
    ModelBank *temp_r0;
    ModelBank *var_r31;
    u32 var_r30;

    if ((u32) M2C_FIELD(this, u32 *, 0x4C) > 0x20U) {
        M2C_FIELD(this, u32 *, 0x4C) = 0x20U;
    }
    if ((u32) M2C_FIELD(this, u32 *, 0x10) == 0U) {
        return 0;
    }
    M2C_FIELD(this, ModelBank **, 0xC) = GSmemAllocClr(M2C_FIELD(this, u32 *, 0x4C) * 0x5C);
    temp_r0 = M2C_FIELD(this, ModelBank **, 0xC);
    if (temp_r0 == NULL) {
        return 0;
    }
    var_r31 = temp_r0;
    var_r30 = 0U;
    M2C_FIELD(this, f32 *, 0x44) = 0.0f;
    while (var_r30 < (u32) M2C_FIELD(this, u32 *, 0x4C)) {
        ((leafEffect*)(this))->GenerateLeafData((leafData*)((leafData *) var_r31));
        var_r30 += 1;
        var_r31 += 0x5C;
    }
    return 1;
}
}

extern "C++" {
leafEffect::leafEffect(unsigned char** p0, float p1) {
    u8 *temp_r30;
    _GSmodel *temp_r3;
    HSD_Archive *temp_r29;

    M2C_FIELD(this, f32 *, 0x14) = 1.0f;
    M2C_FIELD(this, f32 *, 0x44) = 0.0f;
    M2C_FIELD(this, f32 *, 0x48) = p1;
    M2C_FIELD(this, f32 *, 0x54) = 0.0f;
    M2C_FIELD(this, f32 *, 0x58) = 0.0f;
    M2C_FIELD(this, f32 *, 0x5C) = 0.0f;
    temp_r30 = *p0;
    M2C_FIELD(this, s32 *, 0xC) = 0;
    M2C_FIELD(this, f32 *, 0x18) = (f32) M2C_FIELD(temp_r30, f32 *, 0);
    M2C_FIELD(this, f32 *, 0x1C) = (f32) M2C_FIELD(temp_r30, f32 *, 4);
    M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(temp_r30, f32 *, 8);
    M2C_FIELD(this, f32 *, 0x24) = (f32) M2C_FIELD(temp_r30, f32 *, 0xC);
    M2C_FIELD(this, f32 *, 0x28) = (f32) M2C_FIELD(temp_r30, f32 *, 0x10);
    M2C_FIELD(this, f32 *, 0x2C) = (f32) M2C_FIELD(temp_r30, f32 *, 0x14);
    M2C_FIELD(this, f32 *, 0x30) = (f32) M2C_FIELD(temp_r30, f32 *, 0x18);
    M2C_FIELD(this, f32 *, 0x34) = (f32) M2C_FIELD(temp_r30, f32 *, 0x1C);
    M2C_FIELD(this, f32 *, 0x38) = (f32) M2C_FIELD(temp_r30, f32 *, 0x20);
    M2C_FIELD(this, f32 *, 0x3C) = (f32) M2C_FIELD(temp_r30, f32 *, 0x24);
    M2C_FIELD(this, s32 *, 0x4C) = (s32) (u16) M2C_FIELD(temp_r30, s32 *, 0x28);
    M2C_FIELD(this, f32 *, 0x40) = (f32) M2C_FIELD(temp_r30, f32 *, 0x2C);
    *p0 += 0x40;
    *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
    M2C_FIELD(this, s32 *, 0x50) = 0;
    temp_r29 = M2C_FIELD(temp_r30, HSD_Archive **, 0x38);
    if (temp_r29 != NULL) {
        M2C_FIELD(this, s32 *, 0x50) = wazaSequenceSysGetResID();
        loadModel((HSD_Archive*)(temp_r29), 0x4E20U, 0U, (u32) M2C_FIELD(this, s32 *, 0x50));
        GSresIsUniqueID(0x4E20U, (u32) M2C_FIELD(this, s32 *, 0x50), 0U);
        M2C_FIELD(this, _GSmodel **, 0x10) = (_GSmodel *)(GSresGetResource(0x4E20U, (u32) M2C_FIELD(this, s32 *, 0x50)));
        temp_r3 = M2C_FIELD(this, _GSmodel **, 0x10);
        if (temp_r3 != NULL) {
            GSmodelSetVisibility((_GSmodel*)(temp_r3), 0U);
        }
    }
    *p0 = &(*p0)[(M2C_FIELD(temp_r30, s32 *, 0x34) + 0x1F) & 0xFFFFFFE0];
    return;
}
}

extern "C++" {
void leafEffect::UpdateLeafData(leafData* leaf) {
    Vec axis;
    Vec* v;

    leaf->t -= 1.0f;
    leaf->q0 = leaf->q1;
    {
        f32 theta = 6.2831855f * HSD_Randf();
        f32 phi = 3.1415927f * HSD_Randf();
        f32 sinPhi = sin(phi);
        f32 sinTheta = sin(theta);
        f32 cosPhi = cos(phi);
        f32 cosTheta = cos(theta);
        axis.y = cosPhi;
        axis.x = sinPhi * cosTheta;
        axis.z = sinPhi * sinTheta;
        C_QUATRotAxisRad(&leaf->q1, &axis, 6.2831855f * HSD_Randf());
    }

    v = &leaf->p2;
    leaf->p0 = leaf->p1;
    leaf->p2 = leaf->p3;
    PSVECSubtract(v, &leaf->p1, v);
    PSVECNormalize(v, v);
    f32 len = params[5] * (2.0f * HSD_Randf() - 1.0f) + params[4];
    len *= leaf->scale;
    PSVECScale(v, v, -len);
    PSVECAdd(v, &leaf->p0, v);

    v = &leaf->p1;
    {
        f32 theta = 6.2831855f * HSD_Randf();
        f32 phi = 3.1415927f * HSD_Randf();
        f32 sinPhi = sin(phi);
        f32 len = params[3] * (2.0f * HSD_Randf() - 1.0f) + params[2];
        len *= leaf->scale;
        f32 sinTheta = sin(theta);
        f32 cosPhi = cos(phi);
        v->x = sinPhi * (f32)cos(theta);
        v->y = cosPhi;
        v->z = sinPhi * sinTheta;
        PSVECScale(v, v, len);
        v->y += params[6];
        PSVECAdd(v, &leaf->p0, v);
    }

    v = &leaf->p3;
    {
        f32 theta = 6.2831855f * HSD_Randf();
        f32 phi = 3.1415927f * HSD_Randf();
        f32 sinPhi = sin(phi);
        f32 len = params[5] * (2.0f * HSD_Randf() - 1.0f) + params[4];
        len *= leaf->scale;
        f32 sinTheta = sin(theta);
        f32 cosPhi = cos(phi);
        v->x = sinPhi * (f32)cos(theta);
        v->y = cosPhi;
        v->z = sinPhi * sinTheta;
        PSVECScale(v, v, len);
        PSVECAdd(v, &leaf->p1, v);
    }
}
}

extern "C++" {
s32 leafEffect::GenerateLeafData(leafData* leaf) {
    Mtx m;
    Vec axisA;
    Vec axisB;
    Vec* v;
    _GSmodel* clone;
    f32 scale;

    leaf->model = GSmodelClone(model);
    clone = leaf->model;
    if (clone == NULL) {
        GSlogWrite("_leaffxGenerateLeafData: Could not create leaf clone model.\n");
        return 0;
    }
    GSmodelSetVisibility(clone, 1U);
    leaf->scale = params[1] * (2.0f * HSD_Randf() - 1.0f) + params[0];
    leaf->scale = leaf->scale * unk14;
    leaf->t = 0.0f;

    {
        f32 theta = 6.2831855f * HSD_Randf();
        f32 phi = 3.1415927f * HSD_Randf();
        f32 sinPhi = sin(phi);
        f32 sinTheta = sin(theta);
        f32 cosPhi = cos(phi);
        f32 cosTheta = cos(theta);
        axisA.y = cosPhi;
        axisA.x = sinPhi * cosTheta;
        axisA.z = sinPhi * sinTheta;
        C_QUATRotAxisRad(&leaf->q0, &axisA, 6.2831855f * HSD_Randf());
    }

    {
        f32 theta = 6.2831855f * HSD_Randf();
        f32 phi = 3.1415927f * HSD_Randf();
        f32 sinPhi = sin(phi);
        f32 sinTheta = sin(theta);
        f32 cosPhi = cos(phi);
        f32 cosTheta = cos(theta);
        axisB.y = cosPhi;
        axisB.x = sinPhi * cosTheta;
        axisB.z = sinPhi * sinTheta;
        C_QUATRotAxisRad(&leaf->q1, &axisB, 6.2831855f * HSD_Randf());
    }

    v = &leaf->p2;
    leaf->p0.x = unk54;
    leaf->p0.y = unk58;
    leaf->p0.z = unk5C;
    f32 len = params[5] * (2.0f * HSD_Randf() - 1.0f) + params[4];
    len *= leaf->scale;
    {
        f32 theta = 6.2831855f * HSD_Randf();
        f32 phi = 3.1415927f * HSD_Randf();
        f32 sinPhi = sin(phi);
        f32 sinTheta = sin(theta);
        f32 cosPhi = cos(phi);
        v->x = sinPhi * (f32)cos(theta);
        v->y = cosPhi;
        v->z = sinPhi * sinTheta;
        PSVECScale(v, v, len);
        PSVECAdd(v, (Vec*)&unk54, v);
    }

    v = &leaf->p1;
    {
        f32 theta = 6.2831855f * HSD_Randf();
        f32 phi = 1.5707964f * HSD_Randf();
        f32 sinPhi = sin(phi);
        f32 len = leaf->scale * (params[9] * (2.0f * HSD_Randf() - 1.0f) + params[8]) * (params[3] * (2.0f * HSD_Randf() - 1.0f) + params[2]);
        f32 sinTheta = sin(theta);
        f32 cosPhi = cos(phi);
        v->x = sinPhi * (f32)cos(theta);
        v->y = cosPhi;
        v->z = sinPhi * sinTheta;
        PSVECScale(v, v, len);
        PSVECAdd(v, (Vec*)&unk54, v);
    }

    v = &leaf->p3;
    {
        f32 theta = 6.2831855f * HSD_Randf();
        f32 phi = 3.1415927f * HSD_Randf();
        f32 sinPhi = sin(phi);
        f32 len = params[5] * (2.0f * HSD_Randf() - 1.0f) + params[4];
        len *= leaf->scale;
        f32 sinTheta = sin(theta);
        f32 cosPhi = cos(phi);
        v->x = sinPhi * (f32)cos(theta);
        v->y = cosPhi;
        v->z = sinPhi * sinTheta;
        PSVECScale(v, v, len);
        PSVECAdd(v, &leaf->p1, v);
    }

    PSMTXQuat(m, &leaf->q0);
    scale = leaf->scale;
    PSMTXScaleApply(m, m, scale, scale, scale);
    PSMTXTransApply(m, m, unk54, unk58, unk5C);
    GSmodelSetMatrix(leaf->model, m);
    return 1;
}
}
