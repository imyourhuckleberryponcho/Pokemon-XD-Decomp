#include <dolphin/types.h>

struct GSgfxCol {
    u8 r, g, b, a;
};

extern "C" {
inline GSgfxCol* GSgfxPerfColorToGSgfxCol(u32 color) {
    static GSgfxCol c;
    c.r = color >> 24;
    c.g = color >> 16;
    c.b = color >> 8;
    c.a = color;
    return &c;
}
}

extern "C" void characterInit(void) {}
