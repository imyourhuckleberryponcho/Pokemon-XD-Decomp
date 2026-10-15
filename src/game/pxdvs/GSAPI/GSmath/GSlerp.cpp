#include <dolphin/mtx.h>

extern "C" {

void GSlerpGetLinearInterpolationVector(Vec* out, Vec* a, Vec* b, f32 t) {
    if (t <= 0.0f) {
        out->x = a->x;
        out->y = a->y;
        out->z = a->z;
    } else if (t >= 1.0f) {
        out->x = b->x;
        out->y = b->y;
        out->z = b->z;
    } else {
        PSVECSubtract(b, a, out);
        PSVECScale(out, out, t);
        PSVECAdd(out, a, out);
    }
}

f32 GSlerpGetLinearInterpolationFloat(f32 a, f32 b, f32 t) {
    if (t <= 0.0f) {
        return a;
    }
    if (t >= 1.0f) {
        return b;
    }
    return t * (b - a) + a;
}

}
