#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gcdata.h>
#pragma pool_strings off
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
enum ASM { ASM_draft_dummy };
struct _HSD_JObj;
typedef void (*DPCtlCallback)(int, int, int, struct _HSD_JObj*);
struct GScamera;
struct GSgfxLayer;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxLayerPass { GSgfxLayerPass_draft_dummy };
struct GSgfxRenderModule;
struct GSpart;
struct GSparticleBank;
struct GSparticleGenerator;
struct GSquat;
struct GSvec;
struct HSD_CObj;
struct HSD_Generator;
struct HSD_JObj;
struct ModelBank;
struct PSGenerator;
struct Quaternion;
struct Vec;
struct _GSmodel;
struct _GSparticleBank;
struct _GSparticleGen;
struct _HSD_JObj;

struct GSparticleBank {
    u8 unk0[4];
    u8 inactive;
};

extern "C" {

extern "C++" {
struct GScamera {
    u8 _draft[1];
};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
    void InvalidateState();
    void FlushState();
};
struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(GSgfxLayer* layer, GSgfxLayerPass pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 id;
};
struct GSpart {
    u8 _draft[1];
};
struct GSparticleGenerator {
    u8 _draft[1];
};
struct GSquat {
    f32 x, y, z, w;
};
struct GSvec {
    u8 _draft[1];
};
struct HSD_CObj {
    u8 _draft[1];
};
struct HSD_Generator {
    u8 _draft[1];
};
struct HSD_JObj {
    u8 _draft[1];
};
struct ModelBank {
    u8 _draft[1];
};
struct PSGenerator {
    PSGenerator* next;
    u32 flags;
    u8 pad08[0x08];
    u16 maxLife;
    u16 angleFlags;
    u8 bank;
    u8 linkNo;
    u8 pad16[2];
    u16 familyId;
    u8 pad1A[0x1E];
    f32 gravity;
    f32 friction;
    u8 pad40[4];
    f32 radius;
    u8 pad48[4];
    u32 childCount;
    void* appSRT;
    f32 shape[12];
    u8 pad84[8];
    u16 generatorFlags;
    u16 index;
    u8 pad90[0x18];
    void* linkedJObj;
    f32 angleRadiusScale[3];
};
struct Quaternion {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
};
struct _GSmodel {
    u8 _draft[1];
};
struct _GSparticleGenData {
    s8 linked;
    s8 infinite;
    s16 id;
    u32 serial;
    HSD_Generator* generator;
    f32 pos[3];
    f32 rot[3];
    f32 scale[3];
};
struct _GSparticleGen {
    u8 native;
    u8 f1;
    u8 f2;
    u8 pad3;
    s32 partIndex;
    s32 attachMode;
    _GSmodel* model;
    f32 pos[3];
    f32 rot[3];
    f32 scale[3];
    void* bank;
    _GSparticleGenData* data;
};
struct _GSparticleBank {
    u8 active;
    u8 id;
    u8 type;
    u8 genCount;
    u8 busy;
    u8 pad5[3];
    void* data;
    _GSparticleGen* gens;
    HSD_CObj* camera;
};
struct GSparticleJObjView {
    void* classInfo;
    u16 refCount;
    u16 refCountIndividual;
    _HSD_JObj* next;
    _HSD_JObj* parent;
    _HSD_JObj* child;
};
struct GSparticlePartView {
    u8 inUse;
    u8 pad;
    u16 index;
    _GSmodel* model;
    HSD_JObj* jobj;
};
struct GSparticleCameraView {
    u8 used;
    u8 lookAt;
    u8 dirty;
    u8 canAnimate;
    void* desc;
    HSD_CObj* cobj;
};
#ifdef __MWERKS__
#define PEBANK_PARAM(b, i) (*(f32*)((s8*)(b) + 0x10C + (i) * 4))
#define PEBANK_FLAGS_PTR(b) ((s8*)(b) + 0x134)
#define PEBANK_ENGINE_PTR(b) ((s8*)(b) + 0x160)
#else
extern "C" f32* peBankPCParams(void* bank);
extern "C" u32* peBankPCFlags(void* bank);
extern "C" void** peBankPCEngine(void* bank);
#define PEBANK_PARAM(b, i) (peBankPCParams((void*)(b))[i])
#define PEBANK_FLAGS_PTR(b) peBankPCFlags((void*)(b))
#define PEBANK_ENGINE_PTR(b) peBankPCEngine((void*)(b))
#endif
struct _HSD_JObj {
    u8 _draft[1];
};

extern "C" {
asm void DCFlushRange(register void* addr, register u32 nBytes);
int EulerToQuat(Vec* euler, Quaternion* q);
GScamera* GScameraGetActiveCamera(void);
u8 GScameraIsValid(GScamera* camera);
void GScameraLoadActiveCameraMatrix(GSgfxLayerID id);
void GScameraLoadProjection(GScamera* camera, GSgfxLayer* layer);
s32 GSgfxPerfbarCPUEntry(s32);
s32 GSgfxVideoGetVsyncCount();
u8 GSgfxVideoGetVsyncRate(void);
void GSlogWrite(const char*, ...);
void* GSmemAlloc(u32 size);
ModelBank* GSmemAllocClr(u32 size);
void GSmemFree(void* ptr);
u32 GSmodelGetGSparticleLinkAttachMode(_GSmodel* model);
void* GSmodelGetLinkedGSparticleBank(_GSmodel* model);
GSpart* GSmodelGetPart(_GSmodel* model, s32 index);
u32 GSmodelGetVisibility(_GSmodel* model);
u8 GSmodelIsRootNullAdded(_GSmodel* model);
_GSmodel* GSmodelSearchModelList(HSD_JObj* jobj);
void GSmodelSet60fpsAnimFlag(_GSmodel* model, u8 enable);
void GSpartFree(GSpart* part);
s32 GSpartGetJObjIndex(void*, void*);
void GSpartGetTransform(GSpart* part, GSvec* pos, GSvec* rot, GSvec* scale);
void GSparticleAttachGeneratorToGSpart(void *p0, void *p1, s32 p2, s8 p3, u8 p4, u8 p5);
void GSparticleBankSetCamera(_GSparticleBank* bank, HSD_CObj* camera);
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* bank, s32 index, s32);
void GSparticleDestroyAllGenerators(GSparticleBank* bank, bool children);
void GSparticleDestroyGenerator(void *p0, bool p1);
void GSparticleDetachGeneratorFromGSpart(void *p0, u8 p1);
void GSparticleFree(GSparticleBank* bank);
void GSparticleGeneratorSetCamera(void *p0, s32 p1);
u32 GSparticleGetGeneratorLife(GSparticleGenerator* gen);
s32 GSparticleIsGeneratorAlive(void *p0);
void GSparticleSetBankVisibility(GSparticleBank* bank, bool visible);
void GSparticleSetGeneratorPosition(GSparticleGenerator* gen, Vec* pos);
void GSparticleSetGeneratorRotation(void *p0, f32 *p1);
void GSparticleSetGeneratorScale(void *p0, void *p1, u8 p2, u8 p3);
void GSparticleSetGeneratorVisibility(void *p0, u8 p1);
void GSparticleSetNodeScaling(void *p0, u8 p1);
void GSparticleSetOffsetRotationInLocal(void *p0, u8 p1, u8 p2);
void GSparticleSetParticleTextureScaling(void *p0, u8 p1);
void GSparticleSetRandomVelocityScaling(void *p0, u8 p1);
void GSparticleSetTornadoScaling(void *p0, u8 p1, u8 p2);
void GSparticleSetVelocityRotationInLocal(void *p0, u8 p1);
void GSparticleStopGenerator(void *p0);
void GSvecMakeFromQuat(GSvec* out, const GSquat* q);
void GSvecTransformQuat(GSvec* out, const GSquat* q, const GSvec* v);
void HSD_JObjSetDPtclCallback(DPCtlCallback cb);
void HSD_JObjSetPtclTargetCallback(void (*cb)(HSD_JObj*, s32));
void HSD_JObjSetSPtclCallback(void (*func)(s32, s32, s32, HSD_JObj*));
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
void* memset(void* dst, int val, size_t n);
s32 particleEngineInit();
s32 particleEnginePostUpdate();
s32 particleEngineRender(void*);
#ifdef __MWERKS__
s32 particleEngineUpdate(u8, f32);
#else
void particleEngineUpdate(f32 dt);
#define particleEngineUpdate(rate, dt) ((void)(rate), particleEngineUpdate(dt))
#endif
void* peBankCreate(s32);
s32 peBankFree(void*);
s32 peBankFreeFile(s32);
f32 peBankGetLife(void*);
u8 peBankIsInfinite(u32 a0 = 0);
void* peBankLoadFile(void*);
s32 peBankStart(void*);
s32 peBankStop(u32);
s32 peBankStopLoop(u32);
HSD_Generator* psCreateGeneratorID(int linkNo, int bank, int id);
void psDispBeginFrame(void);
int psDispHasRenderData(u32 target_link);
void psDispParticles(u32 target_link, u32 sw, void* camera);
void psDispSetProjection(void* proj);
void psExecGenerator(int mask);
void* psGeneratorGetCamera(HSD_Generator* gp);
void psGeneratorSetCamera(HSD_Generator* gp, HSD_CObj* cobj);
u32 psGetGeneratorChildMaxLife(PSGenerator* gen);
u32 psGetParticleChildCount(PSGenerator* gen);
s32 psInitAppSRT(s32 num, u32 size);
void psInitDataBank(int bank, int* cmdBank, int* texBank, u32* ref, int* formBank);
void psInitGenerator(int num);
void psInitParticle(int num);
s32 psInterpretParticles(s32);
void psKillFamily(s32 familyId, s32 linkNo);
void psKillGenerator(HSD_Generator* gp);
void psLinkChildGensToJObj(PSGenerator* gen, void* jobj);
void psSetBillboardCamera(HSD_CObj* cobj);
void psSetGeneratorAngleRadiusScale(PSGenerator* gen, f32* scale, u8 scaleMotion);
void psSetNodeScaling(PSGenerator* gen, u8 enabled);
void psSetOffsetRotationInLocal(PSGenerator* gen, u8 enabledA, u8 enabledB);
void psSetParticleTexScaling(PSGenerator* gen, u8 enabled);
void psSetParticleVisibility(PSGenerator* gen, u8 visible);
void psSetRandomVelocityScaling(PSGenerator* gen, u8 enabled);
void psSetToken(u16 token);
void psSetTornadoScaling(PSGenerator* gen, u8 enabledA, u8 enabledB);
void psSetVelocityRotationInLocal(PSGenerator* gen, u8 enabled);
void psUnlinkChildGensFromJObj(PSGenerator* gen);
void psSetPointJObjNodup();
struct XdBlob10 { u8 data[0x10]; };
extern XdBlob10 zeroQuaternion;
struct XdBlobC { u8 data[0xC]; };
extern XdBlobC zeroVector;
extern XdBlobC unitScaleVector;
extern s32 init;
extern s32 jtbl_1991;
extern s32 func;
}
extern "C++" {
void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);
#ifdef __MWERKS__
s32 GSgfxRenderWaitForDrawComplete();
#else
void GSgfxRenderWaitForDrawComplete();
#endif
static void _particleBankDestroyOldestGenerator(_GSparticleBank* p0);
static void _particleJObjCallback(int p0, int p1, int p2, _HSD_JObj* p3);
static void _particlePostUpdate(float p0);
static void _particlePreUpdate(float p0);
static void _particleRender(GSgfxLayer* p0, GSgfxLayerPass p1);
static void _particleUpdateAttachment(_GSparticleGen* p0);
}
u32 g_particle_cameras_count;
static u8* _particleBankStructList;
static u32 _particleBankStructCount;
static u8 _particlePALFrameCount;
static u8 _invalidateVtx;
GScamera* g_particle_cameras[4];
static u8 _invalidateTex;

extern "C" {
void GSparticleInit(u32 p0);
}

extern "C" {
u8* GSparticleLoad(void *p0);
}

}
}

extern "C++" {
static inline void _particleRenderCamera(GSgfxLayer* layer, GScamera* cam, u32 link, void* dispCam) {
    GScameraLoadProjection(cam, layer);
    layer->FlushState();
#ifdef __MWERKS__
    psDispSetProjection((u8*)layer + 0xD54);
#else
    psDispSetProjection((u8*)&layer->hw.projType);
#endif
    psSetBillboardCamera((*(HSD_CObj **)&((GSparticleCameraView*)(cam))->cobj));
    psDispParticles(link, 1, dispCam);
    psDispParticles(link, 2, dispCam);
    layer->InvalidateState();
}
}

extern "C++" {
static inline u32 _genGetMaxLife(u8* gen) {
    u8* bank = (*(u8 **)&((_GSparticleGen*)(gen))->data);
    if (bank == NULL) {
        return 0;
    }
    if ((*(u8 *)&((_GSparticleGen*)(gen))->native) != 0) {
        if (peBankIsInfinite((u32)bank) != 0) {
            return -1U;
        }
        return (u32)(peBankGetLife((*(u8 **)&((_GSparticleGen*)(gen))->data)) * (f32)GSgfxVideoGetVsyncRate());
    }
    if ((*(u8 *)&((_GSparticleGenData*)(bank))->infinite) == 1) {
        return -1U;
    }
    return psGetGeneratorChildMaxLife((*(PSGenerator **)&((_GSparticleGenData*)(bank))->generator));
}
}

extern "C++" {
static inline u8 _genIsAlive(u8* gen) {
    u8* bank = (*(u8 **)&((_GSparticleGen*)(gen))->data);
    if (bank == NULL) {
        return 0;
    }
    if ((*(u8 *)&((_GSparticleGen*)(gen))->native) != 0) {
        return _genGetMaxLife(gen) != 0;
    }
    if ((*(u8 *)&((_GSparticleGenData*)(bank))->infinite) != 0) {
        return 1;
    }
    if (psGetParticleChildCount((*(PSGenerator **)&((_GSparticleGenData*)(bank))->generator)) != 0) {
        return 1;
    }
    return _genGetMaxLife(gen) != 0;
}
}

extern "C++" {
static inline void _particleClampScale(f32* v) {
    f32 x = *v;
    f32 a;
    if (x > 0.0f) {
        a = x;
    } else {
        a = -x;
    }
    f32 r = 0.00001f;
    if (a < 0.00001f) {
        if (x < 0.0f) {
            r = -0.00001f;
        }
        *v = r;
    }
}
}

extern "C" {
static inline s32 _particleBankFindFreeGenerator(GSparticleBank* bank, const u8* kind) {
    u8* gen = (*(u8 **)&((_GSparticleBank*)(bank))->gens);
    for (s32 i = 0; i < (*(u8 *)&((_GSparticleBank*)(bank))->genCount); i++, gen += sizeof(_GSparticleGen)) {
        if (*kind != (*(u8 *)&((_GSparticleGen*)(gen))->native)) {
            return -1;
        }
        if ((*(u32 *)&((_GSparticleGen*)(gen))->data) == 0) {
            return i;
        }
    }
    return -1;
}
}

extern "C" {
typedef _GSparticleBank ParticleBankStruct;
}

extern "C" {
struct ParticleFileHeader {
    gc_bes32 magic;
    gc_ptr32(gc_be16) cmd;
    gc_ptr32(int) tex;
    gc_bes32 texSize;
    gc_ptr32(u32) ref;
};
}

extern "C" {
static inline ParticleBankStruct* _particleFindFreeBank() {
    ParticleBankStruct* p = (ParticleBankStruct*)_particleBankStructList;
    u32 i;
    for (i = 0; i < _particleBankStructCount; i++, p++) {
        if (p->active == 0) {
            return p;
        }
    }
    return NULL;
}

static inline ParticleBankStruct* _particleBankAlloc() {
    return _particleFindFreeBank();
}
}

extern "C" {
static inline bool _particleIdUsed(u8 id) {
    ParticleBankStruct* p = (ParticleBankStruct*)_particleBankStructList;
    u32 i;
    for (i = 0; i < _particleBankStructCount; i++, p++) {
        if (p->id == id) {
            return true;
        }
    }
    return false;
}
}

extern "C" {
static inline u8 _particleFindFreeId() {
    u8 id;
    for (id = 0; id < 0x40; id++) {
        if (!_particleIdUsed(id)) {
            return id;
        }
    }
    return 0xFF;
}
}

extern "C" {
#pragma push
}

extern "C" {
#pragma dont_inline on
}

extern "C" {
#pragma pop
}

extern "C++" {
static inline _HSD_JObj* _particleJObjGetParent(_HSD_JObj* jobj) {
    if (jobj == NULL) {
        return NULL;
    }
    return (*(_HSD_JObj **)&((GSparticleJObjView*)(jobj))->parent);
}
}
extern "C++" static void _particleRender(GSgfxLayer* p0, GSgfxLayerPass p1);
extern "C++" static void _particlePostUpdate(float p0);
extern "C++" static void _particlePreUpdate(float frames);
extern "C++" static void _particleUpdateAttachment(_GSparticleGen* p0);
extern "C" void GSparticleGeneratorSetCamera(void *p0, s32 p1);
extern "C" void GSparticleBankSetCamera(_GSparticleBank* bank, HSD_CObj* camera);
extern "C" void GSparticleDestroyAllGenerators(GSparticleBank* p0, bool p1);
extern "C" void GSparticleDestroyGenerator(void *p0, bool p1);
extern "C" void GSparticleStopGenerator(void *p0);
extern "C" void GSparticleSetBankVisibility(GSparticleBank* p0, bool p1);
extern "C" void GSparticleSetGeneratorVisibility(void *p0, u8 p1);
extern "C" void GSparticleSetRandomVelocityScaling(void *p0, u8 p1);
extern "C" void GSparticleSetNodeScaling(void *p0, u8 p1);
extern "C" void GSparticleSetTornadoScaling(void *p0, u8 p1, u8 p2);
extern "C" void GSparticleSetParticleTextureScaling(void *p0, u8 p1);
extern "C" void GSparticleSetOffsetRotationInLocal(void *p0, u8 p1, u8 p2);
extern "C" void GSparticleSetVelocityRotationInLocal(void *p0, u8 p1);
extern "C" void GSparticleActivateBank(GSparticleBank* bank);
extern "C" void GSparticleDisactivateBank(GSparticleBank* bank);
extern "C" s32 GSparticleIsGeneratorAlive(void *p0);
extern "C" u32 GSparticleGetGeneratorLife(GSparticleGenerator* p0);
extern "C" void GSparticleSetGeneratorScale(void *p0, void *p1, u8 p2, u8 p3);
extern "C" void GSparticleSetGeneratorRotation(void *p0, f32 *p1);
extern "C" void GSparticleSetGeneratorPosition(GSparticleGenerator* p0, Vec* p1);
extern "C" void GSparticleDetachGeneratorFromGSpart(void *p0, u8 p1);
extern "C" void GSparticleAttachGeneratorToGSpart(void *p0, void *p1, s32 p2, s8 p3, u8 p4, u8 p5);
extern "C" GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* p0, s32 p1, s32 p2);
extern "C" void GSparticleFree(GSparticleBank* p0);
extern "C" u8* GSparticleLoad(void* file);
extern "C" void GSparticleInit(u32 count);
extern "C++" static void _particleBankDestroyOldestGenerator(_GSparticleBank* bank);
extern "C++" static void _particleJObjCallback(int p0, int p1, int p2, _HSD_JObj* p3);

extern "C++" {
static void _particleJObjCallback(int p0, int p1, int p2, _HSD_JObj* p3) {
    _HSD_JObj* root = p3;
    while (_particleJObjGetParent(root) != NULL) {
        root = _particleJObjGetParent(root);
    }
    _GSmodel* model = GSmodelSearchModelList((HSD_JObj*)root);
    if (model == NULL) {
        return;
    }
    GSparticleBank* bank = (GSparticleBank*)GSmodelGetLinkedGSparticleBank(model);
    if (bank == NULL) {
        return;
    }
    if (GSmodelIsRootNullAdded(model)) {
        root = (*(_HSD_JObj **)&((GSparticleJObjView*)(root))->child);
    }
    u32 index = GSpartGetJObjIndex(root, p3);
    if (index == 0xFFFFFFFF) {
        return;
    }
    GSpart* part = GSmodelGetPart(model, index);
    if (part == NULL) {
        return;
    }
    GSparticleGenerator* gen = GSparticleCreateGenerator(bank, p2, 0);
    if (gen != NULL) {
        u8* data = (*(u8 **)&((_GSparticleGen*)(gen))->data);
        if (data != NULL && (*(u8 *)&((_GSparticleGen*)(gen))->native) == 0) {
            psSetParticleTexScaling((*(PSGenerator **)&((_GSparticleGenData*)(data))->generator), 1);
        }
        data = (*(u8 **)&((_GSparticleGen*)(gen))->data);
        if (data != NULL && (*(u8 *)&((_GSparticleGen*)(gen))->native) == 0) {
            psSetRandomVelocityScaling((*(PSGenerator **)&((_GSparticleGenData*)(data))->generator), 1);
        }
        GSparticleAttachGeneratorToGSpart(gen, part, GSmodelGetGSparticleLinkAttachMode(model), 0, 1, 0);
        u32 visible = GSmodelGetVisibility(model);
        data = (*(u8 **)&((_GSparticleGen*)(gen))->data);
        if (data != NULL) {
            if ((*(u8 *)&((_GSparticleGen*)(gen))->native) != 0) {
                if (data != NULL) {
                    if ((u8)visible) {
                        (*(u32 *)PEBANK_FLAGS_PTR(data)) |= 4;
                    } else {
                        (*(u32 *)PEBANK_FLAGS_PTR(data)) &= ~4;
                    }
                }
            } else {
                psSetParticleVisibility((*(PSGenerator **)&((_GSparticleGenData*)(data))->generator), visible);
            }
        }
    }
    GSpartFree(part);
}
}

extern "C++" {
static void _particleBankDestroyOldestGenerator(_GSparticleBank* bank) {
    _GSparticleGen* gens;
    _GSparticleGen* gen;
    s32 i;
    u32 oldest = 0xFFFFFFFF;
    s32 found = -1;
    gens = bank->gens;
    gen = gens;
    for (i = 0; i < bank->genCount; i++, gen++) {
        if (gen->data != NULL && gen->data->serial < oldest) {
            oldest = gen->data->serial;
            found = i;
        }
    }
    if (found != -1) {
        GSparticleDestroyGenerator(&gens[found], 1);
    }
}
}

extern "C" {
void GSparticleInit(u32 count) {
    GSgfxRenderModule module = { NULL, _particlePreUpdate, _particleRender, NULL, _particlePostUpdate, NULL, 0xB29A48E1 };
    u32 i;

    memset(g_particle_cameras, 0, sizeof(g_particle_cameras));
    _particleBankStructCount = count;
    g_particle_cameras_count = 0;
    _particleBankStructList = (u8*)GSmemAlloc(count * sizeof(_GSparticleBank));
    if (_particleBankStructList == NULL) {
        return;
    }
    for (i = 0; i < _particleBankStructCount; i++) {
        ((_GSparticleBank*)_particleBankStructList)[i].active = 0;
    }
    psSetToken(0);
    psInitParticle(0);
    psInitGenerator(0);
    psInitAppSRT(0, 0x74);
    HSD_JObjSetSPtclCallback((void (*)(s32, s32, s32, HSD_JObj*))_particleJObjCallback);
    HSD_JObjSetDPtclCallback((DPCtlCallback)_particleJObjCallback);
    HSD_JObjSetPtclTargetCallback((void (*)(HSD_JObj*, s32))psSetPointJObjNodup);
    particleEngineInit();
    GSgfxRenderModuleRegister(0x40, &module, NULL);
}
}

extern "C" {
u8* GSparticleLoad(void* file) {
    ParticleFileHeader* hdr = (ParticleFileHeader*)file;
    ParticleBankStruct* bank = _particleBankAlloc();
    u8 id;
    if (bank == NULL) {
        return NULL;
    }
    id = _particleFindFreeId();
    if (id == 0xFF) {
        return NULL;
    }
    bank->camera = 0;
    bank->gens = NULL;
    bank->busy = 0;
    if (hdr->magic == 0x01F056DA) {
        int i;
        if ((s32)GC_RAW32(hdr->cmd) != 0x30002) {
            return NULL;
        }
        bank->type = 1;
        bank->genCount = 0x10;
        bank->gens = (_GSparticleGen*)GSmemAllocClr(0x10 * sizeof(_GSparticleGen));
        if (bank->gens == NULL) {
            return NULL;
        }
        for (i = 0; i < 0x10; i++) {
            bank->gens[i].native = 1;
        }
        bank->data = peBankLoadFile(hdr);
        if (bank->data == NULL) {
            goto fail;
        }
    } else {
        bank->type = 0;
        bank->genCount = 0x40;
        bank->gens = (_GSparticleGen*)GSmemAllocClr(0x40 * sizeof(_GSparticleGen));
        if (bank->gens == NULL) {
            return NULL;
        }
        switch (hdr->magic) {
        case 0x47505430:
            GSlogWrite("GSparticle: ***************************************************************************\n");
            GSlogWrite("GSparticle: ************* version 0 .gpt files are no longer supported ****************\n");
            GSlogWrite("GSparticle: ***************************************************************************\n");
            goto fail;
        default:
            GSlogWrite("GSparticle: unknown version\n");
            goto fail;
        case 0x47505431:
            hdr->cmd = (gc_be16*)((u8*)hdr->cmd + GC_ADDR32(hdr));
            hdr->tex = (int*)((u8*)hdr->tex + GC_ADDR32(hdr));
            hdr->ref = (u32*)((u8*)hdr->ref + GC_ADDR32(hdr));
            int ver = *hdr->cmd;
            if (ver != 0x43) {
                GSlogWrite("GSparticle: version mismatch between system(%d) and ptcl-file(%d)", 0x43, ver);
                goto fail;
            }
            bank->data = hdr;
            DCFlushRange(hdr->tex, (hdr->texSize + 0x1F) & ~0x1F);
            psInitDataBank(id, (int*)hdr->cmd, hdr->tex, hdr->ref, NULL);
            break;
        }
    }
    bank->active = 1;
    bank->id = id;
    return (u8*)bank;
fail:
    if (bank->gens != NULL) {
        GSmemFree(bank->gens);
        bank->gens = NULL;
    }
    return NULL;
}

static void _particleSetGeneratorZDraw(void* gen, u8 flag) {
    GSlogWrite("GSparticle: changing the Z draw flag of a generator currently has no effect\n");
}

}

extern "C" {
void GSparticleFree(GSparticleBank* p0) {
    u8 *temp_r3;

    GSgfxRenderWaitForDrawComplete();
    GSparticleDestroyAllGenerators((GSparticleBank*)(p0), 1);
    temp_r3 = (*(u8 **)&((_GSparticleBank*)(p0))->gens);
    if (temp_r3 != NULL) {
        GSmemFree((void*)(temp_r3));
        (*(u8 **)&((_GSparticleBank*)(p0))->gens) = NULL;
    }
    (*(u8 **)&((_GSparticleBank*)(p0))->gens) = NULL;
    (*(s8 *)&((_GSparticleBank*)(p0))->genCount) = 0;
    if ((u8) (*(u8 *)&((_GSparticleBank*)(p0))->type) != 0) {
        peBankFreeFile((*(s32 *)&((_GSparticleBank*)(p0))->data));
    }
    (*(s8 *)&((_GSparticleBank*)(p0))->active) = 0;
}
}

extern "C" {
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* p0, s32 p1, s32 p2) {
    GSparticleGenerator* gen;
    s32 idx;

    if ((*(u8 *)&((_GSparticleBank*)(p0))->active) == 0) {
        return NULL;
    }
    if ((*(u8 *)&((_GSparticleBank*)(p0))->busy) != 0) {
        return NULL;
    }
    u8 kind = (*(u8 *)&((_GSparticleBank*)(p0))->type);
    if (kind != 0) {
        s32 idx = _particleBankFindFreeGenerator(p0, &kind);
        if (idx < 0) {
            return NULL;
        }
        u8* data = (u8*)peBankCreate((*(s32 *)&((_GSparticleBank*)(p0))->data));
        if (data == NULL) {
            return NULL;
        }
        gen = (GSparticleGenerator*)((*(u8 **)&((_GSparticleBank*)(p0))->gens) + idx * sizeof(_GSparticleGen));
        if ((*(u8 *)&((_GSparticleGen*)(gen))->native) == 0) {
            return NULL;
        }
        HSD_CObj* cam = (*(HSD_CObj **)&((_GSparticleBank*)(p0))->camera);
        if (data != NULL) {
            (*(HSD_CObj **)PEBANK_ENGINE_PTR(data)) = cam;
        }
        peBankStart(data);
        (*(u8 **)&((_GSparticleGen*)(gen))->data) = data;
        _invalidateVtx = 1;
    } else {
        idx = _particleBankFindFreeGenerator(p0, &kind);
        if (idx < 0) {
            _particleBankDestroyOldestGenerator((_GSparticleBank*)p0);
            idx = _particleBankFindFreeGenerator(p0, &(*(u8 *)&((_GSparticleBank*)(p0))->type));
            if (idx < 0) {
                return NULL;
            }
        }
        u8* data = (u8*)GSmemAlloc(sizeof(_GSparticleGenData));
        if (data == NULL) {
            return NULL;
        }
        s32 linked = 0;
        if ((u8)p2 == 1) {
            linked = 1;
        }
        (*(HSD_Generator **)&((_GSparticleGenData*)(data))->generator) = psCreateGeneratorID(linked, (*(u8 *)&((_GSparticleBank*)(p0))->id), p1);
        HSD_Generator* ps = (*(HSD_Generator **)&((_GSparticleGenData*)(data))->generator);
        if (ps == NULL) {
            GSmemFree(data);
            return NULL;
        }
        (*(s8 *)((u8*)&((PSGenerator*)(ps))->pad16 + 0x1)) = 1;
        psGeneratorSetCamera((*(HSD_Generator **)&((_GSparticleGenData*)(data))->generator), (*(HSD_CObj **)&((_GSparticleBank*)(p0))->camera));
        (*(s16 *)&((_GSparticleGenData*)(data))->id) = p1;
        (*(s8 *)&((_GSparticleGenData*)(data))->linked) = p2;
        (*(s32 *)&((_GSparticleGenData*)(data))->serial) = GSgfxVideoGetVsyncCount();
        if ((*(u16 *)&((PSGenerator*)((*(HSD_Generator **)&((_GSparticleGenData*)(data))->generator)))->maxLife) == 0) {
            (*(s8 *)&((_GSparticleGenData*)(data))->infinite) = 1;
        } else {
            (*(s8 *)&((_GSparticleGenData*)(data))->infinite) = 0;
        }
        gen = (GSparticleGenerator*)((*(u8 **)&((_GSparticleBank*)(p0))->gens) + idx * sizeof(_GSparticleGen));
        if ((*(u8 *)&((_GSparticleGen*)(gen))->native) != 0) {
            return NULL;
        }
        (*(u8 **)&((_GSparticleGen*)(gen))->data) = data;
    }
    _invalidateTex = 1;
    (*(s32 *)&((_GSparticleGen*)(gen))->attachMode) = 0;
    (*(s32 *)&((_GSparticleGen*)(gen))->model) = 0;
    (*(s32 *)&((_GSparticleGen*)(gen))->partIndex) = 0;
    (*(s8 *)&((_GSparticleGen*)(gen))->f1) = 0;
    (*(s8 *)&((_GSparticleGen*)(gen))->f2) = 0;
    (*(GSparticleBank **)&((_GSparticleGen*)(gen))->bank) = p0;
    return gen;
}
}

extern "C" {
void GSparticleAttachGeneratorToGSpart(void *p0, void *p1, s32 p2, s8 p3, u8 p4, u8 p5) {
    GSquat q;
    u8 *temp_r3;
    u8 *temp_r3_2;
    u8 *temp_r3_3;
    u8 *temp_r3_4;
    u8 *temp_r3_5;
    u8 *temp_r3_6;
    u8 *temp_r3_7;
    u8 *temp_r3_8;
    u8 *temp_r3_9;
    u8 *temp_r4;
    u8 *temp_r4_2;
    u8 *temp_r4_3;

    if (((u8 *) (*(u8 **)&((_GSparticleGen*)(p0))->data) != NULL) && ((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) == 0) && (p2 != 0)) {
        (*(s32 *)&((_GSparticleGen*)(p0))->model) = (s32) (*(s32 *)&((GSparticlePartView*)(p1))->model);
        (*(s32 *)&((_GSparticleGen*)(p0))->partIndex) = (s32) (*(u16 *)&((GSparticlePartView*)(p1))->index);
        if (p4 == 1) {
            (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]) = 0.0f;
            (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]) = 0.0f;
            (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]) = 0.0f;
            (*(f32 *)&((_GSparticleGen*)(p0))->rot[0]) = 0.0f;
            (*(f32 *)&((_GSparticleGen*)(p0))->rot[1]) = 0.0f;
            (*(f32 *)&((_GSparticleGen*)(p0))->rot[2]) = 0.0f;
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]) = 1.0f;
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]) = 1.0f;
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]) = 1.0f;
        } else if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            temp_r3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if (temp_r3 != NULL) {
                (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]) = (f32) PEBANK_PARAM(temp_r3, 0);
                (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]) = (f32) PEBANK_PARAM(temp_r3, 1);
                (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]) = (f32) PEBANK_PARAM(temp_r3, 2);
            } else {
                (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]) = 0.0f;
                (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]) = 0.0f;
                (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]) = 0.0f;
            }
            temp_r3_2 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if (temp_r3_2 != NULL) {
                q.x = PEBANK_PARAM(temp_r3_2, 3);
                q.y = PEBANK_PARAM(temp_r3_2, 4);
                q.z = PEBANK_PARAM(temp_r3_2, 5);
                q.w = PEBANK_PARAM(temp_r3_2, 6);
            } else {
                q.x = 0.0f;
                q.y = 0.0f;
                q.z = 0.0f;
                q.w = 1.0f;
            }
            GSvecMakeFromQuat((GSvec*)((_GSparticleGen*)(p0))->rot, &q);
            temp_r3_3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if (temp_r3_3 != NULL) {
                (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]) = (f32) PEBANK_PARAM(temp_r3_3, 7);
                (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]) = (f32) PEBANK_PARAM(temp_r3_3, 8);
                (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]) = (f32) PEBANK_PARAM(temp_r3_3, 9);
            } else {
                (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]) = 1.0f;
                (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]) = 1.0f;
                (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]) = 1.0f;
            }
        } else {
            temp_r3_4 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]) = (f32) (*(f32 *)&((_GSparticleGenData*)(temp_r3_4))->pos[0]);
            (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]) = (f32) (*(f32 *)&((_GSparticleGenData*)(temp_r3_4))->pos[1]);
            (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]) = (f32) (*(f32 *)&((_GSparticleGenData*)(temp_r3_4))->pos[2]);
            temp_r3_5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            (*(f32 *)&((_GSparticleGen*)(p0))->rot[0]) = (f32) (*(f32 *)&((_GSparticleGenData*)(temp_r3_5))->rot[0]);
            (*(f32 *)&((_GSparticleGen*)(p0))->rot[1]) = (f32) (*(f32 *)&((_GSparticleGenData*)(temp_r3_5))->rot[1]);
            (*(f32 *)&((_GSparticleGen*)(p0))->rot[2]) = (f32) (*(f32 *)&((_GSparticleGenData*)(temp_r3_5))->rot[2]);
            temp_r3_6 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]) = (f32) (*(f32 *)&((_GSparticleGenData*)(temp_r3_6))->scale[0]);
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]) = (f32) (*(f32 *)&((_GSparticleGenData*)(temp_r3_6))->scale[1]);
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]) = (f32) (*(f32 *)&((_GSparticleGenData*)(temp_r3_6))->scale[2]);
        }
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            temp_r4 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if (temp_r4 != NULL) {
                PEBANK_PARAM(temp_r4, 0) = (f32) (*(f32 *)((s8 *)(&zeroVector) + (0)));
                PEBANK_PARAM(temp_r4, 1) = (f32) (*(f32 *)((s8 *)(&zeroVector) + (4)));
                PEBANK_PARAM(temp_r4, 2) = (f32) (*(f32 *)((s8 *)(&zeroVector) + (8)));
            }
            temp_r4_2 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if (temp_r4_2 != NULL) {
                PEBANK_PARAM(temp_r4_2, 3) = (f32) (*(f32 *)((s8 *)(&zeroQuaternion) + (0)));
                PEBANK_PARAM(temp_r4_2, 4) = (f32) (*(f32 *)((s8 *)(&zeroQuaternion) + (4)));
                PEBANK_PARAM(temp_r4_2, 5) = (f32) (*(f32 *)((s8 *)(&zeroQuaternion) + (8)));
                PEBANK_PARAM(temp_r4_2, 6) = (f32) (*(f32 *)((s8 *)(&zeroQuaternion) + (0xC)));
            }
            temp_r4_3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if (temp_r4_3 != NULL) {
                PEBANK_PARAM(temp_r4_3, 7) = (f32) (*(f32 *)((s8 *)(&unitScaleVector) + (0)));
                PEBANK_PARAM(temp_r4_3, 8) = (f32) (*(f32 *)((s8 *)(&unitScaleVector) + (4)));
                PEBANK_PARAM(temp_r4_3, 9) = (f32) (*(f32 *)((s8 *)(&unitScaleVector) + (8)));
            }
        } else {
            temp_r3_7 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            (*(f32 *)&((_GSparticleGenData*)(temp_r3_7))->pos[0]) = 0.0f;
            (*(f32 *)&((_GSparticleGenData*)(temp_r3_7))->pos[1]) = 0.0f;
            (*(f32 *)&((_GSparticleGenData*)(temp_r3_7))->pos[2]) = 0.0f;
            temp_r3_8 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            (*(f32 *)&((_GSparticleGenData*)(temp_r3_8))->rot[0]) = 0.0f;
            (*(f32 *)&((_GSparticleGenData*)(temp_r3_8))->rot[1]) = 0.0f;
            (*(f32 *)&((_GSparticleGenData*)(temp_r3_8))->rot[2]) = 0.0f;
            temp_r3_9 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            (*(f32 *)&((_GSparticleGenData*)(temp_r3_9))->scale[0]) = 1.0f;
            (*(f32 *)&((_GSparticleGenData*)(temp_r3_9))->scale[1]) = 1.0f;
            (*(f32 *)&((_GSparticleGenData*)(temp_r3_9))->scale[2]) = 1.0f;
            if (p5 != 0) {
                psLinkChildGensToJObj((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)((*(u8 **)&((_GSparticleGen*)(p0))->data)))->generator)), (void*)((*(u8 **)&((GSparticlePartView*)(p1))->jobj)));
            }
        }
        (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) = p2;
        (*(s8 *)&((_GSparticleGen*)(p0))->f1) = p3;
        (*(s8 *)&((_GSparticleGen*)(p0))->f2) = 1;
    }
}
}

extern "C" {
void GSparticleDetachGeneratorFromGSpart(void *p0, u8 p1) {
    f32 var_f1_3;
    f32 var_f1_2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f1;
    f32 temp_f2;
    f32 v8[4];
    u8 *temp_r3;
    u8 *temp_r3_2;
    u8 *temp_r4;
    u8 *temp_r4_2;
    u8 *temp_r4_3;

    if (((u8 *) (*(u8 **)&((_GSparticleGen*)(p0))->data) != NULL) && ((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) != 0)) {
        GSmodelSet60fpsAnimFlag((_GSmodel*)((*(_GSmodel **)&((_GSparticleGen*)(p0))->model)), 0U);
        (*(_GSmodel **)&((_GSparticleGen*)(p0))->model) = NULL;
        (*(s32 *)&((_GSparticleGen*)(p0))->partIndex) = 0;
        (*(s8 *)&((_GSparticleGen*)(p0))->f2) = 0;
        (*(s8 *)&((_GSparticleGen*)(p0))->f1) = 0;
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) == 0) {
            psUnlinkChildGensFromJObj((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)((*(u8 **)&((_GSparticleGen*)(p0))->data)))->generator)));
        }
        (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) = 0;
        if (p1 == 0) {
            temp_r4 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if ((temp_r4 != NULL) && ((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) == 0)) {
                if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                    if (temp_r4 != NULL) {
                        PEBANK_PARAM(temp_r4, 0) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]);
                        PEBANK_PARAM(temp_r4, 1) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]);
                        PEBANK_PARAM(temp_r4, 2) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]);
                    }
                } else {
                    (*(f32 *)&((_GSparticleGenData*)(temp_r4))->pos[0]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]);
                    (*(f32 *)&((_GSparticleGenData*)(temp_r4))->pos[1]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]);
                    (*(f32 *)&((_GSparticleGenData*)(temp_r4))->pos[2]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]);
                    (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r4))->generator)))->pad1A + 0x6)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]);
                    (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r4))->generator)))->pad1A + 0xA)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]);
                    (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r4))->generator)))->pad1A + 0xE)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]);
                }
            }
            temp_r4_2 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if ((temp_r4_2 != NULL) && ((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) == 0)) {
                if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                    EulerToQuat((Vec*)(((u8*)(p0) + 0x1C)), (Quaternion*)(v8));
                    temp_r3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                    if (temp_r3 != NULL) {
                        PEBANK_PARAM(temp_r3, 3) = v8[0];
                        PEBANK_PARAM(temp_r3, 4) = v8[1];
                        PEBANK_PARAM(temp_r3, 5) = v8[2];
                        PEBANK_PARAM(temp_r3, 6) = v8[3];
                    }
                } else {
                    (*(f32 *)&((_GSparticleGenData*)(temp_r4_2))->rot[0]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[0]);
                    (*(f32 *)&((_GSparticleGenData*)(temp_r4_2))->rot[1]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[1]);
                    (*(f32 *)&((_GSparticleGenData*)(temp_r4_2))->rot[2]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[2]);
                    (*(f32 *)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r4_2))->generator)))->pad90) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[0]);
                    (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r4_2))->generator)))->pad90 + 0x4)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[1]);
                    (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r4_2))->generator)))->pad90 + 0x8)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[2]);
                }
            }
            if (((u8 *) (*(u8 **)&((_GSparticleGen*)(p0))->data) != NULL) && ((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) == 0)) {
                temp_f2 = (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]);
                if (temp_f2 > 0.0f) {
                    var_f0 = temp_f2;
                } else {
                    var_f0 = -temp_f2;
                }
                var_f1 = 0.00001f;
                if (var_f0 < 0.00001f) {
                    if (temp_f2 < 0.0f) {
                        var_f1 = -0.00001f;
                    }
                    (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]) = var_f1;
                }
                temp_f2_2 = (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]);
                if (temp_f2_2 > 0.0f) {
                    var_f0_2 = temp_f2_2;
                } else {
                    var_f0_2 = -temp_f2_2;
                }
                var_f1_2 = 0.00001f;
                if (var_f0_2 < 0.00001f) {
                    if (temp_f2_2 < 0.0f) {
                        var_f1_2 = -0.00001f;
                    }
                    (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]) = var_f1_2;
                }
                temp_f2_3 = (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]);
                if (temp_f2_3 > 0.0f) {
                    var_f0_3 = temp_f2_3;
                } else {
                    var_f0_3 = -temp_f2_3;
                }
                var_f1_3 = 0.00001f;
                if (var_f0_3 < 0.00001f) {
                    if (temp_f2_3 < 0.0f) {
                        var_f1_3 = -0.00001f;
                    }
                    (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]) = var_f1_3;
                }
                if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                    temp_r3_2 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                    if (temp_r3_2 != NULL) {
                        PEBANK_PARAM(temp_r3_2, 7) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]);
                        PEBANK_PARAM(temp_r3_2, 8) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]);
                        PEBANK_PARAM(temp_r3_2, 9) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]);
                    }
                } else {
                    temp_r4_3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                    (*(f32 *)&((_GSparticleGenData*)(temp_r4_3))->scale[0]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]);
                    (*(f32 *)&((_GSparticleGenData*)(temp_r4_3))->scale[1]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]);
                    (*(f32 *)&((_GSparticleGenData*)(temp_r4_3))->scale[2]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]);
                    (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r4_3))->generator)))->pad90 + 0xC)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]);
                    (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r4_3))->generator)))->pad90 + 0x10)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]);
                    (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r4_3))->generator)))->pad90 + 0x14)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]);
                }
            }
        }
    }
}
}

extern "C" {
void GSparticleSetGeneratorPosition(GSparticleGenerator* p0, Vec* p1) {
    u8 *temp_r5;

    temp_r5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r5 != NULL) {
        if ((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) == 0) {
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                if (temp_r5 != NULL) {
                    PEBANK_PARAM(temp_r5, 0) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
                    PEBANK_PARAM(temp_r5, 1) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
                    PEBANK_PARAM(temp_r5, 2) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
                }
            } else {
                (*(f32 *)&((_GSparticleGenData*)(temp_r5))->pos[0]) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
                (*(f32 *)&((_GSparticleGenData*)(temp_r5))->pos[1]) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
                (*(f32 *)&((_GSparticleGenData*)(temp_r5))->pos[2]) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r5))->generator)))->pad1A + 0x6)) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r5))->generator)))->pad1A + 0xA)) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r5))->generator)))->pad1A + 0xE)) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
            }
        } else {
            (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
            (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
            (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
        }
    }
}
}

extern "C" {
void GSparticleSetGeneratorRotation(void *p0, f32 *p1) {
    f32 v8[4];
    u8 *temp_r3;
    u8 *temp_r5;

    temp_r5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r5 != NULL) {
        if ((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) == 0) {
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                EulerToQuat((Vec*)((Vec *) p1), (Quaternion*)(v8));
                temp_r3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r3 != NULL) {
                    PEBANK_PARAM(temp_r3, 3) = v8[0];
                    PEBANK_PARAM(temp_r3, 4) = v8[1];
                    PEBANK_PARAM(temp_r3, 5) = v8[2];
                    PEBANK_PARAM(temp_r3, 6) = v8[3];
                }
            } else {
                (*(f32 *)&((_GSparticleGenData*)(temp_r5))->rot[0]) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
                (*(f32 *)&((_GSparticleGenData*)(temp_r5))->rot[1]) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
                (*(f32 *)&((_GSparticleGenData*)(temp_r5))->rot[2]) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
                (*(f32 *)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r5))->generator)))->pad90) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r5))->generator)))->pad90 + 0x4)) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r5))->generator)))->pad90 + 0x8)) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
            }
        } else {
            (*(f32 *)&((_GSparticleGen*)(p0))->rot[0]) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
            (*(f32 *)&((_GSparticleGen*)(p0))->rot[1]) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
            (*(f32 *)&((_GSparticleGen*)(p0))->rot[2]) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
        }
    }
}
}

extern "C" {
void GSparticleSetGeneratorScale(void *p0, void *p1, u8 p2, u8 p3) {
    f32 var_f1_2;
    f32 var_f1_3;
    f32 temp_f2_3;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f1;
    f32 temp_f2;
    f32 temp_f2_2;
    u8 *temp_r7;
    u8 *temp_r8;

    if ((u8 *) (*(u8 **)&((_GSparticleGen*)(p0))->data) != NULL) {
        if ((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) == 0) {
            temp_f2 = (*(f32 *)((s8 *)(p1) + (0)));
            if (temp_f2 > 0.0f) {
                var_f0 = temp_f2;
            } else {
                var_f0 = -temp_f2;
            }
            var_f1 = 0.00001f;
            if (var_f0 < 0.00001f) {
                if (temp_f2 < 0.0f) {
                    var_f1 = -0.00001f;
                }
                (*(f32 *)((s8 *)(p1) + (0))) = var_f1;
            }
            temp_f2_2 = (*(f32 *)((s8 *)(p1) + (4)));
            if (temp_f2_2 > 0.0f) {
                var_f0_2 = temp_f2_2;
            } else {
                var_f0_2 = -temp_f2_2;
            }
            var_f1_2 = 0.00001f;
            if (var_f0_2 < 0.00001f) {
                if (temp_f2_2 < 0.0f) {
                    var_f1_2 = -0.00001f;
                }
                (*(f32 *)((s8 *)(p1) + (4))) = var_f1_2;
            }
            temp_f2_3 = (*(f32 *)((s8 *)(p1) + (8)));
            if (temp_f2_3 > 0.0f) {
                var_f0_3 = temp_f2_3;
            } else {
                var_f0_3 = -temp_f2_3;
            }
            var_f1_3 = 0.00001f;
            if (var_f0_3 < 0.00001f) {
                if (temp_f2_3 < 0.0f) {
                    var_f1_3 = -0.00001f;
                }
                (*(f32 *)((s8 *)(p1) + (8))) = var_f1_3;
            }
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                temp_r7 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r7 != NULL) {
                    PEBANK_PARAM(temp_r7, 7) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
                    PEBANK_PARAM(temp_r7, 8) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
                    PEBANK_PARAM(temp_r7, 9) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
                }
            } else {
                temp_r8 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r8))->scale[0]) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
                (*(f32 *)&((_GSparticleGenData*)(temp_r8))->scale[1]) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
                (*(f32 *)&((_GSparticleGenData*)(temp_r8))->scale[2]) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
                (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r8))->generator)))->pad90 + 0xC)) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
                (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r8))->generator)))->pad90 + 0x10)) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
                (*(f32 *)((u8*)&((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r8))->generator)))->pad90 + 0x14)) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
            }
        } else {
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]) = (f32) (*(f32 *)((s8 *)(p1) + (0)));
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]) = (f32) (*(f32 *)((s8 *)(p1) + (4)));
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]) = (f32) (*(f32 *)((s8 *)(p1) + (8)));
        }
        if (((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) == 0) && (p2 == 1)) {
            psSetGeneratorAngleRadiusScale((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)((*(u8 **)&((_GSparticleGen*)(p0))->data)))->generator)), (f32*)((f32 *) p1), (u16)p3);
        }
    }
}
}

extern "C" {
u32 GSparticleGetGeneratorLife(GSparticleGenerator* p0) {
    u8 *temp_r3;

    temp_r3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r3 == NULL) {
        return 0U;
    }
    if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
        if (peBankIsInfinite((u32)(temp_r3)) != 0) {
            return -1U;
        }
        return (u32) (peBankGetLife((*(u8 **)&((_GSparticleGen*)(p0))->data)) * ((f32) GSgfxVideoGetVsyncRate()));
    }
    if ((u8) (*(u8 *)&((_GSparticleGenData*)(temp_r3))->infinite) == 1) {
        return -1U;
    }
    return psGetGeneratorChildMaxLife((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r3))->generator)));
}
}

extern "C" {
s32 GSparticleIsGeneratorAlive(void *p0) {
    u32 var_r3;
    u32 var_r3_2;
    u8 temp_r0;
    u8 *temp_r3;
    u8 *temp_r3_2;

    temp_r3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r3 == NULL) {
        return 0;
    }
    temp_r0 = (*(u8 *)&((_GSparticleGen*)(p0))->native);
    if (temp_r0 != 0) {
        if (temp_r3 == NULL) {
            var_r3_2 = 0;
        } else if (temp_r0 != 0) {
            if (peBankIsInfinite((u32)(temp_r3)) != 0) {
                var_r3_2 = -1U;
            } else {
                var_r3_2 = (u32) (peBankGetLife((*(u8 **)&((_GSparticleGen*)(p0))->data)) * ((f32) GSgfxVideoGetVsyncRate()));
            }
        } else if ((u8) (*(u8 *)&((_GSparticleGenData*)(temp_r3))->infinite) == 1) {
            var_r3_2 = -1U;
        } else {
            var_r3_2 = psGetGeneratorChildMaxLife((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r3))->generator)));
        }
        return var_r3_2 != 0;
    }
    if ((u8) (*(u8 *)&((_GSparticleGenData*)(temp_r3))->infinite) != 0) {
        return 1;
    }
    if (psGetParticleChildCount((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r3))->generator))) != 0) {
        return 1;
    }
    temp_r3_2 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r3_2 == NULL) {
        var_r3 = 0;
    } else if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
        if (peBankIsInfinite((u32)(temp_r3_2)) != 0) {
            var_r3 = -1U;
        } else {
            var_r3 = (u32) (peBankGetLife((*(u8 **)&((_GSparticleGen*)(p0))->data)) * ((f32) GSgfxVideoGetVsyncRate()));
        }
    } else if ((u8) (*(u8 *)&((_GSparticleGenData*)(temp_r3_2))->infinite) == 1) {
        var_r3 = -1U;
    } else {
        var_r3 = psGetGeneratorChildMaxLife((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r3_2))->generator)));
    }
    return var_r3 != 0;
}
}

extern "C" {
void GSparticleDisactivateBank(GSparticleBank* bank) {
    bank->inactive = 1;
}
}

extern "C" {
void GSparticleActivateBank(GSparticleBank* bank) {
    bank->inactive = 0;
}
}

extern "C" {
void GSparticleSetVelocityRotationInLocal(void *p0, u8 p1) {
    u8 *temp_r5;

    temp_r5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r5 != NULL) {
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetVelocityRotationInLocal((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r5))->generator)), (u16)p1);
        }
    }
}
}

extern "C" {
void GSparticleSetOffsetRotationInLocal(void *p0, u8 p1, u8 p2) {
    u8 *temp_r6;

    temp_r6 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r6 != NULL) {
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            if (temp_r6 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetOffsetRotationInLocal((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r6))->generator)), (u16)p1, (u16)p2);
        }
    }
}
}

extern "C" {
void GSparticleSetParticleTextureScaling(void *p0, u8 p1) {
    u8 *temp_r5;

    temp_r5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r5 != NULL) {
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetParticleTexScaling((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r5))->generator)), (u16)p1);
        }
    }
}
}

extern "C" {
void GSparticleSetTornadoScaling(void *p0, u8 p1, u8 p2) {
    u8 *temp_r6;

    temp_r6 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r6 != NULL) {
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            if (temp_r6 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetTornadoScaling((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r6))->generator)), (u16)p1, (u16)p2);
        }
    }
}
}

extern "C" {
void GSparticleSetNodeScaling(void *p0, u8 p1) {
    u8 *temp_r5;

    temp_r5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r5 != NULL) {
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetNodeScaling((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r5))->generator)), (u16)p1);
        }
    }
}
}

extern "C" {
void GSparticleSetRandomVelocityScaling(void *p0, u8 p1) {
    u8 *temp_r5;

    temp_r5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r5 != NULL) {
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetRandomVelocityScaling((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r5))->generator)), (u16)p1);
        }
    }
}
}

extern "C" {
void GSparticleSetGeneratorVisibility(void *p0, u8 p1) {
    u8 *temp_r5;

    temp_r5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r5 != NULL) {
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                    (*(s32 *)PEBANK_FLAGS_PTR(temp_r5)) = (s32) ((*(s32 *)PEBANK_FLAGS_PTR(temp_r5)) | 4);
                    return;
                }
                (*(s32 *)PEBANK_FLAGS_PTR(temp_r5)) = (s32) ((*(s32 *)PEBANK_FLAGS_PTR(temp_r5)) & 0xFFFFFFFB);
            }
        } else {
            psSetParticleVisibility((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r5))->generator)), (u16)p1);
        }
    }
}
}

extern "C" {
void GSparticleSetBankVisibility(GSparticleBank* p0, bool p1) {
    u8 *var_r30;
    u8 *temp_r3;
    u32 var_r29;

    var_r29 = 0U;
    var_r30 = (*(u8 **)&((_GSparticleBank*)(p0))->gens);
    while (var_r29 < (u8) (*(u8 *)&((_GSparticleBank*)(p0))->genCount)) {
        temp_r3 = (*(u8 **)&((_GSparticleGen*)(var_r30))->data);
        if (temp_r3 != NULL) {
            if ((u8) (*(u8 *)&((_GSparticleGen*)(var_r30))->native) != 0) {
                if (temp_r3 != NULL) {
                    if (p1 != 0) {
                        (*(s32 *)PEBANK_FLAGS_PTR(temp_r3)) = (s32) ((*(s32 *)PEBANK_FLAGS_PTR(temp_r3)) | 4);
                    } else {
                        (*(s32 *)PEBANK_FLAGS_PTR(temp_r3)) = (s32) ((*(s32 *)PEBANK_FLAGS_PTR(temp_r3)) & 0xFFFFFFFB);
                    }
                }
            } else {
                psSetParticleVisibility((PSGenerator*)((*(PSGenerator **)&((_GSparticleGenData*)(temp_r3))->generator)), p1);
            }
        }
        var_r29 += 1;
        var_r30 += sizeof(_GSparticleGen);
    }
}
}

extern "C" {
void GSparticleStopGenerator(void *p0) {
    if (((u32) (*(u32 *)&((_GSparticleGen*)(p0))->data) != 0) && ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0)) {
        if (peBankIsInfinite((*(u32 *)&((_GSparticleGen*)(p0))->data)) != 0) {
            peBankStopLoop((*(u32 *)&((_GSparticleGen*)(p0))->data));
            return;
        }
        peBankStop((*(u32 *)&((_GSparticleGen*)(p0))->data));
    }
}
}

extern "C" {
void GSparticleDestroyGenerator(void *p0, bool p1) {
    HSD_Generator *temp_r4;
    u8 *temp_r3;

    if ((u8 *) (*(u8 **)&((_GSparticleGen*)(p0))->data) != NULL) {
        if ((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) != 0) {
            GSparticleDetachGeneratorFromGSpart(p0, 0U);
        }
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            peBankFree((*(u8 **)&((_GSparticleGen*)(p0))->data));
            (*(u8 **)&((_GSparticleGen*)(p0))->data) = NULL;
            return;
        }
        if (p1 == 1) {
            temp_r4 = (*(HSD_Generator **)&((_GSparticleGenData*)((*(u8 **)&((_GSparticleGen*)(p0))->data)))->generator);
            psKillFamily((s32) (*(u16 *)&((PSGenerator*)(temp_r4))->familyId), (s32) (*(u8 *)&((PSGenerator*)(temp_r4))->linkNo));
        }
        psKillGenerator((HSD_Generator*)((*(HSD_Generator **)&((_GSparticleGenData*)((*(u8 **)&((_GSparticleGen*)(p0))->data)))->generator)));
        temp_r3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
        if (temp_r3 != NULL) {
            GSmemFree((void*)(temp_r3));
            (*(u8 **)&((_GSparticleGen*)(p0))->data) = NULL;
        }
    }
}
}

extern "C" {
void GSparticleDestroyAllGenerators(GSparticleBank* p0, bool p1) {
    u8 *var_r31;
    u32 var_r30;

    var_r30 = 0U;
    var_r31 = (*(u8 **)&((_GSparticleBank*)(p0))->gens);
    while (var_r30 < (u8) (*(u8 *)&((_GSparticleBank*)(p0))->genCount)) {
        if ((u32) (*(u32 *)&((_GSparticleGen*)(var_r31))->data) != 0U) {
            GSparticleDestroyGenerator(var_r31, p1);
        }
        var_r30 += 1;
        var_r31 += sizeof(_GSparticleGen);
    }
}
}

extern "C" {
void GSparticleBankSetCamera(_GSparticleBank* bank, HSD_CObj* camera) {
    if (bank == NULL || bank->active == 0) {
        return;
    }
    bank->camera = camera;
    _GSparticleGen* gen;
    u8 n;
    n = bank->genCount;
    gen = bank->gens;
    while (n--) {
        _GSparticleGenData* data = gen->data;
        if (data != NULL && gen->data != NULL) {
            if (gen->native) {
                if (data != NULL) {
                    (*(HSD_CObj**)PEBANK_ENGINE_PTR(data)) = camera;
                }
            } else {
                psGeneratorSetCamera(data->generator, camera);
            }
        }
        gen++;
    }
}
}

extern "C" {
void GSparticleGeneratorSetCamera(void *p0, s32 p1) {
    u8 *temp_r5;

    temp_r5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
    if (temp_r5 != NULL) {
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            if (temp_r5 != NULL) {
                (*(s32 *)PEBANK_ENGINE_PTR(temp_r5)) = p1;
            }
        } else {
            psGeneratorSetCamera((HSD_Generator*)((*(HSD_Generator **)&((_GSparticleGenData*)(temp_r5))->generator)), (HSD_CObj*)((HSD_CObj *) p1));
        }
    }
}
}

extern "C++" {
static void _particleUpdateAttachment(_GSparticleGen* p0) {
    f32 v8C[3];
    f32 v80[3];
    f32 v74[3];
    f32 unksp64[4];
    f32 unksp58[3];
    f32 v48[4];
    f32 v38[4];
    f32 q28[4];
    f32 q18[4];
    f32 v8[4];
    f32 var_f1_3;
    GSpart *temp_r3;
    f32 var_f1_2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 var_f0;
    f32 var_f0_10;
    f32 var_f0_11;
    f32 var_f0_12;
    f32 var_f0_13;
    f32 var_f0_14;
    f32 var_f0_15;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f0_5;
    f32 var_f0_6;
    f32 var_f0_7;
    f32 var_f0_8;
    f32 var_f0_9;
    f32 var_f1;
    f32 var_f1_10;
    f32 var_f1_11;
    f32 var_f1_12;
    f32 var_f1_13;
    f32 var_f1_14;
    f32 var_f1_15;
    f32 temp_f2;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f1_6;
    f32 var_f1_7;
    f32 var_f1_8;
    f32 var_f1_9;
    s32 temp_r0;
    u8 *temp_r3_11;
    u8 *temp_r3_12;
    u8 *temp_r3_13;
    u8 *temp_r3_14;
    u8 *temp_r3_15;
    u8 *temp_r3_16;
    u8 *temp_r3_2;
    u8 *temp_r3_3;
    u8 *temp_r3_4;
    u8 *temp_r3_6;
    u8 *temp_r3_8;
    u8 *temp_r4;
    u8 *temp_r4_10;
    u8 *temp_r4_11;
    u8 *temp_r4_12;
    u8 *temp_r4_13;
    u8 *temp_r4_14;
    u8 *temp_r4_15;
    u8 *temp_r4_2;
    u8 *temp_r4_3;
    u8 *temp_r4_4;
    u8 *temp_r4_5;
    u8 *temp_r4_6;
    u8 *temp_r4_7;
    u8 *temp_r4_8;
    u8 *temp_r4_9;

    if (((s32) (*(s32 *)&((_GSparticleGen*)(p0))->attachMode) != 0) && ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->f2) != 0)) {
        temp_r3 = GSmodelGetPart((_GSmodel*)((*(_GSmodel **)&((_GSparticleGen*)(p0))->model)), (*(s32 *)&((_GSparticleGen*)(p0))->partIndex));
        GSpartGetTransform((GSpart*)(temp_r3), (GSvec*)(v8C), (GSvec*)(v80), (GSvec*)(v74));
        GSpartFree((GSpart*)(temp_r3));
        EulerToQuat((Vec*)(v80), (Quaternion*)(unksp64));
        GSvecTransformQuat((GSvec*)(unksp58), (const GSquat*)(unksp64), (const GSvec*)(((u8*)((GCsptr)p0) + 0x10)));
        PSVECAdd((const register Vec*)(v8C), (const register Vec*)(unksp58), (register Vec*)(v8C));
        PSVECAdd((const register Vec*)(v80), (const register Vec*)(((u8*)((GCsptr)p0) + 0x1C)), (register Vec*)(v80));
        v74[0] *= (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]);
        v74[1] *= (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]);
        v74[2] *= (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]);
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            temp_r3_2 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if (temp_r3_2 != NULL) {
                PEBANK_PARAM(temp_r3_2, 0) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]);
                PEBANK_PARAM(temp_r3_2, 1) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]);
                PEBANK_PARAM(temp_r3_2, 2) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]);
            }
        } else {
            temp_r4 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            (*(f32 *)&((_GSparticleGenData*)(temp_r4))->pos[0]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]);
            (*(f32 *)&((_GSparticleGenData*)(temp_r4))->pos[1]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]);
            (*(f32 *)&((_GSparticleGenData*)(temp_r4))->pos[2]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]);
            (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4))->generator)))->pad1A + 0x6)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[0]);
            (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4))->generator)))->pad1A + 0xA)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[1]);
            (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4))->generator)))->pad1A + 0xE)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->pos[2]);
        }
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            EulerToQuat((Vec*)(((u8*)(p0) + 0x1C)), (Quaternion*)(v48));
            temp_r3_3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if (temp_r3_3 != NULL) {
                PEBANK_PARAM(temp_r3_3, 3) = v48[0];
                PEBANK_PARAM(temp_r3_3, 4) = v48[1];
                PEBANK_PARAM(temp_r3_3, 5) = v48[2];
                PEBANK_PARAM(temp_r3_3, 6) = v48[3];
            }
        } else {
            temp_r4_2 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            (*(f32 *)&((_GSparticleGenData*)(temp_r4_2))->rot[0]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[0]);
            (*(f32 *)&((_GSparticleGenData*)(temp_r4_2))->rot[1]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[1]);
            (*(f32 *)&((_GSparticleGenData*)(temp_r4_2))->rot[2]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[2]);
            (*(f32 *)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_2))->generator)))->pad90) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[0]);
            (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_2))->generator)))->pad90 + 0x4)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[1]);
            (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_2))->generator)))->pad90 + 0x8)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->rot[2]);
        }
        temp_f2 = (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]);
        if (temp_f2 > 0.0f) {
            var_f0 = temp_f2;
        } else {
            var_f0 = -temp_f2;
        }
        var_f1 = 0.00001f;
        if (var_f0 < 0.00001f) {
            if (temp_f2 < 0.0f) {
                var_f1 = -0.00001f;
            }
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]) = var_f1;
        }
        temp_f2_2 = (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]);
        if (temp_f2_2 > 0.0f) {
            var_f0_2 = temp_f2_2;
        } else {
            var_f0_2 = -temp_f2_2;
        }
        var_f1_2 = 0.00001f;
        if (var_f0_2 < 0.00001f) {
            if (temp_f2_2 < 0.0f) {
                var_f1_2 = -0.00001f;
            }
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]) = var_f1_2;
        }
        temp_f2_3 = (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]);
        if (temp_f2_3 > 0.0f) {
            var_f0_3 = temp_f2_3;
        } else {
            var_f0_3 = -temp_f2_3;
        }
        var_f1_3 = 0.00001f;
        if (var_f0_3 < 0.00001f) {
            if (temp_f2_3 < 0.0f) {
                var_f1_3 = -0.00001f;
            }
            (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]) = var_f1_3;
        }
        if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
            temp_r3_4 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            if (temp_r3_4 != NULL) {
                PEBANK_PARAM(temp_r3_4, 7) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]);
                PEBANK_PARAM(temp_r3_4, 8) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]);
                PEBANK_PARAM(temp_r3_4, 9) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]);
            }
        } else {
            temp_r4_3 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
            (*(f32 *)&((_GSparticleGenData*)(temp_r4_3))->scale[0]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]);
            (*(f32 *)&((_GSparticleGenData*)(temp_r4_3))->scale[1]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]);
            (*(f32 *)&((_GSparticleGenData*)(temp_r4_3))->scale[2]) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]);
            (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_3))->generator)))->pad90 + 0xC)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[0]);
            (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_3))->generator)))->pad90 + 0x10)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[1]);
            (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_3))->generator)))->pad90 + 0x14)) = (f32) (*(f32 *)&((_GSparticleGen*)(p0))->scale[2]);
        }
        switch ((*(s32 *)&((_GSparticleGen*)(p0))->attachMode)) {
        case 1:
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                u8* g = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (g != NULL) {
                    PEBANK_PARAM(g, 0) = v8C[0];
                    PEBANK_PARAM(g, 1) = v8C[1];
                    PEBANK_PARAM(g, 2) = v8C[2];
                }
            } else {
                temp_r4_4 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_4))->pos[0]) = v8C[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_4))->pos[1]) = v8C[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_4))->pos[2]) = v8C[2];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_4))->generator)))->pad1A + 0x6)) = v8C[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_4))->generator)))->pad1A + 0xA)) = v8C[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_4))->generator)))->pad1A + 0xE)) = v8C[2];
            }
            break;
        case 2:
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                EulerToQuat((Vec*)(v80), (Quaternion*)(v38));
                temp_r3_6 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r3_6 != NULL) {
                    PEBANK_PARAM(temp_r3_6, 3) = v38[0];
                    PEBANK_PARAM(temp_r3_6, 4) = v38[1];
                    PEBANK_PARAM(temp_r3_6, 5) = v38[2];
                    PEBANK_PARAM(temp_r3_6, 6) = v38[3];
                }
            } else {
                temp_r4_5 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_5))->rot[0]) = v80[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_5))->rot[1]) = v80[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_5))->rot[2]) = v80[2];
                (*(f32 *)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_5))->generator)))->pad90) = v80[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_5))->generator)))->pad90 + 0x4)) = v80[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_5))->generator)))->pad90 + 0x8)) = v80[2];
            }
            break;
        case 3:
            _particleClampScale(&v74[0]);
            _particleClampScale(&v74[1]);
            _particleClampScale(&v74[2]);
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                u8* g = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (g != NULL) {
                    PEBANK_PARAM(g, 7) = v74[0];
                    PEBANK_PARAM(g, 8) = v74[1];
                    PEBANK_PARAM(g, 9) = v74[2];
                }
            } else {
                temp_r4_6 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_6))->scale[0]) = v74[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_6))->scale[1]) = v74[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_6))->scale[2]) = v74[2];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_6))->generator)))->pad90 + 0xC)) = v74[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_6))->generator)))->pad90 + 0x10)) = v74[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_6))->generator)))->pad90 + 0x14)) = v74[2];
            }
            break;
        case 4:
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                temp_r3_8 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r3_8 != NULL) {
                    PEBANK_PARAM(temp_r3_8, 0) = v8C[0];
                    PEBANK_PARAM(temp_r3_8, 1) = v8C[1];
                    PEBANK_PARAM(temp_r3_8, 2) = v8C[2];
                }
            } else {
                temp_r4_7 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_7))->pos[0]) = v8C[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_7))->pos[1]) = v8C[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_7))->pos[2]) = v8C[2];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_7))->generator)))->pad1A + 0x6)) = v8C[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_7))->generator)))->pad1A + 0xA)) = v8C[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_7))->generator)))->pad1A + 0xE)) = v8C[2];
            }
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                EulerToQuat((Vec*)(v80), (Quaternion*)(q28));
                u8* g = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (g != NULL) {
                    PEBANK_PARAM(g, 3) = q28[0];
                    PEBANK_PARAM(g, 4) = q28[1];
                    PEBANK_PARAM(g, 5) = q28[2];
                    PEBANK_PARAM(g, 6) = q28[3];
                }
            } else {
                temp_r4_8 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_8))->rot[0]) = v80[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_8))->rot[1]) = v80[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_8))->rot[2]) = v80[2];
                (*(f32 *)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_8))->generator)))->pad90) = v80[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_8))->generator)))->pad90 + 0x4)) = v80[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_8))->generator)))->pad90 + 0x8)) = v80[2];
            }
            break;
        case 5:
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                EulerToQuat((Vec*)(v80), (Quaternion*)(q18));
                u8* g = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (g != NULL) {
                    PEBANK_PARAM(g, 3) = q18[0];
                    PEBANK_PARAM(g, 4) = q18[1];
                    PEBANK_PARAM(g, 5) = q18[2];
                    PEBANK_PARAM(g, 6) = q18[3];
                }
            } else {
                temp_r4_9 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_9))->rot[0]) = v80[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_9))->rot[1]) = v80[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_9))->rot[2]) = v80[2];
                (*(f32 *)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_9))->generator)))->pad90) = v80[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_9))->generator)))->pad90 + 0x4)) = v80[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_9))->generator)))->pad90 + 0x8)) = v80[2];
            }
            _particleClampScale(&v74[0]);
            _particleClampScale(&v74[1]);
            _particleClampScale(&v74[2]);
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                temp_r3_11 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r3_11 != NULL) {
                    PEBANK_PARAM(temp_r3_11, 7) = v74[0];
                    PEBANK_PARAM(temp_r3_11, 8) = v74[1];
                    PEBANK_PARAM(temp_r3_11, 9) = v74[2];
                }
            } else {
                temp_r4_10 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_10))->scale[0]) = v74[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_10))->scale[1]) = v74[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_10))->scale[2]) = v74[2];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_10))->generator)))->pad90 + 0xC)) = v74[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_10))->generator)))->pad90 + 0x10)) = v74[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_10))->generator)))->pad90 + 0x14)) = v74[2];
            }
            break;
        case 6:
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                temp_r3_12 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r3_12 != NULL) {
                    PEBANK_PARAM(temp_r3_12, 0) = v8C[0];
                    PEBANK_PARAM(temp_r3_12, 1) = v8C[1];
                    PEBANK_PARAM(temp_r3_12, 2) = v8C[2];
                }
            } else {
                temp_r4_11 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_11))->pos[0]) = v8C[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_11))->pos[1]) = v8C[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_11))->pos[2]) = v8C[2];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_11))->generator)))->pad1A + 0x6)) = v8C[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_11))->generator)))->pad1A + 0xA)) = v8C[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_11))->generator)))->pad1A + 0xE)) = v8C[2];
            }
            _particleClampScale(&v74[0]);
            _particleClampScale(&v74[1]);
            _particleClampScale(&v74[2]);
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                temp_r3_13 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r3_13 != NULL) {
                    PEBANK_PARAM(temp_r3_13, 7) = v74[0];
                    PEBANK_PARAM(temp_r3_13, 8) = v74[1];
                    PEBANK_PARAM(temp_r3_13, 9) = v74[2];
                }
            } else {
                temp_r4_12 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_12))->scale[0]) = v74[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_12))->scale[1]) = v74[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_12))->scale[2]) = v74[2];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_12))->generator)))->pad90 + 0xC)) = v74[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_12))->generator)))->pad90 + 0x10)) = v74[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_12))->generator)))->pad90 + 0x14)) = v74[2];
            }
            break;
        case 7:
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                temp_r3_14 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r3_14 != NULL) {
                    PEBANK_PARAM(temp_r3_14, 0) = v8C[0];
                    PEBANK_PARAM(temp_r3_14, 1) = v8C[1];
                    PEBANK_PARAM(temp_r3_14, 2) = v8C[2];
                }
            } else {
                temp_r4_13 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_13))->pos[0]) = v8C[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_13))->pos[1]) = v8C[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_13))->pos[2]) = v8C[2];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_13))->generator)))->pad1A + 0x6)) = v8C[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_13))->generator)))->pad1A + 0xA)) = v8C[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_13))->generator)))->pad1A + 0xE)) = v8C[2];
            }
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                EulerToQuat((Vec*)(v80), (Quaternion*)(v8));
                temp_r3_15 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r3_15 != NULL) {
                    PEBANK_PARAM(temp_r3_15, 3) = v8[0];
                    PEBANK_PARAM(temp_r3_15, 4) = v8[1];
                    PEBANK_PARAM(temp_r3_15, 5) = v8[2];
                    PEBANK_PARAM(temp_r3_15, 6) = v8[3];
                }
            } else {
                temp_r4_14 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_14))->rot[0]) = v80[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_14))->rot[1]) = v80[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_14))->rot[2]) = v80[2];
                (*(f32 *)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_14))->generator)))->pad90) = v80[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_14))->generator)))->pad90 + 0x4)) = v80[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_14))->generator)))->pad90 + 0x8)) = v80[2];
            }
            _particleClampScale(&v74[0]);
            _particleClampScale(&v74[1]);
            _particleClampScale(&v74[2]);
            if ((u8) (*(u8 *)&((_GSparticleGen*)(p0))->native) != 0) {
                temp_r3_16 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                if (temp_r3_16 != NULL) {
                    PEBANK_PARAM(temp_r3_16, 7) = v74[0];
                    PEBANK_PARAM(temp_r3_16, 8) = v74[1];
                    PEBANK_PARAM(temp_r3_16, 9) = v74[2];
                }
            } else {
                temp_r4_15 = (*(u8 **)&((_GSparticleGen*)(p0))->data);
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_15))->scale[0]) = v74[0];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_15))->scale[1]) = v74[1];
                (*(f32 *)&((_GSparticleGenData*)(temp_r4_15))->scale[2]) = v74[2];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_15))->generator)))->pad90 + 0xC)) = v74[0];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_15))->generator)))->pad90 + 0x10)) = v74[1];
                (*(f32 *)((u8*)&((PSGenerator*)((*(u8 **)&((_GSparticleGenData*)(temp_r4_15))->generator)))->pad90 + 0x14)) = v74[2];
            }
            break;
        }
        (*(bool *)&((_GSparticleGen*)(p0))->f2) = !(*(u8 *)&((_GSparticleGen*)(p0))->f1);
    }
}
}

extern "C++" {
#pragma optimize_for_size on
static void _particlePreUpdate(float frames) {
    static f32 sysdolRemain = 0.0f;
    u32 i;
    _GSparticleBank* bank;
    s32 perf = GSgfxPerfbarCPUEntry(0x800080);
    u32 steps;

    memset(g_particle_cameras, 0, sizeof(g_particle_cameras));
    g_particle_cameras_count = 0;
    for (i = 0; i < _particleBankStructCount; i++) {
        bank = &((_GSparticleBank*)_particleBankStructList)[i];
        if (bank->active == 1) {
            HSD_CObj* bankCam = bank->camera;
            if (bankCam != NULL && GScameraIsValid((GScamera*)bankCam) == 0 && bank != NULL && bank->active != 0) {
                bank->camera = NULL;
                u8 n = bank->genCount;
                _GSparticleGen* gen = bank->gens;
                while (n--) {
                    _GSparticleGenData* data = gen->data;
                    if (data != NULL && gen->data != NULL) {
                        if (gen->native) {
                            if (data != NULL) {
                                (*(HSD_CObj**)PEBANK_ENGINE_PTR(data)) = NULL;
                            }
                        } else {
                            psGeneratorSetCamera(data->generator, NULL);
                        }
                    }
                    gen++;
                }
            }
            _GSparticleGen* gen = bank->gens;
            for (u32 j = 0; j < bank->genCount; j++, gen++) {
                if (gen->data == NULL) {
                    continue;
                }
                _particleUpdateAttachment(gen);
                GScamera* cam;
                _GSparticleGenData* data = gen->data;
                if (data == NULL) {
                    cam = NULL;
                } else if (gen->native) {
                    if (data != NULL) {
                        cam = (GScamera*)(*(HSD_CObj**)PEBANK_ENGINE_PTR(data));
                    } else {
                        cam = NULL;
                    }
                } else {
                    cam = (GScamera*)psGeneratorGetCamera(data->generator);
                }
                if (GScameraIsValid(cam) != 0) {
                    GScamera** p = g_particle_cameras;
                    u8 found = 0;
                    for (u32 k = 0; k < g_particle_cameras_count; k++, p++) {
                        if (*p == cam) {
                            found = 1;
                            break;
                        }
                    }
                    if (found == 0) {
                        g_particle_cameras[g_particle_cameras_count] = cam;
                        g_particle_cameras_count++;
                    }
                } else {
                    data = gen->data;
                    if (data != NULL) {
                        if (gen->native) {
                            if (data != NULL) {
                                (*(HSD_CObj**)PEBANK_ENGINE_PTR(data)) = NULL;
                            }
                        } else {
                            psGeneratorSetCamera(data->generator, NULL);
                        }
                    }
                }
            }
        }
    }
    steps = (u32)frames;
    sysdolRemain += frames - (f32)steps;
    if (sysdolRemain >= 1.0f) {
        u32 extra = (u32)sysdolRemain;
        steps += extra;
        sysdolRemain -= (f32)extra;
    }
    if (GSgfxVideoGetVsyncRate() == 50) {
        if (++_particlePALFrameCount >= 5) {
            steps++;
            _particlePALFrameCount = 0;
        }
    }
    GScamera* active = GScameraGetActiveCamera();
    if (active != NULL && GScameraIsValid(active) != 0) {
        psSetBillboardCamera((*(HSD_CObj **)&((GSparticleCameraView*)(active))->cobj));
        for (i = 0; i < steps; i++) {
            psInterpretParticles(0);
            psExecGenerator(0);
        }
    }
    u32 rate = GSgfxVideoGetVsyncRate();
    particleEngineUpdate(rate, frames / (f32)rate);
    psDispBeginFrame();
    GSgfxPerfbarCPUEntry(perf);
}
#pragma optimize_for_size reset
}

extern "C++" {
static void _particlePostUpdate(float p0) {
    s32 var_r31;
    u32 var_r30;
    u32 var_r29;
    s32 temp_r28;
    u8 *var_r27;
    u32 var_r3_2;
    u8 *temp_r26;
    u8 temp_r0;
    u8 var_r0;
    u8 *temp_r3;
    u8 *temp_r3_2;
    u32 var_r3;

    temp_r28 = GSgfxPerfbarCPUEntry(0x800080);
    var_r30 = 0U;
    var_r31 = 0;
    while (var_r30 < (u32) _particleBankStructCount) {
        temp_r26 = &_particleBankStructList[var_r31];
        if ((u8) (*(u8 *)&((_GSparticleBank*)(temp_r26))->active) == 1) {
            var_r27 = (*(u8 **)&((_GSparticleBank*)(temp_r26))->gens);
            var_r29 = 0U;
            while (var_r29 < (u8) (*(u8 *)&((_GSparticleBank*)(temp_r26))->genCount)) {
                if ((*(u8 **)&((_GSparticleGen*)(var_r27))->data) != NULL) {
                    if (!_genIsAlive(var_r27)) {
                        GSparticleDestroyGenerator(var_r27, 1U);
                    }
                }
                var_r29 += 1;
                var_r27 += sizeof(_GSparticleGen);
            }
        }
        var_r31 += sizeof(_GSparticleBank);
        var_r30 += 1;
    }
    particleEnginePostUpdate();
    GSgfxPerfbarCPUEntry(temp_r28);
}
}

extern "C++" {
static void _particleRender(GSgfxLayer* p0, GSgfxLayerPass p1) {
    GScamera **var_r30;
    u32 var_r24;
    GScamera *temp_r3;
    u32 var_r29;
    s32 temp_r28;
    u32 temp_r31;
    GScamera *temp_r25;
    s32 temp_r0;
    u8 var_r27;

    temp_r3 = GScameraGetActiveCamera();
    var_r29 = 1;
    temp_r31 = (*(u8 *)&((GSgfxLayer*)(p0))->hw.fogEnable) != 0;
    if (temp_r3 == NULL || GScameraIsValid((GScamera*)(temp_r3)) == 0) {
        return;
    } else {
        temp_r28 = GSgfxPerfbarCPUEntry(0xFF00FF);
        if ((u8) _invalidateVtx != 0) {
            (*(s32 *)&((GSgfxLayer*)(p0))->flags) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->flags) | 0x08000000);
            _invalidateVtx = 0;
        }
        if ((u8) _invalidateTex != 0) {
            (*(s32 *)&((GSgfxLayer*)(p0))->flags) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->flags) | 0x10000000);
            _invalidateTex = 0;
        }
        if (temp_r31 != 0) {
            (*(u8 *)&((GSgfxLayer*)(p0))->hw.fogEnable) = 0U;
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].pe) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].pe) | 0x40);
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].pe) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].pe) | 0x40);
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].groups) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].groups) | 0x40);
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].groups) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].groups) | 0x40);
        }
        temp_r0 = (*(s32 *)&((GSgfxLayer*)(p0))->id);
        switch (temp_r0) {
        case 4:
            var_r29 = 2;
        case 2:
            if ((p1 == 1) && (psDispHasRenderData(var_r29) == 1)) {
                (*(s32 *)&((GSgfxLayer*)(p0))->hw.clipMode) = 0;
                var_r27 = 0;
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].raster) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].raster) | 4);
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].groups) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].groups) | 2);
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].raster) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].raster) | 4);
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].groups) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].groups) | 2);
                _particleRenderCamera(p0, temp_r3, var_r29, NULL);
                for (var_r24 = 0; var_r24 < g_particle_cameras_count; var_r24++) {
                    temp_r25 = g_particle_cameras[var_r24];
                    if (GScameraIsValid((GScamera*)(temp_r25)) != 0) {
                        var_r27 = 1;
                        _particleRenderCamera(p0, temp_r25, var_r29, temp_r25);
                    }
                }
                (*(s8 *)&((GSgfxLayer*)(p0))->hw.texOffsets[0][0]) = 0;
                (*(s8 *)&((GSgfxLayer*)(p0))->hw.texOffsets[0][1]) = 0;
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].texOffsets) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].texOffsets) | 1);
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].groups) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].groups) | 1);
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].texOffsets) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].texOffsets) | 1);
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].groups) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].groups) | 1);
                if (var_r27 != 0) {
                    GScameraLoadActiveCameraMatrix((GSgfxLayerID)((*(s32 *)&((GSgfxLayer*)(p0))->id)));
                }
            }
        case 0:
        case 1:
        case 3:
        case 5:
            particleEngineRender(p0);
            break;
        }
        if (temp_r31 != 0) {
            (*(u8 *)&((GSgfxLayer*)(p0))->hw.fogEnable) = 1U;
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].pe) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].pe) | 0x40);
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].pe) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].pe) | 0x40);
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].pe) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].pe) | 0x200);
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].pe) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].pe) | 0x200);
            if ((u8) (*(u8 *)&((GSgfxLayer*)(p0))->hw.fogRangeEnable) != 0) {
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].pe) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].pe) | 0x100);
                (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].pe) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].pe) | 0x100);
            }
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].groups) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[0].groups) | 0x40);
            (*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].groups) = (s32) ((*(s32 *)&((GSgfxLayer*)(p0))->dirty[1].groups) | 0x40);
        }
        GSgfxPerfbarCPUEntry(temp_r28);
    }
}
}
