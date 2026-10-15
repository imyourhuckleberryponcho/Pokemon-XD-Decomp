#include <dolphin/types.h>

struct FightActionKindData {
    u8 pri;
    u8 unk1[3];
    void* flowFunc;
    void* dispFunc;
};

struct FightActionData {
    u16 kind;
    u8 unk2[2];
    u32 buff;
};

struct FightActionDispBuff {
    u32 buff[4];
};

struct FightAction {
    u16 kind;
    u8 unk2[2];
    u32 buff;
    FightActionData* fightActionData;
    void* buffDataPtr;
    u32 buffDataId;
    void* actorFightTarget;
    FightActionData* motoFightActionData;
    u32 fifoBanme;
    FightActionDispBuff disp;
};

extern "C" {

extern FightActionKindData fight_action_kind_data[];
extern u32 fight_action_kind_data_number;

void fightActionBiosSetFifoBanme(FightAction* action, u32 banme) {
    if (action != NULL) {
        action->fifoBanme = banme;
    }
}

void* fightActionKindDataBiosGetDispFuncPtr(FightActionKindData* data) {
    if (data == NULL) {
        return NULL;
    }
    return data->dispFunc;
}

void* fightActionKindDataBiosGetFlowFuncPtr(FightActionKindData* data) {
    if (data == NULL) {
        return NULL;
    }
    return data->flowFunc;
}

s32 fightActionKindDataBiosGetPri(FightActionKindData* data) {
    if (data == NULL) {
        return -128;
    }
    return (s8)data->pri;
}

FightActionKindData* fightActionKindDataBiosGetPtr(u16 id) {
    if (id >= fight_action_kind_data_number) {
        return 0;
    }
    return &fight_action_kind_data[id];
}

u32 fightActionDataBiosGetBuff(FightActionData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->buff;
}

u16 fightActionDataBiosGetKind(FightActionData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->kind;
}

void fightActionBiosSetDispBuff(FightAction* action, u16 index, u32 buff) {
    if (action != NULL && index < 4) {
        action->disp.buff[index] = buff;
    }
}

void fightActionBiosSetMotoFightActionDataPtr(FightAction* action, FightActionData* data) {
    if (action != NULL) {
        action->motoFightActionData = data;
    }
}

void fightActionBiosSetBuffDataId(FightAction* action, u32 id) {
    if (action != NULL) {
        action->buffDataId = id;
    }
}

void fightActionBiosSetBuffDataPtr(FightAction* action, void* ptr) {
    if (action != NULL) {
        action->buffDataPtr = ptr;
    }
}

void fightActionBiosSetActorFightTargetPtr(FightAction* action, void* target) {
    if (action != NULL) {
        action->actorFightTarget = target;
    }
}

void fightActionBiosSetFightActionDataPtr(FightAction* action, FightActionData* data) {
    if (action != NULL) {
        action->fightActionData = data;
    }
}

void fightActionBiosSetBuff(FightAction* action, u32 buff) {
    if (action != NULL) {
        action->buff = buff;
    }
}

void fightActionBiosSetKind(FightAction* action, u16 kind) {
    if (action != NULL) {
        action->kind = kind;
    }
}

u32 fightActionBiosGetBuffDataId(FightAction* action) {
    if (action == NULL) {
        return 0;
    }
    return action->buffDataId;
}

void* fightActionBiosGetBuffDataPtr(FightAction* action) {
    if (action == NULL) {
        return NULL;
    }
    return action->buffDataPtr;
}

void* fightActionBiosGetActorFightTargetPtr(FightAction* action) {
    if (action == NULL) {
        return NULL;
    }
    return action->actorFightTarget;
}

FightActionData* fightActionBiosGetFightActionDataPtr(FightAction* action) {
    if (action == NULL) {
        return 0;
    }
    return action->fightActionData;
}

u32 fightActionBiosGetBuff(FightAction* action) {
    if (action == NULL) {
        return 0;
    }
    return action->buff;
}

u16 fightActionBiosGetKind(FightAction* action) {
    if (action == NULL) {
        return 0;
    }
    return action->kind;
}

void fightActionBiosCopy(FightAction* dst, FightAction* src) {
    if (dst != NULL && src != NULL) {
        dst->kind = src->kind;
        dst->buff = src->buff;
        dst->fightActionData = src->fightActionData;
        dst->buffDataPtr = src->buffDataPtr;
        dst->buffDataId = src->buffDataId;
        dst->actorFightTarget = src->actorFightTarget;
        dst->motoFightActionData = src->motoFightActionData;
        dst->fifoBanme = src->fifoBanme;
        dst->disp = src->disp;
    }
}

}
