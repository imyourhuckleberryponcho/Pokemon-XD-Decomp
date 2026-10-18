#include <dolphin/types.h>

typedef struct FightKoukaData {
    u16 fightJoukenDataId;
    u16 fightTargetDataId;
    u16 koukaDataId;
} FightKoukaData;

FightKoukaData fight_kouka_data[] = {
    {0x0002, 0x0000, 0x0000},
    {0x0006, 0x0001, 0x0002},
};

u32 fight_kouka_data_number = sizeof(fight_kouka_data) / sizeof(fight_kouka_data[0]);
