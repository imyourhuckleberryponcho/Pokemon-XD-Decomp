#include <dolphin/types.h>

#pragma peephole off

enum darkPokemonWhere { place0, place1, place2, place3, place4, place5, place6 };

class DarkPokemon {
public:
    void setPlace(darkPokemonWhere, u8);
};

class Pokemon {
public:
    DarkPokemon* getDarkPokemon();
    u8 getLevel() const;
    char* getNicknamePtr();
    void* getPokemonDataPtr() const;
    bool isDarkPokemon() const;
    u16 getHp() const;
    u16 getItemDataId() const;
    u8 data[0xC4];
};

class Hero {
public:
    static Hero* getHeroPtr();
    Pokemon* getPokemon(s32 index);
};

struct MENU_MODEL {
    MENU_MODEL() {}
    u8 unk0[0xEC];
};

struct POKEMON_EVOLUTION_INFO {
    u8 kind;
    u8 reserved;
    u16 parameter;
};

struct MenuItem {
    u8 pad0[6];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
};

struct MenuItemBios {
    u8 valid : 1;
    u8 pad0[5];
    s16 x;
    u8 pad8[0x10];
    s16 next;
};

struct MenuDataBios {
    u8 pad0[6];
    s16 first;
};

struct tagWINDOW_WORK {
    u8 used;
    s8 state;
    s8 seqSet;
    u8 pad3;
    s32 menuId;
    u8 pad8[0x14];
    s32 msgHandle;
    u8 pad20[0x6C];
    s16 offset;
    u8 pad8E[5];
    u8 alpha;
};

struct tagSPRITE_WORK {
    u8 pad0[6];
    s16 itemId;
    u8 pad8[0x44];
    u32 msg;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    u8 pad58[0xC];
    union {
        u32 color;
        struct {
            u8 r, g, b, a;
        } rgba;
    };
};

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

struct KeyInfo {
    u16 on;
    u16 up;
    u16 trg;
    u16 rep;
    u16 rel;
    u8 pad_a[0x10];
};

struct WinSys {
    u16 count;
    u8 pad_2[6];
    s32 activeID;
    void* pool;
    void* head;
    KeyInfo key;
    KeyInfo port[4];
    u8 pad_96[10];
};

struct PortKeyInfo {
    u8 pad0[4];
    u16 down;
};

extern WinSys winSysWork;
extern WinSys winSysWork2;

extern "C" {
u8 fn_80098B44(u8, Pokemon*);
s32 windowGetParam(tagWINDOW_WORK*, s32);
void menuFaceDisp(tagWINDOW_WORK*, tagSPRITE_WORK*, Pokemon*);
u8 menuSubGetPokemonSexForFightDisp(Pokemon*);
u32 GSmsgGetGSchar(u32);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
u16 pokemonBiosGetItemDataId(Pokemon*);
u16 pokemonGetSoubiItemDataId(Pokemon*);
u32 heroBiosGetNamePtr(Hero*);
void menuCBMessageCenterDisp(tagWINDOW_WORK*, tagSPRITE_WORK*, u32);
u32 itemDataBiosGetName(void*);
u32 wazaGetStatus(s32, s32, s32, s32);
s32 pokemonBiosGetPokemonWazaDataId(Pokemon*, u16);
u8 pokemonWazaCheckValid(Pokemon*, u16);
u32 pokemonDataBiosGetName(void*);
s32 pokecoloGetCountryCode();
void menuModelAdjustCamera(MENU_MODEL*);
void menuModelSetSize(MENU_MODEL*, s32, s16, s16, s16);
void menuModelSetZoom(MENU_MODEL*, f32);
void menuModelRender(MENU_MODEL*);
u8 GSgfxVideoGetVsyncRate();
double sin(double);
void pokemonInit(u32);
void pokemonBiosSetFriend(Pokemon*, u16);
void pokemonBiosCopy(Pokemon*, const Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
char* pokemonBiosGetNicknamePtr(Pokemon*);
u16 pokemonEvolutionCheck(Pokemon*, s32, u16, u16*, POKEMON_EVOLUTION_INFO*);
s32 pokemonEvolutionAll(Pokemon*, u16, u16, POKEMON_EVOLUTION_INFO*, Hero*, s32, s32, s32);
void memoDataSet(s32, Pokemon*);
u32 heroGetStatus(Hero*, s32, s32);
void menuModelInit(MENU_MODEL*, s16, s16);
void menuModelLoadPokemon(MENU_MODEL*, Pokemon*);
void menuModelCheck(MENU_MODEL*, s32);
void menuFaceLoad(Pokemon*, void* (*)(void*), void*);
s32 menuFaceGetID(Pokemon*);
s8 menuFaceSearchEnable(s32);
void cameraPlayAnime(s32, u32, f32, s32);
s32 floorGetCurrentGroupID();
void scriptModelSetMotion(u32, s32, s32, s32);
void cameraWaitSyncAnime(s32);
void fadeCheck(s32);
s32 menuGetLastError();
void windowCheckCursor(s32, s32);
s32 windowGetValue(s32);
PortKeyInfo* windowGetPortKeyInfo(s32);
s32 GSfsysGetDriveStatus();
s32 openMenuGBA(s32, u32, Hero**);
tagWINDOW_WORK* windowSearchID(s32);
tagSPRITE_WORK* windowSearchItemID(tagWINDOW_WORK*, u16);
void windowSetParam(tagWINDOW_WORK*, s32, s32);
void winSpriteSetDisp(tagSPRITE_WORK*, bool);
void winSeqSetMenu(s32, s32);
void menuClose(s32);
void menuCloseCustom(s32, s32, s32);
s32 menuOpenCustom(s32, ...);
void menuSetDisp(s32, bool);
s32 windowGetActiveID();
MenuItemBios* menuItemBiosGetPtr(s32, s32);
MenuDataBios* menuDataBiosGetPtr(s32);
f32 timeGetLastFrameSec();
u32 timeGetLastFrameTime();
void* memcardMemAllocForSavedata();
void* memcardMemFreeForSavedata(void*);
void menuGBACSetRomVer(s32, s32);
u8 menuFaceCheckLoading();
void GSfsysFree(s32);
void GSresFreeGroup(s32);
void GSfsysReadWait(s32);
u8 GSfloorIsFloorPushed();
void GSfloorPop();
s32 floorGetPrevFloorID();
void floorLink(s32, s32);
void scriptModelClose(s32);
s32 scriptModelOpen(u32);
s32 GSresGetResource(s32, s32);
void cameraSetType(s32);
void GSmodelSetVisibility(s32, s32);
void fadeSet(s32, f32);
void fadeSetToBlackInIfBlack(f32);
void fadeSetToBlackOutIfNotBlack(f32);
u8 itemDataBiosCheckExportable(void*);
u8 itemDataBiosCheckImportable(void*);
void* itemDataBiosGetPtr(u16);
u8 pokemonBiosGetFuseiFlag(Pokemon*);
u8 pokemonBiosGetTamagoFlag(Pokemon*);
u8 pokemonCheckValid(Pokemon*);
u8 menuCBRule_CheckPokemonEventFlag(Pokemon*);
u8 menuCBRule_CheckPokemonError(Pokemon*, s32);
u8 winSeqCheckMove(s32);
void menuCursorNormal(tagWINDOW_WORK*, s32);
void* pokemonGetStatus(Pokemon*, s32, s32, s32);

u32 GSmsgGetCharLength(void*);
void GSsndPlayNow(s32);
void winMsgOpen(s32, s32, s32, s32);
void winMsgOpenWithSE(s32, s32, s32, s32, s32);
void winMsgClose(s32);
s8 menuSubOpenYesNoField();
s8 menuSubOpenYesNo(s32, s32, s32, s32);
s32 GSfloorGetCurrentFloorGroupID();
s32 floorGetNextFloorID();
void gamedatasaveSetStatus(s32, s32, s32);
s32 memcardTaskCall(s32, s32, s32);
void GSfloorPush(s32);
void floorWaitForChange();
void GSthreadUnblockGroup(s32);
void GSthreadSwitch();
void floorMapSetDisp(s32);
void scriptModelStopMotion(u32);
void msgctrlSetValue(s32, u32);
void menuSetEnablePort(s32);
u8 gbaCommandIsConnected(s32);
s32 gbaCommandChangePokemon(s32, Pokemon*, s32, s32);
s32 gbaCommandChangePokemonIsPrepared(s32);
void gbaCommandSetKeyState(s32, s32);
void memcardSetupTask(s32, s32, s32);
u8 memcardCheckTaskWaitGBA();
void memcardUnlockWaitGBA(s32);
s32 memcardGetTaskResult();
void memcardFinalizeTask();
u32 HSD_Rand();
void* savedataGetStatus(s32, s32);
void menuModelFree(MENU_MODEL*);
void menuModelTerm(MENU_MODEL*);
}

enum MENU_POKEMON_CB_TYPE { CB_TYPE_0 = 0, CB_TYPE_1, CB_TYPE_2 };

MenuItem* menuPtItemGetByMenuIdAndItemId(s32, u32, s32);
tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(s32, u32, s32);
void menuPtSpriteWorkSetSpriteId(tagSPRITE_WORK*, u32);
void menuPtWindowWorkDraw(tagWINDOW_WORK*);
void menuPtWindowWorkDraw(s32);
s32 menuPtSpriteWorkGetIndexFromId(tagWINDOW_WORK*, tagSPRITE_WORK*, u32);
extern "C" void menuPokemonStatusOpenFromPokemonChange(Pokemon*, Pokemon* (*)(Pokemon*, MENU_POKEMON_CB_TYPE, s32), s32);

namespace {

enum enumPlayerIndex { PLAYER_1 = 0, PLAYER_2 = 1 };
enum enumMenuState {
    MENU_STATE_0 = 0,
    MENU_STATE_1,
    MENU_STATE_2,
    MENU_STATE_3,
    MENU_STATE_4,
    MENU_STATE_5,
    MENU_STATE_6
};
enum MENU_POKEMONCHANGE_USERTYPE { USERTYPE_0 = 0, USERTYPE_1 = 1 };

u8 _isTemochiPokemonCheck();
void _setInfo(u32);
void _menuWait(f32);
void _pokemonChangeFadeIn(f32);
void _pokemonChangeFadeOut(f32);
bool _isPokemonExchangeAble(Pokemon*, enumPlayerIndex);
bool _isPokemonValid(Pokemon*, enumPlayerIndex);
s32 _getPokemonState(Pokemon*, enumPlayerIndex);
s32 _getQuantityBattleAbleWoIt(Hero*, s32, enumPlayerIndex);
s32 _actionSelect2or3(u32, u32, u32);
void _menuSetMsg(s32, u16, u32);
bool _isPokemonBattleAble(Pokemon*, enumPlayerIndex);
bool _pokemonChangeGetHinsi(Pokemon*);
u8 _isPokemonItemExchangeOk(Pokemon*, enumPlayerIndex);
s16 _selectDisplay_2p_offset();
void* pokemonChangeRequestPokemonFaceLoadCallBack(void*);
Pokemon* _cbMenuPokemonStatus(Pokemon*, MENU_POKEMON_CB_TYPE, s32);

class CMenuPokemonChange {
public:
    u8 pokemonExchangeCheck(enumPlayerIndex);
    u8 pokmonSelectCheck(enumPlayerIndex);
    u8 isPokemonLookAbleStatus(s32);
    void stateFunctionError(Pokemon*, u32);
    void stateFunctionCheckNext();
    u8 gbaConnectionCheckIsError();
    void stateFunctionSaveReport();
    void stateFunctionEvolution();
    void _pokemonChangeEvolutionEffect(Pokemon*, MENU_POKEMONCHANGE_USERTYPE, u16, POKEMON_EVOLUTION_INFO);
    void stateFunctionExChangeOK();
    void stateFunctionExChangeMain();
    void stateFunctionExChangeStart();
    void stateFunctionConfirmExChange();
    void stateFunctionSelectPokemon2DecideAfterWait();
    void stateFunctionSelectPokemon2PokeExChange();
    void stateFunctionSelectPokemon2CheckStatus();
    void stateFunctionSelectPokemon2Selected();
    void stateFunctionSelectPokemon2Main();
    void stateFunctionSelectPokemon1PokeExChange();
    void stateFunctionSelectPokemon1CheckStatus();
    void stateFunctionSelectPokemon1Chanceld();
    void stateFunctionSelectPokemon1Selected();
    void stateFunctionSelectPokemon1Main();
    void stateFunctionSelectPokemonStart();
    void stateFunctionSelectPokemon2Reset();
    void stateFunctionCheckconnection();
    void selectItemHookPrime(tagWINDOW_WORK*, tagSPRITE_WORK*, u32);
    void selectItemHook(tagWINDOW_WORK*, tagSPRITE_WORK*);
    void selectDrawHook(tagWINDOW_WORK*);
    void ctrlHook(tagWINDOW_WORK*);
    s32 getQuantityAllPokemon();
    s32 getQuantityHeroPokemon(enumPlayerIndex);
    s32 selectPokemonMenuOpen();
    void waitMenuOpen();
    void oneMenuLoad(s32);
    void menuStateChange(enumMenuState);
    void bgDrawFadeIn(f32);
    void bgDrawFadeIn();
    bool bgDrawFadeIsLive();
    void bgDrawFadeOut();
    void setMenuByTbl(s32*);
    void requestPokemonFaceLoad();
    Pokemon* pokemonStatusCallback(Pokemon*, MENU_POKEMON_CB_TYPE, enumPlayerIndex);
    s32 pokemonStatusSearch(s32, s32);
    void menuPokemonStatusExecute(enumPlayerIndex);
    void loop();
    void main();
    void bgModelRelease();
    void bgModelLoad();
    void init();

    void loadModels(s32 menuId, u32 itemId)
    {
        MenuItem* item = menuPtItemGetByMenuIdAndItemId(menuId, itemId, 0);
        for (s32 i = 0; i < 2; i++) {
            menuModelInit(&m_model[i], item->w, item->h);
            menuModelLoadPokemon(&m_model[i], getPokemonByIndex(m_sel[i]));
            menuModelCheck(&m_model[i], 1);
        }
    }

    void releaseModels()
    {
        for (s32 i = 0; i < 2; i++) {
            menuModelFree(&m_model[i]);
            menuModelTerm(&m_model[i]);
        }
    }

    s32 getSelHeroIndex(enumPlayerIndex p)
    {
        s32 index = m_sel[p];
        if (index >= getQuantityHeroPokemon(PLAYER_1)) {
            index -= getQuantityHeroPokemon(PLAYER_1);
        }
        return index;
    }

    Pokemon* getSelPokemon(enumPlayerIndex p)
    {
        return getPokemonByIndex(m_sel[p]);
    }

    void setState(s32 s)
    {
        m_state.next = s;
        memset(m_state.work, 0, 0x40);
    }

    Pokemon* getPokemonByIndex(int index)
    {
        s32 second = 0;
        if (index >= getQuantityHeroPokemon(PLAYER_1)) {
            index -= getQuantityHeroPokemon(PLAYER_1);
            second = 1;
        }
        Hero* hero = (second == 0) ? m_hero0 : (Hero*)m_hero1;
        return hero->getPokemon(index);
    }

    s32 m_menuState;
    s32 m_menuTbl[8];
    Hero* m_hero0;
    u8 m_hero1[0x978];
    s32 m_player;
    CState m_state;
    s32 m_menuSeq;
    void* m_saveBuf;
    bool m_flags[2];
    s32 m_bgModel;
    s32 m_bgGSmodel;
    s32 m_sel[2];
    s32 m_cursor;
    MENU_MODEL m_model[2];
    s32 m_evoId;
    u64 m_time;
    bool m_flagC50;
    bool m_flagC51;
};

CMenuPokemonChange MenuPokemonChange;

}

namespace {

s32 _getPokemonState(Pokemon* pokemon, enumPlayerIndex player)
{
    if (!pokemon) {
        return 0;
    }
    if (pokemonBiosGetFuseiFlag(pokemon)) {
        return 1;
    }
    if (!pokemonCheckValid(pokemon)) {
        return 0;
    }
    if (pokemonBiosGetTamagoFlag(pokemon)) {
        return 2;
    }
    if (pokemon->isDarkPokemon()) {
        return 3;
    }
    if (!menuCBRule_CheckPokemonEventFlag(pokemon)) {
        return 5;
    }
    if (!menuCBRule_CheckPokemonError(pokemon, 0)) {
        return 6;
    }
    if (_isPokemonItemExchangeOk(pokemon, player)) {
        return 7;
    }
    return 4;
}

}

namespace {

u8 _isPokemonItemExchangeOk(Pokemon* pokemon, enumPlayerIndex player)
{
    u16 itemId = pokemon->getItemDataId();
    if (itemId == 0) {
        return 1;
    }
    if (player == 0) {
        if (!itemDataBiosCheckExportable(itemDataBiosGetPtr(itemId))) {
            return 0;
        }
    } else if (!itemDataBiosCheckImportable(itemDataBiosGetPtr(itemId))) {
        return 0;
    }
    return 1;
}

}

namespace {

bool _pokemonChangeGetHinsi(Pokemon* pokemon)
{
    return pokemon->getHp() == 0;
}

}

namespace {

bool _isPokemonBattleAble(Pokemon* pokemon, enumPlayerIndex player)
{
    switch (_getPokemonState(pokemon, player)) {
    case 0:
    case 1:
    case 2:
        return false;
    }
    return !_pokemonChangeGetHinsi(pokemon);
}

}

namespace {

bool _isPokemonValid(Pokemon* pokemon, enumPlayerIndex player)
{
    return _getPokemonState(pokemon, player) != 0;
}

}

namespace {

bool _isPokemonExchangeAble(Pokemon* pokemon, enumPlayerIndex player)
{
    return _getPokemonState(pokemon, player) == 7;
}

}

namespace {

s32 _getQuantityBattleAbleWoIt(Hero* hero, s32 skip, enumPlayerIndex player)
{
    s32 count = 0;
    for (s32 i = 0; i < 6; i++) {
        if (i != skip && _isPokemonBattleAble(hero->getPokemon(i), player)) {
            count++;
        }
    }
    return count;
}

}

namespace {

void _menuWait(f32 time)
{
    f32 elapsed = 0.0f;
    while (elapsed < time) {
        GSthreadSwitch();
        elapsed += timeGetLastFrameSec();
    }
}

}

namespace {

void _pokemonChangeFadeOut(f32 time)
{
    fadeSetToBlackOutIfNotBlack(time);
    fadeCheck(1);
}

}

namespace {

void _pokemonChangeFadeIn(f32 time)
{
    fadeSetToBlackInIfBlack(time);
}

}

namespace {

void _menuSetMsg(s32 window, u16 itemId, u32 value)
{
    tagWINDOW_WORK* win = windowSearchID(window);
    tagSPRITE_WORK* sprite = windowSearchItemID(win, itemId);
    if (value != 0) {
        if (win && sprite) {
            winSpriteSetDisp(sprite, 1);
            sprite->msg = value;
        }
    } else if (win && sprite) {
        sprite->msg = 0;
        winSpriteSetDisp(sprite, 0);
    }
}

}

namespace {

void _setInfo(u32 value)
{
    _menuSetMsg(0xD5, 0x61E, value);
}

}

namespace {

s32 _actionSelect2or3(u32 a, u32 b, u32 c)
{
    u32 result[3] = { 0, 0, 0 };
    result[0] = a;
    result[1] = b;
    result[2] = c;
    menuOpenCustom(0xD2, windowGetActiveID(), 0, 0, 0, 0);
    s32 window = (c == 0) ? 0x11A : 0x11B;
    menuOpenCustom(window, windowGetActiveID(), 0, 0, 0, 0);
    if (c == 0) {
        _menuSetMsg(window, 0x8C3, a);
        _menuSetMsg(window, 0x8C4, b);
    } else {
        _menuSetMsg(window, 0x8CD, a);
        _menuSetMsg(window, 0x8CC, b);
        _menuSetMsg(window, 0x8CB, c);
    }
    windowCheckCursor(window, 1);
    s32 value = windowGetValue(window);
    menuClose(window);
    menuClose(0xD2);
    if (value == -1) {
        if (c == 0) {
            value = 1;
        } else {
            value = 2;
        }
    }
    return result[value];
}

}

namespace {

void CMenuPokemonChange::init()
{
    memset(this, 0, 0xC58);
    m_hero0 = Hero::getHeroPtr();
    m_state.init();
    fadeSet(3, 0.0f);
    GSfsysReadWait(0x88C);
    menuStateChange(MENU_STATE_2);
    bgModelLoad();
    _pokemonChangeFadeIn(0.3f);
}

}

namespace {

void CMenuPokemonChange::bgModelLoad()
{
    s32 group = floorGetCurrentGroupID();
    m_bgModel = scriptModelOpen(0x5681000);
    m_bgGSmodel = GSresGetResource(group, m_bgModel);
    cameraPlayAnime(0x37C, 0x5691800, 0.0f, 1);
    cameraSetType(4);
    GSmodelSetVisibility(m_bgGSmodel, 0);
}

}

namespace {

void CMenuPokemonChange::bgModelRelease()
{
    scriptModelClose(m_bgModel);
}

}

namespace {

void CMenuPokemonChange::main()
{
    init();
    m_saveBuf = memcardMemAllocForSavedata();
    setState(1);
    loop();
    menuGBACSetRomVer(0, 0xFFFF);
    _pokemonChangeFadeOut(0.3f);
    menuStateChange(MENU_STATE_0);
    while (menuFaceCheckLoading()) {
        GSthreadSwitch();
    }
    bgModelRelease();
    GSfsysFree(0x88C);
    GSresFreeGroup(0x88C);
    if (GSfloorIsFloorPushed()) {
        GSfloorPop();
    } else {
        floorLink(floorGetPrevFloorID(), 0);
    }
}

}

namespace {

void CMenuPokemonChange::loop()
{
    u8* work = m_state.work;
    for (;;) {
        m_state.update();
        switch (m_state.current) {
        case 0:
            break;
        case 1:
            m_state.next = 5;
            memset(work, 0, 0x40);
            break;
        case 2:
            menuStateChange(MENU_STATE_2);
            bgDrawFadeIn();
            winMsgOpen(2, 0xC4A2, 1, 0);
            winMsgClose(1);
            m_state.next = 4;
            memset(work, 0, 0x40);
            break;
        case 3:
            menuStateChange(MENU_STATE_2);
            bgDrawFadeIn();
            winMsgOpen(2, 0xC49F, 1, 0);
            winMsgClose(1);
            m_state.next = 4;
            memset(work, 0, 0x40);
            break;
        case 4:
            m_saveBuf = memcardMemFreeForSavedata(m_saveBuf);
            return;
        case 5:
            stateFunctionCheckconnection();
            break;
        case 6:
            stateFunctionSelectPokemonStart();
            break;
        case 7:
            stateFunctionSelectPokemon1Main();
            break;
        case 8:
            stateFunctionSelectPokemon1Selected();
            break;
        case 9:
            stateFunctionSelectPokemon1Chanceld();
            break;
        case 10:
            stateFunctionSelectPokemon1CheckStatus();
            break;
        case 11:
            stateFunctionSelectPokemon1PokeExChange();
            break;
        case 12:
            stateFunctionSelectPokemon2Main();
            break;
        case 13:
            stateFunctionSelectPokemon2Selected();
            break;
        case 14:
            stateFunctionSelectPokemon2CheckStatus();
            break;
        case 15:
            stateFunctionSelectPokemon2PokeExChange();
            break;
        case 16:
            stateFunctionSelectPokemon2DecideAfterWait();
            break;
        case 17:
            stateFunctionConfirmExChange();
            break;
        case 18:
            stateFunctionExChangeStart();
            break;
        case 19:
            stateFunctionExChangeMain();
            break;
        case 20:
            stateFunctionExChangeOK();
            break;
        case 21:
            stateFunctionEvolution();
            break;
        case 22:
            stateFunctionSaveReport();
            break;
        case 23:
            stateFunctionCheckNext();
            break;
        }
    }
}

}

namespace {

Pokemon* _cbMenuPokemonStatus(Pokemon* pokemon, MENU_POKEMON_CB_TYPE type, s32 player)
{
    return MenuPokemonChange.pokemonStatusCallback(pokemon, type, (enumPlayerIndex)player);
}

}

namespace {

void CMenuPokemonChange::menuPokemonStatusExecute(enumPlayerIndex player)
{
    m_cursor = m_sel[player];
    Pokemon* pokemon = getPokemonByIndex(m_sel[player]);
    menuPokemonStatusOpenFromPokemonChange(pokemon, _cbMenuPokemonStatus, player);
    m_sel[player] = m_cursor;
}

}

namespace {

s32 CMenuPokemonChange::pokemonStatusSearch(s32 start, s32 step)
{
    s32 count = getQuantityAllPokemon();
    s32 index = m_cursor;
    do {
        index += step;
        if (index < 0 || index >= count) {
            return m_cursor;
        }
    } while (!isPokemonLookAbleStatus(index));
    return index;
}

}

namespace {

Pokemon* CMenuPokemonChange::pokemonStatusCallback(Pokemon* pokemon, MENU_POKEMON_CB_TYPE type, enumPlayerIndex player)
{
    getQuantityAllPokemon();
    s32 index = m_cursor;
    s32 result = index;
    if (type == 1) {
        result = pokemonStatusSearch(index, -1);
    } else if (type == 2) {
        result = pokemonStatusSearch(index, 1);
    }
    m_cursor = result;
    return getPokemonByIndex(m_cursor);
}

}

namespace {

void* pokemonChangeRequestPokemonFaceLoadCallBack(void* data)
{
    Pokemon** list = (Pokemon**)data;
    if (list == 0) {
        return 0;
    }
    u32 index = (u32)list[13];
    if (index >= 13) {
        return 0;
    }
    list[13] = (Pokemon*)(index + 1);
    return list[index];
}

}

namespace {

void CMenuPokemonChange::requestPokemonFaceLoad()
{
    static Pokemon* stPokemonListFace[14];
    s32 player = 0;
    s32 count = 0;
    for (; player < 2; player++) {
        for (s32 i = 0; i < 6; i++) {
            Hero* hero = (player == 0) ? m_hero0 : (Hero*)m_hero1;
            Pokemon* pokemon = hero->getPokemon(i);
            if (_isPokemonValid(pokemon, (enumPlayerIndex)player)) {
                stPokemonListFace[count++] = pokemon;
            }
        }
    }
    stPokemonListFace[count] = 0;
    stPokemonListFace[13] = 0;
    menuFaceLoad(0, pokemonChangeRequestPokemonFaceLoadCallBack, stPokemonListFace);
}

}

namespace {

s16 _selectDisplay_2p_offset()
{
    MenuItem* a = menuPtItemGetByMenuIdAndItemId(0xD4, 0x60D, 0);
    MenuItem* b = menuPtItemGetByMenuIdAndItemId(0xD4, 0x60E, 0);
    return b->x - a->x;
}

}

namespace {

void CMenuPokemonChange::setMenuByTbl(s32* tbl)
{
    s32 count = 0;
    while (tbl[count] != 0) {
        count++;
    }
    u32 i;
    s32 id;
    for (i = 0; i < 8; i++) {
        if (0 == m_menuTbl[i] || m_menuTbl[i] != tbl[i]) {
            break;
        }
    }
    u32 common = i;
    for (i = common; (id = m_menuTbl[i]) != 0 && i < 8; i++) {
        s32* p;
        u8 found;
        for (p = tbl, found = 0; *p != 0; p++) {
            if (id == *p) {
                found = 1;
                break;
            }
        }
        if (!found) {
            menuCloseCustom(id, 2, 0);
        }
    }
    u8 loaded = 0;
    for (i = common; (id = tbl[i]) != 0 && i < 8; i++) {
        oneMenuLoad(id);
        loaded = 1;
    }
    if (!loaded) {
        s32 last = tbl[count - 1];
        if (last == 0xD6) {
            oneMenuLoad((u16)last);
        }
    }
    memset(m_menuTbl, 0, 0x20);
    memcpy(m_menuTbl, tbl, (count + 1) * 4);
}

}

namespace {

void CMenuPokemonChange::bgDrawFadeOut()
{
    menuOpenCustom(0xDF, windowGetActiveID(), 0, 2, 0, 0);
    menuSetDisp(0xDF, 1);
    tagWINDOW_WORK* window = windowSearchID(0xDF);
    f32 t = 0.0f;
    while (t < 0.3f) {
        window->alpha = (u8)(255.0f * (t / 0.3f));
        GSthreadSwitch();
        t += timeGetLastFrameSec();
    }
    window->alpha = 0xFF;
}

}

namespace {

bool CMenuPokemonChange::bgDrawFadeIsLive()
{
    return windowSearchID(0xDF) ? true : false;
}

}

namespace {

void CMenuPokemonChange::bgDrawFadeIn()
{
    bgDrawFadeIn(0.3f);
}

}

namespace {

void CMenuPokemonChange::bgDrawFadeIn(f32 time)
{
    tagWINDOW_WORK* window = windowSearchID(0xDF);
    if (window) {
        f32 t = 0.0f;
        while (t < time) {
            window->alpha = (u8)(255.0f * (1.0f - t / time));
            GSthreadSwitch();
            t += timeGetLastFrameSec();
        }
        window->alpha = 0;
        menuCloseCustom(0xDF, 0, 1);
    }
}

}

namespace {

void CMenuPokemonChange::menuStateChange(enumMenuState state)
{
    static s32 tbl0[] = { 0 };
    static s32 tbl1[] = { 0xD3, 0 };
    static s32 tbl2[] = { 0xD3, 0xE1, 0 };
    static s32 tbl3[] = { 0xD3, 0xE1, 0xD4, 0xD5, 0xD6, 0 };
    static s32 tbl4[] = { 0xD3, 0xE1, 0xDD, 0 };
    static s32 tbl5[] = { 0xD3, 0xE1, 0xDE, 0 };
    m_menuState = state;
    switch (state) {
    case 0:
        setMenuByTbl(tbl0);
        break;
    case 1:
        setMenuByTbl(tbl1);
        break;
    case 2:
        setMenuByTbl(tbl2);
        break;
    case 3:
    case 4:
        setMenuByTbl(tbl3);
        break;
    case 5:
        setMenuByTbl(tbl4);
        break;
    case 6:
        setMenuByTbl(tbl5);
        break;
    }
    m_flagC51 = 0;
}

}

namespace {

void CMenuPokemonChange::oneMenuLoad(s32 id)
{
    m_menuSeq = id;
    if (id == 0xD6) {
        selectPokemonMenuOpen();
    } else {
        menuOpenCustom(id, windowGetActiveID(), 0, 4, 0, 0);
        menuSetDisp(id, id == 0xD3);
    }
}

}

namespace {

void CMenuPokemonChange::waitMenuOpen()
{
    while (winSeqCheckMove(m_menuSeq)) {
        GSthreadSwitch();
    }
}

}

namespace {

s32 CMenuPokemonChange::selectPokemonMenuOpen()
{
    s32 player = m_player;
    windowSearchID(0xD6);
    MenuDataBios* data = menuDataBiosGetPtr(0xD6);
    MenuItemBios* item = menuItemBiosGetPtr(0xD6, data->first);
    for (s32 i = 0; i < 2; i++) {
        Hero* hero;
        if (i == 0) {
            hero = m_hero0;
        } else {
            hero = (Hero*)m_hero1;
        }
        for (s32 j = 0; j < 6; j++) {
            item->valid = _isPokemonValid(hero->getPokemon(j), (enumPlayerIndex)player);
            item = menuItemBiosGetPtr(0xD6, item->next);
        }
    }
    static bool isDirty = false;
    if (!isDirty) {
        isDirty = true;
        s16 offset = _selectDisplay_2p_offset();
        item = menuItemBiosGetPtr(0xD6, 0x627);
        for (s32 k = 0; k < 6; k++) {
            item->x += offset;
            item = menuItemBiosGetPtr(0xD6, item->next);
        }
    }
    s32 flags = m_flagC51 ? 4 : 0;
    menuOpenCustom(0xD6, windowGetActiveID(), &m_sel[player], flags, 0, 0);
    _setInfo(0xC491);
    return 0xD6;
}

}

namespace {

s32 CMenuPokemonChange::getQuantityHeroPokemon(enumPlayerIndex player)
{
    Hero* hero = (player == 0) ? m_hero0 : (Hero*)m_hero1;
    s32 i;
    for (i = 0; i < 6; i++) {
        if (!_isPokemonValid(hero->getPokemon(i), player)) {
            break;
        }
    }
    return i;
}

}

namespace {

s32 CMenuPokemonChange::getQuantityAllPokemon()
{
    return getQuantityHeroPokemon(PLAYER_1) + getQuantityHeroPokemon(PLAYER_2);
}

}

namespace {

void CMenuPokemonChange::ctrlHook(tagWINDOW_WORK* window)
{
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            switch (window->menuId) {
            case 0xD4:
            case 0xD6:
                winSeqSetMenu(window->menuId, 0x1BC);
            }
            window->seqSet = 1;
        }
        break;
    case 3:
        if (window->seqSet == 0) {
            window->seqSet = 1;
        }
        break;
    }
}

}

namespace {

void CMenuPokemonChange::selectDrawHook(tagWINDOW_WORK* window)
{
    if (m_menuState != 0) {
        tagWINDOW_WORK* win = windowSearchID(0xE1);
        if (win) {
            menuPtWindowWorkDraw(win);
        }
        win = windowSearchID(0xD4);
        if (win) {
            tagSPRITE_WORK* sprite = menuPtSpriteWorkGetByItemID(win->menuId, 0x60D, 0);
            s16 old = win->offset;
            win->offset = old;
            menuPtSpriteWorkSetSpriteId(sprite, 0x20F);
            windowSetParam(win, 0, 0);
            menuPtWindowWorkDraw(win);
            win->offset = _selectDisplay_2p_offset() - old;
            menuPtSpriteWorkSetSpriteId(sprite, 0x20E);
            windowSetParam(win, 0, 1);
            menuPtWindowWorkDraw(win);
            win->offset = old;
            menuPtWindowWorkDraw(0xD5);
        }
        win = windowSearchID(0xDD);
        if (win) {
            tagSPRITE_WORK* sprite = menuPtSpriteWorkGetByItemID(win->menuId, 0x63E, 0);
            win->offset = 0;
            menuPtSpriteWorkSetSpriteId(sprite, 0x20F);
            windowSetParam(win, 0, 0);
            menuPtWindowWorkDraw(win);
            win->offset = _selectDisplay_2p_offset();
            menuPtSpriteWorkSetSpriteId(sprite, 0x20E);
            windowSetParam(win, 0, 1);
            menuPtWindowWorkDraw(win);
        }
        win = windowSearchID(0xDE);
        if (win) {
            tagSPRITE_WORK* sprite = menuPtSpriteWorkGetByItemID(win->menuId, 0x650, 0);
            win->offset = 0;
            menuPtSpriteWorkSetSpriteId(sprite, 0x20F);
            windowSetParam(win, 0, 0);
            menuPtWindowWorkDraw(win);
            win->offset = _selectDisplay_2p_offset();
            menuPtSpriteWorkSetSpriteId(sprite, 0x20E);
            windowSetParam(win, 0, 1);
            menuPtWindowWorkDraw(win);
        }
        m_time += timeGetLastFrameTime();
    }
}

}

namespace {

void CMenuPokemonChange::selectItemHook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    selectItemHookPrime(window, sprite, sprite->itemId);
}

}

namespace {

void CMenuPokemonChange::selectItemHookPrime(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, u32 itemId)
{
    s32 waza;
    Pokemon* target;
    u16 item;
    MENU_MODEL* model;
    s32 player = windowGetParam(window, 0);
    u32 color;
    Hero* hero = (player == 0) ? m_hero0 : (Hero*)m_hero1;
    Pokemon* pokemon = getSelPokemon((enumPlayerIndex)player);
    u8 pulse;
    u32 msg;
    bool visible;
    u8 windowAlpha = window->alpha;
    sprite->rgba.a = windowAlpha;
    color = (windowAlpha & 0xFF) | 0xFFFFFF00;
    if (m_state.current == 13 || m_state.current == 8) {
        pulse = 0xFF;
    } else {
        f32 scale = 1.0f;
        u32 rate = (u32)(scale * GSgfxVideoGetVsyncRate());
        u32 phase = m_time % rate;
        f32 wave = (f32)sin(3.1415927f * ((f32)phase / (f32)rate));
        u32 value = (u32)(205.0f * wave + 50.0f);
        pulse = (u8)(sprite->rgba.a * value / 255);
    }
    switch (itemId) {
    case 0x5F3:
    case 0x5F4:
    case 0x5F5:
    case 0x5F6:
    case 0x5F7:
    case 0x5F8: {
        s32 index = menuPtSpriteWorkGetIndexFromId(window, sprite, 0x5F3);
        Pokemon* target = hero->getPokemon(index);
        if (_isPokemonValid(target, (enumPlayerIndex)player)) {
            menuFaceDisp(window, sprite, target);
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x5F9:
    case 0x5FA:
    case 0x5FB:
    case 0x5FC:
    case 0x5FD:
    case 0x5FE: {
        s32 index = menuPtSpriteWorkGetIndexFromId(window, sprite, 0x5F9);
        Pokemon* target = hero->getPokemon(index);
        switch (_getPokemonState(target, (enumPlayerIndex)player)) {
        case 0:
        case 4:
        case 7:
            sprite->color = 0xFFFFFFFF;
            break;
        case 3:
            sprite->color = 0xB473C8FF;
            break;
        default:
            sprite->color = 0xDC6464FF;
            break;
        }
        break;
    }
    case 0x5FF:
    case 0x600:
    case 0x601:
    case 0x602:
    case 0x603:
    case 0x604: {
        s32 index = menuPtSpriteWorkGetIndexFromId(window, sprite, 0x5FF);
        target = hero->getPokemon(index);
        item = 0;
        if (_isPokemonValid(target, (enumPlayerIndex)player)) {
            item = pokemonBiosGetItemDataId(target);
        }
        sprite->color = 0xFFFFFFFF;
        if (item != 0 && !_isPokemonItemExchangeOk(target, (enumPlayerIndex)player)) {
            sprite->color = 0xFF0000FF;
        }
        winSpriteSetDisp(sprite, item != 0);
        break;
    }
    case 0x60F:
    case 0x610:
    case 0x611:
    case 0x612:
    case 0x613:
    case 0x614: {
        s32 index = menuPtSpriteWorkGetIndexFromId(window, sprite, 0x60F);
        Pokemon* target = hero->getPokemon(index);
        msg = 0;
        s32 state = _getPokemonState(target, (enumPlayerIndex)player);
        if (state >= 3 || state < 0) {
            u8 sex = menuSubGetPokemonSexForFightDisp(target);
            switch (fn_80098B44(sex, target)) {
            case 0:
                msg = 0x9C5;
                break;
            case 1:
                msg = 0x9C6;
                break;
            }
        }
        if (msg != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(msg));
            GSmsgPrint2(window->msgHandle, 0, 0, color, 0x4276);
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x615:
    case 0x616:
    case 0x617:
    case 0x618:
    case 0x619:
    case 0x61A: {
        s32 index = menuPtSpriteWorkGetIndexFromId(window, sprite, 0x615);
        u32 msg;
        Pokemon* target;
        target = hero->getPokemon(index);
        msg = 0x4277;
        switch (_getPokemonState(target, (enumPlayerIndex)player)) {
        case 1:
            msgctrlSetValue(0x37, GSmsgGetGSchar(0x56C));
            break;
        case 2:
            msgctrlSetValue(0x37, GSmsgGetGSchar(0x56B));
            break;
        case 0:
            msg = 0;
            break;
        default:
            s32 tmp1 = (u32)pokemonBiosGetNicknamePtr(target);
            msgctrlSetValue(0x37, tmp1);
            break;
        }
        if (msg != 0) {
            u32 rect = GSmsgGetRect(msg);
            s16 rectW = rect >> 16;
            u32 rf_t = sprite->w;
            s16 x = (s16)(rf_t / 2 - rectW / 2);
            GSmsgPrint2(window->msgHandle, x - 1, 0, color, 0x4277);
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x61B:
        s32 tmp1 = heroBiosGetNamePtr(hero);
        msgctrlSetValue(0x37, tmp1);
        GSmsgPrint2(window->msgHandle, 0, 0, color, 0x4277);
        break;
    case 0x605:
    case 0x606:
    case 0x607:
    case 0x608:
    case 0x609:
    case 0x60A:
    case 0x60B:
    case 0x60C:
        winSpriteSetDisp(sprite, m_player == player);
        break;
    case 0x8B9:
    case 0x8BA:
    case 0x8BB:
    case 0x8BC:
    case 0x8BD:
    case 0x8BE: {
        s32 selected = getSelHeroIndex((enumPlayerIndex)player);
        s32 index = menuPtSpriteWorkGetIndexFromId(window, sprite, 0x8B9);
        bool visible = false;
        if (selected == index) {
            s32 state = m_state.current;
            if (player == 0) {
                visible = (state >= 0xC && state <= 0x10);
            } else if (player == 1) {
                visible = (state == 0x10);
            }
        }
        winSpriteSetDisp(sprite, visible);
        break;
    }
    case 0x8CE:
    case 0x8CF:
    case 0x8D0:
    case 0x8D1:
    case 0x8D2:
    case 0x8D3: {
        s32 value = windowGetValue(0xD6);
        s32 index = value;
        if (value >= getQuantityHeroPokemon(PLAYER_1)) {
            index -= getQuantityHeroPokemon(PLAYER_1);
        }
        s32 who = (value >= getQuantityHeroPokemon(PLAYER_1)) ? 1 : 0;
        s32 spriteIndex = menuPtSpriteWorkGetIndexFromId(window, sprite, 0x8CE);
        visible = false;
        if (spriteIndex == index && player == who && m_state.current != 0x10
            && spriteIndex < getQuantityHeroPokemon((enumPlayerIndex)who)) {
            visible = true;
        }
        winSpriteSetDisp(sprite, visible);
        sprite->rgba.a = pulse;
        break;
    }
    case 0x620:
        winSpriteSetDisp(sprite, m_flagC50);
        if (m_flagC50) {
            menuCBMessageCenterDisp(window, sprite, 0xC4AC);
        }
        break;
    case 0x61F:
        winSpriteSetDisp(sprite, m_flagC50);
        break;
    case 0x8D4: {
        s32 value = windowGetValue(0xD6);
        s32 count2 = getQuantityHeroPokemon(PLAYER_2);
        s32 count1 = getQuantityHeroPokemon(PLAYER_1);
        sprite->rgba.a = pulse;
        winSpriteSetDisp(sprite, value == count1 + count2);
        break;
    }

    case 0x8BF:
        winSpriteSetDisp(sprite, windowGetValue(window->menuId) == 0);
        break;
    case 0x8C0:
        winSpriteSetDisp(sprite, windowGetValue(window->menuId) == 1);
        break;
    case 0x8C5:
        winSpriteSetDisp(sprite, windowGetValue(window->menuId) == 0);
        break;
    case 0x8C6:
        winSpriteSetDisp(sprite, windowGetValue(window->menuId) == 1);
        break;
    case 0x8C7:
        winSpriteSetDisp(sprite, windowGetValue(window->menuId) == 2);
        break;
    case 0x63D:
        if (window->alpha == 0xFF) {
            model = &m_model[player];
            menuModelAdjustCamera(model);
            menuModelSetSize(model, window->offset + sprite->x, sprite->y, sprite->w, sprite->h);
            menuModelSetZoom(model, pokemonBiosGetPokemonDataId(pokemon) == 0x18E ? 0.4f : 0.65f);
            menuModelRender(model);
        }
        break;
    case 0x640:
        selectItemHookPrime(window, sprite, 0x61B);
        break;
    case 0x642:
        msgctrlSetValue(0x34, pokemon->getLevel());
        GSmsgPrint2(window->msgHandle, 0, 0, color, 0x426F);
        break;
    case 0x7B3:
        msgctrlSetValue(0x37, (u32)pokemon->getNicknamePtr());
        switch (pokecoloGetCountryCode()) {
        case 0:
            GSmsgPrint2(window->msgHandle, 0, 0, color, 0x4276);
            break;
        case 1:
        case 2:
            GSmsgPrint2(window->msgHandle, 0, 0, color, 0x4277);
            break;
        }
        break;
    case 0x7B4: {
        u32 msg;
        u8 sex = menuSubGetPokemonSexForFightDisp(pokemon);
        switch (fn_80098B44(sex, pokemon)) {
        case 0:
            msg = 0x9C5;
            break;
        case 1:
            msg = 0x9C6;
            break;
        case 3:
        case 2:        default:
            msg = 0;
            break;
        }
        if (msg != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(msg));
            GSmsgPrint2(window->msgHandle, 0, 0, color, 0x4276);
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x643:
        msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonDataBiosGetName(pokemon->getPokemonDataPtr())));
        switch (pokecoloGetCountryCode()) {
        case 0:
            GSmsgPrint2(window->msgHandle, 0, 0, color, 0x4276);
            break;
        case 1:
        case 2:
            GSmsgPrint2(window->msgHandle, 0, 0, color, 0x4277);
            break;
        }
        break;
    case 0x645:
    case 0x646:
    case 0x647:
    case 0x648: {
        s32 index = menuPtSpriteWorkGetIndexFromId(window, sprite, 0x645);
        waza = pokemonBiosGetPokemonWazaDataId(pokemon, (u16)index);
        if (pokemonWazaCheckValid(pokemon, (u16)index)) {
            u32 name = wazaGetStatus(0, waza, 1, 0);
            if (name != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                GSmsgPrintRect(window->msgHandle, 0, 0, sprite->w, sprite->h, color, 0x4277);
                winSpriteSetDisp(sprite, 1);
            } else {
                winSpriteSetDisp(sprite, 0);
            }
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x649:
        break;
    case 0x64A: {
        u16 item = pokemonGetSoubiItemDataId(pokemon);
        if (item != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(item))));
            GSmsgPrint2(window->msgHandle, 0, 0, color, 0x4277);
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    case 0x64B:
        sprite->msg = 0xC495;
        winSpriteSetDisp(sprite, m_flags[player] == 0);
        break;
    case 0x64C:
        winSpriteSetDisp(sprite, m_flags[player] == 0);
        sprite->msg = 0x4295;
        break;
    case 0x637:
        winSpriteSetDisp(sprite, m_flags[player] == 0);
        break;
    case 0x638:
        winSpriteSetDisp(sprite, m_flags[player] == 0);
        break;
    case 0x64D:
        winSpriteSetDisp(sprite, m_flags[player]);
        break;
    case 0x652:
        selectItemHookPrime(window, sprite, 0x63D);
        break;
    case 0x653:
        selectItemHookPrime(window, sprite, 0x61B);
        break;
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionCheckconnection()
{
    Hero* list[4] = { 0, 0, 0, 0 };
    list[1] = (Hero*)m_hero1;
    if (openMenuGBA(0, 9, list) < 0) {
        setState(4);
    } else {
        requestPokemonFaceLoad();
        setState(m_state.current + 1);
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon2Reset()
{
    m_sel[1] = getQuantityHeroPokemon(PLAYER_1);
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemonStart()
{
    m_sel[0] = 0;
    m_sel[1] = getQuantityHeroPokemon(PLAYER_1);
    setState(m_state.current + 1);
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon1Main()
{
    stateFunctionSelectPokemon2Reset();
    m_player = 0;
    if (bgDrawFadeIsLive()) {
        menuStateChange(MENU_STATE_2);
        bgDrawFadeIn();
    }
    menuStateChange(MENU_STATE_3);
    m_flagC50 = 1;
    windowCheckCursor(0xD6, 1);
    m_flagC50 = 0;
    s32 value = windowGetValue(0xD6);
    if (value == -1 || value >= getQuantityAllPokemon()) {
        setState(9);
    } else {
        m_sel[m_player] = value;
        setState(8);
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon1Selected()
{
    if (pokmonSelectCheck(PLAYER_1)) {
        s32 selected = m_sel[m_player];
        s32 cmp = (selected >= getQuantityHeroPokemon(PLAYER_1)) ? 1 : 0;
        s32 action;
        if (cmp == m_player) {
            action = _actionSelect2or3(0xC494, 0xC495, 0xC4AC);
        } else {
            action = _actionSelect2or3(0xC494, 0xC4AC, 0);
        }
        switch (action) {
        case 0xC494:
            setState(0xA);
            break;
        case 0xC495:
            setState(0xB);
            break;
        case 0xC4AC:
            setState(7);
            break;
        }
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon1Chanceld()
{
    _setInfo(0xC499);
    s32 action = _actionSelect2or3(0x426A, 0x426B, 0);
    _setInfo(0);
    switch (action) {
    case 0x426A:
        setState(2);
        break;
    case 0x426B:
        setState(7);
        break;
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon1CheckStatus()
{
    _pokemonChangeFadeOut(0.3f);
    menuStateChange(MENU_STATE_0);
    menuPokemonStatusExecute(PLAYER_1);
    m_flagC51 = 1;
    menuStateChange(MENU_STATE_3);
    waitMenuOpen();
    _pokemonChangeFadeIn(0.3f);
    fadeCheck(1);
    setState(8);
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon1PokeExChange()
{
    if (pokemonExchangeCheck(PLAYER_1)) {
        setState(0xC);
        stateFunctionSelectPokemon2Reset();
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon2Main()
{
    m_player = 1;
    menuSetEnablePort(2);
    menuStateChange(MENU_STATE_4);
    m_flagC50 = 1;
    windowCheckCursor(0xD6, 1);
    m_flagC50 = 0;
    menuSetEnablePort(1);
    if (!gbaConnectionCheckIsError()) {
        s32 value = windowGetValue(0xD6);
        if (value == -1 || value >= getQuantityAllPokemon()) {
            setState(7);
        } else {
            m_sel[m_player] = value;
            setState(0xD);
        }
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon2Selected()
{
    if (pokmonSelectCheck(PLAYER_2)) {
        menuSetEnablePort(2);
        s32 selected = m_sel[m_player];
        s32 cmp = (selected >= getQuantityHeroPokemon(PLAYER_1)) ? 1 : 0;
        s32 action;
        if (cmp == m_player) {
            action = _actionSelect2or3(0xC494, 0xC495, 0xC4AC);
        } else {
            action = _actionSelect2or3(0xC494, 0xC4AC, 0);
        }
        menuSetEnablePort(1);
        if (!gbaConnectionCheckIsError()) {
            switch (action) {
            case 0xC494:
                setState(0xE);
                break;
            case 0xC495:
                setState(0xF);
                break;
            case 0xC4AC:
                setState(0xC);
                break;
            }
        }
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon2CheckStatus()
{
    _pokemonChangeFadeOut(0.3f);
    menuStateChange(MENU_STATE_0);
    menuSetEnablePort(2);
    menuPokemonStatusExecute(PLAYER_2);
    menuSetEnablePort(1);
    m_flagC51 = 1;
    menuStateChange(MENU_STATE_4);
    waitMenuOpen();
    _pokemonChangeFadeIn(0.3f);
    fadeCheck(1);
    if (menuGetLastError() == 1) {
        GSsndPlayNow(0x13);
        winMsgOpen(2, 0xC4A3, 1, 0);
        setState(2);
    } else {
        setState(0xD);
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon2PokeExChange()
{
    if (pokemonExchangeCheck(PLAYER_2)) {
        setState(0x10);
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionSelectPokemon2DecideAfterWait()
{
    _menuWait(0.6f);
    loadModels(0xDD, 0x63D);
    bgDrawFadeOut();
    setState(0x11);
}

}

namespace {

void CMenuPokemonChange::stateFunctionConfirmExChange()
{
    m_flags[0] = 0;
    m_flags[1] = 0;
    menuStateChange(MENU_STATE_5);
    bgDrawFadeIn();
    menuSetEnablePort(3);
    bool ready1 = false;
    bool ready2 = false;
    while (!ready1 || !ready2) {
        u32 down1 = windowGetPortKeyInfo(1)->down;
        u32 down2 = windowGetPortKeyInfo(2)->down;
        if (gbaConnectionCheckIsError()) {
            goto done;
        }
        if (GSfsysGetDriveStatus() != 5) {
            if (down1 & 0x10) {
                if (!ready1) {
                    GSsndPlayNow(0x11);
                }
                ready1 = 1;
            } else if (down1 & 0x20) {
                GSsndPlayNow(0x12);
                if (!ready1) {
                    break;
                }
                ready1 = 0;
            }
            if (down2 & 0x10) {
                if (!ready2) {
                    GSsndPlayNow(0x11);
                }
                ready2 = 1;
            } else if (down2 & 0x20) {
                GSsndPlayNow(0x12);
                if (!ready2) {
                    break;
                }
                ready2 = 0;
            }
        }
        GSthreadSwitch();
        m_flags[0] = ready1;
        m_flags[1] = ready2;
    }
    m_flags[0] = ready1;
    m_flags[1] = ready2;
    if (!ready1 || !ready2) {
        setState(7);
    } else {
        void* src = savedataGetStatus(0, 0);
        memcpy(m_saveBuf, src, 0x27FD0);
        setState(0x12);
    }
done:
    bgDrawFadeOut();
    releaseModels();
    menuSetEnablePort(1);
}

}

namespace {

void CMenuPokemonChange::stateFunctionExChangeStart()
{
    loadModels(0xDE, 0x652);
    menuStateChange(MENU_STATE_6);
    bgDrawFadeIn();
    _menuWait(1.0f);
    u32 money0 = heroGetStatus(m_hero0, 1, 0);
    u32 money1 = heroGetStatus((Hero*)m_hero1, 1, 0);
    char* name0 = pokemonBiosGetNicknamePtr(getPokemonByIndex(m_sel[0]));
    char* name1 = pokemonBiosGetNicknamePtr(getPokemonByIndex(m_sel[1]));
    msgctrlSetValue(0x4D, money1);
    msgctrlSetValue(0x57, money0);
    msgctrlSetValue(0x32, (u32)name0);
    msgctrlSetValue(0x33, (u32)name1);
    winMsgOpen(2, 0xC49A, 1, 0);
    winMsgOpen(2, 0xC49B, 1, 0);
    winMsgClose(1);
    bgDrawFadeOut();
    releaseModels();
    menuStateChange(MENU_STATE_1);
    setState(0x13);
}

}

namespace {

void CMenuPokemonChange::stateFunctionExChangeMain()
{
    static Pokemon pokemon;
    pokemonInit((u32)&pokemon);
    Pokemon* pokemons[2];
    for (s32 i = 0; i < 2; i++) {
        pokemons[i] = getPokemonByIndex(m_sel[i]);
    }
    DarkPokemon* dark = pokemons[0]->getDarkPokemon();
    if (dark) {
        dark->setPlace(place5, 0);
    }
    pokemonBiosCopy(&pokemon, pokemons[1]);
    pokemonBiosCopy(pokemons[1], pokemons[0]);
    pokemonBiosCopy(pokemons[0], &pokemon);
    bgDrawFadeIn(2.0f);
    _pokemonChangeFadeOut(0.0f);
    _pokemonChangeFadeIn(1.0f);
    cameraPlayAnime(floorGetCurrentGroupID(), 0xFCD1800, 0.0f, 0);
    GSthreadSwitch();
    GSsndPlayNow(0x462);
    floorMapSetDisp(1);
    scriptModelSetMotion(0xFCC1000, 0, 0, 0);
    _pokemonChangeFadeIn(3.0f);
    cameraWaitSyncAnime(1);
    _pokemonChangeFadeOut(0.7f);
    floorMapSetDisp(0);
    loadModels(0xDE, 0x652);
    menuStateChange(MENU_STATE_6);
    _pokemonChangeFadeIn(0.15f);
    setState(0x14);
}

}

namespace {

void CMenuPokemonChange::stateFunctionExChangeOK()
{
    pokemonBiosSetFriend(getPokemonByIndex(m_sel[0]), 0x46);
    pokemonBiosSetFriend(getPokemonByIndex(m_sel[1]), 0x46);
    memoDataSet(0, getPokemonByIndex(m_sel[0]));
    u32 money0 = heroGetStatus(m_hero0, 1, 0);
    u32 money1 = heroGetStatus((Hero*)m_hero1, 1, 0);
    char* name0 = pokemonBiosGetNicknamePtr(getPokemonByIndex(m_sel[0]));
    char* name1 = pokemonBiosGetNicknamePtr(getPokemonByIndex(m_sel[1]));
    msgctrlSetValue(0x4D, money0);
    msgctrlSetValue(0x57, money1);
    msgctrlSetValue(0x32, (u32)name0);
    msgctrlSetValue(0x33, (u32)name1);
    winMsgOpen(2, 0xC49C, 1, 0);
    winMsgClose(1);
    setState(0x15);
}

}

namespace {

void CMenuPokemonChange::_pokemonChangeEvolutionEffect(Pokemon* pokemon, MENU_POKEMONCHANGE_USERTYPE type, u16 species, POKEMON_EVOLUTION_INFO info)
{
    if (species != 0 && species != 0xFFFF) {
        switch (type) {
        case USERTYPE_0:
            pokemonEvolutionAll(pokemon, species, 0, &info, 0, 0, 0, 1);
            break;
        case USERTYPE_1:
            pokemonEvolutionAll(pokemon, species, 0, &info, 0, 1, 0, 1);
            break;
        }
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionEvolution()
{
    u16 extra;
    POKEMON_EVOLUTION_INFO info0;
    POKEMON_EVOLUTION_INFO info1;
    u8 evolve = 0;
    m_evoId = 0;
    u16 evo0 = pokemonEvolutionCheck(getPokemonByIndex(m_sel[0]), 2, 0, &extra, &info0);
    if (evo0 != 0 && evo0 != 0xFFFF) {
        evolve = 1;
    }
    u16 evo1 = pokemonEvolutionCheck(getPokemonByIndex(m_sel[1]), 2, 0, &extra, &info1);
    if (evo1 != 0 && evo1 != 0xFFFF) {
        evolve = 1;
        m_evoId = pokemonBiosGetPokemonDataId(getPokemonByIndex(m_sel[1]));
    }
    if (evolve) {
        _pokemonChangeFadeOut(0.3f);
        menuStateChange(MENU_STATE_0);
        releaseModels();
        bgModelRelease();
        GSthreadSwitch();
        _pokemonChangeFadeIn(0.0f);
        _pokemonChangeEvolutionEffect(getPokemonByIndex(m_sel[0]), USERTYPE_1, evo0, info0);
        _pokemonChangeEvolutionEffect(getPokemonByIndex(m_sel[1]), USERTYPE_0, evo1, info1);
        _pokemonChangeFadeOut(0.0f);
        bgModelLoad();
        loadModels(0xDE, 0x652);
        menuStateChange(MENU_STATE_6);
        _pokemonChangeFadeIn(0.3f);
        for (s32 i = 0; i < 2; i++) {
            Pokemon* pokemon = getPokemonByIndex(m_sel[i]);
            menuFaceLoad(pokemon, 0, 0);
            while (!menuFaceSearchEnable(menuFaceGetID(pokemon))) {
                GSthreadSwitch();
            }
        }
    }
    setState(0x16);
}

}

namespace {

void CMenuPokemonChange::stateFunctionSaveReport()
{
    u8 prepared;
    u8 saved;
    saved = 0;
    prepared = 0;
    winMsgOpen(2, 0xC49D, 1, 1);
    Pokemon* pokemon = getPokemonByIndex(m_sel[1]);
    s32 index = m_sel[1];
    if (index >= getQuantityHeroPokemon(PLAYER_1)) {
        index -= getQuantityHeroPokemon(PLAYER_1);
    }
    if (gbaCommandChangePokemon(2, pokemon, index, m_evoId) == 0) {
        s32 result;
        memcardSetupTask(8, 2, 0);
        do {
            if (!prepared && memcardCheckTaskWaitGBA()) {
                s32 ready = gbaCommandChangePokemonIsPrepared(2);
                if (ready >= 0) {
                    if (ready != 0) {
                        memcardUnlockWaitGBA(0);
                    } else {
                        memcardUnlockWaitGBA(1);
                    }
                    prepared = 1;
                }
            }
            GSthreadSwitch();
            result = memcardGetTaskResult();
        } while (result == 0);
        gbaCommandSetKeyState(2, 1);
        memcardFinalizeTask();
        if (result == 4) {
            saved = 1;
        }
    }
    if (!prepared || !saved) {
        memcpy(savedataGetStatus(0, 0), m_saveBuf, 0x27FD0);
        GSsndPlayNow(0x13);
        winMsgOpen(2, 0xC49E, 1, 0);
        winMsgClose(1);
        releaseModels();
        setState(3);
    } else {
        u32 lo = HSD_Rand();
        u32 hi = HSD_Rand();
        u32 frames = ((hi << 16) | lo) % 60;
        while (frames-- != 0) {
            GSthreadSwitch();
        }
        winMsgOpen(2, 0xC4A0, 1, 0);
        winMsgClose(1);
        setState(0x17);
    }
}

}

namespace {

u8 CMenuPokemonChange::gbaConnectionCheckIsError()
{
    if (!gbaCommandIsConnected(2)) {
        menuSetEnablePort(1);
        GSsndPlayNow(0x13);
        winMsgOpen(2, 0xC4A3, 1, 0);
        setState(2);
        return 1;
    }
    return 0;
}

}

namespace {

void CMenuPokemonChange::stateFunctionCheckNext()
{
    winMsgOpen(2, 0xC4A1, 0, 0);
    s8 result = menuSubOpenYesNo(0, -1, -1, 0);
    winMsgClose(1);
    _menuWait(0.5f);
    bgDrawFadeOut();
    releaseModels();
    if (result == 0) {
        setState(6);
    } else {
        setState(2);
    }
}

}

namespace {

void CMenuPokemonChange::stateFunctionError(Pokemon* pokemon, u32 msg)
{
    u32 name = (u32)pokemonBiosGetNicknamePtr(pokemon);
    msgctrlSetValue(0x32, name);
    _setInfo(msg);
    GSsndPlayNow(0x13);
    _menuWait(1.5f);
    _setInfo(0);
    if (m_state.current >= 12) {
        setState(12);
    } else {
        setState(7);
    }
}

}

namespace {

u8 CMenuPokemonChange::isPokemonLookAbleStatus(s32 index)
{
    Pokemon* pokemon = getPokemonByIndex(index);
    enumPlayerIndex player = (index >= getQuantityHeroPokemon(PLAYER_1)) ? PLAYER_2 : PLAYER_1;
    s32 state = _getPokemonState(pokemon, player);
    switch (state) {
    case 1:
    case 2:
        return 0;
    }
    return 1;
}

}

namespace {

u8 CMenuPokemonChange::pokmonSelectCheck(enumPlayerIndex player)
{
    Pokemon* pokemon = getSelPokemon(player);
    if (isPokemonLookAbleStatus(m_sel[player])) {
        return 1;
    }
    switch (_getPokemonState(pokemon, player)) {
    case 2:
        stateFunctionError(pokemon, 0xC492);
        break;
    case 1:
        stateFunctionError(pokemon, 0xC493);
        break;
    }
    return 0;
}

}

namespace {

u8 CMenuPokemonChange::pokemonExchangeCheck(enumPlayerIndex player)
{
    Pokemon* pokemon = getPokemonByIndex(m_sel[player]);
    switch (_getPokemonState(pokemon, player)) {
    case 0:
    case 1:
    case 2:
    case 7:
        break;
    case 3:
        stateFunctionError(pokemon, 0xC497);
        return 0;
    case 4:
        stateFunctionError(pokemon, 0xC496);
        return 0;
    case 5:
    case 6:
        stateFunctionError(pokemon, 0xC4AB);
        return 0;
    }
    Hero* hero = (player == 0) ? m_hero0 : (Hero*)m_hero1;
    s32 index = m_sel[player];
    if (index >= getQuantityHeroPokemon(PLAYER_1)) {
        index -= getQuantityHeroPokemon(PLAYER_1);
    }
    if (_getQuantityBattleAbleWoIt(hero, index, player) == 0) {
        stateFunctionError(pokemon, 0xC498);
        return 0;
    }
    return 1;
}

}

namespace {

u8 _isTemochiPokemonCheck()
{
    Hero* hero = Hero::getHeroPtr();
    s32 i = 0;
    s32 exchangeable = 0;
    s32 counts[8];
    memset(counts, 0, 0x20);
    do {
        Pokemon* p = hero->getPokemon(i);
        if (_isPokemonExchangeAble(p, PLAYER_1)) {
            exchangeable++;
        }
        counts[_getPokemonState(p, PLAYER_1)]++;
        if (!_isPokemonValid(p, PLAYER_1)) {
            break;
        }
        i++;
    } while (i < 6);
    if (i <= 1) {
        GSsndPlayNow(0x13);
        winMsgOpenWithSE(3, 0xC482, 1, 0, 2);
        winMsgClose(1);
        return 0;
    }
    if (exchangeable == 0) {
        s32 msg = 0xC4A5;
        if (counts[3]) {
            msg = 0xC483;
        } else if (counts[4]) {
            msg = 0xC484;
        } else if (counts[2] || counts[1]) {
            msg = 0xC4A7;
        } else if (counts[5] || counts[6]) {
            msg = 0xC4AA;
        }
        GSsndPlayNow(0x13);
        winMsgOpenWithSE(3, msg, 1, 0, 2);
        winMsgClose(1);
        return 0;
    }
    return 1;
}

}

extern "C" {
void menuPokemonChange()
{
    s32 group;
    if (_isTemochiPokemonCheck()) {
        group = GSfloorGetCurrentFloorGroupID();
        winMsgOpenWithSE(3, 0xC48E, 1, 0, 2);
        if (menuSubOpenYesNoField() == 0) {
            s32 nextFloor = floorGetNextFloorID();
            gamedatasaveSetStatus(0, 5, nextFloor);
            s32 result = memcardTaskCall(4, 2, 0);
            winMsgClose(1);
            if (result == 4) {
                GSfloorPush(0x394);
                floorWaitForChange();
            }
            return;
        }
    }
    winMsgClose(1);
    GSthreadUnblockGroup(group);
}
}

extern "C" {
void menuPokemonChangeInit()
{
    floorMapSetDisp(0);
    scriptModelStopMotion(0xFCC1000);
}
}

extern "C" {
void menuPokemonChangeMain()
{
    MenuPokemonChange.main();
}
}

extern "C" {
void menuPokemonChangeExit()
{
}
}

extern "C" {
void menuPokemonChangeDraw(tagWINDOW_WORK* window)
{
    MenuPokemonChange.selectDrawHook(window);
}
}

extern "C" {
void menuPokemonChangeItemHook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    MenuPokemonChange.selectItemHook(window, sprite);
}
}

extern "C" {
s32 menuPokemonChangeCtrl(tagWINDOW_WORK* window)
{
    MenuPokemonChange.ctrlHook(window);
    return 0;
}
}

extern "C" {
void menuPokemonChangeCursor(tagWINDOW_WORK* window)
{
    if (!winSeqCheckMove(window->menuId)) {
        u16 on1 = winSysWork.key.on;
        u16 on2 = winSysWork2.key.on;
        u16 both = on1 | on2;
        if ((both & 0xC) != 0 && (both & 3) != 0) {
            u16 rep1 = winSysWork.key.rep;
            u16 rep2 = winSysWork2.key.rep;
            winSysWork.key.on = on1 & 0xC;
            winSysWork.key.rep = rep1 & 0xC;
            winSysWork2.key.on = on2 & 0xC;
            winSysWork2.key.rep = rep2 & 0xC;
            menuCursorNormal(window, 1);
            winSysWork.key.on = on1 & 3;
            winSysWork.key.rep = rep1 & 3;
            winSysWork2.key.on = on2 & 3;
            winSysWork2.key.rep = rep2 & 3;
            menuCursorNormal(window, 1);
            winSysWork.key.on = on1;
            winSysWork.key.rep = rep1;
            winSysWork2.key.on = on2;
            winSysWork2.key.rep = rep2;
        } else {
            menuCursorNormal(window, 1);
        }
    }
}
}

extern "C" {
u8 fn_80098B44(u8 sex, Pokemon* pokemon)
{
    u16 ch;
    u16* name = (u16*)pokemonGetStatus(pokemon, 0, 0x77, 0);
    u32 len = GSmsgGetCharLength(name);
    u16 same;
    u16 other;
    other = 0;
    same = 0;
    u16 c1;
    u16 c2;
    switch (sex) {
    case 0:
        c1 = 0x2642;
        c2 = 0x2640;
        break;
    case 1:
        c1 = 0x2640;
        c2 = 0x2642;
        break;
    default:
        return sex;
    }
    for (u32 i = 0; i < len; i++) {
        ch = name[i];
        if (c1 == ch) {
            same++;
        }
        if (c2 == ch) {
            other++;
        }
    }
    if (other == 0 && same != 0) {
        return 2;
    }
    return sex;
}
}

