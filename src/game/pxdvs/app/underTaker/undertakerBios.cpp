#include <dolphin/types.h>

struct UnderTakerPlace {
    u16 unk0;
    u16 flagValue;
    u32 msgID;
};

struct UnderTakerData {
    u8 unk0[0x18];
    u32 flagID;
    u8 unk1C[0x34 - 0x1C];
    UnderTakerPlace places[7];
};

extern "C" {
extern UnderTakerData* undertakerdata;
u32 GSflagGet(u32 flagID);
}

class underTakerBios {
public:
    static u32 getPlaceMsg();
};

u32 underTakerBios::getPlaceMsg() {
    u32 flag = GSflagGet(undertakerdata->flagID);
    if (undertakerdata->places[0].flagValue == flag) {
        return undertakerdata->places[0].msgID;
    }
    if (undertakerdata->places[1].flagValue == flag) {
        return undertakerdata->places[1].msgID;
    }
    if (undertakerdata->places[2].flagValue == flag) {
        return undertakerdata->places[2].msgID;
    }
    if (undertakerdata->places[3].flagValue == flag) {
        return undertakerdata->places[3].msgID;
    }
    if (undertakerdata->places[4].flagValue == flag) {
        return undertakerdata->places[4].msgID;
    }
    if (undertakerdata->places[5].flagValue == flag) {
        return undertakerdata->places[5].msgID;
    }
    if (undertakerdata->places[6].flagValue == flag) {
        return undertakerdata->places[6].msgID;
    }
    return 1;
}
