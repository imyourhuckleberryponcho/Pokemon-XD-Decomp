#include <dolphin/types.h>

typedef struct FightActionData {
    u16 kind;
    u8 unk2[2];
    u32 buff;
} FightActionData;

FightActionData fight_action_data_waza[] = {
    {0x0013, {0x00, 0x00}, 0x00000000},
    {0x0000, {0x00, 0x00}, 0x00000000},
};
