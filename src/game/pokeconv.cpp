#include <game/pxdvs/app/pokemon/pokemonBios.hpp>

#pragma peephole off

struct GBAPokemon {
    u8 unk0[0x64];
};

struct GBASaveData {
    u8 flags[4];
    u8 name[8];
    u8 sex;
    u8 unkD[3];
    u32 rnd;
    GBAPokemon pokemon[6];
    u8 exribbon[11];
};

extern "C" {
void heroBiosSetHomePlace(void* hero, s32 place);
void heroBiosSetNamePtr(void* hero, u16* name);
void heroBiosSetSexDataId(void* hero, u8 sex);
void heroBiosSetRnd(void* hero, u32 rnd);
Pokemon* heroBiosGetPokemonPtr(void* hero, u16 index);
void* gamedataGetStatus(void*, s32);
void GScharMakeFromGBA(u16* dst, u8* src, s32 len, void* gamedata);
void gbaPokemonToGC(Pokemon* pokemon, GBAPokemon* gbaPokemon);
void exribbonSetNo(u32 index, u8 no);
}

static u32 _swap32(u32 value);

extern "C" {

void pokeconv(void* hero, GBASaveData* gba) {
    u16 name[8];
    s32 i;
    u32 flags = (gba->flags[3] << 24) | (gba->flags[2] << 16) | (gba->flags[1] << 8) | gba->flags[0];
    switch ((flags >> 10) & 0xF) {
    case 1:
        heroBiosSetHomePlace(hero, 1);
        break;
    case 2:
        heroBiosSetHomePlace(hero, 1);
        break;
    case 3:
        heroBiosSetHomePlace(hero, 2);
        break;
    case 4:
        heroBiosSetHomePlace(hero, 2);
        break;
    case 5:
        heroBiosSetHomePlace(hero, 3);
        break;
    default:
        heroBiosSetHomePlace(hero, 1);
        break;
    }
    GScharMakeFromGBA(name, gba->name, 7, gamedataGetStatus(0, 5));
    heroBiosSetNamePtr(hero, name);
    heroBiosSetSexDataId(hero, gba->sex);
    heroBiosSetRnd(hero, _swap32(gba->rnd));
    for (i = 0; i < 6; i++) {
        Pokemon* pokemon = heroBiosGetPokemonPtr(hero, i);
        gbaPokemonToGC(pokemon, &gba->pokemon[i]);
        pokemonBiosSetFightTrainerPokemonDataId(pokemon, i);
    }
    for (i = 0; i < 11; i++) {
        exribbonSetNo(i, gba->exribbon[i]);
    }
}

}

static u32 _swap32(u32 value) {
    return (value << 24) | ((value & 0xFF00) << 8) | ((value & 0xFF0000) >> 8) | (value >> 24);
}
