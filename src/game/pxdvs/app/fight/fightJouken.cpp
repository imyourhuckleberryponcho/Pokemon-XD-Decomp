#include <dolphin/types.h>

struct FightTarget;
struct FightTargetData;

extern "C" {
u16 fightJoukenDataBiosGetLink(u16 id);
u8 fightJoukenDataBiosGetForm(u16 id);
u8 fightJoukenDataBiosGetValueKind(u16 id, u16 index);
u16 fightJoukenDataBiosGetValueTarget(u16 id, u16 index);
u16 fightJoukenDataBiosGetValueBuff(u16 id, u16 index);
s16 fightJoukenDataBiosGetValueKake(u16 id, u16 index);
s16 fightJoukenDataBiosGetValueWaru(u16 id, u16 index);
u8 fightJoukenDataBiosGetValueHoseiFlag(u16 id, u16 index);
u16 fightJoukenLinkDataBiosGetJoukenDataId(u16 id);
u8 fightJoukenLinkDataBiosGetJoint(u16 id);
u16 fightJoukenLinkDataBiosGetNextLinkDataId(u16 id);
u32 HSD_Rand(void);
u8 fightFloor_GetFightType(s32);
FightTarget* fightTargetGetPtr(u16 targetDataId, void* fightPokemon, s32 fightType);
FightTargetData* fightTargetDataBiosGetPtr(u16 id);
u8 fightTargetDataBiosGetStatusKid(FightTargetData* data);
s32 statusGetStatus(u8 statusKind, FightTarget* target, u16, u16, u16);
}

static inline u32 HSD_Rand32(void) {
    u32 lo = HSD_Rand();
    u32 hi = HSD_Rand() << 16;
    return hi | lo;
}

static u8 _fightJoukenExecOne(u16 id, void* fightPokemon);
static s32 _fightJoukenGetValue(u16 id, u16 index, void* fightPokemon);

extern "C" u8 fightJoukenExec(u16 id, void* fightPokemon) {
    u8 result;
    u16 joukenId;
    u8 next;
    result = _fightJoukenExecOne(id, fightPokemon);
    u16 link = fightJoukenDataBiosGetLink(id);
    if (link == 0) {
        return result;
    }
    do {
        joukenId = fightJoukenLinkDataBiosGetJoukenDataId(link);
        next = _fightJoukenExecOne(joukenId, fightPokemon);
        switch (fightJoukenLinkDataBiosGetJoint(joukenId)) {
        case 1:
            if (result || next) {
                result = 1;
            } else {
                result = 0;
            }
            break;
        case 2:
            if (result && next) {
                result = 1;
            } else {
                result = 0;
            }
            break;
        }
        link = fightJoukenLinkDataBiosGetNextLinkDataId(link);
    } while (link != 0);
    return result;
}

static u8 _fightJoukenExecOne(u16 id, void* fightPokemon) {
    s32 values[2];
    u8 i;
    u8 result;
    for (i = 0; i < 2; i++) {
        values[i] = _fightJoukenGetValue(id, i, fightPokemon);
    }
    result = 0;
    switch (fightJoukenDataBiosGetForm(id)) {
    case 0:
        result = 1;
        break;
    case 1:
        if (values[0] == values[1]) {
            result = 1;
        }
        break;
    case 2:
        if (values[0] != values[1]) {
            result = 1;
        }
        break;
    case 3:
        if (values[0] >= values[1]) {
            result = 1;
        }
        break;
    case 4:
        if (values[0] <= values[1]) {
            result = 1;
        }
        break;
    case 5:
        if (values[0] < values[1]) {
            result = 1;
        }
        break;
    case 6:
        if (values[0] > values[1]) {
            result = 1;
        }
        break;
    }
    return result;
}

static s32 _fightJoukenGetValue(u16 id, u16 index, void* fightPokemon) {
    s32 value = 0;
    u8 kind = fightJoukenDataBiosGetValueKind(id, index);
    u16 target = fightJoukenDataBiosGetValueTarget(id, index);
    u16 buff = fightJoukenDataBiosGetValueBuff(id, index);
    s16 kake = fightJoukenDataBiosGetValueKake(id, index);
    s16 waru = fightJoukenDataBiosGetValueWaru(id, index);
    u8 hosei = fightJoukenDataBiosGetValueHoseiFlag(id, index);
    switch (kind) {
    case 0:
        break;
    case 1:
        value = target;
        break;
    case 2: {
        value = target + HSD_Rand32() % (buff - target);
        break;
    }
    case 3: {
        FightTarget* fightTarget = fightTargetGetPtr(target, fightPokemon, fightFloor_GetFightType(0));
        if (fightTarget == NULL) {
            return 0;
        }
        u8 statusKind = fightTargetDataBiosGetStatusKid(fightTargetDataBiosGetPtr(target));
        if (hosei == 0) {
            value = statusGetStatus(statusKind, fightTarget, kake, buff, waru);
        } else {
            value = statusGetStatus(statusKind, fightTarget, 0, buff, 0);
        }
        break;
    }
    }
    if (hosei == 1) {
        value *= kake;
        if (waru != 0) {
            value /= waru;
        }
    }
    return value;
}
