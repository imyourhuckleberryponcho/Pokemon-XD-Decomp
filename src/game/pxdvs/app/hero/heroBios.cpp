#include <dolphin/types.h>

struct Item {
    u16 itemDataId;
    u16 num;
};

struct Pokemon {
    u8 unk0[0xC4];
};

struct Hero {
    u16 name[11];
    u8 unk16[0x2C - 0x16];
    u32 rnd;
    Pokemon pokemon[6];
    Item itemNormal[30];
    Item extraItem[43];
    Item itemBall[16];
    Item itemSkill[64];
    Item itemSeed[46];
    Item itemKoron[3];
    u8 unk7F0[0x8E0 - 0x7F0];
    u8 sexDataId;
    u8 homePlace;
    u8 unk8E2[2];
    s32 pokedoru;
    s32 pokecoupon;
    s32 pokecouponAll;
    u8 badge01Flag;
    u8 badge02Flag;
    u8 badge03Flag;
    u8 badge04Flag;
    u8 badge05Flag;
    u8 badge06Flag;
    u8 badge07Flag;
    u8 badge08Flag;
    u8 hizukiFlag;
    u8 unk8F9;
    Item hizukiItem[10];
    u16 hizukiName[11];
    u8 meetDarkPokemonCount;
    u8 unk939[0x978 - 0x939];
};

extern "C" {

void GScharLenCpy(u16* dst, const u16* src, s32 len);
void* memcpy(void* dst, const void* src, u32 n);

void heroBiosSetMeetDarkPokemonCount(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->meetDarkPokemonCount = value;
    }
}

u8 heroBiosGetMeetDarkPokemonCount(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->meetDarkPokemonCount;
}

void heroBiosSetHomePlace(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->homePlace = value;
    }
}

u8 heroBiosGetHomePlace(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->homePlace;
}

u8 heroBiosGetHizukiFlag(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->hizukiFlag;
}

void heroBiosSetHizukiFlag(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->hizukiFlag = value;
    }
}

s32 heroBiosGetPokecouponAll(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->pokecouponAll;
}

void heroBiosSetPokecouponAll(Hero* hero, s32 value) {
    if (hero != NULL) {
        if (value < 0) {
            value = 0;
        }
        if (value > 9999999) {
            value = 9999999;
        }
        hero->pokecouponAll = value;
    }
}

s32 heroBiosGetPokecoupon(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->pokecoupon;
}

void heroBiosSetPokecoupon(Hero* hero, s32 value) {
    if (hero != NULL) {
        if (value < 0) {
            value = 0;
        }
        if (value > 9999999) {
            value = 9999999;
        }
        hero->pokecoupon = value;
    }
}

s32 heroBiosGetPokedoru(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->pokedoru;
}

void heroBiosSetPokedoru(Hero* hero, s32 value) {
    if (hero != NULL) {
        if (value < 0) {
            value = 0;
        }
        if (value > 9999999) {
            value = 9999999;
        }
        hero->pokedoru = value;
    }
}

void heroBiosSetHizukiNamePtr(Hero* hero, const u16* name) {
    if (hero != NULL && name != NULL) {
        GScharLenCpy(hero->hizukiName, name, 11);
    }
}

u16* heroBiosGetHizukiNamePtr(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->hizukiName;
}

u8 heroBiosGetBadge08Flag(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->badge08Flag;
}

u8 heroBiosGetBadge07Flag(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->badge07Flag;
}

u8 heroBiosGetBadge06Flag(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->badge06Flag;
}

u8 heroBiosGetBadge05Flag(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->badge05Flag;
}

u8 heroBiosGetBadge04Flag(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->badge04Flag;
}

u8 heroBiosGetBadge03Flag(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->badge03Flag;
}

u8 heroBiosGetBadge02Flag(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->badge02Flag;
}

u8 heroBiosGetBadge01Flag(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->badge01Flag;
}

void heroBiosSetBadge08Flag(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->badge08Flag = value;
    }
}

void heroBiosSetBadge07Flag(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->badge07Flag = value;
    }
}

void heroBiosSetBadge06Flag(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->badge06Flag = value;
    }
}

void heroBiosSetBadge05Flag(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->badge05Flag = value;
    }
}

void heroBiosSetBadge04Flag(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->badge04Flag = value;
    }
}

void heroBiosSetBadge03Flag(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->badge03Flag = value;
    }
}

void heroBiosSetBadge02Flag(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->badge02Flag = value;
    }
}

void heroBiosSetBadge01Flag(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->badge01Flag = value;
    }
}

u8 heroBiosGetSexDataId(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->sexDataId;
}

void heroBiosSetSexDataId(Hero* hero, u8 value) {
    if (hero != NULL) {
        hero->sexDataId = value;
    }
}

void heroBiosSetRnd(Hero* hero, u32 value) {
    if (hero != NULL) {
        hero->rnd = value;
    }
}

void heroBiosSetNamePtr(Hero* hero, const u16* name) {
    if (hero == NULL || name == NULL) {
        return;
    }
    GScharLenCpy(hero->name, name, 11);
}

Item* heroBiosGetHizukiItemPtr(Hero* hero, u16 index) {
    if (hero == NULL) {
        return 0;
    }
    if (index >= 10) {
        return 0;
    }
    return &hero->hizukiItem[index];
}

Item* heroBiosGetItemKoronPtr(Hero* hero, u16 index) {
    if (hero == NULL) {
        return 0;
    }
    if (index >= 3) {
        return 0;
    }
    return &hero->itemKoron[index];
}

Item* heroBiosGetItemSeedPtr(Hero* hero, u16 index) {
    if (hero == NULL) {
        return 0;
    }
    if (index >= 46) {
        return 0;
    }
    return &hero->itemSeed[index];
}

Item* heroBiosGetItemSkillPtr(Hero* hero, u16 index) {
    if (hero == NULL) {
        return 0;
    }
    if (index >= 64) {
        return 0;
    }
    return &hero->itemSkill[index];
}

Item* heroBiosGetItemBallPtr(Hero* hero, u16 index) {
    if (hero == NULL) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    return &hero->itemBall[index];
}

Item* heroBiosGetExtraItemPtr(Hero* hero, u16 index) {
    if (hero == NULL) {
        return 0;
    }
    if (index >= 43) {
        return 0;
    }
    return &hero->extraItem[index];
}

Item* heroBiosGetItemNormalPtr(Hero* hero, u16 index) {
    if (hero == NULL) {
        return 0;
    }
    if (index >= 30) {
        return 0;
    }
    return &hero->itemNormal[index];
}

Pokemon* heroBiosGetPokemonPtr(Hero* hero, u16 index) {
    if (hero == NULL) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return &hero->pokemon[index];
}

u32 heroBiosGetRnd(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->rnd;
}

u16* heroBiosGetNamePtr(Hero* hero) {
    if (hero == NULL) {
        return 0;
    }
    return hero->name;
}

void heroBiosCopy(Hero* dst, Hero* src) {
    if (dst != NULL && src != NULL) {
        memcpy(dst, src, sizeof(Hero));
    }
}

}
