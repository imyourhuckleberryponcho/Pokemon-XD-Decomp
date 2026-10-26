#include <dolphin/types.h>

struct PeopleWork {
    u8 active;
    u8 unk01[7];
    void* model;
    u8 unk0C[4];
    u32 flags;
    u8 unk14[0x94];
    f32 prevX;
    f32 prevY;
    f32 prevZ;
};

extern "C" {
s32 _people_num;
PeopleWork* _pPeopleWorkTop;
void GSmodelSetRotation(void* model, void* rotation);
void* GSmodelGetRotation(void* model);
void* GSmodelGetRotationPtr(void* model);
void GSmodelSetPosition(void* model, void* position);
void* GSmodelGetPosition(void* model);
void* GSmodelGetPositionPtr(void* model);
void GScolsys2HumanEnable(s32 id);
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
void* getHeroPtr__4HeroFv();
u32 getFollowerGrpID__4HeroFv(void*);
u32 getFollowerResID__4HeroFv(void*);

void peopleBiosSetTresureID(PeopleWork* work, u32 id);
bool peopleBiosCheckFlag(PeopleWork* work, u32 flags);
void peopleBiosSetFlagOff(PeopleWork* work, u32 flags);
void peopleBiosSetFlagOn(PeopleWork* work, u32 flags);
void peopleBiosSetFlags(PeopleWork* work, u32 flags);
void* peopleBiosGetModelPtr(PeopleWork* work);
void peopleBiosSetPrevPos(PeopleWork* work, f32* pos);
f32* peopleBiosGetPrevPosPtr(PeopleWork* work);
void peopleBiosSetRot(PeopleWork* work, void* rotation);
void* peopleBiosGetRot(PeopleWork* work);
void* peopleBiosGetRotPtr(PeopleWork* work);
void peopleBiosSetPos(PeopleWork* work, void* position);
void* peopleBiosGetPos(PeopleWork* work);
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
void peopleBiosPushData(void* buffer,u32 size);
void peopleBiosPopData(void* buffer,u32 size);

s32 peopleBiosGetPushDataSize() {
    s32 index=0;
    s32 size=8;
    while(index<peopleBiosGetMaxNum()) {
        PeopleWork* work=peopleBiosGetWorkPtr(index);
        if(work->active) {
            size+=0x220;
            if(*(u16*)((u8*)work+0x74) && *(void**)((u8*)work+0x78))
                size+=*(u16*)((u8*)work+0x74)*12;
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
            memcpy(data,(u8*)work+12,0x184);
            memcpy(data+0x184,GSmodelGetPositionPtr(model),12);
            memcpy(data+0x190,GSmodelGetRotationPtr(model),12);
            memcpy(data+0x19c,model+0x5b4,12);
            memcpy(data+0x1a8,model+0x5c0,12);
            GSmodelPushState(model,data+0x1b4);
            if(*(u16*)((u8*)work+0x74) && *(void**)((u8*)work+0x78)) {
                u8* next=data+0x220;
                memcpy(next,*(void**)((u8*)work+0x78),*(u16*)((u8*)work+0x74)*12);
                next+=*(u16*)((u8*)work+0x74)*12;
                peopleFreeWalkList(*(u32*)((u8*)work+0x14),*(u32*)((u8*)work+0x18));
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
    memset(_pPeopleWorkTop,0,_people_num*0x1b0);
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
                memcpy((u8*)work+12,data,0x184);
                if(work->model) GSmodelPopState(work->model,data+0x1b4);
                works[index++]=work;
                if(*(u16*)((u8*)work+0x74) && *(void**)((u8*)work+0x78)) {
                    u8* next=data+0x220;
                    next+=*(u16*)((u8*)work+0x74)*12;
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
                peopleBiosSetDispFlag(work,*((u8*)work+0xd));
                peopleBiosSetCollision(work,*((u8*)work+0xf));
                peopleSetMotionType(work,*(u32*)((u8*)work+0x9c));
                GSmodelPopState(model,data+0x1b4);
                if(*(s32*)((u8*)work+0x11c)!=-1 && *(s32*)((u8*)work+0x120)!=-1) {
                    peopleDoAttach(model,*(s32*)((u8*)work+0x11c),*(s32*)((u8*)work+0x120),*(u32*)((u8*)work+0x124),0);
                    f32* vec=(f32*)GSmodelGetPositionPtr(model);
                    vec[0]=*(f32*)(data+0x184); vec[1]=*(f32*)(data+0x188); vec[2]=*(f32*)(data+0x18c);
                    vec=(f32*)GSmodelGetRotationPtr(model);
                    vec[0]=*(f32*)(data+0x190); vec[1]=*(f32*)(data+0x194); vec[2]=*(f32*)(data+0x198);
                    GSmodelSetPosition(model,data+0x19c);
                    GSmodelSetRotation(model,data+0x1a8);
                }
                *((u8*)work+0xc0)=0; *((u8*)work+0x10c)=0;
                _peopleRegisterAnimMix(work);
                if(*((u8*)work+0x154)) GSmodelEnableAnimBlend(work->model);
                if(*((u8*)work+0xc4)) {
                    for(s32 i=0;i<60;i++) _peopleDoNeckUpdate(work);
                }
                if(*(u16*)((u8*)work+0x74) && *(void**)((u8*)work+0x78)) {
                    next=data+0x220;
                    *(void**)((u8*)work+0x78)=GSmemAlloc(*(u16*)((u8*)work+0x74)*12);
                    if(*(void**)((u8*)work+0x78)) memcpy(*(void**)((u8*)work+0x78),next,*(u16*)((u8*)work+0x74)*12);
                    else { *(u16*)((u8*)work+0x74)=0; *(u16*)((u8*)work+0x76)=0; }
                    next+=*(u16*)((u8*)work+0x74)*12;
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
        if (work->active != 0 && *(u32*)((u8*)work + 0x1C) == objectID) {
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
        if (work->active != 0 && *(u16*)((u8*)work + 0x17C) == id) {
            return work;
        }
        index++;
    }
    return 0;
}

void peopleBiosSetTresureID(PeopleWork* work, u32 id) {
    *(u16*)((u8*)work + 0x17C) = id;
}

#pragma dont_inline on
void peopleBiosSetCollision(PeopleWork* work, u8 enabled) {
    *(u8*)((u8*)work + 0x0F) = enabled;
    s32 id = *(s32*)((u8*)work + 0x50);
    if (id >= 0) {
        GScolsys2HumanEnable(id);
    }
}
#pragma dont_inline reset

#pragma dont_inline on
void peopleBiosSetDispFlag(PeopleWork* work, u8 visible) {
    void* model = peopleBiosGetModelPtr(work);
    if (model != 0) {
        *(u8*)((u8*)work + 0x0D) = visible;
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

void* peopleBiosGetRot(PeopleWork* work) {
    return GSmodelGetRotation(work->model);
}

void* peopleBiosGetRotPtr(PeopleWork* work) {
    return GSmodelGetRotationPtr(work->model);
}

void peopleBiosSetPos(PeopleWork* work, void* position) {
    GSmodelSetPosition(work->model, position);
}

void* peopleBiosGetPos(PeopleWork* work) {
    return GSmodelGetPosition(work->model);
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
    if (*(u16*)((u8*)work + 0x17C) != 0) {
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
            memset(work, 0, 0x1B0);
            work->active = 1;
            *(PeopleWork**)((u8*)work + 4) = work;
            *(s32*)((u8*)work + 0x50) = -1;
            f32 value = *(f32*)((u8*)work + 0x20);
            *(f32*)((u8*)work + 0x28) = value;
            return work;
        }
        index++;
    }
    return 0;
}
#pragma dont_inline reset

PeopleWork* peopleBiosGetPeopleWork(u32 id0, u32 id1) {
    u8* work = (u8*)_pPeopleWorkTop;
    u8* end = work + _people_num * 0x1B0;
    while (work != end) {
        if (work[0] != 0 && *(u32*)(work + 0x18) == id1 && *(u32*)(work + 0x14) == id0) {
            return (PeopleWork*)work;
        }
        work += 0x1B0;
    }
    return 0;
}

#pragma dont_inline on
PeopleWork* peopleBiosGetWorkPtr(s32 index) {
    if (index < 0 || _people_num <= index) {
        return 0;
    }
    return (PeopleWork*)((u8*)_pPeopleWorkTop + index * 0x1B0);
}
#pragma dont_inline reset

#pragma dont_inline on
s32 peopleBiosGetMaxNum(void) {
    return _people_num;
}
#pragma dont_inline reset

bool peopleBiosFreeWork(PeopleWork* work) {
    work->active = 0;
    *((u8*)work + 0x0C) = 0;
    return true;
}

PeopleWork* peopleBiosAllocWork(s32 count) {
    PeopleWork* top = (PeopleWork*)GSmemAllocClr(count * 0x1B0);
    _pPeopleWorkTop = top;
    _people_num = count;
    return top;
}

u8 isAnimBlend__13tagPeopleWorkCFv(PeopleWork* work) {
    return *((u8*)work + 0x154);
}

bool isFollower__13tagPeopleWorkCFv(const PeopleWork* work) {
    void* hero = getHeroPtr__4HeroFv();
    if (*(const u32*)((const u8*)work+0x14)==getFollowerGrpID__4HeroFv(hero) &&
        *(const u32*)((const u8*)work+0x18)==getFollowerResID__4HeroFv(hero)) return true;
    return false;
}

bool isHero__13tagPeopleWorkCFv(PeopleWork* work) {
    return *(u32*)((u8*)work + 0x18) == 0x64;
}

}
