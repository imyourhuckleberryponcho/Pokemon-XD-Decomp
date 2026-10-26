#include <dolphin/types.h>
class Hero {
public:
    static Hero* getHeroPtr();
    u8 getFollowerID();
    s32 getFollowerModelLevel();
    void addFootStep(unsigned long);
};
#pragma pool_strings off
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>
#include <game/shared/floor_module.h>

struct GSvec {
    f32 x, y, z;
    GSvec();
};

struct _GSmodel;
enum HEROMOVE_MEMBER { HEROMOVE_MEMBER_0, HEROMOVE_MEMBER_1, HEROMOVE_MEMBER_2, HEROMOVE_MEMBER_3 };
enum FootStepCounter { FOOT_STEP_COUNTER_0 };

struct AnalogStickEmu {
    s8 stick[4];
    u8 accel;
    u8 decel;
    void calculate(s8&, s8&, s8&, s8&);
    void init();
    inline void approach(s8& cur, s8& target);
};

static s32 abs(s8);

inline void AnalogStickEmu::approach(s8& cur, s8& target) {
    if (cur < target) {
        if (cur < 0 && target > 0) {
            cur = target;
        } else {
            s8 mag = abs(cur);
            s8 tmag = abs(target);
            if (tmag > mag) {
                cur = cur + accel;
            } else {
                cur = cur + decel;
            }
            if (cur > target) {
                cur = target;
            }
        }
    } else if (cur > target) {
        if (cur > 0 && target < 0) {
            cur = target;
        } else {
            s8 mag = abs(cur);
            s8 tmag = abs(target);
            if (tmag > mag) {
                cur = cur - accel;
            } else {
                cur = cur - decel;
            }
            if (cur < target) {
                cur = target;
            }
        }
    }
}

extern f32 __float_nan[];
struct Vec3 {
    f32 x, y, z;
};
struct FOOTWORK {
    f32 v[4];
};
struct FOOTSTEP {
    f32 speed[4];
    GSvec pos[4];
};

struct PeopleWork {
    u8 active;
    u8 pad1[0xc];
    u8 unkD;
    u8 pad0E[6];
    u32 group;
    u32 id;
    u32 objID;
    f32 walkSpeed;
    f32 runSpeed;
    f32 animRate;
    f32 unk2C;
    u8 pad30[0x20];
    s32 unk50;
    u8 pad54[0x14];
    GSvec target;
    u8 pad74[0xb0];
    s32 unk124;
    u8 pad128[0x18];
    s32 unk140;
};

struct EventTri;

struct HeroMoveEvent {
    GSvec pos[3];
    u32 unk24[3];
    u16 eventID;
    u16 pad32;
};

struct HeroMoveMember {
    s32 leader;
    u16 flags;
    u16 pad6;
    f32 formation;
    s32 neckMode;
    s32 unk10;
    u8 pad14[0xc];
};

struct StepCallback {
    void (*func)(long, FootStepCounter, long);
    s32 arg;
};

struct HeroMoveWork {
    HeroMoveMember members[4];
    u8 pad80[4];
    s32 logHead;
    s32 logCount;
    GSvec leaderLog[60];
    f32 stepAccum;
    StepCallback callbacks[8];
    s32 poisonCounter;
    s32 friendCounter;
    s32 lockFrame;
    u8 smoothFloorLink;
    u8 started;
    u8 stickOverride;
    s8 stickData[4];
    u8 pad3b3;
    u32 autoEvent[5];
    HeroMoveEvent events3[4];
    HeroMoveEvent events1[4];
    HeroMoveEvent events2[4];
    s32 eventCount3;
    s32 eventCount1;
    s32 eventCount2;
    s32 stepPool[4];
    AnalogStickEmu analog;
    s32 frameCounter;
};

extern "C" {
void heroMoveSetLockFrame(s32);
u8 floorDataBiosGetFloorKind(void*);
void* floorDataBiosGetPtr(u32);
void* floorCreateThread(s32, u32, s32, void*);
u8 floorRegisterModule(u8, u32, FloorModuleInterface*);
void FloorModuleInterface_clear(FloorModuleInterface*);
u32 GSflagGet(u32);
f32 PSVECDistance(const GSvec*, const GSvec*);
u8* itemDataBiosGetPtr(u16);
u16 itemDataBiosGetItemSoubiDataId(u8*);
u16 pokemonBiosGetItemDataId(Pokemon*);
void pokemonGetFriendFormPokemonFriendFilterId(Pokemon*, u16, u16);
void* peopleGet(u32, u32);
void peopleSetCollision(s32, s32, u8);
void peopleSetFlagOn(s32, s32, s32);
void peopleSetFlagOff(s32, s32, s32);
void peopleRemoveNeckTarget(s32, s32, f32);
void* memcpy(void*, const void*, u32);
u32 heroGetStatus(Hero*, u32, u16);
u8 pokemonCheckValid(Pokemon*);
void fadeEffectDokuStart(void);
void heroMoveInitEvent();

void heroMoveTermEvent();
char* pokemonBiosGetNicknamePtr(Pokemon*);
void msgctrlSetValue(s32, u32);
s32 winMsgOpenField(u32, bool, bool);
void winMsgCloseField(bool);
u8 GSinputGetLeftStickXData(s32, s32);
s8 GSinputGetLeftStickYData(s32, s32);
s8 GSinputGetRightStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
u32 GSinputButtonsPressed(s32);
u8 cameraGetType(void);
u8 gimmickBoxIsGimmickMoving(void);
}
static bool getResID(u32*, u32*, HEROMOVE_MEMBER);
static void getPos(GSvec*, HEROMOVE_MEMBER);
static f32 moveParty(HEROMOVE_MEMBER);
static f32 GSvecDistanceXZ(GSvec*, GSvec*);
static void* _heroGetPeople(HEROMOVE_MEMBER);
static void _getStickData(s8&, s8&, s8&, s8&);
static _GSmodel* getModel(HEROMOVE_MEMBER);
static void updateAnimation(f32, HEROMOVE_MEMBER);
static void getStep(FOOTSTEP*, _GSmodel*, int*, FOOTWORK*);
extern "C" void heroMoveCallStepCallback(FootStepCounter, s32);
static void updateMotion(HEROMOVE_MEMBER, f32);
static f32 moveLeaderPosition(HEROMOVE_MEMBER);
extern "C" HEROMOVE_MEMBER heroMoveGetLeader(void);
extern "C" s32 heroMoveJoinMember(s32);
extern "C" s32 heroMoveAppointLeader(s32);
static void initLeaderLog();
static void remakeFormation();
extern "C" u8 heroMoveSetNeckMode(s32, s32);
extern "C" s32 heroMoveGetNeckMode(s32);
static void updateLeaderLog();
static bool getLeaderLog(GSvec*, int);
extern "C" f32 GSgfxVideoGetLastRenderTime(void);
extern "C" bool heroMoveIsMember(HEROMOVE_MEMBER);
extern "C" void GSthreadSwitch(void);
extern "C" f32 timeGetLastFrameSec(void);
static void _heroMoveSlowStopFactor(f32, bool);
extern "C" void GSmodelGetPosition(_GSmodel*, Vec3*);
extern "C" void GSmodelGetRotation(_GSmodel*, GSvec*);
extern "C" void GSmodelSetRotation(_GSmodel*, GSvec*);
extern "C" _GSmodel* GSresGetResource(u32, u32);
extern "C" void peopleSetPos(u32, u32, GSvec*);
extern "C" s32 heroMoveCheckEvent(EventTri*);
extern "C" void heroMoveSetEventList(u8, void*, s32);
static u8 updateChat(HEROMOVE_MEMBER);
static f32 moveLeader(HEROMOVE_MEMBER);
static void updateLeaderMovement(HEROMOVE_MEMBER, f32*);
static void procStep(HEROMOVE_MEMBER);
static void proc1Step(f32);
static void initHeroMove();
static void initFloor();
struct GSwalkHit {
    f32 height;
    u16 attrHi;
    u16 attrLo;
    u8 layer;
    u8 subLayer;
    u8 pad[2];
};
extern "C" u8 GSfloorIsPop(void);
extern "C" s32 GScolsys2WalkGetHeight(GSvec*, GSwalkHit*);
extern "C" u32 floorGetNextFloorID(void);
extern "C" s32 menuCBBios_GetToolBattleTrainerKind(void);
extern "C" void peopleOpen(u32, u32, u32);
extern "C" void peopleAddCollision(u32, u32);
extern "C" void peopleSetFlags(s32, s32, s32);
extern "C" void peopleSetNeckLimitHold(u32, u32, u32);
extern "C" void peopleSetRot(s32, s32, GSvec*);
extern "C" void GSmodelEnableAnimBlend(_GSmodel*);
extern "C" void heroSetFollowerWithID(u8, s32);

static s32 getObjID(HEROMOVE_MEMBER);
extern "C" u32 heroGetObjID(Hero*);

extern "C" void peopleSetDisp(u32, u32, bool);
extern "C" void* GSmodelGetPart(_GSmodel*, s32);
extern "C" void GSpartGetTransform(void*, Vec3*, s32, s32);
extern "C" void GSpartFree(void*);
extern "C" f32 GSgfxVideoGetLastRenderTime(void);
extern "C" u32 GSinputButtonsChanged(s32);
extern "C" u32 GSinputButtonsPressed(s32);
extern "C" u32 GSgfxVideoGetVsyncRate(void);
extern "C" u32 timeGetLastFrameTime(u8);
extern "C" f32 PSVECMag(const Vec3*);
extern "C" void PSVECSubtract(const Vec3*, const Vec3*, Vec3*);
extern "C" s32 pokecoloFrameCounter;
extern "C" bool dbgMenuIsOpen(void);
extern "C" bool menuIsCheck(s32);
extern "C" s32 floorGetFloorState(void);
extern "C" void floorExecScriptInteger(u32, u32, u32, u32, u32);
extern "C" s32 floorEventExecScript(s32, s32);
struct FloorBgmMask {
    void stopMask();
};
extern "C" FloorBgmMask* floorSound_getBgmMaskObj(void);
extern "C" void menuFieldMain(s32);
extern "C" void peopleRotateToAngle(u32, u32, f32, f32);
extern "C" f32 peopleGetBlendFactor(f32, f32, f32);
extern "C" void peopleMoveForward(u32, u32, f32);
extern "C" f32 cameraGetRotY(void);
extern "C" void PSVECNormalize(const Vec3*, Vec3*);
extern "C" void PSVECScale(const Vec3*, Vec3*, f32);
extern "C" f32 peopleVecCalcRotY(const Vec3*, const Vec3*, f32);
extern "C" f32 GScolsys2HumanGetWalkHeight(GSvec*);
extern "C" void peopleMoveAlongAngle(u32, u32, f32, f32);
extern "C" f32* peopleBiosGetPrevPosPtr(PeopleWork*);
extern "C" u8 heroMoveChkHinderClear(s32);
extern "C" void* peopleInfoBiosGetPtr(s32);
extern "C" f32 peopleInfoBiosGetColBallSize(void*);
extern "C" bool GScolsys2HitCollision(Vec3*, Vec3*, void*);
extern "C" s32 GScolsys2HumanCollision(s32, Vec3*, Vec3*, void*);
extern "C" s32 heroGetFollower(void);
extern "C" void heroMoveGetResID(u32*, u32*, HEROMOVE_MEMBER);
extern "C" u8 peopleCheckFlag(u32, u32, u32);
extern "C" u32 peopleGetHumanID(u32, u32);
extern "C" PeopleWork* peopleSearchID(u32);
extern "C" void peopleUpdateAnimation(PeopleWork*, s32);
extern "C" f32* peopleBiosGetPosPtr(PeopleWork*);
extern "C" f32* peopleBiosGetRotPtr(PeopleWork*);
extern "C" s32 GScolsys2CheckGetEventID(Vec3*, Vec3*, EventTri*);
extern "C" void PSVECAdd(const Vec3*, const Vec3*, Vec3*);
extern "C" void peopleSetNeckTargetHero(u32, u32);
extern "C" void setFollowerGrpID__4HeroFUl(Hero*, u32);
extern "C" void setFollowerResID__4HeroFUl(Hero*, u32);
extern "C" void setFollowerID__4HeroFUc(Hero*, u8);
extern "C" u32 getFollowerResID__4HeroFv(Hero*);
extern "C" u32 getFollowerGrpID__4HeroFv(Hero*);
extern "C" PeopleWork* peopleTalkCheck(u32, u32, f32, f32);
extern "C" void GSinputResetLeftSmoothing(s32, s32, s32);
extern "C" void GSinputResetRightSmoothing(s32, s32, s32);
extern "C" void peopleGetNeckPos(u32, u32, Vec3*);
extern "C" void peopleRotateToXYZ(u32, u32, f32, f32, f32, f32);
extern "C" void peopleRotateStop(u32, u32);
extern "C" u8 peopleCheckTresure(u32, u32);
extern "C" void floorEventCtrlTresure(u32, u32, s32);
extern "C" void peopleBlockMoveScript(u32);
extern "C" void peopleUnblockMoveScript(u32);
extern "C" void peopleWalkPause(u32, u32, u8);
extern "C" void peopleWalkPauseTalkMode(u32, u32, u8);
extern "C" s32 peopleGetTalkSctID(u32, u32);
extern "C" void floorExecScriptRes(s32, u32, u32);
extern "C" void peopleTalkMsgEnd(u32, u32);
extern "C" u8 peopleBiosCheckFlag(PeopleWork*, u32);
extern "C" u8 getMoveType__13tagPeopleWorkFv(PeopleWork*);
extern "C" double sin(double);
extern "C" double cos(double);

static bool getResID(u32* group, u32* id, HEROMOVE_MEMBER member);
static s32 getObjID(HEROMOVE_MEMBER member);
extern "C" void heroMoveAllInit();
extern "C" void fn_80151F6C();
static void initHeroMove();
extern "C" void heroMoveSyncWithHero();
extern "C" s32 heroMoveInit(GSvec* pos, GSvec* rot);
extern "C" u32 heroMoveGetKenObjID();
static void initFloor();
static void initLeaderLog();
static void updateLeaderLog();
static bool getLeaderLog(GSvec* out, int index);
extern "C" s32 heroMoveAppointLeader(s32 member);
extern "C" HEROMOVE_MEMBER heroMoveGetLeader();
extern "C" s32 heroMoveJoinMember(s32 member);
extern "C" s32 heroGetFollower();
extern "C" u8 heroMoveDismissMember(s32 member);
static void remakeFormation();
extern "C" bool heroMoveIsMember(HEROMOVE_MEMBER member);
extern "C" u8 heroMoveSetNeckMode(s32 member, s32 mode);
extern "C" s32 heroMoveGetNeckMode(s32 member);
extern "C" void heroMoveGetResID(u32* group, u32* id, HEROMOVE_MEMBER member);
extern "C" s32 heroMoveMain();
static f32 moveLeader(HEROMOVE_MEMBER member);
static f32 moveLeaderPosition(HEROMOVE_MEMBER member);
static void updateLeaderMovement(HEROMOVE_MEMBER member, f32* speed);
extern "C" void heroMoveMoveParty();
static f32 moveParty(HEROMOVE_MEMBER member);
static _GSmodel* getModel(HEROMOVE_MEMBER member);
static void setDisp(HEROMOVE_MEMBER member, bool disp);
static void updateMotion(HEROMOVE_MEMBER member, f32 rate);
extern "C" void heroMoveGetHeroPos(GSvec* pos);
extern "C" void heroMoveGetHeroRot(GSvec* rot);
static void getPos(GSvec* pos, HEROMOVE_MEMBER member);
static void setPos(HEROMOVE_MEMBER member, GSvec* pos);
static void getRot(GSvec* rot, HEROMOVE_MEMBER member);
static void setRot(HEROMOVE_MEMBER member, GSvec* rot);
static void updateAnimation(f32 rate, HEROMOVE_MEMBER member);
extern "C" s32 heroMoveCheckEvent(EventTri* out);
static u8 updateChat(HEROMOVE_MEMBER member);
static void initFootWork(FOOTWORK* work);
static void getStep(FOOTSTEP* step, _GSmodel* model, int* parts, FOOTWORK* work);
static void procStep(HEROMOVE_MEMBER member);
static void proc1Step(f32 distance);
extern "C" void heroMoveCallStepCallback(FootStepCounter kind, s32 amount);
extern "C" s32 heroMoveAddStepCallback(void (*callback)(long, FootStepCounter, long), s32 arg);
extern "C" void heroMovePoolCounter(s32 kind, s32 amount);
extern "C" u8 heroMoveCallStepCallbackAll();
extern "C" void heroMoveInitEvent();
extern "C" void heroMoveTermEvent();
extern "C" void heroMoveSetColision(u8 enable);
extern "C" void heroMoveSetEventList(u8 kind, void* src, s32 count);
extern "C" void heroMoveAddAutoEvent(s32 a, s32 b, s32 c, s32 d, s32 e);
extern "C" u8 heroMoveChkHinderClear(s32 memberArg);
extern "C" void heroMoveSetLockFrame(s32 frames);
extern "C" void heroMoveSlowStop();
static void _heroMoveSlowStopFactor(f32 factor, bool moveParty_);
static void cbPoison(long, FootStepCounter counter, long);
static void cbTsureFriend(long, FootStepCounter counter, long amount);
static void actionFriendSet(Pokemon* pokemon, u16 value);
static u16 getEquipItemEffect(u16 itemID);
static s32 abs(s8 v);
static void _getStickData(s8& a, s8& b, s8& c, s8& d);
static void _setStickData(s8 a, s8 b, s8 c, s8 d);
static u8 isStoryMode();
static void* _heroGetPeople(HEROMOVE_MEMBER member);
static f32 GSvecDistanceXZ(GSvec* p, GSvec* q);
extern "C" void heroMoveSetSmoothFloorLink(u8 v);
extern "C" u8 heroMoveIsSmoothFloorLink(void);
static void _heroMoveInitialize(unsigned int groupID, FloorEnterMode mode);
static void _heroMoveFinalize(unsigned int groupID, FloorEnterMode mode);
static const char* _heroMoveGetModuleName();
static void _closeHeroThread();

static HeroMoveWork HeroMove;
static FloorModuleInterface _floorModuleHero;

static inline f32 _sqrtf(f32 x) {
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

static inline bool vecIsZero(const Vec3& v) {
    if (!(v.x < 0.00001f && v.x > -0.00001f && v.y < 0.00001f && v.y > -0.00001f && v.z < 0.00001f && v.z > -0.00001f)) {
        return false;
    }
    return true;
}

static bool getResID(u32* group, u32* id, HEROMOVE_MEMBER member) {
    u32 table[4] = {0x64, 0x65, 0x68, 0x69};
    if (member < 0 || member >= 4) {
        return false;
    }
    *group = 0;
    *id = table[member];
    return true;
}

static s32 getObjID(HEROMOVE_MEMBER member) {
    u32 group;
    u32 id;
    if (!getResID(&group, &id, member)) {
        return -1;
    }
    PeopleWork* people = peopleSearchID(peopleGetHumanID(group, id));
    if (people == 0) {
        return -1;
    }
    return people->objID;
}

extern "C" {
void heroMoveAllInit() {
    initHeroMove();
    heroMoveJoinMember(0);
    heroMoveAppointLeader(0);
    HeroMove.stepAccum = 0.0f;
    HeroMove.autoEvent[0] = 0;
    for (int i = 0; i < 8; i++) {
        HeroMove.callbacks[i].func = 0;
    }
    HeroMove.poisonCounter = 0;
    heroMoveAddStepCallback(cbPoison, 0);
    HeroMove.friendCounter = 0;
    heroMoveAddStepCallback(cbTsureFriend, 0);
    HeroMove.stickOverride = 0;
    HeroMove.stepPool[0] = 0;
    HeroMove.stepPool[1] = 0;
    HeroMove.stepPool[2] = 0;
    HeroMove.stepPool[3] = 0;
    HeroMove.analog.init();
    FloorModuleInterface_clear(&_floorModuleHero);
    _floorModuleHero.enterFloor = _heroMoveInitialize;
    _floorModuleHero.exitFloor = _heroMoveFinalize;
    _floorModuleHero.getModuleName = _heroMoveGetModuleName;
    floorRegisterModule(0x80, 0, &_floorModuleHero);
}
}

extern "C" {
void fn_80151F6C() {
    HeroMove.stepPool[0] = 0;
    HeroMove.stepPool[1] = 0;
    HeroMove.stepPool[2] = 0;
    HeroMove.stepPool[3] = 0;
}
}

static void initHeroMove() {
    HeroMove.members[0].flags = 0;
    HeroMove.members[1].flags = 0;
    HeroMove.members[2].flags = 0;
    HeroMove.members[3].flags = 0;
    HeroMove.members[0].leader = 0;
    HeroMove.lockFrame = 0;
    HeroMove.stickOverride = 0;
    HeroMove.analog.init();
}

extern "C" {
void heroMoveSyncWithHero() {
    u8 story = 0;
    if (isStoryMode() && (s32)heroGetStatus(0, 0x18, 0) != 0) {
        story = 1;
    }
    if (story) {
        heroMoveJoinMember(1);
    } else {
        heroMoveDismissMember(1);
    }
}
}

extern "C" {
s32 heroMoveInit(GSvec* pos, GSvec* rot) {
    if (!GSfloorIsPop()) {
        s32 tmp2 = heroMoveGetKenObjID();
        peopleOpen(0, 0x64, tmp2);
        peopleOpen(0, 0x65, 0x16C70400);
        peopleOpen(0, 0x68, 0x195B0400);
        peopleOpen(0, 0x69, 0x19540400);
    }
    int i;
    _GSmodel* models[4];
    for (i = 0; i < 4; i++) {
        models[i] = getModel((HEROMOVE_MEMBER)i);
        if (models[i] != 0) {
            GSmodelEnableAnimBlend(models[i]);
        }
    }
    peopleAddCollision(0, 0x64);
    peopleAddCollision(0, 0x65);
    peopleAddCollision(0, 0x68);
    peopleAddCollision(0, 0x69);
    if (!GSfloorIsPop()) {
        peopleSetFlags(0, 0x64, 0x40000F00);
        peopleSetFlags(0, 0x65, 0x701);
        peopleSetFlags(0, 0x68, 0x701);
        peopleSetFlags(0, 0x69, 0x701);
    }
    peopleSetNeckLimitHold(0, 0x65, 1);
    peopleSetNeckLimitHold(0, 0x68, 1);
    peopleSetNeckLimitHold(0, 0x69, 1);
    if (!GSfloorIsPop()) {
        peopleSetPos(0, 0x64, pos);
        peopleSetRot(0, 0x64, rot);
    }
    for (i = 0; i < 4; i++) {
        updateAnimation(0.0f, (HEROMOVE_MEMBER)i);
    }
    initFloor();
    initLeaderLog();
    HeroMove.eventCount1 = 0;
    HeroMove.eventCount2 = 0;
    HeroMove.eventCount3 = 0;
    HeroMove.lockFrame = 0;
    HeroMove.analog.init();
    Hero* hero = Hero::getHeroPtr();
    u8 followerID = hero->getFollowerID();
    s32 level = hero->getFollowerModelLevel();
    if (followerID != 0) {
        heroMoveJoinMember(followerID);
        heroSetFollowerWithID(followerID, level);
    } else {
        heroMoveDismissMember(1);
        heroMoveDismissMember(2);
        heroMoveDismissMember(3);
    }
    return 0;
}
}

extern "C" {
u32 heroMoveGetKenObjID() {
    int floorList[20] = {0x20, 0x17, 0x21, 0x18, 0x22, 0x19, 0x11, 0x1A, 0x12, 0x1B,
                         0x13, 0x1C, 0x0C, 0x1D, 0x0D, 0x1E, 0x0E, 0x1F, 0x0F, 0x10};
    struct {
        s32 kind;
        u32 objID;
    } trainerTable[5] = {{0, 0x16C90400}, {1, 0x16C90400}, {2, 0x16C90400}, {3, 0x16C90400}, {4, 0x16C90400}};
    if (isStoryMode()) {
        return heroGetObjID(0);
    }
    u32 nextFloor = floorGetNextFloorID();
    int i;
    for (i = 0; i < 20; i++) {
        if (nextFloor == floorList[i]) {
            break;
        }
    }
    if (i >= 20) {
        return heroGetObjID(0);
    }
    s32 kind = menuCBBios_GetToolBattleTrainerKind();
    int j;
    for (j = 0; j < 5; j++) {
        if (kind == trainerTable[j].kind) {
            break;
        }
    }
    return trainerTable[j].objID;
}
}

static void initFloor() {
    f32 h;
    f32 bestAny;
    Vec3 rot;
    Vec3 pos;
    if (!GSfloorIsPop()) {
        getPos((GSvec*)&pos, heroMoveGetLeader());
        getRot((GSvec*)&rot, heroMoveGetLeader());
        f32 sinY = -(f32)sin(rot.y);
        f32 cosY = -(f32)cos(rot.y);
        f32 offset = 10.0f;
        Vec3 target;
        target.y = pos.y;
        for (int i = 0; i < 4; i++) {
            if (heroMoveIsMember((HEROMOVE_MEMBER)i) && i != heroMoveGetLeader()) {
                GSwalkHit hits[8];
                target.x = sinY * offset + pos.x;
                target.y = pos.y;
                target.z = cosY * offset + pos.z;
                s32 count = GScolsys2WalkGetHeight((GSvec*)&target, hits);
                if (count > 0) {
                    if (count >= 2) {
                        f32 bestNear = -1000000.0f;
                        bestAny = bestNear;
                        int found = 0;
                        for (int k = 0; k < count; k++) {
                            h = hits[k].height;
                            if (bestAny < h) {
                                bestAny = h;
                            }
                            if (!(h - target.y >= 100.0f) && bestNear < h) {
                                bestNear = h;
                                found = 1;
                            }
                        }
                        if (found) {
                            target.y = bestNear;
                        } else {
                            target.y = bestAny;
                        }
                    } else {
                        target.y = hits[0].height;
                    }
                }
                offset += 10.0f;
                setPos((HEROMOVE_MEMBER)i, (GSvec*)&target);
                setRot((HEROMOVE_MEMBER)i, (GSvec*)&rot);
            }
        }
    }
    setDisp(HEROMOVE_MEMBER_0, heroMoveIsMember(HEROMOVE_MEMBER_0));
    if (!GSfloorIsPop()) {
        for (int i = 1; i < 4; i++) {
            setDisp((HEROMOVE_MEMBER)i, heroMoveIsMember((HEROMOVE_MEMBER)i));
        }
    }
    HeroMoveMember* m = HeroMove.members;
    for (int i = 0; i < 4; i++) {
        initFootWork((FOOTWORK*)((u8*)m + 0x14));
        m++;
    }
    for (int i = 0; i < 4; i++) {
        if (heroMoveIsMember((HEROMOVE_MEMBER)i)) {
            heroMoveSetNeckMode(i, heroMoveGetNeckMode(i));
        }
    }
    HeroMove.members[0].unk10 = 300;
    HeroMove.members[1].unk10 = 300;
    HeroMove.members[2].unk10 = 300;
    HeroMove.members[3].unk10 = 300;
    HeroMove.stepAccum = 0.0f;
}

static void initLeaderLog() {
    HeroMove.logHead = 0;
    HeroMove.logCount = 0;
}

static void updateLeaderLog() {
    u8 moved = 0;
    Vec3 prev;
    Vec3 pos;
    getPos((GSvec*)&pos, heroMoveGetLeader());
    if (getLeaderLog((GSvec*)&prev, 1)) {
        f32 dx = prev.x - pos.x;
        f32 dz = prev.z - pos.z;
        f32 sx = dx * dx;
        f32 sz = dz * dz;
        f32 len = _sqrtf(sx + sz);
        if (len > 1.0f) {
            moved = 1;
        }
    } else {
        moved = 1;
    }
    if (moved) {
        for (int i = 58; i >= 0; i--) {
            HeroMove.leaderLog[i + 1].x = HeroMove.leaderLog[i].x;
            HeroMove.leaderLog[i + 1].y = HeroMove.leaderLog[i].y;
            HeroMove.leaderLog[i + 1].z = HeroMove.leaderLog[i].z;
        }
        HeroMove.logHead = 0;
        HeroMove.leaderLog[0].x = pos.x;
        HeroMove.leaderLog[0].y = pos.y;
        HeroMove.leaderLog[0].z = pos.z;
        if (HeroMove.logCount < 0x3C) {
            HeroMove.logCount++;
        }
    }
}

static bool getLeaderLog(GSvec* out, int index) {
    if (index >= HeroMove.logCount) {
        return false;
    }
    if (index >= 0x3C) {
        return false;
    }
    out->x = HeroMove.leaderLog[index].x;
    out->y = HeroMove.leaderLog[index].y;
    out->z = HeroMove.leaderLog[index].z;
    return true;
}

extern "C" {
s32 heroMoveAppointLeader(s32 member) {
    if (!heroMoveIsMember((HEROMOVE_MEMBER)member)) {
        return 0;
    }
    HeroMove.members[0].leader = member;
    if (heroMoveGetNeckMode(member) == 1) {
        heroMoveSetNeckMode(member, 0);
    }
    remakeFormation();
    initLeaderLog();
    return 1;
}
}

extern "C" {
HEROMOVE_MEMBER heroMoveGetLeader() { return (HEROMOVE_MEMBER)HeroMove.members[0].leader; }
}

extern "C" {
s32 heroMoveJoinMember(s32 member) {
    Hero* hero;
    if (member < 0 || member >= 4) {
        return 0;
    }
    if (heroMoveIsMember((HEROMOVE_MEMBER)member)) {
        return 1;
    }
    hero = Hero::getHeroPtr();
    setFollowerGrpID__4HeroFUl(hero, 0);
    switch (member) {
    case 1:
        setFollowerResID__4HeroFUl(hero, 0x65);
        setFollowerID__4HeroFUc(hero, 1);
        break;
    case 2:
        setFollowerResID__4HeroFUl(hero, 0x68);
        setFollowerID__4HeroFUc(hero, 2);
        break;
    case 3:
        setFollowerResID__4HeroFUl(hero, 0x69);
        setFollowerID__4HeroFUc(hero, 3);
        break;
    }
    HeroMove.members[member].flags |= 1;
    heroMoveSetNeckMode(member, 1);
    remakeFormation();
    setDisp((HEROMOVE_MEMBER)member, true);
    return 1;
}
}

extern "C" {
s32 heroGetFollower() {
    Hero* hero = Hero::getHeroPtr();
    PeopleWork* people = (PeopleWork*)peopleGet(getFollowerGrpID__4HeroFv(hero), getFollowerResID__4HeroFv(hero));
    if (people == 0) {
        return 0;
    }
    if (people->active == 0) {
        return 0;
    }
    if (people->unkD == 0) {
        return 0;
    }
    if (people->objID == 0) {
        return 0;
    }
    switch (getFollowerResID__4HeroFv(hero)) {
    case 0x65:
        return HeroMove.members[1].flags & 1;
    case 0x68:
        return 2 & -(HeroMove.members[2].flags & 1);
    case 0x69:
        return 3 & -(HeroMove.members[3].flags & 1);
    default:
        return 0;
    }
}
}

extern "C" {
u8 heroMoveDismissMember(s32 member) {
    if (member < 0 || member >= 4) {
        return 0;
    }
    if (member == heroMoveGetLeader()) {
        return 0;
    }
    HeroMove.members[member].flags &= 0xFFFE;
    remakeFormation();
    return 1;
}
}

static void remakeFormation() {
    f32 dist = 12.0f;
    f32 step = 12.0f;
    HeroMove.members[HeroMove.members[0].leader].formation = 0.0f;
    HeroMoveMember* m = HeroMove.members;
    for (int i = 0; i < 4; i++) {
        if ((m->flags & 1) && HeroMove.members[0].leader != i) {
            m->formation = dist;
            dist += step;
        }
        m++;
    }
}

extern "C" {
bool heroMoveIsMember(HEROMOVE_MEMBER member) {
    if (member < 0 || member >= 4) {
        return 0;
    }
    return HeroMove.members[member].flags & 1;
}
}

extern "C" {
u8 heroMoveSetNeckMode(s32 member, s32 mode) {
    if ((mode < 0) || (mode >= 2)) {
        return 0;
    }
    if (!heroMoveIsMember((HEROMOVE_MEMBER)member)) {
        return 0;
    }
    u32 group;
    u32 id;
    getResID(&group, &id, (HEROMOVE_MEMBER)member);
    HeroMoveMember * m;
    switch ((&HeroMove.members[member])->neckMode) {
    case 1:
        peopleRemoveNeckTarget(group, id, 1.0f);
        break;
    }
    switch (mode) {
    case 1:
        peopleSetNeckTargetHero(group, id);
        break;
    }
    (&HeroMove.members[member])->neckMode = mode;
    return 1;
}
}

extern "C" {
s32 heroMoveGetNeckMode(s32 member) {
    if (heroMoveIsMember((HEROMOVE_MEMBER)member)) {
        return HeroMove.members[member].neckMode;
    }
    return 2;
}
}

extern "C" {
void heroMoveGetResID(u32* group, u32* id, HEROMOVE_MEMBER member) { getResID(group, id, member); }
}

extern "C" {
s32 heroMoveMain() {
    u32 handled = 0;
    int i;
    if (!HeroMove.started) {
        HeroMove.started = 1;
    }
    if (dbgMenuIsOpen()) {
        return 0;
    }
    if (menuIsCheck(0x23)) {
        return 0;
    }
    if (floorGetFloorState() == 2 || floorGetFloorState() == 6) {
        return 0;
    }
    if (cameraGetType() == 6) {
        return 0;
    }
    if (menuIsCheck(0xA)) {
        return 0;
    }
    if (HeroMove.lockFrame > 0) {
        HeroMove.lockFrame--;
        return 0;
    }
    HeroMove.frameCounter = pokecoloFrameCounter;
    u32 group;
    u32 id;
    heroMoveGetResID(&group, &id, heroMoveGetLeader());
    if (peopleCheckFlag(group, id, 0x80000000)) {
        return 0;
    }
    u32 script = HeroMove.autoEvent[0];
    if (script != 0) {
        HeroMove.autoEvent[0] = 0;
        floorExecScriptInteger(script, HeroMove.autoEvent[1], HeroMove.autoEvent[2], HeroMove.autoEvent[3], HeroMove.autoEvent[4]);
        return 0;
    }
    if (heroMoveCallStepCallbackAll()) {
        return 0;
    }
    for (i = 0; i < HeroMove.eventCount3; i++) {
        handled += floorEventExecScript(3, HeroMove.events3[i].eventID);
    }
    for (i = 0; i < HeroMove.eventCount2; i++) {
        handled += floorEventExecScript(2, HeroMove.events2[i].eventID);
    }
    for (i = 0; i < HeroMove.eventCount1; i++) {
        handled += floorEventExecScript(1, HeroMove.events1[i].eventID);
    }
    HeroMove.eventCount1 = 0;
    HeroMove.eventCount2 = 0;
    HeroMove.eventCount3 = 0;
    if (HeroMove.autoEvent[0] != 0) {
        return 0;
    }
    if (!gimmickBoxIsGimmickMoving() && handled == 0 && !peopleCheckFlag(group, id, 0x80000000)) {
        if (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x1C00) {
            FloorBgmMask* mask = floorSound_getBgmMaskObj();
            if (mask != 0) {
                mask->stopMask();
            }
            menuFieldMain(0);
            return 0;
        }
    }
    if ((u32)(pokecoloFrameCounter - HeroMove.frameCounter) > 5) {
        HeroMove.analog.init();
    }
    f32 moved = moveLeader(heroMoveGetLeader());
    procStep(heroMoveGetLeader());
    proc1Step(moved);
    return 0;
}
}

static f32 moveLeader(HEROMOVE_MEMBER member) {
    if ((GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x100) && updateChat(member)) {
        return 0.0f;
    }
    return moveLeaderPosition(member);
}

static f32 moveLeaderPosition(HEROMOVE_MEMBER member) {
    u8 rate = GSgfxVideoGetVsyncRate();
    volatile f32 rateF = rate;
    u32 frame = timeGetLastFrameTime(rate);
    f32 dt = (30.0f * (f32)frame) / rateF;
    Vec3 before;
    Vec3 after;
    Vec3 diff;
    f32 speed;
    u32 group;
    u32 id;
    getPos((GSvec*)&before, member);
    updateLeaderMovement(member, &speed);
    getPos((GSvec*)&after, member);
    PSVECSubtract(&after, &before, &diff);
    getResID(&group, &id, member);
    f32 dist = PSVECMag(&diff);
    if (dt == 0.0f) {
        updateMotion(member, 0.0f);
    } else {
        updateMotion(member, dist / dt);
    }
    updateLeaderLog();
    return dist;
}

static void updateLeaderMovement(HEROMOVE_MEMBER member, f32* speed) {
    u32 group;
    u32 id;
    s8 lx;
    s8 ly;
    s8 rx;
    s8 ry;
    GSresGetResource(0, 2);
    getResID(&group, &id, member);
    getModel(member);
    _getStickData(lx, ly, rx, ry);
    if (!gimmickBoxIsGimmickMoving()) {
        if (lx != 0 || ly != 0) {
            if (lx > 0x38) {
                lx = 0x38;
            } else if (lx < -0x38) {
                lx = -0x38;
            }
            if (ly > 0x38) {
                ly = 0x38;
            } else if (ly < -0x38) {
                ly = -0x38;
            }
            int ax = lx > 0 ? lx : -lx;
            f32 fx = (f32)ax / 28.0f;
            int ay = ly > 0 ? ly : -ly;
            f32 fy = (f32)ay / 28.0f;
            *speed = _sqrtf(fx * fx + fy * fy);
            if (*speed > 2.0f) {
                *speed = 2.0f;
            }
            if (rx <= -2 || rx >= 2 || ry <= -2 || ry >= 2) {
                f32 angle;
                f32 dir;
                if (fy < 0.001f) {
                    angle = 1.5707964f;
                } else {
                    f32 q = fx / fy;
                    if (q > 5.0f) {
                        q = 5.0f;
                    }
                    angle = 1.5707964f * (f32)sin(q / 3.1830988f);
                }
                if (ly >= 0) {
                    dir = angle;
                } else {
                    dir = 3.1415927f - angle;
                }
                if (lx < 0) {
                    if (ly >= 0) {
                        dir = 3.1415927f + (3.1415927f - angle);
                    } else {
                        dir = 3.1415927f + angle;
                    }
                }
                peopleRotateToAngle(group, id, dir + cameraGetRotY(), *speed);
            }
            PeopleWork* people = peopleSearchID(peopleGetHumanID(group, id));
            if (*speed < 1.0f) {
                *speed = people->walkSpeed * peopleGetBlendFactor(*speed, 0.0f, 1.0f);
            } else {
                f32 blend = peopleGetBlendFactor(*speed, 1.0f, 2.0f);
                *speed = (1.0f - blend) * people->walkSpeed + blend * people->runSpeed;
            }
            peopleMoveForward(group, id, *speed);
            return;
        }
        *speed = 0.0f;
        peopleRotateStop(group, id);
    }
}

extern "C" {
void heroMoveMoveParty() {
    for (int i = 0; i < 4; i++) {
        if (heroMoveIsMember((HEROMOVE_MEMBER)i) && i != heroMoveGetLeader()) {
            moveParty((HEROMOVE_MEMBER)i);
        }
    }
}
}

static f32 moveParty(HEROMOVE_MEMBER member) {
    Vec3 target;
    Vec3 dir;
    Vec3 away;
    Vec3 diff;
    Vec3 sum;
    PeopleWork* memberPeople = (PeopleWork*)_heroGetPeople(member);
    if (memberPeople == 0) {
        return 0.0f;
    }
    if (memberPeople->unk124 > 0) {
        HeroMove.logCount = 0;
        return 0.0f;
    }
    PeopleWork* leaderPeople = (PeopleWork*)peopleGet(0, 0x64);
    if (leaderPeople == 0) {
        return 0.0f;
    }
    Hero* hero = Hero::getHeroPtr();
    PeopleWork* follower = (PeopleWork*)peopleGet(getFollowerGrpID__4HeroFv(hero), getFollowerResID__4HeroFv(hero));
    if (follower == 0) {
        return 0.0f;
    }
    if (peopleBiosCheckFlag(follower, 0x80000000)) {
        return 0.0f;
    }
    Vec3* leaderPos = (Vec3*)peopleBiosGetPosPtr(leaderPeople);
    Vec3* followerPos = (Vec3*)peopleBiosGetPosPtr(follower);
    s32 followerMember = heroGetFollower();
    if (followerMember == 0) {
        return 0.0f;
    }
    if (heroMoveChkHinderClear(followerMember) && follower->unk140 == 0) {
        HeroMove.logCount = 0;
    }
    static f32 radius_fix = 3.0f;
    int j;
    for (j = 0; j < HeroMove.logCount; j++) {
        if (PSVECDistance((GSvec*)followerPos, &HeroMove.leaderLog[j]) < radius_fix) {
            HeroMove.logCount = j + 1;
            break;
        }
    }
    if (memberPeople->unk140 != 0) {
        return 0.0f;
    }
    if (HeroMove.logCount > 0) {
        GSvec* last = &HeroMove.leaderLog[HeroMove.logCount - 1];
        target.x = last->x;
        target.y = last->y;
        target.z = last->z;
    } else {
        PSVECSubtract(followerPos, leaderPos, &diff);
        dir = diff;
        if (vecIsZero(dir)) {
            dir.x = 0.0f;
            dir.y = 0.0f;
            dir.z = 1.0f;
        }
        PSVECNormalize(&dir, &dir);
        PSVECScale(&dir, &dir, 10.950001f);
        PSVECAdd(leaderPos, &dir, &sum);
        target = sum;
    }
    GSvecDistanceXZ((GSvec*)followerPos, (GSvec*)&target);
    f32 dist = GSvecDistanceXZ((GSvec*)followerPos, (GSvec*)leaderPos);
    s8 lx;
    s8 ly;
    s8 rx;
    s8 ry;
    _getStickData(lx, ly, rx, ry);
    static f32 len_fix = 0.5f;
    if (dist < 12.0f - len_fix && lx == 0 && ly == 0 && rx == 0 && ry == 0) {
        return 0.0f;
    }
    follower->target.x = target.x;
    follower->target.y = target.y;
    follower->target.z = target.z;
    f32 dirTarget = peopleVecCalcRotY(followerPos, (Vec3*)&follower->target, 0.0f);
    f32 dirLeader = peopleVecCalcRotY(followerPos, leaderPos, 0.0f);
    f32 speed;
    if (dist <= 12.0f) {
        PSVECSubtract(followerPos, leaderPos, &away);
        if (dist < 0.00001f && dist > -0.00001f) {
            away.x = 0.0f;
            away.y = 0.0f;
            away.z = 10.950001f;
        } else {
            away.y = 0.0f;
            PSVECNormalize(&away, &away);
            PSVECScale(&away, &away, 10.950001f);
        }
        PSVECAdd(leaderPos, &away, (Vec3*)&follower->target);
        follower->target.y = GScolsys2HumanGetWalkHeight(&follower->target);
        dirTarget = peopleVecCalcRotY(followerPos, (Vec3*)&follower->target, 0.0f);
        if (dist < 9.900001f) {
            if (dist <= 9.0f) {
                speed = leaderPeople->unk2C;
            } else {
                speed = leaderPeople->unk2C * peopleGetBlendFactor(dist, 9.900001f, 9.0f);
            }
        } else {
            speed = 0.0f;
        }
    } else if (dist < 18.0f) {
        speed = leaderPeople->runSpeed * peopleGetBlendFactor(dist, 12.0f, 18.0f);
    } else {
        speed = leaderPeople->runSpeed;
    }
    peopleRotateToAngle(getFollowerGrpID__4HeroFv(hero), getFollowerResID__4HeroFv(hero), dirLeader, 20.0f);
    peopleMoveAlongAngle(getFollowerGrpID__4HeroFv(hero), getFollowerResID__4HeroFv(hero), speed, dirTarget);
    return GSvecDistanceXZ((GSvec*)peopleBiosGetPosPtr(follower), (GSvec*)peopleBiosGetPrevPosPtr(follower));
}

static _GSmodel* getModel(HEROMOVE_MEMBER member) {
    u32 group;
    u32 id;
    getResID(&group, &id, member);
    return GSresGetResource(group, id);
}

static void setDisp(HEROMOVE_MEMBER member, bool disp) {
    u32 group;
    u32 id;
    getResID(&group, &id, member);
    peopleSetDisp(group, id, disp);
}

static void updateMotion(HEROMOVE_MEMBER member, f32 rate) {
    getModel(member);
    updateAnimation(rate, member);
}

extern "C" {
void heroMoveGetHeroPos(GSvec* pos) { getPos(pos, heroMoveGetLeader()); }
}

extern "C" {
void heroMoveGetHeroRot(GSvec* rot) { getRot(rot, heroMoveGetLeader()); }
}

static void getPos(GSvec* pos, HEROMOVE_MEMBER member) {
    _GSmodel* model = getModel(member);
    if (model != 0) {
        GSmodelGetPosition(model, (Vec3*)pos);
    }
}

static void setPos(HEROMOVE_MEMBER member, GSvec* pos) {
    u32 group;
    u32 id;
    getResID(&group, &id, member);
    peopleSetPos(group, id, pos);
}

static void getRot(GSvec* rot, HEROMOVE_MEMBER member) { GSmodelGetRotation(getModel(member), rot); }

static void setRot(HEROMOVE_MEMBER member, GSvec* rot) { GSmodelSetRotation(getModel(member), rot); }

static void updateAnimation(f32 rate, HEROMOVE_MEMBER member) {
    u32 group;
    u32 id;
    getResID(&group, &id, member);
    PeopleWork* people = peopleSearchID(peopleGetHumanID(group, id));
    if (people != 0) {
        people->animRate = rate;
        peopleUpdateAnimation(people, 0);
    }
}

extern "C" {
s32 heroMoveCheckEvent(EventTri* out) {
    s32 result;
    u32 group;
    u32 id;
    getResID(&group, &id, heroMoveGetLeader());
    PeopleWork* people = peopleSearchID(peopleGetHumanID(group, id));
    if (people != 0) {
        f32* pos = peopleBiosGetPosPtr(people);
        f32* rot = peopleBiosGetRotPtr(people);
        Vec3 start;
        Vec3 end;
        start.x = pos[0];
        start.y = pos[1];
        start.z = pos[2];
        start.y += 5.0f;
        end.x = 10.0f * (f32)sin(rot[1]);
        end.y = 0.0f;
        end.z = 10.0f * (f32)cos(rot[1]);
        PSVECAdd(&start, &end, &end);
        result = GScolsys2CheckGetEventID(&start, &end, out);
    }
    return result;
}
}

static u8 updateChat(HEROMOVE_MEMBER member) {
    u32 group;
    u32 id;
    PeopleWork* target;
    s32 script;
    s32 count;
    u8 walking;
    getResID(&group, &id, member);
    target = peopleTalkCheck(group, id, 0.3f, 40.0f);
    if (target == 0) {
        HeroMoveEvent events[4];
        count = heroMoveCheckEvent((EventTri*)events);
        heroMoveSetEventList(3, events, count);
        if (count != 0) {
            peopleRotateStop(0, 0x64);
            return 1;
        }
        return 0;
    }
    GSinputResetLeftSmoothing(1, 0, 0);
    GSinputResetRightSmoothing(1, 0, 0);
    heroMoveInitEvent();
    Vec3 neck;
    peopleGetNeckPos(target->group, target->id, &neck);
    peopleRotateToXYZ(group, id, neck.x, neck.y, neck.z, 1.0f);
    if (peopleCheckTresure(target->group, target->id)) {
        floorEventCtrlTresure(target->group, target->id, 2);
    } else {
        walking = 0;
        u8 moveType = getMoveType__13tagPeopleWorkFv(target);
        if (moveType == 2 || moveType == 3) {
            walking = 1;
        }
        peopleBlockMoveScript(peopleGetHumanID(target->group, target->id));
        if (walking) {
            peopleWalkPause(target->group, target->id, 1);
        }
        script = peopleGetTalkSctID(target->group, target->id);
        if (script != 0) {
            peopleWalkPauseTalkMode(target->group, target->id, 1);
            floorExecScriptRes(script, target->group, target->id);
            peopleWalkPauseTalkMode(target->group, target->id, 0);
            peopleTalkMsgEnd(target->group, target->id);
        }
        if (walking && !peopleBiosCheckFlag(target, 0x80000)) {
            peopleWalkPause(target->group, target->id, 0);
        }
        peopleUnblockMoveScript(peopleGetHumanID(target->group, target->id));
    }
    heroMoveTermEvent();
    GSinputResetLeftSmoothing(1, 0, 0);
    GSinputResetRightSmoothing(1, 0, 0);
    return 1;
}

static void initFootWork(FOOTWORK* work) {
    work->v[0] = 0.0f;
    work->v[1] = 0.0f;
    work->v[2] = 0.0f;
    work->v[3] = 0.0f;
}

static void getStep(FOOTSTEP* step, _GSmodel* model, int* parts, FOOTWORK* work) {
    void* part;
    f32 dt = GSgfxVideoGetLastRenderTime();
    Vec3 modelPos;
    GSmodelGetPosition(model, &modelPos);
    Vec3 t;
    f32 cur[4];
    for (int i = 0; i < 4; i++) {
        cur[i] = 0.0f;
        step->pos[i].x = 0.0f;
        step->pos[i].y = 0.0f;
        step->pos[i].z = 0.0f;
        if (parts[i] >= 0) {
            part = GSmodelGetPart(model, parts[i]);
            if (part != 0) {
                GSpartGetTransform(part, &t, 0, 0);
                GSpartFree(part);
                cur[i] = t.y - modelPos.y;
                step->pos[i].x = t.x;
                step->pos[i].y = t.y;
                step->pos[i].z = t.z;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        f32 old = work->v[i];
        if (old >= 0.5f && cur[i] < 0.5f) {
            step->speed[i] = (old - cur[i]) / dt;
        } else {
            step->speed[i] = 0.0f;
        }
    }
    for (int i = 0; i < 4; i++) {
        work->v[i] = cur[i];
    }
}

static void procStep(HEROMOVE_MEMBER member) {
    int partTable[2][4] = {{0x35, 0x30, -1, -1}, {0x2E, 0x29, -1, -1}};
    GSgfxVideoGetLastRenderTime();
    FOOTSTEP step;
    _GSmodel* model = getModel(member);
    if (model != 0) {
        getStep(&step, model, partTable[member], (FOOTWORK*)((u8*)&HeroMove + member * 0x20 + 0x14));
    }
}

static void proc1Step(f32 distance) {
    Hero* hero = Hero::getHeroPtr();
    if (isStoryMode()) {
        u32 group;
        u32 id;
        heroMoveGetResID(&group, &id, heroMoveGetLeader());
        if (!peopleCheckFlag(group, id, 0x80000000)) {
            HeroMove.stepAccum += distance;
            while (HeroMove.stepAccum >= 7.0f) {
                hero->addFootStep(1);
                heroMoveCallStepCallback((FootStepCounter)0, 1);
                HeroMove.stepAccum -= 7.0f;
            }
        }
    }
}

extern "C" {
void heroMoveCallStepCallback(FootStepCounter kind, s32 amount) {
    HeroMoveWork* hm = &HeroMove;
    for (int i = 0; i < 8; i++) {
        StepCallback* cb = &hm->callbacks[i];
        if (cb != 0 && cb->func != 0) {
            cb->func(cb->arg, kind, amount);
        }
    }
}
}

extern "C" {
s32 heroMoveAddStepCallback(void (*callback)(long, FootStepCounter, long), s32 arg) {
    int i;
    for (i = 0; i < 8; i++) {
        if (HeroMove.callbacks[i].func == 0) {
            break;
        }
    }
    if (i >= 8) {
        return -1;
    }
    HeroMove.callbacks[i].func = callback;
    HeroMove.callbacks[i].arg = arg;
    return i;
}
}

extern "C" {
void heroMovePoolCounter(s32 kind, s32 amount) {
    switch (kind) {
    case 0:
        HeroMove.stepPool[0] += amount;
        break;
    case 1:
        HeroMove.stepPool[1] += amount;
        break;
    case 2:
        HeroMove.stepPool[2] += amount;
        break;
    case 3:
        HeroMove.stepPool[3] += amount;
        break;
    }
}
}

extern "C" {
u8 heroMoveCallStepCallbackAll() {
    u8 called = 0;
    if (HeroMove.stepPool[0] != 0) {
        heroMoveCallStepCallback((FootStepCounter)0, HeroMove.stepPool[0]);
        called = 1;
        HeroMove.stepPool[0] = 0;
    }
    if (HeroMove.stepPool[1] != 0) {
        heroMoveCallStepCallback((FootStepCounter)1, HeroMove.stepPool[1]);
        called = 1;
        HeroMove.stepPool[1] = 0;
    }
    if (HeroMove.stepPool[2] != 0) {
        heroMoveCallStepCallback((FootStepCounter)2, HeroMove.stepPool[2]);
        called = 1;
        HeroMove.stepPool[2] = 0;
    }
    if (HeroMove.stepPool[3] != 0) {
        heroMoveCallStepCallback((FootStepCounter)3, HeroMove.stepPool[3]);
        called = 1;
        HeroMove.stepPool[3] = 0;
    }
    return called;
}
}

extern "C" {
void heroMoveInitEvent() {
    for (int i = 0; i < 4; i++) {
        if (heroMoveIsMember((HEROMOVE_MEMBER)i)) {
            u32 group;
            u32 id;
            getResID(&group, &id, (HEROMOVE_MEMBER)i);
            getModel((HEROMOVE_MEMBER)i);
            updateAnimation(0.0f, (HEROMOVE_MEMBER)i);
            peopleSetFlagOn(group, id, 0x80000008);
            peopleSetFlagOff(group, id, 0x100);
            peopleSetFlagOff(group, id, 0x400);
            peopleSetCollision(group, id, 0);
        }
    }
}
}

extern "C" {
void heroMoveTermEvent() {
    for (int i = 0; i < 4; i++) {
        if (heroMoveIsMember((HEROMOVE_MEMBER)i)) {
            u32 group;
            u32 id;
            getResID(&group, &id, (HEROMOVE_MEMBER)i);
            peopleSetCollision((u16)group, id, 1);
            peopleSetFlagOn(group, id, 0x700);
            peopleSetFlagOff(group, id, 0x80000008);
        }
    }
    HeroMove.analog.init();
    peopleRemoveNeckTarget(0, 0x64, 1.0f);
}
}

extern "C" {
void heroMoveSetColision(u8 enable) {
    for (int i = 0; i < 4; i++) {
        if (heroMoveIsMember((HEROMOVE_MEMBER)i)) {
            u32 group;
            u32 id;
            getResID(&group, &id, (HEROMOVE_MEMBER)i);
            if (enable) {
                peopleSetCollision(group, id, 1);
                peopleSetFlagOn(group, id, 0x700);
            } else {
                peopleSetFlagOff(group, id, 0x100);
                peopleSetFlagOff(group, id, 0x400);
                peopleSetCollision(group, id, 0);
            }
        }
    }
}
}

extern "C" {
void heroMoveSetEventList(u8 kind, void* src, s32 count) {
    switch (kind) {
    case 1:
        memcpy(HeroMove.events1, src, 0xD0);
        HeroMove.eventCount1 = count;
        break;
    case 2:
        memcpy(HeroMove.events2, src, 0xD0);
        HeroMove.eventCount2 = count;
        break;
    case 3:
        memcpy(HeroMove.events3, src, 0xD0);
        HeroMove.eventCount3 = count;
        break;
    }
}
}

extern "C" {
void heroMoveAddAutoEvent(s32 a, s32 b, s32 c, s32 d, s32 e) {
    HeroMove.autoEvent[0] = a;
    HeroMove.autoEvent[1] = b;
    HeroMove.autoEvent[2] = c;
    HeroMove.autoEvent[3] = d;
    HeroMove.autoEvent[4] = e;
}
}

extern "C" {
u8 heroMoveChkHinderClear(s32 memberArg) {
    HEROMOVE_MEMBER leader;
    s32 colID;
    HEROMOVE_MEMBER member = (HEROMOVE_MEMBER)memberArg;
    if (!heroMoveIsMember(member)) {
        return 0;
    }
    leader = heroMoveGetLeader();
    Vec3 memberPos;
    Vec3 leaderPos;
    Vec3 diff;
    Vec3 scaled;
    u32 group;
    u32 id;
    getPos((GSvec*)&memberPos, member);
    memberPos.y += 8.5f;
    getPos((GSvec*)&leaderPos, leader);
    leaderPos.y += 8.5f;
    u32 obj = getObjID(member);
    if (obj == 0xFFFFFFFF) {
        return 0;
    }
    void* info = peopleInfoBiosGetPtr(obj);
    if (info == 0) {
        return 0;
    }
    f32 size1 = peopleInfoBiosGetColBallSize(info);
    if (GScolsys2HitCollision(&memberPos, &leaderPos, 0)) {
        return 0;
    }
    obj = getObjID(leader);
    if (obj == 0xFFFFFFFF) {
        return 0;
    }
    info = peopleInfoBiosGetPtr(obj);
    if (info == 0) {
        return 0;
    }
    f32 size2 = peopleInfoBiosGetColBallSize(info);
    getResID(&group, &id, member);
    PeopleWork* people = peopleSearchID(peopleGetHumanID(group, id));
    if (people == 0) {
        return 0;
    }
    colID = people->unk50;
    getPos((GSvec*)&memberPos, member);
    getPos((GSvec*)&leaderPos, leader);
    PSVECSubtract(&leaderPos, &memberPos, &diff);
    f32 total = size1 + size2;
    f32 dx = memberPos.x - leaderPos.x;
    f32 dz = memberPos.z - leaderPos.z;
    f32 sx = dx * dx;
    f32 sz = dz * dz;
    f32 len = _sqrtf(sx + sz);
    if (len <= 0.0f) {
        return 1;
    }
    if (len <= total) {
        return 1;
    }
    PSVECScale(&diff, &scaled, ((len - total) - 0.010000001f) / len);
    PSVECAdd(&memberPos, &scaled, &leaderPos);
    return GScolsys2HumanCollision(colID, &memberPos, &leaderPos, 0) != 6;
}
}

extern "C" {
void heroMoveSetLockFrame(s32 frames) {
    if (frames >= 0) {
        HeroMove.lockFrame = frames;
        HeroMove.analog.init();
    }
}
}

extern "C" {
void heroMoveSlowStop() { _heroMoveSlowStopFactor(3.0f, false); }
}

static void _heroMoveSlowStopFactor(f32 factor, bool moveParty_) {
    s8 a;
    s8 b;
    s8 c;
    s8 d;
    heroMoveGetLeader();
    _getStickData(a, b, c, d);
    f32 scale = 1.0f;
    f32 fa = a;
    f32 fb = b;
    f32 fc = c;
    f32 fd = d;
    while (scale >= 0.0f) {
        if (moveParty_) {
            for (int i = 0; i < 4; i++) {
                if (heroMoveIsMember((HEROMOVE_MEMBER)i) && i != heroMoveGetLeader()) {
                    updateMotion((HEROMOVE_MEMBER)i, moveParty((HEROMOVE_MEMBER)i));
                }
            }
        }
        fa *= scale;
        fb *= scale;
        fc *= scale;
        fd *= scale;
        _setStickData((s8)fa, (s8)fb, (s8)fc, (s8)fd);
        moveLeaderPosition(HEROMOVE_MEMBER_0);
        if (moveParty_) {
            moveLeaderPosition(HEROMOVE_MEMBER_1);
            moveLeaderPosition(HEROMOVE_MEMBER_2);
            moveLeaderPosition(HEROMOVE_MEMBER_3);
        }
        GSthreadSwitch();
        scale -= factor * timeGetLastFrameSec();
    }
    HeroMove.stickOverride = 0;
}

static void cbPoison(long, FootStepCounter counter, long) {
    int faintedCount = 0;
    u8 poisoned = 0;
    int alive;
    if (counter == 0) {
        if (++HeroMove.poisonCounter >= 4) {
            alive = 0;
            HeroMove.poisonCounter = 0;
            for (int i = 0; i < 6; i++) {
                Pokemon* pokemon = (Pokemon*)heroGetStatus(0, 3, i);
                if (pokemon != 0 && pokemonCheckValid(pokemon) && pokemon->getHp() != 0) {
                    alive++;
                }
            }
            int faintedIdx[6];
            for (int i = 0; i < 6; i++) {
                Pokemon* pokemon = (Pokemon*)heroGetStatus(0, 3, i);
                if (pokemon != 0 && pokemonCheckValid(pokemon)) {
                    u16 hp = pokemon->getHp();
                    if (hp != 0) {
                        u8 condition = pokemon->getCondition();
                        if (condition == 3 || condition == 4) {
                            poisoned = 1;
                            if (alive > 1 || hp > 1) {
                                pokemon->setHp(hp - 1);
                                if ((u16)(hp - 1) == 0) {
                                    faintedIdx[faintedCount] = i;
                                    alive--;
                                    faintedCount++;
                                    pokemon->initCondition();
                                    DarkPokemon* dark = pokemon->getDarkPokemon();
                                    if (dark != 0) {
                                        dark->setReversMode(false);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (poisoned) {
                fadeEffectDokuStart();
            }
            if (faintedCount > 0) {
                heroMoveInitEvent();
                for (int j = 0; j < faintedCount; j++) {
                    Pokemon* pokemon = (Pokemon*)heroGetStatus(0, 3, (u16)faintedIdx[j]);
                    msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(pokemon));
                    winMsgOpenField(0xC37E, 1, 0);
                    winMsgCloseField(1);
                    actionFriendSet(pokemon, 7);
                }
                heroMoveTermEvent();
            }
        }
    }
}

static void cbTsureFriend(long, FootStepCounter counter, long amount) {
    if (counter != 1) {
        HeroMove.friendCounter += amount;
        while (HeroMove.friendCounter > 0x100) {
            for (int i = 0; i < 6; i++) {
                Pokemon* pokemon = (Pokemon*)heroGetStatus(0, 3, i);
                if (pokemon != 0 && pokemonCheckValid(pokemon)) {
                    actionFriendSet(pokemon, 5);
                }
            }
            HeroMove.friendCounter -= 0x100;
        }
    }
}

static void actionFriendSet(Pokemon* pokemon, u16 value) {
    u16 effect = getEquipItemEffect(pokemonBiosGetItemDataId(pokemon));
    pokemonGetFriendFormPokemonFriendFilterId(pokemon, effect, value);
}

static u16 getEquipItemEffect(u16 itemID) {
    u8* data = itemDataBiosGetPtr(itemID);
    if (data == 0) {
        return 0;
    }
    return itemDataBiosGetItemSoubiDataId(data);
}

static s32 abs(s8 v) {
    s32 sign = v >> 31;
    return (s8)((sign ^ v) - sign);
}

static void _getStickData(s8& a, s8& b, s8& c, s8& d) {
    s8 lx;
    s8 ly;
    s8 rx;
    s8 ry;
    if (HeroMove.stickOverride) {
        lx = HeroMove.stickData[0];
        ly = HeroMove.stickData[1];
        rx = HeroMove.stickData[2];
        ry = HeroMove.stickData[3];
    } else {
        lx = GSinputGetLeftStickXData(1, 1);
        ly = GSinputGetLeftStickYData(1, 1);
        rx = GSinputGetLeftStickXData(1, 0);
        ry = GSinputGetLeftStickYData(1, 0);
        if (lx == 0 && ly == 0) {
            if (GSinputButtonsPressed(1) & 8) {
                ly = -0x38;
            }
            if (GSinputButtonsPressed(1) & 4) {
                ly = 0x38;
            }
            if (GSinputButtonsPressed(1) & 1) {
                lx = -0x38;
            }
            if (GSinputButtonsPressed(1) & 2) {
                lx = 0x38;
            }
            rx = lx;
            ry = ly;
        }
        if (cameraGetType() != 6 && cameraGetType() != 5 && lx == 0 && ly == 0 && rx == 0 && ry == 0) {
            s8 x0 = GSinputGetRightStickXData(1, 1);
            int t0 = x0 < 0 ? -x0 : x0;
            if (t0 < 0x10) {
                x0 = 0;
            }
            s8 y0 = GSinputGetRightStickYData(1, 1);
            int t1 = y0 < 0 ? -y0 : y0;
            if (t1 < 0x10) {
                y0 = 0;
            }
            s8 x1 = GSinputGetRightStickXData(1, 0);
            int t2 = x1 < 0 ? -x1 : x1;
            if (t2 < 0x10) {
                x1 = 0;
            }
            s8 y1 = GSinputGetRightStickYData(1, 0);
            int t3 = y1 < 0 ? -y1 : y1;
            if (t3 < 0x10) {
                y1 = 0;
            }
            lx = (x0 * 0x38) / 44;
            ly = (y0 * 0x38) / 44;
            rx = (x1 * 0x38) / 44;
            ry = (y1 * 0x38) / 44;
        }
    }
    a = lx;
    b = ly;
    c = rx;
    d = ry;
    HeroMove.analog.calculate(a, b, c, d);
    if (gimmickBoxIsGimmickMoving()) {
        a = 0;
        b = 0;
        c = 0;
        d = 0;
    }
}

static void _setStickData(s8 a, s8 b, s8 c, s8 d) {
    HeroMove.stickOverride = 1;
    HeroMove.stickData[0] = a;
    HeroMove.stickData[1] = b;
    HeroMove.stickData[2] = c;
    HeroMove.stickData[3] = d;
}

static u8 isStoryMode() { return GSflagGet(0x30D) == 0; }

static void* _heroGetPeople(HEROMOVE_MEMBER member) {
    u32 group;
    u32 id;
    getResID(&group, &id, member);
    return peopleGet(group, id);
}

static f32 GSvecDistanceXZ(GSvec* p, GSvec* q) {
    GSvec a = *p;
    GSvec b = *q;
    a.y = 0.0f;
    b.y = 0.0f;
    return PSVECDistance(&a, &b);
}

void AnalogStickEmu::init() {
    stick[0] = 0;
    stick[1] = 0;
    stick[2] = 0;
    stick[3] = 0;
    accel = 0x14;
    decel = 10;
}

void AnalogStickEmu::calculate(s8& a, s8& b, s8& c, s8& d) {
    approach(stick[0], a);
    approach(stick[1], b);
    approach(stick[2], c);
    approach(stick[3], d);
    a = stick[0];
    b = stick[1];
    c = stick[2];
    d = stick[3];
}

extern "C" {
void heroMoveSetSmoothFloorLink(u8 v) { HeroMove.smoothFloorLink = v; }
}

extern "C" {
u8 heroMoveIsSmoothFloorLink(void) { return HeroMove.smoothFloorLink; }
}

static void _heroMoveInitialize(unsigned int groupID, FloorEnterMode mode) {
    HeroMove.started = 0;
    HeroMove.smoothFloorLink = 0;
    HeroMove.stickOverride = 0;
    if (mode == FLOOR_ENTER_MODE_3) {
        heroMoveSetLockFrame(4);
    }
}

static void _heroMoveFinalize(unsigned int groupID, FloorEnterMode mode) {
    HeroMove.started = 0;
    if (HeroMove.smoothFloorLink) {
        if (floorDataBiosGetFloorKind(floorDataBiosGetPtr(groupID)) == 1) {
            floorCreateThread(0x80, 0, 1, (void*)_closeHeroThread);
        }
    }
}

static const char* _heroMoveGetModuleName() { return "hero"; }

static void _closeHeroThread() { _heroMoveSlowStopFactor(4.0f, true); }
