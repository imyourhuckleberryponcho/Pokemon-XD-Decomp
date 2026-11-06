
#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/gcptr.h>
#include <game/gcdata.h>
#include <game/gsmodelview.h>
#include <dolphin/mtx.h>
#include <dolphin/gx/GXVert.h>

#pragma pool_strings off

struct _GSmodel;
struct GSlight;
struct GSbound;
struct GSvec {
    f32 x, y, z;
};
struct GStexture {
    u8 pad0[7];
    u8 f7;
};
struct HSD_CObj;
struct HSD_Shadow {
    struct ShadowNode* objects;
    HSD_CObj* cobj;
    void* tex;
    u8 pad0c[0x20 - 0xc];
    u8 intensity;
};
struct ShadowNode {
    ShadowNode* next;
    void* jobj;
};
struct HSD_ViewingRect {
    u8 pad0[0x40];
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    s8 flags;
};
struct GSlightData {
    struct {
        void* classInfo;
        u16 refCount;
        u16 refCountIndividual;
    } parent;
    u16 flags;
};
struct GSlightHead {
    u8 used;
    u8 active;
    u8 canAnimate;
    u8 animating;
    s32 type;
    void* desc;
    GSlightData* lobj;
};

enum GSgfxLayerID { GS_GFX_LAYER_NONE = -1 };
enum GSgfxLayerOffset {};
enum GSgfxLayerType {};

class GSgfxLayerConfig {
public:
    static void Remove(GSgfxLayerID id);
    static GSgfxLayerID Add(char* name, u32 width, u32 height, u32 count, GSgfxLayerType type, bool clearColor,
                            bool clearAlpha, bool clearDepth, GSgfxLayerID relative, GSgfxLayerOffset offset);
};

struct ShadowTexInfo {
    u8 pad0[0x58];
    u32* image;
};

struct ShadowObj {
    u8 pad0[8];
    ShadowTexInfo* tex;
};

struct ShadowReceive {
    _GSmodel* model;
    GSlight* light;
    _GSmodel* receivers[16];
    u32 sizeMin;
    u32 sizeMax;
    u8 active;
    u8 pad51;
    u16 unk52;
    HSD_Shadow* shadow;
};

struct GScameraShadow {
    u8 pad0[0x6c];
    f32 x;
    f32 y;
    f32 z;
};

struct ShadowVolume {
#ifdef __MWERKS__
    u8 data[0x20];
#else
    union {
        u8 data[sizeof(GSmodelBoundView)];
        GSmodelBoundView view;
    };
#endif
};

struct _GSmodel {
    u32 flags;
    _GSmodel* next;
    void* set;
    void* jobj;
    void* blendJObj;
    void* blendDest;
    f32 unk18;
    f32 groundY;
    f32 unk20;
    f32 unk24;
    f32 rotY;
    f32 unk2C;
    GSvec scale;
#ifdef __MWERKS__
    u8 bound[0x20];
#else
    union {
        u8 bound[sizeof(GSmodelBoundView)];
        GSmodelBoundView boundView;
    };
#endif
    GScameraShadow* camera;
    u16 flags2;
    u16 token;
    u8 layers[8];
    u32 animCount;
    u32 texAnimCount;
    s32 animType;
    u32 animIndex;
    f32 animRate;
    f32 animFrame;
    f32 animReqFrame;
    f32 animEndFrame;
    void* animAObj;
    s32 blendAnimType;
    u32 blendAnimIndex;
    f32 blendAnimRate;
    f32 blendAnimFrame;
    f32 blendAnimReqFrame;
    f32 blendAnimEndFrame;
    void* blendAnimAObj;
    s32 texAnimType;
    u32 texAnimIndex;
    f32 texAnimRate;
    f32 texAnimFrame;
    f32 texAnimReqFrame;
    f32 texAnimEndFrame;
    void* texAnimAObj;
    GSmodelPartMixView partMix[12];
    f32 blendFactor;
    u8 animDirty;
    u8 texAnimDirty;
    u8 unk21E[2];
    void* animEndedCallback;
    void* animEndedCallbackArg;
    GSmodelPartAnimView partAnim[16];
    s32 attachMode;
    _GSmodel* attachModel;
    u32 attachIndex;
    f32 attachPosition[3];
    f32 attachRotation[3];
    f32 attachScale[3];
    void* particleBank;
    u32 particleAttachMode;
    void* materials;
    u32 materialCount;
    u32 shadowSurfaceCount;
    void* shadowSurfaces;
    GSlight* shadowLight;
    f32 groundPlane;
    GCuptr unk5F8;
    f32 unk5FC;
    u8 unk600[4];
    f32 unk604;
    u8 unk608[4];
    f32 unk60C;
    u16 unk610;
    u8 unk612;
    u8 unk613;
    GCuptr unk614;
    GCuptr unk618;
    GCuptr unk61C;
    s32 vertexCount;
    s32 polygonCount;
};

struct HSD_MObj {
    void* class_info;
    u32 flags;
};

struct HSD_DObj {
    void* class_info;
    HSD_DObj* next;
    HSD_MObj* mobj;
};

#ifdef __MWERKS__
struct _HSD_JObj {
    u8 pad0[0x14];
    u32 flags;
    HSD_DObj* dobj;
};
#else
struct _HSD_JObj {
    void* pcObject[2];
    _HSD_JObj* next;
    _HSD_JObj* parent;
    _HSD_JObj* child;
    u32 flags;
    HSD_DObj* dobj;
    Vec rotate;
    f32 rotateW;
    Vec scale;
    Vec translate;
    Mtx mtx;
    void* scl;
    void* envelopemtx;
    void* aobj;
    void* robj;
    u32 id;
};
#endif
typedef _HSD_JObj HSD_JObj;

extern "C" {
double ceil(double);
extern f32 __float_epsilon[];
void* memcpy(void*, const void*, u32);
void* GSmemAlloc(u32 size);
void GSmemFree(void*);
void GStextureSetFilter(GStexture*, s32, s32, u32);
void HSD_ShadowSetDebug(u8);
void HSD_ShadowSetActive(HSD_Shadow*, PCARG(u8, int));
void HSD_ShadowFreeTexture(HSD_Shadow*);
HSD_Shadow* HSD_ShadowAlloc(void);
}
void GSgfxRenderWaitForDrawComplete();
#ifdef __MWERKS__
HSD_JObj* modelGetRenderJObj(_GSmodel*);
#else
HSD_JObj* modelGetRenderJObj(_GSmodel* model);
#endif
extern "C" void HSD_JObjWalkTree(HSD_JObj*, void* func, void* data);

struct GSgfxVF;
struct BlendState {
    u8 pad[0xbc];
};

#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();
    void FlushState();
    void InvalidateState();
    u16 tokenMark();

};

extern "C" {
GSgfxLayer* GSgfxLayerFindByID(GCsptr id);
GSgfxVF* GSgfxVFGetPredef(s32 id);
bool GSlightGetPosition(GSlight*, Vec*);
void GSboundGetWorldPosition(void* bound, Vec* pos);
void GSboundGetSize(GSbound* bound, Vec* size, s32, s32);
}
void GSprimSetup3DRender(GSgfxLayer* layer);

static inline void _layerBlendNormal(GSgfxLayer* l)
{
    if ((*(s32*)&l->curPass) != 0) {
        (*(s32*)&l->curPass) = 0;
        l->curFifo = &l->passes[l->curPass];
    }
    (*(s32*)&l->hw.blend[0]) = 0;
    (*(s32*)&l->hw.blend[1]) = 1;
    (*(s32*)&l->hw.blend[2]) = 1;
    (*(s32*)&l->hw.blend[3]) = 5;
    (*(u32*)&l->dirty[0].pe) |= 1;
    (*(u32*)&l->dirty[0].groups) |= 0x40;
    (*(u32*)&l->dirty[1].pe) |= 1;
    (*(u32*)&l->dirty[1].groups) |= 0x40;
}

static inline void _layerSetZ(GSgfxLayer* l, u8 enable, s32 func)
{
    (*(u8*)&l->hw.zEnable) = enable;
    (*(s32*)&l->hw.zFunc) = func;
    (*(u32*)&l->dirty[0].pe) |= 8;
    (*(u32*)&l->dirty[0].groups) |= 0x40;
    (*(u32*)&l->dirty[1].pe) |= 8;
    (*(u32*)&l->dirty[1].groups) |= 0x40;
}

static inline void _layerSetAlphaCompare(GSgfxLayer* l, s32 a, u8 b, s32 c, s32 d, u8 e, u8 f)
{
    (*(s32*)&l->hw.alphaComp0) = a;
    (*(u8*)&l->hw.alphaRef0) = b;
    (*(s32*)&l->hw.alphaCmpOp) = c;
    (*(s32*)&l->hw.alphaComp1) = d;
    (*(u8*)&l->hw.alphaRef1) = e;
    (*(u8*)&l->hw.zCompLoc) = f;
    (*(u32*)&l->dirty[0].pe) |= 0x10;
    (*(u32*)&l->dirty[0].groups) |= 0x40;
    (*(u32*)&l->dirty[1].pe) |= 0x10;
    (*(u32*)&l->dirty[1].groups) |= 0x40;
}

static inline void _layerSetDepthTest(GSgfxLayer* l, u8 a, u8 b, u8 c)
{
    (*(u8*)&l->hw.colorUpdate) = a;
    (*(u8*)&l->hw.alphaUpdate) = b;
    (*(u8*)&l->hw.zUpdate) = c;
    (*(u32*)&l->dirty[0].pe) |= 4;
    (*(u32*)&l->dirty[0].groups) |= 0x40;
    (*(u32*)&l->dirty[1].pe) |= 4;
    (*(u32*)&l->dirty[1].groups) |= 0x40;
}

static inline void _layerSetLineWidth(GSgfxLayer* l, u8 w)
{
    (*(u8*)&l->hw.lineWidth) = w;
    (*(s32*)&l->hw.lineOffset) = 0;
    (*(u32*)&l->dirty[0].geom) |= 4;
    (*(u32*)&l->dirty[0].groups) |= 1;
    (*(u32*)&l->dirty[1].geom) |= 4;
    (*(u32*)&l->dirty[1].groups) |= 1;
}

static inline void _shadowDbgVertex(Vec* p, u8 r, u8 g, u8 b, u8 a)
{
    Vec v = *p;
    GXWGFifo.f32 = v.x;
    GXWGFifo.f32 = v.y;
    GXWGFifo.f32 = v.z;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;
}

struct ShadowColor {
    u8 r, g, b, a;
};

static inline void _layerBlendShadow(GSgfxLayer* l)
{
    if ((*(s32*)&l->curPass) != 1) {
        (*(s32*)&l->curPass) = 1;
        l->curFifo = &l->passes[l->curPass];
    }
    (*(s32*)&l->hw.blend[0]) = 3;
    (*(s32*)&l->hw.blend[1]) = 4;
    (*(s32*)&l->hw.blend[2]) = 5;
    (*(s32*)&l->hw.blend[3]) = 5;
    (*(u32*)&l->dirty[0].pe) |= 1;
    (*(u32*)&l->dirty[0].groups) |= 0x40;
    (*(u32*)&l->dirty[1].pe) |= 1;
    (*(u32*)&l->dirty[1].groups) |= 0x40;
}

static inline void _layerSetTexture(GSgfxLayer* l, GStexture* tex)
{
    if ((*(GStexture**)&l->dirty[0].tex[0]) != tex || (*(GStexture**)&l->dirty[1].tex[0]) != tex || tex->f7 != 0) {
        (*(GStexture**)&l->dirty[0].tex[0]) = tex;
        (*(u32*)&l->dirty[0].texMask) |= 1;
        (*(GStexture**)&l->dirty[1].tex[0]) = tex;
        (*(u32*)&l->dirty[1].texMask) |= 1;
    }
}

static inline void _shadowTexVertex(f32 x, f32 y, f32 z, ShadowColor c, f32 u, f32 v)
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
    GXWGFifo.u32 = GC_BYTES32(&c);
    GXWGFifo.f32 = u;
    GXWGFifo.f32 = v;
}

static inline void _shadowTexVertexV(Vec p, ShadowColor c, f32 u, f32 v)
{
    GXWGFifo.f32 = p.x;
    GXWGFifo.f32 = p.y;
    GXWGFifo.f32 = p.z;
    GXWGFifo.u32 = GC_BYTES32(&c);
    GXWGFifo.f32 = u;
    GXWGFifo.f32 = v;
}

static inline f32 _shadowFabs(f32 x)
{
    return (x > 0.0f) ? x : -x;
}

extern "C" {
void GSgfxProjectSetupParameters(void);
void GSmodelGetPosition(_GSmodel* model, GSvec* position);
f32 GSmodelGetDistanceFromCamera(_GSmodel* model);
void GSboundGetShadowVolume(ShadowVolume* volume, void* bound, Vec* lightPos, f32 groundY);
s32 GSboundIsInViewFast(ShadowVolume* volume);
GScameraShadow* GScameraGetActiveCamera(void);
u32 __cvt_fp2unsigned(f64);
extern _GSmodel* _modelTopPtr;
}
void modelApplyAnimation(_GSmodel*);
void modelUpdateAttachments(_GSmodel*);
void modelUpdateTransform(_GSmodel*);
void modelApplyPartAnimMixes(_GSmodel*);

extern "C" {
void GSgfxTokenWaitForClearAndReset(u16* token);
void HSD_StateInvalidate(s32 mask);
void GSlogWrite(const char* fmt, ...);
_GSmodel* GSmodelSearchModelList(void* jobj);
u8 GSboundHasAnimData(void* bound);
void GSboundGetShadowSize(Vec* out, ShadowVolume* volume, Vec* eye, Vec* interest, Vec* up);
void HSD_ShadowAddObject(HSD_Shadow* shadow, HSD_JObj* jobj);
void HSD_ShadowDeleteObject(HSD_Shadow* shadow, s32 flag);
void HSD_ShadowCopyLightPos(HSD_Shadow* shadow, void* light, f32 dist);
void HSD_ShadowCopyTex(HSD_Shadow* shadow);
void HSD_ShadowRender(HSD_Shadow* shadow);
void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 w, u16 h);
void HSD_ShadowSetViewingRect(HSD_Shadow* shadow, f32 a, f32 b, f32 c, f32 d);
void HSD_ViewingRectInit(HSD_ViewingRect* rect, Vec* eye, Vec* interest, Vec* up, PCARG(u8, int) persp);
void HSD_ViewingRectAddRect(HSD_ViewingRect* rect, Vec* pos, f32 a, f32 b, f32 c, f32 d);
s32 HSD_ViewingRectCheck(HSD_ViewingRect* rect);
void HSD_CObjSetProjectionType(HSD_CObj* cobj, s32 type);
void HSD_CObjSetInterest(HSD_CObj* cobj, Vec* interest);
void HSD_CObjSetNear(HSD_CObj* cobj, f32 value);
void HSD_CObjSetFar(HSD_CObj* cobj, f32 value);
f32 HSD_CObjGetEyeDistance(HSD_CObj* cobj);
void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec* out);
void HSD_CObjGetUpVector(HSD_CObj* cobj, Vec* out);
void __assert(const char* file, s32 line, const char* expr);
}

static ShadowReceive _modelShadowReceiveList[5];

static f32 _modelShadowMarukageDist = 350.0f;
static f32 _modelShadowOffDist = 400.0f;
extern "C" {
GSgfxLayerID modelShadowLayerID = GS_GFX_LAYER_NONE;
}

static u8 _modelShadowIntensity;
static s32 _modelShadowXsize;
static s32 _modelShadowYsize;
static f32 _modelShadowCutoffDist;
static f32 _modelShadowBoundExpansion;
static u32 _modelShadowLayerUseCount;
static u32 _modelShadowActiveCount;
static GStexture* _modelShadowMarukageTex;
static u8 _shadowCheckCameraHeight;

static void _modelShadowSetShadowFlag(HSD_JObj* jobj, void** data, int unused);

static inline void shVecSet(Vec* v, f32 x, f32 y, f32 z) { v->x = x; v->y = y; v->z = z; }

static u8 _modelShadowGetLightToGroundIntersect(_GSmodel* model, GSvec* out);
static bool _modelShadowAddAsNewReceiver(_GSmodel* model, _GSmodel* receiveModel, GSlight* light, GSbound* bound);
static ShadowReceive* _modelShadowFindValidReceiveModel(_GSmodel* model, _GSmodel* model2, GSlight* light, GSbound* bound);

void modelShadowRenderDebug(void)
{
    ShadowReceive* r;
    u32 i;
    u32 j;
    GSgfxLayer* layer = GSgfxLayerFindByID(2);

    GSprimSetup3DRender(layer);
    _layerBlendNormal(layer);
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
    _layerSetZ(layer, 1, 3);
    _layerSetAlphaCompare(layer, 7, 0, 0, 7, 0, 1);
    _layerSetDepthTest(layer, 1, 0, 0);
    (*(u32*)&layer->unk1998) = 0xA8;
    _layerSetLineWidth(layer, 9);
    for (i = 0; i < 5; i++) {
        r = &_modelShadowReceiveList[i];
        if (r->model != 0 && (r->model->flags & 1)) {
            for (j = 0; j < 16; j++) {
                _GSmodel* m = r->receivers[j];
                if (m != 0 && (m->flags & 1)) {
                    Vec lightPos;
                    Vec center;
                    Vec ground;
                    Vec size;
                    GSlightGetPosition(m->shadowLight, &lightPos);
                    GSboundGetWorldPosition(m->bound, &center);
                    GSboundGetSize((GSbound*)m->bound, &size, 1, 1);
                    center.y = 0.5f * size.y + center.y;
                    _modelShadowGetLightToGroundIntersect(m, (GSvec*)&ground);
                    layer->beginSurface(2);
                    _shadowDbgVertex(&lightPos, 255, 0, 0, 255);
                    _shadowDbgVertex(&center, 255, 0, 0, 255);
                    layer->endSurface();
                    layer->beginSurface(2);
                    _shadowDbgVertex(&center, 0, 0, 255, 255);
                    _shadowDbgVertex(&ground, 0, 0, 255, 255);
                    layer->endSurface();
                }
            }
        }
    }
}

void modelShadowRenderMarukage(_GSmodel* model, GSgfxLayer* layer)
{
    Vec size;
    Vec pos;
    Vec corner;
    ShadowColor color;
    Mtx rot;
    f32 minSize;
    s32 intensity;
    f32 y;
    f32 zero = 0.0f;
    f32 one = 1.0f;

    GSboundGetSize((GSbound*)model->bound, &size, 0, 0);
    size.x *= 0.5f;
    size.z *= 0.5f;
    minSize = size.x;
    if (size.z < minSize) {
        minSize = size.z;
    }
    PSMTXRotRad(rot, 'Y', model->rotY);
    PSMTXMultVec(rot, &size, &size);
    size.x = (size.x > 0.0f) ? size.x : -size.x;
    size.z = (size.z > 0.0f) ? size.z : -size.z;
    if (size.x < minSize) {
        size.x = minSize;
    }
    if (size.z < minSize) {
        size.z = minSize;
    }
    GSboundGetWorldPosition(model->bound, &pos);
    corner.x = pos.x;
    corner.y = pos.y;
    corner.z = pos.z;
    pos.x = pos.x - size.x;
    pos.z = pos.z - size.z;
    corner.x = corner.x + size.x;
    corner.z = corner.z + size.z;
    y = 0.2f + model->groundY;
    pos.y = y;
    corner.y = y;
    intensity = _modelShadowIntensity;
    color.r = color.g = color.b = color.a = intensity - (intensity >> 2);
    GSprimSetup3DRender(layer);
    _layerBlendShadow(layer);
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(5));
    _layerSetTexture(layer, _modelShadowMarukageTex);
    _layerSetZ(layer, 1, 3);
    _layerSetAlphaCompare(layer, 7, 0, 0, 7, 0, 1);
    _layerSetDepthTest(layer, 1, 0, 0);
    (*(u32*)&layer->unk1998) = 0x98;
    layer->beginSurface(4);
    _shadowTexVertexV(pos, color, zero, zero);
    _shadowTexVertex(pos.x, pos.y, corner.z, color, zero, one);
    _shadowTexVertex(corner.x, pos.y, pos.z, color, one, zero);
    _shadowTexVertexV(corner, color, one, one);
    layer->endSurface();
}

#ifndef __MWERKS__
extern "C" int HSD_ShadowPCHasTexture(HSD_Shadow* shadow);
extern "C" void HSD_ShadowPCSetIntensity(HSD_Shadow* shadow, u8 intensity);
#endif

static inline bool _shadowHasTexture(HSD_Shadow* shadow)
{
#ifndef __MWERKS__
    return HSD_ShadowPCHasTexture(shadow) != 0;
#endif
    ShadowObj* obj = (ShadowObj*)shadow;

    if (obj == 0) {
        return false;
    }
    if (obj->tex == 0) {
        return false;
    }
    if (obj->tex->image == 0) {
        return false;
    }
    if (*obj->tex->image == 0) {
        return false;
    }
    return true;
}

static inline int _shadowClassify(f32 x)
{
    switch ((*(s32*)&x) & 0x7f800000) {
    case 0x7f800000:
        if ((*(s32*)&x) & 0x007fffff) {
            return 1;
        }
        return 2;
    case 0:
        if ((*(s32*)&x) & 0x007fffff) {
            return 5;
        }
        return 3;
    }
    return 4;
}

static inline void _layerResetD90(GSgfxLayer* l)
{
    (*(s32*)&l->hw.clipMode) = 0;
    (*(u32*)&l->dirty[0].raster) |= 4;
    (*(u32*)&l->dirty[0].groups) |= 2;
    (*(u32*)&l->dirty[1].raster) |= 4;
    (*(u32*)&l->dirty[1].groups) |= 2;
}

static inline u32 _shadowLightType(GSlight* light)
{
    return ((GSlightHead*)light)->lobj->flags & 3;
}

void modelShadowRender(GSgfxLayer* layer)
{
    u8 shade;
    _GSmodel* m;
    ShadowReceive* r = _modelShadowReceiveList;
    ShadowReceive* slot;
    u32 j;
    u32 i;
    u32 k;

    for (j = 0; j < 5; j++) {
    slot = &r[j];
        if (slot->model != 0) {
            GSgfxTokenWaitForClearAndReset(&slot->unk52);
            if (slot->model != 0) {
                GSgfxTokenWaitForClearAndReset(&slot->model->token);
            }
        }
    }
    if (_modelShadowActiveCount != 0) {
        _layerResetD90(layer);
        layer->FlushState();
        HSD_StateInvalidate(-1);
        for (i = 0; i < 5; i++, r++) {
            if (r->model == 0) {
                if (_shadowHasTexture(r->shadow)) {
                    GSgfxRenderWaitForDrawComplete();
                    HSD_ShadowFreeTexture(r->shadow);
                }
                r->active = 0;
            } else if (r->model->flags & 1) {
                Vec avg;
                Vec eye;
                Vec tmp;
                Vec up;
                HSD_ViewingRect rect;
                ShadowNode* node;
                u32 type;
                f32 dist;

                avg.x = 0.0f;
                avg.y = 0.0f;
                avg.z = 0.0f;
                j = 0;
                for (k = 0; k < 16; k++) {
                    _GSmodel* m = r->receivers[k];
                    if (m != 0 && (m->flags & 1)) {
                        HSD_ShadowAddObject(r->shadow, modelGetRenderJObj(m));
                        GSboundGetWorldPosition(m->bound, &tmp);
                        PSVECAdd(&avg, &tmp, &avg);
                        j++;
                    }
                }
                if (j == 0) {
                    r->active = 0;
                    continue;
                }
                switch (_shadowLightType(r->light)) {
                case 1:
                    HSD_CObjSetProjectionType(r->shadow->cobj, 3);
                    break;
                case 2:
                case 3:
                    HSD_CObjSetProjectionType(r->shadow->cobj, 2);
                    break;
                }
                if ((f32)j != 0.0f) {
                    PSVECScale(&avg, &avg, 1.0f / (f32)j);
                }
                HSD_CObjSetInterest(r->shadow->cobj, &avg);
                HSD_ShadowCopyLightPos(r->shadow, ((GSlightHead*)r->light)->lobj, 30.0f);
                HSD_CObjSetNear(r->shadow->cobj, 0.1f);
                HSD_CObjSetFar(r->shadow->cobj, 3000.0f);
                dist = HSD_CObjGetEyeDistance(r->shadow->cobj);
                if (_shadowClassify(dist) == 1 || dist < 0.1f) {
                    HSD_ShadowDeleteObject(r->shadow, 0);
                    continue;
                }
                HSD_CObjGetEyePosition(r->shadow->cobj, &eye);
                HSD_CObjGetUpVector(r->shadow->cobj, &up);
                type = _shadowLightType(r->light);
                HSD_ViewingRectInit(&rect, &eye, &avg, &up, type != 1);
                for (node = r->shadow->objects; node != 0; node = node->next) {
                    m = GSmodelSearchModelList(node->jobj);
                    if (m != 0) {
                        GSboundGetWorldPosition(m->bound, &tmp);
                        if (!GSboundHasAnimData(m->bound)) {
                            Vec size;
                            f32 largest;
                            u32 n;
                            f32 e;

                            GSboundGetSize((GSbound*)m->bound, &size, 1, 1);
                            if (size.y > (largest = size.x)) {
                                largest = size.y;
                            }
                            if (size.z > largest) {
                                largest = size.z;
                            }
                            n = (u32)(f32)ceil(largest);
                            e = _modelShadowBoundExpansion;
                            e += (f32)n;
                            if (e > 0.1f) {
                                HSD_ViewingRectAddRect(&rect, &tmp, e, -e, -e, e);
                            }
                        } else {
                            ShadowVolume volume;
                            Vec size;
                            f32 y;

                            if (m->flags2 & 4) {
                                GSvec pos;
                                GSmodelGetPosition(m, &pos);
                                y = pos.y;
                            } else {
                                y = m->groundPlane;
                            }
                            GSboundGetShadowVolume(&volume, m->bound, &eye, y);
                            GSboundGetShadowSize(&size, &volume, &eye, &avg, &up);
                            PSVECScale(&size, &size, 0.5f);
                            HSD_ViewingRectAddRect(&rect, &tmp, size.z, -size.z, -size.x, size.x);
                        }
                    }
                }
                if (HSD_ViewingRectCheck(&rect) != 0) {
                    HSD_ShadowSetViewingRect(r->shadow, rect.a, rect.b, rect.c, rect.d);
                } else {
                    f32 e = (f32)r->sizeMax + _modelShadowBoundExpansion;
                    if (e > 0.1f) {
                        HSD_ShadowSetViewingRect(r->shadow, e, -e, -e, e);
                    }
                }
                {
                    HSD_Shadow* shadow = r->shadow;
                    shade = 255 - _modelShadowIntensity;
                    if (shadow == 0) {
                        __assert("shadow.h", 0x6c, "shadow");
                    }
#ifdef __MWERKS__
                    shadow->intensity = shade;
#else
                    HSD_ShadowPCSetIntensity(shadow, shade);
#endif
                }
                HSD_ShadowSetSize(r->shadow, _modelShadowXsize, _modelShadowYsize);
                r->active = 1;
                if (!_shadowHasTexture(r->shadow)) {
                    GSlogWrite("*** GSmodel shadow texture memory unavailable, skipping rendering\n");
                } else {
                    _layerResetD90(layer);
                    layer->FlushState();
                    HSD_ShadowRender(r->shadow);
                    HSD_ShadowCopyTex(r->shadow);
                    layer->InvalidateState();
                    r->unk52 = layer->tokenMark();
                }
                HSD_ShadowDeleteObject(r->shadow, 0);
            }
        }
        (*(u32*)&layer->flags) |= 0x10000000;
        (*(u32*)&layer->flags) |= 0x20000000;
    }
}

static inline s32 _shadowFindReceiver(ShadowReceive* slot, _GSmodel* what)
{
    u32 k;

    for (k = 0; k < 16; k++) {
        if (slot->receivers[k] == what) {
            return k;
        }
    }
    return -1;
}

static inline bool _shadowTryReceiver(_GSmodel* model, u32 index)
{
    GSlight* light = model->shadowLight;
    _GSmodel* caster = ((_GSmodel**)model->shadowSurfaces)[index];
    ShadowReceive* slot;
    s32 idx;

    if (light == 0) {
        return true;
    }
    if ((model->scale.x + model->scale.y + model->scale.z) / 3.0f < 0.01f) {
        return true;
    }
    _modelShadowActiveCount++;
    slot = _modelShadowFindValidReceiveModel(caster, model, light, (GSbound*)model->bound);
    if (slot != 0) {
        idx = _shadowFindReceiver(slot, model);
        if (idx != -1) {
            return true;
        }
        idx = _shadowFindReceiver(slot, 0);
        if (idx == -1) {
            return _modelShadowAddAsNewReceiver(caster, model, light, (GSbound*)model->bound);
        }
        if (idx < 0) {
            return false;
        }
        slot->receivers[idx] = model;
        {
            Vec size;
            f32 m;
            u32 n;
            GSboundGetSize((GSbound*)model->bound, &size, 1, 1);
            m = size.x;
            if (size.y > m) {
                m = size.y;
            }
            if (size.z > m) {
                m = size.z;
            }
            n = (u32)(f32)ceil(m);
            if (n < slot->sizeMin) {
                slot->sizeMin = n;
            }
            if (n > slot->sizeMax) {
                slot->sizeMax = n;
            }
        }
        return true;
    }
    return _modelShadowAddAsNewReceiver(caster, model, light, (GSbound*)model->bound);
}

void modelShadowUpdate(void)
{
    u32 k;
    _GSmodel* model;
    u32 j;
    ShadowReceive* slot;
    u32 i;

    GSgfxProjectSetupParameters();
    slot = _modelShadowReceiveList;
    for (i = 0; i < 5; i++, slot++) {
        slot->active = 0;
        slot->model = 0;
        slot->unk52 = 0;
        for (j = 0; j < 16; j++) {
            slot->receivers[j] = 0;
        }
    }
    _modelShadowActiveCount = 0;
    for (model = _modelTopPtr; model != 0; model = model->next) {
        bool visible;

        if (model->shadowSurfaceCount == 0) {
            continue;
        }
        model->flags &= ~0x08000000;
        if (!(model->flags & 2)) {
            continue;
        }
        visible = false;
        if (model->flags & 0x10000000) {
            if (model->flags & 0x04000000) {
                visible = true;
            } else {
                Vec lightPos;
                GSvec pos;
                ShadowVolume volume;
                f32 y;

                GSlightGetPosition(model->shadowLight, &lightPos);
                if (model->flags2 & 4) {
                    GSmodelGetPosition(model, &pos);
                    y = pos.y;
                } else {
                    y = model->groundPlane;
                }
                GSboundGetShadowVolume(&volume, model->bound, &lightPos, y);
                if (GSboundIsInViewFast(&volume)) {
                    visible = true;
                    modelApplyAnimation(model);
                    modelUpdateAttachments(model);
                    modelUpdateTransform(model);
                    modelApplyPartAnimMixes(model);
                }
            }
        }
        if (!visible) {
            continue;
        }
        if (_shadowCheckCameraHeight == 1) {
            GScameraShadow* camera = model->camera;
            f32 camY;

            if (camera == 0) {
                camera = GScameraGetActiveCamera();
            }
            if (camera == 0) {
                camY = 0.0f;
            } else {
                camY = camera->y;
            }
            if (camY < 20.0f + model->groundY) {
                model->flags |= 0x08000000;
                continue;
            }
        }
        {
            f32 dist = GSmodelGetDistanceFromCamera(model);

            if (dist < _modelShadowOffDist) {
                if (_modelShadowMarukageTex != 0 && dist >= _modelShadowMarukageDist) {
                    model->flags |= 0x08000000;
                } else {
                    for (k = 0; k < model->shadowSurfaceCount; k++) {
                        if (!_shadowTryReceiver(model, k)) {
                            model->flags |= 0x08000000;
                        }
                    }
                }
            }
        }
    }
}

static inline void _shadowFreeSurfaces(_GSmodel* model)
{
    if (model->shadowSurfaces != 0) {
        GSmemFree(model->shadowSurfaces);
        model->shadowSurfaceCount = 0;
        model->shadowSurfaces = 0;
        if (--_modelShadowLayerUseCount == 0) {
            GSgfxLayerConfig::Remove((GSgfxLayerID)modelShadowLayerID);
            modelShadowLayerID = GS_GFX_LAYER_NONE;
        }
    }
}

extern "C" {

void GSmodelSetShadowToCameraHeightCheck(bool check)
{
    _shadowCheckCameraHeight = check;
}

void GSmodelSetGroundPlane(_GSmodel* model, f32 plane, bool enable)
{
    model->groundPlane = plane;
    if (enable) {
        model->flags2 |= 4;
    } else {
        model->flags2 &= ~4;
    }
}

void GSmodelSetMarukageTexture(GStexture* tex)
{
    _modelShadowMarukageTex = tex;
    GStextureSetFilter(tex, 2, 2, 0);
}

void GSmodelSetShadowDistLimits(f32 marukage, f32 off)
{
    _modelShadowMarukageDist = marukage;
    _modelShadowOffDist = off;
}

void GSmodelFreeAllShadowTextures(void)
{
    u32 i;

    for (i = 0; i < 5; i++) {
        ShadowReceive* r = &_modelShadowReceiveList[i];
        if (_shadowHasTexture(r->shadow)) {
            GSgfxRenderWaitForDrawComplete();
            HSD_ShadowFreeTexture(r->shadow);
        }
        HSD_ShadowSetActive(r->shadow, 0);
        r->active = 0;
    }
}

void GSmodelSetShadowBoundExpansion(f32 expansion)
{
    _modelShadowBoundExpansion = expansion;
}

void GSmodelSetShadowCutoffDist(f32 dist)
{
    _modelShadowCutoffDist = dist * dist;
}

void GSmodelSetShadowDebug(bool debug)
{
    HSD_ShadowSetDebug(debug);
}

void GSmodelSetShadowTextureSize(s32 width, s32 height)
{
    if (width & 1) {
        width++;
    }
    if (height & 1) {
        height++;
    }
    if (width < 2 || height < 2) {
        return;
    }
    if (width > 640) {
        width = 640;
    }
    if (height > 528) {
        height = 528;
    }
    _modelShadowXsize = width;
    _modelShadowYsize = height;
}

void GSmodelSetShadowLight(_GSmodel* model, GSlight* light)
{
    if (light != 0) {
        if ((((GSlightHead*)light)->lobj->flags & 3) == 0) {
            light = 0;
        }
    }
    model->shadowLight = light;
}

void GSmodelSetShadowSurface(_GSmodel* model, s32 count, void* surfaces)
{
    if (count < 0 || count > 8) {
        return;
    }
    if (count == 0 || surfaces == 0) {
        _shadowFreeSurfaces(model);
        return;
    }
    if (model->shadowSurfaces == 0) {
        model->shadowSurfaces = GSmemAlloc(8 * sizeof(_GSmodel*));
        model->shadowSurfaceCount = 0;
        if (_modelShadowLayerUseCount == 0) {
            modelShadowLayerID = GSgfxLayerConfig::Add("model shadow", 0, 0x40000, 4, (GSgfxLayerType)0, false, false,
                                                       false, GS_GFX_LAYER_NONE, (GSgfxLayerOffset)3);
        }
        _modelShadowLayerUseCount++;
    }
    model->shadowSurfaceCount = count;
    memcpy(model->shadowSurfaces, surfaces, model->shadowSurfaceCount * sizeof(_GSmodel*));
}

void GSmodelClearShadowFlags(_GSmodel* model, u32 flags)
{
    if (flags & 1) {
        model->flags &= ~0x10000000;
    }
    if (flags & 4) {
        model->flags &= ~0x40000000;
    }
}

void GSmodelSetShadowFlags(_GSmodel* model, u32 flags)
{
    if (flags & 1) {
        model->flags |= 0x10000000;
    }
    if (flags & 4) {
        model->flags |= 0x40000000;
    }
}

}

static inline bool _shadowIsReceiveModel(_GSmodel* model)
{
    u32 i;

    for (i = 0; i < 5; i++) {
        if (_modelShadowReceiveList[i].model == model) {
            return true;
        }
    }
    return false;
}

void modelShadowPrepare(_GSmodel* model, bool enable)
{
    HSD_JObj* jobj;
    u32 i;

    if (!_shadowIsReceiveModel(model)) {
        return;
    }
    jobj = modelGetRenderJObj(model);
    if (!enable) {
        HSD_JObjWalkTree(jobj, (void*)_modelShadowSetShadowFlag, (void*)0);
    } else {
        HSD_JObjWalkTree(jobj, (void*)_modelShadowSetShadowFlag, (void*)1);
    }
    for (i = 0; i < 5; i++) {
        if (_modelShadowReceiveList[i].active && _modelShadowReceiveList[i].model == model) {
            HSD_ShadowSetActive(_modelShadowReceiveList[i].shadow, enable);
        }
    }
}

void modelShadowFreeModelList(_GSmodel* model)
{
    _shadowFreeSurfaces(model);
}

void modelShadowInit(void)
{
    ShadowReceive* r;
    u32 i;

    _modelShadowIntensity = 0x80;
    _modelShadowXsize = 0x180;
    _modelShadowYsize = 0x180;
    _modelShadowCutoffDist = 0.0f;
    _modelShadowBoundExpansion = 0.0f;
    for (i = 0; i < 5; i++) {
        r = &_modelShadowReceiveList[i];
        r->active = 0;
        r->shadow = HSD_ShadowAlloc();
        HSD_ShadowSetActive(r->shadow, 0);
        r->model = 0;
        r->unk52 = 0;
    }
}

static inline bool _shadowCanMark(HSD_JObj* jobj)
{
    return (jobj->flags & 0x4020) == 0;
}

static void _modelShadowSetShadowFlag(HSD_JObj* jobj, void** data, int unused)
{
    s32 valid;
    bool enable = data != 0;
    HSD_DObj* dobj;

    valid = (jobj->flags & 0x4020) ? 0 : 1;
    if (valid == 0) {
        return;
    }
    for (dobj = jobj->dobj; dobj != 0; dobj = dobj->next) {
        if (dobj->mobj != 0) {
            if (enable) {
                dobj->mobj->flags |= 0x4000000;
            } else {
                dobj->mobj->flags &= ~0x4000000;
            }
        }
    }
}

static inline u32 _shadowBoundSize(GSbound* bound)
{
    Vec size;
    f32 m;

    GSboundGetSize(bound, &size, 1, 1);
    m = size.x;
    if (size.y > m) {
        m = size.y;
    }
    if (size.z > m) {
        m = size.z;
    }
    return (u32)(f32)ceil(m);
}

static inline ShadowReceive* _shadowFindReceiveModel(_GSmodel* model)
{
    ShadowReceive* slot;
    u32 i;

    for (i = 0; i < 5; i++) {
        slot = &_modelShadowReceiveList[i];
        if (slot->model == model) {
            return slot;
        }
    }
    return 0;
}

static inline bool _shadowAddReceiver(ShadowReceive* slot, _GSmodel* receiveModel, GSbound* bound)
{
    s32 idx;
    u32 n;

    idx = _shadowFindReceiver(slot, receiveModel);
    if (idx != -1) {
        return true;
    }
    idx = _shadowFindReceiver(slot, 0);
    if (idx < 0) {
        return false;
    }
    slot->receivers[idx] = receiveModel;
    n = _shadowBoundSize(bound);
    if (n < slot->sizeMin) {
        slot->sizeMin = n;
    }
    if (n > slot->sizeMax) {
        slot->sizeMax = n;
    }
    return true;
}

static bool _modelShadowAddAsNewReceiver(_GSmodel* model, _GSmodel* receiveModel, GSlight* light, GSbound* bound)
{
    ShadowReceive* slot;
    u32 i;
    bool valid;
    u32 j;
    _GSmodel* receiver;
    u32 n;

    slot = _shadowFindReceiveModel(0);
    if (slot == 0) {
        slot = _modelShadowFindValidReceiveModel(model, receiveModel, light, 0);
        if (slot != 0) {
            for (i = 0; i < 16; i++) {
                receiver = slot->receivers[i];
                if (receiver != 0 && (receiver->flags & 0x40000000)) {
                    slot = 0;
                    break;
                }
            }
        }
        if (slot == 0) {
            valid = false;
            for (i = 0; i < 5; i++) {
                slot = &_modelShadowReceiveList[i];
                if (slot->model != model) {
                    continue;
                }
                valid = true;
                for (j = 0; j < 16; j++) {
                    receiver = slot->receivers[i];
                    if (receiver != 0 && (receiver->flags & 0x40000000)) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    break;
                }
            }
            if (!valid) {
                return false;
            }
        }
        return _shadowAddReceiver(slot, receiveModel, bound);
    }
    slot->model = model;
    slot->light = light;
    n = _shadowBoundSize(bound);
    slot->sizeMax = n;
    slot->sizeMin = n;
    slot->receivers[0] = receiveModel;
    return true;
}

static ShadowReceive* _modelShadowFindValidReceiveModel(_GSmodel* model, _GSmodel* model2, GSlight* light, GSbound* bound)
{    u32 i;
    Vec p0;
    Vec p1;
    Vec size;

    for (i = 0; i < 5; i++) {
        ShadowReceive* r = &_modelShadowReceiveList[i];
        if (r->model == model && r->light == light) {
            if (bound != 0) {
                f32 m;
                u32 n;
                GSboundGetSize(bound, &size, 1, 1);
                {
                    Vec* dims = &size;
                    m = dims->x;
                    if (dims->y > m) {
                        m = dims->y;
                    }
                    if (dims->z > m) {
                        m = dims->z;
                    }
                }
                n = (u32)(f32)ceil(m);
                if (n < r->sizeMin) {
                    if (n < r->sizeMax / 3) {
                        continue;
                    }
                }
                if (n > r->sizeMax) {
                    if (n > r->sizeMin * 3) {
                        continue;
                    }
                }
            }
            if (_modelShadowCutoffDist > 0.0f) {
                u32 j;
                bool ok = true;
                GSboundGetWorldPosition(model2->bound, &p0);
                for (j = 0; j < 16; j++) {
                    if (r->receivers[j] != 0) {
                        GSboundGetWorldPosition((u8*)r->receivers[j] + 0x3c, &p1);
                        if (PSVECSquareDistance(&p0, &p1) > _modelShadowCutoffDist) {
                            ok = false;
                            j = 16;
                        }
                    }
                }
                if (!ok) {
                    continue;
                }
            }
            return r;
        }
    }
    return 0;
}

static u8 _modelShadowGetLightToGroundIntersect(_GSmodel* model, GSvec* out)
{
    Vec lightPos;
    Vec center;
    Vec size;
    Vec scaled2;
    Vec rayPt;
    Vec rayDir;
    Vec planeN;
    Vec planePt;
    Vec tmp1;
    Vec tmp2;
    Vec result;
    Vec scaled;
    f32 denom;
    f32 numer;
    int status;

    GSlightGetPosition(model->shadowLight, &lightPos);
    GSboundGetWorldPosition(model->bound, &center);
    GSboundGetSize((GSbound*)model->bound, &size, 1, 1);
    center.y = 0.5f * size.y + center.y;
    shVecSet(&planePt, 0.0f, model->groundY, 0.0f);
    shVecSet(&planeN, 0.0f, -1.0f, 0.0f);
    PSVECSubtract(&lightPos, &center, &tmp1);
    rayDir = tmp1;
    PSVECSubtract(&center, &planePt, &tmp2);
    rayPt = tmp2;
    denom = PSVECDotProduct(&planeN, &rayDir);
    numer = PSVECDotProduct(&planeN, &rayPt);
    if ((denom > 0.0f ? denom : -denom) < __float_epsilon[0]) {
        if (numer == 0.0f) {
            status = 2;
        } else {
            status = 1;
        }
    } else {
        PSVECScale(&rayDir, &scaled, numer / denom);
        scaled2 = scaled;
        PSVECSubtract(&center, &scaled2, &result);
        f32 x = result.x;
        f32 y = result.y;
        f32 z = result.z;
        shVecSet((Vec*)out, x, y, z);
        status = 0;
    }
    return status == 0;
}
