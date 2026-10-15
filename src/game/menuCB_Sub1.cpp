// Pokemon XD menu callbacks for the Colosseum battle sub screens (rules, entry, errors).
// WIP: see per-function status via fcheck.
#include <dolphin/types.h>

// Menu callbacks were built without the peephole optimizer.
#pragma peephole off

struct Pokemon {
    u8 data[0xC4];
};

struct CAnt {
    u8 data[0x34];
    void initByPokemonAndSetColorAnimationInAny(Pokemon*);
    void setAnimation(long);
};

struct ErrEntry {
    u8 a7 : 1, a6 : 1, a5 : 1, a4 : 1, a3 : 1, a2 : 1, a1 : 1, a0 : 1;
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
    u8 pad[2];
};

struct CBWork {
    u8 pad0[0x8];
    s32 unk8;
    u8 padC[0x992A];
    u8 ruleStr[0x90];
    u8 pad99C6[0x2B2];
    u8* rule;
    u8 pad9C7C[0x8];
    ErrEntry err[4][6];
    u8 pad9CE4[0x978];
    u8 hero[1];
    u8 padA65D[0x983];
    s32 unkAFE0;
    s32 unkAFE4;
    u8 padAFE8[0x2C];
    s32 unkB014;
    u8 padB018[0x10];
    s32 scroll;
    u8 padB02C[0xA8];
    u32 tempBuff;
    s32 errPlayer;
    u8 padB0DC[0x8];
    s32 unkB0E4;
    s32 unkB0E8;
    s32 unkB0EC;
    s32 unkB0F0;
    u8 padB0F4[0x4];
    s32 unkB0F8;
    s32 unkB0FC;
    s32 unkB100;
    u8 padB104[0x14];
    s32 unkB118;
    u32 unkB11C;
    u8 padB120[0x4];
    s32 unkB124;
    s32 unkB128;
    s32 unkB12C;
    u8 padB130[0x8];
    s32 unkB138;
    u8 padB13C[0x8];
    s32 unkB144;
    s32 unkB148;
    s32 unkB14C;
    u8 padB150[0x84];
    s32 unkB1D4;
    s32 unkB1D8;
    s32 unkB1DC;
    s32 unkB1E0;
    u8 padB1E4[0x2BC];
    u8 unkB4A0;
    u8 padB4A1[0x83];
    Pokemon* relive[8][4];
};
struct CBMsgWin {
    u8 pad0[6];
    s16 id;
    u8 pad8[0x44];
    s32 unk4C;
};

struct tagWINDOW_WORK {
    u8 pad0[4];
    s32 menuId;
    u8 pad8[0x14];
    s32 layer;
    u8 pad20[0x73];
    u8 alpha;
};
typedef tagWINDOW_WORK CBWin;

struct CBSprite {
    u8 pad0[6];
    s16 itemId;
};

struct CBMenuItem {
    u8 pad0[6];
    s16 x, y, w, h;
};

struct CBItem {
    u8 pad0[0x54];
    s16 w;
    s16 h;
    u8 pad58[0xC];
    u8 cr, cg, cb;
    u8 alpha;
};

struct MenuSpriteVal {
    s16 unk0;
    s16 unk2;
    s16 x;
    s16 y;
};

void menuPtSpriteDrawColor(u16, long, long, long, long, u32);
void menuPtSpriteDrawColor(u16, long, long, u32);

extern "C" {
extern CBWork _CB;
struct BattleStartWork {
    u8 pad[0x2C];
    s32 a, b;
};
extern BattleStartWork _menuCBBattleStartWork;
void msgctrlSetValue(s32, void*);
u32 GSmsgGetRect(s32);
void GSmsgPrint2(s32, s32, s32, u32, s32);
void GSsndPlay(s32, s32, s32);
void GSsndStop(s32, s32, s32);
u8 menuSubAnimAlpha(void);
f32 timeGetLastFrameSec(void);
double fmod(double, double);
void* menuSpriteBiosGetPtr(s32);
void menuCB_MenuDispCheckONorOFF(CBWin*, bool);
void menuCB_SpriteDispCheckONorOFF(CBSprite*, bool);
u8 menuCBPokemonCheck(u32, u32);
void* pokemonBiosGetNicknamePtr(Pokemon*);
u16 pokemonGetSoubiItemDataId(Pokemon*);
s32 heroItemCheckAddItemDataId(void*, u16);
void heroItemAddItemDataId(void*, u16, s32, s32);
s32 heroItemDecItemDataId(void*, u16, s32, u8);
u16 pokemonDoItemSoubi(Pokemon*, u16, s32);
struct CBRule {
    u8 pad[8];
    s32 unk8;
};
CBRule* menuCBBios_CurrentRule(void);
u16 menuPocket2Call(s32, s32, void*);
u8 menuPocket2GetLastSlotID(void);
void menuCBRule_ErrorFlagSetItemGetTiming(void*, Pokemon*, u32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
void menuPokemonStatusOpenFromPokemonChange(Pokemon*, s32, s32);
u8 menuCBPokemonEntryGetReadFlag(void);
void menuCB_SetSprite(CBWin*, void*);
u16 toolentryTaisenGetBattlePlayerID(s32);
s32 toolentryTaisenGetHomePlace(s32);
u16 toolentryTaisenGetEntryPokemonNum(s32);
Pokemon* toolentryTaisenGetEntryPokemonPtr(s32, s32);
s32 menuCBBattleStartGetStatus(void);
u16 toolentryTaisenGetHomePlaceX(s32);
void menuCBPokemonEntryDispPokemonFace(s32, s32, s32, s32);
u8 menuCBPokemonEntryDisp(CBSprite*);
u8 menuCBPokemonGetDataId(s32, s32);
u16* heroBiosGetNamePtr(void*);
void* pokemonDataBiosGetPtr(u16);
s32 zokuseiGetPokemonSpriteID(void*, s32);
void windowDrawSprite(s32, s32, CBWin*, u16, s32, s32);
u8 GSinputIsConnected(s32);
u8 gbaCommandIsConnected(s32);
void menuSetDisp(s32, s32);
void winSpriteSetDisp(CBSprite*, s32);
u8 fightReadResourceID(s32, s32);
void fightFreeResourceID(s32, s32);
s32 winSpriteGetLayerID(CBWin*, CBSprite*);
CBMenuItem* menuItemBiosGetPtr(s32, s32);
void spriteSetScissor(s32, s32, s32, s32, s32);
void spriteClearScissor(s32);
u16 menuCBRule_RegulationItemID(s32);
u8 itemDataCheckValid(u16);
void* itemDataBiosGetPtr(u16);
s32 itemDataBiosGetName(void*);
u16* GSmsgGetGSchar(s32);
MenuSpriteVal* menuSpriteBiosGetValPtr(void*);
void pokemonAllKaihuku(Pokemon*);
void menuCB_SE_Play(s32);
s32 fn_8007E634(s32);
void* savedataGetStatus(s32, s32);
Pokemon* heroBiosGetPokemonPtr(void*, u16);
Pokemon* toolentryTaisenGetPokemonPtr(u32, u32);
void* memcpy(void*, const void*, u32);
void pokemonInit(Pokemon*);
void menuCBGCEntryTypeIndex(u32*, u32*);
void toolBattleRuleErrorFlagClear(s32, u32);
void menuCBRule_ErrorFlagSetPokemonGetTiming(void*, Pokemon*, u32);
u8 menuCB_Trainer_Error_Check(u32, s32);
u32 pokemonGetStatus(Pokemon*, s32, s32, s32);
u16 pokemonGetStatusU16(Pokemon*, s32, s32, s32);
void menuCBGCDelPokemon(void);
void menuCBMessageCenterDisp(CBWin*, CBItem*, s32);
s32 pokecoloGetCountryCode(void);
u8 pokemonCheckValid(Pokemon*);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
void GSthreadSwitch(void);
void* windowGetKeyInfo(void);
void GSfsysReadWait(s32);
void GSfsysFree(s32);
void GSresFreeGroup(s32);
void menuTopOpenFlashBack(void);
void menuCB_FlashStart(s32);
void menuCB_FlashEnd(s32);
void fadeSet(s32, f32);
void menuOpen(s32, s32);
void menuCloseCustom(s32, s32, s32);
}

class CReliveStage {
public:
    Pokemon* getDancerPointer(long);
    Pokemon* getVisitorPointer();
    void insertDancer(Pokemon&, long);
};

class CReliveHall {
public:
    static CReliveHall* getPointer();
    CReliveStage* getStage(long);
};

struct PCBOX {
    static PCBOX* getPointer();
    Pokemon* getPokemon(s8, s8);
};

static CAnt ant[0x24];
static CAnt antR[0x1E];
static CAnt antL[0x1E];

static Pokemon* menuCBPokemonPtrGet(u32, u32);
static void _menuCB_errorMsgDisp2(u32);
static void _menuCB_errorMsgDisp(u32);
static void _menuCB_PokemonStatusDispBeforeJob(u32);
static void _menuCB_PokemonStatusDispAfterJob(u32);
static f32 _f_menuCB_circleAnimationTime;
static u32 backup_type[6];
static u32 backup_index[6];

static const s32 BATTLE_BA_XP_PRINT_Char[4] = {0x20F, 0x20E, 0x20D, 0x20C};
static const s32 BATTLE_BA_HP_Bar_Char[3] = {0x2B8, 0x2B9, 0x2BA};
static void _drawStrings(CBWin*, u16*, long, long, u32);
static void _menuCBPokemonName(tagWINDOW_WORK*, u32, u32, u32, bool);
struct CBKeyInfo {
    u8 pad[4];
    u16 buttons;
};

extern "C" {

void fn_8007E5AC(CBWin* a, CBMsgWin* w) {
    switch (w->id) {
    case 0x2B7:
        menuCBMessageCenterDisp(a, (CBItem*)w, 0xD11E);
        break;
    case 0x2B8:
        menuCBMessageCenterDisp(a, (CBItem*)w, 0xD11F);
        break;
    case 0x4D1:
        w->unk4C = 0xD160;
        break;
    case 0x433:
        menuCBMessageCenterDisp(a, (CBItem*)w, 0x3BD6);
        break;
    }
}

s32 fn_8007E634(s32 msg) {
    switch (pokecoloGetCountryCode()) {
    case 0:
        return msg;
    case 1:
    case 2:
        switch (msg) {
        case 0x4278:
            return 0x4279;
        case 0x4276:
            return 0x4277;
        case 0x427C:
            return 0x4352;
        case 0x427B:
            return 0x4351;
        }
    }
    return 0x56C;
}
}

static s32 _menuCB_NotDarkWaza(s32 id) {
    if (id < 0x176 && id >= 0x164) {
        return 0;
    }
    return id;
}

static void _menuCB_ErrorTAMAGOCheck() {
    int i;
    for (i = 0; i < 6; i++) {
        if (_CB.err[_CB.errPlayer][i].a2) {
            _CB.err[_CB.errPlayer][i].a5 = 0;
            _CB.err[_CB.errPlayer][i].a4 = 0;
            _CB.err[_CB.errPlayer][i].b3 = 0;
        }
        if (_CB.err[_CB.errPlayer][i].b1) {
            _CB.err[_CB.errPlayer][i].a5 = 0;
            _CB.err[_CB.errPlayer][i].a4 = 0;
            _CB.err[_CB.errPlayer][i].b3 = 0;
            _CB.err[_CB.errPlayer][i].a2 = 1;
        }
        if (_CB.err[_CB.errPlayer][i].b4 && _CB.err[_CB.errPlayer][i].b6) {
            _CB.err[_CB.errPlayer][i].b6 = 0;
        }
    }
}

static void _menuCB2DPokemonNewSet2(u32 type, u32 base, u32 count, u8 kind) {
    Pokemon* p;
    u32 i;
    for (i = 0; i < count; i++) {
        p = menuCBPokemonPtrGet(type, base | i);
        if (p && pokemonCheckValid(p)) {
            switch (kind) {
            case 0:
                antR[i].initByPokemonAndSetColorAnimationInAny(p);
                antR[i].setAnimation(0);
                break;
            case 1:
                antL[i].initByPokemonAndSetColorAnimationInAny(p);
                antL[i].setAnimation(0);
                break;
            case 2:
                ant[i].initByPokemonAndSetColorAnimationInAny(p);
                ant[i].setAnimation(0);
                break;
            }
        }
    }
}

static void _menuCB2DPokemonNewSet(u8 kind) {
    if (kind == 2) {
        _menuCB2DPokemonNewSet2(4, 0, 6, kind);
        return;
    }
    switch (_CB.unkB0F0) {
    case 0:
        switch (kind) {
        case 0:
            _menuCB2DPokemonNewSet2(5, 0, 0x1E, kind);
            break;
        case 1:
            if (_CB.unkB4A0 == 1) {
                _menuCB2DPokemonNewSet2(6, 0x80000, 5, kind);
            } else {
                _menuCB2DPokemonNewSet2(5, 0x70000, 0x1E, kind);
            }
            break;
        }
        break;
    case 1:
        switch (kind) {
        case 0:
            if (_CB.unkB0E8 == 7) {
                if (_CB.unkB4A0 == 1) {
                    _menuCB2DPokemonNewSet2(6, 0, 5, kind);
                } else {
                    _menuCB2DPokemonNewSet2(4, 0, 6, kind);
                }
            } else {
                _menuCB2DPokemonNewSet2(5, (_CB.unkB0E8 + 1) << 16, 0x1E, kind);
            }
            break;
        case 1:
            if (_CB.unkB0E8 == 0) {
                _menuCB2DPokemonNewSet2(4, 0, 6, kind);
            } else {
                _menuCB2DPokemonNewSet2(5, (_CB.unkB0E8 - 1) << 16, 0x1E, kind);
            }
            break;
        }
        break;
    case 2:
        switch (kind) {
        case 0:
            if (_CB.unkB0EC == 8) {
                _menuCB2DPokemonNewSet2(4, 0, 6, kind);
            } else {
                _menuCB2DPokemonNewSet2(6, (_CB.unkB0EC + 1) << 16, 5, kind);
            }
            break;
        case 1:
            if (_CB.unkB0EC == 0) {
                _menuCB2DPokemonNewSet2(5, 0x70000, 0x1E, kind);
            } else {
                _menuCB2DPokemonNewSet2(6, (_CB.unkB0EC - 1) << 16, 5, kind);
            }
            break;
        }
        break;
    }
}

static void _menuCB_errorMsgDisp2(u32 msg) {
    winMsgOpen(2, msg, 1, 0);
    winMsgClose(1);
}

static void _menuCB_errorMsgDisp(u32 msg) {
    winMsgOpen(2, msg, 1, 1);
    do {
        GSthreadSwitch();
    } while ((((CBKeyInfo*)windowGetKeyInfo())->buttons & 0x30) == 0);
    winMsgClose(1);
}

static void _menuCB_PokemonStatusDispAfterJob(u32 first) {
    if (first == 0) {
        GSfsysReadWait(0x88C);
        menuTopOpenFlashBack();
        menuCB_FlashStart(0);
        fadeSet(2, 0.5f);
    }
    menuCB_SE_Play(0x14);
    menuOpen(0xBB, 0);
    menuOpen(0xBD, 0);
    menuOpen(0xBE, 0);
    menuOpen(0xBF, 0);
    menuOpen(0x10D, 0);
    menuOpen(0x10F, 0);
    menuOpen(0x10E, 0);
    menuOpen(0xC2, 0);
}

static void _menuCB_PokemonStatusDispBeforeJob(u32 first) {
    if (first == 0) {
        menuCB_FlashEnd(1);
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xBC, 0, 0);
    menuCloseCustom(0xC2, 0, 0);
    menuCloseCustom(0x10E, 0, 0);
    menuCloseCustom(0x10F, 0, 0);
    menuCloseCustom(0x10D, 0, 0);
    menuCloseCustom(0xBF, 0, 0);
    menuCloseCustom(0xBE, 0, 0);
    menuCloseCustom(0xBD, 0, 0);
    menuCloseCustom(0xBB, 0, 1);
    if (first == 0) {
        GSfsysFree(0x88C);
        GSresFreeGroup(0x88C);
    }
}

static void _menuCBGCDelPokemon() {
    u32 i;
    Pokemon* cur;
    u32 index;
    u32 type;
    Pokemon* src;
    Pokemon* dst;
    switch (_CB.unkB0F8) {
    case 30:
        i = 0;
        break;
    case 31:
        i = 1;
        break;
    case 32:
        i = 2;
        break;
    case 33:
        i = 3;
        break;
    case 34:
        i = 4;
        break;
    case 35:
        i = 5;
        break;
    }
    type = backup_type[i];
    index = backup_index[i];
    backup_type[i] = 0;
    backup_index[i] = 0;
    menuCBGCEntryTypeIndex(backup_index, backup_type);
    cur = menuCBPokemonPtrGet(_CB.unkB1D4, _CB.unkB1D8);
    switch (pokecoloGetCountryCode()) {
    case 0:
        if (type != 6) {
            memcpy(menuCBPokemonPtrGet(type, index), cur, 0xC4);
            pokemonInit(cur);
        } else {
            CReliveHall::getPointer()->getStage(index >> 16)->insertDancer(*cur, 0);
        }
        break;
    case 1:
    case 2:
        memcpy(menuCBPokemonPtrGet(type, index), cur, 0xC4);
        pokemonInit(cur);
        break;
    }
    for (; i < 5; i++) {
        dst = menuCBPokemonPtrGet(7, i);
        backup_type[i] = backup_type[i + 1];
        backup_index[i] = backup_index[i + 1];
        backup_type[i + 1] = 0;
        backup_index[i + 1] = 0;
        src = menuCBPokemonPtrGet(7, i + 1);
        memcpy(dst, src, 0xC4);
        pokemonInit(src);
    }
    _CB.unkB100--;
}

static u8 menuCBGCEntry_ErrorDisp(u32 type, u32 index) {
    u32 idx = _CB.unkB100 - 1;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    toolBattleRuleErrorFlagClear(0, idx);
    menuCBRule_ErrorFlagSetPokemonGetTiming(_CB.hero, p, idx);
    _CB.errPlayer = 0;
    if (menuCB_Trainer_Error_Check(idx, -1)) {
        menuCBGCDelPokemon();
        _CB.unkB0FC = 2;
        if (_CB.err[_CB.errPlayer][idx].a7) {
            _CB.unkB1DC = 0x43AF;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a6) {
            _CB.unkB1DC = 0x43A2;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a5 || _CB.err[_CB.errPlayer][idx].a4) {
            _CB.unkB1DC = 0x43B0;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a3) {
            _CB.unkB1DC = 0x43A5;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a2) {
            _CB.unkB1DC = 0x43A6;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a1) {
            _CB.unkB1DC = 0x43A7;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a0 || _CB.err[_CB.errPlayer][idx].b1) {
            _CB.unkB1DC = 0x43A8;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b7) {
            _CB.unkB1DC = 0x43A9;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b6) {
            _CB.unkB1DC = 0x43AA;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b5) {
            _CB.unkB1DC = 0x43AB;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b4) {
            _CB.unkB1DC = 0x43AC;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b3) {
            _CB.unkB1DC = 0x43AD;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b2) {
            _CB.unkB1DC = 0x43AE;
            return 0;
        }
        return 0;
    }
    return 1;
}

static u8 _menuCBPokemonEntryGetlevel(Pokemon* p) {
    return pokemonGetStatus(p, 0, 0x7A, 0);
}

static u32 menuCBPokemonGetIndex(u32 type, u32 index) {
    switch (type) {
    case 4:
        break;
    case 5:
        index = (u16)index;
        break;
    case 6:
        index = (u16)index;
        break;
    case 7:
        index += 0x1E;
        break;
    }
    return index;
}

static Pokemon* menuCBPokemonPtrGet(u32 type, u32 index) {
    u16 lo;
    u32 hi;
    Pokemon* p;
    if ((u16)index >= 0x24) {
        return 0;
    }
    if ((u16)index >= 0x1E && (u16)index <= 0x23) {
        type = 7;
        index = (u16)index - 0x1E;
    }
    switch (type) {
    case 4:
        p = heroBiosGetPokemonPtr(savedataGetStatus(0, 2), (u16)index);
        break;
    case 5:
        p = PCBOX::getPointer()->getPokemon((s8)(index >> 16), (s8)(u16)index);
        break;
    case 6: {
        CReliveHall* hall = CReliveHall::getPointer();
        hi = index >> 16;
        CReliveStage* stage = hall->getStage(hi);
        lo = (u16)index;
        if (lo == 4) {
            p = stage->getVisitorPointer();
        } else {
            switch (pokecoloGetCountryCode()) {
            case 0:
                p = stage->getDancerPointer(lo);
                break;
            case 1:
            case 2:
                p = _CB.relive[hi][lo];
                break;
            }
        }
        break;
    }
    case 7:
        p = heroBiosGetPokemonPtr(_CB.hero, (u16)index);
        break;
    case 0:
    case 1:
    case 2:
    case 3:
        p = toolentryTaisenGetPokemonPtr(type, index);
        break;
    }
    return p;
}

extern "C" {
void fn_8007F43C(CBWin* win, CBItem* item, void* str, s32 unused, s32 y, s32 msg) {
    s16 w;
    s16 x;
    msgctrlSetValue(0x37, str);
    w = GSmsgGetRect(msg) >> 16;
    x = item->w / 2 - w / 2;
    GSmsgPrint2(win->layer, x, y, win->alpha | ~0xFF, msg);
}
}

static void _drawStrings(CBWin* win, void* str, long x, long y, u32 msg) {
    msgctrlSetValue(0x37, str);
    GSmsgPrint2(win->layer, x, y, win->alpha | ~0xFF, msg);
}

extern "C" {
void menuCB_SE_Stop(s32 id) {
    GSsndStop(id, 0, 0);
}

void menuCB_SE_Play(s32 id) {
    GSsndPlay(id, 0, 0);
}

void menuCB_Cursol_Disp_AlphaSet(CBWin* win, CBItem* item, u8 flag) {
    if (flag) {
        if (win->alpha == 0xFF) {
            item->alpha = _CB.unkB138;
        } else {
            item->alpha = win->alpha;
        }
    } else {
        if (win->alpha >= 0x7F) {
            item->alpha = 0x7F;
        } else {
            item->alpha = win->alpha;
        }
    }
}

void menuCB_AlphaGet(CBWin* win) {
    if (win->alpha == 0xFF) {
        _CB.unkB138 = menuSubAnimAlpha();
    } else {
        _CB.unkB138 = win->alpha;
    }
}

void menuCB_GCEntryCursolDisp(CBWin* win, void* unused, u8 flag) {
    f32 t;
    f32 k;
    s16 a;
    s16 b;
    s16 y;
    int n;
    u32 color;
    s16 x;
    MenuSpriteVal* v;
    if (flag) {
        t = _f_menuCB_circleAnimationTime / 0.5f;
        if (t > 0.5f) {
            t = 1.0f - t;
        }
        k = 2.0f * t;
        _f_menuCB_circleAnimationTime = _f_menuCB_circleAnimationTime + timeGetLastFrameSec();
        if (_f_menuCB_circleAnimationTime >= 0.5f) {
            _f_menuCB_circleAnimationTime = fmod(_f_menuCB_circleAnimationTime, 0.5);
        }
        color = win->alpha | ~0xFF;
        v = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x216));
        x = v->x;
        y = v->y;
        n = (s16)(5.0f * k);
        if (n > 4) {
            n = 4;
        }
        a = n + 4;
        menuPtSpriteDrawColor(0x216, a, a, x, y, color);
        b = 0x32 - n;
        menuPtSpriteDrawColor(0x216, b, a, -x, y, color);
        menuPtSpriteDrawColor(0x216, a, b, x, -y, color);
        menuPtSpriteDrawColor(0x216, b, b, -x, -y, color);
        menuPtSpriteDrawColor(0x214, 7, 0x23, color);
    }
}

void menuCB_GCPokemonHPandWAZA_MAX() {
    u32 i;
    for (i = 0; i < 6; i++) {
        Pokemon* p = menuCBPokemonPtrGet(4, i);
        if (p) {
            pokemonAllKaihuku(p);
        }
    }
}
}

extern "C" {
void menuCB_RuleMessageTblDisp(CBWin* win, CBItem* item, s32 idx) {
    u16 buf[0x1F];
    u16* s;
    s16 x;
    int i;
    if (idx >= 3) {
        msgctrlSetValue(0x37, &_CB.ruleStr[idx * 0x90]);
    } else {
        switch (idx) {
        case 0:
            s = GSmsgGetGSchar(0x4387);
            break;
        case 1:
            s = GSmsgGetGSchar(0x4389);
            break;
        case 2:
            s = GSmsgGetGSchar(0x4388);
            break;
        }
        for (i = 0; i < 0x1F; i++) {
            if (s) {
                if (*s == 0xFFFF) {
                    s += 2;
                }
                buf[i] = *s;
                if (*s) {
                    s++;
                }
            } else {
                buf[i] = 0;
            }
        }
        msgctrlSetValue(0x37, buf);
    }
    x = item->w / 2 - ((s16)(GSmsgGetRect(fn_8007E634(0x4276)) >> 16)) / 2;
    GSmsgPrint2(win->layer, x, 0, (*(u32*)&item->cr & ~0xFF) | win->alpha, fn_8007E634(0x4276));
}

void menuCB_RuleDispColorChenge_flag(CBWin* win, CBItem* item, u8 flag) {
    if (flag) {
        item->cb = 0xFF;
        item->cg = 0xFF;
        item->cr = 0xFF;
        item->alpha = _CB.unkB138;
    } else {
        item->cb = 0x7F;
        item->cg = 0x7F;
        item->cr = 0x7F;
        item->alpha = win->alpha;
    }
}

void menuCB_RuleDispColorChenge(CBWin* win, CBItem* item, u32 n) {
    if (n == _CB.unkB11C) {
        item->cb = 0xFF;
        item->cg = 0xFF;
        item->cr = 0xFF;
        item->alpha = _CB.unkB138;
    } else {
        item->cb = 0x7F;
        item->cg = 0x7F;
        item->cr = 0x7F;
        item->alpha = win->alpha;
    }
}
}

extern "C" {
void menuCB_RuleItemFlagDisp(CBWin* win, CBSprite* sprite) {
    s32 layer;
    CBMenuItem* base;
    CBMenuItem* item;
    s16 y;
    s32 first;
    s32 last;
    layer = winSpriteGetLayerID(win, sprite);
    base = menuItemBiosGetPtr(win->menuId, 0x3AB);
    item = menuItemBiosGetPtr(win->menuId, sprite->itemId);
    y = -(_CB.scroll * 0x18);
    if (_CB.scroll == 0) {
        first = 0;
    } else {
        first = _CB.scroll - 1;
        y += first * 0x18;
    }
    last = first + 0xD;
    if (last >= 0x3E) {
        last = 0x3E;
    }
    spriteSetScissor(layer, base->x - item->x, base->y - item->y, item->w, item->h);
    for (; first <= last; first++, y += 0x18) {
        if (first == 0x3E) {
            GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, 1);
        } else if (_CB.rule[first + 0x52]) {
            GSmsgPrint2(win->layer, 0, y, win->alpha | 0xFF3F0000, 0x43E4);
        } else {
            GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, 0x43E3);
        }
    }
    spriteClearScissor(layer);
}

void menuCB_RuleItemNameEntry(CBWin* win, CBSprite* sprite) {
    s32 layer;
    CBMenuItem* base;
    CBMenuItem* item;
    s16 y;
    s32 first;
    s32 last;
    s32 i;
    u16 id;
    layer = winSpriteGetLayerID(win, sprite);
    base = menuItemBiosGetPtr(win->menuId, 0x3AC);
    item = menuItemBiosGetPtr(win->menuId, sprite->itemId);
    y = -(_CB.scroll * 0x18);
    if (_CB.scroll == 0) {
        first = 0;
    } else {
        first = _CB.scroll - 1;
        y += first * 0x18;
    }
    last = first + 0xD;
    if (last >= 0x3E) {
        last = 0x3E;
    }
    spriteSetScissor(layer, base->x - item->x, base->y - item->y, item->w, item->h);
    for (i = first; i <= last; i++, y += 0x18) {
        id = menuCBRule_RegulationItemID(i);
        if (id == 0) {
            GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, 0x4345);
        } else {
            if (itemDataCheckValid(id)) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(id))));
            }
            GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, fn_8007E634(0x4276));
        }
    }
    spriteClearScissor(layer);
}
}

extern "C" {
void menuCBMessageYCenterDisp(CBWin* win, CBItem* item, s32 msg) {
    u16 h;
    s16 y;
    h = GSmsgGetRect(msg);
    y = item->h / 2 - (s16)h / 2;
    GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, msg);
}

void fn_80080390(CBWin* win, CBItem* item, s32 msg) {
    switch (pokecoloGetCountryCode()) {
    case 0:
        *(s32*)((u8*)item + 0x4C) = msg;
        break;
    case 1:
    case 2:
        menuCBMessageCenterDisp(win, item, msg);
        break;
    }
}

void menuCBMessageCenterDisp(CBWin* win, CBItem* item, s32 msg) {
    s16 w;
    s16 x;
    w = GSmsgGetRect(msg) >> 16;
    x = item->w / 2 - w / 2;
    GSmsgPrint2(win->layer, x, 0, (*(u32*)&item->cr & ~0xFF) | win->alpha, msg);
}

void menuCB_RuleNameChengeAfterJob(u8 first) {
    if (first) {
        GSfsysReadWait(0x88C);
        menuTopOpenFlashBack();
        menuCB_FlashStart(0);
        GSthreadSwitch();
        GSthreadSwitch();
        GSthreadSwitch();
        GSthreadSwitch();
    }
    menuCB_SE_Play(0x14);
    menuOpen(0xA9, 0);
    menuOpen(0xCE, 0);
    menuOpen(0xCB, 0);
    menuOpen(0xCC, 0);
    menuOpen(0xCD, 0);
    menuOpen(0xAA, 0);
    menuOpen(0xF7, 0);
}

void menuCB_RuleNameChengeBeforeJob(u8 first) {
    if (first) {
        menuCB_FlashEnd(1);
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xF7, 0, 0);
    menuCloseCustom(0xAA, 0, 0);
    menuCloseCustom(0xCD, 0, 0);
    menuCloseCustom(0xCC, 0, 0);
    menuCloseCustom(0xCB, 0, 0);
    menuCloseCustom(0xCE, 0, 0);
    menuCloseCustom(0xA9, 0, 1);
    if (first) {
        if (fightReadResourceID(0x842, 0x195F3400) == 0) {
            fightFreeResourceID(0x842, 0x195F3400);
        }
        GSfsysFree(0x88C);
        GSresFreeGroup(0x88C);
    }
}

void menuCB_MenuDispCheckONorOFF_RULE(CBWin* win, s32 idx) {
    bool on;
    if (_CB.unkB124 != -1) {
        menuSetDisp(win->menuId, 0);
        if (_CB.unkB124 == idx) {
            menuSetDisp(win->menuId, 1);
            win->alpha = _CB.unkB128;
        }
        if (_CB.unkB118 == idx) {
            menuSetDisp(win->menuId, 1);
            win->alpha = _CB.unkB12C;
        }
    } else {
        if (idx == 1) {
            on = false;
            if (_CB.unkB118 == idx || _CB.unkB118 == 5) {
                on = true;
            }
            menuCB_MenuDispCheckONorOFF(win, on);
            return;
        }
        menuCB_MenuDispCheckONorOFF(win, _CB.unkB118 == idx);
    }
}

void menuCB_MenuDispCheckONorOFF_TUNAIDESUB(CBWin* win, s32 idx) {
    if (_CB.unkB144 != -1) {
        menuSetDisp(win->menuId, 0);
        if (_CB.unkB144 == idx) {
            menuSetDisp(win->menuId, 1);
            win->alpha = _CB.unkB148;
        }
        if (_CB.unkAFE4 == idx) {
            menuSetDisp(win->menuId, 1);
            win->alpha = _CB.unkB14C;
        }
    } else {
        menuCB_MenuDispCheckONorOFF(win, _CB.unkAFE4 == idx);
    }
}

void menuCB_MenuDispCheckONorOFF(CBWin* win, bool on) {
    if (on) {
        menuSetDisp(win->menuId, 1);
    } else {
        menuSetDisp(win->menuId, 0);
    }
}

void menuCB_SpriteDispCheckONorOFF(CBSprite* sprite, bool on) {
    if (on) {
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}
}

extern "C" {
void menuCB_GCEntry_ItemKeepJob() {
    Pokemon* p;
    u8* hero;
    u16 item;
    u16 old;
    void* nick;
    p = menuCBPokemonPtrGet(_CB.unkB1D4, _CB.unkB1D8);
    nick = pokemonBiosGetNicknamePtr(p);
    hero = _CB.hero;
    msgctrlSetValue(0x32, nick);
    item = pokemonGetSoubiItemDataId(p);
    if (item != 0) {
        if (heroItemCheckAddItemDataId(hero, item) <= 0) {
            _menuCB_errorMsgDisp2(0x3ACF);
            return;
        }
        heroItemAddItemDataId(hero, item, 1, -1);
        old = pokemonDoItemSoubi(p, 0, 0);
        msgctrlSetValue(0x2D, (void*)old);
        _menuCB_errorMsgDisp2(0x3ACD);
    } else {
        _menuCB_errorMsgDisp2(0x3ACE);
    }
}
}

extern "C" {
void menuCB_GCEntry_ItemGiveJob() {
    Pokemon* p;
    s8 answer;
    u8 slot;
    u8* hero;
    u16 chosen;
    u32 idx;
    u16 old;
    u16 cur;
    void* nick;
    p = menuCBPokemonPtrGet(_CB.unkB1D4, _CB.unkB1D8);
    nick = pokemonBiosGetNicknamePtr(p);
    hero = _CB.hero;
    msgctrlSetValue(0x32, nick);
    if (menuCBBios_CurrentRule()->unk8 == 1) {
        _menuCB_errorMsgDisp(0x43A9);
        return;
    }
    menuOpen(0xE6, 1);
    chosen = menuPocket2Call(5, 0, hero);
    slot = menuPocket2GetLastSlotID();
    menuCloseCustom(0xE6, 0, 1);
    if (chosen != 0) {
        idx = (u16)_CB.unkB1D8 - 0x1E;
        toolBattleRuleErrorFlagClear(0, idx);
        old = pokemonDoItemSoubi(p, 0, 0);
        pokemonDoItemSoubi(p, chosen, 1);
        menuCBRule_ErrorFlagSetItemGetTiming(hero, p, idx);
        pokemonDoItemSoubi(p, 0, 0);
        pokemonDoItemSoubi(p, old, 1);
        if (menuCB_Trainer_Error_Check(idx, 9)) {
            _menuCB_errorMsgDisp(0x43AA);
            return;
        }
        if (menuCB_Trainer_Error_Check(idx, 10)) {
            _menuCB_errorMsgDisp(0x43AB);
            return;
        }
        if (menuCB_Trainer_Error_Check(idx, 11)) {
            _menuCB_errorMsgDisp(0x43AC);
            return;
        }
        cur = pokemonGetSoubiItemDataId(p);
        if (cur != 0) {
            msgctrlSetValue(0x2D, (void*)cur);
            winMsgOpen(2, 0x3ACA, 1, 0);
            switch (pokecoloGetCountryCode()) {
            case 0:
                answer = menuSubOpenYesNo(0, 0x3C, 0xD2, 0);
                break;
            case 1:
            case 2:
                answer = menuSubOpenYesNo(0, 0x3C, 0xC8, 0);
                break;
            }
            winMsgClose(1);
            if (answer == 0) {
                if (heroItemDecItemDataId(hero, chosen, 1, slot) != 0) {
                    _menuCB_errorMsgDisp2(0x3ACF);
                    return;
                }
                if (heroItemCheckAddItemDataId(hero, cur) <= 0) {
                    heroItemAddItemDataId(hero, chosen, 1, -1);
                    _menuCB_errorMsgDisp2(0x3ACF);
                    return;
                }
                heroItemAddItemDataId(hero, cur, 1, -1);
                old = pokemonDoItemSoubi(p, 0, 0);
                pokemonDoItemSoubi(p, chosen, 1);
                msgctrlSetValue(0x2D, (void*)old);
                msgctrlSetValue(0x2E, (void*)chosen);
                _menuCB_errorMsgDisp2(0x3ACB);
            }
        } else if (heroItemDecItemDataId(hero, chosen, 1, slot) == 0) {
            pokemonDoItemSoubi(p, chosen, 1);
            msgctrlSetValue(0x2D, (void*)chosen);
            _menuCB_errorMsgDisp2(0x3ACC);
        }
    }
}
}

extern "C" {
void menuCBRULE_EditNameDispLarge(CBWin* win, s32 idx) {
    u16 buf[0x1F];
    u16* s;
    int i;
    s32 n;
    if (idx >= 3) {
        msgctrlSetValue(0x37, &_CB.ruleStr[idx * 0x90]);
    } else {
        switch (idx) {
        case 0:
            s = GSmsgGetGSchar(0x4387);
            break;
        case 1:
            s = GSmsgGetGSchar(0x4389);
            break;
        case 2:
            s = GSmsgGetGSchar(0x4388);
            break;
        }
        for (i = 0; i < 0x1F; i++) {
            if (s) {
                if (*s == 0xFFFF) {
                    s += 2;
                }
                buf[i] = *s;
                if (*s) {
                    s++;
                }
            } else {
                buf[i] = 0;
            }
        }
        msgctrlSetValue(0x37, buf);
    }
    GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4275);
    if (_CB.unkB118 == 5) {
        msgctrlSetValue(0x34, (void*)2);
    } else {
        msgctrlSetValue(0x34, (void*)(_CB.unkB118 + 1));
    }
    msgctrlSetValue(0x2F, (void*)_CB.unkB1E0);
    GSmsgPrint2(win->layer, 0x1CE, 0, win->alpha | ~0xFF, 0x427A);
    GSmsgPrint2(win->layer, 0x1E4, 2, win->alpha | ~0xFF, 0x4417);
    msgctrlSetValue(0x34, (void*)(n = _CB.unkB014 != -1 ? 5 : 4));
    msgctrlSetValue(0x2F, (void*)n);
    GSmsgPrint2(win->layer, 0x1FA, 0, win->alpha | ~0xFF, 0x427A);
}

void menuCBRULE_EditNameDisp(CBWin* win, CBItem* item, s32 idx) {
    msgctrlSetValue(0x37, &_CB.ruleStr[idx * 0x90]);
    GSmsgPrint2(win->layer, 0, 0, (*(u32*)&item->cr & ~0xFF) | win->alpha, 0x4277);
}

void menuCB_GCEntry_PokemonStatusDisp() {
    Pokemon* p = menuCBPokemonPtrGet(_CB.unkB1D4, _CB.unkB1D8);
    _menuCB_PokemonStatusDispBeforeJob(0);
    menuPokemonStatusOpenFromPokemonChange(p, 0, 0);
    _menuCB_PokemonStatusDispAfterJob(0);
}
}

extern "C" {
bool toolBattle_tunaideMenu02menuTempBuffGet(u32 mask) {
    return (_CB.tempBuff & mask) != 0;
}

void toolBattle_tunaideMenu02menuTempBuffSet(u32 mask) {
    if (_CB.tempBuff & mask) {
        return;
    }
    _CB.tempBuff |= mask;
}

void toolBattleRuleErrorFlagClear(s32 player, u32 idx) {
    *(s32*)&_CB.err[player][idx] = 0;
}

void menuCBPokemonName(CBWin* win, u32 a, u32 b, u32 c) {
    _menuCBPokemonName(win, a, b, c, false);
}

void menuCBPokemonName_nido(CBWin* win, u32 a, u32 b, u32 c) {
    _menuCBPokemonName(win, a, b, c, true);
}

s32 menuCBPokemonGetItemDataId(u32 a, u32 b) {
    return pokemonGetSoubiItemDataId(toolentryTaisenGetPokemonPtr(a, b)) != 0;
}

void menuCBpokemonFaceReadWait() {
    for (;;) {
        if (menuCBPokemonEntryGetReadFlag()) {
            break;
        }
        GSthreadSwitch();
    }
}

void menuCBtrainerFaceReadWait() {
    for (;;) {
        if (_menuCBBattleStartWork.a == _menuCBBattleStartWork.b) {
            break;
        }
        GSthreadSwitch();
    }
}

u8 menuCBPokemonCheck(u32 a, u32 b) {
    Pokemon* p = menuCBPokemonPtrGet(a, b);
    if (p && pokemonCheckValid(p)) {
        return 1;
    }
    return 0;
}

void menuCB_PrintXP(CBWin* win, s32 player) {
    menuCB_SetSprite(win, menuSpriteBiosGetPtr(BATTLE_BA_XP_PRINT_Char[toolentryTaisenGetBattlePlayerID(player)]));
}

void menuCB_BattleEntryPokemonSelectDisp(CBSprite* sprite, u32 a, u32 b) {
    menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonCheck(a, b) == 0);
}
}

extern "C" {
u8 menuCBPokemonEntryDisp(CBSprite* sprite) {
    u8 ok = 1;
    switch ((u16)toolentryTaisenGetHomePlace(0)) {
    case 0:
        winSpriteSetDisp(sprite, 1);
        break;
    default:
        winSpriteSetDisp(sprite, 0);
        ok = 0;
        break;
    }
    return ok;
}

void menuCBPokemonEntryGCControlDisp(CBSprite* sprite, s32 b) {
    if (menuCBPokemonEntryDisp(sprite)) {
        if (!menuCBPokemonGetDataId(0, b)) {
            winSpriteSetDisp(sprite, 0);
        }
    }
}

u8 menuCBPokemonEntryDispPokemonFace_AFTER(s32 a, s32 b, s32 c, s32 d) {
    if (menuCBBattleStartGetStatus() != 0) {
        menuCBPokemonEntryDispPokemonFace(a, b, c, d);
        return 1;
    }
    return 0;
}

u8 menuCBPokemonEntryDispPokemonFace_BEFORE(s32 a, s32 b, s32 c, s32 d) {
    if (menuCBBattleStartGetStatus() == 0) {
        menuCBPokemonEntryDispPokemonFace(a, b, c, d);
        return 1;
    }
    return 0;
}

u8 menuCB_GCStatusDispMode(CBSprite* sprite, s32 mode) {
    if (_CB.unk8 == 2) {
        if (mode == 0) {
            winSpriteSetDisp(sprite, 1);
            return 1;
        }
        winSpriteSetDisp(sprite, 0);
        return 0;
    }
    if (mode == 1) {
        winSpriteSetDisp(sprite, 1);
        return 1;
    }
    winSpriteSetDisp(sprite, 0);
    return 0;
}

void menuCB_WaitGCControler1() {
    if (!GSinputIsConnected(1)) {
        winMsgOpen(2, gbaCommandIsConnected(1) ? 0x442D : 0x4436, 0, 0);
        while (!GSinputIsConnected(1)) {
            GSthreadSwitch();
        }
        winMsgClose(1);
    }
}

void menuCB2DPokemonItemDisp(CBSprite* sprite, u32 a, u32 b) {
    Pokemon* p = menuCBPokemonPtrGet(a, b);
    winSpriteSetDisp(sprite, 0);
    if (p && pokemonCheckValid(p) && pokemonGetSoubiItemDataId(p)) {
        winSpriteSetDisp(sprite, 1);
    }
}

u8 menuCBPokemonGetDataId(s32 a, s32 b) {
    Pokemon* p;
    if (menuCBBattleStartGetStatus() == 0) {
        p = toolentryTaisenGetPokemonPtr(a, b);
    } else if (toolentryTaisenGetEntryPokemonNum(a) <= b) {
        p = 0;
    } else {
        p = toolentryTaisenGetEntryPokemonPtr(a, b);
    }
    if (p) {
        return pokemonCheckValid(p) != 0;
    }
    return 0;
}

void toobattle_drawHeroName(CBWin* win, s32 player) {
    _drawStrings(win, heroBiosGetNamePtr((u8*)&_CB + player * 0x1320 + 0x563C), 0, 0, fn_8007E634(0x4276));
}

void toobattle_drawHeroNames(CBWin* win, s32 player) {
    _drawStrings(win, heroBiosGetNamePtr((u8*)&_CB + player * 0x1320 + 0x9BC), 0, 0, fn_8007E634(0x4278));
}

void menuCBPokemonTYPE1(CBWin* win, u32 a, u32 b) {
    Pokemon* p = menuCBPokemonPtrGet(a, b);
    u16 id = pokemonGetStatus(p, 0, 0x6E, 0);
    u16 sprite = zokuseiGetPokemonSpriteID(pokemonDataBiosGetPtr(id), 0);
    if (sprite) {
        windowDrawSprite(0, 0, win, sprite, 0, win->layer);
    }
}
}
