#include <dolphin/types.h>
#include "game/gc_fused.h"

struct GSquat {
    f32 x, y, z, w;
};

struct GSvec {
    GSvec(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

    f32 x, y, z;
};

extern "C" {
double asin(double x);
double atan(double x);
}

extern "C" {
GSvec xAxisVector(1.0f, 0.0f, 0.0f);
GSvec yAxisVector(0.0f, 1.0f, 0.0f);
GSvec zAxisVector(0.0f, 0.0f, 1.0f);
GSvec zeroVector(0.0f, 0.0f, 0.0f);
GSvec unitScaleVector(1.0f, 1.0f, 1.0f);
}

extern "C" {

void GSvecMakeFromQuat(GSvec* out, const GSquat* q) {
    f32 x = q->x;
    f32 y = q->y;
    f32 z = q->z;
    f32 w = q->w;
    f32 xx;
    f32 yy = y * y;
    xx = x * x;
    f32 zz = z * z;
    f32 ww = w * w;

    out->x = asin(-2.0f * (GC_FUSED(x, z) - w * y));
    out->y = atan(2.0f * (GC_FUSED(x, y) + w * z) / (ww + xx - yy - zz));
    out->z = atan(2.0f * (GC_FUSED(w, x) + y * z) / (zz + (ww - xx - yy)));
}

void GSvecTransformQuat(GSvec* out, const GSquat* q, const GSvec* v) {
    f32 vx;
    f32 d;
    f32 qz;
    f32 qw;
    f32 vy;
    f32 vz;
    f32 qx;
    f32 qy;
    vy = v->y;
    qy = q->y;
    vz = v->z;
    qx = q->x;
    vx = v->x;
    qz = q->z;
    qw = q->w;
    f32 a = GC_FUSED(vx, qw) + qy * vz - GC_FUSED(vy, qz);
    f32 b = GC_FUSED(vy, qw) + qz * vx - GC_FUSED(vz, qx);
    f32 c = GC_FUSED(vz, qw) + qx * vy - GC_FUSED(vx, qy);
    d = GC_FUSED(vx, qx) + qy * vy + GC_FUSED(vz, qz);

    out->x = GC_FUSED(a, qw) + qx * d + GC_FUSED(qy, c) - GC_FUSED(b, qz);
    out->y = GC_FUSED(b, qw) + qy * d + GC_FUSED(qz, a) - GC_FUSED(c, qx);
    out->z = GC_FUSED(c, qw) + qz * d + GC_FUSED(qx, b) - GC_FUSED(a, qy);
}

}
