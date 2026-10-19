// STATUS (dPcBox): 36/36 exact (fcheck LAYOUT/CONST/CALLS/DATA OK). Flags needed: -inline noauto (peephole off in source).
#include <dolphin/types.h>

#pragma peephole off
// Some entry points are only called from REL code: keep them in the DOL.
#pragma force_active on

extern "C" {
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
}

struct Pokemon {
    u8 data[0xC4];
};

struct tagSPRITE_WORK {
    u8 pad0[0x4C];
    s32 value;
};

struct tagWINDOW_WORK {
    s8 pad0;
    s8 type;
    s8 done;
    u8 pad3;
    s32 id;
};

struct MenuPtWorkSound {
    u32 bgm;
    u32 env;
    u8 bgmVol;
    u8 envVol;
};

struct CMenuGlobalState {
    enum enumCallFrom { PcBox, ReliveHall, Hologram, ReliveHallTutorial };
    s32 from;
    s32 mode;
    s32 next;
    u8 pad0C[0x150];
    u8 tutorial;
    u8 cancel;
    u8 cancelExit;
    u8 pad15F[0x208 - 0x15F];
    void init();
};

class CReliveHall {
public:
    static void* getPointer();
    static bool isOpen();
    void init();
    void allocMakeBackup();
    void checkWithBackupSet();
};

class PCBOX {
public:
    static PCBOX* getPointer();
    void init();
    void setPokemon(Pokemon*, s8, s8);
};

class CAnt {
public:
    static void systemInit();
    static void systemFree();
};

struct VP {
    u32 id;
    u32 value;
};

class CMetaMenu;

struct CInfoWindow {
    s32 windowId;
    s32 itemId;
    u8 opened;
    bool isMsg;
    s32 msgId;
    VP values[4];
    u16 buttons;
};

struct CState {
    s32 current, next, prev;
    u32 count;
    f32 time;
    f32 dt;
    u32 work[0x10];
    u32 work2[0x10];
    s32 w98, w9c, wa0;
    u8 padA4[4];
    void update();
    void init();
    inline void change(s32 n)
    {
        next = n;
        memset(work, 0, 0x40);
    }
};

struct CKeyInfo {
    u8 pad0[4];
    u16 trg;
    u16 rep;
    u8 pad8[0x12];
};

class CMetaMenu {
public:
    s32 fadeTime;
    s32 fadeState;
    s32 pad8;
    u32 seId;
    u8 pad10[0xC];
    s32 windowIds[64];
    void (*windowFuncs[64])(CMetaMenu*, long);
    long* windowTable;
    CKeyInfo keyInfo;
    s32 repeat;
    u16 lastOn;
    u8 tutorialMode;
    CInfoWindow info;
    CState state;
    u64 time;
    CMenuGlobalState* gstate;
    u8 updated;
    u8 pad32D;
    u16 cachedInput;

    CMetaMenu() {}
    virtual void drawAll() = 0;
    virtual bool isAnimationStateNone() { return true; }
    virtual void updateAll();
    virtual void tutorialExitKick() {}

    void localWindowCreateAll();
    void localWindowDeleteAll();
    void localWindowSetTable(long*);
    static void systemFadeInKick();
    void systemFadeOutSetAndWait(f32);
    void systemFadeWaitToEnd();
    static long defautlLocalWindowOpenTable[];
};

extern "C" {
void* savedataGetStatus(long, long);
void* gamedataGetStatus(long, long);
void* memcardMemAllocForSavedata();
void* memcardMemFreeForSavedata(void*);
void pokemonCreate(Pokemon*, u16, u8, void*);
void winSeqSetMenu(s32, u32);
void winSpriteSetDisp(void*, bool);
s32 windowGetValue(s32);
s32 windowGetActiveID();
void* windowSearchID(long);
s32 menuOpen(s32, s32);
void menuOpenCustom(s32, ...);
void menuClose(s32);
void menuCloseSync(s32, s32);
s32 menuPocket2Call(s32, s32, s32);
void GSfsysReadWait(u32);
void GSfsysFree(u32);
void GSresFreeGroup(u32);
u8 GSfloorPop();
}

void menuPocketSetDarkPokemon(Pokemon&, f32, u16);
void menuPtPlaySe(u32);
void menuPtPlayBgm(u32);
void menuPtSaveSound(MenuPtWorkSound*);
void menuPtRestoreSound(MenuPtWorkSound*);
void menuPtSpriteWorkSetMenuItem(tagWINDOW_WORK*, tagSPRITE_WORK*, u32);
void menuPcBoxPokemon(CMenuGlobalState&);
void menuReliveHallExecFromPcBox(CMenuGlobalState&);
void menuHologramExecFromPcBox(CMenuGlobalState&);
enum MENU_PCBOX_DOUGU_HIKIDASHI_MODE { HIKIDASHI_0, HIKIDASHI_1 };
void menuPcBoxDouguHikidashi(MENU_PCBOX_DOUGU_HIKIDASHI_MODE);
long relivehallGetLastViewStage();
void relivehallSetLastViewStage(long);
long menuPcBoxGetLastViewBox();
void menuPcBoxSetLastViewBox(long);

extern u32 pcBoxSoundTbl[5];

namespace {

struct SelectMenu {
    s32 window;
    s32 title;
    s32 info;
    s32 items[6];
};

SelectMenu _selectMenuTbl[3] = {
    { 0x7A, 0x353, 0x3BB0, { 0x3BB1, 0x3BB2, 0x3BB4, 0, 0, 0 } },
    { 0x7B, 0x353, 0x3BB0, { 0x3BB1, 0x3BB2, 0x3B70, 0x3BB4, 0, 0 } },
    { 0x7B, 0x37E, 0x3BB6, { 0x3BB7, 0x3BB8, 0x3BB9, 0x3BBA, 0, 0 } },
};

class CmenuPcBox : public CMetaMenu {
public:
    SelectMenu* menu;
    u8 loadedA;
    u8 loadedB;
    u8 pad33E[2];
    void* backup;
    s32 resultA;
    s32 resultB;
    MenuPtWorkSound sound;

    virtual void drawAll() {}

    void tutorialPokemonRecover();
    void tutorialPokemonSetup();
    void ctrl(tagWINDOW_WORK*);
    void drawItemText(tagWINDOW_WORK*, tagSPRITE_WORK*, long);
    void drawInfo(tagWINDOW_WORK*, tagSPRITE_WORK*);
    void drawTitle(tagWINDOW_WORK*, tagSPRITE_WORK*);
    void drawRedBar(tagWINDOW_WORK*, tagSPRITE_WORK*, long);
    void loop();
    void main(CMenuGlobalState::enumCallFrom);
};

CMenuGlobalState _menuGlobalState;
CmenuPcBox _menuPcBox;
long localWindowTable[1] = { 0 };

}

u8 menuReliveHallTutorialGetIsCancelExit()
{
    return _menuGlobalState.cancelExit;
}

extern "C" {

void menuReliveHallTutorialExit() {}
void menuReliveHallTutorialMain() { _menuPcBox.main(CMenuGlobalState::ReliveHallTutorial); }
void menuReliveHallTutorialInit() {}
void menuHologramExit() {}
void menuHologramMain() { _menuPcBox.main(CMenuGlobalState::Hologram); }
void menuHologramInit() {}
void menuReliveHallExit() {}
void menuReliveHallMain() { _menuPcBox.main(CMenuGlobalState::ReliveHall); }
void menuReliveHallInit() {}
void menuPcBoxExit() {}
void menuPcBoxMain() { _menuPcBox.main(CMenuGlobalState::PcBox); }
void menuPcBoxInit() {}
s32 menuPcBoxSelectMenuItem() { return 0; }

s32 menuPcBoxCtrl(tagWINDOW_WORK* w)
{
    _menuPcBox.ctrl(w);
    return 0;
}

s32 menuPcBoxItem3(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawItemText(w, s, 3);
    return 0;
}

s32 menuPcBoxItem2(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawItemText(w, s, 2);
    return 0;
}

s32 menuPcBoxItem1(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawItemText(w, s, 1);
    return 0;
}

s32 menuPcBoxItem0(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawItemText(w, s, 0);
    return 0;
}

s32 menuPcBoxInfo(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawInfo(w, s);
    return 0;
}

s32 menuPcBoxTitle(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawTitle(w, s);
    return 0;
}

s32 menuPcBoxBarRed3(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawRedBar(w, s, 3);
    return 0;
}

s32 menuPcBoxBarRed2(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawRedBar(w, s, 2);
    return 0;
}

s32 menuPcBoxBarRed1(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawRedBar(w, s, 1);
    return 0;
}

s32 menuPcBoxBarRed0(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    _menuPcBox.drawRedBar(w, s, 0);
    return 0;
}

}

namespace {

void CmenuPcBox::tutorialPokemonRecover()
{
    memcpy(savedataGetStatus(0, 0), backup, 0x27FD0);
    backup = memcardMemFreeForSavedata(backup);
}

void CmenuPcBox::tutorialPokemonSetup()
{
    static u16 pokemonTbl[18] = { 0x14A, 0x173, 0x141, 0x148, 0x132, 0x151, 0x15A, 0x14F, 0x16F,
                                  0x14C, 0x130, 0x15F, 0x122, 0x140, 0x169, 0x18B, 0x178, 0x163 };
    static u16 darkPokemonTbl[2] = { 0xA, 1 };
    Pokemon pokemon;
    u32 i;
    backup = memcardMemAllocForSavedata();
    memcpy(backup, savedataGetStatus(0, 0), 0x27FD0);
    PCBOX::getPointer()->init();
    ((CReliveHall*)CReliveHall::getPointer())->init();
    for (i = 0; i < 18; i++) {
        pokemonCreate(&pokemon, pokemonTbl[i], 25, gamedataGetStatus(0, 1));
        if (i < 2) {
            menuPocketSetDarkPokemon(pokemon, 0.5f, darkPokemonTbl[i]);
        }
        PCBOX::getPointer()->setPokemon(&pokemon, 0, i);
    }
}

void CmenuPcBox::ctrl(tagWINDOW_WORK* w)
{
    switch (w->type) {
    case 0:
        if (w->done == 0) {
            winSeqSetMenu(w->id, 0x1C4);
            w->done = 1;
        }
        break;
    case 3:
        if (w->done == 0) {
            winSeqSetMenu(w->id, 0x1C8);
            w->done = 1;
        }
        break;
    }
}

void CmenuPcBox::drawItemText(tagWINDOW_WORK* w, tagSPRITE_WORK* s, long idx)
{
    s->value = menu->items[idx];
}

void CmenuPcBox::drawInfo(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    s->value = menu->info;
}

void CmenuPcBox::drawTitle(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    menuPtSpriteWorkSetMenuItem(w, s, menu->title);
}

void CmenuPcBox::drawRedBar(tagWINDOW_WORK* w, tagSPRITE_WORK* s, long idx)
{
    long v = windowGetValue(w->id);
    winSpriteSetDisp(s, idx == v);
}

void CmenuPcBox::loop()
{
    s32* sel;
    while (true) {
        state.update();
        switch (state.current) {
        case 0:
            state.change(1);
            menuOpen(0x79, 0);
            break;
        case 1:
            if (CReliveHall::isOpen()) {
                menu = &_selectMenuTbl[1];
            } else {
                menu = &_selectMenuTbl[0];
            }
            state.change(4);
            break;
        case 2:
            resultB = 0;
            menu = &_selectMenuTbl[2];
            state.change(4);
            break;
        case 3:
            menu = &_selectMenuTbl[2];
            state.change(4);
            break;
        case 4:
            if (state.prev == 1) {
                sel = &resultA;
            } else {
                sel = &resultB;
            }
            menuOpenCustom(menu->window, windowGetActiveID(), sel, 0, 1, 0);
            *sel = windowGetValue(menu->window);
            menuClose(menu->window);
            menuCloseSync(menu->window, 1);
            if (state.prev == 1) {
                if (*sel != -1) {
                    switch (menu->items[*sel]) {
                    case 0x3BB1:
                        systemFadeOutSetAndWait(-1.0f);
                        state.change(5);
                        break;
                    case 0x3BB2:
                        state.change(2);
                        break;
                    case 0x3B70:
                        systemFadeOutSetAndWait(-1.0f);
                        state.change(6);
                        break;
                    case 0x3BB4:
                        state.change(11);
                        break;
                    }
                } else {
                    state.change(11);
                }
            } else {
                if (*sel != -1) {
                    switch (menu->items[*sel]) {
                    case 0x3BB7:
                        state.change(8);
                        break;
                    case 0x3BB8:
                        state.change(9);
                        break;
                    case 0x3BB9:
                        state.change(10);
                        break;
                    case 0x3BBA:
                        state.change(1);
                        break;
                    }
                } else {
                    state.change(1);
                }
            }
            break;
        case 5:
            if (state.prev == 6) {
                _menuGlobalState.mode = 2;
            } else {
                _menuGlobalState.mode = 0;
            }
            if (!loadedB) {
                GSfsysReadWait(0x16);
                loadedB = 1;
            }
            localWindowDeleteAll();
            if (windowSearchID(0x79)) {
                menuClose(0x79);
            }
            menuPcBoxPokemon(_menuGlobalState);
            localWindowCreateAll();
            if (_menuGlobalState.cancel) {
                state.change(11);
            } else if (_menuGlobalState.next == 2) {
                state.change(6);
            } else {
                systemFadeInKick();
                state.change(0);
            }
            break;
        case 6:
            if (state.prev == 5) {
                _menuGlobalState.mode = 1;
            } else if (state.prev == 7) {
                _menuGlobalState.mode = 3;
            } else {
                _menuGlobalState.mode = 0;
            }
            if (!loadedA) {
                GSfsysReadWait(0x824);
                loadedA = 1;
            }
            localWindowDeleteAll();
            if (windowSearchID(0x79)) {
                menuClose(0x79);
            }
            menuPtPlayBgm(0x469);
            menuReliveHallExecFromPcBox(_menuGlobalState);
            localWindowCreateAll();
            if (_menuGlobalState.cancel) {
                state.change(11);
            } else if (_menuGlobalState.next == 1) {
                state.change(5);
            } else if (_menuGlobalState.next == 4) {
                state.change(11);
            } else if (_menuGlobalState.from == 1) {
                state.change(11);
            } else if (_menuGlobalState.from == 2) {
                state.change(7);
            } else {
                menuPtRestoreSound(&sound);
                systemFadeInKick();
                state.change(0);
            }
            break;
        case 7:
            _menuGlobalState.mode = 0;
            localWindowDeleteAll();
            menuHologramExecFromPcBox(_menuGlobalState);
            localWindowCreateAll();
            if (_menuGlobalState.next == 2) {
                state.change(6);
            } else {
                state.change(11);
            }
            break;
        case 8:
            systemFadeOutSetAndWait(-1.0f);
            localWindowDeleteAll();
            menuClose(0x79);
            menuPcBoxDouguHikidashi(HIKIDASHI_0);
            menuOpen(0x79, 0);
            localWindowCreateAll();
            systemFadeInKick();
            state.change(3);
            break;
        case 10:
            systemFadeOutSetAndWait(-1.0f);
            localWindowDeleteAll();
            menuClose(0x79);
            menuPcBoxDouguHikidashi(HIKIDASHI_1);
            menuOpen(0x79, 0);
            localWindowCreateAll();
            systemFadeInKick();
            state.change(3);
            break;
        case 9:
            systemFadeOutSetAndWait(-1.0f);
            GSfsysReadWait(0x66F);
            localWindowDeleteAll();
            menuClose(0x79);
            menuOpen(0x8A, 0);
            systemFadeInKick();
            systemFadeWaitToEnd();
            menuPocket2Call(4, 0, 0);
            menuClose(0x8A);
            menuOpen(0x79, 0);
            localWindowCreateAll();
            GSfsysFree(0x66F);
            GSresFreeGroup(0x66F);
            systemFadeInKick();
            state.change(3);
            break;
        case 11:
            systemFadeOutSetAndWait(-1.0f);
            if (windowSearchID(0x79)) {
                menuClose(0x79);
            }
            return;
        }
    }
}

void CmenuPcBox::main(CMenuGlobalState::enumCallFrom from)
{
    void* hall;
    CAnt::systemInit();
    time = 0;
    state.init();
    fadeTime = 0;
    fadeState = 0;
    memset(windowIds, 0, 0x100);
    memset(windowFuncs, 0, 0x100);
    windowTable = CMetaMenu::defautlLocalWindowOpenTable;
    if (pcBoxSoundTbl != 0) {
        memcpy(&pad8, pcBoxSoundTbl, 0x14);
    }
    tutorialMode = 0;
    updated = 0;
    cachedInput = 0;
    memset(&keyInfo, 0, 0x1A);
    repeat = 0;
    lastOn = 0;
    menu = 0;
    loadedA = 0;
    loadedB = 0;
    resultA = 0;
    resultB = 0;
    memset(&sound, 0, 0xC);
    menuPtSaveSound(&sound);
    localWindowSetTable(localWindowTable);
    localWindowCreateAll();
    _menuGlobalState.init();
    _menuGlobalState.from = from;
    hall = CReliveHall::getPointer();
    ((CReliveHall*)hall)->allocMakeBackup();
    switch (_menuGlobalState.from) {
    case 0:
        menuPtPlaySe(0x447);
        loadedB = 1;
        state.change(0);
        loop();
        localWindowDeleteAll();
        if (loadedA) {
            GSfsysFree(0x824);
            GSresFreeGroup(0x824);
        }
        break;
    case 1:
        loadedA = 1;
        state.change(6);
        loop();
        localWindowDeleteAll();
        if (loadedB) {
            GSfsysFree(0x16);
            GSresFreeGroup(0x16);
        }
        menuPtRestoreSound(&sound);
        break;
    case 3: {
        long stage = relivehallGetLastViewStage();
        long box = menuPcBoxGetLastViewBox();
        menuPcBoxSetLastViewBox(0);
        relivehallSetLastViewStage(0);
        tutorialPokemonSetup();
        _menuGlobalState.tutorial = 1;
        loadedA = 1;
        state.change(6);
        loop();
        localWindowDeleteAll();
        if (loadedB) {
            GSfsysFree(0x16);
            GSresFreeGroup(0x16);
        }
        tutorialPokemonRecover();
        menuPcBoxSetLastViewBox(box);
        relivehallSetLastViewStage(stage);
        menuPtRestoreSound(&sound);
        break;
    }
    case 2:
        state.change(7);
        loop();
        localWindowDeleteAll();
        if (loadedA) {
            GSfsysFree(0x824);
            GSresFreeGroup(0x824);
        }
        if (loadedB) {
            GSfsysFree(0x16);
            GSresFreeGroup(0x16);
        }
        break;
    }
    ((CReliveHall*)hall)->checkWithBackupSet();
    CAnt::systemFree();
    GSfloorPop();
}

}
