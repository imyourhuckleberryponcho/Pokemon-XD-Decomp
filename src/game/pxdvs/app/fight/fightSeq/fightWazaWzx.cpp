#include <dolphin/types.h>

#pragma optimize_for_size on

struct FightOutPokemon;

static void _fightWazaWxzfightOutPokemonWazaEffectSpe(FightOutPokemon*, u16, bool);
static void _fightWazaWxzfightOutPokemonWazaEffectDef(FightOutPokemon*, u16, bool);
static void _fightWazaWxzfightOutPokemonWazaEffectAtk(FightOutPokemon*, u16, bool);

extern "C" {

u8 fight_seq_oiuchiflag;
extern u8* UserWork;

u32 fightFloorGetNowTenkouDataId(u32, u32);
s16 fightOutPokemonGetCountAsJoutaiDataId(void*, u32);
void* fightOutPokemon_GetFightWazaPtr(void*);
u16 fightWaza_GetIryoku(void*);
u8 figthOutPokemonGetLevel(void*);

u32 fightFloor_GetFightType(u32);
FightOutPokemon* fightTargetGetPtr(u32, FightOutPokemon*, u8);
void fightOutPokemonLoadWazaEffect(FightOutPokemon*, u16, u32, bool);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u32);
void fightOutPokemonWazaEffect(FightOutPokemon*, u16, u32, bool, void*);
void* fightTargetDataBiosGetPtr(u32);
void* fightTargetDataBiosGetBuff(void*);
u16 wazaDB_GetWazawzxdataId(u16);
void* fightOutPokemon_GetSequencePtr(FightOutPokemon*);
void* fightOutPokemonCreateSequence(FightOutPokemon*, u32, s8);
void fightOutPokemonBiosCopy(void*, FightOutPokemon*);
void fightOutPokemon_SetSequencePtr(void*, void*);
void battleGridReplacePokemon(void*, void*);
void battleGridUpdate(void);
void Sequence_Free(void*);
void* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
void* fightPokemonGetPokemonPtr(void*);
s32 pokemonCheckRare(void*);
void* fightWaza_GetTargetDataId(void*);
void* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(void*, u8);
s32 fightWaza_GetDamage(void*);
void fightSeqFightOutPokemonEffect(u32, FightOutPokemon*, u32, u32);

u8 fightWazaWzxVariationFuncOiuchi(void) { return fight_seq_oiuchiflag == 1; }

s32 fightWazaWzxVariationFuncWeatherBall(void) {
    switch ((u8)fightFloorGetNowTenkouDataId(0, 1)) {
    case 0: return 0;
    case 2: return 1;
    case 4: return 2;
    case 1: return 3;
    case 3: return 4;
    case 5: return 5;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncIceball(void* unused, void* pokemon) {
    switch (fightOutPokemonGetCountAsJoutaiDataId(pokemon, 0x2f)) {
    case 1: return 0;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case -1: return 4;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncKawarawari(void) {
    switch (*(u8*)(UserWork + 0x10000 + 0x6002)) {
    case 0: return 3;
    case 1: return 2;
    case 2: return 1;
    case 3: return 0;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncNomikomu(void) {
    switch (*(u8*)(UserWork + 0x10000 + 0x6002)) {
    case 1:
    case 2: return 0;
    case 3: return 1;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncHakidasu(void) {
    switch (*(u8*)(UserWork + 0x10000 + 0x6002)) {
    case 1:
    case 2: return 0;
    case 3: return 1;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncWeatherHP(void) {
    switch ((u8)fightFloorGetNowTenkouDataId(0, 1)) {
    case 1: return 0;
    case 0: return 1;
    case 2:
    case 3:
    case 4:
    case 5: return 2;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncMagnitude(void* unused, void* pokemon) {
    switch (fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(pokemon))) {
    case 10:
    case 30: return 0;
    case 50:
    case 70:
    case 90: return 1;
    case 110:
    case 150: return 2;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncYatuatari(void* unused, void* pokemon) {
    u16 power = fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(pokemon));
    if (power > 89) {
        return 3;
    }
    if (power >= 62) {
        return 2;
    }
    return (u8)(power >= 22);
}

s32 fightWazaWzxVariationFuncPresent(void* unused, void* pokemon) {
    switch (fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(pokemon))) {
    case 40:
    case 80:
    case 120: return 0;
    }
    return 1;
}

s32 fightWazaWzxVariationFuncOngaesi(void* unused, void* pokemon) {
    u32 power = fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(pokemon));
    if (power <= 24) {
        return 0;
    }
    if (power <= 36) {
        return 1;
    }
    return (u32)-(power <= 80) + 3;
}

s32 fightWazaWzxVariationFuncRenzokugiri(void* unused, void* pokemon) {
    switch (fightOutPokemonGetCountAsJoutaiDataId(pokemon, 0x2e)) {
    case 1: return 0;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case 5: return 4;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncKorogaru(void* unused, void* pokemon) {
    switch (fightOutPokemonGetCountAsJoutaiDataId(pokemon, 0x2f)) {
    case 1: return 0;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case -1: return 4;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncTripleKick(void* unused, void* pokemon) {
    switch (fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(pokemon))) {
    case 10: return 0;
    case 20: return 1;
    case 30: return 2;
    }
    return 0;
}

s32 fightWazaWzxVariationFuncTikyuunage(void* unused, void* pokemon) {
    u32 level = (u8)figthOutPokemonGetLevel(pokemon);
    if (level < 33) {
        return 0;
    }
    return (u32)-(level < 66) + 2;
}

s32 fightWazaWzxVariationFuncKetaguri(void* unused, void* pokemon) {
    switch (fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(pokemon))) {
    case 20: return 0;
    case 40: return 1;
    case 60: return 2;
    case 80: return 3;
    case 100: return 4;
    case 120: return 5;
    }
    return 0;
}

void fightWazaWzxTypeFuncHuuin(u16 waza, FightOutPokemon* user, FightOutPokemon* a, u16 mode, bool flag) {
    u8 fightType = fightFloor_GetFightType(0);
    a = fightTargetGetPtr(0xf, user, fightType);
    FightOutPokemon* b = fightTargetGetPtr(0x10, user, fightType);
    fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
    fightOutPokemonLoadWazaEffect(a, waza, 2, flag);
    fightOutPokemonLoadWazaEffect(b, waza, 2, flag);
    if (fightOutPokemonCheckFightOut(a) == 1 && fightOutPokemonCheckFightOut(b) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(a, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(b, waza, false);
    } else if (fightOutPokemonCheckFightOut(b) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(b, waza, false);
    } else if (fightOutPokemonCheckFightOut(a) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(a, waza, false);
    } else {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
    }
}

void fightWazaWzxTypeFuncMigawari(u16 waza, FightOutPokemon* user) {
    void* oldSeq;
    u8 weather = fightFloorGetNowTenkouDataId(0, 1);
    wazaDB_GetWazawzxdataId(waza);
    oldSeq = fightOutPokemon_GetSequencePtr(user);
    void* newSeq = fightOutPokemonCreateSequence(user, weather, -1);
    u8 copy[0x898];
    fightOutPokemonBiosCopy(copy, user);
    fightOutPokemon_SetSequencePtr(copy, newSeq);
    fightOutPokemonLoadWazaEffect(user, waza, 1, false);
    fightOutPokemonLoadWazaEffect((FightOutPokemon*)copy, waza, 3, false);
    _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
    battleGridReplacePokemon(oldSeq, newSeq);
    battleGridUpdate();
    fightOutPokemon_SetSequencePtr(user, newSeq);
    _fightWazaWxzfightOutPokemonWazaEffectSpe(user, waza, false);
    Sequence_Free(oldSeq);
}

void fightWazaWzxTypeFuncHensin(u16 waza, FightOutPokemon* user) {
    void* oldSeq;
    u8 weather = fightFloorGetNowTenkouDataId(0, 1);
    wazaDB_GetWazawzxdataId(waza);
    oldSeq = fightOutPokemon_GetSequencePtr(user);
    s32 rare = pokemonCheckRare(fightPokemonGetPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(user)));
    void* newSeq = fightOutPokemonCreateSequence(user, weather, rare);
    u8 copy[0x898];
    fightOutPokemonBiosCopy(copy, user);
    fightOutPokemon_SetSequencePtr(copy, newSeq);
    fightOutPokemonLoadWazaEffect(user, waza, 3, false);
    fightOutPokemonLoadWazaEffect((FightOutPokemon*)copy, waza, 3, true);
    _fightWazaWxzfightOutPokemonWazaEffectSpe(user, waza, true);
    battleGridReplacePokemon(oldSeq, newSeq);
    battleGridUpdate();
    fightOutPokemon_SetSequencePtr(user, newSeq);
    _fightWazaWxzfightOutPokemonWazaEffectSpe(user, waza, false);
    Sequence_Free(oldSeq);
}

void fightWazaWzxTypeFuncKawarawari(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    fightOutPokemonLoadWazaEffect(user, waza, 1, false);
    fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
    _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
    _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
}

void fightWazaWzxTypeFuncMagiccort(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
    if (fightOutPokemonIsJoutaiDataId(target, 0x37) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, false);
    }
}

void fightWazaWzxTypeFuncNegaigoto(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
    _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, false);
}

void fightWazaWzxTypeFuncTedasuke(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    u8 fightType = fightFloor_GetFightType(0);
    fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightWaza_GetTargetDataId(fightOutPokemon_GetFightWazaPtr(user)), fightType);
    FightOutPokemon* ally = fightTargetGetPtr(0xe, user, fightType);
    fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
    fightOutPokemonLoadWazaEffect(ally, waza, 3, flag);
    _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
    if (fightOutPokemonCheckFightOut(ally) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectSpe(ally, waza, false);
    }
}

void fightWazaWzxTypeFuncAtt(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
    if (mode == 0) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, false);
    }
}

void fightWazaWzxTypeFuncItamiwake(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, false);
    } else {
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
    }
}

void fightWazaWzxTypeFuncAttDef(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, false);
    } else {
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
    }
}

void fightWazaWzxTypeFuncAllAlly(u16 waza, FightOutPokemon* user, FightOutPokemon* unused, u16 mode, bool flag) {
    FightOutPokemon* ally = fightTargetGetPtr(0xe, user, fightFloor_GetFightType(0));
    fightOutPokemonLoadWazaEffect(user, waza, 3, flag);
    fightOutPokemonLoadWazaEffect(ally, waza, 3, flag);
    if (fightOutPokemonCheckFightOut(ally) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectSpe(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectSpe(ally, waza, false);
    } else {
        _fightWazaWxzfightOutPokemonWazaEffectSpe(user, waza, false);
    }
}

void fightWazaWzxTypeFuncAllEnemy(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    FightOutPokemon* other = fightTargetGetPtr(0x10, user, fightFloor_GetFightType(0));
    fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
    fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
    fightOutPokemonLoadWazaEffect(other, waza, 2, flag);
    if (fightOutPokemonCheckFightOut(other) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(other, waza, false);
    } else {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
    }
}

void fightWazaWzxTypeFuncAttDefSpc(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        fightOutPokemonLoadWazaEffect(user, waza, 3, flag);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
    } else if (mode == 1) {
        fightOutPokemonLoadWazaEffect(user, waza, 3, flag);
        _fightWazaWxzfightOutPokemonWazaEffectSpe(user, waza, false);
    }
}

void fightWazaWzxTypeFuncVampire(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    s32 damage = fightWaza_GetDamage(fightOutPokemon_GetFightWazaPtr(user));
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        fightOutPokemonLoadWazaEffect(user, waza, 3, flag);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
    } else if (mode == 1) {
        fightOutPokemonLoadWazaEffect(user, waza, 3, flag);
        if (damage > 0) {
            fightSeqFightOutPokemonEffect(0x32, user, 0, 1);
        } else {
            _fightWazaWxzfightOutPokemonWazaEffectSpe(user, waza, false);
        }
    }
}

void fightWazaWzxTypeFuncSpc(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    fightOutPokemonLoadWazaEffect(user, waza, 3, flag);
    _fightWazaWxzfightOutPokemonWazaEffectSpe(user, waza, false);
}

void fightWazaWzxTypeFuncNormal(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag);

void fightWazaWzxTypeFuncTame(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    if (*(u8*)(UserWork + 0x10000 + 0x6002) != 1) {
        fightOutPokemonLoadWazaEffect(user, waza, 3, flag);
        _fightWazaWxzfightOutPokemonWazaEffectSpe(user, waza, false);
    } else {
        fightWazaWzxTypeFuncNormal(waza, user, target, mode, flag);
    }
}

void fightWazaWzxTypeFuncNormal2(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(user, waza, 1, false);
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
    } else {
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
    }
}

void fightWazaWzxTypeFuncNormal(u16 waza, FightOutPokemon* user, FightOutPokemon* target, u16 mode, bool flag) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(user, waza, 1, flag);
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(user, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
    } else {
        fightOutPokemonLoadWazaEffect(target, waza, 2, flag);
        _fightWazaWxzfightOutPokemonWazaEffectDef(target, waza, false);
    }
}

s32 fightWazaWzxVariationFuncNormal(void) { return 0; }
void fightWazaWzxTypeFuncNull(void) {}
s32 fightWazaWzxVariationFuncNull(void) { return 0; }

}

static void _fightWazaWxzfightOutPokemonWazaEffectSpe(FightOutPokemon* pokemon, u16 waza, bool flag) {
    fightOutPokemonWazaEffect(pokemon, waza, 3, flag, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
}

static void _fightWazaWxzfightOutPokemonWazaEffectDef(FightOutPokemon* pokemon, u16 waza, bool flag) {
    fightOutPokemonWazaEffect(pokemon, waza, 2, flag, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
}

static void _fightWazaWxzfightOutPokemonWazaEffectAtk(FightOutPokemon* pokemon, u16 waza, bool flag) {
    fightOutPokemonWazaEffect(pokemon, waza, 1, flag, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
}
