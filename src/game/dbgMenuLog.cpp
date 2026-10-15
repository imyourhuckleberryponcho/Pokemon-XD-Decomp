#include <dolphin/types.h>
#include <dolphin/gx/GXStruct.h>

// Debug menu units were built without the peephole optimizer.
#pragma peephole off

struct WindowKeyInfo {
    u8 unk0[4];
    u16 trigger;
    u16 repeat;
};

struct Window {
    u8 unk0[0x1C];
    s32 layer;
};

extern "C" {

WindowKeyInfo* windowGetKeyInfo(void);
s32 windowGetParam(Window* window, s32 index);
void windowSetParam(Window* window, s32 index, s32 value);
void GSgfxZCompare(s32, s32);
void menuSubDrawTile(s32 layer, s32 x, s32 y, s32 w, s32 h, GXColor color);
s32 GSlogGetLineCount(void);
const char* GSlogGetLine(s32 line);
void GSprint(s32 layer, s32 x, s32 y, u32 color, const char* fmt, ...);
bool menuIsCheck(s32 menuID);
void menuClose(s32 menuID);
void menuOpenCustom(s32 menuID, ...);

static s32 _viewStartLine;
static u8 _calcStartLine;

// Nothing references these, but the original link kept them.
#pragma force_active on

s32 dbgMenuLogDraw(Window* window) {
    GXColor color = { 0, 0, 0, 0x80 };
    WindowKeyInfo* key = windowGetKeyInfo();
    s32 y;
    s32 lines;
    s32 height;
    s32 max;
    s32 i;

    if (key->trigger & 0x100) {
        s32 mode = windowGetParam(window, 0) + 1;
        if (mode >= 3) {
            mode = 0;
        }
        windowSetParam(window, 0, mode);
    }
    switch (windowGetParam(window, 0)) {
    case 0:
    default:
        lines = 10;
        height = 130;
        y = 325;
        break;
    case 1:
        lines = 10;
        height = 130;
        y = 39;
        break;
    case 2:
        lines = 1;
        height = 13;
        y = 442;
        break;
    }
    GSgfxZCompare(0, 7);
    menuSubDrawTile(window->layer, 15, y - 5, 605, height + 18, color);
    if (_calcStartLine) {
        _viewStartLine = GSlogGetLineCount() - lines;
        _calcStartLine = 0;
    }
    if (key->repeat & 1) {
        _viewStartLine--;
    }
    if (key->repeat & 2) {
        _viewStartLine++;
    }
    if (key->repeat & 8) {
        _viewStartLine += lines;
    }
    if (key->repeat & 4) {
        _viewStartLine -= lines;
    }
    max = GSlogGetLineCount() - lines;
    if (_viewStartLine < 0) {
        _viewStartLine = 0;
    }
    if (_viewStartLine > max) {
        _viewStartLine = max;
    }
    for (i = 0; i < lines; i++) {
        s32 line = i + _viewStartLine;
        if (line >= 0) {
            GSprint(window->layer, 20, y, 0xC0C0C0FF, GSlogGetLine(line));
        }
        y += 13;
    }
    return 0;
}

s32 dbgMenuLogChangeDisp(void) {
    if (menuIsCheck(0x22)) {
        menuClose(0x22);
    } else {
        _calcStartLine = 1;
        menuOpenCustom(0x22, 0, 0, 0, 1, 0);
    }
    return 0;
}

#pragma force_active reset

}
