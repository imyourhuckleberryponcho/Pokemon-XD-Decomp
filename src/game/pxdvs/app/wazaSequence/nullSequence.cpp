#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

struct _GScamera;
class NullSequence;

class WazaSequence {
public:
    ~WazaSequence();
    bool Update(f32 dt);
    void SetRenderCamera(_GScamera* camera);

    bool IsActive() const {
        return m_active && !m_finished;
    }

    u8 unk0[0xC];
    u16 m_wazaID;
    u8 m_kind;
    u8 unkF[5];
    u8 m_active;
    u8 unk15[2];
    u8 m_finished;
    u8 unk18[0xC];
    NullSequence* m_owner;
    WazaSequence* m_next;
    WazaSequence* m_prev;
};

// A group of move animations ("sequences") sharing one transform.
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

    void Remove(WazaSequence* sequence);
    void Add(WazaSequence* sequence);
    WazaSequence* GetWaza(unsigned short wazaID, unsigned short kind) const;
    bool IsActive() const;
    void FreeAllWaza();

    u16 m_unk4;
    bool m_visible;
    u8 m_unk7;
    u32 m_unk8;
    GSvec m_position;
    GSvec m_rotation;
    GSvec m_scale;
    WazaSequence* m_list;
    _GScamera* m_camera;
    NullSequence* m_next;
};

extern NullSequence* g_Sequences;

void NullSequence::Remove(WazaSequence* sequence) {
    WazaSequence* next;
    WazaSequence* prev;
    if (sequence == NULL) {
        return;
    }
    next = sequence->m_next;
    prev = sequence->m_prev;
    if (next != NULL) {
        next->m_prev = prev;
    }
    if (prev != NULL) {
        prev->m_next = next;
    } else {
        m_list = next;
    }
}

void NullSequence::Add(WazaSequence* sequence) {
    sequence->m_next = m_list;
    if (m_list != NULL) {
        m_list->m_prev = sequence;
    }
    sequence->m_prev = NULL;
    sequence->m_owner = this;
    m_list = sequence;
}

WazaSequence* NullSequence::GetWaza(unsigned short wazaID, unsigned short kind) const {
    WazaSequence* sequence;
    for (sequence = m_list; sequence != NULL; sequence = sequence->m_next) {
        if (wazaID == sequence->m_wazaID && kind == sequence->m_kind) {
            break;
        }
    }
    return sequence;
}

bool NullSequence::IsActive() const {
    WazaSequence* sequence;
    for (sequence = m_list; sequence != NULL; sequence = sequence->m_next) {
        if (sequence->IsActive()) {
            return true;
        }
    }
    return false;
}

void NullSequence::Update(f32 dt) {
    WazaSequence* next;
    WazaSequence* sequence;

    for (sequence = m_list; sequence != NULL; sequence = next) {
        next = sequence->m_next;
        if (sequence->IsActive() && !sequence->Update(dt)) {
            sequence->m_finished = true;
        }
    }
    for (sequence = m_list; sequence != NULL; sequence = sequence->m_next) {
        sequence->SetRenderCamera(m_camera);
    }
}

void NullSequence::FreeAllWaza() {
    WazaSequence* sequence = m_list;
    while (sequence != NULL) {
        WazaSequence* next = sequence->m_next;
        delete sequence;
        sequence = next;
    }
    m_list = NULL;
}

void NullSequence::SetVisibility(bool visible) {
    m_visible = visible;
}

void NullSequence::SetScale(GSvec* scale) {
    m_scale.x = scale->x;
    m_scale.y = scale->y;
    m_scale.z = scale->z;
}

void NullSequence::SetRotation(GSvec* rot) {
    m_rotation.x = rot->x;
    m_rotation.y = rot->y;
    m_rotation.z = rot->z;
}

void NullSequence::SetPosition(GSvec* pos) {
    m_position.x = pos->x;
    m_position.y = pos->y;
    m_position.z = pos->z;
}

void NullSequence::GetScale(GSvec* scale) {
    scale->x = m_scale.x;
    scale->y = m_scale.y;
    scale->z = m_scale.z;
}

void NullSequence::GetRotation(GSvec* rot) {
    rot->x = m_rotation.x;
    rot->y = m_rotation.y;
    rot->z = m_rotation.z;
}

void NullSequence::GetPosition(GSvec* pos) {
    pos->x = m_position.x;
    pos->y = m_position.y;
    pos->z = m_position.z;
}

NullSequence::~NullSequence() {
    NullSequence* seq = g_Sequences;
    FreeAllWaza();
    if (seq != NULL) {
        if (seq == this) {
            g_Sequences = m_next;
        } else {
            for (; seq->m_next != NULL; seq = seq->m_next) {
                if (seq->m_next == this) {
                    seq->m_next = m_next;
                    break;
                }
            }
        }
    }
}

NullSequence::NullSequence() {
    m_unk4 = 0;
    m_visible = true;
    m_unk7 = 0;
    m_unk8 = 0;
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_position.z = 0.0f;
    m_rotation.x = 0.0f;
    m_rotation.y = 0.0f;
    m_rotation.z = 0.0f;
    m_scale.x = 1.0f;
    m_scale.y = 1.0f;
    m_scale.z = 1.0f;
    m_list = NULL;
    m_camera = NULL;
    m_next = NULL;
}

NullSequence* New_NullSequence() {
    NullSequence* seq = new NullSequence;
    if (seq == NULL) {
        return NULL;
    }
    seq->m_next = g_Sequences;
    g_Sequences = seq;
    return seq;
}
