#include <dolphin/types.h>
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
    u8 _draft[1];
};
struct GSpart {
    u8 _draft[1];
};
struct GSparticleGenerator {
    u8 _draft[1];
};
struct GSquat {
    u8 _draft[1];
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
struct _GSparticleBank {
    u8 _draft[1];
};
struct _GSparticleGen {
    u8 _draft[1];
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
u32 GSmodelIsRootNullAdded(_GSmodel* model);
_GSmodel* GSmodelSearchModelList(HSD_JObj* jobj);
void GSmodelSet60fpsAnimFlag(_GSmodel* model, u8 enable);
void GSpartFree(GSpart* part);
s32 GSpartGetJObjIndex(void*, void*);
void GSpartGetTransform(GSpart* part, GSvec* pos, GSvec* rot, GSvec* scale);
void GSparticleAttachGeneratorToGSpart(void *p0, void *p1, s32 p2, s8 p3, u8 p4, u8 p5);
void GSparticleBankSetCamera(void *p0, s32 p1);
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
void* peBankLoadFile(void*, void*);
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
extern s32 unitScaleVector;
struct XdBlob10 { u8 data[0x10]; };
extern XdBlob10 zeroQuaternion;
struct XdBlobC { u8 data[0xC]; };
extern XdBlobC zeroVector;
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
static u8 init_S2345;
static f32 sysdolRemain_S2344;

extern "C" {
u8* GSparticleLoad(void *p0);
}

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
                GScameraLoadProjection((GScamera*)(temp_r3), (GSgfxLayer*)(p0));
                ((GSgfxLayer*)(p0))->FlushState();
                psDispSetProjection((void*)(((u8*)(p0) + 0xD54)));
                psSetBillboardCamera((HSD_CObj*)(M2C_FIELD(temp_r3, HSD_CObj **, 8)));
                psDispParticles(var_r29, 1U, (void*)(NULL));
                psDispParticles(var_r29, 2U, (void*)(NULL));
                ((GSgfxLayer*)(p0))->InvalidateState();
                var_r24 = 0U;
                var_r30 = g_particle_cameras;
                while (var_r24 < (u32) g_particle_cameras_count) {
                    temp_r25 = *var_r30;
                    if (GScameraIsValid((GScamera*)(temp_r25)) != 0) {
                        var_r27 = 1;
                        GScameraLoadProjection((GScamera*)(temp_r25), (GSgfxLayer*)(p0));
                        ((GSgfxLayer*)(p0))->FlushState();
                        psDispSetProjection((void*)(((u8*)(p0) + 0xD54)));
                        psSetBillboardCamera((HSD_CObj*)(M2C_FIELD(temp_r25, HSD_CObj **, 8)));
                        psDispParticles(var_r29, 1U, (void*)(temp_r25));
                        psDispParticles(var_r29, 2U, (void*)(temp_r25));
                        ((GSgfxLayer*)(p0))->InvalidateState();
                    }
                    var_r30++;
                    var_r24 += 1;
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

extern "C++" {
static void _particlePostUpdate(float p0) {
    s32 var_r31;
    u32 var_r30;
    s32 temp_cr0_eq;
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
                temp_r3 = M2C_FIELD(var_r27, u8 **, 0x38);
                temp_cr0_eq = temp_r3 == NULL;
                if (temp_cr0_eq) {
                    if (temp_cr0_eq != 0) {
                        var_r0 = 0;
                    } else {
                        temp_r0 = M2C_FIELD(var_r27, u8 *, 0);
                        if (temp_r0 != 0) {
                            if (temp_r3 == NULL) {
                                var_r3 = 0;
                            } else if (temp_r0 != 0) {
                                if (peBankIsInfinite((u32)(temp_r3)) != 0) {
                                    var_r3 = -1U;
                                } else {
                                    var_r3 = (u32) (peBankGetLife(M2C_FIELD(var_r27, u8 **, 0x38)) * ((f32) GSgfxVideoGetVsyncRate()));
                                }
                            } else if ((u8) M2C_FIELD(temp_r3, u8 *, 1) == 1) {
                                var_r3 = -1U;
                            } else {
                                var_r3 = psGetGeneratorChildMaxLife((PSGenerator*)(M2C_FIELD(temp_r3, PSGenerator **, 8)));
                            }
                            var_r0 = var_r3 != 0;
                        } else if ((u8) M2C_FIELD(temp_r3, u8 *, 1) != 0) {
                            var_r0 = 1;
                        } else if (psGetParticleChildCount((PSGenerator*)(M2C_FIELD(temp_r3, PSGenerator **, 8))) != 0) {
                            var_r0 = 1;
                        } else {
                            temp_r3_2 = M2C_FIELD(var_r27, u8 **, 0x38);
                            if (temp_r3_2 == NULL) {
                                var_r3_2 = 0;
                            } else if ((u8) M2C_FIELD(var_r27, u8 *, 0) != 0) {
                                if (peBankIsInfinite((u32)(temp_r3_2)) != 0) {
                                    var_r3_2 = -1U;
                                } else {
                                    var_r3_2 = (u32) (peBankGetLife(M2C_FIELD(var_r27, u8 **, 0x38)) * ((f32) GSgfxVideoGetVsyncRate()));
                                }
                            } else if ((u8) M2C_FIELD(temp_r3_2, u8 *, 1) == 1) {
                                var_r3_2 = -1U;
                            } else {
                                var_r3_2 = psGetGeneratorChildMaxLife((PSGenerator*)(M2C_FIELD(temp_r3_2, PSGenerator **, 8)));
                            }
                            var_r0 = var_r3_2 != 0;
                        }
                    }
                    if (var_r0 == 0) {
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
extern "C++" {
#pragma optimize_for_size on

extern "C++" {
static void _particlePreUpdate(float p0) {
    GScamera **var_r3;
    s32 var_r31 = 0;
    GScamera *temp_r3_7;
    u8 var_r4;
    _GSparticleGen *var_r25;
    u32 var_r30;
    f32 temp_f1;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    GScamera *temp_r3;
    u32 temp_r3_5;
    u32 var_ctr;
    u32 var_r25_3;
    u32 var_r27_2;
    u32 var_r29_2;
    s32 temp_r28;
    _GSparticleGen *var_r27;
    u8 *temp_r26;
    u8 temp_r3_6;
    u8 temp_r3_8;
    u32 var_r29;
    GScamera *var_r25_2;
    u8 *temp_r3_2;
    u8 *temp_r3_3;
    u8 *temp_r3_4;

    if ((s8) init_S2345 == 0) {
        init_S2345 = 1;
        sysdolRemain_S2344 = 0.0f;
    }
    temp_r28 = GSgfxPerfbarCPUEntry(0x800080);
    memset((void*)(g_particle_cameras), 0, 0x10U);
    var_r30 = 0U;
    g_particle_cameras_count = 0;
    while (var_r30 < (u32) _particleBankStructCount) {
        temp_r26 = &_particleBankStructList[var_r31];
        if ((u8) M2C_FIELD(temp_r26, u8 *, 0) == 1) {
            temp_r3 = M2C_FIELD(temp_r26, GScamera **, 0x10);
            if ((temp_r3 != NULL) && (GScameraIsValid((GScamera*)(temp_r3)) == 0) && (temp_r26 != NULL) && ((u8) M2C_FIELD(temp_r26, u8 *, 0) != 0)) {
                M2C_FIELD(temp_r26, GScamera **, 0x10) = NULL;
                var_r29 = M2C_FIELD(temp_r26, u8 *, 3);
                var_r25 = M2C_FIELD(temp_r26, _GSparticleGen **, 0xC);
loop_16:
                temp_cr0_eq = var_r29 == 0;
                var_r29 -= 1;
                if (temp_cr0_eq == 0) {
                    temp_r3_2 = M2C_FIELD(var_r25, u8 **, 0x38);
                    temp_cr0_eq_2 = temp_r3_2 == NULL;
                    if ((temp_cr0_eq_2 == 0) && (temp_cr0_eq_2 == 0)) {
                        if ((u8) M2C_FIELD(var_r25, u8 *, 0) != 0) {
                            if (temp_r3_2 != NULL) {
                                M2C_FIELD(temp_r3_2, s32 *, 0x160) = 0;
                            }
                        } else {
                            psGeneratorSetCamera((HSD_Generator*)(M2C_FIELD(temp_r3_2, HSD_Generator **, 8)), (HSD_CObj*)(NULL));
                        }
                    }
                    var_r25 += 0x3C;
                    goto loop_16;
                }
            }
            var_r27 = M2C_FIELD(temp_r26, _GSparticleGen **, 0xC);
            var_r29_2 = 0U;
            while (var_r29_2 < (u8) M2C_FIELD(temp_r26, u8 *, 3)) {
                if ((u8 *) M2C_FIELD(var_r27, u8 **, 0x38) != NULL) {
                    _particleUpdateAttachment((_GSparticleGen*)(var_r27));
                    temp_r3_3 = M2C_FIELD(var_r27, u8 **, 0x38);
                    if (temp_r3_3 == NULL) {
                        var_r25_2 = NULL;
                    } else if ((u8) M2C_FIELD(var_r27, u8 *, 0) != 0) {
                        if (temp_r3_3 != NULL) {
                            var_r25_2 = M2C_FIELD(temp_r3_3, GScamera **, 0x160);
                        } else {
                            var_r25_2 = NULL;
                        }
                    } else {
                        var_r25_2 = (GScamera *)(psGeneratorGetCamera((HSD_Generator*)(M2C_FIELD(temp_r3_3, HSD_Generator **, 8))));
                    }
                    if (GScameraIsValid((GScamera*)(var_r25_2)) != 0) {
                        var_r3 = (GScamera **)(g_particle_cameras);
                        var_r4 = 0;
                        var_ctr = g_particle_cameras_count;
                        if ((u32) g_particle_cameras_count > 0U) {
loop_28:
                            if ((GScamera *) *var_r3 == var_r25_2) {
                                var_r4 = 1;
                            } else {
                                var_r3 += 4;
                                var_ctr -= 1;
                                if (var_ctr != 0) {
                                    goto loop_28;
                                }
                            }
                        }
                        if (var_r4 == 0) {
                            g_particle_cameras[g_particle_cameras_count] = var_r25_2;
                            g_particle_cameras_count += 1;
                        }
                    } else {
                        temp_r3_4 = M2C_FIELD(var_r27, u8 **, 0x38);
                        if (temp_r3_4 != NULL) {
                            if ((u8) M2C_FIELD(var_r27, u8 *, 0) != 0) {
                                if (temp_r3_4 != NULL) {
                                    M2C_FIELD(temp_r3_4, GScamera **, 0x160) = NULL;
                                }
                            } else {
                                psGeneratorSetCamera((HSD_Generator*)(M2C_FIELD(temp_r3_4, HSD_Generator **, 8)), (HSD_CObj*)(NULL));
                            }
                        }
                    }
                }
                var_r29_2 += 1;
                var_r27 += 0x3C;
            }
        }
        var_r31 += 0x14;
        var_r30 += 1;
    }
    var_r27_2 = (u32) p0;
    temp_f1 = sysdolRemain_S2344 + (p0 - (f32) var_r27_2);
    sysdolRemain_S2344 = temp_f1;
    if (temp_f1 >= 1.0f) {
        temp_r3_5 = (u32) temp_f1;
        var_r27_2 += temp_r3_5;
        sysdolRemain_S2344 -= (f32) temp_r3_5;
    }
    if (GSgfxVideoGetVsyncRate() == 0x32) {
        temp_r3_6 = 1;
        temp_r3_6 += _particlePALFrameCount;
        _particlePALFrameCount = temp_r3_6;
        if (temp_r3_6 >= 5U) {
            var_r27_2 += 1;
            _particlePALFrameCount = 0;
        }
    }
    temp_r3_7 = GScameraGetActiveCamera();
    if ((temp_r3_7 != NULL) && (GScameraIsValid((GScamera*)(temp_r3_7)) != 0)) {
        psSetBillboardCamera((HSD_CObj*)(M2C_FIELD(temp_r3_7, HSD_CObj **, 8)));
        var_r25_3 = 0U;
        while (var_r25_3 < var_r27_2) {
            psInterpretParticles(0);
            psExecGenerator(0);
            var_r25_3 += 1;
        }
    }
    temp_r3_8 = GSgfxVideoGetVsyncRate();
    particleEngineUpdate((u16)temp_r3_8, p0 / (f32) temp_r3_8);
    psDispBeginFrame();
    GSgfxPerfbarCPUEntry(temp_r28);
}
}
static void _particleUpdateAttachment(_GSparticleGen* p0) {
    f32 var_f1_3;
    f32 sp1C;
    f32 sp20;
    f32 sp24;
    f32 sp2C;
    f32 sp30;
    f32 sp34;
    f32 unksp18;
    f32 unksp28;
    f32 v38[4];
    f32 v48[4];
    s32 unksp58;
    s32 unksp64;
    f32 v8[4];
    f32 v80[3];
    f32 v8C[3];
    f32 sp7C;
    f32 sp78;
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
    u32 unksp74;
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
        GSpartGetTransform((GSpart*)(temp_r3), (GSvec*)(v8C), (GSvec*)(v80), (GSvec*)(&unksp74));
        GSpartFree((GSpart*)(temp_r3));
        EulerToQuat((Vec*)(v80), (Quaternion*)(&unksp64));
        GSvecTransformQuat((GSvec*)(&unksp58), (const GSquat*)(&unksp64), (const GSvec*)(((u8*)((s32)p0) + 0x10)));
        PSVECAdd((const register Vec*)(v8C), (const register Vec*)(&unksp58), (register Vec*)(v8C));
        PSVECAdd((const register Vec*)(v80), (const register Vec*)(((u8*)((s32)p0) + 0x1C)), (register Vec*)(v80));
        sp78 *= M2C_FIELD(p0, f32 *, 0x2C);
        sp7C *= M2C_FIELD(p0, f32 *, 0x30);
        unksp74 *= M2C_FIELD(p0, f32 *, 0x28);
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
        temp_r0 = M2C_FIELD(p0, s32 *, 8);
        if ((u32) temp_r0 <= 7U) {
            switch (temp_r0) {
            case 1:
                if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                    if ((M2C_FIELD(p0, u8 **, 0x38)) != NULL) {
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x10C) = v8C[0];
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x110) = v8C[1];
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x114) = v8C[2];
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
                if (unksp74 > 0.0f) {
                    var_f0_4 = unksp74;
                } else {
                    var_f0_4 = -unksp74;
                }
                var_f1_4 = 0.00001f;
                if (var_f0_4 < 0.00001f) {
                    if (unksp74 < 0.0f) {
                        var_f1_4 = -0.00001f;
                    }
                    unksp74 = var_f1_4;
                }
                if (sp78 > 0.0f) {
                    var_f0_5 = sp78;
                } else {
                    var_f0_5 = -sp78;
                }
                var_f1_5 = 0.00001f;
                if (var_f0_5 < 0.00001f) {
                    if (sp78 < 0.0f) {
                        var_f1_5 = -0.00001f;
                    }
                    sp78 = var_f1_5;
                }
                if (sp7C > 0.0f) {
                    var_f0_6 = sp7C;
                } else {
                    var_f0_6 = -sp7C;
                }
                var_f1_6 = 0.00001f;
                if (var_f0_6 < 0.00001f) {
                    if (sp7C < 0.0f) {
                        var_f1_6 = -0.00001f;
                    }
                    sp7C = var_f1_6;
                }
                if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                    if ((M2C_FIELD(p0, u8 **, 0x38)) != NULL) {
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x128) = unksp74;
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x12C) = sp78;
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x130) = sp7C;
                    }
                } else {
                    temp_r4_6 = M2C_FIELD(p0, u8 **, 0x38);
                    M2C_FIELD(temp_r4_6, f32 *, 0x28) = sp78;
                    M2C_FIELD(temp_r4_6, f32 *, 0x24) = unksp74;
                    M2C_FIELD(M2C_FIELD(temp_r4_6, u8 **, 8), f32 *, 0xA0) = sp78;
                    M2C_FIELD(temp_r4_6, f32 *, 0x2C) = sp7C;
                    M2C_FIELD(M2C_FIELD(temp_r4_6, u8 **, 8), f32 *, 0x9C) = unksp74;
                    M2C_FIELD(M2C_FIELD(temp_r4_6, u8 **, 8), f32 *, 0xA4) = sp7C;
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
                    EulerToQuat((Vec*)(v80), (Quaternion*)(&unksp28));
                    if ((M2C_FIELD(p0, u8 **, 0x38)) != NULL) {
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x118) = unksp28;
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x11C) = sp2C;
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x120) = sp30;
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x124) = sp34;
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
                    EulerToQuat((Vec*)(v80), (Quaternion*)(&unksp18));
                    if ((M2C_FIELD(p0, u8 **, 0x38)) != NULL) {
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x118) = unksp18;
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x11C) = sp1C;
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x120) = sp20;
                        M2C_FIELD((M2C_FIELD(p0, u8 **, 0x38)), f32 *, 0x124) = sp24;
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
                if (unksp74 > 0.0f) {
                    var_f0_7 = unksp74;
                } else {
                    var_f0_7 = -unksp74;
                }
                var_f1_7 = 0.00001f;
                if (var_f0_7 < 0.00001f) {
                    if (unksp74 < 0.0f) {
                        var_f1_7 = -0.00001f;
                    }
                    unksp74 = var_f1_7;
                }
                if (sp78 > 0.0f) {
                    var_f0_8 = sp78;
                } else {
                    var_f0_8 = -sp78;
                }
                var_f1_8 = 0.00001f;
                if (var_f0_8 < 0.00001f) {
                    if (sp78 < 0.0f) {
                        var_f1_8 = -0.00001f;
                    }
                    sp78 = var_f1_8;
                }
                if (sp7C > 0.0f) {
                    var_f0_9 = sp7C;
                } else {
                    var_f0_9 = -sp7C;
                }
                var_f1_9 = 0.00001f;
                if (var_f0_9 < 0.00001f) {
                    if (sp7C < 0.0f) {
                        var_f1_9 = -0.00001f;
                    }
                    sp7C = var_f1_9;
                }
                if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                    temp_r3_11 = M2C_FIELD(p0, u8 **, 0x38);
                    if (temp_r3_11 != NULL) {
                        M2C_FIELD(temp_r3_11, f32 *, 0x128) = unksp74;
                        M2C_FIELD(temp_r3_11, f32 *, 0x12C) = sp78;
                        M2C_FIELD(temp_r3_11, f32 *, 0x130) = sp7C;
                    }
                } else {
                    temp_r4_10 = M2C_FIELD(p0, u8 **, 0x38);
                    M2C_FIELD(temp_r4_10, f32 *, 0x28) = sp78;
                    M2C_FIELD(temp_r4_10, f32 *, 0x24) = unksp74;
                    M2C_FIELD(temp_r4_10, f32 *, 0x2C) = sp7C;
                    M2C_FIELD(M2C_FIELD(temp_r4_10, u8 **, 8), f32 *, 0x9C) = unksp74;
                    M2C_FIELD(M2C_FIELD(temp_r4_10, u8 **, 8), f32 *, 0xA0) = sp78;
                    M2C_FIELD(M2C_FIELD(temp_r4_10, u8 **, 8), f32 *, 0xA4) = sp7C;
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
                if (unksp74 > 0.0f) {
                    var_f0_10 = unksp74;
                } else {
                    var_f0_10 = -unksp74;
                }
                var_f1_10 = 0.00001f;
                if (var_f0_10 < 0.00001f) {
                    if (unksp74 < 0.0f) {
                        var_f1_10 = -0.00001f;
                    }
                    unksp74 = var_f1_10;
                }
                if (sp78 > 0.0f) {
                    var_f0_11 = sp78;
                } else {
                    var_f0_11 = -sp78;
                }
                var_f1_11 = 0.00001f;
                if (var_f0_11 < 0.00001f) {
                    if (sp78 < 0.0f) {
                        var_f1_11 = -0.00001f;
                    }
                    sp78 = var_f1_11;
                }
                if (sp7C > 0.0f) {
                    var_f0_12 = sp7C;
                } else {
                    var_f0_12 = -sp7C;
                }
                var_f1_12 = 0.00001f;
                if (var_f0_12 < 0.00001f) {
                    if (sp7C < 0.0f) {
                        var_f1_12 = -0.00001f;
                    }
                    sp7C = var_f1_12;
                }
                if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                    temp_r3_13 = M2C_FIELD(p0, u8 **, 0x38);
                    if (temp_r3_13 != NULL) {
                        M2C_FIELD(temp_r3_13, f32 *, 0x128) = unksp74;
                        M2C_FIELD(temp_r3_13, f32 *, 0x12C) = sp78;
                        M2C_FIELD(temp_r3_13, f32 *, 0x130) = sp7C;
                    }
                } else {
                    temp_r4_12 = M2C_FIELD(p0, u8 **, 0x38);
                    M2C_FIELD(temp_r4_12, f32 *, 0x28) = sp78;
                    M2C_FIELD(temp_r4_12, f32 *, 0x24) = unksp74;
                    M2C_FIELD(temp_r4_12, f32 *, 0x2C) = sp7C;
                    M2C_FIELD(M2C_FIELD(temp_r4_12, u8 **, 8), f32 *, 0x9C) = unksp74;
                    M2C_FIELD(M2C_FIELD(temp_r4_12, u8 **, 8), f32 *, 0xA0) = sp78;
                    M2C_FIELD(M2C_FIELD(temp_r4_12, u8 **, 8), f32 *, 0xA4) = sp7C;
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
                if (unksp74 > 0.0f) {
                    var_f0_13 = unksp74;
                } else {
                    var_f0_13 = -unksp74;
                }
                var_f1_13 = 0.00001f;
                if (var_f0_13 < 0.00001f) {
                    if (unksp74 < 0.0f) {
                        var_f1_13 = -0.00001f;
                    }
                    unksp74 = var_f1_13;
                }
                if (sp78 > 0.0f) {
                    var_f0_14 = sp78;
                } else {
                    var_f0_14 = -sp78;
                }
                var_f1_14 = 0.00001f;
                if (var_f0_14 < 0.00001f) {
                    if (sp78 < 0.0f) {
                        var_f1_14 = -0.00001f;
                    }
                    sp78 = var_f1_14;
                }
                if (sp7C > 0.0f) {
                    var_f0_15 = sp7C;
                } else {
                    var_f0_15 = -sp7C;
                }
                var_f1_15 = 0.00001f;
                if (var_f0_15 < 0.00001f) {
                    if (sp7C < 0.0f) {
                        var_f1_15 = -0.00001f;
                    }
                    sp7C = var_f1_15;
                }
                if ((u8) M2C_FIELD(p0, u8 *, 0) != 0) {
                    temp_r3_16 = M2C_FIELD(p0, u8 **, 0x38);
                    if (temp_r3_16 != NULL) {
                        M2C_FIELD(temp_r3_16, f32 *, 0x128) = unksp74;
                        M2C_FIELD(temp_r3_16, f32 *, 0x12C) = sp78;
                        M2C_FIELD(temp_r3_16, f32 *, 0x130) = sp7C;
                    }
                } else {
                    temp_r4_15 = M2C_FIELD(p0, u8 **, 0x38);
                    M2C_FIELD(temp_r4_15, f32 *, 0x28) = sp78;
                    M2C_FIELD(temp_r4_15, f32 *, 0x24) = unksp74;
                    M2C_FIELD(temp_r4_15, f32 *, 0x2C) = sp7C;
                    M2C_FIELD(M2C_FIELD(temp_r4_15, u8 **, 8), f32 *, 0x9C) = unksp74;
                    M2C_FIELD(M2C_FIELD(temp_r4_15, u8 **, 8), f32 *, 0xA0) = sp78;
                    M2C_FIELD(M2C_FIELD(temp_r4_15, u8 **, 8), f32 *, 0xA4) = sp7C;
                }
                break;
            }
        }
        M2C_FIELD(p0, u8 *, 2) = (u8) (M2C_FIELD(p0, u8 *, 1) == 0);
    }
}
#pragma optimize_for_size reset
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

extern "C" {
void GSparticleBankSetCamera(void *p0, s32 p1) {
    u8 *var_r31;
    s32 temp_cr0_eq_2;
    s32 var_r30;
    u8 *temp_r3;
    s32 temp_cr0_eq;

    if (p0 != NULL) {
        if ((u8) M2C_FIELD(p0, u8 *, 0) == 0) {
            return;
        }
        var_r31 = M2C_FIELD(p0, u8 **, 0xC);
        M2C_FIELD(p0, s32 *, 0x10) = p1;
        var_r30 = M2C_FIELD(p0, u8 *, 3);
loop_11:
        temp_cr0_eq = var_r30 == 0;
        var_r30 -= 1;
        if (temp_cr0_eq == 0) {
            temp_r3 = M2C_FIELD(var_r31, u8 **, 0x38);
            temp_cr0_eq_2 = temp_r3 == NULL;
            if ((temp_cr0_eq_2 == 0) && (temp_cr0_eq_2 == 0)) {
                if ((u8) M2C_FIELD(var_r31, u8 *, 0) != 0) {
                    if (temp_r3 != NULL) {
                        M2C_FIELD(temp_r3, s32 *, 0x160) = p1;
                    }
                } else {
                    psGeneratorSetCamera((HSD_Generator*)(M2C_FIELD(temp_r3, HSD_Generator **, 8)), (HSD_CObj*)((HSD_CObj *) p1));
                }
            }
            var_r31 += 0x3C;
            goto loop_11;
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
}
void GSparticleActivateBank(GSparticleBank* bank) {
    bank->inactive = 0;
}

void GSparticleDisactivateBank(GSparticleBank* bank) {
    bank->inactive = 1;
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
void GSparticleAttachGeneratorToGSpart(void *p0, void *p1, s32 p2, s8 p3, u8 p4, u8 p5) {
    volatile f32 spC;
    volatile f32 sp10;
    f32 sp14;
    f32 sp8;
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
                sp8 = M2C_FIELD(temp_r3_2, f32 *, 0x118);
                spC = M2C_FIELD(temp_r3_2, f32 *, 0x11C);
                sp10 = M2C_FIELD(temp_r3_2, f32 *, 0x120);
                sp14 = M2C_FIELD(temp_r3_2, f32 *, 0x124);
            } else {
                sp10 = 0.0f;
                spC = 0.0f;
                sp8 = 0.0f;
                sp14 = 1.0f;
            }
            GSvecMakeFromQuat((GSvec*)(((u8*)(p0) + 0x1C)), (const GSquat*)((GSquat *) &sp8));
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
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* p0, s32 p1, s32 p2) {
    GSparticleGenerator *var_r30;
    s32 var_r30_2;
    s32 var_r28;
    HSD_Generator *temp_r3_3;
    s32 var_r3_2;
    u8 *var_r4;
    s32 var_r4_2;
    s8 temp_r0;
    s8 temp_r0_2;
    s8 temp_r0_3;
    u8 temp_r5;
    u8 *var_r5;
    s32 var_ctr_2;
    s32 var_ctr_3;
    u8 *temp_r3;
    u8 *temp_r3_2;
    u8 *var_r3;
    s32 var_r3_3;
    s32 var_ctr;

    if ((u8) M2C_FIELD(p0, u8 *, 0) == 0) {
        return NULL;
    }
    if ((u8) M2C_FIELD(p0, u8 *, 4) != 0) {
        return NULL;
    }
    temp_r5 = M2C_FIELD(p0, u8 *, 2);
    if (temp_r5 != 0) {
        temp_r0 = M2C_FIELD(p0, u8 *, 3);
        var_r30_2 = 0;
        var_r3 = M2C_FIELD(p0, u8 **, 0xC);
        var_ctr = temp_r0;
        if (temp_r0 > 0) {
loop_6:
            if (temp_r5 != (u8) M2C_FIELD(var_r3, u8 *, 0)) {
                var_r30_2 = -1;
            } else if ((u32) M2C_FIELD(var_r3, u32 *, 0x38) == 0U) {

            } else {
                var_r30_2 += 1;
                var_r3 += 0x3C;
                var_ctr -= 1;
                if (var_ctr == 0) {
                    goto block_11;
                }
                goto loop_6;
            }
        } else {
block_11:
            var_r30_2 = -1;
        }
        if (var_r30_2 < 0) {
            return NULL;
        }
        temp_r3 = (unsigned char *)(peBankCreate(M2C_FIELD(p0, s32 *, 8)));
        if (temp_r3 == NULL) {
            return NULL;
        }
        var_r30 = (GSparticleGenerator *)(M2C_FIELD(p0, u8 **, 0xC) + (var_r30_2 * 0x3C));
        if ((u8) M2C_FIELD(var_r30, u8 *, 0) == 0) {
            return NULL;
        }
        if (temp_r3 != NULL) {
            M2C_FIELD((u16)temp_r3, HSD_CObj **, 0x160) = (HSD_CObj *) M2C_FIELD(p0, HSD_CObj **, 0x10);
        }
        peBankStart(temp_r3);
        M2C_FIELD(var_r30, u8 **, 0x38) = temp_r3;
        _invalidateVtx = 1;
        goto block_50;
    }
    temp_r0_2 = M2C_FIELD(p0, u8 *, 3);
    var_r3_2 = 0;
    var_r4 = M2C_FIELD(p0, u8 **, 0xC);
    var_ctr_2 = temp_r0_2;
    if (temp_r0_2 > 0) {
loop_22:
        if (temp_r5 != (u8) M2C_FIELD(var_r4, u8 *, 0)) {
            var_r3_2 = -1;
        } else if ((u32) M2C_FIELD(var_r4, u32 *, 0x38) == 0U) {

        } else {
            var_r3_2 += 1;
            var_r4 += 0x3C;
            var_ctr_2 -= 1;
            if (var_ctr_2 == 0) {
                goto block_27;
            }
            goto loop_22;
        }
    } else {
block_27:
        var_r3_2 = -1;
    }
    var_r28 = var_r3_2;
    if (var_r3_2 < 0) {
        _particleBankDestroyOldestGenerator((_GSparticleBank*)((_GSparticleBank *) p0));
        temp_r0_3 = M2C_FIELD(p0, u8 *, 3);
        var_r4_2 = 0;
        var_r5 = M2C_FIELD(p0, u8 **, 0xC);
        var_ctr_3 = temp_r0_3;
        if (temp_r0_3 > 0) {
loop_30:
            if ((u8) M2C_FIELD(p0, u8 *, 2) != (u8) M2C_FIELD(var_r5, u8 *, 0)) {
                var_r4_2 = -1;
            } else if ((u32) M2C_FIELD(var_r5, u32 *, 0x38) == 0U) {

            } else {
                var_r4_2 += 1;
                var_r5 += 0x3C;
                var_ctr_3 -= 1;
                if (var_ctr_3 == 0) {
                    goto block_35;
                }
                goto loop_30;
            }
        } else {
block_35:
            var_r4_2 = -1;
        }
        var_r28 = var_r4_2;
        if (var_r4_2 < 0) {
            return NULL;
        }
        goto block_38;
    }
block_38:
    temp_r3_2 = (unsigned char *)(GSmemAlloc(0x30U));
    if (temp_r3_2 == NULL) {
        return NULL;
    }
    var_r3_3 = 0;
    if ((u8) p2 == 1) {
        var_r3_3 = 1;
    }
    M2C_FIELD(temp_r3_2, HSD_Generator **, 8) = psCreateGeneratorID(var_r3_3, (s32) M2C_FIELD(p0, u8 *, 1), p1);
    temp_r3_3 = M2C_FIELD(temp_r3_2, HSD_Generator **, 8);
    if (temp_r3_3 == NULL) {
        GSmemFree((void*)(temp_r3_2));
        return NULL;
    }
    M2C_FIELD(temp_r3_3, s8 *, 0x17) = 1;
    psGeneratorSetCamera((HSD_Generator*)(M2C_FIELD(temp_r3_2, HSD_Generator **, 8)), (HSD_CObj*)(M2C_FIELD(p0, HSD_CObj **, 0x10)));
    M2C_FIELD(temp_r3_2, s16 *, 2) = (s16) p1;
    M2C_FIELD(temp_r3_2, s8 *, 0) = (s8) p2;
    M2C_FIELD(temp_r3_2, s32 *, 4) = GSgfxVideoGetVsyncCount();
    if ((u16) M2C_FIELD(M2C_FIELD(temp_r3_2, HSD_Generator **, 8), u16 *, 0x10) == 0) {
        M2C_FIELD(temp_r3_2, s8 *, 1) = 1;
    } else {
        M2C_FIELD(temp_r3_2, s8 *, 1) = 0;
    }
    var_r30 = (GSparticleGenerator *)(M2C_FIELD(p0, u8 **, 0xC) + (var_r28 * 0x3C));
    if ((u8) M2C_FIELD(var_r30, u8 *, 0) != 0) {
        return NULL;
    }
    M2C_FIELD(var_r30, u8 **, 0x38) = temp_r3_2;
block_50:
    _invalidateTex = 1;
    M2C_FIELD(var_r30, s32 *, 8) = 0;
    M2C_FIELD(var_r30, s32 *, 0xC) = 0;
    M2C_FIELD(var_r30, s32 *, 4) = 0;
    M2C_FIELD(var_r30, s8 *, 1) = 0;
    M2C_FIELD(var_r30, s8 *, 2) = 0;
    M2C_FIELD(var_r30, GSparticleBank **, 0x34) = p0;
    return var_r30;
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
extern "C" {
u8* GSparticleLoad(void *p0) {
    bool var_r30;
    ModelBank *temp_r4;
    ModelBank *temp_r4_2;
    ModelBank *temp_ret;
    f32 temp_f1;
    s32 temp_r4_3;
    s32 temp_r5;
    u32 var_ctr;
    u32 var_ctr_2;
    u8 *var_r29;
    u8 *var_r4;
    s32 var_r0;
    ModelBank *temp_r3;

    var_r29 = _particleBankStructList;
    if (var_ctr < _particleBankStructCount) var_ctr = _particleBankStructCount;
    if ((u32) _particleBankStructCount > 0U) {
loop_1:
        if ((u8) *var_r29 == 0) {

        } else {
            var_r29 += 0x14;
            var_ctr -= 1;
            if (var_ctr == 0U) {
                goto block_4;
            }
            goto loop_1;
        }
    } else {
block_4:
        var_r29 = NULL;
    }
    if (var_r29 == NULL) {
        return NULL;
    }
    var_r30 = 0;
loop_16:
    if (var_r30 >= 0x40U) {
        var_r30 = 0xFF;
    } else {
        var_r4 = _particleBankStructList;
        var_ctr_2 = _particleBankStructCount;
        if ((u32) _particleBankStructCount > 0U) {
loop_9:
            if ((u8) M2C_FIELD(var_r4, u8 *, 1) == var_r30) {
                var_r0 = 1;
            } else {
                var_r4 += 0x14;
                var_ctr_2 -= 1;
                if (var_ctr_2 == 0U) {
                    goto block_12;
                }
                goto loop_9;
            }
        } else {
block_12:
            var_r0 = 0;
        }
        if (var_r0) {

        } else {
            var_r30 += 1;
            goto loop_16;
        }
    }
    switch (var_r30) {
    case 0xFF:
            return NULL;
        break;
    }
    M2C_FIELD(var_r29, s32 *, 0x10) = 0;
    M2C_FIELD(var_r29, ModelBank **, 0xC) = NULL;
    M2C_FIELD(var_r29, s8 *, 4) = 0;
    if ((u32) (M2C_FIELD(p0, s32 *, 0) + 0xFE100000) == 0x56DAU) {
        if ((u32) (M2C_FIELD(p0, s32 **, 4) + 0xFFFD0000) != 2U) {
            return NULL;
        }
        M2C_FIELD(var_r29, s8 *, 2) = 1;
        M2C_FIELD(var_r29, s8 *, 3) = 0x10;
        M2C_FIELD(var_r29, ModelBank **, 0xC) = GSmemAllocClr(0x3C0U);
        temp_r4 = M2C_FIELD(var_r29, ModelBank **, 0xC);
        if (temp_r4 == NULL) {
            return NULL;
        }
        M2C_FIELD(temp_r4, s8 *, 0) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x3C) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x78) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0xB4) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0xF0) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x12C) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x168) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x1A4) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x1E0) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x21C) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x258) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x294) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x2D0) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x30C) = 1;
        M2C_FIELD(M2C_FIELD(var_r29, ModelBank **, 0xC), s8 *, 0x348) = 1;
        temp_r4_2 = M2C_FIELD(var_r29, ModelBank **, 0xC);
        M2C_FIELD(temp_r4_2, s8 *, 0x384) = 1;
        M2C_FIELD(var_r29, u8 **, 8) = (unsigned char *)(peBankLoadFile(p0, temp_r4_2));
        if ((u8 *) M2C_FIELD(var_r29, u8 **, 8) != NULL) {
            goto block_38;
        }
        goto block_39;
    }
    M2C_FIELD(var_r29, s8 *, 2) = 0;
    M2C_FIELD(var_r29, s8 *, 3) = 0x40;
    temp_ret = GSmemAllocClr(0xF00U);
    temp_f1 = M2C_BITWISE(f32, temp_ret);
    M2C_FIELD(var_r29, ModelBank **, 0xC) = temp_ret;
    if ((ModelBank *) M2C_FIELD(var_r29, ModelBank **, 0xC) == NULL) {
        return NULL;
    }
    temp_r4_3 = M2C_FIELD(p0, s32 *, 0);
    switch (temp_r4_3) {
    case 0x47505430:
        GSlogWrite((const char*)(&jtbl_1991 + 0x6C), temp_r4_3, temp_f1);
        GSlogWrite((const char*)(&jtbl_1991 + 0xC8));
        GSlogWrite((const char*)(&jtbl_1991 + 0x6C));
block_39:
        temp_r3 = M2C_FIELD(var_r29, ModelBank **, 0xC);
        if (temp_r3 != NULL) {
            GSmemFree((void*)(temp_r3));
            M2C_FIELD(var_r29, ModelBank **, 0xC) = NULL;
        }
        return NULL;
    default:
        GSlogWrite((const char*)(&jtbl_1991 + 0x124), temp_r4_3, temp_f1);
        goto block_39;
    case 0x47505431:
        M2C_FIELD(p0, s32 **, 4) = (s32 *) ((s32)M2C_FIELD(p0, s32 **, 4) + (s32)p0);
        M2C_FIELD(p0, s32 **, 8) = (s32 *) ((s32)M2C_FIELD(p0, s32 **, 8) + (s32)p0);
        M2C_FIELD(p0, u32 **, 0x10) = (u32 *) ((s32)M2C_FIELD(p0, u32 **, 0x10) + (s32)p0);
        temp_r5 = *M2C_FIELD(p0, s32 **, 4);
        if ((s32) temp_r5 != 0x43) {
            GSlogWrite((const char*)(&jtbl_1991 + 0x144), 0x43, temp_r5, temp_f1);
            goto block_39;
        }
        M2C_FIELD(var_r29, u8 **, 8) = (unsigned char *)(p0);
        DCFlushRange((register void*)(M2C_FIELD(p0, s32 **, 8)), (M2C_FIELD(p0, s32 *, 0xC) + 0x1F) & 0xFFFFFFE0);
        psInitDataBank((s32) var_r30, (int*)(M2C_FIELD(p0, s32 **, 4)), (int*)(M2C_FIELD(p0, s32 **, 8)), (u32*)(M2C_FIELD(p0, u32 **, 0x10)), (int*)(NULL));
block_38:
        M2C_FIELD(var_r29, u8 *, 0) = 1;
        M2C_FIELD(var_r29, u8 *, 1) = var_r30;
        return var_r29;
    }
}
}

extern "C" {
#pragma push
#pragma dont_inline on
extern "C" {
#pragma push
#pragma peephole off
void GSparticleInit(u32 p0) {
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r5;
    u32 var_r6;
    u8 *temp_r3;

    sp8 = M2C_FIELD(&jtbl_1991, s32 *, 0);
    spC = M2C_FIELD(&jtbl_1991, s32 *, 4);
    sp10 = M2C_FIELD(&jtbl_1991, s32 *, 8);
    sp14 = M2C_FIELD(&jtbl_1991, s32 *, 0xC);
    sp18 = M2C_FIELD(&jtbl_1991, s32 *, 0x10);
    _particleBankStructList = temp_r3;
    sp1C = M2C_FIELD(&jtbl_1991, s32 *, 0x14);
    sp20 = M2C_FIELD(&jtbl_1991, s32 *, 0x18);
    memset((void*)(g_particle_cameras), 0, 0x10U);
    _particleBankStructCount = p0;
    g_particle_cameras_count = 0;
    temp_r3 = (unsigned char *)(GSmemAlloc(p0 * 0x14));
    if (temp_r3 != NULL) {
        var_r5 = 0;
        var_r6 = 0U;
        while (var_r6 < (u32) _particleBankStructCount) {
            var_r6 += 1;
            _particleBankStructList[var_r5] = 0;
            var_r5 += 0x14;
        }
        psSetToken(0U);
        psInitParticle(0);
        psInitGenerator(0);
        psInitAppSRT(0, 0x74U);
        HSD_JObjSetSPtclCallback((void (*)(s32, s32, s32, HSD_JObj*))(_particleJObjCallback));
        HSD_JObjSetDPtclCallback((DPCtlCallback)((s32) _particleJObjCallback));
        HSD_JObjSetPtclTargetCallback((void (*)(HSD_JObj*, s32))(&psSetPointJObjNodup));
        particleEngineInit();
        GSgfxRenderModuleRegister(0x40U, (GSgfxRenderModule*)((GSgfxRenderModule *) &sp8), (void*)(NULL));
    }
}
#pragma pop
}
#pragma pop
}

}

extern "C" {
extern "C" {
extern "C++" {
static void _particleBankDestroyOldestGenerator(_GSparticleBank* p0) {
    u8 *var_r4;
    s32 var_ctr;
    u32 temp_r0_2;
    u32 var_r7;
    s32 var_r8;
    s32 var_r3;

    var_r7 = -1U;
    var_r8 = -1;
    var_r3 = 0;
    var_r4 = (M2C_FIELD(p0, u8 **, 0xC));
    var_ctr = (M2C_FIELD((s32)p0, u8 *, 3));
    if ((s32) (M2C_FIELD(p0, u8 *, 3)) > 0) {
        do {
            if ((M2C_FIELD(var_r4, u8 **, 0x38)) != NULL) {
                temp_r0_2 = M2C_FIELD((M2C_FIELD(var_r4, u8 **, 0x38)), u32 *, 4);
                if (temp_r0_2 < var_r7) {
                    var_r7 = temp_r0_2;
                    var_r8 = var_r3;
                }
            }
            var_r3 += 1;
            var_r4 += 0x3C;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    if (var_r8 != -1) {
        GSparticleDestroyGenerator((M2C_FIELD(p0, u8 **, 0xC)) + (var_r8 * 0x3C), 1U);
    }
}
}

extern "C++" {
static void _particleJObjCallback(int p0, int p1, int p2, _HSD_JObj* p3) {
    GSpart *temp_r3_4;
    _GSmodel *temp_r3;
    GSparticleGenerator *temp_r3_5;
    GSparticleBank *temp_r3_2;
    _HSD_JObj *var_r0;
    _HSD_JObj *var_r31;
    s32 temp_r3_3;
    u32 temp_r4;
    u8 *temp_r3_6;
    u8 *temp_r3_7;

    var_r31 = p3;
loop_4:
    if (var_r31 == NULL) {
        var_r0 = NULL;
    } else {
        var_r0 = M2C_FIELD(var_r31, _HSD_JObj **, 0xC);
    }
    if (var_r0 != NULL) {
        if (var_r31 == NULL) {
            var_r31 = NULL;
        } else {
            var_r31 = M2C_FIELD(var_r31, _HSD_JObj **, 0xC);
        }
        goto loop_4;
    }
    temp_r3 = GSmodelSearchModelList((HSD_JObj*)((HSD_JObj *) var_r31));
    if (temp_r3 != NULL) {
        temp_r3_2 = (GSparticleBank *)(GSmodelGetLinkedGSparticleBank((_GSmodel*)(temp_r3)));
        if (temp_r3_2 != NULL) {
            u8 cmpv = GSmodelIsRootNullAdded((_GSmodel*)(temp_r3));
            if (cmpv != 0) {
                var_r31 = M2C_FIELD(var_r31, _HSD_JObj **, 0x10);
            }
            temp_r3_3 = GSpartGetJObjIndex(var_r31, p3);
            if ((u32) (temp_r3_3 + 0x10000) != -1U) {
                temp_r3_4 = GSmodelGetPart((_GSmodel*)(temp_r3), temp_r3_3);
                if (temp_r3_4 != NULL) {
                    temp_r3_5 = GSparticleCreateGenerator((GSparticleBank*)(temp_r3_2), p2, 0);
                    if (temp_r3_5 != NULL) {
                        temp_r3_6 = M2C_FIELD(temp_r3_5, u8 **, 0x38);
                        if ((temp_r3_6 != NULL) && ((u8) M2C_FIELD(temp_r3_5, u8 *, 0) == 0)) {
                            psSetParticleTexScaling((PSGenerator*)(M2C_FIELD(temp_r3_6, PSGenerator **, 8)), 1U);
                        }
                        temp_r3_7 = M2C_FIELD(temp_r3_5, u8 **, 0x38);
                        if ((temp_r3_7 != NULL) && ((u8) M2C_FIELD(temp_r3_5, u8 *, 0) == 0)) {
                            psSetRandomVelocityScaling((PSGenerator*)(M2C_FIELD(temp_r3_7, PSGenerator **, 8)), 1U);
                        }
                        GSparticleAttachGeneratorToGSpart(temp_r3_5, temp_r3_4, GSmodelGetGSparticleLinkAttachMode((_GSmodel*)(temp_r3)), 0, 1U, 0U);
                        temp_r4 = GSmodelGetVisibility((_GSmodel*)(temp_r3));
                        if ((M2C_FIELD(temp_r3_5, u8 **, 0x38)) != NULL) {
                            if ((u8) M2C_FIELD(temp_r3_5, u8 *, 0) != 0) {
                                if ((M2C_FIELD(temp_r3_5, u8 **, 0x38)) != NULL) {
                                    if ((u8) temp_r4 != 0) {
                                        M2C_FIELD((M2C_FIELD(temp_r3_5, u8 **, 0x38)), s32 *, 0x134) = (s32) (M2C_FIELD((M2C_FIELD(temp_r3_5, u8 **, 0x38)), s32 *, 0x134) | 4);
                                    } else {
                                        M2C_FIELD((M2C_FIELD(temp_r3_5, u8 **, 0x38)), s32 *, 0x134) = (s32) (M2C_FIELD((M2C_FIELD(temp_r3_5, u8 **, 0x38)), s32 *, 0x134) & 0xFFFFFFFB);
                                    }
                                }
                            } else {
                                psSetParticleVisibility((PSGenerator*)(M2C_FIELD((M2C_FIELD(temp_r3_5, u8 **, 0x38)), PSGenerator **, 8)), (u8) temp_r4);
                            }
                        }
                    }
                    GSpartFree((GSpart*)(temp_r3_4));
                }
            }
        }
    }
}
}
}
}

}
