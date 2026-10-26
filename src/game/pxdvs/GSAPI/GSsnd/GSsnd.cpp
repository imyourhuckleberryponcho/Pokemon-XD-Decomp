#include <dolphin/types.h>

#pragma pool_strings off

struct SVec {
    f32 x, y, z;
};

typedef struct {
    void* (*malloc)(u32 size);
    void (*free)(void* ptr);
} SND_HOOKS;

typedef struct {
    u32 flags;
    u32 trackMute[2];
    u16 speed;
    struct {
        u16 time;
        u8 target;
    } volume;
    u8 numSeqVolDef;
    void* seqVolDef;
    u8 numFaded;
    u8* faded;
} SND_PLAYPARA;

struct SndWork {
    u8 used;
    u8 vol;
    u8 pan;
    u8 b3;
    u8 pushCount;
    u8 push[3];
    u32 voice;
    u32 res0;
    u32 res1;
};

struct SndData {
    u8 group : 4;
    u8 reverb : 4;
    u8 b1;
    u8 env : 1;
    u8 stream : 1;
    u8 se : 1;
    u8 f3 : 1;
    u8 open : 1;
    u8 paused : 1;
    u8 f6 : 2;
    u8 b3;
    u16 fxid;
    u16 file;
    SndWork* work;
};

struct SndFile {
    u32 a;
    u32 b;
    u32 c;
};

struct SndWaveData {
    u8 b0;
    u8 loaded;
    u16 gid;
    u32 pad[5];
};

struct SndRevData {
    f32 coloration;
    f32 mix;
    f32 time;
    f32 damping;
    f32 preDelay;
    f32 crosstalk;
};

struct SndStream {
    SndStream* master;
    SndStream* child;
    s32 state;
    u32 stid;
    void* buf;
    u32 bufSize;
    u32 bufBytes;
    u32 x1c;
    u32 x20;
    u32 x24;
    u32 fsysId;
    u32 x2c;
    u32 sndId;
    u16 time;
    u8 mode;
    u8 baseVol;
    u8 vol;
    u8 x39;
    u8 curVol;
    u8 right;
    u8 x3c;
    u8 x3d;
    u8 ready;
    u8 x3f;
    u8 pad40[0x1c];
    s32 x5c;
    u32 x60;
    u32 x64;
    u32 x68;
    u8 pad6c[5];
    u8 x71;
    u8 x72;
    u8 x73;
    u32 x74;
    u32 x78;
    u32 x7c;
    u8 pad80[0x2e];
    u8 xae;
    u8 xaf;
    u32 xb0;
    u32 xb4;
    u32 xb8;
    u32 xbc;
    u8 padc0[0x2e];
    u8 xee;
    u8 xef;
    u32 xf0;
    u32 xf4;
    u32 xf8;
    u32 xfc;
};

struct SndEmitter {
    u8 used;
    u8 maxVol;
    u8 minVol;
    u8 pad3;
    u32 sndId;
    f32 maxDis;
    f32 comp;
    SVec pos;
    SVec dir;
    u8 em[0x50];
};

struct SndListener {
    u8 used;
    u8 vol;
    u8 pad2[2];
    f32 frontSur;
    f32 backSur;
    f32 soundSpeed;
    SVec pos;
    SVec dir;
    SVec heading;
    SVec up;
    u8 li[0x90];
};

struct SndRevH {
    u8 work[0x1c4];
    u8 tempDisableFX;
    u8 pad[3];
    f32 coloration;
    f32 mix;
    f32 time;
    f32 damping;
    f32 preDelay;
    f32 crosstalk;
};

extern "C" {
void* GSmemAllocAlign(u32 size, u32 align);
void GSmemFree(void* p);
void GSlogWrite(const char* fmt, ...);
void* GSgappCreate(u32 a, u32 b, u32 c, void (*fn)());
void GSgappSetName(void* gapp, const char* name);
void GSgappTerminate(void* gapp);
void* GSresGetResource(u32 a, u32 b);
void* GSdvdOpen(u32 id);
void GSdvdClose(void* f);
s32 GSdvdRead(void* f, void* buf, u32 size, u32 offset);
void GSfsysStreamSetLoopFlag(u32 a, u32 b, u8 flag);
void GSfsysStreamSetLoopPoint(u32 a, u32 b, u32 c, u32 d);
s32 GSfsysGetStatus(u32 id);
s32 GSfsysGetDriveStatus();
void GSfsysCancel(u32 id);
void GSfsysWait(u32 id);
u32 GSfsysGetInvalidID();
u8 GSfsysReadStreamingEX(u32 a, u32 b, u32 c);
u32 OSDisableInterrupts();
void OSRestoreInterrupts(u32 level);
u32 OSGetSoundMode();
void OSSetSoundMode(u32 mode);
u32 ARGetDMAStatus();
u32 ARQGetChunkSize();
void PSVECSubtract(const SVec* a, const SVec* b, SVec* out);

u8 sndCheckEmitter(void* em);
u32 sndEmitterVoiceID(void* em);
u8 sndRemoveEmitter(void* em);
u32 sndAddEmitter(void* em, SVec* pos, SVec* dir, f32 maxDis, f32 comp, u32 flags, u32 fxid, u8 maxVol,
                  u8 minVol, void* room);
u8 sndUpdateEmitter(void* em, SVec* pos, SVec* dir, u8 maxVol, void* room);
u8 sndAddListener(void* li, SVec* pos, SVec* dir, SVec* heading, SVec* up, f32 frontSur, f32 backSur,
                  f32 soundSpeed, u32 flags, u8 vol, const f32* exPara);
u8 sndUpdateListener(void* li, SVec* pos, SVec* dir, SVec* heading, SVec* up, u8 vol, void* room);
u8 sndRemoveListener(void* li);
u32 sndFXCheck(u32 vid);
u8 sndFXKeyOff(u32 vid);
u8 sndFXCtrl(u32 vid, u8 ctrl, u8 value);
u32 sndFXStartEx(u16 fid, u8 vol, u8 pan, u8 studio);
u8 sndSeqGetValid(u32 seq);
void sndSeqContinue(u32 seq);
void sndSeqPause(u32 seq);
void sndSeqVolume(u8 vol, u16 time, u32 seq, u8 mode);
u32 sndSeqPlayEx(u8 gid, u16 sid, void* arr, SND_PLAYPARA* para, u8 studio);
void sndStreamDeactivate(u32 stid);
u32 sndStreamAllocEx(u8 prio, void* buffer, u32 samples, u32 frq, u8 vol, u8 pan, u8 span, u8 auxa,
                     u8 auxb, u8 studio, u32 flags,
                     u32 (*updateFunction)(void*, u32, void*, u32, u32), u32 user, void* adpcmInfo);
void sndMasterVolume(u8 volume, u16 time, u8 music, u8 fx);
void sndVolume(u8 volume, u16 time, u8 volGroup);
void sndOutputMode(u32 mode);
u8 sndIsInstalled();
void sndQuit();
s32 sndInit(u8 voices, u8 music, u8 sfx, u8 studios, u32 flags, u32 aramSize);
void sndSetHooks(SND_HOOKS* hooks);
u8 sndPushGroup(void* prj, u16 gid, void* samples, void* sampdir, void* pool);
void sndSetSampleDataUploadCallback(void* (*cb)(u32, u32), u32 chunk);
void sndSetReceiveMessageCallback(void (*cb)(u32, s32));
void sndSetAuxProcessingCallbacks(u8 studio, void (*auxA)(u8, void*, void*), void* userA, u8 midiA,
                                  u32 seqIDA, void (*auxB)(u8, void*, void*), void* userB, u8 midiB,
                                  u32 seqIDB);
void sndAuxCallbackReverbHI(u8 reason, void* info, void* user);
u8 sndAuxCallbackPrepareReverbHI(void* rev);
u8 sndAuxCallbackUpdateSettingsReverbHI(void* rev);

u32 _sndStreamCallback(void*, u32, void*, u32, u32);
void _sndStreamCtrl(SndStream* s, u32 mode);
void _sndStreamGetData(SndStream* s, void (*cb)());
void _sndStreamGetDataCallback_START();
void _sndStreamGetDataCallback_ACTIVATE();
void _sndStreamGetDataCallback_EXEC_UPDATE();
void _sndStreamPrepareGetData(SndStream* s);
u32 _sndStreamNibble_HeaderON2OFF(u32 v);

u8 GSsndClose(u32 id);
u8 GSsndStop(u32 id, s32 time, u32 unused);
u8 GSsndOpen(u32 id, u32 a, u32 b);
s32 GSsndGetStatus(u32 id);
void GSsndUpdateSettingsReverbHI(u32 rev);
u8 GSsndSetOriginalVolume(u32 id, s32 time, s32 vol);
u8 GSsndPopVolumeID(u32 id, u32 time);
u8 GSsndPushVolumeID(u32 id, s32 time, s32 vol);
SndEmitter* GSsndCreateEmitterParam(u32 id, SVec* pos, SVec* dir, f32 maxDis, f32 comp, u8 maxVol, u8 minVol);
SndListener* GSsndCreateListenerParam(SVec* pos, SVec* dir, SVec* heading, SVec* up, u8 vol, f32 frontSur, f32 backSur, f32 soundSpeed);
void GSsndSetOutputMode(s32 mode);
u32 GSsndGetOutputMode();
void GSsndSetVolume(s32 vol, s32 time, u32 a, u32 b);

extern u32* snd_data_number;
extern SndData* snd_data;
extern u32* snd_file_number;
extern SndFile* snd_file;
extern u32* snd_wave_data_number;
extern SndWaveData* snd_wave_data;
extern u32* snd_rev_data_number;
extern SndRevData* snd_rev_data;
}

extern "C" {

static u8 _initFlag;
static void* _sndDaemonHDL;
static SndStream* _sndStreaming;
static u32 _maxStreaming;
static u32 _SampleDataFileOffset;
static void* _SampleDataFileInfo;
static void* _SampleDataUploadBuffer;
static SndEmitter* _sndEmitter;
static u32 _maxEmitter;
static SndListener* _sndListener;
static u32 _maxListener;
static u8* _sndStack;
static u32 _maxStack;
static SndWork* _sndWork;
static u32 _maxSndWork;
static u32 _revH_now_parm_id;
static u32 _maxSoundID;
static SndRevH _revH;
static f32 expParam = 1.0f;

static SndStream* _sndGetStream(u32 key);
static u8 _sndStreamGetValid(u32 id);
static u32 _sndStreamGetSndID(u32 id);
static void _sndStreamVolume(u8 vol, u16 time, u32 id, u8 mode);
static void _sndStreamDaemon(SndStream* s);
static void _sndDaemon();
static void _sndFreeEmitter(SndEmitter* e);
static void _sndFreeListener(SndListener* l);
static void _sndFreeStream(SndStream* s);
static void _sndFreeSndWork(SndWork* w);
static SndStream* _sndGetNewStream();
static SndEmitter* _sndGetNewEmitter();
static SndListener* _sndGetNewListener();
static SndWork* _sndGetNewSndWork();
static u8 _sndCheckEmitter(SndEmitter* e);
static u8 _sndStreamInit(u32 n);
static void _sndReceiveMessage(u32 vid, s32 msg);
static u8 _sndClose(u32 id, u8 stop);
static u8 _sndOpenWave(u32 id, u32 mode, u32 fileId, u32 offset, u32 res, u32 a, u32 b, u32 c);
static void* _sndSetSampleDataUploadCallbackFunction(u32 off, u32 bytes);
static void _sndCheckSndWorkALL();
static u8 _sndSetVolume(SndData* d, s32 time, s32 vol);
static u8 _sndSetVolumeWork(u32 id, u8 vol);
static u8 _sndStopSTREAM(SndData* d, s32 time, u32 unused);
static u8 _sndStopSE(SndData* d, s32 time, u32 unused);
static u8 _sndStopBGM(SndData* d, s32 time, u32 unused);
static u8 _sndPlay(u32 id, s32 time, u8 vol, u32 flag);
static u8 _sndGetProperVolume(SndData* d, u8 vol);
static u8 _sndPlaySTREAM(SndData* d, u32 id, s32 time, u8 vol, u32 flag);
static u8 _sndPlaySE(SndData* d, u32 id, u8 vol);
static u8 _sndPlayBGM(SndData* d, u32 id, s32 time, u8 vol, u32 flag);
static u32 _sndDesc2Id(u32 vid);
static void _sndInitEmitter();
static void _sndInitListener();
static void _sndInitStack();
static void _sndInitSndWork();
static void _sndSetReverbParm(u32 id);
static void _sndInitParms(SndData* d, SndWork* w);
static void _sndDoFree(void* p);
static void* _sndDoMalloc(u32 size);

static inline SND_HOOKS _sndMakeHooks() {
    SND_HOOKS hooks = {_sndDoMalloc, _sndDoFree};
    return hooks;
}

void GSsndStreamPostFunc(u32 a, u32 b) {
    SndStream* s;
    if (_initFlag) {
        s = _sndGetStream(a);
        if (s) {
            s->state = 3;
            if (s->child) {
                s->child->state = 3;
            }
            GSfsysStreamSetLoopFlag(a, b, s->x5c);
            s->xae = 0;
            s->xaf = 0;
            s->xb0 = 0;
            s->xb4 = 0;
            s->xb8 = 0;
            s->xbc = 1;
            s->xee = 0;
            s->xef = 0;
            s->xf0 = 0;
            s->xf4 = 0;
            s->xf8 = 0;
            s->xfc = 1;
            s->x71 = 0;
            s->x72 = 0;
            s->x73 = 0;
            s->x74 = ((s->x60 - 2) >> 16) * 0xE000;
            s->x78 = ((s->x64 + 0xFFFF) >> 16) * 0xE000;
            s->x7c = _sndStreamNibble_HeaderON2OFF(s->x68);
            u32 loopStart;
            u32 loopEnd;
            if (s->x5c == 1) {
                loopStart = ((s->x60 - 2) >> 16) << 15;
                loopEnd = ((s->x64 + 0xFFFF) >> 16) << 15;
            } else {
                loopStart = 0;
                loopEnd = ((s->x68 + 0xFFFF) >> 16) << 15;
            }
            GSfsysStreamSetLoopPoint(a, b, loopStart << 1, loopEnd << 1);
        }
    }
}

void* GSsndStreamPreFunc(u32 id) {
    if (!_initFlag) {
        return 0;
    }
    SndStream* s = _sndGetStream(id);
    if (s == 0) {
        return 0;
    }
    return &s->pad40;
}

static u32 _sndStreamGetSndID(u32 id) {
    SndStream* s = _sndGetStream(id);
    if (!s) {
        return -1;
    }
    if (s->master) {
        s = s->master;
    }
    return s->sndId;
}

static u8 _sndStreamGetValid(u32 id) {
    if (_sndGetStream(id) || GSfsysGetStatus(id) == 1) {
        return 1;
    }
    return 0;
}

static void _sndStreamVolume(u8 vol, u16 time, u32 id, u8 mode) {
    SndStream* a;
    SndStream* b;
    u32 en = OSDisableInterrupts();
    SndStream* s = _sndGetStream(id);
    if (!s) {
        OSRestoreInterrupts(en);
        return;
    }
    if (s->master) {
        a = s->master;
        b = s;
    } else {
        a = s;
        b = s->child;
    }
    if (a->x3d == 1 && mode == 0) {
        _sndStreamCtrl(a, 0);
        _sndStreamCtrl(b, 0);
    }
    a->curVol = a->baseVol;
    a->vol = vol;
    a->x39 = 0;
    a->time = time;
    a->mode = mode;
    b->curVol = a->baseVol;
    b->vol = vol;
    b->x39 = 0;
    b->time = time;
    b->mode = mode;
    OSRestoreInterrupts(en);
}

static void _sndStreamDaemon(SndStream* s) {
}

static void _sndDaemon() {
    u32 en;
    SndStream* s;
    u8 ready;
    u32 i;
    SndStream* m;
    SndStream* c;
    switch (GSfsysGetDriveStatus()) {
    case -1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
    case 11:
        ready = 1;
        break;
    default:
        ready = 0;
        break;
    }
    for (i = 0; i < _maxStreaming; i++) {
        s = &_sndStreaming[i];
        if (s->master) {
            m = s->master;
            c = s;
        } else {
            m = s;
            c = s->child;
        }
        switch (s->state) {
        case 0:
        case 1:
        case 2:
        case 10:
        case 11:
        case 13:
            break;
        default:
            _sndStreamPrepareGetData(s);
            break;
        }
        s->ready = ready;
        en = OSDisableInterrupts();
        switch (s->state) {
        case 3:
            _sndStreamGetData(s, _sndStreamGetDataCallback_START);
            break;
        case 6:
            _sndStreamGetData(s, _sndStreamGetDataCallback_ACTIVATE);
            break;
        case 9:
            _sndStreamDaemon(s);
            break;
        case 10:
            s->state = 11;
            if (!s->master) {
                GSsndClose(s->sndId);
            }
            break;
        case 13:
            sndStreamDeactivate(s->stid);
            if (m->x5c == 0) {
                s->state = 10;
            } else {
                s->state = 12;
            }
            break;
        case 12:
            if (!m->x3f && !c->x3f) {
                s->state = 3;
            } else if (s->x3f) {
                _sndStreamGetData(s, _sndStreamGetDataCallback_EXEC_UPDATE);
            }
            break;
        }
        OSRestoreInterrupts(en);
    }
}

u8 GSsndIsPlayingStream(u32 id) {
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    SndData* d = &snd_data[id];
    if (d->stream == 1) {
        SndWork* w = d->work;
        if (!w) {
            return 0;
        }
        if (w->voice == -1) {
            return 0;
        }
        if (!_sndStreamGetValid(w->voice)) {
            return 0;
        }
        SndStream* s = _sndGetStream(w->voice);
        if (s == 0) {
            return 0;
        }
        return s->state == 9;
    }
}

u8 GSsndCheckEnv(u32 id) {
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    return snd_data[id].env;
}

u8 GSsndCheckStream(u32 id) {
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    return snd_data[id].stream;
}

u8 GSsndCheckSE(u32 id) {
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    return snd_data[id].se;
}

void GSsndSetPushVolumeID(u32 id, u8* buf) {
    SndWork* w;
    SndData* d;
    s32 i;
    if (!_initFlag) {
        return;
    }
    if (id == -1 || id >= *snd_data_number) {
        return;
    }
    d = &snd_data[id];
    w = d->work;
    if (!w) {
        return;
    }
    if (!buf) {
        return;
    }
    if (buf[0] >= 3) {
        return;
    }
    w->pushCount = buf[0];
    for (i = 0; i < buf[0]; i++) {
        w->push[i] = buf[i + 1];
    }
}

void GSsndGetPushVolumeID(u32 id, u8* buf) {
    SndWork* w;
    SndData* d;
    s32 i;
    if (!_initFlag) {
        return;
    }
    if (id == -1 || id >= *snd_data_number) {
        return;
    }
    d = &snd_data[id];
    w = d->work;
    if (!w) {
        return;
    }
    if (!buf) {
        return;
    }
    if (w->pushCount >= 3) {
        return;
    }
    buf[0] = w->pushCount;
    for (i = 0; i < buf[0]; i++) {
        buf[i + 1] = w->push[i];
    }
}

u8 GSsndGetVolume(u32 id) {
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    SndData* d = &snd_data[id];
    if (d->open != 1) {
        return 0;
    }
    SndWork* w = d->work;
    if (w == 0) {
        return 0;
    }
    return w->vol;
}

void GSsndPopVolumeALL(u32 time, u32 bgm, u32 se) {
    int i;
    SndData* d;
    for (i = 0; i < _maxSoundID; i++) {
        d = &snd_data[i];
        if (d->open == 1) {
            if (d->se == 1) {
                if (!se) {
                    continue;
                }
            } else if (!bgm) {
                continue;
            }
            GSsndPopVolumeID(i, time);
        }
    }
}

u8 GSsndPopVolumeID(u32 id, u32 time) {
    SndData* d;
    SndWork* w;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    w = d->work;
    if (!w) {
        return 0;
    }
    if (w->pushCount == 0) {
        return 0;
    }
    w->pushCount--;
    return GSsndSetOriginalVolume(id, time, w->push[w->pushCount]);
}

void GSsndPushVolumeALL(s32 vol, s32 time, u32 bgm, u32 se) {
    int i;
    SndData* d;
    for (i = 0; i < _maxSoundID; i++) {
        d = &snd_data[i];
        if (d->open == 1) {
            if (d->se == 1) {
                if (!se) {
                    continue;
                }
            } else if (!bgm) {
                continue;
            }
            GSsndPushVolumeID(i, time, vol);
        }
    }
}

u8 GSsndPushVolumeID(u32 id, s32 time, s32 vol) {
    SndData* d;
    SndWork* w;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    w = d->work;
    if (!w) {
        return 0;
    }
    if (w->pushCount >= 3) {
        return 0;
    }
    s32 pv = _sndGetProperVolume(d, vol);
    if (w->vol < pv) {
        pv = w->vol;
    }
    w->push[w->pushCount] = w->vol;
    if (w->pushCount < 2) {
        w->pushCount++;
    }
    return GSsndSetOriginalVolume(id, time, pv);
}

u32 GSsndCheckEmitter(SndEmitter* e) {
    u32 r;
    if (!_initFlag) {
        return 0;
    }
    if (!e) {
        return 0;
    }
    r = _sndCheckEmitter(e) != 0;
    return r;
}

u8 GSsndUpdateEmitter(SndEmitter* e, SVec* pos) {
    SVec diff;
    if (!_initFlag) {
        return 0;
    }
    if (!e) {
        return 0;
    }
    if (!_sndCheckEmitter(e)) {
        return 0;
    }
    PSVECSubtract(&e->pos, pos, &diff);
    if (sndUpdateEmitter(e->em, pos, &diff, e->maxVol, 0)) {
        e->pos.x = pos->x;
        e->pos.y = pos->y;
        e->pos.z = pos->z;
        e->dir.x = diff.x;
        e->dir.y = diff.y;
        e->dir.z = diff.z;
        return 1;
    }
    return 0;
}

u8 GSsndFreeEmitter(SndEmitter* e) {
    u32 v;
    if (!_initFlag) {
        return 0;
    }
    if (!e) {
        return 0;
    }
    if (!e->used) {
        return 1;
    }
    v = sndEmitterVoiceID(e->em);
    if (v != -1) {
        sndFXKeyOff(v);
    }
    sndRemoveEmitter(e->em);
    _sndFreeEmitter(e);
    return 1;
}

SndEmitter* GSsndCreateEmitter(u32 id, SVec* pos) {
    SVec dir;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 0.0f;
    return GSsndCreateEmitterParam(id, pos, &dir, 10000.0f, 0.0f, 0x7F, 0);
}

SndEmitter* GSsndCreateEmitterParam(u32 id, SVec* pos, SVec* dir, f32 maxDis, f32 comp, u8 maxVol,
                                    u8 minVol) {
    SndData* d;
    SndEmitter* e;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    e = _sndGetNewEmitter();
    if (!e) {
        return 0;
    }
    sndAddEmitter(e->em, pos, dir, maxDis, comp, 0x9F, d->fxid, maxVol, minVol, 0);
    e->pos.x = pos->x;
    e->pos.y = pos->y;
    e->pos.z = pos->z;
    e->dir.x = dir->x;
    e->dir.y = dir->y;
    e->dir.z = dir->z;
    e->maxVol = maxVol;
    e->minVol = minVol;
    e->maxDis = maxDis;
    e->comp = comp;
    e->sndId = id;
    if (sndCheckEmitter(e->em) == 1) {
        return e;
    }
    _sndFreeEmitter(e);
    return 0;
}

u8 GSsndUpdateListenerParam(SndListener* l, SVec* pos, SVec* heading, SVec* up) {
    SVec diff;
    if (!_initFlag) {
        return 0;
    }
    if (!l) {
        return 0;
    }
    PSVECSubtract(&l->pos, pos, &diff);
    if (sndUpdateListener(l->li, pos, &diff, heading, up, l->vol, 0) == 1) {
        l->pos.x = pos->x;
        l->pos.y = pos->y;
        l->pos.z = pos->z;
        l->dir.x = diff.x;
        l->dir.y = diff.y;
        l->dir.z = diff.z;
        l->heading.x = heading->x;
        l->heading.y = heading->y;
        l->heading.z = heading->z;
        l->up.x = up->x;
        l->up.y = up->y;
        l->up.z = up->z;
        return 1;
    }
    return 0;
}

u8 GSsndFreeListener(SndListener* l) {
    if (!_initFlag) {
        return 0;
    }
    if (!l) {
        return 0;
    }
    sndRemoveListener(l->li);
    _sndFreeListener(l);
    return 1;
}

SndListener* GSsndCreateListener(SVec* pos) {
    SVec dir;
    SVec heading;
    SVec up;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 0.0f;
    heading.x = 0.0f;
    heading.y = 0.0f;
    heading.z = -1.0f;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    return GSsndCreateListenerParam(pos, &dir, &heading, &up, 0x7F, 250.0f, 250.0f, 1000.0f);
}

SndListener* GSsndCreateListenerParam(SVec* pos, SVec* dir, SVec* heading, SVec* up, u8 vol,
                                      f32 frontSur, f32 backSur, f32 soundSpeed) {
    SndListener* l;
    if (!_initFlag) {
        return 0;
    }
    l = _sndGetNewListener();
    if (!l) {
        return 0;
    }
    if (sndAddListener(l->li, pos, dir, heading, up, frontSur, backSur, soundSpeed, 1, vol, &expParam) == 1) {
        l->pos.x = pos->x;
        l->pos.y = pos->y;
        l->pos.z = pos->z;
        l->dir.x = dir->x;
        l->dir.y = dir->y;
        l->dir.z = dir->z;
        l->heading.x = heading->x;
        l->heading.y = heading->y;
        l->heading.z = heading->z;
        l->up.x = up->x;
        l->up.y = up->y;
        l->up.z = up->z;
        l->frontSur = frontSur;
        l->backSur = backSur;
        l->soundSpeed = soundSpeed;
        l->vol = vol;
        return l;
    }
    _sndFreeListener(l);
    return 0;
}

u8 GSsndSetOriginalVolume(u32 id, s32 time, s32 vol) {
    SndData* d;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    if (!d->se && d->open != 1) {
        return 0;
    }
    return _sndSetVolume(d, time, vol);
}

s32 GSsndGetStatus(u32 id) {
    SndData* d;
    SndWork* w;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    if (d->open != 1) {
        return 0;
    }
    w = d->work;
    if (!w) {
        return 0;
    }
    if (d->stream == 1) {
        if (d->paused == 1) {
            return 3;
        }
        if (w->voice != -1 && _sndStreamGetValid(w->voice) == 1) {
            return 2;
        }
        _sndClose(id, 1);
        return 0;
    } else if (d->se == 1) {
        if (w->voice != -1 && sndFXCheck(w->voice) != -1) {
            return 2;
        }
        _sndClose(id, 1);
        return 0;
    } else {
        if (d->paused == 1) {
            return 3;
        }
        if (w->voice != -1 && sndSeqGetValid(w->voice) == 1) {
            return 2;
        }
        _sndClose(id, 1);
        return 0;
    }
}

u8 GSsndContinue(u32 id, s32 time) {
    SndData* d;
    SndWork* w;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    if (d->se == 1) {
        return 0;
    }
    if (d->open != 1) {
        return 0;
    }
    w = d->work;
    if (!w) {
        return 0;
    }
    if (w->voice == -1) {
        return 0;
    }
    if (d->paused != 1) {
        return 0;
    }
    GSsndUpdateSettingsReverbHI(d->reverb);
    if (id == 8) {
        return 1;
    }
    if (d->stream == 1) {
        _sndStreamVolume(w->vol, time, w->voice, 0);
    } else {
        sndSeqContinue(w->voice);
        sndSeqVolume(w->vol, time, w->voice, 0);
    }
    d->paused = 0;
    return 1;
}

u8 GSsndPause(u32 id, s32 time) {
    SndData* d;
    SndWork* w;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    if (d->se == 1) {
        return 0;
    }
    if (d->open != 1) {
        return 0;
    }
    w = d->work;
    if (!w) {
        return 0;
    }
    if (w->voice == -1) {
        return 0;
    }
    if (d->paused == 1) {
        return 0;
    }
    if (id == 8) {
        return 1;
    }
    if (d->stream == 1) {
        _sndStreamVolume(0, time, w->voice, 2);
    } else {
        sndSeqVolume(0, time, w->voice, 0);
        sndSeqPause(w->voice);
    }
    d->paused = 1;
    return 1;
}

u8 GSsndStopNow(u32 id) {
    return GSsndStop(id, 0, 0);
}

u8 GSsndStop(u32 id, s32 time, u32 unused) {
    SndData* d;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    if (d->stream == 1) {
        return _sndStopSTREAM(d, time, unused);
    } else if (d->se == 1) {
        return _sndStopSE(d, time, unused);
    } else {
        return _sndStopBGM(d, time, unused);
    }
}

u8 GSsndPlayNow(u32 id) {
    return _sndPlay(id, 0, 0x7F, 0);
}

u8 GSsndPlayVolume(u32 id, s32 time, u8 vol, u32 flag) {
    return _sndPlay(id, time, vol, flag);
}

u8 GSsndPlay(u32 id, s32 time, u32 flag) {
    return _sndPlay(id, time, 0x7F, flag);
}

u8 GSsndClose(u32 id) {
    return _sndClose(id, 1);
}

u8 GSsndOpen(u32 id, u32 a, u32 b) {
    SndData* d;
    SndWork* w;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    if (d->open == 1) {
        return 0;
    }
    w = _sndGetNewSndWork();
    if (!w) {
        _sndCheckSndWorkALL();
        w = _sndGetNewSndWork();
        if (!w) {
            return 0;
        }
    }
    _sndInitParms(d, w);
    w->res0 = a;
    w->res1 = b;
    return 1;
}

u8 GSsndOpenWaveDVD(u32 wave, u32 fileId, u32 heap, u32 a, u32 b, u32 c, u32 e) {
    return _sndOpenWave(wave, 1, fileId, heap, a, b, c, e);
}

void GSsndUpdateSettingsReverbHI(u32 rev) {
    if (_initFlag && rev < *snd_rev_data_number && rev != 0 && _revH_now_parm_id != rev) {
        _sndSetReverbParm(rev);
        sndAuxCallbackUpdateSettingsReverbHI(&_revH);
    }
}

u32 GSsndGetOutputMode() {
    switch (OSGetSoundMode()) {
    case 0:
        return 0;
    case 1:
        return 1;
    default:
        return 0;
    }
}

void GSsndSetOutputMode(s32 mode) {
    if (_initFlag) {
        sndOutputMode(mode);
        switch (mode) {
        case 0:
            OSSetSoundMode(0);
            break;
        case 1:
        case 2:
            OSSetSoundMode(1);
            break;
        }
    }
}

void GSsndSetMasterVolume(s32 vol, s32 time, s32 music, s32 fx) {
    if (_initFlag) {
        sndMasterVolume(vol, time, music, fx);
    }
}

void GSsndSetVolume(s32 vol, s32 time, u32 a, u32 b) {
    s32 g;
    SndData* d;
    int i;
    if (_initFlag) {
        if (a == 1 && b == 1) {
            g = 0xFF;
        } else if (a == 1 && b != 1) {
            g = 0xFD;
        } else if (a != 1 && b == 1) {
            g = 0xFE;
        } else {
            return;
        }
        for (i = 0; i < _maxSoundID; i++) {
            d = &snd_data[i];
            if (d->open == 1) {
                switch (g) {
                case 0xFD:
                    if (d->se == 1) {
                        continue;
                    }
                    break;
                case 0xFE:
                    if (!d->se) {
                        continue;
                    }
                    break;
                case 0xFF:
                    break;
                }
                _sndSetVolumeWork(i, vol);
                if (d->stream == 1) {
                    _sndSetVolume(d, time, vol);
                }
            }
        }
        sndVolume(vol, time, g);
    }
}

void GSsndQuit() {
    if (_initFlag && sndIsInstalled() == 1) {
        GSsndSetVolume(0, 0, 1, 1);
        sndQuit();
        GSgappTerminate(_sndDaemonHDL);
        _sndDaemonHDL = 0;
    }
}

u8 GSsndInit(u32 a, u32 maxStack, u32 b, u32 maxListener, u32 maxEmitter) {
    SND_HOOKS hooks = _sndMakeHooks();
    u32 n;
    if (_initFlag == 1) {
        return 0;
    }
    n = a + b;
    if (n >= 0x40) {
        return 0;
    }
    _maxSoundID = *snd_data_number;
    _revH_now_parm_id = -1;
    _maxSndWork = n;
    _sndWork = (SndWork*)_sndDoMalloc(n * 0x14);
    if (!_sndWork) {
        return 0;
    }
    _sndInitSndWork();
    _maxStack = maxStack;
    _sndStack = (u8*)_sndDoMalloc(maxStack);
    if (!_sndStack) {
        return 0;
    }
    _sndInitStack();
    _maxListener = maxListener;
    _sndListener = (SndListener*)_sndDoMalloc(maxListener * 0xD0);
    if (!_sndListener) {
        return 0;
    }
    _sndInitListener();
    _maxEmitter = maxEmitter;
    _sndEmitter = (SndEmitter*)_sndDoMalloc(maxEmitter * 0x78);
    if (!_sndEmitter) {
        return 0;
    }
    _sndInitEmitter();
    sndSetHooks(&hooks);
    if (sndInit(0x40, 0x30, 0x10, 1, 2, 0x5FC000)) {
        return 0;
    }
    _sndSetReverbParm(0);
    sndAuxCallbackPrepareReverbHI(&_revH);
    sndSetAuxProcessingCallbacks(0, sndAuxCallbackReverbHI, &_revH, 0xFF, 0, 0, 0, 0xFF, 0);
    sndSetReceiveMessageCallback(_sndReceiveMessage);
    _sndDaemonHDL = GSgappCreate(1, 0x1E, 0, _sndDaemon);
    GSgappSetName(_sndDaemonHDL, "GSmovieDaemon");
    if (!_sndStreamInit(4)) {
        return 0;
    }
    _initFlag = 1;
    GSsndSetVolume(0x7F, 0, 1, 0);
    GSsndSetVolume(100, 0, 0, 1);
    GSsndSetOutputMode(GSsndGetOutputMode());
    return 1;
}

static u8 _sndCheckEmitter(SndEmitter* e) {
    u32 v;
    if (!e->used) {
        return 0;
    }
    v = sndEmitterVoiceID(e->em);
    if (v == -1) {
        return 0;
    }
    if (!sndCheckEmitter(e->em)) {
        sndFXKeyOff(v);
        return 0;
    }
    if (sndFXCheck(v) == -1) {
        sndFXKeyOff(v);
        return 0;
    }
    return 1;
}

static u8 _sndStreamInit(u32 n) {
    SndStream* s;
    u32 i;
    _maxStreaming = n;
    _sndStreaming = (SndStream*)_sndDoMalloc(n << 8);
    if (!_sndStreaming) {
        return 0;
    }
    for (i = 0; i < _maxStreaming; i++) {
        s = &_sndStreaming[i];
        s->master = 0;
        s->child = 0;
        s->state = 0;
        s->baseVol = 0;
        s->curVol = 0;
        s->vol = 0;
        s->right = 0;
        s->bufSize = 0x10000;
        s->bufBytes = (s->bufSize >> 3) * 0xE;
        s->buf = _sndDoMalloc(0x18000);
        s->x3f = 0;
        s->x1c = 0;
        s->x20 = 0;
        s->x24 = 0;
        s->fsysId = 0;
        s->sndId = 0;
        s->time = 0;
        s->mode = 0;
        s->x3c = 0;
        s->x3d = 0;
        s->ready = 0;
        s->stid = sndStreamAllocEx(0xFF, s->buf, s->bufBytes, 32000, s->baseVol, 0x40, 0, 0, 0, 0, 0x30001,
                                   _sndStreamCallback, (u32)s, 0);
    }
    return 1;
}

static void _sndReceiveMessage(u32 vid, s32 msg) {
    u32 id = _sndDesc2Id(vid);
    if (id) {
        _sndClose(id, 0);
    }
}

static u8 _sndClose(u32 id, u8 stop) {
    SndData* d;
    SndWork* w;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    if (d->open != 1) {
        return 0;
    }
    w = d->work;
    if (!w) {
        return 0;
    }
    if (stop == 1) {
        GSsndStop(id, 0, 0);
    }
    _sndInitParms(d, w);
    _sndFreeSndWork(w);
    d->work = 0;
    d->open = 0;
    return 1;
}

static u8 _sndOpenWave(u32 id, u32 mode, u32 fileId, u32 offset, u32 res, u32 a, u32 b, u32 c) {
    SndWaveData* wd;
    void* prj;
    void* samples;
    void* sampdir;
    void* pool;
    if (!_initFlag) {
        return 0;
    }
    if (id >= *snd_wave_data_number) {
        return 0;
    }
    wd = &snd_wave_data[id];
    if (wd->loaded == 1) {
        return 0;
    }
    prj = GSresGetResource(res, b);
    if (!prj) {
        return 0;
    }
    sampdir = GSresGetResource(res, c);
    if (!sampdir) {
        return 0;
    }
    pool = GSresGetResource(res, a);
    if (!pool) {
        return 0;
    }
    if (mode == 1) {
        samples = 0;
        sndSetSampleDataUploadCallback(_sndSetSampleDataUploadCallbackFunction, ARQGetChunkSize());
        _SampleDataFileInfo = GSdvdOpen(fileId);
        if (!_SampleDataFileInfo) {
            return 0;
        }
        _SampleDataFileOffset = offset;
        _SampleDataUploadBuffer = _sndDoMalloc(ARQGetChunkSize());
        if (!_SampleDataUploadBuffer) {
            GSdvdClose(_SampleDataFileInfo);
            return 0;
        }
    } else {
        samples = (void*)fileId;
        sndSetSampleDataUploadCallback(0, 0);
    }
    if (!sndPushGroup(prj, wd->gid, samples, sampdir, pool)) {
        if (mode == 1) {
            GSdvdClose(_SampleDataFileInfo);
        }
        return 0;
    }
    if (mode == 1) {
        _sndDoFree(_SampleDataUploadBuffer);
        GSdvdClose(_SampleDataFileInfo);
    }
    wd->loaded = 1;
    return 1;
}

static void* _sndSetSampleDataUploadCallbackFunction(u32 off, u32 bytes) {
    while (ARGetDMAStatus() != 0) {
    }
    while (1) {
        s32 r = GSdvdRead(_SampleDataFileInfo, _SampleDataUploadBuffer, bytes, off + _SampleDataFileOffset);
        switch (r) {
        case -1:
        case -3:
            continue;
        }
        break;
    }
    return _SampleDataUploadBuffer;
}

static void _sndCheckSndWorkALL() {
    int i;
    GSlogWrite("_sndCheckSndWorkALL:Start\n");
    for (i = 0; i < _maxSoundID; i++) {
        GSsndGetStatus(i);
    }
    GSlogWrite("_sndCheckSndWorkALL:End\n");
}

static u8 _sndSetVolume(SndData* d, s32 time, s32 vol) {
    SndWork* w = d->work;
    if (!w) {
        return 0;
    }
    w->vol = _sndGetProperVolume(d, vol);
    if (w->voice != -1) {
        if (d->stream == 1) {
            _sndStreamVolume(w->vol, time, w->voice, 0);
        } else if (d->se == 1) {
            sndFXCtrl(w->voice, 7, w->vol);
        } else {
            sndSeqVolume(w->vol, time, w->voice, 0);
        }
        return 1;
    }
    return 0;
}

static u8 _sndSetVolumeWork(u32 id, u8 vol) {
    SndData* d = &snd_data[id];
    if (d->open != 1) {
        if (d->se == 1) {
            GSsndOpen(id, 0, 0);
        } else {
            return 0;
        }
    }
    if (d->work) {
        d->work->vol = vol & 0x7F;
    }
    return 1;
}

static u8 _sndStopSTREAM(SndData* d, s32 time, u32 unused) {
    SndWork* w = d->work;
    SndStream* s;
    SndStream* m;
    SndStream* c;
    if (!w) {
        return 0;
    }
    if (w->voice == -1) {
        return 0;
    }
    GSfsysCancel(w->voice);
    w->voice = -1;
    s = _sndGetStream(snd_file[d->file].a);
    if (!s) {
        return 0;
    }
    if (s->master) {
        m = s->master;
        c = s;
    } else {
        m = s;
        c = s->child;
    }
    sndStreamDeactivate(m->stid);
    sndStreamDeactivate(c->stid);
    _sndFreeStream(m);
    _sndFreeStream(c);
    return 1;
}

static u8 _sndStopSE(SndData* d, s32 time, u32 unused) {
    SndWork* w = d->work;
    u8 r;
    if (!w) {
        return 0;
    }
    if (w->voice == -1) {
        return 0;
    }
    if (sndFXCheck(w->voice) != -1) {
        r = sndFXKeyOff(w->voice);
    } else {
        r = 0;
    }
    w->voice = -1;
    return r;
}

static u8 _sndStopBGM(SndData* d, s32 time, u32 unused) {
    SndWork* w = d->work;
    if (!w) {
        return 0;
    }
    if (d->open != 1) {
        return 0;
    }
    if (w->voice == -1) {
        return 0;
    }
    sndSeqVolume(0, time, w->voice, 1);
    w->voice = -1;
    return 1;
}

static u8 _sndPlay(u32 id, s32 time, u8 vol, u32 flag) {
    SndData* d;
    if (!_initFlag) {
        return 0;
    }
    if (id == -1 || id >= *snd_data_number) {
        return 0;
    }
    d = &snd_data[id];
    vol = _sndGetProperVolume(d, vol);
    if (d->stream == 1) {
        return _sndPlaySTREAM(d, id, time, vol, flag);
    } else if (d->se == 1) {
        return _sndPlaySE(d, id, vol);
    } else {
        return _sndPlayBGM(d, id, time, vol, flag);
    }
}

static u8 _sndGetProperVolume(SndData* d, u8 vol) {
    if (vol == 0xFF) {
        if (d->se == 1) {
            vol = 100;
        } else {
            vol = 0x7F;
        }
    }
    if (vol > 0x7F) {
        vol = 0x7F;
    }
    return vol;
}

static u8 _sndPlaySTREAM(SndData* d, u32 id, s32 time, u8 vol, u32 flag) {
    SndWork* w;
    SndStream* s0;
    SndStream* s1;
    u32 f0;
    u32 f1;
    u32 f2;
    if (d->open != 1) {
        GSsndOpen(id, 0, 0);
    }
    w = d->work;
    if (!w) {
        return 0;
    }
    if (!d->se && w->voice != -1) {
        return 0;
    }
    f0 = snd_file[d->file].a;
    f1 = snd_file[d->file].b;
    f2 = snd_file[d->file].c;
    if (_sndStreamGetValid(f0) == 1) {
        GSfsysWait(f0);
        GSsndClose(_sndStreamGetSndID(f0));
        GSfsysWait(f0);
        GSsndOpen(id, 0, 0);
        w = d->work;
        if (!w) {
            return 0;
        }
    } else {
        GSfsysCancel(f0);
        GSfsysWait(f0);
    }
    s0 = _sndGetNewStream();
    if (!s0) {
        _sndClose(id, 0);
        return 0;
    }
    s0->master = 0;
    s0->child = 0;
    s0->state = 2;
    s0->fsysId = f0;
    s0->x2c = f2;
    s0->baseVol = 0;
    s0->curVol = 0;
    s0->vol = vol;
    s0->x39 = 0;
    s0->right = 0;
    s0->x3f = 0;
    s0->x1c = 0;
    s0->x20 = 0;
    s0->x24 = 0;
    s0->x3c = 0;
    s0->x3d = 0;
    s0->ready = 0;
    s0->sndId = id;
    s0->time = time;
    s0->mode = 0;
    s1 = _sndGetNewStream();
    if (!s1) {
        _sndClose(id, 0);
        _sndFreeStream(s0);
        return 0;
    }
    s1->master = 0;
    s1->child = 0;
    s1->state = 2;
    s1->fsysId = 0;
    s1->x2c = 0;
    s1->baseVol = 0;
    s1->curVol = 0;
    s1->vol = vol;
    s1->x39 = 0;
    s1->right = 1;
    s1->x3f = 0;
    s1->x1c = 0;
    s1->x20 = 0;
    s1->x24 = 0;
    s1->x3c = 0;
    s1->x3d = 0;
    s1->ready = 0;
    s1->sndId = id;
    s1->time = time;
    s1->mode = 0;
    s0->child = s1;
    s1->master = s0;
    if (f1 == 0) {
        f1 = GSfsysGetInvalidID();
    }
    if (!GSfsysReadStreamingEX(f0, f1, f2)) {
        _sndClose(id, 0);
        _sndFreeStream(s0);
        _sndFreeStream(s1);
        return 0;
    }
    w->vol = vol;
    w->voice = f0;
    return 1;
}

static SndStream* _sndGetStream(u32 key) {
    u32 i;
    SndStream* base = _sndStreaming;
    for (i = 0; i < _maxStreaming; i++) {
        if (base[i].state != 0 && base[i].fsysId == key) {
            return &base[i];
        }
    }
    return 0;
}

static u8 _sndPlaySE(SndData* d, u32 id, u8 vol) {
    SndWork* w;
    if (d->open != 1) {
        GSsndOpen(id, 0, 0);
    }
    w = d->work;
    if (!w) {
        return 0;
    }
    w->vol = vol;
    w->voice = sndFXStartEx(d->fxid, vol, w->pan, 0);
    sndFXCtrl(w->voice, 7, vol);
    return 1;
}

static u8 _sndPlayBGM(SndData* d, u32 id, s32 time, u8 vol, u32 flag) {
    void* res;
    SndWork* w;
    SND_PLAYPARA para;
    if (d->open != 1) {
        if (d->file >= *snd_file_number) {
            return 0;
        }
        GSsndOpen(id, snd_file[d->file].a, snd_file[d->file].c);
    }
    w = d->work;
    if (!w) {
        return 0;
    }
    if (d->open != 1) {
        return 0;
    }
    if (w->voice != -1) {
        return 0;
    }
    res = GSresGetResource(w->res0, w->res1);
    if (!res) {
        return 0;
    }
    GSsndUpdateSettingsReverbHI(d->reverb);
    para.flags = 4;
    para.trackMute[0] = 0;
    para.trackMute[1] = 0;
    para.speed = 0x100;
    para.volume.time = 0;
    para.volume.target = 0;
    para.numSeqVolDef = 0;
    para.seqVolDef = 0;
    para.numFaded = 0;
    para.faded = 0;
    w->vol = vol;
    w->voice = sndSeqPlayEx(d->group, d->fxid, res, &para, 0);
    sndSeqVolume(vol, time, w->voice, 0);
    return 1;
}

static u32 _sndDesc2Id(u32 vid) {
    int i;
    for (i = 0; i < _maxSoundID; i++) {
        SndData* d = &snd_data[i];
        SndWork* w = d->work;
        if (w && !d->stream && w->voice == vid) {
            return i;
        }
    }
    return 0;
}

static void _sndFreeStream(SndStream* s) {
    u32 en = OSDisableInterrupts();
    s->state = 0;
    s->fsysId = 0;
    OSRestoreInterrupts(en);
}

static void _sndFreeEmitter(SndEmitter* e) {
    u32 en = OSDisableInterrupts();
    e->used = 0;
    OSRestoreInterrupts(en);
}

static void _sndFreeListener(SndListener* l) {
    u32 en = OSDisableInterrupts();
    l->used = 0;
    OSRestoreInterrupts(en);
}

static void _sndFreeSndWork(SndWork* w) {
    u32 en = OSDisableInterrupts();
    w->used = 0;
    OSRestoreInterrupts(en);
}

static SndStream* _sndGetNewStream() {
    u32 i;
    u32 en = OSDisableInterrupts();
    SndStream* r = 0;
    for (i = 0; i < _maxStreaming; i++) {
        if (_sndStreaming[i].state == 0) {
            _sndStreaming[i].state = 1;
            r = &_sndStreaming[i];
            break;
        }
    }
    OSRestoreInterrupts(en);
    return r;
}

static SndEmitter* _sndGetNewEmitter() {
    u32 i;
    u32 en = OSDisableInterrupts();
    SndEmitter* r = 0;
    for (i = 0; i < _maxEmitter; i++) {
        if (_sndEmitter[i].used != 1) {
            _sndEmitter[i].used = 1;
            r = &_sndEmitter[i];
            break;
        }
    }
    OSRestoreInterrupts(en);
    return r;
}

static SndListener* _sndGetNewListener() {
    u32 i;
    u32 en = OSDisableInterrupts();
    SndListener* r = 0;
    for (i = 0; i < _maxListener; i++) {
        if (_sndListener[i].used != 1) {
            _sndListener[i].used = 1;
            r = &_sndListener[i];
            break;
        }
    }
    OSRestoreInterrupts(en);
    return r;
}

static SndWork* _sndGetNewSndWork() {
    u32 i;
    u32 en = OSDisableInterrupts();
    SndWork* r = 0;
    for (i = 0; i < _maxSndWork; i++) {
        if (_sndWork[i].used != 1) {
            _sndWork[i].used = 1;
            r = &_sndWork[i];
            break;
        }
    }
    OSRestoreInterrupts(en);
    return r;
}

static void _sndInitEmitter() {
    u32 i;
    for (i = 0; i < _maxEmitter; i++) {
        _sndEmitter[i].used = 0;
    }
}

static void _sndInitListener() {
    u32 i;
    for (i = 0; i < _maxListener; i++) {
        _sndListener[i].used = 0;
    }
}

static void _sndInitStack() {
    u32 i;
    for (i = 0; i < _maxStack; i++) {
        _sndStack[i] = 0;
    }
}

static void _sndInitSndWork() {
    u32 i;
    for (i = 0; i < _maxSndWork; i++) {
        _sndWork[i].used = 0;
    }
}

static void _sndSetReverbParm(u32 id) {
    SndRevData* r;
    r = &snd_rev_data[id];
    _revH.tempDisableFX = 0;
    _revH.coloration = r->coloration;
    _revH.mix = r->mix;
    _revH.time = r->time;
    _revH.damping = r->damping;
    _revH.preDelay = r->preDelay;
    _revH.crosstalk = r->crosstalk;
    _revH_now_parm_id = id;
}

static void _sndInitParms(SndData* d, SndWork* w) {
    u32 en = OSDisableInterrupts();
    d->open = 1;
    d->paused = 0;
    d->work = w;
    w->voice = -1;
    w->pushCount = 0;
    w->vol = 0x7F;
    w->pan = 0x40;
    w->b3 = 0x40;
    OSRestoreInterrupts(en);
}

static void _sndDoFree(void* p) {
    GSmemFree(p);
}

static void* _sndDoMalloc(u32 size) {
    return GSmemAllocAlign(size, 0x20);
}

}
