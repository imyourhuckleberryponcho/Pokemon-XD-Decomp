#include <dolphin/types.h>

struct FightItem {
    u16 itemDataId;
    u16 targetDataId;
    u32 count;
    u32 buff;
};

extern "C" {

void fightItem_SetBuff(FightItem* item, u32 buff) {
    if (item != NULL) {
        item->buff = buff;
    }
}

void fightItem_SetCount(FightItem* item, u32 count) {
    if (item != NULL) {
        item->count = count;
    }
}

void fightItem_SetTargetDataId(FightItem* item, u16 id) {
    if (item != NULL) {
        item->targetDataId = id;
    }
}

void fightItem_SetItemDataId(FightItem* item, u16 id) {
    if (item != NULL) {
        item->itemDataId = id;
    }
}

u32 fightItem_GetBuff(FightItem* item) {
    if (item == NULL) {
        return 0;
    }
    return item->buff;
}

u32 fightItem_GetCount(FightItem* item) {
    if (item == NULL) {
        return 0;
    }
    return item->count;
}

u16 fightItem_GetTargetDataId(FightItem* item) {
    if (item == NULL) {
        return 0;
    }
    return item->targetDataId;
}

u16 fightItem_GetItemDataId(FightItem* item) {
    if (item == NULL) {
        return 0;
    }
    return item->itemDataId;
}

}
