// Written from the asm; built with -inline noauto (see configure.py).
// Called only from REL code: keep the functions alive for the linker.
#pragma force_active on
#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct ToolBattleCB {
    s32 result;           // 0x0
    s32 mode;             // 0x4
    s32 kind;             // 0x8
    u8 pad0C[0xAFFC - 0xC];
    s32 afFC;             // 0xAFFC
    u8 padB000[0xB140 - 0xB000];
    s32 flashB140;        // 0xB140
    u8 padB144[0xB170 - 0xB144];
    s32 flashB170;        // 0xB170
    s32 flashB174;        // 0xB174
    s32 flashB178;        // 0xB178
    u8 padB17C[8];
    s32 battleActive;     // 0xB184
    u8 padB188[0xB19C - 0xB188];
    s32 disconnected;     // 0xB19C
    u8 padB1A0[0xB1E4 - 0xB1A0];
    s16 timer;            // 0xB1E4
    u8 padB1E6[0xB5F8 - 0xB1E6];
};

struct KeyInfo {
    u16 pad0;
    u16 pad2;
    u16 trg;
};

extern "C" {
extern ToolBattleCB _CB;

void FlashSystemSetNowFrameLabel(u32 id, const char* label);
void FlashSystemSetPlayFrameLabel(u32 id, const char* from, const char* to);
void FlashSystemSetLoopFlag(u32 id, s32 loop);
bool FlashSystemIsLastFrame(u32 id);
void GSthreadSwitch(void);
bool GSfloorIsFloorPushed(void);
u8 GSfloorPop(void);
void GSfsysFree(u32 id);
s32 GSfsysReadWait(u32 id);
void GSresFreeGroup(u32 grp);
u16 fightGetFightResultId(void);
u8 fightReadResourceID(s32 a, s32 b);
void fightFreeResourceID(s32 a, s32 b);
void menuCBBattleEndSetPokemonHP(void);
void menuCBBattleStartInit(ToolBattleCB* cb, s32 flag);
void menuCBBattleStartTrainerFaceFree(void);
void menuCBBattleStartTrainerLoadTex(void);
void menuCBBios_CurrentlyWorkingToolBattleSet(s32 on);
void menuCBPokemonEntryLoadTex(void);
void menuCBPokemonEntryPokemonFaceFree(void);
s32 menuCB_Battle(ToolBattleCB* cb);
bool menuCB_BattleBA_PokemonEntryNum(void);
s32 menuCB_BattleResult(ToolBattleCB* cb);
void menuCB_GBADisconnectedErrorJob(void);
s32 menuCB_InitBattle(ToolBattleCB* cb);
s32 menuCB_MenuRollback(s32 id);
s32 menuCB_PokemonEntry(ToolBattleCB* cb);
void menuCB_SE_Play(s32 id);
void menuCBpokemonFaceReadWait(void);
void menuCBtrainerFaceReadWait(void);
void menuCloseCustom(s32 menuID, s32 a, s32 b);
bool menuIsCheck(s32 menuID);
s32 menuOpen(s32 menuID, s32 a);
bool pauseIsPause(void);
void* savedataGetStatus(void* save, s32 kind);
void toolentryCopyHero(void);
bool winSeqCheckMove(s32 menuID);
KeyInfo* windowGetKeyInfo(void);
}

static void _menuCB_FlashEnd_WINLOSE() {
    if (menuIsCheck(0x110)) {
        menuCloseCustom(0x110, 0, 0);
    }
}

static void _menuCB_FlashStart_WINLOSE() {
    switch (fightGetFightResultId()) {
    case 5:
    case 2:
        FlashSystemSetPlayFrameLabel(0x21543000, "winlose_start", "winlose_stop");
        FlashSystemSetNowFrameLabel(0x21543000, "winlose_start");
        break;
    case 3:
    case 4:
        FlashSystemSetPlayFrameLabel(0x21543000, "losewin_start", "losewin_stop");
        FlashSystemSetNowFrameLabel(0x21543000, "losewin_start");
        break;
    case 6:
    case 7:
    default:
        FlashSystemSetPlayFrameLabel(0x21543000, "draw_start", "draw_stop");
        FlashSystemSetNowFrameLabel(0x21543000, "draw_start");
        break;
    }
    FlashSystemSetLoopFlag(0x21543000, 0);
    _CB.flashB178 = 1;
    menuOpen(0x110, 0);
    menuCB_SE_Play(0x5E0);
    do {
        do {
            GSthreadSwitch();
        } while (!FlashSystemIsLastFrame(0x21543000));
        if (!pauseIsPause()) {
            _CB.timer--;
        }
    } while (_CB.timer != 0 && (windowGetKeyInfo()->trg & 0x20) == 0);
}

static void _menuCB_FlashEnd_VS(bool open) {
    if (open) {
        menuOpen(0x113, 0);
        do {
            GSthreadSwitch();
        } while (winSeqCheckMove(0x113));
    } else {
        _CB.flashB174 = 1;
    }
}

static void _menuCB_FlashStart_VS(bool start) {
    if (start) {
        FlashSystemSetPlayFrameLabel(0x21533000, "start", "end_keep");
        FlashSystemSetNowFrameLabel(0x21533000, "start");
    } else {
        FlashSystemSetPlayFrameLabel(0x21533000, "end_keep", "end_keep");
        FlashSystemSetNowFrameLabel(0x21533000, "end_keep");
    }
    _CB.flashB170 = 1;
    _CB.flashB174 = 0;
}

static void _menuCB_FlashEnd() {
    if (menuIsCheck(0x105)) {
        menuCloseCustom(0x105, 0, 0);
    }
}

static void _menuCB_FlashStart(bool start) {
    if (start) {
        FlashSystemSetPlayFrameLabel(0x20093000, "start", "end");
        FlashSystemSetNowFrameLabel(0x20093000, "start");
    } else {
        FlashSystemSetPlayFrameLabel(0x20093000, "end", "end");
        FlashSystemSetNowFrameLabel(0x20093000, "end");
    }
    _CB.flashB140 = 1;
    menuOpen(0x105, 0);
    do {
        GSthreadSwitch();
    } while (!FlashSystemIsLastFrame(0x20093000));
}

extern "C" {

void menuToolBattleExit(void) {
    if (_CB.mode == 1) {
        if (fightReadResourceID(0x842, 0x184F3400) == 0) {
            fightFreeResourceID(0x842, 0x184F3400);
        }
    } else if (fightReadResourceID(0x842, 0x195F3400) == 0) {
        fightFreeResourceID(0x842, 0x195F3400);
    }
    GSfsysFree(0x14);
    GSresFreeGroup(0x14);
}

void menuToolBattleMain(void) {
    u8 loop = 1;
    s32 res;
    u8 saved;
    u8* status;

    _menuCB_FlashStart(true);
    status = (u8*)savedataGetStatus(0, 2);
    saved = status[0x959];
    status[0x959] = 0;
    while (loop) {
        menuCBBios_CurrentlyWorkingToolBattleSet(1);
        menuCBBattleStartInit(&_CB, 0);
        _CB.disconnected = 0;
        _CB.timer = 0xF;
        menuCBPokemonEntryPokemonFaceFree();
        menuCBPokemonEntryLoadTex();
        menuCBpokemonFaceReadWait();
        menuCBBattleStartTrainerFaceFree();
        menuCBBattleStartTrainerLoadTex();
        menuCBtrainerFaceReadWait();
        if (_CB.kind == 2) {
            menuOpen(0xB1, 0);
            _menuCB_FlashStart_VS(true);
            menuOpen(0x103, 0);
            menuOpen(0xB2, 1);
            _menuCB_FlashEnd_VS(false);
            menuCloseCustom(0xB2, 0, 0);
            menuCloseCustom(0x103, 0, 0);
            menuCloseCustom(0xB1, 0, 1);
        } else if (menuCB_BattleBA_PokemonEntryNum()) {
            menuOpen(0xB1, 0);
            _menuCB_FlashStart_VS(true);
            menuOpen(0x103, 0);
            menuOpen(0xB3, 1);
            _menuCB_FlashEnd_VS(false);
            menuCloseCustom(0xB3, 0, 0);
            menuCloseCustom(0x103, 0, 0);
            menuCloseCustom(0xB1, 0, 1);
        } else {
            menuOpen(0xB1, 0);
            _menuCB_FlashStart_VS(true);
            menuOpen(0x103, 0);
            menuOpen(0xB4, 1);
            if (_CB.mode != 1) {
                _menuCB_FlashEnd_VS(false);
                menuCloseCustom(0xB4, 0, 0);
                menuCloseCustom(0x103, 0, 0);
                menuCloseCustom(0xB1, 0, 1);
            }
        }
        if (_CB.disconnected != 0) {
            menuCB_GBADisconnectedErrorJob();
            menuCB_MenuRollback(0xA9);
            break;
        }
        if (_CB.mode == 1) {
            res = 0;
        } else {
            res = menuCB_PokemonEntry(&_CB);
        }
        switch (res) {
        case 0xA9:
            menuCB_MenuRollback(res);
            goto done;
        case 0xB1:
        default:
            break;
        }
        GSfsysFree(0x14);
        GSresFreeGroup(0x14);
        _CB.battleActive = 1;
        _CB.result = menuCB_Battle(&_CB);
        _CB.battleActive = 0;
        _menuCB_FlashStart(false);
        menuCBBattleEndSetPokemonHP();
        menuCBBattleStartInit(&_CB, 1);
        _CB.disconnected = 0;
        _CB.timer = 0xB4;
        menuCBPokemonEntryPokemonFaceFree();
        menuCBPokemonEntryLoadTex();
        menuCBpokemonFaceReadWait();
        menuCBBattleStartTrainerFaceFree();
        menuCBBattleStartTrainerLoadTex();
        menuCBtrainerFaceReadWait();
        menuCB_SE_Play(0x14);
        if (_CB.kind == 2) {
            menuOpen(0xB1, 0);
            _menuCB_FlashStart_VS(false);
            menuOpen(0x103, 0);
            menuOpen(0xB2, 1);
            _menuCB_FlashStart_WINLOSE();
            res = menuCB_BattleResult(&_CB);
            _menuCB_FlashEnd_VS(true);
            _menuCB_FlashEnd_WINLOSE();
            if (res != 0xB1) {
                _menuCB_FlashEnd();
            }
            menuCloseCustom(0xB2, 0, 0);
            menuCloseCustom(0x103, 0, 0);
            menuCloseCustom(0xB1, 0, 1);
        } else if (menuCB_BattleBA_PokemonEntryNum()) {
            menuOpen(0xB1, 0);
            _menuCB_FlashStart_VS(false);
            menuOpen(0x103, 0);
            menuOpen(0xB3, 1);
            _menuCB_FlashStart_WINLOSE();
            res = menuCB_BattleResult(&_CB);
            _menuCB_FlashEnd_VS(true);
            _menuCB_FlashEnd_WINLOSE();
            if (res != 0xB1) {
                _menuCB_FlashEnd();
            }
            menuCloseCustom(0xB3, 0, 0);
            menuCloseCustom(0x103, 0, 0);
            menuCloseCustom(0xB1, 0, 1);
        } else {
            menuOpen(0xB1, 0);
            _menuCB_FlashStart_VS(false);
            menuOpen(0x103, 0);
            menuOpen(0xB4, 1);
            _menuCB_FlashStart_WINLOSE();
            res = menuCB_BattleResult(&_CB);
            _menuCB_FlashEnd_VS(true);
            _menuCB_FlashEnd_WINLOSE();
            if (res != 0xB1) {
                _menuCB_FlashEnd();
            }
            menuCloseCustom(0xB4, 0, 0);
            menuCloseCustom(0x103, 0, 0);
            menuCloseCustom(0xB1, 0, 1);
        }
        if (res == 0xB1 || res == 0xAC) {
            if (_CB.mode != 1) {
                if (_CB.afFC == 6) {
                    menuCB_InitBattle(&_CB);
                }
            } else {
                menuCB_InitBattle(&_CB);
            }
            if (_CB.disconnected != 0) {
                menuCB_GBADisconnectedErrorJob();
                menuCB_MenuRollback(0xA9);
                break;
            }
        }
        switch (res) {
        case 0xB1:
            toolentryCopyHero();
            break;
        default:
        case 0xAC:
        case 0xA9:
        case -1:
            menuCB_MenuRollback(res);
            loop = 0;
            break;
        }
    }
done:
    _menuCB_FlashEnd();
    menuCBBattleStartTrainerFaceFree();
    ((u8*)savedataGetStatus(0, 2))[0x959] = saved;
    if (GSfloorIsFloorPushed()) {
        GSfloorPop();
    } else {
        GSfloorPop();
    }
}

void menuToolBattleInit(void) {
    if (_CB.mode == 1) {
        fightReadResourceID(0x842, 0x184F3400);
    } else {
        fightReadResourceID(0x842, 0x195F3400);
    }
    GSfsysReadWait(0x14);
}

}
