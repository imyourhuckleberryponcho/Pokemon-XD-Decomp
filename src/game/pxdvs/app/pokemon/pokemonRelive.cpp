// Partial: only preReliveInit is written so far.
#include <dolphin/types.h>
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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

// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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
    s32 index; // 0x04
};

static PreReliveParameter pParameter;

extern "C" {


extern "C++" {
// ---- draft declarations ----
struct DeckDarkPokemon {
    u8 _draft[1];
    u16 getBonusExp() const;
    DeckDarkPokemon* getDeckDarkPokemonObj(unsigned long);
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
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
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
s32 Sequence_DoAnimation(s32, u8);
void Sequence_Free(void*);
s32 Sequence_GetPosition(s32, f32*, f32);
s32 Sequence_GetRotation(s32, f32*);
s32 Sequence_GetScale(s32, f32*);
WazaSequence* Sequence_GetWaza(Sequence* sequence, u16 wzxID, u32 kind);
u32 Sequence_LoadPokemon(u16, u32, u32);
void* Sequence_LoadWaza(Sequence* sequence, u16 wazaID, u8 kind, s32);
s32 Sequence_SetPosition(s32, f32*);
s32 Sequence_SetRotation(s32, f32*);
s32 Sequence_SetScale(s32, f32*);
s32 Sequence_SetVisibility(s32, s32);
void WazaSequence_Free(WazaSequence* sequence);
bool WazaSequence_IsActive(WazaSequence* sequence);
void WazaSequence_Start(WazaSequence* sequence, s32);
static void __sinit_pokemonRelive_cpp();
void darkPokemonBiosSetReliveFlag(u16 id);
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
s8 menuModelGetPokemonAnimationIndexByPointer(s32);
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
u16 pokemonBiosGetPokemonWazaDataId(Pokemon* poke, u32 wazaNum);
u32 pokemonBiosGetPoolExp(Pokemon* poke);
u32 pokemonBiosGetPoolFriend(Pokemon* poke);
u32 pokemonBiosGetRnd(Pokemon* poke);
void pokemonBiosSetExp(Pokemon* poke, u32 data);
void pokemonBiosSetFriend(Pokemon* poke, u16 data);
void pokemonBiosSetPoolFriend(Pokemon* poke, u16 data);
bool pokemonCheckValid(Pokemon* pokemon);
s32 pokemonEvolutionAll(s32, u16, u16, s32*, s32, s32, s32, s32);
u16 pokemonEvolutionCheck(s32, s32, s32, u16*, s32*);
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
extern s32 lbl_804EB994;
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
static s32 hokoraParticleGen;
static s32 hologramPigeonReliveWazaSeqTbl;
static s32 hologramReliveWazaSeqTbl;
static u8 isHokoraParticleLoaded;
static s32 keepRelivePatternIsHologram;
static Pokemon* mParameter;
static SequenceWaza noWazaSeqTbl;
static SequenceWaza normalReliveWazaSeqTbl;
// ---- draft declarations ----


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
        Sequence_SetVisibility((s32) sp8, 1);
        temp_r3 = Sequence_GetWaza((Sequence*)(sp8), M2C_FIELD(&noWazaSeqTbl, u16 *, 0), (u32) M2C_FIELD(&noWazaSeqTbl, u16 *, 2));
        if (temp_r3 != NULL) {
            WazaSequence_Start((WazaSequence*)(temp_r3), 1);
            if (((Pokemon*)(p0))->getPokemonDataId() == 0x15C) {
                Sequence_DoAnimation((s32) sp8, menuModelGetPokemonAnimationIndexByPointer((s32) p0));
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
            Sequence_DoAnimation((s32) sp8, menuModelGetPokemonAnimationIndexByPointer((s32) p0));
        }
    }
    return (s8) var_r30;
}
}

extern "C++" {
#pragma peephole off
static void _preReliveDisplayHokoraParticleThreadFunc() {
    volatile f32 sp10;
    f32 spC;
    f32 sp8;
    s32 temp_cr0_eq;
    s32 temp_r3;

    sp8 = 0.0f;
    temp_cr0_eq = (u8) isHokoraParticleLoaded == 1;
    spC = 7.0f;
    sp10 = 0.0f;
    if ((temp_cr0_eq != 0) && (temp_cr0_eq != 0)) {
        GSparticleDestroyGenerator((u16)hokoraParticleGen, 1);
        hokoraParticleGen = 0;
        isHokoraParticleLoaded = 0;
    }
    temp_r3 = (long)(GSparticleCreateGenerator((GSparticleBank*)(GSresGetResource(floorGetCurrentGroupID(), 0x0FAE1400U)), 0, 0));
    hokoraParticleGen = temp_r3;
    GSparticleSetGeneratorPosition((GSparticleGenerator*)((GSparticleGenerator *) temp_r3), (Vec*)((Vec *) &sp8));
    isHokoraParticleLoaded = 1;
    soundOpenPlay(0x597, 0, 0x7F);
    waitTime(4.0f);
    if ((u8) isHokoraParticleLoaded == 1) {
        GSparticleDestroyGenerator(hokoraParticleGen, 1);
        hokoraParticleGen = 0;
        isHokoraParticleLoaded = 0;
    }
    lbl_804EB994 = NULL;
}
#pragma peephole reset
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
    u32 newLevel;
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
            soundOpenPlayME(0x4CA, 0, 0xFF);
            msgctrlSetValue(0x2F, (u8)newLevel);
            winMsgOpenField((void*)0x44CE, 1, 0);
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
#pragma optimize_for_size on
static s32 reliveCeremonyAll(long p0, Pokemon* p1, unsigned long p2) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp28;
    u16 sp20;
    s32 sp1C;
    Sequence *sp18;
    Sequence *sp14;
    Sequence *sp10;
    Sequence *spC;
    u16 sp8;
    s32 *var_r25_3;
    s32 *var_r27_2;
    Sequence *temp_r3_9;
    Sequence *var_r30;
    SequenceWaza *var_r28;
    WazaSequence *temp_r26_2;
    WazaSequence *temp_r27;
    WazaSequence *temp_r3;
    WazaSequence *temp_r3_11;
    WazaSequence *temp_r3_6;
    WazaSequence *temp_r3_7;
    WazaSequence *temp_r3_8;
    f32 var_f30;
    f32 var_f30_2;
    f32 var_f30_3;
    f32 var_f30_4;
    s32 var_r25_2;
    s32 var_r26_2;
    s32 var_r27;
    s32 var_r27_3;
    s32 var_r28_2;
    s32 var_r28_3;
    s32 temp_r25_2;
    u16 *var_r4;
    u16 temp_r3_10;
    s32 temp_r3_2;
    u16 temp_r3_3;
    u16 temp_r3_4;
    s32 temp_r3_5;
    s32 var_ctr;
    s32 var_r25;
    u16 var_r26;
    u32 temp_r25;
    u32 temp_r26;
    u32 temp_ret;
    u8 var_r0;
    u8 var_r5;
    keepRelivePatternIsHologram = 0;
    var_r30 = NULL;
    switch (p0) {
    default:
        block_44:
                sp8 = 0;
        if (pokemonCheckValid((Pokemon*)(p1)) != 1) {
            return 0;
        }
        var_r25 = 0;
        var_r28_2 = 0;
        loop_47:
                temp_r3_2 = pokemonBiosGetPokemonWazaDataId((Pokemon*)(p1), (u32) var_r25);
        if (temp_r3_2 != 0) {
            var_r25 += 1;
            *(&sp20 + var_r28_2) = temp_r3_2;
            var_r28_2 += 2;
            if ((s32) var_r25 < 4) {
                goto loop_47;
            }
        }
        pokemonAllKaihuku((Pokemon*)(p1));
        temp_r3_3 = pokemonBiosGetDarkpokemonDataId((Pokemon*)(p1));
        darkPokemonBiosSetReliveFlag(temp_r3_3);
        if (pokemonIsJoutaiDataId((Pokemon*)(p1), 0x3EU) != 0) {
            pokemonInitJoutaiDataId((Pokemon*)(p1), 0x3EU);
        }
        soundOpenPlayME(0x3B5U, 0U, 0xFFU);
        var_r28_3 = 0;
        var_r26 = 0;
        loop_52:
                temp_r3_4 = pokemonBiosGetPokemonWazaDataId((Pokemon*)(p1), (u32) var_r26);
        if (temp_r3_4 != 0) {
            var_r4 = &sp20;
            var_r5 = 0;
            var_ctr = var_r25;
            if ((s32) var_r25 > 0) {
                loop_54:
                        if (temp_r3_4 == (u16) *var_r4) {
                            var_r5 = 1;
                        } else {
                            var_r4 += 2;
                            var_ctr -= 1;
                            if (var_ctr != 0) {
                                goto loop_54;
                            }
                        }
            }
            if (var_r5 == 0) {
                var_r28_3 += 1;
            }
            var_r26 += 1;
            if ((s32) var_r26 < 4) {
                goto loop_52;
            }
        }
        if (var_r28_3 != 0) {
            msgctrlSetValue((long)(0x32), (unsigned long)(pokemonBiosGetNicknamePtr((Pokemon*)(p1))));
            winMsgOpenField((void*)((u8 *)0xC547), 1U, 0U);
            var_r25_2 = 0;
            while (var_r25_2 < var_r28_3) {
                        soundOpenPlayME(0x3C7U, 0U, 0xFFU);
                        msgctrlSetValue(0x39, (u32) pokemonBiosGetPokemonWazaDataId((Pokemon*)(p1), (u32) (u16) var_r25_2));
                        winMsgOpenField((void*)((var_r25_2 == (var_r28_3 - 1)) + 0xC54E), 1U, 0U);
                        var_r25_2 += 1;
                    }
        }
        temp_ret = pokemonBiosGetPoolExp((Pokemon*)(p1));
        temp_r25 = temp_ret + ((DeckDarkPokemon*)(((DeckDarkPokemon*)((DeckDarkPokemon *) temp_r3_3))->getDeckDarkPokemonObj((u32) (u64) temp_ret)))->getBonusExp();
        if (temp_r25 != 0) {
            msgctrlSetValue(0x2F, temp_r25);
            winMsgOpenField((void*)((u8 *)0xC548), 1U, 0U);
            winMsgCloseField(1U);
        }
        pokemonBiosSetFriend((Pokemon*)(p1), (u16) ((pokemonBiosGetFriend((Pokemon*)(p1))) + (pokemonBiosGetPoolFriend((Pokemon*)(p1)) + 0x46)));
        pokemonBiosSetPoolFriend((Pokemon*)(p1), 0U);
        if (_expRecover((Pokemon*)(p1), temp_r25) == 1) {
            temp_r3_5 = pokemonEvolutionCheck((s32) p1, 0, 0, &sp8, &sp1C);
            if ((temp_r3_5 != 0) && (temp_r3_5 != -1U)) {
                fadeSetToBlackOutIfNotBlack(0.5f);
                fadeCheck(1);
                if ((s32) keepRelivePatternIsHologram != 0) {
                    menuHologramUnloadDatas();
                }
                if (pokemonEvolutionAll((s32) p1, temp_r3_5, sp8, &sp1C, 0, 1, 1, 0) == 0) {
                    if ((s32) keepRelivePatternIsHologram != 0) {
                        menuHologramReloadDatas();
                        fadeSetToBlackInIfBlack(0.5f);
                        fadeCheck(1);
                    } else {
                        loadSequence((Sequence**)(&sp14), (Pokemon*)(p1), (SequenceWaza*)(&noWazaSeqTbl), 1);
                        fadeSetToBlackInIfBlack(0.5f);
                        fadeSet(2, 0.5f);
                        Sequence_SetVisibility((s32) sp14, 1);
                        temp_r3_6 = Sequence_GetWaza((Sequence*)(sp14), M2C_FIELD(&noWazaSeqTbl, u16 *, 0), (u32) M2C_FIELD(&noWazaSeqTbl, u16 *, 2));
                        if (temp_r3_6 != NULL) {
                            WazaSequence_Start((WazaSequence*)(temp_r3_6), 1);
                            if (((Pokemon*)(p1))->getPokemonDataId() == 0x15C) {
                                Sequence_DoAnimation((s32) sp14, menuModelGetPokemonAnimationIndexByPointer((s32) p1));
                            }
                            var_f30_2 = 0.0f;
                            while (WazaSequence_IsActive((WazaSequence*)(temp_r3_6)) != 0) {
                                        GSthreadSwitch();
                                        var_f30_2 += timeGetLastFrameSec();
                                        if (!(!(var_f30_2 > 4.0f))) {
                                            break;
                                        }
                                    }
                                    WazaSequence_Free((WazaSequence*)(temp_r3_6));
                        }
                        if (((Pokemon*)(p1))->getPokemonDataId() == 0x15C) {
                            Sequence_DoAnimation((s32) sp14, menuModelGetPokemonAnimationIndexByPointer((s32) p1));
                        }
                    }
                    msgctrlSetValue((long)(0x32), (unsigned long)(pokemonBiosGetNicknamePtr((Pokemon*)(p1))));
                } else {
                    msgctrlSetValue((long)(0x32), (unsigned long)(pokemonBiosGetNicknamePtr((Pokemon*)(p1))));
                    if ((s32) keepRelivePatternIsHologram != 0) {
                        menuHologramReloadDatas();
                        fadeSetToBlackInIfBlack(0.5f);
                        fadeCheck(1);
                    } else {
                        loadSequence((Sequence**)(&sp10), (Pokemon*)(p1), (SequenceWaza*)(&noWazaSeqTbl), 1);
                        fadeSetToBlackInIfBlack(0.5f);
                        fadeSet(2, 0.5f);
                        Sequence_SetVisibility((s32) sp10, 1);
                        temp_r3_7 = Sequence_GetWaza((Sequence*)(sp10), M2C_FIELD(&noWazaSeqTbl, u16 *, 0), (u32) M2C_FIELD(&noWazaSeqTbl, u16 *, 2));
                        if (temp_r3_7 != NULL) {
                            WazaSequence_Start((WazaSequence*)(temp_r3_7), 1);
                            if (((Pokemon*)(p1))->getPokemonDataId() == 0x15C) {
                                Sequence_DoAnimation((s32) sp10, menuModelGetPokemonAnimationIndexByPointer((s32) p1));
                            }
                            var_f30_3 = 0.0f;
                            while (WazaSequence_IsActive((WazaSequence*)(temp_r3_7)) != 0) {
                                        GSthreadSwitch();
                                        var_f30_3 += timeGetLastFrameSec();
                                        if (!(!(var_f30_3 > 4.0f))) {
                                            break;
                                        }
                                    }
                                    WazaSequence_Free((WazaSequence*)(temp_r3_7));
                        }
                        if (((Pokemon*)(p1))->getPokemonDataId() == 0x15C) {
                            Sequence_DoAnimation((s32) sp10, menuModelGetPokemonAnimationIndexByPointer((s32) p1));
                        }
                    }
                }
            }
        }
        soundOpenPlayME(0x3CEU, 0U, 0xFFU);
        exribbonSetNarionalRibbon((Pokemon*)(p1));
        winMsgOpenField((void*)((u8 *)0xC549), 1U, 0U);
        winMsgOpenField((void*)((u8 *)0xC54A), 1U, 1U);
        temp_r25_2 = menuSubOpenYesNoField();
        winMsgCloseField(1U);
        switch (temp_r25_2) {
                case 0:
                        fadeSetToBlackOutIfNotBlack(0.5f);
                        fadeCheck(1);
                        if ((s32) keepRelivePatternIsHologram != 0) {
                            menuHologramUnloadDatas();
                        }
                        Sequence_SetVisibility((s32) var_r30, 0);
                        Sequence_Free((void*)(var_r30));
                        var_r30 = NULL;
                        menuNameEntryOpenNoFade(5, (s32) p1);
                        if ((s32) keepRelivePatternIsHologram != 0) {
                            menuHologramReloadDatas();
                        } else {
                            loadSequence((Sequence**)(&spC), (Pokemon*)(p1), (SequenceWaza*)(&noWazaSeqTbl), 1);
                            fadeSetToBlackInIfBlack(0.5f);
                            fadeSet(2, 0.5f);
                            Sequence_SetVisibility((s32) spC, 1);
                            temp_r3_8 = Sequence_GetWaza((Sequence*)(spC), M2C_FIELD(&noWazaSeqTbl, u16 *, 0), (u32) M2C_FIELD(&noWazaSeqTbl, u16 *, 2));
                            if (temp_r3_8 != NULL) {
                                WazaSequence_Start((WazaSequence*)(temp_r3_8), 1);
                                if (((Pokemon*)(p1))->getPokemonDataId() == 0x15C) {
                                    Sequence_DoAnimation((s32) spC, menuModelGetPokemonAnimationIndexByPointer((s32) p1));
                                }
                                var_f30_4 = 0.0f;
                                while (WazaSequence_IsActive((WazaSequence*)(temp_r3_8)) != 0) {
                                    GSthreadSwitch();
                                    var_f30_4 += timeGetLastFrameSec();
                                    if (!(!(var_f30_4 > 4.0f))) {
                                        break;
                                    }
                                }
                                WazaSequence_Free((WazaSequence*)(temp_r3_8));
                            }
                            if (((Pokemon*)(p1))->getPokemonDataId() == 0x15C) {
                                Sequence_DoAnimation((s32) spC, menuModelGetPokemonAnimationIndexByPointer((s32) p1));
                            }
                        }
                    break;
                }
        return (s32) var_r30;
    }
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
