// Draft (dr4). WazaSequence: one move animation made of "entries" (camera, model, particle, ...).
#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
};

struct _GScamera;
struct _GSmodel;
class WazaSequence;

struct HSD_Archive {
    u8 pad[0x44];
};

enum GSmodelAnimType {
    GS_ANIM_TYPE_0,
    GS_ANIM_TYPE_1
};

// From the Dolphin SDK's OSFastCast.h (GQR3 is set up for u16 conversion).
static inline f32 __OSu16tof32(register const u16* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 3 }
    return ret;
}

class GSgfxLayer {
public:
    void SetDistortionParams(float (*mtx)[3], s8 flag);

    GSgfxLayer* m_next;
    u8 unk4[0x2c - 4];
    s32 m_kind;
};

class NullSequence {
public:
    virtual ~NullSequence();
    virtual void Update(f32 dt);
    virtual void GetPosition(GSvec* pos);
    virtual void GetRotation(GSvec* rot);
    virtual void GetScale(GSvec* scale);
    virtual void SetPosition(GSvec* pos);
    virtual void SetRotation(GSvec* rot);
    virtual void SetScale(GSvec* scale);
    virtual void SetVisibility(bool visible);

    void Remove(WazaSequence* sequence);
    void Add(WazaSequence* sequence);

    u16 m_unk4;
    bool m_visible;
    u8 m_unk7;
    s32 m_kind;
};

class ModelSequence : public NullSequence {
public:
    void LinkWithWazaSequence(WazaSequence* seq);
    bool ModelMotionStart();
    void DoDefaultAnimation(GSmodelAnimType type, bool restart);
    void DestroyParticles(bool children, bool restart);

    u8 unkC[0x51 - 0xC];
    u8 m_maxSection;
    u8 m_section;
    u8 unk53;
    u8 m_flags;
    u8 unk55;
    u8 m_busy;
    u8 unk57[0x94 - 0x57];
    _GSmodel* m_model;
    void* m_particle;
};

class SequenceEntry {
public:
    SequenceEntry();
    virtual ~SequenceEntry();
    virtual bool Start();
    virtual bool Update(f32 dt);
    virtual void End();
    virtual void Stop(bool immediate);
    virtual void SetRenderCamera(_GScamera* camera);
    void Link();

    u8 unk4[0x18 - 4];
    s32 m_state;
    f32 m_start;
    f32 m_nextTime;
    SequenceEntry* m_next;
};

// Parses/owns the header of a sequence file while its entries are loaded.
class MainSequenceEntry {
public:
    MainSequenceEntry(WazaSequence* seq, u8** data);
    ~MainSequenceEntry();
    u8 unk[0x34];
};

class CameraEntry : public SequenceEntry {
public:
    CameraEntry(WazaSequence* seq, u8** data);
    static bool Load(u8** data);
    static void Unload(u8** data);
    u8 pad[0x38 - 0x28];
};

class ModelEntry : public SequenceEntry {
public:
    ModelEntry(WazaSequence* seq, u8** data);
    static bool Load(u8** data);
    static void Unload(u8** data);
    u8 pad[0x50 - 0x28];
};

class ParticleEntry : public SequenceEntry {
public:
    ParticleEntry(WazaSequence* seq, u8** data);
    static bool Load(u8** data);
    static void Unload(u8** data);
    u8 pad[0x44 - 0x28];
};

class EffectEntry : public SequenceEntry {
public:
    EffectEntry(WazaSequence* seq, u8** data);
    static bool Load(u8** data);
    static void Unload(u8** data);
    u8 pad[0x44 - 0x28];
};

class SoundEntry : public SequenceEntry {
public:
    SoundEntry(WazaSequence* seq, u8** data);
    static bool Load(u8** data);
    static void Unload(u8** data);
    u8 pad[0x40 - 0x28];
};

class EventEntry : public SequenceEntry {
public:
    EventEntry(WazaSequence* seq, u8** data);
    static bool Load(u8** data);
    static void Unload(u8** data);
    u8 pad[0x34 - 0x28];
};

class LensFlareEntry : public SequenceEntry {
public:
    LensFlareEntry(WazaSequence* seq, u8** data);
    static bool Load(u8** data);
    static void Unload(u8** data);
    u8 pad[0x3c - 0x28];
};

// File header of a move animation sequence.
struct WazaHeader {
    u16 distortion;
    u16 section;
    s32 count;
    u32 flags;
    u32 partKind;
    s32 version;
    s32 cameraSize;
    u32 unk18;
    HSD_Archive* camera;
};

struct WazaResourceEntry {
    u32 groupID;
    u32 unk4;
};

struct WazaWzxEntry {
    u16 res[3];
};

struct WazaExtWzxEntry {
    u8 variation;
    u8 pad1;
    u16 wazaID;
    u16 res[3];
};

f32 wazaSequenceSysGetWazaTime(ModelSequence* seq, WazaSequence* waza, u8 mode);
f32 wazaSequenceSysNullGetWazaTime(WazaSequence* waza, u8 mode);

class WazaSequence {
public:
    WazaSequence(NullSequence* owner, u16 wazaID, u8 kind, u8 variation);
    ~WazaSequence();
    bool LoadData(u8* data);
    bool IsImpactPoint(u8 flag);
    SequenceEntry* GetEntryFromID(u8 id);
    bool Update(f32 dt);
    void ApplyStop();
    void Start(bool camera);
    void SetRenderCamera(_GScamera* camera);
    static int GetNumVariations(u16 wazaID, u16 kind);
    static void Unload(u8* data);
    static bool Load(u8* data, u32 a, u32 b);

    bool IsActive() const {
        return m_active && !m_finished;
    }

    inline f32 GetTime(u8 mode) {
        if (m_owner->m_kind == 1) {
            return wazaSequenceSysGetWazaTime((ModelSequence*)m_owner, this, mode);
        }
        return wazaSequenceSysNullGetWazaTime(this, mode);
    }

    f32 m_time;
    f32 m_duration;
    u32 m_flags;
    u16 m_wazaID;
    u8 m_kind;
    u8 m_error;
    u16 m_resID;
    u8 m_numEntries;
    u8 m_section;
    u8 m_active;
    u8 m_started;
    u8 m_partKind;
    u8 m_finished;
    f32 m_distortion;
    u32 m_camera;
    SequenceEntry* m_entries;
    NullSequence* m_owner;
    WazaSequence* m_next;
    WazaSequence* m_prev;
};

void* operator new(unsigned long size);
void operator delete(void* p);

extern WazaSequence* g_LastStartedWaza;
extern u8 g_EnableModelLayerChange;
extern WazaResourceEntry waza_resource_data[];
extern WazaWzxEntry waza_wzx_data[];
extern WazaExtWzxEntry waza_ext_wzx_data[];
extern u16 waza_generic_wzx_data[];
extern u32 waza_wzx_data_number;
extern u32 waza_ext_wzx_data_number;
extern u32 waza_generic_wzx_data_number;

extern "C" {
void GSmodelLinkToGSparticleBank(_GSmodel* model, void* bank);
void GSmodelSetRenderLayer(_GSmodel* model, s32 count, s32* layers);
void GSresFreeResource(u32 grp, u32 id);
void GSresIsUniqueID(u32 grp, u32 id, u8 unique);
void* GSresGetResource(u32 grp, u32 id);
GSgfxLayer* GSgfxLayerGetLayerList();
s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, u32 size);
void loadCamera(HSD_Archive* archive, u32 arg1, u32 arg2);
s32 wazaSequenceSysGetResID(void);
bool wazaSequenceSysIsValidWaza(WazaSequence* waza);
void battleCameraStartWaza(WazaSequence* waza);
void battleGridHideModelsExcept(NullSequence* seq);
}

f32 wazaSequenceSysGetWazaTime(ModelSequence* seq, WazaSequence* waza, u8 mode);
f32 wazaSequenceSysNullGetWazaTime(WazaSequence* waza, u8 mode);
void wazaSequenceSysFreeWazaResource(WazaSequence* waza);
void wazaSequenceSysApplyStop();
void wazaSequenceSysResetAnimationExcept(ModelSequence* except);
u8* wazaSequenceSysLoadResource(u32 a, u32 b);
u16 wazaSequenceSysGetResourceID(ModelSequence* seq, u16 wazaID, u16 kind, u8 variation);

static f32 distmtx[2][3] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};

static inline ModelSequence* AsModel(NullSequence* seq) {
    ModelSequence* r;
    if (seq->m_kind == 1) {
        r = (ModelSequence*)seq;
    } else {
        r = 0;
    }
    return r;
}

static inline u8* Align32(u8* p) {
    return (u8*)(((u32)p + 0x1F) & ~0x1F);
}

bool WazaSequence::Load(u8* data, u32 a, u32 b) {
    u8* p = data;
    MainSequenceEntry main(0, &p);
    WazaHeader* hdr;
    u16 count;
    u16 i;

    wazaSequenceSysGetResID();
    hdr = (WazaHeader*)p;
    p = (u8*)hdr + 0x20;
    p = Align32(p);
    count = hdr->count - 1;
    hdr->camera = 0;
    if (hdr->cameraSize != 0) {
        HSD_Archive* archive = (HSD_Archive*)operator new(0x44);
        if (archive != 0) {
            hdr->camera = archive;
            HSD_ArchiveParse(archive, p, hdr->cameraSize);
        }
        p = p + (((u32)hdr->cameraSize + 0x1F) & ~0x1F);
    }
    for (i = 0; i < count; i++) {
        switch (*(u32*)(p + 4)) {
        case 1:
            if (!CameraEntry::Load(&p)) {
                return false;
            }
            break;
        case 2:
            if (!ModelEntry::Load(&p)) {
                return false;
            }
            break;
        case 3:
            if (!ParticleEntry::Load(&p)) {
                return false;
            }
            break;
        case 4:
            if (!EffectEntry::Load(&p)) {
                return false;
            }
            break;
        case 5:
            if (!SoundEntry::Load(&p)) {
                return false;
            }
            break;
        case 6:
            if (!EventEntry::Load(&p)) {
                return false;
            }
            break;
        case 7:
            if (!LensFlareEntry::Load(&p)) {
                return false;
            }
            break;
        default:
            return false;
        }
    }
    return true;
}

void WazaSequence::Unload(u8* data) {
    u8* p = data;
    MainSequenceEntry main(0, &p);
    WazaHeader* hdr = (WazaHeader*)p;
    u16 count;
    u16 i;

    p = (u8*)hdr + 0x20;
    p = Align32(p);
    count = hdr->count - 1;
    if (hdr->camera != 0) {
        operator delete(hdr->camera);
        hdr->camera = 0;
    }
    if (hdr->cameraSize != 0) {
        p = p + (((u32)hdr->cameraSize + 0x1F) & ~0x1F);
    }
    for (i = 0; i < count; i++) {
        switch (*(u32*)(p + 4)) {
        case 1:
            CameraEntry::Unload(&p);
            break;
        case 2:
            ModelEntry::Unload(&p);
            break;
        case 3:
            ParticleEntry::Unload(&p);
            break;
        case 4:
            EffectEntry::Unload(&p);
            break;
        case 5:
            SoundEntry::Unload(&p);
            break;
        case 6:
            EventEntry::Unload(&p);
            break;
        case 7:
            LensFlareEntry::Unload(&p);
            break;
        default:
            break;
        }
    }
}

WazaSequence::WazaSequence(NullSequence* owner, u16 wazaID, u8 kind, u8 variation) {
    m_time = 0.0f;
    m_duration = 0.0f;
    m_flags = 0;
    m_wazaID = 0;
    m_kind = 0;
    m_error = 0;
    m_resID = 0;
    m_numEntries = 0;
    m_section = 0;
    m_active = 0;
    m_started = 0;
    m_partKind = 0;
    m_finished = 0;
    m_camera = 0;
    m_entries = 0;
    m_owner = 0;
    m_next = 0;
    m_prev = 0;

    if (owner == 0) {
        m_error = 1;
    } else if (kind == 0) {
        m_error = 1;
    } else {
        ModelSequence* ms = 0;
        u16 resID;
        if (owner->m_kind == 1) {
            ms = (ModelSequence*)owner;
        }
        resID = wazaSequenceSysGetResourceID(ms, wazaID, kind, variation);
        if (resID == 0) {
            m_error = 1;
        } else {
            u32 a = waza_resource_data[resID].groupID;
            u32 b = waza_resource_data[resID].unk4;
            u8* data;
            if (a == 0 || b == 0) {
                m_error = 1;
            } else {
                data = wazaSequenceSysLoadResource(a, b);
                m_resID = a;
                if (data == 0) {
                    m_error = 1;
                } else {
                    m_wazaID = wazaID;
                    m_kind = kind;
                    owner->Add(this);
                    if (!LoadData(data)) {
                        m_error = 2;
                    }
                }
            }
        }
    }
}

WazaSequence::~WazaSequence() {
    if (m_active) {
        ApplyStop();
    }
    delete m_entries;
    if (m_camera != 0) {
        GSresFreeResource(20000, m_camera);
    }
    wazaSequenceSysFreeWazaResource(this);
    if (m_owner != 0) {
        m_owner->Remove(this);
    }
}

int WazaSequence::GetNumVariations(u16 wazaID, u16 kind) {
    int n = 0;
    if (kind == 0) {
        return 0;
    }
    if (kind == 4) {
        if (wazaID == 0 || wazaID >= waza_generic_wzx_data_number) {
            return 0;
        }
        if (waza_generic_wzx_data[wazaID] != 0) {
            n = 1;
        }
    } else {
        WazaExtWzxEntry* x = waza_ext_wzx_data;
        u16 idx = kind - 1;
        u32 i;
        if (wazaID == 0 || wazaID >= waza_wzx_data_number) {
            return 0;
        }
        if (waza_wzx_data[wazaID].res[idx] != 0) {
            n = 1;
        }
        for (i = 0; i < waza_ext_wzx_data_number; i++, x++) {
            if (x->wazaID == wazaID && x->res[idx] != 0) {
                n++;
            }
        }
    }
    return n;
}

void WazaSequence::SetRenderCamera(_GScamera* camera) {
    SequenceEntry* e;
    for (e = m_entries; e != 0; e = e->m_next) {
        bool running = false;
        if (e->m_state == 1 || e->m_state == 3) {
            running = true;
        }
        if (running) {
            e->SetRenderCamera(camera);
        }
    }
}

void WazaSequence::Start(bool camera) {
    ModelSequence* ms;
    SequenceEntry* e;
    GSgfxLayer* layer;

    if (m_active) {
        ApplyStop();
    }
    wazaSequenceSysApplyStop();
    ms = AsModel(m_owner);
    e = m_entries;
    if (ms != 0) {
        _GSmodel* model = ms->m_model;
        ms->LinkWithWazaSequence(this);
        if (ms->m_busy != 0 && m_kind == 2) {
            wazaSequenceSysResetAnimationExcept(ms);
        }
        if (m_flags & 0x80000000) {
            ms->DestroyParticles((m_flags & 0x8000) == 0, false);
        }
        if (m_flags & 0x08000000) {
            GSmodelLinkToGSparticleBank(model, 0);
        }
        ms->ModelMotionStart();
        if ((m_flags & 2) && g_EnableModelLayerChange) {
            s32 layers[1] = {4};
            GSmodelSetRenderLayer(model, 1, layers);
        }
        if (camera) {
            battleCameraStartWaza(this);
        }
        if (m_flags & 0x04000000) {
            battleGridHideModelsExcept(ms);
        }
    }
    m_active = 1;
    for (; e != 0; e = e->m_next) {
        e->m_state = 0;
    }
    distmtx[1][1] = distmtx[0][1] = 0.5f * m_distortion;
    for (layer = GSgfxLayerGetLayerList(); layer != 0; layer = layer->m_next) {
        if (layer->m_kind == 1) {
            layer->SetDistortionParams(distmtx, 0);
        }
    }
    m_time = 0.0f;
    m_started = 0;
    g_LastStartedWaza = Update(0.0f) ? this : 0;
}

void WazaSequence::ApplyStop() {
    ModelSequence* ms;
    SequenceEntry* e;
    GSgfxLayer* layer;

    m_finished = 0;
    if (m_active) {
        if (g_LastStartedWaza == this) {
            g_LastStartedWaza = 0;
        }
        ms = AsModel(m_owner);
        if (ms != 0) {
            _GSmodel* model = ms->m_model;
            if (m_flags & 0x08000000) {
                GSmodelLinkToGSparticleBank(model, ms->m_particle);
            }
            if (ms->m_busy == 0) {
                ms->DoDefaultAnimation(GS_ANIM_TYPE_1, false);
            }
            if ((m_flags & 2) && g_EnableModelLayerChange) {
                s32 layers[1] = {2};
                GSmodelSetRenderLayer(model, 1, layers);
            }
        }
        for (e = m_entries; e != 0; e = e->m_next) {
            e->Stop(true);
        }
        distmtx[1][1] = distmtx[0][1] = 0.5f;
        for (layer = GSgfxLayerGetLayerList(); layer != 0; layer = layer->m_next) {
            if (layer->m_kind == 1) {
                layer->SetDistortionParams(distmtx, 0);
            }
        }
        m_active = 0;
        m_started = 0;
    }
}

bool WazaSequence::Update(f32 dt) {
    SequenceEntry* e = m_entries;
    int waiting = 0;
    int running = 0;
    ModelSequence* ms;

    m_time += dt;
    if (GetTime(3) > m_time) {
        running = 1;
    }
    ms = AsModel(m_owner);
    if (ms != 0) {
        u8 f = ms->m_flags;
        if ((f & 8) != 8 && (f & 0x10) == 0x10) {
            if (GetTime(2) < m_time) {
                return false;
            }
        }
        if (ms->m_section != 0 && (ms->m_flags & 4) != 4) {
            running++;
        }
    }
    for (; e != 0; e = e->m_next) {
        switch (e->m_state) {
        case 0:
            if (e->m_start <= 0.00001f + m_time) {
                if (e->Start()) {
                    running++;
                } else {
                    e->m_state = -1;
                }
            } else {
                e->m_nextTime = e->m_start;
                waiting++;
            }
            break;
        case 1:
            if (e->Update(dt)) {
                running++;
            } else {
                e->Stop(false);
            }
            break;
        case 3:
            if (!e->Update(dt)) {
                e->Stop(false);
            }
            break;
        }
    }
    if (running + waiting == 0) {
        return false;
    }
    return m_started == 0;
}

SequenceEntry* WazaSequence::GetEntryFromID(u8 id) {
    SequenceEntry* e;
    for (e = m_entries; e != 0; e = e->m_next) {
        if (*((u8*)e + 4) == id) {
            break;
        }
    }
    return e;
}

bool WazaSequence::IsImpactPoint(u8 flag) {
    if (flag == 4) {
        return m_active == 0;
    }
    return m_time >= GetTime(flag);
}

bool WazaSequence::LoadData(u8* data) {
    u8* p = data;
    MainSequenceEntry main(this, &p);
    WazaHeader* hdr;
    ModelSequence* ms;
    SequenceEntry* e;
    u16 i;

    if (m_owner == 0) {
        return false;
    }
    hdr = (WazaHeader*)p;
    p = (u8*)hdr + 0x20;
    m_numEntries = hdr->count - 1;
    m_section = hdr->section;
    if (hdr->version >= 6) {
        u16 d = hdr->distortion;
        m_distortion = __OSu16tof32(&d) / 65535.0f;
    } else {
        m_distortion = 1.0f;
    }
    ms = AsModel(m_owner);
    if (ms != 0) {
        u8 sec = m_section;
        if (sec == 11) {
            if (ms->m_maxSection < sec) {
                m_section = 0;
            }
        } else if (sec >= 12 && sec < 16) {
            if (ms->m_maxSection < sec) {
                m_section = 1;
            }
        }
    }
    m_flags = hdr->flags;
    m_partKind = hdr->partKind;
    p = Align32(p);
    if (hdr->version <= 3) {
        m_flags |= 0x78;
    }
    if (hdr->version <= 5) {
        m_flags &= 0xFFE07FFF;
    }
    if (hdr->camera != 0) {
        s32 id = wazaSequenceSysGetResID();
        loadCamera(hdr->camera, 20000, id);
        GSresIsUniqueID(20000, id, 0);
        if (GSresGetResource(20000, id) != 0) {
            m_camera = id;
        }
        p = p + (((u32)hdr->cameraSize + 0x1F) & ~0x1F);
    } else {
        m_camera = 0;
    }
    for (i = 0; i < m_numEntries; i++) {
        switch (*(u32*)(p + 4)) {
        case 1:
            e = new CameraEntry(this, &p);
            break;
        case 2:
            e = new ModelEntry(this, &p);
            break;
        case 3:
            e = new ParticleEntry(this, &p);
            break;
        case 4:
            e = new EffectEntry(this, &p);
            break;
        case 5:
            e = new SoundEntry(this, &p);
            break;
        case 6:
            e = new EventEntry(this, &p);
            break;
        case 7:
            e = new LensFlareEntry(this, &p);
            break;
        default:
            return false;
        }
        e->Link();
    }
    e = m_entries;
    m_duration = 0.0f;
    for (; e != 0; e = e->m_next) {
        if (e->m_start < m_duration) {
            m_duration = e->m_start;
        }
    }
    if (m_duration < 0.0f) {
        m_duration = -m_duration;
        for (e = m_entries; e != 0; e = e->m_next) {
            e->m_start += m_duration;
            e->m_nextTime += m_duration;
        }
    }
    return true;
}

extern "C" {

void WazaSequence_Start(WazaSequence* seq, bool camera) {
    if (seq != 0 && wazaSequenceSysIsValidWaza(seq)) {
        seq->Start(camera);
    }
}

void WazaSequence_Stop(WazaSequence* seq) {
    if (seq != 0 && wazaSequenceSysIsValidWaza(seq)) {
        seq->m_finished = 1;
    }
}

void WazaSequence_Free(WazaSequence* seq) {
    if (seq != 0 && wazaSequenceSysIsValidWaza(seq)) {
        delete seq;
    }
}

WazaSequence* Sequence_LoadWaza(NullSequence* owner, u16 wazaID, u8 kind, u8 variation) {
    WazaSequence* seq = new WazaSequence(owner, wazaID, kind, variation);
    if (seq == 0) {
        return 0;
    }
    if (seq->m_error != 0) {
        delete seq;
        seq = 0;
    }
    return seq;
}

bool WazaSequence_IsActive(WazaSequence* seq) {
    if (seq == 0) {
        return false;
    }
    if (wazaSequenceSysIsValidWaza(seq)) {
        return seq->IsActive();
    }
    return false;
}

}  // extern "C"
