// itemBios: all 89 functions match GXXE01 (itemParamConvertOrigFormat written from asm 2026-10-15).
// Source: src/game/people/people_data_r51_801431AC_suffix.c
// Revision: fd207bc8a541348f8f00046592c5dba4a75d8ec0
#include <dolphin/types.h>

extern "C" {
extern u32 item_param_number;
extern u8 item_param[];
extern u32 taste_data_number;
extern u8 taste_data[];
extern u32 item_soubi_data_number;
extern u8 item_soubi_data[];
extern u32 item_ball_data_number;
extern u8 item_ball_data[];
extern u32 item_waza_machine_no_number;
extern u32* item_data_index_number;
extern u32* item_data_prime_number;
extern u16* item_data_index;
extern u8* item_data_prime;
typedef struct {
    u32 field_00;
    u32 wazaId;
} WazaMachineData;
extern WazaMachineData item_waza_machine_no[];
typedef struct ItemParamDataRef {
    u8 meromeroFlag : 1;
    u8 field_00_bit6 : 1;
    u8 criticalFlag : 1;
    u8 attackUp : 4;
    u8 field_00_bit0 : 1;
    u8 defenceUp : 4;
    u8 quickUp : 4;
    u8 hitUp : 4;
    u8 spAttackUp : 4;
    u8 guardFlag : 1;
    u8 levelUpFlag : 1;
    u8 sleepFlag : 1;
    u8 poisonFlag : 1;
    u8 burnFlag : 1;
    u8 freezeFlag : 1;
    u8 paralyzeFlag : 1;
    u8 confuseFlag : 1;
    u8 ppMaxUpFlag : 1;
    u8 reviveFlag : 1;
    u8 ppSelectFlag : 1;
    u8 evolutionFlag : 1;
    u8 ppMaxFullFlag : 1;
    u8 field_04_bits0_2 : 3;
    s8 friend1Up;
    s8 friend2Up;
    s8 friend3Up;
    u8 hpEffortUp;
    u8 attackEffortUp;
    u8 hpUp;
    u8 ppUp;
    u8 defenceEffortUp;
    u8 quickEffortUp;
    u8 spDefenceEffortUp;
    u8 spAttackEffortUp;
} ItemParamDataRef;

// Field descriptor of the original (packed) item parameter format.
typedef struct ItemParamOrigDesc {
    s32 id;
    s32 offset;
    u8 mask;
    s32 type;
} ItemParamOrigDesc;
































// Source: src/game/people/people_item_getters_exact_80143C50.c
// Revision: fd207bc8a541348f8f00046592c5dba4a75d8ec0; MIT license above.
typedef struct ItemBiosDataRef {
    u16 itemDataId;
    u16 num;
} ItemBiosDataRef;
typedef struct ItemBallDataBiosRef {
    u16 fightKoukaDataId;
    u16 padding_02;
    u32 inWzxDataId;
    u32 openWzxDataId;
    u32 outWzxDataId;
    u32 downinWzxDataId;
    u32 throwWzxDataId;
    u32 snatchAttackWzxDataId;
    u32 snatchBalllandWzxDataId;
    u32 snatchMissWzxDataId;
    u32 snatchPokeoutWzxDataId;
    u32 snatchShakeWzxDataId;
    u32 snatchSnatchWzxDataId;
} ItemBallDataBiosRef;
typedef struct ItemDataBiosRef {
    u8 kind;
    u8 important;
    u8 useful;
    u8 field_03;
    u8 itemEffectParam;
    u8 padding_05;
    u16 price;
    u16 coupon;
    u16 itemSoubiDataId;
    u16 fightUseKoukaDataId;
    u16 padding_0E;
    u32 name;
    u32 doc;
    u32 buff;
    u32 fieldUseFunc;
    u32 battleUseFunc;
    s8 useFriend[3];
    u8 padding_27;
} ItemDataBiosRef;





























// Sources: src/game/people/people_item_effort_exact_80143718.c and
// people_data_candidate_801436F0.c, people_data_candidate_80143778.c,
// people_data_candidate_801437B8.c, people_data_candidate_801437F8.c,
// people_data_candidate_80143A44.c.
// Revision: fd207bc8a541348f8f00046592c5dba4a75d8ec0; MIT license above.






















// Sources: src/game/people/people_item_getters_exact_80143C50.c,
// people_item_tail_exact_80144064.c, and people_data.c.
// Revision: fd207bc8a541348f8f00046592c5dba4a75d8ec0; MIT license above.
extern u32 item_waza_machine_no_number;
extern u32 item_ball_data_number;
extern u8 item_ball_data[];
extern u32* item_data_index_number;
extern u16* item_data_index;
extern u32* item_data_prime_number;
extern u8* item_data_prime;










void itemParamConvertOrigFormat(ItemParamDataRef* dst, u8* src) {
    ItemParamOrigDesc desc[32] = {
        {0, 0, 0x80, 0},
        {1, 0, 0x40, 0},
        {2, 0, 0x30, 0},
        {3, 0, 0x0F, 1},
        {4, 1, 0xF0, 1},
        {5, 1, 0x0F, 1},
        {6, 2, 0xF0, 1},
        {7, 2, 0x0F, 1},
        {8, 3, 0x80, 0},
        {9, 3, 0x40, 0},
        {10, 3, 0x20, 0},
        {11, 3, 0x10, 0},
        {12, 3, 0x08, 0},
        {13, 3, 0x04, 0},
        {14, 3, 0x02, 0},
        {15, 3, 0x01, 0},
        {16, 4, 0x20, 0},
        {17, 4, 0x01, 2},
        {18, 4, 0x02, 2},
        {19, 4, 0x40, 0},
        {20, 4, 0x04, 2},
        {21, 4, 0x10, 0},
        {22, 4, 0x08, 2},
        {23, 4, 0x80, 0},
        {24, 5, 0x01, 2},
        {25, 5, 0x02, 2},
        {26, 5, 0x04, 2},
        {27, 5, 0x08, 2},
        {28, 5, 0x10, 0},
        {29, 5, 0x20, 3},
        {30, 5, 0x40, 3},
        {31, 5, 0x80, 3},
    };
    ItemParamOrigDesc* d;
    s32 i;
    u8* extra = src + 6;
    u8 value;
    s8 svalue;
    u8 flag;

    for (d = desc, i = 0; i < 32; i++, d++) {
        u8 bits = src[d->offset];
        if (d->type == 3 || d->type == 2) {
            if (bits & d->mask) {
                value = *extra++;
                if (d->type == 3) {
                    svalue = value;
                }
            } else if (d->type == 3) {
                svalue = 0;
            }
        } else {
            s32 shift = 0;
            bits &= d->mask;
            while (shift < 8 && !((d->mask >> shift) & 1)) {
                shift++;
            }
            value = (u8)(bits >> shift);
            if (d->type == 0) {
                if (value == 0) {
                    flag = 0;
                } else {
                    flag = 1;
                }
            }
        }
        switch (d->id) {
        case 0:
            dst->meromeroFlag = flag;
            break;
        case 1:
            break;
        case 2:
            dst->criticalFlag = flag;
            break;
        case 3:
            dst->attackUp = value;
            break;
        case 4:
            dst->defenceUp = value;
            break;
        case 5:
            dst->quickUp = value;
            break;
        case 6:
            dst->hitUp = value;
            break;
        case 7:
            dst->spAttackUp = value;
            break;
        case 8:
            dst->guardFlag = flag;
            break;
        case 9:
            dst->levelUpFlag = flag;
            break;
        case 10:
            dst->sleepFlag = flag;
            break;
        case 11:
            dst->poisonFlag = flag;
            break;
        case 12:
            dst->burnFlag = flag;
            break;
        case 13:
            dst->freezeFlag = flag;
            break;
        case 14:
            dst->paralyzeFlag = flag;
            break;
        case 15:
            dst->confuseFlag = flag;
            break;
        case 16:
            dst->ppMaxUpFlag = flag;
            break;
        case 17:
            dst->hpEffortUp = value;
            break;
        case 18:
            dst->attackEffortUp = value;
            break;
        case 19:
            dst->reviveFlag = flag;
            break;
        case 20:
            dst->hpUp = value;
            break;
        case 21:
            dst->ppSelectFlag = flag;
            break;
        case 22:
            dst->ppUp = value;
            break;
        case 23:
            dst->evolutionFlag = flag;
            break;
        case 24:
            dst->defenceEffortUp = value;
            break;
        case 25:
            dst->quickEffortUp = value;
            break;
        case 26:
            dst->spDefenceEffortUp = value;
            break;
        case 27:
            dst->spAttackEffortUp = value;
            break;
        case 28:
            dst->ppMaxFullFlag = flag;
            break;
        case 29:
            dst->friend1Up = svalue;
            break;
        case 30:
            dst->friend2Up = svalue;
            break;
        case 31:
            dst->friend3Up = svalue;
            break;
        }
    }
}

s32 itemParamGetRecoverType(u8* itemParam)
{
    s32 selectedType;
    s32 selectedCount;
    s32 returnType;
    u32 bitValue;
    u8 firstGate;
    u8 statusNibble;
    u8 byteFlag;

    if (itemParam == NULL) {
        return 0x16;
    }

    if (itemParam == NULL) {
        firstGate = 0;
    } else {
        bitValue = (itemParam[0] >> 5) & 1;
        firstGate = ((-bitValue | bitValue) >> 31);
    }
    if (firstGate) {
        goto returnZero;
    }

    if (itemParam == NULL) {
        statusNibble = 0;
    } else {
        statusNibble = (itemParam[0] >> 1) & 0xF;
    }
    if (statusNibble) {
        goto returnZero;
    }

    if (itemParam == NULL) {
        statusNibble = 0;
    } else {
        statusNibble = (itemParam[1] >> 4) & 0xF;
    }
    if (statusNibble) {
        goto returnZero;
    }

    if (itemParam == NULL) {
        statusNibble = 0;
    } else {
        statusNibble = itemParam[1] & 0xF;
    }
    if (statusNibble) {
        goto returnZero;
    }

    if (itemParam == NULL) {
        statusNibble = 0;
    } else {
        statusNibble = (itemParam[2] >> 4) & 0xF;
    }
    if (statusNibble) {
        goto returnZero;
    }

    if (itemParam == NULL) {
        statusNibble = 0;
    } else {
        statusNibble = itemParam[2] & 0xF;
    }
    if (statusNibble) {
        goto returnZero;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[3] >> 7) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (!byteFlag) {
        goto afterReturnZero;
    }
returnZero:
    return 0;
afterReturnZero:

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[0] >> 6) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        return 1;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[3] >> 6) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        return 2;
    }

    selectedCount = 0;

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[3] >> 5) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        selectedType = 3;
        selectedCount = 1;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[3] >> 4) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        selectedType = 4;
        selectedCount++;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[3] >> 3) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        selectedType = 5;
        selectedCount++;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[3] >> 2) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        selectedType = 6;
        selectedCount++;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[3] >> 1) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        selectedType = 7;
        selectedCount++;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = itemParam[3] & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        selectedType = 8;
        selectedCount++;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[0] >> 7) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        selectedType = 9;
        selectedCount++;
    }

    if (selectedCount > 0) {
        returnType = selectedType;
        if (selectedCount > 1) {
            returnType = 0xA;
        }
        return returnType;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        byteFlag = itemParam[0xA];
    }
    if (byteFlag) {
        return 0xB;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        byteFlag = itemParam[9];
    }
    if (byteFlag) {
        return 0xC;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        byteFlag = itemParam[8];
    }
    if (byteFlag) {
        return 0xD;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        byteFlag = itemParam[0xF];
    }
    if (byteFlag) {
        return 0xE;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        byteFlag = itemParam[0xE];
    }
    if (byteFlag) {
        return 0xF;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        byteFlag = itemParam[0xD];
    }
    if (byteFlag) {
        return 0x10;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        byteFlag = itemParam[0xC];
    }
    if (byteFlag) {
        return 0x11;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[4] >> 4) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        return 0x12;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[4] >> 7) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        return 0x13;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[4] >> 3) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        return 0x14;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        bitValue = (itemParam[4] >> 5) & 1;
        byteFlag = ((-bitValue | bitValue) >> 31);
    }
    if (byteFlag) {
        goto returnFifteen;
    }

    if (itemParam == NULL) {
        byteFlag = 0;
    } else {
        byteFlag = itemParam[0xB];
    }
    if (!byteFlag) {
        goto returnSixteen;
    }

returnFifteen:
    return 0x15;
returnSixteen:
    return 0x16;
}

// Source: src/game/people/people_item_friend_exact_8014369C.c
// Revision: fd207bc8a541348f8f00046592c5dba4a75d8ec0; MIT license above.
s8 itemParamGetFriend3Up(u8* data) {
    if (data == NULL) return 0;
    return (s8)data[7];
}

s8 itemParamGetFriend2Up(u8* data) {
    if (data == NULL) return 0;
    return (s8)data[6];
}

s8 itemParamGetFriend1Up(u8* data) {
    if (data == NULL) return 0;
    return (s8)data[5];
}

s32 itemParamGetPPMaxFullFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->ppMaxFullFlag;
    return (-bitValue | bitValue) >> 31;
}

u8 itemParamGetSpAttackEffortUp(u8* p) {
    if (p == NULL) return 0;
    return p[0xF];
}

u8 itemParamGetSpDefenceEffortUp(u8* p) {
    if (p == NULL) return 0;
    return p[0xE];
}

u8 itemParamGetQuickEffortUp(u8* p) {
    if (p == NULL) return 0;
    return p[0xD];
}

u8 itemParamGetDefenceEffortUp(u8* p) {
    if (p == NULL) return 0;
    return p[0xC];
}

s32 itemParamGetEvolutionFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->evolutionFlag;
    return (-bitValue | bitValue) >> 31;
}

// Source: src/game/people/people_item_ppup_exact_801437A0.c
// Revision: fd207bc8a541348f8f00046592c5dba4a75d8ec0; MIT license above.
u8 itemParamGetPPUp(u8* p) {
    if (p == NULL) {
        return 0;
    }
    return p[0xB];
}

s32 itemParamGetPPSelectFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->ppSelectFlag;
    return (-bitValue | bitValue) >> 31;
}

// Source: src/game/people/people_item_hpup_exact_801437E0.c
// Revision: fd207bc8a541348f8f00046592c5dba4a75d8ec0; MIT license above.
u8 itemParamGetHPUp(u8* p) {
    if (p == NULL) {
        return 0;
    }
    return p[0xA];
}

s32 itemParamGetReviveFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->reviveFlag;
    return (-bitValue | bitValue) >> 31;
}

u8 itemParamGetAttackEffortUp(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    return item->attackEffortUp;
}

u8 itemParamGetHPEffortUp(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    return item->hpEffortUp;
}

s32 itemParamGetPPMaxUpFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->ppMaxUpFlag;
    return (-bitValue | bitValue) >> 31;
}

s32 itemParamGetConfuseFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->confuseFlag;
    return (-bitValue | bitValue) >> 31;
}

s32 itemParamGetParalyzeFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->paralyzeFlag;
    return (-bitValue | bitValue) >> 31;
}

s32 itemParamGetFreezeFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->freezeFlag;
    return (-bitValue | bitValue) >> 31;
}

s32 itemParamGetBurnFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->burnFlag;
    return (-bitValue | bitValue) >> 31;
}

s32 itemParamGetPoisonFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->poisonFlag;
    return (-bitValue | bitValue) >> 31;
}

s32 itemParamGetSleepFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->sleepFlag;
    return (-bitValue | bitValue) >> 31;
}

s32 itemParamGetLevelUpFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->levelUpFlag;
    return (-bitValue | bitValue) >> 31;
}

s32 itemParamGetGuardFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->guardFlag;
    return (-bitValue | bitValue) >> 31;
}

// Source: src/game/people/people_item_battle_boost_exact_801439B8.c
// Revision: fd207bc8a541348f8f00046592c5dba4a75d8ec0; MIT license above.
u8 itemParamGetSpAttackUp(u8* p) {
    if (p == NULL) return 0;
    return p[0x2] & 0xF;
}

u8 itemParamGetHitUp(u8* p) {
    if (p == NULL) return 0;
    return (p[0x2] >> 4) & 0xF;
}

u8 itemParamGetQuickUp(u8* p) {
    if (p == NULL) return 0;
    return p[0x1] & 0xF;
}

u8 itemParamGetDefenceUp(u8* p) {
    if (p == NULL) return 0;
    return (p[0x1] >> 4) & 0xF;
}

u8 itemParamGetAttackUp(u8* p) {
    if (p == NULL) return 0;
    return (p[0x0] >> 1) & 0xF;
}

s32 itemParamGetCriticalFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->criticalFlag;
    return (-bitValue | bitValue) >> 31;
}

s32 itemParamGetMeromeroFlag(const ItemParamDataRef* item) {
    if (item == NULL) return 0;
    u32 bitValue = item->meromeroFlag;
    return (-bitValue | bitValue) >> 31;
}

// Source: src/game/people/people_item_tables_setters_exact_80143A94.c
// Revision: fd207bc8a541348f8f00046592c5dba4a75d8ec0; MIT license above.
u8* itemParamGetPtr(u8 idx) {
    u8* result = &item_param[idx * 16];
    if (idx < item_param_number) return result;
    return NULL;
}

s8 tasteDataGetAisyou(u8* p, u16 idx) {
    if (p == NULL) return 0;
    if (idx >= 0x19) return 0;
    return (s8)p[idx + 4];
}

u32 tasteDataGetNigateMsgDataId(u8* p) {
    if (p == NULL) return 0;
    return *(u32*)p;
}

u8* tasteDataGetPtr(u16 idx) {
    u8* result = &taste_data[idx * 32];
    if (idx < taste_data_number) return result;
    return NULL;
}

u16 itemSoubiDataBiosGetFightKoukaDataId(u8* p) {
    if (p == NULL) return 0;
    return *(u16*)p;
}

u8* itemSoubiDataBiosGetPtr(u16 idx) {
    u8* result = &item_soubi_data[idx * 2];
    if (idx < item_soubi_data_number) return result;
    return NULL;
}

void itemBiosSetNum(u8* p, u16 val) {
    if (p == NULL) return;
    *(u16*)(p + 2) = val;
}

void itemBiosSetItemDataId(u8* p, u16 val) {
    if (p == NULL) return;
    *(u16*)p = val;
}

void itemBallDataBiosSetFightKoukaDataId(u8* p, u16 val) {
    if (p == NULL) return;
    *(u16*)p = val;
}

void itemDataBiosSetBuff(u8* p, u32 val) {
    if (p == NULL) return;
    *(u32*)(p + 0x18) = val;
}

void itemDataBiosSetUseFriend(u8* p, u16 idx, u8 val) {
    if (p == NULL) return;
    if (idx >= 3) return;
    p[idx + 0x24] = val;
}

void itemDataBiosSetFightUseKoukaDataId(u8* p, u16 val) {
    if (p == NULL) return;
    *(u16*)(p + 0xC) = val;
}

void itemDataBiosSetItemSoubiDataId(u8* p, u16 val) {
    if (p == NULL) return;
    *(u16*)(p + 0xA) = val;
}

void itemDataBiosSetDoc(u8* p, u32 val) {
    if (p == NULL) return;
    *(u32*)(p + 0x14) = val;
}

void itemDataBiosSetUseful(u8* p, u8 val) {
    if (p == NULL) return;
    p[2] = val;
}

void itemDataBiosSetImportant(u8* p, u8 val) {
    if (p == NULL) return;
    p[1] = val;
}

void itemDataBiosSetPrice(u8* p, u16 val) {
    if (p == NULL) return;
    *(u16*)(p + 6) = val;
}

void itemDataBiosSetKind(u8* p, u8 val) {
    if (p == NULL) return;
    p[0] = val;
}

void itemDataBiosSetName(u8* p, u32 val) {
    if (p == NULL) return;
    *(u32*)(p + 0x10) = val;
}

u32 itemBiosGetNum(u8* p) {
    ItemBiosDataRef* item = (ItemBiosDataRef*)p;
    if (item == NULL) return 0;
    return item->num;
}

u32 itemBiosGetItemDataId(u8* p) {
    ItemBiosDataRef* item = (ItemBiosDataRef*)p;
    if (item == NULL) return 0;
    return item->itemDataId;
}

u32 itemBallDataBiosGetSnatchSnatchWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->snatchSnatchWzxDataId;
}

u32 itemBallDataBiosGetSnatchShakeWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->snatchShakeWzxDataId;
}

u32 itemBallDataBiosGetSnatchPokeoutWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->snatchPokeoutWzxDataId;
}

u32 itemBallDataBiosGetSnatchMissWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->snatchMissWzxDataId;
}

u32 itemBallDataBiosGetSnatchBalllandWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->snatchBalllandWzxDataId;
}

u32 itemBallDataBiosGetSnatchAttackWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->snatchAttackWzxDataId;
}

u32 itemBallDataBiosGetThrowWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->throwWzxDataId;
}

u32 itemBallDataBiosGetDowninWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->downinWzxDataId;
}

u32 itemBallDataBiosGetOutWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->outWzxDataId;
}

u32 itemBallDataBiosGetOpenWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->openWzxDataId;
}

u32 itemBallDataBiosGetInWzxDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->inWzxDataId;
}

u32 itemBallDataBiosGetFightKoukaDataId(u8* p) {
    ItemBallDataBiosRef* data = (ItemBallDataBiosRef*)p;
    if (data == NULL) return 0;
    return data->fightKoukaDataId;
}

u8* itemBallDataBiosGetPtr(u16 idx) {
    u16 ballId = idx;
    if (ballId >= item_ball_data_number) return NULL;
    return &item_ball_data[ballId * 0x40];
}

u32 itemDataBiosGetBattleUseFunc(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->battleUseFunc;
}

u32 itemDataBiosGetFieldUseFunc(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->fieldUseFunc;
}

u32 itemDataBiosGetItemEffectParam(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->itemEffectParam;
}

u32 itemDataBiosGetBuff(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->buff;
}

s32 itemDataBiosGetUseFriend(u8* p, u16 idx) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    u16 friendIdx;
    if (item == NULL) return 0;
    friendIdx = idx;
    if (friendIdx >= 3) return 0;
    return (s8)((u8)item->useFriend[friendIdx]);
}

u32 itemDataBiosGetKinomiNo(u16 itemId) {
    u16 itemNo = itemId;
    if (itemNo < 0x85 || itemNo > 0xAF) return 0xFF;
    return (u8)(itemId - 0x85);
}

u32 itemDataBiosGetHidenMachineNo(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    u8 machineNo;
    if (item == NULL) {
        machineNo = 0;
    } else if (item->kind != 4) {
        machineNo = 0xFF;
    } else {
        machineNo = (u8)item->buff;
    }
    if (machineNo == 0xFF) return 0xFF;
    if (machineNo < 0x32 || machineNo >= item_waza_machine_no_number) return 0xFF;
    return (u8)(machineNo - 0x32);
}

u32 itemDataBiosGetWazaIDByWazaMachineNo(u32 machineNo) {
    if ((u8)machineNo >= item_waza_machine_no_number) return 0;
    return (u16)item_waza_machine_no[(u8)machineNo].wazaId;
}

u32 itemDataBiosGetWazaMachineNo(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    if (item->kind != 4) return 0xFF;
    return (u8)item->buff;
}

u32 itemDataBiosGetFightUseKoukaDataId(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->fightUseKoukaDataId;
}

u32 itemDataBiosGetItemSoubiDataId(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->itemSoubiDataId;
}

u32 itemDataBiosGetDoc(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->doc;
}

s32 itemDataBiosGetDeposit(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    u32 value = item->field_03;
    return (s32)((-value | value) >> 31);
}

s32 itemDataBiosGetUseful(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    u32 value = item->useful;
    return (s32)((-value | value) >> 31);
}

s32 itemDataBiosGetImportant(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    u32 value = item->important;
    return (s32)((-value | value) >> 31);
}

u32 itemDataBiosGetCoupon(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->coupon;
}

u32 itemDataBiosGetPrice(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->price;
}

u8 itemDataBiosGetKind(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->kind;
}

static inline u8 _itemIsImportant(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->important != 0;
}

s32 itemDataBiosCheckExportable(u8* p) {
    if (p == NULL) return 0;
    if (_itemIsImportant(p)) return 0;
    return 1;
}

s32 itemDataBiosCheckImportable(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    u32 value = item->name;
    return (-value | value) >> 31;
}

u32 itemDataBiosGetName(u8* p) {
    ItemDataBiosRef* item = (ItemDataBiosRef*)p;
    if (item == NULL) return 0;
    return item->name;
}

u8* itemDataBiosGetPtr(u16 index) {
    u16 slot;
    if (index >= *item_data_index_number) return NULL;
    slot = item_data_index[index];
    if (slot >= *item_data_prime_number) return NULL;
    return &item_data_prime[slot * 0x28];
}

}




