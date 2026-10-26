#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
    GSvec();
    void set(f32 x, f32 y, f32 z);
    void clear();
};

struct GSmtx {
    f32 m[3][4];
    GSmtx();
    static GSmtx makeIdentity();
};

struct GSgfxColAu8 {
    u32 rgba;
};
struct GSgfxSize {
    u16 w;
    u16 h;
};
extern "C" void GSgfxVideoGetEFBSize(GSgfxSize*, s32);

enum GSgfxFogType { GSFOG_0 };

struct GSgfxLayer {
    u8 pad0[0x1678];
    s32 fogType;
    f32 fogStart;
    f32 fogEnd;
    u8 pad1[0x168c - 0x1684];
    GSgfxColAu8 fogColor;
    u8 pad2[0x16a4 - 0x1690];
    u16 fogRange;
    u8 fogRangeOn;
    u8 fogOn;
    u32 dirty16a8;
    u8 pad3[0x170c - 0x16ac];
    u32 dirty170c;
    u8 pad4[0x1760 - 0x1710];
    u32 dirty1760;
    u8 pad5[0x17c4 - 0x1764];
    u32 dirty17c4;
    inline void fog(bool on);
    inline void setFogRange(bool on, u16 range);
    inline void setFog(GSgfxFogType type, f32 start, f32 end, GSgfxColAu8 col);
};

struct HSD_Archive;
struct GSfloor_dd_ {
    u8 area;
    u8 kind;
    u16 floorID;
    u32 mapResID;
};

enum FloorStateMode { FSM_0, FSM_1, FSM_2 };
enum FloorEnterMode { FEM_0, FEM_1, FEM_2 };

struct FloorModuleInterface {
    void (*create)(unsigned int, FloorEnterMode);
    void (*initialize)(unsigned int, FloorEnterMode);
    void (*update)(unsigned int, FloorEnterMode);
    void (*unk0c)();
    void (*finalize)(unsigned int, FloorEnterMode);
    void (*free)(unsigned int, FloorEnterMode);
    const char* (*getModuleName)();
    void (*makeStateData)(FloorStateMode, void*, unsigned long);
    void (*restoreStateData)(FloorStateMode, void*, unsigned long);
    unsigned long (*getStateSize)(FloorStateMode);
    unsigned long (*getUID)();
};

typedef void (*FloorUniqueFn)(GSfloor_dd_*, u32);
struct FloorUniqueFunc {
    FloorUniqueFn pre;
    u32 unk4;
    FloorUniqueFn post;
};

struct FLOOR_CHANGE_INFO {
    u32 prevFloorID;
    u32 nextFloorID;
    u8 usePos;
    u32 nextPosIndex;
    GSvec pos;
    GSvec rot;
    u32 fadeIn;
    u32 fadeOut;
    u8 fadeFlag;
    u8 pad31[0x4c - 0x31];
    u32 retFloor;
    u32 retPrevFloor;
    u8 retArg;
    u8 retValid;
    u8 continueMode;
    u8 dispScriptInfo;
    u32 lightInfoA;
    u32 lightInfoB;
    u8 humanColision;
    u8 bgmFlag;
    u8 envFlag;
    FLOOR_CHANGE_INFO();
};

struct EvLogEntry {
    s8 type;
    u32 value;
};

struct StateEntry {
    u32 id;
    u32 kind;
    u8 data[0x6c];
};

struct StateCtx {
    StateEntry* cur;
    u32 count;
};

struct SceneData {
    void** models;
    void* camera;
    void** lights;
};

struct FogRange {
    u32 unk0;
    u16 range;
};
struct FogData {
    u32 mode;
    FogRange* range;
    f32 start;
    f32 end;
    GSgfxColAu8 color;
};

struct FloorTresureEntry {
    u8 type : 3;
    u8 pad0 : 5;
    u8 pad1;
    s16 angle;
    u16 floorID;
    u16 flagA;
    u16 flagB;
    u8 pad2[6];
    f32 x;
    f32 y;
    f32 z;
};

struct FloorDoorEntry {
    u8 pad0[7];
    u8 type;
    u8 pad1[4];
    u16 floorID;
    u16 flag;
    u8 pad2[8];
};

struct FloorCharInfo2 {
    u8 pad0 : 3;
    u8 neckTarget : 1;
    u8 pad1 : 4;
};

struct FloorPosEntry {
    s16 angle;
    s16 pad;
    f32 x;
    f32 y;
    f32 z;
};
struct FloorPosCount {
    u32 count;
};
struct FloorPosList {
    FloorPosCount* count;
    FloorPosEntry* entries;
};

struct HeroRef;
struct FLOOR_BGM_MASK;

namespace GSscript {
struct Tiga {
    u32 getNameToFuncId(const char*);
    void debugDump();
};
}
struct AppScript : GSscript::Tiga {
    void unload();
};
struct Hero {
    static Hero* getHeroPtr();
    void getRestertPos(GSvec*, s16&) const;
};
struct FIGHT_ENCOUNT {
    void setDirtyFlag(bool);
};
struct FloorBgmMask {
    void initialize();
    void finalize();
    void update(f32);
};

typedef void (*FloorMapCB)(unsigned long, unsigned long, unsigned long, void*, void*);
typedef BOOL (*FloorUnloadFunc)(void*, u32, u32);

AppScript* floorGetCurentScript();
void EvlogPrint();
void EvlogSet(s8, u32);

extern "C" {
void floorMapResourceDataIterate(FloorMapCB, void*);
u32 fn_8011E5D8();
u32 fn_8011E650();
void floorUnblockModule(s32);
void floorBlockModule(s32);
void GSmodelPushState(void*, void*);
void GSmodelPopState(void*, void*);
void GSlightPushState(void*, void*);
void GSlightPopState(void*, void*);
u32 soundGetBGMID();
u32 soundGetEnvID();
u32 soundGetVolume(u32);
void soundOpenPlay(s32, s32, s32);
void soundOpenPlayEnv(s32, s32, s32);
void soundSetVolumeID(s32, s32, s32);
void floorReleaseOffscreen();
void* memset(void*, int, unsigned long);
u32 floorDataBiosGetCurrentPtr();
GSfloor_dd_* floorDataBiosGetPtr(u32);
u32 floorDataBiosGetMapResID(void*);
u32 floorGetCurrentGroupID();
void* GSresGetResource(u32, u32);
void* HSD_ArchiveGetPublicAddress(void*, const char*);
u32 floorReadMakeModelResID(u32);
u32 floorReadMakeLightResID(u32);
u32 floorReadMakeCameraResID(u32);
u32 floorReadMakeFogResID(u32);
void GSmodelSetVisibility(void*, bool);
void GSlightSetActive(void*, bool);
u32 pokecoloGetLanguage();
s32 pokecoloGetRomVersion();
u8 pokecoloIsDVDETHMode();
s32 pokecoloGetCountryCode();
u8 floorDataBiosGetFloorKind(void*);
void cameraSetType(s32);
void GSgfxVideoSetClearColor(GSgfxColAu8);
s32 GSfsysGetStatus(u32);
void GSfsysReadWait(u32);
void GSfsysReadIDWait(u32, u32);
void GSfsysFree(u32);
void GSfsysPreRead(u32);
void GSresFreeGroup(u32);
void GSthreadSwitch();
s32 GSmemGetCurrentHeap();
void GSmemGetHeapFreeSize(s32, u32*, u32*);
void GSresFreeGroup2();
u32 heroMoveGetKenObjID();
u32 heroGetObjID(s32);
void* floorCharacterBiosGetCurrentPtr(u32);
void* floorCharacterBiosGetPeopleInfoPtr(void*);
u32 peopleInfoBiosGetModelResID(void*);
u32 peopleOpen(u32, u32, u32);
u32 peopleGetHumanID(u32, u32);
void GSlogWrite(const char*, ...);
s32 floorGetCurentScriptMode();
u8 floorIsContinueMode();
u32 GSfloorGetCurrentFloorGroupID();
u8 floorExecScriptIntegerByName(const char*, s32, s32, s32, s32);
u8 floorExecScriptInteger(u32, s32, s32, s32, s32);
u8 floorExecScriptIntegerThread(u32, s32, s32, s32, s32);
void fadeCheck(s32);
extern u8 pokecoloWaitVSync;
void GSgfxVideoSetLockFrameRate(s32);
void FloorModuleInterface_clear(FloorModuleInterface*);
s32 floorRegisterModule(s32, s32, FloorModuleInterface*);
s32 floorRegisterScriptModule(s32, s32, u32, u32, u32);
void GSfloorOpen(u32);
void GSfloorStart(u32);
void floorOffscreenMainInit();
void floorCharacterBiosInitGlobalCharacter();
u32 floorDataBiosGetGroupID(void*);
u32 floorDataBiosGetPreFunc(void*);
u32 floorDataBiosGetMainFunc(void*);
u32 floorDataBiosGetPostFunc(void*);
u32 floorGetNextChangeID();
void* floorSound_getBgmMaskObj();
void peopleAllClose(s32);
void menuCloseFloor();
void scriptGlowEnd();
void mailMainReceiveTerminate();
f32 timeGetLastFrameSec();
u8 floorIsDispScriptInfo();
void msgctrlInitValue();
void scriptModelInit();
void* fightEncountGetStrObj();
void floorInitOffscreen(void*);
void* effectViewerGetFloorModule();
void* fightGetFloorModule();
void menuPocketClearItemScript();
void floorSound_playEnvSound(s32);
void floorSound_playSound();
void battleCameraStop();
void battleGridReset();
void wazaSequenceSysRelease();
void wazaSequenceSysUpdate();
void battleCameraUpdate();
void cameraUpdate();
void wazaSequenceSysInit();
void wazaSequenceSysInitExtras();
void battleCameraInit(void*);
void* GSresGetResourceAllGroup(u32);
void* floorReadResourceID(u32, u32);
extern u32* floor_tresure_list_number;
extern u8* floor_tresure_list;
extern u32* floor_door_list_number;
extern u8* floor_door_list;
u8 floorIsPop();
u8 floorIsPush();
u8 floorIsFloorPushed();
void* peopleGet(u32, u32);
void peopleSetPos(u32, u32, GSvec*);
void peopleSetRot(u32, u32, GSvec*);
void peopleAddCollision(u32, u32);
void peopleSetFlagOn(u32, u32, u32);
void peopleSetFlagOff(u32, u32, u32);
void peopleSetDisp(u32, u32, u32);
void peopleManualAnimation(u32, u32);
void peopleBiosSetTresureID(void*, u16);
void GSmodelClearShadowFlags(void*, u32);
u8 GSflagTest(s32);
void GSflagClear(s32);
void floorEventCtrlTresure(u32, u32, u8);
s32 floorEventCtrlDoor(s32, s32, u8);
void peopleExecMoveScript(u32, u32, u32, u32, u32);
u32 floorDataBiosGetCharNum(void*);
u8 floorCharacterBiosGetLoadInit(void*);
u32 peopleGetMoveSctID(u32, u32);
void floorCharacterBiosGetPos(void*, GSvec*);
void floorCharacterBiosGetRot(void*, GSvec*);
u32 floorCharacterBiosGetVisibility(void*);
u32 floorCharacterBiosGetIsHit(void*);
u8 floorCharacterBiosGetMoveType(void*);
u8 floorCharacterBiosGetTalkStartType(void*);
u8 floorCharacterBiosGetTalkEndType(void*);
void peopleSetCollision(u32, u32, u32);
void peopleStartWalkRandom(u32, u32, f32);
void peopleStartRotRandom(u32, u32, f32, f32);
void peopleMoveNeckTargetHero(u32, u32, f32);
void* floorOpenObject(u32);
void GSresFreeResource(u32, u32);
void GSresRegisterResource(void*, u32, u32, FloorUnloadFunc);
u8 GSmodelCanAnimate(void*);
u8 GSmodelCanTexAnimate(void*);
void GSmodelSetBoundCheck(void*, bool);
void GSmodelSetRenderLayer(void*, s32, s32*);
u32 GSfloorGetCurrent();
void GSmodelLinkTexAnimToAnim(void*, s32);
void GSmodelSetTexAnimRate(void*, f32);
u8 GSlightCanAnimate(void*);
void GSlightSetAnimIndex(void*, s32);
void GSlightSetAnimRate(void*, f32);
void GSlightStartAnimation(void*);
void cameraSetGScamera(void*);
u32 floorDataBiosGetSecondaryRenderNum(void*);
u32 floorDataBiosGetSecondaryRenderID(void*, u32);
u32 floorGetCurrent();
void GSfloorChange(u32);
u8 floorCheckAnywaySaveData();
u32 floorDataBiosGetFileGroupID(void*);
void GSsndPlayNow(s32);
void floorChange(u32);
u32 floorDataBiosGetPlaceName(void*);
FloorPosList* floorDataBiosGetPosListPtr(void*);
u8 floorDataBiosGetArea(void*);
void floorUpdateFieldCamera();
void floorUpdateOffscreen();
void GScolsys2Draw(GSmtx*);
void GScolsys2HumanDispColision();
s32 heroMoveInit(GSvec*, GSvec*);
f32 cameraGetDistance();
void cameraSetDistance(f32);
void cameraSetTarget(s32, s32);
void cameraSetTargetOfs(GSvec*);
void GSinputResetLeftSmoothing(s32, s32, s32);
void GSinputResetRightSmoothing(s32, s32, s32);
void GSmodelFree(void*);
void* GSmodelLoad(void*, void*);
void GSmodelSetAnimIndex(void*, s32);
void GSmodelSetAnimRate(void*, f32);
void GSmodelStartAnimation(void*);
void GSmodelSetTexAnimIndex(void*, s32);
void GSmodelStartTexAnimation(void*);
s32 gamedatasaveGetStatus(s32, s32);
void* OSGetArenaLo();
void OSSetArenaLo(void*);
s32 GSmemCreateHeap(void*, void*);
s32 dbgMenuGetLayerID();
void GSprint(s32, s32, s32, u32, const char*, ...);
void floorLinkWithSE(u32, u32, u32);
void PSMTXIdentity(GSmtx*);
void floorClearReturnPoint();
GSgfxLayer* GSgfxLayerFindByID(s32);
void GSmodelSetShadowToCameraHeightCheck(bool);
void GSmodelSetShadowBoundExpansion(f32);
void GSmodelSetShadowDistLimits(f32, f32);
void GSmodelSetShadowCutoffDist(f32);
void GSmodelSetShadowTextureSize(s32, s32);
u32 floorDataBiosGetLensFlareResID(void*);
u32 floorDataBiosGetSunResID(void*);
void GSlensFlareSetVisible(void*, bool);
void GSlensFlareSetSunPosition(void*, GSvec*);
void GSmodelGetPosition(void*, GSvec*);
void* GScameraGetActiveCamera();
void GScameraGetPerspective(void*, f32*, f32*, f32*, f32*);
void GScameraSetPerspective(void*, f32, f32, f32, f32);
s32 floorDataBiosModelIDGetFogState(u32);
void GSmodelSetFogState(void*, s32, s32);
}

static const char* _floorGetModuleName();
static u32 _floorGetUID();
static u32 _floorGetStateSize(FloorStateMode);
static void _floorRestoreStateData(FloorStateMode, void*, unsigned long);
static void _floorMakeStateData(FloorStateMode, void*, unsigned long);
static void _floorMapPopCB(unsigned long, unsigned long, unsigned long, void*, void*);
static void _floorMapPushCB(unsigned long, unsigned long, unsigned long, void*, void*);
static void _floorMapGetResourceCounts(int*, int*);
static void _floorMapGetCountCB(unsigned long, unsigned long, unsigned long, void*, void*);
static void _floorMapSetDispCB(unsigned long, unsigned long, unsigned long, void*, void*);
static void _floorFsysFree(unsigned long);
static void _floorCreateCommon(unsigned int, FloorEnterMode);
static void _floorUniqueFinalize(unsigned int, FloorEnterMode);
static void _floorUniqueUpdate();
static void _floorUniqueInitialize(unsigned int, FloorEnterMode);
static void _floorFreeCommon(unsigned int, FloorEnterMode);
static void _floorFinalizeCommon(unsigned int, FloorEnterMode);
static void _floorUpdateCommon(unsigned int, FloorEnterMode);
static void _floorInitializeCommon(unsigned int, FloorEnterMode);
static void _floorReleaseWazaSequence(GSfloor_dd_*);
static void _floorUpdateWazaSequence(GSfloor_dd_*);
static void _floorInitShadow(GSfloor_dd_*);
static void _floorInitScene(GSfloor_dd_*);
static void _floorInitMapFog(GSfloor_dd_*);
static void _floorInitTresure(GSfloor_dd_*);
static void _floorInitDoor(GSfloor_dd_*);
static void _floorInitCharacters(GSfloor_dd_*);
static void _floorInitCharactor(unsigned long, unsigned long, unsigned long);
static void _floorSetInitPosition();
static void _floorClearFlag();
static void _floorFinalize(unsigned int, FloorEnterMode);
static void _floorUpdate(unsigned int, FloorEnterMode);
static void _floorInitialize(unsigned int, FloorEnterMode);
static const char* _floorGetUniqueModuleName();
static const char* _floorGetMenuModuleName();
static const char* _floorGetFieldModuleName();
static BOOL _floorUnloadModel(void*, unsigned long, unsigned long);

static FloorModuleInterface _floorModuleCommon;
static FloorModuleInterface _floorModuleField;
static FloorModuleInterface _floorModuleWazaViewer;
static FloorModuleInterface _floorModuleUniqueFunc;
static FloorUniqueFunc _floorUniqueFunc;
static FLOOR_CHANGE_INFO _floorChangeInfo;

static s32 _hModuleCommon;
static s32 _hModuleField;
static s32 _hModuleWazaViewer;
static s32 _hModuleUniqueFunc;
static s32 _hModuleFloorScript;
static void (*_floorUniqueFuncThread)();
static s32 _floorLocalHeap;
static s8 evlog_start;

static EvLogEntry EvLog[10] = {
    {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0},
};

extern "C" {
void floorGetLightInfo(u32* a, u32* b);
void floorSetLightInfo(u32 a, u32 b);
void floorUnblockMainScript();
void floorBlockMainScript();
void floorMapResourceDataIterate(FloorMapCB cb, void* ctx);
void floorMapSetDisp(u8 disp);
u8 floorGetHumanColision();
void floorSetHumanColision(u8 v);
u8 floorCheckFightKind(u32 id);
u32 fn_8011E5D8();
u32 fn_8011E650();
u8 floorReadCharacter(u32 group, u32 id, u32 modelRes);
void floorExecSoundScript();
void floorCheckFade();
void floorExecFadeOut();
void floorExecFadeIn();
void flooSetFrameRate();
void floorSetFadeScript(u32 out, u32 in);
void floorInit();
void floorInitWazaSequence(u32 id);
void floorInitMap(u32 group, u32 mapRes);
void floorChangePos(u32 floorID, s16 angle, f32 x, f32 y, f32 z);
void floorLink(u32 floorID, u32 posIndex);
void floorLinkWithSE(u32 floorID, u32 posIndex, u32 se);
u32 floorGetNextPosIndex();
u32 floorGetNextFloorID();
u32 floorGetPrevFloorID();
void floorSetPrevFloorID(u32 id);
u32 floorGetPlaceName(u32 id);
void* floorOpenModel(u32, u32 id);
void* floorOpenObject(u32 id);
u32 floorGetCurrentGroupID();
void* floorGetResource(u32 id, u32 resID);
void floorReturnSavePoint();
u8 floorIsDispScriptInfo();
void floorSetDispScriptInfo(u8 v);
u8 floorIsContinueMode();
void floorSetContinueMode(u8 v);
void floorSetFloorChangeInfo(u32 floorID, u32 posIndex);
void floorClearReturnPoint();
s32 floorGetLocalHeapHandle();
u8 floorCreateLocalHeap();
}

#pragma dont_inline on
inline void GSvec::clear() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

inline void GSvec::set(f32 _x, f32 _y, f32 _z) {
    x = _x;
    y = _y;
    z = _z;
}

FLOOR_CHANGE_INFO::FLOOR_CHANGE_INFO() {}

void EvlogSet(s8 type, u32 value) {
    EvLog[evlog_start].type = type;
    EvLog[evlog_start++].value = value;
    evlog_start = evlog_start % 10;
}

void EvlogPrint() {
    u8* res = (u8*)GSresGetResource(0, 2);
    if (res != 0 && *res != 0) {
        s32 i;
        s32 y = 30;
        for (i = 0; i < 10; y += 12, i++) {
            EvLogEntry* e = &EvLog[(evlog_start + i) % 10];
            switch (e->type) {
            case 1:
                GSprint(dbgMenuGetLayerID(), 30, y, 0x8080FFFF, "PASS EVENT = %d", e->value);
                break;
            case 2:
                GSprint(dbgMenuGetLayerID(), 30, y, 0x8080FFFF, "TOUCH EVENT = %d", e->value);
                break;
            case 3:
                GSprint(dbgMenuGetLayerID(), 30, y, 0x8080FFFF, "CHECK EVENT = %d", e->value);
                break;
            }
        }
    }
}

u8 floorCreateLocalHeap() {
    u8* lo = (u8*)OSGetArenaLo();
    u8* hi = lo + 0x18000;
    _floorLocalHeap = GSmemCreateHeap(lo, hi);
    if (_floorLocalHeap == -1) {
        return 0;
    }
    OSSetArenaLo(hi);
    return 1;
}

s32 floorGetLocalHeapHandle() {
    return _floorLocalHeap;
}

void floorClearReturnPoint() {
    _floorChangeInfo.retValid = 0;
}

void floorSetFloorChangeInfo(u32 floorID, u32 posIndex) {
    if (floorID != 0) {
        _floorChangeInfo.prevFloorID = GSfloorGetCurrent();
        _floorChangeInfo.nextFloorID = floorID;
        _floorChangeInfo.usePos = 1;
        _floorChangeInfo.nextPosIndex = posIndex;
    }
}

void floorSetContinueMode(u8 v) {
    _floorChangeInfo.continueMode = v;
}

u8 floorIsContinueMode() {
    return _floorChangeInfo.continueMode;
}

void floorSetDispScriptInfo(u8 v) {
    _floorChangeInfo.dispScriptInfo = v;
}

u8 floorIsDispScriptInfo() {
    return _floorChangeInfo.dispScriptInfo;
}

void floorReturnSavePoint() {
    u32 a;
    u32 b;
    u8 c;
    if (_floorChangeInfo.retValid) {
        a = _floorChangeInfo.retFloor;
        b = _floorChangeInfo.retPrevFloor;
        c = _floorChangeInfo.retArg;
    } else {
        a = gamedatasaveGetStatus(0, 5);
        b = gamedatasaveGetStatus(0, 7);
        c = gamedatasaveGetStatus(0, 8);
    }
    floorLinkWithSE(a, c, 0);
    _floorChangeInfo.prevFloorID = b;
    floorClearReturnPoint();
}

void* floorGetResource(u32 id, u32 resID) {
    GSfloor_dd_* floor = floorDataBiosGetPtr(id);
    if (floor == 0) {
        return 0;
    }
    return GSresGetResource(floorDataBiosGetGroupID(floor), resID);
}

u32 floorGetCurrentGroupID() {
    return floorDataBiosGetGroupID((void*)floorDataBiosGetCurrentPtr());
}

void* floorOpenObject(u32 id) {
    u8 isScene = 0;
    switch (id) {
    case 3:
    case 0x64:
        id = (u32)GSresGetResource(0, 0x64);
        break;
    case 4:
    case 0x65:
        id = (u32)GSresGetResource(0, 0x65);
        break;
    default:
        if (((id >> 9) & 0x3F) == 2) {
            isScene = 1;
        }
        break;
    }
    if (id == 0) {
        GSlogWrite("Error!! %s: objID is zero\n", __FUNCTION__);
        return 0;
    }
    void* res = GSresGetResourceAllGroup(id);
    if (res == 0) {
        res = floorReadResourceID(0x9A, id);
    }
    if (res == 0) {
        return 0;
    }
    if (isScene) {
        if (res == 0) {
            GSlogWrite("%s: got NULL pointer archive\n", __FUNCTION__);
            GSlogWrite("objID : %08x\n", id);
            while (1) {
                GSthreadSwitch();
            }
        }
        SceneData* scene = (SceneData*)HSD_ArchiveGetPublicAddress(res, "scene_data");
        if (scene == 0) {
            GSlogWrite("%s: got NULL pointer scene descriptor\n", __FUNCTION__);
            GSlogWrite("objID : %08x\n", id);
            while (1) {
                GSthreadSwitch();
            }
        }
        res = scene->models[0];
        if (res == 0) {
            GSlogWrite("%s: couldn't load model\n", __FUNCTION__);
            GSlogWrite("objID : %d\n", id);
            while (1) {
                GSthreadSwitch();
            }
        }
    }
    void* model = GSmodelLoad(res, 0);
    if (model == 0) {
        GSlogWrite("Error! %s: couldn't load model %d\n", __FUNCTION__);
        GSlogWrite("モデルの初期化に失敗\n");
    } else {
        GSmodelSetVisibility(model, true);
        if (GSmodelCanAnimate(model)) {
            GSmodelSetAnimIndex(model, 0);
            GSmodelSetAnimRate(model, 0.5f);
            GSmodelStartAnimation(model);
        }
        if (GSmodelCanTexAnimate(model)) {
            GSmodelSetTexAnimIndex(model, 0);
            GSmodelSetTexAnimRate(model, 0.5f);
            GSmodelStartTexAnimation(model);
        }
    }
    return model;
}

void* floorOpenModel(u32, u32 id) {
    return floorOpenObject(id);
}

static BOOL _floorUnloadModel(void* model, unsigned long, unsigned long) {
    GSmodelFree(model);
    return TRUE;
}

static const char* _floorGetFieldModuleName() {
    return "floorFiledModule";
}

static const char* _floorGetMenuModuleName() {
    return "floorMenuModule";
}

static const char* _floorGetUniqueModuleName() {
    return "floorUniqueModule";
}

static void _floorInitialize(unsigned int id, FloorEnterMode mode) {
    GSfloor_dd_* floor = floorDataBiosGetPtr(id);
    heroMoveInit(&_floorChangeInfo.pos, &_floorChangeInfo.rot);
    if (mode != 2) {
        _floorInitCharacters(floor);
        _floorInitDoor(floor);
        _floorInitTresure(floor);
        GSvec ofs;
        ofs.set(0.0f, 14.0f, 0.0f);
        cameraSetType(0);
        if (cameraGetDistance() < 0.00001f && cameraGetDistance() > -0.00001f) {
            cameraSetDistance(89.5f);
        }
        cameraSetTarget(0, 100);
        cameraSetTargetOfs(&ofs);
    }
    cameraUpdate();
    GSinputResetLeftSmoothing(1, 0, 0);
    GSinputResetRightSmoothing(1, 0, 0);
    if (mode == 2) {
        floorExecScriptIntegerByName("pushpop_preprocess", GSfloorGetCurrentFloorGroupID(), 0, 0, 0);
    }
}

static void _floorUpdate(unsigned int id, FloorEnterMode mode) {
    u8 drew = 0;
    GSmtx m;
    GSmtx::makeIdentity();
    floorUpdateFieldCamera();
    floorUpdateOffscreen();
    u8* res = (u8*)GSresGetResource(0, 2);
    if (res != 0 && *res != 0) {
        EvlogPrint();
        GScolsys2Draw(&m);
        drew = 1;
    }
    if (floorGetHumanColision() && !drew) {
        GScolsys2HumanDispColision();
    }
}

static void _floorFinalize(unsigned int id, FloorEnterMode mode) {
    switch (mode) {
    case 1:
        break;
    }
}

static void _floorClearFlag() {
    u8 areaA = 0;
    u8 areaB = 0;
    if (floorIsPop() == 1) {
        return;
    }
    if (floorIsPush() == 1) {
        return;
    }
    if (floorIsFloorPushed()) {
        return;
    }
    if (floorIsContinueMode()) {
        return;
    }
    if (_floorChangeInfo.prevFloorID == 0x384) {
        return;
    }
    GSflagClear(1);
    GSfloor_dd_* prev = floorDataBiosGetPtr(_floorChangeInfo.prevFloorID);
    if (prev != 0) {
        areaA = floorDataBiosGetArea(prev);
    }
    if (prev->kind == 2) {
        return;
    }
    GSfloor_dd_* next = floorDataBiosGetPtr(_floorChangeInfo.nextFloorID);
    if (next != 0) {
        areaB = floorDataBiosGetArea(next);
    }
    if (areaA != areaB) {
        GSflagClear(2);
    }
}

static void _floorSetInitPosition() {
    FloorPosEntry* entry = 0;
    if (_floorChangeInfo.usePos != 0) {
        FloorPosList* list = floorDataBiosGetPosListPtr((void*)floorDataBiosGetCurrentPtr());
        if (list != 0) {
            if (_floorChangeInfo.nextPosIndex < list->count->count) {
                entry = list->entries + _floorChangeInfo.nextPosIndex;
            }
        }
        if (entry != 0) {
            _floorChangeInfo.pos.set(entry->x, entry->y, entry->z);
            _floorChangeInfo.rot.set(0.0f, 0.017453292f * entry->angle, 0.0f);
        } else {
            _floorChangeInfo.pos.clear();
            _floorChangeInfo.rot.clear();
        }
        _floorChangeInfo.usePos = 0;
    }
}

u32 floorGetPlaceName(u32 id) {
    switch (id) {
    case 0xFF:
    case 0x258:
    case 0x259:
        return 0;
    }
    GSfloor_dd_* floor = floorDataBiosGetPtr(id);
    if (floor == 0) {
        return 0;
    }
    return floorDataBiosGetPlaceName(floor);
}

void floorSetPrevFloorID(u32 id) {
    _floorChangeInfo.prevFloorID = id;
}

u32 floorGetPrevFloorID() {
    return _floorChangeInfo.prevFloorID;
}

u32 floorGetNextFloorID() {
    return _floorChangeInfo.nextFloorID;
}

u32 floorGetNextPosIndex() {
    return _floorChangeInfo.nextPosIndex;
}

void floorLinkWithSE(u32 floorID, u32 posIndex, u32 se) {
    GSfloor_dd_* next;
    Hero* hero;
    GSfloor_dd_* cur;
    if (floorID != 0) {
        _floorChangeInfo.prevFloorID = GSfloorGetCurrent();
        _floorChangeInfo.nextFloorID = floorID;
        if (floorIsContinueMode() && floorCheckAnywaySaveData()) {
            hero = Hero::getHeroPtr();
            GSvec p;
            s16 ang;
            hero->getRestertPos(&p, ang);
            _floorChangeInfo.pos.set(p.x, p.y, p.z);
            _floorChangeInfo.rot.set(0.0f, 0.017453292f * ang, 0.0f);
            _floorChangeInfo.usePos = 0;
        } else {
            _floorChangeInfo.usePos = 1;
            _floorChangeInfo.nextPosIndex = posIndex;
        }
        cur = floorDataBiosGetPtr(GSfloorGetCurrent());
        next = floorDataBiosGetPtr(floorID);
        if (floorDataBiosGetFileGroupID(next) != floorDataBiosGetFileGroupID(cur)) {
            GSfsysPreRead(floorDataBiosGetFileGroupID(next));
        }
        u32 snd;
        switch (se) {
        case 0:
            snd = 0;
            break;
        case 1:
        default:
            snd = 0x1C;
            break;
        }
        if (snd != 0) {
            GSsndPlayNow(snd);
        }
        floorChange(floorID);
    }
}

void floorLink(u32 floorID, u32 posIndex) {
    floorLinkWithSE(floorID, posIndex, 0);
}

void floorChangePos(u32 floorID, s16 angle, f32 x, f32 y, f32 z) {
    if (floorID != 0) {
        _floorChangeInfo.pos.set(x, y, z);
        _floorChangeInfo.rot.set(0.0f, 0.017453292f * angle, 0.0f);
        _floorChangeInfo.prevFloorID = GSfloorGetCurrent();
        _floorChangeInfo.nextFloorID = floorID;
        _floorChangeInfo.usePos = 0;
        GSfloorChange(floorID);
    }
}

void floorInitMap(u32 group, u32 mapRes) {
    s32 layerA[1] = {0};
    s32 layerB[1] = {4};
    u32 modelIdx = 0;
    u32 lightIdx = 0;
    if (mapRes != 0) {
        SceneData* scene = (SceneData*)HSD_ArchiveGetPublicAddress(GSresGetResource(group, mapRes), "scene_data");
        if (scene != 0) {
            if (scene->models != 0) {
                u32 base = floorReadMakeModelResID(mapRes);
                for (int i = 0; scene->models[i] != 0; i++, modelIdx++) {
                    u32 id = base | modelIdx;
                    void* model = floorOpenObject(id);
                    if (model == 0) {
                        GSlogWrite("Error! %s: couldn't load model %d\n", __FUNCTION__, modelIdx);
                        GSlogWrite("マップモデルの初期化に失敗\n");
                        continue;
                    }
                    GSresFreeResource(group, id);
                    GSresRegisterResource(model, group, id, _floorUnloadModel);
                    GSmodelSetVisibility(model, false);
                    if (!GSmodelCanAnimate(model)) {
                        GSmodelSetBoundCheck(model, true);
                    }
                    GSmodelSetRenderLayer(model, 1, layerA);
                    if (pokecoloGetCountryCode() == 1) {
                        switch (GSfloorGetCurrent()) {
                        case 0x3A:
                        case 0x3B:
                        case 0x5E:
                        case 0x5F:
                        case 0x64:
                        case 0x69:
                        case 0x6A:
                        case 0x74:
                        case 0x7D:
                        case 0x7E:
                        case 0x84:
                        case 0x1F6:
                        case 0x1FC:
                        case 0x20A:
                            if (GSmodelCanAnimate(model)) {
                                GSmodelLinkTexAnimToAnim(model, 0);
                                GSmodelSetTexAnimRate(model, 0.35f);
                            }
                            break;
                        }
                    }
                }
            }
            if (scene->lights != 0) {
                u32 base = floorReadMakeLightResID(mapRes);
                for (int i = 0; scene->lights[i] != 0; i++, lightIdx++) {
                    void* light = GSresGetResource(group, base | lightIdx);
                    if (light != 0) {
                        GSlightSetActive(light, true);
                        if (GSlightCanAnimate(light)) {
                            GSlightSetAnimIndex(light, 0);
                            GSlightSetAnimRate(light, 0.5f);
                            GSlightStartAnimation(light);
                        }
                    }
                }
            }
            u32 camRes = floorReadMakeCameraResID(mapRes);
            void* cam = GSresGetResource(group, camRes);
            if (cam != 0) {
                cameraSetGScamera(cam);
            }
            u32 j;
            GSfloor_dd_* floor = floorDataBiosGetPtr(floorGetCurrent());
            if (floor != 0) {
                u32 num = floorDataBiosGetSecondaryRenderNum(floor);
                for (j = 0; j < num; j++) {
                    u32 rid = floorDataBiosGetSecondaryRenderID(floor, j);
                    if (rid != 0) {
                        GSmodelSetRenderLayer(GSresGetResource(group, rid), 1, layerB);
                    }
                }
            }
        }
    }
}

static void _floorInitCharactor(unsigned long group, unsigned long id, unsigned long obj) {
    GSvec a;
    GSvec b;
    u32 sct;
    FloorCharInfo2* ci = (FloorCharInfo2*)floorCharacterBiosGetCurrentPtr(id);
    sct = peopleGetMoveSctID(group, id);
    if (!floorIsContinueMode()) {
        peopleExecMoveScript(group, id, sct, obj, 0);
    }
    peopleSetFlagOn(group, id, 4);
    peopleSetFlagOn(group, id, 8);
    floorCharacterBiosGetPos(ci, &a);
    peopleSetPos(group, id, &a);
    floorCharacterBiosGetRot(ci, &b);
    peopleSetRot(group, id, &b);
    peopleAddCollision(group, id);
    peopleSetDisp(group, id, floorCharacterBiosGetVisibility(ci));
    peopleSetCollision(group, id, floorCharacterBiosGetIsHit(ci));
    switch (floorCharacterBiosGetMoveType(ci)) {
    case 0:
    case 1:
        break;
    case 2:
        peopleStartWalkRandom(group, id, 15.0f);
        break;
    case 3:
        peopleStartRotRandom(group, id, 5.0f, 3.0f);
        break;
    }
    switch (floorCharacterBiosGetTalkStartType(ci)) {
    case 0:
        break;
    case 1:
        peopleSetFlagOn(group, id, 0x10);
        break;
    case 2:
        peopleSetFlagOn(group, id, 0x20);
        break;
    }
    switch (floorCharacterBiosGetTalkEndType(ci)) {
    case 0:
        peopleSetFlagOff(group, id, 0x40);
        break;
    case 1:
        peopleSetFlagOn(group, id, 0x40);
        break;
    }
    if (ci->neckTarget) {
        peopleMoveNeckTargetHero(group, id, 1.0f);
    }
}

static void _floorInitCharacters(GSfloor_dd_* floor) {
    GSvec a;
    GSvec b;
    u32 group = floorDataBiosGetGroupID(floor);
    u32 num = floorDataBiosGetCharNum(floor);
    for (u32 i = 0; i < num; i++) {
        void* ci = floorCharacterBiosGetCurrentPtr(i);
        u32 res = peopleInfoBiosGetModelResID(floorCharacterBiosGetPeopleInfoPtr(ci));
        if (floorCharacterBiosGetLoadInit(ci)) {
            u32 obj;
            if (floorIsPop() == 0) {
                obj = peopleOpen(group, i, res);
            } else {
                obj = peopleGetHumanID(group, i);
            }
            if (obj == 0) {
                GSlogWrite("Error! [%s] 人の初期化に失敗\n", __FUNCTION__);
            } else if (floorIsPop() != 1) {
                _floorInitCharactor(group, i, obj);
            }
        }
    }
}

static void _floorInitDoor(GSfloor_dd_* floor) {
    u32 off;
    u32 i;
    for (i = 0, off = 0; i < *floor_door_list_number; off += sizeof(FloorDoorEntry), i++) {
        FloorDoorEntry* d = (FloorDoorEntry*)((u8*)floor_door_list + off);
        if (d->floorID == floor->floorID) {
            switch (d->type) {
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
                if (GSflagTest(d->flag)) {
                    floorEventCtrlDoor(floor->floorID, i, 1);
                } else {
                    floorEventCtrlDoor(floor->floorID, i, 3);
                }
                break;
            case 2:
                floorEventCtrlDoor(floor->floorID, i, 3);
                break;
            }
        }
    }
}

static void _floorInitTresure(GSfloor_dd_* floor) {
    GSvec pos;
    GSvec rot;
    u32 off;
    FloorTresureEntry* t;
    u32 i;
    u32 group;
    u32 id;
    u32 res;
    u32 count = 0;
    group = floorDataBiosGetGroupID(floor);
    for (i = 0, off = 0; i < *floor_tresure_list_number; off += sizeof(FloorTresureEntry), i++) {
        t = (FloorTresureEntry*)((u8*)floor_tresure_list + off);
        if (t->floorID == floor->floorID) {
            switch (t->type) {
            case 1:
                res = 0x2F80400;
                break;
            case 2:
                res = 0x2F90400;
                break;
            case 3:
                res = 0x2FA0400;
                break;
            }
            id = (count++) | 0x7FFF0000;
            u32 obj;
            if (floorIsPop() == 0) {
                obj = peopleOpen(group, id, res);
            } else {
                obj = peopleGetHumanID(group, id);
            }
            if (obj != 0 && floorIsPop() != 1) {
                void* people = peopleGet(group, id);
                pos.set(t->x, t->y, t->z);
                peopleSetPos(group, id, &pos);
                rot.set(0.0f, 0.017453292f * t->angle, 0.0f);
                peopleSetRot(group, id, &rot);
                peopleAddCollision(group, id);
                peopleSetFlagOn(group, id, 4);
                peopleSetDisp(group, id, true);
                peopleManualAnimation(group, id);
                if (people != 0) {
                    peopleBiosSetTresureID(people, (u16)i);
                }
                if (t->type == 2) {
                    void* model = GSresGetResource(group, id);
                    if (model != 0) {
                        GSmodelClearShadowFlags(model, 1);
                    }
                }
                if (t->flagA != 0) {
                    if (GSflagTest(t->flagA)) {
                        floorEventCtrlTresure(group, id, 0);
                    } else {
                        floorEventCtrlTresure(group, id, 1);
                        if (t->flagB != 0) {
                            if (!GSflagTest(t->flagB)) {
                                peopleSetDisp(group, id, false);
                            }
                            peopleExecMoveScript(group, id, 0x596000B, t->flagA, t->flagB);
                        }
                    }
                }
            }
        }
    }
}

static void _floorInitMapFog(GSfloor_dd_* floor) {
    u32 id;
    u32 idx;
    FogRange* range;
    GSgfxColAu8 zero = {0};
    u32 group;
    u32 mapRes;
    FogData* fog = 0;
    GSgfxLayer* layerA;
    GSgfxLayer* layerB;
    switch (floorDataBiosGetFloorKind(floor)) {
    case 3:
    case 5:
    case 6:
        break;
    case 1:
    case 2:
    case 4: {
        group = floorDataBiosGetGroupID(floor);
        mapRes = floorDataBiosGetMapResID(floor);
        u32 fogRes = floorReadMakeFogResID(mapRes);
        if (fogRes != 0) {
            fog = (FogData*)GSresGetResource(group, fogRes);
        }
        layerA = GSgfxLayerFindByID(0);
        layerB = GSgfxLayerFindByID(2);
        if (fog != 0) {
            GSgfxFogType type;
            switch (fog->mode) {
            case 2:
            case 10:
                type = (GSgfxFogType)2;
                break;
            case 4:
            case 12:
                type = (GSgfxFogType)4;
                break;
            case 5:
            case 13:
                type = (GSgfxFogType)5;
                break;
            case 6:
            case 14:
                type = (GSgfxFogType)6;
                break;
            case 7:
            case 15:
                type = (GSgfxFogType)7;
                break;
            default:
                return;
            }
            range = fog->range;
            layerA->setFog(type, fog->start, fog->end, fog->color);
            layerB->setFog(type, fog->start, fog->end, fog->color);
            if (range != 0) {
                layerA->setFogRange(true, range->range);
                layerB->setFogRange(true, range->range);
            } else {
                layerA->setFogRange(false, 0xFFFF);
                layerB->setFogRange(false, 0xFFFF);
            }
            layerA->fog(true);
            layerB->fog(true);
            GSgfxVideoSetClearColor(fog->color);
            idx = 0;
            SceneData* scene = (SceneData*)HSD_ArchiveGetPublicAddress(GSresGetResource(group, mapRes), "scene_data");
            if (scene != 0 && scene->models != 0) {
                u32 base = floorReadMakeModelResID(mapRes);
                for (int i = 0; scene->models[i] != 0; i++, idx++) {
                    id = base | idx;
                    void* model = GSresGetResource(group, id);
                    if (model != 0) {
                        s32 state = floorDataBiosModelIDGetFogState(id);
                        GSmodelSetFogState(model, state, state);
                    }
                }
            }
        } else {
            layerA->setFog((GSgfxFogType)2, 0.0f, 5000.0f, zero);
            layerA->setFogRange(false, 0xFFFF);
            layerA->fog(false);
            layerB->setFog((GSgfxFogType)2, 0.0f, 5000.0f, zero);
            layerB->setFogRange(false, 0xFFFF);
            layerB->fog(false);
            GSgfxVideoSetClearColor(zero);
        }
        break;
    }
    }
}

static void _floorInitScene(GSfloor_dd_* floor) {
    f32 fov, aspect, nearZ, farZ;
    void* cam2;
    floorDataBiosGetGroupID(floor);
    if (floorDataBiosGetMapResID(floor) != 0) {
        u32 idx = 0;
        GSfloor_dd_* cur = (GSfloor_dd_*)floorDataBiosGetCurrentPtr();
        SceneData* scene =
            (SceneData*)HSD_ArchiveGetPublicAddress(GSresGetResource(floorGetCurrentGroupID(), cur->mapResID), "scene_data");
        if (scene != 0 && scene->models != 0) {
            u32 base = floorReadMakeModelResID(cur->mapResID);
            for (int i = 0; scene->models[i] != 0; i++, idx++) {
                void* model = GSresGetResource(floorGetCurrentGroupID(), base | idx);
                if (model != 0) {
                    GSmodelSetVisibility(model, true);
                }
            }
        }
    }
    u32 lensRes = floorDataBiosGetLensFlareResID(floor);
    if (lensRes != 0) {
        void* lens = GSresGetResource(floorGetCurrentGroupID(), lensRes);
        if (lens != 0) {
            u32 sunRes = floorDataBiosGetSunResID(floor);
            GSlensFlareSetVisible(lens, false);
            if (sunRes != 0) {
                GSvec pos;
                void* sun = GSresGetResource(floorGetCurrentGroupID(), sunRes);
                if (sun != 0) {
                    GSmodelGetPosition(sun, &pos);
                    GSlensFlareSetSunPosition(lens, &pos);
                    GSlensFlareSetVisible(lens, true);
                }
            }
        }
    }
    void* cam = GScameraGetActiveCamera();
    if (cam != 0) {
        GScameraGetPerspective(cam, &fov, &aspect, &nearZ, &farZ);
        aspect = 1.18f;
        GScameraSetPerspective(cam, fov, aspect, nearZ, farZ);
    }
    cam2 = GSresGetResource(0, 0);
    if (cam2 != 0) {
        GScameraGetPerspective(cam2, &fov, &aspect, &nearZ, &farZ);
        aspect = 1.18f;
        GScameraSetPerspective(cam2, fov, aspect, nearZ, farZ);
    }
}

static void _floorInitShadow(GSfloor_dd_* floor) {
    GSmodelSetShadowToCameraHeightCheck(false);
    switch (floorDataBiosGetFloorKind(floor)) {
    case 1:
        if (floor->floorID == 0x84) {
            GSmodelSetShadowToCameraHeightCheck(true);
        }
        GSmodelSetShadowBoundExpansion(4.0f);
        GSmodelSetShadowDistLimits(400.0f, 350.0f);
        switch (floor->floorID) {
        case 0x3B:
        case 0x3C:
        case 0x3D:
            GSmodelSetShadowCutoffDist(1000.0f);
            GSmodelSetShadowTextureSize(640, 480);
            break;
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x47:
        case 0xAD:
            GSmodelSetShadowDistLimits(700.0f, 650.0f);
        default:
            GSmodelSetShadowCutoffDist(70.0f);
            GSmodelSetShadowTextureSize(384, 384);
            break;
        }
        break;
    case 2:
        GSmodelSetShadowTextureSize(512, 512);
        GSmodelSetShadowCutoffDist(90.0f);
        GSmodelSetShadowBoundExpansion(7.0f);
        GSmodelSetShadowDistLimits(20000.0f, 10000.0f);
        break;
    case 4:
        GSmodelSetShadowTextureSize(512, 512);
        GSmodelSetShadowCutoffDist(80.0f);
        GSmodelSetShadowBoundExpansion(3.0f);
        GSmodelSetShadowDistLimits(20000.0f, 10000.0f);
        break;
    case 3:
    case 5:
    case 6:
        break;
    }
}

void floorInitWazaSequence(u32 id) {
    GSfloor_dd_* floor = floorDataBiosGetPtr(id);
    switch (floorDataBiosGetFloorKind(floor)) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        battleGridReset();
        wazaSequenceSysInit();
        if (floorDataBiosGetFloorKind(floor) == 2) {
            wazaSequenceSysInitExtras();
        }
        battleCameraInit(floor);
        break;
    }
}

static void _floorUpdateWazaSequence(GSfloor_dd_* floor) {
    switch (floorDataBiosGetFloorKind(floor)) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        wazaSequenceSysUpdate();
        battleCameraUpdate();
        cameraUpdate();
        break;
    }
}

static void _floorReleaseWazaSequence(GSfloor_dd_* floor) {
    switch (floorDataBiosGetFloorKind(floor)) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        battleCameraStop();
        battleGridReset();
        wazaSequenceSysRelease();
        break;
    }
}

static void _floorInitializeCommon(unsigned int id, FloorEnterMode mode) {
    u32 group;
    GSfloor_dd_* floor = floorDataBiosGetPtr(id);
    _floorClearFlag();
    msgctrlInitValue();
    scriptModelInit();
    _floorSetInitPosition();
    FIGHT_ENCOUNT* enc = (FIGHT_ENCOUNT*)fightEncountGetStrObj();
    if (enc != 0) {
        enc->setDirtyFlag(true);
    }
    _floorInitScene(floor);
    floorInitOffscreen(floor);
    _floorInitShadow(floor);
    _floorInitMapFog(floor);
    if (floorGetCurentScriptMode() == 1) {
        floorExecScriptIntegerByName("modify_floor", GSfloorGetCurrentFloorGroupID(), mode, 0, 0);
    }
    group = GSfloorGetCurrentFloorGroupID();
    if (mode != 2) {
        switch (floorDataBiosGetFloorKind(floor)) {
        case 1:
            if (pokecoloGetRomVersion() == 2) {
                _hModuleField = floorRegisterModule(0x14, group, (FloorModuleInterface*)effectViewerGetFloorModule());
            } else {
                FloorModuleInterface_clear(&_floorModuleField);
                _floorModuleField.initialize = _floorInitialize;
                _floorModuleField.update = _floorUpdate;
                _floorModuleField.finalize = _floorFinalize;
                _floorModuleField.getModuleName = _floorGetFieldModuleName;
                _hModuleField = floorRegisterModule(0xA, group, &_floorModuleField);
            }
            if (mode != 2 && mode != 1) {
                menuPocketClearItemScript();
            }
            break;
        case 2:
            if (pokecoloGetRomVersion() == 2) {
                _hModuleField = floorRegisterModule(0x14, group, (FloorModuleInterface*)effectViewerGetFloorModule());
            } else {
                _hModuleField = floorRegisterModule(0x14, group, (FloorModuleInterface*)fightGetFloorModule());
            }
            break;
        case 4:
            _hModuleWazaViewer = floorRegisterModule(0x14, group, (FloorModuleInterface*)effectViewerGetFloorModule());
            break;
        case 5:
        case 6:
            FloorModuleInterface_clear(&_floorModuleField);
            _floorModuleField.update = _floorUpdate;
            _floorModuleField.getModuleName = _floorGetMenuModuleName;
            _hModuleField = floorRegisterModule(0x14, group, &_floorModuleField);
            break;
        case 3:
            break;
        }
        if (pokecoloGetRomVersion() != 2 && floorGetCurentScriptMode() == 1) {
            u32 pre = floorGetCurentScript()->getNameToFuncId("preprocess");
            u32 main = floorGetCurentScript()->getNameToFuncId("hero_main");
            u32 post = floorGetCurentScript()->getNameToFuncId("postprocess");
            _hModuleFloorScript = floorRegisterScriptModule(0xF, group, pre, main, post);
        }
        FloorModuleInterface_clear(&_floorModuleUniqueFunc);
        _floorUniqueFunc.pre = (FloorUniqueFn)floorDataBiosGetPreFunc(floor);
        _floorUniqueFuncThread = (void (*)())floorDataBiosGetMainFunc(floor);
        _floorUniqueFunc.unk4 = 0;
        _floorUniqueFunc.post = (FloorUniqueFn)floorDataBiosGetPostFunc(floor);
        _floorModuleUniqueFunc.initialize = _floorUniqueInitialize;
        _floorModuleUniqueFunc.unk0c = _floorUniqueUpdate;
        _floorModuleUniqueFunc.finalize = _floorUniqueFinalize;
        _floorModuleUniqueFunc.getModuleName = _floorGetUniqueModuleName;
        _hModuleUniqueFunc = floorRegisterModule(0xF, group, &_floorModuleUniqueFunc);
        floorSound_playEnvSound(1);
        floorSound_playSound();
    } else {
        _floorUniqueFunc.pre = (FloorUniqueFn)floorDataBiosGetPreFunc(floor);
        _floorUniqueFuncThread = (void (*)())floorDataBiosGetMainFunc(floor);
        _floorUniqueFunc.unk4 = 0;
        _floorUniqueFunc.post = (FloorUniqueFn)floorDataBiosGetPostFunc(floor);
    }
    FloorBgmMask* bgm = (FloorBgmMask*)floorSound_getBgmMaskObj();
    if (bgm != 0) {
        bgm->initialize();
    }
}

static void _floorUpdateCommon(unsigned int id, FloorEnterMode mode) {
    _floorUpdateWazaSequence(floorDataBiosGetPtr(id));
    if (_floorChangeInfo.fadeIn != 0 && _floorChangeInfo.fadeFlag != 0) {
        _floorChangeInfo.fadeFlag = 0;
        floorExecScriptIntegerThread(_floorChangeInfo.fadeIn, 0, 0, 0, 0);
    }
    if (floorIsDispScriptInfo()) {
        floorGetCurentScript()->debugDump();
    }
    FloorBgmMask* bgm = (FloorBgmMask*)floorSound_getBgmMaskObj();
    if (bgm != 0) {
        bgm->update(timeGetLastFrameSec());
    }
}

static void _floorFinalizeCommon(unsigned int id, FloorEnterMode mode) {
    FloorBgmMask* bgm = (FloorBgmMask*)floorSound_getBgmMaskObj();
    if (bgm != 0) {
        bgm->finalize();
    }
    if (mode == 1) {
        floorExecScriptIntegerByName("pushpop_postprocess", GSfloorGetCurrentFloorGroupID(), 0, 0, 0);
    } else {
        mailMainReceiveTerminate();
    }
}

static void _floorFreeCommon(unsigned int id, FloorEnterMode mode) {
    GSfloor_dd_* floor = floorDataBiosGetPtr(id);
    floorDataBiosGetPtr(floorGetNextChangeID());
    AppScript* script = floorGetCurentScript();
    if (script != 0) {
        script->unload();
    }
    _floorReleaseWazaSequence(floor);
    floorReleaseOffscreen();
    if (mode == 1) {
        peopleAllClose(0);
    } else {
        peopleAllClose(1);
    }
    menuCloseFloor();
    scriptGlowEnd();
}

static void _floorUniqueInitialize(unsigned int id, FloorEnterMode mode) {
    GSfloor_dd_* floor = floorDataBiosGetPtr(id);
    if (_floorUniqueFunc.pre != 0) {
        _floorUniqueFunc.pre(floor, floorDataBiosGetGroupID(floor));
    }
}

static void _floorUniqueUpdate() {
    if (_floorUniqueFuncThread != 0) {
        _floorUniqueFuncThread();
    }
}

static void _floorUniqueFinalize(unsigned int id, FloorEnterMode mode) {
    if (mode != 1) {
        GSfloor_dd_* floor = floorDataBiosGetPtr(id);
        if (_floorUniqueFunc.post != 0) {
            _floorUniqueFunc.post(floor, floorDataBiosGetGroupID(floor));
        }
    }
}

void floorInit() {
    FloorModuleInterface_clear(&_floorModuleCommon);
    FloorModuleInterface_clear(&_floorModuleField);
    FloorModuleInterface_clear(&_floorModuleWazaViewer);
    _floorModuleCommon.create = _floorCreateCommon;
    _floorModuleCommon.initialize = _floorInitializeCommon;
    _floorModuleCommon.update = _floorUpdateCommon;
    _floorModuleCommon.finalize = _floorFinalizeCommon;
    _floorModuleCommon.free = _floorFreeCommon;
    _floorModuleCommon.makeStateData = _floorMakeStateData;
    _floorModuleCommon.restoreStateData = _floorRestoreStateData;
    _floorModuleCommon.getStateSize = _floorGetStateSize;
    _floorModuleCommon.getUID = _floorGetUID;
    _floorModuleCommon.getModuleName = _floorGetModuleName;
    _hModuleCommon = floorRegisterModule(0, 0x5000, &_floorModuleCommon);
    u32 floorID;
    switch (pokecoloGetRomVersion()) {
    case 5:
        floorID = 0x3E4;
        break;
    case 1:
        floorID = 0x3E6;
        break;
    case 2:
        floorID = 0xAE;
        break;
    case 6:
        floorID = 0x399;
        break;
    default:
        if (pokecoloIsDVDETHMode()) {
            floorID = 0x384;
        } else {
            floorID = 0x399;
        }
        break;
    }
    _floorChangeInfo.prevFloorID = 0;
    _floorChangeInfo.nextFloorID = floorID;
    _floorChangeInfo.usePos = 1;
    _floorChangeInfo.nextPosIndex = 0;
    _floorChangeInfo.fadeFlag = 0;
    _floorChangeInfo.continueMode = 0;
    _floorChangeInfo.bgmFlag = 0;
    _floorChangeInfo.envFlag = 1;
    GSfloorOpen(floorID);
    GSfloorStart(floorID);
    floorOffscreenMainInit();
    floorCharacterBiosInitGlobalCharacter();
}

void floorSetFadeScript(u32 out, u32 in) {
    _floorChangeInfo.fadeIn = in;
    _floorChangeInfo.fadeOut = out;
}

void flooSetFrameRate() {
    pokecoloWaitVSync = 1;
    switch (floorDataBiosGetFloorKind((void*)floorDataBiosGetCurrentPtr())) {
    case 5:
    case 6:
        GSgfxVideoSetLockFrameRate(0);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    default:
        GSgfxVideoSetLockFrameRate(1);
        break;
    }
}

void floorExecFadeIn() {
    if (_floorChangeInfo.fadeIn != 0) {
        if (_floorChangeInfo.fadeIn != 0) {
            _floorChangeInfo.fadeFlag = 1;
        }
    }
}

void floorExecFadeOut() {
    if (_floorChangeInfo.fadeOut != 0) {
        floorExecScriptInteger(_floorChangeInfo.fadeOut, 0, 0, 0, 0);
    }
}

void floorCheckFade() {
    fadeCheck(1);
    pokecoloWaitVSync = 0;
    GSgfxVideoSetLockFrameRate(0);
}

void floorExecSoundScript() {
    if (floorGetCurentScriptMode() == 1) {
        s32 arg = 0;
        if (floorIsContinueMode()) {
            arg = 3;
        }
        floorExecScriptIntegerByName("sound", GSfloorGetCurrentFloorGroupID(), arg, 0, 0);
    }
}

u8 floorReadCharacter(u32 group, u32 id, u32 modelRes) {
    GSvec a;
    GSvec b;
    void* info = floorCharacterBiosGetPeopleInfoPtr(floorCharacterBiosGetCurrentPtr(id));
    if (modelRes == 0) {
        modelRes = peopleInfoBiosGetModelResID(info);
    }
    u32 obj = peopleOpen(group, id, modelRes);
    if (obj == 0) {
        GSlogWrite("Error! [%s] 人の初期化に失敗\n", __FUNCTION__);
        return 0;
    }
    _floorInitCharactor(group, id, obj);
    return 1;
}

static void _floorFsysFree(unsigned long id) {
    switch (GSfsysGetStatus(id)) {
    case -1:
        break;
    case 1:
        while (GSfsysGetStatus(id) == 1) {
            GSthreadSwitch();
        }
    case 0:
        GSresFreeGroup(id);
        GSfsysFree(id);
        break;
    }
}

u32 fn_8011E650() {
    switch (pokecoloGetLanguage()) {
    case 2:
        return 0xC;
    case 3:
        return 0xA99;
    case 4:
        return 0xA9A;
    case 5:
        return 0xA9B;
    case 6:
        return 0xA9C;
    default:
        return 0xC;
    }
}

u32 fn_8011E5D8() {
    switch (pokecoloGetLanguage()) {
    case 2:
        return 0xB;
    case 3:
        return 0xA95;
    case 4:
        return 0xA96;
    case 5:
        return 0xA97;
    case 6:
        return 0xA98;
    default:
        return 0xB;
    }
}

static void _floorCreateCommon(unsigned int id, FloorEnterMode mode) {
    GSgfxColAu8 clearColor = {0};
    GSfloor_dd_* floor = floorDataBiosGetPtr(id);
    cameraSetType(3);
    GSgfxVideoSetClearColor(clearColor);
    switch (floorDataBiosGetFloorKind(floor)) {
    case 6:
        _floorFsysFree(0x9A);
        if (GSfsysGetStatus(fn_8011E5D8()) != 0) {
            GSfsysReadWait(fn_8011E5D8());
        }
        _floorFsysFree(fn_8011E650());
        break;
    case 1:
        if (pokecoloGetRomVersion() != 2) {
            _floorFsysFree(fn_8011E650());
            u32 total, freeSize;
            GSmemGetHeapFreeSize(GSmemGetCurrentHeap(), &total, &freeSize);
            if (freeSize * 100 / total < 80) {
                _floorFsysFree(fn_8011E5D8());
                _floorFsysFree(0x9A);
            }
            u32 ken = heroMoveGetKenObjID();
            if (ken != heroGetObjID(0)) {
                GSfsysReadIDWait(0x9A, ken);
            }
            if (GSfsysGetStatus(fn_8011E5D8()) != 0) {
                GSfsysReadWait(fn_8011E5D8());
            }
        }
        break;
    case 2:
        if (pokecoloGetRomVersion() != 2) {
            _floorFsysFree(fn_8011E5D8());
            _floorFsysFree(0x9A);
            if (GSfsysGetStatus(fn_8011E650()) != 0) {
                GSfsysReadWait(fn_8011E650());
            }
        }
        break;
    }
}

u8 floorCheckFightKind(u32 id) {
    u8 result = 0;
    if (id != 0xFFFFFFFF) {
        switch (floorDataBiosGetFloorKind(floorDataBiosGetPtr(id))) {
        case 2:
            result = 1;
            break;
        }
    }
    return result;
}

void floorSetHumanColision(u8 v) {
    _floorChangeInfo.humanColision = v;
}

u8 floorGetHumanColision() {
    return _floorChangeInfo.humanColision;
}

static void _floorMapSetDispCB(unsigned long kind, unsigned long, unsigned long, void* res, void* ctx) {
    bool disp = ctx != 0;
    switch (kind) {
    case 1:
        GSmodelSetVisibility(res, disp);
        break;
    case 2:
        GSlightSetActive(res, disp);
        break;
    }
}

void floorMapSetDisp(u8 disp) {
    floorMapResourceDataIterate(_floorMapSetDispCB, (void*)disp);
}

void floorMapResourceDataIterate(FloorMapCB cb, void* ctx) {
    u32 group;
    u32 lightIdx = 0;
    u32 modelIdx = 0;
    u32 id;
    u32 mapRes = floorDataBiosGetMapResID((void*)floorDataBiosGetCurrentPtr());
    if (mapRes != 0) {
        group = floorGetCurrentGroupID();
        void* archive = GSresGetResource(group, mapRes);
        SceneData* scene = (SceneData*)HSD_ArchiveGetPublicAddress(archive, "scene_data");
        if (scene != 0) {
            if (scene->models != 0) {
                u32 base = floorReadMakeModelResID(mapRes);
                for (int i = 0; scene->models[i] != 0; i++, modelIdx++) {
                    id = base | modelIdx;
                    void* res = GSresGetResource(group, id);
                    if (res != 0) {
                        cb(1, group, id, res, ctx);
                    }
                }
            }
            if (scene->lights != 0) {
                u32 base = floorReadMakeLightResID(mapRes);
                for (int i = 0; scene->lights[i] != 0; i++, lightIdx++) {
                    id = lightIdx | base;
                    void* res = GSresGetResource(group, id);
                    if (res != 0) {
                        cb(2, group, id, res, ctx);
                    }
                }
            }
        }
    }
}

static void _floorMapGetCountCB(unsigned long kind, unsigned long, unsigned long, void*, void* ctx) {
    int* counts = (int*)ctx;
    switch (kind) {
    case 1:
        counts[0]++;
        break;
    case 2:
        counts[1]++;
        break;
    }
}

static void _floorMapGetResourceCounts(int* models, int* lights) {
    int counts[2];
    counts[0] = 0;
    counts[1] = 0;
    floorMapResourceDataIterate(_floorMapGetCountCB, counts);
    *models = counts[0];
    *lights = counts[1];
}

static void _floorMapPopCB(unsigned long kind, unsigned long, unsigned long id, void* res, void* ctx) {
    StateCtx* c = (StateCtx*)ctx;
    StateEntry* e = c->cur;
    for (u32 i = c->count; i != 0; i--, e++) {
        if (id == e->id) {
            switch (e->kind) {
            case 1:
                GSmodelPopState(res, e->data);
                break;
            case 2:
                GSlightPopState(res, e->data);
                break;
            }
            return;
        }
    }
}

static void _floorMakeStateData(FloorStateMode mode, void* data, unsigned long size) {
    u32* d = (u32*)data;
    if (mode == 1 || mode == 2) {
        if (mode == 1) {
            floorReleaseOffscreen();
        }
        memset(d, 0, 0x10);
        d[0] = soundGetBGMID();
        d[1] = soundGetVolume(d[0]);
        d[2] = soundGetEnvID();
        d[3] = soundGetVolume(d[2]);
        StateEntry* cur = (StateEntry*)(d + 4);
        floorMapResourceDataIterate(_floorMapPushCB, &cur);
    }
}

static void _floorRestoreStateData(FloorStateMode mode, void* data, unsigned long size) {
    u32* d = (u32*)data;
    if (mode == 1 || mode == 2) {
        if (_floorChangeInfo.bgmFlag != 0 && d[0] != soundGetBGMID()) {
            soundOpenPlay(d[0], 1000, 127);
            soundSetVolumeID(d[0], 1000, (u8)d[1]);
        }
        if (_floorChangeInfo.envFlag != 0 && d[2] != soundGetEnvID()) {
            soundOpenPlayEnv(d[2], 1000, 127);
            soundSetVolumeID(d[2], 1000, (u8)d[3]);
        }
        StateCtx ctx;
        ctx.cur = (StateEntry*)(d + 4);
        ctx.count = (size - 0x10) / sizeof(StateEntry);
        floorMapResourceDataIterate(_floorMapPopCB, &ctx);
    }
}

static u32 _floorGetStateSize(FloorStateMode mode) {
    if (mode != 1 && mode != 2) {
        return 0;
    }
    int a, b;
    _floorMapGetResourceCounts(&a, &b);
    return (a + b) * sizeof(StateEntry) + 0x10;
}

static u32 _floorGetUID() {
    static const char* id = "FLOR";
    return (id[0] << 24) | (id[1] << 16) | (id[2] << 8) | id[3];
}

static const char* _floorGetModuleName() {
    return "floorModuleCommon";
}

static void _floorMapPushCB(unsigned long kind, unsigned long, unsigned long id, void* res, void* ctx) {
    StateEntry** pp = (StateEntry**)ctx;
    StateEntry* e = *pp;
    e->id = id;
    e->kind = kind;
    switch (kind) {
    case 1:
        GSmodelPushState(res, e->data);
        break;
    case 2:
        GSlightPushState(res, e->data);
        break;
    }
    *pp = e + 1;
}

void floorBlockMainScript() {
    floorBlockModule(_hModuleFloorScript);
}

void floorUnblockMainScript() {
    floorUnblockModule(_hModuleFloorScript);
}

void floorSetLightInfo(u32 a, u32 b) {
    _floorChangeInfo.lightInfoA = a;
    _floorChangeInfo.lightInfoB = b;
}

void floorGetLightInfo(u32* a, u32* b) {
    if (a != 0) {
        *a = _floorChangeInfo.lightInfoA;
    }
    if (b == 0) {
        return;
    }
    *b = _floorChangeInfo.lightInfoB;
}

inline GSmtx GSmtx::makeIdentity() {
    GSmtx m;
    PSMTXIdentity(&m);
    return m;
}

inline void GSgfxLayer::fog(bool on) {
    fogOn = on;
    dirty170c |= 0x40;
    dirty17c4 |= 0x40;
    if (on) {
        dirty170c |= 0x200;
        dirty17c4 |= 0x200;
        if (fogRangeOn) {
            dirty170c |= 0x100;
            dirty17c4 |= 0x100;
        }
    }
    dirty16a8 |= 0x40;
    dirty1760 |= 0x40;
}

inline void GSgfxLayer::setFogRange(bool on, u16 range) {
    fogRangeOn = on;
    if (range != 0xFFFF) {
        fogRange = range;
    } else {
        GSgfxSize size;
        GSgfxVideoGetEFBSize(&size, 0);
        fogRange = size.w >> 1;
    }
    if (fogOn) {
        dirty170c |= 0x200;
        dirty17c4 |= 0x200;
        if (on) {
            dirty170c |= 0x100;
            dirty17c4 |= 0x100;
        }
        dirty16a8 |= 0x40;
        dirty1760 |= 0x40;
    }
}

inline void GSgfxLayer::setFog(GSgfxFogType type, f32 start, f32 end, GSgfxColAu8 col) {
    fogType = type;
    fogStart = start;
    fogEnd = end;
    fogColor.rgba = col.rgba;
    if (fogOn) {
        dirty170c |= 0x40;
        dirty16a8 |= 0x40;
        dirty17c4 |= 0x40;
        dirty1760 |= 0x40;
    }
}
