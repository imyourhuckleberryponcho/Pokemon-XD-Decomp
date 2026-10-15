#include <dolphin/types.h>

struct Pokemon;
struct Sequence;

// One move whose animation should be preloaded.
struct SequenceWaza {
    u16 wazaID;
    u16 kind;
};

extern "C" {

void GSthreadSwitch(void);
f32 pokecoloGetFrameTime(void);
u32 pokemonGetStatus(Pokemon* pokemon, u32 species, s32 kind, s32);
u32 pokemonBiosGetRnd(Pokemon* pokemon);
Sequence* Sequence_LoadPokemon(u16 id, u32 rnd, bool shiny);
void* Sequence_LoadWaza(Sequence* sequence, u16 wazaID, u8 kind, s32);

void waitTime(f32 time) {
    f32 elapsed = 0.0f;
    while (elapsed < time) {
        GSthreadSwitch();
        elapsed += pokecoloGetFrameTime();
    }
}

BOOL loadSequence(Sequence** out, Pokemon* pokemon, SequenceWaza* wazas, s32 num) {
    u32 rnd;
    u16 id;
    u16 species;
    s32 i;

    species = pokemonGetStatus(pokemon, 0, 0x6E, 0);
    if (species == 0) {
        return FALSE;
    }
    id = pokemonGetStatus(NULL, species, 0x66, 0);
    if (id == 0) {
        return FALSE;
    }
    rnd = pokemonBiosGetRnd(pokemon);
    if ((*out = Sequence_LoadPokemon(id, rnd, pokemonGetStatus(pokemon, 0, 0xC1, 0) != 0)) == NULL) {
        return FALSE;
    }
    for (i = 0; i < num; i++) {
        if (Sequence_LoadWaza(*out, wazas[i].wazaID, wazas[i].kind, 0) == NULL) {
            return FALSE;
        }
    }
    return TRUE;
}

// Unknown function that was dead-stripped from the final link; it used its own 0.0f constant.
f32 pokemonWazaSequenceDisplayZero(void) {
    return 0.0f;
}

}
