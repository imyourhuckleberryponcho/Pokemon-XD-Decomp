#include <dolphin/types.h>

#define ALIGN32(x) (((u32)(x) + 0x1F) & ~0x1F)

// Animation keys (16 bytes each) follow an effect's parameters in the sequence data.
#define LOAD_KEYS(data, num)          m_hasKeys = 1;                    m_keys = *(data);                 m_keyNum = (num);                 m_time = 0.0f;                    m_keyIndex = 0;                   *(data) += m_keyNum * 16;

struct _GSparticleBank;
enum enumNullJointName {
    NULL_JOINT_0
};

class GSeffect {
public:
    u32 unk0;
    u32 unk4;

    GSeffect();
    virtual ~GSeffect();
    virtual void effectInit();
    virtual void effectUpdate();
    virtual void effectRender();
    virtual void effectEnd();
    virtual void effectFree();
};

class boneFillEffect : public GSeffect {
public:
    boneFillEffect(_GSparticleBank* bank, enumNullJointName from, enumNullJointName to, f32 time);

    u8 unkC[0x20];
};

class blurEffect : public GSeffect {
public:
    blurEffect(bool on);

    u8 unkC[0x10];
};

class envMapEffect : public GSeffect {
public:
    envMapEffect(u32 texture, u32 model) {
        unkC = 0;
        m_texture = texture;
        m_model = model;
        m_time = 0.0f;
    }
    virtual ~envMapEffect();
    virtual void effectInit();
    virtual void effectUpdate();
    virtual void effectRender();
    virtual void effectEnd();
    virtual void effectFree();

    u32 unkC;
    u32 m_texture;
    u32 m_model;
    f32 m_time;
};

class filterEffect : public GSeffect {
public:
    filterEffect() {
        unkC = 0;
        m_type = 0;
        m_alpha = 0;
        m_color[2] = 0;
        m_color[1] = 0;
        m_color[0] = 0;
    }
    filterEffect(bool invert, bool mono) {
        unkC = 0;
        m_invert = invert;
        unk15 = 0;
        unk16 = 0;
        u8 type = 2;
        if (mono) {
            type = 1;
        }
        m_type = type;
        m_color[2] = 0x7F;
        m_color[1] = 0x7F;
        m_color[0] = 0x7F;
        m_alpha = invert ? 0 : 0xFF;
    }
    virtual ~filterEffect();
    virtual void effectInit();
    virtual void effectUpdate();
    virtual void effectRender();
    virtual void effectEnd();
    virtual void effectFree();

    u32 unkC;
    u8 unk10[4];
    u8 m_invert;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 m_type;
    u8 m_color[3];
    u8 m_alpha;
};

class WazaSequence;

class EffectEntry {
public:
    void boneFillEffectLoad(u8** data);
    void blurEffectLoad(u8** data);
    void envMapEffectLoad(u8** data);
    void filterEffectLoad(u8** data);

    u8 unk0[9];
    u8 m_parentID;
    u8 unkA[0x22];
    WazaSequence* m_sequence;
    GSeffect* m_effect;
    u8* m_keys;
    f32 m_time;
    u8 m_keyNum;
    u8 m_keyIndex;
    u8 unk3E[2];
    u8 m_hasKeys;
};

class WazaSequence {
public:
    EffectEntry* GetEntryFromID(u8 id);
};

struct BoneFillEffectData {
    enumNullJointName from;
    enumNullJointName to;
    f32 time;
    u32 size;
    _GSparticleBank* bank;
    u32 unk14;
};

struct BlurEffectData {
    u32 keyNum;
    u32 unk4;
    u32 on;
};

struct EnvMapEffectData {
    u32 texture;
    u32 model;
    u32 keyNum;
    u32 unkC;
};

struct FilterEffectData {
    s32 type;
    u32 keyNum;
    u32 unk8;
    s32 flags;
};

void EffectEntry::boneFillEffectLoad(u8** data) {
    BoneFillEffectData* effect = (BoneFillEffectData*)*data;
    _GSparticleBank* bank = NULL;

    *data += sizeof(BoneFillEffectData);
    *data = (u8*)ALIGN32(*data);
    *data += ALIGN32(effect->size);
    if (m_parentID != 0) {
        EffectEntry* parent = m_sequence->GetEntryFromID(m_parentID);
        if (parent->m_effect != NULL) {
            bank = (_GSparticleBank*)((u32*)parent->m_effect)[3];
        }
    } else {
        bank = effect->bank;
    }
    m_effect = new boneFillEffect(bank, effect->from, effect->to, effect->time);
}

void EffectEntry::blurEffectLoad(u8** data) {
    BlurEffectData* effect = (BlurEffectData*)*data;
    *data += sizeof(BlurEffectData);
    LOAD_KEYS(data, effect->keyNum);
    m_effect = new blurEffect(effect->on != 0);
}

void EffectEntry::envMapEffectLoad(u8** data) {
    EnvMapEffectData* effect = (EnvMapEffectData*)*data;
    *data += sizeof(EnvMapEffectData);
    LOAD_KEYS(data, effect->keyNum);
    m_effect = new envMapEffect(effect->texture, effect->model);
}

void EffectEntry::filterEffectLoad(u8** data) {
    bool invert = false;
    bool mono = false;
    FilterEffectData* effect = (FilterEffectData*)*data;
    *data += sizeof(FilterEffectData);
    LOAD_KEYS(data, effect->keyNum);
    switch (effect->type) {
    case 0:
        m_effect = new filterEffect();
        break;
    case 1:
        mono = true;
 // fall through
    case 2:
        if ((effect->flags & 1) == 1) {
            invert = true;
        }
        m_effect = new filterEffect(invert, mono);
        break;
    }
}
