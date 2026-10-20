// Shop menu (Poke Mart, vending machine, coupon exchange, battle disk shop).
// STATUS: 60/72 exact; LAYOUT/CONST/CALLS/DATA OK.
// Needs extra_cflags=["-inline noauto,deferred"] (source is written bottom-to-top).
// Not exact: couponExchangeMain, menuShopDrawListText, _getBattleDiskShopID, menuShopNumDrawBuyNum,
// menuShopCtrl, menuShopOpen, menuShopNumDrawCursor, menuShopDrawPointEmblem, menuShopDrawHaveWaku(Back),
// setDefMenuItem (register allocation / operand order only).
// Skip libc/stdarg.h: the target's va_list is a NAMED struct (__va_list_struct in mangled names).
#define _STDARG_H_
struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
};
typedef __va_list_struct va_list[1];
#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))
extern "C" void* __va_arg(va_list, unsigned char);
#include <dolphin/types.h>
#include <game/shared/menu_work.h>

#pragma peephole off
#pragma pool_strings off

struct Hero;


struct VPC_BOX {
    u8 pad0[0x758];
    s32 f758;
    s32 f75C;
    u8 exchanged;
    u8 pad761[0x764 - 0x761];
};

enum MENU_COUPON_MSG_CODE { COUPON_MSG0 };
enum MENU_SHOP_MSG_CODE { SHOP_MSG0 };

struct SHOP_MENU_ARG {
    int index;
    u16 item;        // 0x04
    u16 pad6;
    u16* goods;      // 0x08
    int count;
    f32* curPos;     // 0x10
    int* isScroll;   // 0x14
    f32* rollUpTime; // 0x18
    u8 mode;         // 0x1C
    u8 flags;        // 0x1D
    u8 pad1E[2];
    VPC_BOX box;     // 0x20
};

struct NUM_MENU_ARG {
    s32 max;    // 0x00
    s32 price;  // 0x04
    int* value;
    s32 coupon; // 0x0C
};

struct SHOP_DATA {
    u8 unk0;
    u8 mode;
    u16 goodsIdx;
};

struct SHOP_SALESMAN {
    u8 se;
    u8 pad[3];
    u32 msg[14];
};

struct SHOP_EXCHANGER {
    u8 se;
    u8 pad[3];
    u32 msg[18];
};

struct SHOP_WORK {
    s32 shop;
    s32 terminate;
};

struct LIST_POS {
    s16 top;
    s16 cursor;
};

struct LIST_POS_ARR {
    s16 v[2];
};

struct MENU_ITEM_POS {
    u8 pad0[6];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
};

extern "C" {
int memcardTaskCall(int, int, int);
void itemInitAry(void*, u16);
void* savedataGetStatus(void*, int);
void* memcpy(void*, const void*, u32);
u32 heroGetStatus(Hero*, u32, u16);
void heroSetStatus(Hero*, u32, u32);
int winMsgOpenWithSE(s8, u32, bool, bool, u8);
int menuSubOpenYesNo(u8, s16, s16, int);
void winMsgClose(bool);
u8 GSgfxVideoGetVsyncRate(void);
f32 GSgfxVideoGetLastRenderTime(void);
void GSthreadSwitch(void);
void heroDecPokecoupon(Hero*, int);
void heroDecPokedoru(Hero*, u32);
void pcboxAddItem(void*, u16, u16);
u16 pcboxGetItemCapacity(void*, u16);
int heroItemCheckAddItemDataId(Hero*, u16);
int heroItemAddItemDataId(Hero*, u16, u16, int);
void* heroItemGetItemKindToItemAryPtr(Hero*, u8, u16*, u16*, u8*, u8*);
u32 itemGetStatus(void*, u32, u32, u32);
u8* itemDataBiosGetPtr(u16);
u32 itemDataBiosGetCoupon(u8*);
u32 itemDataBiosGetPrice(u8*);
u8 itemDataBiosGetKind(u8*);
u32 itemDataBiosGetDoc(u8*);
u32 itemDataBiosGetName(u8*);
u32 itemDataBiosGetWazaMachineNo(u8*);
u16 itemDataBiosGetWazaIDByWazaMachineNo(u8);
void msgctrlSetValue(int, u32);
void menuPtPlaySe__FUl(u32);
int GSmsgGetRect(int);
void GSmsgPrint2(int, int, int, int, int);
void GSmsgPrintRight(int, int, int, int, int, u32, u32);
int menuPocketInputNumber(tagWINDOW_WORK*, int, int, u16, int, int, int);
u16 windowGetKeyRepeat(void);
u16 windowGetKeyTrg(void);
void winSeqSetMenu(int, u32);
int windowGetActiveID(void);
int menuOpenCustom(int, ...);
void menuClose(int);
void menuCloseSync(int, int);
void menuCloseCustom(int, int, int);
MENU_ITEM_POS* menuItemBiosGetPtr(int, u32);
void spriteSetScissor(int, int, int, int, int);
void spriteClearScissor(int);
void spriteSetEnv(int);
int winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void windowDrawSpriteCursor(int, s16, int, tagWINDOW_WORK*, int, int, int, f32*, int);
void menuSubCursorAnimeValGet(f32*, int*);
bool winSeqCheckMove(int);
void menuSubCursorAnimeStart(void);
void menuButtonNormal(tagWINDOW_WORK*);
void menuSubCursorAnimeInit(void);
void menuSubCursorAnimeMain(void);
void* GSmemAlloc(u32);
void GSmemFree(void*);
u8 GSsndPlay(u32, int, u32);
int menuSubOpenSelect(u8, s32*, int, int, int, int);
void menuPocket2Call(int, int, void*);
u8 GSfloorPush(u32);
u8 GSfloorPop(void);
void floorSetFadeScript(u32, u32);
void floorWaitForChange(void);
void mailMainReceiveTerminate(void);
void menuCreateOffScreen(f32, f32);
void menuReleaseOffScreen(f32);
bool savedataGetBattleDiskSellOut(int);
void savedataSetBattleDiskSellOut(int);
void winSpriteSetDisp(tagSPRITE_WORK*, bool);
u8 heroItemCheckHaveItemDataId(Hero*, u32);
}

bool deckDataVirtualDB_GetFlagData(u16);
u8 heroItemCheckHaveItemDataId(Hero*, u32);
extern SHOP_DATA* shopData;
extern u16* shopGoods;
extern SHOP_EXCHANGER* shopExchanger;
extern SHOP_SALESMAN* shopSalesman;

static inline SHOP_MENU_ARG* shopArg(tagWINDOW_WORK* w) { return (SHOP_MENU_ARG*)w->params[0]; }

struct NUM_WIN_ITEM {
    s32 spriteID;
    s32 cursorID;
};
struct DEF_MENU_ITEM {
    s32 id;
    s16 y;
    s16 pad;
};
extern "C" {
s32 shopmode[7] = {0xC5E2, 0xC5E4, 0xC5E9, 0xC5E9, 0xC5E9, 0xC5F1, 0xC5E3};
s32 _shopDataBattleDiskTbl[3] = {0x10, 0x11, 0x12};
}
static const NUM_WIN_ITEM NumWinItem[2] = {{0x94, 0x92}, {0x1A6, 0x93}};
static DEF_MENU_ITEM DefMenuItem = {0x64, 0};
static SHOP_WORK ShopWork;
static f32 CurPos;
static int IsScroll;
static f32 RollUpTime;
static u32 ExplanationMsgID;
static int NumValue;
static void* PPcboxBackup;
static u32 CouponBackup;

extern "C" {
u32 menuShopGetCouponMsgID(u8* se, int shop, MENU_COUPON_MSG_CODE code, int arg, ...);
u32 menuShopGetMsgID(u8* se, int shop, MENU_SHOP_MSG_CODE code, int arg, ...);
int menuShopNumDrawPriceText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopNumDrawBuyNum(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopNumDrawCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopNumCursor(tagWINDOW_WORK* w);
int menuShopNumCtrl(tagWINDOW_WORK* w);
int menuShopDrawTitleText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawPointEmblem(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawMoneyText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawMoneyWaku(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawHaveWakuBack(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawHaveWaku(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawHaveText2(tagWINDOW_WORK* w);
int menuShopDrawHaveText1(tagWINDOW_WORK* w);
int menuShopDrawExpText(tagWINDOW_WORK* w);
int menuShopDrawRollDown(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawRollUp(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawListText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawBallCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopDrawLineCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
int menuShopCursor(tagWINDOW_WORK* w);
int menuShopButton(tagWINDOW_WORK* w);
int menuShopCtrl(tagWINDOW_WORK* w);
void menuShopMain(void);
void menuShopOpen(int shop);
}
static int memCardSave(VPC_BOX* box);
static void memCardDecCouponAddItem(int coupon, u16 id, int n, VPC_BOX* box);
static int memCardConnect(VPC_BOX* box);
static bool checkExchangeVpc(VPC_BOX* box);
static bool writeBackPcBox(int shop, u8 kind, VPC_BOX* box);
static void waitTime(f32 seconds);
static void decCouponAddItem(int coupon, u16 id, int n, u8 kind, VPC_BOX* box);
static int checkAddItem(u16 id, u8 kind);
static int getMinPoint(int shop);
static u16* getGoodsList(int shop, int* count);
static u32 getCouponMsgID(u8* se, int shop, MENU_COUPON_MSG_CODE code, int arg, va_list args);
static u32 getMsgID(u8* se, int shop, MENU_SHOP_MSG_CODE code, int arg, va_list args);
static u32 _msgIdWazaMachineChange(u16 id, u32 msg);
static void openCouponMsgWin(int shop, MENU_COUPON_MSG_CODE code, int arg, ...);
static void openMsgWin(int shop, MENU_SHOP_MSG_CODE code, int arg, ...);
static int inputBuyNum(int initial, int max, int price, int coupon);
static void addItem(u16 id, int n);
static int getCouponPoint(u8 kind);
static int getMoney(void);
static int getItemCouponPoint(u16 id);
static int getItemPrice(u16 id);
static int getNbHaveItem(u16 id);
static void setExplanationMsgID(u32 id);
static u32 getItemExplanationMsg(u16 id);
static u32 getItemNameMsg(u16 id);
static int getNbItem(SHOP_MENU_ARG* arg);
static u16 getItem(SHOP_MENU_ARG* arg, int index);
static u16 selectItem(int shop, u8 mode, u8 flags, SHOP_MENU_ARG* arg);
static void setDefMenuItem(void);
static int getExchangeMax(u16 id, u8 kind);
static int getBuyMax(u16 id);
static void couponExplanationMain(int shop, u8 kind);
static void couponListMain(int shop, u8 kind);
static void couponExchangeMain(int shop, u8 kind);
static int selectExchangeMode(void);
static void couponProc(int shop, u8 kind);
static void vendingMachineProc(int shop, u8 kind);
static void shopBuyMain(int shop, u8 kind);
static int selectDealMode(void);
static void shopProc(int shop, u8 kind);
static int _getIsBattleDiskShopAllSelWithAllSellOutYet(void);
static int _getBattleDiskShopID(void);
static void _setBattleDiskSellOut(int index);
static bool _getIsBattleDiskSellOut(int index);
static bool _isBattleDiskShop(void);
static int _getBattleDiskShopLevel(void);

static int _getBattleDiskShopLevel(void) {
    switch (ShopWork.shop) {
    case 16:
        return 0;
    case 17:
        return 1;
    case 18:
        return 2;
    default:
        return -1;
    }
}
static bool _isBattleDiskShop(void) {
    return _getBattleDiskShopLevel() != -1;
}
static bool _getIsBattleDiskSellOut(int index) {
    int level = _getBattleDiskShopLevel();
    if (level == -1) {
        return false;
    }
    return savedataGetBattleDiskSellOut(index + level * 3);
}
static void _setBattleDiskSellOut(int index) {
    int level = _getBattleDiskShopLevel();
    if (level != -1) {
        savedataSetBattleDiskSellOut(index + level * 3);
    }
}
static int _getBattleDiskShopID(void) {
    u16 flags[11];
    int count;
    u32 i;
    u16* list;
    for (i = 0; i < 3; i++) {
        list = getGoodsList(_shopDataBattleDiskTbl[i], &count);
        flags[i * 3] = list[0] - 0x215;
        flags[i * 3 + 1] = list[1] - 0x215;
        flags[i * 3 + 2] = list[2] - 0x215;
    }
    if (!deckDataVirtualDB_GetFlagData(flags[0]) || !deckDataVirtualDB_GetFlagData(flags[1]) || !deckDataVirtualDB_GetFlagData(flags[2])) {
        return 0x10;
    }
    if (!deckDataVirtualDB_GetFlagData(flags[3]) || !deckDataVirtualDB_GetFlagData(flags[4]) || !deckDataVirtualDB_GetFlagData(flags[5])) {
        return 0x11;
    }
    return 0x12;
}
static int _getIsBattleDiskShopAllSelWithAllSellOutYet(void) {
    int level = _getBattleDiskShopLevel();
    int base;
    int i;
    if (level == 0 || level == 1) {
        base = level * 3;
        for (i = 0; i < 3; base++, i++) {
            if (!savedataGetBattleDiskSellOut(base)) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
extern "C" {
void menuShopOpen(int shop) {
    mailMainReceiveTerminate();
    menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    ShopWork.shop = shop;
    ShopWork.terminate = 1;
    GSfloorPush(0x3A4);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(20.0f / GSgfxVideoGetVsyncRate());
}
}
extern "C" {
void menuShopMain(void) {
    u8 mode;
    if (ShopWork.shop == 0x10) {
        ShopWork.shop = _getBattleDiskShopID();
    }
    mode = shopData[ShopWork.shop].mode;
    switch (mode) {
    case 0:
        shopProc(ShopWork.shop, mode);
        break;
    case 1:
        vendingMachineProc(ShopWork.shop, mode);
        break;
    case 5:
        shopProc(ShopWork.shop, mode);
        break;
    case 6:
        shopProc(ShopWork.shop, mode);
        break;
    default:
        couponProc(ShopWork.shop, mode);
        break;
    }
    if (ShopWork.terminate != 0) {
        GSfloorPop();
        floorSetFadeScript(0, 0);
    }
}
}
static void shopProc(int shop, u8 kind) {
    u8 se;
    int mode;
    mode = menuShopGetMsgID(&se, shop, (MENU_SHOP_MSG_CODE)0, 0x4B, getMoney(), -1);
    msgctrlSetValue(0x59, 0x1772);
    winMsgOpenWithSE(2, mode, 1, 0, se);
    while ((mode = selectDealMode()) != 2) {
        winMsgClose(1);
        switch (mode) {
        case 0:
            shopBuyMain(shop, kind);
            break;
        case 1:
            menuPocket2Call(3, shop, 0);
            break;
        }
        winMsgOpenWithSE(2, menuShopGetMsgID(&se, shop, (MENU_SHOP_MSG_CODE)1, -1), 1, 0, se);
    }
    openMsgWin(shop, (MENU_SHOP_MSG_CODE)2, -1);
}
static int selectDealMode(void) {
    static s32 msgIDTbl[3] = {0x3AB3, 0x3AB4, 0x3AB5};
    int r = menuSubOpenSelect(0, msgIDTbl, 3, 0x46, 0x3C, 0);
    if (r == -1 || r == 2) {
        return 2;
    }
    return r != 0;
}
static void shopBuyMain(int shop, u8 kind) {
    SHOP_MENU_ARG arg;
    u8 se;
    u16 item;
    int max;
    int num;
    int price;
    int total;
    s8 answer;
    u8* data;
    if (_getIsBattleDiskShopAllSelWithAllSellOutYet()) {
        winMsgOpenWithSE(2, 0xC5EA, 1, 0, shopSalesman[shopData[shop].unk0].se);
        winMsgClose(1);
    }
    while (true) {
        item = selectItem(shop, kind, 0, &arg);
        if (item == 0) {
            break;
        }
        data = itemDataBiosGetPtr(item);
        if (data == 0) {
            continue;
        }
        if (itemDataBiosGetKind(data) == 6 && !heroItemCheckHaveItemDataId(0, 0x200)) {
            openMsgWin(shop, (MENU_SHOP_MSG_CODE)8, -1);
            continue;
        }
        max = getBuyMax(item);
        if (max <= 0) {
            openMsgWin(shop, (MENU_SHOP_MSG_CODE)5, -1);
            continue;
        }
        price = getItemPrice(item);
        if (_isBattleDiskShop()) {
            num = 1;
        } else {
            setExplanationMsgID(menuShopGetMsgID(&se, shop, (MENU_SHOP_MSG_CODE)0xC, 0x2D, item, -1));
            num = inputBuyNum(1, max, price, 0);
            if (num < 0) {
                continue;
            }
        }
        total = num * price;
        winMsgOpenWithSE(2, menuShopGetMsgID(&se, shop, (MENU_SHOP_MSG_CODE)3, 0x2D, item, 0x2F, num, 0x4B, total, -1), 1, 0, se);
        answer = menuSubOpenYesNo(0, -1, -1, 0);
        winMsgClose(1);
        if (answer == 1 || answer == -1) {
            continue;
        }
        if (heroItemCheckAddItemDataId(0, item) < num) {
            openMsgWin(shop, (MENU_SHOP_MSG_CODE)6, -1);
            continue;
        }
        GSsndPlay(0x1A, 0, 0);
        heroDecPokedoru(0, total);
        addItem(item, num);
        _setBattleDiskSellOut(arg.index);
        openMsgWin(shop, (MENU_SHOP_MSG_CODE)4, -1);
        if (item == 4 && num >= 10 && heroItemCheckAddItemDataId(0, 0xC) >= 1) {
            openMsgWin(shop, (MENU_SHOP_MSG_CODE)7, -1);
            addItem(0xC, 1);
        }
    }
    menuCloseCustom(0x3C, 0, 1);
}
static void vendingMachineProc(int shop, u8 kind) {
    SHOP_MENU_ARG arg;
    u16 item;
    int price;
    int money;
    while (true) {
        menuCloseCustom(0x3C, 0, 1);
        money = getMoney();
        openMsgWin(shop, (MENU_SHOP_MSG_CODE)0, 0x4B, money, -1);
        waitTime(0.5f);
        item = selectItem(shop, kind, 0, &arg);
        if (item == 0) {
            openMsgWin(shop, (MENU_SHOP_MSG_CODE)2, -1);
            break;
        }
        price = getItemPrice(item);
        if (getBuyMax(item) <= 0) {
            openMsgWin(shop, (MENU_SHOP_MSG_CODE)5, -1);
            break;
        }
        if (heroItemCheckAddItemDataId(0, item) < 1) {
            openMsgWin(shop, (MENU_SHOP_MSG_CODE)6, -1);
            break;
        }
        GSsndPlay(0x1A, 0, 0);
        heroDecPokedoru(0, price);
        addItem(item, 1);
        openMsgWin(shop, (MENU_SHOP_MSG_CODE)4, 0x2D, item, -1);
    }
    menuCloseCustom(0x3C, 0, 1);
}
static void couponProc(int shop, u8 kind) {
    u8 se;
    int mode;
    int done = 0;
    PPcboxBackup = GSmemAlloc(0xBC50);
    msgctrlSetValue(0x59, 0x1772);
    winMsgOpenWithSE(2, menuShopGetCouponMsgID(&se, shop, (MENU_COUPON_MSG_CODE)0, -1), 1, 0, se);
    while ((mode = selectExchangeMode()) != 3) {
        winMsgClose(1);
        switch (mode) {
        case 0:
            couponExchangeMain(shop, kind);
            break;
        case 1:
            couponListMain(shop, kind);
            break;
        case 2:
            couponExplanationMain(shop, kind);
            break;
        case 3:
            done = 1;
            break;
        }
        if (done != 0) {
            break;
        }
        winMsgOpenWithSE(2, menuShopGetCouponMsgID(&se, shop, (MENU_COUPON_MSG_CODE)1, -1), 1, 0, se);
    }
    if (kind != 2) {
        openCouponMsgWin(shop, (MENU_COUPON_MSG_CODE)2, -1);
    } else {
        winMsgClose(1);
    }
    if (PPcboxBackup != 0) {
        GSmemFree(PPcboxBackup);
        PPcboxBackup = 0;
    }
}
static int selectExchangeMode(void) {
    static s32 msgIDTbl[4] = {0x3AB9, 0x3ABA, 0x3ABB, 0x3ABC};
    int r = menuSubOpenSelect(0, msgIDTbl, 4, 0x46, 0x3C, 0);
    switch (r) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    default:
        return 3;
    }
}
static void couponExchangeMain(int shop, u8 kind) {
    SHOP_MENU_ARG arg;
    u8 se;
    int total;
    int price;
    int ok;
    int num;
    s8 answer;
    u16 item;
    int done = 0;
    int max;
    switch (kind) {
    case 2:
        ok = memCardConnect(&arg.box);
        break;
    default:
        ok = 1;
        break;
    }
    if (ok) {
        if (kind == 4) {
            int minPoint = getMinPoint(shop);
            if (getCouponPoint(kind) < minPoint) {
                openCouponMsgWin(shop, (MENU_COUPON_MSG_CODE)4, -1);
                return;
            }
        }
        while (done == 0) {
            while (true) {
                item = selectItem(shop, kind, 0, &arg);
                if (item == 0) {
                    break;
                }
                max = getExchangeMax(item, kind);
                if (max <= 0) {
                    openCouponMsgWin(shop, (MENU_COUPON_MSG_CODE)8, -1);
                    continue;
                }
                price = getItemCouponPoint(item);
                setExplanationMsgID(menuShopGetCouponMsgID(&se, shop, (MENU_COUPON_MSG_CODE)0xC, 0x2D, item, -1));
                num = inputBuyNum(1, max, price, 1);
                if (num < 0) {
                    continue;
                }
                total = num * price;
                winMsgOpenWithSE(2, menuShopGetCouponMsgID(&se, shop, (MENU_COUPON_MSG_CODE)5, 0x2D, item, 0x2F, num, 0x4B, total, -1), 1, 0, se);
                answer = menuSubOpenYesNo(0, -1, -1, 0);
                winMsgClose(1);
                if (answer == 1 || answer == -1) {
                    continue;
                }
                if (checkAddItem(item, kind) < num) {
                    openCouponMsgWin(shop, (MENU_COUPON_MSG_CODE)9, -1);
                    continue;
                }
                openCouponMsgWin(shop, (MENU_COUPON_MSG_CODE)6, -1);
                decCouponAddItem(total, item, num, kind, &arg.box);
                GSsndPlay(0x1B, 0, 0);
                if (kind != 4) {
                    continue;
                }
                winMsgOpenWithSE(2, menuShopGetCouponMsgID(&se, shop, (MENU_COUPON_MSG_CODE)7, -1), 1, 0, se);
                answer = menuSubOpenYesNo(0, -1, -1, 0);
                winMsgClose(1);
                if (answer == -1 || answer == 1) {
                    break;
                }
            }
            if (kind == 2) {
                done = writeBackPcBox(shop, kind, &arg.box);
            } else {
                done = 1;
            }
        }
        menuCloseCustom(0x3C, 0, 1);
    }
}
static void couponListMain(int shop, u8 kind) {
    SHOP_MENU_ARG arg;
    if (kind != 2) {
        openCouponMsgWin(shop, (MENU_COUPON_MSG_CODE)0xA, -1);
    }
    selectItem(shop, kind, 1, &arg);
    menuCloseCustom(0x3C, 0, 1);
}
static void couponExplanationMain(int shop, u8 kind) {
    openCouponMsgWin(shop, (MENU_COUPON_MSG_CODE)0xB, -1);
}
static int getBuyMax(u16 id) {
    int price = getItemPrice(id);
    int n;
    if (price > 0) {
        n = getMoney() / price;
        if (n > 99) {
            n = 99;
        }
    } else {
        n = 99;
    }
    return n;
}
static int getExchangeMax(u16 id, u8 kind) {
    int point = getItemCouponPoint(id);
    int n;
    if (point > 0) {
        n = getCouponPoint(kind) / point;
        if (n > 99) {
            n = 99;
        }
    } else {
        n = 99;
    }
    return n;
}
static void setDefMenuItem(void) {
    DEF_MENU_ITEM* item = &DefMenuItem;
    item->y = menuItemBiosGetPtr(0x3C, item->id)->y;
}
static u16 selectItem(int shop, u8 mode, u8 flags, SHOP_MENU_ARG* arg) {
    static int first = 1;
    if (first) {
        setDefMenuItem();
        first = 0;
    }
    arg->item = 0;
    arg->goods = getGoodsList(shop, &arg->count);
    arg->curPos = &CurPos;
    arg->isScroll = &IsScroll;
    arg->rollUpTime = &RollUpTime;
    arg->mode = mode;
    arg->flags = flags;
    if (menuOpenCustom(0x3C, windowGetActiveID(), 0, 0, 1, 1, arg) == -1) {
        return 0;
    }
    return arg->item;
}
extern "C" {
int menuShopCtrl(tagWINDOW_WORK* w) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    f32 v;
    f32 n;
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(0x3C, 0x78);
            *arg->curPos = 0.0f;
            *arg->isScroll = 0;
            *arg->rollUpTime = 0.0f;
            w->seqSet = 1;
            menuSubCursorAnimeInit();
        }
        break;
    case 2:
        v = *arg->curPos;
        if (v > 0.0f) {
            n = v - 7.0f;
            *arg->curPos = n;
            if (n < 0.0f) {
                *arg->curPos = 0.0f;
            }
        }
        v = *arg->curPos;
        if (v < 0.0f) {
            n = v;
            n += 7.0f;
            *arg->curPos = n;
            if (n > 0.0f) {
                *arg->curPos = 0.0f;
            }
        }
        *arg->rollUpTime += 0.06666667f;
        if (*arg->rollUpTime > 1.0f) {
            *arg->rollUpTime = 0.0f;
        }
        menuSubCursorAnimeMain();
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(0x3C, 0x7C);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}
}
extern "C" {
int menuShopButton(tagWINDOW_WORK* w) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    u16 trg = windowGetKeyTrg();
    int index = w->top + w->cursor;
    u16 item;
    if (!winSeqCheckMove(w->menuID)) {
        if (_getIsBattleDiskSellOut(index)) {
            if ((trg & 0x20) != 0) {
                menuButtonNormal(w);
            }
        } else {
            item = 0;
            if ((trg & 0x10) != 0) {
                item = getItem(arg, w->top + w->cursor);
                if ((arg->flags & 1) != 0 && item != 0) {
                    return 0;
                }
            }
            if (item != 0) {
                arg->index = w->top + w->cursor;
                arg->item = item;
            }
            menuButtonNormal(w);
        }
    }
    return 0;
}
}
extern "C" {
int menuShopCursor(tagWINDOW_WORK* w) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    u16 repeat = windowGetKeyRepeat();
    LIST_POS_ARR old;
    int limit;
    u32 msg;
    u16 item;
    s16 c;
    windowGetKeyTrg();
    if (*arg->curPos != 0.0f) {
        return 0;
    }
    if (winSeqCheckMove(w->menuID)) {
        return 0;
    }
    old = *(LIST_POS_ARR*)&w->top;
    limit = getNbItem(arg) + 1;
    if ((repeat & 2) != 0) {
        w->cursor++;
        if (w->cursor + w->top >= limit) {
            w->cursor--;
        } else {
            if (w->cursor >= 10) {
                w->top++;
                w->cursor--;
                *arg->isScroll = 1;
            } else {
                *arg->isScroll = 0;
            }
            *arg->curPos = -30.0f;
        }
    }
    if ((repeat & 1) != 0 && (w->cursor > 0 || w->top > 0)) {
        if (--w->cursor < 0) {
            w->cursor = 0;
            w->top--;
            *arg->isScroll = 1;
        } else {
            *arg->isScroll = 0;
        }
        *arg->curPos = 30.0f;
    }
    if (old.v[1] != w->cursor || old.v[0] != w->top) {
        menuSubCursorAnimeStart();
    }
    item = getItem(arg, w->top + w->cursor);
    if (item != 0) {
        msg = getItemExplanationMsg(item);
    } else if (arg->mode == 0 || arg->mode == 1 || arg->mode == 5 || arg->mode == 6) {
        msg = 0x3AAF;
    } else if ((arg->flags & 1) != 0) {
        msg = 0x3ABD;
    } else {
        msg = 0x3AB2;
    }
    setExplanationMsgID(msg);
    return 0;
}
}
extern "C" {
int menuShopDrawLineCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    LIST_POS pos = *(LIST_POS*)&w->top;
    int y = pos.cursor * 30;
    if (*arg->isScroll == 0) {
        y += (int)*arg->curPos;
    }
    s16 base = menuItemBiosGetPtr(w->menuID, sp->id)->y;
    sp->y = base + y;
    return 0;
}
}
extern "C" {
int menuShopDrawBallCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    LIST_POS pos = *(LIST_POS*)&w->top;
    int y = pos.cursor * 30;
    if (*arg->isScroll == 0) {
        y = (int)((f32)y + *arg->curPos);
    }
    f32 anim[2] = {0.0f, 0.0f};
    int color = -1;
    if (w->menuID == windowGetActiveID()) {
        menuSubCursorAnimeValGet(anim, &color);
    }
    windowDrawSpriteCursor(0, y, -1, w, 0xC2, 0, winSpriteGetLayerID(w, sp), anim, color);
    winSpriteSetDisp(sp, false);
    return 0;
}
}
extern "C" {
int menuShopDrawListText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int last;
    int listY;
    int count;
    int row;
    s32 priceX;
    SHOP_MENU_ARG* arg;
    int scroll;
    int idx;
    int y;
    int first;
    u16 id;
    u32 nameMsg;
    u32 nameW;
    MENU_ITEM_POS* base;
    MENU_ITEM_POS* item;
    arg = (SHOP_MENU_ARG*)w->params[0];
    first = 0;
    last = 10;
    scroll = 0;
    base = menuItemBiosGetPtr(w->menuID, 0x66);
    item = menuItemBiosGetPtr(w->menuID, sp->id);
    spriteSetScissor(w->layer, base->x - item->x, base->y - item->y, base->w, base->h);
    count = getNbItem(arg);
    idx = w->top;
    msgctrlSetValue(0x50, 99999);
    nameW = (u32)GSmsgGetRect(0x434E) >> 16;
    priceX = sp->w - nameW - ((u32)GSmsgGetRect(0x42AF) >> 16);
    if (*arg->curPos != 0.0f && *arg->isScroll != 0) {
        if (*arg->curPos < 0.0f) {
            idx--;
            first = -1;
        } else {
            last = 11;
        }
        scroll = (int)*arg->curPos;
    }
    listY = first * 30;
    for (row = first; row < last && idx < count; row++, idx++, listY += 30) {
        if (idx >= 0) {
            y = listY - scroll;
            id = getItem(arg, idx);
            nameMsg = getItemNameMsg(id);
            if (nameMsg != 0) {
                GSmsgPrint2(w->layer, 0, y, -1, nameMsg);
            }
            if (arg->mode == 0 || arg->mode == 1 || arg->mode == 5 || arg->mode == 6) {
                if (_getIsBattleDiskSellOut(row)) {
                    GSmsgPrint2(w->layer, priceX, y, -1, 0xC5EB);
                } else {
                    GSmsgPrint2(w->layer, priceX, y, -1, 0x42AF);
                    s32 tmp1 = getItemPrice(id);
                    msgctrlSetValue(0x50, tmp1);
                    GSmsgPrint2(w->layer, sp->w - ((u32)GSmsgGetRect(0x434E) >> 16), y, -1, 0x434E);
                }
            } else {
                msgctrlSetValue(0x50, getItemCouponPoint(id));
                GSmsgPrint2(w->layer, sp->w - ((u32)GSmsgGetRect(0x4359) >> 16), y, -1, 0x4359);
            }
        }
    }
    if (row < last) {
        int msg;
        if ((arg->flags & 1) != 0) {
            msg = 0x3ABE;
        } else {
            msg = 0x3AAE;
        }
        if (arg->mode == 1) {
            msg = 0x3C3F;
        }
        GSmsgPrint2(w->layer, 0, row * 30 - scroll, -1, msg);
    }
    spriteClearScissor(w->layer);
    spriteSetEnv(w->layer);
    return 0;
}
}
extern "C" {
int menuShopDrawRollUp(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    if (w->top > 0 && arg->item == 0) {
        sp->alpha = 255.0f * (1.0f - RollUpTime);
    } else {
        sp->alpha = 0;
    }
    return 0;
}
}
extern "C" {
int menuShopDrawRollDown(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    SHOP_MENU_ARG* arg;
    int bottom = w->top + 10;
    arg = (SHOP_MENU_ARG*)w->params[0];
    if (bottom < getNbItem(arg) + 1 && arg->item == 0) {
        sp->alpha = 255.0f * (1.0f - RollUpTime);
    } else {
        sp->alpha = 0;
    }
    return 0;
}
}
extern "C" {
int menuShopDrawExpText(tagWINDOW_WORK* w) {
    GSmsgPrint2(w->layer, 0, 0, -1, ExplanationMsgID);
    return 0;
}
}
extern "C" {
int menuShopDrawHaveText1(tagWINDOW_WORK* w) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    if (arg->mode == 0 || arg->mode == 1 || arg->mode == 4 || arg->mode == 6) {
        u16 item = getItem(arg, w->cursor + w->top);
        if (item != 0) {
            msgctrlSetValue(0x2D, item);
            GSmsgPrint2(w->layer, 0, 0, -1, 0x3AB0);
        }
    }
    return 0;
}
}
extern "C" {
int menuShopDrawHaveText2(tagWINDOW_WORK* w) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    if (arg->mode == 0 || arg->mode == 1 || arg->mode == 4 || arg->mode == 6) {
        u16 item = getItem(arg, w->cursor + w->top);
        if (item != 0) {
            int n = getNbHaveItem(item);
            msgctrlSetValue(0x34, n);
            msgctrlSetValue(0x2D, item);
            GSmsgPrint2(w->layer, 0, 0, -1, 0x3AB1);
        }
    }
    return 0;
}
}
extern "C" {
int menuShopDrawHaveWaku(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    winSpriteSetDisp(sp, arg->mode == 0 || arg->mode == 1 || arg->mode == 4 || arg->mode == 6);
    return 0;
}
}
extern "C" {
int menuShopDrawHaveWakuBack(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    winSpriteSetDisp(sp, arg->mode == 0 || arg->mode == 1 || arg->mode == 4 || arg->mode == 6);
    return 0;
}
}
extern "C" {
int menuShopDrawMoneyWaku(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    winSpriteSetDisp(sp, (arg->flags & 1) == 0);
    return 0;
}
}
extern "C" {
int menuShopDrawMoneyText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    if ((arg->flags & 1) != 0) {
        sp->alpha = 0;
        return 0;
    }
    if (arg->mode == 0 || arg->mode == 1 || arg->mode == 5 || arg->mode == 6) {
        int money = getMoney();
        msgctrlSetValue(0x50, money);
    } else {
        int point = getCouponPoint(arg->mode);
        msgctrlSetValue(0x50, point);
    }
    GSmsgPrint2(w->layer, sp->w - (s16)((u32)GSmsgGetRect(0x434E) >> 16), 0, -1, 0x434E);
    return 0;
}
}
extern "C" {
int menuShopDrawPointEmblem(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    bool show = false;
    SHOP_MENU_ARG* arg = (SHOP_MENU_ARG*)w->params[0];
    if (sp->id == 0x6F && (arg->flags & 1) == 0 && (arg->mode == 2 || arg->mode == 3 || arg->mode == 4)) {
        show = true;
    }
    winSpriteSetDisp(sp, show);
    return 0;
}
}
extern "C" {
int menuShopDrawTitleText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int msg = shopmode[shopData[ShopWork.shop].mode];
    int x = sp->w - (s16)((u32)GSmsgGetRect(msg) >> 16);
    GSmsgPrint2(w->layer, x / 2, 0, -1, msg);
    return 0;
}
}
static u16 getItem(SHOP_MENU_ARG* arg, int index) {
    if (index < 0 || index >= getNbItem(arg)) {
        return 0;
    }
    return arg->goods[index];
}
static int getNbItem(SHOP_MENU_ARG* arg) {
    return arg->count;
}
static u32 getItemNameMsg(u16 id) {
    return itemDataBiosGetName(itemDataBiosGetPtr(id));
}
static u32 getItemExplanationMsg(u16 id) {
    return itemDataBiosGetDoc(itemDataBiosGetPtr(id));
}
static void setExplanationMsgID(u32 id) {
    ExplanationMsgID = id;
}
static int getNbHaveItem(u16 id) {
    u16 count;
    u32* ary;
    int i;
    int total = 0;
    if (id == 0) {
        return 0;
    }
    ary = (u32*)heroItemGetItemKindToItemAryPtr(0, itemDataBiosGetKind(itemDataBiosGetPtr(id)), &count, 0, 0, 0);
    for (i = 0; i < count; i++, ary++) {
        u16 status = itemGetStatus(ary, 0, 0x1B, 0);
        if (status == id) {
            total += itemGetStatus(ary, 0, 0x1C, 0);
        }
    }
    return total;
}
static int getItemPrice(u16 id) {
    u16 price = itemDataBiosGetPrice(itemDataBiosGetPtr(id));
    return price;
}
static int getItemCouponPoint(u16 id) {
    u16 point = itemDataBiosGetCoupon(itemDataBiosGetPtr(id));
    return point;
}
static int getMoney(void) {
    return heroGetStatus(0, 0xC, 0);
}
static int getCouponPoint(u8 kind) {
    switch (kind) {
    case 2:
        return heroGetStatus(0, 0xD, 0);
    default:
        return heroGetStatus(0, 0xD, 0);
    }
}
static void addItem(u16 id, int n) {
    heroItemAddItemDataId(0, id, n, -1);
}
static int inputBuyNum(int initial, int max, int price, int coupon) {
    NUM_MENU_ARG arg;
    int one;
    int result;
    if (max < 0) {
        return 0;
    }
    arg.max = max;
    arg.price = price;
    NumValue = initial;
    arg.value = &NumValue;
    arg.coupon = coupon;
    one = 1;
    result = menuOpenCustom(0x3D, windowGetActiveID(), &one, 0, 1, 1, &arg);
    menuClose(0x3D);
    menuCloseSync(0x3D, 1);
    if (result == -1 || NumValue == 0) {
        return -1;
    }
    return NumValue;
}
extern "C" {
int menuShopNumCtrl(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(0x3D, 0x70);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(0x3D, 0x74);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}
}
extern "C" {
int menuShopNumCursor(tagWINDOW_WORK* w) {
    NUM_MENU_ARG* arg = (NUM_MENU_ARG*)w->params[0];
    *arg->value = menuPocketInputNumber(w, *arg->value, arg->max, windowGetKeyRepeat(), 2, 0x10, 0x44D);
    return 0;
}
}
extern "C" {
int menuShopNumDrawCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    s16 c = w->cursor;
    if (c < 0 || c >= 2) {
        return 0;
    }
    if (NumWinItem[c].cursorID == sp->id) {
        sp->alpha = 0xFF;
    } else {
        sp->alpha = 0;
    }
    return 0;
}
}
extern "C" {
int menuShopNumDrawBuyNum(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int slot;
    NUM_MENU_ARG* arg = (NUM_MENU_ARG*)w->params[0];
    int i;
    int div;
    int value;
    const NUM_WIN_ITEM* p = NumWinItem;
    for (slot = 0; slot < 2; slot++, p++) {
        if (sp->id == p->spriteID) {
            break;
        }
    }
    if (slot >= 2) {
        return 0;
    }
    slot = 1 - slot;
    div = 1;
    for (i = 0; i < slot; i++) {
        div *= 10;
    }
    msgctrlSetValue(0x34, (*arg->value / div) % 10);
    GSmsgPrintRight(w->layer, 0, 0, sp->w, sp->h, -1, 0x4270);
    return 0;
}
}
extern "C" {
int menuShopNumDrawPriceText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    NUM_MENU_ARG* arg = (NUM_MENU_ARG*)w->params[0];
    int msg;
    msgctrlSetValue(0x50, arg->price * *arg->value);
    if (arg->coupon != 0) {
        msg = 0x4359;
    } else {
        msg = 0x434F;
    }
    GSmsgPrint2(w->layer, sp->w - ((u32)GSmsgGetRect(msg) >> 16), 0, -1, msg);
    return 0;
}
}
static void openMsgWin(int shop, MENU_SHOP_MSG_CODE code, int arg, ...) {
    va_list args;
    u8 se;
    switch (code) {
    case 5:
    case 6:
    case 8:
    case 0xB:
        menuPtPlaySe__FUl(0x13);
        break;
    }
    va_start(args, arg);
    winMsgOpenWithSE(2, getMsgID(&se, shop, code, arg, args), 1, 0, se);
    winMsgClose(1);
}
static void openCouponMsgWin(int shop, MENU_COUPON_MSG_CODE code, int arg, ...) {
    va_list args;
    u8 se;
    switch (code) {
    case 4:
    case 8:
    case 9:
        menuPtPlaySe__FUl(0x13);
        break;
    }
    va_start(args, arg);
    winMsgOpenWithSE(2, getCouponMsgID(&se, shop, code, arg, args), 1, 0, se);
    winMsgClose(1);
}
extern "C" {
u32 menuShopGetMsgID(u8* se, int shop, MENU_SHOP_MSG_CODE code, int arg, ...) {
    va_list args;
    va_start(args, arg);
    return getMsgID(se, shop, code, arg, args);
}
}
extern "C" {
u32 menuShopGetCouponMsgID(u8* se, int shop, MENU_COUPON_MSG_CODE code, int arg, ...) {
    va_list args;
    va_start(args, arg);
    return getCouponMsgID(se, shop, code, arg, args);
}
}
static u32 _msgIdWazaMachineChange(u16 id, u32 msg) {
    if (id != 0) {
        u8* item = itemDataBiosGetPtr(id);
        if (item != 0 && itemDataBiosGetKind(item) == 4) {
            msgctrlSetValue(0x39, itemDataBiosGetWazaIDByWazaMachineNo(itemDataBiosGetWazaMachineNo(item)));
            switch (msg) {
            case 0xC5AC:
                msg = 0xC5EC;
                break;
            case 0xC5B5:
                msg = 0xC5EE;
                break;
            case 0xC5BC:
                msg = 0xC5EF;
                break;
            }
        }
    }
    return msg;
}
static u32 getMsgID(u8* se, int shop, MENU_SHOP_MSG_CODE code, int arg, va_list args) {
    int off = code * 4;
    u32* msgs;
    int v = arg;
    int id;
    int first;
    u16 item = 0;
    first = 1;
    int idx = shopData[shop].unk0;
    *se = shopSalesman[idx].se;
    msgs = shopSalesman[idx].msg;
    while (v >= 0) {
        if (first) {
            id = v;
            first = 0;
        } else {
            first = 1;
            msgctrlSetValue(id, v);
            if (id == 0x2D) {
                item = v;
            }
        }
        v = *(int*)__va_arg(args, 1);
    }
    return _msgIdWazaMachineChange(item, *(u32*)((u8*)msgs + off));
}
static u32 getCouponMsgID(u8* se, int shop, MENU_COUPON_MSG_CODE code, int arg, va_list args) {
    int off = code * 4;
    u32* msgs;
    int v = arg;
    int id;
    int first;
    u16 item = 0;
    first = 1;
    int idx = shopData[shop].unk0;
    *se = shopExchanger[idx].se;
    msgs = shopExchanger[idx].msg;
    while (v >= 0) {
        if (first) {
            id = v;
            first = 0;
        } else {
            first = 1;
            msgctrlSetValue(id, v);
            if (id == 0x2D) {
                item = v;
            }
        }
        v = *(int*)__va_arg(args, 1);
    }
    return _msgIdWazaMachineChange(item, *(u32*)((u8*)msgs + off));
}
static u16* getGoodsList(int shop, int* count) {
    int n = 0;
    u16* start = shopGoods + shopData[shop].goodsIdx;
    u16* p = start;
    while (*p != 0) {
        p++;
        n++;
    }
    *count = n;
    return start;
}
static int getMinPoint(int shop) {
    int count;
    u16* list;
    int best = 9999999;
    list = getGoodsList(shop, &count);
    while (*list != 0) {
        int p = getItemCouponPoint(*list);
        if (p < best) {
            best = p;
        }
        list++;
    }
    return best;
}
static int checkAddItem(u16 id, u8 kind) {
    switch (kind) {
    case 2:
        return pcboxGetItemCapacity(0, id);
    default:
        return heroItemCheckAddItemDataId(0, id);
    }
}
static void decCouponAddItem(int coupon, u16 id, int n, u8 kind, VPC_BOX* box) {
    switch (kind) {
    case 2:
        heroDecPokecoupon(0, coupon);
        pcboxAddItem(0, id, n);
        memCardDecCouponAddItem(coupon, id, n, box);
        break;
    default:
        heroDecPokecoupon(0, coupon);
        addItem(id, n);
        break;
    }
}
static void waitTime(f32 seconds) {
    int i;
    u32 frames = (u32)(seconds * GSgfxVideoGetVsyncRate());
    i = 0;
    while (i < (int)frames) {
        GSthreadSwitch();
        i = (int)((f32)i + GSgfxVideoGetLastRenderTime());
    }
}
static bool writeBackPcBox(int shop, u8 kind, VPC_BOX* box) {
    u8 se;
    s8 answer;
    if (!checkExchangeVpc(box)) {
        winMsgOpenWithSE(2, menuShopGetCouponMsgID(&se, shop, (MENU_COUPON_MSG_CODE)0xD, -1), 1, 0, se);
        answer = menuSubOpenYesNo(0, -1, -1, 0);
        winMsgClose(1);
        if (answer == 1 || answer == -1) {
            return false;
        }
        return true;
    }
    winMsgOpenWithSE(2, menuShopGetCouponMsgID(&se, shop, (MENU_COUPON_MSG_CODE)0xF, -1), 1, 0, se);
    answer = menuSubOpenYesNo(0, -1, -1, 0);
    winMsgClose(1);
    if (answer == 1 || answer == -1) {
        return false;
    }
    if (memCardSave(box) == 0) {
        memcpy(savedataGetStatus(0, 3), PPcboxBackup, 0xBC50);
        heroSetStatus(0, 0xD, CouponBackup);
    }
    return true;
}
static bool checkExchangeVpc(VPC_BOX* box) {
    return box->exchanged != 0;
}
static int memCardConnect(VPC_BOX* box) {
    itemInitAry(box, 0xEB);
    itemInitAry((u8*)box + 0x3AC, 0xEB);
    box->f758 = 0;
    box->f75C = 0;
    box->exchanged = 0;
    void* save = savedataGetStatus(0, 3);
    memcpy(PPcboxBackup, save, 0xBC50);
    CouponBackup = heroGetStatus(0, 0xD, 0);
    return 1;
}
static void memCardDecCouponAddItem(int coupon, u16 id, int n, VPC_BOX* box) {
    if (box != 0) {
        box->exchanged = 1;
    }
}
static int memCardSave(VPC_BOX* box) {
    if (memcardTaskCall(4, 2, 0) == 4) {
        return 1;
    }
    return 0;
}
