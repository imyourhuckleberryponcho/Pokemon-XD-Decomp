#include <dolphin/types.h>

// Built with -O4,s (see configure.py).

struct FightWaza;
struct Sequence;
struct WazaSequence;
struct Joutai;

typedef u32 (*FightWazaWzxFunc)(u32, u32, u32, u32, u32);
typedef u32 (*FightWazaWzxVariationFunc)(u32, u32, u32, u32);

extern "C" {
u32 wazaDB_GetWazawzxdataId(u16 wazaID);
WazaSequence* Sequence_GetWaza(Sequence* sequence, u16 wzxID, u32 kind);
void WazaSequence_Start(WazaSequence* sequence, s32);
bool WazaSequence_IsActive(WazaSequence* sequence);
void WazaSequence_Free(WazaSequence* sequence);
void GSthreadSwitch(void);
FightWazaWzxFunc wazaDB_GetFightWazaWzxTypeFuncPtr(u32 wazaID);
FightWazaWzxVariationFunc wazaDB_GetFightWazaWzxVariationFuncPtr(u32 wazaID);
u32 fightWazaWzxTypeFuncNull(u32, u32, u32, u32, u32);
u32 fightWazaWzxVariationFuncNull(u32, u32, u32, u32);
u16 joutaiDataBiosGetStatus(u16 id);
void joutaiWriteJoutaiDataId(FightWaza* waza, u16 id, u32 value);
u8 joutaiCheckWriteJoutaiDataId(FightWaza* waza, u16 id);
u8 joutaiIsJoutaiDataId(FightWaza* waza, u16 id);
void joutaiInitJoutaiDataId(FightWaza* waza, u16 id);
void joutaiInitAry(Joutai* joutai, s32 num);
Joutai* fightWaza_GetJoutaiPtr(FightWaza* waza, s32 index);
void fightWaza_SetWazaBanme(FightWaza* waza, s32 banme);
void fightWaza_SetTargetDataId(FightWaza* waza, u16 id);
void fightWaza_SetMotoWazaDataId(FightWaza* waza, u16 id);
void fightWaza_SetUseWazaDataId(FightWaza* waza, u16 id);
void fightWaza_SetAutoMakeFlag(FightWaza* waza, u8 flag);
void fightWaza_SetIryoku(FightWaza* waza, u16 iryoku);
void fightWaza_SetZokusei(FightWaza* waza, u8 zokusei);
void fightWaza_SetDamage(FightWaza* waza, s32 damage);
void fightWaza_SetHitDamage(FightWaza* waza, s32 damage);
void fightWaza_SetKaisuu(FightWaza* waza, s32 kaisuu);
void fightWaza_SetCritical(FightWaza* waza, s32 critical);
void fightWaza_SetDamageValue(FightWaza* waza, s32 value);
u16 fightWaza_GetMotoWazaDataId(FightWaza* waza);
u16 fightWaza_GetUseWazaDataId(FightWaza* waza);
u16 fightWaza_GetTargetDataId(FightWaza* waza);
u32 wazaDB_GetIryoku(u16 id);
u32 wazaDB_GetZokuseiDataId(u16 id);

u8 fightWazaIsJoutaiDataId(FightWaza* waza, u16 id);
void fightWazaWriteJoutaiDataId(FightWaza* waza, u16 id, u32 value);
void fightWazaInit(FightWaza* waza);
void fightWazaSetUseWazaStatus(FightWaza* waza, u16 id);
void fightWazaInitLoop(FightWaza* waza);
void fightWazaInitJoutai(FightWaza* waza);

void fightWazaDoEffect(Sequence* sequence, u16 wazaID, u32 kind, u8 wait) {
    u32 wzxID = wazaDB_GetWazawzxdataId(wazaID);
    WazaSequence* waza = Sequence_GetWaza(sequence, wzxID, kind);
    if (waza != NULL) {
        WazaSequence_Start(waza, 1);
        if (wait == 1) {
            while (WazaSequence_IsActive(waza)) {
                GSthreadSwitch();
            }
            WazaSequence_Free(waza);
        }
    }
}

u32 fightWazaDoEffectFunc(u32 wazaID, u32 a, u32 b, u32 c) {
    FightWazaWzxFunc typeFunc = wazaDB_GetFightWazaWzxTypeFuncPtr(wazaID);
    FightWazaWzxVariationFunc variationFunc;
    if (typeFunc == NULL) {
        typeFunc = fightWazaWzxTypeFuncNull;
    }
    variationFunc = wazaDB_GetFightWazaWzxVariationFuncPtr(wazaID);
    if (variationFunc == NULL) {
        variationFunc = fightWazaWzxVariationFuncNull;
    }
    return typeFunc(wazaID, a, b, c, variationFunc(wazaID, a, b, c));
}

// Mixed status: two or more of the 0x41-0x47 states at once.
u8 fightWazaIsMix(FightWaza* waza) {
    u16 ids[7] = { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47 };
    u16 i;
    u16 count = 0;
    for (i = 0; i < 7; i++) {
        if (fightWazaIsJoutaiDataId(waza, ids[i]) == 1) {
            count++;
        }
    }
    if (count >= 2) {
        return 1;
    }
    return 0;
}

bool fightWazaIsHit(FightWaza* waza) {
    if (fightWazaIsJoutaiDataId(waza, 0x40) == 1) {
        return 0;
    }
    if (fightWazaIsJoutaiDataId(waza, 0x43) == 1) {
        return 0;
    }
    return fightWazaIsJoutaiDataId(waza, 0x45) != 1;
}

void fightWazaWriteJoutaiDataId(FightWaza* waza, u16 id, u32 value) {
    if (joutaiDataBiosGetStatus(id) == 0x2A) {
        joutaiWriteJoutaiDataId(waza, id, value);
    }
}

u8 fightWazaCheckWriteJoutaiDataId(FightWaza* waza, u16 id) {
    if (joutaiDataBiosGetStatus(id) != 0x2A) {
        return 0;
    }
    return joutaiCheckWriteJoutaiDataId(waza, id);
}

u8 fightWazaIsJoutaiSousai(FightWaza* waza) {
    if (fightWazaIsJoutaiDataId(waza, 0x41) == 1 && fightWazaIsJoutaiDataId(waza, 0x42) == 1) {
        return 1;
    }
    return 0;
}

u8 fightWazaIsJoutaiDataId(FightWaza* waza, u16 id) {
    if (joutaiDataBiosGetStatus(id) != 0x2A) {
        return 0;
    }
    return joutaiIsJoutaiDataId(waza, id);
}

void fightWazaInitJoutaiDataId(FightWaza* waza, u16 id) {
    if (joutaiDataBiosGetStatus(id) == 0x2A) {
        joutaiInitJoutaiDataId(waza, id);
    }
}

void fightWazaCreate(FightWaza* waza, s32 banme, u16 motoID, u16 targetID, u8 autoMake) {
    if (waza != NULL) {
        fightWazaInit(waza);
        fightWaza_SetWazaBanme(waza, banme);
        fightWaza_SetTargetDataId(waza, targetID);
        fightWaza_SetMotoWazaDataId(waza, motoID);
        fightWazaSetUseWazaStatus(waza, motoID);
        fightWaza_SetAutoMakeFlag(waza, autoMake);
    }
}

void fightWazaSetUseWazaStatus(FightWaza* waza, u16 id) {
    fightWaza_SetUseWazaDataId(waza, id);
    fightWaza_SetIryoku(waza, wazaDB_GetIryoku(id));
    fightWaza_SetZokusei(waza, wazaDB_GetZokuseiDataId(id));
}

bool fightWazaCheckValid(FightWaza* waza) {
    if (waza == NULL) {
        return 0;
    }
    if (fightWaza_GetMotoWazaDataId(waza) == 0) {
        return 0;
    }
    if (fightWaza_GetMotoWazaDataId(waza) == 0x163) {
        return 0;
    }
    if (fightWaza_GetUseWazaDataId(waza) == 0) {
        return 0;
    }
    if (fightWaza_GetUseWazaDataId(waza) == 0x163) {
        return 0;
    }
    return fightWaza_GetTargetDataId(waza) != 0;
}

void fightWazaInit(FightWaza* waza) {
    if (waza != NULL) {
        fightWaza_SetWazaBanme(waza, -1);
        fightWaza_SetMotoWazaDataId(waza, 0);
        fightWaza_SetUseWazaDataId(waza, 0);
        fightWaza_SetTargetDataId(waza, 0);
        fightWazaInitLoop(waza);
        fightWaza_SetDamage(waza, 0);
        fightWaza_SetHitDamage(waza, 0);
        fightWaza_SetIryoku(waza, 0);
        fightWaza_SetZokusei(waza, 9);
        fightWaza_SetKaisuu(waza, 0);
        fightWaza_SetAutoMakeFlag(waza, 0);
    }
}

void fightWazaInitLoop(FightWaza* waza) {
    fightWazaInitJoutai(waza);
    fightWaza_SetCritical(waza, 1);
    fightWaza_SetDamageValue(waza, 1);
}

#pragma dont_inline on
void fightWazaInitJoutai(FightWaza* waza) {
    joutaiInitAry(fightWaza_GetJoutaiPtr(waza, 0), 9);
    fightWazaWriteJoutaiDataId(waza, 0x3F, 0);
}
#pragma dont_inline reset

}
