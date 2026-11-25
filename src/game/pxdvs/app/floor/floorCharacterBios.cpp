#include <game/pcret.h>
#include <dolphin/types.h>
#include <game/gcdata.h>
#include <game/gcptr.h>
#include <game/pxdvs/app/floor/floorData.h>
#include <game/bitfield.h>
#include <game/pxdvs/app/people/peopleInfo.h>
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
struct GSvec {
    f32 x, y, z;
};
struct floorCharacter_dd_ {
    GC_BITS7(
    u8 visible : 1,
    u8 loadInit : 1,
    u8 isHit : 1,
    u8 flag4 : 1,
    u8 talkWallThrough : 1,
    u8 flag2 : 1, u8 : 2)
    GC_BITS4(
    u8 moveType : 3,
    u8 talkStartType : 2,
    u8 talkEndType : 2, u8 : 1)
    u8 unk2;
    u8 unk3;
    gc_bes16 rotY;
    gc_be16 peopleInfoIndex;
    gc_be16 nameID;
    gc_be32 unkC;
    gc_be32 moveSctID;
    gc_be32 talkSctID;
    gc_bef32 x, y, z;

};

extern "C" {
s32 GSfloorGetCurrent(void);
u8* floorCharacterBiosFindByResID(u32 p0, u32 p1);
FloorCharInfo* floorCharacterBiosGetCurrentPtr(u32 idx);
s32 floorCharacterBiosGetIsHit(u8 *p0);
s32 floorCharacterBiosGetLoadInit(u8 *p0);
s32 floorCharacterBiosGetMoveSctID(void *p0);
s32 floorCharacterBiosGetMoveType(void *p0);
PCRET(u16) floorCharacterBiosGetNameID(void *p0);
GCsptr floorCharacterBiosGetPeopleInfoPtr(void *p0);
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
    GC_BITS2(
    u8 visible : 1, u8 : 7)
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
        ((floorCharacter_dd_*)p0)->x = (f32) M2C_FIELD(p1, f32 *, 0);
        ((floorCharacter_dd_*)p0)->y = (f32) M2C_FIELD(p1, f32 *, 4);
        ((floorCharacter_dd_*)p0)->z = (f32) M2C_FIELD(p1, f32 *, 8);
    }
}
}

extern "C" {
s32 floorCharacterBiosGetTalkSctID(void *p0) {
    if (p0 != NULL) {
        return ((floorCharacter_dd_*)p0)->talkSctID;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetMoveSctID(void *p0) {
    if (p0 != NULL) {
        return ((floorCharacter_dd_*)p0)->moveSctID;
    }
    return 0;
}
}

extern "C" {
PCRET(u16) floorCharacterBiosGetNameID(void *p0) {
    if (p0 != NULL) {
        return ((floorCharacter_dd_*)p0)->nameID;
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
        return ((floorCharacter_dd_*)p0)->talkEndType;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetTalkStartType(void *p0) {
    if (p0 != NULL) {
        return ((floorCharacter_dd_*)p0)->talkStartType;
    }
    return 0;
}
}

extern "C" {
s32 floorCharacterBiosGetMoveType(void *p0) {
    if (p0 != NULL) {
        return ((floorCharacter_dd_*)p0)->moveType;
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
    GSvecSet((GSvec*)p1, 0.0f, 0.017453292f * ((floorCharacter_dd_*)p0)->rotY, 0.0f);
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
    GSvecSet((GSvec*)p1, ((floorCharacter_dd_*)p0)->x, ((floorCharacter_dd_*)p0)->y, ((floorCharacter_dd_*)p0)->z);
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
GCsptr floorCharacterBiosGetPeopleInfoPtr(void *p0) {
    if (p0 != NULL) {
        return (GCsptr)(peopleInfoBiosGetPtrFromIndex(((floorCharacter_dd_*)p0)->peopleInfoIndex));
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
    c.isHit = 1;
    c.flag4 = 1;
    c.talkWallThrough = 1;
    c.flag2 = 1;
    c.moveType = 0;
    c.talkStartType = 2;
    c.talkEndType = 0;
    c.unk2 = 0;
    c.unk3 = 0;
    c.rotY = 0;
    c.peopleInfoIndex = 0;
    c.nameID = 0;
    c.unkC = 0;
    c.moveSctID = 0;
    c.talkSctID = 0;
    c.x = 0.0f;
    c.y = 0.0f;
    c.z = 0.0f;
    c.nameID = 1;
    c.peopleInfoIndex = 2;
    _globalCharacter[0] = c;
    c.nameID = 3;
    c.peopleInfoIndex = 90;
    _globalCharacter[1] = c;
    c.nameID = 0x18;
    c.peopleInfoIndex = 45;
    _globalCharacter[2] = c;
}
}

extern "C" {
PC_KEEP_INLINE inline void GSvecSet(GSvec* v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}
}
