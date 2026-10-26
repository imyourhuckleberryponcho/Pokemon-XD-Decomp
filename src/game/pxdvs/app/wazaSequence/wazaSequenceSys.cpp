#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

struct _GSmodel;
struct _GSmodelAnimCBData;
struct GSpart;
enum GSpartMixType {
    GS_PART_MIX_0
};
struct GSparticleGen;
struct GSparticleBank;
struct PartAnimData;
class WazaSequence;

enum enumNullJointName {
    NULL_JOINT_0,
    NULL_JOINT_1,
    NULL_JOINT_16 = 16
};
enum enumSectionMotionType {
    SECTION_MOTION_0,
    SECTION_MOTION_1,
    SECTION_MOTION_2
};
enum GSmodelAnimType {
    GS_ANIM_TYPE_0,
    GS_ANIM_TYPE_1
};

static inline u16 __OSf32tou16(register f32 inF) {
    u16 tmp;
    register u16* tmpPtr = &tmp;
    asm { psq_st inF, 0(tmpPtr), 1, 3 }
    return *tmpPtr;
}

static inline f32 __OSu16tof32(register const u16* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 3 }
    return ret;
}

struct MotionEntry {
    s32 type;
    s32 index;
};

struct MotionSection {
    u8 pad0[4];
    s32 count;
    u8 pad8[0x44];
    s32 joints[16];
    MotionEntry motions[8];
    s32 pad;
};

struct ColorInfo {
    s32 swap[4];
    u8 mod[4];
};

struct PkxEntry {
    u32 a;
    u32 b;
};

struct RareEntry {
    u16 id;
    u8 pad[2];
    u32 a;
    u32 b;
};

#define ALIGN32(x) (((u32)(x) + 0x1F) & ~0x1F)

struct PartAnimData {
    u8 enabled;
    u8 count;
    u8 parts[8];
    u8 tex[8];
    u8 id;
};

struct PkxHeader {
    s32 size;
    void* model;
    s32 unk8;
    GSparticleBank* particle;
    s32 count;
    s32 modelSize;
    u16 id;
    u16 type;
    PartAnimData anims[4];
    u8 flags;
    u8 pad69;
    u16 distortionID;
    u8 distortionParam;
    u8 pad6D;
    u16 headJoint;
    ColorInfo colors;
};

struct _GSmodelAnimCBData {
    s32 flags;
    s32 anim;
    void* owner;
};

extern "C" {
void GSmodelSetVisibility(_GSmodel* model, u8 visible);
void GSparticleSetBankVisibility(GSparticleBank* bank, u8 visible);
void GSparticleSetGeneratorVisibility(GSparticleGen* gen, u8 visible);
void GSparticleDestroyAllGenerators(GSparticleBank* bank, bool children);
s32 GSmodelGetAnimType(_GSmodel* model);
u8 GSmodelIsAnimating(_GSmodel* model);
f32 GSmodelGetAnimRate(_GSmodel* model);
void GSmodelSetTexAnimIndex(_GSmodel* model, s32 index);
void GSmodelSetTexAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetTexAnimFrame(_GSmodel* model, f32 frame);
void GSmodelSetTexAnimType(_GSmodel* model, s32 type);
void GSmodelStartTexAnimation(_GSmodel* model);
void GSmodelSetKeepPartAnimFlag(_GSmodel* model, s32 flag);
void GSmodelGetFrameCount(_GSmodel* model, f32* frames, s32 tex);
void GSmodelSetAnimEndedCallback(_GSmodel* model, void (*cb)(_GSmodel*, _GSmodelAnimCBData*), void* user);
void GSmodelLinkTexAnimToAnim(_GSmodel* model, s32 link);
void GSmodelGetAnimIndex(_GSmodel* model, s32* index, s32 tex);
void GSmodelSetAnimType(_GSmodel* model, s32 type);
void GSmodelSetAnimRate(_GSmodel* model, f32 rate);
u8 GSmodelHasAnimationEnded(_GSmodel* model);
void GSmodelSetAnimIndex(_GSmodel* model, s32 index);
void GSmodelSetAnimFrame(_GSmodel* model, f32 frame);
void GSmodelStartAnimation(_GSmodel* model);
void GSmodelStopAnimation(_GSmodel* model);
f32 GSmodelGetAnimFrame(_GSmodel* model);
void GSmodelRemoveNull(_GSmodel* model);
u16 GSmodelCenterNull(_GSmodel* model);
GSpart* GSmodelGetPart(_GSmodel* model, s32 joint);
f32 menuModelGetScale(u8 a, u16 b);
u8 GSgfxVideoGetVsyncRate(void);
void GSmodelSetDontResetPartAnimFlag(_GSmodel* model, s32 flag);
void GSparticleDestroyGenerator(GSparticleGen* gen, s32 children);
GSparticleGen* GSparticleCreateGenerator(GSparticleBank* bank, s32 a, s32 b);
void GSparticleSetOffsetRotationInLocal(GSparticleGen* gen, s32 a, s32 b);
void GSparticleSetParticleTextureScaling(GSparticleGen* gen, s32 a);
void GSparticleSetTornadoScaling(GSparticleGen* gen, s32 a, s32 b);
void GSparticleAttachGeneratorToGSpart(GSparticleGen* gen, GSpart* part, s32 a, s32 b, s32 c, s32 d);
void GSparticleSetGeneratorRotation(GSparticleGen* gen, GSvec* rot);
void GSparticleSetGeneratorScale(GSparticleGen* gen, GSvec* scale, s32 a, s32 b);
void GSpartFree(GSpart* part);
u8 GSmodelIsRootNullAdded(_GSmodel* model);
void GSmodelGetRootPosition(_GSmodel* model, GSvec* pos);
void GSmodelAddNull(_GSmodel* model, GSvec* pos, s32 a, s32 b);
}

extern "C" {
void GSpartUnregisterAnimMix(GSpart* part, s32 a);
void GSpartRegisterAnimMix(GSpart* part, s32 a, s32 b, f32 (*cb)(GSpart*, GSpartMixType, void*, GSvec*), void* user);
void GSmodelDisableColorSwap(_GSmodel* model);
void GSmodelDisableModulation(_GSmodel* model);
void GSmemFree(void* p);
void* GSmemAllocAlign(u32 size, u32 align);
void* memcpy(void* dst, const void* src, u32 n);
void DCFlushRange(void* p, u32 n);
void loadModel(void* archive, u32 group, u32 index, u32 id);
void GSresFreeResource(u32 group, u32 id);
void GSresIsUniqueID(u32 group, u32 id, u32 x);
void* GSresGetResource(u32 group, u32 id);
s32 wazaSequenceSysGetResID(void);
void GSmodelSetGroundPlane(_GSmodel* model, s32 a, f32 b);
void GSmodelRemoveRootJointAnimation(_GSmodel* model);
void GSmodelSetSkipFractionalFramesFlag(_GSmodel* model, s32 flag);
GSparticleBank* GSparticleLoad(void* data);
void GSmodelRecalculateBound(_GSmodel* model);
void GSmodelLinkToGSparticleBank(_GSmodel* model, GSparticleBank* bank);
void GSmodelSetGSparticleLinkAttachMode(_GSmodel* model, s32 mode);
void GSmodelCreateDistortion(_GSmodel* model, u16 id, u8 param);
void GSmodelEnableDistortion(_GSmodel* model);
void GSmodelSetBoundCheck(_GSmodel* model, s32 flag);
void GSmodelSetShadowFlags(_GSmodel* model, s32 flags);
void GSmodelSetShadowLight(_GSmodel* model, u32 light);
void GSmodelSetShadowSurface(_GSmodel* model, u32 count, s32 list);
void* GScameraGetActiveCamera(void);
void GScameraGetRotation(void* camera, GSvec* rot);
void GSpartGetTransform(GSpart* part, GSvec* pos, s32 a, s32 b);
f32 HSD_Randf(void);
void GSmodelSetRenderCamera(void* camera);
void GSparticleBankSetCamera(void* camera);
void GSparticleGeneratorSetCamera(void* camera);
f32* GSmodelGetMatrixPtr(_GSmodel* model);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* dst);
void PSVECNormalize(const GSvec* src, GSvec* dst);
f32 PSVECDotProduct(const GSvec* a, const GSvec* b);
double asin(double x);
void HSD_ArchiveParse(void* archive, u8* data, u32 size);
void GSparticleFree(GSparticleBank* bank);
void pachiruEffectCreate(void* handle, _GSmodel* model, u32 variant);
void pachiruEffectFree(void* handle);
void GSmodelEnableColorSwap(_GSmodel* model, s8* colors);
void GSmodelEnableModulation(_GSmodel* model, u8* color);
void GSmodelSetScale(_GSmodel* model, GSvec* v);
void GSmodelSetRotation(_GSmodel* model, GSvec* v);
void GSmodelSetPosition(_GSmodel* model, GSvec* v);
void GSmodelGetScale(_GSmodel* model, GSvec* v);
void GSmodelGetRotation(_GSmodel* model, GSvec* v);
void GSmodelGetPosition(_GSmodel* model, GSvec* v);
}

extern GSvec zeroVector;
extern GSvec unitScaleVector;
u32 wazaSequenceSysGetModelShadowLight(void);
u32 wazaSequenceSysGetModelShadowCount(void);
s32 wazaSequenceSysGetModelShadowList(void);
class ModelSequence;
void wazaSequenceSysFreeSequenceResource(ModelSequence* seq);
f32 _getHeadRotationCallback(GSpart* part, GSpartMixType type, void* user, GSvec* out);
extern PkxEntry pokemon_pkx_data[];
extern PkxEntry unknown_pokemon_pkx_data[];
extern PkxEntry deoxys_pokemon_pkx_data[];
extern PkxEntry rare_deoxys_pokemon_pkx_data[];
extern PkxEntry trainer_pkx_data[];
extern RareEntry rare_pokemon_pkx_data[];
extern u32 pokemon_pkx_data_number;
extern u32 unknown_pokemon_pkx_data_number;
extern u32 deoxys_pokemon_pkx_data_number;
extern u32 rare_deoxys_pokemon_pkx_data_number;
extern u32 rare_pokemon_pkx_data_number;
extern u32 trainer_pkx_data_number;

void* operator new(unsigned long size);
void operator delete(void* p);
u8* wazaSequenceSysLoadResource(u32 a, u32 b);
void _sequenceModelAnimEndedCallback(_GSmodel* model, _GSmodelAnimCBData* data);
void _mouthAnimEnded(_GSmodel* model, _GSmodelAnimCBData* data);
void _eyeAnimEnded(_GSmodel* model, _GSmodelAnimCBData* data);

GSparticleBank* wazaSequenceSysGetIceParticle(void);
GSparticleBank* wazaSequenceSysGetSleepParticle(void);
void wazaSequenceSysPartAnimationStart(_GSmodel* model, PartAnimData* data);
void sequenceAnimEndCallback(_GSmodel* model, _GSmodelAnimCBData* data);

class NullSequence {
public:
    NullSequence();
    virtual ~NullSequence();
    virtual void Update(f32 dt);
    virtual void GetPosition(GSvec* pos);
    virtual void GetRotation(GSvec* rot);
    virtual void GetScale(GSvec* scale);
    virtual void SetPosition(GSvec* pos);
    virtual void SetRotation(GSvec* rot);
    virtual void SetScale(GSvec* scale);
    virtual void SetVisibility(bool visible);

    void FreeAllWaza();
    WazaSequence* GetWaza(unsigned short wazaID, unsigned short kind) const;
    bool IsActive() const;

    u16 m_unk4;
    bool m_visible;
    u8 m_unk7;
    s32 m_kind;
    GSvec m_position;
    GSvec m_rotation;
    GSvec m_scale;
    WazaSequence* m_list;
    void* m_camera;
    NullSequence* m_next;
};

extern NullSequence* g_Sequences;

class WazaSequence {
public:
    ~WazaSequence();
    bool IsImpactPoint(u8 flag);
    void ApplyStop();
    bool IsStopped() const {
        return m_active && m_finished;
    }
    static int GetNumVariations(u16 wazaID, u16 kind);

    bool IsActive() const {
        return m_active && !m_finished;
    }

    u8 unk0[4];
    f32 m_duration;
    u8 unk8[8];
    u16 m_resID;
    u8 unk12;
    u8 m_section;
    u8 m_active;
    u8 unk15[2];
    u8 m_finished;
    u8 unk18[0xC];
    NullSequence* m_owner;
    WazaSequence* m_next;
    WazaSequence* m_prev;
};

class ModelSequence : public NullSequence {
public:
    ModelSequence(u16 id, u32 variant, bool rare);
    ModelSequence(u16 trainerID);
    virtual ~ModelSequence();
    virtual void Update(f32 dt);
    virtual void GetPosition(GSvec* pos);
    virtual void GetRotation(GSvec* rot);
    virtual void GetScale(GSvec* scale);
    virtual void SetPosition(GSvec* pos);
    virtual void SetRotation(GSvec* rot);
    virtual void SetScale(GSvec* scale);
    virtual void SetVisibility(bool visible);

    f32 GetModelScale(bool raw) const;
    bool ModelMotionStart();
    GSpart* GetPart(enumNullJointName joint);
    void LinkWithWazaSequence(WazaSequence* seq);
    void CopyState(ModelSequence* src);
    void Land();
    void Fly(bool);
    void UnFreeze();
    void Freeze();
    void WakeUp();
    void Sleep();
    void DoDefaultAnimation(GSmodelAnimType type, bool restart);
    void DoAnimation(int index, enumSectionMotionType type, bool restart);
    void Talk();
    void UpdateLookAt();
    void SetFlags(u8 flags);
    void SetDefaultFlags();
    void SetInitFlags();
    void DoModelAnimation(int);
    void ResetStatus(u8 flags);
    void SetStatus(u8 flags);
    void UpdateVisibility(bool);
    void DestroyParticles(bool, bool);
    void FreeData();
    u8 LoadData(u8* data);
    void ResetScale();
    void ResetRotation();
    void ResetPosition();
    static void Unload(u8* data);
    static int Load(u8* data, u32 id, u32 variant);

    static int FirstMotion(const MotionSection* s) {
        const MotionEntry* m = s->motions;
        for (int i = s->count; i > 0; i--, m++) {
            if (m->type != 0) {
                return m->index;
            }
        }
        return 0;
    }

    int IdleMotion() const {
        const MotionSection* s = m_sections;
        if ((m_flags & 1) && m_modelID > 0x10) {
            s = &m_sections[16];
            if (s->motions[0].type == 0) {
                s = m_sections;
            }
        }
        return FirstMotion(s);
    }

    u32 m_unk3C;
    u32 m_seed;
    u16 m_resID;
    u16 m_unk46;
    u16 m_timer;
    u16 m_unk4A;
    u16 m_distortionID;
    u8 m_mouthState;
    u8 m_distortionParam;
    s8 m_modelSize;
    u8 m_modelID;
    u8 m_section;
    u8 m_step;
    u8 m_flags;
    u8 m_unk55;
    u8 m_hasParent;
    u8 m_rare;
    u8 m_unk58;
    u8 unk59[3];
    u8 m_unk5C;
    u8 m_stepRestart;
    u8 m_colorSwap;
    u8 m_modulation;
    u8 m_unk60;
    u8 m_unk61;
    u16 m_unk62;
    _GSmodel* m_unk64;
    f32 m_unk68;
    GSvec m_look;
    ModelSequence* m_unk78;
    ModelSequence* m_parent;
    ColorInfo* m_colors;
    PartAnimData* m_sleepAnim;
    PartAnimData* m_wakeAnim;
    PartAnimData* m_unk8C;
    PartAnimData* m_talkAnim;
    _GSmodel* m_model;
    GSparticleBank* m_unk98;
    MotionSection* m_sections;
    u32 m_pachiruA;
    u32 m_pachiruB;
    void* m_unkA8;
    void* m_unkAC;
    void* m_unkB0;
    GSparticleGen* m_iceGen;
    GSparticleGen* m_sleepGen;
};

struct PokemonWazaWzxEntry {
    u8 variation;
    u8 pad1;
    u16 modelID;
    u16 wazaID;
    u16 resID;
};

struct WazaExtWzxEntry {
    u8 variation;
    u8 pad1;
    u16 wazaID;
    u16 res[3];
};

struct WazaWzxEntry {
    u16 res[3];
};

struct SectionTimes {
    s32 count;
    f32 time[1];
};

extern PokemonWazaWzxEntry pokemon_waza_wzx_data[];
extern WazaWzxEntry waza_wzx_data[];
extern WazaExtWzxEntry waza_ext_wzx_data[];
extern u16 waza_generic_wzx_data[];
extern u32 waza_wzx_data_number;
extern u32 waza_ext_wzx_data_number;
extern u32 waza_generic_wzx_data_number;
extern "C" {
void GSmodelSetPartAnimIndex(_GSmodel* model, s32 partIndex, u32 a, u32 b, f32 c);
void GSmodelSetPartTexAnimIndex(_GSmodel* model, s32 partIndex, u32 a, u32 b, u32 c, f32 d);
}

NullSequence* g_Sequences;
WazaSequence* g_LastStartedWaza;
static GSparticleBank* g_IceParticle;
static GSparticleBank* g_SleepParticle;
static u32 _resource_id_count;
static u32 _modelShadowCount;
static u32 _modelShadowLight;
static void* g_SoundListener;
_GSmodel* gCameraShakeModel;
u8 g_EnableModelLayerChange;

_GSmodel* gCameraShakeModels[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
static u32 _modelShadowList[16];

struct FloorData;
extern "C" {
u8 GSmodelCanAnimate(_GSmodel* model);
u8 GSmodelCanTexAnimate(_GSmodel* model);
_GSmodel* GSmodelLoad(void* set, void* header);
void GSlogWrite(const char* fmt, ...);
u8 GSgfxVideoGetVsyncRate(void);
f32 GSgfxVideoGetLastRenderTime(void);
void GScameraLoadActiveCameraMatrix(s32 id);
void GScameraGetPosition(void* camera, GSvec* position);
void GScameraGetLookAt(void* camera, GSvec* up, GSvec* interest);
void* GSsndCreateListenerParam(GSvec* pos, GSvec* dir, GSvec* heading, GSvec* up, u8 vol, f32 frontSur, f32 backSur, f32 soundSpeed);
u8 GSsndUpdateListenerParam(void* listener, GSvec* pos, GSvec* heading, GSvec* up);
s32 GSfsysGetStatus(u32 id);
s32 GSfsysReadWait(u32 id);
void GSthreadSwitch(void);
FloorData* floorDataBiosGetCurrentPtr(void);
u32 floorDataBiosGetGroupID(FloorData* floor);
u32 floorDataBiosGetFloorKind(FloorData* floor);
s32 floorDataBiosGetShadowReciveNum(FloorData* floor);
u32 floorDataBiosGetShadowReciveID(FloorData* floor, u32 idx);
u32 floorDataBiosGetShadowLightID(FloorData* floor);
}

static inline u8* loadResource(u32 group, u32 id) {
    u8* res = (u8*)GSresGetResource(group, id);
    if (res != 0) {
        return res;
    }
    GSfsysReadWait(group);
    return (u8*)GSresGetResource(group, id);
}

static inline _GSmodel* _wazaSequenceSysLoadModel(void* res) {
    _GSmodel* model;
    if (res == 0) {
        return 0;
    }
    model = GSmodelLoad(res, 0);
    if (model == 0) {
        GSlogWrite("%s: couldn't load model", __FUNCTION__);
        return model;
    }
    GSmodelSetVisibility(model, 1);
    if (GSmodelCanAnimate(model)) {
        GSmodelSetAnimIndex(model, 0);
        GSmodelSetAnimRate(model, 0.5f);
        GSmodelStartAnimation(model);
    }
    if (GSmodelCanTexAnimate(model)) {
        GSmodelSetTexAnimIndex(model, 0);
        GSmodelSetTexAnimRate(model, 0.5f);
        GSmodelStartTexAnimation(model);
    }
    return model;
}

static inline bool isValidSequence(NullSequence* seq) {
    NullSequence* p = g_Sequences;
    if (seq == 0) {
        return false;
    }
    for (; p != 0; p = p->m_next) {
        if (p == seq) {
            return true;
        }
    }
    return false;
}

static inline ModelSequence* asModelSequence(NullSequence* seq) {
    return seq->m_kind == 1 ? (ModelSequence*)seq : 0;
}

extern "C" {

void Sequence_SetCamera(NullSequence* seq, void* camera) {
    if (seq == 0) {
        return;
    }
    if (isValidSequence(seq)) {
        seq->m_camera = camera;
    }
}

void Sequence_SetLookTarget(ModelSequence* seq, ModelSequence* target) {
    if (seq == 0) {
        return;
    }
    if (!isValidSequence(seq)) {
        return;
    }
    seq = asModelSequence(seq);
    if (seq == 0 || seq->m_hasParent != 0) {
        return;
    }
    if (isValidSequence(target) && target != 0) {
        target = asModelSequence(target);
    } else {
        target = 0;
    }
    if (target != 0 && target->m_hasParent == 0) {
        target = 0;
    }
    if (seq->m_unk61 != 0) {
        seq->m_unk78 = target;
    }
}

void Sequence_GetScale(NullSequence* seq, GSvec* out) {
    if (seq == 0) {
        return;
    }
    if (!isValidSequence(seq)) {
        out->z = 1.0f;
        out->y = 1.0f;
        out->x = 1.0f;
    } else {
        seq->GetScale(out);
    }
}

void Sequence_GetRotation(NullSequence* seq, GSvec* out) {
    if (seq == 0) {
        return;
    }
    if (!isValidSequence(seq)) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
    } else {
        seq->GetRotation(out);
    }
}

void Sequence_GetPosition(NullSequence* seq, GSvec* out) {
    if (seq == 0) {
        return;
    }
    if (!isValidSequence(seq)) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
    } else {
        seq->GetPosition(out);
    }
}

void Sequence_SetScale(NullSequence* seq, GSvec* v) {
    if (seq != 0 && isValidSequence(seq)) {
        seq->SetScale(v);
    }
}

void Sequence_SetRotation(NullSequence* seq, GSvec* v) {
    if (seq != 0 && isValidSequence(seq)) {
        seq->SetRotation(v);
    }
}

void Sequence_SetPosition(NullSequence* seq, GSvec* v) {
    if (seq != 0 && isValidSequence(seq)) {
        seq->SetPosition(v);
    }
}

u32 Sequence_GetPokemonRndVal(ModelSequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!isValidSequence(seq)) {
        return 0;
    }
    seq = asModelSequence(seq);
    if (seq == 0) {
        return 0;
    }
    return seq->m_seed;
}

}
ModelSequence* New_ModelSequence(u16 id);
ModelSequence* New_ModelSequence(u16 id, u32 variant, bool rare);
NullSequence* New_NullSequence();

extern "C" {

u8 Sequence_IsFlipped(ModelSequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!isValidSequence(seq)) {
        return 0;
    }
    seq = asModelSequence(seq);
    if (seq == 0) {
        return 0;
    }
    return seq->m_unk55;
}

void Sequence_SetFlipped(ModelSequence* seq, u8 flipped) {
    if (seq == 0) {
        return;
    }
    if (!isValidSequence(seq)) {
        return;
    }
    seq = asModelSequence(seq);
    if (seq == 0) {
        return;
    }
    seq->m_unk55 = flipped;
}

u8 Sequence_IsRare(ModelSequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!isValidSequence(seq)) {
        return 0;
    }
    seq = asModelSequence(seq);
    if (seq == 0) {
        return 0;
    }
    return seq->m_rare;
}

u8 Sequence_GetFlags(ModelSequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!isValidSequence(seq)) {
        return 0;
    }
    seq = asModelSequence(seq);
    if (seq == 0) {
        return 0;
    }
    return seq->m_flags;
}

u16 Sequence_GetID(NullSequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (isValidSequence(seq)) {
        return seq->m_unk4;
    }
    return 0;
}

_GSmodel* Sequence_GetGSmodel(ModelSequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!isValidSequence(seq)) {
        return 0;
    }
    seq = asModelSequence(seq);
    if (seq == 0) {
        return 0;
    }
    return seq->m_model;
}

int Sequence_GetModelSize(ModelSequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!isValidSequence(seq)) {
        return 0;
    }
    seq = asModelSequence(seq);
    if (seq == 0) {
        return 0;
    }
    return seq->m_modelSize;
}

void Sequence_SetDownFlag(ModelSequence* seq, u8 down) {
    if (seq == 0) {
        return;
    }
    if (!isValidSequence(seq)) {
        return;
    }
    seq = asModelSequence(seq);
    if (seq == 0) {
        return;
    }
    seq->m_flags &= ~8;
    if (down) {
        seq->m_flags |= 0x10;
    } else {
        seq->m_flags &= 0x10;
    }
}

WazaSequence* Sequence_GetWaza(NullSequence* seq, u16 wazaID, u16 kind) {
    if (seq == 0) {
        return 0;
    }
    if (isValidSequence(seq)) {
        return seq->GetWaza(wazaID, kind);
    }
    return 0;
}

void Sequence_FreeAllWaza(NullSequence* seq) {
    if (seq != 0 && isValidSequence(seq)) {
        seq->FreeAllWaza();
    }
}

void Sequence_Free(NullSequence* seq) {
    if (seq != 0 && isValidSequence(seq)) {
        delete seq;
    }
}

void Sequence_DoAnimation(ModelSequence* seq, int index) {
    if (seq != 0 && isValidSequence(seq)) {
        seq = asModelSequence(seq);
        if (seq != 0) {
            seq->DoModelAnimation(index);
        }
    }
}

void Sequence_Talk(ModelSequence* seq) {
    if (seq != 0 && isValidSequence(seq)) {
        seq = asModelSequence(seq);
        if (seq != 0) {
            seq->Talk();
        }
    }
}

void Sequence_CopyState(ModelSequence* seq, ModelSequence* src) {
    if (seq != 0 && isValidSequence(seq)) {
        seq = asModelSequence(seq);
        if (seq != 0) {
            if (!isValidSequence(src)) {
                src = 0;
            } else {
                src = asModelSequence(src);
            }
            seq->CopyState(src);
        }
    }
}

void Sequence_SetFlags(ModelSequence* seq, u8 flags) {
    if (seq != 0 && isValidSequence(seq)) {
        seq = asModelSequence(seq);
        if (seq != 0) {
            seq->SetFlags(flags);
        }
    }
}

void Sequence_SetDefaultFlags(ModelSequence* seq) {
    if (seq != 0 && isValidSequence(seq)) {
        seq = asModelSequence(seq);
        if (seq != 0) {
            seq->SetDefaultFlags();
        }
    }
}

void Sequence_ResetStatus(ModelSequence* seq, u8 flags) {
    if (seq != 0 && isValidSequence(seq)) {
        seq = asModelSequence(seq);
        if (seq != 0) {
            seq->ResetStatus(flags);
        }
    }
}

void Sequence_SetStatus(ModelSequence* seq, u8 flags) {
    if (seq != 0 && isValidSequence(seq)) {
        seq = asModelSequence(seq);
        if (seq != 0) {
            seq->SetStatus(flags);
        }
    }
}

void Sequence_SetVisibility(NullSequence* seq, bool visible) {
    if (seq != 0 && isValidSequence(seq)) {
        seq->SetVisibility(visible);
    }
}

ModelSequence* Sequence_LoadPokemon(u16 id, u32 variant, bool rare) {
    return New_ModelSequence(id, variant, rare);
}

ModelSequence* Sequence_LoadTrainer(u16 id) {
    return New_ModelSequence(id);
}

NullSequence* Sequence_CreateNull() {
    return New_NullSequence();
}

}

struct WazaResourceEntry {
    u32 groupID;
    u32 unk4;
};
extern WazaResourceEntry waza_resource_data[];

extern "C" {
void GSresFreeGroup(u32 group);
void GSfsysFree(u32 id);
void GSmodelFree(_GSmodel* model);
void* memset(void* dst, int val, u32 n);
void GSsndFreeListener(void* listener);
}

u16 wazaSequenceSysGetResourceID(ModelSequence* seq, u16 wazaID, u16 kind, u8 variation);

extern "C" {
u32 wazaSequenceSysGetWazaGroupID(u16 wazaID, u16 kind) {
    u16 id = wazaSequenceSysGetResourceID(0, wazaID, kind, 0);
    if (id != 0) {
        return waza_resource_data[id].groupID;
    }
    return 0;
}
}

u16 wazaSequenceSysGetResourceID(ModelSequence* seq, u16 wazaID, u16 kind, u8 variation) {
    u16 start;
    int modelID;
    u16 i;
    PokemonWazaWzxEntry* e;
    u16 end;
    if (kind == 0 || kind > 4) {
        return 0;
    }
    if (seq != 0 && seq->m_hasParent != 0) {
        modelID = seq->m_unk4;
        if (variation != 0 && variation < WazaSequence::GetNumVariations(wazaID, kind)) {
            switch (kind) {
            case 1:
                start = 0x33c;
                end = 0x359;
                break;
            case 2:
                start = 0x35b;
                end = 0x35b;
                break;
            case 3:
                start = 0x35d;
                end = 0x361;
                break;
            case 4:
                start = 0x33a;
                end = 0x33a;
                variation = 0;
                break;
            }
        } else {
            switch (kind) {
            case 1:
                start = 1;
                end = 0x236;
                break;
            case 2:
                start = 0x238;
                end = 0x2ab;
                break;
            case 3:
                start = 0x2ad;
                end = 0x338;
                break;
            case 4:
                start = 0x33a;
                end = 0x33a;
                break;
            }
        }
        e = &pokemon_waza_wzx_data[start];
        for (i = start; i < end; i++, e++) {
            if (e->modelID == modelID && e->wazaID == wazaID && e->variation == variation) {
                return e->resID;
            }
        }
    }
    if (kind == 4) {
        if (wazaID == 0 || wazaID >= waza_generic_wzx_data_number) {
            return 0;
        }
        return waza_generic_wzx_data[wazaID];
    } else {
        u16 idx = kind - 1;
        u16 result;
        if (wazaID == 0 || wazaID >= waza_wzx_data_number) {
            return 0;
        }
        result = waza_wzx_data[wazaID].res[idx];
        if (variation != 0) {
            WazaExtWzxEntry* x = waza_ext_wzx_data;
            for (i = 0; i < waza_ext_wzx_data_number; i++, x++) {
                if (x->wazaID == wazaID && x->variation == variation) {
                    if (x->res[idx] != 0) {
                        result = x->res[idx];
                    }
                    break;
                }
            }
        }
        return result;
    }
}

f32 wazaSequenceSysNullGetWazaTime(WazaSequence* waza, u8 mode) {
    u16 n;
    f32 t;
    switch (waza->m_section) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 12:
    case 13:
    case 14:
    case 15:
        n = 4;
        break;
    case 8:
    case 10:
        n = 3;
        break;
    case 9:
        n = 5;
        break;
    case 0:
    case 11:
    case 16:
    default:
        n = 2;
        break;
    }
    t = waza->m_duration;
    if (mode == -1) {
        return 0.0f;
    }
    if (mode == 0) {
        return t;
    }
    if (mode == 3 || mode == 4) {
        u16 a = n - 1;
        return t + __OSu16tof32(&a);
    }
    if (mode == 1) {
        return 1.0f + t;
    }
    if (mode == 2) {
        if (n > 2) {
            u16 b = n - 2;
            return t + __OSu16tof32(&b);
        } else {
            u16 c = n - 1;
            return t + __OSu16tof32(&c);
        }
    }
    return 0.0f;
}

f32 wazaSequenceSysGetWazaTime(ModelSequence* seq, WazaSequence* waza, u8 mode) {
    SectionTimes* sec = (SectionTimes*)((u8*)seq->m_sections + waza->m_section * 0xD0);
    f32 t = waza->m_duration;
    if (mode == -1) {
        return 0.0f;
    }
    if (mode == 0) {
        return t;
    }
    if (mode == 3 || mode == 4) {
        return t + sec->time[sec->count + 1];
    }
    if (mode == 1) {
        return t + sec->time[3];
    }
    if (mode == 2) {
        if (sec->count > 2) {
            return t + sec->time[sec->count];
        } else {
            return t + sec->time[sec->count + 1];
        }
    }
    return 0.0f;
}

void wazaSequenceSysPartAnimationStart(_GSmodel* model, PartAnimData* data) {
    switch (data->enabled) {
    case 1:
        GSmodelLinkTexAnimToAnim(model, 0);
        GSmodelSetTexAnimIndex(model, data->id);
        GSmodelSetTexAnimRate(model, 0.5f);
        GSmodelSetTexAnimType(model, 0);
        GSmodelSetTexAnimFrame(model, 0.0f);
        GSmodelStartTexAnimation(model);
        break;
    case 2: {
        u8 i;
        u8 count = data->count;
        u8* part = data->parts;
        u8* tex = data->tex;
        for (i = 0; i < count; i++, part++, tex++) {
            if (*part != 0xFF) {
                if (*tex == 0xFF) {
                    GSmodelSetPartAnimIndex(model, *part, data->id, 0, 0.0f);
                } else {
                    GSmodelSetPartTexAnimIndex(model, *part, *tex, data->id, 0, 0.0f);
                }
            }
        }
        break;
    }
    }
}

GSparticleBank* wazaSequenceSysGetSleepParticle() {
    return g_SleepParticle;
}

GSparticleBank* wazaSequenceSysGetIceParticle() {
    return g_IceParticle;
}

extern "C" {

void wazaSequenceSysSetVisibilityAll(bool visible) {
    NullSequence* seq;
    for (seq = g_Sequences; seq != 0; seq = seq->m_next) {
        seq->SetVisibility(visible);
    }
}

u16 wazaSequenceSysGetActiveWazaNum() {
    u16 count = 0;
    NullSequence* seq;
    for (seq = g_Sequences; seq != 0; seq = seq->m_next) {
        WazaSequence* waza;
        for (waza = seq->m_list; waza != 0; waza = waza->m_next) {
            if (waza->IsActive()) {
                count++;
            }
        }
    }
    return count;
}

bool wazaSequenceSysLastWazaIsImpactPoint(u8 flag) {
    if (g_LastStartedWaza != 0) {
        return g_LastStartedWaza->IsImpactPoint(flag);
    }
    return true;
}

void wazaSequenceSysFreeAllWazaExcept(NullSequence* seq, WazaSequence* except) {
    if (isValidSequence(seq)) {
        WazaSequence* waza = seq->m_list;
        while (waza != 0) {
            WazaSequence* next = waza->m_next;
            if (waza != except) {
                delete waza;
            }
            waza = next;
        }
    }
}

void wazaSequenceSysFreeAllWaza() {
    NullSequence* seq;
    for (seq = g_Sequences; seq != 0; seq = seq->m_next) {
        seq->FreeAllWaza();
    }
}

}

static inline void _wazaSequenceSysReleaseAll() {
    NullSequence* seq = g_Sequences;
    while (seq != 0) {
        NullSequence* next = seq->m_next;
        delete seq;
        seq = next;
    }
    g_Sequences = 0;
    if (g_IceParticle != 0 || g_SleepParticle != 0) {
        GSresFreeGroup(0x6F7);
        GSfsysFree(0x6F7);
        g_IceParticle = 0;
        g_SleepParticle = 0;
    }
    {
        _GSmodel** p = gCameraShakeModels;
        int i;
        for (i = 0; i < 9; i++, p++) {
            if (*p != 0) {
                GSmodelFree(*p);
                *p = 0;
            }
        }
    }
    gCameraShakeModel = 0;
    GSresFreeGroup(0x634);
    GSfsysFree(0x634);
    _modelShadowCount = 0;
    _modelShadowLight = 0;
    memset(_modelShadowList, 0, _modelShadowCount * 4);
    if (g_SoundListener != 0) {
        GSsndFreeListener(g_SoundListener);
        g_SoundListener = 0;
    }
}

extern "C" {

void wazaSequenceSysRelease() {
    _wazaSequenceSysReleaseAll();
}

}
extern "C" {

bool wazaSequenceSysIsValidSequence(NullSequence* seq) {
    return isValidSequence(seq);
}

bool wazaSequenceSysIsValidWaza(WazaSequence* waza) {
    NullSequence* seq = g_Sequences;
    if (waza == 0) {
        return false;
    }
    for (; seq != 0; seq = seq->m_next) {
        WazaSequence* w;
        for (w = seq->m_list; w != 0; w = w->m_next) {
            if (w == waza) {
                return true;
            }
        }
    }
    return false;
}

void wazaSequenceSysEnableLayerChange() {
    g_EnableModelLayerChange = 1;
}

void wazaSequenceSysInit() {
    void* camera = GScameraGetActiveCamera();
    _wazaSequenceSysReleaseAll();
    if (camera != 0) {
        GSvec pos;
        GSvec dir;
        GSvec up;
        GScameraGetPosition(camera, &pos);
        GScameraGetLookAt(camera, &up, &dir);
        PSVECSubtract(&dir, &pos, &dir);
        PSVECNormalize(&dir, &dir);
        g_SoundListener = GSsndCreateListenerParam(&pos, &zeroVector, &dir, &up, 0x7F, 250.0f, 250.0f, 360.0f);
    }
    {
        u32 group;
        FloorData* floor;
        u32 i;
        u32 n;
        floor = floorDataBiosGetCurrentPtr();
        group = floorDataBiosGetGroupID(floor);
        switch ((u8)floorDataBiosGetFloorKind(floor)) {
        case 2:
        case 4:
            g_EnableModelLayerChange = 1;
            break;
        case 3:
        default:
            g_EnableModelLayerChange = 0;
            break;
        }
        n = floorDataBiosGetShadowReciveNum(floor);
        if (n > 16) {
            n = 16;
        }
        _modelShadowCount = 0;
        for (i = 0; i < n; i++) {
            void* res = GSresGetResource(group, floorDataBiosGetShadowReciveID(floor, i));
            if (res != 0) {
                _modelShadowList[_modelShadowCount++] = (u32)res;
            }
        }
        {
            u32 light = floorDataBiosGetShadowLightID(floor);
            if (light != 0) {
                _modelShadowLight = (u32)GSresGetResource(group, light);
            }
        }
    }
}

}

static void _wazaSequenceSysCameraShakeInit();

extern "C" {

void wazaSequenceSysInitExtras() {
    g_IceParticle = (GSparticleBank*)loadResource(0x6F7, 0x205D2400);
    g_SleepParticle = (GSparticleBank*)loadResource(0x6F7, 0x11052400);
    _wazaSequenceSysCameraShakeInit();
}

}

#define SHAKE_LOAD(id)                                                \
    {                                                                 \
        u8* res = loadResource(0x634, id);                            \
        if (res != 0) {                                               \
            *p = _wazaSequenceSysLoadModel(res);                      \
            if (*p != 0) {                                            \
                GSmodelSetVisibility(*p, 0);                          \
            }                                                         \
            p++;                                                      \
        }                                                             \
    }

static void _wazaSequenceSysCameraShakeInit() {
    _GSmodel** p = gCameraShakeModels;
    SHAKE_LOAD(0x102E1000)
    SHAKE_LOAD(0x102B1000)
    SHAKE_LOAD(0x10271000)
    SHAKE_LOAD(0x102C1000)
    SHAKE_LOAD(0x10281000)
    SHAKE_LOAD(0x10251000)
    SHAKE_LOAD(0x102D1000)
    SHAKE_LOAD(0x10291000)
    SHAKE_LOAD(0x10261000)
}

extern "C" {

static inline void applyStopAll() {
    NullSequence* seq;
    for (seq = g_Sequences; seq != 0; seq = seq->m_next) {
        WazaSequence* waza;
        for (waza = seq->m_list; waza != 0; waza = waza->m_next) {
            if (waza->IsStopped()) {
                waza->ApplyStop();
            }
        }
    }
}

s32 wazaSequenceSysGetResID() {
    if (_resource_id_count == 0xFFFFFFFF) {
        _resource_id_count = 0;
    }
    return ++_resource_id_count;
}

void wazaSequenceSysUpdate() {
    f32 dt = GSgfxVideoGetLastRenderTime() / (f32)GSgfxVideoGetVsyncRate();
    NullSequence* seq;
    void* camera;
    applyStopAll();
    for (seq = g_Sequences; seq != 0; seq = seq->m_next) {
        seq->Update(dt);
    }
    camera = GScameraGetActiveCamera();
    if (camera != 0) {
        GSvec pos;
        GSvec dir;
        GSvec up;
        GScameraLoadActiveCameraMatrix(-1);
        GScameraGetPosition(camera, &pos);
        GScameraGetLookAt(camera, &up, &dir);
        PSVECSubtract(&dir, &pos, &dir);
        PSVECNormalize(&dir, &dir);
        if (g_SoundListener != 0) {
            GSsndUpdateListenerParam(g_SoundListener, &pos, &dir, &up);
        } else {
            g_SoundListener = GSsndCreateListenerParam(&pos, &zeroVector, &dir, &up, 0x7F, 250.0f, 250.0f, 360.0f);
        }
    }
}

}

static inline void waitResourceLoad(u32 group) {
    while (GSfsysGetStatus(group) == 1) {
        GSthreadSwitch();
    }
}

void wazaSequenceSysApplyStop() {
    NullSequence* seq;
    for (seq = g_Sequences; seq != 0; seq = seq->m_next) {
        WazaSequence* waza;
        for (waza = seq->m_list; waza != 0; waza = waza->m_next) {
            if (waza->IsStopped()) {
                waza->ApplyStop();
            }
        }
    }
}

static inline void freeSequenceRes(u16 id) {
    if (id != 0) {
        NullSequence* s;
        int count;
        ModelSequence* m;
        count = 0;
        for (s = g_Sequences; s != 0; s = s->m_next) {
            m = asModelSequence(s);
            if (m != 0 && id == m->m_resID) {
                count++;
            }
        }
        if (count == 1) {
            waitResourceLoad(id);
            GSresFreeGroup(id);
            GSfsysFree(id);
        }
    }
}

void wazaSequenceSysFreeSequenceResource(ModelSequence* seq) {
    freeSequenceRes(seq->m_resID);
}

static inline void freeWazaRes(u16 id) {
    if (id != 0) {
        int count;
        WazaSequence* w;
        NullSequence* s;
        count = 0;
        for (s = g_Sequences; s != 0; s = s->m_next) {
            for (w = s->m_list; w != 0; w = w->m_next) {
                if (id == w->m_resID) {
                    count++;
                }
            }
        }
        if (count == 1) {
            waitResourceLoad(id);
            GSresFreeGroup(id);
            GSfsysFree(id);
        }
    }
}

void wazaSequenceSysFreeWazaResource(WazaSequence* waza) {
    freeWazaRes(waza->m_resID);
}

u32 wazaSequenceSysGetModelShadowLight() {
    return _modelShadowLight;
}

u32 wazaSequenceSysGetModelShadowCount() {
    return _modelShadowCount;
}

s32 wazaSequenceSysGetModelShadowList() {
    return (s32)_modelShadowList;
}

void wazaSequenceSysResetAnimationExcept(ModelSequence* except) {
    NullSequence* s = g_Sequences;
    if (except == 0) {
        return;
    }
    for (; s != 0; s = s->m_next) {
        ModelSequence* m = asModelSequence(s);
        if (except != m && m->m_hasParent != 0) {
            m->DoDefaultAnimation(GS_ANIM_TYPE_1, false);
        }
    }
}

u8* wazaSequenceSysLoadResource(u32 group, u32 id) {
    return loadResource(group, id);
}
