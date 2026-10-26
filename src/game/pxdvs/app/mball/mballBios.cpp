#include <dolphin/types.h>

extern "C" {

extern u32* mball_data_number;
extern u16* mball_data;

u16 mballBiosGetSpriteID(u16 id) {
    if (id < *mball_data_number) {
        return mball_data[id];
    }
    return 0;
}

}
