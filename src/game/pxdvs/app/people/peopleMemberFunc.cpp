#include <dolphin/types.h>

struct GSmodel;

enum GSmodelAnimType {
    GS_MODEL_ANIM_TYPE_0
};

struct PeopleInfo {
    u8 unk0_0 : 6;
    u8 noWalkStart : 1;
    u8 unk0_7 : 1;
};

struct tagPeopleWork;

extern "C" {
bool GSmodelIsNullAnimation(GSmodel* model, s32 index);
void GSmodelSetAnimType(GSmodel* model, GSmodelAnimType type);
void GSmodelSetAnimFrame(GSmodel* model, f32 frame);
void GSmodelSetAnimBlend(GSmodel* model, int index0, int index1);
void GSmodelSetAnimIndex(GSmodel* model, s32 index);
void GSmodelSetAnimRate(GSmodel* model, f32 rate);
bool GSmodelHasAnimationEnded(GSmodel* model);
void GSmodelGetAnimIndex(GSmodel* model, s32* index, s32* blendIndex);
f32 peopleViewerGetPlaySpeedRate(tagPeopleWork* people);
bool peopleBiosCheckFlag(const tagPeopleWork* people, u32 flags);
PeopleInfo* peopleInfoBiosGetPtr(u32 id);
}

struct tagPeopleWork {
    u8 getMoveType();
    s32 getRunMotion();
    s32 getWalkMotion();
    void setAnimType(GSmodelAnimType type);
    void setAnimFrame(f32 frame);
    void setAnimBlend(int index0, int index1);
    void setAnimIndex(int index);
    void setAnimRate(f32 rate, bool scaleBySpeed);
    bool isAnimLast() const;
    u32 getFlags() const;
    bool checkFlags(unsigned long flags) const;
    bool isWalkStartMotion() const;
    bool isAlwayBlendChara() const;

    u8 unk0[8];
    GSmodel* model;
    u8 unkC[4];
    u32 flags;
    u8 unk14[8];
    u32 infoID;
    u8 unk20[0x34];
    u8 moveType;
    u8 unk55[0x10F];
    s32 walkStartMotion;
    s32 walkMotion;
    s32 runMotion;
    s32 walkStartMotion2;
    s32 walkStartMotion3;
};

u8 tagPeopleWork::getMoveType() {
    return moveType;
}

s32 tagPeopleWork::getRunMotion() {
    int first = runMotion;
    s32 second;
    if (first >= 0 && !GSmodelIsNullAnimation(model, first)) {
        return first;
    }
    second = walkMotion;
    if (second >= 0 && !GSmodelIsNullAnimation(model, second)) {
        return second;
    }
    return 3;
}

s32 tagPeopleWork::getWalkMotion() {
    int first = walkMotion;
    s32 second;
    if (first >= 0 && !GSmodelIsNullAnimation(model, first)) {
        return first;
    }
    second = runMotion;
    if (second >= 0 && !GSmodelIsNullAnimation(model, second)) {
        return second;
    }
    return 3;
}

void tagPeopleWork::setAnimType(GSmodelAnimType type) {
    if (model != NULL) {
        GSmodelSetAnimType(model, type);
    }
}

void tagPeopleWork::setAnimFrame(f32 frame) {
    if (model != NULL) {
        if (frame < 0.0f) {
            frame = 0.0f;
        }
        GSmodelSetAnimFrame(model, frame);
    }
}

void tagPeopleWork::setAnimBlend(int index0, int index1) {
    if (model == NULL) {
        return;
    }
    if (GSmodelIsNullAnimation(model, index0)) {
        return;
    }
    if (GSmodelIsNullAnimation(model, index1)) {
        setAnimIndex(index0);
    } else {
        GSmodelSetAnimBlend(model, index0, index1);
    }
}

void tagPeopleWork::setAnimIndex(int index) {
    if (model != NULL) {
        GSmodelSetAnimIndex(model, index);
    }
}

void tagPeopleWork::setAnimRate(f32 rate, bool scaleBySpeed) {
    if (model != NULL && !checkFlags(0x8000)) {
        if (scaleBySpeed) {
            rate *= peopleViewerGetPlaySpeedRate(this);
        }
        GSmodelSetAnimRate(model, rate);
    }
}

bool tagPeopleWork::isAnimLast() const {
    if (model == NULL) {
        return false;
    }
    return GSmodelHasAnimationEnded(model);
}

u32 tagPeopleWork::getFlags() const {
    return flags;
}

bool tagPeopleWork::checkFlags(unsigned long flags) const {
    return peopleBiosCheckFlag(this, flags);
}

bool tagPeopleWork::isWalkStartMotion() const {
    PeopleInfo* info;
    s32 index;
    s32 blendIndex;

    info = peopleInfoBiosGetPtr(infoID);
    if (info == NULL) {
        return false;
    }
    if (info->noWalkStart) {
        return false;
    }
    GSmodelGetAnimIndex(model, &index, &blendIndex);
    if (blendIndex != -1) {
        return false;
    }
    if (index == walkStartMotion || index == walkStartMotion2 || index == walkStartMotion3) {
        return true;
    }
    return false;
}

// Characters whose animations are always blended.
bool tagPeopleWork::isAlwayBlendChara() const {
    u32 id = infoID;
    if (id == 0x16C90400 || id == 0x169E0400 || id == 0x169F0400 || id == 0x16A00400 || id == 0x20250400 ||
        id == 0x1EE20400 || id == 0x16C70400 || id == 0x195B0400 || id == 0x1A7C0400 || id == 0x19540400) {
        return true;
    }
    return false;
}
