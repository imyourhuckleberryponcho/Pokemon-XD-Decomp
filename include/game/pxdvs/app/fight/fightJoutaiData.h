#ifndef GAME_FIGHTJOUTAIDATA_H
#define GAME_FIGHTJOUTAIDATA_H
#include <dolphin/types.h>

struct FightJoutai {
    u16 joutaiDataId;
    u16 userFightTargetId;
    u8 kaisuu;
    u8 nowKaisuu;
    u8 count;
    u8 unk7;
    u32 buff;
    u16 idBuff;
    u8 unkE[2];
};
typedef char FightJoutaiCheckSize[(sizeof(FightJoutai) == 0x10) ? 1 : -1];

#endif
