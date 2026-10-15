#include <dolphin/types.h>

// Built with -O4,s (see configure.py).

struct FightJoukenLinkData {
    u8 joint;
    u8 unk1;
    u16 joukenDataId;
    u16 nextLinkDataId;
};

struct FightJoukenValue {
    u8 kind;
    u8 hoseiFlag;
    s16 kake;
    s16 waru;
    u16 target;
    u16 buff;
};

struct FightJoukenData {
    u8 form;
    u8 unk1;
    u16 link;
    FightJoukenValue value[2];
};

extern "C" {

extern FightJoukenLinkData fight_jouken_link_data[];
extern u32 fight_jouken_link_data_number;
extern FightJoukenData fight_jouken_data[];
extern u32 fight_jouken_data_number;

FightJoukenLinkData* fightJoukenLinkDataBiosGetDataPtr(u16 id);
FightJoukenValue* fightJoukenDataBiosGetValuePtr(u16 id, u16 index);
FightJoukenData* fightJoukenDataBiosGetDataPtr(u16 id);

u16 fightJoukenLinkDataBiosGetNextLinkDataId(u16 id) {
    FightJoukenLinkData* data = fightJoukenLinkDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->nextLinkDataId;
}

u16 fightJoukenLinkDataBiosGetJoukenDataId(u16 id) {
    FightJoukenLinkData* data = fightJoukenLinkDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->joukenDataId;
}

u8 fightJoukenLinkDataBiosGetJoint(u16 id) {
    FightJoukenLinkData* data = fightJoukenLinkDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->joint;
}

FightJoukenLinkData* fightJoukenLinkDataBiosGetDataPtr(u16 id) {
    if (id >= fight_jouken_link_data_number) {
        return 0;
    }
    return &fight_jouken_link_data[id];
}

s16 fightJoukenDataBiosGetValueWaru(u16 id, u16 index) {
    FightJoukenValue* value = fightJoukenDataBiosGetValuePtr(id, index);
    if (value == NULL) {
        return 0;
    }
    return value->waru;
}

s16 fightJoukenDataBiosGetValueKake(u16 id, u16 index) {
    FightJoukenValue* value = fightJoukenDataBiosGetValuePtr(id, index);
    if (value == NULL) {
        return 0;
    }
    return value->kake;
}

u8 fightJoukenDataBiosGetValueHoseiFlag(u16 id, u16 index) {
    FightJoukenValue* value = fightJoukenDataBiosGetValuePtr(id, index);
    if (value == NULL) {
        return 0;
    }
    return value->hoseiFlag ? 1 : 0;
}

u16 fightJoukenDataBiosGetValueBuff(u16 id, u16 index) {
    FightJoukenValue* value = fightJoukenDataBiosGetValuePtr(id, index);
    if (value == NULL) {
        return 0;
    }
    return value->buff;
}

u16 fightJoukenDataBiosGetValueTarget(u16 id, u16 index) {
    FightJoukenValue* value = fightJoukenDataBiosGetValuePtr(id, index);
    if (value == NULL) {
        return 0;
    }
    return value->target;
}

u8 fightJoukenDataBiosGetValueKind(u16 id, u16 index) {
    FightJoukenValue* value = fightJoukenDataBiosGetValuePtr(id, index);
    if (value == NULL) {
        return 0;
    }
    return value->kind;
}

u16 fightJoukenDataBiosGetLink(u16 id) {
    FightJoukenData* data = fightJoukenDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->link;
}

u8 fightJoukenDataBiosGetForm(u16 id) {
    FightJoukenData* data = fightJoukenDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->form;
}

FightJoukenValue* fightJoukenDataBiosGetValuePtr(u16 id, u16 index) {
    FightJoukenData* data = fightJoukenDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return &data->value[index];
}

FightJoukenData* fightJoukenDataBiosGetDataPtr(u16 id) {
    if (id >= fight_jouken_data_number) {
        return 0;
    }
    return &fight_jouken_data[id];
}

}
