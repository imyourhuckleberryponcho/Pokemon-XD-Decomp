#include <dolphin/types.h>

#pragma dont_inline on

struct Hero;
struct Pokemon { u8 data[0xC8]; };
struct PokemonData;
struct POKEMON_EVOLUTION_INFO { u8 kind; u8 reserved; u16 parameter; };
static const u16 shedinjaName[6] = { 0x30CC, 0x30B1, 0x30CB, 0x30F3, 0, 0 };

extern "C" {
u32 heroGetStatus(Hero*, u16, u16);
u8 pokemonCheckValid(Pokemon*);
void heroAddPokemon(Hero*, Pokemon*);
void memoDataSet(s32, Pokemon*);
void pokemonBiosCopy(Pokemon*, Pokemon*);
void pokemonBiosSetPokemonDataId(Pokemon*, u16);
void* pokemonBiosGetAttest(Pokemon*);
u8 gamedataAttestBiosGetLangareaId(void*);
u32 pokemonDataBiosGetName(PokemonData*);
u16* GSmsgGetGSchar(u32);
void pokemonBiosSetNicknamePtr(Pokemon*, const u16*);
const u16* pokemonBiosGetNicknamePtr(Pokemon*);
void pokemonBiosSetItemDataId(Pokemon*, u16);
void pokemonSetStatus(Pokemon*, u16, u16, u16, u32);
void pokemonInitJoutai(Pokemon*);
void pokemonResetBasisStatus(Pokemon*);
u8 pokemonDataCheckValid(void*, u16);
void* savedataGetStatus(s32, s32);
void* gamedataBiosGetGamedataAtttestPtr(void*);
s32 GScharCmp(const u16*, const u16*);
PokemonData* pokemonDataBiosGetPtr(u16);
void pokemonDoItemSoubi(Pokemon*, u16, s32);
u8 pokemonBiosGetLevel(Pokemon*);
u16 pokemonGetOboeWazaDataId(Pokemon*, u8, u8*);
s8 pokemonSearchWazaDataId(Pokemon*, u16);
u32 pokemonBiosGetRnd(Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
u8 pokemonDataBiosGetSinkaKind(PokemonData*, u16);
u16 pokemonDataBiosGetSinkaBuff(PokemonData*, u16);
u16 pokemonDataBiosGetSinkaPokemonDataId(PokemonData*, u16);
u16 pokemonBiosGetItemDataId(Pokemon*);
u16 pokemonBiosGetFriend(Pokemon*);
u16 pokemonBiosGetPhyAtk(Pokemon*);
u16 pokemonBiosGetPhyDef(Pokemon*);
u8 pokemonBiosGetBeautiful(Pokemon*);
u8 fightIsFight();
void* fightFloorGetGcHeroFightTrainerPtr(s32);
Hero* fightTrainerGetStatus(void*, s32, u16, u16);
u8 heroItemCheckHaveItemDataId(Hero*, u16);
u16 pokemonGetSoubiItemDataId(Pokemon*);
void* itemDataBiosGetPtr(u16);
u16 itemDataBiosGetItemSoubiDataId(void*);
void fadeSet(s32, f32);
void fadeCheck(s32);
s32 evolutionOpen(Pokemon*, Pokemon*, s32, u16*, s32, u8*);
void pokemonWazaCreate(Pokemon*, u8, u16);
void heroItemDecItemDataId(Hero*, u16, s32, s32);
s32 pokemonEvolutionCreateAddPokemon(Pokemon*, Pokemon*, u16);
s32 pokemonEvolution(Pokemon*, Pokemon*, u16, POKEMON_EVOLUTION_INFO*, u16*);
}
static PokemonData* getPokemonData(Pokemon*);

static s8 getEmptySlotID(Hero* hero) {
    int i;
    for (i = 0; i < 6; i++) {
        if (!pokemonCheckValid((Pokemon*)heroGetStatus(hero, 3, i))) break;
    }
    if (i >= 6) return -1;
    return (s8)i;
}
static void evolutionAddPokemon(Pokemon* pokemon, u16 species, Hero* hero, int writeMemo) {
    Pokemon added;
    if (species && getEmptySlotID(hero) >= 0) {
        pokemonEvolutionCreateAddPokemon(&added, pokemon, species);
        heroAddPokemon(hero, &added);
        if (writeMemo) memoDataSet(0, &added);
    }
}
extern "C" s32 pokemonEvolutionAll(Pokemon* pokemon, u16 species, u16 extraSpecies,
    POKEMON_EVOLUTION_INFO* info, Hero* hero, int writeMemo, int mode, int fade) {
    int i;
    int count;
    Pokemon evolved;
    u16 moves[20];
    u16 shownMoves[20];
    u8 selected[20];
    if (!pokemonCheckValid(pokemon)) return 2;
    if (!species) return 2;
    count = pokemonEvolution(&evolved, pokemon, species, info, moves);
    if (count < 0) return 2;
    if (fade) { fadeSet(3, 0.5f); fadeCheck(1); }
    for (i = 0; i < count; i++) shownMoves[i] = moves[i];
    s32 result = evolutionOpen(pokemon, &evolved, mode, shownMoves, count, selected);
    if (fade) { fadeSet(2, 0.5f); fadeCheck(1); }
    if (result == 2) return 2;
    if (result == 1) return 1;
    if (writeMemo) memoDataSet(0, &evolved);
    pokemonBiosCopy(pokemon, &evolved);
    for (i = 0; i < count; i++) {
        if (selected[i] != 0xFF) pokemonWazaCreate(pokemon, selected[i], moves[i]);
    }
    if (extraSpecies) evolutionAddPokemon(pokemon, extraSpecies, hero, writeMemo);
    if (info->kind == 16) {
        Hero* itemHero = 0;
        void* trainer; if (fightIsFight() && (trainer = fightFloorGetGcHeroFightTrainerPtr(0)))
            itemHero = fightTrainerGetStatus(trainer, 0, 0x44, 0);
        heroItemDecItemDataId(itemHero, info->parameter, 1, -1);
    }
    return 0;
}
extern "C" s32 pokemonEvolutionCreateAddPokemon(Pokemon* destination, Pokemon* source, u16 species) {
    int i;
    PokemonData* data;
    u16 contestStatus[5] = {0xB0, 0xB1, 0xB2, 0xB3, 0xB4};
    u16 ribbonStatus[12] = {0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE};
    if (!pokemonDataCheckValid(0, species)) return 0;
    if (!getPokemonData(source)) return 0;
    pokemonBiosCopy(destination, source);
    pokemonBiosSetPokemonDataId(destination, species);
    data = getPokemonData(destination);
    if (!data) return 0;
    if (species != 0x12F) {
        u16* name = GSmsgGetGSchar(pokemonDataBiosGetName(data));
        pokemonBiosSetNicknamePtr(destination, name);
    } else {
        switch (gamedataAttestBiosGetLangareaId(pokemonBiosGetAttest(destination))) {
        case 1: pokemonBiosSetNicknamePtr(destination, shedinjaName); break;
        default: pokemonBiosSetNicknamePtr(destination, GSmsgGetGSchar(pokemonDataBiosGetName(data))); break;
        }
    }
    pokemonBiosSetItemDataId(destination, 0);
    pokemonSetStatus(destination, 0, 0xBB, 0, 0);
    pokemonSetStatus(destination, 0, 0xBE, 0, 0);
    for (i = 0; i < 5; i++) pokemonSetStatus(destination, 0, contestStatus[i], 0, 0);
    for (i = 0; i < 12; i++) pokemonSetStatus(destination, 0, ribbonStatus[i], 0, 0);
    pokemonSetStatus(destination, 0, 0xAF, 0, 0);
    pokemonInitJoutai(destination);
    pokemonSetStatus(destination, 0, 0xBC, 0, 0);
    pokemonResetBasisStatus(destination);
    return 1;
}
extern "C" s32 pokemonEvolution(Pokemon* destination, Pokemon* source, u16 species,
    POKEMON_EVOLUTION_INFO* info, u16* moves) {
    u8 level;
    u32 language;
    u16 move;
    const u16* nickname;
    PokemonData* data;
    void* attest;
    s32 count = 0;
    if (!pokemonCheckValid(source)) return -1;
    if (!pokemonDataCheckValid(0, species)) return -1;
    data = getPokemonData(source);
    if (!data) return -1;
    pokemonBiosCopy(destination, source);
    attest = pokemonBiosGetAttest(source);
    language = gamedataAttestBiosGetLangareaId(gamedataBiosGetGamedataAtttestPtr(savedataGetStatus(0, 1)));
    u32 originalLanguage = gamedataAttestBiosGetLangareaId(attest);
    if (originalLanguage == language) {
        nickname = pokemonBiosGetNicknamePtr(destination);
        const u16* name = GSmsgGetGSchar(pokemonDataBiosGetName(data));
        if (GScharCmp(nickname, name) == 0) {
            const u16* newName = GSmsgGetGSchar(pokemonDataBiosGetName(pokemonDataBiosGetPtr(species)));
            pokemonBiosSetNicknamePtr(destination, newName);
        }
    }
    pokemonBiosSetPokemonDataId(destination, species);
    pokemonResetBasisStatus(destination);
    if (info->kind == 6) pokemonDoItemSoubi(destination, 0, 0);
    level = pokemonBiosGetLevel(destination);
    u8 index = 0;
    while ((move = pokemonGetOboeWazaDataId(destination, level, &index)) != 0) {
        if (pokemonSearchWazaDataId(destination, move) == -1) {
            moves[count++] = move;
            if (count >= 20) break;
        }
        index++;
    }
    return count;
}
static s8 getTemotiEmptySlotID() {
    int i;
    for (i = 0; i < 6; i++) if (!pokemonCheckValid((Pokemon*)heroGetStatus(0, 3, i))) break;
    if (i >= 6) return -1;
    return (s8)i;
}
static u32 getUniqueRandom(Pokemon* pokemon) { return (pokemonBiosGetRnd(pokemon) >> 16) % 10; }
static s32 getNoon() { return 2; }
static PokemonData* getPokemonData(Pokemon* pokemon) {
    u16 species = pokemonBiosGetPokemonDataId(pokemon);
    if (species == 0) { return 0; } else { return pokemonDataBiosGetPtr(species); }
}
static u16 getEvoPokemonCommunication(Pokemon* pokemon, POKEMON_EVOLUTION_INFO* info) {
    int i;
    u16 result = 0;
    PokemonData* data;
    data = getPokemonData(pokemon);
    if (!data) return 0xFFFF;
    for (i = 0; i < 5; i++) {
        u8 kind = pokemonDataBiosGetSinkaKind(data, i);
        u16 parameter = pokemonDataBiosGetSinkaBuff(data, i);
        switch (kind) {
        case 5:
            result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
            info->kind = kind; info->parameter = parameter;
            break;
        case 6:
            if (parameter == pokemonBiosGetItemDataId(pokemon)) {
                result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter;
            }
            break;
        }
    }
    return result;
}
static u16 getEvoPokemonItem(Pokemon* pokemon, u16 item, POKEMON_EVOLUTION_INFO* info) {
    int i;
    u16 result = 0;
    PokemonData* data;
    data = getPokemonData(pokemon);
    if (!data) return 0xFFFF;
    for (i = 0; i < 5; i++) {
        u8 kind = pokemonDataBiosGetSinkaKind(data, i);
        u16 parameter = pokemonDataBiosGetSinkaBuff(data, i);
        switch (kind) { case 7: if (parameter == item) {
            result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
            info->kind = kind; info->parameter = parameter;
        } break; }
    }
    return result;
}
static u16 getEvoPokemonLevelUp(Pokemon* pokemon, u16* extra, POKEMON_EVOLUTION_INFO* info) {
    int i;
    PokemonData* data;
    u16 result = 0;
    u16 extraSpecies = 0;
    data = getPokemonData(pokemon);
    if (!data) return 0xFFFF;
    for (i = 0; i < 5; i++) {
        u8 kind = pokemonDataBiosGetSinkaKind(data, i);
        u16 parameter = pokemonDataBiosGetSinkaBuff(data, i);
        switch (kind) {
        case 1:
            if (pokemonBiosGetFriend(pokemon) >= 220) {
                result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter;
            }
            break;
        case 2:
            if (pokemonBiosGetFriend(pokemon) >= 220 && getNoon() == 1) {
                result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter;
            }
            break;
        case 3:
            if (pokemonBiosGetFriend(pokemon) >= 220 && getNoon() == 0) {
                result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter;
            }
            break;
        case 4:
            if (pokemonBiosGetLevel(pokemon) >= parameter) {
                result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter;
            }
            break;
        case 8:
            if (pokemonBiosGetLevel(pokemon) >= parameter) {
                u32 attack = pokemonBiosGetPhyAtk(pokemon);
                if (pokemonBiosGetPhyDef(pokemon) < attack) { result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter; }
            }
            break;
        case 9:
            if (pokemonBiosGetLevel(pokemon) >= parameter) {
                u32 attack = pokemonBiosGetPhyAtk(pokemon);
                u32 defense = pokemonBiosGetPhyDef(pokemon); if (defense == attack) { result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter; }
            }
            break;
        case 10:
            if (pokemonBiosGetLevel(pokemon) >= parameter) {
                u32 attack = pokemonBiosGetPhyAtk(pokemon);
                if (pokemonBiosGetPhyDef(pokemon) > attack) { result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter; }
            }
            break;
        case 11:
            if (pokemonBiosGetLevel(pokemon) >= parameter && getUniqueRandom(pokemon) < 5) { result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter; }
            break;
        case 12:
            if (pokemonBiosGetLevel(pokemon) >= parameter && getUniqueRandom(pokemon) >= 5) { result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter; }
            break;
        case 14:
            if (pokemonBiosGetLevel(pokemon) >= parameter && getTemotiEmptySlotID() >= 0)
                extraSpecies = pokemonDataBiosGetSinkaPokemonDataId(data, i);
            break;
        case 15:
            if (pokemonBiosGetBeautiful(pokemon) >= parameter) {
result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter;
            }
            break;
        case 16:
            if (pokemonBiosGetFriend(pokemon) >= 220) {
                Hero* hero = 0;
                void* trainer; if (fightIsFight() && (trainer = fightFloorGetGcHeroFightTrainerPtr(0))) hero = fightTrainerGetStatus(trainer, 0, 0x44, 0);
                if (heroItemCheckHaveItemDataId(hero, parameter)) {
result = pokemonDataBiosGetSinkaPokemonDataId(data, i);
                info->kind = kind; info->parameter = parameter;
                }
            }
            break;
        }
    }
    *extra = extraSpecies;
    return result;
}
static u16 getItemSoubiDataID(Pokemon* pokemon) {
    u16 item = pokemonGetSoubiItemDataId(pokemon);
    if (item == 0) { return 0; } else { return itemDataBiosGetItemSoubiDataId(itemDataBiosGetPtr(item)); }
}
extern "C" u16 pokemonEvolutionCheck(Pokemon* pokemon, s32 mode, u16 item,
    u16* extra, POKEMON_EVOLUTION_INFO* info) {
    u16 added = 0;
    u16 result;
    if (!pokemonCheckValid(pokemon)) return 0xFFFF;
    if (getItemSoubiDataID(pokemon) == 0x26) { *extra = added; return 0; }
    switch (mode) {
    case 0: result = getEvoPokemonLevelUp(pokemon, &added, info); break;
    case 1: result = getEvoPokemonItem(pokemon, item, info); break;
    case 2: result = getEvoPokemonCommunication(pokemon, info); break;
    default: result = 0xFFFF; break;
    }
    *extra = added;
    return result;
}



