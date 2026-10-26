#include <dolphin/types.h>

struct MemoEntry {
    u16 id;
    u16 pad;
    u32 trainerRnd;
    u32 rnd;
};

struct Memo {
    u16 count;
    u16 pad;
    MemoEntry entries[500];
};

extern "C" {
void* savedataGetStatus(void*, u16);
u32 HSD_Rand(void);
u32 pokemonBiosGetPokemonDataId(void*);
u32 pokemonBiosGetRnd(void*);
u32 pokemonBiosGetCatchTrainerRnd(void*);
}

static inline u32 memoGetRandom(u32 range) {
    u32 low = HSD_Rand();
    u32 high = HSD_Rand() << 16;
    return (high | low) % range;
}

static inline u16 memoGetCountInline(Memo* memo) {
    if (memo == 0) {
        memo = (Memo*)savedataGetStatus(0, 0xC);
    }
    return memo->count;
}

static inline void memoSetPokemonIDInline(Memo* memo, u16 id) {
    Memo* m = memo;
    if (m == 0) {
        m = (Memo*)savedataGetStatus(0, 0xC);
    }
    u16 count = m->count;
    u16 i;
    for (i = 0; i < count; i++) {
        if (((u32)m->entries[i].id & 0x3FFF) == (u16)id) {
            return;
        }
    }
    m->entries[count].id = id | 0x8000;
    m->entries[m->count].rnd = memoGetRandom(0xFFFFFFFF);
    m->count++;
}

extern "C" {

void memoGetScaleAngle(u16 id, f32* outScale, f32* outAngle) {
    f32 scale = 1.0f;
    switch (id) {
    case 0x15C:
        scale = 1.2f;
        break;
    case 0x26:
        scale = 0.6f;
        break;
    case 0x4B:
        scale = 0.8f;
        break;
    case 0x91:
        scale = 0.75f;
        break;
    case 0x12C:
        scale = 0.7f;
        break;
    case 0x8E:
        scale = 0.85f;
        break;
    case 0x197:
        scale = 0.65f;
        break;
    case 0x198:
        scale = 0.65f;
        break;
    case 0x1A:
        scale = 0.7f;
        break;
    case 0x6:
        scale = 0.7f;
        break;
    case 0xE2:
        scale = 0.75f;
        break;
    case 0xD9:
        scale = 0.75f;
        break;
    case 0x14B:
        scale = 0.78f;
        break;
    case 0x44:
        scale = 0.78f;
        break;
    case 0x136:
        scale = 0.75f;
        break;
    case 0x4A:
        scale = 0.8f;
        break;
    case 0x16B:
        scale = 0.8f;
        break;
    case 0x85:
        scale = 0.8f;
        break;
    case 0x92:
        scale = 0.6f;
        break;
    case 0x90:
        scale = 0.6f;
        break;
    case 0x65:
        scale = 1.2f;
        break;
    case 0xFA:
        scale = 0.65f;
        break;
    case 0x194:
        scale = 0.7f;
        break;
    case 0xF9:
        scale = 0.85f;
        break;
    case 0x135:
        scale = 0.75f;
        break;
    case 0x156:
        scale = 1.25f;
        break;
    case 0x14C:
        scale = 1.2f;
        break;
    case 0x6C:
        scale = 1.3f;
        break;
    case 0x5C:
        scale = 0.8f;
        break;
    case 0x57:
        scale = 1.2f;
        break;
    case 0x13A:
        scale = 1.18f;
        break;
    case 0x82:
        scale = 1.1f;
        break;
    case 0x8F:
        break;
    }
    if (outAngle != 0) {
        *outAngle = 0.2617994f;
    }
    if (outScale != 0) {
        *outScale = scale;
    }
}

void memoInitDebug(Memo* memo) {
    u16 id;
    if (memo == 0) {
        memo = (Memo*)savedataGetStatus(0, 0xC);
    }
    for (id = 1; id <= 0xFB; id++) {
        memoSetPokemonIDInline(0, id);
    }
    for (id = 0x115; id <= 0x19B; id++) {
        memoSetPokemonIDInline(0, id);
    }
}

u32 memoDataGetPokemonTrainerRndFromID(Memo* memo, u16 id) {
    u16 i;
    u16 count;
    Memo* m = memo;
    if (m == 0) {
        m = (Memo*)savedataGetStatus(0, 0xC);
    }
    count = memoGetCountInline(m);
    for (i = 0; i < count; i++) {
        if ((m->entries[i].id & 0x3FFF) == id) {
            return m->entries[i].trainerRnd;
        }
    }
    return 0;
}

u32 memoDataGetPokemonRndFromID(Memo* memo, u16 id) {
    u16 i;
    u16 count;
    Memo* m = memo;
    if (m == 0) {
        m = (Memo*)savedataGetStatus(0, 0xC);
    }
    count = memoGetCountInline(m);
    for (i = 0; i < count; i++) {
        if ((m->entries[i].id & 0x3FFF) == id) {
            return m->entries[i].rnd;
        }
    }
    return 0;
}

u16 memoDataGetPokemonID(Memo* memo, u16 index) {
    if (memo == 0) {
        memo = (Memo*)savedataGetStatus(0, 0xC);
    }
    if (memo->count != 0) {
        return memo->entries[index].id;
    }
    return 0;
}

u16 memoDataGetCount(Memo* memo) {
    if (memo == 0) {
        memo = (Memo*)savedataGetStatus(0, 0xC);
    }
    return memo->count;
}

u32 memoDataSetMemoFlag(Memo* memo) {
    u32 result = 0;
    u16 i;
    if (memo == 0) {
        memo = (Memo*)savedataGetStatus(0, 0xC);
    }
    for (i = 0; i < memo->count; i++) {
        if (memo->entries[i].id & 0x8000) {
            result = 1;
        }
        memo->entries[i].id &= 0x3FFF;
    }
    return result;
}

void memoDataSetPokemonID(Memo* memo, u16 id) {
    memoSetPokemonIDInline(memo, (u16)id);
}

void memoDataSet(Memo* memo, void* pokemon) {
    Memo* m = memo;
    unsigned short new_var;
    if (m == 0) {
        m = (Memo*)savedataGetStatus(0, 0xC);
    }
    u32 id = pokemonBiosGetPokemonDataId(pokemon);
    u16 count = m->count;
    u16 i;
    for (i = 0; i < count; i++) {
        new_var = ((u32)m->entries[i].id) & 0x3FFF;
        if (new_var == ((u16)id)) {
            return;
        }
    }
    m->entries[count].id = id | 0x8000;
    m->entries[m->count].rnd = pokemonBiosGetRnd(pokemon);
    m->entries[m->count].trainerRnd = pokemonBiosGetCatchTrainerRnd(pokemon);
    m->count++;
}

void memoInit(Memo* memo_in) {
    Memo* memo = memo_in;
    int i;
    if (memo == 0) {
        memo = (Memo*)savedataGetStatus(0, 0xC);
    }
    memo->count = 0;
    for (i = 0; i < 500; i++) {
        memo->entries[i].id = 0;
        memo->entries[i].rnd = memoGetRandom(0xFFFFFFFF);
    }
}

}
