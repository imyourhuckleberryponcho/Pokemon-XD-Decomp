#include <dolphin/types.h>

// Script helpers for plain models and people opened from scripts.
// STATUS: 12/15 exact. SetMotion/SetMotionRate: clrlwi of the loop flag is
// scheduled after the r5/r6 moves (target: before); SetParticle: see fcheck.
// Built with -inline deferred: functions are written in reverse object order.
#pragma peephole off

struct _GSmodel;
struct GSpart;
struct GSparticleGenerator;

extern "C" {
s32 floorGetCurrentGroupID();
_GSmodel* GSresGetResource(s32, s32);
u32 peopleGetHumanID(s32, s32);
void* peopleOpen(s32, s32, s32);
void* peopleSearchID(void*);
_GSmodel* peopleBiosGetModelPtr(void*);
void peopleClose(s32, s32, s32);
void peopleSetDisp(s32, s32, u8);
void peopleSetMotionForce(s32, s32, s32, s32, u8);
void peopleStopMotion(s32, s32);
u8 peopleWaitSyncMotion(s32, s32, u8);
void peopleAttach(s32, s32, s32, s32, s32);
void peopleDetach(s32, s32, u8);
void GSthreadSwitch();
void GSmodelSetBoundCheck(_GSmodel*, u8);
void GSmodelSetVisibility(_GSmodel*, u8);
void GSmodelSetAnimIndex(_GSmodel*, s32);
void GSmodelSetAnimFrame(_GSmodel*, f32);
void GSmodelSetAnimRate(_GSmodel*, f32);
void GSmodelSetTexAnimIndex(_GSmodel*, s32);
void GSmodelSetTexAnimFrame(_GSmodel*, f32);
void GSmodelSetTexAnimRate(_GSmodel*, f32);
void GSmodelSetAnimType(_GSmodel*, s32);
void GSmodelStartAnimation(_GSmodel*);
void GSmodelStopAnimation(_GSmodel*);
u8 GSmodelHasAnimationEnded(_GSmodel*);
GSpart* GSmodelGetPart(_GSmodel*, s32);
void GSmodelAttachToGSpart(_GSmodel*, GSpart*, s32, s32, s32);
void GSmodelDetachFromGSpart(_GSmodel*, s32);
void GSpartFree(GSpart*);
void GSmodelLinkToGSparticleBank(_GSmodel*, _GSmodel*);
void GSmodelSetGSparticleLinkAttachMode(_GSmodel*, s32);
void GSparticleDestroyAllGenerators(_GSmodel*, u8);
GSparticleGenerator* GSparticleCreateGenerator(_GSmodel*, s32, s32);
void GSparticleAttachGeneratorToGSpart(GSparticleGenerator*, GSpart*, s32, s32, s32, s32);
void GSmodelSetForceUseFractionalFramesFlag(_GSmodel*, u8);

static s8 script_model_num;

void scriptModelInit()
{
    script_model_num = 0;
}

s32 scriptModelOpen(s32 resource)
{
    s32 id = script_model_num++ | 0x7FFE0000;
    void* people = peopleOpen(floorGetCurrentGroupID(), id, resource);
    if (people == 0) {
        return 0;
    }
    GSmodelSetBoundCheck(peopleBiosGetModelPtr(peopleSearchID(people)), 0);
    return id;
}

void scriptModelClose(s32 id)
{
    peopleClose(floorGetCurrentGroupID(), id, 0);
}

void scriptModelSetDisp(s32 id, s32 disp)
{
    s32 group = floorGetCurrentGroupID();
    if (peopleGetHumanID(group, id)) {
        peopleSetDisp(group, id, disp != 0);
    } else {
        _GSmodel* model = GSresGetResource(group, id);
        if (model) {
            GSmodelSetVisibility(model, disp != 0);
        }
    }
}

void scriptModelSetMotion(s32 id, s32 anim, s32 frame, s32 loop)
{
    s32 group = floorGetCurrentGroupID();
    if (peopleGetHumanID(group, id)) {
        peopleSetMotionForce(group, id, anim, frame, (bool)loop);
    } else {
        _GSmodel* model = GSresGetResource(group, id);
        if (model) {
            GSmodelSetAnimIndex(model, anim);
            GSmodelSetAnimFrame(model, frame);
            GSmodelSetAnimRate(model, 0.5f);
            GSmodelSetTexAnimIndex(model, anim);
            GSmodelSetTexAnimFrame(model, frame);
            GSmodelSetTexAnimRate(model, 0.5f);
            if (loop) {
                GSmodelSetAnimType(model, 1);
            } else {
                GSmodelSetAnimType(model, 0);
            }
            GSmodelStartAnimation(model);
        }
    }
}

void scriptModelSetMotionRate(s32 id, s32 anim, s32 frame, f32 rate, s32 loop)
{
    s32 group = floorGetCurrentGroupID();
    if (peopleGetHumanID(group, id)) {
        peopleSetMotionForce(group, id, anim, frame, (bool)loop);
    } else {
        _GSmodel* model = GSresGetResource(group, id);
        if (model) {
            GSmodelSetAnimIndex(model, anim);
            GSmodelSetAnimFrame(model, frame);
            GSmodelSetAnimRate(model, rate);
            GSmodelSetTexAnimIndex(model, anim);
            GSmodelSetTexAnimFrame(model, frame);
            GSmodelSetTexAnimRate(model, rate);
            if (loop) {
                GSmodelSetAnimType(model, 1);
            } else {
                GSmodelSetAnimType(model, 0);
            }
            GSmodelStartAnimation(model);
        }
    }
}

s32 scriptModelSetEndedMotion(s32 id, s32 anim, u8 loop)
{
    _GSmodel* model = GSresGetResource(floorGetCurrentGroupID(), id);
    if (model == 0) {
        return 0;
    }
    for (;;) {
        if (GSmodelHasAnimationEnded(model)) break;
        GSthreadSwitch();
    }
    GSmodelSetAnimIndex(model, anim);
    GSmodelSetAnimFrame(model, 0.0f);
    GSmodelSetAnimRate(model, 0.5f);
    GSmodelSetTexAnimIndex(model, anim);
    GSmodelSetTexAnimFrame(model, 0.0f);
    GSmodelSetTexAnimRate(model, 0.5f);
    if (loop) {
        GSmodelSetAnimType(model, 1);
    } else {
        GSmodelSetAnimType(model, 0);
    }
    GSmodelStartAnimation(model);
    return 1;
}

void scriptModelStopMotion(s32 id)
{
    s32 group = floorGetCurrentGroupID();
    if (peopleGetHumanID(group, id)) {
        peopleStopMotion(group, id);
    } else {
        _GSmodel* model = GSresGetResource(group, id);
        if (model) {
            GSmodelStopAnimation(model);
        }
    }
}

s32 scriptModelWaitMotion(s32 id, s32 wait)
{
    s32 group = floorGetCurrentGroupID();
    if (peopleGetHumanID(group, id)) {
        return peopleWaitSyncMotion(group, id, wait != 0);
    }
    _GSmodel* model = GSresGetResource(group, id);
    if (model == 0) {
        return 0;
    }
    for (;;) {
        if (GSmodelHasAnimationEnded(model)) {
            return 0;
        }
        if (!wait) {
            break;
        }
        GSthreadSwitch();
    }
    return 1;
}

s32 scriptModelAttach(s32 id, s32 target, s32 partIndex)
{
    _GSmodel* model;
    GSpart* part;
    s32 group = floorGetCurrentGroupID();
    if (peopleGetHumanID(group, id)) {
        peopleAttach(group, id, group, target, partIndex);
    } else {
        model = GSresGetResource(group, id);
        if (model == 0) {
            return 0;
        }
        _GSmodel* parent = GSresGetResource(group, target);
        if (parent == 0) {
            return 0;
        }
        part = GSmodelGetPart(parent, partIndex);
        GSmodelAttachToGSpart(model, part, 7, 0, 1);
        GSpartFree(part);
    }
    return 1;
}

s32 scriptModelDetach(s32 id)
{
    s32 group = floorGetCurrentGroupID();
    if (peopleGetHumanID(group, id)) {
        peopleDetach(group, id, 0);
    } else {
        _GSmodel* model = GSresGetResource(group, id);
        if (model == 0) {
            return 0;
        }
        GSmodelDetachFromGSpart(model, 1);
    }
    return 1;
}

void scriptModelSetParticle(s32 id, s32 bank, u8)
{
    _GSmodel* model = GSresGetResource(floorGetCurrentGroupID(), id);
    _GSmodel* particle = GSresGetResource(floorGetCurrentGroupID(), bank);
    GSmodelLinkToGSparticleBank(model, particle);
    GSmodelSetGSparticleLinkAttachMode(model, 4);
}

void scriptModelDeleteParticle(s32 id, u8 flag)
{
    GSparticleDestroyAllGenerators(GSresGetResource(floorGetCurrentGroupID(), id), flag);
}

void scriptModelPartPaticle(s32 id, s32 generator, s32 partIndex)
{
    GSpart* part = GSmodelGetPart(GSresGetResource(floorGetCurrentGroupID(), id), partIndex);
    GSparticleAttachGeneratorToGSpart(GSparticleCreateGenerator(GSresGetResource(floorGetCurrentGroupID(), generator), 0, 0), part, 7, 0, 1, 0);
    GSpartFree(part);
}

void scriptModelSetFractionalFramesFlag(s32 id, u8 flag)
{
    GSmodelSetForceUseFractionalFramesFlag(GSresGetResource(floorGetCurrentGroupID(), id), flag);
}
}
