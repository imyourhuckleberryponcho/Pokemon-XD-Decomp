#include <dolphin/types.h>
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

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
class GSeffect;
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

class SeqCameraTarget {
public:
    virtual void unk08();
    virtual void unk0C();
    virtual void GetPosition(f32* pos);
    virtual void GetRotation(f32* rot);
    virtual void GetScale(f32* scale);
};

class SequenceEntry {
public:
    virtual ~SequenceEntry();
    virtual s32 Start();
    virtual bool Update(float);
    virtual void End();
    virtual void Stop(bool);
    virtual void SetRenderCamera(_GScamera* camera);

    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    u8 unk08;
    u8 unk09;
    u16 unk0A;
    enumSequenceEntryDataType type;
    u8 unk10;
    u8 unk11;
    u16 unk12;
    u8* params;
    s32 unk18;
    f32 unk1C;
    f32 unk20;
    SequenceEntry* child;
    s32 unk28;
    WazaSequence* seq;

    SequenceEntry(enumSequenceEntryDataType, WazaSequence*, unsigned char**);
    void Link();
};

class EventEntry : public SequenceEntry {
public:
    bool Update(f32 time);
public:
    static s32 Load(unsigned char**);
    s32 Start();
    ~EventEntry();
    static void Unload(unsigned char**);
    EventEntry(WazaSequence*, unsigned char**);
};

class CameraEntry : public SequenceEntry {
public:
    void Stop(bool);
    ~CameraEntry();
    CameraEntry(WazaSequence*, unsigned char**);
    static void Unload(unsigned char**);
    bool Update(float);
    static s32 Load(unsigned char**);
    s32 Start();
};
struct EffectKey {
    union {
        struct {
            u8 from[4];
            u8 to[4];
        } color;
        struct {
            f32 from;
            f32 to;
        } value;
    };
    f32 duration;
    u32 unk0C;
};

class EffectEntry : public SequenceEntry {
public:
    GSeffect* m_effect;
    union {
        EffectKey* m_keys;
        f32 m_elapsed;
    };
    f32 m_time;
    u8 m_keyCount;
    u8 m_curKey;
    u8 unk3E[2];
    u8 m_keyed;
    u8 m_type;

    void blurEffectLoad(unsigned char**);
    ~EffectEntry();
    void End();
    void boneFillEffectLoad(unsigned char**);
    void envMapEffectLoad(unsigned char**);
    bool Update(float);
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
struct GSgfxLayer;
enum GSgfxLayerPass { GSgfxLayerPass_draft_dummy };
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
    f32 x, y, z;
};
struct HSD_Archive {
    u8 _draft[1];
};
class LensFlareEntry : public SequenceEntry {
public:
    LensFlareEntry(WazaSequence*, unsigned char**);
    s32 Start();
    void Stop(bool);
    static void Unload(unsigned char**);
    static s32 Load(unsigned char**);
    ~LensFlareEntry();
    bool Update(float);
};
class MainSequenceEntry : public SequenceEntry {
public:
    ~MainSequenceEntry();
    MainSequenceEntry(WazaSequence*, unsigned char**);
};
class ModelEntry : public SequenceEntry {
public:
    ModelEntry(WazaSequence*, unsigned char**);
    ~ModelEntry();
    bool Update(float);
    void SetRenderCamera(_GScamera*);
    static s32 Load(unsigned char**);
    void Stop(bool);
    static void Unload(unsigned char**);
    s32 Start();
};
struct ModelSequence {
    virtual ~ModelSequence();
    virtual bool Update(f32);
    virtual void GetPosition(GSvec*);
    virtual void GetRotation(GSvec*);
    virtual void GetScale(GSvec*);
    virtual void SetPosition(GSvec*);
    virtual void SetRotation(GSvec*);
    virtual void SetScale(GSvec*);
    virtual void SetVisibility(bool);
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
class ParticleEntry : public SequenceEntry {
public:
    s32 Start();
    void End();
    void Stop(bool);
    void SetRenderCamera(_GScamera*);
    static s32 Load(unsigned char**);
    bool Update(float);
    ParticleEntry(WazaSequence*, unsigned char**);
    static void Unload(unsigned char**);
    ~ParticleEntry();
};
struct SVec {
    f32 x, y, z;
};
struct SndEmitter {
    u8 _draft[1];
};
class SoundEntry : public SequenceEntry {
public:
    s32 Start();
    void Stop(bool);
    static s32 Load(unsigned char**);
    bool Update(float);
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
    u8 _draft[0x28];
    billboardEffect(unsigned char**);
};
struct leafEffect {
    u8 _draft[0x60];
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
void GSparticleBankSetCamera(GSparticleBank* bank, _GScamera* camera);
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* bank, s32 index, s32);
void GSparticleDestroyAllGenerators(GSparticleBank* bank, s32 children);
s32 GSparticleDestroyGenerator(s32, u8);
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
bool GSsndCheckEmitter(SndEmitter* e);
u8 GSsndClose(u32 id);
SndEmitter* GSsndCreateEmitterParam(u32 id, SVec* pos, SVec* dir, f32 maxDis, f32 comp, u8 maxVol, u8 minVol);
u8 GSsndFreeEmitter(SndEmitter* e);
s32 GSsndGetStatus(u32 id);
u8 GSsndPlay(u32 id, s32 time, u32 flag);
u8 GSsndUpdateEmitter(SndEmitter* e, SVec* pos);
void* GSthreadCreate(s32, s32, s32, s32, s32, void (*)(void));
bool GSthreadIsRunning(GSthread*);
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
struct XdBlob24 { u8 data[0x24]; };
extern XdBlob24 gCameraShakeModels;
s32 soundOpenPlayME(u32 id, s32 time, s32 vol);
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
GSthread* gSoundThread;

extern "C" {
extern s32 jtbl_2422;
}

extern "C++" {

extern "C++" {
extern "C++" {

}
}

extern "C++" {
#pragma push
#pragma dont_inline on
extern "C++" {

#pragma pop
}
}

}

extern "C++" {

extern "C++" {
extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {

static void _wazaCameraInitShake(WazaSequence* p0, int p1) {
    GSvec pos;
    GSvec rot;
    GSpart *temp_r3;

    if ((p0 == NULL) || ((u32) M2C_FIELD(p0, u32 *, 0x1C) != 0U)) {
        gCameraShakeModel = NULL;
        return;
    }
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
    cameraSetOffsetPosition(&pos);
    cameraSetOffsetRotation(&pos);
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
            GSpartGetTransform((GSpart*)(temp_r3), &pos, &rot, (GSvec*)(NULL));
            PSVECScale((const Vec*)&pos, (Vec*)&pos, 2.5f);
            cameraSetOffsetPosition(&pos);
            cameraSetOffsetRotation(&rot);
            GSpartFree((GSpart*)(temp_r3));
        }
    }
}
}

extern "C++" {
SequenceEntry::SequenceEntry(enumSequenceEntryDataType p0, WazaSequence* p1, unsigned char** p2) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    u8 *temp_r7;
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
SequenceEntry::~SequenceEntry() {
    if (child != 0) {
        delete child;
    }
}
}

extern "C++" {
MainSequenceEntry::MainSequenceEntry(WazaSequence* seq, unsigned char** data)
    : SequenceEntry((enumSequenceEntryDataType)0, seq, data) {
}
}

extern "C++" {
MainSequenceEntry::~MainSequenceEntry() {
}
}

extern "C++" {
s32 CameraEntry::Load(unsigned char** p0) {
    s32 temp_r0;
    u8 *temp_r4;

    *p0 += 0x70;
    temp_r4 = *p0;
    *p0 = temp_r4 + 0xC;
    temp_r0 = M2C_FIELD(temp_r4, s32 *, 0);
    if (temp_r0 != 3) {
        if (temp_r0 < 3) {

        }
    } else {
        *p0 += M2C_FIELD((u16)temp_r4, s32 *, 4) * 8;
    }
    return 1;
}
}

extern "C++" {
void CameraEntry::Unload(unsigned char** p0) {
    s32 temp_r0;
    u8 *temp_r4;

    *p0 += 0x70;
    temp_r4 = *p0;
    *p0 = temp_r4 + 0xC;
    temp_r0 = M2C_FIELD(temp_r4, s32 *, 0);
    if (temp_r0 != 3) {
        if (temp_r0 >= 3) {
            return;
        }
        return;
    }
    *p0 += M2C_FIELD(temp_r4, s32 *, 4) * 8;
}
}

extern "C++" {
CameraEntry::CameraEntry(WazaSequence* p0, unsigned char** p1)
    : SequenceEntry((enumSequenceEntryDataType)1, p0, p1) {
    s32 temp_r0;
    u8 *temp_r3;
    temp_r3 = *p1;
    *p1 = temp_r3 + 0xC;
    M2C_FIELD(this, s32 *, 0x30) = (s32) M2C_FIELD(temp_r3, s32 *, 0);
    temp_r0 = M2C_FIELD(this, s32 *, 0x30);
    switch (temp_r0) {
    case 0:
        M2C_FIELD(this, f32 *, 0x34) = (f32) M2C_FIELD(temp_r3, f32 *, 4);
        break;
    case 1:
        M2C_FIELD(this, u32 *, 0x34) = M2C_FIELD(temp_r3, u32 *, 4);
        break;
    case 2:
        M2C_FIELD(this, f32 *, 0x34) = (f32) M2C_FIELD(temp_r3, f32 *, 4);
        break;
    case 3:
        *p1 += M2C_FIELD(temp_r3, u32 *, 4) * 8;
        M2C_FIELD(this, s32 *, 0x30) = 0;
        M2C_FIELD(this, f32 *, 0x34) = 0.0f;
        break;
    }
    return;
}
}

extern "C++" {
CameraEntry::~CameraEntry() {
}
}

extern "C++" {
s32 ModelEntry::Load(unsigned char** p0) {
    u32 temp_r3;
    u8 *temp_r31;

    wazaSequenceSysGetResID();
    *p0 += 0x70;
    temp_r31 = *p0;
    *p0 = temp_r31 + 0x28;
    *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
    M2C_FIELD(temp_r31, u32 *, 0x20) = 0U;
    if ((s32) M2C_FIELD(temp_r31, s32 *, 0x1C) != 0) {
        temp_r3 = (unsigned long)(operator new(0x44U));
        if (temp_r3 != 0) {
            M2C_FIELD(temp_r31, u32 *, 0x20) = temp_r3;
            HSD_ArchiveParse((HSD_Archive*)((HSD_Archive *) temp_r3), (u8*)(*p0), (u32) M2C_FIELD(temp_r31, s32 *, 0x1C));
        }
        *p0 = &(*p0)[(M2C_FIELD(temp_r31, s32 *, 0x1C) + 0x1F) & 0xFFFFFFE0];
    }
    return 1;
}
}

extern "C++" {
void ModelEntry::Unload(unsigned char** p0) {
    s32 temp_r3_2;
    u8 *temp_r31;
    u8 *temp_r3;

    *p0 = *p0 + 0x70;
    temp_r31 = *p0;
    *p0 = temp_r31 + 0x28;
    *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
    temp_r3 = M2C_FIELD(temp_r31, u8 **, 0x20);
    if (temp_r3 != NULL) {
        operator delete((void*)(temp_r3));
        M2C_FIELD(temp_r31, u8 **, 0x20) = NULL;
    }
    temp_r3_2 = M2C_FIELD(temp_r31, s32 *, 0x1C);
    if (temp_r3_2 != 0) {
        *p0 = &(*p0)[(temp_r3_2 + 0x1F) & 0xFFFFFFE0];
    }
}
}

extern "C++" {
ModelEntry::ModelEntry(WazaSequence* p0, unsigned char** p1)
    : SequenceEntry((enumSequenceEntryDataType)2, p0, p1) {
    f32 spC;
    f32 sp8;
    HSD_Archive *temp_r3;
    _GSmodel *temp_r3_2;
    _GSmodel *temp_r3_4;
    f32 var_f31;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r28;
    s32 temp_r3_3;
    u8 *temp_r31;
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
    switch (temp_r0) {
    case 0:
        M2C_FIELD(this, s32 *, 0x34) = 0;
        break;
    case 1:
        M2C_FIELD(this, s32 *, 0x34) = 1;
        break;
    }
    M2C_FIELD(this, s32 *, 0x40) = (s32) M2C_FIELD(temp_r31, s32 *, 8);
    temp_r0_2 = M2C_FIELD(temp_r31, s32 *, 0xC);
    switch (temp_r0_2) {
    case 0:
        M2C_FIELD(this, s32 *, 0x3C) = 0;
        break;
    case 1:
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
        var_f31 = var_f31 >= sp8 ? var_f31 : sp8;
        M2C_FIELD((M2C_FIELD(this, s32 *, 0x14) + (M2C_FIELD(this, u8 *, 8) * 4)), f32 *, -4) = (f32) ((f32) (s32) var_f31 / (f32) GSgfxVideoGetVsyncRate());
    }
    return;
}
}

extern "C++" {
ModelEntry::~ModelEntry() {
    if (M2C_FIELD(this, u32 *, 0x30) != 0) {
        GSresFreeResource(0x4E20, M2C_FIELD(this, u32 *, 0x30));
    }
}
}

extern "C++" {
s32 ParticleEntry::Load(unsigned char** p0) {
    u8 *temp_r31;
    u8 *temp_r4;

    temp_r4 = *p0;
    *p0 = temp_r4 + 0x70;
    temp_r31 = *p0;
    *p0 = temp_r31 + 0x14;
    *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
    M2C_FIELD(temp_r31, s32 *, 0xC) = 0;
    if ((s32) M2C_FIELD(temp_r4, s32 *, 0x6C) == 0) {
        M2C_FIELD(temp_r31, s32 *, 0xC) = GSparticleLoad(*p0);
    }
    *p0 = &(*p0)[(M2C_FIELD(temp_r31, s32 *, 8) + 0x1F) & 0xFFFFFFE0];
    return 1;
}
}

extern "C++" {
void ParticleEntry::Unload(unsigned char** p0) {
    GSparticleBank *temp_r3;
    u8 *temp_r31;

    *p0 = *p0 + 0x70;
    temp_r31 = *p0;
    *p0 = temp_r31 + 0x14;
    *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
    temp_r3 = M2C_FIELD(temp_r31, GSparticleBank **, 0xC);
    if (temp_r3 != NULL) {
        GSparticleFree((GSparticleBank*)(temp_r3));
        M2C_FIELD(temp_r31, GSparticleBank **, 0xC) = NULL;
    }
    *p0 = &(*p0)[(M2C_FIELD(temp_r31, s32 *, 8) + 0x1F) & 0xFFFFFFE0];
}
}

extern "C++" {
ParticleEntry::ParticleEntry(WazaSequence* p0, unsigned char** p1)
    : SequenceEntry((enumSequenceEntryDataType)3, p0, p1) {
    u8 *temp_r31;
    u8 temp_r4;
    u8 *temp_r3;
    u8 *temp_ret;
    M2C_FIELD(this, s32 *, 0x3C) = 0;
    temp_r31 = *p1;
    *p1 = temp_r31 + 0x14;
    *p1 = (u8 *) ((s32) (*p1 + 0x1F) & 0xFFFFFFE0);
    *p1 = &(*p1)[(M2C_FIELD(temp_r31, s32 *, 8) + 0x1F) & 0xFFFFFFE0];
    temp_r4 = M2C_FIELD(this, u8 *, 9);
    if (temp_r4 != 0) {
        temp_r3 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4));
        if (temp_r3 != NULL) {
            M2C_FIELD(this, s32 *, 0x38) = (s32) M2C_FIELD(temp_r3, s32 *, 0x38);
        } else {
            GSlogWrite("particle waza entry not found");
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
ParticleEntry::~ParticleEntry() {
    if (unk09 == 0 && M2C_FIELD(this, GSparticleBank **, 0x38) != 0) {
        GSparticleDestroyAllGenerators(M2C_FIELD(this, GSparticleBank **, 0x38), 1);
    }
    M2C_FIELD(this, s32 *, 0x3C) = 0;
    M2C_FIELD(this, s32 *, 0x38) = 0;
}
}

extern "C++" {
s32 LensFlareEntry::Load(unsigned char** p0) {
    u8 *temp_r5;

    *p0 += 0x70;
    temp_r5 = *p0;
    *p0 = temp_r5 + 0x14;
    *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
    *p0 = &(*p0)[(*(u32*)temp_r5 + 0x1F) & 0xFFFFFFE0];
    return 1;
}
}

extern "C++" {
void LensFlareEntry::Unload(unsigned char** p0) {
    u8 *temp_r5;

    *p0 += 0x70;
    temp_r5 = *p0;
    *p0 = temp_r5 + 0x14;
    *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
    *p0 = &(*p0)[(*(u32*)temp_r5 + 0x1F) & 0xFFFFFFE0];
}
}

extern "C++" {
LensFlareEntry::LensFlareEntry(WazaSequence* p0, unsigned char** p1)
    : SequenceEntry((enumSequenceEntryDataType)7, p0, p1) {
    u8 *temp_r31;
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
LensFlareEntry::~LensFlareEntry() {
    GSlensFlareSetVisible(M2C_FIELD(this, u32 *, 0x30), 0);
    GSlensFlareFree(M2C_FIELD(this, u32 *, 0x30));
}
}

extern "C++" {
s32 EffectEntry::Load(unsigned char** p0) {
    s32 var_ctr;
    u32 temp_r0;
    u32 temp_r3_3;
    u32 temp_r3_6;
    u8 *temp_r30;
    u8 *temp_r30_2;
    u8 *temp_r30_3;
    u8 *temp_r3;
    u8 *temp_r3_4;
    u8 *temp_r3_5;
    u8 *temp_r4;
    u8 *var_r4;

    temp_r4 = *p0;
    *p0 = temp_r4 + 0x70;
    temp_r3 = *p0;
    *p0 = temp_r3 + 0xC;
    temp_r0 = M2C_FIELD(temp_r3, u32 *, 0);
    switch (temp_r0) {
    case 0:
        var_ctr = (M2C_FIELD((*p0), s32 *, 4));
        *p0 = (*p0) + 0x10;
        var_r4 = *p0;
        if ((M2C_FIELD((*p0), s32 *, 4)) > 0) {
            do {
                M2C_FIELD(var_r4, u8 *, 0) ^= M2C_FIELD(var_r4, u8 *, 3);
                M2C_FIELD(var_r4, u8 *, 3) = (u8) (M2C_FIELD(var_r4, u8 *, 3) ^ M2C_FIELD(var_r4, u8 *, 0));
                M2C_FIELD(var_r4, u8 *, 0) ^= M2C_FIELD(var_r4, u8 *, 3);
                M2C_FIELD(var_r4, u8 *, 1) = (u8) (M2C_FIELD(var_r4, u8 *, 1) ^ M2C_FIELD(var_r4, u8 *, 2));
                M2C_FIELD(var_r4, u8 *, 2) = (u8) (M2C_FIELD(var_r4, u8 *, 2) ^ M2C_FIELD(var_r4, u8 *, 1));
                M2C_FIELD(var_r4, u8 *, 1) = (u8) (M2C_FIELD(var_r4, u8 *, 1) ^ M2C_FIELD(var_r4, u8 *, 2));
                M2C_FIELD(var_r4, u8 *, 4) = (u8) (M2C_FIELD(var_r4, u8 *, 4) ^ M2C_FIELD(var_r4, u8 *, 7));
                M2C_FIELD(var_r4, u8 *, 7) = (u8) (M2C_FIELD(var_r4, u8 *, 7) ^ M2C_FIELD(var_r4, u8 *, 4));
                M2C_FIELD(var_r4, u8 *, 4) = (u8) (M2C_FIELD(var_r4, u8 *, 4) ^ M2C_FIELD(var_r4, u8 *, 7));
                M2C_FIELD(var_r4, u8 *, 5) = (u8) (M2C_FIELD(var_r4, u8 *, 5) ^ M2C_FIELD(var_r4, u8 *, 6));
                M2C_FIELD(var_r4, u8 *, 6) = (u8) (M2C_FIELD(var_r4, u8 *, 6) ^ M2C_FIELD(var_r4, u8 *, 5));
                M2C_FIELD(var_r4, u8 *, 5) = (u8) (M2C_FIELD(var_r4, u8 *, 5) ^ M2C_FIELD(var_r4, u8 *, 6));
                var_r4 += 0x10;
                var_ctr -= 1;
            } while (var_ctr != 0);
        }
        *p0 += M2C_FIELD((*p0), s32 *, 4) * 0x10;
block_21:
        return 1;
    case 5:
        temp_r30 = *p0;
        *p0 = temp_r30 + 0x40;
        *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
        M2C_FIELD(temp_r30, u32 *, 0x38) = 0U;
        if ((s32) M2C_FIELD(temp_r30, s32 *, 0x34) != 0) {
            temp_r3_3 = (unsigned long)(operator new(0x44U));
            if (temp_r3_3 != 0) {
                M2C_FIELD(temp_r30, u32 *, 0x38) = temp_r3_3;
                HSD_ArchiveParse((HSD_Archive*)((HSD_Archive *) temp_r3_3), (u8*)(*p0), (u32) M2C_FIELD(temp_r30, s32 *, 0x34));
            }
            *p0 = &(*p0)[(M2C_FIELD(temp_r30, s32 *, 0x34) + 0x1F) & 0xFFFFFFE0];
        }
        goto block_21;
    case 6:
        temp_r3_4 = *p0;
        *p0 = temp_r3_4 + 0x10;
        *p0 += M2C_FIELD(temp_r3_4, s32 *, 8) * 0x10;
        goto block_21;
    case 7:
        temp_r3_5 = *p0;
        *p0 = temp_r3_5 + 0xC;
        *p0 += M2C_FIELD(temp_r3_5, s32 *, 0) * 0x10;
        goto block_21;
    case 1:
        temp_r30_2 = *p0;
        *p0 = temp_r30_2 + 0x18;
        *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
        M2C_FIELD(temp_r30_2, s32 *, 0x10) = 0;
        if ((s32) M2C_FIELD(temp_r4, s32 *, 0x6C) == 0) {
            M2C_FIELD(temp_r30_2, s32 *, 0x10) = GSparticleLoad(*p0);
        }
        *p0 = &(*p0)[(M2C_FIELD(temp_r30_2, s32 *, 0xC) + 0x1F) & 0xFFFFFFE0];
        goto block_21;
    case 9:
        temp_r30_3 = *p0;
        *p0 = temp_r30_3 + 0x20;
        *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
        M2C_FIELD(temp_r30_3, s32 *, 4) = 0;
        if ((s32) M2C_FIELD(temp_r30_3, s32 *, 0) != 0) {
            temp_r3_6 = (unsigned long)(operator new(0x44U));
            if (temp_r3_6 != 0) {
                M2C_FIELD(temp_r30_3, s32 *, 4) = (s32) temp_r3_6;
                HSD_ArchiveParse((HSD_Archive*)((HSD_Archive *) temp_r3_6), (u8*)(*p0), (u32) M2C_FIELD(temp_r30_3, s32 *, 0));
            }
            *p0 = &(*p0)[(M2C_FIELD(temp_r30_3, s32 *, 0) + 0x1F) & 0xFFFFFFE0];
        }
        M2C_FIELD(temp_r30_3, s32 *, 0xC) = 0;
        if ((s32) M2C_FIELD(temp_r30_3, s32 *, 8) != 0) {
            M2C_FIELD(temp_r30_3, s32 *, 0xC) = GSparticleLoad(*p0);
            *p0 = &(*p0)[(M2C_FIELD(temp_r30_3, s32 *, 8) + 0x1F) & 0xFFFFFFE0];
        }
        goto block_21;
    default:
        return 0;
    }
}
}

struct EffectEntryHeader {
    u32 type;
    f32 time;
    u32 unk08;
};

EffectEntry::EffectEntry(WazaSequence* p0, unsigned char** p1) : SequenceEntry((enumSequenceEntryDataType)4, p0, p1) {
    EffectEntryHeader* hdr;
    f32* end;

    M2C_FIELD(this, GSeffect**, 0x30) = NULL;
    M2C_FIELD(this, u32*, 0x34) = 0;
    M2C_FIELD(this, f32*, 0x38) = 0.0f;
    M2C_FIELD(this, u8*, 0x3C) = 0;
    M2C_FIELD(this, u8*, 0x3D) = 0;
    M2C_FIELD(this, u8*, 0x40) = 0;
    hdr = (EffectEntryHeader*)*p1;
    M2C_FIELD(this, u8*, 0x41) = hdr->type;
    M2C_FIELD(this, f32*, 0x38) = hdr->time;
    *p1 += sizeof(EffectEntryHeader);
    switch (hdr->type) {
    case 0:
        filterEffectLoad(p1);
        break;
    case 6:
        envMapEffectLoad(p1);
        break;
    case 7:
        blurEffectLoad(p1);
        break;
    case 5:
        M2C_FIELD(this, GSeffect**, 0x30) = (GSeffect*)new leafEffect(p1, hdr->time);
        M2C_FIELD(this, u8*, 0x3D) = 1;
        M2C_FIELD(this, u8*, 0x3C) = 0;
        break;
    case 9:
        M2C_FIELD(this, GSeffect**, 0x30) = (GSeffect*)new billboardEffect(p1);
        M2C_FIELD(this, u8*, 0x3D) = 0;
        M2C_FIELD(this, u8*, 0x3C) = 0;
        break;
    case 1:
        boneFillEffectLoad(p1);
        M2C_FIELD(this, u8*, 0x3D) = 0;
        M2C_FIELD(this, u8*, 0x3C) = 0;
        break;
    }
    end = (f32*)params + unk08;
    if (end[-1] < 0.00001f) {
        end[-1] = hdr->time;
    }
}

extern "C++" {
EffectEntry::~EffectEntry() {
    if (M2C_FIELD(this, GSeffect **, 0x30) != 0) {
        delete M2C_FIELD(this, GSeffect **, 0x30);
    }
}
}

extern "C++" {
s32 EventEntry::Load(unsigned char** p0) {
    *p0 += 0x70;
    *p0 += 8;
    return 1;
}
}

extern "C++" {
void EventEntry::Unload(unsigned char** p0) {
    *p0 += 0x70;
    *p0 += 8;
}
}

extern "C++" {
EventEntry::EventEntry(WazaSequence* seq, unsigned char** data)
    : SequenceEntry((enumSequenceEntryDataType)6, seq, data) {
    *(u32*)((u8*)this + 0x30) = *(u32*)*data;
    *data += 8;
}
}

extern "C++" {
EventEntry::~EventEntry() {
}
}

extern "C++" {
s32 SoundEntry::Load(unsigned char** p0) {
    *p0 += 0x70;
    *p0 += 0x14;
    return 1;
}
}

extern "C++" {
void SoundEntry::Unload(unsigned char** p0) {
    *p0 += 0x70;
    *p0 += 0x14;
}
}

extern "C++" {
SoundEntry::SoundEntry(WazaSequence* p0, unsigned char** p1)
    : SequenceEntry((enumSequenceEntryDataType)5, p0, p1) {
    u8 *temp_r4;
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
SoundEntry::~SoundEntry() {
}
}

void SequenceEntry::SetRenderCamera(_GScamera* camera) {
}

extern "C++" {
s32 SequenceEntry::Start() {
    M2C_FIELD(this, s32 *, 0x18) = 1;
    M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
    return 1;
}
}

extern "C++" {
bool SequenceEntry::Update(float p0) {
    M2C_FIELD(this, f32 *, 0x20) = (f32) (M2C_FIELD(this, f32 *, 0x20) + p0);
    return 1;
}
}

void SequenceEntry::End() {
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
    volatile u16 tmp1 = M2C_FIELD(this, s32 *, 0x34);
    _wazaCameraInitShake((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)), (u8)tmp1);
block_8:
    M2C_FIELD(this, s32 *, 0x18) = 1;
    M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
    return 1;
}
}

extern "C++" {
bool CameraEntry::Update(float p0) {
    s32 unksp14;
    f32 unksp8;
    GSpart *temp_r3;
    s32 temp_r0;

    M2C_FIELD(this, f32 *, 0x20) = (f32) (M2C_FIELD(this, f32 *, 0x20) + p0);
    temp_r0 = M2C_FIELD(this, s32 *, 0x30);
    switch (temp_r0) {
    case 0:
        if ((M2C_FIELD(this, f32 *, 0x20) - M2C_FIELD(this, f32 *, 0x1C)) >= M2C_FIELD(this, f32 *, 0x34)) {
            M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), s8 *, 0x15) = 1;
            return 0;
        }
    case 2:    default:
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
void CameraEntry::Stop(bool p0) {
    volatile f32 sp10;
    f32 spC;
    volatile f32 sp8;
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
void ModelEntry::SetRenderCamera(_GScamera* camera) {
    _GSmodel* model = M2C_FIELD(this, _GSmodel **, 0x4C);
    if (model != NULL) {
        GSmodelSetRenderCamera(model, (GScamera*)camera);
    }
}
}

extern "C++" {
s32 ModelEntry::Start() {
    f32 sp30;
    s32 unksp24;
    s32 unksp18;
    f32 sp38;
    volatile f32 sp34;
    volatile f32 sp14;
    s32 unkspC;
    f32 sp10;
    s32 sp8;
    GSpart *temp_r27_3;
    GSpart *var_r30_2;
    ModelSequence *var_r30;
    ModelSequence *var_r3;
    s32 temp_r28;
    _GSmodel *temp_r27_2;
    _GSmodel *temp_r3_6;
    _GSmodel *var_r28;
    f32 *temp_r3_4;
    f32 temp_f1;
    WazaSequence *temp_r3;
    s32 temp_r30;
    s32 temp_r3_7;
    s32 var_r31;
    u16 temp_r3_3;
    u8 temp_r0;
    u8 temp_r4;
    u8 temp_r4_2;
    u8 *temp_r3_2;
    u8 *temp_r3_5;

    if ((_GSmodel *) M2C_FIELD(this, _GSmodel **, 0x4C) == NULL) {
        return 0;
    }
    temp_r28 = M2C_FIELD(temp_r3, s32 *, 8);
    temp_r3 = M2C_FIELD((u16)this, WazaSequence **, 0x2C);
    if (!(temp_r28 & 0x2000) && ((u8) M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 *, 6) == 0)) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
        M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
        return 1;
    }
    temp_r0 = M2C_FIELD(this, u8 *, 0x11);
    switch (temp_r0) {
    case 1:
        var_r31 = 1;
        break;
    case 2:
        var_r31 = 2;
        break;
    case 3:
        var_r31 = 3;
        break;
    case 4:
        var_r31 = 4;
        break;
    case 5:
        var_r31 = 5;
        break;
    case 6:
        var_r31 = 6;
        break;
    case 7:
        var_r31 = 7;
        break;
    default:
        var_r31 = 0;
        break;
    }
    if ((s32) M2C_FIELD((M2C_FIELD((s32)temp_r3, ModelSequence **, 0x24)), s32 *, 8) == 1) {
        var_r30 = (M2C_FIELD(temp_r3, ModelSequence **, 0x24));
    } else {
        var_r30 = NULL;
    }
    if (var_r30 != NULL) {
        M2C_FIELD(M2C_FIELD((M2C_FIELD((s32)temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, s32 *), 0x10)((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), &unksp18);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, s32 *), 0x14)((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), &unksp24);
        if (M2C_FIELD(this, u16 *, 0xA) & 1) {
            temp_r4 = M2C_FIELD(this, u8 *, 5);
            if ((temp_r4 != 0) && (temp_r4 != 0xFF)) {
                temp_r3_2 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4));
                if ((M2C_FIELD(temp_r3_2, f32 *, 0x1C) <= M2C_FIELD(this, f32 *, 0x1C)) && ((s32) M2C_FIELD(temp_r3_2, s32 *, 0xC) == 2)) {
                    temp_r27_2 = M2C_FIELD(temp_r3_2, _GSmodel **, 0x4C);
                    if (temp_r27_2 != NULL) {
                        GSmodelForceAnimTransformUpdate((_GSmodel*)(temp_r27_2));
                        GSmodelGetPosition((_GSmodel*)(temp_r27_2), (GSvec*)(&unksp18));
                        GSmodelGetRotation((_GSmodel*)(temp_r27_2), (GSvec*)(&unksp24));
                    }
                }
            }
        }
        temp_f1 = ((ModelSequence*)(var_r30))->GetModelScale((temp_r28 & 0x10000000) == 0);
        sp30 = temp_f1;
        sp34 = temp_f1;
        sp38 = temp_f1;
    } else {
        M2C_FIELD(M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, s32 *), 0x10)((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), &unksp18);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, s32 *), 0x14)((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), &unksp24);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, f32 *), 0x18)((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), &sp30);
    }
    if (M2C_FIELD(this, u16 *, 0xA) & 0x20) {
        sp38 = 1.0f;
        sp34 = 1.0f;
        sp30 = 1.0f;
    }
    var_r28 = NULL;
    M2C_FIELD(this, s8 *, 0x4B) = 0;
    temp_r3_3 = M2C_FIELD(this, u16 *, 0xA);
    if (temp_r3_3 & 4) {
        if (temp_r3_3 & 8) {
            battleGridGetNormalisedScale((GSvec*)((GSvec *) &sp30));
            if (M2C_FIELD(this, u16 *, 0xA) & 0x10) {
                sp34 = 1.0f;
            }
            GSmodelSetScale((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)((GSvec *) &sp30));
        }
    } else {
        if (var_r30 != NULL) {
            var_r28 = M2C_FIELD(var_r30, _GSmodel **, 0x94);
        }
        if (var_r31 != 0) {
            if ((u8) M2C_FIELD(this, u8 *, 0x4A) != 0) {
                temp_r27_3 = GSmodelGetPart((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), M2C_FIELD(this, s32 *, 0x44));
                GSmodelSetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp18));
                GSmodelSetRotation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp24));
                if ((var_r31 != 7) && (var_r31 != 3) && (var_r31 != 5) && (var_r31 != 6)) {
                    GSmodelSetScale((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)((GSvec *) &sp30));
                }
                if ((var_r28 != NULL) && ((u8) M2C_FIELD(var_r30, u8 *, 0x58) == 0) && (temp_r27_3 != NULL)) {
                    if (M2C_FIELD(this, u16 *, 0x48) & 0x10) {
                        temp_r3_4 = (float *)(GSmodelGetBound((_GSmodel*)(var_r28)));
                        GSboundGetWorldPosition(temp_r3_4);
                        GSmodelSetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unkspC));
                        GSboundGetLocalPosition((long)((s32) temp_r3_4), (float *)(&unkspC));
                        unkspC = -unkspC;
                        sp10 = -sp10;
                        sp14 = -sp14;
                        GSmodelAddNull((_GSmodel*)(var_r28), (Vec*)(&unkspC), (Vec*)(NULL), (Vec*)(NULL));
                    }
                    GSmodelAttachToGSpart((_GSmodel*)(var_r28), (GSpart*)(temp_r27_3), var_r31, 0U, 1U);
                    M2C_FIELD(var_r30, u8 *, 0x58) = 1U;
                    M2C_FIELD(this, s8 *, 0x4B) = 1;
                    GSpartFree((GSpart*)(temp_r27_3));
                    if ((u32) var_r31 <= 7U) {
                        switch (var_r31) {
                        case 1:
                        case 6:
                            GSmodelSetRotation((_GSmodel*)(var_r28), (GSvec*)(&unksp24));
                            break;
                        case 2:
                        case 5:
                            GSmodelSetPosition((_GSmodel*)(var_r28), (GSvec*)(&unksp18));
                            break;
                        case 3:
                            GSmodelSetRotation((_GSmodel*)(var_r28), (GSvec*)(&unksp24));
                            GSmodelSetPosition((_GSmodel*)(var_r28), (GSvec*)(&unksp18));
                            break;
                        case 0:
                            GSmodelSetRotation((_GSmodel*)(var_r28), (GSvec*)(&unksp24));
                            GSmodelSetPosition((_GSmodel*)(var_r28), (GSvec*)(&unksp18));
                            break;
                        }
                    }
                }
            } else {
                if (temp_r3_3 & 1) {
                    temp_r4_2 = M2C_FIELD(this, u8 *, 5);
                    if ((temp_r4_2 != 0) && (temp_r4_2 != 0xFF) && (temp_r3_5 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4_2)), (((s32) M2C_FIELD(temp_r3_5, s32 *, 0xC) == 2) != 0))) {
                        temp_r3_6 = M2C_FIELD(temp_r3_5, _GSmodel **, 0x4C);
                        if (M2C_FIELD(temp_r3_5, f32 *, 0x1C) > M2C_FIELD(this, f32 *, 0x1C)) {
                            var_r30_2 = NULL;
                        } else if (temp_r3_6 != NULL) {
                            var_r30_2 = GSmodelGetPart((_GSmodel*)(temp_r3_6), (s32) M2C_FIELD(this, s16 *, 0x12));
                        } else {
                            goto block_68;
                        }
                    } else {
                        goto block_68;
                    }
                } else {
                    var_r3 = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), ModelSequence **, 0x24);
                    var_r3 = (s32) M2C_FIELD(var_r3, s32 *, 8) == 1 ? var_r3 : NULL;
                    if (var_r3 != NULL) {
                        var_r30_2 = ((ModelSequence*)(var_r3))->GetPart((enumNullJointName)((s32) M2C_FIELD(this, u8 *, 0x10)));
                    } else {
block_68:
                        var_r30_2 = NULL;
                    }
                }
                if (var_r30_2 != NULL) {
                    GSmodelAttachToGSpart((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSpart*)(var_r30_2), var_r31, ((u16) M2C_FIELD(this, u16 *, 0xA) >> 1U) & 1, 1U);
                    M2C_FIELD(this, s8 *, 0x4B) = 1;
                    if ((u32) var_r31 <= 7U) {
                        switch (var_r31) {
                        case 4:
                            GSmodelSetScale((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)((GSvec *) &sp30));
                            break;
                        case 1:
                            GSmodelSetScale((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)((GSvec *) &sp30));
                            GSmodelSetRotation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp24));
                            break;
                        case 5:
                            GSmodelSetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp18));
                            break;
                        case 2:
                            GSmodelSetScale((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)((GSvec *) &sp30));
                            GSmodelSetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp18));
                            break;
                        case 6:
                            GSmodelSetRotation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp24));
                            break;
                        case 3:
                            GSmodelSetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp18));
                            GSmodelSetRotation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp24));
                            break;
                        }
                    }
                    GSpartFree((GSpart*)(var_r30_2));
                }
            }
        }
    }
    GSmodelSetVisibility((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 1U);
    GSmodelSetBoundCheck((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 0U);
    if (M2C_FIELD(this, u16 *, 0x48) & 1) {
        sp8 = jtbl_2422;
        GSmodelSetRenderLayer((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 1, (s32*)(&sp8));
    }
    if (M2C_FIELD(this, u16 *, 0x48) & 4) {
        GSmodelSet60fpsAnimFlag((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 1U);
    }
    if ((s32) M2C_FIELD(this, s32 *, 0x38) >= 0) {
        u8 cmpv = GSmodelCanAnimate((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)));
        if (cmpv != 0) {
            GSmodelSetAnimIndex((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (u32) M2C_FIELD(this, s32 *, 0x38));
            GSmodelSetAnimType((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), M2C_FIELD(this, s32 *, 0x34));
            GSmodelSetAnimRate((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 0.5f);
            GSmodelSetAnimFrame((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 0.0f);
            GSmodelStartAnimation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)));
        } else {
            M2C_FIELD(this, s32 *, 0x38) = -1;
        }
    }
    if (((s32) M2C_FIELD(this, s32 *, 0x38) != (temp_r3_7 = M2C_FIELD(this, s32 *, 0x40))) && (temp_r3_7 >= 0)) {
        u8 cmpv = GSmodelCanTexAnimate((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)));
        if (cmpv != 0) {
            GSmodelSetTexAnimIndex((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (u32) M2C_FIELD(this, s32 *, 0x40));
            GSmodelSetTexAnimType((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), M2C_FIELD(this, s32 *, 0x3C));
            GSmodelSetTexAnimRate((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 0.5f);
            GSmodelSetTexAnimFrame((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 0.0f);
            GSmodelStartTexAnimation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)));
        } else {
            M2C_FIELD(this, s32 *, 0x40) = -1;
        }
    }
    if ((M2C_FIELD(this, u16 *, 0x48) & 0x20) && (wazaSequenceSysGetModelShadowLight() != 0) && (wazaSequenceSysGetModelShadowCount() != 0)) {
        GSmodelSetShadowFlags((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), 1U);
        GSmodelSetShadowLight((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSlight*)(wazaSequenceSysGetModelShadowLight()));
        temp_r30 = wazaSequenceSysGetModelShadowList();
        GSmodelSetShadowSurface((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), wazaSequenceSysGetModelShadowCount(), (void*)((u8 *) temp_r30));
    }
    M2C_FIELD(this, s32 *, 0x18) = 1;
    M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
    return 1;
}
}

extern "C++" {
bool ModelEntry::Update(float p0) {
    s32 unksp20;
    s32 unksp14;
    volatile s32 temp_r0_2;
    volatile s32 temp_r0;
    s32 unksp8;
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
    if (((s32) M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), s32 *, 8) != 1) && !(M2C_FIELD(this, u16 *, 0xA) & 4) && ((u8) M2C_FIELD(this, u8 *, 0x4A) == 0) && ((u8) M2C_FIELD(this, u8 *, 0x4B) == 0)) {
        M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), SeqCameraTarget **, 0x24)->GetPosition((f32*)&unksp20);
        M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), SeqCameraTarget **, 0x24)->GetRotation((f32*)&unksp14);
        M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), SeqCameraTarget **, 0x24)->GetScale((f32*)&unksp8);
        GSmodelSetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp20));
        GSmodelSetRotation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp14));
        GSmodelSetScale((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp8));
    }
    if ((s32) M2C_FIELD(this, s32 *, 0x38) < 0) {
        var_r30 = 1;
    } else {
        if ((temp_r0 = M2C_FIELD(this, s32 *, 0x34)) != 1) {
            if (temp_r0 < 1) {

            }
            var_r30 = GSmodelHasAnimationEnded((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)));
        } else {
            M2C_ERROR( );
            var_r30 = ((u32) M2C_ERROR( ) >> 0x1DU) & 1;
        }
    }
    if (((s32) M2C_FIELD(this, s32 *, 0x38) != (temp_r3 = M2C_FIELD(this, s32 *, 0x40))) && (temp_r3 >= 0)) {
        if ((temp_r0_2 = M2C_FIELD(this, s32 *, 0x3C)) != 1) {
            if (temp_r0_2 < 1) {

            }
            var_r3 = GSmodelHasTexAnimationEnded((_GSmodel*)(M2C_FIELD((u16)this, _GSmodel **, 0x4C)));
        } else {
            M2C_ERROR( );
            var_r3 = ((u32) M2C_ERROR( ) >> 0x1DU) & 1;
        }
        var_r4 = 0;
        if (((u8) var_r30 != 0) && ((u8) var_r3 != 0)) {
            var_r4 = 1;
        }
        var_r30 = var_r4;
    }
    if ((u8) var_r30 != 0) {
        if (M2C_FIELD(this, u16 *, 0x48) & 2) {
            M2C_FIELD(this, s32 *, 0x18) = 3;
            return 1;
        }
        return 0;
    }
    return 1;
}
}

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
            if (p0) {
                return;
            }
            goto block_4;
        }
    } else {
block_4:
        M2C_FIELD((u16)this, s32 *, 0x18) = 2;
        temp_r3 = M2C_FIELD(this, _GSmodel **, 0x4C);
        if (temp_r3 != NULL) {
            var_r30 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), ModelSequence **, 0x24);
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
            if ((var_r29 != NULL) && ((u8) M2C_FIELD(this, u8 *, 0x4A) != 0)) {
                GSmodelGetPosition((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp20));
                GSmodelGetRotation((_GSmodel*)(M2C_FIELD(this, _GSmodel **, 0x4C)), (GSvec*)(&unksp14));
                GSmodelGetPosition((_GSmodel*)(var_r29), (GSvec*)(&unksp8));
                PSVECSubtract((const register Vec*)(&unksp8), (const register Vec*)(&unksp20), (register Vec*)(&unksp8));
                M2C_FIELD(var_r30, u8 *, 0x58) = 0;
                if ((u8) M2C_FIELD(this, u8 *, 0x4B) != 0) {
                    M2C_FIELD(this, u8 *, 0x4B) = 0U;
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
            if ((u8) M2C_FIELD(this, u8 *, 0x4B) != 0) {
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
void ParticleEntry::SetRenderCamera(_GScamera* camera) {
    if (M2C_FIELD(this, GSparticleBank **, 0x38) != 0) {
        GSparticleBankSetCamera(M2C_FIELD(this, GSparticleBank **, 0x38), camera);
    }
}
}

extern "C++" {
s32 ParticleEntry::Start() {
    s32 unksp14;
    s32 unksp20;
    volatile f32 sp10;
    s32 temp_r30_3;
    f32 sp8;
    GSpart *var_r27;
    GSparticleGenerator *temp_r3_3;
    ModelSequence *var_r29;
    ModelSequence *var_r3;
    WazaSequence *temp_r3;
    _GSmodel *temp_r30_2;
    _GSmodel *temp_r3_6;
    f32 temp_f1;
    s32 temp_r27;
    s32 temp_r29;
    s32 var_r31;
    f32 spC;
    u16 temp_r3_4;
    u32 temp_r0_2;
    u8 temp_r0;
    u8 temp_r4;
    u8 temp_r4_2;
    u8 *temp_r3_2;
    u8 *temp_r3_5;

    if ((GSparticleBank *) M2C_FIELD(this, GSparticleBank **, 0x38) == NULL) {
        return 0;
    }
    temp_r3 = M2C_FIELD(this, WazaSequence **, 0x2C);
    temp_r27 = M2C_FIELD((u16)temp_r3, s32 *, 8);
    if (!(temp_r27 & 0x2000) && ((u8) M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 *, 6) == 0)) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
        M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
        return 1;
    }
    temp_r0 = M2C_FIELD(this, u8 *, 0x11);
    switch (temp_r0) {
    case 1:
        var_r31 = 1;
        break;
    case 2:
        var_r31 = 2;
        break;
    case 3:
        var_r31 = 3;
        break;
    case 4:
        var_r31 = 4;
        break;
    case 5:
        var_r31 = 5;
        break;
    case 6:
        var_r31 = 6;
        break;
    case 7:
        var_r31 = 7;
        break;
    default:
        var_r31 = 0;
        break;
    }
    if ((s32) M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), s32 *, 8) == 1) {
        var_r29 = (M2C_FIELD(temp_r3, ModelSequence **, 0x24));
    } else {
        var_r29 = NULL;
    }
    if (var_r29 != NULL) {
        M2C_FIELD(M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, s32 *), 0x10)((M2C_FIELD((s32)temp_r3, ModelSequence **, 0x24)), &unksp20);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, s32 *), 0x14)((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), &unksp14);
        if (M2C_FIELD(this, u16 *, 0xA) & 1) {
            temp_r4 = M2C_FIELD(this, u8 *, 5);
            if ((temp_r4 != 0) && (temp_r4 != 0xFF)) {
                temp_r3_2 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4));
                if ((M2C_FIELD(temp_r3_2, f32 *, 0x1C) <= M2C_FIELD(this, f32 *, 0x1C)) && ((s32) M2C_FIELD(temp_r3_2, s32 *, 0xC) == 2)) {
                    temp_r30_2 = M2C_FIELD(temp_r3_2, _GSmodel **, 0x4C);
                    if (temp_r30_2 != NULL) {
                        GSmodelForceAnimTransformUpdate((_GSmodel*)(temp_r30_2));
                        GSmodelGetPosition((_GSmodel*)(temp_r30_2), (GSvec*)(&unksp20));
                        GSmodelGetRotation((_GSmodel*)(temp_r30_2), (GSvec*)(&unksp14));
                    }
                }
            }
        }
        temp_f1 = ((ModelSequence*)(var_r29))->GetModelScale((temp_r27 & 0x10000000) == 0);
        sp8 = temp_f1;
        spC = temp_f1;
        sp10 = temp_f1;
    } else {
        M2C_FIELD(M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, s32 *), 0x10)((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), &unksp20);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, s32 *), 0x14)((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), &unksp14);
        M2C_FIELD(M2C_FIELD((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), u8 **, 0), s32 (**)(ModelSequence *, f32 *), 0x18)((M2C_FIELD(temp_r3, ModelSequence **, 0x24)), &sp8);
    }
    if (M2C_FIELD(this, u16 *, 0xA) & 0x20) {
        sp10 = 1.0f;
        spC = 1.0f;
        sp8 = 1.0f;
    }
    M2C_FIELD(this, GSparticleGenerator **, 0x3C) = GSparticleCreateGenerator((GSparticleBank*)(M2C_FIELD(this, GSparticleBank **, 0x38)), M2C_FIELD(this, s32 *, 0x30), M2C_FIELD(this, u32 *, 0x34) & 1);
    M2C_FIELD(this, s32 *, 0x40) = 0;
    temp_r3_3 = M2C_FIELD(this, GSparticleGenerator **, 0x3C);
    if (temp_r3_3 == NULL) {
        return 0;
    }
    if (M2C_FIELD(this, u32 *, 0x34) & 4) {
        GSparticleSetOffsetRotationInLocal((s32) temp_r3_3, 1);
    }
    if (M2C_FIELD(this, u32 *, 0x34) & 8) {
        GSparticleSetVelocityRotationInLocal((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), 1);
    }
    if (M2C_FIELD(this, u32 *, 0x34) & 0x80) {
        GSparticleSetParticleTextureScaling((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), 1);
    }
    if (M2C_FIELD(this, u32 *, 0x34) & 0x800) {
        GSparticleSetNodeScaling((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), 1);
    }
    if (M2C_FIELD(this, u32 *, 0x34) & 0x1000) {
        GSparticleSetRandomVelocityScaling((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), 1);
    }
    temp_r0_2 = M2C_FIELD(this, u32 *, 0x34);
    temp_r30_3 = (temp_r0_2 >> 5U) & 1;
    temp_r29 = (temp_r0_2 >> 9U) & 1;
    GSparticleSetTornadoScaling((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), (temp_r0_2 >> 8U) & 1, (temp_r0_2 >> 0xAU) & 1);
    temp_r3_4 = M2C_FIELD(this, u16 *, 0xA);
    if (temp_r3_4 & 4) {
        GSparticleSetGeneratorPosition((GSparticleGenerator*)(M2C_FIELD(this, GSparticleGenerator **, 0x3C)), (Vec*)((Vec *) &zeroVector));
        GSparticleSetGeneratorRotation((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), (f32 *) &zeroVector);
        if (M2C_FIELD(this, u16 *, 0xA) & 8) {
            battleGridGetNormalisedScale((GSvec*)((GSvec *) &sp8));
            GSparticleSetGeneratorScale((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), &sp8, temp_r30_3, temp_r29);
        } else {
            spC = 1.0f;
            sp8 = 1.0f;
            GSparticleSetGeneratorScale((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), &sp8, temp_r30_3, temp_r29);
            sp10 = 1.0f;
        }
        M2C_FIELD(this, s32 *, 0x18) = 1;
        M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
        return 1;
    }
    if (temp_r3_4 & 1) {
        temp_r4_2 = M2C_FIELD(this, u8 *, 5);
        if ((temp_r4_2 != 0) && (temp_r4_2 != 0xFF) && (temp_r3_5 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4_2)), (((s32) M2C_FIELD(temp_r3_5, s32 *, 0xC) == 2) != 0))) {
            temp_r3_6 = M2C_FIELD(temp_r3_5, _GSmodel **, 0x4C);
            if (M2C_FIELD(temp_r3_5, f32 *, 0x1C) > M2C_FIELD(this, f32 *, 0x1C)) {
                var_r27 = NULL;
            } else if (temp_r3_6 != NULL) {
                var_r27 = GSmodelGetPart((_GSmodel*)(temp_r3_6), (s32) M2C_FIELD(this, s16 *, 0x12));
            } else {
                goto block_60;
            }
        } else {
            goto block_60;
        }
    } else {
        var_r3 = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), ModelSequence **, 0x24);
        var_r3 = (s32) M2C_FIELD(var_r3, s32 *, 8) == 1 ? var_r3 : NULL;
        if (var_r3 != NULL) {
            var_r27 = ((ModelSequence*)(var_r3))->GetPart((enumNullJointName)((s32) M2C_FIELD(this, u8 *, 0x10)));
        } else {
block_60:
            var_r27 = NULL;
        }
    }
    if (var_r27 != NULL) {
        if (var_r31 != 0) {
            GSparticleAttachGeneratorToGSpart((unsigned long)((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C)), (float *)((u32) var_r27), (long)(var_r31), (long)(((u16) M2C_FIELD(this, u16 *, 0xA) >> 1U) & 1), (long)(1), (long)(((u32) M2C_FIELD(this, u32 *, 0x34) >> 1U) & 1));
            M2C_FIELD(this, s32 *, 0x40) = 1;
            if ((u32) var_r31 <= 7U) {
                switch (var_r31) {
                case 1:
                    GSparticleSetGeneratorRotation((unsigned long)((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C)), (float *)(&unksp14));
                case 4:
                    GSparticleSetGeneratorScale((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), &sp8, temp_r30_3, temp_r29);
                    break;
                case 2:
                    GSparticleSetGeneratorScale((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), &sp8, temp_r30_3, temp_r29);
                case 5:
                    GSparticleSetGeneratorPosition((GSparticleGenerator*)(M2C_FIELD(this, GSparticleGenerator **, 0x3C)), (Vec*)(&unksp20));
                    break;
                case 3:
                    GSparticleSetGeneratorPosition((GSparticleGenerator*)(M2C_FIELD(this, GSparticleGenerator **, 0x3C)), (Vec*)(&unksp20));
                case 6:
                    GSparticleSetGeneratorRotation((unsigned long)((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C)), (float *)(&unksp14));
                    break;
                }
            }
        }
        GSpartFree((GSpart*)(var_r27));
    } else {
        GSparticleSetGeneratorPosition((GSparticleGenerator*)(M2C_FIELD(this, GSparticleGenerator **, 0x3C)), (Vec*)(&unksp20));
        GSparticleSetGeneratorRotation((unsigned long)((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C)), (float *)(&unksp14));
        GSparticleSetGeneratorScale((u32) M2C_FIELD(this, GSparticleGenerator **, 0x3C), &sp8, temp_r30_3, temp_r29);
    }
    M2C_FIELD(this, s32 *, 0x18) = 1;
    M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
    return 1;
}
}

extern "C++" {
bool ParticleEntry::Update(float p0) {
    enum TsE { TsE0 };
    s32 unksp20;
    f32 sp14;
    f32 sp8;
    enum TsE temp_r30;
    u32 temp_r31_2;

    M2C_FIELD(this, f32 *, 0x20) = (f32) (M2C_FIELD(this, f32 *, 0x20) + p0);
    if (GSparticleIsGeneratorAlive(M2C_FIELD(this, u32 *, 0x3C)) == 0) {
        M2C_FIELD(this, u32 *, 0x3C) = 0U;
        return 0;
    }
    if (((s32) M2C_FIELD((M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), u8 **, 0x24)), s32 *, 8) != 1) && !(M2C_FIELD(this, u16 *, 0xA) & 4) && ((s32) (u16)M2C_FIELD(this, s32 *, 0x40) == 0)) {
        M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), SeqCameraTarget **, 0x24)->GetPosition((f32*)&unksp20);
        M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), SeqCameraTarget **, 0x24)->GetRotation((f32*)&sp14);
        M2C_FIELD(M2C_FIELD(this, u8 **, 0x2C), SeqCameraTarget **, 0x24)->GetScale((f32*)&sp8);
        temp_r31_2 = M2C_FIELD(this, u32 *, 0x34);
        temp_r30 = (enum TsE)((temp_r31_2 >> 5U) & 1);
        GSparticleSetGeneratorPosition((GSparticleGenerator*)((GSparticleGenerator *) M2C_FIELD(this, u32 *, 0x3C)), (Vec*)(&unksp20));
        GSparticleSetGeneratorRotation(M2C_FIELD(this, u32 *, 0x3C), &sp14);
        GSparticleSetGeneratorScale(M2C_FIELD(this, u32 *, 0x3C), &sp8, temp_r30, (temp_r31_2 >> 9U) & 1);
    }
    return 1;
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
void ParticleEntry::Stop(bool p0) {
    s32 temp_r3;
    u32 temp_r3_2;

    temp_r3 = M2C_FIELD(this, s32 *, 0x18);
    if ((temp_r3 != 2) && ((p0 != 0) || (temp_r3 == 1))) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
        temp_r3_2 = M2C_FIELD(this, u32 *, 0x3C);
        if (temp_r3_2 != 0U) {
            GSparticleDestroyGenerator((s32) temp_r3_2, 1);
        }
        M2C_FIELD(this, u32 *, 0x3C) = 0U;
    }
}
}

extern "C++" {
s32 LensFlareEntry::Start() {
    GSvec pos;
    GSpart *var_r30;
    ModelSequence *var_r3;
    WazaSequence *temp_r3;
    _GSmodel *temp_r3_4;
    u8 temp_r4;
    u8 *temp_r3_2;
    u8 *temp_r3_3;

    temp_r3 = M2C_FIELD(this, WazaSequence **, 0x2C);
    temp_r3_2 = M2C_FIELD(temp_r3, u8 **, 0x24);
    if (!(M2C_FIELD(temp_r3, s32 *, 8) & 0x2000) && ((u8) M2C_FIELD(temp_r3_2, u8 *, 6) == 0)) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
        M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
        return 1;
    }
    ((ModelSequence*)temp_r3_2)->GetPosition(&pos);
    if (M2C_FIELD(this, u16 *, 0xA) & 1) {
        temp_r4 = M2C_FIELD(this, u8 *, 5);
        if ((temp_r4 != 0) && (temp_r4 != 0xFF) && (temp_r3_3 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4)), (((s32) M2C_FIELD(temp_r3_3, s32 *, 0xC) == 2) != 0))) {
            temp_r3_4 = M2C_FIELD(temp_r3_3, _GSmodel **, 0x4C);
            if (M2C_FIELD(temp_r3_3, f32 *, 0x1C) > M2C_FIELD(this, f32 *, 0x1C)) {
                var_r30 = NULL;
            } else if (temp_r3_4 != NULL) {
                var_r30 = GSmodelGetPart((_GSmodel*)(temp_r3_4), (s32) M2C_FIELD(this, s16 *, 0x12));
            } else {
                goto block_16;
            }
        } else {
            goto block_16;
        }
    } else {
        var_r3 = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), ModelSequence **, 0x24);
        var_r3 = (s32) M2C_FIELD(var_r3, s32 *, 8) == 1 ? var_r3 : NULL;
        if (var_r3 != NULL) {
            var_r30 = ((ModelSequence*)(var_r3))->GetPart((enumNullJointName)((s32) M2C_FIELD(this, u8 *, 0x10)));
        } else {
block_16:
            var_r30 = NULL;
        }
    }
    if (var_r30 != NULL) {
        GSpartGetTransform((GSpart*)(var_r30), &pos, (GSvec*)(NULL), (GSvec*)(NULL));
        GSpartFree((GSpart*)(var_r30));
    }
    GSlensFlareSetSunPosition(M2C_FIELD(this, u32 *, 0x30), (Vec*)&pos);
    GSlensFlareSetVisible(M2C_FIELD(this, u32 *, 0x30), 1U);
    M2C_FIELD(this, s32 *, 0x18) = 1;
    M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
    return 1;
}
}

extern "C++" {
bool LensFlareEntry::Update(f32 p0) {
    GSvec pos;
    GSpart *var_r31;
    ModelSequence *temp_r3;
    ModelSequence *var_r3;
    _GSmodel *temp_r3_3;
    u8 temp_r4;
    u8 *temp_r3_2;

    M2C_FIELD(this, f32 *, 0x20) = (f32) (M2C_FIELD(this, f32 *, 0x20) + p0);
    if ((M2C_FIELD(this, f32 *, 0x20) - M2C_FIELD(this, f32 *, 0x1C)) >= M2C_FIELD(this, f32 *, 0x34)) {
        return 0;
    }
    temp_r3 = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), ModelSequence **, 0x24);
    temp_r3->GetPosition(&pos);
    if (M2C_FIELD(this, u16 *, 0xA) & 1) {
        temp_r4 = M2C_FIELD(this, u8 *, 5);
        if ((temp_r4 != 0) && (temp_r4 != 0xFF) && (temp_r3_2 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4)), (((s32) M2C_FIELD(temp_r3_2, s32 *, 0xC) == 2) != 0))) {
            temp_r3_3 = M2C_FIELD(temp_r3_2, _GSmodel **, 0x4C);
            if (M2C_FIELD(temp_r3_2, f32 *, 0x1C) > M2C_FIELD(this, f32 *, 0x1C)) {
                var_r31 = NULL;
            } else if (temp_r3_3 != NULL) {
                var_r31 = GSmodelGetPart((_GSmodel*)(temp_r3_3), (s32) M2C_FIELD(this, s16 *, 0x12));
            } else {
                goto block_15;
            }
        } else {
            goto block_15;
        }
    } else {
        var_r3 = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), ModelSequence **, 0x24);
        var_r3 = (s32) M2C_FIELD(var_r3, s32 *, 8) == 1 ? var_r3 : NULL;
        if (var_r3 != NULL) {
            var_r31 = ((ModelSequence*)(var_r3))->GetPart((enumNullJointName)((s32) M2C_FIELD(this, u8 *, 0x10)));
        } else {
block_15:
            var_r31 = NULL;
        }
    }
    if (var_r31 != NULL) {
        GSpartGetTransform((GSpart*)(var_r31), &pos, (GSvec*)(NULL), (GSvec*)(NULL));
        GSpartFree((GSpart*)(var_r31));
    }
    GSlensFlareSetSunPosition(M2C_FIELD(this, u32 *, 0x30), (Vec*)&pos);
    return 1;
}
}

extern "C++" {
void LensFlareEntry::Stop(bool p0) {
    GSlensFlareSetVisible(M2C_FIELD(((s32)this), u32 *, 0x30), 0U);
}
}

extern "C++" {
s32 EffectEntry::Start() {
    f32 v8[3];
    u8 var_r3;
    GSeffect *temp_r4_2;
    GSeffect *temp_r4_3;
    GSeffect *temp_r5;
    GSpart *var_r29_2;
    ModelSequence *temp_r31;
    ModelSequence *var_r30;
    ModelSequence *var_r3_2;
    _GSmodel *temp_r3_4;
    f32 var_f31;
    s32 temp_r3;
    s32 var_r29;
    u8 temp_r0;
    u8 temp_r3_2;
    u8 temp_r4_4;
    u8 var_r0;
    GSeffect *temp_r30;
    u8 *temp_r3_3;
    u8 *temp_r4;

    temp_r31 = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), ModelSequence **, 0x24);
    if ((s32) M2C_FIELD(temp_r31, s32 *, 8) == 1) {
        var_r30 = temp_r31;
    } else {
        var_r30 = NULL;
    }
    var_r29 = 0;
    var_f31 = 1.0f;
    if ((GSeffect *) M2C_FIELD(this, GSeffect **, 0x30) == NULL) {
        return 0;
    }
    if ((u8) M2C_FIELD(this, u8 *, 0x40) != 0) {
        if (((u32) M2C_FIELD(this, u32 *, 0x34) == 0U) || ((u8) M2C_FIELD(this, u8 *, 0x3C) == 0)) {
            return 0;
        }
        M2C_FIELD(this, f32 *, 0x38) = 0.0f;
        M2C_FIELD(this, u8 *, 0x3D) = 0U;
        goto block_11;
    }
    M2C_FIELD(this, u32 *, 0x34) = 0.0f;
block_11:
    temp_r3 = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), s32 *, 8);
    if (!(temp_r3 & 0x2000) && ((u8) M2C_FIELD(temp_r31, u8 *, 6) == 0)) {
        M2C_FIELD(this, s32 *, 0x18) = 2;
        M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
        return 1;
    }
    if (var_r30 != NULL) {
        var_r29 = M2C_FIELD(var_r30, s32 *, 0x94);
        var_f31 = ((ModelSequence*)(var_r30))->GetModelScale((temp_r3 & 0x10000000) == 0);
    }
    temp_r3_2 = M2C_FIELD(this, u8 *, 0x41);
    switch (temp_r3_2) {
    case 0:
        temp_r5 = M2C_FIELD(this, GSeffect **, 0x30);
        if ((u8) M2C_FIELD(temp_r5, u8 *, 0x18) == 2) {
            M2C_FIELD(temp_r5, s32 *, 0xC) = var_r29;
        }
        if ((var_r30 != NULL) && ((u8) M2C_FIELD((u16)temp_r5, u8 *, 0x18) == 2)) {
            M2C_FIELD(temp_r5, u8 *, 0x15) = (u8) M2C_FIELD(var_r30, u8 *, 0x60);
        }
        temp_r4 = (unsigned char *)(M2C_FIELD(this, u32 *, 0x34) + (M2C_FIELD(this, u8 *, 0x3D) * 0x10));
        M2C_FIELD(temp_r5, u8 *, 0x19) = (u8) M2C_FIELD(temp_r4, u8 *, 0);
        M2C_FIELD(temp_r5, u8 *, 0x1A) = (u8) M2C_FIELD(temp_r4, u8 *, 1);
        M2C_FIELD(temp_r5, u8 *, 0x1B) = (u8) M2C_FIELD(temp_r4, u8 *, 2);
        var_r3 = !(((u8) M2C_FIELD(temp_r5, u8 *, 0x18) == 0) || ((u8) M2C_FIELD(temp_r5, u8 *, 0x14) != 0)) ? var_r3 : 1;
        var_r3 = 0;
        if (var_r3 != 0) {
            var_r0 = M2C_FIELD(temp_r4, u8 *, 3);
        } else {
            var_r0 = 0xFF;
        }
        M2C_FIELD(temp_r5, u8 *, 0x1C) = var_r0;
    case 1:
block_59:
        if (((GSeffect*)(M2C_FIELD((u16)this, GSeffect **, 0x30)))->Start() == 0) {
            return 0;
        }
        M2C_FIELD(this, s32 *, 0x18) = 1;
        M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
        return 1;
    case 6:
        temp_r4_2 = M2C_FIELD(this, GSeffect **, 0x30);
        if (var_r30 == NULL) {
            return 0;
        }
        M2C_FIELD(temp_r4_2, s32 *, 0xC) = var_r29;
        M2C_FIELD(temp_r4_2, u8 *, 0x18) = *(M2C_FIELD(this, u32 **, 0x34) + (M2C_FIELD(this, u8 *, 0x3D) * 0x10));
        goto block_59;
    case 7:
        temp_r4_3 = M2C_FIELD(this, GSeffect **, 0x30);
        temp_r0 = M2C_FIELD(temp_r4_3, u8 *, 0x14);
        if (temp_r0 == 0) {
            if (var_r30 == NULL) {
                return 0;
            }
            if (temp_r0 == 0) {
                M2C_FIELD(temp_r4_3, s32 *, 0xC) = var_r29;
            }
            goto block_38;
        }
block_38:
        M2C_FIELD(temp_r4_3, u8 *, 0x18) = *(M2C_FIELD(this, u32 **, 0x34) + (M2C_FIELD(this, u8 *, 0x3D) * 0x10));
        goto block_59;
    case 5:
        temp_r30 = M2C_FIELD(this, GSeffect **, 0x30);
        if (M2C_FIELD(this, u16 *, 0xA) & 1) {
            temp_r4_4 = M2C_FIELD(this, u8 *, 5);
            if ((temp_r4_4 != 0) && (temp_r4_4 != 0xFF) && (temp_r3_3 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4_4)), (((s32) M2C_FIELD(temp_r3_3, s32 *, 0xC) == 2) != 0))) {
                temp_r3_4 = M2C_FIELD(temp_r3_3, _GSmodel **, 0x4C);
                if (M2C_FIELD(temp_r3_3, f32 *, 0x1C) > M2C_FIELD(this, f32 *, 0x1C)) {
                    var_r29_2 = NULL;
                } else if (temp_r3_4 != NULL) {
                    var_r29_2 = GSmodelGetPart((_GSmodel*)(temp_r3_4), (s32) M2C_FIELD(this, s16 *, 0x12));
                } else {
                    goto block_52;
                }
            } else {
                goto block_52;
            }
        } else {
            var_r3_2 = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), ModelSequence **, 0x24);
            var_r3_2 = (s32) M2C_FIELD(var_r3_2, s32 *, 8) == 1 ? var_r3_2 : NULL;
            if (var_r3_2 != NULL) {
                var_r29_2 = ((ModelSequence*)(var_r3_2))->GetPart((enumNullJointName)((s32) M2C_FIELD(this, u8 *, 0x10)));
            } else {
block_52:
                var_r29_2 = NULL;
            }
        }
        if (var_r29_2 != NULL) {
            GSpartGetTransform((GSpart*)(var_r29_2), (GSvec*)(v8), (GSvec*)(NULL), (GSvec*)(NULL));
            GSpartFree((GSpart*)(var_r29_2));
        } else {
            M2C_FIELD(M2C_FIELD(temp_r31, u8 **, 0), s32 (**)(ModelSequence *, s32 *), 0x10)(temp_r31, (long *)(v8));
        }
        M2C_FIELD(temp_r30, f32 *, 0x54) = v8[0];
        M2C_FIELD(temp_r30, f32 *, 0x58) = v8[1];
        M2C_FIELD(temp_r30, f32 *, 0x5C) = v8[2];
        M2C_FIELD(temp_r30, f32 *, 0x14) = var_f31;
        goto block_59;
    case -1:
    case 2:
    case 3:
    case 4:
    case 8:
        M2C_FIELD(M2C_FIELD((u8)this, GSeffect **, 0x30), u8 *, 0x14) = (unsigned char)(var_r30);
        goto block_59;
    case 9:
    default:
        return 0;
    }
}
}

extern "C++" {
inline u8 EffectLerp(f32 t, f32 from, f32 to) {
    return t * (to - from) + from;
}

bool EffectEntry::Update(f32 dt) {
    f32 t;

    unk20 += dt;
    if (m_effect == NULL) {
        return false;
    }
    if (!m_effect->m_active) {
        return false;
    }
    if (m_keyed) {
        if (m_keys == NULL || m_keyCount == 0) {
            return false;
        }
        m_time += dt;
        if (m_keys[m_curKey].duration >= 0.0f) {
            while (m_time >= m_keys[m_curKey].duration) {
                m_time -= m_keys[m_curKey].duration;
                m_curKey++;
                if (m_curKey >= m_keyCount) {
                    m_effect->Stop();
                    return false;
                }
                if (m_keys[m_curKey].duration < 0.0f) {
                    m_time = 0.0f;
                    break;
                }
            }
            if (m_keys[m_curKey].duration > 0.0f) {
                t = m_time / m_keys[m_curKey].duration;
            } else {
                t = 1.0f;
            }
        } else {
            unk18 = 3;
        }
    } else {
        t = 1.0f;
        m_elapsed += dt;
        if (m_keyCount != 0) {
            unk18 = 3;
        } else if (m_curKey != 0) {
            if (m_elapsed >= m_time) {
                return false;
            }
            t = m_elapsed / m_time;
        }
    }
    switch (m_type) {
    case 0: {
        EffectKey* key = &m_keys[m_curKey];
        u8* fx = (u8*)m_effect;
        f32 a = t;
        bool useAlpha;
        u8 r, g, b, alpha;

        if (t < 0.0f) {
            a = 0.0f;
        }
        if (a > 1.0f) {
            a = 1.0f;
        }
        r = EffectLerp(a, key->color.from[0], key->color.to[0]);
        g = EffectLerp(a, key->color.from[1], key->color.to[1]);
        b = EffectLerp(a, key->color.from[2], key->color.to[2]);
        alpha = EffectLerp(a, key->color.from[3], key->color.to[3]);
        fx[0x19] = r;
        fx[0x1A] = g;
        fx[0x1B] = b;
        useAlpha = false;
        if (fx[0x18] == 0 || fx[0x14] != 0) {
            useAlpha = true;
        }
        fx[0x1C] = useAlpha ? alpha : 0xFF;
        break;
    }
    case 6: {
        EffectKey* key = &m_keys[m_curKey];
        *(f32*)((u8*)m_effect + 0x18) = t * (key->value.to - key->value.from) + key->value.from;
        break;
    }
    case 7: {
        EffectKey* key = &m_keys[m_curKey];
        *(f32*)((u8*)m_effect + 0x18) = t * (key->value.to - key->value.from) + key->value.from;
        break;
    }
    case 1:
    case 5:
    case 9:
        break;
    case -1:
    default:
        return false;
    }
    return true;
}
}

void EffectEntry::End() {
    u8* keys;
    if (*((u8*)this + 0x40) != 0 && *(u8**)((u8*)this + 0x34) != NULL) {
        if (*((u8*)this + 0x3C) != 0) {
            while (*(f32*)(*(u8**)((u8*)this + 0x34) + *((u8*)this + 0x3D) * 0x10 + 8) < 0.0f) {
                (*((u8*)this + 0x3D))++;
                if (*((u8*)this + 0x3D) >= *((u8*)this + 0x3C)) {
                    return;
                }
            }
        }
    }
}

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
s32 SoundEntry::Start() {
    GSvec pos;
    GSvec rot;
    _GSmodel *temp_r30_2;
    f32 var_f31;
    s32 temp_r0;
    u16 temp_r3;
    u8 temp_r4;
    u8 *temp_r3_2;
    u8 *temp_r3_3;
    u8 *temp_ret;

    temp_r3 = M2C_FIELD(this, u16 *, 0x34);
    if (temp_r3 & 1) {
        if ((u8 *) gSoundThread != NULL) {
            return 0;
        }
        temp_ret = (unsigned char *)(GSthreadCreate(0x15, 0x4E20, 0x2000, 1, 1, (void (*)(void))soundOpenPlayME));
        temp_r3_2 = temp_ret;
        gSoundThread = (GSthread *)(temp_r3_2);
        if (temp_r3_2 != NULL) {
            GSthreadSetArgs((void*)(temp_r3_2), 3, M2C_FIELD(this, u32 *, 0x30), 0, 0xFF);
            M2C_FIELD(this, s32 *, 0x18) = 1;
            M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
            return 1;
        }
        goto block_24;
    }
    if (temp_r3 & 2) {
        temp_r0 = temp_r3 & 0xC;
        switch (temp_r0) {
        case 4:
            var_f31 = -1.0f;
            break;
        case 12:
            var_f31 = 1.0f;
            break;
        default:
        case 8:
            var_f31 = 0.0f;
            break;
        }
        ModelSequence* ms = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), ModelSequence **, 0x24);
        ms->GetPosition(&pos);
        ms->GetRotation(&rot);
        if (M2C_FIELD(this, u16 *, 0xA) & 1) {
            temp_r4 = M2C_FIELD(this, u8 *, 5);
            if ((temp_r4 != 0) && (temp_r4 != 0xFF)) {
                temp_r3_3 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4));
                if ((M2C_FIELD(temp_r3_3, f32 *, 0x1C) <= M2C_FIELD(this, f32 *, 0x1C)) && ((s32) M2C_FIELD(temp_r3_3, s32 *, 0xC) == 2)) {
                    temp_r30_2 = M2C_FIELD(temp_r3_3, _GSmodel **, 0x4C);
                    if (temp_r30_2 != NULL) {
                        GSmodelForceAnimTransformUpdate((_GSmodel*)(temp_r30_2));
                        GSmodelGetPosition((_GSmodel*)(temp_r30_2), &pos);
                        GSmodelGetRotation((_GSmodel*)(temp_r30_2), &rot);
                    }
                }
            }
        }
        M2C_FIELD(this, SndEmitter **, 0x3C) = GSsndCreateEmitterParam(M2C_FIELD(this, u32 *, 0x30), (SVec*)&pos, (SVec*)(&zeroVector), M2C_FIELD(this, f32 *, 0x38), var_f31, 0x7FU, M2C_FIELD(this, u8 *, 0x36));
        if ((SndEmitter *) M2C_FIELD(this, SndEmitter **, 0x3C) != NULL) {
            M2C_FIELD(this, s32 *, 0x18) = 1;
            M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
            return 1;
        }
        goto block_24;
    }
block_24:
    if (GSsndPlay(M2C_FIELD(this, u32 *, 0x30), 0, 0U) != 0) {
        M2C_FIELD(this, s32 *, 0x18) = 1;
        M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
        return 1;
    }
    return 0;
}
}

extern "C++" {

bool SoundEntry::Update(float p0) {
    f32 pos[3];
    f32 rot[3];
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
        SeqCameraTarget* cam = M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), SeqCameraTarget **, 0x24);
        cam->GetPosition(pos);
        cam->GetRotation(rot);
        if (M2C_FIELD(this, u16 *, 0xA) & 1) {
            temp_r4 = M2C_FIELD(this, u8 *, 5);
            if ((temp_r4 != 0) && (temp_r4 != 0xFF)) {
                temp_r3 = (unsigned char *)(((WazaSequence*)(M2C_FIELD(this, WazaSequence **, 0x2C)))->GetEntryFromID(temp_r4));
                if ((M2C_FIELD(temp_r3, f32 *, 0x1C) <= M2C_FIELD(this, f32 *, 0x1C)) && ((s32) M2C_FIELD(temp_r3, s32 *, 0xC) == 2)) {
                    temp_r31_2 = M2C_FIELD(temp_r3, _GSmodel **, 0x4C);
                    if (temp_r31_2 != NULL) {
                        GSmodelForceAnimTransformUpdate((_GSmodel*)(temp_r31_2));
                        GSmodelGetPosition((_GSmodel*)(temp_r31_2), (GSvec*)pos);
                        GSmodelGetRotation((_GSmodel*)(temp_r31_2), (GSvec*)rot);
                    }
                }
            }
        }
        if (GSsndUpdateEmitter((SndEmitter*)(M2C_FIELD(this, SndEmitter **, 0x3C)), (SVec*)pos) != 0) {
            return GSsndCheckEmitter((SndEmitter*)(M2C_FIELD(this, SndEmitter **, 0x3C)));
        }
        return 0;
    }
    temp_r4_2 = GSsndGetStatus(M2C_FIELD(this, u32 *, 0x30));
    return temp_r4_2 == 2 || temp_r4_2 == 3;
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

s32 EventEntry::Start() {
    ModelSequence* target = M2C_FIELD(seq, ModelSequence**, 0x24);
    ModelSequence* model;

    if (M2C_FIELD(target, s32*, 8) == 1) {
        model = target;
    } else {
        model = NULL;
    }
    switch (M2C_FIELD(this, u32*, 0x30)) {
    case 0:
        if (model != NULL) {
            model->Sleep();
        }
        break;
    case 1:
        if (model != NULL) {
            model->WakeUp();
        }
        break;
    case 2:
        target->SetVisibility(false);
        break;
    case 3:
        target->SetVisibility(true);
        break;
    case 4:
        if (model != NULL) {
            GSmodelRemoveNull(M2C_FIELD(model, _GSmodel**, 0x94));
        }
        break;
    case 5:
        if (model != NULL) {
            model->Fly(false);
        }
        break;
    case 6:
        if (model != NULL) {
            model->Land();
        }
        break;
    case 7:
        if (model != NULL) {
            model->Freeze();
        }
        break;
    case 8:
        break;
    case 9:
        if (model != NULL) {
            model->UnFreeze();
        }
        break;
    default:
        return 0;
    }
    unk18 = 1;
    unk20 = unk1C;
    return 1;
}
extern "C++" {
void EffectEntry::Unload(unsigned char** p0) {
    GSparticleBank *temp_r3_6;
    GSparticleBank *temp_r3_8;
    u32 temp_r0;
    u32 temp_r3_7;
    u8 *temp_r30;
    u8 *temp_r30_2;
    u8 *temp_r30_3;
    u8 *temp_r3;
    u8 *temp_r3_2;
    u8 *temp_r3_4;
    u8 *temp_r3_5;
    u8 *temp_r3_3;

    *p0 = *p0 + 0x70;
    temp_r3 = *p0;
    *p0 = temp_r3 + 0xC;
    temp_r0 = M2C_FIELD(temp_r3, u32 *, 0);
    switch (temp_r0) {
    case 0:
        temp_r3_2 = *p0;
        *p0 = temp_r3_2 + 0x10;
        *p0 += M2C_FIELD(temp_r3_2, u32 *, 4) * 0x10;
        return;
    case 5:
        temp_r30 = *p0;
        *p0 = temp_r30 + 0x40;
        *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
        temp_r3_3 = M2C_FIELD(temp_r30, u8 **, 0x38);
        if (temp_r3_3 != NULL) {
            operator delete((void*)(temp_r3_3));
            M2C_FIELD(temp_r30, u8 **, 0x38) = NULL;
        }
        *p0 = &(*p0)[(M2C_FIELD(temp_r30, s32 *, 0x34) + 0x1F) & 0xFFFFFFE0];
        return;
    case 6:
        temp_r3_4 = *p0;
        *p0 = temp_r3_4 + 0x10;
        *p0 += M2C_FIELD(temp_r3_4, s32 *, 8) * 0x10;
        return;
    case 7:
        temp_r3_5 = *p0;
        *p0 = temp_r3_5 + 0xC;
        *p0 += M2C_FIELD(temp_r3_5, u32 *, 0) * 0x10;
        return;
    case 1:
        temp_r30_2 = *p0;
        *p0 = temp_r30_2 + 0x18;
        *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
        temp_r3_6 = M2C_FIELD(temp_r30_2, GSparticleBank **, 0x10);
        if (temp_r3_6 != NULL) {
            GSparticleFree((GSparticleBank*)(temp_r3_6));
            M2C_FIELD(temp_r30_2, GSparticleBank **, 0x10) = NULL;
        }
        *p0 += (M2C_FIELD(temp_r30_2, u32 *, 0xC) + 0x1F) & 0xFFFFFFE0;
        return;
    case 9:
        temp_r30_3 = *p0;
        *p0 = temp_r30_3 + 0x20;
        *p0 = (u8 *) ((s32) (*p0 + 0x1F) & 0xFFFFFFE0);
        temp_r3_7 = M2C_FIELD(temp_r30_3, u32 *, 4);
        if (temp_r3_7 != 0) {
            operator delete((void*)((u8 *) temp_r3_7));
            M2C_FIELD(temp_r30_3, u32 *, 4) = 0U;
        }
        *p0 = &(*p0)[(M2C_FIELD(temp_r30_3, u32 *, 0) + 0x1F) & 0xFFFFFFE0];
        temp_r3_8 = M2C_FIELD(temp_r30_3, GSparticleBank **, 0xC);
        if (temp_r3_8 != NULL) {
            GSparticleFree((GSparticleBank*)(temp_r3_8));
            M2C_FIELD(temp_r30_3, GSparticleBank **, 0xC) = NULL;
        }
        *p0 = &(*p0)[(M2C_FIELD(temp_r30_3, s32 *, 8) + 0x1F) & 0xFFFFFFE0];
    default:
        return;
    }
}
}

extern "C++" {
void SequenceEntry::Link() {
    volatile u8 sp8;
    SequenceEntry *temp_r3_4;
    SequenceEntry *temp_r3_5;
    SequenceEntry *var_r31;
    WazaSequence *temp_r3;
    WazaSequence *temp_r3_3;
    f32 temp_f0;
    f32 temp_f1;
    s32 temp_r0;
    u8 temp_r4;
    u8 *temp_r3_2;
    u8 *var_r4;

    temp_r4 = M2C_FIELD(this, u8 *, 5);
    temp_r3 = M2C_FIELD(this, WazaSequence **, 0x2C);
    var_r31 = M2C_FIELD(temp_r3, SequenceEntry **, 0x20);
    if ((temp_r4 != 0) && (temp_r3_2 = (unsigned char *)(((WazaSequence*)(temp_r3))->GetEntryFromID(temp_r4)), ((temp_r3_2 == NULL) == 0))) {
        M2C_FIELD(this, f32 *, 0x1C) = (f32) M2C_FIELD(temp_r3_2, f32 *, 0x1C);
        M2C_FIELD(this, f32 *, 0x1C) = M2C_FIELD(this, f32 *, 0x1C) + M2C_FIELD(temp_r3_2, f32 **, 0x14)[M2C_FIELD(this, u8 *, 7)];
    } else {
        temp_r3_3 = M2C_FIELD(this, WazaSequence **, 0x2C);
        var_r4 = M2C_FIELD(temp_r3_3, u8 **, 0x24);
        var_r4 = (s32) M2C_FIELD(var_r4, s32 *, 8) == 1 ? var_r4 : NULL;
        if (var_r4 != NULL) {
            M2C_FIELD(this, f32 *, 0x1C) = (f32) *(M2C_FIELD(var_r4, s32 **, 0x9C) + ((M2C_FIELD(temp_r3_3, u8 *, 0x13) * 0xD0) + 0xC + (M2C_FIELD(this, u8 *, 7) * 4)));
        } else {
            sp8 = M2C_FIELD(this, u8 *, 7);
            M2C_FIELD(this, f32 *, 0x1C) = (f32) M2C_ERROR( );
        }
    }
    M2C_FIELD(this, f32 *, 0x1C) = (f32) (M2C_FIELD(this, f32 *, 0x1C) - *(M2C_FIELD(this, s32 **, 0x14) + (M2C_FIELD(this, u8 *, 6) * 4)));
    M2C_FIELD(this, f32 *, 0x20) = (f32) M2C_FIELD(this, f32 *, 0x1C);
    if (var_r31 != NULL) {
        temp_f0 = M2C_FIELD(var_r31, f32 *, 0x1C);
        temp_f1 = M2C_FIELD(this, f32 *, 0x1C);
        if ((temp_f0 > temp_f1) || ((temp_r0 = M2C_FIELD(this, s32 *, 0xC), ((temp_r0 == 6) != 0)) && (temp_f0 == temp_f1))) {
            M2C_FIELD(this, SequenceEntry **, 0x24) = var_r31;
            M2C_FIELD(this, SequenceEntry **, 0x28) = NULL;
            M2C_FIELD(var_r31, SequenceEntry **, 0x28) = this;
            M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), SequenceEntry **, 0x20) = this;
            return;
        }
loop_19:
        temp_r3_4 = M2C_FIELD(var_r31, SequenceEntry **, 0x24);
        if (temp_r3_4 != NULL) {
            if (!(M2C_FIELD(temp_r3_4, f32 *, 0x1C) > temp_f1) && ((temp_r0 != 6) || (M2C_FIELD(var_r31, f32 *, 0x1C) != temp_f1))) {
                var_r31 = temp_r3_4;
                goto loop_19;
            }
        }
        M2C_FIELD(this, SequenceEntry **, 0x24) = temp_r3_4;
        temp_r3_5 = M2C_FIELD(this, SequenceEntry **, 0x24);
        if (temp_r3_5 != NULL) {
            M2C_FIELD(temp_r3_5, SequenceEntry **, 0x28) = this;
        }
        M2C_FIELD(var_r31, SequenceEntry **, 0x24) = this;
        M2C_FIELD(this, SequenceEntry **, 0x28) = var_r31;
        return;
    }
    M2C_FIELD(M2C_FIELD(this, WazaSequence **, 0x2C), SequenceEntry **, 0x20) = this;
    M2C_FIELD(this, SequenceEntry **, 0x24) = NULL;
    M2C_FIELD(this, SequenceEntry **, 0x28) = NULL;
}
}

bool EventEntry::Update(f32 time) {
    return false;
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
