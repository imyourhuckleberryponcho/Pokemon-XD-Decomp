#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
    GSvec();
};

struct _GSmodel;
struct GSpart;
struct GSthread;

struct FloorEventTresure {
    u8 kind : 3;     // 0x00
    u8 type : 3;
    u8 pad0 : 2;
    u8 count;        // 0x01
    u8 pad1[2];
    u16 floorID;     // 0x04
    u16 eventFlag;   // 0x06
    u8 pad2[4];
    u32 item;        // 0x0C
    u8 pad3[0xC];
};

struct FloorEventDoor {
    s8 openAnim;     // 0x00
    s8 closeAnim;    // 0x01
    s8 openEndAnim;  // 0x02
    s8 closeEndAnim; // 0x03
    u8 pad4;
    s8 altAnimA;     // 0x05
    s8 altAnimB;     // 0x06
    u8 doorType;     // 0x07
    u8 partIndex;    // 0x08
    u8 pad9;
    s16 collisionId; // 0x0A
    u8 padC[2];
    u16 openFlag;    // 0x0E
    u16 closeFlag;   // 0x10
    u8 pad12[2];
    u32 resourceId;  // 0x14
};

struct FloorEventEntry {
    u8 type;         // 0x00
    u8 pad1;
    u16 floorID;     // 0x02
    u32 arg;         // 0x04
    u32 script;      // 0x08
    u32 args[4];     // 0x0C
};

struct PlayMEParam {
    u32 id;
    u8 busy;
};

extern "C" {
extern u32* floor_tresure_list_number;
extern FloorEventTresure* floor_tresure_list;
extern u32* floor_door_list_number;
extern FloorEventDoor* floor_door_list;
extern u32* floor_event_list_number;
extern FloorEventEntry* floor_event_list;

u32 GSfloorGetCurrent(void);
u32 floorGetCurrentGroupID();
void peopleSetDisp(s32, s32, s32);
s32 GSsndGetStatus(u32 id);
void GSthreadSwitch(void);
void soundPlayWait(u32 id);
void* floorCreateThread(s32 a, u32 stackSize, s32 c, void* func);
void msgctrlSetValue(s32 id, u32 value);
s32 winMsgOpen(s32, s32 msgID, s32, s32);
void winMsgClose(s32 flag);
void heroAddPokedoru(void* hero, u32 offset);
s32 heroItemAddItemDataId(void* hero, u32 itemID, u32 amount, u32 index);
u16 pcboxAddItem(void* box, u16 item, u16 count);
void peopleSetMotion(u32, u32, u32, u32, u32);
void peopleSetFlagOn(s32, s32, s32);
u8 GSflagTest(u32 id);
u8 GSsndPlayNow(u32 id);
u8 GSsndStopNow(u32 id);
void peopleWaitSyncMotion(s32, s32, u8);
void GSflagOn(u32 id);
void GSflagOff(u32 id);
void* floorGetResource(u32 id, u32 resID);
void* floorDataBiosGetPtr(u32 key);
u32 floorDataBiosGetGroupID(void* floor);
GSpart* GSmodelGetPart(_GSmodel* model, s32 index);
void GSpartGetTransform(GSpart* part, GSvec* pos, GSvec* rot, GSvec* scale);
void GSpartFree(GSpart* part);
void peopleWalkTo(s32, s32, u8, GSvec*);
u8 peopleMoveCheck(s32, s32, u8);
void peopleRotateToAngle(s32, s32, f32, f32);
void peopleDetach(s32, s32, u8);
void peopleGetPos(s32, s32, GSvec*);
void peopleAttach(s32, s32, s32, s32, s32);
void peopleSetPosXYZ(s32, s32, f32, f32, f32);
void GSmodelSetAnimIndex(_GSmodel* model, u32 index);
void GSmodelGetFrameCount(_GSmodel* model, f32* count, f32* blendCount);
u8 GSmodelCanAnimate(_GSmodel* model);
u8 GSmodelIsAnimating(_GSmodel* model);
void GSmodelSetAnimFrame(_GSmodel* model, f32 frame);
void GSmodelSetAnimRate(_GSmodel* model, f32 rate);
void GSmodelSetAnimType(_GSmodel* model, s32 type);
void GSmodelStartAnimation(_GSmodel* model);
u8 GSgfxVideoGetVsyncRate(void);
void scriptSetCol(s32 id, u8 enable);
u32 peopleGetFlags(s32, s32);
void peopleSetFlags(s32, s32, u32);
void heroMoveInitEvent();
void heroMoveTermEvent();
void GSlogWrite(const char*, ...);
s32 scriptSetEventColID(s32 id);
u8 floorExecScriptInteger(int func, s32 a, s32 b, s32 c, s32 d);
u8 scriptSoundOpenPlayME(u32 id, u32 time, u8 flag);
}

void EvlogSet(s8 type, u32 value);
void _floorEventWaitMotion(_GSmodel* model);
void _floorEventSetMotion(_GSmodel* model, s16 index, f32 frame);
static void _floorEventWaitME();
static u8 _floorEventPlayMEThread(GSthread* thread);

static PlayMEParam _playMEParam;

extern "C" {

void* floorEventGetTresureList(u32 param) {
    u32 off;
    FloorEventTresure* entry;
    u32 index;
    u32 found;
    u32 target;

    entry = 0;
    found = 0;
    if ((param & 0x7FFF0000) != 0x7FFF0000) {
        return 0;
    }

    target = param & 0x1FF;
    for (index = 0, off = 0; index < *floor_tresure_list_number; off += sizeof(FloorEventTresure), index++) {
        entry = (FloorEventTresure*)((u8*)floor_tresure_list + off);
        if (entry->floorID == GSfloorGetCurrent()) {
            if (target == found++) {
                break;
            }
        }
    }

    if (index == *floor_tresure_list_number) {
        return 0;
    }
    return entry;
}

void floorEventSetTresureDisp(u32 rawIndex, u32 display) {
    u32 off;
    FloorEventTresure* entry;
    u32 index;
    u32 found = 0;
    u32 encoded;

    for (index = 0, off = 0; index < *floor_tresure_list_number; off += sizeof(FloorEventTresure), index++) {
        entry = (FloorEventTresure*)((u8*)floor_tresure_list + off);
        if (entry->floorID == GSfloorGetCurrent()) {
            if (index == rawIndex) {
                encoded = found | 0x7FFF0000;
                break;
            }
            found++;
        }
    }

    if (index != *floor_tresure_list_number) {
        peopleSetDisp(floorGetCurrentGroupID(), encoded, display);
    }
}

s32 floorEventChangeTresure(u32 index, u16 val, u8 byte) {
    FloorEventTresure* entry;
    if (index >= *floor_tresure_list_number) {
        GSlogWrite("[%s] Range Over!!\n", __FUNCTION__);
        return -1;
    }
    entry = &floor_tresure_list[index];
    entry->item = val;
    entry->count = byte;
    return 0;
}

s32 floorEventGetTresureEx(u8 type, u32 item, s32 count, u8 playFanfare) {
    s32 result;
    u8 boxed = 0;
    u32 message = 0;

    for (;;) {
        if (GSsndGetStatus(0x3CE) != 2) {
            break;
        }
        GSthreadSwitch();
    }
    if (playFanfare == 1) {
        soundPlayWait(0x3CE);
        _playMEParam.id = 0x3CE;
        _playMEParam.busy = 1;
        floorCreateThread(0x80, 0, 1, (void*)_floorEventPlayMEThread);
    }

    switch (type) {
    case 2:
        msgctrlSetValue(0x4B, item);
        winMsgOpen(3, 0xD2F1, 1, 0);
        winMsgClose(1);
        heroAddPokedoru(0, item);
        winMsgOpen(3, 0xD2F4, 1, 0);
        _floorEventWaitME();
        winMsgClose(1);
        break;

    case 1:
    case 4:
        if (count <= 0) {
            break;
        }
        msgctrlSetValue(0x2D, item);
        msgctrlSetValue(0x2F, count);
        if (type == 1) {
            if (count == 1) {
                message = 0xD2F2;
            } else {
                message = 0xD2F3;
            }
            winMsgOpen(3, message, 1, 0);
            winMsgClose(1);
        }

        result = heroItemAddItemDataId(0, (u16)item, (u16)count, -1);
        if (result == 0) {
            if (count == 1) {
                message = 0xD2F5;
            } else {
                message = 0xD2F6;
            }
        } else if (result > 0) {
            result = pcboxAddItem(0, (u16)item, (u16)result);
            if (result != 0) {
                boxed = 1;
            }
            if (count == 1) {
                message = 0xD2F7;
            } else {
                message = 0xD2F8;
            }
        }
        winMsgOpen(3, message, 1, 0);
        if (boxed == 1) {
            winMsgOpen(3, 0xD2F9, 1, 0);
        }
        _floorEventWaitME();
        winMsgClose(1);
        break;
    }

    _floorEventWaitME();
    return result;
}

s32 floorEventGetTresure(u8 type, u32 item, s32 count) {
    s32 result;
    s32 stored;
    s32 boxedCount = 0;
    u32 message;

    soundPlayWait(0x3CE);
    _playMEParam.id = 0x3CE;
    _playMEParam.busy = 1;
    floorCreateThread(0x80, 0, 1, (void*)_floorEventPlayMEThread);

    switch (type) {
    case 2:
        msgctrlSetValue(0x4B, item);
        winMsgOpen(3, 0xD2F1, 1, 0);
        winMsgClose(1);
        heroAddPokedoru(0, item);
        winMsgOpen(3, 0xD2F4, 1, 0);
        _floorEventWaitME();
        winMsgClose(1);
        break;

    case 1:
    case 4:
        if (count <= 0) {
            break;
        }
        msgctrlSetValue(0x2D, item);
        msgctrlSetValue(0x2F, count);
        if (type == 1) {
            if (count == 1) {
                message = 0xD2F2;
            } else {
                message = 0xD2F3;
            }
            winMsgOpen(3, message, 1, 0);
            winMsgClose(1);
        }

        result = heroItemAddItemDataId(0, (u16)item, (u16)count, -1);
        stored = count - result;
        if (result > 0) {
            result = pcboxAddItem(0, (u16)item, (u16)result);
            boxedCount = (count - result) - stored;
        }

        if (stored > 0) {
            if (count == 1) {
                message = 0xD2F5;
            } else {
                message = 0xD2F6;
            }
            msgctrlSetValue(0x2F, stored);
            winMsgOpen(3, message, 1, 1);
            winMsgClose(1);
        }

        if (count - stored > 0) {
            if (boxedCount != 0) {
                if (count == 1) {
                    message = 0xD2F7;
                    msgctrlSetValue(0x2F, boxedCount);
                } else if (stored == 0) {
                    message = 0xD2F8;
                    msgctrlSetValue(0x2F, count);
                } else {
                    message = 0xD2FA;
                    msgctrlSetValue(0x2F, count - stored);
                }
            } else {
                message = 0xD2FA;
                msgctrlSetValue(0x2F, count - stored);
            }
            winMsgOpen(3, message, 1, 1);
            winMsgClose(1);
        }

        if (count - stored - boxedCount > 0) {
            msgctrlSetValue(0x2F, count - stored - boxedCount);
            if (count == 1) {
                message = 0xD2F9;
            } else {
                message = 0xD2FB;
            }
            winMsgOpen(3, message, 1, 1);
            winMsgClose(1);
        }
        _floorEventWaitME();
        break;
    }

    _floorEventWaitME();
    return result;
}

s32 floorEventCtrlTresure(s32 character, u32 index, u8 mode) {
    FloorEventTresure* entry;

    entry = (FloorEventTresure*)floorEventGetTresureList(index);
    if (entry == 0) {
        return -1;
    }

    switch (mode) {
    case 0:
        switch (entry->kind) {
        case 1:
            peopleSetMotion(character, index, 2, 0, 1);
            peopleSetFlagOn(character, index, 1);
            break;
        case 2:
        case 3:
            peopleSetDisp(character, index, 0);
            break;
        }
        break;

    case 1:
        switch (entry->kind) {
        case 1:
            peopleSetMotion(character, index, 0, 0, 1);
        case 2:
        case 3:
            peopleSetMotion(character, index, 0, 0, 1);
            break;
        }
        break;

    case 2:
        if (entry->eventFlag != 0 && GSflagTest(entry->eventFlag) != 0) {
            return 0;
        }

        switch (entry->kind) {
        case 1:
            peopleSetMotion(character, index, 1, 0, 0);
            GSsndPlayNow(0x461);
            peopleWaitSyncMotion(character, index, 1);
            break;
        case 2:
        case 3:
            break;
        }

        floorEventCtrlTresure(character, index, 0);
        GSflagOn(entry->eventFlag);
        floorEventGetTresure(entry->type, entry->item, entry->count);
        break;
    }

    return 0;
}

s32 floorEventCtrlElevator(s32 floor, u32 index, u16 command, s32 group, s32 person) {
    FloorEventDoor* elevator;
    _GSmodel* model;
    s16 animation = -1;
    f32 frame = 0.0f;
    GSvec position;
    GSpart* part;
    u32 floorGroup;

    if (index >= *floor_door_list_number) {
        return -1;
    }
    elevator = &floor_door_list[index];
    if (elevator->resourceId == 0) {
        return -1;
    }
    model = (_GSmodel*)floorGetResource(floor, elevator->resourceId);
    if (model == 0) {
        return -1;
    }

    floorGroup = floorDataBiosGetGroupID(floorDataBiosGetPtr(floor));

    switch (command) {
    case 1:
    case 2:
    case 0x81:
    case 0x82:
        if (elevator->openAnim >= 0) {
            _floorEventSetMotion(model, elevator->openAnim, frame);
        }
        if (command & 0x80) {
            GSsndPlayNow(0x27);
        }
        _floorEventWaitMotion(model);

        part = GSmodelGetPart(model, elevator->partIndex);
        GSpartGetTransform(part, &position, 0, 0);
        GSpartFree(part);
        if (command & 1) {
            peopleWalkTo(group, person, 1, &position);
            peopleMoveCheck(group, person, 1);
            peopleRotateToAngle(group, person, 0.0f, 0.5f);
            peopleMoveCheck(group, person, 1);
        } else {
            peopleDetach(group, person, 0);
            peopleGetPos(group, person, &position);
            position.z += 25.0f;
            peopleWalkTo(group, person, 1, &position);
            peopleMoveCheck(group, person, 1);
        }

        if (elevator->closeAnim >= 0) {
            _floorEventSetMotion(model, elevator->closeAnim, frame);
        }
        if (command & 0x80) {
            GSsndPlayNow(0x27);
        }
        _floorEventWaitMotion(model);
        break;

    case 0xC0:
        _floorEventWaitMotion(model);
        if (command & 0x80) {
            GSsndStopNow(0x29);
            GSsndPlayNow(0x2A);
        }
        break;

    default:
        if (command & 4) {
            animation = elevator->altAnimA;
        } else if (command & 8) {
            animation = elevator->altAnimB;
        }
        if (animation < 0) {
            return -1;
        }
        if (GSmodelCanAnimate(model) == 0) {
            return -1;
        }

        if (command & 0x20) {
            peopleAttach(group, person, floorGroup, elevator->resourceId, elevator->partIndex);
            peopleSetPosXYZ(group, person, 0.0f, 0.0f, 0.0f);
        }
        if (command & 0x10) {
            GSmodelSetAnimIndex(model, animation);
            GSmodelGetFrameCount(model, &frame, 0);
            frame -= 1.0f;
        }

        _floorEventSetMotion(model, animation, frame);

        if (command & 0x40) {
            floorEventCtrlElevator(floor, index, 0xC0, group, person);
        } else if (command & 0x80) {
            GSsndPlayNow(0x29);
        }
        break;
    }

    GSmodelGetFrameCount(model, &frame, 0);
    return (s32)(100.0f * ((2.0f * frame) / (f32)GSgfxVideoGetVsyncRate()));
}

s32 floorEventCtrlDoor(s32 floor, u32 index, u8 mode) {
    FloorEventDoor* door;
    _GSmodel* model;
    s16 animation = -1;
    u32 sound = 0;
    f32 frame = 0.0f;

    if (index >= *floor_door_list_number) {
        return -1;
    }
    door = &floor_door_list[index];

    switch (mode) {
    case 0:
        if (door->openFlag != 0 && GSflagTest(door->openFlag) != 0) {
            return 0;
        }
        if (door->closeFlag != 0 && GSflagTest(door->closeFlag) == 0) {
            return 1;
        }
    case 1:
        if (door->openFlag != 0) {
            GSflagOn(door->openFlag);
        }
        scriptSetCol(door->collisionId, 0);
        break;

    case 2:
        if (door->openFlag != 0 && GSflagTest(door->openFlag) == 0) {
            return 0;
        }
    case 3:
        if (door->openFlag != 0) {
            GSflagOff(door->openFlag);
        }
        scriptSetCol(door->collisionId, 1);
        break;
    }

    if (door->resourceId == 0) {
        return -1;
    }
    model = (_GSmodel*)floorGetResource(floor, door->resourceId);
    if (model == 0) {
        return -1;
    }

    switch (mode) {
    case 0:
        animation = door->openAnim;
        switch (door->doorType) {
        case 1:
            sound = 0x27;
            break;
        case 2:
            sound = 0x27;
            break;
        case 3:
            sound = 0x2B;
            break;
        case 4:
            sound = 0x463;
            break;
        case 5:
            sound = 0x52D;
            break;
        case 6:
            sound = 0x561;
            break;
        }
        break;

    case 1:
        animation = door->openEndAnim;
        if (animation < 0) {
            animation = door->openAnim;
            if (animation >= 0) {
                GSmodelSetAnimIndex(model, animation);
                GSmodelGetFrameCount(model, &frame, 0);
                frame -= 1.0f;
            }
        }
        break;

    case 2:
        animation = door->closeAnim;
        switch (door->doorType) {
        case 1:
            sound = 0x27;
            break;
        case 2:
            sound = 0x27;
            break;
        case 3:
            sound = 0x2B;
            break;
        case 4:
            sound = 0x26;
            break;
        case 5:
            sound = 0x52D;
            break;
        case 6:
            sound = 0x561;
            break;
        }
        break;

    case 3:
        animation = door->closeEndAnim;
        if (animation < 0) {
            animation = door->closeAnim;
            if (animation >= 0) {
                GSmodelSetAnimIndex(model, animation);
                GSmodelGetFrameCount(model, &frame, 0);
                frame -= 1.0f;
            }
        }
        break;
    }

    if (animation < 0) {
        return -1;
    }
    if (GSmodelCanAnimate(model) == 0) {
        return -1;
    }

    _floorEventSetMotion(model, animation, frame);
    if (sound != 0) {
        GSsndPlayNow(sound);
    }

    switch (mode) {
    case 0:
    case 2: {
        u32 savedHero = peopleGetFlags(0, 0x64);
        u32 savedPartner = peopleGetFlags(0, 0x65);
        u32 savedA = peopleGetFlags(0, 0x69);
        u32 savedB = peopleGetFlags(0, 0x68);
        heroMoveInitEvent();
        _floorEventWaitMotion(model);
        heroMoveTermEvent();
        peopleSetFlags(0, 0x64, savedHero);
        peopleSetFlags(0, 0x65, savedPartner);
        peopleSetFlags(0, 0x69, savedA);
        peopleSetFlags(0, 0x68, savedB);
        break;
    }
    }

    return 0;
}

s32 floorEventExecScript(s8 type, u32 arg) {
    u32 current;
    u32 off;
    FloorEventEntry* e;
    u32 i;
    s32 count = 0;

    EvlogSet(type, arg);
    current = GSfloorGetCurrent();
    for (i = 0, off = 0; i < *floor_event_list_number; off += sizeof(FloorEventEntry), i++) {
        e = (FloorEventEntry*)((u8*)floor_event_list + off);
        if (e->floorID == current && e->type == type && e->arg == arg && e->script != 0) {
            scriptSetEventColID(arg);
            floorExecScriptInteger(e->script, e->args[0], e->args[1], e->args[2], e->args[3]);
            count++;
        }
    }
    return count;
}

}

void _floorEventWaitMotion(_GSmodel* model) {
    if (model == 0) {
        return;
    }
    while (GSmodelIsAnimating(model)) {
        GSthreadSwitch();
    }
}

void _floorEventSetMotion(_GSmodel* model, s16 index, f32 frame) {
    if (model != 0) {
        GSmodelSetAnimIndex(model, index);
        GSmodelSetAnimFrame(model, frame);
        GSmodelSetAnimRate(model, 0.5f);
        GSmodelSetAnimType(model, 0);
        GSmodelStartAnimation(model);
    }
}

static void _floorEventWaitME() {
    while (_playMEParam.busy) {
        GSthreadSwitch();
    }
    GSthreadSwitch();
}

static u8 _floorEventPlayMEThread(GSthread* thread) {
    scriptSoundOpenPlayME(_playMEParam.id, 0, 0xFF);
    _playMEParam.busy = 0;
    return 0;
}
