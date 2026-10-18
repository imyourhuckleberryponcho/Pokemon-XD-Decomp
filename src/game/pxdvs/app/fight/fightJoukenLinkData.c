#include <dolphin/types.h>

typedef struct FightJoukenLinkData {
    u8 joint;
    u8 unk1;
    u16 joukenDataId;
    u16 nextLinkDataId;
} FightJoukenLinkData;

FightJoukenLinkData fight_jouken_link_data[] = {
    {0x00, 0x00, 0x0000, 0x0000},
};

u32 fight_jouken_link_data_number = sizeof(fight_jouken_link_data) / sizeof(fight_jouken_link_data[0]);
