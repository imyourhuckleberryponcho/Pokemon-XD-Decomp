#ifndef GAME_MENUCBWORK_H
#define GAME_MENUCBWORK_H
#include <dolphin/types.h>
#include <game/menucbsize.h>

#include <game/menuCBRecords.h>

#ifndef MENUCB_TRAINER
#define MENUCB_TRAINER MenuCBTrainer
#endif
#ifndef MENUCB_RULE
#define MENUCB_RULE MenuCBRule
#endif
#ifndef MENUCB_ERR
#define MENUCB_ERR MenuCBErr
#endif
#ifndef MENUCB_DANCER
#define MENUCB_DANCER void
#endif

struct _MENUCBWORK {
    s32 result;
    s32 mode;
    s32 state;
    s32 ruleType;
    s32 selection;
    s32 versus;
    MENUCB_TRAINER trainer[4];
    MENUCB_TRAINER trainerOrg[4];
    MENUCB_RULE rule[6];
    MENUCB_RULE* currentRule;
#ifdef __MWERKS__
    u32 bgmCounter;
#endif
    s32 unk9C80;
    MENUCB_ERR err[4][6];
    u8 heroBackup[0x978];
    u8 hero[0x978];
    s32 col;
    s32 row;
    s32 unkAFDC;
    s32 cursor;
    s32 unkAFE4;
    s32 unkAFE8;
    s32 unkAFEC;
    s32 unkAFF0;
    s32 unkAFF4;
    s32 unkAFF8;
    s32 floorSelect;
    s32 unkB000;
    s32 unkB004;
    s32 unkB008;
    s32 unkB00C;
    s32 unkB010;
    s32 unkB014;
    s32 unkB018;
    s32 unkB01C;
    s32 unkB020;
    s32 unkB024;
    s32 scroll;
    s32 unkB02C;
    s32 unkB030;
    s32 unkB034;
    s32 unkB038;
    s32 unkB03C;
    s32 unkB040;
    s32 unkB044;
    s32 unkB048;
    s32 unkB04C;
    s32 unkB050;
    s32 unkB054;
    s32 unkB058;
    s32 unkB05C;
    s32 unkB060;
    s32 unkB064;
    s32 unkB068;
    s32 unkB06C;
    s32 unkB070;
    s32 unkB074;
    s32 unkB078;
    s32 unkB07C;
    s32 unkB080;
    s32 unkB084;
    s32 unkB088;
    s32 unkB08C;
    s32 unkB090;
    s32 unkB094;
    s32 unkB098;
    s32 unkB09C;
    s32 unkB0A0;
    s32 unkB0A4;
    s32 unkB0A8;
    s32 unkB0AC;
    s32 unkB0B0;
    s32 unkB0B4;
    s32 unkB0B8;
    s32 unkB0BC;
    s32 unkB0C0;
    s32 unkB0C4;
    s32 unkB0C8;
    s32 unkB0CC;
    s32 unkB0D0;
    u32 tempBuff;
    s32 errPlayer;
    s32 unkB0DC;
    s32 controlerId;
    s32 unkB0E4;
    s32 unkB0E8;
    s32 unkB0EC;
    s32 unkB0F0;
    s32 unkB0F4;
    s32 unkB0F8;
    s32 unkB0FC;
    s32 unkB100;
    s32 unkB104;
    s32 unkB108;
    s32 unkB10C;
    s32 unkB110;
    s32 unkB114;
    s32 unkB118;
    u32 unkB11C;
    s32 unkB120;
    s32 unkB124;
    s32 unkB128;
    s32 unkB12C;
    s32 unkB130;
    s32 unkB134;
    s32 unkB138;
    s32 unkB13C;
    s32 unkB140;
    s32 unkB144;
    s32 unkB148;
    s32 unkB14C;
    s32 unkB150;
    s32 unkB154;
    s32 unkB158;
    s32 unkB15C;
    s32 unkB160;
    s32 unkB164;
    s32 unkB168;
    s32 unkB16C;
    s32 unkB170;
    s32 unkB174;
    s32 unkB178;
    s32 unkB17C;
    s32 unkB180;
    s32 battleActive;
    s32 unkB188;
    s32 unkB18C;
    s32 unkB190;
    s32 unkB194;
    s32 unkB198;
    s32 disconnected;
    s32 unkB1A0;
    s32 unkB1A4;
    s32 unkB1A8;
    s32 unkB1AC;
    s32 unkB1B0;
    s32 unkB1B4;
    s32 unkB1B8;
    s32 unkB1BC;
    s32 unkB1C0;
    s32 unkB1C4;
    s32 unkB1C8;
    s32 unkB1CC;
    s32 unkB1D0;
    s32 unkB1D4;
    s32 unkB1D8;
    s32 unkB1DC;
    s32 unkB1E0;
    s16 waitTimer;
    u8 unkB1E6[2];
    f32 hpNow[4][6];
    f32 hpDisp[4][6];
    f32 hpMax[4][6];
    f32 hpStep[4][6];
    f32 hpFade[4][6];
    f32 hpFadeSpeed[4][6];
    s16 ballX[4][6];
    s16 ballOfs[4][6];
    s8 ballOn[4][6];
    u8 reliveHallOpen;
    s8 nameIndex;
    u16 name[8];
    u8 unkB4B2[0xB524 - 0xB4B2];
#ifndef __MWERKS__
    u32 bgmCounter;
#endif
    MENUCB_DANCER* dancer[9][4];
    u8 unkB5B4[0xB5F4 - 0xB5B4];
};

#ifdef __MWERKS__
#define MENUCB_OFFSET_OF(f) ((u32)&((_MENUCBWORK*)0)->f)
#else
#include <stddef.h>
#define MENUCB_OFFSET_OF(f) offsetof(_MENUCBWORK, f)
#endif
#define MENUCB_CHECK(name, cond) typedef char name[(cond) ? 1 : -1]
MENUCB_CHECK(MenuCBCheckSize, sizeof(_MENUCBWORK) == MENUCB_SIZE);
MENUCB_CHECK(MenuCBCheckTrainer, sizeof(MENUCB_TRAINER) == 0x1320);
MENUCB_CHECK(MenuCBCheckRule, sizeof(MENUCB_RULE) == 0x90);
MENUCB_CHECK(MenuCBCheckErr, sizeof(MENUCB_ERR) == 4);
#ifdef __MWERKS__
MENUCB_CHECK(MenuCBCheckTrainerOrg, MENUCB_OFFSET_OF(trainerOrg) == 0x4C98);
MENUCB_CHECK(MenuCBCheckRuleOff, MENUCB_OFFSET_OF(rule) == 0x9918);
MENUCB_CHECK(MenuCBCheckCurRule, MENUCB_OFFSET_OF(currentRule) == 0x9C78);
MENUCB_CHECK(MenuCBCheckBgm, MENUCB_OFFSET_OF(bgmCounter) == 0x9C7C);
#endif
MENUCB_CHECK(MenuCBCheck9C80, MENUCB_OFFSET_OF(unk9C80) == 0x9C80);
MENUCB_CHECK(MenuCBCheckErrOff, MENUCB_OFFSET_OF(err) == 0x9C84);
MENUCB_CHECK(MenuCBCheckHero, MENUCB_OFFSET_OF(hero) == 0xA65C);
MENUCB_CHECK(MenuCBCheckCol, MENUCB_OFFSET_OF(col) == 0xAFD4);
MENUCB_CHECK(MenuCBCheckB054, MENUCB_OFFSET_OF(unkB054) == 0xB054);
MENUCB_CHECK(MenuCBCheckTemp, MENUCB_OFFSET_OF(tempBuff) == 0xB0D4);
MENUCB_CHECK(MenuCBCheckB194, MENUCB_OFFSET_OF(unkB194) == 0xB194);
MENUCB_CHECK(MenuCBCheckWait, MENUCB_OFFSET_OF(waitTimer) == 0xB1E4);
MENUCB_CHECK(MenuCBCheckHp, MENUCB_OFFSET_OF(hpNow) == 0xB1E8);
MENUCB_CHECK(MenuCBCheckBall, MENUCB_OFFSET_OF(ballX) == 0xB428);
MENUCB_CHECK(MenuCBCheckRelive, MENUCB_OFFSET_OF(reliveHallOpen) == 0xB4A0);
MENUCB_CHECK(MenuCBCheckName, MENUCB_OFFSET_OF(name) == 0xB4A2);
#ifdef __MWERKS__
MENUCB_CHECK(MenuCBCheckDancer, MENUCB_OFFSET_OF(dancer) == 0xB524);
#else
MENUCB_CHECK(MenuCBCheckDancer, MENUCB_OFFSET_OF(dancer) == 0xB528);
#endif

#endif
