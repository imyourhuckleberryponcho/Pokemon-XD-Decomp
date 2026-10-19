// STATUS: 22/31 functions exact (3160 bytes). Needs extra_cflags=["-inline noauto,deferred"]
// (source is written bottom-to-top; LAYOUT of .text and .data tables confirms it).
// Not exact: Button 99.2% (grid index add order), Sub 99.2% (wazaGetStatus arg shuffle), ChangeSubMenu 99.1%
// (id/i register swap), Cursor 94.7% (registers in ribbon grid navigation), DrawRibbon 93.9% (n=idx%9 hoist),
// MakeRibbon 82.6% (target keeps loop guards "li r3,0; cmpwi r3,9; bge" around unrolled clears),
// DrawWaza/DrawStatus/DrawTitle are EMPTY STUBS (not reconstructed, 4084/3220/2048 bytes).
// Pokemon summary screen (menuPokemonStatus).
#include <dolphin/types.h>

// Menu files were built without the peephole optimizer.
#pragma peephole off

struct CURSOR {
    s16 top;
    s16 pos;
};

struct FIGHT_TRAINER;
struct tagSPRITE_WORK {
    u8 pad0[6];
    s16 itemId;
    u8 pad8[0x44];
    s32 msgId;
    u8 pad4C[4];
    s16 w;
    s16 h;
    u8 pad58[0xC];
    u32 color;
};

enum MENU_POKEMON_CB_TYPE { MENU_POKEMON_CB_TYPE_0 };

class DarkPokemon {
public:
    bool isWazaNew(u8) const;
    void setWazaNew(u8, bool);
};

class Pokemon {
public:
    bool isDarkPokemon() const;
    DarkPokemon* getDarkPokemon();
};

typedef Pokemon* (*MenuPokemonCB)(Pokemon*, MENU_POKEMON_CB_TYPE, long);

struct tagWINDOW_WORK {
    u8 pad0[1];
    s8 state;
    u8 pad2[2];
    s32 menuId;
    u8 pad8[0x8B];
    u8 alpha;
    u8 pad94[8];
    CURSOR cursor;
    u8 padA0[2];
    s16 selOld;
    u8 padA4[2];
};

struct RIBBON_WORK {
    s32 count;
    s8 grid[9][4];
};

struct MenuStatus {
    u8 flags;
    u8 state;
    s8 cursor;
    s8 f3;
    s32 result;
    FIGHT_TRAINER* trainer;
    Pokemon* pokemon;
    MenuPokemonCB cb;
    long cbArg;
    u16 sel;
    s8 f1a;
    u8 pad1b[1];
    RIBBON_WORK ribbon;
    u8 dark[4];
};

struct MenuItemInfo {
    u8 pad0[6];
    s16 x6;
    s16 x8;
    s16 a;
    s16 b;
};

struct MENU_MODEL {
    MENU_MODEL() {}
    u8 unk0[0xEC];
};

extern "C" {
bool menuIsCheck(s32);
void menuSetDisp(s32, s32);
s32 menuOpen(s32, s32);
void menuClose(s32);
s32 menuOpenCustom(s32, ...);
void menuCloseCustom(s32, s32, s32);
void menuDrawReliveUpdate(void);
MenuItemInfo* menuItemBiosGetPtr(s32, s32);
void menuModelInit(MENU_MODEL*, s32, s32);
void menuModelFree(MENU_MODEL*);
void menuModelTerm(MENU_MODEL*);
void menuModelLoadPokemon(MENU_MODEL*, Pokemon*);
bool menuFaceCheckLoading(void);
void menuOffScreenSetPriority(s32);
void fadeCheck(s32);
void fadeSet(s32, f32);
void GSthreadSwitch(void);
void GSsndPlayNow(u32);
void GSfloorPush(s32);
void GSfloorPop(void);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s32 wazaGetStatus(void*, u16, s32, s32);
s32 pokemonGetStatus(Pokemon*, s32, s32, u16);
void* savedataGetStatus(s32, s32);
void* heroBiosGetPokemonPtr(void*, s32);
bool pokemonCheckValid(void*);
void* memset(void*, int, u32);
u8 gamedataGetStatus(s32, s32);
u32 GSflagGet(s32);
FIGHT_TRAINER* fightFloorGetGcHeroFightTrainerPtr(s32);
void* fightTrainerBiosGetHeroPtr(FIGHT_TRAINER*);
void* menuCBBios_GetRegisteredHero(void);
char* heroBiosGetNamePtr(void*);
u32 heroBiosGetRnd(void*);
s32 GScharCmp(const char*, const char*);
char* GSmsgGetGSchar(u32);
s32 zokuseiBiosGetSpriteID(u16);
u16 windowGetKeyTrg(void);
u32 windowGetKeyRepeat(void);
void menuPlaySe(s32, s32);
bool menuModelComparePokemon(MENU_MODEL*, Pokemon*);
void pokemonWazaReplace(Pokemon*, s32, s32);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
void* windowSearchID(s32);
void msgctrlSetValue(s32, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, s32);
void windowDrawSprite(s16, s16, tagWINDOW_WORK*, s32, s32, s32);
u32 getRibbonCnt(void);
s32 getRibbonMsgID(s32);
u8 exribbonGetNo(s32);
u8 pokemonWazaCheckValid(Pokemon*, u16);
u32 GSmsgGetRect(u32);
s32 GSmsgPrint2(s32, s32, s32, u32, u32);
u32 mballBiosGetSpriteID(u16);
void menuModelAdjustCamera(MENU_MODEL*);
u8 menuModelCheck(MENU_MODEL*, s32);
void menuModelRender(MENU_MODEL*);
void menuModelSetAngle(MENU_MODEL*, f32*);
void menuModelSetSize(MENU_MODEL*, s16, s16, s16, s16);
s32 menuPokemonGetJoutaiSpriteID(Pokemon*, s32);
s32 menuSubGetPokemonSexForDisp(Pokemon*);
u8 pokemonBiosGetCatchBallId(Pokemon*);
u8 pokemonCheckRare(Pokemon*);
void* pokemonDataBiosGetPtr(u16);
u16 pokemonGetSoubiItemDataId(Pokemon*);
u8 pokemonIsDarkPokemon(Pokemon*);
u32 zokuseiGetPokemonSpriteID(void*, s32);
u32 pokemonDataBiosGetZokuseiDataId(void*, u16);
u8 pokemonGetDarkPokemonLevel(Pokemon*);
void* pokemonSeikakuDataBiosGetPtr(u32);
u32 pokemonSeikakuDataBiosGetName(void*);
u32 floorGetPlaceName(u32);
u8 fightKind_CheckFightKind(u8);
u32 pokemonGetLevelToExp(Pokemon*, u8);
u32 pokemonGetTokuseiDataId(Pokemon*);
u32 pokemonTokuseiDataBiosGetPtr(u16);
u32 pokemonTokuseiDataBiosGetName(u32);
u32 pokemonTokuseiDataBiosGetDoc(u32);
void menuDrawReliveMeter(Pokemon*, s32, s32, s32);
u32 zokuseiGetPokemonSpriteID(void*, s32);
u32 pokemonDataBiosGetZokuseiDataId(void*, u16);
u8 pokemonGetDarkPokemonLevel(Pokemon*);
void* pokemonSeikakuDataBiosGetPtr(u32);
u32 pokemonSeikakuDataBiosGetName(void*);
u32 floorGetPlaceName(u32);
u8 fightKind_CheckFightKind(u8);
u32 pokemonGetLevelToExp(Pokemon*, u8);
u32 pokemonGetTokuseiDataId(Pokemon*);
u32 pokemonTokuseiDataBiosGetPtr(u16);
u32 pokemonTokuseiDataBiosGetName(u32);
u32 pokemonTokuseiDataBiosGetDoc(u32);
void menuDrawReliveMeter(Pokemon*, s32, s32, s32);
u32 zokuseiGetPokemonSpriteID(void*, s32);
u32 pokemonDataBiosGetZokuseiDataId(void*, u16);
u8 pokemonGetDarkPokemonLevel(Pokemon*);
void* pokemonSeikakuDataBiosGetPtr(u32);
u32 pokemonSeikakuDataBiosGetName(void*);
u32 floorGetPlaceName(u32);
u8 fightKind_CheckFightKind(u8);
u32 pokemonGetLevelToExp(Pokemon*, u8);
u32 pokemonGetTokuseiDataId(Pokemon*);
u32 pokemonTokuseiDataBiosGetPtr(u16);
u32 pokemonTokuseiDataBiosGetName(u32);
u32 pokemonTokuseiDataBiosGetDoc(u32);
void menuDrawReliveMeter(Pokemon*, s32, s32, s32);
u16 zokuseiBiosGetWazaJoutai(u16, u16);
u8 wazaDB_GetCompatible(u16);
u8 pokemonWazaGetMaxPP(Pokemon*, u16);
void GSmsgPrintRight(s32, s32, s32, s32, s32, u32, s32);
void windowDrawSprite2(s32, s32, s32, s32, u32, tagWINDOW_WORK*, u32, u32, s32);
}

s32 _menuPokemonStatusCheckWazaItem(tagWINDOW_WORK*, tagSPRITE_WORK*);
s32 _menuPokemonStatusCheckWazaItem(tagWINDOW_WORK*, tagSPRITE_WORK*);
static MenuStatus _menuStatus;
static MENU_MODEL _menuModel;


static s32 ribbon_id_tbl[32] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6,
};

static s32 ex_ribbon_id[64] = {
    0x2B12, 0x2B13, 0x2B14, 0x2B15, 0x2B16, 0x2B17, 0x2B18, 0x2B19,
    0x2B1A, 0x2B1B, 0x2B1C, 0x2B1D, 0x2B1E, 0x2B1F, 0x2B20, 0x2B21,
    0x2B22, 0x2B23, 0x2B24, 0x2B25, 0x2B26, 0x2B27, 0x2B28, 0x2B29,
    0x2B2A, 0x2B2B, 0x2B2C, 0x2B2D, 0x2B2E, 0x2B2F, 0x2B30, 0x2B31,
    0x2B32, 0x2B33, 0x2B34, 0x2B35, 0x2B36, 0x2B37, 0x2B38, 0x2B39,
    0x2B3A, 0x2B3B, 0x2B3C, 0x2B3D, 0x2B3E, 0x2B3F, 0x2B40, 0x2B41,
    0x2B42, 0x2B43, 0x2B44, 0x2B45, 0x2B46, 0x2B47, 0x2B48, 0x2B49,
    0x2B4A, 0x2B4B, 0x2B4C, 0x2B4D, 0x2B4E, 0x2B4F, 0x2B50, 0x2B51,
};

struct RibbonMap {
    u16 id;
    u8 start;
    u8 max;
};

// Forward declarations (the file is written bottom-to-top: -inline noauto,deferred).
extern "C" {
void menuPokemonStatusClose(void);
}
u16 _menuPokemonStatusGetWazaDataID(Pokemon*, u16);
void _menuPokemonStatusMakeRibbon(Pokemon*, RIBBON_WORK*);
static s32 _menuPokemonStatusChangeSubMenu(CURSOR cursor);
static s32 _menuPokemonStatusSub(u8, FIGHT_TRAINER*, Pokemon*, u16, MenuPokemonCB, long);
static s32 _menuPokemonStatusOpen(u8, FIGHT_TRAINER*, Pokemon*, u16, MenuPokemonCB, long);

extern "C" {
s32 menuPokemonStatusOpenFieldMenu(Pokemon* pokemon, MenuPokemonCB cb, long arg) {
    return _menuPokemonStatusOpen(0x8E, 0, pokemon, 0, cb, arg);
}
}

extern "C" {
s32 menuPokemonStatusOpenFightMenu(FIGHT_TRAINER* trainer, Pokemon* pokemon, MenuPokemonCB cb, long arg) {
    return _menuPokemonStatusOpen(0xAC, trainer, pokemon, 0, cb, arg);
}
}

extern "C" {
s32 menuPokemonStatusOpenFromPcBox(Pokemon* pokemon, MenuPokemonCB cb, long arg) {
    return _menuPokemonStatusOpen(0xE, 0, pokemon, 0, cb, arg);
}
}

extern "C" {
s32 menuPokemonStatusOpenFromPokemonChange(Pokemon* pokemon, MenuPokemonCB cb, long arg) {
    return _menuPokemonStatusOpen(0xC, 0, pokemon, 0, cb, arg);
}
}

extern "C" {
s32 menuPokemonStatusOpenWazaList(u8 index) {
    Pokemon* pokemon = 0;
    if (index < 6) {
        void* save = savedataGetStatus(0, 2);
        if (save) {
            pokemon = (Pokemon*)heroBiosGetPokemonPtr(save, index);
            if (!pokemonCheckValid(pokemon)) {
                pokemon = 0;
            }
        }
    }
    return pokemon == 0 ? -1 : _menuPokemonStatusOpen(0x11, 0, pokemon, 0, 0, 0);
}
}

extern "C" {
s32 menuPokemonStatusOpenWazaMachine(Pokemon* pokemon, u16 sel) {
    return _menuPokemonStatusOpen(0x58, 0, pokemon, sel, 0, 0);
}
}

extern "C" {
s32 menuPokemonStatusOpenWazaLearn(Pokemon* pokemon, u16 sel) {
    int ids[4] = { 0x37, 0x40, 0x38, 0x41 };
    s32 result;
    int i;
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 0);
        }
    }
    result = _menuPokemonStatusOpen(0x59, 0, pokemon, sel, 0, 0);
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 1);
        }
    }
    return result;
}
}

extern "C" {
s32 menuPokemonStatusOpenWazaLearnList(Pokemon* pokemon, u16 sel) {
    int ids[4] = { 0x37, 0x40, 0x38, 0x41 };
    s32 result;
    int i;
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 0);
        }
    }
    result = _menuPokemonStatusOpen(0x19, 0, pokemon, sel, 0, 0);
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 1);
        }
    }
    return result;
}
}

extern "C" {
s32 menuPokemonStatus(void) {
    return _menuStatus.result = _menuPokemonStatusSub(_menuStatus.flags, _menuStatus.trainer, _menuStatus.pokemon, _menuStatus.sel, _menuStatus.cb, _menuStatus.cbArg);
}
}

extern "C" {
void menuPokemonStatusClose(void) {
    if ((_menuStatus.flags & 1) && !(_menuStatus.flags & 8)) {
        fadeCheck(1);
        fadeSet(3, 0.5f);
        fadeCheck(1);
    }
    if (menuIsCheck(0x5F)) {
        menuCloseCustom(0x5F, 0, 0);
    }
    if (menuIsCheck(0x60)) {
        menuCloseCustom(0x60, 0, 0);
    }
    if (menuIsCheck(0x62)) {
        menuCloseCustom(0x62, 0, 0);
    }
    if (menuIsCheck(0x63)) {
        menuCloseCustom(0x63, 0, 0);
    }
    menuCloseCustom(0x5E, 0, 1);
    if (_menuStatus.flags & 1) {
        GSfloorPop();
        if (_menuStatus.flags & 8) {
            floorSetFadeScript(0, 0);
        }
    }
}
}

static s32 _menuPokemonStatusOpen(u8 flags, FIGHT_TRAINER* trainer, Pokemon* pokemon, u16 sel, MenuPokemonCB cb, long arg) {
    while (menuFaceCheckLoading()) {
        GSthreadSwitch();
    }
    memset(&_menuStatus, 0, sizeof(_menuStatus));
    MenuStatus* st = &_menuStatus;
    st->flags = flags;
    st->trainer = trainer;
    st->pokemon = pokemon;
    st->sel = sel;
    st->cb = cb;
    st->cbArg = arg;
    st->result = -1;
    u8* slot = (u8*)st;
    for (int i = 0; i < 4; slot++, i++) {
        slot[0x44] = 0;
        if (pokemon->isDarkPokemon()) {
            DarkPokemon* dp = pokemon->getDarkPokemon();
            if (dp) {
                sel = pokemonGetStatus(pokemon, 0, 0x7F, (u8)i);
                switch (sel) {
                case 0:
                case 0x164:
                case 0x165:
                case 0x166:
                case 0x167:
                case 0x168:
                case 0x169:
                case 0x16A:
                case 0x16B:
                case 0x16C:
                case 0x16D:
                case 0x16E:
                case 0x16F:
                case 0x170:
                case 0x171:
                case 0x172:
                case 0x173:
                case 0x174:
                case 0x175:
                case 0x176:
                    break;
                default:
                    if (i != 0 && !dp->isWazaNew(i - 1)) {
                        slot[0x44] = 1;
                    }
                    break;
                }
            }
        }
    }
    if (flags & 1) {
        GSfloorPush(0x39D);
        if (_menuStatus.flags & 8) {
            floorSetFadeScript(0, 0);
        }
        floorWaitForChange();
    } else {
        _menuPokemonStatusSub(flags, trainer, pokemon, sel, cb, arg);
    }
    return st->result;
}

static s32 _menuPokemonStatusSub(u8 flags, FIGHT_TRAINER* trainer, Pokemon* pokemon, u16 sel, MenuPokemonCB cb, long arg) {
    MenuItemInfo* item = menuItemBiosGetPtr(0x5E, 0x81F);
    menuModelInit(&_menuModel, item->a, item->b);
    menuModelFree(&_menuModel);
    menuModelLoadPokemon(&_menuModel, pokemon);
    if (_menuStatus.flags & 8) {
        fadeCheck(1);
        if (_menuStatus.flags & 0x80) {
            fadeSet(2, 0.25f);
        } else {
            fadeSet(2, 0.5f);
        }
    }
    int start = 0;
    menuOffScreenSetPriority(0);
    MenuStatus* st = &_menuStatus;
    while (1) {
        s32 r = menuOpenCustom(0x5E, 0, &start, 0, 1, 0);
        if (r == -1) {
            st->result = r;
            break;
        }
        st->result = st->cursor;
        if (st->flags & 0x40) {
            u16 w = _menuPokemonStatusGetWazaDataID(st->pokemon, st->cursor);
            if (wazaGetStatus(0, w, 0x19, 0)) {
                GSsndPlayNow(0x13);
                winMsgOpen(2, 0x3AFC, 1, 0);
                winMsgClose(1);
                start = st->cursor;
                continue;
            }
        }
        break;
    }
    if (_menuStatus.flags & 8) {
        fadeCheck(1);
        if (_menuStatus.flags & 0x80) {
            fadeSet(3, 0.25f);
        } else {
            fadeSet(3, 0.5f);
        }
        fadeCheck(1);
    }
    menuPokemonStatusClose();
    menuModelTerm(&_menuModel);
    menuOffScreenSetPriority(1);
    GSthreadSwitch();
    return st->result;
}

static s32 _menuPokemonStatusChangeSubMenu(CURSOR cursor) {
    static int sub_menu_id[4] = { 0x5F, 0x60, 0x62, 0x63 };
    int id = 0;
    if (!_menuStatus.pokemon) {
        return -1;
    }
    switch (cursor.pos) {
    case 0:
        id = 0x5F;
        break;
    case 1:
        id = 0x60;
        break;
    case 2:
        id = 0x62;
        break;
    case 3:
        id = 0x63;
        break;
    }
    for (u32 i = 0; i < 4; i++) {
        if (id == sub_menu_id[i]) {
            if (!menuIsCheck(id)) {
                menuOpen(id, 0);
            }
        } else if (menuIsCheck(sub_menu_id[i])) {
            menuClose(sub_menu_id[i]);
        }
    }
    return -1;
}

extern "C" {
bool menuPokemonStatusCtrl(tagWINDOW_WORK* win) {
    switch (win->state) {
    case 0:
        win->selOld = -1;
        _menuStatus.state = 0;
        _menuStatus.cursor = (s8)win->cursor.pos;
        _menuStatus.f3 = -1;
        _menuStatus.f1a = -1;
        if (_menuStatus.flags & 4) {
            win->cursor.pos = 0;
            _menuStatus.state = 8;
        } else {
            win->cursor.pos = 2;
            _menuStatus.state = 7;
        }
        _menuPokemonStatusChangeSubMenu(win->cursor);
        break;
    case 1:
        break;
    case 2:
        _menuPokemonStatusChangeSubMenu(win->cursor);
        menuDrawReliveUpdate();
        break;
    }
    return 0;
}
}

extern "C" {
void menuPokemonStatusCursor(tagWINDOW_WORK* win) {
    s32 dir = 0;
    s8 limit;
    u32 key;
    MenuStatus* st;
    if (_menuStatus.sel != 0) {
        limit = 5;
    } else {
        limit = 4;
    }
    key = windowGetKeyRepeat();
    st = &_menuStatus;
    switch (st->state) {
    case 0:
    case 9:
        break;
    case 1:
    case 2:
    case 5:
    case 8: {
        u16 keys = key;
        s8 pos = win->cursor.pos;
        if (keys & 8) {
            pos++;
        } else if (keys & 4) {
            pos--;
        }
        if (pos > 3) {
            pos = 3;
        }
        if (pos < 0) {
            pos = 0;
        }
        win->cursor.pos = pos;
        switch (pos) {
        case 0:
            st->state = 8;
            break;
        case 1:
            st->state = 1;
            break;
        case 2:
            st->state = 2;
            break;
        case 3:
            st->state = 5;
            break;
        }
        if (keys & 1) {
            dir = 1;
        } else if (keys & 2) {
            dir = 2;
        }
        if (dir != 0) {
            st = &_menuStatus;
            if (st->cb) {
                Pokemon* next = st->cb(st->pokemon, (MENU_POKEMON_CB_TYPE)dir, st->cbArg);
                if (st->pokemon != next) {
                    if (next) {
                        menuPlaySe(win->menuId, 1);
                        if (!menuModelComparePokemon(&_menuModel, next)) {
                            menuModelLoadPokemon(&_menuModel, next);
                        }
                    }
                    st->pokemon = next;
                    u8* slot = (u8*)&_menuStatus;
                    for (int i = 0; i < 4; i++, slot++) {
                        slot[0x44] = 0;
                        if (next->isDarkPokemon()) {
                            DarkPokemon* dp = next->getDarkPokemon();
                            if (dp) {
                                switch ((u16)pokemonGetStatus(next, 0, 0x7F, (u8)i)) {
                                case 0:
                                case 0x164:
                                case 0x165:
                                case 0x166:
                                case 0x167:
                                case 0x168:
                                case 0x169:
                                case 0x16A:
                                case 0x16B:
                                case 0x16C:
                                case 0x16D:
                                case 0x16E:
                                case 0x16F:
                                case 0x170:
                                case 0x171:
                                case 0x172:
                                case 0x173:
                                case 0x174:
                                case 0x175:
                                case 0x176:
                                    break;
                                default:
                                    if (!dp->isWazaNew(i - 1)) {
                                        slot[0x44] = 1;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    case 3:
    case 4:
    case 7: {
        u16 keys = key;
        MenuStatus* ms = &_menuStatus;
        s8 pos = ms->cursor;
        if (keys & 1) {
            pos--;
        } else if (keys & 2) {
            pos++;
        }
        if (pos >= limit) {
            pos = limit - 1;
        }
        if (pos < 0) {
            pos = 0;
        }
        if (_menuPokemonStatusGetWazaDataID(_menuStatus.pokemon, pos) != 0) {
            if (pos != (s8)ms->cursor) {
                menuPlaySe(win->menuId, 1);
                ms->cursor = pos;
            }
        }
        break;
    }
    case 6: {
        u16 keys = key;
        s8 cur = st->f1a;
        int row = cur % 9;
        int col = cur / 9;
        int c;
        int r;
        if (keys & 1) {
            c = col;
            while (c-- > 0) {
                r = row;
                do {
                    if (st->ribbon.grid[r][c] >= 0) {
                        col = c;
                        row = r;
                        c = -1;
                        break;
                    }
                } while (r-- > 0);
            }
        } else if (keys & 2) {
            c = col;
            while (++c < 4) {
                r = row;
                do {
                    if (st->ribbon.grid[r][c] >= 0) {
                        col = c;
                        row = r;
                        c = 5;
                        break;
                    }
                } while (r-- > 0);
            }
        } else if (keys & 8) {
            bool found = false;
            for (c = col; c < 4; c++) {
                r = (c == col) ? row + 1 : 0;
                for (; r < 9; r++) {
                    if (st->ribbon.grid[r][c] >= 0) {
                        row = r;
                        col = c;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        } else if (keys & 4) {
            bool found = false;
            for (c = col; c >= 0; c--) {
                r = (c == col) ? row - 1 : 8;
                for (; r >= 0; r--) {
                    if (st->ribbon.grid[r][c] >= 0) {
                        row = r;
                        col = c;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
        s8 next = row + col * 9;
        if (next != cur) {
            menuPlaySe(win->menuId, 1);
            st->f1a = next;
        }
        break;
    }
    }
}
}

extern "C" {
void menuPokemonStatusButton(tagWINDOW_WORK* win) {
    u16 keys = windowGetKeyTrg();
    if (keys & 0x10) {
        MenuStatus* st = &_menuStatus;
        switch (st->state) {
        case 0:
        case 1:
        case 6:
        case 8:
        case 9:
            break;
        case 2:
            st->cursor = 0;
            st->state = 3;
            GSsndPlayNow(0x11);
            break;
        case 3:
            if (st->pokemon) {
                if (pokemonGetStatus(st->pokemon, 0, 0xC2, 0)) {
                    GSsndPlayNow(0x13);
                } else if (_menuStatus.flags & 2) {
                    st->state = 4;
                    _menuStatus.f3 = _menuStatus.cursor;
                    GSsndPlayNow(0x11);
                } else {
                    GSsndPlayNow(0x13);
                }
            }
            break;
        case 4: {
            if ((s8)st->f3 != (s8)st->cursor) {
                if (st->pokemon) {
                    pokemonWazaReplace(st->pokemon, (s8)st->f3, (s8)st->cursor);
                }
                st->f3 = -1;
                st->state = 3;
                GSsndPlayNow(0x11);
            }
            break;
        }
        case 5:
            if (st->ribbon.count > 0) {
                s8 i = 0;
                while (i < 0x24) {
                    s8* row = st->ribbon.grid[i % 9];
                    if (row[i / 9] >= 0) {
                        break;
                    }
                    i++;
                }
                st->state = 6;
                _menuStatus.f1a = i;
                GSsndPlayNow(0x11);
            }
            break;
        case 7:
            if (st->flags & 0x10) {
                win->padA4[0] = 1;
                st->result = st->cursor;
            }
            break;
        }
    } else if (keys & 0x20) {
        switch (_menuStatus.state) {
        case 0:
        case 9:
            break;
        case 1:
        case 2:
        case 5:
        case 7:
        case 8:
            win->padA4[0] = 1;
            win->padA4[1] = 1;
            _menuStatus.state = 9;
            break;
        case 3:
            _menuStatus.state = 2;
            GSsndPlayNow(0x12);
            break;
        case 4:
            _menuStatus.state = 3;
            GSsndPlayNow(0x12);
            break;
        case 6:
            _menuStatus.f1a = -1;
            _menuStatus.state = 5;
            GSsndPlayNow(0x12);
            break;
        }
    }
}
}

static s32 _menuPokemonStatusGetZokuseiSpriteID(u16 id) {
    return zokuseiBiosGetSpriteID(id);
}

extern "C" {
void menuPokemonStatusChangeColor(void) {
}
}

extern "C" {
void menuPokemonStatusDrawTitle(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s16 x;
    u32 name;
    Pokemon* pk = _menuStatus.pokemon;
    u32 color;
    if (!pk) {
        return;
    }
    if (!pokemonDataBiosGetPtr((u16)pokemonGetStatus(pk, 0, 0x6E, 0))) {
        return;
    }
    color = win->alpha | 0xFFFFFF00;
    switch (sprite->itemId) {
    case 0x80F:
        if (win->cursor.pos == 0) {
            sprite->color = 0xFFFFFFFF;
        } else {
            sprite->color = 0x808080FF;
        }
        break;
    case 0x80E:
        if (win->cursor.pos == 1) {
            sprite->color = 0xFFFFFFFF;
        } else {
            sprite->color = 0x808080FF;
        }
        break;
    case 0x80D:
        if (win->cursor.pos == 2) {
            sprite->color = 0xFFFFFFFF;
        } else {
            sprite->color = 0x808080FF;
        }
        break;
    case 0x80C:
        if (win->cursor.pos == 3) {
            sprite->color = 0xFFFFFFFF;
        } else {
            sprite->color = 0x808080FF;
        }
        break;
    case 0x81C:
        winSpriteSetDisp(sprite, 1);
        switch (win->cursor.pos) {
        case 2:
            switch (_menuStatus.state) {
            case 3:
            case 4:
                if (_menuStatus.flags & 2) {
                    sprite->msgId = 0x3AE4;
                } else {
                    sprite->msgId = 0x3AE3;
                }
                break;
            case 7:
                sprite->msgId = 0x3C3B;
                break;
            case 9:
                break;
            default:
                sprite->msgId = 0x3AE3;
                break;
            }
            if (_menuStatus.state == 3) {
                if (pokemonIsDarkPokemon(pk) || !(_menuStatus.flags & 2)) {
                    winSpriteSetDisp(sprite, 0);
                }
            }
            break;
        case 3:
            if (_menuStatus.ribbon.count != 0) {
                if (_menuStatus.state == 6) {
                    winSpriteSetDisp(sprite, 0);
                } else {
                    sprite->msgId = 0x3AE6;
                }
            } else {
                winSpriteSetDisp(sprite, 0);
            }
            break;
        default:
            winSpriteSetDisp(sprite, 0);
            break;
        }
        break;
    case 0x811:
    case 0x812:
    case 0x815:
        winSpriteSetDisp(sprite, 0);
        switch (win->cursor.pos) {
        case 2:
            winSpriteSetDisp(sprite, 1);
            if (_menuStatus.state == 3) {
                if (pokemonIsDarkPokemon(pk) || !(_menuStatus.flags & 2)) {
                    winSpriteSetDisp(sprite, 0);
                }
            }
            break;
        case 3:
            if (_menuStatus.ribbon.count != 0) {
                if (_menuStatus.state != 6) {
                    winSpriteSetDisp(sprite, 1);
                }
            }
            break;
        }
        break;
    case 0x81F: {
        MenuItemInfo* item = menuItemBiosGetPtr(0x5E, 0x81F);
        menuModelSetSize(&_menuModel, item->x6, item->x8, item->a, item->b);
        if (menuModelComparePokemon(&_menuModel, pk) == 1) {
            f32 ang[3];
            if (menuModelCheck(&_menuModel, 0) == 0) {
                menuModelAdjustCamera(&_menuModel);
            }
            ang[0] = -0.1f;
            ang[1] = 0.3f;
            ang[2] = 0.0f;
            menuModelSetAngle(&_menuModel, ang);
            menuModelRender(&_menuModel);
        }
        break;
    }
    case 0x817:
    case 0x818:
    case 0x819:
    case 0x81A: {
        u8 mask = 0;
        u8 flags = pokemonGetStatus(pk, 0, 0xBB, 0);
        switch (sprite->itemId) {
        case 0x817:
            mask = 8;
            break;
        case 0x818:
            mask = 4;
            break;
        case 0x819:
            mask = 2;
            break;
        case 0x81A:
            mask = 1;
            break;
        }
        winSpriteSetDisp(sprite, (flags & mask) != 0);
        break;
    }
    case 0x816: {
        u8 ball = pokemonBiosGetCatchBallId(pk);
        if (ball != 0) {
            MenuItemInfo* item = menuItemBiosGetPtr(0x5E, 0x816);
            s32 layer = winSpriteGetLayerID(win, sprite);
            windowDrawSprite2(0, 0, item->a, item->b, -1, win, mballBiosGetSpriteID(ball), 0, layer);
        }
        break;
    }
    case 0x804: {
        u8 v = pokemonGetStatus(pk, 0, 0xB5, 0);
        s32 id;
        if (v & 0xF) {
            id = 0x84;
        } else if (v != 0) {
            id = 0x1F8;
        } else {
            id = 0;
        }
        windowDrawSprite(0, 0, win, id, 0, winSpriteGetLayerID(win, sprite));
        break;
    }
    case 0x805: {
        s32 id = menuPokemonGetJoutaiSpriteID(pk, 1);
        windowDrawSprite(0, 0, win, id, 0, winSpriteGetLayerID(win, sprite));
        break;
    }
    case 0x25D: {
        u16 item = pokemonGetSoubiItemDataId(pk);
        if (item != 0) {
            msgctrlSetValue(0x2D, item);
            GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x3AE7);
        } else {
            msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(0x3C1A));
            GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, 0, color, 0x4277);
        }
        break;
    }
    case 0x81D: {
        x = GSmsgGetRect(sprite->msgId) >> 16;
        msgctrlSetValue(0x5F, (u8)pokemonGetStatus(pk, 0, 0x7A, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), x + 3, 0, sprite->w, sprite->h, color, 0x4351);
        break;
    }
    case 0x81E:
    case 0x264: {
        u32 sexMsg;
        bool sex;
        if (sprite->itemId == 0x264) {
            name = (u32)GSmsgGetGSchar(pokemonGetStatus(0, (u16)pokemonGetStatus(pk, 0, 0x6E, 0), 1, 0));
        } else {
            name = pokemonGetStatus(pk, 0, 0x77, 0);
            if (pokemonCheckRare(pk)) {
                color = win->alpha | 0xFFDC0000;
            }
        }
        msgctrlSetValue(0x37, name);
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
        GSmsgGetRect(0x4277);
        sex = menuSubGetPokemonSexForDisp(pk);
        switch (sex) {
        case 0:
            sexMsg = 0x9C5;
            break;
        case 1:
            sexMsg = 0x9C6;
            break;
        case 2:
        default:
            sexMsg = 0;
            break;
        }
        if (sexMsg != 0) {
            msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(sexMsg));
            GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0x78, 0, color, 0x4276);
        }
        break;
    }
    case 0x81B:
        break;
    }
}
}

bool _menuPokemonStatusCheckOya(Pokemon* pokemon) {
    FIGHT_TRAINER* trainer = _menuStatus.trainer;
    void* hero;
    char* name;
    u32 rnd;
    if (!pokemon) {
        return 0;
    }
    if (gamedataGetStatus(pokemonGetStatus(pokemon, 0, 0x70, 0), 2) != 0xB) {
        return 0;
    }
    if (_menuStatus.flags & 0x20) {
        if (!trainer) {
            trainer = fightFloorGetGcHeroFightTrainerPtr(0);
        }
        if (!trainer) {
            return 0;
        }
        hero = fightTrainerBiosGetHeroPtr(trainer);
    } else {
        if (GSflagGet(0x30D) == 0) {
            hero = savedataGetStatus(0, 2);
        } else {
            hero = menuCBBios_GetRegisteredHero();
        }
    }
    name = heroBiosGetNamePtr(hero);
    rnd = heroBiosGetRnd(hero);
    if (rnd == pokemonGetStatus(pokemon, 0, 0x75, 0)) {
        if (GScharCmp(name, (char*)pokemonGetStatus(pokemon, 0, 0x76, 0)) == 0) {
            return 1;
        }
    }
    return 0;
}

bool _menuPokemonStatusCheckGinzaru(Pokemon* pokemon) {
    int id = (u16)pokemonGetStatus(pokemon, 0, 0x75, 0);
    if (id == 0x911D) {
        if (GScharCmp((char*)pokemonGetStatus(pokemon, 0, 0x76, 0), GSmsgGetGSchar(0x17B9)) == 0) {
            return 1;
        }
    }
    return 0;
}

bool _menuPokemonStatusCheckDanny(Pokemon* pokemon) {
    int id = (u16)pokemonGetStatus(pokemon, 0, 0x75, 0);
    if (id == 0xA1B8) {
        if (GScharCmp((char*)pokemonGetStatus(pokemon, 0, 0x76, 0), GSmsgGetGSchar(0x1828)) == 0) {
            return 1;
        }
    }
    return 0;
}

extern "C" {
void menuPokemonStatusDrawStatus(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    u16 id;
    u32 place;
    MenuStatus* st = &_menuStatus;
    Pokemon* pk = st->pokemon;
    void* pdata;
    u32 color;
    if (!pk) {
        return;
    }
    pdata = pokemonDataBiosGetPtr((u16)pokemonGetStatus(pk, 0, 0x6E, 0));
    if (!pdata) {
        return;
    }
    if (!(u8)_menuPokemonStatusCheckWazaItem(win, sprite)) {
        return;
    }
    color = win->alpha | 0xFFFFFF00;
    switch (sprite->itemId) {
    case 0x845:
        if (pokemonGetStatus(st->pokemon, 0, 0xC2, 0)) {
            sprite->msgId = 0x3C11;
        } else {
            sprite->msgId = 0x3C10;
        }
        break;
    case 0x21D: {
        u16 id = zokuseiGetPokemonSpriteID(pdata, 0);
        if (id != 0) {
            windowDrawSprite(0, 0, win, id, 0, winSpriteGetLayerID(win, sprite));
        }
        break;
    }
    case 0x21C: {
        u8 first = pokemonDataBiosGetZokuseiDataId(pdata, 0);
        u8 second = pokemonDataBiosGetZokuseiDataId(pdata, 1);
        if (first != second) {
            id = zokuseiGetPokemonSpriteID(pdata, 1);
            windowDrawSprite(0, 0, win, id, 0, winSpriteGetLayerID(win, sprite));
        }
        break;
    }
    case 0x25C: {
        u32 msg;
        u32 placeId;
        if (pokemonGetDarkPokemonLevel(pk) < 3) {
            msg = 0x945;
        } else {
            msg = pokemonSeikakuDataBiosGetName(pokemonSeikakuDataBiosGetPtr((u8)pokemonGetStatus(pk, 0, 0xBF, 0)));
        }
        msgctrlSetValue(0x55, msg);
        switch (msg) {
        case 0xC86:
        case 0xC96:
            msgctrlSetValue(0x56, 1);
            break;
        default:
            msgctrlSetValue(0x56, 0x3AEC);
            break;
        }
        {
            u32 n = pokemonGetStatus(pk, 0, 0x72, 0) & 0xFF;
            if (n == 0) {
                n = 5;
            }
            msgctrlSetValue(0x34, n);
        }
        if (_menuPokemonStatusCheckOya(pk)) {
            switch ((u16)pokemonGetStatus(pk, 0, 0x6E, 0)) {
            case 0x85:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0xC4:
            case 0xC5:
                msg = 0x3AF7;
                break;
            default:
                msg = 0x3AE1;
                break;
            }
        } else {
            msg = 0x3AE1;
        }
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, msg);
        msg = 0x3AFA;
        placeId = pokemonGetStatus(pk, 0, 0x71, 0);
        place = floorGetPlaceName(placeId);
        if (_menuPokemonStatusCheckOya(pk)) {
            switch ((u16)pokemonGetStatus(pk, 0, 0x6E, 0)) {
            case 0x85:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0xC4:
            case 0xC5:
                if (!fightKind_CheckFightKind(0xE)) {
                    msg = 0x3AF8;
                }
                break;
            default:
                if (place != 0) {
                    msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(place));
                    msg = 0x3AEB;
                }
                break;
            }
        } else {
            switch ((u8)gamedataGetStatus(pokemonGetStatus(pk, 0, 0x70, 0), 2)) {
            case 0xB:
                if (_menuPokemonStatusCheckGinzaru(pk)) {
                    if (place != 0) {
                        msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(place));
                        msg = 0x3AEB;
                    }
                } else if (_menuPokemonStatusCheckDanny(pk)) {
                    if (place != 0) {
                        msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(place));
                        msg = 0x3AEB;
                    }
                } else if (placeId == 0xFF) {
                    msg = 0x3AF9;
                }
                break;
            case 8:
            case 9:
            case 10:
                if (placeId == 0xFF) {
                    msg = 0x3AF9;
                }
                break;
            }
        }
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0x20, sprite->w, sprite->h, color, msg);
        break;
    }
    case 0x849:
        if (pokemonIsDarkPokemon(pk) == 1) {
            switch (pokemonGetDarkPokemonLevel(pk)) {
            case 0:
                sprite->msgId = 0x3AED;
                break;
            case 1:
                sprite->msgId = 0x3AEE;
                break;
            case 2:
                sprite->msgId = 0x3AEF;
                break;
            case 3:
                sprite->msgId = 0x3AF0;
                break;
            case 4:
                sprite->msgId = 0x3AF1;
                break;
            case 5:
                sprite->msgId = 0x3AF2;
                break;
            case 6:
                sprite->msgId = 0x3AF3;
                break;
            }
        } else {
            sprite->msgId = 0x3ADF;
        }
        break;
    case 0x846: {
        u8 lv = pokemonGetStatus(pk, 0, 0x7A, 0);
        u32 next = pokemonGetLevelToExp(pk, (u8)(lv + 1));
        u32 rem;
        if (next == 0) {
            rem = 0;
        } else {
            rem = next - pokemonGetStatus(pk, 0, 0x79, 0);
        }
        msgctrlSetValue(0x34, rem);
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4287);
        break;
    }
    case 0x848:
        msgctrlSetValue(0x34, pokemonGetStatus(pk, 0, 0x79, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4287);
        break;
    case 0x84A:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pk, 0, 0x8C, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4287);
        break;
    case 0x84C:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pk, 0, 0x8B, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4287);
        break;
    case 0x84E:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pk, 0, 0x8A, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4287);
        break;
    case 0x850:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pk, 0, 0x89, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4287);
        break;
    case 0x852:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pk, 0, 0x88, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4287);
        break;
    case 0x854:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pk, 0, 0x83, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, 0x37, sprite->h, color, 0x4287);
        GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0x37, 0, color, 0x3AE8);
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pk, 0, 0x87, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4287);
        break;
    case 0x843:
        msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetDoc(pokemonTokuseiDataBiosGetPtr(pokemonGetTokuseiDataId(pk)))));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4276);
        break;
    case 0x844:
        msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(pokemonGetTokuseiDataId(pk)))));
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4276);
        break;
    case 0x25F: {
        s32 x = (s16)(GSmsgGetRect(sprite->msgId) >> 16);
        if (pokemonIsDarkPokemon(pk) == 1) {
            GSmsgPrint2(winSpriteGetLayerID(win, sprite), x, 0, color, 0x3AD4);
        } else {
            s32 i;
            u32 v;
            u32 div;
            v = pokemonGetStatus(pk, 0, 0x75, 0);
            div = 10000;
            for (i = 0; i < 5; i++) {
                u32 digit = v / div;
                v = v % div;
                div = div / 10;
                msgctrlSetValue(0x34, digit);
                GSmsgPrint2(winSpriteGetLayerID(win, sprite), x + i * 13, 0, color, 0x426F);
            }
        }
        break;
    }
    case 0x261: {
        s32 x;
        if (pokemonIsDarkPokemon(pk) == 1) {
            msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(0x3AD4));
        } else {
            msgctrlSetValue(0x37, pokemonGetStatus(pk, 0, 0x76, 0));
        }
        x = GSmsgGetRect(sprite->msgId) >> 16;
        GSmsgPrint2(winSpriteGetLayerID(win, sprite), x, 0, color, 0x4276);
        break;
    }
    case 0x83B: {
        s16 cur = pokemonGetStatus(pk, 0, 0x83, 0);
        s16 max = pokemonGetStatus(pk, 0, 0x87, 0);
        f32 ratio = (f32)cur / (f32)max;
        u32 key;
        if (ratio < 0.2) {
            key = 0xF5;
        } else if (ratio < 0.5) {
            key = 0xF4;
        } else {
            key = 0xF3;
        }
        windowDrawSprite2(0, 0, (s32)(sprite->w * ratio), sprite->h, color, win, key, 0, winSpriteGetLayerID(win, sprite));
        break;
    }
    case 0x83C: {
        u8 lv = pokemonGetStatus(pk, 0, 0x7A, 0);
        u32 next = pokemonGetLevelToExp(pk, (u8)(lv + 1));
        if (next != 0) {
            u32 base = pokemonGetLevelToExp(pk, lv);
            u32 range = next - base;
            u32 have = pokemonGetStatus(pk, 0, 0x79, 0) - base;
            u32 num = range + have * sprite->w;
            s16 w = (num - 1) / range;
            windowDrawSprite2(0, 0, w, sprite->h, color, win, 0xF6, 0, winSpriteGetLayerID(win, sprite));
        }
        break;
    }
    case 0x83E: {
        MenuItemInfo* item = menuItemBiosGetPtr(0x60, 0x83E);
        menuDrawReliveMeter(pk, item->a, item->b, winSpriteGetLayerID(win, sprite));
        break;
    }
    }
}
}

s32 _menuPokemonStatusCheckWazaItem(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s32 show = 1;
    switch (sprite->itemId) {
    case 0x1E1:
    case 0x1E2:
    case 0x1E3:
    case 0x1E4:
    case 0x1E5:
    case 0x1E6:
    case 0x1E7:
    case 0x1E8:
    case 0x1E9:
    case 0x1EA:
    case 0x1EB:
    case 0x1EC:
    case 0x1ED:
    case 0x1EE:
    case 0x1EF:
    case 0x1F0:
    case 0x1F1:
    case 0x1F2:
    case 0x1F3:
    case 0x1F4:
    case 0x1F5:
    case 0x1F6:
    case 0x1F7:
    case 0x1F8:
    case 0x24C:
        switch (_menuStatus.state) {
        case 3:
        case 4:
        case 7: {
            s32 c = _menuStatus.cursor;
            if (c >= 0 && c <= 4) {
                show = 1;
            } else {
                show = 0;
            }
            break;
        }
        default:
            show = 0;
            break;
        }
        winSpriteSetDisp(sprite, show);
        break;
    case 0x83D:
    case 0x83E:
    case 0x83F:
    case 0x840:
    case 0x841:
    case 0x842:
        winSpriteSetDisp(sprite, 0);
        break;
    case 0x837:
    case 0x83C:
    case 0x846:
    case 0x847:
    case 0x848:
        if (pokemonGetStatus(_menuStatus.pokemon, 0, 0xC2, 0) != 0) {
            show = 0;
        } else {
            show = 1;
        }
        winSpriteSetDisp(sprite, show);
        break;
    }
    return show;
}

u16 _menuPokemonStatusGetWazaDataID(Pokemon* pokemon, u16 index) {
    u16 waza;
    if (index == 4) {
        waza = _menuStatus.sel;
    } else {
        waza = pokemonGetStatus(pokemon, 0, 0x7F, index);
        if (!pokemonWazaCheckValid(pokemon, index)) {
            return 0;
        }
    }
    return waza;
}

static long NotDarkWaza(long id) {
    if (id >= 0x176) {
        return id;
    }
    if (id < 0x164) {
        return id;
    }
    return 0;
}

extern "C" {
void menuPokemonStatusDrawWaza(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    Pokemon* pk = _menuStatus.pokemon;
    u16 idx;
    s32 n = 0;
    u32 color;
    if (!pk) {
        return;
    }
    if (!(u8)_menuPokemonStatusCheckWazaItem(win, sprite)) {
        return;
    }
    color = win->alpha | 0xFFFFFF00;
    switch (sprite->itemId) {
    case 0x205:
        winSpriteSetDisp(sprite, 0);
        switch (_menuStatus.state) {
        case 4:
            if (_menuStatus.sel != 0) {
                windowDrawSprite(0, (s8)_menuStatus.f3 * 0x2C, win, 0xF7, 0, winSpriteGetLayerID(win, sprite));
                windowDrawSprite(0, (s8)_menuStatus.cursor * 0x2C, win, 0xF2, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, ((s8)_menuStatus.f3 + 1) * 0x2C, win, 0xF7, 0, winSpriteGetLayerID(win, sprite));
                windowDrawSprite(0, ((s8)_menuStatus.cursor + 1) * 0x2C, win, 0xF2, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        case 3:
        case 7:
            if (_menuStatus.sel != 0) {
                windowDrawSprite(0, (s8)_menuStatus.cursor * 0x2C, win, 0xF2, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, ((s8)_menuStatus.cursor + 1) * 0x2C, win, 0xF2, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        }
        break;
    case 0x200:
    case 0x201:
    case 0x202:
    case 0x203:
    case 0x204: {
        u16 waza;
        if (_menuStatus.sel == 0) {
            if (sprite->itemId == 0x204) {
                return;
            }
            switch (sprite->itemId) {
            case 0x203:
                idx = 0;
                break;
            case 0x202:
                idx = 1;
                break;
            case 0x201:
                idx = 2;
                break;
            case 0x200:
                idx = 3;
                break;
            }
        } else {
            if (sprite->itemId == 0x200) {
                windowDrawSprite(7, 0x14, win, 0xF8, 0, winSpriteGetLayerID(win, sprite));
            }
            switch (sprite->itemId) {
            case 0x204:
                idx = 0;
                break;
            case 0x203:
                idx = 1;
                break;
            case 0x202:
                idx = 2;
                break;
            case 0x201:
                idx = 3;
                break;
            case 0x200:
                idx = 4;
                break;
            }
        }
        waza = _menuPokemonStatusGetWazaDataID(pk, idx);
        switch (NotDarkWaza(waza)) {
        case 0:
            waza = 0;
            break;
        case 0x176:
            waza = 0x7B;
            break;
        default:
            waza = _menuPokemonStatusGetZokuseiSpriteID((u16)wazaGetStatus(0, waza, 3, 0));
            if (_menuStatus.dark[idx] != 0) {
                if (idx != 0) {
                    windowDrawSprite(7, 0x14, win, 0xF8, 0, winSpriteGetLayerID(win, sprite));
                    pk->getDarkPokemon()->setWazaNew((u8)(idx - 1), true);
                }
            }
            break;
        }
        if (waza != 0) {
            windowDrawSprite(0, 0, win, waza, 0, winSpriteGetLayerID(win, sprite));
        }
        break;
    }
    case 0x24F:
    case 0x250:
    case 0x251:
    case 0x252:
    case 0x253: {
        u16 idx;
        u16 waza;
        if (_menuStatus.sel == 0) {
            if (sprite->itemId == 0x253) {
                return;
            }
            switch (sprite->itemId) {
            case 0x252:
                idx = 0;
                break;
            case 0x251:
                idx = 1;
                break;
            case 0x250:
                idx = 2;
                break;
            case 0x24F:
                idx = 3;
                break;
            }
        } else {
            switch (sprite->itemId) {
            case 0x253:
                idx = 0;
                break;
            case 0x252:
                idx = 1;
                break;
            case 0x251:
                idx = 2;
                break;
            case 0x250:
                idx = 3;
                break;
            case 0x24F:
                idx = 4;
                break;
            }
        }
        waza = _menuPokemonStatusGetWazaDataID(pk, idx);
        if (waza == 0) {
            GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x3AF4);
            return;
        }
        {
            u32 name = wazaGetStatus(0, waza, 1, 0);
            if (name == 0) {
                return;
            }
            msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(name));
            GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4277);
        }
        break;
    }
    case 0x254:
    case 0x255:
    case 0x256:
    case 0x257:
    case 0x258: {
        u16 idx;
        u16 waza;
        s16 half;
        if (_menuStatus.sel == 0) {
            if (sprite->itemId == 0x258) {
                return;
            }
            switch (sprite->itemId) {
            case 0x257:
                idx = 0;
                break;
            case 0x256:
                idx = 1;
                break;
            case 0x255:
                idx = 2;
                break;
            case 0x254:
                idx = 3;
                break;
            }
        } else {
            switch (sprite->itemId) {
            case 0x258:
                idx = 0;
                break;
            case 0x257:
                idx = 1;
                break;
            case 0x256:
                idx = 2;
                break;
            case 0x255:
                idx = 3;
                break;
            case 0x254:
                idx = 4;
                break;
            }
        }
        waza = _menuPokemonStatusGetWazaDataID(pk, idx);
        half = (sprite->w - (s16)(GSmsgGetRect(0x3AE8) >> 16)) / 2;
        GSmsgPrint2(winSpriteGetLayerID(win, sprite), (u16)half, 0, color, 0x3AE8);
        switch (NotDarkWaza(waza)) {
        case 0:
            GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, half, sprite->h, color, 0x3AF5);
            GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x3AF5);
            break;
        case 0x176:
            GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, half, sprite->h, color, 0x3AD1);
            GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x3AD1);
            break;
        default:
            msgctrlSetValue(0x34, idx == 4 ? wazaGetStatus(0, waza, 2, 0) : pokemonGetStatus(pk, 0, 0x80, idx));
            GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, half, sprite->h, color, 0x427B);
            msgctrlSetValue(0x34, idx == 4 ? wazaGetStatus(0, waza, 2, 0) : (u8)pokemonWazaGetMaxPP(pk, idx));
            GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x427B);
            break;
        }
        break;
    }
    case 0x24C: {
        u32 v = wazaGetStatus(0, _menuPokemonStatusGetWazaDataID(pk, _menuStatus.cursor), 0x22, 0);
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, (u16)v);
        break;
    }
    case 0x24D:
        switch (_menuStatus.state) {
        case 3:
        case 4:
        case 7: {
            u32 v = wazaGetStatus(0, _menuPokemonStatusGetWazaDataID(pk, _menuStatus.cursor), 6, 0);
            if (v <= 1) {
                GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x3AF6);
            } else {
                msgctrlSetValue(0x34, v);
                GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4270);
            }
            winSpriteSetDisp(sprite, 1);
            break;
        }
        default:
            winSpriteSetDisp(sprite, 0);
            break;
        }
        break;
    case 0x24E:
        switch (_menuStatus.state) {
        case 3:
        case 4:
        case 7: {
            u32 v = wazaGetStatus(0, _menuPokemonStatusGetWazaDataID(pk, _menuStatus.cursor), 7, 0);
            if (v <= 1) {
                GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x3AF6);
            } else {
                msgctrlSetValue(0x34, v);
                GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4270);
            }
            winSpriteSetDisp(sprite, 1);
            break;
        }
        default:
            winSpriteSetDisp(sprite, 0);
            break;
        }
        break;
    case 0x1FD:
        if (_menuStatus.sel == 0) {
            winSpriteSetDisp(sprite, 0);
        } else {
            winSpriteSetDisp(sprite, 1);
        }
        break;
    case 0x388:
    case 0x389:
    case 0x38A:
    case 0x38B:
        if (_menuStatus.sel == 0) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x1E8:
        n++;
    case 0x1E9:
        n++;
    case 0x1EB:
        n++;
    case 0x1EA:
        n++;
    case 0x1ED:
        n++;
    case 0x1EC:
        n++;
    case 0x1EE:
        n++;
    case 0x1EF:
        n += 2;
    case 0x1F0:
        n++;
    case 0x1F1:
        n++;
    case 0x1F3:
        n++;
    case 0x1F2:
        n++;
    case 0x1F5:
        n++;
    case 0x1F6:
        n++;
    case 0x1F4:
        n++;
    case 0x1F7:
        n++;
    case 0x1F8: {
        u16 wid = _menuPokemonStatusGetWazaDataID(pk, (s8)_menuStatus.cursor);
        switch (wazaDB_GetCompatible(wid)) {
        case 1: {
            u16 id;
            switch (zokuseiBiosGetWazaJoutai((u16)wazaGetStatus(0, wid, 3, 0), (u16)n)) {
            case 0x3F:
                id = 0x35D;
                break;
            case 0x41:
                id = 0x35F;
                break;
            case 0x42:
                id = 0x360;
                break;
            case 0x43:
                id = 0x35E;
                break;
            }
            windowDrawSprite(0, 0, win, id, 0, winSpriteGetLayerID(win, sprite));
            break;
        }
        case 4:
            if (n == 7) {
                windowDrawSprite(0, 0, win, 0x35E, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, 0, win, 0x35D, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        case 5:
            if (n == 0xC) {
                windowDrawSprite(0, 0, win, 0x35E, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, 0, win, 0x35D, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        case 6:
            if (n == 3 || n == 8) {
                windowDrawSprite(0, 0, win, 0x35E, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, 0, win, 0x35D, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        case 7:
            if (n == 4) {
                windowDrawSprite(0, 0, win, 0x35E, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, 0, win, 0x35D, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        case 8:
            if (n == 2) {
                windowDrawSprite(0, 0, win, 0x35E, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, 0, win, 0x35D, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        case 9:
            if (n == 0) {
                windowDrawSprite(0, 0, win, 0x35E, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, 0, win, 0x35D, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        case 10:
        case 11:
        case 14:
            windowDrawSprite(0, 0, win, 0x376, 0, winSpriteGetLayerID(win, sprite));
            break;
        case 12:
            if (n == 0x11) {
                windowDrawSprite(0, 0, win, 0x35E, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, 0, win, 0x35D, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        case 13:
            if (n == 0xA) {
                windowDrawSprite(0, 0, win, 0x35E, 0, winSpriteGetLayerID(win, sprite));
            } else {
                windowDrawSprite(0, 0, win, 0x35D, 0, winSpriteGetLayerID(win, sprite));
            }
            break;
        case 15:
            windowDrawSprite(0, 0, win, 0x35D, 0, winSpriteGetLayerID(win, sprite));
            break;
        }
        break;
    }
    }
}
}

void _menuPokemonStatusMakeRibbon(Pokemon* pokemon, RIBBON_WORK* work) {
    static RibbonMap ribbon_mapping_tbl[10] = {
        { 0xA3, 0, 1 }, { 0xB0, 1, 4 }, { 0xB1, 5, 4 }, { 0xB2, 9, 4 }, { 0xB3, 0xD, 4 },
        { 0xB4, 0x11, 4 }, { 0xA4, 0x15, 1 }, { 0xA5, 0x16, 1 }, { 0xA6, 0x17, 1 }, { 0xA7, 0x18, 1 },
    };
    static RibbonMap exribbon_mapping_tbl[7] = {
        { 0xA8, 0x19, 1 }, { 0xA9, 0x1A, 1 }, { 0xAA, 0x1B, 1 }, { 0xAB, 0x1C, 1 },
        { 0xAC, 0x1D, 1 }, { 0xAD, 0x1E, 1 }, { 0xAE, 0x1F, 1 },
    };
    int i;
    int j;
    int n;
    int idx = 0;
    int count;
    u32 k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 9; j++) {
            work->grid[j][i] = -1;
        }
    }
    for (k = 0; k < 10; k++) {
        n = pokemonGetStatus(pokemon, 0, ribbon_mapping_tbl[k].id, 0);
        if (n > ribbon_mapping_tbl[k].max) {
            n = ribbon_mapping_tbl[k].max;
        }
        for (i = 0; i < n; i++) {
            work->grid[idx % 9][idx / 9] = ribbon_mapping_tbl[k].start + i;
            idx++;
        }
    }
    idx = 0;
    for (k = 0; k < 7; k++) {
        n = pokemonGetStatus(pokemon, 0, exribbon_mapping_tbl[k].id, 0);
        if (n > exribbon_mapping_tbl[k].max) {
            n = exribbon_mapping_tbl[k].max;
        }
        for (i = 0; i < n; i++) {
            work->grid[idx][3] = exribbon_mapping_tbl[k].start + i;
            idx++;
        }
    }
    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 9; j++) {
            if (work->grid[j][i] >= 0) {
                count++;
            }
        }
    }
    work->count = count;
}

extern "C" {
void menuPokemonStatusCtrlRibbon(void) {
    if (_menuStatus.pokemon) {
        _menuPokemonStatusMakeRibbon(_menuStatus.pokemon, &_menuStatus.ribbon);
    }
}
}

extern "C" {
void menuPokemonStatusDrawRibbon(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    u32 color;
    u32 msg;
    s32 n = 0;
    if (windowSearchID(0x5E) == 0) {
        return;
    }
    if (!_menuStatus.pokemon) {
        return;
    }
    color = win->alpha | 0xFFFFFF00;
    switch (sprite->itemId) {
    case 0x25B:
        msgctrlSetValue(0x34, _menuStatus.ribbon.count);
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, 0x4287);
        break;
    case 0x25A:
        if (_menuStatus.state != 6) {
            break;
        }
        {
            s8 idx = _menuStatus.f1a;
            n = _menuStatus.ribbon.grid[idx % 9][idx / 9];
        }
        if (n < 0) {
            if (getRibbonCnt() <= n) {
                break;
            }
        }
        {
            s32 id = ribbon_id_tbl[n];
            switch (id) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6: {
                u8 no = exribbonGetNo(id);
                if (no != 0) {
                    s32 k = no - 1;
                    msg = ex_ribbon_id[k];
                } else {
                    msg = 0;
                }
                break;
            }
            case -1:
                msg = getRibbonMsgID(n);
                break;
            }
        }
        if (msg != 0) {
            GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->w, sprite->h, color, msg);
        }
        break;
    case 0x22A:
        n++;
    case 0x22B:
        n++;
    case 0x22C:
        n++;
    case 0x22D:
        n++;
    case 0x22E:
        n++;
    case 0x22F:
        n++;
    case 0x230:
        n++;
    case 0x231:
        n++;
    case 0x232:
        n++;
    case 0x233:
        n++;
    case 0x234:
        n++;
    case 0x235:
        n++;
    case 0x236:
        n++;
    case 0x237:
        n++;
    case 0x238:
        n++;
    case 0x239:
        n++;
    case 0x23A:
        n++;
    case 0x23B:
        n++;
    case 0x23C:
        n++;
    case 0x23D:
        n++;
    case 0x23E:
        n++;
    case 0x23F:
        n++;
    case 0x240:
        n++;
    case 0x241:
        n++;
    case 0x242:
        n++;
    case 0x243:
        n++;
    case 0x244:
        n++;
    case 0x245:
        n++;
    case 0x246:
        n++;
    case 0x247:
        n++;
    case 0x248:
        n++;
    case 0x249: {
        s32 idx = 32 - (n + 1);
        if (idx > 0x18) {
            idx += 2;
        }
        if (_menuStatus.ribbon.grid[idx % 9][idx / 9] >= 0) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x229: {
        s32 idx = (s8)_menuStatus.f1a;
        if (idx < 0) {
            break;
        }
        s32 col = idx % 9;
        windowDrawSprite(col * 30, (idx / 9) * 0x34, win, 0x366, 0, winSpriteGetLayerID(win, sprite));
        break;
    }
    case 0x21E:
    case 0x220:
        if (_menuStatus.state == 6) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
}
}
