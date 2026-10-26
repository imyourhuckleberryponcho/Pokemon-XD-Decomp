#include <dolphin/types.h>

#pragma peephole off

struct CURSOR {
    s16 top;
    s16 pos;
};

struct MenuItem {
    u8 unk0[6];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    s8 seqSet;
    u8 unk3;
    void* seq;
    u8 unk8[0x14];
    s32 layer;
    u8 unk20[0x73];
    u8 alpha;
    u8 unk94[8];
    s16 top;
    s16 pos;
    u8 unkA0[4];
    u8 unkA4;
    u8 unkA5;
};

struct tagSPRITE_WORK {
    u8 unk0[6];
    s16 id;
    u8 unk8[0x14];
    s32 layer;
    u8 unk20[0x34];
    s16 x;
    u8 unk56[0xE];
    u8 color[3];
    u8 alpha;
};

struct WindowKeyInfo {
    u16 unk0;
    u16 unk2;
    u16 trigger;
};

struct MailListWork {
    s16 top;
    s16 pos;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
};

extern "C" {
void* GSmemAlloc(u32);
void GSmemFree(void*);
s32 mailGetNbMailInMailbox(void);
s32 mailGetMailIDInMailbox(s32);
void mailGetSortMode(void);
u32 mailGetSenderName(s32);
u32 mailGetSubject(s32);
s32 GSmsgGetGSchar(u32);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void GSsndPlayNow(u32);
CURSOR cursorBiosGetPos(s32);
void cursorBiosSetPos(s32, CURSOR);
void menuClose(s32);
void menuCloseSync(s32, s32);
MenuItem* menuItemBiosGetPtr(s32, s32);
s32 menuOpen(s32, s32);
CURSOR* menuPdaMailXD(CURSOR*, u8, void*);
void menuPdaSubCalcAlpha(f32*, s32, s32);
void menuPdaSubCalcPositon(f32*, f32, f32);
void menuPdaSubCheckUpDownCursor(tagWINDOW_WORK*, tagSPRITE_WORK*, s16*, s32, s32, s32);
void menuPdaSubInitAlpha(f32*, s32, s32);
void menuPdaSubScrollBar(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32, u32, s32, s32, s16*);
void msgctrlSetValue(s32, u32);
void spriteClearScissor(s32);
void spriteSetScissor(s32, s32, s32, s32, s32);
u8 winSeqCheckMove(void*);
void winSeqSetMenu(void*, s32);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
WindowKeyInfo* windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
s32 pdaMailGetMailID(s32);
}

static void _pdaMailListDownCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static void _pdaMailListUpCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static void _pdaMailListCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static void _pdaMailListScrollBar(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static void _menuPdaMailListMain(tagWINDOW_WORK* window);
static void _menuPdaMailListXDInit();
static void _menuPdaMailListCalcPosition(CURSOR* cursor);
static void _menuPdaMailListPosition();
static void _menuPdaMailCalc(f32* value, f32 target, f32 speed);
static s32 _pdaMailListDraw(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static s32 _pdaMailListPageBunbo(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static s32 _pdaMailListPageBunshi(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static void _pdaMailListPage(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static void _menuClose(long menuID);
static void _sortReceive(u16* dst);
static void _pdaMailSort();
static void _setCursor(CURSOR cursor);
static CURSOR _getCursor();
static u32 _getSenderName(long index);
static u32 _getSubject(long index);
static s32 _getMailID(long index);

MailListWork _maillistwork;
static f32 _menuPdaMailAlpha[5];
static u16* _sortwork;

extern "C" {

void menuPdaMailListSortExit(void) {
    if (_sortwork != 0) {
        if (_sortwork != 0) {
            GSmemFree(_sortwork);
            _sortwork = 0;
        }
    }
}

s32 menuPdaMailListSortInit(s32 id) {
    int n = mailGetNbMailInMailbox();
    if (n > 0) {
        _sortwork = (u16*)GSmemAlloc(n * 2);
    } else {
        _sortwork = 0;
    }
    if (_sortwork != 0) {
        _pdaMailSort();
        u16* p = _sortwork;
        for (s32 i = 0; i < n; p++, i++) {
            if (id == *p) {
                return i;
            }
        }
        return -1;
    }
    return -1;
}

void menuPdaMailListButtonXD(tagWINDOW_WORK* window) {
    if (window != 0) {
        int count = mailGetNbMailInMailbox();
        if (winSeqCheckMove(window->seq) == 0) {
            u16 trigger = windowGetKeyInfo()->trigger;
            if (count != 0 && (trigger & 0x10) != 0) {
                window->unkA4 = 1;
            }
            if ((trigger & 0x20) != 0) {
                window->unkA4 = 1;
                window->unkA5 = 1;
            }
        }
    }
}

s32 menuPdaMailListCursorXD(tagWINDOW_WORK* window) {
    windowGetKeyInfo();
    CURSOR c = _getCursor();
    c.top = window->top;
    c.pos = window->pos;
    int count = mailGetNbMailInMailbox();
    int visible = 5;
    if (count < 5) {
        visible = count;
    }
    u16 key = windowGetKeyRepeat();
    if (visible != 0) {
        if ((key & 1) != 0) {
            if (c.pos + c.top != 0) {
                GSsndPlayNow(0x450);
            }
            c.pos -= 1;
        } else if ((key & 2) != 0) {
            if (count - 1 != c.pos + c.top) {
                GSsndPlayNow(0x450);
            }
            c.pos += 1;
        } else if ((key & 8) != 0) {
            if (count - 1 != c.pos + c.top) {
                GSsndPlayNow(0x453);
            }
            c.pos += visible;
        } else if ((key & 4) != 0) {
            if (c.pos + c.top != 0) {
                GSsndPlayNow(0x453);
            }
            c.pos -= visible;
        }
        if (c.pos < 0) {
            c.top += c.pos;
            c.pos = 0;
            if (c.top < 0) {
                c.top = 0;
                c.pos = 0;
            }
        } else if (c.pos >= visible) {
            c.top = c.top + (c.pos - (visible - 1));
            c.pos = (s8)(visible - 1);
            if (c.top + c.pos >= count) {
                c.pos = (s8)(visible - 1);
                c.top = (s8)(count - visible);
            }
        }
    }
    _setCursor(c);
    window->top = c.top;
    window->pos = c.pos;
    return 0;
}

s32 menuPdaMailListCallBack(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x8D:
        _pdaMailListScrollBar(window, sprite);
        break;
    case 0x9C:
        _pdaMailListPageBunshi(window, sprite);
        break;
    case 0x9B:
        _pdaMailListPage(window, sprite);
        break;
    case 0x9A:
        _pdaMailListPageBunbo(window, sprite);
        break;
    case 0x97:
        _pdaMailListDraw(window, sprite);
        break;
    case 0x98:
        sprite->color[0] = 0xF0;
        sprite->color[1] = 0xF0;
        sprite->color[2] = 0xF0;
        break;
    case 0x99:
        sprite->color[0] = 0xD5;
        sprite->color[1] = 0xAA;
        sprite->color[2] = 0x33;
        break;
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
        _pdaMailListCursor(window, sprite);
        break;
    case 0x8B:
        _pdaMailListUpCursor(window, sprite);
        break;
    case 0x8C:
        _pdaMailListDownCursor(window, sprite);
        break;
    }
    return 0;
}

}

static void _pdaMailListDownCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    CURSOR cursor = _getCursor();
    int n = mailGetNbMailInMailbox();
    menuPdaSubCheckUpDownCursor(window, sprite, &cursor.top, n, 5, 0);
}

static void _pdaMailListUpCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    CURSOR cursor = _getCursor();
    int n = mailGetNbMailInMailbox();
    menuPdaSubCheckUpDownCursor(window, sprite, &cursor.top, n, 5, 1);
}

static void _pdaMailListCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    const s32 ids[5] = { 0x81, 0x82, 0x83, 0x84, 0x85 };
    s32 i;
    int count = mailGetNbMailInMailbox();
    s32 pos = window->pos;
    if (count == 0) {
        pos = 0;
    }
    for (i = 0; i < 5; i++) {
        if (sprite->id == ids[i]) {
            break;
        }
    }
    *((s8*)sprite + 0x67) = _menuPdaMailAlpha[i];
    if (pos == i) {
        winSpriteSetDisp(sprite, 1);
        return;
    }
    if (_menuPdaMailAlpha[i] == 0.0f) {
        winSpriteSetDisp(sprite, 0);
    }
}

static void _pdaMailListScrollBar(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    int n = mailGetNbMailInMailbox();
    CURSOR cursor = _getCursor();
    menuPdaSubScrollBar(window, sprite, 0x6E, 0x8D, 0xF2642200, n, 5, &cursor.top);
}

extern "C" {

s32 menuPdaMailListCtrlXD(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x132);
            window->seqSet = 1;
        }
        break;
    case 2:
        _menuPdaMailListMain(window);
        break;
    case 3:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x136);
            window->seqSet = 1;
        }
        break;
    }
    return 0;
}

s32 menuPdaMailListSubXD(long unused, CURSOR* cursor) {
    CURSOR c;
    c.top = cursor->top;
    c.pos = cursor->pos;
    _setCursor(c);
    s32 result;
    do {
        result = menuOpen(0x6E, 1);
        c = _getCursor();
    } while (result != -1 && c.pos >= 5);
    _menuClose(0x6E);
    if (result == -1 || mailGetNbMailInMailbox() == 0) {
        return -1;
    }
    cursor->pos = c.pos;
    cursor->top = c.top;
    return c.top + c.pos;
}

void menuPdaMailListXD(void) {
    CURSOR cursor;
    s32 result = 0;
    int n = mailGetNbMailInMailbox();
    if (n > 0) {
        _sortwork = (u16*)GSmemAlloc(n * 2);
    } else {
        _sortwork = 0;
    }
    _menuPdaMailListXDInit();
    _pdaMailSort();
    cursor.pos = 0;
    cursor.top = 0;
    menuOpen(0x77, 0);
    for (;;) {
        result = menuPdaMailListSubXD(result, &cursor);
        if (result < 0) {
            break;
        }
        CURSOR* c = menuPdaMailXD(&cursor, 1, 0);
        cursor.pos = c->pos;
        cursor.top = c->top;
        menuPdaSubInitAlpha(_menuPdaMailAlpha, 5, c->pos);
        _menuPdaMailListCalcPosition(&cursor);
        _maillistwork.unk8 = _maillistwork.unk10;
    }
    _menuClose(0x77);
    if (n > 0) {
        if (_sortwork != 0) {
            GSmemFree(_sortwork);
            _sortwork = 0;
        }
    }
}

}

static void _menuPdaMailListXDInit() {
    int n = mailGetNbMailInMailbox();
    _maillistwork.pos = 0;
    _maillistwork.top = 0;
    _maillistwork.unk4 = 0.0f;
    _maillistwork.unk8 = 0.0f;
    _maillistwork.unkC = 0.0f;
    _maillistwork.unk10 = 0.0f;
    _maillistwork.unk14 = 0;
    if (n >= 5) {
        _maillistwork.unk18 = 5;
    } else {
        _maillistwork.unk18 = n;
    }
    menuPdaSubInitAlpha(_menuPdaMailAlpha, 5, 0);
}

static void _menuPdaMailListMain(tagWINDOW_WORK* window) {
    CURSOR c = _getCursor();
    _menuPdaMailListPosition();
    _menuPdaMailListCalcPosition(&c);
    menuPdaSubCalcAlpha(_menuPdaMailAlpha, 5, c.pos);
}

static void _menuPdaMailListCalcPosition(CURSOR* cursor) {
    _maillistwork.unk10 = -cursor->top * 0x2F;
}

static void _menuPdaMailListPosition() {
    if (_maillistwork.unk4 != _maillistwork.unkC) {
        _menuPdaMailCalc(&_maillistwork.unk4, _maillistwork.unkC, 20.0f);
    }
    if (_maillistwork.unk8 != _maillistwork.unk10) {
        _menuPdaMailCalc(&_maillistwork.unk8, _maillistwork.unk10, 20.0f);
    }
}

static void _menuPdaMailCalc(f32* value, f32 target, f32 speed) {
    menuPdaSubCalcPositon(value, target, speed);
}

static s32 _pdaMailListDraw(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    CURSOR cursor = _getCursor();
    int n = mailGetNbMailInMailbox();
    u32 colorA = 0xD5AA3300 | window->alpha;
    u32 colorB = 0xF0F0F000 | window->alpha;
    MenuItem* area = menuItemBiosGetPtr(0x6E, 0x70);
    MenuItem* self = menuItemBiosGetPtr(0x6E, sprite->id);
    spriteSetScissor(window->layer, area->x - self->x, area->y - self->y, area->width, area->height);
    f32 step = 47.0f;
    f32 y = _maillistwork.unk8;
    s32 xA = (s32)_maillistwork.unk4;
    s32 xB = (s32)(step + _maillistwork.unk4);
    for (s32 i = 0; i < n; i++) {
        if (i >= cursor.top - 1 && i < cursor.top + 6) {
            u32 subject = _getSubject(i);
            if (subject != 0) {
                u32 str = GSmsgGetGSchar(subject);
                msgctrlSetValue(0x37, str);
                GSmsgPrint2(window->layer, xA, (s32)y, colorA | window->alpha, 0x4276);
            } else {
                GSmsgPrint2(window->layer, xA, (s32)y, colorA | window->alpha, 0);
            }
            u32 sender = _getSenderName(i);
            if (sender != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(sender));
                GSmsgPrint2(window->layer, xB, (s32)(21.0f + y), colorB | window->alpha, 0x4276);
            } else {
                GSmsgPrint2(window->layer, xB, (s32)(21.0f + y), colorB | window->alpha, 0);
            }
        }
        y += step;
    }
    spriteClearScissor(window->layer);
    return 0;
}

static s32 _pdaMailListPageBunbo(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    int n = mailGetNbMailInMailbox();
    if (n != 0) {
        msgctrlSetValue(0x34, n);
        s32 w = GSmsgGetRect(0x426F) >> 16;
        GSmsgPrint2(window->layer, sprite->x - w, 0, window->alpha | -0x100, 0x426F);
    }
    return 0;
}

static s32 _pdaMailListPageBunshi(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (mailGetNbMailInMailbox() != 0) {
        msgctrlSetValue(0x34, window->top + window->pos + 1);
        s32 w = GSmsgGetRect(0x426F) >> 16;
        GSmsgPrint2(window->layer, sprite->x - w, 0, window->alpha | -0x100, 0x426F);
    }
    return 0;
}

static void _pdaMailListPage(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (mailGetNbMailInMailbox() != 0) {
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}

static void _menuClose(long menuID) {
    menuClose(menuID);
    menuCloseSync(menuID, 1);
}

static void _sortReceive(u16* dst) {
    for (int i = mailGetNbMailInMailbox() - 1; i >= 0; i--) {
        *dst = mailGetMailIDInMailbox(i);
        dst++;
    }
}

static void _pdaMailSort() {
    u16* work = _sortwork;
    mailGetSortMode();
    _sortReceive(work);
}

static void _setCursor(CURSOR cursor) {
    cursorBiosSetPos(0xA, cursor);
}

static CURSOR _getCursor() {
    return cursorBiosGetPos(0xA);
}

static u32 _getSenderName(long index) {
    return mailGetSenderName(_getMailID(index));
}

static u32 _getSubject(long index) {
    return mailGetSubject(_getMailID(index));
}

static s32 _getMailID(long index) {
    return pdaMailGetMailID(index);
}

extern "C" {

s32 pdaMailGetMailID(s32 index) {
    if (index < 0 || index >= mailGetNbMailInMailbox()) {
        return -1;
    }
    return _sortwork[index];
}

}
