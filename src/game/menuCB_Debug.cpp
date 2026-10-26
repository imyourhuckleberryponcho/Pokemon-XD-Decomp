#include <dolphin/types.h>

#pragma peephole off

static u8 _DBG = TRUE;

extern "C" {

void menuCBDebug_SkipAGBConnection(bool skip) { _DBG = !skip; }

}
