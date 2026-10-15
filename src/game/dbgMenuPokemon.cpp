// STATUS: EditButton + GetTotalEffort written; dbgMenuPokemonEditSub (8.5 KB) NOT started (empty stub).
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
s32 pokemonGetStatus(void*, s32, s32, s32);

void dbgMenuPokemonEditButton(PokemonEditWindow* window) {
    void* pokemon = window->pokemon;
    s32* out = window->out;
    s32 repeat;
    s32 held;
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
void dbgMenuPokemonEditSub(void* window) {
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
