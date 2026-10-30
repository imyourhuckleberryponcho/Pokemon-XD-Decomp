#include <dolphin/types.h>
#pragma pool_strings off
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct FIGHT_ENCOUNT;
struct FIGHT_FLOOR;
struct FightEncountData;
enum FloorEnterMode { FloorEnterMode_draft_dummy };
struct FloorModuleInterface;
enum FloorStateMode { FloorStateMode_draft_dummy };
struct GSthread;

extern "C" {

extern "C" {
struct FIGHT_ENCOUNT {
    u8 _draft[1];
    s16 getMsg(unsigned char) const;
    u32 getRoundNo() const;
    s32 getFightMode() const;
    s32 getDestroyFlag() const;
    u8 getTrainerKind() const;
    u16 getField() const;
};
struct FIGHT_FLOOR {
    u8 _draft[1];
};
struct FightEncountData {
    u8 _draft[1];
};
struct FloorModuleInterface {
    u8 _draft[1];
};
struct GSthread {
    u8 _draft[1];
};

extern "C" {
void FloorModuleInterface_clear(FloorModuleInterface*);
s32 GSfloorGetCurrentFloorGroupID(void);
u8 GSfloorIsPop(void);
void GSfsysFree(u32 id);
void GSfsysFreeCache(s32 group);
s32 GSfsysReadIDEXWait(u32 id, u32 idx, s32 a, s32 b, s32 c);
void GSlogWrite(const char*, ...);
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
void GSresFreeResource(u32 grp, u32 id);
void* GSresGetResource(u32 grp, u32 id);
void* GSthreadCreate(s32, s32, s32, s32, s32, void (*)(void));
void GSthreadSetName(GSthread*, const char*);
s32 GSthreadTerminateGroup();
u32 HSD_Rand(void);
static void __sinit_fight_cpp();
s32 battleCameraStartRandom(s32);
u8 cameraGetType(void);
u8 cameraSetType(u8 type);
void dbgMenuClose(void);
u8 dbgMenuGetEnable(void);
void dbgMenuSetEnable(u8 enable);
s32 fightActionCreateAndFlowFifo(s32*, s32, s32, s32, s32, s32*);
s32 fightActionDispFifoAll();
s32 fightActionFifoInit();
void fightCloseAllMenu();
void fightDataRewrite();
u16 fightEncountDataBiosGetDiskId(FightEncountData* data);
u16 fightEncountDataBiosGetFightDeckGrpId(FightEncountData* data, u8 index);
u16 fightEncountDataBiosGetFightFloorDataId(FightEncountData* data);
u8 fightEncountDataBiosGetFightKind(FightEncountData* data);
u16 fightEncountDataBiosGetFightTrainerDataId(FightEncountData* data, u8 index);
FightEncountData* fightEncountDataBiosGetPtr(u16 id);
void fightEncountDataBiosSetFightFloorDataId(FightEncountData* data, u16 value);
void fightEncountDataBiosSetFightKind(FightEncountData* data, u8 value);
void fightEncountDataBiosSetFightTrainerDataId(FightEncountData* data, u8 index, u16 id);
void fightEncountDataBiosSetSyoukaiWzxDataId(FightEncountData* data, u32 value);
void fightEncountDataBiosSetZenmetuFlag(FightEncountData* data, u8 value);
s32 fightEncountGetStrObj();
FIGHT_FLOOR* fightFloorGetNowPtr(void);
u8 fightFloorIsNowEncountHostEnemyPokemonKime(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountHostPokemonKime(FIGHT_FLOOR* floor);
u8 fightFloorIsNowEncountSnatchOnly(FIGHT_FLOOR* floor);
u32 fightFloor_GetEnvSndId(FIGHT_FLOOR* floor);
s32 fightFloor_GetFightType(FIGHT_FLOOR* floor);
s8 fightFloor_GetStatusMenuCnt(u8 status);
void fightFloor_SetStatusMenuCnt(u8 status, s8 cnt);
void fightFreeDeck(u16 id);
void fightFreeResourceDeclArchive();
void fightFreeResourceID(s32 p0, s32 p1);
s32 fightGSfloorFree();
s32 fightGSfloorGetPushDataSize();
s32 fightGSfloorPopData(s32, s32);
s32 fightGSfloorPushData(s32, s32);
u16 fightGetFightEncountDataId(void);
void fightInit();
void fightMenuCloseMsg(void);
void fightPokemonSetNonTrainerPokemonIsActiveFlag(u8 flag);
s32 fightReadDeck(u16 id);
bool fightReadResourceID(s32 p0, s32 p1);
s32 fightSeqEventKurein(s32);
void fightSeq_ClearUserWork(void);
void fightSetFightEncountDataId(u16 value);
void fightSetFightFlag(u8 value);
void fightSetFightResultId(u16 value);
void fightSetGsthreadPtrFightMain(u32 value);
void fightSetMenuCtrlHero(s32 p0);
void fightTrainerDB_SetKindDataId(u16 id, u8 v);
void fightTrainerDB_SetSerihuMsgId(u16 id, u8 index, u16 v);
void* memcpy(void* dst, const void* src, size_t n);
void menuCloseCustom(s32 menuID, s32, s32);
s32 menuFightCloseAll();
bool menuIsCheck(s32 menuID);
void msgctrlSetValue(s32 id, u32 value);
s32 pokecoloGetCountryCode(void);
void soundOpenPlay(s32, s32, s32);
s32 soundStop(s32, u32 a1 = 0);
extern s32 ServerWork;
extern void* UserWork;
void fightMain();
extern s32 fight_action_data_kaisi[];
extern s16 msgFrame;
extern s8 underTakerDeckRand;
extern s32 jtbl_2044;
}
extern "C++" {
static void _fightFinalize(unsigned int p0, FloorEnterMode p1);
static void _fightFree(unsigned int p0, FloorEnterMode p1);
static s32* _fightGetModuleName();
static s32 _fightGetStateSize(FloorStateMode p0);
static s32 _fightGetUID();
static void _fightInitialize(unsigned int p0, FloorEnterMode p1);
static void _fightMakeStateData(FloorStateMode p0, void* p1, unsigned long p2);
static void _fightRestoreStateData(FloorStateMode p0, void* p1, unsigned long p2);
static void _fightUpdate(unsigned int p0, FloorEnterMode p1);
static void _fsysLoadCallbak(long p0, void* p1, long p2);
void* deckDataVirtual_GetPtr(unsigned short);
}
static s32 fight_action[0xC];
static u8 _floorModuleFight[0x2C];
static u8 _menuCtrlHero[0x978];
static u32 _gsthread_ptr_fight_main;
static u8 _is_fight_flag;
static u16 _fight_result_id;
static u16 _fight_encount_data_id;
static u8 _old_fight_debug_menu_flag;
static u8 gOldCameraType;
u32 dbgEffLoadFsysGroupID;
}
}

extern "C" {
static void __sinit_fight_cpp() {
}
}

extern "C" {
u8 fightIsFight(void) {
    return _is_fight_flag;
}
}

extern "C" {
void fightSetFightFlag(u8 value) {
    _is_fight_flag = value;
}
}

extern "C" {
u16 fightGetFightResultId(void) {
    return _fight_result_id;
}
}

extern "C" {
void fightSetFightResultId(u16 value) {
    _fight_result_id = value;
}
}

extern "C" {
void fightSetGsthreadPtrFightMain(u32 value) {
    _gsthread_ptr_fight_main = value;
}
}

extern "C" {
u16 fightGetFightEncountDataId(void) {
    return _fight_encount_data_id;
}
}

extern "C" {
void fightSetFightEncountDataId(u16 value) {
    _fight_encount_data_id = value;
}
}

extern "C" {
void fightInit() {
    fightSetFightFlag(0);
    fightSetFightResultId(0U);
    fightSetFightEncountDataId(0);
    fightSetGsthreadPtrFightMain(0);
    FloorModuleInterface_clear((FloorModuleInterface*)(&_floorModuleFight));
    M2C_FIELD(&_floorModuleFight, void (**)(u32, s32), 4) = (void (*)(unsigned long, long))(_fightInitialize);
    M2C_FIELD(&_floorModuleFight, void (**)(u32, s32), 8) = (void (*)(unsigned long, long))(_fightUpdate);
    M2C_FIELD(&_floorModuleFight, void (**)(u32, s32), 0x10) = (void (*)(unsigned long, long))(_fightFinalize);
    M2C_FIELD(&_floorModuleFight, void (**)(u32, s32), 0x14) = (void (*)(unsigned long, long))(_fightFree);
    M2C_FIELD(&_floorModuleFight, void (**)(s32, void *, u32), 0x1C) = (void (*)(long, void *, unsigned long))(_fightMakeStateData);
    M2C_FIELD(&_floorModuleFight, void (**)(s32, void *, u32), 0x20) = (void (*)(long, void *, unsigned long))(_fightRestoreStateData);
    M2C_FIELD(&_floorModuleFight, s32 (**)(s32), 0x24) = (long (*)(long))(_fightGetStateSize);
    M2C_FIELD(&_floorModuleFight, s32 (**)(), 0x28) = _fightGetUID;
    M2C_FIELD(&_floorModuleFight, s32 *(**)(), 0x18) = _fightGetModuleName;
}
}

extern "C++" {
#pragma optimize_for_size on
static void _fightInitialize(unsigned int p0, FloorEnterMode p1) {
    GSthread* thread;

    if (GSfloorIsPop()) {
        dbgMenuClose();
        dbgMenuSetEnable(0U);
        return;
    }
    GSlogWrite("---------- fight start !! ---------- \n");
    fightSetFightFlag(1);
    fightReadDeck(fightGetFightEncountDataId());
    if ((u8 *) UserWork == NULL) {
        UserWork = GSmemAlloc(0x20000U);
        fightSeq_ClearUserWork();
    }
    fightPokemonSetNonTrainerPokemonIsActiveFlag(1U);
    fightDataRewrite();
    battleCameraStartRandom(1);
    _old_fight_debug_menu_flag = dbgMenuGetEnable();
    dbgMenuClose();
    dbgMenuSetEnable(0U);
    fightActionFifoInit();
    gOldCameraType = cameraGetType();
    fightActionCreateAndFlowFifo(fight_action, 0, 0, 1, 0, fight_action_data_kaisi);
    if (fightFloorIsNowEncountSnatchOnly((FIGHT_FLOOR*)(NULL)) == 1) {
        fightSeqEventKurein(0);
        fightSeqEventKurein(1);
    }
    fightActionCreateAndFlowFifo(fight_action, 0, 0, 3, 5, fight_action_data_kaisi);
    if (fightFloorIsNowEncountHostEnemyPokemonKime((FIGHT_FLOOR*)(NULL)) == 1) {
        fightActionCreateAndFlowFifo(fight_action, 0, 0, 4, 5, fight_action_data_kaisi);
    }
    fightActionCreateAndFlowFifo(fight_action, 0, 0, 3, 4, fight_action_data_kaisi);
    if (fightFloorIsNowEncountHostPokemonKime((FIGHT_FLOOR*)(NULL)) == 1) {
        fightActionCreateAndFlowFifo(fight_action, 0, 0, 4, 4, fight_action_data_kaisi);
    }
    fightActionDispFifoAll();
    thread = (GSthread*)GSthreadCreate(0x14, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 0, (void (*)(void))fightMain);
    _gsthread_ptr_fight_main = (unsigned long)thread;
    GSthreadSetName(thread, "fightMain");
}
#pragma optimize_for_size reset
}

extern "C++" {
#pragma optimize_for_size on
static void _fightUpdate(unsigned int, FloorEnterMode) {
    u8 menu;
    u8 i;
    s8 cnt;

    fightFloorGetNowPtr();
    fightFloor_GetFightType(NULL);
    u8 menus[4] = { 0x37, 0x38, 0x40, 0x41 };
    for (i = 0; i < 4; i++) {
        menu = menus[i];
        cnt = fightFloor_GetStatusMenuCnt((s32)menu);
        if (cnt >= 0) {
            cnt--;
            fightFloor_SetStatusMenuCnt(menu, cnt);
            if (cnt <= 0) {
                if (menuIsCheck(menu) == 0) {
                    return;
                }
                menuCloseCustom(menu, 2, 0);
                fightFloor_SetStatusMenuCnt(menu, -1);
            }
        }
    }
    if (M2C_FIELD(&ServerWork, u8 *, 7) == 2) {
        if (msgFrame-- <= 0) {
            fightMenuCloseMsg();
            M2C_FIELD(&ServerWork, u8 *, 7) = 0;
        }
    }
}
#pragma optimize_for_size reset
}

extern "C++" {
static void _fightFinalize(unsigned int p0, FloorEnterMode p1) {
    u32 temp_r3;

    if (p1 != 1) {
        GSfloorGetCurrentFloorGroupID();
        GSthreadTerminateGroup();
        GSfloorGetCurrentFloorGroupID();
        GSthreadTerminateGroup();
        fightCloseAllMenu();
        cameraSetType(gOldCameraType);
        temp_r3 = fightFloor_GetEnvSndId((FIGHT_FLOOR*)(NULL));
        if (temp_r3 != 0) {
            soundStop((s32) temp_r3);
        }
        soundOpenPlay(8, 0, 0xFF);
        if ((u8 *) UserWork != NULL) {
            GSmemFree((void*)(UserWork));
            UserWork = NULL;
        }
        dbgMenuSetEnable(_old_fight_debug_menu_flag);
        fightSetFightFlag(0);
        fightFreeDeck(fightGetFightEncountDataId());
        fightSetFightEncountDataId(0);
        msgctrlSetValue(0x59, 0x1772U);
        GSlogWrite((const char*)("---------- fight end !! ---------- \n"));
    }
}
}

extern "C++" {
static void _fightFree(unsigned int p0, FloorEnterMode p1) {
    if (p1 == 1) {
        fightGSfloorFree();
    }
}
}

extern "C" {
void fightCloseAllMenu() {
    menuFightCloseAll();
}
}

extern "C++" {
static void _fightMakeStateData(FloorStateMode p0, void* p1, unsigned long p2) {
    if (p0 == 2) {
        fightGSfloorPushData((s32) p1, (s32) p2);
    }
}
}

extern "C++" {
static void _fightRestoreStateData(FloorStateMode p0, void* p1, unsigned long p2) {
    if (p0 == 2) {
        fightGSfloorPopData((s32) p1, (s32) p2);
    }
}
}

extern "C++" {
static s32 _fightGetStateSize(FloorStateMode p0) {
    if (p0 == 2) {
        return fightGSfloorGetPushDataSize();
    }
    return 0;
}
}

extern "C++" {
static s32 _fightGetUID() {
    return 0x12;
}
}

extern "C" {
void* fightGetFloorModule(void) {
    return _floorModuleFight;
}
}

extern "C++" {
static s32* _fightGetModuleName() {
    return (long *)("fight");
}
}

extern "C++" {
static void _fsysLoadCallbak(long p0, void* p1, long p2) {
}
}

extern "C" {
void* fightGetMenuCtrlHero(void) {
    return _menuCtrlHero;
}
}

extern "C" {
void fightSetMenuCtrlHero(s32 p0) {
    memcpy((void*)(&_menuCtrlHero), (const void*)((u8 *) p0), 0x978U);
}
}

extern "C" {
#pragma optimize_for_size on
s32 fightReadDeck(u16 id) {
    FightEncountData* data;
    u8 i;
    s32 ret;
    bool result;

    ret = 0;
    data = fightEncountDataBiosGetPtr(id);
    for (i = 0; i < 4; i++) {
        switch (fightEncountDataBiosGetFightDeckGrpId(data, i)) {
        case 1:
            result = fightReadResourceID(0x842, 0x18503400);
            break;
        case 2:
            result = fightReadResourceID(0x842, 0x184E3400);
            break;
        case 3:
            result = fightReadResourceID(0x842, 0x184F3400);
            break;
        case 4:
            result = fightReadResourceID(0x842, 0x18513400);
            break;
        case 5:
            result = fightReadResourceID(0x842, 0x184B3400);
            break;
        case 6:
            result = fightReadResourceID(0x842, 0x184C3400);
            break;
        case 7:
            result = fightReadResourceID(0x842, 0x195F3400);
            break;
        }
        if (result == 1) {
            ret = 1;
        }
    }
    return ret;
}
#pragma optimize_for_size reset
}

extern "C" {
#pragma optimize_for_size on
void fightFreeDeck(u16 id) {
    FightEncountData* data;
    u8 i;

    data = fightEncountDataBiosGetPtr(id);
    for (i = 0; i < 4; i++) {
        switch (fightEncountDataBiosGetFightDeckGrpId(data, i)) {
        case 1:
            fightFreeResourceID(0x842, 0x18503400);
            break;
        case 2:
            fightFreeResourceID(0x842, 0x184E3400);
            break;
        case 3:
            fightFreeResourceID(0x842, 0x184F3400);
            break;
        case 4:
            fightFreeResourceID(0x842, 0x18513400);
            break;
        case 5:
            fightFreeResourceID(0x842, 0x184B3400);
            break;
        case 6:
            fightFreeResourceID(0x842, 0x184C3400);
            break;
        case 7:
            fightFreeResourceID(0x842, 0x195F3400);
            break;
        }
    }
}
#pragma optimize_for_size reset
}

extern "C" {
#pragma optimize_for_size on
bool fightReadResourceID(s32 fsys, s32 id) {
    if (fsys == 0) {
        fsys = 0x842;
    }
    if (pokecoloGetCountryCode() == 2) {
        switch (id) {
        case 0x184B3400:
            id = 0x22523400;
            break;
        case 0x184C3400:
            id = 0x22533400;
            break;
        case 0x184D3400:
            id = 0x22543400;
            break;
        case 0x184E3400:
            id = 0x22553400;
            break;
        case 0x184F3400:
            id = 0x22563400;
            break;
        case 0x18503400:
            id = 0x22573400;
            break;
        case 0x18513400:
            id = 0x22583400;
            break;
        case 0x195F3400:
            id = 0x22593400;
            break;
        default:
            return 0;
        }
        GSresFreeResource(fsys, 0x22583400);
    } else {
        GSresFreeResource(fsys, 0x18513400);
    }
    GSfsysFreeCache(fsys);
    if (GSresGetResource(fsys, id) != NULL) {
        return 0;
    }
    GSfsysReadIDEXWait(fsys, id, (s32)_fsysLoadCallbak, 0, id);
    GSfsysFree(fsys);
    return GSresGetResource(fsys, id) != NULL;
}
#pragma optimize_for_size reset
}

extern "C" {
#pragma optimize_for_size on
void fightFreeResourceID(s32 p0, s32 p1) {
    s32 id;

    if (pokecoloGetCountryCode() == 2) {
        switch (p1) {
        case 0x184B3400:
            id = 0x22523400;
            break;
        case 0x184C3400:
            id = 0x22533400;
            break;
        case 0x184D3400:
            id = 0x22543400;
            break;
        case 0x184E3400:
            id = 0x22553400;
            break;
        case 0x184F3400:
            id = 0x22563400;
            break;
        case 0x18503400:
            id = 0x22573400;
            break;
        case 0x18513400:
            id = 0x22583400;
            break;
        case 0x195F3400:
            id = 0x22593400;
            break;
        default:
            return;
        }
    } else {
        id = p1;
    }
    GSresFreeResource(p0, id);
}
#pragma optimize_for_size reset
}

extern "C" {
void fightFreeResourceDeclArchive() {
    fightFreeResourceID(0x842, 0x18503400);
    fightFreeResourceID(0x842, 0x184E3400);
    fightFreeResourceID(0x842, 0x184F3400);
    fightFreeResourceID(0x842, 0x18513400);
    fightFreeResourceID(0x842, 0x184B3400);
    fightFreeResourceID(0x842, 0x184C3400);
    fightFreeResourceID(0x842, 0x195F3400);
    fightFreeResourceID(0x842, 0x184D3400);
}
}

extern "C" {
void fightDataRewrite() {
    FIGHT_ENCOUNT* enc;
    FightEncountData* data;
    u16 id;
    u32 trainer;
    u8 kind;
    u8* deck;
    u16 field;
    u8 mode;
    u8 destroy;
    u32 round;
    u8 trainerKind;
    u16 msgs[4];
    u8 i;

    enc = (FIGHT_ENCOUNT*)fightEncountGetStrObj();
    id = fightGetFightEncountDataId();
    data = fightEncountDataBiosGetPtr(id);
    kind = fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(id));
    deck = (u8*)deckDataVirtual_GetPtr(fightEncountDataBiosGetDiskId(data));
    field = enc->getField();
    mode = enc->getFightMode();
    destroy = enc->getDestroyFlag();
    round = enc->getRoundNo();
    trainerKind = enc->getTrainerKind();
    for (i = 0; i < 4; i++) {
        msgs[i] = enc->getMsg(i);
    }
    if ((kind == 0xF || kind == 0xE) && deck != NULL) {
        u16 floor = *(u16*)(deck + 4);
        if (floor != 0) {
            fightEncountDataBiosSetFightFloorDataId(data, floor);
        }
    }
    if (id == 0x73) {
        if (underTakerDeckRand == -1) {
            underTakerDeckRand = (u16)HSD_Rand() % 4;
        }
        if (fightEncountDataBiosGetFightFloorDataId(data) == 0x1F) {
            switch (underTakerDeckRand) {
            case 0:
                trainer = 0x60001;
                break;
            case 1:
                trainer = 0x60002;
                break;
            case 2:
                trainer = 0x60003;
                break;
            case 3:
                trainer = 0x60004;
                break;
            }
        } else if (fightEncountDataBiosGetFightFloorDataId(data) == 0x21) {
            switch (underTakerDeckRand) {
            case 0:
                trainer = 0x60005;
                break;
            case 1:
                trainer = 0x60006;
                break;
            case 2:
                trainer = 0x60007;
                break;
            case 3:
                trainer = 0x60008;
                break;
            }
        }
        fightEncountDataBiosSetFightTrainerDataId(data, 1, trainer);
    }
    if (field != 0) {
        fightEncountDataBiosSetFightFloorDataId(data, field);
    }
    switch (mode) {
    case 2:
        fightEncountDataBiosSetFightKind(data, 0x10);
        break;
    case 3:
        fightEncountDataBiosSetFightKind(data, 0xC);
        break;
    }
    switch (destroy) {
    case 1:
        fightEncountDataBiosSetZenmetuFlag(data, 1);
        break;
    case 2:
        fightEncountDataBiosSetZenmetuFlag(data, 0);
        break;
    }
    if (round != 0) {
        fightEncountDataBiosSetSyoukaiWzxDataId(data, round);
    }
    for (u8 i_loop = 0; i_loop < 4; i_loop++) {
        u16 msg = msgs[i_loop];
        if (msg != 0) {
            fightTrainerDB_SetSerihuMsgId(fightEncountDataBiosGetFightTrainerDataId(data, 1), i_loop, msg);
        }
    }
    if (trainerKind != 0) {
        fightTrainerDB_SetKindDataId(fightEncountDataBiosGetFightTrainerDataId(data, 1), trainerKind);
    }
}
}
