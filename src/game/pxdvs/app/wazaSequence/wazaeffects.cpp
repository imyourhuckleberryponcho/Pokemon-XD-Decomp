#include <dolphin/types.h>
#include <game/gcdata.h>
#include <game/effects.h>
#include <game/wazaentry.h>

inline envMapEffect::envMapEffect(u32 texture, u32 texture2) {
    m_model = 0;
    m_texture = texture;
    m_texture2 = texture2;
    m_blend = 0.0f;
}

inline filterEffect::filterEffect() {
    m_target = 0;
    m_modulate = 0;
    m_color[3] = 0;
    m_color[2] = 0;
    m_color[1] = 0;
    m_color[0] = 0;
}

inline filterEffect::filterEffect(bool invert, bool mono) {
    m_target = 0;
    m_resetPE = invert;
    m_useSaved = 0;
    m_hasSaved = 0;
    u8 type = 2;
    if (mono) {
        type = 1;
    }
    m_modulate = type;
    m_color[2] = 0x7F;
    m_color[1] = 0x7F;
    m_color[0] = 0x7F;
    m_color[3] = invert ? 0 : 0xFF;
}

#define ALIGN32(x) (((u32)(x) + 0x1F) & ~0x1F)

#define LOAD_KEYS(data, num)          m_keyed = 1;                    m_keys = *(data);                 m_keyCount = (num);                 m_time = 0.0f;                    m_curKey = 0;                   *(data) += m_keyCount * 16;

struct _GSparticleBank;

class WazaSequence;

class SequenceEntry;

class EffectEntry {
public:
    void boneFillEffectLoad(u8** data);
    void blurEffectLoad(u8** data);
    void envMapEffectLoad(u8** data);
    void filterEffectLoad(u8** data);

    void* m_vtbl;
    SEQUENCE_ENTRY_MEMBERS
    EFFECT_ENTRY_MEMBERS(u8* m_keys)
};

class WazaSequence {
public:
    SequenceEntry* GetEntryFromID(u8 id);
};

struct BoneFillEffectData {
    gc_enum32(enumNullJointName) from;
    gc_enum32(enumNullJointName) to;
    gc_bef32 time;
    gc_be32 size;
    gc_ptr32(_GSparticleBank) bank;
    gc_be32 unk14;
};

struct BlurEffectData {
    gc_be32 keyNum;
    gc_be32 unk4;
    gc_be32 on;
};

struct EnvMapEffectData {
    gc_be32 texture;
    gc_be32 model;
    gc_be32 keyNum;
    gc_be32 unkC;
};

struct FilterEffectData {
    gc_bes32 type;
    gc_be32 keyNum;
    gc_be32 unk8;
    gc_bes32 flags;
};

void EffectEntry::boneFillEffectLoad(u8** data) {
    BoneFillEffectData* effect = (BoneFillEffectData*)*data;
    _GSparticleBank* bank = NULL;

    *data += sizeof(BoneFillEffectData);
    *data = (u8*)ALIGN32(*data);
    *data += ALIGN32(effect->size);
    if (unk09 != 0) {
        EffectEntry* parent = (EffectEntry*)seq->GetEntryFromID(unk09);
        if (parent->m_effect != NULL) {
            bank = (_GSparticleBank*)((u32*)parent->m_effect)[3];
        }
    } else {
        bank = effect->bank;
    }
    m_effect = new boneFillEffect(bank, (enumNullJointName)GC_BES32(effect->from), (enumNullJointName)GC_BES32(effect->to), effect->time);
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
    case 2:
        if ((effect->flags & 1) == 1) {
            invert = true;
        }
        m_effect = new filterEffect(invert, mono);
        break;
    }
}
