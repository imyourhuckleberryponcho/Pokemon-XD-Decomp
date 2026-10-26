#include <dolphin/types.h>

struct Vec3 {
    f32 x, y, z;
};

struct Quat {
    f32 x, y, z, w;
    Quat() {}
    Quat(const Quat& o) {
        x = o.x;
        y = o.y;
        z = o.z;
        w = o.w;
    }
    Quat(f32 x_, f32 y_, f32 z_, f32 w_) {
        x = x_;
        y = y_;
        z = z_;
        w = w_;
    }
};

struct Mtx34 {
    f32 m[3][4];
};

struct peXform {
    Vec3 pos;
    Quat rot;
    Vec3 scale;
};

struct peEmitParams {
    u32 flags;
    u8 pad4[0x9C];
    f32 drag;
    f32 bounce;
    f32 force;
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

class peNode {
public:
    f32 life0;
    f32 life;
    Vec3 pos;
    Vec3 vel;
    peXform* xform;
    f32 speed;

    bool Update(peEmitterNode* e, f32 dt);
    void Start(peEmitterNode* e, _EmitParams* p);
};

struct Vec3C : Vec3 {
    Vec3C(f32 x_, f32 y_, f32 z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};
#define vec3(a, b, c) Vec3C(a, b, c)

extern "C" {
void PSMTXQuat(Mtx34* m, const Quat* q);
void PSMTXMultVecSR(const Mtx34* m, const Vec3* src, Vec3* dst);
void PSVECAdd(const Vec3* a, const Vec3* b, Vec3* dst);
void PSVECSubtract(const Vec3* a, const Vec3* b, Vec3* dst);
void PSVECScale(const Vec3* src, Vec3* dst, f32 scale);
f32 PSVECMag(const Vec3* v);
void PSQUATMultiply(const Quat* a, const Quat* b, Quat* dst);
void PSQUATInverse(const Quat* src, Quat* dst);
void C_QUATMtx(Quat* q, const Mtx34* m);
Mtx34* GSgfxMatrixGetPtr(int id);
}

static inline void vecSub(Vec3* dst, const Vec3* a, const Vec3* b) {
    Vec3 t;
    PSVECSubtract(a, b, &t);
    *dst = t;
}

static inline void vecScale(Vec3* dst, const Vec3* a, f32 k) {
    Vec3 t;
    PSVECScale(a, &t, k);
    *dst = t;
}

static inline void quatToMtx(Mtx34* m, Quat q) {
    PSMTXQuat(m, &q);
}

static inline void rotateInverse(Vec3* v, peXform* xf) {
    Mtx34 m;
    Quat q;
    PSQUATInverse(&xf->rot, &q);
    quatToMtx(&m, q);
    PSMTXMultVecSR(&m, v, v);
}

static inline void rotateForward(Vec3* v, peXform* xf) {
    Mtx34 m;
    PSMTXQuat(&m, &xf->rot);
    PSMTXMultVecSR(&m, v, v);
}

static inline void divScale(Vec3* v, peXform* xf) {
    if (0.0f != xf->scale.x) {
        v->x /= xf->scale.x;
    }
    if (0.0f != xf->scale.y) {
        v->y /= xf->scale.y;
    }
    if (0.0f != xf->scale.z) {
        v->z /= xf->scale.z;
    }
}

extern "C" {

void peNodeTransformsConcat(peXform* out, peXform* a, peXform* b, bool useGfx) {
    Mtx34 mtx;
    Quat q;

    {
        f32 pz = b->pos.z * a->scale.z;
        f32 py = a->scale.y;
        py *= b->pos.y;
        f32 px = b->pos.x * a->scale.x;
        out->pos = vec3(px, py, pz);
    }
    PSMTXQuat(&mtx, &a->rot);
    PSMTXMultVecSR(&mtx, &out->pos, &out->pos);
    PSVECAdd(&out->pos, &a->pos, &out->pos);
    if (useGfx) {
        C_QUATMtx(&out->rot, GSgfxMatrixGetPtr(3));
    } else {
        PSQUATMultiply(&a->rot, &b->rot, &q);
        out->rot = q;
    }
    {
        f32 sy = b->scale.y * a->scale.y;
        f32 sz = b->scale.z * a->scale.z;
        f32 sx = b->scale.x * a->scale.x;
        out->scale = vec3(sx, sy, sz);
    }
}
}

bool peNode::Update(peEmitterNode* e, f32 dt) {
    peEmitParams* params;
    bool moving;
    Vec3 dirB;
    Vec3 dirA;
    f32 absSpeed;

    absSpeed = speed;
    if (absSpeed < 0.0f) {
        absSpeed = -absSpeed;
    }
    moving = absSpeed > 0.00001f;
    life -= dt;
    if (life <= 0.0f) {
        return false;
    }
    if (e == 0) {
        return true;
    }
    params = e->params;
    if (moving) {
        dirA = e->dir;
        if (!(params->flags & 0x100)) {
            rotateInverse(&dirA, xform);
        }
        if (params->flags & 0x10000) {
            f32 mag;
            vecSub(&dirB, &dirA, &pos);
            mag = PSVECMag(&dirB);
            if (mag > 0.00001f) {
                PSVECScale(&dirB, &dirB, params->force * speed * dt / mag);
            }
        } else {
            vecScale(&dirB, &dirA, speed * dt);
        }
        PSVECAdd(&vel, &dirB, &vel);
        if (params->drag) {
            PSVECScale(&vel, &vel, 1.0f - params->drag);
        }
    }
    vecScale(&dirB, &vel, dt);
    PSVECAdd(&pos, &dirB, &pos);
    if (moving && (params->flags & 0x200)) {
        dirB = vec3(pos.x * xform->scale.x, pos.y * xform->scale.y, pos.z * xform->scale.z);
        rotateForward(&dirB, xform);
        PSVECAdd(&dirB, &xform->pos, &dirB);
        if (dirB.y <= 0.0f) {
            dirB.y = 0.0f;
            PSVECSubtract(&dirB, &xform->pos, &dirB);
            rotateInverse(&dirB, xform);
            divScale(&dirB, xform);
            pos = dirB;
            dirB = vec3(vel.x * xform->scale.x, vel.y * xform->scale.y, vel.z * xform->scale.z);
            rotateForward(&dirB, xform);
            dirB.y *= params->bounce;
            rotateInverse(&dirB, xform);
            divScale(&dirB, xform);
            vel = dirB;
        }
    }
    return true;
}

void peNode::Start(peEmitterNode* e, _EmitParams* p) {
    life0 = life = p->life;
    speed = p->speed;
    pos = p->pos;
    vel = p->vel;
    if (e == 0) {
        return;
    }
    if (!(e->params->flags & 0x40)) {
        return;
    }
    xform->pos = p->xpos;
    xform->rot = p->xrot;
    xform->scale = p->xscale;
}
