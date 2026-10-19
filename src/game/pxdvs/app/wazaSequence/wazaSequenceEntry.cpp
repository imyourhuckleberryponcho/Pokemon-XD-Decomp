// Partial: only the empty / trivial entry methods are written so far.
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
struct CameraEntry;
struct EffectEntry;
struct EventEntry;
struct GSbound;
struct GScamera;
struct GSeffect;
struct GSlight;
struct GSpart;
struct GSparticleBank;
struct GSparticleGenerator;
struct GSthread;
struct GSvec;
struct HSD_Archive;
struct LensFlareEntry;
struct MainSequenceEntry;
struct ModelEntry;
struct ModelSequence;
struct ParticleEntry;
struct SVec;
struct SequenceEntry;
struct SndEmitter;
struct SoundEntry;
struct Vec;
struct WazaSequence;
struct _GScamera;
struct _GSmodel;
struct billboardEffect;
enum enumNullJointName { enumNullJointName_draft_dummy };
enum enumSequenceEntryDataType { enumSequenceEntryDataType_draft_dummy };
struct leafEffect;

struct _GScamera;

class EventEntry {
public:
    bool Update(f32 time);
public: // draft
    static s32 Load(unsigned char**);
    s32 Start();
    ~EventEntry();
    static void Unload(unsigned char**);
    EventEntry(WazaSequence*, unsigned char**);
};

class SequenceEntry {
public:
    void End();
    void SetRenderCamera(_GScamera* camera);
public: // draft
    ~SequenceEntry();
    SequenceEntry(enumSequenceEntryDataType, WazaSequence*, unsigned char**);
    s32 Update(float);
    void Link();
    void Stop(bool);
    s32 Start();
};

// ---- draft declarations ----
struct CameraEntry {
    u8 _draft[1];
    void Stop(bool);
    ~CameraEntry();
    CameraEntry(WazaSequence*, unsigned char**);
    static void Unload(unsigned char**);
    s32 Update(float);
    static s32 Load(unsigned char**);
    s32 Start();
};
struct EffectEntry {
    u8 _draft[1];
    void blurEffectLoad(unsigned char**);
    ~EffectEntry();
    void End();
    void boneFillEffectLoad(unsigned char**);
    void envMapEffectLoad(unsigned char**);
    s32 Update(float);
    s32 Start();
    void filterEffectLoad(unsigned char**);
    void Stop(bool);
    static s32 Load(unsigned char**);
    EffectEntry(WazaSequence*, unsigned char**);
    static void Unload(unsigned char**);
};
struct GSbound {
    u8 _draft[1];
};
struct GScamera {
    u8 _draft[1];
};
struct GSeffect {
    u8 _draft[1];
    bool Start();
    void Stop();
};
struct GSlight {
    u8 _draft[1];
};
struct GSpart {
    u8 _draft[1];
};
struct GSparticleBank {
    u8 _draft[1];
};
struct GSparticleGenerator {
    u8 _draft[1];
};
struct GSthread {
    u8 _draft[1];
};
struct GSvec {
    u8 _draft[1];
};
struct HSD_Archive {
    u8 _draft[1];
};
struct LensFlareEntry {
    u8 _draft[1];
    LensFlareEntry(WazaSequence*, unsigned char**);
    s32 Start();
    static void Stop(bool);
    static void Unload(unsigned char**);
    static s32 Load(unsigned char**);
    ~LensFlareEntry();
    s32 Update(float);
};
struct MainSequenceEntry {
    u8 _draft[1];
    ~MainSequenceEntry();
    MainSequenceEntry(WazaSequence*, unsigned char**);
};
struct ModelEntry {
    u8 _draft[1];
    ModelEntry(WazaSequence*, unsigned char**);
    ~ModelEntry();
    s32 Update(float);
    static void SetRenderCamera(_GScamera*);
    static s32 Load(unsigned char**);
    void Stop(bool);
    static void Unload(unsigned char**);
    s32 Start();
};
struct ModelSequence {
    u8 _draft[1];
    void ResetRotation();
    f32 GetModelScale(bool) const;
    void Fly(bool);
    void WakeUp();
    void UnFreeze();
    void ResetPosition();
    void Land();
    GSpart* GetPart(enumNullJointName);
    void Sleep();
    void Freeze();
    void ResetScale();
};
struct ParticleEntry {
    u8 _draft[1];
    s32 Start();
    void End();
    void Stop(bool);
    static void SetRenderCamera(_GScamera*);
    static s32 Load(unsigned char**);
    s32 Update(float);
    ParticleEntry(WazaSequence*, unsigned char**);
    static void Unload(unsigned char**);
    ~ParticleEntry();
};
struct SVec {
    u8 _draft[1];
};
struct SndEmitter {
    u8 _draft[1];
};
struct SoundEntry {
    u8 _draft[1];
    s32 Start();
    void Stop(bool);
    static s32 Load(unsigned char**);
    s32 Update(float);
    ~SoundEntry();
    SoundEntry(WazaSequence*, unsigned char**);
    static void Unload(unsigned char**);
};
struct Vec {
    u8 _draft[1];
};
struct WazaSequence {
    u8 _draft[1];
    void* GetEntryFromID(unsigned char);
};
struct _GSmodel {
    u8 _draft[1];
};
struct billboardEffect {
    u8 _draft[1];
    billboardEffect(unsigned char**);
};
struct leafEffect {
    u8 _draft[1];
    leafEffect(unsigned char**, float);
};

extern "C" {
s32 GSboundGetLocalPosition(s32, f32*);
s32 GSboundGetWorldPosition(f32*);
u8 GSgfxVideoGetVsyncRate(void);
void GSlensFlareFree(u32 id);
u32 GSlensFlareLoad(u8* data);
void GSlensFlareSetSunPosition(u32 id, Vec* pos);
void GSlensFlareSetVisible(u32 id, bool visible);
void GSlogWrite(const char*, ...);
void GSmodelAddNull(_GSmodel* model, Vec* position, Vec* rotation, Vec* scale);
void GSmodelAttachToGSpart(_GSmodel* model, GSpart* part, s32 mode, u8 inherit, u8 identity);
u32 GSmodelCanAnimate(_GSmodel* model);
u32 GSmodelCanTexAnimate(_GSmodel* model);
void GSmodelDetachFromGSpart(_GSmodel* model, u8 restore);
void GSmodelForceAnimTransformUpdate(_GSmodel* model);
GSbound* GSmodelGetBound(_GSmodel* model);
void GSmodelGetFrameCount(_GSmodel* model, f32* count, f32* blendCount);
GSpart* GSmodelGetPart(_GSmodel* model, s32 index);
void GSmodelGetPosition(_GSmodel* model, GSvec* position);
void GSmodelGetRotation(_GSmodel* model, GSvec* rotation);
u32 GSmodelHasAnimationEnded(_GSmodel* model);
u32 GSmodelHasTexAnimationEnded(_GSmodel* model);
u32 GSmodelIsAnimating(_GSmodel* model);
void GSmodelRemoveNull(_GSmodel* model);
void GSmodelSet60fpsAnimFlag(_GSmodel* model, u8 enable);
void GSmodelSetAnimFrame(_GSmodel* model, f32 frame);
void GSmodelSetAnimIndex(_GSmodel* model, u32 index);
void GSmodelSetAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetAnimType(_GSmodel* model, s32 type);
void GSmodelSetBoundCheck(_GSmodel* model, u8 enable);
void GSmodelSetPosition(_GSmodel* model, GSvec* position);
void GSmodelSetRenderCamera(_GSmodel* model, GScamera* camera);
void GSmodelSetRenderLayer(_GSmodel* model, s32 count, s32* layers);
void GSmodelSetRotation(_GSmodel* model, GSvec* rotation);
void GSmodelSetScale(_GSmodel* model, GSvec* scale);
void GSmodelSetShadowFlags(_GSmodel* model, u32 flags);
void GSmodelSetShadowLight(_GSmodel* model, GSlight* light);
void GSmodelSetShadowSurface(_GSmodel* model, s32 count, void* surfaces);
void GSmodelSetTexAnimFrame(_GSmodel* model, f32 frame);
void GSmodelSetTexAnimIndex(_GSmodel* model, u32 index);
void GSmodelSetTexAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetTexAnimType(_GSmodel* model, s32 type);
void GSmodelSetVisibility(_GSmodel* model, u8 visible);
void GSmodelStartAnimation(_GSmodel* model);
void GSmodelStartTexAnimation(_GSmodel* model);
void GSmodelStopAnimation(_GSmodel* model);
void GSmodelStopTexAnimation(_GSmodel* model);
void GSpartFree(GSpart* part);
void GSpartGetTransform(GSpart* part, GSvec* pos, GSvec* rot, GSvec* scale);
s32 GSparticleAttachGeneratorToGSpart(u32, f32*, s32, s32, s32, s32);
s32 GSparticleBankSetCamera();
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* bank, s32 index, s32);
void GSparticleDestroyAllGenerators(GSparticleBank* bank, s32 children);
s32 GSparticleDestroyGenerator(s32);
void GSparticleFree(GSparticleBank* bank);
u8 GSparticleIsGeneratorAlive(u32);
s32 GSparticleLoad(void*);
void GSparticleSetGeneratorPosition(GSparticleGenerator* gen, Vec* pos);
s32 GSparticleSetGeneratorRotation(u32, f32*);
s32 GSparticleSetGeneratorScale(u32, f32*, s32, s32);
s32 GSparticleSetNodeScaling(u32, s32);
s32 GSparticleSetOffsetRotationInLocal(s32, s32);
s32 GSparticleSetParticleTextureScaling(u32, s32);
s32 GSparticleSetRandomVelocityScaling(u32, s32);
s32 GSparticleSetTornadoScaling(u32, s32, s32);
s32 GSparticleSetVelocityRotationInLocal(u32, s32);
void GSparticleStopGenerator(void* generator);
void GSresFreeResource(u32 grp, u32 id);
void* GSresGetResource(u32 grp, u32 id);
void GSresIsUniqueID(u32 grp, u32 id, u8 unique);
u32 GSsndCheckEmitter(SndEmitter* e);
u8 GSsndClose(u32 id);
SndEmitter* GSsndCreateEmitterParam(u32 id, SVec* pos, SVec* dir, f32 maxDis, f32 comp, u8 maxVol, u8 minVol);
u8 GSsndFreeEmitter(SndEmitter* e);
s32 GSsndGetStatus(u32 id);
u8 GSsndPlay(u32 id, s32 time, u32 flag);
u8 GSsndUpdateEmitter(SndEmitter* e, SVec* pos);
void* GSthreadCreate(s32, s32, s32, s32, s32, void (*)(void));
u8 GSthreadIsRunning(GSthread*);
void GSthreadSetArgs(void*, s32, ...);
s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, u32 file_size);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
void battleGridGetNormalisedScale(GSvec* scale);
void cameraSetOffsetPosition(GSvec* pos);
void cameraSetOffsetRotation(GSvec* rot);
void loadModel(HSD_Archive* archive, u32 arg1, u32 index, u32 arg2);
s32 wazaSequenceSysGetResID(void);
extern _GSmodel* gCameraShakeModel;
extern s32 gCameraShakeModels;
extern s32 soundOpenPlayME;
extern GSvec unitScaleVector;
extern SVec zeroVector;
extern s32 this_;
}
extern "C++" {
static void _wazaCameraInitShake(WazaSequence* p0, int p1);
u32 wazaSequenceSysGetModelShadowCount();
u32 wazaSequenceSysGetModelShadowLight();
s32 wazaSequenceSysGetModelShadowList();
}
s32 __vt__10EventEntry;
s32 __vt__10ModelEntry;
s32 __vt__10SoundEntry;
s32 __vt__11CameraEntry;
s32 __vt__11EffectEntry;
s32 __vt__13ParticleEntry;
s32 __vt__13SequenceEntry;
s32 __vt__14LensFlareEntry;
s32 __vt__17MainSequenceEntry;
GSthread* gSoundThread;
bool EventEntry::Update(f32 time) {
    return false;
}

void SequenceEntry::End() {
}

void SequenceEntry::SetRenderCamera(_GScamera* camera) {
}

extern "C++" {
s32 EventEntry::Start() {
    ModelSequence *temp_r5;
    ModelSequence *var_r3;
    u32 temp_r0;

    temp_r5 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), ModelSequence **, 0x24);
    if ((s32) M2C_FIELD(temp_r5, s32 *, 8) == 1) {
        var_r3 = temp_r5;
    } else {
        var_r3 = NULL;
    }
    temp_r0 = M2C_FIELD(this, u32 *, 0x30);
    switch (temp_r0) {
    case 0:
        if (var_r3 != NULL) {
            ((ModelSequence*)(var_r3))->Sleep();
        }
block_22:
        M2C_FIELD(this, s32 *, 0x18) = 1;
        M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
        return 1;
    case 1:
        if (var_r3 != NULL) {
            ((ModelSequence*)(var_r3))->WakeUp();
        }
        goto block_22;
    case 2:
        M2C_FIELD(M2C_FIELD(temp_r5, u8 **, 0), s32 (**)(ModelSequence *, s32), 0x28)(temp_r5, 0);
        goto block_22;
    case 3:
        M2C_FIELD(M2C_FIELD(temp_r5, u8 **, 0), s32 (**)(ModelSequence *, s32), 0x28)(temp_r5, 1);
        goto block_22;
    case 4:
        if (var_r3 != NULL) {
            GSmodelRemoveNull((_GSmodel*)(M2C_FIELD(var_r3, _GSmodel **, 0x94)));
        }
        goto block_22;
    case 5:
        if (var_r3 != NULL) {
            ((ModelSequence*)(var_r3))->Fly(0U);
        }
        goto block_22;
    case 6:
        if (var_r3 != NULL) {
            ((ModelSequence*)(var_r3))->Land();
        }
        goto block_22;
    case 7:
        if (var_r3 != NULL) {
            ((ModelSequence*)(var_r3))->Freeze();
        }
        goto block_22;
    case 9:
        if (var_r3 != NULL) {
            ((ModelSequence*)(var_r3))->UnFreeze();
        }
        goto block_22;
    default:
        return 0;
    }
}
}

extern "C++" {
void SoundEntry::Stop(bool p0) {
    SndEmitter *temp_r3_2;
    s32 temp_r3;

    temp_r3 = M2C_FIELD(this, s32 *, 0x18);
    if ((temp_r3 != 2) && ((p0 != 0) || (temp_r3 == 1))) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
        if (M2C_FIELD(this, u16 *, 0x34) & 1) {
            gSoundThread = NULL;
        } else {
            temp_r3_2 = M2C_FIELD(this, SndEmitter **, 0x3C);
            if (temp_r3_2 != NULL) {
                GSsndFreeEmitter((SndEmitter*)(temp_r3_2));
                M2C_FIELD(this, SndEmitter **, 0x3C) = NULL;
            }
        }
        GSsndClose(M2C_FIELD(this, u32 *, 0x30));
    }
}
}

extern "C++" {
s32 SoundEntry::Update(float p0) {
    s32 unksp14;
    s32 unksp8;
    _GSmodel *temp_r31_2;
    s32 temp_r4_2;
    s32 var_r3;
    u8 temp_r4;
    u8 *temp_r3;

    M2C_FIELD(this, f32 *, 0x20) = (f32) (M2C_FIELD(this, f32 *, 0x20) + p0);
    if (M2C_FIELD(this, u16 *, 0x34) & 1) {
        if ((GSthread *) gSoundThread != NULL) {
            return GSthreadIsRunning((GSthread*)(gSoundThread));
        }
        return 0;
    }
    if ((SndEmitter *) M2C_FIELD(this, SndEmitter **, 0x3C) != NULL) {
        M2C_FIELD(*(M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), u8 ***, 0x24)), s32 (**)(u8 **, s32 *), 0x10)((M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), u8 ***, 0x24)), &unksp14);
        M2C_FIELD(*(M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), u8 ***, 0x24)), s32 (**)(u8 **, s32 *), 0x14)((M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), u8 ***, 0x24)), &unksp8);
        if (M2C_FIELD(this, u16 *, 0xA) & 1) {
            temp_r4 = M2C_FIELD(this, u8 *, 5);
            if ((temp_r4 != 0) && (temp_r4 != 0xFF)) {
                temp_r3 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4));
                M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
                if ((M2C_FIELD(temp_r3, f32 *, 0x1C) == M2C_FIELD(this, f32 *, 0x1C)) && ((s32) M2C_FIELD(temp_r3, s32 *, 0xC) == 2)) {
                    temp_r31_2 = M2C_FIELD(temp_r3, _GSmodel **, 0x4C);
                    if (temp_r31_2 != NULL) {
                        GSmodelForceAnimTransformUpdate((_GSmodel*)(temp_r31_2));
                        GSmodelGetPosition((_GSmodel*)(temp_r31_2), (GSvec*)(&unksp14));
                        GSmodelGetRotation((_GSmodel*)(temp_r31_2), (GSvec*)(&unksp8));
                    }
                }
            }
        }
        if (GSsndUpdateEmitter((SndEmitter*)(M2C_FIELD(this, SndEmitter **, 0x3C)), (SVec*)(&unksp14)) != 0) {
            return GSsndCheckEmitter((SndEmitter*)(M2C_FIELD(this, SndEmitter **, 0x3C)));
        }
        return 0;
    }
    temp_r4_2 = GSsndGetStatus(M2C_FIELD(this, u32 *, 0x30)) - 2;
    var_r3 = 1;
    if (((u32) ((1 | ~temp_r4_2) - ((u32) (1 - temp_r4_2) >> 1U)) >> 0x1FU) == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
}

extern "C++" {
s32 SoundEntry::Start() { return 0; }
extern "C++" {
void EffectEntry::Stop(bool p0) {
    GSeffect *temp_r3;
    s32 temp_r5;

    temp_r5 = M2C_FIELD(this, s32 *, 0x18);
    if ((temp_r5 != 2) && ((p0 != 0) || (temp_r5 == 1))) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
        temp_r3 = M2C_FIELD(this, GSeffect **, 0x30);
        if (temp_r3 != NULL) {
            ((GSeffect*)(temp_r3))->Stop();
        }
    }
}
}

extern "C++" {
void EffectEntry::End() { }
extern "C++" {
s32 EffectEntry::Update(float p0) { return 0; }
extern "C++" {
s32 EffectEntry::Start() { return 0; }
extern "C++" {
void LensFlareEntry::Stop(bool p0) {
    GSlensFlareSetVisible(M2C_FIELD(this_, u32 *, 0x30), 0U);
}
}

extern "C++" {
s32 LensFlareEntry::Update(float p0) { return 0; }
extern "C++" {
s32 LensFlareEntry::Start() { return 0; }
extern "C++" {
void ParticleEntry::Stop(bool p0) {
    s32 temp_r3;
    u32 temp_r3_2;

    temp_r3 = M2C_FIELD(this, s32 *, 0x18);
    if ((temp_r3 != 2) && ((p0 != 0) || (temp_r3 == 1))) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
        temp_r3_2 = M2C_FIELD(this, u32 *, 0x3C);
        if (temp_r3_2 != 0U) {
            GSparticleDestroyGenerator((s32) temp_r3_2);
        }
        M2C_FIELD(this, u32 *, 0x3C) = 0U;
    }
}
}

extern "C++" {
void ParticleEntry::End() {
    void* generator = M2C_FIELD(this, void**, 0x3C);
    if (generator != 0) {
        GSparticleStopGenerator(generator);
    }
}
}

extern "C++" {
s32 ParticleEntry::Update(float p0) {
    s32 unksp20;
    f32 sp14;
    f32 sp8;
    s32 temp_r30;
    u32 temp_r31_2;

    M2C_FIELD(this, f32 *, 0x20) = (f32) (M2C_FIELD(this, f32 *, 0x20) + p0);
    if (GSparticleIsGeneratorAlive(M2C_FIELD(this, u32 *, 0x3C)) == 0) {
        M2C_FIELD(this, u32 *, 0x3C) = 0U;
        return 0;
    }
    if (((s32) M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), s32 *, 8) != 1) && !(M2C_FIELD(this, u16 *, 0xA) & 4) && ((s32) M2C_FIELD(this, s32 *, 0x40) == 0)) {
        M2C_FIELD(M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), u8 **, 0), s32 (**)(void *, s32 *), 0x10)((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), &unksp20);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), u8 **, 0), s32 (**)(void *, f32 *), 0x14)((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), &sp14);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), u8 **, 0), s32 (**)(void *, f32 *), 0x18)((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), &sp8);
        temp_r31_2 = M2C_FIELD(this, u32 *, 0x34);
        temp_r30 = (temp_r31_2 >> 5U) & 1;
        GSparticleSetGeneratorPosition((GSparticleGenerator*)((GSparticleGenerator *) M2C_FIELD(this, u32 *, 0x3C)), (Vec*)(&unksp20));
        GSparticleSetGeneratorRotation(M2C_FIELD(this, u32 *, 0x3C), &sp14);
        GSparticleSetGeneratorScale(M2C_FIELD(this, u32 *, 0x3C), &sp8, temp_r30, (temp_r31_2 >> 9U) & 1);
    }
    return 1;
}
}

extern "C++" {
s32 ParticleEntry::Start() { return 0; }
extern "C++" {
void ParticleEntry::SetRenderCamera(_GScamera* p0) { }
extern "C++" {
void ModelEntry::Stop(bool p0) {
    s32 unksp14;
    s32 unksp20;
    s32 unksp8;
    ModelSequence *var_r30;
    _GSmodel *temp_r3;
    _GSmodel *var_r29;
    s32 temp_r0;

    var_r29 = NULL;
    temp_r0 = M2C_FIELD(this, s32 *, 0x18);
    if (temp_r0 != 1) {
        if (temp_r0 != 2) {
            if (p0 == 0) {
                return;
            }
            goto block_4;
        }
    } else {
block_4:
        M2C_FIELD(this, s32 *, 0x18) = 2;
        temp_r3 = M2C_FIELD(this, _GSmodel **, 0x4C);
        if (temp_r3 != NULL) {
            var_r30 = M2C_FIELD(M2C_FIELD(this, s8 **, 0x2C), ModelSequence **, 0x24);
            if ((s32) M2C_FIELD(var_r30, s32 *, 8) == 1) {

            } else {
                var_r30 = NULL;
            }
            if (var_r30 != NULL) {
                var_r29 = M2C_FIELD(var_r30, _GSmodel **, 0x94);
            }
            GSmodelStopAnimation((_GSmodel*)(temp_r3));
            GSmodelStopTexAnimation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)));
            GSmodelSetVisibility((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 0U);
            if ((var_r29 != NULL) && ((s8) M2C_FIELD(this, s8 *, 0x4A) != 0)) {
                GSmodelGetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp20));
                GSmodelGetRotation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp14));
                GSmodelGetPosition((_GSmodel*)(var_r29), (GSvec*)(&unksp8));
                PSVECSubtract((const register Vec*)(&unksp8), (const register Vec*)(&unksp20), (register Vec*)(&unksp8));
                M2C_FIELD(var_r30, s8 *, 0x58) = 0;
                if ((s8) M2C_FIELD(this, s8 *, 0x4B) != 0) {
                    M2C_FIELD(this, s8 *, 0x4B) = 0U;
                    GSmodelDetachFromGSpart((_GSmodel*)(var_r29), 0U);
                }
                ((ModelSequence*)(var_r30))->ResetPosition();
                ((ModelSequence*)(var_r30))->ResetRotation();
                ((ModelSequence*)(var_r30))->ResetScale();
                if (M2C_FIELD(this, u16 *, 0x48) & 0x10) {
                    GSmodelRemoveNull((_GSmodel*)(var_r29));
                }
                if (M2C_FIELD(this, u16 *, 0x48) & 8) {
                    GSmodelAddNull((_GSmodel*)(var_r29), (Vec*)(&unksp8), (Vec*)(NULL), (Vec*)(NULL));
                }
            }
            if ((s8) M2C_FIELD(this, s8 *, 0x4B) != 0) {
                GSmodelDetachFromGSpart((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 0U);
            }
            GSmodelSetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)((GSvec *) &zeroVector));
            GSmodelSetRotation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)((GSvec *) &zeroVector));
            GSmodelSetScale((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unitScaleVector));
        }
    }
}
}

extern "C++" {
s32 ModelEntry::Update(float p0) {
    s32 unksp14;
    s32 unksp20;
    s32 unksp8;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r3;
    u32 var_r30;
    u32 var_r3;
    u32 var_r4;

    M2C_FIELD(this, f32 *, 0x20) = (f32) (M2C_FIELD(this, f32 *, 0x20) + p0);
    if ((_GSmodel *) M2C_FIELD(this, _GSmodel **, 0x4C) == NULL) {
        return 0;
    }
    if ((s32) M2C_FIELD(this, s32 *, 0x18) == 3) {
        return 1;
    }
    if (((s32) M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), s32 *, 8) != 1) && !(M2C_FIELD(this, s16 *, 0xA) & 4) && ((u8) M2C_FIELD(this, u8 *, 0x4A) == 0) && ((u8) M2C_FIELD(this, u8 *, 0x4B) == 0)) {
        M2C_FIELD(M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), u8 **, 0), s32 (**)(void *, s32 *), 0x10)((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), &unksp20);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), u8 **, 0), s32 (**)(void *, s32 *), 0x14)((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), &unksp14);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), u8 **, 0), s32 (**)(void *, s32 *), 0x18)((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), &unksp8);
        GSmodelSetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp20));
        GSmodelSetRotation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp14));
        GSmodelSetScale((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp8));
    }
    if ((s32) M2C_FIELD(this, s32 *, 0x38) < 0) {
        var_r30 = 1;
    } else {
        temp_r0 = M2C_FIELD(this, s32 *, 0x34);
        if (temp_r0 != 1) {
            if (temp_r0 < 1) {

            }
            var_r30 = GSmodelHasAnimationEnded((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)));
        } else {
            M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
            var_r30 = ((u32) M2C_ERROR(/* unknown instruction: mfcr $r0 */) >> 0x1DU) & 1;
        }
    }
    temp_r3 = M2C_FIELD(this, s32 *, 0x40);
    if (((s32) M2C_FIELD(this, s32 *, 0x38) != temp_r3) && (temp_r3 >= 0)) {
        temp_r0_2 = M2C_FIELD(this, s32 *, 0x3C);
        if (temp_r0_2 != 1) {
            if (temp_r0_2 < 1) {

            }
            var_r3 = GSmodelHasTexAnimationEnded((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)));
        } else {
            M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
            var_r3 = ((u32) M2C_ERROR(/* unknown instruction: mfcr $r0 */) >> 0x1DU) & 1;
        }
        var_r4 = 0;
        if (((u8) var_r30 != 0) && ((u8) var_r3 != 0)) {
            var_r4 = 1;
        }
        var_r30 = var_r4;
    }
    if ((u8) var_r30 != 0) {
        if (M2C_FIELD(this, s16 *, 0x48) & 2) {
            M2C_FIELD(this, s32 *, 0x18) = 3;
            return 1;
        }
        return 0;
    }
    return 1;
}
}

extern "C++" {
s32 ModelEntry::Start() { return 0; }
extern "C++" {
void ModelEntry::SetRenderCamera(_GScamera* p0) { }
extern "C++" {
void CameraEntry::Stop(bool p0) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    s32 temp_r0;
    s32 temp_r5;

    temp_r5 = M2C_FIELD(this, s32 *, 0x18);
    if ((temp_r5 != 2) && ((p0 != 0) || (temp_r5 == 1))) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
        temp_r0 = M2C_FIELD(this, s32 *, 0x30);
        if (temp_r0 != 1) {
            if (temp_r0 < 1) {

            }
        } else {
            sp8 = 0.0f;
            spC = 0.0f;
            sp10 = 0.0f;
            cameraSetOffsetPosition((GSvec*)((GSvec *) &sp8));
            cameraSetOffsetRotation((GSvec*)((GSvec *) &sp8));
            if ((_GSmodel *) gCameraShakeModel != NULL) {
                GSmodelStopAnimation((_GSmodel*)(gCameraShakeModel));
                gCameraShakeModel = NULL;
            }
        }
    }
}
}

extern "C++" {
s32 CameraEntry::Update(float p0) {
    s32 unksp14;
    f32 unksp8;
    GSpart *temp_r3;
    s32 temp_r0;

    M2C_FIELD(this, f32 *, 0x20) = (f32) (M2C_FIELD(this, f32 *, 0x20) + p0);
    temp_r0 = M2C_FIELD(this, s32 *, 0x30);
    switch (temp_r0) {                              /* irregular */
    case 0:
        M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
        if ((M2C_FIELD(this, f32 *, 0x20) - M2C_FIELD(this, f32 *, 0x1C)) == M2C_FIELD(this, f32 *, 0x34)) {
            M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), s8 *, 0x15) = 1;
            return 0;
        }
    default:
        return 1;
    case 1:
        if ((_GSmodel *) gCameraShakeModel == NULL) {
            return 0;
        }
        if ((GSmodelIsAnimating((_GSmodel*)(gCameraShakeModel)) == 0) || (GSmodelHasAnimationEnded((_GSmodel*)(gCameraShakeModel)) != 0)) {
            return 0;
        }
        temp_r3 = GSmodelGetPart((_GSmodel*)(gCameraShakeModel), 1);
        if (temp_r3 == NULL) {
            return 0;
        }
        GSpartGetTransform((GSpart*)(temp_r3), (GSvec*)(&unksp8), (GSvec*)(&unksp14), (GSvec*)(NULL));
        PSVECScale((const register Vec*)(&unksp8), (register Vec*)(&unksp8), 2.5f);
        cameraSetOffsetPosition((GSvec*)(&unksp8));
        cameraSetOffsetRotation((GSvec*)(&unksp14));
        GSpartFree((GSpart*)(temp_r3));
        return 1;
    }
}
}

extern "C++" {
s32 CameraEntry::Start() {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(this, s32 *, 0x30);
    if (temp_r0 != 1) {
        if (temp_r0 < 1) {
            if (temp_r0 < 0) {
                goto block_7;
            }
            goto block_8;
        }
        if (temp_r0 < 4) {
            goto block_8;
        }
block_7:
        return 0;
    }
    _wazaCameraInitShake((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)), M2C_FIELD(this, s32 *, 0x34));
block_8:
    M2C_FIELD(this, s32 *, 0x18) = 1;
    M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
    return 1;
}
}

extern "C++" {
void SequenceEntry::Stop(bool p0) {
    s32 temp_r5;

    temp_r5 = M2C_FIELD(this, s32 *, 0x18);
    if ((temp_r5 != 2) && ((p0 != 0) || (temp_r5 == 1))) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
    }
}
}

extern "C++" {
s32 SequenceEntry::Update(float p0) {
    M2C_FIELD(this, f32 *, 0x20) = (f32) (M2C_FIELD(this, f32 *, 0x20) + p0);
    return 1;
}
}

extern "C++" {
s32 SequenceEntry::Start() {
    M2C_FIELD(this, s32 *, 0x18) = 1;
    M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
    return 1;
}
}

extern "C++" {
SoundEntry::~SoundEntry() {
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    u8 **temp_r3;

    temp_cr0_eq = this == NULL;
    if (temp_cr0_eq == 0) {
        M2C_FIELD(this, s32 **, 0) = &__vt__10SoundEntry;
        if (temp_cr0_eq) {
            M2C_FIELD((u16)this, s32 **, 0) = &__vt__13SequenceEntry;
            temp_r3 = M2C_FIELD(this, u8 ***, 0x24);
            temp_cr0_eq_2 = temp_r3 == NULL;
            if ((temp_cr0_eq_2 == 0) && (temp_cr0_eq_2 == 0)) {
                M2C_FIELD(*temp_r3, s32 (**)(s32), 8)(1);
            }
        }
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
SoundEntry::SoundEntry(WazaSequence* p0, unsigned char** p1) {
    u8 *temp_r4;

    ((SequenceEntry*)((SequenceEntry *) this))->SequenceEntry((enumSequenceEntryDataType)(5), (WazaSequence*)((u16)p0), (unsigned char**)(p1));
    M2C_FIELD(this, s32 **, 0) = &__vt__10SoundEntry;
    temp_r4 = *p1;
    M2C_FIELD(this, s32 *, 0x3C) = 0;
    M2C_FIELD(this, s16 *, 0x34) = (s16) M2C_FIELD(temp_r4, s32 *, 8);
    M2C_FIELD(this, s8 *, 0x36) = (s8) M2C_FIELD(temp_r4, s32 *, 0x10);
    M2C_FIELD(this, f32 *, 0x38) = (f32) M2C_FIELD(temp_r4, f32 *, 0xC);
    M2C_FIELD(this, s32 *, 0x30) = (s32) M2C_FIELD(temp_r4, s32 *, 0);
    *p1 += 0x14;
    return;
}
}

extern "C++" {
void SoundEntry::Unload(unsigned char** p0) { }
extern "C++" {
s32 SoundEntry::Load(unsigned char** p0) { return 0; }
extern "C++" {
EventEntry::~EventEntry() {
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    u8 **temp_r3;

    temp_cr0_eq = this == NULL;
    if (temp_cr0_eq == 0) {
        M2C_FIELD(this, s32 **, 0) = &__vt__10EventEntry;
        if (temp_cr0_eq) {
            M2C_FIELD((u16)this, s32 **, 0) = &__vt__13SequenceEntry;
            temp_r3 = M2C_FIELD(this, u8 ***, 0x24);
            temp_cr0_eq_2 = temp_r3 == NULL;
            if ((temp_cr0_eq_2 == 0) && (temp_cr0_eq_2 == 0)) {
                M2C_FIELD(*temp_r3, s32 (**)(s32), 8)(1);
            }
        }
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
EventEntry::EventEntry(WazaSequence* p0, unsigned char** p1) {
    M2C_FIELD(this, s32 **, 0) = &__vt__10EventEntry;
    ((SequenceEntry*)((SequenceEntry *) this))->SequenceEntry((enumSequenceEntryDataType)(6), (WazaSequence*)(p0), (unsigned char**)(p1));
    M2C_FIELD(this, s32 *, 0x30) = (s32) **p1;
    *p1 += 8;
    return;
}
}

extern "C++" {
void EventEntry::Unload(unsigned char** p0) { }
extern "C++" {
s32 EventEntry::Load(unsigned char** p0) { return 0; }
extern "C++" {
EffectEntry::~EffectEntry() {
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    u8 **temp_r3_2;
    u8 *temp_r3;

    if (this != NULL) {
        M2C_FIELD(this, s32 **, 0) = &__vt__11EffectEntry;
        temp_r3 = M2C_FIELD(this, u8 **, 0x30);
        temp_cr0_eq = temp_r3 == NULL;
        if ((temp_cr0_eq == 0) && (temp_cr0_eq == 0)) {
            M2C_FIELD(M2C_FIELD(temp_r3, u8 **, 8), s32 (**)(s32), 0x1C)(1);
        }
        if (this != NULL) {
            M2C_FIELD((u16)this, s32 **, 0) = &__vt__13SequenceEntry;
            temp_r3_2 = M2C_FIELD(this, u8 ***, 0x24);
            temp_cr0_eq_2 = temp_r3_2 == NULL;
            if ((temp_cr0_eq_2 == 0) && (temp_cr0_eq_2 == 0)) {
                M2C_FIELD(*temp_r3_2, s32 (**)(s32), 8)(1);
            }
        }
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
EffectEntry::EffectEntry(WazaSequence* p0, unsigned char** p1) { }
extern "C++" {
void EffectEntry::Unload(unsigned char** p0) { }
extern "C++" {
s32 EffectEntry::Load(unsigned char** p0) { return 0; }
extern "C++" {
LensFlareEntry::~LensFlareEntry() {
    s32 temp_cr0_eq;
    u8 **temp_r3;

    if (this != NULL) {
        M2C_FIELD(this, s32 **, 0) = &__vt__14LensFlareEntry;
        GSlensFlareSetVisible(M2C_FIELD(this, u32 *, 0x30), 0U);
        GSlensFlareFree(M2C_FIELD(this, u32 *, 0x30));
        if (this != NULL) {
            M2C_FIELD((u16)this, s32 **, 0) = &__vt__13SequenceEntry;
            temp_r3 = M2C_FIELD(this, u8 ***, 0x24);
            temp_cr0_eq = temp_r3 == NULL;
            if ((temp_cr0_eq == 0) && (temp_cr0_eq == 0)) {
                M2C_FIELD(*temp_r3, s32 (**)(s32), 8)(1);
            }
        }
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
LensFlareEntry::LensFlareEntry(WazaSequence* p0, unsigned char** p1) {
    u8 *temp_r31;

    M2C_FIELD(this, s32 **, 0) = &__vt__14LensFlareEntry;
    ((SequenceEntry*)((SequenceEntry *) this))->SequenceEntry((enumSequenceEntryDataType)(7), (WazaSequence*)(p0), (unsigned char**)(p1));
    M2C_FIELD(this, u32 *, 0x30) = 0U;
    temp_r31 = *p1;
    M2C_FIELD(this, f32 *, 0x34) = (f32) M2C_FIELD(temp_r31, f32 *, 0xC);
    M2C_FIELD(this, s32 *, 0x38) = (s32) M2C_FIELD(temp_r31, s32 *, 8);
    *p1 += 0x14;
    *p1 = (u8 *) ((s32) (*p1 + 0x1F) & 0xFFFFFFE0);
    M2C_FIELD(this, u32 *, 0x30) = GSlensFlareLoad((u8*)(*p1));
    *p1 = &(*p1)[(M2C_FIELD(temp_r31, s32 *, 0) + 0x1F) & 0xFFFFFFE0];
    GSlensFlareSetVisible(M2C_FIELD(this, u32 *, 0x30), 0U);
    return;
}
}

extern "C++" {
void LensFlareEntry::Unload(unsigned char** p0) { }
extern "C++" {
s32 LensFlareEntry::Load(unsigned char** p0) { return 0; }
extern "C++" {
ParticleEntry::~ParticleEntry() {
    GSparticleBank *temp_r3;
    s32 temp_cr0_eq;
    u8 **temp_r3_2;

    if (this != NULL) {
        M2C_FIELD(this, s32 **, 0) = &__vt__13ParticleEntry;
        if ((u8) M2C_FIELD(this, u8 *, 9) == 0) {
            temp_r3 = M2C_FIELD(this, GSparticleBank **, 0x38);
            if (temp_r3 != NULL) {
                GSparticleDestroyAllGenerators((GSparticleBank*)(temp_r3), 1);
            }
        }
        M2C_FIELD(this, s32 *, 0x3C) = 0;
        M2C_FIELD(this, GSparticleBank **, 0x38) = NULL;
        if (this != NULL) {
            M2C_FIELD((u16)this, s32 **, 0) = &__vt__13SequenceEntry;
            temp_r3_2 = M2C_FIELD(this, u8 ***, 0x24);
            temp_cr0_eq = temp_r3_2 == NULL;
            if ((temp_cr0_eq == 0) && (temp_cr0_eq == 0)) {
                M2C_FIELD(*temp_r3_2, s32 (**)(s32), 8)(1);
            }
        }
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
ParticleEntry::ParticleEntry(WazaSequence* p0, unsigned char** p1) {
    u8 *temp_r31;
    u8 temp_r4;
    u8 *temp_r3;
    u8 *temp_ret;

    M2C_FIELD(this, s32 **, 0) = &__vt__13ParticleEntry;
    ((SequenceEntry*)((SequenceEntry *) this))->SequenceEntry((enumSequenceEntryDataType)(3), (WazaSequence*)(p0), (unsigned char**)(p1));
    M2C_FIELD(this, s32 *, 0x3C) = 0;
    temp_r31 = *p1;
    *p1 = temp_r31 + 0x14;
    *p1 = (u8 *) ((s32) (*p1 + 0x1F) & 0xFFFFFFE0);
    *p1 = &(*p1)[(M2C_FIELD(temp_r31, s32 *, 8) + 0x1F) & 0xFFFFFFE0];
    temp_r4 = M2C_FIELD(this, u8 *, 9);
    if (temp_r4 != 0) {
        temp_ret = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4));
        temp_r3 = temp_ret;
        if (temp_r3 != NULL) {
            M2C_FIELD(this, s32 *, 0x38) = (s32) M2C_FIELD(temp_r3, s32 *, 0x38);
        } else {
            GSlogWrite((const char*)("particle waza entry not found"), (u32) (u64) temp_ret, M2C_BITWISE(f32, (s32)temp_ret));
            M2C_FIELD(this, s32 *, 0x38) = 0;
        }
    } else {
        M2C_FIELD(this, s32 *, 0x38) = (s32) M2C_FIELD(temp_r31, s32 *, 0xC);
    }
    M2C_FIELD(this, s32 *, 0x30) = (s32) M2C_FIELD(temp_r31, s32 *, 0);
    M2C_FIELD(this, s32 *, 0x34) = (s32) M2C_FIELD(temp_r31, s32 *, 4);
    M2C_FIELD(this, s32 *, 0x3C) = 0;
    return;
}
}

extern "C++" {
void ParticleEntry::Unload(unsigned char** p0) { }
extern "C++" {
s32 ParticleEntry::Load(unsigned char** p0) { return 0; }
extern "C++" {
ModelEntry::~ModelEntry() {
    s32 temp_cr0_eq;
    u32 temp_r4;
    u8 **temp_r3;

    if (this != NULL) {
        M2C_FIELD(this, s32 **, 0) = &__vt__10ModelEntry;
        temp_r4 = M2C_FIELD(this, u32 *, 0x30);
        if (temp_r4 != 0) {
            GSresFreeResource(0x4E20U, temp_r4);
        }
        if (this != NULL) {
            M2C_FIELD((u16)this, s32 **, 0) = &__vt__13SequenceEntry;
            temp_r3 = M2C_FIELD(this, u8 ***, 0x24);
            temp_cr0_eq = temp_r3 == NULL;
            if ((temp_cr0_eq == 0) && (temp_cr0_eq == 0)) {
                M2C_FIELD(*temp_r3, s32 (**)(s32), 8)(1);
            }
        }
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
ModelEntry::ModelEntry(WazaSequence* p0, unsigned char** p1) {
    f32 sp8;
    f32 spC;
    HSD_Archive *temp_r3;
    _GSmodel *temp_r3_2;
    _GSmodel *temp_r3_4;
    f32 var_f31;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r28;
    s32 temp_r3_3;
    u8 *temp_r31;

    ((SequenceEntry*)((SequenceEntry *) this))->SequenceEntry((enumSequenceEntryDataType)(2), (WazaSequence*)(p0), (unsigned char**)(p1));
    M2C_FIELD(this, s32 **, 0) = &__vt__10ModelEntry;
    temp_r31 = *p1;
    temp_r28 = wazaSequenceSysGetResID();
    *p1 += 0x28;
    *p1 = (u8 *) ((s32) (*p1 + 0x1F) & 0xFFFFFFE0);
    M2C_FIELD(this, s32 *, 0x30) = 0;
    M2C_FIELD(this, _GSmodel **, 0x4C) = NULL;
    temp_r3 = M2C_FIELD(temp_r31, HSD_Archive **, 0x20);
    if (temp_r3 != NULL) {
        loadModel((HSD_Archive*)(temp_r3), 0x4E20U, 0U, (u32) temp_r28);
        GSresIsUniqueID(0x4E20U, (u32) temp_r28, 0U);
        temp_r3_2 = (_GSmodel *)(GSresGetResource(0x4E20U, (u32) temp_r28));
        M2C_FIELD(this, _GSmodel **, 0x4C) = temp_r3_2;
        if (temp_r3_2 != NULL) {
            M2C_FIELD(this, s32 *, 0x30) = temp_r28;
        }
    }
    temp_r3_3 = M2C_FIELD(temp_r31, s32 *, 0x1C);
    if (temp_r3_3 != 0) {
        *p1 = &(*p1)[(temp_r3_3 + 0x1F) & 0xFFFFFFE0];
    }
    M2C_FIELD(this, s32 *, 0x38) = (s32) M2C_FIELD(temp_r31, s32 *, 0);
    temp_r0 = M2C_FIELD(temp_r31, s32 *, 4);
    switch (temp_r0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        M2C_FIELD(this, s32 *, 0x34) = 0;
        break;
    case 1:                                         /* switch 1 */
        M2C_FIELD(this, s32 *, 0x34) = 1;
        break;
    }
    M2C_FIELD(this, s32 *, 0x40) = (s32) M2C_FIELD(temp_r31, s32 *, 8);
    temp_r0_2 = M2C_FIELD(temp_r31, s32 *, 0xC);
    switch (temp_r0_2) {                            /* switch 2; irregular */
    case 0:                                         /* switch 2 */
        M2C_FIELD(this, s32 *, 0x3C) = 0;
        break;
    case 1:                                         /* switch 2 */
        M2C_FIELD(this, s32 *, 0x3C) = 1;
        break;
    }
    M2C_FIELD(this, s8 *, 0x4A) = (s8) (M2C_FIELD(temp_r31, s32 *, 0x10) != 0);
    M2C_FIELD(this, s32 *, 0x44) = (s32) M2C_FIELD(temp_r31, s32 *, 0x14);
    M2C_FIELD(this, s16 *, 0x48) = (s16) M2C_FIELD(temp_r31, s32 *, 0x18);
    if (M2C_FIELD((M2C_FIELD(this, s32 *, 0x14) + (M2C_FIELD(this, u8 *, 8) * 4)), f32 *, -4) < 0.00001f) {
        spC = 0.0f;
        sp8 = 0.0f;
        temp_r3_4 = M2C_FIELD(this, _GSmodel **, 0x4C);
        if (temp_r3_4 != NULL) {
            GSmodelGetFrameCount((_GSmodel*)(temp_r3_4), (f32*)(&spC), (f32*)(&sp8));
        }
        var_f31 = spC;
        M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
        if (var_f31 == sp8) {

        } else {
            var_f31 = sp8;
        }
        M2C_FIELD((M2C_FIELD(this, s32 *, 0x14) + (M2C_FIELD(this, u8 *, 8) * 4)), f32 *, -4) = (f32) ((f32) (s32) var_f31 / (f32) GSgfxVideoGetVsyncRate());
    }
    return;
}
}

extern "C++" {
void ModelEntry::Unload(unsigned char** p0) { }
extern "C++" {
s32 ModelEntry::Load(unsigned char** p0) { return 0; }
extern "C++" {
CameraEntry::~CameraEntry() {
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    u8 **temp_r3;

    temp_cr0_eq = this == NULL;
    if (temp_cr0_eq == 0) {
        M2C_FIELD(this, s32 **, 0) = &__vt__11CameraEntry;
        if (temp_cr0_eq) {
            M2C_FIELD((u16)this, s32 **, 0) = &__vt__13SequenceEntry;
            temp_r3 = M2C_FIELD(this, u8 ***, 0x24);
            temp_cr0_eq_2 = temp_r3 == NULL;
            if ((temp_cr0_eq_2 == 0) && (temp_cr0_eq_2 == 0)) {
                M2C_FIELD(*temp_r3, s32 (**)(s32), 8)(1);
            }
        }
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
CameraEntry::CameraEntry(WazaSequence* p0, unsigned char** p1) {
    s32 temp_r0;
    u8 *temp_r3;

    ((SequenceEntry*)((SequenceEntry *) this))->SequenceEntry((enumSequenceEntryDataType)(1), (WazaSequence*)((u16)p0), (unsigned char**)(p1));
    M2C_FIELD((u16)this, s32 **, 0) = &__vt__11CameraEntry;
    temp_r3 = *p1;
    *p1 = temp_r3 + 0xC;
    M2C_FIELD(this, s32 *, 0x30) = (s32) M2C_FIELD(temp_r3, s32 *, 0);
    temp_r0 = M2C_FIELD(this, s32 *, 0x30);
    switch (temp_r0) {                              /* irregular */
    case 0:
        M2C_FIELD(this, f32 *, 0x34) = (f32) M2C_FIELD(temp_r3, f32 *, 4);
        break;
    case 1:
        M2C_FIELD(this, f32 *, 0x34) = (f32) M2C_FIELD(temp_r3, f32 *, 4);
        break;
    case 2:
        M2C_FIELD(this, f32 *, 0x34) = (f32) M2C_FIELD(temp_r3, f32 *, 4);
        break;
    case 3:
        *p1 += M2C_BITWISE(s32, M2C_FIELD(temp_r3, f32 *, 4)) * 8;
        M2C_FIELD(this, s32 *, 0x30) = 0;
        M2C_FIELD(this, f32 *, 0x34) = 0.0f;
        break;
    }
    return;
}
}

extern "C++" {
void CameraEntry::Unload(unsigned char** p0) { }
extern "C++" {
s32 CameraEntry::Load(unsigned char** p0) { return 0; }
extern "C++" {
MainSequenceEntry::~MainSequenceEntry() {
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    u8 **temp_r3;

    temp_cr0_eq = this == NULL;
    if (temp_cr0_eq == 0) {
        M2C_FIELD(this, s32 **, 0) = &__vt__17MainSequenceEntry;
        if (temp_cr0_eq) {
            M2C_FIELD((u16)this, s32 **, 0) = &__vt__13SequenceEntry;
            temp_r3 = M2C_FIELD(this, u8 ***, 0x24);
            temp_cr0_eq_2 = temp_r3 == NULL;
            if ((temp_cr0_eq_2 == 0) && (temp_cr0_eq_2 == 0)) {
                M2C_FIELD(*temp_r3, s32 (**)(s32), 8)(1);
            }
        }
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
MainSequenceEntry::MainSequenceEntry(WazaSequence* p0, unsigned char** p1) { }
extern "C++" {
void SequenceEntry::Link() { }
extern "C++" {
SequenceEntry::~SequenceEntry() {
    s32 temp_cr0_eq;
    u8 **temp_r3;

    if (this != NULL) {
        M2C_FIELD(this, s32 **, 0) = &__vt__13SequenceEntry;
        temp_r3 = M2C_FIELD(this, u8 ***, 0x24);
        temp_cr0_eq = temp_r3 == NULL;
        if ((temp_cr0_eq == 0) && (temp_cr0_eq == 0)) {
            M2C_FIELD(*temp_r3, s32 (**)(s32), 8)(1);
        }
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
SequenceEntry::SequenceEntry(enumSequenceEntryDataType p0, WazaSequence* p1, unsigned char** p2) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    u8 *temp_r7;

    M2C_FIELD(this, s32 **, 0) = &__vt__13SequenceEntry;
    M2C_FIELD(this, s32 *, 0xC) = p0;
    M2C_FIELD(this, WazaSequence **, 0x2C) = p1;
    temp_r7 = *p2;
    M2C_FIELD(this, u8 *, 9) = (u8) M2C_FIELD(temp_r7, s32 *, 0x6C);
    M2C_FIELD(this, u8 *, 4) = (u8) M2C_FIELD(temp_r7, s32 *, 0);
    temp_r0 = M2C_FIELD(temp_r7, s32 *, 0x10);
    if (temp_r0 >= 0) {
        M2C_FIELD(this, u8 *, 5) = (u8) temp_r0;
    } else {
        M2C_FIELD(this, u8 *, 5) = 0xFF;
    }
    temp_r0_2 = M2C_FIELD(temp_r7, s32 *, 0x14);
    if (temp_r0_2 >= 0) {
        M2C_FIELD(this, u8 *, 6) = (u8) temp_r0_2;
    } else {
        M2C_FIELD(this, u8 *, 6) = 0;
    }
    temp_r0_3 = M2C_FIELD(temp_r7, s32 *, 0x18);
    if (temp_r0_3 >= 0) {
        M2C_FIELD(this, u8 *, 7) = (u8) temp_r0_3;
    } else {
        M2C_FIELD(this, u8 *, 7) = 0;
    }
    M2C_FIELD(this, u8 *, 8) = (u8) M2C_FIELD(temp_r7, s32 *, 0x1C);
    M2C_FIELD(this, s16 *, 0xA) = (s16) M2C_FIELD(temp_r7, s32 *, 0x60);
    M2C_FIELD(this, s16 *, 0x12) = (s16) M2C_FIELD(temp_r7, s32 *, 0x64);
    M2C_FIELD(this, u8 *, 0x10) = (u8) M2C_FIELD(temp_r7, s32 *, 8);
    M2C_FIELD(this, u8 *, 0x11) = (u8) M2C_FIELD(temp_r7, s32 *, 0xC);
    M2C_FIELD(this, u8 **, 0x14) = (u8 *) (temp_r7 + 0x20);
    M2C_FIELD(this, s32 *, 0x24) = 0;
    M2C_FIELD(this, s32 *, 0x28) = 0;
    M2C_FIELD(this, f32 *, 0x20) = 0.0f;
    M2C_FIELD(this, f32 *, 0x1C) = 0.0f;
    M2C_FIELD(this, s32 *, 0x18) = 0;
    *p2 += 0x70;
}
}

extern "C++" {
static void _wazaCameraInitShake(WazaSequence* p0, int p1) {
    s32 unksp8;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    GSpart *temp_r3;

    if ((p0 == NULL) || ((u32) M2C_FIELD(p0, u32 *, 0x1C) != 0U)) {
        gCameraShakeModel = NULL;
        return;
    }
    sp14 = 0.0f;
    sp18 = 0.0f;
    sp1C = 0.0f;
    cameraSetOffsetPosition((GSvec*)((GSvec *) &sp14));
    cameraSetOffsetRotation((GSvec*)((GSvec *) &sp14));
    if ((s32) (p1 & 9) == 9) {
        gCameraShakeModel = M2C_FIELD(&gCameraShakeModels, _GSmodel **, 0);
    } else if ((s32) (p1 & 0x11) == 0x11) {
        gCameraShakeModel = M2C_FIELD(&gCameraShakeModels, _GSmodel **, 4);
    } else if ((s32) (p1 & 0x21) == 0x21) {
        gCameraShakeModel = M2C_FIELD(&gCameraShakeModels, _GSmodel **, 8);
    } else if ((s32) (p1 & 0xA) == 0xA) {
        gCameraShakeModel = M2C_FIELD(&gCameraShakeModels, _GSmodel **, 0xC);
    } else if ((s32) (p1 & 0x12) == 0x12) {
        gCameraShakeModel = M2C_FIELD(&gCameraShakeModels, _GSmodel **, 0x10);
    } else if ((s32) (p1 & 0x22) == 0x22) {
        gCameraShakeModel = M2C_FIELD(&gCameraShakeModels, _GSmodel **, 0x14);
    } else if ((s32) (p1 & 0xC) == 0xC) {
        gCameraShakeModel = M2C_FIELD(&gCameraShakeModels, _GSmodel **, 0x18);
    } else if ((s32) (p1 & 0x14) == 0x14) {
        gCameraShakeModel = M2C_FIELD(&gCameraShakeModels, _GSmodel **, 0x1C);
    } else if ((s32) (p1 & 0x24) == 0x24) {
        gCameraShakeModel = M2C_FIELD(&gCameraShakeModels, _GSmodel **, 0x20);
    } else {
        gCameraShakeModel = NULL;
    }
    if ((_GSmodel *) gCameraShakeModel != NULL) {
        GSmodelSetAnimIndex((_GSmodel*)(gCameraShakeModel), 0U);
        GSmodelSetAnimType((_GSmodel*)(gCameraShakeModel), 0);
        GSmodelSetAnimRate((_GSmodel*)(gCameraShakeModel), 0.5f);
        GSmodelSetAnimFrame((_GSmodel*)(gCameraShakeModel), 0.0f);
        GSmodelStartAnimation((_GSmodel*)(gCameraShakeModel));
        temp_r3 = GSmodelGetPart((_GSmodel*)(gCameraShakeModel), 1);
        if (temp_r3 != NULL) {
            GSpartGetTransform((GSpart*)(temp_r3), (GSvec*)((GSvec *) &sp14), (GSvec*)(&unksp8), (GSvec*)(NULL));
            PSVECScale((const register Vec*)((Vec *) &sp14), (register Vec*)((Vec *) &sp14), 2.5f);
            cameraSetOffsetPosition((GSvec*)((GSvec *) &sp14));
            cameraSetOffsetRotation((GSvec*)(&unksp8));
            GSpartFree((GSpart*)(temp_r3));
        }
    }
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
