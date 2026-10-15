#include <dolphin/types.h>

struct FightWazaJoutai {
    u8 unk0[0x10];
};

struct FightWaza {
    u8 wazaBanme;               // 0x00
    u16 motoWazaDataId;         // 0x02
    u16 useWazaDataId;          // 0x04
    u16 targetDataId;           // 0x06
    FightWazaJoutai joutai[9];  // 0x08
    u8 critical;                // 0x98
    u8 damageValue;             // 0x99
    s32 damage;                 // 0x9C
    s32 hitDamage;              // 0xA0
    u16 iryoku;                 // 0xA4
    u16 zokusei;                // 0xA6
    u8 kaisuu;                  // 0xA8
    u8 autoMakeFlag;            // 0xA9
};

struct WazaData {
    u8 pri;                // 0x00
    u8 pp;                 // 0x01
    u8 zokuseiDataId;      // 0x02
    u8 rangeId;            // 0x03
    u8 avg;                // 0x04
    u8 addFightKoukaAvg;   // 0x05
    u8 dageki;             // 0x06
    u8 mamoru;             // 0x07
    u8 majikku;            // 0x08
    u8 yokodori;           // 0x09
    u8 oumugaesi;          // 0x0A
    u8 oujanosirusi;       // 0x0B
    u8 unkC[4];
    u8 bouon;              // 0x10
    u8 unk11;
    u8 hidenFlag;          // 0x12
    u8 darkWazaKind;       // 0x13
    u8 riskFlag;           // 0x14
    u8 compatible;         // 0x15
    u8 unk16[2];
    s16 iryoku;            // 0x18
    u8 unk1A[2];
    u16 seqId;             // 0x1C
    u16 wazaFuncDataId;    // 0x1E
    u32 name;              // 0x20
    u8 unk24[0xC];
    u32 wazawzxdataId;     // 0x30
    u8 typeId[3];          // 0x34
};

struct WazaFuncData {
    void* aiValue;              // 0x00
    void* aiHit;                // 0x04
    void* aiDamage;             // 0x08
    void* aiDamageFightPokemon; // 0x0C
    void* wzxType;              // 0x10
    void* wzxVariation;         // 0x14
};

extern "C" {

WazaData* wazaDataBiosGetPtr(u16 id);
u16 wazaDataBiosGetWazaFuncDataId(WazaData* data);
WazaFuncData* wazaFuncDataBiosGetPtr(u16 id);
u8 wazaCheckDarkWaza(u16 id);
u8 zokuseiBiosGetWazaKind(u8 zokusei);

static inline u8 wazaDB_GetDarkWazaKind(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->darkWazaKind;
}

void fightWaza_SetAutoMakeFlag(FightWaza* waza, u8 value) {
    if (waza != 0) {
        waza->autoMakeFlag = value;
    }
}

void fightWaza_SetKaisuu(FightWaza* waza, u8 value) {
    if (waza != 0) {
        waza->kaisuu = value;
    }
}

void fightWaza_SetZokusei(FightWaza* waza, u16 value) {
    if (waza != 0) {
        waza->zokusei = value;
    }
}

void fightWaza_SetIryoku(FightWaza* waza, u16 value) {
    if (waza != 0) {
        waza->iryoku = value;
    }
}

void fightWaza_SetHitDamage(FightWaza* waza, s32 value) {
    if (waza != 0) {
        waza->hitDamage = value;
    }
}

void fightWaza_SetDamage(FightWaza* waza, s32 value) {
    if (waza != 0) {
        waza->damage = value;
    }
}

void fightWaza_SetDamageValue(FightWaza* waza, u8 value) {
    if (waza != 0) {
        waza->damageValue = value;
    }
}

void fightWaza_SetCritical(FightWaza* waza, u8 value) {
    if (waza != 0) {
        waza->critical = value;
    }
}

void fightWaza_SetTargetDataId(FightWaza* waza, u16 value) {
    if (waza != 0) {
        waza->targetDataId = value;
    }
}

void fightWaza_SetUseWazaDataId(FightWaza* waza, u16 value) {
    if (waza != 0) {
        waza->useWazaDataId = value;
    }
}

void fightWaza_SetMotoWazaDataId(FightWaza* waza, u16 value) {
    if (waza != 0) {
        waza->motoWazaDataId = value;
    }
}

void fightWaza_SetWazaBanme(FightWaza* waza, u8 value) {
    if (waza != 0) {
        waza->wazaBanme = value;
    }
}

u8 fightWaza_GetAutoMakeFlag(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->autoMakeFlag;
}

u8 fightWaza_GetKaisuu(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->kaisuu;
}

u16 fightWaza_GetZokusei(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->zokusei;
}

u16 fightWaza_GetIryoku(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->iryoku;
}

s32 fightWaza_GetHitDamage(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->hitDamage;
}

s32 fightWaza_GetDamage(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->damage;
}

u8 fightWaza_GetDamageValue(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->damageValue;
}

u8 fightWaza_GetCritical(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->critical;
}

FightWazaJoutai* fightWaza_GetJoutaiPtr(FightWaza* waza, u16 index) {
    if (waza == 0) {
        return 0;
    }
    if (index >= 9) {
        return 0;
    }
    return &waza->joutai[index];
}

u16 fightWaza_GetTargetDataId(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->targetDataId;
}

u16 fightWaza_GetUseWazaDataId(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->useWazaDataId;
}

u16 fightWaza_GetMotoWazaDataId(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->motoWazaDataId;
}

u8 fightWaza_GetWazaBanme(FightWaza* waza) {
    if (waza == 0) {
        return 0;
    }
    return waza->wazaBanme;
}

void* wazaDB_GetFightWazaWzxVariationFuncPtr(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    WazaFuncData* func = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data));
    if (func == 0) {
        return 0;
    }
    return func->wzxVariation;
}

void* wazaDB_GetFightWazaWzxTypeFuncPtr(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    WazaFuncData* func = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data));
    if (func == 0) {
        return 0;
    }
    return func->wzxType;
}

void* wazaDB_GetFightTrainerAiWazaDamageFightPokemonFuncPtr(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    WazaFuncData* func = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data));
    if (func == 0) {
        return 0;
    }
    return func->aiDamageFightPokemon;
}

void* wazaDB_GetFightTrainerAiWazaDamageFuncPtr(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    WazaFuncData* func = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data));
    if (func == 0) {
        return 0;
    }
    return func->aiDamage;
}

void* wazaDB_GetFightTrainerAiWazaHitFuncPtr(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    WazaFuncData* func = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data));
    if (func == 0) {
        return 0;
    }
    return func->aiHit;
}

void* wazaDB_GetFightTrainerAiWazaValueFuncPtr(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    WazaFuncData* func = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data));
    if (func == 0) {
        return 0;
    }
    return func->aiValue;
}

u8 wazaDB_GetCompatible(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->compatible;
}

u32 wazaDB_GetWazawzxdataId(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->wazawzxdataId;
}

u8 wazaDB_GetRiskFlag(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->riskFlag;
}

u8 wazaDB_GetTypeId(u16 id, u16 index) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    if (index >= 3) {
        return 0;
    }
    return data->typeId[index];
}

u8 wazaDB_GetHidenFlag(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->hidenFlag;
}

u8 wazaDB_GetBouon(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->bouon;
}

u8 wazaDB_GetOujanosirusi(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->oujanosirusi;
}

u8 wazaDB_GetOumugaesi(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->oumugaesi;
}

u8 wazaDB_GetYokodori(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->yokodori;
}

u8 wazaDB_GetMajikku(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->majikku;
}

u8 wazaDB_GetMamoru(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->mamoru;
}

u8 wazaDB_GetDageki(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->dageki;
}

u8 wazaDB_GetAddFightKoukaAvg(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->addFightKoukaAvg;
}

u16 wazaDB_GetSeqId(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->seqId;
}

s16 wazaDB_GetIryoku(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->iryoku;
}

u8 wazaDB_GetAvg(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->avg;
}

u8 wazaDB_GetRangeId(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->rangeId;
}

s32 wazaDB_GetPri(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return (s8)data->pri;
}

u8 waza_GetZokuseiKindData(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    if (wazaCheckDarkWaza(id) == 1) {
        return wazaDB_GetDarkWazaKind(id);
    }
    return zokuseiBiosGetWazaKind(data->zokuseiDataId);
}

u8 wazaDB_GetZokuseiDataId(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->zokuseiDataId;
}

u8 wazaDB_GetPp(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->pp;
}

u32 wazaDB_GetName(u16 id) {
    WazaData* data = wazaDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    return data->name;
}

}
