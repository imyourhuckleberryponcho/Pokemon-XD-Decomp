#include <dolphin/types.h>

#pragma peephole off

struct MenuWindow {
    u8 unk0;
    s8 state;
    s8 seqSet;
    u8 unk3;
    void* seq;
    u8 unk8[0x60];
    s32* data;
};

struct MenuItem {
    u8 unk0[6];
    s16 id;
    u8 unk8[0x5F];
    u8 alpha;
};

struct UndertakerData {
    u8 unk0[0x24];
    u32 flag;
};

extern "C" {

extern UndertakerData* undertakerdata;

bool menuIsCheck(s32 menuID);
void menuClose(s32 menuID);
void menuCloseSync(s32 menuID, s32);
void menuOpenCustom(s32 menuID, ...);
s32 winSpriteGetLayerID(MenuWindow* window, MenuItem* item);
void* GSgfxLayerFindByID(s32 layer);
u32 GSfloorGetCurrent(void);
void* floorDataBiosGetPtr(u32 id);
u8 floorDataBiosGetFloorKind(void* data);
bool GSflagTest(u32 flag);
void winSpriteSetDisp(MenuItem* item, s32 disp);
double cos(double x);
f32 timeGetLastFrameSec(void);
void GSsndPlayNow(u32 id);
void winSeqSetMenu(void* seq, s32 menu);
bool winSeqCheckMove(void* seq);
void menuButtonNormal(MenuWindow* window);
s32 gamedatasaveGetStatus(s32, s32);
void GSinputMotorStart(s32 pad, s32, s32 strength, s32 frames, s32);

}

static inline f32 _menuIntWave(f32 c, f32 scale) {
    return 300.0f * ((1.0f + c) * scale);
}

static u8 _menuIntGetAlpha2();
static u8 _menuIntGetAlpha();
static void _menuIntVibSet();

static bool _menuIntVibFlag = true;
static bool _underTakerIconFlag = true;
static f32 _menuIntFrameCount;
static f32 _menuIntFrameCount2;

#define UNDERTAKER_MENU 0xC1

extern "C" {

void menuIntUnderTakerOpenIcon(void) {
    if (menuIsCheck(UNDERTAKER_MENU)) {
        menuClose(UNDERTAKER_MENU);
    } else {
        menuOpenCustom(UNDERTAKER_MENU, 0, 0, 0, 1, 0);
    }
}

void menuIntUnderTakerMenuClose(void) {
    if (menuIsCheck(UNDERTAKER_MENU)) {
        menuClose(UNDERTAKER_MENU);
        menuCloseSync(UNDERTAKER_MENU, 1);
    }
}

void menuIntUnderTakerMenuOpen(void) {
    _menuIntVibFlag = true;
    menuOpenCustom(UNDERTAKER_MENU, 0, 0, 0, 1, 0);
}

void menuIntUnderTakerDispIconRestore2(void) {
    _underTakerIconFlag = true;
}

void menuIntUnderTakerDispIconOff2(void) {
    _underTakerIconFlag = false;
}

void menuIntUnderTakerHook(MenuWindow* window, MenuItem* item) {
    u8 kind;
    GSgfxLayerFindByID(winSpriteGetLayerID(window, item));
    kind = floorDataBiosGetFloorKind(floorDataBiosGetPtr(GSfloorGetCurrent()));
    if (_underTakerIconFlag && GSflagTest(undertakerdata->flag) && kind == 1) {
        winSpriteSetDisp(item, 1);
        switch (item->id) {
        case 0x65C:
            if (window->state != 0) {
                item->alpha = _menuIntGetAlpha2();
            }
            break;
        }
    } else {
        winSpriteSetDisp(item, 0);
    }
}

}

static u8 _menuIntGetAlpha2() {
    f32 c = cos(6.2831855f * _menuIntFrameCount2 / 1.5f);
    u16 alpha = _menuIntWave(c, 0.5f);
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    if (alpha < 50) {
        alpha = 50;
    }
    _menuIntFrameCount2 += timeGetLastFrameSec();
    return alpha;
}

extern "C" {

s32 menuIntUnderTakerMainCtrl(MenuWindow* window) {
    switch (window->state) {
    case 0:
        GSsndPlayNow(0x5B4);
        if (_menuIntVibFlag) {
            _menuIntVibSet();
        }
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x171);
            window->seqSet = 1;
        }
        _menuIntVibFlag = true;
        break;
    case 3:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x177);
            window->seqSet = 1;
        }
        break;
    }
    return 0;
}

void menuIntHook(MenuWindow* window, MenuItem* item) {
    s32* data = window->data;
    switch (item->id) {
    case 0x4BE:
        if (*data != 0) {
            winSpriteSetDisp(item, 0);
        } else {
            winSpriteSetDisp(item, 1);
            if (window->state != 0) {
                item->alpha = _menuIntGetAlpha();
            }
        }
        break;
    case 0x505:
        if (*data != 1) {
            winSpriteSetDisp(item, 0);
        } else {
            winSpriteSetDisp(item, 1);
            if (window->state != 0) {
                item->alpha = _menuIntGetAlpha();
            }
        }
        break;
    case 0x506:
        if (*data != 2) {
            winSpriteSetDisp(item, 0);
        } else {
            winSpriteSetDisp(item, 1);
            if (window->state != 0) {
                item->alpha = _menuIntGetAlpha();
            }
        }
        break;
    }
}

}

static u8 _menuIntGetAlpha() {
    f32 c = cos(6.2831855f * _menuIntFrameCount / 1.5f);
    u16 alpha = _menuIntWave(c, 0.5f);
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    if (alpha < 50) {
        alpha = 50;
    }
    _menuIntFrameCount += timeGetLastFrameSec();
    return alpha;
}

extern "C" {

void menuIntButton(MenuWindow* window) {
    if (!winSeqCheckMove(window->seq)) {
        menuButtonNormal(window);
    }
}

s32 menuIntMainCtrl(MenuWindow* window) {
    s32* data = window->data;
    switch (window->state) {
    case 0: {
        u32 se;
        _menuIntVibSet();
        se = 0;
        switch (*data) {
        case 0:
            se = 0x566;
            break;
        case 1:
            se = 0x564;
            break;
        case 2:
            se = 0x565;
            break;
        }
        if (se != 0) {
            GSsndPlayNow(se);
        }
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x171);
            window->seqSet = 1;
        }
        break;
    }
    case 3:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x177);
            window->seqSet = 1;
        }
        break;
    }
    return 0;
}

}

static void _menuIntVibSet() {
    if (gamedatasaveGetStatus(0, 9) == 0) {
        GSinputMotorStart(1, 0, 0xFF, 30, 0);
    }
}
