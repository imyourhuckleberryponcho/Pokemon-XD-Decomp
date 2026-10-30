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
struct Hero;
struct MenuItem;
struct POCKET_COLOGNE_ARG;
struct tagSPRITE_WORK;
struct tagWINDOW_WORK;

extern "C++" {
struct Hero {
    u8 _draft[1];
};
struct MenuItem {
    u8 _draft[1];
};
struct POCKET_COLOGNE_ITEM {
    u16 id;
    u16 pad;
};
struct POCKET_COLOGNE_ARG {
    u32 param;
    POCKET_COLOGNE_ITEM items[4];
    s32 count;
};
struct tagSPRITE_WORK {
    u8 _draft[1];
};
struct tagWINDOW_WORK {
    u8 _draft[1];
};

extern "C" {
u32 GSmsgGetRect(s32);
s32 GSmsgPrint2(s32 layer, s32 x, s32 y, s32 color, u32 msg);
void* heroItemGetItemKindToItemAryPtr(Hero*, u8, u16*, u16*, u8*, u8*);
u16 itemBiosGetNum(u8* p);
u8 itemCheckValid(u32);
u8 itemDataBiosGetKind(u8* p);
u32 itemDataBiosGetName(u8* p);
u8* itemDataBiosGetPtr(u16 index);
u32 itemGetStatus(u32, u32, u32, u32);
void menuClose(s32 menuID);
void menuCloseSync(s32 menuID, s32);
MenuItem* menuItemBiosGetPtr(s32 menuID, u32 index);
s32 menuOpenCustom(s32 menuID, ...);
s32 menuPocketColognCtrl(void *p0);
s32 menuPocketColognCursor(void *p0);
s32 menuPocketColognDrawCursor(void *p0, void *p1);
s32 menuPocketColognDrawItemText(tagWINDOW_WORK* win, tagSPRITE_WORK* sp);
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
s32 windowDrawSpriteCursor(s32, s32, s32, void*, s32, s32, s32, f32*, s32);
s32 windowGetActiveID(void);
u32 windowGetKeyRepeat(void);
extern s32 jtbl_2063;
extern s32 jtbl_2041;
extern s32 init;
extern s32 jtbl_2066;
}
extern "C++" {
static u32 getItemName(unsigned long p0);
static s32 getItemNum(unsigned short p0);
static s32 getLineHeight(tagWINDOW_WORK* p0);
static u32 getStockMax(unsigned short p0);
static void makePocketCologneArg(POCKET_COLOGNE_ARG* p0, unsigned long p1);
}
static f32 ActMenuCursorBlinkTime;

static s32 first_S1990;
static u8 init_S1991;
}

extern "C" {
struct ColognList {
    struct {
        u16 item;
        u16 pad;
    } entry[5];
    s32 count;
};
}

extern "C" {
u16 menuPocketCologne(s32 param) {
    POCKET_COLOGNE_ARG arg;
    s32 sel;
    u16 item;

    if ((s8)init_S1991 == 0) {
        first_S1990 = 1;
        init_S1991 = 1;
    }
    if (first_S1990 != 0) {
        first_S1990 = 0;
    }
    makePocketCologneArg(&arg, param);
    sel = menuOpenCustom(0x32, windowGetActiveID(), 0, 0, 1, 1, &arg);
    menuClose(0x32);
    menuCloseSync(0x32, 1);
    if (sel >= 0 && sel < arg.count) {
        item = arg.items[sel].id;
        if (getItemNum(item) != 0) {
            return item;
        }
        return 0;
    }
    return 0;
}
}

extern "C++" {
static void makePocketCologneArg(POCKET_COLOGNE_ARG* arg, unsigned long param) {
    arg->param = param;
    arg->items[0].id = 0x201;
    arg->items[1].id = 0x202;
    arg->items[2].id = 0x203;
    arg->items[3].id = 0;
    arg->count = 4;
}
}

extern "C" {
s32 menuPocketColognCtrl(void *p0) {
    f32 temp_f1;
    u8 temp_r0;

    temp_r0 = M2C_FIELD(p0, u8 *, 1);
    switch ((s8) temp_r0) {
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
        M2C_FIELD(p0, s16 *, 0x9E) = (s8) var_r0;
    }
    if ((s32) (temp_r3 & 1) != 0) {
        var_r0_2 = M2C_FIELD(p0, s16 *, 0x9E) - 1;
        if (var_r0_2 < 0) {
            var_r0_2 = 0;
        }
        M2C_FIELD(p0, s16 *, 0x9E) = (s8) var_r0_2;
    }
    if (temp_r4 != (s16) M2C_FIELD(p0, s16 *, 0x9E)) {
        menuSubCursorAnimeStart();
    }
    return 0;
}
}

extern "C" {
s32 menuPocketColognDrawItemText(tagWINDOW_WORK* win, tagSPRITE_WORK* sp) {
    s16 id = *(s16*)((u8*)sp + 6);
    ColognList* list = *(ColognList**)((u8*)win + 0x68);
    s32 ids[4] = {0x130, 0x12F, 0x12E, 0x12D};
    s32 i;
    u32 name;
    s16 width;
    s16 base;

    if (id == 0x127) {
        s16 width;
        u32 name;
        s16 base;
        name = getItemName(0x200);
        base = *(s16*)((u8*)menuItemBiosGetPtr(*(s32*)((u8*)win + 4), 0x127) + 0xA);
        width = GSmsgGetRect(name) >> 16;
        GSmsgPrint2(winSpriteGetLayerID(win, sp), (base - width) / 2, 0, -1, name);
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (id == ids[i]) {
            break;
        }
    }
    if (i < 0 || i >= list->count) {
        return 0;
    }
    if (*(u16*)((u8*)list + i * 4 + 4) == 0) {
        name = 0x4295;
    } else {
        name = getItemName(*(u16*)((u8*)list + i * 4 + 4));
    }
    GSmsgPrint2(winSpriteGetLayerID(win, sp), 0, 0, -1, name);
    if (*(u16*)((u8*)list + i * 4 + 4) != 0) {
        base = *(s16*)((u8*)menuItemBiosGetPtr(*(s32*)((u8*)win + 4), 0x130) + 0xA);
        s32 tmp1 = getStockMax(*(u16*)((u8*)list + i * 4 + 4));
        msgctrlSetValue(0x34, tmp1);
        width = (s16)(GSmsgGetRect(0x426F) >> 16);
        width += (s16)(GSmsgGetRect(0x428F) >> 16);
        GSmsgPrint2(winSpriteGetLayerID(win, sp), base - width, 0, -1, 0x428F);
        s32 num = getItemNum(*(u16*)((u8*)list + i * 4 + 4));
        msgctrlSetValue(0x34, num);
        width = GSmsgGetRect(0x426F) >> 16;
        GSmsgPrint2(winSpriteGetLayerID(win, sp), base - width, 0, -1, 0x426F);
    }
    return 0;
}
}

extern "C" {
s32 menuPocketColognDrawCursor(void* win, void* sp) {
    s32 ids[4] = {0x12C, 0x12B, 0x12A, 0x129};
    if (*(s16*)((u8*)sp + 6) == ids[*(s16*)((u8*)win + 0x9E)]) {
        f32 anim[2] = {0.0f, 0.0f};
        s32 color = -1;
        if (*(s32*)((u8*)win + 4) == windowGetActiveID()) {
            menuSubCursorAnimeValGet(anim, &color);
        }
        windowDrawSpriteCursor(0, 0, -1, win, 0xC2, 0, winSpriteGetLayerID((tagWINDOW_WORK*)win, (tagSPRITE_WORK*)sp), anim, color);
    }
    winSpriteSetDisp((tagSPRITE_WORK*)sp, 0);
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
s32 menuPocketColognDrawLineCursor(void *p0, void *p1) {
    MenuItem *temp_r31;

    temp_r31 = menuItemBiosGetPtr(M2C_FIELD(p0, s32 *, 4), (u32) M2C_FIELD(p1, s16 *, 6));
    M2C_FIELD(p1, s16 *, 0x52) = (s16) (M2C_FIELD(temp_r31, s16 *, 8) + (M2C_FIELD(p0, s16 *, 0x9E) * getLineHeight((tagWINDOW_WORK*)((tagWINDOW_WORK *) p0))));
    return 0;
}
}

extern "C++" {
static u32 getItemName(unsigned long item) {
    return itemDataBiosGetName((u8*)itemDataBiosGetPtr((u16)item));
}
}

extern "C++" {
static u32 getStockMax(unsigned short p0) {
    u16 sp8;

    heroItemGetItemKindToItemAryPtr((Hero*)(NULL), itemDataBiosGetKind((u8*)(itemDataBiosGetPtr(p0))), (u16*)(NULL), (u16*)(&sp8), (u8*)(NULL), (u8*)(NULL));
    return sp8;
}
}

extern "C++" {
static s32 getItemNum(unsigned short p0) {
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
