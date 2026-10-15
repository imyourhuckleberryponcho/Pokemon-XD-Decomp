#include <dolphin/types.h>

struct PeopleInfo {
    u8 talkSe : 3;
    u8 boundCheck : 1;
    u8 colType : 2;
    u8 unk0 : 2;
    u8 neckIndex;
    u8 chestIndex;
    u8 unk3;
    u32 modelResID;
    f32 walkLength;
    f32 runLength;
    f32 colBallSize;
    f32 neckLeftLimit;
    f32 neckRightLimit;
    f32 neckUpLimit;
    f32 neckDownLimit;
    f32 talkDistance;
    u8 unk28[0xC];
};

extern "C" {

extern u32* peopleInfoData_number;
extern PeopleInfo* peopleInfoData;

void gimmickBoxGetMotion(s32* motion, u8* loop);

bool peopleInfoBiosGetBoundCheck(PeopleInfo* info) {
    if (info != NULL) {
        return info->boundCheck != 0;
    }
    return false;
}

u8 peopleInfoBiosGetTalkSe(PeopleInfo* info) {
    if (info != NULL) {
        return info->talkSe;
    }
    return 0;
}

void peopleInfoBiosGetMotion(PeopleInfo* info, u8 kind, s32* motion, u8* loop) {
    if (info == NULL) {
        return;
    }
    gimmickBoxGetMotion(motion, loop);
    switch (kind) {
    case 0:
        break;
    case 1:
        *motion = 3;
        *loop = 1;
        break;
    case 2:
        *motion = 5;
        *loop = 1;
        break;
    case 3:
        *motion = 8;
        *loop = 1;
        break;
    case 4:
        *motion = 11;
        *loop = 0;
        break;
    case 5:
        *motion = 12;
        *loop = 1;
        break;
    case 6:
        *motion = 13;
        *loop = 0;
        break;
    case 7:
        *motion = 39;
        *loop = 1;
        break;
    case 8:
        *motion = 40;
        *loop = 0;
        break;
    }
}

f32 peopleInfoBiosGetRunLength(PeopleInfo* info) {
    if (info != NULL) {
        return info->runLength;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetWalkLength(PeopleInfo* info) {
    if (info != NULL) {
        return info->walkLength;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetColBallSize(PeopleInfo* info) {
    if (info != NULL) {
        return info->colBallSize;
    }
    return 0.0f;
}

u8 peopleInfoBiosGetColType(PeopleInfo* info) {
    if (info != NULL) {
        return info->colType;
    }
    return 0;
}

f32 peopleInfoBiosGetTalkDistance(PeopleInfo* info) {
    if (info != NULL) {
        return info->talkDistance;
    }
    return 3.0f;
}

f32 peopleInfoBiosGetNeckDownLimit(PeopleInfo* info) {
    if (info != NULL) {
        return 0.017453292f * info->neckDownLimit;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetNeckUpLimit(PeopleInfo* info) {
    if (info != NULL) {
        return 0.017453292f * info->neckUpLimit;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetNeckRightLimit(PeopleInfo* info) {
    if (info != NULL) {
        return 0.017453292f * info->neckRightLimit;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetNeckLeftLimit(PeopleInfo* info) {
    if (info != NULL) {
        return 0.017453292f * info->neckLeftLimit;
    }
    return 0.0f;
}

s32 peopleInfoBiosGetNeckIndex(PeopleInfo* info) {
    if (info != NULL) {
        return (s8)info->neckIndex;
    }
    return -1;
}

s32 peopleInfoBiosGetChestIndex(PeopleInfo* info) {
    if (info != NULL) {
        return (s8)info->chestIndex;
    }
    return -1;
}

u32 peopleInfoBiosGetModelResID(PeopleInfo* info) {
    if (info != NULL) {
        return info->modelResID;
    }
    return 0;
}

PeopleInfo* peopleInfoBiosGetPtrFromIndex(u32 index) {
    if (index >= *peopleInfoData_number) {
        return 0;
    }
    return &peopleInfoData[index];
}

PeopleInfo* peopleInfoBiosGetPtr(u32 modelResID) {
    PeopleInfo* info = peopleInfoData;
    for (u32 i = *peopleInfoData_number; i != 0; i--, info++) {
        if (info->modelResID == modelResID) {
            return info;
        }
    }
    return 0;
}

}
