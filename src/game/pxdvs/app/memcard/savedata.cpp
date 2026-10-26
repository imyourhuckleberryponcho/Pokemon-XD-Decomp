#include <dolphin/types.h>
#pragma pool_strings off
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
typedef u16 char16;
struct CReliveHall;
struct Gamedata;
struct Hero;
struct HeroPokemonGetParam;
struct Mailbox;
struct Memo;
struct Pokemon;
struct Savedata;

extern "C" {
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
    u8 trainerSexID;
    u8 catchLevel;
    u16 pokemonDataID;
    u16 shadowPokemonDataID;
    u16 friendLevel;
    u16 move1;
    u16 move2;
    u16 move3;
    u16 move4;
    u32 trainerRnd;
    char16* trainerNamePtr;
    char16* nicknamePtr;
    u32 catchFloorID;
    u32 exp;
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
s32 GScharMakeFromSJIS(char16*, const char*);
void GSflagClear(u32 level);
void GSflagOn(u32 id);
s32 darkpokemonValInit(void* dark);
void exribbonInit(void* exribbon);
void gamedataCreate(Gamedata* ptr, u8 ver, u8 gen, u8 area, u8 langarea);
void gamedataInit(void* ptr);
void gamedatasaveSetStatus(Gamedata* ptr, u32 kind, u32 value);
char16* heroBiosGetNamePtr(Hero* hero);
u32 heroBiosGetRnd(Hero* hero);
u8 heroBiosGetSexDataId(Hero* hero);
void heroCreate(Hero* hero, char16* name, u8 sex);
void heroInit(void* hero);
s32 heroItemAddItemDataId(Hero* hero, u32 itemID, u32 amount, u32 index);
void heroSetStatus(Hero* hero, u32 selector, u32 value);
void mailInitMailbox(void* box);
void* memcpy(void* dst, const void* src, size_t n);
void memoInit(void* memo);
void* memset(void* dst, int val, size_t n);
s32 menuCB_RULE_INIT(void* rule);
s32 pcboxInit(void* pcbox);
s32 pokecoloGetCountryCode(void);
s32 pokecoloGetLanguage(void);
s32 pokecoloGetRomVersion(void);
void pokemonBiosSetTokuseiFlag(Pokemon* poke, u8 data);
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
s32 sodateyaInit(void* sodateya);
extern s32 jtbl_2134;
}

extern "C" {
void savedataCreate(void* save, char16* name);
s32 savedataGetBattleDiskSellOut(u32 p0);
void savedataInit(void* save);
extern s32 jtbl_2059;
}

void savedataSetBattleDiskSellOut(u32 id) {
    u32* bits = (u32*)savedataGetStatus(NULL, 0x18);
    bits[id >> 5] |= 1 << (id & 0x1F);
}
extern "C" {
#pragma push
#pragma dont_inline on
s32 savedataGetBattleDiskSellOut(u32 id) {
    u32* bits = (u32*)savedataGetStatus(NULL, 0x18);
    return (bits[id >> 5] & (1 << (id & 0x1F))) != 0;
}
u8 pokecolo_savedata[0x287D0] __attribute__((aligned(32)));
void* now_savedata_ptr;

struct StartPokemon {
    u8 level;
    u16 species;
    u16 shadow;
    u16 friendLevel;
    u16 moves[4];
    u32 floor;
    u32 exp;
    s8 sex;
    s8 seikaku;
    u8 tokusei;
};

extern "C" {
void savedataCreate(void* save, char16* name) {
    StartPokemon* sp2;
    s32 i;
    Gamedata* game;
    Pokemon* pokemon;
    char16 defName[10];
    Hero* hero;
    HeroPokemonGetParam param;
    StartPokemon* sp;
    s32 j;

    memset(&param, 0, sizeof(param));
    savedataInit(save);
    game = (Gamedata*)savedataGetStatus(save, 1);
    switch (pokecoloGetCountryCode()) {
    case 0:
        gamedataCreate(game, 0xB, 3, 1, 1);
        break;
    case 1:
        gamedataCreate(game, 0xB, 3, 2, 2);
        break;
    case 2:
        gamedataCreate(game, 0xB, 3, 3, 8);
        break;
    }
    gamedatasaveSetStatus(game, 0xB, pokecoloGetLanguage());
    hero = (Hero*)savedataGetStatus(save, 2);
    if (name == 0) {
        GScharMakeFromSJIS(defName, "\x81\x40");
        name = defName;
    }
    heroCreate(hero, name, 0);
    if (pokecoloGetRomVersion() == 1) {
        StartPokemon party[4] = {
            {0x28, 0x2F, 0, 0, {0x93, 0xCA, 0xA, 0x4A}, 0, 0xFA00, 0, 0, 0},
            {0x28, 0x189, 0, 0, {0x5D, 0x15F, 0xF7, 0x15B}, 0, 0x13880, 1, 0x12, 0},
            {0x28, 0x65, 0, 0, {0xD1, 0x56, 0x81, 0x67}, 0, 0xFA00, 0, 0xC, 0},
            {0x28, 0x155, 0, 0, {0x3E, 0x39, 0x22, 0x2D}, 0, 0xDD54, 1, 0x12, 0},
        };
        gamedatasaveSetStatus(game, 5, 0x8A);
        gamedatasaveSetStatus(game, 7, 0x8F);
        gamedatasaveSetStatus(game, 8, 2);
        sp = party;
        for (i = 0; i < 4; i++) {
            param.pokemonDataID = sp->species;
            param.shadowPokemonDataID = sp->shadow;
            param.catchLevel = sp->level;
            param.friendLevel = sp->friendLevel;
            param.move1 = sp->moves[0];
            param.move2 = sp->moves[1];
            param.move3 = sp->moves[2];
            param.move4 = sp->moves[3];
            param.trainerSexID = heroBiosGetSexDataId(hero);
            param.trainerRnd = heroBiosGetRnd(hero);
            param.trainerNamePtr = heroBiosGetNamePtr(hero);
            param.catchFloorID = sp->floor;
            param.exp = sp->exp;
            sp++;
            hero->pokemonGet(&param, 1);
        }
        sp2 = party;
        for (j = 0; j < 4; j++) {
            pokemon = hero->getPokemon(j);
            u32 rnd = pokemonCreateRndFit(pokemon, sp2->sex, sp2->seikaku, 0, heroBiosGetRnd(hero));
            pokemon_SetRnd(pokemon, rnd);
            pokemonBiosSetTokuseiFlag(pokemon, sp2->tokusei);
            pokemonResetBasisStatus(pokemon);
            sp2++;
        }
        heroSetStatus(hero, 0xC, 0);
        heroItemAddItemDataId(hero, 2, 0x14, -1);
        heroItemAddItemDataId(hero, 0x15, 0x14, -1);
        heroItemAddItemDataId(hero, 0x17, 0xA, -1);
        heroItemAddItemDataId(hero, 0x18, 5, -1);
        hero->setBattleResumeFloorID(0x47);
        hero->setBattleResumeFloorIndex(0);
        hero->setHeroStyle(2, 0);
        hero->setFollowerID(0);
        return;
    }
    gamedatasaveSetStatus(game, 5, 0x8A);
    gamedatasaveSetStatus(game, 7, 0x8F);
    gamedatasaveSetStatus(game, 8, 2);
    param.pokemonDataID = 0x85;
    param.shadowPokemonDataID = 0;
    param.catchLevel = 0xA;
    param.friendLevel = 0xD7;
    param.move1 = 0x21;
    param.move2 = 0x27;
    param.move3 = 0x2C;
    param.move4 = 0x1C;
    param.trainerSexID = heroBiosGetSexDataId(hero);
    param.trainerRnd = heroBiosGetRnd(hero);
    param.trainerNamePtr = heroBiosGetNamePtr(hero);
    param.catchFloorID = 0;
    param.exp = 0x4E2;
    hero->pokemonGet(&param, 1);
    heroSetStatus(hero, 0xC, 0x1388);
    hero->setBattleResumeFloorID(0x8A);
    hero->setBattleResumeFloorIndex(2);
    hero->setHeroStyle(0, 0);
    hero->setFollowerID(0);
}
}

#pragma pop
}

}

extern "C" {
void savedataInit(void* save) {
    u8 game[0x88];
    u8 rule[0x364];

    memcpy(game, savedataGetStatus(save, 1), 0x88);
    memcpy(rule, savedataGetStatus(save, 0xE), 0x364);
    memset(savedataGetStatus(0, 0), 0, 0x27FD0);
    memcpy(savedataGetStatus(save, 1), game, 0x88);
    memcpy(savedataGetStatus(save, 0xE), rule, 0x364);
    gamedataInit(savedataGetStatus(save, 1));
    heroInit(savedataGetStatus(save, 2));
    pcboxInit(savedataGetStatus(save, 3));
    if (save == 0 || save == savedataGetStatus(0, 0)) {
        GSflagClear(1);
        GSflagClear(2);
        GSflagClear(3);
        GSflagOn(0x3DE);
    }
    memset(savedataGetStatus(save, 0x18), 0, (u32)savedataGetStatus(save, 0x19) * 4);
    memset(savedataGetStatus(save, 0x1B), 0, (u32)savedataGetStatus(save, 0x1C) * 4);
    mailInitMailbox(savedataGetStatus(save, 0xA));
    sodateyaInit(savedataGetStatus(save, 0xB));
    menuCB_RULE_INIT(savedataGetStatus(save, 0xE));
    memoInit(savedataGetStatus(save, 0xC));
    darkpokemonValInit(savedataGetStatus(save, 0xF));
    exribbonInit(savedataGetStatus(save, 0x10));
    ((CReliveHall*)savedataGetStatus(save, 0x15))->init();
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
