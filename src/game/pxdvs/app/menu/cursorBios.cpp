#include <dolphin/types.h>

struct CursorPos {
    s16 x;
    s16 y;
};

#pragma peephole off

static CursorPos _cursor[16];

// The original's two {-1, -1} initializer constants are laid out with SetPos's first,
// even though GetPos comes first in .text. Explicit constants reproduce that order.
static const CursorPos sSetPosInvalid = { -1, -1 };
static const CursorPos sGetPosInvalid = { -1, -1 };

extern "C" {

CursorPos cursorBiosGetPos(u16 index) {
    CursorPos pos = sGetPosInvalid;
    if (index >= 16) {
        return pos;
    }
    pos = _cursor[index];
    return pos;
}

CursorPos cursorBiosSetPos(u16 index, CursorPos newPos) {
    CursorPos pos = sSetPosInvalid;
    if (index >= 16) {
        return pos;
    }
    pos = _cursor[index];
    _cursor[index] = newPos;
    return pos;
}

void cursorBiosInit(void) {
    for (s32 i = 0; i < 16; i++) {
        _cursor[i].x = 0;
        _cursor[i].y = 0;
    }
}

}
