// STATUS: all 40 functions written; see fcheck for the per-function state.
// Tool-battle rule checks (menuCBRule_*) for the Colosseum-style menus.
#include <dolphin/types.h>

// Menu callbacks were built without the peephole optimizer.
#pragma peephole off

struct Hero;
struct Pokemon {
    u8 data[0xC4];
};
struct WazaData;

#pragma pack(push, 1)
// one tool-battle rule (0x90 bytes, misaligned s32 members)
struct CBRule {
    s16 a0, a2, a4, a6;
    s32 a8;
    u8 aC, aD, aE, aF, a10, a11, a12, a13;
    s16 a14, a16;
    u8 a18, a19;
    s16 a1A, a1C;
    u16 name[7][3];
    struct { s32 a, b; } a48;
    u16 a50;
    u8 f[0x3C];
    u16 a8E;
};
#pragma pack(pop)

// per-slot error flags (4 bytes), bit n = field an / bn
struct ErrEntry {
    u8 a7 : 1, a6 : 1, a5 : 1, a4 : 1, a3 : 1, a2 : 1, a1 : 1, a0 : 1;
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
    u8 pad[2];
};

struct _MENUCBWORK {
    u8 pad0[0xC];
    s32 ruleType;           // 0x0C
    u8 pad10[0x9918 - 0x10];
    CBRule rule[6];         // 0x9918
    u8 pad9C78[4];
    u8 pad9C7C[8];
    ErrEntry err[4][6];     // 0x9C84
    u8 padrest[0xB5F4 - 0x9CE4];
};

extern "C" {
extern _MENUCBWORK _CB;
extern u16 itemtoolbattle[];
extern u32 itemtoolbattle_number;
extern u16* legendPokemonData;
extern u32* legendPokemonData_number;

u16* GSmsgGetGSchar(u32 key);
Pokemon* heroBiosGetPokemonPtr(Hero* hero, u16 index);
bool itemDataCheckValid(u16 id);
int memcmp(const void* a, const void* b, u32 n);
void* memcpy(void* dst, const void* src, u32 n);
void* memset(void* dst, int v, u32 n);
CBRule* menuCBBios_CurrentRule(void);
u8 menuCBBios_CurrentlyWorkingToolBattle(void);
void pokemonBiosCopy(Pokemon* dst, const Pokemon* src);
u8 pokemonBiosGetEventGetFlag(Pokemon* p);
u16 pokemonBiosGetItemDataId(Pokemon* p);
u8 pokemonBiosGetLevel(Pokemon* p);
u32 pokemonBiosGetMaxHp(Pokemon* p);
u16 pokemonBiosGetMaxHpEffort(Pokemon* p);
u32 pokemonBiosGetNimbleness(Pokemon* p);
u16 pokemonBiosGetNimblenessEffort(Pokemon* p);
u32 pokemonBiosGetPhyAtk(Pokemon* p);
u16 pokemonBiosGetPhyAtkEffort(Pokemon* p);
u32 pokemonBiosGetPhyDef(Pokemon* p);
u16 pokemonBiosGetPhyDefEffort(Pokemon* p);
u16 pokemonBiosGetPokemonDataId(Pokemon* p);
u32 pokemonBiosGetSpeAtk(Pokemon* p);
u16 pokemonBiosGetSpeAtkEffort(Pokemon* p);
u32 pokemonBiosGetSpeDef(Pokemon* p);
u16 pokemonBiosGetSpeDefEffort(Pokemon* p);
u8 pokemonBiosGetTamagoFlag(Pokemon* p);
bool pokemonCheckValid(Pokemon* p);
int pokemonGetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index);
u8 pokemonIsDarkPokemon(Pokemon* p);
void pokemonResetBasisStatus(Pokemon* p);
void toolBattleRuleErrorFlagClear(s32 player, u32 idx);
WazaData* wazaDataBiosGetPtr(u16 id);

bool menuCBRule_CheckTrainerRegulation(Hero* hero, CBRule* rule, s32 kind);
bool menuCBRule_CheckTrainerRegulationAt(Hero* hero, Pokemon* p, CBRule* rule, s32 kind);
bool menuCBRule_CheckPokemonRegulation(Pokemon* p, CBRule* rule, s32 kind);
bool menuCBRule_CheckPokemonError(Pokemon* p, s32 kind);
bool menuCBRule_CheckLegendPokemon(Pokemon* p, CBRule* rule);
bool menuCBRule_CheckPokemonEventFlag(Pokemon* p);
bool menuCBRule_CheckTrainerErrorAll(Hero* hero);
bool menuCBRule_CheckTrainerError(Hero* hero, s32 kind);
bool menuCBRule_CheckPokemonErrorAll(Pokemon* p);
bool menuCBRule_CheckTrainerRegulationAll(Hero* hero, CBRule* rule);
bool menuCBRule_CheckPokemonRegulationAll(Pokemon* p, CBRule* rule);
bool menuCBRule_CheckErrorAll(Hero* hero);
bool menuCBRule_CheckRegulationAll(Hero* hero, CBRule* rule);
bool menuCBRule_IsBlankPokemon(Pokemon* p);
bool menuCBRule_CheckValidItem(u16 id);
bool menuCBRule_CheckRegulationItem(u16 id);
u16 menuCBRule_RegulationItemID(s32 i);
u32 menuCBRule_RegulationItems(void);
CBRule* menuCBRule_ConstantRule(s32 i);
}

static bool _menuCBRule_IsTamagoPokemon(Pokemon* p);

static const CBRule oreRule = {
    1, 100, 600, 1, 0,
    1, 1, 0, 0, 1, 1, 0, 1,
    -60, -20,
    1, 1, 6, 1,
    {0}, {0, 0}, 0, {0}, 0,
};

static const CBRule staRule[3] = {
    { 1, 100, 600, 1, 0,
      1, 1, 1, 1, 1, 0, 1, 1,
      -60, -20,
      1, 1, 6, 1,
      {0}, {0, 0}, 0, {0}, 0 },
    { 1, 50, 300, 6, 2,
      0, 0, 0, 0, 1, 1, 0, 1,
      -60, -20,
      1, 1, 6, 1,
      {0}, {0, 0}, 0, {0}, 0 },
    { 1, 100, 600, 6, 2,
      0, 0, 0, 0, 1, 1, 0, 1,
      -60, -20,
      1, 1, 6, 1,
      {0}, {0, 0}, 0, {0}, 0 },
};

static CBRule ruleTempBuff;

extern "C" {

void menuCBRule_ErrorFlagSetOkPushTiming(Hero* hero) {
    CBRule* rule = menuCBBios_CurrentRule();
    u32 i;
    for (i = 0; i < 6; i++) {
        _CB.err[0][i].b2 = menuCBRule_CheckTrainerRegulation(hero, rule, 3) == 0;
    }
}

void menuCBRule_ErrorFlagSetItemGetTiming(Hero* hero, Pokemon* p, u32 idx) {
    CBRule* rule = menuCBBios_CurrentRule();
    pokemonBiosGetItemDataId(p);
    if (!menuCBRule_CheckPokemonRegulation(p, rule, 2)) {
        switch (rule->a8) {
        case 0:
            break;
        case 1:
            _CB.err[0][idx].b7 = 1;
            break;
        case 2:
            _CB.err[0][idx].b6 = 1;
            break;
        }
    }
    _CB.err[0][idx].b4 = menuCBRule_CheckPokemonError(p, 3) == 0;
    _CB.err[0][idx].b5 = menuCBRule_CheckTrainerRegulationAt(hero, p, rule, 2) == 0;
}

void menuCBRule_ErrorFlagSetPokemonGetTiming(Hero* hero, Pokemon* p, u32 idx) {
    CBRule* rule = menuCBBios_CurrentRule();
    _CB.err[0][idx].a5 = menuCBRule_CheckPokemonRegulation(p, rule, 0) == 0;
    _CB.err[0][idx].a4 = menuCBRule_CheckPokemonRegulation(p, rule, 1) == 0;
    _CB.err[0][idx].a0 = menuCBRule_CheckPokemonError(p, 0) == 0;
    _CB.err[0][idx].a3 = menuCBRule_CheckPokemonError(p, 1) == 0;
    _CB.err[0][idx].a2 = menuCBRule_CheckPokemonError(p, 2) == 0;
    _CB.err[0][idx].b1 = menuCBRule_CheckPokemonError(p, 5) == 0;
    _CB.err[0][idx].a1 = menuCBRule_CheckPokemonError(p, 4) == 0;
    _CB.err[0][idx].b3 = menuCBRule_CheckTrainerRegulation(hero, rule, 0) == 0;
    _CB.err[0][idx].a7 = menuCBRule_CheckLegendPokemon(p, rule) == 0;
    _CB.err[0][idx].a6 = menuCBRule_CheckTrainerRegulationAt(hero, p, rule, 1) == 0;
}

bool menuCBRule_CheckLegendPokemon(Pokemon* p, CBRule* rule) {
    if (rule->a18 == 1) {
        return 1;
    }
    u16 id = pokemonBiosGetPokemonDataId(p);
    u32 n = *legendPokemonData_number;
    u16* t = legendPokemonData;
    for (u32 i = 0; i < n; i++, t++) {
        if (id == *t) {
            return 0;
        }
    }
    return 1;
}

void menuCBRule_ErrorFlagSet(Hero* hero, s32 player) {
    CBRule* rule = menuCBBios_CurrentRule();
    u32 i;
    for (i = 0; i < 6; i++) {
        Pokemon* p = heroBiosGetPokemonPtr(hero, i);
        pokemonBiosGetItemDataId(p);
        toolBattleRuleErrorFlagClear(player, i);
        _CB.err[player][i].a5 = menuCBRule_CheckPokemonRegulation(p, rule, 0) == 0;
        _CB.err[player][i].a4 = menuCBRule_CheckPokemonRegulation(p, rule, 1) == 0;
        if (!menuCBRule_CheckPokemonRegulation(p, rule, 2)) {
            switch (rule->a8) {
            case 0:
                break;
            case 1:
                _CB.err[player][i].b7 = 1;
                break;
            case 2:
                _CB.err[player][i].b6 = 1;
                break;
            }
        }
        _CB.err[player][i].a0 = menuCBRule_CheckPokemonError(p, 0) == 0;
        _CB.err[player][i].a3 = menuCBRule_CheckPokemonError(p, 1) == 0;
        _CB.err[player][i].a2 = menuCBRule_CheckPokemonError(p, 2) == 0;
        _CB.err[player][i].b4 = menuCBRule_CheckPokemonError(p, 3) == 0;
        _CB.err[player][i].a1 = menuCBRule_CheckPokemonError(p, 4) == 0;
        _CB.err[player][i].b1 = menuCBRule_CheckPokemonError(p, 5) == 0;
        _CB.err[player][i].b3 = menuCBRule_CheckTrainerRegulation(hero, rule, 0) == 0;
        _CB.err[player][i].a6 = menuCBRule_CheckTrainerRegulationAt(hero, p, rule, 1) == 0;
        _CB.err[player][i].b5 = menuCBRule_CheckTrainerRegulationAt(hero, p, rule, 2) == 0;
        _CB.err[player][i].b2 = menuCBRule_CheckTrainerRegulation(hero, rule, 3) == 0;
        _CB.err[player][i].a7 = menuCBRule_CheckLegendPokemon(p, rule) == 0;
    }
}

bool menuCBRule_CheckPokemonEventFlag(Pokemon* p) {
    switch (pokemonBiosGetPokemonDataId(p)) {
    case 0x97:
    case 0x19A:
        if (!pokemonBiosGetEventGetFlag(p)) {
            return 0;
        }
        break;
    }
    return 1;
}

bool menuCBRule_CheckErrorAll(Hero* hero) {
    u16 i;
    if (!menuCBRule_CheckTrainerErrorAll(hero)) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        if (!menuCBRule_CheckPokemonErrorAll(heroBiosGetPokemonPtr(hero, i))) {
            return 0;
        }
    }
    return 1;
}

bool menuCBRule_CheckTrainerErrorAll(Hero* hero) {
    s32 i;
    for (i = 0; i < 0; i++) {
        if (!menuCBRule_CheckTrainerError(hero, i)) {
            return 0;
        }
    }
    return 1;
}

bool menuCBRule_CheckTrainerError(Hero* hero, s32 kind) {
    return 0;
}

bool menuCBRule_CheckPokemonErrorAll(Pokemon* p) {
    s32 i;
    for (i = 0; i < 6; i++) {
        if (!menuCBRule_CheckPokemonError(p, i)) {
            return 0;
        }
    }
    return 1;
}

bool menuCBRule_CheckPokemonError(Pokemon* p, s32 kind) {
    if (menuCBRule_IsBlankPokemon(p)) {
        return 1;
    }
    switch (kind) {
    case 0: {
        Pokemon tmp;
        if (!menuCBRule_CheckPokemonError(p, 2)) {
            return 1;
        }
        if (!menuCBRule_CheckPokemonEventFlag(p)) {
            return 0;
        }
        pokemonBiosCopy(&tmp, p);
        pokemonResetBasisStatus(&tmp);
        u16 maxHp, phyAtk, phyDef, speAtk, speDef, nimble;
        if ((maxHp = pokemonBiosGetMaxHp(p), (u16)pokemonBiosGetMaxHp(&tmp) < maxHp) ||
            (phyAtk = pokemonBiosGetPhyAtk(p), (u16)pokemonBiosGetPhyAtk(&tmp) < phyAtk) ||
            (phyDef = pokemonBiosGetPhyDef(p), (u16)pokemonBiosGetPhyDef(&tmp) < phyDef) ||
            (speAtk = pokemonBiosGetSpeAtk(p), (u16)pokemonBiosGetSpeAtk(&tmp) < speAtk) ||
            (speDef = pokemonBiosGetSpeDef(p), (u16)pokemonBiosGetSpeDef(&tmp) < speDef) ||
            (nimble = pokemonBiosGetNimbleness(p), (u16)pokemonBiosGetNimbleness(&tmp) < nimble)) {
            return 0;
        }
        s32 sum = pokemonBiosGetMaxHpEffort(p);
        sum += pokemonBiosGetPhyAtkEffort(p);
        sum += pokemonBiosGetPhyDefEffort(p);
        sum += pokemonBiosGetSpeAtkEffort(p);
        sum += pokemonBiosGetSpeDefEffort(p);
        sum += pokemonBiosGetNimblenessEffort(p);
        if ((u32)sum > 0x1FE) {
            return 0;
        }
        if (pokemonBiosGetMaxHpEffort(p) > 0xFF || pokemonBiosGetPhyAtkEffort(p) > 0xFF ||
            pokemonBiosGetPhyDefEffort(p) > 0xFF || pokemonBiosGetSpeAtkEffort(p) > 0xFF ||
            pokemonBiosGetSpeDefEffort(p) > 0xFF || pokemonBiosGetNimblenessEffort(p) > 0xFF) {
            return 0;
        }
        return 1;
    }
    case 1:
        return pokemonIsDarkPokemon(p) == 0;
    case 2:
        return pokemonBiosGetTamagoFlag(p) == 0;
    case 3:
        return menuCBRule_CheckValidItem(pokemonBiosGetItemDataId(p));
    case 4: {
        int i;
        for (i = 0; i < 4; i++) {
            u16 waza = pokemonGetStatus(p, 0, 0x7F, i);
            if (waza != 0) {
                if (wazaDataBiosGetPtr(waza) == wazaDataBiosGetPtr(0)) {
                    return 0;
                }
            }
        }
        return 1;
    }
    case 5:
        pokemonGetStatus(p, 0, 0x6E, 0);
        return pokemonCheckValid(p);
    }
    return 0;
}

bool menuCBRule_CheckRegulationAll(Hero* hero, CBRule* rule) {
    int i;
    s32 count = 0;
    if (!menuCBRule_CheckTrainerRegulationAll(hero, rule)) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        Pokemon* p = heroBiosGetPokemonPtr(hero, i);
        if (p != 0 && pokemonCheckValid(p)) {
            if (!menuCBRule_CheckPokemonRegulationAll(p, rule)) {
                return 0;
            }
            if (!menuCBRule_CheckLegendPokemon(p, rule)) {
                return 0;
            }
            count++;
        }
    }
    return count > 0;
}

bool menuCBRule_CheckTrainerRegulationAll(Hero* hero, CBRule* rule) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (!menuCBRule_CheckTrainerRegulation(hero, rule, i)) {
            return 0;
        }
    }
    return 1;
}

bool menuCBRule_CheckTrainerRegulationAt(Hero* hero, Pokemon* p, CBRule* rule, s32 kind) {
    int i;
    switch (kind) {
    case 0:
        return menuCBRule_CheckTrainerRegulation(hero, rule, kind);
    case 1:
        if (rule->aC) {
            return 1;
        }
        if (menuCBRule_IsBlankPokemon(p) || _menuCBRule_IsTamagoPokemon(p)) {
            return 1;
        }
        for (i = 0; i < 6; i++) {
            Pokemon* q = heroBiosGetPokemonPtr(hero, i);
            if (q != p && !menuCBRule_IsBlankPokemon(q) && !_menuCBRule_IsTamagoPokemon(q)) {
                if (pokemonBiosGetPokemonDataId(q) == pokemonBiosGetPokemonDataId(p)) {
                    return 0;
                }
            }
        }
        return 1;
    case 2:
        if (rule->aD) {
            return 1;
        }
        if (menuCBRule_IsBlankPokemon(p) || _menuCBRule_IsTamagoPokemon(p)) {
            return 1;
        }
        if (pokemonBiosGetItemDataId(p) == 0) {
            return 1;
        }
        for (i = 0; i < 6; i++) {
            Pokemon* q = heroBiosGetPokemonPtr(hero, i);
            if (q != p && !menuCBRule_IsBlankPokemon(q) && !_menuCBRule_IsTamagoPokemon(q)) {
                if (pokemonBiosGetItemDataId(q) == pokemonBiosGetItemDataId(p)) {
                    return 0;
                }
            }
        }
        return 1;
    case 3: {
        bool r = 0;
        if (menuCBRule_CheckTrainerRegulation(hero, rule, 3) || !menuCBRule_IsBlankPokemon(p)) {
            r = 1;
        }
        return r;
    }
    }
    return 0;
}

bool menuCBRule_CheckTrainerRegulation(Hero* hero, CBRule* rule, s32 kind) {
    s32 total = 0;
    bool noDupSpecies = 1;
    bool noDupItem = 1;
    u32 i;
    Pokemon* p;
    u32 j;
    Pokemon* q;
    int count;
    u16 k;
    for (i = 0; i < 6; i++) {
        p = heroBiosGetPokemonPtr(hero, i);
        if (!menuCBRule_IsBlankPokemon(p) && !_menuCBRule_IsTamagoPokemon(p)) {
            total += pokemonBiosGetLevel(p);
            for (j = i + 1; j < 6; j++) {
                q = heroBiosGetPokemonPtr(hero, j);
                if (!menuCBRule_IsBlankPokemon(q) && !_menuCBRule_IsTamagoPokemon(q)) {
                    if (pokemonBiosGetItemDataId(p) != 0) {
                        noDupItem &= pokemonBiosGetItemDataId(p) != pokemonBiosGetItemDataId(q);
                    }
                    noDupSpecies &= pokemonBiosGetPokemonDataId(p) != pokemonBiosGetPokemonDataId(q);
                }
            }
        }
    }
    switch (kind) {
    case 0:
        return total <= rule->a4;
    case 1: {
        bool r = 0;
        if (rule->aC || noDupSpecies) {
            r = 1;
        }
        return r;
    }
    case 2: {
        bool r = 0;
        if (rule->aD || noDupItem) {
            r = 1;
        }
        return r;
    }
    case 3:
        count = 0;
        for (k = 0; k < 6; k++) {
            if (!menuCBRule_IsBlankPokemon(heroBiosGetPokemonPtr(hero, k))) {
                count++;
            }
        }
        {
            s32 lim = rule->a1C;
            if (lim == 1) {
                return lim <= (u16)count;
            }
            lim = rule->a1A;
            return lim <= (u16)count;
        }
    }
    return 0;
}

bool menuCBRule_CheckPokemonRegulationAll(Pokemon* p, CBRule* rule) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (!menuCBRule_CheckPokemonRegulation(p, rule, i)) {
            return 0;
        }
    }
    return 1;
}

bool menuCBRule_CheckPokemonRegulation(Pokemon* p, CBRule* rule, s32 kind) {
    if (menuCBRule_IsBlankPokemon(p)) {
        return 1;
    }
    switch (kind) {
    case 0:
        return rule->a0 <= pokemonBiosGetLevel(p);
    case 1:
        return pokemonBiosGetLevel(p) <= rule->a2;
    case 2:
        return menuCBRule_CheckRegulationItem(pokemonBiosGetItemDataId(p));
    }
    return 0;
}

s32 menuCBRule_CheckHero(Hero* hero) {
    s32 ok = 0;
    if (menuCBRule_CheckErrorAll(hero) && menuCBRule_CheckRegulationAll(hero, menuCBBios_CurrentRule())) {
        ok = 1;
    }
    return ok;
}

}

static bool _menuCBRule_IsTamagoPokemon(Pokemon* p) {
    bool r;
    if (menuCBRule_IsBlankPokemon(p)) {
        r = 0;
    } else {
        r = 0;
        if (pokemonBiosGetTamagoFlag(p) || !pokemonCheckValid(p)) {
            r = 1;
        }
    }
    return r;
}

extern "C" {

CBRule* menuCB_OreRule(void) {
    if (menuCBBios_CurrentlyWorkingToolBattle()) {
        return 0;
    }
    return (CBRule*)&oreRule;
}

bool menuCBRule_IsBlankPokemon(Pokemon* p) {
    bool r = 0;
    if (p == 0 || pokemonGetStatus(p, 0, 0x6E, 0) == 0) {
        r = 1;
    }
    return r;
}

u8 menuCBRule_EnableSkill_SonicBoom(void) {
    return menuCBBios_CurrentRule()->a13;
}

u8 menuCBRule_EnableSkill_Michidure(void) {
    return menuCBBios_CurrentRule()->a12;
}

u8 menuCBRule_ProhibitionSuicide(void) {
    return menuCBBios_CurrentRule()->a11;
}

u8 menuCBRule_EnableSkillSwap(void) {
    return menuCBBios_CurrentRule()->a10;
}

u8 menuCBRule_EnableSbToIceed(void) {
    return menuCBBios_CurrentRule()->aF;
}

u8 menuCBRule_EnableSbToSleep(void) {
    return menuCBBios_CurrentRule()->aE;
}

u8 menuCBRule_DEOKISISUCamouflage(void) {
    return menuCBBios_CurrentRule()->a19;
}

s16 menuCBRule_GetCommandTimeLimit(void) {
    return menuCBBios_CurrentRule()->a16;
}

s32 menuCBRule_GetBattleTimeLimit(void) {
    return menuCBBios_CurrentRule()->a14 * 60;
}

bool menuCBRule_CheckValidItem(u16 id) {
    switch (id) {
    case 0:
        return 1;
    case 0xAF:
        return 0;
    }
    return itemDataCheckValid(id);
}

bool menuCBRule_CheckRegulationItem(u16 id) {
    CBRule* rule = menuCBBios_CurrentRule();
    if (!menuCBRule_CheckValidItem(id)) {
        return 0;
    }
    switch (rule->a8) {
    case 0:
        return 1;
    case 1:
        return id == 0;
    case 2: {
        u32 n = menuCBRule_RegulationItems();
        for (u32 i = 0; i < n; i++) {
            if (id == itemtoolbattle[i]) {
                return rule->f[i] == 0;
            }
        }
        return 1;
    }
    }
    return 0;
}

u16 menuCBRule_RegulationItemID(s32 i) {
    if (i < 0 || menuCBRule_RegulationItems() <= (u32)i) {
        return 0;
    }
    return itemtoolbattle[i];
}

u32 menuCBRule_RegulationItems(void) {
    return itemtoolbattle_number - 1;
}

s16 menuCBRule_ParticipationPokemonMax2(void) {
    s16 max = 6;
    switch (_CB.ruleType) {
    case 0:
        if (_CB.rule[0].a1C == 0) max = _CB.rule[0].a1A;
        break;
    case 1:
        if (_CB.rule[1].a1C == 0) max = _CB.rule[1].a1A;
        break;
    case 2:
        if (_CB.rule[2].a1C == 0) max = _CB.rule[2].a1A;
        break;
    case 3:
        if (_CB.rule[3].a1C == 0) max = _CB.rule[3].a1A;
        break;
    case 4:
        if (_CB.rule[4].a1C == 0) max = _CB.rule[4].a1A;
        break;
    case 5:
        if (_CB.rule[5].a1C == 0) max = _CB.rule[5].a1A;
        break;
    }
    return max;
}

void menuCBRule_ParticipationPokemonMax(void) {
    menuCBRule_ParticipationPokemonMax2();
}

CBRule* menuCBRule_ConstantRule2(s32 type) {
    u16* src = 0;
    int idx;
    switch (type) {
    case 0:
    case 1:
    case 2:
        idx = type;
        break;
    case 3:
    case 4:
    case 5:
        idx = 2;
        break;
    default:
        idx = 0;
        break;
    }
    memset(&ruleTempBuff, 0, 0x90);
    memcpy(&ruleTempBuff, &staRule[idx], 0x90);
    switch (type) {
    case 3:
    case 4:
    case 5:
        ruleTempBuff.a1C = 0;
        ruleTempBuff.a1A = 4;
        break;
    }
    if (type != 0) {
        u32 i;
        for (i = 0; i < itemtoolbattle_number; i++) {
            if (menuCBRule_RegulationItemID(i) == 0xBF) {
                ruleTempBuff.f[i] = 1;
            }
        }
    }
    switch (type) {
    case 3:
        src = GSmsgGetGSchar(0x438A);
        break;
    case 4:
        src = GSmsgGetGSchar(0x438B);
        break;
    case 5:
        src = GSmsgGetGSchar(0x438C);
        break;
    default:
        src = 0;
        break;
    }
    for (int k = 0; k < 7; k++) {
        for (int j = 0; j < 3; j++) {
            if (src != 0) {
                if (*src == 0xFFFF) src += 2;
                ruleTempBuff.name[k][j] = *src;
                if (*src != 0) src += 1;
            } else {
                ruleTempBuff.name[k][j] = 0;
            }
        }
    }
    return &ruleTempBuff;
}

CBRule* menuCBRule_ConstantRule(s32 i) {
    switch (i) {
    case 0:
    case 1:
    case 2:
        return (CBRule*)&staRule[i];
    }
    return 0;
}

void menuCBRule_Copy(CBRule* dst, CBRule* src) {
    memcpy(dst, src, 0x90);
}

bool menuCBRule_IsEquals(CBRule* a, CBRule* b) {
    return memcmp(a, b, 0x90) == 0;
}

}
