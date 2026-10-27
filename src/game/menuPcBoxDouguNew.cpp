#include <dolphin/types.h>
#include <game/shared/menu_work.h>

#pragma peephole off
#pragma pool_strings off

struct Hero;
enum MENU_PCBOX_DOUGU_HIKIDASHI_MODE { HIKIDASHI_HIKIDASU, HIKIDASHI_SUTERU };

struct HIKI_ITEM_POS {
    u8 pad0[6];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
};

extern "C" {
u32 GSmsgGetRect(u32);
s32 GSmsgPrint2(s32, s32, s32, s32, u32);
void GSmsgPrintRight(s32, s32, s32, s16, s16, s32, u32);
void fadeCheck(s32);
void fadeSet(s32, f32);
s32 heroItemAddItemDataId(Hero*, u32, u16, s32);
s32 heroItemCheckAddItemDataId(Hero*, u32);
u16 itemBiosGetItemDataId(u8*);
u16 itemBiosGetNum(u8*);
u8 itemCheckValid(u8*);
u32 itemDataBiosGetDoc(u8*);
u8 itemDataBiosGetKind(u8*);
u32 itemDataBiosGetName(u8*);
u8* itemDataBiosGetPtr(u16);
void menuButtonNormal(tagWINDOW_WORK*);
void menuClose(s32);
void menuCloseSync(s32, s32);
s32 menuOpen(s32, s32);
s32 menuOpenCustom(s32, ...);
s32 menuPocketInputNumber(tagWINDOW_WORK*, s32, s32, u16, s32, s32, s32);
void menuPtPlaySe__FUl(u32);
void menuSubCursorAnimeInit(void);
void menuSubCursorAnimeMain(void);
void menuSubCursorAnimeStart(void);
void menuSubCursorAnimeValGet(f32*, s32*);
void msgctrlSetValue(s32, u32);
void pcboxDelItem(void*, u32, u16);
u8* pcboxGetItem(void*, s16);
u16 pcboxGetNbItemSlot(void*);
void pcboxSwapItemSlot(void*, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void spriteSetScissor(s32, s32, s32, s32, s32);
void winMsgClose(bool);
s32 winMsgOpen(s8, u32, bool, bool);
void winSeqSetMenu(s32, u32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void winSpriteSetDisp(tagSPRITE_WORK*, bool);
void windowDrawSpriteCursor(s32, s16, s32, tagWINDOW_WORK*, s32, s32, s32, f32*, s32);
s32 windowGetActiveID(void);
u16 windowGetKeyRepeat(void);
u16 windowGetKeyTrg(void);
tagSPRITE_WORK* menuPtSpriteWorkGetByItemID__FP14tagWINDOW_WORKUll(tagWINDOW_WORK*, u32, s32);
HIKI_ITEM_POS* menuPtItemGetBySpriteWork__FP14tagWINDOW_WORKP14tagSPRITE_WORK(tagWINDOW_WORK*, tagSPRITE_WORK*);
}

static s32 beforCursorPosition;
static f32 CurPos;
static s32 IsScroll;
static s32 IrekaeSlotID;
static u32 ExplanationMsgID;
static s32 Mode;
static s32 CursorOfs;
static s32 CursorPos;
static f32 _RollUpTime;
static s32 NumValue;

static s32 menuPcBoxDouguConfirm(void);
static s32 _getItemListLineHeight(void);
static void setExplanationMsgID(u32);
static void hikidasu(int pos);
static void suteru(int pos);

#define W90(w) (*(u32*)(w)->color)
extern "C" {
s32 fn_8006A84C(void) { return 0; }
}

static s32 menuPcBoxDouguConfirm(void) {
    s32 r;
    menuSubCursorAnimeInit();
    beforCursorPosition = 0;
    r = menuOpen(0x8D, 1);
    menuClose(0x8D);
    menuCloseSync(0x8D, 1);
    s32 ret;
    if (r == -1) {
        ret = 0;
    } else if (r == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

extern "C" {
s32 menuPcBoxDouguConfirmDrawCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int y = w->cursor * 0x22;
    HIKI_ITEM_POS* item = menuPtItemGetBySpriteWork__FP14tagWINDOW_WORKP14tagSPRITE_WORK(w, sp);
    if (sp->id == 0x4BA) {
        if (beforCursorPosition != w->cursor) {
            menuSubCursorAnimeStart();
        }
        f32 anim[2] = {0.0f, 0.0f};
        s32 color = -1;
        if (w->menuID == windowGetActiveID()) {
            menuSubCursorAnimeValGet(anim, &color);
        }
        windowDrawSpriteCursor(0, y, -1, w, 0xC2, 0, winSpriteGetLayerID(w, sp), anim, color);
        winSpriteSetDisp(sp, false);
        beforCursorPosition = w->cursor;
    } else {
        sp->y = item->y + y;
    }
    return 0;
}
}

static s32 _getItemListLineHeight(void) {
    return 0x22;
}

static void printItemListDougu(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u32 color);
static u32 getItemNameMsg(u16 id);
static u16 getItemIDFromMenuPos(int pos);
static u16 getItemNumFromMenuPos(int pos);
static u8 getItemKind(u16 id);
static u32 getItemInstMsg(u32 id);
static s32 menuPcBoxDouguNum(int a, int b);
static void swapItemSlot(int a, int b);
static s32 getNbItemSlot(void);

void menuPcBoxDouguHikidashi(MENU_PCBOX_DOUGU_HIKIDASHI_MODE mode) {
    s32 pos;
    Mode = mode;
    menuOpen(0x8A, 0);
    fadeSet(2, 0.5f);
    fadeCheck(1);
    for (;;) {
        if (menuOpen(0x8B, 1) == -1) {
            break;
        }
        pos = CursorOfs + CursorPos;
        if (getItemIDFromMenuPos(pos) == 0) {
            break;
        }
        switch (mode) {
        case HIKIDASHI_HIKIDASU:
            hikidasu(pos);
            break;
        case HIKIDASHI_SUTERU:
            suteru(pos);
            break;
        }
    }
    menuClose(0x8B);
    menuCloseSync(0x8B, 1);
    fadeSet(3, 0.5f);
    fadeCheck(1);
    menuClose(0x8A);
}

static void hikidasu(int pos) {
    enum TsE { TsE0 };
    enum TsE id = (enum TsE)(getItemIDFromMenuPos(pos));
    s32 n;
    setExplanationMsgID(0x3BBD);
    if (getItemKind(id) != 5) {
        n = menuPcBoxDouguNum(1, getItemNumFromMenuPos(pos));
    } else {
        n = 1;
    }
    if (n > 0) {
        if (heroItemCheckAddItemDataId(0, id) < n) {
            menuPtPlaySe__FUl(0x13);
            winMsgOpen(2, 0x3BC2, 1, 0);
            winMsgClose(1);
            return;
        }
        heroItemAddItemDataId(0, id, n, -1);
        pcboxDelItem(0, id, n);
        msgctrlSetValue(0x2D, (u16)id);
        msgctrlSetValue(0x2F, n);
        winMsgOpen(2, 0x3BC3, 1, 0);
        winMsgClose(1);
    }
}

static void suteru(int pos) {
    u16 id = getItemIDFromMenuPos(pos);
    s32 n;
    if (getItemKind(id) == 5) {
        menuPtPlaySe__FUl(0x13);
        winMsgOpen(2, 0x3BC5, 1, 0);
        winMsgClose(1);
        return;
    }
    setExplanationMsgID(0x3BBE);
    n = menuPcBoxDouguNum(1, getItemNumFromMenuPos(pos));
    if (n > 0) {
        msgctrlSetValue(0x2D, (u16)id);
        msgctrlSetValue(0x2F, n);
        setExplanationMsgID(0x3BBF);
        if (menuPcBoxDouguConfirm() != 0) {
            pcboxDelItem(0, id, n);
            msgctrlSetValue(0x2F, n);
            msgctrlSetValue(0x2D, (u16)id);
            winMsgOpen(2, 0x3BC4, 1, 0);
            winMsgClose(1);
        }
    }
}

extern "C" {
s32 menuPcBoxDouguHikidashiCtrl(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(0x8B, 0x90);
            u16 cur = getItemIDFromMenuPos(CursorOfs + CursorPos);
            u32 msg;
            if (cur != 0) {
                msg = getItemInstMsg(cur);
            } else {
                msg = 0x3BBB;
            }
            setExplanationMsgID(msg);
            IsScroll = 0;
            CurPos = 0.0f;
            IrekaeSlotID = -1;
            w->seqSet = 1;
            menuSubCursorAnimeInit();
        }
        break;
    case 2:
        if (CurPos > 0.0f) {
            CurPos = CurPos - (f32)(_getItemListLineHeight() / 4);
            if (CurPos < 0.0f) {
                CurPos = 0.0f;
            }
        }
        if (CurPos < 0.0f) {
            CurPos = CurPos + (f32)(_getItemListLineHeight() / 4);
            if (CurPos > 0.0f) {
                CurPos = 0.0f;
            }
        }
        _RollUpTime += 0.033333335f;
        if (_RollUpTime > 1.0f) {
            _RollUpTime = 0.0f;
        }
        menuSubCursorAnimeMain();
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(0x8B, 0x94);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

void menuPcBoxDouguHikidashiButton(tagWINDOW_WORK* w) {
    if (IrekaeSlotID < 0) {
        menuButtonNormal(w);
    }
}

s32 menuPcBoxDouguHikidashiCursor(tagWINDOW_WORK* w) {
    u16 repeat = windowGetKeyRepeat();
    u16 trg = windowGetKeyTrg();
    s32 cur, ofs;
    s32 pos, limit, pages;
    if (CurPos != 0.0f) {
        return 0;
    }
    pos = CursorOfs + CursorPos;
    if (IrekaeSlotID < 0) {
        if ((trg & 0xC0) != 0 && getItemIDFromMenuPos(pos) != 0) {
            IrekaeSlotID = pos;
            menuPtPlaySe__FUl(0x442);
        }
    } else if ((trg & 0xD0) != 0) {
        if (getItemIDFromMenuPos(pos) != 0) {
            swapItemSlot(IrekaeSlotID, pos);
            menuPtPlaySe__FUl(0x442);
        } else {
            menuPtPlaySe__FUl(0x443);
        }
        IrekaeSlotID = -1;
    } else if ((trg & 0x20) != 0) {
        IrekaeSlotID = -1;
        menuPtPlaySe__FUl(0x443);
    }
    limit = getNbItemSlot() + 1;
    pages = (limit + 7) / 8;
    cur = CursorPos;
    ofs = CursorOfs;
    if ((repeat & 2) != 0) {
        s32 next = cur + 1;
        CursorPos = next;
        if (next + ofs >= limit) {
            CursorPos = next - 1;
        } else {
            if (next >= 8) {
                CursorOfs = ofs + 1;
                CursorPos = next - 1;
                IsScroll = 1;
            } else {
                IsScroll = 0;
            }
            CurPos = (f32)-_getItemListLineHeight();
            menuPtPlaySe__FUl(0x441);
        }
    } else if ((repeat & 1) != 0) {
        if (cur > 0 || ofs > 0) {
            s32 prev = CursorPos - 1;
            CursorPos = prev;
            if (prev < 0) {
                CursorPos = 0;
                CursorOfs = CursorOfs - 1;
                IsScroll = 1;
            } else {
                IsScroll = 0;
            }
            CurPos = (f32)_getItemListLineHeight();
            menuPtPlaySe__FUl(0x441);
        }
    } else if ((repeat & 8) != 0) {
        s16 last = limit - 8;
        if (pages == 1) {
            CursorPos = (s16)(limit - 1);
        } else if (ofs == last) {
            CursorPos = 7;
        } else {
            CursorOfs = ofs + 8;
            if (CursorOfs > last) {
                CursorOfs = last;
            }
        }
        if (ofs != CursorOfs || cur != CursorPos) {
            menuPtPlaySe__FUl(0x444);
        }
    } else if ((repeat & 4) != 0) {
        if (ofs == 0) {
            CursorPos = 0;
        } else {
            CursorOfs = ofs - 8;
            if (CursorOfs < 0) {
                CursorOfs = 0;
            }
        }
        if (ofs != CursorOfs || cur != CursorPos) {
            menuPtPlaySe__FUl(0x444);
        }
    }
    if (ofs != CursorOfs || cur != CursorPos) {
        menuSubCursorAnimeStart();
    }
    u32 msg;
    if (IrekaeSlotID >= 0) {
        msg = 0x3BBC;
    } else {
        u16 id = getItemIDFromMenuPos(CursorOfs + CursorPos);
        if (id != 0) {
            msg = getItemInstMsg(id);
        } else {
            msg = 0x3BBB;
        }
    }
    setExplanationMsgID(msg);
    return 0;
}
}

static void setExplanationMsgID(u32 id) {
    ExplanationMsgID = id;
}

extern "C" {
s32 menuPcBoxDouguHikidasuDrawExplanationText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    GSmsgPrint2(winSpriteGetLayerID(w, sp), 0, 0, W90(w), ExplanationMsgID);
    return 0;
}

s32 menuPcBoxDouguHikidasuDrawLineCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    HIKI_ITEM_POS* item = menuPtItemGetBySpriteWork__FP14tagWINDOW_WORKP14tagSPRITE_WORK(w, sp);
    int y;
    if (IrekaeSlotID >= 0) {
        s32 d = IrekaeSlotID - CursorOfs;
        y = item->y + d * _getItemListLineHeight();
        if (IsScroll != 0) {
            y -= (s32)CurPos;
        }
        winSpriteSetDisp(sp, d >= 0 && d < 8);
    } else {
        y = item->y + CursorPos * _getItemListLineHeight();
        if (IsScroll == 0) {
            y += (s32)CurPos;
        }
        winSpriteSetDisp(sp, true);
    }
    sp->y = y;
    return 0;
}

s32 menuPcBoxDouguHikidasuDrawCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int y = CursorPos * _getItemListLineHeight();
    if (IsScroll == 0) {
        y += (s32)CurPos;
    }
    f32 anim[2] = {0.0f, 0.0f};
    s32 color = -1;
    if (w->menuID == windowGetActiveID()) {
        menuSubCursorAnimeValGet(anim, &color);
    }
    windowDrawSpriteCursor(0, y, -1, w, 0xC2, 0, winSpriteGetLayerID(w, sp), anim, color);
    winSpriteSetDisp(sp, false);
    return 0;
}

s32 menuPcBoxDouguHikidasuDrawItemText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    tagSPRITE_WORK* base = menuPtSpriteWorkGetByItemID__FP14tagWINDOW_WORKUll(w, 0x4A7, 0);
    spriteSetScissor(winSpriteGetLayerID(w, sp), base->x - sp->x, base->y - sp->y, base->w, base->h);
    printItemListDougu(w, sp, W90(w));
    spriteClearScissor(winSpriteGetLayerID(w, sp));
    spriteSetEnv(winSpriteGetLayerID(w, sp));
    return 0;
}
}

static void printItemListDougu(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u32 color) {
    s16 w2;
    s32 idx;
    s32 last;
    s32 scroll;
    s32 count;
    s32 numW;
    u16 id;
    s32 row;
    s32 nameW;
    s32 first;
    s32 xAdj;
    first = 0;
    last = 8;
    scroll = 0;
    count = getNbItemSlot();
    idx = CursorOfs;
    msgctrlSetValue(0x34, 999);
    nameW = (s16)(GSmsgGetRect(0x4270) >> 16);
    numW = nameW + (s16)(GSmsgGetRect(0x428F) >> 16);
    if (CurPos != 0.0f && IsScroll != 0) {
        if (CurPos < 0.0f) {
            idx--;
            first = -1;
        } else {
            last = 9;
        }
        scroll = (s32)CurPos;
    }
    xAdj = 0x11A - numW;
    for (row = first; row < last && idx < count; row++, idx++) {
        if (idx >= 0) {
            s32 y = row * _getItemListLineHeight() - scroll;
            u32 name;
            id = getItemIDFromMenuPos(idx);
            name = getItemNameMsg(id);
            if (name != 0) {
                GSmsgPrint2(winSpriteGetLayerID(w, sp), 0, y, color, name);
            }
            u32 cmpv = getItemKind(id);
            if (cmpv != 5) {
                GSmsgPrint2(winSpriteGetLayerID(w, sp), xAdj, y, color, 0x428F);
                msgctrlSetValue(0x34, getItemNumFromMenuPos(idx));
                w2 = GSmsgGetRect(0x4270) >> 16;
                GSmsgPrint2(winSpriteGetLayerID(w, sp), 0x11A - w2, y, color, 0x4270);
            }
        }
    }
    if (row < last) {
        id = row * _getItemListLineHeight();
        GSmsgPrint2(winSpriteGetLayerID(w, sp), 0, (id - scroll), (u16)color, 0x3BBA);
    }
}

extern "C" {
s32 menuPcBoxDouguHikidasuDrawRollUp(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    bool on;
    if (CursorOfs > 0) {
        on = true;
    } else {
        on = false;
    }
    sp->alpha = 255.0f * (1.0f - _RollUpTime);
    winSpriteSetDisp(sp, on);
    return 0;
}

s32 menuPcBoxDouguHikidasuDrawRollDown(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    s32 bottom = CursorOfs + 8;
    bool on;
    if (bottom < getNbItemSlot() + 1) {
        on = true;
    } else {
        on = false;
    }
    sp->alpha = 255.0f * (1.0f - _RollUpTime);
    winSpriteSetDisp(sp, on);
    return 0;
}

s32 menuPcBoxDouguHikidasuDrawTitleText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    s32 msg;
    HIKI_ITEM_POS* item;
    s16 tw;
    if (Mode == 0) {
        msg = 0x3BC0;
    } else {
        msg = 0x3BC1;
    }
    sp->msgID = msg;
    item = menuPtItemGetBySpriteWork__FP14tagWINDOW_WORKP14tagSPRITE_WORK(w, sp);
    s16 half = sp->w / 2;
    tw = GSmsgGetRect(msg) >> 16;
    sp->x = item->x + (s16)(half - tw / 2);
    return 0;
}
}

static s32 getNbItemSlot(void) {
    u16 count;
    int i;
    s32 n = 0;
    count = pcboxGetNbItemSlot(0);
    for (i = 0; i < count; i++) {
        u8* item = pcboxGetItem(0, (s16)i);
        if (itemCheckValid(item)) {
            n++;
        }
    }
    return n;
}

static u16 getItemIDFromMenuPos(int pos) {
    u16 count = pcboxGetNbItemSlot(0);
    u8* item;
    int i;
    s32 n = -1;
    for (i = 0; i < count; i++) {
        item = pcboxGetItem(0, (s16)i);
        if (itemCheckValid(item)) {
            n++;
            if (n >= pos) {
                return itemBiosGetItemDataId(item);
            }
        }
    }
    return 0;
}

static u32 getItemNameMsg(u16 id) {
    return itemDataBiosGetName(itemDataBiosGetPtr(id));
}

static u16 getItemNumFromMenuPos(int pos) {
    u16 count = pcboxGetNbItemSlot(0);
    u8* item;
    int i;
    s32 n = -1;
    for (i = 0; i < count; i++) {
        item = pcboxGetItem(0, (s16)i);
        if (itemCheckValid(item)) {
            n++;
            if (n >= pos) {
                return itemBiosGetNum(item);
            }
        }
    }
    return 0;
}

static u32 getItemInstMsg(u32 id) {
    return itemDataBiosGetDoc(itemDataBiosGetPtr(id));
}

static void swapItemSlot(int a, int b) {
    pcboxSwapItemSlot(0, a, b);
}

static u8 getItemKind(u16 id) {
    return itemDataBiosGetKind(itemDataBiosGetPtr(id));
}

static s32 menuPcBoxDouguNum(int value, int max) {
    s32 limit;
    s32 mode;
    s32 r;
    NumValue = value;
    mode = 2;
    limit = max;
    r = menuOpenCustom(0x8C, windowGetActiveID(), &mode, 0, 1, 1, &limit);
    menuClose(0x8C);
    menuCloseSync(0x8C, 1);
    if (r == -1 || NumValue == 0) {
        return -1;
    }
    return NumValue;
}

extern "C" {
s32 menuPcBoxDouguNumCtrl(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(0x8C, 0x70);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(0x8C, 0x74);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

s32 menuPcBoxDouguNumCursor(tagWINDOW_WORK* w) {
    s32 i;
    s32* max = (s32*)w->params[0];
    NumValue = menuPocketInputNumber(w, NumValue, *max, windowGetKeyRepeat(), 3, 0x441, 0x444);
    for (i = 0; i < 3; i++) {
        winSpriteSetDisp(menuPtSpriteWorkGetByItemID__FP14tagWINDOW_WORKUll(w, 0x4AB, 2 - i), i == w->cursor);
    }
    return 0;
}

s32 menuPcBoxDouguNumDrawNum(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    s32 index, i, div;
    s32 ids[3] = {0x4B0, 0x4AF, 0x4AE};
    for (index = 0; index < 3; index++) {
        if (sp->id == ids[index]) {
            break;
        }
    }
    if (index >= 3) {
        return 0;
    }
    div = 1;
    for (i = 0; i < index; i++) {
        div *= 10;
    }
    s32 digit = NumValue / div;
    digit %= 10;
    msgctrlSetValue(0x34, digit);
    GSmsgPrintRight(winSpriteGetLayerID(w, sp), 0, 0, sp->w, sp->h, W90(w), 0x4270);
    return 0;
}
}
