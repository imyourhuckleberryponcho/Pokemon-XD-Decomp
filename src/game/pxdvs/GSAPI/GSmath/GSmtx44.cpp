#include <dolphin/mtx.h>

extern "C" {

void GSmtx44Perspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f) {
    C_MTXPerspective(m, fovY, aspect, n, f);
}

void GSmtx44Ortho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    C_MTXOrtho(m, t, b, l, r, n, f);
}

}
