// Debug menu units were built without the peephole optimizer.
#include <dolphin/types.h>

#pragma peephole off

struct PokemonEditWindow {
    u8 unk0[4];
    s32 menu;
    u8 unk8[0x60];
    void* pokemon;
    s32* out;
    u8 unk70[0x18];
    s32 selection;
    u8 unk8C[0x12];
    s16 cursor;
    u8 unkA0[4];
    u8 done;
};

struct EditKeyInfo {
    u16 held;
    u8 unk2[4];
    u16 repeat;
};

static inline bool hit(u16 v, u16 m) {
    return (v & m) != 0;
}

extern "C" {
EditKeyInfo* windowGetKeyInfo(void);
u8 pokemonCheckValid(void*);
void* menuDataBiosGetPtr(s32);
s32 menuGetCursorItemID(s32);
s32 pokemonGetStatus(void*, u16, u16, u16);

void dbgMenuPokemonEditButton(PokemonEditWindow* window) {
    void* pokemon = window->pokemon;
    s32* out = window->out;
    u16 repeat;
    u16 held;
    s32 delta;
    s32 id;

    if (window != 0) {
        repeat = (u16)windowGetKeyInfo()->repeat;
        held = (u16)windowGetKeyInfo()->held;
        if (hit(repeat, 0x20)) {
            window->selection = -1;
            window->done = 1;
        } else if (hit(repeat, 0x10)) {
            window->selection = -2;
            window->done = 1;
        } else if (pokemon == 0) {
            window->selection = -1;
            window->done = 1;
        } else {
            delta = 0;
            if (hit(repeat, 0x80) && hit(held, 0x200) && hit(held, 0x400)) {
                delta = 100;
            } else if (hit(repeat, 0x40) && hit(held, 0x200) && hit(held, 0x400)) {
                delta = -100;
            } else if (hit(repeat, 0x80) && hit(held, 0x200)) {
                delta = 10;
            } else if (hit(repeat, 0x40) && hit(held, 0x200)) {
                delta = -10;
            } else if (hit(repeat, 0x80)) {
                delta = 1;
            } else if (hit(repeat, 0x40)) {
                delta = -1;
            } else if (hit(repeat, 0x100) && hit(held, 0x200)) {
                delta = 0xFFFF;
            } else if (hit(repeat, 0x100)) {
                delta = -0xFFFF;
            }
            if (!pokemonCheckValid(pokemon)) {
                window->cursor = 0;
                id = 0x16;
            } else {
                menuDataBiosGetPtr(window->menu);
                id = menuGetCursorItemID(window->menu);
            }
            if (delta != 0) {
                if (out != 0) {
                    *out = delta;
                }
                window->selection = id;
                window->done = 1;
            }
        }
    }
}

}


extern "C" {
void pokemonSetStatus(void*, u16, u16, u16, u32);
void pokemonCreate(void*, u16, u8, void*);
u32 gamedataGetStatus(void*, u32);
void pokemonSetCatchStatus(void*, u32, u8, u32, u8, u32, void*);
s32 menuOpenCustom(s32, ...);
void menuCloseCustom(s32, s32, s32);
s32 menuOpen(s32, s32);
u8 menuSubOpenNumberInput(u32, s32*, u8, s16, s16, bool);
void menuSubCloseNumberInput(void);
u32 GSmsgGetGSchar(u32);
void pokemonSetTokuseiFlag(void*, u32);
void pokemonWazaInit(void*, u16);
void pokemonWazaCreate(void*, u16, u16);
u8 pokemonWazaCheckValid(void*, u16);
u8 pokemonWazaGetMaxPP(void*, u16);
u32 wazaCheckDarkWaza(u16);
u16 pokemonGetSoubiItemDataId(void*);
u16 pokemonDoItemSoubi(void*, u16, u8);
u32 pokemonCheckRare(void*);
u32 pokemonCreateRndFit(void*, s8, s8, s8, u32);
u16 pokemonGetJoutaiDataId(void*);
void pokemonInitJoutai(void*);
u8 pokemonCheckWriteJoutaiDataId(void*, u16);
void pokemonWriteJoutaiDataId(void*, u16, u32);
s8 pokemonGetKaisuuJoutaiDataId(void*, u16);
void pokemonSetKaisuuJoutaiDataId(void*, u16, s8);
s8 pokemonGetNowKaisuuJoutaiDataId(void*, u16);
void pokemonSetNowKaisuuJoutaiDataId(void*, u16, s8);
s16 pokemonGetCountAsJoutaiDataId(void*, u16);
void pokemonSetCountAsJoutaiDataId(void*, u16, s16);
u8 joutaiDataBiosGetMaxCount(u16);
void pokemonInitDarkPokemon(void*);
void pokemonSetDarkPokemonStatus(void*, u16);
u8 pokemonIsDarkPokemon(void*);
void pokemonInitJoutaiDataId(void*, u16);
u32 fightTrainerGetStatus(void*, u16, u16, u16);
void fightTrainerSetStatus(void*, u16, u16, u16, u32);
u32 pokemonGetNowLevelToExp(void*);
void pokemonGrowBasisStatus(void*, u32);
u16 pokemonBiosGetPokemonDataId(void*);
void pokemonBiosSetEventGetFlag(void*, u32);
u8 itemDataCheckValid(u16);
void pokemonInit(void*);
extern u32* pokemon_data_number;
extern u32* item_data_index_number;
extern u32 sex_data_number;
extern u32* pokemon_seikaku_data_number;
extern u32 darkPokemonList_number;
extern u32* fight_trainer_pokemon_part_data_number;
}

static u16 gRibbonStat[18] = {
    0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB,
    0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
};
static s32 gRibbonNum;
static s32 pokemon_edit_value;

struct SavedPokemon {
    u8 bytes[0xC4];
};


extern "C" {
static s32 dbgMenuPokemonEditSubGetTotalEffort(void* pokemon);
}

extern "C" {
s32 dbgMenuPokemonEditSub(void* pokemon, u8 a1, u8* a2, u8* a3, u8* a4, u8* a5) {
    s32 catchSeed[1] = {0};
    u16 ivStats[6] = {0x93, 0x94, 0x95, 0x96, 0x97, 0x98};
    u16 evStats[6] = {0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92};
    SavedPokemon saved;
    s32 input;
    s32 selection;
    s32 delta;
    u32 trainerId;
    u8 changed;
    s32 value;
    s32 i;

    if (a2 != 0) {
        *a2 = 0;
    }
    if (a3 != 0) {
        *a3 = 0;
    }
    if (a4 != 0) {
        *a4 = 0;
    }
    if (a5 != 0) {
        *a5 = 0;
    }

    saved = *(SavedPokemon*)pokemon;

    if (pokemonCheckValid(pokemon) == 0) {
        pokemonCreate(pokemon, 0x115, 1, (void*)gamedataGetStatus(0, 1));
        pokemonSetCatchStatus(pokemon, 0, 1, 0, 2, 0, catchSeed);
    }
    trainerId = pokemonGetStatus(pokemon, 0, 0xC9, 0) & 0xFFFF;

    for (;;) {
        pokemon_edit_value = 0;
        selection = menuOpenCustom(0xD, 0, 0, 0, 1, 2, pokemon, &pokemon_edit_value);
        delta = pokemon_edit_value;

        if (selection == -1) {
            menuCloseCustom(0xD, 0, 1);
            *(SavedPokemon*)pokemon = saved;
            return -1;
        }

        if (selection == -2) {
            if (menuOpen(0x55, 1) == 0) {
                break;
            }
            menuCloseCustom(0x55, 0, 1);
            continue;
        }

        if (delta == 0) {
            continue;
        }

        changed = 0;
        switch (selection) {
        case 0x16:
        {
            s32 species = pokemonGetStatus(pokemon, 0, 0x6E, 0);
            species += delta;
            if (species < 0) {
                species = 0;
            }
            if (species >= *pokemon_data_number) {
                species = *pokemon_data_number - 1;
            }
            pokemonSetStatus(pokemon, 0, 0x6E, 0, species);
            pokemonSetStatus(pokemon, 0, 0x77, 0, GSmsgGetGSchar(pokemonGetStatus(0, species, 1, 0)));
            pokemonSetTokuseiFlag(pokemon, 0);
            changed = 1;
            if (a2 != 0) {
                *a2 = 1;
            }
            if (a3 != 0) {
                *a3 = 1;
            }
        }
            break;
        case 0x18:
            value = pokemonGetStatus(pokemon, 0, 0x7A, 0);
            value += delta;
            if (value <= 0) {
                value = 1;
            }
            if (value > 0x64) {
                value = 0x64;
            }
            pokemonSetStatus(pokemon, 0, 0x7A, 0, value);
            changed = 1;
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x1A:
            value = pokemonGetStatus(pokemon, 0, 0x79, 0);
            if (delta == -0xFFFF) {
                value = 1;
            } else if (delta == 0xFFFF) {
                value = 0x1E8480;
            } else if (menuSubOpenNumberInput(value, &input, 1, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
                break;
            } else {
                value = input;
                menuSubCloseNumberInput();
                if (value <= 0) {
                    value = 1;
                }
                if (value > 0x1E8480) {
                    value = 0x1E8480;
                }
            }
            pokemonSetStatus(pokemon, 0, 0x79, 0, value);
            changed = 1;
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x1C:
            value = pokemonGetStatus(pokemon, 0, 0x83, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > pokemonGetStatus(pokemon, 0, 0x87, 0)) {
                value = pokemonGetStatus(pokemon, 0, 0x87, 0);
            }
            pokemonSetStatus(pokemon, 0, 0x83, 0, value);
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x26:
            value = pokemonGetStatus(pokemon, 0, 0x87, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x3E7) {
                value = 0x3E7;
            }
            pokemonSetStatus(pokemon, 0, 0x87, 0, value);
            pokemonSetStatus(pokemon, 0, 0x83, 0, value);
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x27:
            value = pokemonGetStatus(pokemon, 0, 0x88, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x3E7) {
                value = 0x3E7;
            }
            pokemonSetStatus(pokemon, 0, 0x88, 0, value);
            break;
        case 0x28:
            value = pokemonGetStatus(pokemon, 0, 0x89, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x3E7) {
                value = 0x3E7;
            }
            pokemonSetStatus(pokemon, 0, 0x89, 0, value);
            break;
        case 0x29:
            value = pokemonGetStatus(pokemon, 0, 0x8C, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x3E7) {
                value = 0x3E7;
            }
            pokemonSetStatus(pokemon, 0, 0x8C, 0, value);
            break;
        case 0x2A:
            value = pokemonGetStatus(pokemon, 0, 0x8A, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x3E7) {
                value = 0x3E7;
            }
            pokemonSetStatus(pokemon, 0, 0x8A, 0, value);
            break;
        case 0x2B:
            value = pokemonGetStatus(pokemon, 0, 0x8B, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x3E7) {
                value = 0x3E7;
            }
            pokemonSetStatus(pokemon, 0, 0x8B, 0, value);
            break;
        case 0x2C:
            value = pokemonGetStatus(pokemon, 0, 0x93, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x1F) {
                value = 0x1F;
            }
            pokemonSetStatus(pokemon, 0, 0x93, 0, value);
            changed = 1;
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x2D:
            value = pokemonGetStatus(pokemon, 0, 0x94, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x1F) {
                value = 0x1F;
            }
            pokemonSetStatus(pokemon, 0, 0x94, 0, value);
            changed = 1;
            break;
        case 0x2E:
            value = pokemonGetStatus(pokemon, 0, 0x95, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x1F) {
                value = 0x1F;
            }
            pokemonSetStatus(pokemon, 0, 0x95, 0, value);
            changed = 1;
            break;
        case 0x2F:
            value = pokemonGetStatus(pokemon, 0, 0x98, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x1F) {
                value = 0x1F;
            }
            pokemonSetStatus(pokemon, 0, 0x98, 0, value);
            changed = 1;
            break;
        case 0x30:
            value = pokemonGetStatus(pokemon, 0, 0x96, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x1F) {
                value = 0x1F;
            }
            pokemonSetStatus(pokemon, 0, 0x96, 0, value);
            changed = 1;
            break;
        case 0x31:
            value = pokemonGetStatus(pokemon, 0, 0x97, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0x1F) {
                value = 0x1F;
            }
            pokemonSetStatus(pokemon, 0, 0x97, 0, value);
            changed = 1;
            break;
        case 0x32:
            if (delta > 0) {
                if ((u32)dbgMenuPokemonEditSubGetTotalEffort(pokemon) >= 0x1FE) {
                    break;
                }
            }
            value = pokemonGetStatus(pokemon, 0, 0x8D, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xFF) {
                value = 0xFF;
            }
            pokemonSetStatus(pokemon, 0, 0x8D, 0, value);
            changed = 1;
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x33:
            if (delta > 0) {
                if ((u32)dbgMenuPokemonEditSubGetTotalEffort(pokemon) >= 0x1FE) {
                    break;
                }
            }
            value = pokemonGetStatus(pokemon, 0, 0x8E, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xFF) {
                value = 0xFF;
            }
            pokemonSetStatus(pokemon, 0, 0x8E, 0, value);
            changed = 1;
            break;
        case 0x34:
            if (delta > 0) {
                if ((u32)dbgMenuPokemonEditSubGetTotalEffort(pokemon) >= 0x1FE) {
                    break;
                }
            }
            value = pokemonGetStatus(pokemon, 0, 0x8F, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xFF) {
                value = 0xFF;
            }
            pokemonSetStatus(pokemon, 0, 0x8F, 0, value);
            changed = 1;
            break;
        case 0x35:
            if (delta > 0) {
                if ((u32)dbgMenuPokemonEditSubGetTotalEffort(pokemon) >= 0x1FE) {
                    break;
                }
            }
            value = pokemonGetStatus(pokemon, 0, 0x92, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xFF) {
                value = 0xFF;
            }
            pokemonSetStatus(pokemon, 0, 0x92, 0, value);
            changed = 1;
            break;
        case 0x36:
            if (delta > 0) {
                if ((u32)dbgMenuPokemonEditSubGetTotalEffort(pokemon) >= 0x1FE) {
                    break;
                }
            }
            value = pokemonGetStatus(pokemon, 0, 0x90, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xFF) {
                value = 0xFF;
            }
            pokemonSetStatus(pokemon, 0, 0x90, 0, value);
            changed = 1;
            break;
        case 0x37:
            if (delta > 0) {
                if ((u32)dbgMenuPokemonEditSubGetTotalEffort(pokemon) >= 0x1FE) {
                    break;
                }
            }
            value = pokemonGetStatus(pokemon, 0, 0x91, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xFF) {
                value = 0xFF;
            }
            pokemonSetStatus(pokemon, 0, 0x91, 0, value);
            changed = 1;
            break;
        case 0x39:
            value = pokemonGetStatus(pokemon, 0, 0x7F, 0);
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                pokemonWazaInit(pokemon, 0);
                break;
            }
            if (value == 0x163) {
                value += delta;
            }
            if (value >= 0x176) {
                value = 0x175;
            }
            pokemonWazaCreate(pokemon, 0, (u16)value);
            break;
        case 0x3A:
            value = pokemonGetStatus(pokemon, 0, 0x7F, 1);
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                pokemonWazaInit(pokemon, 1);
                break;
            }
            if (value == 0x163) {
                value += delta;
            }
            if (value >= 0x176) {
                value = 0x175;
            }
            pokemonWazaCreate(pokemon, 1, (u16)value);
            break;
        case 0x3B:
            value = pokemonGetStatus(pokemon, 0, 0x7F, 2);
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                pokemonWazaInit(pokemon, 2);
                break;
            }
            if (value == 0x163) {
                value += delta;
            }
            if (value >= 0x176) {
                value = 0x175;
            }
            pokemonWazaCreate(pokemon, 2, (u16)value);
            break;
        case 0x3C:
            value = pokemonGetStatus(pokemon, 0, 0x7F, 3);
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                pokemonWazaInit(pokemon, 3);
                break;
            }
            if (value == 0x163) {
                value += delta;
            }
            if (value >= 0x176) {
                value = 0x175;
            }
            pokemonWazaCreate(pokemon, 3, (u16)value);
            break;
        case 0x3D:
            if (pokemonWazaCheckValid(pokemon, 0) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0x80, 0);
            if ((u8)wazaCheckDarkWaza((u16)value) == 1) {
                break;
            }
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > pokemonWazaGetMaxPP(pokemon, 0)) {
                value = pokemonWazaGetMaxPP(pokemon, 0);
            }
            pokemonSetStatus(pokemon, 0, 0x80, 0, (u8)value);
            break;
        case 0x3E:
            if (pokemonWazaCheckValid(pokemon, 1) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0x80, 1);
            if ((u8)wazaCheckDarkWaza((u16)value) == 1) {
                break;
            }
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > pokemonWazaGetMaxPP(pokemon, 1)) {
                value = pokemonWazaGetMaxPP(pokemon, 1);
            }
            pokemonSetStatus(pokemon, 0, 0x80, 1, (u8)value);
            break;
        case 0x3F:
            if (pokemonWazaCheckValid(pokemon, 2) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0x80, 2);
            if ((u8)wazaCheckDarkWaza((u16)value) == 1) {
                break;
            }
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > pokemonWazaGetMaxPP(pokemon, 2)) {
                value = pokemonWazaGetMaxPP(pokemon, 2);
            }
            pokemonSetStatus(pokemon, 0, 0x80, 2, (u8)value);
            break;
        case 0x40:
            if (pokemonWazaCheckValid(pokemon, 3) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0x80, 3);
            if ((u8)wazaCheckDarkWaza((u16)value) == 1) {
                break;
            }
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > pokemonWazaGetMaxPP(pokemon, 3)) {
                value = pokemonWazaGetMaxPP(pokemon, 3);
            }
            pokemonSetStatus(pokemon, 0, 0x80, 3, (u8)value);
            break;
        case 0x41:
            if (pokemonWazaCheckValid(pokemon, 0) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0x81, 0);
            if ((u8)wazaCheckDarkWaza((u16)value) == 1) {
                break;
            }
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 3) {
                value = 3;
            }
            pokemonSetStatus(pokemon, 0, 0x81, 0, (u8)value);
            pokemonSetStatus(pokemon, 0, 0x80, 0, pokemonWazaGetMaxPP(pokemon, 0));
            break;
        case 0x42:
            if (pokemonWazaCheckValid(pokemon, 1) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0x81, 1);
            if ((u8)wazaCheckDarkWaza((u16)value) == 1) {
                break;
            }
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 3) {
                value = 3;
            }
            pokemonSetStatus(pokemon, 0, 0x81, 1, (u8)value);
            pokemonSetStatus(pokemon, 0, 0x80, 1, pokemonWazaGetMaxPP(pokemon, 1));
            break;
        case 0x43:
            if (pokemonWazaCheckValid(pokemon, 2) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0x81, 2);
            if ((u8)wazaCheckDarkWaza((u16)value) == 1) {
                break;
            }
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 3) {
                value = 3;
            }
            pokemonSetStatus(pokemon, 0, 0x81, 2, (u8)value);
            pokemonSetStatus(pokemon, 0, 0x80, 2, pokemonWazaGetMaxPP(pokemon, 2));
            break;
        case 0x44:
            if (pokemonWazaCheckValid(pokemon, 3) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0x81, 3);
            if ((u8)wazaCheckDarkWaza((u16)value) == 1) {
                break;
            }
            if (value == 0x176) {
                break;
            }
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 3) {
                value = 3;
            }
            pokemonSetStatus(pokemon, 0, 0x81, 3, (u8)value);
            pokemonSetStatus(pokemon, 0, 0x80, 3, pokemonWazaGetMaxPP(pokemon, 3));
            break;
        case 0x46:
            if ((u8)pokemonGetStatus(pokemon, 0, 0xB7, 0) == 1) {
                value = 0;
            } else {
                value = 1;
            }
            if (pokemonGetStatus(0, pokemonGetStatus(pokemon, 0, 0x6E, 0), 0x17, 1) == 0) {
                value = 0;
            }
            pokemonSetTokuseiFlag(pokemon, value);
            if (a4 != 0) {
                *a4 = 1;
            }
            break;
        case 0x48:
            value = pokemonGetSoubiItemDataId(pokemon);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value >= *item_data_index_number) {
                value = *item_data_index_number - 1;
            }
            pokemonDoItemSoubi(pokemon, (u16)value, 1);
            if (a5 != 0) {
                *a5 = 1;
            }
            break;
        case 0x4A:
            value = pokemonGetStatus(pokemon, 0, 0x6F, 0);
            if (delta == -0xFFFF) {
                value = 0;
            } else if (delta == 0xFFFF) {
                value = -1;
            } else if (menuSubOpenNumberInput(value, &input, 1, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
                break;
            } else {
                value = input;
                menuSubCloseNumberInput();
            }
            pokemonSetStatus(pokemon, 0, 0x6F, 0, value);
            changed = 1;
            if (a2 != 0) {
                *a2 = 1;
            }
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x4B:
        {
            u32 pid;
            value = pokemonGetStatus(pokemon, 0, 0xBA, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value >= sex_data_number) {
                value = sex_data_number - 1;
            }
            pid = pokemonCreateRndFit(pokemon, (s8)value, (s8)pokemonGetStatus(pokemon, 0, 0xBF, 0), (s8)pokemonCheckRare(pokemon), pokemonGetStatus(pokemon, 0, 0x75, 0));
            pokemonSetStatus(pokemon, 0, 0x6F, 0, pid);
            changed = 1;
            if (a2 != 0) {
                *a2 = 1;
            }
            if (a3 != 0) {
                *a3 = 1;
            }
        }
            break;
        case 0x4C:
            value = (u8)pokemonGetStatus(pokemon, 0, 0xBF, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value >= *pokemon_seikaku_data_number) {
                value = *pokemon_seikaku_data_number - 1;
            }
            pokemonSetStatus(pokemon, 0, 0x6F, 0, pokemonCreateRndFit(pokemon, (s8)pokemonGetStatus(pokemon, 0, 0xBA, 0), (s8)value, (s8)pokemonCheckRare(pokemon), pokemonGetStatus(pokemon, 0, 0x75, 0)));
            changed = 1;
            if (a2 != 0) {
                *a2 = 1;
            }
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x4D:
            if (delta > 0) {
                value = 1;
            } else {
                value = 0;
            }
            pokemonSetStatus(pokemon, 0, 0x6F, 0, pokemonCreateRndFit(pokemon, (s8)pokemonGetStatus(pokemon, 0, 0xBA, 0), (s8)pokemonGetStatus(pokemon, 0, 0xBF, 0), (s8)value, pokemonGetStatus(pokemon, 0, 0x75, 0)));
            changed = 1;
            if (a2 != 0) {
                *a2 = 1;
            }
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x4F:
            value = pokemonGetStatus(pokemon, 0, 0x75, 0);
            if (delta == -0xFFFF) {
                value = 0;
            } else if (delta == 0xFFFF) {
                value = -1;
            } else if (menuSubOpenNumberInput(value, &input, 1, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
                break;
            } else {
                value = input;
                menuSubCloseNumberInput();
            }
            pokemonSetStatus(pokemon, 0, 0x75, 0, value);
            if (a2 != 0) {
                *a2 = 1;
            }
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x51:
            value = pokemonGetStatus(pokemon, 0, 0x99, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xFF) {
                value = 0xFF;
            }
            pokemonSetStatus(pokemon, 0, 0x99, 0, value);
            break;
        case 0x53:
            value = pokemonGetStatus(pokemon, 0, 0xB5, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xFF) {
                value = 0xFF;
            }
            pokemonSetStatus(pokemon, 0, 0xB5, 0, value);
            break;
        case 0x55:
            value = pokemonGetJoutaiDataId(pokemon);
            if (value == 0) {
                value = delta + 2;
            } else {
                value += delta;
            }
            if (value < 3) {
                value = 0;
            }
            if (value > 8) {
                value = 8;
            }
            pokemonInitJoutai(pokemon);
            if (value != 0 && pokemonCheckWriteJoutaiDataId(pokemon, (u16)value) == 2) {
                pokemonWriteJoutaiDataId(pokemon, (u16)value, 0);
            }
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x56:
            value = pokemonGetJoutaiDataId(pokemon);
            if (value == 0) {
                break;
            }
            i = pokemonGetKaisuuJoutaiDataId(pokemon, value);
            if (value != 4) {
                if (i < 0) {
                    break;
                }
                i += delta;
                if (i < 0) {
                    i = 0;
                }
                if (i > 0x10) {
                    i = 0x10;
                }
                pokemonSetKaisuuJoutaiDataId(pokemon, value, i);
                if (pokemonGetNowKaisuuJoutaiDataId(pokemon, value) > i) {
                    pokemonSetNowKaisuuJoutaiDataId(pokemon, value, i);
                }
            } else {
                i = pokemonGetCountAsJoutaiDataId(pokemon, value);
                i += delta;
                if (i < 0) {
                    i = 0;
                }
                if (i > joutaiDataBiosGetMaxCount(value)) {
                    i = joutaiDataBiosGetMaxCount(value);
                }
                pokemonSetCountAsJoutaiDataId(pokemon, value, i);
            }
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x57:
        {
            s32 max;
            value = pokemonGetJoutaiDataId(pokemon);
            if (value == 0) {
                break;
            }
            max = pokemonGetKaisuuJoutaiDataId(pokemon, value);
            if (value == 4 || max < 0) {
                break;
            }
            i = pokemonGetNowKaisuuJoutaiDataId(pokemon, value);
            i += delta;
            if (i < 0) {
                i = 0;
            }
            if (i > pokemonGetKaisuuJoutaiDataId(pokemon, value)) {
                i = pokemonGetKaisuuJoutaiDataId(pokemon, value);
            }
            pokemonSetNowKaisuuJoutaiDataId(pokemon, value, i);
            if (a3 != 0) {
                *a3 = 1;
            }
        }
            break;
        case 0x59:
            value = pokemonGetStatus(pokemon, 0, 0xC3, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value >= darkPokemonList_number) {
                value = darkPokemonList_number - 1;
            }
            if (value == 0) {
                pokemonInitDarkPokemon(pokemon);
            } else {
                pokemonSetStatus(pokemon, 0, 0xC3, 0, value);
                pokemonSetDarkPokemonStatus(pokemon, (u16)value);
            }
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x5B:
            if ((u16)pokemonGetStatus(pokemon, 0, 0xC3, 0) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0xC5, 0);
            if (delta == -0xFFFF) {
                value = -1;
            } else if (delta == 0xFFFF) {
                value = 0xFFFF;
            } else if (menuSubOpenNumberInput(value, &input, 0, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
                break;
            } else {
                value = input;
                menuSubCloseNumberInput();
                if (value < -1) {
                    value = -1;
                }
                if ((f32)value > 65535.0f) {
                    value = 0xFFFF;
                }
            }
            pokemonSetStatus(pokemon, 0, 0xC5, 0, value);
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x5D:
            if (pokemonIsDarkPokemon(pokemon) == 0) {
                break;
            }
            if (delta > 0) {
                pokemonWriteJoutaiDataId(pokemon, 0x3E, 0);
            } else {
                pokemonInitJoutaiDataId(pokemon, 0x3E);
            }
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x5F:
            if ((u16)pokemonGetStatus(pokemon, 0, 0xC3, 0) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0xC6, 0);
            if (delta == -0xFFFF) {
                value = 0;
            } else if (delta == 0xFFFF) {
                value = 0x1E8480;
            } else if (menuSubOpenNumberInput(value, &input, 1, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
                break;
            } else {
                value = input;
                menuSubCloseNumberInput();
                if (value < 0) {
                    value = 0;
                }
                if (value > 0x1E8480) {
                    value = 0x1E8480;
                }
            }
            pokemonSetStatus(pokemon, 0, 0xC6, 0, value);
            break;
        case 0x61:
            if ((u16)pokemonGetStatus(pokemon, 0, 0xC3, 0) == 0) {
                break;
            }
            value = pokemonGetStatus(pokemon, 0, 0xC7, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xFF) {
                value = 0xFF;
            }
            pokemonSetStatus(pokemon, 0, 0xC7, 0, value);
            break;
        case 0x69:
            if (trainerId == 0 || a1 != 1) {
                break;
            }
            value = (u8)fightTrainerGetStatus(0, trainerId, 0x1C, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 3) {
                value = 3;
            }
            fightTrainerSetStatus(0, trainerId, 0x1C, 0, (u8)value);
            break;
        case 0x6B:
            if (trainerId == 0 || a1 != 1) {
                break;
            }
            value = (u16)fightTrainerGetStatus(0, trainerId, 0x1D, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value >= *fight_trainer_pokemon_part_data_number) {
                value = *fight_trainer_pokemon_part_data_number - 1;
            }
            fightTrainerSetStatus(0, trainerId, 0x1D, 0, (u16)value);
            break;
        case 0x70:
            value = pokemonGetStatus(pokemon, 0, 0x73, 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 0xC) {
                value = 0xC;
            }
            pokemonSetStatus(pokemon, 0, 0x73, 0, value);
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x6E:
            value = pokemonGetStatus(pokemon, 0, gRibbonStat[gRibbonNum], 0);
            value += delta;
            if (value < 0) {
                value = 0;
            }
            if (value > 4) {
                value = 4;
            }
            pokemonSetStatus(pokemon, 0, gRibbonStat[gRibbonNum], 0, value);
            if (a3 != 0) {
                *a3 = 1;
            }
            break;
        case 0x6D:
            gRibbonNum += delta;
            if (gRibbonNum < 0) {
                gRibbonNum = 0;
            }
            if (gRibbonNum > 0x11) {
                gRibbonNum = 0x11;
            }
            break;
        }
        if (changed == 1) {
            pokemonSetTokuseiFlag(pokemon, (u8)pokemonGetStatus(pokemon, 0, 0xB7, 0));
            if (selection == 0x18) {
                value = pokemonGetNowLevelToExp(pokemon);
            } else {
                value = pokemonGetStatus(pokemon, 0, 0x79, 0);
            }
            pokemonGrowBasisStatus(pokemon, value);
        }
    }
    menuCloseCustom(0x55, 0, 1);
    menuCloseCustom(0xD, 0, 1);
    switch (pokemonBiosGetPokemonDataId(pokemon)) {
    case 0x97:
    case 0x19A: {
        u8 state = pokemonGetStatus(pokemon, 0, 0x73, 0);
        if (state == 4 || state == 0) {
            pokemonBiosSetEventGetFlag(pokemon, 1);
        } else {
            pokemonBiosSetEventGetFlag(pokemon, 0);
        }
        break;
    }
    }
    if (pokemonCheckValid(pokemon) == 0) {
        pokemonInit(pokemon);
    } else {
        if (itemDataCheckValid(pokemonGetSoubiItemDataId(pokemon)) == 0) {
            pokemonDoItemSoubi(pokemon, 0, 0);
        }
        if (trainerId != 0 && a1 == 1) {
            s32 j;
            value = pokemonGetStatus(pokemon, 0, 0x6E, 0);
            fightTrainerSetStatus(0, trainerId, 0x15, 0, value);
            fightTrainerSetStatus(0, trainerId, 0xE, 0, pokemonGetStatus(0, value, 1, 0));
            fightTrainerSetStatus(0, trainerId, 0x11, 0, pokemonGetStatus(pokemon, 0, 0x7A, 0));
            for (j = 0; j < 6; j++) {
                fightTrainerSetStatus(0, trainerId, 0xF, j, pokemonGetStatus(pokemon, 0, ivStats[j], 0));
            }
            for (j = 0; j < 6; j++) {
                fightTrainerSetStatus(0, trainerId, 0x10, j, pokemonGetStatus(pokemon, 0, evStats[j], 0));
            }
            fightTrainerSetStatus(0, trainerId, 0x14, 0, (u8)pokemonGetStatus(pokemon, 0, 0xB7, 0));
            fightTrainerSetStatus(0, trainerId, 0x16, 0, pokemonGetSoubiItemDataId(pokemon));
            fightTrainerSetStatus(0, trainerId, 0x19, 0, pokemonGetStatus(pokemon, 0, 0x99, 0));
            fightTrainerSetStatus(0, trainerId, 0x1A, 0, pokemonGetStatus(pokemon, 0, 0xBA, 0));
            fightTrainerSetStatus(0, trainerId, 0x1B, 0, pokemonGetStatus(pokemon, 0, 0xBF, 0));
            for (j = 0; j < 4; j++) {
                fightTrainerSetStatus(0, trainerId, 0x17, j, pokemonGetStatus(pokemon, 0, 0x7F, j));
                fightTrainerSetStatus(0, trainerId, 0x18, j, pokemonGetStatus(pokemon, 0, 0x81, j));
            }
            fightTrainerSetStatus(0, trainerId, 0x13, 0, pokemonGetStatus(pokemon, 0, 0xC3, 0));
        }
    }
    return 1;
}
}

extern "C" {
static s32 dbgMenuPokemonEditSubGetTotalEffort(void* pokemon) {
    s32 total;
    total = pokemonGetStatus(pokemon, 0, 0x8D, 0);
    total += pokemonGetStatus(pokemon, 0, 0x8E, 0);
    total += pokemonGetStatus(pokemon, 0, 0x8F, 0);
    total += pokemonGetStatus(pokemon, 0, 0x90, 0);
    total += pokemonGetStatus(pokemon, 0, 0x91, 0);
    total += pokemonGetStatus(pokemon, 0, 0x92, 0);
    return total;
}
}
