

#include <dolphin/types.h>

#pragma pool_strings off


extern f32 __float_nan[];
#define NAN (__float_nan[0])
extern "C" {
double atan2(double y, double x);
double fmod(double x, double y);
double __fabs(double x);
}

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
        return NAN;
    } else if (__fpclassifyf(x) == 1) {
        return NAN;
    }
    return x;
}

inline float atan2fInline(float y, float x) {
    float r = (float)atan2(y, x);
    return r;
}

struct Vec3 {
    f32 x, y, z;
};
struct Quat {
    f32 x, y, z, w;
};
struct Vec3C : Vec3 {
    Vec3C(f32 x_, f32 y_, f32 z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

typedef f32 Mtx[3][4];
struct Mtx34 {
    f32 m[3][4];
};
struct GSmtx;

struct peXform {
    Vec3 pos;
    Quat rot;
    Vec3 scale;
};

struct peEmitParams {
    u32 flags;
};

struct peEmitterNode {
    u8 pad0[0x9C];
    Vec3 dir;
    u8 padA8[0x54];
    peEmitParams* params;
};

struct _EmitParams {
    f32 life;
    f32 speed;
    Vec3 pos;
    Vec3 vel;
    Vec3 xpos;
    Quat xrot;
    Vec3 xscale;
};

struct HSD_JObj {
    u8 unk0[0x14];
    u32 flags;
    u8 unk18[0x2C];
    f32 mtx[3][4];
};

struct peSpline {
    u8 flags;
    u8 pad1[3];
    f32 value;
    f32 time;
};


struct _peModel {
    u32 flags;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    Vec3 spin;
    Vec3 base;
    Vec3 jitter;
    peSpline* rotXSpline;
    peSpline* rotYSpline;
    peSpline* rotZSpline;
    peSpline* sclXSpline;
    peSpline* sclYSpline;
    peSpline* sclZSpline;
    HSD_JObj* jobj;
    f32 loopTime;
};

class peNode {
public:
    f32 life0;
    f32 life;
    Vec3 pos;
    Vec3 vel;
    peXform* xform;
    f32 speed;
    peNode* prev;
    peNode* next;

    bool Update(peEmitterNode* e, f32 dt);
    void Start(peEmitterNode* e, _EmitParams* p);
};

class peModelNode : public peNode {
public:
    peXform world;
    u16 flip;
    s16 instance;
    Quat spinQuat;
    Quat rotQuat;
    Vec3 offset;
    Vec3 spinRate;
    f32 sortKey;

    bool Update(peEmitterNode* e, _peModel* m, f32 dt);
    void Start(peEmitterNode* e, _peModel* m, _EmitParams* p);
};

class GSgfxMatrixStack {
public:
    void pushMult(GSmtx* m);
    void pop();
};

struct GSgfxLayer {
    u8 pad0[0x28];
    s32 id;
    u8 pad2C[0x19A0 - 0x2C];
    GSgfxMatrixStack* matrixStack;
    void InvalidateState();
};

struct GScamera {
    u8 pad0[8];
    void* cobj;
};

class peContainer {
public:
    void* emitter;
    u32 unk4;
    void* buffer;
    peNode* freeList;
    peNode* activeList;
    u16 count;
    u16 maxCount;
    u8 dirty;
    u8 started;

    peContainer(peEmitterNode* e, u32 nodeSize, u16 max);
    virtual ~peContainer();
    virtual void Start();
    virtual void PreUpdate();
    virtual u16 Emit(u16 n) = 0;
    virtual void Update(f32 dt) = 0;
    virtual void Render() = 0;
    virtual void Stop() = 0;

    void MoveNode(peNode* node, peNode* after);
    void RemoveAll();
    void RemoveNode(peNode* node);
    u16 CreateNodes(u16 n);
};

class peModelContainer : public peContainer {
public:
    _peModel* model;

    peModelContainer(peEmitterNode* e, _peModel* m, u16 max);
    virtual ~peModelContainer();
    virtual u16 Emit(u16 n);
    virtual void Update(f32 dt);
    virtual void Render();
    virtual void Stop();
};

struct ParticleDebugStats {
    u32 pad0;
    u32 nodeMem;
    u32 pad8;
    u32 pad0c;
    u32 shapeMem;
    u32 total;
    u32 pad18[3];
};
extern ParticleDebugStats g_particle_debug_stats;
extern s32 g_render_pass;
extern GSgfxLayer* g_current_layer;
extern _EmitParams* g_emitParams;
extern void* g_currentBound;
extern Vec3 g_CameraPosition;
extern Vec3 g_CameraLookDir;
extern Vec3 unitScaleVector;
static s32 _primitive_instance_memory;

extern "C" {
void __assert(const char* file, s32 line, const char* expr);
void PSMTXQuat(Mtx34* m, const Quat* q);
void PSMTXScale(Mtx34* m, f32 x, f32 y, f32 z);
void PSMTXConcat(const Mtx34* a, const Mtx34* b, Mtx34* ab);
void PSMTXTransApply(const Mtx34* src, Mtx34* dst, f32 x, f32 y, f32 z);
void PSMTXMultVecSR(const Mtx34* m, const Vec3* src, Vec3* dst);
void PSMTXCopy(const Mtx34* src, Mtx34* dst);
void PSQUATMultiply(const Quat* a, const Quat* b, Quat* dst);
void PSVECScale(const Vec3* src, Vec3* dst, f32 scale);
void PSVECAdd(const Vec3* a, const Vec3* b, Vec3* ab);
void PSVECSubtract(const Vec3* a, const Vec3* b, Vec3* ab);
f32 PSVECDotProduct(const Vec3* a, const Vec3* b);
int EulerToQuat(Vec3* euler, Quat* q);
f32 HSD_Randf();
void GXSetClipMode(int mode);
void HSD_StateInvalidate(s32 state);
void HSD_CObjSetCurrent(void* cobj);
void GSlightSetupLights(void* cobj);
GScamera* GScameraGetActiveCamera();
void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj);
void HSD_JObjReqAnimAll(HSD_JObj* jobj, f32 frame);
void HSD_JObjAnimAll(HSD_JObj* jobj);
void HSD_JObjDispAll(HSD_JObj* jobj, Mtx34* vmtx, u32 flags, u32 rendermode);
u8 GSgfxVideoGetVsyncRate();
void shapeUpdate(u16 id, s16 instance, f32 dt);
void shapeRender(u16 id, s16 instance, s32 layer);
void shapeFreePrimitiveInstance(u16 id, s16 instance);
s16 shapeCreatePrimitiveInstance(u16 id);
u32 shapeGetInstancedMemorySizeAll();
void GSboundAlwaysInView(void* bound, int v);
void particleEngineSetDefaultRenderState(int v);
f32 peSplineGetValue(peSpline* s, f32 t);
void peNodeTransformsConcat(peXform* out, peXform* a, peXform* b, bool useGfx);
}


static inline bool HSD_JObjMtxIsDirty(HSD_JObj* jobj) {
    bool result;
    if (!jobj) {
        __assert("jobj.h", 605, "jobj");
    }
    result = false;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) {
        result = true;
    }
    return result;
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj* jobj) {
    if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjCopyMtx(HSD_JObj* jobj, Mtx mtx) {
    if (!jobj) {
        __assert("jobj.h", 1173, "jobj");
    }
    if (!mtx) {
        __assert("jobj.h", 1174, "mtx");
    }
    PSMTXCopy((Mtx34*)mtx, (Mtx34*)jobj->mtx);
}

static inline f32 evalSpline(peSpline* s, f32 t) {
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
    return peSplineGetValue(s, t);
}


static inline void freeShapeInstance(_peModel* m, peModelNode* n) {
    shapeFreePrimitiveInstance((u16)((s32)m->jobj - 1), n->instance);
    g_particle_debug_stats.shapeMem -= _primitive_instance_memory;
    g_particle_debug_stats.total -= _primitive_instance_memory;
    _primitive_instance_memory = shapeGetInstancedMemorySizeAll();
    g_particle_debug_stats.shapeMem += _primitive_instance_memory;
    g_particle_debug_stats.total += _primitive_instance_memory;
}

void peModelContainer::Stop() {
    if (started) {
        PreUpdate();
        started = 0;
        if (model->flags & 0x40) {
            peNode* n = activeList;
            while (n != 0) {
                peNode* next = n->prev;
                if (model->flags & 0x40) {
                    freeShapeInstance(model, (peModelNode*)n);
                }
                n = next;
            }
        }
        RemoveAll();
    }
}

static inline bool canRender(peModelContainer* c) {
    if (!c->started) {
        return false;
    }
    u32 flags = c->model->flags;
    if (c->count == 0) {
        return false;
    }
    if (g_render_pass != 1) {
        return false;
    }
    switch (g_current_layer->id) {
    case 2:
        if (flags & 2) {
            return false;
        }
        return true;
    case 4:
        if (flags & 2) {
            return true;
        }
        return false;
    default:
        return false;
    }
}

void peModelContainer::Render() {
    if (started) {
        if (canRender(this)) {
            if (!(model->flags & 0x40)) {
                GScamera* cam = GScameraGetActiveCamera();
                if (cam == 0) {
                    return;
                }
                GXSetClipMode(0);
                HSD_StateInvalidate(-1);
                HSD_CObjSetCurrent(cam->cobj);
                GSlightSetupLights(cam->cobj);
            }
            for (peNode* n = activeList; n != 0; n = n->prev) {
                peModelNode* node = (peModelNode*)n;
                _peModel* m = model;
                Mtx mtx;
                Mtx rot;
                PSMTXQuat((Mtx34*)rot, &node->world.rot);
                PSMTXScale((Mtx34*)mtx, node->world.scale.x, node->world.scale.y, node->world.scale.z);
                PSMTXConcat((Mtx34*)rot, (Mtx34*)mtx, (Mtx34*)mtx);
                PSMTXTransApply((Mtx34*)mtx, (Mtx34*)mtx, node->world.pos.x, node->world.pos.y, node->world.pos.z);
                if (m->flags & 0x40) {
                    u16 id = (s32)m->jobj - 1;
                    shapeUpdate(id, node->instance, node->life0 - node->life);
                    g_current_layer->matrixStack->pushMult((GSmtx*)mtx);
                    shapeRender(id, node->instance, g_current_layer->id);
                    g_current_layer->matrixStack->pop();
                } else {
                    HSD_JObj* jobj = m->jobj;
                    if (jobj != 0) {
                        u32 mode;
                        switch (g_render_pass) {
                        case 0:
                            mode = 1;
                            break;
                        case 1:
                            mode = 6;
                            break;
                        default:
                            continue;
                        }
                        HSD_JObjCopyMtx(jobj, *(Mtx*)(&mtx));
                        jobj->flags |= 0x3800000;
                        HSD_JObjSetMtxDirty(jobj);
                        if (m->loopTime > 0.00001f) {
                            f32 t = (node->life0 - node->life) * (f32)GSgfxVideoGetVsyncRate();
                            f32 f = (f32)fmod(t, m->loopTime);
                            HSD_JObjReqAnimAll(jobj, f);
                            HSD_JObjAnimAll(jobj);
                            HSD_JObjDispAll(jobj, 0, 0, mode);
                        }
                    }
                }
            }
            if (!(model->flags & 0x40)) {
                g_current_layer->InvalidateState();
            }
            particleEngineSetDefaultRenderState(1);
        }
    }
}

void peModelContainer::Update(f32 dt) {
    if (started) {
        peNode* n = activeList;
        while (n != 0) {
            peNode* next = n->prev;
            if (!((peModelNode*)n)->Update((peEmitterNode*)emitter, model, dt)) {
                if (model->flags & 0x40) {
                    freeShapeInstance(model, (peModelNode*)n);
                }
                RemoveNode(n);
            }
            n = next;
        }
        if (started && (model->flags & 0x10000) && count >= 2) {
            for (peNode* n2 = activeList->prev; n2 != 0;) {
                f32 key = ((peModelNode*)n2)->sortKey;
                peNode* best = n2;
                peNode* cur = n2->next;
                while (cur != 0 && ((peModelNode*)cur)->sortKey < key) {
                    best = cur;
                    cur = cur->next;
                }
                peNode* next2 = n2->prev;
                if (best != n2) {
                    MoveNode(n2, best);
                }
                n2 = next2;
            }
        }
        if (g_currentBound != 0 && activeList != 0) {
            GSboundAlwaysInView(g_currentBound, 1);
        }
    }
}

u16 peModelContainer::Emit(u16 n) {
    if (!started) {
        return 0;
    }
    u16 left = CreateNodes(n);
    _EmitParams* params = g_emitParams;
    peNode* next;
    peNode* node = activeList;
    u16 created = left;
    while (left != 0) {
        next = node->prev;
        ((peModelNode*)node)->Start((peEmitterNode*)emitter, model, params);
        node = next;
        left--;
        params++;
    }
    return created;
}

peModelContainer::~peModelContainer() {
    g_particle_debug_stats.nodeMem -= 0x24;
    g_particle_debug_stats.total -= 0x24;
}

peModelContainer::peModelContainer(peEmitterNode* e, _peModel* m, u16 max) : peContainer(e, 0x98, max) {
    model = m;
    g_particle_debug_stats.nodeMem += 0x24;
    g_particle_debug_stats.total += 0x24;
}

bool peModelNode::Update(peEmitterNode* e, _peModel* m, f32 dt) {
    u32 flags = m->flags;
    if (!peNode::Update(e, dt)) {
        return false;
    }
    if ((flags & 8) && (life0 - life) >= m->loopTime) {
        return false;
    }
    f32 t = 1.0f - life / life0;
    u32 pf = e->params->flags;
    Vec3 euler;
    peXform local;
    Quat fq;
    Vec3 v;
    Quat q;
    Vec3 d2;
    Vec3 d;
    Vec3 delta;
    Mtx34 mtx;
    Quat out;
    if (pf & 0x400) {
        v.x = vel.x;
        v.y = vel.y;
        v.z = vel.z;
        if (pf & 0x40) {
            PSMTXQuat(&mtx, &xform->rot);
            PSMTXMultVecSR(&mtx, &v, &v);
        }
        f32 len = sqrtf(v.x * v.x + v.z * v.z);
        euler.x = (f32)atan2(-v.y, len);
        euler.y = (f32)atan2(v.x, v.z);
        euler.z = 0.0f;
        EulerToQuat(&euler, &rotQuat);
    } else if (flags & 0x20) {
        euler.x = m->rotX * evalSpline(m->rotXSpline, t);
        euler.y = m->rotY * evalSpline(m->rotYSpline, t);
        euler.z = m->rotZ * evalSpline(m->rotZSpline, t);
        EulerToQuat(&euler, &rotQuat);
    } else {
        PSVECScale(&spinRate, &delta, dt);
        euler.x = delta.x;
        euler.y = delta.y;
        euler.z = delta.z;
        EulerToQuat(&euler, &q);
        PSQUATMultiply(&rotQuat, &q, &rotQuat);
    }
    fq.x = (flip & 1) ? -rotQuat.x : rotQuat.x;
    if (flip & 2) {
        fq.y = -rotQuat.y;
    } else {
        fq.y = rotQuat.y;
    }
    if (flip & 4) {
        fq.z = -rotQuat.z;
    } else {
        fq.z = rotQuat.z;
    }
    fq.w = rotQuat.w;
    euler.x = offset.x * evalSpline(m->sclXSpline, t);
    euler.y = offset.y * evalSpline(m->sclYSpline, t);
    euler.z = offset.z * evalSpline(m->sclZSpline, t);
    local.pos.x = pos.x;
    local.pos.y = pos.y;
    local.pos.z = pos.z;
    PSQUATMultiply(&spinQuat, &fq, &out);
    local.rot.x = out.x;
    local.rot.y = out.y;
    local.rot.z = out.z;
    local.rot.w = out.w;
    local.scale.x = euler.x;
    local.scale.y = euler.y;
    local.scale.z = euler.z;
    peNodeTransformsConcat(&world, xform, &local, false);
    PSVECSubtract(&world.pos, &g_CameraPosition, &d);
    d2.x = d.x;
    d2.y = d.y;
    d2.z = d.z;
    sortKey = PSVECDotProduct(&g_CameraLookDir, &d2);
    return true;
}

void peModelNode::Start(peEmitterNode* e, _peModel* m, _EmitParams* p) {
    u32 flags = m->flags;
    Vec3 euler;
    Vec3 jitter;
    peNode::Start(e, p);
    flip = 0;
    PSVECScale(&m->jitter, &jitter, HSD_Randf());
    offset = Vec3C(jitter.x, jitter.y, jitter.z);
    PSVECAdd(&offset, &m->base, &offset);
    spinQuat.x = 0.0f;
    spinQuat.y = 0.0f;
    spinQuat.z = 0.0f;
    spinQuat.w = 1.0f;
    world.pos.x = 0.0f;
    world.pos.y = 0.0f;
    world.pos.z = 0.0f;
    world.rot.x = 0.0f;
    world.rot.y = 0.0f;
    world.rot.z = 0.0f;
    world.rot.w = 1.0f;
    world.scale = unitScaleVector;
    if (!(e->params->flags & 0x400)) {
        EulerToQuat((Vec3*)&m->rotX, &rotQuat);
        if (flags & 0xE380) {
            if (flags & 0x80) {
                euler.x = 6.2831855f * HSD_Randf();
            } else {
                euler.x = 0.0f;
            }
            if (flags & 0x100) {
                euler.y = 6.2831855f * HSD_Randf();
            } else {
                euler.y = 0.0f;
            }
            if (flags & 0x200) {
                euler.z = 6.2831855f * HSD_Randf();
            } else {
                euler.z = 0.0f;
            }
            if (flags & 0x2000) {
                if (HSD_Randf() < 0.5f) {
                    flip |= 1;
                }
            }
            if (flags & 0x4000) {
                if (HSD_Randf() < 0.5f) {
                    flip |= 2;
                }
            }
            if (flags & 0x8000) {
                if (HSD_Randf() < 0.5f) {
                    flip |= 4;
                }
            }
            EulerToQuat(&euler, &spinQuat);
        }
    }
    spinRate = m->spin;
    if (flags & 0x400) {
        spinRate.x *= HSD_Randf();
    }
    if (flags & 0x800) {
        spinRate.y *= HSD_Randf();
    }
    if (flags & 0x1000) {
        spinRate.z *= HSD_Randf();
    }
    if (m->flags & 0x40) {
        instance = shapeCreatePrimitiveInstance((u16)((s32)m->jobj - 1));
        g_particle_debug_stats.shapeMem -= _primitive_instance_memory;
        g_particle_debug_stats.total -= _primitive_instance_memory;
        _primitive_instance_memory = shapeGetInstancedMemorySizeAll();
        g_particle_debug_stats.shapeMem += _primitive_instance_memory;
        g_particle_debug_stats.total += _primitive_instance_memory;
    }
}
