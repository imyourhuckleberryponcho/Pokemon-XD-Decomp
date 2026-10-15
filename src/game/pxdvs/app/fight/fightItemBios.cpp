#include <dolphin/types.h>

struct FightItem {
    u16 itemDataId;
    u16 targetDataId;
    u32 count;
    u32 buff;
};

extern "C" {

void fightItemBiosSetBuff(FightItem* item, u32 buff) {
    if (item != NULL) {
        item->buff = buff;
    }
}

void fightItemBiosSetCount(FightItem* item, u32 count) {
    if (item != NULL) {
        item->count = count;
    }
}

void fightItemBiosSetTargetDataId(FightItem* item, u16 id) {
    if (item != NULL) {
        item->targetDataId = id;
    }
}

void fightItemBiosSetItemDataId(FightItem* item, u16 id) {
    if (item != NULL) {
        item->itemDataId = id;
    }
}

u32 fightItemBiosGetBuff(FightItem* item) {
    if (item == NULL) {
        return 0;
    }
    return item->buff;
}

u32 fightItemBiosGetCount(FightItem* item) {
    if (item == NULL) {
        return 0;
    }
    return item->count;
}

u16 fightItemBiosGetTargetDataId(FightItem* item) {
    if (item == NULL) {
        return 0;
    }
    return item->targetDataId;
}

u16 fightItemBiosGetItemDataId(FightItem* item) {
    if (item == NULL) {
        return 0;
    }
    return item->itemDataId;
}

}
