// Floor data accessors (floordata table, 0x40 bytes per floor).
#include <dolphin/types.h>

#pragma peephole off

struct GSvec {
    f32 x, y, z;
    void set(f32 x, f32 y, f32 z);
};

// Per-floor graphics description (shadow / sun / fog model ids).
struct FloorGfxInfo {
    u32 sunResID;           // 0x00
    u32 shadowLightID;      // 0x04
    u32 shadowRecive[8];    // 0x08
    u32 secondaryRender[3]; // 0x28
    u32 fogModel[3];        // 0x34
};

struct FloorGfxHolder {
    FloorGfxInfo* info;
};

struct FloorCharInfo {
    u8 data[0x24];
};

struct FloorCharCount {
    u32 count;
};

struct FloorCharList {
    FloorCharCount* count;
    FloorCharInfo* info;
};

struct FloorCharHolder {
    FloorCharList* list;
};

struct FloorPosEntry {
    s16 angle;
    s16 pad;
    f32 x;
    f32 y;
    f32 z;
};

struct FloorPosCount {
    u32 count;
};

struct FloorPosList {
    FloorPosCount* count;
    FloorPosEntry* entries;
};

struct FloorPosHolder {
    FloorPosList* list;
};

struct FloorFieldCameraHolder {
    void* list;
};

struct FloorData {
    u8 area;                             // 0x00
    u8 kind;                             // 0x01
    u16 floorID;                         // 0x02
    u32 mapResID;                        // 0x04
    FloorGfxHolder* gfx;                 // 0x08
    FloorCharHolder* chars;              // 0x0C
    FloorPosHolder* positions;           // 0x10
    FloorFieldCameraHolder* fieldCamera; // 0x14
    u32 placeName;                       // 0x18
    u32 preFunc;                         // 0x1C
    u32 mainFunc;                        // 0x20
    u32 postFunc;                        // 0x24
    u32 unk28;                           // 0x28
    u32 groupID[5];                      // 0x2C, indexed by language
};

struct FloorTresure {
    u8 unk0[4];
    u16 floorID; // 0x04
    u8 unk6[0x16];
};

extern "C" {

s32 pokecoloGetLanguage(void);
u16 fightGetFightEncountDataId(void);
s32 pokecoloGetRomVersion(void);
u32 GSfloorGetCurrent(void);

extern u32* floordata_number;
extern FloorData* floordata;
extern FloorTresure* floor_tresure_list;

s32 fn_801231D4(void);
FloorData* floorDataBiosGetPtr(u32 key);
FloorData* floorDataBiosGetCurrentPtr(void);
FloorPosList* floorDataBiosGetPosListPtr(FloorData* floor);

s32 floorTresureGetResID(u16 idx) {
    s32 count = 0;
    FloorData* cur = floorDataBiosGetCurrentPtr();
    FloorTresure* entry = floor_tresure_list;
    for (u32 i = 0; i < idx; i++) {
        if (entry->floorID == cur->floorID) {
            count++;
        }
        entry++;
    }
    return count | 0x7FFF0000;
}

s32 floorDataBiosModelIDGetFogState(u32 modelID) {
    FloorData* floor = floorDataBiosGetCurrentPtr();
    if (modelID == 0) {
        return 1;
    }
    if (floor == 0) {
        return 1;
    }
    FloorGfxHolder* gfx = floor->gfx;
    if (gfx == 0) {
        return 1;
    }
    FloorGfxInfo* info = gfx->info;
    for (s32 i = 0; i < 3; i++) {
        if (info->fogModel[i] == modelID) {
            return 0;
        }
    }
    return 1;
}

s32 floorDataBiosGetSecondaryRenderNum(FloorData* floor) {
    s32 count = 0;
    if (floor == 0) {
        return 0;
    }
    FloorGfxHolder* gfx = floor->gfx;
    if (gfx == 0) {
        return 0;
    }
    FloorGfxInfo* info = gfx->info;
    if (info == 0) {
        return 0;
    }
    if (info->secondaryRender[0] != 0) {
        count++;
    }
    if (info->secondaryRender[1] != 0) {
        count++;
    }
    if (info->secondaryRender[2] != 0) {
        count++;
    }
    return count;
}

u32 floorDataBiosGetSecondaryRenderID(FloorData* floor, u32 idx) {
    if (floor == 0) {
        return 0;
    }
    FloorGfxHolder* gfx = floor->gfx;
    if (gfx == 0) {
        return 0;
    }
    if (idx >= 3) {
        return 0;
    }
    FloorGfxInfo* info = gfx->info;
    if (info == 0) {
        return 0;
    }
    return info->secondaryRender[idx];
}

s32 floorDataBiosGetShadowReciveNum(FloorData* floor) {
    s32 count = 0;
    if (floor == 0) {
        return 0;
    }
    FloorGfxHolder* gfx = floor->gfx;
    if (gfx == 0) {
        return 0;
    }
    FloorGfxInfo* info = gfx->info;
    if (info == 0) {
        return 0;
    }
    if (info->shadowRecive[0] != 0) {
        count++;
    }
    if (info->shadowRecive[1] != 0) {
        count++;
    }
    if (info->shadowRecive[2] != 0) {
        count++;
    }
    if (info->shadowRecive[3] != 0) {
        count++;
    }
    if (info->shadowRecive[4] != 0) {
        count++;
    }
    if (info->shadowRecive[5] != 0) {
        count++;
    }
    if (info->shadowRecive[6] != 0) {
        count++;
    }
    if (info->shadowRecive[7] != 0) {
        count++;
    }
    return count;
}

u32 floorDataBiosGetShadowReciveID(FloorData* floor, u32 idx) {
    if (floor == 0) {
        return 0;
    }
    FloorGfxHolder* gfx = floor->gfx;
    if (gfx == 0) {
        return 0;
    }
    if (idx >= 8) {
        return 0;
    }
    FloorGfxInfo* info = gfx->info;
    if (info == 0) {
        return 0;
    }
    return info->shadowRecive[idx];
}

u32 floorDataBiosGetShadowLightID(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    FloorGfxHolder* gfx = floor->gfx;
    if (gfx == 0) {
        return 0;
    }
    FloorGfxInfo* info = gfx->info;
    if (info == 0) {
        return 0;
    }
    return info->shadowLightID;
}

u32 floorDataBiosGetLensFlareResID(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    FloorGfxHolder* gfx = floor->gfx;
    if (gfx == 0) {
        return 0;
    }
    if (gfx->info == 0) {
        return 0;
    }
    return 0;
}

u32 floorDataBiosGetSunResID(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    FloorGfxHolder* gfx = floor->gfx;
    if (gfx == 0) {
        return 0;
    }
    FloorGfxInfo* info = gfx->info;
    if (info == 0) {
        return 0;
    }
    return info->sunResID;
}

void floorDataBiosSetMapResID(FloorData* floor, u32 resID) {
    if (floor == 0) {
        return;
    }
    floor->mapResID = resID;
}

void* floorDataBiosGetFieldCameraListPtr(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    FloorFieldCameraHolder* holder = floor->fieldCamera;
    if (holder == 0) {
        return 0;
    }
    return holder->list;
}

s32 floorDataBiosGetPosListData(u32 idx, GSvec* pos, f32* angle) {
    FloorPosList* list = floorDataBiosGetPosListPtr(floorDataBiosGetCurrentPtr());
    if (list == 0) {
        return 0;
    }
    if (idx < list->count->count) {
        FloorPosEntry* entry = &list->entries[idx];
        if (pos != 0) {
            pos->set(entry->x, entry->y, entry->z);
        }
        if (angle != 0) {
            *angle = 0.017453292f * entry->angle;
        }
        return 1;
    }
    return 0;
}

FloorPosList* floorDataBiosGetPosListPtr(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    FloorPosHolder* holder = floor->positions;
    if (holder == 0) {
        return 0;
    }
    return holder->list;
}

FloorCharInfo* floorDataBiosGetCharInfo(FloorData* floor, u32 idx) {
    if (floor == 0) {
        return 0;
    }
    FloorCharHolder* holder = floor->chars;
    if (holder == 0) {
        return 0;
    }
    FloorCharList* list = holder->list;
    if (idx >= list->count->count) {
        return 0;
    }
    return &list->info[idx];
}

u32 floorDataBiosGetCharNum(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    FloorCharHolder* holder = floor->chars;
    if (holder == 0) {
        return 0;
    }
    FloorCharList* list = holder->list;
    if (list == 0) {
        return 0;
    }
    return list->count->count;
}

u32 floorDataBiosGetPostFunc(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    return floor->postFunc;
}

u32 floorDataBiosGetMainFunc(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    return floor->mainFunc;
}

u32 floorDataBiosGetPreFunc(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    return floor->preFunc;
}

u32 floorDataBiosGetPlaceName(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    return floor->placeName;
}

u16 floorDataBiosGetFloorID(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    return floor->floorID;
}

u32 floorDataBiosGetFileGroupID(FloorData* floor) {
    s32 lang = fn_801231D4();
    if (floor == 0) {
        return 0;
    }
    return floor->groupID[lang];
}

u32 floorDataBiosGetGroupID(FloorData* floor) {
    s32 lang = fn_801231D4();
    if (floor == 0) {
        return 0;
    }
    return floor->groupID[lang];
}

u32 floorDataBiosGetFloorKind(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    if (floor->kind == 2 && fightGetFightEncountDataId() == 0) {
        if (pokecoloGetRomVersion() == 2) {
            return 4;
        }
        return 1;
    }
    return floor->kind;
}

u32 floorDataBiosGetMapResID(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    return floor->mapResID;
}

u8 floorDataBiosGetArea(FloorData* floor) {
    if (floor == 0) {
        return 0;
    }
    return floor->area;
}

FloorData* floorDataBiosGetCurrentPtr(void) {
    return floorDataBiosGetPtr(GSfloorGetCurrent());
}

FloorData* floorDataBiosGetPtr(u32 key) {
    FloorData* data = floordata;
    u32 n = *floordata_number;
    while (n--) {
        if (data->floorID == key) {
            return data;
        }
        data++;
    }
    return 0;
}

s32 fn_801231D4(void) {
    switch (pokecoloGetLanguage()) {
    case 2:
        return 0;
    case 3:
        return 1;
    case 4:
        return 2;
    case 5:
        return 3;
    case 6:
        return 4;
    default:
        return 0;
    }
}

}  // extern "C"
