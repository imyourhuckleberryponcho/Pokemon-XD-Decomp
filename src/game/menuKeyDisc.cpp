#include <dolphin/types.h>

// Nothing references these, but the original link kept them.
#pragma force_active on

extern "C" {

s32 floorGetCurrentGroupID(void);
void* GSresGetResource(s32 groupID, u32 resID);

void menuKeyDiscExit(void) {}

void* menuKeyDiscMain(void) { return GSresGetResource(floorGetCurrentGroupID(), 0x117F0000); }

void menuKeyDiscInit(void) {}

}
