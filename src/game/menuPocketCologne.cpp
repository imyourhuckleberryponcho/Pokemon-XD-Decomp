// Not yet decompiled.
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
struct Hero;
struct MenuItem;
struct POCKET_COLOGNE_ARG;
struct tagSPRITE_WORK;
struct tagWINDOW_WORK;

extern "C++" {
// ---- draft declarations ----
struct Hero {
    u8 _draft[1];
};
struct MenuItem {
    u8 _draft[1];
};
struct POCKET_COLOGNE_ARG {
    u8 _draft[1];
};
struct tagSPRITE_WORK {
    u8 _draft[1];
};
struct tagWINDOW_WORK {
    u8 _draft[1];
};

extern "C" {
u32 GSmsgGetRect(s32);
s32 GSmsgPrint2(s32, s32, s32, s32);
void* heroItemGetItemKindToItemAryPtr(Hero*, u8, u16*, u16*, u8*, u8*);
u32 itemBiosGetNum(u8* p);
u8 itemCheckValid(u32);
u8 itemDataBiosGetKind(u8* p);
u32 itemDataBiosGetName(u8* p);
u8* itemDataBiosGetPtr(u16 index);
u32 itemGetStatus(u32, u32, u32, u32);
void menuClose(s32 menuID);
void menuCloseSync(s32 menuID, s32);
MenuItem* menuItemBiosGetPtr(s32 menuID, u32 index);
void menuOpenCustom(s32 menuID, ...);
s32 menuPocketColognCtrl(void *p0);
s32 menuPocketColognCursor(void *p0);
s32 menuPocketColognDrawCursor(void *p0, void *p1);
s32 menuPocketColognDrawItemText(void *p0, void *p1);
s32 menuPocketColognDrawLineCursor(void *p0, void *p1);
u16 menuPocketCologne(s32 p0);
void menuSubCursorAnimeInit(void);
void menuSubCursorAnimeMain(void);
void menuSubCursorAnimeStart(void);
void menuSubCursorAnimeValGet(f32* pos, s32* color);
void msgctrlSetValue(s32 id, u32 value);
void winSeqSetMenu(s32 menuID, u32 id);
s32 winSpriteGetLayerID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on);
s32 windowDrawSpriteCursor(s32, s32, s32, void*, s32, s32, s32, s32*);
s32 windowGetActiveID(void);
u32 windowGetKeyRepeat(void);
extern s32 jtbl_2063;
extern s32 jtbl_2041;
extern s32 init;
extern s32 jtbl_2066;
}
extern "C++" {
static void getItemName(unsigned long p0);
static u16 getItemNum(unsigned short p0);
static s32 getLineHeight(tagWINDOW_WORK* p0);
static u16 getStockMax(unsigned short p0);
static void makePocketCologneArg(POCKET_COLOGNE_ARG* p0, unsigned long p1);
}
static f32 ActMenuCursorBlinkTime;
// ---- draft declarations ----


static s32 first_S1990;
static u8 init_S1991;
static u16 getItemNum(unsigned short p0) {
    u8 *var_r30;
    s32 var_r29;
    s32 var_r28;
    u16 sp8;

    var_r28 = 0;
    var_r30 = (unsigned char *)(heroItemGetItemKindToItemAryPtr((Hero*)(NULL), itemDataBiosGetKind((u8*)(itemDataBiosGetPtr(p0))), (u16*)(&sp8), (u16*)(NULL), (u8*)(NULL), (u8*)(NULL)));
    if (var_r30 == NULL) {
        return 0U;
    }
    var_r29 = 0;
    while (var_r29 < (s32) sp8) {
        if ((itemCheckValid((u32) var_r30) != 0) && (p0 == itemGetStatus((u32) var_r30, 0U, 0x1BU, 0U))) {
            var_r28 += itemBiosGetNum((u8*)(var_r30));
        }
        var_r29 += 1;
        var_r30 += 4;
    }
    return var_r28;
}
}

extern "C++" {
static u16 getStockMax(unsigned short p0) {
    u16 sp8;

    heroItemGetItemKindToItemAryPtr((Hero*)(NULL), itemDataBiosGetKind((u8*)(itemDataBiosGetPtr(p0))), (u16*)(NULL), (u16*)(&sp8), (u8*)(NULL), (u8*)(NULL));
    return sp8;
}
}

extern "C++" {
static void getItemName(unsigned long p0) {
    itemDataBiosGetName((u8*)(itemDataBiosGetPtr((u16) p0)));
}
}

extern "C" {
s32 menuPocketColognDrawLineCursor(void *p0, void *p1) {
    MenuItem *temp_r31;

    temp_r31 = menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), (u32) M2C_FIELD(p1, s16 *, 6));
    M2C_FIELD(p1, s16 *, 0x52) = (s16) (M2C_FIELD(temp_r31, s16 *, 8) + (M2C_FIELD(p0, s16 *, 0x9E) * getLineHeight((tagWINDOW_WORK*)((tagWINDOW_WORK *) p0))));
    return 0;
}
}

extern "C++" {
static s32 getLineHeight(tagWINDOW_WORK* p0) {
    MenuItem *temp_r31;
    s32 var_r3;

    temp_r31 = menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), 0x12BU);
    var_r3 = M2C_FIELD(temp_r31, s16 *, 8) - M2C_FIELD(menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), 0x12CU), s16 *, 8);
    if (var_r3 < 0) {
        var_r3 = -var_r3;
    }
    return var_r3;
}
}

extern "C" {
s32 menuPocketColognDrawCursor(void *p0, void *p1) {
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    f32 sp14;
    s32 sp10;
    s32 sp8;
    s32 temp_r9;

    sp1C = M2C_FIELD(&jtbl_2063, s32 *, 0);
    sp20 = M2C_FIELD(&jtbl_2063, s32 *, 4);
    sp24 = M2C_FIELD(&jtbl_2063, s32 *, 8);
    sp28 = M2C_FIELD(&jtbl_2063, s32 *, 0xC);
    if ((s16) M2C_FIELD(p1, s16 *, 6) == (s32) (&sp1C)[M2C_FIELD(p0, s16 *, 0x9E)]) {
        sp14 = M2C_FIELD(&jtbl_2066, f32 *, 0);
        sp18 = M2C_FIELD(&jtbl_2066, s32 *, 4);
        sp10 = -1;
        if ((s32) M2C_FIELD(p0, s32 *, 4) == windowGetActiveID()) {
            menuSubCursorAnimeValGet((f32*)(&sp14), (s32*)(&sp10));
        }
        temp_r9 = winSpriteGetLayerID((tagWINDOW_WORK*)((tagWINDOW_WORK *) p0), (tagSPRITE_WORK*)((tagSPRITE_WORK *) p1));
        sp8 = sp10;
        windowDrawSpriteCursor(0, 0, -1, p0, 0xC2, 0, temp_r9, (s32 *) &sp14);
    }
    winSpriteSetDisp((tagSPRITE_WORK*)((tagSPRITE_WORK *) p1), 0U);
    return 0;
}
}

extern "C" {
s32 menuPocketColognDrawItemText(void *p0, void *p1) {
    s16 temp_r26;
    s16 temp_r28;
    s16 temp_r28_2;
    s16 temp_r28_3;
    s16 temp_r28_4;
    s16 temp_r29;
    s16 temp_r7;
    s32 temp_r27;
    s32 var_r6;
    u16 temp_r3;
    u32 temp_r4;
    u8 *temp_r31;

    temp_r7 = M2C_FIELD(p1, s16 *, 6);
    temp_r31 = M2C_FIELD(p0, u8 **, 0x68);
    if (temp_r7 == 0x127) {
        getItemName(0x200U);
        temp_r28 = M2C_FIELD(menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), 0x127U), s16 *, 0xA);
        temp_r29 = (s16) (GSmsgGetRect(M2C_ERROR(/* Read from unset register $r3 */)) >> 0x10U);
        temp_r4 = temp_r28 - temp_r29;
        GSmsgPrint2(winSpriteGetLayerID((tagWINDOW_WORK*)((tagWINDOW_WORK *) p0), (tagSPRITE_WORK*)((tagSPRITE_WORK *) p1)), (s32) ((temp_r4 >> 0x1FU) + temp_r4) >> 1, 0, -1);
        return 0;
    }
    var_r6 = 0;
    if (temp_r7 != (s32) M2C_FIELD(&jtbl_2041, s32 *, 0)) {
        var_r6 = 1;
        if (temp_r7 != (s32) M2C_FIELD(&jtbl_2041, s32 *, 4)) {
            var_r6 = 2;
            if (temp_r7 != (s32) M2C_FIELD(&jtbl_2041, s32 *, 8)) {
                var_r6 = 3;
                if (temp_r7 != (s32) M2C_FIELD(&jtbl_2041, s32 *, 0xC)) {
                    var_r6 = 4;
                }
            }
        }
    }
    if ((var_r6 < 0) || (var_r6 >= (s32) M2C_FIELD(temp_r31, s32 *, 0x14))) {
        return 0;
    }
    temp_r27 = (var_r6 * 4) + 4;
    temp_r3 = *(temp_r31 + temp_r27);
    if (temp_r3 == 0) {

    } else {
        getItemName((u32) temp_r3);
    }
    GSmsgPrint2(winSpriteGetLayerID((tagWINDOW_WORK*)((tagWINDOW_WORK *) p0), (tagSPRITE_WORK*)((tagSPRITE_WORK *) p1)), 0, 0, -1);
    if ((u16) *(temp_r31 + temp_r27) != 0) {
        temp_r26 = M2C_FIELD(menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), 0x130U), s16 *, 0xA);
        msgctrlSetValue(0x34, getStockMax(*(temp_r31 + temp_r27)));
        temp_r28_2 = (s16) (GSmsgGetRect(0x426F) >> 0x10U);
        temp_r28_3 = temp_r28_2 + (s16) (GSmsgGetRect(0x428F) >> 0x10U);
        GSmsgPrint2(winSpriteGetLayerID((tagWINDOW_WORK*)((tagWINDOW_WORK *) p0), (tagSPRITE_WORK*)((tagSPRITE_WORK *) p1)), temp_r26 - temp_r28_3, 0, -1);
        msgctrlSetValue(0x34, getItemNum(*(temp_r31 + temp_r27)));
        temp_r28_4 = (s16) (GSmsgGetRect(0x426F) >> 0x10U);
        GSmsgPrint2(winSpriteGetLayerID((tagWINDOW_WORK*)((tagWINDOW_WORK *) p0), (tagSPRITE_WORK*)((tagSPRITE_WORK *) p1)), temp_r26 - temp_r28_4, 0, -1);
    }
    return 0;
}
}

extern "C" {
s32 menuPocketColognCursor(void *p0) {
    s16 temp_r4;
    u16 temp_r3;
    s32 var_r0;
    s32 var_r0_2;
    s32 temp_r5;
    u8 *temp_r31;

    temp_r31 = M2C_FIELD(p0, u8 **, 0x68);
    temp_r3 = windowGetKeyRepeat();
    temp_r5 = M2C_FIELD(temp_r31, s32 *, 0x14);
    temp_r4 = M2C_FIELD(p0, s16 *, 0x9E);
    if ((s32) (temp_r3 & 2) != 0) {
        var_r0 = temp_r4 + 1;
        if (var_r0 >= temp_r5) {
            var_r0 = temp_r5 - 1;
        }
        M2C_FIELD(p0, s16 *, 0x9E) = (s16) var_r0;
    }
    if ((s32) (temp_r3 & 1) != 0) {
        var_r0_2 = M2C_FIELD(p0, s16 *, 0x9E) - 1;
        if (var_r0_2 < 0) {
            var_r0_2 = 0;
        }
        M2C_FIELD(p0, s16 *, 0x9E) = (s16) var_r0_2;
    }
    if (temp_r4 != (s16) M2C_FIELD(p0, s16 *, 0x9E)) {
        menuSubCursorAnimeStart();
    }
    return 0;
}
}

extern "C" {
s32 menuPocketColognCtrl(void *p0) {
    f32 temp_f1;
    u8 temp_r0;

    temp_r0 = M2C_FIELD(p0, u8 *, 1);
    switch ((s8) temp_r0) {                         /* irregular */
    case 0:
        if ((s8) M2C_FIELD(p0, u8 *, 2) == 0) {
            winSeqSetMenu(0x32, 0x60U);
            ActMenuCursorBlinkTime = 0.0f;
            M2C_FIELD(p0, u8 *, 2) = 1U;
            menuSubCursorAnimeInit();
        }
        break;
    case 2:
        temp_f1 = ActMenuCursorBlinkTime + 0.033333335f;
        ActMenuCursorBlinkTime = temp_f1;
        if (temp_f1 > 1.0f) {
            ActMenuCursorBlinkTime = 0.0f;
        }
        menuSubCursorAnimeMain();
        break;
    case 3:
        if ((s8) M2C_FIELD(p0, u8 *, 2) == 0) {
            winSeqSetMenu(0x32, 0x64U);
            M2C_FIELD(p0, u8 *, 2) = 1U;
        }
        break;
    }
    return 0;
}
}

extern "C++" {
static void makePocketCologneArg(POCKET_COLOGNE_ARG* p0, unsigned long p1) {
    M2C_FIELD(p0, u32 *, 0) = p1;
    M2C_FIELD(p0, s16 *, 4) = 0x201;
    M2C_FIELD(p0, s16 *, 8) = 0x202;
    M2C_FIELD(p0, s16 *, 0xC) = 0x203;
    M2C_FIELD(p0, s16 *, 0x10) = 0;
    M2C_FIELD(p0, s32 *, 0x14) = 4;
}
extern "C" {
u16 menuPocketCologne(s32 p0) {
    volatile s32 sp1C;
    u8 spC[16];
    f32 unksp8;
    s32 temp_r31_2;
    s32 temp_ret;
    u16 temp_r31;

    if ((s8) init_S1991 == 0) {
        first_S1990 = 1;
        init_S1991 = 1;
    }
    if ((s32) first_S1990 != 0) {
        first_S1990 = 0;
    }
    makePocketCologneArg((POCKET_COLOGNE_ARG*)(&unksp8), (u32) p0);
    temp_ret = windowGetActiveID();
    menuOpenCustom(0x32, temp_ret, 0, 0, 1, 1, &unksp8, M2C_BITWISE(f32, temp_ret));
    temp_r31_2 = M2C_ERROR(/* Read from unset register $r3 */);
    menuClose(0x32);
    menuCloseSync(0x32, 1);
    if ((0 <= temp_r31_2) && (temp_r31_2 < sp1C)) {
        temp_r31 = (&spC[0])[temp_r31_2];
        if (getItemNum(temp_r31) != 0) {
            return temp_r31;
        }
        return 0U;
    }
    return 0U;
}
}

}

