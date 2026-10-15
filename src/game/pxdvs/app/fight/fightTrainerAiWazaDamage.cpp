#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightPokemon;
struct FightWaza;
typedef void (*FightWazaSubPre)(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);

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
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*, u8);
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
s32 fightSeqWazaDamageCalc(FightOutPokemon*, FightOutPokemon*, FightOutPokemon*, u16, u16, u16);
s32 fightSeqGetNromalWazaDamage(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*, u32, u32, FightWazaSubPre, u32);
s32 fightTrainerAiWazaDamage000(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaDamage002(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaDamage004(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
s32 fightTrainerAiWazaDamage039(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
int fightTrainerAiWazaDamage132(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
}

static void _fightTrainerAiWazaDamage203SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage196SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage190SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage135SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage126SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage123SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage122SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage121SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage117SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage104SubPre1(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage104SubPre2(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage104SubPre3(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static void _fightTrainerAiWazaDamage099SubPre(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
static s32 _fightTrainerAiWazaDamageNormal(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);

extern "C" {
u32 fightTrainerAiWazaDamage217(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage216(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage215(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage214(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage213(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage212(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage211(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage210(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage209(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage002(t, a, w, d);
}
u32 fightTrainerAiWazaDamage208(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage207(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage206(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage205(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage204(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage203(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    u8 weather = fightTrainerAiGetFightFloorNowTenkouDataId(t, 0, 1);
    s32 damage = fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage203SubPre, 0);
    if (weather != 0) {
        damage <<= 1;
    }
    return damage;
}
}
static void _fightTrainerAiWazaDamage203SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
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
s32 fightTrainerAiWazaDamage202(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage201(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage200(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage004(t, a, w, d);
}
u32 fightTrainerAiWazaDamage199(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage198(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage197(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage196(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage196SubPre, 0);
}
}
static void _fightTrainerAiWazaDamage196SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u16 power = fightSeqGetKetaguriIryoku(pokemonDB_GetWeight(fightTrainerAiGetFightOutPokemonPokemonDataId(t, a)));
    fightWaza_SetIryoku(waza, power);
}
extern "C" {
u32 fightTrainerAiWazaDamage195(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage194(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage193(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage192(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage191(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage190(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage190SubPre, 0);
}
}
static void _fightTrainerAiWazaDamage190SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
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
u32 fightTrainerAiWazaDamage189(FIGHT_TRAINER* ctx, FightOutPokemon* slot, u32 param, FightOutPokemon* arg3)
{
    s32 first;
    s32 second;

    first = fightTrainerAiGetFightOutPokemonNowHp(ctx, slot) & 0xFFFF;
    second = fightTrainerAiGetFightOutPokemonNowHp(ctx, arg3) & 0xFFFF;

    if (first >= second) {
        return 0;
    }
    return second - first;
}
s32 fightTrainerAiWazaDamage188(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage187(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage186(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamage185(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamage184(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage183(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage182(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage181(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage180(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage179(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage178(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage177(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage176(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage175(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage174(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage173(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    u16 paramType;
    u16 otherType;
    u16 other;
    other = tikeiDataBiosGetWazaId(fightFloor_GetTikeiDataId(0));
    paramType = wazaDB_GetSeqId(w);
    w = other;
    otherType = wazaDB_GetSeqId(w);
    if (otherType != paramType) {
        return fightTrainerAiWazaDoWazaDamageFunc(t, a, w, d, 1);
    }
    return 0;
}
u32 fightTrainerAiWazaDamage172(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage171(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage = _fightTrainerAiWazaDamageNormal(t, w, a, d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, d, 0x5) == 1) {
        damage <<= 1;
    }
    return damage;
}
s32 fightTrainerAiWazaDamage170(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage169(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage = _fightTrainerAiWazaDamageNormal(t, w, a, d);
    if (fightTrainerAiIsFightOutPokemonJoutaiKaragenki(t, a) == 1) {
        damage <<= 1;
    }
    return damage;
}
u32 fightTrainerAiWazaDamage168(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage167(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage166(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage165(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage164(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
#pragma push
#pragma global_optimizer off
s32 fightTrainerAiWazaDamage162(FIGHT_TRAINER* ctx, FightOutPokemon* param1, FightOutPokemon* param2)
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
s32 fightTrainerAiWazaDamage161(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s16 multiplier = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, a, 0x2d) == 1) {
        multiplier = fightOutPokemonGetCountAsJoutaiDataId(a, 0x2d);
    }
    return multiplier * _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamage160(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage159(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamage158(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
int fightTrainerAiWazaDamage157(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return -(fightTrainerAiGetFightOutPokemonMaxHp(ctx, slot) >> 1 & 0x7FFF);
}
u32 fightTrainerAiWazaDamage156(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage155(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamage154(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    FightPokemon* pokemon[24];
    s32 total = 0;
    u16 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, t, pokemon, 1, 1);
    u16 i;
    for (i = 0; i < count; i++) {
        u32 id = fightTrainerAiGetFightPokemonPokemonDataId(t, pokemon[i]);
        u32 level = fightTrainerAiGetFightPokemonLevel(t, pokemon[i]);
        u32 defId = fightTrainerAiGetFightOutPokemonPokemonDataId(t, d);
        u32 defLevel = fightTrainerAiGetFightOutPokemonLevel(t, d);
        total += fightSeqGetHukuroDatakiDamage(w, id, level, defId, defLevel);
    }
    return total;
}
u32 fightTrainerAiWazaDamage153(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage152(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage151(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage039(t, a, w, d);
}
s32 fightTrainerAiWazaDamage150(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage = _fightTrainerAiWazaDamageNormal(t, w, a, d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, d, 0x23) == 1) {
        damage <<= 1;
    }
    return damage;
}
s32 fightTrainerAiWazaDamage149(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage = _fightTrainerAiWazaDamageNormal(t, w, a, d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, d, 0x1f) == 1) {
        damage <<= 1;
    }
    return damage;
}
s32 fightTrainerAiWazaDamage148(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage;
    u32 zokusei;
    u16 power = fightTrainerAiGetWazaIryoku(t, w);
    zokusei = fightTrainerAiGetWazaZokuseiDataId(t, w, a);
    FightOutPokemon* target = fightTargetGetPtrAsNowFightType(2, d);
    damage = fightSeqWazaDamageCalc(a, d, target, w, power, zokusei);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, a, 0x32) == 1) {
        damage = damage * 15 / 10;
    }
    return damage;
}
s32 fightTrainerAiWazaDamage147(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage = _fightTrainerAiWazaDamageNormal(t, w, a, d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, d, 0x20) == 1) {
        damage <<= 1;
    }
    return damage;
}
s32 fightTrainerAiWazaDamage146(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage = _fightTrainerAiWazaDamageNormal(t, w, a, d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, d, 0x1f) == 1) {
        damage <<= 1;
    }
    return damage;
}
s32 fightTrainerAiWazaDamage145(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage039(t, a, w, d);
}
u32 fightTrainerAiWazaDamage144(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage143(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage142(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage140(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage139(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage138(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage137(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage136(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage135(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage135SubPre, 0);
}
}
static void _fightTrainerAiWazaDamage135SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u16 power;
    u16 zokusei;
    pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(a), &power, &zokusei);
    fightWaza_SetIryoku(waza, power);
    fightWaza_SetZokusei(waza, zokusei);
}
extern "C" {
s32 fightTrainerAiWazaDamage134(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage132(t, a, w, d);
}
s32 fightTrainerAiWazaDamage133(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage132(t, a, w, d);
}
int fightTrainerAiWazaDamage132(FIGHT_TRAINER* ctx, FightOutPokemon* param1, u16 param2, FightOutPokemon* param3)
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
u32 fightTrainerAiWazaDamage130(void* ctx, u32 p1, u32 p2, u32 p3) { return 20; }
s32 fightTrainerAiWazaDamage129(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage128(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamage127(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage126(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage126SubPre, 0);
}
}
static void _fightTrainerAiWazaDamage126SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0x46);
}
extern "C" {
s32 fightTrainerAiWazaDamage125(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage124(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage123(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage123SubPre, 0);
}
}
static void _fightTrainerAiWazaDamage123SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    fightWaza_GetIryoku(waza);
    u16 power = fightSeqGetYatuatariIryoku(fightTrainerAiGetFightOutPokemonFriend(t, a));
    fightWaza_SetIryoku(waza, power);
}
extern "C" {
s32 fightTrainerAiWazaDamage122(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage122SubPre, 0);
}
}
static void _fightTrainerAiWazaDamage122SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0x28);
}
extern "C" {
s32 fightTrainerAiWazaDamage121(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage121SubPre, 0);
}
}
static void _fightTrainerAiWazaDamage121SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    fightWaza_GetIryoku(waza);
    u16 power = fightSeqGetOngaesiIryoku(fightTrainerAiGetFightOutPokemonFriend(t, a));
    fightWaza_SetIryoku(waza, power);
}
extern "C" {
u32 fightTrainerAiWazaDamage120(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage119(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamage118(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage117(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage117SubPre, 0);
}
}
static void _fightTrainerAiWazaDamage117SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u16 power = fightWaza_GetIryoku(waza);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, a, 0x1a) == 1) {
        power <<= 1;
    }
    fightWaza_SetIryoku(waza, power);
}
extern "C" {
u32 fightTrainerAiWazaDamage116(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage115(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage114(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage113(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage112(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage111(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage109(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage108(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage107(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage106(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage105(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage104(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage = fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage104SubPre1, 0);
    damage += fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage104SubPre2, 0);
    damage += fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage104SubPre3, 0);
    return damage;
}
}
static void _fightTrainerAiWazaDamage104SubPre3(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0x1e);
}
static void _fightTrainerAiWazaDamage104SubPre2(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0x14);
}
static void _fightTrainerAiWazaDamage104SubPre1(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(a), 0xa);
}
extern "C" {
s32 fightTrainerAiWazaDamage103(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage102(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage101(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    u32 hp = fightTrainerAiGetFightOutPokemonNowHp(t, d);
    s32 damage = _fightTrainerAiWazaDamageNormal(t, w, a, d);
    if ((s32)(hp & 0xFFFF) <= damage) {
        damage = (hp & 0xFFFF) - 1;
    }
    return damage;
}
u32 fightTrainerAiWazaDamage100(void* ctx, u32 p1, u32 p2, u32 p3) { return 5; }
s32 fightTrainerAiWazaDamage099(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, _fightTrainerAiWazaDamage099SubPre, 0);
}
}
static void _fightTrainerAiWazaDamage099SubPre(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(a);
    u32 nowHp = fightTrainerAiGetFightOutPokemonNowHp(t, a);
    u32 maxHp = fightTrainerAiGetFightOutPokemonMaxHp(t, a);
    fightWaza_SetIryoku(waza, fightSeqGetJitabataIryoku(nowHp, maxHp));
}
extern "C" {
u16 fightTrainerAiWazaDamage098(FIGHT_TRAINER* ctx, u32 p1, u32 p2, FightOutPokemon* p3)
{
    return (u16) fightTrainerAiGetFightOutPokemonNowHp(ctx, p3);
}
u32 fightTrainerAiWazaDamage097(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage095(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage094(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage093(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage092(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamage091(FIGHT_TRAINER* ctx, FightOutPokemon* slot, u32 arg2, FightOutPokemon* param)
{
    s32 val1, val2, avg;
    val1 = fightTrainerAiGetFightOutPokemonNowHp(ctx, slot) & 0xFFFF;
    val2 = fightTrainerAiGetFightOutPokemonNowHp(ctx, param) & 0xFFFF;
    avg = (s32)(val1 + val2) / 2;
    return val2 - avg;
}
u32 fightTrainerAiWazaDamage090(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage089(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u8 fightTrainerAiWazaDamage088(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return (u8) fightTrainerAiGetFightOutPokemonLevel(ctx, slot);
}
u8 fightTrainerAiWazaDamage087(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return (u8) fightTrainerAiGetFightOutPokemonLevel(ctx, slot);
}
u32 fightTrainerAiWazaDamage086(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage085(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage084(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage083(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage082(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage081(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage080(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage079(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage078(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage077(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d) << 1;
}
s32 fightTrainerAiWazaDamage076(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage075(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage039(t, a, w, d);
}
s32 fightTrainerAiWazaDamage073(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage072(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage071(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage070(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage069(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage068(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage067(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage066(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage065(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage062(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage060(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage059(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage058(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage057(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage054(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage053(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage052(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage051(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage050(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage049(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage048(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage047(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage046(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage045(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage044(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d) << 1;
}
s32 fightTrainerAiWazaDamage043(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage042(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage = _fightTrainerAiWazaDamageNormal(t, w, a, d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, d, 0x21) == 1 && w == 0xfa) {
        damage <<= 1;
    }
    return damage;
}
u32 fightTrainerAiWazaDamage041(void* ctx, u32 p1, u32 p2, u32 p3) { return 40; }
s32 fightTrainerAiWazaDamage040(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamage039(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
u16 fightTrainerAiWazaDamage038(FIGHT_TRAINER* ctx, u32 p1, u32 p2, FightOutPokemon* p3)
{
    return (u16) fightTrainerAiGetFightOutPokemonNowHp(ctx, p3);
}
int fightTrainerAiWazaDamage037(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return -(fightTrainerAiGetFightOutPokemonMaxHp(ctx, slot) & 0xFFFF);
}
s32 fightTrainerAiWazaDamage036(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage035(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage034(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage033(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
int fightTrainerAiWazaDamage032(FIGHT_TRAINER* ctx, FightOutPokemon* slot)
{
    return -(fightTrainerAiGetFightOutPokemonMaxHp(ctx, slot) >> 1 & 0x7FFF);
}
s32 fightTrainerAiWazaDamage031(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage030(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage029(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d) * 3;
}
u32 fightTrainerAiWazaDamage028(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage027(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
u32 fightTrainerAiWazaDamage026(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage025(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage024(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage023(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage020(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage019(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage018(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage017(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage016(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage013(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage011(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage010(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
u32 fightTrainerAiWazaDamage009(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage008(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamage007(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamage006(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage005(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage004(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
s32 fightTrainerAiWazaDamage003(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return _fightTrainerAiWazaDamageNormal(t, w, a, d);
}
s32 fightTrainerAiWazaDamage002(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    return fightTrainerAiWazaDamage000(t, a, w, d);
}
u32 fightTrainerAiWazaDamage001(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
s32 fightTrainerAiWazaDamage000(FIGHT_TRAINER* t, FightOutPokemon* a, u16 w, FightOutPokemon* d) {
    s32 damage = _fightTrainerAiWazaDamageNormal(t, w, a, d);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(t, d, 0x21) == 1 && w == 0x39) {
        damage <<= 1;
    }
    return damage;
}
u32 fightTrainerAiWazaDamageNull(void* ctx, u32 p1, u32 p2, u32 p3) { return 0; }
}
static s32 _fightTrainerAiWazaDamageNormal(FIGHT_TRAINER* t, u16 w, FightOutPokemon* a, FightOutPokemon* d) {
    return fightSeqGetNromalWazaDamage(t, w, a, d, 0, 0, 0, 0);
}
