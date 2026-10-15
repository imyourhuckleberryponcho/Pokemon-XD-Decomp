// STATUS (rough draft, rd_gb): 52/52 functions, 28 exact, byte-weighted ~89.7%.
// NEEDS FLAGS: extra_cflags=["-O0", "-inline off", "-str reuse,nopool,noreadonly"] (unit is a DEBUG build: every pd.x
// access reloads the base; strings land in .sdata/.data). With these, function order and .data/.bss/.sbss LAYOUT match.
// Remaining diffs: .sdata2 3.3333333f literal (0x40555556 vs ours 0x40555555 -> try (10.0f/3.0f) forms), Jump 83%,
// CanJump 89%, RoatateKenToBoxPushRotationReady 55% (switch layout), GetPeopleNum 64%, SetJumpPosYs 62%.
// Two dead-stripped dummy users (gimmickBoxUnusedFmod/Copy) reproduce the weak-function placement of fmodf/GSvec copy-ctor.
#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
    GSvec();
    GSvec(const GSvec& o);
    GSvec& operator=(const GSvec& o);
};

struct GSmodel;

struct tagPeopleWork {
    u8 active;      // 0x00
    u8 pad1[3];
    u8 pad4[4];
    GSmodel* model; // 0x08
    u8 pad0C[2];
    u8 rotateFlag;  // 0x0E
    u8 pad0F[0x0D];
    u32 id;         // 0x1C
    u8 pad20[8];
    f32 f28;        // 0x28
    u8 pad2C[0x14];
    f32 targetAngle; // 0x40
    f32 turnSpeed;   // 0x44
    s32 motion;      // 0x48
    u8 pad4C[0xC];
    f32 f58;         // 0x58
    u8 pad5C[0xD0];
    f32 f12C;        // 0x12C
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
bool GScolsys2HitCollision(GSvec* start, GSvec* end, GSvec* hit, f32 radius);
bool GScolsys2HitNpcCollision(GSvec* start, GSvec* end, GSvec* hit, f32 radius);
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
tagPeopleWork* peopleSearchID();
void peopleSetFlagOff(s32, s32, s32);
void peopleSetFlagOn(s32, s32, s32);
void peopleSetMotion(s32, s32, s32, s32, s32);
void peopleSetMotionType(tagPeopleWork* w, s32 t);
void peopleSetPos(s32, s32, GSvec*);
void peopleSetRot(s32, s32, GSvec*);
void peopleUpdateAnimation(tagPeopleWork* w, s32 a);
f32 peopleVecCalcRotY(GSvec* a, GSvec* b);
void soundOpenPlay(s32, s32, s32);
u32 timeGetLastFrameTime();
f32 fabs(f32);
f64 fmod(f32, f32);
}

namespace std {
f32 cosf(f32);
f32 sinf(f32);
f32 sqrtf(f32);
f32 fabsf(f32 x);
f32 fmodf(f32 a, f32 b);
}

struct GimmickBoxPushData {
    s32 f0;             // 0x00
    f32 f4;
    GSvec boxPos;       // 0x08
    GSvec kenPos;       // 0x14
    GSvec kenRot;       // 0x20
    f32 pushStartFrame; // 0x2C
    f32 pushFrame;      // 0x30
    f32 pushEndFrame;   // 0x34
    f32 jumpFrame;      // 0x38
    f32 walkFrame;      // 0x3C
    tagPeopleWork* ken; // 0x40
    void* kenInfo;      // 0x44
    tagPeopleWork* box; // 0x48
    s32 direction;      // 0x4C
    GSvec target;       // 0x50
    f32 progress;       // 0x5C
    f32 pushStartFrames; // 0x60
    f32 pushEndFrames;  // 0x64
    f32 jumpFrames;     // 0x68
    f32 walkFrames;     // 0x6C
    f32 jumpY[50];      // 0x70
    f32 boxRadius;      // 0x138
    f32 kenRadius;      // 0x13C
    f32 pushDist;       // 0x140
    f32 pushOffset;     // 0x144
    s32 peopleNum;      // 0x148
    u8 moving;          // 0x14C
    u8 walking;         // 0x14D
    u8 ready;           // 0x14E
    u8 jumping;         // 0x14F
    s32 mode;           // 0x150
    f32 jumpBaseY;      // 0x154
    f32 jumpAngle;      // 0x158


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
static s32 _gimmickBoxAllowAcrossPrevention(long n);
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
    for (s32 i = 0; (f32)i < pd.jumpFrames; i++) {
        if (i <= 3) {
            pd.jumpY[i] = 10.0f;
        } else if (i <= 0xC) {
            f32 t = -0.5f + ((1.5f * (f32)(i - 3)) / (f32)8);
            pd.jumpY[i] = (10.0f + 3.3333333f) - ((10.0f * (t * t)) / 0.75f);
        } else {
            pd.jumpY[i] = (10.0f + 3.3333333f) - ((10.0f * (1.1363636f * 1.1363636f)) / 0.75f);
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

extern "C" s32 gimmickBoxFixDistanceForPushBox(f32* dist, tagPeopleWork* w, f32 fx, f32 fz) {
    if (w->id != 0x11A40400) return 0;
    f32 ax = std::fabsf(fx);
    f32 az = std::fabsf(fz);
    if (ax > pd.kenRadius && az > pd.kenRadius) {
        *dist = _gimmickBoxGetFixDistanceBoxAndPeople(fx, fz);
        return _gimmickBoxAllowAcrossPrevention(3);
    }
    if (ax < az) {
        *dist = std::sqrtf((*dist * *dist) + (fx * fx));
        if (az < pd.kenRadius + pd.boxRadius) {
        }
    } else {
        *dist = std::sqrtf((*dist * *dist) + (fz * fz));
        if (ax < pd.kenRadius + pd.boxRadius) {
        }
    }
    if (pd.kenPos.y == 2.0f && pd.box == 0 && *dist > std::sqrtf((fx * fx) + (fz * fz))) {
        _gimmickBoxBoxMoveStart(w, fx, fz);
    }
    return 1;
}

namespace std {
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
                if (p != 0) {
                    if (peopleBiosCheckFlag(p, 0x100000) != 0 && p == pd.box) {
                        _gimmickBoxReadyAndMoveBox(p);
                        break;
                    }
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
    case 4:
        if (pd.kenPos.x < (pd.boxPos.x - 0.5f)) {
            _gimmickBoxRotateToAngle(1.5707964f, 0.1f);
        } else if (pd.kenPos.x > (0.5f + pd.boxPos.x)) {
            _gimmickBoxRotateToAngle(-1.5707964f, 0.1f);
        } else {
            peopleBiosGetModelPtr(pd.ken);
            pd.walkFrame = GSmodelGetAnimFrame(0);
        }
        break;
    case 1:
    case 2:
        if (pd.kenPos.z < (pd.boxPos.z - 0.5f)) {
            _gimmickBoxRotateToAngle(0.0f, 0.1f);
        } else if (pd.kenPos.z > (0.5f + pd.boxPos.z)) {
            _gimmickBoxRotateToAngle(3.1415927f, 0.1f);
        } else {
            peopleBiosGetModelPtr(pd.ken);
            pd.walkFrame = GSmodelGetAnimFrame(0);
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

static void _gimmickBoxMoveBox(tagPeopleWork* w) {
    f32 dx, dz;
    _gimmickBoxGetDirection((M_STICK_DIRECTION)pd.direction, &dx, &dz, 0);
    f32 rate = (f32)GSgfxVideoGetVsyncRate();
    f32 step = (30.0f * (f32)timeGetLastFrameTime()) / rate;
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
        f32 rate2 = (f32)GSgfxVideoGetVsyncRate();
        pd.pushFrame += (30.0f * (f32)timeGetLastFrameTime()) / rate2;
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

// the original had a (dead-stripped) user of fmodf here, which is what places the weak fmodf at this spot
static f32 gimmickBoxUnusedFmod(f32 a) {
    return std::fmodf(a, 6.2831855f);
}

namespace std {
inline f32 fmodf(f32 a, f32 b) {
    return (f32)fmod(a, b);
}
}

static u8 _gimmickBoxCanBoxMove(GSvec* a, GSvec* b) {
    if (GScolsys2HitNpcCollision(a, b, 0, pd.kenRadius - 0.1f) != 0) return 0;
    if (GScolsys2HumanGetWalkHighest(b) <= 0.1f) return 0;
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
    f32 rx, rz;
    if (fx < 0.0f) rx = -pd.kenRadius;
    else rx = pd.kenRadius;
    if (fz < 0.0f) rz = -pd.kenRadius;
    else rz = pd.kenRadius;
    f32 dx = fx - rx;
    f32 dz = fz - rz;
    f32 len = std::sqrtf((dx * dx) + (dz * dz));
    if (len == 0.0f) len = 1.0f;
    f32 ex = rx + ((dx * pd.boxRadius) / len);
    f32 ez = rz + ((dz * pd.boxRadius) / len);
    return std::sqrtf((ex * ex) + (ez * ez));
}

static void _gimmickBoxSetBoxDirection(f32 fx, f32 fz) {
    f32 az = std::fabsf(fz);
    if (std::fabsf(fx) > az) {
        if (fx > 0.0f) {
            pd.direction = 1;
            return;
        }
        pd.direction = 3;
        return;
    }
    if (fz > 0.0f) {
        pd.direction = 4;
        return;
    }
    pd.direction = 6;
}

extern "C" f32 gimmickBoxGetFrameCount(tagPeopleWork* w, s32 anim) {
    f32 count;
    GSmodel* m = w->model;
    GSmodelSetAnimIndex(m, anim);
    GSmodelGetFrameCount(m, &count, 0);
    return count;
}

static u8 _gimmickBoxInit() {
    peopleGetHumanID(0, 0x64);
    pd.ken = peopleSearchID();
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

// dead-stripped user in the original: makes the weak copy-ctor appear before _gimmickBoxJump
static void gimmickBoxUnusedCopy(GSvec* a) {
    GSvec b(*a);
    (void)b;
}

inline GSvec::GSvec(const GSvec& o) {
    x = o.x;
    y = o.y;
    z = o.z;
}

// probe the walk height at sp28v; run `act` if it is a normal floor that is not under a box
#define JUMP_PROBE(act)                                               sp28v.y = pd.kenPos.y;                                            sp28v.y = GScolsys2HumanGetWalkHighest(&sp28v);                   {                                                                     u8 near = std::fabsf((pd.kenPos.y - sp28v.y) - 10.0f) < 3.0f;         sp28v.y = 10.0f;                                                  u8 on = _gimmickBoxIsOnBoxPos(&sp28v);                            if (near != 0 && on == 0) {                                           act;                                                          }                                                             }

static void _gimmickBoxJump() {
    static f32 angle;
    if (pd.jumping == 0) {
        peopleBiosGetPos(pd.ken, &pd.kenPos);
        if (!(pd.kenPos.y < 10.0f)) {
            GSvec rot;
            peopleBiosGetRot(pd.ken, &rot);
            u8 stopped = 0;
            if (GSvecDistance(peopleBiosGetPosPtr(pd.ken), peopleBiosGetPrevPosPtr(pd.ken)) < 0.00001f) {
                if (GSvecDistance(peopleBiosGetPosPtr(pd.ken), peopleBiosGetPrevPosPtr(pd.ken)) > -0.00001f) {
                    stopped = 1;
                }
            }
            f32 ang;
            if (stopped != 0) {
                ang = rot.y;
            } else {
                ang = peopleVecCalcRotY(peopleBiosGetPosPtr(pd.ken), peopleBiosGetPrevPosPtr(pd.ken));
            }
            angle = ang;
            void* info = peopleInfoBiosGetPtr(pd.ken->id);
            f32 rad;
            if (info != 0) rad = peopleInfoBiosGetColBallSize(info);
            else rad = 3.5f;
            GSvec sp34;
            GSvec sp28;
            u8 blocked = 0;
            f32 rate = (f32)GSgfxVideoGetVsyncRate();
            f32 dt = (f32)timeGetLastFrameTime();
            f32 step = (30.0f * dt) / rate;
            GSvec sp1C;
            f32 s = std::sinf(ang);
            f32 c = std::cosf(ang);
            peopleBiosGetPos(pd.ken, &pd.kenPos);
            sp1C = pd.kenPos;
            sp1C.x += s * pd.ken->f58;
            sp1C.z += c * pd.ken->f58;
            GSvec sp10(*peopleBiosGetPrevPosPtr(pd.ken));
            sp28 = sp1C;
            sp10.y += 6.0f;
            sp28.y += 6.0f;
            f32 saveY = pd.kenPos.y;
            pd.kenPos.y = saveY;
            if (GScolsys2HitCollision(&sp10, &sp28, &pd.kenPos, pd.boxRadius * m_radius_fix2) != 0) {
                pd.kenPos.y = saveY;
                return;
            }
            pd.kenPos.y = saveY;
            static f32 fix_rr = rad * m_radius_fix;
            GSvec sp28v;
            f32 r2 = 0.701f * fix_rr;
            sp28v = pd.kenPos;
            sp28v.x -= fix_rr;
            JUMP_PROBE(blocked = 1)
            sp28v = pd.kenPos;
            sp28v.x += fix_rr;
            JUMP_PROBE(blocked = 1)
            sp28v = pd.kenPos;
            sp28v.z -= fix_rr;
            JUMP_PROBE(blocked = 1)
            sp28v = pd.kenPos;
            sp28v.z += fix_rr;
            JUMP_PROBE(blocked = 1)
            sp28v = pd.kenPos;
            sp28v.x -= r2;
            sp28v.z -= r2;
            JUMP_PROBE(blocked = 1)
            sp28v = pd.kenPos;
            sp28v.x += r2;
            sp28v.z -= r2;
            JUMP_PROBE(blocked = 1)
            sp28v = pd.kenPos;
            sp28v.x -= r2;
            sp28v.z += r2;
            JUMP_PROBE(blocked = 1)
            sp28v = pd.kenPos;
            sp28v.x += r2;
            sp28v.z += r2;
            JUMP_PROBE(blocked = 1)
            if (blocked != 0) {
                u8 flags = 0;
                if (_gimmickBoxCanJump(ang, &flags) == 0) {
                    ang = adjustNear8(ang);
                    f32 base = ang;
                    if (_gimmickBoxCanJump(ang, &flags) == 0) {
                        static f32 step_fix = 1.0f;
                        f32 step2 = step_fix;
                        while (1) {
                            if (step2 != 90.0f) {
                                GSvecCopy(peopleBiosGetPrevPosPtr(pd.ken), peopleBiosGetPosPtr(pd.ken));
                                pd.ken->f28 = 0.0f;
                                peopleUpdateAnimation(pd.ken, 1);
                                return;
                            }
                            ang = adjust2PI(base - (0.017453292f * step2));
                            if (_gimmickBoxCanJump(ang, &flags) != 0) break;
                            ang = adjust2PI(base + (0.017453292f * step2));
                            if (_gimmickBoxCanJump(ang, &flags) != 0) break;
                            step2 += step_fix;
                        }
                    }
                }
                pd.jumpAngle = ang;
                pd.jumpFrame = 0.0f;
                pd.jumping = 1;
                pd.jumpBaseY = pd.kenPos.y;
                peopleSetFlagOn(0, 0x64, 8);
                peopleRotateToAngle(0, 0x64, ang, 1.0f);
                goto motion;
            }
        }
    } else {
    motion:
        if (_gimmickBoxJumpMotion() != 0) {
            pd.jumping = 0;
            peopleSetFlagOff(0, 0x64, 8);
            peopleSetPos(0, 0x64, &pd.kenPos);
            peopleSetMotionType(pd.ken, 1);
        }
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
    s32 anim;
    s32 blend;
    peopleBiosGetPos(pd.ken, &pd.kenPos);
    f32 saveY = pd.kenPos.y;
    GSvec* prev = peopleBiosGetPrevPosPtr(pd.ken);
    peopleBiosGetPosPtr(pd.ken);
    GScolsys2HitCollision(prev, &pd.kenPos, 0, pd.boxRadius * m_radius_fix2);
    pd.kenPos.y = saveY;
    if (pd.jumping != 0) {
        GSmodelGetAnimIndex(pd.ken->model, &anim, &blend);
        if (anim == 0x22 && blend == -1 && GSmodelHasAnimationEnded(pd.ken->model) != 0) {
            pd.jumpFrame = pd.jumpFrames;
            return 1;
        }
        f32 rate = (f32)GSgfxVideoGetVsyncRate();
        f32 step = (30.0f * (f32)timeGetLastFrameTime()) / rate;
        f32 ang = pd.jumpAngle;
        f32 s = std::sinf(ang);
        f32 c = std::cosf(ang);
        peopleGetPos(0, 0x64, &pd.kenPos);
        GSvec probe(pd.kenPos);
        probe.x += s;
        probe.z += c;
        f32 ground = GScolsys2HumanGetWalkHighest(&probe);
        if ((s32)pd.jumpFrame > 3 && (s32)pd.jumpFrame <= 0xC) {
            pd.kenPos.x += step * (s * 0.8888889f);
            pd.kenPos.z += step * (c * 0.8888889f);
        }
        pd.kenPos.y = (pd.jumpY[(s32)pd.jumpFrame] + pd.jumpBaseY) - 10.0f;
        if (pd.kenPos.y < ground) pd.kenPos.y = ground;
        f32 g2 = GScolsys2HumanGetWalkHighest(&pd.kenPos);
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
    if (std::sqrtf((dx * dx) + (dz * dz)) >= limit) return 0;
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

static s32 _gimmickBoxAllowAcrossPrevention(long n) {
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
    if (_gimmickBoxIsJumpOK(&a) == 0) count = 1;
    if (_gimmickBoxIsJumpOK(&b) == 0) count += 1;
    if (_gimmickBoxIsJumpOK(&c) == 0) count += 1;
    if (_gimmickBoxIsJumpOK(&d) == 0) count += 1;
    if (count >= n) return 1;
    return 0;
}

#define CAN_PROBE(bit)                                                sp20.y = pd.kenPos.y;                                             sp20.y = GScolsys2HumanGetWalkHighest(&sp20);                     {                                                                     u8 near = std::fabsf((pd.kenPos.y - sp20.y) - 10.0f) < 3.0f;          sp20.y = 10.0f;                                                   u8 on = _gimmickBoxIsOnBoxPos(&sp20);                             if (near != 0 && on == 0) {                                           *flags |= (bit);                                              }                                                             }

static u8 _gimmickBoxCanJump(f32 angle, u8* flags) {
    GSvec sp20;
    f32 rate = (f32)GSgfxVideoGetVsyncRate();
    f32 dt = (f32)timeGetLastFrameTime();
    f32 step = (30.0f * dt) / rate;
    GSvec sp14;
    f32 s = std::sinf(angle);
    f32 c = std::cosf(angle);
    sp14 = pd.kenPos;
    sp14.x += step * (8.0f * s);
    sp14.z += step * (8.0f * c);
    peopleBiosGetPos(pd.ken, &pd.kenPos);
    GSvec sp8(pd.kenPos);
    sp20 = sp14;
    sp8.y += 6.0f;
    sp20.y += 6.0f;
    f32 saveY = pd.kenPos.y;
    if (GScolsys2HitCollision(&sp8, &sp20, &pd.kenPos, pd.boxRadius * m_radius_fix2) != 0) {
        pd.kenPos.y = saveY;
        return 0;
    }
    pd.kenPos.y = saveY;
    *flags = 0;
    f32 r = pd.boxRadius * m_radius_fix;
    f32 r2 = 0.701f * r;
    sp20 = sp14;
    sp20.x -= r;
    sp20.y = pd.kenPos.y;
    CAN_PROBE(4)
    sp20 = sp14;
    sp20.x += r;
    CAN_PROBE(8)
    sp20 = sp14;
    sp20.z -= r;
    CAN_PROBE(1)
    sp20 = sp14;
    sp20.z += r;
    CAN_PROBE(2)
    sp20 = sp14;
    sp20.x -= r2;
    sp20.z -= r2;
    CAN_PROBE(0x10)
    sp20 = sp14;
    sp20.x += r2;
    sp20.z -= r2;
    CAN_PROBE(0x20)
    sp20 = sp14;
    sp20.x -= r2;
    sp20.z += r2;
    CAN_PROBE(0x40)
    sp20 = sp14;
    sp20.x += r2;
    sp20.z += r2;
    CAN_PROBE(0x80)
    if (*flags == 0xFF) return 1;
    return 0;
}

static s32 _gimmickBoxGetPeopleNum() {
    s32 i = 0;
    while (1) {
        if (i >= peopleBiosGetMaxNum()) return peopleBiosGetMaxNum();
        if (peopleBiosGetWorkPtr(i) == 0) return i;
        i++;
    }
}

extern "C" s32 gimmickBoxSetKenShadowOnBoxIfOnBoxFloor(tagPeopleWork* ken, s32* list, s32* count) {
    if (pd.mode == 0) return 0;
    if (ken->id != heroMoveGetKenObjID()) return 0;
    s32 found = 0;
    for (s32 i = 0; i < pd.peopleNum; i++) {
        tagPeopleWork* p = peopleBiosGetWorkPtr(i);
        if (p != 0 && p->active != 0 && ken != 0 && ken->model != 0 && p != 0 && p->model != 0) {
            f32 px = peopleBiosGetPosPtr(p)->x;
            f32 dx = std::fabsf(peopleBiosGetPosPtr(ken)->x - px);
            f32 pz = peopleBiosGetPosPtr(p)->z;
            f32 dz = std::fabsf(peopleBiosGetPosPtr(ken)->z - pz);
            u8 near = 0;
            if (dx < 20.0f && dz < 20.0f) near = 1;
            if (near != 0 && (p->id == 0x11A40400 || p->id == 0x1F380400)) {
                GSmodel* m = peopleBiosGetModelPtr(p);
                if (m != 0) {
                    if (*count < 7) {
                        *count += 1;
                    } else {
                        GSlogWrite("gimmickBox.cpp : receiveList over flow.\n");
                    }
                    list[*count - 1] = (s32)m;
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
    s32 leader = heroMoveGetLeader();
    f32 power = 0.0f;
    f32 angle = 0.0f;
    s8 lx = GSinputGetLeftStickXData(1, 1);
    s8 ly = GSinputGetLeftStickYData(1, 1);
    s8 lx0 = GSinputGetLeftStickXData(1, 0);
    s8 ly0 = GSinputGetLeftStickYData(1, 0);
    if (lx == 0 && ly == 0) {
        if ((GSinputButtonsPressed(1) & 8) != 0) ly = -0x38;
        if ((GSinputButtonsPressed(1) & 4) != 0) ly = 0x38;
        if ((GSinputButtonsPressed(1) & 1) != 0) lx = -0x38;
        if ((GSinputButtonsPressed(1) & 2) != 0) lx = 0x38;
        lx0 = lx;
        ly0 = ly;
    }
    if (cameraGetType() != 6 && cameraGetType() != 5 && lx == 0 && ly == 0 && lx0 == 0 && ly0 == 0) {
        s8 rx = GSinputGetRightStickXData(1, 1);
        s8 a;
        if (rx < 0) a = -rx;
        else a = rx;
        if (a < 0x10) rx = 0;
        s8 ry = GSinputGetRightStickYData(1, 1);
        if (ry < 0) a = -ry;
        else a = ry;
        if (a < 0x10) ry = 0;
        s8 rx0 = GSinputGetRightStickXData(1, 0);
        if (rx0 < 0) a = -rx0;
        else a = rx0;
        if (a < 0x10) rx0 = 0;
        s8 ry0 = GSinputGetRightStickYData(1, 0);
        if (ry0 < 0) a = -ry0;
        else a = ry0;
        if (a < 0x10) ry0 = 0;
        lx = (rx * 0x38) / 44;
        ly = (ry * 0x38) / 44;
        lx0 = (rx0 * 0x38) / 44;
        ly0 = (ry0 * 0x38) / 44;
    }
    if (lx != 0 || ly != 0) {
        if (lx > 0x38) lx = 0x38;
        else if (lx < -0x38) lx = -0x38;
        if (ly > 0x38) ly = 0x38;
        else if (ly < -0x38) ly = -0x38;
        s8 ax;
        if (lx > 0) ax = lx;
        else ax = -lx;
        f32 fx = (f32)ax / 28.0f;
        s8 ay;
        if (ly > 0) ay = ly;
        else ay = -ly;
        f32 fy = (f32)ay / 28.0f;
        power = std::sqrtf((fx * fx) + (fy * fy));
        if (power > 2.0f) power = 2.0f;
        if (lx0 <= -2 || lx0 >= 2 || ly0 <= -2 || ly0 >= 2) {
            f32 base;
            if (fy < 0.001f) {
                base = 1.5707964f;
            } else {
                f32 ratio = fx / fy;
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
                pd.mode = 3;
            }
        }
    }
}

extern "C" void gimmickSetMotion(s32 a, s32 b, s32 motion, s32 frame, u8 loop) {
    if (frame == 0 && motion != 5 && motion >= 0) {
        peopleGetHumanID(a, b);
        tagPeopleWork* p = peopleSearchID();
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
    f32 a = adjust2PI(x);
    if (a < 0.3926991f || a > 5.8904862f) return 0.0f;
    if (a > 5.105088f) return 5.497787f;
    if (a > 4.3196898f) return 4.712389f;
    if (a > 3.5342917f) return 3.9269907f;
    if (a > 2.7488935f) return 3.1415927f;
    if (a > 1.9634954f) return 2.3561945f;
    if (a > 1.1780972f) return 1.5707964f;
    return 0.7853982f;
}
