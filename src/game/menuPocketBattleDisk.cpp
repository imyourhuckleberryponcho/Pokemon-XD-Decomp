#include <dolphin/types.h>
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
struct MenuSprite;
struct MenuSpriteVal;
#pragma peephole off
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
struct MenuItem;
struct tagSPRITE_WORK;
struct tagWINDOW_WORK;

extern "C" {

extern "C" {
struct MenuItem {
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
s32 GSmsgPrint2(s32, s32, s32, u32, u32);
void* memset(void* dst, int val, size_t n);
s32 menuBattleDiskCloseDoc();
s32 menuBattleDiskOpenDoc(u8);
void menuCloseCustom(s32 menuID, s32, s32);
MenuItem* menuItemBiosGetPtr(s32 menuID, u32 index);
void menuPdaSubScrollBar(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32, u32, s32, s32, s16*);
s32 menuPocketBattleDiskDrawBallCursor(void *p0, void *p1);
s32 menuPocketBattleDiskDrawLineCursor(void *p0, void *p1);
u16 menuPocketBattleDiskMain(s32 p0, s32 p1, s32 p2);
s32 menuPocketBattleDiskPrintItemKind(void *p0, void *p1);
s32 menuPocketBattleDiskPrintItemList(void *p0, void *p1);
void menuSubCursorAnimeInit(void);
void menuSubCursorAnimeMain(void);
void menuSubCursorAnimeValGet(f32* pos, s32* color);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void spriteSetOffset(s32, s16, s16);
void spriteSetScissor(s32, s32, s32, s32, s32);
void winSeqSetMenu(s32 menuID, u32 id);
s32 winSpriteGetLayerID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on);
s32 windowDrawSpriteCursor(s32, s16, s32, void*, s32, s32, s32, void*, s32);
s32 windowGetActiveID(void);
extern s32 jtbl_2177;
extern s32 Data__34;
extern s32 _controlCursor__34;
extern s32 printItemList__34;
}
extern "C++" {
static s32 getCursorPositionY();
void menuPocketButtonWait();
void menuPocketToolFloatToZero(f32& v, f32 step);
}

struct Hero {
    u8 _draft[1];
};
struct MenuSprite {
    u8 _draft[1];
};
struct MenuSpriteVal {
    u8 _draft[1];
};

extern "C" {
void* heroItemGetItemKindToItemAryPtr(Hero*, u8, u16*, u16*, u8*, u8*);
u16 itemBiosGetItemDataId(u8* p);
u8 itemCheckValid(s32);
u32 itemDataBiosGetName(u8* p);
u8* itemDataBiosGetPtr(u16 index);
s32 menuOpenCustom(s32 menuID, ...);
MenuSprite* menuSpriteBiosGetPtr(u32 id);
MenuSpriteVal* menuSpriteBiosGetValPtr(MenuSprite* sprite);
void menuSubCursorAnimeStart(void);
void windowDrawSprite2(s16 x, s16 y, s16 w, s16 h, u32 color, void* ctx, u16 key, u32 flags, s32 layer);
u32 windowGetKeyRepeat(void);
}
namespace {
static void _controlCursor();
static void diskUsedMarkDisplay(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, int p2);
static u16 getItemIDFromMenuPos(int p0);
static u32 getItemNameMsg(unsigned long p0);
static s32 getNbItemSlot();
static void printItemList(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1);
static u16 selectItem();
}
extern "C++" {
bool deckDataVirtualDB_GetFlagData(u16 id);
void menuPtPlaySe(u32 id);
}
namespace {
u8 Data[0x28];
}

extern "C" {
s32 menuPocketBattleDiskCtrl(void *p0);
s32 menuPocketBattleDiskDrawRollDown(void *p0, void *p1);
s32 menuPocketBattleDiskDrawRollUp(void *p0, void *p1);
s32 menuPocketBattleDiskPageBar(void *p0, s32 p1);
}

s32 menuPocketBattleDiskDrawLineCursor(void *p0, void *p1) {
    MenuItem *temp_r31;

    temp_r31 = menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), (u32) M2C_FIELD(p1, s16 *, 6));
    M2C_FIELD(p1, s16 *, 0x52) = (s16) (M2C_FIELD(temp_r31, s16 *, 8) + getCursorPositionY());
    return 0;
}
}

extern "C" {
struct BallCursorPos {
    f32 x;
    f32 y;
};

s32 menuPocketBattleDiskDrawBallCursor(void *p0, void *p1) {
    BallCursorPos pos = {0.0f, 0.0f};
    s32 color = -1;
    if ((s32) M2C_FIELD(p0, s32 *, 4) == windowGetActiveID()) {
        menuSubCursorAnimeValGet(&pos.x, &color);
    }
    s32 layer = winSpriteGetLayerID((tagWINDOW_WORK*)p0, (tagSPRITE_WORK*)p1);
    windowDrawSpriteCursor(0, getCursorPositionY(), -1, p0, 0xC2, 0, layer, &pos, color);
    winSpriteSetDisp((tagSPRITE_WORK*)p1, 0U);
    return 0;
}
extern "C++" {
static s32 getCursorPositionY() {
    s32 var_r3;

    var_r3 = (s16)(M2C_FIELD(&Data, s16 *, 0xE) * 0x1E);
    if ((u8) M2C_FIELD(&Data, u8 *, 0x14) == 0) {
        var_r3 += (s16) M2C_FIELD(&Data, f32 *, 0x10);
    }
    return var_r3;
}
}

extern "C" {
s32 menuPocketBattleDiskDrawRollDown(void *p0, void *p1) {
    if ((u8) M2C_FIELD(&Data, u8 *, 0x1C) == 0) {
        return 0;
    }
    if ((s32) (M2C_FIELD(&Data, s16 *, 0xC) + 8) < (s32) (M2C_FIELD(&Data, s32 *, 8) + 1)) {
        M2C_FIELD(p1, s8 *, 0x67) = (s8) (255.0f * (1.0f - M2C_FIELD(&Data, f32 *, 0x18)));
    } else {
        M2C_FIELD(p1, s8 *, 0x67) = 0;
    }
    return 0;
}
}

extern "C" {
s32 menuPocketBattleDiskDrawRollUp(void *p0, void *p1) {
    if ((u8) M2C_FIELD(&Data, u8 *, 0x1C) == 0) {
        return 0;
    }
    if ((s16) M2C_FIELD(&Data, s16 *, 0xC) > 0) {
        M2C_FIELD(p1, s8 *, 0x67) = (s8) (255.0f * (1.0f - M2C_FIELD(&Data, f32 *, 0x18)));
    } else {
        M2C_FIELD(p1, s8 *, 0x67) = 0;
    }
    return 0;
}
}

extern "C" {
s32 menuPocketBattleDiskPageBar(void *p0, s32 p1) {
    menuPdaSubScrollBar((tagWINDOW_WORK*)p0, (tagSPRITE_WORK*)p1, M2C_FIELD(p0, s32 *, 4), 0x110, 0xF06422FF, M2C_FIELD(&Data, s32 *, 8) + 1, 8, (s16*)((u8*)&Data + 0xC));
    winSpriteSetDisp((tagSPRITE_WORK*)((tagSPRITE_WORK *) p1), 0U);
    return 0;
}
}

extern "C" {
s32 menuPocketBattleDiskCtrl(void *p0) {
    f32 temp_f1;
    u8 temp_r0;

    temp_r0 = M2C_FIELD(p0, u8 *, 1);
    switch ((s8) temp_r0) {
    case 0:
        if ((s8) M2C_FIELD(p0, u8 *, 2) == 0) {
            winSeqSetMenu(0x3B, 0x60U);
            M2C_FIELD(p0, u8 *, 2) = 1U;
            menuSubCursorAnimeInit();
        }
        break;
    case 2:
        _controlCursor();
        menuPocketToolFloatToZero(*(float*)((u8*)&Data + 0x10), 7.0f);
        f32 kc494 = 0.033333335f;
        temp_f1 = M2C_FIELD(&Data, f32 *, 0x18) + kc494;
        M2C_FIELD(&Data, f32 *, 0x18) = temp_f1;
        if (temp_f1 > 1.0f) {
            M2C_FIELD(&Data, f32 *, 0x18) = 0.0f;
        }
        menuSubCursorAnimeMain();
        break;
    case 3:
        if ((s8) M2C_FIELD(p0, u8 *, 2) == 0) {
            winSeqSetMenu(0x3B, 0x64U);
            M2C_FIELD(p0, u8 *, 2) = 1U;
        }
        break;
    }
    return 0;
}
}

}

extern "C++" {
extern "C" {
extern "C" {
extern "C" {
extern "C" {
extern "C" {
s32 menuPocketBattleDiskPrintItemKind(void *p0, void *p1) {
    s16 width = GSmsgGetRect(0x14D3) >> 16;
    GSmsgPrint2(winSpriteGetLayerID((tagWINDOW_WORK*)p0, (tagSPRITE_WORK*)p1), (M2C_FIELD(p1, s16 *, 0x54) - width) / 2, 0, -1, 0x14D3);
    return 0;
}
extern "C" {
s32 menuPocketBattleDiskPrintItemList(void *p0, void *p1) {
    MenuItem* area = menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), 0x11BU);
    MenuItem* item = menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), (u32) M2C_FIELD(p1, s16 *, 6));
    spriteSetScissor(winSpriteGetLayerID((tagWINDOW_WORK*)p0, (tagSPRITE_WORK*)p1), M2C_FIELD(area, s16 *, 6) - M2C_FIELD(item, s16 *, 6),
                     M2C_FIELD(area, s16 *, 8) - M2C_FIELD(item, s16 *, 8), M2C_FIELD(area, s16 *, 0xA), M2C_FIELD(area, s16 *, 0xC));
    spriteSetEnv(winSpriteGetLayerID((tagWINDOW_WORK*)p0, (tagSPRITE_WORK*)p1));
    printItemList((tagWINDOW_WORK*)p0, (tagSPRITE_WORK*)p1);
    spriteSetOffset(winSpriteGetLayerID((tagWINDOW_WORK*)p0, (tagSPRITE_WORK*)p1), 0, 0);
    spriteClearScissor(winSpriteGetLayerID((tagWINDOW_WORK*)p0, (tagSPRITE_WORK*)p1));
    spriteSetEnv(winSpriteGetLayerID((tagWINDOW_WORK*)p0, (tagSPRITE_WORK*)p1));
    return 0;
}
}

}

}
}
}
}
}
s32 menuPocketBattleDiskCursor(void) {
    return 0x0;
}
extern "C" {
u16 menuPocketBattleDiskMain(s32 p0, s32 p1, s32 p2) {
    u16 temp_r28;

    memset((void*)(&Data), 0, 0x24U);
    M2C_FIELD(&Data, s32 *, 0) = p1;
    M2C_FIELD(&Data, s32 *, 4) = p2;
    M2C_FIELD(&Data, s32 *, 8) = getNbItemSlot();
loop_1:
    M2C_FIELD(&Data, s8 *, 0x1C) = 1;
    temp_r28 = selectItem();
    M2C_FIELD(&Data, s8 *, 0x1C) = 0;
    if (temp_r28 != 0) {
        menuBattleDiskOpenDoc((u8) (temp_r28 - 0x215));
        menuPocketButtonWait();
        menuBattleDiskCloseDoc();
        goto loop_1;
    }
    menuCloseCustom(0x3B, 0, 1);
    return temp_r28;
}
}

namespace {
static void _controlCursor() {
    volatile s32 unkspA;
    s32 sp8;
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r6;
    u32 temp_r3;
    u32 var_r29;

    temp_r3 = windowGetKeyRepeat();
    var_r29 = 0;
    temp_r6 += 1;
    temp_r6 = M2C_FIELD(&Data, s32 *, 8);
    if (M2C_FIELD(&Data, f32 *, 0x10) == 0.0f) {
        if ((u8) M2C_FIELD(&Data, u8 *, 0x1C) == 0) {
            return;
        }
        sp8 = M2C_FIELD(&Data, s32 *, 0xC);
        if ((s32) (temp_r3 & 8) != 0) {
            temp_r0 = temp_r6 - 8;
            if ((s32) ((s32) (temp_r6 + 7) / 8) == 1) {
                M2C_FIELD(&Data, s16 *, 0xE) = (s16) (temp_r6 - 1);
            } else if ((s16) M2C_FIELD(&Data, s32 *, 0xC) == temp_r0) {
                M2C_FIELD(&Data, s16 *, 0xE) = 7;
            } else {
                temp_r3_2 = (s16) M2C_FIELD(&Data, s32 *, 0xC) + 8;
                M2C_FIELD(&Data, s32 *, 0xC) = temp_r3_2;
                if (temp_r3_2 > temp_r0) {
                    M2C_FIELD(&Data, s32 *, 0xC) = temp_r0;
                }
            }
            if ((sp8 != (s16) M2C_FIELD(&Data, s32 *, 0xC)) || (unkspA != (s16) M2C_FIELD(&Data, s16 *, 0xE))) {
                menuPtPlaySe(0x44DU);
            }
        } else if ((s32) (temp_r3 & 4) != 0) {
            if ((s16) M2C_FIELD(&Data, s32 *, 0xC) == 0) {
                M2C_FIELD(&Data, s16 *, 0xE) = 0;
            } else {
                temp_r3_3 = (s16) M2C_FIELD(&Data, s32 *, 0xC) - 8;
                M2C_FIELD(&Data, s32 *, 0xC) = temp_r3_3;
                if (temp_r3_3 < 0) {
                    M2C_FIELD(&Data, s32 *, 0xC) = 0;
                }
            }
            if (((s16) sp8 != (s16) M2C_FIELD(&Data, s32 *, 0xC)) || (unkspA != (s16) M2C_FIELD(&Data, s16 *, 0xE))) {
                menuPtPlaySe(0x44DU);
            }
        } else if ((temp_r3 & 2) != 0) {
            temp_r0_2 = M2C_FIELD(&Data, s16 *, 0xE) + 1;
            M2C_FIELD(&Data, s16 *, 0xE) = temp_r0_2;
            if ((s32) (temp_r0_2 + M2C_FIELD(&Data, s32 *, 0xC)) >= temp_r6) {
                M2C_FIELD(&Data, s16 *, 0xE) = (s16) (temp_r0_2 - 1);
            } else {
                if (temp_r0_2 >= 8) {
                    M2C_FIELD(&Data, s32 *, 0xC) = ((s16) M2C_FIELD(&Data, s32 *, 0xC) + 1);
                    var_r29 = 0x10;
                    M2C_FIELD(&Data, s16 *, 0xE) = (s16) (temp_r0_2 - 1);
                    M2C_FIELD(&Data, s8 *, 0x14) = 1;
                } else {
                    var_r29 = 0x10;
                    M2C_FIELD(&Data, s8 *, 0x14) = 0;
                }
                M2C_FIELD(&Data, f32 *, 0x10) = -(f32)(30.0f);
            }
        }
        if (((s32) (temp_r3 & 1) != 0) && (((s16) M2C_FIELD(&Data, s16 *, 0xE) > 0) || (M2C_FIELD(&Data, s32 *, 0xC) > 0))) {
            M2C_FIELD(&Data, s16 *, 0xE)--;
            if (M2C_FIELD(&Data, s16 *, 0xE) < 0) {
                var_r29 = 0x10;
                M2C_FIELD(&Data, s32 *, 0xC) = (M2C_FIELD(&Data, s32 *, 0xC) - 1);
                M2C_FIELD(&Data, s16 *, 0xE) = 0;
                M2C_FIELD(&Data, s8 *, 0x14) = 1;
            } else {
                var_r29 = 0x10;
                M2C_FIELD(&Data, s8 *, 0x14) = 0;
            }
            M2C_FIELD(&Data, f32 *, 0x10) = 30.0f;
        }
        if (((s16) sp8 != M2C_FIELD(&Data, s32 *, 0xC)) || (unkspA != (s16) M2C_FIELD(&Data, s16 *, 0xE))) {
            menuSubCursorAnimeStart();
        }
        if (var_r29 != 0) {
            menuPtPlaySe(var_r29);
        }
    }
}
}

namespace {
static void printItemList(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1) {
    s32 temp_r22;
    s32 var_r28;
    s32 temp_r27;
    s32 var_r4;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    volatile u16 temp_r3;

    var_r4 = 0;
    var_r25 = 8;
    temp_r27 = M2C_FIELD(&Data, s32 *, 8);
    var_r24 = 0;
    var_r26 = M2C_FIELD(&Data, s16 *, 0xC);
    if ((M2C_FIELD(&Data, f32 *, 0x10) != 0.0f) && ((u8) M2C_FIELD(&Data, u8 *, 0x14) != 0)) {
        if (M2C_FIELD(&Data, f32 *, 0x10) < 0.0f) {
            var_r26 -= 1;
            var_r4 = -1;
        } else {
            var_r25 = 9;
        }
        var_r24 = (s32) M2C_FIELD(&Data, f32 *, 0x10);
    }
    var_r28 = var_r4 * 0x1E;
    var_r23 = var_r4;
    while ((var_r23 < var_r25) && (var_r26 < temp_r27)) {
        if (var_r26 >= 0) {
            temp_r22 = var_r28 - var_r24;
            temp_r3 = getItemIDFromMenuPos((s32) var_r26);
            u32 msg = getItemNameMsg((u32) temp_r3);
            if (msg != 0U) {
                if (deckDataVirtualDB_GetFlagData((u16) (temp_r3 - 0x215)) != 0) {
                    diskUsedMarkDisplay((tagWINDOW_WORK*)(p0), (tagSPRITE_WORK*)(p1), temp_r22);
                }
                GSmsgPrint2(winSpriteGetLayerID((tagWINDOW_WORK*)(p0), (tagSPRITE_WORK*)(p1)), 0, temp_r22, -1U, msg);
            }
        }
        var_r28 += 0x1E;
        var_r23 += 1;
        var_r26 += 1;
    }
    if (var_r23 < var_r25) {
        GSmsgPrint2(winSpriteGetLayerID((tagWINDOW_WORK*)(p0), (tagSPRITE_WORK*)(p1)), 0, (var_r23 * 0x1E) - var_r24, -1U, 0x3A9E);
    }
}
}

namespace {
static void diskUsedMarkDisplay(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, int p2) {
    s32 sp8;
    MenuItem *temp_r31;
    MenuItem *temp_r3;
    MenuSpriteVal *temp_r31_2;
    s32 temp_r30;
    s32 temp_r29;

    temp_r31 = menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), (u32) M2C_FIELD(p1, s16 *, 6));
    temp_r3 = menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), 0x117U);
    temp_r30 = M2C_FIELD(temp_r3, s16 *, 6) - M2C_FIELD(temp_r31, s16 *, 6);
    temp_r29 = M2C_FIELD(temp_r3, s16 *, 8) - M2C_FIELD(temp_r31, s16 *, 8);
    temp_r31_2 = menuSpriteBiosGetValPtr((MenuSprite*)(menuSpriteBiosGetPtr(0xD9U)));
    sp8 = winSpriteGetLayerID((tagWINDOW_WORK*)(p0), (tagSPRITE_WORK*)(p1));
    windowDrawSprite2(temp_r30, (s16) (temp_r29 + p2), M2C_FIELD(temp_r31_2, s16 *, 4), M2C_FIELD(temp_r31_2, s16 *, 6), -1U, (void*)(p0), 0xD9U, 0U, sp8);
}
}

namespace {
static u16 selectItem() {
    if (menuOpenCustom(0x3B, windowGetActiveID(), 0, 0, 1, 0) == -1) {
        return 0;
    }
    M2C_FIELD(&Data, s32 *, 0x20) = M2C_FIELD(&Data, s16 *, 0xC) + M2C_FIELD(&Data, s16 *, 0xE);
    return getItemIDFromMenuPos(M2C_FIELD(&Data, s16 *, 0xC) + M2C_FIELD(&Data, s16 *, 0xE));
}
}

namespace {
static u16 getItemIDFromMenuPos(int pos) {
    u16 count;
    u8* item = (u8*)heroItemGetItemKindToItemAryPtr(M2C_FIELD(&Data, Hero **, 4), 7, &count, 0, 0, 0);
    s32 n = -1;
    for (s32 i = 0; i < count; i++, item += 4) {
        if (itemCheckValid((s32)item) != 0) {
            n++;
            if (n >= pos) {
                return itemBiosGetItemDataId(item);
            }
        }
    }
    return 0;
}
}

namespace {
static s32 getNbItemSlot() {
    u16 count;
    u8* item = (u8*)heroItemGetItemKindToItemAryPtr(M2C_FIELD(&Data, Hero **, 4), 7, &count, 0, 0, 0);
    s32 n = 0;
    for (s32 i = 0; i < count; i++, item += 4) {
        if (itemCheckValid((s32)item) != 0) {
            n++;
        }
    }
    return n;
}
}

namespace {
static u32 getItemNameMsg(unsigned long p0) {
    return itemDataBiosGetName((u8*)(itemDataBiosGetPtr((u16) p0)));
}
}

}
