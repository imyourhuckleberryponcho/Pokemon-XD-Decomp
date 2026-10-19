// STATUS: 13/13 functions, 8 exact; remaining 5 differ only in register allocation (98-99.8%).
// LAYOUT/CONST/CALLS/DATA OK with default flags (-inline deferred breaks function order).
// Helpers are static inline mirrors of the original's inlines (itemCV = item validity check, itemAt = &ary[i]
// as an rvalue; itemIs does its own null check before itemCV).
#include <dolphin/types.h>

struct ITEM {
    u16 id;
    u16 num;
};

extern "C" {
u16* currentPriorityTbl;
u32 currentPriorityTblQuantity;
extern u16 item_ball_sort[];
extern u32 item_ball_sort_number;
extern u16 item_dougu_sort[];
extern u32 item_dougu_sort_number;
extern u32* item_data_index_number;

u32 itemDB_GetName(u16 id);
u16 item_GetItemDataId(ITEM* item);
u16 item_GetNum(ITEM* item);
void item_SetItemDataId(ITEM* item, u16 value);
void item_SetNum(ITEM* item, u16 value);

u32 fightItemBiosGetBuff(void* p);
u32 fightItemBiosGetCount(void* p);
u16 fightItemBiosGetItemDataId(void* p);
u16 fightItemBiosGetTargetDataId(void* p);
void fightItemBiosSetBuff(void* p, u32 v);
void fightItemBiosSetCount(void* p, u32 v);
void fightItemBiosSetItemDataId(void* p, u16 v);
void fightItemBiosSetTargetDataId(void* p, u16 v);
u32 itemBallDataBiosGetDowninWzxDataId(u8* p);
u32 itemBallDataBiosGetFightKoukaDataId(u8* p);
u32 itemBallDataBiosGetInWzxDataId(u8* p);
u32 itemBallDataBiosGetOpenWzxDataId(u8* p);
u32 itemBallDataBiosGetOutWzxDataId(u8* p);
u8* itemBallDataBiosGetPtr(u16 idx);
u32 itemBallDataBiosGetSnatchAttackWzxDataId(u8* p);
u32 itemBallDataBiosGetSnatchBalllandWzxDataId(u8* p);
u32 itemBallDataBiosGetSnatchMissWzxDataId(u8* p);
u32 itemBallDataBiosGetSnatchPokeoutWzxDataId(u8* p);
u32 itemBallDataBiosGetSnatchShakeWzxDataId(u8* p);
u32 itemBallDataBiosGetSnatchSnatchWzxDataId(u8* p);
u32 itemBallDataBiosGetThrowWzxDataId(u8* p);
void itemBallDataBiosSetFightKoukaDataId(u8* p, u16 val);
u32 itemBiosGetItemDataId(u8* p);
u32 itemBiosGetNum(u8* p);
void itemBiosSetItemDataId(u8* p, u16 val);
void itemBiosSetNum(u8* p, u16 val);
u32 itemDataBiosGetBuff(u8* p);
u32 itemDataBiosGetDoc(u8* p);
u32 itemDataBiosGetFightUseKoukaDataId(u8* p);
s32 itemDataBiosGetImportant(u8* p);
u32 itemDataBiosGetItemSoubiDataId(u8* p);
u8 itemDataBiosGetKind(u8* p);
u32 itemDataBiosGetName(u8* p);
u32 itemDataBiosGetPrice(u8* p);
u8* itemDataBiosGetPtr(u16 index);
s32 itemDataBiosGetUseFriend(u8* p, u16 idx);
s32 itemDataBiosGetUseful(u8* p);
void itemDataBiosSetBuff(u8* p, u32 val);
void itemDataBiosSetDoc(u8* p, u32 val);
void itemDataBiosSetFightUseKoukaDataId(u8* p, u16 val);
void itemDataBiosSetImportant(u8* p, u8 val);
void itemDataBiosSetItemSoubiDataId(u8* p, u16 val);
void itemDataBiosSetKind(u8* p, u8 val);
void itemDataBiosSetName(u8* p, u32 val);
void itemDataBiosSetPrice(u8* p, u16 val);
void itemDataBiosSetUseFriend(u8* p, u16 idx, s8 val);
void itemDataBiosSetUseful(u8* p, u8 val);
u16 itemSoubiDataBiosGetFightKoukaDataId(u8* p);
u8* itemSoubiDataBiosGetPtr(u16 idx);
}

static void _itemSortAry(ITEM* ary, u16 n, u8 mode);

static inline bool itemIdOk(u16 id) {
    if (itemDB_GetName(id) == 0) return false;
    if (id >= *item_data_index_number) return false;
    return true;
}

static inline bool itemCV(ITEM* p) {
    if (p == 0) return false;
    u16 id = item_GetItemDataId(p);
    if (id == 0) return false;
    if (!itemIdOk(id)) return false;
    return true;
}

static inline bool itemOk(ITEM* p) {
    return itemCV(p);
}

static inline bool itemIs(ITEM* p, u16 id) {
    if (p == 0) return false;
    if (!itemOk(p)) return false;
    if (id == item_GetItemDataId(p)) return true;
    return false;
}

static inline void itemSwapI(ITEM* a, ITEM* b) {
    if (a != 0 && b != 0) {
        u16 num;
        u16 id = a->id;
        num = a->num;
        a->id = b->id;
        a->num = b->num;
        b->id = id;
        b->num = num;
    }
}

static inline ITEM* itemAt(ITEM* a, u16 i) {
    return &a[i];
}

static inline ITEM* itemFindAny(ITEM* ary, u16 n, u16 id) {
    if (ary == 0) return 0;
    if (!itemIdOk(id)) return 0;
    for (u16 i = 0; i < n; i++) {
        ITEM* p = itemAt(ary, i);
        if (itemIs(p, id)) return ary + i;
    }
    return 0;
}

static inline ITEM* itemFindNotFull(ITEM* ary, u16 n, u16 id, u16 max) {
    if (ary == 0) return 0;
    if (!itemIdOk(id)) return 0;
    for (u16 i = 0; i < n; i++) {
        ITEM* p = itemAt(ary, i);
        if (itemIs(p, id) && item_GetNum(p) < max) return p;
    }
    return 0;
}

static inline ITEM* itemFindEmpty(ITEM* ary, u16 n, u16 id) {
    if (ary == 0) return 0;
    if (!itemIdOk(id)) return 0;
    for (u16 i = 0; i < n; i++) {
        ITEM* p = itemAt(ary, i);
        if (!itemOk(p)) return ary + i;
    }
    return 0;
}

static inline s32 itemAddOne(ITEM* p, u16 id, u16 cnt, u16 max) {
    if (p == 0) return -1;
    if (!itemIdOk(id)) return -1;
    if (!itemIs(p, id)) return -1;
    if (p == 0) return -1;
    if (!itemCV(p)) return -1;
    s32 total = item_GetNum(p);
    s32 over;
    total += cnt;
    if (total > (s32)max) {
        over = total - max;
        total = max;
    } else {
        over = 0;
    }
    item_SetNum(p, (u16)total);
    return over;
}

static inline s32 itemAddNew(ITEM* p, u16 id, u16 cnt, u16 max) {
    if (p == 0) return -1;
    if (!itemIdOk(id)) return -1;
    if (p != 0) {
        item_SetItemDataId(p, 0);
        item_SetNum(p, 0);
    }
    item_SetItemDataId(p, id);
    if (p == 0) return -1;
    if (!itemCV(p)) return -1;
    s32 total = item_GetNum(p);
    s32 over;
    total += cnt;
    if (total > (s32)max) {
        over = total - max;
        total = max;
    } else {
        over = 0;
    }
    item_SetNum(p, (u16)total);
    return over;
}

static inline s32 itemDecOne(ITEM* p, u16 id, u16 cnt) {
    if (p == 0) return -1;
    if (!itemIdOk(id)) return -1;
    if (!itemIs(p, id)) return -1;
    if (p == 0) return -1;
    if (!itemOk(p)) return -1;
    s32 left = item_GetNum(p);
    s32 over;
    left -= cnt;
    if (left < 0) {
        over = cnt - left;
        left = 0;
    } else {
        over = 0;
    }
    item_SetNum(p, (u16)left);
    if (left <= 0 && p != 0) {
        item_SetItemDataId(p, 0);
        item_SetNum(p, 0);
    }
    return over;
}

static inline int itemPriorityOf(int id) {
    int i;
    u16* t = currentPriorityTbl;
    for (i = 0; i < currentPriorityTblQuantity; i++, t++) {
        if (id == *t) return i;
    }
    return 0;
}

extern "C" {

void itemSortAryByPriority(void* ary, u16 n, s32 type) {
    if (type == 2) {
        currentPriorityTbl = item_dougu_sort;
        currentPriorityTblQuantity = item_dougu_sort_number;
    } else if (type == 1) {
        currentPriorityTbl = item_ball_sort;
        currentPriorityTblQuantity = item_ball_sort_number;
    }
    ITEM* a = (ITEM*)ary;
    if (a != 0 && n != 0) {
        int j;
        int i;
        ITEM* q;
        ITEM* p = a;
        int last = n - 1;
        for (i = 0; i < last; i++, p++) {
            if (itemOk(p)) {
                j = i + 1;
                q = a + j;
                for (; j < (int)n; j++, q++) {
                    if (itemOk(q)) {
                        int idA = item_GetItemDataId(p);
                        int idB = item_GetItemDataId(q);
                        if (itemPriorityOf(idA) - itemPriorityOf(idB) > 0) itemSwapI(p, q);
                    }
                }
            }
        }
    }
}

s32 itemCheckAddItemDataIdAry(void* aryv, u16 n, u16 id, u16 cnt, u8 flag) {
    ITEM* ary = (ITEM*)aryv;
    ITEM* p;
    s32 r;
    u16 i;
    if (ary == 0) return -1;
    if (!itemIdOk(id)) return -1;
    if (flag == 0) {
        p = itemFindAny(ary, n, id);
        if (p != 0) {
            r = cnt - item_GetNum(p);
        } else {
            ITEM* e = itemFindEmpty(ary, n, id);
            if (e != 0) r = cnt;
            else r = 0;
        }
    } else {
        r = 0;
        for (i = 0; i < n; i++) {
            p = &ary[i];
            if (!itemOk(p)) {
                r += cnt;
            } else if (itemIs(p, id) == 1) {
                r += cnt - item_GetNum(p);
            }
        }
    }
    return r;
}

void itemReplace(void* a, void* b) {
    itemSwapI((ITEM*)a, (ITEM*)b);
}

s32 itemDecItemDataIdAry(ITEM* ary, u16 n, u16 id, u32 cnt, s16 slot, u16 unused, u8 mode) {
    if (ary == 0) return -1;
    if (!itemIdOk(id)) return -1;
    u8 sort = 0;
    if (slot < 0) {
        cnt &= 0xFFFF;
        while (1) {
            ITEM* p = itemFindAny(ary, n, id);
            if (p == 0) break;
            s32 r = itemDecOne(p, id, cnt);
            if (r < 0) return r;
            if (!itemOk(p)) sort = 1;
            cnt = r;
            if (r <= 0) break;
        }
    } else {
        ITEM* p = ary + slot;
        cnt = itemDecOne(p, id, cnt);
        if (!itemOk(p)) sort = 1;
    }
    if (sort == 1) _itemSortAry(ary, n, mode);
    return cnt;
}

s32 itemAddItemDataIdAry(void* aryv, u16 n, u16 id, u32 cnt, s16 slot, u16 max, u8 mode, u8 flag) {
    ITEM* p;
    ITEM* ary = (ITEM*)aryv;
    if (ary == 0) return -1;
    if (!itemIdOk(id)) return -1;
    u16 c16 = cnt;
    int rem = c16;
    u8 sort = 0;
    if (flag == 0) {
        ITEM* p = itemFindAny(ary, n, id);
        if (p != 0) {
            if (item_GetNum(p) < max) {
                s32 r = itemAddOne(p, id, rem, max);
                if (r < 0) return r;
                rem = r;
            }
        } else {
            ITEM* e = itemFindEmpty(ary, n, id);
            if (e != 0) {
                s32 r = itemAddNew(e, id, rem, max);
                if (r < 0) return r;
                rem = r;
                sort = 1;
            }
        }
    } else if (slot < 0) {
        do {
            ITEM* p = itemFindNotFull(ary, n, (u16)id, max);
            if (p != 0) {
                s32 r = itemAddOne(p, id, rem, max);
                if (r < 0) return r;
                rem = r;
            } else {
                ITEM* e = itemFindEmpty(ary, n, id);
                if (e == 0) break;
                s32 r = itemAddNew(e, id, rem, max);
                if (r < 0) return r;
                sort = 1;
                rem = r;
            }
        } while (rem > 0);
    } else {
        p = ary + slot;
        rem = itemAddOne(p, id, c16, max);
    }
    if (sort == 1) _itemSortAry(ary, n, mode);
    return rem;
}

u16 itemGetQuantityInAry(void* aryv, u16 n, u16 id, u16 unused) {
    ITEM* ary = (ITEM*)aryv;
    if (ary == 0) return 0;
    if (!itemIdOk(id)) return 0;
    ITEM* p = ary;
    s32 total = 0;
    for (s32 i = 0; i < (s32)n; i++, p++) {
        if (itemIs(p, id)) total += item_GetNum(p);
    }
    return total;
}

s32 itemSearchItemDataIdAry(void* aryv, u16 n, u16 id, u8 mode, u16 max) {
    ITEM* ary = (ITEM*)aryv;
    u16 i;
    if (ary == 0) return 0;
    if (!itemIdOk(id)) return 0;
    for (i = 0; i < n; i++) {
        if (mode == 2) {
            ITEM* p = itemAt(ary, i);
            if (!itemCV(p)) return (s32)(ary + i);
        } else {
            ITEM* p = itemAt(ary, i);
            if (itemIs(p, id)) {
                if (mode == 1) {
                    if (item_GetNum(p) < max) return (s32)(ary + i);
                } else {
                    return (s32)(ary + i);
                }
            }
        }
    }
    return 0;
}

}

static void _itemSortAry(ITEM* ary, u16 n, u8 mode) {
    if (ary != 0 && n != 0) {
        if (mode == 0 || mode == 1) {
            ITEM* q;
            ITEM* p = ary;
            for (int i = 0; i < (int)(n - 1); i++, p++) {
                if (!itemOk(p)) {
                    int j = i + 1;
                    q = ary + j;
                    for (; j < (int)n; j++, q++) {
                        if (itemOk(q) == 1) {
                            itemSwapI(p, ary + j);
                            break;
                        }
                    }
                }
            }
        }
        if (mode == 1) {
            ITEM* p = ary;
            for (int i = 0; i < (int)(n - 1); i++, p++) {
                if (itemOk(p)) {
                    int j = i + 1;
                    ITEM* q = ary + j;
                    for (; j < (int)n; j++, q++) {
                        if (itemOk(q)) {
                            u16 a = item_GetItemDataId(p);
                            if (a > item_GetItemDataId(q)) itemSwapI(p, q);
                        }
                    }
                }
            }
        }
    }
}

extern "C" {

bool itemDataCheckValid(u16 id) {
    if (itemDB_GetName(id) == 0) return false;
    return id < *item_data_index_number;
}

bool itemCheckValid(void* p) {
    if (p == 0) return false;
    u16 id = item_GetItemDataId((ITEM*)p);
    if (id == 0) return false;
    return itemIdOk(id) != 0;
}

void itemInitAry(void* aryv, u16 n) {
    ITEM* ary = (ITEM*)aryv;
    if (ary != 0) {
        ITEM* p;
        for (u16 i = 0; i < n; i++) {
            p = &ary[i];
            if (p != 0) {
                item_SetItemDataId(p, 0);
                item_SetNum(p, 0);
            }
        }
    }
}

void itemSetStatus(u8* p, u16 id, u16 kind, u16 idx, s32 value) {
    if (kind == 0 || kind >= 0x23) return;
    if (kind < 0xB) {
        p = itemDataBiosGetPtr(id);
        if (p == 0) return;
    } else if (kind < 0x18) {
        p = itemBallDataBiosGetPtr(id);
        if (p == 0) return;
    } else if (p == 0) {
        return;
    }
    switch (kind) {
    case 1: itemDataBiosSetName(p, value); break;
    case 2: itemDataBiosSetKind(p, value); break;
    case 3: itemDataBiosSetPrice(p, value); break;
    case 4: itemDataBiosSetImportant(p, value != 0); break;
    case 5: itemDataBiosSetUseful(p, value != 0); break;
    case 6: itemDataBiosSetDoc(p, value); break;
    case 7: itemDataBiosSetItemSoubiDataId(p, value); break;
    case 8: itemDataBiosSetFightUseKoukaDataId(p, value); break;
    case 9: itemDataBiosSetUseFriend(p, idx, value); break;
    case 10: itemDataBiosSetBuff(p, value);
    case 12: itemBallDataBiosSetFightKoukaDataId(p, value); break;
    case 27: itemBiosSetItemDataId(p, value); break;
    case 28: itemBiosSetNum(p, value); break;
    case 30: fightItemBiosSetItemDataId(p, value); break;
    case 31: fightItemBiosSetTargetDataId(p, value); break;
    case 32: fightItemBiosSetCount(p, value); break;
    case 33: fightItemBiosSetBuff(p, value); break;
    }
}

u32 itemGetStatus(void* entry, u16 id, u16 kind, u16 idx) {
    u8* p = (u8*)entry;
    if (kind == 0 || kind >= 0x23) return 0;
    if (kind < 0xB) {
        p = itemDataBiosGetPtr(id);
        if (p == 0) return 0;
    } else if (kind < 0x18) {
        p = itemBallDataBiosGetPtr(id);
        if (p == 0) return 0;
    } else if (kind < 0x1A) {
        p = itemSoubiDataBiosGetPtr(id);
        if (p == 0) return 0;
    } else if (p == 0) {
        return 0;
    }
    switch (kind) {
    case 1: return itemDataBiosGetName(p);
    case 2: return itemDataBiosGetKind(p);
    case 3: return (u16)itemDataBiosGetPrice(p);
    case 4: return (u8)itemDataBiosGetImportant(p);
    case 5: return (u8)itemDataBiosGetUseful(p);
    case 6: return itemDataBiosGetDoc(p);
    case 7: return (u16)itemDataBiosGetItemSoubiDataId(p);
    case 8: return (u16)itemDataBiosGetFightUseKoukaDataId(p);
    case 9: return (s8)itemDataBiosGetUseFriend(p, idx);
    case 10: return itemDataBiosGetBuff(p);
    case 12: return (u16)itemBallDataBiosGetFightKoukaDataId(p);
    case 13: return itemBallDataBiosGetInWzxDataId(p);
    case 14: return itemBallDataBiosGetOpenWzxDataId(p);
    case 15: return itemBallDataBiosGetOutWzxDataId(p);
    case 16: return itemBallDataBiosGetDowninWzxDataId(p);
    case 17: return itemBallDataBiosGetThrowWzxDataId(p);
    case 18: return itemBallDataBiosGetSnatchAttackWzxDataId(p);
    case 19: return itemBallDataBiosGetSnatchBalllandWzxDataId(p);
    case 20: return itemBallDataBiosGetSnatchMissWzxDataId(p);
    case 21: return itemBallDataBiosGetSnatchPokeoutWzxDataId(p);
    case 22: return itemBallDataBiosGetSnatchShakeWzxDataId(p);
    case 23: return itemBallDataBiosGetSnatchSnatchWzxDataId(p);
    case 25: return (u16)itemSoubiDataBiosGetFightKoukaDataId(p);
    case 27: return (u16)itemBiosGetItemDataId(p);
    case 28: return (u16)itemBiosGetNum(p);
    case 30: return (u16)fightItemBiosGetItemDataId(p);
    case 31: return (u16)fightItemBiosGetTargetDataId(p);
    case 32: return fightItemBiosGetCount(p);
    case 33: return fightItemBiosGetBuff(p);
    }
    return 0;
}

}
