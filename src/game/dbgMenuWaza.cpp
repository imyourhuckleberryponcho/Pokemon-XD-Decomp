#include <dolphin/types.h>

#pragma peephole off

struct WazaViewerData {
    u8 unk0[0x16];
    u8 unk16;
    u8 unk17;
    u8 unk18[0x30 - 0x18];
    s32 unk30;
    u8 unk34[4];
};

extern "C" {

extern WazaViewerData wazaViewerData;

bool menuIsCheck(s32 menuID);
void menuClose(s32 menuID);
void menuOpenCustom(s32 menuID, ...);
void menuSetPosition(s32 menuID, s32 x, s32 y);
void GSfloorPush(s32 floorID);
void GSfloorPop(void);
void GSthreadSwitch(void);

#pragma force_active on

s32 dbgMenuWazaDebugStop(void) {
    if (wazaViewerData.unk30 != 0) {
        GSfloorPop();
    }
    return 0;
}

s32 dbgMenuPokemonDebugSelect(void) {
    if (menuIsCheck(0x26)) {
        menuClose(0x26);
    } else {
        wazaViewerData.unk16 = 0;
        wazaViewerData.unk17 = 0;
        menuOpenCustom(0x26, 0, 0, 0, 1, 0);
        menuSetPosition(0x26, 12, 10);
    }
    return 0;
}

s32 dbgMenuWazaDebugSelect(void) {
    if (menuIsCheck(0x15)) {
        menuClose(0x15);
    } else {
        menuOpenCustom(0x15, 0, 0, 0, 1, 0);
        menuSetPosition(0x15, 12, 10);
    }
    return 0;
}

s32 dbgMenuWazaDebugStart(void) {
    if (menuIsCheck(0x11)) {
        menuClose(0x11);
    }
    if (wazaViewerData.unk30 == 0) {
        GSfloorPush(999);
        GSthreadSwitch();
    }
    return 0;
}

s32 dbgMenuWazaMain(void) { return 1; }

#pragma force_active reset

}
