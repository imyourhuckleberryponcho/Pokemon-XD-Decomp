#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct EncountData {
    u8 bytes[0x3C];
};

extern "C" {

void* GSmsgGetGSchar(u32 id);
void GScharMakeFromSJIS(s16* dst, const char* src);
void GScharCat(s16* dst, void* src);
s32 GSfloorGetCurrentFloorGroupID(void);
u32 GSinputButtonsChanged(s32 pad);
u32 GSinputButtonsPressed(s32 pad);
void* GSmemAlloc(u32 size);
void GSmemFree(void* p);
void* GSthreadCreate(s32, s32, s32, s32, s32, void*);
void GSthreadSetArgs(void*, s32, ...);
void GSthreadSetName(void*, const char*);
void GSthreadSwitch(void);
void GSfsysFreeCache(s32);
void Sequence_Free(void*);
void Sequence_SetVisibility(void*, s32);
void battleGridReplacePokemon(void*, void*);
void battleGridUpdate(void);
void dbgMenuClose(void);
void dbgMenuFightTrainerAiAddsubDataComboEditSub(void);
void dbgMenuFightTrainerAiAddsubDataIrekaeDasuEditSub(void);
void dbgMenuFightTrainerAiAddsubDataIrekaeModosuEditSub(void);
void dbgMenuFightTrainerAiAddsubDataItemEditSub(void);
void dbgMenuFightTrainerAiAddsubDataWazaDefpokemonEditSub(void);
void dbgMenuFightTrainerAiAddsubDataWazaUsewazaEditSub(void);
s32 dbgMenuFightTrainerAiDataEditSub(u16);
void dbgMenuFightTrainerDataStatusInputDigit(u16, s32, s32, s32, s32);
void dbgMenuFightTrainerPokemonPartDataEditSub(u16);
void dbgMenuFightWazaEditSub(u16);
s32 dbgMenuPokemonEditSub(void*, s32, u8*, u8*, u8*, u8*);
void* fightFloorGetFightPokemonPtrToFightTrainerPtr(s32, void*);
u32 fightFloorGetStatus(s32, u32, s32, s32);
void fightFloorSetTimeOutAllFightResult(s32);
u8 fightIsFight(void);
u32 fightKindDataBiosGetName(void*);
void* fightKindDataBiosGetPtr(u16);
void fightMenuFightOutPokemonRenewStatusMenu(void*, u16, s32);
void fightMenuFightTrainerRenewStatusMenu(void*, u16);
void fightOutPokemonGetTokuseiDataId(void*);
void fightOutPokemonGetZokuseiDataId(void*, s32);
void fightOutPokemonInitJoutaiDataId(void*, s32);
u8 fightOutPokemonIsUseHensinBuff(void);
void fightOutPokemonSetTokuseiDataId(void*, s32);
void fightOutPokemonSetZokuseiDataId(void*, u8, u16);
void* fightPokemonGetPokemonPtr(void*);
u8 fightSeqCheckYubiwohuruWazaDataId(u16);
u8 fightSeqGetEffectAminFlag(void);
void fightSeqSetEffectAminFlag(u8);
void fightSetFightResultId(s32);
void* fightSideGetValidFightTrainerPtr(void*, s32);
void* fightTargetGetPtrAsNowFightType(s32, s32);
u8 fightTrainerCheckCanIrekaeFightPokemon(void*, void*);
void* fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(void*, void*);
u32 fightTrainerGetStatus(void*, u16, u32, u32);
void* fightTrainerGetValidFightPokemonPtr(void*, s32);
u8 figthPokemonGetLevel(void*);
void* getDeckMsgID(u16, s32);
s32 menuFaceGetID(void*);
void menuFaceLoad(void*, s32, s32);
s8 menuFaceSearchEnable(s32);
void menuCloseCustom(s32, s32, s32);
s32 menuGetCursorItemID(s32);
s32 menuOpen(s32, s32);
s32 menuOpenCustom(s32, ...);
void menuSubCloseNumberInput(void);
u8 menuSubOpenNumberInput(s32, s32*, s32, s32, s32, s32);
u8 menuSubOpenNumberInputID(u16, u32*, void* (*)(u32));
s8 menuSubOpenYesNo(s32, s32, s32, bool);
void msgctrlSetValue(s32, void*);
void* pokemonCreateSequence(void*);
u32 pokemonGetStatus(void*, u32, u32, u32);
s32 pokemonGetTokuseiDataId(void*);
void pokemonSetSequenceStatus(void*, u32);
void pokemonSetStatus(void*, s32, s32, s32, s32);
void* wazaGetStatus(void*, u16, s32, s32);
void* wazaGetWazaTypeIdName(u8);
u8 winMsgCloseCheckFight(void);
void winMsgCloseFight(s32);
void winMsgOpenFight(void*, s32, s32);
u32 zokuseiBiosGetName(u16);
void fightFreeResourceDeclArchive(void);
void fightFreeResourceID(s32, s32);
u8 fightReadResourceID(s32, s32);
s32 getDeckResourceID(u8);
u32 deckGetTrainerSize(void);
void fightEncount(void);

extern u32* fight_encount_data_number;
extern u32* fight_floor_data_number;
extern u32* fight_kind_data_number;
extern u32* fight_trainer_ai_value_addsub_data_number;
extern u32* fight_trainer_pokemon_part_data_number;
extern u32* zokusei_data_number;
extern u32 deck_group_data_number;
extern u32 deck_group_data[];

void* fightEncountDataBiosGetPtr(u16 id);
u32 fightEncountDataBiosGetFightKind(void*);
void fightEncountDataBiosSetFightKind(void*, u8);
u32 fightEncountDataBiosGetTrainer(void*);
void fightEncountDataBiosSetTrainer(void*, u8);
u32 fightEncountDataBiosGetPokemon(void*);
void fightEncountDataBiosSetPokemon(void*, u8);
u32 fightEncountDataBiosGetEntry(void*);
void fightEncountDataBiosSetEntry(void*, u8);
u16 fightEncountDataBiosGetFightFloorDataId(void*);
void fightEncountDataBiosSetFightFloorDataId(void*, u16);
u16 fightEncountDataBiosGetFightTrainerDataId(void*, u8);
void fightEncountDataBiosSetFightTrainerDataId(void*, u8, u16);
u16 fightEncountDataBiosGetGSInputDevice(void*, u8);
void fightEncountDataBiosSetGSInputDevice(void*, u8, u32);
u16 fightEncountDataBiosGetFightDeckGrpId(void*, u8);
u32 fightEncountDataBiosGetFightName(void*);

static s32 _dbgMenuFightFightTrainerSerihuTestSub(u16, u8);
static s32 _dbgMenuFightFightPokemonSelectSub(void*);
static void _dbgMenuFightStopSub(s32);
static void* _dbgMenuFightGetFightTrainerAiAddsubValueDataIdSub(u32);
static void* _dbgMenuFightGetFightTrainerPokemonPartDataIdSub(u32);
static void* _dbgMenuFightGetWazaDataIdSub(u32);
static void* _dbgMenuFightGetWazaTypeIdSub(u32);
static void* _dbgMenuFightGetZokuseiDataIdSub(u32);
static void* _dbgMenuFightGetGsinputDevIdSub(u32);
static void* _dbgMenuFightGetFightTrainerDataIdSub(u32);
static void* _dbgMenuFightGetPokemonEntrySub(u32);
static void* _dbgMenuFightGetPokemonFightTypeSub(u32);
static void* _dbgMenuFightGetFightTypeDataIdSub(u32);
static void* _dbgMenuFightGetFightKindDataIdSub(u32);
static void* _dbgMenuFightGetFightFloorDataIdSub(u32);
static void* _dbgMenuFightGetFightDeckDataIdSub(u32);
static void _dbgMenuFightGetFightEncountDataIdSub(u32);

s32 dbgMenuFightGetFightTrainerDataId(u32);
s32 dbgMenuFightGetFightTrainerPokemonPartDataId(u32);
s32 dbgMenuFightGetFightTrainerAiAddsubValueDataId(u32, u8);
s32 dbgMenuFightGetWazaDataId(u32);
s32 dbgMenuFightGetWazaTypeId(u8);
s32 dbgMenuFightGetZokuseiDataId(u32);
s32 dbgMenuFightGetGsinputDevId(u32);
s32 dbgMenuFightGetPokemonEntry(u8);
s32 dbgMenuFightGetPokemonFightType(u8);
s32 dbgMenuFightGetFightTypeDataId(u8);
s32 dbgMenuFightGetFightKindDataId(u8);
s32 dbgMenuFightGetFightFloorDataId(u32);
s32 dbgMenuFightGetFightDeckDataId(u32);
s32 dbgMenuFightGetFightEncountDataId(u32);
s32 dbgMenuFightEncount(u16);
void dbgMenuFightSetMsgSpeed(u8);
u8 dbgMenuFightGetMsgSpeed(void);
void dbgMenuFightSetTuikakoukaFlag(u8);
u8 dbgMenuFightGetTuikakoukaFlag(void);
void dbgMenuFightSetMsgKeyWaitFlag(u8);
u8 dbgMenuFightGetMsgKeyWaitFlag(void);
void dbgMenuFightSetAllFightTrainerOperateFlag(u8);
u8 dbgMenuFightGetAllFightTrainerOperateFlag(void);
void dbgMenuFightSetFightDebugMenuOpenFlag(u8);
u8 dbgMenuFightGetFightDebugMenuOpenFlag(void);
void dbgMenuFightSetFightTrainerAiFlowDispFlag(u8);
u8 dbgMenuFightGetFightTrainerAiFlowDispFlag(void);
void dbgMenuFightSetSoubikoukaFlag(u8);
u8 dbgMenuFightGetSoubikoukaFlag(void);
void dbgMenuFightSetYubiwohuruWazaDataId(u16);
u16 dbgMenuFightGetYubiwohuruWazaDataId(void);
void dbgMenuFightSetFightTrainerAiLastValueReviseFlag(u8);
u8 dbgMenuFightGetFightTrainerAiLastValueReviseFlag(void);
void dbgMenuFightSetFightPokeStMenuOpenFlag(u8);
u8 dbgMenuFightGetFightPokeStMenuOpenFlag(void);
s32 dbgMenuGetGsinputMsgId(s32);

static u8 _msg_speed = 5;
static u16 _dbgmenu_fight_waza_edit_waza_data_id = 1;
static u16 _dbgmenu_fight_deck_data_id = 1;
static u16 _dbgmenu_fight_sample_encount_data_id = 1;
static u16 _dbgmenu_fight_story_encount_data_id = 1;
static u16 _dbgmenu_fight_hundred_encount_data_id = 1;
static u16 _dbgmenu_fight_imasugu_encount_data_id = 1;
static u16 _dbgmenu_fight_virtual_encount_data_id = 1;
static u16 _dbgmenu_fight_bingo_encount_data_id = 1;
static u16 _dbgmenu_fight_colosseum_encount_data_id = 1;
static u8 _fight_trainer_ai_last_value_revise_flag = 1;
static u8 _fight_pokemon_status_menu_open_flag = 1;
static u16 _dbgmenu_fight_trainer_pokemon_part_data_id = 1;
static u8 _msg_key_wait_flag;
static u8 _all_fight_trainer_operate_flag;
static u8 _fight_debug_menu_open_flag;
static u8 _fight_trainer_ai_flow_disp_flag;
static u8 _tuikakouka_flag;
static void* _target_fight_side_ptr;
static void* _target_fight_trainer_ptr;
static void* _target_fight_pokemon_ptr;
static u8 _soubikakouka_flag;
static u16 _yubiwohuru_waza_data_id;
static u16 _dbgmenu_fight_trainer_data_id;
static u16 _dbgmenu_fight_trainer_ai_addsub_data_id;
static u16 _readEncountDataCnt;
static u16* _readEncountDataID;
static u32* _readEncountDataName;

void dbgMenuFightFightTrainerSerihuTestHaiboku2(void) {
    _dbgMenuFightFightTrainerSerihuTestSub(_dbgmenu_fight_trainer_data_id, 3);
}

void dbgMenuFightFightTrainerSerihuTestHaiboku(void) {
    _dbgMenuFightFightTrainerSerihuTestSub(_dbgmenu_fight_trainer_data_id, 2);
}

void dbgMenuFightFightTrainerSerihuTestSyouri(void) {
    _dbgMenuFightFightTrainerSerihuTestSub(_dbgmenu_fight_trainer_data_id, 1);
}

void dbgMenuFightFightTrainerSerihuTestToujou(void) {
    _dbgMenuFightFightTrainerSerihuTestSub(_dbgmenu_fight_trainer_data_id, 0);
}

static s32 _dbgMenuFightFightTrainerSerihuTestSub(u16 id, u8 kind) {
    void* result = (void*)fightTrainerGetStatus(0, id, 8, kind);
    if (result == 0) {
        return -1;
    }
    winMsgOpenFight(result, 1, 1);
    winMsgCloseFight(1);
    return 1;
}

s32 dbgMenuFightFightTrainerSerihuTest(void) {
    s32 id = dbgMenuFightGetFightTrainerDataId(_dbgmenu_fight_trainer_data_id);
    if (id < 0) {
        return -1;
    }
    _dbgmenu_fight_trainer_data_id = id;
    return 1;
}

s32 dbgMenuFightEncountDataEditSub(u16 id) {
    void* data;
    EncountData backup;
    s32 value;
    s32 result;

    if (id == 0) {
        return 1;
    }
    if (id >= *fight_encount_data_number) {
        return 1;
    }
    data = fightEncountDataBiosGetPtr(id);
    backup = *(EncountData*)data;
    for (;;) {
        result = menuOpenCustom(0x25, 0, 0, 0, 1, 1, id);
        if (result == -1) {
            menuCloseCustom(0x25, 0, 1);
            *(EncountData*)data = backup;
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x25)) {
        case 0x10A:
            value = dbgMenuFightGetFightKindDataId(fightEncountDataBiosGetFightKind(data));
            if (value >= 0) {
                fightEncountDataBiosSetFightKind(data, value);
            }
            break;
        case 0x10B:
            value = dbgMenuFightGetFightTypeDataId(fightEncountDataBiosGetTrainer(data));
            if (value >= 0) {
                fightEncountDataBiosSetTrainer(data, value);
            }
            break;
        case 0x10C:
            value = dbgMenuFightGetPokemonFightType(fightEncountDataBiosGetPokemon(data));
            if (value >= 0) {
                fightEncountDataBiosSetPokemon(data, value);
            }
            break;
        case 0x10D:
            value = dbgMenuFightGetPokemonEntry(fightEncountDataBiosGetEntry(data));
            if (value >= 0) {
                fightEncountDataBiosSetEntry(data, value);
            }
            break;
        case 0x10E:
            value = dbgMenuFightGetFightFloorDataId(fightEncountDataBiosGetFightFloorDataId(data));
            if (value >= 0) {
                fightEncountDataBiosSetFightFloorDataId(data, value);
            }
            break;
        case 0x10F:
            value = dbgMenuFightGetFightTrainerDataId(fightEncountDataBiosGetFightTrainerDataId(data, 0));
            if (value >= 0) {
                fightEncountDataBiosSetFightTrainerDataId(data, 0, value);
                value = dbgMenuFightGetGsinputDevId(fightEncountDataBiosGetGSInputDevice(data, 0));
                if (value >= 0) {
                    fightEncountDataBiosSetGSInputDevice(data, 0, value);
                }
            }
            break;
        case 0x110:
            value = dbgMenuFightGetFightTrainerDataId(fightEncountDataBiosGetFightTrainerDataId(data, 1));
            if (value >= 1) {
                fightEncountDataBiosSetFightTrainerDataId(data, 1, value);
                value = dbgMenuFightGetGsinputDevId(fightEncountDataBiosGetGSInputDevice(data, 1));
                if (value >= 0) {
                    fightEncountDataBiosSetGSInputDevice(data, 1, value);
                }
            }
            break;
        case 0x111:
            value = dbgMenuFightGetFightTrainerDataId(fightEncountDataBiosGetFightTrainerDataId(data, 2));
            if (value >= 0) {
                fightEncountDataBiosSetFightTrainerDataId(data, 2, value);
                value = dbgMenuFightGetGsinputDevId(fightEncountDataBiosGetGSInputDevice(data, 2));
                if (value >= 0) {
                    fightEncountDataBiosSetGSInputDevice(data, 2, value);
                }
            }
            break;
        case 0x112:
            value = dbgMenuFightGetFightTrainerDataId(fightEncountDataBiosGetFightTrainerDataId(data, 3));
            if (value >= 0) {
                fightEncountDataBiosSetFightTrainerDataId(data, 3, value);
                value = dbgMenuFightGetGsinputDevId(fightEncountDataBiosGetGSInputDevice(data, 3));
                if (value >= 0) {
                    fightEncountDataBiosSetGSInputDevice(data, 3, value);
                }
            }
            break;
        }
    }
    menuCloseCustom(0x25, 0, 1);
    return 1;
}

s32 dbgMenuGetGsinputMsgId(s32 kind) {
    if (kind == 0) {
        return 0xED04;
    }
    if (kind == 1) {
        return 0xED05;
    }
    if (kind == 2) {
        return 0xED06;
    }
    if (kind == 3) {
        return 0xED07;
    }
    if (kind == 4) {
        return 0xED08;
    }
    return 0xED04;
}

struct DbgMenuWindow {
    u8 unk0[4];
    s32 menuID;
    u8 unk8[0x80];
    s32 result;
    u8 unk8C[0x18];
    u8 done;
    u8 cancelled;
};

void dbmMenuFightButtonNormal(DbgMenuWindow* win) {
    if (win != 0) {
        u32 changed;
        u32 pressed;
        changed = GSinputButtonsChanged(1);
        pressed = GSinputButtonsPressed(1);
        if ((pressed & changed) & 0x100) {
            win->done = 1;
            win->result = menuGetCursorItemID(win->menuID);
        }
        changed = GSinputButtonsChanged(1);
        pressed = GSinputButtonsPressed(1);
        if ((pressed & changed) & 0x1000) {
            win->done = 1;
            win->result = -2;
        }
        changed = GSinputButtonsChanged(1);
        pressed = GSinputButtonsPressed(1);
        if ((pressed & changed) & 0x200) {
            win->done = 1;
            win->cancelled = 1;
            win->result = -1;
        }
    }
}

s32 dbgMenuFightStopTimeOut(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    fightFloorSetTimeOutAllFightResult(0);
    dbgMenuClose();
    return 0;
}

s32 dbgMenuFightStopHostLose(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _dbgMenuFightStopSub(3);
    return 0;
}

s32 dbgMenuFightStopHostWin(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _dbgMenuFightStopSub(2);
    return 0;
}

static void _dbgMenuFightStopSub(s32 result) {
    fightSetFightResultId(result);
    dbgMenuClose();
}

s32 dbgMenuFightFightPokemonSelect5(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_pokemon_ptr = fightTrainerGetValidFightPokemonPtr(_target_fight_trainer_ptr, 5);
    if (_target_fight_pokemon_ptr == 0) {
        return -1;
    }
    return _dbgMenuFightFightPokemonSelectSub(_target_fight_pokemon_ptr);
}

s32 dbgMenuFightFightPokemonSelect4(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_pokemon_ptr = fightTrainerGetValidFightPokemonPtr(_target_fight_trainer_ptr, 4);
    if (_target_fight_pokemon_ptr == 0) {
        return -1;
    }
    return _dbgMenuFightFightPokemonSelectSub(_target_fight_pokemon_ptr);
}

s32 dbgMenuFightFightPokemonSelect3(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_pokemon_ptr = fightTrainerGetValidFightPokemonPtr(_target_fight_trainer_ptr, 3);
    if (_target_fight_pokemon_ptr == 0) {
        return -1;
    }
    return _dbgMenuFightFightPokemonSelectSub(_target_fight_pokemon_ptr);
}

s32 dbgMenuFightFightPokemonSelect2(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_pokemon_ptr = fightTrainerGetValidFightPokemonPtr(_target_fight_trainer_ptr, 2);
    if (_target_fight_pokemon_ptr == 0) {
        return -1;
    }
    return _dbgMenuFightFightPokemonSelectSub(_target_fight_pokemon_ptr);
}

s32 dbgMenuFightFightPokemonSelect1(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_pokemon_ptr = fightTrainerGetValidFightPokemonPtr(_target_fight_trainer_ptr, 1);
    if (_target_fight_pokemon_ptr == 0) {
        return -1;
    }
    return _dbgMenuFightFightPokemonSelectSub(_target_fight_pokemon_ptr);
}

s32 dbgMenuFightFightPokemonSelect0(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_pokemon_ptr = fightTrainerGetValidFightPokemonPtr(_target_fight_trainer_ptr, 0);
    if (_target_fight_pokemon_ptr == 0) {
        return -1;
    }
    return _dbgMenuFightFightPokemonSelectSub(_target_fight_pokemon_ptr);
}

static s32 _dbgMenuFightFightPokemonSelectSub(void* fightPokemon) {
    u8 spB;
    u8 spA;
    u8 sp9;
    u8 sp8;
    u32 species;
    u8 level;
    void* trainer;
    void* pokemon;
    s32 result;
    void* outPokemon;
    u16 floorStatus;
    void* seq;
    void* newSeq;
    u16 i;

    spB = 0;
    spA = 0;
    sp9 = 0;
    sp8 = 0;
    floorStatus = fightFloorGetStatus(0, 0, 0x14, 0);
    pokemon = fightPokemonGetPokemonPtr(fightPokemon);
    if (pokemon == 0) {
        return -1;
    }
    trainer = fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fightPokemon);
    if (trainer == 0) {
        return -1;
    }
    level = figthPokemonGetLevel(fightPokemon);
    if (fightTrainerCheckCanIrekaeFightPokemon(trainer, fightPokemon) == 2) {
        outPokemon = fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(trainer, fightPokemon);
        if (fightOutPokemonIsUseHensinBuff() == 1) {
            return -1;
        }
        if (outPokemon != 0) {
            fightOutPokemonGetTokuseiDataId(outPokemon);
            for (i = 0; i < 2; i++) {
                fightOutPokemonGetZokuseiDataId(outPokemon, 0);
            }
        }
        result = dbgMenuPokemonEditSub(pokemon, 1, &spB, &spA, &sp9, &sp8);
        if (result == 1) {
            species = pokemonGetStatus(pokemon, 0, 0x6E, 0);
            if (outPokemon != 0) {
                seq = (void*)pokemonGetStatus(outPokemon, 0, 0xEE, 0);
                if (seq != 0) {
                    menuFaceLoad(pokemon, 0, 0);
                    while (menuFaceSearchEnable(menuFaceGetID(pokemon)) == 0) {
                        GSthreadSwitch();
                    }
                    newSeq = pokemonCreateSequence(fightPokemon);
                    battleGridReplacePokemon(seq, newSeq);
                    battleGridUpdate();
                    pokemonSetStatus(outPokemon, 0, 0xEE, 0, (s32)newSeq);
                    Sequence_Free(seq);
                    Sequence_SetVisibility(newSeq, 1);
                    fightOutPokemonInitJoutaiDataId(outPokemon, 0x14);
                }
                fightMenuFightOutPokemonRenewStatusMenu(outPokemon, fightFloorGetStatus(0, 0, 0x14, 0), 1);
                pokemonSetSequenceStatus(pokemon, pokemonGetStatus(outPokemon, 0, 0xEE, 0));
                fightOutPokemonSetTokuseiDataId(outPokemon, pokemonGetTokuseiDataId(pokemon));
                {
                    u32 i;
                    for (i = 0; (u16)i < 2; i++) {
                        u16 val = pokemonGetStatus(0, species, 0x16, i);
                        fightOutPokemonSetZokuseiDataId(outPokemon, (u8)i, val);
                    }
                }
            }
        }
    } else {
        result = dbgMenuPokemonEditSub(pokemon, 1, 0, 0, 0, 0);
    }
    if (figthPokemonGetLevel(fightPokemon) > level) {
        pokemonSetStatus(fightPokemon, 0, 0xD0, 0, 1);
    }
    fightMenuFightTrainerRenewStatusMenu(trainer, floorStatus);
    return result;
}

s32 dbgMenuFightFightTrainerPokemonPartDataEdit(void) {
    s32 id;

    if (fightIsFight() == 0) {
        return -1;
    }
    for (;;) {
        id = dbgMenuFightGetFightTrainerPokemonPartDataId(_dbgmenu_fight_trainer_pokemon_part_data_id);
        if (id < 0) {
            return 1;
        }
        _dbgmenu_fight_trainer_pokemon_part_data_id = id;
        dbgMenuFightTrainerPokemonPartDataEditSub(id);
    }
}

s32 dbgMenuFightFightTrainerAiDataEdit(void) {
    u16 id = fightTrainerGetStatus(0, fightTrainerGetStatus(_target_fight_trainer_ptr, 0, 0x43, 0), 2, 0);
    if (fightIsFight() == 0) {
        return -1;
    }
    return dbgMenuFightTrainerAiDataEditSub(id);
}

void dbgMenuFightFightTrainerAiAddsubCombo(void) {
    dbgMenuFightTrainerAiAddsubDataComboEditSub();
}

void dbgMenuFightFightTrainerAiAddsubItem(void) {
    dbgMenuFightTrainerAiAddsubDataItemEditSub();
}

void dbgMenuFightFightTrainerAiAddsubWazaUsewaza(void) {
    dbgMenuFightTrainerAiAddsubDataWazaUsewazaEditSub();
}

void dbgMenuFightFightTrainerAiAddsubWazaDefpokemon(void) {
    dbgMenuFightTrainerAiAddsubDataWazaDefpokemonEditSub();
}

s32 dbgMenuFightFightTrainerAiAddsubWaza(void) {
    return 1;
}

void dbgMenuFightFightTrainerAiAddsubIrekaeDasu(void) {
    dbgMenuFightTrainerAiAddsubDataIrekaeDasuEditSub();
}

void dbgMenuFightFightTrainerAiAddsubIrekaeModosu(void) {
    dbgMenuFightTrainerAiAddsubDataIrekaeModosuEditSub();
}

s32 dbgMenuFightFightTrainerAiAddsubIrekae(void) {
    return 1;
}

s32 dbgMenuFightFightTrainerAiAddsubDataEdit(void) {
    s32 id;

    for (;;) {
        id = dbgMenuFightGetFightTrainerAiAddsubValueDataId(_dbgmenu_fight_trainer_ai_addsub_data_id, 1);
        if (id < 0) {
            return 1;
        }
        _dbgmenu_fight_trainer_ai_addsub_data_id = id;
        dbgMenuFightTrainerDataStatusInputDigit(id, 0x3E, 0, 0xC8, -0xC8);
    }
}

s32 dbgMenuFightFightTrainerSelect1(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_trainer_ptr = fightSideGetValidFightTrainerPtr(_target_fight_side_ptr, 1);
    if (_target_fight_trainer_ptr == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightTrainerSelect0(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_trainer_ptr = fightSideGetValidFightTrainerPtr(_target_fight_side_ptr, 0);
    if (_target_fight_trainer_ptr == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightSideSelectHostEnemy(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_side_ptr = fightTargetGetPtrAsNowFightType(5, 0);
    if (_target_fight_side_ptr == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightSideSelectHost(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _target_fight_side_ptr = fightTargetGetPtrAsNowFightType(4, 0);
    if (_target_fight_side_ptr == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightFloorEditTenkou(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightWazaEdit(void) {
    s32 id;

    if (fightIsFight() == 0) {
        return -1;
    }
    for (;;) {
        id = dbgMenuFightGetWazaDataId(_dbgmenu_fight_waza_edit_waza_data_id);
        if (id < 0) {
            return 1;
        }
        _dbgmenu_fight_waza_edit_waza_data_id = id;
        dbgMenuFightWazaEditSub(id);
    }
}

s32 dbgMenuFightFlagEdit(void) {
    s32 value;
    u8 allOperate;
    u8 debugOpen;
    u8 effectAnim;
    u8 aiFlowDisp;
    u8 soubikouka;
    u16 yubiwohuru;
    u8 aiLastValue;
    u8 msgKeyWait;
    u8 tuikakouka;
    u8 msgSpeed;
    s32 waza;
    s32 result;
    s8 answer;

    msgSpeed = dbgMenuFightGetMsgSpeed();
    tuikakouka = dbgMenuFightGetTuikakoukaFlag();
    msgKeyWait = dbgMenuFightGetMsgKeyWaitFlag();
    allOperate = dbgMenuFightGetAllFightTrainerOperateFlag();
    debugOpen = dbgMenuFightGetFightDebugMenuOpenFlag();
    effectAnim = fightSeqGetEffectAminFlag();
    aiFlowDisp = dbgMenuFightGetFightTrainerAiFlowDispFlag();
    soubikouka = dbgMenuFightGetSoubikoukaFlag();
    yubiwohuru = dbgMenuFightGetYubiwohuruWazaDataId();
    aiLastValue = dbgMenuFightGetFightTrainerAiLastValueReviseFlag();
    dbgMenuFightGetFightPokeStMenuOpenFlag();

    for (;;) {
        result = menuOpenCustom(0xE, 0, 0, 0, 1, 0, 0);
        if (result == -1) {
            menuCloseCustom(0xE, 0, 1);
            dbgMenuFightSetMsgSpeed(msgSpeed);
            dbgMenuFightSetTuikakoukaFlag(tuikakouka);
            dbgMenuFightSetMsgKeyWaitFlag(msgKeyWait);
            dbgMenuFightSetAllFightTrainerOperateFlag(allOperate);
            dbgMenuFightSetFightDebugMenuOpenFlag(debugOpen);
            fightSeqSetEffectAminFlag(effectAnim);
            dbgMenuFightSetFightTrainerAiFlowDispFlag(aiFlowDisp);
            dbgMenuFightSetSoubikoukaFlag(soubikouka);
            dbgMenuFightSetYubiwohuruWazaDataId(yubiwohuru);
            dbgMenuFightSetFightTrainerAiLastValueReviseFlag(aiLastValue);
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        if (result == 0x72) {
            answer = menuSubOpenYesNo(0x7F, -1, -1, dbgMenuFightGetTuikakoukaFlag() == 0);
            if (answer == 0) {
                dbgMenuFightSetTuikakoukaFlag(1);
            } else if (answer == 1) {
                dbgMenuFightSetTuikakoukaFlag(0);
            }
        } else if (result == 0x76) {
            if (menuSubOpenNumberInput(dbgMenuFightGetMsgSpeed(), &value, 1, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
            } else {
                dbgMenuFightSetMsgSpeed(value);
                menuSubCloseNumberInput();
            }
        } else if (result == 0x78) {
            answer = menuSubOpenYesNo(0x7F, -1, -1, dbgMenuFightGetMsgKeyWaitFlag() == 0);
            if (answer == 0) {
                dbgMenuFightSetMsgKeyWaitFlag(1);
            } else if (answer == 1) {
                dbgMenuFightSetMsgKeyWaitFlag(0);
            }
        } else if (result == 0x7A) {
            answer = menuSubOpenYesNo(0x7F, -1, -1, fightSeqGetEffectAminFlag() == 0);
            if (answer == 0) {
                fightSeqSetEffectAminFlag(1);
            } else if (answer == 1) {
                fightSeqSetEffectAminFlag(0);
            }
        } else if (result == 0x7C) {
            answer = menuSubOpenYesNo(0x7F, -1, -1, dbgMenuFightGetAllFightTrainerOperateFlag() == 0);
            if (answer == 0) {
                dbgMenuFightSetAllFightTrainerOperateFlag(1);
            } else if (answer == 1) {
                dbgMenuFightSetAllFightTrainerOperateFlag(0);
            }
        } else if (result == 0x7E) {
            answer = menuSubOpenYesNo(0x7F, -1, -1, dbgMenuFightGetFightDebugMenuOpenFlag() == 0);
            if (answer == 0) {
                dbgMenuFightSetFightDebugMenuOpenFlag(1);
            } else if (answer == 1) {
                dbgMenuFightSetFightDebugMenuOpenFlag(0);
            }
        } else if (result == 0x80) {
            answer = menuSubOpenYesNo(0x7F, -1, -1, dbgMenuFightGetFightTrainerAiFlowDispFlag() == 0);
            if (answer == 0) {
                dbgMenuFightSetFightTrainerAiFlowDispFlag(1);
            } else if (answer == 1) {
                dbgMenuFightSetFightTrainerAiFlowDispFlag(0);
            }
        } else if (result == 0x74) {
            answer = menuSubOpenYesNo(0x7F, -1, -1, dbgMenuFightGetSoubikoukaFlag() == 0);
            if (answer == 0) {
                dbgMenuFightSetSoubikoukaFlag(1);
            } else if (answer == 1) {
                dbgMenuFightSetSoubikoukaFlag(0);
            }
        } else if (result == 0x82) {
            if (fightIsFight() != 0) {
                waza = dbgMenuFightGetYubiwohuruWazaDataId();
                for (;;) {
                    waza = dbgMenuFightGetWazaDataId((u16)waza);
                    if (waza < 0) {
                        break;
                    }
                    if (fightSeqCheckYubiwohuruWazaDataId(waza) == 1) {
                        dbgMenuFightSetYubiwohuruWazaDataId(waza);
                        break;
                    }
                }
            }
        } else if (result == 0x84) {
            answer = menuSubOpenYesNo(0x7F, -1, -1, dbgMenuFightGetFightTrainerAiLastValueReviseFlag() == 0);
            if (answer == 0) {
                dbgMenuFightSetFightTrainerAiLastValueReviseFlag(1);
            } else if (answer == 1) {
                dbgMenuFightSetFightTrainerAiLastValueReviseFlag(0);
            }
        } else if (result == 0x86) {
            answer = menuSubOpenYesNo(0x7F, -1, -1, dbgMenuFightGetFightPokeStMenuOpenFlag() == 0);
            if (answer == 0) {
                dbgMenuFightSetFightPokeStMenuOpenFlag(1);
            } else if (answer == 1) {
                dbgMenuFightSetFightPokeStMenuOpenFlag(0);
            }
        }
    }
    menuCloseCustom(0xE, 0, 1);
    return 1;
}

s32 dbgMenuFightStop(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightFloorEdit(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightEncountSelect(void) {
    s32 id;
    u32 deck;
    u32 loaded;
    s32 encountId;
    u16 i;

    loaded = 0;
    _readEncountDataName = (u32*)GSmemAlloc(0x1200);
    _readEncountDataID = (u16*)GSmemAlloc(0x600);
    for (;;) {
        id = dbgMenuFightGetFightDeckDataId(_dbgmenu_fight_deck_data_id);
        if (id < 0) {
            break;
        }
        _dbgmenu_fight_deck_data_id = id;
        if (fightIsFight() == 0) {
            fightFreeResourceDeclArchive();
            GSfsysFreeCache(0x842);
            fightFreeResourceID(10, 0x184D3400);
            fightReadResourceID(0x842, 0x184D3400);
            loaded = fightReadResourceID(0x842, getDeckResourceID(id));
            if (loaded == 1) {
                deck = id;
            }
            _readEncountDataCnt = 0;
            for (i = 0; i < *fight_encount_data_number; i++) {
                if (id == fightEncountDataBiosGetFightDeckGrpId(fightEncountDataBiosGetPtr(i), 1)) {
                    _readEncountDataName[_readEncountDataCnt] = fightEncountDataBiosGetFightName(fightEncountDataBiosGetPtr(i));
                    _readEncountDataID[_readEncountDataCnt] = i;
                    _readEncountDataCnt++;
                }
            }
        }
        for (;;) {
            switch (deck) {
            case 1:
                encountId = _dbgmenu_fight_story_encount_data_id;
                break;
            case 2:
                encountId = _dbgmenu_fight_hundred_encount_data_id;
                break;
            case 3:
                encountId = _dbgmenu_fight_imasugu_encount_data_id;
                break;
            case 4:
                encountId = _dbgmenu_fight_virtual_encount_data_id;
                break;
            case 5:
                encountId = _dbgmenu_fight_bingo_encount_data_id;
                break;
            case 6:
                encountId = _dbgmenu_fight_colosseum_encount_data_id;
                break;
            case 7:
                encountId = _dbgmenu_fight_sample_encount_data_id;
                break;
            }
            if ((u16)encountId > _readEncountDataCnt) {
                encountId = _readEncountDataCnt;
            }
            id = dbgMenuFightGetFightEncountDataId(encountId);
            if (id < 0) {
                break;
            }
            switch (deck) {
            case 1:
                _dbgmenu_fight_story_encount_data_id = id;
                break;
            case 2:
                _dbgmenu_fight_hundred_encount_data_id = id;
                break;
            case 3:
                _dbgmenu_fight_imasugu_encount_data_id = id;
                break;
            case 4:
                _dbgmenu_fight_virtual_encount_data_id = id;
                break;
            case 5:
                _dbgmenu_fight_bingo_encount_data_id = id;
                break;
            case 6:
                _dbgmenu_fight_colosseum_encount_data_id = id;
                break;
            case 7:
                _dbgmenu_fight_sample_encount_data_id = id;
                break;
            }
            if (_readEncountDataID[id - 1] == 0) {
                break;
            }
            if (dbgMenuFightEncountDataEditSub(_readEncountDataID[id - 1]) < 0) {
                continue;
            }
            if (fightIsFight() != 0) {
                break;
            }
            dbgMenuFightEncount(_readEncountDataID[id - 1]);
            GSmemFree(_readEncountDataName);
            GSmemFree(_readEncountDataID);
            if (loaded == 1) {
                fightFreeResourceID(0x842, getDeckResourceID(deck));
            }
            return 0;
        }
    }
    if (loaded == 1) {
        fightFreeResourceID(0x842, getDeckResourceID(deck));
    }
    GSmemFree(_readEncountDataName);
    GSmemFree(_readEncountDataID);
    return -1;
}

s32 dbgMenuFightEncount(u16 id) {
    void* thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (void*)fightEncount);
    if (thread != 0) {
        GSthreadSetArgs(thread, 1, id);
        GSthreadSetName(thread, "fightEnc(Debug)");
    }
    return 0;
}

s32 dbgMenuFightMain(void) {
    return 1;
}

void dbgMenuFightSetYubiwohuruWazaDataId(u16 id) {
    _yubiwohuru_waza_data_id = id;
}

void dbgMenuFightSetSoubikoukaFlag(u8 flag) {
    _soubikakouka_flag = flag;
}

u16 dbgMenuFightGetYubiwohuruWazaDataId(void) {
    return _yubiwohuru_waza_data_id;
}

u8 dbgMenuFightGetSoubikoukaFlag(void) {
    return _soubikakouka_flag;
}

void dbgMenuFightSetFightPokeStMenuOpenFlag(u8 flag) {
    _fight_pokemon_status_menu_open_flag = flag;
}

u8 dbgMenuFightGetFightPokeStMenuOpenFlag(void) {
    return _fight_pokemon_status_menu_open_flag;
}

void dbgMenuFightSetFightTrainerAiLastValueReviseFlag(u8 flag) {
    _fight_trainer_ai_last_value_revise_flag = flag;
}

u8 dbgMenuFightGetFightTrainerAiLastValueReviseFlag(void) {
    return _fight_trainer_ai_last_value_revise_flag;
}

void dbgMenuFightSetFightTrainerAiFlowDispFlag(u8 flag) {
    _fight_trainer_ai_flow_disp_flag = flag;
}

u8 dbgMenuFightGetFightTrainerAiFlowDispFlag(void) {
    return _fight_trainer_ai_flow_disp_flag;
}

void dbgMenuFightSetFightDebugMenuOpenFlag(u8 flag) {
    _fight_debug_menu_open_flag = flag;
}

u8 dbgMenuFightGetFightDebugMenuOpenFlag(void) {
    return _fight_debug_menu_open_flag;
}

void dbgMenuFightSetAllFightTrainerOperateFlag(u8 flag) {
    _all_fight_trainer_operate_flag = flag;
}

u8 dbgMenuFightGetAllFightTrainerOperateFlag(void) {
    return _all_fight_trainer_operate_flag;
}

void dbgMenuFightSetMsgKeyWaitFlag(u8 flag) {
    _msg_key_wait_flag = flag;
}

u8 dbgMenuFightGetMsgKeyWaitFlag(void) {
    return _msg_key_wait_flag;
}

void dbgMenuFightSetTuikakoukaFlag(u8 flag) {
    _tuikakouka_flag = flag;
}

u8 dbgMenuFightGetTuikakoukaFlag(void) {
    return _tuikakouka_flag;
}

void dbgMenuFightSetMsgSpeed(u8 speed) {
    if (speed < 1) {
        speed = 1;
    }
    if (speed > 9) {
        speed = 9;
    }
    _msg_speed = speed;
}

u8 dbgMenuFightGetMsgSpeed(void) {
    return _msg_speed;
}

u32 dbgMenuFightGetMsgSpeedToFrame(u32 frames) {
    u8 buf[10] = {0, 10, 25, 50, 75, 100, 125, 150, 175, 200};
    u8 speed;
    u32 changed;
    u32 pressed;

    speed = dbgMenuFightGetMsgSpeed();
    if (winMsgCloseCheckFight() == 1) {
        frames = frames * buf[speed] / 100;
        if (dbgMenuFightGetMsgKeyWaitFlag() == 1) {
            frames = 0;
            for (;;) {
                changed = GSinputButtonsChanged(1);
                pressed = GSinputButtonsPressed(1);
                if ((pressed & changed) & 0x100) {
                    break;
                }
                GSthreadSwitch();
            }
        }
    }
    return frames;
}

s32 dbgMenuFightGetFightTrainerAiAddsubValueDataId(u32 id, u8 close) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, (void* (*)(u32))_dbgMenuFightGetFightTrainerAiAddsubValueDataIdSub) == 0) {
        return -1;
    }
    if (value > *fight_trainer_ai_value_addsub_data_number) {
        value = *fight_trainer_ai_value_addsub_data_number - 1;
    }
    if (close == 1) {
        menuSubCloseNumberInput();
    }
    return value;
}

static void* _dbgMenuFightGetFightTrainerAiAddsubValueDataIdSub(u32 id) {
    u32 a;
    u32 b;
    u32 c;
    u32 d;

    if (id >= *fight_trainer_ai_value_addsub_data_number) {
        d = 0;
        a = 0xEB63;
        b = 0xEB63;
        c = 0xEB63;
    } else {
        a = fightTrainerGetStatus(0, (u16)id, 0x40, 0);
        b = fightTrainerGetStatus(0, (u16)id, 0x41, 0);
        c = fightTrainerGetStatus(0, (u16)id, 0x3F, 0);
        d = fightTrainerGetStatus(0, (u16)id, 0x3E, 0);
    }
    if (c == 0) {
        c = 0xEB63;
    }
    if (a == 0) {
        a = 0xEB63;
    }
    if (b == 0) {
        b = 0xEB63;
    }
    msgctrlSetValue(0xD, GSmsgGetGSchar(a));
    msgctrlSetValue(0xE, GSmsgGetGSchar(b));
    msgctrlSetValue(0x4D, GSmsgGetGSchar(c));
    msgctrlSetValue(0x2F, (void*)d);
    return GSmsgGetGSchar(0xF159);
}

s32 dbgMenuFightGetFightTrainerPokemonPartDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, (void* (*)(u32))_dbgMenuFightGetFightTrainerPokemonPartDataIdSub) == 0) {
        return -1;
    }
    if (value >= *fight_trainer_pokemon_part_data_number) {
        value = *fight_trainer_pokemon_part_data_number - 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetFightTrainerPokemonPartDataIdSub(u32 id) {
    if (id == 0) {
        return GSmsgGetGSchar(0xEB63);
    }
    if (id >= *fight_trainer_pokemon_part_data_number) {
        return GSmsgGetGSchar(0xEB63);
    }
    return GSmsgGetGSchar(fightTrainerGetStatus(0, (u16)id, 0xB, 0));
}

s32 dbgMenuFightGetWazaDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, (void* (*)(u32))_dbgMenuFightGetWazaDataIdSub) == 0) {
        return -1;
    }
    if (value >= 0x163) {
        value = 0x162;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetWazaDataIdSub(u32 id) {
    if (id == 0) {
        return GSmsgGetGSchar(0xEB63);
    }
    if (id >= 0x163) {
        return GSmsgGetGSchar(0xEB63);
    }
    return GSmsgGetGSchar((u32)wazaGetStatus(0, (u16)id, 1, 0));
}

s32 dbgMenuFightGetWazaTypeId(u8 type) {
    u32 value;

    if (menuSubOpenNumberInputID(type, &value, (void* (*)(u32))_dbgMenuFightGetWazaTypeIdSub) == 0) {
        return -1;
    }
    if (value > 0xD) {
        value = 0xD;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetWazaTypeIdSub(u32 type) {
    if (type == 0) {
        return GSmsgGetGSchar(0xEB63);
    }
    if (type > 0xD) {
        return GSmsgGetGSchar(0xEB63);
    }
    return GSmsgGetGSchar((u32)wazaGetWazaTypeIdName((u8)type));
}

s32 dbgMenuFightGetZokuseiDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, (void* (*)(u32))_dbgMenuFightGetZokuseiDataIdSub) == 0) {
        return -1;
    }
    if (value >= *zokusei_data_number) {
        value = *zokusei_data_number - 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetZokuseiDataIdSub(u32 id) {
    if (id == 9) {
        return GSmsgGetGSchar(0xEB63);
    }
    if (id >= *zokusei_data_number) {
        return GSmsgGetGSchar(0xEB63);
    }
    return GSmsgGetGSchar(zokuseiBiosGetName((u16)id));
}

s32 dbgMenuFightGetGsinputDevId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, (void* (*)(u32))_dbgMenuFightGetGsinputDevIdSub) == 0) {
        return -1;
    }
    if (value >= 5) {
        value = 4;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetGsinputDevIdSub(u32 id) {
    u32 msg;

    if ((s32)id >= 5) {
        msg = 0xEB63;
    } else {
        msg = dbgMenuGetGsinputMsgId(id);
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    return GSmsgGetGSchar(msg);
}

s32 dbgMenuFightGetFightTrainerDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, (void* (*)(u32))_dbgMenuFightGetFightTrainerDataIdSub) == 0) {
        return -1;
    }
    if (value > _readEncountDataCnt && value < 0x1388) {
        value = _readEncountDataCnt;
    }
    if (value > 0x138E) {
        value = 0x138E;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetFightTrainerDataIdSub(u32 id) {
    u32 msg;

    if (id >= deckGetTrainerSize()) {
        msg = 0xEB63;
    } else {
        msg = fightTrainerGetStatus(0, (u16)id, 3, 0);
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    switch (id) {
    case 0x1388:
        msg = 0xED00;
        break;
    case 0x1389:
        msg = 0xF60A;
        break;
    case 0x138A:
        msg = 0xF60B;
        break;
    case 0x138B:
        msg = 0xF60C;
        break;
    case 0x138C:
        msg = 0xF60D;
        break;
    case 0x138D:
        msg = 0xF60E;
        break;
    case 0x138E:
        msg = 0xF60F;
        break;
    }
    return GSmsgGetGSchar(msg);
}

s32 dbgMenuFightGetPokemonEntry(u8 entry) {
    u32 value;

    if (menuSubOpenNumberInputID(entry, &value, (void* (*)(u32))_dbgMenuFightGetPokemonEntrySub) == 0) {
        return -1;
    }
    if (value > 6) {
        value = 6;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetPokemonEntrySub(u32 id) {
    u32 msg = id;

    if (msg > 6) {
        msg = 0xEB63;
    } else {
        switch (msg) {
        case 1:
            msg = 0xF604;
            break;
        case 2:
            msg = 0xF605;
            break;
        case 3:
            msg = 0xF606;
            break;
        case 4:
            msg = 0xF607;
            break;
        case 5:
            msg = 0xF608;
            break;
        case 6:
            msg = 0xF609;
            break;
        }
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    return GSmsgGetGSchar(msg);
}

s32 dbgMenuFightGetPokemonFightType(u8 type) {
    u32 value;

    if (menuSubOpenNumberInputID(type, &value, (void* (*)(u32))_dbgMenuFightGetPokemonFightTypeSub) == 0) {
        return -1;
    }
    if (value > 2) {
        value = 2;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetPokemonFightTypeSub(u32 id) {
    u32 msg = id;

    if (msg > 2) {
        msg = 0xEB63;
    } else {
        switch (msg) {
        case 1:
            msg = 0xF602;
            break;
        case 2:
            msg = 0xF603;
            break;
        }
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    return GSmsgGetGSchar(msg);
}

s32 dbgMenuFightGetFightTypeDataId(u8 type) {
    u32 value;

    if (menuSubOpenNumberInputID(type, &value, (void* (*)(u32))_dbgMenuFightGetFightTypeDataIdSub) == 0) {
        return -1;
    }
    if (value > 2) {
        value = 2;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetFightTypeDataIdSub(u32 id) {
    u32 msg = id;

    if (msg > 2) {
        msg = 0xEB63;
    } else {
        switch (msg) {
        case 0:
            msg = 0xF5FF;
            break;
        case 1:
            msg = 0xF600;
            break;
        case 2:
            msg = 0xF601;
            break;
        }
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    return GSmsgGetGSchar(msg);
}

s32 dbgMenuFightGetFightKindDataId(u8 kind) {
    u32 value;

    if (menuSubOpenNumberInputID(kind, &value, (void* (*)(u32))_dbgMenuFightGetFightKindDataIdSub) == 0) {
        return -1;
    }
    if (value >= *fight_kind_data_number) {
        value = *fight_kind_data_number - 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetFightKindDataIdSub(u32 id) {
    u32 msg;

    if (id >= *fight_kind_data_number) {
        msg = 0xEB63;
    } else {
        msg = fightKindDataBiosGetName(fightKindDataBiosGetPtr((u16)id));
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    return GSmsgGetGSchar(msg);
}

s32 dbgMenuFightGetFightFloorDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, (void* (*)(u32))_dbgMenuFightGetFightFloorDataIdSub) == 0) {
        return -1;
    }
    if (value >= *fight_floor_data_number) {
        value = *fight_floor_data_number - 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetFightFloorDataIdSub(u32 id) {
    u32 msg;

    if (id >= *fight_floor_data_number) {
        msg = 0xEB63;
    } else {
        msg = fightFloorGetStatus(0, (u16)id, 1, 0);
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    return GSmsgGetGSchar(msg);
}

s32 dbgMenuFightGetFightDeckDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, (void* (*)(u32))_dbgMenuFightGetFightDeckDataIdSub) == 0) {
        return -1;
    }
    if (value >= deck_group_data_number) {
        value = deck_group_data_number - 1;
    }
    if (value == 0) {
        value = 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void* _dbgMenuFightGetFightDeckDataIdSub(u32 id) {
    u32 msg;

    if (id == 0) {
        msg = 0xEB63;
    } else if (id >= deck_group_data_number) {
        msg = 0xEB63;
    } else {
        msg = deck_group_data[id];
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    return GSmsgGetGSchar(msg);
}

s32 dbgMenuFightGetFightEncountDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, (void* (*)(u32))_dbgMenuFightGetFightEncountDataIdSub) == 0) {
        return -1;
    }
    if (value > _readEncountDataCnt) {
        value = _readEncountDataCnt;
    }
    if (value == 0) {
        value = 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetFightEncountDataIdSub(u32 id) {
    static s16 strbuf[0x40];
    s16 bracket;
    u32 msg;
    void* deckMsg;

    if (id >= 1 && id <= _readEncountDataCnt) {
        msg = _readEncountDataName[id - 1];
    } else {
        msg = 0xEB63;
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    if (id <= _readEncountDataCnt) {
        deckMsg = getDeckMsgID(_readEncountDataID[id - 1], 1);
        GScharMakeFromSJIS(strbuf, "[");
        GScharMakeFromSJIS(&strbuf[1], (const char*)deckMsg);
        GScharMakeFromSJIS(&bracket, "]");
        GScharCat(strbuf, &bracket);
    } else {
        strbuf[0] = 0;
    }
    GScharCat(strbuf, GSmsgGetGSchar(msg));
}

}
