#include <dolphin/types.h>

// Menu files were built without the peephole optimizer.
#pragma peephole off

struct MailCursor {
    s16 top;
    s16 pos;
};

// Parameters handed to the mail menu window.
struct MailMenuParam {
    u8 mode;
    void* unk4;
    MailCursor* cursor;
};

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    s8 seqSet;
    u8 unk3;
    void* seq;
    u8 unk8[0x60];
    MailMenuParam* param;
};

struct tagSPRITE_WORK {
    u8 unk0[6];
    s16 id;
    u8 unk8[0x44];
    u32 msgID;
    u8 unk50[0x14];
    u8 color[3];
};

struct WindowKeyInfo {
    u16 trigger;
};

extern "C" {
void menuPdaSetSubres(s32, s32);
s32 menuOpen(s32 menuID, s32);
s32 menuOpenCustom(s32 menuID, ...);
s32 windowGetActiveID(void);
bool menuScriptCheckMailOpen(void);
void menuClose(s32 menuID);
void menuCloseSync(s32 menuID, s32);
WindowKeyInfo* windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
bool winSeqCheckMove(void* seq);
void winSeqSetMenu(void* seq, s32 menu);
void menuButtonNormal(tagWINDOW_WORK* window);
int pdaMailGetMailID(int index);
u32 mailGetAttachFileGroup(int id);
u32 mailGetSenderName(int id);
u32 mailGetSubject(int id);
u32 mailGetContents(int id);
int mailGetNbMailInMailbox(void);
char* GSmsgGetGSchar(u32 msg);
void msgctrlSetValue(s32 id, u32 value);
void GSsndPlayNow(u32 id);
void menuPlaySe(void* seq, s32);
}

static s32 _mailHonbun(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static s32 _mailSender(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static s32 _mailSubject(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static void _menuClose(long menuID);

static MailCursor _cursor;

#define MAIL_MENU 0x6F

extern "C" {

s32 menuPdaMailCallBack(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0xAA:
        _mailHonbun(window, sprite);
        break;
    case 0xAB:
        _mailSender(window, sprite);
        break;
    case 0xAC:
        _mailSubject(window, sprite);
        break;
    }
    return 0;
}

void menuPdaMailXDScript(int top) {
    MailMenuParam param;
    s32 result;
    _cursor.pos = 0;
    _cursor.top = top;
    param.mode = 0;
    menuPdaSetSubres(2, 2);
    menuOpen(0x77, 0);
    do {
        param.cursor = &_cursor;
        result = menuOpenCustom(MAIL_MENU, windowGetActiveID(), 0, 0, 1, 1, &param);
    } while (!menuScriptCheckMailOpen() && result != -1);
    _menuClose(MAIL_MENU);
    _menuClose(0x77);
}

MailCursor* menuPdaMailXD(MailCursor* cursor, u8 mode, void* arg) {
    MailMenuParam param;
    _cursor.pos = cursor->pos;
    _cursor.top = cursor->top;
    param.mode = mode;
    if (mode == 0) {
        param.unk4 = arg;
    }
    do {
        param.cursor = &_cursor;
    } while (menuOpenCustom(MAIL_MENU, windowGetActiveID(), 0, 0, 1, 1, &param) != -1);
    _menuClose(MAIL_MENU);
    return &_cursor;
}

void menuPdaMailContentsButtonXD(tagWINDOW_WORK* window) {
    WindowKeyInfo* key = windowGetKeyInfo();
    MailCursor* cursor = window->param->cursor;
    int index = cursor->pos + cursor->top;
    if (window != NULL) {
        if (winSeqCheckMove(window->seq)) {
            return;
        }
        index = pdaMailGetMailID(index);
        if (!menuScriptCheckMailOpen() && mailGetAttachFileGroup(index) == 0 && (key->trigger & 0x10)) {
            return;
        }
    }
    menuButtonNormal(window);
}

s32 menuPdaMailContentsCursorXD(tagWINDOW_WORK* window) {
    MailMenuParam* param = window->param;
    MailCursor* cursor;
    int num;
    int visible;
    s16 old;
    u16 repeat;

    windowGetKeyInfo();
    cursor = param->cursor;
    if (param->mode == 0) {
        return 0;
    }
    num = mailGetNbMailInMailbox();
    visible = 5;
    old = cursor->pos + cursor->top;
    repeat = windowGetKeyRepeat();
    if (num < 5) {
        visible = num;
    }
    if (repeat & 1) {
        if (cursor->pos + cursor->top != 0) {
            GSsndPlayNow(0x450);
        }
        cursor->pos--;
    } else if (repeat & 2) {
        if (num - 1 != cursor->pos + cursor->top) {
            GSsndPlayNow(0x450);
        }
        cursor->pos++;
    }
    if (cursor->pos < 0) {
        cursor->top += cursor->pos;
        cursor->pos = 0;
        if (cursor->top < 0) {
            cursor->top = 0;
            cursor->pos = 0;
        }
    } else if (cursor->pos >= visible) {
        cursor->top = cursor->top + (cursor->pos - (visible - 1));
        cursor->pos = (s8)(visible - 1);
        if (cursor->top + cursor->pos >= num) {
            cursor->pos = (s8)(visible - 1);
            cursor->top = (s8)(num - visible);
        }
    }
    if (old != cursor->pos + cursor->top) {
        menuPlaySe(window->seq, 1);
    }
    return 0;
}

s32 menuPdaMailCtrlXD(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x132);
            window->seqSet = 1;
        }
        break;
    case 1:
        menuScriptCheckMailOpen();
        break;
    case 2:
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

}

static s32 _mailSender(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    MailCursor* cursor = window->param->cursor;
    u32 name = mailGetSenderName(pdaMailGetMailID(cursor->pos + cursor->top));
    if (name != 0) {
        u32 str = (u32)GSmsgGetGSchar(name);
        msgctrlSetValue(0x37, str);
        sprite->msgID = 0x4276;
    } else {
        sprite->msgID = 0;
    }
    sprite->color[0] = 0xF0;
    sprite->color[1] = 0xF0;
    sprite->color[2] = 0xF0;
    return 0;
}

static s32 _mailSubject(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    MailCursor* cursor = window->param->cursor;
    u32 subject = mailGetSubject(pdaMailGetMailID(cursor->pos + cursor->top));
    if (subject != 0) {
        u32 str = (u32)GSmsgGetGSchar(subject);
        msgctrlSetValue(0x37, str);
        sprite->msgID = 0x4276;
    } else {
        sprite->msgID = 0;
    }
    sprite->color[0] = 0xD5;
    sprite->color[1] = 0xAA;
    sprite->color[2] = 0x33;
    return 0;
}

static s32 _mailHonbun(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    MailCursor* cursor = window->param->cursor;
    sprite->msgID = mailGetContents(pdaMailGetMailID(cursor->pos + cursor->top));
    return 0;
}

static void _menuClose(long menuID) {
    menuClose(menuID);
    menuCloseSync(menuID, 1);
}
