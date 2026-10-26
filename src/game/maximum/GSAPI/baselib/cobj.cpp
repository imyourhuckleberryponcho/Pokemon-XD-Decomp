




#define HSD_FILE_NAME "cobj.c"

#include <sysdolphin/baselib/forward.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/object.h>
#include <sysdolphin/baselib/wobj.h>
#include <dolphin/mtx.h>

#pragma pool_strings off

#define PROJ_PERSPECTIVE 1
#define PROJ_FRUSTUM 2
#define PROJ_ORTHO 3

typedef struct _Scissor {
    u16 left;
    u16 right;
    u16 top;
    u16 bottom;
} Scissor;

typedef struct _HSD_RectS16 {
    s16 xmin;
    s16 xmax;
    s16 ymin;
    s16 ymax;
} HSD_RectS16;

typedef struct _HSD_RectF32 {
    f32 xmin;
    f32 xmax;
    f32 ymin;
    f32 ymax;
} HSD_RectF32;

struct HSD_CObj {
 HSD_Obj parent;
 u32 flags;
 HSD_RectF32 viewport;
 Scissor scissor;
 HSD_WObj* eyepos;
 HSD_WObj* interest;
    union {
 f32 roll;
 Vec3 up;
    } u;
 f32 near;
 f32 far;
    union {
        struct {
            f32 fov;
            f32 aspect;
        } perspective;
        struct {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } frustum;
        struct {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } ortho;
    } projection_param;
 u8 projection_type;
 Mtx view_mtx;
 HSD_AObj* aobj;
 Mtx* proj_mtx;
};

struct HSD_CameraDescCommon {
    char* class_name;
    u16 flags;
    u16 projection_type;
    HSD_RectS16 viewport;
    Scissor scissor;
    HSD_WObjDesc* eyepos;
    HSD_WObjDesc* interest;
    f32 roll;
    Vec3* up_vector;
    f32 nnear;
    f32 ffar;
};

struct HSD_CameraDescFrustum {
    struct HSD_CameraDescCommon common;
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
};

struct HSD_CameraDescPerspective {
    struct HSD_CameraDescCommon common;
    f32 fov;
    f32 aspect;
};

typedef union HSD_CObjDesc {
    char* class_name;
    struct HSD_CameraDescCommon common;
    struct HSD_CameraDescFrustum frustum;
    struct HSD_CameraDescFrustum ortho;
    struct HSD_CameraDescPerspective perspective;
} HSD_CObjDesc;

struct HSD_CObjInfo {
    HSD_ObjInfo parent;
    int (*load)(HSD_CObj* cobj, HSD_CObjDesc* desc);
    void (*update)(void* obj, u32 type, f32* val);
};

struct HSD_CameraAnim {
    HSD_AObjDesc* aobjdesc;
    HSD_WObjAnim* eye_anim;
    HSD_WObjAnim* interest_anim;
};

#define HSD_COBJ(o) ((HSD_CObj*) (o))
#define HSD_COBJ_INFO(i) ((HSD_CObjInfo*) (i))
#define HSD_COBJ_METHOD(o) HSD_COBJ_INFO(HSD_OBJECT_METHOD(o))

void* HSD_MtxAlloc(void);
void HSD_MtxFree(void* mtx);
void GXSetProjection(Mtx44 mtx, int type);
void OSReport(const char* fmt, ...);
double atan2(double y, double x);
int __fpclassifyf(float x);

extern f32 __float_min[];
extern f32 __float_nan[];
#define FLT_MIN (__float_min[0])
#define NAN (__float_nan[0])

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

inline int __fpclassifyf(float x)
{
    switch ((*(s32*) &x) & 0x7F800000) {
    case 0x7F800000:
        if ((*(s32*) &x) & 0x007FFFFF) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(s32*) &x) & 0x007FFFFF) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

inline float sqrtf(float x)
{
    if (x > 0.0f) {
        double guess = __frsqrte((double) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (float) (x * guess);
    } else if (x < 0.0) {
        return NAN;
    } else if (__fpclassifyf(x) == 1) {
        return NAN;
    }
    return x;
}

static inline int vec_normalize_check(Vec3* src, Vec3* dst)
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

static inline f32 atan2f_check(f32 y, f32 x)
{
    if (x == 0.0f) {
        return y >= 0.0f ? 1.5707964f : -1.5707964f;
    }
    return atan2f(y, x);
}


static HSD_CObj* current;
static HSD_ClassInfo* default_class;

static int CObjInit(HSD_Class* o);
static int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* cobjdesc);
static void CObjInfoInit(void);
static void CObjUpdateFunc(void* obj, u32 type, f32* val);
static void CObjRelease(HSD_Class* o);
static void CObjAmnesia(HSD_ClassInfo* info);

HSD_CObjInfo hsdCObj = { CObjInfoInit };

void HSD_CObjSetRoll(HSD_CObj* cobj, f32 roll);
void HSD_CObjSetupViewingMtx(HSD_CObj* cobj);

static inline void HSD_CObjRemoveAnimByFlags(HSD_CObj* cobj, u32 flags);
HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj);
HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj);

void HSD_CObjRemoveAnim(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return;
    }
    HSD_CObjRemoveAnimByFlags(cobj, 0x7FF);
}

static inline void HSD_CObjRemoveAnimByFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    HSD_AObjRemove(cobj->aobj);
    cobj->aobj = NULL;
    HSD_WObjRemoveAnim(HSD_CObjGetEyePositionWObj(cobj));
    HSD_WObjRemoveAnim(HSD_CObjGetInterestWObj(cobj));
}

void HSD_CObjAddAnim(HSD_CObj* cobj, HSD_CameraAnim* canim)
{
    if (cobj == NULL) {
        return;
    }
    if (canim == NULL) {
        return;
    }
    if (cobj->aobj != NULL) {
        HSD_AObjRemove(cobj->aobj);
    }
    cobj->aobj = HSD_AObjLoadDesc(canim->aobjdesc);
    HSD_WObjAddAnim(HSD_CObjGetEyePositionWObj(cobj), canim->eye_anim);
    HSD_WObjAddAnim(HSD_CObjGetInterestWObj(cobj), canim->interest_anim);
}

void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* position);
void HSD_CObjSetEyePosition(HSD_CObj* cobj, Vec3* position);
void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest);
void HSD_CObjSetInterest(HSD_CObj* cobj, Vec3* interest);
void HSD_CObjSetFov(HSD_CObj* cobj, f32 fov);
void HSD_CObjSetNear(HSD_CObj* cobj, f32 near);
void HSD_CObjSetFar(HSD_CObj* cobj, f32 far);

static void CObjUpdateFunc(void* obj, u32 type, f32* val)
{
    HSD_CObj* cobj = obj;
    Vec3 vec;

    if (cobj == NULL) {
        return;
    }

    switch (type) {
    case 1:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.x = *val;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 2:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.y = *val;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 3:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.z = *val;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 5:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = *val;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 6:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = *val;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 7:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = *val;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 9:
        HSD_CObjSetRoll(cobj, *val);
        break;
    case 10:
        HSD_CObjSetFov(cobj, *val);
        break;
    case 11:
        HSD_CObjSetNear(cobj, *val);
        break;
    case 12:
        HSD_CObjSetFar(cobj, *val);
        break;
    }
}

void HSD_CObjAnim(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return;
    }
    HSD_AObjInterpretAnim(cobj->aobj, cobj, (void*) HSD_COBJ_METHOD(cobj)->update);
    HSD_WObjInterpretAnim(cobj->eyepos);
    HSD_WObjInterpretAnim(cobj->interest);
}

void HSD_CObjReqAnim(HSD_CObj* cobj, f32 startframe)
{
    if (cobj == NULL) {
        return;
    }
    if (cobj == NULL) {
        return;
    }
    HSD_AObjReqAnim(cobj->aobj, startframe);
    HSD_WObjReqAnim(cobj->eyepos, startframe);
    HSD_WObjReqAnim(cobj->interest, startframe);
}

int HSD_CObjMakeProjectionMtx(HSD_CObj* cobj, Mtx44 mtx)
{
    int projection_type;

    current = cobj;
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        projection_type = GX_PERSPECTIVE;
        C_MTXPerspective(mtx, cobj->projection_param.perspective.fov,
                         cobj->projection_param.perspective.aspect, cobj->near,
                         cobj->far);
        break;
    case PROJ_FRUSTUM:
        projection_type = GX_PERSPECTIVE;
        C_MTXFrustum(mtx, cobj->projection_param.frustum.top,
                     cobj->projection_param.frustum.bottom,
                     cobj->projection_param.frustum.left,
                     cobj->projection_param.frustum.right, cobj->near, cobj->far);
        break;
    case PROJ_ORTHO:
        projection_type = GX_ORTHOGRAPHIC;
        C_MTXOrtho(mtx, cobj->projection_param.ortho.top,
                   cobj->projection_param.ortho.bottom,
                   cobj->projection_param.ortho.left,
                   cobj->projection_param.ortho.right, cobj->near, cobj->far);
        break;
    }
    return projection_type;
}

int HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up);
static inline bool HSD_CObjMtxIsDirty(HSD_CObj* cobj);
static inline void HSD_CObjClearFlags(HSD_CObj* cobj, u32 flags);
static inline void HSD_CObjSetFlags(HSD_CObj* cobj, u32 flags);

void HSD_CObjSetupViewingMtx(HSD_CObj* cobj)
{
    Vec3 eyepos;
    Vec3 up_vec;
    Vec3 interest;

    if (!(cobj->flags & 2) && HSD_CObjMtxIsDirty(cobj)) {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        if (HSD_CObjGetUpVector(cobj, &up_vec) == 0) {
            up_vec.x = 0.0f;
            up_vec.y = 1.0f;
            up_vec.z = 0.0f;
        }
        HSD_CObjGetInterest(cobj, &interest);
        C_MTXLookAt(cobj->view_mtx, &eyepos, &up_vec, &interest);
        HSD_WObjClearFlags(cobj->eyepos, 2);
        HSD_WObjClearFlags(cobj->interest, 2);
        HSD_CObjClearFlags(cobj, 0x40000000);
        HSD_CObjSetFlags(cobj, 0x80000000);
    }
}

int HSD_CObjSetCurrent(HSD_CObj* cobj)
{
    Mtx44 mtx;

    if (cobj == NULL) {
        return 0;
    }
    GXSetProjection(mtx, HSD_CObjMakeProjectionMtx(cobj, mtx));
    HSD_CObjSetupViewingMtx(cobj);
    return 1;
}

HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj)
{
    HSD_ASSERT(606, cobj);
    return cobj->interest;
}

HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj)
{
    HSD_ASSERT(630, cobj);
    return cobj->eyepos;
}

void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest)
{
    HSD_ASSERT(654, cobj);
    HSD_WObjGetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

void HSD_CObjSetInterest(HSD_CObj* cobj, Vec3* interest)
{
    HSD_ASSERT(666, cobj);
    HSD_WObjSetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    HSD_ASSERT(678, cobj);
    HSD_WObjGetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

void HSD_CObjSetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    HSD_ASSERT(690, cobj);
    HSD_WObjSetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}


static inline int HSD_CObjGetEyeVector(HSD_CObj* cobj, Vec3* eye)
{
    Vec3 eyepos;
    Vec3 interest;

    if (cobj == NULL || cobj->eyepos == NULL || cobj->interest == NULL) {
        return 0;
    }
    HSD_CObjGetEyePosition(cobj, &eyepos);
    HSD_CObjGetInterest(cobj, &interest);
    PSVECSubtract(&interest, &eyepos, eye);
    return vec_normalize_check(eye, eye) == 0;
}

f32 HSD_CObjGetEyeDistance(HSD_CObj* cobj)
{
    Vec3 position;
    Vec3 interest;
    Vec3 look_vector;

    if (cobj == NULL) {
        return 0.0f;
    }
    HSD_ASSERT(737, cobj->eyepos);
    HSD_ASSERT(738, cobj->interest);
    HSD_CObjGetEyePosition(cobj, &position);
    HSD_CObjGetInterest(cobj, &interest);
    PSVECSubtract(&interest, &position, &look_vector);
    return PSVECMag(&look_vector);
}

static f32 upvec2roll(HSD_CObj* cobj, Vec3* up)
{
    static Vec3 orig = { 0.0F, 0.0F, 0.0F };
    static Vec3 uy = { 0.0F, 1.0F, 0.0F };
    Vec3 v;
    Vec3 eye;
    Mtx vmtx;
    f32 dot;

    if (!HSD_CObjGetEyeVector(cobj, &eye)) {
        return 0.0f;
    }
    dot = 1.0f - fabsf(PSVECDotProduct(up, &eye));
    if (dot < FLT_MIN) {
        return 0.0f;
    }
    C_MTXLookAt(vmtx, &orig, &uy, &eye);
    PSMTXMultVecSR(vmtx, up, &v);
    return atan2f_check(-v.x, v.y);
}

static int roll2upvec(HSD_CObj* cobj, Vec3* up, f32 roll)
{
    Vec3 eye;
    Vec3 v0;
    Vec3 v1;
    Mtx m;

    if (!HSD_CObjGetEyeVector(cobj, &eye)) {
        return 0;
    }
    if (1.0 - fabsf(eye.y) < 0.0001) {
        v0.x = sqrtf(eye.y * eye.y + eye.z * eye.z);
        v0.y = eye.y * (-eye.x / v0.x);
        v0.z = eye.z * (-eye.x / v0.x);
    } else {
        v0.y = sqrtf(eye.x * eye.x + eye.z * eye.z);
        v0.x = eye.x * (-eye.y / v0.y);
        v0.z = eye.z * (-eye.y / v0.y);
    }
    PSMTXRotAxisRad(m, &eye, -roll);
    PSMTXMultVecSR(m, &v0, &v1);
    PSVECNormalize(&v1, up);
    return 1;
}

int HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up)
{
    if (cobj == NULL || up == NULL) {
        return 0;
    }
    if (cobj->flags & 1) {
        *up = cobj->u.up;
        return 1;
    }
    return roll2upvec(cobj, up, cobj->u.roll);
}

void HSD_CObjSetMtxDirty(HSD_CObj* cobj);

void HSD_CObjSetUpVector(HSD_CObj* cobj, Vec3* up)
{
    Vec3 v;

    if (!cobj || !up) {
        return;
    }
    if (cobj->flags & 1) {
        if (vec_normalize_check(up, &v) != 0) {
            OSReport("illegal up vector.");
            HSD_ASSERT(882, 0);
        }
        if (cobj->u.up.x != v.x || cobj->u.up.y != v.y || cobj->u.up.z != v.z) {
            HSD_CObjSetMtxDirty(cobj);
            cobj->u.up = v;
        }
    } else {
        HSD_CObjSetRoll(cobj, upvec2roll(cobj, up));
    }
}

void HSD_CObjSetMtxDirty(HSD_CObj* cobj)
{
    cobj->flags |= 0xC0000000;
}

static inline bool HSD_CObjMtxIsDirty(HSD_CObj* cobj)
{
    return (cobj->flags & 0x40000000) ||
           (cobj->eyepos != NULL && (cobj->eyepos->flags & 2)) ||
           (cobj->interest != NULL && (cobj->interest->flags & 2));
}

MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj* cobj);

void HSD_CObjGetViewingMtx(HSD_CObj* cobj, Mtx mtx)
{
    PSMTXCopy(HSD_CObjGetViewingMtxPtr(cobj), mtx);
}

MtxPtr HSD_CObjGetInvViewingMtxPtrDirect(HSD_CObj* cobj)
{
    if (cobj->flags & 0x80000000) {
        if (cobj->proj_mtx == NULL) {
            cobj->proj_mtx = HSD_MtxAlloc();
        }
        PSMTXInverse(cobj->view_mtx, *cobj->proj_mtx);
        HSD_CObjClearFlags(cobj, 0x80000000);
    }
    return *cobj->proj_mtx;
}

MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj* cobj)
{
    HSD_CObjSetupViewingMtx(cobj);
    return cobj->view_mtx;
}

void HSD_CObjSetRoll(HSD_CObj* cobj, f32 roll)
{
    Vec3 up;

    if (cobj == NULL) {
        return;
    }
    if (cobj->flags & 1) {
        roll2upvec(cobj, &up, roll);
        HSD_CObjSetUpVector(cobj, &up);
    } else {
        if (cobj->u.roll != roll) {
            HSD_CObjSetMtxDirty(cobj);
        }
        cobj->u.roll = roll;
    }
}

void HSD_CObjSetFov(HSD_CObj* cobj, f32 fov)
{
    if (cobj == NULL || cobj->projection_type != PROJ_PERSPECTIVE) {
        return;
    }
    cobj->projection_param.perspective.fov = fov;
}

void HSD_CObjSetAspect(HSD_CObj* cobj, f32 aspect)
{
    if (cobj == NULL || cobj->projection_type != PROJ_PERSPECTIVE) {
        return;
    }
    cobj->projection_param.perspective.aspect = aspect;
}

f32 HSD_CObjGetNear(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    return cobj->near;
}

void HSD_CObjSetNear(HSD_CObj* cobj, f32 near)
{
    if (cobj != NULL) {
        cobj->near = near;
    }
}

f32 HSD_CObjGetFar(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    return cobj->far;
}

void HSD_CObjSetFar(HSD_CObj* cobj, f32 far)
{
    if (cobj != NULL) {
        cobj->far = far;
    }
}

static inline void HSD_CObjSetScissor(HSD_CObj* cobj, Scissor* scissor)
{
    if (cobj != NULL) {
        cobj->scissor = *scissor;
    }
}

void HSD_CObjSetScissorx4(HSD_CObj* cobj, u16 left, u16 right, u16 top, u16 bottom)
{
    if (cobj == NULL) {
        return;
    }
    cobj->scissor.left = left;
    cobj->scissor.right = right;
    cobj->scissor.top = top;
    cobj->scissor.bottom = bottom;
}

static inline void HSD_CObjSetViewport(HSD_CObj* cobj, HSD_RectS16* viewport)
{
    if (cobj != NULL) {
        cobj->viewport.xmin = viewport->xmin;
        cobj->viewport.xmax = viewport->xmax;
        cobj->viewport.ymin = viewport->ymin;
        cobj->viewport.ymax = viewport->ymax;
    }
}

void HSD_CObjSetViewportfx4(HSD_CObj* cobj, f32 xmin, f32 xmax, f32 ymin, f32 ymax)
{
    if (cobj == NULL) {
        return;
    }
    cobj->viewport.xmin = xmin;
    cobj->viewport.xmax = xmax;
    cobj->viewport.ymin = ymin;
    cobj->viewport.ymax = ymax;
}

int HSD_CObjGetProjectionType(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return PROJ_PERSPECTIVE;
    }
    return cobj->projection_type;
}

void HSD_CObjSetProjectionType(HSD_CObj* cobj, u32 proj_type)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = proj_type;
}

void HSD_CObjSetPerspective(HSD_CObj* cobj, f32 fov, f32 aspect)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_PERSPECTIVE;
    cobj->projection_param.perspective.fov = fov;
    cobj->projection_param.perspective.aspect = aspect;
}

void HSD_CObjSetFrustum(HSD_CObj* cobj, f32 top, f32 bottom, f32 left, f32 right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_FRUSTUM;
    cobj->projection_param.frustum.top = top;
    cobj->projection_param.frustum.bottom = bottom;
    cobj->projection_param.frustum.left = left;
    cobj->projection_param.frustum.right = right;
}

void HSD_CObjSetOrtho(HSD_CObj* cobj, f32 top, f32 bottom, f32 left, f32 right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_ORTHO;
    cobj->projection_param.ortho.top = top;
    cobj->projection_param.ortho.bottom = bottom;
    cobj->projection_param.ortho.left = left;
    cobj->projection_param.ortho.right = right;
}

void HSD_CObjGetPerspective(HSD_CObj* cobj, f32* fov, f32* aspect)
{
    if (cobj == NULL || cobj->projection_type != PROJ_PERSPECTIVE) {
        return;
    }
    if (fov != NULL) {
        *fov = cobj->projection_param.perspective.fov;
    }
    if (aspect != NULL) {
        *aspect = cobj->projection_param.perspective.aspect;
    }
}

void HSD_CObjGetOrtho(HSD_CObj* cobj, f32* top, f32* bottom, f32* left, f32* right)
{
    if (cobj == NULL || cobj->projection_type != PROJ_ORTHO) {
        return;
    }
    if (top != NULL) {
        *top = cobj->projection_param.ortho.top;
    }
    if (bottom != NULL) {
        *bottom = cobj->projection_param.ortho.bottom;
    }
    if (left != NULL) {
        *left = cobj->projection_param.ortho.left;
    }
    if (right != NULL) {
        *right = cobj->projection_param.ortho.right;
    }
}

static inline void HSD_CObjSetFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj != NULL) {
        cobj->flags |= flags;
    }
}

static inline void HSD_CObjClearFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj != NULL) {
        cobj->flags &= ~flags;
    }
}

HSD_CObj* HSD_CObjGetCurrent(void)
{
    return current;
}

HSD_CObj* HSD_CObjAlloc(void)
{
    HSD_CObj* cobj = HSD_COBJ(
        hsdNew(default_class ? default_class : HSD_CLASS_INFO(&hsdCObj)));
    HSD_ASSERT(1842, cobj);
    return cobj;
}

static inline void CObjResetFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags = (cobj->flags & 0xC0000000) | (flags & ~0xC0000000);
}

static int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* desc)
{
    static Vec3 y_axis = { 0.0f, 1.0f, 0.0f };

    cobj->flags = desc->common.flags;
    CObjResetFlags(cobj, desc->common.flags);
    HSD_CObjSetViewport(cobj, &desc->common.viewport);
    HSD_CObjSetScissor(cobj, &desc->common.scissor);
    HSD_WObjInit(cobj->eyepos, desc->common.eyepos);
    HSD_WObjInit(cobj->interest, desc->common.interest);
    HSD_CObjSetNear(cobj, desc->common.nnear);
    HSD_CObjSetFar(cobj, desc->common.ffar);
    if (desc->common.flags & 1) {
        if (desc->common.up_vector != NULL) {
            HSD_CObjSetUpVector(cobj, desc->common.up_vector);
        } else {
            HSD_CObjSetUpVector(cobj, &y_axis);
        }
    } else {
        HSD_CObjSetRoll(cobj, desc->common.roll);
    }
    switch (desc->common.projection_type) {
    case PROJ_PERSPECTIVE:
        HSD_CObjSetPerspective(cobj, desc->perspective.fov,
                               desc->perspective.aspect);
        break;
    case PROJ_ORTHO:
        HSD_CObjSetOrtho(cobj, desc->ortho.top, desc->ortho.bottom,
                         desc->ortho.left, desc->ortho.right);
        break;
    case PROJ_FRUSTUM:
        HSD_CObjSetFrustum(cobj, desc->frustum.top, desc->frustum.bottom,
                           desc->frustum.left, desc->frustum.right);
        break;
    default:
        HSD_ASSERT(1888, 0);
        break;
    }
    return 0;
}

HSD_CObj* HSD_CObjLoadDesc(HSD_CObjDesc* desc)
{
    HSD_ClassInfo* info;
    HSD_CObj* cobj;

    if (desc != NULL) {
        if (desc->class_name == NULL ||
            (info = hsdSearchClassInfo(desc->class_name)) == NULL)
        {
            cobj = HSD_CObjAlloc();
        } else {
            cobj = hsdNew(info);
            HSD_ASSERT(1927, cobj);
        }
        HSD_COBJ_METHOD(cobj)->load(cobj, desc);
        return cobj;
    }
    return NULL;
}

static int CObjInit(HSD_Class* o)
{
    HSD_CObj* cobj;
    int status = HSD_OBJECT_PARENT_INFO(&hsdCObj)->init(o);
    if (status < 0) {
        return status;
    }
    cobj = HSD_COBJ(o);
    if (cobj != NULL) {
        HSD_CObjSetMtxDirty(cobj);
    }
    cobj->eyepos = HSD_WObjAlloc();
    cobj->interest = HSD_WObjAlloc();
    return 0;
}

static void CObjRelease(HSD_Class* o)
{
    HSD_CObj* cobj = HSD_COBJ(o);

    HSD_AObjRemove(cobj->aobj);
    HSD_WObjUnref(HSD_CObjGetEyePositionWObj(cobj));
    HSD_WObjUnref(HSD_CObjGetInterestWObj(cobj));
    if (cobj->proj_mtx != NULL) {
        HSD_MtxFree(cobj->proj_mtx);
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->release(o);
}

static void CObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdCObj)) {
        current = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->amnesia(info);
}

static void CObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdCObj), &hsdObj,
                     "sysdolphin_base_library", "hsd_cobj",
                     sizeof(HSD_CObjInfo), sizeof(HSD_CObj));

    HSD_CLASS_INFO(&hsdCObj)->init = CObjInit;
    HSD_CLASS_INFO(&hsdCObj)->release = CObjRelease;
    HSD_CLASS_INFO(&hsdCObj)->amnesia = CObjAmnesia;
    hsdCObj.load = CObjLoad;
    hsdCObj.update = CObjUpdateFunc;
}
