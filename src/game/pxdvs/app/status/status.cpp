#include <dolphin/types.h>

extern "C" {

s32 gamedataSetStatus(void* p, u16 b, s32 value);
s32 pcboxSetStatus(void* p, u16 b, s32 value);
s32 heroSetStatus(void* p, u16 b, s32 value);
s32 itemSetStatus(void* p, u16 a, u16 b, void* target, s32 value);
s32 pokemonSetStatus(void* p, u16 a, u16 b, void* target, s32 value);
s32 wazaSetStatus(void* p, u16 a, u16 b, void* target, s32 value);
s32 fightFloorSetStatus(void* p, u16 a, u16 b, void* target, s32 value);
s32 fightSideSetStatus(void* p, u16 a, u16 b, void* target, s32 value);
s32 fightTrainerSetStatus(void* p, u16 a, u16 b, void* target, s32 value);

s32 gamedataGetStatus(void* p, u16 b);
s32 pcboxGetStatus(void* p, u16 b, u16 c);
s32 heroGetStatus(void* p, u16 b, u16 c);
s32 itemGetStatus(void* p, u16 a, u16 b, u16 c);
s32 pokemonGetStatus(void* p, u16 a, u16 b, u16 c);
s32 wazaGetStatus(void* p, u16 a, u16 b, u16 c);
s32 fightFloorGetStatus(void* p, u16 a, u16 b, u16 c);
s32 fightSideGetStatus(void* p, u16 a, u16 b, u16 c);
s32 fightTrainerGetStatus(void* p, u16 a, u16 b, u16 c);

s32 statusSetStatus(u8 kind, void* p, u16 a, u16 b, void* target, s32 value) {
    s32 result = 0;
    switch (kind) {
    case 0:
        break;
    case 1:
        gamedataSetStatus(p, b, value);
        break;
    case 2:
        pcboxSetStatus(p, b, value);
        break;
    case 3:
        heroSetStatus(p, b, value);
        break;
    case 4:
        itemSetStatus(p, a, b, target, value);
        break;
    case 5:
        pokemonSetStatus(p, a, b, target, value);
        break;
    case 6:
        wazaSetStatus(p, a, b, target, value);
        break;
    case 7:
        result = fightFloorSetStatus(p, a, b, target, value);
        break;
    case 8:
        fightSideSetStatus(p, a, b, target, value);
        break;
    case 9:
        fightTrainerSetStatus(p, a, b, target, value);
        break;
    }
    return result;
}

s32 statusGetStatus(u8 kind, void* p, u16 a, u16 b, u16 c) {
    switch (kind) {
    case 0:
        return 0;
    case 1:
        return gamedataGetStatus(p, b);
    case 2:
        return pcboxGetStatus(p, b, c);
    case 3:
        return heroGetStatus(p, b, c);
    case 4:
        return itemGetStatus(p, a, b, c);
    case 5:
        return pokemonGetStatus(p, a, b, c);
    case 6:
        return wazaGetStatus(p, a, b, c);
    case 7:
        return fightFloorGetStatus(p, a, b, c);
    case 8:
        return fightSideGetStatus(p, a, b, c);
    case 9:
        return fightTrainerGetStatus(p, a, b, c);
    }
    return 0;
}

}
