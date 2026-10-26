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
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

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
enum ASM { ASM_draft_dummy };
enum GSgappFunc { GSgappFunc_draft_dummy };
struct GStexture;
struct Gamedata;
struct GamedataSave;
typedef s64 OSTime;
struct Savedata;
enum resFreeFunc { resFreeFunc_draft_dummy };

extern "C" {

extern u8 pokecolo_DVDETHMode;
extern u32 _pokecoloCurrentLanguage;
extern u8 __pokecolo_CountPlayTime;
extern u32 _RomVer;

struct GStexture {
    u8 _draft[1];
};
struct Gamedata {
    u8 _draft[1];
};
struct GamedataSave {
    u8 _draft[1];
};
struct Savedata {
    u8 _draft[1];
};

extern "C" {
void GScameraInit(u32 count);
s32 GScolsys2Init();
s32 GSdvdSetErrorMsg(s32, s32, s32, s32, s32);
extern "C" void GSeffectInitSystem(void);
void GSfilterInitialise(u8 count);
u32 GSflagGet(u32 id);
void GSflagInit(u32* bits1, u32 num1, u32* bits2, u32 num2, u32* bits3, u32 num3);
void GSfloorInit(u32 a, u32 b, u32 c, u32 d);
s32 GSfloorSetData(s32, s32);
s32 GSfsysGetDriveStatus(void);
s32 GSfsysReadWait(u32 id);
int GSgappCreate(s32 type, u8 priority, void* arg, GSgappFunc func);
void GSgappInit(u32 maxJobs, u32 maxBkgndJobs);
void GSgappSetName(int id, const char* name);
void GSgappSetPauseLevel(int id, s32 level);
void GSgappUpdate(void);
s32 GSgfxPerfbarSetRenderMode(s32);
extern "C" void GSgfxRelocToScratch(void);
void GSgfxRender(void);
s32 GSgfxReset(s32);
s32 GSgfxResetEnable();
u8 GSgfxResetGetStatus();
s32 GSgfxResetSetShutdownCallback(void*);
s32 GSgfxVideoSetLockFrameActive(s32);
s32 GSgfxVideoSetLockFrameRate(s32);
s32 GSgfxVideoSetMode(s32, s32, s32, s32, s32);
u32 GSinputButtonsChanged(s32 pad);
u32 GSinputButtonsPressed(s32 pad);
s32 GSinputInit();
u8 GSinputIsConnected(s32);
s32 GSinputOpen(s32);
s32 GSinputRead(s32);
s32 GSinputReadEnd();
s32 GSinputReadStart();
s32 GSinputSetClamping(s32, s32);
s32 GSinputSetSmoothingFunc(s32, s32);
s32 GSinputSetSmoothingRate(s32, s32);
void GSlensFlareInit(void);
void GSlightInit(u32 count);
void GSmaterialInit(void);
void GSmodelInit(void);
void GSmodelSetMarukageTexture(GStexture* tex);
s32 GSmovieInit();
s32 GSmsgDaemon();
s32 GSmsgFontOpen(s32*);
s32 GSmsgInit(s32, s32);
s32 GSmsgOpen(s32*);
s32 GSmsgSetCtrlFunc(s32*);
s32 GSnetworkInit();
s32 GSpartInit(s32);
s32 GSparticleInit(s32);
void* GSresAllocResource(u32 size, u32 grp, u32 id, resFreeFunc freeFunc);
void* GSresGetResourceAllGroup(u32 id);
void GSresInit(u32 count);
void GSsndQuit();
void GStextureInit(u32 count);
void* GSthreadCreate(s32, s32, s32, s32, s32, void (*)(void));
s32 GSthreadExecuteAll();
s32 GSthreadInit(s32);
u8 GSvtrGetInfoDisp(void);
s32 GSvtrGetState();
s32 GSvtrInit();
bool GSvtrIsActive(void);
s32 GSvtrLoadTexture();
void GSvtrPause(void);
void GSvtrPlay(void);
s32 GSvtrRegisterGSgapp(s32);
void GSvtrSetInfoDisp(bool disp, u8);
void GSvtrSingleStep(void);
void GSvtrSlowPlay(void);
u32 OSGetProgressiveMode(void);
u32 OSGetResetCode();
asm OSTime OSGetTime(void);
void cameraInit(void);
s32 characterInit();
void dbgMenuGSvtrCaptureUpdate(void);
u8 dbgMenuIsOpen(void);
void deckInit(void);
s32 esabaHeroCallBackInit();
s32 fadeInit();
s32 fightInit();
void floorFieldCameraInit();
void floorInit();
void floorLayerConfig(u32 floorID, u8 kind);
s32 floorLayerConfigLoad();
void floorMappingCommonScript(void);
void fn_8005C068(u32 value);
void fn_8005C8CC();
void fn_8005C8EC();
f64 gamedatasaveBiosGetPlaytime(GamedataSave* save);
GamedataSave* gamedatasaveBiosGetPtr(Gamedata* gamedata);
void gamedatasaveBiosSetPlaytime(GamedataSave* save, f64 value);
bool gbaCommandIsConnected(s32 gba);
s32 gbaCommandKeyRead(s32);
s32 heroMoveAllInit();
extern "C" void lightInit(void);
s32 memcardInitialize();
void* memset(void* dst, int val, size_t n);
s32 menuDaemon();
s32 menuFaceAllocMemory();
u8 menuFieldIsOpen();
s32 menuInit(s32);
bool menuIsCheck(s32 menuID);
s32 menuNintendo();
void pauseInit(void);
bool pauseIsPause(void);
void pauseOff(void);
void pauseOn(void);
s32 peopleDaemon(s32, s32);
s32 peopleInit(s32);
u8 peopleIsBlock();
s32 peopleUpdateShadow();
void pokecoloCheckDiskTray();
f32 pokecoloGetFrameTime(void);
s32 pokecoloGetLanguage(void);
f64 pokecoloGetPlayTime();
u32 pokecoloGetPlayTimeValue(void);
u32 pokecoloGetRomVersion(void);
void pokecoloSetPlayTime(f64 time);
void pokecoloStartCountPlayTime(u8 value);
s32 reliveHallCallBackInit();
void* savedataBiosGetGamedataPtr(Savedata* savedata);
u32 savedataBiosGetNowSavedataPtr();
s32 savedataBiosGetSavedataBufferPtr();
void savedataBiosSetNowSavedataPtr(Savedata* savedata);
s32 savedataCreate(s32, s32);
void* savedataGetStatus(void* save, s32 kind);
s32 shapeInit(s32);
s32 sodateyaHeroCallBackInit();
void* tableResBiosGetResPtr(u32 index);
f32 timeGetLastFrameSec(void);
extern s32 floordata;
extern s32* floordata_number;
extern s32 msgctrlcode;
struct XdBlob94 { u8 data[0x94]; };
extern XdBlob94 systemVars;
f32 __cvt_ull_flt(s32, s32);
extern s32 _clearAddress;
extern s32 init;
}
extern "C++" {
static void _countPlayTime();
static u32 _getSaveSystemDataPtr();
static void _mainDaemon(unsigned long p0, unsigned long p1);
static void _mainGBARead(unsigned long p0, unsigned long p1);
static void _mainPadRead(unsigned long p0, unsigned long p1);
static void _mainRender(unsigned long p0, unsigned long p1);
static void _mainThreadExec(unsigned long p0, unsigned long p1);
s32 _pokecoloCheckExDisc();
static void _pokecoloInit();
static void _pokecoloShutdown();
static void _setSystemVars();
}
static s32 _AntiActionReplayTimer;
static s32 _frameTime;
static f32 _resettimer;
s32 pokecoloFrameCounter;
s32 pokecoloGappAntiActionReplayHandle;
s32 pokecoloGappGBAReadHandle;
s32 pokecoloGappMainDeamonHandle;
s32 pokecoloGappPadReadHandle;
s32 pokecoloGappRenderHandle;
s32 pokecoloGappThreadHandle;
s8 pokecoloWaitVSync;

extern "C" {
void mainAntiActionReplay();
void pokecoloMain(int argc, char** argv);
}
static s32 common_fnt_S2162;
static s32 common_tbl_S2164;
static s32 debug_menu_fnt_S2163;
static s32 resident_fnt_S2161;
static s32 system_error_fnt_S2165;
static s32 system_error_tbl_S2166;

extern "C" {
extern s32 lbl_8038FBE0;
u64 __div2u(s32, s32, s32, s32);
}

u8 pokecoloIsDVDETHMode(void) {
    return pokecolo_DVDETHMode;
}

void fn_8005C068(u32 value) {
    _pokecoloCurrentLanguage = value;
}
extern "C" {
s32 pokecoloGetLanguage() {
    switch (_pokecoloCurrentLanguage) {
    case 0:
            return 2;
        break;
    }
    return _pokecoloCurrentLanguage;
}
}

void pokecoloStartCountPlayTime(u8 value) {
    __pokecolo_CountPlayTime = value;
}

extern "C" {
void pokecoloSetPlayTime(f64 time) {
    GamedataSave* save = (GamedataSave*)_getSaveSystemDataPtr();
    if (save != 0) {
        gamedatasaveBiosSetPlaytime(save, time);
    }
}
}

extern "C" {
u32 pokecoloGetPlayTimeValue() {
    return (u32) pokecoloGetPlayTime();
}
}

extern "C" {
f64 pokecoloGetPlayTime() {
    GamedataSave* save = (GamedataSave*)_getSaveSystemDataPtr();
    if (save != 0) {
        return gamedatasaveBiosGetPlaytime(save);
    }
    return 0.0;
}
}

extern "C++" {
#pragma peephole off
static void _countPlayTime() {
    f64 temp_f31;
    f64 var_f1;
    u32 temp_r3;

    temp_r3 = _getSaveSystemDataPtr();
    if ((temp_r3 != 0U) && ((u8) __pokecolo_CountPlayTime == 1) && (GSflagGet(0x30D) == 0U)) {
        temp_f31 = gamedatasaveBiosGetPlaytime((GamedataSave*)(temp_r3));
        var_f1 = temp_f31 + pokecoloGetFrameTime();
        if (var_f1 >= M2C_BITWISE(f32, 3599940.0)) {
            var_f1 = 3599940.0;
        }
        gamedatasaveBiosSetPlaytime((GamedataSave*)(temp_r3), var_f1);
    }
}
#pragma peephole reset
}

extern "C++" {
static u32 _getSaveSystemDataPtr() {
    if ((savedataBiosGetNowSavedataPtr() != 0U) && (savedataBiosGetGamedataPtr((Savedata *)(0)) != 0U)) {
        return (unsigned long)(gamedatasaveBiosGetPtr((Gamedata *)(0)));
    }
    return 0;
}
}

s32 pokecoloGetCountryCode(void) {
    return 0x1;
}
extern "C++" {
s32 _pokecoloCheckExDisc() {
    return pokecoloGetRomVersion() == 4 ? 1 : 0;
}
}

void pokecoloInitRomVersion(void) {
    _RomVer = 0x0;
}

u32 pokecoloGetRomVersion(void) {
    return _RomVer;
}
extern "C" {
f32 pokecoloGetFrameTime() {
    return (__cvt_ull_flt(M2C_FIELD(&_frameTime, s32 *, 0), M2C_FIELD(&_frameTime, s32 *, 4)) / 1000.0f) / 1000.0f;
}
}

extern "C" {
void pokecoloCheckDiskTray() {
    s32 temp_r3;

    if (menuIsCheck(0x2A) != 0) {
        if (pauseIsPause() == 0) {
            pauseOn();
        }
    } else {
        temp_r3 = GSfsysGetDriveStatus();
        if (temp_r3 != 0xB) {
            if ((temp_r3 < 0xB) && (temp_r3 < 7)) {
                if (temp_r3 < 3) {
                    goto block_10;
                }
                goto block_8;
            }
block_10:
            if (pauseIsPause() != 0) {
                pauseOff();
            }
        } else {
block_8:
            if (pauseIsPause() == 0) {
                pauseOn();
            }
        }
    }
}
extern "C" {
#pragma push
#pragma optimize_for_size on
void pokecoloMain(int p0, char** p1) {
    volatile s32 var_r0;
    s32 var_r28_2;
    u32 temp_r6;
    u32 var_r28_3;
    u64 temp_ret;
    u64 temp_ret_2;
    u64 temp_ret_3;
    u64 temp_ret_4;
    u64 var_r29;
    u8 var_r28;

    GSgfxRelocToScratch();
    pokecoloFrameCounter = 0;
    switch ((s32) M2C_FIELD(&systemVars, s32 *, 8)) {
    case 0:
        GSgfxPerfbarSetRenderMode(0);
        break;
    case 1:
        GSgfxPerfbarSetRenderMode(1);
        break;
    case 2:
        GSgfxPerfbarSetRenderMode(2);
        break;
    }
    GSthreadInit(0x14);
    fn_8005C068(2);
    var_r28 = 0;
    if (_pokecoloCheckExDisc() == 1) {
        if (OSGetProgressiveMode() == 1U) {
            var_r28 = 1;
        }
    } else if (OSGetProgressiveMode() == 1U) {
        if ((u32) (OSGetResetCode() & 0x80000000) != 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 == 1) {
            var_r28 = 1;
        }
    }
    if (var_r28 != 0) {
        GSgfxVideoSetMode(0, 1, 0, 0, 1);
    }
    pauseInit();
    GStextureInit(0x10);
    GSmodelInit();
    GSpartInit(8);
    GSmaterialInit();
    GScameraInit(0x20);
    GSlightInit(0x20);
    shapeInit(0x20);
    GSparticleInit(0x20);
    GSinputInit();
    var_r28_2 = 1;
    do {
        GSinputOpen(var_r28_2);
        GSinputSetClamping(var_r28_2, 2);
        GSinputSetSmoothingRate(var_r28_2, 7);
        GSinputSetSmoothingFunc(var_r28_2, 1);
        var_r28_2 += 1;
    } while (var_r28_2 <= 4);
    GSgappInit(0x14, 4);
    GSresInit(0x15E);
    GSfloorInit(4, 0x10, 0x10, 0x10);
    GScolsys2Init();
    GSmsgInit(2, 5);
    GSmsgSetCtrlFunc(&msgctrlcode);
    GSnetworkInit();
    GSmsgFontOpen(&resident_fnt_S2161);
    GSmsgFontOpen(&common_fnt_S2162);
    GSmsgOpen(&common_tbl_S2164);
    GSmsgFontOpen(&system_error_fnt_S2165);
    GSmsgOpen(&system_error_tbl_S2166);
    GSmsgFontOpen(&debug_menu_fnt_S2163);
    GSmsgOpen(&lbl_8038FBE0);
    GSdvdSetErrorMsg(0x65, 0x66, 0x67, 0x68, 0x69);
    GSvtrInit();
    GSlensFlareInit();
    GSmovieInit();
    menuInit(0x18);
    GSgfxVideoSetLockFrameRate(0);
    GSgfxVideoSetLockFrameActive(1);
    pokecoloGappRenderHandle = GSgappCreate(1, 0xFF, 0, (GSgappFunc)(_mainRender));
    GSgappSetName((int)("Render"), (const char *)(0));
    pokecoloGappPadReadHandle = GSgappCreate(1, 0, 0, (GSgappFunc)(_mainPadRead));
    GSgappSetName((int)("PADRead"), (const char *)(0));
    pokecoloGappGBAReadHandle = GSgappCreate(1, 1, 0, (GSgappFunc)(_mainGBARead));
    GSgappSetName((int)("GBARead"), (const char *)(0));
    pokecoloGappThreadHandle = GSgappCreate(1, 0xA, 0, (GSgappFunc)(_mainThreadExec));
    GSgappSetName((int)(&_clearAddress + 0x80), (const char *)(0));
    GSgappSetPauseLevel(pokecoloGappThreadHandle, 1);
    GSvtrRegisterGSgapp(pokecoloGappThreadHandle);
    pokecoloGappAntiActionReplayHandle = GSgappCreate(1, 0xFD, 0, (GSgappFunc)(mainAntiActionReplay));
    GSgappSetName((int)(&_clearAddress + 0x8C), (const char *)(0));
    pokecoloGappMainDeamonHandle = GSgappCreate(1, 0xFE, 0, (GSgappFunc)(_mainDaemon));
    GSgappSetName((int)(&_clearAddress + 0xA0), (const char *)(0));
    GSgfxResetEnable();
    GSgfxResetSetShutdownCallback(_pokecoloShutdown);
    fadeInit();
    GSfilterInitialise(8);
    GSeffectInitSystem();
    deckInit();
    GSthreadCreate(0, 0x3E8, 0x4000, 1, 1, (void (*)(void))(_pokecoloInit));
    temp_ret = OSGetTime();
    var_r28_3 = (u32) temp_ret;
    var_r29 = temp_ret;
loop_23:
    GSgappUpdate();
    pokecoloCheckDiskTray();
    temp_ret_2 = OSGetTime();
    var_r29 = temp_ret_4;
    temp_r6 = (u32) temp_ret_2 - var_r28_3;
    var_r28_3 = (u32) temp_ret_4;
    temp_ret_3 = __div2u(((((temp_ret_2 - var_r29) - !M2C_CARRY) * 8) & ~7) | (temp_r6 >> 0x1DU), temp_r6 * 8, 0, *(u32 *)0x800000F8 / 500000);
    M2C_FIELD(&_frameTime, s32 *, 0) = temp_ret_3;
    M2C_FIELD(&_frameTime, u32 *, 4) = (u32) temp_ret_3;
    temp_ret_4 = OSGetTime();
    pokecoloFrameCounter += 1;
    goto loop_23;
}
#pragma pop
}

}

extern "C" {
extern "C++" {
static void _pokecoloShutdown() {
    GSsndQuit();
}
}

extern "C++" {
#pragma push
#pragma peephole off
static void _pokecoloInit() {
    void* flags1;
    void* num3;
    void* flags2;
    void* num2;
    void* flags3;
    u8* res;

    floorLayerConfig(0, 5);
    menuNintendo();
    floorLayerConfigLoad();
    GSfloorSetData(floordata, *floordata_number);
    res = (u8*)GSresAllocResource(2, 0, 2, (resFreeFunc)0);
    res[0] = 0;
    res[1] = 0;
    pokecoloWaitVSync = 0;
    pokecoloSetPlayTime(0.0);
    pokecoloStartCountPlayTime(0);
    GSmsgFontOpen((s32*)tableResBiosGetResPtr(0));
    GSmsgOpen((s32*)tableResBiosGetResPtr(1));
    GSdvdSetErrorMsg(0x65, 0x66, 0x67, 0x68, 0x69);
    floorMappingCommonScript();
    savedataBiosSetNowSavedataPtr((Savedata*)(savedataBiosGetSavedataBufferPtr() + ((u32) OSGetTime() & 0x7E0)));
    savedataCreate(0, 0);
    fightInit();
    flags3 = savedataGetStatus(0, 9);
    num2 = savedataGetStatus(0, 6);
    flags2 = savedataGetStatus(0, 8);
    num3 = savedataGetStatus(0, 5);
    flags1 = savedataGetStatus(0, 7);
    savedataGetStatus(0, 4);
    GSflagInit((u32*)flags1, (u32)num3, (u32*)flags2, (u32)num2, (u32*)flags3, 0);
    GSvtrLoadTexture();
    menuFaceAllocMemory();
    GSresGetResourceAllGroup(0x1F3A1200);
    GSmodelSetMarukageTexture((GStexture *)(0));
    characterInit();
    cameraInit();
    lightInit();
    heroMoveAllInit();
    peopleInit(0x30);
    floorFieldCameraInit();
    sodateyaHeroCallBackInit();
    reliveHallCallBackInit();
    esabaHeroCallBackInit();
    memcardInitialize();
    floorInit();
    _setSystemVars();
    memset((void*)(0x80001803), 0, 0x17FD);
}
#pragma pop
}
}

s32 fn_8005C8C4(void) {
    return 0x2;
}
extern "C" {
void fn_8005C8CC() {
    fn_8005C8EC();
}
}

extern "C" {
void fn_8005C8EC() {
    GSfsysReadWait(0xA);
}
extern "C" {
void mainAntiActionReplay() {
    s32 *var_r31;
    s32 temp_r6;
    s32 temp_r6_2;
    u32 var_r30;

    switch (_AntiActionReplayTimer) {

    case 0:
            var_r30 = 0U;
            var_r31 = &_clearAddress;
            do {
                temp_r6 = M2C_FIELD(var_r31, s32 *, 0);
                temp_r6_2 = temp_r6 + 0x15;
                memset((void *)((void*)(temp_r6 + 0x80000015)), (int)(0), (unsigned long)((M2C_FIELD(var_r31, s32 *, 4) + 0x16) - temp_r6_2));
                var_r31 += 8;
                var_r30 += 2;
            } while (var_r30 < 0x20U);
            memset((void*)(0x80001801), 0, 0x17FF);
            _AntiActionReplayTimer = 0x64;

        break;

    }
    _AntiActionReplayTimer -= 1;
}
}

extern "C++" {
#pragma peephole off
static void _mainRender(unsigned long p0, unsigned long p1) {
    static s32 frame = 0;
    GSgfxRender();
}
extern "C++" {
static void _mainDaemon(unsigned long p0, unsigned long p1) {

    dbgMenuGSvtrCaptureUpdate();
    if ((GSvtrIsActive() != 0) && (dbgMenuIsOpen() == 0)) {
        if ((u32) (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x40) != 0) {
            if (GSvtrGetState() == 2) {
                GSvtrSlowPlay();
            } else if (GSvtrGetState() == 4) {
                GSvtrPause();
            } else {
                GSvtrPlay();
            }
        }
        if ((u32) (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x10) != 0) {
            GSvtrSingleStep();
        }
        if ((u32) (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 8) != 0) {
            GSvtrSetInfoDisp(GSvtrGetInfoDisp() == 0, 0);
        }
    }
    menuDaemon();
    GSmsgDaemon();
    _countPlayTime();
}
}

#pragma peephole reset
}

}

extern "C++" {
static void _setSystemVars() {
}
}

extern "C" {
extern "C++" {

extern "C++" {
static void _mainThreadExec(unsigned long p0, unsigned long p1) {
    s32 arg1;
    s32 arg0;
    f32 temp_f1;
    u8 temp_r31;

    temp_r31 = GSgfxResetGetStatus();
    if (((u32) (GSinputButtonsPressed(1) & 0x1600) == 0x1600) && (temp_r31 != 0)) {
        temp_f1 = _resettimer + timeGetLastFrameSec();
        _resettimer = temp_f1;
        if (temp_f1 >= 0.5f) {
            GSgfxReset(0);
        }
    } else {
        _resettimer = 0.0f;
    }
    GSthreadExecuteAll();
    if ((menuFieldIsOpen() == 0) && (peopleIsBlock() == 0)) {
        peopleDaemon(arg0, arg1);
        return;
    }
    peopleUpdateShadow();
}
}

extern "C++" {
#pragma peephole off
static void _mainGBARead(unsigned long p0, unsigned long p1) {
    s32 i;

    for (i = 1; i <= 4; i++) {
        if (GSinputIsConnected(i) == 0) {
            gbaCommandKeyRead(i);
        }
    }
}
}

extern "C++" {
static void _mainPadRead(unsigned long p0, unsigned long p1) {
    s32 i;

    GSinputReadStart();
    for (i = 1; i <= 4; i++) {
        if (gbaCommandIsConnected(i) == 0) {
            GSinputRead(i);
        }
    }
    GSinputReadEnd();
}
#pragma peephole reset
}
}
}

}
