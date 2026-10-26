#pragma pool_strings off
#include <dolphin/types.h>

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
    u8 videoDone;
    u8 audioDone;
    u32 filled;
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
    u8 ready;
};

struct THPPlayer {
    THPHeader header;
    THPFrameCompInfo compInfo;
    THPVideoInfo videoInfo;
    THPAudioInfo audioInfo;
    u8 cache[0x8000];
    s32 prepState;
    u32 readOffset;
    s32 partial;
    u32 nextSize;
    s32 readFrame;
    u8* thpWork;
    u8 state;
    u8 internalState;
    u8 playFlag;
    u8 audioExist;
    s32 dvdError;
    s32 videoError;
    u8 onMemory;
    u8 dropped;
    u8 paused;
    u8 visible;
    u8* movieData;
    s32 f808C;
    s32 firstFrameSize;
    s32 initReadFrame;
    s64 retraceCount;
    s32 prevCount;
    s32 curCount;
    s32 videoDecodeCount;
    s32 curAudioTrack;
    s32 curVideoNumber;
    s32 curAudioNumber;
    u16 videoBacklog;
    u16 audioDecodeCount;
    THPTextureSet* dispTextureSet;
    THPAudioBuffer* playAudioBuffer;
    THPReadBuffer readBuffer[10];
    u32 readWriteIdx;
    u32 decodeReadIdx;
    u32 audioReadIdx;
    THPTextureSet textureSet[3];
    u32 texWriteIdx;
    u32 texUseIdx;
    THPAudioBuffer audioBuffer[6];
    u32 audioDecodeIdx;
    u32 audioGetIdx;
    u32 sndStream0;
    u32 sndStream1;
    s16* audioWork0;
    s16* audioWork1;
    u8 f822C[4];
    u64 ring[5];
    s32 ringRead;
    s32 ringWrite;
    u64 played;
    u64 total;
    u64 submitted;
    u8 f8278[8];
};

struct __GSmovieStreaming {
    s32 state;
    struct GStexture* tex;
    u32 id;
    u16 x;
    u16 y;
    void* mem;
    u8 f14;
    u8 f15;
    u8 loop;
    u8 startOffset;
    u16 token;
    s16 f1A;
    THPPlayer* player;
};

extern "C" {
void DCFlushRange(void* addr, u32 nBytes);
u32 GSfsysStreamGetCacheSize(void);
s32 GSfsysStreamGetData(u32 gid, u32 id, u32 dst, u32 size, u32 offset, u32 a, u32 b, u32 c);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32 level);
void OSReport(const char* msg, ...);
u32 THPAudioDecode(s16* out, u8* in, s32 flag);
s32 THPVideoDecode(void* file, void* tileY, void* tileU, void* tileV, void* work);
void* memcpy(void* dst, const void* src, u32 n);
void* memset(void* dst, int val, u32 n);
void sndStreamARAMUpdate(u32 stid, u32 off1, u32 len1, u32 off2, u32 len2);
u8 sndStreamActivate(u32 stid);
u32 sndStreamAllocEx(u8 prio, void* buffer, u32 samples, u32 frq, u8 vol, u32 pan, u8 span, u8 auxa, u8 auxb,
                     u8 studio, u32 flags, u32 (*updateFunction)(void*, u32, void*, u32, u32), u32 user,
                     void* adpcmInfo);
void sndStreamDeactivate(u32 stid);
void sndStreamFree(u32 stid);
}

static u32 StreamUpdateCallback(void* buf1, u32 len1, void* buf2, u32 len2, u32 user);
static u32 GetAudioSample(__GSmovieStreaming* s, s16* left, s16* right, u32 count, s32* status);
static u32 _VideoDecode(__GSmovieStreaming* s, THPReadBuffer* rb, THPTextureSet* ts);
static void _movieStreamPrepareGetDataCallback(s32 error, void* arg, s32 size);
static void _movieStreamPrepareGetDataCallback_Exec(__GSmovieStreaming* s, u32 offset, u32 size);

static inline u32 _audioChunkSamples(THPPlayer* p) {
    return ((u32)(0.5f + (f32)(p->audioInfo.sndFrequency * 60) / 1000.0f) + 0x1F) & ~0x1F;
}
static inline u32 _audioChunkSamplesFreq(u32 freq) {
    return ((u32)(0.5f + (f32)(freq * 60) / 1000.0f) + 0x1F) & ~0x1F;
}

extern "C" void _StreamQuit(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    sndStreamFree(p->sndStream0);
    p->sndStream0 = (u32)-1;
    if (p->sndStream1 != (u32)-1) {
        sndStreamFree(p->sndStream1);
        p->sndStream1 = (u32)-1;
    }
}

extern "C" u8 _StreamPlay(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    if (p->sndStream0 != (u32)-1 && sndStreamActivate(p->sndStream0) != 0) {
        if (p->sndStream1 != (u32)-1) {
            if (sndStreamActivate(p->sndStream1) != 0) {
                return 1;
            }
            sndStreamDeactivate(p->sndStream0);
        } else {
            return 1;
        }
    }
    return 0;
}

static inline void FillStreamBuffer(__GSmovieStreaming* s, s16* left, s16* right, u32 count) {
    u32 remaining = count;
    THPPlayer* p = s->player;
    u64 submitted = p->submitted;
    while (1) {
        s32 status;
        u32 got = GetAudioSample(s, left, right, remaining, &status);
        submitted += got;
        if (status != 0) {
            if (status == 1) {
                THPPlayer* q;
                remaining -= got;
                left += got;
                if (right != 0) {
                    right += got;
                }
                q = s->player;
                q->ring[q->ringWrite] = submitted;
                q->ringWrite++;
                if (q->ringWrite >= 5) {
                    q->ringWrite = 0;
                }
                continue;
            }
            memset(left, 0, remaining * 2);
            if (right != 0) {
                memset(right, 0, remaining * 2);
            }
        }
        break;
    }
    p->submitted += count;
}

extern "C" s32 _StreamInitFillStreamBuffer(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    unsigned int n = _audioChunkSamples(p);
    if (p->audioInfo.sndChannels == 2) {
        FillStreamBuffer(s, p->audioWork0, p->audioWork1, n);
    } else {
        FillStreamBuffer(s, p->audioWork0, 0, n);
    }
    DCFlushRange(p->audioWork0, n * 2);
    sndStreamARAMUpdate(p->sndStream0, 0, n, 0, 0);
    if (p->audioInfo.sndChannels == 2) {
        DCFlushRange(p->audioWork1, n * 2);
        sndStreamARAMUpdate(p->sndStream1, 0, n, 0, 0);
    }
    s->f1A = 1;
    return 1;
}

extern "C" s32 _StreamInit(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    u32 freq = p->audioInfo.sndFrequency;
    u32 n = _audioChunkSamplesFreq(freq);
    p->sndStream0 = sndStreamAllocEx(0xFF, p->audioWork0, n, freq, 0x7F, p->audioInfo.sndChannels == 2 ? 0 : 0x40,
                                     0, 0, 0, 0, 0x30000, StreamUpdateCallback, (u32)s, 0);
    if (p->sndStream0 == (u32)-1) {
        return 0;
    }
    if (p->audioInfo.sndChannels == 2) {
        p->sndStream1 = sndStreamAllocEx(0xFF, p->audioWork1, n, p->audioInfo.sndFrequency, 0x7F, 0x7F, 0, 0, 0, 0,
                                         0x30000, StreamUpdateCallback, 0, 0);
        if (p->sndStream1 == (u32)-1) {
            sndStreamFree(p->sndStream0);
            return 0;
        }
    }
    p->ringRead = 0;
    p->ringWrite = 0;
    p->played = 0;
    p->total = 0;
    p->submitted = 0;
    return 1;
}

static inline void _ringAdvance(__GSmovieStreaming* s, u64 total) {
    THPPlayer* q = s->player;
    while (q->ringRead != q->ringWrite) {
        if (total < q->ring[q->ringRead]) {
            break;
        }
        q->ringRead++;
        if (q->ringRead >= 5) {
            q->ringRead = 0;
        }
        q->curAudioNumber++;
    }
}
static u32 StreamUpdateCallback(void* buf1, u32 len1, void* buf2, u32 len2, u32 user) {
    THPPlayer* p;
    __GSmovieStreaming* s = (__GSmovieStreaming*)user;
    u32 n;
    if (s == 0) {
        return 0;
    }
    p = s->player;
    if (buf1 == 0 && buf2 == 0 && len1 == 0 && len2 == 0) {
        OSReport("--- Drop Stream Voice!! ---\n");
        p->dropped = 1;
        return 0;
    }
    n = _audioChunkSamples(p) >> 1;
    p->total = p->played + len1 + len2;
    _ringAdvance(s, p->total);
    if (len1 + len2 >= n) {
        s16* left = p->audioWork0;
        if (buf1 == left) {
            if (p->audioInfo.sndChannels == 2) {
                FillStreamBuffer(s, left, p->audioWork1, n);
            } else {
                FillStreamBuffer(s, left, 0, n);
            }
            DCFlushRange(p->audioWork0, n * 2);
            sndStreamARAMUpdate(p->sndStream0, 0, n, 0, 0);
            if (p->audioInfo.sndChannels == 2) {
                DCFlushRange(p->audioWork1, n * 2);
                sndStreamARAMUpdate(p->sndStream1, 0, n, 0, 0);
            }
        } else {
            if (p->audioInfo.sndChannels == 2) {
                FillStreamBuffer(s, left + n, p->audioWork1 + n, n);
            } else {
                FillStreamBuffer(s, left + n, 0, n);
            }
            DCFlushRange(p->audioWork0 + n, n * 2);
            sndStreamARAMUpdate(p->sndStream0, n, n, 0, 0);
            if (p->audioInfo.sndChannels == 2) {
                DCFlushRange(p->audioWork1 + n, n * 2);
                sndStreamARAMUpdate(p->sndStream1, n, n, 0, 0);
            }
        }
        p->played += n;
        return n;
    }
    return 0;
}

static u32 GetAudioSample(__GSmovieStreaming* s, s16* left, s16* right, u32 count, s32* status) {
    THPPlayer* p = s->player;
    THPAudioBuffer* ab;
    s16 n;
    s16* src;
    if (p->playAudioBuffer == 0) {
        if (p->audioBuffer[p->audioGetIdx].ready == 0) {
            *status = 2;
            return 0;
        }
        p->playAudioBuffer = &p->audioBuffer[p->audioGetIdx];
    }
    ab = p->playAudioBuffer;
    n = ab->validSample;
    if (n != 0) {
        u32 i;
        n = n < count ? n : count;
        src = ab->curPtr;
        if (right == 0) {
            for (i = 0; i < n; i++) {
                *left++ = src[1];
                src += 2;
            }
        } else {
            for (i = 0; i < n; i++) {
                *right++ = src[0];
                *left++ = src[1];
                src += 2;
            }
        }
        p->playAudioBuffer->validSample -= n;
        p->playAudioBuffer->curPtr = src;
        ab = p->playAudioBuffer;
        if (ab->validSample == 0) {
            ab->ready = 0;
            p->audioGetIdx++;
            if (p->audioGetIdx >= 6) {
                p->audioGetIdx = 0;
            }
            p->playAudioBuffer = 0;
            *status = 1;
            return n;
        }
        *status = 0;
        return n;
    }
}

static inline void _movieStreamFreeReadBuffer(__GSmovieStreaming* s, THPReadBuffer* rb) {
    THPPlayer* p = s->player;
    if (rb->videoDone != 0 && rb->audioDone != 0) {
        rb->isValid = 0;
        rb->videoDone = 0;
        p->decodeReadIdx++;
        if (p->decodeReadIdx >= 10) {
            p->decodeReadIdx = 0;
        }
        if (p->audioExist != 0) {
            rb->audioDone = 0;
            p->audioReadIdx++;
            if (p->audioReadIdx >= 10) {
                p->audioReadIdx = 0;
            }
        }
    }
}

static inline void _movieStreamAudioDecode(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    if (p->audioExist != 0) {
        THPAudioBuffer* ab = &p->audioBuffer[p->audioDecodeIdx];
        if (ab->ready != 1) {
            THPReadBuffer* rb = &p->readBuffer[p->audioReadIdx];
            if (rb->isValid != 0 && rb->audioDone != 1) {
                u32 i;
                u32 n = p->compInfo.numComponents;
                s32* sizes = (s32*)(rb->ptr + 8);
                u8* data = rb->ptr + 8 + n * 4;
                for (i = 0; i < n; i++) {
                    if (p->compInfo.frameComp[i] == 1) {
                        ab->validSample = THPAudioDecode(ab->buffer, data + *sizes * p->curAudioTrack, 0);
                        ab->curPtr = ab->buffer;
                        ab->ready = 1;
                        p->audioDecodeIdx++;
                        if (p->audioDecodeIdx >= 6) {
                            p->audioDecodeIdx = 0;
                        }
                        break;
                    }
                    data += *sizes;
                    sizes++;
                }
                if (p->audioDecodeCount < 2 && !(p->playFlag & 1) &&
                    (u32)(rb->frameNumber + p->initReadFrame) == p->header.numFrames - 1) {
                    s->f14 = 1;
                }
                if (p->audioDecodeCount == 2) {
                    s->f14 = 1;
                }
                rb->audioDone = 1;
                _movieStreamFreeReadBuffer(s, rb);
                p->audioDecodeCount++;
            }
        }
    }
}

static inline void _movieStreamVideoDecode(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    if (p->audioExist != 0) {
        while (p->videoBacklog != 0) {
            THPTextureSet* ts = &p->textureSet[p->texWriteIdx];
            THPReadBuffer* rb;
            if (ts->isValid == 1) {
                break;
            }
            rb = &p->readBuffer[p->decodeReadIdx];
            if (rb->isValid == 0 || rb->videoDone == 1) {
                break;
            }
            {
                u32 n = p->header.numFrames;
                if ((u32)(rb->frameNumber + p->initReadFrame) % n == n - 1 && !(p->playFlag & 1)) {
                    _VideoDecode(s, rb, ts);
                }
            }
            rb->videoDone = 1;
            _movieStreamFreeReadBuffer(s, rb);
            p->videoBacklog--;
            p->videoDecodeCount++;
        }
    }
    if (p->audioExist == 0 || p->videoBacklog == 0) {
        THPTextureSet* ts = &p->textureSet[p->texWriteIdx];
        if (ts->isValid != 1) {
            THPReadBuffer* rb = &p->readBuffer[p->decodeReadIdx];
            if (rb->isValid != 0 && rb->videoDone != 1) {
                p->videoBacklog = _VideoDecode(s, rb, ts);
                rb->videoDone = 1;
                _movieStreamFreeReadBuffer(s, rb);
            }
        }
    }
}

extern "C" void _movieStreamDecode(__GSmovieStreaming* s) {
    _movieStreamAudioDecode(s);
    _movieStreamVideoDecode(s);
}

static u32 _VideoDecode(__GSmovieStreaming* s, THPReadBuffer* rb, THPTextureSet* ts) {
    u32 i;
    s32* sizes;
    u8* data;
    THPPlayer* p = s->player;
    u32 result = 0;
    sizes = (s32*)(rb->ptr + 8);
    data = rb->ptr + 8 + p->compInfo.numComponents * 4;
    for (i = 0; i < p->compInfo.numComponents; i++) {
        switch (p->compInfo.frameComp[i]) {
        case 0:
                s32 err = THPVideoDecode(data, ts->ytexture, ts->utexture, ts->vtexture, p->thpWork);
                p->videoError = err;
                if (err != 0) {
                    if (s->f15 == 1) {
                        s->f14 = 0;
                        s->f15 = 0;
                    }
                    p->state = 5;
                }
                ts->frameNumber = rb->frameNumber;
                ts->isValid = 1;
                p->texWriteIdx++;
                if (p->texWriteIdx >= 3) {
                    p->texWriteIdx = 0;
                }
                {
                    s32 old = p->videoDecodeCount;
                    s32 cur = p->curVideoNumber + 1;
                    result = cur > old ? cur - old : 0;
                    p->videoDecodeCount = old + 1;
                }
            break;
        }
        data += *sizes;
        sizes++;
    }
    if (s->f15 == 1) {
        s->f14 = 1;
        s->f15 = 0;
    }
    return result;
}

static inline void _movieStreamAdvanceReadOffset(__GSmovieStreaming* s) {
    THPPlayer* p = s->player;
    p->readOffset += 0x8000;
    if (p->onMemory != 0) {
        if (p->readOffset >= p->header.movieDataSize) {
            p->readOffset = 0;
        }
    } else if (p->readOffset >= p->header.movieDataSize) {
        p->readOffset = 0;
    } else if (p->readOffset >= GSfsysStreamGetCacheSize()) {
        p->readOffset = 0;
    }
}

static inline void _movieStreamPrepareGetData_GetNewData(__GSmovieStreaming* s, u32 size, int prev) {
    THPPlayer* p = s->player;
    u8* dst = p->cache;
    u32 readOffset = p->readOffset;
    p->prepState = 2;
    if (!(p->playFlag & 1) && (u32)(p->readFrame + p->initReadFrame) >= p->header.numFrames) {
        memset(dst, 0, 0x8000);
        _movieStreamAdvanceReadOffset(s);
        _movieStreamPrepareGetDataCallback_Exec(s, 0, size);
    } else if (p->onMemory != 0) {
        memcpy(dst, p->movieData + readOffset, 0x8000);
        _movieStreamAdvanceReadOffset(s);
        _movieStreamPrepareGetDataCallback_Exec(s, 0, size);
    } else if (GSfsysStreamGetData(s->id, 0, (u32)dst, 0x8000, readOffset,
                                   (u32)_movieStreamPrepareGetDataCallback, size, (u32)s) == 0) {
        p->prepState = prev;
    }
}

static inline void _movieStreamPrepareGetData_Exec(__GSmovieStreaming* s, u32 size) {
    THPPlayer* p = s->player;
    s32 st = p->prepState;
    switch (st) {
    case 2:
        break;
    case 1:
        _movieStreamPrepareGetData_GetNewData(s, size, st);
        break;
    case 3:
        _movieStreamPrepareGetDataCallback_Exec(s, p->partial, size);
        break;
    }
}

extern "C" void _movieStreamPrepareGetData(__GSmovieStreaming* s) {
    u32 size;
    THPPlayer* p = s->player;
    s32 level = OSDisableInterrupts();
    switch (s->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 10:
    case 11:
        break;
    default:
        if (p->readBuffer[p->readWriteIdx].isValid == 0) {
            size = p->nextSize;
            if (size != 0) {
                _movieStreamPrepareGetData_Exec(s, size);
            }
        }
        break;
    }
    OSRestoreInterrupts(level);
}

static void _movieStreamPrepareGetDataCallback(s32, void* size, s32 arg) {
    u32 size_c = (u32)size;
    __GSmovieStreaming* s = (__GSmovieStreaming*)arg;
    _movieStreamAdvanceReadOffset(s);
    _movieStreamPrepareGetDataCallback_Exec(s, 0, size_c);
}

static void _movieStreamPrepareGetDataCallback_Exec(__GSmovieStreaming* s, u32 offset, u32 size) {
    s32 count = 0x8000 - offset;
    u32 next;
    THPPlayer* p = s->player;
    u32 filled = p->readBuffer[p->readWriteIdx].filled;
    u8* src = p->cache + offset;
    u8* dst = p->readBuffer[p->readWriteIdx].ptr + filled;
    if (filled + count > size) {
        count = size - filled;
        p->partial = offset + count;
        p->prepState = 3;
    } else {
        p->partial = 0;
        p->prepState = 1;
    }
    memcpy(dst, src, count);
    p->readBuffer[p->readWriteIdx].filled += count;
    if (p->readBuffer[p->readWriteIdx].filled >= size) {
        p->readBuffer[p->readWriteIdx].filled = 0;
        p->readBuffer[p->readWriteIdx].isValid = 1;
        p->readBuffer[p->readWriteIdx].frameNumber = p->readFrame;
        p->nextSize = *(u32*)p->readBuffer[p->readWriteIdx].ptr;
        p->readWriteIdx++;
        if (p->readWriteIdx >= 10) {
            p->readWriteIdx = 0;
        }
        p->readFrame++;
        if ((u32)(p->readFrame + p->initReadFrame) >= p->header.numFrames) {
            if (p->playFlag & 1) {
                p->readFrame = 0;
                p->partial = 0;
                p->prepState = 1;
                p->nextSize = p->firstFrameSize;
            } else {
                p->nextSize = 0;
            }
        }
    } else {
        p->readBuffer[p->readWriteIdx].isValid = 0;
    }
    {
        THPPlayer* q = s->player;
        s32 level = OSDisableInterrupts();
    switch (s->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 10:
    case 11:
        break;
    default:
        if (q->readBuffer[q->readWriteIdx].isValid == 0) {
            next = q->nextSize;
            if (next != 0) {
                _movieStreamPrepareGetData_Exec(s, next);
            }
        }
        break;
    }
        OSRestoreInterrupts(level);
    }
}
