#include <dolphin/types.h>
extern "C" void* memcpy(void*, const void*, unsigned long);

enum FootStepCounter { FOOT_STEP_COUNTER_0, FOOT_STEP_COUNTER_1 };
enum darkPokemonWhere { place0, place1, place2, place3, place4, place5, place6 };

class DarkPokemon {
public:
    void setPlace(darkPokemonWhere, u8);
};

class Pokemon {
public:
    DarkPokemon* getDarkPokemon();
};

// Daycare save block (savedata kind 0xB).
struct Sodateya {
    u8 active;
    u8 level;
    u16 steps;
    s32 dp;
    u8 pokemon[0xC4];
};

extern "C" {
void* savedataGetStatus(void*, u16);
Pokemon* heroBiosGetPokemonPtr(void* hero, u16 index);
u32 heroGetPokeomCount(void* hero);
u8 pokemonCheckValid(Pokemon*);
s32 pokemonBiosGetDp(Pokemon*);
bool pokemonBiosGetDarkFlag(Pokemon*);
u16 pokemonBiosGetDarkpokemonDataId(Pokemon*);
u16 pokemonBiosGetHp(Pokemon*);
u8 pokemonBiosGetLevel(Pokemon*);
u32 pokemonBiosGetExp(Pokemon*);
f32 pokemonGetDp(Pokemon*);
void pokemonInit(Pokemon*);
void pokemonAllKaihuku(Pokemon*);
u8 pokemonIsJoutaiDataId(Pokemon*, u16);
void pokemonInitJoutaiDataId(Pokemon*, u16);
void pokemonAddDpFormPokemonDpFilterId(Pokemon*, u16, u16);
void pokemonGrowBasisStatus(Pokemon*, u32);
s8 pokemonOboeWaza(Pokemon*, u8, u8, u8*);
u8 darkPokemonBiosGetReliveFlag(u16);
bool darkPokemonBiosGetInformationFlag(u16);
s32 darkPokemonBiosGetSteps(u16);
void darkPokemonBiosSetSteps(u16, u16);
u32 GSflagGet(u32);
void GSflagSet(u32, u32);
void GSthreadSwitch(void);
void heroMoveInitEvent(void);
void heroMoveSetColision(bool);
void heroMoveTermEvent(void);
void menuScriptInfoRelive(Pokemon*, s32);
s32 heroMoveAddStepCallback(void (*callback)(long, FootStepCounter, long), s32);
}

static void _sodateyaCallBackFunc(long, FootStepCounter, long);

static s32 _sodateyaHandle;

static inline Pokemon* getPokemonPtrInline(Sodateya* s) {
    if (s == 0) {
        s = (Sodateya*)savedataGetStatus(0, 0xB);
    }
    return (Pokemon*)s->pokemon;
}

extern "C" {

s32 sodateyaeChekcRais(void) {
    Sodateya* s = (Sodateya*)savedataGetStatus(0, 0xB);
    if (s == 0) {
        return -1;
    }
    switch (s->active) {
    case 1:
        return 1;
    case 0:
        return 0;
    default:
        return -1;
    }
}

s32 sodateyaCalcPrice(s32 count) {
    s32 price;
    Sodateya* s = (Sodateya*)savedataGetStatus(0, 0xB);
    if ((u32)(s->active != 0 ? s->dp : -1) != 0) {
        s32 dp;
        s32 q;
        savedataGetStatus(0, 0xB);
        s = (Sodateya*)savedataGetStatus(0, 0xB);
        dp = s->active != 0 ? s->dp : -1;
        s = (Sodateya*)savedataGetStatus(0, 0xB);
        q = (dp - pokemonBiosGetDp((Pokemon*)s->pokemon)) / 100;
        if (q != 0) {
            price = q * 100 + 100;
        } else {
            price = 0;
        }
    } else {
        price = 0;
    }
    return count * 100 + price + 100;
}

void sodateyaReclaim(s32 slot) {
    Sodateya* s;
    Pokemon* hp = heroBiosGetPokemonPtr(savedataGetStatus(0, 2), slot);
    s = (Sodateya*)savedataGetStatus(0, 0xB);
    if (hp != 0) {
        Pokemon* np = getPokemonPtrInline(s);
        if (np != 0) {
            memcpy(hp, np, 0xC4);
            if (pokemonBiosGetDarkFlag(np)) {
                pokemonBiosGetDp(np);
            }
            DarkPokemon* d = hp->getDarkPokemon();
            if (d != 0) {
                d->setPlace(place1, 0);
            }
            if (s == 0) {
                s = (Sodateya*)savedataGetStatus(0, 0xB);
            }
            if (s != 0) {
                s->active = 0;
            }
            pokemonInit(np);
        }
    }
    pokemonAllKaihuku(hp);
}

void sodateyaRaise(s32 slot) {
    Pokemon* cur;
    Pokemon* poke;
    void* hero;
    u32 count;
    Sodateya* s;
    Pokemon* np;
    u8 ok;
    hero = savedataGetStatus(0, 2);
    poke = heroBiosGetPokemonPtr(hero, slot);
    count = heroGetPokeomCount(hero);
    s = (Sodateya*)savedataGetStatus(0, 0xB);
    if (poke == 0) {
        ok = 0;
    } else {
        u8 level = pokemonBiosGetLevel(poke);
        Sodateya* t = s;
        if (t == 0) {
            t = (Sodateya*)savedataGetStatus(0, 0xB);
        }
        if (t != 0) {
            t->level = level;
        }
        np = getPokemonPtrInline(s);
        if (np == 0) {
            ok = 0;
        } else {
            if (pokemonIsJoutaiDataId(poke, 0x3E)) {
                pokemonInitJoutaiDataId(poke, 0x3E);
            }
            memcpy(np, poke, 0xC4);
            if (pokemonBiosGetDarkFlag(poke)) {
                s->dp = pokemonBiosGetDp(poke);
            } else {
                s->dp = 0;
            }
            DarkPokemon* d = poke->getDarkPokemon();
            if (d != 0) {
                d->setPlace(place4, 0);
            }
            if (s == 0) {
                s = (Sodateya*)savedataGetStatus(0, 0xB);
            }
            if (s != 0) {
                s->active = 1;
            }
            pokemonInit(poke);
            ok = 1;
        }
    }
    if (ok && slot < 6) {
        int i = slot;
        int end = count;
        end--;
        for (; i < end; i++) {
            cur = heroBiosGetPokemonPtr(hero, i);
            poke = heroBiosGetPokemonPtr(hero, i + 1);
            if (!pokemonCheckValid(poke)) {
                break;
            }
            memcpy(cur, poke, 0xC4);
        }
        pokemonInit(poke);
    }
}

s32 sodateyaGetPokemonDPValue(void) {
    Sodateya* s;
    s32 dp;
    savedataGetStatus(0, 0xB);
    s = (Sodateya*)savedataGetStatus(0, 0xB);
    dp = s->active != 0 ? s->dp : -1;
    s = (Sodateya*)savedataGetStatus(0, 0xB);
    return (dp - pokemonBiosGetDp((Pokemon*)s->pokemon)) / 100;
}

s32 sodateyaGetPokemonLevelUpValue(void) {
    Sodateya* s = (Sodateya*)savedataGetStatus(0, 0xB);
    u8 level = s->active != 0 ? s->level : 0xFF;
    s = (Sodateya*)savedataGetStatus(0, 0xB);
    u8 now = pokemonBiosGetLevel((Pokemon*)s->pokemon);
    return now - level;
}

u8* sodateyaGetPokemonPtr(void* data) {
    if (data == 0) {
        data = savedataGetStatus(0, 0xB);
    }
    return (u8*)data + 8;
}

void sodateyaInit(Sodateya* data) {
    Sodateya* status = data;
    if (status == 0) {
        status = (Sodateya*)savedataGetStatus(0, 0xB);
    }
    if (status != 0) {
        data = status;
        if (status == 0) {
            data = (Sodateya*)savedataGetStatus(0, 0xB);
        }
        if (data != 0) {
            data->steps = 0;
        }
        status->level = 0;
        status->active = 0;
    }
}

void sodateyaHeroCallBackInit(void) {
    _sodateyaHandle = heroMoveAddStepCallback(_sodateyaCallBackFunc, 0);
}

}

static inline u16 getDarkId(Pokemon* p, FootStepCounter mode) {
    u16 d = pokemonBiosGetDarkpokemonDataId(p);
    if (d != 0) {
        if (mode == FOOT_STEP_COUNTER_1) {
            if (darkPokemonBiosGetReliveFlag(d) || d == 0x49) {
                return 0;
            }
            if (pokemonGetDp(p) == 0.0f) {
                return d;
            }
            return 0;
        }
        if (darkPokemonBiosGetReliveFlag(d) || (pokemonBiosGetHp(p) != 0 && d == 0x49)) {
            return 0;
        }
    }
    return d;
}

static inline void reliveEvent(Pokemon* p) {
    heroMoveInitEvent();
    heroMoveSetColision(true);
    GSthreadSwitch();
    menuScriptInfoRelive(p, 1);
    heroMoveTermEvent();
}

static void _sodateyaCallBackFunc(long, FootStepCounter mode, long steps) {
    u16 i;
    void* hero = savedataGetStatus(0, 2);
    u16 progress;
    if (hero != 0) {
        for (i = 0; i < 6; i++) {
            Pokemon* p = heroBiosGetPokemonPtr(hero, i);
            if (pokemonCheckValid(p) && p != 0) {
                u16 dark = getDarkId(p, mode);
                if (dark != 0) {
                    u32 cmpv = pokemonBiosGetDp(p);
                    if (cmpv != 0) {
                        u16 sum = steps + darkPokemonBiosGetSteps(dark);
                        if (sum >= 0x100) {
                            pokemonAddDpFormPokemonDpFilterId(p, 0, 1);
                            if (pokemonGetDp(p) == 0.0f) {
                                u16 d2 = getDarkId(p, mode);
                                if (d2 != 0 && !darkPokemonBiosGetInformationFlag(d2)) {
                                    reliveEvent(p);
                                }
                                darkPokemonBiosSetSteps(dark, 0);
                            } else {
                                darkPokemonBiosSetSteps(dark, sum - 0x100);
                            }
                        } else {
                            darkPokemonBiosSetSteps(dark, sum);
                        }
                    } else {
                        u16 d2 = getDarkId(p, mode);
                        if (d2 != 0 && !darkPokemonBiosGetInformationFlag(d2)) {
                            reliveEvent(p);
                        }
                    }
                }
            }
        }
    }
    if (GSflagGet(4) != 0) {
        progress = GSflagGet(5);
        if (progress < 10000) {
            s32 t = progress + steps;
            if (t >= 0xFFFF) {
                t = 0xFFFF;
            }
            progress = t;
        }
        GSflagSet(5, progress);
    }
    Sodateya* s = (Sodateya*)savedataGetStatus(0, 0xB);
    if (s->active != 0) {
        if (steps > 0) {
            Pokemon* np = (Pokemon*)((u8*)savedataGetStatus(0, 0xB) + 8);
            u16 dark = 0;
            if (np != 0) {
                dark = getDarkId(np, mode);
                if (dark != 0 && darkPokemonBiosGetReliveFlag((u8)dark)) {
                    dark = 0;
                }
            }
            if (dark == 0) {
                if (pokemonBiosGetLevel(np) < 100) {
                    u32 exp = pokemonBiosGetExp(np);
                    u32 sum = exp + steps;
                    u32 arg = 0xFFFFFFFF;
                    arg = exp > sum ? arg : sum;
                    pokemonGrowBasisStatus(np, arg);
                    u8 learned = 0;
                    pokemonOboeWaza(np, pokemonBiosGetLevel(np), 1, &learned);
                }
            }
        }
        s = (Sodateya*)savedataGetStatus(0, 0xB);
        if (s != 0) {
            s->steps = progress;
        }
    }
}
