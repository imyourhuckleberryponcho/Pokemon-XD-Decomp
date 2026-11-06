#include <dolphin/types.h>
#include <game/miscTables.h>

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
    if (undertakerdata->places[0].id == flag) {
        return undertakerdata->places[0].msgID;
    }
    if (undertakerdata->places[1].id == flag) {
        return undertakerdata->places[1].msgID;
    }
    if (undertakerdata->places[2].id == flag) {
        return undertakerdata->places[2].msgID;
    }
    if (undertakerdata->places[3].id == flag) {
        return undertakerdata->places[3].msgID;
    }
    if (undertakerdata->places[4].id == flag) {
        return undertakerdata->places[4].msgID;
    }
    if (undertakerdata->places[5].id == flag) {
        return undertakerdata->places[5].msgID;
    }
    if (undertakerdata->places[6].id == flag) {
        return undertakerdata->places[6].msgID;
    }
    return 1;
}
