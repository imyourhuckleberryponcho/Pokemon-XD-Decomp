#include <dolphin/types.h>
#include "game/shared/floor_module.h"

struct GSvec {
    f32 x, y, z;
};

typedef f32 GSmtx[3][4];

struct GSgfxVF {
    u8 data[0x440];
};

struct CCD_BLOCK {
    void* field00;
    u32 field04;
    void* field08;
    void* field0C;
};

struct CCD_RECORD {
    f32 pos[3];
    f32 rot[3];
    f32 scale[3];
    CCD_BLOCK* block24;
    CCD_BLOCK* block28;
    CCD_BLOCK* block2C;
    CCD_BLOCK* block30;
    CCD_BLOCK* block34;
    CCD_BLOCK* block38;
    u32 unk3C;
};

struct CCD_FILEHEAD {
    CCD_RECORD* records;
    u32 count;
};

struct GSCOLSYS2_OBJ {
    f32 pos[3];
    f32 rot[3];
    f32 scale[3];
    u16 flags;
    GSCOLSYS2_OBJ() {}
};

struct GSCOLSYS2_ATTR {
    u8 unk0[0x10];
    u16 flags;
    u8 pad12[2];
};

struct GSCOLSYS2_FLOOR {
    GSCOLSYS2_OBJ objs[64];
    GSCOLSYS2_ATTR attrs[48];
};

struct GScolsys2Data {
    CCD_FILEHEAD* head;
    GSCOLSYS2_FLOOR floors[1];
    s32 cur;
    GSgfxVF* vf;
    void* dl;
};

struct StateData {
    u16 magic;
    u16 pad;
    u16 flags[64];
};

extern "C" {
extern GSmtx mtxIdent;
void* memcpy(void* dst, const void* src, unsigned long n);
void PSMTXRotRad(GSmtx m, char axis, f32 rad);
void PSMTXConcat(const GSmtx a, const GSmtx b, GSmtx ab);
void PSMTXScaleApply(const GSmtx src, GSmtx dst, f32 x, f32 y, f32 z);
void PSMTXTransApply(const GSmtx src, GSmtx dst, f32 x, f32 y, f32 z);
void GSgfxDLFree(void* dl);
void GSgfxVFInit(GSgfxVF* vf);
void GSgfxVFCreate(GSgfxVF* vf);
void GSgfxVFSetElement(GSgfxVF* vf, s32, s32, s32, s32);
void FloorModuleInterface_clear(FloorModuleInterface*);
s32 floorRegisterModule(u8 kind, u32 id, FloorModuleInterface* module);
}

GScolsys2Data GScolsys2;
FloorModuleInterface _floorModuleColsys;
static GSgfxVF _colsysVF;
s32 _hModuleField;

static const char* _gscolsysGetModuleName();
static u32 _gscolsysGetUID();
static u32 _gscolsysGetStateSize(FloorStateMode mode);
static void _gscolsysRestoreStateData(FloorStateMode mode, void* data, unsigned long size);
static void _gscolsysMakeStateData(FloorStateMode mode, void* data, unsigned long size);

static inline s32 getObj(s32 index, GSCOLSYS2_OBJ*& out) {
    if (GScolsys2.head == 0) {
        return 1;
    }
    if (index < 0 || (u32)index >= GScolsys2.head->count) {
        return 2;
    }
    u8* t = (u8*)&GScolsys2 + GScolsys2.cur * sizeof(GSCOLSYS2_FLOOR);
    t = t + 4;
    t = t + index * sizeof(GSCOLSYS2_OBJ);
    out = (GSCOLSYS2_OBJ*)t;
    return 0;
}

extern "C" {

f32 GScolsy2UtilGetSidePlanePoint(GSvec* normal, GSvec* a, GSvec* b) {
    return normal->x * (b->x - a->x) + normal->y * (b->y - a->y) + normal->z * (b->z - a->z);
}

s32 GScolsys2GetObjEnable(s32 index, bool* enable) {
    GSCOLSYS2_OBJ* obj;
    s32 result = getObj(index, obj);
    if (result != 0) {
        return result;
    }
    if (obj->flags & 1) {
        *enable = false;
    } else {
        *enable = true;
    }
    return 0;
}

s32 GScolsys2SetObjEnable(s32 index, bool enable) {
    GSCOLSYS2_OBJ* obj;
    s32 result = getObj(index, obj);
    if (result != 0) {
        return result;
    }
    if (enable) {
        obj->flags &= ~1;
    } else {
        obj->flags |= 1;
    }
    return 0;
}

s32 GScolsys2GetObjRotMatrix(GSmtx m, u32 index) {
    GSmtx mx, my, mz;
    GSCOLSYS2_OBJ* obj;

    if (GScolsys2.head == 0) {
        return 0;
    }
    if (index >= GScolsys2.head->count) {
        return 0;
    }
    u8* t = (u8*)&GScolsys2 + GScolsys2.cur * sizeof(GSCOLSYS2_FLOOR);
    u8* u = t + 4;
    u = u + index * sizeof(GSCOLSYS2_OBJ);
    obj = (GSCOLSYS2_OBJ*)u;
    memcpy(m, mtxIdent, sizeof(GSmtx));
    if (obj->flags & 1) {
        PSMTXRotRad(mx, 'X', obj->rot[0]);
        PSMTXRotRad(my, 'Y', obj->rot[1]);
        PSMTXConcat(my, mx, mx);
        PSMTXRotRad(mz, 'Z', obj->rot[2]);
        PSMTXConcat(mz, mx, mx);
        PSMTXConcat(mx, m, m);
    }
    return 1;
}

s32 GScolsys2GetObjMatrix(GSmtx m, u32 index) {
    GSmtx mx, my, mz;
    GSCOLSYS2_OBJ* obj;

    if (GScolsys2.head == 0) {
        return 0;
    }
    if (index >= GScolsys2.head->count) {
        return 0;
    }
    u8* t = (u8*)&GScolsys2 + GScolsys2.cur * sizeof(GSCOLSYS2_FLOOR);
    u8* u = t + 4;
    u = u + index * sizeof(GSCOLSYS2_OBJ);
    obj = (GSCOLSYS2_OBJ*)u;
    memcpy(m, mtxIdent, sizeof(GSmtx));
    if (obj->flags & 1) {
        PSMTXScaleApply(m, m, obj->scale[0], obj->scale[1], obj->scale[2]);
        PSMTXRotRad(mx, 'X', obj->rot[0]);
        PSMTXRotRad(my, 'Y', obj->rot[1]);
        PSMTXConcat(my, mx, mx);
        PSMTXRotRad(mz, 'Z', obj->rot[2]);
        PSMTXConcat(mz, mx, mx);
        PSMTXConcat(mx, m, m);
        PSMTXTransApply(m, m, obj->pos[0], obj->pos[1], obj->pos[2]);
    }
    return 1;
}

CCD_FILEHEAD* GScolsys2GetCCDFileHead(void) {
    return GScolsys2.head;
}

GSCOLSYS2_FLOOR* GScolsys2GetCurFloor(void) {
    if (GScolsys2.cur < 0 || GScolsys2.cur >= 1) {
        return 0;
    }
    return &GScolsys2.floors[GScolsys2.cur];
}

s32 GScolsys2UnloadCCD(void) {
    GScolsys2.head = 0;
    if (GScolsys2.dl != 0) {
        GSgfxDLFree(GScolsys2.dl);
        GScolsys2.dl = 0;
    }
    return 1;
}

}

static void _offsetCCD(CCD_FILEHEAD* head) {
    CCD_RECORD* record;
    CCD_BLOCK* block;
    u32 i;

    if (head == 0) {
        return;
    }
    head->records = (CCD_RECORD*)((u32)head->records + (u32)head);
    record = head->records;

    for (i = 0; i < head->count; i++, record++) {
        if (record->block24 != 0) {
            record->block24 = (CCD_BLOCK*)((u32)record->block24 + (u32)head);
            block = record->block24;
            if (block->field00 != 0) {
                block->field00 = (void*)((u32)block->field00 + (u32)head);
            }
            if (block->field08 != 0) {
                block->field08 = (void*)((u32)block->field08 + (u32)head);
            }
            if (block->field0C != 0) {
                block->field0C = (void*)((u32)block->field0C + (u32)head);
            }
        }
        if (record->block28 != 0) {
            record->block28 = (CCD_BLOCK*)((u32)record->block28 + (u32)head);
            block = record->block28;
            if (block->field00 != 0) {
                block->field00 = (void*)((u32)block->field00 + (u32)head);
            }
            if (block->field08 != 0) {
                block->field08 = (void*)((u32)block->field08 + (u32)head);
            }
            if (block->field0C != 0) {
                block->field0C = (void*)((u32)block->field0C + (u32)head);
            }
        }
        if (record->block2C != 0) {
            record->block2C = (CCD_BLOCK*)((u32)record->block2C + (u32)head);
            block = record->block2C;
            if (block->field00 != 0) {
                block->field00 = (void*)((u32)block->field00 + (u32)head);
            }
            if (block->field08 != 0) {
                block->field08 = (void*)((u32)block->field08 + (u32)head);
            }
            if (block->field0C != 0) {
                block->field0C = (void*)((u32)block->field0C + (u32)head);
            }
        }
        if (record->block30 != 0) {
            record->block30 = (CCD_BLOCK*)((u32)record->block30 + (u32)head);
            block = record->block30;
            if (block->field00 != 0) {
                block->field00 = (void*)((u32)block->field00 + (u32)head);
            }
        }
        if (record->block34 != 0) {
            record->block34 = (CCD_BLOCK*)((u32)record->block34 + (u32)head);
            block = record->block34;
            if (block->field00 != 0) {
                block->field00 = (void*)((u32)block->field00 + (u32)head);
            }
            if (block->field08 != 0) {
                block->field08 = (void*)((u32)block->field08 + (u32)head);
            }
            if (block->field0C != 0) {
                block->field0C = (void*)((u32)block->field0C + (u32)head);
            }
        }
        if (record->block38 != 0) {
            record->block38 = (CCD_BLOCK*)((u32)record->block38 + (u32)head);
            block = record->block38;
            if (block->field00 != 0) {
                block->field00 = (void*)((u32)block->field00 + (u32)head);
            }
        }
    }
}

extern "C" {

s32 GScolsys2LoadCCD(CCD_FILEHEAD* head) {
    GSCOLSYS2_FLOOR* floor;
    CCD_RECORD* src;
    GSCOLSYS2_OBJ* dst;
    u32 i;

    if (GScolsys2.cur < 0) {
        return 0;
    }
    floor = &GScolsys2.floors[GScolsys2.cur];
    for (int k = 0; k < 48; k++) {
        floor->attrs[k].flags &= ~1;
    }
    _offsetCCD(head);
    GScolsys2.head = head;
    if (head != 0) {
        src = head->records;
        dst = GScolsys2.floors[GScolsys2.cur].objs;
        for (i = 0; i < head->count; i++, src++, dst++) {
            dst->pos[0] = src->pos[0];
            dst->pos[1] = src->pos[1];
            dst->pos[2] = src->pos[2];
            dst->rot[0] = src->rot[0];
            dst->rot[1] = src->rot[1];
            dst->rot[2] = src->rot[2];
            dst->scale[0] = src->scale[0];
            dst->scale[1] = src->scale[1];
            dst->scale[2] = src->scale[2];
            dst->flags = 0;
        }
    }
    return 1;
}

}

static const char* _gscolsysGetModuleName() {
    return "GScolsys";
}

static u32 _gscolsysGetUID() {
    return 0x14;
}

static u32 _gscolsysGetStateSize(FloorStateMode mode) {
    if (mode == FLOOR_STATE_MODE_1 || mode == FLOOR_STATE_MODE_2) {
        return sizeof(GSCOLSYS2_FLOOR);
    }
    if (mode == FLOOR_STATE_MODE_3) {
        return sizeof(StateData);
    }
    return 0;
}

static void _gscolsysRestoreStateData(FloorStateMode mode, void* data, unsigned long size) {
    s32 i;

    if (mode == FLOOR_STATE_MODE_1 || mode == FLOOR_STATE_MODE_2) {
        if (size == sizeof(GSCOLSYS2_FLOOR)) {
            memcpy(GScolsys2.floors, data, sizeof(GSCOLSYS2_FLOOR));
        }
    } else if (mode == FLOOR_STATE_MODE_3) {
        data = (u8*)data + 4;
        u16* src = (u16*)data;
        for (int i = 0; i < 64; i++) {
            GScolsys2.floors[0].objs[i].flags = src[i];
        }
    }
}

static void _gscolsysMakeStateData(FloorStateMode mode, void* data, unsigned long size) {
    s32 i;

    if (mode == FLOOR_STATE_MODE_1 || mode == FLOOR_STATE_MODE_2) {
        if (size == sizeof(GSCOLSYS2_FLOOR)) {
            memcpy(data, GScolsys2.floors, sizeof(GSCOLSYS2_FLOOR));
        }
    } else if (mode == FLOOR_STATE_MODE_3) {
        StateData* state = (StateData*)data;
        u16* dst = state->flags;
        state->magic = 0xAA55;
        state->pad = 0;
        for (int i = 0; i < 64; i++) {
            *dst++ = GScolsys2.floors[0].objs[i].flags;
        }
    }
}

extern "C" void GScolsys2Init(void) {
    GScolsys2.cur = 0;
    GScolsys2.dl = 0;
    GSgfxVFInit(&_colsysVF);
    GSgfxVFCreate(&_colsysVF);
    GScolsys2.vf = &_colsysVF;
    GSgfxVFSetElement(&_colsysVF, 9, 1, 4, 0);
    GSgfxVFSetElement(GScolsys2.vf, 11, 1, 5, 0);
    FloorModuleInterface_clear(&_floorModuleColsys);
    _floorModuleColsys.makeStateData = _gscolsysMakeStateData;
    _floorModuleColsys.restoreStateData = _gscolsysRestoreStateData;
    _floorModuleColsys.getStateSize = _gscolsysGetStateSize;
    _floorModuleColsys.getUID = _gscolsysGetUID;
    _floorModuleColsys.getModuleName = _gscolsysGetModuleName;
    _hModuleField = floorRegisterModule(0x14, 0, &_floorModuleColsys);
}
