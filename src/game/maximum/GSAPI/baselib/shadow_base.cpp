


#define HSD_FILE_NAME "shadow.c"

#include <sysdolphin/baselib/shadow.h>

#define _MATH_H_
#include <string.h>

#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/object.h>
#include <sysdolphin/baselib/perf.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/util.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#pragma pool_strings off

extern f32 __float_epsilon[];
extern f32 __float_min[];
#define EPS (__float_epsilon[0])
#undef FLT_MIN
#define FLT_MIN (__float_min[0])

double atan2(double y, double x);
void PSVECNormalize(const Vec* src, Vec* dst);

#undef fabs
#undef fabsf
inline double fabs(double x)
{
    return __fabs(x);
}

inline float fabsf(float x)
{
    return (float) fabs(x);
}

inline float atan2f(float y, float x)
{
    return (float) atan2(y, x);
}

static inline int vecNormalize(Vec3* src, Vec3* dst)
{
    if (!src || !dst) {
        return -1;
    }
    if (fabs(src->x) <= FLT_MIN && fabs(src->y) <= FLT_MIN &&
        fabs(src->z) <= FLT_MIN)
    {
        return -1;
    }
    PSVECNormalize(src, dst);
    return 0;
}

void* GSmemAllocAlignFromEnd(u32 size, int align);
void GSmemFree(void* ptr);
void DCFlushRange(void* addr, u32 nBytes);

static u8 shadow_debug = 0;

HSD_ObjAllocData shadow_alloc_data;

static inline void freeImage(HSD_Shadow* shadow)
{
    HSD_ImageDesc* idesc = shadow->texture->imagedesc;
    if (idesc->image_ptr) {
        GSmemFree(idesc->image_ptr);
        idesc->image_ptr = NULL;
    }
}



#define HSD_ASSERT2(line, text, cond)                                         \
    ((cond) ? ((void) 0) : __assert(HSD_FILE_NAME, line, text))



inline HSD_TObj* makeShadowTObj(void);
HSD_ObjAllocData* HSD_ShadowGetAllocData(void);
void HSD_ShadowInitAllocData(void);
HSD_Shadow* HSD_ShadowAlloc(void);
void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 width, u16 height);
void HSD_ShadowRender(HSD_Shadow* shadow);
void HSD_ShadowCopyTex(HSD_Shadow* shadow);
void HSD_ShadowCopyLightPos(HSD_Shadow* shadow, HSD_LObj* lobj, float distance);
void HSD_ShadowSetActive(HSD_Shadow* shadow, int active);
void HSD_ShadowAddObject(HSD_Shadow* shadow, HSD_JObj* jobj);
void HSD_ShadowDeleteObject(HSD_Shadow* shadow, HSD_JObj* jobj);
void HSD_ShadowFreeTexture(HSD_Shadow* shadow);
void HSD_ShadowSetDebug(u8 debug);
void HSD_ShadowSetViewingRect(HSD_Shadow* shadow, float top, float bottom, float left, float right);
void HSD_ViewingRectInit(HSD_ViewingRect* rect, Vec3* position, Vec3* interest, Vec3* upvector, int perspective);
int HSD_ViewingRectCheck(HSD_ViewingRect* rect);
void HSD_ViewingRectAddRect(HSD_ViewingRect* rect, Vec3* position, float top, float bottom, float left, float right);

inline HSD_TObj* makeShadowTObj(void)
{
    HSD_TObj* shadowTObj;
    shadowTObj = HSD_TObjAlloc();
    shadowTObj->src = 0;
    shadowTObj->wrap_s = 0;
    shadowTObj->wrap_t = 0;
    shadowTObj->flags = 0x540103;
    shadowTObj->imagedesc = HSD_ImageDescAlloc();
    return shadowTObj;
}

HSD_ObjAllocData* HSD_ShadowGetAllocData(void)
{
    return &shadow_alloc_data;
}

void HSD_ShadowInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_ShadowGetAllocData(), sizeof(HSD_Shadow), 4);
}

HSD_Shadow* HSD_ShadowAlloc(void)
{
    HSD_Shadow* shadow;

    shadow = HSD_ObjAlloc(HSD_ShadowGetAllocData());
    memset(shadow, 0, sizeof(HSD_Shadow));
    shadow->camera = HSD_CObjAlloc();
    shadow->texture = makeShadowTObj();

    shadow->scaleS = 0.5F;
    shadow->scaleT = -0.5F;
    shadow->transS = 0.5F;
    shadow->transT = 0.5F;
    shadow->intensity = 0;

    shadow->texture->imagedesc->format = 0;
    shadow->texture->imagedesc->width = 256;
    shadow->texture->imagedesc->height = 256;
    shadow->texture->imagedesc->image_ptr = NULL;

    HSD_CObjSetViewportfx4(shadow->camera, 0.0f, 256.f, 0.0f, 256.f);
    HSD_CObjSetScissorx4(shadow->camera, 0, 256, 0, 256);

    return shadow;
}

void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 width, u16 height)
{
    u32 size;
    HSD_ImageDesc* idesc;

    HSD_ASSERT(272, shadow);
    HSD_ASSERT(273, width > 0);
    HSD_ASSERT(274, height > 0);

    idesc = shadow->texture->imagedesc;
    if (!idesc->image_ptr || idesc->width != width || idesc->height != height)
    {
        if (idesc->image_ptr) {
            freeImage(shadow);
        }

        size = GXGetTexBufferSize(width, height, GX_TF_I4, GX_FALSE, 0);
        HSD_ASSERT(283, size > 0);
        idesc->image_ptr = GSmemAllocAlignFromEnd(size, 0x20);
        if (idesc->image_ptr) {
            DCFlushRange(idesc->image_ptr, size);
            idesc->width = width;
            idesc->height = height;

            HSD_CObjSetViewportfx4(shadow->camera, 0, width, 0, height);
            HSD_CObjSetScissorx4(shadow->camera, 0, width, 0, height);
        }
    }
}

static inline void drawQuad(void)
{
    GXLoadPosMtxImm(HSD_identityMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    HSD_ClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U8, 0);
    HSD_StateSetCullMode(GX_CULL_BACK);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2u8(0, 1);
    GXPosition2u8(1, 1);
    GXPosition2u8(1, 0);
    GXPosition2u8(0, 0);
    GXEnd();
}

void HSD_ShadowRender(HSD_Shadow* shadow)
{
    static HSD_Chan chan = {
        NULL,           GX_COLOR0A0,      0,
        { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, GX_FALSE,
        GX_SRC_REG,     GX_SRC_REG,       GX_LIGHT_NULL,
        GX_DF_CLAMP,    GX_AF_NONE,       NULL,
    };
    static HSD_TevDesc tev = {
        NULL,
        1,
        GX_TEVSTAGE0,
        GX_TEXCOORD_NULL,
        GX_TEXMAP_NULL,
        GX_COLOR0A0,
        { { GX_TEV_ADD, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC,
            GX_CS_SCALE_1, GX_TB_ZERO, GX_TRUE, GX_TEVPREV, GX_TEV_ADD,
            GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA, GX_CS_SCALE_1,
            GX_TB_ZERO, GX_TRUE, GX_TEVPREV, (GXTevClampMode) 0, GX_TEV_SWAP0,
            GX_TEV_SWAP0, (GXTevKColorSel) 0, (GXTevKAlphaSel) 0, { 0, 1, 2, 3 } } }
    };
    static HSD_PEDesc pedesc = {
        9, 0, 0, 0, GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET,
        GX_ALWAYS, GX_ALWAYS, GX_AOP_AND, GX_ALWAYS,
    };
    static Mtx m = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1 } };
    HSD_SList* list;
    HSD_CObj* cobj;
    HSD_ImageDesc* idesc;
    Mtx44 ortho;
    Mtx proj;

    HSD_ASSERT(400, shadow);
    HSD_ASSERT(401, shadow->camera);
    HSD_ASSERT(402, shadow->texture);
    HSD_ASSERT(403, shadow->texture->imagedesc);

    if (shadow->objects) {
        cobj = shadow->camera;
        idesc = shadow->texture->imagedesc;
        HSD_ASSERT(411, idesc->image_ptr);

        HSD_StateInitTev();
        HSD_SetupTevStageAll(&tev);
        HSD_StateSetNumTexGens();
        HSD_SetupPEMode(0, &pedesc);

        chan.mat_color.r = 255;
        chan.mat_color.g = 255;
        chan.mat_color.b = 255;
        HSD_SetupChannelAll(&chan);

        MTXOrtho(ortho, 1.0F, 0.0F, 0.0F, 1.0F, -1.0F, 1.0F);
        GXSetProjection(ortho, GX_ORTHOGRAPHIC);
        GXSetViewport(0.0F, 0.0F, idesc->width, idesc->height, 0.0F, 1.0F);
        GXSetScissor(0, 0, idesc->width, idesc->height);
        drawQuad();

        if (shadow_debug) {
            chan.mat_color.r = 0;
            chan.mat_color.g = 0;
            chan.mat_color.b = 0;
            HSD_SetupChannelAll(&chan);
            GXSetScissor(2, 2, idesc->width - 4, idesc->height - 4);
            drawQuad();

            chan.mat_color.r = 255;
            chan.mat_color.g = 255;
            chan.mat_color.b = 255;
            HSD_SetupChannelAll(&chan);
            GXSetScissor(4, 4, idesc->width - 8, idesc->height - 8);
            drawQuad();
        }

        chan.mat_color.r = shadow->intensity;
        chan.mat_color.g = shadow->intensity;
        chan.mat_color.b = shadow->intensity;
        HSD_SetupChannelAll(&chan);

        if (HSD_CObjGetEyeDistance(cobj) >= EPS) {
            HSD_CObjSetCurrent(cobj);
            GXSetScissor(2, 2, idesc->width - 4, idesc->height - 4);
            for (list = shadow->objects; list != NULL; list = list->next) {
                HSD_JObjDispAll(list->data, NULL,
                                (HSD_TRSP_OPA | HSD_TRSP_TEXEDGE),
                                RENDER_SHADOW);
            }
        }

        if (HSD_CObjGetEyeDistance(shadow->camera) < EPS) {
            MTXCopy(m, shadow->texture->mtx);
        } else {
            switch (HSD_CObjGetProjectionType(shadow->camera)) {
            case PROJ_PERSPECTIVE:
                MTXLightPerspective(
                    proj, shadow->camera->projection_param.perspective.fov,
                    shadow->camera->projection_param.perspective.aspect,
                    shadow->scaleS, shadow->scaleT, shadow->transS,
                    shadow->transT);
                break;

            case PROJ_FRUSTUM:
                MTXLightFrustum(
                    proj, shadow->camera->projection_param.frustum.top,
                    shadow->camera->projection_param.frustum.bottom,
                    shadow->camera->projection_param.frustum.left,
                    shadow->camera->projection_param.frustum.right,
                    shadow->camera->near, shadow->scaleS, shadow->scaleT,
                    shadow->transS, shadow->transT);
                break;

            case PROJ_ORTHO:
                MTXLightOrtho(
                    proj, shadow->camera->projection_param.ortho.top,
                    shadow->camera->projection_param.ortho.bottom,
                    shadow->camera->projection_param.ortho.left,
                    shadow->camera->projection_param.ortho.right,
                    shadow->scaleS, shadow->scaleT, shadow->transS,
                    shadow->transT);
                break;

            default:
                HSD_ASSERT(711, 0);
            }
            MTXConcat(proj, HSD_CObjGetViewingMtxPtrDirect(shadow->camera),
                      shadow->texture->mtx);
        }
    }
}

void HSD_ShadowCopyTex(HSD_Shadow* shadow)
{
    HSD_ImageDesc* idesc;

    HSD_ASSERT(489, shadow);

    idesc = shadow->texture->imagedesc;
    HSD_ASSERT(493, idesc->image_ptr);

    GXSetTexCopySrc(0, 0, idesc->width, idesc->height);
    GXSetTexCopyDst(idesc->width, idesc->height, 0x20, 0);
    GXCopyTex(idesc->image_ptr, 1);
}

void HSD_ShadowCopyLightPos(HSD_Shadow* shadow, HSD_LObj* lobj, float distance)
{
    Vec3 eye;
    Vec3 interest;
    Vec3 position;

    HSD_ASSERT(522, shadow);
    HSD_ASSERT(523, lobj);

    switch (lobj->flags & 3) {
    case 1:
        HSD_CObjGetInterest(shadow->camera, &interest);
        HSD_LObjGetPosition(lobj, &position);
        VECScale(&position, &position, distance / (EPS + VECMag(&position)));
        VECAdd(&interest, &position, &eye);
        HSD_CObjSetEyePosition(shadow->camera, &eye);
        break;
    case 2:
    case 3:
        HSD_LObjGetPosition(lobj, &eye);
        HSD_CObjSetEyePosition(shadow->camera, &eye);
        break;
    default:
        HSD_ASSERT(541, 0);
    }
}

void HSD_ShadowSetActive(HSD_Shadow* shadow, int active)
{
    HSD_ImageDesc* idesc;

    HSD_ASSERT(563, shadow);

    if ((shadow->active && active) || (!shadow->active && !active)) {
        return;
    }

    shadow->active = active;
    if (active) {
        idesc = shadow->texture->imagedesc;
        if (!idesc->image_ptr) {
            HSD_ShadowSetSize(shadow, idesc->width, idesc->height);
        }

        HSD_MObjAddShadowTexture(shadow->texture);
    } else {
        HSD_MObjDeleteShadowTexture(shadow->texture);
    }
}

void HSD_ShadowAddObject(HSD_Shadow* shadow, HSD_JObj* jobj)
{
    HSD_SList* list;

    if (!shadow || !jobj) {
        return;
    }

    for (list = shadow->objects; list; list = list->next) {
        if (list->data == jobj) {
            return;
        }
    }
    shadow->objects = HSD_SListPrepend(shadow->objects, jobj);
    HSD_JObjRef(jobj);
}

void HSD_ShadowDeleteObject(HSD_Shadow* shadow, HSD_JObj* jobj)
{
    if (!shadow) {
        return;
    }

    if (jobj) {
        HSD_SList** list = &(shadow->objects);
        for (; *list; list = &((*list)->next)) {
            if ((*list)->data == jobj) {
                HSD_JObjUnref(jobj);
                (*list) = HSD_SListRemove(*list);
                return;
            }
        }
    } else {
        while (shadow->objects) {
            HSD_JObjUnref(shadow->objects->data);
            shadow->objects = HSD_SListRemove(shadow->objects);
        }
    }
}

void HSD_ShadowFreeTexture(HSD_Shadow* shadow)
{
    freeImage(shadow);
}

void HSD_ShadowSetDebug(u8 debug)
{
    shadow_debug = debug;
}

void HSD_ShadowSetViewingRect(HSD_Shadow* shadow, float top, float bottom,
                              float left, float right)
{
    HSD_CObj* cobj;
    float distance;

    HSD_ASSERT(734, shadow);

    cobj = shadow->camera;
    distance = HSD_CObjGetEyeDistance(cobj);
    if (!(distance < EPS)) {
        switch (HSD_CObjGetProjectionType(cobj)) {
        case PROJ_PERSPECTIVE: {
            float width, height;

            if (fabs(top) > fabs(bottom)) {
                width = fabs(top);
            } else {
                width = fabs(bottom);
            }
            if (fabs(left) > fabs(right)) {
                height = fabs(left);
            } else {
                height = fabs(right);
            }
            HSD_CObjSetAspect(cobj, height / (width + EPS));
            HSD_CObjSetFov(cobj, 57.29578F * atan2f(width, distance));
        } break;

        case PROJ_ORTHO:
            HSD_CObjSetOrtho(cobj, top, bottom, left, right);
            break;

        case PROJ_FRUSTUM: {
            float scale = HSD_CObjGetNear(cobj) / distance;
            if (scale < EPS) {
                scale = EPS;
            }
            HSD_CObjSetFrustum(cobj, scale * top, scale * bottom,
                               scale * left, scale * right);
        } break;

        default:
            HSD_ASSERT(779, 0);
        }
    }
}

void HSD_ViewingRectInit(HSD_ViewingRect* rect, Vec3* position, Vec3* interest,
                         Vec3* upvector, int perspective)
{
    HSD_ASSERT(810, rect);

    rect->invalid = 0;
    rect->origin = *position;
    VECSubtract(interest, position, &rect->eye_v);
    if (vecNormalize(&rect->eye_v, &rect->eye_vn) < 0) {
        rect->invalid = 1;
        return;
    }
    VECCrossProduct(&rect->eye_vn, upvector, &rect->right_v);
    if (vecNormalize(&rect->right_v, &rect->right_v) < 0) {
        HSD_VecGetOrthogonal(&rect->eye_vn, &rect->right_v);
        VECNormalize(&rect->right_v, &rect->right_v);
    }
    VECCrossProduct(&rect->right_v, &rect->eye_vn, &rect->up_v);
    rect->distance = VECMag(&rect->eye_v);

    rect->top = rect->right = -F32_MAX;
    rect->bottom = rect->left = F32_MAX;
    rect->perspective = perspective != 0;
}

int HSD_ViewingRectCheck(HSD_ViewingRect* rect)
{
    int result;

    HSD_ASSERT(840, rect);
    result = 0;
    if (!rect->invalid) {
        if (rect->top > rect->bottom && rect->right > rect->left) {
            result = 1;
        }
    }
    return result;
}


static void unusedAssertHolder(float a)
{
    HSD_ASSERT(0, a > 0.0F);
}

void HSD_ViewingRectAddRect(HSD_ViewingRect* rect, Vec3* position, float top,
                            float bottom, float left, float right)
{
    float x, y, dot, scale;
    Vec3 o2p, e2p;

    HSD_ASSERT(878, rect);
    HSD_ASSERT(879, position);

    if (rect->invalid) {
        return;
    }
    VECSubtract(position, &rect->origin, &o2p);
    dot = VECDotProduct(&o2p, &rect->eye_vn);
    if (rect->perspective) {
        if (dot <= 0.0F) {
            return;
        }
        scale = rect->distance / dot;
        VECScale(&o2p, &o2p, scale);
        VECSubtract(&o2p, &rect->eye_v, &e2p);
        x = VECDotProduct(&rect->right_v, &e2p);
        y = VECDotProduct(&rect->up_v, &e2p);

        top *= scale;
        bottom *= scale;
        left *= scale;
        right *= scale;
    } else {
        Vec3 tmp;
        VECScale(&rect->eye_vn, &tmp, dot);
        VECSubtract(&o2p, &tmp, &e2p);
        x = VECDotProduct(&rect->right_v, &e2p);
        y = VECDotProduct(&rect->up_v, &e2p);
    }

    if (x + right > rect->right) {
        rect->right = x + right;
    }
    if (x + left < rect->left) {
        rect->left = x + left;
    }
    if (y + top > rect->top) {
        rect->top = y + top;
    }
    if (y + bottom < rect->bottom) {
        rect->bottom = y + bottom;
    }
}
