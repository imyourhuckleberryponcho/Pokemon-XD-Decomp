#include <dolphin/types.h>

struct Hero;
struct Pokemon { u8 data[0xC8]; };
struct SmallPokemon { u8 data[0xC0]; };
struct GamedataAttest { u32 value; };

extern "C" {
s32 gamedataGetStatus(s32, s32);
void gamedataAttestCreate(GamedataAttest*, s32, s32, s32, s32);
void pokemonCreate(void*, s32, s32, GamedataAttest*);
void pokemonSetStatus(void*, s32, s32, s32, s32);
s32 GSmsgGetGSchar(s32);
void pokemonSetCatchStatus(void*, s32, s32, s32, s32, s32, s32);
s32 pokemonCreateRndFit(void*, s32, s32, s32, s32);
void pokemonDoItemSoubi(void*, s32, s32);
void pokemonResetBasisStatus(void*);
void memoDataSet(s32, void*);
void heroGetPokemon(Hero*, void*, s32);
s32 heroGetStatus(Hero*, s32, s32);
void pokemonWazaCreate(void*, s32, s32);
void heroCatchPokemon(Hero*, void*, s32, s32, s32);
}

extern "C" {
void heroPokemonGetCelebi(Hero* hero)
{
    GamedataAttest attest;
    Pokemon pokemon;
    u8 status1 = (u8)gamedataGetStatus(0, 5);
    u8 status2 = (u8)gamedataGetStatus(0, 4);
    gamedataAttestCreate(&attest, 9, 3, status2, status1);
    pokemonCreate(&pokemon, 0xFB, 10, &attest);
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(&pokemon, 0xFF, 10, 4, 1, 0x7991, GSmsgGetGSchar(1));
    s32 fit = pokemonCreateRndFit(&pokemon, -1, -1, 0, 0x7991);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonResetBasisStatus(&pokemon);
    memoDataSet(0, &pokemon);
    heroGetPokemon(hero, &pokemon, 1);
}

void heroPokemonGetPikachu(Hero* hero)
{
    GamedataAttest attest;
    Pokemon pokemon;
    u8 status1 = (u8)gamedataGetStatus(0, 5);
    u8 status2 = (u8)gamedataGetStatus(0, 4);
    gamedataAttestCreate(&attest, 9, 3, status2, status1);
    pokemonCreate(&pokemon, 0x19, 10, &attest);
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(&pokemon, 0xFF, 10, 4, 0, 0x7991, GSmsgGetGSchar(1));
    s32 fit = pokemonCreateRndFit(&pokemon, -1, -1, 0, 0x7991);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonDoItemSoubi(&pokemon, 0xCA, 1);
    pokemonResetBasisStatus(&pokemon);
    memoDataSet(0, &pokemon);
    heroGetPokemon(hero, &pokemon, 1);
}

void heroPokemonGetHouou(Hero* hero)
{
    GamedataAttest attest;
    Pokemon pokemon;
    u8 status1 = (u8)gamedataGetStatus(0, 5);
    u8 status2 = (u8)gamedataGetStatus(0, 4);
    gamedataAttestCreate(&attest, 8, 3, status2, status1);
    pokemonCreate(&pokemon, 0xFA, 0x46, &attest);
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(&pokemon, 0xFF, 0x46, 4, 0, 0x2740, GSmsgGetGSchar(1));
    s32 fit = pokemonCreateRndFit(&pokemon, -1, -1, 0, 0x2740);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonResetBasisStatus(&pokemon);
    memoDataSet(0, &pokemon);
    heroGetPokemon(hero, &pokemon, 1);
}

void heroPokemonGetPrasle(Hero* hero)
{
    Pokemon pokemon;
    pokemonCreate(&pokemon, 0x161, 0xD, (GamedataAttest*)gamedataGetStatus(0, 1));
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(&pokemon, 0x259, 0xD, 4, 0, 0x911D, GSmsgGetGSchar(1));
    s32 fit = pokemonCreateRndFit(&pokemon, -1, -1, 0, 0x911D);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonResetBasisStatus(&pokemon);
    memoDataSet(0, &pokemon);
    heroGetPokemon(hero, &pokemon, 1);
}

void heroPokemonGetEifie(Hero* hero)
{
    Pokemon pokemon;
    s32 heroStatus = heroGetStatus(hero, 2, 0);
    pokemonCreate(&pokemon, 0x86, 0x1E, (GamedataAttest*)gamedataGetStatus(0, 1));
    pokemonWazaCreate(&pokemon, 0, 0x10E);
    pokemonWazaCreate(&pokemon, 1, 0x37);
    pokemonWazaCreate(&pokemon, 2, 0x62);
    pokemonWazaCreate(&pokemon, 3, 0x2C);
    s32 fit = pokemonCreateRndFit(&pokemon, 0, -1, 0, heroStatus);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonSetStatus(&pokemon, 0, 0x79, 0, 0x7148);
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0xDC);
    pokemonResetBasisStatus(&pokemon);
    heroCatchPokemon(hero, &pokemon, 0x259, 4, 0);
}

void heroPokemonGetBlacky(Hero* hero)
{
    Pokemon pokemon;
    s32 heroStatus = heroGetStatus(hero, 2, 0);
    pokemonCreate(&pokemon, 0x87, 0x1A, (GamedataAttest*)gamedataGetStatus(0, 1));
    pokemonWazaCreate(&pokemon, 0, 0x62);
    pokemonWazaCreate(&pokemon, 1, 0x1C);
    pokemonWazaCreate(&pokemon, 2, 0x10E);
    pokemonWazaCreate(&pokemon, 3, 0x54);
    s32 fit = pokemonCreateRndFit(&pokemon, 0, -1, 0, heroStatus);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonSetStatus(&pokemon, 0, 0x79, 0, 0x4A6F);
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0xDC);
    pokemonResetBasisStatus(&pokemon);
    heroCatchPokemon(hero, &pokemon, 0x259, 4, 0);
}
}







