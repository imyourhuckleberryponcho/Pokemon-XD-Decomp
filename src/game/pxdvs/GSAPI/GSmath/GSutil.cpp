#include <dolphin/types.h>

extern "C" {

#include <libc/math.h>

f32 gCosTable[181];

f32 GSmathHalf(f32 x) { return x * 0.5f; }

void GSmathInitCosTable(void) {
    for (s32 i = 0; i < 181; i++) {
        gCosTable[i] = cos(0.017453292f * (0.5f * i));
    }
}

}
