#include <dolphin/types.h>

// This unit was built optimizing for size (uses stmw/lmw).
#pragma optimize_for_size on

struct FightItem;

extern "C" {

void fightItem_SetBuff(FightItem* item, u32 buff);
void fightItem_SetCount(FightItem* item, u32 count);
void fightItem_SetTargetDataId(FightItem* item, u16 id);
void fightItem_SetItemDataId(FightItem* item, u16 id);
void fightItemInit(FightItem* item);

void fightItemCreate(FightItem* item, u16 itemDataId, u16 targetDataId, u32 count) {
    if (item != NULL) {
        fightItemInit(item);
        fightItem_SetItemDataId(item, itemDataId);
        fightItem_SetTargetDataId(item, targetDataId);
        fightItem_SetCount(item, count);
    }
}

void fightItemInit(FightItem* item) {
    if (item != NULL) {
        fightItem_SetItemDataId(item, 0);
        fightItem_SetTargetDataId(item, 0);
        fightItem_SetCount(item, -1);
        fightItem_SetBuff(item, 0);
    }
}

}
