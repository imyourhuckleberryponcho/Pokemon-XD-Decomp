#include <dolphin/types.h>

struct ZokuseiData {
    u8 wazaKind;
    u8 unk1;
    u16 spriteID;
    u16 smallSpriteID;
    u8 unk6[2];
    u32 name;
    u16 wazaJoutai[18];
};

extern "C" {

extern u32* zokusei_data_number;
extern ZokuseiData* zokusei_data;

u16 zokuseiBiosGetSmallSpriteID(u16 id) {
    if (id >= *zokusei_data_number) {
        return 0;
    }
    return zokusei_data[id].smallSpriteID;
}

u16 zokuseiBiosGetSpriteID(u16 id) {
    if (id >= *zokusei_data_number) {
        return 0;
    }
    return zokusei_data[id].spriteID;
}

u8 zokuseiBiosGetWazaKind(u16 id) {
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
