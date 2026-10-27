#include <dolphin/types.h>

struct Pokemon;
struct FightOutPokemon;
struct FightPokemon;
struct FightItem;
struct FIGHT_TRAINER;
struct Hero;

enum darkPokemonWhere {};

class DeckDarkPokemon {
public:
    static DeckDarkPokemon* getDeckDarkPokemonObj(u32 id);
    u8 getRevers() const;
};

class DarkPokemon {
public:
    void setPlace(darkPokemonWhere where, u8 flag);
    void setReversPattern(u8 pattern);
};

extern "C" {

extern u8 ActionSeqNo;
extern u8 WildPokemonCatchFlag;
extern u8 ServerWork[8];
extern u32 GetFailMsgTbl[];
extern u32 GetYaseiFailMsgTbl[];
extern u8 ITEM_MonsGetSuccess[];
extern u8 ITEM_MonsGetFail[];

u8* fightSeq_GetWazaSeq(void);
void fightSeq_NextWazaSeq(s32 size);
void fightSeq_JumpWazaSeq(void* target);
FightOutPokemon* fightTargetGetPtrAsNowFightType(u16 slotType, void* ptr);
s32 fightFloor_GetFightType(void* floor);
u8 fightFloor_GetFightKind(void* floor);
u32 fightFloor_GetEncountFloorId(void);
u16 fightFloor_GetEncountDataId(void* floor);
u8 fightFloor_GetTikeiDataId(void* floor);
u8 fightFloor_GetFightTypeEntryPokemonNum(void* floor);
u8 fightFloor_GetStockPokemonNum(void* floor);
void fightFloor_SetStockPokemonBallID(void* floor, u8 index, u8 ballID);
void fightFloor_SetStockPokemonPtr(void* floor, u8 index, Pokemon* pokemon);
void fightFloor_SetStockPokemonNum(void* floor, u8 num);
u8 fightFloor_GetFightKindGetFriendFlag(void* floor);
u8 fightFloor_GetFightKindBossFlag(void* floor);
u8 fightFloor_GetFightKindDoZukanTukamaetaFlag(void* floor);
u8 fightFloor_GetTrainer(void* floor);
u16 fightFloor_GetTurnCount(void* floor);
s16 fightFloorGetFightPokemonEntryCntInc(void* floor);
FIGHT_TRAINER* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void* floor, FightOutPokemon* p);
Hero* fightFloorGetFightOutPokemonPtrToHeroPtr(void* floor, FightOutPokemon* p);
FightItem* fightOutPokemon_GetFightItemPtr(FightOutPokemon* p);
u16 fightItem_GetItemDataId(FightItem* item);
u32 fightItem_GetCount(FightItem* item);
u32 itemDB_GetBuff(u16 id);
u32 itemDB_GetName(u16 id);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon* p);
FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon* p);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon* fp);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon* p);
char* fightOutPokemonGetNicknamePtr(FightOutPokemon* p);
u8 figthOutPokemonGetLevel(FightOutPokemon* p);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon* p, u16 zokusei);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon* p, u16 id);
void fightOutPokemonHokakuEffect(FightOutPokemon* p, u8 shakes, u16 ball, u8 mode, u8* work);
void fightTrainerHokakuThrowEffect(FIGHT_TRAINER* trainer, u16 ball, u8 mode);
u8 pokemonIsDarkPokemon(Pokemon* p);
u16 pokemon_GetDarkpokemonDataId(Pokemon* p);
u16 pokemon_GetPokemonDataId(Pokemon* p);
u16 pokemon_GetHp(Pokemon* p);
u16 pokemon_GetMaxHp(Pokemon* p);
void pokemon_SetHp(Pokemon* p, u16 hp);
void pokemon_SetLevel(Pokemon* p, u8 level);
void pokemon_SetExp(Pokemon* p, u32 exp);
u32 pokemonGetLevelToExp(Pokemon* p, u8 level);
void pokemonResetBasisStatus(Pokemon* p);
char* pokemon_GetNicknamePtr(Pokemon* p);
void pokemon_SetFightTrainerPokemonDataId(Pokemon* p, u16 id);
u8 pokemonCheckValid(Pokemon* p);
u8 pokemonIsJoutaiDataId(Pokemon* p, u16 id);
void pokemonSetCountAsJoutaiDataId(Pokemon* p, u16 id, u32 value);
void pokemonSetOnZukanFlag(Pokemon* p, u8 caught);
void pokemonSetOnDarkPokemonFlag(Pokemon* p, u8 snatched);
u8 pokemonDB_GetGet(u16 id);
bool pokemonDB_GetTukamaetaFlag(u16 id);
u8 darkPokemonBiosGetLevel(u16 id);
u8 darkPokemonBiosGetHokakuritu(u16 id);
u8 darkPokemonBiosGetSnatchSuccessFlag(u16 id);
DarkPokemon* darkPokemonGetDarkPokemon(u32 id);
s16 heroCatchPokemon(Hero* hero, Pokemon* pokemon, u32 floorId, u8 ball, u8 allowPCBox);
Pokemon* heroGetStatus(Hero* hero, u32 selector, u16 index);
FightPokemon* fightTrainerSearchInvalidFightPokemonPtr(FIGHT_TRAINER* trainer, u16 num);
u8 fightTrainerIsGcHero(FIGHT_TRAINER* trainer);
void fightTrainer_SetNigeruCount(FIGHT_TRAINER* trainer, u8 value);
void fightPokemonCreate(FIGHT_TRAINER* trainer, FightPokemon* fp, Pokemon* p, s16 entry);
void fightPokemon_SetCatchEntryFlag(FightPokemon* fp, u8 value);
void fightPokemon_SetHokakuFlag(FightPokemon* fp, u8 value);
void fightPokemonGetFriendFormPokemonFriendFilterId(FightPokemon* fp, u32 id);
void fightMsgctrlSetValue(s32 id, u32 value);
u32 fightMenuOpenMsg(u32 msg);
void fightMenuCloseMsg(void);
u8 fightSeqOpenMsg(u32 msgId);
u32 fightMenuGetFightOutPokemonPtrToStatusMenuId(FightOutPokemon* p, u8 type, bool flag);
void fightSeqKizetuInit(FightOutPokemon* p);
void fightSeqCheckSetHensinBuffToMotoFightPokemon(FightOutPokemon* p, u16 id);
void fightMainAllCamera(u8 a, u8 b);
u32 GSthreadGetCurrentThread(void);
void menuCloseCustom(s32 menuID, s32 a, s32 b);
s32 winMsgOpenField(u32 msg, bool a, bool b);
s8 menuSubOpenYesNoField(void);
s32 menuNameEntryOpen(s32 mode, s32 param);
char* GSmsgGetGSchar(u32 msg);
void soundOpenPlayME(u32 id, u32 a, u8 volume);
u32 HSD_Rand(void);
double sqrt(double x);

void WS_GETEND(void) {
    ActionSeqNo = 0x1;
}

void WS_ITEMEND(void) {
    ActionSeqNo = 0x1;
}

void WS_ITEM_CONDITION_RECOVER(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_ITEM_HP_KAIFUKU(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_NICKNAME(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(5);
}

void WS_ZUKAN(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_ZUKAN_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(5);
}

}

u8 fightSeqItemSeq_AddPoke(Pokemon* pokemon, u8 ball, FIGHT_TRAINER* trainer, Hero* hero);

extern "C" {

void WS_ADD_POKE(void) {
    FIGHT_TRAINER* trainer;
    u8* seq;
    s32 type;
    FightOutPokemon* attacker;
    FightOutPokemon* target;
    Pokemon* pokemon;
    u8 num;
    u8 ball;
    FIGHT_TRAINER* targetTrainer;
    u8 full;
    Hero* hero;

    full = 0;
    type = fightFloor_GetFightType(0);
    seq = fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    ball = itemDB_GetBuff(fightItem_GetItemDataId(fightOutPokemon_GetFightItemPtr(attacker)));
    target = fightTargetGetPtrAsNowFightType(0x12, 0);
    pokemon = fightPokemonGetPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(target));
    targetTrainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, target);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, attacker);
    hero = fightFloorGetFightOutPokemonPtrToHeroPtr(0, attacker);

    if (fightFloor_GetFightKind(0) == 0xC) {
        full = fightSeqItemSeq_AddPoke(pokemon, ball, trainer, hero);
    } else if (pokemonIsDarkPokemon(pokemon) == 1) {
        num = fightFloor_GetStockPokemonNum(0);
        fightFloor_SetStockPokemonBallID(0, num, ball);
        fightFloor_SetStockPokemonPtr(0, num, pokemon);
        fightFloor_SetStockPokemonNum(0, num + 1);
        u8 menu = fightMenuGetFightOutPokemonPtrToStatusMenuId(target, type, 0);
        if (GSthreadGetCurrentThread()) {
            menuCloseCustom(menu, 2, 1);
        } else {
            menuCloseCustom(menu, 2, 0);
        }
    }
    pokemon_SetHp(pokemon, 0);
    pokemon_SetHp(fightOutPokemonGetPokemonPtr(target), 0);
    fightSeqKizetuInit(target);
    fightPokemon_SetHokakuFlag(fightOutPokemon_GetFightPokemonPtr(target), 1);
    fightSeqCheckSetHensinBuffToMotoFightPokemon(target, 0xD2);
    fightTrainer_SetNigeruCount(targetTrainer, 1);
    if (full == 1) {
        fightMainAllCamera(1, 0);
        fightSeq_NextWazaSeq(5);
    } else {
        if (fightFloor_GetFightKind(0) == 0xC) {
            fightSeqOpenMsg(0x5002);
            fightMenuCloseMsg();
        }
        fightSeq_JumpWazaSeq(*(void**)(seq + 1));
    }
}

}

u8 fightSeqItemSeq_AddPoke(Pokemon* pokemon, u8 ball, FIGHT_TRAINER* trainer, Hero* hero) {
    Pokemon* caught;
    FightPokemon* fp;
    u8 level;
    u8 full;
    u32 floorId;
    u32 entryNum;
    DarkPokemon* dark;
    DeckDarkPokemon* deck;
    full = 0;
    floorId = fightFloor_GetEncountFloorId();
    deck = DeckDarkPokemon::getDeckDarkPokemonObj(pokemon_GetDarkpokemonDataId(pokemon));
    dark = darkPokemonGetDarkPokemon(pokemon_GetDarkpokemonDataId(pokemon));
    entryNum = fightFloor_GetFightTypeEntryPokemonNum(0);

    if (fightFloor_GetFightKind(0) == 0xC) {
        WildPokemonCatchFlag = 1;
        fightMsgctrlSetValue(0x16, (u32)pokemon_GetNicknamePtr(pokemon));
        winMsgOpenField(0x4F85, 1, 1);
        if (menuSubOpenYesNoField() == 0) {
            menuNameEntryOpen(4, 0);
        }
    }
    if (pokemonIsDarkPokemon(pokemon) == 1) {
        u16 hp = pokemon_GetHp(pokemon);
        u16 percent = (hp * 100) / pokemon_GetMaxHp(pokemon);
        level = darkPokemonBiosGetLevel(pokemon_GetDarkpokemonDataId(pokemon));
        pokemon_SetLevel(pokemon, level);
        s32 tmp1 = pokemonGetLevelToExp(pokemon, level);
        pokemon_SetExp(pokemon, tmp1);
        pokemonResetBasisStatus(pokemon);
        u16 newHp = (percent * pokemon_GetMaxHp(pokemon)) / 100;
        if (newHp == 0 && hp != 0) {
            newHp = 1;
        }
        pokemon_SetHp(pokemon, newHp);
    }
    u8 rev = deck->getRevers();
    dark->setReversPattern(rev);
    pokemon_SetFightTrainerPokemonDataId(pokemon, 0);
    s16 slot = heroCatchPokemon(hero, pokemon, floorId, (u8)ball, 1);
    if (slot == -1) {
        full = 1;
    }
    if (full == 0 && slot >= 0) {
        fp = fightTrainerSearchInvalidFightPokemonPtr(trainer, entryNum);
        if (fp) {
            caught = heroGetStatus(hero, 3, slot);
            if (caught && pokemonCheckValid(caught) == 1) {
                if (dark) {
                    dark->setPlace((darkPokemonWhere)1, 0);
                }
                if (pokemonIsJoutaiDataId(caught, 4) == 1) {
                    pokemonSetCountAsJoutaiDataId(caught, 4, 1);
                }
                fightPokemonCreate(trainer, fp, caught, fightFloorGetFightPokemonEntryCntInc(0));
                fightPokemon_SetCatchEntryFlag(fp, 1);
                if (fightFloor_GetFightKindGetFriendFlag(0) == 1 && fightFloor_GetFightKindBossFlag(0) == 1 &&
                    fightTrainerIsGcHero(trainer) == 1) {
                    fightPokemonGetFriendFormPokemonFriendFilterId(fp, 3);
                }
            }
        }
    }
    if (fightFloor_GetFightKindDoZukanTukamaetaFlag(0) == 1 && fightTrainerIsGcHero(trainer) == 1) {
        pokemonSetOnZukanFlag(pokemon, 1);
        pokemonSetOnDarkPokemonFlag(pokemon, 1);
    }
    return full;
}

extern "C" {

void WS_BALL_THROW(void) {
    u32 threshold;
    u32 value;
    u8 bonus;
    u8 rate = 0;
    u8 shakes;
    bonus = 0;
    u8 work[8];
    fightFloor_GetEncountDataId(0);
    fightSeq_GetWazaSeq();
    u32 tikei = fightFloor_GetTikeiDataId(0);
    FightOutPokemon* attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    FightItem* item = fightOutPokemon_GetFightItemPtr(attacker);
    fightItem_GetCount(item);
    u16 ball = fightItem_GetItemDataId(item);
    FightOutPokemon* target = fightTargetGetPtrAsNowFightType(0x12, 0);
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(target);
    u16 darkId = pokemon_GetDarkpokemonDataId(pokemon);
    u16 monsId = pokemon_GetPokemonDataId(pokemon);
    u32 level = figthOutPokemonGetLevel(target);
    u32 hp = pokemon_GetHp(pokemon);
    u32 maxHp = pokemon_GetMaxHp(pokemon);
    FIGHT_TRAINER* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, attacker);
    u8 catchRate;
    if (pokemonIsDarkPokemon(pokemon) == 1) {
        catchRate = darkPokemonBiosGetHokakuritu(darkId);
    } else {
        catchRate = pokemonDB_GetGet(monsId);
    }

    switch (ball) {
    case 2:
        rate = 20;
        break;
    case 3:
        rate = 15;
        break;
    case 4:
    case 5:
        rate = 10;
        break;
    case 6:
        if (fightOutPokemonIsZokuseiDataId(target, 0xB) == 1 || fightOutPokemonIsZokuseiDataId(target, 6) == 1) {
            rate = 30;
        } else {
            rate = 10;
        }
        break;
    case 7:
        if ((u16)(tikei - 3) <= 1 || tikei == 5) {
            rate = 35;
        } else {
            rate = 10;
        }
        break;
    case 8:
        if (level < 40) {
            rate = 40 - level;
            if (rate < 10) {
                rate = 10;
            }
        } else {
            rate = 10;
        }
        break;
    case 9:
        if (pokemonIsDarkPokemon(pokemon) == 1) {
            if (darkPokemonBiosGetSnatchSuccessFlag(darkId) == 1) {
                bonus = 1;
            }
        } else if (pokemonDB_GetTukamaetaFlag(0) == 1) {
            bonus = 1;
        }
        if (bonus == 1) {
            rate = 30;
        } else {
            rate = 10;
        }
        break;
    case 10:
        rate = fightFloor_GetTurnCount(0) + 10;
        if (rate > 40) {
            rate = 40;
        }
        break;
    case 11:
    case 12:
        rate = 10;
        break;
    }

    if (ball == 1 || darkId == 1) {
        shakes = 4;
    } else {
        value = ((catchRate * rate) / 10 * (maxHp * 3 - hp * 2)) / (maxHp * 3);
        if (fightOutPokemonIsJoutaiDataId(target, 8) == 1 || fightOutPokemonIsJoutaiDataId(target, 7) == 1) {
            value *= 2;
        }
        if (fightOutPokemonIsJoutaiDataId(target, 3) == 1 || fightOutPokemonIsJoutaiDataId(target, 4) == 1 ||
            fightOutPokemonIsJoutaiDataId(target, 5) == 1 || fightOutPokemonIsJoutaiDataId(target, 6) == 1) {
            value = (value * 15) / 10;
        }
        if (value >= 0xFF) {
            shakes = 4;
        } else {
            u32 root = sqrt(0xFF0000 / value);
            threshold = 0xFFFF0 / (u32)sqrt(root);
            for (shakes = 0; shakes < 4; shakes++) {
                if ((u16)HSD_Rand() >= threshold) {
                    break;
                }
            }
        }
    }

    fightTrainerHokakuThrowEffect(trainer, ball, 0);
    fightOutPokemonHokakuEffect(target, shakes, ball, 0, work);
    if (!fightFloor_GetTrainer(0)) {
        fightTrainerHokakuThrowEffect(trainer, ball, 3);
    }
    if (fightFloor_GetFightKind(0) == 0xC || fightFloor_GetFightKind(0) == 0xD) {
        fightMsgctrlSetValue(0x5D, 0);
        fightMsgctrlSetValue(0x29, (u32)GSmsgGetGSchar(itemDB_GetName(ball)));
        fightMenuOpenMsg(0x4FFC);
    } else {
        fightMsgctrlSetValue(0x5D, 0);
        fightMenuOpenMsg(0x4FD9);
    }
    fightTrainerHokakuThrowEffect(trainer, ball, 1);
    fightTrainerHokakuThrowEffect(trainer, ball, 2);
    if (fightFloor_GetTrainer(0)) {
        fightTrainerHokakuThrowEffect(trainer, ball, 3);
    }
    fightOutPokemonHokakuEffect(target, shakes, ball, 1, work);
    fightMsgctrlSetValue(0x16, (u32)fightOutPokemonGetNicknamePtr(target));
    if (shakes >= 4) {
        fightTrainerHokakuThrowEffect(trainer, ball, 4);
        if (fightFloor_GetFightKind(0) == 0xC || fightFloor_GetFightKind(0) == 0xD) {
            fightMsgctrlSetValue(0x5D, 0);
            fightMenuOpenMsg(0x4FF9);
        } else {
            fightMsgctrlSetValue(0x5D, 0);
            fightMenuOpenMsg(0x4FE0);
        }
        soundOpenPlayME(0x36B, 0, 0xFF);
        fightTrainerHokakuThrowEffect(trainer, ball, 5);
        fightMenuCloseMsg();
        fightSeq_JumpWazaSeq(ITEM_MonsGetSuccess);
    } else {
        fightOutPokemonHokakuEffect(target, shakes, ball, 2, work);
        ServerWork[5] = shakes;
        if (fightFloor_GetFightKind(0) == 0xC || fightFloor_GetFightKind(0) == 0xD) {
            fightMenuOpenMsg(GetYaseiFailMsgTbl[ServerWork[5]]);
        } else {
            fightMenuOpenMsg(GetFailMsgTbl[ServerWork[5]]);
        }
        fightOutPokemonHokakuEffect(target, shakes, ball, 3, work);
        fightMenuCloseMsg();
        fightSeq_JumpWazaSeq(ITEM_MonsGetFail);
    }
    fightTrainerHokakuThrowEffect(trainer, ball, 6);
    fightOutPokemonHokakuEffect(target, shakes, ball, 4, work);
}

}
