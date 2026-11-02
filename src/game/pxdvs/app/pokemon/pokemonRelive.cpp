#include <dolphin/types.h>
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
struct DeckDarkPokemon;
struct GSparticleBank;
struct GSparticleGenerator;
struct GSthread;
struct Hero;
struct MenuPtWorkSound;
struct Pokemon;
struct Sequence;
struct SequenceWaza;
struct Vec;
struct WazaSequence;

struct PreReliveParameter {
    u32 unk0;
    s32 index;
};

static PreReliveParameter pParameter;

extern "C" {

extern "C++" {
struct DeckDarkPokemon {
    u8 _draft[1];
    u16 getBonusExp() const;
    static DeckDarkPokemon* getDeckDarkPokemonObj(unsigned long);
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
struct Hero {
    u8 _draft[1];
};
struct MenuPtWorkSound {
    u8 _draft[1];
};
struct Pokemon {
    u8 _draft[1];
    u16 getPokemonDataId() const;
};
struct Sequence {
    u8 _draft[1];
};
struct SequenceWaza {
    u16 id;
    u16 kind;
};
struct Vec {
    f32 x, y, z;
};
struct WazaSequence {
    u8 _draft[1];
};

extern "C" {
s32 GSfloorGetCurrentFloorGroupID(void);
u8 GSfloorPop(void);
u8 GSfloorPush(u32 id);
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* bank, s32 index, s32);
s32 GSparticleDestroyGenerator(s32, s32);
void GSparticleSetGeneratorPosition(GSparticleGenerator* gen, Vec* pos);
void* GSresGetResource(u32 grp, u32 id);
void GSthreadClose(GSthread*);
void* GSthreadCreate(s32, s32, s32, s32, s32, void (*)(void));
u8 GSthreadIsRunning(GSthread*);
void GSthreadSwitch(void);
s32 Sequence_DoAnimation(Sequence*, u8);
void Sequence_Free(Sequence*);
s32 Sequence_GetPosition(Sequence*, Vec*);
s32 Sequence_GetRotation(Sequence*, Vec*);
s32 Sequence_GetScale(Sequence*, Vec*);
WazaSequence* Sequence_GetWaza(Sequence* sequence, u16 wzxID, u32 kind);
Sequence* Sequence_LoadPokemon(u16, u32, u32);
void* Sequence_LoadWaza(Sequence* sequence, u16 wazaID, u8 kind, s32);
s32 Sequence_SetPosition(Sequence*, Vec*);
s32 Sequence_SetRotation(Sequence*, Vec*);
s32 Sequence_SetScale(Sequence*, Vec*);
s32 Sequence_SetVisibility(Sequence*, s32);
void WazaSequence_Free(WazaSequence* sequence);
bool WazaSequence_IsActive(WazaSequence* sequence);
void WazaSequence_Start(WazaSequence* sequence, s32);
static void __sinit_pokemonRelive_cpp();
void darkPokemonBiosSetReliveFlag(u16 id, s32 flag);
s32 evolutionWazaLearn(s32, u16, u8*, s32, void*, s32);
BOOL exribbonSetNarionalRibbon(Pokemon* pokemon);
void fadeCheck(s32);
void fadeSet(s32 type, f32 time);
s32 fadeSetToBlackInIfBlack(f32);
s32 fadeSetToBlackOutIfNotBlack(f32);
u32 floorGetCurrentGroupID();
void floorSetFadeScript(u32 out, u32 in);
void floorWaitForChange(void);
u32 heroGetStatus(Hero* hero, u32 selector, u16 index);
BOOL loadSequence(Sequence** out, Pokemon* pokemon, SequenceWaza* wazas, s32 num);
s32 menuHologramReloadDatas();
s32 menuHologramUnloadDatas();
s8 menuModelGetPokemonAnimationIndexByPointer(Pokemon*);
s32 menuModelReSetScale();
s32 menuModelSetScale(f32);
s32 menuNameEntryOpenNoFade(s32 mode, s32 param);
s32 menuPokemonOpen(s32, s32, s32);
s32 menuPokemonStatusOpenWazaLearn(Pokemon* pokemon, u16 sel);
s8 menuSubOpenYesNoField(void);
void msgctrlSetValue(s32 id, u32 value);
void pokemonAllKaihuku(Pokemon* pokemon);
u16 pokemonBiosGetDarkpokemonDataId(Pokemon* poke);
u16 pokemonBiosGetFriend(Pokemon* poke);
u8 pokemonBiosGetLevel(Pokemon* poke);
char* pokemonBiosGetNicknamePtr(Pokemon* poke);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon* poke, u16 wazaNum);
u32 pokemonBiosGetPoolExp(Pokemon* poke);
u32 pokemonBiosGetPoolFriend(Pokemon* poke);
u32 pokemonBiosGetRnd(Pokemon* poke);
void pokemonBiosSetExp(Pokemon* poke, u32 data);
void pokemonBiosSetFriend(Pokemon* poke, u16 data);
void pokemonBiosSetPoolFriend(Pokemon* poke, u16 data);
bool pokemonCheckValid(Pokemon* pokemon);
s32 pokemonEvolutionAll(Pokemon*, u16, u16, s32*, s32, s32, s32, s32);
u16 pokemonEvolutionCheck(Pokemon*, s32, s32, u16*, s32*);
void pokemonGetFriendFormPokemonFriendFilterId(Pokemon* pokemon, u16 itemDataId, u16 filterId);
u32 pokemonGetLevelToExp(Pokemon* pokemon, u8 level);
u16 pokemonGetOboeWazaDataId(Pokemon* pokemon, u8 level, u8* cursor);
u16 pokemonGetSoubiItemSoubiDataId(Pokemon* pokemon);
u32 pokemonGetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index);
void pokemonInitJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
bool pokemonIsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
void pokemonResetBasisStatus(Pokemon* pokemon);
s8 pokemonSearchWazaDataId(Pokemon* pokemon, u16 waza);
void pokemonSetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index, u32 value);
void pokemonWazaCreate(Pokemon* pokemon, u16 wazaNum, u16 waza);
void preReliveDisplayHokoraParticle();
void preReliveMain(u8 p0);
void preReliveSetParameter(s32, s32, u8);
void reliveMain();
s32 scriptGetDarkPointZeroPokemonNum();
void soundOpenPlay(s32, s32, s32);
void soundOpenPlayME(u32 id, u32, u8 volume);
f32 timeGetLastFrameSec(void);
void waitTime(f32 time);
void winMsgCloseField(bool flag);
void winMsgCloseLevelUpStatus(bool flag);
s32 winMsgOpenField(void* msg, bool a, bool b);
s32 winMsgOpenLevelUpStatus(void* msg, bool a);
}
extern "C++" {
static s8 _cbWazaForget(Pokemon* p0, unsigned short p1, long p2);
static u8 _expRecover(Pokemon* p0, unsigned long p1);
static void _preReliveDisplayHokoraParticleThreadFunc();
void menuPtRestoreSound(MenuPtWorkSound* s);
void menuPtStopSound(MenuPtWorkSound* s);
static s32 reliveCeremonyAll(long p0, Pokemon* p1, unsigned long p2);
void reliveCeremonyFromHologram(Pokemon* p0, unsigned long p1);
}
static Pokemon* mParameter;
static s32 lbl_804EB994;
static s32 keepRelivePatternIsHologram;
static s32 hokoraParticleGen;
static u8 isHokoraParticleLoaded;
static SequenceWaza normalReliveWazaSeqTbl[2] = {{0x4D, 4}, {0x7A, 4}};
static SequenceWaza hologramReliveWazaSeqTbl[1] = {{0x4D, 4}};
static SequenceWaza hologramPigeonReliveWazaSeqTbl[1] = {{0x13B, 4}};
static SequenceWaza noWazaSeqTbl = {0x7A, 4};

extern "C" {
void fn_80233AB4();
}

static s8 _cbWazaForget(Pokemon* p0, unsigned short p1, long p2) {
    Sequence *sp8;
    WazaSequence *temp_r3;
    f32 var_f30;
    s32 var_r30;

    fadeSetToBlackOutIfNotBlack(0.5f);
    fadeCheck(1);
    if ((s32) keepRelivePatternIsHologram != 0) {
        menuHologramUnloadDatas();
    }
    var_r30 = menuPokemonStatusOpenWazaLearn((Pokemon*)(p0), p1);
    if (var_r30 >= 4) {
        var_r30 = -1;
    }
    if ((s32) keepRelivePatternIsHologram != 0) {
        menuHologramReloadDatas();
        fadeSetToBlackInIfBlack(0.5f);
        fadeCheck(1);
    } else {
        loadSequence((Sequence**)(&sp8), (Pokemon*)(p0), (SequenceWaza*)(&noWazaSeqTbl), 1);
        fadeSetToBlackInIfBlack(0.5f);
        fadeSet(2, 0.5f);
        Sequence_SetVisibility(sp8, 1);
        temp_r3 = Sequence_GetWaza((Sequence*)(sp8), M2C_FIELD(&noWazaSeqTbl, u16 *, 0), (u32) M2C_FIELD(&noWazaSeqTbl, u16 *, 2));
        if (temp_r3 != NULL) {
            WazaSequence_Start((WazaSequence*)(temp_r3), 1);
            if (((Pokemon*)(p0))->getPokemonDataId() == 0x15C) {
                Sequence_DoAnimation(sp8, menuModelGetPokemonAnimationIndexByPointer(p0));
            }
            var_f30 = 0.0f;
            while (WazaSequence_IsActive((WazaSequence*)(temp_r3)) != 0) {
                GSthreadSwitch();
                var_f30 += timeGetLastFrameSec();
                if (!(!(var_f30 > 4.0f))) {
                    break;
                }
            }
            WazaSequence_Free((WazaSequence*)(temp_r3));
        }
        if (((Pokemon*)(p0))->getPokemonDataId() == 0x15C) {
            Sequence_DoAnimation(sp8, menuModelGetPokemonAnimationIndexByPointer(p0));
        }
    }
    return (s8) var_r30;
}
}

extern "C++" {
#pragma peephole off
static inline void _preReliveDestroyHokoraParticle() {
    if (isHokoraParticleLoaded == 1) {
        GSparticleDestroyGenerator(hokoraParticleGen, 1);
        hokoraParticleGen = 0;
        isHokoraParticleLoaded = 0;
    }
}
#pragma peephole reset

static void _preReliveDisplayHokoraParticleThreadFunc() {
    Vec pos;
    pos.x = 0.0f;
    pos.y = 7.0f;
    pos.z = 0.0f;

    if (isHokoraParticleLoaded == 1) {
        _preReliveDestroyHokoraParticle();
    }
    hokoraParticleGen = (s32)GSparticleCreateGenerator((GSparticleBank*)GSresGetResource(floorGetCurrentGroupID(), 0x0FAE1400), 0, 0);
    GSparticleSetGeneratorPosition((GSparticleGenerator*)hokoraParticleGen, &pos);
    isHokoraParticleLoaded = 1;
    soundOpenPlay(0x597, 0, 0x7F);
    waitTime(4.0f);
    _preReliveDestroyHokoraParticle();
    lbl_804EB994 = NULL;
}
}

extern "C" {
void preReliveDisplayHokoraParticle() {
    if (((u16)scriptGetDarkPointZeroPokemonNum() != 0) && ((u8) isHokoraParticleLoaded == 0)) {
        lbl_804EB994 = (long)(GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (void (*)(void))(_preReliveDisplayHokoraParticleThreadFunc)));
    }
}
}

extern "C++" {
struct ReliveLevelUpStatus {
    u8 mode;
    u8 pad;
    s16 hp;
    s16 attack;
    s16 defense;
    s16 speed;
    s16 spAttack;
    s16 spDefense;
};

static u8 _expRecover(Pokemon* pokemon, unsigned long gainExp) {
    u8 slot;
    u32 next;
    ReliveLevelUpStatus gain;
    ReliveLevelUpStatus status;
    s16 attack;
    s16 defense;
    u8 level;
    s16 spAttack;
    s16 spDefense;
    s16 speed;
    s16 hp;
    u8 newLevel;
    u8 levelUp;
    u32 exp;
    u8 wazaIndex;
    u16 waza;
    u16 item;

    levelUp = 0;
    wazaIndex = 0;
    pokemonGetStatus(pokemon, 0, 0x7A, 0);
    for (;;) {
        if (gainExp == 0) {
            pokemonSetStatus(pokemon, 0, 0xC6, 0, gainExp);
            break;
        }
        level = (u8)pokemonGetStatus(pokemon, 0, 0x7A, 0);
        if (level >= 100) {
            break;
        }
        exp = pokemonGetStatus(pokemon, 0, 0x79, 0);
        next = pokemonGetLevelToExp(pokemon, level + 1);
        hp = (s16)pokemonGetStatus(pokemon, 0, 0x87, 0);
        attack = (s16)pokemonGetStatus(pokemon, 0, 0x88, 0);
        defense = (s16)pokemonGetStatus(pokemon, 0, 0x89, 0);
        spAttack = (s16)pokemonGetStatus(pokemon, 0, 0x8A, 0);
        spDefense = (s16)pokemonGetStatus(pokemon, 0, 0x8B, 0);
        speed = (s16)pokemonGetStatus(pokemon, 0, 0x8C, 0);
        exp += gainExp;
        if (exp >= next) {
            gainExp = exp - next;
            levelUp = 1;
            pokemonBiosSetExp(pokemon, next);
            pokemonResetBasisStatus(pokemon);
            item = pokemonGetSoubiItemSoubiDataId(pokemon);
            pokemonGetFriendFormPokemonFriendFilterId(pokemon, item, 0);
            newLevel = pokemonBiosGetLevel(pokemon);
            soundOpenPlayME(0x3C7, 0, 0xFF);
            msgctrlSetValue(0x2F, (u8)newLevel);
            winMsgOpenField((void*)0xC367, 1, 0);
            status.hp = (s16)pokemonGetStatus(pokemon, 0, 0x87, 0);
            status.attack = (s16)pokemonGetStatus(pokemon, 0, 0x88, 0);
            status.defense = (s16)pokemonGetStatus(pokemon, 0, 0x89, 0);
            status.spAttack = (s16)pokemonGetStatus(pokemon, 0, 0x8A, 0);
            status.spDefense = (s16)pokemonGetStatus(pokemon, 0, 0x8B, 0);
            status.speed = (s16)pokemonGetStatus(pokemon, 0, 0x8C, 0);
            gain.hp = status.hp - hp;
            gain.attack = status.attack - attack;
            gain.defense = status.defense - defense;
            gain.spAttack = status.spAttack - spAttack;
            gain.spDefense = status.spDefense - spDefense;
            gain.speed = status.speed - speed;
            gain.mode = 1;
            winMsgOpenLevelUpStatus(&gain, 1);
            status.mode = 0;
            winMsgOpenLevelUpStatus(&status, 1);
            winMsgCloseLevelUpStatus(1);
            wazaIndex = 0;
            while ((waza = pokemonGetOboeWazaDataId(pokemon, newLevel, &wazaIndex)) != 0) {
                if (pokemonSearchWazaDataId(pokemon, waza) == -1 &&
                    evolutionWazaLearn((s32)pokemon, waza, &slot, 0, (void*)_cbWazaForget, 0) != 0) {
                    pokemonWazaCreate(pokemon, slot, waza);
                }
                wazaIndex++;
            }
        } else {
            gainExp = 0;
            pokemonSetStatus(pokemon, 0, 0x79, 0, exp);
        }
    }
    return levelUp;
}
}

extern "C++" {
#pragma push
static inline void reliveShowPokemon(Pokemon* pokemon) {
    Sequence* seq;
    loadSequence(&seq, pokemon, &noWazaSeqTbl, 1);
    fadeSetToBlackInIfBlack(0.5f);
    fadeSet(2, 0.5f);
    Sequence_SetVisibility(seq, 1);
    WazaSequence* waza = Sequence_GetWaza(seq, noWazaSeqTbl.id, noWazaSeqTbl.kind);
    if (waza != NULL) {
        WazaSequence_Start(waza, 1);
        if (pokemon->getPokemonDataId() == 0x15C) {
            Sequence_DoAnimation(seq, menuModelGetPokemonAnimationIndexByPointer(pokemon));
        }
        f32 t = 0.0f;
        while (WazaSequence_IsActive(waza)) {
            GSthreadSwitch();
            t += timeGetLastFrameSec();
            if (t > 4.0f) {
                break;
            }
        }
        WazaSequence_Free(waza);
    }
    if (pokemon->getPokemonDataId() == 0x15C) {
        Sequence_DoAnimation(seq, menuModelGetPokemonAnimationIndexByPointer(pokemon));
    }
}

static inline bool reliveStartNormal(Pokemon* pokemon) {
    Sequence* seq0;
    s32 i;
    if (pokemonCheckValid(pokemon) != 1) {
        return false;
    }
    bool ok = loadSequence(&seq0, pokemon, normalReliveWazaSeqTbl, 2);
    if (ok == 1) {
        fadeSet(2, 0.5f);
        Sequence_SetVisibility(seq0, 1);
        for (i = 0; i < 2; i++) {
            WazaSequence* waza = Sequence_GetWaza(seq0, normalReliveWazaSeqTbl[i].id, normalReliveWazaSeqTbl[i].kind);
            if (waza != NULL) {
                WazaSequence_Start(waza, 1);
                if (pokemon->getPokemonDataId() == 0x15C) {
                    Sequence_DoAnimation(seq0, menuModelGetPokemonAnimationIndexByPointer(pokemon));
                }
                f32 t = 0.0f;
                while (WazaSequence_IsActive(waza)) {
                    GSthreadSwitch();
                    t += timeGetLastFrameSec();
                    if (t > 4.0f) {
                        break;
                    }
                }
                WazaSequence_Free(waza);
            }
        }
        if (pokemon->getPokemonDataId() == 0x15C) {
            Sequence_DoAnimation(seq0, menuModelGetPokemonAnimationIndexByPointer(pokemon));
        }
        return true;
    }
    return false;
}

static s32 reliveCeremonyAll(long mode, Pokemon* pokemon, unsigned long p2) {
    WazaSequence* waza;
    s32 pokemon_c = (s32)pokemon;
    Sequence* result;
    u16 evoLevel;
    s32 evoParam;
    u16 oldWaza[4];
    u16 darkId;
    s32 newCount;

    keepRelivePatternIsHologram = 0;
    result = NULL;
    switch (mode) {
    case 0:
        if (!reliveStartNormal(pokemon)) {
            return 0;
        }
        break;
    case 1: {
        keepRelivePatternIsHologram = 1;
        if (pokemon->getPokemonDataId() == 0xF9) {
            Sequence_LoadWaza((Sequence*)p2, 0x103, 4, 0);
            bool flag = (s32)pokemonGetStatus(pokemon, 0, 0xC1, 0) != 0;
            Sequence* newSeq = Sequence_LoadPokemon(0xF9, pokemonBiosGetRnd(pokemon), flag);
            Sequence_LoadWaza(newSeq, 0x104, 4, 0);
            Vec scale;
            Vec rot;
            Vec pos;
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = 0.0f;
            rot.x = 0.0f;
            rot.y = 0.0f;
            rot.z = 0.0f;
            scale.x = 1.0f;
            scale.y = 1.0f;
            scale.z = 1.0f;
            Sequence_GetPosition((Sequence*)p2, &pos);
            Sequence_GetRotation((Sequence*)p2, &rot);
            Sequence_GetScale((Sequence*)p2, &scale);
            Sequence_SetPosition(newSeq, &pos);
            Sequence_SetRotation(newSeq, &rot);
            Sequence_SetScale(newSeq, &scale);
            WazaSequence* waza0 = Sequence_GetWaza((Sequence*)p2, 0x103, 4);
            WazaSequence* waza1 = Sequence_GetWaza(newSeq, 0x104, 4);
            WazaSequence_Start(waza0, 0);
            WazaSequence_Start(waza1, 0);
            f32 t = 0.0f;
            while (WazaSequence_IsActive(waza0) || WazaSequence_IsActive(waza1)) {
                GSthreadSwitch();
                t += timeGetLastFrameSec();
            }
            WazaSequence_Free(waza0);
            WazaSequence_Free(waza1);
            result = newSeq;
        } else {
            s32 num;
            SequenceWaza* tbl;
            tbl = hologramReliveWazaSeqTbl;
            num = 1;
            u16 id = pokemon->getPokemonDataId();
            if (id == 0x11 || id == 0x15C || id == 0x15D) {
                tbl = hologramPigeonReliveWazaSeqTbl;
                num = 1;
            }
            Vec holoScale;
            Sequence_GetScale((Sequence*)p2, &holoScale);
            menuModelSetScale(holoScale.x);
            for (s32 i = 0; i < num; i++) {
                Sequence_LoadWaza((Sequence*)p2, tbl[i].id, tbl[i].kind, 0);
            }
            Sequence_SetVisibility((Sequence*)p2, 1);
            for (s32 i = 0; i < num; tbl++, i++) {
                waza = Sequence_GetWaza((Sequence*)p2, tbl->id, tbl->kind);
                if (waza != NULL) {
                    WazaSequence_Start(waza, 0);
                    while (WazaSequence_IsActive(waza)) {
                        GSthreadSwitch();
                    }
                    WazaSequence_Free(waza);
                }
            }
            menuModelReSetScale();
        }
        break;
    }
    }

    evoLevel = 0;
    if (pokemonCheckValid(pokemon) != 1) {
        return 0;
    }
    s32 oldCount;
    for (oldCount = 0; oldCount < 4; oldCount++) {
        u16 id = pokemonBiosGetPokemonWazaDataId(pokemon, oldCount);
        if (id == 0) {
            break;
        }
        oldWaza[oldCount] = id;
    }
    pokemonAllKaihuku(pokemon);
    darkId = pokemonBiosGetDarkpokemonDataId(pokemon);
    darkPokemonBiosSetReliveFlag(darkId, 1);
    if (pokemonIsJoutaiDataId(pokemon, 0x3E)) {
        pokemonInitJoutaiDataId(pokemon, 0x3E);
    }
    soundOpenPlayME(0x3B5, 0, 0xFF);
    newCount = 0;
    for (s32 i = 0; i < 4; i++) {
        u16 id = pokemonBiosGetPokemonWazaDataId(pokemon, i);
        if (id == 0) {
            break;
        }
        s32 j;
        u8 found = 0;
        for (j = 0; j < oldCount; j++) {
            if (id == oldWaza[j]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            newCount++;
        }
    }
    if (newCount != 0) {
        char* nick = pokemonBiosGetNicknamePtr(pokemon);
        msgctrlSetValue(0x32, (u32)nick);
        winMsgOpenField((void*)0xC547, 1, 0);
        for (s32 i = 0; i < newCount; i++) {
            soundOpenPlayME(0x3C7, 0, 0xFF);
            u16 newWaza = pokemonBiosGetPokemonWazaDataId(pokemon, i);
            msgctrlSetValue(0x39, newWaza);
            winMsgOpenField((void*)((u8*)0xC54E + (i == newCount - 1 ? 1 : 0)), 1, 0);
        }
    }
    u32 poolExp = pokemonBiosGetPoolExp(pokemon);
    u32 exp = poolExp + DeckDarkPokemon::getDeckDarkPokemonObj(darkId)->getBonusExp();
    if (exp != 0) {
        msgctrlSetValue(0x2F, exp);
        winMsgOpenField((void*)0xC548, 1, 0);
        winMsgCloseField(1);
    }
    u32 friendship = pokemonBiosGetFriend(pokemon);
    u32 pool = pokemonBiosGetPoolFriend(pokemon) + 0x46;
    pokemonBiosSetFriend(pokemon, friendship + pool);
    pokemonBiosSetPoolFriend(pokemon, 0);
    if (_expRecover(pokemon, exp) == 1) {
        u16 evo = pokemonEvolutionCheck(pokemon, 0, 0, &evoLevel, &evoParam);
        if (evo != 0 && evo != 0xFFFF) {
            fadeSetToBlackOutIfNotBlack(0.5f);
            fadeCheck(1);
            if (keepRelivePatternIsHologram != 0) {
                menuHologramUnloadDatas();
            }
            if (pokemonEvolutionAll(pokemon, evo, evoLevel, &evoParam, 0, 1, 1, 0) == 0) {
                if (keepRelivePatternIsHologram != 0) {
                    menuHologramReloadDatas();
                    fadeSetToBlackInIfBlack(0.5f);
                    fadeCheck(1);
                } else {
                    reliveShowPokemon(pokemon);
                }
                msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(pokemon));
            } else {
                msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(pokemon));
                if (keepRelivePatternIsHologram != 0) {
                    menuHologramReloadDatas();
                    fadeSetToBlackInIfBlack(0.5f);
                    fadeCheck(1);
                } else {
                    reliveShowPokemon(pokemon);
                }
            }
        }
    }
    soundOpenPlayME(0x3CE, 0, 0xFF);
    exribbonSetNarionalRibbon(pokemon);
    winMsgOpenField((void*)0xC549, 1, 0);
    winMsgOpenField((void*)0xC54A, 1, 1);
    s32 answer = menuSubOpenYesNoField();
    winMsgCloseField(1);
    if (answer == 0) {
        fadeSetToBlackOutIfNotBlack(0.5f);
        fadeCheck(1);
        if (keepRelivePatternIsHologram != 0) {
            menuHologramUnloadDatas();
        }
        Sequence_SetVisibility(result, 0);
        Sequence_Free(result);
        result = NULL;
        menuNameEntryOpenNoFade(5, pokemon_c);
        if (keepRelivePatternIsHologram != 0) {
            menuHologramReloadDatas();
        } else {
            reliveShowPokemon(pokemon);
        }
    }
    return (s32)result;
}
#pragma pop
}

extern "C++" {
void reliveCeremonyFromHologram(Pokemon* p0, unsigned long p1) {
    s32 unksp8;
    menuPtStopSound((MenuPtWorkSound*)(&unksp8));
    reliveCeremonyAll(1, (Pokemon*)(p0), p1);
}
}

extern "C" {
void reliveMain() {
    reliveCeremonyAll(0, (Pokemon*)(mParameter), 0U);
    fadeSetToBlackOutIfNotBlack(0.5f);
    fadeCheck(1);
    M2C_FIELD(&pParameter, s32 *, 4) = -1;
    mParameter = NULL;
    GSfloorPop();
    floorSetFadeScript(0U, 0U);
    floorWaitForChange();
}
}

extern "C" {
void preReliveMain(u8 p0) {
    s32 unksp8;
    if (scriptGetDarkPointZeroPokemonNum() != 0) {
        if ((u8) isHokoraParticleLoaded == 1) {
            GSparticleDestroyGenerator(hokoraParticleGen, 1);
            hokoraParticleGen = 0;
            isHokoraParticleLoaded = 0;
        }
        if ((u16)scriptGetDarkPointZeroPokemonNum() == 0) {
            M2C_FIELD(&pParameter, s32 *, 4) = -1;
            return;
        }
        winMsgOpenField((void*)((u8 *)0xC546), 1U, 0U);
        winMsgCloseField(1U);
        s32 sel = menuPokemonOpen(7, 0, 0);
        if (sel != -1) {
            mParameter = (Pokemon *)(heroGetStatus((Hero*)(NULL), 3U, (u16)sel));
            fadeSetToBlackOutIfNotBlack(0.5f);
            fadeCheck(1);
            menuPtStopSound((MenuPtWorkSound*)(&unksp8));
            GSfloorPush(0x385U);
            floorSetFadeScript(0U, 0U);
            floorWaitForChange();
            fadeSetToBlackInIfBlack(1.0f);
            if (p0 == 1) {
                fadeCheck(1);
            }
            menuPtRestoreSound((MenuPtWorkSound*)(&unksp8));
        }
    } else {
        M2C_FIELD(&pParameter, s32 *, 4) = -1;
    }
}
}
void preReliveInit(void) {
    pParameter.index = -1;
}
extern "C" {
void preReliveSetParameter(s32 p0, s32 p1, u8 p2) {
    M2C_FIELD(&pParameter, s32 *, 4) = p1;
    if ((p0 == 0) || (p0 == 1)) {
        preReliveMain(p2);
    }
}
extern "C" {
void fn_80233AB4() {
    if (((GSthread *) lbl_804EB994 != NULL) && (GSthreadIsRunning((GSthread*)(lbl_804EB994)) != 0)) {
        GSthreadClose((GSthread*)(lbl_804EB994));
        lbl_804EB994 = NULL;
    }
    if ((u8) isHokoraParticleLoaded == 1) {
        GSparticleDestroyGenerator(hokoraParticleGen, 1);
        hokoraParticleGen = 0;
        isHokoraParticleLoaded = 0;
    }
}
}

}

extern "C" {
extern "C" {
static void __sinit_pokemonRelive_cpp() {
}
}
}

}
