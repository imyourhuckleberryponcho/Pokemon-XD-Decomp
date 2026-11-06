#ifndef GAME_MENUWAZASTATUS_H
#define GAME_MENUWAZASTATUS_H
#include <dolphin/types.h>

struct MenuWazaStatusEntry {
    unsigned short* name;
    unsigned short* zokuseiName;
    u16 zokusei;
    u8 maxPp;
    u8 pp;
};

struct MenuWazaStatus {
    unsigned short* nickname;
    MenuWazaStatusEntry waza[4];
    u8 pad34[0xC];
    void* fightOutPokemon;
    u8 tuusin;
};

#ifdef __MWERKS__
#define MENU_WAZA_STATUS_SIZE 0x48
#else
#define MENU_WAZA_STATUS_SIZE sizeof(MenuWazaStatus)
#endif

#endif
