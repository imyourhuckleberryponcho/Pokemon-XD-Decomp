#include <dolphin/types.h>

#pragma peephole off

struct CursorPos {
    s16 x;
    s16 y;
};

struct tagSPRITE_WORK {
    u8 pad0[0x6];
    s16 id;
    u8 pad8[0x5F];
    u8 alpha;
};

struct tagWINDOW_WORK {
    u8 pad0;
    s8 state;
    s8 seqSet;
    u8 pad3;
    s32 menuID;
    u8 pad8[0x14];
    s32 layer;
    u8 pad20[0x73];
    u8 alpha;
    u8 pad94[8];
    CursorPos pos;
    u8 padA0[4];
    u8 done;
    u8 cancel;
};

struct TitleOptionWork {
    s32 f0;
    s32 f4;
    s32 count;
    s32 flag;
    f32 rot;
    f32 f14;
    f32 amp;
    f32 dt;
    f32 t;
    f32 t2;
    f32 speed;
};

struct KeyInfo {
    u16 pad0;
    u16 pad2;
    u16 trg;
};

extern "C" {
double sin(double x);
void GSinputMotorStart(s32 pad, s32 a, s32 strength, s32 frames, s32 b);
u32 GSsndGetOutputMode();
void GSsndSetOutputMode(s32 mode);
s32 GSmsgPrint2(s32 layer, s32 x, s32 y, u32 color, u32 msg);
void fadeCheck(s32 type);
void fadeSet(s32 type, f32 time);
void fn_800A3A1C();
s32 gamedatasaveGetStatus(void* ptr, s32 kind);
void gamedatasaveSetStatus(void* ptr, s32 kind, s32 value);
u8 memcardIsMemCardValid();
s32 memcardTaskCall(s32 a, s32 b, s32 c);
void menuButtonNormal(tagWINDOW_WORK* w);
void menuCloseCustom(s32 menuID, s32 a, s32 b);
void menuCursorNormal(tagWINDOW_WORK* w, s32 flag);
s32 menuOpen(s32 menuID, s32 a);
void menuPdaSubCalcAlpha(f32* alpha, s32 count, s32 selected);
void menuPdaSubInitAlpha(f32* alpha, s32 count, s32 selected);
void menuPlaySe(s32 menuID, s32 se);
s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 initial);
void menuTitleCursorAnime(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
void menuTitleCursorAnimeMain();
void menuToolSetSelect(s32 sel);
f32 timeGetLastFrameSec(void);
void winMsgClose(bool flag);
s32 winMsgOpen(s8 type, s32 msg, bool a, bool b);
void winSeqSetMenu(s32 menuID, u32 id);
void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on);
KeyInfo* windowGetKeyInfo();
u16 windowGetKeyRepeat();
tagWINDOW_WORK* windowSearchID(s32 id);
}

static void _menuTitleOptionSetFrameSec();
static void _menuTitleOptionCalcRot();
static void _menuTitleOptionClose(long id);
static void _menuTitleOptionExit();
static void _menuTitleOptionInit();

static u32 _menuOptionMsgTable[3] = {0x42E7, 0x42E8, 0x42E9};

static TitleOptionWork _menuTitleOptionWork;
static f32 _atable[3];

extern "C" {

void menuTitleOptionCtrl(tagWINDOW_WORK* w) {
    menuTitleCursorAnimeMain();
    CursorPos pos = w->pos;
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x24);
            fadeSet(2, 0.5f);
            w->seqSet = 1;
        }
        break;
    case 2:
        menuPdaSubCalcAlpha(_atable, 3, pos.y);
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x17B);
            fadeSet(3, 0.5f);
            w->seqSet = 1;
        }
        break;
    }
}

s32 menuTitleOptionCursorControl(tagWINDOW_WORK* w) {
    CursorPos pos = w->pos;
    u16 keys;

    windowGetKeyInfo();
    keys = windowGetKeyRepeat();
    _menuTitleOptionSetFrameSec();
    _menuTitleOptionCalcRot();
    menuCursorNormal(w, 1);
    switch (pos.y) {
    case 0:
        if (keys & 4) {
            menuPlaySe(w->menuID, 1);
            GSsndSetOutputMode(1);
        }
        if (keys & 8) {
            menuPlaySe(w->menuID, 1);
            GSsndSetOutputMode(0);
        }
        break;
    case 1:
        if (keys & 4) {
            menuPlaySe(w->menuID, 1);
            if (gamedatasaveGetStatus(0, 9) != 0) {
                GSinputMotorStart(1, 0, 0xFF, 0x1E, 0);
            }
            gamedatasaveSetStatus(0, 9, 0);
            _menuTitleOptionWork.count = 1;
            _menuTitleOptionWork.t = 1.0f;
            _menuTitleOptionWork.flag = 1;
        }
        if (keys & 8) {
            menuPlaySe(w->menuID, 1);
            gamedatasaveSetStatus(0, 9, 1);
            _menuTitleOptionWork.amp = 0.0f;
        }
        break;
    }
    return 0;
}

}

static void _menuTitleOptionSetFrameSec() {
    _menuTitleOptionWork.dt = timeGetLastFrameSec();
    _menuTitleOptionWork.t2 += _menuTitleOptionWork.dt;
    if (_menuTitleOptionWork.t2 >= 1.0f) {
        _menuTitleOptionWork.t2 = 0.0f;
    }
    if (gamedatasaveGetStatus(0, 9) == 1) {
        if (_menuTitleOptionWork.t != 0.0f) {
            _menuTitleOptionWork.t += _menuTitleOptionWork.dt;
            if (_menuTitleOptionWork.t >= 1.0f) {
                _menuTitleOptionWork.t = 0.0f;
                _menuTitleOptionWork.count = 0;
            }
        }
    } else {
        _menuTitleOptionWork.t += _menuTitleOptionWork.dt;
        if (_menuTitleOptionWork.t >= 1.0f) {
            _menuTitleOptionWork.t = 0.0f;
            _menuTitleOptionWork.count++;
            if (_menuTitleOptionWork.count % 2 == 0) {
                _menuTitleOptionWork.flag ^= 1;
                if (_menuTitleOptionWork.flag != 0) {
                    _menuTitleOptionWork.amp = 0.0f;
                } else {
                    _menuTitleOptionWork.amp = 0.20943952f;
                }
            }
        }
    }
}

static void _menuTitleOptionCalcRot() {
    _menuTitleOptionWork.rot =
        _menuTitleOptionWork.amp * (f32)sin(6.2831855f * _menuTitleOptionWork.t * _menuTitleOptionWork.speed);
}

extern "C" {

void menuTitleOptionHook(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    CursorPos pos = w->pos;

    if (w->state < 3) {
        switch (sp->id) {
        case 0x5B:
            if (GSsndGetOutputMode() != 0) {
                winSpriteSetDisp(sp, true);
                if (pos.y == 0) {
                    menuTitleCursorAnime(w, sp);
                } else {
                    sp->alpha = 0xFF;
                }
            } else {
                winSpriteSetDisp(sp, false);
            }
            break;
        case 0x5C:
            if (GSsndGetOutputMode() != 0) {
                winSpriteSetDisp(sp, false);
            } else {
                winSpriteSetDisp(sp, true);
                if (pos.y == 0) {
                    menuTitleCursorAnime(w, sp);
                } else {
                    sp->alpha = 0xFF;
                }
            }
            break;
        case 0x5D:
            if (gamedatasaveGetStatus(0, 9) != 1) {
                winSpriteSetDisp(sp, true);
                if (pos.y == 1) {
                    menuTitleCursorAnime(w, sp);
                } else {
                    sp->alpha = 0xFF;
                }
            } else {
                winSpriteSetDisp(sp, false);
            }
            break;
        case 0x5E:
            if (gamedatasaveGetStatus(0, 9) != 1) {
                winSpriteSetDisp(sp, false);
            } else {
                winSpriteSetDisp(sp, true);
                if (pos.y == 1) {
                    menuTitleCursorAnime(w, sp);
                } else {
                    sp->alpha = 0xFF;
                }
            }
            break;
        case 0x5F:
            if (pos.y == 2) {
                winSpriteSetDisp(sp, true);
                menuTitleCursorAnime(w, sp);
            } else {
                winSpriteSetDisp(sp, false);
            }
            break;
        case 0x56:
            sp->alpha = _atable[0];
            break;
        case 0x57:
            sp->alpha = _atable[1];
            break;
        case 0x58:
            sp->alpha = _atable[2];
            break;
        case 0x68:
            if (pos.y >= 0) {
                GSmsgPrint2(w->layer, 0, -8, w->alpha | 0xFFFFFF00, _menuOptionMsgTable[pos.y]);
            }
            break;
        }
    }
}

void menuTitleOption() {
    s32 state = 0;
    s32 running = 1;
    s32 mode;
    s32 saved;

    _menuTitleOptionInit();
    do {
        switch (state) {
        case 0:
            mode = GSsndGetOutputMode();
            saved = gamedatasaveGetStatus(0, 9);
            do {
                state = menuOpen(0x117, 1);
                tagWINDOW_WORK* w = windowSearchID(0x117);
                s16 c = w->pos.y;
                if (state < 0) {
                    GSsndSetOutputMode(mode);
                    gamedatasaveSetStatus(0, 9, saved);
                    break;
                }
                if (w == 0 || c == 2) {
                    break;
                }
            } while (true);
            state = 0x64;
            break;
        case 0x64:
            if (saved != gamedatasaveGetStatus(0, 9) && memcardIsMemCardValid()) {
                winMsgOpen(1, 0x4457, true, true);
                if (menuSubOpenYesNo(0, 0x3C, 0xDC, 1) == 0) {
                    memcardTaskCall(7, 2, 0);
                }
                winMsgClose(true);
            }
            running = 0;
            break;
        }
    } while (running != 0);
    fn_800A3A1C();
    _menuTitleOptionClose(0x117);
    fadeCheck(1);
    _menuTitleOptionExit();
}

void menuTitleOptionButton(tagWINDOW_WORK* w) {
    if (w->pos.y == 2) {
        menuButtonNormal(w);
    } else if (windowGetKeyInfo()->trg & 0x20) {
        w->done = 1;
        w->cancel = 1;
    }
}

}

static void _menuTitleOptionClose(long id) {
    menuCloseCustom(id, 0, 1);
}

static void _menuTitleOptionExit() {}

static void _menuTitleOptionInit() {
    menuToolSetSelect(0);
    _menuTitleOptionWork.f0 = 0;
    _menuTitleOptionWork.f14 = 0.0f;
    _menuTitleOptionWork.rot = 0.0f;
    _menuTitleOptionWork.f4 = 0;
    _menuTitleOptionWork.t = 0.0f;
    _menuTitleOptionWork.speed = 3.0f;
    _menuTitleOptionWork.amp = 0.20943952f;
    _menuTitleOptionWork.count = 0;
    _menuTitleOptionWork.flag = 0;
    menuPdaSubInitAlpha(_atable, 3, 0);
}
