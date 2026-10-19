#include <dolphin/types.h>

enum darkPokemonWhere { place0, place1, place2, place3, place4, place5, place6 };

class DarkPokemon {
public:
    u8 unk0x0[60];
    u16 getPokemonID() const;
    u8 getSnatchIndex() const;
    s32 getInitDarkPointDirect() const;
    s32 getDarkPointDirect() const;
    s32 getStatus() const;
    void setUpdate(bool update);
    bool isUpdate() const;
    bool isSnach() const;
    bool isRelive() const;
    void getPlace(darkPokemonWhere& where, u8& floor) const;
    f32 getDarkPoint() const;
    u16 getCatchBallID() const;
};
extern "C" DarkPokemon* darkPokemonGetDarkPokemon(u32 index);

// Menu files were built without the peephole optimizer.
#pragma peephole off

struct CURSOR {
    s16 top;
    s16 pos;
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
    u8 unk20[0x44];
    u32 color;
};

struct WindowKeyInfo {
    u16 unk0;
    u16 unk2;
    u16 trigger;
};

enum DPMSelSort {
    DPM_SORT_POKEMON,
    DPM_SORT_DP,
    DPM_SORT_PLACE
};

struct SnatchSortBuff {
    s32 key;
    u16 pokemonID;
    u16 darkID;
};

struct DPMIdPair {
    u16 pokemonID;
    u16 darkID;
};

class menuPdaDPMList {
public:
    menuPdaDPMList();
    ~menuPdaDPMList();
    u16 GetDarkPokemonID(long index);
    void ScrollBar(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void DispList(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void DownCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void UpCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void ListCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void SortCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void SetItemColor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    s32 SortPlace();
    u8 getTemochiIndex(u16 pokemonID, u16 darkID);
    s32 SortDP();
    s32 SortPokemon();
    void Button(tagWINDOW_WORK* window);
    void Cursor(tagWINDOW_WORK* window);
    s32 Sort(DPMSelSort sort);
    void SortSetTemp(SnatchSortBuff* dst, SnatchSortBuff* src, long count);
    void SortSub2(SnatchSortBuff* buf, long count, bool ascending);
    void SortSub(SnatchSortBuff* buf, long count, bool ascending);
    void Ctrl(tagWINDOW_WORK* window);
    void ListMain(tagWINDOW_WORK* window);
    void CalcPosition(CURSOR* cursor);
    void ListPosition();
    s32 Main(long unused, CURSOR* cursor);
    void InitWork();
    void _setCursor(CURSOR cursor);
    CURSOR _getCursor();
    void _menuClose(long menuID);

    s32 count;
    f32 alpha[10];
    s16 listTop;
    s16 listPos;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 sortKind;
    DPMIdPair* pairs;
    SnatchSortBuff* sorted;
    SnatchSortBuff* temp;
    SnatchSortBuff* temp2;
    s32 tempCount;
};

extern "C" {
void* __nw__FUl(unsigned long);
void* __nwa__FUl(unsigned long);
void __dl__FPv(void*);
void __dla__FPv(void*);
void* memcpy(void* dst, const void* src, unsigned long n);
u16 mballBiosGetSpriteID(u16);
s32 GSmsgGetGSchar(u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void GSsndPlayNow(u32);
CURSOR cursorBiosGetPos(s32);
CURSOR cursorBiosSetPos(s32, CURSOR);
s32 darkPokemonGetMeetNum(void);
s32 heroBiosGetPokemonPtr(s32, s32);
void menuClose(s32);
void menuCloseSync(s32, s32);
void menuDrawReliveMeterByDarkPokemon(DarkPokemon*, s32, s32, s32, s32, u8, s32);
void menuDrawReliveUpdate(void);
MenuItem* menuItemBiosGetPtr(s32, s32);
s32 menuOpen(s32, s32);
CURSOR* menuPdaDPMon(CURSOR*);
void menuPdaSetSubres(s32, s32);
void menuPdaSubCalcAlpha(f32*, s32, s32);
void menuPdaSubCalcPositon(f32*, f32, f32);
void menuPdaSubCheckUpDownCursor(tagWINDOW_WORK*, tagSPRITE_WORK*, s16*, s32, s32, s32);
void menuPdaSubInitAlpha(f32*, s32, s32);
void menuPdaSubScrollBar(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32, u32, s32, s32, s16*);
void msgctrlSetValue(s32, u32);
u16 pokemonBiosGetDarkpokemonDataId(s32);
u16 pokemonBiosGetPokemonDataId(s32);
u8 pokemonCheckValid(s32);
u32 pokemonDataBiosGetName(void*);
void* pokemonDataBiosGetPtr(u16);
s32 savedataGetStatus(s32, s32);
void spriteClearScissor(s32);
void spriteSetScissor(s32, s32, s32, s32, s32);
u8 winSeqCheckMove(void*);
void winSeqSetMenu(void*, s32);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
void windowDrawSprite2(s16, s32, s32, s32, u32, tagWINDOW_WORK*, s32, s32, s32);
WindowKeyInfo* windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
}

static menuPdaDPMList* pDPMList;

extern "C" {

s32 menuPdaDPMListGetDPointer(s32 index);
s32 menuPdaDPMListGetDarkPokemonPlace(s32 index, s32* where, u8* floor);
s32 menuPdaDPMListGetDPNum(void);

s32 menuPdaDPMListDispRelive(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, s32 x, s32 y, s32 index, u8 alpha,
                             u8 flag) {
    DarkPokemon* dark = (DarkPokemon*)menuPdaDPMListGetDPointer(index);
    s32 status = dark->getStatus();
    dark->getDarkPoint();
    switch (status) {
    case 0:
    case 1:
    case 2:
        break;
    case 3: {
        MenuItem* item = menuItemBiosGetPtr(0x74, 0x4A);
        menuDrawReliveMeterByDarkPokemon(dark, x, y, item->width, item->height, window->alpha, window->layer);
        break;
    }
    case 4:
        u32 name = GSmsgGetGSchar(0x3C0B);
        msgctrlSetValue(0x37, name);
        if (flag != 0) {
            GSmsgPrint2(window->layer, x, y, alpha | 0xEE444400, 0x4276);
        } else {
            GSmsgPrint2(window->layer, x, y, alpha | 0xEE444400, 0x4275);
        }
        break;
    }
    return 1;
}

u32 menuPdaDPMListGetDarkPokemonPlaceMsgID(s32 index, u8* floor) {
    s32 where;
    u32 msg = 0;
    menuPdaDPMListGetDarkPokemonPlace(index, &where, floor);
    switch (where) {
    case 0:
        msg = 0;
        break;
    case 1:
        msg = 0x3C0C;
        break;
    case 2:
        msg = 0x3C0E;
        break;
    case 3:
        msg = 0x3C0D;
        break;
    case 4:
        msg = 0x3B7A;
        break;
    case 5:
    case 6:
        msg = 0x3C0F;
        break;
    }
    return msg;
}

s32 menuPdaDPMListGetDarkPokemonPlace(s32 index, s32* where, u8* floor) {
    if (pDPMList == 0) {
        return 0;
    }
    DarkPokemon* dark = darkPokemonGetDarkPokemon(pDPMList->GetDarkPokemonID(index));
    switch (dark->getStatus()) {
    case 0:
    case 1:
    case 2:
        *where = 0;
        *floor = 0;
        break;
    case 3:
    case 4: {
        darkPokemonWhere w;
        u8 f;
        dark->getPlace(w, f);
        *where = w;
        *floor = f;
        break;
    }
    }
    return 1;
}

u16 menuPdaDPMListGetDarkPokemonID(s32 index) {
    if (pDPMList == 0) {
        return 0;
    }
    return pDPMList->GetDarkPokemonID(index);
}

u16 menuPdaDPMListGetPokemonID(s32 index) {
    if (pDPMList == 0) {
        return 0;
    }
    return darkPokemonGetDarkPokemon(pDPMList->GetDarkPokemonID(index))->getPokemonID();
}

u32 menuPdaDPMListGetPokemonName(s32 index) {
    if (pDPMList == 0) {
        return 0;
    }
    u16 id = darkPokemonGetDarkPokemon(pDPMList->GetDarkPokemonID(index))->getPokemonID();
    void* data = pokemonDataBiosGetPtr(id);
    if (data != 0) {
        return GSmsgGetGSchar(pokemonDataBiosGetName(data));
    }
    return 0;
}

u16 menuPdaDPMListGetDarkpokemonID(s32 index) {
    if (pDPMList != 0) {
        return pDPMList->GetDarkPokemonID(index);
    }
    return 0;
}

s32 menuPdaDPMListGetDPointer(s32 index) {
    return (s32)darkPokemonGetDarkPokemon(pDPMList->GetDarkPokemonID(index));
}

s32 menuPdaDPMListCallBack(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (pDPMList == 0) {
        return 0;
    }
    switch (sprite->id) {
    case 0x37:
        pDPMList->ScrollBar(window, sprite);
        break;
    case 0x4B:
        pDPMList->DispList(window, sprite);
        break;
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    case 0x40:
    case 0x41:
        pDPMList->ListCursor(window, sprite);
        break;
    case 0x46:
        pDPMList->UpCursor(window, sprite);
        break;
    case 0x47:
        pDPMList->DownCursor(window, sprite);
        break;
    case 0x1CD:
    case 0x1CE:
    case 0x1CF:
        pDPMList->SortCursor(window, sprite);
        break;
    case 0x4C:
    case 0x4D:
    case 0x4E:
        pDPMList->SetItemColor(window, sprite);
        break;
    }
    return 0;
}

s32 menuPdaDPMListGetDPNum(void) {
    if (pDPMList == 0) {
        return 0;
    }
    return pDPMList->count;
}

void menuPdaDPMListButton(tagWINDOW_WORK* window) {
    if (pDPMList != 0) {
        pDPMList->Button(window);
    }
}

s32 menuPdaDPMListCursor(tagWINDOW_WORK* window) {
    if (pDPMList == 0) {
        return 0;
    }
    pDPMList->Cursor(window);
    return 0;
}

s32 menuPdaDPMListCtrl(tagWINDOW_WORK* window) {
    if (pDPMList == 0) {
        return 0;
    }
    pDPMList->Ctrl(window);
    return 0;
}

void menuPdaDPMonList(void) {
    CURSOR cursor;
    s32 result = 0;
    pDPMList = new menuPdaDPMList;
    pDPMList->InitWork();
    cursor.pos = 0;
    cursor.top = 0;
    menuOpen(0x77, 0);
    for (;;) {
        result = pDPMList->Main(result, &cursor);
        if (result < 0) {
            break;
        }
        DarkPokemon* dark = darkPokemonGetDarkPokemon(menuPdaDPMListGetDarkPokemonID(cursor.pos + cursor.top));
        if (dark->isUpdate()) {
            dark->setUpdate(false);
        }
        CURSOR* c = menuPdaDPMon(&cursor);
        cursor.pos = c->pos;
        cursor.top = c->top;
        menuPdaSubInitAlpha(pDPMList->alpha, 10, c->pos);
        pDPMList->CalcPosition(&cursor);
        pDPMList->unk34 = pDPMList->unk3C;
    }
    pDPMList->_menuClose(0x77);
    delete pDPMList;
    pDPMList = 0;
}

}

menuPdaDPMList::~menuPdaDPMList() {
    if (pairs != 0) {
        delete[] pairs;
        pairs = 0;
    }
    if (sorted != 0) {
        delete[] sorted;
        sorted = 0;
    }
    if (temp != 0) {
        delete[] temp;
        temp = 0;
    }
    if (temp2 != 0) {
        delete[] temp2;
        temp2 = 0;
    }
}

menuPdaDPMList::menuPdaDPMList() {
    pairs = 0;
    sorted = 0;
    temp = 0;
    temp2 = 0;
    count = 0;
    tempCount = 0;
}

u16 menuPdaDPMList::GetDarkPokemonID(long index) {
    return sorted[index].darkID;
}

void menuPdaDPMList::ScrollBar(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    int n = count;
    CURSOR cursor = _getCursor();
    menuPdaSubScrollBar(window, sprite, 0x74, 0x37, 0xF2642200, n, 10, &cursor.top);
}

void menuPdaDPMList::DispList(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    CURSOR cursor = _getCursor();
    int n = count;
    MenuItem* base = menuItemBiosGetPtr(0x74, 0x4B);
    MenuItem* meter = menuItemBiosGetPtr(0x74, 0x4A);
    MenuItem* placeItem = menuItemBiosGetPtr(0x74, 0x49);
    MenuItem* ball = menuItemBiosGetPtr(0x74, 0x45);
    MenuItem* area = menuItemBiosGetPtr(0x74, 0x48);
    MenuItem* self = menuItemBiosGetPtr(0x74, sprite->id);
    spriteSetScissor(window->layer, area->x - self->x, area->y - self->y, area->width, area->height);
    f32 y = unk34;
    menuDrawReliveUpdate();
    for (s32 i = 0; i < n; i++) {
        if (i >= cursor.top - 1 && i < cursor.top + 11) {
            DarkPokemon* dark = darkPokemonGetDarkPokemon(GetDarkPokemonID(i));
            s32 color1;
            s32 color2;
            if (dark->isUpdate()) {
                color1 = 0xD5AA3300;
                color2 = 0xD5AA3300;
            } else {
                color1 = -0x100;
                color2 = -0x100;
            }
            u32 name = menuPdaDPMListGetPokemonName(i);
            if (name == 0) {
                name = GSmsgGetGSchar(1);
            }
            u8 floor;
            u32 placeMsg = menuPdaDPMListGetDarkPokemonPlaceMsgID(i, &floor);
            msgctrlSetValue(0x37, name);
            s32 yy = (s32)y;
            GSmsgPrint2(window->layer, 0, yy, color1 | window->alpha, 0x4277);
            menuPdaDPMListDispRelive(window, sprite, meter->x - base->x, yy, i, window->alpha, 1);
            if (placeMsg != 0) {
                msgctrlSetValue(0x2F, floor + 1);
                GSmsgPrint2(window->layer, placeItem->x - base->x, yy, color2 | window->alpha, placeMsg);
            }
            if (dark->isSnach()) {
                u16 spriteID = mballBiosGetSpriteID(dark->getCatchBallID());
                if (spriteID != 0) {
                    windowDrawSprite2(ball->x - base->x, (s32)y, ball->width, ball->height,
                                      window->alpha | ~0xFF, window, spriteID, 0, window->layer);
                }
            }
        }
        y += 23.0f;
    }
    spriteClearScissor(window->layer);
}

void menuPdaDPMList::DownCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    CURSOR cursor = _getCursor();
    menuPdaSubCheckUpDownCursor(window, sprite, &cursor.top, count, 10, 0);
}

void menuPdaDPMList::UpCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    CURSOR cursor = _getCursor();
    menuPdaSubCheckUpDownCursor(window, sprite, &cursor.top, count, 10, 1);
}

void menuPdaDPMList::ListCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s32 pos = window->pos;
    const s32 ids[10] = { 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41 };
    if (count == 0) {
        pos = 0;
    }
    s32 i;
    for (i = 0; i < 10; i++) {
        if (sprite->id == ids[i]) {
            break;
        }
    }
    *((s8*)sprite + 0x67) = alpha[i];
    if (pos == i) {
        winSpriteSetDisp(sprite, 1);
        return;
    }
    if (alpha[pos] == 0.0f) {
        winSpriteSetDisp(sprite, 0);
    }
}

void menuPdaDPMList::SortCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x1CD:
        if (sortKind == 0) {
            winSpriteSetDisp(sprite, 1);
            sprite->color = 0xFFB400FF;
            return;
        }
        winSpriteSetDisp(sprite, 0);
        sprite->color = -1;
        return;
    case 0x1CE:
        if (sortKind == 1) {
            winSpriteSetDisp(sprite, 1);
            sprite->color = 0xFFB400FF;
            return;
        }
        winSpriteSetDisp(sprite, 0);
        sprite->color = -1;
        return;
    case 0x1CF:
        if (sortKind == 2) {
            sprite->color = 0xFFB400FF;
            winSpriteSetDisp(sprite, 1);
            return;
        }
        winSpriteSetDisp(sprite, 0);
        sprite->color = -1;
        return;
    }
}

void menuPdaDPMList::SetItemColor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x4C:
        if (sortKind == 2) {
            sprite->color = 0xFFB400FF;
            return;
        }
        sprite->color = -1;
        return;
    case 0x4D:
        if (sortKind == 1) {
            sprite->color = 0xFFB400FF;
            return;
        }
        sprite->color = -1;
        return;
    case 0x4E:
        if (sortKind == 0) {
            sprite->color = 0xFFB400FF;
            return;
        }
        sprite->color = -1;
        return;
    }
}

s32 menuPdaDPMList::SortPlace() {
    darkPokemonWhere place;
    u8 floor;
    s32 total;
    s32 n = 0;
    total = Sort(DPM_SORT_POKEMON);
    tempCount = 0;
    for (int i = 0; i < total; i++) {
        u16 did = GetDarkPokemonID(i);
        DarkPokemon* dark = darkPokemonGetDarkPokemon(did);
        dark->getPlace(place, floor);
        if (dark->isSnach() && place == 1) {
            u16 pid = dark->getPokemonID();
            floor = getTemochiIndex(pid, did);
            temp[n].key = floor;
            temp[n].pokemonID = pid;
            temp[n].darkID = did;
            n++;
        }
    }
    if (n != 0) {
        SortSub(temp, n, true);
        SortSetTemp(temp2, temp, n);
    }
    for (int fl = 0; fl < 9; fl++) {
        s32 n = 0;
        for (int i = 0; i < total; i++) {
            u16 did = GetDarkPokemonID(i);
            DarkPokemon* dark = darkPokemonGetDarkPokemon(did);
            dark->getPlace(place, floor);
            if (dark->isSnach() && place == 3 && floor == fl) {
                u16 pid = dark->getPokemonID();
                temp[n].key = floor;
                temp[n].pokemonID = pid;
                temp[n].darkID = did;
                n++;
            }
        }
        if (n != 0) {
            SortSetTemp(temp2, temp, n);
        }
    }
    for (int fl = 0; fl < 8; fl++) {
        s32 n = 0;
        for (int i = 0; i < total; i++) {
            u16 did = GetDarkPokemonID(i);
            DarkPokemon* dark = darkPokemonGetDarkPokemon(did);
            dark->getPlace(place, floor);
            if (dark->isSnach() && place == 2 && floor == fl) {
                u16 pid = dark->getPokemonID();
                temp[n].key = floor;
                temp[n].pokemonID = pid;
                temp[n].darkID = did;
                n++;
            }
        }
        if (n != 0) {
            SortSetTemp(temp2, temp, n);
        }
    }
    {
        s32 n = 0;
        for (int i = 0; i < total; i++) {
            u16 did = GetDarkPokemonID(i);
            DarkPokemon* dark = darkPokemonGetDarkPokemon(did);
            dark->getPlace(place, floor);
            if (dark->isSnach() && place == 4) {
                u16 pid = dark->getPokemonID();
                temp[n].key = floor;
                temp[n].pokemonID = pid;
                temp[n].darkID = did;
                n++;
            }
        }
        if (n != 0) {
            SortSub(temp, n, true);
            SortSetTemp(temp2, temp, n);
        }
    }
    {
        s32 n = 0;
        for (int i = 0; i < total; i++) {
            u16 did = GetDarkPokemonID(i);
            DarkPokemon* dark = darkPokemonGetDarkPokemon(did);
            dark->getPlace(place, floor);
            if (dark->isSnach() && (place == 5 || place == 6)) {
                u16 pid = dark->getPokemonID();
                temp[n].key = floor;
                temp[n].pokemonID = pid;
                temp[n].darkID = did;
                n++;
            }
        }
        if (n != 0) {
            SortSetTemp(temp2, temp, n);
        }
    }
    {
        s32 n = 0;
        for (int i = 0; i < total; i++) {
            u16 did = GetDarkPokemonID(i);
            DarkPokemon* dark = darkPokemonGetDarkPokemon(did);
            if (!dark->isSnach()) {
                u16 pid = dark->getPokemonID();
                temp[n].key = dark->getSnatchIndex();
                temp[n].darkID = did;
                temp[n].pokemonID = pid;
                n++;
            }
        }
        if (n != 0) {
            SortSub(temp, n, true);
            SortSetTemp(temp2, temp, n);
        }
    }
    tempCount = 0;
    SortSetTemp(sorted, temp2, total);
    return total;
}

u8 menuPdaDPMList::getTemochiIndex(u16 pokemonID, u16 darkID) {
    s32 mon;
    s32 party = savedataGetStatus(0, 2);
    u8 i;
    for (i = 0; i < 6; i++) {
        mon = heroBiosGetPokemonPtr(party, i);
        if (pokemonCheckValid(mon) != 0) {
            u16 dark = pokemonBiosGetDarkpokemonDataId(mon);
            pokemonBiosGetPokemonDataId(mon);
            if (dark == darkID) {
                return i;
            }
        }
    }
    return 0;
}

s32 menuPdaDPMList::SortDP() {
    DarkPokemon* dark;
    int i;
    s32 n = 0;
    s32 total = Sort(DPM_SORT_POKEMON);
    tempCount = 0;
    for (i = 0; i < total; i++) {
        u16 did = GetDarkPokemonID(i);
        DarkPokemon* dark = darkPokemonGetDarkPokemon(did);
        if (dark->isSnach() && !dark->isRelive()) {
            u16 pid = dark->getPokemonID();
            s32 init = dark->getInitDarkPointDirect();
            temp[n].key = (s32)((f32)(dark->getDarkPointDirect() * 100) / (f32)init);
            temp[n].pokemonID = pid;
            temp[n].darkID = did;
            n++;
        }
    }
    if (n != 0) {
        SortSub2(temp, n, true);
        SortSetTemp(temp2, temp, n);
    }
    n = 0;
    for (i = 0; i < total; i++) {
        u16 did = GetDarkPokemonID(i);
        dark = darkPokemonGetDarkPokemon(did);
        if (dark->isRelive()) {
            u16 pid = dark->getPokemonID();
            temp[n].key = dark->getSnatchIndex();
            temp[n].pokemonID = pid;
            temp[n].darkID = did;
            n++;
        }
    }
    if (n != 0) {
        SortSub(temp, n, true);
        SortSetTemp(temp2, temp, n);
    }
    n = 0;
    for (i = 0; i < total; i++) {
        u16 did = GetDarkPokemonID(i);
        DarkPokemon* dark = darkPokemonGetDarkPokemon(did);
        if (!dark->isSnach()) {
            u16 pid = dark->getPokemonID();
            temp[n].key = dark->getSnatchIndex();
            temp[n].pokemonID = pid;
            temp[n].darkID = did;
            n++;
        }
    }
    if (n != 0) {
        SortSub(temp, n, true);
        SortSetTemp(temp2, temp, n);
    }
    tempCount = 0;
    SortSetTemp(sorted, temp2, total);
    return total;
}

s32 menuPdaDPMList::SortPokemon() {
    int id;
    int n = 0;
    tempCount = 0;
    for (id = 1; id < 0x80; id++) {
        DarkPokemon* dark = darkPokemonGetDarkPokemon((u16)id);
        u16 pid = dark->getPokemonID();
        if (pid != 0 && dark->getStatus() >= 1) {
            pairs[n].pokemonID = pid;
            pairs[n].darkID = (u16)id;
            sorted[n].key = dark->getSnatchIndex();
            sorted[n].pokemonID = pairs[n].pokemonID;
            sorted[n].darkID = pairs[n].darkID;
            n++;
        }
    }
    SortSub(sorted, n, true);
    return n;
}

void menuPdaDPMList::Button(tagWINDOW_WORK* window) {
    if (window != 0) {
        int n = menuPdaDPMListGetDPNum();
        if (winSeqCheckMove(window->seq) == 0) {
            u16 trigger = windowGetKeyInfo()->trigger;
            if (n != 0 && (trigger & 0x10) != 0) {
                window->unkA4 = 1;
            }
            if ((trigger & 0x20) != 0) {
                window->unkA4 = 1;
                window->unkA5 = 1;
            }
        }
    }
}

void menuPdaDPMList::Cursor(tagWINDOW_WORK* window) {
    windowGetKeyInfo();
    CURSOR c = _getCursor();
    c.top = window->top;
    c.pos = window->pos;
    int n = menuPdaDPMListGetDPNum();
    int visible = 10;
    if (n < 10) {
        visible = n;
    }
    u16 key = windowGetKeyRepeat();
    s32 sort = sortKind;
    if ((key & 0x400) != 0) {
        sort += 1;
        if (sort >= 3) {
            sort = 0;
        }
        Sort((DPMSelSort)sort);
    } else if ((key & 0x200) != 0) {
        sort -= 1;
        if (sort < 0) {
            sort = 2;
        }
        Sort((DPMSelSort)sort);
    }
    sortKind = sort;
    if (visible != 0) {
        if ((key & 1) != 0) {
            if (c.pos + c.top != 0) {
                GSsndPlayNow(0x450);
            }
            c.pos -= 1;
        } else if ((key & 2) != 0) {
            if (n - 1 != c.pos + c.top) {
                GSsndPlayNow(0x450);
            }
            c.pos += 1;
        } else if ((key & 8) != 0) {
            if (n - 1 != c.pos + c.top) {
                GSsndPlayNow(0x453);
            }
            c.pos += visible;
        } else if ((key & 4) != 0) {
            if (c.pos + c.top != 0) {
                GSsndPlayNow(0x453);
            }
            c.pos -= visible;
        }
        s16 p = c.pos;
        if (p < 0) {
            c.pos = 0;
            s32 t1 = c.top + p;
            c.top = t1;
            if (t1 < 0) {
                c.top = 0;
                c.pos = 0;
            }
        } else if (p >= visible) {
            s8 last = visible - 1;
            s16 t2 = c.top + (p - (visible - 1));
            c.pos = last;
            c.top = t2;
            if (t2 + last >= n) {
                c.pos = last;
                c.top = (s8)(n - visible);
            }
        }
    }
    _setCursor(c);
    window->top = c.top;
    window->pos = c.pos;
}

s32 menuPdaDPMList::Sort(DPMSelSort sort) {
    switch (sort) {
    case DPM_SORT_POKEMON:
        count = SortPokemon();
        break;
    case DPM_SORT_DP:
        count = SortDP();
        break;
    case DPM_SORT_PLACE:
        count = SortPlace();
        break;
    }
    return count;
}

void menuPdaDPMList::SortSetTemp(SnatchSortBuff* dst, SnatchSortBuff* src, long n) {
    SnatchSortBuff* p = src;
    for (long i = 0; i < n; i++) {
        memcpy(&dst[tempCount], p, sizeof(SnatchSortBuff));
        p++;
        tempCount++;
    }
}

void menuPdaDPMList::SortSub2(SnatchSortBuff* buf, long n, bool ascending) {
    SnatchSortBuff tmp;
    long i;
    long j;
    if (ascending) {
        for (i = 1; i < n; i++) {
            memcpy(&tmp, &buf[i], sizeof(SnatchSortBuff));
            j = i - 1;
            for (; j >= 0 && buf[j].key > tmp.key; j--) {
                memcpy(&buf[j + 1], &buf[j], sizeof(SnatchSortBuff));
            }
            memcpy(&buf[j + 1], &tmp, sizeof(SnatchSortBuff));
        }
        return;
    }
    for (i = 1; i < n; i++) {
        memcpy(&tmp, &buf[i], sizeof(SnatchSortBuff));
        j = i - 1;
        for (; j >= 0 && buf[j].key < tmp.key; j--) {
            memcpy(&buf[j + 1], &buf[j], sizeof(SnatchSortBuff));
        }
        memcpy(&buf[j + 1], &tmp, sizeof(SnatchSortBuff));
    }
}

void menuPdaDPMList::SortSub(SnatchSortBuff* buf, long n, bool ascending) {
    SnatchSortBuff tmp;
    long gap;
    long i;
    long j;
    if (ascending) {
        for (gap = n / 2; gap > 0; gap /= 2) {
            for (i = gap; i < n; i++) {
                for (j = i - gap; j >= 0 && buf[j].key > buf[j + gap].key; j -= gap) {
                    SnatchSortBuff* a = &buf[j];
                    SnatchSortBuff* b = &buf[j + gap];
                    memcpy(&tmp, a, sizeof(SnatchSortBuff));
                    memcpy(a, b, sizeof(SnatchSortBuff));
                    memcpy(b, &tmp, sizeof(SnatchSortBuff));
                }
            }
        }
        return;
    }
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            for (j = i - gap; j >= 0 && buf[j].key < buf[j + gap].key; j -= gap) {
                SnatchSortBuff* a = &buf[j];
                SnatchSortBuff* b = &buf[j + gap];
                memcpy(&tmp, a, sizeof(SnatchSortBuff));
                memcpy(a, b, sizeof(SnatchSortBuff));
                memcpy(b, &tmp, sizeof(SnatchSortBuff));
            }
        }
    }
}

void menuPdaDPMList::Ctrl(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x132);
            menuPdaSetSubres(0, 1);
            window->seqSet = 1;
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

void menuPdaDPMList::ListMain(tagWINDOW_WORK* window) {
    CURSOR c = _getCursor();
    ListPosition();
    CalcPosition(&c);
    menuPdaSubCalcAlpha(alpha, 10, c.pos);
}

void menuPdaDPMList::CalcPosition(CURSOR* cursor) {
    unk3C = -cursor->top * 0x17;
}

void menuPdaDPMList::ListPosition() {
    if (unk30 != unk38) {
        menuPdaSubCalcPositon(&unk30, unk38, 10.0f);
    }
    if (unk34 != unk3C) {
        menuPdaSubCalcPositon(&unk34, unk3C, 10.0f);
    }
}

s32 menuPdaDPMList::Main(long unused, CURSOR* cursor) {
    CURSOR c;
    c.top = cursor->top;
    c.pos = cursor->pos;
    _setCursor(c);
    s32 result;
    do {
        result = menuOpen(0x74, 1);
        c = _getCursor();
    } while (result != -1 && c.pos >= 10);
    _menuClose(0x74);
    if (result == -1 || count == 0) {
        return -1;
    }
    cursor->pos = c.pos;
    cursor->top = c.top;
    return c.top + c.pos;
}

void menuPdaDPMList::InitWork() {
    int n = count;
    darkPokemonGetMeetNum();
    listPos = 0;
    listTop = 0;
    sortKind = 0;
    unk30 = 0.0f;
    unk34 = 0.0f;
    unk38 = 0.0f;
    unk3C = 0.0f;
    unk40 = 0;
    if (n >= 10) {
        unk44 = 10;
    } else {
        unk44 = n;
    }
    pairs = (DPMIdPair*)__nwa__FUl(0x200);
    sorted = (SnatchSortBuff*)__nwa__FUl(0x400);
    temp = (SnatchSortBuff*)__nwa__FUl(0x400);
    temp2 = (SnatchSortBuff*)__nwa__FUl(0x400);
    Sort((DPMSelSort)sortKind);
    menuPdaSubInitAlpha(alpha, 10, 0);
}

void menuPdaDPMList::_setCursor(CURSOR cursor) {
    cursorBiosSetPos(0xC, cursor);
}

CURSOR menuPdaDPMList::_getCursor() {
    return cursorBiosGetPos(0xC);
}

void menuPdaDPMList::_menuClose(long menuID) {
    menuClose(menuID);
    menuCloseSync(menuID, 1);
}
