#include <dolphin/types.h>

struct RibbonData {
    u32 unk0;
    u32 msgID;
};

extern "C" {

extern u32* ribbon_data_number;
extern RibbonData* ribbon_data;

u32 getRibbonMsgID(u32 id) {
    if (*ribbon_data_number <= id) {
        return 0;
    }
    return ribbon_data[id].msgID;
}

u32 getRibbonCnt(void) { return *ribbon_data_number; }

}
