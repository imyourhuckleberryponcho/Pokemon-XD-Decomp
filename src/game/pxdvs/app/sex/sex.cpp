#include <dolphin/types.h>

struct SexData {
    u8 raitoKotei;
    u8 unk1[7];
};

extern "C" {

extern SexData sex_data[];

u8 sexGetPokemonSexRaitoKotei(u16 id) { return sex_data[id].raitoKotei; }

}
