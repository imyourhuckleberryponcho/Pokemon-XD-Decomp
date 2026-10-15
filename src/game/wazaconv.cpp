#include <dolphin/types.h>
#include <libc/string.h>

#pragma peephole off

struct WazaData;
struct Pokemon;

extern "C" {
Pokemon* heroBiosGetPokemonPtr(void* hero, u16 index);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon* pokemon, u16 index);
WazaData* wazaDataBiosGetPtr(u16 id);
u32 wazaDataBiosGetDoc(WazaData* waza);
const u16* GSmsgGetGSchar(u32 msgID);
void* gamedataGetStatus(void*, s32);
s32 GBAMakeFromGSchar(u8* dst, const u16* src, void* gamedata);
s32 GetWazaDocGBA(u8* out, u16 wazaID);
}

static s32 convline(u8* out, const u16** src);

extern "C" {

s32 wazaconv(void* hero, u8* out) {
    s32 i;
    s32 j;
    s32 result;
    for (i = 0; i < 6; i++) {
        Pokemon* pokemon = heroBiosGetPokemonPtr(hero, i);
        for (j = 0; j < 4; j++) {
            u16 wazaID = pokemonBiosGetPokemonWazaDataId(pokemon, j);
            result = GetWazaDocGBA(out, wazaID);
            if (result != 0) {
                return result;
            }
            out += 0x50;
        }
    }
    return 0;
}

s32 GetWazaDocGBA(u8* out, u16 wazaID) {
    const u16* doc;
    WazaData* waza = wazaDataBiosGetPtr(wazaID);
    memset(out, 0, 0x50);
    if (waza != NULL) {
        doc = GSmsgGetGSchar(wazaDataBiosGetDoc(waza));
        out += convline(out, &doc);
        if (*doc == 0xFFFF) {
            *out++ = 0xFE;
            doc = (const u16*)((const u8*)doc + 3);
            out += convline(out, &doc);
        }
        *out = 0xFF;
    }
    return 0;
}

}

static s32 convline(u8* out, const u16** src) {
    u16 buf[88];
    s32 n = 0;
    u32 c;
    while ((c = **src) != 0 && c != 0xFFFF) {
        if (n < 0x50) {
            buf[n++] = c;
        }
        (*src)++;
    }
    buf[n] = 0;
    return GBAMakeFromGSchar(out, buf, gamedataGetStatus(0, 5));
}
