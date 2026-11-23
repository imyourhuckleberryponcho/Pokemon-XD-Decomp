#include <game/pcret.h>
#ifndef __MWERKS__
#include <string.h>
#include <game/pcret.h>
#endif
#include <dolphin/types.h>
#include <game/gcdata.h>
#include <game/statusval.h>
#include "game/portxd_xg.h"

struct Hero;
struct Pokemon { u8 data[0xC8]; };
struct SmallPokemon { u8 data[0xC0]; };
struct GamedataAttest { u32 value; };

extern "C" {
StatusS32 gamedataGetStatus(PCARG(s32, void*), s32);
void gamedataAttestCreate(GamedataAttest*, s32, s32, s32, s32);
void pokemonCreate(void*, s32, s32, GamedataAttest*);
void pokemonSetStatus(void*, s32, s32, s32, s32);
u16 * GSmsgGetGSchar(s32);
void pokemonSetCatchStatus(void*, s32, s32, s32, s32, s32, StatusU32);
s32 pokemonCreateRndFit(void*, s32, s32, s32, s32);
void pokemonDoItemSoubi(void*, s32, s32);
void pokemonResetBasisStatus(void*);
void memoDataSet(PCARG(s32, void*), void*);
void heroGetPokemon(Hero*, void*, s32);
StatusS32 heroGetStatus(Hero*, s32, s32);
void pokemonWazaCreate(void*, s32, s32);
void heroCatchPokemon(Hero*, void*, s32, s32, s32);
}

extern "C" {
void heroPokemonGetCelebi(Hero* hero)
{
    GamedataAttest attest;
    Pokemon pokemon;
#ifndef __MWERKS__
    memset(&pokemon, 0, sizeof(pokemon));
#endif
    u8 status1 = (u8)gamedataGetStatus(0, 5);
    u8 status2 = (u8)gamedataGetStatus(0, 4);
    gamedataAttestCreate(&attest, 9, 3, status2, status1);
    pokemonCreate(&pokemon, 0xFB, 10, &attest);
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(&pokemon, 0xFF, 10, 4, 1, 0x7991, (StatusU32)GSmsgGetGSchar(1));
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
#ifndef __MWERKS__
    memset(&pokemon, 0, sizeof(pokemon));
#endif
    u8 status1 = (u8)gamedataGetStatus(0, 5);
    u8 status2 = (u8)gamedataGetStatus(0, 4);
    gamedataAttestCreate(&attest, 9, 3, status2, status1);
    pokemonCreate(&pokemon, 0x19, 10, &attest);
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(&pokemon, 0xFF, 10, 4, 0, 0x7991, (StatusU32)GSmsgGetGSchar(1));
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
#ifndef __MWERKS__
    memset(&pokemon, 0, sizeof(pokemon));
#endif
    u8 status1 = (u8)gamedataGetStatus(0, 5);
    u8 status2 = (u8)gamedataGetStatus(0, 4);
    gamedataAttestCreate(&attest, 8, 3, status2, status1);
    pokemonCreate(&pokemon, 0xFA, 0x46, &attest);
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(&pokemon, 0xFF, 0x46, 4, 0, 0x2740, (StatusU32)GSmsgGetGSchar(1));
    s32 fit = pokemonCreateRndFit(&pokemon, -1, -1, 0, 0x2740);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonResetBasisStatus(&pokemon);
    memoDataSet(0, &pokemon);
    heroGetPokemon(hero, &pokemon, 1);
}

void heroPokemonGetPrasle(Hero* hero)
{
    Pokemon pokemon;
#ifndef __MWERKS__
    memset(&pokemon, 0, sizeof(pokemon));
#endif
    pokemonCreate(&pokemon, 0x161, 0xD, (GamedataAttest*)gamedataGetStatus(0, 1));
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(&pokemon, 0x259, 0xD, 4, 0, 0x911D, (StatusU32)GSmsgGetGSchar(1));
    s32 fit = pokemonCreateRndFit(&pokemon, -1, -1, 0, 0x911D);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonResetBasisStatus(&pokemon);
    memoDataSet(0, &pokemon);
    heroGetPokemon(hero, &pokemon, 1);
}

void heroPokemonGetEifie(Hero* hero)
{
    Pokemon pokemon;
#ifndef __MWERKS__
    memset(&pokemon, 0, sizeof(pokemon));
#endif
    s32 heroStatus = heroGetStatus(hero, 2, 0);
    pokemonCreate(&pokemon, XG(0x86, 0x85), XG(0x1E, 0xF), (GamedataAttest*)gamedataGetStatus(0, 1));
    pokemonWazaCreate(&pokemon, 0, XG(0x10E, 0x1D));
    pokemonWazaCreate(&pokemon, 1, XG(0x37, 0x2C));
    pokemonWazaCreate(&pokemon, 2, XG(0x62, 0x130));
    pokemonWazaCreate(&pokemon, 3, XG(0x2C, 0xB6));
    s32 fit = pokemonCreateRndFit(&pokemon, XG(0, -1), -1, XG(0, -1), heroStatus);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonSetStatus(&pokemon, 0, 0x79, 0, XG(0x7148, 0xD2F));
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0xDC);
    pokemonResetBasisStatus(&pokemon);
    heroCatchPokemon(hero, &pokemon, 0x259, 4, 0);
}

void heroPokemonGetBlacky(Hero* hero)
{
    Pokemon pokemon;
#ifndef __MWERKS__
    memset(&pokemon, 0, sizeof(pokemon));
#endif
    s32 heroStatus = heroGetStatus(hero, 2, 0);
    pokemonCreate(&pokemon, XG(0x87, 0x120), XG(0x1A, 0xE), (GamedataAttest*)gamedataGetStatus(0, 1));
    pokemonWazaCreate(&pokemon, 0, XG(0x62, 0x21));
    pokemonWazaCreate(&pokemon, 1, XG(0x1C, 0x2D));
    pokemonWazaCreate(&pokemon, 2, XG(0x10E, 0xB6));
    pokemonWazaCreate(&pokemon, 3, XG(0x54, 0x10E));
    s32 fit = pokemonCreateRndFit(&pokemon, XG(0, -1), -1, XG(0, -1), heroStatus);
    pokemonSetStatus(&pokemon, 0, 0x6F, 0, fit);
    pokemonSetStatus(&pokemon, 0, 0x79, 0, XG(0x4A6F, 0xAB8));
    pokemonSetStatus(&pokemon, 0, 0x99, 0, 0xDC);
    pokemonResetBasisStatus(&pokemon);
    heroCatchPokemon(hero, &pokemon, 0x259, 4, 0);
}
}

