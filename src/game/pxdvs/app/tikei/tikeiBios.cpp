#include <dolphin/types.h>

struct TikeiData {
    u8 zokuseiDataId;
    u8 unk1;
    u16 fightKoukaId;
    u16 wazaId;
    u8 unk6[6];
};

extern "C" {

extern TikeiData tikei_data[];
extern u32 tikei_data_number;

static inline TikeiData* tikeiDataBiosGetPtr(u16 id) {
    if (id > tikei_data_number) {
        return 0;
    }
    return &tikei_data[id];
}

u16 tikeiDataBiosGetWazaId(u16 id) {
    TikeiData* data = tikeiDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->wazaId;
}

u8 tikeiDataBiosGetZokuseiDataId(u16 id) {
    TikeiData* data = tikeiDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->zokuseiDataId;
}

u16 tikeiDataBiosGetFightKoukaId(u16 id) {
    TikeiData* data = tikeiDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->fightKoukaId;
}

}
