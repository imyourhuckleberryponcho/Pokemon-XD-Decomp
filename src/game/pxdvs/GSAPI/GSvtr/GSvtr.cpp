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
enum GXColor { GXColor_draft_dummy };

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
s32 GSprimDraw2DTexQuad(u32, s32*, f32, f32, f32, f32);
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
    u32 *var_r31;
    u32 temp_r3;
    u32 var_r30;

    var_r31 = _vtrGSgappHdlList;
    var_r30 = 0U;
    _vtrState = 0;
    _vtrEnabled = 0;
    while (var_r30 < (u32) _vtrGSgappCount) {
        temp_r3 = *var_r31;
        if (temp_r3 != 0) {
            GSgappUnblock((s32) temp_r3);
        }
        var_r30 += 1;
        var_r31 += 4;
    }
    if ((u8) _vtrGSgfxIsPaused == 1) {
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
s32 GSvtrRegisterGSgapp(u32 p0) {
    u32 *var_r5;
    s32 var_ctr;

    if ((u32) (_vtrGSgappCount + 1) >= 4U) {
        return 0;
    }
    var_r5 = _vtrGSgappHdlList;
    var_ctr = 4;
loop_3:
    if ((u32) *var_r5 == 0) {
        *var_r5 = p0;
        _vtrGSgappCount += 1;
        return 1;
    }
    var_r5 += 4;
    var_ctr -= 1;
    if (var_ctr == 0) {
        return 0;
    }
    goto loop_3;
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
static void _vtrUpdateFunc(unsigned long p0, unsigned long p1) {
    enum TsE { TsE0 };
    s32 saved_reg_r30;
    s32 var_r4;
    u32 *var_r30_3;
    u32 *var_r31;
    u32 temp_r0;
    enum TsE temp_r3;
    u32 temp_r3_2;
    u32 var_r30_2;
    u32 var_r31_2;
    u8 var_r30;

    var_r30 = saved_reg_r30;
    if ((u8) _vtrEnabled != 0) {
        _vtrTexDispFunc();
        switch ((s32) _vtrBlockState) {
        case 0:
            var_r30 = 0;
            break;
        case 1:
            _vtrBlockState = 2;
            var_r31 = _vtrGSgappHdlList;
            var_r30_2 = 0U;
            while (var_r30_2 < (u32) _vtrGSgappCount) {
                temp_r3 = (enum TsE)(*var_r31);
                if (temp_r3 != 0) {
                    GSgappBlock((s32) temp_r3);
                }
                var_r30_2 += 1;
                var_r31 += 4;
            }
            var_r30 = 1;
            break;
        case 2:
            var_r30 = 1;
            break;
        case 3:
            var_r31_2 = 0U;
            _vtrBlockState = 0;
            var_r30_3 = _vtrGSgappHdlList;
            while (var_r31_2 < (u32) _vtrGSgappCount) {
                temp_r3_2 = *var_r30_3;
                if (temp_r3_2 != 0) {
                    GSgappUnblock((s32) temp_r3_2);
                }
                var_r30_3 += 4;
                var_r31_2 += 1;
            }
            var_r30 = 0;
            break;
        }
        if (var_r30 != (u8) _vtrGSgfxIsPaused) {
            if (var_r30 == 1) {
                GSgfxRenderPause();
            } else {
                GSgfxRenderUnpause();
            }
            _vtrGSgfxIsPaused = var_r30;
        }
        switch ((s32) _vtrState) {
        case 3:
            if ((s32) _vtrBlockState != 2) {
                _vtrBlockState = 1;
            }
            break;
        case 4:
            var_r4 = 2;
            if ((s32) _vtrBlockState == 0) {
                var_r4 = 1;
            }
            _vtrBlockState = var_r4;
            temp_r0 = _vtrSlowPlayFrame + 1;
            _vtrSlowPlayFrame = temp_r0;
            if (temp_r0 >= 5U) {
                _vtrBlockState = 3;
                _vtrSlowPlayFrame = 0U;
            }
            break;
        }
        if ((s32) _vtrBlockState == 2) {
            GSthreadExecuteGroup(-0x1C706EF5);
            GSthreadExecuteGroup(0x175F4322);
        }
    }
}
}

extern "C++" {
#pragma optimize_for_size on
static void _vtrTexDispFunc() {
    volatile s32 sp14;
    volatile s32 sp10;
    s32 spC;
    s32 sp8;
    f32 temp_f1;
    s32 temp_r3;

    sp14 = jtbl_1961;
    sp10 = jtbl_1962;
    if ((u8) _vtrEnabled != 0) {
        if ((u8) _vtrTexDisp == 0) {
            return;
        }
        if (((u8 *) _vtrTex != NULL) && (temp_r3 = GSgfxLayerFindByID(7), ((temp_r3 == 0) == 0))) {
            GSprimSetup2DRender((GSgfxLayer*)((GSgfxLayer *) temp_r3));
            if ((s32) M2C_FIELD(temp_r3, s32 *, 0x1994) != 1) {
                M2C_FIELD(temp_r3, s32 *, 0x1994) = 1;
                M2C_FIELD(temp_r3, s32 *, 0x1990) = (s32) ((u8*)temp_r3 + 0x1818 + M2C_FIELD(temp_r3, s32 *, 0x1994) * 0xBC);
            }
            M2C_FIELD(temp_r3, s32 *, 0x1644) = 1;
            M2C_FIELD(temp_r3, s32 *, 0x1648) = 1;
            M2C_FIELD(temp_r3, s32 *, 0x164C) = 0;
            M2C_FIELD(temp_r3, s32 *, 0x1650) = 5;
            M2C_FIELD(temp_r3, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x170C) | 1);
            M2C_FIELD(temp_r3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(temp_r3, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x17C4) | 1);
            M2C_FIELD(temp_r3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x1760) | 0x40);
            if ((u8) _vtrTexDispBorder != 0) {
                spC = sp14;
                GSprimDraw2DQuad((GXColor)((s32) &spC), 6.0f, 24.0f, 634.0f, 68.0f);
            }
            sp8 = sp10;
            temp_f1 = M2C_BITWISE(f32, GSprimDraw2DTexQuad((u32) _vtrTex, &sp8, 12.0f, 28.0f, 628.0f, 64.0f));
            switch ((s32) _vtrState) {
            case 0:
                GSprint(M2C_FIELD(temp_r3, s32 *, 0x28), 0x230, 0x2C, -1, (const char*)("???"), temp_f1);
                return;
            case 1:
                GSprint(M2C_FIELD(temp_r3, s32 *, 0x28), 0x230, 0x2C, -1, (const char*)("Pause"), temp_f1);
                return;
            case 2:
                GSprint(M2C_FIELD(temp_r3, s32 *, 0x28), 0x230, 0x2C, -1, (const char*)("Play"), temp_f1);
                return;
            case 3:
                if ((s32) _vtrBlockState < 2) {
                    if ((s32) _vtrBlockState < 0) {
                        return;
                    }
                    GSprint(M2C_FIELD(temp_r3, s32 *, 0x28), 0x230, 0x2C, -1, (const char*)("SStep"), temp_f1);
                    return;
                }
                if ((s32) _vtrBlockState < 4) {
                    GSprint(M2C_FIELD(temp_r3, s32 *, 0x28), 0x230, 0x2C, -1, (const char*)("Pause"), temp_f1);
                    return;
                }
                break;
            case 4:
                GSprint(M2C_FIELD(temp_r3, s32 *, 0x28), 0x230, 0x2C, -1, (const char*)("Slow"), temp_f1);
                break;
            }
        }
    }
}
#pragma optimize_for_size reset
}

}
