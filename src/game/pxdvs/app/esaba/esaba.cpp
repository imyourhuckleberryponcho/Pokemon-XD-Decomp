// Draft: esaba (feeding spots on the field).
#include <dolphin/types.h>

enum FootStepCounter { FOOT_STEP_COUNTER_0 };

class Hero;
struct Pokemon {
    u8 raw[0xC4];
};

struct EsaEntry {
    u16 pad;
    u16 id;
    u32 prob;
    u32 rate;
};

struct EsaHead {
    u32 count;
};

struct EsaTable {
    EsaHead* head;
    EsaEntry* entries;
};

struct EsaData {
    u32 flagNum;
    u32 flag4;
    u32 flag8;
    u32 flagID;
    u32 flagRnd;
    u32 flag14;
    EsaTable** table;
};

struct EsaAppData {
    u16 limitA;
    u16 limitB;
    u16 stepMax;
    u16 randMod;
    u16 unk8;
    u16 pad;
    u32 unkC;
    u32 flagKind;
    u32 flagCheck;
};

struct FlagEtcEntry {
    u8 unk0[8];
    u32 limit;
    u8 unkC[0x20 - 0xC];
};

extern "C" {
extern u32* esabadata_number;
extern EsaData* esabadata;
extern EsaEntry* esabapokemondata_EX;
extern EsaAppData* esabaappdata;
extern FlagEtcEntry* flag_etc;

u32 GSflagGet(u32 id);
void GSflagSet(u32 id, u32 value);
bool GSflagTest(u32 id);
u32 heroGetStatus(Hero* hero, u32 selector, u16 index);
u32 gamedataGetStatus(u32 ptr, u32 kind);
void pokemonCreate(Pokemon* pokemon, u16 id, u8 level, u32 trainer);
void pokemonBiosSetCatchTrainerRnd(Pokemon* pokemon, u32 data);
u32 pokemonCreateRndFit(Pokemon* pokemon, s8 sex, s8 seikaku, s8 rare, u32 trainerRnd);
u32 pokemonCreateRnd(void);
void heroMoveInitEvent(void);
void heroMoveSetColision(bool);
void GSthreadSwitch(void);
void menuScriptInfoEsa(void);
void heroMoveTermEvent(void);
Hero* getHeroPtr__4HeroFv(void);
u32 itemQuantity__4HeroFUs(Hero* hero, u16 id);
bool menuPanelInputNumber(s32 a, s32* value, s32 b, s32 max, s32 c);
void msgctrlSetValue(s32 id, u32 value);
s32 winMsgOpen(s8 type, void* msg, bool a, bool b);
void winMsgClose(bool flag);
s32 heroItemDecItemDataId(Hero* hero, u32 itemID, u32 amount, u32 index);
s32 heroItemAddItemDataId(Hero* hero, u32 itemID, u32 amount, u32 index);
u16 pcboxAddItem(s32 box, u32 itemID, u32 amount);
s32 heroMoveAddStepCallback(void (*callback)(long, FootStepCounter, long), s32);
void underTakerCallBackFunc(long, FootStepCounter, long);
u32 underTakerGetMiraboPlace(void);
u32 HSD_Rand(void);
}

static void _esabaCallBackFunc(long, FootStepCounter, long);
static void _esabaCallBackAppFunc(u16, FootStepCounter, long);
static void _esabaCallBackEsaFunc(u16, FootStepCounter, long);
static void _esabaAppearPokemon(u16);
static void _esabaAppearPokemonSub2(u16);
static void _esabaAppearPokemonSub(u16);

static s32 _esabaHandle;

static inline EsaTable* getTable(u16 place) {
    if (place >= *esabadata_number) {
        return 0;
    }
    return *esabadata[place].table;
}

static inline u16 getMax(u16 place) {
    EsaTable* t = getTable(place);
    if (t != 0) {
        return t->head->count;
    }
    return 0;
}

static inline u16 getEntryID(u16 place, s32 index) {
    EsaTable* t = getTable(place);
    if (t != 0) {
        return t->entries[index].id;
    }
    return 0;
}

static inline s32 findIndex(u16 place, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        if (getEntryID(place, i) == GSflagGet(esabadata[place].flagID)) {
            return i;
        }
    }
    return 0;
}

static inline u32 getRateID(u16 place, u16 id) {
    s32 index;
    EsaTable* t;
    if (id == esabapokemondata_EX[0].id) {
        return esabapokemondata_EX[0].rate;
    }
    if (id == esabapokemondata_EX[1].id) {
        return esabapokemondata_EX[1].rate;
    }
    index = findIndex(place, getMax(place));
    t = getTable(place);
    if (t != 0) {
        return t->entries[index].rate;
    }
    return 0;
}

static inline u32 getRate(u16 place) {
    return getRateID(place, GSflagGet(esabadata[place].flagID));
}

static inline void setNum(s32 place, s32 n) {
    GSflagSet(esabadata[place].flagNum, n);
    if (n == 0) {
        GSflagSet(esabadata[place].flag4, 0);
        GSflagSet(esabadata[place].flag8, 0);
    }
}

static inline void setPokemon(u16 place, s32 id) {
    Pokemon pokemon;
    u32 hero;
    u32 rnd;

    GSflagSet(esabadata[place].flagID, id);
    GSflagSet(esabadata[place].flag8, 0);
    if (id < 0x19F && id >= 0x19D) {
        hero = heroGetStatus(0, 2, 0);
        pokemonCreate(&pokemon, id, 10, gamedataGetStatus(0, 1));
        pokemonBiosSetCatchTrainerRnd(&pokemon, hero);
        rnd = pokemonCreateRndFit(&pokemon, -1, -1, 0, hero);
        GSflagSet(esabadata[place].flagRnd, rnd);
    } else {
        GSflagSet(esabadata[place].flagRnd, pokemonCreateRnd());
    }
    heroMoveInitEvent();
    heroMoveSetColision(1);
    GSthreadSwitch();
    menuScriptInfoEsa();
    heroMoveTermEvent();
}

extern "C" {

void esabaSetPokemon(u16 place, u16 id) {
    Pokemon pokemon;
    u32 hero;
    u32 rnd;

    if (id == 0) {
        GSflagSet(esabadata[place].flagID, 0);
        GSflagSet(esabadata[place].flag4, 0);
    } else {
        GSflagSet(esabadata[place].flagID, id);
        GSflagSet(esabadata[place].flag8, 0);
        if (id < 0x19F && id >= 0x19D) {
            hero = heroGetStatus(0, 2, 0);
            pokemonCreate(&pokemon, id, 10, gamedataGetStatus(0, 1));
            pokemonBiosSetCatchTrainerRnd(&pokemon, hero);
            rnd = pokemonCreateRndFit(&pokemon, -1, -1, 0, hero);
            GSflagSet(esabadata[place].flagRnd, rnd);
        } else {
            GSflagSet(esabadata[place].flagRnd, pokemonCreateRnd());
        }
        heroMoveInitEvent();
        heroMoveSetColision(1);
        GSthreadSwitch();
        menuScriptInfoEsa();
        heroMoveTermEvent();
    }
}

u16 esabaGetPokemonMax(u16 place) {
    return getMax(place);
}

u32 esabaGetDigestRate(u32 place) {
    u16 p = place;
    return getRate(p);
}

u32 esabaGetEsaItemNum(void) {
    return itemQuantity__4HeroFUs(getHeroPtr__4HeroFv(), 0x1FF);
}

s32 esabaGet(s32 place) {
    s32 left;
    s32 num = GSflagGet(esabadata[place].flagNum);

    if (menuPanelInputNumber(0, &num, 0, num, 1)) {
        left = -num;
        left = GSflagGet(esabadata[place].flagNum) + left;
        GSflagSet(esabadata[place].flagNum, left);
        if (left == 0) {
            GSflagSet(esabadata[place].flag4, 0);
            GSflagSet(esabadata[place].flag8, 0);
        }
        return num;
    }
    return 0;
}

s32 esabaPut(s32 place) {
    s32 total;
    s32 num = GSflagGet(esabadata[place].flagNum);

    if (menuPanelInputNumber(0, &num, 0, 10 - num, 1)) {
        total = (s16)num;
        total = GSflagGet(esabadata[place].flagNum) + total;
        GSflagSet(esabadata[place].flagNum, total);
        if (total == 0) {
            GSflagSet(esabadata[place].flag4, 0);
            GSflagSet(esabadata[place].flag8, 0);
        }
        return num;
    }
    return 0;
}

s32 esabaSet(s32 place) {
    s32 num = GSflagGet(esabadata[place].flagNum);
    s32 orig = num;
    s32 bag = itemQuantity__4HeroFUs(getHeroPtr__4HeroFv(), 0x1FF);
    s32 diff;
    s32 fromBag;
    s32 fromBox;
    s32 n;
    s32 max;
    s32 msg;

    GSthreadSwitch();
    msg = 0xC92E;
    msg += -(num != 0);
    msgctrlSetValue(0x2F, num);
    winMsgOpen(2, (void*)msg, 0, 1);
    max = num + bag;
    if (max > 10) {
        max = 10;
    }
    if (menuPanelInputNumber(0, &num, 0, max, 1)) {
        n = (s16)num;
        GSflagSet(esabadata[place].flagNum, n);
        if (n == 0) {
            GSflagSet(esabadata[place].flag4, 0);
            GSflagSet(esabadata[place].flag8, 0);
        }
        fromBox = 0;
        diff = num - orig;
        fromBag = 0;
        if (diff != 0) {
            if (diff > 0) {
                heroItemDecItemDataId(0, 0x1FF, (u16)diff, -1);
            } else {
                s32 need = -diff;
                s32 rest = heroItemAddItemDataId(0, 0x1FF, (u16)need, -1);
                if (rest == 0) {
                    fromBag = need;
                } else if (rest > 0) {
                    s32 left = rest;
                    fromBag = -(diff + rest);
                    n = (u16)pcboxAddItem(0, 0x1FF, left);
                    if (n != 0) {
                        fromBox = left - n;
                    } else {
                        fromBox = left;
                    }
                }
            }
        }
    } else {
        diff = 0;
        winMsgClose(1);
    }
    if (diff != 0) {
        if (diff >= 0) {
            winMsgClose(1);
            msgctrlSetValue(0x2F, diff);
            winMsgOpen(2, (void*)0xC930, 1, 1);
            winMsgClose(1);
        } else {
            winMsgClose(1);
            if (fromBag == 0 && fromBox == 0) {
                winMsgOpen(2, (void*)0xC932, 1, 1);
                winMsgClose(1);
                n = (s16)orig;
                diff = 0;
                GSflagSet(esabadata[place].flagNum, n);
                if (n == 0) {
                    GSflagSet(esabadata[place].flag4, 0);
                    GSflagSet(esabadata[place].flag8, 0);
                }
            } else {
                if (fromBag > 0) {
                    msgctrlSetValue(0x2F, fromBag);
                    winMsgOpen(2, (void*)0xC92F, 1, 1);
                    winMsgClose(1);
                }
                if (fromBox > 0) {
                    msgctrlSetValue(0x2F, fromBox);
                    winMsgOpen(2, (void*)0xC933, 1, 1);
                    winMsgClose(1);
                }
                s32 t = orig - fromBag - fromBox;
                if (t != 0) {
                    s32 m = (s16)t;
                    diff = -(orig - t);
                    GSflagSet(esabadata[place].flagNum, m);
                    if (m == 0) {
                        GSflagSet(esabadata[place].flag4, 0);
                        GSflagSet(esabadata[place].flag8, 0);
                    }
                }
            }
        }
    }
    winMsgClose(1);
    return diff;
}

void esabaHeroCallBackInit(void) {
    _esabaHandle = heroMoveAddStepCallback(_esabaCallBackFunc, 0);
}

bool esabaGetPokemonIsRare(s32 place) {
    u32 hero;
    u32 rnd;

    if (GSflagGet(esabadata[place].flagID) != 0) {
        hero = heroGetStatus(0, 2, 0);
        rnd = GSflagGet(esabadata[place].flagRnd);
        return (((hero >> 16) ^ (hero & 0xFFFF) ^ (rnd >> 16) ^ (rnd & 0xFFFF)) < 8);
    }
    return 0;
}

void esabaSetPokemonRnd(s32 place, u32 rnd) {
    GSflagSet(esabadata[place].flagRnd, rnd);
}

u32 esabaGetPokemonRnd(s32 place) {
    return GSflagGet(esabadata[place].flagRnd);
}

u16 esabaGetPokemonID(s32 place) {
    return GSflagGet(esabadata[place].flagID);
}

void esabaSetEsaNum(s32 place, s32 n) {
    setNum(place, n);
}

u32 esabaGetEsaNum(s32 place) {
    return GSflagGet(esabadata[place].flagNum);
}

}

static void _esabaCallBackFunc(long arg, FootStepCounter counter, long amount) {
    u16 i;

    underTakerCallBackFunc(arg, counter, amount);
    for (i = 0; i < (u16)*esabadata_number; i++) {
        if (GSflagGet(esabadata[i].flagNum) != 0) {
            if (GSflagGet(esabadata[i].flagID) != 0) {
                _esabaCallBackEsaFunc(i, counter, amount);
            } else {
                _esabaCallBackAppFunc(i, counter, amount);
            }
        }
    }
}

static void _esabaCallBackAppFunc(u16 place, FootStepCounter, long amount) {
    u32 mirabo = underTakerGetMiraboPlace();
    u32 table[3] = {0x5A, 0x5B, 0x5C};
    u32 total;
    u32 mod;
    u32 limit;
    u32 stepB;

    if (mirabo == table[place]) {
        return;
    }
    if (GSflagTest(esabadata[place].flag14)) {
        return;
    }
    total = GSflagGet(esabadata[place].flag4);
    total += amount;
    if (total >= esabaappdata->limitA) {
        if (total >= esabaappdata->limitB) {
            _esabaAppearPokemon(place);
        } else {
            limit = esabaappdata->stepMax;
            stepB = amount + GSflagGet(esabadata[place].flag8);
            if (stepB >= limit) {
                mod = esabaappdata->randMod;
                if ((u16)HSD_Rand() % (s32)mod == 0) {
                    _esabaAppearPokemon(place);
                } else {
                    GSflagSet(esabadata[place].flag8, stepB - limit);
                }
            } else {
                GSflagSet(esabadata[place].flag8, stepB);
            }
        }
    }
    GSflagSet(esabadata[place].flag4, total);
}

static void _esabaCallBackEsaFunc(u16 place, FootStepCounter, long amount) {
    u32 steps;
    u32 rate;
    u32 left;
    u16 id = GSflagGet(esabadata[place].flagID);

    if (!GSflagTest(esabadata[place].flag14)) {
        rate = getRateID(place, id);
        steps = GSflagGet(esabadata[place].flag8);
        steps += amount;
        if (steps >= rate) {
            steps -= rate;
            left = GSflagGet(esabadata[place].flagNum) - 1;
            if (left == 0) {
                GSflagSet(esabadata[place].flagID, 0);
                GSflagSet(esabadata[place].flag4, 0);
            }
            GSflagSet(esabadata[place].flagNum, left);
        }
        GSflagSet(esabadata[place].flag8, (u16)steps);
    }
}

static void _esabaAppearPokemon(u16 place) {
    u32 kind = esabaappdata->flagKind;
    u16 want;

    if (GSflagGet(0x3C4) >= flag_etc[kind].limit) {
        want = esabaappdata->unk8;
        u32 flag = GSflagGet(esabaappdata->flagCheck);
        if (flag == want) {
            _esabaAppearPokemonSub(place);
            return;
        }
    }
    _esabaAppearPokemonSub2(place);
}

static void _esabaAppearPokemonSub2(u16 place) {
    u16 count = getMax(place);
    u16 i;
    u8 found = 0;
    u16 roll;
    u16 total;
    u16 id;
    s32 k;

    for (i = 0; i < (u16)*esabadata_number; i++) {
        u32 cmpv = (u16)GSflagGet(esabadata[i].flagID);
        if (cmpv == esabapokemondata_EX[1].id) {
            found = 1;
            break;
        }
    }
    if (!found) {
        roll = (u16)HSD_Rand() % 100;
        if (roll < (u16)esabapokemondata_EX[1].prob) {
            setPokemon(place, esabapokemondata_EX[1].id);
            return;
        }
    } else {
        roll = (u16)HSD_Rand() % 100;
        for (k = 0, total = 0; k < (u8)count; k++) {
            EsaTable* t = getTable(place);
            total += t ? t->entries[k].prob : 0;
            if (total >= roll) {
                volatile EsaTable* t2 = getTable(place);
                id = t2 ? t2->entries[k].id : 0;
                setPokemon(place, id);
                return;
            }
        }
    }
}

static void _esabaAppearPokemonSub(u16 place) {
    enum TsE { TsE0 };
    u16 count = getMax((u16)place);
    u16 roll = (u16)HSD_Rand() % 100;
    u16 probA = esabapokemondata_EX[0].prob;
    u16 total;
    enum TsE foundA = (enum TsE)(0);
    u8 foundB;
    u16 i;
    u16 probB = esabapokemondata_EX[1].prob;
    u16 id;
    s32 k;

    for (i = 0; i < (u16)*esabadata_number; i++) {
        u32 cmpv = (u16)GSflagGet(esabadata[i].flagID);
        if (cmpv == esabapokemondata_EX[0].id) {
            foundA = (enum TsE)(1);
            break;
        }
    }
    if (foundA) {
        probA = 0;
    }
    foundB = 0;
    for (i = 0; i < (u16)*esabadata_number; i++) {
        u32 cmpv = (u16)GSflagGet(esabadata[i].flagID);
        if (cmpv == esabapokemondata_EX[1].id) {
            foundB = 1;
            break;
        }
    }
    if (foundB) {
        probB = 0;
    }
    roll = (u16)HSD_Rand() % 100;
    if (roll < probA) {
        setPokemon((u16)place, esabapokemondata_EX[0].id);
    } else if (roll < (u16)(probA ? probA + probB : probB)) {
        setPokemon((u16)place, esabapokemondata_EX[1].id);
    } else {
        roll = (u16)HSD_Rand() % 100;
        total = 0;
        for (k = 0; k < count; k++) {
            EsaTable* t = getTable(place);
            total += t ? t->entries[k].prob : 0;
            if (total >= roll) {
                volatile EsaTable* t2 = getTable(place);
                id = t2 ? t2->entries[k].id : 0;
                setPokemon(place, id);
                return;
            }
        }
    }
}
