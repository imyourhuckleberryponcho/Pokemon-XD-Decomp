#include <dolphin/types.h>

struct GSgfxCol {
    u8 r, g, b, a;
};

extern "C" {
// From the precompiled GS header (only its function-local static is emitted here). The body is
// inferred from its inlined use in layer.cpp (byte stores, then the word is read back).
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
