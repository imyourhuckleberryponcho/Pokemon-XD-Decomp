// STATUS (snC): 10/16 exact with extra_cflags=["-inline noauto"]. Not exact: DrawSelect/2 (reg alloc), CursorSelect/2 (reg alloc), CtrlSelect2 (clrlwi), DecimalInput (s64 reg pair).
#include <dolphin/types.h>
#include <game/shared/menu_work.h>

#pragma peephole off

struct CURSOR {
    s16 top;
    s16 pos;
};

struct SpriteVal {
    u8 pad[4];
    s16 w;
};

struct InputNumberArg {
    s32 value;
    s32 max;
    s32 min;
    s32 start;
};

struct LvUpInfo {
    bool show;
    u8 pad;
    s16 val[6];
};

extern "C" {
u32 GSmsgGetRect(u32);
s32 GSmsgPrint2(s32, s32, s32, u32, u32);
s32 esabaGetEsaItemNum(void);
void* memcpy(void*, const void*, u32);
void menuClose(s32);
void menuCloseSync(s32, s32);
u8 menuCursorCmp(CURSOR, CURSOR);
u8 menuDataBiosGetDispMax(s32);
s32 menuOpenCustom(s32, ...);
void menuSetStatus(s32, s32);
void* menuSpriteBiosGetPtr(u32);
SpriteVal* menuSpriteBiosGetValPtr(void*);
void menuSubCursorAnimeMain(void);
void menuSubCursorAnimeStart(void);
void menuSubCursorAnimeValGet(f32*, s32*);
void menuSubDrawCursorBack(s32, s32, s32, s32, s32, u8, u8);
void menuSubDrawMsgWindow2(s32, s32, s32, s32, s32, u8, u8);
void menuSubDrawNormalWindow2(s32, s32, s32, s32, s32, u8);
void menuSubDrawSimpleWindow(s32, s32, s32, s32, s32);
void msgctrlSetValue(s32, s32);
u8 winSeqIsCheck(s32, u16);
void winSeqSetMenu(s32, u32);
void* windowAllocMemory(tagWINDOW_WORK*, s32);
void windowDrawSprite(s16, s16, tagWINDOW_WORK*, u16, u32, s32);
void windowDrawSpriteCursor(s16, s16, u32, tagWINDOW_WORK*, u16, u32, s32, f32*, s32);
s32 windowGetActiveID(void*);
u32* windowGetAllocPtr(tagWINDOW_WORK*);
s32* windowGetFreeWork(tagWINDOW_WORK*);
struct KeyInfo { u8 pad[6]; u16 trg; };
KeyInfo* windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
u32 windowGetParam(tagWINDOW_WORK*, u32);
void windowSetParam(tagWINDOW_WORK*, u32, u32);
}

static InputNumberArg _inputnumberarg;
static s32 _DrawSelectOffset = 0xC;
static s32 _addwidth = 8;
static s32 _cursorOffset = 5;
static s32 _lsizecursorYoffset = 2;
static s32 _backWidth = 5;

static s32 _menuPanelInputNumber(s16, s16, s32, s32*, s32, s32, bool);
static void _menuPanelDrawDigit(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, bool);

extern "C" {
s32 menuPanelInputNumber(s32 value, s32* out, s32 a, s32 b, bool c) {
    s32 r = _menuPanelInputNumber(0, 0, value, out, a, b, c);
    if (r >= 0) {
        *out = r;
        return 1;
    }
    *out = value;
    return 0;
}

void menuPaneInputNumberClose(void) {
    menuClose(0xB9);
    menuCloseSync(0xB9, 1);
}
}

static s32 _menuPanelInputNumber(s16, s16, s32 a, s32*, s32 c, s32 d, bool e) {
    s32 r;
    _inputnumberarg.value = a;
    _inputnumberarg.max = d;
    _inputnumberarg.min = c;
    _inputnumberarg.start = a;
    r = menuOpenCustom(0xB9, windowGetActiveID(&_inputnumberarg), 0, 0, 1, 1, &_inputnumberarg);
    if (r >= 0) {
        r = _inputnumberarg.value;
    }
    if (e) {
        menuPaneInputNumberClose();
    }
    return r;
}

extern "C" {
void menuPanelInputNumberHook(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    InputNumberArg* arg = (InputNumberArg*)w->params[0];
    switch (sp->id) {
    case 0x504:
        msgctrlSetValue(0x34, arg->value / 10);
        break;
    case 0x503:
        msgctrlSetValue(0x34, arg->value % 10);
        break;
    case 0x511:
        msgctrlSetValue(0x34, arg->start - arg->value + esabaGetEsaItemNum());
        break;
    }
}

void menuPanelInputNumberCursor(tagWINDOW_WORK* w) {
    windowGetKeyInfo();
    InputNumberArg* arg = (InputNumberArg*)w->params[0];
    u16 key = windowGetKeyRepeat();
    if (key & 1) {
        if (arg->value < arg->max) {
            arg->value++;
        }
    } else if (key & 2) {
        if (arg->value > arg->min) {
            arg->value--;
        }
    }
}

void menuPanelInputNumberCtrl(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x24);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x17B);
            w->seqSet = 1;
        }
        break;
    }
}

s32 menuPanelDrawSelect2(tagWINDOW_WORK* w) {
    enum TsE { TsE0 };
    u32* items;
    enum TsE maxCount;
    CURSOR cur;
    u8 type;
    s32 vis;
    s32 width;
    s32 maxH;
    s32 maxW;
    s32 i;
    s32 y;
    s32 h;
    s32 count;
    u32* p;
    s32 off;
    s32 total;
    SpriteVal* sv;
    int top;
    f32 pos[2];
    s32 color;
    total = 0;
    maxH = 0;
    cur = *(CURSOR*)&w->top;
    off = _DrawSelectOffset;
    maxW = 0;
    type = windowGetParam(w, 0);
    items = windowGetAllocPtr(w);
    count = (s8)windowGetParam(w, 2);
    vis = count;
    maxCount = (enum TsE)(windowGetParam(w, 3));
    if (vis > maxCount) {
        vis = maxCount;
    }
    for (i = 0, p = items; i < count; i++, p++) {
        u32 rect = GSmsgGetRect(*p);
        if (maxH < (s32)(rect >> 16)) {
            maxH = rect >> 16;
        }
        if (maxW < (s32)(rect & 0xFFFF)) {
            maxW = rect & 0xFFFF;
        }
        if (i < vis) {
            total += off + (rect & 0xFFFF);
        }
    }
    total -= off;
    width = maxH + 0x1A + _addwidth;
    switch ((u16)type) {
    case 0:
        menuSubDrawNormalWindow2(w->layer, 0, 0, width + 2, total, w->alpha);
        break;
    case 1:
        menuSubDrawMsgWindow2(w->layer, 0, 0, width + 2, total, w->alpha, 1);
        break;
    case 0x7F:
        menuSubDrawSimpleWindow(w->layer, 0, 0, width + 2, total - 2);
        break;
    }
    sv = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x237));
    if (count > maxCount && cur.top != 0) {
        windowDrawSprite(width / 2 - sv->w / 2, -0x12, w, 0x237, 2, w->layer);
    }
    if (count > maxCount && maxCount != count - cur.top) {
        windowDrawSprite(width / 2 - sv->w / 2, total + 10, w, 0x237, 0, w->layer);
    }
    top = cur.top;
    p = items;
    for (i = 0, y = 1; i < vis; i++, p++) {
        if (*p != 0) {
            h = off + (GSmsgGetRect(items[top + i]) & 0xFFFF);
        } else {
            h = 0x14;
        }
        if (w->cursor == i) {
            if (maxW >= 0x14) {
                menuSubDrawCursorBack(w->layer, _cursorOffset - 5, y + _lsizecursorYoffset - 7, width + _backWidth, h, w->alpha, 0);
            } else {
                menuSubDrawCursorBack(w->layer, _cursorOffset - 6, y - 6, width + _backWidth, h, w->alpha, 1);
            }
        }
        y += h;
    }
    p = items;
    for (i = 0, y = 1; i < vis; i++, p++) {
        if (*p != 0) {
            h = off + (GSmsgGetRect(items[top + i]) & 0xFFFF);
            GSmsgPrint2(w->layer, 0x1A, y, w->alpha | ~0xFF, items[top + i]);
        } else {
            h = 0x14;
        }
        menuSubCursorAnimeValGet(pos, &color);
        if (w->cursor == i) {
            if (maxW >= 0x14) {
                windowDrawSpriteCursor(_cursorOffset, y + _lsizecursorYoffset, w->alpha | ~0xFF, w, 0x7D, 0, w->layer, pos, color);
            } else {
                windowDrawSpriteCursor(_cursorOffset, y, w->alpha | ~0xFF, w, 0xC2, 0, w->layer, pos, color);
            }
        }
        y += h;
    }
    return 0;
}
s32 menuPanelCtrlSelect2(tagWINDOW_WORK* w) {
    menuSubCursorAnimeMain();
    switch (w->state) {
    case 5:
        break;
    case 0:
        if (w->seqSet == 0) {
            s32 size;
            void* src;
            u32 n;
            src = (void*)windowGetParam(w, 1);
            size = windowGetParam(w, 2);
            size <<= 2;
            void* buf = windowAllocMemory(w, size);
            if (buf != 0) {
                memcpy(buf, src, size);
            }
            bool flag = (bool)windowGetParam(w, 5);
            if (!flag) {
                menuSetStatus(w->menuID, 8);
            }
            winSeqSetMenu(w->menuID, 0x24);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x17B);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}
s32 menuPanelCursorSelect2(tagWINDOW_WORK* w) {
    enum TsE { TsE0 };
    u16 key = windowGetKeyInfo()->trg;
    s8 count;
    s8 disp;
    bool wrap;
    CURSOR cur;
    CURSOR old;
    key |= windowGetKeyRepeat();
    count = windowGetParam(w, 2);
    disp = windowGetParam(w, 3);
    wrap = windowGetParam(w, 4) != 0;
    if (count < disp) {
        disp = count;
    }
    cur.top = w->top;
    cur.pos = w->cursor;
    old.top = w->top;
    old.pos = w->cursor;
    if (key & 1) {
        cur.pos--;
    } else if (key & 2) {
        cur.pos++;
    }
    if (cur.pos < 0) {
        cur.top += cur.pos;
        cur.pos = 0;
        if (wrap) {
            if (cur.top < 0) {
                cur.pos = (s8)(disp - 1);
                cur.top = (s8)(count - disp);
            }
        } else if (cur.top < 0) {
            cur.pos = 0;
            cur.top = 0;
        }
    } else if (cur.pos >= disp) {
        enum TsE last = (enum TsE)(disp - 1);
        cur.top = cur.top + (cur.pos - last);
        cur.pos = last;
        if (wrap) {
            if (cur.top + last >= count) {
                cur.top = 0;
                cur.pos = 0;
            }
        } else if (cur.top + last >= count) {
            cur.pos = last;
            cur.top = (s8)(count - disp);
        }
    }
    if (menuCursorCmp(old, cur)) {
        menuSubCursorAnimeStart();
    }
    w->top = cur.top;
    w->cursor = cur.pos;
    return 0;
}
s32 menuPanelDrawSelect(tagWINDOW_WORK* w) {
    u32* p;
    s32 i;
    u8 type;
    u32* items;
    s32 count;
    s32 maxW = 0;
    s32 maxH = 0;
    u8 disp;
    s32 total = 0;
    s32 y;
    s32 h;
    s32 width;
    s32 off = _DrawSelectOffset;
    f32 pos[2];
    s32 color;
    type = windowGetParam(w, 0);
    items = windowGetAllocPtr(w);
    count = (s8)windowGetParam(w, 2);
    disp = menuDataBiosGetDispMax(w->menuID);
    if (count > disp) {
        count = disp;
    }
    for (i = 0, p = items; i < count; p++, i++) {
        u32 rect = GSmsgGetRect(*p);
        if (maxH < (s32)(rect >> 16)) {
            maxH = rect >> 16;
        }
        if (maxW < (s32)(rect & 0xFFFF)) {
            maxW = rect & 0xFFFF;
        }
        total += off + (rect & 0xFFFF);
    }
    total -= off;
    width = maxH + 0x1A + _addwidth;
    switch (type) {
    case 0:
        menuSubDrawNormalWindow2(w->layer, 0, 0, width, total, w->alpha);
        break;
    case 1:
        menuSubDrawMsgWindow2(w->layer, 0, 0, width, total, w->alpha, 1);
        break;
    case 0x7F:
        menuSubDrawSimpleWindow(w->layer, 0, 0, width, total - 2);
        break;
    }
    p = items;
    for (i = 0, y = 1; i < count; i++, p++) {
        if (*p != 0) {
            h = off + (GSmsgGetRect(*p) & 0xFFFF);
        } else {
            h = 0x14;
        }
        if (w->cursor == i) {
            if (maxW >= 0x14) {
                menuSubDrawCursorBack(w->layer, _cursorOffset - 5, y + _lsizecursorYoffset - 7, width + _backWidth, h, w->alpha, 0);
            } else {
                menuSubDrawCursorBack(w->layer, _cursorOffset - 6, y - 6, width + _backWidth, h, w->alpha, 1);
            }
        }
        y += h;
    }
    p = items;
    for (i = 0, y = 1; i < count; i++, p++) {
        if (*p != 0) {
            h = off + (GSmsgGetRect(*p) & 0xFFFF);
            GSmsgPrint2(w->layer, 0x1A, y, w->alpha | ~0xFF, *p);
        } else {
            h = 0x14;
        }
        menuSubCursorAnimeValGet(pos, &color);
        if (w->cursor == i) {
            if (maxW >= 0x14) {
                windowDrawSpriteCursor(_cursorOffset, y + _lsizecursorYoffset, w->alpha | ~0xFF, w, 0x7D, 0, w->layer, pos, color);
            } else {
                windowDrawSpriteCursor(_cursorOffset, y, w->alpha | ~0xFF, w, 0xC2, 0, w->layer, pos, color);
            }
        }
        y += h;
    }
    return 0;
}
s32 menuPanelCtrlSelect(tagWINDOW_WORK* w) {
    menuSubCursorAnimeMain();
    switch (w->state) {
    case 5:
        break;
    case 0:
        if (w->seqSet == 0) {
            s32 size;
            void* src;
            u32 n;
            src = (void*)windowGetParam(w, 1);
            size = windowGetParam(w, 2);
            size <<= 2;
            void* buf = windowAllocMemory(w, size);
            if (buf != 0) {
                memcpy(buf, src, size);
            }
            winSeqSetMenu(w->menuID, 0x24);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x17B);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}
s32 menuPanelCursorSelect(tagWINDOW_WORK* w) {
    u16 key = windowGetKeyInfo()->trg;
    s8 count;
    s8 disp;
    CURSOR cur;
    CURSOR old;
    key |= windowGetKeyRepeat();
    count = windowGetParam(w, 2);
    disp = menuDataBiosGetDispMax(w->menuID);
    bool lt = disp < count;
    if (lt) {
        count = disp;
    }
    if (!lt) {
        disp = count;
    }
    cur.top = w->top;
    cur.pos = w->cursor;
    old.top = w->top;
    old.pos = w->cursor;
    if (key & 1) {
        cur.pos--;
    } else if (key & 2) {
        cur.pos++;
    }
    s16 p = cur.pos;
    if (p < 0) {
        cur.pos = 0;
        cur.top += p;
        if (cur.top < 0) {
            cur.pos = (s8)(disp - 1);
            cur.top = (s8)(count - disp);
        }
    } else if (p >= disp) {
        s32 last = disp - 1;
        cur.top = cur.top + (p - last);
        cur.pos = (s8)last;
        if (cur.top + cur.pos >= count) {
            cur.top = 0;
            cur.pos = 0;
        }
    }
    if (menuCursorCmp(old, cur)) {
        menuSubCursorAnimeStart();
    }
    w->top = cur.top;
    w->cursor = cur.pos;
    w->cursor88 = cur.top + cur.pos;
    return 0;
}
s32 menuPanelCursorDecimalInput(tagWINDOW_WORK* w) {
    s32 type;
    s32* sel;
    s32 delta;
    s32 base;
    s32 value;
    s32 digits;
    s32 i;
    s64 r;
    u16 key;
    sel = windowGetFreeWork(w);
    delta = 0;
    value = windowGetParam(w, 0);
    type = windowGetParam(w, 1);
    if (type == 2) {
        digits = 8;
        base = 16;
    } else {
        digits = 10;
        base = 10;
    }
    key = windowGetKeyInfo()->trg;
    if (key & 8) {
        (*sel)--;
    } else if (key & 4) {
        (*sel)++;
    }
    if (*sel < 0) {
        value = 0;
        *sel = 0;
    }
    if (*sel >= digits) {
        *sel = digits - 1;
    }
    if (key & 1) {
        delta = 1;
        for (i = 0; i < *sel; i++) {
            delta *= base;
        }
    } else if (key & 2) {
        delta = -1;
        for (i = 0; i < *sel; i++) {
            delta *= base;
        }
    }
    if (type == 0) {
        r = (s64)value + delta;
        if (r < -0x80000000LL) {
            r = -0x80000000LL;
        }
        if (r > 0x7FFFFFFFLL) {
            r = 0x7FFFFFFFLL;
        }
    } else {
        r = (s64)(u32)value + delta;
        if (r < 0) {
            r = 0;
        }
        if (r > 0xFFFFFFFFLL) {
            r = 0xFFFFFFFFLL;
        }
    }
    value = r & 0xFFFFFFFF;
    w->cursor88 = value;
    windowSetParam(w, 0, value);
    return 0;
}

s32 menuPanelDrawLvUpItem(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    LvUpInfo* info = (LvUpInfo*)windowGetParam(w, 0);
    switch (sp->id) {
    case 0x1C5:
        if (w->menuID == 0x29) {
            menuSubDrawNormalWindow2(w->layer, 0, 0, sp->w, sp->h, w->alpha);
        } else {
            menuSubDrawMsgWindow2(w->layer, 0, 0, sp->w, sp->h, w->alpha, 1);
        }
        break;
    case 0x1C6: _menuPanelDrawDigit(w, sp, info->val[0], info->show); break;
    case 0x1C7: _menuPanelDrawDigit(w, sp, info->val[1], info->show); break;
    case 0x1C8: _menuPanelDrawDigit(w, sp, info->val[2], info->show); break;
    case 0x1C9: _menuPanelDrawDigit(w, sp, info->val[3], info->show); break;
    case 0x1CA: _menuPanelDrawDigit(w, sp, info->val[4], info->show); break;
    case 0x1CB: _menuPanelDrawDigit(w, sp, info->val[5], info->show); break;
    }
    return 0;
}

s32 menuPanelCtrlLvUp(tagWINDOW_WORK* w) {
    bool flag = false;
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) flag = true;
        if (winSeqIsCheck(w->menuID, 0x2C) == 1) flag = true;
        if (flag) {
            winSeqSetMenu(w->menuID, 0x28);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x2C);
            w->seqSet = 1;
        }
        break;
    case 5:
    default:
        break;
    }
    return 0;
}
}

static void _menuPanelDrawDigit(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, s32 value, bool flag) {
    if (flag) {
        s16 h = GSmsgGetRect(0x42CD) >> 16;
        GSmsgPrint2(w->layer, sp->w - 0x30 - h, 0, w->alpha | ~0xFF, 0x42CD);
    }
    msgctrlSetValue(0x34, value);
    s16 h2 = GSmsgGetRect(0x426E) >> 16;
    GSmsgPrint2(w->layer, sp->w - h2, 0, w->alpha | ~0xFF, 0x426E);
}
