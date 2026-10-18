#include <dolphin/types.h>

struct PkxEntry {
    u32 a;
    u32 b;
};

struct PkxEntry rare_deoxys_pokemon_pkx_data[] = {
    {0x0000077E, 0x11A31E00},
    {0x0000081E, 0x17C31E00},
    {0x0000081F, 0x17C41E00},
    {0x00000820, 0x17C51E00},
};

u32 rare_deoxys_pokemon_pkx_data_number = sizeof(rare_deoxys_pokemon_pkx_data) / sizeof(rare_deoxys_pokemon_pkx_data[0]);
