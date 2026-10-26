#include <dolphin/types.h>

struct FIGHT_FLOOR;
struct FIGHT_SIDE;
struct FIGHT_TRAINER;
struct FightTypeData;

struct FightTargetData {
    u8 kid;
    u8 relativeFlag;
    u16 pad;
    void* buff;
};

extern "C" {
extern FightTargetData fight_target_data[];
extern u32 fight_target_data_number;

FIGHT_FLOOR* fightFloorGetNowPtr(void);
u32 fightFloorGetStatus(FIGHT_FLOOR*, u16, u16, u16);
FIGHT_SIDE* fightFloor_GetFightSidePtr(FIGHT_FLOOR*, u16);
void* fightFloor_GetAttackPokemonPtr(FIGHT_FLOOR*);
void* fightFloor_GetDefensePokemonPtr(FIGHT_FLOOR*);
void* fightFloor_GetEscapePokemonPtr(FIGHT_FLOOR*);
void* fightFloor_GetIrekaePokemonPtr(FIGHT_FLOOR*);
void* fightFloor_GetKizetuPokemonPtr(FIGHT_FLOOR*);
void* fightFloor_GetTuikakoukaPokemonPtr(FIGHT_FLOOR*);
void* fightFloor_GetTokuseiPokemonPtr(FIGHT_FLOOR*);
void* fightFloor_GetItemPokemonPtr(FIGHT_FLOOR*);
void* fightFloor_GetAppointPokemonPtr(FIGHT_FLOOR*);
void* fightFloor_GetAppointTrainerPtr(FIGHT_FLOOR*);
void* fightFloor_GetAppointWazaPtr(FIGHT_FLOOR*);
void* fightFloor_GetAppointSidePtr(FIGHT_FLOOR*);
void* fightFloor_GetAppointItemPtr(FIGHT_FLOOR*);
s32 fightFloor_GetFightType(FIGHT_FLOOR*);

FIGHT_TRAINER* fightSide_GetFightTrainerPtr(FIGHT_SIDE*, u16);
void* fightTrainer_GetFightoutPokemonPtr(FIGHT_TRAINER*, u16);
void* fightTrainer_GetFightPokemonPtr(FIGHT_TRAINER*, u16);

FightTypeData* fightTypeDataBiosGetPtr(u16);
u8 fightTypeDataBiosGetTrainerNum(FightTypeData*);
u8 fightTypeDataBiosGetFightoutPokemonNum(FightTypeData*);
u8 fightTypeDataBiosGetEntryPokemonNum(FightTypeData*);

void* fightTargetGetPtr(u16 slotType, void* ptr, u16 type);
u16 fightTargetGetTragetPtrToRelativeFightTargetId(void* ptr, void* target, u16 type);
FightTargetData* fightTargetDataBiosGetPtr(u16 index);
u8 fightTargetDataBiosGetRelativeFlag(FightTargetData*);
}

static FIGHT_SIDE* _fightTargetGetTargetPtrToFightSidePtr(void* target, u16 type);

extern "C" {

bool fightTargetIsHostSide(void* slotType, u16 type) {
    void* host = fightTargetGetPtr(4, 0, type);
    if (host == 0) {
        return 0;
    }
    void* other = fightTargetGetPtr(2, slotType, type);
    if (other == 0) {
        return 0;
    }
    return other == host;
}

void* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u16 slotType, u16 type) {
    void* host = fightTargetGetPtr(4, 0, type);
    if (host == 0) {
        return 0;
    }
    void* result = fightTargetGetPtr(slotType, host, type);
    if (result == 0) {
        result = 0;
    }
    return result;
}

u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(void* target, u16 type) {
    void* host = fightTargetGetPtr(4, 0, type);
    if (host == 0) {
        return 0;
    }
    return fightTargetGetTragetPtrToRelativeFightTargetId(host, target, type);
}

u16 fightTargetGetTragetPtrToRelativeFightTargetId(void* ptr, void* target, u16 type) {
    u16 i;
    for (i = 0; i < fight_target_data_number; i++) {
        if (i != 0) {
            FightTargetData* data = fightTargetDataBiosGetPtr(i);
            if (data != 0) {
                if (fightTargetDataBiosGetRelativeFlag(data)) {
                    if (fightTargetGetPtr(i, ptr, type) == target) {
                        return i;
                    }
                }
            }
        }
    }
    return 0;
}

u8 fightTargetDataBiosGetRelativeFlag(FightTargetData* data) {
    if (data == 0) {
        return 0;
    }
    return data->relativeFlag;
}

void* fightTargetDataBiosGetBuff(FightTargetData* data) {
    if (data == 0) {
        return 0;
    }
    return data->buff;
}

u8 fightTargetDataBiosGetStatusKid(FightTargetData* data) {
    if (data == 0) {
        return 0;
    }
    return data->kid;
}

FightTargetData* fightTargetDataBiosGetPtr(u16 index) {
    FightTargetData* data = &fight_target_data[index];
    if (index < fight_target_data_number) {
        return data;
    }
    return 0;
}

void* fightTargetGetPtrAsNowFightType(u16 slotType, void* ptr) {
    return fightTargetGetPtr(slotType, ptr, (u8)fightFloor_GetFightType(0));
}

void* fightTargetGetPtr(u16 slotType, void* ptr, u16 type) {
    void* sides[2];
    void* trainers[4];
    void* pokemon[8];
    u16 c;
    u16 i;
    u16 n;
    u16 k;
    u16 m;
    FightTypeData* typeData;
    u8 trainerNum;
    u16 j;
    u8 pokemonNum;
    u8 flag;
    FIGHT_FLOOR* floor;
    void* savedPtr;

    if (slotType == 0) {
        return 0;
    }
    floor = fightFloorGetNowPtr();
    if (slotType == 1) {
        return floor;
    }
    switch (slotType) {
    case 0x11:
        return fightFloor_GetAttackPokemonPtr(floor);
    case 0x12:
        return fightFloor_GetDefensePokemonPtr(floor);
    case 0x13:
        return fightFloor_GetEscapePokemonPtr(floor);
    case 0x14:
        return fightFloor_GetIrekaePokemonPtr(floor);
    case 0x15:
        return fightFloor_GetKizetuPokemonPtr(floor);
    case 0x16:
        return fightFloor_GetTuikakoukaPokemonPtr(floor);
    case 0x17:
        return fightFloor_GetTokuseiPokemonPtr(floor);
    case 0x18:
        return fightFloor_GetItemPokemonPtr(floor);
    case 0x19:
        return fightFloor_GetAppointPokemonPtr(floor);
    case 0x1a:
        return fightFloor_GetAppointTrainerPtr(floor);
    case 0x1b:
        return fightFloor_GetAppointWazaPtr(floor);
    case 0x1c:
        return fightFloor_GetAppointSidePtr(floor);
    case 0x1d:
        return fightFloor_GetAppointItemPtr(floor);
    }

    typeData = fightTypeDataBiosGetPtr(type);
    if (typeData == 0) {
        return 0;
    }
    if (ptr != 0) {
        savedPtr = ptr;
        ptr = _fightTargetGetTargetPtrToFightSidePtr(ptr, type);
        if (ptr == 0) {
            return 0;
        }
    }
    n = 0;
    m = 0;
    trainerNum = fightTypeDataBiosGetTrainerNum(typeData);
    pokemonNum = fightTypeDataBiosGetFightoutPokemonNum(typeData);
    for (i = 0; i < 2; i++) {
        sides[i] = fightFloor_GetFightSidePtr(floor, i);
        if (slotType == 4 && i == 0) {
            return sides[i];
        }
        if (slotType == 5 && i == 1) {
            return sides[i];
        }
        if (sides[i] == ptr) {
            flag = 1;
            if (slotType == 2) {
                return sides[i];
            }
        } else {
            flag = 0;
            if (slotType == 3) {
                return sides[i];
            }
        }
        j = 0;
        for (c = 0; c < trainerNum; c++) {
            trainers[n] = fightSide_GetFightTrainerPtr((FIGHT_SIDE*)sides[i], c);
            if (slotType == 0xb && i == 0 && c == 0) {
                return trainers[n];
            }
            if (flag == 1) {
                if (slotType == 6 && c == 0) {
                    return trainers[n];
                }
                if (slotType == 7 && c == 1) {
                    return trainers[n];
                }
                if (slotType == 8) {
                    if (savedPtr != trainers[n]) {
                        return trainers[n];
                    }
                }
            } else {
                if (slotType == 9 && c == 0) {
                    return trainers[n];
                }
                if (slotType == 0xa && c == 1) {
                    return trainers[n];
                }
            }
            for (k = 0; k < pokemonNum; k++) {
                pokemon[m] = fightTrainer_GetFightoutPokemonPtr((FIGHT_TRAINER*)trainers[n], k);
                if (flag == 1) {
                    if (slotType == 0xc && j == 0) {
                        return pokemon[m];
                    }
                    if (slotType == 0xd && j == 1) {
                        return pokemon[m];
                    }
                    if (slotType == 0xe) {
                        if (savedPtr != pokemon[m]) {
                            return pokemon[m];
                        }
                    }
                } else {
                    if (slotType == 0xf && j == 0) {
                        return pokemon[m];
                    }
                    if (slotType == 0x10 && j == 1) {
                        return pokemon[m];
                    }
                }
                m++;
                j++;
            }
            n++;
        }
    }
    return 0;
}
}

static FIGHT_SIDE* _fightTargetGetTargetPtrToFightSidePtr(void* target, u16 type) {
    FIGHT_FLOOR* floor;
    FightTypeData* typeData;
    u8 trainerNum;
    u8 pokemonNum;
    u8 entryNum;
    u16 i;
    u16 j;
    u16 k;
    FIGHT_SIDE* side;
    FIGHT_TRAINER* trainer;

    floor = (FIGHT_FLOOR*)fightFloorGetStatus(0, 0, 0, 0);
    typeData = fightTypeDataBiosGetPtr(type);
    if (typeData == 0) {
        return 0;
    }
    trainerNum = fightTypeDataBiosGetTrainerNum(typeData);
    pokemonNum = fightTypeDataBiosGetFightoutPokemonNum(typeData);
    entryNum = fightTypeDataBiosGetEntryPokemonNum(typeData);
    for (i = 0; i < 2; i++) {
        side = fightFloor_GetFightSidePtr(floor, i);
        if ((void*)side == target) {
            return side;
        }
        for (j = 0; j < trainerNum; j++) {
            trainer = fightSide_GetFightTrainerPtr(side, j);
            if ((void*)trainer == target) {
                return side;
            }
            for (k = 0; k < entryNum; k++) {
                if (fightTrainer_GetFightPokemonPtr(trainer, k) == target) {
                    return side;
                }
            }
            for (k = 0; k < pokemonNum; k++) {
                if (fightTrainer_GetFightoutPokemonPtr(trainer, k) == target) {
                    return side;
                }
            }
        }
    }
    return 0;
}
