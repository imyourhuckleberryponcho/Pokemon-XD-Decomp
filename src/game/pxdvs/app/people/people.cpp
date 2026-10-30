#include <dolphin/types.h>
#pragma pool_strings off
#include "game/shared/floor_module.h"

struct GSvec {
    f32 x, y, z;
    GSvec() {}
};
struct GSquat {
    f32 x, y, z, w;
};
struct _GSmodel {
    u8 pad[0x74];
    s32 blendMode;
};
struct HumanCollInfo {
    u32 groupID, peopleID;
    f32 size, height;
};
struct GSpart;
struct GSlight;
struct FloorData;
enum GSmodelAnimType { GS_MODEL_ANIM_TYPE_0, GS_MODEL_ANIM_TYPE_1 };
enum GSpartMixType { GSpartMixType0 };

struct _GSmodelAnimCBData {
    u8 pad0[4];
    s32 index;
    void* user;
};

struct PeopleInfo {
    u8 unk0_0 : 6;
    u8 noWalkStart : 1;
    u8 unk0_7 : 1;
};
struct PeopleInfoOld {
    u8 flags;
};

struct PeopleNeckInfo {
    s8 index;
    f32 left, right, up, down;
    GSvec pos;
    GSvec rot;
};

struct _peopleMotionTable {
    s32 m[5];
};

struct tagPeopleWork {
    void setAnimType(GSmodelAnimType type);
    void setAnimFrame(f32 frame);
    void setAnimBlend(int index0, int index1);
    void setAnimIndex(int index);
    void setAnimRate(f32 rate, bool scaleBySpeed);
    bool isAnimLast() const;
    u32 getFlags() const;
    bool isWalkStartMotion() const;
    bool isAlwayBlendChara() const;
    bool isAnimBlend() const;
    bool isHero() const;
    bool isFollower() const;
    s32 getRunMotion();
    s32 getWalkMotion();

    u8 used;
    u8 saveFlags;
    u8 pad02[2];
    u32 searchID;
    _GSmodel* model;
    u8 active;
    u8 display;
    u8 rotating;
    u8 flagF;
    u32 flags;
    u32 groupID;
    u32 peopleID;
    u32 objectID;
    f32 walkRate;
    f32 runRate;
    f32 curRate;
    f32 f2C;
    f32 idleFrames;
    f32 walkFrames;
    f32 f38;
    f32 runFrames;
    f32 angle;
    f32 angleSpeed;
    s32 motion;
    u16 scriptHandle;
    u8 pad4E[2];
    s32 humanID;
    u8 moveType;
    u8 mode;
    u8 paused;
    u8 prevMoveType;
    f32 speed;
    GSvec startPos;
    GSvec destPos;
    u16 pointCount;
    u16 pointIndex;
    GSvec* points;
    u8 f7C;
    u8 pad7D[3];
    GSvec basePos;
    f32 randRadius;
    f32 timer;
    f32 timeBase;
    f32 timeRange;
    u32 motionType;
    u8 padA0[8];
    GSvec savedPos;
    GSvec lastPos;
    u8 neckReg;
    u8 neckF1;
    u8 neckF2;
    u8 neckF3;
    u8 neckMode;
    u8 padC5[3];
    GSvec neckTarget;
    GSvec neckGoal;
    GSvec neckCur;
    GSvec neckSaved;
    u32 neckGroupID;
    u32 neckPeopleID;
    f32 neckSpeed;
    f32 neckSpeedMax;
    f32 neckThreshold;
    u8 chestReg;
    u8 pad10D[3];
    GSvec chestRot;
    s32 attachGroupID;
    s32 attachID;
    s32 attachPart;
    f32 blendT;
    f32 blendStep;
    f32 f130;
    f32 startAngle;
    f32 f138;
    u8 chestUnreg;
    u8 waitAnim;
    u8 ownsRes;
    u8 animEnded;
    s32 followState;
    u8 pad144[8];
    u8 f14C;
    u8 f14D;
    u8 pad14E[2];
    f32 f150;
    u8 blend;
    u8 manualAnim;
    u8 pad156[6];
    u8 running;
    u8 slowDown;
    u8 pad15E[2];
    f32 moveDist;
    s32 motionTable[5];
    f32 talkDistance;
    u8 pad17C[2];
    u8 collFlags;
    u8 f17F;
    f32 rotRate;
    u8 pad184[0x1B0 - 0x184];
};

struct MarkRes {
    u32 groupID, peopleID;
};

extern "C" {
tagPeopleWork* peopleGet(u32 groupID, u32 peopleID);
void peopleSetFlagOn(u32 groupID, u32 peopleID, u32 flags);
void peopleSetFlagOff(u32 groupID, u32 peopleID, u32 flags);
void peopleSetFlags(u32 groupID, u32 peopleID, u32 flags);
u32 peopleGetFlags(u32 groupID, u32 peopleID);
void peopleSetDisp(u32 groupID, u32 peopleID, u8 disp);
void peopleSetCollision(u32 groupID, u32 peopleID, u8 enable);
void peopleGetPos(u32 groupID, u32 peopleID, GSvec* out);
void peopleSetPos(u32 groupID, u32 peopleID, GSvec* pos);
void peopleSetRot(u32 groupID, u32 peopleID, GSvec* rot);
void peopleSetRotXYZ(u32 groupID, u32 peopleID, f32 x, f32 y, f32 z);
void peopleRotateToAngle(u32 groupID, u32 peopleID, f32 angle, f32 rate);
bool peopleMoveAlongAngle(u32 groupID, u32 peopleID, f32 dist, f32 angle);
bool peopleMoveForward(u32 groupID, u32 peopleID, f32 dist);
void peopleWalkTo(u32 groupID, u32 peopleID, u8 keepRot, GSvec* dest);
bool peopleWaitSyncMotion(u32 groupID, u32 peopleID, u8 wait);
void peopleSetMotionType(tagPeopleWork* work, u32 type);
s32 peopleSetMotion(u32 groupID, u32 peopleID, s32 motion, s32 frame, bool loop);
void peopleSetNeckTargetHero(u32 groupID, u32 peopleID);
void peopleSetNeckTarget(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID);
void peopleMoveNeckTarget(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, f32 speed);
bool peopleSetDefaultMotionTable(u32 groupID, u32 peopleID);
void peopleDetach(u32 groupID, u32 peopleID, u8 restore);
void peopleAttachWithMode(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, u32 part, u8 mode);
void peopleDoAttach(_GSmodel* model, u32 targetGroupID, u32 targetPeopleID, u32 part, u8 mode);
void peopleAttach(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, s32 part);
void peopleClose(u32 groupID, u32 peopleID, bool freeRes);
u32 peopleGetHumanID(u32 groupID, u32 peopleID);
void _peopleDoNeckUpdate(tagPeopleWork* work);
void _peopleRegisterAnimMix(tagPeopleWork* work);
bool peopleOpenSub(tagPeopleWork* work, u32 groupID, u32 peopleID, u32 objectID);
void peopleTaskSwich();
bool peopleSetInfo(tagPeopleWork* work, u32 groupID, u32 peopleID, u32 objectID);
bool peopleChangeModel(tagPeopleWork* work, u32 groupID, u32 peopleID, u32 objectID);
bool _peopleSetMotionMain(u32 groupID, u32 peopleID, s32 motion, s32 frame, bool loop);
void _peopleSetMoveAnimation(tagPeopleWork* work);
tagPeopleWork* peopleSearchID(u32 searchID);
void peopleUpdateAnimation(tagPeopleWork* work, u8 byHero);
f32 peopleGetBlendFactor(f32 value, f32 lo, f32 hi);
f32 peopleVecCalcRotY(GSvec* a, GSvec* b, f32 base);

s32 peopleBiosGetMaxNum();
tagPeopleWork* peopleBiosGetWorkPtr(s32 index);
tagPeopleWork* peopleBiosGetNewWork();
tagPeopleWork* peopleBiosGetPeopleWork(u32 groupID, u32 peopleID);
tagPeopleWork* peopleBiosAllocWork(s32 count);
bool peopleBiosFreeWork(tagPeopleWork* work);
bool peopleBiosCheckFlag(tagPeopleWork* work, u32 flags);
void peopleBiosSetFlagOn(tagPeopleWork* work, u32 flags);
void peopleBiosSetFlagOff(tagPeopleWork* work, u32 flags);
void peopleBiosSetFlags(tagPeopleWork* work, u32 flags);
void peopleBiosSetCollision(tagPeopleWork* work, u8 enable);
void peopleBiosSetDispFlag(tagPeopleWork* work, u8 disp);
_GSmodel* peopleBiosGetModelPtr(tagPeopleWork* work);
void peopleBiosGetPos(tagPeopleWork* work, GSvec* out);
GSvec* peopleBiosGetPosPtr(tagPeopleWork* work);
void peopleBiosSetPos(tagPeopleWork* work, GSvec* pos);
void peopleBiosGetRot(tagPeopleWork* work, GSvec* out);
GSvec* peopleBiosGetRotPtr(tagPeopleWork* work);
void peopleBiosSetRot(tagPeopleWork* work, GSvec* rot);
GSvec* peopleBiosGetPrevPosPtr(tagPeopleWork* work);
void peopleBiosSetPrevPos(tagPeopleWork* work, GSvec* pos);
tagPeopleWork* peopleBiosGetTresureIDToPeopleWork(u32 treasureID);
u32 peopleBiosGetUseObjIDSize(u32 objectID);
s32 peopleBiosGetPushDataSize();
void peopleBiosPushData(void* buffer, u32 size);
void peopleBiosPopData(void* buffer, u32 size);
s32 peopleGetAnywaySaveSize();
void peopleMakeAnywaySaveData(void* data, s32 size);
void peopleRestoreAnywaySaveData(void* data, s32 size);
BOOL peopleFreeWalkList(u32 group, u32 id);

PeopleInfo* peopleInfoBiosGetPtr(u32 objectID);
s8 peopleInfoBiosGetNeckIndex(PeopleInfo* info);
f32 peopleInfoBiosGetNeckLeftLimit(PeopleInfo* info);
f32 peopleInfoBiosGetNeckRightLimit(PeopleInfo* info);
f32 peopleInfoBiosGetNeckUpLimit(PeopleInfo* info);
f32 peopleInfoBiosGetNeckDownLimit(PeopleInfo* info);
s8 peopleInfoBiosGetChestIndex(PeopleInfo* info);
f32 peopleInfoBiosGetWalkLength(PeopleInfo* info);
f32 peopleInfoBiosGetRunLength(PeopleInfo* info);
f32 peopleInfoBiosGetTalkDistance(PeopleInfo* info);
f32 peopleInfoBiosGetColBallSize(PeopleInfo* info);
u8 peopleInfoBiosGetColType(PeopleInfo* info);
bool peopleInfoBiosGetBoundCheck(PeopleInfo* info);
void peopleInfoBiosGetMotion(PeopleInfo* info, u8 kind, s32* motion, bool* loop);

void peoplePartAnimationSpeakStop(tagPeopleWork* work);
void peoplePartAnimationSpeakStart(tagPeopleWork* work);
void peoplePartAnimationBlinkStop(tagPeopleWork* work);
void peoplePartAnimationBlinkStart(tagPeopleWork* work);
void peoplePartAnimationBlinkOnce(tagPeopleWork* work);
void peoplePartAnimationBlink(tagPeopleWork* work);

void peopleTalkEnterFloor();
void peopleTalkLeaveFloor();
void peopleTalkMessageDaemon();
f32 peopleViewerGetPlaySpeedRate(tagPeopleWork* work);
void peopleViewerSetPlaySpeedRate(f32 rate);
void peopleViewerSetHeroPos(u32 pos);
void peopleViewerDisplayDaemonInfo(tagPeopleWork* work);
void peopleViewerDisplayAnimRate(tagPeopleWork* work, f32 rate);
void peopleViewerDisplayMoveRotInfo(tagPeopleWork* work);
void peopleViewerDisplayRandWalk();
bool peopleViewerIsCheckNpc(tagPeopleWork* work);
void peopleViewerThread();

bool GScolsys2HitCollision(GSvec* start, GSvec* end, GSvec* hitOut, f32 radius);
bool GScolsys2HitNpcCollision(GSvec* start, GSvec* end, GSvec* hitOut, f32 radius);
s32 GScolsys2HumanAddCurrentFloor(s32* id, HumanCollInfo* info);
s32 GScolsys2HumanCollision(s32 id, GSvec* from, GSvec* to, GSvec* out);
f32 GScolsys2HumanGetHumanRadius(s32 id);
f32 GScolsys2HumanGetWalkHeight(GSvec* pos);
s32 GScolsys2ThruGetEventID(GSvec* start, GSvec* end, void* out, f32 radius);
s32 GScolsys2ThruPassEventID(GSvec* start, GSvec* end, void* out);
s32 GScolsys2WalkGetHeight(GSvec* pos, f32* outHeights);
BOOL GScolsys2WalkGetLayer(GSvec* pos, u8* layer, u8* subLayer);
u8 GSgfxVideoGetVsyncRate();
u32 GSinputButtonsPressed(s32 pad);
GSlight* GSlightCreate();
void GSlightSetActive(GSlight* light, u8 active);
void GSlightSetPosition(GSlight* light, GSvec* position);
void GSlightSetTarget(GSlight* light, GSvec* target);
void GSlightSetType(GSlight* light, s32 type);
void GSlogWrite(const char*, ...);
void GSmodelAllPauseAnimation();
void GSmodelAllUnpauseAnimation();
void GSmodelAttachToGSpart(_GSmodel* model, GSpart* part, s32 mode, u8 inherit, u8 identity);
void GSmodelClearShadowFlags(_GSmodel* model, u32 flags);
void GSmodelDetachFromGSpart(_GSmodel* model, u8 restore);
void GSmodelDisableAnimBlend(_GSmodel* model);
void GSmodelEnableAnimBlend(_GSmodel* model);
void GSmodelFree(_GSmodel* model);
f32 GSmodelGetAnimFrame(_GSmodel* model);
f32 GSmodelGetAnimFrameCount(_GSmodel* model, s32 index);
void GSmodelGetAnimIndex(_GSmodel* model, s32* index, s32* blendIndex);
s32 GSmodelGetAnimType(_GSmodel* model);
void GSmodelGetFrameCount(_GSmodel* model, f32* count, f32* blendCount);
s32 GSmodelGetMaxAnimIndex(_GSmodel* model);
GSpart* GSmodelGetPart(_GSmodel* model, s32 index);
void GSmodelGetPosition(_GSmodel* model, GSvec* position);
GSvec* GSmodelGetPositionPtr(_GSmodel* model);
void GSmodelGetRotation(_GSmodel* model, GSvec* rotation);
u8 GSmodelGetVisibility(_GSmodel* model);
bool GSmodelHasAnimationEnded(_GSmodel* model);
bool GSmodelIsAnimating(_GSmodel* model);
bool GSmodelIsNullAnimation(_GSmodel* model, s32 index);
void GSmodelLinkTexAnimToAnim(_GSmodel* model, u8 link);
void GSmodelRecalculateBound(_GSmodel* model);
void GSmodelSetAnimEndedCallback(_GSmodel* model, void (*cb)(_GSmodel*, _GSmodelAnimCBData*), void* user);
void GSmodelSetAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetBlendAnimFrameForce(_GSmodel* model, f32 frame, f32 blendFrame);
void GSmodelSetBlendFactor(_GSmodel* model, f32 factor);
void GSmodelSetBoundCheck(_GSmodel* model, bool enable);
void GSmodelSetPosition(_GSmodel* model, GSvec* position);
void GSmodelSetRenderLayer(_GSmodel* model, s32 count, s32* layers);
void GSmodelSetRotation(_GSmodel* model, GSvec* rotation);
void GSmodelSetShadowFlags(_GSmodel* model, u32 flags);
void GSmodelSetShadowLight(_GSmodel* model, GSlight* light);
void GSmodelSetShadowSurface(_GSmodel* model, s32 count, void* surfaces);
void GSmodelSetTexAnimFrame(_GSmodel* model, f32 frame);
void GSmodelSetTexAnimIndex(_GSmodel* model, int index);
void GSmodelSetTexAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetVisibility(_GSmodel* model, u8 visible);
void GSmodelStartAnimation(_GSmodel* model);
void GSmodelStopAnimation(_GSmodel* model);
void GSpartFree(GSpart* part);
void GSpartGetTransform(GSpart* part, GSvec* pos, GSvec* rot, GSvec* scale);
void GSpartRegisterAnimMix(GSpart* part, s32 a, s32 b, f32 (*cb)(GSpart*, GSpartMixType, void*, GSvec*), void* user);
void GSpartUnregisterAnimMix(GSpart* part, s32 a);
void GSresChangeResourceAdress(void* mem, u32 grp, u32 id, void* freeFunc);
void GSresFreeResource(u32 grp, u32 id);
void GSresFreeResourceAllGroup(u32 id);
void* GSresGetResource(u32 grp, u32 id);
void GSresRegisterResource(void* mem, u32 grp, u32 id, void* freeFunc);
u8 GSsndPlayNow(u32 id);
u32 GSthreadGetCurrentThread();
void GSthreadSwitch();
void GSvecTransformQuat(GSvec* out, const GSquat* q, const GSvec* v);
u16 HSD_Rand(void);
f32 HSD_Randf();
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
f32 PSVECDistance(const GSvec* a, const GSvec* b);
f32 PSVECMag(const GSvec* v);
void PSVECNormalize(const GSvec* src, GSvec* unit);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* ab);
void C_QUATRotAxisRad(GSquat* q, const GSvec* axis, f32 rad);
double atan2(double y, double x);
inline f32 atan2f(f32 y, f32 x) { return (f32)atan2(y, x); }
double sin(double x);
double cos(double x);
double fmod(double x, double y);
void* memset(void* dst, int val, u32 n);
u8 dbgMenuIsOpen();
void floorBlockScriptThread(long handle);
void floorUnblockScriptThread(long handle);
void* floorCreateThread(s32 a, u32 stackSize, s32 c, void (*func)());
FloorData* floorDataBiosGetCurrentPtr();
u32 floorDataBiosGetFloorKind(FloorData* floor);
void* floorDataBiosGetShadowLightID(FloorData* floor);
void* floorDataBiosGetShadowReciveID(FloorData* floor, u32 idx);
s32 floorDataBiosGetShadowReciveNum(FloorData* floor);
s16 floorExecScriptResThread(int func, u32 group, u32 id);
void floorFreeResource(u32 group, u32 id);
u32 floorGetCurrentGroupID();
s32 floorGetFloorState();
s32 floorIsCurentScriptMode();
bool floorIsRunningThread(long handle);
void* floorOpenObject(u32 id);
void* floorReadResourceID(u32 group, u32 id);
s32 floorRegisterModule(s32 priority, s32 id, FloorModuleInterface* module);
u8* floorCharacterBiosFindByResID(u32 group, u32 id);
s32 floorCharacterBiosGetMoveSctID(u8* chr);
s32 floorCharacterBiosGetTalkSctID(u8* chr);
s32 getNameToFuncId__Q28GSscript4TigaFPCc(void* script, const char* name);
void* getHeroPtr__4HeroFv();
u32 getFollowerGrpID__4HeroFv(void*);
u32 getFollowerResID__4HeroFv(void*);
s32 heroGetFollower();
u8 heroIsPlayerPeople(u32 groupID, u32 resID);
void heroMoveDismissMember(u32);
void heroMoveJoinMember(u32);
void heroMoveMoveParty();
void heroMoveSetEventList(s32 kind, void* events, s32 count);
void gimmickBoxFloorInit();
f32 gimmickBoxGetBoxHeight();
bool gimmickBoxIsBox(tagPeopleWork* work);
bool gimmickBoxIsGimmickMoving();
bool gimmickBoxIsPushBoxFloor();
bool gimmickBoxOnBox(tagPeopleWork* work, GSvec* from, GSvec* to);
void gimmickBoxPushBox(tagPeopleWork* work);
void gimmickBoxSetKenShadowOnBoxIfOnBoxFloor(tagPeopleWork* work, void* surfaces, s32* count);
s32 scriptModelOpen(u32 resource);
void scriptModelSetMotion(u32 id, s32 a, s32 b, s32 c);
void soundOpenPlay(s32, s32, s32);
f32 timeGetLastFrameSec();
u32 timeGetLastFrameTime();
void FloorModuleInterface_clear(FloorModuleInterface* iface);
extern GSvec yAxisVector;
extern f32 __float_nan;
}

inline double fabs(double x) {
    return __fabs(x);
}

inline float fabsf(float x) {
    return (float)fabs(x);
}

inline int __fpclassifyf(float x) {
    switch ((*(s32*)&x) & 0x7F800000) {
    case 0x7F800000:
        if ((*(s32*)&x) & 0x007FFFFF) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(s32*)&x) & 0x007FFFFF) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

inline float sqrtf(float x) {
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (float)(x * guess);
    } else if (x < 0.0) {
        return __float_nan;
    } else if (__fpclassifyf(x) == 1) {
        return __float_nan;
    }
    return x;
}

static f32 _peopleGetChestRotationCB(GSpart*, GSpartMixType, void* user, GSvec* out);
static void _peopleClearTargetIfFollower(u32 groupID, u32 peopleID);
static f32 _peopleGetNeckRotationCB(GSpart*, GSpartMixType, void* user, GSvec* out);
static bool _peopleSideStepCheck();
void* floorGetCurentScript();
static const char* _peopleGetModuleName();
static u32 _peopleGetMagicNumber();
static f32 _getLastFrameSec();
static u32 _getLastFrameTime();
static void _peopleMoveRotate(tagPeopleWork* work);
static void _peopleMoveTypeLinear(tagPeopleWork* work);
static void _peopleMoveTypeList(tagPeopleWork* work, bool loop);
static void _peopleMoveTypeRandomRot(tagPeopleWork* work);
static void _peopleMoveTypeRandomWalk(tagPeopleWork* work);
static s32 _peopleMoveSub(tagPeopleWork* work);
static bool _peopleIsMoving(tagPeopleWork* work);
static void _peopleUpdateNeck(tagPeopleWork* work, f32 dist);
static f32 adjustPIPI(f32 angle);
static f32 adjust2PI(f32 angle);
static f32 _peopleGetDiffAngle(f32 a, f32 b);
static f32 _peopleGetDiffAngleFix(f32 a, f32 b);
static f32 _peopleGetDiffAngleFixForNeck(f32 a, f32 b, tagPeopleWork* work);
static f32 _peopleGetNearAngle(f32 angle);
static void _peopleRegisterChestPart(tagPeopleWork* work);
static void _peopleUnregisterChestPart(tagPeopleWork* work);
static void _peopleExecAnimEndCallBack(tagPeopleWork* work);
static void _peopleAnimEndCallback(_GSmodel* model, _GSmodelAnimCBData* data);
static void _peopleUpdateBlendAnimation(tagPeopleWork* work, f32 speed);
static void _peopleUpdateNoBlendAnimation(tagPeopleWork* work, f32 speed);
static void _peopleSetMotionSub(tagPeopleWork* work, _GSmodel* model, s32 motion, s32 frame, bool loop);
static void _peopleValidMotionTable(_GSmodel* model, _peopleMotionTable* table);
static bool _peopleSetAutoMotionFrameCount(tagPeopleWork* work);
static bool _peopleBreakWithWalkList(tagPeopleWork* work);
static bool _peopleBlockMoveScript(tagPeopleWork* work);
static void _peopleCloseSub(tagPeopleWork* work, bool freeWalkList, bool freeRes);
static bool _peopleAdjustPosition(tagPeopleWork* work, GSvec* pos, GSvec* saved);
static bool _peopleAdjustPositionSub(tagPeopleWork* work, GSvec* pos, GSvec* saved);
static void _peopleUpdateShadows(tagPeopleWork* work);
static void _peoplePostUpdateShadows();
static void _peopleInitShadow();
static bool _peopleOpenSubWithoutModel(tagPeopleWork* work, u32 groupID, u32 peopleID, u32 objectID);
static f32 _distanceXZ(GSvec* a, GSvec* b);
static void _registerNeck(tagPeopleWork* work);
static bool _getNeck(tagPeopleWork* work, PeopleNeckInfo* info);
static void _peopleMarkAnimEndCallback(_GSmodel* model, _GSmodelAnimCBData* data);

static f32 END_NEED_DISTANCE = 1.0f;
static u8 m_hero_move = 1;
static u8 m_bPeopleOpenWithModel = 1;
static u8 m_b_bikkuri;
static u32 m_change_people_objID;
static bool m_bMoveByHero;
static f32 m_hero_idling_time;
static f32 m_hero_next_special_idling_time;
static s32 m_before_special_effect;
static u8 m_peopleBlock;
static s32 _hModulePeople;
tagPeopleWork* g_pHero;
tagPeopleWork* g_pMana;
static GSlight* shadowLight[2];
static FloorModuleInterface _floorModulePeople;

static void _peopleClearTargetIfFollower(u32 groupID, u32 peopleID) {
    if (groupID == 0 && (peopleID == 0x65 || peopleID == 0x68 || peopleID == 0x69)) {
        tagPeopleWork* work = peopleGet(groupID, peopleID);
        if (work) {
            work->destPos.x = peopleBiosGetPosPtr(work)->x;
            work->destPos.y = peopleBiosGetPosPtr(work)->y;
            work->destPos.z = peopleBiosGetPosPtr(work)->z;
            work->moveType = 0;
        }
    }
}

static f32 _distanceXZ(GSvec* a, GSvec* b) {
    GSvec va = *a;
    GSvec vb = *b;
    va.y = 0.0f;
    vb.y = 0.0f;
    return PSVECDistance(&va, &vb);
}

static void _registerNeck(tagPeopleWork* work) {
    if (work->objectID) {
        PeopleInfo* info = peopleInfoBiosGetPtr(work->objectID);
        if (info) {
            s8 index = peopleInfoBiosGetNeckIndex(info);
            if (index >= 0 && !work->neckReg) {
                GSpart* part = GSmodelGetPart(work->model, index);
                if (part) {
                    GSpartRegisterAnimMix(part, 2, 0x20202, _peopleGetNeckRotationCB, work);
                    GSpartFree(part);
                    work->neckReg = 1;
                }
            }
        }
    }
}

static f32 _peopleGetNeckRotationCB(GSpart*, GSpartMixType, void* user, GSvec* out) {
    tagPeopleWork* work = (tagPeopleWork*)user;
    if (_peopleIsMoving(work) && !work->paused) {
        _peopleDoNeckUpdate(work);
    }
    out->x = work->neckCur.x;
    out->y = work->neckCur.y;
    out->z = work->neckCur.z;
    return 1.0f;
}

static bool _getNeck(tagPeopleWork* work, PeopleNeckInfo* info) {
    if (!info) {
        return false;
    }
    peopleBiosGetRot(work, &info->rot);
    PeopleInfo* pi = peopleInfoBiosGetPtr(work->objectID);
    if (!pi) {
        return false;
    }
    info->index = peopleInfoBiosGetNeckIndex(pi);
    if (info->index < 0) {
        return false;
    }
    info->left = peopleInfoBiosGetNeckLeftLimit(pi);
    info->right = peopleInfoBiosGetNeckRightLimit(pi);
    info->up = peopleInfoBiosGetNeckUpLimit(pi);
    info->down = peopleInfoBiosGetNeckDownLimit(pi);
    GSpart* part = GSmodelGetPart(work->model, info->index);
    if (!part) {
        return false;
    }
    GSpartGetTransform(part, &info->pos, 0, 0);
    GSpartFree(part);
    return true;
}

static bool _peopleSideStepCheck() {
    GSvec heroPos, manaPos, heroRot, manaRot;
    GSvec dir, toMana, p, hit, diff, norm, sum, np;

    if (!g_pHero || !g_pMana) {
        return false;
    }
    if (!g_pMana->used || !g_pMana->display) {
        return false;
    }
    if (g_pHero->curRate < 0.5f * (g_pHero->walkRate + g_pHero->runRate)) {
        return false;
    }
    if (!heroGetFollower()) {
        return false;
    }
    peopleBiosGetPos(g_pHero, &heroPos);
    peopleBiosGetPos(g_pMana, &manaPos);
    peopleBiosGetRot(g_pHero, &heroRot);
    peopleBiosGetRot(g_pMana, &manaRot);
    f32 heroRadius = GScolsys2HumanGetHumanRadius(g_pHero->humanID);
    f32 manaRadius = GScolsys2HumanGetHumanRadius(g_pMana->humanID);
    if (g_pMana->followState == 6) {
        f32 dist = PSVECDistance(&heroPos, &manaPos);
        f32 both = heroRadius + manaRadius;
        if (dist >= 5.0f + both || dist <= 0.1f + both) {
            g_pMana->followState = 0;
        }
    }
    s32 state = g_pMana->followState;
    if (state != 0 && state != 3 && state != 5) {
        return false;
    }
    if (heroPos.x == g_pHero->savedPos.x && heroPos.y == g_pHero->savedPos.y && heroPos.z == g_pHero->savedPos.z) {
        return false;
    }
    bool found = false;
    PSVECSubtract(&heroPos, &g_pHero->savedPos, &dir);
    PSVECSubtract(&manaPos, &heroPos, &toMana);
    f32 heroAngle = atan2(dir.x, dir.z);
    f32 manaAngle = atan2(toMana.x, toMana.z);
    f32 both = heroRadius + manaRadius;
    f32 step = 0.0f;
    f32 limit = 2.0f * both;
    for (; step <= limit; step += 1.0f) {
        p.x = heroPos.x;
        p.y = heroPos.y;
        p.z = heroPos.z;
        p.x = step * sin(heroAngle) + heroPos.x;
        p.z = step * cos(heroAngle) + heroPos.z;
        p.y = GScolsys2HumanGetWalkHeight(&p);
        if (PSVECDistance(&p, &manaPos) <= both) {
            if (step <= 3.0f) {
                return false;
            }
            found = true;
            break;
        }
    }
    if (found) {
        f32 angle;
        if (_peopleGetDiffAngleFix(heroAngle, manaAngle) < 0.0f) {
            angle = 1.5707964f + heroAngle;
            g_pMana->followState = 2;
        } else {
            angle = heroAngle - 1.5707964f;
            g_pMana->followState = 1;
        }
        bool clear = true;
        g_pMana->startPos.x = manaPos.x;
        g_pMana->startPos.y = manaPos.y;
        g_pMana->startPos.z = manaPos.z;
        f32 sideAngle = adjustPIPI(angle);
        for (f32 i = 0.0f; i <= 8.0f; i += 1.0f) {
            manaPos.x = i * sin(sideAngle) + g_pMana->startPos.x;
            manaPos.z = i * cos(sideAngle) + g_pMana->startPos.z;
            manaPos.y = GScolsys2HumanGetWalkHeight(&manaPos);
            if (GScolsys2HitNpcCollision(&g_pMana->startPos, &manaPos, 0, manaRadius)) {
                clear = false;
            }
            if (GScolsys2HumanCollision(g_pMana->humanID, &g_pMana->startPos, &manaPos, &hit) == 6) {
                clear = false;
            }
        }
        if (!clear) {
            g_pMana->followState = 0;
            f32 dist = PSVECDistance(&heroPos, &manaPos);
            if (!(dist < 0.00001f && dist > -0.00001f) && dist <= both) {
                PSVECSubtract(&manaPos, &heroPos, &diff);
                norm.x = diff.x;
                norm.y = diff.y;
                norm.z = diff.z;
                PSVECNormalize(&norm, &norm);
                PSVECScale(&norm, &norm, dist);
                PSVECAdd(&heroPos, &norm, &sum);
                np.x = sum.x;
                np.y = sum.y;
                np.z = sum.z;
                peopleBiosSetPos(g_pMana, &np);
            }
            return false;
        }
        g_pMana->destPos.x = manaPos.x;
        g_pMana->destPos.y = manaPos.y;
        g_pMana->destPos.z = manaPos.z;
        peopleSetFlagOn(g_pMana->groupID, g_pMana->peopleID, 8);
        g_pMana->rotating = 0;
        g_pMana->moveType = 1;
        g_pMana->angle = sideAngle;
        manaRot.y = adjustPIPI(3.1415927f + heroAngle);
        peopleBiosSetRot(g_pMana, &manaRot);
        _peopleMoveTypeLinear(g_pMana);
        return true;
    }
    return false;
}

extern "C" {
void peopleSpeakStop(u32 groupID, u32 peopleID) {
    peoplePartAnimationSpeakStop(peopleGet(groupID, peopleID));
}

void peopleSpeakStart(u32 groupID, u32 peopleID) {
    peoplePartAnimationSpeakStart(peopleGet(groupID, peopleID));
}

void peopleBlinkStop(u32 groupID, u32 peopleID) {
    peoplePartAnimationBlinkStop(peopleGet(groupID, peopleID));
}

void peopleBlinkStart(u32 groupID, u32 peopleID) {
    peoplePartAnimationBlinkStart(peopleGet(groupID, peopleID));
}

void peopleBlinkOnce(u32 groupID, u32 peopleID) {
    peoplePartAnimationBlinkOnce(peopleGet(groupID, peopleID));
}

tagPeopleWork* peopleGet(u32 groupID, u32 peopleID) {
    return peopleBiosGetPeopleWork(groupID, peopleID);
}
}

extern "C" bool peopleReadObject(u32 groupID, u32 peopleID, u32 objectID);

static void _peopleLoadThread() {
    void* hero = getHeroPtr__4HeroFv();
    u32 groupID = getFollowerGrpID__4HeroFv(hero);
    u32 resID = getFollowerResID__4HeroFv(hero);
    if (peopleGet(groupID, resID)) {
        switch (resID) {
        case 0x65:
            heroMoveDismissMember(2);
            heroMoveDismissMember(3);
            heroMoveJoinMember(1);
            break;
        case 0x68:
            heroMoveDismissMember(1);
            heroMoveDismissMember(3);
            heroMoveJoinMember(2);
            break;
        case 0x69:
            heroMoveDismissMember(1);
            heroMoveDismissMember(2);
            heroMoveJoinMember(3);
            break;
        }
        peopleReadObject(groupID, resID, m_change_people_objID);
    }
}

static void _peopleEnterFloor(unsigned int groupID, FloorEnterMode mode) {
    if (!(floorDataBiosGetFloorKind(floorDataBiosGetCurrentPtr()) != 2 && (mode == 0 || mode == 1 || mode == 3))) {
        return;
    }
    m_bPeopleOpenWithModel = 1;
    peopleTalkEnterFloor();
    if (groupID == 0xFA1) {
        floorCreateThread(0x40, 0, 1, peopleViewerThread);
    }
    for (s32 i = 0; i < peopleBiosGetMaxNum(); i++) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(i);
        if (work) {
            work->f138 = 0.0f;
        }
    }
    peopleViewerSetPlaySpeedRate(1.0f);
    m_hero_move = 1;
    gimmickBoxFloorInit();
    switch (HSD_Rand() % 3) {
    case 0:
        m_before_special_effect = 0x13;
        break;
    case 1:
        m_before_special_effect = 0x14;
        break;
    default:
        m_before_special_effect = 0x15;
        break;
    }
    m_hero_idling_time = 0.0f;
    m_hero_next_special_idling_time = 4.0f * HSD_Randf() + 8.0f;
    peopleSetMotion(0, 0x64, 3, false, 1);
}

extern "C" {
f32 peopleGetSpeed(u32 groupID, u32 peopleID) {
    GSvec pos;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    peopleBiosGetPos(work, &pos);
    f32 dist = PSVECDistance(&pos, &work->lastPos);
    work->lastPos.x = pos.x;
    work->lastPos.y = pos.y;
    work->lastPos.z = pos.z;
    return dist;
}

bool peopleRunOrNot(u32 groupID, u32 peopleID) {
    GSvec pos;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    peopleBiosGetPos(work, &pos);
    f32 dist = PSVECDistance(&pos, &work->lastPos);
    work->lastPos.x = pos.x;
    work->lastPos.y = pos.y;
    work->lastPos.z = pos.z;
    return dist > work->walkRate ? 1 : 0;
}

void _peopleDoNeckUpdate(tagPeopleWork* work) {
    _peopleUpdateNeck(work, 75.0f);
}

bool peopleWalkPauseTalkMode(u32 groupID, u32 peopleID, u8 pause) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    if (pause) {
        work->prevMoveType = work->moveType;
        switch (work->moveType) {
        case 4:
        case 5:
            work->moveType = 0;
            break;
        }
    } else {
        u8 prev = work->prevMoveType;
        switch (prev) {
        case 4:
        case 5:
            work->moveType = prev;
            work->mode = 0;
            work->timer = 1.0f;
            break;
        }
    }
    return true;
}

bool peopleWalkPause(u32 groupID, u32 peopleID, u8 pause) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    if (work->moveType == 0) {
        return true;
    }
    if (pause) {
        if (!work->paused) {
            work->paused = 1;
            peopleSetMotionType(work, 1);
        }
        return true;
    }
    if (work->paused) {
        work->paused = 0;
    }
    return false;
}

void peopleUpdateShadow() {
    tagPeopleWork* work;
    for (s32 i = peopleBiosGetMaxNum(); i-- > 0;) {
        work = peopleBiosGetWorkPtr(i);
        if (work->used && work->model && work->display) {
            if (peopleBiosCheckFlag(work, 0x2000)) {
                GSmodelClearShadowFlags(work->model, 1);
            } else {
                GSmodelSetShadowFlags(work->model, 1);
            }
            _peopleUpdateShadows(work);
        }
    }
    _peoplePostUpdateShadows();
}

void peopleDaemon() {
    s32 prevIndex, prevBlend, curIndex, curBlend;
    f32 rate = GSgfxVideoGetVsyncRate();
    f32 scale = (30.0f * timeGetLastFrameTime()) / rate;
    if (!dbgMenuIsOpen() && _getLastFrameTime()) {
        if (_getLastFrameSec() == 0.0f) {
            return;
        }
        if ((s16)floorGetFloorState() == 4 || floorGetFloorState() == 5) {
            heroMoveMoveParty();
            peopleTalkMessageDaemon();
            _peopleSideStepCheck();
            for (s32 i = peopleBiosGetMaxNum(); i-- > 0;) {
                peopleBiosGetWorkPtr(i);
            }
            for (s32 i = peopleBiosGetMaxNum(); i-- > 0;) {
                tagPeopleWork* work = peopleBiosGetWorkPtr(i);
                if (work->used && work->model) {
                    if (peopleBiosCheckFlag(work, 0x40000)) {
                        _peopleCloseSub(work, true, false);
                    } else {
                        GSmodelGetAnimIndex(work->model, &prevIndex, &prevBlend);
                        work->collFlags = 0;
                        if (GSmodelHasAnimationEnded(work->model)) {
                            _peopleExecAnimEndCallBack(work);
                        }
                        peoplePartAnimationBlink(work);
                        work->curRate = work->speed;
                        work->moveDist = 0.0f;
                        if (_peopleIsMoving(work) && !work->paused) {
                            switch (work->moveType) {
                            case 1:
                                _peopleMoveTypeLinear(work);
                                break;
                            case 2:
                                _peopleMoveTypeList(work, false);
                                break;
                            case 3:
                                _peopleMoveTypeList(work, true);
                                break;
                            case 4:
                                _peopleMoveTypeRandomWalk(work);
                                break;
                            case 5:
                                _peopleMoveTypeRandomRot(work);
                                break;
                            }
                        }
                        if (scale == 0.0f ||
                            (_distanceXZ(peopleBiosGetPosPtr(work), peopleBiosGetPrevPosPtr(work)) < 0.00001f &&
                             _distanceXZ(peopleBiosGetPosPtr(work), peopleBiosGetPrevPosPtr(work)) > -0.00001f)) {
                            work->curRate = 0.0f;
                        } else {
                            work->curRate = PSVECDistance(peopleBiosGetPosPtr(work), peopleBiosGetPrevPosPtr(work)) / scale;
                        }
                        peopleViewerDisplayDaemonInfo(work);
                        _peopleMoveRotate(work);
                        peopleUpdateAnimation(work, true);
                        gimmickBoxPushBox(work);
                        GSvec* pos = peopleBiosGetPosPtr(work);
                        GSvec* prev = peopleBiosGetPrevPosPtr(work);
                        prev->x = pos->x;
                        prev->y = pos->y;
                        prev->z = pos->z;
                        work->animEnded = 0;
                        GSmodelGetAnimIndex(work->model, &curIndex, &curBlend);
                        if (!work->blend && curBlend != -1) {
                            work->setAnimIndex(curBlend);
                        }
                        if (prevIndex != curIndex || prevBlend != curBlend || (work->flags & 0x4000)) {
                            work->flags &= ~0x4000;
                            GSmodelStartAnimation(work->model);
                        }
                    }
                }
            }
            static bool bCameraMove = true;
            if (bCameraMove) {
                peopleViewerSetHeroPos(0);
            }
            peopleUpdateShadow();
        }
    }
}
}

static void _peopleMarkAnimEndCallback(_GSmodel* model, _GSmodelAnimCBData* data) {
    MarkRes* res = (MarkRes*)data->user;
    GSmodelSetVisibility(model, 0);
    peopleSetFlagOn(res->groupID, res->peopleID, 0x40000);
}

extern "C" {
void peopleDispMark(u32 groupID, u32 peopleID) {
    extern void peopleAttach(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, s8 part);
    static MarkRes markRes;
    u32 floorGroup;
    u32 markID;
    s32 neck = 0;
    PeopleInfo* info;
    floorGroup = floorGetCurrentGroupID();
    markID = scriptModelOpen(0x0EBB0400);
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work && (info = peopleInfoBiosGetPtr(work->objectID))) {
        neck = peopleInfoBiosGetNeckIndex(info);
    }
    m_b_bikkuri = 1;
    if ((s8)neck >= 0) {
        peopleAttach(floorGroup, markID, groupID, peopleID, neck);
    } else {
        peopleAttach(floorGroup, markID, groupID, peopleID, 0);
    }
    m_b_bikkuri = 0;
    tagPeopleWork* mark = peopleGet(floorGroup, markID);
    if (mark) {
        peopleBiosSetFlagOn(mark, 0x2000);
    }
    _GSmodel* model = (_GSmodel*)GSresGetResource(floorGroup, markID);
    if (model) {
        s32 layers[1] = { 4 };
        GSmodelSetRenderLayer(model, 1, layers);
        GSmodelClearShadowFlags(model, 1);
    }
    markRes.groupID = floorGroup;
    markRes.peopleID = markID;
    GSmodelSetAnimEndedCallback(model, _peopleMarkAnimEndCallback, &markRes);
    scriptModelSetMotion(markID, 0, 0, 0);
    GSsndPlayNow(0x16);
}

void peopleFallAppear(u32 groupID, u32 peopleID, f32 height) {
    GSvec pos;
    s32 t = 0;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        peopleGetPos(groupID, peopleID, &pos);
        pos.y = height;
        peopleSetDisp(groupID, peopleID, true);
        soundOpenPlay(0x5A2, 0, 0x7F);
        peopleSetMotionType(work, 7);
        do {
            t++;
            pos.y = pos.y - (((f32)t * (0.4f * (f32)t)) / 2.0f - ((f32)(t - 1) * (0.4f * (f32)(t - 1))) / 2.0f);
            peopleSetPos(groupID, peopleID, &pos);
            if (pos.y <= 0.0f) {
                pos.y = 0.0f;
                peopleSetPos(groupID, peopleID, &pos);
                break;
            }
            GSthreadSwitch();
        } while (true);
        soundOpenPlay(0x5A3, 0, 0x7F);
        peopleSetMotionType(work, 8);
        peopleWaitSyncMotion(groupID, peopleID, 1);
        peopleSetMotionType(work, 1);
    }
}

void peopleTermEvent(u32 groupID, u32 peopleID) {
    _peopleClearTargetIfFollower(groupID, peopleID);
    peopleSetFlagOn(groupID, peopleID, 0x100);
    peopleSetFlagOn(groupID, peopleID, 0x400);
    peopleSetFlagOff(groupID, peopleID, 0x80000000);
}

void peopleInitEvent(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work && work->followState == 0) {
        _peopleClearTargetIfFollower(groupID, peopleID);
    }
    peopleSetFlagOff(groupID, peopleID, 0x100);
    peopleSetFlagOff(groupID, peopleID, 0x400);
    peopleSetFlagOn(groupID, peopleID, 0x80000000);
}

bool peopleUnblockMoveScript(u32 searchID) {
    tagPeopleWork* work = peopleSearchID(searchID);
    if (!work) {
        return false;
    }
    work->active = 1;
    if (floorIsCurentScriptMode()) {
        floorUnblockScriptThread(work->scriptHandle);
    }
    return true;
}

void peopleBlockMoveScript(u32 searchID) {
    _peopleBlockMoveScript(peopleSearchID(searchID));
}

bool peopleExecMoveScript(u32 groupID, u32 peopleID, u32 func) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    if (!func) {
        return false;
    }
    work->scriptHandle = floorExecScriptResThread(func, groupID, peopleID);
    return true;
}

s32 peopleGetMoveSctID(u32 groupID, u32 peopleID) {
    return floorCharacterBiosGetMoveSctID(floorCharacterBiosFindByResID(groupID, peopleID));
}

s32 peopleGetTalkSctID(u32 groupID, u32 peopleID) {
    if (peopleID == 0x65 || peopleID == 0x68 || peopleID == 0x69) {
        return getNameToFuncId__Q28GSscript4TigaFPCc(floorGetCurentScript(), "talk_follower");
    }
    u8* chr = floorCharacterBiosFindByResID(groupID, peopleID);
    if (chr) {
        return floorCharacterBiosGetTalkSctID(chr);
    }
    return 0;
}

bool peopleStartRotRandom(u32 groupID, u32 peopleID, f32 base, f32 range) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    work->moveType = 5;
    work->mode = 0;
    peopleSetFlagOn(groupID, peopleID, 8);
    peopleBiosGetPos(work, &work->basePos);
    work->timer = work->timeRange * (2.0f * HSD_Randf() - 1.0f) + work->timeBase;
    work->timeBase = base;
    work->timeRange = range;
    work->curRate = work->walkRate;
    return true;
}

bool peopleStartWalkRandom(u32 groupID, u32 peopleID, f32 radius) {
    s32 index, blendIndex;
    f32 count, blendCount, count2, blendCount2;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    work->moveType = 4;
    work->mode = 0;
    peopleSetFlagOn(groupID, peopleID, 8);
    peopleBiosGetPos(work, &work->basePos);
    work->randRadius = radius;
    work->timer = 0.0f;
    work->timeBase = 5.0f;
    work->timeRange = 3.0f;
    work->curRate = work->walkRate;
    if (work->isAlwayBlendChara()) {
        _GSmodel* model = work->model;
        GSmodelGetAnimIndex(model, &index, &blendIndex);
        GSmodelGetFrameCount(model, &count, &blendCount);
        f32 frame = GSmodelGetAnimFrame(model);
        f32 rate1 = 0.0f;
        rate1 = count <= 0.0f ? rate1 : frame / count;
        f32 rate2 = 0.0f;
        if (blendCount > 0.0f) {
            rate2 = frame / blendCount;
        }
        if (index != work->motionTable[0] || blendIndex != -1) {
            work->setAnimIndex(work->motionTable[0]);
            GSmodelGetFrameCount(model, &count2, &blendCount2);
            rate1 = blendIndex != -1 ? rate1 : rate2;
            work->setAnimFrame(count2 * rate1);
            work->setAnimType(GS_MODEL_ANIM_TYPE_1);
            work->setAnimRate(0.5f, true);
            GSmodelStartAnimation(work->model);
        }
    }
    return true;
}

void peopleTaskSwich() {
    GSthreadSwitch();
}

void peopleDetach(u32 groupID, u32 peopleID, u8 restore) {
    _GSmodel* model;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work && (model = (_GSmodel*)GSresGetResource(groupID, peopleID)) && work->attachPart >= 0) {
        work->attachGroupID = -1;
        work->attachID = -1;
        work->attachPart = -1;
        GSmodelDetachFromGSpart(model, restore);
        _peopleClearTargetIfFollower(groupID, peopleID);
    }
}

void peopleAttach(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, s32 part) {
    peopleAttachWithMode(groupID, peopleID, targetGroupID, targetPeopleID, part, 0);
}

void peopleAttachWithMode(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, u32 part, u8 mode) {
    GSvec rot;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        _GSmodel* model = (_GSmodel*)GSresGetResource(groupID, peopleID);
        if (model) {
            peopleDetach(groupID, peopleID, 1);
            work->attachGroupID = targetGroupID;
            work->attachID = targetPeopleID;
            work->attachPart = part;
            peopleDoAttach(model, targetGroupID, targetPeopleID, part, mode);
            work->rotating = 0;
            peopleBiosGetRot(work, &rot);
            work->angle = rot.y;
        }
    }
}

void peopleDoAttach(_GSmodel* model, u32 targetGroupID, u32 targetPeopleID, u32 part, u8 mode) {
    _GSmodel* target = (_GSmodel*)GSresGetResource(targetGroupID, targetPeopleID);
    if (target) {
        s32 type = 7;
        if (mode == 1) {
            type = 8;
        }
        GSpart* p = GSmodelGetPart(target, part);
        if (p) {
            GSmodelAttachToGSpart(model, p, type, 0, m_b_bikkuri);
            GSpartFree(p);
        }
    }
}

void peopleSetWalkSpeed(u32 groupID, u32 peopleID, f32 speed, u32 kind) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work || !work->model) {
        return;
    }
    if (kind == 1) {
        work->walkRate = speed / work->walkFrames;
        return;
    }
    work->runRate = speed / work->runFrames;
}

void peopleSetSpeedRate(u32 groupID, u32 peopleID, f32 rate) {
    s32 index, blendIndex;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work || !work->model) {
        return;
    }
    {
        GSmodelGetAnimIndex(work->model, &index, &blendIndex);
        if (rate < 0.00001f && rate > -0.00001f) {
            work->speed = 0.0f;
            if (!work->manualAnim) {
                peopleSetMotion(work->groupID, work->peopleID, work->motionTable[0], false, 1);
            }
        } else if (rate < 1.5f) {
            work->speed = work->walkRate;
            if (work->running) {
                work->running = 0;
                if ((index == work->motionTable[1] || index == work->motionTable[2]) && !work->isAlwayBlendChara() &&
                    !work->manualAnim) {
                    peopleSetMotion(work->groupID, work->peopleID, work->motionTable[1], false, 1);
                }
            }
        } else {
            work->speed = work->runRate;
            if (!work->running) {
                work->running = 1;
                if ((index == work->motionTable[1] || index == work->motionTable[2]) && !work->isAlwayBlendChara() &&
                    !work->manualAnim) {
                    peopleSetMotion(work->groupID, work->peopleID, work->motionTable[2], false, 1);
                }
            }
        }
    }
}
}

#pragma push
#pragma optimize_for_size on
static void _peopleMoveRotate(tagPeopleWork* work) {
    GSvec rot;
    f32 dir, step, diffStart, diffNow, rotateStep, scale, time;
    u32 vsync;
    peopleBiosGetRot(work, &rot);
    rot.y = adjustPIPI(rot.y);
    work->angle = adjustPIPI(work->angle);
    if (peopleBiosCheckFlag(work, 8) || work->peopleID != 0x64) {
        if (work->rotating) {
            dir = adjustPIPI(_peopleGetDiffAngleFixForNeck(work->angle, rot.y, work));
            step = 0.03f * work->rotRate;
            diffNow = fabsf(_peopleGetDiffAngleFixForNeck(work->angle, rot.y, work));
            diffStart = fabsf(_peopleGetDiffAngleFixForNeck(work->startAngle, rot.y, work));
            if (diffStart < diffNow) {
                if (rotateStep < step) rotateStep = step;
            } else {
                rotateStep = -step;
            }
            work->angleSpeed += rotateStep;
            if (work->angleSpeed < step) {
                work->angleSpeed = step;
            }
            _peopleRegisterChestPart(work);
            vsync = GSgfxVideoGetVsyncRate();
            time = (f32)timeGetLastFrameTime();
            if (work->angleSpeed * peopleViewerGetPlaySpeedRate(work) * ((30.0f * time) / (f32)vsync) > diffNow) {
                rot.y = work->angle;
                work->rotating = 0;
                work->angleSpeed = 0.0f;
                work->rotRate = 1.0f;
                work->chestRot.y = 0.0f;
                if (!work->neckMode) {
                    work->neckCur.y = 0.0f;
                }
            } else {
                f32 signedStep;
                if (dir > 0.0f) {
                    signedStep = work->angleSpeed;
                } else {
                    signedStep = -work->angleSpeed;
                }
                vsync = GSgfxVideoGetVsyncRate();
                time = (f32)timeGetLastFrameTime();
                rot.y += signedStep * (peopleViewerGetPlaySpeedRate(work) * ((30.0f * time) / (f32)vsync));
            }
        }
    } else if (work->groupID == 0 && work->peopleID == 0x64) {
        if (!work->rotating) {
            _peopleUnregisterChestPart(work);
        } else {
            if (rot.y - work->angle > 3.2986722f) {
                rot.y -= 6.2831855f;
            } else if (work->angle - rot.y > 3.2986722f) {
                rot.y += 6.2831855f;
            }
            f32 diff = work->angle - rot.y;
            scale = diff / (10.0f * (2.3f - work->rotRate));
            _peopleRegisterChestPart(work);
            vsync = GSgfxVideoGetVsyncRate();
            time = (f32)timeGetLastFrameTime();
            rot.y += scale * peopleViewerGetPlaySpeedRate(work) * ((30.0f * time) / (f32)vsync);
        }
    }
    if (work->attachPart < 0) {
        if (peopleViewerIsCheckNpc(work)) {
            _peopleGetDiffAngleFixForNeck(rot.y, rot.y, work);
            peopleViewerDisplayMoveRotInfo(work);
        }
        peopleBiosSetRot(work, &rot);
    }
}
#pragma pop

static f32 _peopleGetDiffAngleFixForNeck(f32 a, f32 b, tagPeopleWork*) {
    return _peopleGetDiffAngle(a, b);
}

static f32 _peopleGetDiffAngleFix(f32 a, f32 b) {
    return _peopleGetDiffAngle(a, b);
}

static f32 _peopleGetDiffAngle(f32 a, f32 b) {
    f32 first = adjustPIPI(a);
    return _peopleGetNearAngle(first - adjustPIPI(b));
}

static f32 _peopleGetNearAngle(f32 angle) {
    if (fabsf(angle) >= 3.1415927f) {
        if (angle < 0.0f) {
            return 6.2831855f + angle;
        }
        return angle - 6.2831855f;
    }
    return angle;
}

static f32 adjustPIPI(f32 angle) {
    f32 result = fmod(6.2831855f + angle, 6.2831854820251465);
    if (result > 3.1415927f) {
        result -= 6.2831855f;
    }
    return result;
}

static f32 adjust2PI(f32 angle) {
    return fmod(6.2831855f + angle, 6.2831854820251465);
}

static void _peopleMoveTypeRandomRot(tagPeopleWork* work) {
    switch (work->mode) {
    case 0:
        if (work->timer > 0.0f) {
            work->timer = work->timer - _getLastFrameSec();
            if (work->timer < 0.0f) {
                work->timer = 0.0f;
                return;
            }
        } else {
            work->mode = 1;
    case 1: {
            f32 rnd = 2.0f * HSD_Randf() - 1.0f;
            f32 target = fmod(6.2831855f + (1.5707964f * rnd + (3.1415927f + work->angle)), 6.2831854820251465);
            f32 rate = 1.0f;
            if (work->speed > 0.1f + work->walkRate) {
                rate = 2.0f;
            }
            peopleRotateToAngle(work->groupID, work->peopleID, target, rate);
            work->mode = 2;
    }
    case 2:
            work->timer = work->timeRange * (2.0f * HSD_Randf() - 1.0f) + work->timeBase;
            work->mode = 0;
            return;
        }
        break;
    }
}

static void _peopleMoveTypeRandomWalk(tagPeopleWork* work) {
    f32 dz;
    f32 rate = 1.0f;
    switch (work->mode) {
    case 0:
        peopleViewerDisplayRandWalk();
        if (work->timer > 0.0f) {
            work->timer = work->timer - _getLastFrameSec();
            if (work->timer <= 0.0f) {
                work->timer = 0.0f;
                goto next;
            }
        } else {
        next:
            if (GSmodelHasAnimationEnded(work->model)) {
                work->mode = 1;
    case 1:
                peopleBiosGetPos(work, &work->startPos);
                peopleBiosGetPos(work, &work->destPos);
                int tries = 0;
                do {
                    f32 angle = 6.2831855f * HSD_Randf();
                    work->destPos.x = work->randRadius * (f32)sin(angle) + work->basePos.x;
                    work->destPos.z = work->randRadius * (f32)cos(angle) + work->basePos.z;
                    work->destPos.y = GScolsys2HumanGetWalkHeight(&work->destPos);
                    if (_distanceXZ(&work->destPos, &work->startPos) > 6.0f * END_NEED_DISTANCE) {
                        break;
                    }
                    tries++;
                } while (tries < 10);
                dz = work->destPos.z - peopleBiosGetPosPtr(work)->z;
                f32 target = atan2(work->destPos.x - peopleBiosGetPosPtr(work)->x, dz);
                if (work->speed > 0.1f + work->walkRate) {
                    rate = 2.0f;
                }
                peopleRotateToAngle(work->groupID, work->peopleID, target, rate);
                _peopleSetMoveAnimation(work);
                work->mode = 2;
    case 2:
                if (_peopleMoveSub(work)) {
                    if (work->collFlags & 1) {
                        if (work->speed > 0.1f + work->walkRate) {
                            rate = 2.0f;
                        }
                        peopleRotateToAngle(work->groupID, work->peopleID, 3.1415927f + work->angle, rate);
                    }
                    work->timer = work->timeRange * (2.0f * HSD_Randf() - 1.0f) + work->timeBase;
                    work->mode = 0;
                }
            }
        }
        return;
    }
}

static void _peopleMoveTypeList(tagPeopleWork* work, bool loop) {
    GSvec rot;
    f32 maxRotSpeed, speed, angle, dist, dist2, factor, rotRate, rate, target;
    bool first = false;
    bool arrived;
    rate = 2.0f;
    if (work->running) {
        speed = work->runRate;
    } else {
        speed = work->walkRate;
    }
    switch (work->mode) {
    case 0:
    case 1:
        if (work->points) {
            first = true;
            GSvec* p = &work->points[work->pointIndex];
            work->destPos.x = p->x;
            work->destPos.y = p->y;
            work->destPos.z = p->z;
            work->mode = 2;
            goto move;
        }
        break;
    case 2:
    move:
        arrived = false;
        if ((work->pointIndex >= work->pointCount - 1 && work->moveType == 2) || work->f7C) {
            dist = PSVECDistance(peopleBiosGetPosPtr(work), &work->destPos);
            f32 vsync = (u8)GSgfxVideoGetVsyncRate();
            if (dist < peopleViewerGetPlaySpeedRate(work) * (speed * ((30.0f * (f32)(timeGetLastFrameTime())) / vsync))) {
                arrived = true;
            }
        } else {
            if (PSVECDistance(peopleBiosGetPosPtr(work), &work->destPos) < 5.0f) {
                arrived = true;
            }
        }
        if (arrived) {
            work->pointIndex++;
            if (work->pointIndex >= work->pointCount) {
                if (loop) {
                    work->pointIndex = 0;
                } else {
                    peopleSetPos(work->groupID, work->peopleID, &work->destPos);
                    work->moveType = 0;
                    return;
                }
            }
            GSvec* p = &work->points[work->pointIndex];
            work->destPos.x = p->x;
            work->destPos.y = p->y;
            work->destPos.z = p->z;
        }
        {
            f32 dz = work->destPos.z - peopleBiosGetPosPtr(work)->z;
            target = atan2(work->destPos.x - peopleBiosGetPosPtr(work)->x, dz);
        }
        if (work->f7C || work->pointCount <= 2 || first) {
            angle = target;
            if (first) {
                peopleBiosGetRotPtr(work)->y = target;
            }
        } else {
            if (work->pointIndex) {
                static f32 max_rot_speed = 5.0f;
                dist = PSVECDistance(&work->points[work->pointIndex], peopleBiosGetPosPtr(work));
                if (dist < PSVECDistance(&work->points[work->pointIndex - 1], &work->points[work->pointIndex])) {
                    factor = peopleGetBlendFactor(dist, 0.0f, 0.0f);
                    rotRate = 2.0f * factor + max_rot_speed * (1.0f - factor);
                    if (rotRate > 2.0f) {
                        rate = rotRate;
                    }
                }
                dist2 = PSVECDistance(&work->points[work->pointIndex - 1], peopleBiosGetPosPtr(work));
                if (dist2 < PSVECDistance(&work->points[work->pointIndex - 1], &work->points[work->pointIndex])) {
                    factor = peopleGetBlendFactor(dist2, 0.0f, 0.0f);
                    rotRate = 2.0f * factor + max_rot_speed * (1.0f - factor);
                    if (rate < rotRate) {
                        rate = rotRate;
                    }
                }
            }
            peopleBiosGetRot(work, &rot);
            angle = adjustPIPI(rot.y);
            if (fabsf(57.29578f * adjustPIPI(angle - target)) > 90.0f) {
                angle = target;
            }
        }
        peopleRotateToAngle(work->groupID, work->peopleID, target, rate);
        peopleMoveAlongAngle(work->groupID, work->peopleID, speed, angle);
    }
}

static bool _peopleBreakWithWalkList(tagPeopleWork* work) {
    u8 type = work->moveType;
    if (type == 3) {
        return false;
    }
    if (type != 2 || work->pointIndex == 0 || work->pointIndex >= work->pointCount - 1) {
        return true;
    }
    return false;
}

static void _peopleMoveTypeLinear(tagPeopleWork* work) {
    if (_peopleMoveSub(work) == 1) {
        if (_peopleBreakWithWalkList(work)) {
            work->moveType = 0;
        }
        work->followState = 0;
    }
}

static s32 _peopleMoveSub(tagPeopleWork* work) {
    GSvec delta;
    f32 speed;
    PSVECSubtract(&work->destPos, peopleBiosGetPosPtr(work), &delta);
    delta.y = 0.0f;
    if (!(PSVECMag(&delta) < 0.00001f) || !(PSVECMag(&delta) > -0.00001f)) {
        work->angle = atan2(delta.x, delta.z);
    }
    switch (work->followState) {
    case 1:
    case 2:
    case 4:
        speed = 0.53333336f;
        break;
    case 3:
        speed = work->f2C;
        break;
    default:
        if (!work->running) {
            speed = work->walkRate;
        } else {
            speed = work->runRate;
        }
        break;
    }
    if (!peopleMoveForward(work->groupID, work->peopleID, speed)) {
        return 2;
    }
    f32 dist = _distanceXZ(&work->destPos, peopleBiosGetPosPtr(work));
    if (dist < 0.00001f && dist > -0.00001f) {
        if (work->isHero()) {
            peopleBiosSetFlagOff(work, 8);
        } else if (peopleBiosCheckFlag(work, 8) && !work->isAlwayBlendChara() && work->isAnimBlend() && !work->animEnded) {
            return false;
        }
        work->moveDist = 0.0f;
        return true;
    }
    return false;
}

extern "C" {
void peopleUpdateAnimation(tagPeopleWork* work, u8 byHero) {
    s32 index;
    PeopleInfo* info;
    m_bMoveByHero = byHero == 0;
    if (work->moveType != 6 && !work->waitAnim && (info = peopleInfoBiosGetPtr(work->objectID)) &&
        !info->noWalkStart && !work->manualAnim && !gimmickBoxIsGimmickMoving()) {
        f32 speed = work->curRate;
        if (work != g_pMana && (peopleBiosCheckFlag(work, 8) || work->peopleID != 0x64)) {
            f32 dist = PSVECDistance(peopleBiosGetPosPtr(work), &work->destPos);
            peopleViewerGetPlaySpeedRate(work);
            if (!work->isAlwayBlendChara()) {
                f32 limit;
                if (work->running) {
                    limit = 2.0f * END_NEED_DISTANCE;
                } else {
                    limit = END_NEED_DISTANCE;
                }
                if (dist < limit && (!(dist < 0.00001f) || !(dist > -0.00001f))) {
                    if (!work->blend) {
                        GSmodelEnableAnimBlend(work->model);
                        work->blend = 1;
                    }
                } else if (work->animEnded && work->blend) {
                    GSmodelGetAnimIndex(work->model, &index, 0);
                    GSmodelDisableAnimBlend(work->model);
                    work->setAnimIndex(index);
                    work->blend = 0;
                }
            }
        }
        if (work->attachPart >= 0) {
            speed = 0.0f;
        }
        f32 maxSpeed = work->runRate;
        if (speed > maxSpeed) {
            speed = maxSpeed;
        }
        if (speed < 0.0f) {
            speed = 0.0f;
        }
        if (work->blend) {
            _peopleUpdateBlendAnimation(work, speed);
            return;
        }
        _peopleUpdateNoBlendAnimation(work, speed);
    }
}
}

static void _peopleUpdateNoBlendAnimation(tagPeopleWork* work, f32 speed) {
    s32 index, blendIndex;
    f32 count, blendCount, count2, blendCount2;
    _GSmodel* model = peopleBiosGetModelPtr(work);
    if (model) {
        GSmodelGetAnimIndex(model, &index, &blendIndex);
        GSmodelGetFrameCount(model, &count, &blendCount);
        if (!gimmickBoxIsBox(work)) {
            if (index == work->motionTable[3]) {
                goto doit;
            }
            if (index == work->motionTable[4]) {
                return;
            }
        }
    doit : {
        f32 rate1 = 0.0f;
        f32 frame = GSmodelGetAnimFrame(model);
        if (count > 0.0f) {
            rate1 = frame / count;
        }
        f32 rate2 = 0.0f;
        if (blendCount > 0.0f) {
            rate2 = frame / blendCount;
        }
        if (work->moveDist < 0.00001f && work->moveDist > -0.00001f) {
            if (index != work->motionTable[0] || blendIndex != -1) {
                work->setAnimIndex(work->motionTable[0]);
                GSmodelGetFrameCount(model, &count2, &blendCount2);
                rate1 = blendIndex != -1 ? rate1 : rate2;
                work->setAnimFrame(count2 * rate1);
                work->setAnimType(GS_MODEL_ANIM_TYPE_1);
                work->setAnimRate(0.5f, true);
            }
        } else {
            _peopleSetMoveAnimation(work);
        }
    }
    }
}

extern "C" {
bool peopleSpeedSlowDownOff(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    work->slowDown = 0;
    return true;
}

bool peopleSpeedSlowDownOn(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    work->slowDown = 1;
    return true;
}
}

static void _peopleAnimEndCallback(_GSmodel* model, _GSmodelAnimCBData* data) {
    tagPeopleWork* work = (tagPeopleWork*)data->user;
    work->animEnded = 1;
    if (!work->manualAnim) {
        if (work->groupID == 0 && work->peopleID == 0x64 && !peopleBiosCheckFlag(work, 0x8000000C)) {
            if (work->curRate < 0.00001f && work->curRate > -0.00001f) {
                if (data->index != 0x13 && data->index != 0x14 && data->index != 0x15 &&
                    m_hero_idling_time > m_hero_next_special_idling_time) {
                    u32 rnd = HSD_Rand() & 1;
                    s32 next = 0x13;
                    switch (m_before_special_effect) {
                    case 0x13:
                        next = rnd ? 0x14 : 0x15;
                        break;
                    case 0x14:
                        next = rnd ? 0x13 : 0x15;
                        break;
                    case 0x15:
                        next = rnd ? 0x13 : 0x14;
                        break;
                    }
                    work->setAnimIndex(next);
                    m_before_special_effect = next;
                    work->setAnimType(GS_MODEL_ANIM_TYPE_0);
                    work->setAnimFrame(0.0f);
                    work->setAnimRate(0.5f, true);
                    m_hero_next_special_idling_time = 5.0f * HSD_Randf() + 15.0f;
                    return;
                }
            }
            if (data->index == 0x13 || data->index == 0x14 || data->index == 0x15) {
                m_hero_idling_time = 0.0f;
                work->setAnimBlend(work->motionTable[0], work->motionTable[1]);
                work->setAnimFrame(0.0f);
                work->setAnimType(GS_MODEL_ANIM_TYPE_1);
                GSmodelSetBlendFactor(model, 0.0f);
                work->setAnimRate(0.5f, true);
                return;
            }
        }
        if (data->index == 1) {
            GSmodelSetTexAnimIndex(model, 0);
            GSmodelLinkTexAnimToAnim(model, 1);
            return;
        }
        PeopleInfo* info = peopleInfoBiosGetPtr(work->objectID);
        if (info && !info->noWalkStart) {
            s32 index = data->index;
            if (index == work->motionTable[0] && !(work->moveDist < 0.00001f && work->moveDist > -0.00001f) &&
                !work->blend) {
                if (!work->running) {
                    work->setAnimIndex(work->motionTable[3]);
                } else {
                    work->setAnimIndex(work->motionTable[4]);
                }
                work->setAnimType(GS_MODEL_ANIM_TYPE_0);
                work->setAnimFrame(0.0f);
                work->setAnimRate(0.5f, true);
                return;
            }
            if (index == work->motionTable[3]) {
                work->setAnimIndex(work->motionTable[1]);
                work->setAnimType(GS_MODEL_ANIM_TYPE_1);
                work->setAnimFrame(0.0f);
                work->setAnimRate(0.5f, true);
                return;
            }
            if (index == work->motionTable[4]) {
                work->setAnimIndex(work->motionTable[2]);
                work->setAnimType(GS_MODEL_ANIM_TYPE_1);
                work->setAnimFrame(0.0f);
                work->setAnimRate(0.5f, true);
                return;
            }
            if (GSmodelGetAnimType(model) != 1 && (work->followState == 4 || work->followState == 6)) {
                work->followState = 0;
                work->setAnimBlend(work->motionTable[0], work->motionTable[1]);
                work->setAnimFrame(0.0f);
                work->setAnimType(GS_MODEL_ANIM_TYPE_1);
            }
        }
    }
}

static void _peopleExecAnimEndCallBack(tagPeopleWork* work) {
    _GSmodelAnimCBData data;
    s32 index, blendIndex;
    GSmodelGetAnimIndex(work->model, &index, &blendIndex);
    s32 selected = blendIndex;
    data.index = index;
    if (selected != -1) {
        data.index = selected;
    }
    data.user = work;
    _peopleAnimEndCallback(work->model, &data);
}

static void _peopleUpdateBlendAnimation(tagPeopleWork* work, f32 speed) {
    s32 index, blendIndex;
    f32 count, blendCount, count2, blendCount2;
    GSvec pos, rot;
    f32 moveAngle;
    f32 walkRate = work->walkRate;
    f32 runRate = work->runRate;
    f32 first;
    f32 second;
    _GSmodel* model = work->model;
    f32 playRate = peopleViewerGetPlaySpeedRate(work);
    if (!(playRate < 0.00001f) || !(playRate > -0.00001f)) {
        f32 realSpeed = speed / playRate;
        f32 rate1 = 0.0f;
        GSmodelGetAnimIndex(model, &index, &blendIndex);
        GSmodelGetFrameCount(model, &count, &blendCount);
        f32 frame = GSmodelGetAnimFrame(model);
        if (count > 1.0f) {
            rate1 = frame / count;
        }
        first = rate1;
        f32 rate2 = 0.0f;
        if (blendCount > 1.0f) {
            rate2 = frame / blendCount;
        }
        second = rate2;
        if (rate1 > 1.0f) {
            first = 0.0f;
        }
        if (rate2 > 1.0f) {
            second = 0.0f;
        }
        if (work->groupID == 0 && work->peopleID == 0x64) {
            if (realSpeed < 0.00001f && realSpeed > -0.00001f && !peopleBiosCheckFlag(work, 0x8000000C)) {
                if ((u32)(index - 0x13) > 1U) {
                    if (index == 0x15) {
                        return;
                    }
                    m_hero_idling_time += _getLastFrameSec();
                    goto general;
                }
            } else {
                m_hero_idling_time = 0.0f;
                goto general;
            }
        } else {
        general:
            if (g_pHero && g_pMana && work == g_pMana && work->followState != 0) {
                switch (work->followState) {
                case 1:
                    work->setAnimIndex(0x29);
                    work->setAnimType(GS_MODEL_ANIM_TYPE_0);
                    work->setAnimFrame(0.0f);
                    work->setAnimRate(0.5f, true);
                    work->followState = 4;
                    return;
                case 2:
                    work->setAnimIndex(0x2A);
                    work->setAnimType(GS_MODEL_ANIM_TYPE_0);
                    work->setAnimFrame(0.0f);
                    work->setAnimRate(0.5f, true);
                    work->followState = 4;
                    return;
                case 3:
                    work->setAnimIndex(0x2B);
                    work->setAnimType(GS_MODEL_ANIM_TYPE_1);
                    work->setAnimFrame(0.0f);
                    work->setAnimRate(0.5f, true);
                    work->followState = 5;
                    return;
                case 0:                default:
                    work->f17F = 1;
                    return;
                }
            } else {
                work->followState = 0;
                if (work != g_pMana && (peopleBiosCheckFlag(work, 8) || work->peopleID != 0x64)) {
                    f32 limit = END_NEED_DISTANCE;
                    peopleBiosGetPosPtr(work);
                    if (PSVECDistance(&work->destPos, peopleBiosGetPosPtr(work)) < limit) {
                        realSpeed *= peopleGetBlendFactor(0.0f, 0.0f, limit);
                        work->f17F = 1;
                    } else {
                        peopleBiosGetPosPtr(work);
                        f32 dist = PSVECDistance(&work->startPos, peopleBiosGetPosPtr(work));
                        static f32 start_dist_fix = 1.0f;
                        if (dist < limit * start_dist_fix) {
                            realSpeed *= peopleGetBlendFactor(0.0f, 0.0f, 0.0f);
                            work->f17F = 1;
                        }
                    }
                }
                peopleBiosGetPos(work, &pos);
                peopleBiosGetRot(work, &rot);
                peopleBiosGetPosPtr(work);
                PSVECDistance(&work->destPos, peopleBiosGetPosPtr(work));
                moveAngle = atan2(pos.x - work->savedPos.x, pos.z - work->savedPos.z);
                f32 moved = PSVECDistance(&pos, &work->savedPos);
                void* hero = getHeroPtr__4HeroFv();
                u32 followerID = getFollowerResID__4HeroFv(hero);
                if (fabsf(_peopleGetDiffAngle(moveAngle, rot.y)) > 1.5707964f && moved > 0.001f &&
                    work->peopleID == followerID && heroGetFollower() && (!(moved < 0.00001f) || !(moved > -0.00001f))) {
                    if (!GSmodelIsAnimating(model) || index != work->motionTable[0] || blendIndex != 0x2B ||
                        frame > blendCount || frame < 0.0f) {
                        work->setAnimBlend(work->motionTable[0], 0x2B);
                        GSmodelGetFrameCount(model, &count2, &blendCount2);
                        f32 use;
                        if (blendIndex == -1) {
                            use = first;
                        } else {
                            use = second;
                        }
                        work->setAnimFrame(blendCount2 * use);
                        work->setAnimType(GS_MODEL_ANIM_TYPE_1);
                    }
                    GSmodelSetBlendFactor(model, peopleGetBlendFactor(realSpeed, 0.0f, work->f2C));
                    work->setAnimRate(0.5f * playRate, false);
                    return;
                }
                f32 margin;
                if (work->f17F) {
                    margin = 0.0f;
                } else {
                    margin = 0.3f;
                }
                if (!peopleBiosCheckFlag(work, 0x8000000C) && work->peopleID == 0x64) {
                    margin = 0.0f;
                }
                if (realSpeed <= work->walkRate + margin) {
                    if (!GSmodelIsAnimating(model) || index != work->motionTable[0] || blendIndex != work->motionTable[1] ||
                        frame > blendCount || frame < 0.0f) {
                        work->setAnimBlend(work->motionTable[0], work->getWalkMotion());
                        GSmodelGetFrameCount(model, &count2, &blendCount2);
                        f32 use;
                        if (blendIndex == -1) {
                            use = first;
                        } else {
                            use = second;
                        }
                        work->setAnimFrame(blendCount2 * use);
                        work->setAnimType(GS_MODEL_ANIM_TYPE_1);
                    }
                    f32 factor = peopleGetBlendFactor(realSpeed, 0.0f, walkRate);
                    GSmodelSetBlendFactor(model, factor);
                    work->setAnimRate(0.5f * playRate, false);
                    peopleViewerDisplayAnimRate(work, factor);
                    return;
                }
                if (!GSmodelIsAnimating(model) || index != work->motionTable[1] || blendIndex != work->motionTable[2] ||
                    frame > blendCount || frame < 0.0f) {
                    work->setAnimBlend(work->motionTable[1], work->getRunMotion());
                    GSmodelGetFrameCount(model, &count2, &blendCount2);
                    f32 use;
                    if (blendIndex == -1) {
                        use = first;
                    } else {
                        use = second;
                    }
                    work->setAnimFrame(blendCount2 * use);
                    work->setAnimType(GS_MODEL_ANIM_TYPE_1);
                }
                f32 factor = peopleGetBlendFactor(realSpeed, walkRate, runRate);
                GSmodelSetBlendFactor(model, factor);
                f32 half = 0.5f * playRate;
                work->setAnimRate((half * (walkRate * (1.0f - factor) + runRate * factor)) / runRate, false);
                peopleViewerDisplayAnimRate(work, factor);
            }
        }
    } else {
        GSmodelStopAnimation(model);
    }
}

extern "C" {
bool peopleManualAnimation(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    work->manualAnim = 1;
    return true;
}

bool peopleAutoAnimation(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    work->manualAnim = 0;
    return true;
}

bool peopleSetDefaultMotionTable(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    work->motionTable[0] = 3;
    work->motionTable[1] = 5;
    work->motionTable[2] = 8;
    work->motionTable[3] = 4;
    work->motionTable[4] = 7;
    _peopleValidMotionTable(work->model, (_peopleMotionTable*)work->motionTable);
    _peopleSetAutoMotionFrameCount(work);
    return true;
}

bool peopleSetMotionTable(u32 groupID, u32 peopleID, _peopleMotionTable table) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    work->motionTable[0] = table.m[0];
    work->motionTable[1] = table.m[1];
    work->motionTable[2] = table.m[2];
    work->motionTable[3] = table.m[3];
    work->motionTable[4] = table.m[4];
    _peopleValidMotionTable(work->model, (_peopleMotionTable*)work->motionTable);
    _peopleSetAutoMotionFrameCount(work);
    return true;
}
}

static void _peopleValidMotionTable(_GSmodel* model, _peopleMotionTable* table) {
    if (model) {
        if (GSmodelIsNullAnimation(model, table->m[3])) {
            table->m[3] = -1;
        }
        if (GSmodelIsNullAnimation(model, table->m[1])) {
            table->m[1] = -1;
        }
        if (GSmodelIsNullAnimation(model, table->m[4])) {
            table->m[4] = -1;
        }
        if (GSmodelIsNullAnimation(model, table->m[2])) {
            table->m[2] = -1;
        }
    }
}

static bool _peopleSetAutoMotionFrameCount(tagPeopleWork* work) {
    f32 walkLen = 1.0f;
    bool running = false;
    f32 runLen = 1.0f;
    if (work->curRate > 0.3f + work->walkRate) {
        running = true;
    }
    s32 maxIndex = GSmodelGetMaxAnimIndex(work->model);
    PeopleInfo* info = peopleInfoBiosGetPtr(work->objectID);
    if (info) {
        walkLen = peopleInfoBiosGetWalkLength(info);
        runLen = peopleInfoBiosGetRunLength(info);
    }
    if (maxIndex >= work->motionTable[3] && maxIndex >= work->motionTable[1] && maxIndex >= work->motionTable[4] &&
        maxIndex >= work->motionTable[2] && (info == 0 || !info->noWalkStart)) {
        if (work->motionTable[3] >= 0) {
            work->idleFrames = GSmodelGetAnimFrameCount(work->model, work->motionTable[3]);
        }
        if (work->motionTable[1] >= 0) {
            work->walkFrames = GSmodelGetAnimFrameCount(work->model, work->motionTable[1]);
        }
        if (work->motionTable[4] >= 0) {
            work->f38 = GSmodelGetAnimFrameCount(work->model, work->motionTable[4]);
        }
        if (work->motionTable[2] >= 0) {
            work->runFrames = GSmodelGetAnimFrameCount(work->model, work->motionTable[2]);
        }
        if (!info) {
            return false;
        }
        f32 frames = work->walkFrames > 0.0f ? work->walkFrames : 30.0f;
        work->walkRate = walkLen / frames;
        f32 frames2 = work->runFrames > 0.0f ? work->runFrames : 17.0f;
        work->runRate = runLen / frames2;
        if (GSmodelIsNullAnimation(work->model, work->motionTable[1])) {
            work->walkRate = 0.35f;
        }
        if (GSmodelIsNullAnimation(work->model, work->motionTable[2])) {
            work->runRate = 1.53f;
        }
        if (!running) {
            work->curRate = work->walkRate;
        } else {
            work->curRate = work->runRate;
        }
        return true;
    }
    if (info) {
        work->walkRate = walkLen / 30.0f;
        work->runRate = runLen / 17.0f;
    } else {
        work->walkRate = 0.35f;
        work->runRate = 1.53f;
    }
    work->curRate = work->walkRate;
    return false;
}

extern "C" {
void peopleUnsetWaitAnimation(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    work->waitAnim = 0;
}

void peopleSetWaitAnimation(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    _peopleSetMotionMain(groupID, peopleID, work->motionTable[0], false, 1);
    work->waitAnim = 1;
}

f32 peopleGetBlendFactor(f32 value, f32 lo, f32 hi) {
    f32 range = lo - hi;
    if (range < 0.00001f && range > -0.00001f) {
        return 0.0f;
    }
    f32 t = (value - lo) / (hi - lo);
    if (t > 1.0f) {
        return 1.0f;
    }
    if (t < 0.0f) {
        return 0.0f;
    }
    return t;
}

void peopleWalkToXYZ(u32 groupID, u32 peopleID, u8 keepRot, f32 x, f32 y, f32 z) {
    GSvec dest;
    dest.x = x;
    dest.y = y;
    dest.z = z;
    peopleWalkTo(groupID, peopleID, keepRot, &dest);
}

void peopleSetRotXYZ(u32 groupID, u32 peopleID, f32 x, f32 y, f32 z) {
    GSvec rot;
    rot.x = 0.017453292f * x;
    rot.y = 0.017453292f * y;
    rot.z = 0.017453292f * z;
    peopleSetRot(groupID, peopleID, &rot);
}

void peopleSetPosXYZ(u32 groupID, u32 peopleID, f32 x, f32 y, f32 z) {
    GSvec pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    peopleSetPos(groupID, peopleID, &pos);
}

bool peopleGazeCheck(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, f32 dist, f32 angle);

bool peopleGazeHeroCheck(u32 groupID, u32 peopleID) {
    return peopleGazeCheck(groupID, peopleID, 0, 0x64, 3.0f, 30.0f);
}

bool peopleGazeCheck(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, f32 dist, f32 angle) {
    GSvec targetPos, viewerPos, diff, rot;
    f32 ballSize = 4.0f;
    tagPeopleWork* dc_peopleGet = peopleGet(targetGroupID, targetPeopleID);
    if (!dc_peopleGet) {
        return false;
    }
    GSvec* p = peopleBiosGetPosPtr(dc_peopleGet);
    targetPos.x = p->x;
    targetPos.y = p->y;
    targetPos.z = p->z;
    tagPeopleWork* viewer = peopleGet(groupID, peopleID);
    if (!viewer) {
        return false;
    }
    GSvec* q = peopleBiosGetPosPtr(viewer);
    viewerPos.x = q->x;
    viewerPos.y = q->y;
    viewerPos.z = q->z;
    PSVECSubtract(&viewerPos, &targetPos, &diff);
    if (PSVECMag(&diff) > 10.0f * dist) {
        return false;
    }
    peopleBiosGetRot(viewer, &rot);
    if (fabsf(peopleVecCalcRotY(&viewerPos, &targetPos, rot.y)) > 0.5f * (0.017453292f * angle)) {
        return false;
    }
    PeopleInfo* dc_peopleInfoBiosGetPtr = peopleInfoBiosGetPtr(viewer->objectID);
    if (dc_peopleInfoBiosGetPtr) {
        ballSize = peopleInfoBiosGetColBallSize(dc_peopleInfoBiosGetPtr);
    }
    if (GScolsys2HitNpcCollision(&viewerPos, &targetPos, 0, ballSize)) {
        return false;
    }
    return true;
}

void peopleRotateStop(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        work->rotating = 0;
        work->angle = peopleBiosGetRotPtr(work)->y;
    }
}

void peopleRotateToTarget(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, f32 rate) {
    GSvec diff, targetPos, rot;
    f32 angle;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    _GSmodel* target;
    if (work && (target = (_GSmodel*)GSresGetResource(targetGroupID, targetPeopleID))) {
        GSvec* tp = GSmodelGetPositionPtr(target);
        targetPos.x = tp->x;
        targetPos.y = tp->y;
        targetPos.z = tp->z;
        PSVECSubtract(&targetPos, peopleBiosGetPosPtr(work), &diff);
        diff.y = 0.0f;
        if (!(PSVECMag(&diff) < 0.00001f) || !(PSVECMag(&diff) > -0.00001f)) {
            angle = atan2f(diff.x, diff.z);
        } else {
            peopleBiosGetRot(work, &rot);
            angle = rot.y;
        }
        if (rate < 0.00001f && rate > -0.00001f) {
            peopleSetRotXYZ(groupID, peopleID, 0.0f, 57.29578f * angle, 0.0f);
            return;
        }
        peopleRotateToAngle(groupID, peopleID, angle, rate);
    }
}

void peopleRotateToXYZ(u32 groupID, u32 peopleID, f32 x, f32 y, f32 z, f32 rate) {
    GSvec diff, target, rot;
    f32 angle;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        target.x = x;
        target.y = y;
        target.z = z;
        PSVECSubtract(&target, peopleBiosGetPosPtr(work), &diff);
        diff.y = 0.0f;
        if (!(PSVECMag(&diff) < 0.00001f) || !(PSVECMag(&diff) > -0.00001f)) {
            angle = atan2f(diff.x, diff.z);
        } else {
            peopleBiosGetRot(work, &rot);
            angle = rot.y;
        }
        peopleRotateToAngle(groupID, peopleID, angle, rate);
    }
}

void peopleRotateToAngle(u32 groupID, u32 peopleID, f32 angle, f32 rate) {
    GSvec rot;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        f32 adjusted = adjustPIPI(angle);
        work->rotating = 1;
        work->angle = adjusted;
        peopleBiosGetRot(work, &rot);
        work->startAngle = rot.y;
        work->angleSpeed = 0.0f;
        work->rotRate = rate;
    }
}

bool peopleMoveAlongAngle(u32 groupID, u32 peopleID, f32 dist, f32 angle) {
    GSvec pos, step, probe, hit;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if ((peopleID == 0x65 || peopleID == 0x68 || peopleID == 0x69) && work->attachPart > 0) {
        work->curRate = 0.0f;
        work->moveDist = 0.0f;
        work->followState = 0;
        return true;
    }
    peopleBiosGetPos(work, &pos);
    static f32 d0_fix = 1.0f;
    volatile u8 vsync = GSgfxVideoGetVsyncRate();
    f32 time = (f32)timeGetLastFrameTime();
    f32 playRate = peopleViewerGetPlaySpeedRate(work);
    work->moveDist = dist;
    f32 move = playRate * (dist * ((30.0f * time) / (f32)vsync));
    if (!peopleInfoBiosGetPtr(work->objectID)) {
        return false;
    }
    if (work->isWalkStartMotion()) {
        return true;
    }
    if (groupID == 0 && peopleID == 0x64 && !m_hero_move) {
        move = 0.0f;
    }
    work->f17F = 0;
    if (_peopleBreakWithWalkList(work) && (peopleBiosCheckFlag(work, 8) || work->peopleID != 0x64)) {
        peopleBiosGetPosPtr(work);
        f32 left = _distanceXZ(&work->destPos, peopleBiosGetPosPtr(work));
        bool vsync2 = GSgfxVideoGetVsyncRate();
        f32 minMove = peopleViewerGetPlaySpeedRate(work) * (0.001f * (f32)((30.0f * (f32)((f32)timeGetLastFrameTime())) / (f32)vsync2));
        if (work->slowDown && work->followState == 0) {
            f32 limit;
            if (work->running) {
                limit = 2.0f * END_NEED_DISTANCE;
            } else {
                limit = END_NEED_DISTANCE;
            }
            if (left < limit) {
                move *= peopleGetBlendFactor(left, 0.0f, limit);
                if (move < minMove) {
                    move = minMove;
                }
                work->f17F = 1;
            }
        }
        if (left < move) {
            pos.x = work->destPos.x;
            pos.y = work->destPos.y;
            pos.z = work->destPos.z;
            peopleBiosSetPos(work, &pos);
            move = 0.0f;
        }
    }
    if (move > 0.0f) {
        probe.z = pos.z;
        step.x = pos.x;
        step.y = pos.y;
        step.z = pos.z;
        probe.x = pos.x;
        probe.y = pos.y;
        step.x = move * sin(angle) + pos.x;
        step.z += move * cos(angle);
        step.y = GScolsys2HumanGetWalkHeight(&step);
        f32 sq = move * move;
        f32 dy = pos.y - step.y;
        f32 slope = sq / sqrtf(sq + dy * dy);
        probe.x += slope * sin(angle);
        probe.z += slope * cos(angle);
        probe.y = GScolsys2HumanGetWalkHeight(&probe);
        if (slope > move) {
            slope = move;
        }
        if (!gimmickBoxOnBox(work, peopleBiosGetPosPtr(work), &step)) {
            pos.x += slope * sin(angle);
            pos.z += slope * cos(angle);
            pos.y = GScolsys2HumanGetWalkHeight(&pos);
        } else {
            pos.x += move * sin(angle);
            pos.z += move * cos(angle);
            pos.y = GScolsys2HumanGetWalkHeight(&pos);
        }
    }
    return _peopleAdjustPosition(work, &pos, &work->savedPos);
}

bool peopleMoveForward(u32 groupID, u32 peopleID, f32 dist) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work || !work->model) {
        return true;
    }
    return peopleMoveAlongAngle(groupID, peopleID, dist, work->angle);
}
}

extern "C" {
bool peopleCheckNeckRotate(u32 groupID, u32 peopleID, u8 wait) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    GSthreadSwitch();
    while (true) {
        f32 dx = work->neckCur.x - work->neckGoal.x;
        f32 dy = work->neckCur.y - work->neckGoal.y;
        if (dx < 0.00001f && dx > -0.00001f && dy < 0.00001f && dy > -0.00001f) {
            return false;
        }
        if (wait) {
            GSthreadSwitch();
            continue;
        }
        return true;
    }
}

void peopleRemoveNeckTarget(u32 groupID, u32 peopleID, f32 speed) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        work->neckMode = 0;
        work->neckGoal.x = 0.0f;
        work->neckGoal.y = 0.0f;
        work->neckGoal.z = 0.0f;
        work->neckF1 = 1;
        work->neckF3 = 0;
        if (speed > 0.0f) {
            f32 max = speed * 0.07853982f;
            f32 half = 0.5f;
            work->neckSpeedMax = max;
            work->neckSpeed = max * half;
            work->neckF2 = 0;
            return;
        }
        work->neckF2 = 1;
        work->neckSpeedMax = 3.1415927f;
        work->neckSpeed = 3.1415927f;
        work->neckCur.x = 0.0f;
        work->neckCur.y = 0.0f;
        work->neckCur.z = 0.0f;
    }
}

void peopleMoveNeckAngleWorld(u32 groupID, u32 peopleID, f32 yaw, f32 pitch, f32 speed) {
    PeopleNeckInfo info;
    tagPeopleWork* work = peopleGet((u16)groupID, peopleID);
    if (work && _getNeck(work, &info)) {
        GSvec* rot = peopleBiosGetRotPtr(work);
        f32 pitchRad = 0.017453292f;
        pitchRad *= pitch;
        f32 diff = adjustPIPI(0.017453292f * yaw - rot->y);
        if (diff < info.left) {
            diff = info.left;
        }
        if (diff > info.right) {
            diff = info.right;
        }
        f32 world = adjust2PI(diff + rot->y);
        f32 s = sin(world);
        f32 c = cos(world);
        f32 sp = sin(pitchRad);
        work->neckTarget.y = -(1000000.0f * sp - info.pos.y);
        work->neckTarget.x = 1000000.0f * s + info.pos.x;
        work->neckTarget.z = 1000000.0f * c + info.pos.z;
        work->neckMode = 3;
        _peopleGetNearAngle(pitchRad - info.rot.x);
        _peopleGetNearAngle(world - info.rot.y);
        work->neckF1 = 1;
        work->neckF3 = 0;
        work->neckF2 = 0;
        if (speed > 0.0f) {
            f32 max = speed * 0.07853982f;
            f32 half = 0.5f;
            work->neckSpeedMax = max;
            work->neckSpeed = max * half;
        } else {
            work->neckSpeedMax = 3.1415927f;
            work->neckSpeed = 3.1415927f;
        }
        _peopleUpdateNeck(work, 75.0f);
    }
}

void peopleMoveNeckAngle(u32 groupID, u32 peopleID, f32 yaw, f32 pitch, f32 speed) {
    f32 c;
    PeopleNeckInfo info;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work && _getNeck(work, &info)) {
        f32 s;
        f32 yawRad = 0.017453292f * yaw;
        f32 pitchRad;
        pitchRad = 0.017453292f * pitch;
        s = sin(yawRad);
        c = cos(yawRad);
        f32 sp = sin(pitchRad);
        work->neckTarget.y = -(1000000.0f * sp - info.pos.y);
        work->neckTarget.z = 1000000.0f * c + info.pos.z;
        work->neckMode = 3;
        _peopleGetNearAngle(pitchRad);
        work->neckTarget.x = 1000000.0f * s + info.pos.x;
        _peopleGetNearAngle(yawRad);
        work->neckF1 = 1;
        work->neckF3 = 0;
        work->neckF2 = 0;
        if (speed > 0.0f) {
            f32 max = speed * 0.07853982f;
            f32 half = 0.5f;
            work->neckSpeedMax = max;
            work->neckSpeed = max * half;
        } else {
            work->neckSpeedMax = 3.1415927f;
            work->neckSpeed = 3.1415927f;
        }
        _peopleUpdateNeck(work, 75.0f);
    }
}

void peopleMoveNeckTargetXYZ(u32 groupID, u32 peopleID, s32 x, s32 y, s32 z, f32 speed) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        work->neckTarget.x = (f32)x;
        work->neckTarget.y = (f32)y;
        work->neckTarget.z = (f32)z;
        work->neckMode = 2;
        work->neckF1 = 1;
        work->neckF3 = 0;
        work->neckF2 = 0;
        if (speed > 0.0f) {
            f32 max = speed * 0.07853982f;
            f32 half = 0.5f;
            work->neckSpeedMax = max;
            work->neckSpeed = max * half;
            return;
        }
        work->neckSpeedMax = 3.1415927f;
        work->neckSpeed = 3.1415927f;
    }
}

void peopleMoveNeckTargetHero(u32 groupID, u32 peopleID, f32 speed) {
    peopleMoveNeckTarget(groupID, peopleID, 0, 0x64, speed);
}

void fn_8029CD20(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, f32 speed) {
    PeopleNeckInfo info;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    tagPeopleWork* target = peopleGet(targetGroupID, targetPeopleID);
    if (work == 0 || target == 0) {
        return;
    }
    if (_getNeck(target, &info)) {
        work->neckTarget.x = info.pos.x;
        work->neckTarget.y = info.pos.y;
        work->neckTarget.z = info.pos.z;
        work->neckMode = 2;
        work->neckF1 = 1;
        work->neckF3 = 0;
        work->neckF2 = 0;
        if (speed > 0.0f) {
            f32 max = speed * 0.07853982f;
            work->neckSpeedMax = max;
            f32 kc737 = 0.5f;
            work->neckSpeed = max * kc737;
            return;
        }
        work->neckSpeedMax = 3.1415927f;
        work->neckSpeed = 3.1415927f;
    }
}

void peopleMoveNeckTarget(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, f32 speed) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        work->neckMode = 1;
        work->neckGroupID = targetGroupID;
        work->neckPeopleID = targetPeopleID;
        work->neckF1 = 1;
        work->neckF3 = 0;
        work->neckF2 = 0;
        if (speed > 0.0f) {
            f32 max = speed * 0.07853982f;
            f32 half = 0.5f;
            work->neckSpeedMax = max;
            work->neckSpeed = max * half;
            return;
        }
        work->neckSpeedMax = 3.1415927f;
        work->neckSpeed = 3.1415927f;
    }
}

void peopleSetNeckTargetXYZ(u32 groupID, u32 peopleID, s32 x, s32 y, s32 z) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        work->neckTarget.x = (f32)x;
        work->neckTarget.y = (f32)y;
        work->neckTarget.z = (f32)z;
        work->neckMode = 2;
        work->neckSpeedMax = 3.1415927f;
        work->neckSpeed = 3.1415927f;
        work->neckF3 = 0;
        work->neckF2 = 1;
    }
}

void peopleSetNeckTargetHero(u32 groupID, u32 peopleID) {
    peopleSetNeckTarget(groupID, peopleID, 0, 0x64);
}

void peopleSetNeckTarget(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        work->neckMode = 1;
        work->neckGroupID = targetGroupID;
        work->neckPeopleID = targetPeopleID;
        work->neckSpeedMax = 3.1415927f;
        work->neckSpeed = 3.1415927f;
        work->neckF3 = 0;
        work->neckF2 = 1;
    }
}

bool peopleSetNeckLimitHold(u32 groupID, u32 peopleID, u8 hold) {
    bool old;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return 0;
    }
    old = peopleBiosCheckFlag(work, 2);
    if (hold) {
        peopleBiosSetFlagOn(work, 2);
    } else {
        peopleBiosSetFlagOff(work, 2);
    }
    return old;
}

bool peopleMoveCheck(u32 groupID, u32 peopleID, u8 wait) {
    s32 index;
    s32 count = 0;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    peopleBiosSetFlagOn(work, 8);
    while (true) {
        GSmodelGetAnimIndex(work->model, &index, 0);
        if (index == 0) {
            count++;
            if (count > 0xB4) {
                work->moveType = 0;
                return false;
            }
        }
        if (work->moveType == 0 && !work->rotating) {
            return false;
        }
        if (!peopleBiosCheckFlag(work, 8)) {
            return false;
        }
        if (!_peopleIsMoving(work) && !work->rotating) {
            return false;
        }
        if (wait) {
            GSthreadSwitch();
            continue;
        }
        return true;
    }
}

bool peopleRotateCheck(u32 groupID, u32 peopleID, u8 wait) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    while (true) {
        if (!work->rotating) {
            return false;
        }
        if (wait) {
            GSthreadSwitch();
            continue;
        }
        return true;
    }
}

void peopleRotateTo(u32 groupID, u32 peopleID, f32 degrees) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        f32 rate = 1.0f;
        if (work->speed > 0.1f + work->walkRate) {
            rate = 2.0f;
        }
        peopleBiosSetFlagOn(work, 8);
        peopleRotateToAngle(groupID, peopleID, 0.017453292f * degrees, rate);
    }
}

void peopleWalkToTarget(u32 groupID, u32 peopleID, u32 targetGroupID, u32 targetPeopleID, u8 keepRot, f32 dist) {
    GSvec diff, to, from;
    f32 t;
    f32 scaled = 10.0f * dist;
    peopleGetPos(groupID, peopleID, &from);
    peopleGetPos(targetGroupID, targetPeopleID, &to);
    PSVECSubtract(&from, &to, &diff);
    f32 len = PSVECMag(&diff);
    if (len < 0.00001f && len > -0.00001f) {
        t = 1.0f;
    } else {
        t = scaled / len;
    }
    if (t >= 1.0f) {
        tagPeopleWork* work = peopleGet(groupID, peopleID);
        if (work) {
            work->moveType = 0;
        }
    } else {
        PSVECScale(&diff, &diff, t);
        PSVECAdd(&to, &diff, &to);
        peopleWalkTo(groupID, peopleID, keepRot, &to);
    }
}

void peopleWalkTo(u32 groupID, u32 peopleID, u8 keepRot, GSvec* dest) {
    GSvec delta, rot;
    f32 angle;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        work->moveType = 1;
        work->destPos.x = dest->x;
        work->destPos.y = dest->y;
        work->destPos.z = dest->z;
        PSVECSubtract(&work->destPos, peopleBiosGetPosPtr(work), &delta);
        delta.y = 0.0f;
        if (!(PSVECMag(&delta) < 0.00001f) || !(PSVECMag(&delta) > -0.00001f)) {
            angle = atan2f(delta.x, delta.z);
        } else {
            peopleBiosGetRot(work, &rot);
            angle = rot.y;
        }
        work->destPos.y = GScolsys2HumanGetWalkHeight(&work->destPos);
        _peopleSetMoveAnimation(work);
        f32 rate = 1.0f;
        if (work->speed > 0.1f + work->walkRate) {
            rate = 2.0f;
        }
        peopleRotateToAngle(groupID, peopleID, angle, rate);
        if (!keepRot) {
            work->rotating = 0;
        }
        peopleBiosGetPos(work, &work->startPos);
    }
}

void _peopleSetMoveAnimation(tagPeopleWork* work) {
    s32 index, blendIndex;
    s32 loop = 0;
    if (work) {
        if (work->model != 0) {
            return;
        }
        if (!work->manualAnim && (work->moveType != 4 || work->mode != 0) && !work->isAlwayBlendChara()) {
            GSmodelGetAnimIndex(work->model, &index, &blendIndex);
            if (!work->running) {
                u32 walk = work->motionTable[1];
                if (index != walk || blendIndex != -1) {
                    s32 motion = work->motionTable[3];
                    if (motion == -1) {
                        motion = walk;
                        loop = 1;
                    }
                    peopleSetMotion(work->groupID, work->peopleID, motion, 0, loop);
                }
            } else {
                s32 run = work->motionTable[2];
                if (index != run || blendIndex != -1) {
                    s32 motion = work->motionTable[4];
                    if (motion == -1) {
                        motion = run;
                        loop = 1;
                    }
                    peopleSetMotion(work->groupID, work->peopleID, motion, 0, loop);
                }
            }
        }
    }
}

bool peopleWaitSyncMotionBlend(u32 groupID, u32 peopleID, u8 wait) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    _GSmodel* model = peopleBiosGetModelPtr(work);
    if (!model) {
        return false;
    }
    while (true) {
        if (work->blendT == 1.0f) {
            return false;
        }
        if (wait) {
            if (model->blendMode == 1) {
                return false;
            }
            GSthreadSwitch();
            continue;
        }
        return true;
    }
}

bool peopleWaitSyncMotion(u32 groupID, u32 peopleID, u8 wait) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    GSlogWrite("[%s] people[%d,%d]\n", __FUNCTION__, groupID, peopleID);
    while (true) {
        if (work->isAnimLast()) {
            GSlogWrite("anm endl people[%d,%d]  %08xh\n", groupID, peopleID, work->flags);
        } else if (wait) {
            GSthreadSwitch();
            continue;
        }
        return true;
    }
}

void peopleStopMotion(u32 groupID, u32 peopleID) {
    _GSmodel* model;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work && (model = peopleBiosGetModelPtr(work))) {
        GSmodelStopAnimation(model);
    }
}

void peopleSetMotionForce(u32 groupID, u32 peopleID, s32 motion, s32 frame, bool loop) {
    if (motion >= 0) {
        _GSmodel* model;
        tagPeopleWork* work = peopleGet(groupID, peopleID);
        if (work && (model = peopleBiosGetModelPtr(work))) {
            _peopleSetMotionSub(work, model, motion, frame, loop);
        }
    }
}

bool peopleSetAnimBlend(u32 groupID, u32 peopleID, s32 from, s32 to, u32 frames) {
    f32 count;
    _GSmodel* model;
    if (from < 0 || to < 0) {
        return false;
    }
    if (frames < 1) {
        return false;
    }
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    model = peopleBiosGetModelPtr(work);
    if (!model) {
        return false;
    }
    work->motion = to;
    f32 step = 1.0f / (f32)frames;
    work->blendStep = step;
    work->blendT = 0.0f;
    GSmodelEnableAnimBlend(work->model);
    work->blend = 1;
    work->setAnimBlend(from, to);
    work->setAnimFrame(0.0f);
    GSmodelSetAnimRate(model, 0.0f);
    GSmodelSetBlendFactor(model, work->blendT);
    work->setAnimType(GS_MODEL_ANIM_TYPE_0);
    GSmodelGetFrameCount(model, &count, 0);
    GSmodelSetBlendAnimFrameForce(model, count - 1.5f, 0.0f);
    return true;
}

bool _peopleSetMotionMain(u32 groupID, u32 peopleID, s32 motion, s32 frame, bool loop) {
    s32 index, blendIndex;
    _GSmodel* model;
    bool changed = false;
    tagPeopleWork* work;
    if (motion < 0) {
        return false;
    }
    work = peopleGet(groupID, peopleID);
    if (!work) {
        return false;
    }
    model = peopleBiosGetModelPtr(work);
    if (!model) {
        return false;
    }
    if (GSmodelHasAnimationEnded(model)) {
        changed = true;
    } else if (!GSmodelIsAnimating(model)) {
        changed = true;
    } else {
        GSmodelGetAnimIndex(model, &index, &blendIndex);
        if (index != motion || blendIndex != -1) {
            changed = true;
        }
    }
    if (changed) {
        _peopleSetMotionSub(work, model, motion, frame, loop);
    }
    if (loop) {
        work->setAnimType(GS_MODEL_ANIM_TYPE_1);
    } else {
        work->setAnimType(GS_MODEL_ANIM_TYPE_0);
    }
    return changed;
}

s32 peopleSetMotion(u32 groupID, u32 peopleID, s32 motion, s32 frame, bool loop) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return 0;
    }
    s32 rf_t = work->manualAnim;
    u8 manual = rf_t;
    bool changed = _peopleSetMotionMain(groupID, peopleID, motion, frame, loop);
    return changed & manual;
}
}

static void _peopleSetMotionSub(tagPeopleWork* work, _GSmodel* model, s32 motion, s32 frame, bool loop) {
    work->motion = motion;
    work->blendStep = 0.0f;
    work->setAnimIndex(motion);
    work->setAnimFrame((f32)frame);
    work->setAnimRate(0.5f, true);
    GSmodelSetTexAnimIndex(model, motion);
    GSmodelSetTexAnimFrame(model, (f32)frame);
    GSmodelSetTexAnimRate(model, 0.5f * peopleViewerGetPlaySpeedRate(work));
    if (loop) {
        work->setAnimType(GS_MODEL_ANIM_TYPE_1);
    } else {
        work->setAnimType(GS_MODEL_ANIM_TYPE_0);
    }
    work->flags |= 0x4000;
}

extern "C" {
void peopleGetPartsPos(u32 groupID, u32 peopleID, s32 part, GSvec* out);

void peopleGetNeckPos(u32 groupID, u32 peopleID, GSvec* out) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    PeopleInfo* info;
    if (work && (info = peopleInfoBiosGetPtr(work->objectID))) {
        s8 part = peopleInfoBiosGetNeckIndex(info);
        peopleGetPartsPos(groupID, peopleID, part, out);
        out->y = peopleBiosGetPosPtr(work)->y;
    }
}

void peopleGetPartsPos(u32 groupID, u32 peopleID, s32 part, GSvec* out) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        if (part >= 0) {
            GSpart* p = GSmodelGetPart(work->model, part);
            if (p) {
                GSpartGetTransform(p, out, 0, 0);
                GSpartFree(p);
            }
        } else {
            GSvec* pos = peopleBiosGetPosPtr(work);
            out->x = pos->x;
            out->y = pos->y;
            out->z = pos->z;
        }
    }
}

f32 peopleGetYDegreeRotation(u32 groupID, u32 peopleID) {
    GSvec rot;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (!work) {
        return 0.0f;
    }
    peopleBiosGetRot(work, &rot);
    return 57.29578f * adjustPIPI(rot.y);
}

void peopleGetRot(u32 groupID, u32 peopleID, GSvec* out) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        peopleBiosGetRot(work, out);
    }
}

void peopleGetPos(u32 groupID, u32 peopleID, GSvec* out) {
    tagPeopleWork* work;
    if (out && (work = peopleGet(groupID, peopleID))) {
        peopleBiosGetPos(work, out);
    }
}

void peopleSetRot(u32 groupID, u32 peopleID, GSvec* rot) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        rot->x = fmod(6.2831855f + rot->x, 6.2831854820251465);
        rot->y = fmod(6.2831855f + rot->y, 6.2831854820251465);
        rot->z = fmod(6.2831855f + rot->z, 6.2831854820251465);
        peopleBiosSetRot(work, rot);
        work->angle = rot->y;
    }
}

void peopleSetPos(u32 groupID, u32 peopleID, GSvec* pos) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        peopleBiosSetPos(work, pos);
        peopleBiosSetPrevPos(work, pos);
        work->basePos.x = pos->x;
        work->basePos.y = pos->y;
        work->basePos.z = pos->z;
    }
}

void peopleSetDisp(u32 groupID, u32 peopleID, u8 disp) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        peopleBiosSetDispFlag(work, disp);
        peopleSetCollision(groupID, peopleID, disp);
    }
}

bool peopleCheckFlag(u32 groupID, u32 peopleID, u32 flags) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work == 0) {
        return 0;
    }
    return peopleBiosCheckFlag(work, flags);
}

u32 peopleGetFlags(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    return work == 0 ? 0 : work->flags;
}

void peopleSetFlagOff(u32 groupID, u32 peopleID, u32 flags) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        peopleBiosSetFlagOff(work, flags);
    }
}

void peopleSetFlagOn(u32 groupID, u32 peopleID, u32 flags) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        peopleBiosSetFlagOn(work, flags);
    }
}

void peopleSetFlags(u32 groupID, u32 peopleID, u32 flags) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        peopleBiosSetFlags(work, flags);
    }
}

void peopleSetCollision(u32 groupID, u32 peopleID, u8 enable) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        if (!work->display) {
            enable = 0;
        }
        peopleBiosSetCollision(work, enable);
    }
}

void peopleAddCollision(u32 groupID, u32 peopleID) {
    HumanCollInfo coll;
    s32 humanID;
    PeopleInfo* info;
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work && (info = peopleInfoBiosGetPtr(work->objectID)) && work->humanID < 0) {
        switch (peopleInfoBiosGetColType(info)) {
        case 1:
            coll.groupID = groupID;
            coll.peopleID = peopleID;
            coll.size = peopleInfoBiosGetColBallSize(info);
            coll.height = 12.0f;
            if (GScolsys2HumanAddCurrentFloor(&humanID, &coll) == 0) {
                work->humanID = humanID;
                return;
            }
            work->humanID = -1;
            return;
        case 2:
            coll.groupID = groupID;
            coll.peopleID = peopleID;
            coll.size = peopleInfoBiosGetColBallSize(info);
            coll.height = gimmickBoxGetBoxHeight();
            if (GScolsys2HumanAddCurrentFloor(&humanID, &coll) == 0) {
                work->humanID = humanID;
                return;
            }
            work->humanID = -1;
            break;
        }
    }
}

bool peopleInsideCheck(GSvec* a, GSvec* b, GSvec* point, f32 margin) {
    GSvec mid, local;
    GSquat quat;
    PSVECAdd(a, b, &mid);
    PSVECScale(&mid, &mid, 0.5f);
    f32 rotY = peopleVecCalcRotY(a, b, 0.0f);
    C_QUATRotAxisRad(&quat, &yAxisVector, rotY);
    PSVECSubtract(point, &mid, point);
    GSvecTransformQuat(&local, &quat, point);
    f32 half = PSVECDistance(&mid, b);
    if (margin >= fabsf(local.x)) {
        if (half >= fabsf(local.z)) {
            return true;
        }
    }
    return false;
}

u8 peopleCheckTresure(u32 groupID, u32 peopleID) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    return work == 0 ? (u8)0 : (u8)((work->peopleID & 0x7FFF0000) == 0x7FFF0000);
}

tagPeopleWork* peopleSearchID(u32 searchID) {
    for (s32 i = 0; i < peopleBiosGetMaxNum(); i++) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(i);
        if (work->used && work->searchID == searchID) {
            return work;
        }
    }
    return 0;
}

u32 peopleGetHumanID(u32 groupID, u32 peopleID) {
    for (s32 i = 0; i < peopleBiosGetMaxNum(); i++) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(i);
        if (work->used && work->groupID == groupID && work->peopleID == peopleID) {
            return work->searchID;
        }
    }
    for (s32 i = 0; i < peopleBiosGetMaxNum(); i++) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(i);
        if (work->used && work->peopleID == peopleID) {
            return work->searchID;
        }
    }
    return 0;
}

void peopleAllBlockMoveScript() {
    for (s32 i = 0; i < peopleBiosGetMaxNum(); i++) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(i);
        if (work->used) {
            _peopleBlockMoveScript(work);
        }
    }
}

void peopleAllClose(bool freeWalkList) {
    for (s32 i = 0; i < peopleBiosGetMaxNum(); i++) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(i);
        if (work->used) {
            _peopleCloseSub(work, freeWalkList, false);
        }
    }
}

void peopleClose(u32 groupID, u32 peopleID, bool freeRes) {
    tagPeopleWork* work = peopleGet(groupID, peopleID);
    if (work) {
        _peopleCloseSub(work, true, freeRes);
    }
}
}

static void _peopleCloseSub(tagPeopleWork* work, bool freeWalkList, bool freeRes) {
    if (work->display) {
        peopleSetDisp(work->groupID, work->peopleID, false);
    }
    if (freeWalkList) {
        peopleFreeWalkList(work->groupID, work->peopleID);
    }
    GSresFreeResourceAllGroup(work->peopleID);
    if (work->model) {
        GSmodelFree(work->model);
        work->model = 0;
        if (freeRes && peopleBiosGetUseObjIDSize(work->objectID) == 1) {
            GSresFreeResource(work->groupID, work->objectID);
            floorFreeResource(0x9A, work->objectID);
        }
    }
    peopleBiosFreeWork(work);
    for (s32 i = 0; i < peopleBiosGetMaxNum(); i++) {
        tagPeopleWork* other = peopleBiosGetWorkPtr(i);
        if (other->used && other->neckGroupID == work->groupID && other->neckPeopleID == work->peopleID) {
            other->neckMode = 0;
        }
    }
}

extern "C" {
bool peopleReadObject(u32 groupID, u32 peopleID, u32 objectID) {
    GSvec pos, rot;
    _GSmodel* model;
    u8 display;
    tagPeopleWork* work;
    u32 oldObject;
    u32 humanID = peopleGetHumanID(groupID, peopleID);
    if (!humanID) {
        return false;
    }
    work = peopleSearchID(humanID);
    if (!work) {
        return false;
    }
    if (objectID == work->objectID) {
        return true;
    }
    display = work->display;
    model = peopleBiosGetModelPtr(work);
    oldObject = work->objectID;
    if (!floorReadResourceID(0x9A, objectID)) {
        return false;
    }
    if (model) {
        GSmodelSetVisibility(model, 0);
        GSmodelGetPosition(model, &pos);
        GSmodelGetRotation(model, &rot);
    }
    if (!peopleChangeModel(work, groupID, peopleID, objectID)) {
        work->objectID = 0;
        return false;
    }
    work->objectID = objectID;
    _GSmodel* newModel = peopleBiosGetModelPtr(work);
    if (newModel) {
        GSmodelSetVisibility(newModel, display);
        GSmodelSetPosition(newModel, &pos);
        GSmodelSetRotation(newModel, &rot);
    }
    if (work->ownsRes) {
        floorFreeResource(0x9A, oldObject);
    }
    work->ownsRes = 1;
    if (!peopleSetInfo(work, groupID, peopleID, objectID)) {
        return false;
    }
    peopleSetDisp(groupID, peopleID, display);
    return true;
}

void peopleChangeFollower(u32 objectID) {
    m_change_people_objID = objectID;
    if (GSthreadGetCurrentThread() == 0) {
        floorCreateThread(0x20, 0, 1, _peopleLoadThread);
        return;
    }
    _peopleLoadThread();
}

void peopleSetFollowerPtr(tagPeopleWork* work) {
    g_pMana = work;
}

void _peopleRegisterAnimMix(tagPeopleWork*) {
}

s32 peopleOpen(u32 groupID, u32 peopleID, u32 objectID) {
    if (peopleGetHumanID(groupID, peopleID)) {
        return 0;
    }
    tagPeopleWork* work = peopleBiosGetNewWork();
    if (!work) {
        return 0;
    }
    if (m_bPeopleOpenWithModel) {
        if (!peopleOpenSub(work, groupID, peopleID, objectID)) {
            memset(work, 0, 0x1B0);
            return 0;
        }
    } else if (!_peopleOpenSubWithoutModel(work, groupID, peopleID, objectID)) {
        memset(work, 0, 0x1B0);
        return 0;
    }
    work->slowDown = 1;
    if (work->groupID == 0 && work->peopleID == 0x64) {
        g_pHero = work;
    }
    void* hero = getHeroPtr__4HeroFv();
    u32 followerGroup = getFollowerGrpID__4HeroFv(hero);
    u32 followerRes = getFollowerResID__4HeroFv(hero);
    if (work->groupID == followerGroup && work->peopleID == followerRes) {
        g_pMana = work;
    }
    PeopleInfo* info = peopleInfoBiosGetPtr(work->objectID);
    if (!info) {
        work->talkDistance = 3.0f;
    } else {
        work->talkDistance = peopleInfoBiosGetTalkDistance(info);
    }
    work->f7C = 0;
    work->points = 0;
    work->pointCount = 0;
    work->f2C = 1.1764706f;
    work->timer = 0.0f;
    work->timeBase = 5.0f;
    work->timeRange = 3.0f;
    f32 jitter = 2.0f * HSD_Randf() - 1.0f;
    f32 one = 1.0f;
    work->timer = work->timeRange * jitter + work->timeBase;
    work->chestReg = 0;
    work->angleSpeed = 0.0f;
    work->rotRate = one;
    work->neckMode = 0;
    work->neckSpeed = 0.07853982f;
    work->neckGoal.x = 0.0f;
    work->neckGoal.y = 0.0f;
    work->neckGoal.z = 0.0f;
    work->neckCur.x = 0.0f;
    work->neckCur.y = 0.0f;
    work->neckCur.z = 0.0f;
    work->chestRot.x = 0.0f;
    work->chestRot.y = 0.0f;
    work->chestRot.z = 0.0f;
    work->angle = 0.0f;
    if (work->model) {
        _peopleRegisterChestPart(work);
        _peopleUpdateNeck(work, 75.0f);
    }
    return work->searchID;
}
}

extern "C" {
bool peopleChangeModel(tagPeopleWork* work, u32 groupID, u32 peopleID, u32 objectID) {
    GSlight* light;
    if (objectID == work->objectID) {
        return true;
    }
    peoplePartAnimationBlinkStop(work);
    _GSmodel* model = (_GSmodel*)floorOpenObject(objectID);
    if (!model) {
        return false;
    }
    GSmodelFree(work->model);
    GSresChangeResourceAdress(model, groupID, peopleID, 0);
    work->model = model;
    work->groupID = groupID;
    work->peopleID = peopleID;
    work->objectID = objectID;
    peopleSetMotionType(work, 1);
    work->attachGroupID = -1;
    work->attachID = -1;
    work->attachPart = -1;
    work->neckMode = 0;
    u8* chr = floorCharacterBiosFindByResID(groupID, peopleID);
    if (chr) {
        if (work->isAlwayBlendChara() || (u32)((chr[0] >> 2) & 1) == 1) {
            GSmodelEnableAnimBlend(work->model);
            work->blend = 1;
        } else {
            work->blend = 0;
        }
    }
    floorDataBiosGetCurrentPtr();
    s32 index = heroIsPlayerPeople(groupID, peopleID) != 1;
    void* lightID = floorDataBiosGetShadowLightID(floorDataBiosGetCurrentPtr());
    if (lightID) {
        light = (GSlight*)GSresGetResource(floorGetCurrentGroupID(), (u32)lightID);
    } else {
        light = shadowLight[index];
    }
    GSmodelSetShadowFlags(model, 1);
    if (index == 0) {
        GSmodelSetShadowFlags(model, 4);
    }
    GSmodelSetShadowLight(model, light);
    work->chestReg = 0;
    return true;
}

bool peopleSetInfo(tagPeopleWork* work, u32 groupID, u32 peopleID, u32 objectID) {
    s32 index, blendIndex;
    f32 count, blendCount;
    void* lightID;
    GSlight* light;
    work->groupID = groupID;
    work->peopleID = peopleID;
    work->objectID = objectID;
    work->active = 1;
    work->display = 1;
    peopleSetMotionType(work, 1);
    if (peopleID == 0x64) {
        peopleSetFlags(groupID, peopleID, peopleGetFlags(groupID, peopleID) | 0x40000000 | 0xF00);
    } else if (peopleID == 0x65) {
        peopleSetFlags(groupID, peopleID, peopleGetFlags(groupID, peopleID) | 0x701);
    } else {
        peopleSetFlags(groupID, peopleID, peopleGetFlags(groupID, peopleID) | 0x700);
    }
    work->attachGroupID = -1;
    work->attachID = -1;
    work->attachPart = -1;
    void* hero = getHeroPtr__4HeroFv();
    u32 followerGroup = getFollowerGrpID__4HeroFv(hero);
    u32 followerRes = getFollowerResID__4HeroFv(hero);
    if (groupID == followerGroup && peopleID == followerRes) {
        peopleSetNeckTargetHero(groupID, peopleID);
    } else {
        work->neckMode = 0;
    }
    PeopleInfo* info;
    if (work->model && (info = peopleInfoBiosGetPtr(objectID))) {
        GSmodelSetBoundCheck(work->model, peopleInfoBiosGetBoundCheck(info));
        peopleSetDefaultMotionTable(work->groupID, work->peopleID);
    }
    u8* chr = floorCharacterBiosFindByResID(groupID, peopleID);
    if (work->model && chr && (work->isAlwayBlendChara() || (u32)((chr[0] >> 2) & 1) == 1)) {
        GSmodelEnableAnimBlend(work->model);
        work->blend = 1;
    } else {
        work->blend = 0;
    }
    if (work->model) {
        floorDataBiosGetCurrentPtr();
        s32 shadowIndex = heroIsPlayerPeople(groupID, peopleID) == 1 ? 0 : 1;
        lightID = (void*)floorDataBiosGetShadowLightID(floorDataBiosGetCurrentPtr());
        if (lightID) {
            light = (GSlight*)GSresGetResource(floorGetCurrentGroupID(), (u32)lightID);
        } else {
            light = shadowLight[shadowIndex];
        }
        GSmodelSetShadowFlags(work->model, 1);
        if (shadowIndex == 0) {
            GSmodelSetShadowFlags(work->model, 4);
        }
        GSmodelSetShadowLight(work->model, light);
    }
    work->chestUnreg = 1;
    work->waitAnim = 0;
    if (work->model && work->isAlwayBlendChara()) {
        GSmodelEnableAnimBlend(work->model);
        work->blend = 1;
    } else {
        work->blend = 0;
    }
    work->speed = work->walkRate;
    work->animEnded = 0;
    work->f14C = 0;
    work->f14D = 0;
    work->followState = 0;
    work->manualAnim = 0;
    if (work->model) {
        work->setAnimType(GS_MODEL_ANIM_TYPE_1);
        GSmodelSetTexAnimRate(work->model, 0.5f * peopleViewerGetPlaySpeedRate(work));
        if (peopleViewerIsCheckNpc(work)) {
            work->setAnimIndex(0);
            GSmodelStartAnimation(work->model);
        } else {
            u8* chr2 = floorCharacterBiosFindByResID(work->groupID, work->peopleID);
            if (!chr2 || !work->groupID) {
                if (work->isAlwayBlendChara()) {
                    work->setAnimBlend(work->motionTable[0], work->motionTable[1]);
                } else {
                    work->setAnimIndex(work->motionTable[0]);
                }
            } else {
                work->setAnimIndex(chr2[3]);
                if (chr2[3] != 3) {
                    work->manualAnim = 1;
                }
            }
            work->setAnimType(GS_MODEL_ANIM_TYPE_1);
            GSmodelStartAnimation(work->model);
        }
        GSmodelGetAnimIndex(work->model, &index, &blendIndex);
        GSmodelGetFrameCount(work->model, &count, &blendCount);
        f32 frames;
        if (blendIndex == -1) {
            frames = count;
        } else {
            frames = blendCount;
        }
        work->setAnimFrame(frames * HSD_Randf());
        GSmodelRecalculateBound(work->model);
    }
    work->neckSpeed = 0.07853982f;
    work->neckSpeedMax = 0.07853982f;
    work->neckF2 = 0;
    work->neckReg = 0;
    work->neckCur.x = 0.0f;
    work->neckCur.y = 0.0f;
    work->neckCur.z = 0.0f;
    work->neckGoal.x = 0.0f;
    work->neckGoal.y = 0.0f;
    work->neckGoal.z = 0.0f;
    work->scriptHandle = 0;
    work->f150 = 0.0f;
    work->chestRot.x = 0.0f;
    work->chestRot.y = 0.0f;
    work->chestRot.z = 0.0f;
    work->neckSaved.x = 0.0f;
    work->neckSaved.y = 0.0f;
    work->neckSaved.z = 0.0f;
    work->chestReg = 0;
    work->running = 0;
    work->f17F = 0;
    work->angleSpeed = 0.0f;
    work->rotRate = 1.0f;
    _registerNeck(work);
    return true;
}

}

static bool _peopleOpenSubWithoutModel(tagPeopleWork* work, u32 groupID, u32 peopleID, u32 objectID) {
    work->model = 0;
    work->ownsRes = 0;
    return peopleSetInfo(work, groupID, peopleID, objectID);
}

extern "C" {
bool peopleOpenSub(tagPeopleWork* work, u32 groupID, u32 peopleID, u32 objectID) {
    void* model = floorOpenObject(objectID);
    if (!model) {
        return false;
    }
    GSresRegisterResource(model, groupID, peopleID, 0);
    work->model = (_GSmodel*)model;
    work->ownsRes = 0;
    return peopleSetInfo(work, groupID, peopleID, objectID);
}
}

static void _peopleUnregisterChestPart(tagPeopleWork* work) {
    PeopleInfo* info;
    if (work && work->used && work->model && !work->chestUnreg && work->objectID &&
        (info = peopleInfoBiosGetPtr(work->objectID))) {
        s8 index = peopleInfoBiosGetChestIndex(info);
        if (index >= 0) {
            work->f130 = 0.0f;
            if (work->chestReg == 1) {
                GSpart* part = GSmodelGetPart(work->model, index);
                if (part) {
                    GSpartUnregisterAnimMix(part, 2);
                    GSpartFree(part);
                    work->chestReg = 0;
                }
            }
            work->chestUnreg = 1;
        }
    }
}

static void _peopleRegisterChestPart(tagPeopleWork* work) {
    PeopleInfo* info;
    if (work && work->used && work->model && work->chestUnreg && work->objectID &&
        (info = peopleInfoBiosGetPtr(work->objectID))) {
        s8 index = peopleInfoBiosGetChestIndex(info);
        if (index >= 0) {
            work->f130 = 0.0f;
            if (work->chestReg == 0) {
                GSpart* part = GSmodelGetPart(work->model, index);
                if (part) {
                    GSpartRegisterAnimMix(part, 2, 0x20202, _peopleGetChestRotationCB, work);
                    GSpartFree(part);
                    work->chestReg = 1;
                }
            }
            work->chestUnreg = 0;
        }
    }
}

static f32 _peopleGetChestRotationCB(GSpart*, GSpartMixType, void* user, GSvec* out) {
    tagPeopleWork* work = (tagPeopleWork*)user;
    out->x = work->chestRot.x;
    out->y = work->chestRot.y;
    out->z = work->chestRot.z;
    return 1.0f;
}

extern "C" {
u8 peopleIsBlock() {
    return m_peopleBlock;
}

void peopleUnblock() {
    if (m_peopleBlock) {
        m_peopleBlock = 0;
        GSmodelAllUnpauseAnimation();
    }
}

void peopleBlock() {
    if (!m_peopleBlock) {
        m_peopleBlock = 1;
        GSmodelAllPauseAnimation();
    }
}
}

static void _peopleExitFloor(unsigned int, FloorEnterMode mode) {
    peopleTalkLeaveFloor();
    if (mode != 1) {
        for (s32 i = peopleBiosGetMaxNum(); i-- > 0;) {
            tagPeopleWork* work = peopleBiosGetWorkPtr(i);
            if (work->used) {
                work->moveType = 0;
            }
        }
    }
}

static const char* _peopleGetModuleName() {
    return "people";
}

static u32 _peopleGetMagicNumber() {
    return 0x13;
}

static u32 _peopleGetStateSize(FloorStateMode mode) {
    if (mode == 3) {
        return peopleGetAnywaySaveSize();
    }
    if (mode == 1) {
        return peopleBiosGetPushDataSize();
    }
    return 0;
}

static void _peopleRestoreStateData(FloorStateMode mode, void* data, unsigned long size) {
    if (mode == 3) {
        peopleRestoreAnywaySaveData(data, size);
        return;
    }
    if (mode == 1) {
        peopleBiosPopData(data, size);
        return;
    }
}

static void _peopleMakeStateData(FloorStateMode mode, void* data, unsigned long size) {
    if (mode == 3) {
        peopleMakeAnywaySaveData(data, size);
        return;
    }
    if (mode == 1) {
        peopleBiosPushData(data, size);
        return;
    }
}

extern "C" {
void peopleInit(s32 count) {
    peopleBiosAllocWork(count);
    _peopleInitShadow();
    FloorModuleInterface_clear(&_floorModulePeople);
    _floorModulePeople.makeStateData = _peopleMakeStateData;
    _floorModulePeople.restoreStateData = _peopleRestoreStateData;
    _floorModulePeople.getStateSize = _peopleGetStateSize;
    _floorModulePeople.getUID = _peopleGetMagicNumber;
    _floorModulePeople.getModuleName = _peopleGetModuleName;
    _floorModulePeople.enterFloor = _peopleEnterFloor;
    _floorModulePeople.exitFloor = _peopleExitFloor;
    _hModulePeople = floorRegisterModule(0xA, 0, &_floorModulePeople);
    m_peopleBlock = 0;
}
}

static bool _peopleBlockMoveScript(tagPeopleWork* work) {
    if (!work) {
        return false;
    }
    work->active = 0;
    floorBlockScriptThread(work->scriptHandle);
    return true;
}

struct WalkHit {
    f32 height, a, b;
};

struct ThruEvent {
    GSvec tri[3];
    u8 pad24[0x10];
};

static bool _peopleAdjustPositionSub(tagPeopleWork* work, GSvec* pos, GSvec* saved) {
    GSvec hit, hiNew, hiOld, newPos, oldPos;
    f32 h;
    WalkHit hits[8];
    ThruEvent events[4];
    volatile f32 radius;
    if (peopleBiosCheckFlag(work, 0x700)) {
        newPos.x = pos->x;
        newPos.y = pos->y;
        newPos.z = pos->z;
        oldPos.x = saved->x;
        oldPos.y = saved->y;
        oldPos.z = saved->z;
        hiNew = newPos;
        hiOld = oldPos;
        f32 kc515 = 6.0f;
        f32 kc577 = 6.0f;
        hiOld.y = oldPos.y + kc577;
        hiNew.y = newPos.y + kc515;
        if (peopleInfoBiosGetPtr(work->objectID) == 0) {
            radius = 3.0f;
        } else {
            radius = peopleInfoBiosGetColBallSize(peopleInfoBiosGetPtr(work->objectID));
        }
        if (peopleBiosCheckFlag(work, 0x800) && work->peopleID == 0x64) {
            heroMoveSetEventList(2, events, GScolsys2ThruGetEventID(&hiOld, &hiNew, events, radius));
        }
        newPos.x = hiNew.x;
        newPos.y = hiNew.y;
        newPos.z = hiNew.z;
        if (gimmickBoxIsPushBoxFloor()) {
            newPos.y = hiOld.y;
        }
        if (peopleBiosCheckFlag(work, 0x400) && (s16)GScolsys2HumanCollision(work->humanID, &oldPos, &newPos, &hit) == 6) {
            work->collFlags |= 2;
            newPos.x = hit.x;
            newPos.y = hit.y;
            newPos.z = hit.z;
            if (gimmickBoxIsPushBoxFloor()) {
                newPos.y = hiOld.y;
            }
        }
        if (peopleBiosCheckFlag(work, 0x100) && GScolsys2HitCollision(&hiOld, &newPos, &hit, radius)) {
            work->collFlags |= 1;
            newPos.x = hit.x;
            newPos.y = hit.y;
            newPos.z = hit.z;
            if (gimmickBoxIsPushBoxFloor()) {
                newPos.y = hiOld.y;
            }
        }
        if (peopleBiosCheckFlag(work, 0x800) && work->peopleID == 0x64) {
            heroMoveSetEventList(1, events, GScolsys2ThruPassEventID(&hiOld, &newPos, events));
            if (gimmickBoxIsPushBoxFloor()) {
                newPos.y = hiOld.y;
            }
        }
        if (peopleBiosCheckFlag(work, 0x200)) {
            s32 n = GScolsys2WalkGetHeight(&newPos, &hits[0].height);
            if (n >= 2) {
                f32 kc2292 = 1000000.0f;
                WalkHit* p = hits;
                bool found = false;
                f32 kc2440 = 1000000.0f;
                f32 highest = -kc2440;
                s32 left = n;
                f32 best = -kc2292;
                if (n > 0) {
                    do {
                        h = p->height;
                        if (highest < h) {
                            highest = h;
                        }
                        if (!(h - newPos.y >= 10.0f) && best < h) {
                            best = h;
                            found = true;
                        }
                        p++;
                    } while (--left);
                }
                if (found) {
                    newPos.y = best;
                } else {
                    newPos.y = highest;
                }
                if (fabsf(newPos.y - peopleBiosGetPrevPosPtr(work)->y) >= 10.0f) {
                    f32 closest = hits[0].height;
                    volatile f32 bestDist = fabsf(peopleBiosGetPrevPosPtr(work)->y - hits[0].height);
                    WalkHit* q = &hits[1];
                    s32 k = 1;
                    while (k < n) {
                        f32 h = q->height;
                        f32 d = fabsf(peopleBiosGetPrevPosPtr(work)->y - h);
                        if (bestDist > d) {
                            bestDist = d;
                            closest = h;
                        }
                        q++;
                        k++;
                    }
                    newPos.y = closest;
                }
            } else if (n > 0) {
                newPos.y = hits[0].height;
            } else {
                newPos.y = 0.0f;
            }
        }
        gimmickBoxOnBox(work, &oldPos, &newPos);
        pos->x = newPos.x;
        pos->y = newPos.y;
        pos->z = newPos.z;
    }
    return work->collFlags == 0;
}

static bool _peopleAdjustPosition(tagPeopleWork* work, GSvec* pos, GSvec* saved) {
    u8* res = (u8*)GSresGetResource(0, 2);
    if (res && res[1] && (GSinputButtonsPressed(1) & 0x200)) {
        peopleBiosSetPos(work, pos);
        return true;
    }
    _peopleAdjustPositionSub(work, pos, saved);
    peopleBiosSetPos(work, pos);
    return work->collFlags == 0;
}

static void _peopleUpdateNeck(tagPeopleWork* work, f32 dist) {
    f32 pitch;
    PeopleNeckInfo info;
    f32 frame = 30.0f * _getLastFrameSec();
    if ((u16)work) {
        int mode = work->neckMode;
        if ((u8)mode != 1) {
            if (mode < 1) {
                if (mode < 0) {
                    goto finish;
                }
                if (!work->rotating) {
                    work->neckGoal.x = 0.0f;
                    work->neckGoal.y = 0.0f;
                    work->neckGoal.z = 0.0f;
                    goto finish;
                }
            } else {
                if (mode < 4) {
                    goto direct;
                }
                goto finish;
            }
        } else {
            tagPeopleWork* target = peopleGet(work->neckGroupID, work->neckPeopleID);
            if (!target) {
                work->neckMode = 0;
                return;
            }
            if (_getNeck(target, &info)) {
                work->neckTarget.x = info.pos.x;
                work->neckTarget.y = info.pos.y;
                work->neckTarget.z = info.pos.z;
            direct:
                if (_getNeck(work, &info)) {
                    f32 d = PSVECDistance(&work->neckTarget, &info.pos);
                    if (!(d > dist) || dist == 0.0f || work->neckMode == 3) {
                        pitch = adjustPIPI(atan2(info.pos.y - work->neckTarget.y, d) - work->chestRot.x);
                        if ((d < 0.00001f && d > -0.00001f) ||
                            (info.pos.y - work->neckTarget.y < 0.00001f && info.pos.y - work->neckTarget.y > -0.00001f)) {
                            pitch = 0.0f;
                        }
                        if (pitch < info.up) {
                            pitch = info.up;
                        } else if (pitch > info.down) {
                            pitch = info.down;
                        }
                        f32 yawDiff = _peopleGetDiffAngleFix(info.rot.y + work->chestRot.y,
                                                            atan2(work->neckTarget.x - info.pos.x, work->neckTarget.z - info.pos.z));
                        f32 yaw = -adjustPIPI(yawDiff);
                        if (_distanceXZ(&info.pos, &work->neckTarget) < 0.00001f &&
                            _distanceXZ(&info.pos, &work->neckTarget) > -0.00001f) {
                            yaw = 0.0f;
                        }
                        bool blocked = false;
                        if (((work->getFlags() & 0x80200000) + 0xFFE00000) == 0 && d < dist && peopleBiosCheckFlag(work, 0x100) &&
                            GScolsys2HitCollision(&info.pos, &work->neckTarget, 0, 3.0f)) {
                            blocked = true;
                        }
                        if (!blocked) {
                            if (yaw >= info.left && yaw <= info.right) {
                                work->neckGoal.y = yaw;
                                work->neckGoal.x = pitch;
                            } else if (peopleBiosCheckFlag(work, 2)) {
                                if (yaw < info.left) {
                                    yaw = info.left;
                                } else if (yaw > info.right) {
                                    yaw = info.right;
                                }
                                work->neckGoal.y = yaw;
                                work->neckGoal.x = pitch;
                            } else {
                                goto outside;
                            }
                        } else {
                        outside:
                            if (yaw < info.left - 0.034906585f || yaw > 0.034906585f + info.right) {
                                work->neckTarget.x = work->neckSaved.x;
                                work->neckTarget.y = work->neckSaved.y;
                                work->neckTarget.z = work->neckSaved.z;
                                if (!peopleBiosCheckFlag(work, 2)) {
                                    work->neckGoal.y = 0.0f;
                                    work->neckGoal.x = 0.0f;
                                }
                            }
                        }
                    }
                finish:
                    if (work->neckF3 == 1) {
                        work->neckSpeedMax = 0.15707964f;
                        work->neckSpeed = 0.07853982f;
                        work->neckF1 = 1;
                        work->neckF3 = 0;
                    }
                    f32 dx = work->neckGoal.x - work->neckCur.x;
                    f32 dy = _peopleGetDiffAngleFix(work->neckGoal.y, work->neckCur.y);
                    f32 len = sqrtf(dx * dx + dy * dy);
                    if (len < 0.00001f && len > -0.00001f) {
                        work->neckF3 = 1;
                        if (work->neckF2 == 1) {
                            work->neckF2 = 0;
                        }
                    } else {
                        f32 speed;
                        if (work->neckF1 == 1) {
                            work->neckThreshold = 0.1f * len;
                            work->neckF1 = 0;
                        }
                        if (work->neckF2 == 1) {
                            speed = 3.1415927f;
                            work->neckF2 = 0;
                        } else if (len < work->neckThreshold) {
                            if (work->neckSpeed > 0.05) {
                                work->neckSpeed -= 0.019634955f;
                                speed = work->neckSpeed;
                            } else {
                                work->neckSpeed = 0.015707964f;
                                speed = work->neckSpeed;
                            }
                        } else {
                            if (work->neckSpeed < work->neckSpeedMax) {
                                work->neckSpeed += 0.0058904868f;
                                speed = work->neckSpeed;
                            } else {
                                speed = work->neckSpeedMax;
                            }
                        }
                        f32 step = speed * (frame * peopleViewerGetPlaySpeedRate(work));
                        f32 stepX = (step * dx) / len;
                        f32 stepY = (step * dy) / len;
                        if (fabsf(dx) < fabsf(stepX)) {
                            work->neckCur.x = work->neckGoal.x;
                        } else {
                            work->neckCur.x += stepX;
                        }
                        if (fabsf(dy) < fabsf(stepY)) {
                            work->neckCur.y = work->neckGoal.y;
                            return;
                        }
                        work->neckCur.y += stepY;
                    }
                }
            }
        }
    }
}

static bool _peopleIsMoving(tagPeopleWork* work) {
    if (work->active) {
        return true;
    }
    return floorIsRunningThread(work->scriptHandle) == 0;
}

extern "C" {
void peopleSetMotionType(tagPeopleWork* work, u32 type) {
    s32 motion;
    bool loop;
    work->motionType = type;
    PeopleInfo* dc_peopleInfoBiosGetPtr = peopleInfoBiosGetPtr(work->objectID);
    if (dc_peopleInfoBiosGetPtr) {
        peopleInfoBiosGetMotion(dc_peopleInfoBiosGetPtr, work->motionType, &motion, &loop);
        if (motion != -1) {
            peopleSetMotion(work->groupID, work->peopleID, motion, 0, loop);
        }
    }
}

f32 peopleVecCalcRotY(GSvec* a, GSvec* b, f32 base) {
    GSvec diff;
    PSVECSubtract(b, a, &diff);
    f32 result = fmod(6.2831855f + (atan2f(diff.x, diff.z) - base), 6.2831854820251465);
    if (result > 3.1415927f) {
        return result - 6.2831855f;
    }
    if (result < -3.1415927f) {
        result = result + 6.2831855f;
    }
    return result;
}
}

static void _peoplePostUpdateShadows() {
    GSvec target;
    _GSmodel* model;
    if (peopleBiosGetMaxNum() != 0) {
        for (s32 i = 0; i < 2; i++) {
            target.x = 0.0f;
            target.y = 0.0f;
            target.z = 0.0f;
            s32 j = 0;
            while (j < peopleBiosGetMaxNum()) {
                tagPeopleWork* work = peopleBiosGetWorkPtr(j);
                if (work->used && (model = peopleBiosGetModelPtr(work)) && work->display && GSmodelGetVisibility(model)) {
                    s32 other = heroIsPlayerPeople(work->groupID, work->peopleID) != 1;
                    if (other == i) {
                        GSvec* pos = peopleBiosGetPosPtr(work);
                        target.x = pos->x;
                        target.y = pos->y;
                        target.z = pos->z;
                        break;
                    }
                }
                j++;
            }
            target.y = 0.0f;
            GSlightSetTarget(shadowLight[i], &target);
            target.y = 2500.0f;
            GSlightSetPosition(shadowLight[i], &target);
        }
    }
}

static void _peopleUpdateShadows(tagPeopleWork* work) {
    void* surfaces[22];
    s32 count;
    GSvec pos;
    u8 layer, subLayer;
    FloorData* floor = floorDataBiosGetCurrentPtr();
    if (floor) {
        u32 group = floorGetCurrentGroupID();
        peopleBiosGetPos(work, &pos);
        if (!GScolsys2WalkGetLayer(&pos, &layer, &subLayer)) {
            layer = 0;
            subLayer = 0;
        }
        s32 num = floorDataBiosGetShadowReciveNum(floor);
        if (layer < num) {
            if (subLayer >= num) {
                return;
            }
            count = 1;
            surfaces[0] = GSresGetResource(group, (u32)floorDataBiosGetShadowReciveID(floor, layer));
            if (layer != subLayer) {
                count = 2;
                surfaces[1] = GSresGetResource(group, (u32)floorDataBiosGetShadowReciveID(floor, subLayer));
            }
            gimmickBoxSetKenShadowOnBoxIfOnBoxFloor(work, surfaces, &count);
            GSmodelSetShadowSurface(work->model, count, surfaces);
        }
    }
}

static void _peopleInitShadow() {
    for (s32 i = 0; i < 2; i++) {
        shadowLight[i] = GSlightCreate();
        GSlightSetType(shadowLight[i], 2);
        GSlightSetActive(shadowLight[i], 0);
    }
}

extern "C" {
void peopleSetTresureSearchDistance(u32 treasureID, f32 distance) {
    tagPeopleWork* work = peopleBiosGetTresureIDToPeopleWork(treasureID);
    if (work) {
        work->talkDistance = distance;
    }
}
}

static f32 _getLastFrameSec() {
    return timeGetLastFrameSec();
}

static u32 _getLastFrameTime() {
    return timeGetLastFrameTime();
}
