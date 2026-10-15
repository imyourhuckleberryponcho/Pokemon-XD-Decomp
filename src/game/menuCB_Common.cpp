#include <dolphin/types.h>

// Menu callbacks were built without the peephole optimizer.
#pragma peephole off

struct CBTrainer {
    u8 unk0[0x24];
    s32 gba;
    u8 unk28[0x1320 - 0x28];
};

struct CB {
    u8 unk0[0x4C98];
    CBTrainer trainers[4];
};

struct MenuSpriteVal {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
};

struct MenuWindow {
    u8 unk0[0x54];
    s16 unk54;
    s16 unk56;
    s32 unk58;
    s16 unk5C;
    s16 unk5E;
};

struct MenuStackEntry {
    s32 id;
    s32 cursor;
};

// Stack of open menus (id + saved cursor), the current menu at stack[depth].
struct MenuStack {
    MenuStackEntry stack[8];
    s32 depth;
};

extern "C" {

extern CB _CB;

s32 winMsgCheck(void);
void winMsgClose(s32);
void winMsgOpen(s32, s32 msgID, s32, s32);
BOOL menuCBTrainerBios_GetHomePlace(CBTrainer* trainer);
bool gbaCommandIsConnected(s32 gba);
MenuSpriteVal* menuSpriteBiosGetValPtr(s32 id);
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
        s32 gba = _CB.trainers[i].gba;
        if (gba != 0 && menuCBTrainerBios_GetHomePlace(&_CB.trainers[i]) && !gbaCommandIsConnected(gba)) {
            return gba;
        }
    }
    return 0;
}

void menuCB_SetSprite(MenuWindow* window, s32 id) {
    MenuSpriteVal* val = menuSpriteBiosGetValPtr(id);
    window->unk54 = val->unk4;
    window->unk56 = val->unk6;
    window->unk58 = val->unk8;
    window->unk5C = val->unk0;
    window->unk5E = val->unk2;
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
