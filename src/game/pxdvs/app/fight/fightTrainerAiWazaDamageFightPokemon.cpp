// WIP: mechanical copy of fightTrainerAiWazaDamage.cpp (its matched twin, found with
// xd-helpers/similar.py). 178/217 exact as-is. Remaining: the defender is a FightPokemon* and uses the
// fightTrainerAiGetFightPokemon* accessors; static SubPre helpers come before their callers (LAYOUT).
#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FightOutPokemon {};
struct FightPokemon : FightOutPokemon {};
struct FightWaza;
typedef void (*FightWazaSubPre)(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);

extern "C" {
u32 fightTrainerAiGetFightOutPokemonLevel(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonMaxHp(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonPokemonDataId(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonFriend(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightPokemonPokemonDataId(FIGHT_TRAINER*, FightPokemon*);
u32 fightTrainerAiGetFightPokemonLevel(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiKaragenki(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER*, u32, u32);
u32 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER*, u16);
u32 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaDoWazaDamageFightPokemonFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightPokemon*, u8);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(u32, FIGHT_TRAINER*, FightPokemon**, u8, u8);
u16 fightFloor_GetTikeiDataId(u32);
u16 tikeiDataBiosGetWazaId(u8);
u32 wazaDB_GetSeqId(u16);
s16 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon*, u16);
u8 joutaiDataBiosGetMaxCount(u32);
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
void* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u16 fightWaza_GetIryoku(FightWaza*);
void fightWaza_SetIryoku(FightWaza*, u16);
void fightWaza_SetZokusei(FightWaza*, u16);
void pokemonGetMezamerupower(void*, u16*, u16*);
u32 pokemonDB_GetWeight(u32);
u16 fightSeqGetKetaguriIryoku(u32);
u16 fightSeqGetYatuatariIryoku(u32);
u16 fightSeqGetOngaesiIryoku(u32);
u8 fightSeqGetJitabataIryoku(u32, u32);
s32 fightSeqGetHukuroDatakiDamage(u16, u32, u8, u32, u8);
FightOutPokemon* fightTargetGetPtrAsNowFightType(u32, FightOutPokemon*);
s32 fightSeqWazaDamageCalcHikaePokemon(FightOutPokemon*, FightPokemon*, FightOutPokemon*, u16, u16, u16);
void* fightPokemon_GetPokemonBuffPtr(FightPokemon*);
u32 pokemon_GetHp(void*);
s32 fightSeqGetWazaDamageHikaePokemon(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*, u32, FightWazaSubPre, u32);
s32 fightTrainerAiWazaDamageFightPokemon000(FIGHT_TRAINER*, FightOutPokemon*, u16, FightPokemon*);
s32 fightTrainerAiWazaDamageFightPokemon002(FIGHT_TRAINER*, FightOutPokemon*, u16, FightPokemon*);
s32 fightTrainerAiWazaDamageFightPokemon004(FIGHT_TRAINER*, FightOutPokemon*, u16, FightPokemon*);
s32 fightTrainerAiWazaDamageFightPokemon039(FIGHT_TRAINER*, FightOutPokemon*, u16, FightPokemon*);
int fightTrainerAiWazaDamageFightPokemon132(FIGHT_TRAINER*, FightOutPokemon*, u16, FightPokemon*);
}

static void _fightTrainerAiWazaDamageFightPokemon203SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon196SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon190SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon135SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon126SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon123SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon122SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon121SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon117SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon104SubPre1(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon104SubPre2(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon104SubPre3(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static void _fightTrainerAiWazaDamageFightPokemon099SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
static s32 _fightTrainerAiWazaDamageFightPokemonNormal(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);

extern "C" {
u32 fightTrainerAiWazaDamageFightPokemon217(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon216(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon215(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon214(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon213(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon212(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon211(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon210(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon209(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon002(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon208(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon207(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon206(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon205(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon204(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon203(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    u8 weather = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1);
    s32 damage = fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon203SubPre, 0);
    if (weather != 0) {
        damage <<= 1;
    }
    return damage;
}
}
static void _fightTrainerAiWazaDamageFightPokemon203SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    u8 weather = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1);
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u16 zokusei;
    if (weather == 2) {
        zokusei = 0xb;
    } else if (weather == 3) {
        zokusei = 5;
    } else if (weather == 1) {
        zokusei = 0xa;
    } else if (weather == 4) {
        zokusei = 0xf;
    } else {
        zokusei = 0;
    }
    fightWaza_SetZokusei(waza, zokusei);
}
extern "C" {
s32 fightTrainerAiWazaDamageFightPokemon202(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon201(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon200(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon004(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon199(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon198(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon197(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon196(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon196SubPre, 0);
}
}
static void _fightTrainerAiWazaDamageFightPokemon196SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u16 power = fightSeqGetKetaguriIryoku(pokemonDB_GetWeight(fightTrainerAiGetFightOutPokemonPokemonDataId(t, a)));
    fightWaza_SetIryoku(waza, power);
}
extern "C" {
u32 fightTrainerAiWazaDamageFightPokemon195(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon194(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon193(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon192(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon191(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon190(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon190SubPre, 0);
}
}
static void _fightTrainerAiWazaDamageFightPokemon190SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u32 nowHp = fightTrainerAiGetFightOutPokemonNowHp(t, a);
    u32 maxHp = fightTrainerAiGetFightOutPokemonMaxHp(t, a);
    u16 base = fightWaza_GetIryoku(waza);
    u16 power = base * (u16)nowHp / (u16)maxHp;
    if (power == 0) {
        power = 1;
    }
    fightWaza_SetIryoku(waza, power);
}
extern "C" {
u32 fightTrainerAiWazaDamageFightPokemon189(FIGHT_TRAINER* ctx, FightOutPokemon* slot, u32 param, FightPokemon* arg3)
{
    s32 first;
    s32 second;

    first = fightTrainerAiGetFightOutPokemonNowHp(ctx, slot) & 0xFFFF;
    second = pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(arg3)) & 0xFFFF;

    if (first >= second) {
        return 0;
    }
    return second - first;
}
s32 fightTrainerAiWazaDamageFightPokemon188(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon187(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon186(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon185(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamageFightPokemon184(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon183(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon182(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon181(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon180(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon179(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon178(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon177(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon176(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon175(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon174(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon173(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    u16 paramType;
    u16 otherType;
    u16 other;
    other = tikeiDataBiosGetWazaId(fightFloor_GetTikeiDataId(0));
    paramType = wazaDB_GetSeqId(w);
    w = other;
    otherType = wazaDB_GetSeqId(w);
    if (otherType != paramType) {
        return fightTrainerAiWazaDoWazaDamageFightPokemonFunc(t, a, w, d, 1);
    }
    return 0;
}
u32 fightTrainerAiWazaDamageFightPokemon172(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon171(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon170(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon169(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    s32 damage = _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
    if (fightTrainerAiIsFightOutPokemonJoutaiKaragenki(t, a) == 1) {
        damage <<= 1;
    }
    return damage;
}
u32 fightTrainerAiWazaDamageFightPokemon168(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon167(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon166(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon165(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon164(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
#pragma push
#pragma global_optimizer off
s32 fightTrainerAiWazaDamageFightPokemon162(FIGHT_TRAINER* ctx, FightOutPokemon* param1, FightOutPokemon* param2)
{
    s16 multiplier;
    s16 shift;
    u32 hp;

    multiplier = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param1, 0x2D) == 1) {
        multiplier = fightOutPokemonGetCountAsJoutaiDataId(param1, 0x2D);
    }
    shift = joutaiDataBiosGetMaxCount(0x2D) - multiplier;
    if (shift < 0) {
        shift = 0;
    }
    multiplier = 1 << shift;
    hp = fightTrainerAiGetFightOutPokemonMaxHp(ctx, param1) & 0xFFFF;
    return -((s32)hp / multiplier);
}
#pragma pop
s32 fightTrainerAiWazaDamageFightPokemon161(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    s16 multiplier = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, a, 0x2d) == 1) {
        multiplier = fightOutPokemonGetCountAsJoutaiDataId(a, 0x2d);
    }
    return multiplier * _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamageFightPokemon160(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon159(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamageFightPokemon158(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
int fightTrainerAiWazaDamageFightPokemon157(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return -(fightTrainerAiGetFightOutPokemonMaxHp(ctx, slot) >> 1 & 0x7FFF);
}
u32 fightTrainerAiWazaDamageFightPokemon156(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon155(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon154(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    FightPokemon* pokemon[24];
    s32 total = 0;
    u16 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, pokemon, 1, 1);
    u16 i;
    for (i = 0; i < count; i++) {
        u32 id = fightTrainerAiGetFightPokemonPokemonDataId(t, pokemon[i]);
        u32 level = fightTrainerAiGetFightPokemonLevel(t, pokemon[i]);
        u32 defId = fightTrainerAiGetFightPokemonPokemonDataId(t, d);
        u32 defLevel = fightTrainerAiGetFightPokemonLevel(t, d);
        total += fightSeqGetHukuroDatakiDamage(w, id, level, defId, defLevel);
    }
    return total;
}
u32 fightTrainerAiWazaDamageFightPokemon153(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon152(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon151(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon039(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon150(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon149(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon148(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    s32 damage;
    u32 zokusei;
    u16 power = fightTrainerAiGetWazaIryoku(t, w);
    zokusei = fightTrainerAiGetWazaZokuseiDataId(t, w, a);
    FightOutPokemon* target = fightTargetGetPtrAsNowFightType(2, d);
    damage = fightSeqWazaDamageCalcHikaePokemon(a, d, target, w, power, zokusei);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, a, 0x32) == 1) {
        damage = damage * 15 / 10;
    }
    return damage;
}
s32 fightTrainerAiWazaDamageFightPokemon147(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon146(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon145(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon039(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon144(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon143(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon142(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon140(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon139(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon138(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon137(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon136(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon135(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon135SubPre, 0);
}
}
static void _fightTrainerAiWazaDamageFightPokemon135SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u16 power;
    u16 zokusei;
    pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(a), &power, &zokusei);
    fightWaza_SetIryoku(waza, power);
    fightWaza_SetZokusei(waza, zokusei);
}
extern "C" {
s32 fightTrainerAiWazaDamageFightPokemon134(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon132(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon133(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon132(t, a, w, d);
}
int fightTrainerAiWazaDamageFightPokemon132(FIGHT_TRAINER* ctx, FightOutPokemon* param1, u16 param2, FightPokemon* param3)
{
    u8 status;
    s32 value;

    status = fightTrainerAiGetFightFloorNowTenkouDataId(ctx, 0, 1);
    if ((u8)status == 0) {
        value = (fightTrainerAiGetFightOutPokemonMaxHp(ctx, param1) >> 1) & 0x7FFF;
    } else if ((u8)status == 1) {
        value = ((s32)(fightTrainerAiGetFightOutPokemonMaxHp(ctx, param1) & 0xFFFF) * 0x14) / 0x1E;
    } else {
        value = (fightTrainerAiGetFightOutPokemonMaxHp(ctx, param1) >> 2) & 0x3FFF;
    }
    return -value;
}
u32 fightTrainerAiWazaDamageFightPokemon130(void* ctx, u32 p1, u32 p2, u32 p3) { return 20; }
s32 fightTrainerAiWazaDamageFightPokemon129(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon128(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d) << 1;
}
u32 fightTrainerAiWazaDamageFightPokemon127(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon126(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon126SubPre, 0);
}
}
static void _fightTrainerAiWazaDamageFightPokemon126SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0x46);
}
extern "C" {
s32 fightTrainerAiWazaDamageFightPokemon125(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon124(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon123(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon123SubPre, 0);
}
}
static void _fightTrainerAiWazaDamageFightPokemon123SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    fightWaza_GetIryoku(waza);
    u16 power = fightSeqGetYatuatariIryoku(fightTrainerAiGetFightOutPokemonFriend(t, a));
    fightWaza_SetIryoku(waza, power);
}
extern "C" {
s32 fightTrainerAiWazaDamageFightPokemon122(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon122SubPre, 0);
}
}
static void _fightTrainerAiWazaDamageFightPokemon122SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0x28);
}
extern "C" {
s32 fightTrainerAiWazaDamageFightPokemon121(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon121SubPre, 0);
}
}
static void _fightTrainerAiWazaDamageFightPokemon121SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    fightWaza_GetIryoku(waza);
    u16 power = fightSeqGetOngaesiIryoku(fightTrainerAiGetFightOutPokemonFriend(t, a));
    fightWaza_SetIryoku(waza, power);
}
extern "C" {
u32 fightTrainerAiWazaDamageFightPokemon120(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon119(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamageFightPokemon118(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon117(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon117SubPre, 0);
}
}
static void _fightTrainerAiWazaDamageFightPokemon117SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u16 power = fightWaza_GetIryoku(waza);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, a, 0x1a) == 1) {
        power <<= 1;
    }
    fightWaza_SetIryoku(waza, power);
}
extern "C" {
u32 fightTrainerAiWazaDamageFightPokemon116(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon115(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon114(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon113(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon112(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon111(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon109(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon108(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon107(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon106(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon105(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon104(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    s32 damage = fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon104SubPre1, 0);
    damage += fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon104SubPre2, 0);
    damage += fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon104SubPre3, 0);
    return damage;
}
}
static void _fightTrainerAiWazaDamageFightPokemon104SubPre3(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0x1e);
}
static void _fightTrainerAiWazaDamageFightPokemon104SubPre2(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0x14);
}
static void _fightTrainerAiWazaDamageFightPokemon104SubPre1(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0xa);
}
extern "C" {
s32 fightTrainerAiWazaDamageFightPokemon103(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon102(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon101(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    u32 hp = pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(d));
    s32 damage = _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
    if ((s32)(hp & 0xFFFF) <= damage) {
        damage = (hp & 0xFFFF) - 1;
    }
    return damage;
}
u32 fightTrainerAiWazaDamageFightPokemon100(void* ctx, u32 p1, u32 p2, u32 p3) { return 5; }
s32 fightTrainerAiWazaDamageFightPokemon099(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, _fightTrainerAiWazaDamageFightPokemon099SubPre, 0);
}
}
static void _fightTrainerAiWazaDamageFightPokemon099SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u32 nowHp = fightTrainerAiGetFightOutPokemonNowHp(t, a);
    u32 maxHp = fightTrainerAiGetFightOutPokemonMaxHp(t, a);
    fightWaza_SetIryoku(waza, fightSeqGetJitabataIryoku(nowHp, maxHp));
}
extern "C" {
u16 fightTrainerAiWazaDamageFightPokemon098(FIGHT_TRAINER* ctx, u32 p1, u32 p2, FightPokemon* p3)
{
    return (u16) pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(p3));
}
u32 fightTrainerAiWazaDamageFightPokemon097(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon095(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon094(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon093(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon092(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamageFightPokemon091(FIGHT_TRAINER* ctx, FightOutPokemon* slot, u32 arg2, FightPokemon* param)
{
    s32 val1, val2, avg;
    val1 = fightTrainerAiGetFightOutPokemonNowHp(ctx, slot) & 0xFFFF;
    val2 = pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(param)) & 0xFFFF;
    avg = (s32)(val1 + val2) / 2;
    return val2 - avg;
}
u32 fightTrainerAiWazaDamageFightPokemon090(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon089(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u8 fightTrainerAiWazaDamageFightPokemon088(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return (u8) fightTrainerAiGetFightOutPokemonLevel(ctx, slot);
}
u8 fightTrainerAiWazaDamageFightPokemon087(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return (u8) fightTrainerAiGetFightOutPokemonLevel(ctx, slot);
}
u32 fightTrainerAiWazaDamageFightPokemon086(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon085(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon084(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon083(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon082(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon081(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon080(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon079(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon078(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon077(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d) << 1;
}
s32 fightTrainerAiWazaDamageFightPokemon076(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon075(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon039(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon073(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon072(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon071(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon070(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon069(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon068(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon067(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon066(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon065(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon062(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon060(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon059(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon058(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon057(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon054(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon053(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon052(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon051(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon050(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon049(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon048(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon047(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon046(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon045(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon044(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d) << 1;
}
s32 fightTrainerAiWazaDamageFightPokemon043(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon042(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamageFightPokemon041(void* ctx, u32 p1, u32 p2, u32 p3) { return 40; }
s32 fightTrainerAiWazaDamageFightPokemon040(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon039(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
u16 fightTrainerAiWazaDamageFightPokemon038(FIGHT_TRAINER* ctx, u32 p1, u32 p2, FightPokemon* p3)
{
    return (u16) pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(p3));
}
int fightTrainerAiWazaDamageFightPokemon037(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return -(fightTrainerAiGetFightOutPokemonMaxHp(ctx, slot) & 0xFFFF);
}
s32 fightTrainerAiWazaDamageFightPokemon036(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon035(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon034(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon033(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
int fightTrainerAiWazaDamageFightPokemon032(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return -(fightTrainerAiGetFightOutPokemonMaxHp(ctx, slot) >> 1 & 0x7FFF);
}
s32 fightTrainerAiWazaDamageFightPokemon031(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon030(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon029(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d) * 3;
}
u32 fightTrainerAiWazaDamageFightPokemon028(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon027(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamageFightPokemon026(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon025(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon024(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon023(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon020(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon019(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon018(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon017(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon016(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon013(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon011(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon010(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamageFightPokemon009(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon008(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon007(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon006(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon005(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon004(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
s32 fightTrainerAiWazaDamageFightPokemon003(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamageFightPokemon002(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return fightTrainerAiWazaDamageFightPokemon000(t, a, w, d);
}
u32 fightTrainerAiWazaDamageFightPokemon001(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamageFightPokemon000(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightPokemon* d) {
    return _fightTrainerAiWazaDamageFightPokemonNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamageFightPokemonNull(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
}
static s32 _fightTrainerAiWazaDamageFightPokemonNormal(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightPokemon* d) {
    return fightSeqGetWazaDamageHikaePokemon(t, w, a, d, 0, 0, 0);
}
