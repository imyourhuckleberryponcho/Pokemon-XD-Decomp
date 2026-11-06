#ifndef GAME_WAZAENTRY_H
#define GAME_WAZAENTRY_H

struct _GSmodel;
struct GSparticleBank;
struct GSparticleGenerator;
struct SndEmitter;
struct GSeffect;
struct EffectKey;
class WazaSequence;
class SequenceEntry;
enum enumSequenceEntryDataType { enumSequenceEntryDataType_draft_dummy };

#define SEQUENCE_ENTRY_MEMBERS                                                                                 \
    u8 unk04;                                                               \
    u8 unk05;                                                               \
    u8 unk06;                                                               \
    u8 unk07;                                                               \
    u8 unk08;                                                               \
    u8 unk09;                                                               \
    u16 unk0A;                                                               \
    enumSequenceEntryDataType type;                                                               \
    u8 unk10;                                                               \
    u8 unk11;                                                               \
    u16 unk12;                                                               \
    u8* params;                                                               \
    s32 m_state;                                                               \
    f32 m_start;                                         \
    f32 m_nextTime;                                                               \
    SequenceEntry* m_next;                              \
    s32 unk28;                                                               \
    WazaSequence* seq;

#define EVENT_ENTRY_MEMBERS                                                             \
    u32 unk30;

#define CAMERA_ENTRY_MEMBERS                                                             \
    s32 unk30;                                                               \
    f32 unk34;

#define LENSFLARE_ENTRY_MEMBERS                                                             \
    u32 unk30;                                                               \
    f32 unk34;                                                               \
    s32 unk38;

#define MODEL_ENTRY_MEMBERS                                                             \
    s32 unk30;                                                               \
    s32 unk34;                                                               \
    s32 unk38;                                                               \
    s32 unk3C;                                                               \
    s32 unk40;                                                               \
    s32 unk44;                                                               \
    s16 unk48;                                                               \
    s8 unk4A;                                                               \
    s8 unk4B;                                                               \
    _GSmodel* model;

#define PARTICLE_ENTRY_MEMBERS                                                             \
    s32 unk30;                                                               \
    s32 unk34;                                                               \
    GSparticleBank* bank;                                                               \
    GSparticleGenerator* generator;                                                               \
    s32 unk40;

#define SOUND_ENTRY_MEMBERS                                                             \
    s32 unk30;                                                               \
    s16 unk34;                                                               \
    s8 unk36;                                                               \
    u8 unk37;                                                               \
    f32 unk38;                                                               \
    SndEmitter* emitter;

#define EFFECT_ENTRY_MEMBERS(x34)                                                             \
    GSeffect* m_effect;                                                               \
    x34;                                                               \
    f32 m_time;                                                               \
    u8 m_keyCount;                                                               \
    u8 m_curKey;                                                               \
    u8 unk3E[2];                                                               \
    u8 m_keyed;                                                               \
    u8 m_type;                                                               \
    u8 unk42[2];

#define WAZA_SEQUENCE_MEMBERS(OwnerT)                                                                         \
    f32 m_time;                                                                 \
    f32 m_duration;                                                                 \
    u32 m_flags;                                                                 \
    u16 m_wazaID;                                                                 \
    u8 m_kind;                                                                 \
    u8 m_error;                                                                 \
    u16 m_resID;                                                                 \
    u8 m_numEntries;                                                                 \
    u8 m_section;                                                                 \
    u8 m_active;                                                                 \
    u8 m_started;                                                                 \
    u8 m_partKind;                                                                 \
    u8 m_finished;                                                                 \
    f32 m_distortion;                                                                 \
    u32 m_camera;                                                                 \
    SequenceEntry* m_entries;                                                                 \
    OwnerT* m_owner;                                                                 \
    WazaSequence* m_next;                                                                 \
    WazaSequence* m_prev;

#endif
