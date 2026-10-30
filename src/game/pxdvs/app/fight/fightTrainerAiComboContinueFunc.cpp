#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightPokemon;

extern "C" {
u16 HSD_Rand(void);
u8 fightAi_CanMoveAppointWaza(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightAi_CreateFightActionAttckIrekae(FightOutPokemon*, s16);
u8 fightAi_CreateFightActionAttckWaza(FightOutPokemon*, FightOutPokemon*, u16, s16);
u8 fightAi_GetTokuseiHaveFlag(u32, FightOutPokemon*, u16);
FightOutPokemon* fightAi_SelectDefPoke(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16, u16, s8);
u32 fightFloor_GetFightType(u32);
void* fightTargetGetPtrAsNowFightType(u32, void*);
void* fightTargetGetPtr(u16, void*, u16);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonLastUseWazaDataId(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER*, FightOutPokemon*, u16*, s16*, u8);
u8 fightTrainerAiIsFightOutPokemonAvoidCntHikui(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
s16 fightTrainerAiSelectIrekaeDasuFightPokemon(FIGHT_TRAINER*, u8, u8, FightOutPokemon*);
FightOutPokemon* getFightPokemonPtr__15FightOutPokemonFv(FightOutPokemon*);
}

extern "C" {
s8 _getWazaMaxValueIndex__FPUcPsUsUc(u8 *arg0, s16 *arg1, u16 arg2, u8 arg3);

s32 fightAiCombo_Batontatti_Zikoanzi_Continue(FIGHT_TRAINER* t, FightOutPokemon* p)
{
    u8 targetSpeed;
    FightOutPokemon* who;
    u8 type;
    u8 i;
    u8 value[4];
    u16 count;
    u16 want;
    u8 speed;
    u16 waza[4];
    FightOutPokemon* target;
    s8 best;
    u8 attack;
    s16 slot[4];
    u16 last;

    want = 0;
    type = fightFloor_GetFightType(0);
    count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, p, waza, slot, 1);
    last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, p);
    target = (FightOutPokemon*)fightTargetGetPtr(0xE, p, type);
    attack = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, p);
    speed = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, p);
    targetSpeed = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, target);

    switch (last) {
    case 0xB6:
        if (speed >= 7) {
            want = 0xE2;
        }
        break;
    case 0xF4:
        if (speed >= 7) {
            want = 0xE2;
        }
        break;
    case 0xFC:
        if (targetSpeed >= 7) {
            want = 0xF4;
        }
        break;
    default:
        if (attack >= 7 && speed >= 7) {
            want = 0xB6;
        }
        break;
    }

    for (i = 0; i < count; i++) {
        value[slot[i]] = 0x32;
        if (fightAi_CanMoveAppointWaza(t, p, waza[i]) == 0) {
            value[slot[i]] = 0;
        }
        if (want != waza[i] || want == 0) {
            value[slot[i]] = 0;
        }
    }

    best = _getWazaMaxValueIndex__FPUcPsUsUc(value, slot, count, 0);
    if (best < 0) {
        return 0;
    }
    if (want == 0xF4) {
        who = target;
    } else {
        who = p;
    }
    if (who == 0) {
        return 0;
    }
    fightAi_CreateFightActionAttckWaza(p, who, waza[best], slot[best]);
    return 1;
}

s32 fightAiCombo_Batontatti_Nekodamasi_Continue(FIGHT_TRAINER* t, FightOutPokemon* p)
{
    s8 best;
    u16 last;
    u16 want;
    u8 value[4];
    u8 i;
    u16 waza[4];
    s16 slot[4];
    u8 attack;
    u16 count;
    u8 speed;

    want = 0;
    count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, p, waza, slot, 1);
    last = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(t, p);
    attack = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(t, p);
    speed = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(t, p);

    if (last == 0xB6 && speed >= 7) {
        want = 0xE2;
    }
    if (last != 0xB6 && attack >= 7 && speed >= 7) {
        want = 0xB6;
    }

    for (i = 0; i < count; i++) {
        value[slot[i]] = 0x32;
        if (fightAi_CanMoveAppointWaza(t, p, waza[i]) == 0) {
            value[slot[i]] = 0;
        }
        if (want != waza[i] || want == 0) {
            value[slot[i]] = 0;
        }
    }

    best = _getWazaMaxValueIndex__FPUcPsUsUc(value, slot, count, 0);
    if (best < 0) {
        return 0;
    }
    if (p == 0) {
        return 0;
    }
    fightAi_CreateFightActionAttckWaza(p, p, waza[best], slot[best]);
    return 1;
}

s32 fightAiCombo_Sukirusuwappu_Irekae_Continue(FIGHT_TRAINER *arg0, FightOutPokemon *arg1)
{
    u16 wazaIds[4];
    s16 wazaVals[4];
    u8 temp_r31;
    s16 entry;

    temp_r31 = fightFloor_GetFightType(0);
    fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, wazaIds, wazaVals, 1);

    if (fightAi_GetTokuseiHaveFlag((u32)arg0, arg1, 0x36) != 2) {
        return 0;
    }
    if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, (FightPokemon*)getFightPokemonPtr__15FightOutPokemonFv(arg1), 0x36) == 1) {
        return 0;
    }
    entry = fightTrainerAiSelectIrekaeDasuFightPokemon(arg0, temp_r31, 1, arg1);
    if (entry < 0) {
        return 0;
    }

    fightAi_CreateFightActionAttckIrekae(arg1, entry);
    return 1;
}

s32 fightAiCombo_Amaikaori_Hubuki_Continue(FIGHT_TRAINER* t, FightOutPokemon* p, FightOutPokemon** opp, u16 oppCnt)
{
    u8 value[4];
    u16 waza[4];
    s8 best;
    u16 count;
    s16 slot[4];
    u8 i;
    FightOutPokemon* who;
    u8 n;

    count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(t, p, waza, slot, 1);
    n = 0;
    for (i = 0; i < oppCnt; i++) {
        if (opp[i] != 0 && fightTrainerAiIsFightOutPokemonAvoidCntHikui(t, opp[i]) == 1) {
            n++;
        }
    }
    if (n == 0) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        value[slot[i]] = 0x32;
        if (fightAi_CanMoveAppointWaza(t, p, waza[i]) == 0) {
            value[slot[i]] = 0;
        }
        if (waza[i] != 0x3B && waza[i] != 0x9D) {
            value[slot[i]] = 0;
        }
    }
    best = _getWazaMaxValueIndex__FPUcPsUsUc(value, slot, count, 0);
    if (best < 0) {
        return 0;
    }
    if (n >= 2) {
        who = fightAi_SelectDefPoke(t, p, opp, oppCnt, waza[best], -1);
    } else {
        for (n = 0; n < oppCnt; n++) {
            if (opp[n] != 0 && fightTrainerAiIsFightOutPokemonAvoidCntHikui(t, opp[n]) == 1) {
                who = opp[n];
                break;
            }
        }
    }
    if (who == 0) {
        return 0;
    }
    fightAi_CreateFightActionAttckWaza(p, who, waza[best], slot[best]);
    return 1;
}

s32 fightAiCombo_null_Continue(void)
{
    return 0;
}

s8 _getWazaMaxValueIndex__FPUcPsUsUc(u8* value, s16* slot, u16 count, u8 min)
{
    u8 buf[0x40];
    u8 best;
    u8 n;
    u8 i;
    s8 result;
    s8 pick;

    best = min;
    for (i = 0; i < count; i++) {
        u8 v = value[slot[i]];
        if (v > best) {
            buf[0] = i;
            best = v;
            n = 1;
        } else if (best == v && best > min) {
            buf[n] = i;
            n++;
        }
    }
    pick = buf[HSD_Rand() % n];
    result = -1;
    if (best > min) {
        result = pick;
    }
    return result;
}
}
