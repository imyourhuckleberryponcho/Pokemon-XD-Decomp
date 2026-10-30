#include <dolphin/types.h>
#pragma pool_strings off
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
enum ASM { ASM_draft_dummy };
struct SndStream;

struct SndStreamCh {
    u8 adpcm[0x2E];
    u8 busy[2];
    u32 filled[2];
    u32 x38;
    s32 state;
};
struct SndStream {
    SndStream* master;
    SndStream* child;
    s32 state;
    s32 stid;
    u8* buf;
    u32 bufSize;
    u32 x18;
    u32 pos;
    u32 played;
    u32 dataOfs;
    u32 gid;
    u32 fid;
    u32 sndId;
    u16 fadeTime;
    u8 unk36;
    u8 vol;
    u8 targetVol;
    u8 fadeFrame;
    u8 startVol;
    u8 right;
    u8 done;
    u8 mute;
    u8 pause;
    u8 half;
    u8 unk40[8];
    s32 frq;
    u32 dataSize;
    u32 cacheEnd;
    u8 unk54[8];
    s32 loop;
    u32 headerOfs;
    u8 unk64[0xD];
    u8 looped;
    u8 updated[2];
    u32 loopStart;
    u32 loopEnd;
    u32 endPos;
    SndStreamCh ch[2];
};

extern "C" {

extern "C" {
asm void DCFlushRange(register void* addr, register u32 nBytes);
u32 GSfsysStreamGetCacheSize(void);
u8 GSfsysStreamGetData(u32 gid, u32 id, u32 dst, u32 size, u32 offset, u32 a, u32 b, u32 c);
asm BOOL OSDisableInterrupts(void);
void OSReport(const char* msg, ...);
asm BOOL OSRestoreInterrupts(register BOOL level);
static void _sndStreamARAMUpdate(void *p0, void *p1);
u32 _sndStreamCallback(void*, u32, void*, u32, u32);
void _sndStreamCtrl(SndStream* s, u32 mode);
static void _sndStreamFadePostProcess(void *p0);
BOOL _sndStreamGetData(SndStream* s, void (*cb)());
void _sndStreamGetDataCallback_ACTIVATE(s32 result, s32 size, void* arg);
void _sndStreamGetDataCallback_EXEC_UPDATE(s32 result, s32 size, SndStream* s);
void _sndStreamGetDataCallback_START(s32 result, s32 size, SndStream* s);
static u32 _sndStreamNibble_GetHeaderPos(u32 p0);
u32 _sndStreamNibble_HeaderOFF2ON(u32 p0);
u32 _sndStreamNibble_HeaderON2OFF(u32 v);
void _sndStreamPrepareGetData(SndStream* s);
static void _sndStreamPrepareGetDataCallback(u8 result, u32 halfArg, void* arg);
static void _sndStreamPrepareGetDataCallback_Exec(SndStream* s, SndStream* master, SndStreamCh* ch, u32 offset, u8 half);
static void _sndStreamPrepareGetData_Exec(SndStream* s, SndStream* master, u8 half);
static void _sndStreamPrepareGetData_GetNewData(SndStream* s, SndStream* master, u8 half);
static void _sndStreamPrepareGetData_GetOldData(SndStream* s, SndStream* master, u8 half);
void* memcpy(void* dst, const void* src, size_t n);
void* memset(void* dst, int val, size_t n);
s32 sndStreamADPCMParameter(s32, void*);
s32 sndStreamARAMUpdate(s32, u32, u32, s32, s32);
s32 sndStreamActivate(s32);
void sndStreamDeactivate(u32 stid);
s32 sndStreamFrq(s32, s32);
s32 sndStreamMixParameterEx(s32, u8, s32, s32, s32, s32);
s32 sndStreamMixParameterVolume(s32 stid, s32 vol, s32 pan, s32 span);
struct SndDataEntry {
    u8 unk0;
    u8 vol;
    u8 unk2[10];
};
extern SndDataEntry* snd_data;
}

void _sndStreamPrepareGetData(SndStream* s) {
    BOOL level;
    SndStream* master;

    level = OSDisableInterrupts();
    if (s->master != NULL) {
        master = s->master;
    } else {
        master = s;
    }
    if (master->ch[s->right].busy[s->half] == 0) {
        _sndStreamPrepareGetData_Exec(s, master, s->half);
    }
    OSRestoreInterrupts(level);
}
}

extern "C" {
static void _sndStreamPrepareGetData_Exec(SndStream* s, SndStream* master, u8 half) {
    switch (master->ch[s->right].state) {
    case 1:
        _sndStreamPrepareGetData_GetNewData(s, master, half);
        break;
    case 3:
        _sndStreamPrepareGetData_GetOldData(s, master, half);
        break;
    }
}
}

extern "C" {
static void _sndStreamPrepareGetData_GetOldData(SndStream* s, SndStream* master, u8 half) {
    SndStreamCh* ch = &master->ch[s->right];
    ch->state = 4;
    _sndStreamPrepareGetDataCallback_Exec(s, master, ch, ch->x38, half);
}
}

extern "C" {
static void _sndStreamPrepareGetData_GetNewData(SndStream* s, SndStream* master, u8 half) {
    SndStreamCh* ch;
    s32 old;
    u8* dst;
    u32 offset;

    ch = &master->ch[s->right];
    old = ch->state;
    ch->state = 2;
    dst = s->buf + 0x10000;
    if (s->master != NULL) {
        offset = master->dataOfs + s->bufSize / 2;
    } else {
        offset = master->dataOfs;
    }
    if (master->loop == 0 && s->pos >= master->dataSize) {
        memset(dst, 0, 0x8000);
        _sndStreamPrepareGetDataCallback(0, half, s);
    } else if (!GSfsysStreamGetData(master->gid, master->fid, (u32)dst, 0x8000, offset, (u32)_sndStreamPrepareGetDataCallback, half, (u32)s)) {
        ch->state = old;
    }
}
}

extern "C" {
static void _sndStreamPrepareGetDataCallback(u8 result, u32 halfArg, void* arg) {
    SndStream* s = (SndStream*)arg;
    SndStream* master;
    SndStream* other;
    SndStreamCh* ch;
    u32 headerPos;
    u8 half;
    u32 pos;
    u32 header;
    u32 end;

    half = halfArg;

    if (s->master != NULL) {
        master = s->master;
        other = s;
    } else {
        master = s;
        other = s->child;
    }
    ch = &master->ch[s->right];
    pos = _sndStreamNibble_HeaderOFF2ON(s->pos);
    end = pos + 0x10000;
    if (master->loop == 1 && master->looped == 1 && (header = master->headerOfs - 2, pos <= header) && header < end) {
        headerPos = _sndStreamNibble_GetHeaderPos((u16)header);
    } else {
        headerPos = 0;
    }
    s->pos += s->x18 / 2;
    if (master->loop == 1 && s->pos >= master->loopEnd) {
        s->pos = master->loopStart;
        master->looped = 1;
    }
    s->done = 1;
    if (master->done && other->done) {
        master->dataOfs += master->bufSize;
        if (master->dataOfs >= (master->cacheEnd & 0x3FFFFFFE)) {
            master->dataOfs = 0;
        } else if (master->dataOfs >= GSfsysStreamGetCacheSize()) {
            master->dataOfs = 0;
        }
        other->done = 0;
        master->done = 0;
    }
    _sndStreamPrepareGetDataCallback_Exec(s, master, ch, headerPos, half);
}
}

extern "C" {
static void _sndStreamPrepareGetDataCallback_Exec(SndStream* s, SndStream* master, SndStreamCh* ch, u32 offset, u8 half) {
    u32 len = 0x8000 - offset;
    u8* src = s->buf + 0x10000;
    src += offset;
    u32 cur = ch->filled[half];
    u8* dst;

    if (half) {
        dst = s->buf + (s->bufSize / 2 + cur);
    } else {
        dst = s->buf + cur;
    }
    if (cur + len > 0x8000) {
        len = 0x8000 - cur;
        ch->x38 = offset + len;
        ch->state = 3;
    } else {
        ch->x38 = 0;
        ch->state = 1;
    }
    memcpy(dst, src, len);
    ch->filled[half] += len;
    if (ch->filled[half] >= 0x8000) {
        ch->filled[half] = 0;
        ch->busy[half] = 1;
    } else {
        ch->busy[half] = 0;
    }
}
}

extern "C" {
static u32 _sndStreamNibble_GetHeaderPos(u32 p0) {
    f64 scale = 0.5;
    return (u32)(p0 * scale) & 0xFFFFFFF8;
}
}

extern "C" {
u32 _sndStreamNibble_HeaderOFF2ON(u32 p0) {
    f64 scale = 1.1428571428571428;
    return (u32)(p0 * scale);
}
}

extern "C" {
u32 _sndStreamNibble_HeaderON2OFF(u32 p0) {
    f64 scale = 0.875;
    return (u32)(p0 * scale);
}
}

extern "C" {
u32 _sndStreamCallback(void* buf1, u32 len1, void* buf2, u32 len2, u32 user) {
    SndStream* s = (SndStream*)user;
    SndStream* master;
    SndStream* other;
    f32 vol;

    if (s->master != NULL) {
        master = s->master;
        other = s;
    } else {
        master = s;
        other = s->child;
    }
    if (buf1 == NULL && buf2 == NULL && len1 == 0 && len2 == 0) {
        OSReport("--- Drop Stream Voice!! ---\n");
        master->state = 0xD;
        other->state = 0xD;
        return 0;
    }
    if (s->vol != s->targetVol) {
        if (s->fadeTime == 0) {
            s->vol = s->targetVol;
            _sndStreamFadePostProcess(s);
        } else {
            f32 target;
            f32 step;
            target = s->targetVol;
            step = (target - s->startVol) / s->fadeTime;
            vol = s->startVol;
            step *= (s->fadeFrame++ * 20);
            vol += step;
            if (step > 0.0f && vol >= target) {
                vol = target;
                _sndStreamFadePostProcess(s);
            } else if (step < 0.0f && vol <= target) {
                vol = target;
                _sndStreamFadePostProcess(s);
            }
            s->vol = vol;
        }
    }
    if (s->mute == 1 || s->pause == 1) {
        sndStreamMixParameterVolume(s->stid, 0, 0, 0);
    } else {
        sndStreamMixParameterVolume(s->stid, s->vol * (snd_data[s->sndId].vol / 128.0f), 0, 0);
    }
    if (s->state != 9) {
        return 0;
    }
    if (master->loop == 0 && master->ch[0].busy[master->half] == 1 && master->ch[1].busy[other->half] == 1 &&
        len1 + (len2 + s->played) >= master->endPos) {
        sndStreamDeactivate(master->stid);
        master->state = 0xA;
        sndStreamDeactivate(other->stid);
        other->state = 0xA;
        return 0;
    }
    if (len1 + len2 < s->x18 / 2) {
        return 0;
    }
    if (master->ch[0].busy[master->half] == 1 && master->ch[1].busy[other->half] == 1) {
        DCFlushRange(master->half ? master->buf + master->bufSize / 2 : master->buf, master->bufSize / 2);
        _sndStreamARAMUpdate(master, &master->ch[master->right]);
        master->updated[master->right] = 1;
        master->played += s->x18 / 2;
        if (master->loop == 1 && master->played >= master->loopEnd) {
            master->played = master->loopStart;
        }
        DCFlushRange(other->half ? other->buf + other->bufSize / 2 : other->buf, other->bufSize / 2);
        _sndStreamARAMUpdate(other, &master->ch[other->right]);
        master->updated[other->right] = 1;
        other->played += s->x18 / 2;
        if (master->loop == 1 && other->played >= master->loopEnd) {
            other->played = master->loopStart;
        }
    }
    if (master->updated[s->right] == 1) {
        master->updated[s->right] = 0;
        return s->x18 / 2;
    }
    return 0;
}
}

extern "C" {
static void _sndStreamFadePostProcess(void *p0) {
    _sndStreamCtrl((SndStream*)((SndStream *) p0), (u32) M2C_FIELD(p0, u8 *, 0x36));
}
}

extern "C" {
void _sndStreamCtrl(SndStream* p0, u32 p1) {
    switch ((s32) (u8) p1) {
    case 1:
        M2C_FIELD(p0, s32 *, 8) = 0xA;
        return;
    case 2:
        M2C_FIELD(p0, s8 *, 0x3D) = 1;
        return;
    case 3:
        M2C_FIELD(p0, s8 *, 0x3D) = 1;
        return;
    default:
    case 0:
        M2C_FIELD(p0, s8 *, 0x3D) = 0;
        return;
    }
}
}

extern "C" {
BOOL _sndStreamGetData(SndStream* s, void (*cb)()) {
    BOOL level;
    SndStream* master;
    u8* buf;

    level = OSDisableInterrupts();
    if (s->master != NULL) {
        master = s->master;
    } else {
        master = s;
    }
    if (master->ch[s->right].busy[s->half] == 0) {
        OSRestoreInterrupts(level);
        return FALSE;
    }
    if (s->half) {
        buf = s->buf + s->bufSize / 2;
    } else {
        buf = s->buf;
    }
    DCFlushRange(buf, s->bufSize / 2);
    if (cb != NULL) {
        ((void (*)(s32, s32, SndStream*))cb)(0, 0, s);
    }
    OSRestoreInterrupts(level);
    return TRUE;
}
}

extern "C" {
void _sndStreamGetDataCallback_ACTIVATE(s32 result, s32 size, void* arg) {
    SndStream* child;
    SndStream* s = (SndStream*)arg;
    SndStream* master;
    switch (s->state) {
    case 6:
    case 7:
        if (s->master != NULL) {
            master = s->master;
            child = s;
        } else {
            master = s;
            child = s->child;
        }
        sndStreamMixParameterEx(s->stid, s->vol, s->right ? 0x7F : 0, 0, 0, 0);
        sndStreamFrq(s->stid, master->frq);
        sndStreamADPCMParameter(s->stid, &master->ch[s->right]);
        s->state = 8;
        if (master->state == 8 && child->state == 8) {
            _sndStreamARAMUpdate(master, &master->ch[master->right]);
            sndStreamActivate(master->stid);
            master->state = 9;
            _sndStreamARAMUpdate(child, &master->ch[child->right]);
            sndStreamActivate(child->stid);
            child->state = 9;
        }
        break;
    }
}
}

extern "C" {
void _sndStreamGetDataCallback_START(s32 result, s32 size, SndStream* s) {
    SndStream* master;
    SndStream* child;
    switch (s->state) {
    case 3:
    case 4:
        if (s->master != NULL) {
            master = s->master;
            child = s;
        } else {
            master = s;
            child = s->child;
        }
        s->state = 5;
        if (master->state == 5 && child->state == 5) {
            _sndStreamARAMUpdate(master, &master->ch[master->right]);
            master->state = 6;
            _sndStreamARAMUpdate(child, &master->ch[child->right]);
            child->state = 6;
        }
        break;
    }
}
extern "C" {
void _sndStreamGetDataCallback_EXEC_UPDATE(s32 result, s32 size, SndStream* s) {
    SndStream* master;
    if (s->master != NULL) {
        master = s->master;
    } else {
        master = s;
    }
    _sndStreamARAMUpdate(s, &master->ch[s->right]);
}
extern "C" {
static void _sndStreamARAMUpdate(void* p0, void* p1) {
    SndStream* s = (SndStream*)p0;
    SndStreamCh* ch = (SndStreamCh*)p1;
    sndStreamARAMUpdate(s->stid, s->half ? s->x18 / 2 : 0, s->x18 / 2, 0, 0);
    ch->busy[s->half] = 0;
    s->half ^= 1;
}
}
}
}
