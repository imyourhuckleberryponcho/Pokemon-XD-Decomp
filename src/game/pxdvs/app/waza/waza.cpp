#include <dolphin/types.h>

extern "C" {
void* wazaDataBiosGetPtr(u16);
u8 wazaDB_GetTypeId(u16, u32);
u8 wazaDB_GetPp(u16);
u8 wazaDB_GetZokuseiDataId(u16);
u32 fightWaza_GetMotoWazaDataId(void*);
u32 fightWaza_GetUseWazaDataId(void*);
void wazaDataBiosSetTypeId(void*, u32, u8);
u8 wazaDataBiosGetTypeId(void*, u32);
void* fightWazaBiosGetJoutaiPtr(void*, u32);

void wazaDataBiosSetName(void*, u32);
u32 wazaDataBiosGetName(void*);
void wazaDataBiosSetPp(void*, u8);
u8 wazaDataBiosGetPp(void*);
void wazaDataBiosSetZokuseiDataId(void*, u8);
u8 wazaDataBiosGetZokuseiDataId(void*);
void wazaDataBiosSetPri(void*, s8);
s8 wazaDataBiosGetPri(void*);
void wazaDataBiosSetRangeId(void*, u8);
u8 wazaDataBiosGetRangeId(void*);
void wazaDataBiosSetAvg(void*, u8);
u8 wazaDataBiosGetAvg(void*);
void wazaDataBiosSetIryoku(void*, s16);
s16 wazaDataBiosGetIryoku(void*);
void wazaDataBiosSetFightKoukaDataId(void*, u16);
u16 wazaDataBiosGetFightKoukaDataId(void*);
void wazaDataBiosSetSeqId(void*, u16);
u16 wazaDataBiosGetSeqId(void*);
void wazaDataBiosSetFightAttackTunagiMsgId(void*, u16);
u32 wazaDataBiosGetFightAttackTunagiMsgId(void*);
void wazaDataBiosSetFightAttackMsgId(void*, u16);
u32 wazaDataBiosGetFightAttackMsgId(void*);
void wazaDataBiosSetAddFightKoukaAvg(void*, u8);
u8 wazaDataBiosGetAddFightKoukaAvg(void*);
void wazaDataBiosSetDageki(void*, u8);
u8 wazaDataBiosGetDageki(void*);
void wazaDataBiosSetMamoru(void*, u8);
u8 wazaDataBiosGetMamoru(void*);
void wazaDataBiosSetMajikku(void*, u8);
u8 wazaDataBiosGetMajikku(void*);
void wazaDataBiosSetYokodori(void*, u8);
u8 wazaDataBiosGetYokodori(void*);
void wazaDataBiosSetOumugaesi(void*, u8);
u8 wazaDataBiosGetOumugaesi(void*);
void wazaDataBiosSetOujanosirusi(void*, u8);
u8 wazaDataBiosGetOujanosirusi(void*);
void wazaDataBiosSetYubiwohuru(void*, u8);
u8 wazaDataBiosGetYubiwohuru(void*);
void wazaDataBiosSetMonomane(void*, u8);
u8 wazaDataBiosGetMonomane(void*);
void wazaDataBiosSetNekonote(void*, u8);
u8 wazaDataBiosGetNekonote(void*);
void wazaDataBiosSetNegoto(void*, u8);
u8 wazaDataBiosGetNegoto(void*);
void wazaDataBiosSetBouon(void*, u8);
u8 wazaDataBiosGetBouon(void*);
void wazaDataBiosSetPressure(void*, u8);
u8 wazaDataBiosGetPressure(void*);
void wazaDataBiosSetHidenFlag(void*, u8);
u8 wazaDataBiosGetHidenFlag(void*);
void wazaDataBiosSetRiskFlag(void*, u8);
u8 wazaDataBiosGetRiskFlag(void*);
void wazaDataBiosSetFightTrainerAiWazaValueFuncPtr(void*, u32);
u32 wazaDataBiosGetFightTrainerAiWazaValueFuncPtr(void*);
void wazaDataBiosSetFightTrainerAiWazaHitFuncPtr(void*, u32);
u32 wazaDataBiosGetFightTrainerAiWazaHitFuncPtr(void*);
void wazaDataBiosSetFightTrainerAiWazaDamageFuncPtr(void*, u32);
u32 wazaDataBiosGetFightTrainerAiWazaDamageFuncPtr(void*);
void wazaDataBiosSetWazawzxdataId(void*, u32);
u32 wazaDataBiosGetWazawzxdataId(void*);
void wazaDataBiosSetFightWazaWzxTypeFuncPtr(void*, u32);
u32 wazaDataBiosGetFightWazaWzxTypeFuncPtr(void*);
void wazaDataBiosSetFightWazaWzxVariationFuncPtr(void*, u32);
u32 wazaDataBiosGetFightWazaWzxVariationFuncPtr(void*);
void wazaDataBiosSetDoc(void*, u32);
u32 wazaDataBiosGetDoc(void*);
void fightWazaBiosSetWazaBanme(void*, s8);
u8 fightWazaBiosGetWazaBanme(void*);
void fightWazaBiosSetMotoWazaDataId(void*, u16);
u16 fightWazaBiosGetMotoWazaDataId(void*);
void fightWazaBiosSetUseWazaDataId(void*, u16);
u16 fightWazaBiosGetUseWazaDataId(void*);
void fightWazaBiosSetTargetDataId(void*, u16);
u16 fightWazaBiosGetTargetDataId(void*);
void fightWazaBiosSetCritical(void*, u8);
u8 fightWazaBiosGetCritical(void*);
void fightWazaBiosSetDamageValue(void*, u8);
u8 fightWazaBiosGetDamageValue(void*);
void fightWazaBiosSetDamage(void*, u32);
u32 fightWazaBiosGetDamage(void*);
void fightWazaBiosSetHitDamage(void*, u32);
u32 fightWazaBiosGetHitDamage(void*);
void fightWazaBiosSetIryoku(void*, u16);
u16 fightWazaBiosGetIryoku(void*);
void fightWazaBiosSetZokusei(void*, u16);
u16 fightWazaBiosGetZokusei(void*);
void fightWazaBiosSetKaisuu(void*, u8);
u8 fightWazaBiosGetKaisuu(void*);
void fightWazaBiosSetAutoMakeFlag(void*, u8);
u8 fightWazaBiosGetAutoMakeFlag(void*);

u32 wazaGetStatus(void*, u16, u16, u32);
}

extern "C" {

u32 wazaCheckDarkWaza(u16 wazaID) {
    switch (wazaID) {
    case 0x164: case 0x165: case 0x166: case 0x167: case 0x168: case 0x169:
    case 0x16A: case 0x16B: case 0x16C: case 0x16D: case 0x16E: case 0x16F:
    case 0x170: case 0x171: case 0x172: case 0x173: case 0x174: case 0x175:
        return 1;
    }
    return 0;
}

u32 wazaGetWazaTypeIdName(u8 type) {
    u32 result = 0;
    switch (type) {
    case 0:
        result = 0;
        break;
    case 1:
        result = 0xEC50;
        break;
    case 2:
        result = 0xEC51;
        break;
    case 3:
        result = 0xEC52;
        break;
    case 4:
        result = 0xED09;
        break;
    case 5:
        result = 0xEC53;
        break;
    case 6:
        result = 0xEC54;
        break;
    case 7:
        result = 0xEC55;
        break;
    case 8:
        result = 0xEC56;
        break;
    case 9:
        result = 0xEC57;
        break;
    case 10:
        result = 0xEC58;
        break;
    case 13:
        result = 0xEC59;
        break;
    }
    return result;
}

u32 wazaIsWazaTypeId(u16 wazaID, u8 typeID) {
    u16 id = wazaID;
    u8 target;
    u8 i;
    if (id == 0 && id == 0x163 && id == 0x176) {
        return 0;
    }
    target = typeID;
    if (target == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        if (target == wazaDB_GetTypeId(wazaID, i)) {
            return 1;
        }
    }
    return 0;
}

u8 wazaGetMaxPP(u16 wazaID, u8 upCount) {
    u8 pp = wazaDB_GetPp(wazaID);
    return pp + upCount * (pp * 20) / 100;
}

void wazaSetStatus(void* ptr, u16 dataID, u16 status, u32 index, u32 value) {
    if (status == 0 || status >= 0x35) {
        return;
    }
    if (status < 0x25) {
        ptr = wazaDataBiosGetPtr(dataID);
        if (ptr == 0) {
            return;
        }
    } else if (ptr == 0) {
        return;
    }
    switch (status) {
    case 1:
        wazaDataBiosSetName(ptr, (u32)value);
        break;
    case 2:
        wazaDataBiosSetPp(ptr, (u8)value);
        break;
    case 3:
        wazaDataBiosSetZokuseiDataId(ptr, (u8)value);
        break;
    case 4:
        wazaDataBiosSetPri(ptr, (s8)value);
        break;
    case 5:
        wazaDataBiosSetRangeId(ptr, (u8)value);
        break;
    case 6:
        wazaDataBiosSetAvg(ptr, (u8)value);
        break;
    case 7:
        wazaDataBiosSetIryoku(ptr, (s16)value);
        break;
    case 8:
        wazaDataBiosSetFightKoukaDataId(ptr, (u16)value);
        break;
    case 9:
        wazaDataBiosSetSeqId(ptr, (u16)value);
        break;
    case 10:
        wazaDataBiosSetFightAttackTunagiMsgId(ptr, (u16)value);
        break;
    case 11:
        wazaDataBiosSetFightAttackMsgId(ptr, (u16)value);
        break;
    case 12:
        wazaDataBiosSetAddFightKoukaAvg(ptr, (u8)value);
        break;
    case 13:
        wazaDataBiosSetDageki(ptr, (u8)value);
        break;
    case 14:
        wazaDataBiosSetMamoru(ptr, (u8)value);
        break;
    case 15:
        wazaDataBiosSetMajikku(ptr, (u8)value);
        break;
    case 16:
        wazaDataBiosSetYokodori(ptr, (u8)value);
        break;
    case 17:
        wazaDataBiosSetOumugaesi(ptr, (u8)value);
        break;
    case 18:
        wazaDataBiosSetOujanosirusi(ptr, (u8)value);
        break;
    case 19:
        wazaDataBiosSetYubiwohuru(ptr, (u8)value);
        break;
    case 20:
        wazaDataBiosSetMonomane(ptr, (u8)value);
        break;
    case 21:
        wazaDataBiosSetNekonote(ptr, (u8)value);
        break;
    case 22:
        wazaDataBiosSetNegoto(ptr, (u8)value);
        break;
    case 23:
        wazaDataBiosSetBouon(ptr, (u8)value);
        break;
    case 24:
        wazaDataBiosSetPressure(ptr, (u8)value);
        break;
    case 25:
        wazaDataBiosSetHidenFlag(ptr, (u8)value);
        break;
    case 26:
        wazaDataBiosSetTypeId(ptr, index, (u8)value);
        break;
    case 27:
        wazaDataBiosSetRiskFlag(ptr, (u8)value);
        break;
    case 28:
        wazaDataBiosSetFightTrainerAiWazaValueFuncPtr(ptr, (u32)value);
        break;
    case 29:
        wazaDataBiosSetFightTrainerAiWazaHitFuncPtr(ptr, (u32)value);
        break;
    case 30:
        wazaDataBiosSetFightTrainerAiWazaDamageFuncPtr(ptr, (u32)value);
        break;
    case 32:
        wazaDataBiosSetFightWazaWzxTypeFuncPtr(ptr, (u32)value);
        break;
    case 33:
        wazaDataBiosSetFightWazaWzxVariationFuncPtr(ptr, (u32)value);
        break;
    case 31:
        wazaDataBiosSetWazawzxdataId(ptr, (u32)value);
        break;
    case 34:
        wazaDataBiosSetDoc(ptr, (u32)value);
        break;
    case 38:
        fightWazaBiosSetWazaBanme(ptr, (s8)value);
        break;
    case 39:
        fightWazaBiosSetMotoWazaDataId(ptr, (u16)value);
        break;
    case 40:
        fightWazaBiosSetUseWazaDataId(ptr, (u16)value);
        break;
    case 41:
        fightWazaBiosSetTargetDataId(ptr, (u16)value);
        break;
    case 43:
        fightWazaBiosSetCritical(ptr, (u8)value);
        break;
    case 44:
        fightWazaBiosSetDamageValue(ptr, (u8)value);
        break;
    case 45:
        fightWazaBiosSetDamage(ptr, (u32)value);
        break;
    case 46:
        fightWazaBiosSetHitDamage(ptr, (u32)value);
        break;
    case 47:
        fightWazaBiosSetIryoku(ptr, (u16)value);
        break;
    case 48:
        fightWazaBiosSetZokusei(ptr, (u16)value);
        break;
    case 49:
        fightWazaBiosSetKaisuu(ptr, (u8)value);
        break;
    case 50:
        fightWazaBiosSetAutoMakeFlag(ptr, (u8)value);
        break;
    }
}

u32 wazaGetStatus(void* ptr, u16 dataID, u16 status, u32 index) {
    if (status == 0 || status >= 0x35) {
        return 0;
    }
    if (status < 0x25) {
        ptr = wazaDataBiosGetPtr(dataID);
        if (ptr == 0) {
            return 0;
        }
    } else if (ptr == 0) {
        return 0;
    }
    switch (status) {
    case 1:
        return wazaDataBiosGetName(ptr);
    case 2:
        return (u8)wazaDataBiosGetPp(ptr);
    case 3:
        return (u8)wazaDataBiosGetZokuseiDataId(ptr);
    case 4:
        return (s8)wazaDataBiosGetPri(ptr);
    case 5:
        return (u8)wazaDataBiosGetRangeId(ptr);
    case 6:
        return (u8)wazaDataBiosGetAvg(ptr);
    case 7:
        return (s16)wazaDataBiosGetIryoku(ptr);
    case 8:
        return (u16)wazaDataBiosGetFightKoukaDataId(ptr);
    case 9:
        return (u16)wazaDataBiosGetSeqId(ptr);
    case 10:
        return wazaDataBiosGetFightAttackTunagiMsgId(ptr);
    case 11:
        return wazaDataBiosGetFightAttackMsgId(ptr);
    case 12:
        return (u8)wazaDataBiosGetAddFightKoukaAvg(ptr);
    case 13:
        return (u8)wazaDataBiosGetDageki(ptr);
    case 14:
        return (u8)wazaDataBiosGetMamoru(ptr);
    case 15:
        return (u8)wazaDataBiosGetMajikku(ptr);
    case 16:
        return (u8)wazaDataBiosGetYokodori(ptr);
    case 17:
        return (u8)wazaDataBiosGetOumugaesi(ptr);
    case 18:
        return (u8)wazaDataBiosGetOujanosirusi(ptr);
    case 19:
        return (u8)wazaDataBiosGetYubiwohuru(ptr);
    case 20:
        return (u8)wazaDataBiosGetMonomane(ptr);
    case 21:
        return (u8)wazaDataBiosGetNekonote(ptr);
    case 22:
        return (u8)wazaDataBiosGetNegoto(ptr);
    case 23:
        return (u8)wazaDataBiosGetBouon(ptr);
    case 24:
        return (u8)wazaDataBiosGetPressure(ptr);
    case 25:
        return (u8)wazaDataBiosGetHidenFlag(ptr);
    case 26:
        return (u8)wazaDataBiosGetTypeId(ptr, index);
    case 27:
        return (u8)wazaDataBiosGetRiskFlag(ptr);
    case 28:
        return wazaDataBiosGetFightTrainerAiWazaValueFuncPtr(ptr);
    case 29:
        return wazaDataBiosGetFightTrainerAiWazaHitFuncPtr(ptr);
    case 30:
        return wazaDataBiosGetFightTrainerAiWazaDamageFuncPtr(ptr);
    case 32:
        return wazaDataBiosGetFightWazaWzxTypeFuncPtr(ptr);
    case 33:
        return wazaDataBiosGetFightWazaWzxVariationFuncPtr(ptr);
    case 31:
        return wazaDataBiosGetWazawzxdataId(ptr);
    case 34:
        return wazaDataBiosGetDoc(ptr);
    case 38:
        return (s8)fightWazaBiosGetWazaBanme(ptr);
    case 39:
        return (u16)fightWazaBiosGetMotoWazaDataId(ptr);
    case 40:
        return (u16)fightWazaBiosGetUseWazaDataId(ptr);
    case 41:
        return (u16)fightWazaBiosGetTargetDataId(ptr);
    case 42:
        return (u32)fightWazaBiosGetJoutaiPtr(ptr, index);
    case 43:
        return (u8)fightWazaBiosGetCritical(ptr);
    case 44:
        return (u8)fightWazaBiosGetDamageValue(ptr);
    case 45:
        return fightWazaBiosGetDamage(ptr);
    case 46:
        return fightWazaBiosGetHitDamage(ptr);
    case 47:
        return (u16)fightWazaBiosGetIryoku(ptr);
    case 48:
        return (u16)fightWazaBiosGetZokusei(ptr);
    case 49:
        return (u8)fightWazaBiosGetKaisuu(ptr);
    case 50:
        return (u8)fightWazaBiosGetAutoMakeFlag(ptr);
    case 51:
        return (u8)wazaDB_GetZokuseiDataId(fightWaza_GetMotoWazaDataId(ptr));
    case 52:
        return (u8)wazaDB_GetZokuseiDataId(fightWaza_GetUseWazaDataId(ptr));
    }
    return 0;
}

}
