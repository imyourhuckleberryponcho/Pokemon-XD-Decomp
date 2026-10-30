#pragma peephole off
#pragma pool_strings off
#include <dolphin/types.h>
#include <game/shared/menu_work.h>

struct KeyInfo {
    u16 on;
    u16 up;
    u16 trg;
    u16 rep;
    u16 rel;
    u8 pad_a[0x10];
};

struct MenuData {
    u8 unk0[6];
    s16 firstItem;
};

struct MenuItem {
    u8 flagA : 1;
    u8 flagB : 1;
    u8 unk0b : 6;
    u8 unk1[5];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    u8 unkE[0xA];
    s16 next;
};

class DarkPokemon;

class Pokemon {
public:
    void* getPokemonDataPtr() const;
    u8 data[0xC4];
};

class Hero {
public:
    Hero() {}
    Pokemon* getPokemon(s32 index);
    static Hero* getHeroPtr();
    u8 data[0x978];
};

struct DISK_ENTRY {
    u8 id;
    u8 pad1;
    u16 itemId;
    u32 name;
    u32 doc;
    u32 expl1;
    u32 expl2;
    u32 title;
};

struct BDISK {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 mode;
    s16 count;
    s16 row;
    s16 scrollY;
    s16 scrollTarget;
    s16 savedCursor;
    s16 cursor;
    u8 pokeNum;
    u8 selectId;
    u16 result;
    u16 f1a;
    u16 f1c;
    u8 pad1e[2];
    f32 timer;
    s32 docMenu;
    DISK_ENTRY disks[60];
    Hero hero[2];
    u8 pad18b8[8];
    BDISK() {
        count = row = scrollTarget = savedCursor = scrollY = 0;
    }
};

BDISK gBDisk;

extern "C" u32 heroGetPokeomCount(Hero* hero);
static inline bool isMine() {
    s16 c = gBDisk.cursor;
    return (u32)c < heroGetPokeomCount(&gBDisk.hero[0]);
}

struct ItemSlot {
    u8 d[4];
};

class cBattleDisk {
public:
    static s32 mItemCurIdx[8];
    static s32 mContentsCurIdx[15];
};
s32 cBattleDisk::mItemCurIdx[8] = {0x6F9, 0x6FB, 0x6FD, 0x6FF, 0x701, 0x703, 0x705, 0x707};
s32 cBattleDisk::mContentsCurIdx[15] = {0x76F, 0x770, 0x771, 0x772, 0x773, 0x774, 0x775, 0x776,
                                        0x777, 0x778, 0x7B6, 0x7B7, 0x7B8, 0x7B9, 0x7BA};

static s16 sRect[56] = {
    216, 6, 42, 42,
    0, 0, -264, 54,
    19, 7, 133, 18,
    30, 29, 95, 18,
    126, 29, 80, 18,
    154, 7, 19, 18,
    9, 29, 20, 15,
    6, 6, 42, 42,
    0, 0, 264, 54,
    64, 7, 133, 18,
    75, 29, 95, 18,
    171, 29, 80, 18,
    199, 7, 19, 18,
    54, 29, 20, 15,
};

struct GSvec2 {
    f32 x;
    f32 y;
};

struct CURSOR {
    s16 top;
    s16 pos;
};

struct PokemonData;
struct FightEncountData;

u32 deckDataVirtualDB_GetEnemyDeck(u16);
u32 deckDataVirtualDB_GetAllyDeck(u16);
u8 deckDataVirtualDB_GetPokemonNum(u16);
u32 deckDataVirtualDB_GetExplanetion1(u16);
u32 deckDataVirtualDB_GetExplanetion2(u16);
u32 deckDataVirtualDB_GetTitle(u16);
bool deckDataVirtualDB_GetFlagData(u16);

static int getPanelIdx(u32 slot, u8 pokeNum);
static void drawPkmPanel(u32 idx, tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
static void dispFace(u32 slot, GSvec2* pos, tagWINDOW_WORK* w, tagSPRITE_WORK* sp, Pokemon* pk);
static void* loadPkmFace(void* arg);

extern "C" {
tagSPRITE_WORK* windowGetCursorToItem(tagWINDOW_WORK*);
KeyInfo* windowGetKeyInfo(void);
KeyInfo* windowGetKeyInfo2(void);
MenuData* menuDataBiosGetPtr(s32 menuID);
MenuItem* menuItemBiosGetPtr(s32 menuID, u32 index);
bool winSeqCheckMove(s32 menuID);
void winSeqSetMenu(s32 menuID, u32 id);
void menuSetPosition(s32 menuID, s32 x, s32 y);
u16 windowGetKeyRepeat(void);
void menuPlaySe(void* seq, s32);
void menuCursorNormal(tagWINDOW_WORK*, s32);
void fightFreeResourceID(s32, s32);
u8 fightReadResourceID(s32, s32);
void* heroItemGetItemKindToItemAryPtr(Hero*, u8, u16*, u16*, u8*, u8*);
u8 itemCheckValid(void* item);
u16 itemBiosGetItemDataId(u8* p);
u8* itemDataBiosGetPtr(u16 index);
u32 itemDataBiosGetName(u8* p);
u32 itemDataBiosGetDoc(u8* p);
void menuItemBiosSetSelectFlag(s32 menuID, u32 index, bool flag);
bool menuItemBiosGetSelectFlag(s32 menuID, u32 index);
void menuClose(s32 menuID);
void menuCloseSync(s32 menuID, s32);
void menuCloseCustom(s32 menuID, s32, s32);
s32 menuOpen(s32 menuID, s32);
s32 menuOpenCustom(s32 menuID, ...);
s32 windowGetActiveID(void);
tagWINDOW_WORK* windowSearchID(s32 id);
void windowCreateCursorSprite(tagWINDOW_WORK*);
u8 GSgfxVideoGetVsyncRate(void);
void menuCreateOffScreen(f32, f32);
void menuReleaseOffScreen(f32);
u8 menuOffScreenSetPriority(u8 val);
void menuOffScreenFadeSync(u8 param);
u8 GSfloorPush(u32 id);
u8 GSfloorPop(void);
void floorSetFadeScript(u32 out, u32 in);
void floorWaitForChange(void);
void GSthreadSwitch(void);
f32 timeGetLastFrameSec(void);
s32 winSpriteGetLayerID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on);
void msgctrlSetValue(s32 id, u32 value);
u32 heroGetPokeomCount(Hero* hero);
u32 pokemonGetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index);
s32 wazaGetStatus(void* ptr, u16 dataID, u16 status, u32 index);
u16 pokemonGetSoubiItemDataId(Pokemon* pokemon);
s32 menuSubGetPokemonSexForDisp(void* pokemon);
u32 pokemonDataBiosGetZokuseiDataId(PokemonData* pdata, u16 index);
u32 pokemonDataBiosGetStatusFaceMenuSpriteId(PokemonData* pdata, u16 unk);
u32 zokuseiGetPokemonSpriteID(void*, u16);
u16 zokuseiBiosGetSpriteID(u16 id);
Pokemon* heroBiosGetPokemonPtr(Hero* hero, u16 index);
u16* heroBiosGetNamePtr(Hero* hero);
char* GSmsgGetGSchar(u32 msg);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
void GSmsgPrint2(s32, s32, s32, u32, s32);
void windowDrawSprite(s16 x, s16 y, void* ctx, u16 key, u32 flags, s32 layer);
void windowDrawSprite2(s16 x, s16 y, s16 w, s16 h, u32 color, void* ctx, u16 key, u32 flags, s32 layer);
u32 FlashSystemGetNowFrame(u32);
u32 FlashSystemGetEndFrame(u32);
void spriteSetScissor(s32, s32, s32, s32, s32);
void spriteClearScissor(s32);
void menuPdaSubScrollBar(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32, u32, s32, s32, s16*);
void menuFaceDispFromID2(tagWINDOW_WORK*, tagSPRITE_WORK*, u16, GSvec2*);
void menuFaceLoad(s32, void* (*)(void*), void*);
u8 menuFaceCheckLoading(void);
void* memcpy(void* dst, const void* src, u32 n);
FightEncountData* fightEncountDataBiosGetPtr(u16 id);
void fightEncountDataBiosSetDiskId(FightEncountData* data, u16 value);
void fightTrainerCreateFightTrainerDataIdToHero(u16 id, s32 allowNoAi, Hero* hero, u16 encountId);
u16 fightEncount(u16);
void winMsgOpen(s8 type, void* msg, bool a, bool b);
void winMsgClose(bool flag);
}

extern "C" void fn_8009E6B8(tagWINDOW_WORK* w, bool pad);

extern "C" {

s32 fn_8009E664(tagWINDOW_WORK* w) {
    if (winSeqCheckMove(0xEC)) {
        return 0;
    }
    fn_8009E6B8(w, true);
    return 0;
}

void fn_8009E6B8(tagWINDOW_WORK* win, bool pad) {
    MenuItem* item;
    int idx;
    MenuItem* from;
    int up, down, left, right;
    int xr, yr;
    tagWINDOW_WORK* w = win;
    MenuData* data;
    int best;
    u16 rep;
    if (w == 0) {
        return;
    }
    data = menuDataBiosGetPtr(w->menuID);
    from = (MenuItem*)windowGetCursorToItem(w);
    if (from == 0) {
        w->cursor = 0;
        return;
    }
    yr = 0xC;
    xr = 0x10;
    rep = windowGetKeyInfo()->rep;
    u16 on = windowGetKeyInfo()->on;
    u16 add;
    if (pad) {
        if ((on & 0xF) != 0) {
            add = 0;
        } else {
            add = windowGetKeyInfo2()->rep;
        }
    } else {
        add = 0;
    }
    rep |= add;
    up = rep & 1;
    down = rep & 2;
    left = rep & 4;
    right = rep & 8;
    do {
        idx = 0;
        item = menuItemBiosGetPtr(w->menuID, data->firstItem);
        if (up) {
            best = 0x1E0;
            while (1) {
                if (item->flagA) {
                    int dy = from->y - item->y;
                    if (dy > 0) {
                        int dx = from->x - item->x;
                        if (dx < 0) dx = -dx;
                        if (dx < xr && best > dy) {
                            best = dy;
                            w->cursor = (s8)idx;
                        }
                    }
                    idx++;
                }
                if (item->flagB) break;
                item = menuItemBiosGetPtr(w->menuID, item->next);
            }
        } else if (down) {
            best = 0x1E0;
            while (1) {
                if (item->flagA) {
                    int dy = item->y - from->y;
                    if (dy > 0) {
                        int dx = from->x - item->x;
                        if (dx < 0) dx = -dx;
                        if (dx < xr && best > dy) {
                            best = dy;
                            w->cursor = (s8)idx;
                        }
                    }
                    idx++;
                }
                if (item->flagB) break;
                item = menuItemBiosGetPtr(w->menuID, item->next);
            }
        } else if (left) {
            best = 0x280;
            while (1) {
                if (item->flagA) {
                    int dx = from->x - item->x;
                    if (dx > 0x1E) {
                        int dy = from->y - item->y;
                        if (dy < 0) dy = -dy;
                        if (dy < yr && best > dx) {
                            best = dx;
                            w->cursor = (s8)idx;
                        }
                    }
                    idx++;
                }
                if (item->flagB) break;
                item = menuItemBiosGetPtr(w->menuID, item->next);
            }
        } else if (right) {
            best = 0x280;
            while (1) {
                if (item->flagA) {
                    int dx = item->x - from->x;
                    if (dx > 0x1E) {
                        int dy = from->y - item->y;
                        if (dy < 0) dy = -dy;
                        if (dy < yr && best > dx) {
                            best = dx;
                            w->cursor = (s8)idx;
                        }
                    }
                    idx++;
                }
                if (item->flagB) break;
                item = menuItemBiosGetPtr(w->menuID, item->next);
            }
        }
        if (w->prevCursor != w->cursor) {
            break;
        }
        xr += 0x10;
        yr += 0xC;
        if (yr >= 0x1E0) yr = 0x1E0;
        if (xr >= 0x280) xr = 0x280;
    } while (xr != 0x280 || yr != 0x1E0);
}

s32 fn_8009E9FC(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x17B);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

s32 fn_8009EA68(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            if (isMine()) {
                winSeqSetMenu(w->menuID, 0x1EE);
            } else {
                winSeqSetMenu(w->menuID, 0x1E6);
            }
            w->seqSet = 1;
        }
        break;
    case 2:
        if (gBDisk.f0 != gBDisk.f4) {
            gBDisk.f0 = gBDisk.f4;
        }
        if (gBDisk.f2 != gBDisk.f6) {
            gBDisk.f2 = gBDisk.f6;
        }
        if (!winSeqCheckMove(0xEC)) {
            if (isMine()) {
                gBDisk.f4 = 0x131;
                gBDisk.f6 = 0;
            } else {
                gBDisk.f4 = 0;
                gBDisk.f6 = 0;
            }
            menuSetPosition(0xEC, gBDisk.f0, gBDisk.f2);
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            if (isMine()) {
                winSeqSetMenu(w->menuID, 0x1F2);
            } else {
                winSeqSetMenu(w->menuID, 0x1EA);
            }
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

s32 BattleDiskStatus(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    Pokemon* pk;
    int slot = 0;
    int layer = winSpriteGetLayerID(w, sp);
    Hero* hero = &gBDisk.hero[0];
    u32 n = heroGetPokeomCount(hero);
    int cur = gBDisk.cursor;
    Hero* hh;
    if ((u32)cur < n) {
        hh = hero;
    } else {
        hh = &gBDisk.hero[1];
        cur -= n;
    }
    pk = hh->getPokemon(cur);
    switch (sp->id) {
    case 0x791: {
        msgctrlSetValue(0x37, pokemonGetStatus(pk, 0, 0x77, 0));
        GSmsgPrintRect(layer, 0, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4277);
        break;
    }
    case 0x792: {
        u32 msg;
        switch ((u8)menuSubGetPokemonSexForDisp(pk)) {
        case 0:
            msg = 0x9C5;
            break;
        case 1:
            msg = 0x9C6;
            break;
        case 2:
        default:
            msg = 0;
            break;
        }
        if (msg != 0) {
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            GSmsgPrint2(layer, 0, 0, w->alpha | 0xFFFFFF00, 0x4276);
        }
        break;
    }
    case 0x793: {
        msgctrlSetValue(0x34, pokemonGetStatus(pk, 0, 0x7A, 0));
        GSmsgPrintRect(layer, 0x24, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x426F);
        break;
    }
    case 0x7FA: {
        msgctrlSetValue(0x34, pokemonGetStatus(pk, 0, 0x83, 0));
        GSmsgPrintRect(layer, 0x24, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x426F);
        break;
    }
    case 0x78B: {
        u16 sid = zokuseiGetPokemonSpriteID(pk->getPokemonDataPtr(), 0);
        if (sid != 0) {
            windowDrawSprite(0, 0, w, sid, 0, winSpriteGetLayerID(w, sp));
        }
        break;
    }
    case 0x78C: {
        u8 t1 = (u8)pokemonDataBiosGetZokuseiDataId((PokemonData*)pk->getPokemonDataPtr(), 0);
        if (t1 != (u8)pokemonDataBiosGetZokuseiDataId((PokemonData*)pk->getPokemonDataPtr(), 1)) {
            u16 sid = zokuseiGetPokemonSpriteID(pk->getPokemonDataPtr(), 1);
            windowDrawSprite(0, 0, w, sid, 0, winSpriteGetLayerID(w, sp));
        }
        break;
    }
    case 0x790:
        slot = 1;
    case 0x78F:
        slot++;
    case 0x78E:
        slot++;
    case 0x78D: {
        int v = pokemonGetStatus(pk, 0, 0x7F, (u16)slot);
        switch (v) {
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
            break;
        case 0x176:
            windowDrawSprite(0, 0, w, 0x7B, 0, winSpriteGetLayerID(w, sp));
            break;
        default:
            windowDrawSprite(0, 0, w, zokuseiBiosGetSpriteID(wazaGetStatus(0, (u16)v, 3, 0)), 0,
                             winSpriteGetLayerID(w, sp));
            break;
        }
        break;
    }
    case 0x797:
        slot = 1;
    case 0x796:
        slot++;
    case 0x795:
        slot++;
    case 0x794: {
        u32 v = pokemonGetStatus(pk, 0, 0x7F, (u16)slot);
        if (v != 0) {
            if (wazaGetStatus(0, (u16)v, 1, 0) != 0) {
                msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(wazaGetStatus(0, (u16)v, 1, 0)));
                GSmsgPrintRect(winSpriteGetLayerID(w, sp), 0, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4277);
            }
        }
        break;
    }
    case 0x79D:
        msgctrlSetValue(0x34, pokemonGetStatus(pk, 0, 0x88, 0));
        GSmsgPrintRect(winSpriteGetLayerID(w, sp), 0, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4287);
        break;
    case 0x79E:
        msgctrlSetValue(0x34, pokemonGetStatus(pk, 0, 0x89, 0));
        GSmsgPrintRect(winSpriteGetLayerID(w, sp), 0, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4287);
        break;
    case 0x79F:
        msgctrlSetValue(0x34, pokemonGetStatus(pk, 0, 0x8A, 0));
        GSmsgPrintRect(winSpriteGetLayerID(w, sp), 0, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4287);
        break;
    case 0x7A0:
        msgctrlSetValue(0x34, pokemonGetStatus(pk, 0, 0x8B, 0));
        GSmsgPrintRect(winSpriteGetLayerID(w, sp), 0, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4287);
        break;
    case 0x7A1:
        msgctrlSetValue(0x34, pokemonGetStatus(pk, 0, 0x8C, 0));
        GSmsgPrintRect(winSpriteGetLayerID(w, sp), 0, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4287);
        break;
    case 0x7A3:
        if (pokemonGetSoubiItemDataId(pk) != 0) {
            msgctrlSetValue(0x2D, pokemonGetSoubiItemDataId(pk));
            GSmsgPrintRect(winSpriteGetLayerID(w, sp), 0, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x3AE7);
        } else {
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0x3C1A));
            GSmsgPrintRect(winSpriteGetLayerID(w, sp), 0, 0, sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4277);
        }
        break;
    }
    return 0;
}

s32 BattleDiskBorADraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    GSvec2 pos;
    Hero* h;
    int slot;
    pos.x = 0.0f;
    pos.y = 0.0f;
    slot = 0;
    switch (sp->id) {
    case 0x738:
        slot = 1;
    case 0x737:
        slot++;
    case 0x736:
        slot++;
    case 0x735:
        slot++;
    case 0x734:
        slot++;
    case 0x733: {
        h = &gBDisk.hero[0];
        if (heroGetPokeomCount(h) > slot) {
            dispFace(slot, &pos, w, sp, heroBiosGetPokemonPtr(h, (u16)slot));
        }
        break;
    }
    case 0x744:
        slot = 1;
    case 0x743:
        slot++;
    case 0x742:
        slot++;
    case 0x741:
        slot++;
    case 0x740:
        slot++;
    case 0x73F: {
        h = &gBDisk.hero[1];
        if (heroGetPokeomCount(h) > slot) {
            dispFace(slot, &pos, w, sp, heroBiosGetPokemonPtr(h, (u16)slot));
        }
        break;
    }
    case 0x73E:
        slot = 1;
    case 0x73D:
        slot++;
    case 0x73C:
        slot++;
    case 0x73B:
        slot++;
    case 0x73A:
        slot++;
    case 0x739:
        winSpriteSetDisp(sp, 0);
        if (slot < heroGetPokeomCount(&gBDisk.hero[0])) {
            winSpriteSetDisp(sp, 1);
        }
        break;
    case 0x74A:
        slot = 1;
    case 0x749:
        slot++;
    case 0x748:
        slot++;
    case 0x747:
        slot++;
    case 0x746:
        slot++;
    case 0x745:
        winSpriteSetDisp(sp, 0);
        if (slot < heroGetPokeomCount(&gBDisk.hero[1])) {
            winSpriteSetDisp(sp, 1);
        }
        break;
    case 0x74B:
        sp->msgID = 0;
        switch (gBDisk.result) {
        case 2:
        case 3:
            sp->msgID = deckDataVirtualDB_GetExplanetion2(gBDisk.selectId);
            break;
        }
        break;
    case 0x74C:
        sp->msgID = 0;
        switch (gBDisk.result) {
        case 2:
        case 3:
            sp->msgID = itemDataBiosGetName(itemDataBiosGetPtr((u16)(gBDisk.selectId + 0x215)));
            break;
        default:
            sp->msgID = deckDataVirtualDB_GetTitle(gBDisk.selectId);
            break;
        }
        break;
    case 0x74D:
        msgctrlSetValue(0x37, (u32)heroBiosGetNamePtr(&gBDisk.hero[1]));
        GSmsgPrint2(winSpriteGetLayerID(w, sp), 0, 0, w->alpha | 0xFFFFFF00, 0x4276);
        break;
    case 0x74E:
        msgctrlSetValue(0x37, (u32)heroBiosGetNamePtr(&gBDisk.hero[0]));
        GSmsgPrint2(winSpriteGetLayerID(w, sp), 0, 0, w->alpha | 0xFFFFFF00, 0x4276);
        break;
    case 0x7F2:
        switch (gBDisk.result) {
        case 2:
        case 3:
            windowDrawSprite(0, 0, w, 0x303, 0, winSpriteGetLayerID(w, sp));
            break;
        default:
            windowDrawSprite(0, 0, w, 0x305, 0, winSpriteGetLayerID(w, sp));
            break;
        }
        break;
    case 0x7F3:
        switch (gBDisk.result) {
        case 2:
            windowDrawSprite(0, 0, w, 0x314, 0, winSpriteGetLayerID(w, sp));
            gBDisk.f1a = FlashSystemGetNowFrame(0x1F333000);
            gBDisk.f1c = FlashSystemGetEndFrame(0x1F333000);
            break;
        case 3:
        case 4:
        case 7:
            windowDrawSprite(0, 0, w, 0x315, 0, winSpriteGetLayerID(w, sp));
            gBDisk.f1a = FlashSystemGetNowFrame(0x1F343000);
            gBDisk.f1c = FlashSystemGetEndFrame(0x1F343000);
            break;
        default:
            windowDrawSprite(0, 0, w, 0x316, 0, winSpriteGetLayerID(w, sp));
            gBDisk.f1a = FlashSystemGetNowFrame(0x1F353000);
            gBDisk.f1c = FlashSystemGetEndFrame(0x1F353000);
            break;
        }
    case 0x877:
    case 0x878:
    case 0x879:
    case 0x87A:
    case 0x87B:
    case 0x87C:
    case 0x87D:
    case 0x87E:
        switch (gBDisk.result) {
        case 2:
        case 3:
        case 4:
        case 7:
            winSpriteSetDisp(sp, 0);
            break;
        default:
            winSpriteSetDisp(sp, 1);
            break;
        }
        break;
    }
    return 0;
}

s32 BattleDiskContentsDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    u32 slot = 0;
    switch (sp->id) {
    case 0x751:
    case 0x752:
        break;
    case 0x753:
        if (gBDisk.pokeNum == 1) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x754:
    case 0x755:
        if (gBDisk.pokeNum == 2) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x756:
        if (gBDisk.pokeNum == 2) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x76E:
        slot = 1;
    case 0x76D:
        slot++;
    case 0x76C:
        slot++;
    case 0x76B:
        slot++;
    case 0x76A:
        slot++;
    case 0x769:
        slot++;
    case 0x768:
        slot++;
    case 0x767:
        slot++;
    case 0x766:
        slot++;
    case 0x765:
        slot++;
    case 0x764:
        slot++;
    case 0x763:
        slot++;
    case 0x762:
        slot++;
    case 0x761:
        slot++;
    case 0x760: {
        BDISK* d = &gBDisk;
        if (getPanelIdx(slot, d->pokeNum) >= 0) {
            drawPkmPanel(getPanelIdx(slot, d->pokeNum), w, sp);
        }
        break;
    }
    case 0x779:
    case 0x77A:
    case 0x77B:
    case 0x77C:
    case 0x77D:
    case 0x77E:
    case 0x77F:
    case 0x780:
    case 0x781:
    case 0x782:
    case 0x783:
    case 0x784:
    case 0x785:
    case 0x786:
    case 0x787:
    case 0x788:
    case 0x789:
    case 0x78A:
    case 0x78B:
    case 0x78C:
    case 0x78D:
    case 0x78E:
    case 0x78F:
    case 0x790:
    case 0x791:
    case 0x792:
    case 0x793:
    case 0x794:
    case 0x795:
    case 0x796:
    case 0x797:
    case 0x798:
    case 0x799:
    case 0x79A:
    case 0x79B:
    case 0x79C:
    case 0x79D:
    case 0x79E:
    case 0x79F:
    case 0x7A0:
    case 0x7A1:
    case 0x7A2:
    case 0x7A3:
    case 0x7A4:
    case 0x7A5:
    case 0x7A6:
    case 0x7A7:
    case 0x7A8:
    case 0x7A9:
    case 0x7AA:
    case 0x7AB:
    case 0x7AC:
    case 0x7AD:
    case 0x7AE:
    case 0x7AF:
    case 0x7B0:
    case 0x7B1:
    case 0x7B2:
    case 0x7B3:
    case 0x7B4:
    case 0x7B5:
        break;
    case 0x7BB:
        sp->msgID = deckDataVirtualDB_GetExplanetion2(gBDisk.selectId);
        break;
    case 0x7BC:
        if (w->menuID != windowGetActiveID()) {
            sp->msgID = 0xE2E2;
        } else {
            sp->msgID = 0xE300;
        }
        break;
    case 0x7BD:
        if (w->menuID == windowGetActiveID()) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x7BE:
        if (w->menuID != windowGetActiveID()) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    }
    return 0;
}

}

static int getPanelIdx(u32 slot, u8 pokeNum) {
    int r = -1;
    switch (slot) {
    case 0:
        r = 0;
        break;
    case 1:
        if (pokeNum == 2) r = 1;
        break;
    case 2:
        if (pokeNum == 1) r = 1;
        break;
    case 3:
        r = 2;
        break;
    case 4:
        r = 3;
        break;
    case 5:
        r = 4;
        break;
    case 6:
        r = 5;
        break;
    case 7:
        if (pokeNum != 2 || (s32)heroGetPokeomCount(&gBDisk.hero[1]) != 1) r = 6;
        break;
    case 8:
        if (pokeNum == 2 && (s32)heroGetPokeomCount(&gBDisk.hero[1]) == 1) r = 6;
        break;
    case 9:
        if (pokeNum == 2 && (s32)heroGetPokeomCount(&gBDisk.hero[1]) != 1) r = 7;
        break;
    case 10:
        if (pokeNum == 1) r = 7;
        break;
    case 11:
        r = 8;
        break;
    case 12:
        r = 9;
        break;
    case 13:
        r = 10;
        break;
    case 14:
        r = 11;
        break;
    }
    return r;
}

static void drawPkmPanel(u32 idx, tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int layer = winSpriteGetLayerID(w, sp);
    u32 n = idx;
    int base;
    Hero* hero;
    int off;
    if (idx < 6) {
        base = 0;
        hero = &gBDisk.hero[0];
        if (gBDisk.timer < 0.2f) {
            off = (int)(1280.0f * gBDisk.timer + -256.0f);
        } else {
            off = 0;
        }
    } else {
        n = idx - 6;
        hero = &gBDisk.hero[1];
        base = 7;
        if (gBDisk.timer < 0.2f) {
            off = (int)(256.0f - 1280.0f * gBDisk.timer);
        } else {
            off = 0;
        }
    }
    if (heroGetPokeomCount(hero) > n) {
        s16 offs = off;
        GSvec2 pos;
        pos.x = offs + sRect[base * 4];
        pos.y = sRect[base * 4 + 1];
        Pokemon* pk = heroBiosGetPokemonPtr(hero, (u16)n);
        if (pk != 0) {
            u32 v77 = pokemonGetStatus(pk, 0, 0x77, 0);
            u32 v83 = pokemonGetStatus(pk, 0, 0x83, 0);
            u32 v7a = pokemonGetStatus(pk, 0, 0x7A, 0);
            dispFace(idx, &pos, w, sp, pk);
            windowDrawSprite2((s16)(offs + sRect[(base + 1) * 4]), sRect[(base + 1) * 4 + 1], sRect[(base + 1) * 4 + 2], sRect[(base + 1) * 4 + 3],
                              w->alpha | 0xFFFFFF00, w, 0x2FC, 0, layer);
            msgctrlSetValue(0x37, v77);
            GSmsgPrintRect((u16)layer, offs + sRect[(base + 2) * 4], sRect[(base + 2) * 4 + 1], sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4277);
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0x42D4));
            GSmsgPrintRect(layer, offs + sRect[(base + 3) * 4], sRect[(base + 3) * 4 + 1], sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4276);
            msgctrlSetValue(0x34, v7a);
            GSmsgPrintRect(layer, offs + sRect[(base + 3) * 4] + 0x18, sRect[(base + 3) * 4 + 1], sp->w, sp->h,
                           w->alpha | 0xFFFFFF00, 0x426F);
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0x42D5));
            GSmsgPrintRect(layer, offs + sRect[(base + 4) * 4], sRect[(base + 4) * 4 + 1], sp->w, sp->h, w->alpha | 0xFFFFFF00, 0x4276);
            msgctrlSetValue(0x34, v83);
            GSmsgPrintRect(layer, offs + sRect[(base + 4) * 4] + 0x1C, sRect[(base + 4) * 4 + 1], sp->w, sp->h,
                           w->alpha | 0xFFFFFF00, 0x426F);
            u32 msg;
            switch ((u8)menuSubGetPokemonSexForDisp(pk)) {
            case 0:
                msg = 0x9C5;
                break;
            case 1:
                msg = 0x9C6;
                break;
            case 2:
            default:
                msg = 0;
                break;
            }
            if (msg != 0) {
                msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
                GSmsgPrint2(layer, offs + sRect[(base + 5) * 4], sRect[(base + 5) * 4 + 1], w->alpha | 0xFFFFFF00, 0x4276);
            }
            if (pokemonGetSoubiItemDataId(pk) != 0) {
                windowDrawSprite2((s16)(offs + sRect[(base + 6) * 4]), sRect[(base + 6) * 4 + 1], sRect[(base + 6) * 4 + 2],
                                  sRect[(base + 6) * 4 + 3], w->alpha | 0xFFFFFF00, w, 0x14B, 0, layer);
            }
        }
    }
}

static void dispFace(u32 slot, GSvec2* pos, tagWINDOW_WORK* w, tagSPRITE_WORK* sp, Pokemon* pk) {
    u32 face = pokemonDataBiosGetStatusFaceMenuSpriteId((PokemonData*)pk->getPokemonDataPtr(), 0);
    u8 save[0x78];
    memcpy(save, sp, 0x78);
    sp->h = 0x2A;
    sp->w = 0x2A;
    if (slot < 6) {
        sp->w *= -1;
    }
    menuFaceDispFromID2(w, sp, face, pos);
    memcpy(sp, save, 0x78);
}

static void* loadPkmFace(void* arg) {
    Pokemon* r = 0;
    if (*(u32*)arg < 12) {
        if (*(u32*)arg < 6) {
            Hero* h = &gBDisk.hero[0];
            if (*(u32*)arg < heroGetPokeomCount(h)) {
                r = heroBiosGetPokemonPtr(h, *(u32*)arg);
            } else {
                *(u32*)arg = 6;
            }
        }
        if (*(u32*)arg >= 6) {
            u16 i = *(u32*)arg % 6;
            Hero* h = &gBDisk.hero[1];
            if (i < heroGetPokeomCount(h)) {
                r = heroBiosGetPokemonPtr(h, i);
            }
        }
    }
    *(u32*)arg = *(u32*)arg + 1;
    return r;
}

extern "C" {

s32 BattleDiskItemDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int slot = 0;
    switch (sp->id) {
    case 0x6EF:
        if (gBDisk.row != 0) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x6EE:
        if (gBDisk.row < gBDisk.count - 8) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x708: {
        BDISK* d = &gBDisk;
        if (d->scrollY < d->scrollTarget) {
            d->scrollTarget -= 6;
        } else if (d->scrollY > d->scrollTarget) {
            d->scrollTarget += 6;
        }
        MenuItem* it = menuItemBiosGetPtr(w->menuID, 0x7B5);
        spriteSetScissor(winSpriteGetLayerID(w, sp), it->x - sp->x, it->y - sp->y, it->w, it->h);
        BDISK* d2 = &gBDisk;
        for (int i = 0; i < d2->count; i++) {
            s16 yy = d->scrollTarget + i * 0x1E;
            if (yy > -0x40 && yy < 0x1E0) {
                GSmsgPrint2(winSpriteGetLayerID(w, sp), 0, yy, w->alpha | 0xFFFFFF00, gBDisk.disks[i].name);
                if (deckDataVirtualDB_GetFlagData((u16)(gBDisk.disks[i].itemId - 0x215))) {
                    windowDrawSprite2(0xB2, (s16)(yy + 3), 0x16, 0xD, w->alpha | 0xFFFFFF00, w, 0x300, 0,
                                      winSpriteGetLayerID(w, sp));
                }
            }
        }
        spriteClearScissor(winSpriteGetLayerID(w, sp));
        break;
    }
    case 0x709:
        sp->msgID = gBDisk.disks[gBDisk.savedCursor + gBDisk.row].title;
        break;
    case 0x706:
        slot = 1;
    case 0x704:
        slot++;
    case 0x702:
        slot++;
    case 0x700:
        slot++;
    case 0x6FE:
        slot++;
    case 0x6FC:
        slot++;
    case 0x6FA:
        slot++;
    case 0x6F8:
        if (gBDisk.savedCursor == (s16)slot) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x6F9:
    case 0x6FB:
    case 0x6FD:
    case 0x70A:
    case 0x715:
    case 0x717:
        break;
    case 0x718:
        slot = 1;
    case 0x716:
        slot++;
    case 0x714:
        if (w->cursor == (s16)slot) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x727:
        sp->msgID = deckDataVirtualDB_GetTitle(gBDisk.selectId);
        break;
    case 0x729:
        sp->msgID = deckDataVirtualDB_GetExplanetion1(gBDisk.selectId);
        break;
    case 0x856: {
        CURSOR cur;
        cur.top = w->top;
        cur.pos = w->cursor;
        cur.top = gBDisk.row;
        menuPdaSubScrollBar(w, sp, w->menuID, 0x856, 0xF06422FF, gBDisk.count, 8, &cur.top);
        break;
    }
    }
    return 0;
}

s32 menuBdisk_selectL_Btn(tagWINDOW_WORK* w) {
    u16 rep = windowGetKeyRepeat();
    gBDisk.savedCursor = w->cursor;
    s16 row = gBDisk.row;
    if (rep & 2) {
        if (gBDisk.scrollTarget == gBDisk.scrollY && w->cursor == 7 && row < gBDisk.count - 8) {
            gBDisk.row++;
            gBDisk.scrollY = gBDisk.row * -0x1E;
            menuPlaySe((void*)w->menuID, 1);
        }
    } else if (rep & 1) {
        if (gBDisk.scrollTarget == gBDisk.scrollY && w->cursor == 0 && row != 0) {
            gBDisk.row--;
            gBDisk.scrollY = gBDisk.row * -0x1E;
            menuPlaySe((void*)w->menuID, 1);
        }
    } else if (rep & 4) {
        gBDisk.row -= 8;
        if (gBDisk.row < 0) {
            w->cursor = 0;
            gBDisk.savedCursor = 0;
            gBDisk.row = 0;
        }
        if (row != gBDisk.row) {
            menuPlaySe((void*)w->menuID, 6);
        }
        gBDisk.scrollTarget = gBDisk.scrollY = gBDisk.row * -0x1E;
    } else if (rep & 8) {
        s16 count = gBDisk.count;
        if (count < 8) {
            gBDisk.row = 0;
            gBDisk.savedCursor = w->cursor = count - 1;
        } else {
            gBDisk.row += 8;
            if (count - 8 < gBDisk.row) {
                gBDisk.row = count - 8;
                w->cursor = 7;
                gBDisk.savedCursor = 7;
            }
        }
        if (row != gBDisk.row) {
            menuPlaySe((void*)w->menuID, 6);
        }
        gBDisk.scrollTarget = gBDisk.scrollY = gBDisk.row * -0x1E;
    }
    menuCursorNormal(w, 1);
    return 0;
}

s32 fn_800A08C0(tagWINDOW_WORK* w) {
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
    return 0;
}

s32 menuBattleDiskCtrl(tagWINDOW_WORK* w) {
    return 0;
}

void menuBattleDiskExit(void) {
    fightFreeResourceID(0x842, 0x18513400);
}

static inline void tsLoopHelper1309() {
    for (int i = 0; i < 15; i++) {
        menuItemBiosSetSelectFlag(0x109, cBattleDisk::mContentsCurIdx[i], 0);
    }
}

void menuBattleDiskMain(void) {
    int arg1 = 0;
    int arg2;
    bool running;
    bool ok;
    Hero* hero0;
    int sel;
    Hero* hero1;
    int faceOut;
    running = true;
    switch (gBDisk.mode) {
    case 0: {
        hero0 = &gBDisk.hero[0];
        hero1 = &gBDisk.hero[1];
        while (running) {
            arg1 = gBDisk.savedCursor;
            sel = menuOpenCustom(0xE7, 0, &arg1, 0, 1, 0, 0);
            if (sel == -1) {
                menuClose(0xE7);
                running = false;
                gBDisk.selectId = 0;
                gBDisk.result = 0;
                continue;
            }
            gBDisk.savedCursor = sel;
            for (int i = 0; i < 6; i++) {
                GSthreadSwitch();
            }
            sel += gBDisk.row;
            int res = menuOpen(0xE8, 1);
            u8 id = gBDisk.disks[sel].id;
            faceOut = 0;
            fightEncountDataBiosSetDiskId(fightEncountDataBiosGetPtr(0xE), id);
            fightTrainerCreateFightTrainerDataIdToHero((u8)deckDataVirtualDB_GetAllyDeck(id), 0, hero0, 0xE);
            fightTrainerCreateFightTrainerDataIdToHero((u8)deckDataVirtualDB_GetEnemyDeck(id), 0, hero1, 0xE);
            menuFaceLoad(0, loadPkmFace, &faceOut);
            gBDisk.pokeNum = deckDataVirtualDB_GetPokemonNum(id);
            gBDisk.selectId = id;
            tsLoopHelper1309();
            while (menuFaceCheckLoading()) {
                GSthreadSwitch();
            }
            menuClose(0xE7);
            menuClose(0xE8);
            switch (res) {
            case 0:
                running = false;
                break;
            case 1: {
                gBDisk.timer = 0.0f;
                menuOpen(0xEB, 0);
                while (gBDisk.timer < 0.2f) {
                    GSthreadSwitch();
                    gBDisk.timer += timeGetLastFrameSec();
                }
                menuClose(0xEB);
                for (int i = 0; i < 15; i++) {
                    ok = true;
                    if (getPanelIdx(i, gBDisk.pokeNum) == -1) {
                        ok = false;
                    } else {
                        u32 p = getPanelIdx(i, gBDisk.pokeNum);
                        if (p < 6) {
                            if (heroGetPokeomCount(hero0) <= p) ok = false;
                        } else {
                            if (heroGetPokeomCount(hero1) <= p - 6) ok = false;
                        }
                    }
                    if (ok) {
                        switch (i) {
                        case 1:
                            if (gBDisk.pokeNum != 2) ok = false;
                            break;
                        case 2:
                            if (gBDisk.pokeNum != 1) ok = false;
                            break;
                        case 7:
                            if (gBDisk.pokeNum == 2 && heroGetPokeomCount(hero1) == 1) ok = false;
                            break;
                        case 8:
                            if (gBDisk.pokeNum != 2 || heroGetPokeomCount(hero1) != 1) ok = false;
                            break;
                        case 9:
                            if (menuItemBiosGetSelectFlag(0x109, cBattleDisk::mContentsCurIdx[8])) {
                                ok = false;
                            } else if (gBDisk.pokeNum != 2) {
                                ok = false;
                            }
                            break;
                        case 10:
                            if (menuItemBiosGetSelectFlag(0x109, cBattleDisk::mContentsCurIdx[8])) {
                                ok = false;
                            } else if (gBDisk.pokeNum != 1) {
                                ok = false;
                            }
                            break;
                        }
                    }
                    menuItemBiosSetSelectFlag(0x109, cBattleDisk::mContentsCurIdx[i], ok);
                }
                menuOpen(0x109, 0);
                int inner = true;
                while (inner) {
                    GSthreadSwitch();
                    if (windowGetKeyInfo()->trg & 0x10) {
                        gBDisk.cursor = windowSearchID(0x109)->cursor;
                        menuOpen(0xEC, 0);
                        while (1) {
                            u32 c = gBDisk.cursor;
                            if (c < heroGetPokeomCount(hero0)) {
                                gBDisk.f4 = 0x131;
                                gBDisk.f6 = 0;
                            } else {
                                gBDisk.f4 = 0;
                                gBDisk.f6 = 0;
                            }
                            menuSetPosition(0xEC, gBDisk.f0, gBDisk.f2);
                            GSthreadSwitch();
                            if (!(windowGetKeyInfo()->trg & 0x10)) {
                                fn_8009E6B8(windowSearchID(0x109), true);
                            }
                            if (gBDisk.cursor != windowSearchID(0x109)->cursor) {
                                windowCreateCursorSprite(windowSearchID(0x109));
                                s16 cc = windowSearchID(0x109)->cursor;
                                windowSearchID(0x109)->prevCursor = cc;
                                gBDisk.cursor = cc;
                                menuPlaySe((void*)0x109, 1);
                            }
                            if (windowGetKeyInfo()->trg & 0x20) break;
                        }
                        menuPlaySe((void*)0x109, 3);
                        menuClose(0xEC);
                        menuCloseSync(0xEC, 1);
                        menuOpen(0x109, 0);
                    } else if (windowGetKeyInfo()->trg & 0x20) {
                        inner = false;
                    }
                }
                menuClose(0x109);
                menuCloseSync(0x109, 1);
                break;
            }
            case 2:
                break;
            }
        }
        break;
    }
    case 1: {
        gBDisk.result = 0;
        menuOpen(0xEA, 0);
        
        while (1) {
            GSthreadSwitch();
            if (windowGetKeyInfo()->trg == 0x40) {
                winMsgOpen(2, (void*)deckDataVirtualDB_GetExplanetion1(gBDisk.selectId), 1, 1);
                do {
                    GSthreadSwitch();
                } while (!(windowGetKeyInfo()->trg & 0x60));
                winMsgClose(1);
            } else if (windowGetKeyInfo()->trg == 0x10) {
                break;
            }
        }
        gBDisk.result = fightEncount(0xE);
        menuOpen(0xEA, 0);
        GSthreadSwitch();
        
        while (gBDisk.f1a < gBDisk.f1c) {
            GSthreadSwitch();
        }
        while (!(windowGetKeyInfo()->trg & 0x30)) {
            GSthreadSwitch();
        }
        menuClose(0xEA);
        break;
    }
    case 2: {
        arg2 = 0;
        menuOpenCustom(0xE9, windowGetActiveID(), 0, 2, 0, 0);
        
        gBDisk.docMenu = menuOpenCustom(0x8F, 0, &arg2, 0, 1, 0);
        menuCloseCustom(0x8F, 0, 1);
        menuClose(0xE9);
        menuCloseSync(0xE9, 1);
        menuOffScreenSetPriority(1);
        break;
    }
    }
    GSfloorPop();
    if (gBDisk.mode == 0 || gBDisk.mode == 2) {
        floorSetFadeScript(0, 0);
    }
}

void menuBattleDiskInit(void) {
    int j;
    u16* itemId;
    u8* id;
    u16 v;
    Hero* hero = Hero::getHeroPtr();
    u16 n;
    ItemSlot* items = (ItemSlot*)heroItemGetItemKindToItemAryPtr(hero, 7, &n, 0, 0, 0);
    int count = 0;
    int i;
    fightReadResourceID(0x842, 0x18513400);
    for (i = 0; i < n; i++, items++) {
        if (itemCheckValid(items)) {
            v = itemBiosGetItemDataId((u8*)items);
            itemId = &gBDisk.disks[(u16)count].itemId;
            *itemId = v;
            gBDisk.disks[(u16)count].name = itemDataBiosGetName(itemDataBiosGetPtr(*itemId));
            gBDisk.disks[(u16)count].doc = itemDataBiosGetDoc(itemDataBiosGetPtr(*itemId));
            id = &gBDisk.disks[(u16)count].id;
            *id = *itemId - 0x215;
            gBDisk.disks[(u16)count].expl1 = deckDataVirtualDB_GetExplanetion1(*id);
            gBDisk.disks[(u16)count].expl2 = deckDataVirtualDB_GetExplanetion2(*id);
            gBDisk.disks[(u16)count].title = deckDataVirtualDB_GetTitle(*id);
            count++;
        }
    }
    gBDisk.count = count;
    for (j = 0; j < 8; j++) {
        if (j < gBDisk.count) {
            menuItemBiosSetSelectFlag(0xE8, cBattleDisk::mItemCurIdx[j], 1);
        } else {
            menuItemBiosSetSelectFlag(0xE8, cBattleDisk::mItemCurIdx[j], 0);
        }
    }
}

void menuBattleDiskCloseDoc(void) {
    menuClose(0xE9);
}

void menuBattleDiskOpenDoc(u8 id) {
    gBDisk.selectId = id;
    menuOpenCustom(0xE9, windowGetActiveID(), 0, 2, 0, 0);
}

s32 menuBattleDiskOpenDocPush(u8 id) {
    gBDisk.selectId = id;
    gBDisk.mode = 2;
    menuCreateOffScreen(8.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    menuOffScreenSetPriority(0);
    menuOffScreenFadeSync(1);
    GSfloorPush(0x38D);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(8.0f / GSgfxVideoGetVsyncRate());
    gBDisk.mode = 1;
    return gBDisk.docMenu;
}

u16 menuBattleDiskGetResult(void) {
    return gBDisk.result;
}

u8 menuBattleDiskGetSelectID(void) {
    return gBDisk.selectId;
}

void menuBattleDiskOpenFight(void) {
    if (gBDisk.selectId != 0) {
        gBDisk.mode = 1;
        GSfloorPush(0x389);
    }
}

void menuBattleDiskOpen(void) {
    gBDisk.mode = 0;
    menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    GSfloorPush(0x389);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(20.0f / GSgfxVideoGetVsyncRate());
}

}
