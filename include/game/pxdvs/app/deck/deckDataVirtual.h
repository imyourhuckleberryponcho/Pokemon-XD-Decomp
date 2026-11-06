#ifndef GAME_DECKDATAVIRTUAL_H
#define GAME_DECKDATAVIRTUAL_H

#include <dolphin/types.h>

struct DeckDataVirtualItem {
    u8 num;
    u8 unk1;
    u16 id;
};

struct DeckDataVirtual {
    u8 unk0;
    u8 turnLimit;
    u8 pokemonNum;
    u8 unk3;
    u16 fightFloorDataId;
    u8 unk6[2];
    u32 allyDeck;
    u32 enemyDeck;
    u32 title;
    u32 explanation1;
    u32 explanation2;
    u32 flag;
    u8 allyJoutai[6];
    u8 enemyJoutai[6];
    DeckDataVirtualItem items[4];
};

#endif
