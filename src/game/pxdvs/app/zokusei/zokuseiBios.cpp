#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/pxdvs/app/zokusei/zokuseiData.h>

extern "C" {

extern u32* zokusei_data_number;
extern ZokuseiData* zokusei_data;

PCRET(u16) zokuseiBiosGetSmallSpriteID(u16 id) {
    if (id >= *zokusei_data_number) {
        return 0;
    }
    return zokusei_data[id].smallSpriteID;
}

PCRET(u16) zokuseiBiosGetSpriteID(u16 id) {
    if (id >= *zokusei_data_number) {
        return 0;
    }
    return zokusei_data[id].spriteID;
}

PCRET(u8) zokuseiBiosGetWazaKind(u16 id) {
    if (id >= *zokusei_data_number) {
        return 0;
    }
    return zokusei_data[id].wazaKind;
}

u32 zokuseiBiosGetName(u16 id) {
    if (id >= *zokusei_data_number) {
        return 0;
    }
    return zokusei_data[id].name;
}

u16 zokuseiBiosGetWazaJoutai(u32 id, u32 target) {
    if (id >= *zokusei_data_number) {
        return 0;
    }
    if (target >= 18) {
        return 0;
    }
    return zokusei_data[id].wazaJoutai[target];
}

}
