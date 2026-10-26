#include <dolphin/types.h>
#pragma pool_strings off
#pragma peephole off

struct floorsound_dd_ {
    u8 kind;
    u8 volume;
    u16 floorId;
    u16 sndId;
    u16 time;
    u16 envFade;
    u16 flagId;
};

class FloorBgmMask {
public:
    enum BgmMaskMode {
        MODE_NONE = 0,
        MODE_FADEOUT = 1,
        MODE_FADEKEEP = 2,
        MODE_FADEINDELAY = 3,
        MODE_FADEIN = 4
    };

    FloorBgmMask();
    void initialize();
    void finalize();
    void update(f32 dt);
    void endMECallback();
    void startMECallback();
    void stopMask();
    void endMask();
    void startMask();
    void setFadeOutTime(f32 t);
    void setFadeInTime(f32 t);
    void setVolumeRate(f32 rate);
    void changeMode(BgmMaskMode mode);
    u8 isEnable();

    BgmMaskMode mode;
    u8 enable;
    u8 curVolume;
    u8 baseVolume;
    u8 maskVolume;
    u32 bgmId;
    f32 volumeRate;
    f32 fadeInTime;
    f32 fadeOutTime;
    f32 timer;
    f32 keepTime;
};

extern "C" {
u32 soundGetBGMID(void);
u32 soundGetVolume(u32 id);
void soundSetVolumeID(u32 id, u32 time, u32 volume);
void soundOpenPlay(s32, s32, s32);
void soundOpenPlayFadeOutIn(u32 id, u32 fadeOut, u32 fadeIn, u32 volume);
void soundOpenPlayEnvFadeOutIn(u32 id, u32 fadeOut, u32 fadeIn, u32 volume);
u8 soundCheckEnv(u32 id);
u8 GSsndCheckSE(u32 id);
s32 GSsndGetVolume(u32 id);
void GSsndSetVolume(s32 vol, s32 time, u32 a, u32 b);
bool GSflagTest(u32 id);
u32 floorGetCurrent(void);
s32 dbgMenuGetLayerID(void);
void GSprint(s32 layer, s32 x, s32 y, s32 color, const char* fmt, ...);
extern u32* floorsoundTbl_number;
extern floorsound_dd_* floorsoundTbl;
}

static u8 _displaySndFlag;
static u32 _bgmMaskStorage[sizeof(FloorBgmMask) / 4];
#define _bgmMask (*(FloorBgmMask*)_bgmMaskStorage)

static u8 _playEnvSound(floorsound_dd_* e);
static u8 _playSound(floorsound_dd_* e);
extern "C" floorsound_dd_* floorSound_SearchTable(u32 floorId, floorsound_dd_* start);

void FloorBgmMask::update(f32 dt) {
    const char* name = "---";
    bgmId = soundGetBGMID();
    if (bgmId == 0) {
        changeMode(MODE_NONE);
    }
    switch (mode) {
    case MODE_NONE:
        name = "noneMask";
        break;
    case MODE_FADEOUT:
        name = "fadeOut";
        timer -= dt;
        if (timer <= 0.0f) {
            changeMode(MODE_FADEKEEP);
        }
        break;
    case MODE_FADEKEEP:
        name = "fadeKeep";
        break;
    case MODE_FADEINDELAY:
        name = "fadeInDelay";
        timer -= dt;
        if (timer <= 0.0f) {
            soundSetVolumeID(bgmId, (u32)(1000.0f * fadeInTime), baseVolume);
            timer = fadeInTime;
            changeMode(MODE_FADEIN);
        }
        break;
    case MODE_FADEIN:
        name = "fadeIn";
        timer -= dt;
        if (timer <= 0.0f) {
            changeMode(MODE_NONE);
        }
        break;
    }
    if (_displaySndFlag) {
        s32 layer = dbgMenuGetLayerID();
        if (layer != -1) {
            u32 vol = 0;
            if (bgmId != 0) {
                vol = soundGetVolume(bgmId);
            }
            GSprint(layer, 8, 26, -1, "snd_id = %d, curVol %d [%s]", bgmId, vol, name);
        }
    }
}

void FloorBgmMask::endMECallback() {
}

void FloorBgmMask::startMECallback() {
    switch (mode) {
    case MODE_FADEINDELAY:
        soundSetVolumeID(bgmId, (u32)(1000.0f * fadeInTime), baseVolume);
        changeMode(MODE_NONE);
        break;
    }
}

void FloorBgmMask::stopMask() {
    if (isEnable() && mode != MODE_NONE) {
        soundSetVolumeID(bgmId, (u32)(1000.0f * fadeInTime), baseVolume);
        changeMode(MODE_NONE);
    }
}

void FloorBgmMask::endMask() {
    if (isEnable()) {
        timer = keepTime;
        changeMode(MODE_FADEINDELAY);
    }
}

void FloorBgmMask::startMask() {
    if (isEnable()) {
        if (mode == MODE_FADEOUT || mode == MODE_FADEKEEP) {
            return;
        }
        if (mode == MODE_FADEINDELAY) {
            changeMode(MODE_FADEKEEP);
            return;
        }
        if (mode == MODE_NONE) {
            bgmId = soundGetBGMID();
            if (bgmId == 0) {
                return;
            }
            curVolume = 0x7F;
            curVolume = soundGetVolume(bgmId);
            baseVolume = curVolume;
            maskVolume = (u8)(curVolume * volumeRate);
        }
        soundSetVolumeID(bgmId, (u32)(1000.0f * fadeOutTime), maskVolume);
        changeMode(MODE_FADEOUT);
        timer = fadeOutTime;
    }
}

void FloorBgmMask::setFadeOutTime(f32 t) {
    fadeOutTime = t;
}

void FloorBgmMask::setFadeInTime(f32 t) {
    fadeInTime = t;
}

void FloorBgmMask::setVolumeRate(f32 rate) {
    if (rate < 0.0f || rate > 1.0f) {
        return;
    }
    volumeRate = rate;
}

void FloorBgmMask::finalize() {
    fadeInTime = 0.0f;
    stopMask();
    enable = 1;
    mode = MODE_NONE;
    curVolume = 0;
    volumeRate = 0.9f;
    fadeInTime = 0.3f;
    fadeOutTime = 0.3f;
    keepTime = 4.0f;
}

void FloorBgmMask::initialize() {
}

FloorBgmMask::FloorBgmMask() {
    enable = 1;
    mode = MODE_NONE;
    curVolume = 0;
    volumeRate = 0.9f;
    fadeInTime = 0.3f;
    fadeOutTime = 0.3f;
    keepTime = 4.0f;
}

extern "C" {

void* floorSound_getBgmMaskObj(void) {
    return &_bgmMask;
}

u8 floorSound_getDispSoundVolume(void) {
    return _displaySndFlag;
}

void floorSound_setDispSoundVolume(u8 flag) {
    _displaySndFlag = flag;
}

u8 floorSound_playEnvSound(s32 kind) {
    floorsound_dd_* e;
    u32 cur;
    cur = floorGetCurrent();
    for (e = floorSound_SearchTable(cur, 0); e != 0; e = floorSound_SearchTable(cur, e + 1)) {
        if (e->flagId == 0 || GSflagTest(e->flagId)) {
            if (kind == e->kind && _playEnvSound(e)) {
                return 1;
            }
        }
    }
    return 0;
}

u8 floorSound_playSound(void) {
    floorsound_dd_* e;
    u32 cur;
    cur = floorGetCurrent();
    for (e = floorSound_SearchTable(cur, 0); e != 0; e = floorSound_SearchTable(cur, e + 1)) {
        if (e->flagId == 0 || GSflagTest(e->flagId)) {
            if (_playSound(e)) {
                return 1;
            }
        }
    }
    return 0;
}

floorsound_dd_* floorSound_SearchTable(u32 floorId, floorsound_dd_* start) {
    floorsound_dd_* end = floorsoundTbl + *floorsoundTbl_number;
    if (start == 0) {
        start = floorsoundTbl;
    }
    for (; start < end; start++) {
        if (start->floorId == floorId) {
            return start;
        }
    }
    return 0;
}

}

static u8 _playEnvSound(floorsound_dd_* e) {
    if (soundCheckEnv(e->sndId) == 0) {
        return 0;
    }
    soundOpenPlayEnvFadeOutIn(e->sndId, e->envFade, e->time, e->volume);
    return 1;
}

static u8 _playSound(floorsound_dd_* e) {
    if (e == 0) {
        return 0;
    }
    if (soundCheckEnv(e->sndId)) {
        return 0;
    }
    if (GSsndCheckSE(e->sndId)) {
        soundOpenPlay(e->sndId, e->time, e->volume);
    } else if (e->sndId == soundGetBGMID()) {
        if (e->volume != GSsndGetVolume(e->sndId)) {
            GSsndSetVolume(e->volume, 0, 1, 0);
        }
    } else {
        soundOpenPlayFadeOutIn(e->sndId, 500, e->time, e->volume);
    }
    return 1;
}

extern "C" void __ct__12FloorBgmMaskFv(void*);

static void __sinit_floorsound_cpp() {
    __ct__12FloorBgmMaskFv(&_bgmMask);
}

__declspec(section ".ctors") extern void* const __sinit_floorsound_cpp_ctor = (void*)__sinit_floorsound_cpp;

inline void FloorBgmMask::changeMode(BgmMaskMode m) {
    mode = m;
}

inline u8 FloorBgmMask::isEnable() {
    return enable;
}
