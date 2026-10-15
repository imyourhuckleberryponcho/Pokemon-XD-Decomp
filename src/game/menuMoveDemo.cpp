// Kyogre travel sequence; verified against the GXXE01 retail executable.
#include <dolphin/types.h>
#pragma peephole off
struct _GSparticleGen;
enum GSattachMode { Attach0 };
class WorldMapModel {
public:
    WorldMapModel() : mOffscreenData(0) {}
    ~WorldMapModel() { if (mOffscreenData) releaseOffscreenData(); }
    void releaseOffscreenData();
    void SetModel(u32,u32,bool);
    void SetMotion(u32,s16,f32,bool);
    f32 GetAnimeFrameCount(u32,u32);
    f32 GetAnimeFrame(u32);
    void ModelAttach(u32,u32,s32,GSattachMode);
    void ModelDetach(u32);
    _GSparticleGen* SetModelPartPaticle(u32,u32,s32,GSattachMode,bool,bool,bool);
    void DetachModelPartPaticle(_GSparticleGen*,bool);
    void* mOffscreenData;
};
struct GSgfxLayer;
enum GSgfxLayerPass { GS_GFX_LAYER_PASS_0 };
class GSeffect {
public:
    bool active,visible; GSeffect* next;
    bool Start();
    virtual bool _start(); virtual void _stop(); virtual bool _update(f32);
    virtual void _render(GSgfxLayer*,GSgfxLayerPass); virtual void _fastRender(); virtual ~GSeffect();
};
class glowEffect : public GSeffect {
public:
    glowEffect();
    virtual ~glowEffect();
    virtual void _render(GSgfxLayer*,GSgfxLayerPass);
    f32 strength; u8 width,blend,normalize,method,samples;
};
struct DemoState {
    u32 reserved; s32 type; u32 group,modelResource,model,sceneResource,scene;
    s32 bone; u32 camera; f32 frames; void* cameraPtr; _GSparticleGen* particles[4];
};
class kyogreMoveDemo : public WorldMapModel {
public:
    ~kyogreMoveDemo(); kyogreMoveDemo(); void Release(); void Main(); u32 GetNextFloorID();
    void Init(); void* cameraPlay(u32,s32,bool); void playBGM(u16);
    glowEffect* glow; DemoState* state;
};
struct WorldMapData { u8 pad[0x118]; u32 returnFloor; u8 pad11c[0x1D8-0x11c]; s32 flag; u8 pad1dc[0x1F0-0x1dc]; u32 nextFloor; };
extern "C" {
extern WorldMapData* worldmapXD_data;
u32 GSflagGet(s32); void GSflagSet(s32,u32); void GSthreadSwitch();
void fadeSet(s32,f32); s8 fadeCheck(s32); void floorLink(u32,s32); void floorSetFadeScript(s32,u32);
void* memset(void*,int,u32); void soundStopEnv(s32); void GSsndPlayNow(u32);
s32 floorGetCurrentGroupID(); void GSgfxVideoSetLockFrameRate(s32);
void* GSresGetResourceAllGroup(u32); void GSmodelSetBoundCheck(void*,bool);
void cameraSetType(s32); void cameraPlayAnime(s32,u32,bool,f32);
void GScameraGetPerspective(void*,f32*,f32*,f32*,f32*); void GScameraSetPerspective(void*,f32,f32,f32,f32);
void soundOpenPlay(u32,s32,s32); void GSsndStopNow(u32); void floorChange(u32);
kyogreMoveDemo* pMDemo;
}
static s32 _movdemo_type;
static u8 _glowmethod;
static bool _AnimeLoop=true, _testExitFlag=true;
static f32 _glowstrngth=1.f;
static u8 _glowwidth=20, _glowblend=1, _glownormalize=1, _glowsamples=1;
static f32 _fadeFrame=40.f, _fadeTime=.7f;


kyogreMoveDemo::~kyogreMoveDemo() { Release(); }
kyogreMoveDemo::kyogreMoveDemo() { Init(); }
void kyogreMoveDemo::Release() {
    if (pMDemo) {
        if (state->model) {
            for (int i=0;i<4;i++) if (state->particles[i]) DetachModelPartPaticle(state->particles[i],true);
            ModelDetach(state->model); ModelDetach(0x21AC1000);
        }
        if (glow) delete glow;
        if (state) { delete state; state=0; }
    }
}
void kyogreMoveDemo::Main() {
    if (pMDemo) {
        for (;;) {
            if (_testExitFlag && state->frames-_fadeFrame < GetAnimeFrame(state->scene)) break;
            GSthreadSwitch();
        }
        fadeSet(3,_fadeTime);
        do { GSthreadSwitch(); } while (fadeCheck(0));
        u32 floor=GetNextFloorID();
        if (floor) {
            if (state->type==1) floorLink(floor,10); else floorLink(floor,0);
            floorSetFadeScript(0,0x05960008);
        }
    }
}
u32 kyogreMoveDemo::GetNextFloorID() {
    u32 floor=0;
    switch (state->type) {
    case 1: floor=worldmapXD_data->returnFloor; break;
    case 0: {
        s32 flag=worldmapXD_data->flag;
        if (GSflagGet(flag)<2) { GSflagSet(flag,2); floor=0x56; }
        else floor=worldmapXD_data->nextFloor;
        break;
    }
    }
    return floor;
}
void kyogreMoveDemo::Init() {
    f32 fov,aspect,nearClip,farClip;
    state=0; state=new DemoState; memset(state,0,sizeof(DemoState));
    glow=0; glow=new glowEffect;
    state->type=_movdemo_type;
    soundStopEnv(1000);
    if (state->type==0) playBGM(0x53D);
    GSsndPlayNow(0x5B8);
    state->modelResource=0x1B870400; state->model=0x1B871000;
    state->group=floorGetCurrentGroupID(); GSgfxVideoSetLockFrameRate(1);
    switch (state->type) {
    case 1: state->sceneResource=0x21200400; state->scene=0x21201000; state->bone=1; state->camera=0x211E1800; break;
    case 0: state->sceneResource=0x21210400; state->scene=0x21211000; state->bone=1; state->camera=0x211F1800; break;
    }
    if (glow) {
        glow->strength=_glowstrngth; glow->width=_glowwidth; glow->blend=_glowblend;
        glow->normalize=_glownormalize; glow->method=_glowmethod; glow->samples=_glowsamples; glow->Start();
    }
    SetModel(state->group,state->sceneResource,false);
    GSmodelSetBoundCheck(GSresGetResourceAllGroup(state->scene),false);
    SetModel(state->group,0x21AC0400,false);
    GSmodelSetBoundCheck(GSresGetResourceAllGroup(0x21AC1000),false);
    SetMotion(0x21AC1000,8,0.f,true);
    SetModel(state->group,state->modelResource,false);
    GSmodelSetBoundCheck(GSresGetResourceAllGroup(state->model),false);
    ModelAttach(state->model,state->scene,state->bone,(GSattachMode)7);
    SetMotion(state->model,8,0.f,true);
    ModelAttach(0x21AC1000,0x1B871000,1,(GSattachMode)4);
    switch (state->type) {
    case 1:
        state->particles[0]=SetModelPartPaticle(state->model,0x21391400,5,(GSattachMode)1,false,true,false);
        state->particles[1]=SetModelPartPaticle(state->model,0x213A1400,19,(GSattachMode)1,false,true,false);
        state->particles[2]=SetModelPartPaticle(state->model,0x213B1400,26,(GSattachMode)1,false,true,false);
        state->particles[3]=SetModelPartPaticle(state->model,0x213C1400,12,(GSattachMode)1,false,true,false); break;
    case 0:
        state->particles[0]=SetModelPartPaticle(state->model,0x21DE1400,5,(GSattachMode)1,false,true,false);
        state->particles[1]=SetModelPartPaticle(state->model,0x21DF1400,19,(GSattachMode)1,false,true,false);
        state->particles[2]=SetModelPartPaticle(state->model,0x213B1400,26,(GSattachMode)1,false,true,false);
        state->particles[3]=SetModelPartPaticle(state->model,0x213C1400,12,(GSattachMode)1,false,true,false); break;
    }
    SetMotion(state->scene,0,0.f,_AnimeLoop);
    state->frames=GetAnimeFrameCount(state->scene,0);
    state->cameraPtr=cameraPlay(state->camera,0,_AnimeLoop);
    GScameraGetPerspective(state->cameraPtr,&fov,&aspect,&nearClip,&farClip);
    farClip=50000.f;
    GScameraSetPerspective(state->cameraPtr,fov,aspect,nearClip,50000.f);
}
void* kyogreMoveDemo::cameraPlay(u32 camera,s32 frame,bool loop) {
    cameraSetType(4); cameraPlayAnime(state->group,camera,loop,(f32)frame);
    return GSresGetResourceAllGroup(camera);
}
void kyogreMoveDemo::playBGM(u16 bgm) { soundOpenPlay(bgm,0,127); }
#pragma dont_inline on
extern "C" {
void menuMoveDemoExit() { GSsndStopNow(0x5B8); delete pMDemo; pMDemo=0; }
void menuMoveDemoMain() { pMDemo->Main(); }
void menuMoveDemoInit() { pMDemo=new kyogreMoveDemo; }
void menuMoveDemo(s32 type) { _movdemo_type=type; floorChange(0x3A9); }
}
