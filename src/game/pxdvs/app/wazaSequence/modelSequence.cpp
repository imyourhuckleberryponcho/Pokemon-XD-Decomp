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

// From the Dolphin SDK's OSFastCast.h (GQR3 is set up for u16 conversion).
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

// One animation section (0xD0 bytes). Section 16 holds the alternate (flying) motion set.
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
    u8 pad1[0x11];
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
void GSmodelSetRenderCamera(_GSmodel* model, void* camera);
void GSparticleBankSetCamera(GSparticleBank* bank, void* camera);
void GSparticleGeneratorSetCamera(GSparticleGen* gen, void* camera);
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
    u8 unk0[4];
    f32 m_duration;
    u8 unk8[0xB];
    u8 m_section;
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

 // First motion entry of a section that has a non-zero type.
    static int FirstMotion(const MotionSection* s) {
        const MotionEntry* m = s->motions;
        for (int i = s->count; i > 0; i--, m++) {
            if (m->type != 0) {
                return m->index;
            }
        }
        return 0;
    }

 // Idle motion of the current state (flying uses the alternate set when present).
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
    s16 m_resID;
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

// ---
void _eyeAnimEnded(_GSmodel* model, _GSmodelAnimCBData* data) {
    u8 matched = 0;
    s32 flags = data->flags;
    if (((flags & 8) || (flags & 2)) && !(flags & 4)) {
        ModelSequence* seq = (ModelSequence*)data->owner;
        if (seq == 0 || seq->m_unk7 != 0) {
            return;
        }
        {
            {
            if ((seq->m_flags & 4) != 4 && model == seq->m_model) {
                s32 anim = data->anim;
                PartAnimData* part = seq->m_sleepAnim;
                if (part->enabled != 0 && anim == part->id) {
                    matched = 1;
                } else {
                    part = seq->m_wakeAnim;
                    if (part->enabled != 0 && anim == part->id) {
                        matched = 1;
                    } else {
                        part = seq->m_unk8C;
                        if (part->enabled != 0 && anim == part->id) {
                            matched = 1;
                        }
                    }
                }
                if (matched) {
                    switch (seq->m_mouthState) {
                    case 1:
                        break;
                    default:
                        return;
                    }
                    GSmodelLinkTexAnimToAnim(model, 1);
                    if (GSmodelIsAnimating(model)) {
                        f32 frame = GSmodelGetAnimFrame(model);
                        f32 rate = GSmodelGetAnimRate(model);
                        s32 type = GSmodelGetAnimType(model);
                        GSmodelGetAnimIndex(model, &anim, 0);
                        if (data->flags & 2) {
                            GSmodelSetTexAnimIndex(model, anim);
                            GSmodelSetTexAnimRate(model, rate);
                            GSmodelSetTexAnimFrame(model, frame);
                            GSmodelSetTexAnimType(model, type);
                            GSmodelStartTexAnimation(model);
                        } else {
                            GSmodelSetKeepPartAnimFlag(model, 0);
                            GSmodelSetAnimIndex(model, anim);
                            GSmodelSetAnimRate(model, rate);
                            GSmodelSetAnimFrame(model, frame);
                            GSmodelSetAnimType(model, type);
                            GSmodelStartAnimation(model);
                            GSmodelSetKeepPartAnimFlag(model, 1);
                        }
                    }
                    seq->m_mouthState = 0;
                }
            }
            }
        }
    }
}

// ---
void _mouthAnimEnded(_GSmodel* model, _GSmodelAnimCBData* data) {
    s32 flags = data->flags;
    if (((flags & 8) || (flags & 2)) && !(flags & 4)) {
        ModelSequence* seq = (ModelSequence*)data->owner;
        if (seq == 0 || seq->m_unk7 != 0) {
            return;
        }
        {
            if ((seq->m_flags & 4) != 4 && model == seq->m_model) {
                s32 anim = data->anim;
                PartAnimData* part = seq->m_talkAnim;
                if (part->enabled == 0 || anim != part->id) {
                    return;
                }
                {
                    seq->m_flags &= ~0x40;
                    GSmodelLinkTexAnimToAnim(model, 1);
                    if (GSmodelIsAnimating(model)) {
                        f32 frame = GSmodelGetAnimFrame(model);
                        f32 rate = GSmodelGetAnimRate(model);
                        s32 type = GSmodelGetAnimType(model);
                        GSmodelGetAnimIndex(model, &anim, 0);
                        if (data->flags & 2) {
                            GSmodelSetTexAnimIndex(model, anim);
                            GSmodelSetTexAnimRate(model, rate);
                            GSmodelSetTexAnimFrame(model, frame);
                            GSmodelSetTexAnimType(model, type);
                            GSmodelStartTexAnimation(model);
                            return;
                        }
                        GSmodelSetKeepPartAnimFlag(model, 0);
                        GSmodelSetAnimIndex(model, anim);
                        GSmodelSetAnimRate(model, rate);
                        GSmodelSetAnimFrame(model, frame);
                        GSmodelSetAnimType(model, type);
                        GSmodelStartAnimation(model);
                        GSmodelSetKeepPartAnimFlag(model, 1);
                    }
                }
            }
        }
    }
}

// ---
void _sequenceModelAnimEndedCallback(_GSmodel* model, _GSmodelAnimCBData* data) {
    s32 flags = data->flags;
    if ((flags & 1) && !(flags & 8) && !(flags & 4)) {
        ModelSequence* seq = (ModelSequence*)data->owner;
        if (seq == 0 || seq->m_unk7 != 0) {
            return;
        }
        {
            if (model == seq->m_model && (seq->m_flags & 4) != 4) {
                MotionSection* section = &seq->m_sections[seq->m_section];
                u16 timer = seq->m_timer;
                if (timer != 0) {
                    seq->m_timer = timer - 1;
                    seq->DoDefaultAnimation(GS_ANIM_TYPE_0, false);
                } else {
                    if (seq->m_stepRestart != 0) {
                        seq->m_step = 0;
                        seq->m_stepRestart = 0;
                    } else {
                        seq->m_step = seq->m_step + 1;
                    }
                    u8 step = seq->m_step;
                    if (step >= section->count) {
                        seq->DoDefaultAnimation(GS_ANIM_TYPE_1, false);
                        seq->m_section = 0;
                        seq->m_step = 0;
                        seq->m_timer = 0;
                        seq->m_stepRestart = 0;
                        ModelSequence* parent = seq->m_parent;
                        if (parent != 0 && parent->m_unk61 != 0) {
                            parent->m_unk78 = 0;
                        }
                    } else {
                        MotionEntry* motion = &section->motions[step];
                        seq->DoAnimation(motion->index, (enumSectionMotionType)motion->type, true);
                    }
                }
            }
        }
    }
}

// ---
void sequenceAnimEndCallback(_GSmodel* model, _GSmodelAnimCBData* data) {
    _sequenceModelAnimEndedCallback(model, data);
    _eyeAnimEnded(model, data);
    _mouthAnimEnded(model, data);
}

// ---
ModelSequence* New_ModelSequence(u16 id) {
    ModelSequence* seq = new ModelSequence(id);
    if (seq == 0) {
        return 0;
    }
    seq->m_next = g_Sequences;
    g_Sequences = seq;
    if (seq->m_unk7 != 0) {
        delete seq;
        return 0;
    }
    return seq;
}

// ---
ModelSequence* New_ModelSequence(u16 id, u32 variant, bool rare) {
    ModelSequence* seq = new ModelSequence(id, variant, rare);
    if (seq == 0) {
        return 0;
    }
    seq->m_next = g_Sequences;
    g_Sequences = seq;
    if (seq->m_unk7 != 0) {
        delete seq;
        return 0;
    }
    return seq;
}

// ---
extern "C" {
int ModelSequence_Load(u8* data, u32 id, u32 variant) {
    return ModelSequence::Load(data, id, variant);
}
}

// ---
#pragma dont_inline on
int ModelSequence::Load(u8* data, u32 id, u32 variant) {
    PkxHeader* hdr = (PkxHeader*)data;
    if (hdr->type == 0xC && hdr->size != 0) {
        data += 0x84;
        data += hdr->count * 0xD0;
        data = (u8*)ALIGN32(data);
        if (hdr->unk8 != 0) {
            hdr->particle = 0;
            data += ALIGN32(hdr->unk8);
        } else {
            hdr->particle = 0;
        }
        if ((id == 0xDD && variant == 0x3001E00) || (id == 0x13F && variant == 0x3641E00) || (id == 0x387 && variant == 0x6691E00)) {
            hdr->model = 0;
        } else {
            void* archive = operator new(0x44);
            if (archive != 0) {
                hdr->model = archive;
                HSD_ArchiveParse(archive, data, hdr->size);
            } else {
                hdr->model = 0;
                return 0;
            }
        }
        return 1;
    }
    hdr->model = 0;
    hdr->particle = 0;
    return 0;
}
#pragma dont_inline reset

// ---
void ModelSequence::Unload(u8* data) {
    PkxHeader* hdr = (PkxHeader*)data;
    if (hdr->model != 0) {
        operator delete(hdr->model);
        hdr->model = 0;
    }
    if (hdr->particle != 0) {
        GSparticleFree(hdr->particle);
        hdr->particle = 0;
    }
}

// ---
ModelSequence::ModelSequence(u16 id) {
    m_unk3C = 0;
    m_seed = 0;
    m_resID = 0;
    m_unk46 = 0;
    m_timer = 0;
    m_unk4A = 0;
    m_mouthState = 0;
    m_modelSize = 0;
    m_modelID = 0;
    m_section = 0;
    m_step = 0;
    m_flags = 0;
    m_unk55 = 0;
    m_hasParent = 0;
    m_rare = 0;
    m_unk58 = 0;
    m_unk5C = 0;
    m_stepRestart = 0;
    m_colorSwap = 0;
    m_modulation = 0;
    m_unk60 = 0;
    m_unk61 = 0;
    m_unk62 = 0;
    m_unk64 = 0;
    m_look.x = 0.0f;
    m_look.y = 0.0f;
    m_look.z = 0.0f;
    m_unk78 = 0;
    m_parent = 0;
    m_colors = 0;
    m_sleepAnim = 0;
    m_wakeAnim = 0;
    m_unk8C = 0;
    m_talkAnim = 0;
    m_model = 0;
    m_unk98 = 0;
    m_sections = 0;
    m_unkA8 = 0;
    m_unkAC = 0;
    m_unkB0 = 0;
    m_iceGen = 0;
    m_sleepGen = 0;
    m_kind = 1;
    m_pachiruB = 0;
    m_pachiruA = 0;
    if (id == 0 || id >= trainer_pkx_data_number) {
        m_unk7 = 1;
        return;
    }
    u32 resA = trainer_pkx_data[id].a;
    u32 resB = trainer_pkx_data[id].b;
    if (resA == 0 || resB == 0) {
        resA = trainer_pkx_data[1].a;
        resB = trainer_pkx_data[1].b;
        if (resA == 0 || resB == 0) {
            m_unk7 = 1;
            return;
        }
    }
    u8* res = wazaSequenceSysLoadResource(resA, resB);
    m_resID = resA;
    if (res == 0) {
        m_unk7 = 1;
        return;
    }
    m_unk4 = id;
    if (!LoadData(res)) {
        FreeData();
        m_unk7 = 1;
    }
}

// ---
ModelSequence::ModelSequence(u16 id, u32 variant, bool rare) {
    u32 resA;
    u32 resB;
    u8 usedRare = 0;
    m_unk3C = 0;
    m_seed = 0;
    m_resID = 0;
    m_unk46 = 0;
    m_timer = 0;
    m_unk4A = 0;
    m_mouthState = 0;
    m_modelSize = 0;
    m_modelID = 0;
    m_section = 0;
    m_step = 0;
    m_flags = 0;
    m_unk55 = 0;
    m_hasParent = 1;
    m_rare = 0;
    m_unk58 = 0;
    m_unk5C = 0;
    m_stepRestart = 0;
    m_colorSwap = 0;
    m_modulation = 0;
    m_unk60 = 0;
    m_unk61 = 0;
    m_unk62 = 0;
    m_unk64 = 0;
    m_look.x = 0.0f;
    m_look.y = 0.0f;
    m_look.z = 0.0f;
    m_unk78 = 0;
    m_parent = 0;
    m_colors = 0;
    m_sleepAnim = 0;
    m_wakeAnim = 0;
    m_unk8C = 0;
    m_talkAnim = 0;
    m_model = 0;
    m_unk98 = 0;
    m_sections = 0;
    m_unkA8 = 0;
    m_unkAC = 0;
    m_unkB0 = 0;
    m_iceGen = 0;
    m_sleepGen = 0;
    m_kind = 1;
    m_pachiruB = 0;
    m_pachiruA = 0;
    if (id == 0 || id >= pokemon_pkx_data_number) {
        m_unk7 = 1;
        return;
    }
    if (id == 0xC9) {
        variant %= unknown_pokemon_pkx_data_number;
        resA = unknown_pokemon_pkx_data[variant].a;
        resB = unknown_pokemon_pkx_data[variant].b;
    } else if (id == 0x19A) {
        variant %= deoxys_pokemon_pkx_data_number;
        resA = deoxys_pokemon_pkx_data[variant].a;
        resB = deoxys_pokemon_pkx_data[variant].b;
    } else {
        resA = pokemon_pkx_data[id].a;
        resB = pokemon_pkx_data[id].b;
    }
    if (resA == 0 || resB == 0) {
        m_unk7 = 1;
        return;
    }
    if (rare) {
        u32 rareA = 0;
        u32 rareB = 0;
        if (id == 0x19A) {
            variant %= rare_deoxys_pokemon_pkx_data_number;
            resA = rare_deoxys_pokemon_pkx_data[variant].a;
            resB = rare_deoxys_pokemon_pkx_data[variant].b;
        } else {
            for (int i = 0; i < rare_pokemon_pkx_data_number; i++) {
                if (id == rare_pokemon_pkx_data[i].id) {
                    rareA = rare_pokemon_pkx_data[i].a;
                    rareB = rare_pokemon_pkx_data[i].b;
                    break;
                }
            }
        }
        if (rareA != 0 && rareB != 0) {
            resA = rareA;
            resB = rareB;
            usedRare = 1;
        }
    }
    u8* res = wazaSequenceSysLoadResource(resA, resB);
    m_resID = resA;
    if (res == 0) {
        m_unk7 = 1;
        return;
    }
    m_unk4 = id;
    m_rare = rare;
    m_seed = variant;
    if (!LoadData(res)) {
        FreeData();
        m_unk7 = 1;
        return;
    }
    if (rare && !usedRare && m_unk60 == 0) {
        ColorInfo* colors = m_colors;
        _GSmodel* model = m_model;
        s8 swap[4];
        swap[0] = colors->swap[0];
        swap[1] = colors->swap[1];
        swap[2] = colors->swap[2];
        swap[3] = colors->swap[3];
        if (m_colorSwap != 0) {
            GSmodelEnableColorSwap(model, swap);
        }
        if (m_modulation != 0) {
            colors->mod[3] = 0xFF;
            GSmodelEnableModulation(model, colors->mod);
        }
        m_unk60 = 1;
    }
    if (id == 0x134) {
        pachiruEffectCreate(&m_pachiruA, m_model, variant);
    }
}

// ---
ModelSequence::~ModelSequence() {
    FreeAllWaza();
    FreeData();
}

// ---
void ModelSequence::GetPosition(GSvec* pos) {
    if (m_model != 0) {
        GSmodelGetPosition(m_model, pos);
        return;
    }
    pos->x = m_position.x;
    pos->y = m_position.y;
    pos->z = m_position.z;
}

// ---
void ModelSequence::GetRotation(GSvec* rot) {
    if (m_model != 0) {
        GSmodelGetRotation(m_model, rot);
        return;
    }
    rot->x = m_rotation.x;
    rot->y = m_rotation.y;
    rot->z = m_rotation.z;
}

// ---
void ModelSequence::GetScale(GSvec* scale) {
    if (m_model != 0) {
        GSmodelGetScale(m_model, scale);
        return;
    }
    scale->x = m_scale.x;
    scale->y = m_scale.y;
    scale->z = m_scale.z;
}

// ---
void ModelSequence::ResetPosition() {
    if (m_model != 0) {
        GSmodelSetPosition(m_model, &m_position);
    }
}

// ---
void ModelSequence::SetPosition(GSvec* pos) {
    m_position.x = pos->x;
    m_position.y = pos->y;
    m_position.z = pos->z;
    if (m_model != 0 && m_unk58 == 0) {
        GSmodelSetPosition(m_model, &m_position);
    }
}

// ---
void ModelSequence::ResetRotation() {
    if (m_model != 0) {
        GSmodelSetRotation(m_model, &m_rotation);
    }
}

// ---
void ModelSequence::SetRotation(GSvec* rot) {
    m_rotation.x = rot->x;
    m_rotation.y = rot->y;
    m_rotation.z = rot->z;
    if (m_model != 0 && m_unk58 == 0) {
        GSmodelSetRotation(m_model, rot);
        if (m_iceGen != 0) {
            GSparticleSetGeneratorRotation(m_iceGen, rot);
        }
        if (m_sleepGen != 0) {
            GSparticleSetGeneratorRotation(m_sleepGen, rot);
        }
    }
}

// ---
void ModelSequence::ResetScale() {
    if (m_model != 0) {
        GSmodelSetScale(m_model, &m_scale);
    }
}

// ---
void ModelSequence::SetScale(GSvec* scale) {
    m_scale.x = scale->x;
    m_scale.y = scale->y;
    m_scale.z = scale->z;
    if (m_model != 0 && m_unk58 == 0) {
        GSmodelSetScale(m_model, scale);
    }
}

// ---
void ModelSequence::SetVisibility(bool visible) {
    bool changed = m_visible != visible;
    m_visible = visible;
    UpdateVisibility(changed);
}

// ---
u8 ModelSequence::LoadData(u8* data) {
    GSpart* part;
    s32 list;
    PkxHeader* hdr = (PkxHeader*)data;
    s32 resID = wazaSequenceSysGetResID();
    if (hdr->size == 0) {
        return 0;
    }
    if (hdr->type != 0xC) {
        return 0;
    }
    if (m_unk4 == 0) {
        m_unk4 = hdr->id;
    }
    m_sleepAnim = &hdr->anims[0];
    m_wakeAnim = &hdr->anims[1];
    m_unk8C = &hdr->anims[2];
    m_talkAnim = &hdr->anims[3];
    m_distortionID = hdr->distortionID;
    m_distortionParam = hdr->distortionParam;
    m_unk5C = hdr->flags;
    if (m_distortionID == 0) {
        m_unk5C &= ~1;
    }
    data += 0x84;
    MotionSection* sections = (MotionSection*)data;
    MotionSection* sec = sections;
    u16 i = 0;
    m_unk46 = hdr->headJoint;
    m_modelSize = hdr->modelSize;
    m_section = 0;
    m_step = 0;
    m_timer = 0;
    m_stepRestart = 0;
    m_sections = sections;
    m_modelID = hdr->count;
    for (; i < m_modelID; i++, sec++) {
        MotionEntry* motion = sec->motions;
        for (s32 n = sec->count; n > 0; motion++, n--) {
            if (motion->type == 0) {
                motion->index = 1;
            }
        }
    }
    u8* body = (u8*)ALIGN32(sections + m_modelID);
    if (hdr->unk8 != 0) {
        m_unkB0 = GSmemAllocAlign(ALIGN32(hdr->unk8), 0x20);
        if (m_unkB0 != 0) {
            memcpy(m_unkB0, body, ALIGN32(hdr->unk8));
        }
        body += ALIGN32(hdr->unk8);
    }
    m_colors = &hdr->colors;
    if (m_colors->swap[0] >= 4 || m_colors->swap[0] < 0) {
        m_colors->swap[0] = 0;
    }
    if (m_colors->swap[1] >= 4 || m_colors->swap[1] < 0) {
        m_colors->swap[1] = 1;
    }
    if (m_colors->swap[2] >= 4 || m_colors->swap[2] < 0) {
        m_colors->swap[2] = 2;
    }
    if (m_colors->swap[3] >= 4 || m_colors->swap[3] < 0) {
        m_colors->swap[3] = 3;
    }
    if (m_colors->swap[0] != 0 || m_colors->swap[1] != 1 || m_colors->swap[2] != 2 || m_colors->swap[3] != 3) {
        m_colorSwap = 1;
    }
    if (m_colors->mod[0] != 0x7F || m_colors->mod[1] != 0x7F || m_colors->mod[2] != 0x7F || m_colors->mod[3] != 0x7F) {
        m_modulation = 1;
    }
    void* archive = hdr->model;
    if (archive == 0) {
        archive = operator new(0x44);
        if (archive == 0) {
            return 0;
        }
        m_unkA8 = GSmemAllocAlign(ALIGN32(hdr->size), 0x20);
        if (m_unkA8 == 0) {
            operator delete(archive);
            return 0;
        }
        m_unkAC = archive;
        memcpy(m_unkA8, body, ALIGN32(hdr->size));
        DCFlushRange(m_unkA8, ALIGN32(hdr->size));
        HSD_ArchiveParse(archive, (u8*)m_unkA8, hdr->size);
    }
    loadModel(archive, 0x4E20, 0, resID);
    GSresIsUniqueID(0x4E20, resID, 0);
    m_model = (_GSmodel*)GSresGetResource(0x4E20, resID);
    if (m_model == 0) {
        return 0;
    }
    GSmodelSetGroundPlane(m_model, 0, 0.0f);
    if (m_unk5C & 0x40) {
        GSmodelRemoveRootJointAnimation(m_model);
    }
    GSmodelSetKeepPartAnimFlag(m_model, 1);
    if (m_unk5C & 0x80) {
        GSmodelSetSkipFractionalFramesFlag(m_model, 1);
    }
    m_unk3C = resID;
    if (m_unkB0 != 0) {
        m_unk98 = GSparticleLoad(m_unkB0);
    }
    GSmodelSetAnimIndex(m_model, IdleMotion());
    GSmodelRecalculateBound(m_model);
    if (m_unk98 != 0) {
        GSmodelLinkToGSparticleBank(m_model, m_unk98);
        if (m_unk5C & 0x20) {
            GSmodelSetGSparticleLinkAttachMode(m_model, 1);
        } else {
            GSmodelSetGSparticleLinkAttachMode(m_model, 6);
        }
    }
    GSmodelLinkTexAnimToAnim(m_model, 1);
    GSmodelSetAnimEndedCallback(m_model, sequenceAnimEndCallback, this);
    DoDefaultAnimation(GS_ANIM_TYPE_1, true);
    SetVisibility(false);
    u8 flags = m_unk5C;
    if (flags & 1) {
        u8 mode = 0;
        if (flags & 2) {
            mode = 1;
            mode = !(flags & 8) ? mode : 1 | 4;
        }
        if (flags & 4) {
            mode |= 2;
            if (flags & 0x10) {
                mode |= 8;
            }
        }
        if (mode != 0) {
            GSmodelCreateDistortion(m_model, m_distortionID, m_distortionParam);
            GSmodelEnableDistortion(m_model);
        }
    }
    GSmodelSetPosition(m_model, &zeroVector);
    GSmodelSetRotation(m_model, &zeroVector);
    GSmodelSetScale(m_model, &unitScaleVector);
    GSmodelSetBoundCheck(m_model, 1);
    if (wazaSequenceSysGetModelShadowLight() != 0 && wazaSequenceSysGetModelShadowCount() != 0) {
        GSmodelSetShadowFlags(m_model, 1);
        GSmodelSetShadowLight(m_model, wazaSequenceSysGetModelShadowLight());
        list = wazaSequenceSysGetModelShadowList();
        GSmodelSetShadowSurface(m_model, wazaSequenceSysGetModelShadowCount(), list);
    }
    if (m_model != 0 && m_hasParent == 0 && m_unk46 != 0) {
        part = GSmodelGetPart(m_model, m_unk46);
        if (part != 0) {
            GSpartRegisterAnimMix(part, 2, 0x202, _getHeadRotationCallback, this);
            m_unk61 = 1;
            m_look.x = 0.0f;
            m_look.y = 0.0f;
            m_look.z = 0.0f;
            GSpartFree(part);
        }
    }
    return 1;
}

// ---
void ModelSequence::FreeData() {
    ModelSequence* parent = m_parent;
    if (parent != 0 && parent->m_unk61 != 0) {
        parent->m_unk78 = 0;
    }
    ModelSequence* target = m_unk78;
    if (target != 0) {
        target->m_parent = 0;
    }
    if (m_unk61 != 0 && m_model != 0 && m_hasParent == 0 && m_unk46 != 0) {
        GSpart* part = GSmodelGetPart(m_model, m_unk46);
        if (part != 0) {
            GSpartUnregisterAnimMix(part, 2);
            m_unk61 = 0;
            m_look.x = 0.0f;
            m_look.y = 0.0f;
            m_look.z = 0.0f;
            GSpartFree(part);
        }
    }
    if (m_unk60 != 0) {
        if (m_unk60 != 0) {
            _GSmodel* model = m_model;
            if (model != 0) {
                if (m_colorSwap != 0) {
                    GSmodelDisableColorSwap(model);
                }
                if (m_modulation != 0) {
                    GSmodelDisableModulation(model);
                }
            }
            m_unk60 = 0;
        }
    }
    if (m_model != 0) {
        GSmodelSetAnimEndedCallback(m_model, 0, 0);
    }
    SetVisibility(false);
    if (m_unk98 != 0) {
        DestroyParticles(true, false);
        GSparticleFree(m_unk98);
        m_unk98 = 0;
    }
    WakeUp();
    UnFreeze();
    Land();
    pachiruEffectFree(&m_pachiruA);
    if (m_unkB0 != 0) {
        GSmemFree(m_unkB0);
        m_unkB0 = 0;
    }
    if (m_unk3C != 0) {
        GSresFreeResource(0x4E20, m_unk3C);
        m_unk3C = 0;
    }
    if (m_unkA8 != 0) {
        GSmemFree(m_unkA8);
        m_unkA8 = 0;
    }
    if (m_unkAC != 0) {
        operator delete(m_unkAC);
        m_unkAC = 0;
    }
    wazaSequenceSysFreeSequenceResource(this);
    m_resID = 0;
    m_model = 0;
}

// ---
void ModelSequence::DestroyParticles(bool children, bool restart) {
    if (m_unk98 != 0) {
        GSparticleDestroyAllGenerators(m_unk98, children);
        if (restart) {
            s32 cur;
            GSmodelGetAnimIndex(m_model, &cur, 0);
            if (cur == IdleMotion()) {
                DoDefaultAnimation((GSmodelAnimType)GSmodelGetAnimType(m_model), true);
            }
        }
    }
}

// ---
void ModelSequence::UpdateVisibility(bool changed) {
    if (m_model != 0) {
        GSmodelSetVisibility(m_model, m_visible);
        if (m_unk98 != 0) {
            GSparticleSetBankVisibility(m_unk98, m_visible);
        }
        if (m_iceGen != 0) {
            GSparticleSetGeneratorVisibility(m_iceGen, m_visible);
        }
        if (m_sleepGen != 0) {
            GSparticleSetGeneratorVisibility(m_sleepGen, m_visible);
        }
        if (changed && m_visible && m_unk98 != 0) {
            GSparticleDestroyAllGenerators(m_unk98, 1);
            s32 cur;
            GSmodelGetAnimIndex(m_model, &cur, 0);
            if (cur == IdleMotion()) {
                DoDefaultAnimation((GSmodelAnimType)GSmodelGetAnimType(m_model), true);
            }
        }
    }
}

// ---
void ModelSequence::SetStatus(u8 status) {
    switch (status) {
    case 1:
        Sleep();
        break;
    case 2:
        Freeze();
        break;
    case 3:
        Fly(false);
        break;
    }
}

// ---
void ModelSequence::ResetStatus(u8 status) {
    switch (status) {
    case 1:
        WakeUp();
        break;
    case 2:
        UnFreeze();
        break;
    case 3:
        Land();
        break;
    }
}

// ---
void ModelSequence::DoModelAnimation(int section) {
    if (section == 0) {
        DoDefaultAnimation(GS_ANIM_TYPE_1, false);
    } else {
        m_section = section;
        int index = 0;
        m_step = 0;
        m_timer = 0;
        m_stepRestart = 0;
        MotionSection* sec = &m_sections[section];
        MotionEntry* motion = sec->motions;
        s32 count = sec->count;
        for (s32 n = count; n > 0; n--) {
            if (motion->type != 0) {
                break;
            }
            index++;
            motion++;
        }
        if (index == count) {
            DoDefaultAnimation(GS_ANIM_TYPE_1, false);
        } else {
            m_step = index;
            DoAnimation(motion->index, (enumSectionMotionType)motion->type, false);
        }
    }
}

// ---
void ModelSequence::SetInitFlags() {
    WakeUp();
    UnFreeze();
    Land();
    SetVisibility(!m_hasParent);
    m_flags = 0;
}

// ---
void ModelSequence::SetDefaultFlags() {
    WakeUp();
    UnFreeze();
    Land();
    SetVisibility(true);
}

// ---
void ModelSequence::SetFlags(u8 flags) {
    if (flags & 2) {
        Sleep();
    } else {
        WakeUp();
    }
    if (flags & 4) {
        Freeze();
    } else {
        UnFreeze();
    }
    if (flags & 1) {
        Fly(false);
    } else {
        Land();
    }
    m_flags = flags;
}

// ---
f32 _getHeadRotationCallback(GSpart* part, GSpartMixType type, void* user, GSvec* out) {
    ModelSequence* seq = (ModelSequence*)user;
    out->x = seq->m_look.x;
    out->y = seq->m_look.y;
    out->z = seq->m_look.z;
    return 1.0f;
}

// ---
void ModelSequence::UpdateLookAt() {
    if (m_unk61 != 0) {
        GSvec step;
        GSvec dir;
        ModelSequence* target = m_unk78;
        if (target == 0) {
            GSvec scaled;
            PSVECScale(&m_look, &scaled, 0.25f);
            step = scaled;
            PSVECSubtract(&m_look, &step, &m_look);
            return;
        }
        GSpart* targetPart = GSmodelGetPart(target->m_model, target->m_unk46);
        if (targetPart != 0) {
            GSpart* myPart = GSmodelGetPart(m_model, m_unk46);
            if (myPart == 0) {
                GSpartFree(targetPart);
                return;
            }
            f32* mtx = GSmodelGetMatrixPtr(m_model);
            GSvec right;
            right.x = mtx[0];
            right.y = mtx[4];
            right.z = mtx[8];
            PSVECNormalize(&right, &right);
            GSvec up;
            up.x = mtx[1];
            up.y = mtx[5];
            up.z = mtx[9];
            PSVECNormalize(&up, &up);
            GSvec myPos;
            GSpartGetTransform(myPart, &myPos, 0, 0);
            GSvec targetPos;
            GSpartGetTransform(targetPart, &targetPos, 0, 0);
            GSvec diff;
            PSVECSubtract(&targetPos, &myPos, &diff);
            dir = diff;
            PSVECNormalize(&dir, &dir);
            f32 dotUp = PSVECDotProduct(&up, &dir);
            f32 pitch = -(f32)asin(dotUp);
            GSvec proj;
            PSVECScale(&up, &proj, dotUp);
            GSvec projCopy = proj;
            PSVECSubtract(&dir, &projCopy, &dir);
            PSVECNormalize(&dir, &dir);
            f32 dotRight = PSVECDotProduct(&right, &dir);
            f32 oldPitch = m_look.x;
            volatile f32 oldYaw = m_look.y;
            f32 newPitch = 0.25f * (pitch - oldPitch) + oldPitch;
            f32 newYaw = 0.25f * ((f32)asin(dotRight) - oldYaw) + oldYaw;
            if (newPitch > 3.1415927f) {
                newPitch = 6.2831855f - newPitch;
            }
            if (newPitch < -0.2617994f) {
                newPitch = -0.2617994f;
            }
            if (newPitch > 0.2617994f) {
                newPitch = 0.2617994f;
            }
            if (newYaw > 3.1415927f) {
                newYaw = 6.2831855f - newYaw;
            }
            if (newYaw < -0.5235988f) {
                newYaw = -0.5235988f;
            }
            if (newYaw > 0.5235988f) {
                newYaw = 0.5235988f;
            }
            m_look.x = newPitch;
            m_look.y = newYaw;
            m_look.z = 0.0f;
            GSpartFree(myPart);
            GSpartFree(targetPart);
        }
    }
}

// ---
void ModelSequence::Update(f32 dt) {
    if (m_unk64 != 0 && m_unk62 != 0) {
        void* camera = m_camera ? m_camera : GScameraGetActiveCamera();
        GSpart* part;
        if (camera != 0) {
            part = GSmodelGetPart(m_unk64, m_unk62);
            if (part != 0) {
                GSvec rot;
                GSvec pos;
                GSpartGetTransform(part, &pos, 0, 0);
                SetPosition(&pos);
                GScameraGetRotation(camera, &rot);
                rot.x = 0.0f;
                rot.y = rot.y + m_unk68;
                rot.z = 0.0f;
                SetRotation(&rot);
                GSpartFree(part);
            }
        }
    }
    UpdateLookAt();
    UpdateVisibility(false);
    NullSequence::Update(dt);
    if (!IsActive() && !(m_flags & 4)) {
        if (m_mouthState != 0) {
            m_unk4A = 0;
        } else if (m_unk8C->enabled != 0) {
            m_unk4A += (u16)(u32)(dt * (f32)GSgfxVideoGetVsyncRate());
            u16 t = m_unk4A;
            if (t >= 10) {
                f32 chance;
                if (t >= 60) {
                    if (t >= 180) {
                        chance = 1.0f;
                    } else {
                        chance = 0.016666668f;
                    }
                } else {
                    s32 d = t - 10;
                    f32 x = (f32)d / 50.0f;
                    chance = x * (2.0f - x);
                    chance *= 0.016666668f;
                }
                if (chance >= HSD_Randf()) {
                    m_mouthState = 1;
                    wazaSequenceSysPartAnimationStart(m_model, m_unk8C);
                }
            }
        }
    }
    if (m_model != 0) {
        GSmodelSetRenderCamera(m_model, m_camera);
    }
    if (m_unk98 != 0) {
        GSparticleBankSetCamera(m_unk98, m_camera);
    }
    if (m_iceGen != 0) {
        GSparticleGeneratorSetCamera(m_iceGen, m_camera);
    }
    if (m_sleepGen != 0) {
        GSparticleGeneratorSetCamera(m_sleepGen, m_camera);
    }
}

// ---
void ModelSequence::Talk() {
    if (m_talkAnim->enabled != 0 && !(m_flags & 0x40)) {
        wazaSequenceSysPartAnimationStart(m_model, m_talkAnim);
        m_flags |= 0x40;
    }
}

// ---
void ModelSequence::DoAnimation(int index, enumSectionMotionType type, bool restart) {
    f32 frame = 0.0f;
    s32 animType;
    switch (type) {
    case SECTION_MOTION_2:
        animType = 1;
        break;
    case SECTION_MOTION_1:
        animType = 0;
        break;
    case 0:
    default:
        DoDefaultAnimation(GS_ANIM_TYPE_1, restart);
        return;
    }
    m_flags &= ~0x10;
    if (m_hasParent) {
        if (m_section == 10) {
            m_flags |= 8;
        } else if (m_flags & 4) {
            return;
        } else if (!(m_flags & 2)) {
            m_mouthState = 0;
            GSmodelLinkTexAnimToAnim(m_model, 1);
        }
    } else if (m_section == 5 || m_section == 10) {
        m_flags |= 8;
    }
    MotionSection* sections = m_sections;
    if (index == FirstMotion(sections)) {
        index = IdleMotion();
        if (!restart) {
            s32 cur;
            GSmodelGetAnimIndex(m_model, &cur, 0);
            if (index == cur) {
                frame = GSmodelGetAnimFrame(m_model);
            }
        }
    }
    GSmodelSetAnimEndedCallback(m_model, sequenceAnimEndCallback, this);
    GSmodelSetAnimIndex(m_model, index);
    GSmodelSetAnimType(m_model, animType);
    GSmodelSetAnimRate(m_model, 0.5f);
    GSmodelSetAnimFrame(m_model, frame);
    GSmodelStartAnimation(m_model);
}

// ---
void ModelSequence::DoDefaultAnimation(GSmodelAnimType type, bool restart) {
    if (!(m_flags & 8) && !(m_flags & 4)) {
        GSmodelSetAnimEndedCallback(m_model, sequenceAnimEndCallback, this);
        if (!(m_flags & 2)) {
            m_mouthState = 0;
            GSmodelLinkTexAnimToAnim(m_model, 1);
        }
        s32 idle = IdleMotion();
        s32 cur;
        GSmodelGetAnimIndex(m_model, &cur, 0);
        GSmodelSetAnimType(m_model, type);
        GSmodelSetAnimRate(m_model, 0.5f);
        if (idle != cur || restart || GSmodelHasAnimationEnded(m_model)) {
            GSmodelSetAnimIndex(m_model, idle);
            GSmodelSetAnimFrame(m_model, 0.0f);
        }
        if (restart) {
            m_section = 0;
            m_step = 0;
        }
        GSmodelStartAnimation(m_model);
    }
}

// ---
void ModelSequence::Sleep() {
    if (!(m_flags & 2)) {
        if (m_sleepAnim->enabled != 0 && m_mouthState != 2) {
            m_mouthState = 2;
            GSmodelSetDontResetPartAnimFlag(m_model, 1);
            wazaSequenceSysPartAnimationStart(m_model, m_sleepAnim);
        }
        m_flags |= 2;
    }
    GSparticleBank* bank;
    if (m_sleepGen == 0 && (bank = wazaSequenceSysGetSleepParticle()) != 0) {
        m_sleepGen = GSparticleCreateGenerator(bank, 0, 0);
        if (m_sleepGen != 0) {
            GSpart* part = GetPart(NULL_JOINT_1);
            if (part != 0) {
                f32 s = GetModelScale(true);
                GSvec scale;
                scale.x = s;
                scale.y = s;
                scale.z = s;
                GSparticleSetOffsetRotationInLocal(m_sleepGen, 1, 0);
                GSparticleSetParticleTextureScaling(m_sleepGen, 1);
                GSparticleSetTornadoScaling(m_sleepGen, 0, 0);
                GSparticleAttachGeneratorToGSpart(m_sleepGen, part, 1, 0, 1, 0);
                GSparticleSetGeneratorRotation(m_sleepGen, &m_rotation);
                GSparticleSetGeneratorScale(m_sleepGen, &scale, 1, 0);
                GSpartFree(part);
            }
        }
    }
}

// ---
void ModelSequence::WakeUp() {
    if (m_flags & 2) {
        if (m_wakeAnim->enabled != 0 && m_mouthState == 2) {
            m_mouthState = 1;
            GSmodelSetDontResetPartAnimFlag(m_model, 0);
            wazaSequenceSysPartAnimationStart(m_model, m_wakeAnim);
        }
        m_flags ^= 2;
        if (m_sleepGen != 0) {
            GSparticleDestroyGenerator(m_sleepGen, 1);
            m_sleepGen = 0;
        }
    }
}

// ---
void ModelSequence::Freeze() {
    if (!(m_flags & 4)) {
        m_flags |= 4;
        GSmodelStopAnimation(m_model);
    }
    GSparticleBank* bank;
    if (m_iceGen == 0 && (bank = wazaSequenceSysGetIceParticle()) != 0) {
        m_iceGen = GSparticleCreateGenerator(bank, 0, 0);
        if (m_iceGen != 0) {
            GSpart* part = GetPart(NULL_JOINT_16);
            if (part != 0) {
                f32 s = GetModelScale(true);
                GSvec scale;
                scale.x = s;
                scale.y = s;
                scale.z = s;
                GSparticleSetOffsetRotationInLocal(m_iceGen, 1, 0);
                GSparticleSetParticleTextureScaling(m_iceGen, 1);
                GSparticleSetTornadoScaling(m_iceGen, 0, 0);
                GSparticleAttachGeneratorToGSpart(m_iceGen, part, 1, 0, 1, 0);
                GSparticleSetGeneratorRotation(m_iceGen, &m_rotation);
                GSparticleSetGeneratorScale(m_iceGen, &scale, 1, 0);
                GSpartFree(part);
            }
        }
    }
}

// ---
void ModelSequence::UnFreeze() {
    if (m_flags & 4) {
        m_flags ^= 4;
        DoDefaultAnimation(GS_ANIM_TYPE_1, false);
        if (m_iceGen != 0) {
            GSparticleDestroyGenerator(m_iceGen, 1);
            m_iceGen = 0;
        }
    }
}

// ---
void ModelSequence::Fly(bool) {
    if (!(m_flags & 1)) {
        m_flags |= 1;
        DoDefaultAnimation(GS_ANIM_TYPE_1, false);
    }
}

// ---
void ModelSequence::Land() {
    if (m_flags & 1) {
        m_flags &= ~1;
        GSmodelRemoveNull(m_model);
        DoDefaultAnimation(GS_ANIM_TYPE_1, false);
    }
}

// ---
void ModelSequence::CopyState(ModelSequence* src) {
    SetInitFlags();
    if (src != 0) {
        SetVisibility(src->m_visible);
        if ((src->m_flags & 1) == 1) {
            if (GSmodelIsRootNullAdded(src->m_model)) {
                GSvec pos;
                GSmodelGetRootPosition(src->m_model, &pos);
                GSmodelAddNull(m_model, &pos, 0, 0);
            }
            Fly(false);
        }
        if ((src->m_flags & 2) == 2) {
            Sleep();
        }
        if ((src->m_flags & 4) == 4) {
            Freeze();
        }
    }
}

// ---
void ModelSequence::LinkWithWazaSequence(WazaSequence* seq) {
    if (seq == 0) {
        m_section = 0;
        m_step = 0;
        m_timer = 0;
        m_stepRestart = 0;
        ModelSequence* parent = m_parent;
        if (parent != 0 && parent->m_unk61 != 0) {
            parent->m_unk78 = 0;
        }
    } else {
        m_section = seq->m_section;
        m_step = 0;
        f32 duration = seq->m_duration;
        m_timer = (u32)(duration * (f32)GSgfxVideoGetVsyncRate());
        m_stepRestart = 0;
    }
}

// ---
GSpart* ModelSequence::GetPart(enumNullJointName joint) {
    MotionSection* section = &m_sections[m_section];
    s32 index;
    if (joint == NULL_JOINT_16) {
        index = GSmodelCenterNull(m_model);
        if (index == 0) {
            index = section->joints[2];
        }
    } else {
        index = section->joints[joint];
    }
    if (index >= 0) {
        return GSmodelGetPart(m_model, index);
    }
    return 0;
}

// ---
bool ModelSequence::ModelMotionStart() {
    if (m_flags & 8) {
        return false;
    }
    if (m_hasParent && (m_section == 10 || m_section == 9)) {
        WakeUp();
        UnFreeze();
        Land();
    }
    MotionEntry* motion = &m_sections[m_section].motions[0];
    if (m_flags & 4) {
        return true;
    }
    if (m_timer == 0) {
        m_step = 0;
        m_stepRestart = 0;
        DoAnimation(motion->index, (enumSectionMotionType)motion->type, false);
    } else {
        m_step = 0;
        int idle = IdleMotion();
        if (!(m_flags & 2)) {
            m_mouthState = 0;
            GSmodelLinkTexAnimToAnim(m_model, 1);
        }
        GSmodelSetAnimIndex(m_model, idle);
        GSmodelSetAnimType(m_model, 0);
        GSmodelSetAnimRate(m_model, 0.5f);
        f32 frames;
        GSmodelGetFrameCount(m_model, &frames, 0);
        frames -= 1.0f;
        if (frames < 1.0f) {
            frames = 1.0f;
        }
        u16 t = (m_timer >> 1) & 0x7FFF;
        u16 rem = t;
        if (t != 0) {
            rem = t - 1;
        }
        u16 divisor = __OSf32tou16(frames);
        m_timer = rem / divisor;
        u16 mod = __OSf32tou16(0.5f + frames);
        u16 part = rem % mod;
        if (part == 0 && m_timer != 0) {
            u16 whole = __OSf32tou16(0.5f + frames);
            s32 part = whole;
            m_timer--;
        }
        m_stepRestart = 1;
        GSmodelSetAnimFrame(m_model, frames - __OSu16tof32(&part));
        GSmodelStartAnimation(m_model);
    }
    return true;
}

// ---
static inline f32 SizeScale(const ModelSequence* seq) {
    switch (seq->m_modelSize) {
    case -2:
        return 0.5f;
    case -1:
        return 0.75f;
    case 1:
        return 1.3333f;
    case 2:
        return 2.0f;
    case 3:
        return 3.25f;
    }
    return 1.0f;
}

f32 ModelSequence::GetModelScale(bool raw) const {
    f32 scale = SizeScale(this);
    if (raw) {
        return scale;
    }
    return menuModelGetScale(m_hasParent, m_unk4);
}
