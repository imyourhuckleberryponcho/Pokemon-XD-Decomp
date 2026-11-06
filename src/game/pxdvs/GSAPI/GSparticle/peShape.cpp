#ifndef __MWERKS__
#include <game/psq.h>
#endif
#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gcdata.h>
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
enum GSgfxCunitAlpha { GSgfxCunitAlpha_draft_dummy };
enum GSgfxCunitSrc { GSgfxCunitSrc_draft_dummy };
enum GSgfxDiffuseFunc { GSgfxDiffuseFunc_draft_dummy };
struct GSgfxLayer;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
struct GSgfxLight;
enum GSgfxLightType { GSgfxLightType_draft_dummy };
struct GSgfxMatrixStack;
enum GSgfxTunitKReg { GSgfxTunitKReg_draft_dummy };
struct GSgfxVF;
struct GSmtx;
typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];
struct Quaternion;
struct Vec;
struct _EmitParams;
struct _peShape;
struct peColorSpline;
class peContainer;
struct peEmitterNode;
struct peNode;
class peShapeContainer;
struct peShapeNode;
struct peSpline;
struct peXform;

extern "C++" {
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
#ifdef __MWERKS__
    s32 drawIcosahedron();
#else
    void drawIcosahedron();
#endif
#ifdef __MWERKS__
    s32 drawCylinder(unsigned char);
#else
    void drawCylinder(unsigned char p0);
#endif
    void drawSphere(unsigned char, unsigned char);
#ifdef __MWERKS__
    s32 cunitChannelGen(unsigned char, GSgfxCunitAlpha, GSgfxCunitSrc, GSgfxCunitSrc, u32, GSgfxLight**, GSgfxLightType, GSgfxDiffuseFunc);
#else
    void cunitChannelGen(unsigned char chan, GSgfxCunitAlpha alpha, GSgfxCunitSrc amb, GSgfxCunitSrc mat,
                                 u32 numLights, GSgfxLight** lights, GSgfxLightType type,
                                 GSgfxDiffuseFunc diffuse);
#endif
#ifdef __MWERKS__
    s32 drawOctahedron();
#else
    void drawOctahedron();
#endif
    void drawSphere(unsigned char);
#ifdef __MWERKS__
    s32 drawDodecaedron();
#else
    void drawDodecaedron();
#endif
#ifdef __MWERKS__
    s32 drawCube();
#else
    void drawCube();
#endif
#ifdef __MWERKS__
    s32 drawTorus(float, unsigned char, unsigned char);
#else
    void drawTorus(float p0, unsigned char p1, unsigned char p2);
#endif
    void tunitKRegSel(unsigned char, GSgfxTunitKReg);
};
struct GSgfxLight {
    u8 _draft[1];
};
struct GSgfxMatrixStack {
    u8 _draft[1];
#ifdef __MWERKS__
    s32 pop();
#else
    void pop();
#endif
    void pushMult(GSmtx*);
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSmtx {
    u8 _draft[1];
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
    virtual u16 Emit(unsigned short n) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Stop() = 0;

#ifdef __MWERKS__
    s32 MoveNode(peNode*, peNode*);
#else
    void MoveNode(peNode* node, peNode* after);
#endif
#ifdef __MWERKS__
    s32 RemoveAll();
#else
    void RemoveAll();
#endif
#ifdef __MWERKS__
    s32 RemoveNode(peNode*);
#else
    void RemoveNode(peNode* node);
#endif
    u16 CreateNodes(unsigned short);
    static void SetLayerVisibility(GSgfxLayerID, bool);
};
struct peEmitterNode {
    u8 _draft[1];
};
struct peNode {
    u8 _draft[1];
    bool Update(peEmitterNode*, float);
    void Start(peEmitterNode*, _EmitParams*);
};
class peShapeContainer : public peContainer {
public:
    PE_SHAPE_CONTAINER_MEMBERS

    peShapeContainer(peEmitterNode*, _peShape*, unsigned short);
    virtual ~peShapeContainer();
    virtual void Start();
    virtual u16 Emit(unsigned short);
    virtual void Update(float);
    virtual void Render();
    virtual void Stop();
};
struct peShapeNode {
    u8 _draft[1];
    u8 Update(peEmitterNode*, _peShape*, float);
    void Start(peEmitterNode*, _peShape*, _EmitParams*);
    void Render(_peShape*);
};
struct peSpline {
    u8 _draft[1];
};
struct peXform {
    u8 _draft[1];
};

extern "C" {
int EulerToQuat(Vec* euler, Quaternion* q);
s32 GSboundAlwaysInView(u32 bound, s32 inView);
GSgfxVF* GSgfxVFGetPredef(s32 id);
f32 HSD_Randf(void);
asm void PSMTXConcat(const register Mtx a, const register Mtx b, register Mtx ab);
asm void PSMTXMultVec(const register Mtx m, const register Vec* src, register Vec* dst);
asm void PSMTXMultVecSR(const register Mtx m, const register Vec* src, register Vec* dst);
void PSMTXQuat(register Mtx m, const register Quaternion* q);
void PSMTXScale(register Mtx m, register f32 xS, register f32 yS, register f32 zS);
asm void PSMTXTransApply(const register Mtx src, register Mtx dst, register f32 xT, register f32 yT, register f32 zT);
void PSQUATMultiply(const register Quaternion* p, const register Quaternion* q, register Quaternion* pq);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
asm f32 PSVECDotProduct(const register Vec* a, const register Vec* b);
void PSVECNormalize(const register Vec* src, register Vec* unit);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
f32 PSVECSquareMag(const register Vec* v);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double atan2(double y, double x);
s32 particleEngineSetDefaultRenderState(s32);
s32 particleEngineSetupBlendMode(s32);
enum GStexFilter { GS_TEXFILTER_NEAR = 0, GS_TEXFILTER_LINEAR = 2 };
void particleEngineSetupTexture(u8, s32, s32, s32, s32, s32);
void peColorSplineGetValue(u8* out, peColorSpline* s, f32 t);
void peNodeTransformsConcat(peXform* out, peXform* a, peXform* b, bool useGfx);
f32 peSplineGetValue(peSpline* s, f32 t);
extern f32 __float_nan[];
extern Vec g_CameraLookDir;
extern GCsptr g_CameraMatrix;
extern Vec g_CameraPosition;
extern u32 g_currentBound;
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
extern Vec unitScaleVector;
extern s32 jtbl_1954;
extern s32 this_;
extern s32 jtbl_1843;
}

void peShapeContainer::Stop() {
    if ((u8) THIS_F(u8 *, 0x19, started) != 0) {
        ((peContainer*)this)->PreUpdate();
        THIS_F(u8 *, 0x19, started) = 0U;
        if (*THIS_F(s32 **, 0x20, shape) & 0x800000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, false);
        }
        if (*THIS_F(s32 **, 0x20, shape) & 0x01000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, false);
        }
        if (*THIS_F(s32 **, 0x20, shape) & 0x02000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, false);
        }
        ((peContainer*)((peContainer *) this))->RemoveAll();
    }
}
}

extern "C++" {
extern "C++" {

#define LAYER_FIELD(l, T, off) (*(T*)((u8*)(l) + (off)))
static inline void layerMark(GSgfxLayer* l, u32 sum, u32 off, u32 bit) {
    LAYER_FIELD(l, u32, off) |= bit;
    LAYER_FIELD(l, u32, 0x16A8) |= sum;
    LAYER_FIELD(l, u32, off + 0xB8) |= bit;
    LAYER_FIELD(l, u32, 0x1760) |= sum;
}

struct peShapeLightVec : Vec {
    peShapeLightVec(const Vec& o) {
        x = o.x;
        y = o.y;
        z = o.z;
    }
    peShapeLightVec(f32 x_, f32 y_, f32 z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

struct peShapeLight {
    u16 dirty;
    u8 pad2[2];
    s32 type;
    u32 color;
    Vec pos;
    Vec dir;
};

static inline void lightSetPos(GSgfxLight* light, const Vec& p) {
    peShapeLight* l = (peShapeLight*)light;
    f32 x = p.x;
    f32 y = p.y;
    f32 z = p.z;
    Vec v;
    v.x = x;
    v.y = y;
    v.z = z;
    switch (l->type) {
    case 0:
        return;
    case 1:
        l->pos.x = v.x;
        l->pos.y = v.y;
        l->pos.z = v.z;
        break;
    case 2:
        l->pos.x = v.x;
        l->pos.y = v.y;
        l->pos.z = v.z;
        break;
    }
    l->dirty |= 2;
}

static inline void lightSetDir(GSgfxLight* light, Vec* dir) {
    peShapeLight* l = (peShapeLight*)light;
    switch (l->type) {
    case 0:
    case 1:
        l->dir.x = dir->x;
        l->dir.y = dir->y;
        l->dir.z = dir->z;
        l->dirty |= 4;
        break;
    }
}

struct peShapeLayerLights {
    u8 pad0[0xD94];
    u8 numLights;
    u8 padD95[3];
    GSgfxLight* lights[8];
};

static inline void layerSetLights(GSgfxLayer* l, u8 n, GSgfxLight** lights) {
    peShapeLayerLights* ll = (peShapeLayerLights*)l;
    ll->numLights = n;
    for (u8 i = 0; i < 8; i++) {
        if (i < n) {
            ll->lights[i] = lights[i];
        } else {
            ll->lights[i] = NULL;
        }
    }
    layerMark(l, 4, 0x16BC, 0x10);
}

static inline bool canRender(peShapeContainer* c) {
    if (!c->started) {
        return false;
    }
    u32 flags = GC_AT(u32, c->shape, 0);
    if (c->count == 0) {
        return false;
    }
    if (g_render_pass != 1) {
        return false;
    }
    switch (M2C_NAMED(g_current_layer, s32 *, 0x28, id)) {
    case 0:
        if (flags & 0x200000) {
            return true;
        }
        break;
    case 2:
        if (flags & 0x400000) {
            return true;
        }
        if (!(flags & 0x03E00008)) {
            return true;
        }
        break;
    case 4:
        if (flags & 8) {
            return true;
        }
        break;
    case 1:
        if (flags & 0x800000) {
            return true;
        }
        break;
    case 3:
        if (flags & 0x01000000) {
            return true;
        }
        break;
    case 5:
        if (flags & 0x02000000) {
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}

extern "C++" {
#pragma push
void peShapeContainer::Render() {
    peShapeNode *var_r30_2;
    s32 temp_r31;
    s32 var_r7;
    s32 var_r8;

    if (THIS_F(u8 *, 0x19, started)) {
        if (canRender(this)) {
            temp_r31 = GC_AT(s32, THIS_F(_peShape **, 0x20, shape), 0);
            if (temp_r31 & 0x800) {
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
            var_r8 = 0;
            if (temp_r31 & 0x40) {
                var_r8 = 2;
            }
            _peShape* sh = THIS_F(_peShape **, 0x20, shape);
            particleEngineSetupTexture(0, GC_AT(s32, sh, 0x74), 0, 0, (temp_r31 & 0x20) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR, var_r8);
            particleEngineSetupBlendMode(2);
            if (temp_r31 & 0x200) {
                GSgfxLight* light0;
                GSgfxLight* light1;
                GSgfxLight* lights[2] = {NULL, NULL};
                u8 numLights;
                light0 = GC_AT(GSgfxLight*, THIS_F(_peShape **, 0x20, shape), 0x78);
                numLights = 1;
                lights[0] = light0;
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s8, 0xEAC) = 1;
                    layerMark(l, 8, 0x16CC, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s8, 0xDB8) = 1;
                    layerMark(l, 4, 0x16BC, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1170) = 0;
                    LAYER_FIELD(l, s32, 0x1174) = 0;
                    LAYER_FIELD(l, s32, 0x1178) = 0;
                    LAYER_FIELD(l, s8, 0x117C) = 1;
                    LAYER_FIELD(l, s32, 0x1180) = 0;
                    layerMark(l, 8, 0x16DC, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x12B0) = 0;
                    LAYER_FIELD(l, s32, 0x12B4) = 0;
                    LAYER_FIELD(l, s32, 0x12B8) = 0;
                    LAYER_FIELD(l, s8, 0x12BC) = 1;
                    LAYER_FIELD(l, s32, 0x12C0) = 0;
                    layerMark(l, 8, 0x16E0, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xF70) = 0xF;
                    LAYER_FIELD(l, s32, 0xF74) = 0xA;
                    LAYER_FIELD(l, s32, 0xF78) = 8;
                    LAYER_FIELD(l, s32, 0xF7C) = 0xF;
                    layerMark(l, 8, 0x16D4, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1544) = 0x1C;
                    layerMark(l, 0x10, 0x1700, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1070) = 7;
                    LAYER_FIELD(l, s32, 0x1074) = 6;
                    LAYER_FIELD(l, s32, 0x1078) = 4;
                    LAYER_FIELD(l, s32, 0x107C) = 7;
                    layerMark(l, 8, 0x16D8, 1);
                }
                Vec dir;
                Vec pos;
                PSMTXMultVec((MtxPtr)(g_CameraMatrix), (Vec*)((u8*)THIS_F(_peShape **, 0x20, shape) + 0x5C), &pos);
                lightSetPos(light0, pos);
                g_current_layer->cunitChannelGen(0, (GSgfxCunitAlpha)0, (GSgfxCunitSrc)0, (GSgfxCunitSrc)0, 1, &light0, (GSgfxLightType)2, (GSgfxDiffuseFunc)2);
                if (temp_r31 & 0x400) {
                    light1 = GC_AT(GSgfxLight*, THIS_F(_peShape **, 0x20, shape), 0x7C);
                    numLights = 2;
                    lights[1] = light1;
                    {
                        GSgfxLayer* l = g_current_layer;
                        LAYER_FIELD(l, s8, 0xEAC) = 2;
                        layerMark(l, 8, 0x16CC, 1);
                    }
                    {
                        GSgfxLayer* l = g_current_layer;
                        LAYER_FIELD(l, s32, 0xEBC) = 0xFF;
                        LAYER_FIELD(l, s32, 0xEC0) = 0xFF;
                        LAYER_FIELD(l, s32, 0xEC4) = 5;
                        layerMark(l, 8, 0x16D0, 2);
                    }
                    {
                        GSgfxLayer* l = g_current_layer;
                        LAYER_FIELD(l, s32, 0x1184) = 0;
                        LAYER_FIELD(l, s32, 0x1188) = 0;
                        LAYER_FIELD(l, s32, 0x118C) = 0;
                        LAYER_FIELD(l, s8, 0x1190) = 1;
                        LAYER_FIELD(l, s32, 0x1194) = 0;
                        layerMark(l, 8, 0x16DC, 2);
                    }
                    {
                        GSgfxLayer* l = g_current_layer;
                        LAYER_FIELD(l, s32, 0x12C4) = 0;
                        LAYER_FIELD(l, s32, 0x12C8) = 0;
                        LAYER_FIELD(l, s32, 0x12CC) = 0;
                        LAYER_FIELD(l, s8, 0x12D0) = 0;
                        LAYER_FIELD(l, s32, 0x12D4) = 0;
                        layerMark(l, 8, 0x16E0, 2);
                    }
                    {
                        GSgfxLayer* l = g_current_layer;
                        LAYER_FIELD(l, s32, 0xF80) = 0xF;
                        LAYER_FIELD(l, s32, 0xF84) = 0xA;
                        LAYER_FIELD(l, s32, 0xF88) = 0xC;
                        LAYER_FIELD(l, s32, 0xF8C) = 0;
                        layerMark(l, 8, 0x16D4, 2);
                    }
                    {
                        GSgfxLayer* l = g_current_layer;
                        LAYER_FIELD(l, s32, 0x1080) = 7;
                        LAYER_FIELD(l, s32, 0x1084) = 7;
                        LAYER_FIELD(l, s32, 0x1088) = 7;
                        LAYER_FIELD(l, s32, 0x108C) = 0;
                        layerMark(l, 8, 0x16D8, 2);
                    }
                    {
                        GSgfxLayer* l = g_current_layer;
                        LAYER_FIELD(l, s8, 0xDB8) = 2;
                        layerMark(l, 4, 0x16BC, 1);
                    }
                    g_current_layer->cunitChannelGen(1, (GSgfxCunitAlpha)0, (GSgfxCunitSrc)0, (GSgfxCunitSrc)0, 1, &light1, (GSgfxLightType)0, (GSgfxDiffuseFunc)2);
                    Vec* src = (Vec*)((u8*)THIS_F(_peShape **, 0x20, shape) + 0x5C);
                    if (PSVECSquareMag(src) < 0.00001f) {
                        dir.x = 0.0f;
                        dir.y = -1.0f;
                        dir.z = 0.0f;
                    } else {
                        Vec* p = (Vec*)((u8*)THIS_F(_peShape **, 0x20, shape) + 0x5C);
                        dir = peShapeLightVec(-p->x, -p->y, -p->z);
                        PSVECNormalize(&dir, &dir);
                    }
                    PSMTXMultVecSR((MtxPtr)(g_CameraMatrix), &dir, &dir);
                    lightSetDir(light1, &dir);
                }
                layerSetLights(g_current_layer, numLights, lights);
            } else {
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s8, 0xDB8) = 0;
                    layerMark(l, 4, 0x16BC, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s8, 0xEAC) = 1;
                    layerMark(l, 8, 0x16CC, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xEB0) = 0;
                    LAYER_FIELD(l, s32, 0xEB4) = 0;
                    LAYER_FIELD(l, s32, 0xEB8) = 0xFF;
                    layerMark(l, 8, 0x16D0, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1170) = 0;
                    LAYER_FIELD(l, s32, 0x1174) = 0;
                    LAYER_FIELD(l, s32, 0x1178) = 0;
                    LAYER_FIELD(l, s8, 0x117C) = 1;
                    LAYER_FIELD(l, s32, 0x1180) = 0;
                    layerMark(l, 8, 0x16DC, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x12B0) = 0;
                    LAYER_FIELD(l, s32, 0x12B4) = 0;
                    LAYER_FIELD(l, s32, 0x12B8) = 0;
                    LAYER_FIELD(l, s8, 0x12BC) = 1;
                    LAYER_FIELD(l, s32, 0x12C0) = 0;
                    layerMark(l, 8, 0x16E0, 1);
                }
                ((GSgfxLayer*)(g_current_layer))->tunitKRegSel(0U, (GSgfxTunitKReg)(0));
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0xF70) = 0xF;
                    LAYER_FIELD(l, s32, 0xF74) = 0xE;
                    LAYER_FIELD(l, s32, 0xF78) = 8;
                    LAYER_FIELD(l, s32, 0xF7C) = 0xF;
                    layerMark(l, 8, 0x16D4, 1);
                }
                {
                    GSgfxLayer* l = g_current_layer;
                    LAYER_FIELD(l, s32, 0x1070) = 7;
                    LAYER_FIELD(l, s32, 0x1074) = 6;
                    LAYER_FIELD(l, s32, 0x1078) = 4;
                    LAYER_FIELD(l, s32, 0x107C) = 7;
                    layerMark(l, 8, 0x16D8, 1);
                }
            }
            M2C_NAMED(g_current_layer, GSgfxVF **, 0x199C, curVF) = GSgfxVFGetPredef(4);
            var_r30_2 = THIS_F(peShapeNode **, 0x10, activeList);
            while (var_r30_2 != NULL) {
                ((peShapeNode*)(var_r30_2))->Render((_peShape*)(THIS_F(_peShape **, 0x20, shape)));
                var_r30_2 = (peShapeNode*)PE_NODE_LINK28(var_r30_2);
            }
            particleEngineSetDefaultRenderState(1);
        }
    }
}
#pragma pop
}
void GSgfxLayer::tunitKRegSel(unsigned char p0, GSgfxTunitKReg p1) {
    s32 bit;

    switch (p1) {
    case 0:
        hw.kcsel[p0] = 0xC;
        bit = 1 << p0;
        dirty[0].kcsel |= bit;
        dirty[0].groups |= 0x10;
        dirty[1].kcsel |= bit;
        dirty[1].groups |= 0x10;
        hw.kasel[p0] = 0x1C;
        dirty[0].kasel |= bit;
        dirty[0].groups |= 0x10;
        dirty[1].kasel |= bit;
        dirty[1].groups |= 0x10;
        return;
    case 1:
        hw.kcsel[p0] = 0xD;
        bit = 1 << p0;
        dirty[0].kcsel |= bit;
        dirty[0].groups |= 0x10;
        dirty[1].kcsel |= bit;
        dirty[1].groups |= 0x10;
        hw.kasel[p0] = 0x1D;
        dirty[0].kasel |= bit;
        dirty[0].groups |= 0x10;
        dirty[1].kasel |= bit;
        dirty[1].groups |= 0x10;
        return;
    case 2:
        hw.kcsel[p0] = 0xE;
        bit = 1 << p0;
        dirty[0].kcsel |= bit;
        dirty[0].groups |= 0x10;
        dirty[1].kcsel |= bit;
        dirty[1].groups |= 0x10;
        hw.kasel[p0] = 0x1E;
        dirty[0].kasel |= bit;
        dirty[0].groups |= 0x10;
        dirty[1].kasel |= bit;
        dirty[1].groups |= 0x10;
        return;
    case 3:
        hw.kcsel[p0] = 0xF;
        bit = 1 << p0;
        dirty[0].kcsel |= bit;
        dirty[0].groups |= 0x10;
        dirty[1].kcsel |= bit;
        dirty[1].groups |= 0x10;
        hw.kasel[p0] = 0x1F;
        dirty[0].kasel |= bit;
        dirty[0].groups |= 0x10;
        dirty[1].kasel |= bit;
        dirty[1].groups |= 0x10;
        return;
    }
}
extern "C++" {
#pragma push
#pragma dont_inline on
#define PE_NEXT(n) PE_NODE_LINK28(n)
#define PE_PREV(n) PE_NODE_LINK2C(n)
#define PE_DEPTH(n) PE_NODE_F(n, f32, 0x84)
#ifdef __MWERKS__
#define PSC(T, off, m) (*(T*)((u8*)this + (off)))
#else
#define PSC(T, off, m) (*(T*)&this->m)
#endif

void peShapeContainer::Update(float dt) {
    peNode* node;
    peNode* next;
    peNode* pos;
    peNode* prev;
    f32 depth;

    if (PSC(u8, 0x19, started) == 0) {
        return;
    }
    for (node = PSC(peNode*, 0x10, activeList); node != NULL; node = next) {
        next = PE_NEXT(node);
        if (!((peShapeNode*)node)->Update(PSC(peEmitterNode*, 0x0, emitter), PSC(_peShape*, 0x20, shape), dt)) {
            ((peContainer*)this)->RemoveNode(node);
        }
    }
    if (g_currentBound != 0 && PSC(peNode*, 0x10, activeList) != NULL) {
        GSboundAlwaysInView(g_currentBound, 1);
    }
    if (PSC(u8, 0x19, started) != 0 && (*PSC(u32*, 0x20, shape) & 0x80) && PSC(u16, 0x14, count) >= 2) {
        for (node = PE_NEXT(PSC(peNode*, 0x10, activeList)); node != NULL; node = next) {
            depth = PE_DEPTH(node);
            pos = node;
            for (prev = PE_PREV(node); prev != NULL && PE_DEPTH(prev) < depth; prev = PE_PREV(prev)) {
                pos = prev;
            }
            next = PE_NEXT(node);
            if (pos != node) {
                ((peContainer*)this)->MoveNode(node, pos);
            }
        }
    }
}
extern "C++" {
u16 peShapeContainer::Emit(unsigned short count) {
    u16 var_r31;
    _EmitParams *var_r30;
    peShapeNode *var_r3;
    peShapeNode *temp_r29;
    u16 temp_r28;

    if ((u8) THIS_F(u8 *, 0x19, started) == 0) {
        return 0U;
    }
    var_r31 = ((peContainer*)this)->CreateNodes(count);
    var_r30 = g_emitParams;
    var_r3 = THIS_F(peShapeNode **, 0x10, activeList);
    temp_r28 = var_r31;
    while (var_r31 != 0) {
        temp_r29 = (peShapeNode*)PE_NODE_LINK28(var_r3);
        ((peShapeNode*)(var_r3))->Start((peEmitterNode*)(THIS_F(peEmitterNode **, 0, emitter)), (_peShape*)(THIS_F(_peShape **, 0x20, shape)), (_EmitParams*)(var_r30));
        var_r3 = temp_r29;
        var_r31 -= 1;
        var_r30 += 0x48;
    }
    return temp_r28;
}
}
#pragma pop
}

extern "C++" {
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
}

}

extern "C++" {
extern "C++" {
#pragma peephole off
#pragma peephole reset
}

extern "C++" {
void peShapeContainer::Start() {
    if ((u8) THIS_F(u8 *, 0x19, started) == 0) {
        THIS_F(u8 *, 0x19, started) = 1U;
        if (*THIS_F(s32 **, 0x20, shape) & 0x800000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, true);
        }
        if (*THIS_F(s32 **, 0x20, shape) & 0x01000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, true);
        }
        if (*THIS_F(s32 **, 0x20, shape) & 0x02000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, true);
        }
    }
}
}

extern "C++" {
peShapeContainer::~peShapeContainer() {
    g_particle_debug_stats.unk4 -= 0x24;
    g_particle_debug_stats.unk14 -= 0x24;
}
}

extern "C++" {
#ifndef __MWERKS__
static u32 peShapeNodeSizePC();
#define PE_SHAPE_NODE_SIZE peShapeNodeSizePC()
#else
#define PE_SHAPE_NODE_SIZE 0x9C
#endif
peShapeContainer::peShapeContainer(peEmitterNode* p0, _peShape* p1, unsigned short p2) : peContainer(p0, PE_SHAPE_NODE_SIZE, p2) {
    shape = p1;
    g_particle_debug_stats.unk4 += 0x24;
    g_particle_debug_stats.unk14 += 0x24;
}
}

#pragma push
#pragma dont_inline off
extern "C++" {
struct peShapeColor {
    u32 rgba;
};

static inline void peShapeSetKColor(GSgfxLayer* layer, peShapeColor c) {
#ifdef __MWERKS__
    *(peShapeColor*)((u8*)layer + 0x14F4) = c;
#else
    *(peShapeColor*)&layer->hw.kcolor[0] = c;
#endif
    M2C_NAMED(layer, u32 *, 0x16F8, dirty[0].kcolor) |= 1;
    M2C_NAMED(layer, u32 *, 0x16A8, dirty[0].groups) |= 0x10;
    M2C_NAMED(layer, u32 *, 0x17B0, dirty[1].kcolor) |= 1;
    M2C_NAMED(layer, u32 *, 0x1760, dirty[1].groups) |= 0x10;
}

static inline void peShapeSetChanColor(GSgfxLayer* layer, int ch, peShapeColor amb, peShapeColor mat) {
#ifdef __MWERKS__
    ((peShapeColor*)((u8*)layer + 0xE9C))[ch] = amb;
    ((peShapeColor*)((u8*)layer + 0xEA4))[ch] = mat;
#else
    *(peShapeColor*)&layer->hw.amb[ch] = amb;
    *(peShapeColor*)&layer->hw.mat[ch] = mat;
#endif
    M2C_NAMED(layer, u32 *, 0x16C4, dirty[0].amb) |= 1 << ch;
    M2C_NAMED(layer, u32 *, 0x16C8, dirty[0].mat) |= 1 << ch;
    M2C_NAMED(layer, u32 *, 0x16A8, dirty[0].groups) |= 4;
    M2C_NAMED(layer, u32 *, 0x177C, dirty[1].amb) |= 1 << ch;
    M2C_NAMED(layer, u32 *, 0x1780, dirty[1].mat) |= 1 << ch;
    M2C_NAMED(layer, u32 *, 0x1760, dirty[1].groups) |= 4;
}

struct peShapeSpline {
    u8 flags;
    u8 pad1[3];
    f32 value;
    f32 time;
};
struct peShapeVecC : Vec {
    peShapeVecC(const Vec& o) {
        x = o.x;
        y = o.y;
        z = o.z;
    }
};
struct peShapeQuat {
    f32 x, y, z, w;
};
struct peShapeXform {
    Vec pos;
    peShapeQuat rot;
    Vec scale;
};
struct peShapeEmitParams {
    u32 flags;
};
struct peShapeEmitter {
    u8 pad0[0x38];
    f32 color[4];
    u8 pad48[0xFC - 0x48];
    peShapeEmitParams* params;
};
struct peShapeDef {
    gc_be32 flags;
    gc_bef32 rotX;
    gc_bef32 rotY;
    gc_bef32 rotZ;
    gc_vec(Vec) spin;
    gc_vec(Vec) base;
    gc_vec(Vec) jitter;
    gc_ptr32(peShapeSpline) rotXSpline;
    gc_ptr32(peShapeSpline) rotYSpline;
    gc_ptr32(peShapeSpline) rotZSpline;
    gc_ptr32(peShapeSpline) sclXSpline;
    gc_ptr32(peShapeSpline) sclYSpline;
    gc_ptr32(peShapeSpline) sclZSpline;
    gc_ptr32(peColorSpline) color;
    gc_ptr32(peShapeSpline) alpha;
};
struct peShapeNodeData {
    f32 life0;
    f32 life;
    Vec pos;
    Vec vel;
    peShapeXform* xform;
    f32 speed;
    void* prev;
    void* next;
    peShapeXform world;
    peShapeQuat spinQuat;
    peShapeQuat rotQuat;
    Vec offset;
    f32 sortKey;
    u32 flip;
    Vec spinRate;
    u8 color[4];
};
#ifndef __MWERKS__
static u32 peShapeNodeSizePC() { return sizeof(peShapeNodeData); }
#endif

#ifdef __MWERKS__
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
#else
#include <math.h>
#endif

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

static inline u8 __OSf32tou8(register f32 inF) {
    u32 tmp;
    register u32* tmpPtr = &tmp;
    register u8 ret;
#ifdef __MWERKS__
    asm {
        psq_st inF, 0(tmpPtr), 1, 2
        lbz ret, 0(tmpPtr)
    }
#else
    PSQ_STORE(tmpPtr, 0, inF, 2);
    ret = *(u8*)tmpPtr;
#endif
    return ret;
}

static inline u8 OSf32tou8(f32 in) {
    return __OSf32tou8(in);
}

static inline f32 evalSpline(peShapeSpline* s, f32 t) {
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
    return peSplineGetValue((peSpline*)s, t);
}

#pragma defer_codegen on

extern "C++" {
void peShapeNode::Start(peEmitterNode* p0, _peShape* p1, _EmitParams* p2) {
    peShapeNodeData* n = (peShapeNodeData*)this;
    peShapeEmitter* e = (peShapeEmitter*)p0;
    peShapeDef* s = (peShapeDef*)p1;
    u32 flags = s->flags;
    Vec euler;
    Vec jitter;
    ((peNode*)this)->Start(p0, p2);
    n->flip = 0;
    PSVECScale(GC_VEC3P(Vec, &s->jitter), &jitter, HSD_Randf());
    n->offset = peShapeVecC(jitter);
    PSVECAdd(&n->offset, GC_VEC3P(Vec, &s->base), &n->offset);
    n->spinQuat.x = 0.0f;
    n->spinQuat.y = 0.0f;
    n->spinQuat.z = 0.0f;
    n->spinQuat.w = 1.0f;
    n->world.pos.x = 0.0f;
    n->world.pos.y = 0.0f;
    n->world.pos.z = 0.0f;
    n->world.rot.x = 0.0f;
    n->world.rot.y = 0.0f;
    n->world.rot.z = 0.0f;
    n->world.rot.w = 1.0f;
    n->world.scale = unitScaleVector;
    if (!(e->params->flags & 0x400)) {
        EulerToQuat((Vec*)&s->rotX, (Quaternion*)&n->rotQuat);
        if (flags & 0x1C7000) {
            Vec* ep = &euler;
            if (flags & 0x1000) {
                ep->x = 6.2831855f * HSD_Randf();
            } else {
                ep->x = 0.0f;
            }
            if (flags & 0x2000) {
                ep->y = 6.2831855f * HSD_Randf();
            } else {
                ep->y = 0.0f;
            }
            if (flags & 0x4000) {
                ep->z = 6.2831855f * HSD_Randf();
            } else {
                ep->z = 0.0f;
            }
            if (flags & 0x40000) {
                if (HSD_Randf() < 0.5f) {
                    n->flip |= 1;
                }
            }
            if (flags & 0x80000) {
                if (HSD_Randf() < 0.5f) {
                    n->flip |= 2;
                }
            }
            if (flags & 0x100000) {
                if (HSD_Randf() < 0.5f) {
                    n->flip |= 4;
                }
            }
            EulerToQuat(&euler, (Quaternion*)&n->spinQuat);
        }
    }
    GC_VEC3(n->spinRate, s->spin);
    if (flags & 0x8000) {
        n->spinRate.x *= HSD_Randf();
    }
    if (flags & 0x10000) {
        n->spinRate.y *= HSD_Randf();
    }
    if (flags & 0x20000) {
        n->spinRate.z *= HSD_Randf();
    }
}
}
}

extern "C++" {
u8 peShapeNode::Update(peEmitterNode* p0, _peShape* p1, float p2) {
    peShapeNodeData* n = (peShapeNodeData*)this;
    peShapeEmitter* e = (peShapeEmitter*)p0;
    peShapeDef* s = (peShapeDef*)p1;
    if (!((peNode*)this)->Update(p0, p2)) {
        return 0;
    }
    f32 t = 1.0f - n->life / n->life0;
    u32 pf = e->params->flags;
    Vec euler;
    peShapeXform local;
    peShapeQuat fq;
    Vec v;
    peShapeQuat q;
    Vec d2;
    Vec d;
    Vec delta;
    f32 mtx[3][4];
    peShapeQuat out;
    if (pf & 0x400) {
        v.x = n->vel.x;
        v.y = n->vel.y;
        v.z = n->vel.z;
        if (pf & 0x40) {
            PSMTXQuat(mtx, (Quaternion*)&n->xform->rot);
            PSMTXMultVecSR(mtx, &v, &v);
        }
        f32 len = sqrtf(v.x * v.x + v.z * v.z);
        euler.x = (f32)atan2(-v.y, len);
        euler.y = (f32)atan2(v.x, v.z);
        euler.z = 0.0f;
        EulerToQuat(&euler, (Quaternion*)&n->rotQuat);
    } else if (s->flags & 0x100) {
        euler.x = s->rotX * evalSpline(s->rotXSpline, t);
        euler.y = s->rotY * evalSpline(s->rotYSpline, t);
        euler.z = s->rotZ * evalSpline(s->rotZSpline, t);
        EulerToQuat(&euler, (Quaternion*)&n->rotQuat);
    } else {
        PSVECScale(&n->spinRate, &delta, p2);
        euler.x = delta.x;
        euler.y = delta.y;
        euler.z = delta.z;
        EulerToQuat(&euler, (Quaternion*)&q);
        PSQUATMultiply((Quaternion*)&n->rotQuat, (Quaternion*)&q, (Quaternion*)&n->rotQuat);
    }
    euler.x = n->offset.x * evalSpline(s->sclXSpline, t);
    euler.y = n->offset.y * evalSpline(s->sclYSpline, t);
    euler.z = n->offset.z * evalSpline(s->sclZSpline, t);
    peColorSplineGetValue(n->color, s->color, t);
    n->color[0] = OSf32tou8(e->color[0] * OSu8tof32(n->color[0]));
    n->color[1] = OSf32tou8(e->color[1] * OSu8tof32(n->color[1]));
    n->color[2] = OSf32tou8(e->color[2] * OSu8tof32(n->color[2]));
    n->color[3] = OSf32tou8(255.0f * e->color[3] * evalSpline(s->alpha, t));
    fq.x = (n->flip & 1) ? -n->rotQuat.x : n->rotQuat.x;
    if (n->flip & 2) {
        fq.y = -n->rotQuat.y;
    } else {
        fq.y = n->rotQuat.y;
    }
    if (n->flip & 4) {
        fq.z = -n->rotQuat.z;
    } else {
        fq.z = n->rotQuat.z;
    }
    fq.w = n->rotQuat.w;
    local.pos.x = n->pos.x;
    local.pos.y = n->pos.y;
    local.pos.z = n->pos.z;
    PSQUATMultiply((Quaternion*)&n->spinQuat, (Quaternion*)&fq, (Quaternion*)&out);
    local.rot.x = out.x;
    local.rot.y = out.y;
    local.rot.z = out.z;
    local.rot.w = out.w;
    local.scale.x = euler.x;
    local.scale.y = euler.y;
    local.scale.z = euler.z;
    peNodeTransformsConcat((peXform*)&n->world, (peXform*)n->xform, (peXform*)&local, false);
    PSVECSubtract(&n->world.pos, &g_CameraPosition, &d);
    d2.x = d.x;
    d2.y = d.y;
    d2.z = d.z;
    n->sortKey = PSVECDotProduct(&g_CameraLookDir, &d2);
    return 1;
}
}

void peShapeNode::Render(_peShape* shape) {
    u32 flags = GC_AT(u32, shape, 0);
    peShapeColor black = {0};
    f32 m[3][4];
    f32 rot[3][4];
    peShapeSetKColor(g_current_layer, PE_NODE_F(this, peShapeColor, 0x98));
    if (flags & 0x200) {
        peShapeSetChanColor(g_current_layer, 0, M2C_FIELD(shape, peShapeColor *, 0x68), PE_NODE_F(this, peShapeColor, 0x98));
        if (flags & 0x400) {
            peShapeSetChanColor(g_current_layer, 1, black, PE_NODE_F(this, peShapeColor, 0x98));
        }
    }
    PSMTXQuat(rot, (const Quaternion*)&PE_NODE_F(this, u8, 0x3C));
    PSMTXScale(m, PE_NODE_F(this, f32, 0x4C), PE_NODE_F(this, f32, 0x50), PE_NODE_F(this, f32, 0x54));
    PSMTXConcat(rot, m, m);
    PSMTXTransApply(m, m, PE_NODE_F(this, f32, 0x30), PE_NODE_F(this, f32, 0x34), PE_NODE_F(this, f32, 0x38));
    M2C_NAMED(g_current_layer, GSgfxMatrixStack **, 0x19A0, matrixStack)->pushMult((GSmtx*)m);
    switch (flags & 7) {
    case 0:
        g_current_layer->drawCube();
        break;
    case 1:
        g_current_layer->drawCylinder(M2C_FIELD(shape, u8 *, 0x59));
        break;
    case 2:
        g_current_layer->drawDodecaedron();
        break;
    case 3:
        g_current_layer->drawIcosahedron();
        break;
    case 4:
        g_current_layer->drawOctahedron();
        break;
    case 7:
        g_current_layer->drawTorus(GC_AT(f32, shape, 0x54), M2C_FIELD(shape, u8 *, 0x58), M2C_FIELD(shape, u8 *, 0x59));
        break;
    case 6:
        g_current_layer->drawSphere(M2C_FIELD(shape, u8 *, 0x59));
        break;
    default:
        g_current_layer->drawSphere(M2C_FIELD(shape, u8 *, 0x58), M2C_FIELD(shape, u8 *, 0x59));
        break;
    }
    M2C_NAMED(g_current_layer, GSgfxMatrixStack **, 0x19A0, matrixStack)->pop();
}
}
#pragma pop
}

#pragma dont_inline off
