#include <game/gcdata.h>
#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/gcptr.h>
#include <game/statusval.h>
#include <game/miscTables.h>
#include <dolphin/gx/GXVert.h>

#pragma peephole off
#pragma pool_strings off

extern "C" {
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
}

struct Pokemon {
    u8 data[0xC4];
    u16 getPokemonDataId() const;
    char* getNicknamePtr();
    bool isDarkPokemon() const;
};

struct GSvec {
    f32 x, y, z;
    GSvec() {}
    GSvec(f32 _x, f32 _y, f32 _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    GSvec& operator=(const GSvec& o)
    {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
};

struct GSgfxColAu8 {
    union {
        u32 rgba;
        u8 v[4];
    };
};
struct GSColor4 {
    u8 r, g, b, a;
};

struct GSpart;
struct GSmodel;
struct GSlight;
struct GSmaterial;
struct GStexture;
struct GSgfxVF;
struct GSgfxLight;
struct GSmtx;
enum GSpartMixType { GSpartMixType0 };
enum GSgfxLayerID {};
enum GSgfxLayerOffset {};
enum GSgfxLayerType {};
enum GSgfxCunitAlpha {};
enum GSgfxCunitSrc {};
enum GSgfxLightType {};
enum GSgfxDiffuseFunc {};
enum GSgfxTgenFunc {};
enum GSgfxTgenSrc {};
enum MENU_POKEMON_CB_TYPE_UNUSED {};

template <typename T>
struct PocketVec {
    T x, y;
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};
struct BlendState {
    u8 pad[0xbc];
};
struct GSmtx44 {
    f32 m[4][4];
};

#define U8_AT(o) (*(u8*)((u8*)this + (o)))
#define U32_AT(o) (*(u32*)((u8*)this + (o)))

#include <game/gsgfxlayer.h>
#include <game/gsmaterialview.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void cunitChannelGen(u8 chan, GSgfxCunitAlpha alpha, GSgfxCunitSrc src0, GSgfxCunitSrc src1, u32 lights,
                         GSgfxLight** light, GSgfxLightType lightType, GSgfxDiffuseFunc diffuse);
    void tgenFunc(u8 index, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* mtx, bool normalize, GSmtx* post);
    void SetTextureCopy(GStexture* tex, bool clear, u8* clearColor);
    void SetClearFlags(bool color, bool alpha, bool depth);
    void beginSurface(u16 count);
    void endSurface();

    inline void mark(u32 sum, u32 off, u32 bit)
    {
#ifdef __MWERKS__
        U32_AT(off) |= bit;
        U32_AT(0x16a8) |= sum;
        U32_AT(off + 0xb8) |= bit;
        U32_AT(0x1760) |= sum;
#else
        GSL_IN(this, u32, dirty[0], 0x16a8, off) |= bit;
        dirty[0].groups |= sum;
        GSL_IN(this, u32, dirty[1], 0x1760, off + 0xb8) |= bit;
        dirty[1].groups |= sum;
#endif
    }

};

class GSgfxLayerConfig {
public:
    static void Remove(GSgfxLayerID id);
    static void Move(GSgfxLayerID id, GSgfxLayerID relative, GSgfxLayerOffset offset);
    static GSgfxLayerID Add(char* name, u32 width, u32 height, u32 count, GSgfxLayerType type, bool clearColor,
                            bool clearAlpha, bool clearDepth, GSgfxLayerID relative, GSgfxLayerOffset offset);
};

struct SceneData {
    u32 pad0[2];
    gc_ptr32(gc_ptr32(void)) lights;
};

class CMetaMenu;
struct CMenuGlobalState {
    s32 f0;
    s32 mode;
    s32 next;
};

struct VP {
    u32 id;
    u32 value;
};

struct CInfoWindow {
    s32 windowId;
    s32 itemId;
    u8 opened;
    bool isMsg;
    s32 msgId;
    VP values[4];
    u16 buttons;

    void close();
    void draw();
    void exec(CMetaMenu&, u32, bool);
    void init(s32, u32);
    void open(u32, bool);
    void setMsgCtrlValue(u32, u32);
};

struct CState {
    s32 current, next, prev;
    u32 count;
    f32 time;
    f32 dt;
    u32 work[0x10];
    u32 work2[0x10];
    s32 w98, w9c, wa0;
    u8 padA4[4];
    void update();
    void init();
    inline void change(s32 n)
    {
        next = n;
        memset(work, 0, 0x40);
    }
};

struct CKeyInfo {
    u8 pad0[4];
    u16 trg;
    u16 rep;
    u8 pad8[0x12];
};

class CMetaMenu {
public:
    s32 fadeTime;
    s32 fadeState;
    s32 pad8;
    u32 seId;
    u8 pad10[0xC];
    s32 windowIds[64];
    void (*windowFuncs[64])(CMetaMenu*, s32);
    s32* windowTable;
    CKeyInfo keyInfo;
    s32 repeat;
    u16 lastOn;
    u8 tutorialMode;
    CInfoWindow info;
    CState state;
    u64 time;
    CMenuGlobalState* gstate;
    u8 updated;
    u8 pad32D;
    u16 cachedInput;

    CMetaMenu() {}
    virtual void drawAll() = 0;
    virtual bool isAnimationStateNone() { return true; }
    virtual void updateAll();
    virtual void tutorialExitKick() {}

    s32 actionMenu(u32*, int, s32, s32, s32);
    void aButtonWait();
    f32 calcAnimationTimeRate0to1(f32);
    CKeyInfo* getKeyInfo();
    void localWindowCreateAll();
    void localWindowDeleteAll();
    void localWindowDrawAll();
    void localWindowSetTable(s32*);
#ifdef __MWERKS__
    static void systemFadeInKick();
#else
    static void systemFadeInKick();
#endif
    void systemFadeOutKeepAfterFloorPush();
    void systemFadeOutSetAndWait(f32);
    void systemFadeWaitToEnd();
    void waitAtTime(f32);
    static s32 defautlLocalWindowOpenTable[];
};

struct CReliveStage {
public:
    u8 pad[0x3D4];
    s8 hit;
    s32 getState();
    s32 getTempo();
    s32 getDancerQuantity();
    Pokemon* getDancerPointer(s32);
    Pokemon* getVisitorPointer();
    bool isReliveReady();
    void pickupVisitor(Pokemon&);
};

struct CReliveHall {
public:
    static CReliveHall* getPointer();
    CReliveStage* getStage(s32);
    bool isReliveReadyPokemonExist();
};

struct PCBOX {
    static PCBOX* getPointer();
    bool isPokemonFull();
#ifdef __MWERKS__
    void addPokemonLastWatchBox(Pokemon*);
#else
    bool addPokemonLastWatchBox(Pokemon* p);
#endif
};

struct ModelSlot {
    s32 id;
    GSmodel* model;
    void* seq;
};

extern "C" {
void GSflagSet(u32, u32);
void GSfsysReadWait(u32);
void GSfsysFree(u32);
void GSresFreeGroup(u32);
void* GSresGetResourceAllGroup(u32);
s32 scriptModelOpen(s32);
void scriptModelClose(s32);
void GSmodelSetRenderLayer(GSmodel*, s32, s32*);
void GSmodelSetAnimIndex(GSmodel*, u32);
void GSmodelSetAnimType(GSmodel*, s32);
void GSmodelStartAnimation(GSmodel*);
void GSmodelGetAnimIndex(GSmodel*, u32*, u32*);
bool GSmodelHasAnimationEnded(GSmodel*);
void GSmodelSetVisibility(GSmodel*, u8);
void GSmodelSetPosition(GSmodel*, GSvec*);
void GSmodelSetRotation(GSmodel*, GSvec*);
void GSmodelSetScale(GSmodel*, GSvec*);
void GSmodelSetAnimRate(GSmodel*, f32);
void GSmodelFree(GSmodel*);
void GSmodelDisableModulation(GSmodel*);
GSpart* GSmodelGetPart(GSmodel*, s32);
void GSmodelAttachToGSpart(GSmodel*, GSpart*, s32, u8, u8);
void GSmodelSetForceUseFractionalFramesFlag(GSmodel*, u8);
void GSmodelSetSkipFractionalFramesFlag(GSmodel*, u8);
void GSpartFree(GSpart*);
void GSpartRegisterAnimMix(GSpart*, s32, s32, f32 (*)(GSpart*, GSpartMixType, void*, GSvec*), void*);
void GSmaterialSetModulate(GSmaterial*, void*);
void GSmaterialEnableExtension(GSmaterial*, u32);
GSlight* GSlightLoad(void*);
void GSlightFree(GSlight*);
void GSlightSetActive(GSlight*, u8);
u8 GSlightCanAnimate(GSlight*);
void GSlightSetAnimIndex(GSlight*, u32);
void GSlightSetAnimRate(GSlight*, f32);
void GSlightStartAnimation(GSlight*);
void cameraPlayAnime(u32, u32, u8, f32);
u8 cameraSetType(u8);
void* floorOpenObject(u32);
u32 floorGetCurrentGroupID();
u32 floorReadMakeLightResID(u32);
void* peopleInfoBiosGetPtr(u32);
s32 peopleInfoBiosGetNeckIndex(void*);
void* Sequence_CreateNull();
void* Sequence_LoadWaza(void*, u16, u8, s32);
void* Sequence_LoadPokemon(u16, u32, u32);
GSmodel* Sequence_GetGSmodel(void*);
void Sequence_SetVisibility(void*, u8);
void Sequence_SetPosition(void*, GSvec*);
void Sequence_SetRotation(void*, GSvec*);
void Sequence_SetScale(void*, GSvec*);
void Sequence_DoAnimation(void*, PCARG(u8, int));
void Sequence_Free(void*);
void WazaSequence_Start(void*, s32);
void WazaSequence_Free(void*);
bool pokemonIsJoutaiDataId(Pokemon*, u16);
u32 soundGetBGMID();
void soundStop(u32, s32);
void GSthreadSwitch();
u32 windowGetKeyTrg();
u16 windowGetKeyOn();
void* GSmemAllocClr(u32);
void GSmemFree(void*);
void GScharCpy(char*, char*);
GStexture* GStextureCreate(u16, u16, s32, s32, u8);
void GStextureFree(GStexture*);
GSgfxLayer* GSgfxLayerFindByID(GCsptr);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void GSmtx44Ortho(f32*, f32, f32, f32, f32, f32, f32);
void* HSD_ArchiveGetPublicAddress(void*, const char*);
void spriteSetOffset(s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void menuDrawReliveUpdate();
u32 menuModelGetPokemonAnimationIndexByPointer(Pokemon*);
StatusU32 pokemonGetStatus(Pokemon*, u32, u16, u32);
}
extern "C" GSmtx44 mtxIdent;

extern "C" ReliveHallData* relivehall_data;
extern "C" s32 pcReliveHallSoundTbl[5];
extern GSgfxColAu8 relivehallAisyou2ColorTbl[3];
extern const GSgfxColAu8 GSgfxColAu8_Black;

void menuPtPlaySe(u32);
void menuPtPlayBgm(u32);
void relivehallSetLastViewStage(s32);
s32 relivehallGetLastViewStage();
void relivehallDraw9StageNumber(int);
void relivehallDraw9StageInfo(int);
void relivehallDrawStageInfoCursor(s32, int, int, Pokemon*, bool);
int reliveHallPokemonToAisyou(Pokemon*, Pokemon*);
void* reliveCeremonyFromHologram(Pokemon*, u32);
f32 menuGetPokemonScale(GCuptr, int);
void menuModelGetPkxRndFromPokemonForSeqenceLoad(u32&, u16&, Pokemon*);

inline void* operator new(size_t, void* p) { return p; }

namespace {

s32 localWindowTable[6] = { 0x71, 0x72, 0x88, 0xD0, 0x87, 0 };

class CMenuHologram;
CMenuHologram* pMenuHologram;

static inline int animIndexOf(GSmodel* m)
{
    u32 idx;
    if (m == 0) {
        return 0;
    }
    GSmodelGetAnimIndex(m, &idx, 0);
    return idx;
}

static inline void startAnimNext(ModelSlot* s, u32 idx)
{
    if (s->model != 0) {
        GSmodelSetAnimIndex(s->model, idx);
        GSmodelSetAnimType(s->model, 1);
        GSmodelStartAnimation(s->model);
    }
}

static inline void fifoColor(u8 r, u8 g, u8 b, u8 a)
{
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;
}

class CMenuHologram : public CMetaMenu {
public:
    s32 stageNo;
    s32 stageCur;
    CReliveStage* stage;
    u8 flag344;
    u8 pad345[3];
    GSlight* lights[8];
    s32 lightCount;
    GStexture* tex;
    u32 group;
    u8 loaded;
    u8 hidden;
    u8 pad376[2];
    GSmodel* object;
    void* seqWaza;
    void* waza;
    void* ceremony;
    ModelSlot models[7];
    CInfoWindow info2;
    CMenuGlobalState* pState;
    u8 pad414[4];

    static s32 model_z_layer;

    virtual void drawAll();

    void stateReliveCeremony();
    void stateMainProc();
    void setStage(int);
    void setStageToReliveReady();
    void moveStageWait(int);
    void reloadDatas(bool);
    void unloadDatas();
    GSgfxColAu8 pokemonToAisyouColor(Pokemon*, Pokemon*);
    void bgmStop();
    void bgmKick();
    void stageAllModelLoad();
    void releaseOffscreenData();
    void renderOffscreenData();
    void initializeOffscreenData();
    void stageAllModelUnLoad();
    ModelSlot* modelPokemonSetScale(s32);
    void modelVisitorSetYPosition(s32);
    ModelSlot* modelPokemonLoad(s32);
    s32 actionYesNo(u32, bool);
    void loop();
    void init(CMenuGlobalState&);
    void main(CMenuGlobalState&);
};

void thisExec(CMenuGlobalState&);
void thisFree();
void thisNew();

void CMenuHologram::main(CMenuGlobalState& st)
{
    systemFadeOutKeepAfterFloorPush();
    init(st);
    systemFadeInKick();
    loop();
    unloadDatas();
    bgmStop();
}

void CMenuHologram::init(CMenuGlobalState& st)
{
    time = 0;
    state.init();
    fadeTime = 0;
    fadeState = 0;
    memset(windowIds, 0, 0x100);
    memset(windowFuncs, 0, sizeof(windowFuncs));
    windowTable = CMetaMenu::defautlLocalWindowOpenTable;
    if (pcReliveHallSoundTbl != 0) {
        memcpy(&pad8, pcReliveHallSoundTbl, 0x14);
    }
    tutorialMode = 0;
    updated = 0;
    cachedInput = 0;
    memset(&keyInfo, 0, 0x1A);
    repeat = 0;
    lastOn = 0;
    hidden = 0;
    stageNo = 0;
    stageCur = 0;
    stage = 0;
    flag344 = 0;
    memset(lights, 0, sizeof(lights));
    lightCount = 0;
    tex = 0;
    loaded = 0;
    seqWaza = 0;
    waza = 0;
    ceremony = 0;
    pState = &st;
    localWindowSetTable(localWindowTable);
    info2.init(0xD0, 0x5DA);
    setStageToReliveReady();
    reloadDatas(true);
}

void CMenuHologram::loop()
{
    state.change(1);
    while (true) {
        state.update();
        switch (state.current) {
        case 1:
            if (stage->isReliveReady()) {
                state.change(4);
            } else {
                state.change(2);
            }
            break;
        case 2:
            flag344 = 1;
            stateMainProc();
            break;
        case 3: {
            static u32 msgTbl[3] = { 0xD134, 0xD135, 0xD136 };
            switch (actionMenu(msgTbl, 3, 0x1B8, 0x78, 0)) {
            case 0:
                state.change(5);
                break;
            case 1:
                moveStageWait(stageCur);
                state.change(2);
                break;
            case 2:
                state.change(2);
                break;
            }
            break;
        }
        case 4:
            stateReliveCeremony();
            break;
        case 5:
            relivehallSetLastViewStage(stageCur);
            systemFadeOutSetAndWait(-1.0f);
            {
                CMenuGlobalState* g = pState;
                g->mode = g->next;
                g->next = 2;
            }
            return;
        case 6:
            if (actionYesNo(0xD15C, false) == 0) {
                state.change(2);
            } else {
                state.change(8);
            }
            break;
        case 7:
        case 8:
            relivehallSetLastViewStage(stageNo);
            systemFadeOutSetAndWait(-1.0f);
            {
                CMenuGlobalState* g = pState;
                g->mode = g->next;
                g->next = 0;
            }
            return;
        }
    }
}

s32 CMenuHologram::actionYesNo(u32 msg, bool exec)
{
    if (exec) {
        info2.exec(*this, msg, false);
    } else {
        info2.open(msg, false);
    }
    static u32 msgTbl[2] = { 0x426A, 0x426B };
    s32 sel = actionMenu(msgTbl, 2, 0x1FE, 0x7F, 0);
    info2.close();
    return sel;
}

s32 CMenuHologram::model_z_layer = -1;

ModelSlot* CMenuHologram::modelPokemonLoad(s32 n)
{
    ModelSlot* slot = &models[n];
    memset(slot, 0, sizeof(*slot));
    Pokemon* p;
    if (n == 2) {
        p = stage->getVisitorPointer();
    } else {
        p = stage->getDancerPointer(n - 3);
    }
    if (p == 0) {
        return 0;
    }
    u16 wazaId = 0;
    if (p->isDarkPokemon() && !stage->isReliveReady()) {
        if (pokemonIsJoutaiDataId(p, 0x3E) == 1) {
            wazaId = 0x87;
        } else {
            wazaId = 0x25;
        }
    }
    u32 rnd;
    u16 dataId;
    menuModelGetPkxRndFromPokemonForSeqenceLoad(rnd, dataId, p);
    slot->seq = Sequence_LoadPokemon(dataId, rnd, pokemonGetStatus(p, 0, 0xC1, 0) != 0);
    slot->model = Sequence_GetGSmodel(slot->seq);
    Sequence_SetVisibility(slot->seq, 1);
    if (wazaId != 0) {
        void* ws = Sequence_LoadWaza(slot->seq, wazaId, 4, 0);
        if (ws != 0) {
            WazaSequence_Start(ws, 0);
        }
    }
    Sequence_DoAnimation(slot->seq, menuModelGetPokemonAnimationIndexByPointer(p));
    GSmodelSetForceUseFractionalFramesFlag(slot->model, 1);
    GSmodelSetSkipFractionalFramesFlag(slot->model, 1);
    return slot;
}

void CMenuHologram::modelVisitorSetYPosition(s32 n)
{
    ModelSlot* slot = &models[n];
    u16 id = stage->getVisitorPointer()->getPokemonDataId();
    f32 y = 0.0f;
    switch (id) {
    case 0xA5:
        y = -2.0f;
        break;
    case 0xA6:
        y = -10.0f;
        break;
    case 0x14A:
        y = -6.5f;
        break;
    case 0x14B:
        y = -20.0f;
        break;
    case 0x52:
        y = 0.0f;
        break;
    case 0x169:
        y = 0.0f;
        break;
    case 0x15:
        y = -2.0f;
        break;
    case 0x16:
        y = -9.0f;
        break;
    case 0xF:
        y = -5.5f;
        break;
    case 0xC:
        y = -8.0f;
        break;
    case 0x31:
        y = -9.0f;
        break;
    case 0x46:
        y = -2.0f;
        break;
    case 0x47:
        y = -6.5f;
        break;
    case 0x16A:
        y = 0.0f;
        break;
    case 0x15D:
        y = -6.5f;
        break;
    case 0x83:
        y = -6.5f;
        break;
    }
    GSvec v(0.0f, y, 0.0f);
    Sequence_SetPosition(slot->seq, &v);
}

ModelSlot* CMenuHologram::modelPokemonSetScale(s32 n)
{
    ModelSlot* slot = &models[n];
    Pokemon* p;
    if (n == 2) {
        p = stage->getVisitorPointer();
    } else {
        p = stage->getDancerPointer(n - 3);
    }
    if (p == 0) {
        return 0;
    }
    u16 id = p->getPokemonDataId();
    f32 base = menuGetPokemonScale((GCuptr)slot->seq, id);
    f32 s = base * (f32)relivehall_data->scale / 100.0f;
    GSvec v(s, s, s);
    Sequence_SetScale(slot->seq, &v);
    return slot;
}

void CMenuHologram::stageAllModelUnLoad()
{
    if (loaded) {
        if (ceremony != 0) {
            Sequence_SetVisibility(ceremony, 0);
            Sequence_Free(ceremony);
            ceremony = 0;
        }
        if (waza != 0) {
            WazaSequence_Free(waza);
            Sequence_Free(seqWaza);
        }
        waza = 0;
        seqWaza = 0;
        releaseOffscreenData();
        for (u32 i = 0; i < 7; i++) {
            ModelSlot* s = &models[i];
            if (s->model != 0) {
                if (s->seq != 0) {
                    Sequence_SetVisibility(s->seq, 0);
                    Sequence_Free(s->seq);
                } else {
                    GSmodelSetVisibility(s->model, 0);
                    scriptModelClose(s->id);
                }
            }
        }
        memset(models, 0, sizeof(models));
        for (s32 i = 0; i < lightCount; i++) {
            GSlightFree(lights[i]);
        }
        memset(lights, 0, sizeof(lights));
        lightCount = 0;
        if (group != 0) {
            GSfsysFree(group);
            GSresFreeGroup(group);
            group = 0;
        }
        cameraSetType(3);
        if (object != 0) {
            GSmodelFree(object);
            object = 0;
        }
        loaded = 0;
    }
}

SceneData* _makeArchiveHeader(u32 id)
{
    return (SceneData*)HSD_ArchiveGetPublicAddress(GSresGetResourceAllGroup(id), "scene_data");
}

void CMenuHologram::initializeOffscreenData()
{
    tex = GStextureCreate(0, 0, 0x45, 0, 0);
    if (tex != 0) {
        GSgfxLayerConfig::Move((GSgfxLayerID)2, (GSgfxLayerID)0, (GSgfxLayerOffset)1);
        if (model_z_layer == -1) {
            model_z_layer = GSgfxLayerConfig::Add("model z layer", 0xE000, 0x2000, 8, (GSgfxLayerType)0, false, false,
                                                  false, (GSgfxLayerID)2, (GSgfxLayerOffset)1);
            GSgfxLayer* l = GSgfxLayerFindByID(model_z_layer);
            if (l != 0) {
                l->SetClearFlags(true, true, false);
            }
        }
        GSgfxLayer* l2 = GSgfxLayerFindByID(2);
        l2->SetTextureCopy(tex, false, 0);
        l2->SetClearFlags(true, true, true);
    }
}

void CMenuHologram::renderOffscreenData()
{
#define LU8(o) (*(u8*)((u8*)layer + (o)))
#define LU32(o) (*(u32*)((u8*)layer + (o)))
    if (tex != 0) {
        GSgfxLayer* layer = GSgfxLayerFindByID(6);
        if (layer != 0) {
            GSgfxVF* vf = GSgfxVFBuildTemp(0, 2, 0, 0, 1, 5, 1, 1, 0);
            spriteSetOffset(6, 0, 0);
            spriteClearScissor(6);
            spriteSetEnv(6);
            f32 mtx[16];
            GSmtx44Ortho(mtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
            (*(s32*)&layer->hw.projType) = 1;
            ((f32*)layer->hw.proj)[0] = mtx[0];
            ((f32*)layer->hw.proj)[1] = mtx[3];
            ((f32*)layer->hw.proj)[2] = mtx[5];
            ((f32*)layer->hw.proj)[3] = mtx[7];
            ((f32*)layer->hw.proj)[4] = mtx[10];
            ((f32*)layer->hw.proj)[5] = mtx[11];
            GSlayerCam* cam = (*(GSlayerCam**)&layer->matrixStack);
            memcpy(cam->data + 1, &mtxIdent, 0x30);
            cam->data[0] |= 1;
            (*(f32*)&layer->hw.fogNear) = 0.0f;
            (*(f32*)&layer->hw.fogFar) = 30000.0f;
            if ((*(u8*)&layer->hw.fogEnable)) {
                if ((*(u8*)&layer->hw.fogRangeEnable)) {
                    (*(u32*)&layer->dirty[0].pe) |= 0x100;
                    (*(u32*)&layer->dirty[1].pe) |= 0x100;
                }
                (*(u32*)&layer->dirty[0].pe) |= 0x40;
                (*(u32*)&layer->dirty[0].groups) |= 0x40;
                (*(u32*)&layer->dirty[1].pe) |= 0x40;
                (*(u32*)&layer->dirty[1].groups) |= 0x40;
            }
            layer->mark(1, 0x16ac, 0x20);
            (*(u8*)&layer->hw.colorUpdate) = 1;
            (*(u8*)&layer->hw.alphaUpdate) = 0;
            (*(u8*)&layer->hw.zUpdate) = 0;
            layer->mark(0x40, 0x170c, 4);
            (*(u8*)&layer->hw.zEnable) = 0;
            (*(s32*)&layer->hw.zFunc) = 7;
            layer->mark(0x40, 0x170c, 8);
            (*(s32*)&layer->hw.cullMode) = 2;
            layer->mark(2, 0x16b8, 2);
            (*(u32*)&layer->unk1998) = 0x80;
            (*(GSgfxVF**)&layer->curVF) = vf;
            LU8(0xc70) = 1;
            layer->mark(1, 0x16ac, 1);
            layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
            LU8(0xdb8) = 1;
            layer->mark(4, 0x16bc, 1);
            layer->cunitChannelGen(0, (GSgfxCunitAlpha)2, (GSgfxCunitSrc)1, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2,
                                   (GSgfxDiffuseFunc)0);
            LU8(0xeac) = 1;
            layer->mark(8, 0x16cc, 1);
            LU32(0xeb0) = 0;
            LU32(0xeb4) = 0;
            LU32(0xeb8) = 4;
            layer->mark(8, 0x16d0, 1);
            LU32(0x1170) = 0;
            LU32(0x1174) = 0;
            LU32(0x1178) = 0;
            LU8(0x117c) = 1;
            LU32(0x1180) = 0;
            layer->mark(8, 0x16dc, 1);
            LU32(0xf70) = 0xF;
            LU32(0xf74) = 0xF;
            LU32(0xf78) = 0xF;
            LU32(0xf7c) = 8;
            layer->mark(8, 0x16d4, 1);
            LU32(0x12b0) = 0;
            LU32(0x12b4) = 0;
            LU32(0x12b8) = 0;
            LU8(0x12bc) = 1;
            LU32(0x12c0) = 0;
            layer->mark(8, 0x16e0, 1);
            LU32(0x1070) = 7;
            LU32(0x1074) = 5;
            LU32(0x1078) = 4;
            LU32(0x107c) = 7;
            layer->mark(8, 0x16d8, 1);
            if ((*(s32*)&layer->curPass) != 1) {
                (*(s32*)&layer->curPass) = 1;
                layer->curFifo = &layer->passes[layer->curPass];
            }
            (*(s32*)&layer->hw.blend[0]) = 1;
            (*(s32*)&layer->hw.blend[1]) = 4;
            (*(s32*)&layer->hw.blend[2]) = 1;
            (*(s32*)&layer->hw.blend[3]) = 5;
            layer->mark(0x40, 0x170c, 1);
            GStexture* t = tex;
            if ((*(GStexture**)&layer->dirty[0].tex[0]) != t || (*(GStexture**)&layer->dirty[1].tex[0]) != t || ((u8*)t)[7] != 0) {
                (*(GStexture**)&layer->dirty[0].tex[0]) = t;
                (*(u32*)&layer->dirty[0].texMask) |= 1;
                (*(GStexture**)&layer->dirty[1].tex[0]) = t;
                (*(u32*)&layer->dirty[1].texMask) |= 1;
            }
            layer->beginSurface(4);
#ifdef __MWERKS__
            GXWGFifo.s16 = GXWGFifo.s16 = 0;
#else
            GXWGFifo.s16 = 0;
            GXWGFifo.s16 = 0;
#endif
            fifoColor(0xFF, 0xFF, 0xFF, relivehall_data->alpha);
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0;
            GXWGFifo.s16 = 640;
            GXWGFifo.s16 = 0;
            fifoColor(0xFF, 0xFF, 0xFF, relivehall_data->alpha);
            GXWGFifo.u8 = 1;
            GXWGFifo.u8 = 0;
            GXWGFifo.s16 = 640;
            GXWGFifo.s16 = 480;
            fifoColor(0xFF, 0xFF, 0xFF, relivehall_data->alpha);
            GXWGFifo.u8 = 1;
            GXWGFifo.u8 = 1;
            GXWGFifo.s16 = 0;
            GXWGFifo.s16 = 480;
            fifoColor(0xFF, 0xFF, 0xFF, relivehall_data->alpha);
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 1;
            layer->endSurface();
        }
    }
#undef LU8
#undef LU32
}

void CMenuHologram::releaseOffscreenData()
{
    GSgfxLayer* layer = GSgfxLayerFindByID(2);
    layer->SetClearFlags(false, false, false);
    layer->SetTextureCopy(0, false, 0);
    if (model_z_layer != -1) {
        GSgfxLayerConfig::Remove((GSgfxLayerID)model_z_layer);
        model_z_layer = -1;
    }
    GSgfxLayerConfig::Move((GSgfxLayerID)2, (GSgfxLayerID)4, (GSgfxLayerOffset)1);
    if (tex != 0) {
        GStextureFree(tex);
        tex = 0;
    }
}

f32 _getNeckRotationCB(GSpart*, GSpartMixType, void*, GSvec* out)
{
    static GSvec neckRotVec(-0.7853982f, 0.0f, 0.0f);
    *out = neckRotVec;
    return 1.0f;
}

s32 plateIndexTbl[4][5][5] = {
    {
        { 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 2, 3, 0, 0, 0 },
        { 4, 5, 6, 0, 0 },
        { 7, 8, 9, 10, 0 },
        { 11, 12, 13, 14, 15 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 16, 17, 18, 19, 20 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 21, 22, 0, 0, 0 },
        { 23, 24, 25, 0, 0 },
        { 26, 27, 28, 29, 0 },
        { 30, 31, 32, 33, 34 },
    },
};
s32 colorLineIndexTbl[4][5][5] = {
    {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 35, 36, 0, 0, 0 },
        { 37, 39, 38, 0, 0 },
        { 40, 43, 42, 41, 0 },
        { 44, 48, 47, 46, 45 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 49, 53, 52, 51, 50 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 54, 55, 0, 0, 0 },
        { 56, 58, 57, 0, 0 },
        { 59, 62, 61, 60, 0 },
        { 63, 67, 66, 65, 64 },
    },
};

void CMenuHologram::stageAllModelLoad()
{
    stageAllModelUnLoad();
    initializeOffscreenData();
    GSColor4 col;
    u16 wazaId;
    s16 dancers;
    u32 camId;
    u32 sceneId;
    int st;
    st = stage->getState();
    dancers = stage->getDancerQuantity();
    switch (st) {
    case 0: {
        if (stage->getVisitorPointer()) {
            wazaId = 0xF0;
        } else {
            wazaId = 0;
        }
        group = 0x8E4;
        GSfsysReadWait(group);
        memset(&models[0], 0, sizeof(models[0]));
        s32 la[1] = { 0 };
        models[0].id = scriptModelOpen(0x18D91000);
        models[0].model = (GSmodel*)GSresGetResourceAllGroup(models[0].id);
        GSmodelSetRenderLayer(models[0].model, 1, la);
        if (models[0].model != 0) {
            GSmodelSetAnimIndex(models[0].model, 1);
            GSmodelSetAnimType(models[0].model, 0);
            GSmodelStartAnimation(models[0].model);
        }
        memset(&models[1], 0, sizeof(models[1]));
        s32 lb[1] = { 0 };
        models[1].id = scriptModelOpen(0x18D91001);
        models[1].model = (GSmodel*)GSresGetResourceAllGroup(models[1].id);
        GSmodelSetRenderLayer(models[1].model, 1, lb);
        if (models[1].model != 0) {
            GSmodelSetAnimIndex(models[1].model, 1);
            GSmodelSetAnimType(models[1].model, 0);
            GSmodelStartAnimation(models[1].model);
        }
        camId = 0x18D71800;
        sceneId = 0x18D90400;
        break;
    }
    case 1: {
        group = 0x8E5;
        wazaId = 0xF3;
        GSfsysReadWait(group);
        memset(&models[0], 0, sizeof(models[0]));
        s32 la[1] = { 0 };
        models[0].id = scriptModelOpen(0x18DC1000);
        models[0].model = (GSmodel*)GSresGetResourceAllGroup(models[0].id);
        GSmodelSetRenderLayer(models[0].model, 1, la);
        if (models[0].model != 0) {
            GSmodelSetAnimIndex(models[0].model, 1);
            GSmodelSetAnimType(models[0].model, 0);
            GSmodelStartAnimation(models[0].model);
        }
        memset(&models[1], 0, sizeof(models[1]));
        s32 lb[1] = { 0 };
        models[1].id = scriptModelOpen(0x18DC1000 + dancers);
        models[1].model = (GSmodel*)GSresGetResourceAllGroup(models[1].id);
        GSmodelSetRenderLayer(models[1].model, 1, lb);
        if (models[1].model != 0) {
            GSmodelSetAnimIndex(models[1].model, 1);
            GSmodelSetAnimType(models[1].model, 0);
            GSmodelStartAnimation(models[1].model);
        }
        camId = 0x18DA1800;
        sceneId = 0x18DC0400;
        break;
    }
    case 2: {
        group = 0x8E6;
        wazaId = 0xEF;
        GSfsysReadWait(group);
        memset(&models[0], 0, sizeof(models[0]));
        s32 la[1] = { 0 };
        models[0].id = scriptModelOpen(0x18DF1000);
        models[0].model = (GSmodel*)GSresGetResourceAllGroup(models[0].id);
        GSmodelSetRenderLayer(models[0].model, 1, la);
        if (models[0].model != 0) {
            GSmodelSetAnimIndex(models[0].model, 1);
            GSmodelSetAnimType(models[0].model, 0);
            GSmodelStartAnimation(models[0].model);
        }
        memset(&models[1], 0, sizeof(models[1]));
        s32 lb[1] = { 0 };
        models[1].id = scriptModelOpen(0x18DF1001);
        models[1].model = (GSmodel*)GSresGetResourceAllGroup(models[1].id);
        GSmodelSetRenderLayer(models[1].model, 1, lb);
        if (models[1].model != 0) {
            GSmodelSetAnimIndex(models[1].model, 1);
            GSmodelSetAnimType(models[1].model, 0);
            GSmodelStartAnimation(models[1].model);
        }
        camId = 0x18DD1800;
        sceneId = 0x18DF0400;
        break;
    }
    case 3: {
        group = 0x8E7;
        wazaId = 0xEF;
        GSfsysReadWait(group);
        memset(&models[0], 0, sizeof(models[0]));
        s32 la[1] = { 0 };
        models[0].id = scriptModelOpen(0x18E41000);
        models[0].model = (GSmodel*)GSresGetResourceAllGroup(models[0].id);
        GSmodelSetRenderLayer(models[0].model, 1, la);
        if (models[0].model != 0) {
            GSmodelSetAnimIndex(models[0].model, 1);
            GSmodelSetAnimType(models[0].model, 0);
            GSmodelStartAnimation(models[0].model);
        }
        memset(&models[1], 0, sizeof(models[1]));
        s32 lb[1] = { 0 };
        models[1].id = scriptModelOpen(0x18E41000 + dancers);
        models[1].model = (GSmodel*)GSresGetResourceAllGroup(models[1].id);
        GSmodelSetRenderLayer(models[1].model, 1, lb);
        if (models[1].model != 0) {
            GSmodelSetAnimIndex(models[1].model, 1);
            GSmodelSetAnimType(models[1].model, 0);
            GSmodelStartAnimation(models[1].model);
        }
        camId = 0x18E01800;
        sceneId = 0x18E40400;
        break;
    }
    }
    Pokemon* visitor = stage->getVisitorPointer();
    if (visitor != 0) {
        ModelSlot* slot = modelPokemonLoad(2);
        GSpart* part = GSmodelGetPart(models[1].model, ((u8*)relivehall_data)[plateIndexTbl[st][dancers][0] + 6]);
        GSmodelAttachToGSpart(slot->model, part, 7, 0, 1);
        GSpartFree(part);
        modelVisitorSetYPosition(2);
        modelPokemonSetScale(2);
    }
    for (int i = 0; i < dancers; i++) {
        ModelSlot* slot = modelPokemonLoad(i + 3);
        int k = (dancers + (i - stage->hit)) % dancers + 1;
        GSpart* part = GSmodelGetPart(models[1].model, ((u8*)relivehall_data)[(int)(plateIndexTbl[st][dancers][k]) + 6]);
        GSmodelAttachToGSpart(slot->model, part, 7, 0, 1);
        GSpartFree(part);
        modelPokemonSetScale(i + 3);
    }
    GSmaterial* mats;
    if (models[1].model != 0) {
        mats = *(GSmaterial**)((u8*)models[1].model + 0x5E0);
    } else {
        mats = 0;
    }
    GSmodelDisableModulation(models[1].model);
    if (dancers != 0) {
        memset(&col, 0, 4);
        if (visitor != 0) {
            GSgfxColAu8 c = pokemonToAisyouColor(visitor, stage->getDancerPointer(stage->hit));
            col.r = c.v[0];
            col.g = c.v[1];
            col.b = c.v[2];
            col.a = c.v[3];
        }
        u8 pl = ((u8*)relivehall_data)[colorLineIndexTbl[st][dancers][0] + 6];
        GSmaterial* mat = (GSmaterial*)((u8*)mats + (pl - 1) * GSMATERIAL_SIZE);
        GSmaterialSetModulate(mat, &col);
        GSmaterialEnableExtension(mat, 1);
    }
    for (int i = 0; i < dancers; i++) {
        GSgfxColAu8 c = pokemonToAisyouColor(stage->getDancerPointer(i), (Pokemon*)(stage->getDancerPointer((i + 1) % dancers)));
        int k = (dancers + (i - stage->hit)) % dancers + 1;
        u8 pl = ((u8*)relivehall_data)[colorLineIndexTbl[st][dancers][k] + 6];
        GSmaterial* mat = (GSmaterial*)((u8*)mats + (pl - 1) * GSMATERIAL_SIZE);
        GSmaterialSetModulate(mat, &c);
        GSmaterialEnableExtension(mat, 1);
    }
    cameraPlayAnime(group, camId, 1, 0.0f);
    cameraSetType(4);
    SceneData* arch = _makeArchiveHeader(sceneId);
    if (arch->lights != 0) {
        floorReadMakeLightResID(sceneId);
        for (int i = 0;; i++) {
            void* d = arch->lights[i];
            if (d == 0) {
                break;
            }
            GSlight* l = GSlightLoad(d);
            lights[lightCount++] = l;
            GSlightSetActive(l, 1);
            if (GSlightCanAnimate(l)) {
                GSlightSetAnimIndex(l, 0);
                GSlightSetAnimRate(l, 0.5f);
                GSlightStartAnimation(l);
            }
        }
    }
    s32 layers[2] = { 0 };
    layers[1] = model_z_layer;
    object = (GSmodel*)floorOpenObject(0x16C90400);
    GSmodelSetAnimIndex(object, 3);
    GSmodelSetAnimRate(object, 0.5f);
    GSmodelStartAnimation(object);
    GSmodelSetVisibility(object, 1);
    GSmodelSetAnimType(object, 1);
    GSmodelSetRenderLayer(object, 2, layers);
    GSpart* neckPart = GSmodelGetPart(object, peopleInfoBiosGetNeckIndex(peopleInfoBiosGetPtr(0x16C90400)));
    GSpartRegisterAnimMix(neckPart, 2, 0x20202, _getNeckRotationCB, 0);
    GSpartFree(neckPart);
    if (wazaId != 0) {
        seqWaza = Sequence_CreateNull();
        waza = Sequence_LoadWaza(seqWaza, wazaId, 4, 0);
        GSvec pos(0.0f, 0.0f, 0.0f);
        GSvec rot(0.0f, 0.0f, 0.0f);
        Sequence_SetPosition(seqWaza, &pos);
        Sequence_SetRotation(seqWaza, &rot);
        WazaSequence_Start(waza, 0);
    }
    loaded = 1;
}

void CMenuHologram::bgmKick()
{
    stage->getState();
    int tempo = stage->getTempo();
    u32 bgm;
    if (tempo <= 0) {
        bgm = 0x5BB;
    } else if (tempo <= 0x35) {
        bgm = 0x510;
    } else if (tempo <= 0x5F) {
        bgm = 0x50F;
    } else {
        bgm = 0x50E;
    }
    u32 cur = soundGetBGMID();
    if (cur != bgm) {
        menuPtPlayBgm(bgm);
    }
}

void CMenuHologram::bgmStop()
{
    soundStop(soundGetBGMID(), 0x32);
}

GSgfxColAu8 CMenuHologram::pokemonToAisyouColor(Pokemon* a, Pokemon* b)
{
    int r = reliveHallPokemonToAisyou(a, b);
    if (r == -1) {
        return GSgfxColAu8_Black;
    }
    return relivehallAisyou2ColorTbl[r];
}

void CMenuHologram::unloadDatas()
{
    localWindowDeleteAll();
    stageAllModelUnLoad();
}

void CMenuHologram::reloadDatas(bool bgm)
{
    stageAllModelLoad();
    if (models[0].model != 0) {
        GSmodelSetAnimIndex(models[0].model, 2);
        GSmodelSetAnimType(models[0].model, 1);
        GSmodelStartAnimation(models[0].model);
    }
    if (models[1].model != 0) {
        GSmodelSetAnimIndex(models[1].model, 2);
        GSmodelSetAnimType(models[1].model, 1);
        GSmodelStartAnimation(models[1].model);
    }
    localWindowCreateAll();
    if (bgm) {
        bgmKick();
    }
}

void CMenuHologram::moveStageWait(int n)
{
    systemFadeOutSetAndWait(0.1f);
    unloadDatas();
    setStage(n);
    reloadDatas(true);
    systemFadeInKick();
}

void CMenuHologram::setStageToReliveReady()
{
    int i;
    for (i = 0; i < 9; i++) {
        if (CReliveHall::getPointer()->getStage(i)->isReliveReady()) {
            break;
        }
    }
    if (i == 9) {
        setStage(relivehallGetLastViewStage());
    } else {
        setStage(i);
    }
}

void CMenuHologram::setStage(int n)
{
    stageNo = n;
    stageCur = n;
    stage = CReliveHall::getPointer()->getStage(stageNo);
}

void CMenuHologram::stateMainProc()
{
    do {
        CKeyInfo* k = getKeyInfo();
        if ((k->trg | k->rep) != 0) {
            switch (k->rep) {
            case 4:
            case 0x200:
                stageCur = (stageCur + 8) % 9;
                menuPtPlaySe(0x45F);
                break;
            case 8:
            case 0x400:
                stageCur = (stageCur + 1) % 9;
                menuPtPlaySe(0x45F);
                break;
            }
            switch (k->trg) {
            case 0x10:
                menuPtPlaySe(0x45A);
                state.change(3);
                break;
            case 0x20:
                menuPtPlaySe(0x45B);
                state.change(6);
                break;
            }
        }
        updateAll();
    } while (state.next == -1);
}

void CMenuHologram::stateReliveCeremony()
{
    GSflagSet(0x5A3, 1);
    flag344 = 0;
    while (true) {
        if (animIndexOf(models[1].model) == 2) {
            break;
        }
        updateAll();
    }
    aButtonWait();
    menuPtPlayBgm(0x5A8);
    menuPtPlaySe(0x5A7);
    cameraPlayAnime(floorGetCurrentGroupID(), 0x18E21800, 0, 0.0f);
    cameraSetType(4);
    if (models[0].model != 0) {
        GSmodelSetAnimIndex(models[0].model, 3);
        GSmodelSetAnimType(models[0].model, 0);
        GSmodelStartAnimation(models[0].model);
    }
    waitAtTime(0.3f);
    GSmodelSetVisibility(object, 0);
    waitAtTime(6.0f);
    Pokemon* visitor = stage->getVisitorPointer();
    hidden = 1;
    ceremony = reliveCeremonyFromHologram(visitor, (u32)models[2].seq);
    hidden = 0;
    systemFadeInKick();
    systemFadeWaitToEnd();
    char buf[0x18];
    GScharCpy(buf, visitor->getNicknamePtr());
    u32 trg;
    do {
        GSthreadSwitch();
        trg = windowGetKeyTrg();
    } while ((u16)windowGetKeyOn() != 0 || (u16)trg != 0);
    info2.setMsgCtrlValue(0x32, (u32)buf);
    info2.exec(*this, 0xD15E, true);
    Pokemon pk;
    stage->pickupVisitor(pk);
    PCBOX::getPointer()->addPokemonLastWatchBox(&pk);
    if (CReliveHall::getPointer()->isReliveReadyPokemonExist()) {
        systemFadeInKick();
        if (PCBOX::getPointer()->isPokemonFull()) {
            info2.exec(*this, 0xD132, true);
            state.change(7);
        } else if (actionYesNo(0xD131, true) == 0) {
            systemFadeOutSetAndWait(-1.0f);
            setStageToReliveReady();
            reloadDatas(true);
            systemFadeInKick();
            state.change(4);
        } else {
            state.change(7);
        }
    } else {
        state.change(7);
    }
}

void CMenuHologram::drawAll()
{
    if (object != 0) {
        static GSvec pos(0.0f, 0.0f, 0.0f);
        static GSvec rot(0.0f, 3.1415927f, 0.0f);
        static GSvec scl(1.0f, 1.0f, 1.0f);
        GSmodelSetPosition(object, &pos);
        GSmodelSetRotation(object, &rot);
        GSmodelSetScale(object, &scl);
    }
    renderOffscreenData();
    if (!hidden) {
        if (models[0].model != 0) {
            int idx = animIndexOf(models[0].model);
            if (idx == 1 || idx == 3) {
                if (GSmodelHasAnimationEnded(models[0].model)) {
                    {
                        int next = idx + 1;
                        startAnimNext(&models[0], next);
                    }
                }
            }
        }
        if (models[1].model != 0) {
            int idx = animIndexOf(models[1].model);
            if (idx == 1 || idx == 3) {
                if (GSmodelHasAnimationEnded(models[1].model)) {
                    {
                        int next = idx + 1;
                        startAnimNext(&models[1], next);
                    }
                }
            }
        }
        if (flag344) {
            f32 rate = calcAnimationTimeRate0to1(32.0f);
            GSvec r(0.0f, 2.0f * (3.1415927f * -rate), 0.0f);
            GSmodelSetRotation(models[1].model, &r);
        }
        CReliveStage* st = CReliveHall::getPointer()->getStage(stageCur);
        int tempo = st->getTempo();
        relivehallDraw9StageNumber(stageNo);
        relivehallDraw9StageInfo(stageCur);
        bool flag = false;
        if (state.current != 4 && state.current != 7) {
            flag = true;
        }
        relivehallDrawStageInfoCursor(stageCur, tempo, st->getDancerQuantity(), (Pokemon*)(st->getVisitorPointer()), flag);
        info2.draw();
        localWindowDrawAll();
        menuDrawReliveUpdate();
    }
}

void thisNew()
{
    void* mem = GSmemAllocClr(sizeof(CMenuHologram));
    pMenuHologram = new (mem) CMenuHologram;
}

void thisFree()
{
    if (pMenuHologram != 0) {
        GSmemFree(pMenuHologram);
        pMenuHologram = 0;
    }
}

void thisExec(CMenuGlobalState& state)
{
    thisNew();
    pMenuHologram->main(state);
    thisFree();
}

}

void menuHologramExecFromPcBox(CMenuGlobalState& state)
{
    thisExec(state);
}

extern "C" {

void menuHologramUnloadDatas()
{
    pMenuHologram->unloadDatas();
}

void menuHologramReloadDatas()
{
    pMenuHologram->reloadDatas(false);
}

}
