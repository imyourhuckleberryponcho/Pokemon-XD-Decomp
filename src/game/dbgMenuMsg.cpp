#include <dolphin/types.h>

// Debug menu units were built without the peephole optimizer.
#pragma peephole off

extern "C" {

void fadeSet(s32 type, f32 time);
void fadeCheck(s32);
void winMsgOpenError(s32, s32, s32);
void winMsgClose(s32);
void winMsgCloseFight(s32);
void winMsgCloseError(s32);
void winMsgOpenField(s32 msgID, s32, s32);
void winMsgCloseField(s32);
void GSthreadSwitch(void);
void msgctrlSetValue(s32, s32);
u32 GSinputButtonsPressed(s32 pad);
bool menuSubOpenNumberInputDigit(s32, s32* value);
void menuSubKeyWait(void);

// Nothing references these, but the original link kept them.
#pragma force_active on

s32 dbgMenuMsgTest(s32, s32 item) {
    switch (item) {
    case 0:
        fadeSet(3, 0.5f);
        fadeCheck(1);
        winMsgOpenError(1, 1, 0);
        winMsgClose(1);
        fadeSet(2, 0.5f);
        fadeCheck(1);
        break;
    case 1:
        winMsgCloseFight(1);
        winMsgCloseError(1);
        break;
    case 2:
        GSthreadSwitch();
        GSthreadSwitch();
        GSthreadSwitch();
        winMsgCloseFight(0);
        GSthreadSwitch();
        GSthreadSwitch();
        break;
    case 3:
        msgctrlSetValue(0x31, 2010);
        break;
    }
    return 0;
}

s32 dbgMenuMsgCheck(void) {
    if (GSinputButtonsPressed(1) & 0x20) {
        s32 msgID;
        if (!menuSubOpenNumberInputDigit(0, &msgID)) {
            return -1;
        }
        winMsgOpenField(msgID, 1, 0);
        menuSubKeyWait();
        winMsgCloseField(1);
        return 0;
    }
    return 1;
}

#pragma force_active reset

}
