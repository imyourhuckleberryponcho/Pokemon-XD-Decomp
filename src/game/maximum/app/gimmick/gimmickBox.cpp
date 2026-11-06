#include <dolphin/types.h>
#include <game/gcptr.h>
#pragma fp_contract off
#pragma use_lmw_stmw off

struct GSvec {
    f32 x, y, z;
    GSvec();
    GSvec(const GSvec& o);
    GSvec& operator=(const GSvec& o);
};

struct GSmodel;

struct tagPeopleWork {
    u8 active;
    u8 pad1[3];
    u8 pad4[4];
    GSmodel* model;
    u8 pad0C[2];
    u8 rotateFlag;
    u8 pad0F[0x0D];
    u32 id;
    u8 pad20[8];
    f32 f28;
    u8 pad2C[0x14];
    f32 targetAngle;
    f32 turnSpeed;
    s32 motion;
    u8 pad4C[0xC];
    f32 f58;
    u8 pad5C[0x1C];
    void* points;
    u8 pad7C[0xB0];
    f32 f12C;
};

enum M_STICK_DIRECTION {
    M_STICK_DIRECTION_NONE = 0,
    M_STICK_DIRECTION_1 = 1,
    M_STICK_DIRECTION_2 = 2,
    M_STICK_DIRECTION_3 = 3,
    M_STICK_DIRECTION_4 = 4
};

extern "C" {
int sprintf(char*, const char*, ...);
f32 C_VECDistance(GSvec*, GSvec*);
bool GScolsys2HitCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hit);
bool GScolsys2HitNpcCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hit);
f32 GScolsys2HumanGetWalkHighest(GSvec* pos);
u8 GSgfxVideoGetVsyncRate();
u32 GSinputButtonsPressed(s32 pad);
s8 GSinputGetLeftStickXData(s32 pad, s32 mode);
s8 GSinputGetLeftStickYData(s32 pad, s32 mode);
s8 GSinputGetRightStickXData(s32 pad, s32 mode);
s8 GSinputGetRightStickYData(s32 pad, s32 mode);
void GSlogWrite(const char*, ...);
f32 GSmodelGetAnimFrame(GSmodel* m);
void GSmodelGetAnimIndex(GSmodel* m, s32* index, s32* blend);
void GSmodelGetFrameCount(GSmodel* m, f32* count, f32* blend);
u32 GSmodelHasAnimationEnded(GSmodel* m);
void GSmodelSetAnimFrame(GSmodel* m, f32 f);
void GSmodelSetAnimIndex(GSmodel* m, s32 i);
void GSmodelSetAnimRate(GSmodel* m, f32 r);
void GSmodelSetAnimType(GSmodel* m, s32 t);
void GSmodelSetTexAnimFrame(GSmodel* m, f32 f);
void GSmodelSetTexAnimIndex(GSmodel* m, s32 i);
void GSmodelSetTexAnimRate(GSmodel* m, f32 r);
void GSmodelStartAnimation(GSmodel* m);
void GSprint(s32 layer, s32 x, s32 y, s32 color, const char* fmt, ...);
void GSthreadSwitch();
void GSvecCopy(GSvec* dst, GSvec* src);
u8 cameraGetType();
s32 dbgMenuGetLayerID();
u32 heroMoveGetKenObjID();
s32 heroMoveGetLeader();
u8 peopleBiosCheckFlag(tagPeopleWork* w, u32 flag);
s32 peopleBiosGetMaxNum();
GSmodel* peopleBiosGetModelPtr(tagPeopleWork* w);
void peopleBiosGetPos(tagPeopleWork* w, GSvec* out);
GSvec* peopleBiosGetPosPtr(tagPeopleWork* w);
GSvec* peopleBiosGetPrevPosPtr(tagPeopleWork* w);
void peopleBiosGetRot(tagPeopleWork* w, GSvec* out);
tagPeopleWork* peopleBiosGetWorkPtr(s32 i);
void peopleBiosSetFlags(tagPeopleWork* w, u32 f);
void peopleBiosSetPos(tagPeopleWork* w, GSvec* p);
u32 peopleGetHumanID(s32, s32);
void peopleGetPos(s32, s32, GSvec*);
void peopleGetRot(s32, s32, GSvec*);
f32 peopleInfoBiosGetColBallSize(void* info);
void* peopleInfoBiosGetPtr(u32 id);
void peopleRotateToAngle(s32, s32, f32, f32);
tagPeopleWork* peopleSearchID(u32 searchID);
void peopleSetFlagOff(s32, s32, s32);
void peopleSetFlagOn(s32, s32, s32);
void peopleSetMotion(s32, s32, s32, s32, s32);
void peopleSetMotionType(tagPeopleWork* w, s32 t);
void peopleSetPos(s32, s32, GSvec*);
void peopleSetRot(s32, s32, GSvec*);
void peopleUpdateAnimation(tagPeopleWork* w, s32 a);
f32 peopleVecCalcRotY(GSvec* a, GSvec* b, f32 c);
void soundOpenPlay(s32, s32, s32);
u32 timeGetLastFrameTime();
double fabs(double);
f64 fmod(f64, f64);
}

#ifndef __MWERKS__
extern "C" double sqrt(double);
#endif
namespace std {
f32 cosf(f32);
f32 sinf(f32);
#ifdef __MWERKS__
f32 sqrtf(f32);
#else
static inline f32 sqrtf(f32 x) { return (f32)sqrt((double)x); }
#endif
f32 fabsf(f32 x);
f32 fmodf(f32 a, f32 b);
}

struct GimmickBoxPushData {
    u8 f0;
    f32 f4;
    GSvec boxPos;
    GSvec kenPos;
    GSvec kenRot;
    f32 pushStartFrame;
    f32 pushFrame;
    f32 pushEndFrame;
    f32 jumpFrame;
    f32 walkFrame;
    tagPeopleWork* ken;
    void* kenInfo;
    tagPeopleWork* box;
    s32 direction;
    GSvec target;
    f32 progress;
    f32 pushStartFrames;
    f32 pushEndFrames;
    f32 jumpFrames;
    f32 walkFrames;
    f32 jumpY[50];
    f32 boxRadius;
    f32 kenRadius;
    f32 pushDist;
    f32 pushOffset;
    s32 peopleNum;
    u8 moving;
    u8 walking;
    u8 ready;
    u8 jumping;
    s32 mode;
    f32 jumpBaseY;
    f32 jumpAngle;

    GimmickBoxPushData() {
        f0 = 0;
        pushStartFrames = 10.0f;
        pushEndFrames = 10.0f;
        jumpFrames = 20.0f;
        walkFrames = 16.0f;
        boxRadius = 4.0f;
        kenRadius = 7.5f;
        pushDist = 2.0f * kenRadius;
        pushOffset = 4.0f + kenRadius;
        peopleNum = 0x40;
        jumpAngle = 0.0f;
    }
};

static GimmickBoxPushData pd;
static f32 m_radius_fix = 1.0f;
static f32 m_radius_fix2 = 1.0f;
static u8 sound_flag;

extern "C" void gimmickBoxFloorInit();
extern "C" u8 gimmickBoxIsPushBoxFloor();
extern "C" void gimmickSetMotion(s32 a, s32 b, s32 c, s32 d, u8 e);
static u8 _gimmickBoxCanJump(f32 angle, u8* flags);
static s32 _gimmickBoxCheckStickDirection();
static void _gimmickBoxGetDirection(M_STICK_DIRECTION d, f32* x, f32* z, f32* ang);
static f32 _gimmickBoxGetFixDistanceBoxAndPeople(f32 a, f32 b);
static s32 _gimmickBoxGetPeopleNum();
static u8 _gimmickBoxIsOnBoxPos(GSvec* p);
static u8 _gimmickBoxJumpMotion();
static void _gimmickBoxJump();
static u8 _gimmickBoxPushEndMotion();
static u8 _gimmickBoxPushStartMotion();
static void _gimmickBoxReadyAndMoveBox(tagPeopleWork* w);
static void _gimmickBoxRotateToAngle(f32 a, f32 b);
static void _gimmickBoxSetBoxDirection(f32 a, f32 b);
static s32 _gimmickBoxWalkMotion();
static f32 adjust2PI(f32 x);
static f32 adjustNear8(f32 x);
static s32 _gimmickBoxAllowAcrossPrevention(s32 n);
static u8 _gimmickBoxCanBoxMove(GSvec* a, GSvec* b);
static s32 _gimmickBoxBoxMoveStart(tagPeopleWork* w, f32 a, f32 b);
extern "C" f32 GSvecDistance(GSvec* a, GSvec* b);

extern "C" {

s32 gimmickBoxPop(void) {
    gimmickBoxFloorInit();
    return 1;
}

s32 gimmickBoxIsBox(tagPeopleWork* w) {
    if (gimmickBoxIsPushBoxFloor() == 0) return 0;
    if (w == 0) return 0;
    if (w->id == 0x11A40400) return 1;
    return 0;
}

}

static void _gimmickBoxSetJumpPosYs() {
    s32 i;
    s32 n;
    s32 k;
    f32 t;
    f32 y;
    f32 h = 3.3333333f;
    for (i = 0; (f32)i < pd.jumpFrames; i++) {
        if (i <= 3) {
            pd.jumpY[i] = 10.0f;
        } else if (i <= 12) {
            n = 9;
            k = i - 3;
            t = -0.5f + (1.5f * k) / (n - 1);
            y = (10.0f + h) - (10.0f * (t * t)) / 0.75f;
            pd.jumpY[i] = y;
        } else {
            t = 1.1363636f;
            y = (10.0f + h) - (10.0f * (t * t)) / 0.75f;
            pd.jumpY[i] = y;
        }
    }
}

extern "C" void gimmickBoxDrawString(s32 x, s32 y, const char* s) {
    GSprint(dbgMenuGetLayerID(), x * 13 + 20, y * 13 + 20, -1, s);
}

extern "C" void gimmickBoxDrawInt(s32 x, s32 y, s32 v) {
    char buf[0x400];
    sprintf(buf, "%d", v);
    GSprint(dbgMenuGetLayerID(), x * 13 + 20, y * 13 + 20, -1, buf);
}

extern "C" void gimmickBoxDrawFloat(s32 x, s32 y, f32 v) {
    char buf[0x400];
    sprintf(buf, "%f", v);
    GSprint(dbgMenuGetLayerID(), x * 13 + 20, y * 13 + 20, -1, buf);
}

extern "C" u8 gimmickBoxIsPushBoxFloor() {
    if (pd.mode == 1) return 1;
    return 0;
}

static s32 _gimmickBoxBoxMoveStart(tagPeopleWork* w, f32 fx, f32 fz) {
    f32 dx, dz;
    peopleBiosGetPos(w, &pd.boxPos);
    _gimmickBoxSetBoxDirection(fx, fz);
    _gimmickBoxGetDirection((M_STICK_DIRECTION)pd.direction, &dx, &dz, 0);
    pd.target.x = pd.boxPos.x + (dx * pd.pushDist);
    pd.target.z = pd.boxPos.z + (dz * pd.pushDist);
    pd.progress = 0.0f;
    if (pd.direction == _gimmickBoxCheckStickDirection() && _gimmickBoxCanBoxMove(&pd.boxPos, &pd.target) != 0) {
        pd.box = w;
        return 1;
    }
    return 0;
}

extern "C" s32 gimmickBoxFixDistanceForPushBox(f32 fx, f32 fz, f32* dist, tagPeopleWork* w) {
    if (w->id != 0x11A40400) return 0;
    f32 ax = std::fabsf(fx);
    f32 az = std::fabsf(fz);
    if (ax > pd.kenRadius && az > pd.kenRadius) {
        *dist = _gimmickBoxGetFixDistanceBoxAndPeople(fx, fz);
        return _gimmickBoxAllowAcrossPrevention(3);
    }
    u8 inside = 0;
    if (ax < az) {
        *dist = std::sqrtf((*dist * *dist) + (fx * fx));
        if (az < pd.kenRadius + pd.boxRadius) {
            inside = 1;
        }
    } else {
        *dist = std::sqrtf((*dist * *dist) + (fz * fz));
        if (ax < pd.kenRadius + pd.boxRadius) {
            inside = 1;
        }
    }
    if (pd.kenPos.y <= 2.0f && pd.box == 0 && *dist > std::sqrtf((fx * fx) + (fz * fz))) {
        _gimmickBoxBoxMoveStart(w, fx, fz);
    }
    return 1;
}

namespace std {
#ifndef __MWERKS__
static
#endif
inline f32 fabsf(f32 x) {
    return (f32)fabs(x);
}
}

extern "C" void gimmickBoxPushBox(tagPeopleWork* w) {
    if (pd.mode == 1 && w == pd.ken) {
        peopleBiosGetPos(pd.ken, &pd.kenPos);
        if (pd.box != 0) {
            for (s32 i = 0; i < pd.peopleNum; i++) {
                tagPeopleWork* p = peopleBiosGetWorkPtr(i);
                if (p == 0) {
                    break;
                }
                if (peopleBiosCheckFlag(p, 0x100000) != 0 && p == pd.box) {
                    _gimmickBoxReadyAndMoveBox(p);
                    break;
                }
            }
        }
        _gimmickBoxJump();
    }
}

static u8 _gimmickBoxTranslateKenToBoxPushPosition() {
    f32 dx, dz;
    _gimmickBoxGetDirection((M_STICK_DIRECTION)pd.direction, &dx, &dz, 0);
    u8 done = 0;
    if (dx == 0.0f) {
        if (pd.kenPos.x < (pd.boxPos.x - 0.5f)) {
            pd.kenPos.x += 0.5f;
        } else if (pd.kenPos.x > (0.5f + pd.boxPos.x)) {
            pd.kenPos.x -= 0.5f;
        } else {
            pd.kenPos.x = pd.boxPos.x;
            done = 1;
        }
        pd.kenPos.z = pd.boxPos.z - (dz * pd.pushOffset);
    } else {
        if (pd.kenPos.z < (pd.boxPos.z - 0.5f)) {
            pd.kenPos.z += 0.5f;
        } else if (pd.kenPos.z > (0.5f + pd.boxPos.z)) {
            pd.kenPos.z -= 0.5f;
        } else {
            pd.kenPos.z = pd.boxPos.z;
            done = 1;
        }
        pd.kenPos.x = pd.boxPos.x - (dx * pd.pushOffset);
    }
    pd.walking = 1;
    pd.moving = 0;
    pd.kenPos.y = GScolsys2HumanGetWalkHighest(&pd.kenPos);
    peopleBiosSetPos(pd.ken, &pd.kenPos);
    if (done == 0) _gimmickBoxWalkMotion();
    return done;
}

static u8 _gimmickBoxRoatateKenToBoxPushRotationReady() {
    switch (pd.direction) {
    case 3:
        if (pd.kenPos.x < (pd.boxPos.x - 0.5f)) {
            _gimmickBoxRotateToAngle(1.5707964f, 0.1f);
        } else if (pd.kenPos.x > (0.5f + pd.boxPos.x)) {
            _gimmickBoxRotateToAngle(-1.5707964f, 0.1f);
        } else {
            pd.walkFrame = GSmodelGetAnimFrame(peopleBiosGetModelPtr(pd.ken));
        }
        break;
    case 4:
        if (pd.kenPos.x < (pd.boxPos.x - 0.5f)) {
            _gimmickBoxRotateToAngle(1.5707964f, 0.1f);
        } else if (pd.kenPos.x > (0.5f + pd.boxPos.x)) {
            _gimmickBoxRotateToAngle(-1.5707964f, 0.1f);
        } else {
            pd.walkFrame = GSmodelGetAnimFrame(peopleBiosGetModelPtr(pd.ken));
        }
        break;
    case 1:
        if (pd.kenPos.z < (pd.boxPos.z - 0.5f)) {
            _gimmickBoxRotateToAngle(0.0f, 0.1f);
        } else if (pd.kenPos.z > (0.5f + pd.boxPos.z)) {
            _gimmickBoxRotateToAngle(3.1415927f, 0.1f);
        } else {
            pd.walkFrame = GSmodelGetAnimFrame(peopleBiosGetModelPtr(pd.ken));
        }
        break;
    case 2:
        if (pd.kenPos.z < (pd.boxPos.z - 0.5f)) {
            _gimmickBoxRotateToAngle(0.0f, 0.1f);
        } else if (pd.kenPos.z > (0.5f + pd.boxPos.z)) {
            _gimmickBoxRotateToAngle(3.1415927f, 0.1f);
        } else {
            pd.walkFrame = GSmodelGetAnimFrame(peopleBiosGetModelPtr(pd.ken));
        }
        break;
    }
    return 1;
}

static u8 _gimmickBoxRoatateKenToBoxPushRotation() {
    f32 ang;
    _gimmickBoxGetDirection((M_STICK_DIRECTION)pd.direction, 0, 0, &ang);
    _gimmickBoxRotateToAngle(ang, 0.1f);
    if (std::fabsf(pd.ken->targetAngle - ang) < 0.1f) {
        peopleGetRot(0, 0x64, &pd.kenRot);
        pd.kenRot.y = ang;
        peopleSetRot(0, 0x64, &pd.kenRot);
        return 1;
    }
    return 0;
}

static void _gimmickBoxPushBoxComplete() {
    pd.box = 0;
    pd.walking = 0;
    pd.ready = 0;
    pd.moving = 0;
    pd.pushStartFrame = 0.0f;
    pd.pushFrame = 0.0f;
    pd.pushEndFrame = 0.0f;
    pd.walkFrame = 0.0f;
    sound_flag = 0;
    peopleSetMotionType(pd.ken, 1);
}

static void _gimmickBoxSetBoxAndKenToPushPosition(tagPeopleWork* w, f32 fx, f32 fz) {
    pd.kenPos.x = pd.boxPos.x - (fx * pd.pushOffset);
    pd.kenPos.z = pd.boxPos.z - (fz * pd.pushOffset);
    pd.kenPos.y = GScolsys2HumanGetWalkHighest(&pd.kenPos);
    peopleBiosSetPos(w, &pd.boxPos);
    peopleBiosSetPos(pd.ken, &pd.kenPos);
}

static bool gimmickBoxUnusedIsZero(f32 a) {
    return a < 0.00001f && a > -0.00001f;
}

static void _gimmickBoxMoveBox(tagPeopleWork* w) {
    f32 dx, dz;
    _gimmickBoxGetDirection((M_STICK_DIRECTION)pd.direction, &dx, &dz, 0);
    f32 step = (30.0f * (f32)timeGetLastFrameTime()) / (f32)((f32)GSgfxVideoGetVsyncRate());
    pd.boxPos.x += step * (0.25f * dx);
    pd.boxPos.z += step * (0.25f * dz);
    pd.progress += 0.25f * step;
    if (sound_flag == 0) {
        soundOpenPlay(0x562, 0, 0x64);
        sound_flag = 1;
    }
    if (pd.progress >= pd.pushDist) {
        pd.boxPos.x = pd.target.x;
        pd.boxPos.z = pd.target.z;
        peopleBiosSetPos(w, &pd.boxPos);
        if (_gimmickBoxPushEndMotion() != 0) {
            _gimmickBoxPushBoxComplete();
        }
    } else {
        gimmickSetMotion(0, 0x64, 0x20, (s32)pd.pushFrame, 1);
        pd.pushFrame += (30.0f * (f32)timeGetLastFrameTime()) / (f32)((f32)GSgfxVideoGetVsyncRate());
        pd.walking = 0;
        pd.moving = 1;
    }
    _gimmickBoxSetBoxAndKenToPushPosition(w, dx, dz);
}

static void _gimmickBoxReadyAndMoveBox(tagPeopleWork* w) {
    if (w->model != 0) {
        peopleBiosGetPos(pd.ken, &pd.kenPos);
        peopleBiosGetPos(w, &pd.boxPos);
        if (_gimmickBoxRoatateKenToBoxPushRotationReady() != 0) {
            if (_gimmickBoxTranslateKenToBoxPushPosition() != 0 && _gimmickBoxRoatateKenToBoxPushRotation() != 0 &&
                _gimmickBoxPushStartMotion() != 0) {
                _gimmickBoxMoveBox(w);
            }
            GSthreadSwitch();
        }
    }
}

static s32 _gimmickBoxWalkMotion() {
    peopleSetMotion(0, 0x64, 5, (s32)pd.walkFrame, 1);
    f32 rate = (f32)GSgfxVideoGetVsyncRate();
    pd.walkFrame += (30.0f * (f32)timeGetLastFrameTime()) / rate;
    return 0;
}

static u8 _gimmickBoxPushStartMotion() {
    if (pd.pushStartFrame < pd.pushStartFrames) {
        gimmickSetMotion(0, 0x64, 0x1F, (s32)pd.pushStartFrame, 0);
        f32 rate = (f32)GSgfxVideoGetVsyncRate();
        pd.pushStartFrame += (30.0f * (f32)timeGetLastFrameTime()) / rate;
        return 0;
    }
    return 1;
}

static u8 _gimmickBoxPushEndMotion() {
    if (pd.pushEndFrame < pd.pushEndFrames) {
        gimmickSetMotion(0, 0x64, 0x21, (s32)pd.pushEndFrame, 0);
        f32 rate = (f32)GSgfxVideoGetVsyncRate();
        pd.pushEndFrame += (30.0f * (f32)timeGetLastFrameTime()) / rate;
        return 0;
    }
    return 1;
}

static void _gimmickBoxGetDirection(M_STICK_DIRECTION dir, f32* x, f32* z, f32* ang) {
    f32 fx = 0.0f;
    f32 fz = 0.0f;
    f32 fa = 0.0f;
    switch (dir) {
    case 3:
        fz = -1.0f;
        fa = 3.1415927f;
        break;
    case 4:
        fz = 1.0f;
        fa = 0.0f;
        break;
    case 2:
        fx = 1.0f;
        fa = 1.5707964f;
        break;
    case 1:
        fx = -1.0f;
        fa = -1.5707964f;
        break;
    }
    if (x != 0) *x = fx;
    if (z != 0) *z = fz;
    if (ang != 0) *ang = fa;
}

static f32 gimmickBoxUnusedFmod(f32 a) {
    a = std::fmodf(a, 6.2831855f);
    if (a < 0.7853982f || a > 2.3561945f) return 0.0f;
    return a;
}

namespace std {
#ifndef __MWERKS__
static
#endif
inline f32 fmodf(f32 a, f32 b) {
    return (f32)fmod(a, b);
}
}

static u8 _gimmickBoxCanBoxMove(GSvec* a, GSvec* b) {
    if (GScolsys2HitNpcCollision(a, b, pd.kenRadius - 0.1f, NULL) != 0) return 0;
    if (GScolsys2HumanGetWalkHighest(b) >= 0.1f) return 0;
    u8 ok = 1;
    for (s32 i = 0; i < pd.peopleNum; i++) {
        tagPeopleWork* p = peopleBiosGetWorkPtr(i);
        if (p->id == 0x11A40400 && p->model != 0 && b->x == peopleBiosGetPosPtr(p)->x && b->z == peopleBiosGetPosPtr(p)->z) {
            ok = 0;
        }
    }
    return ok;
}

static f32 _gimmickBoxGetFixDistanceBoxAndPeople(f32 fx, f32 fz) {
    f32 len;
    f32 rx;
    f32 rz;
    f32 dx;
    f32 dz;
    f32 ex;
    f32 ez;
    f32 sx;
    f32 sz;
    if (fx < 0.0f) rx = -pd.kenRadius;
    else rx = pd.kenRadius;
    if (fz < 0.0f) rz = -pd.kenRadius;
    else rz = pd.kenRadius;
    dx = fx - rx;
    dz = fz - rz;
    len = std::sqrtf((dx * dx) + (dz * dz));
    if (0.0f == len) len = 1.0f;
    sx = (dx * pd.boxRadius) / len;
    sz = (dz * pd.boxRadius) / len;
    ex = rx + sx;
    ez = rz + sz;
    return std::sqrtf((ex * ex) + (ez * ez));
}

static void _gimmickBoxSetBoxDirection(f32 fx, f32 fz) {
    if (std::fabsf(fx) > (f32)(std::fabsf(fz))) {
        if (fx > 0.0f) {
            pd.direction = 1;
            return;
        }
        pd.direction = 2;
        return;
    }
    if (fz > 0.0f) {
        pd.direction = 3;
        return;
    }
    pd.direction = 4;
}

extern "C" f32 gimmickBoxGetFrameCount(tagPeopleWork* w, s32 anim) {
    f32 count;
    GSmodel* m = w->model;
    GSmodelSetAnimIndex(m, anim);
    GSmodelGetFrameCount(m, &count, 0);
    return count;
}

static u8 _gimmickBoxInit() {
    pd.ken = peopleSearchID(peopleGetHumanID(0, 0x64));
    if (pd.ken == 0) return 0;
    pd.kenInfo = peopleInfoBiosGetPtr(pd.ken->id);
    pd.box = 0;
    pd.progress = 0.0f;
    pd.boxPos.y = 0.0f;
    pd.kenPos.y = 0.0f;
    pd.moving = 0;
    pd.walking = 0;
    pd.ready = 0;
    pd.jumping = 0;
    pd.pushStartFrame = 0.0f;
    pd.pushFrame = 0.0f;
    pd.pushEndFrame = 0.0f;
    pd.jumpFrame = 0.0f;
    pd.walkFrame = 0.0f;
    pd.pushStartFrames = gimmickBoxGetFrameCount(pd.ken, 0x1F);
    pd.pushEndFrames = gimmickBoxGetFrameCount(pd.ken, 0x21);
    pd.jumpFrames = gimmickBoxGetFrameCount(pd.ken, 0x22);
    pd.walkFrames = gimmickBoxGetFrameCount(pd.ken, 5);
    pd.boxRadius = peopleInfoBiosGetColBallSize(pd.kenInfo);
    pd.kenRadius = peopleInfoBiosGetColBallSize(peopleInfoBiosGetPtr(0x11A40400));
    pd.pushDist = 2.0f * pd.kenRadius;
    pd.pushOffset = 4.0f + pd.kenRadius;
    _gimmickBoxSetJumpPosYs();
    pd.peopleNum = _gimmickBoxGetPeopleNum();
    return 1;
}

static u8 _gimmickBoxIsJumpOK(GSvec* p) {
    if (GScolsys2HumanGetWalkHighest(p) <= 2.0f && _gimmickBoxIsOnBoxPos(p) == 0) {
        return 1;
    }
    return 0;
}

static void gimmickBoxUnusedCopy(GSvec* a) {
    GSvec b(*a);
    (void)b;
}

inline GSvec::GSvec(const GSvec& o) {
    x = o.x;
    y = o.y;
    z = o.z;
}

static void _gimmickBoxJump() {
    static f32 angle;
    f32 ang;
    f32 r2;
    f32 step2;
    f32 saveY;
    f32 rad;
    f32 base;
    f32 s;
    f32 c;
    u8 jflags;
    bool near;
    u8 on;
    bool blocked;
    void* info;
    bool stopped;
    if (pd.jumping == 0) {
        peopleBiosGetPos(pd.ken, &pd.kenPos);
        if (pd.kenPos.y < 10.0f) return;
        GSvec rot;
        peopleBiosGetRot(pd.ken, &rot);
        u8 unused = 0;
        u8 flags;
        stopped = GSvecDistance(peopleBiosGetPrevPosPtr(pd.ken), peopleBiosGetPosPtr(pd.ken)) < 0.00001f &&
                  GSvecDistance(peopleBiosGetPrevPosPtr(pd.ken), peopleBiosGetPosPtr(pd.ken)) > -0.00001f;
        if (stopped) {
            ang = rot.y;
        } else {
            ang = peopleVecCalcRotY(peopleBiosGetPrevPosPtr(pd.ken), peopleBiosGetPosPtr(pd.ken), 0.0f);
        }
        angle = ang;
        info = peopleInfoBiosGetPtr(pd.ken->id);
        if (info != 0) rad = peopleInfoBiosGetColBallSize(info);
        else rad = 3.5f;
        GSvec sp34;
        GSvec sp28;
        blocked = 0;
        jflags = 0;
        f32 step = (30.0f * (f32)timeGetLastFrameTime()) / (f32)GSgfxVideoGetVsyncRate();
        GSvec sp1C;
        s = std::sinf(ang);
        c = std::cosf(ang);
        peopleBiosGetPos(pd.ken, &pd.kenPos);
        sp1C = pd.kenPos;
        sp1C.x += s * pd.ken->f58;
        sp1C.z += c * pd.ken->f58;
        GSvec sp10(*peopleBiosGetPrevPosPtr(pd.ken));
        sp28 = sp1C;
        sp10.y += 6.0f;
        sp28.y += 6.0f;
        saveY = pd.kenPos.y;
        pd.kenPos.y = saveY;
        if (GScolsys2HitCollision(&sp10, &sp28, pd.boxRadius * m_radius_fix2, &pd.kenPos) != 0) {
            pd.kenPos.y = saveY;
            return;
        }
        pd.kenPos.y = saveY;
        static f32 fix_rr = rad * m_radius_fix;
        sp28 = pd.kenPos;
        sp28.x -= fix_rr;
        sp28.y = pd.kenPos.y;
        sp28.y = GScolsys2HumanGetWalkHighest(&sp28);
        near = std::fabsf((pd.kenPos.y - sp28.y) - 10.0f) < 3.0f;
        sp28.y = 10.0f;
        on = _gimmickBoxIsOnBoxPos(&sp28);
        if (near != 0 && on == 0) {
            blocked = 1;
            jflags |= 4;
        }
        sp28 = pd.kenPos;
        sp28.x += fix_rr;
        sp28.y = pd.kenPos.y;
        sp28.y = GScolsys2HumanGetWalkHighest(&sp28);
        near = std::fabsf((pd.kenPos.y - sp28.y) - 10.0f) < 3.0f;
        sp28.y = 10.0f;
        on = _gimmickBoxIsOnBoxPos(&sp28);
        if (near != 0 && on == 0) {
            blocked = 1;
            jflags |= 8;
        }
        sp28 = pd.kenPos;
        sp28.z -= fix_rr;
        sp28.y = pd.kenPos.y;
        sp28.y = GScolsys2HumanGetWalkHighest(&sp28);
        near = std::fabsf((pd.kenPos.y - sp28.y) - 10.0f) < 3.0f;
        sp28.y = 10.0f;
        on = _gimmickBoxIsOnBoxPos(&sp28);
        if (near != 0 && on == 0) {
            blocked = 1;
            jflags |= 1;
        }
        sp28 = pd.kenPos;
        sp28.z += fix_rr;
        sp28.y = pd.kenPos.y;
        sp28.y = GScolsys2HumanGetWalkHighest(&sp28);
        near = std::fabsf((pd.kenPos.y - sp28.y) - 10.0f) < 3.0f;
        sp28.y = 10.0f;
        on = _gimmickBoxIsOnBoxPos(&sp28);
        if (near != 0 && on == 0) {
            blocked |= 1;
            jflags |= 2;
        }
        r2 = 0.701f * fix_rr;
        sp28 = pd.kenPos;
        sp28.x -= r2;
        sp28.z -= r2;
        sp28.y = pd.kenPos.y;
        sp28.y = GScolsys2HumanGetWalkHighest(&sp28);
        near = std::fabsf((pd.kenPos.y - sp28.y) - 10.0f) < 3.0f;
        sp28.y = 10.0f;
        on = _gimmickBoxIsOnBoxPos(&sp28);
        if (near != 0 && on == 0) {
            blocked = 1;
            jflags |= 0x10;
        }
        sp28 = pd.kenPos;
        sp28.x += r2;
        sp28.z -= r2;
        sp28.y = pd.kenPos.y;
        sp28.y = GScolsys2HumanGetWalkHighest(&sp28);
        near = std::fabsf((pd.kenPos.y - sp28.y) - 10.0f) < 3.0f;
        sp28.y = 10.0f;
        on = _gimmickBoxIsOnBoxPos(&sp28);
        if (near != 0 && on == 0) {
            blocked = 1;
            jflags |= 0x20;
        }
        sp28 = pd.kenPos;
        sp28.x -= r2;
        sp28.z += r2;
        sp28.y = pd.kenPos.y;
        sp28.y = GScolsys2HumanGetWalkHighest(&sp28);
        near = std::fabsf((pd.kenPos.y - sp28.y) - 10.0f) < 3.0f;
        sp28.y = 10.0f;
        on = _gimmickBoxIsOnBoxPos(&sp28);
        if (near != 0 && on == 0) {
            blocked = 1;
            jflags |= 0x40;
        }
        sp28 = pd.kenPos;
        sp28.x += r2;
        sp28.z += r2;
        sp28.y = pd.kenPos.y;
        sp28.y = GScolsys2HumanGetWalkHighest(&sp28);
        near = std::fabsf((pd.kenPos.y - sp28.y) - 10.0f) < 3.0f;
        sp28.y = 10.0f;
        on = _gimmickBoxIsOnBoxPos(&sp28);
        if (near != 0 && on == 0) {
            blocked = 1;
            jflags |= 0x80;
        }
        if (near != 0 && on == 0) {
            blocked = 1;
        }
        if (blocked == 0) return;
        flags = 0;
        if (_gimmickBoxCanJump(ang, &flags) == 0) {
            ang = adjustNear8(ang);
            base = ang;
            if (_gimmickBoxCanJump(ang, &flags) == 0) {
                static f32 step_fix = 1.0f;
                for (step2 = step_fix; step2 <= 90.0f; step2 += step_fix) {
                    ang = adjust2PI(base - (0.017453292f * step2));
                    if (_gimmickBoxCanJump(ang, &flags) != 0) goto found;
                    ang = adjust2PI(base + (0.017453292f * step2));
                    if (_gimmickBoxCanJump(ang, &flags) != 0) goto found;
                }
                GSvecCopy(peopleBiosGetPosPtr(pd.ken), peopleBiosGetPrevPosPtr(pd.ken));
                pd.ken->f28 = 0.0f;
                peopleUpdateAnimation(pd.ken, 1);
                return;
            }
        }
    found:
        pd.jumpAngle = ang;
        pd.jumpFrame = 0.0f;
        pd.jumping = 1;
        pd.jumpBaseY = pd.kenPos.y;
        peopleSetFlagOn(0, 0x64, 8);
        peopleRotateToAngle(0, 0x64, ang, 1.0f);
    }
    if (_gimmickBoxJumpMotion() != 0) {
        pd.jumping = 0;
        peopleSetFlagOff(0, 0x64, 8);
        peopleSetPos(0, 0x64, &pd.kenPos);
        peopleSetMotionType(pd.ken, 1);
    }
}

inline GSvec& GSvec::operator=(const GSvec& o) {
    x = o.x;
    y = o.y;
    z = o.z;
    return *this;
}

extern "C" inline f32 GSvecDistance(GSvec* a, GSvec* b) {
    return C_VECDistance(a, b);
}

static u8 _gimmickBoxJumpMotion() {
    f32 step;
    f32 s;
    f32 c;
    f32 ang;
    f32 k;
    f32 ground;
    f32 g2;
    f32 saveY;
    f32 rate;
    s32 anim;
    s32 blend;
    GSvec* prev;
    peopleBiosGetPos(pd.ken, &pd.kenPos);
    saveY = pd.kenPos.y;
    prev = peopleBiosGetPrevPosPtr(pd.ken);
    GScolsys2HitCollision(peopleBiosGetPosPtr(pd.ken), prev, pd.boxRadius * m_radius_fix2, &pd.kenPos);
    pd.kenPos.y = saveY;
    if (pd.jumping != 0) {
        GSmodelGetAnimIndex(pd.ken->model, &anim, &blend);
        if (anim == 0x22 && blend == -1 && (u8)GSmodelHasAnimationEnded(pd.ken->model) != 0) {
            pd.jumpFrame = pd.jumpFrames;
            return 1;
        }
        rate = (f32)GSgfxVideoGetVsyncRate();
        step = (30.0f * (f32)timeGetLastFrameTime()) / rate;
        ang = pd.jumpAngle;
        s = std::sinf(ang);
        c = std::cosf(ang);
        peopleGetPos(0, 0x64, &pd.kenPos);
        k = 0.8888889f;
        GSvec probe(pd.kenPos);
        probe.x += s;
        probe.z += c;
        ground = GScolsys2HumanGetWalkHighest(&probe);
        if ((s32)pd.jumpFrame > 3 && (s32)pd.jumpFrame <= 0xC) {
            pd.kenPos.x += step * (s * k);
            pd.kenPos.z += step * (c * k);
        }
        pd.kenPos.y = (pd.jumpY[(s32)pd.jumpFrame] + pd.jumpBaseY) - 10.0f;
        if (pd.kenPos.y < ground) pd.kenPos.y = ground;
        g2 = GScolsys2HumanGetWalkHighest(&pd.kenPos);
        if (pd.kenPos.y < g2) pd.kenPos.y = g2;
        peopleSetPos(0, 0x64, &pd.kenPos);
        gimmickSetMotion(0, 0x64, 0x22, (s32)pd.jumpFrame, 0);
        pd.jumpFrame += step;
        return 0;
    }
    return 1;
}

static u8 _gimmickBoxIsOnBox(f32 x, f32 z, f32 y, f32 bx, f32 bz) {
    f32 dx = x - bx;
    f32 dz = z - bz;
    f32 adx = std::fabsf(dx);
    f32 adz = std::fabsf(dz);
    f32 limit;
    if (adx > pd.kenRadius && adz > pd.kenRadius) {
        limit = _gimmickBoxGetFixDistanceBoxAndPeople(dx, dz);
    } else {
        f32 r = y + pd.kenRadius;
        if (adx < adz) limit = std::sqrtf((r * r) + (dx * dx));
        else limit = std::sqrtf((r * r) + (dz * dz));
    }
    f32 dist = std::sqrtf((dx * dx) + (dz * dz));
    if (dist >= limit) return 0;
    return 1;
}

extern "C" s32 gimmickBoxOnBox(tagPeopleWork* w, GSvec* a, GSvec* pos) {
    if (pd.mode == 1 && w == pd.ken && (a->y - 10.0f) < 0.00001f && (a->y - 10.0f) > -0.00001f) {
        for (s32 i = 0; i < pd.peopleNum; i++) {
            tagPeopleWork* p = peopleBiosGetWorkPtr(i);
            if (p != 0 && p->model != 0 && p->id == 0x11A40400) {
                GSvec* pp = peopleBiosGetPosPtr(p);
                if (_gimmickBoxIsOnBox(pos->x, pos->z, 0.0f, peopleBiosGetPosPtr(p)->x, pp->z) != 0) {
                    pos->y = 10.0f;
                    return 1;
                }
            }
        }
    }
    return 0;
}

static u8 _gimmickBoxIsOnBoxPos(GSvec* p) {
    if (p->y == 10.0f) {
        for (s32 i = 0; i < pd.peopleNum; i++) {
            tagPeopleWork* w = peopleBiosGetWorkPtr(i);
            if (w != 0 && w->model != 0 && w->id == 0x11A40400) {
                GSvec* pp = peopleBiosGetPosPtr(w);
                if (_gimmickBoxIsOnBox(p->x, p->z, 0.0f, peopleBiosGetPosPtr(w)->x, pp->z) != 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

static s32 _gimmickBoxAllowAcrossPrevention(s32 n) {
    peopleBiosGetPos(pd.ken, &pd.kenPos);
    GSvec a(pd.kenPos);
    GSvec b(pd.kenPos);
    GSvec c(pd.kenPos);
    GSvec d(pd.kenPos);
    a.x -= 4.0f;
    a.z += 4.0f;
    b.x += 4.0f;
    b.z += 4.0f;
    c.x -= 4.0f;
    c.z -= 4.0f;
    d.x += 4.0f;
    d.z -= 4.0f;
    s32 count = 0;
    if (_gimmickBoxIsJumpOK(&a) == 0) count++;
    if (_gimmickBoxIsJumpOK(&b) == 0) count++;
    if (_gimmickBoxIsJumpOK(&c) == 0) count++;
    if (_gimmickBoxIsJumpOK(&d) == 0) count++;
    if (count >= n) return 1;
    return 0;
}

static u8 _gimmickBoxCanJump(f32 angle, u8* flags) {
    f32 r2;
    f32 r;
    f32 step;
    f32 saveY;
    f32 s;
    f32 c;
    bool near;
    u8 on;
    u8 ok;
    GSvec sp20;
    step = (30.0f * (f32)timeGetLastFrameTime()) / (f32)GSgfxVideoGetVsyncRate();
    GSvec sp14;
    s = std::sinf(angle);
    c = std::cosf(angle);
    sp14 = pd.kenPos;
    sp14.x += step * (8.0f * s);
    sp14.z += step * (8.0f * c);
    peopleBiosGetPos(pd.ken, &pd.kenPos);
    GSvec sp8(pd.kenPos);
    sp20 = sp14;
    sp8.y += 6.0f;
    sp20.y += 6.0f;
    saveY = pd.kenPos.y;
    if (GScolsys2HitCollision(&sp8, &sp20, pd.boxRadius * m_radius_fix2, &pd.kenPos) != 0) {
        pd.kenPos.y = saveY;
        return 0;
    }
    pd.kenPos.y = saveY;
    ok = 1;
    *flags = 0;
    r = pd.boxRadius * m_radius_fix;
    r2 = 0.701f * r;
    sp20 = sp14;
    sp20.x -= r;
    sp20.y = pd.kenPos.y;
    sp20.y = GScolsys2HumanGetWalkHighest(&sp20);
    near = std::fabsf((pd.kenPos.y - sp20.y) - 10.0f) < 3.0f;
    sp20.y = 10.0f;
    on = _gimmickBoxIsOnBoxPos(&sp20);
    if (near != 0 && on == 0) {
        *flags |= 4;
    } else {
        ok = 0;
    }
    sp20 = sp14;
    sp20.x += r;
    sp20.y = pd.kenPos.y;
    sp20.y = GScolsys2HumanGetWalkHighest(&sp20);
    near = std::fabsf((pd.kenPos.y - sp20.y) - 10.0f) < 3.0f;
    sp20.y = 10.0f;
    on = _gimmickBoxIsOnBoxPos(&sp20);
    if (near != 0 && on == 0) {
        *flags |= 8;
    } else {
        ok = 0;
    }
    sp20 = sp14;
    sp20.z -= r;
    sp20.y = pd.kenPos.y;
    sp20.y = GScolsys2HumanGetWalkHighest(&sp20);
    near = std::fabsf((pd.kenPos.y - sp20.y) - 10.0f) < 3.0f;
    sp20.y = 10.0f;
    on = _gimmickBoxIsOnBoxPos(&sp20);
    if (near != 0 && on == 0) {
        *flags |= 1;
    } else {
        ok = 0;
    }
    sp20 = sp14;
    sp20.z += r;
    sp20.y = pd.kenPos.y;
    sp20.y = GScolsys2HumanGetWalkHighest(&sp20);
    near = std::fabsf((pd.kenPos.y - sp20.y) - 10.0f) < 3.0f;
    sp20.y = 10.0f;
    on = _gimmickBoxIsOnBoxPos(&sp20);
    if (near != 0 && on == 0) {
        *flags |= 2;
    } else {
        ok = 0;
    }
    sp20 = sp14;
    sp20.x -= r2;
    sp20.z -= r2;
    sp20.y = pd.kenPos.y;
    sp20.y = GScolsys2HumanGetWalkHighest(&sp20);
    near = std::fabsf((pd.kenPos.y - sp20.y) - 10.0f) < 3.0f;
    sp20.y = 10.0f;
    on = _gimmickBoxIsOnBoxPos(&sp20);
    if (near != 0 && on == 0) {
        *flags |= 0x10;
    } else {
        ok = 0;
    }
    sp20 = sp14;
    sp20.x += r2;
    sp20.z -= r2;
    sp20.y = pd.kenPos.y;
    sp20.y = GScolsys2HumanGetWalkHighest(&sp20);
    near = std::fabsf((pd.kenPos.y - sp20.y) - 10.0f) < 3.0f;
    sp20.y = 10.0f;
    on = _gimmickBoxIsOnBoxPos(&sp20);
    if (near != 0 && on == 0) {
        *flags |= 0x20;
    } else {
        ok = 0;
    }
    sp20 = sp14;
    sp20.x -= r2;
    sp20.z += r2;
    sp20.y = pd.kenPos.y;
    sp20.y = GScolsys2HumanGetWalkHighest(&sp20);
    near = std::fabsf((pd.kenPos.y - sp20.y) - 10.0f) < 3.0f;
    sp20.y = 10.0f;
    on = _gimmickBoxIsOnBoxPos(&sp20);
    if (near != 0 && on == 0) {
        *flags |= 0x40;
    } else {
        ok = 0;
    }
    sp20 = sp14;
    sp20.x += r2;
    sp20.z += r2;
    sp20.y = pd.kenPos.y;
    sp20.y = GScolsys2HumanGetWalkHighest(&sp20);
    near = std::fabsf((pd.kenPos.y - sp20.y) - 10.0f) < 3.0f;
    sp20.y = 10.0f;
    on = _gimmickBoxIsOnBoxPos(&sp20);
    if (near != 0 && on == 0) {
        *flags |= 0x80;
    } else {
        ok = 0;
    }
    if (*flags == 0xFF) return 1;
    return 0;
}

static s32 _gimmickBoxGetPeopleNum() {
    s32 i;
    for (i = 0; i < peopleBiosGetMaxNum(); i++) {
        void* work = peopleBiosGetWorkPtr(i);
        if (work == 0) {
            return i;
        }
    }
    return peopleBiosGetMaxNum();
}

extern "C" s32 gimmickBoxSetKenShadowOnBoxIfOnBoxFloor(tagPeopleWork* ken, s32* list, s32* count) {
    if (pd.mode == 0) return 0;
    if (ken->id != heroMoveGetKenObjID()) return 0;
    f32 dx;
    f32 dz;
    s32 found = 0;
    GSmodel* m;
    for (s32 i = 0; i < pd.peopleNum; i++) {
        tagPeopleWork* p = peopleBiosGetWorkPtr(i);
        if (p != 0 && p->active != 0 && ken != 0 && ken->model != 0 && p != 0 && p->model != 0) {
            dx = std::fabsf(peopleBiosGetPosPtr(ken)->x - peopleBiosGetPosPtr(p)->x);
            dz = std::fabsf(peopleBiosGetPosPtr(ken)->z - peopleBiosGetPosPtr(p)->z);
            bool near = dx < 20.0f && dz < 20.0f;
            if (near != 0 && (p->id == 0x11A40400 || p->id == 0x1F380400)) {
                m = peopleBiosGetModelPtr(p);
                if (m != 0) {
                    if (*count < 7) {
                        *count += 1;
                    } else {
                        GSlogWrite("gimmickBox.cpp : receiveList over flow.\n");
                    }
                    list[*count - 1] = (GCsptr)m;
                    found = 1;
                }
            }
        }
    }
    return found;
}

extern "C" s32 gimmickBoxGetMotion(s32* motion, s8* loop) {
    if (pd.mode == 1) {
        if (pd.ready != 0) {
            *motion = 0x1F;
            *loop = 0;
            return 1;
        }
        if (pd.moving != 0) {
            *motion = 0x20;
            *loop = 1;
            return 1;
        }
        if (pd.walking != 0) {
            *motion = 5;
            *loop = 0;
            return 1;
        }
    }
    return 0;
}

extern "C" s32 gimmickBoxIsGimmickMoving(void) {
    if (pd.mode == 1 && (pd.moving != 0 || pd.walking != 0 || pd.jumping != 0)) return 1;
    return 0;
}

extern "C" f32 gimmickBoxGetBoxHeight(void) {
    return 10.0f;
}

static s32 _gimmickBoxCheckStickDirection() {
    s8 ly;
    s8 lx;
    s8 lx0;
    s8 ly0;
    s32 a1;
    s32 a2;
    s32 a3;
    s32 a4;
    s32 ax;
    s32 ay;
    f32 angle;
    f32 base;
    f32 power;
    f32 fy;
    f32 fx;
    f32 ratio;
    s32 leader = heroMoveGetLeader();
    power = 0.0f;
    lx = GSinputGetLeftStickXData(1, 1);
    ly = GSinputGetLeftStickYData(1, 1);
    lx0 = GSinputGetLeftStickXData(1, 0);
    ly0 = GSinputGetLeftStickYData(1, 0);
    if (lx == 0 && ly == 0) {
        if ((GSinputButtonsPressed(1) & 8) != 0) ly = -0x38;
        if ((GSinputButtonsPressed(1) & 4) != 0) ly = 0x38;
        if ((GSinputButtonsPressed(1) & 1) != 0) lx = -0x38;
        if ((GSinputButtonsPressed(1) & 2) != 0) lx = 0x38;
        lx0 = lx;
        ly0 = ly;
    }
    if (cameraGetType() != 6 && cameraGetType() != 5 && lx == 0 && ly == 0 && lx0 == 0 && ly0 == 0) {
        lx = GSinputGetRightStickXData(1, 1);
        if (lx < 0) a1 = -lx;
        else a1 = lx;
        if (a1 < 0x10) lx = 0;
        ly = GSinputGetRightStickYData(1, 1);
        if (ly < 0) a2 = -ly;
        else a2 = ly;
        if (a2 < 0x10) ly = 0;
        lx0 = GSinputGetRightStickXData(1, 0);
        if (lx0 < 0) a3 = -lx0;
        else a3 = lx0;
        if (a3 < 0x10) lx0 = 0;
        ly0 = GSinputGetRightStickYData(1, 0);
        if (ly0 < 0) a4 = -ly0;
        else a4 = ly0;
        if (a4 < 0x10) ly0 = 0;
        lx = (lx * 0x38) / 44;
        ly = (ly * 0x38) / 44;
        lx0 = (lx0 * 0x38) / 44;
        ly0 = (ly0 * 0x38) / 44;
    }
    if (lx != 0 || ly != 0) {
        if (lx > 0x38) lx = 0x38;
        else if (lx < -0x38) lx = -0x38;
        if (ly > 0x38) ly = 0x38;
        else if (ly < -0x38) ly = -0x38;
        if (lx > 0) ax = lx;
        else ax = -lx;
        fx = (f32)ax / 28.0f;
        if (ly > 0) ay = ly;
        else ay = -ly;
        fy = (f32)ay / 28.0f;
        power = std::sqrtf((fx * fx) + (fy * fy));
        if (power > 2.0f) power = 2.0f;
        if (lx0 <= -2 || lx0 >= 2 || ly0 <= -2 || ly0 >= 2) {
            if (fy < 0.001f) {
                base = 1.5707964f;
            } else {
                ratio = fx / fy;
                if (ratio > 5.0f) ratio = 5.0f;
                base = 1.5707964f * std::sinf(ratio / 3.1830988f);
            }
            if (ly >= 0) angle = base;
            else angle = 3.1415927f - base;
            if (lx < 0) {
                if (ly >= 0) angle = 3.1415927f + (3.1415927f - base);
                else angle = 3.1415927f + base;
            }
        }
    }
    if (power == 0.0f) return 0;
    if (angle < 0.3926991f || angle > 5.8904862f) return 4;
    if (angle > 1.1780972f && angle < 1.9634954f) return 2;
    if (angle > 2.7488935f && angle < 3.5342917f) return 3;
    if (angle > 4.3196898f && angle < 5.105088f) return 1;
    return 0;
}

extern "C" void gimmickBoxFloorInit() {
    pd.mode = 0;
    pd.peopleNum = peopleBiosGetMaxNum();
    for (s32 i = 0; i < pd.peopleNum; i++) {
        tagPeopleWork* p = peopleBiosGetWorkPtr(i);
        if (p == 0) break;
        if (p->active != 0) {
            if (p->id == 0x11A40400) {
                peopleBiosSetFlags(p, 0x100000);
                if (_gimmickBoxInit() != 0) pd.mode = 1;
            } else if (p->id == 0x1F380400) {
                pd.mode = 2;
            }
        }
    }
}

extern "C" void gimmickSetMotion(s32 a, s32 b, s32 motion, s32 frame, u8 loop) {
    if (frame == 0 && motion != 5 && motion >= 0) {
        tagPeopleWork* p = peopleSearchID(peopleGetHumanID(a, b));
        if (p != 0) {
            GSmodel* m = peopleBiosGetModelPtr(p);
            if (m != 0) {
                p->motion = motion;
                p->f12C = 0.0f;
                GSmodelSetAnimIndex(m, motion);
                GSmodelSetAnimFrame(m, (f32)frame);
                GSmodelSetAnimRate(m, 0.5f);
                GSmodelSetTexAnimIndex(m, motion);
                GSmodelSetTexAnimFrame(m, (f32)frame);
                GSmodelSetTexAnimRate(m, 0.5f);
                if (loop != 0) GSmodelSetAnimType(m, 1);
                else GSmodelSetAnimType(m, 0);
                if (frame == 0) GSmodelStartAnimation(m);
            }
        }
    }
}

static void _gimmickBoxRotateToAngle(f32 ang, f32 speed) {
    pd.ken->rotateFlag = 1;
    pd.ken->targetAngle = ang;
    pd.ken->turnSpeed = speed;
}

static f32 adjust2PI(f32 x) {
    return std::fmodf(6.2831855f + x, 6.2831855f);
}

static f32 adjustNear8(f32 x) {
    x = adjust2PI(x);
    if (x < 0.3926991f || x > 5.8904862f) return 0.0f;
    if (x > 5.105088f) return 5.497787f;
    if (x > 4.3196898f) return 4.712389f;
    if (x > 3.5342917f) return 3.9269907f;
    if (x > 2.7488935f) return 3.1415927f;
    if (x > 1.9634954f) return 2.3561945f;
    if (x > 1.1780972f) return 1.5707964f;
    return 0.7853982f;
}
