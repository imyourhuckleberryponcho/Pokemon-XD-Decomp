#ifndef __MWERKS__
#include <game/psq.h>
#endif
#include <dolphin/types.h>
#include <game/gcdata.h>
#include <game/pecontainer.h>
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
struct GSvec;
typedef f32 Mtx[3][4];
struct Quaternion;
struct Vec;
struct _EmitParams;
struct _peDistortion;
struct _peEmitter;
struct _peModel;
struct _peParticle;
struct _peParticleStrip;
struct _pePositionFunction;
struct _peShape;
struct peColorSpline;
class peContainer;
class peDistortionContainer;
class peEmitterContainer;
struct peEmitterNode;
class peModelContainer;
struct peNode;
class peParticleContainer;
class peParticleStripContainer;
class peShapeContainer;
struct peSpline;
struct peXform;

extern "C++" {
struct GSvec {
    f32 x, y, z;
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
struct _peEmitter {
    u8 _draft[1];
};
struct _peModel {
    u8 _draft[1];
};
struct _peParticle {
    u8 _draft[1];
};
struct _peParticleStrip {
    u8 _draft[1];
};
struct _pePositionFunction {
    gc_be16 flags;
    union {
        struct {
            gc_vec(Vec) center;
            gc_vec(Vec) spread;
            gc_vec(Vec) dir;
            gc_vec(Vec) axis;
            gc_bef32 radBase;
            gc_bef32 radRange;
            gc_bef32 spin;
        } sphere;
        struct {
            gc_vec(Vec) start;
            gc_vec(Vec) axis;
            gc_bef32 radBase;
            gc_bef32 radRange;
            gc_bef32 angBase;
            gc_bef32 angRange;
            gc_bef32 angSpeed;
            gc_bef32 spin;
        } ring;
        struct {
            gc_vec(Vec) center;
            gc_vec(Vec) dir;
            gc_vec(Vec) axis;
            gc_bef32 radBase;
            gc_bef32 radRange;
            gc_bef32 spin;
        } line;
    };
};
struct _peShape {
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
    virtual u16 Emit(unsigned short n);
    virtual void Update(float dt);
    virtual void Render();
    virtual void Stop();

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
#ifdef __MWERKS__
    s32 MoveNode(peNode*, peNode*);
#else
    void MoveNode(peNode* node, peNode* after);
#endif
};
class peEmitterContainer : public peContainer {
public:
    PE_EMITTER_CONTAINER_MEMBERS
    peEmitterContainer(peEmitterNode* e, _peEmitter* em, unsigned short n);
    virtual ~peEmitterContainer();
    virtual void Stop();
    virtual void Render();
    virtual void PreUpdate();
    virtual void Update(float);
    virtual u16 Emit(unsigned short);
    u8 DoRender();
};
class peShapeContainer : public peContainer {
public:
    PE_SHAPE_CONTAINER_MEMBERS
    peShapeContainer(peEmitterNode*, _peShape*, unsigned short);
    virtual ~peShapeContainer();
};
class peModelContainer : public peContainer {
public:
    PE_MODEL_CONTAINER_MEMBERS
    peModelContainer(peEmitterNode*, _peModel*, unsigned short);
    virtual ~peModelContainer();
};
class peDistortionContainer : public peContainer {
public:
    PE_RENDER_MEMBERS
    PE_DISTORTION_CONTAINER_MEMBERS
    peDistortionContainer(peEmitterNode*, _peDistortion*, unsigned short);
    virtual ~peDistortionContainer();
};
class peParticleStripContainer : public peContainer {
public:
    PE_RENDER_MEMBERS
    PE_STRIP_CONTAINER_MEMBERS
    peParticleStripContainer(peEmitterNode*, _peParticleStrip*, unsigned short);
    virtual ~peParticleStripContainer();
};
class peParticleContainer : public peContainer {
public:
    PE_RENDER_MEMBERS
    PE_PARTICLE_CONTAINER_MEMBERS
    peParticleContainer(peEmitterNode*, _peParticle*, unsigned short);
    virtual ~peParticleContainer();
};
struct peEmitterNode {
    u8 _draft[1];
    void Release();
    void CreateWorldParams();
    void CreateParameters(unsigned short, float);
    void Start(peEmitterNode*, _peEmitter*, _EmitParams*);
    void Render(_peEmitter*);
    static void GetPositionParameter(GSvec*, GSvec*, _pePositionFunction*, float);
    void Init(_peEmitter*);
    u8 Update(peEmitterNode*, _peEmitter*, float);
    void Stop(_peEmitter*);
    void SetLastLoop();
};
struct peNode {
    u8 _draft[1];
    void Start(peEmitterNode*, _EmitParams*);
    bool Update(peEmitterNode*, float);
};
struct peSpline {
    u8 _draft[1];
};
struct peXform {
    u8 _draft[1];
};

extern "C" {
void C_QUATLerp(const Quaternion* p, const Quaternion* q, Quaternion* r, f32 t);
void C_QUATRotAxisRad(Quaternion* r, const Vec* axis, f32 rad);
int EulerToQuat(Vec* euler, Quaternion* q);
f32 HSD_Randf(void);
asm void PSMTXMultVecSR(const register Mtx m, const register Vec* src, register Vec* dst);
void PSMTXQuat(register Mtx m, const register Quaternion* q);
void PSQUATInverse(const register Quaternion* src, register Quaternion* inv);
void PSQUATMultiply(const register Quaternion* p, const register Quaternion* q, register Quaternion* pq);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
asm f32 PSVECDotProduct(const register Vec* a, const register Vec* b);
void PSVECNormalize(const register Vec* src, register Vec* unit);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
f32 PSVECSquareMag(const register Vec* v);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double atan2(double y, double x);
void peColorSplineGetValue(u8* out, peColorSpline* s, f32 t);
void peNodeTransformsConcat(peXform* out, peXform* a, peXform* b, u32 useGfx);
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

#ifdef __MWERKS__
inline float sqrtf(float x) {
#else
static inline float sqrtf(float x) {
#endif
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
extern void* g_current_layer;
extern _EmitParams* g_emitParams;
extern u16 g_maxEmitParams;
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

struct peXformE {
    Vec pos;
    Quaternion rot;
    Vec scale;
};

struct _EmitParamsE {
    f32 life;
    f32 speed;
    Vec pos;
    Vec vel;
    peXformE xf;
};

struct peEmitterDefE {
    gc_be32 flags;
    gc_be32 maxNodes;
    gc_bef32 rate;
    gc_bef32 countBase;
    gc_bef32 countRange;
    gc_ptr32(peSpline) countSpline;
    gc_bef32 start;
    gc_bef32 duration;
    gc_bef32 lifeBase;
    gc_bef32 lifeRange;
    gc_bef32 length;
    gc_bef32 speedBase;
    gc_bef32 speedRange;
    gc_be16 posFlags;
    u8 pad36[0x3e];
    gc_be16 velFlags;
    u8 pad76[2];
    gc_vec(Vec) dir;
    gc_vec(Vec) axis;
    gc_bef32 magBase;
    gc_bef32 magRange;
    gc_bef32 coneBase;
    gc_bef32 coneRange;
    u8 padA0[0xc];
    gc_vec(Vec) vAC;
    gc_ptr32(peSpline) vACSpline[3];
    gc_vec(Vec) vC4;
    gc_ptr32(peSpline) vC4Spline[3];
    gc_vec(Vec) euler;
    gc_ptr32(peSpline) eulerSpline[3];
    gc_vec(Vec) spinBase;
    gc_vec(Vec) spinRange;
    gc_ptr32(peSpline) spinSpline[3];
    gc_vec(Vec) scale;
    gc_ptr32(peSpline) scaleSpline[3];
    gc_ptr32(peColorSpline) color;
    gc_ptr32(peSpline) alpha;
    gc_ptr32(struct peEffectItemE) items;
};

struct peEffectItemE {
    gc_be32 unk0;
    gc_be32 type;
    gc_ptr32(void) data;
    gc_ptr32(peEffectItemE) next;
};

struct peEmitterNodeE {
    f32 life0;
    f32 life;
    u8 pad8[0xc];
    Vec pos;
    peXformE* xf;
    u8 pad24[0x4];
    void* slot28;
    void* slot2C;
    f32 time;
    f32 emitAcc;
    f32 color[4];
    u16 flags;
    u16 emitted;
    Vec scaleBase;
    Vec scale;
    Quaternion rot;
    Vec unk74;
    Quaternion rot2;
    Vec spin;
    Vec unk9C;
    peXformE cur;
    peXformE prev;
    f32 depth;
    peEmitterDefE* def;
    peContainer* containers;
};

#ifdef __MWERKS__
#define PEC(x, T, off, m) M2C_FIELD(x, T, off)
#define PEN(x, T, off, m) M2C_FIELD(x, T, off)
#define PECR(x, T, off, m) (*(T)((u8*)(x) + (off)))
#define PENR(x, T, off, m) (*(T)((u8*)(x) + (off)))
#define PE_EMITTER_NODE_SIZE 0x104
#define PED(x, T, off, m) M2C_FIELD(x, T, off)
#define PEI(x, T, off, m) M2C_FIELD(x, T, off)
#define PE_LAYER_ID(l) M2C_FIELD(l, s32 *, 0x28)
#else
extern "C++" { template <class P> struct pe_pointee;
template <class X> struct pe_pointee<X*> { typedef X type; }; }
#define PED(x, T, off, m) ((pe_pointee<T>::type)(((peEmitterDefE*)(x))->m))
#define PEI(x, T, off, m) ((pe_pointee<T>::type)(((peEffectItemE*)(x))->m))
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxLayerType { GSgfxLayerType_draft_dummy };
#include <game/gsgfxlayer.h>
#define PE_LAYER_ID(l) (*(s32*)&((GSgfxLayerData*)(l))->id)
#define PEC(x, T, off, m) (*(T)&((peEmitterContainer*)(x))->m)
#define PEN(x, T, off, m) (*(T)&((peEmitterNodeE*)(x))->m)
#define PECR PEC
#define PENR PEN
#define PE_EMITTER_NODE_SIZE sizeof(peEmitterNodeE)
#endif
inline peEmitterContainer::peEmitterContainer(peEmitterNode* e, _peEmitter* em, unsigned short n) : peContainer(e, PE_EMITTER_NODE_SIZE, n) {
    peEmitterNode* node;
    peEmitterNode* next;

    data = em;
    node = (peEmitterNode*)freeList;
    while (node != 0) {
        next = PEN(node, peEmitterNode **, 0x28, slot28);
        node->Init(em);
        node = next;
    }
    g_particle_debug_stats.unk4 += 0x24;
    g_particle_debug_stats.unk14 += 0x24;
}

extern s32 g_render_pass;
extern Vec unitScaleVector;
extern s32 this_;
}
extern "C++" {
void* operator new(size_t);
}

void peEmitterContainer::Stop() {
    u8 *var_r31;
    u8 *temp_r30;
    u8 *var_r3;

    if ((u8) PEC(this, u8 *, 0x19, started) != 0) {
        ((peContainer*)this)->PreUpdate();
        PEC(this, u8 *, 0x19, started) = 0U;
        var_r3 = PEC(this, u8 **, 0x10, activeList);
        while (var_r3 != NULL) {
            temp_r30 = PEN(var_r3, u8 **, 0x28, slot28);
            var_r31 = PEN(var_r3, u8 **, 0x100, containers);
            while (var_r31 != NULL) {
                ((peContainer*)var_r31)->Stop();
                var_r31 = PEC(var_r31, u8 **, 0x4, next);
            }
            var_r3 = temp_r30;
        }
        ((peContainer*)((peContainer *) this))->RemoveAll();
    }
}
}

extern "C++" {
void peEmitterContainer::Render() {
    u8 *var_r31;
    u8 *var_r30;

    if (((u8) PEC(this, u8 *, 0x19, started) != 0) && (((peEmitterContainer*)(this))->DoRender() != 0)) {
        for (var_r30 = PEC(this, u8 **, 0x10, activeList); var_r30 != NULL; var_r30 = PEN(var_r30, u8 **, 0x28, slot28)) {
            var_r31 = PEN(var_r30, u8 **, 0x100, containers);
            if ((u16) PEN(var_r30, u16 *, 0x4A, emitted) == 0) {
                continue;
            } else {
                while (var_r31 != NULL) {
                    ((peContainer*)var_r31)->Render();
                    var_r31 = PEC(var_r31, u8 **, 0x4, next);
                }
            }
        }
    }
}
}

extern "C++" {
u8 peEmitterContainer::DoRender() {
    if (started == 0) {
        return 0;
    }
    u32 flags = GC_AT(u32, data, 0);
    if (count == 0) {
        return 0;
    }
    if (flags & 0x80000000) {
        return 0;
    }
    switch (g_render_pass) {
    case 0:
        if (!(flags & 0x800)) {
            return 0;
        }
        break;
    case 1:
        if (!(flags & 0x1000)) {
            return 0;
        }
        break;
    default:
        return 0;
    }
    switch (PE_LAYER_ID(g_current_layer)) {
    case 0:
        if (flags & 0x2000) {
            return 1;
        }
        break;
    case 2:
        if (flags & 0x4000) {
            return 1;
        }
        if (!(flags & 0x0380E000)) {
            return 1;
        }
        break;
    case 4:
        if (flags & 0x8000) {
            return 1;
        }
        break;
    case 1:
        if (flags & 0x800000) {
            return 1;
        }
        break;
    case 3:
        if (flags & 0x01000000) {
            return 1;
        }
        break;
    case 5:
        if (flags & 0x02000000) {
            return 1;
        }
        break;
    default:
        return 0;
    }
    return 0;
}
}

void peEmitterContainer::Update(float dt) {
    u8* child;
    peNode* node;
    peNode* next;
    peNode* pos;
    peNode* prev;
    f32 depth;

    if (PECR(this, u8*, 0x19, started) == 0) {
        return;
    }
    for (node = PECR(this, peNode**, 0x10, activeList); node != NULL; node = next) {
        next = PENR(node, peNode**, 0x28, slot28);
        if (!((peEmitterNode*)node)->Update(PECR(this, peEmitterNode**, 0x0, emitter), PECR(this, _peEmitter**, 0x20, data), dt)) {
            for (child = PENR(node, u8**, 0x100, containers); child != NULL; child = PECR(child, u8**, 0x4, next)) {
                ((peContainer*)child)->Stop();
            }
            ((peContainer*)this)->RemoveNode(node);
        }
    }
    if (PECR(this, u8*, 0x19, started) != 0 && (*PECR(this, u32**, 0x20, data) & 0x40000) && PECR(this, u16*, 0x14, count) >= 2) {
        for (node = *(peNode**)(PECR(this, u8**, 0x10, activeList) + 0x28); node != NULL; node = next) {
            depth = PENR(node, f32*, 0xF8, depth);
            pos = node;
            for (prev = PENR(node, peNode**, 0x2C, slot2C); prev != NULL && PENR(prev, f32*, 0xF8, depth) < depth;
                 prev = PENR(prev, peNode**, 0x2C, slot2C)) {
                pos = prev;
            }
            next = PENR(node, peNode**, 0x28, slot28);
            if (pos != node) {
                ((peContainer*)this)->MoveNode(node, pos);
            }
        }
    }
}

extern "C++" {
u16 peEmitterContainer::Emit(unsigned short count) {
    u16 var_r31;
    _EmitParams *var_r30;
    peEmitterNode *var_r3;
    peEmitterNode *temp_r29;
    u16 temp_r28;

    if ((u8) PEC(this, u8 *, 0x19, started) == 0) {
        return 0U;
    }
    var_r31 = ((peContainer*)this)->CreateNodes(count);
    var_r30 = g_emitParams;
    var_r3 = PEC(this, peEmitterNode **, 0x10, activeList);
    temp_r28 = var_r31;
    while (var_r31 != 0) {
        temp_r29 = PEN(var_r3, peEmitterNode **, 0x28, slot28);
        ((peEmitterNode*)(var_r3))->Start((peEmitterNode*)(PEC(this, peEmitterNode **, 0x0, emitter)), (_peEmitter*)(PEC(this, _peEmitter **, 0x20, data)), (_EmitParams*)(var_r30));
        var_r3 = temp_r29;
        var_r31 -= 1;
        var_r30 += 0x48;
    }
    return temp_r28;
}
}

extern "C++" {
extern "C++" {
#pragma peephole off
#pragma peephole reset
}

extern "C++" {
void peEmitterContainer::PreUpdate() {
    u8 *var_r3;

    var_r3 = PED(PEC(this, u8 **, 0x20, data), u8 **, 0x138, items);
    while (var_r3 != NULL) {
        var_r3 = PEI(var_r3, u8 **, 0xC, next);
    }
}
}

extern "C++" {
peEmitterContainer::~peEmitterContainer() {
    peContainer* child;
    peContainer* nextChild;
    peNode* node;
    peNode* next;

    node = freeList;
    while (node != 0) {
        next = PEN(node, peNode **, 0x28, slot28);
        child = PEN(node, peContainer **, 0x100, containers);
        while (child != 0) {
            nextChild = child->next;
            child->Stop();
            delete child;
            child = nextChild;
        }
        PEN(node, peContainer **, 0x100, containers) = 0;
        node = next;
    }
    g_particle_debug_stats.unk4 -= 0x24;
    g_particle_debug_stats.unk14 -= 0x24;
}
}

extern "C++" {
void peEmitterNode::Release() {
    u8 *temp_r31;
    u8 *var_r30;

    var_r30 = PEN(this, u8 **, 0x100, containers);
    while (var_r30 != NULL) {
        temp_r31 = (u8*)((peContainer*)var_r30)->next;
        ((peContainer*)var_r30)->Stop();
        delete (peContainer*)var_r30;
        var_r30 = temp_r31;
    }
    PEN(this, u8 **, 0x100, containers) = NULL;
}
}

typedef f32 PeMtx[3][4];

static inline void peMtxQuat(PeMtx m, Quaternion* q) {
    PSMTXQuat(m, q);
}

static inline void peMtxMultVecSR(PeMtx m, Vec* src, Vec* dst) {
    PSMTXMultVecSR(m, src, dst);
}

static inline void quatToMtxE(PeMtx m, Quaternion q) {
    peMtxQuat(m, &q);
}

static inline void rotateForwardE(Vec* v, Quaternion* q) {
    PeMtx m;
    peMtxQuat(m, q);
    peMtxMultVecSR(m, v, v);
}

static inline void rotateInverseE(Vec* v, Quaternion* rot) {
    PeMtx m;
    Quaternion q;
    Quaternion t;
    PSQUATInverse(rot, &q);
    t = q;
    peMtxQuat(m, &t);
    peMtxMultVecSR(m, v, v);
}

static inline void divScaleE(Vec* v, Vec* s) {
    if (0.0f != s->x) {
        v->x /= s->x;
    }
    if (0.0f != s->y) {
        v->y /= s->y;
    }
    if (0.0f != s->z) {
        v->z /= s->z;
    }
}

static inline void lerpVecE(Vec* dst, Vec* a, Vec* b, f32 t) {
    Vec r;
    Vec d;
    PSVECSubtract(a, b, &d);
    r = d;
    PSVECScale(&r, &r, t);
    PSVECAdd(&r, b, &r);
    f32 z, y, x;
    x = r.x;
    y = r.y;
    z = r.z;
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

static inline f32 __OSu16tof32E(register const u16* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 3 }
#else
    ret = PSQ_LOAD(arg, 0, 3);
#endif
    return ret;
}

static inline f32 u16tof32E(u16 v) {
    return __OSu16tof32E(&v);
}

static inline void vecScaleE(Vec* dst, Vec* a, f32 k) {
    Vec t;
    PSVECScale(a, &t, k);
    f32 z, y, x;
    x = t.x;
    y = t.y;
    z = t.z;
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

static inline void mtxMultVecSRE(Vec* dst, PeMtx m, Vec* a) {
    Vec t;
    peMtxMultVecSR(m, a, &t);
    f32 z, y, x;
    x = t.x;
    y = t.y;
    z = t.z;
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

static inline f32 absE(f32 x) {
    if (x < 0.0f) {
        x = -x;
    }
    return x;
}

static inline void vecCopyE(Vec* dst, Vec* src) {
    f32 z, y, x;
    x = src->x;
    y = src->y;
    z = src->z;
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

struct peSplineHdrE {
    u8 flags;
    gc_bef32 value;
    gc_bef32 time;
};

struct GSColorE {
    u8 r, g, b, a;
};

static inline f32 evalSplineE(peSpline* sp, f32 t) {
    peSplineHdrE* s = (peSplineHdrE*)sp;
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

static inline f32 __OSu8tof32E(register const u8* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 2 }
#else
    ret = PSQ_LOAD(arg, 0, 2);
#endif
    return ret;
}

static inline f32 u8tof32E(u8 v) {
    return __OSu8tof32E(&v);
}

static inline u16 f32tou16E(register f32 inF) {
    u32 out;
    u32* outP = &out;
    register u32* ptr = outP;
#ifdef __MWERKS__
    asm { psq_st inF, 0(ptr), 1, 3 }
#else
    PSQ_STORE(ptr, 0, inF, 3);
#endif
    return *(u16*)ptr;
}

static inline void quatIdentityE(Quaternion* q) {
    q->x = 0.0f;
    q->y = 0.0f;
    q->z = 0.0f;
    q->w = 1.0f;
}

static inline void xfInitE(peXformE* xf) {
    xf->pos.x = 0.0f;
    xf->pos.y = 0.0f;
    xf->pos.z = 0.0f;
    quatIdentityE(&xf->rot);
    xf->scale = unitScaleVector;
}

static inline void vecNormalizeE(Vec* dst, Vec* src) {
    Vec t;
    PSVECNormalize(src, &t);
    vecCopyE(dst, &t);
}

static inline u16 emitCountE(peEmitterNodeE* self, f32 t, f32 dt) {
    u16 count;
    if (self->flags & 0x40) {
        return 0;
    }
    if (!(self->flags & 8) && self->time < self->def->start) {
        return 0;
    }
    self->flags |= 8;
    if ((self->flags & 0x10) && self->time > self->def->start + self->def->duration) {
        return 0;
    }
    self->flags |= 0x10;
    f32 r = HSD_Randf();
    f32 n = self->def->countRange * r + self->def->countBase;
    n *= evalSplineE(self->def->countSpline, t);
    if (self->def->duration <= 0.00001f) {
        self->emitAcc = 0.0f;
        return f32tou16E(n);
    }
    n *= dt;
    n += self->emitAcc;
    count = f32tou16E(n);
    self->emitAcc = n - u16tof32E(count);
    if (count == 0 && self->emitted == 0) {
        count = 1;
        self->emitAcc = 0.0f;
    }
    return count;
}

struct peEmitterNodeW {
    u8 pad0[8];
    Vec pos;
    u8 pad14[0xc];
    peXform* parent;
    u8 pad24[0x4];
    void* slot28;
    void* slot2C;
    u8 pad30[0x18];
    u16 flipFlags;
    u16 emitted;
    u8 pad4c[0xc];
    Vec scale;
    f32 rot[4];
    Vec offset;
    Quaternion baseRot;
    u8 pad90[0x18];
    peXformE cur;
    peXformE prev;
    f32 depth;
    u32* def;
};
static inline void xfCopyE(peXformE* d, peXformE* s) {
    d->pos.x = s->pos.x;
    d->pos.y = s->pos.y;
    d->pos.z = s->pos.z;
    d->rot.x = s->rot.x;
    d->rot.y = s->rot.y;
    d->rot.z = s->rot.z;
    d->rot.w = s->rot.w;
    d->scale.x = s->scale.x;
    d->scale.y = s->scale.y;
    d->scale.z = s->scale.z;
}

static inline void vecAddE(Vec* dst, Vec* a, Vec* b) {
    Vec t;
    PSVECAdd(a, b, &t);
    dst->x = t.x;
    dst->y = t.y;
    dst->z = t.z;
}

static inline void vecSubE(Vec* dst, Vec* a, Vec* b) {
    Vec t;
    PSVECSubtract(a, b, &t);
    dst->x = t.x;
    dst->y = t.y;
    dst->z = t.z;
}

static inline void quatMulE(Quaternion* dst, Quaternion* a, Quaternion* b) {
    Quaternion t;
    PSQUATMultiply(a, b, &t);
    dst->x = t.x;
    dst->y = t.y;
    dst->z = t.z;
    dst->w = t.w;
}

#pragma defer_codegen on

void peEmitterNode::GetPositionParameter(GSvec* outPos, GSvec* outDir, _pePositionFunction* fn, float t) {
    PeMtx m2;
    PeMtx m0;
    PeMtx m1;
    PeMtx m3;
    Vec spread;
    Quaternion q;

    switch (fn->flags & 3) {
    case 0:
        GC_VEC3(*(Vec*)outDir, fn->sphere.dir);
        if ((absE(fn->sphere.radBase) > 0.00001f || absE(fn->sphere.radRange) > 0.00001f) &&
            PSVECSquareMag((Vec*)outDir) > 0.00001f) {
            f32 a;
            f32 s;
            if (fn->flags & 0x80) {
                a = 3.1415927f * (2.0f * (fn->sphere.spin * t));
            } else {
                f32 r = HSD_Randf();
                a = 3.1415927f * (2.0f * r);
            }
            C_QUATRotAxisRad(&q, (Vec*)outDir, a);
            peMtxQuat(m0, &q);
            mtxMultVecSRE((Vec*)outPos, m0, GC_VEC3P(Vec, &fn->sphere.axis));
            if (fn->flags & 0x20) {
                s = t * fn->sphere.radRange + fn->sphere.radBase;
            } else {
                s = fn->sphere.radRange * HSD_Randf() + fn->sphere.radBase;
            }
            PSVECScale((Vec*)outPos, (Vec*)outPos, s);
        } else {
            outPos->x = 0.0f;
            outPos->y = 0.0f;
            outPos->z = 0.0f;
        }
        {
            if (fn->flags & 0x10) {
                vecScaleE(&spread, GC_VEC3P(Vec, &fn->sphere.spread), t);
            } else {
                vecScaleE(&spread, GC_VEC3P(Vec, &fn->sphere.spread), HSD_Randf());
            }
            PSVECAdd(&spread, GC_VEC3P(Vec, &fn->sphere.center), &spread);
            PSVECAdd((Vec*)outPos, &spread, (Vec*)outPos);
        }
        if (PSVECSquareMag((Vec*)outPos) > 0.00001f) {
            vecNormalizeE((Vec*)outDir, (Vec*)outPos);
        } else {
            outDir->x = 0.0f;
            outDir->y = 0.0f;
            outDir->z = 0.0f;
        }
        return;
    case 1: {
        f32 a;
        f32 s;
        if (fn->flags & 0x40) {
            a = fn->ring.angRange * (fn->ring.angSpeed * t) + fn->ring.angBase;
        } else {
            a = fn->ring.angRange * HSD_Randf() + fn->ring.angBase;
        }
        C_QUATRotAxisRad(&q, GC_VEC3P(Vec, &fn->ring.axis), a);
        peMtxQuat(m1, &q);
        mtxMultVecSRE((Vec*)outDir, m1, GC_VEC3P(Vec, &fn->ring.start));
        if (fn->flags & 0x80) {
            a = 3.1415927f * (2.0f * (fn->ring.spin * t));
        } else {
            f32 r = HSD_Randf();
            a = 3.1415927f * (2.0f * r);
        }
        C_QUATRotAxisRad(&q, GC_VEC3P(Vec, &fn->ring.start), a);
        peMtxQuat(m2, &q);
        peMtxMultVecSR(m2, (Vec*)outDir, (Vec*)outDir);
        if (fn->flags & 0x20) {
            s = t * fn->ring.radRange + fn->ring.radBase;
        } else {
            s = fn->ring.radRange * HSD_Randf() + fn->ring.radBase;
        }
        vecScaleE((Vec*)outPos, (Vec*)outDir, s);
        return;
    }
    case 3: {
        f32 a;
        f32 s;
        GC_VEC3(*(Vec*)outDir, fn->line.dir);
        if (fn->flags & 0x80) {
            a = 3.1415927f * (2.0f * (fn->line.spin * t));
        } else {
            f32 r = HSD_Randf();
            a = 3.1415927f * (2.0f * r);
        }
        C_QUATRotAxisRad(&q, (Vec*)outDir, a);
        peMtxQuat(m3, &q);
        mtxMultVecSRE((Vec*)outPos, m3, GC_VEC3P(Vec, &fn->line.axis));
        if (fn->flags & 0x20) {
            s = t * fn->line.radRange + fn->line.radBase;
        } else {
            s = fn->line.radRange * HSD_Randf() + fn->line.radBase;
        }
        PSVECScale((Vec*)outPos, (Vec*)outPos, s);
        PSVECAdd((Vec*)outPos, GC_VEC3P(Vec, &fn->line.center), (Vec*)outPos);
        return;
    }
    default:
    case 2:
        outPos->x = 0.0f;
        outPos->y = 0.0f;
        outPos->z = 0.0f;
        outDir->x = 0.0f;
        outDir->y = 0.0f;
        outDir->z = 0.0f;
        return;
    }
}

void peEmitterNode::CreateParameters(unsigned short count, float dt) {
    peEmitterNodeE* self = (peEmitterNodeE*)this;
    peEmitterDefE* def = self->def;
    _EmitParamsE* ep;
    int interp = (def->flags >> 6) & 1;
    f32 rate = def->rate;
    f32 phase = rate * u16tof32E(self->emitted + count);
    f32 inv = 1.0f / u16tof32E(count);
    ep = (_EmitParamsE*)g_emitParams;
    _pePositionFunction* posFn;
    posFn = (_pePositionFunction*)&def->posFlags;
    f32 lerpT = 1.0f;
    f32 timeOff = 0.0f;
    f32 dtStep = dt * inv;

    while (count-- != 0) {
        Vec dir;
        GetPositionParameter((GSvec*)&ep->pos, (GSvec*)&dir, posFn, phase);
        switch (def->velFlags & 2) {
        case 0: {
            Quaternion q;
            PeMtx m;
            C_QUATRotAxisRad(&q, GC_VEC3P(Vec, &def->axis), HSD_Randf() * def->coneRange + def->coneBase);
            peMtxQuat(m, &q);
            mtxMultVecSRE(&ep->vel, m, GC_VEC3P(Vec, &def->dir));
            f32 r = HSD_Randf();
            C_QUATRotAxisRad(&q, GC_VEC3P(Vec, &def->dir), 3.1415927f * (2.0f * r));
            rotateForwardE(&ep->vel, &q);
            f32 s;
            if (def->velFlags & 0x20) {
                s = phase * def->magRange + def->magBase;
            } else {
                s = HSD_Randf() * def->magRange + def->magBase;
            }
            PSVECScale(&ep->vel, &ep->vel, s);
            break;
        }
        case 2: {
            f32 s;
            if (def->velFlags & 0x20) {
                s = phase * def->dir.y + def->dir.x;
            } else {
                s = HSD_Randf() * def->dir.y + def->dir.x;
            }
            vecScaleE(&ep->vel, &dir, s);
            break;
        }
        default:
            ep->vel.x = 0.0f;
            ep->vel.y = 0.0f;
            ep->vel.z = 0.0f;
            break;
        }
        vecScaleE(&dir, &ep->vel, timeOff);
        PSVECAdd(&ep->pos, &dir, &ep->pos);
        f32 r = HSD_Randf();
        ep->life = (self->def->lifeRange * r + self->def->lifeBase) - timeOff;
        r = HSD_Randf();
        ep->speed = self->def->speedRange * r + self->def->speedBase;
        if (interp) {
            Quaternion q;
            lerpVecE(&ep->xf.pos, &self->cur.pos, &self->prev.pos, lerpT);
            C_QUATLerp(&self->prev.rot, &self->cur.rot, &q, lerpT);
            f32 x, y, z, w;
            x = q.x;
            y = q.y;
            z = q.z;
            w = q.w;
            ep->xf.rot.x = x;
            ep->xf.rot.y = y;
            ep->xf.rot.z = z;
            ep->xf.rot.w = w;
            lerpVecE(&ep->xf.scale, &self->cur.scale, &self->prev.scale, lerpT);
            if (posFn->flags & 0x100) {
                PSVECSubtract(&ep->pos, &ep->xf.pos, &ep->pos);
                rotateInverseE(&ep->pos, &ep->xf.rot);
                divScaleE(&ep->pos, &ep->xf.scale);
            }
            if (def->velFlags & 0x10) {
                rotateInverseE(&ep->vel, &ep->xf.rot);
            }
        } else {
            if (posFn->flags & 0x100) {
                PSVECSubtract(&ep->pos, &self->cur.pos, &ep->pos);
                rotateInverseE(&ep->pos, &self->cur.rot);
                divScaleE(&ep->pos, &self->cur.scale);
            }
            if (def->velFlags & 0x10) {
                rotateInverseE(&ep->vel, &self->cur.rot);
            }
        }
        phase -= rate;
        ep++;
        lerpT -= inv;
        timeOff += dtStep;
    }
}

void peEmitterNode::CreateWorldParams() {
    peEmitterNodeW* self = (peEmitterNodeW*)this;
    int flags = *self->def;
    peXformE local;
    Vec d;
    Vec diff;
    xfCopyE(&self->prev, &self->cur);
    if (self->flipFlags & 1) {
        self->cur.rot.x = -self->rot[0];
    } else {
        self->cur.rot.x = self->rot[0];
    }
    if (self->flipFlags & 2) {
        self->cur.rot.y = -self->rot[1];
    } else {
        self->cur.rot.y = self->rot[1];
    }
    if (self->flipFlags & 4) {
        self->cur.rot.z = -self->rot[2];
    } else {
        self->cur.rot.z = self->rot[2];
    }
    self->cur.rot.w = self->rot[3];
    vecAddE(&local.pos, &self->pos, &self->offset);
    quatMulE(&local.rot, &self->baseRot, &self->cur.rot);
    local.scale.x = self->scale.x;
    local.scale.y = self->scale.y;
    local.scale.z = self->scale.z;
    peNodeTransformsConcat((peXform*)&self->cur, self->parent, (peXform*)&local, (flags >> 1) & 1);
    PSVECSubtract(&self->cur.pos, &g_CameraPosition, &diff);
    d.x = diff.x;
    d.y = diff.y;
    d.z = diff.z;
    self->depth = PSVECDotProduct(&g_CameraLookDir, &d);
    if (self->emitted == 0) {
        xfCopyE(&self->prev, &self->cur);
    }
}

void peEmitterNode::SetLastLoop() {
    f32 temp_f0;
    f32 temp_f2;
    u16 temp_r5;
    u8 *temp_r4;

    temp_r5 = PEN(this, u16 *, 0x48, flags);
    if (!(temp_r5 & 0x40) && (PED(PEN(this, u8 **, 0xFC, def), s32 *, 0, flags) & 1)) {
        PEN(this, u16 *, 0x48, flags) = (u16) (temp_r5 | 0x40);
        temp_r4 = PEN(this, u8 **, 0xFC, def);
        temp_f2 = PED(temp_r4, f32 *, 0x18, start) + PED(temp_r4, f32 *, 0x1C, duration);
        if (PEN(this, f32 *, 0x4, life) < (temp_f0 = PED(temp_r4, f32 *, 0x28, length) - temp_f2)) {
            PEN(this, f32 *, 0x4, life) = temp_f0;
            PEN(this, f32 *, 0x30, time) = temp_f2;
        }
    }
}

void peEmitterNode::Start(peEmitterNode* parent, _peEmitter* em, _EmitParams* params) {
    peEmitterNodeE* self = (peEmitterNodeE*)this;
    peEmitterDefE* def = (peEmitterDefE*)em;
    u32 dflags = def->flags;
    Vec euler;
    peContainer* c;

    ((peNode*)this)->Start(parent, params);
    if (parent == NULL && (dflags & 1)) {
        self->life = def->start + def->duration;
    } else {
        self->life = def->length;
    }
    self->life0 = def->length;
    self->time = 0.0f;
    self->emitAcc = 0.0f;
    self->color[3] = 0.0f;
    self->emitted = 0;
    self->flags = 0x20;
    quatIdentityE(&self->rot);
    quatIdentityE(&self->rot2);
    xfInitE(&self->prev);
    xfInitE(&self->cur);
    if (!(dflags & 2) &&
        (parent == NULL || (((peEmitterNodeE*)parent)->def->flags & 0x400) != 0x400)) {
        if ((dflags & 0x80) != 0x80) {
            EulerToQuat(GC_VEC3P(Vec, &def->euler), &self->rot);
        }
        if (dflags & 0x700038) {
            Vec* e = &euler;
            if (dflags & 8) {
                e->x = 6.2831855f * HSD_Randf();
            } else {
                e->x = 0.0f;
            }
            if (dflags & 0x10) {
                e->y = 6.2831855f * HSD_Randf();
            } else {
                e->y = 0.0f;
            }
            if (dflags & 0x20) {
                e->z = 6.2831855f * HSD_Randf();
            } else {
                e->z = 0.0f;
            }
            if ((dflags & 0x100000) && HSD_Randf() < 0.5f) {
                self->flags |= 1;
                euler.x = -euler.x;
            }
            if ((dflags & 0x200000) && HSD_Randf() < 0.5f) {
                self->flags |= 2;
                euler.y = -euler.y;
            }
            if ((dflags & 0x400000) && HSD_Randf() < 0.5f) {
                self->flags |= 4;
                euler.z = -euler.z;
            }
            EulerToQuat(&euler, &self->rot2);
        }
    }
    if ((dflags & 0x80) != 0x80) {
        f32 r = HSD_Randf();
        self->spin.x = def->spinRange.x * r + def->spinBase.x;
        r = HSD_Randf();
        self->spin.y = def->spinRange.y * r + def->spinBase.y;
        r = HSD_Randf();
        self->spin.z = def->spinRange.z * r + def->spinBase.z;
    }
    self->scaleBase.x = def->scale.x;
    self->scaleBase.y = def->scale.y;
    self->scaleBase.z = def->scale.z;
    for (c = self->containers; c != NULL; c = c->next) {
        c->Start();
    }
}

u8 peEmitterNode::Update(peEmitterNode* parent, _peEmitter* em, float dt) {
    peEmitterNodeE* self = (peEmitterNodeE*)this;
    peEmitterDefE* def = (peEmitterDefE*)em;
    u32 dflags = def->flags;
    f32 t;
    u16 count;
    peContainer* c;

    if (!((peNode*)this)->Update(parent, dt)) {
        if (parent == NULL && (dflags & 1)) {
            if (self->flags & 0x40) {
                return 0;
            }
            self->life += def->duration;
            self->time -= def->length - def->start;
            self->emitted = 0;
        } else {
            return 0;
        }
        self->flags &= ~0x20;
    }
    if (self->flags & 0x20) {
        t = 1.0f - self->life / self->life0;
    } else {
        t = 1.0f;
    }
    {
        GSColorE col;
        peColorSplineGetValue((u8*)&col, def->color, t);
        self->color[0] = 0.00390625f * (2.0f * u8tof32E(col.r));
        self->color[1] = 0.00390625f * (2.0f * u8tof32E(col.g));
        self->color[2] = 0.00390625f * (2.0f * u8tof32E(col.b));
    }
    self->color[3] = evalSplineE(def->alpha, t);
    if (parent != NULL) {
        peEmitterNodeE* p = (peEmitterNodeE*)parent;
        self->color[0] *= p->color[0];
        self->color[1] *= p->color[1];
        self->color[2] *= p->color[2];
        self->color[3] *= p->color[3];
    }
    if (!(dflags & 2)) {
        Vec e;
        u32 pflags;
        if (parent != NULL && ((pflags = ((peEmitterNodeE*)parent)->def->flags) & 0x400)) {
            Vec d;
            d = self->pos;
            if (pflags & 0x40) {
                PeMtx m;
                PSMTXQuat(m, &self->xf->rot);
                PSMTXMultVecSR(m, &d, &d);
            }
            e.x = atan2(-d.y, sqrtf(d.x * d.x + d.z * d.z));
            e.y = atan2(d.x, d.z);
            e.z = 0.0f;
            EulerToQuat(&e, &self->rot);
        } else if (dflags & 0x80) {
            e.x = def->euler.x * evalSplineE(def->eulerSpline[0], t);
            e.y = def->euler.y * evalSplineE(def->eulerSpline[1], t);
            e.z = def->euler.z * evalSplineE(def->eulerSpline[2], t);
            EulerToQuat(&e, &self->rot);
        } else {
            Quaternion q;
            e.x = dt * (self->spin.x * evalSplineE(def->spinSpline[0], t));
            e.y = dt * (self->spin.y * evalSplineE(def->spinSpline[1], t));
            e.z = dt * (self->spin.z * evalSplineE(def->spinSpline[2], t));
            EulerToQuat(&e, &q);
            PSQUATMultiply(&self->rot, &q, &self->rot);
        }
    }
    self->scale.x = self->scaleBase.x * evalSplineE(def->scaleSpline[0], t);
    self->scale.y = self->scaleBase.y * evalSplineE(def->scaleSpline[1], t);
    self->scale.z = self->scaleBase.z * evalSplineE(def->scaleSpline[2], t);
    self->unk74.x = def->vC4.x * evalSplineE(def->vC4Spline[0], t);
    self->unk74.y = def->vC4.y * evalSplineE(def->vC4Spline[1], t);
    self->unk74.z = def->vC4.z * evalSplineE(def->vC4Spline[2], t);
    self->unk9C.x = def->vAC.x * evalSplineE(def->vACSpline[0], t);
    self->unk9C.y = def->vAC.y * evalSplineE(def->vACSpline[1], t);
    self->unk9C.z = def->vAC.z * evalSplineE(def->vACSpline[2], t);
    CreateWorldParams();
    for (c = self->containers; c != NULL; c = c->next) {
        c->PreUpdate();
    }
    count = emitCountE(self, t, dt);
    if (count != 0) {
        if (count > g_maxEmitParams) {
            count = g_maxEmitParams;
        }
        CreateParameters(count, def->duration > 0.00001f ? dt : 0.0f);
        for (c = self->containers; c != NULL; c = c->next) {
            self->emitted += c->Emit(count);
        }
    }
    for (c = self->containers; c != NULL; c = c->next) {
        c->Update(dt);
    }
    self->time += dt;
    return 1;
}

void peEmitterNode::Render(_peEmitter* p0) {
    peContainer* c = PEN(this, peContainer **, 0x100, containers);
    if (PEN(this, u16 *, 0x4A, emitted) == 0) {
        return;
    }
    while (c != NULL) {
        c->Render();
        c = c->next;
    }
}

void peEmitterNode::Stop(_peEmitter* p0) {
    peContainer* c;

    for (c = PEN(this, peContainer **, 0x100, containers); c != NULL; c = c->next) {
        c->Stop();
    }
}

void peEmitterNode::Init(_peEmitter* em) {
    peEmitterNodeE* self = (peEmitterNodeE*)this;
    peContainer* c;
    void* data;
    u16 n;
    peEffectItemE* it;
    peEmitterDefE* def;

    self->def = (peEmitterDefE*)em;
    def = (peEmitterDefE*)em;
    n = def->maxNodes;
    for (it = def->items; it != NULL; it = it->next) {
        data = it->data;
        if (data != NULL) {
            c = NULL;
            switch (it->type) {
            case 0: {
                _peEmitter* sub = (_peEmitter*)data;
                if (((peEmitterDefE*)sub)->items != NULL) {
                    c = new peEmitterContainer(this, sub, n);
                }
                break;
            }
            case 1:
                if (*(s32*)((u8*)data + 0x54) != 0) {
                    c = new peParticleContainer(this, (_peParticle*)data, n);
                }
                break;
            case 6:
                if (*(s32*)((u8*)data + 0x1C) != 0) {
                    c = new peParticleStripContainer(this, (_peParticleStrip*)data, n);
                }
                break;
            case 3:
                if (*(s32*)((u8*)data + 0x60) != 0) {
                    c = new peDistortionContainer(this, (_peDistortion*)data, n);
                }
                break;
            case 2:
                if (*(s32*)((u8*)data + 0x4C) != 0) {
                    c = new peModelContainer(this, (_peModel*)data, n);
                }
                break;
            case 4:
                if (*(s32*)((u8*)data + 0x74) != 0) {
                    c = new peShapeContainer(this, (_peShape*)data, n);
                }
                break;
            }
            if (c != NULL) {
                if (self->containers == NULL) {
                    self->containers = c;
                } else {
                    peContainer* last = self->containers;
                    while (last->next != 0) {
                        last = last->next;
                    }
                    last->next = c;
                }
            }
        }
    }
}

}

#ifndef __MWERKS__
#include <stddef.h>
static_assert(offsetof(peEmitterNodeE, def) == offsetof(peEmitterNodeView, def), "emitter node view");
static_assert(offsetof(peEmitterNodeE, containers) == offsetof(peEmitterNodeView, containers), "emitter node view");
static_assert(offsetof(peEmitterNodeE, time) == sizeof(peNodeHead), "node head");
#endif
