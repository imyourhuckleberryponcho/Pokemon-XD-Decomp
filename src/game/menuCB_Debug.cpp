#include <dolphin/types.h>

// This unit was built without the peephole optimizer (otherwise the
// srwi + clrlwi pair below gets merged into a single extrwi).
#pragma peephole off

static u8 _DBG = TRUE;

extern "C" {

void menuCBDebug_SkipAGBConnection(bool skip) { _DBG = !skip; }

}
