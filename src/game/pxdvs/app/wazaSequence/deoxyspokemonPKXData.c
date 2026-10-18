#include <dolphin/types.h>

struct PkxEntry {
    u32 a;
    u32 b;
};

struct PkxEntry deoxys_pokemon_pkx_data[] = {
    {0x00000386, 0x06681E00},
    {0x0000081B, 0x17C01E00},
    {0x0000081C, 0x17C11E00},
    {0x0000081D, 0x17C21E00},
};

u32 deoxys_pokemon_pkx_data_number = sizeof(deoxys_pokemon_pkx_data) / sizeof(deoxys_pokemon_pkx_data[0]);
