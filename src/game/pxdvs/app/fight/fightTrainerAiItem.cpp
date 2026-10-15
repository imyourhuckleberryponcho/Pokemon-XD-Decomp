#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightPokemon;
struct Pokemon;
struct FightActionData;

extern "C" {
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
u16 fightTrainerDB_GetAiDataId(u16);
u16 fightTrainerGetTemotiNormalItemDataIdAry(FIGHT_TRAINER*, u16*, u16, u8);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void*, FIGHT_TRAINER*, FightOutPokemon**, u8, u8);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(void*, FIGHT_TRAINER*, FightPokemon**, u8, u8);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
u8 itemDataCheckValid(u16);
u8 fightSeqGetItemType(u16, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonPartDataId(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(FIGHT_TRAINER*, FightOutPokemon*);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u8 pokemonIsDarkPokemon(Pokemon*);
s32 fightTrainerAiAddValueByAddsubDataId(s32, FIGHT_TRAINER*, u16);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
u8 fightPokemonCheckFightOut(FightPokemon*);
s32 fightTrainerAiGetValueAryMaxBanme(s32*, u16, u8);
s32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, void*);
void fightOutPokemonCreateFightActionUseItem(FightOutPokemon*, u8, u16, u16, FightActionData*, u16, s32, s32, u8);
s16 itemUse2PokemonSimulation(void*, Pokemon*, FightPokemon*, u16, u8);
extern FightActionData fight_action_data_item;
}

static u8 _fightTrainerAiSelectFightActionItemSubCheckUseItem(FIGHT_TRAINER*, FightOutPokemon*, u16);

extern "C" {
u8 fightTrainerAiSelectFightActionItem(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, void* target)
{
    FightOutPokemon* p;
    u16 i;
    u16 partyCount;
    u16 activeCount;
    u16 j;
    u16 itemCount;
    u8 allStatsHigh;
    s32 values[30];
    FightPokemon* party[24];
    u16 items[30];
    FightOutPokemon* active[8];
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
 // Preserve the retail flag logic: both initialization and the loop write zero.
    allStatsHigh = 0;
    itemCount = fightTrainerGetTemotiNormalItemDataIdAry(trainer, items, 30, 1);
    if (itemCount == 0) return 0;
    activeCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, active, 1, 1);
    partyCount = fightFloorGetFightTrainerFightPokemonPtrAry(0, trainer, party, 1, 1);
    for (i = 0; i < activeCount; i++) {
        p = active[i];
        if (p != 0 && fightOutPokemonCheckFightOut(p) != 0 &&
            fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer, p) == 1) {
            allStatsHigh = 0;
        }
    }
    for (u16 k = 0; k < 30; k++) values[k] = 0;
    for (j = 0; j < itemCount; j++) {
        u16 item = items[j];
        if (item == 0 || !itemDataCheckValid(item)) continue;
        u8 type = fightSeqGetItemType(item, pokemon);
        if (type == 7 || !_fightTrainerAiSelectFightActionItemSubCheckUseItem(trainer, pokemon, item)) continue;
        if ((type == 2 || type == 1) && fightTrainerAiIsFightOutPokemonNokoriHpHikui(trainer, pokemon) == 1) {
            if (!pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(pokemon))) {
                values[j] = fightTrainerAiAddValueByAddsubDataId(values[j], trainer, 0x32);
            }
        }
        if ((type == 3 || type == 1) && fightTrainerAiIsFightOutPokemonJoutaiNormal(trainer, pokemon) == 0) {
            if (!pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(pokemon))) {
                values[j] = fightTrainerAiAddValueByAddsubDataId(values[j], trainer, 0x33);
            }
        }
        if (type == 5 && fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer, pokemon) == 0) {
            values[j] = fightTrainerAiAddValueByAddsubDataId(values[j], trainer, 0x34);
        }
        if (type == 4 && fightTrainerAiGetFightOutPokemonPartDataId(trainer, pokemon) == 2) {
            values[j] = fightTrainerAiAddValueByAddsubDataId(values[j], trainer, 0x35);
        }
        if (type == 6 && allStatsHigh == 1) {
            values[j] = fightTrainerAiAddValueByAddsubDataId(values[j], trainer, 0x36);
        }
        if (fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer, pokemon) != 2 &&
            fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer, pokemon) != 3) {
            for (i = 0; i < partyCount; i++) {
                if (fightOutPokemon_GetMotoFightPokemonPtr(pokemon) != party[i] &&
                    (fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer, pokemon) == 2 ||
                     fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer, pokemon) == 3) &&
                    fightPokemonCheckFightOut(party[i]) == 1) {
                    values[j] = fightTrainerAiAddValueByAddsubDataId(values[j], trainer, 0x37);
                    break;
                }
            }
        }
    }
    u16 selected;
    for (selected = 0; selected < itemCount; selected++) {
        if (values[selected] > 0) break;
    }
    if (selected >= itemCount) return 0;
 // Retail checks the maximum-index result but keeps the first positive entry.
    if (fightTrainerAiGetValueAryMaxBanme(values, itemCount, 1) < 0) return 0;
    u16 item = items[selected];
    if (item == 0) return 0;
    s32 targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(pokemon, target);
    fightOutPokemonCreateFightActionUseItem(pokemon, 0, 0x12, 0, &fight_action_data_item, item, targetId, -1, 0);
    return 1;
}
}

static u8 _fightTrainerAiSelectFightActionItemSubCheckUseItem(FIGHT_TRAINER*, FightOutPokemon* pokemon, u16 item)
{
    u8 result[0x100];
    return itemUse2PokemonSimulation(result, 0, fightOutPokemon_GetMotoFightPokemonPtr(pokemon), item, 0) > 0;
}
