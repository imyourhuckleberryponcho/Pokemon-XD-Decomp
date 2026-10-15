#include <dolphin/types.h>

#pragma peephole off

struct MenuData {
    u8 type : 3;
    u8 unk0 : 5;
    u8 unk1[2];
    u8 dispMax;
    u8 unk4[4];
    s16 x;
    s16 y;
    u8 unkC[0x1C - 0xC];
};

struct MenuItem {
    u8 selectFlag : 1;
    u8 unk0 : 7;
    u8 unk1[5];
    s16 x;
    s16 y;
    u8 unkA[4];
    s16 spriteId;
    u8 unk10[0x1C - 0x10];
};

struct MenuSe {
    u16 sndId[6];
};

struct MenuSpriteVal {
    u8 unk0[0xC];
};

struct MenuSprite {
    u8 unk0[8];
    MenuSpriteVal val[5];
    u8 unk44[4];
};

struct MenuSeq {
    u8 unk0[0xC];
};

extern "C" {

extern MenuSe* menu_se;
extern u32* menu_se_number;
extern MenuSeq _menu_seq[];
extern u32 _menu_seq_number;
extern MenuSprite _menu_sprite[];
extern u32 _menu_sprite_number;
extern MenuData _menu_data[];
extern u32 _menu_data_number;
extern MenuItem _menu_item[];
extern MenuItem _menu_itemmx[];
extern MenuItem _menu_item_tool[];
extern MenuItem _menu_item_debug[];
extern MenuItem _menu_item_pda[];
extern MenuItem _menu_itembt[];
extern MenuItem _menu_item_xd[];

MenuItem* windowGetCursorToItem(void* window);
s32 pokecoloGetLanguage(void);
s32 dbgMenuGetLayerID(void);
MenuSprite* menuSpriteBiosGetPtr(u32 id);
MenuSpriteVal* menuSpriteBiosGetValPtr(MenuSprite* sprite);
MenuItem* menuItemBiosGetPtr(s32 menuID, u32 index);
MenuData* menuDataBiosGetPtr(s32 menuID);

s32 menuBiosGetCursorSize(void* window) {
    MenuItem* item = windowGetCursorToItem(window);
    menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(item->spriteId));
    s32 size = 0;
    switch (item->spriteId) {
    case 0x7D:
    case 0xBE:
        size = 0x147;
        break;
    case 0xC1:
    case 0xC2:
        size = 0x14D;
        break;
    }
    return size;
}

u16 menuSeBiosGetSndId(MenuSe* se, u8 kind) {
    u16 sndId = 0;
    switch (kind) {
    case 1:
        sndId = se->sndId[2];
        break;
    case 2:
        sndId = se->sndId[3];
        break;
    case 3:
        sndId = se->sndId[4];
        break;
    case 4:
        sndId = se->sndId[0];
        break;
    case 5:
        sndId = se->sndId[1];
        break;
    case 6:
        sndId = se->sndId[5];
        break;
    }
    return sndId;
}

MenuSe* menuSeBiosGetPtr(u32 id) {
    if (menu_se == NULL) {
        return 0;
    }
    if (id >= *menu_se_number) {
        return 0;
    }
    return &menu_se[id];
}

MenuSeq* menuSeqBiosGetPtr(u32 id) {
    if (id >= _menu_seq_number) {
        return 0;
    }
    return &_menu_seq[id];
}

MenuSpriteVal* menuSpriteBiosGetValPtr(MenuSprite* sprite) {
    s32 index;
    switch (pokecoloGetLanguage()) {
    case 2:
        index = 0;
        break;
    case 3:
        index = 1;
        break;
    case 4:
        index = 2;
        break;
    case 5:
        index = 3;
        break;
    case 6:
        index = 4;
        break;
    default:
        index = 0;
        break;
    }
    return &sprite->val[index];
}

MenuSprite* menuSpriteBiosGetPtr(u32 id) {
    if (id >= _menu_sprite_number) {
        return 0;
    }
    return &_menu_sprite[id];
}

void menuItemBiosSetXY(s32 menuID, u32 index, s16 x, s16 y) {
    MenuItem* item = menuItemBiosGetPtr(menuID, index);
    if (item != NULL) {
        item->x = x;
        item->y = y;
    }
}

bool menuItemBiosGetSelectFlag(s32 menuID, u32 index) {
    MenuItem* item = menuItemBiosGetPtr(menuID, index);
    if (item != NULL) {
        return item->selectFlag != 0;
    }
    return false;
}

void menuItemBiosSetSelectFlag(s32 menuID, u32 index, bool flag) {
    MenuItem* item = menuItemBiosGetPtr(menuID, index);
    if (item != NULL) {
        item->selectFlag = flag;
    }
}

s32 menuItemBiosGetLayerID(s32 menuID) {
    if (menuDataBiosGetPtr(menuID)->type == 3) {
        return dbgMenuGetLayerID();
    }
    return 7;
}

MenuItem* menuItemBiosGetPtr(s32 menuID, u32 index) {
    u8 type = menuDataBiosGetPtr(menuID)->type;
    if (type == 0) {
        return &_menu_item[index];
    } else if (type == 1) {
        return &_menu_itemmx[index];
    } else if (type == 2) {
        return &_menu_item_tool[index];
    } else if (type == 3) {
        return &_menu_item_debug[index];
    } else if (type == 4) {
        return &_menu_item_pda[index];
    } else if (type == 5) {
        return &_menu_itembt[index];
    } else if (type == 6) {
        return &_menu_item_xd[index];
    }
    return 0;
}

void menuDataBiosGetXY(s32 menuID, s16* x, s16* y) {
    MenuData* data = menuDataBiosGetPtr(menuID);
    if (x != NULL) {
        *x = data->x;
    }
    if (y != NULL) {
        *y = data->y;
    }
}

void menuDataBiosSetXY(s32 menuID, s16 x, s16 y) {
    MenuData* data = menuDataBiosGetPtr(menuID);
    data->x = x;
    data->y = y;
}

u8 menuDataBiosGetDispMax(s32 menuID) { return menuDataBiosGetPtr(menuID)->dispMax; }

MenuData* menuDataBiosGetPtr(s32 menuID) {
    if (menuID < 0) {
        menuID = 0;
    }
    if (menuID >= _menu_data_number) {
        menuID = 1;
    }
    return &_menu_data[menuID];
}

}
