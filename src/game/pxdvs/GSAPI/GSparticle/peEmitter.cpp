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
struct GSvec;
enum Mtx { Mtx_draft_dummy };
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
// ---- draft declarations ----
struct GSvec {
    u8 _draft[1];
};
struct Quaternion {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
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
    u8 _draft[1];
};
struct _peShape {
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
    virtual u16 Emit(unsigned short n);
    virtual void Update(float dt);
    virtual void Render();
    virtual void Stop();

    s32 RemoveNode(peNode*);
    u16 CreateNodes(unsigned short);
    s32 RemoveAll();
    s32 MoveNode(peNode*, peNode*);
};
class peEmitterContainer : public peContainer {
public:
    _peEmitter* data;  // 0x20
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
    u8 unk20[0x4];
    peShapeContainer(peEmitterNode*, _peShape*, unsigned short);
    virtual ~peShapeContainer();
};
class peModelContainer : public peContainer {
public:
    u8 unk20[0x4];
    peModelContainer(peEmitterNode*, _peModel*, unsigned short);
    virtual ~peModelContainer();
};
class peDistortionContainer : public peContainer {
public:
    u8 unk20[0x58];
    peDistortionContainer(peEmitterNode*, _peDistortion*, unsigned short);
    virtual ~peDistortionContainer();
};
class peParticleStripContainer : public peContainer {
public:
    u8 unk20[0x40];
    peParticleStripContainer(peEmitterNode*, _peParticleStrip*, unsigned short);
    virtual ~peParticleStripContainer();
};
class peParticleContainer : public peContainer {
public:
    u8 unk20[0x5C];
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
    void GetPositionParameter(GSvec*, GSvec*, _pePositionFunction*, float);
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
void peNodeTransformsConcat(peXform* out, peXform* a, peXform* b, bool useGfx);
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
inline peEmitterContainer::peEmitterContainer(peEmitterNode* e, _peEmitter* em, unsigned short n) : peContainer(e, 0x104, n) {
    peEmitterNode* node;
    peEmitterNode* next;

    data = em;
    node = (peEmitterNode*)freeList;
    while (node != 0) {
        next = M2C_FIELD(node, peEmitterNode **, 0x28);
        node->Init(em);
        node = next;
    }
    g_particle_debug_stats.unk4 += 0x24;
    g_particle_debug_stats.unk14 += 0x24;
}


extern s32 g_render_pass;
struct XdBlobC { u8 data[0xC]; };
extern XdBlobC unitScaleVector;
extern s32 this_;
}
extern "C++" {
void* operator new(unsigned long);
}
// ---- draft declarations ----



// ---- draft declarations ----



void peEmitterContainer::Stop() {
    u8 *var_r31;
    u8 *temp_r30;
    u8 *var_r3;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) != 0) {
        ((peContainer*)this)->PreUpdate();
        M2C_FIELD(this, u8 *, 0x19) = 0U;
        var_r3 = M2C_FIELD(this, u8 **, 0x10);
        while (var_r3 != NULL) {
            temp_r30 = M2C_FIELD(var_r3, u8 **, 0x28);
            var_r31 = M2C_FIELD(var_r3, u8 **, 0x100);
            while (var_r31 != NULL) {
                ((peContainer*)var_r31)->Stop();
                var_r31 = M2C_FIELD(var_r31, u8 **, 4);
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

    if (((u8) M2C_FIELD(this, u8 *, 0x19) != 0) && (((peEmitterContainer*)(this))->DoRender() != 0)) {
        var_r30 = M2C_FIELD(this, u8 **, 0x10);
        while (var_r30 != NULL) {
            var_r31 = M2C_FIELD(var_r30, u8 **, 0x100);
            if ((u16) M2C_FIELD(var_r30, u16 *, 0x4A) == 0) {

            } else {
                while (var_r31 != NULL) {
                    ((peContainer*)var_r31)->Render();
                    var_r31 = M2C_FIELD(var_r31, u8 **, 4);
                }
            }
            var_r30 = M2C_FIELD(var_r30, u8 **, 0x28);
        }
    }
}
}

extern "C++" {
u8 peEmitterContainer::DoRender() {
    s32 temp_r0;
    s32 temp_r4;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        return 0U;
    }
    temp_r4 = *M2C_FIELD(this, s32 **, 0x20);
    if ((u16) M2C_FIELD(this, u16 *, 0x14) == 0) {
        return 0U;
    }
    if (temp_r4 & 0x80000000) {
        return 0U;
    }
    switch ((s32) g_render_pass) {                  /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if (!(temp_r4 & 0x800)) {
            return 0U;
        }
block_15:
        temp_r0 = M2C_FIELD(g_current_layer, s32 *, 0x28);
        switch (temp_r0) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            if (temp_r4 & 0x2000) {
                return 1U;
            }
            return 0U;
        case 2:                                     /* switch 2 */
            if (temp_r4 & 0x4000) {
                return 1U;
            }
            if (!(temp_r4 & 0x0380E000)) {
                return 1U;
            }
            /* Duplicate return node #39. Try simplifying control flow for better match */
            return 0U;
        case 4:                                     /* switch 2 */
            if (temp_r4 & 0x8000) {
                return 1U;
            }
            /* Duplicate return node #39. Try simplifying control flow for better match */
            return 0U;
        case 1:                                     /* switch 2 */
            if (temp_r4 & 0x800000) {
                return 1U;
            }
            /* Duplicate return node #39. Try simplifying control flow for better match */
            return 0U;
        case 3:                                     /* switch 2 */
            if (temp_r4 & 0x01000000) {
                return 1U;
            }
            /* Duplicate return node #39. Try simplifying control flow for better match */
            return 0U;
        case 5:                                     /* switch 2 */
            if (temp_r4 & 0x02000000) {
                return 1U;
            }
            /* Duplicate return node #39. Try simplifying control flow for better match */
            return 0U;
        default:                                    /* switch 2 */
            return 0U;
        }
        break;
    case 1:                                         /* switch 1 */
        if (!(temp_r4 & 0x1000)) {
            return 0U;
        }
        goto block_15;
    case 3:    default:                                        /* switch 1 */
        return 0U;
    }
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

    var_r3 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x20), u8 **, 0x138);
    while (var_r3 != NULL) {
        var_r3 = M2C_FIELD(var_r3, u8 **, 0xC);
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
        next = M2C_FIELD(node, peNode **, 0x28);
        child = M2C_FIELD(node, peContainer **, 0x100);
        while (child != 0) {
            nextChild = (peContainer*)child->unk4;
            child->Stop();
            delete child;
            child = nextChild;
        }
        M2C_FIELD(node, peContainer **, 0x100) = 0;
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

    var_r30 = M2C_FIELD(this, u8 **, 0x100);
    while (var_r30 != NULL) {
        temp_r31 = M2C_FIELD(var_r30, u8 **, 4);
        ((peContainer*)var_r30)->Stop();
        delete (peContainer*)var_r30;
        var_r30 = temp_r31;
    }
    M2C_FIELD(this, u8 **, 0x100) = NULL;
}
}

extern "C++" {
extern "C++" {
extern "C++" {
extern "C++" {

extern "C++" {
#pragma push
#pragma dont_inline on
extern "C++" {
#pragma push
#pragma dont_inline off
void peEmitterNode::Init(_peEmitter* p0) {
    _peEmitter *temp_r30;
    peContainer *temp_r0_2;
    peContainer *temp_r0_3;
    peContainer *temp_r3;
    peContainer *var_r3_2;
    peContainer *var_r4;
    peDistortionContainer *temp_r3_4;
    peDistortionContainer *var_r0_3;
    peEmitterNode *temp_r30_2;
    peEmitterNode *var_r3;
    peModelContainer *temp_r3_5;
    peModelContainer *var_r0_4;
    peParticleContainer *temp_r3_2;
    peParticleContainer *var_r0;
    peParticleStripContainer *temp_r3_3;
    peParticleStripContainer *var_r0_2;
    peShapeContainer *temp_r3_6;
    peShapeContainer *var_r0_5;
    u16 temp_r29;
    u32 temp_r0;
    u8 *var_r28;

    M2C_FIELD(this, _peEmitter **, 0xFC) = p0;
    temp_r29 = (u16) M2C_FIELD(p0, s32 *, 4);
    for (var_r28 = M2C_FIELD(p0, u8 **, 0x138); var_r28 != NULL; var_r28 = M2C_FIELD(var_r28, u8 **, 0xC)) {
        temp_r30 = M2C_FIELD(var_r28, _peEmitter **, 8);
        if (temp_r30 != NULL) {
            temp_r0 = M2C_FIELD(var_r28, u32 *, 4);
            var_r4 = NULL;
            switch (temp_r0) {
            case 0:
                if ((u32) M2C_FIELD(temp_r30, u32 *, 0x138) != 0U) {
                    temp_r3 = new peEmitterContainer(this, temp_r30, temp_r29);
                    var_r4 = temp_r3;
                }
                break;
            case 1:
                if ((s32) M2C_FIELD(temp_r30, s32 *, 0x54) != 0) {
                    var_r4 = new peParticleContainer(this, (_peParticle*)temp_r30, temp_r29);
                }
                break;
            case 6:
                if ((s32) M2C_FIELD(temp_r30, s32 *, 0x1C) != 0) {
                    var_r4 = new peParticleStripContainer(this, (_peParticleStrip*)temp_r30, temp_r29);
                }
                break;
            case 3:
                if ((s32) M2C_FIELD(temp_r30, s32 *, 0x60) != 0) {
                    var_r4 = new peDistortionContainer(this, (_peDistortion*)temp_r30, temp_r29);
                }
                break;
            case 2:
                if ((s32) M2C_FIELD(temp_r30, s32 *, 0x4C) != 0) {
                    var_r4 = new peModelContainer(this, (_peModel*)temp_r30, temp_r29);
                }
                break;
            case 4:
                if ((s32) M2C_FIELD(temp_r30, s32 *, 0x74) != 0) {
                    var_r4 = new peShapeContainer(this, (_peShape*)temp_r30, temp_r29);
                }
                break;
            }
            if (var_r4 != NULL) {
                temp_r0_2 = M2C_FIELD(this, peContainer **, 0x100);
                if (temp_r0_2 == NULL) {
                    M2C_FIELD(this, peContainer **, 0x100) = var_r4;
                } else {
                    var_r3_2 = temp_r0_2;
                    while (M2C_FIELD(var_r3_2, peContainer **, 4) != NULL) {
                        var_r3_2 = M2C_FIELD(var_r3_2, peContainer **, 4);
                    }
                    M2C_FIELD(var_r3_2, peContainer **, 4) = var_r4;
                }
            }
        }
    }
}
#pragma pop
}

extern "C++" {
void peEmitterNode::Stop(_peEmitter* p0) {
    peContainer* c;

    for (c = M2C_FIELD(this, peContainer **, 0x100); c != NULL; c = (peContainer*)c->unk4) {
        c->Stop();
    }
}
}

extern "C++" {
void peEmitterNode::Render(_peEmitter* p0) {
    peContainer* c = M2C_FIELD(this, peContainer **, 0x100);
    if (M2C_FIELD(this, u16 *, 0x4A) == 0) {
        return;
    }
    while (c != NULL) {
        c->Render();
        c = (peContainer*)c->unk4;
    }
}
}
#pragma pop
}

extern "C++" {
#pragma push
#pragma dont_inline on
// container fields: 0x0 emitter, 0x10 node list, 0x14 node count, 0x19 active, 0x20 emitter data;
// emitter nodes: 0x28 next, 0x2C previous, 0xF8 depth, 0x100 child container list (linked at +0x4, vtable at +0x1C)
void peEmitterContainer::Update(float dt) {
    u8* child;
    peNode* node;
    peNode* next;
    peNode* pos;
    peNode* prev;
    f32 depth;

    if (*((u8*)this + 0x19) == 0) {
        return;
    }
    for (node = *(peNode**)((u8*)this + 0x10); node != NULL; node = next) {
        next = *(peNode**)((u8*)node + 0x28);
        if (!((peEmitterNode*)node)->Update(*(peEmitterNode**)this, *(_peEmitter**)((u8*)this + 0x20), dt)) {
            for (child = *(u8**)((u8*)node + 0x100); child != NULL; child = *(u8**)(child + 4)) {
                ((peContainer*)child)->Stop();
            }
            ((peContainer*)this)->RemoveNode(node);
        }
    }
    if (*((u8*)this + 0x19) != 0 && (**(u32**)((u8*)this + 0x20) & 0x40000) && *(u16*)((u8*)this + 0x14) >= 2) {
        for (node = *(peNode**)(*(u8**)((u8*)this + 0x10) + 0x28); node != NULL; node = next) {
            depth = *(f32*)((u8*)node + 0xF8);
            pos = node;
            for (prev = *(peNode**)((u8*)node + 0x2C); prev != NULL && *(f32*)((u8*)prev + 0xF8) < depth;
                 prev = *(peNode**)((u8*)prev + 0x2C)) {
                pos = prev;
            }
            next = *(peNode**)((u8*)node + 0x28);
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

    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        return 0U;
    }
    var_r31 = ((peContainer*)this)->CreateNodes(count);
    var_r30 = g_emitParams;
    var_r3 = M2C_FIELD(this, peEmitterNode **, 0x10);
    temp_r28 = var_r31;
    while (var_r31 != 0) {
        temp_r29 = M2C_FIELD(var_r3, peEmitterNode **, 0x28);
        ((peEmitterNode*)(var_r3))->Start((peEmitterNode*)(M2C_FIELD(this, peEmitterNode **, 0)), (_peEmitter*)(M2C_FIELD(this, _peEmitter **, 0x20)), (_EmitParams*)(var_r30));
        var_r3 = temp_r29;
        var_r31 -= 1;
        var_r30 += 0x48;
    }
    return temp_r28;
}
}
#pragma pop
}
u8 peEmitterNode::Update(peEmitterNode* p0, _peEmitter* p1, float p2) {
    s32 sp10;
    s32 sp14;
    s32 sp1D;
    s32 sp1E;
    s32 unksp20;
    s32 sp48;
    volatile f32 sp44;
    volatile f32 sp40;
    f32 sp3C;
    volatile f32 sp38;
    f32 sp34;
    f32 sp30;
    u8 sp1C;
    f32 sp18;
    u16 spC;
    u8 spA;
    u8 sp9;
    u8 sp8;
    Quaternion *temp_r3_10;
    f32 temp_f1_4;
    f32 temp_f29;
    f32 var_f1;
    f32 var_f1_10;
    f32 var_f1_11;
    f32 var_f1_12;
    f32 var_f1_13;
    f32 var_f1_14;
    f32 var_f1_15;
    f32 var_f1_16;
    f32 var_f1_17;
    f32 var_f1_18;
    f32 var_f1_19;
    f32 var_f1_20;
    f32 var_f1_21;
    f32 var_f1_22;
    f32 var_f1_23;
    f32 var_f1_24;
    f32 var_f1_25;
    f32 var_f1_26;
    f32 var_f1_27;
    f32 var_f1_28;
    f32 var_f1_29;
    f32 var_f1_2;
    f32 var_f1_30;
    f32 var_f1_31;
    f32 var_f1_32;
    f32 var_f1_33;
    f32 var_f1_34;
    f32 var_f1_35;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f1_6;
    f32 var_f1_7;
    f32 var_f1_8;
    f32 var_f1_9;
    f32 var_f2;
    f32 var_f31;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;
    peSpline *temp_r3;
    peSpline *temp_r3_11;
    peSpline *temp_r3_12;
    peSpline *temp_r3_13;
    peSpline *temp_r3_14;
    peSpline *temp_r3_15;
    peSpline *temp_r3_16;
    peSpline *temp_r3_17;
    peSpline *temp_r3_18;
    peSpline *temp_r3_19;
    peSpline *temp_r3_4;
    peSpline *temp_r3_5;
    peSpline *temp_r3_6;
    peSpline *temp_r3_7;
    peSpline *temp_r3_8;
    peSpline *temp_r3_9;
    s32 temp_r29;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 var_r0;
    s32 temp_r3_20;
    s32 var_r29;
    u32 var_r3;
    u8 *temp_r3_21;
    u8 *temp_r4;
    u8 *var_r28;
    u8 *var_r28_2;
    u8 *var_r28_3;

    temp_r29 = M2C_FIELD(p1, s32 *, 0);
    if (((peNode*)((peNode *) this))->Update((peEmitterNode*)(p0), p2) == 0) {
        if ((p0 == NULL) && (temp_r29 & 1)) {
            if (M2C_FIELD(this, u16 *, 0x48) & 0x40) {
                return 0U;
            }
            M2C_FIELD(this, f32 *, 4) = (f32) (M2C_FIELD(this, f32 *, 4) + M2C_FIELD(p1, f32 *, 0x1C));
            M2C_FIELD(this, f32 *, 0x30) = (f32) (M2C_FIELD(this, f32 *, 0x30) - (M2C_FIELD(p1, f32 *, 0x28) - M2C_FIELD(p1, f32 *, 0x18)));
            M2C_FIELD(this, u16 *, 0x4A) = 0U;
            M2C_FIELD(this, u16 *, 0x48) = (u16) (M2C_FIELD(this, u16 *, 0x48) & 0xFFFFFFDF);
            goto block_8;
        }
        return 0U;
    }
block_8:
    if (M2C_FIELD(this, u16 *, 0x48) & 0x20) {
        var_f31 = 1.0f - (M2C_FIELD(this, f32 *, 4) / M2C_FIELD(this, f32 *, 0));
    } else {
        var_f31 = 1.0f;
    }
    peColorSplineGetValue((u8*)(&sp1C), (peColorSpline*)(M2C_FIELD(p1, peColorSpline **, 0x130)), var_f31);
    spA = sp1C;
    M2C_FIELD(this, f32 *, 0x38) = (f32) (0.00390625f * (2.0f * M2C_ERROR(/* psq_l unimplemented */)));
    sp9 = sp1D;
    M2C_FIELD(this, f32 *, 0x3C) = (f32) (0.00390625f * (2.0f * M2C_ERROR(/* psq_l unimplemented */)));
    sp8 = sp1E;
    M2C_FIELD(this, f32 *, 0x40) = (f32) (0.00390625f * (2.0f * M2C_ERROR(/* psq_l unimplemented */)));
    temp_r3 = M2C_FIELD(p1, peSpline **, 0x134);
    if ((temp_r3 == NULL) || !(M2C_FIELD(temp_r3, u8 *, 0) & 3)) {
        var_f1 = 1.0f;
    } else {
        var_f1_2 = M2C_FIELD((u16)temp_r3, f32 *, 8);
        var_f1_2 -= var_f31;
        if (var_f1_2 < 0.0f) {
            var_f1_2 = -var_f1_2;
        }
        if (var_f1_2 <= 0.00001f) {
            var_f1 = M2C_FIELD(temp_r3, f32 *, 4);
        } else {
            var_f1 = peSplineGetValue((peSpline*)(temp_r3), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0x44) = var_f1;
    if (p0 != NULL) {
        M2C_FIELD(this, f32 *, 0x38) = (f32) (M2C_FIELD(this, f32 *, 0x38) * M2C_FIELD(p0, f32 *, 0x38));
        M2C_FIELD(this, f32 *, 0x3C) = (f32) (M2C_FIELD(this, f32 *, 0x3C) * M2C_FIELD(p0, f32 *, 0x3C));
        M2C_FIELD(this, f32 *, 0x40) = (f32) (M2C_FIELD(this, f32 *, 0x40) * M2C_FIELD(p0, f32 *, 0x40));
        M2C_FIELD(this, f32 *, 0x44) = (f32) (M2C_FIELD(this, f32 *, 0x44) * M2C_FIELD(p0, f32 *, 0x44));
    }
    if (!(temp_r29 & 2)) {
        if ((p0 != NULL) && (temp_r3_2 = *M2C_FIELD(p0, s32 **, 0xFC), (((temp_r3_2 & 0x400) == 0) == 0))) {
            sp30 = M2C_FIELD(this, f32 *, 0x14);
            sp34 = M2C_FIELD(this, f32 *, 0x18);
            sp38 = M2C_FIELD(this, f32 *, 0x1C);
            if (temp_r3_2 & 0x40) {
                PSMTXQuat((Mtx)((s32) &sp48), (const Quaternion *)((const register Quaternion*)(M2C_FIELD(this, s32 *, 0x20) + 0xC)));
                PSMTXMultVecSR((const Mtx)((s32) &sp48), (const Vec *)((const register Vec*)((Vec *) &sp30)), (Vec *)((register Vec*)((Vec *) &sp30)));
            }
            var_f2 = (sp38 * sp38);
            var_f2 += (sp30 * sp30);
            var_f2 = sqrtf(var_f2);
            sp3C = (f32) atan2(-sp34, (f64) var_f2);
            temp_f1_4 = (f32) atan2((f64) sp30, (f64) sp38);
            sp44 = 0.0f;
            sp40 = temp_f1_4;
            EulerToQuat((Vec*)((Vec *) &sp3C), (Quaternion*)(this + 0x64));
        } else if (temp_r29 & 0x80) {
            temp_r3_4 = M2C_FIELD(p1, peSpline **, 0xE8);
            if ((temp_r3_4 == NULL) || !(M2C_FIELD(temp_r3_4, u8 *, 0) & 3)) {
                var_f1_3 = 1.0f;
            } else {
                var_f1_4 = M2C_FIELD(temp_r3_4, f32 *, 8) - var_f31;
                if (var_f1_4 < 0.0f) {
                    var_f1_4 = -var_f1_4;
                }
                if (var_f1_4 <= 0.00001f) {
                    var_f1_3 = M2C_FIELD(temp_r3_4, f32 *, 4);
                } else {
                    var_f1_3 = peSplineGetValue((peSpline*)(temp_r3_4), var_f31);
                }
            }
            sp3C = M2C_FIELD(p1, f32 *, 0xDC) * var_f1_3;
            temp_r3_5 = M2C_FIELD(p1, peSpline **, 0xEC);
            if ((temp_r3_5 == NULL) || !(M2C_FIELD(temp_r3_5, u8 *, 0) & 3)) {
                var_f1_5 = 1.0f;
            } else {
                var_f1_6 = M2C_FIELD(temp_r3_5, f32 *, 8) - var_f31;
                if (var_f1_6 < 0.0f) {
                    var_f1_6 = -var_f1_6;
                }
                if (var_f1_6 <= 0.00001f) {
                    var_f1_5 = M2C_FIELD(temp_r3_5, f32 *, 4);
                } else {
                    var_f1_5 = peSplineGetValue((peSpline*)(temp_r3_5), var_f31);
                }
            }
            sp40 = M2C_FIELD(p1, f32 *, 0xE0) * var_f1_5;
            temp_r3_6 = M2C_FIELD(p1, peSpline **, 0xF0);
            if ((temp_r3_6 == NULL) || !(M2C_FIELD(temp_r3_6, u8 *, 0) & 3)) {
                var_f1_7 = 1.0f;
            } else {
                var_f1_8 = M2C_FIELD(temp_r3_6, f32 *, 8) - var_f31;
                if (var_f1_8 < 0.0f) {
                    var_f1_8 = -var_f1_8;
                }
                if (var_f1_8 <= 0.00001f) {
                    var_f1_7 = M2C_FIELD(temp_r3_6, f32 *, 4);
                } else {
                    var_f1_7 = peSplineGetValue((peSpline*)(temp_r3_6), var_f31);
                }
            }
            sp44 = M2C_FIELD(p1, f32 *, 0xE4) * var_f1_7;
            EulerToQuat((Vec*)((Vec *) &sp3C), (Quaternion*)(this + 0x64));
        } else {
            temp_r3_7 = M2C_FIELD(p1, peSpline **, 0x10C);
            if ((temp_r3_7 == NULL) || !(M2C_FIELD(temp_r3_7, u8 *, 0) & 3)) {
                var_f1_9 = 1.0f;
            } else {
                var_f1_10 = M2C_FIELD(temp_r3_7, f32 *, 8) - var_f31;
                if (var_f1_10 < 0.0f) {
                    var_f1_10 = -var_f1_10;
                }
                if (var_f1_10 <= 0.00001f) {
                    var_f1_9 = M2C_FIELD(temp_r3_7, f32 *, 4);
                } else {
                    var_f1_9 = peSplineGetValue((peSpline*)(temp_r3_7), var_f31);
                }
            }
            sp3C = p2 * (M2C_FIELD(this, f32 *, 0x90) * var_f1_9);
            temp_r3_8 = M2C_FIELD(p1, peSpline **, 0x110);
            if ((temp_r3_8 == NULL) || !(M2C_FIELD(temp_r3_8, u8 *, 0) & 3)) {
                var_f1_11 = 1.0f;
            } else {
                var_f1_12 = M2C_FIELD(temp_r3_8, f32 *, 8) - var_f31;
                if (var_f1_12 < 0.0f) {
                    var_f1_12 = -var_f1_12;
                }
                if (var_f1_12 <= 0.00001f) {
                    var_f1_11 = M2C_FIELD(temp_r3_8, f32 *, 4);
                } else {
                    var_f1_11 = peSplineGetValue((peSpline*)(temp_r3_8), var_f31);
                }
            }
            sp40 = p2 * (M2C_FIELD(this, f32 *, 0x94) * var_f1_11);
            temp_r3_9 = M2C_FIELD(p1, peSpline **, 0x114);
            if ((temp_r3_9 == NULL) || !(M2C_FIELD(temp_r3_9, u8 *, 0) & 3)) {
                var_f1_13 = 1.0f;
            } else {
                var_f1_14 = M2C_FIELD(temp_r3_9, f32 *, 8) - var_f31;
                if (var_f1_14 < 0.0f) {
                    var_f1_14 = -var_f1_14;
                }
                if (var_f1_14 <= 0.00001f) {
                    var_f1_13 = M2C_FIELD(temp_r3_9, f32 *, 4);
                } else {
                    var_f1_13 = peSplineGetValue((peSpline*)(temp_r3_9), var_f31);
                }
            }
            sp44 = p2 * (M2C_FIELD(this, f32 *, 0x98) * var_f1_13);
            EulerToQuat((Vec*)((Vec *) &sp3C), (Quaternion*)(&unksp20));
            temp_r3_10 = (Quaternion *)(this + 0x64);
            PSQUATMultiply((const register Quaternion*)(temp_r3_10), (const register Quaternion*)(&unksp20), (register Quaternion*)(temp_r3_10));
        }
    }
    temp_r3_11 = M2C_FIELD(p1, peSpline **, 0x124);
    if ((temp_r3_11 == NULL) || !(M2C_FIELD(temp_r3_11, u8 *, 0) & 3)) {
        var_f1_15 = 1.0f;
    } else {
        var_f1_16 = M2C_FIELD(temp_r3_11, f32 *, 8) - var_f31;
        if (var_f1_16 < 0.0f) {
            var_f1_16 = -var_f1_16;
        }
        if (var_f1_16 <= 0.00001f) {
            var_f1_15 = M2C_FIELD(temp_r3_11, f32 *, 4);
        } else {
            var_f1_15 = peSplineGetValue((peSpline*)(temp_r3_11), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0x58) = (f32) (M2C_FIELD(this, f32 *, 0x4C) * var_f1_15);
    temp_r3_12 = M2C_FIELD(p1, peSpline **, 0x128);
    if ((temp_r3_12 == NULL) || !(M2C_FIELD(temp_r3_12, u8 *, 0) & 3)) {
        var_f1_17 = 1.0f;
    } else {
        var_f1_18 = M2C_FIELD(temp_r3_12, f32 *, 8) - var_f31;
        if (var_f1_18 < 0.0f) {
            var_f1_18 = -var_f1_18;
        }
        if (var_f1_18 <= 0.00001f) {
            var_f1_17 = M2C_FIELD(temp_r3_12, f32 *, 4);
        } else {
            var_f1_17 = peSplineGetValue((peSpline*)(temp_r3_12), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0x5C) = (f32) (M2C_FIELD(this, f32 *, 0x50) * var_f1_17);
    temp_r3_13 = M2C_FIELD(p1, peSpline **, 0x12C);
    if ((temp_r3_13 == NULL) || !(M2C_FIELD(temp_r3_13, u8 *, 0) & 3)) {
        var_f1_19 = 1.0f;
    } else {
        var_f1_20 = M2C_FIELD(temp_r3_13, f32 *, 8) - var_f31;
        if (var_f1_20 < 0.0f) {
            var_f1_20 = -var_f1_20;
        }
        if (var_f1_20 <= 0.00001f) {
            var_f1_19 = M2C_FIELD(temp_r3_13, f32 *, 4);
        } else {
            var_f1_19 = peSplineGetValue((peSpline*)(temp_r3_13), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0x60) = (f32) (M2C_FIELD(this, f32 *, 0x54) * var_f1_19);
    temp_r3_14 = M2C_FIELD(p1, peSpline **, 0xD0);
    if ((temp_r3_14 == NULL) || !(M2C_FIELD(temp_r3_14, u8 *, 0) & 3)) {
        var_f1_21 = 1.0f;
    } else {
        var_f1_22 = M2C_FIELD(temp_r3_14, f32 *, 8) - var_f31;
        if (var_f1_22 < 0.0f) {
            var_f1_22 = -var_f1_22;
        }
        if (var_f1_22 <= 0.00001f) {
            var_f1_21 = M2C_FIELD(temp_r3_14, f32 *, 4);
        } else {
            var_f1_21 = peSplineGetValue((peSpline*)(temp_r3_14), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0x74) = (f32) (M2C_FIELD(p1, f32 *, 0xC4) * var_f1_21);
    temp_r3_15 = M2C_FIELD(p1, peSpline **, 0xD4);
    if ((temp_r3_15 == NULL) || !(M2C_FIELD(temp_r3_15, u8 *, 0) & 3)) {
        var_f1_23 = 1.0f;
    } else {
        var_f1_24 = M2C_FIELD(temp_r3_15, f32 *, 8) - var_f31;
        if (var_f1_24 < 0.0f) {
            var_f1_24 = -var_f1_24;
        }
        if (var_f1_24 <= 0.00001f) {
            var_f1_23 = M2C_FIELD(temp_r3_15, f32 *, 4);
        } else {
            var_f1_23 = peSplineGetValue((peSpline*)(temp_r3_15), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0x78) = (f32) (M2C_FIELD(p1, f32 *, 0xC8) * var_f1_23);
    temp_r3_16 = M2C_FIELD(p1, peSpline **, 0xD8);
    if ((temp_r3_16 == NULL) || !(M2C_FIELD(temp_r3_16, u8 *, 0) & 3)) {
        var_f1_25 = 1.0f;
    } else {
        var_f1_26 = M2C_FIELD(temp_r3_16, f32 *, 8) - var_f31;
        if (var_f1_26 < 0.0f) {
            var_f1_26 = -var_f1_26;
        }
        if (var_f1_26 <= 0.00001f) {
            var_f1_25 = M2C_FIELD(temp_r3_16, f32 *, 4);
        } else {
            var_f1_25 = peSplineGetValue((peSpline*)(temp_r3_16), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0x7C) = (f32) (M2C_FIELD(p1, f32 *, 0xCC) * var_f1_25);
    temp_r3_17 = M2C_FIELD(p1, peSpline **, 0xB8);
    if ((temp_r3_17 == NULL) || !(M2C_FIELD(temp_r3_17, u8 *, 0) & 3)) {
        var_f1_27 = 1.0f;
    } else {
        var_f1_28 = M2C_FIELD(temp_r3_17, f32 *, 8) - var_f31;
        if (var_f1_28 < 0.0f) {
            var_f1_28 = -var_f1_28;
        }
        if (var_f1_28 <= 0.00001f) {
            var_f1_27 = M2C_FIELD(temp_r3_17, f32 *, 4);
        } else {
            var_f1_27 = peSplineGetValue((peSpline*)(temp_r3_17), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0x9C) = (f32) (M2C_FIELD(p1, f32 *, 0xAC) * var_f1_27);
    temp_r3_18 = M2C_FIELD(p1, peSpline **, 0xBC);
    if ((temp_r3_18 == NULL) || !(M2C_FIELD(temp_r3_18, u8 *, 0) & 3)) {
        var_f1_29 = 1.0f;
    } else {
        var_f1_30 = M2C_FIELD(temp_r3_18, f32 *, 8) - var_f31;
        if (var_f1_30 < 0.0f) {
            var_f1_30 = -var_f1_30;
        }
        if (var_f1_30 <= 0.00001f) {
            var_f1_29 = M2C_FIELD(temp_r3_18, f32 *, 4);
        } else {
            var_f1_29 = peSplineGetValue((peSpline*)(temp_r3_18), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0xA0) = (f32) (M2C_FIELD(p1, f32 *, 0xB0) * var_f1_29);
    temp_r3_19 = M2C_FIELD(p1, peSpline **, 0xC0);
    if ((temp_r3_19 == NULL) || !(M2C_FIELD(temp_r3_19, u8 *, 0) & 3)) {
        var_f1_31 = 1.0f;
    } else {
        var_f1_32 = M2C_FIELD(temp_r3_19, f32 *, 8) - var_f31;
        if (var_f1_32 < 0.0f) {
            var_f1_32 = -var_f1_32;
        }
        if (var_f1_32 <= 0.00001f) {
            var_f1_31 = M2C_FIELD(temp_r3_19, f32 *, 4);
        } else {
            var_f1_31 = peSplineGetValue((peSpline*)(temp_r3_19), var_f31);
        }
    }
    M2C_FIELD(this, f32 *, 0xA4) = (f32) (M2C_FIELD(p1, f32 *, 0xB4) * var_f1_31);
    ((peEmitterNode*)(this))->CreateWorldParams();
    var_r28 = M2C_FIELD(this, u8 **, 0x100);
    while (var_r28 != NULL) {
        ((peContainer*)var_r28)->PreUpdate();
        var_r28 = M2C_FIELD(var_r28, u8 **, 4);
    }
    temp_r3_20 = M2C_FIELD((s32)this, u16 *, 0x48);
    if (temp_r3_20 & 0x40) {
        var_r3 = 0;
    } else if (!(temp_r3_20 & 8) && (M2C_FIELD(this, f32 *, 0x30) < M2C_FIELD(M2C_FIELD(this, u8 **, 0xFC), f32 *, 0x18))) {
        var_r3 = 0;
    } else {
        M2C_FIELD(this, u16 *, 0x48) = (u16) (M2C_FIELD(this, u16 *, 0x48) | 8);
        if ((M2C_FIELD(this, u16 *, 0x48) & 0x10) && (temp_r3_21 = M2C_FIELD(this, u8 **, 0xFC), ((M2C_FIELD(this, f32 *, 0x30) > (M2C_FIELD(temp_r3_21, f32 *, 0x18) + M2C_FIELD(temp_r3_21, f32 *, 0x1C))) != 0))) {
            var_r3 = 0;
        } else {
            temp_r4 = M2C_FIELD(this, u8 **, 0xFC);
            M2C_FIELD(this, u16 *, 0x48) = (u16) (M2C_FIELD(this, u16 *, 0x48) | 0x10);
            temp_f29 = (M2C_FIELD(temp_r4, f32 *, 0x10) * HSD_Randf()) + M2C_FIELD(temp_r4, f32 *, 0xC);
            if (((M2C_FIELD(temp_r4, peSpline **, 0x14)) == NULL) || !(M2C_FIELD((M2C_FIELD(temp_r4, peSpline **, 0x14)), u8 *, 0) & 3)) {
                var_f1_33 = 1.0f;
            } else {
                var_f1_34 = M2C_FIELD((M2C_FIELD(temp_r4, peSpline **, 0x14)), f32 *, 8) - var_f31;
                if (var_f1_34 < 0.0f) {
                    var_f1_34 = -var_f1_34;
                }
                if (var_f1_34 <= 0.00001f) {
                    var_f1_33 = M2C_FIELD((M2C_FIELD(temp_r4, peSpline **, 0x14)), f32 *, 4);
                } else {
                    var_f1_33 = peSplineGetValue((peSpline*)((M2C_FIELD(temp_r4, peSpline **, 0x14))), var_f31);
                }
            }
            if (M2C_FIELD(M2C_FIELD(this, u8 **, 0xFC), f32 *, 0x1C) <= 0.00001f) {
                M2C_FIELD(this, f32 *, 0x34) = 0.0f;
                var_r3 = sp14;
            } else {
                var_r3 = sp10;
                spC = var_r3;
                M2C_FIELD(this, f32 *, 0x34) = (f32) (((temp_f29 * var_f1_33 * p2) + M2C_FIELD(this, f32 *, 0x34)) - M2C_ERROR(/* psq_l unimplemented */));
                if ((var_r3 == 0) && ((u16) M2C_FIELD(this, u16 *, 0x4A) == 0)) {
                    var_r3 = 1;
                    M2C_FIELD(this, f32 *, 0x34) = 0.0f;
                }
            }
        }
    }
    var_r29 = var_r3;
    if (var_r3 != 0) {
        if (var_r3 > (u16) g_maxEmitParams) {
            var_r29 = g_maxEmitParams;
        }
        if (M2C_FIELD(p1, f32 *, 0x1C) > 0.00001f) {
            var_f1_35 = p2;
        } else {
            var_f1_35 = 0.0f;
        }
        ((peEmitterNode*)(this))->CreateParameters(var_r29, var_f1_35);
        var_r28_2 = M2C_FIELD(this, u8 **, 0x100);
        while (var_r28_2 != NULL) {
            M2C_FIELD(this, u16 *, 0x4A) = (u16) (M2C_FIELD(this, u16 *, 0x4A) + ((peContainer*)var_r28_2)->Emit(var_r29));
            var_r28_2 = M2C_FIELD(var_r28_2, u8 **, 4);
        }
    }
    var_r28_3 = M2C_FIELD(this, u8 **, 0x100);
    while (var_r28_3 != NULL) {
        ((peContainer*)var_r28_3)->Update(p2);
        var_r28_3 = M2C_FIELD(var_r28_3, u8 **, 4);
    }
    M2C_FIELD(this, f32 *, 0x30) = (f32) (M2C_FIELD(this, f32 *, 0x30) + p2);
    return 1U;
}
}

extern "C++" {
void peEmitterNode::Start(peEmitterNode* p0, _peEmitter* p1, _EmitParams* p2) {
    volatile f32 sp10;
    volatile f32 spC;
    f32 sp8;
    s32 temp_r31;
    u8 *var_r29;

    temp_r31 = M2C_FIELD(p1, s32 *, 0);
    ((peNode*)((peNode *) this))->Start((peEmitterNode*)(p0), (_EmitParams*)(p2));
    if ((p0 == NULL) && (temp_r31 & 1)) {
        M2C_FIELD(this, f32 *, 4) = (f32) (M2C_FIELD(p1, f32 *, 0x18) + M2C_FIELD(p1, f32 *, 0x1C));
    } else {
        M2C_FIELD(this, f32 *, 4) = (f32) M2C_FIELD(p1, f32 *, 0x28);
    }
    M2C_FIELD(this, f32 *, 0) = (f32) M2C_FIELD(p1, f32 *, 0x28);
    M2C_FIELD(this, f32 *, 0x30) = 0.0f;
    M2C_FIELD(this, f32 *, 0x34) = 0.0f;
    M2C_FIELD(this, f32 *, 0x44) = 0.0f;
    M2C_FIELD(this, s16 *, 0x4A) = 0;
    M2C_FIELD(this, u16 *, 0x48) = 0x20U;
    M2C_FIELD(this, f32 *, 0x64) = 0.0f;
    M2C_FIELD(this, f32 *, 0x68) = 0.0f;
    M2C_FIELD(this, f32 *, 0x6C) = 0.0f;
    M2C_FIELD(this, f32 *, 0x70) = 1.0f;
    M2C_FIELD(this, f32 *, 0x80) = 0.0f;
    M2C_FIELD(this, f32 *, 0x84) = 0.0f;
    M2C_FIELD(this, f32 *, 0x88) = 0.0f;
    M2C_FIELD(this, f32 *, 0x8C) = 1.0f;
    M2C_FIELD(this, f32 *, 0xD0) = 0.0f;
    M2C_FIELD(this, f32 *, 0xD4) = 0.0f;
    M2C_FIELD(this, f32 *, 0xD8) = 0.0f;
    M2C_FIELD(this, f32 *, 0xDC) = 0.0f;
    M2C_FIELD(this, f32 *, 0xE0) = 0.0f;
    M2C_FIELD(this, f32 *, 0xE4) = 0.0f;
    M2C_FIELD(this, f32 *, 0xE8) = 1.0f;
    M2C_FIELD(this, f32 *, 0xEC) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 0);
    M2C_FIELD(this, f32 *, 0xF0) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 4);
    M2C_FIELD(this, f32 *, 0xF4) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 8);
    M2C_FIELD(this, f32 *, 0xA8) = 0.0f;
    M2C_FIELD(this, f32 *, 0xAC) = 0.0f;
    M2C_FIELD(this, f32 *, 0xB0) = 0.0f;
    M2C_FIELD(this, f32 *, 0xB4) = 0.0f;
    M2C_FIELD(this, f32 *, 0xB8) = 0.0f;
    M2C_FIELD(this, f32 *, 0xBC) = 0.0f;
    M2C_FIELD(this, f32 *, 0xC0) = 1.0f;
    M2C_FIELD(this, f32 *, 0xC4) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 0);
    M2C_FIELD(this, f32 *, 0xC8) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 4);
    M2C_FIELD(this, f32 *, 0xCC) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 8);
    if (!(temp_r31 & 2) && ((p0 == NULL) || ((u32) (*M2C_FIELD(p0, s32 **, 0xFC) & 0x400) != 0x400))) {
        if ((u32) (temp_r31 & 0x80) != 0x80) {
            EulerToQuat((Vec*)(((u8*)(p1) + 0xDC)), (Quaternion*)(this + 0x64));
        }
        if (temp_r31 & 0x700038) {
            if (temp_r31 & 8) {
                sp8 = HSD_Randf();
                sp8 *= 6.2831855f;
            } else {
                sp8 = 0.0f;
            }
            if (temp_r31 & 0x10) {
                spC = 6.2831855f;
                spC *= HSD_Randf();
            } else {
                spC = 0.0f;
            }
            if (temp_r31 & 0x20) {
                sp10 = 6.2831855f;
                sp10 *= HSD_Randf();
            } else {
                sp10 = 0.0f;
            }
            if ((temp_r31 & 0x100000) && (HSD_Randf() < 0.5f)) {
                M2C_FIELD(this, u16 *, 0x48) = (u16) (M2C_FIELD(this, u16 *, 0x48) | 1);
                sp8 = -sp8;
            }
            if ((temp_r31 & 0x200000) && (HSD_Randf() < 0.5f)) {
                M2C_FIELD(this, u16 *, 0x48) = (u16) (M2C_FIELD(this, u16 *, 0x48) | 2);
                spC = -spC;
            }
            if ((temp_r31 & 0x400000) && (HSD_Randf() < 0.5f)) {
                M2C_FIELD(this, u16 *, 0x48) = (u16) (M2C_FIELD(this, u16 *, 0x48) | 4);
                sp10 = -sp10;
            }
            EulerToQuat((Vec*)((Vec *) &sp8), (Quaternion*)(this + 0x80));
        }
    }
    if ((u32) (temp_r31 & 0x80) != 0x80) {
        M2C_FIELD(this, f32 *, 0x90) = (f32) ((M2C_FIELD(p1, f32 *, 0x100) * HSD_Randf()) + M2C_FIELD(p1, f32 *, 0xF4));
        M2C_FIELD(this, f32 *, 0x94) = (f32) ((M2C_FIELD(p1, f32 *, 0x104) * HSD_Randf()) + M2C_FIELD(p1, f32 *, 0xF8));
        M2C_FIELD(this, f32 *, 0x98) = (f32) ((M2C_FIELD(p1, f32 *, 0x108) * HSD_Randf()) + M2C_FIELD(p1, f32 *, 0xFC));
    }
    M2C_FIELD(this, f32 *, 0x4C) = (f32) M2C_FIELD(p1, f32 *, 0x118);
    M2C_FIELD(this, f32 *, 0x50) = (f32) M2C_FIELD(p1, f32 *, 0x11C);
    M2C_FIELD(this, f32 *, 0x54) = (f32) M2C_FIELD(p1, f32 *, 0x120);
    var_r29 = M2C_FIELD(this, u8 **, 0x100);
    while (var_r29 != NULL) {
        ((peContainer*)var_r29)->Start();
        var_r29 = M2C_FIELD(var_r29, u8 **, 4);
    }
}
extern "C++" {
void peEmitterNode::CreateParameters(unsigned short p0, float p1) {
    s32 unksp100;
    s32 sp10;
    u8 *temp_r31;
    s32 sp1C;
    s32 sp20;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    f32 sp74;
    f32 sp78;
    f32 sp8C;
    f32 sp90;
    f32 sp94;
    s32 spA8;
    s32 spAC;
    s32 unksp18;
    s32 unksp24;
    s32 unksp34;
    s32 unksp44;
    s32 unksp54;
    f32 v64[3];
    f32 unksp70;
    f32 unksp88;
    s32 unkspA4;
    s32 unkspC;
    f32 unkspF0;
    s32 sp1FC;
    s32 sp1CC;
    s32 sp19C;
    s32 sp16C;
    s32 sp13C;
    s32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    s16 spA;
    u16 sp8;
    Vec *temp_r3_2;
    Vec *temp_r3_3;
    Vec *temp_r3_6;
    Vec *temp_r3_7;
    Vec *temp_r4;
    Vec *temp_r4_2;
    Vec *temp_r4_3;
    Vec *temp_r4_4;
    Vec *temp_r4_5;
    _EmitParams *var_r30;
    f32 temp_f29;
    f32 temp_f31;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f27;
    f32 var_f28;
    f32 var_f30;
    s32 temp_cr0_eq;
    s32 temp_r0;
    u16 temp_r3;
    s32 var_r27;
    u32 temp_r29;
    s32 sp14;
    u8 *temp_r3_4;
    u8 *temp_r3_5;

    temp_r31 = M2C_FIELD(this, u8 **, 0xFC);
    var_r27 = p0;
    temp_f31 = M2C_FIELD(temp_r31, f32 *, 8);
    spA = M2C_FIELD(this, u16 *, 0x4A) + var_r27;
    temp_r29 = ((u32) M2C_FIELD(temp_r31, u32 *, 0) >> 6U) & 1;
    sp8 = var_r27;
    var_f30 = temp_f31 * M2C_ERROR(/* psq_l unimplemented */);
    var_f27 = 0.0f;
    temp_f29 = 1.0f / M2C_ERROR(/* psq_l unimplemented */);
    var_r30 = g_emitParams;
    var_f28 = 1.0f;
loop_36:
    temp_cr0_eq = var_r27 == 0;
    var_r27 -= 1;
    if (temp_cr0_eq == 0) {
        peEmitterNode::GetPositionParameter((GSvec *)((GSvec*)(((u8*)(var_r30) + 8))), (GSvec *)((GSvec*)(&unksp100)), (_pePositionFunction *)((_pePositionFunction*)(temp_r31 + 0x34)), (float)(M2C_ERROR(/* Read from unset register $r6 */)));
        temp_r3 = M2C_FIELD(temp_r31, u16 *, 0x74);
        temp_r0 = temp_r3 & 2;
        switch (temp_r0) {                          /* irregular */
        case 0:
            C_QUATRotAxisRad((Quaternion*)(&unkspF0), (const Vec*)(temp_r31 + 0x84), (M2C_FIELD(temp_r31, f32 *, 0x9C) * HSD_Randf()) + M2C_FIELD(temp_r31, f32 *, 0x98));
            PSMTXQuat((Mtx)((s32) &sp10C), (const Quaternion *)((const register Quaternion*)(&unkspF0)));
            PSMTXMultVecSR((const Mtx)(&sp10C), (const Vec *)((const register Vec*)(temp_r31 + 0x78)), (Vec *)((register Vec*)(&unksp70)));
            M2C_FIELD(var_r30, f32 *, 0x14) = unksp70;
            M2C_FIELD(var_r30, f32 *, 0x18) = sp74;
            M2C_FIELD(var_r30, f32 *, 0x1C) = sp78;
            C_QUATRotAxisRad((Quaternion*)(&unkspF0), (const Vec*)(temp_r31 + 0x78), 3.1415927f * (2.0f * HSD_Randf()));
            PSMTXQuat((Mtx)((s32) &sp13C), (const Quaternion *)((const register Quaternion*)(&unkspF0)));
            temp_r4 = (Vec *)(((u8*)(var_r30) + 0x14));
            PSMTXMultVecSR((const Mtx)((s32) &sp13C), (const Vec *)((const register Vec*)(temp_r4)), (Vec *)((register Vec*)(temp_r4)));
            if (M2C_FIELD(temp_r31, u16 *, 0x74) & 0x20) {
                var_f1 = (var_f30 * M2C_FIELD(temp_r31, f32 *, 0x94)) + M2C_FIELD(temp_r31, f32 *, 0x90);
            } else {
                var_f1 = (M2C_FIELD(temp_r31, f32 *, 0x94) * HSD_Randf()) + M2C_FIELD(temp_r31, f32 *, 0x90);
            }
            temp_r3_2 = (Vec *)(((u8*)(var_r30) + 0x14));
            PSVECScale((const register Vec*)(temp_r3_2), (register Vec*)(temp_r3_2), var_f1);
            break;
        case 2:
            if (temp_r3 & 0x20) {
                var_f1_2 = (var_f30 * M2C_FIELD(temp_r31, f32 *, 0x7C)) + M2C_FIELD(temp_r31, f32 *, 0x78);
            } else {
                var_f1_2 = (M2C_FIELD(temp_r31, f32 *, 0x7C) * HSD_Randf()) + M2C_FIELD(temp_r31, f32 *, 0x78);
            }
            PSVECScale((const register Vec*)(&unksp100), (register Vec*)(v64), var_f1_2);
            M2C_FIELD(var_r30, f32 *, 0x14) = v64[0];
            M2C_FIELD(var_r30, f32 *, 0x18) = v64[1];
            M2C_FIELD(var_r30, f32 *, 0x1C) = v64[2];
            break;
        default:
        case 1:
            M2C_FIELD(var_r30, f32 *, 0x14) = 0.0f;
            M2C_FIELD(var_r30, f32 *, 0x18) = 0.0f;
            M2C_FIELD(var_r30, f32 *, 0x1C) = 0.0f;
            break;
        }
        PSVECScale((const register Vec*)(((u8*)(var_r30) + 0x14)), (register Vec*)(&unkspA4), var_f27);
        temp_r3_3 = (Vec *)(((u8*)(var_r30) + 8));
        unksp100 = unkspA4;
        sp104 = spA8;
        sp108 = spAC;
        PSVECAdd((const register Vec*)(temp_r3_3), (const register Vec*)(&unksp100), (register Vec*)(temp_r3_3));
        temp_r3_4 = M2C_FIELD(this, u8 **, 0xFC);
        M2C_FIELD(var_r30, f32 *, 0) = (f32) (((M2C_FIELD(temp_r3_4, f32 *, 0x24) * HSD_Randf()) + M2C_FIELD(temp_r3_4, f32 *, 0x20)) - var_f27);
        temp_r3_5 = M2C_FIELD(this, u8 **, 0xFC);
        M2C_FIELD(var_r30, f32 *, 4) = (f32) ((M2C_FIELD(temp_r3_5, f32 *, 0x30) * HSD_Randf()) + M2C_FIELD(temp_r3_5, f32 *, 0x2C));
        if (temp_r29 != 0) {
            PSVECSubtract((const register Vec*)(this + 0xA8), (const register Vec*)(this + 0xD0), (register Vec*)(&unksp18));
            sp98 = unksp18;
            sp9C = sp1C;
            spA0 = sp20;
            PSVECScale((const register Vec*)((Vec *) &sp98), (register Vec*)((Vec *) &sp98), var_f28);
            PSVECAdd((const register Vec*)((Vec *) &sp98), (const register Vec*)(this + 0xD0), (register Vec*)((Vec *) &sp98));
            M2C_FIELD(var_r30, f32 *, 0x20) = sp98;
            M2C_FIELD(var_r30, f32 *, 0x24) = sp9C;
            M2C_FIELD(var_r30, f32 *, 0x28) = spA0;
            C_QUATLerp((const Quaternion*)(this + 0xDC), (const Quaternion*)(this + 0xB4), (Quaternion*)(&unksp88), var_f28);
            M2C_FIELD(var_r30, f32 *, 0x2C) = unksp88;
            M2C_FIELD(var_r30, f32 *, 0x30) = sp8C;
            M2C_FIELD(var_r30, f32 *, 0x34) = sp90;
            M2C_FIELD(var_r30, f32 *, 0x38) = sp94;
            PSVECSubtract((const register Vec*)(this + 0xC4), (const register Vec*)(this + 0xEC), (register Vec*)(&unkspC));
            sp7C = unkspC;
            sp80 = sp10;
            sp84 = sp14;
            PSVECScale((const register Vec*)((Vec *) &sp7C), (register Vec*)((Vec *) &sp7C), var_f28);
            PSVECAdd((const register Vec*)((Vec *) &sp7C), (const register Vec*)(this + 0xEC), (register Vec*)((Vec *) &sp7C));
            M2C_FIELD(var_r30, f32 *, 0x3C) = sp7C;
            M2C_FIELD(var_r30, f32 *, 0x40) = sp80;
            M2C_FIELD(var_r30, f32 *, 0x44) = sp84;
            if (M2C_FIELD(temp_r31, u16 *, 0x34) & 0x100) {
                temp_r3_6 = (Vec *)(((u8*)(var_r30) + 8));
                PSVECSubtract((const register Vec*)(temp_r3_6), (const register Vec*)(((u8*)(var_r30) + 0x20)), (register Vec*)(temp_r3_6));
                PSQUATInverse((const register Quaternion*)(((u8*)(var_r30) + 0x2C)), (register Quaternion*)(&unksp54));
                spE0 = unksp54;
                spE4 = sp58;
                spE8 = sp5C;
                spEC = sp60;
                PSMTXQuat((Mtx)((s32) &sp1FC), (const Quaternion *)((const register Quaternion*)((Quaternion *) &spE0)));
                temp_r4_2 = (Vec *)(((u8*)(var_r30) + 8));
                PSMTXMultVecSR((const Mtx)((s32) &sp1FC), (const Vec *)((const register Vec*)(temp_r4_2)), (Vec *)((register Vec*)(temp_r4_2)));
                if ((M2C_FIELD(var_r30, f32 *, 0x3C)) != 0.0f) {
                    M2C_FIELD(var_r30, f32 *, 8) = (f32) (M2C_FIELD(var_r30, f32 *, 8) / (M2C_FIELD(var_r30, f32 *, 0x3C)));
                }
                if ((M2C_FIELD(var_r30, f32 *, 0x40)) != 0.0f) {
                    M2C_FIELD(var_r30, f32 *, 0xC) = (f32) (M2C_FIELD(var_r30, f32 *, 0xC) / (M2C_FIELD(var_r30, f32 *, 0x40)));
                }
                if ((M2C_FIELD(var_r30, f32 *, 0x44)) != 0.0f) {
                    M2C_FIELD(var_r30, f32 *, 0x10) = (f32) (M2C_FIELD(var_r30, f32 *, 0x10) / (M2C_FIELD(var_r30, f32 *, 0x44)));
                }
            }
            if (M2C_FIELD(temp_r31, u16 *, 0x74) & 0x10) {
                PSQUATInverse((const register Quaternion*)(((u8*)(var_r30) + 0x2C)), (register Quaternion*)(&unksp44));
                spD0 = unksp44;
                spD4 = sp48;
                spD8 = sp4C;
                spDC = sp50;
                PSMTXQuat((Mtx)((s32) &sp1CC), (const Quaternion *)((const register Quaternion*)((Quaternion *) &spD0)));
                temp_r4_3 = (Vec *)(((u8*)(var_r30) + 0x14));
                PSMTXMultVecSR((const Mtx)((s32) &sp1CC), (const Vec *)((const register Vec*)(temp_r4_3)), (Vec *)((register Vec*)(temp_r4_3)));
            }
        } else {
            if (M2C_FIELD(temp_r31, u16 *, 0x34) & 0x100) {
                temp_r3_7 = (Vec *)(((u8*)(var_r30) + 8));
                PSVECSubtract((const register Vec*)(temp_r3_7), (const register Vec*)(this + 0xA8), (register Vec*)(temp_r3_7));
                PSQUATInverse((const register Quaternion*)(this + 0xB4), (register Quaternion*)(&unksp34));
                spC0 = unksp34;
                spC4 = sp38;
                spC8 = sp3C;
                spCC = sp40;
                PSMTXQuat((Mtx)((s32) &sp19C), (const Quaternion *)((const register Quaternion*)((Quaternion *) &spC0)));
                temp_r4_4 = (Vec *)(((u8*)(var_r30) + 8));
                PSMTXMultVecSR((const Mtx)((s32) &sp19C), (const Vec *)((const register Vec*)(temp_r4_4)), (Vec *)((register Vec*)(temp_r4_4)));
                if ((M2C_FIELD(this, f32 *, 0xC4)) != 0.0f) {
                    M2C_FIELD(var_r30, f32 *, 8) = (f32) (M2C_FIELD(var_r30, f32 *, 8) / (M2C_FIELD(this, f32 *, 0xC4)));
                }
                if ((M2C_FIELD(this, f32 *, 0xC8)) != 0.0f) {
                    M2C_FIELD(var_r30, f32 *, 0xC) = (f32) (M2C_FIELD(var_r30, f32 *, 0xC) / (M2C_FIELD(this, f32 *, 0xC8)));
                }
                if ((M2C_FIELD(this, f32 *, 0xCC)) != 0.0f) {
                    M2C_FIELD(var_r30, f32 *, 0x10) = (f32) (M2C_FIELD(var_r30, f32 *, 0x10) / (M2C_FIELD(this, f32 *, 0xCC)));
                }
            }
            if (M2C_FIELD(temp_r31, u16 *, 0x74) & 0x10) {
                PSQUATInverse((const register Quaternion*)(this + 0xB4), (register Quaternion*)(&unksp24));
                spB0 = unksp24;
                spB4 = sp28;
                spB8 = sp2C;
                spBC = sp30;
                PSMTXQuat((Mtx)((s32) &sp16C), (const Quaternion *)((const register Quaternion*)((Quaternion *) &spB0)));
                temp_r4_5 = (Vec *)(((u8*)(var_r30) + 0x14));
                PSMTXMultVecSR((const Mtx)((s32) &sp16C), (const Vec *)((const register Vec*)(temp_r4_5)), (Vec *)((register Vec*)(temp_r4_5)));
            }
        }
        var_f30 -= temp_f31;
        var_r30 += 0x48;
        var_f28 -= temp_f29;
        var_f27 += p1 * temp_f29;
        goto loop_36;
    }
}
}

}

extern "C++" {
void peEmitterNode::SetLastLoop() {
    f32 temp_f0;
    f32 temp_f2;
    u16 temp_r5;
    u8 *temp_r4;

    temp_r5 = M2C_FIELD(this, u16 *, 0x48);
    if (!(temp_r5 & 0x40) && (M2C_FIELD(M2C_FIELD(this, u8 **, 0xFC), s32 *, 0) & 1)) {
        M2C_FIELD(this, u16 *, 0x48) = (u16) (temp_r5 | 0x40);
        temp_r4 = M2C_FIELD(this, u8 **, 0xFC);
        temp_f2 = M2C_FIELD(temp_r4, f32 *, 0x18) + M2C_FIELD(temp_r4, f32 *, 0x1C);
        if (M2C_FIELD(this, f32 *, 4) < (temp_f0 = M2C_FIELD(temp_r4, f32 *, 0x28) - temp_f2)) {
            M2C_FIELD(this, f32 *, 4) = temp_f0;
            M2C_FIELD(this, f32 *, 0x30) = temp_f2;
        }
    }
}
}

extern "C++" {
void peEmitterNode::CreateWorldParams() {
    s32 sp10;
    s32 sp14;
    s32 sp1C;
    s32 sp20;
    s32 sp28;
    s32 sp2C;
    s32 spC;
    u32 unksp18;
    u32 unksp24;
    s32 unksp8;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    u32 temp_r31;

    temp_r31 = *M2C_FIELD(this, u32 **, 0xFC);
    M2C_FIELD(this, f32 *, 0xD0) = (f32) M2C_FIELD(this, f32 *, 0xA8);
    M2C_FIELD(this, f32 *, 0xD4) = (f32) M2C_FIELD(this, f32 *, 0xAC);
    M2C_FIELD(this, f32 *, 0xD8) = (f32) M2C_FIELD(this, f32 *, 0xB0);
    M2C_FIELD(this, f32 *, 0xDC) = (f32) M2C_FIELD(this, f32 *, 0xB4);
    M2C_FIELD(this, f32 *, 0xE0) = (f32) M2C_FIELD(this, f32 *, 0xB8);
    M2C_FIELD(this, f32 *, 0xE4) = (f32) M2C_FIELD(this, f32 *, 0xBC);
    M2C_FIELD(this, f32 *, 0xE8) = (f32) M2C_FIELD(this, f32 *, 0xC0);
    M2C_FIELD(this, f32 *, 0xEC) = (f32) M2C_FIELD(this, f32 *, 0xC4);
    M2C_FIELD(this, f32 *, 0xF0) = (f32) M2C_FIELD(this, f32 *, 0xC8);
    M2C_FIELD(this, f32 *, 0xF4) = (f32) M2C_FIELD(this, f32 *, 0xCC);
    if (M2C_FIELD(this, u16 *, 0x48) & 1) {
        M2C_FIELD(this, f32 *, 0xB4) = (f32) -M2C_FIELD(this, f32 *, 0x64);
    } else {
        M2C_FIELD(this, f32 *, 0xB4) = (f32) M2C_FIELD(this, f32 *, 0x64);
    }
    if (M2C_FIELD(this, u16 *, 0x48) & 2) {
        M2C_FIELD(this, f32 *, 0xB8) = (f32) -M2C_FIELD(this, f32 *, 0x68);
    } else {
        M2C_FIELD(this, f32 *, 0xB8) = (f32) M2C_FIELD(this, f32 *, 0x68);
    }
    if (M2C_FIELD(this, u16 *, 0x48) & 4) {
        M2C_FIELD(this, f32 *, 0xBC) = (f32) -M2C_FIELD(this, f32 *, 0x6C);
    } else {
        M2C_FIELD(this, f32 *, 0xBC) = (f32) M2C_FIELD(this, f32 *, 0x6C);
    }
    PSVECAdd((const register Vec*)(this + 8), (const register Vec*)(this + 0x74), (register Vec*)(&unksp18));
    sp3C = unksp18;
    sp40 = sp1C;
    sp44 = sp20;
    PSQUATMultiply((const register Quaternion*)(this + 0x80), (const register Quaternion*)(this + 0xB4), (register Quaternion*)(&unksp8));
    M2C_FIELD(this, f32 *, 0xC0) = (f32) M2C_FIELD(this, f32 *, 0x70);
    sp48 = unksp8;
    sp4C = spC;
    sp50 = sp10;
    sp54 = sp14;
    sp58 = M2C_FIELD(this, f32 *, 0x58);
    sp5C = M2C_FIELD(this, f32 *, 0x5C);
    sp60 = M2C_FIELD(this, f32 *, 0x60);
    peNodeTransformsConcat((peXform*)(this + 0xA8), (peXform*)(M2C_FIELD(this, peXform **, 0x20)), (peXform*)((peXform *) &sp3C), (temp_r31 >> 1U) & 1);
    PSVECSubtract((const register Vec*)(this + 0xA8), (const register Vec*)(&g_CameraPosition), (register Vec*)(&unksp24));
    sp30 = unksp24;
    sp34 = sp28;
    sp38 = sp2C;
    M2C_FIELD(this, f32 *, 0xF8) = PSVECDotProduct((const register Vec*)(&g_CameraLookDir), (const register Vec*)((Vec *) &sp30));
    if ((u16) M2C_FIELD(this, u16 *, 0x4A) == 0) {
        M2C_FIELD(this, f32 *, 0xD0) = (f32) M2C_FIELD(this, f32 *, 0xA8);
        M2C_FIELD(this, f32 *, 0xD4) = (f32) M2C_FIELD(this, f32 *, 0xAC);
        M2C_FIELD(this, f32 *, 0xD8) = (f32) M2C_FIELD(this, f32 *, 0xB0);
        M2C_FIELD(this, f32 *, 0xDC) = (f32) M2C_FIELD(this, f32 *, 0xB4);
        M2C_FIELD(this, f32 *, 0xE0) = (f32) M2C_FIELD(this, f32 *, 0xB8);
        M2C_FIELD(this, f32 *, 0xE4) = (f32) M2C_FIELD(this, f32 *, 0xBC);
        M2C_FIELD(this, f32 *, 0xE8) = (f32) M2C_FIELD(this, f32 *, 0xC0);
        M2C_FIELD(this, f32 *, 0xEC) = (f32) M2C_FIELD(this, f32 *, 0xC4);
        M2C_FIELD(this, f32 *, 0xF0) = (f32) M2C_FIELD(this, f32 *, 0xC8);
        M2C_FIELD(this, f32 *, 0xF4) = (f32) M2C_FIELD(this, f32 *, 0xCC);
    }
}
}

extern "C++" {
#pragma optimize_for_size on
#pragma optimize_for_size reset
}

extern "C++" {
void peEmitterNode::GetPositionParameter(GSvec* p0, GSvec* p1, _pePositionFunction* p2, float p3) {
    f32 sp10;
    f32 sp18;
    f32 sp1C;
    volatile f32 sp24;
    f32 sp28;
    volatile f32 sp30;
    f32 sp34;
    s32 sp48;
    s32 sp4C;
    f32 sp54;
    f32 sp58;
    f32 spC;
    f32 unksp14;
    f32 unksp20;
    f32 unksp2C;
    u32 v38[3];
    u32 unksp44;
    f32 unksp50;
    s32 unksp5C;
    f32 unksp8;
    s32 sp108;
    s32 spD8;
    s32 spA8;
    s32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f1_6;
    f32 var_f1_7;
    f32 var_f1_8;
    f32 var_f1_9;
    s32 temp_r0;
    u16 temp_r5;

    temp_r5 = M2C_FIELD(p1, u16 *, 0);
    temp_r0 = temp_r5 & 3;
    switch (temp_r0) {                              /* irregular */
    case 0:
        M2C_FIELD(p0, f32 *, 0) = (f32) M2C_FIELD(p1, f32 *, 0x1C);
        M2C_FIELD(p0, f32 *, 4) = (f32) M2C_FIELD(p1, f32 *, 0x20);
        M2C_FIELD(p0, f32 *, 8) = (f32) M2C_FIELD(p1, f32 *, 0x24);
        var_f1 = M2C_FIELD(p1, f32 *, 0x34);
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (!(var_f1 > 0.00001f)) {
            var_f1_2 = M2C_FIELD(p1, f32 *, 0x38);
            if (var_f1_2 < 0.0f) {
                var_f1_2 = -var_f1_2;
            }
            if (var_f1_2 > 0.00001f) {
                goto block_13;
            }
            goto block_21;
        }
block_13:
        if (PSVECSquareMag((const register Vec*)((Vec *) p0)) > 0.00001f) {
            if (M2C_FIELD(p1, u16 *, 0) & 0x80) {
                var_f1_3 = 3.1415927f * (2.0f * (M2C_FIELD(p1, f32 *, 0x3C) * p3));
            } else {
                var_f1_3 = (2.0f * HSD_Randf());
                var_f1_3 *= 3.1415927f;
            }
            C_QUATRotAxisRad((Quaternion*)(&unksp5C), (const Vec*)((Vec *) p0), var_f1_3);
            PSMTXQuat((Mtx)((s32) &spD8), (const Quaternion *)((const register Quaternion*)(&unksp5C)));
            PSMTXMultVecSR((const Mtx)((s32) &spD8), (const Vec *)((const register Vec*)(((u8*)(p1) + 0x28))), (Vec *)((register Vec*)(&unksp50)));
            M2C_FIELD(((s32)this), f32 *, 0) = unksp50;
            M2C_FIELD(((s32)this), f32 *, 4) = sp54;
            M2C_FIELD(((s32)this), f32 *, 8) = sp58;
            if (M2C_FIELD((u16)p1, u16 *, 0) & 0x20) {
                var_f1_4 = (p3 * M2C_FIELD(p1, f32 *, 0x38)) + M2C_FIELD(p1, f32 *, 0x34);
            } else {
                var_f1_4 = (M2C_FIELD(p1, f32 *, 0x38) * HSD_Randf()) + M2C_FIELD(p1, f32 *, 0x34);
            }
            PSVECScale((const register Vec*)((Vec *) ((s32)this)), (register Vec*)((Vec *) ((s32)this)), var_f1_4);
        } else {
block_21:
            M2C_FIELD(((s32)this), f32 *, 0) = 0.0f;
            M2C_FIELD(((s32)this), f32 *, 4) = 0.0f;
            M2C_FIELD(((s32)this), f32 *, 8) = 0.0f;
        }
        if (M2C_FIELD(p1, u16 *, 0) & 0x10) {
            PSVECScale((const register Vec*)(((u8*)(p1) + 0x10)), (register Vec*)(&unksp44), p3);
            sp6C = unksp44;
            sp70 = sp48;
            sp74 = sp4C;
        } else {
            PSVECScale((const register Vec*)(((u8*)(p1) + 0x10)), (register Vec*)(v38), HSD_Randf());
            sp6C = v38[0];
            sp70 = v38[1];
            sp74 = v38[2];
        }
        PSVECAdd((const register Vec*)((Vec *) &sp6C), (const register Vec*)(((u8*)(p1) + 4)), (register Vec*)((Vec *) &sp6C));
        PSVECAdd((const register Vec*)((Vec *) ((s32)this)), (const register Vec*)((Vec *) &sp6C), (register Vec*)((Vec *) ((s32)this)));
        if (PSVECSquareMag((const register Vec*)((Vec *) ((s32)this))) > 0.00001f) {
            PSVECNormalize((const register Vec*)((Vec *) ((s32)this)), (register Vec*)(&unksp2C));
            M2C_FIELD((u16)p0, f32 *, 0) = unksp2C;
            M2C_FIELD(p0, f32 *, 4) = sp30;
            M2C_FIELD(p0, f32 *, 8) = sp34;
            return;
        }
        M2C_FIELD(p0, f32 *, 0) = 0.0f;
        M2C_FIELD(p0, f32 *, 4) = 0.0f;
        M2C_FIELD(p0, f32 *, 8) = 0.0f;
        return;
    case 1:
        if (temp_r5 & 0x40) {
            var_f1_5 = (M2C_FIELD(p1, f32 *, 0x28) * (M2C_FIELD(p1, f32 *, 0x2C) * p3)) + M2C_FIELD(p1, f32 *, 0x24);
        } else {
            var_f1_5 = (M2C_FIELD(p1, f32 *, 0x28) * HSD_Randf()) + M2C_FIELD(p1, f32 *, 0x24);
        }
        C_QUATRotAxisRad((Quaternion*)(&unksp5C), (const Vec*)(((u8*)(p1) + 0x10)), var_f1_5);
        PSMTXQuat((Mtx)((s32) &spA8), (const Quaternion *)((const register Quaternion*)(&unksp5C)));
        PSMTXMultVecSR((const Mtx)((s32) &spA8), (const Vec *)((const register Vec*)(((u8*)((s32)p1) + 4))), (Vec *)((register Vec*)(&unksp20)));
        M2C_FIELD(p0, f32 *, 0) = unksp20;
        M2C_FIELD(p0, f32 *, 4) = sp24;
        M2C_FIELD(p0, f32 *, 8) = sp28;
        if (M2C_FIELD(p1, u16 *, 0) & 0x80) {
            var_f1_6 = 3.1415927f * (2.0f * (M2C_FIELD(p1, f32 *, 0x30) * p3));
        } else {
            var_f1_6 = 3.1415927f * (2.0f * HSD_Randf());
        }
        C_QUATRotAxisRad((Quaternion*)(&unksp5C), (const Vec*)(((u8*)(p1) + 4)), var_f1_6);
        PSMTXQuat((Mtx)((s32) &sp108), (const Quaternion *)((const register Quaternion*)(&unksp5C)));
        PSMTXMultVecSR((const Mtx)((s32) &sp108), (const Vec *)((const register Vec*)((Vec *) p0)), (Vec *)((register Vec*)((Vec *) p0)));
        if (M2C_FIELD(p1, u16 *, 0) & 0x20) {
            var_f1_7 = (p3 * M2C_FIELD(p1, f32 *, 0x20)) + M2C_FIELD(p1, f32 *, 0x1C);
        } else {
            var_f1_7 = (M2C_FIELD(p1, f32 *, 0x20) * HSD_Randf()) + M2C_FIELD(p1, f32 *, 0x1C);
        }
        PSVECScale((const register Vec*)((Vec *) p0), (register Vec*)(&unksp14), var_f1_7);
        M2C_FIELD(((s32)this), f32 *, 0) = unksp14;
        M2C_FIELD(((s32)this), f32 *, 4) = sp18;
        M2C_FIELD(((s32)this), f32 *, 8) = sp1C;
        return;
    case 3:
        M2C_FIELD(p0, f32 *, 0) = (f32) M2C_FIELD(p1, f32 *, 0x10);
        M2C_FIELD(p0, f32 *, 4) = (f32) M2C_FIELD(p1, f32 *, 0x14);
        M2C_FIELD(p0, f32 *, 8) = (f32) M2C_FIELD(p1, f32 *, 0x18);
        if (M2C_FIELD(p1, u16 *, 0) & 0x80) {
            var_f1_8 = 3.1415927f * (2.0f * (M2C_FIELD(p1, f32 *, 0x30) * p3));
        } else {
            var_f1_8 = 3.1415927f * (2.0f * HSD_Randf());
        }
        C_QUATRotAxisRad((Quaternion*)(&unksp5C), (const Vec*)((Vec *) p0), var_f1_8);
        PSMTXQuat((Mtx)((s32) &sp78), (const Quaternion *)((const register Quaternion*)(&unksp5C)));
        PSMTXMultVecSR((const Mtx)((s32) &sp78), (const Vec *)((const register Vec*)(((u8*)(p1) + 0x1C))), (Vec *)((register Vec*)(&unksp8)));
        M2C_FIELD(((s32)this), f32 *, 0) = unksp8;
        M2C_FIELD(((s32)this), f32 *, 4) = spC;
        M2C_FIELD(((s32)this), f32 *, 8) = sp10;
        if (M2C_FIELD((u16)p1, u16 *, 0) & 0x20) {
            var_f1_9 = (p3 * M2C_FIELD(p1, f32 *, 0x2C)) + M2C_FIELD(p1, f32 *, 0x28);
        } else {
            var_f1_9 = (M2C_FIELD(p1, f32 *, 0x2C) * HSD_Randf()) + M2C_FIELD(p1, f32 *, 0x28);
        }
        PSVECScale((const register Vec*)((Vec *) ((s32)this)), (register Vec*)((Vec *) ((s32)this)), var_f1_9);
        PSVECAdd((const register Vec*)((Vec *) ((s32)this)), (const register Vec*)(((u8*)(p1) + 4)), (register Vec*)((Vec *) ((s32)this)));
        return;
    default:
    case 2:
        M2C_FIELD(((s32)this), f32 *, 0) = 0.0f;
        M2C_FIELD(((s32)this), f32 *, 4) = 0.0f;
        M2C_FIELD(((s32)this), f32 *, 8) = 0.0f;
        M2C_FIELD(p0, f32 *, 0) = 0.0f;
        M2C_FIELD(p0, f32 *, 4) = 0.0f;
        M2C_FIELD(p0, f32 *, 8) = 0.0f;
        return;
    }
}
}
}
}
}
}
