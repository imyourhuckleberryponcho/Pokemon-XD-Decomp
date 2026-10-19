// STATUS: all 33 functions written bottom-to-top (unit was built with -inline deferred).
// Item-use handlers for the pocket menu (menuUseItem*).
#include <dolphin/types.h>

// Menu callbacks were built without the peephole optimizer.
#pragma peephole off

struct Hero {
    u8 getHeroStyle() const;
};
struct Pokemon {
    u8 data[0xC4];
    u16 getPokemonDataId() const;
};
struct FightPokemon;
struct FIGHT_FLOOR;
struct FightTrainer;
struct PokemonData;
struct Gamedata;
struct POKEMON_EVOLUTION_INFO;
struct tagWINDOW_WORK;

struct underTakerBios {
    u8 data[4];
    u32 getPlaceMsg();
};

struct UnderTakerData {
    u8 pad[0x14];
    u32 flagId;
};

struct ITEMUSE2POKEMON_LOG1 {
    s32 kind;
    s16 a;
    s16 b;
};

struct LogMsg {
    s32 kind;
    s32 msg;
};
struct LogMsgField {
    s32 kind;
    s32 msg;
    s32 link;
};
struct ScriptCologn {
    u16 item;
    s32 msgA;
    s32 msgB;
};

struct MENU_LVUP_STATUS {
    u8 flag;
    u8 pad;
    s16 hp;
    s16 atk;
    s16 def;
    s16 spd;
    s16 spAtk;
    s16 spDef;
    s16 pad2;
};

struct CraneMemo {
    u16 item;
    u16 index;
    s32 msg;
};

struct PocketEntry {
    u16 item;
    u16 pad;
    u32 value;
};
struct PocketScript {
    PocketEntry e[8];
    s32 count;
};

extern "C" {
extern PocketScript menuPocketWork;
extern UnderTakerData* undertakerdata;

u32 GSflagGet(u32 id);
f32 GSgfxVideoGetLastRenderTime(void);
void GSinputMotorStart(s32 pad, s32, s32 strength, s32 frames, s32);
char* GSmsgGetGSchar(u32 msg);
u8 GSsndPlayNow(u32 id);
s32 GSsndGetStatus(u32 id);
u8 GSsndPlayVolume(u32 id, s32 time, u8 vol, u32 flag);
void GSthreadSwitch(void);
s32 evolutionWazaLearn(Pokemon* p, u16 waza, u8* slot, s32 a, s8 (*cb)(Pokemon*, u16, s32), s32 b);
void fadeCheck(s32);
void fadeSet(s32 type, f32 time);
FIGHT_FLOOR* fightFloorGetNowPtr(void);
s32 fightFloor_GetFightKind(FIGHT_FLOOR* floor);
u32 fightFloor_GetStockPokemonNum(FIGHT_FLOOR* floor);
u8 fightTrainerIsSelectedItemBall(FightTrainer* trainer);
s32 gamedatasaveGetStatus(Gamedata* ptr, u32 kind);
u32 itemDataBiosGetHidenMachineNo(u8* p);
u8 itemDataBiosGetItemEffectParam(u8* p);
u8* itemDataBiosGetPtr(u16 index);
u32 itemDataBiosGetWazaIDByWazaMachineNo(u8 machineNo);
u32 itemDataBiosGetWazaMachineNo(u8* p);
void itemParamConvertOrigFormat(void* dst, void* src);
u8 itemParamGetPPSelectFlag(const void* item);
u8* itemParamGetPtr(u8 idx);
s32 itemParamGetRecoverType(void* itemParam);
s16 itemUse2Pokemon(ITEMUSE2POKEMON_LOG1* log, Pokemon* pokemon, FightPokemon* fightPokemon, u16 itemDataId, u8 moveSlot);
u8 menuOffScreenSetDisp(u8 val);
u8 menuOffScreenSetPriority(u8 val);
void menuPocket2AddItemScript(s32, s32);
void menuPocket2ClosePokemonMenu(s32 slot);
s32 menuPocket2GetCurrentTemochiPokemonSlotID(void);
void menuPocket2GetHero(Hero** hero, FightTrainer** trainer);
void menuPocket2GetTemochiPokemon(s32 slot, Pokemon** pokemon, FightPokemon** fightPokemon);
s32 menuPocket2OpenPokemonMenu(u32 item, int use);
void menuPokemonCloseWazaLight(void);
s32 menuPokemonOpenWazaLight(s8 index);
s32 menuPokemonStatusOpenWazaMachine(Pokemon* pokemon, u16 sel);
void menuPokemonUpdate(void);
void menuScriptUsohachi2(void);
s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 initial);
void msgctrlSetValue(s32 id, s32 value);
s8 pcboxGetNbPokemonBox();
s8 pcboxGetPokemonBoxNbEmptySlot(void* base, s8 b);
void pokemonAddDpFormPokemonDpFilterId(Pokemon* pokemon, u16 itemDataId, u16 filterId);
u8 pokemonBiosGetLevel(Pokemon* poke);
char* pokemonBiosGetNicknamePtr(Pokemon* poke);
u16 pokemonBiosGetPokemonDataId(Pokemon* poke);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon* poke, u32 wazaNum);
bool pokemonCheckValid(Pokemon* pokemon);
PokemonData* pokemonDataBiosGetPtr(u16 pokeNum);
u16 pokemonDataBiosGetVoice(PokemonData* pdata);
bool pokemonDataBiosGetWazaMcn(PokemonData* pdata, u16 index);
s32 pokemonEvolutionAll(Pokemon*, u16, u16, POKEMON_EVOLUTION_INFO*, Hero*, s32, s32, s32);
u16 pokemonEvolutionCheck(Pokemon*, s32, u16, u16*, POKEMON_EVOLUTION_INFO*);
f32 pokemonGetDp(Pokemon* pokemon);
void pokemonGetFriendFormPokemonFriendFilterId(Pokemon* pokemon, u16 itemDataId, u16 filterId);
u16 pokemonGetOboeWazaDataId(Pokemon* pokemon, u8 level, u8* cursor);
u16 pokemonGetSoubiItemSoubiDataId(Pokemon* pokemon);
s32 pokemonGetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index);
void pokemonInitJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
u8 pokemonIsDarkPokemon(Pokemon* pokemon);
bool pokemonIsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
s8 pokemonSearchWazaDataId(Pokemon* pokemon, u16 waza);
void pokemonWazaCreate(Pokemon* pokemon, u16 wazaNum, u16 waza);
void reliveHallInfomationPokemonDP0(Pokemon* p);
void soundOpenPlayME(u32 id, u32, u8 volume);
s8 winMsgCheck(void);
void winMsgClose(bool flag);
void winMsgCloseLevelUpStatus(bool flag);
s32 winMsgOpen(s8 type, u32 msg, bool a, bool b);
s32 winMsgOpenLevelUpFiledStatus(void* msg, bool a);
tagWINDOW_WORK* windowSearchID(s32 id);
}

extern "C" u16* GSmsgMakeGScharStr(u16*, long, unsigned long);

static PokemonData* getPokemonData(Pokemon* p);
static u32 playPokemonVoice(Pokemon* p);
static void waitTime(f32 t);
static void playRecoverSE(unsigned long item);
static void getLogMsgBattle(u16* out, int idx, ITEMUSE2POKEMON_LOG1* log, short n, Pokemon* p);
static void getLogMsgField(u16* out, int idx, ITEMUSE2POKEMON_LOG1* log, short n, Pokemon* p);
static s32 dispMsgYesNo(unsigned long msg);
static void dispMsg(unsigned long msg);
static s8 cbForgetWazaSelect(Pokemon* p, unsigned short sel, long x);
static void getPokemonLvupStatus(MENU_LVUP_STATUS* dst, Pokemon* p);
static void getDifLvupStatus(MENU_LVUP_STATUS* dst, MENU_LVUP_STATUS* a, MENU_LVUP_STATUS* b);
static void wazaLean(Pokemon* p, unsigned short waza, unsigned char slot);
static s32 wazaMachineProc(Pokemon* p, int machineNo);

extern "C" {

s32 menuUseItemDummy(u32 item, s32* consume) {
    dispMsg(0xC373);
    return 1;
}

s32 menuUseItemNoEffects(u32 item, s32* consume) {
    dispMsg(0xC374);
    return 1;
}

s32 menuUseItemNoPokecolo(u32 item, s32* consume) {
    dispMsg(0xC380);
    return 1;
}

s32 menuUseItemRecovery(u32 item, s32* consume) {
    ITEMUSE2POKEMON_LOG1 log[32];
    u16 text[66];
    Pokemon* pokemon;
    FightPokemon* fp;
    s32 slot;
    s16 result;
    slot = menuPocket2OpenPokemonMenu(item, 1);
    if (slot >= 0) {
        menuPocket2GetTemochiPokemon(slot, &pokemon, &fp);
        if (!pokemonIsJoutaiDataId(pokemon, 0x3E)) {
            result = itemUse2Pokemon(log, pokemon, fp, item, 0);
            if (result > 0) {
                playRecoverSE(item);
                menuPokemonUpdate();
            }
            getLogMsgField(text, 0x40, log, result, pokemon);
            msgctrlSetValue(0x4D, (s32)text);
            dispMsg(0x4289);
        } else {
            {
                char* nick = pokemonBiosGetNicknamePtr(pokemon);
                msgctrlSetValue(0x32, (s32)nick);
            }
            dispMsg(0xC372);
            result = 0;
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(slot);
    if (slot >= 0 && result > 0) {
        switch (item) {
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
            *consume = 0;
            break;
        default:
            *consume = 1;
            break;
        }
        return 0;
    }
    return 1;
}

s32 menuUseItemPPRecovery(u32 item, s32* consume) {
    ITEMUSE2POKEMON_LOG1 log[32];
    u16 text[66];
    Pokemon* pokemon;
    FightPokemon* fp;
    s32 slot;
    s16 result;
    s32 wazaSlot;
    s32 dark = 0;
    do {
        slot = menuPocket2OpenPokemonMenu(item, 1);
        if (slot >= 0) {
            menuPocket2GetTemochiPokemon(slot, &pokemon, &fp);
            if (pokemonIsJoutaiDataId(pokemon, 0x3E)) {
                dark = 1;
            } else {
                if (itemParamGetPPSelectFlag(itemParamGetPtr(itemDataBiosGetItemEffectParam(itemDataBiosGetPtr(item))))) {
                    wazaSlot = menuPokemonOpenWazaLight(slot);
                    menuPokemonCloseWazaLight();
                } else {
                    wazaSlot = 0;
                }
                if (wazaSlot < 0) {
                    continue;
                }
            }
        }
        break;
    } while (1);
    if (slot >= 0) {
        if (dark) {
            {
                char* nick = pokemonBiosGetNicknamePtr(pokemon);
                msgctrlSetValue(0x32, (s32)nick);
            }
            dispMsg(0xC372);
            result = 0;
        } else {
            result = itemUse2Pokemon(log, pokemon, fp, item, wazaSlot);
            if (result > 0) {
                playRecoverSE(item);
                menuPokemonUpdate();
            }
            getLogMsgField(text, 0x40, log, result, pokemon);
            msgctrlSetValue(0x4D, (s32)text);
            dispMsg(0x4289);
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(slot);
    if (slot >= 0 && result > 0) {
        *consume = 1;
        return 0;
    }
    return 1;
}

s32 menuUseItemAlldeathRcv(u32 item, s32* consume) {
    ITEMUSE2POKEMON_LOG1 log[32];
    u16 text[66];
    Pokemon* pokemon;
    FightPokemon* fp;
    s32 i;
    u16 total = 0;
    s16 result;
    s32 ret;
    menuPocket2OpenPokemonMenu(item, 0);
    for (i = 0; i < 6; i++) {
        menuPocket2GetTemochiPokemon(i, &pokemon, &fp);
        if (pokemonCheckValid(pokemon) && pokemonGetStatus(pokemon, 0, 0x83, 0) <= 0 &&
            !pokemonIsJoutaiDataId(pokemon, 0x3E)) {
            result = itemUse2Pokemon(log, pokemon, fp, item, 0);
            if (result > 0) {
                playRecoverSE(item);
                menuPokemonUpdate();
                getLogMsgField(text, 0x40, log, result, pokemon);
                msgctrlSetValue(0x4D, (s32)text);
                dispMsg(0x4289);
                total += result;
            }
        }
    }
    if (total == 0) {
        dispMsg(0xC374);
        ret = -1;
    } else {
        ret = 1;
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(-1);
    if (ret < 0) {
        return 1;
    }
    *consume = 1;
    return 0;
}

s32 menuUseItemListLVUp(u32 item, s32* consume) {
    ITEMUSE2POKEMON_LOG1 log[32];
    MENU_LVUP_STATUS diff;
    MENU_LVUP_STATUS before;
    MENU_LVUP_STATUS after;
    Pokemon* pokemon;
    FightPokemon* fp;
    u32 info[1];
    u16 evoExtra;
    u8 newSlot;
    u8 cursor = 0;
    s32 slot;
    s16 result;
    u16 evo;
    slot = menuPocket2OpenPokemonMenu(item, 1);
    if (slot >= 0) {
        menuPocket2GetTemochiPokemon(slot, &pokemon, &fp);
        if (!pokemonIsDarkPokemon(pokemon)) {
            getPokemonLvupStatus(&before, pokemon);
            result = itemUse2Pokemon(log, pokemon, fp, item, 0);
            if (result > 0) {
                menuPokemonUpdate();
            } else {
                result = 0;
            }
        } else {
            result = -1;
        }
        switch (result) {
        case 0:
            dispMsg(0xC374);
            break;
        case -1:
            dispMsg(0xC371);
            break;
        default: {
            u8 level;
            menuOffScreenSetPriority(0);
            soundOpenPlayME(0x3C7, 0, 0xFF);
            {
                char* nick = pokemonBiosGetNicknamePtr(pokemon);
                msgctrlSetValue(0x32, (s32)nick);
            }
            u8 lv = pokemonBiosGetLevel(pokemon);
            msgctrlSetValue(0x2F, lv);
            dispMsg(0xC367);
            getPokemonLvupStatus(&after, pokemon);
            getDifLvupStatus(&diff, &after, &before);
            diff.flag = 1;
            winMsgOpenLevelUpFiledStatus(&diff, 1);
            after.flag = 0;
            winMsgOpenLevelUpFiledStatus(&after, 1);
            winMsgCloseLevelUpStatus(1);
            level = pokemonBiosGetLevel(pokemon);
            cursor = 0;
            u16 waza;
            while ((waza = pokemonGetOboeWazaDataId(pokemon, level, &cursor)) != 0) {
                if (pokemonSearchWazaDataId(pokemon, waza) == -1) {
                    if (evolutionWazaLearn(pokemon, waza, &newSlot, 1, (s8(*)(Pokemon*, u16, s32))cbForgetWazaSelect, 0)) {
                        pokemonWazaCreate(pokemon, newSlot, waza);
                    }
                }
                cursor++;
            }
            evo = pokemonEvolutionCheck(pokemon, 0, 0, &evoExtra, (POKEMON_EVOLUTION_INFO*)info);
            break;
        }
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(slot);
    if (slot >= 0 && result > 0) {
        if (evo != 0) {
            fadeSet(3, 0.5f);
            fadeCheck(1);
            menuOffScreenSetDisp(0);
            pokemonEvolutionAll(pokemon, evo, evoExtra, (POKEMON_EVOLUTION_INFO*)info, 0, 1, 1, 0);
            menuOffScreenSetDisp(1);
            fadeSet(2, 0.5f);
            fadeCheck(1);
        }
        *consume = 1;
        return 0;
    }
    return 1;
}

}

static s8 cbForgetWazaSelect(Pokemon* p, unsigned short sel, long x) {
    int r;
    fadeSet(3, 0.5f);
    fadeCheck(1);
    r = menuPokemonStatusOpenWazaMachine(p, sel);
    if (r >= 4) {
        r = -1;
    }
    fadeSet(2, 0.5f);
    fadeCheck(1);
    return r;
}

static void getDifLvupStatus(MENU_LVUP_STATUS* dst, MENU_LVUP_STATUS* a, MENU_LVUP_STATUS* b) {
    dst->hp = a->hp - b->hp;
    dst->atk = a->atk - b->atk;
    dst->def = a->def - b->def;
    dst->spAtk = a->spAtk - b->spAtk;
    dst->spDef = a->spDef - b->spDef;
    dst->spd = a->spd - b->spd;
}

static void getPokemonLvupStatus(MENU_LVUP_STATUS* dst, Pokemon* p) {
    dst->hp = pokemonGetStatus(p, 0, 0x87, 0);
    dst->atk = pokemonGetStatus(p, 0, 0x88, 0);
    dst->def = pokemonGetStatus(p, 0, 0x89, 0);
    dst->spAtk = pokemonGetStatus(p, 0, 0x8A, 0);
    dst->spDef = pokemonGetStatus(p, 0, 0x8B, 0);
    dst->spd = pokemonGetStatus(p, 0, 0x8C, 0);
}

extern "C" {

s32 menuUseItemWPointUp(u32 item, s32* consume) {
    ITEMUSE2POKEMON_LOG1 log[32];
    u16 text[66];
    Pokemon* pokemon;
    FightPokemon* fp;
    s32 slot;
    s16 result;
    s32 wazaSlot;
    s32 dark = 0;
    u16 waza;
    do {
        slot = menuPocket2OpenPokemonMenu(item, 1);
        if (slot >= 0) {
            menuPocket2GetTemochiPokemon(slot, &pokemon, &fp);
            if (pokemonIsJoutaiDataId(pokemon, 0x3E)) {
                dark = 1;
            } else {
                wazaSlot = menuPokemonOpenWazaLight(slot);
                menuPokemonCloseWazaLight();
                if (wazaSlot < 0) {
                    continue;
                }
            }
        }
        break;
    } while (1);
    if (slot >= 0) {
        if (dark) {
            {
                char* nick = pokemonBiosGetNicknamePtr(pokemon);
                msgctrlSetValue(0x32, (s32)nick);
            }
            dispMsg(0xC372);
            result = 0;
        } else {
            waza = pokemonBiosGetPokemonWazaDataId(pokemon, (u16)wazaSlot);
            if (waza > 0x163 && waza < 0x176) {
                dispMsg(0xC374);
                result = 0;
            } else {
                result = itemUse2Pokemon(log, pokemon, fp, item, wazaSlot);
                if (result > 0) {
                    playRecoverSE(item);
                    menuPokemonUpdate();
                }
                msgctrlSetValue(0x4D, (s32)text);
                msgctrlSetValue(0x39, waza);
                getLogMsgField(text, 0x40, log, result, pokemon);
                dispMsg(0x4289);
            }
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(slot);
    if (slot >= 0 && result > 0) {
        *consume = 1;
        return 0;
    }
    return 1;
}

s32 menuUseItemEvolution(u32 item, s32* consume) {
    ITEMUSE2POKEMON_LOG1 log[32];
    Pokemon* pokemon;
    FightPokemon* fp;
    u16 info[2];
    u16 extra;
    s16 result = -1;
    s32 slot = menuPocket2OpenPokemonMenu(item, 1);
    if (slot >= 0) {
        menuPocket2GetTemochiPokemon(slot, &pokemon, &fp);
        if (!pokemonIsDarkPokemon(pokemon)) {
            result = itemUse2Pokemon(log, pokemon, fp, item, 0);
            if (result <= 0) {
                dispMsg(0xC374);
            }
        } else {
            dispMsg(0xC371);
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(slot);
    if (slot >= 0 && result > 0) {
        u16 evo = pokemonEvolutionCheck(pokemon, 1, item, &extra, (POKEMON_EVOLUTION_INFO*)info);
        fadeSet(3, 0.5f);
        fadeCheck(1);
        menuOffScreenSetDisp(0);
        pokemonEvolutionAll(pokemon, evo, extra, (POKEMON_EVOLUTION_INFO*)info, 0, 1, 0, 0);
        menuOffScreenSetDisp(1);
        fadeSet(2, 0.5f);
        fadeCheck(1);
        *consume = 1;
        return 0;
    }
    return 1;
}

s32 menuUseItemCologn(u32 item, s32* consume) {
    Pokemon* pokemon;
    FightPokemon* fp;
    s32 slot = menuPocket2OpenPokemonMenu(item, 1);
    if (slot >= 0) {
        menuPocket2GetTemochiPokemon(slot, &pokemon, &fp);
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(slot);
    if (slot >= 0) {
        menuPocket2AddItemScript(item, 0x05960011);
        *consume = 1;
        return 2;
    }
    return 1;
}

s32 menuUseItemScriptCologn(u32 item, s32 slot) {
    ScriptCologn table[3] = {
        { 0x0201, 0xC3B6, 0xC3B8 },
        { 0x0202, 0xC3BC, 0xC3B9 },
        { 0x0203, 0xC3BD, 0xC3BA },
    };
    Pokemon* pokemon;
    FightPokemon* fp;
    s32 i;
    s32 j;
    u32 voice;
    menuPocket2GetTemochiPokemon(slot, &pokemon, &fp);
    if (!pokemonCheckValid(pokemon)) {
        return 1;
    }
    for (i = 0; i < 3; i++) {
        if ((u16)item == table[i].item) {
            break;
        }
    }
    if (i >= 3) {
        return 1;
    }
    {
        char* nick = pokemonBiosGetNicknamePtr(pokemon);
        msgctrlSetValue(0x32, (s32)nick);
    }
    msgctrlSetValue(0x2D, item);
    dispMsg(table[i].msgA);
    GSsndPlayVolume(0x444, 0, 0xFF, 0);
    if (gamedatasaveGetStatus(0, 9) == 0) {
        for (j = 0; j < 2; j++) {
            GSinputMotorStart(1, 0, 0xFF, 0x15, 0);
            waitTime(1.0f);
        }
        GSinputMotorStart(1, 0, 0xFF, 0x30, 0);
        waitTime(1.6f);
    }
    voice = playPokemonVoice(pokemon);
    while (GSsndGetStatus(voice) == 2) {
        GSthreadSwitch();
    }
    msgctrlSetValue(0x32, (s32)pokemonBiosGetNicknamePtr(pokemon));
    dispMsg(0xC3B7);
    if (pokemonIsJoutaiDataId(pokemon, 0x3E)) {
        pokemonInitJoutaiDataId(pokemon, 0x3E);
        dispMsg(0xC3BE);
    }
    if (pokemonGetDp(pokemon) > 0.0f && pokemon->getPokemonDataId() != 0xF9) {
        pokemonAddDpFormPokemonDpFilterId(pokemon, item, 4);
        msgctrlSetValue(0x32, (s32)pokemonBiosGetNicknamePtr(pokemon));
        dispMsg(table[i].msgB);
        if (!pokemonGetDp(pokemon)) {
            reliveHallInfomationPokemonDP0(pokemon);
        }
    }
    return 1;
}

static f32 unusedZero(f32 x) {
    return x > 0.0f ? x : 0.0f;
}

s32 menuUseItemSkill(u32 item, s32* consume) {
    Pokemon* pokemon;
    FightPokemon* fp;
    s32 learned;
    u8* data = itemDataBiosGetPtr(item);
    u8 machine = itemDataBiosGetWazaMachineNo(data);
    s32 msg;
    u32 hiden;
    s32 yn;
    s32 slot;
    u16 waza = itemDataBiosGetWazaIDByWazaMachineNo(machine);
    GSsndPlayNow(0x23);
    hiden = itemDataBiosGetHidenMachineNo(data);
    if ((u8)hiden != 0xFF) {
        msg = 0xC376;
    } else {
        msg = 0xC375;
    }
    msgctrlSetValue(0x39, waza);
    dispMsg(msg);
    yn = dispMsgYesNo(0xC377);
    if (yn == 1 || yn == 2) {
        return 1;
    }
    slot = menuPocket2OpenPokemonMenu(item, 1);
    if (slot >= 0) {
        menuPocket2GetTemochiPokemon(slot, &pokemon, &fp);
        learned = wazaMachineProc(pokemon, machine);
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(slot);
    if (slot >= 0 && learned != 0) {
        if ((u8)hiden != 0xFF) {
            *consume = 0;
        } else {
            *consume = 1;
        }
        return 0;
    }
    return 1;
}

}

static s32 wazaMachineProc(Pokemon* p, int machineNo) {
    u8 slot;
    int i;
    u32 waza;
    u16 wz;
    s32 learned;
    menuOffScreenSetPriority(0);
    if (pokemonIsDarkPokemon(p)) {
        dispMsg(0xC371);
        return 0;
    }
    i = 0;
    waza = itemDataBiosGetWazaIDByWazaMachineNo(machineNo);
    wz = waza;
    do {
        if (wz == pokemonBiosGetPokemonWazaDataId(p, i)) {
            break;
        }
        i++;
    } while (i < 4);
    if (i < 4) {
        {
            char* nick = pokemonBiosGetNicknamePtr(p);
            msgctrlSetValue(0x32, (s32)nick);
        }
        msgctrlSetValue(0x39, (u16)waza);
        dispMsg(0xC368);
        return 0;
    }
    if (!pokemonDataBiosGetWazaMcn(pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(p)), machineNo)) {
        {
            char* nick = pokemonBiosGetNicknamePtr(p);
            msgctrlSetValue(0x32, (s32)nick);
        }
        msgctrlSetValue(0x39, (u16)waza);
        dispMsg(0xC369);
        return 0;
    }
    learned = evolutionWazaLearn(p, waza, &slot, 1, (s8(*)(Pokemon*, u16, s32))cbForgetWazaSelect, 0);
    if (learned != 0) {
        wazaLean(p, waza, slot);
    }
    return learned;
}

static void wazaLean(Pokemon* p, unsigned short waza, unsigned char slot) {
    pokemonWazaCreate(p, slot, waza);
    u16 id = pokemonGetSoubiItemSoubiDataId(p);
    pokemonGetFriendFormPokemonFriendFilterId(p, id, 4);
}

extern "C" {

s32 menuUseItemFieldNazonomi(u32 item, s32* consume) {
    static s32 origRamSeedParam[2] = { 0, 0 };
    u8 param[8];
    itemParamConvertOrigFormat(param, origRamSeedParam);
    switch (itemParamGetRecoverType(param)) {
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
        return menuUseItemRecovery(item, consume);
    case 1:
        return menuUseItemAlldeathRcv(item, consume);
    case 2:
        return menuUseItemListLVUp(item, consume);
    case 19:
    case 20:
        return menuUseItemWPointUp(item, consume);
    case 21:
        return menuUseItemPPRecovery(item, consume);
    }
    return menuUseItemDummy(item, consume);
}

}

extern "C" {

s32 menuUseItemStatusUp(u32 item, s32* consume) {
    ITEMUSE2POKEMON_LOG1 log[32];
    u16 text[66];
    Pokemon* pokemon;
    FightPokemon* fp;
    s16 result;
    menuPocket2GetTemochiPokemon(menuPocket2GetCurrentTemochiPokemonSlotID(), &pokemon, &fp);
    if (pokemonIsJoutaiDataId(pokemon, 0x3E)) {
        {
            char* nick = pokemonBiosGetNicknamePtr(pokemon);
            msgctrlSetValue(0x32, (s32)nick);
        }
        dispMsg(0xC372);
        return 1;
    }
    result = itemUse2Pokemon(log, pokemon, fp, item, 0);
    if (result > 0) {
        playRecoverSE(item);
        menuPokemonUpdate();
    }
    getLogMsgBattle(text, 0x40, log, result, pokemon);
    msgctrlSetValue(0x4D, (s32)text);
    dispMsg(0x4289);
    if (result > 0) {
        *consume = 1;
        return 0;
    }
    return 1;
}

s32 menuUseItemBattleBall(u32 item, s32* consume) {
    Hero* hero;
    FightTrainer* trainer;
    Pokemon* pokemon;
    FightPokemon* fp;
    s32 empty = 0;
    int stock = (u8)fightFloor_GetStockPokemonNum(0);
    int i;
    s8 boxes;
    u8 kind;
    for (i = 0; i < 6; i++) {
        menuPocket2GetTemochiPokemon(i, &pokemon, &fp);
        if (!pokemonCheckValid(pokemon)) {
            empty++;
        }
    }
    boxes = pcboxGetNbPokemonBox();
    for (i = 0; i < boxes;) {
        s8 n = pcboxGetPokemonBoxNbEmptySlot(0, i);
        i++;
        empty += n;
    }
    if (empty < stock + 1) {
        dispMsg(0x4F8B);
        return 1;
    }
    menuPocket2GetHero(&hero, &trainer);
    kind = fightFloor_GetFightKind(fightFloorGetNowPtr());
    if (hero->getHeroStyle() != 2 && kind != 0xC && kind != 0xD) {
        dispMsg(0x5000);
        return 1;
    }
    if (fightTrainerIsSelectedItemBall(trainer)) {
        dispMsg(0xC378);
        return 1;
    }
    *consume = 0;
    return 0;
}

void menuUseItemBattleNazonomi(u32 item, s32* consume) {
    static s32 origRamSeedParam[2] = { 0, 0 };
    u8 param[8];
    itemParamConvertOrigFormat(param, origRamSeedParam);
    s32 type = itemParamGetRecoverType(param);
    switch (type) {
    case 0:
        menuUseItemStatusUp(item, consume);
        return;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        menuUseItemRecovery(item, consume);
        return;
    case 21:
        menuUseItemPPRecovery(item, consume);
        return;
    }
    menuUseItemDummy(item, consume);
}

s32 menuUseItemEventNotConsum(u32 item, s32* consume) {
    s32 i;
    *consume = 0;
    for (i = 0; i < menuPocketWork.count; i++) {
        if (item == menuPocketWork.e[i].item) {
            return 2;
        }
    }
    dispMsg(0xC373);
    return 1;
}

CraneMemo item_crane_memo[5] = {
    { 0x020B, 0, 0x3C20 }, { 0x020C, 1, 0x3C21 }, { 0x020D, 2, 0x3C22 }, { 0x020E, 3, 0x3C23 }, { 0x020F, 4, 0x3C24 },
};
u32 item_crane_memo_number = 5;

s32 menuUseItemEventCraneMemo(u32 item, s32* consume) {
    u32 i;
    CraneMemo* m = item_crane_memo;
    *consume = 0;
    for (i = 0; i < item_crane_memo_number; i++, m++) {
        if (m->item == item) {
            dispMsg(m->msg);
            return 2;
        }
    }
    dispMsg(0xC373);
    return 1;
}

s32 menuUseItemEventMirraboradar(u32 item, s32* consume) {
    underTakerBios ub;
    u32 msg = 1;
    *consume = 0;
    if (GSflagGet(0x8ED)) {
        msg = 0x3C31;
    } else if (GSflagGet(0x8EE)) {
        msg = 0x3C32;
    } else {
        u16 n = GSflagGet(undertakerdata->flagId);
        if (n <= 2) {
            dispMsg(0x3C1C);
        } else if (n <= 5) {
            dispMsg(0x3C1D);
        } else if (n <= 8) {
            dispMsg(0x3C1E);
        } else {
            msg = ub.getPlaceMsg();
        }
    }
    if (msg != 1) {
        char* str = GSmsgGetGSchar(msg);
        msgctrlSetValue(0x4D, (s32)str);
        dispMsg(0x3C1F);
    }
    return 2;
}

s32 menuUseItemEventUsohachiPhoto(u32 item, s32* consume) {
    *consume = 0;
    menuScriptUsohachi2();
    return 2;
}

}

static void dispMsg(unsigned long msg) {
    switch (msg) {
    case 0xC368:
    case 0xC369:
    case 0xC371:
    case 0xC372:
        GSsndPlayNow(0x13);
        break;
    }
    if (windowSearchID(0x4C) == 0) {
        winMsgOpen(2, msg, 1, 0);
    } else {
        winMsgOpen(2, msg, 0, 0);
        do {
            menuOffScreenSetPriority(0);
            GSthreadSwitch();
        } while (winMsgCheck() != 0);
    }
    winMsgClose(1);
}

static s32 dispMsgYesNo(unsigned long msg) {
    s32 r;
    winMsgOpen(2, msg, 1, 0);
    r = menuSubOpenYesNo(0, -1, -1, 0);
    winMsgClose(1);
    switch (r) {
    case 0:
        return 0;
    case 1:
        return 1;
    }
    return 2;
}

static void getLogMsgField(u16* out, int idx, ITEMUSE2POKEMON_LOG1* log, short n, Pokemon* p) {
    LogMsgField table[21] = {
        { 9, 0xC353, 0 },   { 10, 0xC353, 0 },  { 11, 0xC354, 1 },  { 12, 0xC354, 1 },  { 13, 0xC354, 1 },
        { 14, 0xC355, 2 },  { 15, 0xC356, 3 },  { 16, 0xC357, 4 },  { 17, 0xC381, 5 },  { 0, 0xC358, 6 },
        { 22, 0xC352, -1 }, { 21, 0xC351, 7 },  { 20, 0xC35A, -1 }, { 19, 0xC35B, -1 }, { 28, 0xC35C, -1 },
        { 27, 0xC35D, -1 }, { 26, 0xC35E, -1 }, { 25, 0xC35F, -1 }, { 18, 0xC360, -1 }, { 29, 0xC360, -1 },
        { 23, 0xC361, -1 },
    };
    int j2;
    s32 kind;
    int j;
    int i;
    s16 a;
    s16 b;
    s32 link;
    s32 msg;
    if (n <= 0) {
        GSmsgMakeGScharStr(out, idx + 1, 0xC374);
        return;
    }
    for (i = 0; i < 21; i++) {
        kind = table[i].kind;
        for (j = 0; j < n; j++) {
            if (kind == log[j].kind) {
                break;
            }
        }
        if (j >= n) {
            continue;
        }
        break;
    }
    if (i >= 21) {
        GSmsgMakeGScharStr(out, idx + 1, 0xC374);
        return;
    }
    link = table[i].link;
    msg = table[i].msg;
    a = log[j].a;
    b = log[j].b;
    if (link >= 0) {
        int i2 = i + 1;
        for (; i2 < 21; i2++) {
            if (table[i2].link >= 0 && link != table[i2].link) {
                for (j2 = 0; j2 < n; j2++) {
                    if (table[i2].kind == log[j2].kind) {
                        break;
                    }
                }
                if (j2 < n) {
                    break;
                }
            }
        }
        if (i2 < 21) {
            msg = 0xC359;
        }
    }
    {
        char* nick = pokemonBiosGetNicknamePtr(p);
        msgctrlSetValue(0x32, (s32)nick);
    }
    msgctrlSetValue(0x2F, a);
    msgctrlSetValue(0x30, b);
    GSmsgMakeGScharStr(out, idx + 1, msg);
}

static void getLogMsgBattle(u16* out, int idx, ITEMUSE2POKEMON_LOG1* log, short n, Pokemon* p) {
    LogMsg table[7] = {
        { 7, 0xC362 }, { 5, 0xC363 }, { 6, 0xC364 }, { 3, 0xC365 }, { 4, 0xC366 }, { 1, 0xC370 }, { 2, 0xC36F },
    };
    int j;
    int i;
    s16 a;
    s16 b;
    s32 msg;
    if (n <= 0) {
        GSmsgMakeGScharStr(out, idx + 1, 0xC374);
        return;
    }
    for (i = 0; i < 7; i++) {
        s32 kind = table[i].kind;
        for (j = 0; j < n; j++) {
            if (kind == log[j].kind) {
                break;
            }
        }
        if (j >= n) {
            continue;
        }
        break;
    }
    if (i >= 7) {
        GSmsgMakeGScharStr(out, idx + 1, 0xC374);
        return;
    }
    msg = table[i].msg;
    a = log[j].a;
    b = log[j].b;
    {
        char* nick = pokemonBiosGetNicknamePtr(p);
        msgctrlSetValue(0x32, (s32)nick);
    }
    msgctrlSetValue(0x2F, a);
    msgctrlSetValue(0x30, b);
    GSmsgMakeGScharStr(out, idx + 1, msg);
}

static void playRecoverSE(unsigned long item) {
    u16 table[5] = { 0x27, 0x28, 0x29, 0x2A, 0x2B };
    int i;
    for (i = 0; i < 5; i++) {
        if (item == table[i]) {
            break;
        }
    }
    u32 snd;
    if (i < 5) {
        snd = 0x20;
    } else {
        snd = 0x1F;
    }
    GSsndPlayNow(snd);
}

static void waitTime(f32 t) {
    s32 n = 0;
    while (n < (s32)(60.0f * t)) {
        GSthreadSwitch();
        n = (s32)((f32)n + GSgfxVideoGetLastRenderTime());
    }
}

static u32 playPokemonVoice(Pokemon* p) {
    PokemonData* d = getPokemonData(p);
    int v;
    if (d == 0) {
        return 0;
    }
    v = (u16)pokemonDataBiosGetVoice(d);
    GSsndPlayNow(v);
    return v;
}

static PokemonData* getPokemonData(Pokemon* p) {
    PokemonData* r;
    if (p == 0) {
        return 0;
    }
    if (!pokemonCheckValid(p)) {
        return 0;
    }
    r = pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(p));
    return r;
}
