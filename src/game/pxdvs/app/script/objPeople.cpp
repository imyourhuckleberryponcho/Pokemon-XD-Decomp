#include <dolphin/types.h>

// Script people commands (0x10..0x72). Unlike objFloor/objHero, the tigaVariant
// getters were not inlined here: they are emitted as weak functions after cmpPeople.
#pragma pool_strings off
#pragma peephole off

struct GSvec {
    f32 x, y, z;
    GSvec() {}
};
struct ScriptPeople { s32 group; s32 object; };
struct PeopleWork { u8 reserved[0x54]; u8 flag54; };
struct PeopleMotionTable { s32 id[5]; };
struct RareColor { u8 swap[4]; u8 color[4]; };

namespace GSscript {
void tigaErrMessage(const char*);
struct tigaVariant;
struct tigaArrayFixed { tigaVariant* get(int); };
struct tigaVariant {
    s16 type;
    u16 flags;
    union { s32 integer; f32 real; void* pointer; } value;
    s32 getCnvInteger();
    GSvec* getCnvVector();
    f32 getCnvSingle();
    inline ScriptPeople* getPeople();
    inline s32 getInteger();
    inline f32 getSingle();
    inline GSvec* getVector();
    inline tigaArrayFixed* getArray();
    inline void setSingle(f32 n) { type = 2; value.real = n; }
    inline void setInteger(s32 n) { type = 1; value.integer = n; }
};
struct TigaContext {
    u8 reserved[0x10];
    tigaVariant result;
    u8 reserved18[0x120];
    GSvec vector;
};
class Tiga {
public:
    u8 reserved[0x914];
    TigaContext* context;
    inline void setRpVec(const GSvec* v);
};
}

class AppScript : public GSscript::Tiga {
public:
    s32 cmpPeople(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
};

extern "C" {
void* GSresGetResource(s32, s32);
void GSmodelGetPosition(void*, GSvec*);
void GSmodelGetRotation(void*, GSvec*);
void GSmodelSetAnimRate(void*, f32);
void GSmodelSetBoundCheck(void*, bool);
void GSmodelSetScale(void*, GSvec*);
void GSmodelRecalculateBound(void*);
void GSmodelEnableColorSwap(void*, u8*);
void GSmodelEnableModulation(void*, u8*);
void* GSmodelGetPart(void*, s32);
void GSpartGetTransform(void*, GSvec*, GSvec*, GSvec*);
void GSpartFree(void*);
s32 floorGetCurrentGroupID();
u8 floorReadCharacter(s32, s32, s32);
void peopleSetDisp(s32, s32, u8);
u8 peopleSetMotion(s32, s32, s32, s32, u8);
void peopleSetMotionForce(s32, s32, s32, s32, u8);
void peopleStopMotion(s32, s32);
void peopleWaitSyncMotion(s32, s32, u8);
void peopleSpeakStart(s32, s32);
void peopleSpeakStop(s32, s32);
void peopleTalkMsg(s32, s32, s32);
void peopleTalkMsgEnd(s32, s32);
void peopleClose(s32, s32, s32);
u8 peopleRectCheck(s32, s32, f32, f32, f32, f32);
u8 peopleLineCheck(s32, s32, f32, f32, f32, f32, f32, u8);
void peopleSetPosXYZ(s32, s32, f32, f32, f32);
void peopleSetRotXYZ(s32, s32, f32, f32, f32);
void peopleSetRot(s32, s32, GSvec*);
void peopleGetPos(s32, s32, GSvec*);
void peopleWalkToXYZ(s32, s32, u8, f32, f32, f32);
void peopleWalkToTarget(s32, s32, s32, s32, f32, u8);
u8 peopleMoveCheck(s32, s32, u8);
void peopleSetFlagOn(s32, s32, s32);
void peopleSetFlagOff(s32, s32, s32);
s32 peopleGetFlags(s32, s32);
void peopleSetFlags(s32, s32, s32);
void peopleSetNeckTargetHero(s32, s32);
void peopleSetNeckTarget(s32, s32, s32, s32);
void peopleSetNeckTargetXYZ(s32, s32, s32, s32, s32);
void peopleRemoveNeckTarget(s32, s32, f32);
u8 peopleCheckNeckRotate(s32, s32, u8);
void peopleMoveNeckAngle(s32, s32, f32, f32, f32);
void peopleMoveNeckAngleWorld(s32, s32, f32, f32, f32);
void peopleMoveNeckTarget(s32, s32, s32, s32, f32);
void peopleMoveNeckTargetHero(s32, s32, f32);
void peopleMoveNeckTargetXYZ(s32, s32, s32, s32, s32, f32);
void peopleRotateTo(s32, s32, f32);
void peopleRotateToXYZ(s32, s32, f32, f32, f32, f32);
void peopleRotateToTarget(s32, s32, s32, s32, f32);
void peopleRotateToAngle(s32, s32, f32, f32);
void peopleRotateStop(s32, s32);
void peopleSetSpeedRate(s32, s32, f32);
void peopleAttach(s32, s32, s32, s32, s32);
void peopleAttachWithMode(s32, s32, s32, s32, s32, u8);
void peopleDetach(s32, s32, u8);
void peopleTaskSwich(s32, s32);
u8 peopleInitWalkList(s32, s32, u16);
u8 peopleAddWalkList(s32, s32, f32, f32, f32);
u8 peopleStartWalkList(s32, s32, u8);
u8 peopleStartWalkListStrict(s32, s32, s32);
u8 peopleFreeWalkList(s32, s32);
void peopleInitEvent(s32, s32);
void peopleTermEvent(s32, s32);
void peopleFallAppear(s32, s32, f32);
void peopleDispMark(s32, s32, s32);
void peopleSetCollision(s32, s32, u8);
u8 peopleGazeHeroCheck(s32, s32);
u8 peopleSetAnimBlend(s32, s32, s32, s32, s32);
u8 peopleWaitSyncMotionBlend(s32, s32, u8);
s32 peopleWalkPause(s32, s32, u8);
void peopleWalkPauseTalkMode(s32, s32, u8);
u32 peopleGetHumanID(s32, s32);
void peopleReadObject(s32, s32, s32);
u8 peopleRunOrNot(s32, s32);
f32 peopleGetSpeed(s32, s32);
void peopleSetWaitAnimation(s32, s32);
void peopleUnsetWaitAnimation(s32, s32);
f32 peopleGetYDegreeRotation(s32, s32);
void peopleAutoAnimation(s32, s32);
void peopleManualAnimation(s32, s32);
void peopleSetMotionTable(s32, s32, PeopleMotionTable);
void peopleSetDefaultMotionTable(s32, s32);
void peopleSpeedSlowDownOn(s32, s32);
void peopleSpeedSlowDownOff(s32, s32);
void peopleBlinkOnce(s32, s32);
void peopleBlinkStart(s32, s32);
void peopleBlinkStop(s32, s32);
void peopleSetTalkDistance(s32, s32, f32);
f32 peopleGetTalkDistance(s32, s32);
void peopleSetWalkSpeed(s32, s32, f32, s32);
PeopleWork* peopleGet(s32, s32);
void peopleTalkMessageBgmStart();
void peopleTalkMessageBgmStop();
s8 menuSubOpenYesNoField();
void winMsgOpenField(s32, s32, s32);
void winMsgCloseField(s32);
void recoveryEventPC(s32, s32, s32, s32*, s32*);
void scriptEncount(u16, s32, s32);
void fightEncount(u16);
void scriptWaitTime(f32);
void scriptGetItem(s32, s32);
void scriptPlayPokemonNakigoe(u16);
void scriptSetEndedMotion(s32, s32, s32, u8);
void scriptModelPartPaticle(s32, s32, s32);
u8 scriptPeopleInsideCheck(GSvec*, GSvec*, f32, GSvec*);
}

static RareColor _pokeRareCol[9] = {
    { { 0, 1, 2, 3 }, { 0x75, 0x9D, 0x62, 0xFF } },
    { { 1, 2, 2, 3 }, { 0x77, 0x80, 0x9D, 0xFF } },
    { { 2, 1, 2, 3 }, { 0x7F, 0x7F, 0x7F, 0xFF } },
    { { 1, 2, 0, 3 }, { 0x4E, 0xB0, 0x28, 0xFF } },
    { { 0, 1, 2, 3 }, { 0x7D, 0xA8, 0xA2, 0xFF } },
    { { 1, 1, 2, 3 }, { 0x61, 0x61, 0x61, 0xFF } },
    { { 0, 2, 0, 3 }, { 0x7F, 0x7F, 0x7F, 0xFF } },
    { { 2, 0, 0, 3 }, { 0x99, 0xAA, 0x93, 0xFF } },
    { { 2, 0, 2, 3 }, { 0x91, 0x91, 0x91, 0xFF } },
};

s32 AppScript::cmpPeople(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    static GSvec Vector;
    ScriptPeople* p;
    s32 flags;
    void* model;

    if (command != 1) {
        if (args[0].type != 0x23) {
            result->setInteger(0);
            return 1;
        }
        p = args[0].getPeople();
    } else {
        return 0;
    }

    switch (command) {
    case 0x10: peopleSetDisp(p->group, p->object, args[1].getInteger() != 0); break;
    case 0x11: result->setInteger(peopleSetMotion(p->group, p->object, args[1].getInteger(), args[2].getInteger(), args[3].getInteger() != 0)); break;
    case 0x12: peopleSetMotionForce(p->group, p->object, args[1].getInteger(), args[2].getInteger(), args[3].getInteger() != 0); break;
    case 0x13: peopleStopMotion(p->group, p->object); break;
    case 0x14: peopleWaitSyncMotion(p->group, p->object, args[1].getInteger() != 0); break;
    case 0x15:
        peopleSpeakStart(p->group, p->object);
        peopleTalkMsg(p->group, p->object, args[1].getInteger());
        if (args[2].getInteger()) {
            peopleTalkMsgEnd(p->group, p->object);
        }
        break;
    case 0x16:
        peopleTalkMsgEnd(p->group, p->object);
        peopleSpeakStop(p->group, p->object);
        break;
    case 0x17: result->setInteger(floorReadCharacter(p->group, p->object, args[1].getInteger())); break;
    case 0x18: peopleClose(p->group, p->object, 1); break;
    case 0x19: result->setInteger(peopleRectCheck(p->group, p->object, args[1].getSingle(), args[2].getSingle(), args[3].getSingle(), args[4].getSingle())); break;
    case 0x1A: {
        GSvec* a = args[1].getVector();
        GSvec* b = args[2].getVector();
        result->setInteger(peopleRectCheck(p->group, p->object, a->x, a->z, b->x, b->z));
        break;
    }
    case 0x1B: result->setInteger(peopleLineCheck(p->group, p->object, args[1].getSingle(), args[2].getSingle(), args[3].getSingle(), args[4].getSingle(), args[5].getSingle(), args[6].getInteger() != 0)); break;
    case 0x1C: {
        GSvec* a = args[1].getVector();
        GSvec* b = args[2].getVector();
        result->setInteger(peopleLineCheck(p->group, p->object, a->x, a->z, b->x, b->z, 0.0f, args[3].getInteger() != 0));
        break;
    }
    case 0x1D: peopleSetPosXYZ(p->group, p->object, args[1].getSingle(), args[2].getSingle(), args[3].getSingle()); break;
    case 0x1E: {
        GSvec* v = args[1].getVector();
        peopleSetPosXYZ(p->group, p->object, v->x, v->y, v->z);
        break;
    }
    case 0x1F: peopleSetRotXYZ(p->group, p->object, args[1].getSingle(), args[2].getSingle(), args[3].getSingle()); break;
    case 0x20: peopleSetRot(p->group, p->object, args[1].getVector()); break;
    case 0x21:
        Vector.x = args[1].getSingle();
        Vector.y = args[2].getSingle();
        Vector.z = args[3].getSingle();
        peopleGetPos(p->group, p->object, &Vector);
        break;
    case 0x22: peopleGetPos(p->group, p->object, args[1].getVector()); break;
    case 0x24: peopleWalkToXYZ(p->group, p->object, args[1].getInteger() != 0, args[2].getSingle(), args[3].getSingle(), args[4].getSingle()); break;
    case 0x25: {
        GSvec* v = args[2].getVector();
        peopleWalkToXYZ(p->group, p->object, args[1].getInteger() != 0, v->x, v->y, v->z);
        break;
    }
    case 0x26: {
        ScriptPeople* t = args[1].getPeople();
        peopleWalkToTarget(p->group, p->object, t->group, t->object, args[2].getSingle(), args[3].getInteger() != 0);
        break;
    }
    case 0x27: result->setInteger(peopleMoveCheck(p->group, p->object, args[1].getInteger() != 0)); break;
    case 0x28: peopleSetFlagOn(p->group, p->object, args[1].getInteger()); break;
    case 0x29: peopleSetFlagOff(p->group, p->object, args[1].getInteger()); break;
    case 0x2A: peopleSetNeckTargetHero(p->group, p->object); break;
    case 0x2B: {
        ScriptPeople* t = args[1].getPeople();
        peopleSetNeckTarget(p->group, p->object, t->group, t->object);
        break;
    }
    case 0x2C: peopleSetNeckTargetXYZ(p->group, p->object, args[1].getInteger(), args[2].getInteger(), args[3].getInteger()); break;
    case 0x43: {
        GSvec* v = args[1].getVector();
        peopleSetNeckTargetXYZ(p->group, p->object, v->x, v->y, v->z);
        break;
    }
    case 0x2D: peopleRemoveNeckTarget(p->group, p->object, args[1].getSingle()); break;
    case 0x2E: result->setInteger(peopleCheckNeckRotate(p->group, p->object, args[1].getInteger() != 0)); break;
    case 0x50: peopleMoveNeckAngle(p->group, p->object, args[1].getSingle(), args[2].getSingle(), args[3].getSingle()); break;
    case 0x53: peopleMoveNeckAngleWorld(p->group, p->object, args[1].getSingle(), args[2].getSingle(), args[3].getSingle()); break;
    case 0x2F: peopleRotateTo(p->group, p->object, args[1].getSingle()); break;
    case 0x30: peopleRotateToXYZ(p->group, p->object, args[1].getSingle(), args[2].getSingle(), args[3].getSingle(), args[4].getSingle()); break;
    case 0x44: {
        GSvec* v = args[1].getVector();
        peopleRotateToXYZ(p->group, p->object, v->x, v->y, v->z, args[2].getSingle());
        break;
    }
    case 0x31: {
        ScriptPeople* t = args[1].getPeople();
        peopleRotateToTarget(p->group, p->object, t->group, t->object, args[2].getSingle());
        break;
    }
    case 0x4F: peopleRotateToAngle(p->group, p->object, 0.017453292f * args[1].getSingle(), args[2].getSingle()); break;
    case 0x32: peopleSetSpeedRate(p->group, p->object, args[1].getSingle()); break;
    case 0x33: {
        ScriptPeople* t = args[1].getPeople();
        peopleAttach(p->group, p->object, t->group, t->object, args[2].getInteger());
        break;
    }
    case 0x34: peopleDetach(p->group, p->object, args[1].getInteger() != 0); break;
    case 0x35: peopleTaskSwich(p->group, p->object); break;
    case 0x36: result->setInteger(peopleInitWalkList(p->group, p->object, args[1].getInteger())); break;
    case 0x37: result->setInteger(peopleAddWalkList(p->group, p->object, args[1].getSingle(), args[2].getSingle(), args[3].getSingle())); break;
    case 0x45: {
        GSvec* v = args[1].getVector();
        result->setInteger(peopleAddWalkList(p->group, p->object, v->x, v->y, v->z));
        break;
    }
    case 0x38: result->setInteger(peopleStartWalkList(p->group, p->object, args[1].getInteger() != 0)); break;
    case 0x39: result->setInteger(peopleFreeWalkList(p->group, p->object)); break;
    case 0x3A: peopleInitEvent(p->group, p->object); break;
    case 0x3B: peopleTermEvent(p->group, p->object); break;
    case 0x3C: peopleFallAppear(p->group, p->object, args[1].getSingle()); break;
    case 0x3D: peopleDispMark(p->group, p->object, args[1].getInteger()); break;
    case 0x3E: peopleSetCollision(p->group, p->object, args[1].getInteger() != 0); break;
    case 0x3F: result->setInteger(peopleGazeHeroCheck(p->group, p->object)); break;
    case 0x40: result->setInteger(peopleSetAnimBlend(p->group, p->object, args[1].getInteger(), args[2].getInteger(), args[3].getInteger())); break;
    case 0x41: result->setInteger(peopleWaitSyncMotionBlend(p->group, p->object, args[1].getInteger() != 0)); break;
    case 0x42: result->setInteger(peopleWalkPause(p->group, p->object, args[1].getInteger() != 0)); break;
    case 0x65: {
        s32 items[6];
        s32 counts[7];
        u16 i;
        for (i = 0; i < 6; i++) {
            items[i] = args[2].getArray()->get(i)->getInteger();
        }
        for (i = 0; i < 7; i++) {
            counts[i] = args[3].getArray()->get(i)->getInteger();
        }
        recoveryEventPC(p->group, p->object, args[1].getInteger(), items, counts);
        break;
    }
    case 0x46:
        if (peopleGetHumanID(p->group, p->object) == 0) {
            floorReadCharacter(p->group, p->object, args[1].getInteger());
        } else {
            peopleReadObject(p->group, p->object, args[1].getInteger());
        }
        break;
    case 0x47: result->setInteger(peopleRunOrNot(p->group, p->object)); break;
    case 0x48: result->setSingle(peopleGetSpeed(p->group, p->object)); break;
    case 0x49:
        switch (args[1].getInteger()) {
        case 1:
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            break;
        case 2:
            peopleSetMotion(p->group, p->object, 0xB, 0, 0);
            peopleWaitSyncMotion(p->group, p->object, 1);
            peopleSetMotion(p->group, p->object, 0xC, 0, 1);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            peopleSetMotion(p->group, p->object, 0xD, 0, 0);
            peopleWaitSyncMotion(p->group, p->object, 1);
            peopleSetMotion(p->group, p->object, 3, 0, 1);
            break;
        case 3:
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            if (args[3].getInteger() == 1) {
                peopleTalkMsgEnd(p->group, p->object);
                peopleSpeakStop(p->group, p->object);
            }
            break;
        case 6:
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            scriptEncount(args[3].getInteger(), 1, 0);
            break;
        case 7:
            peopleSetMotion(p->group, p->object, args[2].getInteger(), 0, 0);
            peopleWaitSyncMotion(p->group, p->object, 1);
            peopleSetMotion(p->group, p->object, args[3].getInteger(), 0, 0);
            peopleWaitSyncMotion(p->group, p->object, 1);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[4].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            break;
        case 8: {
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMessageBgmStart();
            s32 answer = menuSubOpenYesNoField();
            winMsgCloseField(1);
            peopleTalkMessageBgmStop();
            peopleSpeakStop(p->group, p->object);
            if (answer == 0) {
                result->setInteger(0);
            } else {
                result->setInteger(1);
            }
            break;
        }
        case 9:
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            fightEncount(args[3].getInteger());
            break;
        case 10:
            peopleSetMotion(p->group, p->object, args[2].getInteger(), 0, 0);
            peopleWaitSyncMotion(p->group, p->object, 1);
            peopleSetMotion(p->group, p->object, args[3].getInteger(), 0, 1);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[4].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            peopleSetMotion(p->group, p->object, args[5].getInteger(), 0, 0);
            peopleWaitSyncMotion(p->group, p->object, 1);
            peopleSetMotion(p->group, p->object, 3, 0, 1);
            break;
        case 11:
            peopleDispMark(p->group, p->object, 1);
            scriptWaitTime(1.0f);
            peopleRotateToTarget(p->group, p->object, 0, 100, 1.0f);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            break;
        case 12:
            peopleRotateToTarget(p->group, p->object, 0, 100, 1.0f);
            peopleDispMark(p->group, p->object, 1);
            scriptWaitTime(1.0f);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            break;
        case 13: {
            flags = peopleGetFlags(p->group, p->object);
            peopleSetFlagOff(p->group, p->object, 0x20);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            peopleSetFlagOn(p->group, p->object, 0x20);
            peopleRotateToTarget(p->group, p->object, 0, 100, 1.0f);
            peopleSetFlags(p->group, p->object, flags);
            break;
        }
        case 14:
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            scriptGetItem(args[3].getInteger(), args[4].getInteger());
            break;
        case 15:
            scriptPlayPokemonNakigoe(args[2].getInteger());
            peopleTalkMsg(p->group, p->object, args[3].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            break;
        case 16:
            winMsgOpenField(args[2].getInteger(), 1, 0);
            winMsgCloseField(1);
            break;
        case 17:
            peopleSetFlagOff(p->group, p->object, 0x20);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            peopleSetFlagOn(p->group, p->object, 0x20);
            break;
        case 18:
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            peopleManualAnimation(p->group, p->object);
            scriptSetEndedMotion(p->group, p->object, args[3].getInteger(), 0);
            peopleWaitSyncMotion(p->group, p->object, 1);
            peopleReadObject(p->group, p->object, args[4].getInteger());
            peopleManualAnimation(p->group, p->object);
            peopleSetMotionForce(p->group, p->object, args[5].getInteger(), 0, 0);
            peopleWaitSyncMotion(p->group, p->object, 1);
            peopleAutoAnimation(p->group, p->object);
            break;
        case 19: {
            flags = peopleGetFlags(p->group, p->object);
            peopleSetFlagOff(p->group, p->object, 0x10);
            peopleSetFlagOff(p->group, p->object, 0x20);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            peopleSetFlags(p->group, p->object, flags);
            break;
        }
        case 20: {
            flags = peopleGetFlags(p->group, p->object);
            peopleSetFlagOff(p->group, p->object, 0x10);
            peopleSetFlagOff(p->group, p->object, 0x20);
            ScriptPeople* t = args[3].getPeople();
            peopleSetNeckTarget(p->group, p->object, t->group, t->object);
            peopleCheckNeckRotate(p->group, p->object, 1);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            if (args[4].getInteger() == 1) {
                peopleRemoveNeckTarget(p->group, p->object, args[5].getSingle());
                peopleCheckNeckRotate(p->group, p->object, 1);
            }
            peopleSetFlags(p->group, p->object, flags);
            break;
        }
        case 21: {
            flags = peopleGetFlags(p->group, p->object);
            peopleSetFlagOff(p->group, p->object, 0x20);
            peopleSpeakStart(p->group, p->object);
            peopleTalkMsg(p->group, p->object, args[2].getInteger());
            peopleTalkMsgEnd(p->group, p->object);
            peopleSpeakStop(p->group, p->object);
            peopleSetFlags(p->group, p->object, flags);
            break;
        }
        }
        break;
    case 0x4A: peopleAttachWithMode(p->group, p->object, floorGetCurrentGroupID(), args[1].getInteger(), args[2].getInteger(), args[3].getInteger()); break;
    case 0x4B: {
        model = GSresGetResource(p->group, p->object);
        if (model) {
            GSmodelGetPosition(model, &Vector);
        }
        setRpVec(&Vector);
        break;
    }
    case 0x4C: {
        model = GSresGetResource(p->group, p->object);
        if (model) {
            GSmodelGetRotation(model, &Vector);
        }
        Vector.y = 57.29578f * Vector.y;
        result->setSingle(Vector.y);
        break;
    }
    case 0x4D: peopleSetWaitAnimation(p->group, p->object); break;
    case 0x4E: peopleUnsetWaitAnimation(p->group, p->object); break;
    case 0x51: {
        ScriptPeople* t = args[1].getPeople();
        peopleMoveNeckTarget(p->group, p->object, t->group, t->object, args[2].getSingle());
        break;
    }
    case 0x52: peopleMoveNeckTargetHero(p->group, p->object, args[1].getSingle()); break;
    case 0x54: peopleMoveNeckTargetXYZ(p->group, p->object, args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getSingle()); break;
    case 0x55: peopleGetYDegreeRotation(p->group, p->object); break;
    case 0x57: peopleAutoAnimation(p->group, p->object); break;
    case 0x58: peopleManualAnimation(p->group, p->object); break;
    case 0x59: {
        PeopleMotionTable table;
        table.id[0] = args[1].getArray()->get(0)->getInteger();
        table.id[1] = args[1].getArray()->get(1)->getInteger();
        table.id[2] = args[1].getArray()->get(2)->getInteger();
        table.id[3] = args[1].getArray()->get(3)->getInteger();
        table.id[4] = args[1].getArray()->get(4)->getInteger();
        peopleSetMotionTable(p->group, p->object, table);
        break;
    }
    case 0x5A: peopleSetDefaultMotionTable(p->group, p->object); break;
    case 0x5B: peopleSpeedSlowDownOn(p->group, p->object); break;
    case 0x5C: peopleSpeedSlowDownOff(p->group, p->object); break;
    case 0x5D: peopleBlinkOnce(p->group, p->object); break;
    case 0x5E: peopleBlinkStart(p->group, p->object); break;
    case 0x5F: peopleBlinkStop(p->group, p->object); break;
    case 0x60: peopleSpeakStart(p->group, p->object); break;
    case 0x61: peopleSpeakStop(p->group, p->object); break;
    case 0x62: peopleSetTalkDistance(p->group, p->object, args[1].getSingle()); break;
    case 0x63: peopleGetTalkDistance(p->group, p->object); break;
    case 0x64: result->setInteger(peopleStartWalkListStrict(p->group, p->object, args[1].getInteger())); break;
    case 0x66: peopleWalkPauseTalkMode(p->group, p->object, args[1].getInteger() != 0); break;
    case 0x67: {
        model = GSresGetResource(p->group, p->object);
        GSmodelSetAnimRate(model, args[1].getSingle());
        break;
    }
    case 0x68: peopleSetWalkSpeed(p->group, p->object, args[1].getSingle(), args[2].getInteger()); break;
    case 0x69: {
        model = GSresGetResource(p->group, p->object);
        GSmodelSetBoundCheck(model, args[1].getInteger() == 0);
        break;
    }
    case 0x6A: scriptSetEndedMotion(p->group, p->object, args[1].getInteger(), args[2].getInteger() != 0); break;
    case 0x6B: scriptModelPartPaticle(p->object, args[1].getInteger(), args[2].getInteger()); break;
    case 0x6C: {
        model = GSresGetResource(p->group, p->object);
        GSmodelSetScale(model, args[1].getVector());
        break;
    }
    case 0x6D: GSmodelRecalculateBound(GSresGetResource(p->group, p->object)); break;
    case 0x6E:
        peopleGetPos(p->group, p->object, &Vector);
        result->setInteger(scriptPeopleInsideCheck(&Vector, args[1].getVector(), args[2].getSingle(), args[3].getVector()));
        break;
    case 0x6F: {
        s32 part = args[1].getInteger();
        void* gspart = GSmodelGetPart(GSresGetResource(floorGetCurrentGroupID(), p->object), part);
        GSpartGetTransform(gspart, &Vector, 0, 0);
        GSpartFree(gspart);
        setRpVec(&Vector);
        break;
    }
    case 0x70: {
        model = GSresGetResource(p->group, p->object);
        if (model) {
            RareColor* col = &_pokeRareCol[args[1].getInteger()];
            GSmodelEnableColorSwap(model, col->swap);
            GSmodelEnableModulation(model, col->color);
        }
        break;
    }
    case 0x71: {
        PeopleWork* work = peopleGet(p->group, p->object);
        work->flag54 = 0;
        break;
    }
    case 0x72: {
        PeopleWork* work = peopleGet(p->group, p->object);
        peopleRotateStop(p->group, p->object);
        work->flag54 = 0;
        break;
    }
    }
    return 0;
}

inline void GSscript::Tiga::setRpVec(const GSvec* v)
{
    context->vector = *v;
    context->result.value.pointer = &context->vector;
    context->result.type = 4;
}

inline GSscript::tigaArrayFixed* GSscript::tigaVariant::getArray()
{
    if (type == 7) return (tigaArrayFixed*)value.pointer;
    tigaErrMessage("pokemon not access");
    return 0;
}

inline GSvec* GSscript::tigaVariant::getVector()
{
    if (type == 4) return (GSvec*)value.pointer;
    return getCnvVector();
}

inline f32 GSscript::tigaVariant::getSingle()
{
    if (type == 1) return (f32)value.integer;
    if (type == 2) return value.real;
    return getCnvSingle();
}

inline s32 GSscript::tigaVariant::getInteger()
{
    if (type == 1) return value.integer;
    if (type == 2) return (s32)value.real;
    return getCnvInteger();
}

inline ScriptPeople* GSscript::tigaVariant::getPeople()
{
    if (type == 0x23) return (ScriptPeople*)value.pointer;
    tigaErrMessage("people not access");
    return 0;
}
