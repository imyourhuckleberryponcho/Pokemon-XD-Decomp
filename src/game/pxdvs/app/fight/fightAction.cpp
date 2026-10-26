#include <dolphin/types.h>

struct FIGHT_ACTION_DATA_dd_ {
    u16 kind;
    u8 unk2[2];
    u32 buff;
};

struct FightActionDispBuff {
    u32 buff[4];
};

struct FIGHT_ACTION {
    u16 kind;
    u32 buff;
    FIGHT_ACTION_DATA_dd_* fightActionData;
    void* buffDataPtr;
    u32 buffDataId;
    void* actorFightTarget;
    FIGHT_ACTION_DATA_dd_* motoFightActionData;
    u32 fifoBanme;
    FightActionDispBuff disp;
};

struct FightActionKindData;

typedef u8 (*FightActionFunc)(FIGHT_ACTION*);

extern "C" {
void fightActionBiosCopy(FIGHT_ACTION* dst, FIGHT_ACTION* src);
u32 fightActionBiosGetBuff(FIGHT_ACTION* action);
FIGHT_ACTION_DATA_dd_* fightActionBiosGetFightActionDataPtr(FIGHT_ACTION* action);
u16 fightActionBiosGetKind(FIGHT_ACTION* action);
void fightActionBiosSetActorFightTargetPtr(FIGHT_ACTION* action, void* target);
void fightActionBiosSetBuff(FIGHT_ACTION* action, u32 buff);
void fightActionBiosSetBuffDataId(FIGHT_ACTION* action, u32 id);
void fightActionBiosSetBuffDataPtr(FIGHT_ACTION* action, void* ptr);
void fightActionBiosSetDispBuff(FIGHT_ACTION* action, u16 index, u32 buff);
void fightActionBiosSetFifoBanme(FIGHT_ACTION* action, u32 banme);
void fightActionBiosSetFightActionDataPtr(FIGHT_ACTION* action, FIGHT_ACTION_DATA_dd_* data);
void fightActionBiosSetKind(FIGHT_ACTION* action, u16 kind);
void fightActionBiosSetMotoFightActionDataPtr(FIGHT_ACTION* action, FIGHT_ACTION_DATA_dd_* data);
u32 fightActionDataBiosGetBuff(FIGHT_ACTION_DATA_dd_* data);
u16 fightActionDataBiosGetKind(FIGHT_ACTION_DATA_dd_* data);
void* fightActionKindDataBiosGetDispFuncPtr(FightActionKindData* data);
void* fightActionKindDataBiosGetFlowFuncPtr(FightActionKindData* data);
s32 fightActionKindDataBiosGetPri(FightActionKindData* data);
FightActionKindData* fightActionKindDataBiosGetPtr(u16 id);

bool fightActionCheckValid(FIGHT_ACTION* action);
u8 fightActionCreate(FIGHT_ACTION* action, FIGHT_ACTION_DATA_dd_* moto, void* actor, u16 kind, u32 buff, FIGHT_ACTION_DATA_dd_* data);
u8 fightActionFlowFifo(FIGHT_ACTION* action);
u8 fightActionDispFifo(void);
u8 fightActionFifoOut(FIGHT_ACTION* out);
FIGHT_ACTION* fightActionFifoIn(FIGHT_ACTION* in);
u8 fightActionDisp(FIGHT_ACTION* action);
void fightActionInit(FIGHT_ACTION* action);
FIGHT_ACTION_DATA_dd_* fightActionSearchDataPtr(FIGHT_ACTION* action);
}

static u8 _fightActionFlowSub(FIGHT_ACTION* action);
static FIGHT_ACTION_DATA_dd_* _fightActionDataSearchDataPtr(FIGHT_ACTION_DATA_dd_* data, u16 kind, s32 buff);

static FIGHT_ACTION _fight_action_fifo[32];
static u32 _fight_action_fifo_head;
static u32 _fight_action_fifo_tail;

extern "C" {

u16 fightActionGetKindDataId(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) {
        return 0;
    }
    FIGHT_ACTION_DATA_dd_* data = fightActionBiosGetFightActionDataPtr(action);
    if (data == 0) {
        return 0;
    }
    return fightActionDataBiosGetKind(data);
}

s32 fightActionGetPri(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) {
        return -128;
    }
    FIGHT_ACTION_DATA_dd_* data = fightActionBiosGetFightActionDataPtr(action);
    if (data == 0) {
        return -128;
    }
    FightActionKindData* kind = fightActionKindDataBiosGetPtr(fightActionDataBiosGetKind(data));
    if (kind == 0) {
        return -128;
    }
    return fightActionKindDataBiosGetPri(kind);
}

void fightActionDispFifoAll(void) {
    u8 r;
    do {
        r = fightActionDispFifo();
    } while (r != 3 && r == 1);
}

u8 fightActionCreateAndFlowFifo(FIGHT_ACTION* action, FIGHT_ACTION_DATA_dd_* moto, void* actor, u16 kind, u32 buff, FIGHT_ACTION_DATA_dd_* data) {
    u8 r = fightActionCreate(action, moto, actor, kind, buff, data);
    if (r != 1) {
        return r;
    }
    return fightActionFlowFifo(action);
}

u8 fightActionDispFifo(void) {
    FIGHT_ACTION tmp;
    if (fightActionFifoOut(&tmp) == 0) {
        return 3;
    }
    return fightActionDisp(&tmp);
}

u8 fightActionFlowFifo(FIGHT_ACTION* action) {
    FIGHT_ACTION tmp;
    u8 result;
    FIGHT_ACTION* in = fightActionFifoIn(action);
    if (in == 0) {
        return 2;
    }
    result = _fightActionFlowSub(action);
    if (result != 1) {
        fightActionFifoOut(&tmp);
    } else {
        fightActionBiosCopy(in, action);
    }
    return result;
}

u8 fightActionDisp(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) {
        return 0;
    }
    FightActionFunc func = (FightActionFunc)fightActionKindDataBiosGetDispFuncPtr(
        fightActionKindDataBiosGetPtr(fightActionDataBiosGetKind(fightActionBiosGetFightActionDataPtr(action))));
    if (func != 0) {
        return func(action);
    }
    return 1;
}

u8 fightActionFifoOut(FIGHT_ACTION* out) {
    if (_fight_action_fifo_tail != _fight_action_fifo_head) {
        *out = _fight_action_fifo[_fight_action_fifo_head];
        _fight_action_fifo_head++;
        _fight_action_fifo_head &= 0x1F;
    } else {
        return 0;
    }
    return 1;
}

FIGHT_ACTION* fightActionFifoIn(FIGHT_ACTION* in) {
    unsigned int tail = _fight_action_fifo_tail;
    FIGHT_ACTION* slot;
    unsigned int next = tail + 1;
    if ((next & 0x1F) != _fight_action_fifo_head) {
        slot = &_fight_action_fifo[tail];
        _fight_action_fifo[tail] = *in;
        _fight_action_fifo_tail = next;
        _fight_action_fifo_tail &= 0x1F;
    } else {
        return 0;
    }
    fightActionBiosSetFifoBanme(in, (s32)tail);
    fightActionBiosSetFifoBanme(slot, tail);
    return slot;
}

void fightActionFifoInit(void) {
    u16 i;
    _fight_action_fifo_head = 0;
    _fight_action_fifo_tail = 0;
    for (i = 0; i < 32; i++) {
        fightActionInit(&_fight_action_fifo[i]);
    }
}

bool fightActionCheckValid(FIGHT_ACTION* action) {
    if (action == 0) {
        return 0;
    }
    if (fightActionBiosGetKind(action) == 0) {
        return 0;
    }
    return fightActionBiosGetFightActionDataPtr(action) != 0;
}

u8 fightActionCreate(FIGHT_ACTION* action, FIGHT_ACTION_DATA_dd_* moto, void* actor, u16 kind, u32 buff, FIGHT_ACTION_DATA_dd_* data) {
    fightActionInit(action);
    fightActionBiosSetKind(action, kind);
    fightActionBiosSetBuff(action, buff);
    fightActionBiosSetFightActionDataPtr(action, data);
    fightActionBiosSetActorFightTargetPtr(action, actor);
    if (fightActionSearchDataPtr(action) == 0) {
        fightActionInit(action);
        return 4;
    }
    fightActionBiosSetBuffDataId(action, buff);
    fightActionBiosSetMotoFightActionDataPtr(action, moto);
    return 1;
}

void fightActionInit(FIGHT_ACTION* action) {
    u16 i;
    fightActionBiosSetKind(action, 0);
    fightActionBiosSetBuff(action, 0);
    fightActionBiosSetFightActionDataPtr(action, 0);
    for (i = 0; i < 4; i++) {
        fightActionBiosSetDispBuff(action, i, 0);
    }
    fightActionBiosSetBuffDataPtr(action, 0);
    fightActionBiosSetBuffDataId(action, 0);
    fightActionBiosSetActorFightTargetPtr(action, 0);
    fightActionBiosSetMotoFightActionDataPtr(action, 0);
    fightActionBiosSetFifoBanme(action, -1);
}

FIGHT_ACTION_DATA_dd_* fightActionSearchDataPtr(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) {
        return 0;
    }
    FIGHT_ACTION_DATA_dd_* found;
    u16 kind = fightActionBiosGetKind(action);
    u32 buff = fightActionBiosGetBuff(action);
    found = _fightActionDataSearchDataPtr(fightActionBiosGetFightActionDataPtr(action), kind, buff);
    if (found == 0) {
        return 0;
    }
    fightActionBiosSetFightActionDataPtr(action, found);
    return found;
}

}

static u8 _fightActionFlowSub(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) {
        return 0;
    }
    FightActionFunc func = (FightActionFunc)fightActionKindDataBiosGetFlowFuncPtr(
        fightActionKindDataBiosGetPtr(fightActionDataBiosGetKind(fightActionBiosGetFightActionDataPtr(action))));
    if (func != 0) {
        return func(action);
    }
    return 1;
}

static FIGHT_ACTION_DATA_dd_* _fightActionDataSearchDataPtr(FIGHT_ACTION_DATA_dd_* data, u16 kind, s32 buff) {
    u16 i;
    FIGHT_ACTION_DATA_dd_* p;
    u16 k;
    s32 b;
    if (data == 0) {
        return 0;
    }
    i = 0;
    while (1) {
        p = &data[i];
        k = fightActionDataBiosGetKind(p);
        if (k == 0) {
            break;
        }
        b = fightActionDataBiosGetBuff(p);
        if (kind == k && buff == b) {
            return p;
        }
        i++;
    }
    return 0;
}
