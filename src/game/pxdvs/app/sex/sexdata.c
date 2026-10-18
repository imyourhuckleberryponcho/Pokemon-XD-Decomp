#include <dolphin/types.h>

typedef struct SexData {
    u8 raitoKotei;
    u8 pad[3];
    u32 msgID;
} SexData;

SexData sex_data[] = {
    {0x00, {0}, 0xCE5},
    {0xFE, {0}, 0xCE6},
    {0xFF, {0}, 0xCE7},
};

u32 sex_data_number = sizeof(sex_data) / sizeof(sex_data[0]);
