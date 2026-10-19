// Not yet decompiled.
#include <dolphin/types.h>
#pragma peephole off
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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
// ---- draft declarations ----
struct FloorCharInfo {
    u8 _draft[1];
};
struct FloorData {
    u8 _draft[1];
};
struct PeopleInfo {
    u8 _draft[1];
};
struct floorCharacter_dd_ {
    u8 _draft[1];
};

extern "C" {
s32 GSfloorGetCurrent(void);
void GSvecSet(void *p0, s16 p1, f32 p2, f32 p3, f32 p4, f32 p5);
u8* floorCharacterBiosFindByResID(u32 p0, u32 p1);
void floorCharacterBiosGetCurrentPtr(s32 p0);
s32 floorCharacterBiosGetIsHit(u8 *p0);
s32 floorCharacterBiosGetLoadInit(u8 *p0);
s32 floorCharacterBiosGetMoveSctID(void *p0);
s32 floorCharacterBiosGetMoveType(void *p0);
u16 floorCharacterBiosGetNameID(void *p0);
s32 floorCharacterBiosGetPeopleInfoPtr(void *p0);
s32 floorCharacterBiosGetPos(void *p0, void *p1);
void floorCharacterBiosGetPtr(s32 p0);
s32 floorCharacterBiosGetRot(void *p0, void *p1);
s32 floorCharacterBiosGetTalkEndType(void *p0);
s32 floorCharacterBiosGetTalkSctID(void *p0);
s32 floorCharacterBiosGetTalkStartType(void *p0);
s32 floorCharacterBiosGetTalkWallThrough(u8 *p0);
s32 floorCharacterBiosGetVisibility(u8 *p0);
void floorCharacterBiosInitGlobalCharacter();
void floorCharacterBiosSetPos(void *p0, void *p1);
void floorCharacterBiosSetVisibility(u8 *p0, u8 p1);
FloorCharInfo* floorDataBiosGetCharInfo(FloorData* floor, u32 idx);
u32 floorDataBiosGetGroupID(FloorData* floor);
FloorData* floorDataBiosGetPtr(u32 key);
void* memset(void* dst, int val, size_t n);
PeopleInfo* peopleInfoBiosGetPtrFromIndex(u32 index);
}
static u8 _globalCharacter[0x6C];
void floorCharacterBiosSetVisibility(u8 *p0, u8 p1) {
    if (p0 != NULL) {
        *p0 = (*p0 & ~0x80) | ((p1 << 7) & 0x80);
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
s32 floorCharacterBiosGetRot(void *p0, void *p1) {
    s16 temp_r5;

    if (p0 == NULL) {
        return 0;
    }
    if (p1 == NULL) {
        return 0;
    }
    temp_r5 = M2C_FIELD(p0, s16 *, 4);
    GSvecSet(p1, temp_r5 ^ 0x80000000, 0.0f, 0.017453292f * (f32) temp_r5, 0.0f, 0.017453292f);
    return 1;
}
}

extern "C" {
s32 floorCharacterBiosGetPos(void *p0, void *p1) {
    if (p0 == NULL) {
        return 0;
    }
    if (p1 == NULL) {
        return 0;
    }
    GSvecSet(p1, (s16) p1, M2C_FIELD(p0, f32 *, 0x18), M2C_FIELD(p0, f32 *, 0x1C), M2C_FIELD(p0, f32 *, 0x20), M2C_ERROR(/* Read from unset register $f4 */));
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
u8* floorCharacterBiosFindByResID(u32 p0, u32 p1) {
    FloorData *temp_r3;

    if (p0 == 0) {
        switch (p1) {                               /* irregular */
        case 0x65:
            return _globalCharacter;
        case 0x69:
            return &_globalCharacter[0x24];
        case 0x68:
            return &_globalCharacter[0x48];
        default:
            return NULL;
        }
    } else {
        temp_r3 = floorDataBiosGetPtr(GSfloorGetCurrent());
        if (p0 != floorDataBiosGetGroupID((FloorData*)(temp_r3))) {
            return NULL;
        }
        return (unsigned char *)(floorDataBiosGetCharInfo((FloorData*)(temp_r3), p1));
    }
}
}

extern "C" {
void floorCharacterBiosGetCurrentPtr(s32 p0) {
    floorCharacterBiosGetPtr(GSfloorGetCurrent());
}
}

extern "C" {
void floorCharacterBiosGetPtr(s32 p0) {
    floorDataBiosGetCharInfo((FloorData*)(floorDataBiosGetPtr((u32) p0)), M2C_ERROR(/* Read from unset register $r4 */));
}
}

extern "C" {
void floorCharacterBiosInitGlobalCharacter() {
    f32 sp28;
    f32 sp24;
    f32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s16 sp10;
    s16 spE;
    s16 spC;
    s8 spB;
    s8 spA;
    u8 sp9;
    u8 sp8;
    s8 temp_r0;
    s8 temp_r0_2;
    s8 temp_r3;
    s8 temp_r4;
    s8 temp_r4_2;
    s8 temp_r5;

    memset((void*)(_globalCharacter), 0, 0x6CU);
    memset((void*)(&sp8), 0, 0x24U);
    temp_r0 = sp8 | 0x80;
    sp8 = temp_r0;
    temp_r4 = temp_r0 | 0x20;
    temp_r0_2 = sp9 & ~0xE0;
    sp8 = temp_r4;
    temp_r3 = temp_r4 | 0x10;
    sp8 = temp_r3;
    temp_r4_2 = temp_r3 | 8;
    spE = 0;
    temp_r5 = (temp_r0_2 & ~0x18) | 0x10;
    sp9 = temp_r0_2;
    sp8 = temp_r4_2;
    sp9 = temp_r5;
    sp10 = 0;
    sp8 = temp_r4_2 | 4;
    sp9 = temp_r5 & ~6;
    spA = 0;
    spB = 0;
    spC = 0;
    sp14 = 0;
    sp18 = 0;
    sp1C = 0;
    sp20 = 0.0f;
    sp24 = 0.0f;
    sp28 = 0.0f;
    sp10 = 1;
    spE = 2;
    ((floorCharacter_dd_*)((floorCharacter_dd_ *) _globalCharacter))->operator=(*(const floorCharacter_dd_*)((floorCharacter_dd_ *) &sp8));
    sp10 = 3;
    spE = 0x5A;
    ((floorCharacter_dd_*)((floorCharacter_dd_ *) &_globalCharacter[0x24]))->operator=(*(const floorCharacter_dd_*)((floorCharacter_dd_ *) &sp8));
    sp10 = 0x18;
    spE = 0x2D;
    ((floorCharacter_dd_*)((floorCharacter_dd_ *) &_globalCharacter[0x48]))->operator=(*(const floorCharacter_dd_*)((floorCharacter_dd_ *) &sp8));
}
}

extern "C" {
void GSvecSet(void *p0, s16 p1, f32 p2, f32 p3, f32 p4, f32 p5) {
    M2C_FIELD(p0, f32 *, 0) = p2;
    M2C_FIELD(p0, f32 *, 4) = p3;
    M2C_FIELD(p0, f32 *, 8) = p4;
}
}
