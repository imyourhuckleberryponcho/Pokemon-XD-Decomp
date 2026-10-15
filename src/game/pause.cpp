#include <dolphin/types.h>

#pragma peephole off

extern "C" {

void GSgfxRenderPause(void);
void GSgfxRenderUnpause(void);
void GSsndPushVolumeALL(s32, s32, s32, s32);
void GSsndPopVolumeALL(s32, s32, s32);
void GSsndPause(u32 id, s32, s32);
void GSsndContinue(u32 id, s32, s32);
void GSgappPauseOn(void);
void GSgappPauseOff(void);
s32 GSgappCreate(s32, s32, s32, void (*func)(u32, u32));
u32 soundGetBGMID(void);
void GSmovieAllPause(void);
void GSmovieAllContinue(void);

}

static bool _pauseFlag;
static bool _enablePauseFlag;
static u32 _sound_id;
static s32 _gappPadReadHandle;

extern "C" {

bool pauseIsPause(void) { return _pauseFlag; }

void pauseOff(void) {
    if (_pauseFlag) {
        _pauseFlag = false;
        GSgfxRenderUnpause();
        GSsndPopVolumeALL(0, 0, 1);
        GSgappPauseOff();
        if (_sound_id != 0xFFFFFFFF) {
            GSsndContinue(_sound_id, 50, 0);
        }
        GSmovieAllContinue();
    }
}

void pauseOn(void) {
    if (!_pauseFlag && _enablePauseFlag) {
        _pauseFlag = true;
        GSgfxRenderPause();
        GSsndPushVolumeALL(0, 0, 0, 1);
        GSgappPauseOn();
        _sound_id = soundGetBGMID();
        if (_sound_id != 0xFFFFFFFF) {
            GSsndPause(_sound_id, 50, 0);
        }
        GSmovieAllPause();
    }
}

}

static void _pauseDaemon(u32, u32) {}

extern "C" {

void pauseInit(void) {
    _pauseFlag = false;
    _enablePauseFlag = true;
    _gappPadReadHandle = GSgappCreate(1, 0, 0, _pauseDaemon);
}

}
