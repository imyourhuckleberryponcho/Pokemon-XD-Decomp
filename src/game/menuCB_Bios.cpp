// STATUS (rough draft, rd_cb): 41/41 functions, 27 exact, byte-weighted ~92.7%, default flags + peephole off;
// LAYOUT/CONST/CALLS/DATA all OK. Candidate for linking after: menuCBBios_InitContext 52% (loop/register shape),
// menuCB_RULE_INIT 94%, InitContextAtFirst 93%, InitVersusTrainer 92% (switch tree), RuleConstRuleSet 98%.
// CBRule is a pack(1) struct (misaligned s32 members): struct assignment gives the member-wise copies of the target.
#include <dolphin/types.h>

// Menu callbacks were built without the peephole optimizer.
#pragma peephole off

struct Hero;
struct Pokemon;

#pragma pack(push, 1)
// one tool-battle rule (0x90 bytes, misaligned s32 members)
struct CBRule {
    s16 a0, a2, a4, a6;
    s32 a8;
    u8 aC, aD, aE, aF, a10, a11, a12, a13;
    s16 a14, a16;
    u8 a18, a19;
    s16 a1A, a1C;
    s32 e[10];
    u16 a46;
    s32 a48, a4C;
    u16 a50;
    s32 f[15];
    u16 a8E;
};
#pragma pack(pop)

// tool battle save data: 6 rules, then a flag byte
struct _TOOL_SAVEDATA {
    CBRule rule[6];
    s8 working; // 0x360 (padded)
    u8 pad361[3];
};

struct CBTrainer {
    u16 dataId;       // 0x00
    u16 playerId;     // 0x02
    s32 homePlace;    // 0x04
    u8 pad8[0x1C];
    s32 controllerId; // 0x24
    s32 versusId;     // 0x28
    u8 hero[0x978];   // 0x2C
    u8 heroOrg[0x978]; // 0x9A4
    u8 padLast[4];
};

struct _MENUCBWORK {
    u8 pad0[4];
    s32 mode;        // 0x04
    s32 state;       // 0x08
    s32 ruleType;    // 0x0C
    u8 pad10[4];
    s32 f14;         // 0x14
    CBTrainer trainer[4];    // 0x18
    CBTrainer trainerOrg[4]; // 0x4C98
    CBRule rule[6];  // 0x9918
    u8 pad9C78[0xB0E0 - 0x9C78];
    s32 controller2P; // 0xB0E0
    u8 padB0E4[0xB5F4 - 0xB0E4];
};

extern "C" {
extern _MENUCBWORK _CB;
extern _MENUCBWORK* pGCB;
extern u32 itemtoolbattle_number;

u16* GSmsgGetGSchar(u32 msg);
void fightTrainerCreateFightTrainerDataIdToHero(u16 id, s32 allowNoAi, Hero* hero, u16 encountId);
void heroBiosCopy(void* dst, void* src);
u8 heroBiosGetHomePlace(u16 id);
Pokemon* heroBiosGetPokemonPtr(Hero* hero, u16 index);
u8 heroBiosGetSexDataId(u16 id);
void heroBiosSetHizukiFlag(void* hero, u8 v);
void* memcpy(void* dst, const void* src, u32 n);
void* memset(void* dst, int v, u32 n);
CBRule* menuCBRule_ConstantRule(s32 i);
CBRule* menuCBRule_ConstantRule2();
u8 menuCBRule_IsBlankPokemon(Pokemon* p);
s32 menuCBRule_ParticipationPokemonMax();
u16 menuCBRule_RegulationItemID(u32 i);
void menuCB_InitMenu(s32 id);
CBRule* menuCB_OreRule();
void pokemonAllKaihuku(Pokemon* p);
void* savedataGetStatus(void* save, s32 kind);

static const s32 staControlerMap[4] = { 1, 2, 3, 4 };
u8 stbCB_Lock;
s32 toolbattle_mode_flag;

void menuCBBios_UnlockContext(void);
u8 menuCBBios_ContextIsLocked(_MENUCBWORK*);
void menuCBBios_ClearTrainer(CBTrainer* t);
void menuCBBios_InitTrainer(CBTrainer* t, u16 id);
s32 menuCBBios_FightTrainerDataIDToHomePlace(u16 id);
s32 menuCBBios_PortIDtoControlerID(u16 port);
s32 menuCBBios_ControlerIDtoPortID(s32 id);
CBRule* menuCBBios_GetRule(s32 i);
void menuCBBios_InitTrainerFromHero(CBTrainer* t, u16 id, u16 unused);
void menuCBBios_InitTrainerFromDataID(CBTrainer* t, u16 id, s32 allowNoAi);
void menuCBBios_CopyTrainer(CBTrainer* dst, CBTrainer* src);
s32 menuCBBios_CurrentRuleType(void);
void menuCBTrainerBios_SetControlerID(CBTrainer* t, s32 id);
void menuCBBios_RuleConstRuleSet(void);
}

static void _menuCBBios_RecoverAllPokemons(Hero* hero);
void menuCBBios_InitContextAtFirst(_MENUCBWORK* cb, _TOOL_SAVEDATA* save);

extern "C" {

void menuCB_SetToolBattleModeFlag(s32 v) {
    toolbattle_mode_flag = v;
}

s32 menuCB_GetToolBattleModeFlag(void) {
    return toolbattle_mode_flag;
}

s32 menuCB_GetBattleController2P(void) {
    return _CB.controller2P;
}

void* menuCB_RuleTitleNameGet(s32 i) {
    return &_CB.rule[i].e[0];
}

u16 menuCBTrainerBios_GetPlayerID(CBTrainer* t) {
    return t->playerId;
}

void menuCBTrainerBios_SetHomePlace(CBTrainer* t, s32 v) {
    t->homePlace = v;
}

s32 menuCBTrainerBios_GetHomePlace(CBTrainer* t) {
    return t->homePlace;
}

void menuCBBios_CopyTrainer(CBTrainer* dst, CBTrainer* src) {
    memcpy(dst, src, 0x1320);
}

s32 menuCBTrainerBios_GetControlerID(CBTrainer* t) {
    return t->controllerId;
}

void menuCBTrainerBios_SetControlerID(CBTrainer* t, s32 v) {
    t->controllerId = v;
}

void menuCBBios_InitVersusTrainer(CBTrainer* t, u16 id) {
    u16 trainerId = 0x1388;
    u8 place = heroBiosGetHomePlace(id);
    switch (place) {
    case 0:
        trainerId = 0x1388;
        break;
    case 1:
        switch (heroBiosGetSexDataId(id)) {
        case 0:
            trainerId = 0x1389;
            break;
        case 1:
            trainerId = 0x138A;
            break;
        }
        break;
    case 2:
        switch (heroBiosGetSexDataId(id)) {
        case 0:
            trainerId = 0x138B;
            break;
        case 1:
            trainerId = 0x138C;
            break;
        }
        break;
    case 3:
        switch (heroBiosGetSexDataId(id)) {
        case 0:
            trainerId = 0x138D;
            break;
        case 1:
            trainerId = 0x138E;
            break;
        }
        break;
    }
    menuCBBios_InitTrainerFromHero(t, id, trainerId);
}

void menuCBBios_InitTrainerFromHero(CBTrainer* t, u16 id, u16 unused) {
    u8 hero[0x978];
    heroBiosCopy(hero, 0);
    heroBiosSetHizukiFlag(hero, 0);
    _menuCBBios_RecoverAllPokemons((Hero*)hero);
    menuCBBios_ClearTrainer(t);
    heroBiosCopy(t->hero, hero);
    heroBiosCopy(t->heroOrg, hero);
    t->dataId = id;
    t->homePlace = menuCBBios_FightTrainerDataIDToHomePlace(id);
}

void menuCBBios_InitTrainerFromDataID(CBTrainer* t, u16 id, s32 allowNoAi) {
    u8 hero[0x978];
    heroBiosCopy(hero, t->heroOrg);
    fightTrainerCreateFightTrainerDataIdToHero(id, menuCBBios_PortIDtoControlerID(0), (Hero*)hero, allowNoAi);
    heroBiosSetHizukiFlag(hero, 0);
    _menuCBBios_RecoverAllPokemons((Hero*)hero);
    menuCBBios_ClearTrainer(t);
    heroBiosCopy(t->hero, hero);
    heroBiosCopy(t->heroOrg, hero);
    t->dataId = id;
    t->homePlace = menuCBBios_FightTrainerDataIDToHomePlace(id);
}

void menuCBBios_ClearTrainer(CBTrainer* t) {
    menuCBBios_InitTrainer(t, menuCBTrainerBios_GetPlayerID(t));
}

void menuCBBios_InitTrainer(CBTrainer* t, u16 id) {
    memset(t, 0, 0x1320);
    t->playerId = id;
}

s32 menuCBBios_FightTrainerDataIDToHomePlace(u16 id) {
    if (id != 0x1388) {
        if (id < 0x1388) {
            if (id < 6) {
                if (id < 1) return 0;
                return 1;
            }
            return 0;
        }
        if (id < 0x138D) {
            if (id < 0x138B) return 1;
            return 2;
        }
        if (id < 0x138F) return 3;
        return 0;
    }
    return 0;
}

CBTrainer* menuCBBios_GetTrainerFromVersusBattleID(s32 id) {
    if (_CB.state != 2 && _CB.state < 2) {
        if (_CB.state >= 0) {
            if (id >= 0 && id <= 1) return &_CB.trainer[id];
            return 0;
        }
    }
    for (s32 i = 0; i < 4; i++) {
        if (id == _CB.trainer[i].versusId) return &_CB.trainer[i];
    }
    return 0;
}

s32 menuCBBios_GetToolBattleTrainerKind(void) {
    return 0;
}

s32 menuCBBios_GetRegisteredHero(void) {
    return 0;
}

CBTrainer* menuCBBios_GetTrainer(void) {
    s32 port = menuCBBios_ControlerIDtoPortID(0);
    if (port < 0) return 0;
    return &_CB.trainer[port];
}

CBTrainer* menuCBBios_GetTrainerOrgImmediately(s32 i) {
    if (i < 0 || i >= 4) return 0;
    return &_CB.trainerOrg[i];
}

CBTrainer* menuCBBios_GetTrainerImmediately(s32 i) {
    if (i < 0 || i >= 4) return 0;
    return &_CB.trainer[i];
}

void* menuCBBios_GetHeroImmediately(s32 i) {
    if (i < 0 || (u32)i >= 4) return 0;
    return _CB.trainer[i].hero;
}

}

static void _menuCBBios_RecoverAllPokemons(Hero* hero) {
    for (u16 i = 0; i < 6; i++) {
        Pokemon* p = heroBiosGetPokemonPtr(hero, i);
        if (menuCBRule_IsBlankPokemon(p) == 0) pokemonAllKaihuku(p);
    }
}

extern "C" {

s32 menuCBBios_ControlerIDtoPortID(s32 id) {
    if (id == staControlerMap[0]) return 0;
    if (id == staControlerMap[1]) return 1;
    if (id == staControlerMap[2]) return 2;
    if (id == staControlerMap[3]) return 3;
    return -1;
}

s32 menuCBBios_PortIDtoControlerID(u16 port) {
    return staControlerMap[port];
}

s32 menuCBBios_ParticipationPokemonMax(void) {
    return menuCBRule_ParticipationPokemonMax();
}

s32 menuCBBios_CurrentRuleType(void) {
    return _CB.ruleType;
}

CBRule* menuCBBios_CurrentRule(void) {
    CBRule* ore = menuCB_OreRule();
    if (ore != 0) return ore;
    menuCBBios_CurrentRuleType();
    CBRule* constant = menuCBRule_ConstantRule2();
    s32 type = menuCBBios_CurrentRuleType();
    if (type < 3) {
        if (type >= 0) {
            if (constant != 0) return constant;
        }
    }
    return menuCBBios_GetRule(menuCBBios_CurrentRuleType());
}

CBRule* menuCBBios_GetRule(s32 i) {
    if (i < 0 || (u32)i >= 6) return 0;
    return &_CB.rule[i];
}

void menuCBBios_RuleConstRuleSet(void) {
    _TOOL_SAVEDATA* save = (_TOOL_SAVEDATA*)savedataGetStatus(0, 0xE);
    save->rule[0] = *menuCBRule_ConstantRule(0);
    save->rule[1] = *menuCBRule_ConstantRule(1);
    save->rule[2] = *menuCBRule_ConstantRule(2);
    save->rule[0].a50 = 0x9124;
    save->rule[1].a50 = 0xA2D4;
    save->rule[2].a50 = 0xB51C;
}

void menuCBBios_RuleEditSaveON(u8 on) {
    _TOOL_SAVEDATA* save = (_TOOL_SAVEDATA*)savedataGetStatus(0, 0xE);
    if (on == 1) {
        save->rule[0].a50 = 0x9124;
        save->rule[1].a50 = 0xA2D4;
        save->rule[2].a50 = 0xB51C;
        save->rule[3].a50 = 0x47FD;
        save->rule[4].a50 = 0x7422;
        save->rule[5].a50 = 0x5633;
        return;
    }
    save->rule[5].a50 = 0;
    save->rule[4].a50 = 0;
    save->rule[3].a50 = 0;
    save->rule[2].a50 = 0;
    save->rule[1].a50 = 0;
    save->rule[0].a50 = 0;
}

void menuCBBios_CurrentlyWorkingToolBattleSet(s8 v) {
    ((_TOOL_SAVEDATA*)savedataGetStatus(0, 0xE))->working = v;
}

u8 menuCBBios_CurrentlyWorkingToolBattle(void) {
    _TOOL_SAVEDATA* save = (_TOOL_SAVEDATA*)savedataGetStatus(0, 0xE);
    if (save == 0) return 0;
    return save->working;
}

_MENUCBWORK* menuCBBios_WorkContext(void) {
    return &_CB;
}

void menuCBBios_InitContext(_MENUCBWORK* cb) {
    static const u16 sta[4] = { 1, 2, 3, 4 };
    pGCB = &_CB;
    if (menuCBBios_ContextIsLocked(&_CB) == 0) {
        for (u16 i = 0; i < 4; i++) {
            CBTrainer* t = &cb->trainer[i];
            menuCBBios_InitTrainerFromDataID(t, sta[i], 0);
            menuCBTrainerBios_SetControlerID(t, menuCBBios_PortIDtoControlerID(i));
            t->playerId = i;
            menuCBBios_CopyTrainer(&cb->trainerOrg[i], t);
        }
        if (cb->mode != 1) {
            menuCB_InitMenu(0xA9);
            cb->f14 = 4;
        } else {
            menuCB_InitMenu(0xA4);
            cb->f14 = 0;
        }
    }
    menuCBBios_UnlockContext();
}

// fill one 3-rule name block (7 entries of 3 u16 each) from a message
static inline void ruleNameFill(u16* src, u16* dst) {
    for (int k = 0; k < 7; k++, dst += 3) {
        if (src != 0) {
            if (*src == 0xFFFF) src += 4;
            dst[0] = *src;
            if (*src != 0) src += 2;
        } else {
            dst[0] = 0;
        }
        if (src != 0) {
            if (*src == 0xFFFF) src += 4;
            dst[1] = *src;
            if (*src != 0) src += 2;
        } else {
            dst[1] = 0;
        }
        if (src != 0) {
            if (*src == 0xFFFF) src += 4;
            dst[2] = *src;
            if (*src != 0) src += 2;
        } else {
            dst[2] = 0;
        }
    }
}

void menuCB_RULE_INIT(_TOOL_SAVEDATA* save) {
    if (save->rule[0].a50 == 0x9124 && save->rule[1].a50 == 0xA2D4 && save->rule[2].a50 == 0xB51C &&
        save->rule[3].a50 == 0x47FD && save->rule[4].a50 == 0x7422 && save->rule[5].a50 == 0x5633) {
        menuCBBios_RuleConstRuleSet();
        return;
    }
    memset(save, 0, 0x364);
    save->rule[0] = *menuCBRule_ConstantRule(0);
    save->rule[1] = *menuCBRule_ConstantRule(1);
    save->rule[2] = *menuCBRule_ConstantRule(2);
    save->rule[3] = *menuCBRule_ConstantRule(2);
    save->rule[4] = *menuCBRule_ConstantRule(2);
    save->rule[5] = *menuCBRule_ConstantRule(2);
    save->rule[3].a1C = 0;
    save->rule[4].a1C = 0;
    save->rule[5].a1C = 0;
    save->rule[3].a1A = 4;
    save->rule[4].a1A = 4;
    save->rule[5].a1A = 4;
    for (u32 i = 0; i < itemtoolbattle_number; i++) {
        if (menuCBRule_RegulationItemID(i) == 0xBF) {
            ((u8*)save)[i + 0xE2] = 1;
            ((u8*)save)[i + 0x172] = 1;
            ((u8*)save)[i + 0x202] = 1;
            ((u8*)save)[i + 0x292] = 1;
            ((u8*)save)[i + 0x322] = 1;
        }
    }
    ruleNameFill(GSmsgGetGSchar(0x438A), (u16*)((u8*)save + 0x1CE));
    ruleNameFill(GSmsgGetGSchar(0x438B), (u16*)((u8*)save + 0x25E));
    ruleNameFill(GSmsgGetGSchar(0x438C), (u16*)((u8*)save + 0x2EE));
    menuCBBios_InitContextAtFirst(&_CB, save);
    save->working = 0;
}

}

void menuCBBios_InitContextAtFirst(_MENUCBWORK* cb, _TOOL_SAVEDATA* save) {
    menuCBBios_UnlockContext();
    memset(cb, 0, 0xB5F4);
    cb->rule[0] = *menuCBRule_ConstantRule(0);
    cb->rule[1] = *menuCBRule_ConstantRule(1);
    cb->rule[2] = *menuCBRule_ConstantRule(2);
    cb->rule[3] = *menuCBRule_ConstantRule(2);
    cb->rule[4] = *menuCBRule_ConstantRule(2);
    cb->rule[5] = *menuCBRule_ConstantRule(2);
    cb->rule[3].a1C = 0;
    cb->rule[4].a1C = 0;
    cb->rule[5].a1C = 0;
    cb->rule[3].a1A = 4;
    cb->rule[4].a1A = 4;
    cb->rule[5].a1A = 4;
    for (u32 i = 0; i < itemtoolbattle_number; i++) {
        if (menuCBRule_RegulationItemID(i) == 0xBF) {
            ((u8*)cb)[i + 0x99FA] = 1;
            ((u8*)cb)[i + 0x9A8A] = 1;
            ((u8*)cb)[i + 0x9B1A] = 1;
            ((u8*)cb)[i + 0x9BAA] = 1;
            ((u8*)cb)[i + 0x9C3A] = 1;
        }
    }
    memcpy((u8*)save + 0x1CE, (u8*)menuCB_RuleTitleNameGet(3), 0x2A);
    memcpy((u8*)save + 0x25E, (u8*)menuCB_RuleTitleNameGet(4), 0x2A);
    memcpy((u8*)save + 0x2EE, (u8*)menuCB_RuleTitleNameGet(5), 0x2A);
}

extern "C" {

u8 menuCBBios_ContextIsLocked(_MENUCBWORK*) {
    return stbCB_Lock;
}

void menuCBBios_UnlockContext(void) {
    stbCB_Lock = 0;
}

void menuCBBios_LockContext(void) {
    stbCB_Lock = 1;
}

}
