#include <dolphin/types.h>

struct Item {
    u16 itemDataId;
    u16 num;
};

struct ItemBallData {
    u8 unk0[4];
    u32 inWzxDataId;
    u32 openWzxDataId;
    u32 outWzxDataId;
    u32 downinWzxDataId;
    u32 throwWzxDataId;
    u32 snatchAttackWzxDataId;
    u32 snatchBalllandWzxDataId;
    u32 snatchMissWzxDataId;
    u32 snatchPokeoutWzxDataId;
    u32 snatchShakeWzxDataId;
    u32 snatchSnatchWzxDataId;
    u32 yaseiBallLandWzxDataId;
    u32 yaseiShakeWzxDataId;
    u32 yaseiGetWzxDataId;
    u32 yaseiPokeoutWzxDataId;
};

struct ItemData {
    u8 kind;
    u8 unk1[9];
    u16 itemSoubiDataId;
    u8 unkC[4];
    u32 name;
    u8 unk14[4];
    u32 buff;
};

extern "C" {

ItemBallData* itemBallDataBiosGetPtr(u16 id);
ItemData* itemDataBiosGetPtr(u16 id);

void item_SetNum(Item* item, u16 value) {
    if (item != NULL) {
        item->num = value;
    }
}

void item_SetItemDataId(Item* item, u16 value) {
    if (item != NULL) {
        item->itemDataId = value;
    }
}

u16 item_GetNum(Item* item) {
    if (item == NULL) {
        return 0;
    }
    return item->num;
}

u16 item_GetItemDataId(Item* item) {
    if (item == NULL) {
        return 0;
    }
    return item->itemDataId;
}

u32 itemBallDB_GetYaseiPokeoutWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->yaseiPokeoutWzxDataId;
}

u32 itemBallDB_GetYaseiGetWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->yaseiGetWzxDataId;
}

u32 itemBallDB_GetYaseiShakeWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->yaseiShakeWzxDataId;
}

u32 itemBallDB_GetYaseiBallLandWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->yaseiBallLandWzxDataId;
}

u32 itemBallDB_GetSnatchSnatchWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->snatchSnatchWzxDataId;
}

u32 itemBallDB_GetSnatchShakeWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->snatchShakeWzxDataId;
}

u32 itemBallDB_GetSnatchPokeoutWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->snatchPokeoutWzxDataId;
}

u32 itemBallDB_GetSnatchMissWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->snatchMissWzxDataId;
}

u32 itemBallDB_GetSnatchBalllandWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->snatchBalllandWzxDataId;
}

u32 itemBallDB_GetSnatchAttackWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->snatchAttackWzxDataId;
}

u32 itemBallDB_GetThrowWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->throwWzxDataId;
}

u32 itemBallDB_GetDowninWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->downinWzxDataId;
}

u32 itemBallDB_GetOutWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->outWzxDataId;
}

u32 itemBallDB_GetOpenWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->openWzxDataId;
}

u32 itemBallDB_GetInWzxDataId(u16 id) {
    ItemBallData* data = itemBallDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->inWzxDataId;
}

u32 itemDB_GetBuff(u16 id) {
    ItemData* data = itemDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->buff;
}

u16 itemDB_GetItemSoubiDataId(u16 id) {
    ItemData* data = itemDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->itemSoubiDataId;
}

u8 itemDB_GetKind(u16 id) {
    ItemData* data = itemDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->kind;
}

u32 itemDB_GetName(u16 id) {
    ItemData* data = itemDataBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->name;
}

}
