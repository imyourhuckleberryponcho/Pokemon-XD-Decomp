// Compiled as C with deferred inlining (see configure.py): functions come out in reverse
// source order. Ported from the Melee decomp's displayfunc.c (headers: include/hsd_ref).
// The original file name, used by the asserts.
#define HSD_FILE_NAME "displayfunc.c"

// XD's MSL <math.h> inlines (sqrtf with its NaN checks) instead of include/libc's math.h.
#include <dolphin/types.h>
#define _MATH_H_

extern f32 __float_nan[];
#define NAN (__float_nan[0])
double acos(double x);

inline float acosf(float x)
{
    return (float) acos(x);
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

#include <sysdolphin/baselib/displayfunc.h>

#include <string.h>

#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/objalloc.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/util.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#pragma pool_strings off

#define FLT_EPSILON 1.00000001335e-10F

static void (*sptcl_callback)(s32, s32, s32, HSD_JObj*) = NULL;


inline HSD_JObj* HSD_JObjFindSkeleton(HSD_JObj* jobj);
inline void HSD_JObjDispDObj(HSD_JObj* jobj, MtxPtr vmtx, HSD_TrspMask trsp_mask, u32 rendermode);
static void mkVBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst);
static void mkHBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst);
static void mkBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst);
static void mkRBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst);
void HSD_JObjMakePositionMtx(HSD_JObj* jobj, Mtx vmtx, Mtx pmtx);
MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx);
void HSD_JObjDispSub(HSD_JObj* jobj, MtxPtr vmtx, MtxPtr pmtx, HSD_TrspMask trsp_mask, u32 rendermode);
void HSD_JObjDisp(HSD_JObj* jobj, MtxPtr vmtx, HSD_TrspMask trsp_mask, u32 rendermode);
void HSD_JObjSetSPtclCallback(void (*func)(s32, s32, s32, HSD_JObj*));
void _HSD_DispForgetMemory(void* lo, void* hi);

inline HSD_JObj* HSD_JObjFindSkeleton(HSD_JObj* jobj)
{
    HSD_ASSERT(325, jobj);
    for (; jobj; jobj = jobj->parent) {
        if (jobj->flags & (JOBJ_SKELETON | JOBJ_SKELETON_ROOT)) {
            return jobj;
        }
    }
    return NULL;
}

inline void HSD_JObjDispDObj(HSD_JObj* jobj, MtxPtr vmtx, HSD_TrspMask trsp_mask,
                      u32 rendermode)
{
    HSD_CObj* cobj;
    Mtx mtx;

    if ((jobj->flags & JOBJ_HIDDEN) == 0) {
        u32 xlu_bits = jobj->flags & (trsp_mask << JOBJ_TRSP_SHIFT);
        if (xlu_bits != 0) {
            HSD_JObjSetupMatrix(jobj);

            if (vmtx == NULL) {
                cobj = HSD_CObjGetCurrent();
                vmtx = HSD_CObjGetViewingMtxPtrDirect(cobj);
            }

            HSD_JOBJ_METHOD(jobj)->make_pmtx(jobj, vmtx, mtx);
            if ((xlu_bits & JOBJ_OPA) != 0) {
                HSD_JOBJ_METHOD(jobj)->disp(jobj, vmtx, mtx, HSD_TRSP_OPA,
                                            rendermode);
            }
            if ((xlu_bits & JOBJ_TEXEDGE) != 0) {
                HSD_JOBJ_METHOD(jobj)->disp(jobj, vmtx, mtx, HSD_TRSP_TEXEDGE, rendermode);
            }
            if ((xlu_bits & JOBJ_XLU) != 0) {
                HSD_JOBJ_METHOD(jobj)->disp(jobj, vmtx, mtx, HSD_TRSP_XLU, rendermode);
            }
        }
    }
}

extern f32 __float_epsilon[];
#define EPS (__float_epsilon[0])

static void mkVBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Vec3 pos, x, y, z, yu;
    float sx, sz, mag;

    pos.x = src[0][3];
    pos.y = src[1][3];
    pos.z = src[2][3];
    y.x = src[0][1];
    y.y = src[1][1];
    y.z = src[2][1];
    VECScale(&y, &yu, 1.0F / (EPS + VECMag(&y)));
    sx = HSD_MtxColMag(src, 0);
    sz = HSD_MtxColMag(src, 2);

    if (jobj->flags & JOBJ_PBILLBOARD) {
        VECScale(&pos, &z, -1.0F / (EPS + VECMag(&pos)));
        VECCrossProduct(&yu, &z, &x);
    } else {
        Vec3 zv = { 0, 0, 1 };
        VECCrossProduct(&yu, &zv, &x);
    }

    mag = VECMag(&x);
    if (!(mag < EPS)) {
        sx /= mag;
        VECCrossProduct(&x, &yu, &z);
        sz /= EPS + VECMag(&z);
        dst[0][0] = sx * x.x;
        dst[1][0] = sx * x.y;
        dst[2][0] = sx * x.z;
        dst[0][1] = y.x;
        dst[1][1] = y.y;
        dst[2][1] = y.z;
        dst[0][2] = sz * z.x;
        dst[1][2] = sz * z.y;
        dst[2][2] = sz * z.z;
        dst[0][3] = pos.x;
        dst[1][3] = pos.y;
        dst[2][3] = pos.z;
    } else {
        MTXCopy(src, dst);
    }
}

static void mkHBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Vec3 pos, x, y, z, xu;
    float sy, sz, mag, horiz;

    pos.x = src[0][3];
    pos.y = src[1][3];
    pos.z = src[2][3];
    x.x = src[0][0];
    x.y = src[1][0];
    x.z = src[2][0];
    VECScale(&x, &xu, 1.0F / (EPS + VECMag(&x)));
    sy = HSD_MtxColMag(src, 1);
    sz = HSD_MtxColMag(src, 2);

    if (jobj->flags & JOBJ_PBILLBOARD) {
        horiz = sqrtf(pos.x * pos.x + pos.z * pos.z);
        y.y = EPS + horiz;
        y.x = -pos.y / y.y * pos.x;
        y.z = -pos.y / y.y * pos.z;
        VECNormalize(&y, &y);
    } else {
        y.x = 0.0F;
        y.y = 1.0F;
        y.z = 0.0F;
    }

    VECCrossProduct(&xu, &y, &z);
    mag = VECMag(&z);
    if (!(mag < EPS)) {
        sz /= mag;
        VECCrossProduct(&z, &xu, &y);
        sy /= EPS + VECMag(&y);
        dst[0][0] = x.x;
        dst[1][0] = x.y;
        dst[2][0] = x.z;
        dst[0][1] = sy * y.x;
        dst[1][1] = sy * y.y;
        dst[2][1] = sy * y.z;
        dst[0][2] = sz * z.x;
        dst[1][2] = sz * z.y;
        dst[2][2] = sz * z.z;
        dst[0][3] = pos.x;
        dst[1][3] = pos.y;
        dst[2][3] = pos.z;
    } else {
        MTXCopy(src, dst);
    }
}

static void mkBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Vec3 x, y, z, pos;
    float sx, sy, sz, mag;

    sz = HSD_MtxColMag(src, 2);
    sx = HSD_MtxColMag(src, 0);
    y.x = src[0][1];
    y.y = src[1][1];
    y.z = src[2][1];
    sy = VECMag(&y);
    pos.x = src[0][3];
    pos.y = src[1][3];
    pos.z = src[2][3];

    if (jobj->flags & JOBJ_PBILLBOARD) {
        mag = VECMag(&pos);
        VECScale(&pos, &z, -1.0F / (EPS + mag));
    } else {
        z.x = 0.0F;
        z.y = 0.0F;
        z.z = 1.0F;
    }

    VECScale(&y, &y, 1.0F / (sy + EPS));
    VECCrossProduct(&y, &z, &x);
    mag = VECMag(&x);
    if (!(mag < EPS)) {
        sx /= mag;
        VECCrossProduct(&z, &x, &y);
        sy /= EPS + VECMag(&y);
        dst[0][0] = sx * x.x;
        dst[1][0] = sx * x.y;
        dst[2][0] = sx * x.z;
        dst[0][1] = sy * y.x;
        dst[1][1] = sy * y.y;
        dst[2][1] = sy * y.z;
    } else {
        float scale;

        mag = sqrtf(z.x * z.x + z.z * z.z);
        scale = -z.y / (EPS + mag);
        y.x = z.x * scale;
        y.y = EPS + mag;
        y.z = z.z * scale;
        VECCrossProduct(&y, &z, &x);
        sx /= EPS + VECMag(&x);
        dst[0][0] = sx * x.x;
        dst[1][0] = sx * x.y;
        dst[2][0] = sx * x.z;
        dst[0][1] = y.x;
        dst[1][1] = y.y;
        dst[2][1] = y.z;
    }

    dst[0][2] = sz * z.x;
    dst[1][2] = sz * z.y;
    dst[2][2] = sz * z.z;
    dst[0][3] = pos.x;
    dst[1][3] = pos.y;
    dst[2][3] = pos.z;
}

static void mkRBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Mtx rot, scl;
    f32 sx, sy, sz;
    sx = HSD_MtxColMag(src, 0);
    sy = HSD_MtxColMag(src, 1);
    sz = HSD_MtxColMag(src, 2);
    MTXScale(scl, sx, sy, sz);
    MTXRotRad(rot, 'z', jobj->rotate.z);
    rot[0][3] = src[0][3];
    rot[1][3] = src[1][3];
    rot[2][3] = src[2][3];
    MTXConcat(rot, scl, dst);
}

void HSD_JObjMakePositionMtx(HSD_JObj* jobj, Mtx vmtx, Mtx pmtx)
{
    Mtx mtx;

    if (jobj->flags & JOBJ_BILLBOARD_FIELD) {
        MTXConcat(vmtx, jobj->mtx, mtx);
        switch (jobj->flags & JOBJ_BILLBOARD_FIELD) {
        case JOBJ_BILLBOARD:
            mkBillBoardMtx(jobj, mtx, pmtx);
            break;
        case JOBJ_VBILLBOARD:
            mkVBillBoardMtx(jobj, mtx, pmtx);
            break;
        case JOBJ_HBILLBOARD:
            mkHBillBoardMtx(jobj, mtx, pmtx);
            break;
        case JOBJ_RBILLBOARD:
            mkRBillBoardMtx(jobj, mtx, pmtx);
            break;
        default:
            HSD_Panic(HSD_FILE_NAME, 305, "unkown type of billboard.\n");
        }
    } else {
        MTXConcat(vmtx, jobj->mtx, pmtx);
    }
}

MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx)
{
    if (m->flags & JOBJ_SKELETON_ROOT) {
        return NULL;
    } else {
        HSD_JObj* x = HSD_JObjFindSkeleton(m);
        HSD_ASSERT(405, x);

        if (x == m) {
            MTXInverse(x->envelopemtx, mtx);
        } else if (x->flags & JOBJ_SKELETON_ROOT) {
            HSD_MtxInverseConcat(x->mtx, m->mtx, mtx);
        } else {
            Mtx n;
            MTXConcat(x->mtx, x->envelopemtx, n);
            HSD_MtxInverseConcat(n, m->mtx, mtx);
        }

        return mtx;
    }
}

void HSD_JObjDispSub(HSD_JObj* jobj, MtxPtr vmtx, MtxPtr pmtx,
                     HSD_TrspMask trsp_mask, u32 rendermode)
{
    HSD_DObj* dobj;
    u32 dobj_trsp;

    HSD_JObjSetCurrent(jobj);

    dobj_trsp = trsp_mask << DOBJ_TRSP_SHIFT;

    if (!(rendermode & RENDER_SHADOW)) {
        if (jobj->flags & JOBJ_SPECULAR) {
            HSD_LObjSetupSpecularInit(pmtx);
        }
    }

    HSD_PObjClearMtxMark(NULL, 0);
    for (dobj = jobj->u.dobj; dobj; dobj = dobj->next) {
        if (dobj->flags & DOBJ_HIDDEN) {
            continue;
        }

        if (dobj->flags & dobj_trsp) {
            HSD_DObjSetCurrent(dobj);
            HSD_DOBJ_METHOD(dobj)->disp(dobj, vmtx, pmtx, rendermode);
        }
    }
    HSD_DObjSetCurrent(NULL);
    HSD_JObjSetCurrent(NULL);
}

void HSD_JObjDisp(HSD_JObj* jobj, MtxPtr vmtx, HSD_TrspMask trsp_mask,
                  u32 rendermode)
{
    if (jobj != NULL) {
        if (union_type_dobj(jobj)) {
            HSD_JObjDispDObj(jobj, vmtx, trsp_mask, rendermode);
        } else if (union_type_ptcl(jobj) && sptcl_callback != NULL) {
            HSD_SList* sp;
            for (sp = jobj->u.ptcl; sp != NULL; sp = sp->next) {
                if ((((u32) sp->data) & 0x80000000) != 0) {
                    u32 bank = JOBJ_PTCL_BANK_MASK & ((u32) sp->data);
                    u32 offset = (((u32) sp->data) >> JOBJ_PTCL_OFFSET_SHIFT) &
                                 JOBJ_PTCL_OFFSET_MASK;
                    (*sptcl_callback)(0, bank, offset, jobj);
                }
                sp->data = (void*) ((u32) sp->data & JOBJ_PTCL_ACTIVE);
            }
        }
    }
}

void HSD_JObjSetSPtclCallback(void (*func)(s32, s32, s32, HSD_JObj*))
{
    sptcl_callback = func;
}

void _HSD_DispForgetMemory(void* lo, void* hi)
{
}
