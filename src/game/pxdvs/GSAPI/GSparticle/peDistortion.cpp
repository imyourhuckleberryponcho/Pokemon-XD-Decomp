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
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
#ifdef __MWERKS__
    s32 dlDraw(GSgfxDL*);
#else
    void dlDraw(GSgfxDL* p0);
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
struct _peDistortion {
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
    s32 MoveNode(peNode*, peNode*);
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
class peDistortionContainer : public peRenderContainer {
public:
    PE_DISTORTION_CONTAINER_MEMBERS
    void hideNode(struct peNodeView* n);
    bool updateNode(struct peNodeView* n, f32 dt);

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
s32 particleEngineSetupBlendMode(s32);
s32 particleEngineSetupTevStages(s32, s32, s32);
enum GStexFilter { GS_TEXFILTER_NEAR = 0, GS_TEXFILTER_LINEAR = 2 };
void particleEngineSetupTexture(u8, s32, s32, s32, s32, s32);
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
extern Vec g_CameraPosition;
extern Vec g_CameraSideDir;
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
extern Vec xAxisVector;
extern Vec yAxisVector;
extern s32 this_;
}

struct peXformP {
    Vec pos;
    Quaternion rot;
    Vec scale;
};
struct peSplineHdr {
    u8 flags;
    gc_bef32 value;
    gc_bef32 time;
};
struct GSColor {
    u8 r, g, b, a;
};

struct peDistortionDef {
    gc_be32 flags;
    u8 pad4[0x10];
    gc_ptr32(peSpline) scaleX;
    gc_ptr32(peSpline) scaleY;
    gc_bef32 offsetX;
    gc_bef32 offsetY;
    gc_bef32 spinScale;
    u8 pad28[8];
    gc_ptr32(peSpline) spin;
    gc_ptr32(peSpline) alpha;
};

struct peDistortionNodeData {
    f32 life0;
    f32 life;
    Vec pos;
    Vec vel;
    peXformP* xform;
    u8 pad24[0x4];
    void* slot28;
    void* slot2C;
    u16 index;
    u16 spin;
    f32 sizeX;
    f32 sizeY;
    f32 rot;
    f32 rotOffset;
    f32 rotSpeed;
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

static inline void projectToNode(Vec* v, Vec* p, peXformP* xf) {
    Quaternion qi;
    Mtx m;
    Vec t;
    PSQUATInverse(&xf->rot, &qi);
    quatToMtx(m, qi);
    PSMTXMultVecSR(m, v, &t);
    *p = t;
    p->x *= xf->scale.x;
    p->y *= xf->scale.y;
    p->z *= xf->scale.z;
    rotateBy(p, &xf->rot);
    PSVECScale(v, v, PSVECDotProduct(v, p));
}

static inline void spinAround(Vec* up, Vec* right, Vec* axis, f32 angle) {
    Quaternion q;
    C_QUATRotAxisRad(&q, axis, angle);
    rotateBy(up, &q);
    rotateBy(right, &q);
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

struct peDLView {
    u16 flags;
    u16 stride;
    u8* buf;
    u32 size;
    GSgfxVF* vf;
};

struct peNodeView {
    u8 pad0[0x20];
    void* slot20;
    u8 pad24[0x4];
    peNodeView* next;
    void* slot2C;
    u16 vtx;
};

inline void peDistortionContainer::hideNode(peNodeView* n) {
    peDLView* d = (peDLView*)dl[cur];
    u16* idx;
    u16 off = n->vtx * 4;
    if (d->flags & 1) {
        idx = (u16*)(d->buf + off * d->stride + 3);
    } else {
        idx = NULL;
    }
    for (u16 i = 4; i-- != 0;) {
        idx[0] = 0xffff;
        idx[1] = 0xffff;
        idx[2] = 0xffff;
        idx += 3;
    }
    d->flags |= 2;
}

void peDistortionContainer::Stop() {
    if (started) {
        PreUpdate();
        started = 0;
        peNodeView* n = (peNodeView*)activeList;
        u32 flags = *PE_EMITTER_DEF_RAW(emitter, u32**);
        if (flags & 0x800000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, false);
        }
        if (flags & 0x1000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, false);
        }
        if (flags & 0x2000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, false);
        }
        for (; n != NULL; n = n->next) {
            hideNode(n);
        }
        RemoveAll();
        ResetSwap();
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

#define PE_DLV(p) ((peDLView*)(p))

static inline bool canRender(peDistortionContainer* c) {
    if (!c->started) {
        return false;
    }
    u32 flags = GC_AT(u32, c->data, 0);
    if (c->count == 0) {
        return false;
    }
    if (g_render_pass != 1) {
        return false;
    }
    switch (M2C_NAMED(g_current_layer, s32 *, 0x28, id)) {
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
    u32 temp_r31;
    GSgfxVF *var_r31;

    if (THIS_F(u8 *, 0x19, started)) {
        if (canRender(this)) {
            ((peRenderContainer*)((peRenderContainer *) this))->ResolveMultipleSwap();
            temp_r31 = GC_AT(u32, THIS_F(u8 **, 0x54, data), 0);
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
            particleEngineSetupBlendMode(0);
            particleEngineSetupTevStages(0, 0, 0);
            particleEngineSetupTexture(0, GC_AT(s32, THIS_F(u8 **, 0x54, data), 0x60), temp_r31 & 3, (temp_r31 >> 2U) & 3, (temp_r31 & 0x20) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR, (temp_r31 & 0x40) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR);
            u8* verts = (&bufA)[cur];
            u8* dlp = dl[cur];
            if (PE_DLV(dlp)->flags & 1) {
                var_r31 = PE_DLV(dlp)->vf;
            } else {
                var_r31 = NULL;
            }
            GSGFX_VF_SET_ARRAY_NATIVE((GSgfxVF*)(var_r31), 9, 3, (void*)(verts), 4, bufSize);
            GSGFX_VF_SET_ARRAY_NATIVE((GSgfxVF*)(var_r31), 0xB, 3, (void*)(verts + 0x30), 4, bufSize);
            GSGFX_VF_SET_ARRAY_NATIVE((GSgfxVF*)(var_r31), 0xD, 3, (void*)&THIS_F(u8 *, 0x58, uv), 4, 0x20);
            ((GSgfxLayer*)(g_current_layer))->dlDraw((GSgfxDL*)dl[cur]);
            ((peRenderContainer*)((peRenderContainer *) this))->MarkForSwap();
        }
    }
}
}

extern "C++" {

extern "C++" {
extern "C++" {

extern "C++" {
inline bool peDistortionContainer::updateNode(peNodeView* node, f32 dt) {
    char* buf = (char*)(&bufA)[cur];
    peDistortionNodeData* n = (peDistortionNodeData*)node;
    peDistortionDef* p = (peDistortionDef*)data;
    peEmitterNode* e = emitter;
    if (buf == NULL) {
        return false;
    }
    if ((((peDLView*)dl[cur])->flags & 1) != 1) {
        return false;
    }
    if (!((peNode*)n)->Update(e, dt)) {
        return false;
    }
    f32 t = 1.0f - n->life / n->life0;
    if (p->flags & 0x200) {
        n->rotOffset = p->spinScale * evalSpline(p->spin, t);
    }
    n->rotOffset = n->rotSpeed * dt + n->rotOffset;
    ((peDistortionNode*)n)->UpdateRenderData(e, (_peDistortion*)p, buf, t);
    return true;
}

void peDistortionContainer::Update(float dt) {
    if (started) {
        peNodeView* n = (peNodeView*)activeList;
        while (n != NULL) {
            peNodeView* next = n->next;
            if (!updateNode(n, dt)) {
                hideNode(n);
                RemoveNode((peNode*)n);
            }
            n = next;
        }
    }
}
}

extern "C++" {
struct peDistortionDefE {
    gc_be32 flags;
    gc_bef32 sizeXBase;
    gc_bef32 sizeYBase;
    gc_bef32 sizeXRange;
    gc_bef32 sizeYRange;
    u8 pad14[0x10];
    gc_bef32 rotBase;
    gc_bef32 spinBase;
    gc_bef32 spinRange;
};

struct _EmitParamsD {
    u8 data[0x48];
};

u16 peDistortionContainer::Emit(unsigned short count) {
    if (!started) {
        return 0;
    }
    peDLView* d;
    u16 left = CreateNodes(count);
    _EmitParamsD* params = (_EmitParamsD*)g_emitParams;
    peNodeView* node = (peNodeView*)activeList;
    u32 flags;
    u16 created = left;
    while (left != 0) {
        peDistortionDefE* p = (peDistortionDefE*)data;
        peNodeView* next = node->next;
        d = (peDLView*)dl[cur];
        flags = p->flags;
        if ((d->flags & 1) == 1) {
            peDistortionNodeData* n = (peDistortionNodeData*)node;
            ((peNode*)n)->Start(emitter, (_EmitParams*)params);
            f32 r = HSD_Randf();
            n->sizeX = p->sizeXRange * r;
            n->sizeY = p->sizeYRange * r;
            n->sizeX += p->sizeXBase;
            n->sizeY += p->sizeYBase;
            if (flags & 0x80) {
                n->rot = 6.2831855f * HSD_Randf();
            } else {
                n->rot = 0.0f;
            }
            if ((flags & 0x1000) && HSD_Randf() < 0.5f) {
                n->spin |= 1;
            }
            n->rotOffset = p->rotBase;
            n->rotSpeed = HSD_Randf() * p->spinRange + p->spinBase;
            {
                u16 base = n->index * 13;
                u16 off = n->index * 4;
                u16* idx;
                if (d->flags & 1) {
                    idx = (u16*)(d->buf + off * d->stride + 3);
                } else {
                    idx = NULL;
                }
                idx[0] = base;
                idx[1] = base;
                idx[2] = 0;
                idx[3] = base + 3;
                idx[4] = base;
                idx[5] = 2;
                idx[6] = base + 6;
                idx[7] = base;
                idx[8] = 4;
                idx[9] = base + 9;
                idx[10] = base;
                idx[11] = 6;
            }
            d->flags |= 2;
        }
        node = next;
        left--;
        params++;
    }
    return created;
}
}

extern "C++" {
void peDistortionContainer::Start() {
    s32 temp_r31;

    if ((u8) THIS_F(u8 *, 0x19, started) == 0) {
        THIS_F(u8 *, 0x19, started) = 1U;
        temp_r31 = GC_AT(s32, PE_EMITTER_DEF_M2C(THIS_F(u8 **, 0, emitter), s32 **), 0);
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
    : peRenderContainer(p0, PE_NODE_SIZE(0x48, peDistortionNodeData), p2, &g_vertex_format, (GSgfxPrimType)0x80, 4, 0x34, (GC_AT(u32, p1, 0) >> 14) & 1) {
    peNode* node;
    u16 i;
    _peDistortion* d;

    data = p1;
    d = data;
    uv[0] = GC_AT(f32, d, 0x58);
    uv[1] = GC_AT(f32, d, 0x5C);
    uv[2] = GC_AT(f32, d, 0x50);
    uv[3] = GC_AT(f32, d, 0x5C);
    uv[4] = GC_AT(f32, d, 0x50);
    uv[5] = GC_AT(f32, d, 0x54);
    uv[6] = GC_AT(f32, d, 0x58);
    uv[7] = GC_AT(f32, d, 0x54);
    DCFlushRange(uv, 0x20);
    i = 0;
    for (node = freeList; node != 0; node = PE_NODE_LINK28(node)) {
        PE_NODE_F(node, u16, 0x30) = i;
        i++;
    }
    g_particle_debug_stats.unk4 += 0x78;
    g_particle_debug_stats.unk14 += 0x78;
}
#pragma pop
}
void peDistortionNode::UpdateRenderData(peEmitterNode* emitter, _peDistortion* dist, char* out, float t) {
    peDistortionNodeData* n = (peDistortionNodeData*)this;
    peEmitterNodeData* e = (peEmitterNodeData*)emitter;
    peDistortionDef* p = (peDistortionDef*)dist;
    u32 flags = p->flags;
    Quaternion pos;
    Vec up;
    Vec v;
    Vec off;
    Vec fwd;
    f32 angle;
    Vec right;
    Quaternion q;
    Vec euler;

    {
        f32 py = n->pos.y * n->xform->scale.y;
        f32 px = n->pos.x * n->xform->scale.x;
        f32 pz = n->pos.z * n->xform->scale.z;
        pos.x = px;
        pos.y = py;
        pos.z = pz;
    }
    rotateBy((Vec*)&pos, &n->xform->rot);
    PSVECAdd((Vec*)&pos, &n->xform->pos, (Vec*)&pos);

    if (flags & 0x100) {
        if (flags & 0x400) {
            Vec unused;
            vecSub(&fwd, &g_CameraPosition, (Vec*)&pos);
            PSVECNormalize(&fwd, &fwd);
            vecCross(&right, &fwd, &g_CameraUpDir);
            PSVECNormalize(&right, &right);
            PSVECCrossProduct(&fwd, &right, &unused);
        } else {
            up = g_CameraUpDir;
            right = g_CameraSideDir;
        }
    } else {
        right = xAxisVector;
        up = yAxisVector;
        if (*e->params & 0x400) {
            f32 vx;
            f32 vz;
            vz = n->vel.z;
            vx = n->vel.x;
            f32 h = sqrtf(vx * vx + vz * vz);
            euler.x = atan2(-n->vel.y, h);
            euler.y = atan2(vx, vz);
            euler.z = 0.0f;
            EulerToQuat(&euler, &q);
            rotateBy(&right, &q);
            rotateBy(&up, &q);
        }
        rotateBy(&right, &n->xform->rot);
        rotateBy(&up, &n->xform->rot);
    }
    vecCross(&fwd, &up, &right);
    angle = 0.0f;
    if (n->spin & 1) {
        angle -= n->rot + n->rotOffset;
    } else {
        angle += n->rot + n->rotOffset;
    }
    u32 spinFirst = flags & 0x8000;
    if (spinFirst && (angle < 0.0f ? -angle : angle) > 0.00001f) {
        spinAround(&up, &right, &fwd, angle);
    }
    projectToNode(&right, &v, n->xform);
    projectToNode(&up, &v, n->xform);
    PSVECScale(&right, &right, n->sizeX * evalSpline(p->scaleX, t));
    PSVECScale(&up, &up, n->sizeY * evalSpline(p->scaleY, t));
    if (!spinFirst && (angle < 0.0f ? -angle : angle) > 0.00001f) {
        spinAround(&up, &right, &fwd, angle);
    }
    bool hasOff = (flags >> 11) & 1;
    if (hasOff) {
        Vec offY;
        vecScale(&off, &right, p->offsetX);
        PSVECScale(&up, &offY, p->offsetY);
        off.x *= offY.x;
        off.y *= offY.y;
        off.z *= offY.z;
    }
    out += n->index * 0x34;
    v.x = -right.x;
    v.y = -right.y;
    v.z = -right.z;
    PSVECSubtract(&v, &up, &v);
    emitCorner(out, &v, &off, hasOff, (Vec*)&pos);
    vecSub(&v, &right, &up);
    emitCorner(out + 0xc, &v, &off, hasOff, (Vec*)&pos);
    vecAdd(&v, &right, &up);
    emitCorner(out + 0x18, &v, &off, hasOff, (Vec*)&pos);
    vecSub(&v, &up, &right);
    emitCorner(out + 0x24, &v, &off, hasOff, (Vec*)&pos);
    {
        GSColor c;
        c.b = 0xff;
        c.g = 0xff;
        c.r = 0xff;
        c.a = OSf32tou8(255.0f * e->color[3] * evalSpline(p->alpha, t));
        *(u32*)(out + 0x30) = *(u32*)&c;
    }
}
}
}
}
