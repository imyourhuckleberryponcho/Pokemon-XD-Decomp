#include <dolphin/types.h>

struct _GSmodel;
struct GSpart;

enum GSmodelAnimType {
    GS_MODEL_ANIM_TYPE_0
};

struct PeopleInfo {
    u8 unk0[0x28];
    char speakParts[7];
    char blinkParts[4];
};

struct tagPeopleWork {
    u8 unk0[8];
    _GSmodel* model;
    u8 unkC[0x10];
    u32 infoID;
    u8 unk20[0x128];
    f32 blinkTimer;
    u8 blinking;
    u8 speaking;
    u8 unk14E[0x42];
    s32 speakAnims[7];
    f32 speakTimer;
};

extern "C" {
PeopleInfo* peopleInfoBiosGetPtr(u32 id);
bool peopleBiosCheckFlag(tagPeopleWork* people, u32 flags);
GSpart* GSmodelGetPart(_GSmodel* model, s32 index);
void GSpartStopAnimIndex(GSpart* part, s32 anim);
s32 GSpartSetAnimIndex(GSpart* part, int anim, GSmodelAnimType type, f32 frame);
void GSpartFree(GSpart* part);
void GSmodelSetKeepPartAnimFlag(_GSmodel* model, s32 flag);
void GSmodelLinkTexAnimToAnim(_GSmodel* model, s32);
void GSmodelSetTexAnimIndex(_GSmodel* model, s32 index);
void GSmodelSetTexAnimType(_GSmodel* model, s32 type);
void GSmodelStartTexAnimation(_GSmodel* model);
u32 HSD_Rand(void);
f32 timeGetLastFrameSec(void);
void peoplePartAnimationBlinkOnce(tagPeopleWork* people);
}

static s32 _peoplePartAnimationStartAnimation(_GSmodel* model, signed char partIndex, int anim, float frame,
                                              GSmodelAnimType type);

extern "C" {

void peoplePartAnimationSpeakStop(tagPeopleWork* people) {
    PeopleInfo* info;
    GSpart* part;
    _GSmodel* model;
    int i;

    if (people != NULL && people->speaking) {
        model = people->model;
        info = peopleInfoBiosGetPtr(people->infoID);
        for (i = 0; i < 7; i++) {
            if (people->speakAnims[i] >= 0) {
                part = GSmodelGetPart(model, info->speakParts[i]);
                if (part != NULL) {
                    GSpartStopAnimIndex(part, people->speakAnims[i]);
                    GSpartFree(part);
                }
                people->speakAnims[i] = -1;
            }
        }
        people->speaking = 0;
    }
}

void peoplePartAnimationSpeakStart(tagPeopleWork* people) {
    PeopleInfo* info;
    bool started = false;
    _GSmodel* model;
    int i;

    if (people == NULL) {
        return;
    }
    model = people->model;
    info = peopleInfoBiosGetPtr(people->infoID);
    if (peopleBiosCheckFlag(people, 0x20000)) {
        return;
    }
    if (people->speaking) {
        return;
    }
    for (i = 0; i < 7; i++) {
        people->speakAnims[i] = _peoplePartAnimationStartAnimation(model, info->speakParts[i], 2, 0.0f, (GSmodelAnimType)1);
        if (people->speakAnims[i] >= 0) {
            started = true;
        }
    }
    if (started) {
        people->speaking = 1;
        GSmodelSetKeepPartAnimFlag(model, 0);
        people->speakTimer = 1.5f;
    }
}

void peoplePartAnimationBlinkStop(tagPeopleWork* people) {
    if (people != NULL) {
        people->blinking = 0;
        if (people->model != NULL) {
            GSmodelSetKeepPartAnimFlag(people->model, 0);
        }
    }
}

void peoplePartAnimationBlinkStart(tagPeopleWork* people) {
    if (people != NULL && !peopleBiosCheckFlag(people, 0x10000)) {
        people->blinking = 1;
        people->blinkTimer = (s32)(HSD_Rand() & 0x7FFF) / 65536.0f;
    }
}

#pragma dont_inline on
void peoplePartAnimationBlink(tagPeopleWork* people) {
    if (people == NULL) {
        return;
    }
    if (people->speaking) {
        people->speakTimer -= timeGetLastFrameSec();
        if (people->speakTimer < 0.0f) {
            peoplePartAnimationSpeakStop(people);
        }
    }
    if (people->blinking) {
        people->blinkTimer -= timeGetLastFrameSec();
        if (!(people->blinkTimer > 0.0f)) {
            s16 rnd = HSD_Rand() & 0x7FFF;
            people->blinkTimer = 2.0f + rnd / 32768.0f;
            peoplePartAnimationBlinkOnce(people);
        }
    }
}
#pragma dont_inline reset

void peoplePartAnimationBlinkOnce(tagPeopleWork* people) {
    PeopleInfo* info;
    _GSmodel* model;
    int i;

    if (people == NULL) {
        return;
    }
    model = people->model;
    info = peopleInfoBiosGetPtr(people->infoID);
    for (i = 0; i < 4; i++) {
        _peoplePartAnimationStartAnimation(model, info->blinkParts[i], 1, 0.0f, (GSmodelAnimType)0);
    }
    GSmodelLinkTexAnimToAnim(model, 0);
    GSmodelSetTexAnimIndex(model, 1);
    GSmodelSetTexAnimType(model, 0);
    GSmodelStartTexAnimation(model);
}

}

static s32 _peoplePartAnimationStartAnimation(_GSmodel* model, signed char partIndex, int anim, float frame,
                                              GSmodelAnimType type) {
    s32 result = -1;
    if (partIndex >= 0) {
        GSpart* part = GSmodelGetPart(model, partIndex);
        if (part == NULL) {
            return -1;
        }
        result = GSpartSetAnimIndex(part, anim, type, frame);
        GSpartFree(part);
    }
    return result;
}
