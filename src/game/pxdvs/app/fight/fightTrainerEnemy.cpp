#include <dolphin/types.h>

struct TrainerEnemyPokemon {
    s16 fightEntryId;
    u8 unk2;
    u8 unk3;
    u16 unk4[4];
    u16 unkC[8];
    u8 unk1C;
    u8 unk1D;
    u16 unk1E;
    u8 unk20[6];
};

extern "C" {

s16 fightTrainerEnemyPokemonBiosGetFightEntryeId(TrainerEnemyPokemon* p);
void fightTrainerEnemyPokemonBiosSetFightEntryeId(TrainerEnemyPokemon* p, s16 id);
void fightTrainerEnemyPokemonBiosSetStoreWazaNum(TrainerEnemyPokemon* p, u8 num);
void fightTrainerEnemyPokemonBiosSetExpectWazaNum(TrainerEnemyPokemon* p, u8 num);
void fightTrainerEnemyPokemonBiosSetStoreWazaDataId(TrainerEnemyPokemon* p, u8 index, u16 id);
void fightTrainerEnemyPokemonBiosSetExpectWazaDataId(TrainerEnemyPokemon* p, u8 index, u16 id);
void fightTrainerEnemyPokemonBiosSetTokuseiFlag(TrainerEnemyPokemon* p, u8 flag);
void fightTrainerEnemyPokemonBiosSetStoreTokuseiData(TrainerEnemyPokemon* p, u16 data);
void fightTrainerEnemyPokemonBiosSetNowhp1banhikuiFlag(TrainerEnemyPokemon* p, u8 flag);
void fightTrainerEnemyPokemonBiosSetLv1banhikuiFlag(TrainerEnemyPokemon* p, u8 flag);
void fightTrainerEnemyPokemonBiosSetDefense1banhikuiFlag(TrainerEnemyPokemon* p, u8 flag);
void fightTrainerEnemyPokemonBiosSetBadwazaHaveFlag(TrainerEnemyPokemon* p, u8 flag);
void fightTrainerEnemyPokemonBiosSetParam1bantakaiFlag(TrainerEnemyPokemon* p, u8 flag);

TrainerEnemyPokemon* fightTrainerEnemyPokemonSearchAry(TrainerEnemyPokemon* ary, u16 num, s16 id);
void fightTrainerEnemyPokemonInit(TrainerEnemyPokemon* p);
void fightTrainerEnemyPokemonCreate(TrainerEnemyPokemon* p, s16 id);
bool fightTrainerEnemyPokemonCheckValid(TrainerEnemyPokemon* p);
void fightTrainerEnemyPokemonInitFightStatus(TrainerEnemyPokemon* p);
void fightTrainerEnemyPokemonInitFightOutStatus(TrainerEnemyPokemon* p);

bool fightTrainerEnemyPokemonEraseAry(TrainerEnemyPokemon* ary, u16 num, s16 id) {
    TrainerEnemyPokemon* p;
    if (ary == NULL) {
        return false;
    }
    if (id < 0) {
        return false;
    }
    p = fightTrainerEnemyPokemonSearchAry(ary, num, id);
    if (p == NULL) {
        return false;
    }
    fightTrainerEnemyPokemonInit(p);
    return true;
}

bool fightTrainerEnemyPokemonRegistAry(TrainerEnemyPokemon* ary, u16 num, s16 id) {
    TrainerEnemyPokemon* p;
    if (ary == NULL) {
        return false;
    }
    if (id < 0) {
        return false;
    }
    if (fightTrainerEnemyPokemonSearchAry(ary, num, id) != NULL) {
        return false;
    }
    p = fightTrainerEnemyPokemonSearchAry(ary, num, -1);
    if (p == NULL) {
        return false;
    }
    fightTrainerEnemyPokemonCreate(p, id);
    return true;
}

TrainerEnemyPokemon* fightTrainerEnemyPokemonSearchAry(TrainerEnemyPokemon* ary, u16 num, s16 id) {
    TrainerEnemyPokemon* p;
    u16 i;
    if (ary == NULL) {
        return NULL;
    }
    for (i = 0; i < num; i++) {
        p = &ary[i];
        if (id < 0) {
            if (!fightTrainerEnemyPokemonCheckValid(p)) {
                return p;
            }
        } else if (fightTrainerEnemyPokemonCheckValid(p) && fightTrainerEnemyPokemonBiosGetFightEntryeId(p) == id) {
            return p;
        }
    }
    return NULL;
}

bool fightTrainerEnemyPokemonCheckValid(TrainerEnemyPokemon* p) {
    if (p == NULL) {
        return false;
    }
    return fightTrainerEnemyPokemonBiosGetFightEntryeId(p) >= 0;
}

void fightTrainerEnemyPokemonCreate(TrainerEnemyPokemon* p, s16 id) {
    if (p != NULL && id >= 0) {
        fightTrainerEnemyPokemonInit(p);
        fightTrainerEnemyPokemonBiosSetFightEntryeId(p, id);
    }
}

void fightTrainerEnemyPokemonInitAry(TrainerEnemyPokemon* ary, u16 num) {
    u16 i;
    if (ary != NULL) {
        for (i = 0; i < num; i++) {
            fightTrainerEnemyPokemonInit(&ary[i]);
        }
    }
}

void fightTrainerEnemyPokemonInit(TrainerEnemyPokemon* p) {
    u8 i;
    fightTrainerEnemyPokemonBiosSetFightEntryeId(p, -1);
    fightTrainerEnemyPokemonInitFightStatus(p);
    fightTrainerEnemyPokemonInitFightOutStatus(p);
    fightTrainerEnemyPokemonBiosSetStoreWazaNum(p, 0);
    fightTrainerEnemyPokemonBiosSetExpectWazaNum(p, 0);
    for (i = 0; i < 4; i++) {
        fightTrainerEnemyPokemonBiosSetStoreWazaDataId(p, i, 0);
    }
    for (i = 0; i < 8; i++) {
        fightTrainerEnemyPokemonBiosSetExpectWazaDataId(p, i, 0);
    }
    fightTrainerEnemyPokemonBiosSetTokuseiFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetStoreTokuseiData(p, 0);
}

void fightTrainerEnemyPokemonInitFightOutStatus(TrainerEnemyPokemon* p) {
    fightTrainerEnemyPokemonBiosSetNowhp1banhikuiFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetLv1banhikuiFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetDefense1banhikuiFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetBadwazaHaveFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetParam1bantakaiFlag(p, 0);
}

void fightTrainerEnemyPokemonInitFightStatus(TrainerEnemyPokemon* p) {
    u8 i;
    for (i = 0; i < 4; i++) {
        p->unk4[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        p->unkC[i] = 0;
    }
    p->unk2 = 0;
    p->unk3 = 0;
    p->unk1C = 0;
    p->unk1E = 0;
}

}
