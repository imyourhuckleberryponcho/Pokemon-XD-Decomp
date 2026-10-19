#include <dolphin/types.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

// Pocket/menu helper tools. Menu files were built without the peephole optimizer.
#pragma peephole off

struct MenuPtWorkSound {
    u32 bgm;
    u32 env;
    u8 bgmVol;
    u8 envVol;
};

extern "C" {
u32 soundGetBGMID();
u32 soundGetEnvID();
u32 soundGetVolume();
void soundOpenPlay(u32, s32, u8);
void soundOpenPlayEnv(u32, s32, u8);
void GSthreadSwitch();
u16 windowGetKeyTrg();
s32 Sequence_GetGSmodel();
s32 Sequence_GetModelSize(s32);
void memoGetScaleAngle(u16, f32*, f32*);
void* GSmodelGetBound(s32);
void GSboundGetSize(void*, f32*, s32, s32);
void pokemonCreate(Pokemon*, u16, s32, s32);
s32 gamedataGetStatus(s32, s32);
void pokemonSetDarkPokemonStatus(Pokemon*, u16);
u16 pokemonBiosGetInitDp(Pokemon*);
extern u32 darkPokemonList_number;
}

static u32 _darkPokemonIndex = 0xC;

void menuPtRestoreSound(MenuPtWorkSound* s)
{
    if (s->bgm != 0 && s->bgm != soundGetBGMID()) {
        soundOpenPlay(s->bgm, 0x32, s->bgmVol);
    }
    if (s->env != 0 && s->env != soundGetEnvID()) {
        soundOpenPlayEnv(s->env, 0x32, s->envVol);
    }
}

void menuPtSaveSound(MenuPtWorkSound* s)
{
    u32 bgm = soundGetBGMID();
    u8 bgmVol;
    if (bgm) bgmVol = soundGetVolume(); else bgmVol = 0;
    u32 env = soundGetEnvID();
    u8 envVol;
    if (env) envVol = soundGetVolume(); else envVol = 0;
    s->bgm = bgm;
    s->env = env;
    s->bgmVol = bgmVol;
    s->envVol = envVol;
}

void menuPtStopSound(MenuPtWorkSound* s)
{
    u32 bgm = soundGetBGMID();
    u8 bgmVol;
    if (bgm) {
        bgmVol = soundGetVolume();
        soundOpenPlay(8, 0x32, 0xFF);
    } else {
        bgmVol = 0;
    }
    u32 env = soundGetEnvID();
    u8 envVol;
    if (env) envVol = soundGetVolume(); else envVol = 0;
    s->bgm = bgm;
    s->env = env;
    s->bgmVol = bgmVol;
    s->envVol = envVol;
}

void menuPocketButtonWait()
{
    do {
        GSthreadSwitch();
    } while ((windowGetKeyTrg() & 0x30) == 0);
}

static inline f32 pmax(f32 a, f32 b)
{
    if (a > b) {
    } else {
        a = b;
    }
    return a;
}

f32 menuGetPokemonScale(u32 id, int index)
{
    f32 size[4];
    f32 scale;
    f32 memoScale;
    f32 angle;
    s32 model = Sequence_GetGSmodel();
    switch (Sequence_GetModelSize(id)) {
    case -2: scale = 0.6f; break;
    case -1: scale = 0.75f; break;
    case 0: scale = 1.0f; break;
    case 1: scale = 1.15f; break;
    case 2: scale = 1.25f; break;
    case 3: scale = 1.4f; break;
    default: scale = 1.0f; break;
    }
    memoGetScaleAngle(index, &memoScale, &angle);
    GSboundGetSize(GSmodelGetBound(model), size, 0, 0);
    f32 m = size[0];
    if (m > size[1]) {
    } else {
        m = size[1];
    }
    f32 r = 11.0f / (memoScale * (m / scale));
    static f32 multi = 2.0f;
    return r * multi;
}

void menuPocketSetDarkPokemon(Pokemon& p, f32 mult, u16 id);
u16 pokemonindex(int);

void menuPocketDebugMakeDarkPokemonByID(Pokemon& p, u16 id, f32 mult)
{
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    u16 pid = dark->getPokemonID();
    pokemonCreate(&p, pid, 0x19, gamedataGetStatus(0, 1));
    menuPocketSetDarkPokemon(p, mult, id);
    pokemonBiosGetInitDp(&p);
}

void menuPocketDebugMakePokemonByID(Pokemon& p, u16 id, bool dark, f32 mult)
{
    pokemonCreate(&p, id, 0x19, gamedataGetStatus(0, 1));
    if (dark) {
        int tries = 0;
        do {
            _darkPokemonIndex++;
            if (_darkPokemonIndex >= darkPokemonList_number) _darkPokemonIndex = 1;
            menuPocketSetDarkPokemon(p, mult, (u16)_darkPokemonIndex);
            if (pokemonBiosGetInitDp(&p) != 0) break;
            tries++;
        } while (tries < 10);
    }
}

void makePocketDeubugMakeDarkPokemonReset()
{
    _darkPokemonIndex = 0xC;
}

void menuPocketDebugMakePokemonBySN(Pokemon& p, u16 sn, bool dark, f32 mult)
{
    menuPocketDebugMakePokemonByID(p, pokemonindex(sn % 386), dark, mult);
}

void menuPocketSetDarkPokemon(Pokemon& p, f32 mult, u16 id)
{
    pokemonSetDarkPokemonStatus(&p, id);
    u16 dp = pokemonBiosGetInitDp(&p);
    p.setDarkPoint((f32)dp * mult);
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    dark->setStatus((darkPokemonStatus)3);
    dark->setSnatchIndex((u8)id);
}

u16 pokemonindex(int n)
{
    int v = n + 1;
    if (v > 0xFB) v += 0x19;
    return v;
}

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

struct MENU_DATA_dd_ {
    u8 b0;
    u8 b1hi : 4;
    u8 b1mode : 3;
    u8 b1lo : 1;
    u8 b2mode : 3;
    u8 b2rest : 5;
    u8 b3;
    u8 b4;
    u8 pad5;
    s16 s6;
    s16 s8;
    s16 sA;
    void (*cursorFunc)(tagWINDOW_WORK*);
    void (*buttonFunc)(tagWINDOW_WORK*);
    s32 i14;
    s32 i18;
};

struct GSgfxColAu8 {
    u8 r, g, b, a;
};

extern "C" {
void GSgfxLayerSetActive(s32);
u8 GSgfxVideoGetVsyncRate();
s32 floorGetMenuLayerID();
void spriteSetOffset(s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void spriteClearEnv(s32);
void GSmsgMain(s16, s32, u16, bool);
void GSmsgPrint2(s16, s32, s32, s32, s32);
void GSmsgExec(u32, s32, s32);
s32 GSmsgIsCheck(s32);
void GSmsgKill(s32);
void msgctrlSetValue(u32, u32);
void* windowSearchID(s32);
s32 winSpriteGetLayerID(void*, void*);
u32 timeGetLastFrameTime();
f32 timeGetLastFrameSec();
s8 fadeCheck(s32);
void fadeSet(s32, f32);
void fadeSetToBlackInIfBlack(f32);
void fadeSetToBlackOutIfNotBlack(f32);
void GSprimSetQuadVertexOrder(s32);
void GSprimDraw2DQuad4V(void*, GSgfxColAu8);
u16 windowGetKeyOn();
s32 windowGetActiveID();
void* menuDataBiosGetPtr(s32);
s32 menuSubOpenSelect(s32, u32*, s32, s32, s32, s32);
void windowCloseMain(void*);
void menuOpenCustom(s32, s32, ...);
void menuSetDisp(s32, s32);
extern u8 winMsgDraw[];
void GSsndPlayNow(u32);
void winSpriteDraw(void*, void*);
void GSgfxBlendMode(s32, s32, s32);
MENU_SPRITE_dd_* menuSpriteBiosGetValPtr(MENU_SPRITE_dd_*);
MENU_SPRITE_dd_* menuSpriteBiosGetPtr(u32);
MENU_ITEM_dd_* menuItemBiosGetPtr(s32, s32);
void windowDrawSprite2(s16, s16, s16, s16, u32, s32, u16, s32, s32);
void windowDrawSprite(s16, s16, s32, u16, s32, s32);
void winSpriteSetDisp(void*, bool);
u8 GSresGetResourceAllGroup(u32);
u16 GStextureGetXsize(u8);
u16 GStextureGetYsize(u8);
void GSprimDraw2DTexQuad4V(f32*, f32*, u8, GSgfxColAu8);
double cos(double);
double fmod(double, double);
double sin(double);

/* MSL-style float math wrappers: callers expand them inline (frsp into a temporary). */
static inline float msl_sinf(float x) { return (float) sin(x); }
static inline float msl_cosf(float x) { return (float) cos(x); }
}



template <typename T>
struct PocketVec {
    T x, y;
    static PocketVec<T> zero;
};

struct CAnt {
    s32 a0, a4, a8;
    f32 aC;
    u8 a10;
    s32 a14;
    s16 a18, a1A;
    f32 a1C;
    s32 a20, a24, a28;
    f32 a2C;
    s32 a30;
    void init();
    void initByPokemonAndSetColorAnimationInAny(Pokemon*);
    void setAnimation(long);
    void drawAndUpdate(PocketVec<short>);
    void drawAndUpdate();
};

extern "C" {
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
}

class CState {
public:
    s32 current, next, prev, count;
    f32 time;
    f32 dt;
    u8 work[0x40];
    u8 work2[0x40];
    s32 w98, w9c, wa0;
    u8 padA4[4];
    void update();
    void addTime();
    void init();
};

class CMenuPokemonCursor {
public:
    u8 active;
    s32 mode;
    f32 t;
    s32 index;
    s32 prevIndex;
    PocketVec<short> pos;
    PocketVec<short>* table;
    f32 timer;
    Pokemon pokemon;
    CAnt ant;
    CAnt before;
    u8 flag;
    static PocketVec<short> defaultPositionTbl;

    void draw();
    bool isCatchPokemon();
    void deletePokemon();
    void setBeforAnt(CAnt&);
    void setPokemon(Pokemon*);
    void setPositionTableDummy();
    void setPositionIndex(long);
    void setPositionTable(PocketVec<short>*, long);
    void setAnimationOff();
    void init();
};

void menuPtSpriteDrawColor(u16, long, long, long, long, u32);
void menuPtSpriteDrawColor(u16, long, long, u32);

PocketVec<short> CMenuPokemonCursor::defaultPositionTbl;

class CMenuGlobalState {
public:
    s32 pad0, pad4, pad8;
    CMenuPokemonCursor cursor;
    u8 padTail[4];
    CState state;
    void init();
};

void CMenuGlobalState::init()
{
    memset(this, 0, 0x208);
    cursor.init();
    state.init();
}

void CMenuPokemonCursor::draw()
{
    if (active) {
        PocketVec<short> p;
        if (mode == 3) {
            PocketVec<short>* dst = &table[index];
            p.x = (short)(t * (f32)(dst->x - pos.x) + (f32)pos.x);
            p.y = (short)(t * (f32)(dst->y - pos.y) + (f32)pos.y);
        } else {
            PocketVec<short>* src = &table[index];
            p.x = src->x;
            p.y = src->y;
        }
        if (isCatchPokemon()) {
            p.x += 8;
            p.y -= 8;
            if (mode == 1) {
                f32 sn = msl_sinf(3.1415927f * t);
                int d1 = (int)(-8.0f * t);
                int d2 = (int)(20.0f * sn);
                PocketVec<short> v1 = p;
                PocketVec<short> v2 = p;
                PocketVec<short> v3 = p;
                v2.x += d2;
                v1.x -= d2;
                v2.y -= d1;
                v1.y -= -8 - d1;
                if (t < 0.5f) {
                    ant.drawAndUpdate(v1);
                    before.drawAndUpdate(v2);
                } else {
                    before.drawAndUpdate(v2);
                    ant.drawAndUpdate(v1);
                }
            } else {
                ant.drawAndUpdate(p);
            }
        } else if (mode == 2) {
            before.aC = 1.0f - t;
            before.drawAndUpdate();
        }
        f32 q = timer / 0.5f;
        if (q > 0.5f) q = 1.0f - q;
        f32 pulse = 2.0f * q;
        timer = timer + timeGetLastFrameSec();
        if (timer >= 0.5f) timer = (f32)fmod(timer, 0.5);
        p.x -= 0x2D;
        p.y -= 0x2D;
        u32 col;
        if (flag) col = 0xFFC800FF; else col = 0xFFFFFFFF;
        if (!isCatchPokemon()) {
            MENU_SPRITE_dd_* sp = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x216));
            short w = sp->w;
            short h = sp->h;
            short off = (short)(5.0f * pulse);
            if (off > 4) off = 4;
            short x1 = p.x + off + 4;
            short y1 = p.y + off + 4;
            menuPtSpriteDrawColor(0x216, x1, y1, w, h, col);
            short x2 = p.x + 0x32 - off;
            menuPtSpriteDrawColor(0x216, x2, y1, -w, h, col);
            short y2 = p.y + 0x32 - off;
            menuPtSpriteDrawColor(0x216, x1, y2, w, -h, col);
            menuPtSpriteDrawColor(0x216, x2, y2, -w, -h, col);
        } else {
            menuPtSpriteDrawColor(0x215, p.x + 0xE, p.y + 0xE, (col & 0xFFFFFF00) | (short)(155.0f * pulse + 100.0f));
        }
        menuPtSpriteDrawColor(0x214, p.x + 7, p.y + 0x23, col);
    }
}

bool CMenuPokemonCursor::isCatchPokemon()
{
    return pokemon.checkValid();
}

void CMenuPokemonCursor::deletePokemon()
{
    pokemonInit((u32)&pokemon);
    before = ant;
    ant.init();
}

void CMenuPokemonCursor::setBeforAnt(CAnt& a)
{
    before = a;
}

void CMenuPokemonCursor::setPokemon(Pokemon* p)
{
    before = ant;
    if (p == 0) {
        pokemonInit((u32)&pokemon);
        ant.init();
        return;
    }
    memcpy(&pokemon, p, 0xC4);
    ant.initByPokemonAndSetColorAnimationInAny(&pokemon);
    ant.setAnimation(0);
}

void CMenuPokemonCursor::setPositionTableDummy()
{
    PocketVec<short> v = table[index];
    defaultPositionTbl.x = v.x;
    defaultPositionTbl.y = v.y;
    table = &defaultPositionTbl;
    index = 0;
    prevIndex = 0;
}

void CMenuPokemonCursor::setPositionIndex(long i)
{
    PocketVec<short> v = table[index];
    pos.x = v.x;
    pos.y = v.y;
    prevIndex = index;
    index = i;
}

void CMenuPokemonCursor::setPositionTable(PocketVec<short>* t, long i)
{
    setPositionIndex(i);
    prevIndex = 0;
    table = t;
}

void CMenuPokemonCursor::setAnimationOff()
{
    mode = 0;
    t = 0.0f;
    before.init();
}

void CMenuPokemonCursor::init()
{
    memset(this, 0, 0x150);
    active = 1;
    pokemonInit((u32)&pokemon);
    ant.init();
    before.init();
    flag = 0;
    defaultPositionTbl.x = 0;
    defaultPositionTbl.y = 0;
    pos.x = 0;
    pos.y = 0;
    table = &defaultPositionTbl;
}

class CMetaMenu;

struct VP {
    u32 id;
    u32 value;
};

struct CInfoWindow {
    s32 windowId;
    s32 itemId;
    u8 opened;
    bool isMsg;
    s32 msgId;
    VP values[4];
    u16 buttons;

    void exec(CMetaMenu&, u32, bool);
    void draw();
    void setMsgCtrlValue(u32, u32);
    bool isMsgEnd();
    void open(u32, bool);
    void close();
    void initTutorialTalk();
    void init(long, u32);
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
    u8 pad278[0xA8];
    u64 time;
    void* tutorial;
    u8 updated;
    u8 pad32D;
    u16 cachedInput;

    virtual void reservedVirtual0() = 0;
    virtual bool isAnimationStateNone() { return true; }
    virtual void updateAll();
    virtual void tutorialExitKick() {}

    static CMetaMenu* pCurrentMenu;
    static long defautlLocalWindowOpenTable[1];

    void waitAtTime(f32);
    long calcAnimationTimeRate0toX(f32, long);
    f32 calcAnimationTimeRate0to1to0(f32);
    f32 calcAnimationTimeRate0to1(f32);
    void drawHook();
    void vsyncUpdate();
    void systemFadeWaitToEnd();
    void systemFadeOutSetAndWait(f32);
    void systemFadeOutKick(f32);
    void systemFadeInKick();
    void systemFadeOutKeepAfterFloorPush();
    void alphaFadeDraw();
    u8 getAlphaFadeAlpha() const;
    void alphaFadeOutAndWait();
    void alphaFadeUpdate();
    void alphaFadeOutKick();
    void alphaFadeInKick();
    CKeyInfo* getKeyInfo();
    void aButtonWait();
    long actionMenu(u32*, int, long, long, long);
    void localWindowRemove(long);
    void localWindowDrawAll(long, long);
    void localWindowDrawAll();
    void localWindowEntry(long, long, void (*)(CMetaMenu*, long));
    long localWindowSearch(long);
    void localWindowDeleteAll();
    void localWindowCreateAll();
    void localWindowSetTable(long*);
    u16 tutorialManage();
    void tutorialManageUpdate();
};

CMetaMenu* CMetaMenu::pCurrentMenu;
long CMetaMenu::defautlLocalWindowOpenTable[1] = { 0 };
extern const GSgfxColAu8 GSgfxColAu8_Black;
const GSgfxColAu8 GSgfxColAu8_Black = { 0, 0, 0, 0xFF };
static CMetaMenu* _pThis;
static long _selectItemQuantity;

void menuPtWindowWorkDraw(long);
tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(tagWINDOW_WORK*, u32, long);
tagSPRITE_WORK* menuPtGetSpriteWorkByHookFunction(tagWINDOW_WORK*, void*, u32, long);
void menuPtPlaySe(u32);
void menuPtMenuLoad(long);
void menuPtWindowWorkDraw(tagWINDOW_WORK*);
void menuPtWindowWorkDrawPrime(tagWINDOW_WORK*);
MENU_ITEM_dd_* menuPtItemGetBySpriteWork(tagWINDOW_WORK*, tagSPRITE_WORK*);
void menuPtSpriteWorkSetMenuSprite(tagSPRITE_WORK*, MENU_SPRITE_dd_*);
tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(long, u32, long);
u32 GSgfxColAu8To32(GSgfxColAu8);

void CInfoWindow::exec(CMetaMenu& menu, u32 msg, bool close_)
{
    open(msg, true);
    do {
        buttons = windowGetKeyTrg();
        menu.updateAll();
    } while (!isMsgEnd());
    if (close_) close();
}

void CInfoWindow::draw()
{
    if (opened) {
        menuPtWindowWorkDraw(windowId);
        CInfoWindow* p = this;
        while (p->values[0].id != 0) {
            msgctrlSetValue(p->values[0].id, p->values[0].value);
            p = (CInfoWindow*)((u8*)p + 8);
        }
        tagWINDOW_WORK* win = (tagWINDOW_WORK*)windowSearchID(windowId);
        tagSPRITE_WORK* spr = menuPtSpriteWorkGetByItemID(win, itemId, 0);
        int layer = winSpriteGetLayerID(win, spr);
        if (isMsg) {
            spriteSetOffset(layer, win->x + spr->x, win->y + spr->y);
            spriteClearScissor(layer);
            spriteSetEnv(layer);
            GSmsgMain((s32)layer, msgId, buttons, (win->flags & 4) == 0);
            spriteSetOffset(layer, 0, 0);
            spriteClearScissor(layer);
            spriteSetEnv(layer);
        } else {
            GSmsgPrint2(layer, win->x + spr->x, win->y + spr->y, -1, msgId);
        }
    }
}

void CInfoWindow::setMsgCtrlValue(u32 id, u32 value)
{
    int i = 0;
    while (values[i].id != 0) i++;
    values[i].id = id;
    values[i].value = value;
}

bool CInfoWindow::isMsgEnd()
{
    return GSmsgIsCheck(msgId) == 0;
}

void CInfoWindow::open(u32 msg, bool isMsg_)
{
    isMsg = isMsg_;
    if (msg != 0) {
        msgId = msg;
        if (isMsg) GSmsgExec(msgId, 0, 0);
    }
    opened = 1;
}

void CInfoWindow::close()
{
    if (isMsg) GSmsgKill(msgId);
    opened = 0;
    isMsg = 0;
    msgId = 0;
    memset(values, 0, 0x20);
}

void CInfoWindow::initTutorialTalk()
{
    itemId = 0;
    buttons = 0;
    opened = 0;
    isMsg = 0;
    msgId = 0;
    memset(values, 0, 0x20);
    windowId = 0xE3;
    tagWINDOW_WORK* win = (tagWINDOW_WORK*)windowSearchID(windowId);
    tagSPRITE_WORK* spr = menuPtGetSpriteWorkByHookFunction(win, winMsgDraw, 0, 0);
    spr->hook = 0;
    spr->unk5 = 0;
    itemId = spr->itemId;
    close();
}

void CInfoWindow::init(long window, u32 item)
{
    itemId = 0;
    buttons = 0;
    opened = 0;
    isMsg = 0;
    msgId = 0;
    memset(values, 0, 0x20);
    windowId = window;
    itemId = item;
    close();
}

void CMetaMenu::waitAtTime(f32 limit)
{
    f32 t = 0.0f;
    while (true) {
        updateAll();
        if (t > limit) break;
        t += timeGetLastFrameSec();
    }
}

long CMetaMenu::calcAnimationTimeRate0toX(f32 sec, long n)
{
    long m = n + 1;
    f32 v = (f32)m * calcAnimationTimeRate0to1(sec);
    if ((f32)n < v) v = (f32)n;
    return (long)v;
}

f32 CMetaMenu::calcAnimationTimeRate0to1to0(f32 sec)
{
    f32 v = calcAnimationTimeRate0to1(sec);
    if (v > 0.5f) v = 1.0f - v;
    v *= 2.0f;
    return v;
}

f32 CMetaMenu::calcAnimationTimeRate0to1(f32 sec)
{
    u32 frames = (u32)(sec * (f32)GSgfxVideoGetVsyncRate());
    return (f32)(u32)(time % frames) / (f32)frames;
}

void CMetaMenu::drawHook()
{
    GSgfxLayerSetActive(7);
    s32 layer = floorGetMenuLayerID();
    spriteSetOffset(7, 0, 0);
    spriteClearScissor(7);
    spriteSetEnv(7);
    spriteSetOffset(layer, 0, 0);
    spriteClearScissor(layer);
    spriteSetEnv(layer);
    reservedVirtual0();
    time += timeGetLastFrameTime();
    alphaFadeUpdate();
    tutorialManageUpdate();
    spriteSetOffset(7, 0, 0);
    spriteClearScissor(7);
    spriteClearEnv(7);
    spriteSetOffset(layer, 0, 0);
    spriteClearScissor(layer);
    spriteClearEnv(layer);
    GSgfxLayerSetActive(2);
}

void CMetaMenu::updateAll()
{
    vsyncUpdate();
}

void CMetaMenu::vsyncUpdate()
{
    GSthreadSwitch();
}

void CMetaMenu::systemFadeWaitToEnd()
{
    while (fadeCheck(0) != 0) {
        updateAll();
    }
}

void CMetaMenu::systemFadeOutSetAndWait(f32 sec)
{
    systemFadeOutKick(sec);
    systemFadeWaitToEnd();
}

void CMetaMenu::systemFadeOutKick(f32 sec)
{
    if (sec == -1.0f) sec = 0.5f;
    fadeSetToBlackOutIfNotBlack(sec);
}

void CMetaMenu::systemFadeInKick()
{
    fadeSetToBlackInIfBlack(0.5f);
}

void CMetaMenu::systemFadeOutKeepAfterFloorPush()
{
    GSthreadSwitch();
    fadeSet(3, 0.0f);
}


void CMetaMenu::alphaFadeDraw()
{
    static f32 xy[8] = { 0.0f, 0.0f, 640.0f, 0.0f, 640.0f, 480.0f, 0.0f, 480.0f };
    GSgfxColAu8 color = { 0, 0, 0, 0xFF };
    GSprimSetQuadVertexOrder(1);
    u8 a = 0xFF - getAlphaFadeAlpha();
    color.a = a;
    if (a != 0) {
        GSprimDraw2DQuad4V(xy, color);
    }
}

u8 CMetaMenu::getAlphaFadeAlpha() const
{
    switch (fadeState) {
    case 0:
        return 0xFF;
    case 3: {
        u32 total = (u32)(0.5f * (f32)GSgfxVideoGetVsyncRate());
        return (s32)(((u32)(0.5f * (f32)GSgfxVideoGetVsyncRate()) - fadeTime) * 0xFF) / (s32)total;
    }
    case 1:
        return (s32)(fadeTime * 0xFF) / (s32)(u32)(0.5f * (f32)GSgfxVideoGetVsyncRate());
    case 2:
        return 0;
    default:
        return 0;
    }
}

void CMetaMenu::alphaFadeOutAndWait()
{
    alphaFadeOutKick();
    u8 ok;
    do {
        updateAll();
        s32 st = fadeState;
        ok = 0;
        if (st == 0 || st == 2) ok = 1;
    } while (ok == 0);
    updateAll();
}

void CMetaMenu::alphaFadeUpdate()
{
    if (fadeTime != 0) {
        fadeTime -= timeGetLastFrameTime();
        if (fadeTime <= 0) {
            if (fadeState == 3) {
                fadeState = 0;
            } else if (fadeState == 1) {
                fadeState = 2;
            }
        }
    }
}

void CMetaMenu::alphaFadeOutKick()
{
    fadeTime = (u32)(0.5f * (f32)GSgfxVideoGetVsyncRate());
    fadeState = 1;
}

void CMetaMenu::alphaFadeInKick()
{
    fadeTime = (u32)(0.5f * (f32)GSgfxVideoGetVsyncRate());
    fadeState = 3;
}

CKeyInfo* CMetaMenu::getKeyInfo()
{
    if (tutorialMode) {
        memset(&keyInfo, 0, 0x1A);
        u16 k = tutorialManage();
        keyInfo.trg = k;
        keyInfo.rep = k;
        return &keyInfo;
    }
    memset(&keyInfo, 0, 0x1A);
    if (windowGetActiveID() != 0xDA) return &keyInfo;
    u16 rep = 0;
    u16 trg = windowGetKeyTrg();
    u16 on = windowGetKeyOn();
    bool count = false;
    if (trg != 0) {
        rep = trg;
    } else if (on != 0 && on == lastOn) {
        if (repeat >= 12) {
            rep = on;
        } else {
            count = true;
        }
    }
    if (count) {
        repeat++;
    } else {
        repeat = 0;
    }
    lastOn = on;
    keyInfo.rep = rep;
    keyInfo.trg = trg;
    return &keyInfo;
}

void CMetaMenu::aButtonWait()
{
    bool done = false;
    while (!done) {
        if ((s32)getKeyInfo()->trg != 0x10) {
        } else {
            done = true;
            menuPtPlaySe(seId);
        }
        updateAll();
    }
}

static void _tutorialWindowCursorFunc(tagWINDOW_WORK*);
static void _tutorialWindowButtonFunc(tagWINDOW_WORK*);

long CMetaMenu::actionMenu(u32* list, int a, long count, long b, long defaultSel)
{
    MENU_DATA_dd_* m = (MENU_DATA_dd_*)menuDataBiosGetPtr(0x59);
    u8 b2, b3, b4;
    s16 s6, s8, sA;
    void (*f0)(tagWINDOW_WORK*);
    void (*f1)(tagWINDOW_WORK*);
    s32 i14, i18;
    u8 b1, b0;
    if (tutorialMode) {
        _selectItemQuantity = count;
        _pThis = this;
        b1 = *((u8*)m + 1);
        b2 = *((u8*)m + 2);
        b3 = m->b3;
        b4 = m->b4;
        s6 = m->s6;
        s8 = m->s8;
        sA = m->sA;
        f0 = m->cursorFunc;
        f1 = m->buttonFunc;
        i14 = m->i14;
        i18 = m->i18;
        b0 = m->b0;
        m->b1mode = 4;
        m->cursorFunc = _tutorialWindowCursorFunc;
        m->b2mode = 4;
        m->buttonFunc = _tutorialWindowButtonFunc;
    }
    long r = menuSubOpenSelect(0, list, a, count, b, defaultSel);
    if (r == -1) r = count - 1;
    if (tutorialMode) {
        m->b0 = b0;
        *((u8*)m + 1) = b1;
        *((u8*)m + 2) = b2;
        m->b3 = b3;
        m->b4 = b4;
        m->s6 = s6;
        m->s8 = s8;
        m->sA = sA;
        m->cursorFunc = f0;
        m->buttonFunc = f1;
        m->i14 = i14;
        m->i18 = i18;
    }
    return r;
}

static void _tutorialWindowCursorFunc(tagWINDOW_WORK* w)
{
    if (w != 0) {
        menuDataBiosGetPtr(w->menuId);
        u16 k = _pThis->tutorialManage();
        if (k & 1) {
            w->cursor--;
            if (w->cursor < 0) {
                w->cursor = (s16)(_selectItemQuantity - 1);
            }
        } else if (k & 2) {
            w->cursor++;
            if (w->cursor >= _selectItemQuantity) {
                w->cursor = 0;
            }
        }
        w->cursorShadow = w->cursor;
    }
}

static void _tutorialWindowButtonFunc(tagWINDOW_WORK* w)
{
    if (w != 0) {
        u16 k = _pThis->tutorialManage();
        if (k & 0x10) {
            w->buttonDone = 1;
        }
        if (k & 0x20) {
            w->buttonDone = 1;
            w->buttonCancel = 1;
        }
    }
}

void CMetaMenu::localWindowRemove(long id)
{
    long i = localWindowSearch(id);
    if (i != -1) {
        windowIds[i] = 0;
    }
}

void CMetaMenu::localWindowDrawAll(long from, long to)
{
    for (long i = from; i <= to; i++) {
        if (windowIds[i] != 0) {
            if (windowFuncs[i] != 0) {
                windowFuncs[i](this, windowIds[i]);
            } else {
                menuPtWindowWorkDraw(windowIds[i]);
            }
        }
    }
}

void CMetaMenu::localWindowDrawAll()
{
    localWindowDrawAll(0, 0x3F);
}

void CMetaMenu::localWindowEntry(long id, long index, void (*func)(CMetaMenu*, long))
{
    windowIds[index] = id;
    windowFuncs[index] = func;
}

long CMetaMenu::localWindowSearch(long id)
{
    for (long i = 0; i < 64; i++) {
        if (windowIds[i] == id) return i;
    }
    return -1;
}

void CMetaMenu::localWindowDeleteAll()
{
    windowCloseMain(windowSearchID(0xDA));
    pCurrentMenu = 0;
    int i = 0;
    while (true) {
        if (windowTable[i] == 0) break;
        windowCloseMain(windowSearchID(windowTable[i]));
        i++;
    }
}

void CMetaMenu::localWindowCreateAll()
{
    menuOpenCustom(0xDA, windowGetActiveID(), 0, 0, 0, 0);
    int i = 0;
    while (true) {
        long id = windowTable[i];
        if (id == 0) break;
        menuPtMenuLoad(id);
        menuSetDisp(id, 0);
        i++;
    }
    pCurrentMenu = this;
}

void CMetaMenu::localWindowSetTable(long* table)
{
    windowTable = table;
}

extern "C" {
s32 menuPocketToolCMetaButton()
{
    return 0;
}
}

extern "C" {
s32 menuPocketToolCMetaDraw()
{
    if (CMetaMenu::pCurrentMenu != 0) {
        CMetaMenu::pCurrentMenu->drawHook();
    }
    return 0;
}
}

extern "C" {
s32 menuPocketToolCMetaCtrl()
{
    return 0;
}
}

void CState::update()
{
    if (next != -1) {
        prev = current;
        current = next;
        next = -1;
        time = 0.0f;
        count = 0;
        w98 = 0;
        w9c = 0;
        wa0 = 0;
        memcpy(work2, work, 0x40);
    } else {
        addTime();
    }
}

void CState::addTime()
{
    count++;
    dt = timeGetLastFrameSec();
    time = time + dt;
}

void CState::init()
{
    memset(this, 0, 0xA8);
    prev = -1;
    dt = timeGetLastFrameSec();
}

void menuPtPlayBgm(u32 id)
{
    soundOpenPlay(id, 0x32, 0xFF);
}

void menuPtPlaySe(u32 id)
{
    GSsndPlayNow(id);
}

void menuPtWindowWorkDraw(long id)
{
    menuPtWindowWorkDraw((tagWINDOW_WORK*)windowSearchID(id));
}

void menuPtWindowWorkDraw(tagWINDOW_WORK* w)
{
    if (w != 0) {
        s32 l;
        s32 menuLayer = floorGetMenuLayerID();
        l = w->layer;
        spriteSetOffset(l, w->x, w->y);
        spriteClearScissor(l);
        spriteSetEnv(l);
        spriteSetOffset(menuLayer, w->x, w->y);
        spriteClearScissor(menuLayer);
        spriteSetEnv(menuLayer);
        menuPtWindowWorkDrawPrime(w);
        spriteSetOffset(w->layer, 0, 0);
        spriteClearScissor(w->layer);
        spriteSetEnv(w->layer);
    }
}

void menuPtWindowWorkDrawPrime(tagWINDOW_WORK* w)
{
    tagSPRITE_WORK* p = w->sprites;
    while (p != 0) {
        winSpriteDraw(w, p);
        p = p->next;
    }
    GSgfxBlendMode(1, 4, 5);
}

void menuPtMenuLoad(long id)
{
    menuOpenCustom(id, windowGetActiveID(), 0, 4, 0, 0);
}

void menuPtSpriteDrawAndRollScale(u16 id, u32 color, f32 ox, f32 oy, f32 angle, f32 scale)
{
    static f32 xy[8];
    static f32 st[8];
    MENU_SPRITE_dd_* spr = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(id));
    u8 group = GSresGetResourceAllGroup(spr->group);
    u8 g = color >> 16;
    u8 b = color >> 8;
    u8 r = color >> 24;
    u8 a = color;
    GSgfxColAu8 col = GSgfxColAu8();
    col.r = r;
    col.g = g;
    col.b = b;
    col.a = a;
    f32 x = (f32)spr->x;
    f32 y = (f32)spr->y;
    f32 w = (f32)spr->w;
    f32 h = (f32)spr->h;
    st[0] = st[2] = x / (f32)GStextureGetXsize(group);
    st[4] = st[6] = (x + w) / (f32)GStextureGetXsize(group);
    st[3] = st[5] = y / (f32)GStextureGetYsize(group);
    f32 v = (y + h) / (f32)GStextureGetYsize(group);
    xy[2] = 0.0f;
    xy[0] = 0.0f;
    xy[6] = w;
    xy[4] = w;
    xy[5] = 0.0f;
    xy[3] = 0.0f;
    xy[7] = h;
    xy[1] = h;
    f32 half = 0.5f;
    f32 hh = h * half;
    f32 hw = w * half;
    st[1] = st[7] = v;
    for (int i = 0; i < 4; i++) {
        xy[2 * i + 1] -= hh;
        xy[2 * i] -= hw;
    }
    f32 ang = -angle;
    f32* p = xy;
    for (int i = 0; i < 4; i++) {
        f32 px = p[0];
        f32 py = p[1];
        f32 c = msl_cosf(ang);
        f32 s = msl_sinf(ang);
        p[0] = py * s + px * c;
        f32 s2 = msl_sinf(ang);
        p[1] = py * msl_cosf(ang) - px * s2;
        p += 2;
    }
    for (int i = 0; i < 4; i++) {
        xy[2 * i] *= scale;
        xy[2 * i + 1] *= scale;
    }
    for (int i = 0; i < 4; i++) {
        xy[2 * i] += ox;
        xy[2 * i + 1] += oy;
    }
    GSprimSetQuadVertexOrder(1);
    GSprimDraw2DTexQuad4V(xy, st, group, col);
}

void menuPtSpriteDrawCenterColor(u16 id, long x, long y, u32 color)
{
    MENU_SPRITE_dd_* spr = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(id));
    s16 w = spr->w;
    s16 h = spr->h;
    windowDrawSprite2(x - w / 2, y - h / 2, w, h, color, 0, id, 0, 7);
}

void menuPtSpriteDrawColor(u16 id, long x, long y, long w, long h, u32 color)
{
    windowDrawSprite2(x, y, w, h, color, 0, id, 0, 7);
}

void menuPtSpriteDrawColor(u16 id, long x, long y, u32 color)
{
    MENU_SPRITE_dd_* spr = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(id));
    windowDrawSprite2(x, y, spr->w, spr->h, color, 0, id, 0, 7);
}

void menuPtSpriteDraw(u16 id, long x, long y)
{
    windowDrawSprite(x, y, 0, id, 0, 7);
}

void menuPtItemDrawOffsetXWColor(MENU_ITEM_dd_* item, long dx, long w, u32 color)
{
    windowDrawSprite2(item->x + dx, item->y, w, item->h, color, 0, item->spriteId, 0, 7);
}

void menuPtItemDrawOffset(MENU_ITEM_dd_* item, long dx, long dy)
{
    windowDrawSprite2(item->x + dx, item->y + dy, item->w, item->h, -1, 0, item->spriteId, 0, 7);
}

void menuPtItemDrawAlpha(MENU_ITEM_dd_* item, u8 alpha)
{
    windowDrawSprite2(item->x, item->y, item->w, item->h, alpha | ~0xFF, 0, item->spriteId, 0, 7);
}

void menuPtSpriteWorkSetWidthRateColor(tagWINDOW_WORK* w, u32 id, long idx, f32 rate, GSgfxColAu8 color)
{
    tagSPRITE_WORK* spr = menuPtSpriteWorkGetByItemID(w, id, idx);
    MENU_ITEM_dd_* item = menuPtItemGetBySpriteWork(w, spr);
    spr->color = GSgfxColAu8To32(color);
    spr->w = (s16)((f32)item->w * rate);
    winSpriteSetDisp(spr, rate != 0.0f);
}

void menuPtSpriteWorkSetSw(tagWINDOW_WORK* w, tagSPRITE_WORK* spr, bool on)
{
    winSpriteSetDisp(spr, on);
}

void menuPtSpriteWorkSetSw(tagWINDOW_WORK* w, u32 id, long idx, bool on)
{
    winSpriteSetDisp(menuPtSpriteWorkGetByItemID(w, id, idx), on);
}

void menuPtSpriteWorkSetSpriteId(tagSPRITE_WORK* spr, u32 id)
{
    MENU_SPRITE_dd_* ms = menuSpriteBiosGetPtr(id);
    menuPtSpriteWorkSetMenuSprite(spr, ms);
}

void menuPtSpriteWorkSetMenuSprite(tagSPRITE_WORK* spr, MENU_SPRITE_dd_* ms)
{
    MENU_SPRITE_dd_* v = menuSpriteBiosGetValPtr(ms);
    spr->unk58 = v->group;
    spr->sx = v->x;
    spr->sy = v->y;
    spr->sw = v->w;
    spr->sh = v->h;
    spr->w = v->w;
    spr->h = v->h;
}

void menuPtSpriteWorkSetMenuItem(tagWINDOW_WORK* w, tagSPRITE_WORK* spr, u32 index)
{
    MENU_ITEM_dd_* item = menuItemBiosGetPtr(w->menuId, index);
    MENU_SPRITE_dd_* v = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(item->spriteId));
    spr->unk58 = v->group;
    spr->sx = v->x;
    spr->sy = v->y;
    spr->sw = v->w;
    spr->sh = v->h;
    spr->x = item->x;
    spr->y = item->y;
    spr->w = item->w;
    spr->h = item->h;
}

tagSPRITE_WORK* menuPtGetSpriteWorkByHookFunction(tagWINDOW_WORK* w, void* hook, u32 idx, long skip)
{
    tagSPRITE_WORK* p = w->sprites;
    while (p != 0) {
        if (p->hook == (u32)hook && idx-- == 0) break;
        p = p->next;
    }
    while (skip != 0 && p != 0) {
        skip--;
        p = p->next;
    }
    return p;
}

MENU_ITEM_dd_* menuPtItemGetBySpriteWork(tagWINDOW_WORK* w, tagSPRITE_WORK* spr)
{
    return menuItemBiosGetPtr(w->menuId, spr->itemId);
}

long menuPtSpriteWorkGetIndexFromId(tagWINDOW_WORK* w, tagSPRITE_WORK* spr, u32 id)
{
    tagSPRITE_WORK* p = menuPtSpriteWorkGetByItemID(w, id, 0);
    long i = 0;
    while (true) {
        if (p == spr) break;
        p = p->next;
        i++;
    }
    return i;
}

tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(tagWINDOW_WORK* w, u32 id, long n)
{
    tagSPRITE_WORK* p = w->sprites;
    while (p != 0) {
        if (p->itemId == id) break;
        p = p->next;
    }
    while (n > 0) {
        p = p->next;
        n--;
    }
    return p;
}

tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(long window, u32 id, long n)
{
    return menuPtSpriteWorkGetByItemID((tagWINDOW_WORK*)windowSearchID(window), id, n);
}

void menuPtSpriteWorkSetMsgId(long window, u32 id, long n, u32 msg)
{
    menuPtSpriteWorkGetByItemID(window, id, n)->msgId = msg;
}

MENU_ITEM_dd_* menuPtItemGetByMenuIdAndItemId(long menu, u32 item, long n)
{
    MENU_ITEM_dd_* p = menuItemBiosGetPtr(menu, item);
    for (long i = 0; i < n; i++) {
        p = menuItemBiosGetPtr(menu, p->next);
    }
    return p;
}

u32 GSgfxColAu8To32(GSgfxColAu8 c)
{
    u32 out;
    memcpy(&out, &c, 4);
    return out;
}

extern "C" {
double atan2(double, double);
extern unsigned long __float_nan[];
}

static inline int ptFPClassify(f32 x)
{
    switch ((*(s32*)&x) & 0x7f800000) {
    case 0x7f800000:
        if ((*(s32*)&x) & 0x007fffff) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(s32*)&x) & 0x007fffff) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

static inline f32 ptSqrt(f32 x)
{
    if (x > 0.0f) {
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x < 0.0) {
        return *(f32*)__float_nan;
    } else if (ptFPClassify(x) == 1) {
        return *(f32*)__float_nan;
    } else {
        return x;
    }
}

f32 xyxy2distance(const PocketVec<short>& a, const PocketVec<short>& b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int d = dx * dx + dy * dy;
    return ptSqrt((f32)d);
}

f32 dirSubOne(f32 a, f32 b);

bool isDirRegionIn(f32 a, f32 b, f32 c)
{
    f32 lim;
    if (c == b) {
        lim = 6.2831855f;
    } else {
        lim = dirSubOne(c, b);
    }
    return dirSubOne(a, b) <= lim;
}

f32 xy2dir(f32 x, f32 y)
{
    return atan2(x, -y);
}

f32 xyxy2dir(const PocketVec<short>& a, const PocketVec<short>& b)
{
    return atan2((f32)(a.x - b.x), (f32) - (a.y - b.y));
}

int degreeRefresh180(long);

int xyxy2dirDegree(const PocketVec<short>& a, const PocketVec<short>& b)
{
    f32 dir = atan2((f32)(a.x - b.x), (f32) - (a.y - b.y));
    return degreeRefresh180((long)(0.5f + (180.0f * dir) / 3.1415927f));
}

f32 dirRefresh2PI(f32 v);
f32 dirRefreshPI(f32 v);

f32 dirSubOne(f32 a, f32 b)
{
    return dirRefresh2PI(a - b);
}

f32 dirSubHalf(f32 a, f32 b)
{
    return dirRefreshPI(a - b);
}

int degreeSubHalf(long a, long b)
{
    return degreeRefresh180(a - b);
}

int degreeRefresh180(long d)
{
    int r = d % 360;
    if (r >= 180) return r - 360;
    if (r <= -180) return r + 360;
    return r;
}

int degreeRefresh360(long d)
{
    int r = d % 360;
    if (r < 0) return r + 360;
    return r;
}

f32 dirRefresh2PI(f32 v)
{
    f32 r = -((6.2831855f * (f32)(s32)(0.15915494f * v)) - v);
    if (r < 0.0f) r += 6.2831855f;
    return r;
}

f32 dirRefreshPI(f32 v)
{
    f32 r = -((6.2831855f * (f32)(s32)(0.15915494f * v)) - v);
    if (r > 3.1415927f) return r - 6.2831855f;
    if (r < -3.1415927f) r += 6.2831855f;
    return r;
}

void menuPocketToolFloatToZero(f32& v, f32 step)
{
    if (v > 0.0f) {
        f32 t = v - step;
        v = t;
        if (t < 0.0f) v = 0.0f;
    } else if (v < 0.0f) {
        f32 t = v + step;
        v = t;
        if (t > 0.0f) v = 0.0f;
    }
}

void setBitTable(u32* table, long i, bool on)
{
    int word = i / 32;
    int bit = i % 32;
    if (on) table[word] |= 1 << bit;
}

bool getBitTable(u32* table, long i)
{
    return (table[i / 32] & (1 << (i % 32))) != 0;
}

template <>
PocketVec<short> PocketVec<short>::zero = { 0, 0 };

u16 menuRelivehallPcBoxDefaultPokemonSprite = 0x2DF;
