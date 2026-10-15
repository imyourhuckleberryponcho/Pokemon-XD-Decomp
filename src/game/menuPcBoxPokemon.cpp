#include <dolphin/types.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

// Pokemon PC box menu. Menu files were built without the peephole optimizer.
#pragma peephole off

class Hero {
public:
    static Hero* getHeroPtr();
    bool setPokemon(const Pokemon*, long);
    u32 addPokemon(const Pokemon*);
    Pokemon* getPokemon(long);
};

struct PCBOX {
    static s8 lastWatchBoxID;
    static PCBOX* getPointer();
    s8 getPokemonBoxNbUsedSlot(s8);
    s8 getPokemonBoxNbEmptySlot(s8);
    void setPokemon(Pokemon*, s8, s8);
    void addPokemon(Pokemon*, s8);
    void delPokemon(s8, s8);
    Pokemon* getPokemon(s8, s8);
    void* getPokemonBoxName(s8);
};

template <typename T>
struct PocketVec {
    T x, y;
};

struct CAnt {
    u32 a0;
    s32 a4;
    PocketVec<short> pos;
    f32 aC;
    u8 a10;
    s32 a14;
    s16 a18, a1A;
    f32 a1C;
    s32 a20, a24, a28;
    f32 a2C;
    s32 a30;
    static void systemUsecountReset();
    static void systemUnUseResourceRelease();
    static void systemUpdate(bool);
    static void waitEndOfReading();
    static void allRequestCancel();
    void init();
    void use();
    inline void setA14(s32 v) { a14 = v; }
    void initByPokemonAndSetColorAnimationInAny(Pokemon*);
    void setAnimation(long);
    void drawAndUpdateWithOffset(PocketVec<short>);
};

struct GSgfxLayer;
void GSprimSetup2DRender(GSgfxLayer*);

class CMenuPokemonCursor {
public:
    u8 active;
    s32 mode;
    f32 t;
    s32 index;
    u8 pad10[0x10];
    Pokemon pokemon;
    CAnt ant;
    CAnt before;
    bool flag;
    bool isCatchPokemon();
    void deletePokemon();
    void draw();
    void setAnimationOff();
    void setBeforAnt(CAnt&);
    void setPokemon(Pokemon*);
    void setPositionIndex(long);
    void setPositionTable(PocketVec<short>*, long);
    void setPositionTableDummy();
    inline void setT(f32 a)
    {
        t = a < 1.0f ? a : 1.0f;
    }
    inline Pokemon* getPokemonPtr()
    {
        return pokemon.checkValid() ? &pokemon : 0;
    }
};

extern "C" void* memset(void*, int, u32);

struct tagSPRITE_WORK {
    tagSPRITE_WORK* next;
    u8 unk4;
    u8 unk5;
    s16 itemId;
    u8 pad8[0x40];
    u32 hook;
    s32 msgId;
    s16 x, y, w, h;
    s32 unk58;
    s16 sx, sy, sw, sh;
    u32 color;
};

struct tagWINDOW_WORK {
    s8 flags;
    u8 pad1[3];
    s32 menuId;
    u8 pad8[0x14];
    s32 layer;
    u8 pad20[4];
    tagSPRITE_WORK* sprites;
    u8 pad28[0x60];
    s32 cursor;
    s16 x, y;
    u8 pad90[0xE];
    s16 cursorShadow;
    u8 padA0[4];
    u8 buttonDone;
    u8 buttonCancel;
};

struct MENU_ITEM_dd_ {
    u8 pad0[4];
    s16 spriteId;
    s16 x, y, w, h;
    u8 padE[10];
    s16 next;
};

struct MENU_SPRITE_dd_ {
    s16 x, y, w, h;
    s32 group;
};

struct SaveStatus {
    u8 pad[0xBC0C];
    long lastViewBox;
};

struct tagWINDOW_KEY {
    u8 pad0[6];
    u16 buttons;
};
struct CMenuGlobalState {
    s32 f0;
    s32 mode;
    s32 next;
    CMenuPokemonCursor cursor;
    u8 tutorial;
};
enum MENU_POKEMON_CB_TYPE { MENU_POKEMON_CB_TYPE_0 };

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

    void close();
    void draw();
    void exec(CMetaMenu&, u32, bool);
    void init(long, u32);
    void initTutorialTalk();
    void open(u32, bool);
    void setMsgCtrlValue(u32, u32);
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

    long actionMenu(u32*, int, long, long, long);
    void alphaFadeDraw();
    void alphaFadeInKick();
    void alphaFadeOutAndWait();
    CKeyInfo* getKeyInfo();
    void localWindowCreateAll();
    void localWindowDeleteAll();
    void localWindowDrawAll();
    void localWindowEntry(long, long, void (*)(CMetaMenu*, long));
    void localWindowRemove(long);
    void localWindowSetTable(long*);
    static void systemFadeInKick();
    void systemFadeOutSetAndWait(f32);
    void waitAtTime(f32);
    static long defautlLocalWindowOpenTable[];
};

extern "C" {
void* GSmemAllocClr(u32);
void GSmemFree(void*);
void* memcpy(void*, const void*, u32);
u8 pokemonCheckValid(Pokemon*);
void* windowSearchID(long);
MENU_SPRITE_dd_* menuSpriteBiosGetPtr(u32);
u8 menuModelCheck(void*, long);
u8 menuModelComparePokemon(void*, Pokemon*);
void menuModelLoadPokemon(void*, Pokemon*);
void menuModelAdjustCamera(void*);
void menuModelSetAngle(void*, f32*);
void menuModelRender(void*);
void menuModelRenderOffAll(void*);
u8 menuSubGetPokemonSexForDisp(Pokemon*);
void msgctrlSetValue(u32, u32);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s32, s32, s32, u32);
void* GSmsgGetGSchar(void*);
s32 pokecoloGetCountryCode();
void* itemDataBiosGetPtr(u16);
void* itemDataBiosGetName(void*);
void* pokemonDataBiosGetName(void*);
void menuDrawReliveMeter3(Pokemon*, s32, s32, s32, s32, s32, s32);
u16 zokuseiGetPokemonSpriteID(void*, u16);
void menuDrawReliveUpdate();
u8 GSgfxVideoGetVsyncRate();
void spriteSetScissor(s32, s32, s32, s32, s32);
void spriteSetOffset(s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void GSfsysRead(u32);
s32 GSfsysGetStatus(u32);
void GSfsysFree(u32);
void GSfsysReadWait(u32);
void GSresFreeGroup(u32);
void GSthreadSwitch();
void menuNameEntryCall(s32, s32);
void menuPokemonStatusOpenFromPcBox(Pokemon*, Pokemon* (*)(Pokemon*, MENU_POKEMON_CB_TYPE, long), long);
void menuOpenCustom(s32, ...);
void menuClose(s32);
void menuCloseSync(s32, s32);
s32 windowGetActiveID();
s32 windowGetValue(s32);
void winSpriteSetDisp(void*, bool);
void menuModelInit(void*, s32, s32);
void menuModelTerm(void*);
void menuModelSetSize(void*, s32, s32, s32, s32);
void GScharCpy(char*, char*);
MENU_ITEM_dd_* menuItemBiosGetPtr(s32, s32);
SaveStatus* savedataGetStatus(long, long);
}

inline void* operator new(unsigned long, void* p) { return p; }

u32 pcBoxSoundTbl[5] = { 0x441, 0x442, 0x443, 0x14, 0x15 };

namespace {

PocketVec<short> _cursorPositionTblDefault[4] = { { 0x164, 0x3A }, { 0x10F, 0x1AC }, { 0x1FE, 0x1AC }, { 0x162, 0x1AD } };
s32 _cursorPositionToStateTbl[4] = { 5, 3, 0x10, 4 };
long localWindowTable[10] = { 0x8A, 0x82, 0x80, 0x84, 0x85, 0x87, 0x88, 0x89, 0xE3, 0 };

class CMenuPokemonLeave;
CMenuPokemonLeave* pMenuPokemonLeave;

class CMenuPokemonLeave : public CMetaMenu {
public:
    CState animState;
    s32 boxIndex;
    s32 boxTarget;
    s32 depositBox;
    CAnt boxAnt[8][30];
    s32 temochiOffset;
    u8 temochiFlag;
    u8 pad34B1[3];
    CAnt temochiAnt[6];
    u8 markMask;
    u8 pad35ED[3];
    f32 scroll;
    CInfoWindow info2;
    u8 model[0xEC];
    u8 modelFlag;
    u8 pad3715[3];
    Pokemon displayPokemon;
    u8 displayFlag;
    u8 displayHide;
    u8 pad37DE[2];
    s32 f37E0, f37E4, f37E8, f37EC;
    CMenuPokemonCursor* cursor;
    s32 slotBaseX, slotBaseY;
    PocketVec<short> cursorPos[40];
    u8 pad389C[4];

    virtual void drawAll();
    virtual bool isAnimationStateNone() { return animState.current == 0; }

    bool pokemonPcBoxMarkGetIndex(Pokemon*, int);
    u8 currentPokemonPcBoxMarkGet();
    void currentPokemonPcBoxMarkSet(u8);
    CAnt* currentAntGetPointer();
    void currentPokemonDel(bool);
    Pokemon* getStatusAndModelDisplayPokemonGetPointer();
    void resetStatusAndModelDisplayPokemon();
    void setStatusAndModelDisplayPokemon(Pokemon*);
    Pokemon* currentPokemonGetPointer();
    int currentPokemonGetArea();
    void cursorUnderPokemonSet(Pokemon*, bool);
    void cursorUnderPokemonDel();
    Pokemon* cursorUnderPokemonGetPointer();
    CAnt* cursorUnderPokemonGetAntPointer();
    int pcBoxUsedQuantity(int);
    int pcBoxEmptyQuantity(int);
    void pcBoxPokemonSet(Pokemon*, int);
    void pcBoxPokemonAdd(Pokemon*, int);
    void pcBoxPokemonDel(int);
    Pokemon* pcBoxPokemonGetPointer(int, int);
    Pokemon* pcBoxPokemonGetPointer(int);
    int searchTemochiPokemonBlankSlot();
    bool temochiPokemonIsFull();
    bool temochiPokemonAddAble();
    int temochiPokemonQuantity();
    int temochiPokemonLiveQuantity(bool);
    void temochiPokemonDelShift(int);
    void temochiPokemonDel(int);
    void temochiPokemonSet(Pokemon*, int);
    bool temochiPokemonAdd(Pokemon*);
    int temochiPokemonGetFreePosition();
    Pokemon* temochiPokemonGetPointer(int);
    void resetViewAntAll();
    PocketVec<short> getPcBoxSlotPosition(int);
    PocketVec<short> getTemochiSlotPosition(int);
    void drawTemochiArea();
    void drawBoxArea(int, float);
    void drawStatusArea();
    void boxNameDraw(int, long, unsigned long);
    void stateMainProc();
    void stateBoxNameChangeExecProc();
    void stateStatusProc();
    Pokemon* pokemonStatusMenuCallback(Pokemon*, MENU_POKEMON_CB_TYPE);
    void stateMarkingProc();
    void depositMenuDraw(long);
    void stateDepositToPcBoxProc();
    void infoMessageDisplay(unsigned long);
    void actionExecByMsgID(unsigned long);
    bool confirmWindow(unsigned long, long);
    void stateActionMenuMainProc();
    void directActionExec();
    void loop();
    void menuModelTerm();
    void menuModelInit();
    void init(CMenuGlobalState&);
    void animationStateUpdate();
    bool animationProcessButtonInterrupt(const tagWINDOW_KEY*);
    void waitAnimationStateEnd();
    void boxScroll(bool);
    bool cursorMoveWhenInPcBoxR(long&);
    bool cursorMoveWhenInPcBoxL(long&);
    void cursorMoveLeft(long&);
    void cursorMoveRight(long&);
    bool cursorMoveDown(long&);
    bool cursorMoveUp(long&);
    void markingMenuItemCallBack(tagWINDOW_WORK*, tagSPRITE_WORK*);
    void main(CMenuGlobalState&);
};

}

void menuPcBoxSetLastViewBox(long);
long menuPcBoxGetLastViewBox();

namespace {
Pokemon* _cbMenuPokemonStatus(Pokemon*, MENU_POKEMON_CB_TYPE, long);
void _depositMenuDrawHook(CMetaMenu*, long);
void thisExec(CMenuGlobalState&);
void thisFree();
void thisNew();
}

void menuPtWindowWorkDraw(long);
void menuPtWindowWorkDraw(tagWINDOW_WORK*);
tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(tagWINDOW_WORK*, u32, long);
tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(long, u32, long);
MENU_ITEM_dd_* menuPtItemGetBySpriteWork(tagWINDOW_WORK*, tagSPRITE_WORK*);
void menuPtSpriteWorkSetMenuSprite(tagSPRITE_WORK*, MENU_SPRITE_dd_*);
MENU_ITEM_dd_* menuPtItemGetByMenuIdAndItemId(long, u32, long);
void menuPtSpriteWorkSetMsgId(long, u32, long, u32);
void menuPtSpriteWorkSetSw(tagWINDOW_WORK*, u32, long, bool);
long relivehallGetLastViewStage();
void menuPtSpriteDraw(u16, long, long);
void menuPtPlaySe(u32);

static inline PocketVec<short> lerpPos(PocketVec<short>& from, PocketVec<short>& to, f32 t)
{
    PocketVec<short> r;
    r.x = (short)(t * (f32)(to.x - from.x) + (f32)from.x);
    r.y = (short)(t * (f32)(to.y - from.y) + (f32)from.y);
    return r;
}

static inline f32 clamp1(f32 x)
{
    return x < 1.0f ? x : 1.0f;
}

static inline void copyTable(void* dst, const void* src, u32 n)
{
    if (src != 0) {
        memcpy(dst, src, n);
    }
}

long menuPcBoxGetLastViewBox()
{
    return savedataGetStatus(0, 3)->lastViewBox;
}

void menuPcBoxSetLastViewBox(long box)
{
    savedataGetStatus(0, 3)->lastViewBox = box;
}

namespace {

PocketVec<short> CMenuPokemonLeave::getTemochiSlotPosition(int i)
{
    MENU_ITEM_dd_* item = menuPtItemGetByMenuIdAndItemId(0x84, 0x417, i * 4);
    PocketVec<short> v;
    v.x = item->x + item->w;
    v.y = item->y + item->h;
    return v;
}

PocketVec<short> CMenuPokemonLeave::getPcBoxSlotPosition(int i)
{
    PocketVec<short> v;
    int row = i / 6;
    int col = i % 6;
    v.x = slotBaseX + col * 64 + 32;
    v.y = slotBaseY + row * 64 + 32;
    return v;
}

void CMenuPokemonLeave::init(CMenuGlobalState& st)
{
    time = 0;
    state.init();
    fadeTime = 0;
    fadeState = 0;
    memset(windowIds, 0, 0x100);
    memset(windowFuncs, 0, 0x100);
    windowTable = CMetaMenu::defautlLocalWindowOpenTable;
    copyTable(&pad8, pcBoxSoundTbl, 0x14);
    tutorialMode = 0;
    updated = 0;
    cachedInput = 0;
    memset(&keyInfo, 0, 0x1A);
    repeat = 0;
    lastOn = 0;
    animState.init();
    boxIndex = menuPcBoxGetLastViewBox();
    boxTarget = 0;
    depositBox = 0;
    memset(boxAnt, 0, 0x30C0);
    memset(&temochiOffset, 0, 0x140);
    temochiOffset = 0x1E0;
    temochiFlag = 0;
    markMask = 0;
    scroll = 0.0f;
    memset(model, 0, 0xEC);
    modelFlag = 0;
    pokemonInit((u32)&displayPokemon);
    displayFlag = 0;
    if (st.tutorial) {
        tutorialMode = 1;
    }
    f37E0 = 0;
    f37E4 = 4;
    f37E8 = 6;
    f37EC = 10;
    MENU_ITEM_dd_* item = menuItemBiosGetPtr(0x82, 0x3EE);
    slotBaseX = item->x;
    slotBaseY = item->y;
    memcpy(&cursorPos[0], &_cursorPositionTblDefault[0], 0x10);
    for (int i = 0; i < 6; i++) {
        PocketVec<short> v = getTemochiSlotPosition(i);
        cursorPos[4 + i] = v;
    }
    for (int i = 0; i < 30; i++) {
        PocketVec<short> v = getPcBoxSlotPosition(i);
        cursorPos[10 + i] = v;
    }
    gstate = &st;
    cursor = &gstate->cursor;
    cursor->setPositionTable(&cursorPos[0], 10);
    resetViewAntAll();
    localWindowSetTable(localWindowTable);
    localWindowCreateAll();
    info2.init(0x87, 0x46A);
    info.initTutorialTalk();
    menuPtSpriteWorkGetByItemID(0x80L, 0x3D4, 0);
    menuModelInit();
}

void CMenuPokemonLeave::menuModelInit()
{
    if (modelFlag) {
        menuModelCheck(model, 1);
    }
    tagSPRITE_WORK* sp = menuPtSpriteWorkGetByItemID(0x80L, 0x3D4, 0);
    ::menuModelInit(model, sp->w, sp->h);
    menuModelSetSize(model, sp->x, sp->y, sp->w, sp->h);
}

void CMenuPokemonLeave::menuModelTerm()
{
    if (modelFlag) {
        menuModelCheck(model, 1);
    }
    ::menuModelTerm(model);
    modelFlag = 0;
    memset(model, 0, 0xEC);
}

void CMenuPokemonLeave::main(CMenuGlobalState& st)
{
    init(st);
    if (gstate->mode == 2) {
        alphaFadeInKick();
        animState.change(2);
    } else {
        systemFadeInKick();
    }
    loop();
    menuModelTerm();
    localWindowDeleteAll();
    cursor->setPositionTableDummy();
    menuPcBoxSetLastViewBox(boxIndex);
    CAnt::allRequestCancel();
    CAnt::waitEndOfReading();
}

void CMenuPokemonLeave::loop()
{
    state.change(1);
    char buf[0x18];
    while (true) {
        state.update();
        switch (state.current) {
        case 1:
            state.change(2);
            break;
        case 2:
            stateMainProc();
            break;
        case 3: {
            Pokemon* cp = currentPokemonGetPointer();
            setStatusAndModelDisplayPokemon(cp);
            menuPtPlaySe(0x14);
            temochiFlag = 1;
            animState.change(3);
            int free = temochiPokemonGetFreePosition();
            long target;
            if (cursor->isCatchPokemon()) {
                if (free == 6) {
                    target = 9;
                } else {
                    target = free + 4;
                }
            } else {
                target = 4;
            }
            cursor->setPositionIndex(target);
            state.change(2);
            break;
        }
        case 4: {
            Pokemon* cp = currentPokemonGetPointer();
            setStatusAndModelDisplayPokemon(cp);
            menuPtPlaySe(0x15);
            temochiFlag = 0;
            animState.change(4);
            cursor->setPositionIndex(10);
            state.change(2);
            break;
        }
        case 5: {
            menuPtPlaySe(0x14);
            u32 list[2];
            list[0] = 0x3C13;
            list[1] = 0x3C14;
            info2.open(0x3BDA, false);
            info2.setMsgCtrlValue(0x4D, (u32)PCBOX::getPointer()->getPokemonBoxName(boxIndex));
            long sel = actionMenu(list, 2, 0x1EC, 0x106, 0);
            info2.close();
            if (sel == 0) {
                state.change(6);
            } else {
                state.change(2);
            }
            break;
        }
        case 6:
            stateBoxNameChangeExecProc();
            state.change(2);
            break;
        case 7:
            if (cursor->flag) {
                directActionExec();
            } else {
                stateActionMenuMainProc();
            }
            break;
        case 8:
            menuPtPlaySe(0x13);
            infoMessageDisplay(state.work2[0]);
            if (state.work2[1] != 0) {
                state.change(state.work2[1]);
            } else {
                state.change(2);
            }
            break;
        case 9:
            stateDepositToPcBoxProc();
            break;
        case 10:
            stateMarkingProc();
            state.change(2);
            break;
        case 11:
            if (currentPokemonGetArea() == 2 && temochiPokemonLiveQuantity(true) <= 0) {
                state.change(8);
                state.work[0] = 0x3BE3;
                break;
            }
            if (currentPokemonGetPointer()->isDarkPokemon()) {
                state.change(8);
                state.work[0] = 0x3BE7;
                break;
            }
            if (!confirmWindow(0x3BE4, 1)) {
                state.change(2);
            } else {
                state.change(0xC);
            }
            break;
        case 12: {
            int area;
            Pokemon* p = currentPokemonGetPointer();
            setStatusAndModelDisplayPokemon(p);
            GScharCpy(buf, p->getNicknamePtr());
            area = currentPokemonGetArea();
            CAnt before = *currentAntGetPointer();
            currentPokemonDel(true);
            cursor->setBeforAnt(before);
            if (area != 1) {
                cursorUnderPokemonGetAntPointer()->init();
            }
            animState.change(7);
            waitAnimationStateEnd();
            resetStatusAndModelDisplayPokemon();
            if (area != 1) {
                displayHide = 1;
            }
            info2.setMsgCtrlValue(0x32, (u32)buf);
            infoMessageDisplay(0x3BE5);
            info2.setMsgCtrlValue(0x32, (u32)buf);
            infoMessageDisplay(0x3BE6);
            if (area == 2) {
                animState.change(9);
            } else {
                animState.change(0);
            }
            state.change(2);
            break;
        }
        case 13: {
            if (!temochiPokemonAddAble()) {
                state.change(8);
                state.work[0] = 0x3BD0;
                break;
            }
            if (!cursor->isCatchPokemon()) {
                Pokemon* under = cursorUnderPokemonGetPointer();
                cursor->setPokemon(under);
                cursorUnderPokemonDel();
                resetViewAntAll();
            }
            long saved = cursor->index;
            temochiFlag = 1;
            animState.change(3);
            cursor->setPositionIndex(searchTemochiPokemonBlankSlot() + 4);
            waitAnimationStateEnd();
            cursorUnderPokemonSet(cursor->getPokemonPtr(), false);
            cursor->deletePokemon();
            resetViewAntAll();
            waitAtTime(0.1f);
            temochiFlag = 0;
            animState.change(4);
            cursor->setPositionIndex(saved);
            state.change(2);
            break;
        }
        case 14:
            stateStatusProc();
            state.change(2);
            break;
        case 15:
            state.change(8);
            state.work[0] = 0x3BD1;
            break;
        case 16:
            if (gstate->mode == 2) {
                state.change(0x12);
            } else if (cursor->isCatchPokemon()) {
                state.change(0xF);
            } else {
                menuPtPlaySe(0x14);
                if (confirmWindow(0x3BDE, 0)) {
                    state.change(2);
                } else {
                    state.change(0x11);
                }
            }
            break;
        case 17:
        {
            systemFadeOutSetAndWait(-1.0f);
            CMenuGlobalState* g = gstate;
            g->mode = g->next;
            g->next = 0;
            return;
        }
        case 18: {
            alphaFadeOutAndWait();
            CMenuGlobalState* g = gstate;
            g->mode = g->next;
            g->next = 2;
            return;
        }
        }
    }
}

void CMenuPokemonLeave::directActionExec()
{
    if (cursor->isCatchPokemon()) {
        if (cursorUnderPokemonGetPointer() != 0) {
            actionExecByMsgID(0x3BCF);
        } else {
            actionExecByMsgID(0x3BCE);
        }
    } else {
        actionExecByMsgID(0x3BC8);
    }
}

void CMenuPokemonLeave::stateActionMenuMainProc()
{
    u32 list[6];
    if (cursor->isCatchPokemon()) {
        if (cursorUnderPokemonGetPointer() != 0) {
            list[0] = 0x3BCF;
        } else {
            list[0] = 0x3BCE;
        }
    } else {
        list[0] = 0x3BC8;
    }
    list[1] = 0x3BC9;
    if (cursor->index >= 4 && cursor->index <= 9) {
        list[2] = 0x3BCD;
    } else {
        list[2] = 0x3BCA;
    }
    list[3] = 0x3BCB;
    list[4] = 0x3BE8;
    list[5] = 0x3BCC;
    info2.open(0x3BC7, false);
    info2.setMsgCtrlValue(0x32, (u32)currentPokemonGetPointer()->getNicknamePtr());
    long sel = actionMenu(list, 6, 0x1C6, 0x8A, 0);
    actionExecByMsgID(list[sel]);
    info2.close();
}

bool CMenuPokemonLeave::confirmWindow(unsigned long msg, long defaultSel)
{
    u32 list[2];
    list[0] = 0x3BDF;
    list[1] = 0x3BE0;
    info2.open(msg, false);
    long sel = actionMenu(list, 2, 0x1FD, 0x106, defaultSel);
    info2.close();
    return sel == 0;
}

void CMenuPokemonLeave::actionExecByMsgID(unsigned long msg)
{
    switch (msg) {
    case 0x3BCF: {
        menuPtPlaySe(0x446);
        if (cursor->getPokemonPtr()->getHp() == 0 && currentPokemonGetArea() == 1 && temochiPokemonLiveQuantity(true) <= 0) {
            state.change(8);
            state.work[0] = 0x3BE3;
            break;
        }
        setStatusAndModelDisplayPokemon(cursor->getPokemonPtr());
        Pokemon tmp = *cursor->getPokemonPtr();
        cursor->setPokemon(cursorUnderPokemonGetPointer());
        cursorUnderPokemonSet(&tmp, true);
        animState.change(6);
        resetViewAntAll();
        break;
    }
    case 0x3BCE: {
        menuPtPlaySe(0x446);
        cursorUnderPokemonSet(cursor->getPokemonPtr(), false);
        cursor->deletePokemon();
        resetViewAntAll();
        int idx = cursor->index;
        if (idx >= 4 && idx <= 9) {
            if (idx - 4 >= temochiPokemonGetFreePosition()) {
                animState.change(8);
            }
        }
        break;
    }
    case 0x3BC8: {
        int area = currentPokemonGetArea();
        if (area == 2 && temochiPokemonLiveQuantity(true) <= 0) {
            state.change(8);
            state.work[0] = 0x3BE3;
            break;
        }
        menuPtPlaySe(0x445);
        Pokemon* under = cursorUnderPokemonGetPointer();
        cursor->setPokemon(under);
        cursorUnderPokemonDel();
        resetViewAntAll();
        if (area == 2) {
            animState.change(9);
        }
        break;
    }
    case 0x3BC9:
        state.change(0xE);
        break;
    case 0x3BCA:
        state.change(0xD);
        break;
    case 0x3BCD:
        if (currentPokemonGetArea() == 2 && temochiPokemonLiveQuantity(true) <= 0) {
            state.change(8);
            state.work[0] = 0x3BE3;
        } else {
            state.change(9);
        }
        break;
    case 0x3BCB:
        state.change(0xA);
        break;
    case 0x3BE8:
        state.change(0xB);
        break;
    case 0x3BCC:
        state.change(2);
        break;
    }
    if (state.next == -1) {
        state.change(2);
    }
}

void CMenuPokemonLeave::infoMessageDisplay(unsigned long msg)
{
    info2.exec(*this, msg, true);
}

void _depositMenuDrawHook(CMetaMenu* menu, long windowId)
{
    ((CMenuPokemonLeave*)menu)->depositMenuDraw(windowId);
}

void CMenuPokemonLeave::stateDepositToPcBoxProc()
{
    bool done;
    int saved = depositBox;
    info2.open(0x3BD3, false);
    localWindowEntry(0x89, 0, _depositMenuDrawHook);
    done = false;
    while (!done) {
        switch (getKeyInfo()->trg) {
        case 4:
            depositBox = (depositBox + 7) % 8;
            menuPtPlaySe(0x441);
            break;
        case 8:
            depositBox = (depositBox + 1) % 8;
            menuPtPlaySe(0x441);
            break;
        case 0x10:
            if (pcBoxEmptyQuantity(depositBox) != 0) {
                done = cursor->isCatchPokemon();
                Pokemon* p = currentPokemonGetPointer();
                menuPtPlaySe(0x442);
                pcBoxPokemonAdd(p, depositBox);
                currentPokemonDel(false);
                if (!done) {
                    animState.change(9);
                }
                done = true;
            } else {
                info2.close();
                menuPtPlaySe(0x13);
                infoMessageDisplay(0x3BD4);
                info2.open(0x3BD3, false);
                continue;
            }
            break;
        case 0x20:
            menuPtPlaySe(0x443);
            depositBox = saved;
            done = true;
            break;
        }
        updateAll();
    }
    localWindowRemove(0x89);
    info2.close();
    state.change(2);
}

void CMenuPokemonLeave::depositMenuDraw(long windowId)
{
    menuPtWindowWorkDraw(windowId);
    boxNameDraw(depositBox, windowId, 0x487);
    tagWINDOW_WORK* w = (tagWINDOW_WORK*)windowSearchID(windowId);
    tagSPRITE_WORK* sp = menuPtSpriteWorkGetByItemID(w, 0x488, 0);
    msgctrlSetValue(0x34, pcBoxUsedQuantity(depositBox));
    msgctrlSetValue(0x35, 0x1E);
    GSmsgPrint2(w->layer, w->x + sp->x, w->y + sp->y, -1, 0x3BD2);
}

void CMenuPokemonLeave::boxNameDraw(int box, long windowId, unsigned long itemId)
{
    tagWINDOW_WORK* w = (tagWINDOW_WORK*)windowSearchID(windowId);
    tagSPRITE_WORK* sp = menuPtSpriteWorkGetByItemID(w, itemId, 0);
    void* name = PCBOX::getPointer()->getPokemonBoxName(box);
    msgctrlSetValue(0x37, (u32)name);
    s16 tw = GSmsgGetRect(0x4276) >> 16;
    s16 off = sp->w / 2 - tw / 2;
    GSmsgPrint2(w->layer, w->x + sp->x + off, w->y + sp->y, -1, 0x4276);
}

void CMenuPokemonLeave::markingMenuItemCallBack(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    int slot;
    switch (s->itemId) {
    case 0x44B:
        slot = 0;
        break;
    case 0x44D:
        slot = 1;
        break;
    case 0x44F:
        slot = 2;
        break;
    case 0x451:
        slot = 3;
        break;
    case 0x453:
        slot = 4;
        break;
    case 0x455:
        slot = 5;
        break;
    default:
        slot = -1;
        break;
    }
    if (slot != -1) {
        long cur = windowGetValue(0x86);
        winSpriteSetDisp(s, cur == slot);
    } else {
        int bit;
        switch (s->itemId) {
        case 0x45B:
            bit = 0;
            break;
        case 0x45C:
            bit = 1;
            break;
        case 0x45D:
            bit = 2;
            break;
        case 0x45E:
            bit = 3;
            break;
        default:
            bit = -1;
            break;
        }
        if (bit != -1) {
            winSpriteSetDisp(s, (markMask & (1 << bit)) != 0);
        }
    }
}

void CMenuPokemonLeave::stateMarkingProc()
{
    markMask = currentPokemonPcBoxMarkGet();
    long v = 0;
    info2.open(0x3BDB, false);
    localWindowEntry(0x86, 0, 0);
    menuOpenCustom(0x86, windowGetActiveID(), &v, 0, 1, 0);
    tagWINDOW_WORK* w = (tagWINDOW_WORK*)windowSearchID(0x86);
    bool done = false;
    while (!done) {
        if (w->buttonCancel) {
            done = true;
        } else if (w->buttonDone) {
            v = windowGetValue(0x86);
            if (v <= 3) {
                markMask = markMask ^ (1 << v);
                w->buttonDone = 0;
            } else if (v == 4) {
                currentPokemonPcBoxMarkSet(markMask);
                done = true;
            } else if (v == 5) {
                done = true;
            }
        }
        updateAll();
    }
    menuClose(0x86);
    menuCloseSync(0x86, 1);
    localWindowRemove(0x86);
    info2.close();
}

Pokemon* CMenuPokemonLeave::pokemonStatusMenuCallback(Pokemon* cur, MENU_POKEMON_CB_TYPE type)
{
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor* c = cursor;
        if (c->pokemon.checkValid()) {
            return &c->pokemon;
        }
        return 0;
    }
    long idx = f37EC;
    Pokemon* r = 0;
    if (idx >= 4 && idx <= 9) {
        if (type == 1) {
            while (true) {
                idx = idx <= 4 ? 4 : idx - 1;
                r = temochiPokemonGetPointer(idx - 4);
                if (r != 0) {
                    break;
                }
                if (idx <= 4) {
                    break;
                }
            }
        } else if (type == 2) {
            while (true) {
                idx = idx >= 9 ? 9 : idx + 1;
                r = temochiPokemonGetPointer(idx - 4);
                if (r != 0) {
                    break;
                }
                if (idx >= 9) {
                    break;
                }
            }
        }
    } else if (idx >= 10) {
        if (type == 1) {
            while (true) {
                idx = idx <= 10 ? 10 : idx - 1;
                r = pcBoxPokemonGetPointer(idx - 10);
                if (r != 0) {
                    break;
                }
                if (idx <= 10) {
                    break;
                }
            }
        } else if (type == 2) {
            do {
                idx = idx >= 0x27 ? 0x27 : idx + 1;
                r = pcBoxPokemonGetPointer(idx - 10);
            } while (r == 0 && idx < 0x27);
        }
    }
    if (r != 0) {
        f37EC = idx;
        return r;
    }
    return cur;
}

Pokemon* _cbMenuPokemonStatus(Pokemon* p, MENU_POKEMON_CB_TYPE type, long)
{
    return pMenuPokemonLeave->pokemonStatusMenuCallback(p, type);
}

void CMenuPokemonLeave::stateStatusProc()
{
    systemFadeOutSetAndWait(-1.0f);
    menuModelTerm();
    localWindowDeleteAll();
    GSfsysReadWait(0x66F);
    f37EC = cursor->index;
    menuPokemonStatusOpenFromPcBox(currentPokemonGetPointer(), _cbMenuPokemonStatus, 0);
    cursor->setPositionIndex(f37EC);
    GSfsysFree(0x66F);
    GSresFreeGroup(0x66F);
    localWindowCreateAll();
    menuModelInit();
    systemFadeInKick();
}

void CMenuPokemonLeave::stateBoxNameChangeExecProc()
{
    systemFadeOutSetAndWait(-1.0f);
    localWindowDeleteAll();
    menuModelRenderOffAll(model);
    GSfsysRead(0x670);
    while (GSfsysGetStatus(0x670) == 1) {
        GSthreadSwitch();
    }
    menuNameEntryCall(3, boxIndex);
    GSfsysFree(0x670);
    GSresFreeGroup(0x670);
    localWindowCreateAll();
    systemFadeInKick();
}

void CMenuPokemonLeave::stateMainProc()
{
    do {
        CKeyInfo* k = getKeyInfo();
        u16 rep = k->rep;
        u16 trg = k->trg;
        bool any = (trg | rep) != 0;
        if (any && animationProcessButtonInterrupt((const tagWINDOW_KEY*)k)) {
            any = false;
        }
        if (any) {
            long pos = cursor->index;
            switch (rep) {
            case 1:
                cursorMoveUp(pos);
                break;
            case 2:
                cursorMoveDown(pos);
                break;
            case 8:
                cursorMoveRight(pos);
                break;
            case 4:
                cursorMoveLeft(pos);
                break;
            case 5:
                if (cursorMoveUp(pos)) {
                    cursorMoveWhenInPcBoxL(pos);
                }
                break;
            case 9:
                if (cursorMoveUp(pos)) {
                    cursorMoveWhenInPcBoxR(pos);
                }
                break;
            case 6:
                if (cursorMoveDown(pos)) {
                    cursorMoveWhenInPcBoxL(pos);
                }
                break;
            case 10:
                if (cursorMoveDown(pos)) {
                    cursorMoveWhenInPcBoxR(pos);
                }
                break;
            case 0x200:
            case 0x400:
                if (!temochiFlag) {
                    boxScroll(rep == 0x200);
                }
                break;
            }
            switch (trg) {
            case 0x10:
                if ((u32)pos < 4) {
                    if (!cursor->isCatchPokemon() || gstate->mode == 2) {
                        menuPtPlaySe(0x442);
                    }
                    state.change(_cursorPositionToStateTbl[pos]);
                } else if (currentPokemonGetPointer() != 0) {
                    if (cursor->flag == 0) {
                        menuPtPlaySe(0x442);
                    }
                    state.change(7);
                }
                break;
            case 0x20:
                if (temochiFlag) {
                    menuPtPlaySe(0x443);
                    state.change(4);
                } else {
                    if (!cursor->isCatchPokemon() || gstate->mode == 2) {
                        menuPtPlaySe(0x443);
                    }
                    state.change(0x10);
                }
                break;
            case 0x40:
            case 0x80:
                cursor->flag = !cursor->flag;
                break;
            case 0x100:
                if (!temochiFlag) {
                    menuPtPlaySe(0x442);
                    state.change(3);
                }
                break;
            }
            if (pos != cursor->index) {
                menuPtPlaySe(0x441);
                if (pos >= 10) {
                    f37E0 = (pos - 10) % 6;
                } else if (pos >= 4 && pos <= 5) {
                    f37E4 = pos;
                } else if (pos >= 6 && pos <= 9) {
                    f37E8 = pos;
                }
                cursor->setPositionIndex(pos);
                animState.change(2);
            }
        }
        updateAll();
    } while (state.next == -1);
}

bool CMenuPokemonLeave::cursorMoveUp(long& idx)
{
    long a = idx;
    if (a == 0) {
        idx = 1;
    } else if (a >= 10 && a <= 15) {
        idx = 0;
    } else if (a >= 10) {
        idx -= 6;
    } else if (a >= 1 && a <= 2) {
        idx = f37E0 + 0x22;
    } else if (a >= 3 && a <= 9) {
        idx = a <= 3 ? 9 : a - 1;
    } else {
        return false;
    }
    return true;
}

bool CMenuPokemonLeave::cursorMoveDown(long& idx)
{
    int a = idx;
    if (a >= 1 && a <= 2) {
        idx = 0;
    } else {
        long b = idx;
        if (b >= 0x22) {
            if ((a - 10) % 6 <= 2) {
                idx = 1;
            } else {
                idx = 2;
            }
        } else if (b >= 10) {
            idx = b + 6;
        } else if (b == 0) {
            idx = f37E0 + 10;
        } else if (a >= 3 && b <= 9) {
            idx = b >= 9 ? 3 : a + 1;
        } else {
            return false;
        }
    }
    return true;
}

void CMenuPokemonLeave::cursorMoveRight(long& idx)
{
    if (!cursorMoveWhenInPcBoxR(idx)) {
        long a = idx;
        if (a >= 1 && a <= 2) {
            int n = a - 1;
            if (n < 1) {
                idx = a + 1;
            }
        } else if (idx == 0) {
            boxScroll(false);
        } else if (a >= 4 && idx <= 5) {
            idx = f37E8;
        } else if (a >= 6 && idx <= 9) {
            state.change(4);
        }
    }
}

void CMenuPokemonLeave::cursorMoveLeft(long& idx)
{
    if (!cursorMoveWhenInPcBoxL(idx)) {
        long a = idx;
        if (a >= 1 && a <= 2) {
            int n = a - 1;
            if (n > 0) {
                idx = n;
            }
        } else if (idx == 0) {
            boxScroll(true);
        } else if (a >= 6 && idx <= 9) {
            idx = f37E4;
        } else if (a >= 4 && idx <= 5) {
            state.change(4);
        }
    }
}

bool CMenuPokemonLeave::cursorMoveWhenInPcBoxL(long& idx)
{
    int i = idx;
    if (i >= 10) {
        if ((i - 10) % 6 > 0) {
            idx = i - 1;
        } else {
            idx = i + 5;
        }
        return true;
    }
    return false;
}

bool CMenuPokemonLeave::cursorMoveWhenInPcBoxR(long& idx)
{
    int i = idx;
    if (i >= 10) {
        if ((i - 10) % 6 < 5) {
            idx = i + 1;
        } else {
            idx = i - 5;
        }
        return true;
    }
    return false;
}

void CMenuPokemonLeave::boxScroll(bool back)
{
    boxTarget = boxIndex;
    if (back) {
        boxIndex = (boxIndex + 7) % 8;
    } else {
        boxIndex = (boxIndex + 1) % 8;
    }
    s8 id = boxIndex;
    PCBOX::getPointer();
    PCBOX::lastWatchBoxID = id;
    animState.change(5);
    state.change(2);
    menuPtPlaySe(0x444);
}

void CMenuPokemonLeave::waitAnimationStateEnd()
{
    do {
        updateAll();
    } while (animState.current != 0 && animState.current != 1);
}

bool CMenuPokemonLeave::animationProcessButtonInterrupt(const tagWINDOW_KEY* key)
{
    int st = animState.current;
    if (st == 5) {
        
        if (key->buttons == 0x200 || key->buttons == 0x400) {
            return true;
        }
        int idx = cursor->index;
        if (key->buttons == 4 || key->buttons == 8) {
            if (idx == 0) {
                return true;
            }
        }
    }
    if (st != 0) {
        animState.change(0);
        animationStateUpdate();
    }
    return false;
}

void CMenuPokemonLeave::animationStateUpdate()
{
    scroll = 0.0f;
    animState.update();
    switch (animState.current) {
    case 0:
        if (!animState.time) {
            if (temochiFlag) {
                temochiOffset = 0;
            } else {
                temochiOffset = 0x1E0;
            }
            resetViewAntAll();
            cursor->setAnimationOff();
            resetStatusAndModelDisplayPokemon();
            displayHide = 0;
        }
        break;
    case 2: {
        if (!animState.time) {
            cursor->mode = 3;
        }
        f32 t = animState.time / 0.1f;
        cursor->setT(t);
        if (t >= 1.0f) {
            animState.change(0);
        }
        break;
    }
    case 3: {
        if (!animState.time) {
            cursor->mode = 3;
            cursor->t = 0.0f;
        }
        f32 t = animState.time / 0.25f;
        f32 m;
        if (t < 1.0f) {
            m = t;
        } else {
            m = 1.0f;
        }
        temochiOffset = (int)(480.0f * (1.0f - m));
        if (t >= 1.0f) {
            animState.change(2);
        }
        break;
    }
    case 4: {
        if (!animState.time) {
            cursor->mode = 3;
            cursor->t = 0.0f;
        }
        f32 t = animState.time / 0.25f;
        temochiOffset = (int)(480.0f * clamp1(t));
        if (t >= 1.0f) {
            animState.change(2);
        }
        break;
    }
    case 5: {
        u32 total = (u32)(0.5f * (f32)GSgfxVideoGetVsyncRate());
        u32 n = animState.count + 1;
        f32 nextF = (f32)(n + 1) / (f32)total;
        f32 curF = (f32)n / (f32)total;
        if (nextF >= 1.0f) {
            animState.change(0);
        }
        f32 v = 1.0f;
        if (curF < 1.0f) {
            v = curF;
        }
        scroll = v;
        break;
    }
    case 6: {
        if (!animState.time) {
            cursor->mode = 1;
            cursorUnderPokemonGetAntPointer()->setA14(1);
        }
        f32 t = animState.time / 0.25f;
        cursor->setT(t);
        if (t >= 1.0f) {
            animState.change(0);
        }
        break;
    }
    case 7: {
        if (!animState.time) {
            cursor->mode = 2;
        }
        f32 t = animState.time / 0.5f;
        cursor->setT(t);
        if (t >= 1.0f) {
            animState.change(1);
        }
        break;
    }
    case 8: {
        f32 t = animState.time / 0.2f;
        int idx = cursor->index;
        int dst = temochiPokemonGetFreePosition() - 1;
        PocketVec<short> a = getTemochiSlotPosition(idx - 4);
        PocketVec<short> b = getTemochiSlotPosition(dst);
        temochiAnt[dst].pos = lerpPos(a, b, t);
        if (t >= 1.0f) {
            animState.change(0);
        }
        break;
    }
    case 9: {
        if (!animState.time) {
            resetViewAntAll();
            if (temochiPokemonIsFull()) {
                animState.change(0);
                break;
            }
        }
        f32 t = animState.time / 0.2f;
        for (int i = cursor->index - 4; i < 6; i++) {
            if (temochiAnt[i].a0 != 0) {
                PocketVec<short> a = getTemochiSlotPosition(i);
                PocketVec<short> b = getTemochiSlotPosition(i + 1);
                temochiAnt[i].pos = lerpPos(b, a, t);
            }
        }
        if (t >= 1.0f) {
            animState.change(0);
        }
        break;
    }
    }
}

void CMenuPokemonLeave::drawAll()
{
    animationStateUpdate();
    menuPtWindowWorkDraw(0x8AL);
    if (animState.current == 5) {
        int target = boxTarget;
        if ((target + 1) % 8 == boxIndex) {
            drawBoxArea(target, -scroll);
            drawBoxArea(boxIndex, 1.0f - scroll);
        } else {
            drawBoxArea(target, scroll);
            drawBoxArea(boxIndex, -1.0f + scroll);
        }
    } else {
        drawBoxArea(boxIndex, 0.0f);
    }
    drawStatusArea();
    drawTemochiArea();
    alphaFadeDraw();
    cursor->draw();
    localWindowDrawAll();
    CAnt::systemUpdate(true);
    info2.draw();
    info.draw();
}

void CMenuPokemonLeave::drawStatusArea()
{
    tagWINDOW_WORK* w = (tagWINDOW_WORK*)windowSearchID(0x80);
    bool loaded = false;
    Pokemon* p = getStatusAndModelDisplayPokemonGetPointer();
    if (p != 0 && !menuModelComparePokemon(model, p) && !menuModelCheck(model, 0)) {
        menuModelLoadPokemon(model, p);
        loaded = true;
        modelFlag = 1;
    }
    if (p != 0 && menuModelComparePokemon(model, p) && !menuModelCheck(model, 0) && !loaded) {
        menuPtSpriteWorkGetByItemID(w, 0x3D4, 0);
        menuModelAdjustCamera(model);
        f32 angle[3];
        angle[0] = -0.1f;
        angle[1] = 0.3f;
        angle[2] = 0.0f;
        menuModelSetAngle(model, angle);
        menuModelRender(model);
    } else {
        menuModelRenderOffAll(model);
    }
    u32 msg = 0;
    if (p != 0) {
        u8 sex = menuSubGetPokemonSexForDisp(p);
        if (sex == 0) {
            msg = 0x9C5;
        } else if (sex == 1) {
            msg = 0x9C6;
        }
    } else {
        msg = 0;
    }
    menuPtSpriteWorkSetMsgId(0x80, 0x5C2, 0, msg);
    u16 item = 0;
    if (p != 0) {
        item = p->getItemDataId();
    }
    menuPtSpriteWorkSetSw(w, 0x3CF, 0, item != 0);
    for (int i = 0; i < 4; i++) {
        menuPtSpriteWorkSetSw(w, 0x3C7, i, p != 0);
    }
    for (int i = 0; i < 4; i++) {
        menuPtSpriteWorkSetSw(w, 0x3CB, i, pokemonPcBoxMarkGetIndex(p, i));
    }
    menuPtSpriteWorkSetSw(w, 0x3DB, 0, p != 0);
    menuPtWindowWorkDraw(0x80L);
    tagSPRITE_WORK* sp = menuPtSpriteWorkGetByItemID(w, 0x3D9, 0);
    u32 msgId = 0x3BD7;
    if (gstate->mode == 2) {
        u32 stage = relivehallGetLastViewStage() + 1;
        msgId = 0x3C2D;
        msgctrlSetValue(0x34, stage);
    }
    s16 tw = GSmsgGetRect(msgId) >> 16;
    GSmsgPrint2(w->layer, sp->x + (s16)((sp->w - tw) / 2), sp->y, -1, msgId);
    if (p != 0) {
        u32 nameId;
        u32 lvId;
        switch (pokecoloGetCountryCode()) {
        case 0:
            nameId = 0x4276;
            lvId = 0x427B;
            break;
        case 1:
        case 2:
            nameId = 0x4277;
            lvId = 0x4351;
            break;
        }
        if (item != 0) {
            void* d = itemDataBiosGetPtr(item);
            if (d != 0) {
                msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(itemDataBiosGetName(d)));
                sp = menuPtSpriteWorkGetByItemID(w, 0x3D8, 0);
                GSmsgPrint2(w->layer, w->x + sp->x, w->y + sp->y, -1, nameId);
            }
        }
        msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(pokemonDataBiosGetName(p->getPokemonDataPtr())));
        sp = menuPtSpriteWorkGetByItemID(w, 0x3DC, 0);
        GSmsgPrint2(w->layer, w->x + sp->x, w->y + sp->y, -1, nameId);
        msgctrlSetValue(0x37, (u32)p->getNicknamePtr());
        sp = menuPtSpriteWorkGetByItemID(w, 0x3DA, 0);
        GSmsgPrint2(w->layer, w->x + sp->x, w->y + sp->y, -1, nameId);
        sp = menuPtSpriteWorkGetByItemID(w, 0x3DB, 0);
        msgctrlSetValue(0x34, p->getLevel());
        GSmsgPrint2(w->layer, sp->x + 0x24 + w->x, w->y + sp->y, -1, lvId);
        if (p->isDarkPokemon()) {
            sp = menuPtSpriteWorkGetByItemID(w, 0x4CE, 0);
            menuDrawReliveMeter3(p, w->x + sp->x, w->y + sp->y, sp->w, sp->h, 0xFF, w->layer);
        }
        u16 ids[2];
        for (int i = 0; i < 2; i++) {
            ids[i] = zokuseiGetPokemonSpriteID(p->getPokemonDataPtr(), i);
        }
        tagSPRITE_WORK* s1 = menuPtSpriteWorkGetByItemID(w, 0x5C0, 0);
        tagSPRITE_WORK* s2 = menuPtSpriteWorkGetByItemID(w, 0x5C1, 0);
        if (ids[0] == ids[1]) {
            menuPtSpriteDraw(ids[0], (s1->x + s2->x) / 2, (s1->y + s2->y) / 2);
        } else {
            menuPtSpriteDraw(ids[0], s1->x, s1->y);
            menuPtSpriteDraw(ids[1], s2->x, s2->y);
        }
        menuDrawReliveUpdate();
    }
}

void CMenuPokemonLeave::drawBoxArea(int box, float offset)
{
    tagSPRITE_WORK* it;
    MENU_SPRITE_dd_* ms;
    tagWINDOW_WORK* w;
    short xoff;
    w = (tagWINDOW_WORK*)windowSearchID(0x82);
    tagSPRITE_WORK* sp = menuPtSpriteWorkGetByItemID(w, 0x3E5, 0);
    xoff = (short)((f32)sp->w * offset);
    w->x = xoff;
    ms = menuSpriteBiosGetPtr(box + 0x325);
    for (it = w->sprites; it != 0; it = it->next) {
        if (menuPtItemGetBySpriteWork(w, it)->spriteId == 0x325) {
            menuPtSpriteWorkSetMenuSprite(it, ms);
        }
    }
    menuPtWindowWorkDraw(w);
    boxNameDraw(box, 0x82, 0x40E);
    GSprimSetup2DRender(0);
    spriteSetScissor(w->layer, 0xDA, 0, 0x1A6, 0x196);
    CAnt* ant = boxAnt[box];
    for (int i = 0; i < 30; ant++, i++) {
        if (ant->a0 != 0) {
            PocketVec<short> off;
            off.x = xoff;
            off.y = 0;
            ant->drawAndUpdateWithOffset(off);
        }
    }
    spriteSetOffset(w->layer, 0, 0);
    spriteClearScissor(w->layer);
    spriteSetEnv(w->layer);
}

void CMenuPokemonLeave::drawTemochiArea()
{
    if (temochiOffset != 0x1E0) {
        tagWINDOW_WORK* w = (tagWINDOW_WORK*)windowSearchID(0x84);
        w->y = temochiOffset;
        menuPtWindowWorkDraw(0x84L);
        GSprimSetup2DRender(0);
        for (int i = 0; i < 6; i++) {
            CAnt* ant = &temochiAnt[i];
            if (ant->a0 != 0) {
                PocketVec<short> off;
                off.x = 0;
                off.y = temochiOffset;
                ant->drawAndUpdateWithOffset(off);
            }
        }
    }
}

void CMenuPokemonLeave::resetViewAntAll()
{
    int next;
    int prev;
    int b;
    CAnt::systemUsecountReset();
    for (int i = 0; i < 6; i++) {
        CAnt* ant = &temochiAnt[i];
        ant->init();
        Pokemon* p = temochiPokemonGetPointer(i);
        if (p != 0) {
            ant->initByPokemonAndSetColorAnimationInAny(p);
            PocketVec<short> v = getTemochiSlotPosition(i);
            ant->pos = v;
            ant->setAnimation(0);
        }
    }
    prev = (boxIndex + 7) % 8;
    next = (boxIndex + 1) % 8;
    for (b = 0; b < 8; b++) {
        bool near = false;
        if (prev == b || boxIndex == b) {
            near = true;
        }
        bool show = true;
        if (!near && next != b) {
            show = false;
        }
        s8 box = b;
        for (int slot = 0; slot < 30; slot++) {
            CAnt* ant = &boxAnt[b][slot];
            ant->init();
            if (show) {
                Pokemon* p = pcBoxPokemonGetPointer(box, (s8)slot);
                if (p != 0) {
                    ant->initByPokemonAndSetColorAnimationInAny(p);
                    PocketVec<short> v = getPcBoxSlotPosition(slot);
                    ant->pos = v;
                    ant->setAnimation(0);
                }
            }
        }
    }
    cursor->ant.use();
    cursor->before.use();
    CAnt::systemUnUseResourceRelease();
}

Pokemon* CMenuPokemonLeave::temochiPokemonGetPointer(int slot)
{
    Pokemon* p = Hero::getHeroPtr()->getPokemon(slot);
    if (p->checkValid()) {
        return p;
    }
    return 0;
}

int CMenuPokemonLeave::temochiPokemonGetFreePosition()
{
    int i = 0;
    do {
        if (temochiPokemonGetPointer(i) == 0) {
            break;
        }
        i++;
    } while (i < 6);
    if (i == 6) {
        return -1;
    }
    return i;
}

bool CMenuPokemonLeave::temochiPokemonAdd(Pokemon* p)
{
    return Hero::getHeroPtr()->addPokemon(p) != -1;
}

void CMenuPokemonLeave::temochiPokemonSet(Pokemon* p, int slot)
{
    Hero::getHeroPtr()->setPokemon(p, slot);
}

void CMenuPokemonLeave::temochiPokemonDel(int slot)
{
    pokemonInit((u32)temochiPokemonGetPointer(slot));
}

void CMenuPokemonLeave::temochiPokemonDelShift(int slot)
{
    for (int i = slot; i < 5; i++) {
        Pokemon* a = temochiPokemonGetPointer(i);
        Pokemon* b = temochiPokemonGetPointer(i + 1);
        if (a != 0) {
            if (b == 0) {
                temochiPokemonDel(i);
            } else {
                memcpy(a, b, 0xC4);
            }
        }
    }
    temochiPokemonDel(5);
}

int CMenuPokemonLeave::temochiPokemonLiveQuantity(bool excludeCursor)
{
    int skip = -1;
    if (excludeCursor) {
        int i = cursor->index;
        if (i >= 4 && i <= 9) {
            skip = i - 4;
        }
    }
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (i == skip) {
            continue;
        }
        Pokemon* p = temochiPokemonGetPointer(i);
        if (p == 0) {
            break;
        }
        if (p->getHp() != 0) {
            count++;
        }
    }
    return count;
}

int CMenuPokemonLeave::temochiPokemonQuantity()
{
    int i = 0;
    do {
        if (temochiPokemonGetPointer(i) == 0) {
            break;
        }
        i++;
    } while (i < 6);
    return i;
}

bool CMenuPokemonLeave::temochiPokemonAddAble()
{
    return temochiPokemonQuantity() < 6;
}

bool CMenuPokemonLeave::temochiPokemonIsFull()
{
    return temochiPokemonQuantity() >= 6;
}

int CMenuPokemonLeave::searchTemochiPokemonBlankSlot()
{
    int n = temochiPokemonQuantity();
    if (n == 6) {
        n = -1;
    }
    return n;
}

Pokemon* CMenuPokemonLeave::pcBoxPokemonGetPointer(int slot)
{
    return pcBoxPokemonGetPointer(boxIndex, slot);
}

Pokemon* CMenuPokemonLeave::pcBoxPokemonGetPointer(int box, int slot)
{
    Pokemon* p = PCBOX::getPointer()->getPokemon(box, slot);
    if (p->checkValid()) {
        return p;
    }
    return 0;
}

void CMenuPokemonLeave::pcBoxPokemonDel(int slot)
{
    PCBOX::getPointer()->delPokemon(boxIndex, slot);
}

void CMenuPokemonLeave::pcBoxPokemonAdd(Pokemon* p, int box)
{
    if (box == -1) {
        box = boxIndex;
    }
    PCBOX::getPointer()->addPokemon(p, box);
}

void CMenuPokemonLeave::pcBoxPokemonSet(Pokemon* p, int slot)
{
    PCBOX::getPointer()->setPokemon(p, boxIndex, slot);
}

int CMenuPokemonLeave::pcBoxEmptyQuantity(int box)
{
    return PCBOX::getPointer()->getPokemonBoxNbEmptySlot(box);
}

int CMenuPokemonLeave::pcBoxUsedQuantity(int box)
{
    return PCBOX::getPointer()->getPokemonBoxNbUsedSlot(box);
}

CAnt* CMenuPokemonLeave::cursorUnderPokemonGetAntPointer()
{
    int i = cursor->index;
    if (i >= 4 && i <= 9) {
        return &temochiAnt[i - 4];
    }
    if (i >= 10) {
        return &boxAnt[boxIndex][i - 10];
    }
    return 0;
}

Pokemon* CMenuPokemonLeave::cursorUnderPokemonGetPointer()
{
    int i = cursor->index;
    if (i >= 4 && i <= 9) {
        return temochiPokemonGetPointer(i - 4);
    }
    if (i >= 10) {
        return pcBoxPokemonGetPointer(i - 10);
    }
    return 0;
}

void CMenuPokemonLeave::cursorUnderPokemonDel()
{
    int i = cursor->index;
    if (i >= 4 && i <= 9) {
        temochiPokemonDelShift(i - 4);
    } else if (i >= 10) {
        pcBoxPokemonDel(i - 10);
    }
}

void CMenuPokemonLeave::cursorUnderPokemonSet(Pokemon* p, bool replace)
{
    int i = cursor->index;
    if (i >= 4 && i <= 9) {
        if (replace) {
            int slot = i - 4;
            temochiPokemonDel(slot);
            temochiPokemonSet(p, slot);
        } else {
            temochiPokemonAdd(p);
        }
    } else if (i >= 10) {
        int slot = i - 10;
        pcBoxPokemonDel(slot);
        pcBoxPokemonSet(p, slot);
    }
}

int CMenuPokemonLeave::currentPokemonGetArea()
{
    if (cursor->isCatchPokemon()) {
        return 1;
    }
    int i = cursor->index;
    if (i >= 4 && i <= 9) {
        return 2;
    }
    if (i >= 10) {
        return 3;
    }
    return 0;
}

Pokemon* CMenuPokemonLeave::currentPokemonGetPointer()
{
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor* c = cursor;
        if (c->pokemon.checkValid()) {
            return &c->pokemon;
        }
        return 0;
    }
    return cursorUnderPokemonGetPointer();
}

void CMenuPokemonLeave::setStatusAndModelDisplayPokemon(Pokemon* p)
{
    displayFlag = 1;
    if (p == 0) {
        pokemonInit((u32)&displayPokemon);
    } else {
        memcpy(&displayPokemon, p, 0xC4);
    }
}

void CMenuPokemonLeave::resetStatusAndModelDisplayPokemon()
{
    pokemonInit((u32)&displayPokemon);
    displayFlag = 0;
}

Pokemon* CMenuPokemonLeave::getStatusAndModelDisplayPokemonGetPointer()
{
    if (displayHide != 0) {
        return 0;
    }
    if (displayFlag != 0) {
        if (pokemonCheckValid(&displayPokemon)) {
            return &displayPokemon;
        }
        return 0;
    }
    return currentPokemonGetPointer();
}

void CMenuPokemonLeave::currentPokemonDel(bool dark)
{
    Pokemon* p = currentPokemonGetPointer();
    if (p != 0) {
        if (dark) {
            DarkPokemon* d = p->getDarkPokemon();
            if (d != 0) {
                d->setPlace(place6, 0);
            }
        }
        if (cursor->isCatchPokemon()) {
            cursor->deletePokemon();
        } else {
            cursorUnderPokemonDel();
        }
    }
}

CAnt* CMenuPokemonLeave::currentAntGetPointer()
{
    if (cursor->isCatchPokemon()) {
        return &cursor->ant;
    }
    return cursorUnderPokemonGetAntPointer();
}

void CMenuPokemonLeave::currentPokemonPcBoxMarkSet(u8 mark)
{
    Pokemon* p = currentPokemonGetPointer();
    if (p != 0) {
        p->setPcboxMark(mark);
    }
}

u8 CMenuPokemonLeave::currentPokemonPcBoxMarkGet()
{
    Pokemon* p = currentPokemonGetPointer();
    if (p != 0) {
        return p->getPcboxMark();
    }
    return 0;
}

bool CMenuPokemonLeave::pokemonPcBoxMarkGetIndex(Pokemon* p, int index)
{
    if (p != 0) {
        return (p->getPcboxMark() & (u8)(1 << index)) != 0;
    }
    return false;
}

void thisNew()
{
    void* mem = GSmemAllocClr(0x38A0);
    pMenuPokemonLeave = new (mem) CMenuPokemonLeave;
}

void thisFree()
{
    if (pMenuPokemonLeave != 0) {
        GSmemFree(pMenuPokemonLeave);
        pMenuPokemonLeave = 0;
    }
}

void thisExec(CMenuGlobalState& state)
{
    thisNew();
    pMenuPokemonLeave->main(state);
    thisFree();
}

}

void menuPcBoxPokemon(CMenuGlobalState& state)
{
    thisExec(state);
}

extern "C" {

struct MarkingCtrl {
    u8 pad0;
    s8 mode;
    s8 flag;
};

s32 menuPcBoxMarkingCtrl(MarkingCtrl* c)
{
    switch (c->mode) {
    case 0:
        if (c->flag == 0) {
            c->flag = 1;
        }
        break;
    case 3:
        if (c->flag == 0) {
            c->flag = 1;
        }
        break;
    }
    return 0;
}

}

extern "C" {

s32 menuPcBoxMarkingItemCallback(tagWINDOW_WORK* w, tagSPRITE_WORK* s)
{
    pMenuPokemonLeave->markingMenuItemCallBack(w, s);
    return 0;
}

}
