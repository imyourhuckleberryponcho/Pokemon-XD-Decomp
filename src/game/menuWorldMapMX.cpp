// Pokemon XD world map menu (WorldMap). Needs extra_cflags -inline noauto,deferred (source is bottom-to-top).
#include <dolphin/types.h>
#pragma peephole off

struct GSvec { f32 x, y, z; };
struct GSgfxLayerID { u8 a, b; s16 c; };
struct _GSparticleGen;
struct tagWINDOW_WORK {
    u8 pad0;
    s8 state;
    u8 pad2[0x1C - 2];
    s32 layer;
    u8 pad20[0x9E - 0x20];
    s16 cursor;
};
struct tagSPRITE_WORK {
    u8 pad0[6];
    s16 id;
    u8 pad8[0x64 - 8];
    u8 r, g, b, a;
};
enum GSattachMode { Attach0 };

class Hero {
public:
    u8 getFollowerID();
    u8 getHeroStyle() const;
};

class WorldMapModel {
public:
    WorldMapModel() : mOffscreenData(0) {}
    ~WorldMapModel() { if (mOffscreenData) releaseOffscreenData(); }
    void releaseOffscreenData();
    void initializeOffscreenData();
    void renderOffscreenData(f32);
    void SetModel(u32, u32, bool);
    void SetMotion(u32, s16, f32, bool);
    f32 GetAnimeFrameCount(u32, u32);
    f32 GetAnimeFrame(u32);
    void ModelAttach(u32, u32, s32, GSattachMode);
    void ModelDetach(u32);
    _GSparticleGen* SetModelPartPaticle(u32, u32, s32, GSattachMode, bool, bool, bool);
    void DetachModelPartPaticle(_GSparticleGen*, bool);
    bool CheckMotion(u32);
    void StopMotion(u32);
    void ObjectVisibility(u32, bool);
    void Visibility(u32, bool);
    void* GetModelPtr(u32);
    void UnloadModel(u32, u32);
    void SetLayerID(u32, s32, GSgfxLayerID*);
    void* mOffscreenData;
};

class GSeffect {
public:
    bool active, visible;
    GSeffect* next;
    bool Start();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32);
    virtual void _render(void*, s32);
    virtual void _fastRender();
    virtual ~GSeffect();
};
class glowEffect : public GSeffect {
public:
    glowEffect();
    virtual ~glowEffect();
    virtual void _render(void*, s32);
    f32 strength;
    u8 width, blend, normalize, method, samples;
};

struct WorldMapData {
    s16 camera;
    u16 npc;
    u32 flag;
    u32 selectIndex;
    u32 model;
    u32 snap;
    u32 motion;
    u32 pad18;
    u32 floorID;
    u32 msgID;
};
struct WorldMapMsgData {
    s32 etc;
    s32 msg[18];
};
struct WorldMapCameraData {
    GSvec pos;
    f32 a, b, c, fov;
};
struct FlagEtc {
    u8 type, unk1;
    u16 floor, pokedoru;
    u8 unk6[2];
    u32 flagValue;
    u8 rest[0x14];
};

struct MoveAnime { u32 modelRes, model; s16 pad; s16 bone; u32 camera; };
struct ScooterData { u32 res, model, p0, p1, p2; };

extern "C" s32* worldmapXD_data_number;
struct WorldMapIconSubWork {
    f32 dist, angle;
    WorldMapIconSubWork(f32 d = 0.0f, f32 a = 0.0f) { dist = d; angle = a; }
};
struct WorldMapIconWork {
    u32 model;
    s16 anim;
    GSvec pos;
    s8 pad[8];
    f32 sx, sy, sz;
    WorldMapIconSubWork* sub;
    WorldMapIconWork() {
        sub = new WorldMapIconSubWork[*worldmapXD_data_number];
        pad[0] = -1;
        pad[1] = -1;
        pad[2] = -1;
        pad[3] = -1;
        pad[4] = -1;
        pad[5] = -1;
        pad[6] = -1;
        pad[7] = -1;
    }
    ~WorldMapIconWork() {
        delete[] sub;
    }
};

struct WorldMapCamWork {
    GSvec pos;
    GSvec up;
    f32 a, b, c, fov;
};
struct WorldMapCamera {
    s32 cur, prev;
    f32 t, acc, speed, time;
    WorldMapCamWork now;
    WorldMapCamWork next;
    WorldMapCamera() {
        time = 0.0f;
        t = 0.0f;
        acc = 0.0f;
    }
};

struct WorldMapState {
    u8 floorPush;
    u8 pad1[3];
    s32 camera;
    GSvec up;
    u8 pad14[0x2C - 0x14];
    s32 cursorSel;
    s32 cursorNow;
    s32 floorID;
    f32 angle;
    f32 fade;
    MoveAnime* anime;
    s32 moveCamera;
    u8 moveFlag;
    u8 pad49[3];
    u32 mdlRes;
    u32 mdl50;
    u32 mdl54;
    u32 mdl58;
    u32 mdl5C;
    s32 scooterType;
    u32 scooterRes;
    u32 scooterModel;
    u32 nullRes;
    u32 nullModel;
    ScooterData* scooter;
    u32 partRes[3];
    _GSparticleGen* part[3];
    u8 flag90;
    u8 pad91[3];
};


extern "C" {
extern WorldMapData* worldmapXD_data;
extern s32* worldmapXD_data_number;
extern WorldMapMsgData* worldmapXD_msgdata;
extern s32* worldmapXD_msgdata_number;
extern WorldMapCameraData* worldmap_cameradata;
extern u32* worldmap_cameradata_number;
extern FlagEtc* flag_etc;

u32 GSflagGet(s32);
void GSflagSet(s32, s32);
void GSthreadSwitch(void);
void* GSmemAlloc(u32);
void GSmemFree(void*);
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
u16 HSD_Rand(void);
void soundStopEnv(s32);
s32 GScameraGetActiveCamera(void);
s32 menuOpenCustom(s32, ...);
void menuClose(s32);
void menuCloseSync(s32, s32);
s32 windowGetActiveID(void);
void GSfloorPop(void);
void msgctrlSetValue(s32, u32);
u8 menuScriptGetOpenWorldMapFlag(void);
void menuScriptSetOpenWorldMapFlag(s32);
u16 menuScriptOpenWorldMapGetMapNumber(void);
void menuItemBiosSetSelectFlag(s32, u32, bool);
bool menuItemBiosGetSelectFlag(s32, u32 a1 = 0);
void heroMovePoolCounter(s32, s32);
void fadeSet(s32, f32);
s8 fadeCheck(s32);
void floorLink(s32, s32);
void floorSetFadeScript(s32, s32);
void* floorDataBiosGetPtr(s32);
u32 floorDataBiosGetFileGroupID(void*);
void GSfsysPreRead(u32);
void GSfsysReadID(s32, s32);
bool GSfsysWait(s32);
void GSfsysFree(s32);
void* GSresGetResource(s32, s32);
void* GSresGetResourceAllGroup(u32);
void GSresFreeResource(s32, s32);
void GSresFreeResourceAllGroup(s32);
s32 floorGetCurrentGroupID(void);
s32 floorGetNextFloorID(void);
s32 floorGetPrevFloorID(void);
void GSsndPlayNow(s32);
void GSsndStopNow(s32);
void GSgfxVideoSetLockFrameRate(s32);
void* GSgfxLayerFindByID(s32);
bool GScameraIsAnimating(s32);
f32 GScameraGetAnimFrame(s32);
void GSmodelSetRenderCamera(void*, s32);
void GSparticleGeneratorSetCamera(_GSparticleGen*, s32);
void GSmodelSetBoundCheck(void*, bool);
void GSmodelSetShadowFlags(void*, s32);
void GSmodelSetShadowLight(void*, void*);
void GSmodelSetShadowSurface(void*, s32, void*);
void GSmodelSetAnimIndex(void*, s32);
void GSmodelSetAnimFrame(void*, f32);
void GSmodelSetAnimRate(void*, f32);
void GSmodelStartAnimation(void*);
void GSmodelGetPosition(void*, void*);
void GSmodelSetPosition(void*, void*);
void GScameraSetAnimIndex(void*, s32);
void GScameraSetAnimType(void*, s32);
void GScameraSetAnimRate(void*, f32);
void GScameraSetAnimFrame(void*, f32);
void GScameraStartAnimation(void*);
void GScameraGetPerspective(s32, f32*, f32*, f32*, f32*);
void GScameraSetPerspective(s32, f32, f32, f32, f32);
void GScameraLookAt(s32, void*, void*);
void* GScameraGetMatrixPtr(void);
void* GScameraGetProjMatrixPtr(s32);
void cameraSetType(s32);
void cameraUpdate(void);
void cameraSetPosition(void*);
void cameraSetTargetPos(void*);
void cameraSetRotation(void*);
void cameraSetFov(f32);
f32 timeGetLastFrameSec(void);
f32 GSlerpGetLinearInterpolationFloat(f32, f32, f32);
void PSMTXConcat(void*, void*, void*);
void PSMTXMultVec(void*, void*, void*);
void PSMTXRotRad(void*, s32, f32);
void PSVECAdd(void*, void*, void*);
f32 PSVECDistance(void*, void*);
double atan2(double, double);
double sin(double);
double tan(double);
void* savedataGetStatus(s32, s32);
u32 charNameBiosGetNameID(u16);
void GSmsgPrint2(s32, s16, s32, u32, u32);
void winSpriteSetDisp(tagSPRITE_WORK*, bool);
void windowDrawSprite(s32, s32, s32, u16, s32, s32);
void* windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
void menuButtonNormal(tagWINDOW_WORK*);
void menuCursorNormal(tagWINDOW_WORK*, s32);
}
class WorldMap;
// ---- data (in original order) ----

static MoveAnime _animeTable_A[4] = {
    { 0x20C30400, 0x20C31000, 0, 1, 0x20BF1800 },
    { 0x20C40400, 0x20C41000, 0, 1, 0x20C01800 },
    { 0x20C50400, 0x20C51000, 0, 1, 0x20C11800 },
    { 0x20C60400, 0x20C61000, 0, 1, 0x20C21800 },
};
static MoveAnime _animeTable_B[4] = {
    { 0x20CB0400, 0x20CB1000, 0, 1, 0x20C71800 },
    { 0x20CC0400, 0x20CC1000, 0, 1, 0x20C81800 },
    { 0x20CD0400, 0x20CD1000, 0, 1, 0x20C91800 },
    { 0x20CE0400, 0x20CE1000, 0, 1, 0x20CA1800 },
};
static ScooterData _mapScooterData[7] = {
    { 0x206D0400, 0x206D1000, 0x51, 0x55, 0 },
    { 0x206E0400, 0x206E1000, 0xA6, 0xAA, 0 },
    { 0x206F0400, 0x206F1000, 0x56, 0x5A, 0 },
    { 0x20700400, 0x20701000, 0xAA, 0xAE, 0 },
    { 0x20710400, 0x20711000, 0x50, 0x51, 0x52 },
    { 0x20720400, 0x20721000, 0x54, 0x55, 0x56 },
    { 0x20730400, 0x20731000, 0x57, 0x58, 0x59 },
};
static s16 _cursor_index[30];
static MoveAnime* _animeTable[2] = { _animeTable_A, _animeTable_B };
static f32 CURSOR_DISTANCE_MAX = 700.0f;
static f32 _waittime = 0.7f;
static f32 _a0 = 0.0001f;
static f32 _checkAngle = 1.3089969f;
static f32 _checkAngleStart = 0.3926991f;
static f32 _checkAngleAdd = 0.08726646f;
static bool _testVisibility = true;
static f32 _testFadeTime = 1.5f;
static bool _testExit = true;
static f32 _glowstrngth = 0.5f;
static u8 _glowwidth = 20;
static u8 _glownormalize = 1;
static u8 _glowsamples = 1;
static u8 _release_flag = 1;
static WorldMap* pWorldmap;
static u8 _cameraDebug;
static u8 _mojiOn;
static u8 _DebugControl;
static s16 _cursor_index_num;
static f32 _v0;
static bool _AnimeLoop;
static u8 _glowblend;
static u8 _glowmethod;

class WorldMap : public WorldMapModel {
public:
    ~WorldMap();
    WorldMap();
    void CallBackFunc(tagWINDOW_WORK*, tagSPRITE_WORK*);
    s32 Ctrl(tagWINDOW_WORK*);
    void MainControl(s32);
    s32 GetNowCursor(tagWINDOW_WORK*);
    void InitRenderModule();
    void Button(tagWINDOW_WORK*);
    void Cursor(tagWINDOW_WORK*);
    void ControlPad(tagWINDOW_WORK*);
    void Release();
    void RenderMoveDemoModel();
    void moveDemo(s32, s32);
    u32 readScooter();
    s32 getScooterType();
    void setNullModel();
    void Main();
    u8 IsFloorPush();
    void MainSub2();
    void MainSub();
    void PreRead(s32);
    void CheckPadIndex(bool);
    void CalcModel2D(f32, bool);
    s8 GetPadIndex3(f32, s32, f32);
    void InitModel2D(f32);
    void SetCameraSpeed(f32);
    void InitCamera(s32);
    void Init();
    void SetCamera();
    void SelectIcon(s32);
    void TargetDebug(s32);
    void ControlCamera(s32);
    bool IsBlending();
    void SetCameraNextWork(GSvec*, f32, f32, f32, f32);
    void SetCameraWork(GSvec*, f32, f32, f32, f32);
    bool Blendf(f32*, f32, f32, f32);
    void InitModel(s32);
    void SetCursorPosition(s32, bool);
    void InitCursor(s32, s16);
    u32 GetModelID(s32);
    void SetSnap(s32, tagWINDOW_WORK*, tagSPRITE_WORK*);
    void SetInfo(s32, tagWINDOW_WORK*, tagSPRITE_WORK*);
    u16 GetNpcID(s32);
    s32 GetInfoMsgID(s32);
    void* GetModelPointer(s32);
    s32 GetInfoLevel();
    f32 GetAngle(s32);
    void SetFlagData(s32);
    u32 GetFlagData(s32);
    s32 SearchFloorID(u16);
    s32 SearchDataFloorID(unsigned int);
    WorldMapData* SearchData(s32);
    s32 GetDataNum();
    s16 GetStartIconAnimIndex(u32);
    void ControlCursor(s32);
    f32 GetLastTime();
    void CheckIconAnime(s32);
    void CheckCursorAnime();
    void SetIconMotion(s32, u32, s16, f32, bool);
    void GetCameraData(s32, GSvec*, f32*, f32*, f32*, f32*);

    glowEffect* glow;
    WorldMapState* st;
    WorldMapIconWork* icons;
    u32 cursorModel;
    s16 cursorAnim;
    s16 pad16;
    s32 cursorIdx;
    u8 cursorMoving;
    u8 pad1d[3];
    GSvec cur, tgt;
    f32 blend, bob, time;
    WorldMapCamera* cam;
};

void WorldMap::GetCameraData(s32 idx, GSvec* pos, f32* a, f32* b, f32* c, f32* fov) {
    if ((u32)idx < *worldmap_cameradata_number) {
        WorldMapCameraData* d = &worldmap_cameradata[idx];
        f32 x, y, z;
        z = d->pos.z;
        y = d->pos.y;
        x = d->pos.x;
        pos->x = x;
        pos->y = y;
        pos->z = z;
        *a = d->a;
        *b = d->b;
        *c = d->c;
        *fov = d->fov;
    }
}

void WorldMap::SetIconMotion(s32 idx, u32 model, s16 motion, f32 frame, bool loop) {
    icons[idx].anim = motion;
    SetMotion(model, motion, frame, loop);
}

void WorldMap::CheckCursorAnime() {
    u32 m = cursorModel;
    switch (cursorAnim) {
    case 2:
        if (!CheckMotion(m)) {
            StopMotion(m);
        }
        break;
    }
}

void WorldMap::CheckIconAnime(s32 sel) {
    s16 selIdx = _cursor_index[sel];
    s32 i = 0;
    st->moveFlag = 0;
    while (i < GetDataNum()) {
        u32 model = icons[i].model;
        switch (icons[i].anim) {
        case 1:
            if (!CheckMotion(model)) {
                SetIconMotion(i, model, 2, 0.0f, true);
            } else {
                st->moveFlag = 1;
            }
            break;
        case 6:
            if (!CheckMotion(model)) {
                SetIconMotion(i, model, 7, 0.0f, true);
            }
            break;
        case 2:
            if (selIdx == i) {
                SetIconMotion(i, model, 4, 0.0f, true);
            }
            break;
        case 7:
            if (selIdx == i) {
                SetIconMotion(i, model, 8, 0.0f, true);
            }
            break;
        case 4:
            if (selIdx != i) {
                SetIconMotion(i, model, 2, 0.0f, true);
            }
            break;
        case 8:
            if (selIdx != i) {
                SetIconMotion(i, model, 7, 0.0f, true);
            }
            break;
        case 5:
            if (!CheckMotion(model)) {
                StopMotion(model);
            }
            break;
        case 9:
            if (!CheckMotion(model)) {
                StopMotion(model);
            }
            break;
        }
        i++;
    }
}

f32 WorldMap::GetLastTime() { return timeGetLastFrameSec(); }

void WorldMap::ControlCursor(s32) {
    void* m = GSresGetResourceAllGroup(cursorModel);
    f32 dt = GetLastTime();
    if (cursorMoving != 0) {
        blend = 2.0f * dt + blend;
        if (blend >= _waittime) {
            blend = 1.0f;
            cursorMoving = 0;
        }
        Blendf(&cur.x, cur.x, tgt.x, blend);
        Blendf(&cur.y, cur.y, tgt.y, blend);
        Blendf(&cur.z, cur.z, tgt.z, blend);
    }
    if (st->floorPush != 0) {
        time = time + dt;
        bob = 5.0f * (f32)sin(6.2831855f * time) + 5.0f;
        cur.y = bob;
    }
    GSmodelSetPosition(m, &cur);
}

s16 WorldMap::GetStartIconAnimIndex(u32 flag) {
    switch (flag) {
    case 0:
        return 0;
    case 1:
        return 6;
    case 2:
        return 1;
    default:
        return 0;
    }
}

WorldMap::WorldMap() {
    st = 0;
    glow = 0;
}

WorldMap::~WorldMap() { Release(); }

s32 WorldMap::GetDataNum() { return *worldmapXD_data_number; }

WorldMapData* WorldMap::SearchData(s32 i) {
    if (i >= GetDataNum()) {
        return 0;
    }
    return &worldmapXD_data[i];
}

s32 WorldMap::SearchDataFloorID(unsigned int floor) {
    s32 i;
    s32 count = 0;
    i = 0;
    while (i < GetDataNum()) {
        WorldMapData* d = SearchData(i);
        u32 f = GSflagGet(d->flag);
        if (d->flag == 0 || f != 0) {
            count++;
            if (floor == worldmapXD_data[i].floorID) {
                return count - 1;
            }
        }
        i++;
    }
    return 0;
}

s32 WorldMap::SearchFloorID(u16 id) {
    WorldMapData* d = SearchData(id);
    u32 f = GSflagGet(d->flag);
    if (d->flag == 0 || f != 0) {
        return d->floorID;
    }
    return SearchData(6)->floorID;
}

u32 WorldMap::GetFlagData(s32 i) {
    WorldMapData* d = SearchData(i);
    if (d->flag == 0) {
        return 2;
    }
    return GSflagGet(d->flag);
}

void WorldMap::SetFlagData(s32 i) {
    WorldMapData* d = SearchData(i);
    if (d->flag != 0) {
        GSflagSet(d->flag, 2);
    }
}

f32 WorldMap::GetAngle(s32 i) { return 0.3926991f * (f32)i; }

s32 WorldMap::GetInfoLevel() {
    WorldMapMsgData* p = worldmapXD_msgdata;
    s32 level = 0;
    s16 i = 0;
    while (i < *worldmapXD_msgdata_number) {
        if (p->etc != 0) {
            u32 need = flag_etc[p->etc].flagValue;
            if (GSflagGet(0x3C4) >= need) {
                level++;
            }
        }
        p++;
        i++;
    }
    return level - 1;
}

void* WorldMap::GetModelPointer(s32 i) { return GSresGetResourceAllGroup(GetModelID(i)); }

s32 WorldMap::GetInfoMsgID(s32 now) {
    s16 idx = _cursor_index[now];
    if (st->floorPush != 0) {
        return SearchData(idx)->msgID;
    }
    return worldmapXD_msgdata[GetInfoLevel()].msg[idx];
}

u16 WorldMap::GetNpcID(s32 now) { return SearchData(_cursor_index[now])->npc; }

void WorldMap::SetInfo(s32 now, tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    SearchData(_cursor_index[now]);
    if (st->floorPush != 0) {
        u32 name = charNameBiosGetNameID(GetNpcID(now));
        if (name == 0) {
            name = 0x1772;
        }
        msgctrlSetValue(0x59, name);
    }
    GSmsgPrint2(window->layer, 0, -4, sprite->a | 0xFFFFFF00, GetInfoMsgID(now));
}

void WorldMap::SetSnap(s32 now, tagWINDOW_WORK* window, tagSPRITE_WORK*) {
    WorldMapData* d = SearchData(_cursor_index[now]);
    switch (GetFlagData(_cursor_index[now])) {
    case 0:
        break;
    case 1:
        windowDrawSprite(0, 0, 0, 0x33F, 0, window->layer);
        return;
    case 2:
        windowDrawSprite(0, 0, 0, d->snap, 0, window->layer);
        return;
    }
}

u32 WorldMap::GetModelID(s32 i) { return SearchData(i)->model; }

void WorldMap::InitCursor(s32 sel, s16 anim) {
    GSgfxLayerID id = {0, 0, 2};
    time = 0.0f;
    bob = 0.0f;
    cursorModel = 0x18531013;
    cursorAnim = anim;
    blend = 0.0f;
    cursorMoving = 1;
    switch (anim) {
    case 2:
        SetMotion(cursorModel, cursorAnim, 0.0f, false);
        break;
    default:
        SetMotion(cursorModel, cursorAnim, 0.0f, true);
        break;
    }
    SetLayerID(cursorModel, 1, &id);
    SetCursorPosition(sel, false);
    cur.x = tgt.x;
    cur.y = tgt.y;
    cur.z = tgt.z;
}

void WorldMap::SetCursorPosition(s32 sel, bool snap) {
    SearchData(_cursor_index[sel]);
    WorldMapIconWork* ic = &icons[_cursor_index[sel]];
    tgt.x = ic->pos.x;
    tgt.y = ic->pos.y;
    tgt.z = ic->pos.z;
    cursorIdx = sel;
    if (snap) {
        cursorMoving = 1;
        blend = 0.0f;
    }
}

void WorldMap::InitModel(s32 sel) {
    GSgfxLayerID id = {0, 0, 2};
    void* model = GSresGetResourceAllGroup(0x18531000);
    void* ptr;
    s32 i;
    u32 mid;
    u32 flag;
    s16 anim;
    GSmodelSetAnimIndex(model, 0);
    GSmodelSetAnimFrame(model, 0.0f);
    GSmodelSetAnimRate(model, 0.5f);
    GSmodelStartAnimation(model);
    SetLayerID(0x18531000, 1, &id);
    i = 0;
    while (i < GetDataNum()) {
        mid = GetModelID(i);
        flag = GetFlagData(i);
        ptr = GetModelPointer(i);
        icons[i].model = mid;
        if (st->floorPush != 0) {
            if (i == _cursor_index[sel]) {
                if (flag == 2) {
                    icons[i].anim = 3;
                } else {
                    icons[i].anim = 7;
                }
            } else {
                icons[i].anim = GetStartIconAnimIndex(flag);
            }
        } else if (i == _cursor_index[sel]) {
            icons[i].anim = 4;
        } else {
            icons[i].anim = GetStartIconAnimIndex(flag);
        }
        SetLayerID(mid, 1, &id);
        anim = icons[i].anim;
        switch (anim) {
        case 0:
            Visibility(mid, false);
            break;
        case 3:
        case 4:
            SetMotion(mid, anim, 0.0f, true);
            break;
        default:
            SetMotion(mid, anim, 0.0f, false);
            break;
        }
        GSmodelGetPosition(ptr, &icons[i].pos);
        i++;
    }
    InitCursor(sel, 1);
}

bool WorldMap::Blendf(f32* out, f32 a, f32 b, f32 t) {
    *out = GSlerpGetLinearInterpolationFloat(a, b, t);
    return true;
}

void WorldMap::SetCameraWork(GSvec* pos, f32 a, f32 b, f32 c, f32 fov) {
    WorldMapCamera* w = cam;
    if (pos != 0) {
        w->now.pos.x = pos->x;
        w->now.pos.y = pos->y;
        w->now.pos.z = pos->z;
    }
    if (a) {
        w->now.a = a;
    }
    w->now.b = b;
    w->now.c = c;
    w->now.fov = fov;
    w->now.up.x = 0.0f;
    w->now.up.y = 1.0f;
    w->now.up.z = 0.0f;
}

void WorldMap::SetCameraNextWork(GSvec* pos, f32 a, f32 b, f32 c, f32 fov) {
    WorldMapCamera* w = cam;
    if (pos != 0) {
        w->next.pos.x = pos->x;
        w->next.pos.y = pos->y;
        w->next.pos.z = pos->z;
    }
    if (a) {
        w->next.a = a;
    }
    w->next.b = b;
    w->next.c = c;
    w->next.fov = fov;
    w->next.up.x = 0.0f;
    w->next.up.y = 1.0f;
    w->next.up.z = 0.0f;
}

bool WorldMap::IsBlending() {
    bool ret = false;
    if (cam->t >= 1.0f) {
        ret = true;
    }
    return ret;
}

void WorldMap::ControlCamera(s32) {
    f32 dt = timeGetLastFrameSec();
    cam->time = cam->time + dt;
    cam->speed = cam->acc * dt + cam->speed;
    if (cam->speed <= 0.01f) {
        cam->speed = 0.01f;
    }
    cam->t = cam->t + cam->speed;
    if (cam->t > 1.0f) {
        cam->t = 1.0f;
    }
    WorldMapCamera* c = cam;
    WorldMapCamWork* w = &c->now;
    Blendf(&w->pos.x, w->pos.x, c->next.pos.x, cam->t);
    Blendf(&w->pos.y, w->pos.y, c->next.pos.y, cam->t);
    Blendf(&w->pos.z, w->pos.z, c->next.pos.z, cam->t);
    Blendf(&w->a, w->a, c->next.a, cam->t);
    Blendf(&w->b, w->b, c->next.b, cam->t);
    Blendf(&w->fov, w->fov, c->next.fov, cam->t);
}

void WorldMap::TargetDebug(s32 sel) {
    WorldMapCamera* c = cam;
    s16 idx = _cursor_index[sel];
    c->prev = c->cur;
    cam->cur = idx;
    if (_cameraDebug != 0) {
        if (cam->prev != cam->cur) {
            SetCameraNextWork(&icons[idx].pos, 51.75f, 35.31f, 0.0f, 50.0f);
            SetCameraSpeed(1.0f);
        }
    }
}

void WorldMap::SelectIcon(s32 sel) {
    GSvec pos;
    GSvec sum;
    f32 a;
    f32 fov;
    f32 c;
    f32 b;
    s32 idx = _cursor_index[sel];
    WorldMapData* d = SearchData(idx);
    GetCameraData(d->camera, &pos, &a, &b, &c, &fov);
    PSVECAdd(&icons[idx].pos, &pos, &sum);
    SetCameraNextWork(&sum, a, b, c, fov);
    SetCameraSpeed(1.0f);
    u32 model = icons[idx].model;
    if (GetFlagData(idx) == 1) {
        SetIconMotion(idx, model, 9, 0.0f, false);
    } else {
        SetIconMotion(idx, model, 5, 0.0f, false);
    }
    InitCursor(sel, 2);
}

void WorldMap::SetCamera() {
    s32 camera;
    GSvec rot;
    GSvec off;
    GSvec eye;
    f32 p14, p10, pC, p8;
    f32 mtx[12];
    rot.x = 0.0f;
    rot.y = 0.0f;
    rot.z = 0.0f;
    timeGetLastFrameSec();
    WorldMapCamWork* w = &cam->now;
    camera = (s32)GSresGetResource(0, 0);
    GScameraGetMatrixPtr();
    GScameraGetPerspective(camera, &p8, &p14, &p10, &pC);
    GScameraSetPerspective(camera, w->fov, p14, p10, pC);
    f32 a = w->a;
    off.y = w->b;
    off.x = 0.0f;
    off.z = a;
    PSMTXRotRad(mtx, 0x59, w->c);
    PSMTXMultVec(mtx, &off, &off);
    PSVECAdd(&w->pos, &off, &eye);
    rot.y = w->c;
    f32 ang = (f32)atan2(w->b, w->a);
    rot.z = 0.0f;
    rot.x = -ang;
    GScameraLookAt(camera, &w->up, &w->pos);
    cameraSetPosition(&eye);
    cameraSetTargetPos(&w->pos);
    cameraSetRotation(&rot);
    cameraSetFov(w->fov);
}

void WorldMap::Init() {
    s16 j;
    s16 i;
    soundStopEnv(1000);
    st = (WorldMapState*)GSmemAlloc(0x94);
    memset(st, 0, 0x94);
    st->camera = GScameraGetActiveCamera();
    s32 n = *worldmapXD_data_number;
    icons = new WorldMapIconWork[n];
    cam = new WorldMapCamera;
    st->floorPush = IsFloorPush();
    j = 0;
    i = 0;
    st->moveFlag = 1;
    st->up.x = 0.0f;
    st->up.y = 1.0f;
    st->up.z = 0.0f;
    while (i < GetDataNum()) {
        WorldMapData* d = SearchData(i);
        if (d->flag == 0) {
            menuItemBiosSetSelectFlag(0x54, d->selectIndex, true);
            _cursor_index[j++] = i;
        } else if (GSflagGet(d->flag) != 0) {
            menuItemBiosSetSelectFlag(0x54, d->selectIndex, true);
            _cursor_index[j++] = i;
        } else {
            menuItemBiosSetSelectFlag(0x54, d->selectIndex, false);
        }
        i++;
    }
    _cursor_index_num = j;
    if (st->floorPush != 0) {
        u16 mapNumber = menuScriptOpenWorldMapGetMapNumber();
        st->floorID = SearchFloorID(mapNumber);
        st->cursorSel = SearchDataFloorID(st->floorID);
        st->cursorNow = st->cursorSel;
        st->angle = GetAngle(st->cursorSel);
        st->floorID = floorGetNextFloorID();
    } else {
        st->floorID = floorGetPrevFloorID();
        st->cursorSel = SearchDataFloorID(st->floorID);
        st->cursorNow = st->cursorSel;
        st->angle = GetAngle(st->cursorSel);
    }
    InitModel(st->cursorSel);
    InitCamera(st->cursorSel);
    InitRenderModule();
}

void WorldMap::InitCamera(s32 sel) {
    GSvec pos;
    f32 fov;
    f32 a;
    f32 b;
    f32 c;
    f32 p1, p2, p3;
    cameraSetType(3);
    cam->t = 0.0f;
    cam->speed = 0.0f;
    if (_cameraDebug != 0) {
        GetCameraData(0x13, &pos, &a, &b, &c, &fov);
    } else if (GetFlagData(5) != 0) {
        GetCameraData(0x13, &pos, &a, &b, &c, &fov);
    } else {
        GetCameraData(0x12, &pos, &a, &b, &c, &fov);
    }
    SetCameraNextWork(&pos, a, b, c, fov);
    memcpy(&cam->now, &cam->next, 0x28);
    SetCamera();
    cameraUpdate();
    f32 saved = fov;
    s32 camera = (s32)GSresGetResource(0, 0);
    GScameraGetMatrixPtr();
    GScameraGetPerspective(camera, &fov, &p1, &p2, &p3);
    GScameraSetPerspective(camera, saved, p1, p2, p3);
    InitModel2D(fov);
    if (st->floorPush == 0) {
        s16 idx = _cursor_index[st->cursorSel];
        WorldMapData* d = SearchData(idx);
        GetCameraData(d->camera, &pos, &a, &b, &c, &fov);
        SetCameraWork(&icons[idx].pos, a, b, c, fov);
        SetCameraSpeed(1.0f);
        SetCamera();
    }
}

void WorldMap::SetCameraSpeed(f32) {
    cam->t = 0.0f;
    cam->speed = _v0;
    cam->acc = _a0;
    cam->time = 0.0f;
}

void WorldMap::InitModel2D(f32 fov) {
    CalcModel2D(fov, true);
    s32 i;
    for (i = 0; i < GetDataNum(); i++) {
    }
}

s8 WorldMap::GetPadIndex3(f32 ang, s32 k, f32 tol) {
    u8 hit = 0;
    s8 result = -1;
    f32 lim = 6.2831855f - tol;
    f32 center = 3.1415927f * (f32)k / 4.0f;
    if (0.0f == (f32)k) {
        if (ang >= lim || ang < tol) {
            hit = 1;
        }
    } else {
        if (ang >= center - tol && ang < center + tol) {
            hit = 1;
        }
    }
    if (hit) {
        result = k;
    }
    return result;
}

struct Mtx34 { f32 m[12]; };

void WorldMap::CalcModel2D(f32 fov, bool init) {
    s32 i;
    s32 a;
    WorldMapIconWork* ia;
    void* camera = GSresGetResource(0, 0);
    f32 nk;
    f32 dist;
    f32 k;
    s32 b;
    void* view = GScameraGetMatrixPtr();
    Mtx34 proj;
    {
        f32* src = (f32*)GScameraGetProjMatrixPtr((s32)camera);
        proj.m[0] = src[0]; proj.m[1] = src[1]; proj.m[2] = src[2]; proj.m[3] = src[3];
        proj.m[4] = src[4]; proj.m[5] = src[5]; proj.m[6] = src[6]; proj.m[7] = src[7];
        proj.m[8] = src[8]; proj.m[9] = src[9]; proj.m[10] = src[10]; proj.m[11] = src[11];
    }
    Mtx34 result;
    PSMTXConcat(view, &proj, &result);
    f32 t = (f32)tan(0.017453292f * fov / 2.0f);
    k = -240.0f / t;
    nk = -k;
    i = 0;
    while (i < GetDataNum()) {
        WorldMapIconWork* ic = &icons[i];
        GSvec v;
        PSMTXMultVec(view, &ic->pos, &v);
        i++;
        f32 sx = 320.0f + (k * v.x) / v.z;
        f32 sy = 240.0f + (nk * v.y) / v.z;
        ic->sx = sx;
        ic->sy = sy;
        ic->sz = 0.0f;
    }
    a = 0;
    while (a < GetDataNum()) {
        b = 0;
        ia = &icons[a];
        while (b < GetDataNum()) {
            WorldMapIconWork* ib = &icons[b];
            if (a != b) {
                f32 ang;
                if (GetFlagData(a) == 0 || GetFlagData(b) == 0) {
                    dist = 0.0f;
                    ang = 0.0f;
                } else {
                    dist = PSVECDistance(&ia->sx, &ib->sx);
                    ang = (f32)atan2(ib->sy - ia->sy, ib->sx - ia->sx);
                    if (ang < 0.0f) {
                        ang = 6.2831855f + ang;
                    }
                }
                ia->sub[b].dist = dist;
                ia->sub[b].angle = ang;
            } else {
                ia->sub[b].dist = 0.0f;
                ia->sub[b].angle = 0.0f;
            }
            b++;
        }
        a++;
    }
    CheckPadIndex(init);
}

void WorldMap::CheckPadIndex(bool) {
    f32 angle = _checkAngleStart;
    s32 i = 0;
    f32 step = _checkAngleAdd;
    while (i < GetDataNum()) {
        WorldMapIconWork* ic = &icons[i];
        i++;
        s32 k;
        for (k = 0; k < 8; k++) {
            ic->pad[k] = -1;
        }
    }
    do {
        s32 a = 0;
        while (a < GetDataNum()) {
            int dist[8];
            s8 idx[8];
            s32 k;
            memset(dist, 0, 0x20);
            for (k = 0; k < 8; k++) {
                idx[k] = -1;
            }
            s32 b = 0;
            WorldMapIconWork* ic = &icons[a];
            while (b < GetDataNum()) {
                if (a != b && GetFlagData(a) != 0 && GetFlagData(b) != 0) {
                    for (k = 0; k < 8; k++) {
                        s8 pad = GetPadIndex3(ic->sub[b].angle, k, angle);
                        if (pad >= 0 && ic->pad[pad] < 0) {
                            f32 d = ic->sub[b].dist;
                            if (d < CURSOR_DISTANCE_MAX) {
                                if (dist[pad] == 0) {
                                    idx[pad] = b;
                                    dist[pad] = (s32)d;
                                } else if (dist[pad] > (s32)d) {
                                    idx[pad] = b;
                                    dist[pad] = (s32)d;
                                }
                            }
                        }
                    }
                }
                b++;
            }
            for (k = 0; k < 8; k++) {
                if (dist[k] != 0.0f) {
                    ic->pad[k] = idx[k];
                }
            }
            a++;
        }
        angle += step;
    } while (angle <= _checkAngle);
}

void WorldMap::PreRead(s32 index) {
    WorldMapData* d = SearchData(_cursor_index[index]);
    void* floor;
    if (st->floorPush != 0) {
        floor = floorDataBiosGetPtr(st->floorID);
    } else if (d != 0) {
        floor = floorDataBiosGetPtr(d->floorID);
    } else {
        floor = floorDataBiosGetPtr(st->floorID);
    }
    GSfsysPreRead(floorDataBiosGetFileGroupID(floor));
}

void WorldMap::MainSub() {
    s32 sel;
    s32 old = st->cursorSel;
    sel = menuOpenCustom(0x54, windowGetActiveID(), &st->cursorSel, 0, 1, 0);
    if (pWorldmap != 0) {
        if (sel < 0) {
            sel = old;
        }
        PreRead(sel);
        SelectIcon(sel);
        WorldMapData* d = SearchData(_cursor_index[sel]);
        menuClose(0x54);
        menuCloseSync(0x54, 1);
        if (sel != old) {
            st->flag90 = 1;
            heroMovePoolCounter(2, 0x28);
            moveDemo(old, sel);
        }
        if (sel != old) {
            fadeSet(3, 1.0f);
            do {
                RenderMoveDemoModel();
                GSthreadSwitch();
            } while (fadeCheck(0) != 0);
            if (st->scooterType >= 4) {
                GSsndStopNow(0x5DC);
            } else {
                GSsndStopNow(0x5B2);
            }
            releaseOffscreenData();
        } else {
            do {
                MainControl(sel);
                GSthreadSwitch();
            } while (IsBlending() == 0);
        }
        GSthreadSwitch();
        if (glow != 0) {
            delete glow;
            glow = 0;
        }
        if (d != 0) {
            floorLink(d->floorID, 0);
            if (st->flag90 != 0) {
                floorSetFadeScript(0, 0x05960008);
            }
            SetFlagData(_cursor_index[sel]);
            return;
        }
        floorLink(st->floorID, 0);
    }
}

void WorldMap::MainSub2() {
    menuOpenCustom(0x54, windowGetActiveID(), &st->cursorSel, 0, 1, 0);
    if (pWorldmap != 0) {
        PreRead(0);
        menuClose(0x54);
        menuCloseSync(0x54, 1);
        menuScriptSetOpenWorldMapFlag(0);
        msgctrlSetValue(0x59, 0x1772);
        GSfloorPop();
    }
}

u8 WorldMap::IsFloorPush() { return menuScriptGetOpenWorldMapFlag(); }

void WorldMap::Main() {
    if (st->floorPush != 0) {
        MainSub2();
        return;
    }
    MainSub();
}

static void* _cameraPlayAnime(u32 camera, s32 frame, bool loop) {
    void* cam = GSresGetResourceAllGroup(camera);
    GScameraSetAnimIndex(cam, 0);
    if (loop) {
        GScameraSetAnimType(cam, 1);
    } else {
        GScameraSetAnimType(cam, 0);
    }
    GScameraSetAnimRate(cam, 0.5f);
    GScameraSetAnimFrame(cam, (f32)frame);
    GScameraStartAnimation(cam);
    return cam;
}

void WorldMap::setNullModel() {
    u32 model = st->anime->model;
    u32 res = st->anime->modelRes;
    s32 group = floorGetCurrentGroupID();
    st->nullRes = res;
    st->nullModel = model;
    SetModel(group, res, false);
    GSgfxLayerID id = {0, 0, 0};
    SetLayerID(st->nullModel, 1, &id);
    GSmodelSetBoundCheck(GSresGetResourceAllGroup(st->nullModel), false);
}

s32 WorldMap::getScooterType() {
    Hero* hero;
    s32 type = 0;
    hero = (Hero*)savedataGetStatus(0, 2);
    if (hero != 0) {
        u32 high;
        if (GSflagGet(0x3C4) < flag_etc[0x44].flagValue) {
            high = 0;
        } else {
            high = 1;
        }
        u8 follower;
        if (hero->getFollowerID() != 1) {
            follower = 0;
        } else {
            follower = 1;
        }
        switch (hero->getHeroStyle()) {
        case 0:
            if (high != 0) {
                type = 4;
            } else if (follower != 0) {
                type = 1;
            } else {
                type = 0;
            }
            break;
        case 2:
            if (high != 0) {
                type = 5;
            } else if (follower != 0) {
                type = 3;
            } else {
                type = 2;
            }
            break;
        case 1:
            if (high != 0) {
                type = 6;
            }
            break;
        }
    }
    return type;
}

u32 WorldMap::readScooter() {
    if (st->floorPush != 0) {
        return 0;
    }
    st->scooter = &_mapScooterData[st->scooterType];
    u32 model = st->scooter->model;
    u32 res = st->scooter->res;
    while (!GSfsysWait(0x9E6)) {
        GSthreadSwitch();
    }
    GSfsysFree(0x9E6);
    SetModel(0x9E6, res, false);
    ObjectVisibility(res, true);
    st->scooterRes = res;
    st->scooterModel = model;
    SetMotion(model, 8, 0.0f, true);
    if (st->nullModel != 0 && st->scooterModel != 0) {
        ModelAttach(st->scooterModel, st->nullModel, st->anime->bone, (GSattachMode)7);
    }
    GSgfxLayerID id = {0, 0, 0};
    SetLayerID(st->scooterModel, 1, &id);
    if (st->scooterType >= 4) {
        st->partRes[0] = 0x213E1400;
        st->partRes[1] = 0x213D1400;
        st->partRes[2] = 0x213D1400;
        st->part[0] = SetModelPartPaticle(st->scooterModel, st->partRes[0], st->scooter->p0, (GSattachMode)4, false, true, false);
        st->part[1] = SetModelPartPaticle(st->scooterModel, st->partRes[1], st->scooter->p1, (GSattachMode)4, false, true, false);
        st->part[2] = SetModelPartPaticle(st->scooterModel, st->partRes[2], st->scooter->p2, (GSattachMode)4, false, true, false);
    } else {
        st->partRes[0] = 0x20D01400;
        st->partRes[1] = 0x20CF1400;
        st->partRes[2] = 0x20CF1400;
        st->part[0] = SetModelPartPaticle(st->scooterModel, st->partRes[0], st->scooter->p0, (GSattachMode)4, false, true, false);
        st->part[1] = SetModelPartPaticle(st->scooterModel, st->partRes[1], st->scooter->p1, (GSattachMode)4, false, true, false);
        st->part[2] = 0;
    }
    GSmodelSetBoundCheck(GSresGetResourceAllGroup(model), false);
    return model;
}

static void* _cameraPlayAnime(u32 camera, s32 frame, bool loop);

void WorldMap::moveDemo(s32 from, s32 to) {
    u16 pick = HSD_Rand() % 2;
    glow = new glowEffect;
    GSgfxVideoSetLockFrameRate(1);
    WorldMapIconWork* ia = &icons[_cursor_index[to]];
    WorldMapIconWork* ib = &icons[_cursor_index[from]];
    f32 ang = atan2(ia->sy - ib->sy, ia->sx - ib->sx);
    if (ang < 0.0f) {
        ang = 6.2831855f + ang;
    }
    if (!(ang >= 1.5707964f && ang < 4.712389f)) {
        pick += 2;
    }
    WorldMapData* d = SearchData(_cursor_index[from]);
    st->mdlRes = d->motion;
    if (d->motion == 0x1B4A0400) {
        st->mdl50 = 0x1B4A1000;
        st->mdl54 = 0x1B4A1001;
        st->mdl58 = 0x1B4A1002;
        st->mdl5C = 0x1B4A1603;
        st->anime = &_animeTable[0][pick];
    } else {
        st->mdl50 = 0x1FDA1000;
        st->mdl54 = 0x1FDA1001;
        st->mdl58 = 0x1FDA1002;
        st->mdl5C = 0x1FDA1602;
        st->anime = &_animeTable[1][pick];
    }
    setNullModel();
    readScooter();
    GSthreadSwitch();
    SetModel(floorGetCurrentGroupID(), st->mdlRes, true);
    GSthreadSwitch();
    ObjectVisibility(st->mdlRes, true);
    st->fade = 1.0f;
    initializeOffscreenData();
    if (st->mdl54 == 0x1B4A1001) {
        if (glow != 0) {
            glow->strength = 0.0f;
            glow->width = _glowwidth;
            glow->blend = _glowblend;
            glow->normalize = _glownormalize;
            glow->method = _glowmethod;
            glow->samples = _glowsamples;
            glow->Start();
        }
    }
    void* shadowModel = GSresGetResourceAllGroup(st->scooter->model);
    void* surface = GSresGetResourceAllGroup(st->mdl58);
    void* light = GSresGetResourceAllGroup(st->mdl5C);
    void* surfaces = surface;
    GSmodelSetShadowFlags(shadowModel, 1);
    GSmodelSetShadowLight(shadowModel, light);
    GSmodelSetShadowSurface(shadowModel, 1, &surfaces);
    SetMotion(st->nullModel, 0, 0.0f, _AnimeLoop);
    f32 total = GetAnimeFrameCount(st->nullModel, 0);
    st->moveCamera = (s32)_cameraPlayAnime(st->anime->camera, 0, _AnimeLoop);
    if (st->scooterType >= 4) {
        GSsndPlayNow(0x5DC);
    } else {
        GSsndPlayNow(0x5B2);
    }
    for (;;) {
        f32 dt = GetLastTime() / _testFadeTime;
        MainControl(to);
        RenderMoveDemoModel();
        if (st->fade != 0.0f) {
            st->fade -= dt;
            if (st->fade < 0.0f) {
                st->fade = 0.0f;
                ObjectVisibility(0x18530200, _testVisibility);
            }
        }
        if (_testExit && total - 60.0f < GetAnimeFrame(st->nullModel)) {
            break;
        }
        GSthreadSwitch();
    }
}

void WorldMap::RenderMoveDemoModel() {
    if (pWorldmap != 0) {
        s32 camera = st->moveCamera;
        if (st->mdl54 == 0x1B4A1001) {
            if (glow != 0) {
                glow->strength = _glowstrngth;
            }
        }
        renderOffscreenData(st->fade);
        GSgfxLayerFindByID(0);
        GScameraIsAnimating(camera);
        GSmodelSetRenderCamera(GetModelPtr(st->mdl54), camera);
        GSmodelSetRenderCamera(GetModelPtr(st->mdl58), camera);
        GSmodelSetRenderCamera(GetModelPtr(st->scooterModel), camera);
        GSmodelSetRenderCamera(GetModelPtr(st->nullModel), camera);
        s32 i;
        for (i = 0; i < 3; i++) {
            if (st->part[i] != 0) {
                GSresGetResourceAllGroup(st->partRes[i]);
                GSparticleGeneratorSetCamera(st->part[i], camera);
            }
        }
        GScameraGetAnimFrame(camera);
    }
}

void WorldMap::Release() {
    if (st->scooterModel != 0) {
        s32 i;
        for (i = 0; i < 3; i++) {
            if (st->part[i] != 0) {
                DetachModelPartPaticle(st->part[i], true);
            }
        }
        ModelDetach(st->scooterModel);
        if (_release_flag != 0 && GSresGetResourceAllGroup(st->scooterModel) != 0) {
            UnloadModel(0x9E6, st->scooter->res);
            GSresFreeResourceAllGroup(st->scooterRes);
        }
    } else if (st->floorPush == 0) {
        while (!GSfsysWait(0x9E6)) {
            GSthreadSwitch();
        }
        GSresFreeResource(0x9E6, st->scooter->res);
    }
    if (st != 0) {
        GSmemFree(st);
        st = 0;
    }
    if (icons != 0) {
        delete[] icons;
    }
    if (cam != 0) {
        delete cam;
    }
}

void WorldMap::ControlPad(tagWINDOW_WORK* window) {
    windowGetKeyInfo();
    u16 key = windowGetKeyRepeat();
    s16 index = _cursor_index[st->cursorNow];
    s32 dir = -1;
    if (fadeCheck(0) == 0 && cursorMoving != 1 && st->moveFlag != 1) {
        GetModelID(index);
        if (key == 8) {
            dir = 0;
        } else if (key == 10) {
            dir = 1;
        } else if (key == 2) {
            dir = 2;
        } else if (key == 6) {
            dir = 3;
        } else if (key == 4) {
            dir = 4;
        } else if (key == 5) {
            dir = 5;
        } else if (key == 1) {
            dir = 6;
        } else if (key == 9) {
            dir = 7;
        }
        WorldMapIconWork* ic = &icons[index];
        if (dir >= 0) {
            s8 next = ic->pad[dir];
            if (next >= 0) {
                s16 i;
                for (i = 0; i < _cursor_index_num; i++) {
                    if (next == _cursor_index[i]) {
                        st->cursorNow = i;
                        window->cursor = i;
                        SetCursorPosition(i, true);
                        return;
                    }
                }
            }
        }
    }
}

void WorldMap::Cursor(tagWINDOW_WORK* window) {
    if (_DebugControl != 0) {
        menuCursorNormal(window, 1);
        return;
    }
    if (st->floorPush == 0) {
        ControlPad(window);
    }
}

void WorldMap::Button(tagWINDOW_WORK* window) {
    if (cursorMoving != 1) {
        menuButtonNormal(window);
    }
}

void WorldMap::InitRenderModule() {}

s32 WorldMap::GetNowCursor(tagWINDOW_WORK* window) {
    if (_DebugControl != 0) {
        return window->cursor;
    }
    return st->cursorNow;
}

void WorldMap::MainControl(s32 now) {
    ControlCamera(now);
    TargetDebug(now);
    SetCamera();
    CalcModel2D(cam->now.fov, false);
    ControlCursor(now);
    CheckIconAnime(now);
    CheckCursorAnime();
}

s32 WorldMap::Ctrl(tagWINDOW_WORK* window) {
    s32 now = GetNowCursor(window);
    switch (window->state) {
    case 0:
        if (st->floorPush == 0) {
            st->scooterType = getScooterType();
            st->scooter = &_mapScooterData[st->scooterType];
            GSfsysReadID(0x9E6, st->scooter->res);
        }
        break;
    case 2:
        MainControl(now);
        break;
    case 3:
    default:
        break;
    }
    return 0;
}

void WorldMap::CallBackFunc(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s32 now = GetNowCursor(window);
    int id = sprite->id;
    switch (id) {
    case 0x395:
        SetSnap(now, window, sprite);
        break;
    case 0x3A4:
        SetInfo(now, window, sprite);
        break;
    case 0x38F: case 0x390: case 0x391: case 0x392: case 0x393: case 0x394:
    case 0x3A5: case 0x3A6:
        if (st->floorPush != 0) {
            winSpriteSetDisp(sprite, false);
        } else {
            winSpriteSetDisp(sprite, true);
        }
        break;
    case 0x5C4:
        break;
    case 0x147: case 0x148: case 0x149: case 0x14A: case 0x14B: case 0x14C: case 0x14D:
    case 0x14E: case 0x14F: case 0x150: case 0x151: case 0x152: case 0x153: case 0x154:
    case 0x38C: case 0x38D: case 0x38E:
    case 0x5E1:
        if (_mojiOn != 0) {
            if (menuItemBiosGetSelectFlag(0x54, (u32)(id)) != 0) {
                u32 ids[18] = {
                    0x147, 0x148, 0x149, 0x14A, 0x14B, 0x14C, 0x14D, 0x14E, 0x14F, 0x150, 0x151, 0x152, 0x153, 0x154, 0x5E1, 0x38C, 0x38D, 0x38E,
                };
                s32 i;
                s32 j;
                s32 found = -1;
                for (i = 0; i < 18; i++) {
                    if (sprite->id == ids[i]) {
                        found = 0;
                        for (j = 0; j < _cursor_index_num; j++, found++) {
                            if (i == _cursor_index[j]) break;
                        }
                        break;
                    }
                }
                if (now == found) {
                    sprite->r = 0x22;
                    sprite->g = 0x44;
                    sprite->b = 0xEE;
                } else {
                    sprite->r = 0xFF;
                    sprite->g = 0xFF;
                    sprite->b = 0xFF;
                }
                winSpriteSetDisp(sprite, true);
            } else {
                winSpriteSetDisp(sprite, false);
            }
        } else {
            winSpriteSetDisp(sprite, false);
        }
        break;
    }
}

extern "C" {
s32 menuWorldMapMX(tagWINDOW_WORK* w, tagSPRITE_WORK* s) {
    if (pWorldmap != 0) {
        pWorldmap->CallBackFunc(w, s);
    }
    return 0;
}
}

extern "C" {
void menuWorldMapCursor(tagWINDOW_WORK* w) {
    if (pWorldmap != 0) {
        pWorldmap->Cursor(w);
    }
}
}

extern "C" {
void menuWorldMapButton(tagWINDOW_WORK* w) {
    if (pWorldmap != 0) {
        pWorldmap->Button(w);
    }
}
}

extern "C" {
void menuWorldMapMXInit(void) {
    pWorldmap = new WorldMap;
    pWorldmap->Init();
}
}

extern "C" {
void menuWorldMapMXMain(void) { pWorldmap->Main(); }
}

extern "C" {
void menuWorldMapMXExit(void) {
    delete pWorldmap;
    pWorldmap = 0;
}
}

extern "C" {
s32 menuWorldMapMXCtrl(tagWINDOW_WORK* w) {
    if (pWorldmap != 0) {
        pWorldmap->Ctrl(w);
    }
    return 0;
}
}

extern "C" {
void menuWorldMapMXDebug(void) {
    s32 i;
    for (i = 0; i < *worldmapXD_data_number; i++) {
        if (worldmapXD_data[i].flag != 0) {
            GSflagSet(worldmapXD_data[i].flag, 2);
        }
    }
}
}
