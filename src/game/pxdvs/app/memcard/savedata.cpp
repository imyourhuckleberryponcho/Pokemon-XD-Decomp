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
struct CReliveHall;
struct Gamedata;
struct Hero;
struct HeroPokemonGetParam;
struct Mailbox;
struct Memo;
struct Pokemon;
struct Savedata;

extern "C" {
// ---- draft declarations ----
struct CReliveHall {
    u8 _draft[1];
    s32 init();
};
struct Gamedata {
    u8 _draft[1];
};
struct Hero {
    u8 _draft[1];
    s32 setFollowerID(unsigned char);
    void setBattleResumeFloorID(unsigned int);
    void setBattleResumeFloorIndex(unsigned char);
    void setHeroStyle(unsigned char, bool);
    Pokemon* getPokemon(long);
    s16 pokemonGet(HeroPokemonGetParam*, bool);
};
struct HeroPokemonGetParam {
    u8 _draft[1];
};
struct Mailbox {
    u8 _draft[1];
};
struct Memo {
    u8 _draft[1];
};
struct Pokemon {
    u8 _draft[1];
};
struct Savedata {
    u8 _draft[1];
};

extern "C" {
s32 GScharMakeFromSJIS(s32*, s32*);
void GSflagClear(u32 level);
void GSflagOn(u32 id);
s32 darkpokemonValInit();
void exribbonInit(u8* exribbon);
void gamedataCreate(Gamedata* ptr, u8 ver, u8 gen, u8 area, u8 langarea);
void gamedataInit(void* ptr);
void gamedatasaveSetStatus(Gamedata* ptr, u32 kind, u32 value);
u16* heroBiosGetNamePtr(Hero* hero);
u32 heroBiosGetRnd(Hero* hero);
u8 heroBiosGetSexDataId(Hero* hero);
void heroCreate(Hero* hero, u32 name, u8 sex);
void heroInit(Hero* hero);
s32 heroItemAddItemDataId(Hero* hero, u32 itemID, u32 amount, u32 index);
void heroSetStatus(Hero* hero, u32 selector, u32 value);
void mailInitMailbox(Mailbox* box);
void* memcpy(void* dst, const void* src, size_t n);
void memoInit(Memo* memo);
void* memset(void* dst, int val, size_t n);
s32 menuCB_RULE_INIT();
s32 pcboxInit();
s32 pokecoloGetCountryCode(void);
s32 pokecoloGetLanguage(void);
s32 pokecoloGetRomVersion(void);
void pokemonBiosSetTokuseiFlag(Pokemon* poke, bool data);
u32 pokemonCreateRndFit(Pokemon* pokemon, s8 sex, s8 seikaku, s8 rare, u32 trainerRnd);
void pokemonResetBasisStatus(Pokemon* pokemon);
void pokemon_SetRnd(Pokemon* poke, u32 data);
void* savedataBiosGetAnywaySavePtr(Savedata* savedata);
void* savedataBiosGetDarkpokemonPtr(Savedata* savedata);
void* savedataBiosGetExRibbonPtr(Savedata* savedata);
void* savedataBiosGetFlagLevel0Ptr(Savedata* savedata);
void* savedataBiosGetFlagLevel1Ptr(Savedata* savedata);
void* savedataBiosGetFlagLevel2Ptr(Savedata* savedata);
void* savedataBiosGetFlagSavedataPtr(Savedata* savedata);
void* savedataBiosGetGamedataPtr(Savedata* savedata);
void* savedataBiosGetHeroPtr(Savedata* savedata);
void* savedataBiosGetMailboxPtr(Savedata* savedata);
void* savedataBiosGetMemoDataPtr(Savedata* savedata);
u32 savedataBiosGetNowSavedataPtr();
void* savedataBiosGetPcboxPtr(Savedata* savedata);
void* savedataBiosGetRelivePtr(Savedata* savedata);
void* savedataBiosGetSodateyaPtr(Savedata* savedata);
void* savedataBiosGetToolPtr(Savedata* savedata);
void* savedataBiosGetYobi1Ptr(Savedata* savedata);
void* savedataBiosGetYobi2Ptr(Savedata* savedata);
void* savedataBiosGetYobi3Ptr(Savedata* savedata);
void* savedataBiosGetYobi4Ptr(Savedata* savedata);
void* savedataGetStatus(void* save, s32 kind);
void savedataSetBattleDiskSellOut(u32 p0);
s32 sodateyaInit();
extern s32 jtbl_2134;
}

// ---- draft declarations ----


extern "C" {
void savedataCreate(u32 p0, s32 *p1);
s32 savedataGetBattleDiskSellOut(u32 p0);
void savedataInit(u32 p0);
extern s32 jtbl_2059;
}

void savedataSetBattleDiskSellOut(u32 p0) {
    s32 temp_r6;
    u8 *temp_r3;

    temp_r3 = (unsigned char *)(savedataGetStatus((void*)(NULL), 0x18));
    temp_r6 = (p0 >> 3U) & 0x1FFFFFFC;
    *(temp_r3 + temp_r6) = *(temp_r3 + temp_r6) | (1 << (p0 & 0x1F));
}
extern "C" {
#pragma push
#pragma dont_inline on
s32 savedataGetBattleDiskSellOut(u32 p0) { return 0; }
extern "C" {
void savedataCreate(u32 p0, s32 *p1) {
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    u16 *sp30;
    u32 sp2C;
    u16 sp2A;
    volatile u16 sp28;
    volatile u16 sp26;
    u16 sp24;
    u16 sp22;
    u16 sp20;
    u16 sp1E;
    u8 sp1D;
    u8 sp1C;
    s32 sp8;
    Gamedata *temp_r30;
    s32 var_r28_2;
    s32 *var_r29;
    s32 *var_r30_2;
    Pokemon *temp_r29;
    s32 *var_r28;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r6;
    Hero *temp_r31;
    s32 var_r30;

    var_r28 = p1;
    memset((void*)(&sp1C), 0, 0x24U);
    savedataInit(p0);
    temp_r30 = (Gamedata *)(savedataGetStatus((void*)((u8 *) p0), 1));
    temp_r3 = pokecoloGetCountryCode();
    switch (temp_r3) {                              /* irregular */
    case 0:
        gamedataCreate((Gamedata*)(temp_r30), 0xBU, 3U, 1U, 1U);
        break;
    case 1:
        gamedataCreate((Gamedata*)(temp_r30), 0xBU, 3U, 2U, 2U);
        break;
    case 2:
        gamedataCreate((Gamedata*)(temp_r30), 0xBU, 3U, 3U, 8U);
        break;
    }
    gamedatasaveSetStatus((Gamedata*)(temp_r30), 0xBU, pokecoloGetLanguage());
    temp_r31 = (Hero *)(savedataGetStatus((void*)((u8 *) p0), 2));
    if (var_r28 == NULL) {
        GScharMakeFromSJIS(&sp8, &jtbl_2134);
        var_r28 = &sp8;
    }
    heroCreate((Hero*)(temp_r31), (u32) var_r28, 0U);
    if (pokecoloGetRomVersion() == 1) {
        M2C_STRUCT_COPY((s32) &sp3C + 4, (s32) (&jtbl_2059 - 4) + 4, 0x70);
        gamedatasaveSetStatus((Gamedata*)(temp_r30), 5U, 0x8AU);
        gamedatasaveSetStatus((Gamedata*)(temp_r30), 7U, 0x8FU);
        gamedatasaveSetStatus((Gamedata*)(temp_r30), 8U, 2U);
        var_r29 = &sp40;
        var_r30 = 0;
        do {
            sp1E = M2C_FIELD(var_r29, u16 *, 2);
            sp20 = M2C_FIELD(var_r29, u16 *, 4);
            sp1D = M2C_FIELD(var_r29, u8 *, 0);
            sp22 = M2C_FIELD(var_r29, u16 *, 6);
            sp24 = M2C_FIELD(var_r29, u16 *, 8);
            sp26 = M2C_FIELD(var_r29, u16 *, 0xA);
            sp28 = M2C_FIELD(var_r29, u16 *, 0xC);
            sp2A = M2C_FIELD(var_r29, u16 *, 0xE);
            sp1C = heroBiosGetSexDataId((Hero*)(temp_r31));
            sp2C = heroBiosGetRnd((Hero*)(temp_r31));
            temp_r6 = M2C_FIELD(var_r29, s32 *, 0x10);
            temp_r0 = M2C_FIELD(var_r29, s32 *, 0x14);
            sp30 = heroBiosGetNamePtr((Hero*)(temp_r31));
            var_r29 += 0x1C;
            sp38 = temp_r6;
            sp3C = temp_r0;
            ((Hero*)(temp_r31))->pokemonGet((HeroPokemonGetParam*)((HeroPokemonGetParam *) &sp1C), 1U);
            var_r30 += 1;
        } while (var_r30 < 4);
        var_r30_2 = &sp40;
        var_r28_2 = 0;
        do {
            temp_r29 = ((Hero*)(temp_r31))->getPokemon(var_r28_2);
            pokemon_SetRnd((Pokemon*)(temp_r29), pokemonCreateRndFit((Pokemon*)(temp_r29), (s8) M2C_FIELD(var_r30_2, u8 *, 0x18), (s8) M2C_FIELD(var_r30_2, u8 *, 0x19), 0, heroBiosGetRnd((Hero*)(temp_r31))));
            pokemonBiosSetTokuseiFlag((Pokemon*)(temp_r29), M2C_FIELD(var_r30_2, u8 *, 0x1A));
            pokemonResetBasisStatus((Pokemon*)(temp_r29));
            var_r28_2 += 1;
            var_r30_2 += 0x1C;
        } while (var_r28_2 < 4);
        heroSetStatus((Hero*)(temp_r31), 0xCU, 0U);
        heroItemAddItemDataId((Hero*)(temp_r31), 2U, 0x14U, -1U);
        heroItemAddItemDataId((Hero*)(temp_r31), 0x15U, 0x14U, -1U);
        heroItemAddItemDataId((Hero*)(temp_r31), 0x17U, 0xAU, -1U);
        heroItemAddItemDataId((Hero*)(temp_r31), 0x18U, 5U, -1U);
        ((Hero*)(temp_r31))->setBattleResumeFloorID(0x47U);
        ((Hero*)(temp_r31))->setBattleResumeFloorIndex(0U);
        ((Hero*)(temp_r31))->setHeroStyle(2U, 0U);
        ((Hero*)(temp_r31))->setFollowerID(0U);
        return;
    }
    gamedatasaveSetStatus((Gamedata*)(temp_r30), 5U, 0x8AU);
    gamedatasaveSetStatus((Gamedata*)(temp_r30), 7U, 0x8FU);
    gamedatasaveSetStatus((Gamedata*)(temp_r30), 8U, 2U);
    sp1E = 0x85;
    sp20 = 0;
    sp1D = 0xA;
    sp22 = 0xD7;
    sp24 = 0x21;
    sp26 = 0x27;
    sp28 = 0x2C;
    sp2A = 0x1C;
    sp1C = heroBiosGetSexDataId((Hero*)(temp_r31));
    sp2C = heroBiosGetRnd((Hero*)(temp_r31));
    sp30 = heroBiosGetNamePtr((Hero*)(temp_r31));
    sp38 = 0;
    sp3C = 0x4E2;
    ((Hero*)(temp_r31))->pokemonGet((HeroPokemonGetParam*)((HeroPokemonGetParam *) &sp1C), 1U);
    heroSetStatus((Hero*)(temp_r31), 0xCU, 0x1388U);
    ((Hero*)(temp_r31))->setBattleResumeFloorID(0x8AU);
    ((Hero*)(temp_r31))->setBattleResumeFloorIndex(2U);
    ((Hero*)(temp_r31))->setHeroStyle(0U, 0U);
    ((Hero*)(temp_r31))->setFollowerID(0U);
}
}

#pragma pop
}

}

extern "C" {
extern "C" {
extern "C" {
extern "C" {
void* savedataGetStatus(void* p0, s32 p1) {
    u8 *var_r3;

    var_r3 = (unsigned char *)(p0);
    if ((u16) p1 >= 0x1DU) {
        return NULL;
    }
    if (var_r3 == NULL) {
        var_r3 = (unsigned char *)(savedataBiosGetNowSavedataPtr());
        if (var_r3 == NULL) {
            return NULL;
        }
    }
    switch ((u16) p1) {
    case 0:
        return var_r3;
    case 1:
        return savedataBiosGetGamedataPtr((Savedata*)((Savedata *) var_r3));
    case 2:
        return savedataBiosGetHeroPtr((Savedata*)((Savedata *) var_r3));
    case 3:
        return savedataBiosGetPcboxPtr((Savedata*)((Savedata *) var_r3));
    case 4:
        return savedataBiosGetFlagLevel0Ptr((Savedata*)((Savedata *) var_r3));
    case 5:
        return savedataBiosGetFlagLevel1Ptr((Savedata*)((Savedata *) var_r3));
    case 6:
        return savedataBiosGetFlagLevel2Ptr((Savedata*)((Savedata *) var_r3));
    case 24:
        return var_r3 + 0x10E30;
    case 27:
        return var_r3 + 0x10E38;
    case 7:
        return (u8 *)8;
    case 8:
        return (u8 *)0x20;
    case 9:
        return (u8 *)0x180;
    case 25:
        return (u8 *)2;
    case 28:
        return (u8 *)2;
    case 10:
        return savedataBiosGetMailboxPtr((Savedata*)((Savedata *) var_r3));
    case 11:
        return savedataBiosGetSodateyaPtr((Savedata*)((Savedata *) var_r3));
    case 12:
        return savedataBiosGetMemoDataPtr((Savedata*)((Savedata *) var_r3));
    case 14:
        return savedataBiosGetToolPtr((Savedata*)((Savedata *) var_r3));
    case 15:
        return savedataBiosGetDarkpokemonPtr((Savedata*)((Savedata *) var_r3));
    case 16:
        return savedataBiosGetExRibbonPtr((Savedata*)((Savedata *) var_r3));
    case 22:
        return savedataBiosGetAnywaySavePtr((Savedata*)((Savedata *) var_r3));
    case 26:
        return (u8 *)0xC800;
    case 17:
        return savedataBiosGetYobi1Ptr((Savedata*)((Savedata *) var_r3));
    case 18:
        return savedataBiosGetYobi2Ptr((Savedata*)((Savedata *) var_r3));
    case 19:
        return savedataBiosGetYobi3Ptr((Savedata*)((Savedata *) var_r3));
    case 20:
        return savedataBiosGetYobi4Ptr((Savedata*)((Savedata *) var_r3));
    case 21:
        return savedataBiosGetRelivePtr((Savedata*)((Savedata *) var_r3));
    case 23:
        return savedataBiosGetFlagSavedataPtr((Savedata*)((Savedata *) var_r3));
    default:
        return NULL;
    }
}
}
}
}
}
