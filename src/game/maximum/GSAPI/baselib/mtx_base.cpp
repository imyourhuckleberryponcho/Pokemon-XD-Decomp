// Compiled as C with deferred inlining (see configure.py): functions come out in reverse
// source order. Ported from the Melee decomp's mtx.c (headers: include/hsd_ref).
#define HSD_FILE_NAME "mtx.c"

// XD's HSD_MtxInverseConcat returns int; hide the header's void prototype.
#define HSD_MtxInverseConcat HSD_MtxInverseConcat_hdr
// Keep libc math.h out: its extern-inline sqrtf/sqrt would emit unused .sdata2 constants.
#define _MATH_H_
double sin(double x);
double cos(double x);
double __fabs(double x);
float sqrtf(float x);
#include <sysdolphin/baselib/mtx.h>
#undef HSD_MtxInverseConcat

#include <sysdolphin/baselib/debug.h>

#pragma pool_strings off

#undef sinf
#undef cosf
#undef asinf
#undef atan2f
#define sinf(x) ((f32) sin(x))
#define cosf(x) ((f32) cos(x))
#define asinf(x) ((f32) asin(x))
#define atan2f(y, x) ((f32) atan2(y, x))

#define EPSILON 0.0000000001f
#define FLOAT_MIN 1.1754943E-38f

extern f32 __float_epsilon[];

static inline f32 recipSafe(f32 x)
{
    if (x >= 0.0f) {
        return 1.0f / (x + __float_epsilon[0]);
    }
    return 1.0f / (x - __float_epsilon[0]);
}

Mtx HSD_identityMtx = { { 1.0F, 0.0F, 0.0F, 0.0F }, { 0.0F, 1.0F, 0.0F, 0.0F }, { 0.0F, 0.0F, 1.0F, 0.0F } };

static HSD_ObjAllocData vec_alloc_data;
static HSD_ObjAllocData mtx_alloc_data;

double asin(double x);
double atan2(double y, double x);

extern int __float_nan[];
extern int __float_min[];
#define XD_NAN (*(f32*) __float_nan)
#define XD_FLOAT_MIN (*(f32*) __float_min)

static inline int mtxFpClassify(f32 x)
{
    switch ((*(int*) &x) & 0x7f800000) {
    case 0x7f800000:
        if ((*(int*) &x) & 0x007fffff) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(int*) &x) & 0x007fffff) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

// MSL math.h inline sqrtf, inlined into this file.
static inline f32 mtxSqrtf(f32 x)
{
    static const f64 _half = .5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64) x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        return (f32) (x * guess);
    } else if (x < 0.0) {
        return XD_NAN;
    } else if (mtxFpClassify(x) == 1) {
        return XD_NAN;
    }
    return x;
}

static inline f32 calcVal(f32 x, f32 y)
{
    if (x == 0.0f) {
        return y >= 0.0f ? 1.5707963267948966f : -1.5707963267948966f;
    }
    return (f32) atan2(y, x);
}

static inline f32 mtxDeterminant(Mtx m)
{
    f32 det;

    det = m[2][0] * (m[0][1] * m[1][2]);
    det += m[2][2] * (m[0][0] * m[1][1]);
    det += m[2][1] * (m[0][2] * m[1][0]);
    det -= m[0][2] * (m[2][0] * m[1][1]);
    det -= m[2][2] * (m[1][0] * m[0][1]);
    det -= m[1][2] * (m[0][0] * m[2][1]);
    return det;
}

int HSD_MtxInverseConcat(Mtx inv, Mtx src, Mtx dst)
{
    f32 i02;
    f32 i11;
    f32 i10;
    f32 i01;
    f32 i00;
    f32 det;
    f32 i12;
    f32 i20;
    f32 i22;
    Mtx result;
    f32 i21;
    f32 tx;
    f32 tz;
    f32 ty;

    det = mtxDeterminant(inv);
    if (det == 0.0f) {
        return 0;
    }

    det = 1.0f / det;
    i00 = det * (inv[1][1] * inv[2][2] - inv[2][1] * inv[1][2]);
    i01 = det * -(inv[0][1] * inv[2][2] - inv[2][1] * inv[0][2]);
    i10 = det * -(inv[1][0] * inv[2][2] - inv[2][0] * inv[1][2]);
    i11 = det * (inv[0][0] * inv[2][2] - inv[2][0] * inv[0][2]);
    i12 = det * -(inv[0][0] * inv[1][2] - inv[1][0] * inv[0][2]);
    i02 = det * (inv[0][1] * inv[1][2] - inv[1][1] * inv[0][2]);
    i20 = det * (inv[1][0] * inv[2][1] - inv[2][0] * inv[1][1]);
    i21 = det * -(-(inv[2][0] * inv[0][1] - inv[0][0] * inv[2][1]));
    i22 = det * (inv[0][0] * inv[1][1] - inv[1][0] * inv[0][1]);

    tx = -(i02 * inv[2][3] - (-i00 * inv[0][3] - i01 * inv[1][3]));
    ty = -(i12 * inv[2][3] - (-i10 * inv[0][3] - i11 * inv[1][3]));
    tz = -(i22 * inv[2][3] - (-i20 * inv[0][3] - i21 * inv[1][3]));

    if (inv == dst || src == dst) {
        result[0][0] = i02 * src[2][0] + (i00 * src[0][0] + i01 * src[1][0]);
        result[0][1] = i02 * src[2][1] + (i00 * src[0][1] + i01 * src[1][1]);
        result[0][2] = i02 * src[2][2] + (i00 * src[0][2] + i01 * src[1][2]);
        result[1][3] = i12 * src[2][3] + (i10 * src[0][3] + i11 * src[1][3]) + ty;
        result[0][3] = i02 * src[2][3] + (i00 * src[0][3] + i01 * src[1][3]) + tx;
        result[2][3] = i22 * src[2][3] + (i20 * src[0][3] + i21 * src[1][3]) + tz;
        result[1][0] = i12 * src[2][0] + (i10 * src[0][0] + i11 * src[1][0]);
        result[1][1] = i12 * src[2][1] + (i10 * src[0][1] + i11 * src[1][1]);
        result[1][2] = i12 * src[2][2] + (i10 * src[0][2] + i11 * src[1][2]);
        result[2][0] = i22 * src[2][0] + (i20 * src[0][0] + i21 * src[1][0]);
        result[2][1] = i22 * src[2][1] + (i20 * src[0][1] + i21 * src[1][1]);
        result[2][2] = i22 * src[2][2] + (i20 * src[0][2] + i21 * src[1][2]);
        MTXCopy(result, dst);
    } else {
        dst[0][0] = i02 * src[2][0] + (i00 * src[0][0] + i01 * src[1][0]);
        dst[0][1] = i02 * src[2][1] + (i00 * src[0][1] + i01 * src[1][1]);
        dst[0][2] = i02 * src[2][2] + (i00 * src[0][2] + i01 * src[1][2]);
        dst[0][3] = i02 * src[2][3] + (i00 * src[0][3] + i01 * src[1][3]) + tx;
        dst[1][0] = i12 * src[2][0] + (i10 * src[0][0] + i11 * src[1][0]);
        dst[1][1] = i12 * src[2][1] + (i10 * src[0][1] + i11 * src[1][1]);
        dst[1][2] = i12 * src[2][2] + (i10 * src[0][2] + i11 * src[1][2]);
        dst[1][3] = i12 * src[2][3] + (i10 * src[0][3] + i11 * src[1][3]) + ty;
        dst[2][0] = i22 * src[2][0] + (i20 * src[0][0] + i21 * src[1][0]);
        dst[2][1] = i22 * src[2][1] + (i20 * src[0][1] + i21 * src[1][1]);
        dst[2][2] = i22 * src[2][2] + (i20 * src[0][2] + i21 * src[1][2]);
        dst[2][3] = i22 * src[2][3] + (i20 * src[0][3] + i21 * src[1][3]) + tz;
    }
    return 1;
}

void HSD_MtxGetRotation(Mtx m, Vec3* vec)
{
    f32 length0;
    f32 length1;
    f32 length2;
    f32 test;
    f32 angle;

    length0 = mtxSqrtf(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);
    if (!(length0 < XD_FLOAT_MIN)) {
        length1 = mtxSqrtf(m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1]);
        if (!(length1 < XD_FLOAT_MIN)) {
            length2 = mtxSqrtf(m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2]);
            if (!(length2 < XD_FLOAT_MIN)) {
                test = -m[2][0] / length0;
                if (test >= 1.0f) {
                    angle = 1.5707963267948966f;
                } else if (test <= -1.0f) {
                    angle = -1.5707963267948966f;
                } else {
                    angle = (f32) asin(test);
                }
                vec->y = angle;

                if ((f32) cos(vec->y) >= XD_FLOAT_MIN) {
                    f32 y = m[2][1] / length1;
                    f32 x = m[2][2] / length2;

                    vec->x = calcVal(x, y);
                    vec->z = calcVal(m[0][0], m[1][0]);
                    return;
                }

                vec->x = calcVal(m[1][1], m[0][1]);
                vec->z = 0.0f;
                return;
            }
        }
    }

    vec->x = 0.0f;
    vec->y = 0.0f;
    vec->z = 0.0f;
}

void HSD_MtxGetRotationMtx(Mtx m, Mtx out, char a, char b)
{
    Vec3 cx, cy, cz;
    switch (a) {
    case 'X':
    case 'x':
        HSD_MtxColVec(m, 0, &cx);
        VECNormalize(&cx, &cx);
        switch (b) {
        case 'Z':
        case 'z':
            HSD_MtxColVec(m, 2, &cz);
            VECNormalize(&cz, &cz);
            VECCrossProduct(&cz, &cx, &cy);
            VECCrossProduct(&cx, &cy, &cz);
            break;
        default:
            HSD_MtxColVec(m, 1, &cy);
            VECNormalize(&cy, &cy);
            VECCrossProduct(&cx, &cy, &cz);
            VECCrossProduct(&cz, &cx, &cy);
            break;
        }
        break;
    case 'Y':
    case 'y':
        HSD_MtxColVec(m, 1, &cy);
        VECNormalize(&cy, &cy);
        switch (b) {
        case 'X':
        case 'x':
            HSD_MtxColVec(m, 0, &cx);
            VECNormalize(&cx, &cx);
            VECCrossProduct(&cx, &cy, &cz);
            VECCrossProduct(&cy, &cz, &cx);
            break;
        default:
            HSD_MtxColVec(m, 2, &cz);
            VECNormalize(&cz, &cz);
            VECCrossProduct(&cy, &cz, &cx);
            VECCrossProduct(&cx, &cy, &cz);
            break;
        }
        break;
    default:
        HSD_MtxColVec(m, 2, &cz);
        VECNormalize(&cz, &cz);
        switch (b) {
        case 'Y':
        case 'y':
            HSD_MtxColVec(m, 1, &cy);
            VECNormalize(&cy, &cy);
            VECCrossProduct(&cy, &cz, &cx);
            VECCrossProduct(&cz, &cx, &cy);
            break;
        default:
            HSD_MtxColVec(m, 0, &cx);
            VECNormalize(&cx, &cx);
            VECCrossProduct(&cz, &cx, &cy);
            VECCrossProduct(&cy, &cz, &cx);
            break;
        }
        break;
    }
    HSD_MtxSetColVec(out, 0, &cx);
    HSD_MtxSetColVec(out, 1, &cy);
    HSD_MtxSetColVec(out, 2, &cz);
    out[0][3] = 0;
    out[1][3] = 0;
    out[2][3] = 0;
}

/// These parameters may not be right
void HSD_MtxGetTranslate(Mtx mat, Vec3* vec)
{
    vec->x = mat[0][3];
    vec->y = mat[1][3];
    vec->z = mat[2][3];
}

void HSD_MtxGetScale(Mtx m, Vec3* scale)
{
    Vec3 x;
    Vec3 y;
    Vec3 z;
    Vec3 projection;
    f32 x_sq;
    f32 y_sq;
    f32 z_sq;

    x.x = m[0][0];
    x.y = m[1][0];
    x.z = m[2][0];

    x_sq = PSVECSquareMag(&x);
    if (x_sq > EPSILON) {
        f32 x_inv_mag = mtxSqrtf(1.0f / x_sq);
        scale->x = 1.0f / x_inv_mag;
        PSVECScale(&x, &x, x_inv_mag);

        y.x = m[0][1];
        y.y = m[1][1];
        y.z = m[2][1];
        PSVECScale(&x, &projection, PSVECDotProduct(&x, &y));
        PSVECSubtract(&y, &projection, &y);

        y_sq = PSVECSquareMag(&y);
        if (y_sq > EPSILON) {
            f32 y_inv_mag = mtxSqrtf(1.0f / y_sq);
            scale->y = 1.0f / y_inv_mag;
            PSVECScale(&y, &y, y_inv_mag);

            z.x = m[0][2];
            z.y = m[1][2];
            z.z = m[2][2];
            PSVECScale(&y, &projection, PSVECDotProduct(&y, &z));
            PSVECSubtract(&z, &projection, &z);
            PSVECScale(&x, &projection, PSVECDotProduct(&x, &z));
            PSVECSubtract(&z, &projection, &z);

            z_sq = PSVECSquareMag(&z);
            if (z_sq > EPSILON) {
                f64 negative;

                scale->z = mtxSqrtf(z_sq);
                PSVECCrossProduct(&y, &z, &projection);
                if (PSVECDotProduct(&x, &projection) < 0.0) {
                    scale->x = (f32) (scale->x * (negative = -1.0));
                    scale->y = (f32) (scale->y * negative);
                    scale->z = (f32) (scale->z * negative);
                }
            } else {
                scale->z = 0.0f;
            }
        } else {
            scale->y = 0.0f;
            z.x = m[0][2];
            z.y = m[1][2];
            z.z = m[2][2];
            PSVECScale(&x, &projection, PSVECDotProduct(&x, &z));
            PSVECSubtract(&z, &projection, &z);

            z_sq = PSVECSquareMag(&z);
            if (z_sq > EPSILON) {
                scale->z = mtxSqrtf(z_sq);
            } else {
                scale->z = 0.0f;
            }
        }
    } else {
        scale->x = 0.0f;
        y.x = m[0][1];
        y.y = m[1][1];
        y.z = m[2][1];

        y_sq = PSVECSquareMag(&y);
        if (y_sq > EPSILON) {
            f32 y_inv_mag = mtxSqrtf(1.0f / y_sq);
            scale->y = 1.0f / y_inv_mag;
            PSVECScale(&y, &y, y_inv_mag);

            z.x = m[0][2];
            z.y = m[1][2];
            z.z = m[2][2];
            PSVECScale(&y, &projection, PSVECDotProduct(&y, &z));
            PSVECSubtract(&z, &projection, &z);
            scale->z = PSVECMag(&z);
        } else {
            scale->y = 0.0f;
            z.x = m[0][2];
            z.y = m[1][2];
            z.z = m[2][2];
            scale->z = PSVECMag(&z);
        }
    }
}

// Placeholders for two functions the linker stripped from the retail DOL: their double
// literals (-1.0 and 0.0) sit in .sdata2 ahead of the sqrt/epsilon constants.
f32 mtxStrippedFlip(f32 v)
{
    return (f32) (v * -1.0);
}

f32 mtxStrippedIsNegative(Vec3* a, Vec3* b)
{
    if (PSVECDotProduct(a, b) < 0.0) {
        return 1.0f;
    }
    return 0.0f;
}

void HSD_MkRotationMtx(Mtx arg0, Vec3* arg1)
{
    f32 sinX;
    f32 cosX;
    f32 sinY;
    f32 cosY;
    f32 sinZ;
    f32 cosZ;
    f32 temp1;
    f32 temp2;

    sinX = sinf(arg1->x);
    cosX = cosf(arg1->x);
    sinY = sinf(arg1->y);
    cosY = cosf(arg1->y);
    sinZ = sinf(arg1->z);
    cosZ = cosf(arg1->z);

    temp1 = sinX * sinY;
    arg0[0][0] = cosY * cosZ;
    arg0[1][0] = cosY * sinZ;
    arg0[2][0] = -sinY;
    temp2 = cosX * sinY;
    arg0[0][1] = (cosZ * temp1) - (cosX * sinZ);
    arg0[1][1] = (sinZ * temp1) + (cosX * cosZ);
    arg0[2][1] = sinX * cosY;
    arg0[0][2] = (cosZ * temp2) + (sinX * sinZ);
    arg0[1][2] = (sinZ * temp2) - (sinX * cosZ);
    arg0[2][2] = cosX * cosY;
    arg0[0][3] = 0;
    arg0[1][3] = 0;
    arg0[2][3] = 0;
}

void HSD_MtxSRT(Mtx m, Vec3* vec1, Vec3* vec2, Vec3* vec3, Vec3* vec4)
{
    f32 vec1z;
    f32 vec1x_2;
    f32 vec1y_2;
    f32 vec1z_2;
    f32 vec1x_1;
    f32 vec1y_1;
    f32 vec1z_1;
    f32 vec1x;
    f32 vec1y;

    f32 sinX = sinf(vec2->x);
    f32 cosX = cosf(vec2->x);
    f32 sinY = sinf(vec2->y);
    f32 cosY = cosf(vec2->y);
    f32 sinZ = sinf(vec2->z);
    f32 cosZ = cosf(vec2->z);

    vec1x_2 = vec1x_1 = vec1x = vec1->x;
    vec1y_2 = vec1y_1 = vec1y = vec1->y;
    vec1z_2 = vec1z_1 = vec1z = vec1->z;

    if (vec4 != NULL) {
        f32 temp1 = recipSafe(vec4->x);
        f32 temp2 = recipSafe(vec4->y);
        f32 temp3 = recipSafe(vec4->z);

        vec1y_2 *= vec4->y * temp1;
        vec1z_2 *= vec4->z * temp1;
        vec1x_1 *= vec4->x * temp2;
        vec1z_1 *= vec4->z * temp2;
        vec1x *= vec4->x * temp3;
        vec1y *= vec4->y * temp3;
    }

    m[0][0] = cosZ * (vec1x_2 * cosY);
    m[1][0] = sinZ * (vec1x_1 * cosY);
    m[2][0] = -vec1x * sinY;
    m[0][1] = vec1y_2 * ((cosZ * (sinX * sinY)) - (cosX * sinZ));
    m[1][1] = vec1y_1 * ((sinZ * (sinX * sinY)) + (cosX * cosZ));
    m[2][1] = cosY * (vec1y * sinX);
    m[0][2] = vec1z_2 * ((cosZ * (cosX * sinY)) + (sinX * sinZ));
    m[1][2] = vec1z_1 * ((sinZ * (cosX * sinY)) - (sinX * cosZ));
    m[2][2] = cosY * (vec1z * cosX);
    m[0][3] = vec3->x;
    m[1][3] = vec3->y;
    m[2][3] = vec3->z;
}

void HSD_MtxSRTQuat(Mtx arg0, Vec3* arg1, Quaternion* arg2, Vec3* arg3,
                    Vec3* arg4)
{
    Mtx temp;

    MTXScale(arg0, arg1->x, arg1->y, arg1->z);
    MTXQuat(temp, arg2);

    if (arg4 != NULL) {
        f32 rx = recipSafe(arg4->x);
        f32 ry = recipSafe(arg4->y);
        f32 rz = recipSafe(arg4->z);

        temp[0][1] = temp[0][1] * (arg4->y * rx);
        temp[0][2] = temp[0][2] * (arg4->y * rx);
        temp[1][0] = temp[1][0] * (arg4->x * ry);
        temp[1][2] = temp[1][2] * (arg4->z * ry);
        temp[2][0] = temp[2][0] * (arg4->x * rz);
        temp[2][1] = temp[2][1] * (arg4->y * rz);
    }

    MTXConcat(temp, arg0, arg0);
    arg0[0][3] = arg3->x;
    arg0[1][3] = arg3->y;
    arg0[2][3] = arg3->z;
}

/// might be a fakematch?
void HSD_MtxScaledAdd(Mtx arg0, Mtx arg1, Mtx arg2, f32 arg3)
{
    f32* arr0 = (&arg0[0][0]);
    f32* arr1 = (&arg1[0][0]);
    f32* arr2 = (&arg2[0][0]);

    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);

    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);

    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
}

void HSD_VecGetOrthogonal(Vec3* in, Vec3* out)
{
    Vec3 axis;
    if (in->x <= in->y) {
        if (in->x <= in->z) {
            axis.x = 1.0f; axis.y = 0.0f; axis.z = 0.0f;
            VECCrossProduct(&axis, in, out);
        } else {
            axis.x = 0.0f; axis.y = 0.0f; axis.z = 1.0f;
            VECCrossProduct(&axis, in, out);
        }
    } else if (in->y <= in->z) {
        axis.x = 0.0f; axis.y = 1.0f; axis.z = 0.0f;
        VECCrossProduct(&axis, in, out);
    } else {
        axis.x = 0.0f; axis.y = 0.0f; axis.z = 1.0f;
        VECCrossProduct(&axis, in, out);
    }
}

void* HSD_VecAlloc(void)
{
    void* vec = HSD_ObjAlloc(&vec_alloc_data);

    HSD_ASSERT(0x38c, vec);

    return vec;
}

void HSD_VecFree(void* arg0)
{
    if (arg0 != NULL) {
        HSD_ObjFree(&vec_alloc_data, arg0);
    }
}

void* HSD_MtxAlloc(void)
{
    void* mtx;

    mtx = HSD_ObjAlloc(&mtx_alloc_data);
    HSD_ASSERT(0x3ab, mtx);
    return mtx;
}

void HSD_MtxFree(void* arg0)
{
    if (arg0 != NULL) {
        HSD_ObjFree(&mtx_alloc_data, arg0);
    }
}

HSD_ObjAllocData* HSD_VecGetAllocData(void)
{
    return &vec_alloc_data;
}

void HSD_VecInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_VecGetAllocData(), sizeof(Vec), 4);
}

HSD_ObjAllocData* HSD_MtxGetAllocData(void)
{
    return &mtx_alloc_data;
}

void HSD_MtxInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_MtxGetAllocData(), sizeof(Mtx), 4);
}
