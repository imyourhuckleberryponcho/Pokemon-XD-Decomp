#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct SelInfo {
    s16 id;
    s16 sel;
};

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    s8 seqSet;
    u8 pad3;
    void* seq;
    u8 pad8[0x93 - 8];
    u8 layer;
    u8 pad94[0x9C - 0x94];
    SelInfo info;
    u8 padA0[4];
    u8 closeFlag;
    u8 cancelFlag;
};

struct tagSPRITE_WORK {
    u8 pad0[6];
    s16 id;
    u8 pad8[0x54 - 8];
    s16 w;
    s16 h;
    u8 pad58[0x64 - 0x58];
    union {
        s32 color;
        struct {
            u8 r, g, b, a;
        } rgba;
    };
};

struct MenuItem {
    u8 pad0[6];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
};

struct WindowKeyInfo {
    u8 pad0[4];
    u16 down;
};

struct Pokemon;
enum MENU_POKEMON_CB_TYPE { MENU_POKEMON_CB_NONE, MENU_POKEMON_CB_PREV, MENU_POKEMON_CB_NEXT };

class menuOrre {
public:
    menuOrre() {
        m_pushed = 0;
        m_idx = 0;
        m_wait = 0.0f;
        m_timer = 0;
        for (s32 i = 0; i < 13; i++) {
            m_list[i] = 0;
        }
        m_count = 0;
        m_sel[0] = -1;
        m_sel[1] = -1;
        m_sel[2] = -1;
        m_sel[3] = -1;
    }
    void Release();
    void Main();
    void Init();
    void InitSub();
    s32 Hook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void ControlCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void SetNumber(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    u32 GetDeckPokemonName(u16 idx);
    s32 GetDeckPokemonFaceID(u16 idx);
    u8 GetDeckPokemonLevel(u16 idx);
    u8 GetDeckPokemonSex(u16 idx);
    u16 GetDeckPokemonMochimono(u16 idx);
    void* GetDeckPokemonPtr(u16 idx);
    u32 GetTemochiPokemonName(u16 idx);
    s32 GetTemochiPokemonFaceID(u16 idx);
    u8 GetTemochiMaxPokemonLevel();
    u8 GetTemochiPokemonLevel(u16 idx);
    u8 GetTemochiPokemonSex(u16 idx);
    u16 GetTemochiPokemonMochimono(u16 idx);
    void* GetTemochiPokemonPtr(u16 idx);
    void* GetHeroPtr(u8 which);
    void RightPanel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void LeftPanel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void Button(tagWINDOW_WORK* window);
    u8 ConfirmPokemon();
    inline bool IsSelected(u16 c) {
        for (u16 i = 0; i < 4; i++) {
            if (m_sel[i] == (s16)c) {
                return true;
            }
        }
        return false;
    }
    s32 SelectPokemon(u16 unused, bool selected);
    void Ctrl(tagWINDOW_WORK* window);
    void CreatePokemonList();

    u8 m_maxLevel;
    u16 m_deck;
    s16 m_count;
    s16 m_sel[4];
    u16 m_cursor;
    s16 m_timer;
    u8 m_pushed;
    u16 m_trainer;
    u16 m_idx;
    f32 m_wait;
    void* m_list[13];
};

extern "C" {
void GSthreadSwitch(void);
u8 GSfloorIsPop(void);
u8 GSfloorIsPush(void);
void GSfloorPush(s32);
void GSfloorPop(void);
void floorWaitForChange(void);
void fadeSet(s32, f32);
void* __nw__FUl(u32);
void __dl__FPv(void*);
void* memcpy(void*, const void*, u32);
u16 HSD_Rand(void);
double sin(double);
f32 timeGetLastFrameSec(void);
u32 FlashSystemGetEndFrame(u32);
s32 FlashSystemGetFrameFromLabel(u32, const char*);
u32 FlashSystemGetNowFrame(u32);
u8 FlashSystemIsLastFrame(u32);
void FlashSystemSetNowFrame(u32, s32);
void FlashSystemSetPlayFrameLabel(u32, const char*, const char*);
void menuFaceLoad(s32, void* (*)(void*), s16*);
u8 menuFaceCheckLoading(void);
s32 menuFaceGetID(void*);
void menuFaceDispFromID3(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s16*, s16*);
void menuOpen(s32, s32);
s32 menuOpenCustom(s32, ...);
void menuClose(s32);
void menuCloseSync(s32, s32);
MenuItem* menuItemBiosGetPtr(s32, s16);
s32 menuPokemonStatusOpenFromPokemonChange(void*, Pokemon* (*)(Pokemon*, MENU_POKEMON_CB_TYPE, long), u16*);
s32 menuSubOpenSelect2(s32, void*, s32, s32, s32, s32, s32, s32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
u8 menuSubGetPokemonSexForFightDisp(void*);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
void winSeqSetMenu(void*, s32);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void windowDrawSprite2(s16, s16, s16, s16, s32, tagWINDOW_WORK*, u16, s32, s32);
s32 windowGetActiveID(void);
tagWINDOW_WORK* windowSearchID(s32);
WindowKeyInfo* windowGetKeyInfo(void);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s32, s32, s32, u32);
void GSmsgPrintRect(s32, s32, s32, s32, s32, s32, u32);
u32 GSmsgGetGSchar(u16);
void msgctrlSetValue(s32, u32);
void* fightGetMenuCtrlHero(void);
void fightSetMenuCtrlHero(void*);
void fightReadResourceID(s32, s32);
void fightFreeResourceID(s32, s32);
void* fightEncountDataBiosGetPtr(u16);
u16 fightEncountDataBiosGetFightTrainerDataId(void*, s32);
void fightTrainerCreateFightTrainerDataIdToHero(u16, s32, void*, u16);
u16 fightEncount(u16);
u32 fightTrainerDB_GetName(u16);
void* heroBiosGetPokemonPtr(void*, u16);
u32 heroBiosGetNamePtr(void*);
void* savedataGetStatus(s32, s32);
void pokemonInit(void*);
void pokemonBiosCopy(void*, void*);
u32 pokemonBiosGetNicknamePtr(void*);
u8 pokemonBiosGetLevel(void*);
u16 pokemonGetSoubiItemDataId(void*);
}

static u16 _deckNumber;
static u16 _fightresult;
static menuOrre* pOrre;
static s16 _loadFaceCount;
struct OrreHero {
    char data[0x978];
    OrreHero() {}
};
static OrreHero _orreHero;

static void* _loadPokemonCallBack(void* idx);
static void* _GetTemochiPokemonPtr(u16 idx);
static Pokemon* _PokemonStatusDisp_CallBack(Pokemon* pokemon, MENU_POKEMON_CB_TYPE type, long idx);

static inline void setNowFrameEnd(u32 id, int n) {
    const char* endLabel[5] = {"1_start", "1_end", "2_end", "3_end", "4_end"};
    FlashSystemSetNowFrame(id, FlashSystemGetFrameFromLabel(id, endLabel[n]));
}

static inline void playLabel(u32 id, int n) {
    const char* anim[5][2] = {{"1_start", "1_start"}, {"1_start", "1_end"}, {"1_start", "2_end"},
                              {"1_start", "3_end"}, {"1_start", "4_end"}};
    FlashSystemSetPlayFrameLabel(id, anim[n][0], anim[n][1]);
}

static void* _loadPokemonCallBack(void* param) {
    u16* idx = (u16*)param;
    void* result = 0;
    if (pOrre != 0) {
        result = pOrre->m_list[*idx];
        (*idx)++;
    }
    return result;
}

void menuOrre::CreatePokemonList() {
    u16 n = 0;
    for (u16 i = 0; i < 6; i++) {
        m_list[n++] = GetTemochiPokemonPtr(i);
    }
    for (u16 i = 0; i < 6; i++) {
        m_list[n++] = GetDeckPokemonPtr(i);
    }
}

void menuOrre::Ctrl(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x24);
            window->seqSet = 1;
        }
        break;
    case 2:
        if (m_idx < 4) {
            u32 end = FlashSystemGetEndFrame(0x1F5B3000);
            u8 done;
            if (FlashSystemGetNowFrame(0x1F5B3000) >= end) {
                done = 1;
            } else {
                done = 0;
            }
            if (done) {
                m_wait = m_wait - timeGetLastFrameSec();
                if (m_wait <= 0.0f) {
                    s32 rnd = HSD_Rand() % 50;
                    m_wait = (50.0f + rnd) / 100.0f;
                    s16 n = ++m_idx;
                    playLabel(0x1F5B3000, n);
                }
            }
        }
        break;
    case 3:
        if (window->seqSet == 0) {
            window->seqSet = 1;
        }
        break;
    }
    m_timer = (s32)(60.0f * timeGetLastFrameSec() + (f32)m_timer) % 1000;
}

s32 menuOrre::SelectPokemon(u16 unused, bool selected) {
    s32 normal[3] = {0x8ACE, 0x8ACF, 0x8AD0};
    s32 chosen[3] = {0x8AF1, 0x8ACF, 0x8AD0};
    if (selected) {
        return menuSubOpenSelect2(0, chosen, 3, 0x15E, 0xB4, 0, 3, 0);
    }
    return menuSubOpenSelect2(0, normal, 3, 0x15E, 0xB4, 0, 3, 0);
}

u8 menuOrre::ConfirmPokemon() {
    u8 result;
    winMsgOpen(2, 0x8AD1, 1, 1);
    if (menuSubOpenYesNo(0, 0x40, 0xC8, 0) == 0) {
        result = 1;
    } else {
        result = 0;
    }
    winMsgClose(1);
    return result;
}

void menuOrre::Button(tagWINDOW_WORK* window) {
    SelInfo info = window->info;
    m_cursor = info.sel;
    if (window != 0) {
        u16 down = windowGetKeyInfo()->down;
        if (down & 0x10) {
            window->closeFlag = 1;
        }
        if (m_count != 0 && (down & 0x20)) {
            window->closeFlag = 1;
            window->cancelFlag = 1;
        }
    }
}

void menuOrre::LeftPanel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s16 ids[6] = {1, 2, 3, 4, 5, 6};
    u16 i = 0;
    while (i < 6) {
        if (sprite->id == ids[i]) {
            break;
        }
        i++;
    }
    MenuItem* item = menuItemBiosGetPtr(0xFD, sprite->id);
    windowDrawSprite2(0, 0, item->w, item->h, window->layer | ~0xFF, window, 0x31B, 0,
                      winSpriteGetLayerID(window, sprite));
    item = menuItemBiosGetPtr(0xFD, 0x25);
    u32 name = GetTemochiPokemonName(i);
    msgctrlSetValue(0x37, name);
    GSmsgPrintRect(winSpriteGetLayerID(window, sprite), item->x, item->y, sprite->w, sprite->h,
                   window->layer | ~0xFF, 0x4277);
    item = menuItemBiosGetPtr(0xFD, 0x26);
    GSmsgPrint2(winSpriteGetLayerID(window, sprite), item->x, item->y + 2, window->layer | ~0xFF, 0x42C1);
    u32 rect = GSmsgGetRect(0x42C1);
    u8 level = GetTemochiPokemonLevel(i);
    msgctrlSetValue(0x5F, level);
    GSmsgPrintRect(winSpriteGetLayerID(window, sprite), item->x + 4 + (s16)(rect >> 16), item->y + 2, sprite->w,
                   sprite->h, window->layer | ~0xFF, 0x4352);
    u8 sex = GetTemochiPokemonSex(i);
    MenuItem* sexItem = menuItemBiosGetPtr(0xFD, 0x27);
    u32 sexMsg;
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
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), sexItem->x + 0x12, sexItem->y,
                    window->layer | ~0xFF, sexMsg);
    }
    if (GetTemochiPokemonMochimono(i) != 0) {
        MenuItem* itemIcon = menuItemBiosGetPtr(0xFD, 0x24);
        windowDrawSprite2(itemIcon->x, itemIcon->y, itemIcon->w, itemIcon->h, window->layer | ~0xFF, window, 0x14B,
                          0, winSpriteGetLayerID(window, sprite));
    }
    MenuItem* face = menuItemBiosGetPtr(0xFD, 0x22);
    s16 pos[2];
    s16 size[2];
    pos[0] = face->x;
    pos[1] = face->y;
    size[0] = face->w;
    size[1] = face->h;
    s32 faceId = GetTemochiPokemonFaceID(i);
    menuFaceDispFromID3(window, sprite, faceId, size, pos);
}

void menuOrre::RightPanel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s16 ids[6] = {7, 8, 9, 10, 11, 12};
    u16 i = 0;
    while (i < 6) {
        if (sprite->id == ids[i]) {
            break;
        }
        i++;
    }
    MenuItem* item = menuItemBiosGetPtr(0xFD, sprite->id);
    windowDrawSprite2(0, 0, item->w, item->h, window->layer | ~0xFF, window, 0x31B, 0,
                      winSpriteGetLayerID(window, sprite));
    item = menuItemBiosGetPtr(0xFD, 0x1F);
    u32 name = GetDeckPokemonName(i);
    msgctrlSetValue(0x37, name);
    GSmsgPrintRect(winSpriteGetLayerID(window, sprite), item->x, item->y, sprite->w, sprite->h,
                   window->layer | ~0xFF, 0x4277);
    item = menuItemBiosGetPtr(0xFD, 0x20);
    GSmsgPrint2(winSpriteGetLayerID(window, sprite), item->x, item->y + 2, window->layer | ~0xFF, 0x42C1);
    u32 rect = GSmsgGetRect(0x42C1);
    u8 level = GetDeckPokemonLevel(i);
    msgctrlSetValue(0x5F, level);
    GSmsgPrintRect(winSpriteGetLayerID(window, sprite), item->x + 4 + (s16)(rect >> 16), item->y + 2, sprite->w,
                   sprite->h, window->layer | ~0xFF, 0x4352);
    u8 sex = GetDeckPokemonSex(i);
    MenuItem* sexItem = menuItemBiosGetPtr(0xFD, 0x21);
    u32 sexMsg;
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
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), sexItem->x + 0x12, sexItem->y,
                    window->layer | ~0xFF, sexMsg);
    }
    if (GetDeckPokemonMochimono(i) != 0) {
        MenuItem* itemIcon = menuItemBiosGetPtr(0xFD, 0x1E);
        windowDrawSprite2(itemIcon->x, itemIcon->y, itemIcon->w, itemIcon->h, window->layer | ~0xFF, window, 0x14B,
                          0, winSpriteGetLayerID(window, sprite));
    }
    MenuItem* face = menuItemBiosGetPtr(0xFD, 0x1C);
    s16 pos[2];
    s16 size[2];
    pos[0] = face->x;
    pos[1] = face->y;
    size[0] = face->w;
    size[1] = face->h;
    s32 faceId = GetDeckPokemonFaceID(i);
    menuFaceDispFromID3(window, sprite, faceId, size, pos);
}

void* menuOrre::GetHeroPtr(u8 which) {
    if (which) {
        return &_orreHero;
    }
    return savedataGetStatus(0, 2);
}

void* menuOrre::GetTemochiPokemonPtr(u16 idx) {
    return heroBiosGetPokemonPtr(GetHeroPtr(0), idx);
}

u16 menuOrre::GetTemochiPokemonMochimono(u16 idx) {
    return pokemonGetSoubiItemDataId(GetTemochiPokemonPtr(idx));
}

u8 menuOrre::GetTemochiPokemonSex(u16 idx) {
    return menuSubGetPokemonSexForFightDisp(GetTemochiPokemonPtr(idx));
}

u8 menuOrre::GetTemochiPokemonLevel(u16 idx) {
    return pokemonBiosGetLevel(GetTemochiPokemonPtr(idx));
}

u8 menuOrre::GetTemochiMaxPokemonLevel() {
    u8 max = 0;
    for (u16 i = 0; i < 6; i++) {
        u8 level = GetTemochiPokemonLevel(i);
        if (max < level) {
            max = level;
        }
    }
    return max;
}

s32 menuOrre::GetTemochiPokemonFaceID(u16 idx) {
    return menuFaceGetID(GetTemochiPokemonPtr(idx));
}

u32 menuOrre::GetTemochiPokemonName(u16 idx) {
    return pokemonBiosGetNicknamePtr(GetTemochiPokemonPtr(idx));
}

void* menuOrre::GetDeckPokemonPtr(u16 idx) {
    return heroBiosGetPokemonPtr(GetHeroPtr(1), idx);
}

u16 menuOrre::GetDeckPokemonMochimono(u16 idx) {
    return pokemonGetSoubiItemDataId(GetDeckPokemonPtr(idx));
}

u8 menuOrre::GetDeckPokemonSex(u16 idx) {
    return menuSubGetPokemonSexForFightDisp(GetDeckPokemonPtr(idx));
}

u8 menuOrre::GetDeckPokemonLevel(u16 idx) {
    return pokemonBiosGetLevel(GetDeckPokemonPtr(idx));
}

s32 menuOrre::GetDeckPokemonFaceID(u16 idx) {
    return menuFaceGetID(GetDeckPokemonPtr(idx));
}

u32 menuOrre::GetDeckPokemonName(u16 idx) {
    return pokemonBiosGetNicknamePtr(GetDeckPokemonPtr(idx));
}

void menuOrre::SetNumber(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s16 ids[6] = {0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
    u16 numbers[4] = {0x31C, 0x31D, 0x31E, 0x31F};
    u16 i = 0;
    while (i < 6) {
        if (sprite->id == ids[i]) {
            break;
        }
        i++;
    }
    for (u16 j = 0; j < 4; j++) {
        if (i == m_sel[j]) {
            windowDrawSprite2(0, 0, sprite->w, sprite->h, window->layer | ~0xFF, window, numbers[j], 0,
                              winSpriteGetLayerID(window, sprite));
            return;
        }
    }
}

void menuOrre::ControlCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    SelInfo info = window->info;
    s32 ids[6] = {13, 14, 15, 16, 17, 18};
    s32* p = ids;
    s16 i = 0;
    while (i < 6) {
        if (sprite->id == *p) {
            break;
        }
        p++;
        i++;
    }
    if (i == info.sel) {
        if (window == windowSearchID(windowGetActiveID())) {
            s32 t = m_timer % 60;
            sprite->color = -1;
            if (t < 30) {
                f32 sv = (f32)sin(3.14f * ((f32)t / 30.0f));
                sprite->rgba.a -= (u8)(128.0f * sv);
            }
        } else {
            sprite->rgba.a = 0xFF;
        }
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}

s32 menuOrre::Hook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        LeftPanel(window, sprite);
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        RightPanel(window, sprite);
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
        SetNumber(window, sprite);
        break;
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        ControlCursor(window, sprite);
        break;
    case 25: {
        msgctrlSetValue(0x37, heroBiosGetNamePtr(GetHeroPtr(0)));
        MenuItem* item = menuItemBiosGetPtr(0xFD, sprite->id);
        u32 rect = GSmsgGetRect(0x4276);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), (s16)(item->w - (rect >> 16)), 0, window->layer | ~0xFF, 0x4276);
        break;
    }
    case 26:
        msgctrlSetValue(0x37, GSmsgGetGSchar(fightTrainerDB_GetName(m_trainer)));
        GSmsgGetRect(0x4276);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, window->layer | ~0xFF, 0x4276);
        break;
    }
    return 0;
}

static void* _GetTemochiPokemonPtr(u16 idx) {
    if (pOrre != 0) {
        return pOrre->GetTemochiPokemonPtr(idx);
    }
    return 0;
}

static Pokemon* _PokemonStatusDisp_CallBack(Pokemon* pokemon, MENU_POKEMON_CB_TYPE type, long param) {
    u16* idx = (u16*)param;
    Pokemon* result = 0;
    switch (type) {
    case 1:
        if (*idx == 0) {
            return pokemon;
        }
        (*idx)--;
        result = (Pokemon*)_GetTemochiPokemonPtr(*idx);
        break;
    case 2:
        if (*idx == 5) {
            return pokemon;
        }
        (*idx)++;
        result = (Pokemon*)_GetTemochiPokemonPtr(*idx);
        break;
    }
    return result;
}

void menuOrre::InitSub() {
    fightReadResourceID(0x842, 0x184C3400);
    m_deck = _deckNumber;
    m_trainer = fightEncountDataBiosGetFightTrainerDataId(fightEncountDataBiosGetPtr(m_deck), 1);
    fightTrainerCreateFightTrainerDataIdToHero(m_trainer, 0, &_orreHero, m_deck);
    void* hero = fightGetMenuCtrlHero();
    memcpy(hero, GetHeroPtr(0), 0x978);
    m_maxLevel = GetTemochiMaxPokemonLevel();
    CreatePokemonList();
}

void menuOrre::Init() {
    m_pushed = GSfloorIsPush();
    InitSub();
}

static inline void _copyPokemon(void* dst, void* src) { pokemonBiosCopy(dst, src); }

void menuOrre::Main() {
    u8 full;
    u16* cursorPtr;
    u8 ok = 1;
    u16 k;
    u16 i;
    void* hero;
    _loadFaceCount = 0;
    menuFaceLoad(0, _loadPokemonCallBack, &_loadFaceCount);
    menuOpen(0xFF, 0);
    do {
        GSthreadSwitch();
    } while (!FlashSystemIsLastFrame(0x1F5C3000));
    playLabel(0x1F5B3000, 0);
    cursorPtr = &m_cursor;
    for (;;) {
        m_wait = 1.0f;
        u8 cont = 1;
        playLabel(0x1F5A3000, 0);
        do {
            s32 cursor = m_cursor;
            if (menuOpenCustom(0xFD, windowGetActiveID(), &cursor, 0, 1, 0) >= 0) {
                bool selected = IsSelected(m_cursor);
                switch (SelectPokemon(m_cursor, selected)) {
                case 0: {
                    if (selected) {
                        u16 cur = m_cursor;
                        u8 r;
                        if (m_count != 0) {
                            u16 j;
                            for (j = 0; j < 4; j++) {
                                if (m_sel[j] == cur) {
                                    break;
                                }
                            }
                            m_count--;
                            for (; j < 3; j++) {
                                m_sel[j] = m_sel[j + 1];
                            }
                            setNowFrameEnd(0x1F5A3000, m_count);
                            playLabel(0x1F5A3000, m_count);
                            r = 1;
                        } else {
                            r = 0;
                        }
                        ok = r;
                    } else {
                        full = 0;
                        u16 cur = m_cursor;
                        m_sel[m_count++] = cur;
                        if (m_count >= 4) {
                            full = 1;
                        }
                        playLabel(0x1F5A3000, m_count);
                        if (full == 1) {
                            cont = 0;
                        }
                    }
                    break;
                }
                case 1:
                    menuPokemonStatusOpenFromPokemonChange(GetTemochiPokemonPtr(m_cursor),
                                                           _PokemonStatusDisp_CallBack, cursorPtr);
                    fadeSet(2, 0.5f);
                    break;
                case 2:
                    break;
                }
            } else {
                u8 r;
                if (m_count != 0) {
                    m_count--;
                    m_sel[m_count] = -1;
                    setNowFrameEnd(0x1F5A3000, m_count);
                    playLabel(0x1F5A3000, m_count);
                    r = 1;
                } else {
                    r = 0;
                }
                ok = r;
                if (!r) {
                    cont = 0;
                }
            }
        } while (cont);
        if (!ok) {
            menuClose(0xFD);
        } else {
            u8 done;
            do {
                GSthreadSwitch();
                u32 end = FlashSystemGetEndFrame(0x1F5A3000);
                if (FlashSystemGetNowFrame(0x1F5A3000) >= end) {
                    done = 1;
                } else {
                    done = 0;
                }
            } while (!done);
            if (!ConfirmPokemon()) {
                m_count = 0;
                m_sel[0] = -1;
                m_sel[1] = -1;
                m_sel[2] = -1;
                m_sel[3] = -1;
                continue;
            }
        }
        break;
    }
    if (ok == 1) {
        while (menuFaceCheckLoading()) {
            GSthreadSwitch();
        }
        u8 done;
        do {
            GSthreadSwitch();
            u32 end = FlashSystemGetEndFrame(0x1F5B3000);
            if (FlashSystemGetNowFrame(0x1F5B3000) >= end) {
                done = 1;
            } else {
                done = 0;
            }
        } while (!done);
        hero = fightGetMenuCtrlHero();
        for (i = 0; i < 6; i++) {
            pokemonInit(heroBiosGetPokemonPtr(hero, i));
        }
        for (k = 0; k < 4; k++) {
            _copyPokemon(heroBiosGetPokemonPtr(hero, k), GetTemochiPokemonPtr(m_sel[k]));
        }
        fightSetMenuCtrlHero(fightGetMenuCtrlHero());
        _fightresult = fightEncount(m_deck);
    }
    menuCloseSync(0xFD, 1);
    menuClose(0xFF);
    menuCloseSync(0xFF, 1);
    if (m_pushed) {
        GSfloorPop();
    }
}

void menuOrre::Release() {
}

extern "C" {

void menuOrreButton(tagWINDOW_WORK* window) {
    if (pOrre != 0) {
        pOrre->Button(window);
    }
}

}

extern "C" {

void menuOrreCtrl(tagWINDOW_WORK* window) {
    if (pOrre != 0) {
        pOrre->Ctrl(window);
    }
}

}

extern "C" {

s32 menuOrreMenuHook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (pOrre != 0) {
        return pOrre->Hook(window, sprite);
    }
    return 0;
}

}

extern "C" {

void menuOrreColosseum(u16 deck) {
    _deckNumber = deck;
    _fightresult = 0;
    GSfloorPush(0x38A);
    floorWaitForChange();
}

}

extern "C" {

u16 menuOrreColosseumGetResult(void) {
    return _fightresult;
}

}

extern "C" {

void menuOrreInit(void) {
    if (!GSfloorIsPop()) {
        pOrre = new menuOrre();
        if (pOrre != 0) {
            pOrre->Init();
        }
    }
}

}

extern "C" {

void menuOrreMain(void) {
    if (pOrre != 0) {
        pOrre->Main();
    }
}

}

extern "C" {

void menuOrreExit(void) {
    if (pOrre != 0) {
        pOrre->Release();
        if (pOrre != 0) {
            delete pOrre;
        }
        pOrre = 0;
    }
    fightFreeResourceID(0x842, 0x184C3400);
}

}
