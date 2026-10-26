#include <dolphin/types.h>

static u8 _menuMainExec;

extern "C" {

void menuColosseumBattleConnectionExit(void) {}

BOOL menuColosseumBattleConnectionMain(void) {
    u8 prev = _menuMainExec;
    _menuMainExec = TRUE;
    return 1 - prev;
}

void menuColosseumBattleConnectionInit(void) { _menuMainExec = FALSE; }

}
