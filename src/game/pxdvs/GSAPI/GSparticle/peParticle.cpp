// Not yet decompiled.
#include <dolphin/types.h>
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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

// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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

// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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
struct GSbound;
struct GSgfxDL;
struct GSgfxLayer;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxPrimType { GSgfxPrimType_draft_dummy };
struct GSgfxVF;
enum Mtx { Mtx_draft_dummy };
struct Quaternion;
struct Vec;
struct _EmitParams;
struct _peParticle;
struct peColorSpline;
class peContainer;
struct peEmitterNode;
struct peNode;
class peParticleContainer;
struct peParticleNode;
class peRenderContainer;
struct peSpline;

extern "C++" {
// ---- draft declarations ----
struct GSbound {
    u8 _draft[1];
};
struct GSgfxDL {
    u8 _draft[1];
};
struct GSgfxLayer {
    u8 _draft[1];
    s32 dlDraw(GSgfxDL*);
    s32 beginSurface(unsigned short);
    s32 endSurface();
};
struct GSgfxVF {
    u8 data[0x440];
};
struct Quaternion {
    u8 _draft[1];
};
struct Vec {
    f32 x, y, z;
};
struct _EmitParams {
    u8 _draft[1];
};
struct _peParticle {
    u8 _draft[1];
};
struct peColorSpline {
    u8 _draft[1];
};
class peContainer {
public:
    peEmitterNode* emitter;  // 0x00
    u32 unk4;                // 0x04
    void* buffer;            // 0x08
    peNode* freeList;        // 0x0c
    peNode* activeList;      // 0x10
    u16 count;               // 0x14
    u16 maxCount;            // 0x16
    u8 dirty;                // 0x18
    u8 started;              // 0x19

    peContainer(peEmitterNode* e, unsigned long nodeSize, unsigned short max);
    virtual ~peContainer();
    virtual void Start();
    virtual void PreUpdate();
    virtual u16 Emit(unsigned short n) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Stop() = 0;

    static void SetLayerVisibility(GSgfxLayerID, bool);
    s32 RemoveNode(peNode*);
    u16 CreateNodes(unsigned short);
    s32 RemoveAll();
};
struct peEmitterNode {
    u8 _draft[1];
};
struct peNode {
    u8 _draft[1];
    bool Update(peEmitterNode*, float);
    void Start(peEmitterNode*, _EmitParams*);
};
struct peParticleNode {
    u8 _draft[1];
    void UpdateRenderData(peEmitterNode*, _peParticle*, char*, float);
    void Render(_peParticle*, GSgfxDL*, char*);
    static void Start(peEmitterNode*, _peParticle*, GSgfxDL*, _EmitParams*);
};
class peRenderContainer : public peContainer {
public:
    u8 swapPending;  // 0x20
    u8 cur;          // 0x21
    u32 bufSize;     // 0x24
    u8 dl[2][0x10];  // 0x28
    u8* bufA;        // 0x48
    u8* bufB;        // 0x4c
    u16 tokens[2];   // 0x50

    peRenderContainer(peEmitterNode*, unsigned long, unsigned short, GSgfxVF*, GSgfxPrimType, unsigned char, unsigned char, bool);
    virtual ~peRenderContainer();
    virtual void PreUpdate();
    s32 InitSwap();
    s32 ResetSwap();
    s32 MarkForSwap();
    s32 ResolveMultipleSwap();
};
class peParticleContainer : public peRenderContainer {
public:
    peNode** sorted;     // 0x54
    _peParticle* data;   // 0x58
    f32 uv[8];           // 0x5c

    peParticleContainer(peEmitterNode*, _peParticle*, unsigned short);
    virtual ~peParticleContainer();
    virtual void Start();
    virtual u16 Emit(unsigned short);
    virtual void Update(float);
    virtual void Render();
    virtual void Stop();
    void DepthSort();
};
struct peSpline {
    u8 _draft[1];
};

extern "C" {
void C_QUATRotAxisRad(Quaternion* r, const Vec* axis, f32 rad);
asm void DCFlushRange(register void* addr, register u32 nBytes);
int EulerToQuat(Vec* euler, Quaternion* q);
void GSboundAddPoint(GSbound* bound, f32 x, f32 y, f32 z);
void GSgfxVFSetArray(GSgfxVF* vf, s32, s32, void*, s32, s32);
f32 HSD_Randf(void);
asm void PSMTXMultVecSR(const register Mtx m, const register Vec* src, register Vec* dst);
void PSMTXQuat(register Mtx m, const register Quaternion* q);
void PSQUATInverse(const register Quaternion* src, register Quaternion* inv);
void PSQUATMultiply(const register Quaternion* p, const register Quaternion* q, register Quaternion* pq);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
asm void PSVECCrossProduct(const register Vec* a, const register Vec* b, register Vec* axb);
asm f32 PSVECDotProduct(const register Vec* a, const register Vec* b);
void PSVECNormalize(const register Vec* src, register Vec* unit);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double atan2(double y, double x);
double fmod(double x, double y);
s32 particleEngineSetupBlendMode(s32);
s32 particleEngineSetupTevStages(s32, u32, bool);
s32 particleEngineSetupTexture(s32, s32, s8, s32, s32, s32);
void peColorSplineGetValue(u8* out, peColorSpline* s, f32 t);
f32 peSplineGetValue(peSpline* s, f32 t);
extern f32 __float_nan;

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
extern Vec g_CameraLookDir;
extern Vec g_CameraPosition;
struct XdBlobC { u8 data[0xC]; };
extern XdBlobC g_CameraSideDir;
extern Vec g_CameraUpDir;
extern GSbound* g_currentBound;
extern GSgfxLayer* g_current_layer;
extern _EmitParams* g_emitParams;
extern GSgfxVF g_ext_vertex_format;
struct ParticleDebugStats {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
};
extern ParticleDebugStats g_particle_debug_stats;

// From the Dolphin SDK's OSFastCast.h (GQR5 is set up for s16 conversion).
static inline f32 __OSs16tof32(register const s16* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 5 }
    return ret;
}

static inline f32 OSs16tof32(s16 in) {
    s16 tmp = in;
    return __OSs16tof32(&tmp);
}

extern s32 g_render_pass;
extern GSgfxVF g_vertex_format;
extern Vec xAxisVector;
extern Vec yAxisVector;
extern Vec zAxisVector;
extern s32 this_;
}
extern "C++" {
// ---- draft declarations ----



// ---- draft declarations ----



void peParticleContainer::Stop() {
    s16 *var_r7;
    s32 temp_cr0_eq;
    s32 var_r4;
    u32 temp_r30;
    u8 *temp_r8;
    u8 *var_r9;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) != 0) {
        ((peContainer*)this)->PreUpdate();
        M2C_FIELD(this, u8 *, 0x19) = 0U;
        temp_r30 = *M2C_FIELD(this, u32 **, 0x58);
        if (temp_r30 & 0x20000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, false);
        }
        if (temp_r30 & 0x40000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, false);
        }
        if (temp_r30 & 0x80000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, false);
        }
        var_r9 = M2C_FIELD(this, u8 **, 0x10);
        while (var_r9 != NULL) {
            var_r7 = NULL;
            M2C_FIELD(var_r9, s8 *, 0x36) = 0;
            temp_r8 = (unsigned char *)((u8*)this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28));
            if (M2C_FIELD(temp_r8, u16 *, 0) & 1) {
                var_r7 = (short *)(M2C_FIELD(temp_r8, s32 *, 4) + ((((M2C_FIELD(var_r9, u16 *, 0x32) * 4) & 0xFFFC) * M2C_FIELD(temp_r8, u16 *, 2)) + 3));
            }
            var_r4 = 4;
loop_13:
            temp_cr0_eq = var_r4 == 0;
            var_r4 -= 1;
            if (temp_cr0_eq == 0) {
                M2C_FIELD(var_r7, u16 *, 0) = 0xFFFF;
                M2C_FIELD(var_r7, u16 *, 2) = 0xFFFF;
                M2C_FIELD(var_r7, u16 *, 4) = 0xFFFF;
                var_r7 += 6;
                if ((u32) (((u32) *M2C_FIELD(this, u32 **, 0x58) >> 0x19U) & 1) != 0) {
                    *var_r7 = 0xFFFF;
                    var_r7 += 2;
                }
                goto loop_13;
            }
            M2C_FIELD(temp_r8, u16 *, 0) = (u16) (M2C_FIELD(temp_r8, u16 *, 0) | 2);
            var_r9 = M2C_FIELD(var_r9, u8 **, 0x28);
        }
        ((peContainer*)((peContainer *) this))->RemoveAll();
        ((peRenderContainer*)((peRenderContainer *) this))->ResetSwap();
    }
}
}

extern "C++" {
extern "C++" {
extern "C++" {
#pragma optimize_for_size on
#pragma optimize_for_size reset
}

extern "C++" {
void peParticleContainer::Start() {
    s32 temp_r31;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        M2C_FIELD(this, u8 *, 0x19) = 1U;
        temp_r31 = *M2C_FIELD(this, s32 **, 0x58);
        ((peRenderContainer*)((peRenderContainer *) this))->InitSwap();
        if (temp_r31 & 0x20000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, true);
        }
        if (temp_r31 & 0x40000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, true);
        }
        if (temp_r31 & 0x80000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, true);
        }
    }
}
}

extern "C++" {
peParticleContainer::~peParticleContainer() {
    if (sorted != 0) {
        delete[] sorted;
    }
    g_particle_debug_stats.unk4 -= 0x7C;
    g_particle_debug_stats.unk14 -= 0x7C;
}
}

extern "C++" {
extern "C++" {


extern "C++" {
#pragma push
#pragma dont_inline on
extern "C++" {
void peParticleContainer::Update(float p0) {
    peNode *var_r31;
    f32 temp_f31;
    f32 var_f1;
    f32 var_f1_2;
    peEmitterNode *temp_r28;
    peNode *temp_r30;
    _peParticle *temp_r27;
    peSpline *temp_r3;
    s16 *var_r6;
    s32 temp_cr0_eq;
    s8 *temp_r26;
    u32 var_r4;
    u8 var_r0;
    u8 *temp_r7;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) != 0) {
        var_r31 = M2C_FIELD(this, peNode **, 0x10);
        while (var_r31 != NULL) {
            temp_r30 = M2C_FIELD(var_r31, peNode **, 0x28);
            temp_r27 = M2C_FIELD(this, _peParticle **, 0x58);
            temp_r28 = M2C_FIELD(this, peEmitterNode **, 0);
            temp_r26 = (signed char *)&(*(this + ((M2C_FIELD(this, u8 *, 0x21) * 4) + 0x48)));
            if (temp_r26 == NULL) {
                var_r0 = 0;
            } else if (((peNode*)(var_r31))->Update((peEmitterNode*)(temp_r28), p0) == 0) {
                var_r0 = 0;
            } else {
                temp_f31 = 1.0f - (M2C_FIELD(var_r31, f32 *, 4) / M2C_FIELD(var_r31, f32 *, 0));
                if (M2C_FIELD(temp_r27, s32 *, 0) & 0x10000) {
                    temp_r3 = M2C_FIELD(temp_r27, peSpline **, 0x34);
                    if ((temp_r3 == NULL) || !(M2C_FIELD(temp_r3, u8 *, 0) & 3)) {
                        var_f1 = 1.0f;
                    } else {
                        var_f1_2 = M2C_FIELD(temp_r3, f32 *, 8) - temp_f31;
                        if (var_f1_2 < 0.0f) {
                            var_f1_2 = -var_f1_2;
                        }
                        if (var_f1_2 <= 0.00001f) {
                            var_f1 = M2C_FIELD(temp_r3, f32 *, 4);
                        } else {
                            var_f1 = peSplineGetValue((peSpline*)(temp_r3), temp_f31);
                        }
                    }
                    M2C_FIELD(var_r31, f32 *, 0x44) = (f32) (M2C_FIELD(temp_r27, f32 *, 0x24) * var_f1);
                }
                M2C_FIELD(var_r31, f32 *, 0x44) = (f32) ((M2C_FIELD(var_r31, f32 *, 0x48) * p0) + M2C_FIELD(var_r31, f32 *, 0x44));
                ((peParticleNode*)((peParticleNode *) var_r31))->UpdateRenderData((peEmitterNode*)(temp_r28), (_peParticle*)(temp_r27), (char*)(temp_r26), temp_f31);
                var_r0 = 1;
            }
            switch (var_r0) {
            case 0:
                    var_r6 = NULL;
                    M2C_FIELD(var_r31, s8 *, 0x36) = 0;
                    temp_r7 = (unsigned char *)(this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28));
                    if (M2C_FIELD(temp_r7, u16 *, 0) & 1) {
                        var_r6 = (short *)(M2C_FIELD(temp_r7, s32 *, 4) + ((((M2C_FIELD(var_r31, u16 *, 0x32) * 4) & 0xFFFC) * M2C_FIELD(temp_r7, u16 *, 2)) + 3));
                    }
                    var_r4 = 4;
    loop_23:
                    temp_cr0_eq = var_r4 == 0;
                    var_r4 -= 1;
                    switch (temp_cr0_eq) {
                    case 0:
                            M2C_FIELD(var_r6, s16 *, 0) = 0xFFFF;
                            M2C_FIELD((u16)var_r6, s16 *, 2) = 0xFFFF;
                            M2C_FIELD(var_r6, s16 *, 4) = 0xFFFF;
                            var_r6 += 6;
                            if ((u32) (((u32) M2C_FIELD(M2C_FIELD(this, _peParticle **, 0x58), u32 *, 0) >> 0x19U) & 1) != 0) {
                                *var_r6 = 0xFFFF;
                                var_r6 += 2;
                            }
                            goto loop_23;
                        break;
                    }
                    M2C_FIELD(temp_r7, u16 *, 0) = (u16) (M2C_FIELD(temp_r7, u16 *, 0) | 2);
                    ((peContainer*)((peContainer *) this))->RemoveNode((peNode*)(var_r31));
                break;
            }
            var_r31 = temp_r30;
        }
        ((peParticleContainer*)(this))->DepthSort();
    }
}
}

#pragma pop
}
extern "C++" {

extern "C++" {
#pragma push
#pragma optimize_for_size on
void peParticleContainer::DepthSort() {
    enum TsE { TsE0 };
    f32 temp_f0;
    f32 temp_f1;
    s16 temp_r7;
    s16 temp_r7_2;
    s32 temp_r0;
    s32 temp_r8_2;
    enum TsE temp_r8_3;
    s32 var_r11;
    s32 var_r12;
    s32 var_r4_2;
    s32 var_r5;
    s32 var_r6;
    s32 var_r8;
    u16 temp_r8;
    u16 var_r9;
    u32 temp_r0_2;
    u32 temp_r9;
    u8 var_r0;
    u8 var_r31;
    u8 *temp_r10;
    u8 *temp_r5;
    u8 *temp_r5_2;
    u8 *temp_r6;
    u8 *temp_r9_2;
    u8 *var_r11_2;
    u8 *var_r4;

    if (((u8) M2C_FIELD(this, u8 *, 0x19) != 0) && (*M2C_FIELD(this, u32 **, 0x58) & 0x80000) && ((u16) M2C_FIELD(this, u16 *, 0x14) >= 2U) && ((u32) M2C_FIELD(this, u32 *, 0x54) != 0U)) {
        var_r31 = 0;
        var_r11 = 1;
        var_r8 = 4;
        while (var_r11 < (s32) M2C_FIELD(this, u16 *, 0x16)) {
            temp_r10 = (unsigned char *)(*(M2C_FIELD(this, u32 **, 0x54) + var_r8));
            if ((u8) M2C_FIELD(temp_r10, u8 *, 0x36) != 0) {
                var_r12 = var_r11;
loop_14:
                temp_r9 = M2C_FIELD(this, u32 *, 0x54);
                var_r6 = var_r12;
                if (temp_r9 == 0U) {
                    var_r6 = -1;
                } else {
                    var_r4 = (unsigned char *)(temp_r9 + (var_r12 * 4));
loop_19:
                    if (var_r6 <= 0) {
                        var_r6 = -1;
                    } else {
                        temp_r5 = M2C_FIELD(var_r4, u8 **, -4);
                        var_r4 = var_r4 - 4;
                        var_r6 = var_r6 - 1;
                        if ((u8) M2C_FIELD(temp_r5, u8 *, 0x36) != 0) {

                        } else {
                            goto loop_19;
                        }
                    }
                }
                if (var_r6 >= 0) {
                    temp_f0 = M2C_FIELD(temp_r10, f32 *, 0x4C);
                    temp_r5_2 = (unsigned char *)(*((u8 *)temp_r9 + (var_r6 * 4)));
                    temp_f1 = M2C_FIELD(temp_r5_2, f32 *, 0x4C);
                    if (temp_f1 == temp_f0) {
                        var_r0 = 0;
                    } else if ((u16) M2C_FIELD(temp_r5_2, u16 *, 0x32) < (u16) M2C_FIELD(temp_r10, u16 *, 0x32)) {
                        var_r0 = temp_f1 < temp_f0;
                    } else {
                        var_r0 = temp_f1 > temp_f0;
                    }
                    if (var_r0 != 0) {
                        temp_r0 = var_r12;
                        temp_r0 *= 4;
                        var_r12 = var_r6;
                        *((u8 *)temp_r9 + temp_r0) = (unsigned char)(temp_r5_2);
                        var_r31 = 1;
                        goto loop_14;
                    }
                }
                *((u8 *)temp_r9 + (var_r12 * 4)) = (unsigned char)(temp_r10);
            }
            var_r8 = var_r8 + 4;
            var_r11 = var_r11 + 1;
        }
        if (var_r31 != 0) {
            var_r5 = 0;
            var_r4_2 = 0;
            temp_r0_2 = ((u32) *M2C_FIELD(this, u32 **, 0x58) >> 0x19U) & 1;
            temp_r6 = (unsigned char *)((u8*)this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28));
            while (var_r5 < (s32) M2C_FIELD(this, u16 *, 0x16)) {
                temp_r9_2 = (unsigned char *)(*(M2C_FIELD(this, u32 **, 0x54) + var_r4_2));
                if (((u8) M2C_FIELD(temp_r9_2, u8 *, 0x36) != 0) && ((u16) M2C_FIELD(temp_r9_2, u16 *, 0x32) != (u16) var_r5)) {
                    M2C_FIELD(temp_r9_2, u16 *, 0x32) = (u16) var_r5;
                    temp_r8 = M2C_FIELD(temp_r9_2, u16 *, 0x30) * (u16) ((temp_r0_2 != 0) + 0xD);
                    if (M2C_FIELD(temp_r6, u16 *, 0) & 1) {
                        var_r11_2 = (unsigned char *)(M2C_FIELD(temp_r6, s32 *, 4) + ((((var_r5 * 4) & 0xFFFC) * M2C_FIELD(temp_r6, u16 *, 2)) + 3));
                    } else {
                        var_r11_2 = NULL;
                    }
                    var_r9 = 0;
                    if (temp_r0_2 != 0) {
                        while (var_r9 < 4U) {
                            temp_r7 = (var_r9 * 2) & 0xFFFE;
                            temp_r8_2 = var_r9 * 3;
                            var_r9 = var_r9 + 1;
                            M2C_FIELD(var_r11_2, s16 *, 0) = (s16) (temp_r8 + temp_r8_2);
                            M2C_FIELD(var_r11_2, u16 *, 2) = temp_r8;
                            M2C_FIELD(var_r11_2, u16 *, 4) = temp_r8;
                            M2C_FIELD(var_r11_2, s16 *, 6) = temp_r7;
                            var_r11_2 = var_r11_2 + 8;
                        }
                    } else {
                        while (var_r9 < 4U) {
                            temp_r7_2 = (var_r9 * 2) & 0xFFFE;
                            temp_r8_3 = (enum TsE)(var_r9 * 3);
                            var_r9 = var_r9 + 1;
                            M2C_FIELD(var_r11_2, s16 *, 0) = (s16) (temp_r8 + temp_r8_3);
                            M2C_FIELD(var_r11_2, u16 *, 2) = temp_r8;
                            M2C_FIELD(var_r11_2, s16 *, 4) = temp_r7_2;
                            var_r11_2 = var_r11_2 + 6;
                        }
                    }
                }
                var_r4_2 = var_r4_2 + 4;
                var_r5 = var_r5 + 1;
            }
            M2C_FIELD(temp_r6, u16 *, 0) = (u16) (M2C_FIELD(temp_r6, u16 *, 0) | 2);
            M2C_FIELD(this, s8 *, 0x18) = 1;
        }
    }
}
#pragma pop
}

extern "C++" {
static inline void setCull(GSgfxLayer* layer, s32 mode) {
    M2C_FIELD(layer, s32 *, 0xD8C) = mode;
    M2C_FIELD(layer, s32 *, 0x16B8) |= 2;
    M2C_FIELD(layer, s32 *, 0x16A8) |= 2;
    M2C_FIELD(layer, s32 *, 0x1770) |= 2;
    M2C_FIELD(layer, s32 *, 0x1760) |= 2;
}

static inline bool canRender(peParticleContainer* c) {
    if (!c->started) {
        return false;
    }
    if (c->count == 0) {
        return false;
    }
    if (g_render_pass != 1) {
        return false;
    }
    u32 flags = *(u32*)c->data;
    switch (M2C_FIELD(g_current_layer, s32 *, 0x28)) {
    case 0:
        if (flags & 0x08000000) {
            return true;
        }
        break;
    case 2:
        if (flags & 0x10000000) {
            return true;
        }
        if (!(flags & 0xF8000800)) {
            return true;
        }
        break;
    case 4:
        if (flags & 0x800) {
            return true;
        }
        break;
    case 1:
        if (flags & 0x20000000) {
            return true;
        }
        break;
    case 3:
        if (flags & 0x40000000) {
            return true;
        }
        break;
    case 5:
        if (flags & 0x80000000) {
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}

void peParticleContainer::Render() {
    if (started) {
        if (canRender(this)) {
            ResolveMultipleSwap();
            u32 flags = *(u32*)data;
            u32 tex = (flags >> 25) & 1;
            if (flags & 0x200) {
                setCull(g_current_layer, 2);
            } else {
                setCull(g_current_layer, 0);
            }
            particleEngineSetupBlendMode(flags & 7);
            GSgfxVF* vf;
            u8* dlp = dl[cur];
            u8* buf = (&bufA)[cur];
            if (*(u16*)dlp & 1) {
                vf = *(GSgfxVF**)(dlp + 0xC);
            } else {
                vf = 0;
            }
            if (tex) {
                GSgfxVFSetArray(vf, 9, 3, buf, 4, bufSize);
                GSgfxVFSetArray(vf, 0xB, 3, buf + 0x30, 4, bufSize);
                GSgfxVFSetArray(vf, 0xC, 3, buf + 0x34, 4, bufSize);
                GSgfxVFSetArray(vf, 0xD, 3, uv, 4, 0x20);
            } else {
                GSgfxVFSetArray(vf, 9, 3, buf, 4, bufSize);
                GSgfxVFSetArray(vf, 0xB, 3, buf + 0x30, 4, bufSize);
                GSgfxVFSetArray(vf, 0xD, 3, uv, 4, 0x20);
            }
            if (flags & 0x100000) {
                particleEngineSetupTevStages(0, tex, (flags & 0xC00000) == 0xC00000);
                M2C_FIELD(g_current_layer, s32 *, 0x1998) = 0x80;
                M2C_FIELD(g_current_layer, GSgfxVF **, 0x199C) = vf;
                for (peNode* n = activeList; n != 0; n = M2C_FIELD(n, peNode **, 0x28)) {
                    ((peParticleNode*)n)->Render(data, (GSgfxDL*)dl[cur], (char*)(&bufA)[cur]);
                }
            } else {
                particleEngineSetupTevStages(0, tex, 0);
                s32 wrapT = 0;
                if (flags & 0x100) {
                    wrapT = 2;
                }
                s32 wrapS = 0;
                u16 tmp1 = M2C_FIELD(data, s32 *, 0x54);
                particleEngineSetupTexture(0, tmp1, (flags >> 12) & 3, (flags >> 14) & 3, wrapS, (u16)wrapT);
                wrapS = !(flags & 0x80) ? wrapS : 2;
                g_current_layer->dlDraw((GSgfxDL*)dl[cur]);
            }
            MarkForSwap();
        }
    }
}
#pragma push
#pragma dont_inline on
extern "C++" {
u16 peParticleContainer::Emit(unsigned short count) {
    _EmitParams *var_r30;
    peParticleNode *temp_r29;
    peParticleNode *var_r3;
    u16 temp_r28;
    u16 var_r31;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        return 0U;
    }
    var_r31 = ((peContainer*)this)->CreateNodes(count);
    var_r30 = g_emitParams;
    var_r3 = M2C_FIELD(this, peParticleNode **, 0x10);
    temp_r28 = var_r31;
    while (var_r31 != 0) {
        temp_r29 = M2C_FIELD(var_r3, peParticleNode **, 0x28);
        ((peParticleNode*)(var_r3))->Start((peEmitterNode*)(M2C_FIELD(this, peEmitterNode **, 0)), (_peParticle*)(M2C_FIELD(this, _peParticle **, 0x58)), (GSgfxDL*)(count + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28)), (_EmitParams*)(var_r30));
        var_r3 = temp_r29;
        var_r31 -= 1;
        var_r30 += 0x48;
    }
    return temp_r28;
}
}

extern "C++" {
#pragma push
#pragma dont_inline off
peParticleContainer::peParticleContainer(peEmitterNode* p0, _peParticle* p1, unsigned short p2)
    : peRenderContainer(p0, 0x50, p2, (*(u32*)p1 & 0x02000000) ? &g_ext_vertex_format : &g_vertex_format, (GSgfxPrimType)0x80, 4,
                        (*(u32*)p1 & 0x02000000) ? 0x38 : 0x34, (*(u32*)p1 >> 26) & 1) {
    peNode* node;
    u16 i;
    f32 u0;
    f32 v0;
    f32 u1;
    f32 v1;
    f32 scale = 0.0009765625f;

    *sorted = 0;
    data = p1;
    u0 = OSs16tof32(M2C_FIELD(data, s16 *, 0x44)) * scale;
    v0 = OSs16tof32(M2C_FIELD(data, s16 *, 0x46)) * scale;
    u1 = OSs16tof32(M2C_FIELD(data, s16 *, 0x48)) * scale;
    v1 = OSs16tof32(M2C_FIELD(data, s16 *, 0x4A)) * scale;
    uv[0] = u1;
    uv[1] = v1;
    uv[2] = u0;
    uv[3] = v1;
    uv[4] = u0;
    uv[5] = v0;
    uv[6] = u1;
    uv[7] = v0;
    DCFlushRange(uv, 0x20);
    if (*(u32*)data & 0x80000) {
        sorted = new peNode*[p2];
    }
    for (node = freeList, i = 0; node != 0; node = M2C_FIELD(node, peNode **, 0x28), i++) {
        M2C_FIELD(node, u16 *, 0x30) = i;
        M2C_FIELD(node, u16 *, 0x32) = i;
        if (sorted != 0) {
            sorted[i] = node;
        }
    }
    g_particle_debug_stats.unk4 += 0x7C;
    g_particle_debug_stats.unk14 += 0x7C;
}
#pragma pop
}

extern "C++" {
void peParticleNode::Render(_peParticle* p0, GSgfxDL* p1, char* p2) {
    s32 sp10;
    s32 sp14;
    s32 unksp21;
    s32 unksp22;
    s32 unksp23;
    u8 sp27;
    u8 sp26;
    u8 sp25;
    u8 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s16 spC;
    s16 spA;
    u16 sp8;
    f32 temp_f1;
    f32 temp_f30;
    f32 var_f1;
    f32 var_f2;
    s32 *temp_r30;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    s32 var_r7;
    s32 var_r7_2;
    s32 var_r8;
    s32 var_r8_2;
    u16 temp_r0;
    u16 temp_r0_2;
    u16 var_r4;
    u32 temp_r24;
    u32 temp_r29;
    u32 temp_r31;
    u8 var_r28;
    u8 *var_r5;

    temp_r31 = M2C_FIELD(p0, u32 *, 0);
    temp_r30 = M2C_FIELD(p0, s32 **, 0x54);
    var_r28 = M2C_FIELD(this, u8 *, 0x34);
    temp_r29 = (temp_r31 >> 0x19U) & 1;
    if ((p2 != NULL) && ((s32) (M2C_FIELD(p1, u16 *, 0) & 1) == 1)) {
        if (temp_r31 & 0x400000) {
            spC = (s16) *temp_r30;
            temp_f1 = M2C_ERROR(/* psq_l unimplemented */);
            temp_r24 = (temp_r31 >> 0x17U) & 1;
            var_f2 = temp_f1;
            if (temp_r24 != 0) {
                var_f2 = temp_f1 - 1.0f;
            }
            if (temp_r31 & 0x01000000) {
                var_f1 = (var_f2 * (M2C_FIELD(this, f32 *, 0) - M2C_FIELD(this, f32 *, 4))) / M2C_FIELD(p0, f32 *, 0x30);
            } else {
                var_f1 = M2C_FIELD(p0, f32 *, 0x30) * (var_f2 * (1.0f - (M2C_FIELD(this, f32 *, 4) / M2C_FIELD(this, f32 *, 0))));
            }
            spA = (s16) var_r28;
            temp_f30 = (f32) fmod((f64) (var_f1 + M2C_ERROR(/* psq_l unimplemented */)), (f64) var_f2);
            var_r28 = (u8) (u16) (sp14 % (u16) *temp_r30);
            if (temp_r24 != 0) {
                sp8 = (u16) var_r28;
                sp27 = sp10;
                sp26 = sp10;
                sp25 = sp10;
                sp24 = sp10;
                M2C_FIELD(g_current_layer, s32 *, 0x14F4) = (s32) sp24;
                sp1C = (s32) sp24;
                M2C_FIELD(g_current_layer, s32 *, 0x16F8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16F8) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x10);
                M2C_FIELD(g_current_layer, s32 *, 0x17B0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17B0) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x10);
                if (temp_r29 != 0) {
                    sp20 = M2C_FIELD((p2 + (M2C_FIELD(this, u16 *, 0x30) * 0x38)), s32 *, 0x34);
                    sp24 = (u8) sp20;
                    sp25 = unksp21;
                    sp26 = unksp22;
                    sp27 = unksp23;
                    M2C_FIELD(g_current_layer, s32 *, 0x14F8) = (s32) sp24;
                    sp18 = (s32) sp24;
                    M2C_FIELD(g_current_layer, s32 *, 0x16F8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16F8) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x10);
                    M2C_FIELD(g_current_layer, s32 *, 0x17B0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17B0) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x10);
                }
                var_r8 = 0;
                var_r8 = !(temp_r31 & 0x100) ? var_r8 : 2;
                var_r7 = 0;
                if (temp_r31 & 0x80) {
                    var_r7 = 2;
                }
                particleEngineSetupTexture(1, M2C_FIELD((temp_r30 + ((var_r28 * 4) & 0x3FFFC)), s32 *, 8), (temp_r31 >> 0xCU) & 3, (temp_r31 >> 0xEU) & 3, var_r7, var_r8);
            }
        }
        var_r8_2 = 0;
        var_r8_2 = !(temp_r31 & 0x100) ? var_r8_2 : 2;
        var_r7_2 = 0;
        if (temp_r31 & 0x80) {
            var_r7_2 = 2;
        }
        particleEngineSetupTexture(0, M2C_FIELD((temp_r30 + ((var_r28 * 4) & 0x3FFFC)), s32 *, 4), (temp_r31 >> 0xCU) & 3, (temp_r31 >> 0xEU) & 3, var_r7_2, var_r8_2);
        ((GSgfxLayer*)(g_current_layer))->beginSurface(4U);
        if (M2C_FIELD(p1, u16 *, 0) & 1) {
            var_r5 = (unsigned char *)(M2C_FIELD(p1, s32 *, 4) + ((((M2C_FIELD(this, u16 *, 0x32) * 4) & 0xFFFC) * M2C_FIELD(p1, u16 *, 2)) + 3));
        } else {
            var_r5 = NULL;
        }
        var_r4 = 4;
        if (temp_r29 != 0) {
loop_26:
            temp_cr0_eq = var_r4 == 0;
            var_r4 -= 1;
            switch (temp_cr0_eq) {
            case 0:
                    *(u16 *)0xCC008000 = M2C_FIELD(var_r5, u16 *, 0);
                    *(u16 *)0xCC008000 = M2C_FIELD(var_r5, u16 *, 2);
                    *(u16 *)0xCC008000 = M2C_FIELD(var_r5, u16 *, 4);
                    temp_r0 = M2C_FIELD(var_r5, u16 *, 6);
                    var_r5 += 8;
                    *(u16 *)0xCC008000 = temp_r0;
                    goto loop_26;
                break;
            }
        } else {
loop_30:
            temp_cr0_eq_2 = var_r4 == 0;
            var_r4 -= 1;
            switch (temp_cr0_eq_2) {
            case 0:
                    *(u16 *)0xCC008000 = M2C_FIELD(var_r5, u16 *, 0);
                    *(u16 *)0xCC008000 = M2C_FIELD(var_r5, u16 *, 2);
                    temp_r0_2 = M2C_FIELD(var_r5, u16 *, 4);
                    var_r5 += 6;
                    *(u16 *)0xCC008000 = temp_r0_2;
                    goto loop_30;
                break;
            }
        }
        ((GSgfxLayer*)(g_current_layer))->endSurface();
    }
}
}
#pragma pop
}
void peParticleNode::Start(peEmitterNode* p0, _peParticle* p1, GSgfxDL* p2, _EmitParams* p3) {
    s32 spC;
    s16 sp8;
    f32 temp_f1;
    s16 temp_r0;
    s16 temp_r0_2;
    s32 temp_r3;
    s32 temp_r3_2;
    u16 temp_r4;
    u16 var_r7;
    u32 temp_r28;
    u32 temp_r31;
    u8 *var_r5;

    temp_r28 = M2C_FIELD(p2, u32 *, 0);
    temp_r31 = (temp_r28 >> 0x19U) & 1;
    if ((s32) (M2C_FIELD(p3, u16 *, 0) & 1) == 1) {
        ((peNode*)((peNode *) p0))->Start((peEmitterNode*)((peEmitterNode *) p1), (_EmitParams*)(M2C_ERROR(/* Read from unset register $r7 */)));
        M2C_FIELD(p0, u8 *, 0x35) = 0U;
        M2C_FIELD(p0, s8 *, 0x36) = 1;
        temp_f1 = HSD_Randf();
        M2C_FIELD(p0, f32 *, 0x38) = (f32) (M2C_FIELD(p2, f32 *, 0xC) * temp_f1);
        M2C_FIELD(p0, f32 *, 0x3C) = (f32) (M2C_FIELD(p2, f32 *, 0x10) * temp_f1);
        M2C_FIELD(p0, f32 *, 0x38) = (f32) (M2C_FIELD(p0, f32 *, 0x38) + M2C_FIELD(p2, f32 *, 4));
        M2C_FIELD(p0, f32 *, 0x3C) = (f32) (M2C_FIELD(p0, f32 *, 0x3C) + M2C_FIELD(p2, f32 *, 8));
        if (temp_r28 & 0x40) {
            M2C_FIELD(p0, f32 *, 0x40) = (f32) (6.2831855f * HSD_Randf());
        } else {
            M2C_FIELD(p0, f32 *, 0x40) = 0.0f;
        }
        if ((temp_r28 & 0x20) && (HSD_Randf() < 0.5f)) {
            M2C_FIELD(p0, u8 *, 0x35) = (u8) (M2C_FIELD(p0, u8 *, 0x35) | 1);
        }
        M2C_FIELD(p0, f32 *, 0x44) = (f32) M2C_FIELD(p2, f32 *, 0x24);
        M2C_FIELD(p0, f32 *, 0x48) = (f32) ((M2C_FIELD(p2, f32 *, 0x2C) * HSD_Randf()) + M2C_FIELD(p2, f32 *, 0x28));
        if ((u32) ((temp_r28 & 0x300000) + 0xFFD00000) == 0U) {
            sp8 = (s16) *M2C_FIELD(p2, s32 **, 0x54);
            HSD_Randf();
            M2C_FIELD(p0, u8 *, 0x34) = spC;
        } else {
            M2C_FIELD(p0, u8 *, 0x34) = 0U;
        }
        temp_r4 = (u8) ((temp_r31 != 0) + 0xD);
        temp_r4 *= M2C_FIELD(p0, u16 *, 0x30);
        if (M2C_FIELD(p3, u16 *, 0) & 1) {
            var_r5 = (unsigned char *)(M2C_FIELD(p3, s32 *, 4) + ((((M2C_FIELD(p0, u16 *, 0x32) * 4) & 0xFFFC) * M2C_FIELD(p3, u16 *, 2)) + 3));
        } else {
            var_r5 = NULL;
        }
        var_r7 = 0;
        if (temp_r31 != 0) {
            while (var_r7 < 4U) {
                temp_r0 = (var_r7 * 2) & 0xFFFE;
                temp_r3 = var_r7 * 3;
                var_r7 += 1;
                M2C_FIELD(var_r5, s16 *, 0) = (s16) (temp_r4 + temp_r3);
                M2C_FIELD(var_r5, u16 *, 2) = temp_r4;
                M2C_FIELD(var_r5, u16 *, 4) = temp_r4;
                M2C_FIELD(var_r5, s16 *, 6) = temp_r0;
                var_r5 += 8;
            }
        } else {
            while (var_r7 < 4U) {
                temp_r0_2 = (var_r7 * 2) & 0xFFFE;
                temp_r3_2 = var_r7 * 3;
                var_r7 += 1;
                M2C_FIELD(var_r5, s16 *, 0) = (s16) (temp_r4 + temp_r3_2);
                M2C_FIELD(var_r5, u16 *, 2) = temp_r4;
                M2C_FIELD(var_r5, s16 *, 4) = temp_r0_2;
                var_r5 += 6;
            }
        }
        M2C_FIELD(p3, u16 *, 0) = (u16) (M2C_FIELD(p3, u16 *, 0) | 2);
    }
}
}

}

extern "C++" {
extern "C++" {
void peParticleNode::UpdateRenderData(peEmitterNode* p0, _peParticle* p1, char* p2, float p3) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp48;
    s32 sp4C;
    s32 sp54;
    s32 sp58;
    u32 temp_r29;
    s32 sp64;
    s32 sp6C;
    s32 sp70;
    s32 sp78;
    s32 sp7C;
    f32 sp84;
    f32 sp88;
    f32 sp90;
    f32 sp94;
    s32 spA8;
    s32 spAC;
    s32 spC;
    s32 spC0;
    s32 spC4;
    s32 spCC;
    s32 spD0;
    s32 spD8;
    s32 spDC;
    s32 spE4;
    s32 spE8;
    f32 unksp130;
    f32 unksp140;
    s32 unksp24;
    s32 unksp34;
    s32 unksp44;
    s32 unksp50;
    s32 unksp5C;
    f32 unksp68;
    f32 unksp74;
    f32 unksp80;
    f32 unksp8C;
    s32 v98[3];
    s32 unkspA4;
    s32 vB0[3];
    s32 unkspBC;
    s32 unkspC8;
    s32 unkspD4;
    s32 unkspE0;
    s32 sp438;
    s32 sp408;
    s32 sp3D8;
    s32 sp3A8;
    s32 sp378;
    s32 sp348;
    s32 sp318;
    s32 sp2E8;
    s32 sp2B8;
    s32 sp288;
    s32 sp258;
    s32 sp228;
    s32 sp1F8;
    s32 sp1C8;
    s32 sp198;
    f32 sp194;
    f32 sp190;
    f32 sp18C;
    f32 sp188;
    f32 sp184;
    f32 sp180;
    f32 sp17C;
    f32 sp178;
    f32 sp174;
    f32 sp170;
    f32 sp16C;
    f32 sp168;
    f32 sp164;
    f32 sp160;
    f32 sp15C;
    f32 sp158;
    f32 sp154;
    f32 sp150;
    f32 sp12C;
    f32 sp128;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    u8 sp23;
    u8 sp22;
    u8 sp21;
    u8 sp20;
    f32 sp1C;
    u8 spA;
    u8 sp9;
    u8 sp8;
    Vec *temp_r5;
    Vec *temp_r5_2;
    Vec *temp_r5_3;
    f32 temp_f1_4;
    f32 temp_f25;
    f32 temp_f26;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f1_6;
    f32 var_f1_7;
    f32 var_f25;
    f32 var_f25_2;
    f32 var_f2;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;
    peSpline *temp_r3_2;
    peSpline *temp_r3_3;
    peSpline *temp_r3_4;
    s32 temp_r3;
    s32 var_r0;
    u32 temp_r25;
    u32 temp_r27;
    u32 temp_r27_2;
    s32 sp60;
    u8 *var_r26;

    temp_r5 = M2C_FIELD(this, Vec **, 0x20);
    temp_r27 = M2C_FIELD(p1, u32 *, 0);
    temp_r29 = (temp_r27 >> 0x19U) & 1;
    sp154 = M2C_FIELD(this, f32 *, 0xC) * M2C_FIELD(temp_r5, f32 *, 0x20);
    sp158 = M2C_FIELD(this, f32 *, 0x10) * M2C_FIELD(temp_r5, f32 *, 0x24);
    sp150 = M2C_FIELD(this, f32 *, 8) * M2C_FIELD(temp_r5, f32 *, 0x1C);
    PSMTXQuat((Mtx)((s32) &sp438), (const Quaternion *)((const register Quaternion*)(((u8*)(temp_r5) + 0xC))));
    PSMTXMultVecSR((const Mtx)((s32) &sp438), (const Vec *)((const register Vec*)((Vec *) &sp150)), (Vec *)((register Vec*)((Vec *) &sp150)));
    PSVECAdd((const register Vec*)((Vec *) &sp150), (const register Vec*)(M2C_FIELD(this, Vec **, 0x20)), (register Vec*)((Vec *) &sp150));
    if (temp_r27 & 0x200) {
        if (temp_r27 & 0x20000) {
            PSVECSubtract((const register Vec*)(&g_CameraPosition), (const register Vec*)((Vec *) &sp150), (register Vec*)(&unkspD4));
            sp174 = unkspD4;
            sp178 = spD8;
            sp17C = spDC;
            PSVECNormalize((const register Vec*)((Vec *) &sp174), (register Vec*)((Vec *) &sp174));
            PSVECCrossProduct((const register Vec*)((Vec *) &sp174), (const register Vec*)(&g_CameraUpDir), (register Vec*)(&unkspC8));
            sp18C = unkspC8;
            sp190 = spCC;
            sp194 = spD0;
            PSVECNormalize((const register Vec*)((Vec *) &sp18C), (register Vec*)((Vec *) &sp18C));
            if (temp_r27 & 0x400) {
                sp178 = 0.0f;
                PSVECNormalize((const register Vec*)((Vec *) &sp174), (register Vec*)((Vec *) &sp174));
                sp180 = 0.0f;
                sp184 = 1.0f;
                sp188 = 0.0f;
            } else {
                PSVECCrossProduct((const register Vec*)((Vec *) &sp18C), (const register Vec*)((Vec *) &sp174), (register Vec*)(&unkspBC));
                sp180 = unkspBC;
                sp184 = spC0;
                sp188 = spC4;
            }
        } else {
            if (temp_r27 & 0x400) {
                sp180 = M2C_FIELD(&yAxisVector, f32 *, 0);
                sp184 = M2C_FIELD(&yAxisVector, f32 *, 4);
                sp188 = M2C_FIELD(&yAxisVector, f32 *, 8);
            } else {
                sp180 = M2C_FIELD(&g_CameraUpDir, f32 *, 0);
                sp184 = M2C_FIELD(&g_CameraUpDir, f32 *, 4);
                sp188 = M2C_FIELD(&g_CameraUpDir, f32 *, 8);
            }
            sp18C = M2C_FIELD(&g_CameraSideDir, f32 *, 0);
            sp190 = M2C_FIELD(&g_CameraSideDir, f32 *, 4);
            sp194 = M2C_FIELD(&g_CameraSideDir, f32 *, 8);
        }
        var_f25 = M2C_FIELD(p1, f32 *, 0x4C);
    } else {
        C_QUATRotAxisRad((Quaternion*)(&unksp140), (const Vec*)(&yAxisVector), M2C_FIELD(p1, f32 *, 0x4C));
        C_QUATRotAxisRad((Quaternion*)(&unksp130), (const Vec*)(&zAxisVector), M2C_FIELD(p1, f32 *, 0x50));
        PSQUATMultiply((const register Quaternion*)(&unksp130), (const register Quaternion*)(&unksp140), (register Quaternion*)(&unksp130));
        PSMTXQuat((Mtx)((s32) &sp228), (const Quaternion *)((const register Quaternion*)(&unksp130)));
        PSMTXMultVecSR((const Mtx)((s32) &sp228), (const Vec *)((const register Vec*)(&xAxisVector)), (Vec *)((register Vec*)(vB0)));
        sp18C = vB0[0];
        sp190 = vB0[1];
        sp194 = vB0[2];
        PSMTXQuat((Mtx)((s32) &sp1F8), (const Quaternion *)((const register Quaternion*)(&unksp130)));
        PSMTXMultVecSR((const Mtx)((s32) &sp1F8), (const Vec *)((const register Vec*)(&yAxisVector)), (Vec *)((register Vec*)(&unkspA4)));
        sp180 = unkspA4;
        sp184 = spA8;
        sp188 = spAC;
        if (*M2C_FIELD(p0, s32 **, 0xFC) & 0x400) {
            temp_f25 = M2C_FIELD(this, f32 *, 0x1C);
            temp_f26 = M2C_FIELD(this, f32 *, 0x14);
            var_f2 = (temp_f26 * temp_f26) + (temp_f25 * temp_f25);
            var_f2 = sqrtf(var_f2);
            sp124 = (f32) atan2(-M2C_FIELD(this, f32 *, 0x18), (f64) var_f2);
            temp_f1_4 = (f32) atan2((f64) temp_f26, (f64) temp_f25);
            sp12C = 0.0f;
            sp128 = temp_f1_4;
            EulerToQuat((Vec*)((Vec *) &sp124), (Quaternion*)(&unksp140));
            PSMTXQuat((Mtx)((s32) &sp408), (const Quaternion *)((const register Quaternion*)(&unksp140)));
            PSMTXMultVecSR((const Mtx)((s32) &sp408), (const Vec *)((const register Vec*)((Vec *) &sp18C)), (Vec *)((register Vec*)((Vec *) &sp18C)));
            PSMTXQuat((Mtx)((s32) &sp3D8), (const Quaternion *)((const register Quaternion*)(&unksp140)));
            PSMTXMultVecSR((const Mtx)((s32) &sp3D8), (const Vec *)((const register Vec*)((Vec *) &sp180)), (Vec *)((register Vec*)((Vec *) &sp180)));
        }
        PSMTXQuat((Mtx)((s32) &sp3A8), (const Quaternion *)((const register Quaternion*)(M2C_FIELD(this, Vec **, 0x20) + 0xC)));
        PSMTXMultVecSR((const Mtx)((s32) &sp3A8), (const Vec *)((const register Vec*)((Vec *) &sp18C)), (Vec *)((register Vec*)((Vec *) &sp18C)));
        PSMTXQuat((Mtx)((s32) &sp378), (const Quaternion *)((const register Quaternion*)(M2C_FIELD(this, Vec **, 0x20) + 0xC)));
        PSMTXMultVecSR((const Mtx)((s32) &sp378), (const Vec *)((const register Vec*)((Vec *) &sp180)), (Vec *)((register Vec*)((Vec *) &sp180)));
        var_f25 = 0.0f;
    }
    PSVECCrossProduct((const register Vec*)((Vec *) &sp180), (const register Vec*)((Vec *) &sp18C), (register Vec*)(v98));
    sp174 = v98[0];
    sp178 = v98[1];
    sp17C = v98[2];
    if (M2C_FIELD(this, u8 *, 0x35) & 1) {
        var_f25_2 = var_f25 - (M2C_FIELD(this, f32 *, 0x40) + M2C_FIELD(this, f32 *, 0x44));
    } else {
        var_f25_2 = var_f25 + (M2C_FIELD(this, f32 *, 0x40) + M2C_FIELD(this, f32 *, 0x44));
    }
    temp_r25 = temp_r27 & 0x10;
    if (temp_r25 != 0) {
        if (var_f25_2 < 0.0f) {
            var_f1 = -var_f25_2;
        } else {
            var_f1 = var_f25_2;
        }
        if (var_f1 > 0.00001f) {
            C_QUATRotAxisRad((Quaternion*)(&unksp140), (const Vec*)((Vec *) &sp174), var_f25_2);
            PSMTXQuat((Mtx)((s32) &sp348), (const Quaternion *)((const register Quaternion*)(&unksp140)));
            PSMTXMultVecSR((const Mtx)((s32) &sp348), (const Vec *)((const register Vec*)((Vec *) &sp180)), (Vec *)((register Vec*)((Vec *) &sp180)));
            PSMTXQuat((Mtx)((s32) &sp318), (const Quaternion *)((const register Quaternion*)(&unksp140)));
            PSMTXMultVecSR((const Mtx)((s32) &sp318), (const Vec *)((const register Vec*)((Vec *) &sp18C)), (Vec *)((register Vec*)((Vec *) &sp18C)));
        }
    }
    PSQUATInverse((const register Quaternion*)(M2C_FIELD(this, Vec **, 0x20) + 0xC), (register Quaternion*)(&unksp34));
    sp114 = unksp34;
    sp118 = sp38;
    sp11C = sp3C;
    sp120 = sp40;
    PSMTXQuat((Mtx)((s32) &sp1C8), (const Quaternion *)((const register Quaternion*)((Quaternion *) &sp114)));
    PSMTXMultVecSR((const Mtx)((s32) &sp1C8), (const Vec *)((const register Vec*)((Vec *) &sp18C)), (Vec *)((register Vec*)(&unksp8C)));
    sp15C = unksp8C;
    sp160 = sp90;
    sp164 = sp94;
    temp_r5_2 = M2C_FIELD(this, Vec **, 0x20);
    sp15C = unksp8C * M2C_FIELD(temp_r5_2, f32 *, 0x1C);
    sp160 = sp90 * M2C_FIELD(temp_r5_2, f32 *, 0x20);
    sp164 = sp94 * M2C_FIELD(temp_r5_2, f32 *, 0x24);
    PSMTXQuat((Mtx)((s32) &sp2E8), (const Quaternion *)((const register Quaternion*)(((u8*)(temp_r5_2) + 0xC))));
    PSMTXMultVecSR((const Mtx)((s32) &sp2E8), (const Vec *)((const register Vec*)((Vec *) &sp15C)), (Vec *)((register Vec*)((Vec *) &sp15C)));
    PSVECScale((const register Vec*)((Vec *) &sp18C), (register Vec*)((Vec *) &sp18C), PSVECDotProduct((const register Vec*)((Vec *) &sp18C), (const register Vec*)((Vec *) &sp15C)));
    PSQUATInverse((const register Quaternion*)(M2C_FIELD(this, Vec **, 0x20) + 0xC), (register Quaternion*)(&unksp24));
    sp104 = unksp24;
    sp108 = sp28;
    sp10C = sp2C;
    sp110 = sp30;
    PSMTXQuat((Mtx)((s32) &sp198), (const Quaternion *)((const register Quaternion*)((Quaternion *) &sp104)));
    PSMTXMultVecSR((const Mtx)((s32) &sp198), (const Vec *)((const register Vec*)((Vec *) &sp180)), (Vec *)((register Vec*)(&unksp80)));
    sp15C = unksp80;
    sp160 = sp84;
    sp164 = sp88;
    temp_r5_3 = M2C_FIELD(this, Vec **, 0x20);
    sp15C = unksp80 * M2C_FIELD(temp_r5_3, f32 *, 0x1C);
    sp160 = sp84 * M2C_FIELD(temp_r5_3, f32 *, 0x20);
    sp164 = sp88 * M2C_FIELD(temp_r5_3, f32 *, 0x24);
    PSMTXQuat((Mtx)((s32) &sp2B8), (const Quaternion *)((const register Quaternion*)(((u8*)(temp_r5_3) + 0xC))));
    PSMTXMultVecSR((const Mtx)((s32) &sp2B8), (const Vec *)((const register Vec*)((Vec *) &sp15C)), (Vec *)((register Vec*)((Vec *) &sp15C)));
    PSVECScale((const register Vec*)((Vec *) &sp180), (register Vec*)((Vec *) &sp180), PSVECDotProduct((const register Vec*)((Vec *) &sp180), (const register Vec*)((Vec *) &sp15C)));
    temp_r3_2 = M2C_FIELD(p1, peSpline **, 0x14);
    if ((temp_r3_2 == NULL) || !(M2C_FIELD(temp_r3_2, u8 *, 0) & 3)) {
        var_f1_2 = 1.0f;
    } else {
        var_f1_3 = M2C_FIELD(temp_r3_2, f32 *, 8) - p3;
        if (var_f1_3 < 0.0f) {
            var_f1_3 = -var_f1_3;
        }
        if (var_f1_3 <= 0.00001f) {
            var_f1_2 = M2C_FIELD(temp_r3_2, f32 *, 4);
        } else {
            var_f1_2 = peSplineGetValue((peSpline*)(temp_r3_2), p3);
        }
    }
    PSVECScale((const register Vec*)((Vec *) &sp18C), (register Vec*)((Vec *) &sp18C), M2C_FIELD(this, f32 *, 0x38) * var_f1_2);
    temp_r3_3 = M2C_FIELD(p1, peSpline **, 0x18);
    if ((temp_r3_3 == NULL) || !(M2C_FIELD(temp_r3_3, u8 *, 0) & 3)) {
        var_f1_4 = 1.0f;
    } else {
        var_f1_5 = M2C_FIELD(temp_r3_3, f32 *, 8) - p3;
        if (var_f1_5 < 0.0f) {
            var_f1_5 = -var_f1_5;
        }
        if (var_f1_5 <= 0.00001f) {
            var_f1_4 = M2C_FIELD(temp_r3_3, f32 *, 4);
        } else {
            var_f1_4 = peSplineGetValue((peSpline*)(temp_r3_3), p3);
        }
    }
    PSVECScale((const register Vec*)((Vec *) &sp180), (register Vec*)((Vec *) &sp180), M2C_FIELD(this, f32 *, 0x3C) * var_f1_4);
    if (temp_r25 == 0) {
        if (var_f25_2 < 0.0f) {
            var_f1_6 = -var_f25_2;
        } else {
            var_f1_6 = var_f25_2;
        }
        if (var_f1_6 > 0.00001f) {
            C_QUATRotAxisRad((Quaternion*)(&unksp140), (const Vec*)((Vec *) &sp174), var_f25_2);
            PSMTXQuat((Mtx)((s32) &sp288), (const Quaternion *)((const register Quaternion*)(&unksp140)));
            PSMTXMultVecSR((const Mtx)((s32) &sp288), (const Vec *)((const register Vec*)((Vec *) &sp180)), (Vec *)((register Vec*)((Vec *) &sp180)));
            PSMTXQuat((Mtx)((s32) &sp258), (const Quaternion *)((const register Quaternion*)(&unksp140)));
            PSMTXMultVecSR((const Mtx)((s32) &sp258), (const Vec *)((const register Vec*)((Vec *) &sp18C)), (Vec *)((register Vec*)((Vec *) &sp18C)));
        }
    }
    temp_r27_2 = (temp_r27 >> 0x12U) & 1;
    if (temp_r27_2 != 0) {
        PSVECScale((const register Vec*)((Vec *) &sp18C), (register Vec*)(&unksp74), M2C_FIELD(p1, f32 *, 0x1C));
        sp168 = unksp74;
        sp16C = sp78;
        sp170 = sp7C;
        PSVECScale((const register Vec*)((Vec *) &sp180), (register Vec*)(&unksp68), M2C_FIELD(p1, f32 *, 0x20));
        spF8 = unksp68;
        spFC = sp6C;
        sp100 = sp70;
        PSVECAdd((const register Vec*)((Vec *) &sp168), (const register Vec*)((Vec *) &spF8), (register Vec*)((Vec *) &sp168));
    }
    if (temp_r29 != 0) {
        var_r26 = (unsigned char *)(p2 + (M2C_FIELD(this, u16 *, 0x30) * 0x38));
    } else {
        var_r26 = (unsigned char *)(p2 + (M2C_FIELD(this, u16 *, 0x30) * 0x34));
    }
    PSVECSubtract((const register Vec*)((Vec *) &sp150), (const register Vec*)(&g_CameraPosition), (register Vec*)(&unkspE0));
    spEC = unkspE0;
    spF0 = spE4;
    spF4 = spE8;
    M2C_FIELD(this, f32 *, 0x4C) = PSVECDotProduct((const register Vec*)(&g_CameraLookDir), (const register Vec*)((Vec *) &spEC));
    sp164 = -sp194;
    sp15C = -sp18C;
    sp160 = -sp190;
    PSVECSubtract((const register Vec*)((Vec *) &sp15C), (const register Vec*)((Vec *) &sp180), (register Vec*)((Vec *) &sp15C));
    if (temp_r27_2 != 0) {
        PSVECAdd((const register Vec*)((Vec *) &sp15C), (const register Vec*)((Vec *) &sp168), (register Vec*)((Vec *) &sp15C));
    }
    PSVECAdd((const register Vec*)((Vec *) &sp15C), (const register Vec*)((Vec *) &sp150), (register Vec*)((Vec *) &sp15C));
    M2C_FIELD(var_r26, f32 *, 0) = sp15C;
    M2C_FIELD(var_r26, f32 *, 4) = sp160;
    M2C_FIELD(var_r26, f32 *, 8) = sp164;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp15C, sp160, sp164);
    }
    PSVECSubtract((const register Vec*)((Vec *) &sp18C), (const register Vec*)((Vec *) &sp180), (register Vec*)(&unksp5C));
    sp15C = unksp5C;
    sp160 = sp60;
    sp164 = sp64;
    if (temp_r27_2 != 0) {
        PSVECAdd((const register Vec*)((Vec *) &sp15C), (const register Vec*)((Vec *) &sp168), (register Vec*)((Vec *) &sp15C));
    }
    PSVECAdd((const register Vec*)((Vec *) &sp15C), (const register Vec*)((Vec *) &sp150), (register Vec*)((Vec *) &sp15C));
    M2C_FIELD(var_r26, f32 *, 0xC) = sp15C;
    M2C_FIELD(var_r26, f32 *, 0x10) = sp160;
    M2C_FIELD(var_r26, f32 *, 0x14) = sp164;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp15C, sp160, sp164);
    }
    PSVECAdd((const register Vec*)((Vec *) &sp18C), (const register Vec*)((Vec *) &sp180), (register Vec*)(&unksp50));
    sp15C = unksp50;
    sp160 = sp54;
    sp164 = sp58;
    if (temp_r27_2 != 0) {
        PSVECAdd((const register Vec*)((Vec *) &sp15C), (const register Vec*)((Vec *) &sp168), (register Vec*)((Vec *) &sp15C));
    }
    PSVECAdd((const register Vec*)((Vec *) &sp15C), (const register Vec*)((Vec *) &sp150), (register Vec*)((Vec *) &sp15C));
    M2C_FIELD(var_r26, f32 *, 0x18) = sp15C;
    M2C_FIELD(var_r26, f32 *, 0x1C) = sp160;
    M2C_FIELD(var_r26, f32 *, 0x20) = sp164;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp15C, sp160, sp164);
    }
    PSVECSubtract((const register Vec*)((Vec *) &sp180), (const register Vec*)((Vec *) &sp18C), (register Vec*)(&unksp44));
    sp15C = unksp44;
    sp160 = sp48;
    sp164 = sp4C;
    if (temp_r27_2 != 0) {
        PSVECAdd((const register Vec*)((Vec *) &sp15C), (const register Vec*)((Vec *) &sp168), (register Vec*)((Vec *) &sp15C));
    }
    PSVECAdd((const register Vec*)((Vec *) &sp15C), (const register Vec*)((Vec *) &sp150), (register Vec*)((Vec *) &sp15C));
    M2C_FIELD(var_r26, f32 *, 0x24) = sp15C;
    M2C_FIELD(var_r26, f32 *, 0x28) = sp160;
    M2C_FIELD(var_r26, f32 *, 0x2C) = sp164;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp15C, sp160, sp164);
    }
    peColorSplineGetValue((u8*)(&sp20), (peColorSpline*)(M2C_FIELD(p1, peColorSpline **, 0x38)), p3);
    spA = sp20;
    sp9 = sp21;
    sp20 = sp14;
    sp8 = sp22;
    sp21 = sp10;
    sp22 = spC;
    temp_r3_4 = M2C_FIELD(p1, peSpline **, 0x40);
    if ((temp_r3_4 == NULL) || !(M2C_FIELD(temp_r3_4, u8 *, 0) & 3)) {

    } else {
        var_f1_7 = M2C_FIELD(temp_r3_4, f32 *, 8) - p3;
        if (var_f1_7 < 0.0f) {
            var_f1_7 = -var_f1_7;
        }
        if (var_f1_7 <= 0.00001f) {

        } else {
            peSplineGetValue((peSpline*)(temp_r3_4), p3);
        }
    }
    sp23 = sp18;
    M2C_FIELD(var_r26, s32 *, 0x30) = (s32) sp20;
    if (temp_r29 != 0) {
        peColorSplineGetValue((u8*)(&sp20), (peColorSpline*)(M2C_FIELD(p1, peColorSpline **, 0x3C)), p3);
        M2C_FIELD(var_r26, s32 *, 0x34) = (s32) sp20;
    }
}
}
}
}
}
}
}
