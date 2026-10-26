#include <dolphin/types.h>
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
struct FloorCharInfo;
struct FloorData;
struct PeopleInfo;
struct floorCharacter_dd_;

extern "C" {
struct FloorCharInfo {
    u8 _draft[1];
};
struct FloorData {
    u8 _draft[1];
};
struct PeopleInfo {
    u8 _draft[1];
};
struct GSvec {
    f32 x, y, z;
};
struct floorCharacter_dd_ {
    u8 visible : 1;
    u8 flag6 : 1;
    u8 flag5 : 1;
    u8 flag4 : 1;
    u8 flag3 : 1;
    u8 flag2 : 1;
    u8 kind : 3;
    u8 mode : 2;
    u8 mode2 : 2;
    u8 unk2;
    u8 unk3;
    s16 unk4;
    u16 angle;
    u16 resID;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    f32 x, y, z;

};

extern "C" {
s32 GSfloorGetCurrent(void);
u8* floorCharacterBiosFindByResID(u32 p0, u32 p1);
FloorCharInfo* floorCharacterBiosGetCurrentPtr(u32 idx);
s32 floorCharacterBiosGetIsHit(u8 *p0);
s32 floorCharacterBiosGetLoadInit(u8 *p0);
s32 floorCharacterBiosGetMoveSctID(void *p0);
s32 floorCharacterBiosGetMoveType(void *p0);
u16 floorCharacterBiosGetNameID(void *p0);
s32 floorCharacterBiosGetPeopleInfoPtr(void *p0);
s32 floorCharacterBiosGetPos(void *p0, void *p1);
FloorCharInfo* floorCharacterBiosGetPtr(u32 key, u32 idx);
s32 floorCharacterBiosGetRot(void *p0, void *p1);
s32 floorCharacterBiosGetTalkEndType(void *p0);
s32 floorCharacterBiosGetTalkSctID(void *p0);
s32 floorCharacterBiosGetTalkStartType(void *p0);
s32 floorCharacterBiosGetTalkWallThrough(u8 *p0);
s32 floorCharacterBiosGetVisibility(u8 *p0);
void floorCharacterBiosInitGlobalCharacter();
void floorCharacterBiosSetPos(void *p0, void *p1);
void floorCharacterBiosSetVisibility(u8* p0, bool visible);
FloorCharInfo* floorDataBiosGetCharInfo(FloorData* floor, u32 idx);
u32 floorDataBiosGetGroupID(FloorData* floor);
FloorData* floorDataBiosGetPtr(u32 key);
void* memset(void* dst, int val, size_t n);
PeopleInfo* peopleInfoBiosGetPtrFromIndex(u32 index);
}
static floorCharacter_dd_ _globalCharacter[3];
void GSvecSet(GSvec* v, f32 x, f32 y, f32 z);
struct FloorCharFlags {
    u8 visible : 1;
};

void floorCharacterBiosSetVisibility(u8* p0, bool visible) {
    FloorCharFlags* c = (FloorCharFlags*)p0;
    if (c != NULL) {
        c->visible = visible;
    }
}
}

extern "C" {
void floorCharacterBiosSetPos(void *p0, void *p1) {
    if ((p0 != NULL) && (p1 != NULL)) {
        M2C_FIELD(p0, f32 *, 0x18) = (f32) M2C_FIELD(p1, f32 *, 0);
        M2C_FIELD(p0, f32 *, 0x1C) = (f32) M2C_FIELD(p1, f32 *, 4);
        M2C_FIELD(p0, f32 *, 0x20) = (f32) M2C_FIELD(p1, f32 *, 8);
    }
}
}

extern "C" {
s32 floorCharacterBiosGetTalkSctID(void *p0) {
    if (p0 != NULL) {
        return M2C_FIELD(p0, s32 *, 0x14);
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetMoveSctID(void *p0) {
    if (p0 != NULL) {
        return M2C_FIELD(p0, s32 *, 0x10);
    }
    return 0;
}
}

extern "C" {
u16 floorCharacterBiosGetNameID(void *p0) {
    if (p0 != NULL) {
        return M2C_FIELD(p0, u16 *, 8);
    }
    return 0U;
}
}

extern "C" {
s32 floorCharacterBiosGetTalkWallThrough(u8 *p0) {
    if (p0 != NULL) {
        return (((u8) *p0 >> 3U) & 1) != 0;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetTalkEndType(void *p0) {
    if (p0 != NULL) {
        return ((u8) M2C_FIELD(p0, u8 *, 1) >> 1U) & 3;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetTalkStartType(void *p0) {
    if (p0 != NULL) {
        return ((u8) M2C_FIELD(p0, u8 *, 1) >> 3U) & 3;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetMoveType(void *p0) {
    if (p0 != NULL) {
        return ((u8) M2C_FIELD(p0, u8 *, 1) >> 5U) & 7;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetRot(void* p0, void* p1) {
    if (p0 == NULL) {
        return 0;
    }
    if (p1 == NULL) {
        return 0;
    }
    GSvecSet((GSvec*)p1, 0.0f, 0.017453292f * *(s16*)((u8*)p0 + 4), 0.0f);
    return 1;
}
}

extern "C" {
s32 floorCharacterBiosGetPos(void* p0, void* p1) {
    if (p0 == NULL) {
        return 0;
    }
    if (p1 == NULL) {
        return 0;
    }
    GSvecSet((GSvec*)p1, *(f32*)((u8*)p0 + 0x18), *(f32*)((u8*)p0 + 0x1C), *(f32*)((u8*)p0 + 0x20));
    return 1;
}
}

extern "C" {
s32 floorCharacterBiosGetIsHit(u8 *p0) {
    if (p0 != NULL) {
        return (((u8) *p0 >> 5U) & 1) != 0;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetLoadInit(u8 *p0) {
    if (p0 != NULL) {
        return (((u8) *p0 >> 6U) & 1) != 0;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetVisibility(u8 *p0) {
    if (p0 != NULL) {
        return (((u8) *p0 >> 7U) & 1) != 0;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetPeopleInfoPtr(void *p0) {
    if (p0 != NULL) {
        return (long)(peopleInfoBiosGetPtrFromIndex((u32) M2C_FIELD(p0, u16 *, 6)));
    }
    return 0;
}
}

extern "C" {
u8* floorCharacterBiosFindByResID(u32 groupID, u32 id) {
    FloorData* floor;
    if (groupID == 0) {
        if (id == 0x65) {
            return (u8*)&_globalCharacter[0];
        }
        if (id == 0x69) {
            return (u8*)&_globalCharacter[1];
        }
        if (id == 0x68) {
            return (u8*)&_globalCharacter[2];
        }
        return NULL;
    }
    floor = floorDataBiosGetPtr(GSfloorGetCurrent());
    if (groupID != floorDataBiosGetGroupID(floor)) {
        return NULL;
    }
    return (u8*)floorDataBiosGetCharInfo(floor, id);
}
}

extern "C" {
FloorCharInfo* floorCharacterBiosGetCurrentPtr(u32 idx) {
    return floorCharacterBiosGetPtr(GSfloorGetCurrent(), idx);
}
}

extern "C" {
FloorCharInfo* floorCharacterBiosGetPtr(u32 key, u32 idx) {
    return floorDataBiosGetCharInfo(floorDataBiosGetPtr(key), idx);
}
}

extern "C" {
void floorCharacterBiosInitGlobalCharacter() {
    floorCharacter_dd_ c;

    memset(_globalCharacter, 0, sizeof(_globalCharacter));
    memset(&c, 0, sizeof(c));
    c.visible = 1;
    c.flag5 = 1;
    c.flag4 = 1;
    c.flag3 = 1;
    c.flag2 = 1;
    c.kind = 0;
    c.mode = 2;
    c.mode2 = 0;
    c.unk2 = 0;
    c.unk3 = 0;
    c.unk4 = 0;
    c.angle = 0;
    c.resID = 0;
    c.unkC = 0;
    c.unk10 = 0;
    c.unk14 = 0;
    c.x = 0.0f;
    c.y = 0.0f;
    c.z = 0.0f;
    c.resID = 1;
    c.angle = 2;
    _globalCharacter[0] = c;
    c.resID = 3;
    c.angle = 90;
    _globalCharacter[1] = c;
    c.resID = 0x18;
    c.angle = 45;
    _globalCharacter[2] = c;
}
}

extern "C" {
inline void GSvecSet(GSvec* v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}
}
