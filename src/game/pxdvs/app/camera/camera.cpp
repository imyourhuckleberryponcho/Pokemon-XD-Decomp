#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec;
extern "C" void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* a_b);

struct GSvec {
    f32 x, y, z;

    GSvec() {}
    GSvec(f32 _x, f32 _y, f32 _z) {
        x = _x;
        y = _y;
        z = _z;
    }
    GSvec& operator=(const GSvec& o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
    GSvec operator-(const GSvec& o) const {
        GSvec r;
        PSVECSubtract(this, &o, &r);
        return r;
    }
    void set(f32 _x, f32 _y, f32 _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};

struct Quaternion {
    f32 x, y, z, w;
};

typedef f32 Mtx[3][4];

struct _GScamera {
    u8 unk0[0x6C];
    GSvec unk6C;
    u8 unk78[0xFC - 0x78];
    GSvec unkFC;
};

struct _GSmodel;
struct GSpart;

enum FloorStateMode {
    FLOOR_STATE_MODE_0
};

struct FloorModuleInterface {
    u8 unk0[0x18];
    const char* (*getModuleName)(void);
    void (*makeStateData)(FloorStateMode mode, void* data, unsigned long size);
    void (*restoreStateData)(FloorStateMode mode, void* data, unsigned long size);
    u32 (*getStateSize)(FloorStateMode mode);
    u32 (*getUID)(void);
};

struct FloorData {
    u8 unk0[2];
    u16 floorID;
    u8 unk4[0x3C];
};

extern "C" {
void* GSresGetResource(u32 group, u32 id);
void* GSresGetResourceAllGroup(u32 id);
void GSresRegisterResource(void* res, u32 group, u32 id, u32 flags);
u32 GSfloorGetCurrent(void);
void GScameraSetRotation(_GScamera* cam, const GSvec* rot);
void GScameraSetPosition(_GScamera* cam, const GSvec* pos);
void GScameraGetPosition(_GScamera* cam, GSvec* pos);
void GScameraLookAt(_GScamera* cam, const GSvec* up, const GSvec* target);
void GScameraGetLookAt(_GScamera* cam, GSvec* up, GSvec* target);
void GScameraGetPerspective(_GScamera* cam, f32* fov, f32* aspect, f32* near, f32* far);
void GScameraSetPerspective(_GScamera* cam, f32 fov, f32 aspect, f32 near, f32 far);
void GScameraGetFrontVector(_GScamera* cam, GSvec* front);
void GScameraGetDistanceVector(_GScamera* cam, GSvec* dist);
void GScameraSetAnimRate(_GScamera* cam, f32 rate);
void GScameraSetAnimIndex(_GScamera* cam, s32 index);
void GScameraSetAnimType(_GScamera* cam, s32 type);
void GScameraSetAnimFrame(_GScamera* cam, f32 frame);
void GScameraStartAnimation(_GScamera* cam);
void GScameraStopAnimation(_GScamera* cam);
u8 GScameraHasAnimationEnded(_GScamera* cam);
u8 GScameraIsAnimating(_GScamera* cam);
_GScamera* GScameraGetActiveCamera(void);
void GScameraSetActiveCamera(_GScamera* cam);
void GScameraLoadActiveCameraMatrix(s32 layer);
void GScameraPushState(_GScamera* cam, void* data);
void GScameraPopState(_GScamera* cam, void* data);
_GScamera* GScameraCreate(void);
u32 GSthreadGetCurrentThread(void);
void GSthreadSwitch(void);
void GSlogWrite(const char* fmt, ...);
void GSmodelGetPosition(_GSmodel* model, GSvec* pos);
GSpart* GSmodelGetPart(_GSmodel* model, s32 index);
void GSpartGetTransform(GSpart* part, GSvec* pos, GSvec* rot, GSvec* scale);
void GSpartFree(GSpart* part);
u8 floorFieldCameraDataExist(void);
u8 floorFieldCameraGetEnabled(void);
void floorFieldCameraEnable(void);
void floorFieldCameraBlend(f32 time);
f32 timeGetLastFrameSec(void);
f32 GSgfxVideoGetLastRenderTime(void);
u8 GSgfxVideoGetVsyncRate(void);
s32 GSgfxVideoGetLockFrameRate(void);
u8 dbgMenuIsOpen(void);
s8 GSinputGetLeftStickXData(s32 pad, s32 mode);
s8 GSinputGetLeftStickYData(s32 pad, s32 mode);
s8 GSinputGetRightStickXData(s32 pad, s32 mode);
s8 GSinputGetRightStickYData(s32 pad, s32 mode);
u32 GSinputButtonsPressed(s32 pad);
u32 GSinputButtonsChanged(s32 pad);
u8 menuIsCheck(s32 menuID);
void menuClose(s32 menuID);
void menuOpenCustom(s32 menuID, ...);
void menuSetPosition(s32 menuID, s32 x, s32 y);
void* GSmemAllocClr(u32 size);
void FloorModuleInterface_clear(FloorModuleInterface* iface);
s32 floorRegisterModule(s32 priority, s32, FloorModuleInterface* iface);
void EulerToQuat(const GSvec* rot, Quaternion* quat);
void PSQUATInverse(const Quaternion* src, Quaternion* inv);
void PSMTXQuat(Mtx m, const Quaternion* q);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXMultVec(const Mtx m, const GSvec* src, GSvec* dst);
void PSMTXMultVecSR(const Mtx m, const GSvec* src, GSvec* dst);
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* a_b);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
void* memset(void* dst, int c, unsigned long n);
void* memcpy(void* dst, const void* src, unsigned long n);
double atan2(double y, double x);
double sin(double x);
double cos(double x);

extern u32* floordata_number;
extern FloorData* floordata;
extern s32 _hModuleField;
extern f32 __float_nan[];
}

static inline void _cameraLerp(f32* out, const f32* start, const f32* end, f32 t) {
    f32 d = *end - *start;
    d *= t;
    *out = d + *start;
}

static inline void _cameraLerp(GSvec* out, const GSvec* start, const GSvec* end, f32 t) {
    GSvec d;
    PSVECSubtract(end, start, &d);
    PSVECScale(&d, &d, t);
    PSVECAdd(start, &d, out);
}

template <typename T>
class CameraAnimation {
public:
    CameraAnimation();

    void start(const T* from, const T* to, f32 time);
    void stop();
    bool isMove() const;
    bool update(f32 dt);
    bool updateAcceleration(f32 dt);
    void setAcceleration(f32 rate);
    const T* getCurrentPos() const;

    s32 mState;
    bool mMove;
    bool mFirst;
    bool mAccel;
    bool mAccelStart;
    bool mAccelEnd;
    f32 mSpeed;
    f32 mAccelRate;
    f32 mDecelTime;
    f32 mTime;
    f32 mCount;
    T mStart;
    T mEnd;
    T mCurrent;
};

struct CameraWork {
    u8 type;
    u8 moving;
    u8 prevType;
    u8 flags;
    GSvec position;
    GSvec rotation;
    GSvec targetPos;
    GSvec targetOfs;
    u32 targetGroup;
    u32 targetID;
    s32 targetPart;
    f32 height;
    f32 distance;
    f32 fov;
    f32 lockY;
    CameraAnimation<f32> fovAnim;
    CameraAnimation<GSvec> targetPosAnim;
    CameraAnimation<GSvec> targetOfsAnim;
    CameraAnimation<GSvec> positionAnim;
    CameraAnimation<GSvec> rotationAnim;
    u32 animGroup;
    u32 animID;
    GSvec offsetPos;
    GSvec offsetRot;
    GSvec offsetScale;
    GSvec partTargetOfs;
};

struct FloorCamera {
    s32 state;
    u32 floorID;
    f32 defHeight;
    f32 defDistance;
    f32 defRotY;
    f32 defFov;
    f32 height;
    f32 distance;
    f32 rotY;
    f32 fov;
};

static CameraWork _cameraWork;
static CameraWork _cameraWorkBak;
static GSvec gUpVec(0.0f, 1.0f, 0.0f);
FloorModuleInterface _floorModuleCamera;
CameraWork* pCamWork = &_cameraWork;
static FloorCamera* _pFloorCamera;

#define CAMERA_EPS 0.0000001f

static inline FloorCamera* _cameraGetFloorCamera() {
    u32 floor = GSfloorGetCurrent();
    for (u32 i = 0; i < *floordata_number; i++) {
        if (floor == _pFloorCamera[i].floorID) {
            return &_pFloorCamera[i];
        }
    }
    return 0;
}

static inline _GScamera* _cameraGetAnimCamera(CameraWork* work) {
    _GScamera* cam = (_GScamera*)GSresGetResource(work->animGroup, work->animID);
    if (cam == 0) {
        cam = (_GScamera*)GSresGetResourceAllGroup(work->animID);
    }
    return cam;
}

static inline u8 _cameraSetType(u8 type) {
    pCamWork->flags = 0;
    u8 old = pCamWork->type;
    if (old == type) {
        return type;
    }
    pCamWork->type = type;
    pCamWork->flags &= ~0x20;
    return old;
}

static inline void _cameraSetTarget(u32 group, u32 id) {
    pCamWork->targetGroup = group;
    pCamWork->targetID = id;
    pCamWork->targetPart = -1;
}

static inline f32 _cameraSqrtf(f32 x) {
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

static inline f32 _cameraLengthXZ(const GSvec* v) {
    return _cameraSqrtf(v->x * v->x + v->z * v->z);
}

static inline f32 _cameraGetPitch() {
    return atan2(pCamWork->height, pCamWork->distance);
}

static inline f32 _cameraGetLength() {
    return _cameraSqrtf(pCamWork->height * pCamWork->height + pCamWork->distance * pCamWork->distance);
}

static inline void _cameraLockY(f32* y) {
    CameraWork* work = pCamWork;
    if (work->flags & 0x10) {
        work->flags &= ~0x10;
        pCamWork->lockY = *y;
    } else if (work->flags & 0x08) {
        *y = work->lockY;
    }
}

static inline void _cameraUpdatePerspective(_GScamera* cam) {
    f32 fov, aspect, near, far;
    GScameraGetPerspective(cam, &fov, &aspect, &near, &far);
    GScameraSetPerspective(cam, pCamWork->fov, aspect, near, far);
}

static inline void _cameraUpdatePitch() {
    pCamWork->rotation.x = -(f32)atan2(pCamWork->height, pCamWork->distance);
}

static inline bool _cameraIsMoving() {
    if (!pCamWork->targetPosAnim.isMove() && !pCamWork->targetOfsAnim.isMove() &&
        !pCamWork->positionAnim.isMove() && !pCamWork->rotationAnim.isMove() &&
        !pCamWork->fovAnim.isMove()) {
        return false;
    }
    return true;
}

static const char* _cameraGetModuleName();
static u32 _cameraGetUID();
static u32 _cameraGetStateSize(FloorStateMode mode);
static void _cameraRestoreStateData(FloorStateMode mode, void* data, unsigned long size);
static void _cameraMakeStateData(FloorStateMode mode, void* data, unsigned long size);
static void _cameraOffsetAnimeUpdate(_GScamera* cam);
static void _cameraPadRotateUpdate(_GScamera* cam);
static void _cameraPadMoveUpdate(_GScamera* cam);

extern "C" {

void cameraStrippedDefaults(void) {
    pCamWork->offsetPos.set(0.0f, 0.0f, 0.0f);
    pCamWork->fov = 30.0f;
    pCamWork->offsetScale.set(1.0f, 1.0f, 1.0f);
}

void fn_80196A14(u8 on) {
    if (on) {
        pCamWork->flags |= 0x20;
    } else {
        pCamWork->flags &= ~0x20;
    }
}

void cameraLockYTarget(u8 on) {
    if (on) {
        pCamWork->flags |= 0x18;
    } else {
        pCamWork->flags &= ~0x08;
    }
}

void cameraSetMirrorFlag(u8 flag) {
    pCamWork->flags &= 0x18;
    pCamWork->flags |= flag;
}

void cameraSetOffsetScale(GSvec* scale) {
    pCamWork->offsetScale = *scale;
}

void cameraSetOffsetRotation(GSvec* rot) {
    pCamWork->offsetRot = *rot;
}

void cameraSetOffsetPosition(GSvec* pos) {
    pCamWork->offsetPos = *pos;
}

f32 cameraGetFov(void) {
    return pCamWork->fov;
}

f32 cameraGetRotY(void) {
    return pCamWork->rotation.y;
}

f32 cameraGetDistance(void) {
    return pCamWork->distance;
}

f32 cameraGetHeight(void) {
    return pCamWork->height;
}

void cameraSetFov(f32 fov) {
    if (fov < 3.0f) {
        fov = 3.0f;
    }
    if (fov > 120.0f) {
        fov = 120.0f;
    }
    FloorCamera* fc = _cameraGetFloorCamera();
    if (fc != 0) {
        fc->fov = fov;
    }
    pCamWork->fov = fov;
}

void cameraSetRotY(f32 rotY) {
    FloorCamera* fc = _cameraGetFloorCamera();
    if (fc != 0) {
        fc->rotY = rotY;
    }
    pCamWork->rotation.y = rotY;
}

void cameraSetDistance(f32 distance) {
    FloorCamera* fc = _cameraGetFloorCamera();
    if (fc != 0) {
        fc->distance = distance;
    }
    pCamWork->distance = distance;
}

void cameraSetHeight(f32 height) {
    FloorCamera* fc = _cameraGetFloorCamera();
    if (fc != 0) {
        fc->height = height;
    }
    pCamWork->height = height;
}

void cameraSetRotationXYZ(f32 x, f32 y, f32 z) {
    GSvec rot(x, y, z);
    _GScamera* cam = (_GScamera*)GSresGetResource(0, 0);
    pCamWork->rotation = rot;
    GScameraSetRotation(cam, &rot);
}

void cameraSetTargetPosXYZ(f32 x, f32 y, f32 z) {
    pCamWork->targetPos.set(x, y, z);
}

void cameraSetTargetOfsXYZ(f32 x, f32 y, f32 z) {
    pCamWork->targetOfs.set(x, y, z);
}

void cameraSetAnimeRate(f32 rate) {
    _GScamera* cam = _cameraGetAnimCamera(pCamWork);
    if (cam != 0) {
        GScameraSetAnimRate(cam, rate);
    }
}

void cameraResumeAnime(void) {
    _GScamera* cam = _cameraGetAnimCamera(pCamWork);
    if (cam != 0) {
        GScameraStartAnimation(cam);
    }
}

void cameraPauseAnime(void) {
    _GScamera* cam = _cameraGetAnimCamera(pCamWork);
    if (cam != 0) {
        GScameraStopAnimation(cam);
    }
}

void cameraStopAnime(void) {
    _GScamera* cam = _cameraGetAnimCamera(pCamWork);
    pCamWork->animGroup = 0;
    pCamWork->animID = 0;
    if (cam != 0) {
        GScameraStopAnimation(cam);
    }
}

s32 cameraWaitSyncAnime(u8 wait) {
    _GScamera* cam = _cameraGetAnimCamera(pCamWork);
    if (cam == 0) {
        return 0;
    }
    if (wait) {
        for (;;) {
            if (GScameraHasAnimationEnded(cam)) {
                break;
            }
            if (GSthreadGetCurrentThread() == 0) {
                GSlogWrite("cameraWaitSyncAnime()  スレッドから呼ぶようにしてください\n");
                break;
            }
            GSthreadSwitch();
        }
    } else if (!GScameraHasAnimationEnded(cam)) {
        return 1;
    }
    return 0;
}

void cameraPlayOffsetAnime(u32 group, u32 id, s32 frame, u8 loop) {
    CameraWork* work = pCamWork;
    if (work->animGroup != 0 || work->animID != 0) {
        cameraStopAnime();
    }
    u8 prev = _cameraSetType(8);
    pCamWork->animGroup = group;
    pCamWork->animID = id;
    pCamWork->prevType = prev;
    _GScamera* cam = _cameraGetAnimCamera(pCamWork);
    if (cam != 0) {
        GScameraSetAnimIndex(cam, 0);
        if (loop) {
            GScameraSetAnimType(cam, 1);
        } else {
            GScameraSetAnimType(cam, 0);
        }
        GScameraSetAnimRate(cam, 0.5f);
        GScameraSetAnimFrame(cam, frame);
        GScameraStartAnimation(cam);
        pCamWork->offsetPos.set(0.0f, 0.0f, 0.0f);
        pCamWork->offsetRot.set(0.0f, 0.0f, 0.0f);
        pCamWork->offsetScale.set(1.0f, 1.0f, 1.0f);
        GScameraSetActiveCamera((_GScamera*)GSresGetResource(0, 0));
    }
}

void cameraPlayAnime(u32 group, u32 id, u8 loop, f32 frame) {
    CameraWork* work = pCamWork;
    if (work->animGroup != 0 || work->animID != 0) {
        cameraStopAnime();
    }
    u8 prev = _cameraSetType(4);
    pCamWork->animGroup = group;
    pCamWork->animID = id;
    pCamWork->prevType = prev;
    _GScamera* cam = _cameraGetAnimCamera(pCamWork);
    if (cam != 0) {
        GScameraSetAnimIndex(cam, 0);
        if (loop) {
            GScameraSetAnimType(cam, 1);
        } else {
            GScameraSetAnimType(cam, 0);
        }
        GScameraSetAnimRate(cam, 0.5f);
        GScameraSetAnimFrame(cam, frame);
        GScameraStartAnimation(cam);
        GScameraSetActiveCamera(cam);
    }
}

void cameraMoveStop(void) {
    pCamWork->targetPosAnim.stop();
    pCamWork->targetOfsAnim.stop();
    pCamWork->positionAnim.stop();
    pCamWork->rotationAnim.stop();
    pCamWork->fovAnim.stop();
    pCamWork->moving = 0;
}

s32 cameraMoveEndCheckSpecial(u8 wait) {
    for (;;) {
        if (!pCamWork->targetPosAnim.isMove() && !pCamWork->positionAnim.isMove() &&
            !pCamWork->rotationAnim.isMove()) {
            return 0;
        }
        if (!wait) {
            break;
        }
        GSthreadSwitch();
    }
    return 1;
}

s32 cameraMoveEndCheck(u8 wait) {
    for (;;) {
        if (!pCamWork->targetPosAnim.isMove() && !pCamWork->targetOfsAnim.isMove() &&
            !pCamWork->positionAnim.isMove() && !pCamWork->rotationAnim.isMove() &&
            !pCamWork->fovAnim.isMove()) {
            return 0;
        }
        if (!wait) {
            break;
        }
        GSthreadSwitch();
    }
    return 1;
}

}

static inline void _cameraMoveTarget(u32 group, u32 id, f32 time) {
    GSvec pos(0.0f, 0.0f, 0.0f);
    _cameraSetTarget(group, id);
    _GSmodel* model = (_GSmodel*)GSresGetResource(group, id);
    if (model != 0) {
        GSmodelGetPosition(model, &pos);
    }
    if (time < CAMERA_EPS && time > -CAMERA_EPS) {
        pCamWork->targetPos = pos;
    } else {
        pCamWork->moving = 1;
        pCamWork->targetPosAnim.start(&pCamWork->targetPos, &pos, time);
    }
}

static inline void _cameraMoveRotation(GSvec* rot, f32 time) {
    if (time < CAMERA_EPS && time > -CAMERA_EPS) {
        _GScamera* cam = (_GScamera*)GSresGetResource(0, 0);
        pCamWork->rotation = *rot;
        GScameraSetRotation(cam, rot);
    } else {
        pCamWork->moving = 1;
        pCamWork->rotationAnim.start(&pCamWork->rotation, rot, time);
    }
}

static inline void _cameraMoveRotationXYZ(f32 x, f32 y, f32 z, f32 time) {
    GSvec rot(x, y, z);
    _cameraMoveRotation(&rot, time);
}

extern "C" {

void cameraReturn(f32 time, s32 wait) {
    _GScamera* cam = GScameraGetActiveCamera();
    if (floorFieldCameraDataExist()) {
        if (pCamWork->type == 3) {
            GSvec pos;
            GSvec front;
            GSvec ofs = pCamWork->targetOfs;
            GScameraGetFrontVector(cam, &front);
            PSVECScale(&front, &front, pCamWork->distance);
            GScameraGetPosition(cam, &pos);
            PSVECAdd(&pos, &front, &pos);
            PSVECSubtract(&pos, &ofs, &pos);
            pCamWork->targetPos = pos;
        }
        _cameraSetType(0);
        floorFieldCameraEnable();
        floorFieldCameraBlend(time);
    } else {
        _cameraSetType(0);
        FloorCamera* fc = _cameraGetFloorCamera();
        if (fc != 0) {
            cameraSetHeight(fc->defHeight);
            cameraSetDistance(fc->defDistance);
            cameraSetFov(fc->defFov);
        }
        _cameraMoveTarget(0, 100, time);
        _cameraMoveRotationXYZ(0.0f, fc->defRotY, 0.0f, time);
    }
    cameraMoveEndCheck(wait);
}

void cameraMoveFovAcc(f32 rate) {
    pCamWork->fovAnim.setAcceleration(rate);
}

void cameraMoveRotationAcc(f32 rate) {
    pCamWork->rotationAnim.setAcceleration(rate);
}

void cameraMovePositionAcc(f32 rate) {
    pCamWork->positionAnim.setAcceleration(rate);
}

void cameraMoveTargetOfsAcc(f32 rate) {
    pCamWork->targetOfsAnim.setAcceleration(rate);
}

void cameraMoveTargetPosAcc(f32 rate) {
    pCamWork->targetPosAnim.setAcceleration(rate);
}

void cameraMoveRotationXYZ(f32 x, f32 y, f32 z, f32 time) {
    _cameraMoveRotationXYZ(x, y, z, time);
}

void cameraMoveRotation(void* unused, GSvec* rot, f32 time) {
    _cameraMoveRotation(rot, time);
}

void cameraMoveFov(f32 fov, f32 time) {
    pCamWork->moving = 1;
    pCamWork->fovAnim.start(&pCamWork->fov, &fov, time);
}

void cameraMovePositionXYZ(f32 x, f32 y, f32 z, f32 time) {
    GSvec pos(x, y, z);
    if (time < CAMERA_EPS && time > -CAMERA_EPS) {
        pCamWork->position = pos;
    } else {
        pCamWork->moving = 1;
        pCamWork->positionAnim.start(&pCamWork->position, &pos, time);
    }
}

void cameraMovePosition(void* unused, GSvec* pos, f32 time) {
    if (time < CAMERA_EPS && time > -CAMERA_EPS) {
        pCamWork->position = *pos;
    } else {
        pCamWork->moving = 1;
        pCamWork->positionAnim.start(&pCamWork->position, pos, time);
    }
}

void cameraMoveTargetXYZ(f32 x, f32 y, f32 z, f32 time) {
    GSvec pos(x, y, z);
    if (time < CAMERA_EPS && time > -CAMERA_EPS) {
        pCamWork->targetPos = pos;
    } else {
        pCamWork->moving = 1;
        pCamWork->targetPosAnim.start(&pCamWork->targetPos, &pos, time);
    }
}

void cameraMoveTargetOfs(void* unused, GSvec* ofs, f32 time) {
    pCamWork->moving = 1;
    pCamWork->targetOfsAnim.start(&pCamWork->targetOfs, ofs, time);
}

void cameraMoveTargetPos(void* unused, GSvec* pos, f32 time) {
    if (time < CAMERA_EPS && time > -CAMERA_EPS) {
        pCamWork->targetPos = *pos;
    } else {
        pCamWork->moving = 1;
        pCamWork->targetPosAnim.start(&pCamWork->targetPos, pos, time);
    }
}

void cameraMoveTarget(void* unused, u32 group, u32 id, f32 time) {
    _cameraMoveTarget(group, id, time);
}

void cameraGetRotation(GSvec* rot) {
    *rot = pCamWork->rotation;
}

void cameraSetRotation(GSvec* rot) {
    _GScamera* cam = (_GScamera*)GSresGetResource(0, 0);
    pCamWork->rotation = *rot;
    GScameraSetRotation(cam, rot);
}

void cameraGetPosition(GSvec* pos) {
    *pos = pCamWork->position;
}

void cameraSetPosition(GSvec* pos) {
    pCamWork->position = *pos;
}

void cameraGetTargetPos(GSvec* pos) {
    *pos = pCamWork->targetPos;
}

void cameraSetTargetPos(GSvec* pos) {
    pCamWork->targetPos = *pos;
}

void cameraGetTargetOfs(GSvec* ofs) {
    *ofs = pCamWork->targetOfs;
}

void cameraSetTargetOfs(GSvec* ofs) {
    pCamWork->targetOfs = *ofs;
}

void cameraSetPartTargetOffset(GSvec* ofs) {
    pCamWork->partTargetOfs = *ofs;
}

void cameraSetTargetExt(u32 group, u32 id, s32 part) {
    pCamWork->targetGroup = group;
    pCamWork->targetID = id;
    pCamWork->targetPart = part;
    pCamWork->partTargetOfs.set(0.0f, 0.0f, 0.0f);
}

void cameraSetTarget(u32 group, u32 id) {
    _cameraSetTarget(group, id);
}

_GScamera* cameraGetActive(void) {
    _GScamera* cam = GScameraGetActiveCamera();
    if (cam != 0) {
        return cam;
    }
    cam = (_GScamera*)GSresGetResource(0, 0);
    GScameraSetActiveCamera(cam);
    return cam;
}

u8 cameraGetType(void) {
    return pCamWork->type;
}

u8 cameraSetType(u8 type) {
    pCamWork->flags = 0;
    if (pCamWork->type == type) {
        return type;
    }
    u8 old = pCamWork->type;
    pCamWork->type = type;
    pCamWork->flags &= ~0x20;
    return old;
}

}

static inline void _cameraRefreshTargetPos(CameraWork* work) {
    u32 group = work->targetGroup;
    if (group != 0 || work->targetID != 0) {
        _GSmodel* model = (_GSmodel*)GSresGetResource(group, work->targetID);
        if (model != 0) {
            GSmodelGetPosition(model, &pCamWork->targetPos);
            if (pCamWork->targetPart >= 0) {
                GSpart* part = GSmodelGetPart(model, pCamWork->targetPart);
                if (part != 0) {
                    GSpartGetTransform(part, &pCamWork->targetOfs, 0, 0);
                    PSVECSubtract(&pCamWork->targetOfs, &pCamWork->targetPos, &pCamWork->targetOfs);
                    PSVECAdd(&pCamWork->targetOfs, &pCamWork->partTargetOfs, &pCamWork->targetOfs);
                    GSpartFree(part);
                }
            }
        }
    }
}

extern "C" {

void cameraUpdate(void) {
    _GScamera* cam = (_GScamera*)GSresGetResource(0, 0);
    CameraWork* work = pCamWork;
    if (work->moving == 1) {
        f32 dt = timeGetLastFrameSec();
        if (pCamWork->targetPosAnim.update(dt)) {
            pCamWork->targetPos = *pCamWork->targetPosAnim.getCurrentPos();
        }
        if (pCamWork->targetOfsAnim.update(dt)) {
            pCamWork->targetOfs = *pCamWork->targetOfsAnim.getCurrentPos();
        }
        if (pCamWork->positionAnim.update(dt)) {
            pCamWork->position = *pCamWork->positionAnim.getCurrentPos();
        }
        if (pCamWork->rotationAnim.update(dt)) {
            pCamWork->rotation = *pCamWork->rotationAnim.getCurrentPos();
        }
        if (pCamWork->fovAnim.update(dt)) {
            pCamWork->fov = *pCamWork->fovAnim.getCurrentPos();
        }

        GSvec d;
        switch (pCamWork->type) {
        case 0:
        case 1:
        case 5:
            if (floorFieldCameraDataExist() && floorFieldCameraGetEnabled()) {
                PSVECAdd(&pCamWork->targetPos, &pCamWork->targetOfs, &d);
                PSVECSubtract(&pCamWork->position, &d, &d);
                pCamWork->height = d.y;
                pCamWork->distance = _cameraSqrtf(d.x * d.x + d.z * d.z);
            }
            break;
        case 7:
            PSVECSubtract(&pCamWork->position, &pCamWork->targetPos, &d);
            pCamWork->height = d.y;
            pCamWork->distance = _cameraSqrtf(d.x * d.x + d.z * d.z);
            if (!pCamWork->rotationAnim.isMove() && !(pCamWork->flags & 0x20)) {
                pCamWork->rotation.y = atan2(d.x, d.z);
            }
            break;
        case 2:
        case 3:
        case 4:
        case 6:
        case 8:
            break;
        }
        if (!_cameraIsMoving()) {
            pCamWork->moving = 0;
        }
    } else {
        switch (work->type) {
        case 0:
        case 1:
        case 5:
        case 7:
            _cameraRefreshTargetPos(work);
            break;
        case 4:
            cam = _cameraGetAnimCamera(work);
            if (cam == 0) {
                pCamWork->animGroup = 0;
                pCamWork->animID = 0;
                _cameraSetType(pCamWork->prevType);
                _cameraSetTarget(0, 100);
                cam = (_GScamera*)GSresGetResource(0, 0);
            }
            break;
        case 2:
        case 3:
        case 6:
        case 8:
            break;
        }
    }

    switch (pCamWork->type) {
    case 0: {
        GSvec diff;
        GSvec ofs(0.0f, pCamWork->height, pCamWork->distance);
        Mtx m;
        GSvec target;
        PSMTXRotRad(m, 'Y', pCamWork->rotation.y);
        PSMTXMultVec(m, &ofs, &ofs);
        PSVECAdd(&pCamWork->targetPos, &pCamWork->targetOfs, &target);
        PSVECAdd(&target, &ofs, &pCamWork->position);
        PSVECSubtract(&pCamWork->position, &target, &diff);
        if (diff.x < 0.00001f && diff.x > -0.00001f && diff.z < 0.00001f && diff.z > -0.00001f) {
            pCamWork->position.z += 1.0f;
        }
        _cameraLockY(&target.y);
        GScameraSetPosition(cam, &pCamWork->position);
        GScameraLookAt(cam, &gUpVec, &target);
        _cameraUpdatePitch();
        _cameraUpdatePerspective(cam);
        break;
    }
    case 1:
    case 2: {
        GSvec diff;
        GSvec target;
        PSVECAdd(&pCamWork->targetPos, &pCamWork->targetOfs, &target);
        _cameraLockY(&target.y);
        GScameraSetPosition(cam, &pCamWork->position);
        GScameraLookAt(cam, &gUpVec, &target);
        PSVECSubtract(&pCamWork->position, &target, &diff);
        pCamWork->height = diff.y;
        pCamWork->distance = _cameraLengthXZ(&diff);
        pCamWork->rotation.y = atan2(diff.x, diff.z);
        _cameraUpdatePitch();
        _cameraUpdatePerspective(cam);
        break;
    }
    case 6:
        _cameraPadMoveUpdate(cam);
        break;
    case 5:
        _cameraPadRotateUpdate(cam);
        break;
    case 3: {
        GSvec up;
        GSvec target;
        GScameraSetPosition(cam, &pCamWork->position);
        GScameraSetRotation(cam, &pCamWork->rotation);
        GScameraGetLookAt(cam, &up, &target);
        PSVECSubtract(&target, &pCamWork->targetOfs, &pCamWork->targetPos);
        _cameraUpdatePerspective(cam);
        break;
    }
    case 4:
        break;
    case 8:
        _cameraOffsetAnimeUpdate(cam);
        GScameraLoadActiveCameraMatrix(-1);
        return;
    case 7: {
        GSvec ofs(0.0f, pCamWork->height, pCamWork->distance);
        Mtx m;
        GSvec target;
        PSMTXRotRad(m, 'Y', pCamWork->rotation.y);
        PSMTXMultVec(m, &ofs, &ofs);
        PSVECAdd(&pCamWork->targetPos, &ofs, &pCamWork->position);
        PSVECAdd(&pCamWork->targetPos, &pCamWork->targetOfs, &target);
        PSMTXRotRad(m, 'Z', pCamWork->offsetRot.z);
        PSMTXMultVec(m, &gUpVec, &ofs);
        PSVECAdd(&target, &pCamWork->offsetPos, &target);
        _cameraLockY(&target.y);
        GScameraSetPosition(cam, &pCamWork->position);
        GScameraLookAt(cam, &ofs, &target);
        _cameraUpdatePitch();
        _cameraUpdatePerspective(cam);
        break;
    }
    }
    GScameraSetActiveCamera(cam);
    GScameraLoadActiveCameraMatrix(-1);
}

void cameraRefreshTargetPos(void) {
    _cameraRefreshTargetPos(pCamWork);
}

}

static void _cameraOffsetAnimeUpdate(_GScamera* cam) {
    _GScamera* anim = _cameraGetAnimCamera(pCamWork);
    Mtx m;
    Mtx m2;
    Mtx m3;
    Quaternion rq;
    GSvec pos;
    GSvec target;
    GSvec up;
    Quaternion q;
    Quaternion iq;
    Quaternion inv;
    f32 fov, aspect, near, far;
    if (anim == 0 || anim == cam || !GScameraIsAnimating(anim) || GScameraHasAnimationEnded(anim)) {
        return;
    }

    GScameraGetPerspective(anim, &fov, &aspect, &near, &far);
    GScameraGetLookAt(anim, &up, &target);
    GScameraGetPosition(anim, &pos);
    up.set(0.0f, 1.0f, 0.0f);
    pos.x *= pCamWork->offsetScale.x;
    pos.y *= pCamWork->offsetScale.y;
    pos.z *= pCamWork->offsetScale.z;
    target.x *= pCamWork->offsetScale.x;
    target.y *= pCamWork->offsetScale.y;
    target.z *= pCamWork->offsetScale.z;
    EulerToQuat(&pCamWork->offsetRot, &q);
    rq = q;
    PSMTXQuat(m, &rq);
    PSMTXMultVecSR(m, &pos, &pos);
    PSMTXQuat(m2, &rq);
    PSMTXMultVecSR(m2, &target, &target);
    PSQUATInverse(&rq, &inv);
    iq = inv;
    PSMTXQuat(m3, &iq);
    PSMTXMultVecSR(m3, &up, &up);
    if (pCamWork->flags & 1) {
        target.x *= -1.0f;
        up.x *= -1.0f;
        pos.x *= -1.0f;
    }
    if (pCamWork->flags & 2) {
        target.y *= -1.0f;
        up.y *= -1.0f;
        pos.y *= -1.0f;
    }
    if (pCamWork->flags & 4) {
        target.z *= -1.0f;
        up.z *= -1.0f;
        pos.z *= -1.0f;
    }
    PSVECAdd(&pos, &pCamWork->offsetPos, &pos);
    PSVECAdd(&target, &pCamWork->offsetPos, &target);
    _cameraLockY(&target.y);
    GScameraSetPerspective(cam, fov, aspect, near, far);
    GScameraSetPosition(cam, &pos);
    GScameraLookAt(cam, &up, &target);
    pCamWork->position = pos;
    pCamWork->targetPos = pCamWork->offsetPos;
    pCamWork->targetOfs = target - pCamWork->targetPos;
    PSVECSubtract(&pos, &target, &pos);
    pCamWork->height = pos.y;
    pCamWork->distance = _cameraLengthXZ(&pos);
    pCamWork->rotation.y = atan2(pos.x, pos.z);
    _cameraUpdatePitch();
}

static void _cameraPadRotateUpdate(_GScamera* cam) {
    GSvec target;
    if (dbgMenuIsOpen()) {
        return;
    }
    s32 rx = GSinputGetRightStickXData(1, 1) * (s32)GSgfxVideoGetLastRenderTime();
    s32 ry = GSinputGetRightStickYData(1, 1) * (s32)GSgfxVideoGetLastRenderTime();
    f32 angle = _cameraGetPitch();
    f32 dist = _cameraGetLength();
    if (GSinputButtonsPressed(1) & 0x20) {
        f32 fov = ry / 64.0f + pCamWork->fov;
        cameraSetFov(fov);
    } else if (GSinputButtonsPressed(1) & 0x40) {
        dist += ry / 64.0f;
    } else {
        angle -= ry / 4096.0f;
    }
    pCamWork->height = dist * (f32)sin(angle);
    pCamWork->distance = dist * (f32)cos(angle);
    if (pCamWork->distance < 10.0f) {
        pCamWork->distance = 10.0f;
    } else if (pCamWork->distance > 500.0f) {
        pCamWork->distance = 500.0f;
    }
    cameraSetHeight(pCamWork->height);
    cameraSetDistance(pCamWork->distance);
    GSvec ofs(0.0f, pCamWork->height, pCamWork->distance);
    pCamWork->rotation.y += rx / 2048.0f;
    cameraSetRotY(pCamWork->rotation.y);
    Mtx m;
    PSMTXRotRad(m, 'Y', pCamWork->rotation.y);
    PSMTXMultVec(m, &ofs, &ofs);
    PSVECAdd(&pCamWork->targetPos, &pCamWork->targetOfs, &target);
    PSVECAdd(&target, &ofs, &pCamWork->position);
    _cameraLockY(&target.y);
    GScameraSetPosition(cam, &pCamWork->position);
    GScameraLookAt(cam, &gUpVec, &target);
    _cameraUpdatePitch();
    _cameraUpdatePerspective(cam);
}

static void _cameraPadMoveUpdate(_GScamera* cam) {
    f32 rx;
    f32 div;
    f32 t;
    f32 lx;
    f32 ly;
    f32 ry;
    t = GSgfxVideoGetLastRenderTime();
    div = 64.0f;
    if (dbgMenuIsOpen()) {
        return;
    }
    if (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x400) {
        if (menuIsCheck(6)) {
            menuClose(6);
        } else {
            menuOpenCustom(6, 0, 0, 0, 1, 0);
            menuSetPosition(6, 20, 260);
        }
    }
    Mtx m;
    Mtx my;
    Mtx mz;
    PSMTXRotRad(m, 'X', pCamWork->rotation.x);
    PSMTXRotRad(my, 'Y', pCamWork->rotation.y);
    PSMTXConcat(my, m, m);
    PSMTXRotRad(mz, 'Z', pCamWork->rotation.z);
    PSMTXConcat(mz, m, m);
    lx = t * GSinputGetLeftStickXData(1, 0);
    ly = t * GSinputGetLeftStickYData(1, 0);
    rx = t * GSinputGetRightStickXData(1, 0);
    ry = t * GSinputGetRightStickYData(1, 0);
    if (GSinputButtonsPressed(1) & 0x40) {
        div *= 4.0f;
    }
    GSvec out;
    GSvec move;
    if (GSinputButtonsPressed(1) & 0x800) {
        move.set(lx / div, -ly / div, 0.0f);
    } else {
        move.set(lx / div, 0.0f, ly / div);
    }
    PSMTXMultVec(m, &move, &out);
    PSVECAdd(&pCamWork->position, &out, &pCamWork->position);
    if (GSinputButtonsPressed(1) & 0x20) {
        f32 fov = ry / div + cameraGetFov();
        cameraSetFov(fov);
    } else {
        pCamWork->rotation.x -= ry / (32.0f * div);
    }
    pCamWork->rotation.y -= rx / (32.0f * div);
    GScameraSetPosition(cam, &pCamWork->position);
    GScameraSetRotation(cam, &pCamWork->rotation);
    _cameraUpdatePerspective(cam);
}

extern "C" {

void cameraSetGScamera(_GScamera* src) {
    if (src == 0) {
        return;
    }
    _GScamera* dst = (_GScamera*)GSresGetResource(0, 0);
    f32 fov, aspect, near, far;
    GSvec dist;
    GScameraGetPerspective(src, &fov, &aspect, &near, &far);
    GScameraSetPerspective(dst, fov, aspect, near, far);
    GScameraGetDistanceVector(src, &dist);
    _cameraSetType(3);
    dst->unkFC = src->unkFC;
    dst->unk6C = src->unk6C;
    f32 height;
    f32 distance;
    f32 setFov;
    f32 rotY;
    setFov = fov;
    rotY = atan2(dist.x, dist.z);
    distance = dist.z;
    height = dist.y;
    FloorCamera* fc = _cameraGetFloorCamera();
    if (fc != 0) {
        if (fc->state != 0) {
            height = fc->height;
            distance = fc->distance;
            rotY = fc->rotY;
        } else {
            if (height < 0.0f) {
                height = 0.0f;
            }
            if (distance < 10.0f) {
                distance = 30.0f;
                height = 0.0f;
            } else if (distance > 500.0f) {
                distance = 500.0f;
            }
            fc->state = 1;
            fc->defHeight = height;
            fc->defDistance = distance;
            fc->defRotY = rotY;
            fc->defFov = setFov;
        }
    }
    cameraSetHeight(height);
    cameraSetDistance(distance);
    cameraSetRotY(rotY);
    if (setFov < 3.0f) {
        setFov = 3.0f;
    }
    if (setFov > 120.0f) {
        setFov = 120.0f;
    }
    FloorCamera* curFc = _cameraGetFloorCamera();
    if (curFc != 0) {
        curFc->fov = setFov;
    }
    pCamWork->fov = setFov;
}

void cameraResetFloor(void) {
    if (pCamWork->type == 6) {
        _cameraSetType(0);
    }
    FloorCamera* fc = _cameraGetFloorCamera();
    if (fc == 0) {
        return;
    }
    cameraSetHeight(fc->defHeight);
    cameraSetDistance(fc->defDistance);
    cameraSetRotY(fc->defRotY);
    cameraSetFov(fc->defFov);
}

void cameraSetFloorDefault(f32 height, f32 distance, f32 rotY) {
    FloorCamera* fc = _cameraGetFloorCamera();
    if (fc == 0) {
        return;
    }
    fc->defHeight = height;
    fc->defDistance = distance;
    fc->defRotY = rotY;
    if (fc->state == 1) {
        fc->state = 2;
        cameraSetHeight(height);
        cameraSetDistance(distance);
        cameraSetRotY(rotY);
    }
}

void cameraInit(void) {
    GSvec target(0.0f, 0.0f, 14.0f);
    GSvec up(0.0f, 1.0f, 0.0f);
    GSvec pos(0.0f, 0.0f, 100.0f);
    memset(&_cameraWork, 0, sizeof(CameraWork));
    pCamWork = &_cameraWork;
    _GScamera* cam = GScameraCreate();
    GSresRegisterResource(cam, 0, 0, 0);
    _cameraSetType(0);
    _cameraSetTarget(0, 100);
    pCamWork->targetOfs = target;
    _pFloorCamera = (FloorCamera*)GSmemAllocClr(*floordata_number * sizeof(FloorCamera));
    for (u32 i = 0; i < *floordata_number; i++) {
        _pFloorCamera[i].state = 0;
        _pFloorCamera[i].floorID = floordata[i].floorID;
    }
    pCamWork->offsetPos.set(0.0f, 0.0f, 0.0f);
    pCamWork->offsetRot.set(0.0f, 0.0f, 0.0f);
    pCamWork->offsetScale.set(1.0f, 1.0f, 1.0f);
    pCamWork->fov = 30.0f;
    FloorModuleInterface_clear(&_floorModuleCamera);
    _floorModuleCamera.makeStateData = _cameraMakeStateData;
    _floorModuleCamera.restoreStateData = _cameraRestoreStateData;
    _floorModuleCamera.getStateSize = _cameraGetStateSize;
    _floorModuleCamera.getUID = _cameraGetUID;
    _floorModuleCamera.getModuleName = _cameraGetModuleName;
    _hModuleField = floorRegisterModule(0x80, 0, &_floorModuleCamera);
    GScameraLookAt(cam, &up, &target);
    GScameraSetPosition(cam, &pos);
    GScameraSetActiveCamera(cam);
    GScameraLoadActiveCameraMatrix(0);
}

}

static inline _GScamera* _cameraGetCurrentCamera() {
    _GScamera* cam = (_GScamera*)GSresGetResource(0, 0);
    CameraWork* work = pCamWork;
    if (work->type == 4 || work->type == 8) {
        cam = _cameraGetAnimCamera(work);
    }
    return cam;
}

static const char* _cameraGetModuleName() {
    return "camera";
}

static u32 _cameraGetUID() {
    return 0x11;
}

static u32 _cameraGetStateSize(FloorStateMode mode) {
    if (mode == 1 || mode == 2) {
        return sizeof(CameraWork) + 0xB0;
    }
    return 0;
}

static void _cameraRestoreStateData(FloorStateMode mode, void* data, unsigned long size) {
    if (mode == 1 || mode == 2) {
        memcpy(pCamWork, data, sizeof(CameraWork));
        _GScamera* cam = _cameraGetCurrentCamera();
        if (pCamWork->flags & 0x08) {
            pCamWork->flags |= 0x10;
        }
        GScameraPopState(cam, (u8*)data + sizeof(CameraWork));
        GScameraSetActiveCamera(cam);
    }
}

static inline u8* _cameraToBytes(void* data) {
    return (u8*)data;
}

static void _cameraMakeStateData(FloorStateMode mode, void* data, unsigned long size) {
    if (mode == 1 || mode == 2) {
        u8* buf = _cameraToBytes(data);
        _GScamera* cam = _cameraGetCurrentCamera();
        memcpy(buf, pCamWork, sizeof(CameraWork));
        GScameraPushState(cam, buf + sizeof(CameraWork));
    }
}

template <typename T>
CameraAnimation<T>::CameraAnimation() {
    mMove = false;
    mAccel = false;
    mAccelEnd = false;
    mAccelStart = false;
    mAccelRate = 0.05f;
}

template <typename T>
void CameraAnimation<T>::start(const T* from, const T* to, f32 time) {
    if (time < CAMERA_EPS && time > -CAMERA_EPS) {
        return;
    }
    mMove = true;
    mTime = time;
    mCount = 0.0f;
    mStart = *from;
    mEnd = *to;
    mAccelRate = 0.05f;
    mSpeed = 0.0f;
    mState = 0;
}

template <typename T>
void CameraAnimation<T>::stop() {
    mMove = false;
    mAccel = false;
}

template <typename T>
bool CameraAnimation<T>::isMove() const {
    return mMove;
}

template <typename T>
bool CameraAnimation<T>::update(f32 dt) {
    if (!mMove) {
        return false;
    }
    if (mAccel) {
        return updateAcceleration(dt);
    }
    mFirst = false;
    mCount += dt;
    if (mCount >= mTime) {
        mCurrent = mEnd;
        mCount = 0.0f;
        mMove = false;
        mAccel = false;
        return true;
    }
    _cameraLerp(&mCurrent, &mStart, &mEnd, mCount / mTime);
    return true;
}

template <typename T>
bool CameraAnimation<T>::updateAcceleration(f32 dt) {
    if (!mMove) {
        return false;
    }
    if (mFirst) {
        if (!mAccelStart && mAccelEnd) {
            mSpeed = 1.0f;
            f32 dist = 0.0f;
            f32 frame = 1.0f / GSgfxVideoGetVsyncRate();
            if (GSgfxVideoGetLockFrameRate() == 1) {
                frame *= 2.0f;
            }
            for (f32 s = 0.0f; s < 1.0f; s += mAccelRate) {
                dist += frame * s;
            }
            mDecelTime = mTime - dist;
            mState = 1;
        }
        mFirst = false;
    }
    mCount += dt * mSpeed;
    if (mCount >= mTime) {
        mCurrent = mEnd;
        mCount = 0.0f;
        mMove = false;
        mAccel = false;
        return true;
    }
    _cameraLerp(&mCurrent, &mStart, &mEnd, mCount / mTime);
    switch (mState) {
    case 0:
        mSpeed += mAccelRate;
        if (mSpeed >= 1.0f) {
            mState = 1;
            mDecelTime = mTime - mCount;
        }
        break;
    case 1:
        if (mAccelEnd && mCount >= mDecelTime) {
            mState = 2;
        }
        break;
    case 2:
        mSpeed -= mAccelRate;
        if (mSpeed < mAccelRate) {
            mSpeed = mAccelRate;
        }
        break;
    }
    return true;
}

template <typename T>
void CameraAnimation<T>::setAcceleration(f32 rate) {
    mAccelRate = rate;
    mAccel = true;
    mAccelEnd = true;
    mAccelStart = true;
}

template <typename T>
const T* CameraAnimation<T>::getCurrentPos() const {
    return &mCurrent;
}
