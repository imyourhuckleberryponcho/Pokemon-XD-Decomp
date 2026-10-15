#include <dolphin/types.h>

extern "C" {

void GSfloorPush(u32 floorID);
void floorSetFadeScript(u32 script, u32 arg);
void floorWaitForChange(void);

static u32 Parameter;

/*
 * --INFO--
 * Address:	802399D4
 * Size:	00003C
 */
void d2presentOpen(u32 param) {
    Parameter = param;
    GSfloorPush(0x16);
    floorSetFadeScript(0x5960009, 0);
    floorWaitForChange();
}

}
