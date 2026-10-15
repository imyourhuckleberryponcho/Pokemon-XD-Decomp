#include <dolphin/types.h>

// Debug menu units were built without the peephole optimizer.
#pragma peephole off

struct WazaData {
    u8 unk0[0x38];
};

extern "C" {

WazaData* wazaDataBiosGetPtr(u16 id);
s32 menuOpenCustom(s32 menuID, ...);
void menuCloseCustom(s32 menuID, s32, s32);
s32 menuOpen(s32 menuID, s32);
s32 menuGetCursorItemID(s32 menuID);
s32 wazaGetStatus(void* p, u16 id, u16 kind, u16 index);
s32 wazaSetStatus(void* p, u16 id, u16 kind, u16 index, s32 value);
s32 dbgMenuFightGetWazaTypeId(u8 type);
s8 menuSubOpenYesNo(s32, s32, s32, bool);

s32 dbgMenuFightWazaEditSub(u16 id) {
    WazaData* waza;
    WazaData backup;
    s32 type;
    s8 answer;

    if (id == 0) {
        return 1;
    }
    if (id >= 0x163) {
        return 1;
    }
    waza = wazaDataBiosGetPtr(id);
    backup = *waza;
    for (;;) {
        s32 result = menuOpenCustom(0x20, 0, 0, 0, 1, 1, id);
        if (result == -1) {
            menuCloseCustom(0x20, 0, 1);
            *waza = backup;
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x20)) {
        case 0x89:
            type = dbgMenuFightGetWazaTypeId(wazaGetStatus(0, id, 0x1A, 0));
            if (type >= 0) {
                wazaSetStatus(0, id, 0x1A, 0, type);
            }
            break;
        case 0x8A:
            type = dbgMenuFightGetWazaTypeId(wazaGetStatus(0, id, 0x1A, 1));
            if (type >= 0) {
                wazaSetStatus(0, id, 0x1A, 1, type);
            }
            break;
        case 0x8B:
            type = dbgMenuFightGetWazaTypeId(wazaGetStatus(0, id, 0x1A, 2));
            if (type >= 0) {
                wazaSetStatus(0, id, 0x1A, 2, type);
            }
            break;
        case 0x8C:
            answer = menuSubOpenYesNo(0x7F, -1, -1, wazaGetStatus(0, id, 0x1B, 0) == 0);
            if (answer == 0) {
                wazaSetStatus(0, id, 0x1B, 0, 1);
            } else if (answer == 1) {
                wazaSetStatus(0, id, 0x1B, 0, 0);
            }
            break;
        }
    }
    menuCloseCustom(0x20, 0, 1);
    return 1;
}

}
