#include <dolphin/types.h>

#pragma optimize_for_size on
#pragma peephole off

extern "C" {
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s8 menuSubOpenYesNoField(void);
void GSfloorChange(s32 floorID);
}

#pragma dont_inline on
static s32 _coutineSave() {
    s32 result;
    s32 state = 0;
    BOOL done = FALSE;
    while (!done) {
        switch (state) {
        case 0:
            winMsgOpen(2, 1, 1, 1);
            result = menuSubOpenYesNoField();
            winMsgClose(1);
            if (result != 0) {
                done = TRUE;
            } else {
                state = 2;
            }
            break;
        case 2:
            break;
        case 3:
            GSfloorChange(0x395);
            state = 4;
            break;
        case 4:
            done = TRUE;
            break;
        }
    }
    return 0;
}
#pragma dont_inline reset

extern "C" {

s32 scriptBattleMountainEnd(void) {
    GSfloorChange(0x395);
    return 0;
}

s32 scriptContinueSave(void) { return _coutineSave(); }

}
