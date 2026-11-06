#ifndef __MWERKS__
#include <game/psq.h>
#endif
#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/pcret.h>
#include <game/gcdata.h>
#include <game/modelsequenceview.h>
#include <game/hsdarchive.h>
#include <game/wazashadow.h>
#include <game/gcfield.h>
#include <game/wazaentry.h>
#include <game/effects.h>
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
class WazaSequence;
struct _GScamera;
struct _GSmodel;
struct billboardEffect;
class leafEffect;

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

    SEQUENCE_ENTRY_MEMBERS

    SequenceEntry(enumSequenceEntryDataType, WazaSequence*, unsigned char**);
    void Link();
};

class EventEntry : public SequenceEntry {
public:
    EVENT_ENTRY_MEMBERS
    bool Update(f32 time);
public:
    static bool Load(unsigned char**);
    s32 Start();
    ~EventEntry();
    static void Unload(unsigned char**);
    EventEntry(WazaSequence*, unsigned char**);
};

class CameraEntry : public SequenceEntry {
public:
    CAMERA_ENTRY_MEMBERS
    void Stop(bool);
    ~CameraEntry();
    CameraEntry(WazaSequence*, unsigned char**);
    static void Unload(unsigned char**);
    bool Update(float);
    static bool Load(unsigned char**);
    s32 Start();
};
struct EffectKey {
    union {
        struct {
            u8 from[4];
            u8 to[4];
        } color;
        struct {
            gc_bef32 from;
            gc_bef32 to;
        } value;
    };
    gc_bef32 duration;
    gc_be32 unk0C;
};

class EffectEntry : public SequenceEntry {
public:
    EFFECT_ENTRY_MEMBERS(union { EffectKey* m_keys; f32 m_elapsed; })

    void blurEffectLoad(unsigned char**);
    ~EffectEntry();
    void End();
    void boneFillEffectLoad(unsigned char**);
    void envMapEffectLoad(unsigned char**);
    bool Update(float);
    s32 Start();
    void filterEffectLoad(unsigned char**);
    void Stop(bool);
    static bool Load(unsigned char**);
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
class LensFlareEntry : public SequenceEntry {
public:
    LENSFLARE_ENTRY_MEMBERS
    LensFlareEntry(WazaSequence*, unsigned char**);
    s32 Start();
    void Stop(bool);
    static void Unload(unsigned char**);
    static bool Load(unsigned char**);
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
    MODEL_ENTRY_MEMBERS
    ModelEntry(WazaSequence*, unsigned char**);
    ~ModelEntry();
    bool Update(float);
    void SetRenderCamera(_GScamera*);
    static bool Load(unsigned char**);
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
    PARTICLE_ENTRY_MEMBERS
    s32 Start();
    void End();
    void Stop(bool);
    void SetRenderCamera(_GScamera*);
    static bool Load(unsigned char**);
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
    SOUND_ENTRY_MEMBERS
    s32 Start();
    void Stop(bool);
    static bool Load(unsigned char**);
    bool Update(float);
    ~SoundEntry();
    SoundEntry(WazaSequence*, unsigned char**);
    static void Unload(unsigned char**);
};
struct Vec {
    u8 _draft[1];
};
class WazaSequence { public:
    WAZA_SEQUENCE_MEMBERS(ModelSequence)
#ifdef __MWERKS__
    void* GetEntryFromID(unsigned char);
#else
    SequenceEntry* GetEntryFromID(u8 id);
#endif
};
struct _GSmodel {
    u8 _draft[1];
};
struct billboardEffect {
#ifdef __MWERKS__
    u8 _draft[0x28];
#else
    alignas(8) u8 _draft[0x40];
#endif
    billboardEffect(unsigned char**);
};
class leafEffect { public:
#ifdef __MWERKS__
    u8 _draft[0x60];
#else
    alignas(8) u8 _draft[0x78];
#endif
    leafEffect(unsigned char**, float);
};
#ifndef __MWERKS__
void leafEffectSetOrigin(leafEffect* e, f32 x, f32 y, f32 z, f32 scale);
#endif

extern "C" {
s32 GSboundGetLocalPosition(s32, f32*);
s32 GSboundGetWorldPosition(f32*, f32* out);
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
bool GSmodelHasAnimationEnded(_GSmodel* model);
bool GSmodelHasTexAnimationEnded(_GSmodel* model);
u8 GSmodelIsAnimating(_GSmodel* model);
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
s32 GSparticleAttachGeneratorToGSpart(PCARG(u32, void*), f32*, s32, s32, s32, s32);
void GSparticleBankSetCamera(GSparticleBank* bank, _GScamera* camera);
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* bank, s32 index, s32);
void GSparticleDestroyAllGenerators(GSparticleBank* bank, s32 children);
s32 GSparticleDestroyGenerator(PCARG(s32, void*), u8);
void GSparticleFree(GSparticleBank* bank);
u8 GSparticleIsGeneratorAlive(PCARG(u32, void*));
u8 * GSparticleLoad(void*);
void GSparticleSetGeneratorPosition(GSparticleGenerator* gen, Vec* pos);
s32 GSparticleSetGeneratorRotation(PCARG(u32, void*), f32*);
s32 GSparticleSetGeneratorScale(PCARG(u32, void*), f32*, s32, s32);
s32 GSparticleSetNodeScaling(PCARG(u32, void*), s32);
void GSparticleSetOffsetRotationInLocal(void* gen, u8 on, u8 local);
s32 GSparticleSetParticleTextureScaling(PCARG(u32, void*), s32);
s32 GSparticleSetRandomVelocityScaling(PCARG(u32, void*), s32);
s32 GSparticleSetTornadoScaling(PCARG(u32, void*), s32, s32);
s32 GSparticleSetVelocityRotationInLocal(PCARG(u32, void*), s32);
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
#ifdef __MWERKS__
extern XdBlob24 gCameraShakeModels;
#define CAMERA_SHAKE_MODEL(off) M2C_FIELD(&gCameraShakeModels, _GSmodel **, off)
#else
extern _GSmodel* gCameraShakeModels[9];
#define CAMERA_SHAKE_MODEL(off) gCameraShakeModels[(off) / 4]
#endif
s32 soundOpenPlayME(u32 id, s32 time, s32 vol);
extern GSvec unitScaleVector;
extern SVec zeroVector;
extern s32 this_;
}
extern "C++" {
static void _wazaCameraInitShake(WazaSequence* p0, int p1);
u32 wazaSequenceSysGetModelShadowCount();
WazaShadowAddr wazaSequenceSysGetModelShadowLight();
WazaShadowListAddr wazaSequenceSysGetModelShadowList();
}
GSthread* gSoundThread;

extern "C" {
#ifdef __MWERKS__
extern s32 jtbl_2422;
#else
static const s32 jtbl_2422 = 4;
#endif
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

    if ((p0 == NULL) || (p0->m_camera != 0U)) {
        gCameraShakeModel = NULL;
        return;
    }
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
    cameraSetOffsetPosition(&pos);
    cameraSetOffsetRotation(&pos);
    if ((s32) (p1 & 9) == 9) {
        gCameraShakeModel = CAMERA_SHAKE_MODEL(0);
    } else if ((s32) (p1 & 0x11) == 0x11) {
        gCameraShakeModel = CAMERA_SHAKE_MODEL(4);
    } else if ((s32) (p1 & 0x21) == 0x21) {
        gCameraShakeModel = CAMERA_SHAKE_MODEL(8);
    } else if ((s32) (p1 & 0xA) == 0xA) {
        gCameraShakeModel = CAMERA_SHAKE_MODEL(0xC);
    } else if ((s32) (p1 & 0x12) == 0x12) {
        gCameraShakeModel = CAMERA_SHAKE_MODEL(0x10);
    } else if ((s32) (p1 & 0x22) == 0x22) {
        gCameraShakeModel = CAMERA_SHAKE_MODEL(0x14);
    } else if ((s32) (p1 & 0xC) == 0xC) {
        gCameraShakeModel = CAMERA_SHAKE_MODEL(0x18);
    } else if ((s32) (p1 & 0x14) == 0x14) {
        gCameraShakeModel = CAMERA_SHAKE_MODEL(0x1C);
    } else if ((s32) (p1 & 0x24) == 0x24) {
        gCameraShakeModel = CAMERA_SHAKE_MODEL(0x20);
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
    THIS_F(s32 *, 0xC, type) = p0;
    THIS_F(WazaSequence * *, 0x2C, seq) = p1;
    temp_r7 = *p2;
    THIS_F(u8 *, 9, unk09) = (u8) GC_AT(s32, temp_r7, 0x6C);
    THIS_F(u8 *, 4, unk04) = (u8) GC_AT(s32, temp_r7, 0);
    temp_r0 = GC_AT(s32, temp_r7, 0x10);
    if (temp_r0 >= 0) {
        THIS_F(u8 *, 5, unk05) = (u8) temp_r0;
    } else {
        THIS_F(u8 *, 5, unk05) = 0xFF;
    }
    temp_r0_2 = GC_AT(s32, temp_r7, 0x14);
    if (temp_r0_2 >= 0) {
        THIS_F(u8 *, 6, unk06) = (u8) temp_r0_2;
    } else {
        THIS_F(u8 *, 6, unk06) = 0;
    }
    temp_r0_3 = GC_AT(s32, temp_r7, 0x18);
    if (temp_r0_3 >= 0) {
        THIS_F(u8 *, 7, unk07) = (u8) temp_r0_3;
    } else {
        THIS_F(u8 *, 7, unk07) = 0;
    }
    THIS_F(u8 *, 8, unk08) = (u8) GC_AT(s32, temp_r7, 0x1C);
    THIS_F(s16 *, 0xA, unk0A) = (s16) GC_AT(s32, temp_r7, 0x60);
    THIS_F(s16 *, 0x12, unk12) = (s16) GC_AT(s32, temp_r7, 0x64);
    THIS_F(u8 *, 0x10, unk10) = (u8) GC_AT(s32, temp_r7, 8);
    THIS_F(u8 *, 0x11, unk11) = (u8) GC_AT(s32, temp_r7, 0xC);
    THIS_F(u8 * *, 0x14, params) = (u8 *) (temp_r7 + 0x20);
    THIS_F(SequenceEntry * *, 0x24, m_next) = 0;
    THIS_F(s32 *, 0x28, unk28) = 0;
    THIS_F(f32 *, 0x20, m_nextTime) = 0.0f;
    THIS_F(f32 *, 0x1C, m_start) = 0.0f;
    THIS_F(s32 *, 0x18, m_state) = 0;
    *p2 += 0x70;
}
}

extern "C++" {
SequenceEntry::~SequenceEntry() {
    if (m_next != 0) {
        delete m_next;
    }
}
}

extern "C++" {
static inline f32 __OSu8tof32(register const u8* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 2 }
#else
    ret = PSQ_LOAD(arg, 0, 2);
#endif
    return ret;
}

static inline f32 OSu8tof32(u8 in) {
    u8 tmp = in;
    return __OSu8tof32(&tmp);
}

static inline SequenceEntry* seqFirstEntry(WazaSequence* s) {
    return s->m_entries;
}

void SequenceEntry::Link() {
    SequenceEntry* base;
    SequenceEntry* e = seqFirstEntry(seq);

    if (unk05 != 0 && (base = (SequenceEntry*)seq->GetEntryFromID(unk05)) != NULL) {
        m_start = base->m_start;
        m_start += GC_AT(f32, base->params, unk07 * 4);
    } else {
        WazaSequence* s = seq;
        u8* target = (u8*)s->m_owner;
        u8* model = ((ModelSequenceLayout*)target)->m_kind == 1 ? target : NULL;
        if (model != NULL) {
            m_start = ((gc_bef32*)((u8*)((ModelSequenceLayout*)model)->m_sections + s->m_section * 0xD0 + 0xC))[unk07];
        } else {
            m_start = OSu8tof32(unk07);
        }
    }
    m_start -= GC_AT(f32, params, unk06 * 4);
    m_nextTime = m_start;
    if (e != NULL) {
        if (e->m_start > m_start || (type == 6 && e->m_start == m_start)) {
            m_next = e;
            unk28 = 0;
            e->unk28 = (GCsptr)this;
            seq->m_entries = this;
            return;
        }
        SequenceEntry* next;
        while ((next = e->m_next) != NULL) {
            if (next->m_start > m_start) {
                break;
            }
            if (type == 6 && e->m_start == m_start) {
                break;
            }
            e = next;
        }
        m_next = next;
        if (m_next != NULL) {
            m_next->unk28 = (GCsptr)this;
        }
        e->m_next = this;
        unk28 = (GCsptr)e;
    } else {
        seq->m_entries = this;
        m_next = NULL;
        unk28 = 0;
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
bool CameraEntry::Load(unsigned char** data) {
    *data += 0x70;
    u8* header = *data;
    *data += 0xC;
    switch (GC_AT(s32, header, 0)) {
    case 2:
        break;
    case 3:
        *data += GC_AT(s32, header, 4) * 8;
        break;
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
    temp_r0 = GC_AT(s32, temp_r4, 0);
    if (temp_r0 != 3) {
        if (temp_r0 >= 3) {
            return;
        }
        return;
    }
    *p0 += GC_AT(s32, temp_r4, 4) * 8;
}
}

extern "C++" {
CameraEntry::CameraEntry(WazaSequence* p0, unsigned char** p1)
    : SequenceEntry((enumSequenceEntryDataType)1, p0, p1) {
    s32 temp_r0;
    u8 *temp_r3;
    temp_r3 = *p1;
    *p1 = temp_r3 + 0xC;
    THIS_F(s32 *, 0x30, unk30) = (s32) GC_AT(s32, temp_r3, 0);
    temp_r0 = THIS_F(s32 *, 0x30, unk30);
    switch (temp_r0) {
    case 0:
        THIS_F(f32 *, 0x34, unk34) = (f32) GC_AT(f32, temp_r3, 4);
        break;
    case 1:
        THIS_F(u32 *, 0x34, unk34) = GC_AT(u32, temp_r3, 4);
        break;
    case 2:
        THIS_F(f32 *, 0x34, unk34) = (f32) GC_AT(f32, temp_r3, 4);
        break;
    case 3:
        *p1 += GC_AT(u32, temp_r3, 4) * 8;
        THIS_F(s32 *, 0x30, unk30) = 0;
        THIS_F(f32 *, 0x34, unk34) = 0.0f;
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
bool ModelEntry::Load(unsigned char** p0) {
    u32 temp_r3;
    u8 *temp_r31;

    wazaSequenceSysGetResID();
    *p0 += 0x70;
    temp_r31 = *p0;
    *p0 = temp_r31 + 0x28;
    *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
    GC_AT(u32, temp_r31, 0x20) = 0U;
    if ((s32) GC_AT(s32, temp_r31, 0x1C) != 0) {
        temp_r3 = (u32)(operator new(HSD_ARCHIVE_SIZE));
        if (temp_r3 != 0) {
            GC_AT(u32, temp_r31, 0x20) = temp_r3;
            HSD_ArchiveParse((HSD_Archive*)((HSD_Archive *) temp_r3), (u8*)(*p0), (u32) GC_AT(s32, temp_r31, 0x1C));
        }
        *p0 = &(*p0)[(GC_AT(s32, temp_r31, 0x1C) + 0x1F) & 0xFFFFFFE0];
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
    *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
    temp_r3 = GC_AT(u8 *, temp_r31, 0x20);
    if (temp_r3 != NULL) {
        operator delete((void*)(temp_r3));
        GC_AT(u8 *, temp_r31, 0x20) = NULL;
    }
    temp_r3_2 = GC_AT(s32, temp_r31, 0x1C);
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
    *p1 = (u8 *) ((GCsptr) (*p1 + 0x1F) & 0xFFFFFFE0);
    THIS_F(s32 *, 0x30, unk30) = 0;
    THIS_F(_GSmodel * *, 0x4C, model) = NULL;
    temp_r3 = GC_AT(HSD_Archive *, temp_r31, 0x20);
    if (temp_r3 != NULL) {
        loadModel((HSD_Archive*)(temp_r3), 0x4E20U, 0U, (u32) temp_r28);
        GSresIsUniqueID(0x4E20U, (u32) temp_r28, 0U);
        temp_r3_2 = (_GSmodel *)(GSresGetResource(0x4E20U, (u32) temp_r28));
        THIS_F(_GSmodel * *, 0x4C, model) = temp_r3_2;
        if (temp_r3_2 != NULL) {
            THIS_F(s32 *, 0x30, unk30) = temp_r28;
        }
    }
    temp_r3_3 = GC_AT(s32, temp_r31, 0x1C);
    if (temp_r3_3 != 0) {
        *p1 = &(*p1)[(temp_r3_3 + 0x1F) & 0xFFFFFFE0];
    }
    THIS_F(s32 *, 0x38, unk38) = (s32) GC_AT(s32, temp_r31, 0);
    temp_r0 = GC_AT(s32, temp_r31, 4);
    switch (temp_r0) {
    case 0:
        THIS_F(s32 *, 0x34, unk34) = 0;
        break;
    case 1:
        THIS_F(s32 *, 0x34, unk34) = 1;
        break;
    }
    THIS_F(s32 *, 0x40, unk40) = (s32) GC_AT(s32, temp_r31, 8);
    temp_r0_2 = GC_AT(s32, temp_r31, 0xC);
    switch (temp_r0_2) {
    case 0:
        THIS_F(s32 *, 0x3C, unk3C) = 0;
        break;
    case 1:
        THIS_F(s32 *, 0x3C, unk3C) = 1;
        break;
    }
    THIS_F(s8 *, 0x4A, unk4A) = (s8) (GC_AT(s32, temp_r31, 0x10) != 0);
    THIS_F(s32 *, 0x44, unk44) = (s32) GC_AT(s32, temp_r31, 0x14);
    THIS_F(s16 *, 0x48, unk48) = (s16) GC_AT(s32, temp_r31, 0x18);
    if ((*(gc_bef32**)&params)[THIS_F(u8 *, 8, unk08) - 1] < 0.00001f) {
        spC = 0.0f;
        sp8 = 0.0f;
        temp_r3_4 = THIS_F(_GSmodel * *, 0x4C, model);
        if (temp_r3_4 != NULL) {
            GSmodelGetFrameCount((_GSmodel*)(temp_r3_4), (f32*)(&spC), (f32*)(&sp8));
        }
        var_f31 = spC;
        var_f31 = var_f31 >= sp8 ? var_f31 : sp8;
        (*(gc_bef32**)&params)[THIS_F(u8 *, 8, unk08) - 1] = (f32) ((f32) (s32) var_f31 / (f32) GSgfxVideoGetVsyncRate());
    }
    return;
}
}

extern "C++" {
ModelEntry::~ModelEntry() {
    if (THIS_F(u32 *, 0x30, unk30) != 0) {
        GSresFreeResource(0x4E20, THIS_F(u32 *, 0x30, unk30));
    }
}
}

extern "C++" {
bool ParticleEntry::Load(unsigned char** p0) {
    u8 *temp_r31;
    u8 *temp_r4;

    temp_r4 = *p0;
    *p0 = temp_r4 + 0x70;
    temp_r31 = *p0;
    *p0 = temp_r31 + 0x14;
    *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
    GC_AT(s32, temp_r31, 0xC) = 0;
    if ((s32) GC_AT(s32, temp_r4, 0x6C) == 0) {
        GC_AT(s32, temp_r31, 0xC) = GC_ADDR32(GSparticleLoad(*p0));
    }
    *p0 = &(*p0)[(GC_AT(s32, temp_r31, 8) + 0x1F) & 0xFFFFFFE0];
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
    *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
    temp_r3 = GC_AT(GSparticleBank *, temp_r31, 0xC);
    if (temp_r3 != NULL) {
        GSparticleFree((GSparticleBank*)(temp_r3));
        GC_AT(GSparticleBank *, temp_r31, 0xC) = NULL;
    }
    *p0 = &(*p0)[(GC_AT(s32, temp_r31, 8) + 0x1F) & 0xFFFFFFE0];
}
}

extern "C++" {
ParticleEntry::ParticleEntry(WazaSequence* p0, unsigned char** p1)
    : SequenceEntry((enumSequenceEntryDataType)3, p0, p1) {
    u8 *temp_r31;
    u8 temp_r4;
    u8 *temp_r3;
    u8 *temp_ret;
    generator = 0;
    temp_r31 = *p1;
    *p1 = temp_r31 + 0x14;
    *p1 = (u8 *) ((GCsptr) (*p1 + 0x1F) & 0xFFFFFFE0);
    *p1 = &(*p1)[(GC_AT(s32, temp_r31, 8) + 0x1F) & 0xFFFFFFE0];
    temp_r4 = THIS_F(u8 *, 9, unk09);
    if (temp_r4 != 0) {
        temp_r3 = (unsigned char *)(((WazaSequence*)(THIS_F(WazaSequence * *, 0x2C, seq)))->GetEntryFromID(temp_r4));
        if (temp_r3 != NULL) {
            bank = ((ParticleEntry*)temp_r3)->bank;
        } else {
            GSlogWrite("particle waza entry not found");
            bank = 0;
        }
    } else {
        bank = GC_AT(GSparticleBank*, temp_r31, 0xC);
    }
    THIS_F(s32 *, 0x30, unk30) = (s32) GC_AT(s32, temp_r31, 0);
    THIS_F(s32 *, 0x34, unk34) = (s32) GC_AT(s32, temp_r31, 4);
    generator = 0;
    return;
}
}

extern "C++" {
ParticleEntry::~ParticleEntry() {
    if (unk09 == 0 && THIS_F(GSparticleBank * *, 0x38, bank) != 0) {
        GSparticleDestroyAllGenerators(THIS_F(GSparticleBank * *, 0x38, bank), 1);
    }
    generator = 0;
    bank = 0;
}
}

extern "C++" {
bool LensFlareEntry::Load(unsigned char** p0) {
    u8 *temp_r5;

    *p0 += 0x70;
    temp_r5 = *p0;
    *p0 = temp_r5 + 0x14;
    *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
    *p0 = &(*p0)[(GC_AT(u32, temp_r5, 0) + 0x1F) & 0xFFFFFFE0];
    return 1;
}
}

extern "C++" {
void LensFlareEntry::Unload(unsigned char** p0) {
    u8 *temp_r5;

    *p0 += 0x70;
    temp_r5 = *p0;
    *p0 = temp_r5 + 0x14;
    *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
    *p0 = &(*p0)[(GC_AT(u32, temp_r5, 0) + 0x1F) & 0xFFFFFFE0];
}
}

extern "C++" {
LensFlareEntry::LensFlareEntry(WazaSequence* p0, unsigned char** p1)
    : SequenceEntry((enumSequenceEntryDataType)7, p0, p1) {
    u8 *temp_r31;
    THIS_F(u32 *, 0x30, unk30) = 0U;
    temp_r31 = *p1;
    THIS_F(f32 *, 0x34, unk34) = (f32) GC_AT(f32, temp_r31, 0xC);
    THIS_F(s32 *, 0x38, unk38) = (s32) GC_AT(s32, temp_r31, 8);
    *p1 += 0x14;
    *p1 = (u8 *) ((GCsptr) (*p1 + 0x1F) & 0xFFFFFFE0);
    THIS_F(u32 *, 0x30, unk30) = GSlensFlareLoad((u8*)(*p1));
    *p1 = &(*p1)[(GC_AT(s32, temp_r31, 0) + 0x1F) & 0xFFFFFFE0];
    GSlensFlareSetVisible(THIS_F(u32 *, 0x30, unk30), 0U);
    return;
}
}

extern "C++" {
LensFlareEntry::~LensFlareEntry() {
    GSlensFlareSetVisible(THIS_F(u32 *, 0x30, unk30), 0);
    GSlensFlareFree(THIS_F(u32 *, 0x30, unk30));
}
}

extern "C++" {
bool EffectEntry::Load(unsigned char** p0) {
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
    temp_r0 = GC_AT(u32, temp_r3, 0);
    switch (temp_r0) {
    case 0: {
        u8* hdr = *p0;
        s32 n = GC_AT(s32, hdr, 4);
        *p0 = hdr + 0x10;
        u8* k = *p0;
        for (var_ctr = 0; var_ctr < n; var_ctr++) {
            GC_AT(u8, k, 0) ^= GC_AT(u8, k, 3);
            GC_AT(u8, k, 3) = (u8) (GC_AT(u8, k, 3) ^ GC_AT(u8, k, 0));
            GC_AT(u8, k, 0) ^= GC_AT(u8, k, 3);
            GC_AT(u8, k, 1) = (u8) (GC_AT(u8, k, 1) ^ GC_AT(u8, k, 2));
            GC_AT(u8, k, 2) = (u8) (GC_AT(u8, k, 2) ^ GC_AT(u8, k, 1));
            GC_AT(u8, k, 1) = (u8) (GC_AT(u8, k, 1) ^ GC_AT(u8, k, 2));
            GC_AT(u8, k, 4) = (u8) (GC_AT(u8, k, 4) ^ GC_AT(u8, k, 7));
            GC_AT(u8, k, 7) = (u8) (GC_AT(u8, k, 7) ^ GC_AT(u8, k, 4));
            GC_AT(u8, k, 4) = (u8) (GC_AT(u8, k, 4) ^ GC_AT(u8, k, 7));
            GC_AT(u8, k, 5) = (u8) (GC_AT(u8, k, 5) ^ GC_AT(u8, k, 6));
            GC_AT(u8, k, 6) = (u8) (GC_AT(u8, k, 6) ^ GC_AT(u8, k, 5));
            GC_AT(u8, k, 5) = (u8) (GC_AT(u8, k, 5) ^ GC_AT(u8, k, 6));
            k += 0x10;
        }
        *p0 += GC_AT(s32, hdr, 4) * 0x10;
    }
block_21:
        return 1;
    case 5:
        temp_r30 = *p0;
        *p0 = temp_r30 + 0x40;
        *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
        GC_AT(u32, temp_r30, 0x38) = 0U;
        if ((s32) GC_AT(s32, temp_r30, 0x34) != 0) {
            temp_r3_3 = (u32)(operator new(HSD_ARCHIVE_SIZE));
            if (temp_r3_3 != 0) {
                GC_AT(u32, temp_r30, 0x38) = temp_r3_3;
                HSD_ArchiveParse((HSD_Archive*)((HSD_Archive *) temp_r3_3), (u8*)(*p0), (u32) GC_AT(s32, temp_r30, 0x34));
            }
            *p0 = &(*p0)[(GC_AT(s32, temp_r30, 0x34) + 0x1F) & 0xFFFFFFE0];
        }
        goto block_21;
    case 6:
        temp_r3_4 = *p0;
        *p0 = temp_r3_4 + 0x10;
        *p0 += GC_AT(s32, temp_r3_4, 8) * 0x10;
        goto block_21;
    case 7:
        temp_r3_5 = *p0;
        *p0 = temp_r3_5 + 0xC;
        *p0 += GC_AT(s32, temp_r3_5, 0) * 0x10;
        goto block_21;
    case 1:
        temp_r30_2 = *p0;
        *p0 = temp_r30_2 + 0x18;
        *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
        GC_AT(s32, temp_r30_2, 0x10) = 0;
        if ((s32) GC_AT(s32, temp_r4, 0x6C) == 0) {
            GC_AT(s32, temp_r30_2, 0x10) = GC_ADDR32(GSparticleLoad(*p0));
        }
        *p0 = &(*p0)[(GC_AT(s32, temp_r30_2, 0xC) + 0x1F) & 0xFFFFFFE0];
        goto block_21;
    case 9:
        temp_r30_3 = *p0;
        *p0 = temp_r30_3 + 0x20;
        *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
        GC_AT(s32, temp_r30_3, 4) = 0;
        if ((s32) GC_AT(s32, temp_r30_3, 0) != 0) {
            temp_r3_6 = (u32)(operator new(HSD_ARCHIVE_SIZE));
            if (temp_r3_6 != 0) {
                GC_AT(s32, temp_r30_3, 4) = (s32) temp_r3_6;
                HSD_ArchiveParse((HSD_Archive*)((HSD_Archive *) temp_r3_6), (u8*)(*p0), (u32) GC_AT(s32, temp_r30_3, 0));
            }
            *p0 = &(*p0)[(GC_AT(s32, temp_r30_3, 0) + 0x1F) & 0xFFFFFFE0];
        }
        GC_AT(s32, temp_r30_3, 0xC) = 0;
        if ((s32) GC_AT(s32, temp_r30_3, 8) != 0) {
            GC_AT(s32, temp_r30_3, 0xC) = GC_ADDR32(GSparticleLoad(*p0));
            *p0 = &(*p0)[(GC_AT(s32, temp_r30_3, 8) + 0x1F) & 0xFFFFFFE0];
        }
        goto block_21;
    default:
        return 0;
    }
}
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
    temp_r0 = GC_AT(u32, temp_r3, 0);
    switch (temp_r0) {
    case 0:
        temp_r3_2 = *p0;
        *p0 = temp_r3_2 + 0x10;
        *p0 += GC_AT(u32, temp_r3_2, 4) * 0x10;
        return;
    case 5:
        temp_r30 = *p0;
        *p0 = temp_r30 + 0x40;
        *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
        temp_r3_3 = GC_AT(u8 *, temp_r30, 0x38);
        if (temp_r3_3 != NULL) {
            operator delete((void*)(temp_r3_3));
            GC_AT(u8 *, temp_r30, 0x38) = NULL;
        }
        *p0 = &(*p0)[(GC_AT(s32, temp_r30, 0x34) + 0x1F) & 0xFFFFFFE0];
        return;
    case 6:
        temp_r3_4 = *p0;
        *p0 = temp_r3_4 + 0x10;
        *p0 += GC_AT(s32, temp_r3_4, 8) * 0x10;
        return;
    case 7:
        temp_r3_5 = *p0;
        *p0 = temp_r3_5 + 0xC;
        *p0 += GC_AT(u32, temp_r3_5, 0) * 0x10;
        return;
    case 1:
        temp_r30_2 = *p0;
        *p0 = temp_r30_2 + 0x18;
        *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
        temp_r3_6 = GC_AT(GSparticleBank *, temp_r30_2, 0x10);
        if (temp_r3_6 != NULL) {
            GSparticleFree((GSparticleBank*)(temp_r3_6));
            GC_AT(GSparticleBank *, temp_r30_2, 0x10) = NULL;
        }
        *p0 += (GC_AT(u32, temp_r30_2, 0xC) + 0x1F) & 0xFFFFFFE0;
        return;
    case 9:
        temp_r30_3 = *p0;
        *p0 = temp_r30_3 + 0x20;
        *p0 = (u8 *) ((GCsptr) (*p0 + 0x1F) & 0xFFFFFFE0);
        temp_r3_7 = GC_AT(u32, temp_r30_3, 4);
        if (temp_r3_7 != 0) {
            operator delete((void*)((u8 *) temp_r3_7));
            GC_AT(u32, temp_r30_3, 4) = 0U;
        }
        *p0 = &(*p0)[(GC_AT(u32, temp_r30_3, 0) + 0x1F) & 0xFFFFFFE0];
        temp_r3_8 = GC_AT(GSparticleBank *, temp_r30_3, 0xC);
        if (temp_r3_8 != NULL) {
            GSparticleFree((GSparticleBank*)(temp_r3_8));
            GC_AT(GSparticleBank *, temp_r30_3, 0xC) = NULL;
        }
        *p0 = &(*p0)[(GC_AT(s32, temp_r30_3, 8) + 0x1F) & 0xFFFFFFE0];
    default:
        return;
    }
}
}

struct EffectEntryHeader {
    gc_be32 type;
    gc_bef32 time;
    gc_be32 unk08;
};

EffectEntry::EffectEntry(WazaSequence* p0, unsigned char** p1) : SequenceEntry((enumSequenceEntryDataType)4, p0, p1) {
    EffectEntryHeader* hdr;
    f32* end;

    THIS_F(GSeffect* *, 0x30, m_effect) = NULL;
    THIS_FP(u32 *, 0x34, m_keys) = 0;
    THIS_F(f32 *, 0x38, m_time) = 0.0f;
    THIS_F(u8 *, 0x3C, m_keyCount) = 0;
    THIS_F(u8 *, 0x3D, m_curKey) = 0;
    THIS_F(u8 *, 0x40, m_keyed) = 0;
    hdr = (EffectEntryHeader*)*p1;
    THIS_F(u8 *, 0x41, m_type) = hdr->type;
    THIS_F(f32 *, 0x38, m_time) = hdr->time;
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
        THIS_F(GSeffect* *, 0x30, m_effect) = (GSeffect*)new leafEffect(p1, hdr->time);
        THIS_F(u8 *, 0x3D, m_curKey) = 1;
        THIS_F(u8 *, 0x3C, m_keyCount) = 0;
        break;
    case 9:
        THIS_F(GSeffect* *, 0x30, m_effect) = (GSeffect*)new billboardEffect(p1);
        THIS_F(u8 *, 0x3D, m_curKey) = 0;
        THIS_F(u8 *, 0x3C, m_keyCount) = 0;
        break;
    case 1:
        boneFillEffectLoad(p1);
        THIS_F(u8 *, 0x3D, m_curKey) = 0;
        THIS_F(u8 *, 0x3C, m_keyCount) = 0;
        break;
    }
    end = (f32*)params + unk08;
#ifdef __MWERKS__
    if (end[-1] < 0.00001f) {
        end[-1] = hdr->time;
    }
#else
    if (GC_AT(f32, end, -4) < 0.00001f) {
        GC_AT(f32, end, -4) = hdr->time;
    }
#endif
}

extern "C++" {
EffectEntry::~EffectEntry() {
    if (THIS_F(GSeffect * *, 0x30, m_effect) != 0) {
        delete THIS_F(GSeffect * *, 0x30, m_effect);
    }
}
}

extern "C++" {
bool EventEntry::Load(unsigned char** p0) {
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
    unk30 = GC_AT(u32, *data, 0);
    *data += 8;
}
}

extern "C++" {
EventEntry::~EventEntry() {
}
}

extern "C++" {
bool SoundEntry::Load(unsigned char** p0) {
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
    emitter = 0;
    THIS_F(s16 *, 0x34, unk34) = (s16) GC_AT(s32, temp_r4, 8);
    THIS_F(s8 *, 0x36, unk36) = (s8) GC_AT(s32, temp_r4, 0x10);
    THIS_F(f32 *, 0x38, unk38) = (f32) GC_AT(f32, temp_r4, 0xC);
    THIS_F(s32 *, 0x30, unk30) = (s32) GC_AT(s32, temp_r4, 0);
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
    THIS_F(s32 *, 0x18, m_state) = 1;
    THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
    return 1;
}
}

extern "C++" {
bool SequenceEntry::Update(float p0) {
    THIS_F(f32 *, 0x20, m_nextTime) = (f32) (THIS_F(f32 *, 0x20, m_nextTime) + p0);
    return 1;
}
}

void SequenceEntry::End() {
}

extern "C++" {
void SequenceEntry::Stop(bool p0) {
    s32 temp_r5;

    temp_r5 = THIS_F(s32 *, 0x18, m_state);
    if ((temp_r5 != 2) && ((p0 != 0) || (temp_r5 == 1))) {
        THIS_F(s32 *, 0x18, m_state) = 2;
    }
}
}

extern "C++" {
s32 CameraEntry::Start() {
    switch (THIS_F(s32 *, 0x30, unk30)) {
    case 0:
        break;
    case 1:
        _wazaCameraInitShake(THIS_F(WazaSequence * *, 0x2C, seq), THIS_F(s32 *, 0x34, unk34));
        break;
    case 2:
    case 3:
        break;
    default:
        return 0;
    }
    THIS_F(s32 *, 0x18, m_state) = 1;
    THIS_F(f32 *, 0x20, m_nextTime) = THIS_F(f32 *, 0x1C, m_start);
    return 1;
}
}

extern "C++" {
bool CameraEntry::Update(float dt) {
    GSvec rot;
    GSvec pos;
    GSpart* part;

    THIS_F(f32 *, 0x20, m_nextTime) += dt;
    switch (THIS_F(s32 *, 0x30, unk30)) {
    case 0:
        if (THIS_F(f32 *, 0x20, m_nextTime) - THIS_F(f32 *, 0x1C, m_start) >= THIS_F(f32 *, 0x34, unk34)) {
            seq->m_started = 1;
            return false;
        }
        break;
    case 1:
        if (gCameraShakeModel == NULL) {
            return false;
        }
        if (GSmodelIsAnimating(gCameraShakeModel) == 0 || GSmodelHasAnimationEnded(gCameraShakeModel) != 0) {
            return false;
        }
        part = GSmodelGetPart(gCameraShakeModel, 1);
        if (part == NULL) {
            return false;
        }
        GSpartGetTransform(part, &pos, &rot, NULL);
        PSVECScale((Vec*)&pos, (Vec*)&pos, 2.5f);
        cameraSetOffsetPosition(&pos);
        cameraSetOffsetRotation(&rot);
        GSpartFree(part);
        return true;
    case 2:
        break;
    }
    return true;
}
}

extern "C++" {
void CameraEntry::Stop(bool force) {
    s32 state = THIS_F(s32 *, 0x18, m_state);
    if (state != 2 && (force || state == 1)) {
        THIS_F(s32 *, 0x18, m_state) = 2;
        switch (THIS_F(s32 *, 0x30, unk30)) {
        case 0:
            break;
        case 2:
            break;
        case 1: {
            GSvec zero;
            zero.x = 0.0f;
            zero.y = 0.0f;
            zero.z = 0.0f;
            cameraSetOffsetPosition(&zero);
            cameraSetOffsetRotation(&zero);
            if (gCameraShakeModel != NULL) {
                GSmodelStopAnimation(gCameraShakeModel);
                gCameraShakeModel = NULL;
            }
            break;
        }
        }
    }
}
}

extern "C++" {
void ModelEntry::SetRenderCamera(_GScamera* camera) {
    _GSmodel* model = THIS_F(_GSmodel * *, 0x4C, model);
    if (model != NULL) {
        GSmodelSetRenderCamera(model, (GScamera*)camera);
    }
}
}

extern "C++" {
s32 ModelEntry::Start() {
    s32 sp8;
    s32 var_r31;
    GSpart *var_r30_2;
    ModelSequence *var_r30;
    ModelSequence *var_r3;
    s32 temp_r28;
    _GSmodel *temp_r27_2;
    _GSmodel *temp_r3_6;
    _GSmodel *var_r28;
    f32 temp_f1;
    WazaSequence *temp_r3;
    ModelSequence *ms;
    GSvec scl;
    GSvec rot;
    GSvec pos;
    GSvec tmp;
    s32 temp_r3_7;
    GSpart *temp_r27_3;
    u16 temp_r3_3;
    u8 temp_r0;
    u8 temp_r4;
    u8 temp_r4_2;
    u8 *temp_r3_2;
    u8 *temp_r3_5;
    f32 *temp_r3_4;

    if ((_GSmodel *) THIS_F(_GSmodel * *, 0x4C, model) == NULL) {
        return 0;
    }
    temp_r3 = THIS_F(WazaSequence * *, 0x2C, seq);
    temp_r28 = temp_r3->m_flags;
    ms = temp_r3->m_owner;
    if (!(temp_r28 & 0x2000) && ((u8) M2C_NAMED(((ModelSequenceLayout*)(ms)), u8 *, 0x6, m_visible) == 0)) {
        THIS_F(s32 *, 0x18, m_state) = 2;
        THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
        return 1;
    }
    temp_r0 = THIS_F(u8 *, 0x11, unk11);
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
    if ((s32) M2C_NAMED(((ModelSequenceLayout*)(ms)), s32 *, 0x8, m_kind) == 1) {
        var_r30 = ms;
    } else {
        var_r30 = NULL;
    }
    if (var_r30 != NULL) {
        ms->GetPosition(&pos);
        ms->GetRotation(&rot);
        if (THIS_F(u16 *, 0xA, unk0A) & 1) {
            temp_r4 = THIS_F(u8 *, 5, unk05);
            if ((temp_r4 != 0) && (temp_r4 != 0xFF)) {
                temp_r3_2 = (unsigned char *)(((WazaSequence*)(THIS_F(WazaSequence * *, 0x2C, seq)))->GetEntryFromID(temp_r4));
                if ((M2C_NAMED(((ModelEntry*)(temp_r3_2)), f32 *, 0x1C, m_start) <= THIS_F(f32 *, 0x1C, m_start)) && ((s32) M2C_NAMED(((ModelEntry*)(temp_r3_2)), s32 *, 0xC, type) == 2)) {
                    temp_r27_2 = M2C_NAMED(((ModelEntry*)(temp_r3_2)), _GSmodel **, 0x4C, model);
                    if (temp_r27_2 != NULL) {
                        GSmodelForceAnimTransformUpdate((_GSmodel*)(temp_r27_2));
                        GSmodelGetPosition((_GSmodel*)(temp_r27_2), &pos);
                        GSmodelGetRotation((_GSmodel*)(temp_r27_2), &rot);
                    }
                }
            }
        }
        temp_f1 = ((ModelSequence*)(var_r30))->GetModelScale(!(temp_r28 & 0x10000000));
        scl.x = temp_f1;
        scl.y = temp_f1;
        scl.z = temp_f1;
    } else {
        ms->GetPosition(&pos);
        ms->GetRotation(&rot);
        ms->GetScale(&scl);
    }
    if (THIS_F(u16 *, 0xA, unk0A) & 0x20) {
        scl.z = 1.0f;
        scl.y = 1.0f;
        scl.x = 1.0f;
    }
    var_r28 = NULL;
    THIS_F(s8 *, 0x4B, unk4B) = 0;
    temp_r3_3 = THIS_F(u16 *, 0xA, unk0A);
    if (temp_r3_3 & 4) {
        if (temp_r3_3 & 8) {
            battleGridGetNormalisedScale(&scl);
            if (THIS_F(u16 *, 0xA, unk0A) & 0x10) {
                scl.y = 1.0f;
            }
            GSmodelSetScale((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &scl);
        }
    } else {
        var_r28 = var_r30 == NULL ? var_r28 : M2C_NAMED(((ModelSequenceLayout*)(var_r30)), _GSmodel **, 0x94, m_model);
        if (var_r31 != 0) {
            if ((u8) THIS_F(u8 *, 0x4A, unk4A) != 0) {
                temp_r27_3 = GSmodelGetPart((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), THIS_F(s32 *, 0x44, unk44));
                GSmodelSetPosition((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &pos);
                GSmodelSetRotation((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &rot);
                if ((var_r31 != 7) && (var_r31 != 3) && (var_r31 != 5) && (var_r31 != 6)) {
                    GSmodelSetScale((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &scl);
                }
                if ((var_r28 != NULL) && ((u8) M2C_NAMED(((ModelSequenceLayout*)(var_r30)), u8 *, 0x58, m_unk58) == 0) && (temp_r27_3 != NULL)) {
                    if (THIS_F(u16 *, 0x48, unk48) & 0x10) {
                        temp_r3_4 = (float *)(GSmodelGetBound((_GSmodel*)(var_r28)));
                        GSboundGetWorldPosition(temp_r3_4, (float *)&tmp);
                        GSmodelSetPosition((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &tmp);
                        GSboundGetLocalPosition((GCsptr)((GCsptr) temp_r3_4), (float *)&tmp);
                        tmp.x = -tmp.x;
                        tmp.y = -tmp.y;
                        tmp.z = -tmp.z;
                        GSmodelAddNull((_GSmodel*)(var_r28), (Vec*)&tmp, (Vec*)(NULL), (Vec*)(NULL));
                    }
                    GSmodelAttachToGSpart((_GSmodel*)(var_r28), (GSpart*)(temp_r27_3), var_r31, 0U, 1U);
                    THIS_F(s8 *, 0x4B, unk4B) = 1;
                    M2C_NAMED(((ModelSequenceLayout*)(var_r30)), u8 *, 0x58, m_unk58) = 1U;
                    GSpartFree((GSpart*)(temp_r27_3));
                    if ((u32) var_r31 <= 7U) {
                        switch (var_r31) {
                        case 1:
                        case 6:
                            GSmodelSetRotation((_GSmodel*)(var_r28), &rot);
                            break;
                        case 2:
                        case 5:
                            GSmodelSetPosition((_GSmodel*)(var_r28), &pos);
                            break;
                        case 3:
                            GSmodelSetRotation((_GSmodel*)(var_r28), &rot);
                            GSmodelSetPosition((_GSmodel*)(var_r28), &pos);
                            break;
                        case 0:
                            GSmodelSetRotation((_GSmodel*)(var_r28), &rot);
                            GSmodelSetPosition((_GSmodel*)(var_r28), &pos);
                            break;
                        }
                    }
                }
            } else {
                if (temp_r3_3 & 1) {
                    temp_r4_2 = THIS_F(u8 *, 5, unk05);
                    if ((temp_r4_2 != 0) && (temp_r4_2 != 0xFF) && (temp_r3_5 = (unsigned char *)(((WazaSequence*)(THIS_F(WazaSequence * *, 0x2C, seq)))->GetEntryFromID(temp_r4_2)), (((s32) M2C_NAMED(((ModelEntry*)(temp_r3_5)), s32 *, 0xC, type) == 2) != 0))) {
                        temp_r3_6 = M2C_NAMED(((ModelEntry*)(temp_r3_5)), _GSmodel **, 0x4C, model);
                        if (M2C_NAMED(((ModelEntry*)(temp_r3_5)), f32 *, 0x1C, m_start) > THIS_F(f32 *, 0x1C, m_start)) {
                            var_r30_2 = NULL;
                        } else if (temp_r3_6 != NULL) {
                            var_r30_2 = GSmodelGetPart((_GSmodel*)(temp_r3_6), (s32) THIS_F(s16 *, 0x12, unk12));
                        } else {
                            goto block_68;
                        }
                    } else {
                        goto block_68;
                    }
                } else {
                    var_r3 = seq->m_owner;
                    var_r3 = (s32) M2C_NAMED(((ModelSequenceLayout*)(var_r3)), s32 *, 0x8, m_kind) == 1 ? var_r3 : NULL;
                    if (var_r3 != NULL) {
                        var_r30_2 = ((ModelSequence*)(var_r3))->GetPart((enumNullJointName)((s32) THIS_F(u8 *, 0x10, unk10)));
                    } else {
block_68:
                        var_r30_2 = NULL;
                    }
                }
                if (var_r30_2 != NULL) {
                    GSmodelAttachToGSpart((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), (GSpart*)(var_r30_2), var_r31, ((u16) THIS_F(u16 *, 0xA, unk0A) >> 1U) & 1, 1U);
                    THIS_F(s8 *, 0x4B, unk4B) = 1;
                    if ((u32) var_r31 <= 7U) {
                        switch (var_r31) {
                        case 4:
                            GSmodelSetScale((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &scl);
                            break;
                        case 1:
                            GSmodelSetScale((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &scl);
                            GSmodelSetRotation((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &rot);
                            break;
                        case 5:
                            GSmodelSetPosition((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &pos);
                            break;
                        case 2:
                            GSmodelSetScale((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &scl);
                            GSmodelSetPosition((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &pos);
                            break;
                        case 6:
                            GSmodelSetRotation((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &rot);
                            break;
                        case 3:
                            GSmodelSetPosition((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &pos);
                            GSmodelSetRotation((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), &rot);
                            break;
                        }
                    }
                    GSpartFree((GSpart*)(var_r30_2));
                }
            }
        }
    }
    GSmodelSetVisibility((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), 1U);
    GSmodelSetBoundCheck((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), 0U);
    if (THIS_F(u16 *, 0x48, unk48) & 1) {
        sp8 = jtbl_2422;
        GSmodelSetRenderLayer((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), 1, (s32*)(&sp8));
    }
    if (THIS_F(u16 *, 0x48, unk48) & 4) {
        GSmodelSet60fpsAnimFlag((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), 1U);
    }
    if ((s32) THIS_F(s32 *, 0x38, unk38) >= 0) {
        u8 cmpv = GSmodelCanAnimate((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)));
        if (cmpv != 0) {
            GSmodelSetAnimIndex((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), (u32) THIS_F(s32 *, 0x38, unk38));
            GSmodelSetAnimType((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), THIS_F(s32 *, 0x34, unk34));
            GSmodelSetAnimRate((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), 0.5f);
            GSmodelSetAnimFrame((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), 0.0f);
            GSmodelStartAnimation((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)));
        } else {
            THIS_F(s32 *, 0x38, unk38) = -1;
        }
    }
    if (((s32) THIS_F(s32 *, 0x38, unk38) != (temp_r3_7 = THIS_F(s32 *, 0x40, unk40))) && (temp_r3_7 >= 0)) {
        u8 cmpv = GSmodelCanTexAnimate((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)));
        if (cmpv != 0) {
            GSmodelSetTexAnimIndex((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), (u32) THIS_F(s32 *, 0x40, unk40));
            GSmodelSetTexAnimType((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), THIS_F(s32 *, 0x3C, unk3C));
            GSmodelSetTexAnimRate((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), 0.5f);
            GSmodelSetTexAnimFrame((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), 0.0f);
            GSmodelStartTexAnimation((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)));
        } else {
            THIS_F(s32 *, 0x40, unk40) = -1;
        }
    }
    if ((THIS_F(u16 *, 0x48, unk48) & 0x20) && (wazaSequenceSysGetModelShadowLight() != 0) && (wazaSequenceSysGetModelShadowCount() != 0)) {
        GSmodelSetShadowFlags((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), 1U);
        GSmodelSetShadowLight((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), (GSlight*)(wazaSequenceSysGetModelShadowLight()));
        GSmodelSetShadowSurface((_GSmodel*)(THIS_F(_GSmodel * *, 0x4C, model)), wazaSequenceSysGetModelShadowCount(), (void*)((u8 *) wazaSequenceSysGetModelShadowList()));
    }
    THIS_F(s32 *, 0x18, m_state) = 1;
    THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
    return 1;
}
}

extern "C++" {
bool ModelEntry::Update(float dt) {
    m_nextTime += dt;
    _GSmodel* model = THIS_F(_GSmodel* *, 0x4C, model);
    if (model == 0) {
        return 0;
    }
    if (m_state == 3) {
        return 1;
    }
    ModelSequence* ms = seq->m_owner;
    if (M2C_NAMED(((ModelSequenceLayout*)(ms)), s32*, 0x8, m_kind) != 1 && !(unk0A & 4) && THIS_F(u8 *, 0x4A, unk4A) == 0 &&
        THIS_F(u8 *, 0x4B, unk4B) == 0) {
        GSvec pos;
        GSvec rot;
        GSvec scale;
        ms->GetPosition(&pos);
        ms->GetRotation(&rot);
        ms->GetScale(&scale);
        GSmodelSetPosition(THIS_F(_GSmodel* *, 0x4C, model), &pos);
        GSmodelSetRotation(THIS_F(_GSmodel* *, 0x4C, model), &rot);
        GSmodelSetScale(THIS_F(_GSmodel* *, 0x4C, model), &scale);
    }
    bool ended;
    if (THIS_F(s32 *, 0x38, unk38) < 0) {
        ended = 1;
    } else {
        switch (THIS_F(s32 *, 0x34, unk34)) {
        case 1:
            {
                f32* e = (f32*)params;
                e += unk08;
                ended = m_start + GC_AT(f32, e, -4) >= seq->m_time;
            }
            break;
        case 0:
        default:
            ended = GSmodelHasAnimationEnded(THIS_F(_GSmodel* *, 0x4C, model));
            break;
        }
    }
    if (THIS_F(s32 *, 0x38, unk38) != THIS_F(s32 *, 0x40, unk40) && 0 <= THIS_F(s32 *, 0x40, unk40)) {
        bool texEnded;
        switch (THIS_F(s32 *, 0x3C, unk3C)) {
        case 1:
            {
                f32* e = (f32*)params;
                e += unk08;
                texEnded = m_start + GC_AT(f32, e, -4) >= seq->m_time;
            }
            break;
        case 0:
        default:
            texEnded = GSmodelHasTexAnimationEnded(THIS_F(_GSmodel* *, 0x4C, model));
            break;
        }
        ended = ended && texEnded;
    }
    if (ended) {
        if (THIS_F(u16 *, 0x48, unk48) & 2) {
            m_state = 3;
            return 1;
        }
        return 0;
    }
    return 1;
}
}

extern "C++" {
static inline ModelSequence* _asModelSequence(ModelSequence* seq) {
    if (M2C_NAMED(((ModelSequenceLayout*)(seq)), s32 *, 0x8, m_kind) == 1) {
        return seq;
    }
    return NULL;
}

void ModelEntry::Stop(bool p0) {
    GSvec pos;
    GSvec rot;
    GSvec partPos;
    ModelSequence* seq;
    _GSmodel* part = NULL;

    if (!(THIS_F(s32 *, 0x18, m_state) == 1 || (THIS_F(s32 *, 0x18, m_state) != 2 && p0))) {
        return;
    }
    THIS_F(s32 *, 0x18, m_state) = 2;
    if (THIS_F(_GSmodel * *, 0x4C, model) == NULL) {
        return;
    }
    seq = _asModelSequence(this->seq->m_owner);
    if (seq != NULL) {
        part = M2C_NAMED(((ModelSequenceLayout*)(seq)), _GSmodel **, 0x94, m_model);
    }
    GSmodelStopAnimation(THIS_F(_GSmodel * *, 0x4C, model));
    GSmodelStopTexAnimation(THIS_F(_GSmodel * *, 0x4C, model));
    GSmodelSetVisibility(THIS_F(_GSmodel * *, 0x4C, model), 0);
    if (part != NULL && THIS_F(u8 *, 0x4A, unk4A) != 0) {
        GSmodelGetPosition(THIS_F(_GSmodel * *, 0x4C, model), &pos);
        GSmodelGetRotation(THIS_F(_GSmodel * *, 0x4C, model), &rot);
        GSmodelGetPosition(part, &partPos);
        PSVECSubtract((Vec*)&partPos, (Vec*)&pos, (Vec*)&partPos);
        M2C_NAMED(((ModelSequenceLayout*)(seq)), u8 *, 0x58, m_unk58) = 0;
        if (THIS_F(u8 *, 0x4B, unk4B) != 0) {
            THIS_F(u8 *, 0x4B, unk4B) = 0;
            GSmodelDetachFromGSpart(part, 0);
        }
        seq->ResetPosition();
        seq->ResetRotation();
        seq->ResetScale();
        if (THIS_F(u16 *, 0x48, unk48) & 0x10) {
            GSmodelRemoveNull(part);
        }
        if (THIS_F(u16 *, 0x48, unk48) & 8) {
            GSmodelAddNull(part, (Vec*)&partPos, NULL, NULL);
        }
    }
    if (THIS_F(u8 *, 0x4B, unk4B) != 0) {
        GSmodelDetachFromGSpart(THIS_F(_GSmodel * *, 0x4C, model), 0);
    }
    GSmodelSetPosition(THIS_F(_GSmodel * *, 0x4C, model), (GSvec*)&zeroVector);
    GSmodelSetRotation(THIS_F(_GSmodel * *, 0x4C, model), (GSvec*)&zeroVector);
    GSmodelSetScale(THIS_F(_GSmodel * *, 0x4C, model), (GSvec*)&unitScaleVector);
}
}

extern "C++" {
void ParticleEntry::SetRenderCamera(_GScamera* camera) {
    if (THIS_F(GSparticleBank * *, 0x38, bank) != 0) {
        GSparticleBankSetCamera(THIS_F(GSparticleBank * *, 0x38, bank), camera);
    }
}
}

extern "C++" {
s32 ParticleEntry::Start() {
    s32 temp_r29;
    GSpart *var_r27;
    GSparticleGenerator *temp_r3_3;
    u32 temp_r27;
    ModelSequence *var_r3;
    WazaSequence *temp_r3;
    ModelSequence *ms;
    GSvec pos;
    GSvec rot;
    GSvec scl;
    _GSmodel *temp_r30_2;
    _GSmodel *temp_r3_6;
    f32 temp_f1;
    ModelSequence *var_r29;
    s32 temp_r30_3;
    s32 var_r31;
    u16 temp_r3_4;
    u32 temp_r0_2;
    u8 temp_r0;
    u8 temp_r4;
    u8 temp_r4_2;
    u8 *temp_r3_2;
    u8 *temp_r3_5;

    if ((GSparticleBank *) THIS_F(GSparticleBank * *, 0x38, bank) == NULL) {
        return 0;
    }
    temp_r3 = THIS_F(WazaSequence * *, 0x2C, seq);
    temp_r27 = temp_r3->m_flags;
    ms = temp_r3->m_owner;
    if (!(temp_r27 & 0x2000) && ((u8) M2C_NAMED(((ModelSequenceLayout*)(ms)), u8 *, 0x6, m_visible) == 0)) {
        THIS_F(s32 *, 0x18, m_state) = 2;
        THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
        return 1;
    }
    temp_r0 = THIS_F(u8 *, 0x11, unk11);
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
    if ((s32) M2C_NAMED(((ModelSequenceLayout*)(ms)), s32 *, 0x8, m_kind) == 1) {
        var_r29 = ms;
    } else {
        var_r29 = NULL;
    }
    if (var_r29 != NULL) {
        ms->GetPosition(&pos);
        ms->GetRotation(&rot);
        if (THIS_F(u16 *, 0xA, unk0A) & 1) {
            temp_r4 = THIS_F(u8 *, 5, unk05);
            if ((temp_r4 != 0) && (temp_r4 != 0xFF)) {
                temp_r3_2 = (unsigned char *)(((WazaSequence*)(THIS_F(WazaSequence * *, 0x2C, seq)))->GetEntryFromID(temp_r4));
                if ((M2C_NAMED(((ModelEntry*)(temp_r3_2)), f32 *, 0x1C, m_start) <= THIS_F(f32 *, 0x1C, m_start)) && ((s32) M2C_NAMED(((ModelEntry*)(temp_r3_2)), s32 *, 0xC, type) == 2)) {
                    temp_r30_2 = M2C_NAMED(((ModelEntry*)(temp_r3_2)), _GSmodel **, 0x4C, model);
                    if (temp_r30_2 != NULL) {
                        GSmodelForceAnimTransformUpdate((_GSmodel*)(temp_r30_2));
                        GSmodelGetPosition((_GSmodel*)(temp_r30_2), &pos);
                        GSmodelGetRotation((_GSmodel*)(temp_r30_2), &rot);
                    }
                }
            }
        }
        temp_f1 = ((ModelSequence*)(var_r29))->GetModelScale(!(temp_r27 & 0x10000000));
        scl.x = temp_f1;
        scl.y = temp_f1;
        scl.z = temp_f1;
    } else {
        ms->GetPosition(&pos);
        ms->GetRotation(&rot);
        ms->GetScale(&scl);
    }
    if (THIS_F(u16 *, 0xA, unk0A) & 0x20) {
        scl.z = 1.0f;
        scl.y = 1.0f;
        scl.x = 1.0f;
    }
    THIS_F(GSparticleGenerator * *, 0x3C, generator) = GSparticleCreateGenerator((GSparticleBank*)(THIS_F(GSparticleBank * *, 0x38, bank)), THIS_F(s32 *, 0x30, unk30), THIS_F(u32 *, 0x34, unk34) & 1);
    THIS_F(s32 *, 0x40, unk40) = 0;
    temp_r3_3 = THIS_F(GSparticleGenerator * *, 0x3C, generator);
    if (temp_r3_3 == NULL) {
        return 0;
    }
    if (THIS_F(u32 *, 0x34, unk34) & 4) {
        GSparticleSetOffsetRotationInLocal(temp_r3_3, 1, (THIS_F(u32 *, 0x34, unk34) >> 4) & 1);
    }
    if (THIS_F(u32 *, 0x34, unk34) & 8) {
        GSparticleSetVelocityRotationInLocal((PCARG(u32, void*))generator, 1);
    }
    if (THIS_F(u32 *, 0x34, unk34) & 0x80) {
        GSparticleSetParticleTextureScaling((PCARG(u32, void*))generator, 1);
    }
    if (THIS_F(u32 *, 0x34, unk34) & 0x800) {
        GSparticleSetNodeScaling((PCARG(u32, void*))generator, 1);
    }
    if (THIS_F(u32 *, 0x34, unk34) & 0x1000) {
        GSparticleSetRandomVelocityScaling((PCARG(u32, void*))generator, 1);
    }
    temp_r0_2 = THIS_F(u32 *, 0x34, unk34);
    temp_r30_3 = (temp_r0_2 >> 5U) & 1;
    temp_r29 = (temp_r0_2 >> 9U) & 1;
    GSparticleSetTornadoScaling((PCARG(u32, void*))generator, (temp_r0_2 >> 8U) & 1, (temp_r0_2 >> 0xAU) & 1);
    temp_r3_4 = THIS_F(u16 *, 0xA, unk0A);
    if (temp_r3_4 & 4) {
        GSparticleSetGeneratorPosition((GSparticleGenerator*)(THIS_F(GSparticleGenerator * *, 0x3C, generator)), (Vec*)((Vec *) &zeroVector));
        GSparticleSetGeneratorRotation((PCARG(u32, void*))generator, (f32 *) &zeroVector);
        if (THIS_F(u16 *, 0xA, unk0A) & 8) {
            battleGridGetNormalisedScale(&scl);
            GSparticleSetGeneratorScale((PCARG(u32, void*))generator, (f32*)&scl, temp_r30_3, temp_r29);
        } else {
            scl.x = 1.0f;
            scl.y = 1.0f;
            scl.z = 1.0f;
            GSparticleSetGeneratorScale((PCARG(u32, void*))generator, (f32*)&scl, temp_r30_3, temp_r29);
        }
        THIS_F(s32 *, 0x18, m_state) = 1;
        THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
        return 1;
    }
    if (temp_r3_4 & 1) {
        temp_r4_2 = THIS_F(u8 *, 5, unk05);
        if ((temp_r4_2 != 0) && (temp_r4_2 != 0xFF) && (temp_r3_5 = (unsigned char *)(((WazaSequence*)(THIS_F(WazaSequence * *, 0x2C, seq)))->GetEntryFromID(temp_r4_2)), (((s32) M2C_NAMED(((ModelEntry*)(temp_r3_5)), s32 *, 0xC, type) == 2) != 0))) {
            temp_r3_6 = M2C_NAMED(((ModelEntry*)(temp_r3_5)), _GSmodel **, 0x4C, model);
            if (M2C_NAMED(((ModelEntry*)(temp_r3_5)), f32 *, 0x1C, m_start) > THIS_F(f32 *, 0x1C, m_start)) {
                var_r27 = NULL;
            } else if (temp_r3_6 != NULL) {
                var_r27 = GSmodelGetPart((_GSmodel*)(temp_r3_6), (s32) THIS_F(s16 *, 0x12, unk12));
            } else {
                goto block_60;
            }
        } else {
            goto block_60;
        }
    } else {
        var_r3 = ((WazaSequence*)THIS_F(WazaSequence * *, 0x2C, seq))->m_owner;
        var_r3 = (s32) M2C_NAMED(((ModelSequenceLayout*)(var_r3)), s32 *, 0x8, m_kind) == 1 ? var_r3 : NULL;
        if (var_r3 != NULL) {
            var_r27 = ((ModelSequence*)(var_r3))->GetPart((enumNullJointName)((s32) THIS_F(u8 *, 0x10, unk10)));
        } else {
block_60:
            var_r27 = NULL;
        }
    }
    if (var_r27 != NULL) {
        if (var_r31 != 0) {
            GSparticleAttachGeneratorToGSpart((PCARG(u32, void*))generator, (float *)var_r27, (s32)(var_r31), (s32)(((u16) THIS_F(u16 *, 0xA, unk0A) >> 1U) & 1), (s32)(1), (s32)(((u32) THIS_F(u32 *, 0x34, unk34) >> 1U) & 1));
            THIS_F(s32 *, 0x40, unk40) = 1;
            switch (var_r31) {
                case 1:
                    GSparticleSetGeneratorRotation((PCARG(u32, void*))generator, (float *)&rot);
                case 4:
                    GSparticleSetGeneratorScale((PCARG(u32, void*))generator, (f32*)&scl, temp_r30_3, temp_r29);
                    break;
                case 2:
                    GSparticleSetGeneratorScale((PCARG(u32, void*))generator, (f32*)&scl, temp_r30_3, temp_r29);
                case 5:
                    GSparticleSetGeneratorPosition((GSparticleGenerator*)(THIS_F(GSparticleGenerator * *, 0x3C, generator)), (Vec*)&pos);
                    break;
                case 3:
                    GSparticleSetGeneratorPosition((GSparticleGenerator*)(THIS_F(GSparticleGenerator * *, 0x3C, generator)), (Vec*)&pos);
                case 6:
                    GSparticleSetGeneratorRotation((PCARG(u32, void*))generator, (float *)&rot);
                    break;
                case 0:
                case 7:
                    break;
                }
        }
        GSpartFree((GSpart*)(var_r27));
    } else {
        GSparticleSetGeneratorPosition((GSparticleGenerator*)(THIS_F(GSparticleGenerator * *, 0x3C, generator)), (Vec*)&pos);
        GSparticleSetGeneratorRotation((PCARG(u32, void*))generator, (float *)&rot);
        GSparticleSetGeneratorScale((PCARG(u32, void*))generator, (f32*)&scl, temp_r30_3, temp_r29);
    }
    THIS_F(s32 *, 0x18, m_state) = 1;
    THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
    return 1;
}
}

extern "C++" {
bool ParticleEntry::Update(float dt) {
    GSvec pos;
    GSvec rot;
    GSvec scale;

    THIS_F(f32 *, 0x20, m_nextTime) += dt;
    if (GSparticleIsGeneratorAlive((PCARG(u32, void*))generator) == 0) {
        generator = 0;
        return false;
    }
    SeqCameraTarget* target = (SeqCameraTarget*)seq->m_owner;
    if (((ModelSequenceLayout*)target)->m_kind != 1 && !(THIS_F(u16 *, 0xA, unk0A) & 4) && THIS_F(s32 *, 0x40, unk40) == 0) {
        u32 flags = THIS_F(u32 *, 0x34, unk34);
        target->GetPosition((f32*)&pos);
        target->GetRotation((f32*)&rot);
        target->GetScale((f32*)&scale);
        u16 local = (flags >> 5) & 1;
        GSparticleSetGeneratorPosition(generator, (Vec*)&pos);
        GSparticleSetGeneratorRotation((PCARG(u32, void*))generator, (f32*)&rot);
        GSparticleSetGeneratorScale((PCARG(u32, void*))generator, (f32*)&scale, local, (flags >> 9) & 1);
    }
    return true;
}
}

extern "C++" {
void ParticleEntry::End() {
    void* generator = THIS_F(void* *, 0x3C, generator);
    if (generator != 0) {
        GSparticleStopGenerator(generator);
    }
}
}

extern "C++" {
void ParticleEntry::Stop(bool p0) {
    s32 temp_r3;
    GSparticleGenerator* temp_r3_2;

    temp_r3 = THIS_F(s32 *, 0x18, m_state);
    if ((temp_r3 != 2) && ((p0 != 0) || (temp_r3 == 1))) {
        THIS_F(s32 *, 0x18, m_state) = 2;
        temp_r3_2 = generator;
        if (temp_r3_2 != 0) {
            GSparticleDestroyGenerator((PCARG(s32, void*))temp_r3_2, 1);
        }
        generator = 0;
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

    temp_r3 = THIS_F(WazaSequence * *, 0x2C, seq);
    temp_r3_2 = (u8*)temp_r3->m_owner;
    if (!(temp_r3->m_flags & 0x2000) && ((ModelSequenceLayout*)temp_r3_2)->m_visible == 0) {
        THIS_F(s32 *, 0x18, m_state) = 2;
        THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
        return 1;
    }
    ((ModelSequence*)temp_r3_2)->GetPosition(&pos);
    if (THIS_F(u16 *, 0xA, unk0A) & 1) {
        temp_r4 = THIS_F(u8 *, 5, unk05);
        if ((temp_r4 != 0) && (temp_r4 != 0xFF) && (temp_r3_3 = (unsigned char *)(((WazaSequence*)(THIS_F(WazaSequence * *, 0x2C, seq)))->GetEntryFromID(temp_r4)), (((s32) M2C_NAMED(((ModelEntry*)(temp_r3_3)), s32 *, 0xC, type) == 2) != 0))) {
            temp_r3_4 = M2C_NAMED(((ModelEntry*)(temp_r3_3)), _GSmodel **, 0x4C, model);
            if (M2C_NAMED(((ModelEntry*)(temp_r3_3)), f32 *, 0x1C, m_start) > THIS_F(f32 *, 0x1C, m_start)) {
                var_r30 = NULL;
            } else if (temp_r3_4 != NULL) {
                var_r30 = GSmodelGetPart((_GSmodel*)(temp_r3_4), (s32) THIS_F(s16 *, 0x12, unk12));
            } else {
                goto block_16;
            }
        } else {
            goto block_16;
        }
    } else {
        var_r3 = seq->m_owner;
        var_r3 = (s32) M2C_NAMED(((ModelSequenceLayout*)(var_r3)), s32 *, 0x8, m_kind) == 1 ? var_r3 : NULL;
        if (var_r3 != NULL) {
            var_r30 = ((ModelSequence*)(var_r3))->GetPart((enumNullJointName)((s32) THIS_F(u8 *, 0x10, unk10)));
        } else {
block_16:
            var_r30 = NULL;
        }
    }
    if (var_r30 != NULL) {
        GSpartGetTransform((GSpart*)(var_r30), &pos, (GSvec*)(NULL), (GSvec*)(NULL));
        GSpartFree((GSpart*)(var_r30));
    }
    GSlensFlareSetSunPosition(THIS_F(u32 *, 0x30, unk30), (Vec*)&pos);
    GSlensFlareSetVisible(THIS_F(u32 *, 0x30, unk30), 1U);
    THIS_F(s32 *, 0x18, m_state) = 1;
    THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
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

    THIS_F(f32 *, 0x20, m_nextTime) = (f32) (THIS_F(f32 *, 0x20, m_nextTime) + p0);
    if ((THIS_F(f32 *, 0x20, m_nextTime) - THIS_F(f32 *, 0x1C, m_start)) >= THIS_F(f32 *, 0x34, unk34)) {
        return 0;
    }
    temp_r3 = seq->m_owner;
    temp_r3->GetPosition(&pos);
    if (THIS_F(u16 *, 0xA, unk0A) & 1) {
        temp_r4 = THIS_F(u8 *, 5, unk05);
        if ((temp_r4 != 0) && (temp_r4 != 0xFF) && (temp_r3_2 = (unsigned char *)(((WazaSequence*)(THIS_F(WazaSequence * *, 0x2C, seq)))->GetEntryFromID(temp_r4)), (((s32) M2C_NAMED(((ModelEntry*)(temp_r3_2)), s32 *, 0xC, type) == 2) != 0))) {
            temp_r3_3 = M2C_NAMED(((ModelEntry*)(temp_r3_2)), _GSmodel **, 0x4C, model);
            if (M2C_NAMED(((ModelEntry*)(temp_r3_2)), f32 *, 0x1C, m_start) > THIS_F(f32 *, 0x1C, m_start)) {
                var_r31 = NULL;
            } else if (temp_r3_3 != NULL) {
                var_r31 = GSmodelGetPart((_GSmodel*)(temp_r3_3), (s32) THIS_F(s16 *, 0x12, unk12));
            } else {
                goto block_15;
            }
        } else {
            goto block_15;
        }
    } else {
        var_r3 = seq->m_owner;
        var_r3 = (s32) M2C_NAMED(((ModelSequenceLayout*)(var_r3)), s32 *, 0x8, m_kind) == 1 ? var_r3 : NULL;
        if (var_r3 != NULL) {
            var_r31 = ((ModelSequence*)(var_r3))->GetPart((enumNullJointName)((s32) THIS_F(u8 *, 0x10, unk10)));
        } else {
block_15:
            var_r31 = NULL;
        }
    }
    if (var_r31 != NULL) {
        GSpartGetTransform((GSpart*)(var_r31), &pos, (GSvec*)(NULL), (GSvec*)(NULL));
        GSpartFree((GSpart*)(var_r31));
    }
    GSlensFlareSetSunPosition(THIS_F(u32 *, 0x30, unk30), (Vec*)&pos);
    return 1;
}
}

extern "C++" {
void LensFlareEntry::Stop(bool p0) {
    GSlensFlareSetVisible(unk30, 0U);
}
}

extern "C++" {
s32 EffectEntry::Start() {
    ModelSequence* model = seq->m_owner;
    ModelSequence* owner;
    if (M2C_NAMED(((ModelSequenceLayout*)(model)), s32*, 0x8, m_kind) == 1) {
        owner = model;
    } else {
        owner = 0;
    }
    bool alpha;
    void* val = 0;
    f32 scale = 1.0f;
    if (m_effect == 0) {
        return 0;
    }
    if (m_keyed != 0) {
        if (m_keys == 0 || m_keyCount == 0) {
            return 0;
        }
        m_time = 0.0f;
        m_curKey = 0;
    } else {
        m_elapsed = 0.0f;
    }
    u32 flags = seq->m_flags;
    if (!(flags & 0x2000) && M2C_NAMED(((ModelSequenceLayout*)(model)), u8*, 0x6, m_visible) == 0) {
        m_state = 2;
        m_nextTime = m_start;
        return 1;
    }
    if (owner != 0) {
        val = ((ModelSequenceLayout*)owner)->m_model;
        scale = owner->GetModelScale(!(flags & 0x10000000));
    }
    switch (m_type) {
    case 0: {
        filterEffect* e = (filterEffect*)m_effect;
        if (e->m_modulate == 2) {
            e->m_target = val;
        }
        if (owner != 0 && e->m_modulate == 2) {
            e->m_useSaved = ((ModelSequenceLayout*)owner)->m_unk60;
        }
        u8* key = (u8*)&m_keys[m_curKey];
        e->m_color[0] = key[0];
        e->m_color[1] = key[1];
        e->m_color[2] = key[2];
        alpha = false;
        if (e->m_modulate == 0 || e->m_resetPE != 0) {
            alpha = true;
        }
        e->m_color[3] = alpha ? key[3] : 0xFF;
        break;
    }
    case 6: {
        envMapEffect* e = (envMapEffect*)m_effect;
        if (owner == 0) {
            return 0;
        }
        e->m_model = (GSmodel*)val;
        e->m_blend = m_keys[m_curKey].value.from;
        break;
    }
    case 7: {
        blurEffect* e = (blurEffect*)m_effect;
        if (e->m_useFB == 0 && owner == 0) {
            return 0;
        }
        if (e->m_useFB == 0) {
            e->m_tex = (GStexture*)val;
        }
        e->m_strength = m_keys[m_curKey].value.from;
        break;
    }
    case 5: {
        GSpart* part;
        GSeffect* e;
        e = m_effect;
        part = 0;
        GSvec pos;
        if (unk0A & 1) {
            u8 id = unk05;
            if (id != 0 && id != 0xFF) {
                SequenceEntry* ent = (SequenceEntry*)seq->GetEntryFromID(id);
                if (M2C_NAMED(((ModelEntry*)(ent)), s32*, 0xC, type) == 2) {
                    _GSmodel* gm = M2C_NAMED(((ModelEntry*)(ent)), _GSmodel**, 0x4C, model);
                    if (ent->m_start > m_start) {
                        part = 0;
                    } else if (gm != 0) {
                        part = GSmodelGetPart(gm, THIS_F(s16 *, 0x12, unk12));
                    }
                }
            }
        } else {
            ModelSequence* m = seq->m_owner;
            m = M2C_NAMED(((ModelSequenceLayout*)(m)), s32*, 0x8, m_kind) == 1 ? m : 0;
            if (m != 0) {
                part = m->GetPart((enumNullJointName)unk10);
            }
        }
        if (part != 0) {
            GSpartGetTransform(part, &pos, 0, 0);
            GSpartFree(part);
        } else {
            model->GetPosition(&pos);
        }
#ifdef __MWERKS__
        M2C_FIELD(e, f32*, 0x54) = M2C_FIELD(&pos, f32*, 0);
        M2C_FIELD(e, f32*, 0x58) = M2C_FIELD(&pos, f32*, 4);
        M2C_FIELD(e, f32*, 0x5C) = M2C_FIELD(&pos, f32*, 8);
        M2C_FIELD(e, f32*, 0x14) = scale;
#else
        leafEffectSetOrigin((leafEffect*)e, pos.x, pos.y, pos.z, scale);
#endif
        break;
    }
    case 1:
        ((boneFillEffect*)m_effect)->m_owner = (BoneFillOwner*)owner;
        break;
    case 9:
        break;
    case -1:
    default:
        return 0;
    }
    if (m_effect->Start() == 0) {
        return 0;
    }
    m_state = 1;
    m_nextTime = m_start;
    return 1;
}
}

extern "C++" {
inline u8 EffectLerp(f32 t, f32 from, f32 to) {
    return t * (to - from) + from;
}

bool EffectEntry::Update(f32 dt) {
    f32 t;

    m_nextTime += dt;
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
            m_state = 3;
        }
    } else {
        t = 1.0f;
        m_elapsed += dt;
        if (m_keyCount != 0) {
            m_state = 3;
        } else if (m_curKey != 0) {
            if (m_elapsed >= m_time) {
                return false;
            }
            t = m_elapsed / m_time;
        }
    }
    switch (m_type) {
    case 0: {
        bool useAlpha;
        EffectKey* key = &m_keys[m_curKey];
        u8* fx = (u8*)m_effect;
        f32 a = t;
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
    if (m_keyed == 0 || m_keys == NULL || m_keyCount == 0) {
        return;
    }
    while (m_keys[m_curKey].duration < 0.0f) {
        m_curKey++;
        if (m_curKey >= m_keyCount) {
            return;
        }
    }
}

extern "C++" {
void EffectEntry::Stop(bool p0) {
    GSeffect *temp_r3;
    s32 temp_r5;

    temp_r5 = THIS_F(s32 *, 0x18, m_state);
    if ((temp_r5 != 2) && ((p0 != 0) || (temp_r5 == 1))) {
        THIS_F(s32 *, 0x18, m_state) = 2;
        temp_r3 = THIS_F(GSeffect * *, 0x30, m_effect);
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

    temp_r3 = THIS_F(u16 *, 0x34, unk34);
    if (temp_r3 & 1) {
        if ((u8 *) gSoundThread != NULL) {
            return 0;
        }
        temp_ret = (unsigned char *)(GSthreadCreate(0x15, 0x4E20, 0x2000, 1, 1, (void (*)(void))soundOpenPlayME));
        temp_r3_2 = temp_ret;
        gSoundThread = (GSthread *)(temp_r3_2);
        if (temp_r3_2 != NULL) {
            GSthreadSetArgs((void*)(temp_r3_2), 3, THIS_F(u32 *, 0x30, unk30), 0, 0xFF);
            THIS_F(s32 *, 0x18, m_state) = 1;
            THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
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
        ModelSequence* ms = seq->m_owner;
        ms->GetPosition(&pos);
        ms->GetRotation(&rot);
        if (THIS_F(u16 *, 0xA, unk0A) & 1) {
            temp_r4 = THIS_F(u8 *, 5, unk05);
            if ((temp_r4 != 0) && (temp_r4 != 0xFF)) {
                temp_r3_3 = (unsigned char *)(((WazaSequence*)(THIS_F(WazaSequence * *, 0x2C, seq)))->GetEntryFromID(temp_r4));
                if ((M2C_NAMED(((ModelEntry*)(temp_r3_3)), f32 *, 0x1C, m_start) <= THIS_F(f32 *, 0x1C, m_start)) && ((s32) M2C_NAMED(((ModelEntry*)(temp_r3_3)), s32 *, 0xC, type) == 2)) {
                    temp_r30_2 = M2C_NAMED(((ModelEntry*)(temp_r3_3)), _GSmodel **, 0x4C, model);
                    if (temp_r30_2 != NULL) {
                        GSmodelForceAnimTransformUpdate((_GSmodel*)(temp_r30_2));
                        GSmodelGetPosition((_GSmodel*)(temp_r30_2), &pos);
                        GSmodelGetRotation((_GSmodel*)(temp_r30_2), &rot);
                    }
                }
            }
        }
        THIS_F(SndEmitter * *, 0x3C, emitter) = GSsndCreateEmitterParam(THIS_F(u32 *, 0x30, unk30), (SVec*)&pos, (SVec*)(&zeroVector), THIS_F(f32 *, 0x38, unk38), var_f31, 0x7FU, THIS_F(u8 *, 0x36, unk36));
        if ((SndEmitter *) THIS_F(SndEmitter * *, 0x3C, emitter) != NULL) {
            THIS_F(s32 *, 0x18, m_state) = 1;
            THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
            return 1;
        }
        goto block_24;
    }
block_24:
    if (GSsndPlay(THIS_F(u32 *, 0x30, unk30), 0, 0U) != 0) {
        THIS_F(s32 *, 0x18, m_state) = 1;
        THIS_F(f32 *, 0x20, m_nextTime) = (f32) THIS_F(f32 *, 0x1C, m_start);
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

    THIS_F(f32 *, 0x20, m_nextTime) = (f32) (THIS_F(f32 *, 0x20, m_nextTime) + p0);
    if (THIS_F(u16 *, 0x34, unk34) & 1) {
        if ((GSthread *) gSoundThread != NULL) {
            return GSthreadIsRunning((GSthread*)(gSoundThread));
        }
        return 0;
    }
    if ((SndEmitter *) THIS_F(SndEmitter * *, 0x3C, emitter) != NULL) {
        SeqCameraTarget* cam = (SeqCameraTarget*)seq->m_owner;
        cam->GetPosition(pos);
        cam->GetRotation(rot);
        if (THIS_F(u16 *, 0xA, unk0A) & 1) {
            temp_r4 = THIS_F(u8 *, 5, unk05);
            if ((temp_r4 != 0) && (temp_r4 != 0xFF)) {
                temp_r3 = (unsigned char *)(((WazaSequence*)(THIS_F(WazaSequence * *, 0x2C, seq)))->GetEntryFromID(temp_r4));
                if ((M2C_FIELD(temp_r3, f32 *, 0x1C) <= THIS_F(f32 *, 0x1C, m_start)) && ((s32) M2C_FIELD(temp_r3, s32 *, 0xC) == 2)) {
                    temp_r31_2 = M2C_FIELD(temp_r3, _GSmodel **, 0x4C);
                    if (temp_r31_2 != NULL) {
                        GSmodelForceAnimTransformUpdate((_GSmodel*)(temp_r31_2));
                        GSmodelGetPosition((_GSmodel*)(temp_r31_2), (GSvec*)pos);
                        GSmodelGetRotation((_GSmodel*)(temp_r31_2), (GSvec*)rot);
                    }
                }
            }
        }
        if (GSsndUpdateEmitter((SndEmitter*)(THIS_F(SndEmitter * *, 0x3C, emitter)), (SVec*)pos) != 0) {
            return GSsndCheckEmitter((SndEmitter*)(THIS_F(SndEmitter * *, 0x3C, emitter)));
        }
        return 0;
    }
    temp_r4_2 = GSsndGetStatus(THIS_F(u32 *, 0x30, unk30));
    return temp_r4_2 == 2 || temp_r4_2 == 3;
}
}

extern "C++" {
void SoundEntry::Stop(bool p0) {
    SndEmitter *temp_r3_2;
    s32 temp_r3;

    temp_r3 = THIS_F(s32 *, 0x18, m_state);
    if ((temp_r3 != 2) && ((p0 != 0) || (temp_r3 == 1))) {
        THIS_F(s32 *, 0x18, m_state) = 2;
        if (THIS_F(u16 *, 0x34, unk34) & 1) {
            gSoundThread = NULL;
        } else {
            temp_r3_2 = THIS_F(SndEmitter * *, 0x3C, emitter);
            if (temp_r3_2 != NULL) {
                GSsndFreeEmitter((SndEmitter*)(temp_r3_2));
                THIS_F(SndEmitter * *, 0x3C, emitter) = NULL;
            }
        }
        GSsndClose(THIS_F(u32 *, 0x30, unk30));
    }
}
}

s32 EventEntry::Start() {
    ModelSequence* target = seq->m_owner;
    ModelSequence* model;

    if (M2C_NAMED(((ModelSequenceLayout*)(target)), s32*, 0x8, m_kind) == 1) {
        model = target;
    } else {
        model = NULL;
    }
    switch (THIS_F(u32 *, 0x30, unk30)) {
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
            GSmodelRemoveNull(M2C_NAMED(((ModelSequenceLayout*)(model)), _GSmodel**, 0x94, m_model));
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
    m_state = 1;
    m_nextTime = m_start;
    return 1;
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
