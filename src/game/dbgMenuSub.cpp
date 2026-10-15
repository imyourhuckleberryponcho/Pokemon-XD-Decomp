#include <dolphin/types.h>

// Debug menu units were built without the peephole optimizer.
#pragma peephole off
#pragma pool_strings off

struct Pokemon {
    u8 unk0[0xC4];
};

class Hero {
public:
    static Hero* getHeroPtr();
    void setHeroStyle(u8 style, bool flag);
};

struct GSgfxFilter {
    u8 v[7];
};

extern "C" {

s32 pokecoloGetRomVersion(void);
bool floorSound_getDispSoundVolume(void);
void floorSound_setDispSoundVolume(bool);
void GSresDumpAll(void);
void* savedataGetStatus(s32, s32);
s32 gamedataGetStatus(s32, s32);
void pokemonCreate(Pokemon*, u16, u8, s32);
void heroCatchPokemon(void* hero, Pokemon*, s32, s32, s32);
void memoDataSet(s32, Pokemon*);
void pokemonSetDarkPokemonStatus(Pokemon*, u16);
s32 heroItemAddItemDataId(void* hero, u16 item, u16 num, s32 slot);
void GSflagOff(u32 id);
extern u32* flag_data_number;
void heroSetFollowerWithID(u8, u8);
bool lightIsDebugMode(void);
void lightSetDebugMode(bool);
bool floorGetHumanColision(void);
void floorSetHumanColision(bool);
u32 soundGetBGMID(void);
u32 soundGetEnvID(void);
void soundStop(u32, s32);
void soundOpenPlay(u32, s32, s32);
bool menuSubOpenNumberInputDigit(s32, s32* value);
u8 menuSubOpenNumberInputID(u32, u32*, void* (*)(u32));
void menuSubCloseNumberInput(void);
s8 menuSubOpenYesNoField(void);
void winMsgOpenField(s32 msgID, s32, s32);
void winMsgClose(s32);
bool floorIsDispScriptInfo(void);
void floorSetDispScriptInfo(bool);
void menuOpenCustom(s32 menuID, ...);
bool menuIsCheck(s32 menuID);
void menuClose(s32 menuID);
s32 menuOpen(s32, s32);
void GSmovieStop(u32 movie);
bool GSmoviePlayCheck(u32 movie);
void GSmoviePlay(u32 movie, s32, s32 loop, void* tex);
void GSthreadSwitch(void);
u32 GSfloorGetCurrent(void);
void* floorGetActiveOffscreenTexture(void);
void GSdvdFstRefresh(void);
void GScharMakeFromSJIS(s16* dst, const char* src);
void GSgfxVideoSetMode(s32, s32, s32, s32, s32);
void GSgfxVideoSetFilter(GSgfxFilter);
bool GSgfxVideoGetLockFrameActive(void);
void GSgfxVideoSetLockFrameActive(bool);
void GSgfxVideoSetLockFrameRate(s32);
void GSmemDumpHeapInfo(void);
void GSmemDumpHeap(s32);
void GSmemDumpPool(s32);
bool GSmemCheckHeap(s32);
extern s32 g_hFloorHeap;
s32 floorGetLocalHeapHandle(void);
void GSlogWrite(const char*, ...);
void mailMainSendAllMail(void);
s32 mailChkReceiveMail(s32);
s32 mailAddMailbox(s32);
void mailMainReceiveStart(void);
void* GSresGetResource(u32, u32);
extern u8 __pokecolo_renderXluc;
void GSmodelSetShadowDebug(bool);
s32 GSgfxPerfbarGetRenderMode(void);
void GSgfxPerfbarSetRenderMode(s32);

}

static u32 _dbgMenuDispAMemInfoFlag;
struct MovieWH { u16 h; u16 w; };

extern "C" {

s32 debugMenuChangePerfBar(void) {
    s32 mode = GSgfxPerfbarGetRenderMode();
    switch (mode) {
    case 0:
        mode = 2;
        break;
    case 2:
        mode = 1;
        break;
    case 1:
        mode = 0;
        break;
    }
    GSgfxPerfbarSetRenderMode(mode);
    return 0;
}

s32 debugMenuChangeMemInfo(void) {
    if (menuIsCheck(4)) {
        menuClose(4);
    } else {
        menuOpenCustom(4, 0, 0, 0, 0, 0);
    }
    return 0;
}

s32 debugMenuNodrawArea(void) {
    if (menuIsCheck(7)) {
        menuClose(7);
    } else {
        menuOpenCustom(7, 0, 0, 0, 0, 0);
    }
    return 0;
}

s32 debugMenuShadowBorderDisp(void) {
    static bool borderDisp = false;
    borderDisp = !borderDisp;
    GSmodelSetShadowDebug(borderDisp);
    return 0;
}

s32 debugMenuColorBarDisp(void) {
    __pokecolo_renderXluc = 0;
    menuOpenCustom(5, 0, 0, 0, 1, 0);
    menuClose(5);
    __pokecolo_renderXluc = 1;
    return 0;
}

s32 dbgMenuColisionDisp(s32 id) {
    u8* res = (u8*)GSresGetResource(0, 2);
    if (res == 0) {
        return 0;
    }
    switch (id) {
    case 0x131:
        if (res[0] != 0) {
            res[0] = 0;
        } else {
            res[0] = 1;
        }
        break;
    case 0x132:
        if (res[1] != 0) {
            res[1] = 0;
        } else {
            res[1] = 1;
        }
        break;
    }
    return 0;
}

s32 dbgMenuSendMail(void) {
    s32 mail;
    while ((mail = menuOpen(2, 1)) != -1) {
        if (mailChkReceiveMail(mail) == 0) {
            if (mailAddMailbox(mail) != 0) {
                mailMainReceiveStart();
            }
        }
    }
    return 0;
}

s32 dbgMenuSendAllMail(void) {
    mailMainSendAllMail();
    return 0;
}

s32 dbgMenuFrameRate60(void) {
    GSgfxVideoSetLockFrameRate(0);
    return 0;
}

s32 dbgMenuFrameRate30(void) {
    GSgfxVideoSetLockFrameRate(1);
    return 0;
}

s32 dbgMenuFrameRate20(void) {
    GSgfxVideoSetLockFrameRate(2);
    return 0;
}

s32 dbgMenuFrameRate15(void) {
    GSgfxVideoSetLockFrameRate(3);
    return 0;
}

s32 dbgMenuFrameLockToggle(void) {
    GSgfxVideoSetLockFrameActive(!GSgfxVideoGetLockFrameActive());
    return 0;
}

s32 dbgMenuScreenFilterOff(void) {
    GSgfxFilter f = {{0x00, 0x00, 0x15, 0x16, 0x15, 0x00, 0x00}};
    GSgfxVideoSetFilter(f);
    return 0;
}

s32 dbgMenuScreenFilterDefault(void) {
    GSgfxFilter f = {{0x08, 0x08, 0x0A, 0x0C, 0x0A, 0x08, 0x08}};
    GSgfxVideoSetFilter(f);
    return 0;
}

s32 dbgMenuScreenFilterLow(void) {
    GSgfxFilter f = {{0x04, 0x06, 0x0E, 0x10, 0x0E, 0x06, 0x04}};
    GSgfxVideoSetFilter(f);
    return 0;
}

s32 dbgMenuScreenFilterMed(void) {
    GSgfxFilter f = {{0x09, 0x09, 0x09, 0x0A, 0x09, 0x09, 0x09}};
    GSgfxVideoSetFilter(f);
    return 0;
}

s32 dbgMenuScreenFilterHi(void) {
    GSgfxFilter f = {{0x0D, 0x09, 0x07, 0x06, 0x07, 0x09, 0x0D}};
    GSgfxVideoSetFilter(f);
    return 0;
}

// The original linked these debug display routines but nothing references them anymore;
// only their strings survive in .rodata. Keep them (dead-stripped by the linker) for layout.
static void dbgMenuDeadMemDisp(void) {
    GSlogWrite("CacheMemory : %.2fkb / %.2fkb");
    GSlogWrite("  - Largest : %.2fkb");
    GSlogWrite("  - KeepCache : %.2fkb");
    GSlogWrite("CacheManage : %d / %d");
    GSlogWrite("ARQManage   : %d / %d");
    GSlogWrite("LocalMemory : %.2fkb / %.2fkb");
    GSlogWrite("Streaming BGM Playing...");
    GSlogWrite("fight/field:%s/%s");
    GSlogWrite("resCount:%d/%d");
    GSlogWrite("fsysfree: %.2fKb");
    GSlogWrite("fsyslarge: %.2fKb");
    GSlogWrite("totalmin: %.2fKb");
    GSlogWrite("memlarge: %.2fKb");
    GSlogWrite("memtotal: %.2fKb");
}

static inline const char* chk(bool b) { return b ? "ok" : "error"; }

s32 dbgMenuGSmemCheck(void) {
    GSlogWrite("check fsys heap\n");
    GSlogWrite("%s\n", chk(GSmemCheckHeap(0)));
    GSlogWrite("check floor heap\n");
    GSlogWrite("%s\n", chk(GSmemCheckHeap(floorGetLocalHeapHandle())));
    GSlogWrite("check system heap\n");
    GSlogWrite("%s\n", chk(GSmemCheckHeap(g_hFloorHeap)));
    return 0;
}

s32 dbgMenuGSmemDispMap(void) {
    GSmemDumpHeapInfo();
    GSmemDumpHeap(g_hFloorHeap);
    GSmemDumpHeap(0);
    GSmemDumpPool(0);
    return 0;
}

s32 dbgMenuGSmemOptimize(void) { return 0; }

s32 dbgMenuSetPAL50(void) {
    GSgfxVideoSetMode(1, 1, 0, 1, 0);
    return 0;
}

s32 dbgMenuSetPAL60(void) {
    GSgfxVideoSetMode(2, 1, 0, 1, 0);
    return 0;
}

}

static void* _dbgMenuMovieTestGetStr(u32 index) {
    static const char* _test_movie_str[16] = {
        "tv_news_common", "tv_news_ren", "tv_music_chiril", "tv_deathgold_appear",
        "tv_agent_report", "tv_cyobin_comments", "tv_battle_demo", "tv_colosseum_demo",
        "tv_colosseum_demo_lugia", "tpc_logo", "gs_logo", "auto_demo",
        "ending", "staffroll", "relive_complete", "event_battle_192x144",
    };
    static char strbuf[64];
    if (index >= 16) {
        index = 15;
    }
    GScharMakeFromSJIS((s16*)strbuf, _test_movie_str[index]);
    return strbuf;
}

extern "C" {

s32 dbgMenuMovieTest(void) {
    static u32 _test_movie[16] = {
        0x8ED, 0x8EE, 0x8EF, 0x8F0, 0x8F1, 0x8F2, 0x8F3, 0x9F4,
        0xA17, 0x7D9, 0x7DA, 0x7DC, 0x8EB, 0x7DD, 0x8EC, 0x814,
    };
    static MovieWH _test_movie_wh[16] = {
        {0xC0, 0x90}, {0xC0, 0x90}, {0xC0, 0x90}, {0xC0, 0x90}, {0xC0, 0x90}, {0xC0, 0x90}, {0xC0, 0x90}, {0xC0, 0x90},
        {0xC0, 0x90}, {0x280, 0x1E0}, {0x280, 0x1E0}, {0x280, 0x1E0}, {0x280, 0x1E0}, {0x280, 0x1E0}, {0x280, 0x1E0}, {0xC0, 0x90},
    };
    static s32 _test_movie_index = 0;
    s32 index;
    void* tex;
    u32 i = 0;
    do {
        while (GSmoviePlayCheck(_test_movie[i]) == true) {
            GSmovieStop(_test_movie[i]);
            GSthreadSwitch();
        }
        i++;
    } while (i < 16);
    if (!menuSubOpenNumberInputID(_test_movie_index, (u32*)&index, _dbgMenuMovieTestGetStr)) {
        return 0;
    }
    if ((u32)index >= 16) {
        index = 15;
    }
    menuSubCloseNumberInput();
    if (GSfloorGetCurrent() == 0x196 && _test_movie_wh[index].h == 0xC0 && _test_movie_wh[index].w == 0x90) {
        tex = floorGetActiveOffscreenTexture();
    } else {
        tex = 0;
    }
    GSdvdFstRefresh();
    GSmoviePlay(_test_movie[index], 0, 1, tex);
    _test_movie_index = index;
    return 0;
}

s32 debugMenuChangeAMemInfo(void) {
    static s32 _disp = 0;
    switch (_disp) {
    case 0:
    case 1:
        _dbgMenuDispAMemInfoFlag = _disp;
        menuOpenCustom(0x21, 0, 0, 0, 0, 0);
        _disp++;
        break;
    default:
        if (menuIsCheck(0x21)) {
            menuClose(0x21);
        }
        _disp = 0;
        break;
    }
    return 0;
}

s32 dbgMenuScriptDispLine(void) {
    if (floorIsDispScriptInfo() == true) {
        floorSetDispScriptInfo(false);
    } else {
        floorSetDispScriptInfo(true);
    }
    return 0;
}

s32 dbgMenuScriptMsgTest(void) {
    static s32 msg_id = 0;
    while (menuSubOpenNumberInputDigit(msg_id, &msg_id) == true) {
        winMsgOpenField(msg_id, 1, 0);
        winMsgClose(1);
    }
    return 0;
}

s32 dbgMenuScriptYesNoMsgTest(void) {
    static s32 msg_id = 0;
    while (menuSubOpenNumberInputDigit(msg_id, &msg_id) == true) {
        winMsgOpenField(msg_id, 1, 0);
        menuSubOpenYesNoField();
        winMsgClose(1);
    }
    return 0;
}

s32 dbgMenuScriptSoundTest(void) {
    static u32 snd_id = 0;
    while (menuSubOpenNumberInputDigit(snd_id, (s32*)&snd_id) == true) {
        if (snd_id == soundGetBGMID() || snd_id == soundGetEnvID()) {
            soundStop(snd_id, 1000);
        } else {
            soundOpenPlay(snd_id, 0, 127);
        }
    }
    return 0;
}

s32 dbgMenuScriptHumanColision(void) {
    if (floorGetHumanColision() == true) {
        floorSetHumanColision(false);
    } else {
        floorSetHumanColision(true);
    }
    return 0;
}

s32 dbgMenuScriptLightEdt(void) {
    if (lightIsDebugMode() == true) {
        lightSetDebugMode(false);
    } else {
        lightSetDebugMode(true);
    }
    return 0;
}

s32 dbgMenuPTout(void) {
    heroSetFollowerWithID(0, 0);
    return 0;
}

s32 dbgMenuManaPTin(void) {
    heroSetFollowerWithID(1, 0);
    return 0;
}

s32 dbgMenuGirlPTin(void) {
    heroSetFollowerWithID(2, 0);
    return 0;
}

s32 dbgMenuKleinPTin(void) {
    heroSetFollowerWithID(3, 0);
    return 0;
}

s32 dbgMenuScriptFlagAllClear(void) {
    for (u32 i = 1; i < *flag_data_number; i++) {
        GSflagOff(i);
    }
    return 0;
}

s32 dbgMenuSetHeroStyleNormal(void) {
    Hero::getHeroPtr()->setHeroStyle(0, true);
    return 0;
}

s32 dbgMenuSetHeroStyleVisor(void) {
    Hero::getHeroPtr()->setHeroStyle(1, true);
    return 0;
}

s32 dbgMenuSetHeroStyleSnatch(void) {
    Hero::getHeroPtr()->setHeroStyle(2, true);
    return 0;
}

s32 dbgMenuDbgPokemonGet(void) {
    Pokemon pokemon;
    void* hero = savedataGetStatus(0, 2);
    pokemonCreate(&pokemon, 0x87, 0x28, gamedataGetStatus(0, 1));
    heroCatchPokemon(hero, &pokemon, 0, 4, 1);
    memoDataSet(0, &pokemon);
    pokemonCreate(&pokemon, 0x86, 0x28, gamedataGetStatus(0, 1));
    heroCatchPokemon(hero, &pokemon, 0, 4, 1);
    memoDataSet(0, &pokemon);
    pokemonCreate(&pokemon, 0x161, 0x64, gamedataGetStatus(0, 1));
    pokemonSetDarkPokemonStatus(&pokemon, 0x40);
    heroCatchPokemon(hero, &pokemon, 0, 4, 1);
    pokemonCreate(&pokemon, 0x162, 0x64, gamedataGetStatus(0, 1));
    pokemonSetDarkPokemonStatus(&pokemon, 0x4D);
    heroCatchPokemon(hero, &pokemon, 0, 4, 1);
    pokemonCreate(&pokemon, 0xAC, 0x64, gamedataGetStatus(0, 1));
    pokemonSetDarkPokemonStatus(&pokemon, 0x4C);
    heroCatchPokemon(hero, &pokemon, 0, 4, 1);
    pokemonCreate(&pokemon, 0xFA, 0x64, gamedataGetStatus(0, 1));
    pokemonSetDarkPokemonStatus(&pokemon, 0x1D);
    heroCatchPokemon(hero, &pokemon, 0, 4, 1);
    heroItemAddItemDataId(hero, 1, 99, -1);
    heroItemAddItemDataId(hero, 2, 99, -1);
    heroItemAddItemDataId(hero, 3, 99, -1);
    heroItemAddItemDataId(hero, 4, 99, -1);
    heroItemAddItemDataId(hero, 5, 99, -1);
    heroItemAddItemDataId(hero, 6, 99, -1);
    heroItemAddItemDataId(hero, 7, 99, -1);
    heroItemAddItemDataId(hero, 8, 99, -1);
    heroItemAddItemDataId(hero, 9, 99, -1);
    heroItemAddItemDataId(hero, 10, 99, -1);
    heroItemAddItemDataId(hero, 11, 99, -1);
    heroItemAddItemDataId(hero, 12, 99, -1);
    heroItemAddItemDataId(hero, 21, 99, -1);
    heroItemAddItemDataId(hero, 13, 300, -1);
    heroItemAddItemDataId(hero, 290, 1, -1);
    heroItemAddItemDataId(hero, 289, 3, -1);
    heroItemAddItemDataId(hero, 136, 3, -1);
    heroItemAddItemDataId(hero, 134, 1, -1);
    heroItemAddItemDataId(hero, 135, 2, -1);
    heroItemAddItemDataId(hero, 512, 1, -1);
    heroItemAddItemDataId(hero, 514, 1, -1);
    heroItemAddItemDataId(hero, 515, 1, -1);
    heroItemAddItemDataId(hero, 513, 1, -1);
    heroItemAddItemDataId(hero, 533, 1, -1);
    heroItemAddItemDataId(hero, 534, 1, -1);
    heroItemAddItemDataId(hero, 535, 1, -1);
    heroItemAddItemDataId(hero, 536, 1, -1);
    heroItemAddItemDataId(hero, 537, 1, -1);
    heroItemAddItemDataId(hero, 538, 1, -1);
    heroItemAddItemDataId(hero, 539, 1, -1);
    heroItemAddItemDataId(hero, 540, 1, -1);
    heroItemAddItemDataId(hero, 541, 1, -1);
    heroItemAddItemDataId(hero, 542, 1, -1);
    heroItemAddItemDataId(hero, 543, 1, -1);
    heroItemAddItemDataId(hero, 544, 1, -1);
    heroItemAddItemDataId(hero, 545, 1, -1);
    heroItemAddItemDataId(hero, 546, 1, -1);
    heroItemAddItemDataId(hero, 547, 1, -1);
    heroItemAddItemDataId(hero, 548, 1, -1);
    heroItemAddItemDataId(hero, 549, 1, -1);
    heroItemAddItemDataId(hero, 550, 1, -1);
    heroItemAddItemDataId(hero, 551, 1, -1);
    heroItemAddItemDataId(hero, 552, 1, -1);
    heroItemAddItemDataId(hero, 553, 1, -1);
    heroItemAddItemDataId(hero, 554, 1, -1);
    heroItemAddItemDataId(hero, 555, 1, -1);
    heroItemAddItemDataId(hero, 556, 1, -1);
    heroItemAddItemDataId(hero, 557, 1, -1);
    heroItemAddItemDataId(hero, 558, 1, -1);
    heroItemAddItemDataId(hero, 559, 1, -1);
    heroItemAddItemDataId(hero, 560, 1, -1);
    heroItemAddItemDataId(hero, 561, 1, -1);
    heroItemAddItemDataId(hero, 562, 1, -1);
    heroItemAddItemDataId(hero, 563, 1, -1);
    heroItemAddItemDataId(hero, 564, 1, -1);
    heroItemAddItemDataId(hero, 565, 1, -1);
    heroItemAddItemDataId(hero, 566, 1, -1);
    heroItemAddItemDataId(hero, 567, 1, -1);
    heroItemAddItemDataId(hero, 568, 1, -1);
    heroItemAddItemDataId(hero, 569, 1, -1);
    heroItemAddItemDataId(hero, 570, 1, -1);
    heroItemAddItemDataId(hero, 571, 1, -1);
    heroItemAddItemDataId(hero, 572, 1, -1);
    heroItemAddItemDataId(hero, 573, 1, -1);
    heroItemAddItemDataId(hero, 574, 1, -1);
    heroItemAddItemDataId(hero, 575, 1, -1);
    heroItemAddItemDataId(hero, 576, 1, -1);
    heroItemAddItemDataId(hero, 577, 1, -1);
    heroItemAddItemDataId(hero, 578, 1, -1);
    heroItemAddItemDataId(hero, 579, 1, -1);
    heroItemAddItemDataId(hero, 580, 1, -1);
    heroItemAddItemDataId(hero, 581, 1, -1);
    heroItemAddItemDataId(hero, 582, 1, -1);
    heroItemAddItemDataId(hero, 583, 1, -1);
    heroItemAddItemDataId(hero, 584, 1, -1);
    heroItemAddItemDataId(hero, 585, 1, -1);
    heroItemAddItemDataId(hero, 586, 1, -1);
    heroItemAddItemDataId(hero, 587, 1, -1);
    heroItemAddItemDataId(hero, 588, 1, -1);
    heroItemAddItemDataId(hero, 589, 1, -1);
    heroItemAddItemDataId(hero, 590, 1, -1);
    heroItemAddItemDataId(hero, 591, 1, -1);
    heroItemAddItemDataId(hero, 592, 1, -1);
    heroItemAddItemDataId(hero, 593, 1, -1);
    return 0;
}

s32 dbgMenuGSresDumpGroup(void) {
    GSresDumpAll();
    return 0;
}

s32 dbgMenuSoundVolumeDisp(void) {
    if (floorSound_getDispSoundVolume() == true) {
        floorSound_setDispSoundVolume(false);
    } else {
        floorSound_setDispSoundVolume(true);
    }
    return 0;
}

s32 dbgMenuPeopleViewerChara(void) { return 0; }

s32 dbgMenuPeopleViewerMotion(void) { return 0; }

s32 dbgMenuPeopleViewerPlaySpeed(void) { return 0; }

s32 dbgMenuPeopleViewerAnim(void) { return 0; }

s32 dbgMenuPeopleViewerEyeOnOff(void) { return 0; }

s32 dbgMenuPeopleViewerMouthOnOff(void) { return 0; }

s32 dbgMenuPeopleViewerRintoOnOff(void) { return 0; }

s32 dbgMenuGetRootMenu(void) {
    switch (pokecoloGetRomVersion()) {
    case 2:
        return 0x1F1;
    case 0:
    case 1:
    default:
        return 2;
    }
}

}
