#include <dolphin/types.h>

typedef struct FightWazaCriticalData {
    u8 bunbo;
} FightWazaCriticalData;

FightWazaCriticalData fight_waza_critical_data[] = {
    {0x10},
    {0x08},
    {0x04},
    {0x03},
    {0x02},
};

u32 fight_waza_critical_data_number = sizeof(fight_waza_critical_data) / sizeof(fight_waza_critical_data[0]);
