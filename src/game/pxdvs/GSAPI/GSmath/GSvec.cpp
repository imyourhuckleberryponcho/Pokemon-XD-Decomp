#include <dolphin/types.h>

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

GSvec xAxisVector(1.0f, 0.0f, 0.0f);
GSvec yAxisVector(0.0f, 1.0f, 0.0f);
GSvec zAxisVector(0.0f, 0.0f, 1.0f);
GSvec zeroVector(0.0f, 0.0f, 0.0f);
GSvec unitScaleVector(1.0f, 1.0f, 1.0f);

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

    out->x = asin(-2.0f * (x * z - w * y));
    out->y = atan(2.0f * (x * y + w * z) / (ww + xx - yy - zz));
    out->z = atan(2.0f * (w * x + y * z) / (zz + (ww - xx - yy)));
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
    f32 a = vx * qw + qy * vz - vy * qz;
    f32 b = vy * qw + qz * vx - vz * qx;
    f32 c = vz * qw + qx * vy - vx * qy;
    d = vx * qx + qy * vy + vz * qz;

    out->x = a * qw + qx * d + qy * c - b * qz;
    out->y = b * qw + qy * d + qz * a - c * qx;
    out->z = c * qw + qz * d + qx * b - a * qy;
}

}
