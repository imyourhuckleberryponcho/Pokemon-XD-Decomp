#include <dolphin/types.h>

struct GSquat {
    GSquat(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}

    f32 x, y, z, w;
};

// The identity rotation.
GSquat zeroQuaternion(0.0f, 0.0f, 0.0f, 1.0f);
