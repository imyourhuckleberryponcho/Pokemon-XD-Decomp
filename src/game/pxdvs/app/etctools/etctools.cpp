#include <game/pxdvs/app/pokemon/pokemonBios.hpp>

extern "C" {

void GSsndPlay(u32 id, s32, s32);

void etctoolSetPokemonNakigoe(u16 pokeNum) {
    PokemonData* data = pokemonDataBiosGetPtr(pokeNum);
    if (data != NULL) {
        GSsndPlay(pokemonDataBiosGetVoice(data), 0, 0);
    }
}

}
