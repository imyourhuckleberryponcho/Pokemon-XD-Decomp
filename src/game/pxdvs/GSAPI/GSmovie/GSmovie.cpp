// DRAFT (dr_movie): all functions written, not yet exact. Source is written bottom-to-top
// (functions come out in reverse source order), expected flags: -inline deferred.
#pragma pool_strings off
#include <dolphin/types.h>

// ---------------------------------------------------------------- types
struct THPHeader {
    char magic[4];
    u32 version;
    u32 bufSize;
    u32 audioMaxSamples;
    f32 frameRate;
    u32 numFrames;
    u32 firstFrameSize;
    u32 movieDataSize;
    u32 compInfoDataOffsets;
    u32 offsetDataOffsets;
    u32 movieDataOffsets;
    u32 finalFrameDataOffsets;
};

struct THPFrameCompInfo {
    u32 numComponents;
    u8 frameComp[16];
};

struct THPVideoInfo {
    u32 xSize;
    u32 ySize;
    u32 videoType;
};

struct THPAudioInfo {
    u32 sndChannels;
    u32 sndFrequency;
    u32 sndNumSamples;
    u32 sndNumTracks;
};

struct THPReadBuffer {
    u8* ptr;
    s32 frameNumber;
    u8 isValid;
    u8 b9;
    u8 bA;
    s32 f0C;
};

struct THPTextureSet {
    u8* ytexture;
    u8* utexture;
    u8* vtexture;
    s32 frameNumber;
    u8 isValid;
    u8 used;
};

struct THPAudioBuffer {
    s16* buffer;
    s16* curPtr;
    u32 validSample;
    u8 pad;
};

struct THPPlayer {
    THPHeader header;                // 0x00
    THPFrameCompInfo compInfo;       // 0x30
    THPVideoInfo videoInfo;          // 0x44
    THPAudioInfo audioInfo;          // 0x50
    u8 cache[0x8000];                // 0x60
    s32 open;                        // 0x8060
    s32 f8064;
    s32 f8068;
    s32 f806C;
    s32 f8070;
    u8* thpWork;                     // 0x8074
    u8 state;                        // 0x8078
    u8 internalState;                // 0x8079
    u8 playFlag;                     // 0x807A
    u8 audioExist;                   // 0x807B
    s32 dvdError;                    // 0x807C
    s32 videoError;                  // 0x8080
    u8 onMemory;                     // 0x8084
    u8 f8085;
    u8 paused;                       // 0x8086
    u8 visible;                      // 0x8087
    u8* movieData;                   // 0x8088
    s32 initOffset;                  // 0x808C
    s32 initReadSize;                // 0x8090
    s32 initReadFrame;               // 0x8094
    s64 retraceCount;                // 0x8098
    s32 prevCount;                   // 0x80A0
    s32 curCount;                    // 0x80A4
    s32 videoDecodeCount;            // 0x80A8
    s32 curAudioTrack;               // 0x80AC
    s32 curVideoNumber;              // 0x80B0
    s32 curAudioNumber;              // 0x80B4
    s16 f80B8;
    s16 f80BA;
    THPTextureSet* dispTextureSet;   // 0x80BC
    THPAudioBuffer* playAudioBuffer; // 0x80C0
    THPReadBuffer readBuffer[10];    // 0x80C4
    s32 f8164;
    s32 f8168;
    s32 f816C;
    THPTextureSet textureSet[3];     // 0x8170
    s32 f81AC;
    u32 textureSetIndex;             // 0x81B0
    THPAudioBuffer audioBuffer[6];   // 0x81B4
    s32 f8214;
    s32 f8218;
    s32 sndStream0;                  // 0x821C
    s32 sndStream1;                  // 0x8220
    s16* audioWork0;                 // 0x8224
    s16* audioWork1;                 // 0x8228
    u8 f822C[4];
    u8 f8230[0x50];
};

struct __GSmovieStreaming {
    s32 state;          // 0x00
    struct GStexture* tex; // 0x04
    u32 id;             // 0x08
    u16 x;              // 0x0C
    u16 y;              // 0x0E
    void* mem;          // 0x10
    u8 f14;
    u8 f15;
    u8 loop;            // 0x16
    u8 startOffset;     // 0x17
    u16 token;          // 0x18
    u8 f1A;
    THPPlayer* player;  // 0x1C
};

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct GSgfxLayer {
    u8 pad[0x28];
    s32 id;
    void textureCopy(GSgfxLayerPass pass, struct GStexture* texture, bool clear, u8* clearColor, bool, bool, bool);
};

enum GSgfxLayerType {};
enum GSgfxLayerID {};
enum GSgfxLayerOffset {};

struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(GSgfxLayer* layer, GSgfxLayerPass pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 unk18;
};

class GSgfxLayerConfig {
public:
    static void Remove(GSgfxLayerID id);
    static GSgfxLayerID Add(char* name, u32 width, u32 height, u32 count, GSgfxLayerType type, bool clearColor,
                            bool clearAlpha, bool clearDepth, GSgfxLayerID relative, GSgfxLayerOffset offset);
};

// ---------------------------------------------------------------- externs
extern "C" {
u8 GSfsysCancel(u32 id);
s32 GSfsysReadStreaming(u32 id);
u32 GSfsysStreamGetCacheSize(void);
s32 GSfsysStreamGetData(u32 gid, u32 id, u32 dst, u32 size, u32 offset, u32 a, u32 b, u32 c);
void GSfsysStreamSetLoopFlag(u32 gid, u32 id, u8 flag);
int GSgappCreate(s32 type, u8 priority, void* arg, void (*func)());
void GSgappSetName(int id, const char* name);
void GSgfxTokenWaitForClearAndReset(u16* tokenPtr);
void GSgfxVideoGetEFBSize(u16* w, u16* h);
void* GSmemAllocAlignFromEnd(u32 size, int align);
void GSmemFree(void* ptr);
void GSscratchSetValid();
void GSscratchSetInvalid();
void GSthreadSwitch(void);
int THPInit(void);
void THPGXRestore(void);
void THPGXSetRenderLayer(GSgfxLayer* layer);
void THPGXYuv2RgbSetup(void);
s16 THPGXYuv2RgbDraw(u8* y, u8* u, u8* v, s16 x, s16 yy, s16 texW, s16 texH, s16 polyW, s16 polyH);
u32 VIGetNextField(void);
u32 VIGetTvFormat(void);
u32 OSGetTick(void);
void DCInvalidateRange(void* addr, u32 nBytes);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32 level);
void* memset(void* dst, int val, u32 n);
void (*GSgfxVideoSetVSyncCallback(void (*func)(void)))(void);
s32 GSmovieGetStatus(u32 id);
void GSmovieStop(u32 id);
}
void GSgfxRenderWaitForDrawComplete();
void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);

extern "C" {
void _movieStreamDecode(__GSmovieStreaming* s);
void _movieStreamPrepareGetData(__GSmovieStreaming* s);
void _StreamQuit(__GSmovieStreaming* s);
u8 _StreamPlay(__GSmovieStreaming* s);
void _StreamInit(__GSmovieStreaming* s);
void _StreamInitFillStreamBuffer(__GSmovieStreaming* s);
}

// ---------------------------------------------------------------- data
static u8 _initFlag;
static int _movieDaemonHDL;
static u32 _maxStreaming;
static __GSmovieStreaming* _movieStreaming;
static __GSmovieStreaming* _activeMovieStreaming;
static u8 _movieValidScratch;
static void (*OldVIPostCallback)(void);
static u8 _readWaitFlag;
static s32 _readAddr;
static u32 _readOffset;
static u32 _readBytes;
static s32 _movieLayerUseCount;
static s32 _movieLayerID = -1;

static void _movieDaemon();
static void _movieBeforeRender(f32 dt);
static void _movieRender(GSgfxLayer* layer, GSgfxLayerPass pass);
static u8 _THPPlayerSetBuffer(__GSmovieStreaming* s);
static void _movieStreamTHPPlayerPrepareGetDataCallback(s32, void* arg, s32);
static void _PlayControl(u32);

// ---------------------------------------------------------------- helpers
static inline __GSmovieStreaming* _movieGetStream(u32 id) {
    __GSmovieStreaming* s;
    u32 i;
    for (i = 0; i < _maxStreaming; i++) {
        s = &_movieStreaming[i];
        if (s->state != 0 && id == s->id) {
            return s;
        }
    }
    return 0;
}

static inline __GSmovieStreaming* _movieFindActive(u32 id) {
    if (_initFlag == 0) {
        return 0;
    }
    return _movieGetStream(id);
}

static inline void _movieFreeStream(__GSmovieStreaming* s) {
    s32 level = OSDisableInterrupts();
    s->state = 0;
    s->id = 0;
    if (s->player != 0) {
        GSmemFree(s->player);
        s->player = 0;
    }
    OSRestoreInterrupts(level);
}

static inline __GSmovieStreaming* _movieGetNewStream() {
    s32 level = OSDisableInterrupts();
    __GSmovieStreaming* s = 0;
    u32 i;
    for (i = 0; i < _maxStreaming; i++) {
        s = &_movieStreaming[i];
        if (s->state == 0) {
            s->player = (THPPlayer*)GSmemAllocAlignFromEnd(sizeof(THPPlayer), 0x20);
            if (s->player == 0) {
                s = 0;
            } else {
                s->state = 1;
            }
            break;
        }
    }
    OSRestoreInterrupts(level);
    return s;
}

static inline bool _movieStreamInit(u32 id) {
    return (u8)GSfsysReadStreaming(id) != 0;
}

static inline void _movieLayerDecrementUse() {
    if (--_movieLayerUseCount == 0) {
        GSgfxLayerConfig::Remove((GSgfxLayerID)_movieLayerID);
        _movieLayerID = -1;
    }
}

static inline void _movieLayerIncrementUse() {
    if (_movieLayerUseCount == 0) {
        _movieLayerID = GSgfxLayerConfig::Add("movie", 0x2000, 0, 4, (GSgfxLayerType)0, false, false, false,
                                              (GSgfxLayerID)-1, (GSgfxLayerOffset)3);
    }
    _movieLayerUseCount++;
}

static inline bool _movieReadStart(__GSmovieStreaming* s) {
    s32 level = OSDisableInterrupts();
    bool started;
    if ((u8)GSfsysStreamGetData(s->id, 0, _readAddr, 0x8000, _readOffset,
                                (u32)_movieStreamTHPPlayerPrepareGetDataCallback, (u32)s, 0) == 1) {
        _readWaitFlag = 0;
        started = true;
    } else {
        started = false;
    }
    OSRestoreInterrupts(level);
    return started;
}

static inline void _movieStop(u32 id) {
    if (_initFlag != 0) {
        __GSmovieStreaming* s = _movieGetStream(id);
        if (s != 0) {
            THPPlayer* p;
            GSgfxRenderWaitForDrawComplete();
            if (s->tex != 0) {
                _movieLayerDecrementUse();
            }
            GSfsysCancel(s->id);
            p = s->player;
            if (p->state != 0) {
                p->internalState = 0;
                p->state = 0;
                if (p->audioExist != 0) {
                    _StreamQuit(s);
                }
                p->dvdError = 0;
                p->videoError = 0;
            }
            GSmemFree(s->mem);
            if (s == _activeMovieStreaming) {
                _activeMovieStreaming = 0;
            }
            _movieFreeStream(s);
            if (_movieValidScratch == 1) {
                u32 i;
                bool any = false;
                for (i = 0; i < _maxStreaming; i++) {
                    if (_movieStreaming[i].state != 0) {
                        any = true;
                    }
                }
                if (!any) {
                    GSscratchSetValid();
                    _movieValidScratch = 0;
                    GSgfxVideoSetVSyncCallback(OldVIPostCallback);
                    OldVIPostCallback = 0;
                }
            }
        }
    }
}

// ---------------------------------------------------------------- public API
extern "C" {

void GSmovieInit(void) {
    GSgfxRenderModule module = {0, _movieBeforeRender, _movieRender, 0, 0, 0, 0xB29A48E1};
    if (_initFlag != 1) {
        bool ok;
        u32 i;
        _maxStreaming = 4;
        _movieStreaming = (__GSmovieStreaming*)GSmemAllocAlignFromEnd(_maxStreaming * sizeof(__GSmovieStreaming), 0x20);
        if (_movieStreaming == 0) {
            ok = false;
        } else {
            for (i = 0; i < _maxStreaming; i++) {
                __GSmovieStreaming* s = &_movieStreaming[i];
                s->id = 0;
                s->state = 0;
                s->player = 0;
            }
            ok = true;
        }
        if (ok) {
            _movieDaemonHDL = GSgappCreate(1, 0x1E, 0, _movieDaemon);
            GSgappSetName(_movieDaemonHDL, "GSmovieDaemon");
            _activeMovieStreaming = 0;
            _movieValidScratch = 0;
            GSgfxRenderModuleRegister(8, &module, 0);
            _initFlag = 1;
        }
    }
}

void GSmoviePlay(u32 id, s8 onMemory, s8 loop, struct GStexture* tex) {
    if (_initFlag != 0) {
        s32 status = GSmovieGetStatus(id);
        switch (status) {
        case 2:
            if (_initFlag != 0) {
                __GSmovieStreaming* s = _movieGetStream(id);
                if (s != 0) {
                    s->player->paused = 0;
                }
            }
            break;
        default:
            if (status >= 1) {
                break;
            }
            {
            __GSmovieStreaming* s = _movieGetNewStream();
            if (s != 0) {
                THPPlayer* p;
                s->state = 1;
                s->tex = tex;
                s->id = id;
                s->mem = 0;
                s->f14 = 0;
                s->f15 = 1;
                s->loop = loop;
                s->startOffset = 0;
                s->token = 0;
                s->f1A = 0;
                p = s->player;
                memset(&p->videoInfo, 0, sizeof(THPVideoInfo));
                memset(&p->audioInfo, 0, sizeof(THPAudioInfo));
                p->open = 1;
                p->f8064 = 0;
                p->f8068 = 0;
                p->f806C = 0;
                p->f8070 = 0;
                p->thpWork = 0;
                p->state = 0;
                p->internalState = 0;
                p->playFlag = 0;
                p->audioExist = 0;
                p->dvdError = 0;
                p->videoError = 0;
                p->onMemory = onMemory;
                p->f8085 = 0;
                p->paused = 0;
                p->visible = 1;
                p->movieData = 0;
                p->initOffset = 0;
                p->initReadSize = 0;
                p->initReadFrame = 0;
                p->retraceCount = 0;
                p->prevCount = 0;
                p->curCount = 0;
                p->videoDecodeCount = 0;
                p->curAudioTrack = 0;
                p->curVideoNumber = 0;
                p->curAudioNumber = 0;
                p->f80B8 = 0;
                p->f80BA = 0;
                p->dispTextureSet = 0;
                p->playAudioBuffer = 0;
                p->f8164 = 0;
                p->f8168 = 0;
                p->f816C = 0;
                p->f81AC = 0;
                p->textureSetIndex = 0;
                p->f8214 = 0;
                p->f8218 = 0;
                p->sndStream0 = -1;
                p->sndStream1 = -1;
                p->audioWork0 = 0;
                p->audioWork1 = 0;
                memset(p->f8230, 0, 0x48);
                if (!_movieStreamInit(id)) {
                    _movieFreeStream(s);
                }
                if (s->tex != 0) {
                    _movieLayerIncrementUse();
                }
            }
            }
        }
    }
}

s32 GSmoviePlayCheck(u32 id) {
    __GSmovieStreaming* s;
    if (_initFlag == 0) {
        return 0;
    }
    s = _movieGetStream(id);
    if (s == 0) {
        return 0;
    }
    return 1;
}


s32 GSmovieGetStatus(u32 id) {
    __GSmovieStreaming* s;
    if (_initFlag == 0) {
        return -2;
    }
    s = _movieGetStream(id);
    if (s == 0) {
        return -1;
    }
    THPPlayer* p = s->player;
    if (p->paused == 1) {
        return 2;
    }
    switch (p->state) {
    case 5:
        return -2;
    case 3:
        return 0;
    default:
    case 4:
        return 1;
    }
}
}

extern "C" void GSmoviePlayWait(u32 id) {
    if (_initFlag != 0) {
        while (1) {
            __GSmovieStreaming* s = _movieGetStream(id);
            if (s == 0) {
                break;
            }
            if (s->state < 9) {
                if (s->state == 0) {
                    break;
                }
            } else if (s->state < 12) {
                break;
            }
            GSthreadSwitch();
        }
    }
}

extern "C" void GSmovieStop(u32 id) {
    _movieStop(id);
}

static inline void _moviePauseSet(u32 id, u8 v) {
    if (_initFlag != 0) {
        __GSmovieStreaming* t = _movieGetStream(id);
        if (t != 0) {
            t->player->paused = v;
        }
    }
}

extern "C" void GSmovieAllPause(void) {
    u32 i;
    for (i = 0; i < _maxStreaming; i++) {
        __GSmovieStreaming* s = &_movieStreaming[i];
        if (s->state != 0) {
            _moviePauseSet(s->id, 1);
        }
    }
}

extern "C" void GSmovieAllContinue(void) {
    u32 i;
    for (i = 0; i < _maxStreaming; i++) {
        __GSmovieStreaming* s = &_movieStreaming[i];
        if (s->state != 0) {
            _moviePauseSet(s->id, 0);
        }
    }
}

static void _movieRender(GSgfxLayer* layer, GSgfxLayerPass pass) {
    if (pass == 0) {
        __GSmovieStreaming* s;
        u32 i;
        for (i = 0; i < _maxStreaming; i++) {
            s = &_movieStreaming[i];
            if (s->state != 0) {
                THPPlayer* p = s->player;
                if (p->visible != 0) {
                    if (s->tex == 0) {
                        if (layer->id != 2) {
                            continue;
                        }
                    } else if (_movieLayerID != layer->id) {
                        continue;
                    }
                    if (p->state != 0 && p->dispTextureSet != 0) {
                        THPTextureSet* t;
                        THPGXSetRenderLayer(layer);
                        THPGXYuv2RgbSetup();
                        t = p->dispTextureSet;
                        s->token = THPGXYuv2RgbDraw(t->ytexture, t->utexture, t->vtexture, s->x, s->y,
                                                    (s16)p->videoInfo.xSize, (s16)p->videoInfo.ySize,
                                                    (s16)p->videoInfo.xSize, (s16)p->videoInfo.ySize);
                        THPGXRestore();
                    }
                    if (s->tex != 0) {
                        layer->textureCopy(pass, s->tex, false, 0, true, true, true);
                    }
                }
            }
        }
    }
}

static void _movieBeforeRender(f32 dt) {
    u8 any = 0;
    u32 i;
    for (i = 0; i < _maxStreaming; i++) {
        __GSmovieStreaming* s = &_movieStreaming[i];
        if (s->state != 0) {
            bool found;
            u32 id = s->id;
            if (_initFlag == 0) {
                found = false;
            } else if (_movieGetStream(id) == 0) {
                found = false;
            } else {
                found = true;
            }
            if (found) {
                any = 1;
                switch (s->player->state) {
                case 4:
                    break;
                case 3:
                case 5:
                    s->state = 10;
                    break;
                }
            }
        }
    }
    if (any == 1) {
        for (i = 0; i < _maxStreaming; i++) {
            __GSmovieStreaming* s = &_movieStreaming[i];
            if (s->state != 0) {
                THPPlayer* p = s->player;
                u32 j;
                GSgfxTokenWaitForClearAndReset(&s->token);
                for (j = 0; j < 3; j++) {
                    if (p->textureSet[j].used == 1) {
                        p->textureSet[j].used = 0;
                        p->textureSet[j].isValid = 0;
                    }
                }
            }
        }
    }
}

extern "C" void* GSmovieStreamPreFunc(u32 id) {
    __GSmovieStreaming* s;
    if (_initFlag == 0) {
        return 0;
    }
    s = _movieGetStream(id);
    if (s == 0) {
        return 0;
    }
    return s->player;
}

extern "C" void GSmovieStreamPostFunc(u32 id, u32 fileId) {
    if (_initFlag != 0) {
        __GSmovieStreaming* s = _movieGetStream(id);
        if (s != 0) {
            s->state = 3;
            GSfsysStreamSetLoopFlag(id, fileId, s->loop);
        }
    }
}

// ---------------------------------------------------------------- daemon
static inline bool _movieStreamCheckComponents(THPPlayer* p) {
    u32 i;
    p->audioExist = 0;
    for (i = 0; i < p->compInfo.numComponents; i++) {
        switch (p->compInfo.frameComp[i]) {
        case 0:
            break;
        case 1:
            p->audioExist = 1;
            break;
        default:
            return false;
        }
    }
    p->internalState = 0;
    p->state = 0;
    p->playFlag = 0;
    return true;
}

static inline u32 _THPPlayerCalcNeedMemory(THPPlayer* p) {
    u32 size;
    if (p->onMemory != 0) {
        size = (p->header.movieDataSize + 0x1F) & ~0x1F;
    } else {
        size = 0;
    }
    u32 tex = p->videoInfo.xSize * p->videoInfo.ySize;
    size += ((p->header.bufSize + 0x1F) & ~0x1F) * 10;
    size += ((tex + 0x1F) & ~0x1F) * 3;
    size += (((tex >> 2) + 0x1F) & ~0x1F) * 3;
    size += (((tex >> 2) + 0x1F) & ~0x1F) * 3;
    if (p->audioExist != 0) {
        size += ((p->header.audioMaxSamples * 4 + 0x1F) & ~0x1F) * 6;
        size += (((u32)(0.5f + (f32)(p->audioInfo.sndFrequency * 60) / 1000.0f) + 0x1F) * 2 & ~0x3F) *
                p->audioInfo.sndChannels;
    }
    return size + 0x1000;
}

static inline bool _movieStreamPrepareStart(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    bool loop = s->loop == 1;
    u8 startOffset = s->startOffset;
    if (p->state != 0) {
        return false;
    }
    p->initOffset = p->header.movieDataOffsets;
    p->initReadSize = p->header.firstFrameSize;
    p->initReadFrame = 0;
    p->f806C = p->initReadSize;
    if (p->audioExist != 0) {
        if ((s32)startOffset < 0 || startOffset >= p->audioInfo.sndNumTracks) {
            return false;
        }
        p->curAudioTrack = startOffset;
    }
    p->playFlag = loop;
    p->videoDecodeCount = 0;
    p->curVideoNumber = -1;
    p->curAudioNumber = 0;
    return true;
}

static void _movieDaemon() {
    u32 i;
    for (i = 0; i < _maxStreaming; i++) {
        __GSmovieStreaming* s = &_movieStreaming[i];
        if (s->state != 0) {
            THPPlayer* p = s->player;
            if (p->f8085 == 1) {
                p->f8085 = 0;
                _StreamPlay(s);
            }
            _movieStreamPrepareGetData(s);
            switch (s->state) {
            case 3: {
                if (p->header.version != 0x11000) {
                    _movieStop(s->id);
                    break;
                }
                if (!_movieStreamCheckComponents(s->player)) {
 // falls through to the buffer allocation with the player reset
                }
                THPPlayer* q = s->player;
                s->mem = GSmemAllocAlignFromEnd(_THPPlayerCalcNeedMemory(q), 0x20);
                if (s->mem == 0) {
                    _movieStop(s->id);
                    break;
                }
                _THPPlayerSetBuffer(s);
                if (p->audioInfo.sndNumTracks != 1) {
                    s->startOffset = OSGetTick() % p->audioInfo.sndNumTracks;
                } else {
                    s->startOffset = 0;
                }
                if (s->tex == 0) {
                    u16 w, h;
                    GSgfxVideoGetEFBSize(&w, &h);
                    s->x = (w - p->videoInfo.xSize) >> 1;
                    s->y = (h - p->videoInfo.ySize) >> 1;
                    if (_activeMovieStreaming == 0) {
                        _activeMovieStreaming = s;
                    }
                } else {
                    s->x = 0;
                    s->y = 0;
                }
                if (_movieValidScratch == 0) {
                    GSscratchSetInvalid();
                    THPInit();
                }
                _movieValidScratch = 1;
                s->state = 2;
            }
 // fall through
            case 2: {
                bool ok = _movieStreamPrepareStart(s);
                if (!ok) {
                    s->state = 10;
                    break;
                }
                if (p->onMemory != 0) {
                    _readWaitFlag = 0;
                    _readAddr = (s32)p->movieData;
                    _readOffset = 0;
                    _readBytes = 0;
                    s->state = 6;
                } else {
                    s->state = 7;
                    break;
                }
            }
 // fall through
            case 6: {
                bool started = _movieReadStart(s);
                if (started == 1) {
                    s->state = 5;
                }
                break;
            }
            case 5: {
                u32 r;
                if (_readWaitFlag == 0) {
                    r = 2;
                } else if (_readBytes >= s->player->header.movieDataSize) {
                    r = 1;
                } else {
                    r = 0;
                }
                switch (r) {
                case 1:
                    s->state = 7;
                    break;
                case 0:
                    s->state = 6;
                    break;
                }
                break;
            }
            case 7:
                _movieStreamDecode(s);
                if (s->f14 != 0) {
                    p->state = 1;
                    p->internalState = 0;
                    p->dispTextureSet = 0;
                    p->playAudioBuffer = 0;
                    if (p->audioExist != 0) {
                        _StreamInit(s);
                        _StreamInitFillStreamBuffer(s);
                    }
                    if (s->player->state == 1 || s->player->state == 4) {
                        s->player->state = 2;
                        s->player->retraceCount = -1;
                        s->player->prevCount = 0;
                        s->player->curCount = 0;
                        if (OldVIPostCallback == 0) {
                            OldVIPostCallback = GSgfxVideoSetVSyncCallback((void (*)(void))_PlayControl);
                        }
                    }
                    s->state = 9;
                }
                break;
            case 9:
                _movieStreamDecode(s);
                break;
            case 10:
                s->state = 11;
                _movieStop(s->id);
                break;
            }
        }
    }
}

static inline bool ProperTimingForStart(__GSmovieStreaming* s) {
    u32 t = s->player->videoInfo.videoType;
    if (t & 1) {
        if (VIGetNextField() == 0) {
            return true;
        }
    } else if (t & 2) {
        if (VIGetNextField() == 1) {
            return true;
        }
    } else {
        return true;
    }
    return false;
}

static inline bool ProperTimingForGettingNextFrame(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    u32 t = p->videoInfo.videoType;
    if (t & 1) {
        if (VIGetNextField() == 0) {
            return true;
        }
    } else if (t & 2) {
        if (VIGetNextField() == 1) {
            return true;
        }
    } else {
        s32 x = (s32)(100.0f * p->header.frameRate);
        if (VIGetTvFormat() == 1) {
            p->curCount = (s32)((p->retraceCount * x) / 5000);
        } else {
            p->curCount = (s32)((p->retraceCount * x) / 5994);
        }
        if (p->prevCount != p->curCount) {
            p->prevCount = p->curCount;
            return true;
        }
    }
    return false;
}

static inline THPTextureSet* _getNextUseTextureSet(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    THPTextureSet* t = &p->textureSet[p->textureSetIndex];
    if (t->isValid == 0 || t->used == 1) {
        return 0;
    }
    p->textureSetIndex++;
    if (p->textureSetIndex >= 3) {
        p->textureSetIndex = 0;
    }
    return t;
}

static void _PlayControlExec(__GSmovieStreaming* s) {
    THPTextureSet* tex;
    THPPlayer* p = s->player;
    if (p->paused != 1) {
        tex = (THPTextureSet*)-1;
        if (p->state == 2) {
            if (p->dvdError != 0 || p->videoError != 0) {
                p->internalState = 5;
                p->state = 5;
                return;
            }
            p->retraceCount++;
            if (p->retraceCount == 0) {
                if (ProperTimingForStart(s)) {
                    if (p->audioExist != 0) {
                        if (p->curVideoNumber - p->curAudioNumber <= 1) {
                            tex = _getNextUseTextureSet(s);
                            p->curVideoNumber++;
                        } else {
                            if (_StreamPlay(s) == 0) {
                                p->internalState = 5;
                                p->state = 5;
                                return;
                            }
                            p->internalState = 2;
                        }
                    } else {
                        tex = _getNextUseTextureSet(s);
                    }
                } else {
                    p->retraceCount = -1;
                }
            } else {
                if (p->audioExist != 0 && p->retraceCount == 1 && p->internalState != 2) {
                    if (_StreamPlay(s) == 0) {
                        p->internalState = 5;
                        p->state = 5;
                        return;
                    }
                    p->internalState = 2;
                }
                if (ProperTimingForGettingNextFrame(s)) {
                    if (p->audioExist != 0) {
                        if (p->curVideoNumber - p->curAudioNumber <= 1) {
                            tex = _getNextUseTextureSet(s);
                            p->curVideoNumber++;
                        }
                    } else {
                        tex = _getNextUseTextureSet(s);
                    }
                }
            }
            if (tex != 0 && tex != (THPTextureSet*)-1) {
                if (p->dispTextureSet != 0) {
                    p->dispTextureSet->used = 1;
                }
                p->dispTextureSet = tex;
            }
            if (!(p->playFlag & 1)) {
                if (p->audioExist != 0) {
                    u32 frames = p->curAudioNumber + p->initReadFrame;
                    if (frames == p->header.numFrames && p->playAudioBuffer == 0) {
                        p->internalState = 3;
                        p->state = 3;
                    }
                } else {
                    u32 n;
                    if (p->dispTextureSet != 0) {
                        n = p->dispTextureSet->frameNumber + p->initReadFrame;
                    } else {
                        n = p->initReadFrame - 1;
                    }
                    if (n == p->header.numFrames - 1 && tex == 0) {
                        p->internalState = 3;
                        p->state = 3;
                    }
                }
            }
        }
    }
}

static void _PlayControl(u32) {
    u32 i;
    if (OldVIPostCallback != 0) {
        OldVIPostCallback();
    }
    for (i = 0; i < _maxStreaming; i++) {
        if (_movieStreaming[i].state != 0) {
            _PlayControlExec(&_movieStreaming[i]);
        }
    }
}

static u8 _THPPlayerSetBuffer(__GSmovieStreaming* s) {
    u8* work;
    THPPlayer* p = s->player;
    if (p->state == 0) {
        int i;
        u32 texSize;
        u32 ySize, uvSize;
        work = (u8*)s->mem;
        if (p->onMemory != 0) {
            p->movieData = work;
            work += p->header.movieDataSize;
        }
        for (i = 0; i < 10; i++) {
            p->readBuffer[i].ptr = work;
            p->readBuffer[i].isValid = 0;
            p->readBuffer[i].b9 = 0;
            if (p->audioExist != 0) {
                p->readBuffer[i].bA = 0;
            } else {
                p->readBuffer[i].bA = 1;
            }
            p->readBuffer[i].f0C = 0;
            work += (p->header.bufSize + 0x1F) & ~0x1F;
        }
        texSize = p->videoInfo.xSize * p->videoInfo.ySize;
        ySize = (texSize + 0x1F) & ~0x1F;
        uvSize = ((texSize >> 2) + 0x1F) & ~0x1F;
        for (i = 0; i < 3; i++) {
            p->textureSet[i].ytexture = work;
            DCInvalidateRange(work, ySize);
            work += ySize;
            p->textureSet[i].utexture = work;
            DCInvalidateRange(work, uvSize);
            work += uvSize;
            p->textureSet[i].vtexture = work;
            DCInvalidateRange(work, uvSize);
            work += uvSize;
            p->textureSet[i].isValid = 0;
            p->textureSet[i].used = 0;
        }
        if (p->audioExist != 0) {
            for (i = 0; i < 6; i++) {
                p->audioBuffer[i].buffer = (s16*)work;
                p->audioBuffer[i].curPtr = (s16*)work;
                p->audioBuffer[i].validSample = 0;
                p->audioBuffer[i].pad = 0;
                work += (p->header.audioMaxSamples * 4 + 0x1F) & ~0x1F;
            }
            p->audioWork0 = (s16*)work;
            work += (((u32)(0.5f + (f32)(p->audioInfo.sndFrequency * 60) / 1000.0f) + 0x1F) * 2) & ~0x3F;
            if (p->audioInfo.sndChannels == 2) {
                p->audioWork1 = (s16*)work;
                work += (((u32)(0.5f + (f32)(p->audioInfo.sndFrequency * 60) / 1000.0f) + 0x1F) * 2) & ~0x3F;
            }
        }
        p->thpWork = work;
        return 1;
    }
    return 0;
}

static void _movieStreamTHPPlayerPrepareGetDataCallback(s32, void* arg, s32) {
    __GSmovieStreaming* s = (__GSmovieStreaming*)arg;
    THPPlayer* p = s->player;
    _readOffset += 0x8000;
    if (_readOffset >= p->header.movieDataSize) {
        _readOffset = 0;
    }
    if (_readOffset >= GSfsysStreamGetCacheSize()) {
        _readOffset = 0;
    }
    _readAddr += 0x8000;
    _readBytes += 0x8000;
    if (_readBytes >= p->header.movieDataSize) {
        _readWaitFlag = 1;
    } else {
        bool started = _movieReadStart(s);
        if (!started) {
            _readWaitFlag = 1;
        }
    }
}
