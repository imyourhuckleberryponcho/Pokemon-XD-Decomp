#include <dolphin/types.h>

typedef struct FightWazaHitKakurituData {
    u8 kake;
    u8 waru;
} FightWazaHitKakurituData;

FightWazaHitKakurituData fight_waza_hit_kakuritu_data[] = {
    {0x21, 0x64},
    {0x24, 0x64},
    {0x2B, 0x64},
    {0x32, 0x64},
    {0x3C, 0x64},
    {0x4B, 0x64},
    {0x01, 0x01},
    {0x85, 0x64},
    {0xA6, 0x64},
    {0x02, 0x01},
    {0xE9, 0x64},
    {0x85, 0x32},
    {0x03, 0x01},
};

u32 fight_waza_hit_kakuritu_data_number = sizeof(fight_waza_hit_kakuritu_data) / sizeof(fight_waza_hit_kakuritu_data[0]);
