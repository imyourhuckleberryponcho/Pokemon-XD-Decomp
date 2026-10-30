#include <dolphin/types.h>
#pragma pool_strings off
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
enum GSgappFunc { GSgappFunc_draft_dummy };
struct GSgfxLayer;
struct GXColor { u8 r, g, b, a; };

extern "C" {

extern u32 _vtrState;
extern u32 _vtrBlockState;
extern u8 _vtrTexDisp;
extern u8 _vtrTexDispBorder;
extern u8 _vtrEnabled;

extern "C" {
struct GSgfxLayer {
    u8 _draft[1];
};

extern "C" {
void GSgappBlock(int id);
int GSgappCreate(s32 type, u8 priority, void* arg, GSgappFunc func);
void GSgappSetName(int id, const char* name);
void GSgappUnblock(int id);
int GSgfxLayerFindByID(int id);
void GSgfxRenderPause(void);
void GSgfxRenderUnpause(void);
void GSprimDraw2DQuad(GXColor color, f32 x, f32 y, f32 w, f32 h);
s32 GSprimDraw2DTexQuad(void* tex, GXColor color, f32, f32, f32, f32);
void GSprint(s32 layer, s32 x, s32 y, s32 color, const char* fmt, ...);
void* GSresGetResourceAllGroup(u32 id);
s32 GSthreadExecuteGroup(s32);
void GSvtrDisable(void);
void GSvtrEnable(void);
void GSvtrInit();
void GSvtrLoadTexture();
void GSvtrPause(void);
void GSvtrPlay(void);
s32 GSvtrRegisterGSgapp(u32 p0);
void GSvtrSlowPlay(void);
void* memset(void* dst, int val, size_t n);
extern s32 jtbl_1961;
extern s32 jtbl_1962;
}
extern "C++" {
void GSprimSetup2DRender(GSgfxLayer* layer);
static void _vtrTexDispFunc();
static void _vtrUpdateFunc(unsigned long p0, unsigned long p1);
}
static u8 _vtrGSgfxIsPaused;
static u32 _vtrGSgappHdlList[0xA];
static void* _vtrTex;
static u32 _vtrSlowPlayFrame;
static u32 _vtrGSgappCount;
void GSvtrSlowPlay() {
    _vtrState = 4;
    _vtrBlockState = 3;
    _vtrSlowPlayFrame = 0U;
}
}
void GSvtrSingleStep(void) {
    _vtrState = 0x3;
    _vtrBlockState = 0x3;
}
extern "C" {
void GSvtrPlay() {
    _vtrState = 2;
    _vtrBlockState = 3;
}
}

extern "C" {
void GSvtrPause() {
    _vtrState = 1;
    if ((s32) _vtrBlockState != 2) {
        _vtrBlockState = 1;
    }
}
}

u8 GSvtrGetInfoDisp(void) {
    return _vtrTexDisp;
}

void GSvtrSetInfoDisp(u8 a, u8 b) {
    _vtrTexDisp = a;
    _vtrTexDispBorder = b;
}

u32 GSvtrGetState(void) {
    return _vtrState;
}

u8 GSvtrIsActive(void) {
    return _vtrEnabled;
}
extern "C" {
void GSvtrDisable() {
    u32 i;
    _vtrState = 0;
    _vtrEnabled = 0;
    for (i = 0; i < _vtrGSgappCount; i++) {
        if (_vtrGSgappHdlList[i] != 0) {
            GSgappUnblock(_vtrGSgappHdlList[i]);
        }
    }
    if (_vtrGSgfxIsPaused == 1) {
        GSgfxRenderUnpause();
        _vtrGSgfxIsPaused = 0;
    }
}
}

extern "C" {
void GSvtrEnable() {
    _vtrEnabled = 1;
    _vtrState = 2;
    _vtrBlockState = 3;
}
}

extern "C" {
void GSvtrLoadTexture() {
    _vtrTex = GSresGetResourceAllGroup(0x0AB21200U);
}
}

extern "C" {
s32 GSvtrRegisterGSgapp(u32 handle) {
    u32 i;
    u32* list;
    if (_vtrGSgappCount + 1 >= 4) {
        return 0;
    }
    list = _vtrGSgappHdlList;
    for (i = 0; i < 4; i++, list++) {
        if (*list == 0) {
            *list = handle;
            _vtrGSgappCount++;
            return 1;
        }
    }
    return 0;
}
}

extern "C" {
void GSvtrInit() {
    _vtrEnabled = 0;
    _vtrState = 0;
    _vtrGSgappCount = 0U;
    _vtrTex = NULL;
    _vtrTexDisp = 1;
    memset((void*)(_vtrGSgappHdlList), 0, 0x10U);
    GSgappSetName(GSgappCreate(1, 0xFDU, (void*)((u8 *)0xA), (GSgappFunc)((s32) _vtrUpdateFunc)), (const char*)("GSvtr"));
}
}

extern "C++" {
static void _vtrUpdateFunc(unsigned long, unsigned long) {
    u8 pause;
    u32 i;
    u32* hdl;

    if (_vtrEnabled == 0) {
        return;
    }
    _vtrTexDispFunc();
    switch ((s32)_vtrBlockState) {
    case 0:
        pause = 0;
        break;
    case 1:
        _vtrBlockState = 2;
        for (i = 0, hdl = _vtrGSgappHdlList; i < _vtrGSgappCount; i++, hdl++) {
            if (*hdl != 0) {
                GSgappBlock(*hdl);
            }
        }
        pause = 1;
        break;
    case 2:
        pause = 1;
        break;
    case 3:
        i = 0;
        _vtrBlockState = 0;
        hdl = _vtrGSgappHdlList;
        for (; i < _vtrGSgappCount; i++, hdl++) {
            if (*hdl != 0) {
                GSgappUnblock(*hdl);
            }
        }
        pause = 0;
        break;
    }
    if (pause != _vtrGSgfxIsPaused) {
        if (pause == 1) {
            GSgfxRenderPause();
        } else {
            GSgfxRenderUnpause();
        }
        _vtrGSgfxIsPaused = pause;
    }
    switch ((s32)_vtrState) {
    case 2:
        break;
    case 3:
        if ((s32)_vtrBlockState != 2) {
            _vtrBlockState = 1;
        }
        break;
    case 4:
        {
            s32 state = 2;
            if ((s32)_vtrBlockState == 0) {
                state = 1;
            }
            _vtrBlockState = state;
        }
        if (++_vtrSlowPlayFrame >= 5) {
            _vtrBlockState = 3;
            _vtrSlowPlayFrame = 0;
        }
        break;
    }
    if ((s32)_vtrBlockState == 2) {
        GSthreadExecuteGroup(0xE38F910B);
        GSthreadExecuteGroup(0x175F4322);
    }
}
}

extern "C++" {
#pragma optimize_for_size on
static void _vtrTexDispFunc() {
    GXColor border = { 0xFF, 0x00, 0x00, 0xFF };
    GXColor white = { 0xFF, 0xFF, 0xFF, 0xFF };
    GSgfxLayer* layer;

    if (_vtrEnabled == 0) {
        return;
    }
    if (_vtrTexDisp == 0) {
        return;
    }
    if (_vtrTex == NULL) {
        return;
    }
    layer = (GSgfxLayer*)GSgfxLayerFindByID(7);
    if (layer == NULL) {
        return;
    }
    GSprimSetup2DRender(layer);
    if (M2C_FIELD(layer, s32 *, 0x1994) != 1) {
        M2C_FIELD(layer, s32 *, 0x1994) = 1;
        M2C_FIELD(layer, u8 **, 0x1990) = (u8*)layer + 0x1818 + M2C_FIELD(layer, s32 *, 0x1994) * 0xBC;
    }
    M2C_FIELD(layer, s32 *, 0x1644) = 1;
    M2C_FIELD(layer, s32 *, 0x1648) = 1;
    M2C_FIELD(layer, s32 *, 0x164C) = 0;
    M2C_FIELD(layer, s32 *, 0x1650) = 5;
    M2C_FIELD(layer, u32 *, 0x170C) |= 1;
    M2C_FIELD(layer, u32 *, 0x16A8) |= 0x40;
    M2C_FIELD(layer, u32 *, 0x17C4) |= 1;
    M2C_FIELD(layer, u32 *, 0x1760) |= 0x40;
    if (_vtrTexDispBorder != 0) {
        GSprimDraw2DQuad(border, 6.0f, 24.0f, 634.0f, 68.0f);
    }
    GSprimDraw2DTexQuad(_vtrTex, white, 12.0f, 28.0f, 628.0f, 64.0f);
    switch ((s32)_vtrState) {
    case 0:
        GSprint(M2C_FIELD(layer, s32 *, 0x28), 0x230, 0x2C, -1, "???");
        break;
    case 1:
        GSprint(M2C_FIELD(layer, s32 *, 0x28), 0x230, 0x2C, -1, "Pause");
        break;
    case 2:
        GSprint(M2C_FIELD(layer, s32 *, 0x28), 0x230, 0x2C, -1, "Play");
        break;
    case 3:
        switch ((s32)_vtrBlockState) {
        case 0:
        case 1:
            GSprint(M2C_FIELD(layer, s32 *, 0x28), 0x230, 0x2C, -1, "SStep");
            break;
        case 2:
        case 3:
            GSprint(M2C_FIELD(layer, s32 *, 0x28), 0x230, 0x2C, -1, "Pause");
            break;
        }
        break;
    case 4:
        GSprint(M2C_FIELD(layer, s32 *, 0x28), 0x230, 0x2C, -1, "Slow");
        break;
    }
}
#pragma optimize_for_size reset
}

}
