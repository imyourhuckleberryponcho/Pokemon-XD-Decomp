#include <dolphin/types.h>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

// Debug menu units were built without the peephole optimizer.
#pragma peephole off
// Nothing references these debug menu entries directly; keep the linker from stripping them.
#pragma force_active on

// This unit needs "-inline noauto" (extra_cflags in configure.py).

struct Pokemon {
    u8 unk0[0xC4];
};

struct DbgWorldMapData {
    u16 index;
    s16 unk2;
    u16 count;
};

struct DbgWindow {
    u8 unk0[4];
    s32 menuID;
    u8 unk8[0x60];
    void* data;
    u8 unk6C[0x32];
    s16 cursor;
};

struct DbgKeyInfo {
    u16 unk0;
    u8 unk2[4];
    u16 repeat;
};

struct WorldMapXDData {
    u8 unk0[4];
    u32 flag;
    u8 unk8[0x1C];
};

struct DbgTableEntry {
    s32 id;
    s32 value;
};

extern "C" {

s32 GSflagGet(s32);
void GSflagOff(s32);
void GSflagOn(s32);
void GSflagSet(s32, s32);
u8 GSflagTest(s32);
s32 GSfloorGetCurrentFloorGroupID(void);
void GSfloorPush(s32);
void* GSthreadCreate(s32, s32, s32, s32, s32, void (*)(void));
void GSthreadSetArgs(void*, s32, ...);
void d2presentOpen(void);
void darkPokemonBiosSetFightFlag(u16, s32);
DarkPokemon* darkPokemonGetDarkPokemon(u32);
u16 darkpokemonBiosGetScenarioNum(void);
void esabaGet(s32);
s32 esabaGetPokemonMax(u16);
void esabaPut(s32);
void esabaSet(s32);
void esabaSetPokemon(u16, u16);
void esabaSetPokemonRnd(s32, s32);
void evolutionOpen(void*, void*, s32, u16*, s32, u8*);
void fadeCheck(s32);
void fadeSet(s32, f32);
s32 gamedataGetStatus(s32, s32);
void* heroBiosGetPokemonPtr(void*, s32);
void heroCatchPokemon(s32, void*, s32, s32, s32);
void* heroGetStatus(s32, s32, s32);
void makePocketDeubugMakeDarkPokemonReset__Fv(void);
s32 memoDataGetPokemonRndFromID(s32, u16);
s32 memoDataGetPokemonTrainerRndFromID(s32, u16);
void memoDataSetMemoFlag(s32);
void memoDataSetPokemonID(s32, u16);
void memoInitDebug(s32);
void menuBattleDiskOpen(void);
void menuBattleDiskOpenFight(void);
void menuClose(s32);
void menuCloseSync(s32, s32);
void menuIntUnderTakerOpenIcon(void);
u8 menuIsCheck(s32);
void menuMoveDemo(s32);
void menuNameEntryOpen(s32, s32);
void menuNintendoWarning(void);
s32 menuOpenCustom(s32, ...);
void menuOrreColosseum(u16);
void menuOrreColosseumGetResult(void);
void menuPokemonChange(void);
void menuPokemonOpen(s32, s32, s32);
void menuPokemonStatusOpenWazaLearn(void*, s32);
void menuScriptEevee(void);
void menuScriptInfoEsa(void);
void menuScriptInfoRelive(s32, s32);
void menuScriptOpenWorldMap(u16);
void menuScriptPdaAddFunc(u32);
void menuScriptReadMail(u32);
void menuScriptReciveMail(void);
void menuScriptTutorial(void);
void menuScriptUsohachi(void);
void menuScriptUsohachi2(void);
void menuScriptWazaBasan(void*);
void menuScriptWazaMeijin(s32);
void menuShopOpen(s32);
void menuSubCloseNumberInput(void);
void menuSubCloseNumberInputWait(void);
u8 menuSubOpenNumberInput(s32, u32*, s32, s32, s32, s32);
s32 menuSubOpenSelect2(s32, void*, s32, s32, s32, s32, s32, s32);
void menuWorldMapMXDebug(void);
void mewWazaSequence(void);
void msgctrlSetValue(s32, s32);
void pcboxDebugPokemonSetup(void);
void pcboxDebugPokemonSetupFull(void);
void pokemonBiosSetCatchTrainerRnd(void*, s32);
void pokemonBiosSetRnd(void*, s32);
u8 pokemonCheckValid(void*);
void pokemonCreate(void*, u16, s32, s32);
s32 pokemonCreateRndFit(void*, s32, s32, s32, s32);
void pokemonSetDarkPokemonStatus(void*, u16);
void reliveHallDebugPokemonSetup(s32);
void* savedataGetStatus(s32, s32);
u32 undertakerGetPlace(u32*);
s32 undertakerGetStartFlagID(void);
void undertakerSetPlace(s32);
s32 windowGetActiveID(void);
DbgKeyInfo* windowGetKeyInfo(void);

extern WorldMapXDData* worldmapXD_data;
extern s32* worldmapXD_data_number;

}

static void _esabaSetPokemon(s32, s32);
static void _pokemonCreate(Pokemon*, u16, u32);
static void _dbgMenuMenuTestPdaFlagSet(u32);
static s32 _getDPStatus(s32);
static void _setDPStatus(s32, darkPokemonStatus);
static u16 _getDPPokemonID(s32);
static void _debugPokemonCreate(Pokemon*, u16);
static void testEvolution(void);
static s32 _getWorldMapFlagData(s32);
static void _setWorldMapFlagData(s32, s32);

// Data (order matters for the link).
u16 _testEncount[0x1C] = {0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64,
                          0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72};
static u32 _undertakerFloorID[8];
static DbgWorldMapData _debugWorldMapData;
static u32 _undertakerFloorCount;
static s32 _esabaPlace;
static u16 _esabaSelectPokemon;
// (The retail .sbss/.sdata2 end in a few bytes of alignment padding; the linker adds it.)

enum D2PRESENT_MODE { D2PRESENT_0, D2PRESENT_1, D2PRESENT_2 };
static void testD2Present(D2PRESENT_MODE);

extern "C" {

s32 dbgMenuMenuTestNameEntryMenu(s32 item) {
    DbgTableEntry table[4] = {{0x1C4, 0}, {0x1C5, 1}, {0x1C6, 2}, {0x1C7, 3}};
    s32 i;

    for (i = 0; i < 4; i++) {
        if (item == table[i].id) {
            break;
        }
    }
    if (i >= 4) {
        return 0;
    }
    menuNameEntryOpen(table[i].value, 0);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestShopMenu(s32 item) {
    DbgTableEntry table[13] = {{0x1C8, 0},  {0x1C9, 0x10}, {0x1CA, 1}, {0x1CB, 2}, {0x1CC, 3},
                               {0x1CD, 4},  {0x1CE, 5},    {0x1CF, 6}, {0x1D0, 7}, {0x1D1, 8},
                               {0x1D2, 9},  {0x1D3, 10},   {0x1D4, 11}};
    s32 i;

    for (i = 0; i < 13; i++) {
        if (item == table[i].id) {
            break;
        }
    }
    if (i >= 13) {
        return 0;
    }
    menuShopOpen(table[i].value);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestPokemonMenu(s32 item) {
    switch (item) {
    case 0x1D5:
        menuPokemonOpen(1, 0, 0);
        break;
    case 0x1D6:
        menuPokemonOpen(2, 0, 0);
        break;
    default:
        menuPokemonOpen(2, 0, 0);
        break;
    }
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestBattleDisk(void) {
    menuBattleDiskOpen();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestBattleDiskExec(void) {
    menuBattleDiskOpenFight();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestBingo(void) {
    GSfloorPush(0x388);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestBingoSelect(void) {
    s32* flags = (s32*)savedataGetStatus(0, 0x1B);
    *flags = *flags | 0x2AAAAA;
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestBingoClear(void) {
    s32* flags = (s32*)savedataGetStatus(0, 0x1B);
    *flags = *flags | 0x3FFFFF;
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestReliveHallMenu(void) {
    GSfloorPush(0x3A3);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestHologramMenu(void) {
    GSfloorPush(0x3A6);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestReliveHallPokemonSet0(void) {
    makePocketDeubugMakeDarkPokemonReset__Fv();
    pcboxDebugPokemonSetup();
    reliveHallDebugPokemonSetup(1);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestReliveHallPokemonSet1(void) {
    makePocketDeubugMakeDarkPokemonReset__Fv();
    pcboxDebugPokemonSetup();
    reliveHallDebugPokemonSetup(0);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestReliveHallPokemonSetBest(void) {
    makePocketDeubugMakeDarkPokemonReset__Fv();
    pcboxDebugPokemonSetup();
    reliveHallDebugPokemonSetup(2);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestPcBoxPokemonSetFull(void) {
    makePocketDeubugMakeDarkPokemonReset__Fv();
    pcboxDebugPokemonSetupFull();
    reliveHallDebugPokemonSetup(2);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestRelivehallTutorialMenu(void) {
    msgctrlSetValue(0x59, 0x1772);
    GSfloorPush(0x3A7);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestPCBox(void) {
    GSfloorPush(0x391);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestPokemonChangeMenu(void) {
    msgctrlSetValue(0x59, 0x1772);
    menuPokemonChange();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestWazaMenu(void) {
    void* savedata;
    void* pokemon;

    savedata = savedataGetStatus(0, 2);
    if (savedata == 0) {
        return 0;
    }
    pokemon = heroBiosGetPokemonPtr(savedata, 0);
    if (pokemonCheckValid(pokemon) == 0) {
        return 0;
    }
    menuPokemonStatusOpenWazaLearn(pokemon, 0x25);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestEvolution(void) {
    GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (void (*)(void))testEvolution);
    return 0;
}

}

static void testEvolution(void) {
    void* first;
    void* second;
    u16 shownMoves[20];
    u8 selected[20];

    first = heroGetStatus(0, 3, 0);
    if (pokemonCheckValid(first) != 0) {
        second = heroGetStatus(0, 3, 1);
        if (pokemonCheckValid(second) != 0) {
            fadeSet(3, 0.5f);
            fadeCheck(1);
            shownMoves[0] = 1;
            shownMoves[1] = 2;
            evolutionOpen(first, second, 1, shownMoves, 2, selected);
            fadeSet(2, 0.5f);
            fadeCheck(1);
        }
    }
}

extern "C" {

s32 dbgMenuMenuTestEnableMemo(void) {
    return 1;
}

}

extern "C" {

s32 dbgMenuMenuTestAddPokemonMemo(void) {
    s32 value;

    value = 0;
    for (;;) {
        if (menuSubOpenNumberInput(value, (u32*)&value, 1, 0x32, 0x32, 0) == 0) {
            break;
        }
        memoDataSetPokemonID(0, value);
    }
    menuSubCloseNumberInput();
    return 1;
}

}

extern "C" {

s32 dbgMenuMenuTestCompleteMemo(void) {
    memoInitDebug(0);
    return 1;
}

}

extern "C" {

s32 dbgMenuMenuTestTeacherMemo(void) {
    memoDataSetMemoFlag(0);
    return 1;
}

}

static s32 _getDPStatus(s32 id) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon((u16)id);
    if (dark->getPokemonID() != 0) {
        return dark->getStatus();
    }
    return 0;
}

static void _setDPStatus(s32 id, darkPokemonStatus status) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon((u16)id);
    if (dark->getPokemonID() != 0) {
        dark->setStatus(status);
        dark->setUpdate(true);
    }
}

static u16 _getDPPokemonID(s32 id) {
    return darkPokemonGetDarkPokemon((u16)id)->getPokemonID();
}

extern "C" {

s32 dbgMenuEntrySnatchList(void) {
    s32 value;
    DarkPokemon* dark;

    value = 0;
    for (;;) {
        if (menuSubOpenNumberInput(value, (u32*)&value, 1, 0x32, 0x32, 0) == 0) {
            break;
        }
        dark = darkPokemonGetDarkPokemon((u16)value);
        if (dark != 0) {
            darkPokemonBiosSetFightFlag(value, 1);
            dark->setUpdate(true);
        }
    }
    menuSubCloseNumberInput();
    return 1;
}

}

extern "C" {

s32 dbgMenuEntrySnatchListAll(void) {
    s32 i;

    for (i = 0; i <= darkpokemonBiosGetScenarioNum(); i++) {
        if (_getDPStatus(i) == 0) {
            _setDPStatus(i, darkPokemonStatus1);
        }
    }
    return 1;
}

}

extern "C" {

s32 dbgMenuEntrySnatchListSuccess(void) {
    Pokemon pokemon;
    s32 i;
    u16 id;

    for (i = 0; i <= darkpokemonBiosGetScenarioNum(); i++) {
        if (_getDPStatus(i) >= 1) {
            id = _getDPPokemonID(i);
            _debugPokemonCreate(&pokemon, id);
            pokemonSetDarkPokemonStatus(&pokemon, i);
            heroCatchPokemon(0, &pokemon, 0, 4, 1);
            _setDPStatus(i, darkPokemonStatus3);
        }
    }
    return 1;
}

}

static void _debugPokemonCreate(Pokemon* pokemon, u16 id) {
    s32 rnd;
    s32 trainerRnd;

    pokemonCreate(pokemon, id, 10, gamedataGetStatus(0, 1));
    rnd = memoDataGetPokemonRndFromID(0, id);
    trainerRnd = memoDataGetPokemonTrainerRndFromID(0, id);
    pokemonBiosSetRnd(pokemon, rnd);
    pokemonBiosSetCatchTrainerRnd(pokemon, trainerRnd);
}

extern "C" {

s32 dbgMenuEntrySnatchListRelive(void) {
    s32 i;

    for (i = 0; i <= darkpokemonBiosGetScenarioNum(); i++) {
        if (_getDPStatus(i) >= 1) {
            _setDPStatus(i, darkPokemonStatusRelive);
        }
    }
    return 1;
}

}

extern "C" {

s32 dbgMenuMenuTestWorlMapSetAllFlag(void) {
    menuWorldMapMXDebug();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestD2Present(s32 mode) {
    DbgTableEntry table[3] = {{0x1DF, 0}, {0x1E0, 1}, {0x1E1, 2}};
    s32 i;
    s32 value;
    void* thread;

    for (i = 0; i < 3; i++) {
        if (mode == table[i].id) {
            break;
        }
    }
    value = table[i].value;
    thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (void (*)(void))testD2Present);
    GSthreadSetArgs(thread, 1, value);
    return 0;
}

}

static void testD2Present(D2PRESENT_MODE) {
    d2presentOpen();
}

static void _dbgMenuMenuTestPdaFlagSet(u32 flag) {
    u32 value;

    value = GSflagTest(flag);
    for (;;) {
        if (menuSubOpenNumberInput(value, &value, 1, 0x32, 0x32, 0) == 0) {
            break;
        }
        if (value != 0) {
            GSflagOn(flag);
        } else {
            GSflagOff(flag);
        }
    }
    menuSubCloseNumberInput();
}

extern "C" {

s32 dbgMenuMenuTestPdaEnable(void) {
    _dbgMenuMenuTestPdaFlagSet(0x3F1);
    return 1;
}

}

extern "C" {

s32 dbgMenuMenuTestPdaDPM(void) {
    _dbgMenuMenuTestPdaFlagSet(0x3F2);
    return 1;
}

}

extern "C" {

s32 dbgMenuMenuTestPdaEsa(void) {
    _dbgMenuMenuTestPdaFlagSet(0x3F3);
    return 1;
}

}

extern "C" {

s32 dbgMenuMenuTestPdaMR(void) {
    _dbgMenuMenuTestPdaFlagSet(0x3F4);
    return 1;
}

}

extern "C" {

s32 dbgMenuMenuTestPdaSyougou(void) {
    s32 value;

    value = GSflagGet(0x6C2);
    for (;;) {
        if (menuSubOpenNumberInput(value, (u32*)&value, 1, 0x32, 0x32, 0) == 0) {
            break;
        }
        if ((u32)value <= 7) {
            GSflagSet(0x6C2, value);
        }
    }
    menuSubCloseNumberInput();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestMailReceive(void) {
    menuScriptReciveMail();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestMailRead(void) {
    u32 value;

    value = 0;
    if (menuSubOpenNumberInput(0, &value, 1, 0x32, 0x32, 0) != 0) {
        menuSubCloseNumberInput();
        menuSubCloseNumberInputWait();
        menuScriptReadMail(value);
    }
    menuSubCloseNumberInput();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestPdaAddFunc(void) {
    u32 value;

    value = 0;
    if (menuSubOpenNumberInput(0, &value, 1, 0x32, 0x32, 0) != 0) {
        menuSubCloseNumberInput();
        menuSubCloseNumberInputWait();
        if (value > 1) {
            value = 0;
        }
        menuScriptPdaAddFunc(value);
    }
    menuSubCloseNumberInput();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestEeveeMenu(void) {
    menuScriptEevee();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestTutorialMenu(void) {
    menuScriptTutorial();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestWazaOshieMeijinMenu(s32, s32 arg) {
    menuScriptWazaMeijin(arg);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestWazaOshieBasanMenu(void) {
    s32 buffer;

    menuScriptWazaBasan(&buffer);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestOrreColosseumMenu(void) {
    u32 value;

    value = 0;
    menuSubOpenNumberInput(0, &value, 1, 0x32, 0x32, 1);
    if (value >= 0x1C) {
        value = 0;
    }
    menuOrreColosseum(_testEncount[value]);
    menuOrreColosseumGetResult();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestMewWazaMenu(void) {
    mewWazaSequence();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuMoveDemo(s32, s32 arg) {
    menuMoveDemo(arg);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuSetPlace(s32, s32 place) {
    _esabaPlace = place;
    return 1;
}

}

extern "C" {

s32 dbgMenuMenuTestEsabaSet(void) {
    esabaSet(_esabaPlace);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestEsabaPut(void) {
    esabaPut(_esabaPlace);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestEsabaGet(void) {
    esabaGet(_esabaPlace);
    return 0;
}

}

static void _esabaSetPokemon(s32, s32) {
    esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
}

static void _pokemonCreate(Pokemon* pokemon, u16 id, u32 trainerRnd) {
    s32 rnd;

    pokemonCreate(pokemon, id, 10, gamedataGetStatus(0, 1));
    rnd = memoDataGetPokemonRndFromID(0, id);
    pokemonBiosSetRnd(pokemon, rnd);
    pokemonBiosSetCatchTrainerRnd(pokemon, trainerRnd);
}

extern "C" {

u32 dbgMenuMenuTestEsabaPokemon(void) {
    s32 table[2] = {0xF86F, 0xF146};
    Pokemon pokemon;
    void* hero;
    s32 result;
    s32 answer;
    s32 rnd;

    _esabaSelectPokemon = 0;
    hero = heroGetStatus(0, 2, 0);
    result = menuOpenCustom(0x10A, windowGetActiveID(), 0, 0, 1, 0);
    if (result > 0) {
        if (_esabaSelectPokemon == 0x19D || _esabaSelectPokemon == 0x19E) {
            _esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
        } else {
            answer = menuSubOpenSelect2(0, table, 2, 0x96, 0x96, 0, 2, 1);
            switch (answer) {
            case 0:
                _esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
                _pokemonCreate(&pokemon, _esabaSelectPokemon, (u32)hero);
                rnd = pokemonCreateRndFit(&pokemon, -1, -1, 0, (s32)hero);
                esabaSetPokemonRnd(_esabaPlace, rnd);
                break;
            case 1:
                _esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
                esabaSetPokemonRnd(_esabaPlace, (s32)hero);
                break;
            }
        }
    } else if (result == 0) {
        _esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
    }
    menuClose(0x10A);
    menuCloseSync(0x10A, 1);
    return (u32)result >> 31;
}

}

extern "C" {

s32 dbgMenuMenuEsabaDisp(void) {
    if (menuIsCheck(0xB7) != 0) {
        menuClose(0xB7);
    } else {
        menuOpenCustom(0xB7, 0, 0, 0, 1, 0);
    }
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestInfoEsa(void) {
    menuScriptInfoEsa();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestInfoRelive(void) {
    menuScriptInfoRelive(0, 1);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuUnderTakerOnOff(void) {
    s32 flag = undertakerGetStartFlagID();
    if (GSflagTest(flag) != 0) {
        GSflagOff(flag);
    } else {
        GSflagOn(flag);
    }
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuUnderTakerDisp(void) {
    if (menuIsCheck(0xC0) != 0) {
        menuClose(0xC0);
    } else {
        menuOpenCustom(0xC0, 0, 0, 0, 1, 0);
    }
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuUnderTakerIconOnOff(void) {
    menuIntUnderTakerOpenIcon();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuUnderTakerIconFlagOnOff(void) {
    if (GSflagTest(0x5AD) != 0) {
        GSflagOff(0x5AD);
    } else {
        GSflagOn(0x5AD);
    }
    return 0;
}

}

extern "C" {

u32 dbgMenuMenuUnderTakerIconAppear(void) {
    s32 result = menuOpenCustom(0x111, windowGetActiveID(), 0, 0, 1, 0);
    if (result >= 0 && _undertakerFloorID[result] != 0) {
        undertakerSetPlace(_undertakerFloorID[result]);
    }
    menuClose(0x111);
    menuCloseSync(0x111, 1);
    return (u32)result >> 31;
}

}

extern "C" {

s32 dbgMenuMenuTestNintendoWarning(void) {
    menuNintendoWarning();
    return 0;
}

}

extern "C" {

s32 dbgMenuUnderTakerebugCursor(DbgWindow* window) {
    DbgKeyInfo* key = windowGetKeyInfo();

    _undertakerFloorCount = undertakerGetPlace(_undertakerFloorID);
    if (_undertakerFloorCount != 0) {
        if (key->repeat & 5) {
            if (--window->cursor < 0) {
                window->cursor = 0;
            }
        } else if (key->repeat & 0xA) {
            if ((u32)++window->cursor >= _undertakerFloorCount) {
                window->cursor = _undertakerFloorCount - 1;
            }
        }
    }
    return 0;
}

}

extern "C" {

s32 dbgMenuEsabaDebugCursor(DbgWindow* window) {
    DbgKeyInfo* key = windowGetKeyInfo();
    s32 max = esabaGetPokemonMax(_esabaPlace);
    u16 limit;

    if (key->repeat & 5) {
        if (--window->cursor < 0) {
            window->cursor = 0;
        }
    } else if (key->repeat & 0xA) {
        limit = max + 3;
        if (++window->cursor >= limit) {
            window->cursor = limit - 1;
        }
    }
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestWorlMapFlagSet(void) {
    _debugWorldMapData.index = 0;
    _debugWorldMapData.unk2 = 0;
    _debugWorldMapData.count = *worldmapXD_data_number;
    while (menuOpenCustom(0xC4, windowGetActiveID(), 0, 0, 1, 1, &_debugWorldMapData) != -1) {
    }
    menuClose(0xC4);
    menuCloseSync(0xC4, 1);
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuWorldMapCursor(DbgWindow* window) {
    DbgKeyInfo* key;
    DbgWorldMapData* data;
    s32 flag;

    key = windowGetKeyInfo();
    data = (DbgWorldMapData*)window->data;

    if (window->menuID != 0xD7) {
        if (key->repeat & 1) {
            if (--window->cursor < 0) {
                window->cursor = 0;
            }
        } else if (key->repeat & 2) {
            if (++window->cursor > 1) {
                window->cursor = 1;
            }
        }
    }
    switch (window->cursor) {
    case 0:
        if (key->repeat & 8) {
            if (data->index < (u16)(data->count - 1)) {
                data->index++;
            }
        } else if (key->repeat & 4) {
            if (data->index != 0) {
                data->index--;
            }
        }
        break;
    case 1:
        flag = _getWorldMapFlagData(data->index);
        if (flag >= 0) {
            if (key->repeat & 8) {
                if (flag < 2) {
                    flag++;
                }
            } else if (key->repeat & 4) {
                if (flag != 0) {
                    flag--;
                }
            }
            _setWorldMapFlagData(data->index, flag);
        }
        break;
    }
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestWorlMapShow(void) {
    s32 result;

    _debugWorldMapData.index = 0;
    _debugWorldMapData.unk2 = 0;
    _debugWorldMapData.count = *worldmapXD_data_number;
    result = menuOpenCustom(0xD7, windowGetActiveID(), 0, 0, 1, 1, &_debugWorldMapData);
    menuClose(0xD7);
    menuCloseSync(0xD7, 1);
    if (result >= 0) {
        menuScriptOpenWorldMap(_debugWorldMapData.index);
    }
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestUsohachi(void) {
    menuScriptUsohachi();
    return 0;
}

}

extern "C" {

s32 dbgMenuMenuTestUsohachi2(void) {
    menuScriptUsohachi2();
    return 0;
}

}

static void _setWorldMapFlagData(s32 index, s32 value) {
    if (worldmapXD_data[index].flag != 0) {
        GSflagSet(worldmapXD_data[index].flag, value);
    }
}

static s32 _getWorldMapFlagData(s32 index) {
    if (worldmapXD_data[index].flag == 0) {
        return -1;
    }
    return GSflagGet(worldmapXD_data[index].flag);
}

extern "C" {

s32 dbgMenuMenuReliveHallDisp(void) {
    if (menuIsCheck(0x108) != 0) {
        menuClose(0x108);
    } else {
        menuOpenCustom(0x108, 0, 0, 0, 1, 0);
    }
    return 0;
}

}
