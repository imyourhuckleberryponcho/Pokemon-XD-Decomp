// Draft (written from asm).
#include <dolphin/types.h>
#pragma pool_strings off
extern "C" double __fabs(double x);
inline double fabs(double x) { return __fabs(x); }

struct GSvec {
    f32 x, y, z;
};

struct PeopleWork {
    u8 active;              // 0x0
    u8 pad1[0xC];
    u8 flagD;               // 0xD
    u8 pad2[6];
    u32 group;              // 0x14
    u32 id;                 // 0x18
    u32 modelResID;         // 0x1C
    u8 pad3[0x20];
    f32 angleY;             // 0x40
    u8 pad4[0x5C];
    u8 rotating;            // 0xA0
    u8 neckHold;            // 0xA1
    u8 padA2[2];
    f32 savedAngle;         // 0xA4
    u8 padA8[0x1C];
    u8 neckFlag;            // 0xC4
    u8 padC5[3];
    f32 neckPos[3];         // 0xC8
    u8 padD4[0x18];
    f32 neckSaved[3];       // 0xEC
    u8 padF8[0x80];
    f32 talkDistance;       // 0x178
};

struct PeopleInfo;
struct FloorBgmMask {
    u8 pad[4];
    u8 maskOn;  // 0x4
    void startMask();
    void endMask();
    void setVolumeRate(f32);
    void setFadeInTime(f32);
    void setFadeOutTime(f32);
};

struct PeopleTalkRes {
    u32 group;
    u32 id;
};

extern "C" {
PeopleWork* peopleGet(s32 group, s32 id);
s32 peopleGetFlags(s32 group, s32 id);
void peopleGetPos(s32 group, s32 id, GSvec* out);
void peopleGetNeckPos(u32 group, u32 id, GSvec* out);
void peopleRotateToAngle(s32 group, s32 id, f32 angle, f32 speed);
void peopleRotateToTarget(s32 group, s32 id, s32 a, s32 b, f32 speed);
void peopleRotateCheck(s32 group, s32 id, u8 flag);
u8 peopleSetNeckLimitHold(s32 group, s32 id, u8 flag);
u8 peopleCheckNeckRotate(s32 group, s32 id, u8 flag);
void fn_8029CD20(s32 group, s32 id, s32 a, s32 b, f32 speed);
void peopleSpeakStart(s32 group, s32 id);
f32 peopleVecCalcRotY(GSvec* a, GSvec* b, f32 base);
u8 peopleInsideCheck(GSvec* a, GSvec* b, GSvec* c);
f32 PSVECDistance(const GSvec* a, const GSvec* b);
f32 peopleInfoBiosGetColBallSize(PeopleInfo* info);
PeopleInfo* peopleInfoBiosGetPtr(u32 modelResID);
u8 peopleInfoBiosGetTalkSe(PeopleInfo* info);
PeopleWork* peopleBiosGetWorkPtr(s32 index);
s32 peopleBiosGetMaxNum();
GSvec* peopleBiosGetPosPtr(PeopleWork* work);
void peopleBiosGetRot(PeopleWork* work, GSvec* out);
bool peopleBiosCheckFlag(PeopleWork* work, u32 flags);
void* floorDataBiosGetCurrentPtr();
u32 floorDataBiosGetFloorKind();
void* floorCharacterBiosFindByResID(u32 group, u32 id);
u32 floorCharacterBiosGetNameID(void* ch);
u8 floorCharacterBiosGetTalkStartType(void* ch);
u8 floorCharacterBiosGetTalkWallThrough(void* ch);
u8* floorEventGetTresureList(u32 id);
u16 charNameBiosGetHearFlag(u32 id);
u32 charNameBiosGetNameID(u32 id);
FloorBgmMask* floorSound_getBgmMaskObj();
void GSflagOn(u32 id);
bool GSflagTest(u32 id);
void GSthreadSwitch();
f32 timeGetLastFrameSec();
void msgctrlSetValue(s32 id, u32 value);
void winMsgClose(bool flag);
s32 winMsgCheckField();
s32 winMsgOpenFieldWithSE(s32 msg, bool a, bool b, u8 se);
u8 heroMoveIsMember(s32 member);
void heroMoveGetResID(u32* group, u32* id, s32 member);
u8 gimmickBoxIsPushBoxFloor();
bool GScolsys2HitCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hitOut);
void GSlogWritef(const char* fmt, ...);
}


static f32 _talkWindowCloseDelay;
static PeopleTalkRes _peopleTalkRes;

extern "C" {

void peopleSetTalkDistance(s32 group, s32 id, f32 dist) {
    PeopleWork* work = peopleGet(group, id);
    if (work != 0) {
        work->talkDistance = dist;
    }
}

f32 peopleGetTalkDistance(s32 group, s32 id) {
    PeopleWork* work = peopleGet(group, id);
    if (work == 0) {
        return 0.0f;
    }
    return work->talkDistance;
}

void peopleTalkLeaveFloor() {}

void peopleTalkEnterFloor() {
    _talkWindowCloseDelay = 0.0f;
}

void peopleTalkMessageDaemon() {
    floorDataBiosGetCurrentPtr();
    if ((u8)floorDataBiosGetFloorKind() == 1 && _talkWindowCloseDelay > 0.0f) {
        _talkWindowCloseDelay -= timeGetLastFrameSec();
    }
}

void peopleTalkMessageBgmStop() {
    FloorBgmMask* bgm = floorSound_getBgmMaskObj();
    if (bgm != 0) {
        bgm->endMask();
    }
}

void peopleTalkMessageBgmStart() {
    FloorBgmMask* bgm = floorSound_getBgmMaskObj();
    if (bgm != 0) {
        bgm->startMask();
    }
}

void peopleTalkMessageBgmSetVolumeRate(f32 rate) {
    FloorBgmMask* bgm = floorSound_getBgmMaskObj();
    if (bgm != 0) {
        bgm->setVolumeRate(rate);
    }
}

void peopleTalkMessageBgmSetFadeSpeed(f32 fadeIn, f32 fadeOut) {
    FloorBgmMask* bgm = floorSound_getBgmMaskObj();
    if (bgm != 0) {
        bgm->setFadeInTime(fadeIn);
        bgm->setFadeOutTime(fadeOut);
    }
}

void peopleTalkMessageBgmMask(u8 on) {
    FloorBgmMask* bgm = floorSound_getBgmMaskObj();
    if (bgm != 0) {
        if (on != 0) {
            bgm->maskOn = 1;
        } else {
            bgm->maskOn = 0;
        }
    }
}

void peopleTalkMsgEnd(s32 group, s32 id) {
    winMsgClose(true);
    _talkWindowCloseDelay = 0.2f;
    PeopleWork* work = peopleGet(group, id);
    if (work != 0) {
        s32 flags = peopleGetFlags(group, id);
        if (work->rotating != 0) {
            work->rotating = 0;
            if (flags & 0x20) {
                if (flags & 0x40) {
                    peopleRotateToAngle(group, id, work->savedAngle, 1.0f);
                }
            } else if (flags & 0x10) {
                work->neckPos[0] = work->neckSaved[0];
                work->neckPos[1] = work->neckSaved[1];
                work->neckPos[2] = work->neckSaved[2];
                work->neckFlag = 1;
                peopleSetNeckLimitHold(group, id, work->neckHold);
            }
        }
    }
    while (winMsgCheckField() != -1) {
        GSthreadSwitch();
    }
    _peopleTalkRes.group = 0;
    _peopleTalkRes.id = 0;
    msgctrlSetValue(0x59, 0x1772);
}

void peopleSetTalkFlagCallback() {
    if (_peopleTalkRes.group == 0 && _peopleTalkRes.id == 0) {
        msgctrlSetValue(0x59, 0x1772);
    } else {
        u32 value = 0x1772;
        void* ch = floorCharacterBiosFindByResID(_peopleTalkRes.group, _peopleTalkRes.id);
        if (ch != 0) {
            u32 nameID = floorCharacterBiosGetNameID(ch);
            u16 flag = charNameBiosGetHearFlag(nameID);
            if (flag != 0) {
                GSflagOn(flag);
                value = charNameBiosGetNameID(nameID);
            }
        }
        msgctrlSetValue(0x59, value);
    }
}

void peopleSetTalkKeyWaitCallback() {
    if (_peopleTalkRes.group != 0 || _peopleTalkRes.id != 0) {
        peopleSpeakStart(_peopleTalkRes.group, _peopleTalkRes.id);
    }
}

void peopleTalkMsg(s32 group, s32 id, s32 msg) {
    void* ch;
    u32 value;
    PeopleInfo* info;
    u16 flag;
    u32 nameID;
    u8 se = 0;
    FloorBgmMask* bgm;
    PeopleWork* work = peopleGet(group, id);
    s32 flags;
    if (work != 0) {
        if (work != 0) {
            flags = peopleGetFlags(group, id);
            if (flags & 0x20) {
                if (work->rotating == 0) {
                    work->savedAngle = work->angleY;
                    work->rotating = 1;
                }
                peopleRotateToTarget(group, id, 0, 100, 1.0f);
                peopleRotateCheck(group, id, 1);
            } else if (flags & 0x10) {
                if (work->rotating == 0) {
                    work->neckSaved[0] = work->neckPos[0];
                    work->neckSaved[1] = work->neckPos[1];
                    work->neckSaved[2] = work->neckPos[2];
                    fn_8029CD20(group, id, 0, 100, 2.0f);
                    work->neckHold = peopleSetNeckLimitHold(group, id, 1);
                    peopleCheckNeckRotate(group, id, 1);
                    work->rotating = 1;
                }
            }
            info = peopleInfoBiosGetPtr(work->modelResID);
            if (info != 0) {
                se = peopleInfoBiosGetTalkSe(info);
            }
            value = 0x1772;
            ch = floorCharacterBiosFindByResID(work->group, work->id);
            if (ch != 0) {
                nameID = floorCharacterBiosGetNameID(ch);
                flag = charNameBiosGetHearFlag(nameID);
                if (flag == 0) {
                    value = 0x1772;
                } else if (GSflagTest(flag) == 1) {
                    value = charNameBiosGetNameID(nameID);
                }
            }
            msgctrlSetValue(0x59, value);
        }
        while (_talkWindowCloseDelay > 0.0f) {
            GSthreadSwitch();
        }
        _peopleTalkRes.group = work->group;
        _peopleTalkRes.id = work->id;
        bgm = floorSound_getBgmMaskObj();
        if (bgm != 0) {
            bgm->startMask();
            winMsgOpenFieldWithSE(msg, 1, 0, se);
            bgm->endMask();
        }
    }
}

PeopleWork* peopleTalkCheck(u32 group, u32 id, f32 unused, f32 range) {
    PeopleWork* me;
    PeopleWork* best = 0;
    s32 i;
    bool member;
    PeopleWork* other;
    PeopleInfo* info;
    void* ch;
    u32 resGroup = 0;
    u32 resId;
    f32 dist;
    f32 ang;
    f32 bestAng;
    f32 myRadius;
    f32 bestArea = 10000.0f;
    f32 limit;
    GSvec target;
    GSvec heroMember;
    GSvec hero;
    heroMember.x = 0.0f;
    heroMember.y = 0.0f;
    heroMember.z = 0.0f;
    resId = 0;
    limit = 0.017453292f * range;
    me = peopleGet(group, id);
    if (me == 0) {
        return 0;
    }
    GSvec* pos = peopleBiosGetPosPtr(me);
    hero.x = pos->x;
    hero.y = pos->y;
    hero.z = pos->z;
    PeopleInfo* myInfo = peopleInfoBiosGetPtr(me->modelResID);
    if (myInfo != 0) {
        myRadius = peopleInfoBiosGetColBallSize(myInfo);
    } else {
        myRadius = 4.0f;
    }
    member = heroMoveIsMember(1) != 0;
    heroMoveGetResID(&resGroup, &resId, 1);
    if (member) {
        peopleGetPos(resGroup, resId, &heroMember);
    }
    for (i = 0; i < peopleBiosGetMaxNum(); i++) {
        other = peopleBiosGetWorkPtr(i);
        if (other->active == 0) continue;
        if (me == other) continue;
        if (other->flagD == 0) continue;
        if (peopleBiosCheckFlag(other, 1)) continue;
        ch = floorCharacterBiosFindByResID(other->group, other->id);
        if (ch != 0 && floorCharacterBiosGetTalkStartType(ch) == 3) continue;
        info = peopleInfoBiosGetPtr(other->modelResID);
        if (info == 0) continue;
        peopleGetNeckPos(other->group, other->id, &target);
        dist = PSVECDistance(&hero, &target);
        f32 size = peopleInfoBiosGetColBallSize(info);
        f32 reach = myRadius + peopleGetTalkDistance(other->group, other->id);
        reach += size;
        if (dist > reach) continue;
        ang = peopleVecCalcRotY(&hero, &target, me->angleY);
        if ((f32)fabs(ang) > limit) continue;
        if (gimmickBoxIsPushBoxFloor()) {
            if ((s32)(hero.y / 10.0f) != (s32)(target.y / 10.0f)) continue;
        }
        bool check;
        if (ch != 0) {
            check = floorCharacterBiosGetTalkWallThrough(ch) == 0;
        } else {
            u8* list = floorEventGetTresureList(other->id);
            if (list != 0 && (u32)((*list >> 5) & 7) == 1) {
                GSvec rot;
                peopleBiosGetRot(other, &rot);
                if ((f32)fabs(peopleVecCalcRotY(&target, &hero, rot.y)) > 2.0943952f) continue;
            }
            check = 0;
        }
        if (check) {
            if (GScolsys2HitCollision(&hero, &target, myRadius, 0)) continue;
        }
        if (member) {
            peopleInfoBiosGetColBallSize(info);
            if (peopleInsideCheck(&hero, &target, &heroMember)) continue;
        }
        f32 area = dist * dist * (f32)fabs(ang) / 2.0f;
        GSlogWritef("talk ->  people(%d,%d)  len =%.2f  ang =%.2f  area =%.2f\n", other->group, other->id, dist, ang, area);
        u8 better = 0;
        if (area < bestArea) {
            better = 1;
        } else if (area == bestArea) {
            f32 a = (f32)fabs(ang);
            f32 b = (f32)fabs(bestAng);
            if (b < a) {
                better = 1;
            } else if (b == a && ang > 0.0f) {
                better = 1;
            }
        }
        if (better) {
            bestArea = area;
            best = other;
            bestAng = ang;
        }
    }
    return best;
}

}
