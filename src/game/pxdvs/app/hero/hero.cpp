#include <dolphin/types.h>

#pragma pool_strings off

class Pokemon;
class Item;

enum FloorStateMode { FLOOR_STATE_MODE_0 };
enum FloorEnterMode { FLOOR_ENTER_MODE_0 };

struct FloorModuleInterface {
    u32 unk0;
    void (*enterFloor)(unsigned int, FloorEnterMode);
    u32 unk8;
    u32 unkC;
    void (*exitFloor)(unsigned int, FloorEnterMode);
    u32 unk14;
    const char* (*getModuleName)(void);
    void (*makeStateData)(FloorStateMode, void*, unsigned long);
    void (*restoreStateData)(FloorStateMode, void*, unsigned long);
    u32 (*getStateSize)(FloorStateMode);
    u32 (*getUID)(void);
    u8 unk2C[4];
};

class Hero {
public:
    static Hero* getHeroPtr();
    void setRestertPos();
    bool setPokemon(const Pokemon*, s32);
    Item** getDisk();
    void setHeroStyle(u8, bool);
    void setFollowerID(u8);
    void setFollowerModelLevel(u8);
    void setFollowerGrpID(u32);
    void setFollowerResID(u32);
    void setFollowerObjID(u32);
    u32 getFollowerGrpID();
    u32 getFollowerResID();
    u32 getHeroObjID(s32, s32);
};

extern "C" {
u32 heroGetStatus(Hero*, u32, u16);
void heroSetStatus(Hero*, u32, u32);
void* savedataGetStatus(void*, u16);
u8 pokemonCheckValid(void*);
u32 pokemonBiosGetDp(void*);
void pokemonCheckSetMonohiroi(void*);
u32 pokemonGetStatus(void*, u32, u32, u32);
void pokemonBiosCopy(void*, void*);
void pokemonSetCatchStatus(void*, u32, u32, u32, u32, u32, u32);
s32 pcboxAddPokemon(u32, void*, s32);
void pokemonInitAry(void*, u16);
void itemInitAry(void*, u16);
u32 itemGetStatus(u32, u32, u32, u32);
s32 itemCheckAddItemDataIdAry(void*, u16, u32, u16, u8);
s32 itemDecItemDataIdAry(void*, u16, u32, u32, u32, u16, u8);
s32 itemAddItemDataIdAry(void*, u16, u32, u32, u32, u16, u8, u8);
s32 itemSearchItemDataIdAry(void*, u16, u32, u32, u16);
s32 GScharCmp(void*, void*);
u32 GSmsgGetGSchar(u32);
u32 HSD_Rand(void);
void* heroBiosGetPokemonPtr(Hero*, u16);
void heroMoveDismissMember(u32);
u8 heroMoveIsSmoothFloorLink(void);
u8 peopleCheckFlag(u32, u32, u32);
void peopleSetMotion(u32, u32, u32, u32, u32);
void* peopleGet(u32, u32);
void peopleChangeFollower(u32);
void peopleSetFollowerPtr(void*);
void GSlogWrite(const char*, ...);
void FloorModuleInterface_clear(FloorModuleInterface*);
u32 floorRegisterModule(u32, u32, FloorModuleInterface*);
void heroInit(Hero*);
u32 heroCreateRnd(void);
}

static u32 _hModuleHero;
static FloorModuleInterface _floorModuleHero;

static Hero* _getHero();
static void _heroExitFloor(unsigned int, FloorEnterMode);
static void _heroEnterFloor(unsigned int, FloorEnterMode);

static u32 _heroGetUID() {
    static const char* id = "HERO";
    return (id[0] << 24) | (id[1] << 16) | (id[2] << 8) | id[3];
}

static const char* _heroGetUniqueModuleName() {
    return "hero";
}

static u32 _heroGetStateSize(FloorStateMode) {
    return 0;
}

static void _heroRestoreStateData(FloorStateMode, void*, unsigned long) {
}

static void _heroMakeStateData(FloorStateMode mode, void*, unsigned long) {
    if (mode == 3) {
        ((Hero*)savedataGetStatus(0, 2))->setRestertPos();
    }
}

extern "C" {

u32 heroGetPokeomCount(Hero* hero) {
    u16 i;
    u16 count = 0;
    for (i = 0; i < 6; i++) {
        if (pokemonCheckValid(heroBiosGetPokemonPtr(hero, i))) {
            count++;
        }
    }
    return count;
}

s32 heroGetEmptySlot(Hero* hero) {
    s32 i;
    for (i = 0; i < 6; i++) {
        void* pokemon = heroBiosGetPokemonPtr(hero, i);
        if (!pokemonCheckValid(pokemon)) {
            return i;
        }
        pokemonBiosGetDp(pokemon);
    }
    return -1;
}

s32 heroGetLivingPokemonCount(Hero* hero) {
    s32 i;
    void* pokemon;
    s32 count = 0;
    for (i = 0; i < 6; i++) {
        pokemon = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(pokemon) && (s32)pokemonGetStatus(pokemon, 0, 0x7B, 0) == 0) {
            count++;
        }
    }
    return count;
}

void heroDecPokecoupon(Hero* hero, s32 offset) {
    heroSetStatus(hero, 0xD, heroGetStatus(hero, 0xD, 0) - offset);
    if (offset <= 0) {
        heroSetStatus(hero, 0xE, heroGetStatus(hero, 0xE, 0) - offset);
    }
}

void heroAddPokecoupon(Hero* hero, s32 offset) {
    u32 value = heroGetStatus(hero, 0xD, 0);
    value += offset;
    heroSetStatus(hero, 0xD, value);
    if (offset >= 0) {
        value = heroGetStatus(hero, 0xE, 0);
        value += offset;
        heroSetStatus(hero, 0xE, value);
    }
}

void heroDecPokedoru(Hero* hero, u32 offset) {
    heroSetStatus(hero, 0xC, heroGetStatus(hero, 0xC, 0) - offset);
}

void heroAddPokedoru(Hero* hero, u32 offset) {
    u32 value = heroGetStatus(hero, 0xC, 0);
    value += offset;
    heroSetStatus(hero, 0xC, value);
}

void* heroHizukiItemGetItemAryPtr(Hero* hero, u16* outCount, u16* outMax, u8* outFlag1,
                                  u8* outFlag2) {
    if (outCount != 0) {
        *outCount = 10;
    }
    if (outMax != 0) {
        *outMax = 1;
    }
    if (outFlag1 != 0) {
        *outFlag1 = 0;
    }
    if (outFlag2 != 0) {
        *outFlag2 = 1;
    }
    return (void*)heroGetStatus(hero, 10, 0);
}

void heroCheckSetMonohiroiAllTemotiPokemon(Hero* hero) {
    void* pokemon;
    u16 i;
    for (i = 0; i < 6; i++) {
        pokemon = (void*)heroGetStatus(hero, 3, i);
        if (pokemonCheckValid(pokemon)) {
            pokemonCheckSetMonohiroi(pokemon);
        }
    }
}

void* heroItemGetItemDataIdToItemAryPtr(Hero*, u32, u16*, u16*, u8*, u8*);

s32 heroItemCheckAddItemDataId(Hero* hero, u32 itemID) {
    u16 count = 0;
    u16 max = 0;
    u8 flag;
    void* items = heroItemGetItemDataIdToItemAryPtr(hero, itemID, &count, &max, 0, &flag);
    if (items == 0) {
        return -1;
    }
    return itemCheckAddItemDataIdAry(items, count, itemID, max, flag);
}

s32 heroItemDecItemDataId(Hero* hero, u32 itemID, u32 amount, u32 index) {
    u16 count = 0;
    u16 max = 0;
    u8 flag;
    void* items = heroItemGetItemDataIdToItemAryPtr(hero, itemID, &count, &max, &flag, 0);
    if (items == 0) {
        return -1;
    }
    return itemDecItemDataIdAry(items, count, itemID, amount, index, max, flag);
}

s32 heroItemAddItemDataId(Hero* hero, u32 itemID, u32 amount, u32 index) {
    u16 count = 0;
    u16 max = 0;
    u8 flag1;
    u8 flag2;
    void* items = heroItemGetItemDataIdToItemAryPtr(hero, itemID, &count, &max, &flag1, &flag2);
    if (items == 0) {
        return -1;
    }
    return itemAddItemDataIdAry(items, count, itemID, amount, index, max, flag1, flag2);
}

u32 heroItemCheckHaveItemDataId(Hero* hero, u32 itemID) {
    u16 count = 0;
    u16 max = 0;
    void* items = heroItemGetItemDataIdToItemAryPtr(hero, itemID, &count, &max, 0, 0);
    if (items == 0) {
        return 0;
    }
    return itemSearchItemDataIdAry(items, count, itemID, 0, max) != 0;
}

void* heroItemGetItemKindToItemAryPtr(Hero*, u8, u16*, u16*, u8*, u8*);

void* heroItemGetItemDataIdToItemAryPtr(Hero* hero, u32 itemID, u16* outCount, u16* outMax,
                                        u8* outFlag1, u8* outFlag2) {
    return heroItemGetItemKindToItemAryPtr(hero, (u8)itemGetStatus(0, itemID, 2, 0), outCount,
                                           outMax, outFlag1, outFlag2);
}

void* heroItemGetItemKindToItemAryPtr(Hero* hero, u8 kind, u16* outCount, u16* outMax,
                                      u8* outFlag1, u8* outFlag2) {
    void* items = 0;
    u16 count = 0;
    u16 max = 0;
    u8 flag1 = 0;
    u8 flag2;

    switch (kind) {
    case 1:
        items = (void*)heroGetStatus(hero, 6, 0);
        count = 0x10;
        max = 999;
        flag1 = 0;
        flag2 = 1;
        break;
    case 2:
        items = (void*)heroGetStatus(hero, 4, 0);
        count = 0x1E;
        max = 999;
        flag1 = 0;
        flag2 = 1;
        break;
    case 3:
        items = (void*)heroGetStatus(hero, 8, 0);
        count = 0x2E;
        max = 999;
        flag1 = 1;
        flag2 = 1;
        break;
    case 4:
        items = (void*)heroGetStatus(hero, 7, 0);
        count = 0x40;
        max = 999;
        flag1 = 1;
        flag2 = 0;
        break;
    case 5:
        items = (void*)heroGetStatus(hero, 5, 0);
        count = 0x2B;
        max = 999;
        flag1 = 0;
        flag2 = 0;
        break;
    case 6:
        items = (void*)heroGetStatus(hero, 9, 0);
        count = 3;
        max = 999;
        flag1 = 1;
        flag2 = 0;
        break;
    case 7:
        if (hero == 0) {
            hero = _getHero();
        }
        items = hero->getDisk();
        count = 0x3C;
        max = 999;
        flag1 = 1;
        flag2 = 0;
        break;
    }
    if (outCount != 0) {
        *outCount = count;
    }
    if (outMax != 0) {
        *outMax = max;
    }
    if (outFlag1 != 0) {
        *outFlag1 = flag1;
    }
    if (outFlag2 != 0) {
        *outFlag2 = flag2;
    }
    return items;
}

u32 heroIsMinePokemon(Hero* hero, void* pokemon) {
    u32 heroRnd = heroGetStatus(hero, 2, 0);
    u32 heroName = heroGetStatus(hero, 1, 0);
    u32 pokemonRnd = pokemonGetStatus(pokemon, 0, 0x75, 0);
    u32 pokemonName = pokemonGetStatus(pokemon, 0, 0x76, 0);
    if (heroRnd != pokemonRnd) {
        return 0;
    }
    return GScharCmp((void*)heroName, (void*)pokemonName) ? 0 : 1;
}

u8 heroAddPokemon(Hero* hero, void* pokemon);

s32 heroGetPokemon(Hero* hero, void* pokemon, u8 allowPCBox) {
    u8 copy[0xC8];
    u8 slot;
    s16 result;

    if (pokemon == 0) {
        return 6;
    }
    pokemonBiosCopy(copy, pokemon);
    slot = heroAddPokemon(hero, copy);
    result = (s16)slot;
    if (slot >= 6) {
        if (allowPCBox == 0) {
            return -2;
        }
        return pcboxAddPokemon(0, copy, -1) == 1 ? -1 : -2;
    }
    return result;
}

s32 heroCatchPokemon(Hero* hero, void* pokemon, u32 arg3, u32 arg4, u8 allowPCBox) {
    u8 copy[0xC8];
    u8 slot;
    s16 result;
    u8 origin;
    u8 sex;
    u32 rnd;
    u32 name;

    if (pokemon == 0) {
        return 6;
    }
    origin = pokemonGetStatus(pokemon, 0, 0x7A, 0);
    sex = heroGetStatus(hero, 0xB, 0);
    rnd = heroGetStatus(hero, 2, 0);
    name = heroGetStatus(hero, 1, 0);
    pokemonBiosCopy(copy, pokemon);
    pokemonSetCatchStatus(copy, arg3, origin, arg4, sex, rnd, name);
    slot = heroAddPokemon(hero, copy);
    result = (s16)slot;
    if (slot >= 6) {
        if (allowPCBox == 0) {
            return -2;
        }
        return pcboxAddPokemon(0, copy, -1) == 1 ? -1 : -2;
    }
    return result;
}

u8 heroAddPokemon(Hero* hero, void* pokemon) {
    u8 i;

    if (pokemon == 0) {
        return 6;
    }
    for (i = 0; i < 6; i++) {
        if (pokemonCheckValid((void*)heroGetStatus(hero, 3, i)) != 1) {
            if (hero == 0) {
                hero = _getHero();
            }
            hero->setPokemon((Pokemon*)pokemon, i);
            return i;
        }
    }
    return 6;
}

u32 heroCheckValid(Hero* hero) {
    u16 empty = 0;
    if (GScharCmp((void*)heroGetStatus(hero, 1, 0), &empty) == 0) {
        return 0;
    }
    return heroGetStatus(hero, 0xB, 0) != 2;
}

void heroCreate(Hero* hero, u32 name, u8 sex) {
    heroInit(hero);
    u32 rnd = heroCreateRnd();
    heroSetStatus(hero, 2, rnd);
    heroSetStatus(hero, 1, name);
    heroSetStatus(hero, 0xB, sex);
    heroSetStatus(hero, 0x17, GSmsgGetGSchar(1));
    if (hero == 0) {
        Hero::getHeroPtr();
    }
}

u32 heroCreateRnd(void) {
    u16 low = HSD_Rand();
    u32 high = HSD_Rand();
    return (high << 16) | low;
}

void heroInit(Hero* hero) {
    u16 emptyName = 0;

    if (hero == 0) {
        hero = Hero::getHeroPtr();
    }
    heroSetStatus(hero, 1, (u32)&emptyName);
    heroSetStatus(hero, 2, 0);
    pokemonInitAry((void*)heroGetStatus(hero, 3, 0), 6);
    itemInitAry((void*)heroGetStatus(hero, 4, 0), 0x1E);
    itemInitAry((void*)heroGetStatus(hero, 5, 0), 0x2B);
    itemInitAry((void*)heroGetStatus(hero, 6, 0), 0x10);
    itemInitAry((void*)heroGetStatus(hero, 7, 0), 0x40);
    itemInitAry((void*)heroGetStatus(hero, 8, 0), 0x2E);
    itemInitAry((void*)heroGetStatus(hero, 9, 0), 3);
    itemInitAry(hero->getDisk(), 0x3C);
    heroSetStatus(hero, 0xB, 2);
    heroSetStatus(hero, 0xC, 0);
    heroSetStatus(hero, 0xD, 0);
    heroSetStatus(hero, 0xE, 0);
    heroSetStatus(hero, 0xF, 1);
    heroSetStatus(hero, 0x10, 1);
    heroSetStatus(hero, 0x11, 1);
    heroSetStatus(hero, 0x12, 1);
    heroSetStatus(hero, 0x13, 1);
    heroSetStatus(hero, 0x14, 1);
    heroSetStatus(hero, 0x15, 1);
    heroSetStatus(hero, 0x16, 1);
    heroSetStatus(hero, 0x17, (u32)&emptyName);
    heroSetStatus(hero, 0x18, 0);
    itemInitAry((void*)heroGetStatus(hero, 10, 0), 10);
    heroSetStatus(hero, 0x19, 0);
    hero->setHeroStyle(0, false);
    hero->setFollowerID(0);
    if (_hModuleHero == 0) {
        FloorModuleInterface_clear(&_floorModuleHero);
        _floorModuleHero.enterFloor = _heroEnterFloor;
        _floorModuleHero.exitFloor = _heroExitFloor;
        _floorModuleHero.getModuleName = _heroGetUniqueModuleName;
        _floorModuleHero.makeStateData = _heroMakeStateData;
        _floorModuleHero.restoreStateData = _heroRestoreStateData;
        _floorModuleHero.getStateSize = _heroGetStateSize;
        _floorModuleHero.getUID = _heroGetUID;
        _hModuleHero = floorRegisterModule(0x19, 0, &_floorModuleHero);
    }
}

void heroSetStatus(Hero* hero, u32 selector, u32 value) {
    extern void heroBiosSetNamePtr(Hero*, u32);
    extern void heroBiosSetRnd(Hero*, u32);
    extern void heroBiosSetSexDataId(Hero*, u8);
    extern void heroBiosSetPokedoru(Hero*, u32);
    extern void heroBiosSetPokecoupon(Hero*, u32);
    extern void heroBiosSetPokecouponAll(Hero*, u32);
    extern void heroBiosSetBadge01Flag(Hero*, u8);
    extern void heroBiosSetBadge02Flag(Hero*, u8);
    extern void heroBiosSetBadge03Flag(Hero*, u8);
    extern void heroBiosSetBadge04Flag(Hero*, u8);
    extern void heroBiosSetBadge05Flag(Hero*, u8);
    extern void heroBiosSetBadge06Flag(Hero*, u8);
    extern void heroBiosSetBadge07Flag(Hero*, u8);
    extern void heroBiosSetBadge08Flag(Hero*, u8);
    extern void heroBiosSetHizukiNamePtr(Hero*, u32);
    extern void heroBiosSetHizukiFlag(Hero*, u8);
    extern void heroBiosSetHomePlace(Hero*, u8);

    if ((u16)selector == 0 || (u16)selector >= 0x1A) {
        return;
    }
    if (hero == 0) {
        hero = (Hero*)savedataGetStatus(0, 0);
        if (hero == 0) {
            return;
        }
        hero = (Hero*)savedataGetStatus(hero, 2);
        if (hero == 0) {
            return;
        }
    }
    switch ((u16)selector) {
    case 1:
        heroBiosSetNamePtr(hero, value);
        break;
    case 2:
        heroBiosSetRnd(hero, value);
        break;
    case 11:
        heroBiosSetSexDataId(hero, value);
        break;
    case 12:
        heroBiosSetPokedoru(hero, value);
        break;
    case 13:
        heroBiosSetPokecoupon(hero, value);
        break;
    case 14:
        heroBiosSetPokecouponAll(hero, value);
        break;
    case 15:
        heroBiosSetBadge01Flag(hero, value != 0);
        break;
    case 16:
        heroBiosSetBadge02Flag(hero, value != 0);
        break;
    case 17:
        heroBiosSetBadge03Flag(hero, value != 0);
        break;
    case 18:
        heroBiosSetBadge04Flag(hero, value != 0);
        break;
    case 19:
        heroBiosSetBadge05Flag(hero, value != 0);
        break;
    case 20:
        heroBiosSetBadge06Flag(hero, value != 0);
        break;
    case 21:
        heroBiosSetBadge07Flag(hero, value != 0);
        break;
    case 22:
        heroBiosSetBadge08Flag(hero, value != 0);
        break;
    case 23:
        heroBiosSetHizukiNamePtr(hero, value);
        break;
    case 24:
        heroBiosSetHizukiFlag(hero, value != 0);
        break;
    case 25:
        heroBiosSetHomePlace(hero, value);
        break;
    }
}

u32 heroGetStatus(Hero* hero, u32 selector, u16 index) {
    extern u32 heroBiosGetNamePtr(Hero*);
    extern u32 heroBiosGetRnd(Hero*);
    extern u32 heroBiosGetItemNormalPtr(Hero*, u16);
    extern u32 heroBiosGetExtraItemPtr(Hero*, u16);
    extern u32 heroBiosGetItemBallPtr(Hero*, u16);
    extern u32 heroBiosGetItemSkillPtr(Hero*, u16);
    extern u32 heroBiosGetItemSeedPtr(Hero*, u16);
    extern u32 heroBiosGetItemKoronPtr(Hero*, u16);
    extern u32 heroBiosGetHizukiItemPtr(Hero*, u16);
    extern u8 heroBiosGetSexDataId(Hero*);
    extern u32 heroBiosGetPokedoru(Hero*);
    extern u32 heroBiosGetPokecoupon(Hero*);
    extern u32 heroBiosGetPokecouponAll(Hero*);
    extern u8 heroBiosGetBadge01Flag(Hero*);
    extern u8 heroBiosGetBadge02Flag(Hero*);
    extern u8 heroBiosGetBadge03Flag(Hero*);
    extern u8 heroBiosGetBadge04Flag(Hero*);
    extern u8 heroBiosGetBadge05Flag(Hero*);
    extern u8 heroBiosGetBadge06Flag(Hero*);
    extern u8 heroBiosGetBadge07Flag(Hero*);
    extern u8 heroBiosGetBadge08Flag(Hero*);
    extern u32 heroBiosGetHizukiNamePtr(Hero*);
    extern u8 heroBiosGetHizukiFlag(Hero*);
    extern u8 heroBiosGetHomePlace(Hero*);

    if ((u16)selector == 0 || (u16)selector >= 0x1A) {
        return 0;
    }
    if (hero == 0) {
        hero = _getHero();
    }
    switch ((u16)selector) {
    case 1:
        return heroBiosGetNamePtr(hero);
    case 2:
        return heroBiosGetRnd(hero);
    case 3:
        return (u32)heroBiosGetPokemonPtr(hero, index);
    case 4:
        return heroBiosGetItemNormalPtr(hero, index);
    case 5:
        return heroBiosGetExtraItemPtr(hero, index);
    case 6:
        return heroBiosGetItemBallPtr(hero, index);
    case 7:
        return heroBiosGetItemSkillPtr(hero, index);
    case 8:
        return heroBiosGetItemSeedPtr(hero, index);
    case 9:
        return heroBiosGetItemKoronPtr(hero, index);
    case 10:
        return heroBiosGetHizukiItemPtr(hero, index);
    case 11:
        return heroBiosGetSexDataId(hero);
    case 12:
        return heroBiosGetPokedoru(hero);
    case 13:
        return heroBiosGetPokecoupon(hero);
    case 14:
        return heroBiosGetPokecouponAll(hero);
    case 15:
        return heroBiosGetBadge01Flag(hero);
    case 16:
        return heroBiosGetBadge02Flag(hero);
    case 17:
        return heroBiosGetBadge03Flag(hero);
    case 18:
        return heroBiosGetBadge04Flag(hero);
    case 19:
        return heroBiosGetBadge05Flag(hero);
    case 20:
        return heroBiosGetBadge06Flag(hero);
    case 21:
        return heroBiosGetBadge07Flag(hero);
    case 22:
        return heroBiosGetBadge08Flag(hero);
    case 23:
        return heroBiosGetHizukiNamePtr(hero);
    case 24:
        return heroBiosGetHizukiFlag(hero);
    case 25:
        return heroBiosGetHomePlace(hero);
    }
    return 0;
}

u32 heroGetObjID(u8 style) {
    Hero* hero = Hero::getHeroPtr();
    if (hero == 0) {
        return 0x16C90400;
    }
    return hero->getHeroObjID(style, -1);
}

}

static Hero* _getHero() {
    Hero* hero = (Hero*)savedataGetStatus(0, 0);
    if (hero == 0) {
        return 0;
    }
    hero = (Hero*)savedataGetStatus(hero, 2);
    if (hero == 0) {
        return 0;
    }
    return hero;
}

static void _heroExitFloor(unsigned int, FloorEnterMode mode) {
    if (mode != 1 && !heroMoveIsSmoothFloorLink()) {
        if (!peopleCheckFlag(0, 0x64, 0x80000000)) {
            peopleSetMotion(0, 0x64, 3, 0, 1);
        }
        peopleSetMotion(0, 0x65, 3, 0, 1);
        peopleSetMotion(0, 0x68, 3, 0, 1);
        peopleSetMotion(0, 0x69, 3, 0, 1);
    }
}

static void _heroEnterFloor(unsigned int, FloorEnterMode) {
}

extern "C" {

void heroSetFollower(u32 groupID, u32 resID, u32 objID);

void heroSetFollowerWithID(u8 id, u8 variant) {
    Hero* hero = Hero::getHeroPtr();
    hero->setFollowerID(id);
    hero->setFollowerModelLevel(0);
    switch (id) {
    case 0:
        heroMoveDismissMember(1);
        heroMoveDismissMember(2);
        heroMoveDismissMember(3);
        break;
    case 1:
        switch (variant) {
        case 0:
            heroSetFollower(0, 0x65, 0x16C70400);
            return;
        case 1:
            heroSetFollower(0, 0x65, 0x16C80400);
            hero->setFollowerModelLevel(1);
            return;
        }
    case 2:
        heroSetFollower(0, 0x68, 0x195B0400);
        break;
    case 3:
        heroSetFollower(0, 0x69, 0x19540400);
        break;
    }
}

void heroSetFollower(u32 groupID, u32 resID, u32 objID) {
    Hero* hero = Hero::getHeroPtr();
    hero->setFollowerGrpID(groupID);
    hero->setFollowerResID(resID);
    hero->setFollowerObjID(objID);
    peopleChangeFollower(objID);
    void* people = peopleGet(groupID, resID);
    if (people == 0) {
        GSlogWrite("Illegal ID!\n");
    } else {
        peopleSetFollowerPtr(people);
        if (objID == 0x16C80400) {
            hero->setFollowerModelLevel(1);
        } else {
            hero->setFollowerModelLevel(0);
        }
    }
}

u8 heroIsPlayerPeople(u32 groupID, u32 resID) {
    if (groupID == 0 && resID == 0x64) {
        return 1;
    }
    Hero* hero = Hero::getHeroPtr();
    if (groupID == hero->getFollowerGrpID() && resID == hero->getFollowerResID()) {
        return 1;
    }
    return 0;
}

}
