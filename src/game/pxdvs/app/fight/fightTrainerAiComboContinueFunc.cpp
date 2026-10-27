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
u32 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER*, FightOutPokemon*);
u32 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonLastUseWazaDataId(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER*, FightOutPokemon*, u16*, s16*, u8);
u8 fightTrainerAiIsFightOutPokemonAvoidCntHikui(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
s16 fightTrainerAiSelectIrekaeDasuFightPokemon(FIGHT_TRAINER*, u8, u8, FightOutPokemon*);
FightOutPokemon* getFightPokemonPtr__15FightOutPokemonFv(FightOutPokemon*);
}

extern "C" {
s8 _getWazaMaxValueIndex__FPUcPsUsUc(u8 *arg0, s16 *arg1, u16 arg2, u8 arg3);

s32 fightAiCombo_Batontatti_Zikoanzi_Continue(FIGHT_TRAINER *arg0, FightOutPokemon *arg1)
{
    u8 sp8[50];
    u16 sp14[25];
    s16 spC[25];
    u8 var_r26;
    FightOutPokemon *var_r4;
    u32 temp_r29;
    s8 temp_r3_2;
    u16 temp_r25;
    u16 temp_r27;
    u16 var_r24;
    u8 temp_r20;
    volatile u8 temp_r20_2;
    u32 temp_r26;
    u32 temp_r3;
    FightOutPokemon *temp_r23;

    var_r24 = 0;
    temp_r20 = fightFloor_GetFightType(0);
    temp_r25 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp14, spC, 1);
    temp_r27 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg1);
    temp_r23 = (FightOutPokemon*)fightTargetGetPtr(0xE, arg1, temp_r20);
    temp_r26 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1);
    temp_r20_2 = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg1);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, temp_r23);

    switch ((s32) temp_r27) {
    case 0xB6:
        if (temp_r20_2 >= 7U) {
            var_r24 = 0xE2;
        }
        break;
    case 0xF4:
        if (temp_r20_2 >= 7U) {
            var_r24 = 0xE2;
        }
        break;
    case 0xFC:
        if (temp_r3 >= 7U) {
            var_r24 = 0xF4;
        }
        break;
    default:
        if ((temp_r26 >= 7U) && (temp_r20_2 >= 7U)) {
            var_r24 = 0xB6;
        }
        break;
    }

    var_r26 = 0;
    while ((s32) var_r26 < (s32) temp_r25) {
        temp_r29 = var_r26;
        temp_r29 *= 2;
        sp8[spC[temp_r29 / 2]] = 0x32;
        if (fightAi_CanMoveAppointWaza(arg0, arg1, sp14[temp_r29 / 2]) == 0) {
            sp8[spC[temp_r29 / 2]] = 0;
        }
        if ((var_r24 != sp14[temp_r29 / 2]) || (var_r24 == 0)) {
            sp8[spC[temp_r29 / 2]] = 0;
        }
        var_r26 += 1;
    }

    temp_r3_2 = _getWazaMaxValueIndex__FPUcPsUsUc(sp8, spC, temp_r25, 0U);
    if (temp_r3_2 < 0) {
        return 0;
    }

    if (var_r24 == 0xF4) {
        var_r4 = temp_r23;
    } else {
        var_r4 = arg1;
    }
    if (var_r4 == 0) {
        return 0;
    }

    fightAi_CreateFightActionAttckWaza(arg1, var_r4, sp14[temp_r3_2], spC[temp_r3_2]);
    return 1;
}

s32 fightAiCombo_Batontatti_Nekodamasi_Continue(FIGHT_TRAINER *arg0, FightOutPokemon *arg1)
{
    u8 var_r27;
    u16 sp14[25];
    s16 spC[25];
    u32 temp_r22;
    s8 temp_r3_2;
    u16 temp_r26;
    u16 temp_r27;
    u16 var_r22;
    u32 temp_r23;
    u32 temp_r3;
    u8 sp8[50];

    var_r22 = 0;
    temp_r26 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp14, spC, 1);
    temp_r27 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg1);
    temp_r23 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg1);

    if ((temp_r27 == 0xB6) && (temp_r3 >= 7U)) {
        var_r22 = 0xE2;
    }
    if ((temp_r27 != 0xB6) && (temp_r23 >= 7U) && (temp_r3 >= 7U)) {
        var_r22 = 0xB6;
    }

    var_r27 = 0;
    while ((s32) var_r27 < (s32) temp_r26) {
        temp_r22 = var_r27;
        temp_r22 *= 2;
        sp8[spC[temp_r22 / 2]] = 0x32;
        if (fightAi_CanMoveAppointWaza(arg0, arg1, sp14[temp_r22 / 2]) == 0) {
            sp8[spC[temp_r22 / 2]] = 0;
        }
        if ((var_r22 != sp14[temp_r22 / 2]) || (var_r22 == 0)) {
            sp8[spC[temp_r22 / 2]] = 0;
        }
        var_r27 += 1;
    }

    temp_r3_2 = _getWazaMaxValueIndex__FPUcPsUsUc(sp8, spC, temp_r26, 0U);
    if (temp_r3_2 < 0) {
        return 0;
    }
    if (arg1 == 0) {
        return 0;
    }

    fightAi_CreateFightActionAttckWaza(arg1, arg1, sp14[temp_r3_2], spC[temp_r3_2]);
    return 1;
}

s32 fightAiCombo_Sukirusuwappu_Irekae_Continue(FIGHT_TRAINER *arg0, FightOutPokemon *arg1)
{
    u8 temp_r31;

    temp_r31 = fightFloor_GetFightType(0);
    fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, 0, 0, 1);

    if (fightAi_GetTokuseiHaveFlag((u32)arg0, arg1, 0x36) != 2) {
        return 0;
    }
    if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, (FightPokemon*)getFightPokemonPtr__15FightOutPokemonFv(arg1), 0x36) == 1) {
        return 0;
    }
    if (fightTrainerAiSelectIrekaeDasuFightPokemon(arg0, temp_r31, 1, arg1) < 0) {
        return 0;
    }

    fightAi_CreateFightActionAttckIrekae(arg1, 0);
    return 1;
}

s32 fightAiCombo_Amaikaori_Hubuki_Continue(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, FightOutPokemon **arg2, u16 arg3)
{
    s16 spC[25];
    u16 sp14[25];
    u8 sp8[50];
    s32 temp_r18;
    u32 temp_r26;
    s8 temp_r3;
    u16 temp_r0;
    u16 temp_r21;
    FightOutPokemon *var_r20;
    u8 var_r19;
    u8 var_r19_2;
    u8 var_r22;
    u8 var_r22_2;

    var_r20 = 0;
    temp_r21 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp14, spC, 1);
    var_r19 = 0;
    var_r22 = 0;

    while ((s32) var_r22 < (s32) arg3) {
        if ((arg2[var_r22] != 0) && (fightTrainerAiIsFightOutPokemonAvoidCntHikui(arg0, arg1) == 1)) {
            var_r19 += 1;
        }
        var_r22 += 1;
    }

    if (var_r19 == 0) {
        return 0;
    }

    var_r22_2 = 0;
    while ((s32) var_r22_2 < (s32) temp_r21) {
        temp_r26 = var_r22_2 * 2;
        sp8[spC[temp_r26 / 2]] = 0x32;
        if (fightAi_CanMoveAppointWaza(arg0, arg1, sp14[temp_r26 / 2]) == 0) {
            sp8[spC[temp_r26 / 2]] = 0;
        }
        temp_r0 = sp14[temp_r26 / 2];
        if ((temp_r0 != 0x3B) && (temp_r0 != 0x9D)) {
            sp8[spC[temp_r26 / 2]] = 0;
        }
        var_r22_2 += 1;
    }

    temp_r3 = _getWazaMaxValueIndex__FPUcPsUsUc(sp8, spC, temp_r21, 0U);
    if (temp_r3 < 0) {
        return 0;
    }

    if (var_r19 >= 2U) {
        var_r20 = fightAi_SelectDefPoke(arg0, arg1, arg2, arg3, sp14[temp_r3], -1);
    } else {
        var_r19_2 = 0;
        while ((s32) var_r19_2 < (s32) arg3) {
            if ((arg2[var_r19_2] != 0) && (fightTrainerAiIsFightOutPokemonAvoidCntHikui(arg0, arg1) == 1)) {
                var_r20 = arg2[var_r19_2];
                break;
            }
            var_r19_2 += 1;
        }
    }

    if (var_r20 == 0) {
        return 0;
    }

    fightAi_CreateFightActionAttckWaza(arg1, var_r20, sp14[temp_r3], spC[temp_r3]);
    return 1;
}

s32 fightAiCombo_null_Continue(void)
{
    return 0;
}

s8 _getWazaMaxValueIndex__FPUcPsUsUc(u8 *arg0, s16 *arg1, u16 arg2, u8 arg3)
{
    u8 sp8[10];
    s8 temp_r0_2;
    s8 var_r3;
    u8 temp_r0;
    u8 temp_r7;
    u8 var_r29;
    u8 var_r30;
    u8 var_r9;

    var_r29 = 1;
    var_r9 = 0;
    var_r30 = arg3;

    while ((s32) var_r9 < (s32) arg2) {
        temp_r7 = arg0[arg1[var_r9]];
        if (temp_r7 > var_r30) {
            sp8[0] = var_r9;
            var_r30 = temp_r7;
            var_r29 = 1;
        } else if ((var_r30 == temp_r7) && (var_r30 > arg3)) {
            temp_r0 = var_r29;
            var_r29 += 1;
            sp8[temp_r0] = var_r9;
        }
        var_r9 += 1;
    }

    var_r3 = -1;
    temp_r0_2 = (s8) sp8[HSD_Rand() % var_r29];
    if (var_r30 > arg3) {
        var_r3 = temp_r0_2;
    }
    return var_r3;
}
}
