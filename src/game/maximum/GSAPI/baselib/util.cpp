#include <dolphin/types.h>
#include <dolphin/gx/GXStruct.h>

#pragma pool_strings off

extern "C" {

void __assert(const char* file, s32 line, const char* expr);

u32 HSD_Index2PosNrmMtx(u32 index) {
    switch (index) {
    case 0:
        return 0;
    case 1:
        return 3;
    case 2:
        return 6;
    case 3:
        return 9;
    case 4:
        return 12;
    case 5:
        return 15;
    case 6:
        return 18;
    case 7:
        return 21;
    case 8:
        return 24;
    case 9:
        return 27;
    }
    __assert("util.c", 132, "0");
    return 0;
}

u32 HSD_GetNbBits(u32 mask) {
    u32 count = 0;
    for (u32 i = 0; i < 32; i++) {
        if (mask & (1 << i)) {
            count++;
        }
    }
    return count;
}

void HSD_MulColor(GXColor* a, GXColor* b, GXColor* out) {
    out->r = (u32)a->r * b->r / 255;
    out->g = (u32)a->g * b->g / 255;
    out->b = (u32)a->b * b->b / 255;
    out->a = (u32)a->a * b->a / 255;
}

}
