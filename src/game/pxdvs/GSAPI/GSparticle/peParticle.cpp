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
struct GSbound;
struct GSgfxDL;
struct GSgfxLayer;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxPrimType { GSgfxPrimType_draft_dummy };
struct GSgfxVF;
typedef f32 Mtx[3][4];
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
    f32 x, y, z, w;
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
    void Start(peEmitterNode*, _peParticle*, GSgfxDL*, _EmitParams*);
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
class peParticleContainer : public peRenderContainer {
public:
    peNode** sorted;
    _peParticle* data;
    f32 uv[8];

    peParticleContainer(peEmitterNode*, _peParticle*, unsigned short);
    virtual ~peParticleContainer();
    virtual void Start();
    virtual u16 Emit(unsigned short);
    virtual void Update(float);
    virtual void Render();
    virtual void Stop();
    void DepthSort();
    void hideNode(struct peNodeView* n);
    bool updateNode(struct peNodeView* n, f32 dt);
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
extern Vec g_CameraSideDir;
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

struct peXformP {
    Vec pos;
    Quaternion rot;
    Vec scale;
};
struct GSColor {
    u8 r, g, b, a;
};
struct peSplineHdr {
    u8 flags;
    f32 value;
    f32 time;
};

struct peParticleDef {
    u32 flags;
    u8 pad4[0x10];
    peSpline* scaleX;
    peSpline* scaleY;
    f32 offsetX;
    f32 offsetY;
    f32 spinScale;
    u8 pad28[0xc];
    peSpline* spin;
    peColorSpline* color;
    peColorSpline* color2;
    peSpline* alpha;
    u8 pad44[8];
    f32 yaw;
    f32 roll;
};

struct peParticleNodeData {
    f32 life0;
    f32 life;
    Vec pos;
    Vec vel;
    peXformP* xform;
    u8 pad24[0xc];
    u16 index;
    u8 pad32[3];
    u8 spin;
    u8 pad36[2];
    f32 sizeX;
    f32 sizeY;
    f32 rot;
    f32 rotOffset;
    f32 rotSpeed;
    f32 depth;
};

struct peEmitterNodeData {
    u8 pad0[0x38];
    f32 color[4];
    u8 pad48[0xb4];
    u32* params;
};

static inline f32 evalSpline(peSpline* sp, f32 t) {
    peSplineHdr* s = (peSplineHdr*)sp;
    if (s == 0 || (s->flags & 3) == 0) {
        return 1.0f;
    }
    f32 d = s->time - t;
    if (d < 0.0f) {
        d = -d;
    }
    if (d <= 0.00001f) {
        return s->value;
    }
    return peSplineGetValue(sp, t);
}

static inline void rotateBy(Vec* v, Quaternion* q) {
    Mtx m;
    PSMTXQuat(m, q);
    PSMTXMultVecSR(m, v, v);
}

static inline void quatToMtx(Mtx m, Quaternion q) {
    PSMTXQuat(m, &q);
}

static inline void mtxMulVec(Vec* dst, Quaternion* q, Vec* src) {
    Mtx m;
    Vec t;
    PSMTXQuat(m, q);
    PSMTXMultVecSR(m, src, &t);
    *dst = t;
}

static inline void vecCross(Vec* dst, Vec* a, Vec* b) {
    Vec t;
    PSVECCrossProduct(a, b, &t);
    *dst = t;
}

static inline void vecSub(Vec* dst, Vec* a, Vec* b) {
    Vec t;
    PSVECSubtract(a, b, &t);
    *dst = t;
}

static inline void vecAdd(Vec* dst, Vec* a, Vec* b) {
    Vec t;
    PSVECAdd(a, b, &t);
    *dst = t;
}

static inline void vecScale(Vec* dst, Vec* a, f32 k) {
    Vec t;
    PSVECScale(a, &t, k);
    *dst = t;
}

static inline void projectToNode(Vec* v, peXformP* xf) {
    Quaternion qi;
    Mtx m;
    Vec t;
    Vec p;
    PSQUATInverse(&xf->rot, &qi);
    quatToMtx(m, qi);
    PSMTXMultVecSR(m, v, &t);
    p = t;
    p.x *= xf->scale.x;
    p.y *= xf->scale.y;
    p.z *= xf->scale.z;
    rotateBy(&p, &xf->rot);
    PSVECScale(v, v, PSVECDotProduct(v, &p));
}

static inline void emitCorner(char* out, Vec* v, Vec* off, bool hasOff, Vec* pos) {
    if (hasOff) {
        PSVECAdd(v, off, v);
    }
    PSVECAdd(v, pos, v);
    ((Vec*)out)->x = v->x;
    ((Vec*)out)->y = v->y;
    ((Vec*)out)->z = v->z;
    if (g_currentBound != NULL) {
        GSboundAddPoint(g_currentBound, v->x, v->y, v->z);
    }
}

static inline f32 __OSu8tof32(register const u8* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 2 }
    return ret;
}

static inline f32 OSu8tof32(u8 in) {
    return __OSu8tof32(&in);
}

static inline u8 OSf32tou8(register f32 inF) {
    u8 out;
    u8* outP = &out;
    register u8* ptr = outP;
    asm { psq_st inF, 0(ptr), 1, 2 }
    return *ptr;
}

struct _EmitParamsP {
    u8 data[0x48];
};

struct peDLView {
    u16 flags;
    u16 stride;
    u8* buf;
    u8 pad8[8];
};

struct peNodeView {
    u8 pad0[0x28];
    peNodeView* next;
    u8 pad2c[6];
    u16 vtx;
    u8 pad34[2];
    u8 visible;
};

inline void peParticleContainer::hideNode(peNodeView* n) {
    peDLView* d = (peDLView*)dl[cur];
    u16* idx = NULL;
    u32 hasColor2 = (*(u32*)data >> 25) & 1;
    n->visible = 0;
    u16 off = n->vtx * 4;
    if (d->flags & 1) {
        idx = (u16*)(d->buf + off * d->stride + 3);
    }
    for (u16 i = 4; i-- != 0;) {
        idx[0] = 0xffff;
        idx[1] = 0xffff;
        idx[2] = 0xffff;
        idx += 3;
        if (hasColor2) {
            *idx = 0xffff;
            idx += 1;
        }
    }
    d->flags |= 2;
}

void peParticleContainer::Stop() {
    if (started) {
        PreUpdate();
        started = 0;
        u32 flags = *(u32*)data;
        if (flags & 0x20000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, false);
        }
        if (flags & 0x40000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, false);
        }
        if (flags & 0x80000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, false);
        }
        for (peNodeView* n = (peNodeView*)activeList; n != NULL; n = n->next) {
            hideNode(n);
        }
        RemoveAll();
        ResetSwap();
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
extern "C++" {
inline bool peParticleContainer::updateNode(peNodeView* node, f32 dt) {
    char* buf = (char*)(&bufA)[cur];
    peParticleNodeData* n = (peParticleNodeData*)node;
    peParticleDef* p = (peParticleDef*)data;
    peEmitterNode* e = emitter;
    if (buf == NULL) {
        return false;
    }
    if (!((peNode*)n)->Update(e, dt)) {
        return false;
    }
    f32 t = 1.0f - n->life / n->life0;
    if (p->flags & 0x10000) {
        n->rotOffset = p->spinScale * evalSpline(p->spin, t);
    }
    n->rotOffset = n->rotSpeed * dt + n->rotOffset;
    ((peParticleNode*)n)->UpdateRenderData(e, (_peParticle*)p, buf, t);
    return true;
}

void peParticleContainer::Update(float dt) {
    if (started) {
        peNodeView* next;
        for (peNodeView* n = (peNodeView*)activeList; n != NULL; n = next) {
            next = n->next;
            if (!updateNode(n, dt)) {
                hideNode(n);
                RemoveNode((peNode*)n);
            }
        }
        DepthSort();
    }
}
}

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
    u8 *temp_r5;
    s32 var_r12;
    s32 var_r4_2;
    u8 *temp_r5_2;
    s32 var_r8;
    u16 var_r9;
    u32 temp_r0_2;
    u32 temp_r9;
    u8 var_r0;
    u8 *var_r4;
    u8 *temp_r10;
    s32 var_r11;
    u32 var_r6;
    u8 *temp_r6;
    u8 *temp_r9_2;
    u8 *var_r11_2;
    u8 var_r31;
    s32 var_r5;
    u16 temp_r8;

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
                        var_r4 -= 4;
                        var_r6 -= 1;
                        if ((u8) M2C_FIELD(temp_r5, u8 *, 0x36) != 0) {

                        } else {
                            goto loop_19;
                        }
                    }
                }
                if (var_r6 >= 0) {
                    temp_f0 = M2C_FIELD(temp_r10, f32 *, 0x4C);
                    temp_f1 = M2C_FIELD(temp_r5_2, f32 *, 0x4C);
                    temp_r5_2 = (unsigned char *)(*((u8 *)temp_r9 + (var_r6 * 4)));
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
            var_r8 += 4;
            var_r11 += 1;
        }
        if (var_r31 != 0) {
            var_r5 = 0;
            var_r4_2 = 0;
            temp_r6 = (unsigned char *)((u8*)this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28));
            temp_r0_2 = ((u32) *M2C_FIELD(this, u32 **, 0x58) >> 0x19U) & 1;
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
                            temp_r8_2 = var_r9 * 3;
                            temp_r7 = (var_r9 * 2) & 0xFFFE;
                            var_r9 += 1;
                            M2C_FIELD(var_r11_2, s16 *, 0) = (s16) (temp_r8 + temp_r8_2);
                            M2C_FIELD(var_r11_2, u16 *, 2) = temp_r8;
                            M2C_FIELD(var_r11_2, u16 *, 4) = temp_r8;
                            M2C_FIELD(var_r11_2, s16 *, 6) = temp_r7;
                            var_r11_2 += 8;
                        }
                    } else {
                        while (var_r9 < 4U) {
                            temp_r8_3 = (enum TsE)(var_r9 * 3);
                            temp_r7_2 = (var_r9 * 2) & 0xFFFE;
                            var_r9 += 1;
                            M2C_FIELD(var_r11_2, s16 *, 0) = (s16) (temp_r8 + temp_r8_3);
                            M2C_FIELD(var_r11_2, u16 *, 2) = temp_r8;
                            M2C_FIELD(var_r11_2, s16 *, 4) = temp_r7_2;
                            var_r11_2 += 6;
                        }
                    }
                }
                var_r4_2 += 4;
                var_r5 += 1;
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
                u32 tmp1 = M2C_FIELD(data, s32 *, 0x54);
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
u16 peParticleContainer::Emit(unsigned short n) {
    if (!started) {
        return 0;
    }
    u16 left = CreateNodes(n);
    _EmitParamsP* params = (_EmitParamsP*)g_emitParams;
    peNodeView* next;
    peNodeView* node = (peNodeView*)activeList;
    u16 created = left;
    while (left != 0) {
        next = node->next;
        ((peParticleNode*)node)->Start(emitter, data, (GSgfxDL*)dl[cur], (_EmitParams*)params);
        node = next;
        left--;
        params++;
    }
    return created;
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
    u0 = OSs16tof32(M2C_FIELD(data, s16 *, 0x44));
    u0 *= scale;
    v0 = OSs16tof32(M2C_FIELD(data, s16 *, 0x46));
    v0 *= scale;
    u1 = OSs16tof32(M2C_FIELD(data, s16 *, 0x48));
    u1 *= scale;
    v1 *= scale;
    v1 = OSs16tof32(M2C_FIELD(data, s16 *, 0x4A));
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
    u32 temp_r31;
    volatile s32 sp14;
    s32 unksp21;
    s32 unksp22;
    s32 unksp23;
    u8 sp27;
    u8 sp26;
    u8 sp25;
    volatile u8 sp24;
    s32 sp20;
    volatile s32 sp1C;
    volatile s32 sp18;
    s16 spC;
    volatile s16 spA;
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
    u8 var_r28;
    u8 *var_r5;
    s32 sp10;

    var_r28 = M2C_FIELD(this, u8 *, 0x34);
    temp_r29 = (temp_r31 >> 0x19U) & 1;
    temp_r31 = M2C_FIELD(p0, u32 *, 0);
    temp_r30 = M2C_FIELD(p0, s32 **, 0x54);
    if ((p2 != NULL) && ((s32) (M2C_FIELD(p1, u16 *, 0) & 1) == 1)) {
        if (temp_r31 & 0x400000) {
            spC = (s16) *temp_r30;
            temp_f1 = M2C_ERROR( );
            temp_r24 = (temp_r31 >> 0x17U) & 1;
            var_f2 = temp_f1;
            if (temp_r24 != 0) {
                var_f2 = temp_f1;
                var_f2 -= 1.0f;
            }
            if (temp_r31 & 0x01000000) {
                var_f1 = (var_f2 * (M2C_FIELD(this, f32 *, 0) - M2C_FIELD(this, f32 *, 4))) / M2C_FIELD(p0, f32 *, 0x30);
            } else {
                var_f1 = M2C_FIELD(p0, f32 *, 0x30) * (var_f2 * (1.0f - (M2C_FIELD(this, f32 *, 4) / M2C_FIELD(this, f32 *, 0))));
            }
            spA = (s16) var_r28;
            temp_f30 = (f32) fmod((f64) (var_f1 + M2C_ERROR( )), (f64) var_f2);
            var_r28 = (u8) (u16) (sp14 % (u16) *temp_r30);
            if (temp_r24 != 0) {
                sp8 = (u16) var_r28;
                sp27 = sp10;
                sp26 = sp10;
                sp25 = sp10;
                if (sp24 < sp10) sp24 = sp10;
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
                    M2C_FIELD((u16)g_current_layer, s32 *, 0x14F8) = (s32) sp24;
                    sp18 = (s32) sp24;
                    M2C_FIELD((u16)g_current_layer, s32 *, 0x16F8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16F8) | 2);
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
        var_r8_2 = !(temp_r31 & 0x100) ? var_r8_2 : 2;
        var_r8_2 = 0;
        var_r7_2 = 0;
        var_r7_2 = !(temp_r31 & 0x80) ? var_r7_2 : 2;
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
static inline f32 __peS16tof32(register const s16* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 3 }
    return ret;
}

static inline f32 peS16tof32(s16 in) {
    s16 tmp = in;
    return __peS16tof32(&tmp);
}

static inline void __peF32tou8(register f32 arg, volatile register u8* out) {
    asm { psq_st arg, 0(out), 1, 2 }
}

static inline u8 peF32tou8(f32 in) {
    u32 out;
    __peF32tou8(in, (u8*)&out);
    return *(u8*)&out;
}

void peParticleNode::Start(peEmitterNode* emitter, _peParticle* particle, GSgfxDL* dl, _EmitParams* params) {
    u32 flags;
    u32 quad;
    f32 r;
    u16 offset;
    u16 base;
    u16* idx;
    u16 i;

    flags = M2C_FIELD(particle, u32*, 0);
    quad = (flags >> 25) & 1;
    if ((M2C_FIELD(dl, u16*, 0) & 1) == 1) {
        ((peNode*)this)->Start(emitter, params);
        M2C_FIELD(this, u8*, 0x35) = 0;
        M2C_FIELD(this, u8*, 0x36) = 1;
        r = HSD_Randf();
        M2C_FIELD(this, f32*, 0x38) = M2C_FIELD(particle, f32*, 0xC) * r;
        M2C_FIELD(this, f32*, 0x3C) = M2C_FIELD(particle, f32*, 0x10) * r;
        M2C_FIELD(this, f32*, 0x38) += M2C_FIELD(particle, f32*, 4);
        M2C_FIELD(this, f32*, 0x3C) += M2C_FIELD(particle, f32*, 8);
        if (flags & 0x40) {
            M2C_FIELD(this, f32*, 0x40) = 6.2831855f * HSD_Randf();
        } else {
            M2C_FIELD(this, f32*, 0x40) = 0.0f;
        }
        if ((flags & 0x20) && HSD_Randf() < 0.5f) {
            M2C_FIELD(this, u8*, 0x35) |= 1;
        }
        M2C_FIELD(this, f32*, 0x44) = M2C_FIELD(particle, f32*, 0x24);
        M2C_FIELD(this, f32*, 0x48) = M2C_FIELD(particle, f32*, 0x2C) * HSD_Randf() + M2C_FIELD(particle, f32*, 0x28);
        if ((flags & 0x300000) == 0x300000) {
            f32 count = peS16tof32(*M2C_FIELD(particle, s32**, 0x54));
            M2C_FIELD(this, u8*, 0x34) = peF32tou8(count * HSD_Randf());
        } else {
            M2C_FIELD(this, u8*, 0x34) = 0;
        }
        offset = M2C_FIELD(this, u16*, 0x32) * 4;
        base = (u8)((quad != 0) + 13);
        base = base * (M2C_FIELD(this, u16*, 0x30));
        if (M2C_FIELD(dl, u16*, 0) & 1) {
            idx = (u16*)(M2C_FIELD(dl, u8**, 4) + offset * M2C_FIELD(dl, u16*, 2) + 3);
        } else {
            idx = NULL;
        }
        i = 0;
        if (quad != 0) {
            for (; i < 4; i++) {
                idx[0] = base + i * 3;
                idx[1] = base;
                idx[2] = base;
                idx[3] = i * 2;
                idx = idx + 4;
            }
        } else {
            for (; i < 4; i++) {
                idx[0] = base + i * 3;
                idx[1] = base;
                idx[2] = i * 2;
                idx = idx + 3;
            }
        }
        M2C_FIELD(dl, u16*, 0) |= 2;
    }
}
}

}

extern "C++" {
extern "C++" {
void peParticleNode::UpdateRenderData(peEmitterNode* emitter, _peParticle* part, char* out_in, float t) {
    Quaternion q;
    peParticleNodeData* n = (peParticleNodeData*)this;
    peEmitterNodeData* e = (peEmitterNodeData*)emitter;
    peParticleDef* p = (peParticleDef*)part;
    u32 flags = p->flags;
    u32 hasColor2 = (flags >> 25) & 1;
    Vec offY;
    Vec right;
    Vec up;
    Vec fwd;
    Vec off;
    char* out = out_in;
    Vec v;
    Vec pos;
    f32 angle;

    {
        f32 py = n->pos.y * n->xform->scale.y;
        f32 pz = n->pos.z * n->xform->scale.z;
        f32 px = n->pos.x * n->xform->scale.x;
        pos.x = px;
        pos.y = py;
        pos.z = pz;
    }
    rotateBy(&pos, &n->xform->rot);
    PSVECAdd(&pos, &n->xform->pos, &pos);

    if (flags & 0x200) {
        if (flags & 0x20000) {
            vecSub(&fwd, &g_CameraPosition, &pos);
            PSVECNormalize(&fwd, &fwd);
            vecCross(&right, &fwd, &g_CameraUpDir);
            PSVECNormalize(&right, &right);
            if (flags & 0x400) {
                fwd.y = 0.0f;
                PSVECNormalize(&fwd, &fwd);
                up.x = 0.0f;
                up.y = 1.0f;
                up.z = 0.0f;
            } else {
                vecCross(&up, &right, &fwd);
            }
        } else {
            if (flags & 0x400) {
                up = yAxisVector;
            } else {
                up = g_CameraUpDir;
            }
            right = g_CameraSideDir;
        }
        angle = p->yaw;
    } else {
        Quaternion qy;
        Quaternion qz;
        C_QUATRotAxisRad(&qy, &yAxisVector, p->yaw);
        C_QUATRotAxisRad(&qz, &zAxisVector, p->roll);
        PSQUATMultiply(&qz, &qy, &qz);
        mtxMulVec(&right, &qz, &xAxisVector);
        mtxMulVec(&up, &qz, &yAxisVector);
        if (*e->params & 0x400) {
            Vec euler;
            f32 vz = n->vel.z;
            f32 vx = n->vel.x;
            f32 h = sqrtf(vx * vx + vz * vz);
            euler.x = atan2(-n->vel.y, h);
            euler.y = atan2(vx, vz);
            euler.z = 0.0f;
            EulerToQuat(&euler, &qy);
            rotateBy(&right, &qy);
            rotateBy(&up, &qy);
        }
        rotateBy(&right, &n->xform->rot);
        rotateBy(&up, &n->xform->rot);
        angle = 0.0f;
    }
    vecCross(&fwd, &up, &right);
    if (n->spin & 1) {
        angle -= n->rot + n->rotOffset;
    } else {
        angle += n->rot + n->rotOffset;
    }
    int spinFirst = flags & 0x10;
    if (spinFirst && (angle < 0.0f ? -angle : angle) > 0.00001f) {
        C_QUATRotAxisRad(&q, &fwd, angle);
        rotateBy(&up, &q);
        rotateBy(&right, &q);
    }
    projectToNode(&right, n->xform);
    projectToNode(&up, n->xform);
    PSVECScale(&right, &right, n->sizeX * evalSpline(p->scaleX, t));
    PSVECScale(&up, &up, n->sizeY * evalSpline(p->scaleY, t));
    if (!spinFirst && (angle < 0.0f ? -angle : angle) > 0.00001f) {
        C_QUATRotAxisRad(&q, &fwd, angle);
        rotateBy(&up, &q);
        rotateBy(&right, &q);
    }
    bool hasOff = (flags >> 18) & 1;
    if (hasOff) {
        vecScale(&off, &right, p->offsetX);
        vecScale(&offY, &up, p->offsetY);
        PSVECAdd(&off, &offY, &off);
    }
    if (hasColor2) {
        out += n->index * 0x38;
    } else {
        out += n->index * 0x34;
    }
    {
        Vec d;
        vecSub(&d, &pos, &g_CameraPosition);
        n->depth = PSVECDotProduct(&g_CameraLookDir, &d);
    }
    {
        v.z = -right.z;
        v.x = -right.x;
        v.y = -right.y;
        PSVECSubtract(&v, &up, &v);
        emitCorner(out, &v, &off, hasOff, &pos);
        vecSub(&v, &right, &up);
        emitCorner(out + 0xc, &v, &off, hasOff, &pos);
        vecAdd(&v, &right, &up);
        emitCorner(out + 0x18, &v, &off, hasOff, &pos);
        vecSub(&v, &up, &right);
        emitCorner(out + 0x24, &v, &off, hasOff, &pos);
    }
    {
        GSColor c;
        peColorSplineGetValue((u8*)&c, p->color, t);
        c.r = OSf32tou8(e->color[0] * OSu8tof32(c.r));
        c.g = OSf32tou8(e->color[1] * OSu8tof32(c.g));
        c.b = OSf32tou8(e->color[2] * OSu8tof32(c.b));
        c.a = OSf32tou8(255.0f * e->color[3] * evalSpline(p->alpha, t));
        *(GSColor*)(out + 0x30) = c;
        if (hasColor2) {
            peColorSplineGetValue((u8*)&c, p->color2, t);
            *(GSColor*)(out + 0x34) = c;
        }
    }
}
}
}
}
}
}
}
