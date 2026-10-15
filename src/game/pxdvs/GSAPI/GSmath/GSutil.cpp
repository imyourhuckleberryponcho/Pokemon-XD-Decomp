#include <dolphin/types.h>

extern "C" {

#include <libc/math.h>

f32 gCosTable[181];

// Unknown function that was dead-stripped from the final link. It used 0.5f,
// which puts that constant first in .sdata2.
f32 GSmathHalf(f32 x) { return x * 0.5f; }

void GSmathInitCosTable(void) {
    for (s32 i = 0; i < 181; i++) {
        gCosTable[i] = cos(0.017453292f * (0.5f * i));
    }
}

}
