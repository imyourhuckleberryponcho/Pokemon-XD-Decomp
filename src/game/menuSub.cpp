#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>

// Menu units were built without the peephole optimizer.
#pragma peephole off

struct GSgfxVF;
enum GSgfxLayerID { GSgfxLayerID0 };
enum menuSubCursorBackColor { menuSubCursorBackColor0, menuSubCursorBackColor1 };
class GSgfxLayer {
public:
    u8 pad0[0xD34];
    u8 colorCount;
    u8 padD35[3];
    u32 colorMode;
    u8 padD3C[0x16A8 - 0xD3C];
    u32 flagsA;
    u32 flagsB;
    u8 pad16B0[0x1760 - 0x16B0];
    u32 flagsC;
    u32 flagsD;
    u8 pad1768[0x1998 - 0x1768];
    u32 primitive;
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    u8 unk2[0x86];
    s32 result;
    u8 unk8C[0x12];
    s16 cursor;
    u8 unkA0[4];
    u8 done;
    u8 cancelled;
};

struct tagSPRITE_WORK {
    u8 unk0[6];
    s16 id;
};

struct MenuSpriteVal {
    u8 unk0[4];
    s16 w;
    s16 h;
};

struct MenuSubCursorAnimeWork {
    f32 x;
    f32 y;
    f32 startX;
    f32 startY;
    f32 endX;
    f32 endY;
    s32 color;
    s16 time;
    s16 duration;
    f32 timer;
    u8 cur[4];
    u8 from[4];
    u8 to[4];
};

struct MenuSubColorItem {
    u8 unk0[0x64];
    u8 color[4];
};

struct MenuSubColorContext {
    u8 unk0[0x90];
    u8 color[4];
};

extern "C" {

GSgfxLayer* GSgfxLayerFindByID(s32);
void menuSubCursorAnimeInit(void);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
void* GSmsgGetGSchar(void*);
s32 GScharCmp(void*, void*);
void GSthreadSwitch(void);
s32 menuCB_GetDisconnectedGBA(void);
void menuClose(s32);
void menuCloseCustom(s16, s32, s32);
void menuCloseSync(s32, s32);
f32 menuGetTotalTime(void);
void* menuItemBiosGetPtr(s32, s32);
s32 menuOpenCustom(s32, ...);
void menuSetPosition(s16, s16, s16);
void* menuSpriteBiosGetPtr(u32);
MenuSpriteVal* menuSpriteBiosGetValPtr(void*);
u16 pokemonBiosGetPokemonDataId(void*);
u8 pokemonCheckValid(void*);
void* pokemonDataBiosGetName(void*);
void* pokemonDataBiosGetPtr(u16);
s32 pokemonGetSex(void*);
u32 pokemonGetStatus(void*, s32, s32, s32);
f32 timeGetLastFrameSec(void);
s32 timeGetLastFrameTime(void);
void winSpriteSetDisp(tagSPRITE_WORK*, u8);
u8 windowCheckCursor(s16, s32);
void windowDrawSprite2(s16, s16, s16, s16, u32, s32, u16, s32, s32);
s32 windowGetActiveID(void);
s32 windowGetValue(s16);
tagWINDOW_WORK* windowSearchID(s32);
f64 cos(f64);

static f32 _cursorTimer;
MenuSubCursorAnimeWork _cursorAnimeWork;

}

static s32 _animAlpha(void);
static void _menuSubDrawCursorBackSub(GSgfxLayerID, s32, s32, s32, s32, u32, u8, u8, menuSubCursorBackColor, bool);
static void menuSubCheckSelectSub(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
static u8 menuSubOpenNumberInputSub(u32, u32*, u8, s16, s16, bool, u16* (*)(u32));

static f32 _cursorSec = 0.5f;
static f32 _max_alpha = 255.0f;
static f32 _min_alpha = 128.0f;

extern "C" {

s32 menuSubGetKaiwaCloseWindowID(void) {
    return 0x3DF;
}

s32 menuSubGetKaiwaCsrID(void) {
    return 0xBA;
}

void menuSubDrawMsgWindow2(s32 layer, s32 x, s32 y, s32 w, s32 h, u8 alpha) {
    MenuSpriteVal* corner;
    MenuSpriteVal* mid;
    s16 x0;
    s16 x1;
    s16 y0;
    s16 y1;
    s16 midW;
    s16 midH;
    u32 color;

    if (GSgfxLayerFindByID(layer) != 0) {
        corner = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0xB3));
        color = alpha | 0xFFFFFF00;
        x0 = x - corner->w / 2 - 15;
        x1 = x + w - corner->w / 2 + 15;
        y0 = y - corner->h / 2 - 10;
        y1 = y + h - corner->h / 2 + 10;
        windowDrawSprite2(x0, y0, corner->w, corner->h, color, 0, 0xB3, 0, layer);
        windowDrawSprite2(x1, y0, corner->w, corner->h, color, 0, 0xB3, 1, layer);
        windowDrawSprite2(x0, y1, corner->w, corner->h, color, 0, 0xB3, 2, layer);
        windowDrawSprite2(x1, y1, corner->w, corner->h, color, 0, 0xB3, 3, layer);
        mid = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0xB2));
        midW = x1 - x0 - corner->w;
        windowDrawSprite2(x0 + corner->w, y0, midW, mid->h, color, 0, 0xB2, 0, layer);
        windowDrawSprite2(x0 + corner->w, y1, midW, mid->h, color, 0, 0xB2, 2, layer);
        mid = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0xB1));
        midH = y1 - y0 - corner->h;
        windowDrawSprite2(x0, y0 + corner->h, mid->w, midH, color, 0, 0xB1, 0, layer);
        windowDrawSprite2(x1, y0 + corner->h, mid->w, midH, color, 0, 0xB1, 1, layer);
        menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0xB0));
        windowDrawSprite2(x0 + corner->w, y0 + corner->h, midW, midH, color, 0, 0xB0, 0, layer);
    }
}

void menuSubDrawNormalWindow2(s32 layer, s32 x, s32 y, s32 w, s32 h, u8 alpha) {
    MenuSpriteVal* top;
    MenuSpriteVal* bottom;
    MenuSpriteVal* mid;
    s16 x0;
    s16 x1;
    s16 y0;
    s16 y1;
    s16 midW;
    s16 midH;
    u32 color;

    if (GSgfxLayerFindByID(layer) != 0) {
        top = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x69));
        x0 = x - top->w / 2 - 10;
        x1 = x + w - top->w / 2 + 10;
        bottom = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x67));
        color = alpha | 0xFFFFFF00;
        y0 = y - top->h / 2 - 10;
        y1 = y + h - top->h / 2 + 10;
        windowDrawSprite2(x0, y0, top->w, top->h, color, 0, 0x69, 0, layer);
        windowDrawSprite2(x1, y0, top->w, top->h, color, 0, 0x69, 1, layer);
        windowDrawSprite2(x0, y1, bottom->w, bottom->h, color, 0, 0x67, 0, layer);
        windowDrawSprite2(x1, y1, bottom->w, bottom->h, color, 0, 0x67, 1, layer);
        mid = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x66));
        midW = x1 - x0 - top->w;
        windowDrawSprite2(x0 + top->w, y0, midW, mid->h, color, 0, 0x66, 0, layer);
        mid = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x65));
        windowDrawSprite2(x0 + top->w, y1, midW, mid->h, color, 0, 0x65, 0, layer);
        mid = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x68));
        midH = y1 - y0 - top->h;
        windowDrawSprite2(x0, y0 + top->h, mid->w, midH, color, 0, 0x68, 0, layer);
        windowDrawSprite2(x1, y0 + top->h, mid->w, midH, color, 0, 0x68, 1, layer);
        menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x64));
        windowDrawSprite2(x0 + top->w, y0 + top->h, midW, midH, color, 0, 0x64, 0, layer);
    }
}

void menuSubDrawCursorBack2(s32 layer, s32 x, s32 y, s32 w, s32 h, u8 alpha, u8 type, menuSubCursorBackColor colorKind) {
    _menuSubDrawCursorBackSub((GSgfxLayerID)layer, x, y, w, h, 0xFFFFFF00, alpha, type, colorKind, 1);
}

void menuSubDrawCursorBackAnimeOnOffAuto(u32 windowID, s32 layer, s32 x, s32 y, s32 w, s32 h, u8 alpha, u8 type) {
    if (windowID == (u32)windowSearchID(windowGetActiveID())) {
        _menuSubDrawCursorBackSub((GSgfxLayerID)layer, x, y, w, h, 0xFFFFFF00, alpha, type, menuSubCursorBackColor0, 1);
        return;
    }
    _menuSubDrawCursorBackSub((GSgfxLayerID)layer, x, y, w, h, 0xFFFFFF00, alpha, type, menuSubCursorBackColor0, 0);
}

void menuSubDrawCursorBackAnimeOnOff(s32 layer, s32 x, s32 y, s32 w, s32 h, u8 alpha, u8 type, bool anim) {
    _menuSubDrawCursorBackSub((GSgfxLayerID)layer, x, y, w, h, 0xFFFFFF00, alpha, type, menuSubCursorBackColor0, anim);
}

void menuSubDrawCursorBack(s32 layer, s32 x, s32 y, s32 w, s32 h, u8 alpha, u8 type) {
    _menuSubDrawCursorBackSub((GSgfxLayerID)layer, x, y, w, h, 0xFFFFFF00, alpha, type, menuSubCursorBackColor0, 1);
}

}

static void _menuSubDrawCursorBackSub(GSgfxLayerID layer, s32 x, s32 y, s32 w, s32 h, u32 color, u8 alpha, u8 type,
                                      menuSubCursorBackColor colorKind, bool anim) {
    u8 a;
    u16 idA;
    u16 idB;
    MenuSpriteVal* side;
    MenuSpriteVal* mid;
    u32 c;
    s16 midW;
    s16 x1;

    if (anim != 0) {
        a = _animAlpha();
    } else {
        a = 0xFF;
    }
    a = a * alpha / 255;
    if (GSgfxLayerFindByID(layer) != 0) {
        if (type == 0) {
            side = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0xBB));
            c = color | a;
            mid = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0xBC));
            midW = w - side->w - side->w;
            windowDrawSprite2(x, y, side->w, side->h, c, 0, 0xBB, 0, layer);
            x1 = x + side->w;
            windowDrawSprite2(x1, y, midW, mid->h, c, 0, 0xBC, 0, layer);
            windowDrawSprite2(x1 + midW, y, side->w, side->h, c, 0, 0xBB, 1, layer);
            return;
        }
        if (colorKind == menuSubCursorBackColor0) {
            idA = 0xBF;
            idB = 0xC0;
        } else {
            idA = 0x1F6;
            idB = 0x1F7;
        }
        side = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(idA));
        c = color | a;
        mid = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(idB));
        midW = w - side->w - side->w;
        windowDrawSprite2(x, y, side->w, side->h, c, 0, idA, 0, layer);
        x1 = x + side->w;
        windowDrawSprite2(x1, y, midW, mid->h, c, 0, idB, 0, layer);
        windowDrawSprite2(x1 + midW, y, side->w, side->h, c, 0, idA, 1, layer);
    }
}

extern "C" {

void menuSubAnimAlpha(void) {
    _animAlpha();
}

}

static s32 _animAlpha(void) {
    f32 rate = 6.2831855f / _cursorSec;
    f32 time = rate * menuGetTotalTime();
    f32 range = _max_alpha - _min_alpha;
    f32 scaled;
    f32 alpha;

    _cursorTimer = time;
    scaled = range * ((1.0f + (f32)cos(time)) * 0.5f);
    alpha = scaled + _min_alpha;
    if (alpha > 255.0f) {
        alpha = 255.0f;
    }
    return (s32)alpha;
}

extern "C" {

s32 menuSubCheckSelect(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x4B:
    case 0x39:
        menuSubCheckSelectSub(window, sprite, 0);
        break;
    case 0x4C:
    case 0x3A:
        menuSubCheckSelectSub(window, sprite, 1);
        break;
    }
    return 0;
}

}

static void menuSubCheckSelectSub(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, s32 index) {
    if (window->cursor == index) {
        winSpriteSetDisp(sprite, 1);
        return;
    }
    winSpriteSetDisp(sprite, 0);
}

extern "C" {

void menuSubSleep(f32 seconds) {
    f32 time = 0.0f;

    while (time < seconds) {
        GSthreadSwitch();
        time += timeGetLastFrameSec();
    }
}

void menuSubKeyWait(void) {
    u32 changed;
    u32 pressed;

    goto test;
    do {
        GSthreadSwitch();
    test:
        changed = GSinputButtonsChanged(1);
        pressed = GSinputButtonsPressed(1);
    } while (((pressed & changed) & 0x300) == 0);
}

u32 menuSubCalcColor(MenuSubColorContext* context, MenuSubColorItem* item) {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;

    red = (u8)(item->color[0] * context->color[0] / 255);
    green = (u8)(item->color[1] * context->color[1] / 255);
    blue = (u8)(item->color[2] * context->color[2] / 255);
    alpha = (u8)(item->color[3] * context->color[3] / 255);
    return (red << 24) | (green << 16) | (blue << 8) | alpha;
}

s32 menuSubOpenSelect_gba(u8 selection, s32* values, s32 a2, s32 x, s32 y, s32 flags, s32 a6, u8 a7, u8 a8) {
    s32 result;
    tagWINDOW_WORK* window;

    result = 0;
    menuSubCursorAnimeInit();
    menuOpenCustom(0xAE, windowGetActiveID(), &flags, 0, 0, 6, selection, values, a2, a6, a7, a8);
    menuSetPosition(0xAE, x, y);
    do {
        GSthreadSwitch();
        if (menuCB_GetDisconnectedGBA() != 0) {
            result = -2;
            window = windowSearchID(0xAE);
            window->done = 1;
            window->cancelled = 1;
        }
    } while (windowCheckCursor(0xAE, 0) != 0);
    if (result != -2) {
        result = windowGetValue(0xAE);
    }
    menuCloseCustom(0xAE, 0, 1);
    return result;
}

s8 menuSubOpenSelect3(u8 selection, s32* values, s32 a2, s32 x, s32 y, s32 flags, s32 a6, u8 a7, u8 a8) {
    s8 result;

    menuSubCursorAnimeInit();
    menuOpenCustom(0xAE, windowGetActiveID(), &flags, 0, 0, 6, selection, values, a2, a6, a7, a8);
    menuSetPosition(0xAE, x, y);
    windowCheckCursor(0xAE, 1);
    result = windowGetValue(0xAE);
    menuCloseCustom(0xAE, 0, 1);
    return result;
}

s8 menuSubOpenSelect2(u8 selection, s32* values, s32 a2, s32 x, s32 y, s32 flags, s32 a6, u8 a7) {
    s8 result;

    menuSubCursorAnimeInit();
    menuOpenCustom(0xAE, windowGetActiveID(), &flags, 0, 0, 6, selection, values, a2, a6, a7, 1);
    menuSetPosition(0xAE, x, y);
    windowCheckCursor(0xAE, 1);
    result = windowGetValue(0xAE);
    menuCloseCustom(0xAE, 0, 1);
    return result;
}

s8 menuSubOpenSelect(u8 selection, s32* values, s32 a2, s32 x, s32 y, s32 flags) {
    s8 result;

    menuSubCursorAnimeInit();
    menuOpenCustom(0x59, windowGetActiveID(), &flags, 0, 0, 3, selection, values, a2);
    menuSetPosition(0x59, x, y);
    windowCheckCursor(0x59, 1);
    result = windowGetValue(0x59);
    menuCloseCustom(0x59, 0, 1);
    return result;
}

void menuSubCursorAnimeValGet(f32* pos, s32* color) {
    pos[0] = _cursorAnimeWork.x;
    pos[1] = _cursorAnimeWork.y;
    *color = _cursorAnimeWork.color;
}

void menuSubCursorAnimeMain(void) {
    f32 ratio;
    f32 value;
    s16 time;

    if (_cursorAnimeWork.x != 0.0f) {
        time = _cursorAnimeWork.time + timeGetLastFrameTime();
        ratio = (f32)time / (f32)_cursorAnimeWork.duration;
        _cursorAnimeWork.time = time;
        value = (s16)((((f32)time * (f32)time) / (f32)_cursorAnimeWork.duration / (f32)_cursorAnimeWork.duration) *
                          (_cursorAnimeWork.endX - _cursorAnimeWork.startX) +
                      _cursorAnimeWork.startX);
        _cursorAnimeWork.x = value;
        _cursorAnimeWork.cur[0] = ratio * (f32)(_cursorAnimeWork.to[0] - _cursorAnimeWork.from[0]) + (f32)_cursorAnimeWork.from[0];
        _cursorAnimeWork.cur[1] = ratio * (f32)(_cursorAnimeWork.to[1] - _cursorAnimeWork.from[1]) + (f32)_cursorAnimeWork.from[1];
        _cursorAnimeWork.cur[2] = ratio * (f32)(_cursorAnimeWork.to[2] - _cursorAnimeWork.from[2]) + (f32)_cursorAnimeWork.from[2];
        _cursorAnimeWork.cur[3] = ratio * (f32)(_cursorAnimeWork.to[3] - _cursorAnimeWork.from[3]) + (f32)_cursorAnimeWork.from[3];
        if (value > 0.0f) {
            _cursorAnimeWork.x = 0.0f;
            _cursorAnimeWork.cur[3] = -1;
            _cursorAnimeWork.cur[2] = -1;
            _cursorAnimeWork.cur[1] = -1;
            _cursorAnimeWork.cur[0] = -1;
        }
        _cursorAnimeWork.color = _cursorAnimeWork.cur[3] | (_cursorAnimeWork.cur[2] << 8) |
                                 (_cursorAnimeWork.cur[0] << 24) | (_cursorAnimeWork.cur[1] << 16);
    }
    _cursorAnimeWork.timer = _cursorAnimeWork.timer + timeGetLastFrameSec();
}

void menuSubCursorAnimeStart(void) {
    _cursorAnimeWork.x = -8.0f;
    _cursorAnimeWork.y = 0.0f;
    _cursorAnimeWork.endX = 0.0f;
    _cursorAnimeWork.endY = 0.0f;
    _cursorAnimeWork.startX = -8.0f;
    _cursorAnimeWork.startY = 0.0f;
    _cursorAnimeWork.color = -0x100;
    _cursorAnimeWork.to[0] = 0xFF;
    _cursorAnimeWork.to[1] = 0xFF;
    _cursorAnimeWork.to[2] = 0xFF;
    _cursorAnimeWork.to[3] = 0xFF;
    _cursorAnimeWork.from[0] = 0xFF;
    _cursorAnimeWork.from[1] = 0xFF;
    _cursorAnimeWork.from[2] = 0xFF;
    _cursorAnimeWork.from[3] = 0;
    _cursorAnimeWork.cur[0] = 0xFF;
    _cursorAnimeWork.cur[1] = 0xFF;
    _cursorAnimeWork.cur[2] = 0xFF;
    _cursorAnimeWork.cur[3] = 0;
    _cursorAnimeWork.timer = 0.0f;
    _cursorAnimeWork.time = 0;
    _cursorAnimeWork.duration = 5;
}

}

extern "C" {

void menuSubCursorAnimeInit(void) {
    memset(&_cursorAnimeWork, 0, 0x30);
    _cursorAnimeWork.color = -1;
    _cursorAnimeWork.x = 0.0f;
    _cursorAnimeWork.y = 0.0f;
}

s32 menuSubGetPokemonSexForFightDisp(void* pokemon) {
    void* species;
    void* name;
    u16 id;

    if (pokemonCheckValid(pokemon) == 0) {
        return 0xFF;
    }
    id = pokemonBiosGetPokemonDataId(pokemon);
    if (id == 0x1D || id == 0x20) {
        species = pokemonDataBiosGetPtr(pokemonGetStatus(pokemon, 0, 0x6E, 0));
        if (species != 0) {
            name = GSmsgGetGSchar(pokemonDataBiosGetName(species));
            if (GScharCmp((void*)pokemonGetStatus(pokemon, 0, 0x77, 0), name) == 0) {
                return 2;
            }
        }
    }
    return pokemonGetSex(pokemon);
}

s32 menuSubGetPokemonSexForDisp(void* pokemon) {
    u16 id;

    if (pokemonCheckValid(pokemon) == 0) {
        return 0xFF;
    }
    id = pokemonBiosGetPokemonDataId(pokemon);
    if (id == 0x1D || id == 0x20) {
        return 2;
    }
    return pokemonGetSex(pokemon);
}

void menuSubOpenColosseumEnter(void) {
    s32 values[3];

    values[0] = *(s32*)((u8*)menuItemBiosGetPtr(0x13, 0x34) + 0x10);
    values[1] = *(s32*)((u8*)menuItemBiosGetPtr(0x13, 0x35) + 0x10);
    values[2] = *(s32*)((u8*)menuItemBiosGetPtr(0x13, 0x36) + 0x10);
    menuSubOpenSelect2(0, values, 3, 0x32, 0x32, 0, 3, 1);
}

s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 initial) {
    s32 id;
    s16 menuID;
    s8 result;

    if (initial != 0) {
        initial = 1;
    }
    switch (type) {
    case 0:
        id = 0x35;
        break;
    case 1:
        id = 0x35;
        break;
    default:
    case 0x7F:
        id = 0x55;
        break;
    }
    menuID = id;
    menuOpenCustom(menuID, windowGetActiveID(), &initial, 0, 0, 0);
    if (x >= 0 && y >= 0) {
        menuSetPosition(menuID, x, y);
    }
    windowCheckCursor(menuID, 1);
    result = windowGetValue(menuID);
    menuCloseCustom(menuID, 0, 1);
    return result;
}

s8 menuSubOpenYesNoField(void) {
    return menuSubOpenYesNo(1, -1, -1, 0);
}

void menuSubCloseNumberInputWait(void) {
    menuCloseSync(2, 1);
}

void menuSubCloseNumberInput(void) {
    menuClose(2);
}

}

static u8 menuSubOpenNumberInputSub(u32 value, u32* out, u8 digits, s16 x, s16 y, bool close, u16* (*callback)(u32)) {
    u8 result;
    tagWINDOW_WORK* window;

    result = 0;
    menuOpenCustom(2, windowGetActiveID(), 0, 0, 0, 3, value, digits, callback);
    menuSetPosition(2, x, y);
    windowCheckCursor(2, 1);
    windowGetValue(2);
    window = windowSearchID(2);
    if (window != 0) {
        if (out != 0) {
            *out = window->result;
        }
        if (window->cancelled == 0) {
            result = 1;
        }
        if (close != 0) {
            menuSubCloseNumberInput();
        }
    }
    return result;
}

extern "C" {

u8 menuSubOpenNumberInput(u32 value, u32* out, u8 digits, s16 x, s16 y, bool close) {
    return menuSubOpenNumberInputSub(value, out, digits, x, y, close, 0);
}

u8 menuSubOpenNumberInputID(u32 value, u32* out, u16* (*callback)(u32)) {
    return menuSubOpenNumberInputSub(value, out, 1, 0x32, 0x3C, 1, callback);
}

u8 menuSubOpenNumberInputDigit(u32 value, u32* out) {
    return menuSubOpenNumberInputSub(value, out, 1, 0x32, 0x3C, 1, 0);
}

void menuSubDrawTriangle(s32 layer, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2) {
    GSgfxLayer* gfx = GSgfxLayerFindByID(layer);
    if (gfx != 0) {
        gfx->primitive = 0x90;
        gfx->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
        gfx->beginSurface(3);
        GXWGFifo.s16 = x0;
        GXWGFifo.s16 = y0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.s16 = x1;
        GXWGFifo.s16 = y1;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.s16 = x2;
        GXWGFifo.s16 = y2;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        gfx->endSurface();
    }
}

void menuSubDrawTile(s32 layer, s32 x, s32 y, s32 w, s32 h, u8* color) {
    GSgfxLayer* gfx = GSgfxLayerFindByID(layer);
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    if (gfx != 0) {
        gfx->primitive = 0x98;
        gfx->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
        w += x;
        h += y;
        gfx->beginSurface(4);
        GXWGFifo.s16 = x;
        r = color[0];
        GXWGFifo.s16 = y;
        g = color[1];
        GXWGFifo.u8 = r;
        b = color[2];
        GXWGFifo.u8 = g;
        a = color[3];
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        GXWGFifo.s16 = w;
        GXWGFifo.s16 = y;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        GXWGFifo.s16 = x;
        GXWGFifo.s16 = h;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        GXWGFifo.s16 = w;
        GXWGFifo.s16 = h;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        gfx->endSurface();
    }
}

void menuSubDrawSimpleWindow(s32 layer, s32 x, s32 y, s32 w, s32 h) {
    GSgfxLayer* gfx = GSgfxLayerFindByID(layer);
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;

    if (gfx != 0) {
        gfx->primitive = 0x98;
        gfx->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
        gfx->beginSurface(4);
        x0 = x - 10;
        y0 = y - 10;
        GXWGFifo.s16 = x0;
        GXWGFifo.s16 = y0;
        x1 = x + (w + 10);
        y1 = y + (h + 10);
        GXWGFifo.u32 = 0xC0;
        GXWGFifo.s16 = x1;
        GXWGFifo.s16 = y0;
        GXWGFifo.u32 = 0xC0;
        GXWGFifo.s16 = x0;
        GXWGFifo.s16 = y1;
        GXWGFifo.u32 = 0xC0;
        GXWGFifo.s16 = x1;
        GXWGFifo.s16 = y1;
        GXWGFifo.u32 = 0xC0;
        gfx->endSurface();
        gfx->colorCount = 6;
        gfx->colorMode = 0;
        gfx->flagsB |= 4;
        gfx->flagsA |= 1;
        gfx->flagsD |= 4;
        gfx->flagsC |= 1;
        gfx->primitive = 0xB0;
        gfx->beginSurface(5);
        x0 = x - 10;
        y0 = y - 10;
        GXWGFifo.s16 = x0;
        GXWGFifo.s16 = y0;
        GXWGFifo.s32 = -1;
        GXWGFifo.s16 = x1;
        GXWGFifo.s16 = y0;
        GXWGFifo.s32 = -1;
        GXWGFifo.s16 = x1;
        GXWGFifo.s16 = y1;
        GXWGFifo.s32 = -1;
        GXWGFifo.s16 = x0;
        GXWGFifo.s16 = y1;
        GXWGFifo.s32 = -1;
        GXWGFifo.s16 = x0;
        GXWGFifo.s16 = y0;
        GXWGFifo.s32 = -1;
        gfx->endSurface();
    }
}

}
