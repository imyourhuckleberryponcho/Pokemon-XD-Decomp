#ifndef GAME_MENUTABLES_H
#define GAME_MENUTABLES_H

#include <dolphin/types.h>

struct MenuSe {
    u16 sndId[6];
};

struct WAZAOSHIE_DATA {
    u16 id;
    u16 pad2;
    u32 mission;
    u32 flag;
};

#endif
