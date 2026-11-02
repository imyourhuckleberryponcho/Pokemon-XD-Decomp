#include <dolphin/types.h>
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
enum DPCtlCallback { DPCtlCallback_draft_dummy };
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
struct GSgfxLayer {
    u8 _draft[1];
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
    u8 _draft[1];
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
    u32 unk0;
    u32 serial;
    HSD_Generator* generator;
    u8 unkC[0x154];
    HSD_CObj* camera;
};
struct _GSparticleGen {
    u8 native;
    u8 unk1[0x37];
    _GSparticleGenData* data;
};
struct _GSparticleBank {
    u8 active;
    u8 unk1[2];
    u8 genCount;
    u8 unk4[8];
    _GSparticleGen* gens;
    HSD_CObj* camera;
};
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
s32 particleEngineUpdate(u8, f32);
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
s32 GSgfxRenderWaitForDrawComplete();
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
    psDispSetProjection((u8*)layer + 0xD54);
    psSetBillboardCamera(M2C_FIELD(cam, HSD_CObj **, 8));
    psDispParticles(link, 1, dispCam);
    psDispParticles(link, 2, dispCam);
    layer->InvalidateState();
}
}

extern "C++" {
static inline u32 _genGetMaxLife(u8* gen) {
    u8* bank = M2C_FIELD(gen, u8 **, 0x38);
    if (bank == NULL) {
        return 0;
    }
    if (M2C_FIELD(gen, u8 *, 0) != 0) {
        if (peBankIsInfinite((u32)bank) != 0) {
            return -1U;
        }
        return (u32)(peBankGetLife(M2C_FIELD(gen, u8 **, 0x38)) * (f32)GSgfxVideoGetVsyncRate());
    }
    if (M2C_FIELD(bank, u8 *, 1) == 1) {
        return -1U;
    }
    return psGetGeneratorChildMaxLife(M2C_FIELD(bank, PSGenerator **, 8));
}
}

extern "C++" {
static inline u8 _genIsAlive(u8* gen) {
    u8* bank = M2C_FIELD(gen, u8 **, 0x38);
    if (bank == NULL) {
        return 0;
    }
    if (M2C_FIELD(gen, u8 *, 0) != 0) {
        return _genGetMaxLife(gen) != 0;
    }
    if (M2C_FIELD(bank, u8 *, 1) != 0) {
        return 1;
    }
    if (psGetParticleChildCount(M2C_FIELD(bank, PSGenerator **, 8)) != 0) {
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
    u8* gen = M2C_FIELD(bank, u8 **, 0xC);
    for (s32 i = 0; i < M2C_FIELD(bank, u8 *, 3); i++, gen += 0x3C) {
        if (*kind != M2C_FIELD(gen, u8 *, 0)) {
            return -1;
        }
        if (M2C_FIELD(gen, u32 *, 0x38) == 0) {
            return i;
        }
    }
    return -1;
}
}

extern "C" {
struct ParticleBankStruct {
    u8 used;
    u8 id;
    u8 type;
    u8 max;
    u8 unk4;
    u8 pad5[3];
    void* data;
    u8* models;
    s32 unk10;
};
}

extern "C" {
struct ParticleFileHeader {
    s32 magic;
    u16* cmd;
    int* tex;
    s32 texSize;
    u32* ref;
};
}

extern "C" {
static inline ParticleBankStruct* _particleFindFreeBank() {
    ParticleBankStruct* p = (ParticleBankStruct*)_particleBankStructList;
    u32 i;
    for (i = 0; i < _particleBankStructCount; i++, p++) {
        if (p->used == 0) {
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
    return M2C_FIELD(jobj, _HSD_JObj **, 0xC);
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
        root = M2C_FIELD(root, _HSD_JObj **, 0x10);
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
        u8* data = M2C_FIELD(gen, u8 **, 0x38);
        if (data != NULL && M2C_FIELD(gen, u8 *, 0) == 0) {
            psSetParticleTexScaling(M2C_FIELD(data, PSGenerator **, 8), 1);
        }
        data = M2C_FIELD(gen, u8 **, 0x38);
        if (data != NULL && M2C_FIELD(gen, u8 *, 0) == 0) {
            psSetRandomVelocityScaling(M2C_FIELD(data, PSGenerator **, 8), 1);
        }
        GSparticleAttachGeneratorToGSpart(gen, part, GSmodelGetGSparticleLinkAttachMode(model), 0, 1, 0);
        u32 visible = GSmodelGetVisibility(model);
        data = M2C_FIELD(gen, u8 **, 0x38);
        if (data != NULL) {
            if (M2C_FIELD(gen, u8 *, 0) != 0) {
                if (data != NULL) {
                    if ((u8)visible) {
                        M2C_FIELD(data, u32 *, 0x134) |= 4;
                    } else {
                        M2C_FIELD(data, u32 *, 0x134) &= ~4;
                    }
                }
            } else {
                psSetParticleVisibility(M2C_FIELD(data, PSGenerator **, 8), visible);
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
    _particleBankStructList = (u8*)GSmemAlloc(count * 0x14);
    if (_particleBankStructList == NULL) {
        return;
    }
    for (i = 0; i < _particleBankStructCount; i++) {
        _particleBankStructList[i * 0x14] = 0;
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
    bank->unk10 = 0;
    bank->models = NULL;
    bank->unk4 = 0;
    if (hdr->magic == 0x01F056DA) {
        int i;
        if ((s32)hdr->cmd != 0x30002) {
            return NULL;
        }
        bank->type = 1;
        bank->max = 0x10;
        bank->models = (u8*)GSmemAllocClr(0x3C0);
        if (bank->models == NULL) {
            return NULL;
        }
        for (i = 0; i < 0x10; i++) {
            bank->models[i * 0x3C] = 1;
        }
        bank->data = peBankLoadFile(hdr);
        if (bank->data == NULL) {
            goto fail;
        }
    } else {
        bank->type = 0;
        bank->max = 0x40;
        bank->models = (u8*)GSmemAllocClr(0xF00);
        if (bank->models == NULL) {
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
            hdr->cmd = (u16*)((u8*)hdr->cmd + (u32)hdr);
            hdr->tex = (int*)((u8*)hdr->tex + (u32)hdr);
            hdr->ref = (u32*)((u8*)hdr->ref + (u32)hdr);
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
    bank->used = 1;
    bank->id = id;
    return (u8*)bank;
fail:
    if (bank->models != NULL) {
        GSmemFree(bank->models);
        bank->models = NULL;
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
    temp_r3 = M2C_FIELD(p0, u8 **, 0xC);
    if (temp_r3 != NULL) {
        GSmemFree((void*)(temp_r3));
        M2C_FIELD(p0, u8 **, 0xC) = NULL;
    }
    M2C_FIELD(p0, u8 **, 0xC) = NULL;
    M2C_FIELD(p0, s8 *, 3) = 0;
    if ((u8) M2C_FIELD(p0, u8 *, 2) != 0) {
        peBankFreeFile(M2C_FIELD(p0, s32 *, 8));
    }
    M2C_FIELD(p0, s8 *, 0) = 0;
}
}

extern "C" {
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* p0, s32 p1, s32 p2) {
    GSparticleGenerator* gen;
    s32 idx;

    if (M2C_FIELD(p0, u8 *, 0) == 0) {
        return NULL;
    }
    if (M2C_FIELD(p0, u8 *, 4) != 0) {
        return NULL;
    }
    u8 kind = M2C_FIELD(p0, u8 *, 2);
    if (kind != 0) {
        s32 idx = _particleBankFindFreeGenerator(p0, &kind);
        if (idx < 0) {
            return NULL;
        }
        u8* data = (u8*)peBankCreate(M2C_FIELD(p0, s32 *, 8));
        if (data == NULL) {
            return NULL;
        }
        gen = (GSparticleGenerator*)(M2C_FIELD(p0, u8 **, 0xC) + idx * 0x3C);
        if (M2C_FIELD(gen, u8 *, 0) == 0) {
            return NULL;
        }
        HSD_CObj* cam = M2C_FIELD(p0, HSD_CObj **, 0x10);
        if (data != NULL) {
            M2C_FIELD(data, HSD_CObj **, 0x160) = cam;
        }
        peBankStart(data);
        M2C_FIELD(gen, u8 **, 0x38) = data;
        _invalidateVtx = 1;
    } else {
        idx = _particleBankFindFreeGenerator(p0, &kind);
        if (idx < 0) {
            _particleBankDestroyOldestGenerator((_GSparticleBank*)p0);
            idx = _particleBankFindFreeGenerator(p0, &M2C_FIELD(p0, u8 *, 2));
            if (idx < 0) {
                return NULL;
            }
        }
        u8* data = (u8*)GSmemAlloc(0x30);
        if (data == NULL) {
            return NULL;
        }
        s32 linked = 0;
        if ((u8)p2 == 1) {
            linked = 1;
        }
        M2C_FIELD(data, HSD_Generator **, 8) = psCreateGeneratorID(linked, M2C_FIELD(p0, u8 *, 1), p1);
        HSD_Generator* ps = M2C_FIELD(data, HSD_Generator **, 8);
        if (ps == NULL) {
            GSmemFree(data);
            return NULL;
        }
        M2C_FIELD(ps, s8 *, 0x17) = 1;
        psGeneratorSetCamera(M2C_FIELD(data, HSD_Generator **, 8), M2C_FIELD(p0, HSD_CObj **, 0x10));
        M2C_FIELD(data, s16 *, 2) = p1;
        M2C_FIELD(data, s8 *, 0) = p2;
        M2C_FIELD(data, s32 *, 4) = GSgfxVideoGetVsyncCount();
        if (M2C_FIELD(M2C_FIELD(data, HSD_Generator **, 8), u16 *, 0x10) == 0) {
            M2C_FIELD(data, s8 *, 1) = 1;
        } else {
            M2C_FIELD(data, s8 *, 1) = 0;
        }
        gen = (GSparticleGenerator*)(M2C_FIELD(p0, u8 **, 0xC) + idx * 0x3C);
        if (M2C_FIELD(gen, u8 *, 0) != 0) {
            return NULL;
        }
        M2C_FIELD(gen, u8 **, 0x38) = data;
    }
    _invalidateTex = 1;
    M2C_FIELD(gen, s32 *, 8) = 0;
    M2C_FIELD(gen, s32 *, 0xC) = 0;
    M2C_FIELD(gen, s32 *, 4) = 0;
    M2C_FIELD(gen, s8 *, 1) = 0;
    M2C_FIELD(gen, s8 *, 2) = 0;
    M2C_FIELD(gen, GSparticleBank **, 0x34) = p0;
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

    if (((u8 *) M2C_FIELD(p0, u8 **, 0x38) != NULL) && ((s32) M2C_FIELD(p0, s32 *, 8) == 0) && (p2 != 0)) {
        M2C_FIELD(p0, s32 *, 0xC) = (s32) M2C_FIELD(p1, s32 *, 4);
        M2C_FIELD(p0, s32 *, 4) = (s32) M2C_FIELD(p1, u16 *, 2);
        if (p4 == 1) {
            M2C_FIELD(p0, f32 *, 0x10) = 0.0f;
            M2C_FIELD(p0, f32 *, 0x14) = 0.0f;
            M2C_FIELD(p0, f32 *, 0x18) = 0.0f;
            M2C_FIELD(p0, f32 *, 0x1C) = 0.0f;
            M2C_FIELD(p0, f32 *, 0x20) = 0.0f;
            M2C_FIELD(p0, f32 *, 0x24) = 0.0f;
            M2C_FIELD(p0, f32 *, 0x28) = 1.0f;
            M2C_FIELD(p0, f32 *, 0x2C) = 1.0f;
            M2C_FIELD(p0, f32 *, 0x30) = 1.0f;
        } else if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            temp_r3 = M2C_FIELD(p0, u8 **, 0x38);
            if (temp_r3 != NULL) {
                M2C_FIELD(p0, f32 *, 0x10) = (f32) M2C_FIELD(temp_r3, f32 *, 0x10C);
                M2C_FIELD(p0, f32 *, 0x14) = (f32) M2C_FIELD(temp_r3, f32 *, 0x110);
                M2C_FIELD(p0, f32 *, 0x18) = (f32) M2C_FIELD(temp_r3, f32 *, 0x114);
            } else {
                M2C_FIELD(p0, f32 *, 0x10) = 0.0f;
                M2C_FIELD(p0, f32 *, 0x14) = 0.0f;
                M2C_FIELD(p0, f32 *, 0x18) = 0.0f;
            }
            temp_r3_2 = M2C_FIELD(p0, u8 **, 0x38);
            if (temp_r3_2 != NULL) {
                q.x = M2C_FIELD(temp_r3_2, f32 *, 0x118);
                q.y = M2C_FIELD(temp_r3_2, f32 *, 0x11C);
                q.z = M2C_FIELD(temp_r3_2, f32 *, 0x120);
                q.w = M2C_FIELD(temp_r3_2, f32 *, 0x124);
            } else {
                q.x = 0.0f;
                q.y = 0.0f;
                q.z = 0.0f;
                q.w = 1.0f;
            }
            GSvecMakeFromQuat((GSvec*)(((u8*)(p0) + 0x1C)), &q);
            temp_r3_3 = M2C_FIELD(p0, u8 **, 0x38);
            if (temp_r3_3 != NULL) {
                M2C_FIELD(p0, f32 *, 0x28) = (f32) M2C_FIELD(temp_r3_3, f32 *, 0x128);
                M2C_FIELD(p0, f32 *, 0x2C) = (f32) M2C_FIELD(temp_r3_3, f32 *, 0x12C);
                M2C_FIELD(p0, f32 *, 0x30) = (f32) M2C_FIELD(temp_r3_3, f32 *, 0x130);
            } else {
                M2C_FIELD(p0, f32 *, 0x28) = 1.0f;
                M2C_FIELD(p0, f32 *, 0x2C) = 1.0f;
                M2C_FIELD(p0, f32 *, 0x30) = 1.0f;
            }
        } else {
            temp_r3_4 = M2C_FIELD(p0, u8 **, 0x38);
            M2C_FIELD(p0, f32 *, 0x10) = (f32) M2C_FIELD(temp_r3_4, f32 *, 0xC);
            M2C_FIELD(p0, f32 *, 0x14) = (f32) M2C_FIELD(temp_r3_4, f32 *, 0x10);
            M2C_FIELD(p0, f32 *, 0x18) = (f32) M2C_FIELD(temp_r3_4, f32 *, 0x14);
            temp_r3_5 = M2C_FIELD(p0, u8 **, 0x38);
            M2C_FIELD(p0, f32 *, 0x1C) = (f32) M2C_FIELD(temp_r3_5, f32 *, 0x18);
            M2C_FIELD(p0, f32 *, 0x20) = (f32) M2C_FIELD(temp_r3_5, f32 *, 0x1C);
            M2C_FIELD(p0, f32 *, 0x24) = (f32) M2C_FIELD(temp_r3_5, f32 *, 0x20);
            temp_r3_6 = M2C_FIELD(p0, u8 **, 0x38);
            M2C_FIELD(p0, f32 *, 0x28) = (f32) M2C_FIELD(temp_r3_6, f32 *, 0x24);
            M2C_FIELD(p0, f32 *, 0x2C) = (f32) M2C_FIELD(temp_r3_6, f32 *, 0x28);
            M2C_FIELD(p0, f32 *, 0x30) = (f32) M2C_FIELD(temp_r3_6, f32 *, 0x2C);
        }
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            temp_r4 = M2C_FIELD(p0, u8 **, 0x38);
            if (temp_r4 != NULL) {
                M2C_FIELD(temp_r4, f32 *, 0x10C) = (f32) M2C_FIELD(&zeroVector, f32 *, 0);
                M2C_FIELD(temp_r4, f32 *, 0x110) = (f32) M2C_FIELD(&zeroVector, f32 *, 4);
                M2C_FIELD(temp_r4, f32 *, 0x114) = (f32) M2C_FIELD(&zeroVector, f32 *, 8);
            }
            temp_r4_2 = M2C_FIELD(p0, u8 **, 0x38);
            if (temp_r4_2 != NULL) {
                M2C_FIELD(temp_r4_2, f32 *, 0x118) = (f32) M2C_FIELD(&zeroQuaternion, f32 *, 0);
                M2C_FIELD(temp_r4_2, f32 *, 0x11C) = (f32) M2C_FIELD(&zeroQuaternion, f32 *, 4);
                M2C_FIELD(temp_r4_2, f32 *, 0x120) = (f32) M2C_FIELD(&zeroQuaternion, f32 *, 8);
                M2C_FIELD(temp_r4_2, f32 *, 0x124) = (f32) M2C_FIELD(&zeroQuaternion, f32 *, 0xC);
            }
            temp_r4_3 = M2C_FIELD(p0, u8 **, 0x38);
            if (temp_r4_3 != NULL) {
                M2C_FIELD(temp_r4_3, f32 *, 0x128) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 0);
                M2C_FIELD(temp_r4_3, f32 *, 0x12C) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 4);
                M2C_FIELD(temp_r4_3, f32 *, 0x130) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 8);
            }
        } else {
            temp_r3_7 = M2C_FIELD(p0, u8 **, 0x38);
            M2C_FIELD(temp_r3_7, f32 *, 0xC) = 0.0f;
            M2C_FIELD(temp_r3_7, f32 *, 0x10) = 0.0f;
            M2C_FIELD(temp_r3_7, f32 *, 0x14) = 0.0f;
            temp_r3_8 = M2C_FIELD(p0, u8 **, 0x38);
            M2C_FIELD(temp_r3_8, f32 *, 0x18) = 0.0f;
            M2C_FIELD(temp_r3_8, f32 *, 0x1C) = 0.0f;
            M2C_FIELD(temp_r3_8, f32 *, 0x20) = 0.0f;
            temp_r3_9 = M2C_FIELD(p0, u8 **, 0x38);
            M2C_FIELD(temp_r3_9, f32 *, 0x24) = 1.0f;
            M2C_FIELD(temp_r3_9, f32 *, 0x28) = 1.0f;
            M2C_FIELD(temp_r3_9, f32 *, 0x2C) = 1.0f;
            if (p5 != 0) {
                psLinkChildGensToJObj((PSGenerator*)(M2C_FIELD(M2C_FIELD(p0, u8 **, 0x38), PSGenerator **, 8)), (void*)(M2C_FIELD(p1, u8 **, 8)));
            }
        }
        M2C_FIELD(p0, s32 *, 8) = p2;
        M2C_FIELD(p0, s8 *, 1) = p3;
        M2C_FIELD(p0, s8 *, 2) = 1;
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

    if (((u8 *) M2C_FIELD(p0, u8 **, 0x38) != NULL) && ((s32) M2C_FIELD(p0, s32 *, 8) != 0)) {
        GSmodelSet60fpsAnimFlag((_GSmodel*)(M2C_FIELD(p0, _GSmodel **, 0xC)), 0U);
        M2C_FIELD(p0, _GSmodel **, 0xC) = NULL;
        M2C_FIELD(p0, s32 *, 4) = 0;
        M2C_FIELD(p0, s8 *, 2) = 0;
        M2C_FIELD(p0, s8 *, 1) = 0;
        if ((u8) M2C_FIELD(p0, u8 *, 0) == 0) {
            psUnlinkChildGensFromJObj((PSGenerator*)(M2C_FIELD(M2C_FIELD(p0, u8 **, 0x38), PSGenerator **, 8)));
        }
        M2C_FIELD(p0, s32 *, 8) = 0;
        if (p1 == 0) {
            temp_r4 = M2C_FIELD(p0, u8 **, 0x38);
            if ((temp_r4 != NULL) && ((s32) M2C_FIELD(p0, s32 *, 8) == 0)) {
                if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                    if (temp_r4 != NULL) {
                        M2C_FIELD(temp_r4, f32 *, 0x10C) = (f32) M2C_FIELD(p0, f32 *, 0x10);
                        M2C_FIELD(temp_r4, f32 *, 0x110) = (f32) M2C_FIELD(p0, f32 *, 0x14);
                        M2C_FIELD(temp_r4, f32 *, 0x114) = (f32) M2C_FIELD(p0, f32 *, 0x18);
                    }
                } else {
                    M2C_FIELD(temp_r4, f32 *, 0xC) = (f32) M2C_FIELD(p0, f32 *, 0x10);
                    M2C_FIELD(temp_r4, f32 *, 0x10) = (f32) M2C_FIELD(p0, f32 *, 0x14);
                    M2C_FIELD(temp_r4, f32 *, 0x14) = (f32) M2C_FIELD(p0, f32 *, 0x18);
                    M2C_FIELD(M2C_FIELD(temp_r4, PSGenerator **, 8), f32 *, 0x20) = (f32) M2C_FIELD(p0, f32 *, 0x10);
                    M2C_FIELD(M2C_FIELD(temp_r4, PSGenerator **, 8), f32 *, 0x24) = (f32) M2C_FIELD(p0, f32 *, 0x14);
                    M2C_FIELD(M2C_FIELD(temp_r4, PSGenerator **, 8), f32 *, 0x28) = (f32) M2C_FIELD(p0, f32 *, 0x18);
                }
            }
            temp_r4_2 = M2C_FIELD(p0, u8 **, 0x38);
            if ((temp_r4_2 != NULL) && ((s32) M2C_FIELD(p0, s32 *, 8) == 0)) {
                if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                    EulerToQuat((Vec*)(((u8*)(p0) + 0x1C)), (Quaternion*)(v8));
                    temp_r3 = M2C_FIELD(p0, u8 **, 0x38);
                    if (temp_r3 != NULL) {
                        M2C_FIELD(temp_r3, f32 *, 0x118) = v8[0];
                        M2C_FIELD(temp_r3, f32 *, 0x11C) = v8[1];
                        M2C_FIELD(temp_r3, f32 *, 0x120) = v8[2];
                        M2C_FIELD(temp_r3, f32 *, 0x124) = v8[3];
                    }
                } else {
                    M2C_FIELD(temp_r4_2, f32 *, 0x18) = (f32) M2C_FIELD(p0, f32 *, 0x1C);
                    M2C_FIELD(temp_r4_2, f32 *, 0x1C) = (f32) M2C_FIELD(p0, f32 *, 0x20);
                    M2C_FIELD(temp_r4_2, f32 *, 0x20) = (f32) M2C_FIELD(p0, f32 *, 0x24);
                    M2C_FIELD(M2C_FIELD(temp_r4_2, PSGenerator **, 8), f32 *, 0x90) = (f32) M2C_FIELD(p0, f32 *, 0x1C);
                    M2C_FIELD(M2C_FIELD(temp_r4_2, PSGenerator **, 8), f32 *, 0x94) = (f32) M2C_FIELD(p0, f32 *, 0x20);
                    M2C_FIELD(M2C_FIELD(temp_r4_2, PSGenerator **, 8), f32 *, 0x98) = (f32) M2C_FIELD(p0, f32 *, 0x24);
                }
            }
            if (((u8 *) M2C_FIELD(p0, u8 **, 0x38) != NULL) && ((s32) M2C_FIELD(p0, s32 *, 8) == 0)) {
                temp_f2 = M2C_FIELD(p0, f32 *, 0x28);
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
                    M2C_FIELD(p0, f32 *, 0x28) = var_f1;
                }
                temp_f2_2 = M2C_FIELD(p0, f32 *, 0x2C);
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
                    M2C_FIELD(p0, f32 *, 0x2C) = var_f1_2;
                }
                temp_f2_3 = M2C_FIELD(p0, f32 *, 0x30);
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
                    M2C_FIELD(p0, f32 *, 0x30) = var_f1_3;
                }
                if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                    temp_r3_2 = M2C_FIELD(p0, u8 **, 0x38);
                    if (temp_r3_2 != NULL) {
                        M2C_FIELD(temp_r3_2, f32 *, 0x128) = (f32) M2C_FIELD(p0, f32 *, 0x28);
                        M2C_FIELD(temp_r3_2, f32 *, 0x12C) = (f32) M2C_FIELD(p0, f32 *, 0x2C);
                        M2C_FIELD(temp_r3_2, f32 *, 0x130) = (f32) M2C_FIELD(p0, f32 *, 0x30);
                    }
                } else {
                    temp_r4_3 = M2C_FIELD(p0, u8 **, 0x38);
                    M2C_FIELD(temp_r4_3, f32 *, 0x24) = (f32) M2C_FIELD(p0, f32 *, 0x28);
                    M2C_FIELD(temp_r4_3, f32 *, 0x28) = (f32) M2C_FIELD(p0, f32 *, 0x2C);
                    M2C_FIELD(temp_r4_3, f32 *, 0x2C) = (f32) M2C_FIELD(p0, f32 *, 0x30);
                    M2C_FIELD(M2C_FIELD(temp_r4_3, PSGenerator **, 8), f32 *, 0x9C) = (f32) M2C_FIELD(p0, f32 *, 0x28);
                    M2C_FIELD(M2C_FIELD(temp_r4_3, PSGenerator **, 8), f32 *, 0xA0) = (f32) M2C_FIELD(p0, f32 *, 0x2C);
                    M2C_FIELD(M2C_FIELD(temp_r4_3, PSGenerator **, 8), f32 *, 0xA4) = (f32) M2C_FIELD(p0, f32 *, 0x30);
                }
            }
        }
    }
}
}

extern "C" {
void GSparticleSetGeneratorPosition(GSparticleGenerator* p0, Vec* p1) {
    u8 *temp_r5;

    temp_r5 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r5 != NULL) {
        if ((s32) M2C_FIELD(p0, s32 *, 8) == 0) {
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                if (temp_r5 != NULL) {
                    M2C_FIELD(temp_r5, f32 *, 0x10C) = (f32) M2C_FIELD(p1, f32 *, 0);
                    M2C_FIELD(temp_r5, f32 *, 0x110) = (f32) M2C_FIELD(p1, f32 *, 4);
                    M2C_FIELD(temp_r5, f32 *, 0x114) = (f32) M2C_FIELD(p1, f32 *, 8);
                }
            } else {
                M2C_FIELD(temp_r5, f32 *, 0xC) = (f32) M2C_FIELD(p1, f32 *, 0);
                M2C_FIELD(temp_r5, f32 *, 0x10) = (f32) M2C_FIELD(p1, f32 *, 4);
                M2C_FIELD(temp_r5, f32 *, 0x14) = (f32) M2C_FIELD(p1, f32 *, 8);
                M2C_FIELD(M2C_FIELD(temp_r5, u8 **, 8), f32 *, 0x20) = (f32) M2C_FIELD(p1, f32 *, 0);
                M2C_FIELD(M2C_FIELD(temp_r5, u8 **, 8), f32 *, 0x24) = (f32) M2C_FIELD(p1, f32 *, 4);
                M2C_FIELD(M2C_FIELD(temp_r5, u8 **, 8), f32 *, 0x28) = (f32) M2C_FIELD(p1, f32 *, 8);
            }
        } else {
            M2C_FIELD(p0, f32 *, 0x10) = (f32) M2C_FIELD(p1, f32 *, 0);
            M2C_FIELD(p0, f32 *, 0x14) = (f32) M2C_FIELD(p1, f32 *, 4);
            M2C_FIELD(p0, f32 *, 0x18) = (f32) M2C_FIELD(p1, f32 *, 8);
        }
    }
}
}

extern "C" {
void GSparticleSetGeneratorRotation(void *p0, f32 *p1) {
    f32 v8[4];
    u8 *temp_r3;
    u8 *temp_r5;

    temp_r5 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r5 != NULL) {
        if ((s32) M2C_FIELD(p0, s32 *, 8) == 0) {
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                EulerToQuat((Vec*)((Vec *) p1), (Quaternion*)(v8));
                temp_r3 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r3 != NULL) {
                    M2C_FIELD(temp_r3, f32 *, 0x118) = v8[0];
                    M2C_FIELD(temp_r3, f32 *, 0x11C) = v8[1];
                    M2C_FIELD(temp_r3, f32 *, 0x120) = v8[2];
                    M2C_FIELD(temp_r3, f32 *, 0x124) = v8[3];
                }
            } else {
                M2C_FIELD(temp_r5, f32 *, 0x18) = (f32) M2C_FIELD(p1, f32 *, 0);
                M2C_FIELD(temp_r5, f32 *, 0x1C) = (f32) M2C_FIELD(p1, f32 *, 4);
                M2C_FIELD(temp_r5, f32 *, 0x20) = (f32) M2C_FIELD(p1, f32 *, 8);
                M2C_FIELD(M2C_FIELD(temp_r5, u8 **, 8), f32 *, 0x90) = (f32) M2C_FIELD(p1, f32 *, 0);
                M2C_FIELD(M2C_FIELD(temp_r5, u8 **, 8), f32 *, 0x94) = (f32) M2C_FIELD(p1, f32 *, 4);
                M2C_FIELD(M2C_FIELD(temp_r5, u8 **, 8), f32 *, 0x98) = (f32) M2C_FIELD(p1, f32 *, 8);
            }
        } else {
            M2C_FIELD(p0, f32 *, 0x1C) = (f32) M2C_FIELD(p1, f32 *, 0);
            M2C_FIELD(p0, f32 *, 0x20) = (f32) M2C_FIELD(p1, f32 *, 4);
            M2C_FIELD(p0, f32 *, 0x24) = (f32) M2C_FIELD(p1, f32 *, 8);
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

    if ((u8 *) M2C_FIELD(p0, u8 **, 0x38) != NULL) {
        if ((s32) M2C_FIELD(p0, s32 *, 8) == 0) {
            temp_f2 = M2C_FIELD(p1, f32 *, 0);
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
                M2C_FIELD(p1, f32 *, 0) = var_f1;
            }
            temp_f2_2 = M2C_FIELD(p1, f32 *, 4);
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
                M2C_FIELD(p1, f32 *, 4) = var_f1_2;
            }
            temp_f2_3 = M2C_FIELD(p1, f32 *, 8);
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
                M2C_FIELD(p1, f32 *, 8) = var_f1_3;
            }
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                temp_r7 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r7 != NULL) {
                    M2C_FIELD(temp_r7, f32 *, 0x128) = (f32) M2C_FIELD(p1, f32 *, 0);
                    M2C_FIELD(temp_r7, f32 *, 0x12C) = (f32) M2C_FIELD(p1, f32 *, 4);
                    M2C_FIELD(temp_r7, f32 *, 0x130) = (f32) M2C_FIELD(p1, f32 *, 8);
                }
            } else {
                temp_r8 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r8, f32 *, 0x24) = (f32) M2C_FIELD(p1, f32 *, 0);
                M2C_FIELD(temp_r8, f32 *, 0x28) = (f32) M2C_FIELD(p1, f32 *, 4);
                M2C_FIELD(temp_r8, f32 *, 0x2C) = (f32) M2C_FIELD(p1, f32 *, 8);
                M2C_FIELD(M2C_FIELD(temp_r8, PSGenerator **, 8), f32 *, 0x9C) = (f32) M2C_FIELD(p1, f32 *, 0);
                M2C_FIELD(M2C_FIELD(temp_r8, PSGenerator **, 8), f32 *, 0xA0) = (f32) M2C_FIELD(p1, f32 *, 4);
                M2C_FIELD(M2C_FIELD(temp_r8, PSGenerator **, 8), f32 *, 0xA4) = (f32) M2C_FIELD(p1, f32 *, 8);
            }
        } else {
            M2C_FIELD(p0, f32 *, 0x28) = (f32) M2C_FIELD(p1, f32 *, 0);
            M2C_FIELD(p0, f32 *, 0x2C) = (f32) M2C_FIELD(p1, f32 *, 4);
            M2C_FIELD(p0, f32 *, 0x30) = (f32) M2C_FIELD(p1, f32 *, 8);
        }
        if (((u8) M2C_FIELD(p0, u8 *, 0) == 0) && (p2 == 1)) {
            psSetGeneratorAngleRadiusScale((PSGenerator*)(M2C_FIELD(M2C_FIELD(p0, u8 **, 0x38), PSGenerator **, 8)), (f32*)((f32 *) p1), (u16)p3);
        }
    }
}
}

extern "C" {
u32 GSparticleGetGeneratorLife(GSparticleGenerator* p0) {
    u8 *temp_r3;

    temp_r3 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r3 == NULL) {
        return 0U;
    }
    if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
        if (peBankIsInfinite((u32)(temp_r3)) != 0) {
            return -1U;
        }
        return (u32) (peBankGetLife(M2C_FIELD(p0, u8 **, 0x38)) * ((f32) GSgfxVideoGetVsyncRate()));
    }
    if ((u8) M2C_FIELD(temp_r3, u8 *, 1) == 1) {
        return -1U;
    }
    return psGetGeneratorChildMaxLife((PSGenerator*)(M2C_FIELD(temp_r3, PSGenerator **, 8)));
}
}

extern "C" {
s32 GSparticleIsGeneratorAlive(void *p0) {
    u32 var_r3;
    u32 var_r3_2;
    u8 temp_r0;
    u8 *temp_r3;
    u8 *temp_r3_2;

    temp_r3 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r3 == NULL) {
        return 0;
    }
    temp_r0 = M2C_FIELD(p0, u8 *, 0);
    if (temp_r0 != 0) {
        if (temp_r3 == NULL) {
            var_r3_2 = 0;
        } else if (temp_r0 != 0) {
            if (peBankIsInfinite((u32)(temp_r3)) != 0) {
                var_r3_2 = -1U;
            } else {
                var_r3_2 = (u32) (peBankGetLife(M2C_FIELD(p0, u8 **, 0x38)) * ((f32) GSgfxVideoGetVsyncRate()));
            }
        } else if ((u8) M2C_FIELD(temp_r3, u8 *, 1) == 1) {
            var_r3_2 = -1U;
        } else {
            var_r3_2 = psGetGeneratorChildMaxLife((PSGenerator*)(M2C_FIELD(temp_r3, PSGenerator **, 8)));
        }
        return var_r3_2 != 0;
    }
    if ((u8) M2C_FIELD(temp_r3, u8 *, 1) != 0) {
        return 1;
    }
    if (psGetParticleChildCount((PSGenerator*)(M2C_FIELD(temp_r3, PSGenerator **, 8))) != 0) {
        return 1;
    }
    temp_r3_2 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r3_2 == NULL) {
        var_r3 = 0;
    } else if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
        if (peBankIsInfinite((u32)(temp_r3_2)) != 0) {
            var_r3 = -1U;
        } else {
            var_r3 = (u32) (peBankGetLife(M2C_FIELD(p0, u8 **, 0x38)) * ((f32) GSgfxVideoGetVsyncRate()));
        }
    } else if ((u8) M2C_FIELD(temp_r3_2, u8 *, 1) == 1) {
        var_r3 = -1U;
    } else {
        var_r3 = psGetGeneratorChildMaxLife((PSGenerator*)(M2C_FIELD(temp_r3_2, PSGenerator **, 8)));
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

    temp_r5 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r5 != NULL) {
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetVelocityRotationInLocal((PSGenerator*)(M2C_FIELD(temp_r5, PSGenerator **, 8)), (u16)p1);
        }
    }
}
}

extern "C" {
void GSparticleSetOffsetRotationInLocal(void *p0, u8 p1, u8 p2) {
    u8 *temp_r6;

    temp_r6 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r6 != NULL) {
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            if (temp_r6 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetOffsetRotationInLocal((PSGenerator*)(M2C_FIELD(temp_r6, PSGenerator **, 8)), (u16)p1, (u16)p2);
        }
    }
}
}

extern "C" {
void GSparticleSetParticleTextureScaling(void *p0, u8 p1) {
    u8 *temp_r5;

    temp_r5 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r5 != NULL) {
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetParticleTexScaling((PSGenerator*)(M2C_FIELD(temp_r5, PSGenerator **, 8)), (u16)p1);
        }
    }
}
}

extern "C" {
void GSparticleSetTornadoScaling(void *p0, u8 p1, u8 p2) {
    u8 *temp_r6;

    temp_r6 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r6 != NULL) {
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            if (temp_r6 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetTornadoScaling((PSGenerator*)(M2C_FIELD(temp_r6, PSGenerator **, 8)), (u16)p1, (u16)p2);
        }
    }
}
}

extern "C" {
void GSparticleSetNodeScaling(void *p0, u8 p1) {
    u8 *temp_r5;

    temp_r5 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r5 != NULL) {
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetNodeScaling((PSGenerator*)(M2C_FIELD(temp_r5, PSGenerator **, 8)), (u16)p1);
        }
    }
}
}

extern "C" {
void GSparticleSetRandomVelocityScaling(void *p0, u8 p1) {
    u8 *temp_r5;

    temp_r5 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r5 != NULL) {
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                } else {
                }
            }
        } else {
            psSetRandomVelocityScaling((PSGenerator*)(M2C_FIELD(temp_r5, PSGenerator **, 8)), (u16)p1);
        }
    }
}
}

extern "C" {
void GSparticleSetGeneratorVisibility(void *p0, u8 p1) {
    u8 *temp_r5;

    temp_r5 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r5 != NULL) {
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            if (temp_r5 != NULL) {
                if (p1 != 0) {
                    M2C_FIELD(temp_r5, s32 *, 0x134) = (s32) (M2C_FIELD(temp_r5, s32 *, 0x134) | 4);
                    return;
                }
                M2C_FIELD(temp_r5, s32 *, 0x134) = (s32) (M2C_FIELD(temp_r5, s32 *, 0x134) & 0xFFFFFFFB);
            }
        } else {
            psSetParticleVisibility((PSGenerator*)(M2C_FIELD(temp_r5, PSGenerator **, 8)), (u16)p1);
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
    var_r30 = M2C_FIELD(p0, u8 **, 0xC);
    while (var_r29 < (u8) M2C_FIELD(p0, u8 *, 3)) {
        temp_r3 = M2C_FIELD(var_r30, u8 **, 0x38);
        if (temp_r3 != NULL) {
            if ((u8) M2C_FIELD(var_r30, u8 *, 0) != 0) {
                if (temp_r3 != NULL) {
                    if (p1 != 0) {
                        M2C_FIELD(temp_r3, s32 *, 0x134) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x134) | 4);
                    } else {
                        M2C_FIELD(temp_r3, s32 *, 0x134) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x134) & 0xFFFFFFFB);
                    }
                }
            } else {
                psSetParticleVisibility((PSGenerator*)(M2C_FIELD(temp_r3, PSGenerator **, 8)), p1);
            }
        }
        var_r29 += 1;
        var_r30 += 0x3C;
    }
}
}

extern "C" {
void GSparticleStopGenerator(void *p0) {
    if (((u32) M2C_FIELD(p0, u32 *, 0x38) != 0) && ((u8) M2C_FIELD(p0, u8 *, 0) != 0)) {
        if (peBankIsInfinite(M2C_FIELD(p0, u32 *, 0x38)) != 0) {
            peBankStopLoop(M2C_FIELD(p0, u32 *, 0x38));
            return;
        }
        peBankStop(M2C_FIELD(p0, u32 *, 0x38));
    }
}
}

extern "C" {
void GSparticleDestroyGenerator(void *p0, bool p1) {
    HSD_Generator *temp_r4;
    u8 *temp_r3;

    if ((u8 *) M2C_FIELD(p0, u8 **, 0x38) != NULL) {
        if ((s32) M2C_FIELD(p0, s32 *, 8) != 0) {
            GSparticleDetachGeneratorFromGSpart(p0, 0U);
        }
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            peBankFree(M2C_FIELD(p0, u8 **, 0x38));
            M2C_FIELD(p0, u8 **, 0x38) = NULL;
            return;
        }
        if (p1 == 1) {
            temp_r4 = M2C_FIELD(M2C_FIELD(p0, u8 **, 0x38), HSD_Generator **, 8);
            psKillFamily((s32) M2C_FIELD(temp_r4, u16 *, 0x18), (s32) M2C_FIELD(temp_r4, u8 *, 0x15));
        }
        psKillGenerator((HSD_Generator*)(M2C_FIELD(M2C_FIELD(p0, u8 **, 0x38), HSD_Generator **, 8)));
        temp_r3 = M2C_FIELD(p0, u8 **, 0x38);
        if (temp_r3 != NULL) {
            GSmemFree((void*)(temp_r3));
            M2C_FIELD(p0, u8 **, 0x38) = NULL;
        }
    }
}
}

extern "C" {
void GSparticleDestroyAllGenerators(GSparticleBank* p0, bool p1) {
    u8 *var_r31;
    u32 var_r30;

    var_r30 = 0U;
    var_r31 = M2C_FIELD(p0, u8 **, 0xC);
    while (var_r30 < (u8) M2C_FIELD(p0, u8 *, 3)) {
        if ((u32) M2C_FIELD(var_r31, u32 *, 0x38) != 0U) {
            GSparticleDestroyGenerator(var_r31, p1);
        }
        var_r30 += 1;
        var_r31 += 0x3C;
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
                    data->camera = camera;
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

    temp_r5 = M2C_FIELD(p0, u8 **, 0x38);
    if (temp_r5 != NULL) {
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            if (temp_r5 != NULL) {
                M2C_FIELD(temp_r5, s32 *, 0x160) = p1;
            }
        } else {
            psGeneratorSetCamera((HSD_Generator*)(M2C_FIELD(temp_r5, HSD_Generator **, 8)), (HSD_CObj*)((HSD_CObj *) p1));
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

    if (((s32) M2C_FIELD(p0, s32 *, 8) != 0) && ((u8) M2C_FIELD(p0, u8 *, 2) != 0)) {
        temp_r3 = GSmodelGetPart((_GSmodel*)(M2C_FIELD(p0, _GSmodel **, 0xC)), M2C_FIELD(p0, s32 *, 4));
        GSpartGetTransform((GSpart*)(temp_r3), (GSvec*)(v8C), (GSvec*)(v80), (GSvec*)(v74));
        GSpartFree((GSpart*)(temp_r3));
        EulerToQuat((Vec*)(v80), (Quaternion*)(unksp64));
        GSvecTransformQuat((GSvec*)(unksp58), (const GSquat*)(unksp64), (const GSvec*)(((u8*)((s32)p0) + 0x10)));
        PSVECAdd((const register Vec*)(v8C), (const register Vec*)(unksp58), (register Vec*)(v8C));
        PSVECAdd((const register Vec*)(v80), (const register Vec*)(((u8*)((s32)p0) + 0x1C)), (register Vec*)(v80));
        v74[0] *= M2C_FIELD(p0, f32 *, 0x28);
        v74[1] *= M2C_FIELD(p0, f32 *, 0x2C);
        v74[2] *= M2C_FIELD(p0, f32 *, 0x30);
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            temp_r3_2 = M2C_FIELD(p0, u8 **, 0x38);
            if (temp_r3_2 != NULL) {
                M2C_FIELD(temp_r3_2, f32 *, 0x10C) = (f32) M2C_FIELD(p0, f32 *, 0x10);
                M2C_FIELD(temp_r3_2, f32 *, 0x110) = (f32) M2C_FIELD(p0, f32 *, 0x14);
                M2C_FIELD(temp_r3_2, f32 *, 0x114) = (f32) M2C_FIELD(p0, f32 *, 0x18);
            }
        } else {
            temp_r4 = M2C_FIELD(p0, u8 **, 0x38);
            M2C_FIELD(temp_r4, f32 *, 0xC) = (f32) M2C_FIELD(p0, f32 *, 0x10);
            M2C_FIELD(temp_r4, f32 *, 0x10) = (f32) M2C_FIELD(p0, f32 *, 0x14);
            M2C_FIELD(temp_r4, f32 *, 0x14) = (f32) M2C_FIELD(p0, f32 *, 0x18);
            M2C_FIELD(M2C_FIELD(temp_r4, u8 **, 8), f32 *, 0x20) = (f32) M2C_FIELD(p0, f32 *, 0x10);
            M2C_FIELD(M2C_FIELD(temp_r4, u8 **, 8), f32 *, 0x24) = (f32) M2C_FIELD(p0, f32 *, 0x14);
            M2C_FIELD(M2C_FIELD(temp_r4, u8 **, 8), f32 *, 0x28) = (f32) M2C_FIELD(p0, f32 *, 0x18);
        }
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            EulerToQuat((Vec*)(((u8*)(p0) + 0x1C)), (Quaternion*)(v48));
            temp_r3_3 = M2C_FIELD(p0, u8 **, 0x38);
            if (temp_r3_3 != NULL) {
                M2C_FIELD(temp_r3_3, f32 *, 0x118) = v48[0];
                M2C_FIELD(temp_r3_3, f32 *, 0x11C) = v48[1];
                M2C_FIELD(temp_r3_3, f32 *, 0x120) = v48[2];
                M2C_FIELD(temp_r3_3, f32 *, 0x124) = v48[3];
            }
        } else {
            temp_r4_2 = M2C_FIELD(p0, u8 **, 0x38);
            M2C_FIELD(temp_r4_2, f32 *, 0x18) = (f32) M2C_FIELD(p0, f32 *, 0x1C);
            M2C_FIELD(temp_r4_2, f32 *, 0x1C) = (f32) M2C_FIELD(p0, f32 *, 0x20);
            M2C_FIELD(temp_r4_2, f32 *, 0x20) = (f32) M2C_FIELD(p0, f32 *, 0x24);
            M2C_FIELD(M2C_FIELD(temp_r4_2, u8 **, 8), f32 *, 0x90) = (f32) M2C_FIELD(p0, f32 *, 0x1C);
            M2C_FIELD(M2C_FIELD(temp_r4_2, u8 **, 8), f32 *, 0x94) = (f32) M2C_FIELD(p0, f32 *, 0x20);
            M2C_FIELD(M2C_FIELD(temp_r4_2, u8 **, 8), f32 *, 0x98) = (f32) M2C_FIELD(p0, f32 *, 0x24);
        }
        temp_f2 = M2C_FIELD(p0, f32 *, 0x28);
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
            M2C_FIELD(p0, f32 *, 0x28) = var_f1;
        }
        temp_f2_2 = M2C_FIELD(p0, f32 *, 0x2C);
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
            M2C_FIELD(p0, f32 *, 0x2C) = var_f1_2;
        }
        temp_f2_3 = M2C_FIELD(p0, f32 *, 0x30);
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
            M2C_FIELD(p0, f32 *, 0x30) = var_f1_3;
        }
        if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
            temp_r3_4 = M2C_FIELD(p0, u8 **, 0x38);
            if (temp_r3_4 != NULL) {
                M2C_FIELD(temp_r3_4, f32 *, 0x128) = (f32) M2C_FIELD(p0, f32 *, 0x28);
                M2C_FIELD(temp_r3_4, f32 *, 0x12C) = (f32) M2C_FIELD(p0, f32 *, 0x2C);
                M2C_FIELD(temp_r3_4, f32 *, 0x130) = (f32) M2C_FIELD(p0, f32 *, 0x30);
            }
        } else {
            temp_r4_3 = M2C_FIELD(p0, u8 **, 0x38);
            M2C_FIELD(temp_r4_3, f32 *, 0x24) = (f32) M2C_FIELD(p0, f32 *, 0x28);
            M2C_FIELD(temp_r4_3, f32 *, 0x28) = (f32) M2C_FIELD(p0, f32 *, 0x2C);
            M2C_FIELD(temp_r4_3, f32 *, 0x2C) = (f32) M2C_FIELD(p0, f32 *, 0x30);
            M2C_FIELD(M2C_FIELD(temp_r4_3, u8 **, 8), f32 *, 0x9C) = (f32) M2C_FIELD(p0, f32 *, 0x28);
            M2C_FIELD(M2C_FIELD(temp_r4_3, u8 **, 8), f32 *, 0xA0) = (f32) M2C_FIELD(p0, f32 *, 0x2C);
            M2C_FIELD(M2C_FIELD(temp_r4_3, u8 **, 8), f32 *, 0xA4) = (f32) M2C_FIELD(p0, f32 *, 0x30);
        }
        switch (M2C_FIELD(p0, s32 *, 8)) {
        case 1:
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                u8* g = M2C_FIELD(p0, u8 **, 0x38);
                if (g != NULL) {
                    M2C_FIELD(g, f32 *, 0x10C) = v8C[0];
                    M2C_FIELD(g, f32 *, 0x110) = v8C[1];
                    M2C_FIELD(g, f32 *, 0x114) = v8C[2];
                }
            } else {
                temp_r4_4 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_4, f32 *, 0xC) = v8C[0];
                M2C_FIELD(temp_r4_4, f32 *, 0x10) = v8C[1];
                M2C_FIELD(temp_r4_4, f32 *, 0x14) = v8C[2];
                M2C_FIELD(M2C_FIELD(temp_r4_4, u8 **, 8), f32 *, 0x20) = v8C[0];
                M2C_FIELD(M2C_FIELD(temp_r4_4, u8 **, 8), f32 *, 0x24) = v8C[1];
                M2C_FIELD(M2C_FIELD(temp_r4_4, u8 **, 8), f32 *, 0x28) = v8C[2];
            }
            break;
        case 2:
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                EulerToQuat((Vec*)(v80), (Quaternion*)(v38));
                temp_r3_6 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r3_6 != NULL) {
                    M2C_FIELD(temp_r3_6, f32 *, 0x118) = v38[0];
                    M2C_FIELD(temp_r3_6, f32 *, 0x11C) = v38[1];
                    M2C_FIELD(temp_r3_6, f32 *, 0x120) = v38[2];
                    M2C_FIELD(temp_r3_6, f32 *, 0x124) = v38[3];
                }
            } else {
                temp_r4_5 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_5, f32 *, 0x18) = v80[0];
                M2C_FIELD(temp_r4_5, f32 *, 0x1C) = v80[1];
                M2C_FIELD(temp_r4_5, f32 *, 0x20) = v80[2];
                M2C_FIELD(M2C_FIELD(temp_r4_5, u8 **, 8), f32 *, 0x90) = v80[0];
                M2C_FIELD(M2C_FIELD(temp_r4_5, u8 **, 8), f32 *, 0x94) = v80[1];
                M2C_FIELD(M2C_FIELD(temp_r4_5, u8 **, 8), f32 *, 0x98) = v80[2];
            }
            break;
        case 3:
            _particleClampScale(&v74[0]);
            _particleClampScale(&v74[1]);
            _particleClampScale(&v74[2]);
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                u8* g = M2C_FIELD(p0, u8 **, 0x38);
                if (g != NULL) {
                    M2C_FIELD(g, f32 *, 0x128) = v74[0];
                    M2C_FIELD(g, f32 *, 0x12C) = v74[1];
                    M2C_FIELD(g, f32 *, 0x130) = v74[2];
                }
            } else {
                temp_r4_6 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_6, f32 *, 0x24) = v74[0];
                M2C_FIELD(temp_r4_6, f32 *, 0x28) = v74[1];
                M2C_FIELD(temp_r4_6, f32 *, 0x2C) = v74[2];
                M2C_FIELD(M2C_FIELD(temp_r4_6, u8 **, 8), f32 *, 0x9C) = v74[0];
                M2C_FIELD(M2C_FIELD(temp_r4_6, u8 **, 8), f32 *, 0xA0) = v74[1];
                M2C_FIELD(M2C_FIELD(temp_r4_6, u8 **, 8), f32 *, 0xA4) = v74[2];
            }
            break;
        case 4:
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                temp_r3_8 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r3_8 != NULL) {
                    M2C_FIELD(temp_r3_8, f32 *, 0x10C) = v8C[0];
                    M2C_FIELD(temp_r3_8, f32 *, 0x110) = v8C[1];
                    M2C_FIELD(temp_r3_8, f32 *, 0x114) = v8C[2];
                }
            } else {
                temp_r4_7 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_7, f32 *, 0xC) = v8C[0];
                M2C_FIELD(temp_r4_7, f32 *, 0x10) = v8C[1];
                M2C_FIELD(temp_r4_7, f32 *, 0x14) = v8C[2];
                M2C_FIELD(M2C_FIELD(temp_r4_7, u8 **, 8), f32 *, 0x20) = v8C[0];
                M2C_FIELD(M2C_FIELD(temp_r4_7, u8 **, 8), f32 *, 0x24) = v8C[1];
                M2C_FIELD(M2C_FIELD(temp_r4_7, u8 **, 8), f32 *, 0x28) = v8C[2];
            }
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                EulerToQuat((Vec*)(v80), (Quaternion*)(q28));
                u8* g = M2C_FIELD(p0, u8 **, 0x38);
                if (g != NULL) {
                    M2C_FIELD(g, f32 *, 0x118) = q28[0];
                    M2C_FIELD(g, f32 *, 0x11C) = q28[1];
                    M2C_FIELD(g, f32 *, 0x120) = q28[2];
                    M2C_FIELD(g, f32 *, 0x124) = q28[3];
                }
            } else {
                temp_r4_8 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_8, f32 *, 0x18) = v80[0];
                M2C_FIELD(temp_r4_8, f32 *, 0x1C) = v80[1];
                M2C_FIELD(temp_r4_8, f32 *, 0x20) = v80[2];
                M2C_FIELD(M2C_FIELD(temp_r4_8, u8 **, 8), f32 *, 0x90) = v80[0];
                M2C_FIELD(M2C_FIELD(temp_r4_8, u8 **, 8), f32 *, 0x94) = v80[1];
                M2C_FIELD(M2C_FIELD(temp_r4_8, u8 **, 8), f32 *, 0x98) = v80[2];
            }
            break;
        case 5:
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                EulerToQuat((Vec*)(v80), (Quaternion*)(q18));
                u8* g = M2C_FIELD(p0, u8 **, 0x38);
                if (g != NULL) {
                    M2C_FIELD(g, f32 *, 0x118) = q18[0];
                    M2C_FIELD(g, f32 *, 0x11C) = q18[1];
                    M2C_FIELD(g, f32 *, 0x120) = q18[2];
                    M2C_FIELD(g, f32 *, 0x124) = q18[3];
                }
            } else {
                temp_r4_9 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_9, f32 *, 0x18) = v80[0];
                M2C_FIELD(temp_r4_9, f32 *, 0x1C) = v80[1];
                M2C_FIELD(temp_r4_9, f32 *, 0x20) = v80[2];
                M2C_FIELD(M2C_FIELD(temp_r4_9, u8 **, 8), f32 *, 0x90) = v80[0];
                M2C_FIELD(M2C_FIELD(temp_r4_9, u8 **, 8), f32 *, 0x94) = v80[1];
                M2C_FIELD(M2C_FIELD(temp_r4_9, u8 **, 8), f32 *, 0x98) = v80[2];
            }
            _particleClampScale(&v74[0]);
            _particleClampScale(&v74[1]);
            _particleClampScale(&v74[2]);
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                temp_r3_11 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r3_11 != NULL) {
                    M2C_FIELD(temp_r3_11, f32 *, 0x128) = v74[0];
                    M2C_FIELD(temp_r3_11, f32 *, 0x12C) = v74[1];
                    M2C_FIELD(temp_r3_11, f32 *, 0x130) = v74[2];
                }
            } else {
                temp_r4_10 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_10, f32 *, 0x24) = v74[0];
                M2C_FIELD(temp_r4_10, f32 *, 0x28) = v74[1];
                M2C_FIELD(temp_r4_10, f32 *, 0x2C) = v74[2];
                M2C_FIELD(M2C_FIELD(temp_r4_10, u8 **, 8), f32 *, 0x9C) = v74[0];
                M2C_FIELD(M2C_FIELD(temp_r4_10, u8 **, 8), f32 *, 0xA0) = v74[1];
                M2C_FIELD(M2C_FIELD(temp_r4_10, u8 **, 8), f32 *, 0xA4) = v74[2];
            }
            break;
        case 6:
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                temp_r3_12 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r3_12 != NULL) {
                    M2C_FIELD(temp_r3_12, f32 *, 0x10C) = v8C[0];
                    M2C_FIELD(temp_r3_12, f32 *, 0x110) = v8C[1];
                    M2C_FIELD(temp_r3_12, f32 *, 0x114) = v8C[2];
                }
            } else {
                temp_r4_11 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_11, f32 *, 0xC) = v8C[0];
                M2C_FIELD(temp_r4_11, f32 *, 0x10) = v8C[1];
                M2C_FIELD(temp_r4_11, f32 *, 0x14) = v8C[2];
                M2C_FIELD(M2C_FIELD(temp_r4_11, u8 **, 8), f32 *, 0x20) = v8C[0];
                M2C_FIELD(M2C_FIELD(temp_r4_11, u8 **, 8), f32 *, 0x24) = v8C[1];
                M2C_FIELD(M2C_FIELD(temp_r4_11, u8 **, 8), f32 *, 0x28) = v8C[2];
            }
            _particleClampScale(&v74[0]);
            _particleClampScale(&v74[1]);
            _particleClampScale(&v74[2]);
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                temp_r3_13 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r3_13 != NULL) {
                    M2C_FIELD(temp_r3_13, f32 *, 0x128) = v74[0];
                    M2C_FIELD(temp_r3_13, f32 *, 0x12C) = v74[1];
                    M2C_FIELD(temp_r3_13, f32 *, 0x130) = v74[2];
                }
            } else {
                temp_r4_12 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_12, f32 *, 0x24) = v74[0];
                M2C_FIELD(temp_r4_12, f32 *, 0x28) = v74[1];
                M2C_FIELD(temp_r4_12, f32 *, 0x2C) = v74[2];
                M2C_FIELD(M2C_FIELD(temp_r4_12, u8 **, 8), f32 *, 0x9C) = v74[0];
                M2C_FIELD(M2C_FIELD(temp_r4_12, u8 **, 8), f32 *, 0xA0) = v74[1];
                M2C_FIELD(M2C_FIELD(temp_r4_12, u8 **, 8), f32 *, 0xA4) = v74[2];
            }
            break;
        case 7:
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                temp_r3_14 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r3_14 != NULL) {
                    M2C_FIELD(temp_r3_14, f32 *, 0x10C) = v8C[0];
                    M2C_FIELD(temp_r3_14, f32 *, 0x110) = v8C[1];
                    M2C_FIELD(temp_r3_14, f32 *, 0x114) = v8C[2];
                }
            } else {
                temp_r4_13 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_13, f32 *, 0xC) = v8C[0];
                M2C_FIELD(temp_r4_13, f32 *, 0x10) = v8C[1];
                M2C_FIELD(temp_r4_13, f32 *, 0x14) = v8C[2];
                M2C_FIELD(M2C_FIELD(temp_r4_13, u8 **, 8), f32 *, 0x20) = v8C[0];
                M2C_FIELD(M2C_FIELD(temp_r4_13, u8 **, 8), f32 *, 0x24) = v8C[1];
                M2C_FIELD(M2C_FIELD(temp_r4_13, u8 **, 8), f32 *, 0x28) = v8C[2];
            }
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                EulerToQuat((Vec*)(v80), (Quaternion*)(v8));
                temp_r3_15 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r3_15 != NULL) {
                    M2C_FIELD(temp_r3_15, f32 *, 0x118) = v8[0];
                    M2C_FIELD(temp_r3_15, f32 *, 0x11C) = v8[1];
                    M2C_FIELD(temp_r3_15, f32 *, 0x120) = v8[2];
                    M2C_FIELD(temp_r3_15, f32 *, 0x124) = v8[3];
                }
            } else {
                temp_r4_14 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_14, f32 *, 0x18) = v80[0];
                M2C_FIELD(temp_r4_14, f32 *, 0x1C) = v80[1];
                M2C_FIELD(temp_r4_14, f32 *, 0x20) = v80[2];
                M2C_FIELD(M2C_FIELD(temp_r4_14, u8 **, 8), f32 *, 0x90) = v80[0];
                M2C_FIELD(M2C_FIELD(temp_r4_14, u8 **, 8), f32 *, 0x94) = v80[1];
                M2C_FIELD(M2C_FIELD(temp_r4_14, u8 **, 8), f32 *, 0x98) = v80[2];
            }
            _particleClampScale(&v74[0]);
            _particleClampScale(&v74[1]);
            _particleClampScale(&v74[2]);
            if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                temp_r3_16 = M2C_FIELD(p0, u8 **, 0x38);
                if (temp_r3_16 != NULL) {
                    M2C_FIELD(temp_r3_16, f32 *, 0x128) = v74[0];
                    M2C_FIELD(temp_r3_16, f32 *, 0x12C) = v74[1];
                    M2C_FIELD(temp_r3_16, f32 *, 0x130) = v74[2];
                }
            } else {
                temp_r4_15 = M2C_FIELD(p0, u8 **, 0x38);
                M2C_FIELD(temp_r4_15, f32 *, 0x24) = v74[0];
                M2C_FIELD(temp_r4_15, f32 *, 0x28) = v74[1];
                M2C_FIELD(temp_r4_15, f32 *, 0x2C) = v74[2];
                M2C_FIELD(M2C_FIELD(temp_r4_15, u8 **, 8), f32 *, 0x9C) = v74[0];
                M2C_FIELD(M2C_FIELD(temp_r4_15, u8 **, 8), f32 *, 0xA0) = v74[1];
                M2C_FIELD(M2C_FIELD(temp_r4_15, u8 **, 8), f32 *, 0xA4) = v74[2];
            }
            break;
        }
        M2C_FIELD(p0, bool *, 2) = !M2C_FIELD(p0, u8 *, 1);
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
                                data->camera = NULL;
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
                        cam = (GScamera*)data->camera;
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
                                data->camera = NULL;
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
        psSetBillboardCamera(M2C_FIELD(active, HSD_CObj **, 8));
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
        if ((u8) M2C_FIELD(temp_r26, u8 *, 0) == 1) {
            var_r27 = M2C_FIELD(temp_r26, u8 **, 0xC);
            var_r29 = 0U;
            while (var_r29 < (u8) M2C_FIELD(temp_r26, u8 *, 3)) {
                if (M2C_FIELD(var_r27, u8 **, 0x38) != NULL) {
                    if (!_genIsAlive(var_r27)) {
                        GSparticleDestroyGenerator(var_r27, 1U);
                    }
                }
                var_r29 += 1;
                var_r27 += 0x3C;
            }
        }
        var_r31 += 0x14;
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
    temp_r31 = M2C_FIELD(p0, u8 *, 0x16A7) != 0;
    if (temp_r3 == NULL || GScameraIsValid((GScamera*)(temp_r3)) == 0) {
        return;
    } else {
        temp_r28 = GSgfxPerfbarCPUEntry(0xFF00FF);
        if ((u8) _invalidateVtx != 0) {
            M2C_FIELD(p0, s32 *, 4) = (s32) (M2C_FIELD(p0, s32 *, 4) | 0x08000000);
            _invalidateVtx = 0;
        }
        if ((u8) _invalidateTex != 0) {
            M2C_FIELD(p0, s32 *, 4) = (s32) (M2C_FIELD(p0, s32 *, 4) | 0x10000000);
            _invalidateTex = 0;
        }
        if (temp_r31 != 0) {
            M2C_FIELD(p0, u8 *, 0x16A7) = 0U;
            M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 0x40);
            M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 0x40);
            M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 0x40);
        }
        temp_r0 = M2C_FIELD(p0, s32 *, 0x28);
        switch (temp_r0) {
        case 4:
            var_r29 = 2;
        case 2:
            if ((p1 == 1) && (psDispHasRenderData(var_r29) == 1)) {
                M2C_FIELD(p0, s32 *, 0xD90) = 0;
                var_r27 = 0;
                M2C_FIELD(p0, s32 *, 0x16B8) = (s32) (M2C_FIELD(p0, s32 *, 0x16B8) | 4);
                M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 2);
                M2C_FIELD(p0, s32 *, 0x1770) = (s32) (M2C_FIELD(p0, s32 *, 0x1770) | 4);
                M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 2);
                _particleRenderCamera(p0, temp_r3, var_r29, NULL);
                for (var_r24 = 0; var_r24 < g_particle_cameras_count; var_r24++) {
                    temp_r25 = g_particle_cameras[var_r24];
                    if (GScameraIsValid((GScamera*)(temp_r25)) != 0) {
                        var_r27 = 1;
                        _particleRenderCamera(p0, temp_r25, var_r29, temp_r25);
                    }
                }
                M2C_FIELD(p0, s8 *, 0xD44) = 0;
                M2C_FIELD(p0, s8 *, 0xD45) = 0;
                M2C_FIELD(p0, s32 *, 0x16B4) = (s32) (M2C_FIELD(p0, s32 *, 0x16B4) | 1);
                M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 1);
                M2C_FIELD(p0, s32 *, 0x176C) = (s32) (M2C_FIELD(p0, s32 *, 0x176C) | 1);
                M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 1);
                if (var_r27 != 0) {
                    GScameraLoadActiveCameraMatrix((GSgfxLayerID)(M2C_FIELD(p0, s32 *, 0x28)));
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
            M2C_FIELD(p0, u8 *, 0x16A7) = 1U;
            M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 0x40);
            M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 0x40);
            M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 0x200);
            M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 0x200);
            if ((u8) M2C_FIELD(p0, u8 *, 0x16A6) != 0) {
                M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 0x100);
                M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 0x100);
            }
            M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 0x40);
        }
        GSgfxPerfbarCPUEntry(temp_r28);
    }
}
}
