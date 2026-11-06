#ifndef __MWERKS__
#include <game/psq.h>
#endif
#include <dolphin/types.h>
#include <game/gcdata.h>
#include <game/gsvfarray.h>
#include <game/pecontainer.h>
#include <game/gcfield.h>
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
    u16 flags;
    u16 stride;
    u8* data;
    u32 size;
    GSgfxVF* vf;
};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
#ifdef __MWERKS__
    s32 dlDraw(GSgfxDL*);
#else
    void dlDraw(GSgfxDL* p0);
#endif
#ifdef __MWERKS__
    s32 beginSurface(unsigned short);
#else
    void beginSurface(unsigned short p0);
#endif
#ifdef __MWERKS__
    s32 endSurface();
#else
    void endSurface();
#endif
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
    PE_CONTAINER_MEMBERS

    peContainer(peEmitterNode* e, u32 nodeSize, unsigned short max);
    virtual ~peContainer();
    virtual void Start();
    virtual void PreUpdate();
    virtual u16 Emit(unsigned short n) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Stop() = 0;

    static void SetLayerVisibility(GSgfxLayerID, bool);
#ifdef __MWERKS__
    s32 RemoveNode(peNode*);
#else
    void RemoveNode(peNode* node);
#endif
    u16 CreateNodes(unsigned short);
#ifdef __MWERKS__
    s32 RemoveAll();
#else
    void RemoveAll();
#endif
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
    PE_RENDER_MEMBERS

    peRenderContainer(peEmitterNode*, u32, unsigned short, GSgfxVF*, GSgfxPrimType, unsigned char, unsigned char, bool);
    virtual ~peRenderContainer();
    virtual void PreUpdate();
#ifdef __MWERKS__
    s32 InitSwap();
#else
    void InitSwap();
#endif
#ifdef __MWERKS__
    s32 ResetSwap();
#else
    void ResetSwap();
#endif
#ifdef __MWERKS__
    s32 MarkForSwap();
#else
    void MarkForSwap();
#endif
#ifdef __MWERKS__
    s32 ResolveMultipleSwap();
#else
    void ResolveMultipleSwap();
#endif
};
class peParticleContainer : public peRenderContainer {
public:
    PE_PARTICLE_CONTAINER_MEMBERS

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
enum GStexFilter { GS_TEXFILTER_NEAR = 0, GS_TEXFILTER_LINEAR = 2 };
void particleEngineSetupTexture(u8, s32, s32, s32, s32, s32);
void peColorSplineGetValue(u8* out, peColorSpline* s, f32 t);
f32 peSplineGetValue(peSpline* s, f32 t);
extern f32 __float_nan[];

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

#ifndef __MWERKS__
static
#endif
inline float sqrtf(float x) {
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (float)(x * guess);
    } else if (x < 0.0) {
        return __float_nan[0];
    } else if (__fpclassifyf(x) == 1) {
        return __float_nan[0];
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
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 5 }
#else
    ret = PSQ_LOAD(arg, 0, 5);
#endif
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
    gc_bef32 value;
    gc_bef32 time;
};

struct peParticleDef {
    gc_be32 flags;
    u8 pad4[0x10];
    gc_ptr32(peSpline) scaleX;
    gc_ptr32(peSpline) scaleY;
    gc_bef32 offsetX;
    gc_bef32 offsetY;
    gc_bef32 spinScale;
    u8 pad28[0xc];
    gc_ptr32(peSpline) spin;
    gc_ptr32(peColorSpline) color;
    gc_ptr32(peColorSpline) color2;
    gc_ptr32(peSpline) alpha;
    u8 pad44[8];
    gc_bef32 yaw;
    gc_bef32 roll;
};

struct peParticleNodeData {
    f32 life0;
    f32 life;
    Vec pos;
    Vec vel;
    peXformP* xform;
    u8 pad24[0x4];
    void* slot28;
    void* slot2C;
    u16 index;
    u16 sortIndex;
    u8 flag34;
    u8 spin;
    u8 active;
    u8 pad37;
    f32 sizeX;
    f32 sizeY;
    f32 rot;
    f32 rotOffset;
    f32 rotSpeed;
    f32 depth;
};

struct peEmitterNodeData {
    u8 pad0[0x20];
    void* slot20;
    u8 pad24[0x4];
    void* slot28;
    void* slot2C;
    u8 pad30[0x8];
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
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 2 }
#else
    ret = PSQ_LOAD(arg, 0, 2);
#endif
    return ret;
}

static inline f32 OSu8tof32(u8 in) {
    return __OSu8tof32(&in);
}

static inline u8 OSf32tou8(register f32 inF) {
    u8 out;
    u8* outP = &out;
    register u8* ptr = outP;
#ifdef __MWERKS__
    asm { psq_st inF, 0(ptr), 1, 2 }
#else
    PSQ_STORE(ptr, 0, inF, 2);
#endif
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
    u8 pad0[0x20];
    void* slot20;
    u8 pad24[0x4];
    peNodeView* next;
    void* slot2C;
    u8 pad30[0x2];
    u16 vtx;
    u8 pad34[2];
    u8 visible;
};

inline void peParticleContainer::hideNode(peNodeView* n) {
    peDLView* d = (peDLView*)dl[cur];
    u16* idx = NULL;
    u32 hasColor2 = (GC_AT(u32, data, 0) >> 25) & 1;
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

#pragma push
#pragma optimize_for_size on
struct peParticleDLView {
    u16 flags;
    u16 stride;
    u8* data;
};

static inline bool peParticleActive(peParticleNodeData* n) {
    return n->active != 0;
}

static inline u8 peParticleBehind(peParticleNodeData* n, peParticleNodeData* p) {
    f32 nd = n->depth;
    f32 pd = p->depth;
    if (pd == nd) {
        return 0;
    }
    if (p->sortIndex < n->sortIndex) {
        return pd < nd;
    }
    return pd > nd;
}

static inline s32 peParticlePrevActive(peParticleNodeData** list, s32 i) {
    if (list == 0) {
        return -1;
    }
    peParticleNodeData** p = &list[i];
    while (i > 0) {
        p--;
        i--;
        if (peParticleActive(*p)) {
            return i;
        }
    }
    return -1;
}

void peParticleContainer::DepthSort() {
    if (started && (((peParticleDef*)data)->flags & 0x80000) && count >= 2 && sorted != 0) {
        u8 changed = 0;
        for (s32 i = 1; i < maxCount; i++) {
            peParticleNodeData* n = ((peParticleNodeData**)sorted)[i];
            if (peParticleActive(n)) {
                s32 slot = i;
                s32 k;
                while ((k = peParticlePrevActive((peParticleNodeData**)sorted, slot)) >= 0) {
                    peParticleNodeData* p = ((peParticleNodeData**)sorted)[k];
                    if (!peParticleBehind(n, p)) {
                        break;
                    }
                    ((peParticleNodeData**)sorted)[slot] = p;
                    slot = k;
                    changed = 1;
                }
                ((peParticleNodeData**)sorted)[slot] = n;
            }
        }
        if (changed) {
            peParticleDLView* dl = (peParticleDLView*)this->dl[cur];
            u16 perQuad = 13 + ((((peParticleDef*)data)->flags >> 25) & 1 ? 1 : 0);
            for (s32 i = 0; i < maxCount; i++) {
                peParticleNodeData* n = ((peParticleNodeData**)sorted)[i];
                if (!peParticleActive(n) || n->sortIndex == (u16)i) {
                    continue;
                }
                n->sortIndex = i;
                u16 base = n->index * perQuad;
                u8* q = (dl->flags & 1) ? dl->data + (u16)(i * 4) * dl->stride + 3 : 0;
                if ((((peParticleDef*)data)->flags >> 25) & 1) {
                    for (u16 v = 0; v < 4; v++) {
                        PE_DL_W16(q, s16, 0, base + v * 3);
                        PE_DL_W16(q, u16, 1, base);
                        PE_DL_W16(q, u16, 2, base);
                        PE_DL_W16(q, s16, 3, v * 2);
                        q += 8;
                    }
                } else {
                    for (u16 v = 0; v < 4; v++) {
                        PE_DL_W16(q, s16, 0, base + v * 3);
                        PE_DL_W16(q, u16, 1, base);
                        PE_DL_W16(q, s16, 2, v * 2);
                        q += 6;
                    }
                }
            }
            dl->flags |= 2;
            dirty = 1;
        }
    }
}
#pragma pop

void peParticleContainer::Stop() {
    if (started) {
        PreUpdate();
        started = 0;
        u32 flags = GC_AT(u32, data, 0);
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

static inline void setCull(GSgfxLayer* layer, s32 mode) {
    M2C_NAMED(layer, s32 *, 0xD8C, hw.cullMode) = mode;
    M2C_NAMED(layer, s32 *, 0x16B8, dirty[0].raster) |= 2;
    M2C_NAMED(layer, s32 *, 0x16A8, dirty[0].groups) |= 2;
    M2C_NAMED(layer, s32 *, 0x1770, dirty[1].raster) |= 2;
    M2C_NAMED(layer, s32 *, 0x1760, dirty[1].groups) |= 2;
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
    u32 flags = GC_AT(u32, c->data, 0);
    switch (M2C_NAMED(g_current_layer, s32 *, 0x28, id)) {
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
            u32 flags = GC_AT(u32, data, 0);
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
                vf = PE_DL_VF(dlp);
            } else {
                vf = 0;
            }
            if (tex) {
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 9, 3, buf, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xB, 3, buf + 0x30, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xC, 3, buf + 0x34, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xD, 3, uv, 4, 0x20);
            } else {
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 9, 3, buf, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xB, 3, buf + 0x30, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xD, 3, uv, 4, 0x20);
            }
            if (flags & 0x100000) {
                particleEngineSetupTevStages(0, tex, (flags & 0xC00000) == 0xC00000);
                M2C_NAMED(g_current_layer, s32 *, 0x1998, unk1998) = 0x80;
                M2C_NAMED(g_current_layer, GSgfxVF **, 0x199C, curVF) = vf;
                for (peNode* n = activeList; n != 0; n = PE_NODE_LINK28(n)) {
                    ((peParticleNode*)n)->Render(data, (GSgfxDL*)dl[cur], (char*)(&bufA)[cur]);
                }
            } else {
                particleEngineSetupTevStages(0, tex, 0);
                particleEngineSetupTexture(0, GC_AT(s32, data, 0x54), (flags >> 12) & 3, (flags >> 14) & 3,
                                           (flags & 0x80) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR,
                                           (flags & 0x100) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR);
                g_current_layer->dlDraw((GSgfxDL*)dl[cur]);
            }
            MarkForSwap();
        }
    }
}

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

#pragma push
#pragma dont_inline on
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
#pragma pop

void peParticleContainer::Start() {
    s32 temp_r31;

    if ((u8) THIS_F(u8 *, 0x19, started) == 0) {
        THIS_F(u8 *, 0x19, started) = 1U;
        temp_r31 = GC_AT(s32, THIS_F(s32 **, 0x58, data), 0);
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

peParticleContainer::~peParticleContainer() {
    if (sorted != 0) {
        delete[] sorted;
    }
    g_particle_debug_stats.unk4 -= 0x7C;
    g_particle_debug_stats.unk14 -= 0x7C;
}

extern "C++" {
extern "C++" {
extern "C++" {
extern "C++" {
extern "C++" {

extern "C++" {
#pragma push
#pragma dont_inline off
peParticleContainer::peParticleContainer(peEmitterNode* p0, _peParticle* p1, unsigned short p2)
    : peRenderContainer(p0, PE_NODE_SIZE(0x50, peParticleNodeData), p2, (GC_AT(u32, p1, 0) & 0x02000000) ? &g_ext_vertex_format : &g_vertex_format, (GSgfxPrimType)0x80, 4,
                        (GC_AT(u32, p1, 0) & 0x02000000) ? 0x38 : 0x34, (GC_AT(u32, p1, 0) >> 26) & 1) {
    peNode* node;
    u16 i;
    f32 u0;
    f32 v0;
    f32 u1;
    f32 v1;
    f32 scale = 0.0009765625f;
    f32* t = uv;

    sorted = 0;
    data = p1;
    u0 = OSs16tof32(GC_AT(s16, data, 0x44));
    u0 *= scale;
    v0 = OSs16tof32(GC_AT(s16, data, 0x46));
    v0 *= scale;
    u1 = OSs16tof32(GC_AT(s16, data, 0x48));
    u1 *= scale;
    v1 = OSs16tof32(GC_AT(s16, data, 0x4A));
    v1 *= scale;
    t[0] = u1;
    t[1] = v1;
    t[2] = u0;
    t[3] = v1;
    t[4] = u0;
    t[5] = v0;
    t[6] = u1;
    t[7] = v0;
    DCFlushRange(t, 0x20);
    if (GC_AT(u32, data, 0) & 0x80000) {
        sorted = new peNode*[p2];
    }
    for (node = freeList, i = 0; node != 0; node = PE_NODE_LINK28(node), i++) {
        PE_NODE_F(node, u16, 0x30) = i;
        PE_NODE_F(node, u16, 0x32) = i;
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
#pragma push
#pragma dont_inline off
#pragma auto_inline on
static inline f32 __peS16tof32(register const s16* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 3 }
#else
    ret = PSQ_LOAD(arg, 0, 3);
#endif
    return ret;
}

static inline f32 peS16tof32(s16 in) {
    s16 tmp = in;
    return __peS16tof32(&tmp);
}

static inline void __peF32tou8(register f32 arg, volatile register u8* out) {
#ifdef __MWERKS__
    asm { psq_st arg, 0(out), 1, 2 }
#else
    PSQ_STORE(out, 0, arg, 2);
#endif
}

static inline u8 peF32tou8(f32 in) {
    u32 out;
    __peF32tou8(in, (u8*)&out);
    return *(u8*)&out;
}

static inline void __peF32tou16(register f32 arg, volatile register u16* out) {
#ifdef __MWERKS__
    asm { psq_st arg, 0(out), 1, 3 }
#else
    PSQ_STORE(out, 0, arg, 3);
#endif
}

static inline u16 peF32tou16(f32 in) {
    u32 out;
    __peF32tou16(in, (u16*)&out);
    return *(u16*)&out;
}

#ifdef __MWERKS__
#define GX_WRITE_U16(v) (*(volatile u16*)0xCC008000 = (v))
#else
#define GX_WRITE_U16(v) (GXWGFifo.u16 = (v))
#endif
#ifdef __MWERKS__
#define PE_DL_R16(q, i) ((q)[i])
#define PE_TEXW(t, i) ((t)[i])
#else
#define PE_DL_R16(q, i) gc_rd16((const u8*)((q) + (i)))
#define PE_TEXW(t, i) ((s32)gc_rd32((const u8*)((t) + (i))))
#endif

struct peColor {
    u8 r, g, b, a;
};

static inline void peSetKColor(GSgfxLayer* layer, int id, peColor c) {
#ifdef __MWERKS__
    ((u32*)((u8*)layer + 0x14F4))[id] = *(u32*)&c;
#else
    *(u32*)&layer->hw.kcolor[id] = *(u32*)&c;
#endif
    M2C_NAMED(layer, u32 *, 0x16F8, dirty[0].kcolor) |= 1 << id;
    M2C_NAMED(layer, u32 *, 0x16A8, dirty[0].groups) |= 0x10;
    M2C_NAMED(layer, u32 *, 0x17B0, dirty[1].kcolor) |= 1 << id;
    M2C_NAMED(layer, u32 *, 0x1760, dirty[1].groups) |= 0x10;
}

struct peVtxDual {
    u8 pad0[0x34];
    peColor color2;
};

void peParticleNode::Render(_peParticle* part, GSgfxDL* dl, char* colors) {
    peVtxDual* colors_c = (peVtxDual*)colors;
    u32 flags = GC_AT(u32, part, 0);
    s32* tex = GC_AT(s32*, part, 0x54);
    u32 dual;
    u16 frame;
    frame = PE_NODE_F(this, u8, 0x34);
    dual = (flags >> 25) & 1;
    if (colors != NULL && (dl->flags & 1) == 1) {
        if (flags & 0x400000) {
            f32 range = peS16tof32(PE_TEXW(tex, 0));
            u32 blend = (flags >> 23) & 1;
            f32 count = range;
            if (blend) {
                count = range - 1.0f;
            }
            f32 alpha;
            f32 t;
            if (flags & 0x1000000) {
                t = (count * (M2C_FIELD(this, f32 *, 0) - M2C_FIELD(this, f32 *, 4))) / GC_AT(f32, part, 0x30);
            } else {
                t = GC_AT(f32, part, 0x30) * (count * (1.0f - M2C_FIELD(this, f32 *, 4) / M2C_FIELD(this, f32 *, 0)));
            }
            f32 pos = fmod(t + peS16tof32(frame), count);
            frame = peF32tou16(pos) % (u16)PE_TEXW(tex, 0);
            if (blend) {
                alpha = pos - peS16tof32(frame);
                alpha *= 255.0f;
                u8 a = peF32tou8(alpha);
                peColor kc;
                kc.r = kc.g = kc.b = kc.a = a;
                peSetKColor(g_current_layer, 0, kc);
                if (dual) {
                    peColor src = (colors_c)[PE_NODE_F(this, u16, 0x30)].color2;
                    kc.r = src.r;
                    kc.g = src.g;
                    kc.b = src.b;
                    kc.a = src.a;
                    peSetKColor(g_current_layer, 1, kc);
                }
                s32 t2 = PE_TEXW(tex, frame + 2);
                particleEngineSetupTexture(1, t2, (flags >> 12) & 3, (flags >> 14) & 3,
                                           (flags & 0x80) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR, (flags & 0x100) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR);
            }
        }
        s32 t1 = PE_TEXW(tex, frame + 1);
        particleEngineSetupTexture(0, t1, (flags >> 12) & 3, (flags >> 14) & 3, (flags & 0x80) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR,
                                   (flags & 0x100) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR);
        g_current_layer->beginSurface(4);
        u16* src;
        u16 ofs = PE_NODE_F(this, u16, 0x32) * 4;
        if (dl->flags & 1) {
            src = (u16*)(dl->data + ofs * dl->stride + 3);
        } else {
            src = NULL;
        }
        u16 n = 4;
        if (dual) {
            while (n--) {
                GX_WRITE_U16(PE_DL_R16(src, 0));
                GX_WRITE_U16(PE_DL_R16(src, 1));
                GX_WRITE_U16(PE_DL_R16(src, 2));
                GX_WRITE_U16(PE_DL_R16(src, 3));
                src += 4;
            }
        } else {
            while (n--) {
                GX_WRITE_U16(PE_DL_R16(src, 0));
                GX_WRITE_U16(PE_DL_R16(src, 1));
                GX_WRITE_U16(PE_DL_R16(src, 2));
                src += 3;
            }
        }
        g_current_layer->endSurface();
    }
}
#pragma pop
}
}
void peParticleNode::Start(peEmitterNode* emitter, _peParticle* particle, GSgfxDL* dl, _EmitParams* params) {
    u32 flags;
    u32 quad;
    f32 r;
    u16 offset;
    u16 base;
    u16* idx;
    u16 i;

    flags = GC_AT(u32, particle, 0);
    quad = (flags >> 25) & 1;
    if ((dl->flags & 1) == 1) {
        ((peNode*)this)->Start(emitter, params);
        PE_NODE_F(this, u8, 0x35) = 0;
        PE_NODE_F(this, u8, 0x36) = 1;
        r = HSD_Randf();
        PE_NODE_F(this, f32, 0x38) = GC_AT(f32, particle, 0xC) * r;
        PE_NODE_F(this, f32, 0x3C) = GC_AT(f32, particle, 0x10) * r;
        PE_NODE_F(this, f32, 0x38) += GC_AT(f32, particle, 4);
        PE_NODE_F(this, f32, 0x3C) += GC_AT(f32, particle, 8);
        if (flags & 0x40) {
            PE_NODE_F(this, f32, 0x40) = 6.2831855f * HSD_Randf();
        } else {
            PE_NODE_F(this, f32, 0x40) = 0.0f;
        }
        if ((flags & 0x20) && HSD_Randf() < 0.5f) {
            PE_NODE_F(this, u8, 0x35) |= 1;
        }
        PE_NODE_F(this, f32, 0x44) = GC_AT(f32, particle, 0x24);
        PE_NODE_F(this, f32, 0x48) = GC_AT(f32, particle, 0x2C) * HSD_Randf() + GC_AT(f32, particle, 0x28);
        if ((flags & 0x300000) == 0x300000) {
            f32 count = peS16tof32(PE_TEXW(GC_AT(s32*, particle, 0x54), 0));
            PE_NODE_F(this, u8, 0x34) = peF32tou8(count * HSD_Randf());
        } else {
            PE_NODE_F(this, u8, 0x34) = 0;
        }
        offset = PE_NODE_F(this, u16, 0x32) * 4;
        base = (u8)((quad != 0) + 13);
        base = base * (PE_NODE_F(this, u16, 0x30));
        if (dl->flags & 1) {
            idx = (u16*)(dl->data + offset * dl->stride + 3);
        } else {
            idx = NULL;
        }
        i = 0;
        if (quad != 0) {
            for (; i < 4; i++) {
                PE_DL_W16(idx, u16, 0, base + i * 3);
                PE_DL_W16(idx, u16, 1, base);
                PE_DL_W16(idx, u16, 2, base);
                PE_DL_W16(idx, u16, 3, i * 2);
                idx = idx + 4;
            }
        } else {
            for (; i < 4; i++) {
                PE_DL_W16(idx, u16, 0, base + i * 3);
                PE_DL_W16(idx, u16, 1, base);
                PE_DL_W16(idx, u16, 2, i * 2);
                idx = idx + 3;
            }
        }
        dl->flags |= 2;
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
    u32 spinFirst = flags & 0x10;
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
        *(u32*)(out + 0x30) = *(u32*)&c;
        if (hasColor2) {
            peColorSplineGetValue((u8*)&c, p->color2, t);
            *(u32*)(out + 0x34) = *(u32*)&c;
        }
    }
}
}
}
}
}
}
}
