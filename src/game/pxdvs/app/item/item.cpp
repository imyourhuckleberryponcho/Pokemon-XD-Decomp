// STATUS (rough draft, rd_item): 13/13 functions, 0 exact, byte-weighted ~81%. LAYOUT/CONST/CALLS/DATA OK
// with default flags (-inline deferred breaks function order; noauto same as default).
// Biggest gaps: itemAddItemDataIdAry 75% (target keeps id/count params raw in regs, clrlwi at use),
// itemSetStatus 68% (switch layout/args), itemSearchItemDataIdAry 79%, itemCheckAddItemDataIdAry 81%.
// Helpers are static inline mirrors of the validity/search inlines the original has.
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
void itemDataBiosSetUseFriend(u8* p, u16 idx, u8 val);
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

static inline bool itemOk(ITEM* p) {
    if (p == 0) return false;
    u16 id = item_GetItemDataId(p);
    if (id == 0) return false;
    return itemIdOk(id);
}

static inline bool itemIs(ITEM* p, u16 id) {
    if (p == 0) return false;
    if (!itemOk(p)) return false;
    if (id == item_GetItemDataId(p)) return true;
    return false;
}

static inline void itemSwapI(ITEM* a, ITEM* b) {
    if (a != 0 && b != 0) {
        u16 id = a->id;
        u16 num = a->num;
        a->id = b->id;
        a->num = b->num;
        b->id = id;
        b->num = num;
    }
}

static inline ITEM* itemFindAny(ITEM* ary, u16 n, u16 id) {
    if (ary == 0) return 0;
    if (!itemIdOk(id)) return 0;
    for (u16 i = 0; i < n; i++) {
        ITEM* p = &ary[i];
        if (itemIs(p, id)) return p;
    }
    return 0;
}

static inline ITEM* itemFindNotFull(ITEM* ary, u16 n, u16 id, u16 max) {
    if (ary == 0) return 0;
    if (!itemIdOk(id)) return 0;
    for (u16 i = 0; i < n; i++) {
        ITEM* p = &ary[i];
        if (itemIs(p, id) && item_GetNum(p) < max) return p;
    }
    return 0;
}

static inline ITEM* itemFindEmpty(ITEM* ary, u16 n, u16 id) {
    if (ary == 0) return 0;
    if (!itemIdOk(id)) return 0;
    for (u16 i = 0; i < n; i++) {
        ITEM* p = &ary[i];
        if (!itemOk(p)) return p;
    }
    return 0;
}

static inline s32 itemAddOne(ITEM* p, u16 id, s32 cnt, u16 max) {
    if (p == 0) return -1;
    if (!itemIdOk(id)) return -1;
    if (!itemIs(p, id)) return -1;
    if (p == 0) return -1;
    if (!itemOk(p)) return -1;
    s32 total = item_GetNum(p) + cnt;
    s32 over;
    if (total > (s32)max) {
        over = total - max;
        total = max;
    } else {
        over = 0;
    }
    item_SetNum(p, (u16)total);
    return over;
}

static inline s32 itemDecOne(ITEM* p, u16 id, s32 cnt) {
    if (p == 0) return -1;
    if (!itemIdOk(id)) return -1;
    if (!itemIs(p, id)) return -1;
    if (p == 0) return -1;
    if (!itemOk(p)) return -1;
    s32 left = item_GetNum(p) - cnt;
    s32 over;
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

static inline int itemPriorityOf(u16 id) {
    int i = 0;
    u16* t = currentPriorityTbl;
    for (u32 c = currentPriorityTblQuantity; c > 0; c--, t++, i++) {
        if (id == *t) return i;
    }
    return 0;
}

extern "C" {

void itemSortAryByPriority(void* ary, u16 n, u32 type) {
    if (type == 2) {
        currentPriorityTbl = item_dougu_sort;
        currentPriorityTblQuantity = item_dougu_sort_number;
    } else if (type == 1) {
        currentPriorityTbl = item_ball_sort;
        currentPriorityTblQuantity = item_ball_sort_number;
    }
    ITEM* a = (ITEM*)ary;
    if (a != 0 && n != 0) {
        ITEM* p = a;
        for (int i = 0; i < (int)(n - 1); i++, p++) {
            if (itemOk(p)) {
                ITEM* q = p + 1;
                for (int j = i + 1; j < (int)n; j++, q++) {
                    if (itemOk(q)) {
                        u16 idA = item_GetItemDataId(p);
                        u16 idB = item_GetItemDataId(q);
                        int pa = itemPriorityOf(idA);
                        int pb = itemPriorityOf(idB);
                        if (pa - pb > 0) itemSwapI(p, q);
                    }
                }
            }
        }
    }
}

s32 itemCheckAddItemDataIdAry(void* aryv, u16 n, u16 id, u16 cnt, u8 flag) {
    ITEM* ary = (ITEM*)aryv;
    if (ary == 0) return -1;
    if (!itemIdOk(id)) return -1;
    u16 r;
    if (flag == 0) {
        ITEM* p = itemFindAny(ary, n, id);
        if (p != 0) {
            r = cnt - item_GetNum(p);
        } else {
            ITEM* e = itemFindEmpty(ary, n, id);
            if (e != 0) r = cnt;
            else r = 0;
        }
    } else {
        r = 0;
        for (u16 i = 0; i < n; i++) {
            ITEM* p = &ary[i];
            if (!itemOk(p)) {
                r += cnt;
            } else if (itemIs(p, id)) {
                r += cnt - item_GetNum(p);
            }
        }
    }
    return r;
}

void itemReplace(void* a, void* b) {
    itemSwapI((ITEM*)a, (ITEM*)b);
}

s32 itemDecItemDataIdAry(void* aryv, u16 n, u16 id, u32 cnt, s16 slot, u16 unused, u8 mode) {
    ITEM* ary = (ITEM*)aryv;
    if (ary == 0) return -1;
    if (!itemIdOk(id)) return -1;
    u8 sort = 0;
    u16 rem;
    if (slot < 0) {
        rem = (u16)cnt;
        while (1) {
            ITEM* p = itemFindAny(ary, n, id);
            if (p == 0) break;
            s32 r = itemDecOne(p, id, rem);
            if (r < 0) return r;
            if (!itemOk(p)) sort = 1;
            rem = (u16)r;
            if (r <= 0) break;
        }
    } else {
        ITEM* p = ary + slot;
        rem = (u16)itemDecOne(p, id, (u16)cnt);
        if (!itemOk(p)) sort = 1;
    }
    if (sort == 1) _itemSortAry(ary, n, mode);
    return rem;
}

s32 itemAddItemDataIdAry(void* aryv, u16 n, u16 id, u32 cnt, s16 slot, u16 max, u8 mode, u8 flag) {
    ITEM* ary = (ITEM*)aryv;
    if (ary == 0) return -1;
    if (!itemIdOk(id)) return -1;
    u8 sort = 0;
    u16 rem = (u16)cnt;
    if (flag == 0) {
        ITEM* p = itemFindAny(ary, n, id);
        if (p != 0 && item_GetNum(p) < max) {
            s32 r = itemAddOne(p, id, rem, max);
            if (r < 0) return r;
            rem = (u16)r;
        } else {
            ITEM* e = itemFindEmpty(ary, n, id);
            if (e != 0) {
                item_SetItemDataId(e, 0);
                item_SetNum(e, 0);
                item_SetItemDataId(e, id);
                s32 r = itemAddOne(e, id, rem, max);
                if (r < 0) return r;
                rem = (u16)r;
                sort = 1;
            }
        }
    } else if (slot < 0) {
        while (1) {
            ITEM* p = itemFindNotFull(ary, n, id, max);
            if (p != 0) {
                s32 r = itemAddOne(p, id, rem, max);
                if (r < 0) return r;
                rem = (u16)r;
            } else {
                ITEM* e = itemFindEmpty(ary, n, id);
                if (e == 0) break;
                item_SetItemDataId(e, 0);
                item_SetNum(e, 0);
                item_SetItemDataId(e, id);
                s32 r = itemAddOne(e, id, rem, max);
                if (r < 0) return r;
                sort = 1;
                rem = (u16)r;
            }
            if ((s32)rem <= 0) break;
        }
    } else {
        ITEM* p = ary + slot;
        rem = (u16)itemAddOne(p, id, (u16)cnt, max);
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

s32 itemSearchItemDataIdAry(void* aryv, u16 n, u16 id, u32 mode, u16 max) {
    ITEM* ary = (ITEM*)aryv;
    if (ary == 0) return 0;
    if (!itemIdOk(id)) return 0;
    for (u16 i = 0; i < n; i++) {
        ITEM* p = &ary[i];
        if (mode == 2) {
            if (!itemOk(p)) return (s32)(ary + i);
            continue;
        }
        if (itemIs(p, id)) {
            if (mode == 1) {
                if (item_GetNum(p) < max) return (s32)(ary + i);
                continue;
            }
            return (s32)(ary + i);
        }
    }
    return 0;
}

}

static void _itemSortAry(ITEM* ary, u16 n, u8 mode) {
    if (ary != 0 && n != 0) {
        if (mode == 0 || mode == 1) {
            ITEM* p = ary;
            for (int i = 0; i < (int)(n - 1); i++, p++) {
                if (!itemOk(p)) {
                    ITEM* q = ary + (i + 1);
                    for (int j = i + 1; j < (int)n; j++, q++) {
                        if (itemOk(q)) {
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
                    ITEM* q = ary + (i + 1);
                    for (int j = i + 1; j < (int)n; j++, q++) {
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
    return itemIdOk(id);
}

bool itemCheckValid(void* p) {
    return itemOk((ITEM*)p);
}

void itemInitAry(void* aryv, u16 n) {
    ITEM* ary = (ITEM*)aryv;
    if (ary != 0) {
        for (u16 i = 0; i < n; i++) {
            ITEM* p = &ary[i];
            if (p != 0) {
                item_SetItemDataId(p, 0);
                item_SetNum(p, 0);
            }
        }
    }
}

s32 itemSetStatus(u32 entry, u32 id, u32 kind16, u32 idx, s32 value) {
    u8* p = (u8*)entry;
    u16 kind = (u16)kind16;
    u8 v = (u8)value;
    if (kind == 0) return 0;
    if (kind >= 0x23) return 0;
    if (kind < 0xB) {
        p = itemDataBiosGetPtr(id);
        if (p == 0) return 0;
    } else if (kind < 0x18) {
        p = itemBallDataBiosGetPtr(id);
        if (p == 0) return 0;
    } else if (p == 0) {
        return 0;
    }
    switch (kind) {
    case 1: itemDataBiosSetName(p, v); break;
    case 2: itemDataBiosSetKind(p, v); break;
    case 3: itemDataBiosSetPrice(p, v); break;
    case 4: itemDataBiosSetImportant(p, v != 0); break;
    case 5: itemDataBiosSetUseful(p, v != 0); break;
    case 6: itemDataBiosSetDoc(p, v); break;
    case 7: itemDataBiosSetItemSoubiDataId(p, v); break;
    case 8: itemDataBiosSetFightUseKoukaDataId(p, v); break;
    case 9: itemDataBiosSetUseFriend(p, (u16)idx, v); break;
    case 10: itemDataBiosSetBuff(p, v); break;
    case 12: itemBallDataBiosSetFightKoukaDataId(p, v); break;
    case 27: itemBiosSetItemDataId(p, v); break;
    case 28: itemBiosSetNum(p, v); break;
    case 30: fightItemBiosSetItemDataId(p, v); break;
    case 31: fightItemBiosSetTargetDataId(p, v); break;
    case 32: fightItemBiosSetCount(p, v); break;
    case 33: fightItemBiosSetBuff(p, v); break;
    }
    return 0;
}

u32 itemGetStatus(u32 entry, u32 id, u32 kind16, u32 idx) {
    u8* p = (u8*)entry;
    u16 kind = (u16)kind16;
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
    case 3: return (u8)itemDataBiosGetPrice(p);
    case 4: return itemDataBiosGetImportant(p);
    case 5: return itemDataBiosGetUseful(p);
    case 6: return itemDataBiosGetDoc(p);
    case 7: return (u8)itemDataBiosGetItemSoubiDataId(p);
    case 8: return (u8)itemDataBiosGetFightUseKoukaDataId(p);
    case 9: return (u8)itemDataBiosGetUseFriend(p, (u16)idx);
    case 10: return itemDataBiosGetBuff(p);
    case 12: return (u8)itemBallDataBiosGetFightKoukaDataId(p);
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
    case 25: return (u8)itemSoubiDataBiosGetFightKoukaDataId(p);
    case 27: return (u8)itemBiosGetItemDataId(p);
    case 28: return (u8)itemBiosGetNum(p);
    case 30: return (u8)fightItemBiosGetItemDataId(p);
    case 31: return (u8)fightItemBiosGetTargetDataId(p);
    case 32: return fightItemBiosGetCount(p);
    case 33: return fightItemBiosGetBuff(p);
    }
    return 0;
}

}
