#include <dolphin/types.h>

#pragma peephole off

struct tagWINDOW_WORK {
    u8 used;
    u8 state;
    s8 seqSet;
    u8 pad3;
    s32 menuID;
    u8 pad8;
    s8 priority;
    u8 closeFlag;
    u8 enablePort;
    u8 pad_c[0x80];
    s16 offX;
    s16 offY;
    u8 pad_90[3];
    u8 b93;
    u8 pad_94[0x10];
    u8 pad_a4;
    u8 pad_a5;
};

struct tagSPRITE_WORK {
    u8 pad0[0x50];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
};

struct KeyInfo {
    u16 on;
    u16 up;
    u16 trg;
    u16 rep;
};

struct WinMsgWork {
    void* msg;
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u32 key;
    s16 w;
    s16 h;
};

extern "C" {
WinMsgWork* windowGetFreeWork(tagWINDOW_WORK*);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void* GSgfxLayerFindByID(s32);
void spriteSetOffset(s32, s16, s16);
void spriteSetEnv(s32);
void menuSubDrawMsgWindow2(s32, s32, s16, s16, s16, u8, u8);
void GSmsgMain(s32, void*, u32, bool);
void GSmsgKill(void*);
s8 GSmsgGetRect(void*);
void GSmsgExec(void*, u8, u8);
s32 GSmsgIsCheck(void*);
u32 windowGetParam(tagWINDOW_WORK*, u32);
bool winSeqIsCheck(s32, u16);
void winSeqSetMenu(s32, s32);
KeyInfo* windowGetKeyInfo(void);
tagWINDOW_WORK* windowSearchID(s32);
s32 windowGetActiveID(void);
u8 menuIsCheck(s32);
s32 menuCloseCustom(s32, s32, bool);
s32 menuOpenCustom(s32, s32, void*, s32, bool, ...);
void GSthreadSwitch(void);
}

static s8 _winMsgType = -1;
static s16 menuPos = -2;
static u8 _winMsgOpenErrWin;

extern "C" {
void winMsgClose(bool flag);
s32 winMsgOpen(s8 type, void* msg, bool a, bool b);
s32 winMsgCheck(void);
}

static s32 _winMsgOpenSub(s8 type, void* msg, bool a, bool b, bool c, u8 d, bool e);
static s32 _winMsgGetMenuID(s8 type);

extern "C" {

s32 winMsgDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp)
{
    WinMsgWork* fw = windowGetFreeWork(w);
    s32 layer = winSpriteGetLayerID(w, sp);
    s32 mw;
    s32 mh;
    GSgfxLayerFindByID(layer);
    if (w->menuID == 0x53) {
        mw = fw->w;
        mh = fw->h;
    } else {
        mw = sp->w;
        mh = sp->h;
    }
    spriteSetOffset(layer, w->offX + sp->x, sp->y + ((s16)(sp->h - 4 - mh) + w->offY));
    spriteSetEnv(layer);
    switch (w->menuID) {
    case 0x14:
        menuSubDrawMsgWindow2(layer, 0, menuPos, mw, mh, w->b93, 1);
        break;
    case 0x2a:
        break;
    case 0x52:
    case 0x53:
        menuSubDrawMsgWindow2(layer, 0, menuPos, mw, mh, w->b93, 1);
        break;
    }
    switch ((s8)w->state) {
    case 0:
    case 1:
        break;
    case 2:
        if (w->menuID != 0x14) {
            GSmsgMain(layer, fw->msg, fw->key, ((s8)w->used & 4) == 0);
            fw->key = 0;
        }
        break;
    case 3:
    case 5:
        break;
    }
    return 0;
}

s32 winMsgCtrlYesNo(tagWINDOW_WORK* w)
{
    switch ((s8)w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x24);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x17b);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

s32 winMsgCtrl(tagWINDOW_WORK* w)
{
    WinMsgWork* fw = windowGetFreeWork(w);
    u8 flag = 0;
    switch ((s8)w->state) {
    case 0:
        if (fw->msg != 0) {
            GSmsgKill(fw->msg);
        }
        fw->msg = (void*)windowGetParam(w, 0);
        fw->b4 = windowGetParam(w, 1) != 0;
        fw->b5 = windowGetParam(w, 2);
        if (w->seqSet == 0) {
            flag = 1;
        }
        if (winSeqIsCheck(w->menuID, 0x2c) == 1) {
            flag = 1;
        }
        if (w->closeFlag != 0) {
            flag = 1;
        }
        if (flag != 0) {
            if (w->menuID != 0x2a) {
                if (w->menuID != 0x52) {
                    winSeqSetMenu(w->menuID, 0x28);
                } else {
                    winSeqSetMenu(w->menuID, 0x24);
                }
            }
            w->seqSet = 1;
        }
        if (w->menuID == 0x53) {
            u32 r = GSmsgGetRect(fw->msg);
            fw->h = r;
            fw->w = r >> 16;
        }
        break;
    case 2:
        switch (w->seqSet) {
        case 0:
                s32 rf_t = fw->b4;
                GSmsgExec(fw->msg, rf_t, fw->b5);
                w->seqSet = 1;
            break;
        }
        if (GSmsgIsCheck(fw->msg) != 0) {
            w->pad_a4 = 0;
        } else {
            w->pad_a4 = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            if (w->menuID != 0x2a) {
                if (w->menuID != 0x52) {
                    winSeqSetMenu(w->menuID, 0x2c);
                } else {
                    winSeqSetMenu(w->menuID, 0x17b);
                }
            }
            w->seqSet = 1;
        }
        break;
    case 5:
        GSmsgKill(fw->msg);
        fw->msg = 0;
        break;
    }
    return 0;
}

void winMsgButton(tagWINDOW_WORK* w)
{
    WinMsgWork* fw = windowGetFreeWork(w);
    fw->key = windowGetKeyInfo()->trg;
}

void winMsgCloseLevelUpStatus(bool flag)
{
    winMsgClose(flag);
}

s32 winMsgOpenLevelUpFiledStatus(void* msg, bool a)
{
    return _winMsgOpenSub(9, msg, a, true, false, 0, false);
}

s32 winMsgOpenLevelUpStatus(void* msg, bool a)
{
    return _winMsgOpenSub(5, msg, a, true, false, 0, false);
}

void winMsgCloseError(void)
{
    s32 menu = _winMsgGetMenuID(6);
    if (menuIsCheck(menu)) {
        menuCloseCustom(menu, 2, 0);
    }
    _winMsgOpenErrWin = 0;
}

s32 winMsgOpenError(void* msg, bool a, bool b)
{
    return _winMsgOpenSub(6, msg, a, b, false, 0, false);
}

void winMsgCloseFight(bool flag)
{
    winMsgClose(flag);
}

u8 winMsgCloseCheckFight(void)
{
    return (s8)winMsgCheck() >= 0;
}

s32 winMsgOpenFightNoWait(void* msg, bool a, bool b)
{
    return _winMsgOpenSub(4, msg, a, b, true, 0, false);
}

s32 winMsgOpenFight2(void* msg, bool a, bool b, bool c)
{
    return _winMsgOpenSub(4, msg, a, b, false, 0, c);
}

s32 winMsgOpenFight(void* msg, bool a, bool b)
{
    return winMsgOpen(4, msg, a, b);
}

s8 winMsgCheckField(void)
{
    return winMsgCheck();
}

void winMsgCloseField(bool flag)
{
    winMsgClose(flag);
}

s32 winMsgOpenFieldWithSE(void* msg, bool a, bool b, u8 se)
{
    return _winMsgOpenSub(3, msg, a, b, false, se, false);
}

s32 winMsgOpenField(void* msg, bool a, bool b)
{
    return _winMsgOpenSub(3, msg, a, b, false, 0, false);
}

s32 winMsgCheck(void)
{
    tagWINDOW_WORK* w = windowSearchID(_winMsgGetMenuID(_winMsgType));
    if (w == 0) {
        return -1;
    }
    if (w->pad_a4 != 0) {
        return 0;
    }
    if (w->pad_a5 == 0) {
        return 1;
    }
    return 0;
}

#pragma dont_inline on
void winMsgClose(bool flag)
{
    if (_winMsgOpenErrWin != 0) {
        if (flag != 0) {
            do {
                GSthreadSwitch();
            } while (_winMsgOpenErrWin != 0);
        } else {
            return;
        }
    }
    {
        s32 menu = _winMsgGetMenuID(_winMsgType);
        if (menuIsCheck(menu)) {
            menuCloseCustom(menu, 2, flag);
        }
        _winMsgType = -1;
    }
}
#pragma dont_inline reset

s32 winMsgOpenWithSE(s8 type, void* msg, bool a, bool b, u8 se)
{
    return _winMsgOpenSub(type, msg, a, b, false, se, false);
}

s32 winMsgOpen(s8 type, void* msg, bool a, bool b)
{
    return _winMsgOpenSub(type, msg, a, b, false, 0, false);
}

}

static s32 _winMsgOpenSub(s8 type, void* msg, bool a, bool b, bool c, u8 d, bool e)
{
    s32 parentID;
    u8 flags = 0;
    if (_winMsgGetMenuID(type) == 0) {
        return 0;
    }
    if (type != 6) {
        if (type != _winMsgType) {
            winMsgClose(a);
        }
        _winMsgType = type;
        parentID = windowGetActiveID();
    } else {
        _winMsgOpenErrWin = 1;
        parentID = -1;
        a = false;
        c = true;
    }
    if (b) {
        flags |= 1;
    }
    if (c) {
        flags |= 2;
    }
    return menuOpenCustom(_winMsgGetMenuID((u16)type), (u8)parentID, 0, e ? 2 : 0, a, 3, msg, flags, (u32)d);
}

static s32 _winMsgGetMenuID(s8 type)
{
    s32 id = 0;
    switch (type) {
    case 0:
        id = 0x52;
        break;
    case 1:
        id = 0x34;
        break;
    case 2:
        id = 0x33;
        break;
    case 3:
        id = 0x52;
        break;
    case 4:
        id = 0x53;
        break;
    case 5:
        id = 0x14;
        break;
    case 6:
        id = 0x2a;
        break;
    case 7:
        id = 0xb6;
        break;
    case 9:
        id = 0x29;
        break;
    }
    return id;
}
