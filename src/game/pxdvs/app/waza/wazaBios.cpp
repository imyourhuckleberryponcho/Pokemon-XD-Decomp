// Scratch port of direct WazaData bios accessors from Colosseum waza.c.
#include <dolphin/types.h>
extern "C" {
extern u32* waza_data_number;
extern u8* waza_data;
extern u32 waza_func_data_number;
extern u8 waza_func_data[];

void wazaDataBiosSetFightWazaWzxVariationFuncPtr(u8* ptr, u32 val) { u16 idx; u8* entry; if (ptr == NULL) { return; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return; } *(u32*)(entry + 0x14) = val; }
void wazaDataBiosSetFightWazaWzxTypeFuncPtr(u8* ptr, u32 val) { u16 idx; u8* entry; if (ptr == NULL) { return; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return; } *(u32*)(entry + 0x10) = val; }
u32 wazaDataBiosGetFightWazaWzxVariationFuncPtr(u8* ptr) { u16 idx; u8* entry; if (ptr == NULL) { return 0; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return 0; } return *(u32*)(entry + 0x14); }
u32 wazaDataBiosGetFightWazaWzxTypeFuncPtr(u8* ptr) { u16 idx; u8* entry; if (ptr == NULL) { return 0; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return 0; } return *(u32*)(entry + 0x10); }
void wazaDataBiosSetFightTrainerAiWazaDamageFuncPtr(u8* ptr, u32 val) { u16 idx; u8* entry; if (ptr == NULL) { return; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return; } *(u32*)(entry + 0x8) = val; }
void wazaDataBiosSetFightTrainerAiWazaHitFuncPtr(u8* ptr, u32 val) { u16 idx; u8* entry; if (ptr == NULL) { return; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return; } *(u32*)(entry + 0x4) = val; }
void wazaDataBiosSetFightTrainerAiWazaValueFuncPtr(u8* ptr, u32 val) { u16 idx; u8* entry; if (ptr == NULL) { return; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return; } *(u32*)(entry + 0x0) = val; }
void wazaDataBiosSetRiskFlag(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x14]) = val;
}

void wazaDataBiosSetTypeId(u8* ptr, u16 idx, u8 val) {
    if (ptr == NULL) { return; }
    if (idx >= 3) { return; }
    ptr[idx + 0x34] = val;
}

u32 wazaDataBiosGetFightTrainerAiWazaDamageFuncPtr(u8* ptr) { u16 idx; u8* entry; if (ptr == NULL) { return 0; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return 0; } return *(u32*)(entry + 0x8); }
u32 wazaDataBiosGetFightTrainerAiWazaHitFuncPtr(u8* ptr) { u16 idx; u8* entry; if (ptr == NULL) { return 0; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return 0; } return *(u32*)(entry + 0x4); }
u32 wazaDataBiosGetFightTrainerAiWazaValueFuncPtr(u8* ptr) { u16 idx; u8* entry; if (ptr == NULL) { return 0; } if (ptr == NULL) { idx = 0; } else { idx = *(u16*)(ptr + 0x1e); } if ((u32)idx >= waza_func_data_number) { entry = NULL; } else { entry = waza_func_data + (u32)idx * 0x18; } if (entry == NULL) { return 0; } return *(u32*)(entry + 0x0); }
u16 wazaDataBiosGetWazaFuncDataId(u8* ptr) { if (ptr == NULL) { return 0; } return *(u16*)(ptr + 0x1e); }
u8 wazaDataBiosGetRiskFlag(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x14]);
}

u8 wazaDataBiosGetTypeId(u8* ptr, u16 idx) {
    if (ptr == NULL) { return 0; }
    if (idx >= 3) { return 0; }
    return ptr[idx + 0x34];
}

void wazaDataBiosSetHidenFlag(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x12]) = val;
}

u8 wazaDataBiosGetHidenFlag(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x12]);
}

void wazaDataBiosSetDoc(u8* ptr, u32 val) {
    if (ptr == NULL) { return; }
    *(u32*)(&ptr[0x2C]) = val;
}

void wazaDataBiosSetWazawzxdataId(u8* ptr, u32 val) {
    if (ptr == NULL) { return; }
    *(u32*)(&ptr[0x30]) = val;
}

void wazaDataBiosSetPressure(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x11]) = val;
}

void wazaDataBiosSetBouon(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x10]) = val;
}

void wazaDataBiosSetNegoto(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0xF]) = val;
}

void wazaDataBiosSetNekonote(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0xE]) = val;
}

void wazaDataBiosSetMonomane(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0xD]) = val;
}

void wazaDataBiosSetYubiwohuru(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0xC]) = val;
}

void wazaDataBiosSetOujanosirusi(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0xB]) = val;
}

void wazaDataBiosSetOumugaesi(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0xA]) = val;
}

void wazaDataBiosSetYokodori(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x9]) = val;
}

void wazaDataBiosSetMajikku(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x8]) = val;
}

void wazaDataBiosSetMamoru(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x7]) = val;
}

void wazaDataBiosSetDageki(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x6]) = val;
}

void wazaDataBiosSetAddFightKoukaAvg(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x5]) = val;
}

void wazaDataBiosSetFightAttackMsgId(u8* ptr, u32 val) {
    if (ptr == NULL) { return; }
    *(u32*)(&ptr[0x28]) = val;
}

void wazaDataBiosSetFightAttackTunagiMsgId(u8* ptr, u32 val) { if (ptr == NULL) { return; } *(u32*)(&ptr[0x24]) = val; }
void wazaDataBiosSetSeqId(u8* ptr, u16 val) {
    if (ptr == NULL) { return; }
    *(u16*)(&ptr[0x1C]) = val;
}

void wazaDataBiosSetFightKoukaDataId(u8* ptr, u16 val) {
    if (ptr == NULL) { return; }
    *(u16*)(&ptr[0x1A]) = val;
}

void wazaDataBiosSetIryoku(u8* ptr, s16 val) {
    if (ptr == NULL) { return; }
    *(u16*)(&ptr[0x18]) = val;
}

void wazaDataBiosSetAvg(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x4]) = val;
}

void wazaDataBiosSetRangeId(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x3]) = val;
}

void wazaDataBiosSetPri(u8* ptr, s8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x0]) = val;
}

void wazaDataBiosSetZokuseiDataId(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x2]) = val;
}

void wazaDataBiosSetPp(u8* ptr, u8 val) {
    if (ptr == NULL) { return; }
    *(u8*)(&ptr[0x1]) = val;
}

void wazaDataBiosSetName(u8* ptr, u32 val) {
    if (ptr == NULL) { return; }
    *(u32*)(&ptr[0x20]) = val;
}

u32 wazaDataBiosGetDoc(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u32*)(&ptr[0x2C]);
}

u32 wazaDataBiosGetWazawzxdataId(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u32*)(&ptr[0x30]);
}

u8 wazaDataBiosGetPressure(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x11]);
}

u8 wazaDataBiosGetBouon(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x10]);
}

u8 wazaDataBiosGetNegoto(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0xF]);
}

u8 wazaDataBiosGetNekonote(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0xE]);
}

u8 wazaDataBiosGetMonomane(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0xD]);
}

u8 wazaDataBiosGetYubiwohuru(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0xC]);
}

u8 wazaDataBiosGetOujanosirusi(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0xB]);
}

u8 wazaDataBiosGetOumugaesi(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0xA]);
}

u8 wazaDataBiosGetYokodori(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x9]);
}

u8 wazaDataBiosGetMajikku(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x8]);
}

u8 wazaDataBiosGetMamoru(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x7]);
}

u8 wazaDataBiosGetDageki(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x6]);
}

u8 wazaDataBiosGetAddFightKoukaAvg(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x5]);
}

u32 wazaDataBiosGetFightAttackMsgId(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u32*)(&ptr[0x28]);
}

u32 wazaDataBiosGetFightAttackTunagiMsgId(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u32*)(&ptr[0x24]);
}

u16 wazaDataBiosGetSeqId(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u16*)(&ptr[0x1C]);
}

u16 wazaDataBiosGetFightKoukaDataId(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u16*)(&ptr[0x1A]);
}

s16 wazaDataBiosGetIryoku(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(s16*)(&ptr[0x18]);
}

u8 wazaDataBiosGetAvg(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x4]);
}

u8 wazaDataBiosGetRangeId(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x3]);
}

s32 wazaDataBiosGetPri(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return (s8)ptr[0x0];
}

u8 wazaDataBiosGetZokuseiDataId(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x2]);
}

u8 wazaDataBiosGetPp(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u8*)(&ptr[0x1]);
}

u32 wazaDataBiosGetName(u8* ptr) {
    if (ptr == NULL) { return 0; }
    return *(u32*)(&ptr[0x20]);
}



void* wazaDataBiosGetPtr(u16 idx) { if ((u32)idx >= *waza_data_number) { return waza_data; } return waza_data + (u32)idx * 0x38; }
void* wazaFuncDataBiosGetPtr(u16 idx) { if ((u32)idx >= waza_func_data_number) { return NULL; } return waza_func_data + (u32)idx * 0x18; }
}




