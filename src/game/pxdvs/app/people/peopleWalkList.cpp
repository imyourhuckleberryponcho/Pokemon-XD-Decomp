#include <dolphin/types.h>

struct Vec {
    f32 x, y, z;
};

struct People {
    u8 unk0[0x20];
    f32 unk20;
    u8 unk24[4];
    f32 unk28;
    u8 unk2C[0x28];
    u8 moveMode;
    u8 walkListActive;
    u8 unk56[0x1E];
    u16 walkListMax;
    u16 walkListNum;
    Vec* walkList;
    u8 walkListStrict;
};

extern "C" {

People* peopleGet(s32 group, s32 id);
void peopleSetFlagOn(s32 group, s32 id, u32 flag);
void _peopleSetMoveAnimation(People* people);
void GSmemFree(void* ptr);
void* GSmemAllocClr(u32 size);

BOOL peopleFreeWalkList(s32 group, s32 id) {
    People* people = peopleGet(group, id);
    if (people == NULL) {
        return FALSE;
    }
    if (people->walkList != NULL) {
        if (people->walkList != NULL) {
            GSmemFree(people->walkList);
            people->walkList = NULL;
        }
        people->moveMode = 0;
        people->walkListMax = 0;
        people->walkListNum = 0;
        people->walkListActive = 0;
    }
    return TRUE;
}

BOOL peopleStartWalkList(s32 group, s32 id, u32 loop) {
    People* people = peopleGet(group, id);
    if (people == NULL) {
        return FALSE;
    }
    peopleSetFlagOn(group, id, 8);
    people->walkListActive = 0;
    people->walkListNum = 0;
    people->unk28 = people->unk20;
    people->walkListActive = 1;
    if (loop) {
        people->moveMode = 3;
    } else {
        people->moveMode = 2;
    }
    people->walkListStrict = 0;
    _peopleSetMoveAnimation(people);
    return TRUE;
}

BOOL peopleStartWalkListStrict(s32 group, s32 id, u32 loop) {
    People* people = peopleGet(group, id);
    if (people == NULL) {
        return FALSE;
    }
    peopleSetFlagOn(group, id, 8);
    people->walkListActive = 0;
    people->walkListNum = 0;
    people->unk28 = people->unk20;
    people->walkListActive = 1;
    if (loop) {
        people->moveMode = 3;
    } else {
        people->moveMode = 2;
    }
    people->walkListStrict = 1;
    _peopleSetMoveAnimation(people);
    return TRUE;
}

BOOL peopleAddWalkList(s32 group, s32 id, f32 x, f32 y, f32 z) {
    People* people = peopleGet(group, id);
    Vec* point;
    if (people == NULL) {
        return FALSE;
    }
    if (people->walkList == NULL) {
        return FALSE;
    }
    if (people->walkListNum >= people->walkListMax) {
        return FALSE;
    }
    point = &people->walkList[people->walkListNum];
    point->x = x;
    point->y = y;
    point->z = z;
    people->walkListNum++;
    return TRUE;
}

#pragma dont_inline on
BOOL peopleInitWalkList(s32 group, s32 id, u16 max) {
    People* people = peopleGet(group, id);
    if (people == NULL) {
        return FALSE;
    }
    peopleFreeWalkList(group, id);
    people->walkList = (Vec*)GSmemAllocClr(max * sizeof(Vec));
    if (people->walkList == NULL) {
        return FALSE;
    }
    people->walkListMax = max;
    people->walkListNum = 0;
    people->walkListActive = 0;
    return TRUE;
}
#pragma dont_inline reset

}
