#include <dolphin/types.h>

#pragma peephole off

extern "C" {

s32 menuOpen(s32 menuID, s32);
void menuClose(s32 menuID);
void menuCBDebug_SkipAGBConnection(u8 skip);

volatile s32 dbgMenuGBAAddCoupon_value;
volatile s32 dbgMenuGBAResetCoupon_on;
volatile s32 dbgMenuGBASetClearFlag_on;
volatile s32 dbgMenuGBAClearCouponFlag_on;

#pragma force_active on

s32 dbgMenuGBAClearCouponFlag(void) {
    dbgMenuGBAClearCouponFlag_on++;
    dbgMenuGBASetClearFlag_on = 0;
    return 0;
}

s32 dbgMenuGBASetClearFlag(void) {
    dbgMenuGBASetClearFlag_on++;
    return 0;
}

s32 dbgMenuGBAResetCoupon(void) {
    dbgMenuGBAResetCoupon_on++;
    dbgMenuGBAAddCoupon_value = 0;
    return 0;
}

s32 dbgMenuGBAAddCoupon(void) {
    s32 value = menuOpen(2, 1);
    menuClose(2);
    if (value >= 0) {
        dbgMenuGBAAddCoupon_value += value;
    }
    return 0;
}

s32 dbgToolBattleDebugSetAGBConnectionMode(s32, s32 mode) {
    menuCBDebug_SkipAGBConnection(mode == 0);
    return 0;
}

#pragma force_active reset

}
