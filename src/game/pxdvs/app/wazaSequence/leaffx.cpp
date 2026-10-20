// Not yet decompiled.
#include <dolphin/types.h>
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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
enum Mtx { Mtx_draft_dummy };
struct Quaternion;
struct Vec;
struct _GSmodel;
struct leafData;
class leafEffect;

extern "C++" {
// ---- draft declarations ----
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
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
};
struct _GSmodel {
    u8 _draft[1];
};
struct leafData {
    u8 _draft[1];
};
class leafEffect : public GSeffect {
public:
    s32 unkC;            // 0x0c
    _GSmodel* model;     // 0x10
    f32 unk14;           // 0x14
    f32 params[10];      // 0x18
    f32 unk40;           // 0x40
    f32 unk44;           // 0x44
    f32 unk48;           // 0x48
    s32 unk4C;           // 0x4c
    u32 resID;           // 0x50
    f32 unk54;           // 0x54
    f32 unk58;           // 0x58
    f32 unk5C;           // 0x5c

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
bool leafEffect::_update(float p0) {
    u32 sp20;
    volatile f32 v18[2];
    f32 unksp8;
    s32 sp24;
    GSmaterial *var_r30;
    _GSmodel *temp_r31;
    f32 temp_f2;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f3;
    f32 var_f31;
    leafData *var_r30_2;
    u32 var_r29;
    u32 var_r29_2;
    u32 var_r31;
    u8 *temp_r3;

    if ((u8 *) M2C_FIELD(this, u8 **, 0x10) == NULL) {
        return 0;
    }
    M2C_FIELD(this, f32 *, 0x44) = (f32) (M2C_FIELD(this, f32 *, 0x44) + p0);
    M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
    if (M2C_FIELD(this, f32 *, 0x44) == M2C_FIELD(this, f32 *, 0x48)) {
        return 0;
    }
    var_f31 = M2C_FIELD(this, f32 *, 0x34) * (f32) (u32) (p0 * (f32) GSgfxVideoGetVsyncRate());
    temp_f3 = M2C_FIELD(this, f32 *, 0x44);
    temp_f2 = M2C_FIELD(this, f32 *, 0x40);
    if (temp_f3 < temp_f2) {
        var_f31 *= 2.0f - (temp_f3 / temp_f2);
    } else {
        temp_r3 = M2C_FIELD(this, u8 **, 0x10);
        temp_f30 = 1.0f - ((temp_f3 - temp_f2) / (M2C_FIELD(this, f32 *, 0x48) - temp_f2));
        if (temp_r3 != NULL) {
            var_r29 = M2C_FIELD(temp_r3, u32 *, 0x5E4);
        } else {
            var_r29 = 0U;
        }
        if (temp_r3 != NULL) {
            var_r30 = M2C_FIELD(temp_r3, GSmaterial **, 0x5E0);
        } else {
            var_r30 = NULL;
        }
        var_r31 = 0U;
        while (var_r31 < var_r29) {
            GSmaterialSetAlpha((GSmaterial*)(var_r30), temp_f30);
            var_r31 += 1;
            var_r30 += 0x34;
        }
    }
    var_r30_2 = M2C_FIELD(this, leafData **, 0xC);
    var_r29_2 = 0U;
    while (var_r29_2 < (u32) M2C_FIELD(this, u32 *, 0x4C)) {
        if ((_GSmodel *) M2C_FIELD(var_r30_2, _GSmodel **, 0x58) != NULL) {
            M2C_FIELD(var_r30_2, f32 *, 0x54) = (f32) (M2C_FIELD(var_r30_2, f32 *, 0x54) + var_f31);
            M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
            if (M2C_FIELD(var_r30_2, f32 *, 0x54) == 1.0f) {
                ((leafEffect*)(this))->UpdateLeafData((leafData*)(var_r30_2));
            }
            GSbezierCalculateVector((Vec*)(v18), (GSbezier*)((GSbezier *) var_r30_2), M2C_FIELD(var_r30_2, f32 *, 0x54));
            if (v18[1] < 0.0f) {
                GSmodelSetVisibility((_GSmodel*)(M2C_FIELD(var_r30_2, _GSmodel **, 0x58)), 0U);
                GSmodelFree((_GSmodel*)(M2C_FIELD(var_r30_2, _GSmodel **, 0x58)));
                M2C_FIELD(var_r30_2, _GSmodel **, 0x58) = NULL;
            } else {
                temp_r31 = M2C_FIELD(var_r30_2, _GSmodel **, 0x58);
                temp_f30_2 = M2C_FIELD(var_r30_2, f32 *, 0x50);
                C_QUATSlerp((const Quaternion*)(((u8*)(var_r30_2) + 0x30)), (const Quaternion*)(((u8*)(var_r30_2) + 0x40)), (Quaternion*)(&unksp8), M2C_FIELD(var_r30_2, f32 *, 0x54));
                PSMTXQuat((Mtx)((s32) &sp24), (const Quaternion *)((const register Quaternion*)(&unksp8)));
                PSMTXScaleApply((const Mtx)((s32) &sp24), (Mtx)((s32) &sp24), (float)(temp_f30_2), (float)(temp_f30_2), (float)(temp_f30_2));
                PSMTXTransApply((const Mtx)((s32) &sp24), (Mtx)((s32) &sp24), (float)(v18[0]), (float)(v18[1]), (float)(sp20));
                GSmodelSetMatrix((_GSmodel*)(temp_r31), (Mtx)((s32) &sp24));
            }
        }
        var_r29_2 += 1;
        var_r30_2 += 0x5C;
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
void leafEffect::UpdateLeafData(leafData* p0) {
    volatile f32 sp10;
    volatile f32 spC;
    f32 sp8;
    Vec *temp_r31;
    Vec *temp_r31_2;
    Vec *temp_r31_3;
    f32 temp_f1;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f30_2;
    f32 temp_f28_2;
    f32 temp_f28_3;
    f32 temp_f29;
    f32 temp_f29_2;
    f32 temp_f29_3;
    f32 temp_f30;
    f32 temp_f28;
    f32 temp_f30_3;
    f32 temp_f30_4;
    f32 temp_f30_5;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;

    M2C_FIELD(p0, f32 *, 0x54) = (f32) (M2C_FIELD(p0, f32 *, 0x54) - 1.0f);
    M2C_FIELD(p0, f32 *, 0x30) = (f32) M2C_FIELD((s32)p0, f32 *, 0x40);
    M2C_FIELD(p0, f32 *, 0x34) = (f32) M2C_FIELD(p0, f32 *, 0x44);
    M2C_FIELD(p0, f32 *, 0x38) = (f32) M2C_FIELD(p0, f32 *, 0x48);
    M2C_FIELD(p0, f32 *, 0x3C) = (f32) M2C_FIELD(p0, f32 *, 0x4C);
    temp_f30 = 6.2831855f * HSD_Randf();
    temp_f31 = 3.1415927f * HSD_Randf();
    temp_f29 = (f32) sin((f64) temp_f31);
    temp_f28 = (f32) sin((f64) temp_f30);
    temp_f31_2 = (f32) cos((f64) temp_f31);
    temp_f1 = (f32) cos((f64) temp_f30);
    spC = temp_f31_2;
    sp10 = temp_f29 * temp_f28;
    sp8 = temp_f29 * temp_f1;
    C_QUATRotAxisRad((Quaternion*)(((u8*)(p0) + 0x40)), (const Vec*)((Vec *) &sp8), 6.2831855f * HSD_Randf());
    temp_r31 = (Vec *)(((u8*)((u16)p0) + 0x18));
    M2C_FIELD(p0, f32 *, 0) = (f32) M2C_FIELD(p0, f32 *, 0xC);
    M2C_FIELD(p0, f32 *, 4) = (f32) M2C_FIELD(p0, f32 *, 0x10);
    M2C_FIELD(p0, f32 *, 8) = (f32) M2C_FIELD(p0, f32 *, 0x14);
    M2C_FIELD(p0, f32 *, 0x18) = (f32) M2C_FIELD((s32)p0, f32 *, 0x24);
    M2C_FIELD(p0, f32 *, 0x1C) = (f32) M2C_FIELD(p0, f32 *, 0x28);
    M2C_FIELD(p0, f32 *, 0x20) = (f32) M2C_FIELD(p0, f32 *, 0x2C);
    PSVECSubtract((const register Vec*)(temp_r31), (const register Vec*)(((u8*)((u16)p0) + 0xC)), (register Vec*)(temp_r31));
    PSVECNormalize((const register Vec*)(temp_r31), (register Vec*)(temp_r31));
    PSVECScale((const register Vec*)(temp_r31), (register Vec*)(temp_r31), -(((M2C_FIELD(this, f32 *, 0x2C) * ((2.0f * HSD_Randf()) - 1.0f)) + M2C_FIELD(this, f32 *, 0x28)) * M2C_FIELD(p0, f32 *, 0x50)));
    PSVECAdd((const register Vec*)(temp_r31), (const register Vec*)((Vec *) p0), (register Vec*)(temp_r31));
    temp_r31_2 = (Vec *)(((u8*)(p0) + 0xC));
    temp_f27 = 6.2831855f * HSD_Randf();
    temp_f30_2 = 3.1415927f * HSD_Randf();
    temp_f28_2 = (f32) sin((f64) temp_f30_2);
    temp_f31_3 = ((M2C_FIELD(this, f32 *, 0x24) * ((2.0f * HSD_Randf()) - 1.0f)) + M2C_FIELD(this, f32 *, 0x20)) * M2C_FIELD(p0, f32 *, 0x50);
    temp_f29_2 = (f32) sin((f64) temp_f27);
    temp_f30_3 = (f32) cos((f64) temp_f30_2);
    M2C_FIELD(p0, f32 *, 0xC) = (f32) (temp_f28_2 * (f32) cos((f64) temp_f27));
    M2C_FIELD(temp_r31_2, f32 *, 4) = temp_f30_3;
    M2C_FIELD(temp_r31_2, f32 *, 8) = (f32) (temp_f28_2 * temp_f29_2);
    PSVECScale((const register Vec*)(temp_r31_2), (register Vec*)(temp_r31_2), temp_f31_3);
    M2C_FIELD(temp_r31_2, f32 *, 4) = (f32) (M2C_FIELD(temp_r31_2, f32 *, 4) + M2C_FIELD(this, f32 *, 0x30));
    PSVECAdd((const register Vec*)(temp_r31_2), (const register Vec*)((Vec *) p0), (register Vec*)(temp_r31_2));
    temp_r31_3 = (Vec *)(((u8*)(p0) + 0x24));
    temp_f27_2 = 6.2831855f * HSD_Randf();
    temp_f30_4 = 3.1415927f * HSD_Randf();
    temp_f28_3 = (f32) sin((f64) temp_f30_4);
    temp_f31_4 = ((M2C_FIELD(this, f32 *, 0x2C) * ((2.0f * HSD_Randf()) - 1.0f)) + M2C_FIELD(this, f32 *, 0x28)) * M2C_FIELD(p0, f32 *, 0x50);
    temp_f29_3 = (f32) sin((f64) temp_f27_2);
    temp_f30_5 = (f32) cos((f64) temp_f30_4);
    M2C_FIELD(p0, f32 *, 0x24) = (f32) (temp_f28_3 * (f32) cos((f64) temp_f27_2));
    M2C_FIELD(temp_r31_3, f32 *, 4) = temp_f30_5;
    M2C_FIELD(temp_r31_3, f32 *, 8) = (f32) (temp_f28_3 * temp_f29_3);
    PSVECScale((const register Vec*)(temp_r31_3), (register Vec*)(temp_r31_3), temp_f31_4);
    PSVECAdd((const register Vec*)(temp_r31_3), (const register Vec*)(((u8*)(p0) + 0xC)), (register Vec*)(temp_r31_3));
}
}

extern "C++" {
s32 leafEffect::GenerateLeafData(leafData* p0) {
    volatile s32 sp20;
    volatile f32 sp1C;
    volatile f32 sp18;
    f32 sp14;
    volatile f32 sp10;
    volatile f32 spC;
    f32 sp8;
    Vec *temp_r31;
    Vec *temp_r31_2;
    Vec *temp_r31_3;
    _GSmodel *temp_r3;
    _GSmodel *temp_ret;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f27_3;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f28_3;
    f32 temp_f28_4;
    f32 temp_f28_5;
    f32 temp_f29;
    f32 temp_f29_2;
    f32 temp_f29_3;
    f32 temp_f29_4;
    f32 temp_f29_5;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f30_4;
    f32 temp_f30_5;
    f32 temp_f30_6;
    f32 temp_f30_7;
    f32 temp_f30_8;
    f32 temp_f30_9;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 temp_f31_6;
    f32 temp_f31_7;

    temp_ret = GSmodelClone((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x10)));
    M2C_FIELD(p0, _GSmodel **, 0x58) = temp_ret;
    temp_r3 = M2C_FIELD(p0, _GSmodel **, 0x58);
    if (temp_r3 == NULL) {
        GSlogWrite((const char*)("_leaffxGenerateLeafData: Could not create leaf clone model.\n"), (u32) (u64) temp_ret, M2C_BITWISE(f32, temp_ret));
        return 0;
    }
    GSmodelSetVisibility((_GSmodel*)(temp_r3), 1U);
    M2C_FIELD(p0, f32 *, 0x50) = (f32) ((M2C_FIELD(this, f32 *, 0x1C) * ((2.0f * HSD_Randf()) - 1.0f)) + M2C_FIELD(this, f32 *, 0x18));
    M2C_FIELD(p0, f32 *, 0x50) = (f32) (M2C_FIELD(p0, f32 *, 0x50) * M2C_FIELD(this, f32 *, 0x14));
    M2C_FIELD(p0, f32 *, 0x54) = 0.0f;
    temp_f30 = 6.2831855f * HSD_Randf();
    temp_f31 = 3.1415927f * HSD_Randf();
    temp_f29 = (f32) sin((f64) temp_f31);
    temp_f28 = (f32) sin((f64) temp_f30);
    temp_f31_2 = (f32) cos((f64) temp_f31);
    temp_f1 = (f32) cos((f64) temp_f30);
    sp18 = temp_f31_2;
    sp1C = temp_f29 * temp_f28;
    sp14 = temp_f29 * temp_f1;
    C_QUATRotAxisRad((Quaternion*)(((u8*)((s32)p0) + 0x30)), (const Vec*)((Vec *) &sp14), 6.2831855f * HSD_Randf());
    temp_f31_3 = 6.2831855f * HSD_Randf();
    temp_f30_2 = 3.1415927f * HSD_Randf();
    temp_f28_2 = (f32) sin((f64) temp_f30_2);
    temp_f29_2 = (f32) sin((f64) temp_f31_3);
    temp_f30_3 = (f32) cos((f64) temp_f30_2);
    temp_f1_2 = (f32) cos((f64) temp_f31_3);
    spC = temp_f30_3;
    sp10 = temp_f28_2 * temp_f29_2;
    sp8 = temp_f28_2 * temp_f1_2;
    C_QUATRotAxisRad((Quaternion*)(((u8*)(p0) + 0x40)), (const Vec*)((Vec *) &sp8), 6.2831855f * HSD_Randf());
    temp_r31 = (Vec *)(((u8*)(p0) + 0x18));
    M2C_FIELD(p0, f32 *, 0) = (f32) M2C_FIELD(this, f32 *, 0x54);
    M2C_FIELD(p0, f32 *, 4) = (f32) M2C_FIELD(this, f32 *, 0x58);
    M2C_FIELD(p0, f32 *, 8) = (f32) M2C_FIELD(this, f32 *, 0x5C);
    temp_f31_4 = ((M2C_FIELD(this, f32 *, 0x2C) * ((2.0f * HSD_Randf()) - 1.0f)) + M2C_FIELD(this, f32 *, 0x28)) * M2C_FIELD(p0, f32 *, 0x50);
    temp_f27 = 6.2831855f * HSD_Randf();
    temp_f30_4 = 3.1415927f * HSD_Randf();
    temp_f28_3 = (f32) sin((f64) temp_f30_4);
    temp_f29_3 = (f32) sin((f64) temp_f27);
    temp_f30_5 = (f32) cos((f64) temp_f30_4);
    M2C_FIELD(p0, f32 *, 0x18) = (f32) (temp_f28_3 * (f32) cos((f64) temp_f27));
    M2C_FIELD(temp_r31, f32 *, 4) = temp_f30_5;
    M2C_FIELD(temp_r31, f32 *, 8) = (f32) (temp_f28_3 * temp_f29_3);
    PSVECScale((const register Vec*)(temp_r31), (register Vec*)(temp_r31), temp_f31_4);
    PSVECAdd((const register Vec*)(temp_r31), (const register Vec*)(this + 0x54), (register Vec*)(temp_r31));
    temp_r31_2 = (Vec *)(((u8*)(p0) + 0xC));
    temp_f27_2 = 6.2831855f * HSD_Randf();
    temp_f30_6 = 1.5707964f * HSD_Randf();
    temp_f28_4 = (f32) sin((f64) temp_f30_6);
    temp_f31_6 = ((M2C_FIELD(this, f32 *, 0x24) * ((2.0f * HSD_Randf()) - 1.0f)) + M2C_FIELD(this, f32 *, 0x20)) * ((M2C_FIELD(this, f32 *, 0x3C) * ((2.0f * HSD_Randf()) - 1.0f)) + M2C_FIELD(this, f32 *, 0x38)) * M2C_FIELD(p0, f32 *, 0x50);
    temp_f29_4 = (f32) sin((f64) temp_f27_2);
    temp_f30_7 = (f32) cos((f64) temp_f30_6);
    M2C_FIELD(p0, f32 *, 0xC) = (f32) (temp_f28_4 * (f32) cos((f64) temp_f27_2));
    M2C_FIELD(temp_r31_2, f32 *, 4) = temp_f30_7;
    M2C_FIELD(temp_r31_2, f32 *, 8) = (f32) (temp_f28_4 * temp_f29_4);
    PSVECScale((const register Vec*)(temp_r31_2), (register Vec*)(temp_r31_2), temp_f31_6);
    PSVECAdd((const register Vec*)(temp_r31_2), (const register Vec*)(this + 0x54), (register Vec*)(temp_r31_2));
    temp_r31_3 = (Vec *)(((u8*)(p0) + 0x24));
    temp_f27_3 = 6.2831855f * HSD_Randf();
    temp_f30_8 = 3.1415927f * HSD_Randf();
    temp_f28_5 = (f32) sin((f64) temp_f30_8);
    temp_f31_7 = ((M2C_FIELD(this, f32 *, 0x2C) * ((2.0f * HSD_Randf()) - 1.0f)) + M2C_FIELD(this, f32 *, 0x28)) * M2C_FIELD(p0, f32 *, 0x50);
    temp_f29_5 = (f32) sin((f64) temp_f27_3);
    temp_f30_9 = (f32) cos((f64) temp_f30_8);
    M2C_FIELD(p0, f32 *, 0x24) = (f32) (temp_f28_5 * (f32) cos((f64) temp_f27_3));
    M2C_FIELD(temp_r31_3, f32 *, 4) = temp_f30_9;
    M2C_FIELD(temp_r31_3, f32 *, 8) = (f32) (temp_f28_5 * temp_f29_5);
    PSVECScale((const register Vec*)(temp_r31_3), (register Vec*)(temp_r31_3), temp_f31_7);
    PSVECAdd((const register Vec*)(temp_r31_3), (const register Vec*)(((u8*)((s32)p0) + 0xC)), (register Vec*)(temp_r31_3));
    PSMTXQuat((Mtx)((s32) &sp20), (const Quaternion *)((const register Quaternion*)(((u8*)(p0) + 0x30))));
    temp_f1_3 = M2C_FIELD(p0, f32 *, 0x50);
    PSMTXScaleApply((const Mtx)((s32) &sp20), (Mtx)((s32) &sp20), (float)(temp_f1_3), (float)(temp_f1_3), (float)(temp_f1_3));
    PSMTXTransApply((const Mtx)((s32) &sp20), (Mtx)((s32) &sp20), (float)(M2C_FIELD(this, f32 *, 0x54)), (float)(M2C_FIELD(this, f32 *, 0x58)), (float)(M2C_FIELD(this, f32 *, 0x5C)));
    GSmodelSetMatrix((_GSmodel*)(M2C_FIELD(p0, _GSmodel **, 0x58)), (Mtx)((s32) &sp20));
    return 1;
}
}
