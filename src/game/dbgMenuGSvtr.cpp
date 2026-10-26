#include <dolphin/types.h>

#pragma peephole off

extern "C" {

u32 GSinputButtonsChanged(s32 pad);
u32 GSinputButtonsPressed(s32 pad);
void soundOpenPlay(s32, s32, s32);
void GSgfxCaptureMovieStart(s32 frames);
void GSgfxCaptureMovieStop(void);
void GSgfxCaptureSetTarget(s32 target);
u8 GSvtrGetInfoDisp(void);
void GSvtrSetInfoDisp(u8 disp, u8);
void GSvtrSlowPlay(void);
void GSvtrSingleStep(void);
void GSvtrPause(void);
void GSvtrPlay(void);
bool GSvtrIsActive(void);
void GSvtrEnable(void);
void GSvtrDisable(void);

static u8 _vtrWantCapture;
static u8 _vtrIsCapturing;

void dbgMenuGSvtrCaptureUpdate(void) {
    if (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x10) {
        switch (_vtrIsCapturing) {
        case 0:
            if (_vtrWantCapture) {
                soundOpenPlay(8, 0, 0);
                GSgfxCaptureMovieStart(18000);
                _vtrWantCapture = 0;
                _vtrIsCapturing = 1;
            }
            break;
        case 1:
            GSgfxCaptureMovieStop();
            _vtrIsCapturing = 0;
            break;
        }
    }
}

#pragma force_active on

s32 dbgMenuGSvtrCaptureSD(void) {
    GSgfxCaptureSetTarget(1);
    _vtrWantCapture = 1;
    GSvtrSetInfoDisp(GSvtrGetInfoDisp(), 1);
    return 0;
}

s32 dbgMenuGSvtrCaptureBBA(void) {
    GSgfxCaptureSetTarget(0);
    _vtrWantCapture = 1;
    GSvtrSetInfoDisp(GSvtrGetInfoDisp(), 1);
    return 0;
}

s32 dbgMenuGSvtrSlow(void) {
    GSvtrSlowPlay();
    return 0;
}

s32 dbgMenuGSvtrStep(void) {
    GSvtrSingleStep();
    return 0;
}

s32 dbgMenuGSvtrPause(void) {
    GSvtrPause();
    return 0;
}

s32 dbgMenuGSvtrPlay(void) {
    GSvtrPlay();
    return 0;
}

s32 dbgMenuGSvtrChangeDisp(void) {
    GSvtrSetInfoDisp(!GSvtrGetInfoDisp(), _vtrWantCapture);
    return 0;
}

s32 dbgMenuGSvtrChangeActive(void) {
    if (!GSvtrIsActive()) {
        GSvtrEnable();
    } else {
        GSvtrDisable();
    }
    return 0;
}

#pragma force_active reset

}
