// Partial: only the status accessors are written so far.
#include <dolphin/types.h>
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#pragma peephole off
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct FightTrainerKindData;
struct Hero;
struct char16;

struct MenuCBBattleStartWork {
    u32 unk0;
    s32 status; // 0x04
    u8 unk8[0x140];
};

extern "C" {

extern MenuCBBattleStartWork _menuCBBattleStartWork;


extern "C++" {
// ---- draft declarations ----
struct FightTrainerKindData {
    u8 _draft[1];
};
struct Hero {
    u8 _draft[1];
};
struct char16 {
    u8 _draft[1];
};
struct _struct__menuCBBattleStartWork_0x8 {
     s32 unk0;                             
     s32 unk4;                             
};
struct _struct_menuCBBattleStartDispWork_0x18 {
     s32 unk0;                            
     s32 unk4;                            
     s32 unk8;                            
     s32 unkC;                            
     s32 unk10;                           
     s32 unk14;                           
};
extern "C" {
void GScharCpy(char16*, const char16*);
void GSfsysFree(u32 id);
u8 GSfsysReadIDEX(u32 id, u32 idx, void (*cb)(long, void*, long), void* user, u32 c);
char* GSmsgGetGSchar(u32 msg);
void GSresFreeGroup(u32 grp);
void GSresFreeResource(u32 grp, u32 id);
void* GSresGetResourceAllGroup(u32 id);
s32 GSsndGetStatus(u32 id);
u32 HSD_Rand(void);
static void __sinit_menuCB_BattleStart_cpp();
u8 fightTrainerDB_GetKindDataId(u16 id);
u32 fightTrainerKindDataBiosGetPrefixName(FightTrainerKindData* data);
FightTrainerKindData* fightTrainerKindDataBiosGetPtr(u16 id);
u16* heroBiosGetNamePtr(Hero* hero);
s32 menuCBPokemonEntryLoadTex();
s32 menuCBPokemonEntryTexWorkInit();
u32 menuCB_BattleStartSoundCheck();
void soundOpenPlay(s32, s32, s32);
u32 toolentryGetTrainerBicFaceResID(s32 player, s32 flag);
u32 toolentryGetTrainerSamllFaceResID(s32 player, s32 flag);
s32 toolentryTaisenGetBattleType(void);
u16 toolentryTaisenGetEntryPokemonNum(s32 player);
Hero* toolentryTaisenGetHeroPtr(s32 player);
u16 toolentryTaisenGetPokemonNum(s32 player);
u16 toolentryTaisenGetTrainerDataID(s32 player);
extern s32 jtbl_2154;
}
extern "C++" {
static u8 _menuCBBattleCheckTrainer(long p0, long p1);
static void _menuCBBattleStartDispTrainerTexCallBack(long p0, void* p1, long p2);
static s32 _menuCBBattleStartGetTrainerFaceSize();
static void _menuCBBattleStartSetIndexDouble(long p0, unsigned short p1);
static void _menuCBBattleStartSetIndexMulti(long p0, unsigned short p1);
static void _menuCBBattleStartSetIndexSingle(long p0, unsigned short p1);
static void _menuCBBattleStartSetIndex();
static void _menuCBBattleStartSetTrainerData();
static void _menuCBBattleStartWorkInit();
}
static struct _struct_menuCBBattleStartDispWork_0x18 menuCBBattleStartDispWork[4];
extern "C++" {
extern "C++" {
extern "C++" {
extern "C++" {

extern "C++" {
// ---- draft declarations ----


extern "C" {
void menuCBBattleStartDispTrainerInit();
void menuCBBattleStartInit(s32 p0, s32 p1);
void menuCBBattleStartTrainerFaceFree();
void menuCBBattleStartTrainerLoadTex();
extern s32 jtbl_2145;
extern s32 jtbl_2136;
}

// ---- draft declarations ----



static void _menuCBBattleStartSetIndex() {
    s32 spC;
    s32 sp8;
    s32 *var_r30;
    s32 *var_r30_2;
    s32 *var_r30_3;
    s32 *var_r30_4;
    s32 *var_r30_5;
    s32 temp_r31;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;

    temp_r31 = toolentryTaisenGetBattleType();
    sp8 = M2C_FIELD(&jtbl_2154, s32 *, 0);
    spC = M2C_FIELD(&jtbl_2154, s32 *, 4);
    _menuCBBattleStartWorkInit();
    switch ((s32) M2C_FIELD(&_menuCBBattleStartWork, s32 *, 4)) { /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        var_r30 = &sp8;
        var_r29 = 0;
        do {
            *var_r30 = toolentryTaisenGetPokemonNum(var_r29);
            var_r30 += 2;
            var_r29 += 1;
        } while (var_r29 < 4);
        break;
    case 1:                                         /* switch 1 */
        var_r30_2 = &sp8;
        var_r29_2 = 0;
        do {
            *var_r30_2 = toolentryTaisenGetEntryPokemonNum(var_r29_2);
            var_r30_2 += 2;
            var_r29_2 += 1;
        } while (var_r29_2 < 4);
        break;
    }
    switch (temp_r31) {                             /* switch 2; irregular */
    case 0:                                         /* switch 2 */
        var_r30_3 = &sp8;
        var_r31 = 0;
        do {
            _menuCBBattleStartSetIndexSingle(var_r31, *var_r30_3);
            var_r30_3 += 2;
            var_r31 += 1;
        } while (var_r31 < 2);
        return;
    case 1:                                         /* switch 2 */
        var_r30_4 = &sp8;
        var_r31_2 = 0;
        do {
            _menuCBBattleStartSetIndexDouble(var_r31_2, *var_r30_4);
            var_r30_4 += 2;
            var_r31_2 += 1;
        } while (var_r31_2 < 2);
        return;
    case 2:                                         /* switch 2 */
        var_r30_5 = &sp8;
        var_r31_3 = 0;
        do {
            _menuCBBattleStartSetIndexMulti(var_r31_3, *var_r30_5);
            var_r30_5 += 2;
            var_r31_3 += 1;
        } while (var_r31_3 < 4);
        return;
    }
}
}

extern "C++" {
static void _menuCBBattleStartSetIndexDouble(long p0, unsigned short p1) {
    s32 sp8;
    s32 sp4;
    struct _struct_menuCBBattleStartDispWork_0x18 *temp_r7;
    u8 *temp_r4;

    temp_r7 = &menuCBBattleStartDispWork[p0];
    M2C_STRUCT_COPY((s32) &sp4 + 4, (s32) (&jtbl_2145 - 4) + 4, 0x90);
    temp_r4 = (unsigned char *)(&sp8 + ((p1 - 1) * 0x18));
    temp_r7->unk0 = M2C_FIELD(temp_r4, s32 *, 0);
    temp_r7->unk4 = M2C_FIELD(temp_r4, s32 *, 4);
    temp_r7->unk8 = M2C_FIELD(temp_r4, s32 *, 8);
    temp_r7->unkC = M2C_FIELD(temp_r4, s32 *, 0xC);
    temp_r7->unk10 = M2C_FIELD(temp_r4, s32 *, 0x10);
    temp_r7->unk14 = M2C_FIELD(temp_r4, s32 *, 0x14);
}
}

extern "C++" {
static void _menuCBBattleStartSetIndexSingle(long p0, unsigned short p1) {
    s32 sp8;
    s32 sp4;
    struct _struct_menuCBBattleStartDispWork_0x18 *temp_r7;
    u8 *temp_r4;

    temp_r7 = &menuCBBattleStartDispWork[p0];
    M2C_STRUCT_COPY((s32) &sp4 + 4, (s32) (&jtbl_2136 - 4) + 4, 0x90);
    temp_r4 = (unsigned char *)(&sp8 + ((p1 - 1) * 0x18));
    temp_r7->unk0 = M2C_FIELD(temp_r4, s32 *, 0);
    temp_r7->unk4 = M2C_FIELD(temp_r4, s32 *, 4);
    temp_r7->unk8 = M2C_FIELD(temp_r4, s32 *, 8);
    temp_r7->unkC = M2C_FIELD(temp_r4, s32 *, 0xC);
    temp_r7->unk10 = M2C_FIELD(temp_r4, s32 *, 0x10);
    temp_r7->unk14 = M2C_FIELD(temp_r4, s32 *, 0x14);
}
}

static void _menuCBBattleStartWorkInit() {
    struct _struct_menuCBBattleStartDispWork_0x18 *temp_r9;
    struct _struct_menuCBBattleStartDispWork_0x18 *temp_r9_2;

    menuCBBattleStartDispWork->unk0 = 0;
    menuCBBattleStartDispWork->unk4 = 1;
    menuCBBattleStartDispWork->unk8 = 2;
    menuCBBattleStartDispWork->unkC = 3;
    menuCBBattleStartDispWork->unk10 = 4;
    menuCBBattleStartDispWork->unk14 = 5;
    menuCBBattleStartDispWork[1].unk0 = 0;
    menuCBBattleStartDispWork[1].unk4 = 1;
    menuCBBattleStartDispWork[1].unk8 = 2;
    menuCBBattleStartDispWork[1].unkC = 3;
    menuCBBattleStartDispWork[1].unk10 = 4;
    menuCBBattleStartDispWork[1].unk14 = 5;
    temp_r9 = &menuCBBattleStartDispWork[1] + 0x18;
    menuCBBattleStartDispWork[2].unk0 = 0;
    temp_r9->unk4 = 1;
    temp_r9->unk8 = 2;
    temp_r9->unkC = 3;
    temp_r9->unk10 = 4;
    temp_r9->unk14 = 5;
    temp_r9_2 = temp_r9 + 0x18;
    M2C_FIELD(temp_r9, s32 *, 0x18) = 0;
    temp_r9_2->unk4 = 1;
    temp_r9_2->unk8 = 2;
    temp_r9_2->unkC = 3;
    temp_r9_2->unk10 = 4;
    temp_r9_2->unk14 = 5;
}
extern "C" {

extern "C++" {
static void _menuCBBattleStartSetIndexMulti(long p0, unsigned short p1) {
    s32 temp_r0;
    struct _struct_menuCBBattleStartDispWork_0x18 *temp_r5;
    u16 temp_r4;
    u32 temp_r4_2;
    u16 temp_r4_3;
    u16 temp_r4_4;
    u16 temp_r4_5;
    u16 temp_r4_6;
    u16 temp_r4_7;
    u16 temp_r6;
    u16 temp_r6_2;
    u16 temp_r7;
    u16 temp_r7_2;
    u16 temp_r8;
    u16 temp_r9;
    u16 var_r3;
    u16 var_r3_2;
    u16 var_r4;
    u8 *temp_r12;
    u8 *temp_r8_2;

    var_r4 = p1;
    var_r3 = 0;
    temp_r5 = &menuCBBattleStartDispWork[p0];
    if (var_r4 > 0U) {
        if (var_r4 > 8U) {
loop_4:
            if (var_r3 < (u16) (var_r4 - 8)) {
                M2C_FIELD(temp_r12, s32 *, 0) = (s32) var_r3;
                temp_r12 = (unsigned char *)(temp_r5 + (var_r3 * 4));
                M2C_FIELD(temp_r12, s32 *, 4) = (s32) (u16) (var_r3 + 1);
                M2C_FIELD(temp_r12, s32 *, 8) = (s32) (u16) (var_r3 + 2);
                temp_r9 = var_r3 + 4;
                temp_r8 = var_r3 + 5;
                M2C_FIELD(temp_r12, s32 *, 0xC) = (s32) (u16) (var_r3 + 3);
                temp_r7 = var_r3 + 6;
                temp_r6 = var_r3 + 7;
                var_r3 += 8;
                M2C_FIELD(temp_r12, s32 *, 0x10) = (s32) temp_r9;
                M2C_FIELD(temp_r12, s32 *, 0x14) = (s32) temp_r8;
                M2C_FIELD(temp_r12, s32 *, 0x18) = (s32) temp_r7;
                M2C_FIELD(temp_r12, s32 *, 0x1C) = (s32) temp_r6;
                goto loop_4;
            }
        }
loop_7:
        if (var_r3 < var_r4) {
            temp_r7_2 = var_r3;
            var_r3 += 1;
            *(s32 *)((u8 *)temp_r5 + (temp_r7_2 * 4)) = (s32) temp_r7_2;
            goto loop_7;
        }
    }
    var_r3_2 = var_r4;
    if (var_r4 < 6U) {
        if ((u16) (6 - var_r4) > 8U) {
loop_12:
            if (var_r3_2 < -2U) {
                temp_r0 = var_r3_2 * 4;
                temp_r4 = var_r4 + 1;
                var_r3_2 += 8;
                temp_r8_2 = (unsigned char *)(temp_r5 + temp_r0);
                temp_r4_2 = temp_r4 + 1;
                M2C_FIELD(temp_r8_2, s32 *, 0) = (s32) var_r4;
                M2C_FIELD(temp_r8_2, s32 *, 4) = (s32) temp_r4;
                temp_r4_3 = temp_r4_2 + 1;
                M2C_FIELD(temp_r8_2, s32 *, 8) = (s32) temp_r4_2;
                temp_r4_4 = temp_r4_3 + 1;
                M2C_FIELD(temp_r8_2, s32 *, 0xC) = (s32) temp_r4_3;
                temp_r4_5 = temp_r4_4 + 1;
                M2C_FIELD(temp_r8_2, s32 *, 0x10) = (s32) temp_r4_4;
                temp_r4_6 = temp_r4_5 + 1;
                M2C_FIELD(temp_r8_2, s32 *, 0x14) = (s32) temp_r4_5;
                temp_r4_7 = temp_r4_6 + 1;
                M2C_FIELD(temp_r8_2, s32 *, 0x18) = (s32) temp_r4_6;
                var_r4 = temp_r4_7 + 1;
                M2C_FIELD(temp_r8_2, s32 *, 0x1C) = (s32) temp_r4_7;
                goto loop_12;
            }
        }
loop_15:
        if (var_r3_2 < 6U) {
            temp_r6_2 = var_r4;
            var_r4 += 1;
            *(s32 *)((u8 *)temp_r5 + (var_r3_2 * 4)) = (s32) temp_r6_2;
            var_r3_2 += 1;
            goto loop_15;
        }
    }
}
}
u32 menuCB_BattleStartSoundCheck() {
    s32 temp_r3;

    temp_r3 = GSsndGetStatus(M2C_FIELD(&_menuCBBattleStartWork, u32 *, 0x124));
    return (u32) ((2 - temp_r3) | (temp_r3 - 2)) >> 0x1FU;
}
}

}

}
}
}
}
void menuCBBattleStartSetStatus(s32 status) {
    _menuCBBattleStartWork.status = status;
}

s32 menuCBBattleStartGetStatus(void) {
    return _menuCBBattleStartWork.status;
}
extern "C++" {
static void _menuCBBattleStartSetTrainerData() {
    char16 *temp_r31;
    u16 *temp_r4;

    if (_menuCBBattleCheckTrainer(1, toolentryTaisenGetBattleType()) != 0) {
        temp_r31 = (char16 *)(&_menuCBBattleStartWork + 0x12C);
        temp_r4 = heroBiosGetNamePtr((Hero*)(toolentryTaisenGetHeroPtr(1)));
        if (temp_r31 != NULL) {
            GScharCpy((char16*)(temp_r31), (const char16*)((char16 *) temp_r4));
        } else {
            GScharCpy((char16*)(temp_r31), (const char16*)(GSmsgGetGSchar(1U)));
        }
        M2C_FIELD(&_menuCBBattleStartWork, u32 *, 0x144) = fightTrainerKindDataBiosGetPrefixName((FightTrainerKindData*)(fightTrainerKindDataBiosGetPtr((u16) fightTrainerDB_GetKindDataId(toolentryTaisenGetTrainerDataID(1)))));
    }
}
}

extern "C++" {
extern "C++" {
static u8 _menuCBBattleCheckTrainer(long p0, long p1) {
    s32 temp_r3;
    u8 var_r31;

    var_r31 = 1;
    temp_r3 = toolentryTaisenGetBattleType();
    if (p1 == 2) {
        if (temp_r3 != 2) {
            var_r31 = 0;
        }
    } else if (temp_r3 == 2) {
        var_r31 = 0;
    }
    return var_r31;
}
extern "C" {
void menuCBBattleStartInit(s32 p0, s32 p1) {
    s32 temp_r0;

    _menuCBBattleStartSetTrainerData();
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0) = p0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 4) = p1;
    _menuCBBattleStartSetIndex();
    switch (p1) {                                   /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        menuCBPokemonEntryTexWorkInit();
        menuCBPokemonEntryLoadTex();
        temp_r0 = HSD_Rand() % 3;
        switch (temp_r0) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x3D2;
            break;
        case 1:                                     /* switch 2 */
            M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x3F5;
            break;
        case 2:                                     /* switch 2 */
            M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x3F6;
            break;
        default:                                    /* switch 2 */
            M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x3F7;
            break;
        }
        soundOpenPlay(M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124), 0, 0xFF);
        return;
    case 1:                                         /* switch 1 */
        menuCBPokemonEntryTexWorkInit();
        menuCBPokemonEntryLoadTex();
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x5DB;
        soundOpenPlay(0x5DB, 0, 0xFF);
        return;
    }
}
}

extern "C" {
void menuCBBattleStartDispTrainerInit() {
    M2C_FIELD(&_menuCBBattleStartWork, s8 *, 0x34) = 0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x2C) = 0;
    if (_menuCBBattleStartGetTrainerFaceSize() == 0) {
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30) = 4;
    } else {
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30) = 2;
    }
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x10) = 0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0xC) = 0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x18) = 0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x14) = 0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x20) = 0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x1C) = 0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x28) = 0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x24) = 0;
}
}

extern "C" {
void menuCBBattleStartTrainerLoadTex() {
    _menuCBBattleStartGetTrainerFaceSize();
    M2C_FIELD(&_menuCBBattleStartWork, s8 *, 0x34) = 1;
    _menuCBBattleStartDispTrainerTexCallBack(0, (void*)(NULL), 0);
}
}

}

extern "C" {
extern "C" {
extern "C" {
extern "C++" {
static s32 _menuCBBattleStartGetTrainerFaceSize() {
    s32 temp_r3;

    temp_r3 = toolentryTaisenGetBattleType();
    return (s32) ((u32) ((2 - temp_r3) | (temp_r3 - 2)) >> 0x1FU);
}
}

extern "C++" {
struct MenuCBBattleStartTrainerTexture {
    void* texture;
    u32 resource;
};

struct MenuCBBattleStartTrainerTextureState {
    u8 pad0[0xC];
    MenuCBBattleStartTrainerTexture entries[4];
    s32 current;
    s32 count;
};

#pragma dont_inline on
static void _menuCBBattleStartDispTrainerTexCallBack(long unused, void* done, long arg) {
    MenuCBBattleStartTrainerTexture* completed = (MenuCBBattleStartTrainerTexture*)done;
    MenuCBBattleStartTrainerTextureState* state;
    MenuCBBattleStartTrainerTexture* entry;
    u32 resource;
    u32 imageId;
    s32 keepLoading;

    keepLoading = 1;
    if (completed != 0) {
        completed->texture = GSresGetResourceAllGroup(completed->resource);
    }

    state = (MenuCBBattleStartTrainerTextureState*)&_menuCBBattleStartWork;
    do {
        if (state->current == state->count) {
            keepLoading = 0;
        } else {
            if (_menuCBBattleStartGetTrainerFaceSize() != 0) {
                if (state->current % 2 != 0) {
                    resource = toolentryGetTrainerBicFaceResID(1, 0);
                } else {
                    resource = toolentryGetTrainerBicFaceResID(0, 1);
                }
            } else if (state->current < 2) {
                resource = toolentryGetTrainerSamllFaceResID(state->current, 1);
            } else {
                resource = toolentryGetTrainerSamllFaceResID(state->current, 0);
            }

            if (_menuCBBattleStartGetTrainerFaceSize() != 0) {
                imageId = 0x5C3;
            } else {
                imageId = 0x5C4;
            }
            entry = &((MenuCBBattleStartTrainerTextureState*)&_menuCBBattleStartWork)->entries[state->current];
            entry->resource = resource;
            entry->texture = GSresGetResourceAllGroup(entry->resource);
            if (entry->texture != 0) {
                state->current++;
            } else {
                GSfsysReadIDEX(imageId, resource, _menuCBBattleStartDispTrainerTexCallBack, entry, resource);
                keepLoading = 0;
                state->current++;
            }
        }
    } while (keepLoading != 0);
}
extern "C" {
void menuCBBattleStartTrainerFaceFree() {
    s32 var_r28;
    u32 var_r29;
    u8 *var_r30;

    if (_menuCBBattleStartGetTrainerFaceSize() != 0) {
        var_r29 = 0x5C3;
    } else {
        var_r29 = 0x5C4;
    }
    GSfsysFree(var_r29);
    GSresFreeGroup(var_r29);
    var_r30 = (unsigned char *)(&_menuCBBattleStartWork + 0xC);
    if (_menuCBBattleStartGetTrainerFaceSize() == 0) {
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30) = 4;
    } else {
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30) = 2;
    }
    var_r28 = 0;
loop_8:
    if (var_r28 < (s32) M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30)) {
        GSresFreeResource(var_r29, M2C_FIELD(var_r30, u32 *, 4));
        var_r30 += 8;
        var_r28 += 1;
        goto loop_8;
    }
    menuCBBattleStartDispTrainerInit();
}
}

#pragma dont_inline reset
extern "C" {
extern "C" {
static void __sinit_menuCB_BattleStart_cpp() {
}
}
}
}
}
}
}
}


}
