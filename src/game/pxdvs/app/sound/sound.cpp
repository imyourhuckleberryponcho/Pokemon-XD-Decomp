#include <dolphin/types.h>

#pragma pool_strings off

struct SndData {
    u8 unk0[2];
    u8 flags;
    u8 unk3[9];
};

struct SndWaveData {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
};

struct SndPos {
    f32 x;
    f32 y;
    f32 z;
};

extern "C" {

extern u32 snd_data;
extern u32* snd_data_number;
extern SndWaveData* snd_wave_data;
extern u32* snd_wave_data_number;

s32 GSfsysReadWait(u32 id);
f32 GSgfxVideoGetLastRenderTime(void);
u8 GSgfxVideoGetVsyncRate(void);
void GSlogWrite(const char*, ...);
u8 GSsndCheckEnv(u32 id);
u8 GSsndCheckSE(u32 id);
u8 GSsndCheckStream(u32 id);
s32 GSsndClose(u32 id);
u8 GSsndContinue(u32 id, s32 time, s32 vol);
u32 GSsndCreateEmitter(u32 id, SndPos* pos);
u32 GSsndCreateListener(SndPos* pos);
s32 GSsndGetStatus(u32 id);
u8 GSsndGetVolume(u32 id);
u8 GSsndOpenWaveDVD(u32 wave, u32 fileId, u32 heap, u32 a, u32 b, u32 c, u32 e);
u8 GSsndPause(u32 id, s32 time, s32 vol);
s32 GSsndPlayVolume(u32 id, s32 time, s32 vol, u32 flag);
u8 GSsndSetOriginalVolume(u32 id, s32 time, s32 vol);
u8 GSsndStop(u32 id, s32 time, u32 unused);
void GSthreadSwitch(void);

}

static u32 soundPlayEnvID;
static u32 soundPlayID;

extern "C" {

static u8 _soundCheckActive(u32 id);
static void _soundCloseFastFadeout(u32 id);
static void _soundFadeout(u32 time, s32 bgm, s32 wait);
static s32 _soundOpenPlay(u32 id, s32 time, s32 vol, s32 bgm);
static void _soundWait(u32 ms);

u8 soundCheckEnv(u32 id) {
    return GSsndCheckEnv(id);
}

u32 soundGetEnvID(void) {
    return soundPlayEnvID;
}

u32 soundGetBGMID(void) {
    return soundPlayID;
}

void soundPlayWait(u32 id);

s32 soundPlayME(u32 id, s32 time, s32 vol) {
    if (id == 0 || id >= *snd_data_number) {
        return 0;
    }
    GSsndPlayVolume(id, time, vol, 0);
    soundPlayWait(id);
    GSsndClose(id);
    return 1;
}

void soundPlayWait(u32 id) {
    while (1) {
        if (GSsndGetStatus(id) != 2) {
            break;
        }
        GSthreadSwitch();
    }
}

void soundContinueBGMEX(u32 id, u32 ms, u8 wait) {
    if (id != -1U) {
        GSsndContinue(id, ms, 0);
        if (wait == 1) {
            _soundWait(ms);
        }
    }
}

u32 soundPauseBGMEX(u32 ms, u8 wait) {
    u32 id = soundGetBGMID();
    if (id != -1U) {
        GSsndPause(id, ms, 0);
        if (wait == 1) {
            _soundWait(ms);
        }
    }
    return id;
}

void soundOpenWave(u32 index) {
    if (*snd_wave_data_number > index) {
        SndWaveData* w = &snd_wave_data[index];
        GSsndOpenWaveDVD(index, w->unk14, 0, w->unk4, w->unk8, w->unkC, w->unk10);
    }
}

s32 soundOpenPlayME(u32 id, s32 time, s32 vol) {
    u32 bgm = soundPauseBGMEX(0x32, 1);
    s32 result = soundPlayME(id, time, vol);
    soundContinueBGMEX(bgm, 0x1F4, 1);
    return result;
}

u8 soundGetVolume(u32 id) {
    return GSsndGetVolume(id);
}

void soundSetVolumeID(u32 id, s32 time, s32 vol);

void soundSetVolume(s32 vol, s32 time) {
    soundSetVolumeID(soundGetBGMID(), time, vol);
}

void soundSetVolumeID(u32 id, s32 time, s32 vol) {
    GSsndSetOriginalVolume(id, time, vol);
}

u32 soundCreateListener(void) {
    SndPos pos;
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
    u32 r = GSsndCreateListener(&pos);
    return (r | -r) >> 31;
}

u32 soundCreateEmitter(u32 id, f32 x, f32 y, f32 z) {
    SndPos pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    u32 r = GSsndCreateEmitter(id, &pos);
    return (r | -r) >> 31;
}

s32 soundStop(u32 id, u32 time);

void soundStopEnv(u32 time) {
    soundStop(soundPlayEnvID, time);
}

s32 soundStop(u32 id, u32 time) {
    s32 bgm;
    if (id == 0 || id >= *snd_data_number) {
        return 0;
    }
    bgm = 0;
    if (soundPlayID == id) {
        bgm = 1;
        soundPlayID = 0;
    }
    if (soundPlayEnvID == id) {
        bgm = 0;
        soundPlayEnvID = 0;
    }
    if (GSsndCheckStream(id) == 1) {
        if (GSsndCheckSE(id) == 0) {
            _soundFadeout(time, bgm, 1);
        }
        return GSsndClose(id);
    }
    if (GSsndCheckSE(id) == 0) {
        _soundFadeout(time, bgm, 1);
        if (bgm != 0) {
            GSlogWrite("soundStop: Warning! BGM cannot be stopped.(snd_id=%d)\n", id);
            return _soundOpenPlay(8, 0, 0xFF, bgm);
        }
        return GSsndClose(id);
    }
    GSsndStop(id, time, 0);
    return GSsndClose(id);
}

s32 soundOpenPlayEnvFadeOutIn(u32 id, u32 time, s32 vol, s32 pri) {
    if (id == 0 || id >= *snd_data_number) {
        return 0;
    }
    _soundFadeout(time, 0, 1);
    return _soundOpenPlay(id, vol, pri, 0);
}

s32 soundOpenPlayFadeOutIn(u32 id, u32 time, s32 vol, s32 pri) {
    if (id == 0 || id >= *snd_data_number) {
        return 0;
    }
    _soundFadeout(time, 1, 1);
    return _soundOpenPlay(id, vol, pri, 1);
}

s32 soundOpenPlayEnv(u32 id, s32 vol, s32 pri) {
    return _soundOpenPlay(id, vol, pri, 0);
}

s32 soundOpenPlay(u32 id, s32 vol, s32 pri) {
    return _soundOpenPlay(id, vol, pri, 1);
}

static s32 _soundOpenPlay(u32 id, s32 time, s32 vol, s32 bgm) {
    if (id == 0 || id >= *snd_data_number) {
        return 0;
    }
    if (bgm == 0) {
        if (soundPlayEnvID != -1U) {
            _soundCloseFastFadeout(soundPlayEnvID);
        }
        soundPlayEnvID = id;
    } else if ((((u32) * (u8*)(snd_data + id * 0xC + 2) >> 5) & 1) != 1) {
        if (soundPlayID != id && soundPlayID != -1U) {
            _soundCloseFastFadeout(soundPlayID);
        }
        soundPlayID = id;
    }
    return GSsndPlayVolume(id, time, vol, 0);
}

static void _soundFadeout(u32 time, s32 bgm, s32 wait) {
    u32 id;
    if (bgm != 0) {
        id = soundGetBGMID();
    } else {
        id = soundGetEnvID();
    }
    if (id != -1U && _soundCheckActive(id) == 1) {
        GSsndSetOriginalVolume(id, time, 0);
        if (wait != 0) {
            _soundWait(time);
        }
    }
}

static void _soundCloseFastFadeout(u32 id) {
    if (_soundCheckActive(id) == 1) {
        GSsndSetOriginalVolume(id, 0x32, 0);
        _soundWait(0x32);
        GSsndClose(id);
    }
}

static u8 _soundCheckActive(u32 id) {
    s32 status = GSsndGetStatus(id);
    if (status != 0 && status >= 0 && status < 4) {
        return 1;
    }
    return 0;
}

static void _soundWait(u32 ms) {
    f32 limit = (f32)ms / 1000.0f;
    f32 elapsed = 0.0f;
    while (elapsed < limit) {
        GSthreadSwitch();
        elapsed += GSgfxVideoGetLastRenderTime() / GSgfxVideoGetVsyncRate();
    }
}

void soundInitBGM(void) {
    GSfsysReadWait(0x99);
}

void soundInit(void) {
    soundPlayID = 0;
    soundPlayEnvID = 0;
}

}
