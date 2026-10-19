#include <dolphin/types.h>

#pragma dont_inline on

extern "C" void* memcpy(void*, const void*, u32);

struct Hero {
    u8 unk0[0x978];
    Hero& operator=(const Hero& o) {
        memcpy(this, &o, sizeof(Hero));
        return *this;
    }
};

struct Pokemon {
    u8 unk0[0xC4];
    Pokemon& operator=(const Pokemon& o) {
        memcpy(this, &o, sizeof(Pokemon));
        return *this;
    }
};

struct ToolentryTrainer {
    u16 dataID;
    u8 unk2[6];
    s32 order[6];
    s32 orderNum;
    s32 controllerType;
    u8 unk28[4];
    Hero entryHero;
    Hero hero;
};

struct ToolentryWork {
    u8 unk0[4];
    s32 mode;
    s32 type;
    u8 unkC[8];
    s32 versus;
};

struct ToolentryFaceData {
    u16 id;
    u8 unk2[2];
    u32 bigFace[2];
    u32 smallFace[2];
};

extern "C" {
void* GSmemAllocAlign(u32, u32);
void GSmemFree(void*);
ToolentryWork* menuCBBios_WorkContext(void);
void* menuCBBios_GetTrainerImmediately(s32);
s32 menuCBTrainerBios_GetPlayerID(void*);
s32 menuCBTrainerBios_GetHomePlace(void*);
s32 menuCBBios_ParticipationPokemonMax(void);
Pokemon* heroBiosGetPokemonPtr(Hero*, u16);
void heroInit(Hero*);
void pokemonInit(Pokemon*);
u8 pokemonCheckValid(Pokemon*);
void* savedataGetStatus(s32, s32);
s32 gamedataGetStatus(s32, s32);
void pokemonCreate(Pokemon*, u16, s32, s32);
void* GSmsgGetGSchar(u32);
void pokemonSetCatchStatus(Pokemon*, s32, s32, s32, s32, s32, void*);
void pokemonAllKaihuku(Pokemon*);
u16 fightTrainerDB_GetPkxDataId(u16);
}

extern ToolentryFaceData* trainer_face_data;
extern u32* trainer_face_data_number;

static void* _toolentryTaisen;
static Pokemon* _toolentryDebugPokemon;
static s32 _toolentryDebugPokemonNum = 0x18;

static void* _toolentryAlloc(u32 size) {
    return GSmemAllocAlign((size + 0x1F) & ~0x1F, 0x20);
}

static void _toolentryFree(void* p) {
    GSmemFree(p);
}

static ToolentryWork* _toolentryGetCBWork(void) {
    return menuCBBios_WorkContext();
}

static Hero* _toolentryTaisenGetHeroPtr(s32 player) {
    return &((ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player))->hero;
}

static Hero* _toolentryTaisenGetEntryHeroPtr(s32 player) {
    return &((ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player))->entryHero;
}

static Pokemon* _toolentryTaisenGetPokemonPtr(s32 player, s32 slot) {
    return heroBiosGetPokemonPtr(&((ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player))->hero, slot);
}

static Pokemon* _toolentryTaisenGetEntryPokemonPtr(s32 player, s32 slot) {
    return heroBiosGetPokemonPtr(&((ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player))->entryHero, slot);
}

static u8 _toolentryTaisenGetPokemonFlag(s32 player, s32 slot) {
    if (pokemonCheckValid(heroBiosGetPokemonPtr(&((ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player))->hero, slot))) {
        return 1;
    }
    return 0;
}

extern "C" {

void toolentryTaisenInit(void) {
    s32 j;
    s32 i;
    for (i = 0; i < 4; i++) {
        heroInit(_toolentryTaisenGetHeroPtr(i));
        for (j = 0; j < 6; j++) {
            pokemonInit(_toolentryTaisenGetPokemonPtr(i, j));
        }
    }
    for (i = 0; i < 4; i++) {
        heroInit(_toolentryTaisenGetEntryHeroPtr(i));
        for (j = 0; j < 6; j++) {
            pokemonInit(_toolentryTaisenGetEntryPokemonPtr(i, j));
        }
    }
}

s32 toolentryTaisenSetPokemon(Pokemon* src, s32 player, s32 slot) {
    Pokemon* dst = _toolentryTaisenGetPokemonPtr(player, slot);
    if (dst != 0) {
        memcpy(dst, src, sizeof(Pokemon));
        return 1;
    }
    return 0;
}

s32 toolentryTaisenSetHeroFromSaveData(s32 player) {
    void* save = savedataGetStatus(0, 2);
    Hero* hero = _toolentryTaisenGetHeroPtr(player);
    if (save != 0) {
        memcpy(hero, save, sizeof(Hero));
        return 1;
    }
    return 0;
}

u8 toolentryTaisenGetPokemonFlag(s32 player, s32 slot) {
    return _toolentryTaisenGetPokemonFlag(player, slot);
}

s32 toolentryTaisenGetBattleType(void) {
    return _toolentryGetCBWork()->type;
}

s32 toolentryTaisenGetEntryPlayerNum(void) {
    s32 type = toolentryTaisenGetBattleType();
    s32 n = 2;
    switch (type) {
    case 0:
    case 1:
        n = 2;
        break;
    case 2:
        n = 4;
        break;
    }
    return n;
}

s32 toolentryTaisenGetBattlePlayerID(s32 player) {
    return menuCBTrainerBios_GetPlayerID(menuCBBios_GetTrainerImmediately(player));
}

u16 toolentryTaisenGetHomePlace(s32 player) {
    return menuCBTrainerBios_GetHomePlace(menuCBBios_GetTrainerImmediately(player));
}

s32 toolentryTaisenGetBattleVersus(void) {
    return _toolentryGetCBWork()->versus;
}

s32 toolentryTaisenGetBattleMode(void) {
    return _toolentryGetCBWork()->mode;
}

Pokemon* toolentryTaisenGetPokemonPtr(s32 player, s32 slot) {
    return _toolentryTaisenGetPokemonPtr(player, slot);
}

Pokemon* toolentryTaisenGetEntryPokemonPtr(s32 player, s32 slot) {
    return _toolentryTaisenGetEntryPokemonPtr(player, slot);
}

Hero* toolentryTaisenGetHeroPtr(s32 player) {
    return _toolentryTaisenGetHeroPtr(player);
}

Hero* toolentryTaisenGetEntryHeroPtr(s32 player) {
    return _toolentryTaisenGetEntryHeroPtr(player);
}

u16 toolentryTaisenGetPokemonNum(s32 player) {
    u16 count = 0;
    s32 i;
    for (i = 0; i < 6; i++) {
        if (toolentryTaisenGetPokemonFlag(player, i)) {
            count++;
        }
    }
    return count;
}

u16 toolentryTaisenGetEntryPokemonNum(s32 player) {
    u16 max = menuCBBios_ParticipationPokemonMax();
    u16 num = toolentryTaisenGetPokemonNum(player);
    return num < max ? num : max;
}

void toolentryCopyHero(void) {
    Hero* src;
    s32 i;
    Hero* dst;
    for (i = 0; i < 4; i++) {
        src = toolentryTaisenGetHeroPtr(i);
        dst = toolentryTaisenGetEntryHeroPtr(i);
        if (src != 0 && dst != 0) {
            *dst = *src;
        }
    }
}

void toolentryTaisenInitPokemonOrder(s32 player) {
    ToolentryTrainer* t = (ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player);
    s32 i;
    t->orderNum = 0;
    for (i = 0; i < 6; i++) {
        t->order[i] = -1;
    }
}

s32 toolentryTaisenSetEtnryPokemonOrder(s32 player, s32 value) {
    ToolentryTrainer* t = (ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player);
    s32 count = t->orderNum;
    s32 i;
    if (t->orderNum >= (u16)toolentryTaisenGetEntryPokemonNum(player)) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        if (t->order[i] == value) {
            return -1;
        }
    }
    t->order[count] = value;
    t->orderNum = t->orderNum + 1;
    return count;
}

s32 toolentryTaisenSetEtnryPokemonOrderGBA(s32 player, s32 n, s32* src) {
    ToolentryTrainer* t = (ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player);
    s32 i;
    for (i = 0; i < n; i++) {
        t->order[i] = src[i];
    }
    t->orderNum = i;
    return i;
}

s32 toolentryTaisenDeleteEtnryPokemonOrder(s32 player) {
    ToolentryTrainer* t = (ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player);
    s32 idx = t->orderNum - 1;
    if (idx < 0 || idx > 6) {
        return 0;
    }
    t->order[idx] = -1;
    t->orderNum = t->orderNum - 1;
    return t->orderNum;
}

s32 toolentryTaisengetEtnryPokemonOrderNum(s32 player) {
    return ((ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player))->orderNum;
}

s32 toolentryTaisenGetEtnryPokemonOrder(s32 player, s32 idx) {
    ToolentryTrainer* t = (ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player);
    s32 v = t->order[idx];
    return v;
}

void toolentryTaisenFreePokemonData(void);

void toolentryTaisenCreateBattlePokemonData(void) {
    toolentryTaisenFreePokemonData();
    _toolentryTaisen = _toolentryAlloc(0x70);
}

void toolentryTaisenFreePokemonData(void) {
    if (_toolentryTaisen != 0) {
        _toolentryFree(_toolentryTaisen);
        _toolentryTaisen = 0;
    }
}

void toolentryTaisenEntryPokemon(s32 player) {
    s32 num = toolentryTaisenGetEntryPokemonNum(player);
    Hero* entry = _toolentryTaisenGetEntryHeroPtr(player);
    s32 i;
    Pokemon* src;
    s32 j;
    *entry = *_toolentryTaisenGetHeroPtr(player);
    for (i = 0; i < 6; i++) {
        pokemonInit(_toolentryTaisenGetEntryPokemonPtr(player, i));
        s32 order = toolentryTaisenGetEtnryPokemonOrder(player, i);
        if (order == 0xF || order == -1) {
            if (num > i) {
                num = i;
            }
        } else {
            src = _toolentryTaisenGetPokemonPtr(player, i);
            Pokemon* dst = _toolentryTaisenGetEntryPokemonPtr(player, i);
            if (dst != 0 && src != 0) {
                *dst = *src;
            }
        }
    }
    for (j = 0; j < num; j++) {
        Pokemon* src = _toolentryTaisenGetPokemonPtr(player, toolentryTaisenGetEtnryPokemonOrder(player, j));
        Pokemon* dst = _toolentryTaisenGetEntryPokemonPtr(player, j);
        if (dst != 0 && src != 0) {
            *dst = *src;
        }
    }
}

u16 toolentryTaisenGetTrainerDataID(s32 player);

}

static s32 _toolentryTrainerFaceIDGet(u32 id);

extern "C" {

u32 toolentryGetTrainerBicFaceResID(s32 player, s32 flag) {
    u16 id = toolentryTaisenGetTrainerDataID(player);
    if (id == 0) {
        return 0;
    }
    u32 idx = _toolentryTrainerFaceIDGet(fightTrainerDB_GetPkxDataId(id));
    ToolentryFaceData* d = &trainer_face_data[idx];
    if (flag == 0) {
        u32 v = d->bigFace[0];
        return v ? v : 0x21BF1200;
    }
    u32 v = d->bigFace[1];
    return v ? v : 0x21E81200;
}

u32 toolentryGetTrainerSamllFaceResID(s32 player, s32 flag) {
    u16 id = toolentryTaisenGetTrainerDataID(player);
    if (id == 0) {
        return 0;
    }
    u32 idx = _toolentryTrainerFaceIDGet(fightTrainerDB_GetPkxDataId(id));
    ToolentryFaceData* d = &trainer_face_data[idx];
    if (flag == 0) {
        u32 v = d->smallFace[0];
        return v ? v : 0x21D91200;
    }
    u32 v = d->smallFace[1];
    return v ? v : 0x21F31200;
}

s32 toolentryTaisenGetControlerType(s32 player) {
    return ((ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player))->controllerType;
}

u16 toolentryTaisenGetTrainerDataID(s32 player) {
    return ((ToolentryTrainer*)menuCBBios_GetTrainerImmediately(player))->dataID;
}

}

static Pokemon* _toolentryDebugGetPokemonPtr(s32 i) {
    return _toolentryDebugPokemon + i;
}

extern "C" {

void toolentryCreateDebugPokemon(void) {
    Pokemon* p;
    s32 i;
    _toolentryDebugPokemon = 0;
    _toolentryDebugPokemon = (Pokemon*)_toolentryAlloc(_toolentryDebugPokemonNum * sizeof(Pokemon));
    p = _toolentryDebugPokemon;
    for (i = 0; i < _toolentryDebugPokemonNum; i++) {
        pokemonCreate(p, (u16)(i + 1), 10, gamedataGetStatus(0, 1));
        void* name = GSmsgGetGSchar(i + 1);
        pokemonSetCatchStatus(p, 0, 8, 1, 0, 0, name);
        pokemonAllKaihuku(p);
        p++;
    }
}

void toolentryFreeDebugPokemon(void) {
    if (_toolentryDebugPokemon != 0) {
        _toolentryFree(_toolentryDebugPokemon);
        _toolentryDebugPokemon = 0;
    }
}

void toolentryDebugPokemonCreate(void) {
    s32 j;
    s32 i;
    s32 idx;
    toolentryCreateDebugPokemon();
    toolentryTaisenCreateBattlePokemonData();
    toolentryTaisenInit();
    idx = 0;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            toolentryTaisenSetHeroFromSaveData(i);
        } else {
            for (j = 0; j < 6; j++) {
                toolentryTaisenSetPokemon(_toolentryDebugGetPokemonPtr(idx), i, j);
                idx++;
            }
        }
    }
    toolentryFreeDebugPokemon();
}

void toolentryDebugPokemonDelete(void) {
    toolentryTaisenFreePokemonData();
}

}

static s32 _toolentryTrainerFaceIDGet(u32 id) {
    s32 i;
    for (i = 0; i < *trainer_face_data_number; i++) {
        u16 faceID = trainer_face_data[i].id;
        if (faceID == (u16)id) {
            return i;
        }
    }
    return 1;
}
