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
struct _peDistortion;
class peContainer;
class peDistortionContainer;
struct peDistortionNode;
struct peEmitterNode;
struct peNode;
class peRenderContainer;
struct peSpline;

extern "C++" {
struct GSbound {
    u8 _draft[1];
};
struct GSgfxDL {
    u8 _draft[1];
};
struct GSgfxLayer {
    u8 _draft[1];
    s32 dlDraw(GSgfxDL*);
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
struct _peDistortion {
    u8 _draft[1];
};
class peContainer {
public:
    peEmitterNode* emitter;
    u32 unk4;
    void* buffer;
    peNode* freeList;
    peNode* activeList;
    u16 count;
    u16 maxCount;
    u8 dirty;
    u8 started;

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
    s32 MoveNode(peNode*, peNode*);
};
class peRenderContainer : public peContainer {
public:
    u8 swapPending;
    u8 cur;
    u32 bufSize;
    u8 dl[2][0x10];
    u8* bufA;
    u8* bufB;
    u16 tokens[2];

    peRenderContainer(peEmitterNode*, unsigned long, unsigned short, GSgfxVF*, GSgfxPrimType, unsigned char, unsigned char, bool);
    virtual ~peRenderContainer();
    virtual void PreUpdate();
    s32 InitSwap();
    s32 ResetSwap();
    s32 MarkForSwap();
    s32 ResolveMultipleSwap();
};
class peDistortionContainer : public peRenderContainer {
public:
    _peDistortion* data;
    f32 uv[8];

    peDistortionContainer(peEmitterNode*, _peDistortion*, unsigned short);
    virtual ~peDistortionContainer();
    virtual void Start();
    virtual u16 Emit(unsigned short);
    virtual void Update(float);
    virtual void Render();
    virtual void Stop();
};
struct peDistortionNode {
    u8 _draft[1];
    void UpdateRenderData(peEmitterNode*, _peDistortion*, char*, float);
};
struct peEmitterNode {
    u8 _draft[1];
};
struct peNode {
    u8 _draft[1];
    void Start(peEmitterNode*, _EmitParams*);
    bool Update(peEmitterNode*, float);
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
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
asm void PSVECCrossProduct(const register Vec* a, const register Vec* b, register Vec* axb);
asm f32 PSVECDotProduct(const register Vec* a, const register Vec* b);
void PSVECNormalize(const register Vec* src, register Vec* unit);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double atan2(double y, double x);
s32 particleEngineSetupBlendMode(s32, void*, s32, s32, void*);
s32 particleEngineSetupTevStages(s32, s32, s32);
s32 particleEngineSetupTexture(s32, s32, s32, s32, s32, s32);
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
extern Vec g_CameraPosition;
extern s32 g_CameraSideDir;
extern Vec g_CameraUpDir;
extern GSbound* g_currentBound;
extern GSgfxLayer* g_current_layer;
extern _EmitParams* g_emitParams;
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
extern s32 g_render_pass;
extern GSgfxVF g_vertex_format;
struct XdBlobC { u8 data[0xC]; };
extern XdBlobC xAxisVector;
extern s32 yAxisVector;
extern s32 this_;
}

void peDistortionContainer::Stop() {
    u8 *var_r6;
    s32 temp_r29;
    s32 var_r4;
    u8 *temp_r7;
    u8 *var_r31;
    s32 temp_cr0_eq;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) != 0) {
        ((peContainer*)this)->PreUpdate();
        M2C_FIELD(this, u8 *, 0x19) = 0U;
        var_r31 = M2C_FIELD(this, u8 **, 0x10);
        temp_r29 = *M2C_FIELD(M2C_FIELD(this, u8 **, 0), s32 **, 0xFC);
        if (temp_r29 & 0x800000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, false);
        }
        if (temp_r29 & 0x01000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, false);
        }
        if (temp_r29 & 0x02000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, false);
        }
        while (var_r31 != NULL) {
            temp_r7 = (unsigned char *)(this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28));
            if (M2C_FIELD((u16)temp_r7, u16 *, 0) & 1) {
                var_r6 = (unsigned char *)(M2C_FIELD(temp_r7, s32 *, 4) + ((((M2C_FIELD(var_r31, u16 *, 0x30) * 4) & 0xFFFC) * M2C_FIELD(temp_r7, u16 *, 2)) + 3));
            } else {
                var_r6 = NULL;
            }
            var_r4 = 4;
loop_13:
            temp_cr0_eq = var_r4 == 0;
            var_r4 -= 1;
            if (temp_cr0_eq == 0) {
                M2C_FIELD(var_r6, u16 *, 0) = 0xFFFF;
                M2C_FIELD(var_r6, u16 *, 2) = 0xFFFF;
                M2C_FIELD(var_r6, u16 *, 4) = 0xFFFF;
                var_r6 += 6;
                goto loop_13;
            }
            M2C_FIELD((u16)temp_r7, u16 *, 0) = (u16) (M2C_FIELD(temp_r7, u16 *, 0) | 2);
            var_r31 = M2C_FIELD(var_r31, u8 **, 0x28);
        }
        ((peContainer*)((peContainer *) this))->RemoveAll();
        ((peRenderContainer*)((peRenderContainer *) this))->ResetSwap();
    }
}
}

#define LAYER_FIELD(l, T, off) (*(T*)((u8*)(l) + (off)))
static inline void layerMark(GSgfxLayer* l, u32 sum, u32 off, u32 bit) {
    LAYER_FIELD(l, u32, off) |= bit;
    LAYER_FIELD(l, u32, 0x16A8) |= sum;
    LAYER_FIELD(l, u32, off + 0xB8) |= bit;
    LAYER_FIELD(l, u32, 0x1760) |= sum;
}

static inline bool canRender(peDistortionContainer* c) {
    if (!M2C_FIELD(c, u8 *, 0x19)) {
        return false;
    }
    u32 flags = M2C_FIELD(M2C_FIELD(c, u8 **, 0x54), u32 *, 0);
    if (M2C_FIELD(c, u16 *, 0x14) == 0) {
        return false;
    }
    if (g_render_pass != 1) {
        return false;
    }
    switch (M2C_FIELD(g_current_layer, s32 *, 0x28)) {
    case 1:
        if (!(flags & 0x2000)) {
            return false;
        }
        break;
    case 3:
        if (flags & 0x10) {
            return false;
        }
        break;
    case 5:
        if (!(flags & 0x10)) {
            return false;
        }
        break;
    default:
        return false;
    }
    return true;
}

extern "C++" {
void peDistortionContainer::Render() {
    u8 *temp_r29;
    s32 temp_cr0_eq;
    s32 temp_r0;
    u8 *temp_r4_2;
    s32 var_r8;
    u32 temp_r31;
    u32 temp_r4;
    s32 temp_r0_2;
    u8 var_r0;
    GSgfxVF *var_r31;
    s32 var_r7;

    if (M2C_FIELD(this, u8 *, 0x19)) {
        if (canRender(this)) {
            ((peRenderContainer*)((peRenderContainer *) this))->ResolveMultipleSwap();
            temp_r31 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), u32 *, 0);
            if (temp_r31 & 0x100) {
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xD8C) = 2;
                    layerMark(l, 2, 0x16B8, 2);
                }
            } else {
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xD8C) = 0;
                    layerMark(l, 2, 0x16B8, 2);
                }
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s8, 0x165C) = 0;
                LAYER_FIELD(l, s32, 0x1660) = 3;
                layerMark(l, 0x40, 0x170C, 8);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s8, 0x1656) = 1;
                LAYER_FIELD(l, s8, 0x1657) = 0;
                LAYER_FIELD(l, s8, 0x1658) = 0;
                layerMark(l, 0x40, 0x170C, 4);
            }
            {
                GSgfxLayer* l = g_current_layer;
                LAYER_FIELD(l, s32, 0x1664) = 7;
                LAYER_FIELD(l, s8, 0x1670) = 0;
                LAYER_FIELD(l, s32, 0x1668) = 0;
                LAYER_FIELD(l, s32, 0x166C) = 7;
                LAYER_FIELD(l, s8, 0x1671) = 0;
                LAYER_FIELD(l, s8, 0x1672) = 1;
                layerMark(l, 0x40, 0x170C, 0x10);
            }
            particleEngineSetupBlendMode(0, g_current_layer, 1, 0, g_current_layer);
            particleEngineSetupTevStages(0, 0, 0);
            var_r8 = 0;
            if (temp_r31 & 0x40) {
                var_r8 = 2;
            }
            var_r7 = !(temp_r31 & 0x20) ? var_r7 : 2;
            particleEngineSetupTexture(0, M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), s32 *, 0x60), temp_r31 & 3, (temp_r31 >> 2U) & 3, var_r7, var_r8);
            temp_r29 = M2C_FIELD((this + (temp_r0_2 * 4)), u8 **, 0x48);
            var_r7 = 0;
            temp_r0_2 = M2C_FIELD(this, u8 *, 0x21);
            temp_r4_2 = (unsigned char *)(this + ((temp_r0_2 * 0x10) + 0x28));
            if (M2C_FIELD((s16)temp_r4_2, s16 *, 0) & 1) {
                var_r31 = M2C_FIELD(temp_r4_2, GSgfxVF **, 0xC);
            } else {
                var_r31 = NULL;
            }
            GSgfxVFSetArray((GSgfxVF*)(var_r31), 9, 3, (void*)(temp_r29), 4, M2C_FIELD(this, s32 *, 0x24));
            GSgfxVFSetArray((GSgfxVF*)(var_r31), 0xB, 3, (void*)(temp_r29 + 0x30), 4, M2C_FIELD(this, s32 *, 0x24));
            GSgfxVFSetArray((GSgfxVF*)(var_r31), 0xD, 3, (void*)((u8*)this + 0x58), 4, 0x20);
            ((GSgfxLayer*)(g_current_layer))->dlDraw((GSgfxDL*)(this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28)));
            ((peRenderContainer*)((peRenderContainer *) this))->MarkForSwap();
        }
    }
}
}

extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
void peDistortionContainer::Update(float p0) {
    peNode *var_r31;
    f32 temp_f31;
    f32 var_f1;
    f32 var_f1_2;
    peEmitterNode *temp_r28;
    peNode *temp_r30;
    _peDistortion *temp_r27;
    peSpline *temp_r3;
    s32 temp_cr0_eq;
    s8 *temp_r26;
    u32 var_r4;
    u8 *var_r5;
    u8 var_r0;
    u8 *temp_r6;
    u8 temp_r0;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) != 0) {
        var_r31 = M2C_FIELD(this, peNode **, 0x10);
        while (var_r31 != NULL) {
            temp_r0 = M2C_FIELD(this, u8 *, 0x21);
            temp_r30 = M2C_FIELD(var_r31, peNode **, 0x28);
            temp_r27 = M2C_FIELD(this, _peDistortion **, 0x54);
            temp_r26 = (signed char *)&(*((u8*)this + ((temp_r0 * 4) + 0x48)));
            temp_r28 = M2C_FIELD(this, peEmitterNode **, 0);
            if (temp_r26 == NULL) {
                var_r0 = 0;
            } else if ((s32) (*((u8 *)this + ((temp_r0 * 0x10) + 0x28)) & 1) != 1) {
                var_r0 = 0;
            } else if (((peNode*)(var_r31))->Update((peEmitterNode*)(temp_r28), p0) == 0) {
                var_r0 = 0;
            } else {
                temp_f31 = 1.0f - (M2C_FIELD(var_r31, f32 *, 4) / M2C_FIELD(var_r31, f32 *, 0));
                if (M2C_FIELD(temp_r27, s32 *, 0) & 0x200) {
                    temp_r3 = M2C_FIELD(temp_r27, peSpline **, 0x30);
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
                    M2C_FIELD(var_r31, f32 *, 0x40) = (f32) (M2C_FIELD(temp_r27, f32 *, 0x24) * var_f1);
                }
                M2C_FIELD(var_r31, f32 *, 0x40) = (f32) ((M2C_FIELD(var_r31, f32 *, 0x44) * p0) + M2C_FIELD(var_r31, f32 *, 0x40));
                ((peDistortionNode*)((peDistortionNode *) var_r31))->UpdateRenderData((peEmitterNode*)(temp_r28), (_peDistortion*)(temp_r27), (char*)(temp_r26), temp_f31);
                var_r0 = 1;
            }
            if (var_r0 == 0) {
                temp_r6 = (unsigned char *)((u8*)this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28));
                if (M2C_FIELD(temp_r6, u16 *, 0) & 1) {
                    var_r5 = (unsigned char *)(M2C_FIELD(temp_r6, s32 *, 4) + ((((M2C_FIELD(var_r31, u16 *, 0x30) * 4) & 0xFFFC) * M2C_FIELD(temp_r6, u16 *, 2)) + 3));
                } else {
                    var_r5 = NULL;
                }
                var_r4 = 4;
loop_25:
                temp_cr0_eq = var_r4 == 0;
                var_r4 -= 1;
                if (temp_cr0_eq == 0) {
                    M2C_FIELD(var_r5, u16 *, 0) = 0xFFFF;
                    M2C_FIELD(var_r5, u16 *, 2) = 0xFFFF;
                    M2C_FIELD(var_r5, u16 *, 4) = 0xFFFF;
                    var_r5 += 6;
                    goto loop_25;
                }
                M2C_FIELD(temp_r6, u16 *, 0) = (u16) (M2C_FIELD(temp_r6, u16 *, 0) | 2);
                ((peContainer*)((peContainer *) this))->RemoveNode((peNode*)(var_r31));
            }
            var_r31 = temp_r30;
        }
    }
}
}

extern "C++" {
u16 peDistortionContainer::Emit(unsigned short p0) {
    u8 *temp_r31;
    f32 temp_f1;
    u16 var_r30;
    s32 temp_r24;
    _EmitParams *var_r29;
    u16 temp_r4;
    u16 temp_r8;
    s32 *temp_r23;
    u8 *var_r9;
    peNode *var_r28;
    peNode *temp_r27;
    u16 temp_r26;

    if ((u8) M2C_FIELD(((s32)this), u8 *, 0x19) == 0) {
        return 0U;
    }
    var_r30 = ((peContainer*)((peContainer *) ((s32)this)))->CreateNodes(p0);
    var_r29 = g_emitParams;
    var_r28 = M2C_FIELD(((s32)this), peNode **, 0x10);
    temp_r26 = var_r30;
    while (var_r30 != 0) {
        temp_r23 = M2C_FIELD(((s32)this), s32 **, 0x54);
        temp_r27 = M2C_FIELD((u16)var_r28, peNode **, 0x28);
        temp_r31 = (unsigned char *)(((s32)this) + ((M2C_FIELD(((s32)this), u8 *, 0x21) * 0x10) + 0x28));
        temp_r24 = M2C_FIELD(temp_r23, s32 *, 0);
        if ((s32) (M2C_FIELD(temp_r31, u16 *, 0) & 1) == 1) {
            ((peNode*)((u16)var_r28))->Start((peEmitterNode*)(M2C_FIELD(((s32)this), peEmitterNode **, 0)), (_EmitParams*)(var_r29));
            temp_f1 = HSD_Randf();
            M2C_FIELD(var_r28, f32 *, 0x34) = (f32) (M2C_FIELD(temp_r23, f32 *, 0xC) * temp_f1);
            M2C_FIELD(var_r28, f32 *, 0x38) = (f32) (M2C_FIELD(temp_r23, f32 *, 0x10) * temp_f1);
            M2C_FIELD(var_r28, f32 *, 0x34) = (f32) (M2C_FIELD(var_r28, f32 *, 0x34) + M2C_FIELD(temp_r23, f32 *, 4));
            M2C_FIELD(var_r28, f32 *, 0x38) = (f32) (M2C_FIELD(var_r28, f32 *, 0x38) + M2C_FIELD(temp_r23, f32 *, 8));
            if (temp_r24 & 0x80) {
                M2C_FIELD(var_r28, f32 *, 0x3C) = (f32) (6.2831855f * HSD_Randf());
            } else {
                M2C_FIELD(var_r28, f32 *, 0x3C) = 0.0f;
            }
            if ((temp_r24 & 0x1000) && (HSD_Randf() < 0.5f)) {
                M2C_FIELD(var_r28, u16 *, 0x32) = (u16) (M2C_FIELD(var_r28, u16 *, 0x32) | 1);
            }
            M2C_FIELD(var_r28, f32 *, 0x40) = (f32) M2C_FIELD(temp_r23, f32 *, 0x24);
            M2C_FIELD(var_r28, f32 *, 0x44) = (f32) ((M2C_FIELD(temp_r23, f32 *, 0x2C) * HSD_Randf()) + M2C_FIELD(temp_r23, f32 *, 0x28));
            temp_r4 = M2C_FIELD(var_r28, u16 *, 0x30);
            temp_r8 = temp_r4 * 0xD;
            if (M2C_FIELD(temp_r31, u16 *, 0) & 1) {
                var_r9 = (unsigned char *)(M2C_FIELD(temp_r31, s32 *, 4) + ((((temp_r4 * 4) & 0xFFFC) * M2C_FIELD(temp_r31, u16 *, 2)) + 3));
            } else {
                var_r9 = NULL;
            }
            M2C_FIELD(var_r9, u16 *, 0) = temp_r8;
            M2C_FIELD(var_r9, u16 *, 2) = temp_r8;
            M2C_FIELD(var_r9, s16 *, 4) = 0;
            M2C_FIELD(var_r9, s16 *, 6) = (s16) (temp_r8 + 3);
            M2C_FIELD(var_r9, u16 *, 8) = temp_r8;
            M2C_FIELD(var_r9, s16 *, 0xA) = 2;
            M2C_FIELD(var_r9, s16 *, 0xC) = (s16) (temp_r8 + 6);
            M2C_FIELD(var_r9, u16 *, 0xE) = temp_r8;
            M2C_FIELD(var_r9, s16 *, 0x10) = 4;
            M2C_FIELD(var_r9, s16 *, 0x12) = (s16) (temp_r8 + 9);
            M2C_FIELD(var_r9, u16 *, 0x14) = temp_r8;
            M2C_FIELD(var_r9, s16 *, 0x16) = 6;
            M2C_FIELD(temp_r31, u16 *, 0) = (u16) (M2C_FIELD(temp_r31, u16 *, 0) | 2);
        }
        var_r28 = temp_r27;
        var_r30 -= 1;
        var_r29 += 0x48;
    }
    return temp_r26;
}
}

extern "C++" {
void peDistortionContainer::Start() {
    s32 temp_r31;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        M2C_FIELD(this, u8 *, 0x19) = 1U;
        temp_r31 = *M2C_FIELD(M2C_FIELD(this, u8 **, 0), s32 **, 0xFC);
        ((peRenderContainer*)((peRenderContainer *) this))->InitSwap();
        if (temp_r31 & 0x800000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, true);
        }
        if (temp_r31 & 0x01000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, true);
        }
        if (temp_r31 & 0x02000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, true);
        }
    }
}
}

extern "C++" {
peDistortionContainer::~peDistortionContainer() {
    g_particle_debug_stats.unk4 -= 0x78;
    g_particle_debug_stats.unk14 -= 0x78;
}
}

extern "C++" {
#pragma push
#pragma dont_inline off
peDistortionContainer::peDistortionContainer(peEmitterNode* p0, _peDistortion* p1, unsigned short p2)
    : peRenderContainer(p0, 0x48, p2, &g_vertex_format, (GSgfxPrimType)0x80, 4, 0x34, (*(u32*)p1 >> 14) & 1) {
    peNode* node;
    u16 i;
    _peDistortion* d;

    data = p1;
    d = data;
    uv[0] = M2C_FIELD(d, f32 *, 0x58);
    uv[1] = M2C_FIELD(d, f32 *, 0x5C);
    uv[2] = M2C_FIELD(d, f32 *, 0x50);
    uv[3] = M2C_FIELD(d, f32 *, 0x5C);
    uv[4] = M2C_FIELD(d, f32 *, 0x50);
    uv[5] = M2C_FIELD(d, f32 *, 0x54);
    uv[6] = M2C_FIELD(d, f32 *, 0x58);
    uv[7] = M2C_FIELD(d, f32 *, 0x54);
    DCFlushRange(uv, 0x20);
    i = 0;
    for (node = freeList; node != 0; node = M2C_FIELD(node, peNode **, 0x28)) {
        M2C_FIELD(node, u16 *, 0x30) = i;
        i++;
    }
    g_particle_debug_stats.unk4 += 0x78;
    g_particle_debug_stats.unk14 += 0x78;
}
#pragma pop
}
void peDistortionNode::UpdateRenderData(peEmitterNode* p0, _peDistortion* p1, char* p2, float p3) {
    u32 temp_r31;
    s32 sp1C;
    s32 sp20;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp38;
    s32 sp3C;
    s32 sp44;
    s32 sp48;
    s32 sp50;
    s32 sp54;
    s32 sp5C;
    s32 sp60;
    s32 sp68;
    s32 sp6C;
    f32 sp74;
    f32 sp78;
    s32 sp8;
    f32 sp80;
    f32 sp84;
    s32 sp8C;
    s32 sp90;
    volatile s32 spA4;
    s32 spA8;
    s32 unksp104;
    s32 unksp14;
    s32 unksp24;
    s32 unksp34;
    s32 unksp40;
    s32 unksp4C;
    f32 unksp58;
    f32 unksp64;
    f32 unksp70;
    f32 unksp7C;
    s32 unksp88;
    s32 v94[3];
    s32 unkspA0;
    s32 unkspAC;
    s32 unkspD8;
    s32 unkspE8;
    s32 sp39C;
    s32 sp36C;
    s32 sp33C;
    s32 sp30C;
    s32 sp2DC;
    s32 sp2AC;
    s32 sp27C;
    s32 sp24C;
    s32 sp21C;
    s32 sp1EC;
    s32 sp1BC;
    s32 sp18C;
    s32 sp15C;
    f32 sp158;
    f32 sp154;
    f32 sp150;
    f32 sp14C;
    f32 sp148;
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    f32 sp12C;
    f32 sp128;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    volatile f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    u8 sp13;
    volatile s8 sp12;
    s8 sp11;
    s8 sp10;
    f32 spC;
    Vec *temp_r5;
    Vec *temp_r5_2;
    Vec *temp_r5_3;
    f32 temp_f1_4;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f1_6;
    f32 var_f1_7;
    f32 var_f29;
    f32 var_f2;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;
    peSpline *temp_r3_2;
    peSpline *temp_r3_3;
    peSpline *temp_r3_4;
    s32 temp_r3;
    s32 var_r0;
    u32 temp_r26;
    u32 temp_r26_2;
    s32 sp18;
    u8 *temp_r27;

    temp_r5 = M2C_FIELD(this, Vec **, 0x20);
    temp_r31 = M2C_FIELD(p1, u32 *, 0);
    sp118 = M2C_FIELD(this, f32 *, 0xC) * M2C_FIELD(temp_r5, f32 *, 0x20);
    sp114 = M2C_FIELD(this, f32 *, 8) * M2C_FIELD(temp_r5, f32 *, 0x1C);
    sp11C = M2C_FIELD(this, f32 *, 0x10) * M2C_FIELD(temp_r5, f32 *, 0x24);
    PSMTXQuat((Mtx)((s32) &sp39C), (const Quaternion *)((const register Quaternion*)(((u8*)(temp_r5) + 0xC))));
    PSMTXMultVecSR((const Mtx)((s32) &sp39C), (const Vec *)((const register Vec*)((Vec *) &sp114)), (Vec *)((register Vec*)((Vec *) &sp114)));
    PSVECAdd((const register Vec*)((Vec *) &sp114), (const register Vec*)(M2C_FIELD(this, Vec **, 0x20)), (register Vec*)((Vec *) &sp114));
    if (temp_r31 & 0x100) {
        if (temp_r31 & 0x400) {
            PSVECSubtract((const register Vec*)(&g_CameraPosition), (const register Vec*)((Vec *) &sp114), (register Vec*)(&unkspA0));
            sp120 = unkspA0;
            sp124 = spA4;
            sp128 = spA8;
            PSVECNormalize((const register Vec*)((Vec *) &sp120), (register Vec*)((Vec *) &sp120));
            PSVECCrossProduct((const register Vec*)((Vec *) &sp120), (const register Vec*)(&g_CameraUpDir), (register Vec*)(v94));
            sp150 = v94[0];
            sp154 = v94[1];
            sp158 = v94[2];
            PSVECNormalize((const register Vec*)((Vec *) &sp150), (register Vec*)((Vec *) &sp150));
            PSVECCrossProduct((const register Vec*)((Vec *) &sp120), (const register Vec*)((Vec *) &sp150), (register Vec*)(&unkspAC));
        } else {
            sp158 = M2C_FIELD(&g_CameraSideDir, f32 *, 8);
            sp144 = M2C_FIELD(&g_CameraUpDir, f32 *, 0);
            sp148 = M2C_FIELD(&g_CameraUpDir, f32 *, 4);
            sp14C = M2C_FIELD(&g_CameraUpDir, f32 *, 8);
            sp150 = M2C_FIELD(&g_CameraSideDir, f32 *, 0);
            sp154 = M2C_FIELD(&g_CameraSideDir, f32 *, 4);
        }
    } else {
        sp150 = M2C_FIELD(&xAxisVector, f32 *, 0);
        sp154 = M2C_FIELD(&xAxisVector, f32 *, 4);
        sp158 = M2C_FIELD(&xAxisVector, f32 *, 8);
        sp144 = M2C_FIELD(&yAxisVector, f32 *, 0);
        sp148 = M2C_FIELD(&yAxisVector, f32 *, 4);
        sp14C = M2C_FIELD(&yAxisVector, f32 *, 8);
        if (*M2C_FIELD(p0, s32 **, 0xFC) & 0x400) {
            temp_f29 = M2C_FIELD(this, f32 *, 0x1C);
            temp_f30 = M2C_FIELD(this, f32 *, 0x14);
            var_f2 = (temp_f30 * temp_f30) + (temp_f29 * temp_f29);
            var_f2 = sqrtf(var_f2);
            temp_f1_4 = (f32) atan2((f64) temp_f30, (f64) temp_f29);
            spF8 = (f32) atan2(-M2C_FIELD(this, f32 *, 0x18), (f64) var_f2);
            sp100 = 0.0f;
            spFC = temp_f1_4;
            EulerToQuat((Vec*)((Vec *) &spF8), (Quaternion*)(&unksp104));
            PSMTXQuat((Mtx)((s32) &sp36C), (const Quaternion *)((const register Quaternion*)(&unksp104)));
            PSMTXMultVecSR((const Mtx)((s32) &sp36C), (const Vec *)((const register Vec*)((Vec *) &sp150)), (Vec *)((register Vec*)((Vec *) &sp150)));
            PSMTXQuat((Mtx)((s32) &sp33C), (const Quaternion *)((const register Quaternion*)(&unksp104)));
            PSMTXMultVecSR((const Mtx)((s32) &sp33C), (const Vec *)((const register Vec*)((Vec *) &sp144)), (Vec *)((register Vec*)((Vec *) &sp144)));
        }
        PSMTXQuat((Mtx)((s32) &sp30C), (const Quaternion *)((const register Quaternion*)(M2C_FIELD(this, Vec **, 0x20) + 0xC)));
        PSMTXMultVecSR((const Mtx)((s32) &sp30C), (const Vec *)((const register Vec*)((Vec *) &sp150)), (Vec *)((register Vec*)((Vec *) &sp150)));
        PSMTXQuat((Mtx)((s32) &sp2DC), (const Quaternion *)((const register Quaternion*)(M2C_FIELD(this, Vec **, 0x20) + 0xC)));
        PSMTXMultVecSR((const Mtx)((s32) &sp2DC), (const Vec *)((const register Vec*)((Vec *) &sp144)), (Vec *)((register Vec*)((Vec *) &sp144)));
    }
    PSVECCrossProduct((const register Vec*)((Vec *) &sp144), (const register Vec*)((Vec *) &sp150), (register Vec*)(&unksp88));
    sp120 = unksp88;
    sp124 = sp8C;
    sp128 = sp90;
    if (M2C_FIELD(this, s16 *, 0x32) & 1) {
        var_f29 = 0.0f - (M2C_FIELD(this, f32 *, 0x3C) + M2C_FIELD(this, f32 *, 0x40));
    } else {
        var_f29 = 0.0f + (M2C_FIELD(this, f32 *, 0x3C) + M2C_FIELD(this, f32 *, 0x40));
    }
    temp_r26 = temp_r31 & 0x8000;
    if (temp_r26 != 0) {
        if (var_f29 < 0.0f) {
            var_f1 = -var_f29;
        } else {
            var_f1 = var_f29;
        }
        if (var_f1 > 0.00001f) {
            C_QUATRotAxisRad((Quaternion*)(&unkspE8), (const Vec*)((Vec *) &sp120), var_f29);
            PSMTXQuat((Mtx)((s32) &sp2AC), (const Quaternion *)((const register Quaternion*)(&unkspE8)));
            PSMTXMultVecSR((const Mtx)((s32) &sp2AC), (const Vec *)((const register Vec*)((Vec *) &sp144)), (Vec *)((register Vec*)((Vec *) &sp144)));
            PSMTXQuat((Mtx)((s32) &sp27C), (const Quaternion *)((const register Quaternion*)(&unkspE8)));
            PSMTXMultVecSR((const Mtx)((s32) &sp27C), (const Vec *)((const register Vec*)((Vec *) &sp150)), (Vec *)((register Vec*)((Vec *) &sp150)));
        }
    }
    PSQUATInverse((const register Quaternion*)(M2C_FIELD(this, Vec **, 0x20) + 0xC), (register Quaternion*)(&unksp24));
    spC8 = unksp24;
    spCC = sp28;
    spD0 = sp2C;
    spD4 = sp30;
    PSMTXQuat((Mtx)((s32) &sp18C), (const Quaternion *)((const register Quaternion*)((Quaternion *) &spC8)));
    PSMTXMultVecSR((const Mtx)((s32) &sp18C), (const Vec *)((const register Vec*)((Vec *) &sp150)), (Vec *)((register Vec*)(&unksp7C)));
    sp138 = unksp7C;
    sp13C = sp80;
    sp140 = sp84;
    temp_r5_2 = M2C_FIELD(this, Vec **, 0x20);
    sp138 = unksp7C * M2C_FIELD(temp_r5_2, f32 *, 0x1C);
    sp13C = sp80 * M2C_FIELD(temp_r5_2, f32 *, 0x20);
    sp140 = sp84 * M2C_FIELD(temp_r5_2, f32 *, 0x24);
    PSMTXQuat((Mtx)((s32) &sp24C), (const Quaternion *)((const register Quaternion*)(((u8*)(temp_r5_2) + 0xC))));
    PSMTXMultVecSR((const Mtx)((s32) &sp24C), (const Vec *)((const register Vec*)((Vec *) &sp138)), (Vec *)((register Vec*)((Vec *) &sp138)));
    PSVECScale((const register Vec*)((Vec *) &sp150), (register Vec*)((Vec *) &sp150), PSVECDotProduct((const register Vec*)((Vec *) &sp150), (const register Vec*)((Vec *) &sp138)));
    PSQUATInverse((const register Quaternion*)(M2C_FIELD(this, Vec **, 0x20) + 0xC), (register Quaternion*)(&unksp14));
    spB8 = unksp14;
    spBC = sp18;
    spC0 = sp1C;
    spC4 = sp20;
    PSMTXQuat((Mtx)((s32) &sp15C), (const Quaternion *)((const register Quaternion*)((Quaternion *) &spB8)));
    PSMTXMultVecSR((const Mtx)((s32) &sp15C), (const Vec *)((const register Vec*)((Vec *) &sp144)), (Vec *)((register Vec*)(&unksp70)));
    sp138 = unksp70;
    sp13C = sp74;
    sp140 = sp78;
    temp_r5_3 = M2C_FIELD(this, Vec **, 0x20);
    sp138 = unksp70 * M2C_FIELD(temp_r5_3, f32 *, 0x1C);
    sp13C = sp74 * M2C_FIELD(temp_r5_3, f32 *, 0x20);
    sp140 = sp78 * M2C_FIELD(temp_r5_3, f32 *, 0x24);
    PSMTXQuat((Mtx)((s32) &sp21C), (const Quaternion *)((const register Quaternion*)(((u8*)(temp_r5_3) + 0xC))));
    PSMTXMultVecSR((const Mtx)((s32) &sp21C), (const Vec *)((const register Vec*)((Vec *) &sp138)), (Vec *)((register Vec*)((Vec *) &sp138)));
    PSVECScale((const register Vec*)((Vec *) &sp144), (register Vec*)((Vec *) &sp144), PSVECDotProduct((const register Vec*)((Vec *) &sp144), (const register Vec*)((Vec *) &sp138)));
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
    PSVECScale((const register Vec*)((Vec *) &sp150), (register Vec*)((Vec *) &sp150), M2C_FIELD(this, f32 *, 0x34) * var_f1_2);
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
    PSVECScale((const register Vec*)((Vec *) &sp144), (register Vec*)((Vec *) &sp144), M2C_FIELD(this, f32 *, 0x38) * var_f1_4);
    if (temp_r26 == 0) {
        if (var_f29 < 0.0f) {
            var_f1_6 = -var_f29;
        } else {
            var_f1_6 = var_f29;
        }
        if (var_f1_6 > 0.00001f) {
            C_QUATRotAxisRad((Quaternion*)(&unkspD8), (const Vec*)((Vec *) &sp120), var_f29);
            PSMTXQuat((Mtx)((s32) &sp1EC), (const Quaternion *)((const register Quaternion*)(&unkspD8)));
            PSMTXMultVecSR((const Mtx)((s32) &sp1EC), (const Vec *)((const register Vec*)((Vec *) &sp144)), (Vec *)((register Vec*)((Vec *) &sp144)));
            PSMTXQuat((Mtx)((s32) &sp1BC), (const Quaternion *)((const register Quaternion*)(&unkspD8)));
            PSMTXMultVecSR((const Mtx)((s32) &sp1BC), (const Vec *)((const register Vec*)((Vec *) &sp150)), (Vec *)((register Vec*)((Vec *) &sp150)));
        }
    }
    temp_r26_2 = (temp_r31 >> 0xBU) & 1;
    if (temp_r26_2 != 0) {
        PSVECScale((const register Vec*)((Vec *) &sp150), (register Vec*)(&unksp64), M2C_FIELD(p1, f32 *, 0x1C));
        sp12C = unksp64;
        sp130 = sp68;
        sp134 = sp6C;
        PSVECScale((const register Vec*)((Vec *) &sp144), (register Vec*)(&unksp58), M2C_FIELD(p1, f32 *, 0x20));
        sp12C *= unksp58;
        sp130 *= sp5C;
        sp134 *= sp60;
    }
    sp138 = -sp150;
    sp13C = -sp154;
    temp_r27 = (unsigned char *)(p2 + (M2C_FIELD(this, s16 *, 0x30) * 0x34));
    sp140 = -sp158;
    PSVECSubtract((const register Vec*)((Vec *) &sp138), (const register Vec*)((Vec *) &sp144), (register Vec*)((Vec *) &sp138));
    if (temp_r26_2 != 0) {
        PSVECAdd((const register Vec*)((Vec *) &sp138), (const register Vec*)((Vec *) &sp12C), (register Vec*)((Vec *) &sp138));
    }
    PSVECAdd((const register Vec*)((Vec *) &sp138), (const register Vec*)((Vec *) &sp114), (register Vec*)((Vec *) &sp138));
    M2C_FIELD(temp_r27, f32 *, 0) = sp138;
    M2C_FIELD(temp_r27, f32 *, 4) = sp13C;
    M2C_FIELD(temp_r27, f32 *, 8) = sp140;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp138, sp13C, sp140);
    }
    PSVECSubtract((const register Vec*)((Vec *) &sp150), (const register Vec*)((Vec *) &sp144), (register Vec*)(&unksp4C));
    sp138 = unksp4C;
    sp13C = sp50;
    sp140 = sp54;
    if (temp_r26_2 != 0) {
        PSVECAdd((const register Vec*)((Vec *) &sp138), (const register Vec*)((Vec *) &sp12C), (register Vec*)((Vec *) &sp138));
    }
    PSVECAdd((const register Vec*)((Vec *) &sp138), (const register Vec*)((Vec *) &sp114), (register Vec*)((Vec *) &sp138));
    M2C_FIELD(temp_r27, f32 *, 0xC) = sp138;
    M2C_FIELD(temp_r27, f32 *, 0x10) = sp13C;
    M2C_FIELD(temp_r27, f32 *, 0x14) = sp140;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp138, sp13C, sp140);
    }
    PSVECAdd((const register Vec*)((Vec *) &sp150), (const register Vec*)((Vec *) &sp144), (register Vec*)(&unksp40));
    sp138 = unksp40;
    sp13C = sp44;
    sp140 = sp48;
    if (temp_r26_2 != 0) {
        PSVECAdd((const register Vec*)((Vec *) &sp138), (const register Vec*)((Vec *) &sp12C), (register Vec*)((Vec *) &sp138));
    }
    PSVECAdd((const register Vec*)((Vec *) &sp138), (const register Vec*)((Vec *) &sp114), (register Vec*)((Vec *) &sp138));
    M2C_FIELD(temp_r27, f32 *, 0x18) = sp138;
    M2C_FIELD(temp_r27, f32 *, 0x1C) = sp13C;
    M2C_FIELD(temp_r27, f32 *, 0x20) = sp140;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp138, sp13C, sp140);
    }
    PSVECSubtract((const register Vec*)((Vec *) &sp144), (const register Vec*)((Vec *) &sp150), (register Vec*)(&unksp34));
    sp138 = unksp34;
    sp13C = sp38;
    sp140 = sp3C;
    if (temp_r26_2 != 0) {
        PSVECAdd((const register Vec*)((Vec *) &sp138), (const register Vec*)((Vec *) &sp12C), (register Vec*)((Vec *) &sp138));
    }
    PSVECAdd((const register Vec*)((Vec *) &sp138), (const register Vec*)((Vec *) &sp114), (register Vec*)((Vec *) &sp138));
    M2C_FIELD(temp_r27, f32 *, 0x24) = sp138;
    M2C_FIELD(temp_r27, f32 *, 0x28) = sp13C;
    M2C_FIELD(temp_r27, f32 *, 0x2C) = sp140;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp138, sp13C, sp140);
    }
    temp_r3_4 = M2C_FIELD(p1, peSpline **, 0x34);
    sp12 = 0xFF;
    sp11 = 0xFF;
    sp10 = 0xFF;
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
    sp13 = sp8;
    M2C_FIELD(temp_r27, s32 *, 0x30) = (s32) sp10;
}
}
}
}
