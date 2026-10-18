// DRAFT (NonMatching): first complete pass of all functions.
#include <dolphin/types.h>
#include <dolphin/pad.h>
#include <dolphin/si.h>
#include <dolphin/os.h>
extern "C" {
void* memcpy(void* dst, const void* src, unsigned long n);
void* memset(void* dst, int c, unsigned long n);
}

/* XD's MSL <math.h> inlines (sqrtf with its NaN checks), not include/libc's. */
#define _MATH_H_
extern f32 __float_nan[];
#define NAN (__float_nan[0])

inline int __fpclassifyf(float x)
{
    switch ((*(s32*) &x) & 0x7F800000) {
    case 0x7F800000:
        if ((*(s32*) &x) & 0x007FFFFF) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(s32*) &x) & 0x007FFFFF) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

inline float sqrtf(float x)
{
    if (x > 0.0f) {
        double guess = __frsqrte((double) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (float) (x * guess);
    } else if (x < 0.0) {
        return NAN;
    } else if (__fpclassifyf(x) == 1) {
        return NAN;
    }
    return x;
}

extern "C" {

u8 GSgfxVideoGetVsyncRate(void);
f32 GSgfxVideoGetLastRenderTime(void);

struct InputDevice {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 subType;
    /* 0x08 */ s32 clamping;
    /* 0x0C */ s32 connState;
    /* 0x10 */ u8 smoothRate;
    /* 0x11 */ u8 smoothCount;
    /* 0x14 */ s32 smoothFunc;
    /* 0x18 */ s32 repeatState;
    /* 0x1C */ u32 repeatButtons;
    /* 0x20 */ u32 repeatOut;
    /* 0x24 */ f32 repeatTimer;
    /* 0x28 */ PADStatus raw;
    /* 0x34 */ PADStatus cur;
    /* 0x40 */ u32 prevButtons;
    /* 0x44 */ u8 prevLX;
    /* 0x45 */ u8 prevLY;
    /* 0x46 */ u8 prevRX;
    /* 0x47 */ u8 prevRY;
    /* 0x48 */ f32 deltaLX;
    /* 0x4C */ f32 deltaLY;
    /* 0x50 */ f32 deltaRX;
    /* 0x54 */ f32 deltaRY;
    /* 0x58 */ f32 smoothLX;
    /* 0x5C */ f32 smoothLY;
    /* 0x60 */ f32 smoothRX;
    /* 0x64 */ f32 smoothRY;
    /* 0x68 */ u8 outLX;
    /* 0x69 */ u8 outLY;
    /* 0x6A */ u8 outRX;
    /* 0x6B */ u8 outRY;
    /* 0x6C */ s32 motorMode;
    /* 0x70 */ u32 motorValue;
    /* 0x74 */ u32 motorFrames;
    /* 0x78 */ u8 motorStep;
};

static InputDevice _inputData[4];
static s32 _padMotorLevel[4];
static u32 _padRumble[4];
static u8 _padMotorFlag = 1;
static s32 _padCallbackCount;
static u32 _padResetBits;
static s32 _padLastVsync;
static u8 _inputInitRead;

static InputDevice* _inputFindDevice(s32 id);
static void _inputCheckConnect(void);
static void _inputPadCallback(void);
static void _inputUpdateMotors(void);
static void _inputDoRepeat(InputDevice* d);
static void _inputInitRepeat(InputDevice* d);
static void _inputUpdateSmoothing(InputDevice* d);
static void _inputDoSmoothing(InputDevice* d, s8 tx, s8 ty, u8* px, u8* py, f32* dx, f32* dy, f32* sx, f32* sy);
static void _inputDoClamping(InputDevice* d);
static void ClampCircle(u8* x, u8* y, s8 radius, s8 dead);

void GSinputClearButtonData(s32 pad, u32 buttons)
{
    InputDevice* d = _inputFindDevice(pad);
    if (d) {
        d->cur.button &= ~buttons;
    }
}

void GSinputMotorStart(s32 pad, u8 mode, u8 strength, u32 frames, u8 step)
{
    if (_padMotorFlag) {
        InputDevice* d = _inputFindDevice(pad);
        if (d && !mode) {
            d->motorMode = 1;
            d->motorValue = strength * 15;
            d->motorFrames = frames;
            d->motorStep = step;
        }
    }
}

u8 GSinputGetRightStickYData(s32 pad, s32 mode)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 0;
    }
    if (mode == 1) {
        return d->outRY;
    }
    return d->cur.substickY;
}

u8 GSinputGetRightStickXData(s32 pad, s32 mode)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 0;
    }
    if (mode == 1) {
        return d->outRX;
    }
    return d->cur.substickX;
}

u8 GSinputGetLeftStickYData(s32 pad, s32 mode)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 0;
    }
    if (mode == 1) {
        return d->outLY;
    }
    return d->cur.stickY;
}

u8 GSinputGetLeftStickXData(s32 pad, s32 mode)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 0;
    }
    if (mode == 1) {
        return d->outLX;
    }
    return d->cur.stickX;
}

u32 GSinputButtonsRepeat(s32 pad)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 0;
    }
    return d->repeatOut;
}

u32 GSinputButtonsChanged(s32 pad)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 0;
    }
    return d->cur.button ^ d->prevButtons;
}

u32 GSinputButtonsPressed(s32 pad)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 0;
    }
    return d->cur.button;
}

s32 GSinputGetSubType(s32 pad)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 2;
    }
    return d->subType;
}

void GSinputResetRightSmoothing(s32 pad, s8 x, s8 y)
{
    InputDevice* d = _inputFindDevice(pad);
    if (d) {
        d->prevRX = x;
        d->prevRY = y;
        d->smoothRX = x;
        d->smoothRY = y;
    }
}

void GSinputResetLeftSmoothing(s32 pad, s8 x, s8 y)
{
    InputDevice* d = _inputFindDevice(pad);
    if (d) {
        d->prevLX = x;
        d->prevLY = y;
        d->smoothLX = x;
        d->smoothLY = y;
    }
}

void GSinputSetSmoothingFunc(s32 pad, s32 func)
{
    InputDevice* d = _inputFindDevice(pad);
    if (d) {
        d->smoothFunc = func;
    }
}

void GSinputSetSmoothingRate(s32 pad, u8 rate)
{
    InputDevice* d = _inputFindDevice(pad);
    if (d) {
        d->smoothRate = rate;
    }
}

void GSinputSetClamping(s32 pad, s32 mode)
{
    InputDevice* d = _inputFindDevice(pad);
    if (d) {
        d->clamping = mode;
    }
}

s32 GSinputIsConnected(s32 pad)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 0;
    }
    if (d->connState == 0) {
        return 1;
    }
    return 0;
}

s32 GSinputRead(s32 pad)
{
    InputDevice* d = _inputFindDevice(pad);
    if (!d) {
        return 2;
    }
    d->prevButtons = d->cur.button;
    BOOL ints = OSDisableInterrupts();
    memcpy(&d->cur, &d->raw, sizeof(PADStatus));
    OSRestoreInterrupts(ints);
    if (_inputInitRead) {
        _inputCheckConnect();
        if (_padResetBits) {
            PADReset(_padResetBits);
        }
        _inputInitRead = 0;
    }
    _inputUpdateSmoothing(d);
    _inputDoClamping(d);
    _inputDoRepeat(d);
    return d->connState;
}

void GSinputReadEnd(void)
{
    _inputInitRead = 0;
}

void GSinputReadStart(void)
{
    _inputInitRead = 1;
}

static void _inputCheckConnect(void)
{
    s32 i;
    _padResetBits = 0;
    for (i = 0; i < 4; i++) {
        InputDevice* d = _inputFindDevice(i + 1);
        if (d) {
            u32 mask;
            s32 type;
            BOOL ints;
            ints = OSDisableInterrupts();
            mask = 0x80000000 >> i;
            type = SIProbe(i);
            OSRestoreInterrupts(ints);
            switch (type) {
            case 0x9000000:
            case 0x8b100000:
                d->subType = 0;
                if ((s8) d->cur.err == -1) {
                    _padResetBits |= mask;
                    d->raw.err = -2;
                    d->connState = 3;
                } else {
                    d->connState = 0;
                }
                break;
            default:
                d->connState = 3;
                d->subType = 2;
                d->raw.err = -1;
                break;
            }
        }
    }
}

s32 GSinputOpen(s32 mode)
{
    InputDevice* d = _inputFindDevice(0);
    if (!d) {
        return 4;
    }
    switch (mode) {
    case 1:
    case 2:
    case 3:
    case 4:
        d->id = mode;
        break;
    default:
        return 1;
    }
    return 0;
}

void GSinputInit(void)
{
    s32 i;
    _padCallbackCount = 0;
    _padResetBits = 0xf0000000;
    _padLastVsync = 0;
    for (i = 0; i < 4; i++) {
        _inputData[i].id = 0;
        _inputData[i].clamping = 0;
        _inputData[i].connState = 3;
        _inputData[i].smoothRate = 0;
        _inputData[i].smoothFunc = 0;
        _inputData[i].prevButtons = 0;
        memset(&_inputData[i].raw, 0, sizeof(PADStatus));
        memset(&_inputData[i].cur, 0, sizeof(PADStatus));
        _inputData[i].prevLX = 0;
        _inputData[i].prevLY = 0;
        _inputData[i].prevRX = 0;
        _inputData[i].prevRY = 0;
        _inputData[i].smoothLX = 0.0f;
        _inputData[i].smoothLY = 0.0f;
        _inputData[i].smoothRX = 0.0f;
        _inputData[i].smoothRY = 0.0f;
        _inputData[i].motorMode = 3;
        _inputData[i].motorValue = 0;
        _inputData[i].motorFrames = 0;
        _inputData[i].motorStep = 0;
        _inputInitRepeat(&_inputData[i]);
        _padRumble[i] = 2;
        _padMotorLevel[i] = 0;
    }
    PADSetAnalogMode(0);
    PADInit();
    PADControlAllMotors(_padRumble);
    PADRecalibrate(_padResetBits);
    SISetSamplingRate(11);
    PADSetSamplingCallback((PADSamplingCallback) _inputPadCallback);
}

static void _inputPadCallback(void)
{
    PADStatus status[4];
    s32 i;
    PADRead(status);
    for (i = 0; i < 4; i++) {
        PADStatus* s = &status[i];
        InputDevice* d = _inputFindDevice(i + 1);
        if (d && s->err != PAD_ERR_TRANSFER) {
            s->stickY = -s->stickY;
            s->substickY = -s->substickY;
            memcpy(&d->raw, s, sizeof(PADStatus));
        }
    }
    _inputUpdateMotors();
    _padCallbackCount++;
}

static void _inputUpdateMotors(void)
{
    s32 i;
    u8 changed = 0;
    for (i = 0; i < 4; i++) {
        InputDevice* d = _inputFindDevice(i + 1);
        if (d && d->connState == 0) {
            switch (d->motorMode) {
            case 1:
                if (d->motorValue > 3600) {
                    if (_padRumble[i] != 1) {
                        changed = 1;
                        _padRumble[i] = 1;
                        break;
                    }
                }
                if (d->motorValue < 100) {
                    if (_padRumble[i] != 0) {
                        _padRumble[i] = 0;
                        changed = 1;
                        break;
                    }
                }
                _padMotorLevel[i] += d->motorValue;
                if (_padMotorLevel[i] > 3600) {
                    _padMotorLevel[i] = 0;
                    if (_padRumble[i] != 1) {
                        _padRumble[i] = 1;
                        changed = 1;
                    }
                } else {
                    if (_padRumble[i] != 0) {
                        _padRumble[i] = 0;
                        changed = 1;
                    }
                }
                break;
            case 2:
                if (_padRumble[i] != 0) {
                    _padRumble[i] = 0;
                    changed = 1;
                }
                break;
            case 3:
                if (_padRumble[i] != 2) {
                    _padRumble[i] = 2;
                    changed = 1;
                }
                break;
            default:
                break;
            }
            if (d->motorFrames) {
                if (--d->motorFrames == 0) {
                    d->motorMode = 2;
                }
            }
            if (d->motorStep) {
                if (d->motorValue < d->motorStep) {
                    d->motorMode = 2;
                    d->motorStep = 0;
                } else {
                    d->motorValue -= d->motorStep;
                }
            }
        }
    }
    if (changed) {
        PADControlAllMotors(_padRumble);
    }
}

static void _inputDoRepeat(InputDevice* d)
{
    u32 cur = d->cur.button;
    u32 pressed = d->cur.button & (d->cur.button ^ d->prevButtons);
    cur &= ~0x60;
    pressed &= ~0x60;
    switch (d->repeatState) {
    case 0:
        d->repeatOut = 0;
        d->repeatState = 1;
    case 1:
        if (pressed == 0) {
            d->repeatOut = 0;
            break;
        }
        d->repeatButtons = pressed;
        d->repeatOut = pressed;
        d->repeatTimer = 0.6f;
        d->repeatState = 2;
        break;
    case 2:
        d->repeatOut = 0;
        d->repeatTimer -= GSgfxVideoGetLastRenderTime() / (f32) GSgfxVideoGetVsyncRate();
        if (cur != d->repeatButtons) {
            d->repeatState = 0;
        } else if (d->repeatTimer < 0.0f) {
            d->repeatOut = d->repeatButtons;
            d->repeatTimer = 0.1f;
        }
        break;
    }
}

static void _inputInitRepeat(InputDevice* d)
{
    d->repeatState = 0;
    d->repeatOut = 0;
    d->repeatButtons = 0;
}

static void _inputUpdateSmoothing(InputDevice* d)
{
    _inputDoSmoothing(d, d->cur.stickX, d->cur.stickY, &d->prevLX, &d->prevLY, &d->deltaLX, &d->deltaLY, &d->smoothLX, &d->smoothLY);
    _inputDoSmoothing(d, d->cur.substickX, d->cur.substickY, &d->prevRX, &d->prevRY, &d->deltaRX, &d->deltaRY, &d->smoothRX, &d->smoothRY);
}

static void _inputDoSmoothing(InputDevice* d, s8 tx, s8 ty, u8* px, u8* py, f32* dx, f32* dy, f32* sx, f32* sy)
{
    f32 ax;
    f32 ay;
    s32 ix;
    s32 iy;
    if ((s8) *px < tx - 2 || (s8) *px > tx + 2 || (s8) *py < ty - 2 || (s8) *py > ty + 2) {
        if (d->smoothFunc == 0) {
            *dx = ((f32) tx - *sx) / (f32) d->smoothRate;
            *dy = ((f32) ty - *sy) / (f32) d->smoothRate;
        } else if (d->smoothFunc == 1) {
            *dx = ((f32) tx - *sx) / ((f32) d->smoothRate * 0.25f);
            *dy = ((f32) ty - *sy) / ((f32) d->smoothRate * 0.25f);
        }
        d->smoothCount = 0;
    }
    *px = tx;
    *py = ty;
    *sx += *dx;
    *sy += *dy;
    if (d->smoothFunc == 1) {
        d->smoothCount++;
        if (d->smoothCount < d->smoothRate) {
            *dx *= 0.5f;
            *dy *= 0.5f;
            if (*dx > 0.0f) {
                ax = *dx;
            } else {
                ax = -*dx;
            }
            if (ax < 1.0f) {
                if (*dx > 0.0f) {
                    ix = 1;
                } else {
                    ix = -1;
                }
                *dx = (f32) ix;
            }
            if (*dy > 0.0f) {
                ay = *dy;
            } else {
                ay = -*dy;
            }
            if (ay < 1.0f) {
                if (*dx > 0.0f) {
                    iy = 1;
                } else {
                    iy = -1;
                }
                *dy = (f32) iy;
            }
        }
    }
    if (*dx < 0.0f) {
        if (*sx < (f32) (s8) *px) {
            *sx = (f32) (s8) *px;
        }
    } else if (*sx > (f32) (s8) *px) {
        *sx = (f32) (s8) *px;
    }
    if (*dy < 0.0f) {
        if (*sy < (f32) (s8) *py) {
            *sy = (f32) (s8) *py;
        }
    } else if (*sy > (f32) (s8) *py) {
        *sy = (f32) (s8) *py;
    }
}

static void _inputDoClamping(InputDevice* d)
{
    switch (d->clamping) {
    case 0:
        d->outLX = (s32) d->smoothLX;
        d->outLY = (s32) d->smoothLY;
        d->outRX = (s32) d->smoothRX;
        d->outRY = (s32) d->smoothRY;
        break;
    case 2: {
        u8 v[2];
        ClampCircle((u8*) &d->cur.stickX, (u8*) &d->cur.stickY, 56, 10);
        ClampCircle((u8*) &d->cur.substickX, (u8*) &d->cur.substickY, 44, 10);
        v[1] = (s32) d->smoothLX;
        v[0] = (s32) d->smoothLY;
        ClampCircle(&v[1], &v[0], 56, 10);
        d->outLX = v[1];
        d->outLY = v[0];
        v[1] = (s32) d->smoothRX;
        v[0] = (s32) d->smoothRY;
        ClampCircle(&v[1], &v[0], 44, 10);
        d->outRX = v[1];
        d->outRY = v[0];
        break;
    }
    }
}

static InputDevice* _inputFindDevice(s32 id)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        InputDevice* d = &_inputData[i];
        if (d->id == id) {
            return d;
        }
    }
    return 0;
}

static void ClampCircle(u8* x, u8* y, s8 radius, s8 dead)
{
    s32 vx = (s8) *x;
    s32 vy = (s8) *y;
    s32 sq;
    if (-dead < vx && vx < dead) {
        vx = 0;
    } else if (vx > 0) {
        vx -= dead;
    } else {
        vx += dead;
    }
    if (-dead < vy && vy < dead) {
        vy = 0;
    } else if (vy > 0) {
        vy -= dead;
    } else {
        vy += dead;
    }
    sq = vx * vx + vy * vy;
    if (radius * radius < sq) {
        s32 len = (s32) sqrtf((f32) sq);
        vx = vx * radius / len;
        vy = vy * radius / len;
    }
    *x = vx;
    *y = vy;
}

}
