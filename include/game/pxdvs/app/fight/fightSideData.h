#ifndef GAME_FIGHTSIDEDATA_H
#define GAME_FIGHTSIDEDATA_H
#include <dolphin/types.h>
#include <game/fightfloor.h>
#include <game/pxdvs/app/fight/fightJoutaiData.h>

struct FightTrainer;

class FIGHT_TRAINER {
public:
    FIGHT_TRAINER() {}
    FightTrainer* getFightTrainer() { return (FightTrainer*)data; }
    u8 data[FIGHT_TRAINER_SIZE];
};

class FIGHT_SIDE {
public:
    u16 fightSideDataId;
    u8 unk2[2];
    FightJoutai joutai[6];
    FIGHT_TRAINER fightTrainer[2];
    u8 makibisiCheckFlag;
    u8 unk6EED[3];
};

#define FIGHT_SIDE_OFFSET_OF(f) ((u32)&((FIGHT_SIDE*)0)->f)
#define FIGHT_SIDE_CHECK(name, cond) typedef char name[(cond) ? 1 : -1]
FIGHT_SIDE_CHECK(FightSideCheckSize, sizeof(FIGHT_SIDE) == FIGHT_SIDE_SIZE);
FIGHT_SIDE_CHECK(FightSideCheckTrainerSize, sizeof(FIGHT_TRAINER) == FIGHT_TRAINER_SIZE);
#ifndef __MWERKS__
#include <stddef.h>
static_assert(offsetof(FIGHT_SIDE, joutai) == 0x4, "FIGHT_SIDE layout");
static_assert(offsetof(FIGHT_SIDE, fightTrainer) == 0x64, "FIGHT_SIDE layout (trainers at 0x64 on PC too)");
static_assert(offsetof(FIGHT_SIDE, makibisiCheckFlag) == 0x64 + 2 * FIGHT_TRAINER_SIZE, "FIGHT_SIDE layout");
#else
FIGHT_SIDE_CHECK(FightSideCheckJoutai, FIGHT_SIDE_OFFSET_OF(joutai) == 0x4);
FIGHT_SIDE_CHECK(FightSideCheckTrainer, FIGHT_SIDE_OFFSET_OF(fightTrainer) == 0x64);
FIGHT_SIDE_CHECK(FightSideCheckMakibisi, FIGHT_SIDE_OFFSET_OF(makibisiCheckFlag) == 0x6EEC);
#endif

#endif
