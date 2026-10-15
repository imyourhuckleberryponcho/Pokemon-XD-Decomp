#include <dolphin/types.h>

struct TenkouData {
    u8 solarFlag;
    u8 unk1[7];
    u32 fightInitMsgId;
    u8 unkC[0xC];
};

extern "C" {

extern TenkouData tenkou_data[];
extern u32 tenkou_data_number;

static inline TenkouData* tenkouDataBiosGetPtr(u16 id) {
    if (id > tenkou_data_number) {
        return 0;
    }
    return &tenkou_data[id];
}

u32 tenkouDataBiosGetFightInitMsgId(u16 id) {
    TenkouData* data = tenkouDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->fightInitMsgId;
}

bool tenkouDataBiosGetSolarFlag(u16 id) {
    TenkouData* data = tenkouDataBiosGetPtr(id);
    if (data == NULL) {
        return false;
    }
    return data->solarFlag != 0;
}

}
