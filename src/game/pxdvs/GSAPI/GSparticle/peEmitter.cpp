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
    _peEmitter* data;
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
void peNodeTransformsConcat(peXform* out, peXform* a, peXform* b, u32 useGfx);
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
    if (started == 0) {
        return 0;
    }
    u32 flags = *(u32*)data;
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
    switch (M2C_FIELD(g_current_layer, s32 *, 0x28)) {
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
    u8 *var_r28_2;
    s32 sp14;
    volatile f32 sp38;
    volatile s32 sp1E;
    f32 sp30;
    s32 sp48;
    volatile f32 sp44;
    volatile f32 sp40;
    s32 unksp20;
    volatile s32 sp1D;
    f32 sp34;
    f32 sp3C;
    volatile u8 sp1C;
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
    volatile s32 temp_r29;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 var_r0;
    s32 temp_r3_20;
    s32 var_r29;
    u32 var_r3;
    u8 *temp_r3_21;
    u8 *temp_r4;
    u8 *var_r28;
    volatile s32 sp10;
    u8 *var_r28_3;

    temp_r29 = M2C_FIELD(p1, s32 *, 0);
    if (((peNode*)((peNode *) this))->Update((peEmitterNode*)(p0), p2) == 0) {
        if ((p0 == NULL) && (temp_r29 & 1)) {
            if (M2C_FIELD(this, u16 *, 0x48) & 0x40) {
                return 0U;
            }
            M2C_FIELD(this, u16 *, 0x48) = (u16) (M2C_FIELD(this, u16 *, 0x48) & 0xFFFFFFDF);
            M2C_FIELD(this, f32 *, 4) = (f32) (M2C_FIELD(this, f32 *, 4) + M2C_FIELD(p1, f32 *, 0x1C));
            M2C_FIELD(this, f32 *, 0x30) = (f32) (M2C_FIELD(this, f32 *, 0x30) - (M2C_FIELD(p1, f32 *, 0x28) - M2C_FIELD(p1, f32 *, 0x18)));
            M2C_FIELD(this, u16 *, 0x4A) = 0U;
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
    M2C_FIELD(this, f32 *, 0x38) = (f32) (0.00390625f * (2.0f * M2C_ERROR( )));
    if (sp9 < sp1D) sp9 = sp1D;
    M2C_FIELD(this, f32 *, 0x3C) = (f32) (0.00390625f * (2.0f * M2C_ERROR( )));
    sp8 = sp1E;
    M2C_FIELD(this, f32 *, 0x40) = (f32) (0.00390625f * (2.0f * M2C_ERROR( )));
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
                PSMTXQuat((f32 (*)[4])(&sp48), (const Quaternion *)((const register Quaternion*)(M2C_FIELD(this, s32 *, 0x20) + 0xC)));
                PSMTXMultVecSR((f32 (*)[4])(&sp48), (const Vec *)((const register Vec*)((Vec *) &sp30)), (Vec *)((register Vec*)((Vec *) &sp30)));
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
        if ((M2C_FIELD((s32)this, u16 *, 0x48) & 0x10) && (temp_r3_21 = M2C_FIELD(this, u8 **, 0xFC), ((M2C_FIELD(this, f32 *, 0x30) > (M2C_FIELD(temp_r3_21, f32 *, 0x18) + M2C_FIELD(temp_r3_21, f32 *, 0x1C))) != 0))) {
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
                M2C_FIELD(this, f32 *, 0x34) = (f32) (((temp_f29 * var_f1_33 * p2) + M2C_FIELD(this, f32 *, 0x34)) - M2C_ERROR( ));
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
typedef f32 PeMtx[3][4];

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
    u32 flags;
    u8 pad4[4];
    f32 rate;
    u8 padc[0x14];
    f32 lifeBase;
    f32 lifeRange;
    u8 pad28[4];
    f32 speedBase;
    f32 speedRange;
    u16 posFlags;
    u8 pad36[0x3e];
    u16 velFlags;
    u8 pad76[2];
    Vec dir;
    Vec axis;
    f32 magBase;
    f32 magRange;
    f32 coneBase;
    f32 coneRange;
};

struct peEmitterNodeE {
    u8 pad0[0x4a];
    u16 emitted;
    u8 pad4c[0x5c];
    peXformE cur;
    peXformE prev;
    u8 padf8[4];
    peEmitterDefE* def;
};

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
    PSQUATInverse(rot, &q);
    quatToMtxE(m, q);
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
    Vec d;
    Vec r;
    PSVECSubtract(a, b, &d);
    r = d;
    PSVECScale(&r, &r, t);
    PSVECAdd(&r, b, &r);
    *dst = r;
}

static inline f32 __OSu16tof32E(register const u16* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 3 }
    return ret;
}

static inline f32 u16tof32E(u16 v) {
    return __OSu16tof32E(&v);
}

void peEmitterNode::CreateParameters(unsigned short count, float dt) {
    peEmitterNodeE* self = (peEmitterNodeE*)this;
    peEmitterDefE* def = self->def;
    f32 rate = def->rate;
    f32 phase = rate * u16tof32E(self->emitted + count);
    f32 inv = 1.0f / u16tof32E(count);
    _EmitParamsE* ep = (_EmitParamsE*)g_emitParams;
    u32 interp;
    _pePositionFunction* posFn;
    posFn = (_pePositionFunction*)&def->posFlags;
    interp = (def->flags >> 6) & 1;
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
            Vec t;
            C_QUATRotAxisRad(&q, &def->axis, HSD_Randf() * def->coneRange + def->coneBase);
            peMtxQuat(m, &q);
            peMtxMultVecSR(m, &def->dir, &t);
            ep->vel = t;
            C_QUATRotAxisRad(&q, &def->dir, 3.1415927f * (2.0f * HSD_Randf()));
            rotateForwardE(&ep->vel, &q);
            f32 s;
            if (def->velFlags & 0x20) {
                s = phase * def->magRange;
                s += def->magBase;
            } else {
                s = HSD_Randf() * def->magRange + def->magBase;
            }
            PSVECScale(&ep->vel, &ep->vel, s);
            break;
        }
        case 2: {
            Vec t;
            f32 s;
            if (def->velFlags & 0x20) {
                s = phase * def->dir.y + def->dir.x;
            } else {
                s = HSD_Randf() * def->dir.y + def->dir.x;
            }
            PSVECScale(&dir, &t, s);
            ep->vel = t;
            break;
        }
        default:
            ep->vel.x = 0.0f;
            ep->vel.y = 0.0f;
            ep->vel.z = 0.0f;
            break;
        }
        {
            Vec t;
            PSVECScale(&ep->vel, &t, timeOff);
            dir = t;
            PSVECAdd(&ep->pos, &dir, &ep->pos);
        }
        ep->life = (HSD_Randf() * self->def->lifeRange + self->def->lifeBase) - timeOff;
        ep->speed = HSD_Randf() * self->def->speedRange + self->def->speedBase;
        if (interp) {
            Quaternion q;
            lerpVecE(&ep->xf.pos, &self->cur.pos, &self->prev.pos, lerpT);
            C_QUATLerp(&self->prev.rot, &self->cur.rot, &q, lerpT);
            ep->xf.rot = q;
            lerpVecE(&ep->xf.scale, &self->cur.scale, &self->prev.scale, lerpT);
            if (def->posFlags & 0x100) {
                PSVECSubtract(&ep->pos, &ep->xf.pos, &ep->pos);
                rotateInverseE(&ep->pos, &ep->xf.rot);
                divScaleE(&ep->pos, &ep->xf.scale);
            }
            if (def->velFlags & 0x10) {
                rotateInverseE(&ep->vel, &ep->xf.rot);
            }
        } else {
            if (def->posFlags & 0x100) {
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
struct peEmitterNodeW {
    u8 pad0[8];
    Vec pos;
    u8 pad14[0xc];
    peXform* parent;
    u8 pad24[0x24];
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
}

extern "C++" {
#pragma optimize_for_size on
#pragma optimize_for_size reset
}

extern "C++" {
#pragma push
#pragma optimize_for_size on
void peEmitterNode::GetPositionParameter(GSvec* p0, GSvec* p1, _pePositionFunction* p2, float p3) {
    f32 sp10;
    f32 sp18;
    f32 sp1C;
    u32 unksp44;
    f32 sp28;
    u32 v38[3];
    f32 sp34;
    s32 sp48;
    s32 sp4C;
    volatile f32 sp54;
    f32 sp58;
    f32 sp6C;
    s32 spD8;
    f32 unksp50;
    f32 unksp2C;
    volatile f32 sp30;
    volatile f32 sp24;
    f32 unksp20;
    s32 unksp5C;
    s32 sp78;
    s32 sp108;
    f32 unksp14;
    s32 spA8;
    f32 unksp8;
    f32 sp74;
    f32 sp70;
    volatile f32 spC;
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
    switch (temp_r0) {
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
            PSMTXQuat((f32 (*)[4])(&spD8), (const Quaternion *)((const register Quaternion*)(&unksp5C)));
            PSMTXMultVecSR((f32 (*)[4])(&spD8), (const Vec *)((const register Vec*)(((u8*)(p1) + 0x28))), (Vec *)((register Vec*)(&unksp50)));
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
        PSMTXQuat((f32 (*)[4])(&spA8), (const Quaternion *)((const register Quaternion*)(&unksp5C)));
        PSMTXMultVecSR((f32 (*)[4])(&spA8), (const Vec *)((const register Vec*)(((u8*)((s32)p1) + 4))), (Vec *)((register Vec*)(&unksp20)));
        M2C_FIELD(p0, f32 *, 0) = unksp20;
        M2C_FIELD(p0, f32 *, 4) = sp24;
        M2C_FIELD(p0, f32 *, 8) = sp28;
        if (M2C_FIELD(p1, u16 *, 0) & 0x80) {
            var_f1_6 = 3.1415927f * (2.0f * (M2C_FIELD(p1, f32 *, 0x30) * p3));
        } else {
            var_f1_6 = (2.0f * HSD_Randf());
            var_f1_6 *= 3.1415927f;
        }
        C_QUATRotAxisRad((Quaternion*)(&unksp5C), (const Vec*)(((u8*)(p1) + 4)), var_f1_6);
        PSMTXQuat((f32 (*)[4])(&sp108), (const Quaternion *)((const register Quaternion*)(&unksp5C)));
        PSMTXMultVecSR((f32 (*)[4])(&sp108), (const Vec *)((const register Vec*)((Vec *) p0)), (Vec *)((register Vec*)((Vec *) p0)));
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
            var_f1_8 = (2.0f * HSD_Randf());
            var_f1_8 *= 3.1415927f;
        }
        C_QUATRotAxisRad((Quaternion*)(&unksp5C), (const Vec*)((Vec *) p0), var_f1_8);
        PSMTXQuat((f32 (*)[4])(&sp78), (const Quaternion *)((const register Quaternion*)(&unksp5C)));
        PSMTXMultVecSR((f32 (*)[4])(&sp78), (const Vec *)((const register Vec*)(((u8*)(p1) + 0x1C))), (Vec *)((register Vec*)(&unksp8)));
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
#pragma pop
}
}
}
}
}
