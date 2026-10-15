// NonMatching: Main differs. Target: lbz r3; li r0,1; clrlwi r3,r3,24; stb; subfic r0,r3,1; blr
// (computes 1-old into r0, then returns old). Nothing tried reproduces the dead subfic.
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
