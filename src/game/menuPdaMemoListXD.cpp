#include <dolphin/types.h>

#pragma peephole off
#pragma opt_unroll_loops off

struct CURSOR {
    s16 top;
    s16 pos;
};

struct PokemonBuf {
    u8 data[0xC4];
};

struct MENU_MODEL {
    u8 unk0[0xEC];
};

struct MemoSortBuff {
    u16 index;
    u16 key;
    char name[0x18];
};

struct MenuItem {
    u8 unk0[6];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    s8 seqSet;
    u8 unk3;
    void* seq;
    u8 unk8[0x14];
    s32 layer;
    u8 unk20[0x73];
    u8 alpha;
    u8 unk94[8];
    s16 top;
    s16 pos;
    u8 unkA0[4];
    u8 unkA4;
    u8 unkA5;
};

struct tagSPRITE_WORK {
    u8 unk0[6];
    s16 id;
    u8 unk8[0x14];
    s32 layer;
    u8 unk20[0x47];
    s8 fade;
};

struct WindowKeyInfo {
    u16 unk0;
    u16 unk2;
    u16 trigger;
};

enum menuPdaMemoSort {
    MEMO_SORT_GOJYUON,
    MEMO_SORT_POKEMON_ID
};

struct AlphaSlot {
    u8 unk0[0x21C];
    f32 value;
};

class pdaMemoList {
public:
    pdaMemoList();
    ~pdaMemoList();
    void Sort(menuPdaMemoSort sort);
    void SortPokemonID();
    void SortGojyuon();
    void Sort_Small(MemoSortBuff* buf, long count);
    u16 SortGojyuonDataSet(u16 id);
    void DispList(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void DispPokemonModel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, unsigned long itemID);
    s32 GetPokemonName(long index);
    void ScrollBar(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void LoadHero(bool load);
    s32 TermThread(MENU_MODEL* model);
    void SetHeroMotion();
    void LoadPokemon(long index);
    void* GetPokemonPointer(long index);
    void ListCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    s32 GetMenuItemNumber(tagSPRITE_WORK* sprite);
    void DownCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void UpCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void Release();
    void InitWork();
    s32 Main(CURSOR* cursor);
    void Button(tagWINDOW_WORK* window);
    void Cursor(tagWINDOW_WORK* window);
    void Ctrl(tagWINDOW_WORK* window);
    void ListMain(tagWINDOW_WORK* window);
    void ListPosition();
    void CalcPosition(CURSOR* cursor);
    void _setCursor(CURSOR cursor);
    CURSOR _getCursor();
    void _menuClose(long menuID);

    u8 unk0[0x3C];
    u16* sortList;
    void* pokemon;
    MENU_MODEL model;
    MENU_MODEL heroModel;
    f32 alpha[8];
    u8 termModel;
    u8 heroLoaded;
    u8 heroMotion;
    s16 listTop;
    s16 listPos;
    f32 unk244;
    f32 unk248;
    f32 unk24C;
    f32 unk250;
    s32 unk254;
    s32 unk258;
    s32 unk25C;
    u32 thread;
};

extern "C" {
void fn_80055C94(pdaMemoList*, MemoSortBuff*, long);
void* __nw__FUl(unsigned long);
void* __nwa__FUl(unsigned long);
void __dl__FPv(void*);
void __dla__FPv(void*);
void* memcpy(void* dst, const void* src, unsigned long n);
s32 GScharCmp(const char*, const char*);
void GScharCpy(char*, s32);
s32 GSfloorGetCurrentFloorGroupID(void);
void* GSgfxLayerFindByID(s32);
s32 GSmsgGetGSchar(u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void GSsndPlayNow(u32);
void GSthreadClose(u32);
u32 GSthreadCreate(s32, s32, s32, s32, s32, s32 (*)(MENU_MODEL*));
u32 GSthreadGetCurrentThread(void);
u8 GSthreadIsRunning(u32);
void GSthreadSetArgs(u32, s32, ...);
void GSthreadSwitch(void);
CURSOR cursorBiosGetPos(s32);
CURSOR cursorBiosSetPos(s32, CURSOR);
void fn_80112AAC(MENU_MODEL*, void*);
s32 gamedataGetStatus(s32, s32);
s32 heroGetObjID(s32);
u16 memoDataGetCount(s32);
u16 memoDataGetPokemonID(s32, u16);
s32 memoDataGetPokemonRndFromID(s32, u16);
s32 memoDataGetPokemonTrainerRndFromID(s32, u16);
void menuClose(s32);
void menuCloseSync(s32, s32);
MenuItem* menuItemBiosGetPtr(s32, s32);
void menuModelAdjustCamera(MENU_MODEL*);
void menuModelAdjustCamera2(MENU_MODEL*, MENU_MODEL*);
u8 menuModelCheck(MENU_MODEL*, s32);
u8 menuModelComparePokemon(MENU_MODEL*, void*);
void menuModelFree(MENU_MODEL*);
void menuModelInit(MENU_MODEL*, s32, s32);
void menuModelLoad(MENU_MODEL*, s32);
void menuModelRender(MENU_MODEL*);
void menuModelRender2(MENU_MODEL*, MENU_MODEL*);
void menuModelRenderOffAll(MENU_MODEL*);
void menuModelSetAngle(MENU_MODEL*, f32*);
void menuModelSetMotion(MENU_MODEL*, s32);
void menuModelSetSize(MENU_MODEL*, s32, s32, s32, s32);
void menuModelSetZoom(MENU_MODEL*, f32);
void menuModelTerm(MENU_MODEL*);
s32 menuOpen(s32, s32);
s32 menuPdaMemoXDGetItem(void);
CURSOR* menuPdaMemoXDMain(CURSOR*);
void menuPdaSubCalcAlpha(f32*, s32, s32);
void menuPdaSubCalcPositon(f32*, f32, f32);
void menuPdaSubCheckUpDownCursor(tagWINDOW_WORK*, tagSPRITE_WORK*, s16*, s32, s32, s32);
void menuPdaSubInitAlpha(f32*, s32, s32);
void menuPdaSubScrollBar(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32, u32, s32, s32, s16*);
void msgctrlSetValue(s32, u32);
void peopleInfoBiosGetMotion(void*, s32, s32*, void*);
void* peopleInfoBiosGetPtr(s32);
s32 pokecoloGetCountryCode(void);
void pokemonBiosSetCatchTrainerRnd(void*, s32);
void pokemonBiosSetRnd(void*, s32);
void pokemonCreate(void*, u16, s32, s32);
u32 pokemonDataBiosGetName(void*);
void* pokemonDataBiosGetPtr(u16);
s32 pokemonGetStatus(void*, u16, s32, s32);
void spriteClearScissor(s32);
void spriteSetScissor(s32, s32, s32, s32, s32);
u8 winSeqCheckMove(void*);
void winSeqSetMenu(void*, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
void windowDrawSprite2(s16, s32, s32, s32, u32, tagWINDOW_WORK*, s32, s32, s32);
WindowKeyInfo* windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
s32 zokuseiBiosGetSmallSpriteID(u16);
extern u16* pdapokemonsortdata;
extern u32* pdapokemonsortdata_number;
}

static pdaMemoList* pMemoList;
static f32 _defaultAngle[3] = { 0.0f, -0.3f, 0.0f };
static s32 _testMotion = 3;

static s32 _menuPdaMemoListThread(MENU_MODEL* model) {
    if (pMemoList != 0) {
        return pMemoList->TermThread(model);
    }
    return 0;
}

extern "C" {

void menuPdaMemoListSetHeroMotion(void) {
    if (pMemoList != 0) {
        pMemoList->SetHeroMotion();
    }
}

u8 menuPdaMemoListIsLoadHero(void) {
    if (pMemoList != 0) {
        if (pMemoList->heroLoaded == 0) {
            return 0;
        }
        return menuModelCheck(&pMemoList->heroModel, 0);
    }
    return 0;
}

u8 menuPdaMemoListIsTermModel(void) {
    if (pMemoList != 0) {
        return pMemoList->termModel;
    }
    return 0;
}

void menuPdaMemoListLoadHero(bool load) {
    if (pMemoList != 0) {
        pMemoList->LoadHero(load);
    }
}

f32 menuPdaMemoListGetDefaultAngle(s16 index) {
    return _defaultAngle[index];
}

void menuPdaMemoListDispPokemonModel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, s32 kind) {
    if (pMemoList != 0) {
        unsigned long itemID;
        switch (kind) {
        case 0:
            itemID = 0xB9;
            break;
        case 1:
            itemID = 0xBB;
            break;
        case 2:
            itemID = 0xBA;
            break;
        case 3:
        default:
            itemID = 0x1C7;
            break;
        }
        pMemoList->DispPokemonModel(window, sprite, itemID);
    }
}

MENU_MODEL* menuPdaMemoListGetMenuModelWork(void) {
    if (pMemoList == 0) {
        return 0;
    }
    return &pMemoList->model;
}

void menuPdaMemoListLoadPokemon(long index) {
    if (pMemoList != 0) {
        pMemoList->LoadPokemon(index);
    }
}

u16 menuPdaMemoListGetPokemonID(long index);

void* menuPdaMemoListGetPokemonDataPointer(long index) {
    if (pMemoList == 0) {
        return 0;
    }
    return pokemonDataBiosGetPtr(menuPdaMemoListGetPokemonID(index));
}

s32 menuPdaMemoListGetPokemonName(long index) {
    if (pMemoList == 0) {
        return 0;
    }
    return pMemoList->GetPokemonName(index);
}

u16 menuPdaMemoListGetPokemonID(long index) {
    pdaMemoList* list = pMemoList;
    if (list == 0) {
        return 0;
    }
    if (index <= memoDataGetCount(0) && index >= 0) {
        return list->sortList[index];
    }
    return 0;
}

void menuPdaMemoListHook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0xDE:
    case 0xE0:
    case 0xE2:
    case 0xE4:
    case 0xE6:
    case 0xE8:
    case 0xEA:
    case 0xEC:
        pMemoList->ListCursor(window, sprite);
        break;
    case 0xDC:
        pMemoList->UpCursor(window, sprite);
        break;
    case 0xDD:
        pMemoList->DownCursor(window, sprite);
        break;
    case 0xDB:
        pMemoList->ScrollBar(window, sprite);
        break;
    case 0xF1:
        pMemoList->DispList(window, sprite);
        break;
    }
}

void menuPdaMemoList(void) {
    CURSOR cursor;
    pMemoList = new pdaMemoList;
    cursor.pos = 0;
    cursor.top = 0;
    menuOpen(0x7F, 0);
    menuOpen(0x77, 0);
    for (;;) {
        if (pMemoList->Main(&cursor) < 0) {
            break;
        }
        CURSOR* result = menuPdaMemoXDMain(&cursor);
        cursor.pos = result->pos;
        cursor.top = result->top;
        menuPdaSubInitAlpha(pMemoList->alpha, 8, result->pos);
        pMemoList->CalcPosition(&cursor);
        pMemoList->unk248 = pMemoList->unk250;
    }
    for (;;) {
        if (pMemoList->thread != 0) {
            if (GSthreadIsRunning(pMemoList->thread) == 0) {
                GSthreadClose(pMemoList->thread);
            } else {
                GSthreadSwitch();
                continue;
            }
        }
        break;
    }
    pMemoList->_menuClose(0x77);
    pMemoList->_menuClose(0x7F);
    delete pMemoList;
    pMemoList = 0;
}

void menuPdaMemoListButton(tagWINDOW_WORK* window) {
    if (pMemoList != 0) {
        pMemoList->Button(window);
    }
}

s32 menuPdaMemoListCursor(tagWINDOW_WORK* window) {
    if (pMemoList == 0) {
        return 0;
    }
    pMemoList->Cursor(window);
    return 0;
}

s32 menuPdaMemoListCtrl(tagWINDOW_WORK* window) {
    if (pMemoList == 0) {
        return 0;
    }
    pMemoList->Ctrl(window);
    return 0;
}

}

void pdaMemoList::Sort(menuPdaMemoSort sort) {
    switch (sort) {
    case MEMO_SORT_POKEMON_ID:
        SortPokemonID();
        break;
    case MEMO_SORT_GOJYUON:
        SortGojyuon();
        break;
    }
}

void pdaMemoList::SortPokemonID() {
    u16 id;
    MemoSortBuff* buf;
    u16* ids;
    int count = memoDataGetCount(0);
    buf = (MemoSortBuff*)new u8[0x2BC0];
    ids = (u16*)new u8[0x320];
    for (u16 i = 0; i < count; i++) {
        id = sortList[i];
        ids[i] = id;
        buf[i].key = id;
        buf[i].index = i;
    }
    Sort_Small(buf, count);
    for (u16 i = 0; i < count; i++) {
        sortList[i] = ids[buf[i].index];
    }
    if (buf != 0) {
        delete buf;
    }
    if (ids != 0) {
        delete ids;
    }
}

void pdaMemoList::SortGojyuon() {
    MemoSortBuff* buf;
    u16* ids;
    int count = memoDataGetCount(0);
    buf = (MemoSortBuff*)new u8[0x2BC0];
    ids = (u16*)new u8[0x320];
    for (u16 i = 0; i < count; i++) {
        u16 id = sortList[i];
        ids[i] = id;
        buf[i].key = SortGojyuonDataSet(id);
        buf[i].index = i;
        GScharCpy(buf[i].name, GetPokemonName(i));
    }
    if (pokecoloGetCountryCode() == 0) {
        Sort_Small(buf, count);
    } else {
        fn_80055C94(this, buf, count);
    }
    for (u16 i = 0; i < count; i++) {
        sortList[i] = ids[buf[i].index];
    }
    if (buf != 0) {
        delete buf;
    }
    if (ids != 0) {
        delete ids;
    }
}

void pdaMemoList::Sort_Small(MemoSortBuff* buf, long count) {
    MemoSortBuff tmp;
    for (long gap = count / 2; gap > 0; gap /= 2) {
        for (long i = gap; i < count; i++) {
            for (long j = i - gap; j >= 0 && buf[j].key >= buf[j + gap].key; j -= gap) {
                MemoSortBuff* a = &buf[j];
                MemoSortBuff* b = &buf[j + gap];
                memcpy(&tmp, a, sizeof(MemoSortBuff));
                memcpy(a, b, sizeof(MemoSortBuff));
                memcpy(b, &tmp, sizeof(MemoSortBuff));
            }
        }
    }
}

extern "C" {

void fn_80055C94(pdaMemoList* self, MemoSortBuff* buf, long count) {
    MemoSortBuff tmp;
    for (long gap = count / 2; gap > 0; gap /= 2) {
        for (long i = gap; i < count; i++) {
            for (long j = i - gap; j >= 0 && GScharCmp(buf[j].name, buf[j + gap].name) >= 0; j -= gap) {
                MemoSortBuff* a = &buf[j];
                MemoSortBuff* b = &buf[j + gap];
                memcpy(&tmp, a, sizeof(MemoSortBuff));
                memcpy(a, b, sizeof(MemoSortBuff));
                memcpy(b, &tmp, sizeof(MemoSortBuff));
            }
        }
    }
}

}

u16 pdaMemoList::SortGojyuonDataSet(u16 id) {
    u16* p = pdapokemonsortdata;
    if (id >= 0x8000) {
        id &= 0x3FFF;
    }
    for (u16 i = 0; i < *pdapokemonsortdata_number; i++) {
        if (*p == 0) {
            return 0;
        }
        if (id == *p) {
            return i;
        }
        p++;
    }
    return 0;
}

void pdaMemoList::DispList(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    CURSOR cursor = _getCursor();
    int count = memoDataGetCount(0);
    int layer = winSpriteGetLayerID(window, sprite);
    MenuItem* type1 = menuItemBiosGetPtr(0x78, 0xEF);
    MenuItem* type2 = menuItemBiosGetPtr(0x78, 0xF0);
    MenuItem* base = menuItemBiosGetPtr(0x78, 0xF1);
    MenuItem* area = menuItemBiosGetPtr(0x78, 0xEE);
    MenuItem* self = menuItemBiosGetPtr(0x78, sprite->id);
    int textLayer = layer;
    spriteSetScissor(layer, area->x - self->x, area->y - self->y, area->width, area->height);
    f32 y = unk248;
    f32 offset;
    if (pokecoloGetCountryCode() != 0) {
        offset = 0.0f;
    } else {
        offset = 0.0f;
    }
    for (s32 i = 0; i < count; i++) {
        if (i >= cursor.top - 1 && i < cursor.top + 9) {
            s32 name = GetPokemonName(i);
            void* mon = GetPokemonPointer(i);
            msgctrlSetValue(0x37, name);
            GSmsgPrint2(textLayer, 0, (s32)(y + offset), window->alpha | ~0xFF, 0x4277);
            u16 type = pokemonGetStatus(0, pokemonGetStatus(mon, 0, 0x6E, 0), 0x16, 0);
            u16 sprID = zokuseiBiosGetSmallSpriteID(type);
            windowDrawSprite2(type1->x - base->x, (s32)y, type1->width, type1->height, window->alpha | ~0xFF, window,
                              sprID, 0, layer);
            u16 type2ID = pokemonGetStatus(0, pokemonGetStatus(mon, 0, 0x6E, 0), 0x16, 1);
            if (type2ID != 0 && type2ID != type) {
                s32 sprID2 = zokuseiBiosGetSmallSpriteID(type2ID);
                windowDrawSprite2(type2->x - base->x, (s32)y, type2->width, type2->height, window->alpha | ~0xFF,
                                  window, (u16)sprID2, 0, layer);
            }
        }
        y += 27.0f;
    }
    spriteClearScissor(textLayer);
}

void pdaMemoList::DispPokemonModel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, unsigned long itemID) {
    MenuItem* item = menuItemBiosGetPtr(0x78, itemID);
    if (GSgfxLayerFindByID(window->layer) != 0) {
        menuModelSetSize(&model, item->x, item->y, item->width, item->height);
        if (menuModelCheck(&model, 0) == 0) {
            switch (menuPdaMemoXDGetItem()) {
            case 2:
                menuModelAdjustCamera2(&model, &heroModel);
                menuModelRender2(&model, &heroModel);
                break;
            case 1:
                menuModelAdjustCamera(&model);
                menuModelRender(&model);
                break;
            default:
                menuModelAdjustCamera(&model);
                menuModelRender(&model);
                break;
            }
        }
    }
}

s32 pdaMemoList::GetPokemonName(long index) {
    u16 id;
    if (index <= memoDataGetCount(0) && index >= 0) {
        id = sortList[index];
    } else {
        id = 0;
    }
    void* data = pokemonDataBiosGetPtr(id);
    if (data != 0) {
        return GSmsgGetGSchar(pokemonDataBiosGetName(data));
    }
    return 0;
}

void pdaMemoList::ScrollBar(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    int count = memoDataGetCount(0);
    CURSOR cursor = _getCursor();
    menuPdaSubScrollBar(window, sprite, 0x78, 0xDB, 0xF2642200, count, 8, &cursor.top);
}

void pdaMemoList::LoadHero(bool load) {
    if (load) {
        if (heroLoaded == 0) {
            menuModelInit(&heroModel, 0x280, 0x1E0);
            menuModelLoad(&heroModel, heroGetObjID(1));
            heroLoaded = 1;
            heroMotion = 0;
        }
    } else if (heroLoaded != 0) {
        if (GSthreadGetCurrentThread() != 0) {
            menuModelTerm(&heroModel);
        } else {
            menuModelRenderOffAll(&heroModel);
            termModel = 1;
            thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, _menuPdaMemoListThread);
            if (thread != 0) {
                GSthreadSetArgs(thread, 1, &heroModel);
            }
        }
        heroLoaded = 0;
    }
}

s32 pdaMemoList::TermThread(MENU_MODEL* m) {
    menuModelTerm(m);
    thread = 0;
    termModel = 0;
    return 1;
}

void pdaMemoList::SetHeroMotion() {
    if (heroMotion == 0) {
        s32 motion;
        u8 info[4];
        void* people = peopleInfoBiosGetPtr(heroGetObjID(1));
        peopleInfoBiosGetMotion(people, 1, &motion, info);
        motion = _testMotion;
        menuModelSetMotion(&heroModel, _testMotion);
        heroMotion = 1;
    }
}

void pdaMemoList::LoadPokemon(long index) {
    if ((int)memoDataGetCount(0) != 0) {
        void* mon = GetPokemonPointer(index);
        if (menuModelComparePokemon(&model, mon) == 0) {
            menuModelFree(&model);
            fn_80112AAC(&model, mon);
            menuModelRenderOffAll(&heroModel);
        }
    }
}

void* pdaMemoList::GetPokemonPointer(long index) {
    u16 id;
    if (index <= memoDataGetCount(0) && index >= 0) {
        id = sortList[index];
    } else {
        id = 0;
    }
    if (id != 0) {
        void* mon = pokemon;
        pokemonCreate(mon, id, 0xA, gamedataGetStatus(0, 1));
        s32 rnd = memoDataGetPokemonRndFromID(0, id);
        s32 trainerRnd = memoDataGetPokemonTrainerRndFromID(0, id);
        pokemonBiosSetRnd(mon, rnd);
        pokemonBiosSetCatchTrainerRnd(mon, trainerRnd);
        return mon;
    }
    return 0;
}

void pdaMemoList::ListCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s16 pos = window->pos;
    s32 n = GetMenuItemNumber(sprite);
    AlphaSlot* slot = (AlphaSlot*)((u8*)this + n * 4);
    sprite->fade = slot->value;
    if (pos == n) {
        winSpriteSetDisp(sprite, 1);
        return;
    }
    if (slot->value == 0.0f) {
        winSpriteSetDisp(sprite, 0);
    }
}

s32 pdaMemoList::GetMenuItemNumber(tagSPRITE_WORK* sprite) {
    const s32 ids[8] = { 0xDE, 0xE0, 0xE2, 0xE4, 0xE6, 0xE8, 0xEA, 0xEC };
    memoDataGetCount(0);
    s32 i;
    for (i = 0; i < 8; i++) {
        if (sprite->id == ids[i]) {
            break;
        }
    }
    return i;
}

void pdaMemoList::DownCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    CURSOR cursor = _getCursor();
    menuPdaSubCheckUpDownCursor(window, sprite, &cursor.top, memoDataGetCount(0), 8, 0);
}

void pdaMemoList::UpCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    CURSOR cursor = _getCursor();
    menuPdaSubCheckUpDownCursor(window, sprite, &cursor.top, memoDataGetCount(0), 8, 1);
}

void pdaMemoList::Release() {
    menuModelTerm(&model);
    menuModelTerm(&heroModel);
    if (sortList != 0) {
        delete[] sortList;
        sortList = 0;
    }
    if (pokemon != 0) {
        delete (PokemonBuf*)pokemon;
        pokemon = 0;
    }
}

void pdaMemoList::InitWork() {
    int count = memoDataGetCount(0);
    listPos = 0;
    listTop = 0;
    unk244 = 0.0f;
    unk248 = 0.0f;
    unk24C = 0.0f;
    unk250 = 0.0f;
    unk25C = 0;
    thread = 0;
    unk254 = 0;
    if (count >= 8) {
        unk258 = 8;
    } else {
        unk258 = count;
    }
    if (count != 0) {
        sortList = new u16[count];
        pokemon = new PokemonBuf;
    }
    MenuItem* item = menuItemBiosGetPtr(0x78, 0xBB);
    menuModelInit(&model, item->width, item->height);
    menuModelInit(&heroModel, 0x280, 0x1E0);
    menuModelTerm(&heroModel);
    s32 i = 0;
    s32 off = 0;
    while (i < memoDataGetCount(0)) {
        u16 id = memoDataGetPokemonID(0, (u16)i) & 0x3FFF;
        i++;
        *(u16*)((u8*)sortList + off) = id;
        off += 2;
    }
    Sort(MEMO_SORT_GOJYUON);
    menuPdaSubInitAlpha(alpha, 8, 0);
    LoadPokemon(0);
    heroLoaded = 0;
    heroMotion = 0;
    termModel = 0;
}

s32 pdaMemoList::Main(CURSOR* cursor) {
    int count = memoDataGetCount(0);
    CURSOR c;
    c.top = cursor->top;
    c.pos = cursor->pos;
    _setCursor(c);
    menuModelSetZoom(&model, 1.0f);
    s32 result;
    do {
        result = menuOpen(0x78, 1);
        c = _getCursor();
    } while (result != -1 && c.pos >= 8);
    _menuClose(0x78);
    if (result == -1 || count == 0) {
        return -1;
    }
    cursor->pos = c.pos;
    cursor->top = c.top;
    return c.top + c.pos;
}

void pdaMemoList::Button(tagWINDOW_WORK* window) {
    if (window != 0) {
        int count = memoDataGetCount(0);
        if (winSeqCheckMove(window->seq) == 0) {
            u16 trigger = windowGetKeyInfo()->trigger;
            if (count != 0 && (trigger & 0x10) != 0) {
                window->unkA4 = 1;
            }
            if ((trigger & 0x20) != 0) {
                window->unkA4 = 1;
                window->unkA5 = 1;
            }
        }
    }
}

void pdaMemoList::Cursor(tagWINDOW_WORK* window) {
    windowGetKeyInfo();
    CURSOR c = _getCursor();
    c.top = window->top;
    c.pos = window->pos;
    int visible;
    int count;
    count = memoDataGetCount(0);
    visible = 8;
    if (count < 8) {
        visible = count;
    }
    s32 prev = c.pos + c.top;
    u16 key = windowGetKeyRepeat();
    if ((key & 1) != 0) {
        if (prev != 0) {
            GSsndPlayNow(0x450);
        }
        c.pos -= 1;
    } else if ((key & 2) != 0) {
        if (count - 1 != prev) {
            GSsndPlayNow(0x450);
        }
        c.pos += 1;
    } else if ((key & 8) != 0) {
        if (count - 1 != prev) {
            GSsndPlayNow(0x453);
        }
        c.pos += visible;
    } else if ((key & 4) != 0) {
        if (prev != 0) {
            GSsndPlayNow(0x453);
        }
        c.pos -= visible;
    }
    if (c.pos < 0) {
        c.top += c.pos;
        c.pos = 0;
        if (c.top < 0) {
            c.top = 0;
            c.pos = 0;
        }
    } else if (c.pos >= visible) {
        s32 last = visible - 1;
        c.top = c.top + (c.pos - last);
        c.pos = last;
        if (c.top + last >= count) {
            c.pos = last;
            c.top = count - visible;
        }
    }
    _setCursor(c);
    window->top = c.top;
    window->pos = c.pos;
    if (prev != c.pos + c.top) {
        LoadPokemon(0);
    }
}

void pdaMemoList::Ctrl(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x132);
            window->seqSet = 1;
            f32 z = menuPdaMemoListGetDefaultAngle(2);
            f32 y = menuPdaMemoListGetDefaultAngle(1);
            f32 x = menuPdaMemoListGetDefaultAngle(0);
            f32 angle[3];
            angle[0] = x;
            angle[1] = y;
            angle[2] = z;
            menuModelSetAngle(menuPdaMemoListGetMenuModelWork(), angle);
        }
        break;
    case 2:
        ListMain(window);
        break;
    case 3:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x136);
            window->seqSet = 1;
        }
        break;
    }
}

void pdaMemoList::ListMain(tagWINDOW_WORK* window) {
    CURSOR c = _getCursor();
    ListPosition();
    CalcPosition(&c);
    menuPdaSubCalcAlpha(alpha, 8, c.pos);
}

void pdaMemoList::ListPosition() {
    if (unk244 != unk24C) {
        menuPdaSubCalcPositon(&unk244, unk24C, 10.0f);
    }
    if (unk248 != unk250) {
        menuPdaSubCalcPositon(&unk248, unk250, 10.0f);
    }
}

void pdaMemoList::CalcPosition(CURSOR* cursor) {
    unk250 = -cursor->top * 0x1B;
}

void pdaMemoList::_setCursor(CURSOR cursor) {
    cursorBiosSetPos(0xD, cursor);
}

CURSOR pdaMemoList::_getCursor() {
    return cursorBiosGetPos(0xD);
}

void pdaMemoList::_menuClose(long menuID) {
    menuClose(menuID);
    menuCloseSync(menuID, 1);
}

pdaMemoList::pdaMemoList() {
    sortList = 0;
    pokemon = 0;
    InitWork();
}

pdaMemoList::~pdaMemoList() {
    Release();
}
