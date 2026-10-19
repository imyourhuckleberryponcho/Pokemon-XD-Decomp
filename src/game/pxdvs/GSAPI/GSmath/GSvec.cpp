// WIP (NonMatching): GSvecTransformQuat register/operand order differs (permuter best 425).
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

// Quaternion to Euler angles (radians).
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

// Rotates v by q (q * v * conj(q)).
void GSvecTransformQuat(GSvec* out, const GSquat* q, const GSvec* v) {
    f32 qy = q->y;
    f32 vx = v->x;
    f32 qw = q->w;
    f32 qz = q->z;
    f32 vy = v->y;
    f32 qx = q->x;
    f32 vz = v->z;
    f32 b = qz * vx + vy * qw - vz * qx;
    f32 c = qx * vy + vz * qw - vx * qy;
    f32 d = qy * vy + vx * qx + vz * qz;
    f32 a = qy * vz + vx * qw - vy * qz;

    out->x = qx * d + a * qw + qy * c - b * qz;
    out->y = qy * d + b * qw + qz * a - c * qx;
    out->z = qz * d + c * qw + qx * b - a * qy;
}

}
