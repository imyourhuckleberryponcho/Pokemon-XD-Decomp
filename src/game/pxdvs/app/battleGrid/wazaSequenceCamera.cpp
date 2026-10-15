#include <dolphin/types.h>
#include <dolphin/mtx.h>

class ModelSequence {
public:
    u8 unk0[4];
    u16 id;
    u8 unk6[0x50 - 6];
    s8 size;
    u8 unk51;
    u8 sequenceId;
    u8 unk53[0x94 - 0x53];
    void* model;
    u8 unk98[4];
    u8* timings;
};

class WazaSequence {
public:
    u8 unk0[8];
    u32 flags;
};

struct wazaSequenceCameraParams {
    s32 motion;
    f32 size;
    f32 height;
    f32 rotationMin;
    f32 rotationMax;
    f32 rotationBase;
    f32 heightMin;
    f32 heightMax;
    f32 distanceMin;
    f32 distanceMax;
    f32 nearLength;
    f32 middleLength;
    f32 farLength;
};

extern "C" {
f32 HSD_Randf(void);
void* GSmodelGetBound(void* model);
extern f32 __float_nan[];
void cameraSetDistance(f32 distance);
void cameraSetHeight(f32 height);
void cameraSetRotY(f32 rotY);
void cameraUpdate(void);
void cameraGetPosition(Vec* pos);
void cameraGetTargetPos(Vec* pos);
void cameraLockYTarget(u8 on);
void cameraSetPosition(Vec* pos);
void cameraMoveRotationAcc(f32 rate);
void cameraMovePosition(int mode, Vec* pos, f32 time);
void cameraMovePositionAcc(f32 rate);
u8 GSgfxVideoGetVsyncRate(void);
void GSmodelGetRotation(void* model, Vec* rotation);
void GSboundGetMinMax(void* bound, Vec* min, Vec* max, s32, s32, s32, s32);
}

struct FOVKey {
    f32 start;
    f32 end;
    f32 startTime;
    f32 endTime;
};

FOVKey gFOVlist[2];
f32 gCurrentFOV = 30.0f;
s32 gLastMotionType = 5;
f32 gCurrentFOVTime;


extern "C" double atan2(double y, double x);

struct WazaCameraPattern {
    f32 weight;
    f32 shot0Weights[4];
    u8 shot0Params[8];
    f32 shot1Weights[4];
    u8 shot1Params[8];
};

WazaCameraPattern* wazaSequenceCameraGetPattern(bool attack, int flags);
extern "C" void cameraSetFov(f32 fov);

struct TemplateExpFileHeader {
    s32 count;
    u8 pad4[4];
    f32 times[1];
};

static inline f32 Lerp(f32 a, f32 b, f32 t) {
    return a + (b - a) * t;
}



static inline f32 WazaSqrtf(f32 x) {
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (f32)(x * guess);
    } else if (x < 0.0) {
        return *__float_nan;
    } else {
        union {
            f32 f;
            s32 i;
        } u;
        s32 cls;
        u.f = x;
        switch (u.i & 0x7F800000) {
        case 0x7F800000:
            if (u.i & 0x007FFFFF) {
                cls = 1;
            } else {
                cls = 2;
            }
            break;
        case 0:
            if (u.i & 0x007FFFFF) {
                cls = 5;
            } else {
                cls = 3;
            }
            break;
        default:
            cls = 4;
            break;
        }
        if (cls == 1) {
            return *__float_nan;
        }
    }
    return x;
}


struct FOVTiming {
    s32 count;
    u8 pad4[8];
    f32 times[3];
};

struct FOVShot {
    f32 thresholds[4];
    u8 mode;
    u8 durationMode;
    u8 flags0;
    u8 flags;
    u8 timingMode;
};


static inline void FovRange(wazaSequenceCameraParams* params, f32 radius, f32* lowFov, f32* highFov) {
    f32 span = 0.75f * params->size;
    if (params->height > span) {
        span = params->height;
    }
    *lowFov = (f32)atan2(0.6f * span, radius);
    *lowFov = 57.29578f * (2.0f * *lowFov);
    *highFov = (f32)atan2(1.8f * span, radius);
    *highFov = 57.29578f * (2.0f * *highFov);
}

static inline void FovClamp(f32* lowFov, f32* highFov) {
    if (*lowFov < 15.0f) {
        *lowFov = 15.0f;
    }
    if (*highFov < 15.0f) {
        *highFov = 15.0f;
    }
    if (*lowFov > 85.0f) {
        *lowFov = 85.0f;
    }
    if (*highFov > 85.0f) {
        *highFov = 85.0f;
    }
}

static inline void FovMix(u8 choice, f32* mixStart, f32* mixEnd) {
    u8 hasFirst;
    u8 hasSecond;

    hasFirst = false;
    hasSecond = hasFirst;
    if ((choice & 1) == 1) {
        *mixStart = 0.0f;
        hasFirst = true;
        *mixEnd = 0.2f;
    }
    if ((choice & 2) == 2) {
        if (!hasFirst) {
            *mixStart = 0.35f;
        }
        *mixEnd = 0.6f;
        hasSecond = true;
    }
    if ((choice & 4) == 4) {
        if (!hasSecond) {
            *mixStart = 0.75f;
        }
        *mixEnd = 1.0f;
    }
}


extern "C" void cameraMoveRotationXYZ(int, f32 x, f32 y, f32 z, f32 time);

void _wazaSequenceCameraDoDollyPosition(TemplateExpFileHeader* header, wazaSequenceCameraParams* params,
                                        f32 scale, bool reverse);
f32 _wazaSequenceCameraSelectDuration(u8 mode, f32* thresholds, f32 duration);

void _wazaSequenceCameraDoPosition(ModelSequence* modelSequence, wazaSequenceCameraParams* params,
                                   f32 scale, bool reverse) {
    TemplateExpFileHeader* timing =
        (TemplateExpFileHeader*)(modelSequence->timings + modelSequence->sequenceId * 0xD0);
    f32 duration;

    cameraLockYTarget((*(u32*)((u8*)timing + 8) >> 4) & 1);

    switch (params->motion) {
    case 0:
        _wazaSequenceCameraDoDollyPosition(timing, params, scale, reverse);
        break;

    case 1: {
        Vec direction;
            f32 duration = timing->times[timing->count];
        duration *= scale;
        f32 offset = 10.0f * HSD_Randf() + 25.0f;
        f32 height = 9.0f * HSD_Randf() + 1.0f;
        f32 distance = 30.0f * HSD_Randf() + 20.0f;
        f32 square;

        cameraSetDistance(distance);
        cameraSetHeight(height);
        cameraSetRotY(0.0f);
        cameraUpdate();
        cameraGetPosition(&direction);
        if (reverse) {
            direction.x += 10.0f;
        } else {
            direction.x -= 10.0f;
        }
        cameraSetPosition(&direction);
        if (reverse) {
            direction.x += offset;
        } else {
            direction.x -= offset;
        }
        cameraMovePosition(7, &direction, duration);
        cameraMovePositionAcc(duration * (0.1f / (f32)GSgfxVideoGetVsyncRate()));

        square = offset * offset + height * height;
        params->nearLength = WazaSqrtf(square);
        params->farLength = WazaSqrtf(distance * distance + square);
        params->middleLength = 0.5f * (params->nearLength + params->farLength);
        break;
    }

    case 2: {
            f32 distance;
        f32 height;
        f32 rotA;
        f32 rotB;
        f32 length;

        duration = timing->times[timing->count];
        duration *= scale;

        distance = Lerp(params->distanceMin, params->distanceMax, HSD_Randf());
        height = Lerp(params->heightMin, params->heightMax, HSD_Randf());
        if (reverse) {
            rotA = (params->rotationBase - params->rotationMin) -
                   (params->rotationMax - params->rotationMin) * HSD_Randf();
            rotB = (params->rotationBase - params->rotationMin) -
                   (params->rotationMax - params->rotationMin) * HSD_Randf();
        } else {
            rotA = (params->rotationMax - params->rotationMin) * HSD_Randf() +
                   (params->rotationBase + params->rotationMin);
            rotB = (params->rotationMax - params->rotationMin) * HSD_Randf() +
                   (params->rotationBase + params->rotationMin);
        }
        if (rotA > rotB) {
            f32 swap = rotA;
            rotA = rotB;
            rotB = swap;
        }

        cameraSetDistance(1.25f * distance);
        cameraSetHeight(height);
        cameraSetRotY(rotA);
        cameraUpdate();
        cameraMoveRotationXYZ(7, 0.0f, rotB, 0.0f, duration);
        cameraMoveRotationAcc(duration * (0.1f / (f32)GSgfxVideoGetVsyncRate()));

        length = WazaSqrtf(distance * distance + height * height);
        params->farLength = length;
        params->middleLength = length;
        params->nearLength = length;
        break;
    }

    case 3: {
        Vec direction;
            f32 distance;
        f32 height;
        f32 rotation;
        f32 length;

        duration = timing->times[timing->count];
        duration *= scale;

        distance = Lerp(params->distanceMin, params->distanceMax, HSD_Randf());
        height = Lerp(params->heightMin, params->heightMax, HSD_Randf());
        if (reverse) {
            rotation = (params->rotationBase - params->rotationMin) -
                       (params->rotationMax - params->rotationMin) * HSD_Randf();
        } else {
            rotation = (params->rotationMax - params->rotationMin) * HSD_Randf() +
                       (params->rotationBase + params->rotationMin);
        }

        cameraSetDistance(1.25f * distance);
        cameraSetHeight(height);
        cameraSetRotY(rotation);
        cameraUpdate();
        cameraGetPosition(&direction);
        cameraMovePosition(7, &direction, duration);

        length = WazaSqrtf(distance * distance + height * height);
        params->farLength = length;
        params->middleLength = length;
        params->nearLength = length;
        break;
    }

    case 4: {
        Vec direction;
            f32 rotation;
        f32 length;

        duration = timing->times[timing->count];

        if (reverse) {
            rotation = params->rotationBase - 0.47123894f;
        } else {
            rotation = 0.47123894f + params->rotationBase;
        }

        cameraSetDistance(110.0f);
        cameraSetHeight(25.0f);
        cameraSetRotY(rotation);
        cameraUpdate();
        cameraGetPosition(&direction);
        cameraMovePosition(7, &direction, duration);

        length = WazaSqrtf(110.0f * 110.0f + 25.0f * 25.0f);
        params->farLength = length;
        params->middleLength = length;
        params->nearLength = length;
        break;
    }

    case 5: {
        Vec direction;
            f32 sizeScale;
        f32 distance;
        f32 height;
        f32 rotation;
        f32 length;
        int mode = modelSequence->size;

        duration = timing->times[timing->count];
        duration *= scale;

        switch (mode) {
        case -2:
        case -1:
            sizeScale = 0.875f;
            break;
        case 1:
            sizeScale = 1.4f;
            break;
        case 2:
            sizeScale = 1.8f;
            break;
        case 3:
            sizeScale = 3.0f;
            break;
        default:
            sizeScale = 1.0f;
            break;
        }

        distance = 50.0f * sizeScale;
        height = Lerp(params->heightMin, params->heightMax, HSD_Randf());
        if (reverse) {
            rotation = params->rotationBase - 0.7853982f;
        } else {
            rotation = 0.7853982f + params->rotationBase;
        }

        cameraSetDistance(1.25f * distance);
        cameraSetHeight(height);
        cameraSetRotY(rotation);
        cameraUpdate();
        cameraGetPosition(&direction);
        cameraMovePosition(7, &direction, duration);

        length = WazaSqrtf(distance * distance + height * height);
        params->farLength = length;
        params->middleLength = length;
        params->nearLength = length;
        break;
    }
    }
}


void _wazaSequenceCameraDoDollyPosition(TemplateExpFileHeader* header, wazaSequenceCameraParams* params,
                                        f32 scale, bool reverse) {
    Vec direction;
    Vec position;
    f32 threshold0 = 0.5f;
    f32 threshold1 = 0.75f;
    f32 fullDuration;
    f32 randomDelay;
    f32 duration;
    f32 delay;
    f32 distance0;
    f32 distance1;
    f32 nearDistance;
    f32 farDistance;
    f32 height;
    f32 rotation;
    f32 chance;
    bool alternate;

    fullDuration = header->times[header->count];
    fullDuration *= scale;

    if (HSD_Randf() <= 0.7f) {
        threshold0 = 0.3f;
        threshold1 = 0.65f;
        alternate = true;
    } else {
        alternate = false;
    }

    chance = HSD_Randf();
    if (chance < threshold0) {
        randomDelay = 0.0f;
        duration = fullDuration;
    } else if (chance < threshold1) {
        randomDelay = 0.0f;
        duration = fullDuration * HSD_Randf();
        if (duration < 0.5f * fullDuration) {
            duration = 0.5f * fullDuration;
        }
    } else {
        randomDelay = fullDuration * HSD_Randf();
        if (randomDelay > 0.5f * fullDuration) {
            randomDelay = 0.5f * fullDuration;
        }
        duration = fullDuration;
    }

    distance0 = Lerp(params->distanceMin, params->distanceMax, HSD_Randf());
    nearDistance = distance0;
    distance1 = Lerp(params->distanceMin, params->distanceMax, HSD_Randf());
    farDistance = distance1;
    if (alternate) {
        if (distance0 < distance1) {
            farDistance = distance0;
            nearDistance = distance1;
        }
        height = Lerp(params->heightMin, params->heightMax, HSD_Randf());
    } else {
        if (distance0 > distance1) {
            farDistance = distance0;
            nearDistance = distance1;
        }
        height = Lerp(params->heightMin, params->heightMax, HSD_Randf());
    }

    if (reverse) {
        rotation = (params->rotationBase - params->rotationMin) -
                   (params->rotationMax - params->rotationMin) * HSD_Randf();
    } else {
        rotation = (params->rotationMax - params->rotationMin) * HSD_Randf() +
                   (params->rotationBase + params->rotationMin);
    }

    cameraSetDistance(1.25f * nearDistance);
    cameraSetHeight(height);
    cameraSetRotY(rotation);
    cameraUpdate();
    cameraGetPosition(&direction);
    cameraGetTargetPos(&position);
    PSVECSubtract(&direction, &position, &direction);
    direction.y = 0.0f;
    PSVECScale(&direction, &direction, farDistance / nearDistance);
    direction.y = height;
    PSVECAdd(&direction, &position, &direction);
    delay = duration - randomDelay;
    cameraMovePosition(7, &direction, delay);
    cameraMovePositionAcc(delay * (0.1f / (f32)GSgfxVideoGetVsyncRate()));

    params->nearLength = WazaSqrtf(nearDistance * nearDistance + height * height);
    distance0 = 0.5f * (nearDistance + farDistance);
    params->middleLength = WazaSqrtf(distance0 * distance0 + height * height);
    params->farLength = WazaSqrtf(farDistance * farDistance + height * height);
}


void _wazaSequenceCameraDoFOV(ModelSequence* modelSequence, wazaSequenceCameraParams* params,
                              int flags, f32 scale) {
    FOVTiming* timing;
    int sequenceId;
    s32 count;
    FOVShot* shot;
    int i;
    int choice;
    f32 startTime;
    f32 currentFov;
    f32 prevTime;
    f32 fov;
    f32 lowFov;
    f32 endTime;
    f32 duration;
    f32 nextTime;
    f32 highFov;
    f32 mixStart;
    f32 mixEnd;

    sequenceId = modelSequence->sequenceId;
    timing = (FOVTiming*)(modelSequence->timings + sequenceId * 0xD0);
    count = timing->count;
    mixStart = 0.0f;
    mixEnd = 1.0f;
    FovRange(params, params->nearLength, &lowFov, &highFov);
    FovClamp(&lowFov, &highFov);

    switch (params->motion) {
    case 0:
    case 4:
    case 5:
        if (flags & 0x80) {
            choice = 1;
        } else if (flags & 0x200) {
            choice = 4;
        } else {
            choice = 2;
        }
        FovMix(choice, &mixStart, &mixEnd);
        fov = mixStart + (mixEnd - mixStart) * HSD_Randf();
        fov = fov * (highFov - lowFov) + lowFov;
        gFOVlist[1].end = fov;
        gFOVlist[1].start = fov;
        gFOVlist[0].end = fov;
        gFOVlist[0].start = fov;
        gCurrentFOV = fov;
        gFOVlist[1].endTime = timing->times[0] * scale;
        gFOVlist[1].startTime = timing->times[0] * scale;
        gFOVlist[0].endTime = timing->times[0] * scale;
        gFOVlist[0].startTime = timing->times[0] * scale;
        gCurrentFOVTime = timing->times[0] * scale;
        cameraSetFov(fov);
        return;
    }

    shot = (FOVShot*)((u8*)wazaSequenceCameraGetPattern(sequenceId != 8 && sequenceId != 9, flags) + 4);

    FovMix(shot->flags0, &mixStart, &mixEnd);
    fov = mixStart + (mixEnd - mixStart) * HSD_Randf();
    fov = fov * (highFov - lowFov) + lowFov;
    gFOVlist[1].end = fov;
    gFOVlist[1].start = fov;
    gFOVlist[0].end = fov;
    gFOVlist[0].start = fov;
    gCurrentFOV = fov;
    gFOVlist[1].endTime = timing->times[0] * scale;
    gFOVlist[1].startTime = timing->times[0] * scale;
    gFOVlist[0].endTime = timing->times[0] * scale;
    gFOVlist[0].startTime = timing->times[0] * scale;
    gCurrentFOVTime = timing->times[0] * scale;
    cameraSetFov(fov);

    if (count <= 2) {
        return;
    }

    nextTime = timing->times[0];
    currentFov = fov;
    for (i = 0; i < 2; i++, shot++) {
        prevTime = nextTime;
        nextTime = timing->times[i + 1];
        if (prevTime == nextTime) {
            gFOVlist[i].startTime = prevTime * scale;
            gFOVlist[i].endTime = prevTime * scale;
            gFOVlist[i].start = currentFov;
            gFOVlist[i].end = currentFov;
        } else switch (shot->mode) {
        case 3:
        case 4:
            duration = _wazaSequenceCameraSelectDuration(shot->durationMode, shot->thresholds,
                                                         nextTime - prevTime);
            FovRange(params, ((f32*)params)[i + 11], &lowFov, &highFov);
            FovClamp(&lowFov, &highFov);
            FovMix(shot->flags, &mixStart, &mixEnd);
            fov = mixStart + (mixEnd - mixStart) * HSD_Randf();
            fov = fov * (highFov - lowFov) + lowFov;
            if (shot->timingMode == 2) {
                endTime = nextTime;
                startTime = nextTime - duration;
            } else {
                startTime = prevTime;
                endTime = prevTime + duration;
            }
            gFOVlist[i].startTime = startTime * scale;
            gFOVlist[i].endTime = endTime * scale;
            gFOVlist[i].start = currentFov;
            currentFov = fov;
            gFOVlist[i].end = fov;
            break;
        case 0:
        case 1:
        case 2:
        default:
            gFOVlist[i].startTime = prevTime * scale;
            gFOVlist[i].endTime = nextTime * scale;
            gFOVlist[i].start = currentFov;
            gFOVlist[i].end = currentFov;
            break;
        }
    }
}


void _wazaSequenceCameraGetFOVRange(wazaSequenceCameraParams* params, f32* lowFov, f32* highFov,
                                    f32 radius) {
    f32 span = 0.75f * params->size;
    if (params->height > span) {
        span = params->height;
    }
    f32 low = (f32)atan2(0.6f * span, radius);
    *lowFov = 57.29578f * (2.0f * low);
    f32 high = (f32)atan2(1.8f * span, radius);
    *highFov = 57.29578f * (2.0f * high);
    if (*lowFov < 15.0f) {
        *lowFov = 15.0f;
    }
    if (*highFov < 15.0f) {
        *highFov = 15.0f;
    }
    if (*lowFov > 85.0f) {
        *lowFov = 85.0f;
    }
    if (*highFov > 85.0f) {
        *highFov = 85.0f;
    }
}


f32 _wazaSequenceCameraSelectDuration(u8 mode, f32* thresholds, f32 duration) {
    f32 random;

    if (mode == 1) {
        return duration < 0.2f ? duration : 0.2f;
    }
    if (mode == 2) {
        return duration < 0.333f ? duration : 0.333f;
    }
    if (mode == 4) {
        return duration < 0.75f ? duration : 0.75f;
    }
    if (mode == 8) {
        return duration;
    }
    if (mode == 3) {
        random = HSD_Randf();
        return random < thresholds[0] ? (duration < 0.2f ? duration : 0.2f) : (duration < 0.333f ? duration : 0.333f);
    }
    if (mode == 5) {
        random = HSD_Randf();
        return random < thresholds[0] ? (duration < 0.2f ? duration : 0.2f) : (duration < 0.75f ? duration : 0.75f);
    }
    if (mode == 9) {
        random = HSD_Randf();
        return random < thresholds[0] ? (duration < 0.2f ? duration : 0.2f) : duration;
    }
    if (mode == 6) {
        random = HSD_Randf();
        return random < thresholds[1] ? (duration < 0.333f ? duration : 0.333f) : (duration < 0.75f ? duration : 0.75f);
    }
    if (mode == 10) {
        random = HSD_Randf();
        return random < thresholds[1] ? (duration < 0.333f ? duration : 0.333f) : duration;
    }
    if (mode == 12) {
        random = HSD_Randf();
        return random < thresholds[2] ? (duration < 0.75f ? duration : 0.75f) : duration;
    }
    if (mode == 7) {
        random = HSD_Randf();
        if (random < thresholds[0]) {
            return (duration < 0.2f ? duration : 0.2f);
        }
        if (random < thresholds[1]) {
            return (duration < 0.333f ? duration : 0.333f);
        }
        return (duration < 0.75f ? duration : 0.75f);
    }
    if (mode == 11) {
        random = HSD_Randf();
        if (random < thresholds[0]) {
            return (duration < 0.2f ? duration : 0.2f);
        }
        if (random < thresholds[1]) {
            return (duration < 0.333f ? duration : 0.333f);
        }
        return duration;
    }
    if (mode == 13) {
        random = HSD_Randf();
        if (random < thresholds[0]) {
            return (duration < 0.2f ? duration : 0.2f);
        }
        if (random < thresholds[2]) {
            return (duration < 0.75f ? duration : 0.75f);
        }
        return duration;
    }
    if (mode == 14) {
        random = HSD_Randf();
        if (random < thresholds[1]) {
            return (duration < 0.2f ? duration : 0.2f);
        }
        if (random < thresholds[2]) {
            return (duration < 0.333f ? duration : 0.333f);
        }
        return duration;
    }
    if (mode == 15) {
        random = HSD_Randf();
        if (random < thresholds[0]) {
            return (duration < 0.2f ? duration : 0.2f);
        }
        if (random < thresholds[1]) {
            return (duration < 0.2f ? duration : 0.2f);
        }
        if (random < thresholds[2]) {
            return (duration < 0.333f ? duration : 0.333f);
        }
        return duration;
    }
    return duration;
}


static inline void SelectRandomMotion(s32* motion, f32 interval, u8 m0, u8 m1, u8 m2, u8 m3) {
    for (;;) {
        f32 random;
        f32 limit;

        random = HSD_Randf();
        limit = interval;
        if (m0) {
            if (limit > random) {
                *motion = 3;
                if (gLastMotionType != *motion) {
                    break;
                }
            }
            limit += interval;
        }
        if (m1) {
            if (limit > random) {
                *motion = 0;
                if (gLastMotionType != *motion) {
                    break;
                }
            }
            limit += interval;
        }
        if (m2) {
            if (limit > random) {
                *motion = 1;
                if (gLastMotionType != *motion) {
                    break;
                }
            }
            limit += interval;
        }
        if (m3 && limit > random) {
            *motion = 2;
            if (gLastMotionType != *motion) {
                break;
            }
        }
    }
    gLastMotionType = *motion;
}

void _wazaSequenceCameraSelectMotion(ModelSequence* modelSequence, WazaSequence* wazaSequence,
                                     wazaSequenceCameraParams* cameraParams) {
    u32 flags;
    u32 option0;
    u32 option1;
    u32 option2;
    u32 option3;
    int count = 0;
    f32 interval;
    s32* motion = &cameraParams->motion;

    if (modelSequence->id == 0x13A) {
        *motion = 4;
        return;
    }

    if (wazaSequence != 0) {
        flags = wazaSequence->flags;
        if ((flags & 1) != 0) {
            *motion = 5;
            return;
        }
        option0 = (flags >> 3) & 1;
        if (option0 != 0) {
            count++;
        }
        option1 = (flags >> 4) & 1;
        if (option1 != 0) {
            count++;
        }
        option2 = (flags >> 5) & 1;
        if (option2 != 0) {
            count++;
        }
        option3 = (flags >> 6) & 1;
        if (option3 != 0) {
            count++;
        }
    }

    if (count == 0) {
        count = 4;
        option0 = 1;
        option1 = 1;
        option2 = 1;
        option3 = 1;
    } else if (count == 1) {
        if (option0) {
            *motion = 3;
        }
        if (option1) {
            *motion = 0;
        }
        if (option2) {
            *motion = 1;
        }
        if (option3) {
            *motion = 2;
        }
        gLastMotionType = *motion;
        return;
    }

    interval = 1.0f / (f32)count;
    SelectRandomMotion(motion, interval, option0, option1, option2, option3);
}


void _wazaSequenceCameraCalculateParams(ModelSequence* modelSequence, int flags,
                                        wazaSequenceCameraParams* params) {
    Vec extent;
    Vec minimum;
    Vec maximum;
    Vec rotation;
    Vec diff;
    void* model = modelSequence->model;
    void* bound = GSmodelGetBound(model);
    int mode;
    f32 sizeScale;
    f32 distanceScale;
    f32 lower;
    f32 upper;

    mode = modelSequence->size;
    GSmodelGetRotation(model, &rotation);
    params->rotationBase = rotation.y;
    switch (mode) {
    case -2:
        sizeScale = 2.4f;
        distanceScale = 0.875f;
        break;
    case -1:
        sizeScale = 1.5f;
        distanceScale = 0.875f;
        break;
    case 1:
        sizeScale = 1.25f;
        distanceScale = 1.4f;
        break;
    case 2:
        sizeScale = 1.3f;
        distanceScale = 1.8f;
        break;
    case 3:
        sizeScale = 1.5f;
        distanceScale = 3.0f;
        break;
    default:
        sizeScale = 1.2f;
        distanceScale = 1.0f;
        break;
    }

    switch (flags & 7) {
    case 1:
        params->rotationMin = 0.0f;
        params->rotationMax = 0.34906584f;
        break;
    case 2:
        params->rotationMin = 0.17453292f;
        params->rotationMax = 0.34906584f;
        break;
    case 3:
        params->rotationMin = 0.20943952f;
        params->rotationMax = 0.7330383f;
        break;
    case 4:
        if (mode > 0) {
            params->rotationMin = 0.31415927f;
            params->rotationMax = 0.83775806f;
        } else {
            params->rotationMin = 0.5235988f;
            params->rotationMax = 1.0471976f;
        }
        break;
    case 5:
        if (mode > 0) {
            params->rotationMin = 0.62831855f;
            params->rotationMax = 1.1519173f;
        } else {
            params->rotationMin = 1.0471976f;
            params->rotationMax = 1.3613569f;
        }
        break;
    case 6:
        params->rotationMin = 1.2217305f;
        params->rotationMax = 1.3962634f;
        break;
    case 7:
        params->rotationMin = 1.2217305f;
        params->rotationMax = 1.5707964f;
        break;
    default:
        if (mode > 0) {
            params->rotationMin = 0.20943952f;
            params->rotationMax = 1.0471976f;
        } else {
            params->rotationMin = 0.20943952f;
            params->rotationMax = 1.2566371f;
        }
        break;
    }

    if (flags & 0x80) {
        lower = 6.0f;
        upper = 8.0f;
        params->distanceMin = 25.0f;
        params->distanceMax = 35.0f;
    } else if (flags & 0x100) {
        params->distanceMin = 35.0f;
        params->distanceMax = 50.0f;
        lower = 6.0f;
        upper = 11.0f;
    } else if (flags & 0x200) {
        params->distanceMin = 50.0f;
        params->distanceMax = 60.0f;
        lower = 6.0f;
        upper = 20.0f;
    } else {
        params->distanceMin = upper = 20.0f;
        params->distanceMax = 60.0f;
        lower = 6.0f;
    }

    params->distanceMin *= distanceScale;
    params->distanceMax *= distanceScale;
    GSboundGetMinMax(bound, &minimum, &maximum, 0, 0, 0, 0);
    PSVECSubtract(&maximum, &minimum, &diff);
    extent = diff;
    if (extent.x < 0.0f) {
        extent.x = -extent.x;
    }
    if (extent.y < 0.0f) {
        extent.y = -extent.y;
    }
    if (extent.z < 0.0f) {
        extent.z = -extent.z;
    }
    {
        f32 size = 0.57735026f * PSVECMag(&extent);
        f32 height = extent.y;
        params->size = size;
        params->height = height;
    }
    params->heightMin = minimum.y;
    params->heightMax = maximum.y;

    if (params->heightMin < lower) {
        params->heightMin = lower;
        if (params->heightMax < lower) {
            params->heightMax = 1.5f * lower;
        }
    }
    if (params->heightMax > upper) {
        params->heightMax = upper;
        if (params->heightMin > upper) {
            params->heightMin = 0.8f * upper;
        }
    }
    params->size *= sizeScale;
    params->height *= sizeScale;
    if (params->distanceMin < 20.0f) {
        params->distanceMin = 20.0f;
    }
    if (params->distanceMax < 40.0f) {
        params->distanceMax = 40.0f;
    }
    if (params->distanceMin > 48.0f) {
        params->distanceMin = 48.0f;
    }
    if (params->distanceMax > 60.0f) {
        params->distanceMax = 60.0f;
    }
}

