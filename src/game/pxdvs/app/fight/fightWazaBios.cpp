#include <dolphin/types.h>

struct FightWazaHitKakurituData {
    u8 kake;
    u8 waru;
};

struct FightWazaCriticalData {
    u8 bunbo;
};

struct Joutai {
    u8 unk0[0x10];
};

struct FightWazaJoutai {
    Joutai joutai[9];
};

struct FightWaza {
    u8 wazaBanme;
    u8 unk1;
    u16 motoWazaDataId;
    u16 useWazaDataId;
    u16 targetDataId;
    FightWazaJoutai joutai;
    u8 critical;
    u8 damageValue;
    u8 unk9A[2];
    u32 damage;
    u32 hitDamage;
    u16 iryoku;
    u16 zokusei;
    u8 kaisuu;
    u8 autoMakeFlag;
};

extern "C" {

extern FightWazaHitKakurituData fight_waza_hit_kakuritu_data[];
extern u32 fight_waza_hit_kakuritu_data_number;
extern FightWazaCriticalData fight_waza_critical_data[];
extern u32 fight_waza_critical_data_number;

u8 fightWazaHitKakurituDataBiosGetWaru(FightWazaHitKakurituData* data) {
    if (data == NULL) {
        return 1;
    }
    return data->waru;
}

u8 fightWazaHitKakurituDataBiosGetKake(FightWazaHitKakurituData* data) {
    if (data == NULL) {
        return 1;
    }
    return data->kake;
}

FightWazaHitKakurituData* fightWazaHitKakurituDataBiosGetPtr(u16 id) {
    FightWazaHitKakurituData* data = &fight_waza_hit_kakuritu_data[id];
    if (id < fight_waza_hit_kakuritu_data_number) {
        return data;
    }
    return 0;
}

u8 fightWazaCriticalDataBiosGetBunbo(FightWazaCriticalData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->bunbo;
}

FightWazaCriticalData* fightWazaCriticalDataBiosGetPtr(u16 id) {
    FightWazaCriticalData* data = &fight_waza_critical_data[id];
    if (id < fight_waza_critical_data_number) {
        return data;
    }
    return 0;
}

void fightWazaBiosSetAutoMakeFlag(FightWaza* waza, u8 value) {
    if (waza != NULL) {
        waza->autoMakeFlag = value;
    }
}

void fightWazaBiosSetKaisuu(FightWaza* waza, u8 value) {
    if (waza != NULL) {
        waza->kaisuu = value;
    }
}

void fightWazaBiosSetZokusei(FightWaza* waza, u16 value) {
    if (waza != NULL) {
        waza->zokusei = value;
    }
}

void fightWazaBiosSetIryoku(FightWaza* waza, u16 value) {
    if (waza != NULL) {
        waza->iryoku = value;
    }
}

void fightWazaBiosSetHitDamage(FightWaza* waza, u32 value) {
    if (waza != NULL) {
        waza->hitDamage = value;
    }
}

void fightWazaBiosSetDamage(FightWaza* waza, u32 value) {
    if (waza != NULL) {
        waza->damage = value;
    }
}

void fightWazaBiosSetDamageValue(FightWaza* waza, u8 value) {
    if (waza != NULL) {
        waza->damageValue = value;
    }
}

void fightWazaBiosSetCritical(FightWaza* waza, u8 value) {
    if (waza != NULL) {
        waza->critical = value;
    }
}

void fightWazaBiosSetTargetDataId(FightWaza* waza, u16 value) {
    if (waza != NULL) {
        waza->targetDataId = value;
    }
}

void fightWazaBiosSetUseWazaDataId(FightWaza* waza, u16 value) {
    if (waza != NULL) {
        waza->useWazaDataId = value;
    }
}

void fightWazaBiosSetMotoWazaDataId(FightWaza* waza, u16 value) {
    if (waza != NULL) {
        waza->motoWazaDataId = value;
    }
}

void fightWazaBiosSetWazaBanme(FightWaza* waza, u8 value) {
    if (waza != NULL) {
        waza->wazaBanme = value;
    }
}

u8 fightWazaBiosGetAutoMakeFlag(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->autoMakeFlag;
}

u8 fightWazaBiosGetKaisuu(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->kaisuu;
}

u16 fightWazaBiosGetZokusei(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->zokusei;
}

u16 fightWazaBiosGetIryoku(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->iryoku;
}

u32 fightWazaBiosGetHitDamage(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->hitDamage;
}

u32 fightWazaBiosGetDamage(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->damage;
}

u8 fightWazaBiosGetDamageValue(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->damageValue;
}

u8 fightWazaBiosGetCritical(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->critical;
}

Joutai* fightWazaBiosGetJoutaiPtr(FightWaza* waza, u16 index) {
    if (waza == NULL) {
        return 0;
    }
    if (index >= 9) {
        return 0;
    }
    return &waza->joutai.joutai[index];
}

u16 fightWazaBiosGetTargetDataId(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->targetDataId;
}

u16 fightWazaBiosGetUseWazaDataId(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->useWazaDataId;
}

u16 fightWazaBiosGetMotoWazaDataId(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->motoWazaDataId;
}

u8 fightWazaBiosGetWazaBanme(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    return waza->wazaBanme;
}

void fightWazaBiosCopy(FightWaza* dst, FightWaza* src) {
    if (dst != NULL && src != NULL) {
        dst->wazaBanme = src->wazaBanme;
        dst->motoWazaDataId = src->motoWazaDataId;
        dst->useWazaDataId = src->useWazaDataId;
        dst->targetDataId = src->targetDataId;
        dst->joutai = src->joutai;
        dst->critical = src->critical;
        dst->damageValue = src->damageValue;
        dst->damage = src->damage;
        dst->hitDamage = src->hitDamage;
        dst->iryoku = src->iryoku;
        dst->zokusei = src->zokusei;
        dst->kaisuu = src->kaisuu;
        dst->autoMakeFlag = src->autoMakeFlag;
    }
}

}
