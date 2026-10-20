// WIP: 49/56 functions exact. Needs extra_cflags=["-inline noauto,deferred"] (source is
// written bottom-to-top). Not exact: _menuScriptTokuseiSetumei (regs), menuScriptWazaOshieHook (extra inline-copy
// regs), _checkWaza2 (loop regs), menuScriptInfoRelive (regs), _menuScriptReadMail/_menuScriptPdaAddFunc (float
// regs, same as menuShopOpen), menuScriptEeveeHook (one store order).
// menus opened from event scripts (written from asm).
#pragma peephole off
#pragma pool_strings off
#include <dolphin/types.h>
#include <game/shared/menu_work.h>

struct CURSOR {
    s16 top;
    s16 pos;
};

struct MenuItem {
    u8 pad0[6];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
};

struct MenuSpriteVal {
    u8 pad0[4];
    s16 x;
    s16 w;
};

struct Pokemon;
struct POKEMON_DATA_dd_;
struct KeyInfo;

struct WAZAOSHIEDEF {
    u16 id;
    u16 pad2;
    u32 name;
    u8 pp;
    u8 type;
    s16 power;
    u8 avg;
    u8 padd[3];
    u32 doc;
    u8 flag;
    u8 pad15[3];
};

struct WAZAOSHIE_DATA {
    u16 id;
    u16 pad2;
    u32 mission;
    u32 flag;
};

struct FlagEtcEntry {
    u8 pad0[8];
    u32 value;
    u8 pad[0x14];
};

u32 deckDataVirtualDB_GetTitle(u16 id);
u32 deckDataVirtualDB_GetFlag(u16 id);
u32 deckDataVirtualDB_GetExplanetion2(u16 id);

enum pdaAddFuncDef { PDA_ADD_FUNC_0 };

extern "C" {
extern u32* tutorialdata_number;
extern u16* tutorialdata;
extern WAZAOSHIE_DATA* wazaoshie_data;
extern s32* wazaoshie_data_number;
extern FlagEtcEntry* flag_etc;

KeyInfo* windowGetKeyInfo(void);
u32 windowGetKeyRepeat(void);
CURSOR cursorBiosGetPos(s32);
CURSOR cursorBiosSetPos(s32, CURSOR);
s32 winSpriteGetLayerID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on);
MenuItem* menuItemBiosGetPtr(s32 menuID, u32 index);
void spriteSetScissor(s32 layer, s32 x, s32 y, s32 w, s32 h);
void spriteClearScissor(s32 layer);
void GSmsgPrint2(s32 layer, s16 x, s16 y, u32 color, u32 msg);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
void GSmsgPrintRight(s32 layer, s32 x, s32 y, s32 w, s32 h, u32 color, u32 msg);
u32 GSmsgGetRect(u32 msg);
u32 GSmsgGetCharLength(u16*);
char* GSmsgGetGSchar(u32 msg);
void msgctrlSetValue(s32 id, u32 value);
void* menuSpriteBiosGetPtr(u32 id);
MenuSpriteVal* menuSpriteBiosGetValPtr(void* sprite);
void windowDrawSprite(s16 x, s16 y, void* ctx, u16 key, u32 flags, s32 layer);
void windowDrawSprite2(s16 x, s16 y, s16 w, s16 h, u32 color, void* ctx, u16 key, u32 flags, s32 layer);
void* savedataGetStatus(void* save, s32 kind);
s32 heroBiosGetPokecoupon(void* hero);
u32 heroGetStatus(void* hero, u32 selector, u16 index);
u16 zokuseiBiosGetSpriteID(u16 id);
u16 zokuseiGetPokemonSpriteID(void*, u16);
POKEMON_DATA_dd_* pokemonDataBiosGetPtr(u16 pokeNum);
u8 pokemonDataBiosGetTokuseiDataId(POKEMON_DATA_dd_* pdata, u16 index);
u32 pokemonTokuseiDataBiosGetPtr(u16 index);
u32 pokemonTokuseiDataBiosGetName(u32 data);
u32 pokemonTokuseiDataBiosGetDoc(u32 data);
const char* pokemonDataBiosGetName(POKEMON_DATA_dd_* pdata);
void* menuDataBiosGetPtr(s32 menuID);
void winSeqSetMenu(s32 menuID, u32 id);
void menuSetStatus(s32 menuID, s32 st);
u32 GSflagGet(u32 id);
bool GSflagTest(u32 id);
void GSflagOn(u32 id);
void GSflagSet(u32 id, u32 value);
u16 pokemonBiosGetPokemonDataId(Pokemon* poke);
u16 pokemonDataBiosGetGetWazaDataId(POKEMON_DATA_dd_* pdata, u16 wazaIdx);
u8 pokemonDataBiosGetGetWazaLevel(POKEMON_DATA_dd_* pdata, u16 wazaIdx);
u8 pokemonBiosGetLevel(Pokemon* poke);
bool pokemonCheckValid(Pokemon* pokemon);
u16 pokemonBiosGetDarkpokemonDataId(Pokemon* poke);
u8 darkPokemonBiosGetReliveFlag(u16 id);
Pokemon* heroBiosGetPokemonPtr(void* hero, u16 index);
u8* wazaDataBiosGetPtr(u16 id);
u32 wazaDataBiosGetName(u8* ptr);
u8 wazaDataBiosGetPp(u8* ptr);
u8 wazaDataBiosGetZokuseiDataId(u8* ptr);
s16 wazaDataBiosGetIryoku(u8* ptr);
u8 wazaDataBiosGetAvg(u8* ptr);
u32 wazaDataBiosGetDoc(u8* ptr);
void* memset(void*, int, u32);
void menuClose(s32 menuID);
s32 menuOpen(s32 menuID, s32);
void menuSetPosition(s32 menuID, s32 x, s32 y);
s32 menuOpenCustom(s32 menuID, ...);
void menuCloseCustom(s32 menuID, s32, s32);
void menuCloseSync(s32 menuID, s32);
s32 windowGetActiveID(void);
s32 GSfsysReadWait(u32 id);
void GSresFreeGroup(u32 grp);
void GSthreadSwitch(void);
u8 GSfloorPush(u32 id);
void floorWaitForChange(void);
u32 GSfloorGetCurrent(void);
u32 floorGetPlaceName(u32 id);
s32 winMsgOpen(s8 type, u32 msg, bool a, bool b);
void winMsgClose(bool flag);
void* fightEncountDataBiosGetPtr(u16 id);
void fightEncountDataBiosSetDiskId(void* data, u16 value);
void menuPdaMailListSortExit(void);
s32 menuPdaMailListSortInit(s32 id);
void menuPdaMailXDScript(int top);
void menuPdaZoomIn(void);
void menuCreateOffScreen(f32, f32);
void menuReleaseOffScreen(f32);
u8 menuOffScreenCheckEnable(u8 param);
void floorSetFadeScript(u32 out, u32 in);
u8 GSgfxVideoGetVsyncRate(void);
void GSgfxVideoSetLockFrameRate(s32);
u8 menuOffScreenSetPriority(u8 val);
void menuPdaSetModelPointer(void);
void menuPdaModelVisibility(u32 id, bool vis);
void menuPdaAddFunc(void);
void menuPdaScript(u8 flag);
void menuPdaReleaseModelPointer(void);
void menuPdaSubCheckUpDownCursor(tagWINDOW_WORK*, tagSPRITE_WORK*, s16*, s32, s32, s32);
void GSmodelAllPauseAnimation(void);
void GSmodelAllUnpauseAnimation(void);
u8 GSfloorPop(void);
u8 GSsndPlayNow(u32 id);
void cameraPlayAnime(u32 group, u32 id, u8 loop, f32 frame);
u32 mailGetOpenFlag(int id);
void darkPokemonBiosSetInformationFlag(u16 id, bool information);
char* pokemonBiosGetNicknamePtr(Pokemon* poke);
}

static u16 _WazaNum = 3;
static s32 _tutorialSelect = -1;

static WAZAOSHIEDEF _wazawork;
static u16 _tempwazaid[21];

static WAZAOSHIEDEF* _wazalist;
static s32 _menuScriptWork;
static s32 _PdaAddFunc;
static s32 _menuScriptMailID;
static u8 _menuPdaMailOpenFlag;
static u16 _worldmapnum;
static u8 _mapFlag;
static u8 _wazaFlag;

static void _wazaOshieCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite);
static u16 _wazaOshieWazaNum(tagWINDOW_WORK* w);
static void _menuScriptTokuseiSetumei(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite, CURSOR* c, POKEMON_DATA_dd_* pd);
static WAZAOSHIEDEF* _getWaza2Pointer(long n);
static void _checkWaza2Release(void);
static u16 _checkWaza2(void);
static void _checkWazaRelease(void);
static u16 _checkWaza(long poke);
static u16 _checkWazaSub(Pokemon* p);
static u8 _checkWazaOverlap(u16* arr, u16 id, u16 n);
static bool _checkRelive(Pokemon* p);
static Pokemon* _getPokemonPtr(long n);
static void _getWazaData(u16 id, WAZAOSHIEDEF* out);
static void _menuScriptPdaAddFunc(pdaAddFuncDef f);
static void _menuScriptReadMail(long id);

extern "C" {
void menuScriptSetMailOpen(u8 flag);
void menuScriptSetOpenWorldMapFlag(u8 flag);
}

extern "C" {

void menuScriptReciveMail(void)
{
    _menuScriptWork = 0;
    menuOpenCustom(0x97, windowGetActiveID(), 0, 0, 1, 1, &_menuScriptWork);
    menuCloseCustom(0x97, 0, 1);
}

}

extern "C" {

void menuScriptInfoEsa(void)
{
    _menuScriptWork = 1;
    menuOpenCustom(0x97, windowGetActiveID(), 0, 0, 1, 1, &_menuScriptWork);
    menuCloseCustom(0x97, 0, 1);
    winMsgOpen(3, 0x3E83, 1, 1);
    winMsgClose(1);
}

}

extern "C" {

void menuScriptInfoRelive(Pokemon* p, u8 flag)
{
    u16 dark;
    u16 d2 = pokemonBiosGetDarkpokemonDataId(p);
    dark = d2;
    _menuScriptWork = 2;
    menuOpenCustom(0x97, windowGetActiveID(), 0, 0, 1, 1, &_menuScriptWork);
    menuCloseCustom(0x97, 0, 1);
    if (p) {
        char* nick = pokemonBiosGetNicknamePtr(p);
        msgctrlSetValue(0x32, (u32)nick);
        if (flag) {
            winMsgOpen(3, 0x3E81, 1, 1);
        } else {
            winMsgOpen(3, 0x3E82, 1, 1);
        }
        winMsgClose(1);
        darkPokemonBiosSetInformationFlag(dark, 1);
    }
}

}

static void _menuScriptReadMail(long id)
{
    GSmodelAllPauseAnimation();
    menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    menuOffScreenCheckEnable(1);
    _menuScriptMailID = id;
    GSfloorPush(0x393);
    u32 f = mailGetOpenFlag(id);
    if (f) {
        GSflagSet(f, 1);
    }
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(0.0f / GSgfxVideoGetVsyncRate());
    GSmodelAllUnpauseAnimation();
}

extern "C" {

void menuScriptReadMail(s32 id)
{
    _menuScriptReadMail(id);
}

}

static void _menuScriptPdaAddFunc(pdaAddFuncDef f)
{
    GSmodelAllPauseAnimation();
    menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    menuOffScreenCheckEnable(1);
    _PdaAddFunc = f;
    GSfloorPush(0x38C);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(0.0f / GSgfxVideoGetVsyncRate());
    GSmodelAllUnpauseAnimation();
}

extern "C" {

void menuScriptPdaAddFunc(pdaAddFuncDef f)
{
    _menuScriptPdaAddFunc(f);
}

}

extern "C" {

void menuScriptMailOpenInit(void)
{
    cameraPlayAnime(0x17, 0x17CF1800, 0, 0.0f);
    GSsndPlayNow(0x44F);
    menuOffScreenSetPriority(0);
    menuScriptSetMailOpen(1);
    menuPdaSetModelPointer();
    menuPdaZoomIn();
}

}

extern "C" {

u8 menuScriptCheckMailOpen(void)
{
    return _menuPdaMailOpenFlag;
}

}

extern "C" {

void menuScriptSetMailOpen(u8 flag)
{
    _menuPdaMailOpenFlag = flag;
}

}

extern "C" {

void menuScriptMailOpenMain(void)
{
    GSgfxVideoSetLockFrameRate(0);
    s32 r = menuPdaMailListSortInit(_menuScriptMailID);
    if (r >= 0) {
        menuPdaMailXDScript(r);
    }
    GSgfxVideoSetLockFrameRate(1);
    menuPdaReleaseModelPointer();
    GSmodelAllPauseAnimation();
    menuScriptSetMailOpen(0);
    GSfloorPop();
}

}

extern "C" {

void menuScriptMailOpenExit(void)
{
    menuPdaMailListSortExit();
}

}

extern "C" {

s32 menuScriptEevee(void)
{
    if (GSfloorGetCurrent() != 0x97) {
        u32 place = floorGetPlaceName(0x97);
        msgctrlSetValue(0x31, place);
        winMsgOpen(3, 0xEFF7, 1, 1);
        winMsgClose(1);
        return -1;
    }
    GSfsysReadWait(0x8CA);
    winMsgOpen(3, 0xA0CF, 0, 1);
    s32 ret = menuOpen(0xAF, 1);
    menuClose(0xAF);
    winMsgClose(1);
    menuCloseSync(0xAF, 1);
    GSresFreeGroup(0x8CA);
    return ret;
}

}

extern "C" {

s32 menuScriptTutorial(void)
{
    s32 param = 0;
    if (GSfloorGetCurrent() != 0x8D) {
        u32 place = floorGetPlaceName(0x8D);
        msgctrlSetValue(0x31, place);
        winMsgOpen(3, 0xEFF7, 1, 1);
        winMsgClose(1);
        return -1;
    }
    GSfsysReadWait(0x8D1);
    CURSOR c = cursorBiosGetPos(0xE);
    c.pos = 0;
    c.top = 0;
    cursorBiosSetPos(0xE, c);
    s32 ret = menuOpenCustom(0xB8, windowGetActiveID(), &param, 0, 1, 0);
    if (ret < 0) {
        _tutorialSelect = ret;
    } else {
        fightEncountDataBiosSetDiskId(fightEncountDataBiosGetPtr(0xD), tutorialdata[ret]);
    }
    menuClose(0xB8);
    menuCloseSync(0xB8, 1);
    GSresFreeGroup(0x8D1);
    if (*tutorialdata_number == _tutorialSelect + 1) {
        _tutorialSelect = -1;
    }
    return _tutorialSelect;
}

}

extern "C" {

void menuScriptOpenWorldMap(u16 n)
{
    _worldmapnum = n;
    GSthreadSwitch();
    menuScriptSetOpenWorldMapFlag(1);
    GSfloorPush(0x3A8);
    floorWaitForChange();
}

}

extern "C" {

u16 menuScriptOpenWorldMapGetMapNumber(void)
{
    return _worldmapnum;
}

}

extern "C" {

u8 menuScriptGetOpenWorldMapFlag(void)
{
    return _mapFlag;
}

}

extern "C" {

void menuScriptSetOpenWorldMapFlag(u8 flag)
{
    _mapFlag = flag;
}

}

extern "C" {

void menuScriptUsohachi(void)
{
    GSfsysReadWait(0x923);
    menuOpen(0xD9, 1);
    menuClose(0xD9);
    menuCloseSync(0xD9, 1);
    GSresFreeGroup(0x923);
}

}

extern "C" {

void menuScriptUsohachi2(void)
{
    GSfsysReadWait(0x923);
    menuOpen(0x101, 1);
    menuClose(0x101);
    menuCloseSync(0x101, 1);
    GSresFreeGroup(0x923);
}

}

extern "C" {

s32 menuScriptWazaMeijin(s32 poke)
{
    s32 ret;
    _WazaNum = _checkWaza(poke);
    if (_WazaNum == 0) {
        ret = -1;
    } else {
        ret = menuOpen(0xE4, 1);
        if (ret >= 0) {
            if (_WazaNum == ret + 1) {
                ret = -1;
            } else {
                ret = _wazalist[ret].id;
            }
        }
        menuClose(0xE4);
        menuCloseSync(0xE4, 1);
    }
    _checkWazaRelease();
    return ret;
}

}

extern "C" {

u8 menuScriptWazaBasanCheck(void)
{
    return _wazaFlag;
}

}

extern "C" {

s32 menuScriptWazaBasan(u8* flag)
{
    s32 ret;
    *flag = 0;
    _wazaFlag = 0;
    _WazaNum = _checkWaza2();
    if (_WazaNum == 0) {
        ret = 0;
    } else {
        CURSOR c = cursorBiosGetPos(0xF);
        s32 arg = c.pos;
        ret = menuOpenCustom(0xE5, windowGetActiveID(), &arg, 0, 1, 0);
        if (ret >= 0) {
            if (_WazaNum == ret + 1) {
                ret = -1;
            } else {
                if (_wazalist[ret].flag) {
                    if (flag) {
                        *flag = 1;
                    }
                    _wazaFlag = 1;
                }
                ret = wazaoshie_data[(u16)ret].id;
            }
        }
        menuClose(0xE5);
        menuCloseSync(0xE5, 1);
    }
    _checkWaza2Release();
    return ret;
}

}

extern "C" {

void menuScriptSetWazaOboetaFlag(u16 id)
{
    u16 i;
    for (i = 0; i < *wazaoshie_data_number; i++) {
        WAZAOSHIE_DATA* d = &wazaoshie_data[i];
        if (id == d->id) {
            GSflagOn(d->flag);
        }
    }
}

}

extern "C" {

void menuScriptMoneyOpen(s32 x, s32 y)
{
    menuOpen(0xD8, 0);
    menuSetPosition(0xD8, x, y);
}

}

extern "C" {

void menuScriptMoneyClose(void)
{
    menuClose(0xD8);
}

}

extern "C" {

void menuScriptCouponOpen(s32 x, s32 y)
{
    menuOpen(0x102, 0);
    menuSetPosition(0x102, x, y);
}

}

extern "C" {

void menuScriptCouponClose(void)
{
    menuClose(0x102);
}

}

extern "C" {

s32 menuScriptMoneyDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite)
{
    if (w->menuID == 0xD8) {
        switch (sprite->id) {
        case 0x65B: {
            msgctrlSetValue(0x50, heroGetStatus(0, 0xC, 0));
            s16 rw = GSmsgGetRect(0x434E) >> 16;
            GSmsgPrint2(w->layer, sprite->w - rw, 0, -1, 0x434E);
            break;
        }
        case 0x65A:
            windowDrawSprite2(0, 0, sprite->w, sprite->h, *(u32*)&w->color[0], w, 0x2D3, 0, winSpriteGetLayerID(w, sprite));
            break;
        }
    } else {
        switch (sprite->id) {
        case 0x65B: {
            msgctrlSetValue(0x50, heroGetStatus(0, 0xD, 0));
            s16 rw = GSmsgGetRect(0x434E) >> 16;
            GSmsgPrint2(w->layer, sprite->w - rw, 0, -1, 0x434E);
            break;
        }
        case 0x65A:
            windowDrawSprite2(0, 0, sprite->w, sprite->h, *(u32*)&w->color[0], w, 0x2F9, 0, winSpriteGetLayerID(w, sprite));
            break;
        }
    }
    return 0;
}

}

static void _getWazaData(u16 id, WAZAOSHIEDEF* out)
{
    u8* wd = wazaDataBiosGetPtr(id);
    WAZAOSHIEDEF* o;
    if (out) {
        o = out;
    } else {
        o = &_wazawork;
    }
    o->id = id;
    o->name = wazaDataBiosGetName(wd);
    o->pp = wazaDataBiosGetPp(wd);
    o->type = wazaDataBiosGetZokuseiDataId(wd);
    o->power = wazaDataBiosGetIryoku(wd);
    o->avg = wazaDataBiosGetAvg(wd);
    o->doc = wazaDataBiosGetDoc(wd);
    o->flag = 0;
}

static Pokemon* _getPokemonPtr(long n)
{
    Pokemon* p = heroBiosGetPokemonPtr(savedataGetStatus(0, 2), n);
    if (pokemonCheckValid(p)) {
        return p;
    }
    return 0;
}

static bool _checkRelive(Pokemon* p)
{
    if (!pokemonCheckValid(p)) {
        return 0;
    }
    u16 dark = pokemonBiosGetDarkpokemonDataId(p);
    if (dark != 0) {
        return darkPokemonBiosGetReliveFlag(dark) != 0;
    }
    return 1;
}

static u8 _checkWazaOverlap(u16* arr, u16 id, u16 n)
{
    for (u16 i = 0; i < n; i++) {
        if (id == arr[i]) {
            return 1;
        }
    }
    arr[n] = id;
    return 0;
}

static u16 _checkWazaSub(Pokemon* p)
{
    POKEMON_DATA_dd_* pd = pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(p));
    u16 n = 0;
    memset(_tempwazaid, 0, 0x2A);
    if (pd != 0) {
        for (u16 i = 0; i < 20; i++) {
            u8 lv = pokemonDataBiosGetGetWazaLevel(pd, i);
            if (lv == 0) {
                break;
            }
            if (pokemonBiosGetLevel(p) >= lv) {
                if (!_checkWazaOverlap(_tempwazaid, pokemonDataBiosGetGetWazaDataId(pd, i), n)) {

                    n++;
                }
            }
        }
    }
    return n;
}

static u16 _checkWaza(long poke)
{
    u16 count = 0;
    Pokemon* p = _getPokemonPtr(poke);
    if (p != 0 && _checkRelive(p)) {
        count = _checkWazaSub(p);
    }
    if (count != 0) {
        count++;
        _wazalist = new WAZAOSHIEDEF[count];
        u16 j;
        for (j = 0; j < count - 1; j++) {
            _getWazaData(_tempwazaid[j], &_wazalist[j]);
        }
        _wazalist[j].id = 0;
    }
    return count;
}

static void _checkWazaRelease(void)
{
    if (_wazalist != 0) {
        delete[] _wazalist;
        _wazalist = 0;
    }
}

static u16 _checkWaza2(void)
{
    int i;
    u16 count = 0;
    u16 done = 0;
    u16* ids = new u16[*wazaoshie_data_number];
    bool* flags = new bool[*wazaoshie_data_number];
    for (i = 0; i < *wazaoshie_data_number; i++) {
        u32 mission = wazaoshie_data[i].mission;
        if (GSflagGet(0x3C4) >= flag_etc[mission].value) {
            u16 idx = count;
            ids[idx] = wazaoshie_data[i].id;
            flags[idx] = GSflagTest(wazaoshie_data[i].flag);
            if (flags[idx]) {
                done++;
            }
            count++;
        }
    }
    if (done == count) {
        count = 0;
    } else if (count != 0) {
        count++;
        _wazalist = new WAZAOSHIEDEF[count];
        bool* fp = flags;
        u16* ip = ids;
        int last = count - 1;
        int j;
        for (j = 0; j < last; j++, ip++, fp++) {
            _getWazaData(*ip, &_wazalist[j]);
            _wazalist[j].flag = *fp;
        }
        _wazalist[j].id = 0;
    }
    delete[] ids;
    delete[] flags;
    return count;
}

static void _checkWaza2Release(void)
{
    if (_wazalist != 0) {
        delete[] _wazalist;
        _wazalist = 0;
    }
}

static WAZAOSHIEDEF* _getWaza2Pointer(long n)
{
    if (_wazalist == 0) {
        return 0;
    }
    return _wazalist + n;
}

extern "C" {

void menuScriptEeveeCtrl(tagWINDOW_WORK* w)
{
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x24);
            w->seqSet = 1;
            switch (w->menuID) {
            case 0xAF:
                menuSetStatus(w->menuID, 8);
                break;
            case 0xD9:
                break;
            }
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

}

static void _menuScriptTokuseiSetumei(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite, CURSOR* c, POKEMON_DATA_dd_* pd)
{
    u8 second;
    int n2;
    int n1;
    volatile MenuItem* item = menuItemBiosGetPtr(0xAF, sprite->id);
    u8 tid = pokemonDataBiosGetTokuseiDataId(pd, 0);
    if (tid != 0) {
        u32 k;
        u16* text = (u16*)GSmsgGetGSchar(pokemonTokuseiDataBiosGetDoc(pokemonTokuseiDataBiosGetPtr(tid)));
        u32 len = GSmsgGetCharLength(text);
        u16* buf1 = new u16[len + 2];
        u16* buf2 = new u16[len + 2];
        u16* name = buf1;
        int n = 0;
        int best = 0;
        u8 wrap = 0;
        do {
            int spaces = 0;
            int prev = n;
            u16* src = text;
            u16* dst = buf1;
            k = 0;
            n++;
            for (;;) {
                u16 ch = *src;
                if (ch == 0x20 || ch == 0x3000) {
                    if (spaces == prev) {
                        break;
                    }
                    *dst = ch;
                    spaces++;
                } else {
                    if (ch == 0) {
                        break;
                    }
                    *dst = ch;
                }
                src++;
                dst++;
                k++;
            }
            buf1[k++] = 0;
            msgctrlSetValue(0x37, (u32)name);
            u32 width = GSmsgGetRect(0x4276) >> 16;
            if (width <= item->w) {
                best = n;
            }
            if (!(item->w >= width)) {
                wrap = 1;
            }
        } while (k < len);
        if (wrap) {
            u16* p = text;
            n1 = 0;
            n2 = 0;
            second = 0;
            u32 total = GSmsgGetCharLength(text);
            u32 idx = 0;
            int spaces = 0;
            for (;; p++, idx++) {
                u16 ch = *p;
                if (ch == 0xFFFF) {
                    continue;
                }
                if (ch == 0x20 || ch == 0x3000) {
                    if (spaces == best - 1) {
                        second = 1;
                    } else if (second) {
                        buf2[n2++] = ch;
                    } else {
                        buf1[n1++] = ch;
                    }
                    spaces++;
                    continue;
                }
                if (ch == 0) {
                    if (total <= idx) {
                        break;
                    }
                } else if (second) {
                    buf2[n2++] = ch;
                } else {
                    buf1[n1++] = ch;
                }
            }
            buf1[n1] = 0;
            buf2[n2] = 0;
            msgctrlSetValue(0x37, (u32)buf1);
            GSmsgPrint2(w->layer, 0, 0, w->alpha | 0xFFFFFF00, 0x4276);
            msgctrlSetValue(0x37, (u32)buf2);
            GSmsgPrint2(w->layer, 0, 0x12, w->alpha | 0xFFFFFF00, 0x4276);
        } else {
            msgctrlSetValue(0x37, (u32)text);
            GSmsgPrint2(w->layer, 0, 0, w->alpha | 0xFFFFFF00, 0x4276);
        }
        delete[] buf1;
        delete[] buf2;
    }
}

extern "C" {

void menuUsohachiHook(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite)
{
    switch (sprite->id) {
    case 0x661:
        if (w->menuID == 0xD9) {
            windowDrawSprite(0, 0, w, 0x2D8, 0, winSpriteGetLayerID(w, sprite));
        } else {
            windowDrawSprite(0, 0, w, 0x341, 0, winSpriteGetLayerID(w, sprite));
        }
        break;
    }
}

}

extern "C" {

void fn_8005DE84(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite)
{
    const u16 ids[5] = { 0x4EF, 0x4F2, 0x4F3, 0x4F4, 0x4F5 };
    const s32 msgs[5] = { 0x13D6, 0x13D5, 0x13D4, 0x1492, 0x1491 };
    s16 i;
    for (i = 0; i < 5; i++) {
        if ((u16)sprite->id == ids[i]) {
            char* str = GSmsgGetGSchar(msgs[i]);
            msgctrlSetValue(0x37, (u32)str);
            GSmsgPrint2(winSpriteGetLayerID(w, sprite), 0, 0, w->alpha | 0xFFFFFF00, 0x4277);
            break;
        }
    }
}

}

extern "C" {

void menuScriptEeveeHook(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite)
{
    const u16 pokeIds[5] = { 0x86, 0x87, 0x88, 0xC5, 0xC4 };
    CURSOR c = *(CURSOR*)&w->top;
    POKEMON_DATA_dd_* pd = pokemonDataBiosGetPtr(pokeIds[c.pos]);
    switch (sprite->id) {
    case 0x4EE:
        if (c.pos >= 3) {
            winSpriteSetDisp(sprite, 1);
            u16 m = (c.pos == 3) ? 0x205 : 0x204;
            msgctrlSetValue(0x2D, m);
            msgctrlSetValue(0x4E, 0x85);
            sprite->msgID = 0xA0D4;
        } else {
            winSpriteSetDisp(sprite, 0);
            sprite->msgID = 0;
        }
        break;
    case 0x4E8: case 0x4E9: case 0x4EA:
        if (c.pos >= 3) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x4EB: {
        const u16 sprIds[5] = { 0x220, 0x21E, 0x21F, 0x21C, 0x21D };
        windowDrawSprite(0, 0, w, sprIds[c.pos], 0, winSpriteGetLayerID(w, sprite));
        break;
    }
    case 0x4FF:
        _menuScriptTokuseiSetumei(w, sprite, &c, pd);
        break;
    case 0x4FE: {
        u8 tid = pokemonDataBiosGetTokuseiDataId(pd, 0);
        if (tid != 0) {
            char* str = GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(tid)));
            msgctrlSetValue(0x37, (u32)str);
            GSmsgPrint2(w->layer, 0, 0, w->alpha | 0xFFFFFF00, 0x4276);
        }
        break;
    }
    case 0x4F0:
        sprite->r = 0xD5;
        sprite->g = 0xAA;
        sprite->b = 0x33;
        break;
    case 0x4F1:
        char* str = GSmsgGetGSchar((u32)pokemonDataBiosGetName(pd));
        msgctrlSetValue(0x37, (u32)str);
        GSmsgPrint2(w->layer, 0, 0, w->alpha | 0xFFFFFF00, 0x4276);
        break;
    case 0x4EC: case 0x4FA: case 0x4FB: case 0x4FC: case 0x4FD: {
        const s32 ids[5] = { 0x4EC, 0x4FA, 0x4FB, 0x4FC, 0x4FD };
        s16 i;
        for (i = 0; i < 5; i++) {
            if (sprite->id == ids[i]) {
                break;
            }
        }
        if (i == c.pos) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x4E7:
        windowDrawSprite(0, 0, w, zokuseiGetPokemonSpriteID(pd, 0), 0, w->layer);
        break;
    case 0x4EF: case 0x4F2: case 0x4F3: case 0x4F4: case 0x4F5:
        fn_8005DE84(w, sprite);
        break;
    }
}

}

extern "C" {

void menuScriptTutorialCtrl(tagWINDOW_WORK* w)
{
    menuDataBiosGetPtr(w->menuID);
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

}

extern "C" {

void menuScriptTutorialCursor(tagWINDOW_WORK* w)
{
    windowGetKeyInfo();
    s32 total = *tutorialdata_number;
    int vis = 8;
    if (total < 8) {
        vis = total;
    }
    u32 rep = windowGetKeyRepeat();
    CURSOR c = cursorBiosGetPos(0xE);
    if (vis != 0) {
        if ((u16)rep & 1) {
            c.pos--;
        } else if ((u16)rep & 2) {
            c.pos++;
        }
        if (c.pos < 0) {
            c.top += c.pos;
            c.pos = 0;
            if (c.top < 0) {
                c.top = 0;
                c.pos = 0;
            }
        } else if (c.pos >= vis) {
            c.top += c.pos - (vis - 1);
            c.pos = (s8)(vis - 1);
            if (c.top + c.pos >= total) {
                c.pos = (s8)(vis - 1);
                c.top = (s8)(total - vis);
            }
        }
    }
    if (c.pos == (s8)(*tutorialdata_number - 1)) {
        _tutorialSelect = -1;
    } else {
        _tutorialSelect = c.pos + c.top;
    }
    w->top = c.top;
    w->cursor = c.pos;
    cursorBiosSetPos(0xE, c);
}

}

extern "C" {

void menuScriptUsohachiCtrl(tagWINDOW_WORK* w)
{
    menuScriptEeveeCtrl(w);
}

}

extern "C" {

void menuScriptWazaOshieCtrl(tagWINDOW_WORK* w)
{
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x24);
            w->seqSet = 1;
            if (w->menuID == 0xE5) {
                CURSOR c = cursorBiosGetPos(0xF);
                w->top = c.top;
                w->cursor = c.pos;
            }
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

}

static u16 _wazaOshieWazaNum(tagWINDOW_WORK* w)
{
    if (w->menuID == 0xE4) {
        return _WazaNum;
    }
    return _WazaNum;
}

static void _wazaOshieCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite)
{
    CURSOR c = *(CURSOR*)&w->top;
    const s32 ids[9] = { 0x6BB, 0x6BC, 0x6BD, 0x6BE, 0x6BF, 0x6C0, 0x6C1, 0x6C2, 0x6C3 };
    int i;
    for (i = 0; i < 9; i++) {
        if (sprite->id == ids[i]) {
            break;
        }
    }
    if (i == c.pos) {
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}

extern "C" {

void menuScriptWazaOshieHook(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite)
{
    CURSOR c = *(CURSOR*)&w->top;
    u16 n = _wazaOshieWazaNum(w);
    volatile WAZAOSHIEDEF* waza = _getWaza2Pointer(c.pos + c.top);
    int layer = winSpriteGetLayerID(w, sprite);
    u32 color = w->alpha | 0xFFFFFF00;
    switch (sprite->id) {
    case 0x6BB: case 0x6BC: case 0x6BD: case 0x6BE: case 0x6BF: case 0x6C0: case 0x6C1: case 0x6C2: case 0x6C3:
        _wazaOshieCursor(w, sprite);
        break;
    case 0x6B6: case 0x6B7: case 0x6B8:
        if (w->menuID == 0xE4) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x6B9:
        menuPdaSubCheckUpDownCursor(w, sprite, &c.top, n, 9, 0);
        break;
    case 0x6BA:
        menuPdaSubCheckUpDownCursor(w, sprite, &c.top, n, 9, 1);
        break;
    case 0x6D5:
        if (n != 0) {
            MenuItem* a = menuItemBiosGetPtr(w->menuID, 0x6D5);
            MenuItem* b = menuItemBiosGetPtr(w->menuID, sprite->id);
            spriteSetScissor(layer, a->x - b->x, a->y - b->y, a->w, a->h);
            s16 y = -c.top * 0x1F;
            for (u16 i = 0; i < n; y += 0x1F, i++) {
                if (i >= c.top - 1 && i < c.top + 10) {
                    WAZAOSHIEDEF* p = _getWaza2Pointer(i);
                    if (p->id != 0) {
                        GSmsgPrint2(layer, 0, y, color, p->name);
                        if (w->menuID == 0xE4) {
                            msgctrlSetValue(0x50, 1000);
                            u32 r = GSmsgGetRect(0x4359);
                            GSmsgPrint2(layer, sprite->w - (r >> 16), (u8)y, color, 0x4359);
                        } else if (p->flag) {
                            MenuSpriteVal* v = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x241));
                            windowDrawSprite(b->w - v->x, y + (0x12 - v->w) / 2, w, 0x241, 0, layer);
                        }
                    } else if (w->menuID == 0xE4) {
                        GSmsgPrint2(layer, 0, y, color, 0x4295);
                    } else {
                        GSmsgPrint2(layer, 0, y, color, 0xC753);
                    }
                }
            }
            spriteClearScissor(layer);
        }
        break;
    case 0x6D4:
        if (waza) {
            if (waza->id != 0) {
                GSmsgPrint2(layer, 0, 0, color, waza->doc);
            } else if (w->menuID == 0xE4) {
                GSmsgPrint2(layer, 0, 0, color, 0xC6DA);
            } else {
                GSmsgPrint2(layer, 0, 0, color, 0xC73B);
            }
        }
        break;
    case 0x6D6:
        if (w->menuID == 0xE4) {
            msgctrlSetValue(0x50, heroBiosGetPokecoupon(savedataGetStatus(0, 2)));
            u32 r = GSmsgGetRect(0x434E);
            GSmsgPrint2(layer, sprite->w - (r >> 16), 0, color, 0x434E);
        }
        break;
    case 0x6CF:
        if (waza && waza->id) {
            msgctrlSetValue(0x5F, waza->pp);
            GSmsgPrintRect(layer, 0, 0, sprite->w, sprite->h, color, 0x4287);
        }
        break;
    case 0x6CD:
        if (waza && waza->id) {
            if (waza->avg <= 1) {
                GSmsgPrintRight(layer, 0, 0, sprite->w, sprite->h, color, 0x3AF6);
            } else {
                msgctrlSetValue(0x34, waza->avg);
                GSmsgPrintRect(layer, 0, 0, sprite->w, sprite->h, color, 0x4287);
            }
        }
        break;
    case 0x6CE:
        if (waza && waza->id) {
            if (waza->power <= 1) {
                GSmsgPrintRight(layer, 0, 0, sprite->w, sprite->h, color, 0x3AF6);
            } else {
                msgctrlSetValue(0x34, waza->power);
                GSmsgPrintRect(layer, 0, 0, sprite->w, sprite->h, color, 0x4287);
            }
        }
        break;
    case 0x6B5:
        if (waza && waza->id) {
            MenuItem* it = menuItemBiosGetPtr(w->menuID, 0x6B5);
            windowDrawSprite2(0, 0, it->w, it->h, color, w, zokuseiBiosGetSpriteID(waza->type), 0, layer);
        }
        break;
    }
}

}

extern "C" {

s32 menuScriptWazaOshieCursor(tagWINDOW_WORK* w)
{
    windowGetKeyInfo();
    u32 rep = windowGetKeyRepeat();
    CURSOR c = *(CURSOR*)&w->top;
    int n = _wazaOshieWazaNum(w);
    int vis = 9;
    if (n < 9) {
        vis = n;
    }
    if (vis != 0) {
        if ((u16)rep & 1) {
            c.pos--;
        } else if ((u16)rep & 2) {
            c.pos++;
        }
        if (c.pos < 0) {
            c.top += c.pos;
            c.pos = 0;
            if (c.top < 0) {
                c.top = 0;
                c.pos = 0;
            }
        } else if (c.pos >= vis) {
            c.top += c.pos - (vis - 1);
            c.pos = (s8)(vis - 1);
            if (c.top + c.pos >= n) {
                c.pos = (s8)(vis - 1);
                c.top = (s8)(n - vis);
            }
        }
    }
    w->top = c.top;
    w->cursor = c.pos;
    if (w->menuID == 0xE5) {
        cursorBiosSetPos(0xF, c);
    }
    return 0;
}

}

extern "C" {

void menuScriptTutorialHook(tagWINDOW_WORK* w, tagSPRITE_WORK* sprite)
{
    CURSOR c = cursorBiosGetPos(0xE);
    switch (sprite->id) {
    case 0x7E6: case 0x7E7: case 0x7E8: case 0x7E9: case 0x7EA: case 0x7EB: case 0x7EC: case 0x7ED: {
        const s32 ids[8] = { 0x7E6, 0x7E7, 0x7E8, 0x7E9, 0x7EA, 0x7EB, 0x7EC, 0x7ED };
        s16 i;
        for (i = 0; i < 8; i++) {
            if (sprite->id == ids[i]) {
                break;
            }
        }
        if (*tutorialdata_number > i) {
            u16 id = tutorialdata[i + c.top];
            sprite->msgID = id != 0 ? deckDataVirtualDB_GetTitle(id) : 0xDECE;
        } else {
            sprite->msgID = 0;
        }
        break;
    }
    case 0x7CF: case 0x7D1: case 0x7D3: case 0x7D5: case 0x7D7: case 0x7D9: case 0x7DB: case 0x7DD: {
        const s32 ids[8] = { 0x7CF, 0x7D1, 0x7D3, 0x7D5, 0x7D7, 0x7D9, 0x7DB, 0x7DD };
        s16 i;
        for (i = 0; i < 8; i++) {
            if (sprite->id == ids[i]) {
                break;
            }
        }
        if (i == c.pos) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x7CE: case 0x7D0: case 0x7D2: case 0x7D4: case 0x7D6: case 0x7D8: case 0x7DA: case 0x7DC: {
        const s32 ids[8] = { 0x7CE, 0x7D0, 0x7D2, 0x7D4, 0x7D6, 0x7D8, 0x7DA, 0x7DC };
        s16 i;
        for (i = 0; i < 8; i++) {
            if (sprite->id == ids[i]) {
                break;
            }
        }
        if (i == c.pos) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x7DE: case 0x7DF: case 0x7E0: case 0x7E1: case 0x7E2: case 0x7E3: case 0x7E4: case 0x7E5: {
        const s32 ids[8] = { 0x7DE, 0x7DF, 0x7E0, 0x7E1, 0x7E2, 0x7E3, 0x7E4, 0x7E5 };
        s16 i;
        for (i = 0; i < 8; i++) {
            if (sprite->id == ids[i]) {
                break;
            }
        }
        u16 id = tutorialdata[i + c.top];
        u32 flag;
        if (id != 0) {
            flag = deckDataVirtualDB_GetFlag(id);
        } else {
            flag = 0;
        }
        if (GSflagTest(flag) && flag) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x7EE: {
        u16 id = tutorialdata[c.pos + c.top];
        sprite->msgID = id != 0 ? deckDataVirtualDB_GetExplanetion2(id) : 0;
        break;
    }
    case 0x7F0:
        menuPdaSubCheckUpDownCursor(w, sprite, &c.top, *tutorialdata_number, 8, 0);
        break;
    case 0x7F1:
        menuPdaSubCheckUpDownCursor(w, sprite, &c.top, *tutorialdata_number, 8, 1);
        break;
    }
}

}

extern "C" {

void menuScriptPdaAddFuncInit(void)
{
    GSsndPlayNow(0x454);
    cameraPlayAnime(0x17, 0x17CF1800, 0, 0.0f);
    menuPdaModelVisibility(0x17CF1000, 0);
}

}

extern "C" {

void menuScriptPdaAddFuncMain(void)
{
    GSgfxVideoSetLockFrameRate(0);
    menuOffScreenSetPriority(0);
    menuPdaSetModelPointer();
    menuPdaModelVisibility(0x17CF1000, 1);
    menuPdaAddFunc();
    menuPdaScript(_PdaAddFunc);
    GSgfxVideoSetLockFrameRate(1);
    menuPdaReleaseModelPointer();
    GSmodelAllPauseAnimation();
    GSfloorPop();
}

}

extern "C" {

void menuScriptPdaAddFuncExit(void)
{
}

}
