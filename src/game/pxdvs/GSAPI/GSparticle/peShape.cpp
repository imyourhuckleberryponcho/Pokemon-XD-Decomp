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
struct GSgfxLayer {
    u8 _draft[1];
    s32 drawIcosahedron();
    s32 drawCylinder(unsigned char);
    s32 drawSphere(unsigned char, unsigned char);
    s32 cunitChannelGen(unsigned char, GSgfxCunitAlpha, GSgfxCunitSrc, GSgfxCunitSrc, unsigned long, GSgfxLight**, GSgfxLightType, GSgfxDiffuseFunc);
    s32 drawOctahedron();
    s32 drawSphere(unsigned char);
    s32 drawDodecaedron();
    s32 drawCube();
    s32 drawTorus(float, unsigned char, unsigned char);
    void tunitKRegSel(unsigned char, GSgfxTunitKReg);
};
struct GSgfxLight {
    u8 _draft[1];
};
struct GSgfxMatrixStack {
    u8 _draft[1];
    s32 pop();
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

    s32 MoveNode(peNode*, peNode*);
    s32 RemoveAll();
    s32 RemoveNode(peNode*);
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
    _peShape* shape;

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
extern s32 g_CameraMatrix;
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
    if ((u8) M2C_FIELD(this, u8 *, 0x19) != 0) {
        ((peContainer*)this)->PreUpdate();
        M2C_FIELD(this, u8 *, 0x19) = 0U;
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x800000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, false);
        }
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x01000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, false);
        }
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x02000000) {
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
    Vec v;
    v.x = p.x;
    v.y = p.y;
    v.z = p.z;
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
    if (!M2C_FIELD(c, u8 *, 0x19)) {
        return false;
    }
    u32 flags = M2C_FIELD(M2C_FIELD(c, _peShape **, 0x20), u32 *, 0);
    if (M2C_FIELD(c, u16 *, 0x14) == 0) {
        return false;
    }
    if (g_render_pass != 1) {
        return false;
    }
    switch (M2C_FIELD(g_current_layer, s32 *, 0x28)) {
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

    if (M2C_FIELD(this, u8 *, 0x19)) {
        if (canRender(this)) {
            temp_r31 = M2C_FIELD(M2C_FIELD((s32)this, _peShape **, 0x20), s32 *, 0);
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
            _peShape* sh = M2C_FIELD(this, _peShape **, 0x20);
            particleEngineSetupTexture(0, M2C_FIELD(sh, s32 *, 0x74), 0, 0, (temp_r31 & 0x20) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR, var_r8);
            particleEngineSetupBlendMode(2);
            if (temp_r31 & 0x200) {
                GSgfxLight* light0;
                GSgfxLight* light1;
                GSgfxLight* lights[2] = {NULL, NULL};
                u8 numLights;
                light0 = M2C_FIELD(M2C_FIELD(this, _peShape **, 0x20), GSgfxLight **, 0x78);
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
                Vec pos;
                PSMTXMultVec((MtxPtr)(g_CameraMatrix), (Vec*)((u8*)M2C_FIELD(this, _peShape **, 0x20) + 0x5C), &pos);
                lightSetPos(light0, pos);
                g_current_layer->cunitChannelGen(0, (GSgfxCunitAlpha)0, (GSgfxCunitSrc)0, (GSgfxCunitSrc)0, 1, &light0, (GSgfxLightType)2, (GSgfxDiffuseFunc)2);
                if (temp_r31 & 0x400) {
                    light1 = M2C_FIELD(M2C_FIELD(this, _peShape **, 0x20), GSgfxLight **, 0x7C);
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
                    Vec dir;
                    Vec* src = (Vec*)((u8*)M2C_FIELD(this, _peShape **, 0x20) + 0x5C);
                    if (PSVECSquareMag(src) < 0.00001f) {
                        dir.x = 0.0f;
                        dir.y = -1.0f;
                        dir.z = 0.0f;
                    } else {
                        Vec* p = (Vec*)((u8*)M2C_FIELD(this, _peShape **, 0x20) + 0x5C);
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
            M2C_FIELD(g_current_layer, GSgfxVF **, 0x199C) = GSgfxVFGetPredef(4);
            var_r30_2 = M2C_FIELD(this, peShapeNode **, 0x10);
            while (var_r30_2 != NULL) {
                ((peShapeNode*)(var_r30_2))->Render((_peShape*)(M2C_FIELD(this, _peShape **, 0x20)));
                var_r30_2 = M2C_FIELD(var_r30_2, peShapeNode **, 0x28);
            }
            particleEngineSetDefaultRenderState(1);
        }
    }
}
#pragma pop
}
void GSgfxLayer::tunitKRegSel(unsigned char p0, GSgfxTunitKReg p1) {
    u8 *temp_r5_2;
    s32 temp_r6_2;
    u8 *temp_r5_4;
    s32 temp_r6_4;
    u8 *temp_r5;
    s32 temp_r6;
    u8 *temp_r5_3;
    s32 temp_r6_3;

    switch (p1) {
    case 0:
        temp_r5 = (unsigned char *)(this + ((p0 * 4) & 0x3FC));
        M2C_FIELD(temp_r5, s32 *, 0x1504) = 0xC;
        temp_r6 = 1 << p0;
        M2C_FIELD(this, s32 *, 0x16FC) = (s32) (M2C_FIELD(this, s32 *, 0x16FC) | temp_r6);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B4) = (s32) (M2C_FIELD(this, s32 *, 0x17B4) | temp_r6);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        M2C_FIELD(temp_r5, s32 *, 0x1544) = 0x1C;
        M2C_FIELD(this, s32 *, 0x1700) = (s32) (M2C_FIELD(this, s32 *, 0x1700) | temp_r6);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B8) = (s32) (M2C_FIELD(this, s32 *, 0x17B8) | temp_r6);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        return;
    case 1:
        temp_r5_2 = (unsigned char *)(this + ((p0 * 4) & 0x3FC));
        M2C_FIELD(temp_r5_2, s32 *, 0x1504) = 0xD;
        temp_r6_2 = 1 << p0;
        M2C_FIELD(this, s32 *, 0x16FC) = (s32) (M2C_FIELD(this, s32 *, 0x16FC) | temp_r6_2);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B4) = (s32) (M2C_FIELD(this, s32 *, 0x17B4) | temp_r6_2);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        M2C_FIELD(temp_r5_2, s32 *, 0x1544) = 0x1D;
        M2C_FIELD(this, s32 *, 0x1700) = (s32) (M2C_FIELD(this, s32 *, 0x1700) | temp_r6_2);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B8) = (s32) (M2C_FIELD(this, s32 *, 0x17B8) | temp_r6_2);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        return;
    case 2:
        temp_r5_3 = (unsigned char *)(this + ((p0 * 4) & 0x3FC));
        M2C_FIELD(temp_r5_3, s32 *, 0x1504) = 0xE;
        temp_r6_3 = 1 << p0;
        M2C_FIELD(this, s32 *, 0x16FC) = (s32) (M2C_FIELD(this, s32 *, 0x16FC) | temp_r6_3);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B4) = (s32) (M2C_FIELD(this, s32 *, 0x17B4) | temp_r6_3);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        M2C_FIELD(temp_r5_3, s32 *, 0x1544) = 0x1E;
        M2C_FIELD(this, s32 *, 0x1700) = (s32) (M2C_FIELD(this, s32 *, 0x1700) | temp_r6_3);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B8) = (s32) (M2C_FIELD(this, s32 *, 0x17B8) | temp_r6_3);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        return;
    case 3:
        temp_r5_4 = (unsigned char *)(this + ((p0 * 4) & 0x3FC));
        M2C_FIELD(temp_r5_4, s32 *, 0x1504) = 0xF;
        temp_r6_4 = 1 << p0;
        M2C_FIELD(this, s32 *, 0x16FC) = (s32) (M2C_FIELD(this, s32 *, 0x16FC) | temp_r6_4);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B4) = (s32) (M2C_FIELD(this, s32 *, 0x17B4) | temp_r6_4);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        M2C_FIELD(temp_r5_4, s32 *, 0x1544) = 0x1F;
        M2C_FIELD(this, s32 *, 0x1700) = (s32) (M2C_FIELD(this, s32 *, 0x1700) | temp_r6_4);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B8) = (s32) (M2C_FIELD(this, s32 *, 0x17B8) | temp_r6_4);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        return;
    }
}
extern "C++" {
#pragma push
#pragma dont_inline on
#define PE_NEXT(n) (*(peNode**)((u8*)(n) + 0x28))
#define PE_PREV(n) (*(peNode**)((u8*)(n) + 0x2C))
#define PE_DEPTH(n) (*(f32*)((u8*)(n) + 0x84))

void peShapeContainer::Update(float dt) {
    peNode* node;
    peNode* next;
    peNode* pos;
    peNode* prev;
    f32 depth;

    if (*((u8*)this + 0x19) == 0) {
        return;
    }
    for (node = *(peNode**)((u8*)this + 0x10); node != NULL; node = next) {
        next = PE_NEXT(node);
        if (!((peShapeNode*)node)->Update(*(peEmitterNode**)this, *(_peShape**)((u8*)this + 0x20), dt)) {
            ((peContainer*)this)->RemoveNode(node);
        }
    }
    if (g_currentBound != 0 && *(peNode**)((u8*)this + 0x10) != NULL) {
        GSboundAlwaysInView(g_currentBound, 1);
    }
    if (*((u8*)this + 0x19) != 0 && (**(u32**)((u8*)this + 0x20) & 0x80) && *(u16*)((u8*)this + 0x14) >= 2) {
        for (node = PE_NEXT(*(peNode**)((u8*)this + 0x10)); node != NULL; node = next) {
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

    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        return 0U;
    }
    var_r31 = ((peContainer*)this)->CreateNodes(count);
    var_r30 = g_emitParams;
    var_r3 = M2C_FIELD(this, peShapeNode **, 0x10);
    temp_r28 = var_r31;
    while (var_r31 != 0) {
        temp_r29 = M2C_FIELD(var_r3, peShapeNode **, 0x28);
        ((peShapeNode*)(var_r3))->Start((peEmitterNode*)(M2C_FIELD(this, peEmitterNode **, 0)), (_peShape*)(M2C_FIELD(this, _peShape **, 0x20)), (_EmitParams*)(var_r30));
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
    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        M2C_FIELD(this, u8 *, 0x19) = 1U;
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x800000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, true);
        }
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x01000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, true);
        }
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x02000000) {
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
peShapeContainer::peShapeContainer(peEmitterNode* p0, _peShape* p1, unsigned short p2) : peContainer(p0, 0x9C, p2) {
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
    *(peShapeColor*)((u8*)layer + 0x14F4) = c;
    M2C_FIELD(layer, u32 *, 0x16F8) |= 1;
    M2C_FIELD(layer, u32 *, 0x16A8) |= 0x10;
    M2C_FIELD(layer, u32 *, 0x17B0) |= 1;
    M2C_FIELD(layer, u32 *, 0x1760) |= 0x10;
}

static inline void peShapeSetChanColor(GSgfxLayer* layer, int ch, peShapeColor amb, peShapeColor mat) {
    ((peShapeColor*)((u8*)layer + 0xE9C))[ch] = amb;
    ((peShapeColor*)((u8*)layer + 0xEA4))[ch] = mat;
    M2C_FIELD(layer, u32 *, 0x16C4) |= 1 << ch;
    M2C_FIELD(layer, u32 *, 0x16C8) |= 1 << ch;
    M2C_FIELD(layer, u32 *, 0x16A8) |= 4;
    M2C_FIELD(layer, u32 *, 0x177C) |= 1 << ch;
    M2C_FIELD(layer, u32 *, 0x1780) |= 1 << ch;
    M2C_FIELD(layer, u32 *, 0x1760) |= 4;
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
    u32 flags;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    Vec spin;
    Vec base;
    Vec jitter;
    peShapeSpline* rotXSpline;
    peShapeSpline* rotYSpline;
    peShapeSpline* rotZSpline;
    peShapeSpline* sclXSpline;
    peShapeSpline* sclYSpline;
    peShapeSpline* sclZSpline;
    peColorSpline* color;
    peShapeSpline* alpha;
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
        return __float_nan[0];
    } else if (__fpclassifyf(x) == 1) {
        return __float_nan[0];
    }
    return x;
}

static inline f32 __OSu8tof32(register const u8* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 2 }
    return ret;
}

static inline f32 OSu8tof32(u8 in) {
    return __OSu8tof32(&in);
}

static inline u8 __OSf32tou8(register f32 inF) {
    u32 tmp;
    register u32* tmpPtr = &tmp;
    register u8 ret;
    asm {
        psq_st inF, 0(tmpPtr), 1, 2
        lbz ret, 0(tmpPtr)
    }
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
    PSVECScale(&s->jitter, &jitter, HSD_Randf());
    n->offset = peShapeVecC(jitter);
    PSVECAdd(&n->offset, &s->base, &n->offset);
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
    n->spinRate = s->spin;
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
    u32 flags = M2C_FIELD(shape, u32 *, 0);
    peShapeColor black = {0};
    f32 m[3][4];
    f32 rot[3][4];
    peShapeSetKColor(g_current_layer, M2C_FIELD(this, peShapeColor *, 0x98));
    if (flags & 0x200) {
        peShapeSetChanColor(g_current_layer, 0, M2C_FIELD(shape, peShapeColor *, 0x68), M2C_FIELD(this, peShapeColor *, 0x98));
        if (flags & 0x400) {
            peShapeSetChanColor(g_current_layer, 1, black, M2C_FIELD(this, peShapeColor *, 0x98));
        }
    }
    PSMTXQuat(rot, (const Quaternion*)((u8*)this + 0x3C));
    PSMTXScale(m, M2C_FIELD(this, f32 *, 0x4C), M2C_FIELD(this, f32 *, 0x50), M2C_FIELD(this, f32 *, 0x54));
    PSMTXConcat(rot, m, m);
    PSMTXTransApply(m, m, M2C_FIELD(this, f32 *, 0x30), M2C_FIELD(this, f32 *, 0x34), M2C_FIELD(this, f32 *, 0x38));
    M2C_FIELD(g_current_layer, GSgfxMatrixStack **, 0x19A0)->pushMult((GSmtx*)m);
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
        g_current_layer->drawTorus(M2C_FIELD(shape, f32 *, 0x54), M2C_FIELD(shape, u8 *, 0x58), M2C_FIELD(shape, u8 *, 0x59));
        break;
    case 6:
        g_current_layer->drawSphere(M2C_FIELD(shape, u8 *, 0x59));
        break;
    default:
        g_current_layer->drawSphere(M2C_FIELD(shape, u8 *, 0x58), M2C_FIELD(shape, u8 *, 0x59));
        break;
    }
    M2C_FIELD(g_current_layer, GSgfxMatrixStack **, 0x19A0)->pop();
}
}
#pragma pop
}

#pragma dont_inline off
