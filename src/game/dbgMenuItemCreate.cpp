#include <dolphin/types.h>

#pragma peephole off
#pragma dont_inline on

struct WindowKeyInfo {
    u8 unk0[6];
    u16 repeat;
};

struct Window {
    u8 unk0[0x9E];
    s16 cursor;
};

extern "C" {

WindowKeyInfo* windowGetKeyInfo(void);
extern s32* item_data_index_number;
bool itemDataCheckValid(u16 id);
s32 menuOpen(s32 menuID, s32);
void menuClose(s32 menuID);
void menuCloseCustom(s32 menuID, s32, s32);
void menuCloseSync(s32 menuID, s32);
void heroItemAddItemDataId(void* hero, u16 id, u16 num, s32);

static BOOL initFlag;
static s32 Num;
static s32 ItemID;

static void nbItemCtrl(void) {
    WindowKeyInfo* key = windowGetKeyInfo();
    if (key->repeat & 8) {
        if (++Num > 999) {
            Num = 999;
        }
    }
    if (key->repeat & 0x400) {
        if ((Num += 10) > 999) {
            Num = 999;
        }
    }
    if (key->repeat & 4) {
        if (--Num < 0) {
            Num = 0;
        }
    }
    if (key->repeat & 0x200) {
        if ((Num -= 10) < 0) {
            Num = 0;
        }
    }
}

static void itemNameCtrl(void) {
    WindowKeyInfo* key = windowGetKeyInfo();
    if (key->repeat & 8) {
        if (++ItemID >= *item_data_index_number) {
            ItemID = *item_data_index_number - 1;
        }
    }
    if (key->repeat & 0x400) {
        if ((ItemID += 10) >= *item_data_index_number) {
            ItemID = *item_data_index_number - 1;
        }
    }
    if (key->repeat & 4) {
        if (--ItemID < 0) {
            ItemID = 0;
        }
    }
    if (key->repeat & 0x200) {
        if ((ItemID -= 10) < 0) {
            ItemID = 0;
        }
    }
}

s32 menuDbgItemCreateCursor(Window* window) {
    WindowKeyInfo* key = windowGetKeyInfo();
    if (key->repeat & 1) {
        if (--window->cursor < 0) {
            window->cursor = 0;
        }
    }
    if (key->repeat & 2) {
        if (++window->cursor > 1) {
            window->cursor = 1;
        }
    }
    switch (window->cursor) {
    case 0:
        itemNameCtrl();
        break;
    case 1:
        nbItemCtrl();
        break;
    }
    return 0;
}

void menuDbgItemCreate(void) {
    if (!initFlag) {
        ItemID = 1;
        initFlag = TRUE;
    }
    Num = 1;
    for (;;) {
        if (menuOpen(0x24, 1) == -1) {
            break;
        }
        if (itemDataCheckValid(ItemID) && Num >= 1 && Num <= 999) {
            s32 answer = menuOpen(0x55, 1);
            menuCloseCustom(0x55, 0, 1);
            if (answer == 0) {
                heroItemAddItemDataId(0, ItemID, Num, -1);
            }
        }
    }
    menuClose(0x24);
    menuCloseSync(0x24, 1);
}

}
