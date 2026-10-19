// STATUS (dTop): 27/29 exact with extra_cflags=["-inline noauto"] (LAYOUT/CONST/CALLS/DATA OK). Left: menuTop (saved-register assignment differs: target state=r29 loop=r28 ids ptr=r30 yes=r27; permuter 240->200 only) and menuTopHookMssageWindow (sel lha goes to r0 instead of r3, 2 instrs). Source uses peephole off + pool_strings off + force_active (REL-only entry points).
#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off
#pragma force_active on

struct tagWINDOW_WORK {
    u8 pad0;
    s8 type;
    s8 done;
    u8 pad3;
    s32 menuID;
    u8 pad8[0x14];
    s32 msgWin;
    u8 pad20[0x73];
    u8 colorA;
    u8 pad94[8];
    s32 data;
    u8 padA0[0x68 - 0xA0 + 0xA0];
};

struct tagSPRITE_WORK {
    u8 pad0[6];
    s16 id;
};

struct S16Pair {
    s16 a;
    s16 b;
};

struct SelPair {
    s16 a;
    s16 sel;
};

struct MenuTopWork {
    s32 select;
    s32 stage;
    u8 battleMode;
    s32 battleSelectMode;
};

struct MenuModel {
    MenuModel() {}
    u8 data[0xEC];
};

extern "C" {
void menuOpen(s32, s32);
s32 menuOpenCustom(s32, ...);
void menuCloseCustom(s32, s32, s32);
u8 menuIsCheck();
void winSeqSetMenu(s32, s32);
void winSpriteSetDisp(void*, s32);
void GSmsgPrint2(s32, s32, s32, s32, s32);
u32 GSmsgGetRect(s32);
void* menuItemBiosGetPtr(s32, s16);
s32 pokecoloGetRomVersion();
s16 menuTitleGetSelect();
void menuTitleCursorAnime();
void menuTitleCursorAnimeMain();
u8 menuModelCheck(MenuModel*, s32);
void menuModelSetSize(MenuModel*, s16, s16, s16, s16);
void menuModelAdjustCamera(MenuModel*);
void menuModelRender(MenuModel*);
void menuModelSetAngle(MenuModel*, f32*);
void menuModelSetZoom(MenuModel*, f32);
void menuModelSetMotion(MenuModel*, s32);
void menuItemBiosSetSelectFlag(s32, s16, s32);
u8 menuItemBiosGetSelectFlag(s32, s32);
void menuTitleSetSelect(s16, s16);
s32 windowGetActiveID();
void fadeCheck(s32);
void fadeSet(s32, f32);
void menuTitleSetStartStatus(s32);
void menuTitleCloseSelectAnime();
u32 gamedatasaveGetStatus(s32, s32);
s32 winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
void menuTitleBattlePreReadCheck();
void menuNameEntryOpen(s32, s32);
void menuNameEntryGetLastName(u16*);
void cursorBiosInit();
void heroMoveSyncWithHero();
void soundOpenPlay(s32, s32, s32);
void floorLink(s32, s32);
void menuTitleOpenMenu();
void menuTitleOpenSelectAnime();
void menuTitleOpenSelectAnime2();
void GScharMakeFromSJIS(u16*, const char*);
void menuPokemonInitWork();
void pokecoloStartCountPlayTime(s32);
u8 memcardIsMemCardValid();
void menuTitlePreReadWait();
void menuTitleBattleSelectFree();
void menuTitleOption();
void FlashSystemSetLoopFlag(s32, s32);
void FlashSystemSetPlayFrameLabel(s32, const char*, const char*);
void FlashSystemSetNowFrameLabel(s32, const char*);
u32 FlashSystemGetFrameFromLabel(s32, const char*);
u32 FlashSystemGetNowFrame(s32);
void GSthreadSwitch();
void menuColosseumBattle(s32);
void* windowSearchID(s32);
void FlashSystemPlayAndWait(s32, const char*, const char*);
void fn_800A39E4();
void menuTitlePlayBGM();
u32 soundGetBGMID();
void savedataCreate(s32, u16*);
void pokecoloSetPlayTime(f64);
s32 pokecoloGetPlayTimeValue();
s32 darkPokemonGetReliveNum();
s32 darkPokemonGetSnatchSuccessNum();
void msgctrlSetValue(s32, s32);
void floorSetContinueMode(s32);
void floorClearReturnPoint();
void floorReturnSavePoint();
void fn_800A3A1C();
void menuModelInit(MenuModel*, s32, s32);
void menuModelTerm(MenuModel*);
void menuModelLoad(MenuModel*, s32);
s32 heroGetObjID(s32);
void* peopleInfoBiosGetPtr(s32);
void peopleInfoBiosGetMotion(void*, u8, s32*, u8*);
void scriptModelClose(s32);
}
static s32 _menuTopMsgTable[5] = {0x42E2, 0x42E1, 0x444E, 0x42E3, 0x42E6};
static s32 _menuTopMsgTableBattleSelect[3] = {0x42E4, 0x42E5, 0xAF};
static s32 _menuTopSelectCursor;
s32 _menuTopResID;
static MenuTopWork _menuTopWork;
static MenuModel _menuTopMenuModel;

static void _menuTopClose(s32 id);
static void _menuTopClose2(s32 id, u32 n);
static void _menuTopInitPokemon(s16 w, s16 h);
static void _menuTopLoadPokemon();
static s32 _menuTopLoadCheck();
static void _menuTopNewGame(u16* name);
static s32 _menuTopSelectBattle();
static void _menuTopSetLastCursor();
static void _menuTopExitPokemon();
static void _menuTopExit();
static void _menuTopInit();
extern "C" {
void menuTopExit();
void menuTopInit();
void menuTopPlayToolBGM();
s32 menuTopGetBattleSelectMode();
void menuTopSetBattleSelectMode(s32);
void menuTopOpenFlashBack();
s32 menuTop();
}

extern "C" {
void menuTopOpenFlashBack() {
    menuOpen(0x119, 0);
}

void menuTopSelectCtrl(tagWINDOW_WORK* w) {
    u8* p = *(u8**)((u8*)w + 0x68);
    switch (w->type) {
    case 0:
        if (w->done == 0) {
            if (*p != 0) {
                winSeqSetMenu(w->menuID, 0x24);
            }
            w->done = 1;
        }
        break;
    case 3:
        if (w->done == 0) {
            winSeqSetMenu(w->menuID, 0x17B);
            w->done = 1;
        }
        break;
    }
}

void menuTopLoadHook() {
    S16Pair pos = {0xFA, 0x1E};
    S16Pair size = {0x140, 0x190};
    f32 ang[3];
    ang[0] = 0.0f;
    ang[1] = -0.2f;
    ang[2] = 0.0f;
    if (menuModelCheck(&_menuTopMenuModel, 0) == 0) {
        menuModelSetSize(&_menuTopMenuModel, pos.a, pos.b, size.a, size.b);
        menuModelAdjustCamera(&_menuTopMenuModel);
        menuModelRender(&_menuTopMenuModel);
        menuModelSetAngle(&_menuTopMenuModel, ang);
        menuModelSetZoom(&_menuTopMenuModel, 1.5f);
    }
}

void menuTopHookMssageWindow(tagWINDOW_WORK* w) {
    SelPair p = *(SelPair*)((u8*)w + 0x9C);
    if (pokecoloGetRomVersion() != 1 && p.sel >= 0) {
        s16 idx = menuTitleGetSelect();
        GSmsgPrint2(w->msgWin, 0, -8, w->colorA | ~0xFF, _menuTopMsgTable[idx]);
    }
}

void menuTopHookMssageBattleSelectWindow(tagWINDOW_WORK* w) {
    SelPair p = *(SelPair*)((u8*)w + 0x9C);
    if (p.sel >= 0) {
        GSmsgPrint2(w->msgWin, 0, -8, w->colorA | ~0xFF, _menuTopMsgTableBattleSelect[p.sel]);
    }
}

void fn_8002F668(tagWINDOW_WORK* w, tagSPRITE_WORK* s, s32 msg);

void menuTopHook(tagWINDOW_WORK* w, tagSPRITE_WORK* s) {
    SelPair p = *(SelPair*)((u8*)w + 0x9C);
    switch (s->id) {
    case 0x70:
        if (p.sel == 0) {
            menuTitleCursorAnime();
            winSpriteSetDisp(s, 1);
        } else {
            winSpriteSetDisp(s, 0);
        }
        break;
    case 0x71:
        if (p.sel == 1) {
            menuTitleCursorAnime();
            winSpriteSetDisp(s, 1);
        } else {
            winSpriteSetDisp(s, 0);
        }
        break;
    case 0x72:
        if (p.sel == 2) {
            menuTitleCursorAnime();
            winSpriteSetDisp(s, 1);
        } else {
            winSpriteSetDisp(s, 0);
        }
        break;
    case 0x76:
        fn_8002F668(w, s, 0x445A);
        break;
    case 0x77:
        fn_8002F668(w, s, 0x4459);
        break;
    }
}

struct MenuItemPos {
    u8 pad[0xA];
    s16 x;
    s16 y;
};

void fn_8002F668(tagWINDOW_WORK* w, tagSPRITE_WORK* s, s32 msg) {
    u32 r = GSmsgGetRect(msg);
    s16 rw = r >> 16;
    s16 rh = (u16)r;
    MenuItemPos* it = (MenuItemPos*)menuItemBiosGetPtr(w->menuID, s->id);
    s32 dx = it->x - rw;
    s32 dy = it->y - rh;
    GSmsgPrint2(w->msgWin, dx / 2, dy / 2, w->colorA | ~0xFF, msg);
}

s32 menuTop() {
    s32 loop;
    s32 state;
    s8 firstFlag;
    s32* q;
    state = 0;
    loop = 1;
    firstFlag = 1;
    u16 nameB[20];
    u16 nameA[20];
    menuTopInit();
    _menuTopWork.stage = 1;
    _menuTopWork.battleMode = 0;
    do {
        switch (state) {
        case 0:
            state = 1;
            break;
        case 1: {
            _menuTopWork.stage = 1;
            s32 ids[5] = {0x44, 0x45, 0x46, 0x47, 0x48};
            s32* p;
            s16 i;
            int n;
            s16 j;
            q = ids;
            p = q;
            for (i = 0; i < 5; p++, i++) {
                menuItemBiosSetSelectFlag(0x116, (s16)*p, 1);
            }
            if (pokecoloGetRomVersion() == 1) {
                menuItemBiosSetSelectFlag(0x116, 0x44, 0);
                menuItemBiosSetSelectFlag(0x116, 0x46, 0);
                menuItemBiosSetSelectFlag(0x116, 0x47, 0);
            }
            n = 0;
            for (j = 0; j < 5; q++, j++) {
                if (menuItemBiosGetSelectFlag(0x116, *q) != 0) {
                    menuTitleSetSelect(n++, j);
                }
            }
            int r = menuOpenCustom(0x116, windowGetActiveID(), &_menuTopWork, 0, 1, 1, &firstFlag);
            firstFlag = 0;
            if (r >= 0) {
                u32 r = menuTitleGetSelect();
                _menuTopWork.select = r;
            }
            if (r < 0) {
                _menuTopWork.select = -1;
            }
            if (r == 0) {
                state = 5;
            } else {
                switch (_menuTopWork.select) {
                case 2:
                    if (_menuTopSelectBattle() >= 0) {
                        state = 100;
                        _menuTopWork.battleMode = 1;
                    } else {
                        _menuTopWork.battleMode = 0;
                    }
                    continue;
                case 1:
                    state = 2;
                    break;
                case 0:
                    break;
                case 3:
                    state = 4;
                    _menuTopWork.stage = 4;
                    break;
                default:
                    menuTitleSetStartStatus(1);
                    state = 100;
                    break;
                }
            }
            fadeCheck(1);
            break;
        }
        case 5: {
            s32 yes;
            _menuTopClose(0x116);
            menuTitleCloseSelectAnime();
            if (pokecoloGetRomVersion() == 1) {
                yes = 0;
            } else {
                s32 msg;
                if (gamedatasaveGetStatus(0, 4) != 0) {
                    msg = 0x8B;
                } else {
                    msg = 0x42D9;
                }
                winMsgOpen(2, msg, 1, 1);
                _menuTopWork.stage = 5;
                yes = menuSubOpenYesNo(0, 0x3C, 0xA6, 1);
                winMsgClose(1);
            }
            if (yes == 0) {
                menuTopExit();
                menuTitleBattlePreReadCheck();
                menuNameEntryOpen(0, 0);
                menuNameEntryGetLastName(nameB);
                if (nameB[0] != 0) {
                    cursorBiosInit();
                    _menuTopNewGame(nameB);
                    heroMoveSyncWithHero();
                    soundOpenPlay(8, 0x3E8, 0xFF);
                    floorLink(0xB6, 0);
                    state = 100;
                } else {
                    state = 1;
                    menuTitleOpenMenu();
                    menuTitleOpenSelectAnime2();
                }
            } else {
                state = 1;
                firstFlag = 1;
                menuTitleOpenSelectAnime();
            }
            break;
        }
        case 2:
            if (pokecoloGetRomVersion() == 1) {
                GScharMakeFromSJIS(nameA, "MICHAEL");
                cursorBiosInit();
                menuPokemonInitWork();
                _menuTopNewGame(nameA);
                soundOpenPlay(8, 0x3E8, 0xFF);
                floorLink(0x47, 0);
                state = 100;
            } else {
                pokecoloStartCountPlayTime(0);
                if (gamedatasaveGetStatus(0, 4) != 0) {
                    state = 3;
                } else {
                    _menuTopClose(0x116);
                    menuTitleCloseSelectAnime();
                    if (memcardIsMemCardValid() == 0) {
                        winMsgOpen(2, 0x82, 1, 0);
                    } else {
                        winMsgOpen(2, 0x98, 1, 0);
                    }
                    winMsgClose(1);
                    state = 1;
                    menuTitleOpenMenu();
                    menuTitleOpenSelectAnime();
                }
            }
            break;
        case 3:
            _menuTopClose(0x116);
            menuTitleCloseSelectAnime();
            fadeSet(3, 0.5f);
            fadeCheck(1);
            _menuTopClose(0x11);
            _menuTopInitPokemon(0x280, 0x1E0);
            menuTitlePreReadWait();
            _menuTopLoadPokemon();
            if (_menuTopLoadCheck() == 0) {
                cursorBiosInit();
                menuTitleBattleSelectFree();
            } else {
                state = 1;
                menuTitleOpenMenu();
                menuTitleOpenSelectAnime2();
                fadeSet(2, 0.5f);
            }
            break;
        case 4:
            _menuTopClose(0x116);
            menuTitleCloseSelectAnime();
            fadeSet(3, 0.5f);
            fadeCheck(1);
            _menuTopClose(0x11);
            menuTitleOption();
            fadeCheck(1);
            state = 1;
            _menuTopWork.stage = 1;
            menuTitleOpenMenu();
            menuTitleOpenSelectAnime2();
            fadeSet(2, 0.5f);
            break;
        case 100:
            _menuTopSetLastCursor();
            loop = 0;
            break;
        }
    } while (loop != 0);
    menuTopExit();
    return _menuTopWork.select;
}

u8 menuTopGetBattleMode() {
    return _menuTopWork.battleMode;
}
}

static s32 _menuTopSelectBattle() {
    u8 loop;
    int r;
    u32 end;
    u32 now;
    s32 mode;
    loop = 1;
    menuTopSetBattleSelectMode(0);
    menuTopOpenFlashBack();
    FlashSystemSetLoopFlag(0x200A3000, 0);
    FlashSystemSetPlayFrameLabel(0x200A3000, "top_start", "top_end");
    FlashSystemSetNowFrameLabel(0x200A3000, "top_start");
    end = FlashSystemGetFrameFromLabel(0x200A3000, "top_end");
    do {
        now = FlashSystemGetNowFrame(0x200A3000);
        GSthreadSwitch();
    } while (now < end);
    menuTopPlayToolBGM();
    do {
        mode = menuTopGetBattleSelectMode();
        r = menuOpenCustom(0x118, windowGetActiveID(), &mode, 0, 1, 0);
        switch (r) {
        case 0: {
            _menuTopClose2(0x118, 2);
            _menuTopClose2(0x116, 2);
            _menuTopClose2(0x11, 2);
            menuTitleBattlePreReadCheck();
            menuColosseumBattle(1);
            u8* w = (u8*)windowSearchID(0x119);
            if (w != 0) {
                w[9] = 0;
            }
            FlashSystemPlayAndWait(0x200A3000, "1back_start", "1back_end");
            break;
        }
        case 1: {
            _menuTopClose2(0x118, 2);
            _menuTopClose2(0x116, 2);
            _menuTopClose2(0x11, 2);
            menuTitleBattlePreReadCheck();
            menuColosseumBattle(0);
            u8* w = (u8*)windowSearchID(0x119);
            if (w != 0) {
                w[9] = 0;
            }
            FlashSystemPlayAndWait(0x200A3000, "2back_start", "2back_end");
            break;
        }
        default:
            r = -1;
            fadeSet(3, 0.5f);
            fadeCheck(1);
            _menuTopClose(0x119);
            _menuTopClose(0x118);
            fn_800A39E4();
            menuOpenCustom(0x11, windowGetActiveID(), 0, 0, 0, 0);
            menuTitleOpenSelectAnime();
            menuTitlePlayBGM();
            fadeSet(2, 0.5f);
            loop = 0;
            break;
        }
    } while (loop != 0);
    return r;
}

extern "C" {
void menuTopBattleSelectCtrl(tagWINDOW_WORK* w) {
    menuTitleCursorAnimeMain();
    switch (w->type) {
    case 0:
        if (w->done == 0) {
            winSeqSetMenu(w->menuID, 0x24);
            w->done = 1;
        }
        break;
    case 3:
        if (w->done == 0) {
            winSeqSetMenu(w->menuID, 0x17B);
            w->done = 1;
        }
        break;
    }
}

void menuTopPlayToolBGM() {
    if (soundGetBGMID() != 0x568) {
        soundOpenPlay(0x568, 0, 0xFF);
    }
}
}

static void _menuTopNewGame(u16* name) {
    savedataCreate(0, name);
    pokecoloStartCountPlayTime(1);
    pokecoloSetPlayTime(0.0);
}

extern "C" {
void menuTopExit() {
    _menuTopExit();
}

void menuTopMain() {
    menuTop();
}

void menuTopInit() {
    _menuTopInit();
}
}

static void _menuTopSetLastCursor() {
    s32 v = _menuTopWork.select;
    if (v >= 5 || v < 0) {
        v = 0;
    }
    _menuTopSelectCursor = v;
}

static s32 _menuTopLoadCheck() {
    s32 ret;
    s32 relive;
    s32 t;
    t = pokecoloGetPlayTimeValue();
    relive = darkPokemonGetReliveNum();
    ret = darkPokemonGetSnatchSuccessNum();
    FlashSystemSetPlayFrameLabel(0x22063000, "start", "end");
    FlashSystemSetLoopFlag(0x22063000, 0);
    FlashSystemSetNowFrameLabel(0x22063000, "start");
    msgctrlSetValue(0x4C, t);
    msgctrlSetValue(0x2F, ret);
    msgctrlSetValue(0x30, relive);
    menuOpen(0xDB, 0);
    winMsgOpen(1, 0x42EE, 0, 1);
    if (menuSubOpenYesNo(0, 0x1C2, 0xC0, 1) == 0) {
        heroMoveSyncWithHero();
        floorSetContinueMode(1);
        floorClearReturnPoint();
        floorReturnSavePoint();
        ret = 100;
        pokecoloStartCountPlayTime(1);
    } else {
        ret = 1;
        pokecoloStartCountPlayTime(1);
    }
    fn_800A3A1C();
    _menuTopExitPokemon();
    _menuTopClose(0xDB);
    winMsgClose(1);
    fadeCheck(1);
    return ret;
}

static void _menuTopClose(s32 id) {
    menuCloseCustom(id, 0, 1);
}

static void _menuTopClose2(s32 id, u32 n) {
    if (menuIsCheck() == 1) {
        menuCloseCustom(id, n, 1);
    }
}

static void _menuTopInitPokemon(s16 w, s16 h) {
    menuModelInit(&_menuTopMenuModel, w, h);
}

static void _menuTopExitPokemon() {
    menuModelTerm(&_menuTopMenuModel);
}

static void _menuTopLoadPokemon() {
    u8 loop;
    s32 motion;
    menuModelLoad(&_menuTopMenuModel, heroGetObjID(1));
    menuModelCheck(&_menuTopMenuModel, 1);
    peopleInfoBiosGetMotion(peopleInfoBiosGetPtr(0x16C90400), 1, &motion, &loop);
    menuModelSetMotion(&_menuTopMenuModel, motion);
}

static void _menuTopExit() {
    _menuTopClose2(0x116, 2);
    scriptModelClose(_menuTopResID);
}

extern "C" {
s32 menuTopGetBattleSelectMode() {
    return _menuTopWork.battleSelectMode;
}

void menuTopSetBattleSelectMode(s32 m) {
    _menuTopWork.battleSelectMode = m;
}
}

static void _menuTopInit() {
    _menuTopWork.select = _menuTopSelectCursor;
    _menuTopWork.stage = 0;
    _menuTopWork.battleSelectMode = 0;
}

extern "C" void menuTopSetInitCursor(s32 c) {
    _menuTopSelectCursor = c;
}
