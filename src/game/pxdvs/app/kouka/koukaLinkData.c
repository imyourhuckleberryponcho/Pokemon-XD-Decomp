#include <dolphin/types.h>

typedef struct KoukaLinkData {
    u16 kouka[8];
} KoukaLinkData;

KoukaLinkData kouka_link_data[] = {
    {{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}},
};

u32 kouka_link_data_number = sizeof(kouka_link_data) / sizeof(kouka_link_data[0]);
