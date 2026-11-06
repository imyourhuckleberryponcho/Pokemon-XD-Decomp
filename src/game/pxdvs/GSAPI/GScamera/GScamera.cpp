

#ifndef __MWERKS__
#include <game/psq.h>
#endif
#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gcdata.h>
#include <dolphin/mtx.h>

#pragma pool_strings off

struct _GScamera;
typedef _GScamera GScamera;
struct GSgfxLayer;
enum GSgfxLayerID { GS_GFX_LAYER_NONE = -1 };

typedef struct _HSD_AObj {
    u32 flags;
    f32 curr_frame;
    f32 rewind_frame;
    f32 end_frame;
} HSD_AObj;

struct HSD_ObjHeader {
    void** class_info;
    u16 ref_count;
};

struct HSD_CObj {
    void** class_info;
    u16 ref_count;
    u16 pad6;
#ifndef __MWERKS__
    u32 pcPad;
#endif
    u32 flags;
    f32 viewport_left;
    f32 viewport_right;
    f32 viewport_top;
    f32 viewport_bottom;
    u16 scissor_left;
    u16 scissor_right;
    u16 scissor_top;
    u16 scissor_bottom;
#ifdef __MWERKS__
    u8 pad24[0x50 - 0x24];
#else

    void* eyepos;
    void* interest;
    f32 up[3];
    f32 nearZ;
    f32 farZ;
    f32 projection_param[4];
#endif
    u8 projection_type;
#ifndef __MWERKS__
    Mtx view_mtx;
#endif
};
#ifdef __MWERKS__
#define GSCAMERA_COBJ_VIEWMTX(cobj) ((MtxPtr)((u8*)(cobj) + 0x54))
#else
#define GSCAMERA_COBJ_VIEWMTX(cobj) ((cobj)->view_mtx)
#endif

struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(GSgfxLayer* layer, s32 pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 id;
};
void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);

struct GScameraWObjDesc {
    gc_ptr32(char) class_name;
    gc_bef32 x, y, z;
    gc_ptr32(void) robjdesc;
};

struct GScameraCObjDesc {
    gc_ptr32(char) class_name;
    gc_be16 flags;
    gc_be16 projection_type;
    gc_bes16 viewport_left;
    gc_bes16 viewport_right;
    gc_bes16 viewport_top;
    gc_bes16 viewport_bottom;
    gc_be16 scissor_left;
    gc_be16 scissor_right;
    gc_be16 scissor_top;
    gc_be16 scissor_bottom;
    gc_ptr32(GScameraWObjDesc) position;
    gc_ptr32(GScameraWObjDesc) interest;
    gc_bef32 roll;
    gc_ptr32(void) targetDesc;
    gc_bef32 near;
    gc_bef32 far;
    gc_bef32 fov;
    gc_bef32 aspect;
};

struct GScameraDesc {
    gc_ptr32(GScameraCObjDesc) cobjDesc;
    gc_ptr32(gc_ptr32(void)) anims;
};

struct _GScamera {
    u8 used;
    u8 lookAt;
    u8 dirty;
    u8 canAnimate;
    GScameraDesc* desc;
    HSD_CObj* cobj;
    GScameraWObjDesc positionDesc;
    GScameraWObjDesc interestDesc;
    GScameraCObjDesc cobjDesc;
    Vec eye;
    Vec prevEye;
    Vec rot;
    Mtx viewMtx;
    Mtx invMtx;
    Vec up;
    Vec interest;
    s32 animType;
    u32 animCount;
    u32 animIndex;
    f32 rate;
    f32 frame;
    f32 frameCount;
    u8 ended;
    s8 direction;
    u8 animating;
    u8 flags;
};

struct GScameraState {
    u8 animating;
    u8 ended;
    u8 pad2[2];
    Vec eye;
    Vec prevEye;
    Vec rot;
    Mtx viewMtx;
    Mtx invMtx;
    Vec up;
    Vec interest;
    s32 animType;
    u32 animIndex;
    f32 rate;
    f32 frame;
};

struct GSlayerMtx {
    u32 flags;
    Mtx mtx;
};

struct GSlayerCam {
    u32 pad;
    GSlayerMtx* data;
};

enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
};

extern "C" {
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
void __assert(const char*, int, const char*);
void* GSmemAlloc(u32 size);
u8 GSgfxVideoGetVsyncRate(void);
void GSgfxVideoGetEFBSize(u16* w, u16* h);
GSgfxLayer* GSgfxLayerFindByID(GCsptr id);
void GSmtx44Perspective(f32* mtx, f32 fov, f32 aspect, f32 near, f32 far);
void GSmtx44Ortho(f32* mtx, f32 l, f32 r, f32 t, f32 b, f32 near, f32 far);
void HSD_ForeachAnim(void* object, u32 type, u32 mask, void* func, u32 callback_type, ...);
void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate);
HSD_CObj* HSD_CObjLoadDesc(void* desc);
void HSD_CObjRemoveAnim(HSD_CObj*);
void HSD_CObjAddAnim(HSD_CObj*, void*);
void HSD_CObjReqAnim(HSD_CObj*, f32);
void HSD_CObjAnim(HSD_CObj*);
void HSD_CObjGetEyePosition(HSD_CObj*, Vec*);
void HSD_CObjSetEyePosition(HSD_CObj*, Vec*);
void HSD_CObjGetUpVector(HSD_CObj*, Vec*);
void HSD_CObjGetInterest(HSD_CObj*, Vec*);
void HSD_CObjSetProjectionType(HSD_CObj*, u32);
void HSD_CObjSetPerspective(HSD_CObj*, f32, f32);
void HSD_CObjSetNear(HSD_CObj*, f32);
void HSD_CObjSetFar(HSD_CObj*, f32);
void HSD_CObjGetPerspective(HSD_CObj*, f32*, f32*);
f32 HSD_CObjGetNear(HSD_CObj*);
f32 HSD_CObjGetFar(HSD_CObj*);
void HSD_CObjGetOrtho(HSD_CObj*, f32*, f32*, f32*, f32*);
MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj*);
void HSD_CObjMakeProjectionMtx(HSD_CObj*, void*);
void HSD_CObjSetupViewingMtx(HSD_CObj*);
extern f32 __float_epsilon[];
extern Mtx mtxIdent;
}

static GScamera* _cameraStructList;
static u32 _cameraStructCount;
static GScamera* _activeCamera;
static GScamera* _newActiveCamera;
static f32 _frameCount;

static void _cameraPreUpdate(f32 dt);
static void _cameraPostUpdate(f32 dt);

static inline f32 HSD_AObjGetEndFrame(HSD_AObj* aobj)
{
    if (aobj == 0) {
        __assert("aobj.h", 0xAC, "aobj");
    }
    return aobj->end_frame;
}

static inline GScamera* _cameraGetFree(void)
{
    GScamera* camera = _cameraStructList;
    u32 i;

    for (i = 0; i < _cameraStructCount; i++, camera++) {
        if (camera->used == 0) {
            return camera;
        }
    }
    return 0;
}

static inline int _objRefDec(HSD_ObjHeader* obj)
{
    u16 ref_count = obj->ref_count;
    int ret = ref_count == (u16)-1;

    if (ret) {
        return ret;
    }
    obj->ref_count = ref_count - 1;
    return ref_count == 0;
}

static inline void _cameraUnref(HSD_CObj* cobj)
{
    HSD_ObjHeader* obj = (HSD_ObjHeader*)cobj;

    if (obj == 0) {
        return;
    }
    if (_objRefDec(obj)) {
        if (obj != 0) {
            ((void (*)(void*))obj->class_info[0x30 / 4])(obj);
            ((void (*)(void*))obj->class_info[0x34 / 4])(obj);
        }
    }
}

static inline void HSD_CObjSetFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == 0) {
        __assert("cobj.h", 0x19E, "cobj");
    }
    cobj->flags |= flags;
}

static inline void HSD_CObjClearFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == 0) {
        __assert("cobj.h", 0x1AA, "cobj");
    }
    cobj->flags &= ~flags;
}

static inline f32 __OSu16tof32(register const u16* arg)
{
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 3 }
#else
    ret = PSQ_LOAD(arg, 0, 3);
#endif
    return ret;
}

static inline void OSu16tof32(const u16* in, f32* out)
{
    *out = __OSu16tof32(in);
}

static inline f32 _fabs(f32 x)
{
    return (x > 0.0f) ? x : -x;
}

static inline void _cameraGetCObjVectors(GScamera* camera)
{
    HSD_CObjGetEyePosition(camera->cobj, &camera->eye);
    HSD_CObjGetUpVector(camera->cobj, &camera->up);
    HSD_CObjGetInterest(camera->cobj, &camera->interest);
}

static inline void _cameraBuildMatrix(GScamera* camera)
{
    if (camera->animating) {
        PSMTXCopy(HSD_CObjGetViewingMtxPtr(camera->cobj), camera->viewMtx);
        _cameraGetCObjVectors(camera);
    } else if (camera->lookAt == 1) {
        Vec diff;
        PSVECSubtract(&camera->eye, &camera->interest, &diff);
        if (_fabs(diff.x) < __float_epsilon[0] && _fabs(diff.y) < __float_epsilon[0] && _fabs(diff.z) < __float_epsilon[0]) {
            camera->interest.x += 0.01;
        }
        C_MTXLookAt(camera->viewMtx, &camera->eye, &camera->up, &camera->interest);
    } else {
        Mtx rotZ;
        Mtx rotY;
        PSMTXRotRad(camera->viewMtx, 'X', camera->rot.x);
        PSMTXRotRad(rotY, 'Y', camera->rot.y);
        PSMTXConcat(rotY, camera->viewMtx, camera->viewMtx);
        PSMTXRotRad(rotZ, 'Z', camera->rot.z);
        PSMTXConcat(rotZ, camera->viewMtx, camera->viewMtx);
        PSMTXTransApply(camera->viewMtx, camera->viewMtx, camera->eye.x, camera->eye.y, camera->eye.z);
        PSMTXInverse(camera->viewMtx, camera->viewMtx);
    }
    camera->dirty = 0;
}

static inline void _cameraGetPerspective(GScamera* camera, f32* fov, f32* aspect, f32* near, f32* far)
{
    f32 f, a;
    HSD_CObjGetPerspective(camera->cobj, &f, &a);
    if (fov != 0) {
        *fov = f;
    }
    if (aspect != 0) {
        *aspect = a;
    }
    if (near != 0) {
        *near = HSD_CObjGetNear(camera->cobj);
    }
    if (far != 0) {
        *far = HSD_CObjGetFar(camera->cobj);
    }
}

static inline void _cameraGetOrtho(GScamera* camera, f32* l, f32* r, f32* t, f32* b)
{
    if (l != 0 && r != 0 && t != 0 && b != 0) {
        HSD_CObjGetOrtho(camera->cobj, l, r, t, b);
    }
}

void cameraGetFrameCount(HSD_AObj* aobj)
{
    _frameCount = 1.0f + HSD_AObjGetEndFrame(aobj);
}

extern "C" {

void GScameraInit(u32 count)
{
    GSgfxRenderModule module = { 0, _cameraPreUpdate, 0, 0, _cameraPostUpdate, 0, 0xB29A48E1 };
    u32 i;

    _cameraStructCount = count;
    _cameraStructList = (GScamera*)GSmemAlloc(count * sizeof(GScamera));
    if (_cameraStructList != 0) {
        for (i = 0; i < _cameraStructCount; i++) {
            _cameraStructList[i].used = 0;
        }
        GSgfxRenderModuleRegister(0, &module, 0);
    }
}

GScamera* GScameraCreate(void)
{
    u16 width;
    u16 height;
    GScamera* camera = _cameraGetFree();

    if (camera == 0) {
        return 0;
    }
    memset(camera, 0, sizeof(GScamera));
    GSgfxVideoGetEFBSize(&width, &height);
    camera->positionDesc.class_name = 0;
    camera->positionDesc.x = 0.0f;
    camera->positionDesc.y = 0.0f;
    camera->positionDesc.z = 0.0f;
    camera->positionDesc.robjdesc = 0;
    camera->interestDesc.class_name = 0;
    camera->interestDesc.x = 0.0f;
    camera->interestDesc.y = 0.0f;
    camera->interestDesc.z = 1.0f;
    camera->interestDesc.robjdesc = 0;
    camera->cobjDesc.class_name = 0;
    camera->cobjDesc.flags = 0;
    camera->cobjDesc.projection_type = 1;
    camera->cobjDesc.viewport_left = 0;
    camera->cobjDesc.viewport_top = 0;
    camera->cobjDesc.viewport_right = width;
    camera->cobjDesc.viewport_bottom = height;
    camera->cobjDesc.scissor_left = 0;
    camera->cobjDesc.scissor_top = 0;
    camera->cobjDesc.scissor_right = width;
    camera->cobjDesc.scissor_bottom = height;
    camera->cobjDesc.position = &camera->positionDesc;
    camera->cobjDesc.interest = &camera->interestDesc;
    camera->cobjDesc.roll = 0.0f;
    camera->cobjDesc.targetDesc = 0;
    camera->cobjDesc.near = 0.1f;
    camera->cobjDesc.far = 2000.0f;
    camera->cobjDesc.fov = 60.0f;
    camera->cobjDesc.aspect = 1.333333f;
    camera->up.x = 0.0f;
    camera->up.y = 1.0f;
    camera->up.z = 0.0f;
    camera->flags = 3;
    camera->cobj = HSD_CObjLoadDesc(&camera->cobjDesc);
    if (camera->cobj == 0) {
        return 0;
    }
    _cameraGetCObjVectors(camera);
    camera->used = 1;
    camera->lookAt = 0;
    camera->animating = 0;
    camera->canAnimate = 0;
    camera->desc = 0;
    return camera;
}

void GScameraSetAnimIndex(GScamera* camera, u32 index);

GScamera* GScameraLoad(GScameraDesc* desc)
{
    u16 width;
    u16 height;
    GScamera* camera = _cameraGetFree();

    if (camera == 0) {
        return 0;
    }
    memset(camera, 0, sizeof(GScamera));
    camera->desc = desc;
    camera->cobj = HSD_CObjLoadDesc(camera->desc->cobjDesc);
    if (camera->cobj == 0) {
        return 0;
    }
    camera->used = 1;
    camera->animating = 0;
    if (camera->desc->anims != 0) {
        camera->canAnimate = 1;
        camera->rate = 1.0f;
        camera->animType = 1;
        camera->ended = 0;
        for (camera->animCount = 0; camera->desc->anims[camera->animCount] != 0; camera->animCount++) {
        }
        GScameraSetAnimIndex(camera, 0);
    } else {
        camera->canAnimate = 0;
    }
    GSgfxVideoGetEFBSize(&width, &height);
    camera->flags = 1;
    if (camera->cobjDesc.viewport_left != 0 || camera->cobjDesc.viewport_top != 0 || camera->cobjDesc.viewport_right != width
        || camera->cobjDesc.viewport_bottom != height) {
        camera->flags |= 2;
    }
    if (camera->cobjDesc.scissor_left != 0 || camera->cobjDesc.scissor_top != 0 || camera->cobjDesc.scissor_right != width
        || camera->cobjDesc.scissor_bottom != height) {
        camera->flags |= 4;
    }
    camera->cobjDesc.scissor_left = 0;
    camera->cobjDesc.scissor_top = 0;
    camera->cobjDesc.scissor_right = width;
    camera->cobjDesc.scissor_bottom = height;
    camera->used = 1;
    camera->lookAt = 0;
    _cameraGetCObjVectors(camera);
    return camera;
}

u8 GScameraIsValid(GScamera* camera)
{
    GScamera* c;
    u32 i;

    if (camera == 0) {
        return 0;
    }
    if (camera->used != 1) {
        return 0;
    }
    if (camera->cobj == 0) {
        return 0;
    }
    c = _cameraStructList;
    for (i = 0; i < _cameraStructCount; i++, c++) {
        if (c == camera) {
            return 1;
        }
    }
    return 0;
}

void GScameraFree(GScamera* camera)
{
    if (camera == _activeCamera) {
        _activeCamera = 0;
    }
    if (camera == _newActiveCamera) {
        _newActiveCamera = 0;
    }
    _cameraUnref(camera->cobj);
    camera->used = 0;
}

void GScameraSetActiveCamera(GScamera* camera)
{
    if (camera != 0) {
        GScamera* active = _activeCamera;
        if (active == 0) {
            _activeCamera = camera;
        }
        if (active != 0) {
            _newActiveCamera = camera;
        }
        _cameraBuildMatrix(camera);
    }
}

GScamera* GScameraGetActiveCamera(void)
{
    return _activeCamera;
}

}

static inline void _layerDirtyViewport(GSgfxLayer* layer)
{
    (*(u32*)&layer->dirty[0].raster) |= 0x10;
    (*(u32*)&layer->dirty[0].groups) |= 2;
    (*(u32*)&layer->dirty[1].raster) |= 0x10;
    (*(u32*)&layer->dirty[1].groups) |= 2;
}

static inline void _layerDirtyScissor(GSgfxLayer* layer)
{
    (*(u32*)&layer->dirty[0].raster) |= 1;
    (*(u32*)&layer->dirty[0].groups) |= 2;
    (*(u32*)&layer->dirty[1].raster) |= 1;
    (*(u32*)&layer->dirty[1].groups) |= 2;
}

static inline void _layerSetViewport(GSgfxLayer* layer, f32 x, f32 y, f32 w, f32 h)
{
    (*(f32*)&layer->hw.viewport[0]) = x;
    (*(f32*)&layer->hw.viewport[1]) = y;
    (*(f32*)&layer->hw.viewport[2]) = w;
    (*(f32*)&layer->hw.viewport[3]) = h;
    _layerDirtyViewport(layer);
}

static inline void _layerSetScissor(GSgfxLayer* layer, s16 x, s16 y, s16 w, s16 h)
{
    (*(s16*)&layer->hw.scissor[0]) = x;
    (*(s16*)&layer->hw.scissor[1]) = y;
    (*(s16*)&layer->hw.scissor[2]) = w;
    (*(s16*)&layer->hw.scissor[3]) = h;
    _layerDirtyScissor(layer);
}


#pragma dont_inline on
static void _cameraLoadClipping(GScamera* camera, GSgfxLayer* layer)
{
    if (camera->flags & 1) {
        if (camera->flags & 2) {
            HSD_CObj* cobj = camera->cobj;
            f32 y = cobj->viewport_top;
            f32 x = cobj->viewport_left;
            _layerSetViewport(layer, x, y, 0.5f * (cobj->viewport_right - x) + x, 0.5f * (cobj->viewport_bottom - y) + y);
        } else {
            u16 h, w;
            u16 hw, hh;
            f32 vh, vw;
            GSgfxVideoGetEFBSize(&w, &h);
            hw = w >> 1;
            vw = __OSu16tof32(&hw);
            hh = h >> 1;
            vh = __OSu16tof32(&hh);
            _layerSetViewport(layer, 0.0f, 0.0f, vw, vh);
        }
        if (camera->flags & 4) {
            HSD_CObj* cobj = camera->cobj;
            u16 top = cobj->scissor_top;
            u16 bottom = cobj->scissor_bottom;
            u16 left = cobj->scissor_left;
            u16 right = cobj->scissor_right;
s16 h = bottom - top;
            s16 w = right - left;
            _layerSetScissor(layer, left, top, w, h);
        } else {
            (*(s16*)&layer->hw.scissor[0]) = 0;
            (*(s16*)&layer->hw.scissor[1]) = 0;
            GSgfxVideoGetEFBSize((u16*)&(*(s16*)&layer->hw.scissor[2]), (u16*)&(*(s16*)&layer->hw.scissor[3]));
            _layerDirtyScissor(layer);
        }
    }
}


#pragma dont_inline reset
static inline void _layerSetProjection(GSgfxLayer* layer, f32* m, s32 type)
{
    (*(s32*)&layer->hw.projType) = type;
    ((f32*)layer->hw.proj)[0] = m[0];
    ((f32*)layer->hw.proj)[1] = m[2];
    ((f32*)layer->hw.proj)[2] = m[5];
    ((f32*)layer->hw.proj)[3] = m[6];
    ((f32*)layer->hw.proj)[4] = m[10];
    ((f32*)layer->hw.proj)[5] = m[11];
}

static inline void _layerSetOrthoProjection(GSgfxLayer* layer, f32* m)
{
    (*(s32*)&layer->hw.projType) = 1;
    ((f32*)layer->hw.proj)[0] = m[0];
    ((f32*)layer->hw.proj)[1] = m[3];
    ((f32*)layer->hw.proj)[2] = m[5];
    ((f32*)layer->hw.proj)[3] = m[7];
    ((f32*)layer->hw.proj)[4] = m[10];
    ((f32*)layer->hw.proj)[5] = m[11];
}

static inline void _layerSetDirty(GSgfxLayer* layer)
{
    if ((*(u8*)&layer->hw.fogEnable) != 0) {
        if ((*(u8*)&layer->hw.fogRangeEnable) != 0) {
            (*(u32*)&layer->dirty[0].pe) |= 0x100;
            (*(u32*)&layer->dirty[1].pe) |= 0x100;
        }
        (*(u32*)&layer->dirty[0].pe) |= 0x40;
        (*(u32*)&layer->dirty[0].groups) |= 0x40;
        (*(u32*)&layer->dirty[1].pe) |= 0x40;
        (*(u32*)&layer->dirty[1].groups) |= 0x40;
    }
    (*(u32*)&layer->dirty[0].geom) |= 0x20;
    (*(u32*)&layer->dirty[0].groups) |= 1;
    (*(u32*)&layer->dirty[1].geom) |= 0x20;
    (*(u32*)&layer->dirty[1].groups) |= 1;
}

static inline void _layerSetCamMtx(GSgfxLayer* layer)
{
    GSlayerCam* cam = (*(GSlayerCam**)&layer->matrixStack);
    memcpy(cam->data->mtx, mtxIdent, 0x30);
    cam->data->flags |= 1;
}

static inline void _layerPerspective(GSgfxLayer* layer, f32 fov, f32 aspect, f32 near, f32 far, Mtx44 proj)
{

    GSmtx44Perspective((f32*)proj, fov, aspect, near, far);
    _layerSetProjection(layer, (f32*)proj, 0);
    (*(f32*)&layer->hw.fogNear) = near;
    (*(f32*)&layer->hw.fogFar) = far;
    _layerSetDirty(layer);
}

static inline void _layerSetPerspective(GScamera* camera, GSgfxLayer* layer, f32* fov, f32* aspect, f32* near, f32* far, Mtx44 proj)
{
    _cameraGetPerspective(camera, fov, aspect, near, far);
    _layerPerspective(layer, *fov, *aspect, *near, *far, proj);
    _layerSetCamMtx(layer);
    {
        GSlayerCam* cam = (*(GSlayerCam**)&layer->matrixStack);
        PSMTXConcat(cam->data->mtx, camera->viewMtx, cam->data->mtx);
        cam->data->flags |= 1;
    }
}

static void _cameraLoadCameraMatrix(GScamera* camera, GSgfxLayerID id)
{
    GSgfxLayer* layer;
    Mtx44 projB, projA, projO;
    f32 p0, p1, p2, p3;

    if (id == GS_GFX_LAYER_NONE) {
        layer = 0;
    } else {
        layer = GSgfxLayerFindByID(id);
    }
    if (camera->animating) {
        HSD_CObjClearFlags(camera->cobj, 2);
        PSMTXCopy(HSD_CObjGetViewingMtxPtr(camera->cobj), camera->viewMtx);
        _cameraGetCObjVectors(camera);
        if (layer != 0) {
            _layerSetPerspective(camera, layer, &p0, &p1, &p2, &p3, projB);
        }
    } else if (camera->cobj->projection_type == 1) {
        if (camera->dirty) {
            _cameraBuildMatrix(camera);
        }
        HSD_CObj* cobj = camera->cobj;
        HSD_CObjSetFlags(cobj, 0x80000002);
        PSMTXCopy(camera->viewMtx, GSCAMERA_COBJ_VIEWMTX(cobj));
        if (layer != 0) {
            _layerSetPerspective(camera, layer, &p0, &p1, &p2, &p3, projA);
        }
    } else if (layer != 0) {
        _cameraGetOrtho(camera, &p1, &p3, &p0, &p2);
        GSmtx44Ortho((f32*)projO, p1, p3, p0, p2, 0.0f, -30000.0f);
        _layerSetOrthoProjection(layer, (f32*)projO);
        _layerSetCamMtx(layer);
        (*(f32*)&layer->hw.fogNear) = 0.0f;
        (*(f32*)&layer->hw.fogFar) = 30000.0f;
        _layerSetDirty(layer);
        _layerSetCamMtx(layer);
    }
    if (layer != 0) {
        _cameraLoadClipping(camera, layer);
    }
}

extern "C" {

void GScameraLoadActiveCameraMatrix(GSgfxLayerID id)
{
    if (_activeCamera != 0) {
        _cameraLoadCameraMatrix(_activeCamera, id);
    }
}

void GScameraLoadCameraMatrix(GScamera* camera, GSgfxLayerID id)
{
    if (camera == 0) {
        if (_activeCamera != 0) {
            _cameraLoadCameraMatrix(_activeCamera, id);
        }
    } else {
        _cameraLoadCameraMatrix(camera, id);
    }
}

void GScameraLoadProjection(GScamera* camera, GSgfxLayer* layer)
{
    Mtx44 proj;
    HSD_CObj* cobj;

    if (camera != 0) {
        cobj = camera->cobj;
        if (cobj != 0) {
            GScameraLoadCameraMatrix(camera, (GSgfxLayerID)(*(s32*)&layer->id));
            HSD_CObjMakeProjectionMtx(cobj, proj);
            HSD_CObjSetupViewingMtx(cobj);
        }
    }
}

#pragma peephole off
void GScameraSetViewport(GScamera* camera, u8 enable, f32 x0, f32 y0, f32 x1, f32 y1)
{
    if (camera == 0 || camera->used == 0) {
        return;
    }
    {
        camera->cobj->viewport_left = x0;
        camera->cobj->viewport_top = y0;
        camera->cobj->viewport_right = 2.0f * (x1 - x0) + x0;
        camera->cobj->viewport_bottom = 2.0f * (y1 - y0) + y0;
        if (enable) {
            camera->flags |= 2;
        } else {
            camera->flags &= ~2;
        }
    }
}
#pragma peephole on

#pragma peephole off
void GScameraSetScissor(GScamera* camera, u8 enable, s16 x, s16 y, s16 w, s16 h)
{
    if (camera == 0 || camera->used == 0) {
        return;
    }
    {
        camera->cobj->scissor_left = x;
        camera->cobj->scissor_top = y;
        camera->cobj->scissor_right = x + w;
        camera->cobj->scissor_bottom = y + h;
        if (enable) {
            camera->flags |= 4;
        } else {
            camera->flags &= ~4;
        }
    }
}
#pragma peephole on

void GScameraSetPerspective(GScamera* camera, f32 fov, f32 aspect, f32 near, f32 far)
{
    HSD_CObjSetProjectionType(camera->cobj, 1);
    HSD_CObjSetPerspective(camera->cobj, fov, aspect);
    HSD_CObjSetNear(camera->cobj, near);
    HSD_CObjSetFar(camera->cobj, far);
    camera->dirty = 1;
}

void GScameraSetPosition(GScamera* camera, f32* position)
{
    HSD_CObjSetEyePosition(camera->cobj, (Vec*)position);
    camera->eye.x = position[0];
    camera->eye.y = position[1];
    camera->eye.z = position[2];
    camera->dirty = 1;
}

void GScameraSetRotation(GScamera* camera, f32* rotation)
{
    camera->rot.x = rotation[0];
    camera->rot.y = rotation[1];
    camera->rot.z = rotation[2];
    camera->dirty = 1;
    camera->lookAt = 0;
}

void GScameraGetPerspective(GScamera* camera, f32* fov, f32* aspect, f32* near, f32* far)
{
    f32 f, a;

    HSD_CObjGetPerspective(camera->cobj, &f, &a);
    if (fov != 0) {
        *fov = f;
    }
    if (aspect != 0) {
        *aspect = a;
    }
    if (near != 0) {
        *near = HSD_CObjGetNear(camera->cobj);
    }
    if (far != 0) {
        *far = HSD_CObjGetFar(camera->cobj);
    }
}

void GScameraGetPosition(GScamera* camera, f32* position)
{
    if (position != 0) {
        if (camera->animating) {
            HSD_CObjGetEyePosition(camera->cobj, &camera->eye);
        }
        position[0] = camera->eye.x;
        position[1] = camera->eye.y;
        position[2] = camera->eye.z;
    }
}

void GScameraGetRotation(GScamera* camera, f32* rotation)
{
    if (rotation != 0) {
        rotation[0] = camera->rot.x;
        rotation[1] = camera->rot.y;
        rotation[2] = camera->rot.z;
    }
}



static f32 _cameraRemovedHalf(f32 v)
{
    return 0.5f * v;
}

#pragma peephole off
void GScameraGetFrontVector(GScamera* camera, f32* front)
{
    if (camera == 0 || front == 0) {
        return;
    }
    {
        if (camera->lookAt != 0) {
            Vec eye;
            if (&eye != 0) {
                if (camera->animating) {
                    HSD_CObjGetEyePosition(camera->cobj, &camera->eye);
                }
                eye.x = camera->eye.x;
                eye.y = camera->eye.y;
                eye.z = camera->eye.z;
            }
            PSVECSubtract(&camera->interest, &eye, (Vec*)front);
        } else {
            Mtx m;
            Mtx rotY;
            Mtx rotZ;
            front[0] = 0.0f;
            front[1] = 0.0f;
            front[2] = -1.0f;
            PSMTXRotRad(m, 'X', camera->rot.x);
            PSMTXRotRad(rotY, 'Y', camera->rot.y);
            PSMTXConcat(rotY, m, m);
            PSMTXRotRad(rotZ, 'Z', camera->rot.z);
            PSMTXConcat(rotZ, m, m);
            PSMTXMultVec(m, (Vec*)front, (Vec*)front);
        }
        PSVECNormalize((Vec*)front, (Vec*)front);
    }
}
#pragma peephole on

void GScameraLookAt(GScamera* camera, f32* up, f32* interest)
{
    if (up != 0) {
        camera->up.x = up[0];
        camera->up.y = up[1];
        camera->up.z = up[2];
    }
    if (interest != 0) {
        camera->interest.x = interest[0];
        camera->interest.y = interest[1];
        camera->interest.z = interest[2];
    }
    camera->dirty = 1;
    camera->lookAt = 1;
}

void GScameraGetLookAt(GScamera* camera, f32* up, f32* interest)
{
    if (up != 0) {
        up[0] = camera->up.x;
        up[1] = camera->up.y;
        up[2] = camera->up.z;
    }
    if (interest != 0) {
        interest[0] = camera->interest.x;
        interest[1] = camera->interest.y;
        interest[2] = camera->interest.z;
    }
}

MtxPtr GScameraGetMatrixPtr(GScamera* camera)
{
    if (camera->dirty) {
        _cameraBuildMatrix(camera);
    }
    return camera->viewMtx;
}

MtxPtr GScameraGetInvMatrixPtr(GScamera* camera)
{
    if (camera->dirty) {
        _cameraBuildMatrix(camera);
    }
    PSMTXInverse(camera->viewMtx, camera->invMtx);
    return camera->invMtx;
}

MtxPtr GScameraGetProjMatrixPtr(GScamera* camera)
{
    static Mtx44 projMtx;
    f32 fov, aspect, near, far;
    f32 t, l, b, r;

    if (camera->cobj->projection_type == 1) {
        _cameraGetPerspective(camera, &fov, &aspect, &near, &far);
        GSmtx44Perspective((f32*)projMtx, fov, aspect, near, far);
    } else {
        _cameraGetOrtho(camera, &l, &r, &t, &b);
        GSmtx44Ortho((f32*)projMtx, l, r, t, b, 0.1f, 2000.0f);
    }
    return (MtxPtr)projMtx;
}

void GScameraGetDistanceVector(GScamera* camera, f32* out)
{
    if (out != 0) {
        PSVECSubtract(&camera->eye, &camera->interest, (Vec*)out);
    }
}

u8 GScameraIsAnimating(GScamera* camera)
{
    return camera->animating;
}

void GScameraSetAnimFrame(GScamera* camera, f32 frame);

void GScameraSetAnimIndex(GScamera* camera, u32 index)
{
    if (camera->canAnimate) {
        HSD_CObjRemoveAnim(camera->cobj);
        if (index <= camera->animCount) {
            camera->animIndex = index;
            HSD_CObjAddAnim(camera->cobj, camera->desc->anims[camera->animIndex]);
            _frameCount = 0.0f;
            HSD_ForeachAnim(camera->cobj, 2, 0xFFFF, cameraGetFrameCount, 0);
            camera->frameCount = _frameCount;
            GScameraSetAnimFrame(camera, 0.0f);
        }
    }
}

void GScameraSetAnimRate(GScamera* camera, f32 rate)
{
    if (camera->canAnimate) {
        if (GSgfxVideoGetVsyncRate() == 50) {
            rate *= 1.2f;
        }
        camera->rate = rate;
        HSD_ForeachAnim(camera->cobj, 2, 0xFFFF, HSD_AObjSetRate, 1, camera->rate);
    }
}

void GScameraSetAnimFrame(GScamera* camera, f32 frame)
{
    if (camera->canAnimate) {
        camera->frame = frame;
        HSD_ForeachAnim(camera->cobj, 2, 0xFFFF, HSD_AObjSetRate, 1, 0.0f);
        HSD_CObjReqAnim(camera->cobj, camera->frame);
        HSD_CObjAnim(camera->cobj);
        _cameraGetCObjVectors(camera);
        HSD_ForeachAnim(camera->cobj, 2, 0xFFFF, HSD_AObjSetRate, 1, camera->rate);
    }
}

void GScameraSetAnimType(GScamera* camera, s32 type)
{
    camera->animType = type;
}

void GScameraStartAnimation(GScamera* camera)
{
    if (camera->canAnimate) {
        camera->animating = 1;
        camera->ended = 0;
        camera->direction = 1;
        GScameraSetAnimFrame(camera, camera->frame);
    }
}

void GScameraStopAnimation(GScamera* camera)
{
    camera->animating = 0;
    camera->lookAt = 1;
    _cameraGetCObjVectors(camera);
}

u8 GScameraHasAnimationEnded(GScamera* camera)
{
    return camera->ended;
}

f32 GScameraGetAnimFrame(GScamera* camera)
{
    return camera->frame;
}

void GScameraPushState(GScamera* camera, GScameraState* state)
{
    state->animating = camera->animating;
    state->eye.x = camera->eye.x;
    state->eye.y = camera->eye.y;
    state->eye.z = camera->eye.z;
    state->prevEye.x = camera->prevEye.x;
    state->prevEye.y = camera->prevEye.y;
    state->prevEye.z = camera->prevEye.z;
    state->rot.x = camera->rot.x;
    state->rot.y = camera->rot.y;
    state->rot.z = camera->rot.z;
    PSMTXCopy(camera->viewMtx, state->viewMtx);
    PSMTXCopy(camera->invMtx, state->invMtx);
    state->up.x = camera->up.x;
    state->up.y = camera->up.y;
    state->up.z = camera->up.z;
    state->interest.x = camera->interest.x;
    state->interest.y = camera->interest.y;
    state->interest.z = camera->interest.z;
    state->animType = camera->animType;
    state->animIndex = camera->animIndex;
    state->rate = camera->rate;
    state->frame = camera->frame;
    state->ended = camera->ended;
}

void GScameraPopState(GScamera* camera, GScameraState* state)
{
    camera->eye.x = state->eye.x;
    camera->eye.y = state->eye.y;
    camera->eye.z = state->eye.z;
    camera->prevEye.x = state->prevEye.x;
    camera->prevEye.y = state->prevEye.y;
    camera->prevEye.z = state->prevEye.z;
    camera->rot.x = state->rot.x;
    camera->rot.y = state->rot.y;
    camera->rot.z = state->rot.z;
    PSMTXCopy(state->viewMtx, camera->viewMtx);
    PSMTXCopy(state->invMtx, camera->invMtx);
    camera->up.x = state->up.x;
    camera->up.y = state->up.y;
    camera->up.z = state->up.z;
    camera->interest.x = state->interest.x;
    camera->interest.y = state->interest.y;
    camera->interest.z = state->interest.z;
    camera->ended = state->ended;
    if (state->ended == 0 && state->animating != 0) {
        GScameraSetAnimIndex(camera, state->animIndex);
        GScameraSetAnimType(camera, state->animType);
        GScameraSetAnimRate(camera, state->rate);
        GScameraSetAnimFrame(camera, state->frame);
        GScameraStartAnimation(camera);
    }
}

}

static void _cameraPreUpdate(f32 dt)
{
    u32 i;
    GScamera* camera;

    for (i = 0; i < _cameraStructCount; i++) {
        camera = &_cameraStructList[i];
        if (camera->used == 1) {
            camera->prevEye.x = camera->eye.x;
            camera->prevEye.y = camera->eye.y;
            camera->prevEye.z = camera->eye.z;
            if (camera->animating == 1) {
                HSD_CObjReqAnim(camera->cobj, camera->frame);
                HSD_CObjAnim(camera->cobj);
                _cameraGetCObjVectors(camera);
                camera->dirty = 1;
            }
            _cameraBuildMatrix(camera);
        }
    }
}

static void _cameraPostUpdate(f32 dt)
{
    u32 i;
    GScamera* camera;
    f32 end;
    f32 step;
    s32 type;

    for (i = 0; i < _cameraStructCount; i++) {
        camera = &_cameraStructList[i];
        if (camera->used == 1 && camera->animating == 1) {
            step = camera->rate * dt;
            end = camera->frameCount - 1.0f;
            type = camera->animType;
            if (camera->direction == -1) {
                camera->frame -= step;
            } else if (camera->direction == 1) {
                camera->frame += step;
            }
            switch (type) {
            case 0:
                if (camera->frame >= end - 0.1f) {
                    camera->ended = 1;
                    camera->direction = 0;
                    camera->frame = end - 0.1f;
                }
                break;
            case 1:
                if (camera->frame >= end) {
                    camera->frame -= end;
                }
                break;
            case 2:
                if (camera->frame >= end) {
                    camera->direction = -1;
                } else if (camera->frame <= 0.0f) {
                    camera->direction = 1;
                }
                break;
            }
            camera->dirty = 1;
        }
    }
    if (_newActiveCamera != 0) {
        if (_newActiveCamera->used != 0) {
            _activeCamera = _newActiveCamera;
        }
        _newActiveCamera = 0;
    }
}
