#include <dolphin/types.h>

#pragma peephole off

struct _MENUCBWORK {
    u8 unk0[8];
    s32 unk8;
};

struct CBResult {
    u8 unk0[0xAFE0];
    s32 selection;
    u8 unkAFE4[0x7C];
    s32 unkB060;
    u8 unkB064[0xB5F8 - 0xB064];
};

extern "C" {
extern CBResult _CB;
extern s32 menuCBBattleStartResID;

s32 toolentryTaisenGetBattleMode(void);
s32 toolentryTaisenGetBattleType(void);
s32 toolentryTaisenGetHomePlace(s32 player);
s32 toolentryTaisenGetControlerType(s32 player);
s32 toolentryTaisenGetEntryPlayerNum(void);
void toolentryCopyHero(void);
s32 fightGetFightResultId(void);
void menuSetEnablePort(s32);
void msgctrlSetValue(s32, s32);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s32 pokecoloGetCountryCode(void);
s32 menuSubOpenSelect_gba(u8 selection, s32* values, s32 a2, s32 x, s32 y, s32 flags, s32 a6, u8 a7, u8 a8);
s32 menuSubOpenSelect3(u8 selection, s32* values, s32 a2, s32 x, s32 y, s32 flags, s32 a6, u8 a7, u8 a8);
u8 GSinputIsConnected(s32);
s32 GSinputGetSubType(s32);
void GSthreadSwitch(void);
bool gbaCommandIsConnected(s32);
}

static s32 _menuCB_BattleResultTonikaku(_MENUCBWORK* work);
static s32 _menuCB_BattleResultTaisen(_MENUCBWORK* work);
static u16 _menuCB_BattleResultGetHomePlace(void);
static s32 _menuCBResultGetHomePlace(void);
static void _menuCBResultCheckController1(void);
static u8 _menuCBResultCheckController1sub(void);
static s32 _menuCBResultCheckGBAPort(void);

static s32 submenu_msg2[3] = {0x4300, 0x4302, 0x4303};
static s32 submenu_msg3[4] = {0x4300, 0x4301, 0x4302, 0x4303};
static s32 submenu_msg1[2] = {0x4300, 0x4303};

extern "C" s32 menuCB_BattleResult(_MENUCBWORK* work) {
    switch (toolentryTaisenGetBattleMode()) {
    case 1:
        return _menuCB_BattleResultTonikaku(work);
    case 0:
    default:
        return _menuCB_BattleResultTaisen(work);
    }
}

static s32 _menuCB_BattleResultTaisen(_MENUCBWORK* work) {
    static s32 msgA[3] = {0x4300, 0x4301, 0x4303};
    static s32 msgB[2] = {0x4300, 0x4303};
    s32 v = -1;
    s32 result = fightGetFightResultId();
    s32 state;
    u8 done = 0;
    s32 busy;
    s32 ret;
    s32 place;
    menuSetEnablePort(0);
    for (;;) {
        switch ((u16)result) {
        case 1:
            menuSetEnablePort(1);
            if (_menuCB_BattleResultGetHomePlace() == 0) {
                s32 port = _menuCBResultCheckGBAPort();
                msgctrlSetValue(0x2F, port);
                winMsgOpen(2, 0x442B, 1, 1);
                winMsgClose(1);
                done = 1;
            } else {
                _menuCBResultCheckGBAPort();
                winMsgOpen(2, 0x442D, 1, 1);
                _menuCBResultCheckController1();
                winMsgClose(1);
                done = 1;
            }
            break;
        }
        if (done) {
            return 0xA9;
        }
        _CB.selection = 0;
        _CB.unkB060 = 0;
        menuSetEnablePort(1);
        winMsgOpen(2, 0x42FF, 1, 1);
        if (work->unk8 != 2) {
            switch (pokecoloGetCountryCode()) {
            case 0:
                _CB.selection = menuSubOpenSelect_gba(0, submenu_msg2, 3, 0x3E, 0x89, 0, 3, 1, 1);
                break;
            case 1:
            case 2:
                _CB.selection = menuSubOpenSelect_gba(0, msgB, 2, 0x3E, 0x89, 0, 2, 1, 1);
                break;
            }
            if (_CB.selection == -2) {
                result = 1;
                continue;
            }
            if (_CB.selection == -1) {
                _CB.selection = 2;
            }
            switch (pokecoloGetCountryCode()) {
            case 0:
                switch (_CB.selection) {
                case 0:
                    v = 0;
                    break;
                case 1:
                    v = 2;
                    break;
                case 2:
                    v = -1;
                    break;
                }
                break;
            case 1:
            case 2:
                switch (_CB.selection) {
                case 0:
                    v = 0;
                    break;
                case 1:
                default:
                    v = -1;
                    break;
                }
                break;
            }
        } else {
            switch (pokecoloGetCountryCode()) {
            case 0:
                _CB.selection = menuSubOpenSelect_gba(0, submenu_msg3, 4, 0x3E, 0x89, 0, 4, 1, 1);
                break;
            case 1:
            case 2:
                _CB.selection = menuSubOpenSelect_gba(0, msgA, 3, 0x3E, 0x89, 0, 3, 1, 1);
                break;
            }
            if (_CB.selection == -2) {
                result = 1;
                continue;
            }
            if (_CB.selection == -1) {
                _CB.selection = 3;
            }
            switch (pokecoloGetCountryCode()) {
            case 0:
                switch (_CB.selection) {
                case 0:
                    v = 0;
                    break;
                case 1:
                    v = 1;
                    break;
                case 2:
                    v = 2;
                    break;
                case 3:
                default:
                    v = -1;
                    break;
                }
                break;
            case 1:
            case 2:
                switch (_CB.selection) {
                case 0:
                    v = 0;
                    break;
                case 1:
                    v = 1;
                    break;
                case 2:
                default:
                    v = -1;
                    break;
                }
                break;
            }
        }
        switch (v) {
        case 0:
            ret = 0xB1;
            break;
        case 1:
            ret = 0xAC;
            break;
        case 2:
            ret = 0xA9;
            break;
        case -1:
        default:
            ret = -1;
            break;
        }
        winMsgClose(1);
        if (ret == -1 || ret == 0xA9) {
            state = 0;
            busy = 1;
            place = (u16)_menuCBResultGetHomePlace();
            do {
                switch (state) {
                case 0:
                    if (place == 0) {
                        state = 1;
                    } else {
                        state = 2;
                    }
                    break;
                case 1:
                    winMsgOpen(2, 0x442C, 1, 1);
                    winMsgClose(1);
                    state = 4;
                    break;
                case 2:
                    winMsgOpen(2, 0x442D, 1, 1);
                    _menuCBResultCheckController1();
                    winMsgClose(1);
                    if (_menuCBResultCheckController1sub()) {
                        state = 4;
                    } else {
                        state = 3;
                    }
                    break;
                case 3:
                    winMsgOpen(2, 0x4436, 1, 1);
                    _menuCBResultCheckController1();
                    winMsgClose(1);
                    state = 4;
                    break;
                case 4:
                    busy = 0;
                    break;
                }
            } while (busy);
        }
        menuCBBattleStartResID = 0;
        return ret;
    }
}

static u16 _menuCB_BattleResultGetHomePlace(void) {
    if (toolentryTaisenGetBattleType() == 2) {
        return (u16)toolentryTaisenGetHomePlace(0) != 0;
    }
    return 0;
}

static s32 _menuCB_BattleResultTonikaku(_MENUCBWORK* work) {
    _CB.selection = 0;
    _CB.unkB060 = 0;
    _CB.selection = menuSubOpenSelect3(0, submenu_msg1, 2, 0x3E, 0x89, 0, 2, 1, 1);
    if (_CB.selection == -1) {
        _CB.selection = 1;
    }
    switch (_CB.selection) {
    case 0:
        toolentryCopyHero();
        return 0xB1;
    case 1:
    default:
        break;
    }
    return -1;
}

static s32 _menuCBResultGetHomePlace(void) {
    if (toolentryTaisenGetBattleType() == 2) {
        return (u16)toolentryTaisenGetHomePlace(0) != 0;
    }
    return 0;
}

static void _menuCBResultCheckController1(void) {
    s32 loop = 1;
    do {
        if (_menuCBResultCheckController1sub()) {
            loop = 0;
        } else {
            GSthreadSwitch();
        }
    } while (loop);
}

static u8 _menuCBResultCheckController1sub(void) {
    if (GSinputIsConnected(1)) {
        return GSinputGetSubType(1) == 0;
    }
    return 0;
}

static s32 _menuCBResultCheckGBAPort(void) {
    s32 num = toolentryTaisenGetEntryPlayerNum();
    s32 home;
    s32 ctrl;
    s32 i;
    toolentryTaisenGetBattleMode();
    for (i = 0; i < num; i++) {
        home = toolentryTaisenGetHomePlace(i);
        ctrl = toolentryTaisenGetControlerType(i);
        if (ctrl != 0 && ((u16)(home - 1) <= 1 || (u16)home == 3) && !gbaCommandIsConnected(ctrl)) {
            return ctrl;
        }
    }
    return 2;
}
