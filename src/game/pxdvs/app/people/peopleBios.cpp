#include <dolphin/types.h>
#include <game/peoplework.h>
#ifndef __MWERKS__
struct Hero { public: static Hero* getHeroPtr(); u16 itemQuantity(u16); u8 getHeroStyle() const; void setBattleResumeFloorID(uint); void setBattleResumeFloorIndex(u8); u8 getFollowerID(); u32 getFollowerGrpID(); u32 getFollowerResID(); void setFollowerGrpID(u32); void setFollowerResID(u32); void setFollowerID(u8); };
#define getHeroPtr__4HeroFv(...) ((void*)Hero::getHeroPtr(__VA_ARGS__))
#define getFollowerGrpID__4HeroFv(o, ...) ((u32)((Hero*)(o))->getFollowerGrpID(__VA_ARGS__))
#define getFollowerResID__4HeroFv(o, ...) ((u32)((Hero*)(o))->getFollowerResID(__VA_ARGS__))
#endif

struct PeopleWork {
    u8 active;
    u8 unk01[7];
    void* model;
    u8 unk0C[4];
    u32 flags;
    u8 unk14[0x64];
    void* points;
    u8 pad7C[0x2C];
    f32 prevX;
    f32 prevY;
    f32 prevZ;
};

extern "C" {
s32 _people_num;
PeopleWork* _pPeopleWorkTop;
#ifdef __MWERKS__
#define PEOPLE_WORK_SIZE 0x1B0
#else
extern "C" u32 peoplePCWorkSize(void);
#define PEOPLE_WORK_SIZE peoplePCWorkSize()
extern "C" void* GSmodelPCAttachPositionPtr(void* model);
extern "C" void* GSmodelPCAttachRotationPtr(void* model);
#endif
void GSmodelSetRotation(void* model, void* rotation);
void GSmodelGetRotation(void* model, void* rotation);
void* GSmodelGetRotationPtr(void* model);
void GSmodelSetPosition(void* model, void* position);
void GSmodelGetPosition(void* model, void* position);
void* GSmodelGetPositionPtr(void* model);
void GScolsys2HumanEnable(s32 id, u8 enable);
void GSmodelSetVisibility(void* model, u8 visible);
u8 GSmodelGetVisibility(void* model);
void* GSmemAllocClr(u32 size);
void* memset(void* dst, int value, u32 size);

s32 peopleBiosGetMaxNum(void);

void* memcpy(void*, const void*, u32);
void GSmodelPushState(void*, void*);
void GSmodelPopState(void*, void*);
void peopleFreeWalkList(u32,u32);
void peopleOpenSub(PeopleWork*,u32,u32,u32);
void peopleSetMotionType(PeopleWork*,u32);
void peopleDoAttach(void*,s32,s32,u32,u32);
void _peopleRegisterAnimMix(PeopleWork*);
void GSmodelEnableAnimBlend(void*);
void _peopleDoNeckUpdate(PeopleWork*);
void* GSmemAlloc(u32);
void gimmickBoxPop();
#ifdef __MWERKS__
void* getHeroPtr__4HeroFv();
#endif
#ifdef __MWERKS__
u32 getFollowerGrpID__4HeroFv(void*);
#endif
#ifdef __MWERKS__
u32 getFollowerResID__4HeroFv(void*);
#endif

void peopleBiosSetTresureID(PeopleWork* work, u32 id);
bool peopleBiosCheckFlag(PeopleWork* work, u32 flags);
void peopleBiosSetFlagOff(PeopleWork* work, u32 flags);
void peopleBiosSetFlagOn(PeopleWork* work, u32 flags);
void peopleBiosSetFlags(PeopleWork* work, u32 flags);
void* peopleBiosGetModelPtr(PeopleWork* work);
void peopleBiosSetPrevPos(PeopleWork* work, f32* pos);
f32* peopleBiosGetPrevPosPtr(PeopleWork* work);
void peopleBiosSetRot(PeopleWork* work, void* rotation);
void peopleBiosGetRot(PeopleWork* work, void* rotation);
void* peopleBiosGetRotPtr(PeopleWork* work);
void peopleBiosSetPos(PeopleWork* work, void* position);
void peopleBiosGetPos(PeopleWork* work, void* position);
void* peopleBiosGetPosPtr(PeopleWork* work);
void peopleBiosSetCollision(PeopleWork* work, u8 enabled);
void peopleBiosSetDispFlag(PeopleWork* work, u8 visible);
s32 peopleBiosGetState(PeopleWork* work);
bool peopleBiosFreeWork(PeopleWork* work);
u8 isAnimBlend__13tagPeopleWorkCFv(PeopleWork* work);
bool isHero__13tagPeopleWorkCFv(PeopleWork* work);
PeopleWork* peopleBiosGetWorkPtr(s32 index);
s32 peopleBiosGetMaxNum(void);
PeopleWork* peopleBiosAllocWork(s32 count);
PeopleWork* peopleBiosGetNewWork(void);
s32 peopleBiosGetUseObjIDSize(u32 objectID);
PeopleWork* peopleBiosGetTresureIDToPeopleWork(u32 treasureID);
PeopleWork* peopleBiosGetPeopleWork(u32 id0, u32 id1);
bool isFollower__13tagPeopleWorkCFv(const PeopleWork* work);
s32 peopleBiosGetPushDataSize();
#ifndef __MWERKS__
static void _peoplePCSaveState(u8* dst, PeopleWorkLayout* w) {
    memcpy(dst, &w->active, 0x78 - 0xC);
    *(u32*)(dst + 0x6C) = (u32)(uintptr_t)w->points;
    memcpy(dst + 0x70, (u8*)&w->points + sizeof(void*), 0x184 - 0x70);
}
static void _peoplePCRestoreState(PeopleWorkLayout* w, const u8* src) {
    memcpy(&w->active, src, 0x78 - 0xC);
    w->points = (void*)(uintptr_t)*(const u32*)(src + 0x6C);
    memcpy((u8*)&w->points + sizeof(void*), src + 0x70, 0x184 - 0x70);
}
#endif
void peopleBiosPushData(void* buffer,u32 size);
void peopleBiosPopData(void* buffer,u32 size);

s32 peopleBiosGetPushDataSize() {
    s32 index=0;
    s32 size=8;
    while(index<peopleBiosGetMaxNum()) {
        PeopleWork* work=peopleBiosGetWorkPtr(index);
        if(work->active) {
            size+=0x220;
            if(((PeopleWorkLayout*)(work))->pointCount && ((PeopleWorkLayout*)(work))->points)
                size+=((PeopleWorkLayout*)(work))->pointCount*12;
        }
        index++;
    }
    return size;
}

void peopleBiosPushData(void* buffer,u32 size) {
    PeopleWork* work;
    u8* end;
    u8* data;
    u8* model;
    s32 index;
    u32 count;
    count=0;
    data=(u8*)buffer+8;
    index=0;
    end=(u8*)buffer+size;
    while(index<peopleBiosGetMaxNum()) {
        work=peopleBiosGetWorkPtr(index);
        if(work->active) {
            model=(u8*)work->model;
            count++;
#ifdef __MWERKS__
            memcpy(data,(u8*)work+12,0x184);
#else
            _peoplePCSaveState(data,(PeopleWorkLayout*)work);
#endif
            memcpy(data+0x184,GSmodelGetPositionPtr(model),12);
            memcpy(data+0x190,GSmodelGetRotationPtr(model),12);
#ifdef __MWERKS__
            memcpy(data+0x19c,model+0x5b4,12);
            memcpy(data+0x1a8,model+0x5c0,12);
#else
            memcpy(data+0x19c,GSmodelPCAttachPositionPtr(model),12);
            memcpy(data+0x1a8,GSmodelPCAttachRotationPtr(model),12);
#endif
            GSmodelPushState(model,data+0x1b4);
            if(((PeopleWorkLayout*)(work))->pointCount && ((PeopleWorkLayout*)(work))->points) {
                u8* next=data+0x220;
                memcpy(next,((PeopleWorkLayout*)(work))->points,((PeopleWorkLayout*)(work))->pointCount*12);
                next+=((PeopleWorkLayout*)(work))->pointCount*12;
                peopleFreeWalkList(((PeopleWorkLayout*)(work))->groupID,((PeopleWorkLayout*)(work))->peopleID);
                data=next;
            } else data+=0x220;
            if(data>end) return;
        }
        index++;
    }
    *(u32*)buffer=size;
    *((u32*)buffer+1)=count;
}

void peopleBiosPopData(void* buffer,u32 size) {
    memset(_pPeopleWorkTop,0,_people_num*PEOPLE_WORK_SIZE);
    if(*(u32*)buffer==size && *((u32*)buffer+1)<=64) {
        u32 count;
        s32 index;
        PeopleWork* works[64];
        count=*((u32*)buffer+1);
        {
            PeopleWork* work;
            u8* data;
            u32 remaining;
            remaining=count;
            data=(u8*)buffer+8;
            index=0;
            while(remaining--) {
                work=peopleBiosGetNewWork();
                peopleOpenSub(work,*(u32*)(data+8),*(u32*)(data+12),*(u32*)(data+16));
#ifdef __MWERKS__
                memcpy((u8*)work+12,data,0x184);
#else
                _peoplePCRestoreState((PeopleWorkLayout*)work,data);
#endif
                if(work->model) GSmodelPopState(work->model,data+0x1b4);
                works[index++]=work;
                if(((PeopleWorkLayout*)(work))->pointCount && ((PeopleWorkLayout*)(work))->points) {
                    u8* next=data+0x220;
                    next+=((PeopleWorkLayout*)(work))->pointCount*12;
                    data=next;
                } else data+=0x220;
            }
        }
        {
            u8* next;
            PeopleWork* work;
            void* model;
            u8* data;
            data=(u8*)((u32)buffer+8);
            index=0;
            while(count--) {
                work=works[index++];
                model=work->model;
                peopleBiosSetDispFlag(work,((PeopleWorkLayout*)(work))->display);
                peopleBiosSetCollision(work,((PeopleWorkLayout*)(work))->flagF);
                peopleSetMotionType(work,((PeopleWorkLayout*)(work))->motionType);
                GSmodelPopState(model,data+0x1b4);
                if(((PeopleWorkLayout*)(work))->attachGroupID!=-1 && ((PeopleWorkLayout*)(work))->attachID!=-1) {
                    peopleDoAttach(model,((PeopleWorkLayout*)(work))->attachGroupID,((PeopleWorkLayout*)(work))->attachID,*(u32*)&((PeopleWorkLayout*)(work))->attachPart,0);
                    f32* vec=(f32*)GSmodelGetPositionPtr(model);
                    vec[0]=*(f32*)(data+0x184); vec[1]=*(f32*)(data+0x188); vec[2]=*(f32*)(data+0x18c);
                    vec=(f32*)GSmodelGetRotationPtr(model);
                    vec[0]=*(f32*)(data+0x190); vec[1]=*(f32*)(data+0x194); vec[2]=*(f32*)(data+0x198);
                    GSmodelSetPosition(model,data+0x19c);
                    GSmodelSetRotation(model,data+0x1a8);
                }
                ((PeopleWorkLayout*)(work))->neckReg=0; ((PeopleWorkLayout*)(work))->chestReg=0;
                _peopleRegisterAnimMix(work);
                if(((PeopleWorkLayout*)(work))->blend) GSmodelEnableAnimBlend(work->model);
                if(((PeopleWorkLayout*)(work))->neckMode) {
                    for(s32 i=0;i<60;i++) _peopleDoNeckUpdate(work);
                }
                if(((PeopleWorkLayout*)(work))->pointCount && ((PeopleWorkLayout*)(work))->points) {
                    next=data+0x220;
                    ((PeopleWorkLayout*)(work))->points=GSmemAlloc(((PeopleWorkLayout*)(work))->pointCount*12);
                    if(((PeopleWorkLayout*)(work))->points) memcpy(((PeopleWorkLayout*)(work))->points,next,((PeopleWorkLayout*)(work))->pointCount*12);
                    else { ((PeopleWorkLayout*)(work))->pointCount=0; ((PeopleWorkLayout*)(work))->pointIndex=0; }
                    next+=((PeopleWorkLayout*)(work))->pointCount*12;
                    data=next;
                } else data+=0x220;
            }
            gimmickBoxPop();
        }
    }
}

s32 peopleBiosGetUseObjIDSize(u32 objectID) {
    s32 index = 0;
    s32 count = 0;
    while (index < peopleBiosGetMaxNum()) {
        PeopleWork* work = peopleBiosGetWorkPtr(index);
        if (work->active != 0 && ((PeopleWorkLayout*)(work))->objectID == objectID) {
            count++;
        }
        index++;
    }
    return count;
}

PeopleWork* peopleBiosGetTresureIDToPeopleWork(u32 treasureID) {
    u16 id = (u16)treasureID;
    s32 index = 0;
    PeopleWork* work;
    while (index < peopleBiosGetMaxNum()) {
        work = peopleBiosGetWorkPtr(index);
        if (work->active != 0 && ((PeopleWorkLayout*)(work))->f17C == id) {
            return work;
        }
        index++;
    }
    return 0;
}

void peopleBiosSetTresureID(PeopleWork* work, u32 id) {
    ((PeopleWorkLayout*)(work))->f17C = id;
}

#pragma dont_inline on
void peopleBiosSetCollision(PeopleWork* work, u8 enabled) {
    ((PeopleWorkLayout*)(work))->flagF = enabled;
    s32 id = ((PeopleWorkLayout*)(work))->humanID;
    if (id >= 0) {
        GScolsys2HumanEnable(id, enabled);
    }
}
#pragma dont_inline reset

#pragma dont_inline on
void peopleBiosSetDispFlag(PeopleWork* work, u8 visible) {
    void* model = peopleBiosGetModelPtr(work);
    if (model != 0) {
        ((PeopleWorkLayout*)(work))->display = visible;
        GSmodelSetVisibility(model, visible);
    }
}
#pragma dont_inline reset

bool peopleBiosCheckFlag(PeopleWork* work, u32 flags) {
    return (work->flags & flags) != 0;
}

void peopleBiosSetFlagOff(PeopleWork* work, u32 flags) {
    work->flags &= ~flags;
}

void peopleBiosSetFlagOn(PeopleWork* work, u32 flags) {
    work->flags |= flags;
}

void peopleBiosSetFlags(PeopleWork* work, u32 flags) {
    work->flags = flags;
}

#pragma dont_inline on
void* peopleBiosGetModelPtr(PeopleWork* work) {
    return work->model;
}
#pragma dont_inline reset

void peopleBiosSetPrevPos(PeopleWork* work, f32* pos) {
    work->prevX = pos[0];
    work->prevY = pos[1];
    work->prevZ = pos[2];
}

f32* peopleBiosGetPrevPosPtr(PeopleWork* work) {
    return &work->prevX;
}

void peopleBiosSetRot(PeopleWork* work, void* rotation) {
    GSmodelSetRotation(work->model, rotation);
}

void peopleBiosGetRot(PeopleWork* work, void* rotation) {
    GSmodelGetRotation(work->model, rotation);
}

void* peopleBiosGetRotPtr(PeopleWork* work) {
    return GSmodelGetRotationPtr(work->model);
}

void peopleBiosSetPos(PeopleWork* work, void* position) {
    GSmodelSetPosition(work->model, position);
}

void peopleBiosGetPos(PeopleWork* work, void* position) {
    GSmodelGetPosition(work->model, position);
}

void* peopleBiosGetPosPtr(PeopleWork* work) {
    return GSmodelGetPositionPtr(work->model);
}

s32 peopleBiosGetState(PeopleWork* work) {
    if (work == 0) {
        return 0;
    }
    if (work->active == 0) {
        return 0;
    }

    s32 state = 1;
    if (GSmodelGetVisibility(work->model) != 0) {
        state |= 2;
    }
    if (((PeopleWorkLayout*)(work))->f17C != 0) {
        state |= 4;
    }
    return state;
}

#pragma dont_inline on
PeopleWork* peopleBiosGetNewWork(void) {
    PeopleWork* work;
    s32 index = 0;
    while (index < peopleBiosGetMaxNum()) {
        work = peopleBiosGetWorkPtr(index);
        if (work->active == 0) {
            memset(work, 0, PEOPLE_WORK_SIZE);
            work->active = 1;
#ifdef __MWERKS__
            *(PeopleWork**)((u8*)work + 4) = work;
#else
            ((PeopleWorkLayout*)(work))->searchID = (u32)(uintptr_t)work;
#endif
            ((PeopleWorkLayout*)(work))->humanID = -1;
            f32 value = ((PeopleWorkLayout*)(work))->walkRate;
            ((PeopleWorkLayout*)(work))->curRate = value;
            return work;
        }
        index++;
    }
    return 0;
}
#pragma dont_inline reset

PeopleWork* peopleBiosGetPeopleWork(u32 id0, u32 id1) {
    u8* work = (u8*)_pPeopleWorkTop;
    u8* end = work + _people_num * PEOPLE_WORK_SIZE;
    while (work != end) {
#ifdef __MWERKS__
        if (work[0] != 0 && *(u32*)(work + 0x18) == id1 && *(u32*)(work + 0x14) == id0) {
#else
        if (work[0] != 0 && ((PeopleWorkLayout*)work)->peopleID == id1 && ((PeopleWorkLayout*)work)->groupID == id0) {
#endif
            return (PeopleWork*)work;
        }
        work += PEOPLE_WORK_SIZE;
    }
    return 0;
}

#pragma dont_inline on
PeopleWork* peopleBiosGetWorkPtr(s32 index) {
    if (index < 0 || _people_num <= index) {
        return 0;
    }
    return (PeopleWork*)((u8*)_pPeopleWorkTop + index * PEOPLE_WORK_SIZE);
}
#pragma dont_inline reset

#pragma dont_inline on
s32 peopleBiosGetMaxNum(void) {
    return _people_num;
}
#pragma dont_inline reset

bool peopleBiosFreeWork(PeopleWork* work) {
    work->active = 0;
    ((PeopleWorkLayout*)(work))->active = 0;
    return true;
}

PeopleWork* peopleBiosAllocWork(s32 count) {
    PeopleWork* top = (PeopleWork*)GSmemAllocClr(count * PEOPLE_WORK_SIZE);
    _pPeopleWorkTop = top;
    _people_num = count;
    return top;
}

u8 isAnimBlend__13tagPeopleWorkCFv(PeopleWork* work) {
    return ((PeopleWorkLayout*)(work))->blend;
}

bool isFollower__13tagPeopleWorkCFv(const PeopleWork* work) {
    void* hero = getHeroPtr__4HeroFv();
    if (*(const u32*)((const u8*)work+0x14)==getFollowerGrpID__4HeroFv(hero) &&
        *(const u32*)((const u8*)work+0x18)==getFollowerResID__4HeroFv(hero)) return true;
    return false;
}

bool isHero__13tagPeopleWorkCFv(PeopleWork* work) {
    return ((PeopleWorkLayout*)(work))->peopleID == 0x64;
}

}

#ifndef __MWERKS__
struct tagPeopleWork {
    bool isAnimBlend() const;
    bool isFollower() const;
    bool isHero() const;
};
bool tagPeopleWork::isAnimBlend() const { return isAnimBlend__13tagPeopleWorkCFv((PeopleWork*)this) != 0; }
bool tagPeopleWork::isFollower() const { return isFollower__13tagPeopleWorkCFv((const PeopleWork*)this); }
bool tagPeopleWork::isHero() const { return isHero__13tagPeopleWorkCFv((PeopleWork*)this); }
#endif
