#include <dolphin/types.h>
#pragma dont_inline on
typedef struct FightOutPokemon FightOutPokemon;

static s32 _fightTrainerAiWazaHitCheck(void*, u32, u32, u32, u32);
static s32 _fightTrainerAiWazaHitAbicnt(void*, u32, u32, u32, u32, u32, u32);
static s32 _fightTrainerAiWazaHitJisin(void*, u32, u32, u32);
static s32 _fightTrainerAiWazaHitWeatherKaifuku(void*, u32);
static u8 _fightTrainerAiWazaHitCheckTokusei(void*, u32, u32);

s32 fightTrainerAiWazaHit000(void*,u32,u32,u32);
s32 fightTrainerAiWazaHit002(void*,u32,u32,u32);
s32 fightTrainerAiWazaHit004(void*,u32,u32,u32);
s32 fightTrainerAiWazaHit029(void*,u32,u32,u32);
s32 fightTrainerAiWazaHit039(void*,u32,u32,u32);
u32 fightTrainerAiWazaHit111(void*,u32,u32,u32);
s32 fightTrainerAiWazaHit121(void*,u32,u32,u32);
s32 fightTrainerAiWazaHit146(void*,u32,u32,u32);

s32 fightTrainerAiWazaHit217(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit216(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    void* side = fightTargetGetPtrAsNowFightType(2, param3);
    if (!fightSideIsJoutaiDataId(side, 0x48) && !fightSideIsJoutaiDataId(side, 0x49) && !fightSideIsJoutaiDataId(side, 0x4b)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit215(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiGetFightFloorNowTenkouDataId(void*, u32, u32);
    return fightTrainerAiGetFightFloorNowTenkouDataId(ctx, 0, 1) != 5;
}

s32 fightTrainerAiWazaHit214(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x90, 7, 1);
}

s32 fightTrainerAiWazaHit213(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightFloor_GetTikeiDataId(u32);
    extern u32 tikeiDataBiosGetZokuseiDataId(u8);
    extern u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(void*, u32, u8);
    u32 value;
    u32 result;
    value = tikeiDataBiosGetZokuseiDataId(fightFloor_GetTikeiDataId(0));
    result = fightTrainerAiIsFightOutPokemonZokuseiDataId(ctx, param1, value);
    result = result != 1;
    return result;
}

u32 fightTrainerAiWazaHit212(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(void*, u32);
    extern u32 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(void*,u32);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    u32 firstStatus;
    u32 secondStatus;

    firstStatus = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(ctx,param1);
    secondStatus = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(ctx, param1);
    if ((firstStatus & 0xff) >= 0xc) {
        if ((secondStatus & 0xff) >= 0xc) {
            return 0;
        }
    }
    if ((fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 1, 0x41) & 0xff) == 0) {
        if ((fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 3, 0x41) & 0xff) == 0) {
            return 0;
        }
    }
    return 1;
}

u32 fightTrainerAiWazaHit211(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(void*, u32);
    extern u32 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(void*, u32);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    u32 firstStatus;
    u32 secondStatus;

    firstStatus = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(ctx, param1);
    secondStatus = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(ctx, param1);
    if ((firstStatus & 0xff) >= 0xc) {
        if ((secondStatus & 0xff) >= 0xc) {
            return 0;
        }
    }
    if ((fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 4, 0x41) & 0xff) == 0) {
        if ((fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 5, 0x41) & 0xff) == 0) {
            return 0;
        }
    }
    return 1;
}

int fightTrainerAiWazaHit210(u32 r3, u32 r4)
{

    extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(u32,u32,u32);
  u32 uVar1;
  uVar1 = fightTrainerAiIsFightOutPokemonJoutaiDataId(r3, r4, 0x39);
  return (uVar1 & 0xFF) != 1;
}

s32 fightTrainerAiWazaHit209(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit002(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit208(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(void*, u32);
    extern u32 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(void*, u32);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    u32 firstStatus;
    u32 secondStatus;

    firstStatus = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(ctx, param1);
    secondStatus = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(ctx, param1);
    if ((firstStatus & 0xff) >= 0xc) {
        if ((secondStatus & 0xff) >= 0xc) {
            return 0;
        }
    }
    if ((fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 1, 0x41) & 0xff) == 0) {
        if ((fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 2, 0x41) & 0xff) == 0) {
            return 0;
        }
    }
    return 1;
}

s32 fightTrainerAiWazaHit207(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit206(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(void*, u32);
    extern u32 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(void*, u32);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    u32 firstStatus;
    u32 secondStatus;

    firstStatus = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(ctx, param1);
    secondStatus = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(ctx, param1);
    if ((firstStatus & 0xff) >= 0xc) {
        if ((secondStatus & 0xff) >= 0xc) {
            return 0;
        }
    }
    if ((fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 2, 0x41) & 0xff) == 0) {
        if ((fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 5, 0x41) & 0xff) == 0) {
            return 0;
        }
    }
    return 1;
}

s32 fightTrainerAiWazaHit205(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(void* ctx, u32 elem);
    extern u8 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(void* ctx, u32 elem);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    u8 a = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(ctx, param3);
    u8 b = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(ctx, param3);

    if (a == 0 && b == 0) {
        return 0;
    }
    if (fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x90, 1, 1) != 0) {
        goto ret1;
    }
    if (fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x90, 2, 1) != 0) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}

s32 fightTrainerAiWazaHit204(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit203(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiGetFightFloorNowTenkouDataId(void* ctx, u32 zero, u32 one);
    extern u32 fightTrainerAiGetWazaIryoku(void* ctx, u32 param2);
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void* ctx, u32 param3, u32 v1, u32 v3);
    u8 state = fightTrainerAiGetFightFloorNowTenkouDataId(ctx, 0, 1);
    s32 gate;
    u32 v1;

    if (state == 2) {
        v1 = 0xb;
    } else if (state == 3) {
        v1 = 0x5;
    } else if (state == 1) {
        v1 = 0xa;
    } else if (state == 4) {
        v1 = 0xf;
    } else {
        v1 = 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, v1, fightTrainerAiGetWazaIryoku(ctx, param2)) == 0x43) {
        gate = 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit202(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

int fightTrainerAiWazaHit201(u32 r3, u32 r4)
{

    extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(u32,u32,u32);
  u32 uVar1;
  uVar1 = fightTrainerAiIsFightOutPokemonJoutaiDataId(r3, r4, 0x38);
  return (uVar1 & 0xFF) != 1;
}

s32 fightTrainerAiWazaHit200(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit004(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit199(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    void* side = fightTargetGetPtrAsNowFightType(2, param3);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 9)) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 9) == 1) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightSideIsJoutaiDataId(side, 0x4b) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit198(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit197(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit196(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit195(void) { return 1; }

int fightTrainerAiWazaHit194(u32 r3, u32 r4, u32 r5, u32 r6)

{
  extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(u32,u32,u32);
  u32 uVar1;

  uVar1 = fightTrainerAiIsFightOutPokemonJoutaiDataId(r3,r6,0x28);
  return (uVar1 & 0xff) != 1;
}

s32 fightTrainerAiWazaHit193(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiKaragenki(void*, u32);
    if (fightTrainerAiIsFightOutPokemonJoutaiKaragenki(ctx, param1) == 1) {
        goto yes;
    }
    return 0;
yes:
    return 1;
}

s32 fightTrainerAiWazaHit192(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(void*, u32, u16*, u32, u32);
    extern u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(u32, void*, void**, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    u16 wazaIds[8];
    void* pokemon[8];
    u32 result;

    fightTrainerAiGetFightOutPokemonWazaDataIdAry(ctx, param1, wazaIds, 0, 0);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, ctx, pokemon, 0, 1);
    result = fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param1, 0x27);
    result = result != 1;
    return result;
}

s32 fightTrainerAiWazaHit191(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightSeqRegulationCheck(u32 param2, u32 param1, u32 param3);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void* ctx, u32 a, u32 type);
    s32 gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0xFFFF);

    if (fightSeqRegulationCheck(param2, param1, param3) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param1, 0x19) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x19) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit190(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit189(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightTrainerAiGetWazaZokuseiDataId(void* ctx, u32 param2, u32 param1);
    extern u16 fightTrainerAiGetFightOutPokemonNowHp(void* ctx, u32 elem);
    extern u32 fightTrainerAiGetWazaIryoku(void* ctx, u32 param2);
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void* ctx, u32 param3, u32 v1, u32 v3);
    u32 v1 = fightTrainerAiGetWazaZokuseiDataId(ctx, param2, param1);
    u16 a = fightTrainerAiGetFightOutPokemonNowHp(ctx, param1);
    u16 b = fightTrainerAiGetFightOutPokemonNowHp(ctx, param3);
    s32 gate;

    if (b <= a) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, v1, fightTrainerAiGetWazaIryoku(ctx, param2)) == 0x43) {
        gate = 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit188(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit187(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void* ctx, u32 elem, u32 type);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void* ctx, u32 elem, u32 type);
    extern u32 fightTargetGetPtrAsNowFightType(u32 type, u32 elem);
    extern u8 fightSideIsJoutaiDataId(u32 a, u32 b);
    extern u8 fightTrainerAiCheckSawagu(void* ctx, u32 a);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(void* ctx, u32 a);
    extern u8 fightSeqRegulationOverTwoCheck(u32 type, u32 elem);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x48) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0xf) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2, param3), 0x4b) == 1) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightTrainerAiCheckSawagu(ctx, param3) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x26) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(ctx, param3) == 0) {
        return 0;
    }
    if (fightSeqRegulationOverTwoCheck(8, param3) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit186(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit185(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit184(void* ctx,u32 target)

{
    extern u16 fightTrainerAiGetFightOutPokemonUsedItemDataId(void*,u32);
  u16 sVar1;

  sVar1 = fightTrainerAiGetFightOutPokemonUsedItemDataId(ctx,target);
  return sVar1 != 0;
}

u32 fightTrainerAiWazaHit183(void) { return 1; }

s32 fightTrainerAiWazaHit182(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

int fightTrainerAiWazaHit181(u32 r3, u32 r4)
{

    extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(u32,u32,u32);
  u32 uVar1;
  uVar1 = fightTrainerAiIsFightOutPokemonJoutaiDataId(r3, r4, 0x25);
  return (uVar1 & 0xFF) != 1;
}

u32 fightTrainerAiWazaHit180(u32 r3, u32 r4)
{
    extern u32 fightSeqGetTemotiPokemonNekonoteWazaDataAry(u32,void*,u32,u32);
    u8 auStack_38[0x38];

    u32 uVar1 = fightSeqGetTemotiPokemonNekonoteWazaDataAry(r3, auStack_38, 0x18, r4);
    return (-uVar1 & ~uVar1) >> 0x1f;
}

int fightTrainerAiWazaHit179(u32 r3, u32 r4)
{

    extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(u32,u32,u32);
  u32 uVar1;
  uVar1 = fightTrainerAiIsFightOutPokemonJoutaiDataId(r3, r4, 0x35);
  return (uVar1 & 0xFF) != 1;
}

u32 fightTrainerAiWazaHit178(void* ctx, u32 slot, u32 param, u32 extra) {
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    s32 gate;

    gate = _fightTrainerAiWazaHitCheck(ctx, slot, param, extra, 0xFFFF);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, extra, 0x19) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit177(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightTrainerAiGetFightOutPokemonSoubiItemDataId(void* ctx, u32 elem);
    extern u8 fightSeqIsDoItemGetWaza(u32 elem);
    extern u8 itemDataCheckValid(u16 elem);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void* ctx, u32 a, u32 type);
    u16 A = fightTrainerAiGetFightOutPokemonSoubiItemDataId(ctx, param1);
    u16 B = fightTrainerAiGetFightOutPokemonSoubiItemDataId(ctx, param3);

    if (fightSeqIsDoItemGetWaza(param1) == 0) {
        return 0;
    }
    if (A == 0 && B == 0) {
        goto ret0;
    }
    if (A == 0xaf) {
        goto ret0;
    }
    if (B == 0xaf) {
        goto ret0;
    }
    if (A != 0 && itemDataCheckValid(A) == 0) {
        goto ret0;
    }
    if (B != 0 && itemDataCheckValid(B) == 0) {
    ret0:
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x3c) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit176(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u16 fightFloor_GetFightSideFightOutPokemonSideMax(u32);
    extern u8 fightOutPokemonCheckFightOut(void*);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    void* target = fightTargetGetPtrAsNowFightType(0xe, param1);

    if (!target) {
        return 0;
    }
    if (fightFloor_GetFightSideFightOutPokemonSideMax(0) < 2 || fightOutPokemonCheckFightOut(target) != 1 || fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param1, 0x32) || fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, (u32)target, 0x32)) {
        return 0;
    }
    return 1;
}

u32 fightTrainerAiWazaHit175(void* ctx, u32 slot, u32 param, u32 param3) {
    extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    u32 result;

    result = _fightTrainerAiWazaHitCheck(ctx, slot, param, param3, 0);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x30) & 0xff) == 1) {
        return 0;
    }
    if ((s32)result == 0) {
        return 0;
    }
    if ((s32)result == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit174(void) { return 1; }

s32 fightTrainerAiWazaHit173(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightFloor_GetTikeiDataId(u32);
    extern u32 tikeiDataBiosGetWazaId(u8);
    extern u32 wazaDB_GetSeqId(u32);
    extern s32 fightTrainerAiWazaDoWazaHitFunc(void*, u32, u32, u32);
    u16 paramType;
    u16 otherType;
    u32 other;
    other = tikeiDataBiosGetWazaId(fightFloor_GetTikeiDataId(0));
    paramType = wazaDB_GetSeqId(param2);
    param2 = other;
    otherType = wazaDB_GetSeqId(param2);
    if (otherType != paramType) {
        return fightTrainerAiWazaDoWazaHitFunc(ctx, param1, param2, param3);
    }
    return 1;
}

u32 fightTrainerAiWazaHit172(void) { return 1; }

s32 fightTrainerAiWazaHit171(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit170(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit169(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit168(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(void* ctx, u32 elem);
    extern u8 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(void* ctx, u32 elem);
    extern u8 fightTrainerAiCheckGuard(void* ctx, u32 param3, u32 param2);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void* ctx, u32 param3, u32 flag);
    u8 q1 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(ctx, param3);
    u8 q2 = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(ctx, param3);

    if (fightTrainerAiCheckGuard(ctx, param3, param2) == 1) {
        return 0;
    }
    if (q1 == 0 && q2 == 0) {
        return 0;
    }
    if (fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0xa0, 1, 1) == 0 &&
        fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0xa0, 4, 1) == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit167(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(void*, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 6) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(ctx, param3, 0xa) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x29) == 1) {
        return 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 6)) {
        return 0;
    }
    if (!fightTrainerAiIsFightOutPokemonJoutaiNormal(ctx, param3)) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2, param3), 0x4b) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit166(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(void*, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    void* side = fightTargetGetPtrAsNowFightType(2, param3);
    u8 abi = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(ctx, param3);
    s32 gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 9) == 1 && abi >= 0xc) {
        if (!fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 4, 1)) {
            return 0;
        }
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 9)) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(side, 0x4b) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit165(void* ctx, u32 slot, u32 param, u32 param3) {
    extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    u32 result;

    result = _fightTrainerAiWazaHitCheck(ctx, slot, param, param3, 0);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x1b) & 0xff) == 1) {
        return 0;
    }
    if ((s32)result == 0) {
        return 0;
    }
    if ((s32)result == -1) {
        return 1;
    }
    return 1;
}

int fightTrainerAiWazaHit164(u32 r3)

{

    extern u32 fightTrainerAiGetFightFloorNowTenkouDataId(u32,u32,u32);
  u32 uVar1;

  uVar1 = fightTrainerAiGetFightFloorNowTenkouDataId(r3,0,1);
  return (uVar1 & 0xff) != 4;
}

u32 fightTrainerAiWazaHit162(void* ctx, u32 slot, u32 param) {

    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonNokoriHp(void*, u32, s32, f32);

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, slot, 0x2d) == 0) {
        return 0;
    }
    return fightTrainerAiIsFightOutPokemonNokoriHp(ctx, slot, 0, 1.0f) != 1;
}

s32 fightTrainerAiWazaHit161(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightTrainerAiGetWazaZokuseiDataId(void* ctx, u32 param2, u32 param1);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void* ctx, u32 param1, u32 flag);
    extern u32 fightTrainerAiGetWazaIryoku(void* ctx, u32 param2);
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void* ctx, u32 param3, u32 v1, u32 v3);
    s32 gate;
    u32 v1 = fightTrainerAiGetWazaZokuseiDataId(ctx, param2, param1);
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param1, 0x2d) == 0) {
        gate = 0;
    }
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, v1, fightTrainerAiGetWazaIryoku(ctx, param2)) == 0x43) {
        gate = 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit160(void* ctx, u32 slot, u32 param) {
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void* ctx, u32 slot, u32 param);
    extern u32 fightOutPokemonGetCountAsJoutaiDataId(u32 slot, u32 param);
    extern u8 joutaiDataBiosGetMaxCount(u32 param);
    u32 result;

    result = slot;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, slot, 0x2d) == 0) {
        result = 0;
    } else {
        result = fightOutPokemonGetCountAsJoutaiDataId(result, 0x2d);
    }
    if ((s16)result >= (s32)joutaiDataBiosGetMaxCount(0x2d)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit159(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit158(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightOutPokemon_GetFightoutTurnCount(u32);
    extern u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(void*, u32, u32);
    if (fightOutPokemon_GetFightoutTurnCount(param1) == 0) {
        return 0;
    }
    return fightTrainerAiIsFightOutPokemonZokuseiDataId(ctx, param3, 7) != 1;
}

u32 fightTrainerAiWazaHit157(void* ctx, u32 slot, u32 param2, u32 param3) {

    extern u8 fightTrainerAiIsFightOutPokemonNokoriHp(void*, u32, s32, f32);

    return fightTrainerAiIsFightOutPokemonNokoriHp(ctx, slot, 0, 1.0f) != 1;
}

u32 fightTrainerAiWazaHit156(void* ctx, u32 slot, u32 param, u32 arg3) {
    extern u32 fightTrainerAiCheckAbiCnt(void*,u32,u32,u32,u32,u32,u32);
    u32 result = fightTrainerAiCheckAbiCnt(ctx, slot, arg3, param, 0x10, 0x2, 0x41) & 0xFF;
    return (result != 0) ? 1 : 0;
}

s32 fightTrainerAiWazaHit155(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit154(u32 r3, u32 r4, u32 r5, u32 r6)
{
  int iVar1;
  iVar1 = _fightTrainerAiWazaHitCheck((void*)r3, r4, r5, r6, 0);
  if (iVar1 == 0) {
    return 0;
  }
  if (iVar1 == -1) {
    return 1;
  }
  return 1;
}

u32 fightTrainerAiWazaHit153(void) { return 0; }

s32 fightTrainerAiWazaHit152(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit151(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit039(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit150(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit146(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit149(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

int fightTrainerAiWazaHit148(u32 r3, u32 r4, u32 r5, u32 r6)

{
  extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(u32,u32,u32);
  u32 uVar1;

  uVar1 = fightTrainerAiIsFightOutPokemonJoutaiDataId(r3,r6,0x34);
  return (uVar1 & 0xff) != 1;
}

s32 fightTrainerAiWazaHit147(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitJisin(ctx, param1, param2, param3);
}

s32 fightTrainerAiWazaHit146(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit145(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit039(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit144(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit143(void) { return 1; }

u32 fightTrainerAiWazaHit142(void* ctx, u32 slot, u32 param) {

    extern u32 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(void*,u32);
    extern u32 fightTrainerAiIsFightOutPokemonNokoriHp(void*, u32, s32, f32);

    if ((fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(ctx,slot) & 0xFF) >= 0xC) {
        goto ret0;
    }
    if ((fightTrainerAiIsFightOutPokemonNokoriHp(ctx, slot, -1, 0.5f) & 0xFF) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

s32 fightTrainerAiWazaHit140(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit139(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit138(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

int fightTrainerAiWazaHit137(u32 r3)

{

    extern u32 fightTrainerAiGetFightFloorNowTenkouDataId(u32,u32,u32);
  u32 uVar1;

  uVar1 = fightTrainerAiGetFightFloorNowTenkouDataId(r3,0,1);
  return (uVar1 & 0xff) != 1;
}

int fightTrainerAiWazaHit136(u32 r3)

{

    extern u32 fightTrainerAiGetFightFloorNowTenkouDataId(u32,u32,u32);
  u32 uVar1;

  uVar1 = fightTrainerAiGetFightFloorNowTenkouDataId(r3,0,1);
  return (uVar1 & 0xff) != 2;
}

s32 fightTrainerAiWazaHit135(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightOutPokemonGetPokemonPtr(u32 v);
    extern void pokemonGetMezamerupower(u32, void*, void*);
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void* ctx, u32 param3, u32 v1, s16 v3);
    u16 hi;
    u16 lo;
    s32 gate;

    pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(param1), &hi, &lo);
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, lo, (s16)hi) == 0x43) {
        gate = 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit134(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitWeatherKaifuku(ctx, param1);
}

u32 fightTrainerAiWazaHit133(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitWeatherKaifuku(ctx, param1);
}

u32 fightTrainerAiWazaHit132(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitWeatherKaifuku(ctx, param1);
}

s32 _fightTrainerAiWazaHitWeatherKaifuku(void* ctx, u32 slot) {
    extern u8 fightTrainerAiIsFightOutPokemonNokoriHp(void*, u32, s32, f32);
    return fightTrainerAiIsFightOutPokemonNokoriHp(ctx, slot, 0, 1.0f) != 1;
}

s32 fightTrainerAiWazaHit130(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit129(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit128(void* ctx, u32 a, u32 b, u32 c) {
    extern s32 fightTrainerAiGetWazaZokuseiDataId(void*,u32,u32);
    extern s32 fightTrainerAiGetWazaIryoku(void*,u32);
    extern s32 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void*,u32,u32,u32);
    s32 res1;

    res1 = fightTrainerAiGetWazaZokuseiDataId(ctx, b, a);
    return !((u16)fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, c, res1, fightTrainerAiGetWazaIryoku(ctx, b)) == 0x43);
}

u32 fightTrainerAiWazaHit127(u32 r3)
{
    extern int fightTrainerSearchIrekaeFightPokemon(u32,void*);

  int iVar1;
  u16 local_8[4];

  local_8[0] = 0;
  iVar1 = fightTrainerSearchIrekaeFightPokemon(r3, local_8);
  return (-iVar1 != 0) ? 1 : 0;
}

s32 fightTrainerAiWazaHit126(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitJisin(ctx, param1, param2, param3);
}

s32 _fightTrainerAiWazaHitJisin(void* ctx, u32 param1, u32 param2, u32 param3) {
    return fightTrainerAiWazaHit000(ctx, param1, param2, param3);
}

s32 fightTrainerAiWazaHit125(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit124(void* ctx,u32 slot)

{
    extern u32 fightTargetGetPtrAsNowFightType(u32,u32);
    extern u32 fightSideCheckWriteJoutaiDataId(u32,u32);
  u32 uVar1;
  u32 uVar2;

  uVar1 = fightTargetGetPtrAsNowFightType(2,slot);
  uVar2 = fightSideCheckWriteJoutaiDataId(uVar1,0x4b);
  uVar2 = __cntlzw(2 - (uVar2 & 0xff));
  return uVar2 >> 5;
}

s32 fightTrainerAiWazaHit123(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit121(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit122(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit121(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit120(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightOutPokemonGetSex(u32);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiKie(void*, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    u8 attackerSex = fightOutPokemonGetSex(param1);
    u8 defenderSex = fightOutPokemonGetSex(param3);
    s32 gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0xc) == 1) {
        gate = 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 0xa)) {
        return 0;
    }
    if (attackerSex == defenderSex || fightTrainerAiIsFightOutPokemonJoutaiKie(ctx, param3) == 1 || fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0xa) == 1 || attackerSex == 2 || defenderSex == 2) {
        gate = 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit119(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit118(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(void*, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    void* side = fightTargetGetPtrAsNowFightType(2, param3);
    u8 abi = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(ctx, param3);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 9) == 1 && abi >= 0xc) {
        if (!fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x20, 1, 1)) {
            return 0;
        }
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 9)) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(side, 0x4b) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit117(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit116(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit111(ctx,param1,param2,param3);
}

int fightTrainerAiWazaHit115(u32 r3)

{

    extern u32 fightTrainerAiGetFightFloorNowTenkouDataId(u32,u32,u32);
  u32 uVar1;

  uVar1 = fightTrainerAiGetFightFloorNowTenkouDataId(r3,0,1);
  return (uVar1 & 0xff) != 3;
}

u32 fightTrainerAiWazaHit114(void* ctx, u32 slot, u32 param, u32 arg3) {
    extern u32 fightSeqRegulationCheck(u32,u32,u32);
    extern u32 fightTrainerAiCheckHorobinouta(void*);

    if ((u8)fightSeqRegulationCheck(param, slot, arg3) == 1) {
        return 0;
    }
    return (u16)fightTrainerAiCheckHorobinouta(ctx) != 0;
}

u32 fightTrainerAiWazaHit113(u32 r3, u32 r4, u32 r5, u32 r6)
{
  int iVar1;
  iVar1 = _fightTrainerAiWazaHitCheck((void*)r3, r4, r5, r6, 0);
  if (iVar1 == 0) {
    return 0;
  }
  if (iVar1 == -1) {
    return 1;
  }
  return 1;
}

u32 fightTrainerAiWazaHit112(void* ctx, u32 slot, u32 param) {
    extern u8 joutaiDataBiosGetMaxCount(u32);
    extern u32 fightTargetGetPtrAsNowFightType(u32,u32);
    extern u32 fightSideGetCountAsJoutaiDataId(u32, u32);
    extern u8 fightSideIsJoutaiDataId(u32, u32);
    u32 target;
    u32 count;

    target = fightTargetGetPtrAsNowFightType(3,slot);
    count = 0;
    if (fightSideIsJoutaiDataId(target, 0x4a) == 1) {
        count = fightSideGetCountAsJoutaiDataId(target, 0x4a);
    }
    if ((s16)count >= (s32)joutaiDataBiosGetMaxCount(0x4a)) {
        return 0;
    }
    return 1;
}

u32 fightTrainerAiWazaHit111(void* ctx,u32 param1,u32 param2,u32 param3) { return 1; }

s32 fightTrainerAiWazaHit109(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(void* ctx, u32 elem);
    extern u8 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(void* ctx, u32 elem);
    extern u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(void* ctx, u32 elem);
    extern u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(void* ctx, u32 a, u32 type);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void* ctx, u32 a, u32 type);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiKie(void* ctx, u32 elem);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    u8 a = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(ctx, param3);
    u8 b = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(ctx, param3);
    u8 c = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(ctx, param3);

    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(ctx, param1, 7) == 1) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
            return 0;
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x18) != 1) {
            if (fightTrainerAiIsFightOutPokemonJoutaiKie(ctx, param3) != 1) {
                goto ret1;
            }
        }
        return 0;
    }

    if (((c == 0) && (a >= 0xc)) && (b >= 0xc)) {
        return 0;
    }
    if (fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x90, 3, 0x41) != 0) {
        goto ret1;
    }
    if (fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 1, 0x41) != 0) {
        goto ret1;
    }
    if (fightTrainerAiCheckAbiCnt(ctx, param1, param3, param2, 0x10, 2, 0x41) != 0) {
        goto ret1;
    }
ret0:
    return 0, 0;

    return 0;
ret1:
    return 1;
}

s32 fightTrainerAiWazaHit108(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x10, 7, 0x41);
}

u32 fightTrainerAiWazaHit107(void* ctx, u32 param1, u32 param2, u32 extra) {
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, extra, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, extra, 0x17) == 1) {
        return 0;
    }
    return fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, extra, 8) != 0;
}

u32 fightTrainerAiWazaHit106(void* ctx, u32 slot, u32 param, u32 extra) {
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    s32 gate;

    gate = _fightTrainerAiWazaHitCheck(ctx, slot, param, extra, 0xFFFE);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, extra, 0x16) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit105(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit104(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit103(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit102(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightFloorGetFightTrainerFightPokemonPtrAry(u32 zero, void* ctx, void* buf, u32 one1, u32 one2);
    extern u8 fightTrainerAiIsFightPokemonTokuseiDataId(void* ctx, u32 elem, u32 type);
    extern u8 fightTrainerAiIsFightPokemonJoutaiNormal(void* ctx, u32 elem);
    u32 buf[0x17];
    u32 count = fightFloorGetFightTrainerFightPokemonPtrAry(0, ctx, buf, 1, 1);
    u32 *bufPtr;
    u16 i;
    u8 flag;

    bufPtr = buf;
    flag = 0;
    for (i = 0; i < (u16)count; i++) {
        if (bufPtr[i] == 0) {
            continue;
        }
        if ((u16)param2 == 0xd7 && fightTrainerAiIsFightPokemonTokuseiDataId(ctx, bufPtr[i], 0x2b) == 1) {
            continue;
        }
        if (fightTrainerAiIsFightPokemonJoutaiNormal(ctx, bufPtr[i]) != 0) {
            continue;
        }
        flag = 1;
        break;
    }
    if (flag == 0) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit101(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit100(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(void*, u32, u16*, s16*, u32);
    extern u32 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(void*, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiKie(void*, u32);
    extern u8 fightTrainerAiGetFightOutPokemonWazaNowPp(void*, u32, u8);
    u16 arrayA[8];
    s16 arrayB[8];
    s32 gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0xFFFF);
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(ctx, param3, arrayA, arrayB, 0);
    u32 last = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(ctx, param3);
    u8 flag;
    u8 i;

    if ((u16)last == 0 || (u16)last == 0x176 || (u16)last == 0xffff || fightTrainerAiIsFightOutPokemonJoutaiKie(ctx, param3) == 1) {
        return 0;
    }
    flag = 0;
    for (i = 0; i < count; i++) {
        if (arrayB[i] < 0) {
            continue;
        }
        if ((u16)last != arrayA[i]) {
            continue;
        }
        flag = fightTrainerAiGetFightOutPokemonWazaNowPp(ctx, param3, (u8)arrayB[i]);
        break;
    }
    if (flag == 0) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit099(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

int fightTrainerAiWazaHit098(u32 arg0, u32 arg1, u32 arg2, u32 arg3)
{
    extern u32 fightSeqRegulationCheck(u32,u32,u32);

    return (u8)fightSeqRegulationCheck(arg2, arg1, arg3) != 1;
}

s32 fightTrainerAiWazaHit097(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(void*, u32, u16*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightSeqRendouWazaCheck(u32);
    extern u8 fightSeqTameWazaCheck(u32);
    u16 buf[8];
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(ctx, param1, buf, 0, 1);
    u16 i;

    if (!fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param1, 8)) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        u32 elem = buf[i];
        if (elem == 0x176 || elem == 0x163) {
            continue;
        }
        if (fightSeqRendouWazaCheck(elem) != 0) {
            continue;
        }
        if (elem == 0x108 || elem == 0xfd) {
            continue;
        }
        if (fightSeqTameWazaCheck(elem) == 0) {
            break;
        }
    }
    if (i >= count) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit095(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(void*, u32, u16*, u32, u32);
    extern u32 fightTrainerAiGetFightOutPokemonSketchWazaDataId(void*, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightSeqIsSketchNgWazaDataId(u32);
    u16 buf[8];
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(ctx, param1, buf, 0, 0);
    u32 sketch = fightTrainerAiGetFightOutPokemonSketchWazaDataId(ctx, param3);
    u16 i;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param1, 0x10) == 1 || fightSeqIsSketchNgWazaDataId(sketch) == 1) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        if ((u16)sketch == buf[i]) {
            return 0;
        }
    }
    return 1;
}

u32 fightTrainerAiWazaHit094(void* ctx, u32 slot, u32 param, u32 extra) {
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    s32 gate;

    gate = _fightTrainerAiWazaHitCheck(ctx, slot, param, extra, 0xFFFF);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, extra, 0x14) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit093(void) { return 1; }

s32 fightTrainerAiWazaHit092(void* ctx, u32 param1, u32 param2, u32 param3) {
    u32 *new_var;
    extern u32 fightTrainerAiGetWazaZokuseiDataId(void* ctx, u32 param2, u32 param1);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void* ctx, u32 param1, u32 flag);
    extern u32 fightTrainerAiGetWazaIryoku(void* ctx, u32 param2);
    s32 gate;
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void* ctx, u32 param3, u32 v1, u32 v3);
    u32 v1 = fightTrainerAiGetWazaZokuseiDataId(ctx, param2, param1);

    if (!fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param1, 0x8)) {
        return 0;
    }
    new_var = &v1;
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, *new_var, fightTrainerAiGetWazaIryoku(ctx, param2)) == 0x43) {
        gate = 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (((0, gate)) == (-1)) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit091(void* ctx, u32 slot, u32 param, u32 extra) {
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    s32 gate;

    gate = _fightTrainerAiWazaHitCheck(ctx, slot, param, extra, 0xFFFF);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, extra, 0x14) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit090(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(void*, u32, u16*, s16*, u32);
    extern u32 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(void*, u32);
    extern u8 fightSeqIsEncoreNgWazaDataId(u32);
    extern u8 fightTrainerAiGetFightOutPokemonWazaNowPp(void*, u32, u8);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    u16 arrayA[8];
    s16 arrayB[8];
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(ctx, param3, arrayA, arrayB, 0);
    u32 last = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(ctx, param3);
    s32 gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    u8 flag;
    u16 i;

    if (fightSeqIsEncoreNgWazaDataId(last) == 1) {
        return 0;
    }
    flag = 0;
    for (i = 0; i < count; i++) {
        if (arrayB[i] < 0) {
            continue;
        }
        if ((u16)last != arrayA[i]) {
            continue;
        }
        flag = fightTrainerAiGetFightOutPokemonWazaNowPp(ctx, param3, (u8)arrayB[i]);
        break;
    }
    if (flag == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x2a) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit089(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit088(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit087(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit086(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(void*, u32, u16*, s16*, u32);
    extern u32 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(void*, u32);
    extern u8 fightTrainerAiGetFightOutPokemonWazaNowPp(void*, u32, u8);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    u16 arrayA[8];
    s16 arrayB[8];
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(ctx, param3, arrayA, arrayB, 0);
    u32 last = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(ctx, param3);
    s32 gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    u8 flag = 0;
    u16 i;

    for (i = 0; i < count; i++) {
        if (arrayB[i] < 0) {
            continue;
        }
        if ((u16)last != arrayA[i]) {
            continue;
        }
        flag = fightTrainerAiGetFightOutPokemonWazaNowPp(ctx, param3, (u8)arrayB[i]);
        break;
    }
    if (flag == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x29) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit085(void) { return 1; }

s32 fightTrainerAiWazaHit084(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void* ctx, u32 a, u32 type);
    extern u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(void* ctx, u32 a, u32 type);
    s32 gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x1c) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(ctx, param3, 0xc) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit083(void) { return 1; }

s32 fightTrainerAiWazaHit082(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(void*, u32, u16*, u32, u32);
    extern u32 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(void*, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightSeqMonomaneNGCheck(u32);
    u16 buf[8];
    u16 count = fightTrainerAiGetFightOutPokemonWazaDataIdAry(ctx, param1, buf, 0, 0);
    u32 last = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(ctx, param3);
    s32 gate;
    u16 i;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0xFFFF);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param1, 0x10) == 1 || fightSeqMonomaneNGCheck(last) != 0 || (u16)last == 0 || (u16)last == 0xffff || (u16)last == 0x176 || (u16)last == 0x163) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        if ((u16)last == buf[i]) {
            return 0;
        }
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit081(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit080(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit079(void* ctx, u32 slot, u32 param) {
    extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u32 fightTrainerAiIsFightOutPokemonNokoriHp(void*, u32, s32, f32);

    u32 result;

    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, slot, 0x14) & 0xff) == 1) {
        return 0;
    }

    result = fightTrainerAiIsFightOutPokemonNokoriHp(ctx, slot, -1, 0.25f) & 0xff;
    return result != 1;
}

s32 fightTrainerAiWazaHit078(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit077(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit029(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit076(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit075(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit039(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit073(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit072(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit071(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit070(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit069(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit068(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit067(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u32 fightTrainerAiGetWazaZokuseiDataId(void*, u32, u32);
    extern u32 fightTrainerAiGetWazaIryoku(void*, u32);
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void*, u32, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(void*, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    void* side = fightTargetGetPtrAsNowFightType(2, param3);
    u32 zokusei = fightTrainerAiGetWazaZokuseiDataId(ctx, param2, param1);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 7) == 1) {
        return 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 5)) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, zokusei, fightTrainerAiGetWazaIryoku(ctx, param2)) == 0x43) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 5) == 1) {
        return 0;
    }
    if (!fightTrainerAiIsFightOutPokemonJoutaiNormal(ctx, param3)) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightSideIsJoutaiDataId(side, 0x4b) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit066(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(void*, u32);
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x11) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 3) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 4) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(ctx, param3, 3) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(ctx, param3, 8) == 1) {
        return 0;
    }
    if (!fightTrainerAiIsFightOutPokemonJoutaiNormal(ctx, param3)) {
        return 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 4)) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2, param3), 0x4b) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit065(void* ctx,u32 slot)

{
    extern u32 fightTargetGetPtrAsNowFightType(u32,u32);
    extern u32 fightSideCheckWriteJoutaiDataId(u32,u32);
  u32 uVar1;
  u32 uVar2;

  uVar1 = fightTargetGetPtrAsNowFightType(2,slot);
  uVar2 = fightSideCheckWriteJoutaiDataId(uVar1,0x48);
  uVar2 = __cntlzw(2 - (uVar2 & 0xff));
  return uVar2 >> 5;
}

s32 fightTrainerAiWazaHit062(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0xa0, 5, 1);
}

s32 fightTrainerAiWazaHit060(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0xa0, 3, 1);
}

s32 fightTrainerAiWazaHit059(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0xa0, 2, 1);
}

s32 fightTrainerAiWazaHit058(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0xa0, 1, 1);
}

int fightTrainerAiWazaHit057(void* ctx, u32 slot, u32 param, u32 arg3) {
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiKie(void*, u32);

    if ((u8)fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, arg3, 0x10) == 1) {
        goto fail;
    }
    if ((u8)fightTrainerAiIsFightOutPokemonJoutaiKie(ctx, arg3) != 1) {
        goto success;
    }
fail:
    return 0;
success:
    return 1;
}

s32 fightTrainerAiWazaHit054(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x20, 5, 0x41);
}

s32 fightTrainerAiWazaHit053(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x20, 4, 0x41);
}

s32 fightTrainerAiWazaHit052(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x20, 3, 0x41);
}

s32 fightTrainerAiWazaHit051(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x20, 2, 0x41);
}

s32 fightTrainerAiWazaHit050(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x20, 1, 0x41);
}

s32 fightTrainerAiWazaHit049(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    void* side = fightTargetGetPtrAsNowFightType(2, param3);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 9) == 1) {
        return 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 9)) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightSideIsJoutaiDataId(side, 0x4b) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit048(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

int fightTrainerAiWazaHit047(u32 r3, u32 r4)
{

    extern u32 fightTrainerAiIsFightOutPokemonJoutaiDataId(u32,u32,u32);
  return (fightTrainerAiIsFightOutPokemonJoutaiDataId(r3, r4, 0xf) & 0xFF) != 1;
}

u32 fightTrainerAiWazaHit046(void* ctx,u32 slot)

{
    extern u32 fightTargetGetPtrAsNowFightType(u32,u32);
    extern u32 fightSideCheckWriteJoutaiDataId(u32,u32);
  u32 uVar1;
  u32 uVar2;

  uVar1 = fightTargetGetPtrAsNowFightType(2,slot);
  uVar2 = fightSideCheckWriteJoutaiDataId(uVar1,0x4c);
  uVar2 = __cntlzw(2 - (uVar2 & 0xff));
  return uVar2 >> 5;
}

s32 fightTrainerAiWazaHit045(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit044(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit029(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit043(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit042(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit041(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit040(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit039(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit038(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiGetFightOutPokemonLevel(void* ctx, u32 elem);
    extern u32 fightTrainerAiGetWazaZokuseiDataId(void* ctx, u32 param2, u32 param1);
    extern u32 fightTrainerAiGetWazaIryoku(void* ctx, u32 param2);
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void* ctx, u32 param3, u32 v1, u32 v3);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void* ctx, u32 a, u32 type);
    s32 gate;
    u8 a = fightTrainerAiGetFightOutPokemonLevel(ctx, param1);
    u8 b = fightTrainerAiGetFightOutPokemonLevel(ctx, param3);
    u32 v1 = fightTrainerAiGetWazaZokuseiDataId(ctx, param2, param1);
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0xFFFF);

    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, v1, fightTrainerAiGetWazaIryoku(ctx, param2)) == 0x43) {
        gate = 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 5) == 1) {
        gate = 0;
    }
    if (a < b) {
        gate = 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit037(void* ctx, u32 param1, u32 param2) {

    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonNokoriHp(void*, u32, s32, f32);
    extern u8 fightTrainerAiCheckSawagu(void*, u32);

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param1, 8) == 1) {
        return 0;
    }
    if (fightTrainerAiCheckSawagu(ctx, param1) == 1) {
        return 0;
    }
    return fightTrainerAiIsFightOutPokemonNokoriHp(ctx, param1, 0, 1.0f) != 1;
}

s32 fightTrainerAiWazaHit036(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit035(void* ctx,u32 slot)

{
    extern u32 fightTargetGetPtrAsNowFightType(u32,u32);
    extern u32 fightSideCheckWriteJoutaiDataId(u32,u32);
  u32 uVar1;
  u32 uVar2;

  uVar1 = fightTargetGetPtrAsNowFightType(2,slot);
  uVar2 = fightSideCheckWriteJoutaiDataId(uVar1,0x49);
  uVar2 = __cntlzw(2 - (uVar2 & 0xff));
  return uVar2 >> 5;
}

s32 fightTrainerAiWazaHit034(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit033(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(void*, u32);
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x11) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 3) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 4) == 1) {
        return 0;
    }
    if (!fightTrainerAiIsFightOutPokemonJoutaiNormal(ctx, param3)) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(ctx, param3, 3) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(ctx, param3, 8) == 1) {
        return 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 4)) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2, param3), 0x4b) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHit032(void* ctx, u32 slot, u32 param2, u32 param3) {

    extern u8 fightTrainerAiIsFightOutPokemonNokoriHp(void*, u32, s32, f32);

    return fightTrainerAiIsFightOutPokemonNokoriHp(ctx, slot, 0, 1.0f) != 1;
}

s32 fightTrainerAiWazaHit031(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit030(void* ctx,void* target)

{
    extern int fightTrainerAiCheckTextureZokusei(void*,void*);
  u8 cVar1;

  cVar1 = fightTrainerAiCheckTextureZokusei(ctx,target);
  return cVar1 != 0;
}

s32 fightTrainerAiWazaHit029(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit028(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightFloorGetFightOutPokemonPtrToFightTrainerPtr(u32 zero, u32 param3);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void* ctx, u32 a, u32 type);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void* ctx, u32 a, u32 type);
    extern u16 fightTrainerGetIrekaeFightPokemonAry(u32 v, void* buf);
    u8 buf[0x14];
    u32 prev = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, param3);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, param3, 0x15) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x25) == 1) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightTrainerGetIrekaeFightPokemonAry(prev, buf) == 0) {
        gate = 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit027(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit026(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit039(ctx,param1,param2,param3);
}

u32 fightTrainerAiWazaHit025(void) { return 1; }

s32 fightTrainerAiWazaHit024(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x90, 7, 1);
}

s32 fightTrainerAiWazaHit023(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x90, 6, 1);
}

s32 fightTrainerAiWazaHit020(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x90, 3, 1);
}

s32 fightTrainerAiWazaHit019(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x90, 2, 1);
}

s32 fightTrainerAiWazaHit018(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x90, 1, 1);
}

s32 fightTrainerAiWazaHit017(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit016(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x10, 7, 0x41);
}

s32 fightTrainerAiWazaHit013(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x10, 4, 0x41);
}

s32 fightTrainerAiWazaHit011(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x10, 2, 0x41);
}

s32 fightTrainerAiWazaHit010(void* ctx, u32 param1, u32 param2, u32 param3) {
    return _fightTrainerAiWazaHitAbicnt(ctx, param1, param3, param2, 0x10, 1, 0x41);
}

s32 _fightTrainerAiWazaHitAbicnt(void* ctx, u32 attacker, u32 defender, u32 waza, u32 kind, u32 index, u32 flag) {
    extern s8 fightSeqCondChgActParaIdToValue(u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);
    extern u8 fightTrainerAiCheckAbiCnt(void*, u32, u32, u32, u32, u32, u32);
    s32 gate;

    if (fightSeqCondChgActParaIdToValue(kind) < 0) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, defender, 0x14) == 1) {
            return 0;
        }
        gate = _fightTrainerAiWazaHitCheck(ctx, attacker, waza, defender, 0);
    }
    if (!fightTrainerAiCheckAbiCnt(ctx, attacker, defender, waza, kind, index, flag)) {
        return 0;
    }
    if (fightSeqCondChgActParaIdToValue(kind) < 0) {
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, defender, 0x1d) == 1) {
            return 0;
        }
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, defender, 0x49) == 1) {
            return 0;
        }
        if (gate == 0) {
            return 0;
        }
        if (gate == -1) {
            return 1;
        }
    }
    return 1;
}

u32 fightTrainerAiWazaHit009(void* ctx,void* target)

{
    extern u16 fightTrainerAiCheckOumu(void*,void*);
  u16 sVar1;

  sVar1 = fightTrainerAiCheckOumu(ctx,target);
  return sVar1 != 0;
}

s32 fightTrainerAiWazaHit008(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightTrainerAiGetWazaZokuseiDataId(void* ctx, u32 param2, u32 param1);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void* ctx, u32 param3, u32 flag);
    extern u32 fightTrainerAiGetWazaIryoku(void* ctx, u32 param2);
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void* ctx, u32 param3, u32 v1, u32 v3);
    u32 v1 = fightTrainerAiGetWazaZokuseiDataId(ctx, param2, param1);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (!fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x8)) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, v1, fightTrainerAiGetWazaIryoku(ctx, param2)) == 0x43) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit007(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightTrainerAiGetWazaZokuseiDataId(void* ctx, u32 param2, u32 param1);
    extern u32 fightFloorGetFightTrainerFightPokemonPtrAry(u32 zero, void* ctx, void* buf, u32 one1, u32 one2);
    extern u8 fightSeqRegulationZenmetuCheck(u32 param2);
    extern u8 fightTrainerAiCheckSimerike(void* ctx);
    extern u32 fightTrainerAiGetWazaIryoku(void* ctx, u32 param2);
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void* ctx, u32 param3, u32 v1, u32 v3);
    u8 buf[0x60];
    u32 v1 = fightTrainerAiGetWazaZokuseiDataId(ctx, param2, param1);
    u32 flinchCount = fightFloorGetFightTrainerFightPokemonPtrAry(0, ctx, buf, 1, 1);
    s32 gate;

    if (fightSeqRegulationZenmetuCheck(param2) == 1 && (u16)flinchCount <= 1) {
        return 0;
    }
    if (fightTrainerAiCheckSimerike(ctx) == 1) {
        return 0;
    }
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, v1, fightTrainerAiGetWazaIryoku(ctx, param2)) == 0x43) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit006(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit005(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit004(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit003(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit002(void* ctx,u32 param1,u32 param2,u32 param3) {
    return fightTrainerAiWazaHit000(ctx,param1,param2,param3);
}

s32 fightTrainerAiWazaHit001(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u8 fightTrainerAiCheckSawagu(void*, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(void*, u32);
    extern void* fightTargetGetPtrAsNowFightType(u32, u32);
    extern u8 fightSideIsJoutaiDataId(void*, u32);
    s32 gate;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 0x14) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, param3, 8) == 1) {
        return 0;
    }
    if (fightTrainerAiCheckSawagu(ctx, param3) == 1) {
        return 0;
    }
    if (!fightTrainerAiIsFightOutPokemonJoutaiNormal(ctx, param3)) {
        return 0;
    }
    if (!_fightTrainerAiWazaHitCheckTokusei(ctx, param3, 8)) {
        return 0;
    }
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2, param3), 0x4b) == 1) {
        return 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit000(void* ctx, u32 param1, u32 param2, u32 param3) {
    extern u32 fightTrainerAiGetWazaZokuseiDataId(void* ctx, u32 param2, u32 param1);
    extern u32 fightTrainerAiGetWazaIryoku(void* ctx, u32 param2);
    extern u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void* ctx, u32 param3, u32 v1, u32 v3);
    s32 gate;
    u32 v1 = fightTrainerAiGetWazaZokuseiDataId(ctx, param2, param1);
    gate = _fightTrainerAiWazaHitCheck(ctx, param1, param2, param3, 0);

    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(ctx, param3, v1, fightTrainerAiGetWazaIryoku(ctx, param2)) == 0x43) {
        gate = 0;
    }
    if (gate == 0) {
        return 0;
    }
    if (gate == -1) {
        return 1;
    }
    return 1;
}

u32 fightTrainerAiWazaHitNull(void) { return 1; }

u8 _fightTrainerAiWazaHitCheckTokusei(void* ctx, u32 pokemon, u32 zokusei) {
    extern u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*, u32, u32);

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, pokemon, 0x11) == 1) {
        if ((u16)zokusei == 3 || (u16)zokusei == 4) {
            return 0;
        }
    } else if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, pokemon, 0x14) == 1) {
        if ((u16)zokusei == 9) {
            return 0;
        }
    } else if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, pokemon, 0x7) == 1) {
        if ((u16)zokusei == 5) {
            return 0;
        }
    } else if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, pokemon, 0xf) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, pokemon, 0x48) == 1) {
        if ((u16)zokusei == 8) {
            return 0;
        }
    } else if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, pokemon, 0x29) == 1) {
        if ((u16)zokusei == 6) {
            return 0;
        }
    } else if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, pokemon, 0x28) == 1) {
        if ((u16)zokusei == 7) {
            return 0;
        }
    } else if (fightTrainerAiIsFightOutPokemonTokuseiDataId(ctx, pokemon, 0xc) == 1) {
        if ((u16)zokusei == 0xa) {
            return 0;
        }
    }
    return 1;
}

s32 _fightTrainerAiWazaHitCheck(void* ctx, u32 attacker, u32 waza, u32 defender, u32 mode) {
    extern u32 fightFloor_GetFightType(u32);
    extern u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(u32, u8);
    extern u8 fightTrainerAiGetFightFloorNowTenkouDataId(void*, u32, u32);
    extern u32 wazaDB_GetSeqId(u32);
    extern u16 fightFloorGetFightOutPokemonPtrAry(u32, u32, u32, u32, u32*);
    extern void fightFloorSortFightOutPokemonPtrArySub(u32, u32*, u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*, u32, u32);
    extern u16 fightOutPokemonGetUserFightTargetIdJoutaiDataId(u32, u32);
    extern u8 fightTrainerAiIsFightOutPokemonJoutaiKie(void*, u32);
    extern u8 fightTrainerAiCheckGuard(void*, u32, u32);
    extern u8 fightSeqRegulationCheck(u32, u32, u32);
    extern u8 fightSeqIsTenkouHit(u32);
    extern u8 fightSeqIsAllwaysHit(u32);
    u32 ptrs[10];
    u32 side;
    u32 seqId;
    u16 count;
    u16 i;
    u16 attackerIndex;
    u16 defenderIndex;
    u32 attackerFirst;

    side = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(attacker, fightFloor_GetFightType(0));
    fightTrainerAiGetFightFloorNowTenkouDataId(ctx, 0, 1);
    seqId = wazaDB_GetSeqId(waza);
    if (defender == 0) {
        return 1;
    }
    count = fightFloorGetFightOutPokemonPtrAry(0, 1, 0, 0, ptrs);
    fightFloorSortFightOutPokemonPtrArySub(0, ptrs, 8, 0);
    attackerIndex = 0;
    defenderIndex = 0;
    for (i = 0; i < count; i++) {
        if (ptrs[i] != 0) {
            if (attacker == ptrs[i]) {
                attackerIndex = i;
            }
            if (defender == ptrs[i]) {
                defenderIndex = i;
            }
        }
    }
    attackerFirst = attackerIndex < defenderIndex;
    if (mode == 0xFFFF || mode == 0xFFFE) {
        if (mode == 0xFFFF) {
            if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, defender, 0x1d) == 1) {
                if ((u16)side == (u16)fightOutPokemonGetUserFightTargetIdJoutaiDataId(defender, 0x1d)) {
                    return -1;
                }
            }
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiKie(ctx, attacker) == 1 && attackerFirst == 1) {
            return 0;
        }
        if (fightTrainerAiCheckGuard(ctx, defender, waza) == 1) {
            return 0;
        }
        return 1;
    }
    if (fightSeqRegulationCheck(waza, attacker, defender) == 1) {
        return 0;
    }
    if (fightTrainerAiCheckGuard(ctx, defender, waza) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, defender, 0x1d) == 1) {
        u16 target = fightOutPokemonGetUserFightTargetIdJoutaiDataId(defender, 0x1d);
        if (target == (u16)side) {
            return -1;
        }
    }
    if (attackerFirst == 1) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, defender, 0x1f) == 1) {
            if ((u16)seqId != 0x92 && (u16)seqId != 0x95 && (u16)seqId != 0x98 && (u16)seqId != 0xcf) {
                return 0;
            }
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, defender, 0x20) == 1) {
            if ((u16)seqId != 0x93) {
                return 0;
            }
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(ctx, defender, 0x21) == 1) {
            if ((u16)waza != 0x39 && (u16)waza != 0xfa) {
                return 0;
            }
        }
    }
    if (fightSeqIsTenkouHit(waza) == 1) {
        return -1;
    }
    if (fightSeqIsAllwaysHit(waza) == 1) {
        return -1;
    }
    return 1;
}

