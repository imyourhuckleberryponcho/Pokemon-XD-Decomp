#include <dolphin/types.h>

// WIP (GXXE01, -O4,s): ten functions match. CheckAbiCnt has the correct
// instruction count but 7 prologue/selection differences. Keep NonMatching.
// Verification: build/scratch/ai-finish-verification.txt.

struct FIGHT_TRAINER;
struct FightOutPokemon;

extern "C" {
u16 wazaDB_GetSeqId(u16);
u8 fightFloorLoopValidFightOutPokemon(u8, s32 (*)(void*, void*, void*), void*, u8);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightTrainerIsAllyFightTargetPtr(FIGHT_TRAINER*, FightOutPokemon*, void*);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(s32, s32, u16);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(s32, s32, u16);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
u16 fightTrainerDB_GetAiDataId(u16);
u8 fightTrainerAiDB_GetZokuseiCheckFlag(u16);
u8 fightSeqGetTextureZokuseiAry(void*, u16*);
s32 fightTargetGetPtrAsNowFightType(u8, s32);
u16 fightSeqCondChgActTypeToPokemonStatusId(void*);
s8 pokemonGetStatus(void*, u8, u16, u8);
s8 fightSeqCondChgActParaIdToValue(void*);
u8 fightSideIsJoutaiDataId(s32, u16);
u8 fightSeqIsGuard(void*, u16);
u8 fightTrainerAiDB_GetPokemonJoutaiFlag(u16);
u16 fightOutPokemon_GetOumuWazaDataId(FightOutPokemon*);
u8 fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(FightOutPokemon*, u16*);
s32 HSD_Rand(void);
u8 fightTrainerAiCheckGuard(s32, s32, u16);
}

struct LoopCount {
    void* first;
    s32 count;
};

struct SawaguArgs {
    void* pokemon;
    void* trainer;
};

extern "C" {
static s32 _fightTrainerAiCheckHorobinoutaSub(void*, void*, void*);
static s32 _fightTrainerAiSimerikeCheckSub(void*, void*, void*);
static s32 _fightTrainerAiSawaguCheckSub(void*, void*, void*);
}

extern "C" {
u8 fightTrainerAiCheckJoutaiKieWazaHitWazaDataId(void*, u16 condition, u16 waza)
{
    u16 seq = wazaDB_GetSeqId(waza);
    if (condition == 0x1f && (seq == 0x92 || seq == 0x95 || seq == 0x98 || seq == 0xcf)) return 1;
    if (condition == 0x20 && seq == 0x93) return 1;
    if (condition == 0x21 && (waza == 0x39 || waza == 0xfa)) return 1;
    if (seq == 0x5e) return 1;
    return 0;
}

u16 fightTrainerAiCheckHorobinouta(FIGHT_TRAINER* trainer)
{
    LoopCount data;
    data.first = trainer;
    data.count = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightTrainerAiCheckHorobinoutaSub, &data, 0);
    return (u16)data.count;
}

s32 _fightTrainerAiCheckHorobinoutaSub(void* currentPtr, void* targetPtr, void* dataPtr)
{
    LoopCount* data = (LoopCount*)dataPtr;
    FightOutPokemon* current = (FightOutPokemon*)currentPtr;
    FIGHT_TRAINER* first = (FIGHT_TRAINER*)data->first;
    if (!fightOutPokemonCheckFightOut((FightOutPokemon*)currentPtr)) return 1;
    if (fightTrainerIsAllyFightTargetPtr(first, current, targetPtr) == 1) return 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId((s32)first, (s32)current, 0x1e) != 1 &&
        fightTrainerAiIsFightOutPokemonTokuseiDataId((s32)first, (s32)current, 0x2b) != 1) {
        data->count++;
    }
    return 1;
}

u8 fightTrainerAiCheckTextureZokusei(FIGHT_TRAINER* trainer, void* pokemon)
{
    u16 data[4];
    if (fightTrainerAiDB_GetZokuseiCheckFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer))) == 1) {
        return fightSeqGetTextureZokuseiAry(pokemon, data) >= 1;
    }
    return 1;
}

 s32 fightTrainerAiCheckAbiCnt(s32 arg0, s32 arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5, u32 arg6)
{
    s32 temp_r21;
    s32 var_r30;
    u16 temp_r3;
    u8 var_r28;
    u8 var_r27;
    int temp_r26;
    var_r28 = 0;
    var_r27 = 0;
    if (arg6 & 0x40) var_r30 = arg1;
    else var_r30 = arg2;
    temp_r21 = fightTargetGetPtrAsNowFightType(2, var_r30);
    u8 flags = arg6;
    u8 maskedFlags = flags & 0xbf;
    if (maskedFlags & 0x80) var_r28 = 1;
    if (flags & 0x20) var_r27 = 1;
    temp_r3 = fightSeqCondChgActTypeToPokemonStatusId((void*)arg5);
    temp_r26 = pokemonGetStatus((void*)var_r30, 0, temp_r3, 0);
    if (fightSeqCondChgActParaIdToValue((void*)arg4) < 0) {
        if (fightSideIsJoutaiDataId(temp_r21, 0x4c) == 1 && var_r28 == 0 && arg3 != 0xae) return 0;
        if (arg3 != 0xae && var_r27 != 1 && fightTrainerAiCheckGuard(arg0, arg2, arg3) == 1) return 0;
        if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, var_r30, 0x1d) == 1 ||
             fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, var_r30, 0x49) == 1) &&
            var_r28 == 0 && arg3 != 0xae) return 0;
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, var_r30, 0x33) == 1 &&
            var_r28 == 0 && temp_r3 == 0xeb) return 0;
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, var_r30, 0x34) == 1 &&
            var_r28 == 0 && temp_r3 == 0xe6) return 0;
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, var_r30, 0x13) == 1 &&
            !(flags & 0x1f)) return 0;
        if ((s8)temp_r26 <= 0) return 0;
    } else if (temp_r26 >= 0xc) {
        return 0;
    }
    return 1;
}

u8 fightTrainerAiCheckGuard(s32 trainer, s32 target, u16 move)
{
    u16 trainerId = fightTrainer_GetFightTrainerDataId((FIGHT_TRAINER*)trainer);
    u16 aiId = fightTrainerDB_GetAiDataId(trainerId);
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(aiId) == 1 && fightSeqIsGuard((void*)target, move) == 1) return 1;
    return 0;
}

u16 fightTrainerAiCheckOumu(void* unused, FightOutPokemon* pokemon)
{
    u16 moves[8];
    u16 move = fightOutPokemon_GetOumuWazaDataId(pokemon);
    if (move != 0 && move != 0x176 && move != 0xffff) return move;
    u8 count = fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(pokemon, moves);
    if (count != 0) {
        u16 random = (u16)HSD_Rand();
        u8 index = (u8)(random % count);
        move = moves[index];
        if (move != 0 && move != 0x176) return move;
    }
    return 0;
}

s32 fightTrainerAiCheckSimerike(void* trainer)
{
    LoopCount data;
    s32 result;
    data.first = trainer;
    result = fightFloorLoopValidFightOutPokemon(0, _fightTrainerAiSimerikeCheckSub, &data, 0);
    if (result == 1) return 0;
    return 1;
}

s32 _fightTrainerAiSimerikeCheckSub(void* currentPtr, void* unused, void* dataPtr)
{
    FightOutPokemon* pokemon = (FightOutPokemon*)*(void**)dataPtr;
    FightOutPokemon* current = (FightOutPokemon*)currentPtr;
    if (fightOutPokemonCheckFightOut(current) == 0) return 1;
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId((s32)pokemon, (s32)current, 6) == 1) return 0;
    return 1;
}

s32 fightTrainerAiCheckSawagu(void* trainer, void* target)
{
    SawaguArgs data;
    s32 result;
    data.pokemon = trainer;
    data.trainer = target;
    result = fightFloorLoopValidFightOutPokemon(0, _fightTrainerAiSawaguCheckSub, &data, 0);
    if (result == 1) return 0;
    return 1;
}

s32 _fightTrainerAiSawaguCheckSub(void* currentPtr, void* unused, void* dataPtr)
{
    s32 temp_r31;
    s32 temp_r30;
    temp_r31 = *(s32*)dataPtr;
    temp_r30 = *(s32*)((u8*)dataPtr + 4);
    if (!fightOutPokemonCheckFightOut((FightOutPokemon*)currentPtr)) return 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(temp_r31, (s32)currentPtr, 0xb) == 1 &&
        fightTrainerAiIsFightOutPokemonTokuseiDataId(temp_r31, temp_r30, 0x2b) == 0) return 0;
    return 1;
}
}

