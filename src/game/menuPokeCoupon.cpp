#include <dolphin/types.h>

#pragma pool_strings off

extern "C" {

void menuShopOpen(s32 shopID);
void GSfloorChange(s32 floorID);
void __assert(const char* file, s32 line, const char* expr);

enum PokeCouponRefer {
    POKECOUPONREFER_INVALID = -1,
    POKECOUPONREFER_0,
    POKECOUPONREFER_1,
};

struct MenuPokeCouponWork {
    PokeCouponRefer m_eRefer;
};

static MenuPokeCouponWork _menuPokeCouponWork = { POKECOUPONREFER_INVALID };


#pragma force_active on

void menuPokeCouponExit(void) { _menuPokeCouponWork.m_eRefer = POKECOUPONREFER_INVALID; }

void menuPokeCouponMain(void) {
    switch (_menuPokeCouponWork.m_eRefer) {
    case POKECOUPONREFER_0:
        menuShopOpen(9);
        break;
    case POKECOUPONREFER_1:
        menuShopOpen(10);
        break;
    }
    GSfloorChange(0x395);
}

void menuPokeCouponInit(void) {
    if (POKECOUPONREFER_INVALID == _menuPokeCouponWork.m_eRefer) {
        __assert("menuPokeCoupon.c", 60, "POKECOUPONREFER_INVALID != _menuPokeCouponWork.m_eRefer");
    }
}

#pragma force_active reset

}
