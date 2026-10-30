#include <dolphin/types.h>
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#pragma peephole off
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct Attest;
struct GBAPokemon;
struct GamedataAttest;
struct Pokemon;

extern "C" {
struct Attest {
    u8 _draft[1];
};
struct GBAPokemon {
    u32 rnd;
    u32 trainerRnd;
    u8 nickname[10];
    u8 language;
    u8 flagAmari : 5;
    u8 isEgg : 1;
    u8 hasSpecies : 1;
    u8 badEgg : 1;
    u8 trainerName[7];
    u8 mark;
    u16 checksum;
    u16 amari;
    union {
        u8 raw[48];
        u16 half[24];
        u32 word[12];
        struct {
            u16 species;
            u16 item;
            u32 exp;
            u8 ppCount;
            u8 friendship;
            u16 amari;
            u16 waza[4];
            u8 pp[4];
            u8 effort[6];
            u8 contest[6];
            u32 misc;
            u32 rndValue;
            u32 ribbon;
        } s;
    } data;
    u32 condition;
    u8 level;
    u8 mail;
    u16 hp;
    u16 maxHp;
    u16 phyAtk;
    u16 phyDef;
    u16 nimbleness;
    u16 speAtk;
    u16 speDef;
};

union GBAMisc {
    struct {
        u32 trainerSex : 1;
        u32 ball : 4;
        u32 version : 4;
        u32 level : 7;
        u32 floor : 8;
        u32 pokerus : 8;
    } b;
    u32 raw;
};
union GBARnd {
    struct {
        u32 tokusei : 1;
        u32 tamago : 1;
        u32 speDef : 5;
        u32 speAtk : 5;
        u32 nimbleness : 5;
        u32 phyDef : 5;
        u32 phyAtk : 5;
        u32 maxHp : 5;
    } b;
    u32 raw;
};
union GBARibbon {
    struct {
        u32 eventGet : 1;
        u32 amari : 4;
        u32 world : 1;
        u32 earth : 1;
        u32 national : 1;
        u32 country : 1;
        u32 sky : 1;
        u32 land : 1;
        u32 marine : 1;
        u32 ganba : 1;
        u32 bromide : 1;
        u32 victory : 1;
        u32 winning : 1;
        u32 champ : 1;
        u32 strongMedal : 3;
        u32 cleverMedal : 3;
        u32 cuteMedal : 3;
        u32 beautifulMedal : 3;
        u32 styleMedal : 3;
    } b;
    u32 raw;
};
struct GamedataAttest {
    u8 _draft[1];
};
struct Pokemon {
    u8 unk0[0x4E];
    u16 nickname[11];
};

extern "C" {
s32 GBAMakeFromGSchar(u8* dst, const u16* src, s32 langarea);
void GScharMakeFromGBA(u16* dst, u8* src, s32 len, s32 lang);
u8 gamedataAttestBiosGetLangareaId(GamedataAttest* attest);
u8 gamedataAttestBiosGetVerId(GamedataAttest* attest);
void gamedataAttestCreate(GamedataAttest* ptr, u8 ver, u8 gen, u8 area, u8 langarea);
u16 gbaPokemonConditonFromGC(void *p0);
void gbaPokemonConditonToGC(void *p0, u16 p1);
void* memcpy(void* dst, const void* src, size_t n);
void* memmove(void* dst, const void* src, size_t len);
void* memset(void* dst, int val, size_t n);
u16 pokemonBiosGetAmari(Pokemon* poke);
u8 pokemonBiosGetAmariRibbon(Pokemon* poke);
Attest* pokemonBiosGetAttest(Pokemon* poke);
u8 pokemonBiosGetBeautiful(Pokemon* poke);
u8 pokemonBiosGetBeautifulMedal(Pokemon* poke);
u8 pokemonBiosGetBromideRibbon(Pokemon* poke);
u8 pokemonBiosGetCatchBallId(Pokemon* poke);
u16 pokemonBiosGetCatchFloorId(Pokemon* poke);
u8 pokemonBiosGetCatchLevel(Pokemon* poke);
char* pokemonBiosGetCatchTrainerNamePtr(Pokemon* poke);
u32 pokemonBiosGetCatchTrainerRnd(Pokemon* poke);
u8 pokemonBiosGetCatchTrainerSex(Pokemon* poke);
u8 pokemonBiosGetChampRibbon(Pokemon* poke);
u8 pokemonBiosGetClever(Pokemon* poke);
u8 pokemonBiosGetCleverMedal(Pokemon* poke);
u32 pokemonBiosGetConditionAmari(Pokemon* poke);
u8 pokemonBiosGetCountryRibbon(Pokemon* poke);
u8 pokemonBiosGetCute(Pokemon* poke);
u8 pokemonBiosGetCuteMedal(Pokemon* poke);
u8 pokemonBiosGetEarthRibbon(Pokemon* poke);
u32 pokemonBiosGetEventGetFlag(Pokemon* poke);
u32 pokemonBiosGetExp(Pokemon* poke);
u8 pokemonBiosGetFlagAmari(Pokemon* poke);
u16 pokemonBiosGetFriend(Pokemon* poke);
u8 pokemonBiosGetFur(Pokemon* poke);
u8 pokemonBiosGetFuseiFlag(Pokemon* poke);
u8 pokemonBiosGetGanbaRibbon(Pokemon* poke);
u16 pokemonBiosGetHp(Pokemon* poke);
u16 pokemonBiosGetItemDataId(Pokemon* poke);
u8 pokemonBiosGetLandRibbon(Pokemon* poke);
u8 pokemonBiosGetLevel(Pokemon* poke);
u8 pokemonBiosGetMailId(Pokemon* poke);
u8 pokemonBiosGetMarineRibbon(Pokemon* poke);
u16 pokemonBiosGetMaxHp(Pokemon* poke);
u16 pokemonBiosGetMaxHpEffort(Pokemon* poke);
u16 pokemonBiosGetMaxHpRnd(Pokemon* poke);
u8 pokemonBiosGetNationalRibbon(Pokemon* poke);
char* pokemonBiosGetNicknameOrgPtr(Pokemon* poke);
u16 pokemonBiosGetNimbleness(Pokemon* poke);
u16 pokemonBiosGetNimblenessEffort(Pokemon* poke);
u16 pokemonBiosGetNimblenessRnd(Pokemon* poke);
u16 pokemonBiosGetPara1Amari(Pokemon* poke);
u8 pokemonBiosGetPcboxMark(Pokemon* poke);
u16 pokemonBiosGetPhyAtk(Pokemon* poke);
u16 pokemonBiosGetPhyAtkEffort(Pokemon* poke);
u16 pokemonBiosGetPhyAtkRnd(Pokemon* poke);
u16 pokemonBiosGetPhyDef(Pokemon* poke);
u16 pokemonBiosGetPhyDefEffort(Pokemon* poke);
u16 pokemonBiosGetPhyDefRnd(Pokemon* poke);
u16 pokemonBiosGetPokemonDataId(Pokemon* poke);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon* poke, u16 wazaNum);
u8 pokemonBiosGetPokemonWazaPp(Pokemon* poke, u16 wazaNum);
u8 pokemonBiosGetPokemonWazaPpCount(Pokemon* poke, u16 wazaNum);
u8 pokemonBiosGetPokerus(Pokemon* poke);
u32 pokemonBiosGetRnd(Pokemon* poke);
u8 pokemonBiosGetSkyRibbon(Pokemon* poke);
u16 pokemonBiosGetSpeAtk(Pokemon* poke);
u16 pokemonBiosGetSpeAtkEffort(Pokemon* poke);
u16 pokemonBiosGetSpeAtkRnd(Pokemon* poke);
u16 pokemonBiosGetSpeDef(Pokemon* poke);
u16 pokemonBiosGetSpeDefEffort(Pokemon* poke);
u16 pokemonBiosGetSpeDefRnd(Pokemon* poke);
u8 pokemonBiosGetStrong(Pokemon* poke);
u8 pokemonBiosGetStrongMedal(Pokemon* poke);
u8 pokemonBiosGetStyle(Pokemon* poke);
u8 pokemonBiosGetStyleMedal(Pokemon* poke);
u8 pokemonBiosGetTamagoFlag(Pokemon* poke);
u8 pokemonBiosGetTokuseiFlag(Pokemon* poke);
u8 pokemonBiosGetVictoryRibbon(Pokemon* poke);
u8 pokemonBiosGetWinningRibbon(Pokemon* poke);
u8 pokemonBiosGetWorldRibbon(Pokemon* poke);
void pokemonBiosSetAmari(Pokemon* poke, u16 data);
void pokemonBiosSetAmariRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetBeautiful(Pokemon* poke, u8 data);
void pokemonBiosSetBeautifulMedal(Pokemon* poke, u8 data);
void pokemonBiosSetBromideRibbon(Pokemon* poke, bool data);
void pokemonBiosSetCatchBallId(Pokemon* poke, u8 data);
void pokemonBiosSetCatchFloorId(Pokemon* poke, u16 data);
void pokemonBiosSetCatchLevel(Pokemon* poke, u8 data);
void pokemonBiosSetCatchTrainerRnd(Pokemon* poke, u32 data);
void pokemonBiosSetCatchTrainerSex(Pokemon* poke, u8 data);
void pokemonBiosSetChampRibbon(Pokemon* poke, bool data);
void pokemonBiosSetClever(Pokemon* poke, u8 data);
void pokemonBiosSetCleverMedal(Pokemon* poke, u8 data);
void pokemonBiosSetConditionAmari(Pokemon* poke, u32 data);
void pokemonBiosSetCountryRibbon(Pokemon* poke, bool data);
void pokemonBiosSetCute(Pokemon* poke, u8 data);
void pokemonBiosSetCuteMedal(Pokemon* poke, u8 data);
void pokemonBiosSetEarthRibbon(Pokemon* poke, bool data);
void pokemonBiosSetEventGetFlag(Pokemon* poke, bool data);
void pokemonBiosSetExp(Pokemon* poke, u32 data);
void pokemonBiosSetFlagAmari(Pokemon* poke, u8 data);
void pokemonBiosSetFriend(Pokemon* poke, u16 data);
void pokemonBiosSetFur(Pokemon* poke, u8 data);
void pokemonBiosSetFuseiFlag(Pokemon* poke, bool data);
void pokemonBiosSetGanbaRibbon(Pokemon* poke, bool data);
void pokemonBiosSetHp(Pokemon* poke, u16 data);
void pokemonBiosSetItemDataId(Pokemon* poke, u16 data);
void pokemonBiosSetLandRibbon(Pokemon* poke, bool data);
void pokemonBiosSetLevel(Pokemon* poke, u8 data);
void pokemonBiosSetMailId(Pokemon* poke, u8 data);
void pokemonBiosSetMarineRibbon(Pokemon* poke, bool data);
void pokemonBiosSetMaxHp(Pokemon* poke, u16 data);
void pokemonBiosSetMaxHpEffort(Pokemon* poke, u16 data);
void pokemonBiosSetMaxHpRnd(Pokemon* poke, u16 data);
void pokemonBiosSetNationalRibbon(Pokemon* poke, bool data);
void pokemonBiosSetNicknamePtr(Pokemon* poke, void* data);
void pokemonBiosSetNimbleness(Pokemon* poke, u16 data);
void pokemonBiosSetNimblenessEffort(Pokemon* poke, u16 data);
void pokemonBiosSetNimblenessRnd(Pokemon* poke, u16 data);
void pokemonBiosSetPara1Amari(Pokemon* poke, u16 data);
void pokemonBiosSetPcboxMark(Pokemon* poke, u8 data);
void pokemonBiosSetPhyAtk(Pokemon* poke, u16 data);
void pokemonBiosSetPhyAtkEffort(Pokemon* poke, u16 data);
void pokemonBiosSetPhyAtkRnd(Pokemon* poke, u16 data);
void pokemonBiosSetPhyDef(Pokemon* poke, u16 data);
void pokemonBiosSetPhyDefEffort(Pokemon* poke, u16 data);
void pokemonBiosSetPhyDefRnd(Pokemon* poke, u16 data);
void pokemonBiosSetPokemonDataId(Pokemon* poke, u16 data);
void pokemonBiosSetPokemonWazaDataId(Pokemon* poke, u16 wazaNum, u16 data);
void pokemonBiosSetPokemonWazaPp(Pokemon* poke, u16 wazaNum, u8 data);
void pokemonBiosSetPokemonWazaPpCount(Pokemon* poke, u16 wazaNum, u8 count);
void pokemonBiosSetPokerus(Pokemon* poke, u8 data);
void pokemonBiosSetRnd(Pokemon* poke, u32 data);
void pokemonBiosSetSkyRibbon(Pokemon* poke, bool data);
void pokemonBiosSetSpeAtk(Pokemon* poke, u16 data);
void pokemonBiosSetSpeAtkEffort(Pokemon* poke, u16 data);
void pokemonBiosSetSpeAtkRnd(Pokemon* poke, u16 data);
void pokemonBiosSetSpeDef(Pokemon* poke, u16 data);
void pokemonBiosSetSpeDefEffort(Pokemon* poke, u16 data);
void pokemonBiosSetSpeDefRnd(Pokemon* poke, u16 data);
void pokemonBiosSetStrong(Pokemon* poke, u8 data);
void pokemonBiosSetStrongMedal(Pokemon* poke, u8 data);
void pokemonBiosSetStyle(Pokemon* poke, u8 data);
void pokemonBiosSetStyleMedal(Pokemon* poke, u8 data);
void pokemonBiosSetTamagoFlag(Pokemon* poke, bool data);
void pokemonBiosSetTokuseiFlag(Pokemon* poke, bool data);
void pokemonBiosSetVictoryRibbon(Pokemon* poke, bool data);
void pokemonBiosSetWinningRibbon(Pokemon* poke, bool data);
void pokemonBiosSetWorldRibbon(Pokemon* poke, bool data);
bool pokemonCheckValid(Pokemon* pokemon);
s16 pokemonGetCountAsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
s8 pokemonGetKaisuuJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
void pokemonInit(Pokemon* pokemon);
bool pokemonIsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
void pokemonSetCountAsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId, s16 value);
void pokemonSetKaisuuJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId, s8 value);
void pokemonWriteJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId, u32 value);
}
extern "C++" {
static void _revrotatepp(unsigned char* p0, unsigned long p1);
static void _rotatepp(unsigned char* p0, unsigned long p1);
static u16 _swap16(unsigned short p0);
static u32 _swap32(u32 value);
}

extern "C" {
extern "C" {

extern "C" {

extern "C" {
void gbaPokemonFromGC(Pokemon* pokemon, GBAPokemon* gba);
void gbaPokemonToGC(Pokemon* pokemon, GBAPokemon* gbaPokemon);
}

void gbaPokemonFromGC(Pokemon* pokemon, GBAPokemon* gba) {
    GamedataAttest* attest;
    u32* data;
    GBAMisc misc;
    GBARnd rnd;
    GBARibbon ribbon;
    u16 sum = 0;
    int i;

    memset(gba, 0, sizeof(GBAPokemon));
    if (pokemonCheckValid(pokemon) == 0) {
        return;
    }
    gba->rnd = _swap32(pokemonBiosGetRnd(pokemon));
    gba->trainerRnd = _swap32(pokemonBiosGetCatchTrainerRnd(pokemon));
    attest = (GamedataAttest*)pokemonBiosGetAttest(pokemon);
    switch (gamedataAttestBiosGetVerId(attest)) {
    case 8:
        misc.b.version = 1;
        break;
    case 9:
        misc.b.version = 2;
        break;
    case 10:
        misc.b.version = 3;
        break;
    case 1:
        misc.b.version = 4;
        break;
    case 2:
        misc.b.version = 5;
        break;
    case 11:
        misc.b.version = 15;
        break;
    default:
        misc.b.version = 0;
        break;
    }
    switch (gamedataAttestBiosGetLangareaId(attest)) {
    case 1:
        gba->language = 1;
        break;
    case 2:
        gba->language = 2;
        break;
    case 3:
        gba->language = 5;
        break;
    case 4:
        gba->language = 3;
        break;
    case 5:
        gba->language = 4;
        break;
    case 6:
        gba->language = 7;
        break;
    case 8:
        gba->language = 2;
        break;
    case 9:
        gba->language = 2;
        break;
    default:
        gba->language = 0;
        break;
    }
    gba->hasSpecies = 1;
    gba->isEgg = pokemonBiosGetTamagoFlag(pokemon) != 0;
    gba->flagAmari = pokemonBiosGetFlagAmari(pokemon);
    gba->badEgg = pokemonBiosGetFuseiFlag(pokemon) != 0;
    s32 len = GBAMakeFromGSchar(gba->nickname, (const u16*)pokemonBiosGetNicknameOrgPtr(pokemon), gamedataAttestBiosGetLangareaId(attest));
    if (len < 10) {
        gba->nickname[len] = 0xFF;
        memset((u8*)gba + len + 9, 0, 9 - len);
    }
    len = GBAMakeFromGSchar(gba->trainerName, (const u16*)pokemonBiosGetCatchTrainerNamePtr(pokemon), gamedataAttestBiosGetLangareaId(attest));
    if (len < 7) {
        gba->trainerName[len] = 0xFF;
        memset((u8*)gba + len + 0x15, 0, 6 - len);
    }
    gba->mark = pokemonBiosGetPcboxMark(pokemon);
    gba->amari = _swap16(pokemonBiosGetAmari(pokemon));
    gba->data.s.species = _swap16(pokemonBiosGetPokemonDataId(pokemon));
    gba->data.s.item = _swap16(pokemonBiosGetItemDataId(pokemon));
    gba->data.s.exp = _swap32(pokemonBiosGetExp(pokemon));
    gba->data.s.friendship = pokemonBiosGetFriend(pokemon);
    gba->data.s.amari = pokemonBiosGetPara1Amari(pokemon);
    gba->data.s.ppCount = 0;
    for (i = 0; i < 4; i++) {
        gba->data.s.waza[i] = _swap16(pokemonBiosGetPokemonWazaDataId(pokemon, i));
        gba->data.s.ppCount |= pokemonBiosGetPokemonWazaPpCount(pokemon, i) << (i * 2);
        gba->data.s.pp[i] = pokemonBiosGetPokemonWazaPp(pokemon, i);
    }
    gba->data.s.effort[0] = pokemonBiosGetMaxHpEffort(pokemon);
    gba->data.s.effort[1] = pokemonBiosGetPhyAtkEffort(pokemon);
    gba->data.s.effort[2] = pokemonBiosGetPhyDefEffort(pokemon);
    gba->data.s.effort[3] = pokemonBiosGetNimblenessEffort(pokemon);
    gba->data.s.effort[4] = pokemonBiosGetSpeAtkEffort(pokemon);
    gba->data.s.effort[5] = pokemonBiosGetSpeDefEffort(pokemon);
    gba->data.s.contest[0] = pokemonBiosGetStyle(pokemon);
    gba->data.s.contest[1] = pokemonBiosGetBeautiful(pokemon);
    gba->data.s.contest[2] = pokemonBiosGetCute(pokemon);
    gba->data.s.contest[3] = pokemonBiosGetClever(pokemon);
    gba->data.s.contest[4] = pokemonBiosGetStrong(pokemon);
    gba->data.s.contest[5] = pokemonBiosGetFur(pokemon);
    misc.b.pokerus = pokemonBiosGetPokerus(pokemon);
    misc.b.floor = pokemonBiosGetCatchFloorId(pokemon);
    misc.b.level = pokemonBiosGetCatchLevel(pokemon);
    misc.b.ball = pokemonBiosGetCatchBallId(pokemon);
    misc.b.trainerSex = pokemonBiosGetCatchTrainerSex(pokemon);
    rnd.b.maxHp = pokemonBiosGetMaxHpRnd(pokemon);
    rnd.b.phyAtk = pokemonBiosGetPhyAtkRnd(pokemon);
    rnd.b.phyDef = pokemonBiosGetPhyDefRnd(pokemon);
    rnd.b.nimbleness = pokemonBiosGetNimblenessRnd(pokemon);
    rnd.b.speAtk = pokemonBiosGetSpeAtkRnd(pokemon);
    rnd.b.speDef = pokemonBiosGetSpeDefRnd(pokemon);
    rnd.b.tamago = pokemonBiosGetTamagoFlag(pokemon) != 0;
    rnd.b.tokusei = pokemonBiosGetTokuseiFlag(pokemon) != 0;
    ribbon.b.styleMedal = pokemonBiosGetStyleMedal(pokemon);
    ribbon.b.beautifulMedal = pokemonBiosGetBeautifulMedal(pokemon);
    ribbon.b.cuteMedal = pokemonBiosGetCuteMedal(pokemon);
    ribbon.b.cleverMedal = pokemonBiosGetCleverMedal(pokemon);
    ribbon.b.strongMedal = pokemonBiosGetStrongMedal(pokemon);
    ribbon.b.champ = pokemonBiosGetChampRibbon(pokemon) != 0;
    ribbon.b.winning = pokemonBiosGetWinningRibbon(pokemon) != 0;
    ribbon.b.victory = pokemonBiosGetVictoryRibbon(pokemon) != 0;
    ribbon.b.bromide = pokemonBiosGetBromideRibbon(pokemon) != 0;
    ribbon.b.ganba = pokemonBiosGetGanbaRibbon(pokemon) != 0;
    ribbon.b.marine = pokemonBiosGetMarineRibbon(pokemon) != 0;
    ribbon.b.land = pokemonBiosGetLandRibbon(pokemon) != 0;
    ribbon.b.sky = pokemonBiosGetSkyRibbon(pokemon) != 0;
    ribbon.b.country = pokemonBiosGetCountryRibbon(pokemon) != 0;
    ribbon.b.national = pokemonBiosGetNationalRibbon(pokemon) != 0;
    ribbon.b.earth = pokemonBiosGetEarthRibbon(pokemon) != 0;
    ribbon.b.world = pokemonBiosGetWorldRibbon(pokemon) != 0;
    ribbon.b.amari = pokemonBiosGetAmariRibbon(pokemon);
    ribbon.b.eventGet = pokemonBiosGetEventGetFlag(pokemon);
    gba->condition = _swap32(gbaPokemonConditonFromGC(pokemon)) | (pokemonBiosGetConditionAmari(pokemon) & 0xFFFFF000);
    gba->level = pokemonBiosGetLevel(pokemon);
    gba->mail = pokemonBiosGetMailId(pokemon);
    gba->maxHp = _swap16(pokemonBiosGetMaxHp(pokemon));
    gba->hp = _swap16(pokemonBiosGetHp(pokemon));
    gba->phyAtk = _swap16(pokemonBiosGetPhyAtk(pokemon));
    gba->phyDef = _swap16(pokemonBiosGetPhyDef(pokemon));
    gba->nimbleness = _swap16(pokemonBiosGetNimbleness(pokemon));
    gba->speAtk = _swap16(pokemonBiosGetSpeAtk(pokemon));
    gba->speDef = _swap16(pokemonBiosGetSpeDef(pokemon));
    gba->data.s.misc = _swap32(misc.raw);
    gba->data.s.rndValue = _swap32(rnd.raw);
    gba->data.s.ribbon = _swap32(ribbon.raw);
    data = gba->data.word;
    u16* p = (u16*)data;
    for (i = 0; i < 24; i++) {
        sum += _swap16(*p);
        p++;
    }
    gba->checksum = _swap16(sum);
    for (i = 0; i < 12; i++) {
        *data ^= gba->rnd ^ gba->trainerRnd;
        data++;
    }
    _rotatepp(gba->data.raw, _swap32(gba->rnd));
}
}

extern "C" {
void gbaPokemonToGC(Pokemon* pokemon, GBAPokemon* gba) {
    GBAMisc misc;
    GBARnd rnd;
    GBARibbon ribbon;
    u16 name[11];
    u16* data;
    u16 sum = 0;
    int i;
    u8 ver;
    u8 area;
    u8 lang;

    pokemonInit(pokemon);
    if (!gba->hasSpecies && !gba->badEgg) {
        return;
    }
    data = gba->data.half;
    for (i = 0; i < 12; i++) {
        ((u32*)data)[i] ^= gba->rnd ^ gba->trainerRnd;
    }
    _revrotatepp(gba->data.raw, _swap32(gba->rnd));
    for (i = 0; i < 24; i++) {
        sum += _swap16(*data);
        data++;
    }
    misc.raw = _swap32(gba->data.s.misc);
    rnd.raw = _swap32(gba->data.s.rndValue);
    ribbon.raw = _swap32(gba->data.s.ribbon);
    pokemonBiosSetRnd(pokemon, _swap32(gba->rnd));
    pokemonBiosSetCatchTrainerRnd(pokemon, _swap32(gba->trainerRnd));
    switch (misc.b.version) {
    case 1:
        ver = 8;
        break;
    case 2:
        ver = 9;
        break;
    case 3:
        ver = 10;
        break;
    case 4:
        ver = 1;
        break;
    case 5:
        ver = 2;
        break;
    case 15:
        ver = 11;
        break;
    default:
        ver = 0;
        break;
    }
    switch (gba->language) {
    case 1:
        area = 1;
        lang = 1;
        break;
    case 2:
        area = 2;
        lang = 2;
        break;
    case 3:
        area = 3;
        lang = 4;
        break;
    case 4:
        area = 3;
        lang = 5;
        break;
    case 5:
        area = 3;
        lang = 3;
        break;
    case 7:
        area = 3;
        lang = 6;
        break;
    default:
        area = 0;
        lang = 0;
        break;
    }
    gamedataAttestCreate((GamedataAttest*)pokemonBiosGetAttest(pokemon), ver, 3, area, lang);
    GScharMakeFromGBA(name, gba->nickname, 10, lang);
    pokemonBiosSetNicknamePtr(pokemon, name);
    if (lang == 1) {
        pokemon->nickname[5] = 0;
    }
    pokemonBiosSetFlagAmari(pokemon, gba->flagAmari);
    pokemonBiosSetFuseiFlag(pokemon, gba->badEgg);
    GScharMakeFromGBA((u16*)pokemonBiosGetCatchTrainerNamePtr(pokemon), gba->trainerName, 7, lang);
    pokemonBiosSetPcboxMark(pokemon, gba->mark);
    pokemonBiosSetAmari(pokemon, _swap16(gba->amari));
    pokemonBiosSetPokemonDataId(pokemon, _swap16(gba->data.s.species));
    pokemonBiosSetItemDataId(pokemon, _swap16(gba->data.s.item));
    pokemonBiosSetExp(pokemon, _swap32(gba->data.s.exp));
    pokemonBiosSetFriend(pokemon, gba->data.s.friendship);
    pokemonBiosSetPara1Amari(pokemon, gba->data.s.amari);
    for (i = 0; i < 4; i++) {
        pokemonBiosSetPokemonWazaDataId(pokemon, i, _swap16(gba->data.s.waza[i]));
        pokemonBiosSetPokemonWazaPpCount(pokemon, i, (gba->data.s.ppCount >> (i * 2)) & 3);
        pokemonBiosSetPokemonWazaPp(pokemon, i, gba->data.s.pp[i]);
    }
    pokemonBiosSetMaxHpEffort(pokemon, gba->data.s.effort[0]);
    pokemonBiosSetPhyAtkEffort(pokemon, gba->data.s.effort[1]);
    pokemonBiosSetPhyDefEffort(pokemon, gba->data.s.effort[2]);
    pokemonBiosSetNimblenessEffort(pokemon, gba->data.s.effort[3]);
    pokemonBiosSetSpeAtkEffort(pokemon, gba->data.s.effort[4]);
    pokemonBiosSetSpeDefEffort(pokemon, gba->data.s.effort[5]);
    pokemonBiosSetStyle(pokemon, gba->data.s.contest[0]);
    pokemonBiosSetBeautiful(pokemon, gba->data.s.contest[1]);
    pokemonBiosSetCute(pokemon, gba->data.s.contest[2]);
    pokemonBiosSetClever(pokemon, gba->data.s.contest[3]);
    pokemonBiosSetStrong(pokemon, gba->data.s.contest[4]);
    pokemonBiosSetFur(pokemon, gba->data.s.contest[5]);
    pokemonBiosSetPokerus(pokemon, misc.b.pokerus);
    pokemonBiosSetCatchFloorId(pokemon, misc.b.floor);
    pokemonBiosSetCatchLevel(pokemon, misc.b.level);
    pokemonBiosSetCatchBallId(pokemon, misc.b.ball);
    pokemonBiosSetCatchTrainerSex(pokemon, misc.b.trainerSex);
    pokemonBiosSetMaxHpRnd(pokemon, rnd.b.maxHp);
    pokemonBiosSetPhyAtkRnd(pokemon, rnd.b.phyAtk);
    pokemonBiosSetPhyDefRnd(pokemon, rnd.b.phyDef);
    pokemonBiosSetNimblenessRnd(pokemon, rnd.b.nimbleness);
    pokemonBiosSetSpeAtkRnd(pokemon, rnd.b.speAtk);
    pokemonBiosSetSpeDefRnd(pokemon, rnd.b.speDef);
    pokemonBiosSetTamagoFlag(pokemon, rnd.b.tamago);
    pokemonBiosSetTokuseiFlag(pokemon, rnd.b.tokusei);
    pokemonBiosSetStyleMedal(pokemon, ribbon.b.styleMedal);
    pokemonBiosSetBeautifulMedal(pokemon, ribbon.b.beautifulMedal);
    pokemonBiosSetCuteMedal(pokemon, ribbon.b.cuteMedal);
    pokemonBiosSetCleverMedal(pokemon, ribbon.b.cleverMedal);
    pokemonBiosSetStrongMedal(pokemon, ribbon.b.strongMedal);
    pokemonBiosSetChampRibbon(pokemon, ribbon.b.champ);
    pokemonBiosSetWinningRibbon(pokemon, ribbon.b.winning);
    pokemonBiosSetVictoryRibbon(pokemon, ribbon.b.victory);
    pokemonBiosSetBromideRibbon(pokemon, ribbon.b.bromide);
    pokemonBiosSetGanbaRibbon(pokemon, ribbon.b.ganba);
    pokemonBiosSetMarineRibbon(pokemon, ribbon.b.marine);
    pokemonBiosSetLandRibbon(pokemon, ribbon.b.land);
    pokemonBiosSetSkyRibbon(pokemon, ribbon.b.sky);
    pokemonBiosSetCountryRibbon(pokemon, ribbon.b.country);
    pokemonBiosSetNationalRibbon(pokemon, ribbon.b.national);
    pokemonBiosSetEarthRibbon(pokemon, ribbon.b.earth);
    pokemonBiosSetWorldRibbon(pokemon, ribbon.b.world);
    pokemonBiosSetAmariRibbon(pokemon, ribbon.b.amari);
    pokemonBiosSetEventGetFlag(pokemon, ribbon.b.eventGet);
    gbaPokemonConditonToGC(pokemon, _swap32(gba->condition));
    pokemonBiosSetConditionAmari(pokemon, _swap32(gba->condition) & 0xFFFFF000);
    pokemonBiosSetLevel(pokemon, gba->level);
    pokemonBiosSetMailId(pokemon, gba->mail);
    pokemonBiosSetMaxHp(pokemon, _swap16(gba->maxHp));
    pokemonBiosSetHp(pokemon, _swap16(gba->hp));
    pokemonBiosSetPhyAtk(pokemon, _swap16(gba->phyAtk));
    pokemonBiosSetPhyDef(pokemon, _swap16(gba->phyDef));
    pokemonBiosSetNimbleness(pokemon, _swap16(gba->nimbleness));
    pokemonBiosSetSpeAtk(pokemon, _swap16(gba->speAtk));
    pokemonBiosSetSpeDef(pokemon, _swap16(gba->speDef));
}
}
u16 gbaPokemonConditonFromGC(void *p0) {
    u16 status = 0;

    if (pokemonIsJoutaiDataId((Pokemon*)p0, 4U) != 0) {
        status = (pokemonGetCountAsJoutaiDataId((Pokemon*)p0, 4U) << 8) | 0x80;
    } else if (pokemonIsJoutaiDataId((Pokemon*)p0, 5U) != 0) {
        status |= 0x40;
    } else if (pokemonIsJoutaiDataId((Pokemon*)p0, 7U) != 0) {
        status |= 0x20;
    } else if (pokemonIsJoutaiDataId((Pokemon*)p0, 6U) != 0) {
        status |= 0x10;
    } else if (pokemonIsJoutaiDataId((Pokemon*)p0, 3U) != 0) {
        status |= 0x08;
    } else if (pokemonIsJoutaiDataId((Pokemon*)p0, 8U) != 0) {
        status = (s16)pokemonGetKaisuuJoutaiDataId((Pokemon*)p0, 8U);
    }
    return status;
}
}

extern "C" {
void gbaPokemonConditonToGC(void* pokemon, u16 cond) {
    if (cond & 0x80) {
        pokemonWriteJoutaiDataId((Pokemon*)pokemon, 4, 0);
        pokemonSetCountAsJoutaiDataId((Pokemon*)pokemon, 4, (cond & 0xF00) >> 8);
        return;
    }
    if (cond & 0x40) {
        pokemonWriteJoutaiDataId((Pokemon*)pokemon, 5, 0);
        return;
    }
    if (cond & 0x20) {
        pokemonWriteJoutaiDataId((Pokemon*)pokemon, 7, 0);
        return;
    }
    if (cond & 0x10) {
        pokemonWriteJoutaiDataId((Pokemon*)pokemon, 6, 0);
        return;
    }
    if (cond & 0x08) {
        pokemonWriteJoutaiDataId((Pokemon*)pokemon, 3, 0);
        return;
    }
    s32 sleep = cond & 7;
    if (sleep != 0) {
        pokemonWriteJoutaiDataId((Pokemon*)pokemon, 8, 0);
        pokemonSetKaisuuJoutaiDataId((Pokemon*)pokemon, 8, sleep);
    }
}
}

extern "C++" {
static void _rotatepp(unsigned char* data, unsigned long order) {
    u8 tmp[12];
    u32 n;

    order %= 24;
    n = order / 6;
    if (n != 0) {
        n *= 12;
        memcpy(tmp, data + n, 12);
        memmove(data + 12, data, n);
        memcpy(data, tmp, 12);
    }
    order %= 6;
    n = order >> 1;
    if (n != 0) {
        n *= 12;
        memcpy(tmp, data + 12 + n, 12);
        memmove(data + 24, data + 12, n);
        memcpy(data + 12, tmp, 12);
    }
    if (order & 1) {
        memcpy(tmp, data + 36, 12);
        memcpy(data + 36, data + 24, 12);
        memcpy(data + 24, tmp, 12);
    }
}
}

extern "C++" {
static void _revrotatepp(unsigned char* data, unsigned long order) {
    u8 tmp[12];
    u32 n;

    if (order & 1) {
        memcpy(tmp, data + 24, 12);
        memcpy(data + 24, data + 36, 12);
        memcpy(data + 36, tmp, 12);
    }
    n = (order >> 1) % 3;
    if (n != 0) {
        memcpy(tmp, data + 12, 12);
        n *= 12;
        memmove(data + 12, data + 24, n);
        memcpy(data + 12 + n, tmp, 12);
    }
    n = (order / 6) % 4;
    if (n != 0) {
        memcpy(tmp, data, 12);
        n *= 12;
        memmove(data, data + 12, n);
        memcpy(data + n, tmp, 12);
    }
}
}

extern "C++" {
static u32 _swap32(unsigned long p0) {
    return (p0 >> 0x18U) | (((u32) (p0 & 0xFF0000) >> 8U) | ((p0 << 0x18) | ((p0 & 0xFF00) << 8)));
}
}

extern "C++" {
static u16 _swap16(unsigned short p0) {
    return (u16) ((p0 << 8) | ((s32) p0 >> 8));
}
}
}
}
