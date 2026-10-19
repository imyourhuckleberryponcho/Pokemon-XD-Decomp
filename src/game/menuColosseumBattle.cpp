// STATUS (rough draft, rd_colb): 26/26 functions, 8 exact, byte-weighted ~88.6% with extra_cflags ["-inline noauto"]
// (+ peephole off, pool_strings off in-file). _CB fields are accessed by offset (CB macro): define a real _MENUCBWORK
// struct next. Open: .data jump tables @2836/@2894 (target uses dense switches in menuColosseumBattleMain/_duel; ours not),
// menuColosseumBattle 41% (the 3 init loops are unrolled differently), _duel 82%, teamselect 81%, SubWinDisp 81%.
#include <dolphin/types.h>

// Menu callbacks were built without the peephole optimizer.
#pragma peephole off
#pragma pool_strings off

struct _MENUCBTRAINER {
    u8 b[0x1320];
    _MENUCBTRAINER() {}
};

struct _MENUCBWORK {
    u8 pad0[0x18];
    _MENUCBTRAINER trainer[4];    // 0x18
    _MENUCBTRAINER trainerOrg[4]; // 0x4C98
    u8 rest[0xB5F4 - 0x9918];
};

struct TunaideSelect {
    s32 mode;     // 0x00
    s32 unk4;
    s32 homePlace; // 0x08
    u8 ctl[4];    // 0x0C
};

extern "C" {
u8 FlashSystemIsLastFrame(u32 id);
void FlashSystemSetNowFrameLabel(u32 id, const char* l);
void FlashSystemSetPlayFrameLabel(u32 id, const char* a, const char* b);
u32 GSflagGet(u32 f);
void GSflagSet(u32 f, s32 v);
s32 GSfloorGetCurrent();
void GSfloorPop();
void GSfloorPush(u32 id);
void GSfsysFree(u32 id);
void GSfsysReadWait(u32 id);
u8 GSinputIsConnected(s32 port);
void* GSmemAllocAlign(u32 size, u32 align);
void GSmemFree(void* p);
void GSresFreeGroup(u32 g);
void GSthreadSwitch();
s32 HSD_Rand(s32 n);
void cursorBiosInit();
void fadeCheck(s32 n);
void fadeSet(s32 id, f32 t);
void fightFreeResourceID(u32 a, u32 b);
u8 fightReadResourceID(u32 a, u32 b);
void floorSetFadeScript(s32 a, s32 b);
void floorWaitForChange();
void fn_80151F6C(void* cb);
u32 gamedatasaveGetStatus(s32 a, s32 b);
u8 gbaCommandIsConnected(s32 p);
void* getDancerPointer__12CReliveStageFl(void* stage, s32 i);
void* getPointer__11CReliveHallFv();
void* getStage__11CReliveHallFl(void* hall, s32 i);
void heroBiosCopy(void* dst, void* src);
void* heroBiosGetPokemonPtr(void* hero, u16 i);
void heroBiosSetHomePlace(void* hero, s32 p);
void heroInit(void* hero);
u8 memcardIsMemCardValid();
void* memcardMemAllocForSavedata();
void* memcardMemFreeForSavedata(void* p);
s32 memcardTaskCall(s32 a, s32 b, s32 c);
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
void menuCB2DPokemonALLClear();
u8 menuCBBios_ContextIsLocked(void*);
void menuCBBios_CurrentlyWorkingToolBattleSet(s8 v);
void* menuCBBios_GetTrainerImmediately(s32 i);
void menuCBBios_InitContext(void* cb);
void menuCBBios_InitVersusTrainer(void* t, void* hero);
void menuCBBios_LockContext();
void menuCBBios_RuleConstRuleSet();
void menuCBBios_RuleEditSaveON(u8 on);
void menuCBBios_UnlockContext();
void menuCBGCEntryPokemon();
void menuCBPokemonEntryLoadTex();
void menuCBReliveHallCursolInit();
void* menuCBRule_ConstantRule2(s32 i);
void menuCBRule_Copy(void* dst, void* src);
u8 menuCBRule_IsEquals(void* a, void* b);
void menuCBTrainerBios_SetControlerID(void* t, s8 id);
void menuCBTrainerBios_SetHomePlace(void* t, s32 p);
s32 menuCB_CurrentMenuID();
void menuCB_GBADisconnectedErrorJob();
void menuCB_GCEntry_ItemGiveJob();
void menuCB_GCEntry_ItemKeepJob();
void menuCB_GCEntry_PokemonStatusDisp();
s32 menuCB_GCEntry_SubWindow_Disp();
void menuCB_GCPokemonHPandWAZA_MAX();
void menuCB_InitBattle(void* cb);
s32 menuCB_MenuPop();
void menuCB_MenuPush(s32 id);
s32 menuCB_MenuRollback(s32 id);
void menuCB_RuleNameChengeAfterJob(s32 a);
void menuCB_RuleNameChengeBeforeJob(s32 a);
void* menuCB_RuleTitleNameGet(s32 i);
void menuCB_SE_Play(s32 id, ...);
void menuCB_TUNAIDE01_Rule_SELECT();
void menuCB_WaitGCControler1();
void menuCBpokemonFaceReadWait();
void menuCloseCustom(s32 id, s32 a, s32 b);
void menuGBACSetRomVer(s32 a, s32 b, s32 c);
u8 menuIsCheck(s32 id);
s32 menuNameEntryOpen(s32 a, void* name);
void menuOpen(s32 id, s32 a);
void menuOpenCustom(s32 id, s32 parent, void* out, s32 a, s32 b, s32 c);
s8 menuSubOpenYesNo(s32 a, s32 b, s32 c, s32 d);
void menuTopOpenFlashBack();
void menuTopSetBattleSelectMode(s32 m);
s32 openMenuGBA(s32 a, s32 b, s32* list);
s32 pokecoloGetCountryCode();
void pokemonBiosCopy(void* dst, void* src);
void pokemonInit(void* p);
void* savedataGetStatus(void* save, s32 kind);
void soundOpenPlay(s32 id, s32 a, s32 b);
void soundStop(s32 id, s32 t);
void systemFree__4CAntFv();
void systemInit__4CAntFv();
void toolentryDebugPokemonCreate();
void toolentryDebugPokemonDelete();
void toolentryTaisenEntryPokemon(s32 i);
void toolentryTaisenSetEtnryPokemonOrder(s32 a, s32 b);
void winMsgClose(s32 a);
void winMsgOpen(s32 a, s32 b, s32 c, s32 d);
s32 windowGetActiveID();
void* windowSearchID(s32 id);
}

struct FlagEtcData {
    u8 pad[0x428];
    u32 reliveOpenFlag;
};
extern "C" FlagEtcData* flag_etc;

static u8* _menuCB_Temp;
static s32 _menuCB_RuleData_SaveJob_flag;
extern "C" {
void* pGCB;
}
void* toolBattleTempSaveData;
_MENUCBWORK _CB;

#define CB(T, off) (*(T*)((u8*)&_CB + (off)))

static u8 _flashBackFlag = 1;

static const TunaideSelect tunaide_select[4] = {
    { 0, 0, 0, { 1, 2, 0, 0 } },
    { 0, 0, 1, { 2, 3, 0, 0 } },
    { 2, 2, 0, { 1, 2, 3, 4 } },
    { 2, 2, 1, { 1, 2, 3, 4 } },
};
static const s32 tunaide_select_field[6] = { 0, 1, 2, 3, 4, 5 };

static s32 _YesNo(long a);
static void _menuCB_RuleData_SaveJob(long a);
static s32 _menuCB_SaveRule();
extern "C" void menuColosseumBattleExit(void);
extern "C" void fn_8004429C(void);
extern "C" void fn_80044314(void);
static void _menuCB_RuleData_CBtoSAVEDATA();
static void _menuCB_Rule_Page_Chenge_Init2();
static void _menuCB_RuleEdit_Cursol_Init(long a);
static void menuCB_SAVEDATA_recover();
static void menuCB_GCEntry_Job();
static u8 menuCB_SubWinDisp_GCENTRY();
static void _tempHeroInitAll();

extern "C" void fn_8004429C(void) {
    u8* row = (u8*)&_CB;
    for (s32 s = 0; s < 9; s++, row += 0x10) {
        u8* slot = row;
        for (s32 i = 0; i < 4; i++, slot += 4) {
            if (*(u32*)(slot + 0xB524) != 0) {
                GSmemFree((void*)*(u32*)(slot + 0xB524));
                *(u32*)(slot + 0xB524) = 0;
            }
        }
    }
}

extern "C" void fn_80044314(void) {
    u8* row = (u8*)&_CB;
    u8* row2 = (u8*)&_CB;
    for (s32 s = 0; s < 9; s++, row += 0x10) {
        u8* slot = row;
        for (s32 i = 0; i < 4; i++, slot += 4) {
            *(void**)(slot + 0xB524) = GSmemAllocAlign(0xC4, 0x20);
            pokemonInit(*(void**)(slot + 0xB524));
        }
    }
    for (s32 s = 0; s < 9; s++, row2 += 0x10) {
        getPointer__11CReliveHallFv();
        void* stage = getStage__11CReliveHallFl(getPointer__11CReliveHallFv(), s);
        u8* slot = row2;
        for (s32 i = 0; i < 4; i++, slot += 4) {
            pokemonBiosCopy(*(void**)(slot + 0xB524), getDancerPointer__12CReliveStageFl(stage, i));
        }
    }
}

static void _menuCB_RuleData_CBtoSAVEDATA() {
    memcpy(&CB(u8, 0x9918), savedataGetStatus(0, 0xE), 0x360);
}

static void _menuCB_Rule_Page_Chenge_Init2() {
    CB(s32, 0xB124) = CB(s32, 0xB118);
    CB(s32, 0xB128) = 0xFF;
    CB(s32, 0xB12C) = 0xF;
}

static void _menuCB_RuleEdit_Cursol_Init(long v) {
    CB(s32, 0xB0AC) = v;
    CB(s32, 0xB0A8) = v;
    CB(s32, 0xB0A4) = v;
    CB(s32, 0xB0A0) = v;
    CB(s32, 0xB09C) = v;
    CB(s32, 0xB098) = v;
    CB(s32, 0xB094) = v;
    CB(s32, 0xB02C) = v;
    CB(s32, 0xB028) = v;
    CB(s32, 0xB024) = v;
    CB(s32, 0xB020) = v;
    CB(s32, 0xB01C) = v;
    CB(s32, 0xB018) = v;
    CB(s32, 0xB014) = v;
}

void menuCB_RuleCustomJobDisp(long mode) {
    s32 cursor;
    if (mode == 0) cursor = 0;
    if (mode == 1) cursor = -1;
    CB(void*, 0x9C78) = &CB(u8, 0x9918) + CB(s32, 0xB004) * 0x90;
    menuCBRule_Copy(_menuCB_Temp + 0x3990, menuCBRule_ConstantRule2(CB(s32, 0xB004)));
    menuCBRule_Copy(_menuCB_Temp + 0x3A20, CB(void*, 0x9C78));
    _menuCB_RuleEdit_Cursol_Init(cursor);
    CB(s32, 0xB118) = 0;
    CB(s32, 0xB11C) = 0;
    CB(s32, 0xB090) = 0;
    CB(s32, 0xB010) = 0;
    CB(s32, 0xB0B4) = 1;
    CB(s32, 0xB0B0) = 1;
    CB(s32, 0xB034) = 1;
    CB(s32, 0xB030) = 1;
    CB(s32, 0xB124) = -1;
    CB(s32, 0xB130) = 0;
    CB(s32, 0xB134) = 0x1F4;
    menuCB_SE_Play(0x14, -1, 1, 0);
    menuOpen(0xF5, 0);
    menuOpen(0xEF, 0);
    menuOpen(0xF0, 0);
    menuOpen(0xF1, 0);
    menuOpen(0xF2, 0);
    menuOpen(0xF3, 0);
    menuOpen(0xF4, 0);
    do {
        if (CB(s32, 0xB0B0) == 0) {
            winMsgOpen(2, 0x4411, 1, 1);
            if (_YesNo(0) == 0) {
                menuCBRule_Copy(CB(void*, 0x9C78), _menuCB_Temp + 0x3990);
                _menuCB_RuleEdit_Cursol_Init(0);
                winMsgClose(0);
                _menuCB_Rule_Page_Chenge_Init2();
                CB(s32, 0xB118) = 0;
            } else {
                winMsgClose(0);
            }
            CB(s32, 0xB0B0) = 1;
            CB(s32, 0xB030) = 1;
        }
        if (CB(s32, 0xB0B4) == 0) {
            winMsgOpen(2, 0x4412, 1, 1);
            if (_YesNo(0) == 0) {
                menuCBRule_Copy(CB(void*, 0x9C78), _menuCB_Temp + 0x3A20);
                _menuCB_RuleEdit_Cursol_Init(0);
                winMsgClose(0);
                _menuCB_Rule_Page_Chenge_Init2();
                CB(s32, 0xB118) = 0;
            } else {
                winMsgClose(0);
            }
            CB(s32, 0xB0B4) = 1;
            CB(s32, 0xB034) = 1;
        }
        if (CB(s32, 0xB010) == 2) {
            if (CB(s32, 0xB014) == -1) CB(s32, 0xB010) = 0;
            CB(s32, 0xB090) = 2;
        }
        if (CB(s32, 0xB010) == 1) {
            if (menuCBRule_IsEquals(_menuCB_Temp + 0x3A20, CB(void*, 0x9C78)) == 0) {
                _menuCB_RuleData_SaveJob(0);
                if (_menuCB_RuleData_SaveJob_flag == 0) CB(s32, 0xB090) = 1;
                else CB(s32, 0xB11C) = 0;
            } else {
                CB(s32, 0xB090) = 1;
            }
            CB(s32, 0xB010) = 0;
        }
        GSthreadSwitch();
    } while (CB(s32, 0xB090) == 0);
    if (CB(s32, 0xB010) == 2 && menuCBRule_IsEquals(_menuCB_Temp + 0x3A20, CB(void*, 0x9C78)) == 0) {
        _menuCB_RuleData_SaveJob(0);
        if (_menuCB_RuleData_SaveJob_flag == 0 && memcardIsMemCardValid() != 0) CB(s32, 0xB090) = 1;
        else CB(s32, 0xB090) = 2;
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xF4, 0, 0);
    menuCloseCustom(0xF3, 0, 0);
    menuCloseCustom(0xF2, 0, 0);
    menuCloseCustom(0xF1, 0, 0);
    menuCloseCustom(0xF0, 0, 0);
    menuCloseCustom(0xEF, 0, 0);
    menuCloseCustom(0xF5, 0, 1);
    if (CB(s32, 0xB090) == 2) {
        menuCBRule_Copy(CB(void*, 0x9C78), _menuCB_Temp + 0x3A20);
        _menuCB_RuleData_CBtoSAVEDATA();
    }
    if (memcardIsMemCardValid() == 0) {
        _menuCB_RuleData_CBtoSAVEDATA();
        menuCBBios_RuleEditSaveON(1);
    }
}

static void _menuCB_RuleData_SaveJob(long v) {
    _menuCB_RuleData_SaveJob_flag = v;
    while (1) {
        if (memcardIsMemCardValid() != 0) {
            winMsgOpen(2, 0xCB, 1, 1);
            s32 r = _YesNo(0);
            _menuCB_RuleData_SaveJob_flag = r;
            if (r == 0) {
                _menuCB_RuleData_CBtoSAVEDATA();
                if (_menuCB_SaveRule() < 0) continue;
            }
        }
        break;
    }
    winMsgClose(1);
}

extern "C" void menuCB_FlashEnd(u8 v) {
    if (v != 0 && menuIsCheck(0x119) == 1) menuCloseCustom(0x119, 0, 0);
}

extern "C" void menuCB_FlashStart(u8 v) {
    if (v != 0) {
        if (CB(s32, 4) == 1) {
            FlashSystemSetPlayFrameLabel(0x200A3000, "1_start", "1_end");
            FlashSystemSetNowFrameLabel(0x200A3000, "1_start");
        } else {
            FlashSystemSetPlayFrameLabel(0x200A3000, "2_start", "2_end");
            FlashSystemSetNowFrameLabel(0x200A3000, "2_start");
        }
    } else if (CB(s32, 4) == 1) {
        FlashSystemSetPlayFrameLabel(0x200A3000, "1_end", "1_end");
        FlashSystemSetNowFrameLabel(0x200A3000, "1_end");
    } else {
        FlashSystemSetPlayFrameLabel(0x200A3000, "2_end", "2_end");
        FlashSystemSetNowFrameLabel(0x200A3000, "2_end");
    }
    u8* w = (u8*)windowSearchID(0x119);
    if (w != 0) w[9] = 0;
    CB(s32, 0xB13C) = 1;
    do {
        GSthreadSwitch();
    } while (FlashSystemIsLastFrame(0x200A3000) == 0);
}

static u8 menuCB_SubWinDisp_GCENTRY() {
    if (CB(s32, 0xB0F4) == 1) {
        if (CB(s32, 0xB070) == 1) return 0;
        if (CB(s32, 0xAFF0) == 1) {
            s32 r = menuCB_GCEntry_SubWindow_Disp();
            switch (r) {
            case 1:
                CB(s32, 0xB0F4) = 0;
                CB(s32, 0xAFF0) = 0;
                return 1;
            case 0:
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        s32 r = menuCB_GCEntry_SubWindow_Disp();
        GSthreadSwitch();
        if (r != 4) {
            if (r < 4) {
                if (r != 2) {
                    if (r < 2) {
                        if (r < 0) goto done;
                        menuCBGCEntryPokemon();
                        if (CB(s32, 0xB0FC) >= 2) return 1;
                        CB(s32, 0xB0FC) = 0;
                        s32 country = pokecoloGetCountryCode();
                        if (country != 0) {
                            if (country >= 0) {
                            }
                        } else if (CB(s32, 0xB0F0) == 2) {
                            menuCBReliveHallCursolInit();
                        }
                        return 1;
                    }
                    goto done;
                }
                menuCB_GCEntry_PokemonStatusDisp();
                goto done;
            }
            if (r != 6 && r < 6) menuCB_GCEntry_ItemKeepJob();
            goto done;
        }
        menuCB_GCEntry_ItemGiveJob();
    done:
        CB(s32, 0xB0FC) = 0;
        return 1;
    }
    return 0;
}

static void menuCB_SAVEDATA_recover() {
    void* dst = savedataGetStatus(0, 0xE);
    memcpy(dst, savedataGetStatus(toolBattleTempSaveData, 0xE), 0x360);
    memcpy(savedataGetStatus(0, 0), toolBattleTempSaveData, 0x27FD0);
}

static void menuCB_GCEntry_Job() {
    void* save = savedataGetStatus(0, 2);
    void* hero = &CB(u8, 0xA65C);
    heroBiosCopy(hero, save);
    for (u16 i = 0; i < 6; i++) {
        pokemonInit(heroBiosGetPokemonPtr(hero, i));
    }
    menuCB_GCPokemonHPandWAZA_MAX();
    s32 c = pokecoloGetCountryCode();
    if (c != 0 && c >= 0 && c < 3) fn_80044314();
    CB(s32, 0xB100) = 0;
    CB(s32, 0xB0FC) = 0;
    CB(s32, 0xB0F8) = 0;
    CB(s32, 0xB0F0) = 0;
    CB(s32, 0xB0EC) = 0;
    CB(s32, 0xB0E8) = 0;
    CB(s32, 0xB070) = 0;
    CB(s32, 0xAFF0) = 0;
    CB(s32, 0xB0D8) = 0;
    CB(s32, 0xB150) = 0;
    menuCB_SE_Play(0x14, &_CB);
    menuOpen(0xBB, 0);
    menuOpen(0xBD, 0);
    menuOpen(0xBE, 0);
    menuOpen(0xBF, 0);
    menuOpen(0x10D, 0);
    menuOpen(0x10F, 0);
    menuOpen(0x10E, 0);
    menuOpen(0xC2, 0);
    do {
        CB(s32, 0xB0F4) = 0;
        CB(s32, 0xB0FC) = 0;
        do {
            menuOpen(0xBC, 1);
        } while (menuCB_SubWinDisp_GCENTRY() != 0);
    } while (CB(s32, 0xAFF0) == 0);
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
    heroBiosCopy(save, hero);
    systemFree__4CAntFv();
    c = pokecoloGetCountryCode();
    if (c != 0 && c >= 0 && c < 3) fn_8004429C();
}

static void _imasuguBattleMenuMain() {
    menuCB_SE_Play(0x14);
    while (1) {
        if (CB(s32, 0xB17C) != 0) {
            menuOpen(0xA4, 0);
        } else {
            menuOpen(0xA4, 1);
            if (CB(s32, 0xB054) != 1) goto open;
            menuCB_SE_Play(0x15);
            menuCloseCustom(0xA4, 0, 0);
            menuCBBios_UnlockContext();
            fn_80151F6C(0);
            menuCloseCustom(0xA4, 0, 1);
            _flashBackFlag = 0;
            GSfloorPop();
            menuTopSetBattleSelectMode(0);
            floorSetFadeScript(0, 0);
            return;
        }
    open:
        CB(s8, 0xB4A1) = -1;
        menuOpenCustom(0x106, windowGetActiveID(), &CB(u8, 0xAFD8), 0, 1, 0);
        if (CB(s32, 0xAFD8) == 4 || CB(s32, 0xB058) == 1) {
            menuCloseCustom(0x106, 0, 1);
            CB(s32, 0xB058) = 0;
            CB(s32, 0xAFD8) = 0;
            CB(s32, 0xB17C) = 0;
        } else {
            CB(s32, 0xB17C) = 1;
            CB(s32, 8) = 1;
            CB(s32, 0xC) = 0;
            CB(s32, 0x10) = HSD_Rand(1) % 3;
            switch (CB(s32, 0xAFD4)) {
            case 0:
                CB(s32, 0x14) = 3;
                break;
            case 1:
                CB(s32, 0x14) = 4;
                break;
            }
            menuCB_InitBattle(&_CB);
            menuCBPokemonEntryLoadTex();
            menuCloseCustom(0x106, 2, 0);
            menuCloseCustom(0xA4, 2, 1);
            menuCBpokemonFaceReadWait();
            menuOpenCustom(0xA5, windowGetActiveID(), &CB(u8, 0xAFDC), 0, 1, 0);
            menuCloseCustom(0xA5, 0, 1);
            if (CB(s32, 0xAFDC) == 1 || CB(s32, 0xB05C) == 1) {
                CB(s32, 0xB05C) = 0;
                CB(s32, 0xAFDC) = 0;
                menuCB_SE_Play(0x14);
            } else {
                for (s32 i = 0; i < 2; i++) {
                    toolentryTaisenSetEtnryPokemonOrder(0, i);
                    toolentryTaisenSetEtnryPokemonOrder(1, i);
                }
                u8* t0 = (u8*)menuCBBios_GetTrainerImmediately(0);
                *(s32*)(t0 + 0x10) = 0xF;
                *(s32*)(t0 + 0x14) = 0xF;
                *(s32*)(t0 + 0x18) = 0xF;
                *(s32*)(t0 + 0x1C) = 0xF;
                u8* t1 = (u8*)menuCBBios_GetTrainerImmediately(1);
                *(s32*)(t1 + 0x10) = 0xF;
                *(s32*)(t1 + 0x14) = 0xF;
                *(s32*)(t1 + 0x18) = 0xF;
                *(s32*)(t1 + 0x1C) = 0xF;
                toolentryTaisenEntryPokemon(0);
                toolentryTaisenEntryPokemon(1);
                soundStop(0x568, 0x1F4);
                menuCBBios_LockContext();
                menuColosseumBattleExit();
                _flashBackFlag = 1;
                GSfloorPush(0x397);
                floorWaitForChange();
                menuTopOpenFlashBack();
                menuCB_FlashStart(0);
                soundOpenPlay(0x568, 0, 0xFF);
            }
        }
    }
}

static s32 _YesNo(long a) {
    s32 c = pokecoloGetCountryCode();
    if (c != 0) {
        if (c >= 0 && c < 3) return menuSubOpenYesNo(0, 0x3C, 0xC8, a);
        return 0;
    }
    return menuSubOpenYesNo(0, 0x3C, 0xD2, a);
}

static void _tempHeroInitAll() {
    s32 off = 0;
    for (u32 i = 0; i < 4; i++) {
        memset(_menuCB_Temp + off + 0x1320, 0, 0x978);
        heroInit(_menuCB_Temp + off + 0x1320);
        off += 0x978;
    }
}

static s32 _menuCB_SaveRule() {
    menuCBBios_RuleEditSaveON(1);
    menuCBBios_CurrentlyWorkingToolBattleSet(0);
    s32 r = memcardTaskCall(0xD, 2, 0);
    menuCBBios_CurrentlyWorkingToolBattleSet(1);
    if (r != 4) menuCBBios_RuleEditSaveON(0);
    if (r == 4) return 0;
    return -1;
}

static s32 _colosseumbattlemenu_teamselect(long) {
    static const s32 sta[3] = { 0x10203, 0x20103, 0x30102 };
    CB(s32, 0xB198) = 0;
    CB(s32, 0xB06C) = 0;
    CB(s32, 0xAFEC) = 0;
    menuCB_SE_Play(0x14, &_CB);
    menuOpen(0xAC, 1);
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xAC, 0, 1);
    if (CB(s32, 0xB198) != 0 || CB(s32, 0xB06C) == 1) {
        menuCB_GBADisconnectedErrorJob();
        return menuCB_MenuRollback(0xA9);
    }
    s32 next = 0xB1;
    s32 sel = CB(s32, 0xAFEC);
    if (sel != 3 && sel < 3) {
        if (sel < 0) goto fail;
        const u8* e = (const u8*)&sta[sel];
        u8 a = e[0], b = e[1], c = e[2];
        CB(s32, 0x4CC0) = (s8)a;
        CB(s32, 0x5FE0) = (s8)b;
        CB(s32, 0x7300) = (s8)c;
        CB(s32, 0x8620) = (s8)e[3];
        menuCB_InitBattle(&_CB);
    } else {
    fail:
        menuCB_GBADisconnectedErrorJob();
        next = menuCB_MenuRollback(0xA9);
    }
    return next;
}

static s32 _colosseumbattlemenu_playerdecide(long) {
    CB(s32, 0xB068) = 0;
    CB(s32, 0xB0D4) = 0;
    CB(s32, 0xB194) = 0;
    menuCB_SE_Play(0x14, &_CB);
    menuOpen(0xAB, 1);
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xAB, 0, 1);
    if (CB(s32, 0xB194) != 0 || CB(s32, 0xB068) == 1) {
        menuCB_GBADisconnectedErrorJob();
        return menuCB_MenuRollback(0xA9);
    }
    if (CB(s32, 8) != 2) {
        menuCB_InitBattle(0);
        return 0xB1;
    }
    return 0xAC;
}

static s32 _gbac_connect_job(long) {
    s32 list[4];
    s32 type;
    _tempHeroInitAll();
    menuCBTrainerBios_SetControlerID(&CB(u8, 0x18), 1);
    menuCBTrainerBios_SetControlerID(&CB(u8, 0x1338), 2);
    menuCBTrainerBios_SetControlerID(&CB(u8, 0x2658), 3);
    menuCBTrainerBios_SetControlerID(&CB(u8, 0x3978), 4);
    if (CB(s32, 8) != 2 && CB(s32, 8) < 2) {
        if (CB(s32, 8) < 0) goto four;
        if (CB(s32, 0x4C9C) == 0) {
            list[2] = 0;
            type = 0;
            list[3] = 0;
            list[0] = (s32)(_menuCB_Temp + 0x1320);
            list[1] = (s32)(_menuCB_Temp + 0x1C98);
        } else {
            list[0] = 0;
            type = 1;
            list[1] = (s32)(_menuCB_Temp + 0x1320);
            list[2] = (s32)(_menuCB_Temp + 0x1C98);
            list[3] = 0;
        }
    } else {
    four:
        if (CB(s32, 0x4C9C) == 0) type = 2;
        else type = 3;
        list[0] = (s32)(_menuCB_Temp + 0x1320);
        list[1] = (s32)(_menuCB_Temp + 0x1C98);
        list[2] = (s32)(_menuCB_Temp + 0x2610);
        list[3] = (s32)(_menuCB_Temp + 0x2F88);
    }
    if (CB(s32, 0x4C9C) == 0) {
        menuCB_SAVEDATA_recover();
        menuCB_GCEntry_Job();
        if (CB(s32, 0xB070) == 1) {
            menuCB_SAVEDATA_recover();
            return menuCB_MenuRollback(0xA9);
        }
    } else {
        systemFree__4CAntFv();
    }
    if (openMenuGBA(type, 0x1A, list) < 0) return menuCB_MenuRollback(0xA9);
    if (CB(s32, 0x4C9C) == 0) heroBiosSetHomePlace(_menuCB_Temp + 0x1320, 0);
    if (CB(s32, 8) != 2 && CB(s32, 8) < 2) {
        if (CB(s32, 8) < 0) goto four2;
        void* t0 = &CB(u8, 0x4C98);
        menuCBBios_InitVersusTrainer(t0, _menuCB_Temp + 0x1320);
        void* t1 = &CB(u8, 0x5FB8);
        menuCBBios_InitVersusTrainer(t1, _menuCB_Temp + 0x1C98);
        if (CB(s32, 0x4C9C) == 0) {
            menuCBTrainerBios_SetControlerID(t0, 1);
            menuCBTrainerBios_SetControlerID(t1, 2);
        } else {
            menuCBTrainerBios_SetControlerID(t0, 2);
            menuCBTrainerBios_SetControlerID(t1, 3);
        }
        menuCBTrainerBios_SetControlerID(&CB(u8, 0x72D8), 0);
        menuCBTrainerBios_SetControlerID(&CB(u8, 0x85F8), 0);
    } else {
    four2:
        void* t0 = &CB(u8, 0x4C98);
        menuCBBios_InitVersusTrainer(t0, _menuCB_Temp + 0x1320);
        void* t1 = &CB(u8, 0x5FB8);
        menuCBBios_InitVersusTrainer(t1, _menuCB_Temp + 0x1C98);
        void* t2 = &CB(u8, 0x72D8);
        menuCBBios_InitVersusTrainer(t2, _menuCB_Temp + 0x2610);
        void* t3 = &CB(u8, 0x85F8);
        menuCBBios_InitVersusTrainer(t3, _menuCB_Temp + 0x2F88);
        menuCBTrainerBios_SetControlerID(t0, 1);
        menuCBTrainerBios_SetControlerID(t1, 2);
        menuCBTrainerBios_SetControlerID(t2, 3);
        menuCBTrainerBios_SetControlerID(t3, 4);
    }
    return 0xAB;
}

static s32 _colosseumbattlemenu_duel(long) {
    s32 next;
    memcpy(&CB(u8, 0x9918), savedataGetStatus(0, 0xE), 0x360);
    systemInit__4CAntFv();
    menuCB2DPokemonALLClear();
    cursorBiosInit();
    CB(s32, 0xB10C) = 0;
    CB(s32, 0xB064) = 0;
    CB(s32, 0xAFE4) = 0;
    CB(s32, 0xB144) = -1;
    menuGBACSetRomVer(0, 0xFFFF, 0);
    menuCB_SE_Play(0x14);
    menuOpen(0xA9, 0);
    menuOpen(0xCE, 0);
    menuOpen(0xCB, 0);
    menuOpen(0xCC, 0);
    menuOpen(0xCD, 0);
    menuOpen(0xAA, 0);
    menuOpen(0xF7, 0);
loop:
    if (CB(s32, 0xB10C) == 2) {
        CB(s32, 0xAFE0) = 0;
    again:
        if (CB(s32, 0xAFE0) >= 0x10) CB(s32, 0xAFE0) = CB(s32, 0xAFE0) - 0x10;
        menuCB_TUNAIDE01_Rule_SELECT();
        if ((u32)CB(s32, 0xAFE0) <= 0x13) {
            switch (CB(s32, 0xAFE0)) {
            case 1:
                menuCB_RuleNameChengeBeforeJob(0);
                menuCB_RuleCustomJobDisp(1);
                menuCB_RuleNameChengeAfterJob(0);
                goto again;
            case 17:
                menuCB_RuleNameChengeBeforeJob(0);
                menuCB_RuleCustomJobDisp(0);
                menuCB_RuleNameChengeAfterJob(0);
                goto again;
            case 18: {
                menuCB_RuleNameChengeBeforeJob(1);
                u16* name = (u16*)menuCB_RuleTitleNameGet(CB(s32, 0xB004));
                u16 save[21];
                for (int k = 0; k < 21; k++) save[k] = name[k];
                s32 r = menuNameEntryOpen(6, name);
                menuCB_RuleNameChengeAfterJob(1);
                if (r != 0) {
                    if (memcardIsMemCardValid() == 0) {
                        _menuCB_RuleData_CBtoSAVEDATA();
                        menuCBBios_RuleEditSaveON(1);
                    } else {
                        _menuCB_RuleData_SaveJob(0);
                        if (_menuCB_RuleData_SaveJob_flag != 0) {
                            for (int k = 0; k < 21; k++) name[k] = save[k];
                            _menuCB_RuleData_CBtoSAVEDATA();
                        }
                    }
                }
                goto again;
            }
            default:
                break;
            }
        }
    }
    if (CB(s32, 0xB064) == 2) {
        next = -1;
        menuGBACSetRomVer(0, 0xFFFF, 0);
        CB(s32, 0xC) = 0;
        fn_80151F6C(&_CB);
    } else if (CB(s32, 0xB064) == 1) {
        if (CB(s32, 0xAFF4) == 0 || CB(s32, 0xAFF4) == 2) {
            if (memcardIsMemCardValid() == 0) {
                winMsgOpen(2, 0x82, 1, 0);
                winMsgClose(1);
                CB(s32, 0xB064) = 0;
                goto loop;
            }
            if (gamedatasaveGetStatus(0, 4) == 0) {
                winMsgOpen(2, 0x9C, 1, 0);
                winMsgClose(1);
                CB(s32, 0xB064) = 0;
                goto loop;
            }
        }
        winMsgOpen(2, 0x4419, 1, 1);
        if (_YesNo(0) != 0) {
            winMsgClose(0);
            CB(s32, 0xB064) = 0;
            goto loop;
        }
        winMsgClose(0);
        CB(s32, 8) = tunaide_select[CB(s32, 0xAFF4)].mode;
        if (CB(s32, 0xAFFC) == 6) CB(s32, 0x10) = 0;
        else CB(s32, 0x10) = tunaide_select_field[CB(s32, 0xAFFC)];
        void* t0 = &CB(u8, 0x4C98);
        menuCBTrainerBios_SetHomePlace(t0, tunaide_select[CB(s32, 0xAFF4)].homePlace);
        menuCBTrainerBios_SetControlerID(t0, (s8)tunaide_select[CB(s32, 0xAFF4)].ctl[0]);
        u8* t = &CB(u8, 0x4C98) + 0x1320;
        for (u32 i = 1; i < 4; i++, t += 0x1320) {
            menuCBTrainerBios_SetHomePlace(t, 1);
            menuCBTrainerBios_SetControlerID(t, (s8)tunaide_select[CB(s32, 0xAFF4)].ctl[i]);
        }
        if (CB(s32, 0xAFF8) == 0) CB(s32, 8) = 0;
        else CB(s32, 8) = 1;
        if (CB(s32, 0xAFF4) >= 2) CB(s32, 8) = 2;
        next = 0xB0;
    } else {
        GSthreadSwitch();
        goto loop;
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xF7, 0, 0);
    menuCloseCustom(0xAA, 0, 0);
    menuCloseCustom(0xCD, 0, 0);
    menuCloseCustom(0xCC, 0, 0);
    menuCloseCustom(0xCB, 0, 0);
    menuCloseCustom(0xCE, 0, 0);
    menuCloseCustom(0xA9, 0, 1);
    if (CB(s32, 0xB064) == 2) systemFree__4CAntFv();
    CB(s32, 0xC) = CB(s32, 0xB004);
    return next;
}

extern "C" void menuColosseumBattleMain(void) {
    menuCB_CurrentMenuID();
    u32 floor = 0;
    menuCB_FlashStart(1);
    while (1) {
        soundOpenPlay(0x568, 0, 0xFF);
        if (CB(s32, 4) == 1) {
            menuGBACSetRomVer(0, 0xFFFF, 0);
            _imasuguBattleMenuMain();
            return;
        }
        CB(s8, 0xB4A1) = 0;
        while (1) {
            if (menuCB_CurrentMenuID() > 0) {
                menuCB_CurrentMenuID();
                s32 next = menuCB_CurrentMenuID();
                switch (menuCB_CurrentMenuID()) {
                case 0xA9:
                    next = _colosseumbattlemenu_duel(next);
                    break;
                case 0xB0:
                    next = _gbac_connect_job(next);
                    break;
                case 0xAB:
                    next = _colosseumbattlemenu_playerdecide(next);
                    break;
                case 0xAC:
                    next = _colosseumbattlemenu_teamselect(next);
                    break;
                case 0xB1:
                    soundStop(0x568, 0x1F4);
                    menuCBBios_LockContext();
                    floor = 0x397;
                    break;
                }
                if (GSinputIsConnected(1) == 0 && gbaCommandIsConnected(1) == 0) {
                    winMsgOpen(2, 0x4436, 0, 0);
                    GSthreadSwitch();
                    do {
                        GSthreadSwitch();
                    } while (GSinputIsConnected(1) == 0);
                    winMsgClose(1);
                }
                if (next < 0) {
                    if (menuCB_MenuPop() >= 0) goto after;
                } else {
                    if (next != menuCB_CurrentMenuID()) {
                        s32 cur = menuCB_CurrentMenuID();
                        if (windowGetActiveID() == cur) {
                            menuCB_CurrentMenuID();
                            menuCloseCustom(0, 0, 0);
                        }
                        menuCB_MenuPush(next);
                    }
                after:
                    if (floor != 0) {
                        s32 cur = menuCB_CurrentMenuID();
                        if (windowGetActiveID() == cur) {
                            menuCB_CurrentMenuID();
                            menuCloseCustom(0, 0, 0);
                        }
                    } else {
                        continue;
                    }
                }
            }
            break;
        }
        if (floor == 0) {
            floor = 0x384;
            menuCBBios_UnlockContext();
            menuCB_WaitGCControler1();
        } else {
            menuCBBios_LockContext();
        }
        if (floor == 0x384) {
            _flashBackFlag = 0;
            GSfloorPop();
            menuTopSetBattleSelectMode(1);
            floorSetFadeScript(0, 0);
            return;
        }
        _flashBackFlag = 1;
        fadeSet(3, 0.5f);
        fadeCheck(1);
        menuColosseumBattleExit();
        GSfloorPush(floor);
        floorSetFadeScript(0, 0x05960008);
        floorWaitForChange();
        menuTopOpenFlashBack();
        menuCB_FlashStart(0);
        fadeSet(2, 0.5f);
        fadeCheck(1);
        menuCB_CurrentMenuID();
        floor = 0;
    }
}

extern "C" void menuColosseumBattleExit(void) {
    fadeCheck(1);
    if (menuCBBios_ContextIsLocked(0) == 0) GSflagSet(0x30D, 0);
    toolentryDebugPokemonDelete();
    if (CB(s32, 4) == 1) {
        if (fightReadResourceID(0x842, 0x184F3400) == 0) fightFreeResourceID(0x842, 0x184F3400);
    } else if (fightReadResourceID(0x842, 0x195F3400) == 0) {
        fightFreeResourceID(0x842, 0x195F3400);
    }
    GSfloorGetCurrent();
    menuCB_FlashEnd(_flashBackFlag);
    if (_menuCB_Temp != 0) GSmemFree(_menuCB_Temp);
    _menuCB_Temp = 0;
    menuCB_SAVEDATA_recover();
    toolBattleTempSaveData = memcardMemFreeForSavedata(toolBattleTempSaveData);
    menuCBBios_CurrentlyWorkingToolBattleSet(0);
    GSfsysFree(0x14);
    GSresFreeGroup(0x14);
    GSfsysFree(0x88C);
    GSresFreeGroup(0x88C);
}

extern "C" void menuColosseumBattleInit(void) {
    if (toolBattleTempSaveData == 0) {
        CB(s32, 0x9C80) = 0;
        menuCBBios_CurrentlyWorkingToolBattleSet(1);
        GSflagSet(0x30D, 0);
        if (GSflagGet(0x3C4) >= flag_etc->reliveOpenFlag) CB(s8, 0xB4A0) = 1;
        else CB(s8, 0xB4A0) = 0;
        if (CB(s32, 4) == 1) fightReadResourceID(0x842, 0x184F3400);
        else fightReadResourceID(0x842, 0x195F3400);
        GSfsysReadWait(0x88C);
        GSfsysReadWait(0x14);
        _menuCB_Temp = (u8*)GSmemAllocAlign(0xF0C0, 0x20);
        menuCBBios_RuleConstRuleSet();
        toolBattleTempSaveData = memcardMemAllocForSavedata();
        memcpy(toolBattleTempSaveData, savedataGetStatus(0, 0), 0x27FD0);
        toolentryDebugPokemonCreate();
        menuCBBios_InitContext(&_CB);
        menuCBBios_ContextIsLocked(0);
    }
}

extern "C" void menuColosseumBattle(s32 mode) {
    menuCBBios_UnlockContext();
    CB(s32, 4) = mode;
    for (s32 i = 0; i < 2; i++) {
        u8* p = (u8*)&_CB + i * 0x40;
        *(s32*)(p + 0xB054) = 0;
        *(s32*)(p + 0xAFD4) = 0;
        *(s32*)(p + 0xB058) = 0;
        *(s32*)(p + 0xAFD8) = 0;
        *(s32*)(p + 0xB05C) = 0;
        *(s32*)(p + 0xAFDC) = 0;
        *(s32*)(p + 0xB060) = 0;
        *(s32*)(p + 0xAFE0) = 0;
        *(s32*)(p + 0xB064) = 0;
        *(s32*)(p + 0xAFE4) = 0;
        *(s32*)(p + 0xB068) = 0;
        *(s32*)(p + 0xAFE8) = 0;
        *(s32*)(p + 0xB06C) = 0;
        *(s32*)(p + 0xAFEC) = 0;
        *(s32*)(p + 0xB070) = 0;
        *(s32*)(p + 0xAFF0) = 0;
        p += 0x20;
        *(s32*)(p + 0xB054) = 0;
        *(s32*)(p + 0xAFD4) = 0;
        *(s32*)(p + 0xB058) = 0;
        *(s32*)(p + 0xAFD8) = 0;
        *(s32*)(p + 0xB05C) = 0;
        *(s32*)(p + 0xAFDC) = 0;
        *(s32*)(p + 0xB060) = 0;
        *(s32*)(p + 0xAFE0) = 0;
        *(s32*)(p + 0xB064) = 0;
        *(s32*)(p + 0xAFE4) = 0;
        *(s32*)(p + 0xB068) = 0;
        *(s32*)(p + 0xAFE8) = 0;
        *(s32*)(p + 0xB06C) = 0;
        *(s32*)(p + 0xAFEC) = 0;
        *(s32*)(p + 0xB070) = 0;
        *(s32*)(p + 0xAFF0) = 0;
    }
    for (s32 i = 0; i < 6; i++) {
        u8* p = (u8*)&_CB + i * 0x20;
        for (s32 o = 0xB0D4; o <= 0xB0F0; o += 4) *(s32*)(p + o) = 0;
    }
    for (s32 i = 0; i < 2; i++) {
        u8* p = (u8*)&_CB + i * 0x20;
        for (s32 o = 0xB194; o <= 0xB1B0; o += 4) *(s32*)(p + o) = 0;
    }
    _flashBackFlag = 1;
    GSfloorPush(0x395);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
}
