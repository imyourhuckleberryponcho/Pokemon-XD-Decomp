#include <dolphin/types.h>
#include <game/shared/menu_work.h>
#include <game/menuCBWork.h>

#pragma peephole off

struct MenuSpriteVal {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
};

struct MenuStackEntry {
    s32 id;
    s32 cursor;
};

struct MenuStack {
    MenuStackEntry stack[8];
    s32 depth;
};

extern "C" {

extern _MENUCBWORK _CB;

s32 winMsgCheck(void);
void winMsgClose(s32);
void winMsgOpen(s32, s32 msgID, s32, s32);
BOOL menuCBTrainerBios_GetHomePlace(MenuCBTrainer* trainer);
bool gbaCommandIsConnected(s32 gba);
MenuSpriteVal* menuSpriteBiosGetValPtr(void* sprite);
s32 windowGetActiveID(void);
void menuCloseCustom(s32 menuID, s32, s32);

static MenuStack _CBC;

s32 menuCB_CurrentMenuID(void);
s32 menuCB_MenuPop(void);

s32 menuCB_MessageDispCheck(void) {
    return winMsgCheck();
}

void menuCB_MessageDispOff(void) {
    winMsgClose(0);
}

void menuCB_MessageDispOn(s32 msgID, s32 arg1) {
    winMsgOpen(7, msgID, arg1, 0);
}

s32 menuCB_GetDisconnectedGBA(void) {
    u32 i;
    for (i = 0; i < 4; i++) {
        s32 gba = _CB.trainerOrg[i].controllerId;
        if (gba != 0 && menuCBTrainerBios_GetHomePlace(&_CB.trainerOrg[i]) && !gbaCommandIsConnected(gba)) {
            return gba;
        }
    }
    return 0;
}

void menuCB_SetSprite(tagSPRITE_WORK* window, void* sprite) {
    MenuSpriteVal* val = menuSpriteBiosGetValPtr(sprite);
    window->w = val->unk4;
    window->h = val->unk6;
    window->unk58 = val->unk8;
    window->sx = val->unk0;
    window->sy = val->unk2;
}

s32 menuCB_MenuRollback(s32 id) {
    menuCB_MenuPop();
    while (id != menuCB_CurrentMenuID()) {
        if (_CBC.depth == 0) {
            break;
        }
        _CBC.depth--;
    }
    return menuCB_CurrentMenuID();
}

s32 menuCB_MenuPop(void) {
    if (windowGetActiveID() == menuCB_CurrentMenuID()) {
        menuCloseCustom(menuCB_CurrentMenuID(), 0, 0);
    }
    _CBC.stack[_CBC.depth].cursor = 0;
    if (_CBC.depth == 0) {
        return -1;
    }
    _CBC.depth--;
    return menuCB_CurrentMenuID();
}

void menuCB_MenuPush(s32 id) {
    if (_CBC.depth < sizeof(_CBC.stack) / sizeof(_CBC.stack[0])) {
        _CBC.depth++;
        _CBC.stack[_CBC.depth].id = id;
        _CBC.stack[_CBC.depth].cursor = 0;
    }
}

s32 menuCB_CurrentMenuID(void) {
    return _CBC.stack[_CBC.depth].id;
}

void menuCB_InitMenu(s32 id) {
    s32 i;
    for (i = 0; i < 8; i++) {
        _CBC.stack[i].id = 0;
        _CBC.stack[i].cursor = 0;
    }
    _CBC.stack[0].id = id;
    _CBC.depth = 0;
}

}
