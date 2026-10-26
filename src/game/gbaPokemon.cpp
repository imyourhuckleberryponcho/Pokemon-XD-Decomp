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
    u8 _draft[1];
};
struct GamedataAttest {
    u8 _draft[1];
};
struct Pokemon {
    u8 _draft[1];
};

extern "C" {
s32 GBAMakeFromGSchar(u8* dst, const u16* src, void* gamedata);
void GScharMakeFromGBA(u16* dst, u8* src, s32 len, void* gamedata);
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
u8 pokemonBiosGetEventGetFlag(Pokemon* poke);
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
u8 pokemonBiosGetMaxHpRnd(Pokemon* poke);
u8 pokemonBiosGetNationalRibbon(Pokemon* poke);
char* pokemonBiosGetNicknameOrgPtr(Pokemon* poke);
u16 pokemonBiosGetNimbleness(Pokemon* poke);
u16 pokemonBiosGetNimblenessEffort(Pokemon* poke);
u8 pokemonBiosGetNimblenessRnd(Pokemon* poke);
u16 pokemonBiosGetPara1Amari(Pokemon* poke);
u8 pokemonBiosGetPcboxMark(Pokemon* poke);
u16 pokemonBiosGetPhyAtk(Pokemon* poke);
u16 pokemonBiosGetPhyAtkEffort(Pokemon* poke);
u8 pokemonBiosGetPhyAtkRnd(Pokemon* poke);
u16 pokemonBiosGetPhyDef(Pokemon* poke);
u16 pokemonBiosGetPhyDefEffort(Pokemon* poke);
u8 pokemonBiosGetPhyDefRnd(Pokemon* poke);
u16 pokemonBiosGetPokemonDataId(Pokemon* poke);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon* poke, u32 wazaNum);
u8 pokemonBiosGetPokemonWazaPp(Pokemon* poke, u32 wazaNum);
u8 pokemonBiosGetPokemonWazaPpCount(Pokemon* poke, u32 wazaNum);
u8 pokemonBiosGetPokerus(Pokemon* poke);
u32 pokemonBiosGetRnd(Pokemon* poke);
u8 pokemonBiosGetSkyRibbon(Pokemon* poke);
u16 pokemonBiosGetSpeAtk(Pokemon* poke);
u16 pokemonBiosGetSpeAtkEffort(Pokemon* poke);
u8 pokemonBiosGetSpeAtkRnd(Pokemon* poke);
u16 pokemonBiosGetSpeDef(Pokemon* poke);
u16 pokemonBiosGetSpeDefEffort(Pokemon* poke);
u8 pokemonBiosGetSpeDefRnd(Pokemon* poke);
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
void pokemonBiosSetBromideRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetCatchBallId(Pokemon* poke, u8 data);
void pokemonBiosSetCatchFloorId(Pokemon* poke, u16 data);
void pokemonBiosSetCatchLevel(Pokemon* poke, u8 data);
void pokemonBiosSetCatchTrainerRnd(Pokemon* poke, u32 data);
void pokemonBiosSetCatchTrainerSex(Pokemon* poke, u8 data);
void pokemonBiosSetChampRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetClever(Pokemon* poke, u8 data);
void pokemonBiosSetCleverMedal(Pokemon* poke, u8 data);
void pokemonBiosSetConditionAmari(Pokemon* poke, u32 data);
void pokemonBiosSetCountryRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetCute(Pokemon* poke, u8 data);
void pokemonBiosSetCuteMedal(Pokemon* poke, u8 data);
void pokemonBiosSetEarthRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetEventGetFlag(Pokemon* poke, u32 data);
void pokemonBiosSetExp(Pokemon* poke, u32 data);
void pokemonBiosSetFlagAmari(Pokemon* poke, u8 data);
void pokemonBiosSetFriend(Pokemon* poke, u16 data);
void pokemonBiosSetFur(Pokemon* poke, u8 data);
void pokemonBiosSetFuseiFlag(Pokemon* poke, bool data);
void pokemonBiosSetGanbaRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetHp(Pokemon* poke, s16 data);
void pokemonBiosSetItemDataId(Pokemon* poke, u16 data);
void pokemonBiosSetLandRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetLevel(Pokemon* poke, u8 data);
void pokemonBiosSetMailId(Pokemon* poke, u8 data);
void pokemonBiosSetMarineRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetMaxHp(Pokemon* poke, u16 data);
void pokemonBiosSetMaxHpEffort(Pokemon* poke, u16 data);
void pokemonBiosSetMaxHpRnd(Pokemon* poke, u16 data);
void pokemonBiosSetNationalRibbon(Pokemon* poke, u8 data);
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
void pokemonBiosSetPokemonWazaDataId(Pokemon* poke, u32 wazaNum, u32 data);
void pokemonBiosSetPokemonWazaPp(Pokemon* poke, u32 wazaNum, u8 data);
void pokemonBiosSetPokemonWazaPpCount(Pokemon* poke, u32 wazaNum, u8 count);
void pokemonBiosSetPokerus(Pokemon* poke, u8 data);
void pokemonBiosSetRnd(Pokemon* poke, u32 data);
void pokemonBiosSetSkyRibbon(Pokemon* poke, u8 data);
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
void pokemonBiosSetVictoryRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetWinningRibbon(Pokemon* poke, u8 data);
void pokemonBiosSetWorldRibbon(Pokemon* poke, u8 data);
bool pokemonCheckValid(Pokemon* pokemon);
s16 pokemonGetCountAsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
s8 pokemonGetKaisuuJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
void pokemonInit(Pokemon* pokemon);
bool pokemonIsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
void pokemonSetCountAsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId, u32 value);
void pokemonSetKaisuuJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId, u32 value);
void pokemonWriteJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
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
void gbaPokemonFromGC(void *p0, void *p1);
void gbaPokemonToGC(Pokemon* pokemon, GBAPokemon* gbaPokemon);
}

void gbaPokemonFromGC(void *p0, void *p1) {
    s32 unksp11;
    u8 sp13;
    volatile u8 sp12;
    u16 sp10;
    u8 spF;
    u16 spE;
    s32 spC;
    u8 spB;
    u16 spA;
    volatile u8 sp9;
    u8 sp8;
    GamedataAttest *temp_r3;
    s32 temp_r31_2;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 var_ctr;
    u16 var_r28;
    u8 *var_r27;
    u16 *var_r27_2;
    u16 *var_r31_2;
    u16 var_r26;
    u8 temp_r0;
    bool temp_r0_10;
    u8 temp_r0_11;
    u8 temp_r0_12;
    u8 temp_r0_13;
    u8 temp_r0_14;
    s32 temp_r0_15;
    s32 temp_r0_16;
    u8 temp_r0_17;
    u8 temp_r0_2;
    s32 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r0_5;
    u8 temp_r0_6;
    u8 temp_r0_7;
    u8 temp_r0_8;
    u8 temp_r0_9;
    u8 temp_r3_2;
    s32 var_r31;
    u16 var_r29;

    var_r29 = 0;
    memset((void*)(p1), 0, 0x64U);
    if (pokemonCheckValid((Pokemon*)((Pokemon *) p0)) != 0) {
        M2C_FIELD(p1, u32 *, 0) = _swap32(pokemonBiosGetRnd((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u32 *, 4) = _swap32(pokemonBiosGetCatchTrainerRnd((Pokemon*)((Pokemon *) p0)));
        temp_r3 = (GamedataAttest *)(pokemonBiosGetAttest((Pokemon*)((Pokemon *) p0)));
        temp_r3_2 = gamedataAttestBiosGetVerId((GamedataAttest*)(temp_r3));
        switch (temp_r3_2) {
        case 8:
            sp10 = (sp10 & ~0x780) | 0x80;
            break;
        case 9:
            sp10 = (sp10 & ~0x780) | 0x100;
            break;
        case 10:
            sp10 = (sp10 & ~0x780) | 0x180;
            break;
        case 1:
            sp10 = (sp10 & ~0x780) | 0x200;
            break;
        case 2:
            sp10 = (sp10 & ~0x780) | 0x280;
            break;
        case 11:
            sp10 |= 0x780;
            break;
        default:
            sp10 &= ~0x780;
            break;
        }
        switch ((u8)(gamedataAttestBiosGetLangareaId((GamedataAttest*)(temp_r3)))) {
        case 1:
            M2C_FIELD(p1, s8 *, 0x12) = 1;
            break;
        case 2:
            M2C_FIELD(p1, s8 *, 0x12) = 2;
            break;
        case 3:
            M2C_FIELD(p1, s8 *, 0x12) = 5;
            break;
        case 4:
            M2C_FIELD(p1, s8 *, 0x12) = 3;
            break;
        case 5:
            M2C_FIELD(p1, s8 *, 0x12) = 4;
            break;
        case 6:
            M2C_FIELD(p1, s8 *, 0x12) = 7;
            break;
        case 8:
            M2C_FIELD(p1, s8 *, 0x12) = 2;
            break;
        case 9:
            M2C_FIELD(p1, s8 *, 0x12) = 2;
            break;
        default:
            M2C_FIELD(p1, s8 *, 0x12) = 0;
            break;
        }
        M2C_FIELD((u16)p1, u8 *, 0x13) = (u8) (M2C_FIELD(p1, u8 *, 0x13) | 2);
        M2C_FIELD(p1, u8 *, 0x13) = (u8) ((M2C_FIELD(p1, u8 *, 0x13) & ~4) | (((pokemonBiosGetTamagoFlag((Pokemon*)((Pokemon *) p0)) != 0) << 2) & 4));
        M2C_FIELD(p1, u8 *, 0x13) = (u8) ((M2C_FIELD(p1, u8 *, 0x13) & ~0xF8) | ((pokemonBiosGetFlagAmari((Pokemon*)((Pokemon *) p0)) << 3) & 0xF8));
        M2C_FIELD(p1, u8 *, 0x13) = (u8) ((M2C_FIELD(p1, u8 *, 0x13) & ~1) | ((pokemonBiosGetFuseiFlag((Pokemon*)((Pokemon *) p0)) != 0) & 1));
        temp_r3_4 = GBAMakeFromGSchar((u8*)(((u8*)(p1) + 8)), (const u16*)(pokemonBiosGetNicknameOrgPtr((Pokemon*)((Pokemon *) p0))), (void*)((u8 *) (u32)(gamedataAttestBiosGetLangareaId((GamedataAttest*)(temp_r3)))));
        if (temp_r3_4 < 0xA) {
            M2C_FIELD(((u8 *)p1 + temp_r3_4), s8 *, 8) = 0xFF;
            memset((void*)((u8*)(p1) + (temp_r3_4 + 9)), 0, 9 - temp_r3_4);
        }
        temp_r3_5 = GBAMakeFromGSchar((u8*)(((u8*)(p1) + 0x14)), (const u16*)(pokemonBiosGetCatchTrainerNamePtr((Pokemon*)((Pokemon *) p0))), (void*)((u8 *) (u8)(gamedataAttestBiosGetLangareaId((GamedataAttest*)(temp_r3)))));
        if (temp_r3_5 < 7) {
            M2C_FIELD(((u8 *)p1 + temp_r3_5), s8 *, 0x14) = 0xFF;
            memset((void*)((u8*)(p1) + (temp_r3_5 + 0x15)), 0, 6 - temp_r3_5);
        }
        M2C_FIELD(p1, u8 *, 0x1B) = pokemonBiosGetPcboxMark((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u16 *, 0x1E) = _swap16(pokemonBiosGetAmari((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u16 *, 0x20) = _swap16(pokemonBiosGetPokemonDataId((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u16 *, 0x22) = _swap16(pokemonBiosGetItemDataId((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u32 *, 0x24) = _swap32(pokemonBiosGetExp((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u8 *, 0x29) = pokemonBiosGetFriend((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u16 *, 0x2A) = pokemonBiosGetPara1Amari((Pokemon*)((Pokemon *) p0));
        var_r31 = 0;
        var_r27 = (unsigned char *)(p1);
        var_r26 = 0;
        M2C_FIELD(p1, u8 *, 0x28) = 0U;
        do {
            var_r27 += 2;
            M2C_FIELD(var_r27, u16 *, 0x2C) = _swap16(pokemonBiosGetPokemonWazaDataId((Pokemon*)((Pokemon *) p0), (u32) var_r26));
            M2C_FIELD(p1, u8 *, 0x28) = (u8) (M2C_FIELD(p1, u8 *, 0x28) | (pokemonBiosGetPokemonWazaPpCount((Pokemon*)((Pokemon *) p0), (u32) var_r26) << var_r31));
            *((u8*)(p1) + (var_r26 + 0x34)) = pokemonBiosGetPokemonWazaPp((Pokemon*)((Pokemon *) p0), (u32) var_r26);
            var_r31 += 2;
            var_r26 += 1;
        } while ((s32) var_r26 < 4);
        M2C_FIELD(p1, u8 *, 0x38) = pokemonBiosGetMaxHpEffort((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x39) = pokemonBiosGetPhyAtkEffort((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x3A) = pokemonBiosGetPhyDefEffort((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x3B) = pokemonBiosGetNimblenessEffort((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x3C) = pokemonBiosGetSpeAtkEffort((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x3D) = pokemonBiosGetSpeDefEffort((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x3E) = pokemonBiosGetStyle((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x3F) = pokemonBiosGetBeautiful((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x40) = pokemonBiosGetCute((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x41) = pokemonBiosGetClever((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x42) = pokemonBiosGetStrong((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x43) = pokemonBiosGetFur((Pokemon*)((Pokemon *) p0));
        sp13 = pokemonBiosGetPokerus((Pokemon*)((Pokemon *) p0));
        sp12 = pokemonBiosGetCatchFloorId((Pokemon*)((Pokemon *) p0));
        unksp11 = (unksp11 & ~0x7F) | (pokemonBiosGetCatchLevel((Pokemon*)((Pokemon *) p0)) & 0x7F);
        temp_r0 = ((u8) sp10 & ~0x78) | ((pokemonBiosGetCatchBallId((Pokemon*)((Pokemon *) p0)) << 3) & 0x78);
        sp10 = temp_r0;
        sp10 = (temp_r0 & ~0x80) | ((pokemonBiosGetCatchTrainerSex((Pokemon*)((Pokemon *) p0)) << 7) & 0x80);
        spF = (spF & ~0x1F) | (pokemonBiosGetMaxHpRnd((Pokemon*)((Pokemon *) p0)) & 0x1F);
        spE = (spE & ~0x3E0) | ((pokemonBiosGetPhyAtkRnd((Pokemon*)((Pokemon *) p0)) << 5) & 0x3E0);
        spC = temp_r0_2;
        spE = ((u8) spE & ~0x7C) | ((pokemonBiosGetPhyDefRnd((Pokemon*)((Pokemon *) p0)) << 2) & 0x7C);
        spC = (spC & ~0xF8000) | ((pokemonBiosGetNimblenessRnd((Pokemon*)((Pokemon *) p0)) << 0xF) & 0xF8000);
        spC = ((u16) spC & ~0x1F0) | ((pokemonBiosGetSpeAtkRnd((Pokemon*)((Pokemon *) p0)) << 4) & 0x1F0);
        temp_r0_2 = (spC & ~0x3E) | ((pokemonBiosGetSpeDefRnd((Pokemon*)((Pokemon *) p0)) << 1) & 0x3E);
        temp_r0_3 = (temp_r0_2 & ~0x40) | (((pokemonBiosGetTamagoFlag((Pokemon*)((Pokemon *) p0)) != 0) << 6) & 0x40);
        spC = temp_r0_3;
        spC = (temp_r0_3 & ~0x80) | (((pokemonBiosGetTokuseiFlag((Pokemon*)((Pokemon *) p0)) != 0) << 7) & 0x80);
        temp_r0_4 = (spB & ~7) | (pokemonBiosGetStyleMedal((Pokemon*)((Pokemon *) p0)) & 7);
        spB = temp_r0_4;
        spB = (temp_r0_4 & ~0x38) | ((pokemonBiosGetBeautifulMedal((Pokemon*)((Pokemon *) p0)) << 3) & 0x38);
        spA = (spA & ~0x1C0) | ((pokemonBiosGetCuteMedal((Pokemon*)((Pokemon *) p0)) << 6) & 0x1C0);
        temp_r0_5 = ((u8) spA & ~0xE) | ((pokemonBiosGetCleverMedal((Pokemon*)((Pokemon *) p0)) << 1) & 0xE);
        sp9 = temp_r0_7;
        spA = temp_r0_5;
        temp_r0_6 = (temp_r0_5 & ~0x70) | ((pokemonBiosGetStrongMedal((Pokemon*)((Pokemon *) p0)) << 4) & 0x70);
        sp9 = temp_r0_9;
        spA = temp_r0_6;
        spA = (temp_r0_6 & ~0x80) | (((pokemonBiosGetChampRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 7) & 0x80);
        sp9 = temp_r0_8;
        temp_r0_7 = (sp9 & ~1) | ((pokemonBiosGetWinningRibbon((Pokemon*)((Pokemon *) p0)) != 0) & 1);
        temp_r0_8 = (temp_r0_7 & ~2) | (((pokemonBiosGetVictoryRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 1) & 2);
        temp_r0_9 = (temp_r0_8 & ~4) | (((pokemonBiosGetBromideRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 2) & 4);
        temp_r0_10 = (temp_r0_9 & ~8) | (((pokemonBiosGetGanbaRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 3) & 8);
        sp9 = temp_r0_10;
        temp_r0_11 = (temp_r0_10 & ~0x10) | (((pokemonBiosGetMarineRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 4) & 0x10);
        sp9 = temp_r0_11;
        temp_r0_12 = (temp_r0_11 & ~0x20) | (((pokemonBiosGetLandRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 5) & 0x20);
        sp9 = temp_r0_12;
        temp_r0_13 = (temp_r0_12 & ~0x40) | (((pokemonBiosGetSkyRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 6) & 0x40);
        sp9 = temp_r0_13;
        sp9 = (temp_r0_13 & ~0x80) | (((pokemonBiosGetCountryRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 7) & 0x80);
        temp_r0_14 = (sp8 & ~1) | ((pokemonBiosGetNationalRibbon((Pokemon*)((Pokemon *) p0)) != 0) & 1);
        sp8 = temp_r0_14;
        temp_r0_15 = (temp_r0_14 & ~2) | (((pokemonBiosGetEarthRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 1) & 2);
        sp8 = temp_r0_15;
        temp_r0_16 = (temp_r0_15 & ~4) | (((pokemonBiosGetWorldRibbon((Pokemon*)((Pokemon *) p0)) != 0) << 2) & 4);
        sp8 = temp_r0_16;
        temp_r0_17 = (temp_r0_16 & ~0x78) | ((pokemonBiosGetAmariRibbon((Pokemon*)((Pokemon *) p0)) << 3) & 0x78);
        sp8 = temp_r0_17;
        sp8 = (temp_r0_17 & ~0x80) | ((pokemonBiosGetEventGetFlag((Pokemon*)((Pokemon *) p0)) << 7) & 0x80);
        temp_r31_2 = pokemonBiosGetConditionAmari((Pokemon*)((Pokemon *) p0)) & 0xFFFFF000;
        M2C_FIELD(p1, s32 *, 0x50) = (s32) (_swap32((u32) gbaPokemonConditonFromGC(p0)) | temp_r31_2);
        M2C_FIELD(p1, u8 *, 0x54) = pokemonBiosGetLevel((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u8 *, 0x55) = pokemonBiosGetMailId((Pokemon*)((Pokemon *) p0));
        M2C_FIELD(p1, u16 *, 0x58) = _swap16(pokemonBiosGetMaxHp((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u16 *, 0x56) = _swap16(pokemonBiosGetHp((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u16 *, 0x5A) = _swap16(pokemonBiosGetPhyAtk((Pokemon*)((Pokemon *) p0)));
        var_r31_2 = (unsigned short *)(((u8*)(p1) + 0x20));
        M2C_FIELD(p1, u16 *, 0x5C) = _swap16(pokemonBiosGetPhyDef((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u16 *, 0x5E) = _swap16(pokemonBiosGetNimbleness((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u16 *, 0x60) = _swap16(pokemonBiosGetSpeAtk((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u16 *, 0x62) = _swap16(pokemonBiosGetSpeDef((Pokemon*)((Pokemon *) p0)));
        M2C_FIELD(p1, u32 *, 0x44) = _swap32((u32) sp10);
        M2C_FIELD(p1, u32 *, 0x48) = _swap32((u32) spC);
        M2C_FIELD(p1, u32 *, 0x4C) = _swap32((u32) sp8);
        var_r27_2 = var_r31_2;
        var_r28 = 0;
        do {
            var_r29 += _swap16(*var_r27_2);
            var_r27_2 += 2;
            var_r28 += 1;
        } while (var_r28 < 0x18);
        M2C_FIELD(p1, u16 *, 0x1C) = _swap16(var_r29);
        var_ctr = 2;
        do {
            M2C_FIELD(var_r31_2, s32 *, 0) = (s32) (M2C_FIELD(var_r31_2, s32 *, 0) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r31_2, s32 *, 4) = (s32) (M2C_FIELD(var_r31_2, s32 *, 4) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r31_2, s32 *, 8) = (s32) (M2C_FIELD(var_r31_2, s32 *, 8) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r31_2, s32 *, 0xC) = (s32) (M2C_FIELD(var_r31_2, s32 *, 0xC) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r31_2, s32 *, 0x10) = (s32) (M2C_FIELD(var_r31_2, s32 *, 0x10) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r31_2, s32 *, 0x14) = (s32) (M2C_FIELD(var_r31_2, s32 *, 0x14) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            var_r31_2 += 0x18;
            var_ctr -= 1;
        } while (var_ctr != 0);
        _rotatepp((unsigned char*)(((u8*)(p1) + 0x20)), _swap32(M2C_FIELD(p1, u32 *, 0)));
    }
}
}

extern "C" {
void gbaPokemonToGC(Pokemon* p0, GBAPokemon* p1) {
    u16 *var_r3;
    s32 unksp12;
    s32 unksp13;
    volatile s32 unksp9;
    u32 sp14;
    s32 unkspB;
    s32 unkspE;
    volatile s32 unkspF;
    volatile s32 unkspA;
    u32 sp10;
    u32 spC;
    volatile u32 sp8;
    GBAPokemon *var_r28_2;
    s32 var_ctr;
    s32 var_r27;
    s32 var_r29_3;
    u16 *var_r29;
    s32 unksp11;
    u16 var_r27_3;
    u32 temp_r0;
    u8 temp_r0_2;
    u8 temp_r3;
    u8 var_r27_2;
    u8 var_r28;
    u8 var_r29_2;

    pokemonInit((Pokemon*)((u16)p0));
    temp_r3 = M2C_FIELD(p1, u8 *, 0x13);
    if (((u32) ((temp_r3 >> 1U) & 1) != 0) || ((u32) (temp_r3 & 1) != 0)) {
        var_r29 = (unsigned short *)(((u8*)(p1) + 0x20));
        var_r3 = var_r29;
        var_ctr = 2;
        do {
            M2C_FIELD(var_r3, s32 *, 0) = (s32) (M2C_FIELD(var_r3, s32 *, 0) ^ (M2C_FIELD((u16)p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r3, s32 *, 4) = (s32) (M2C_FIELD(var_r3, s32 *, 4) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r3, s32 *, 8) = (s32) (M2C_FIELD(var_r3, s32 *, 8) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r3, s32 *, 0xC) = (s32) (M2C_FIELD(var_r3, s32 *, 0xC) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r3, s32 *, 0x10) = (s32) (M2C_FIELD(var_r3, s32 *, 0x10) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            M2C_FIELD(var_r3, s32 *, 0x14) = (s32) (M2C_FIELD(var_r3, s32 *, 0x14) ^ (M2C_FIELD(p1, u32 *, 0) ^ M2C_FIELD(p1, u32 *, 4)));
            var_r3 = var_r3 + 0x18;
            var_ctr = var_ctr - 1;
        } while (var_ctr != 0);
        _revrotatepp((unsigned char*)(((u8*)((s32)p1) + 0x20)), _swap32(M2C_FIELD(p1, u32 *, 0)));
        var_r27 = 0;
        do {
            _swap16(*var_r29);
            var_r29 = var_r29 + 2;
            var_r27 = var_r27 + 1;
        } while (var_r27 < 0x18);
        sp10 = _swap32(M2C_FIELD(p1, u32 *, 0x44));
        spC = _swap32(M2C_FIELD(p1, u32 *, 0x48));
        sp8 = _swap32(M2C_FIELD(p1, u32 *, 0x4C));
        pokemonBiosSetRnd((Pokemon*)(p0), _swap32(M2C_FIELD(p1, u32 *, 0)));
        pokemonBiosSetCatchTrainerRnd((Pokemon*)(p0), _swap32(M2C_FIELD(p1, u32 *, 4)));
        temp_r0 = (sp10 >> 7U) & 0xF;
        switch (temp_r0) {
        case 1:
            var_r27_2 = 8;
            break;
        case 2:
            var_r27_2 = 9;
            break;
        case 3:
            var_r27_2 = 0xA;
            break;
        case 4:
            var_r27_2 = 1;
            break;
        case 5:
            var_r27_2 = 2;
            break;
        case 15:
            var_r27_2 = 0xB;
            break;
        default:
            var_r27_2 = 0;
            break;
        }
        temp_r0_2 = M2C_FIELD(p1, u8 *, 0x12);
        switch (temp_r0_2) {
        case 1:
            var_r28 = 1;
            var_r29_2 = 1;
            break;
        case 2:
            var_r28 = 2;
            var_r29_2 = 2;
            break;
        case 3:
            var_r28 = 3;
            var_r29_2 = 4;
            break;
        case 4:
            var_r28 = 3;
            var_r29_2 = 5;
            break;
        case 5:
            var_r28 = 3;
            var_r29_2 = 3;
            break;
        case 7:
            var_r28 = 3;
            var_r29_2 = 6;
            break;
        default:
            var_r28 = 0;
            var_r29_2 = 0;
            break;
        }
        gamedataAttestCreate((GamedataAttest*)(pokemonBiosGetAttest((Pokemon*)(p0))), var_r27_2, 3U, var_r28, var_r29_2);
        GScharMakeFromGBA((u16*)(&sp14), (u8*)(((u8*)(p1) + 8)), 0xA, (void*)((u8 *) var_r29_2));
        pokemonBiosSetNicknamePtr((Pokemon*)(p0), (void*)(&sp14));
        if (var_r29_2 == 1) {
            M2C_FIELD(p0, s16 *, 0x58) = 0;
        }
        pokemonBiosSetFlagAmari((Pokemon*)(p0), ((u8) M2C_FIELD(p1, u8 *, 0x13) >> 3U) & 0x1F);
        pokemonBiosSetFuseiFlag((Pokemon*)(p0), (M2C_FIELD(p1, u8 *, 0x13) & 1) != 0);
        GScharMakeFromGBA((u16*)(pokemonBiosGetCatchTrainerNamePtr((Pokemon*)(p0))), (u8*)(((u8*)(p1) + 0x14)), 7, (void*)((u8 *) var_r29_2));
        pokemonBiosSetPcboxMark((Pokemon*)(p0), M2C_FIELD(p1, u8 *, 0x1B));
        pokemonBiosSetAmari((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x1E)));
        pokemonBiosSetPokemonDataId((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x20)));
        var_r29_3 = 0;
        pokemonBiosSetItemDataId((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x22)));
        pokemonBiosSetExp((Pokemon*)(p0), _swap32(M2C_FIELD(p1, u32 *, 0x24)));
        pokemonBiosSetFriend((Pokemon*)(p0), (u16) M2C_FIELD(p1, u8 *, 0x29));
        pokemonBiosSetPara1Amari((Pokemon*)(p0), M2C_FIELD(p1, u16 *, 0x2A));
        var_r27_3 = 0;
        var_r28_2 = p1;
        do {
            u16 tmp2 = _swap16(M2C_FIELD((u16)var_r28_2, u16 *, 0x2C));
            pokemonBiosSetPokemonWazaDataId((Pokemon*)(p0), (u32) var_r27_3, tmp2);
            pokemonBiosSetPokemonWazaPpCount((Pokemon*)(p0), (u32) var_r27_3, ((s32) M2C_FIELD(p1, u8 *, 0x28) >> var_r29_3) & 3);
            pokemonBiosSetPokemonWazaPp((Pokemon*)(p0), (u32) var_r27_3, *((u8*)(p1) + (var_r27_3 + 0x34)));
            var_r28_2 = var_r28_2 + 2;
            var_r29_3 = var_r29_3 + 2;
            var_r27_3 = var_r27_3 + 1;
        } while ((s32) var_r27_3 < 4);
        pokemonBiosSetPhyAtkEffort((Pokemon*)(p0), (u16) M2C_FIELD(p1, u8 *, 0x39));
        pokemonBiosSetPhyDefEffort((Pokemon*)(p0), (u16) M2C_FIELD(p1, u8 *, 0x3A));
        pokemonBiosSetNimblenessEffort((Pokemon*)(p0), (u16) M2C_FIELD(p1, u8 *, 0x3B));
        pokemonBiosSetSpeAtkEffort((Pokemon*)(p0), (u16) M2C_FIELD(p1, u8 *, 0x3C));
        pokemonBiosSetSpeDefEffort((Pokemon*)(p0), (u16) M2C_FIELD(p1, u8 *, 0x3D));
        pokemonBiosSetStyle((Pokemon*)(p0), M2C_FIELD(p1, u8 *, 0x3E));
        pokemonBiosSetBeautiful((Pokemon*)(p0), M2C_FIELD(p1, u8 *, 0x3F));
        pokemonBiosSetCute((Pokemon*)(p0), M2C_FIELD(p1, u8 *, 0x40));
        pokemonBiosSetClever((Pokemon*)(p0), M2C_FIELD(p1, u8 *, 0x41));
        pokemonBiosSetStrong((Pokemon*)(p0), M2C_FIELD(p1, u8 *, 0x42));
        pokemonBiosSetFur((Pokemon*)(p0), M2C_FIELD(p1, u8 *, 0x43));
        pokemonBiosSetMaxHpEffort((Pokemon*)(p0), (u16) M2C_FIELD((u16)p1, u8 *, 0x38));
        pokemonBiosSetPokerus((Pokemon*)(p0), unksp13);
        pokemonBiosSetCatchFloorId((Pokemon*)(p0), (u16) unksp12);
        pokemonBiosSetCatchLevel((Pokemon*)(p0), unksp11 & 0x7F);
        pokemonBiosSetCatchTrainerSex((Pokemon*)(p0), ((u8) sp10 >> 7U) & 1);
        pokemonBiosSetMaxHpRnd((Pokemon*)(p0), unkspF & 0x1F);
        pokemonBiosSetPhyAtkRnd((Pokemon*)(p0), (unkspE >> 5U) & 0x1F);
        pokemonBiosSetNimblenessRnd((Pokemon*)(p0), (spC >> 0xFU) & 0x1F);
        pokemonBiosSetPhyDefRnd((Pokemon*)(p0), (unkspE >> 2U) & 0x1F);
        pokemonBiosSetSpeAtkRnd((Pokemon*)(p0), ((u16) spC >> 4U) & 0x1F);
        pokemonBiosSetCatchBallId((Pokemon*)(p0), (sp10 >> 3U) & 0xF);
        pokemonBiosSetSpeDefRnd((Pokemon*)(p0), ((u8) spC >> 1U) & 0x1F);
        pokemonBiosSetTamagoFlag((Pokemon*)(p0), (((u8) spC >> 6U) & 1) != 0);
        pokemonBiosSetTokuseiFlag((Pokemon*)(p0), (((u8) spC >> 7U) & 1) != 0);
        pokemonBiosSetStyleMedal((Pokemon*)(p0), unkspB & 7);
        pokemonBiosSetBeautifulMedal((Pokemon*)(p0), (unkspB >> 3U) & 7);
        pokemonBiosSetCuteMedal((Pokemon*)(p0), (unkspA >> 6U) & 7);
        pokemonBiosSetCleverMedal((Pokemon*)(p0), (unkspA >> 1U) & 7);
        pokemonBiosSetStrongMedal((Pokemon*)(p0), (unkspA >> 4U) & 7);
        pokemonBiosSetChampRibbon((Pokemon*)(p0), ((unkspA >> 7U) & 1) != 0);
        pokemonBiosSetWinningRibbon((Pokemon*)(p0), (unksp9 & 1) != 0);
        pokemonBiosSetVictoryRibbon((Pokemon*)(p0), ((unksp9 >> 1U) & 1) != 0);
        pokemonBiosSetBromideRibbon((Pokemon*)(p0), ((unksp9 >> 2U) & 1) != 0);
        pokemonBiosSetGanbaRibbon((Pokemon*)(p0), ((unksp9 >> 3U) & 1) != 0);
        pokemonBiosSetMarineRibbon((Pokemon*)(p0), ((unksp9 >> 4U) & 1) != 0);
        pokemonBiosSetLandRibbon((Pokemon*)(p0), ((unksp9 >> 5U) & 1) != 0);
        pokemonBiosSetSkyRibbon((Pokemon*)(p0), ((unksp9 >> 6U) & 1) != 0);
        pokemonBiosSetEarthRibbon((Pokemon*)(p0), ((sp8 >> 1U) & 1) != 0);
        pokemonBiosSetNationalRibbon((Pokemon*)(p0), ((u8) sp8 & 1) != 0);
        pokemonBiosSetCountryRibbon((Pokemon*)(p0), ((unksp9 >> 7U) & 1) != 0);
        pokemonBiosSetWorldRibbon((Pokemon*)(p0), (((u8) sp8 >> 2U) & 1) != 0);
        pokemonBiosSetAmariRibbon((Pokemon*)(p0), ((u8) sp8 >> 3U) & 0xF);
        pokemonBiosSetEventGetFlag((Pokemon*)(p0), (((u8) sp8 >> 7U) & 1) != 0);
        gbaPokemonConditonToGC(p0, _swap32(M2C_FIELD(p1, u32 *, 0x50)));
        pokemonBiosSetConditionAmari((Pokemon*)(p0), _swap32(M2C_FIELD(p1, u32 *, 0x50)) & 0xFFFFF000);
        pokemonBiosSetLevel((Pokemon*)(p0), M2C_FIELD(p1, u8 *, 0x54));
        pokemonBiosSetMailId((Pokemon*)(p0), M2C_FIELD(p1, u8 *, 0x55));
        pokemonBiosSetMaxHp((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x58)));
        pokemonBiosSetHp((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x56)));
        pokemonBiosSetPhyAtk((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x5A)));
        pokemonBiosSetPhyDef((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x5C)));
        pokemonBiosSetNimbleness((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x5E)));
        pokemonBiosSetSpeAtk((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x60)));
        pokemonBiosSetSpeDef((Pokemon*)(p0), _swap16(M2C_FIELD(p1, u16 *, 0x62)));
    }
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
void gbaPokemonConditonToGC(void *p0, u16 p1) {
    s32 temp_r31;

    if ((s32) (p1 & 0x80) != 0) {
        pokemonWriteJoutaiDataId((Pokemon*)((Pokemon *) p0), 4U);
        pokemonSetCountAsJoutaiDataId((Pokemon*)((Pokemon *) p0), 4U, (u32) (s16) ((s32) (p1 & 0xF00) >> 8));
        return;
    }
    if ((s32) (p1 & 0x40) != 0) {
        pokemonWriteJoutaiDataId((Pokemon*)((Pokemon *) p0), 5U);
        return;
    }
    if ((s32) (p1 & 0x20) != 0) {
        pokemonWriteJoutaiDataId((Pokemon*)((Pokemon *) p0), 7U);
        return;
    }
    if ((s32) (p1 & 0x10) != 0) {
        pokemonWriteJoutaiDataId((Pokemon*)((Pokemon *) p0), 6U);
        return;
    }
    if ((s32) (p1 & 8) != 0) {
        pokemonWriteJoutaiDataId((Pokemon*)((Pokemon *) p0), 3U);
        return;
    }
    temp_r31 = p1 & 7;
    if (temp_r31 != 0) {
        pokemonWriteJoutaiDataId((Pokemon*)((Pokemon *) p0), 8U);
        pokemonSetKaisuuJoutaiDataId((Pokemon*)((Pokemon *) p0), 8U, (u32) temp_r31);
    }
}
}

extern "C++" {
static void _rotatepp(unsigned char* p0, unsigned long p1) {
    u32 temp_r31;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r30;
    u8 sp8[sizeof(s32) + 8];
    u32 temp_r31_2;

    temp_r0 = (p1 % 24) / 6;
    if (temp_r0 != 0) {
        temp_r31 = temp_r0 * 0xC;
        memcpy((void*)(&sp8), (const void*)(p0 + temp_r31), 0xCU);
        memmove((void*)(p0 + 0xC), (const void*)(p0), temp_r31);
        memcpy((void*)(p0), (const void*)(&sp8), 0xCU);
    }
    temp_r30 = (p1 % 24) % 6;
    temp_r0_2 = temp_r30 >> 1U;
    if (temp_r0_2 != 0) {
        temp_r31_2 = temp_r0_2 * 0xC;
        memcpy((void*)(&sp8), (const void*)(p0 + (temp_r31_2 + 0xC)), 0xCU);
        memmove((void*)(p0 + 0x18), (const void*)(p0 + 0xC), temp_r31_2);
        memcpy((void*)(p0 + 0xC), (const void*)(&sp8), 0xCU);
    }
    if ((u32) (temp_r30 & 1) != 0) {
        memcpy((void*)(&sp8), (const void*)(p0 + 0x24), 0xCU);
        memcpy((void*)(p0 + 0x24), (const void*)(p0 + 0x18), 0xCU);
        memcpy((void*)(p0 + 0x18), (const void*)(&sp8), 0xCU);
    }
}
}

extern "C++" {
static void _revrotatepp(unsigned char* p0, unsigned long p1) {
    u8 sp8[sizeof(s32) + 8];
    u32 temp_r31_3;
    u32 temp_r31_2;
    u32 temp_r31;
    u32 temp_r31_4;

    if ((u32) (p1 & 1) != 0) {
        memcpy((void*)(&sp8), (const void*)(p0 + 0x18), 0xCU);
        memcpy((void*)(p0 + 0x18), (const void*)(p0 + 0x24), 0xCU);
        memcpy((void*)(p0 + 0x24), (const void*)(&sp8), 0xCU);
    }
    temp_r31 = (p1 >> 1U);
    temp_r31 -= ((p1 / 6) * 3);
    if (temp_r31 != 0) {
        memcpy((void*)(&sp8), (const void*)(p0 + 0xC), 0xCU);
        temp_r31_2 = temp_r31 * 0xC;
        memmove((void*)(p0 + 0xC), (const void*)(p0 + 0x18), temp_r31_2);
        memcpy((void*)(p0 + (temp_r31_2 + 0xC)), (const void*)(&sp8), 0xCU);
    }
    temp_r31_3 = (p1 / 6) & 3;
    if (temp_r31_3 != 0) {
        memcpy((void*)(&sp8), (const void*)(p0), 0xCU);
        temp_r31_4 = temp_r31_3;
        temp_r31_4 *= 0xC;
        memmove((void*)(p0), (const void*)(p0 + 0xC), temp_r31_4);
        memcpy((void*)(p0 + temp_r31_4), (const void*)(&sp8), 0xCU);
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
