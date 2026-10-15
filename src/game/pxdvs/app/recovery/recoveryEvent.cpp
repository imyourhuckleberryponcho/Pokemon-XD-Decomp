#include <dolphin/types.h>

struct Vec {
    f32 x, y, z;
};

struct GSmodel;
struct GSpart;
struct Pokemon;

struct People {
    u8 unk0[8];
    GSmodel* model;
};

class FloorBgmMask {
public:
    void stopMask();
};

extern "C" {
void recoveryPokemon(void);
void fadeSet(s32 type, f32 time);
void fadeCheck(s32);
void soundOpenPlayME(u32 id, u32, u8 volume);
void heroMovePoolCounter(s32, u32);
FloorBgmMask* floorSound_getBgmMaskObj(void);
u32 floorGetCurrentGroupID(void);
GSmodel* GSresGetResource(u32 group, u32 id);
People* peopleGet(s32 group, s32 id);
void* savedataGetStatus(s32, s32);
u32 heroGetPokeomCount(void);
u8 revoceryCatchPokemonBall(u16 index);
GSmodel* floorOpenObject(u32 id);
void GSmodelSetVisibility(GSmodel* model, s32 visible);
void GSmodelGetRotation(GSmodel* model, Vec* rot);
void peopleRotateToTarget(s32 group, s32 id, u32 targetGroup, u32 targetID, f32 time);
void peopleMoveCheck(s32 group, s32 id, s32);
Pokemon* heroBiosGetPokemonPtr(void* party, u16 index);
void pokemonAllKaihuku(Pokemon* pokemon);
GSpart* GSmodelGetPart(GSmodel* model, u32 id);
void GSpartGetTransform(GSpart* part, Vec* pos, Vec* rot, Vec* scale);
void GSpartFree(GSpart* part);
void GSmodelSetPosition(GSmodel* model, Vec* pos);
void scriptWaitTime(f32 time);
void scriptModelSetMotion(u32 id, u32 motion, s32, s32);
bool GSmodelIsAnimating(GSmodel* model);
void GSthreadSwitch(void);
void GSmodelFree(GSmodel* model);
void soundContinueBGMEX(u32 bgm, u32 time, s32);
void peopleRotateToAngle(s32 group, s32 id, f32 angle, f32 time);
u32 soundPauseBGMEX(u32 time, s32);
void GSsndPlay(u32 id, s32, s32);
}

void _recoveryEventSetME(unsigned long id, unsigned long arg1, unsigned char volume);

static u32 _recoveryPauseBGM(unsigned long time);
static void _recoveryEventSetSE(unsigned long id);

// Ball model for each kind of Poke Ball.
static u32 _recoveryTestBallTable[13] = {
    0x02E50400, 0x02E60400, 0x02E50400, 0x02EC0400, 0x02B70400, 0x18740400, 0x02E70400,
    0x02C10400, 0x18730400, 0x02EA0400, 0x02ED0400, 0x18720400, 0x02E90400,
};

extern "C" {

void recoveryEventCommon(u32 counter) {
    recoveryPokemon();
    fadeSet(3, 1.0f);
    fadeCheck(1);
    soundOpenPlayME(0x3C8, 0, 0x7F);
    fadeSet(2, 1.0f);
    fadeCheck(1);
    heroMovePoolCounter(3, counter);
}

void recoveryEventPC(s32 group, s32 id, u32 machineID, u32* ballParts, u32* motions) {
    u32 bgm;
    u32 count;
    People* people;
    GSmodel* machine;
    void* party;
    bool hasPeople;
    FloorBgmMask* mask;
    GSpart* part;
    u32 i;
    Vec pos;
    Vec rot;
    GSmodel* balls[6];

    pos.x = 0.0f;
    pos.y = 10.0f;
    pos.z = 0.0f;
    mask = floorSound_getBgmMaskObj();
    machine = GSresGetResource(floorGetCurrentGroupID(), machineID);
    people = peopleGet(group, id);
    party = savedataGetStatus(0, 2);
    count = heroGetPokeomCount();
    hasPeople = people != NULL;

    for (i = 0; i < count; i++) {
        balls[i] = floorOpenObject(_recoveryTestBallTable[revoceryCatchPokemonBall(i)]);
        GSmodelSetVisibility(balls[i], 0);
    }
    if (hasPeople) {
        GSmodelGetRotation(people->model, &rot);
        peopleRotateToTarget(group, id, floorGetCurrentGroupID(), machineID, 1.0f);
        peopleMoveCheck(group, id, 1);
    }
    if (mask != NULL) {
        mask->stopMask();
    }
    bgm = _recoveryPauseBGM(500);
    for (i = 0; i < count; i++) {
        pokemonAllKaihuku(heroBiosGetPokemonPtr(party, i));
        part = GSmodelGetPart(machine, ballParts[i]);
        GSpartGetTransform(part, &pos, NULL, NULL);
        GSpartFree(part);
        GSmodelSetPosition(balls[i], &pos);
        GSmodelSetVisibility(balls[i], 1);
        _recoveryEventSetSE(0x19);
        scriptWaitTime(0.5f);
    }
    for (i = 0; i < count; i++) {
        scriptModelSetMotion(machineID, motions[i], 0, 0);
    }
    _recoveryEventSetME(0x3C8, 0, 0xFF);
    while (GSmodelIsAnimating(machine)) {
        GSthreadSwitch();
    }
    scriptModelSetMotion(machineID, motions[6], 0, 1);
    for (i = 0; i < count; i++) {
        if (balls[i] != NULL) {
            GSmodelSetVisibility(balls[i], 0);
            GSmodelFree(balls[i]);
        }
    }
    scriptWaitTime(0.7f);
    soundContinueBGMEX(bgm, 1000, 0);
    if (hasPeople && group != 0U && id != 100U) {
        peopleRotateToAngle(group, id, rot.y, 1.0f);
        peopleMoveCheck(group, id, 1);
    }
}

}

static u32 _recoveryPauseBGM(unsigned long time) {
    return soundPauseBGMEX(time, 0);
}

static void _recoveryEventSetSE(unsigned long id) {
    GSsndPlay(id, 0, 0);
}

void _recoveryEventSetME(unsigned long id, unsigned long arg1, unsigned char volume) {
    soundOpenPlayME(id, arg1, volume);
}
