#include <dolphin/types.h>
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
struct Hero;
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
struct KeyInfo;
struct tagWINDOW_WORK;

#pragma peephole off

class Pokemon;

enum GSinputDevice { GSinputDevice_dummy };

struct PokemonEntryFace {
    u8 active;
    u8 pad1;
    u16 face;
    u32 value;
    u32 pad8;
};

struct PokemonEntryWork {
    s32 f0;
    bool entryFlag[4];
    s8 trainerKind[4];
    s32 fC;
    u8 pad10[0x1C];
    s32 f2C;
    PokemonEntryFace faces[4][6];
    s32 f150;
    s32 f154;
    u8 readFlag;
    u8 pad159[7];
    f32 track[4][12];
    f32 f220;
    s32 f224;
    u8 pad228[4];
    u8 connected;
    u8 pad22D[3];
    s32 f230;
};

struct GCBEntry {
    s16 value;
    s16 flag;
    u8 pad4[0x8C];
};

struct GCB {
    u8 pad0[0xC];
    s32 cur;
    u8 pad10[0x9922];
    GCBEntry entries[4];
};

extern u8 _CB[0xB5F8];
extern u8 _menuCBBattleStartWork[0x148];
extern GCB* pGCB;
u16 uToolPokemon_faceId;

struct CBTrainerRaw {
    u8 pad0[0x3C];
    u32 f3C;
    u8 pad40[0x1320 - 0x40];
};
#define CBF(type, off) (*(type*)(&_CB[off]))

struct CBLoadState {
    u8 pad0[0xB458];
    s16 value[4][6];
    s8 flag[4][6];
};

extern "C" {
u16 toolentryTaisenGetPokemonNum(s32);
u16 toolentryTaisenGetEntryPokemonNum(s32);
u32 menuCBBios_ParticipationPokemonMax(void);
s32 toolentryTaisenGetBattleType(void);
s32 toolentryTaisenGetBattleVersus(void);
s32 toolentryTaisenGetEntryPlayerNum(void);
s32 toolentryTaisenGetBattlePlayerID(s32);
s32 toolentryTaisenGetControlerType(s32);
u16 toolentryTaisenGetHomePlace(s32);
void toolentryTaisenInitPokemonOrder(s32);
void toolentryTaisenEntryPokemon(s32);
s32 toolentryTaisengetEtnryPokemonOrderNum(s32);
s32 toolentryTaisenSetEtnryPokemonOrder(s32, s32);
s32 toolentryTaisenDeleteEtnryPokemonOrder(s32);
void toolentryTaisenSetEtnryPokemonOrderGBA(s32, s32, s32*);
Pokemon* toolentryTaisenGetPokemonPtr(s32, s32);
Pokemon* toolentryTaisenGetEntryPokemonPtr(s32, s32);
void* menuCBBios_GetTrainerFromVersusBattleID(s32);
void* menuCBBios_GetTrainerImmediately(s32);
void* menuCBBios_GetTrainer(void);
s32 menuCBBios_GetHeroImmediately(s32);
s32 menuCBTrainerBios_GetControlerID(void);
s32 menuCBBattleStartGetStatus(void);
void menuCBBattleStartTrainerFaceFree(void);
void menuCB_SE_Play(s32);
void menuCB_GBADisconnectedErrorJob(void);
void* menuFaceLoad_Tool(s32, Pokemon* (*)(void*), s32);
u16 menuFaceGetID2(Pokemon*, u8);
void menuFaceDispFromID(s32, s32, u16);
s32 pokemonGetStatus(Pokemon*, u16, u16, u16);
u32 pokemon_GetSeikaku(Pokemon*);
u32 pokemonAdjustValueBySeikaku(u32, u16, u32);
void pokemonBiosSetPhyAtk(Pokemon*, u16);
void pokemonBiosSetPhyDef(Pokemon*, u16);
void pokemonBiosSetSpeAtk(Pokemon*, u16);
void pokemonBiosSetSpeDef(Pokemon*, u16);
void pokemonBiosSetNimbleness(Pokemon*, u16);
u16 menuGBACGetRomVer(u16);
u8 menuCBRule_DEOKISISUCamouflage(void);
Pokemon* heroBiosGetPokemonPtr(void*, u16);
u8 pokemonCheckValid(Pokemon*);
void soundOpenPlay(s32, s32, s32);
void gba_SIProbe_ErrorCntClear(s32);
s32 menuOpen(s32, s32);
s32 menuOpenCustom(s32, ...);
void menuCloseCustom(s32, s32, s32);
s32 windowGetActiveID(void);
void GSthreadSwitch(void);
void gbaCommandEntryRequest(s32, u16, u16, s32);
void gbaCommandSendWazaText(s32, s32);
u8 gbaCommandIsConnected(s32);
void gbaCommandEntryResult(s32, s32*);
void gbaCommandEntryPokemon(s32, u8*);
u8 GSsndPlay(u32, s32, u32);
bool pauseIsPause(void);
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
u16* windowGetKeyInfo(void);
void* windowSearchID(s32);
void menuCBPokemonEntryTexWorkInit(void);
u16 menuCBPokemonEntryPokemonNumMin(s32);
void menuCBPokemonEntryPokemonFaceFree(void);
}

static s32 _GBA_DeokisisuParamTable[4][5] = {
    {0x96, 0x32, 0x96, 0x32, 0x96},
    {0xB4, 0x14, 0xB4, 0x14, 0x96},
    {0x46, 0xA0, 0x46, 0xA0, 0x5A},
    {0x5F, 0x5A, 0x5F, 0x5A, 0xB4},
};
static PokemonEntryWork _menuCBPokemonWork;

static u8 _menuCB_pokemonGetDeoxysSel(u16 player, bool flag);
static void _menuCBPokemonEntryEntCheckDebug(long);
static void _menuCBPokemonEntryEntCheckGBA(GSinputDevice inputDevice, long player);
static void _menuCBPokemonEntryEntCheck(GSinputDevice dev, long player);
static s32 _menuCBPokemonEntryButtonCheck(u32 buttons, long player);
static void _menuCBPokemonEntryWork(void);
static u16 _menuCBPokemonEntryPokemonNum(long player);
static void _menuCBPokemonEntryWorkInit(void);
static void _menuCBPokemonEntrySetEntryFlag(long player, bool flag);
static u8 _menuCBPokemonEntryGetEntryFlag(long player);
static void _menuCBPokemonEntryDispPosition(void);
static u8 _menuCBPokemonEntryAllPlayer(void);
static Pokemon* _menuCBPokemonEntryLoadCallBack(void* flag);
static PokemonEntryFace* _menuCBPokemonEntryGetFaceBase(long player, long slot);

struct KeyInfo {
    u8 _draft[1];
};
struct tagWINDOW_WORK {
    u8 _draft[1];
};

struct Hero {
    u8 _draft[1];
};

extern "C" {
void menuCBPokemonEntryButtonTask_20041006();
}
extern "C++" {
static void _menuCB_DeoxysParamCustom(Pokemon* pokemon, u16 player);
}

extern "C" {
s32 menuCB_PokemonEntry();
}

static void _menuCB_DeoxysParamCustom(Pokemon* pokemon, u16 player) {
    s32 level = pokemonGetStatus(pokemon, 0, 0x7A, 0);
    s32 seikaku = pokemon_GetSeikaku(pokemon);
    s32 b0 = pokemonGetStatus(pokemon, 0, 0x94, 0);
    s32 b1 = pokemonGetStatus(pokemon, 0, 0x95, 0);
    s32 b2 = pokemonGetStatus(pokemon, 0, 0x96, 0);
    s32 b3 = pokemonGetStatus(pokemon, 0, 0x97, 0);
    s32 b4 = pokemonGetStatus(pokemon, 0, 0x98, 0);
    s32 e0 = pokemonGetStatus(pokemon, 0, 0x8E, 0);
    s32 e1 = pokemonGetStatus(pokemon, 0, 0x8F, 0);
    s32 e2 = pokemonGetStatus(pokemon, 0, 0x90, 0);
    s32 e3 = pokemonGetStatus(pokemon, 0, 0x91, 0);
    s32 e4 = pokemonGetStatus(pokemon, 0, 0x92, 0);
    s32 s0 = level * (b0 + _GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][0] * 2 + e0 / 4) / 100 + 5;
    s32 s1 = level * (b1 + _GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][1] * 2 + e1 / 4) / 100 + 5;
    s32 s2 = level * (b2 + _GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][2] * 2 + e2 / 4) / 100 + 5;
    s32 s3 = level * (b3 + _GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][3] * 2 + e3 / 4) / 100 + 5;
    s32 s4 = level * (b4 + _GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][4] * 2 + e4 / 4) / 100 + 5;
    s32 r0 = pokemonAdjustValueBySeikaku(seikaku, 0x88, s0);
    s32 r1 = pokemonAdjustValueBySeikaku(seikaku, 0x89, s1);
    s32 r2 = pokemonAdjustValueBySeikaku(seikaku, 0x8A, s2);
    s32 r3 = pokemonAdjustValueBySeikaku(seikaku, 0x8B, s3);
    s32 r4 = pokemonAdjustValueBySeikaku(seikaku, 0x8C, s4);
    pokemonBiosSetPhyAtk(pokemon, r0);
    pokemonBiosSetPhyDef(pokemon, r1);
    pokemonBiosSetSpeAtk(pokemon, r2);
    pokemonBiosSetSpeDef(pokemon, r3);
    pokemonBiosSetNimbleness(pokemon, r4);
}
static u8 _menuCB_pokemonGetDeoxysSel(u16 player, bool flag) {
    u8 sel = 0;
    CBTrainerRaw* tr = (CBTrainerRaw*)_CB;
    u16 slot = tr[player].f3C - 1;
    if (CBF(s32, 4) == 1) {
        return 0;
    }
    if (menuCBRule_DEOKISISUCamouflage() != 0 || flag == 0) {
        switch (menuGBACGetRomVer(slot)) {
        case 1:
        case 2:
            sel = 0;
            break;
        case 3:
            sel = 1;
            break;
        case 4:
            sel = 2;
            break;
        case 5:
            sel = 3;
            break;
        default:
            sel = 0;
            break;
        }
    }
    return sel;
}

extern "C" {
s32 menuCB_PokemonEntry() {
    s32 opened;
    s32 sum;
    s32 i;
    s32 j;
    s32 type;
    s32 num;
    u16 k;
    Pokemon* pokemon;
    Hero* hero;

    *(s32*)&_menuCBBattleStartWork[0x124] = 0x5DB;
    soundOpenPlay(0x5DB, 0, 0xFF);
    _menuCBPokemonEntryWorkInit();
    gba_SIProbe_ErrorCntClear(-1);
    CBF(s32, 0xB104) = -1;
    CBF(s32, 0xB108) = 0;
    CBF(s32, 0xAFE0) = 0;
    CBF(s32, 0xB060) = 0;
    CBF(s32, 0xB110) = 2;
    CBF(s32, 0xB1A0) = 0;
    menuCB_SE_Play(0x14);
    menuOpen(0xC6, 0);
    menuOpen(0xC5, 0);
    opened = 0;
    do {
        if (CBF(s32, 0xB108) == 1) {
            if (opened == 0) {
                menuOpenCustom(0xE2, windowGetActiveID(), &_CB[0xAFE0], 0, 0, 0);
                opened = 1;
            }
            if (CBF(s32, 0xB060) != 0) {
                if (CBF(s32, 0xAFE0) == 0) {
                    _menuCBPokemonEntrySetEntryFlag(0, true);
                    CBF(s32, 0xB108) = 2;
                } else {
                    toolentryTaisenInitPokemonOrder(0);
                    CBF(s32, 0xB108) = 0;
                    CBF(s32, 0xAFE0) = 0;
                    CBF(s32, 0xB060) = 0;
                    CBF(s32, 0xB110) = 2;
                    menuCloseCustom(0xE2, 0, 0);
                    opened = 0;
                }
            }
        }
        if (CBF(s32, 0xB1A0) == 1) {
            _menuCBPokemonWork.connected = 0;
        }
        if (_menuCBPokemonEntryAllPlayer() != 0) {
            CBF(s32, 0xB108) = 0x7FFFFFFF;
        }
        if (_menuCBPokemonWork.connected == 0) {
            CBF(s32, 0xB108) = 0x7FFFFFFF;
        }
        GSthreadSwitch();
    } while (CBF(s32, 0xB108) != 0x7FFFFFFF);
    if (_menuCBPokemonWork.connected == 0) {
        menuCB_SE_Play(0x15);
        menuCloseCustom(0xE2, 0, 0);
        menuCloseCustom(0xC5, 0, 0);
        menuCloseCustom(0xC6, 0, 1);
        menuCB_GBADisconnectedErrorJob();
        menuCBPokemonEntryPokemonFaceFree();
        menuCBBattleStartTrainerFaceFree();
        return 0xA9;
    }
    do {
        GSthreadSwitch();
        sum = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 6; j++) {
                if (((CBLoadState*)_CB)->flag[i][j] == 1) {
                    sum += ((CBLoadState*)_CB)->value[i][j];
                }
            }
        }
    } while (sum != 0);
    GSthreadSwitch();
    GSthreadSwitch();
    GSthreadSwitch();
    type = toolentryTaisenGetBattleType();
    if (toolentryTaisenGetBattleVersus() == 4) {
        switch (type) {
        case 0:
        case 1:
            num = 2;
            break;
        default:
            num = 4;
            break;
        }
    } else {
        switch (type) {
        case 0:
        case 1:
            num = 2;
            break;
        default:
            num = 1;
            break;
        }
    }
    for (i = 0; i < num; i++) {
        toolentryTaisenEntryPokemon(i);
    }
    if (CBF(s32, 4) == 0) {
        for (i = 0; i < num; i++) {
            hero = (Hero*)((u8*)menuCBBios_GetTrainerImmediately(i) + 0x2C);
            for (k = 0; k < 6; k++) {
                pokemon = heroBiosGetPokemonPtr(hero, k);
                if (pokemonGetStatus(pokemon, 0, 0x6E, 0) == 0x19A) {
                    _menuCB_DeoxysParamCustom(pokemon, i);
                }
            }
        }
    }
    return 0xB1;
}
}

extern "C" {
#pragma push
#pragma dont_inline on
extern "C" {
void menuCBPokemonEntryButtonTask_20041006() {
    s32 num;
    int i;

    num = toolentryTaisenGetEntryPlayerNum();
    toolentryTaisenGetBattleType();
    toolentryTaisenGetHomePlace(0);
    toolentryTaisenGetHomePlace(1);
    toolentryTaisenGetHomePlace(2);
    toolentryTaisenGetHomePlace(3);
    for (i = 0; i < num; i++) {
        if (toolentryTaisenGetBattleVersus() == 4) {
            int player = i;
            if (_menuCBPokemonEntryGetEntryFlag(player) != 0) {
                toolentryTaisenGetControlerType(player);
                void* trainer = menuCBBios_GetTrainer();
                if (M2C_FIELD(trainer, s32 *, 4) == 1 || M2C_FIELD(trainer, s32 *, 4) == 2 || M2C_FIELD(trainer, s32 *, 4) == 3) {
                    s32 pad = toolentryTaisenGetControlerType(player);
                    if (gbaCommandIsConnected(pad) == 0) {
                        M2C_FIELD(&_menuCBPokemonWork, s8 *, 0x22C) = 0;
                        if ((s32) M2C_FIELD(&_menuCBPokemonWork, s32 *, 0x230) < 0) {
                            M2C_FIELD(&_menuCBPokemonWork, s32 *, 0x230) = pad;
                        }
                    }
                }
            }
        }
        if (_menuCBPokemonEntryGetEntryFlag(i) == 0) {
            if (toolentryTaisenGetBattleVersus() == 4) {
                toolentryTaisenGetControlerType(i);
                void* trainer = menuCBBios_GetTrainer();
                if (M2C_FIELD(trainer, s32 *, 4) == 1 || M2C_FIELD(trainer, s32 *, 4) == 2 || M2C_FIELD(trainer, s32 *, 4) == 3) {
                    _menuCBPokemonEntryEntCheckGBA((GSinputDevice)(toolentryTaisenGetControlerType(i)), i);
                } else {
                    _menuCBPokemonEntryEntCheck((GSinputDevice)(toolentryTaisenGetControlerType(i)), i);
                }
            }
            if (toolentryTaisenGetControlerType(i) == 1 && toolentryTaisenGetHomePlace(i) == 0) {
                toolentryTaisengetEtnryPokemonOrderNum(i);
                _menuCBPokemonEntryPokemonNum(i);
            }
        }
    }
}
}
#pragma pop
}

extern "C" {

}

static void _menuCBPokemonEntryEntCheckGBA(GSinputDevice inputDevice, long player) {
    u32 linkStatus;
    u8 gbaOrder[8];
    s32 order[6];
    f32* track;
    s32 result;
    s32 count;
    s32 i;

    toolentryTaisenGetBattlePlayerID(player);
    gbaCommandEntryResult(inputDevice, (s32*)&linkStatus);
    switch (linkStatus & 0xFF000000) {
    case 0x01000000:
        count = toolentryTaisengetEtnryPokemonOrderNum(player);
        result = toolentryTaisenSetEtnryPokemonOrder(player, count);
        if (result >= 0) {
            if (!pauseIsPause()) {
                GSsndPlay(0x19, 0, 0);
            }
            track = _menuCBPokemonWork.track[player];
            track[result] = (f32)((5 - result) * 0x18);
            track[result + 6] = 0.0f;
            _menuCBPokemonEntryEntCheckDebug(player);
        }
        break;
    case 0xFF000000:
        count = toolentryTaisengetEtnryPokemonOrderNum(player);
        if (count != toolentryTaisenDeleteEtnryPokemonOrder(player)) {
            if (!pauseIsPause()) {
                GSsndPlay(0x12, 0, 0);
            }
        }
        break;
    case 0:
        count = toolentryTaisenGetEntryPokemonNum(player);
        gbaCommandEntryPokemon(linkStatus, gbaOrder);
        for (i = 0; i < count; i++) {
            order[i] = gbaOrder[i];
        }
        toolentryTaisenSetEtnryPokemonOrderGBA(player, count, order);
        _menuCBPokemonEntrySetEntryFlag(player, true);
        break;
    case 0x03000000:
        _menuCBPokemonWork.connected = 0;
        if (_menuCBPokemonWork.f230 < 0) {
            _menuCBPokemonWork.f230 = inputDevice;
        }
        break;
    }
}

static void _menuCBPokemonEntryEntCheckDebug(long) {
}

extern "C++" {
static inline u32 _btnTrg(s32 dev) {
    return GSinputButtonsPressed(dev) & GSinputButtonsChanged(dev);
}

static void _menuCBPokemonEntryEntCheck(GSinputDevice inputDevice, long player) {
    f32* track;
    s32 i;
    u32 buttons;
    s32 result;
    s32 count;
    u8* trainer;
    s32 num;

    buttons = _btnTrg(inputDevice);
    toolentryTaisenGetBattlePlayerID(player);
    if (pauseIsPause() == 0 && (*windowGetKeyInfo() & 0x400) == 0 && windowSearchID(0xE2) == NULL) {
        if (buttons & 0x140) {
            if (buttons & 0x40) {
                count = toolentryTaisengetEtnryPokemonOrderNum(player);
                if (count != toolentryTaisenDeleteEtnryPokemonOrder(player)) {
                    GSsndPlay(0x12, 0, 0);
                }
            } else if (buttons & 0x100) {
                trainer = (u8*)menuCBBios_GetTrainerImmediately(player);
                num = toolentryTaisenGetEntryPokemonNum(player);
                i = *(s32*)(trainer + 0x20);
                if (i >= (u16)menuCBPokemonEntryPokemonNumMin(player)) {
                    for (; i < num; i++) {
                        *(s32*)(trainer + 8 + i * 4) = 0xF;
                        (*(s32*)(trainer + 0x20))++;
                    }
                    GSsndPlay(0x11, 0, 0);
                }
            }
        } else if (buttons & 0xC0F) {
            result = _menuCBPokemonEntryButtonCheck(buttons, player);
            if (result >= 0) {
                result = toolentryTaisenSetEtnryPokemonOrder(player, result);
                if (result >= 0) {
                    GSsndPlay(0x19, 0, 0);
                    track = _menuCBPokemonWork.track[player];
                    track[result] = (f32)((5 - result) * 0x18);
                    track[result + 6] = 0.0f;
                }
            }
        }
    }
}
}

static s32 _menuCBPokemonEntryButtonCheck(u32 buttons, long player) {
    s32 r = -1;
    s32 num = toolentryTaisenGetPokemonNum(player);
    if (buttons & 1) {
        r = 0;
    }
    if (buttons & 8) {
        r = 1;
    }
    if (buttons & 0x800) {
        r = 2;
    }
    if (buttons & 4) {
        r = 3;
    }
    if (buttons & 2) {
        r = 4;
    }
    if (buttons & 0x400) {
        r = 5;
    }
    if (num <= r) {
        return -1;
    }
    return r;
}

static void _menuCBPokemonEntryWork(void) {
    void* trainers[4];
    s32 i;
    for (i = 0; i < 4; i++) {
        trainers[i] = menuCBBios_GetTrainerFromVersusBattleID(i);
        if (trainers[i] != 0) {
            _menuCBPokemonWork.trainerKind[i] = *(s32*)((u8*)trainers[i] + 0x28);
        } else {
            _menuCBPokemonWork.trainerKind[i] = -1;
        }
    }
}

extern "C" {
u16 menuCBPokemonEntryPokemonNumMin(s32 player) {
    u16 n;
    u16 max;
    if (pGCB->entries[pGCB->cur].flag == 0) {
        max = pGCB->entries[pGCB->cur].value;
    } else {
        max = 1;
    }
    n = _menuCBPokemonEntryPokemonNum(player);
    if (n < max) {
        return n;
    }
    return max;
}
}

static u16 _menuCBPokemonEntryPokemonNum(long player) {
    u16 max = menuCBBios_ParticipationPokemonMax();
    u16 n = toolentryTaisenGetPokemonNum(player);
    if (n < max) {
        return n;
    }
    return max;
}

static void _menuCBPokemonEntryWorkInit(void) {
    s32 hero;
    s32 pad;
    s32 j;
    s32 type = toolentryTaisenGetBattleType();
    s32 count = toolentryTaisenGetEntryPlayerNum();
    s32 i;
    _menuCBPokemonWork.connected = 1;
    _menuCBPokemonWork.f230 = -1;
    _menuCBPokemonWork.f220 = 0.0f;
    _menuCBPokemonWork.f224 = 0;
    _menuCBPokemonWork.f2C = 0;
    _menuCBPokemonWork.f154 = 0;
    _menuCBPokemonWork.f0 = 0;
    _menuCBPokemonWork.fC = 0;
    for (i = 0; i < count; i++) {
        void* trainer = menuCBBios_GetTrainerImmediately(i);
        pad = menuCBTrainerBios_GetControlerID();
        hero = menuCBBios_GetHeroImmediately(i);
        _menuCBPokemonEntrySetEntryFlag(i, false);
        if (*(s32*)((u8*)trainer + 4) != 0) {
            s32 mode;
            gbaCommandSendWazaText(pad, hero);
            if (type == 1) {
                mode = 2;
            } else {
                mode = 1;
            }
            gbaCommandEntryRequest(pad, (s32)(_menuCBPokemonEntryPokemonNum(i)), (u16)(menuCBPokemonEntryPokemonNumMin(i)), mode);
        }
    }
    for (j = 0; j < 4; j++) {
        toolentryTaisenInitPokemonOrder(j);
    }
    _menuCBPokemonEntryWork();
    _menuCBPokemonEntryDispPosition();
}

extern "C" {
void menuCBPokemonEntryTexWorkInit(void) {
    s32 i;
    s32 j;
    _menuCBPokemonWork.f2C = 0;
    _menuCBPokemonWork.readFlag = 0;
    for (i = 0; i < 4; i++) {
        PokemonEntryFace* group = _menuCBPokemonWork.faces[i];
        for (j = 0; j < 6; j++) {
            PokemonEntryFace* entry = &group[j];
            entry->active = 0;
            entry->value = 0;
        }
    }
}

u8 menuCBPokemonEntryGetReadFlag(void) {
    return _menuCBPokemonWork.readFlag;
}
}

static void _menuCBPokemonEntrySetEntryFlag(long player, bool flag) {
    _menuCBPokemonWork.entryFlag[player] = flag;
}

static u8 _menuCBPokemonEntryGetEntryFlag(long player) {
    return _menuCBPokemonWork.entryFlag[player];
}

static void _menuCBPokemonEntryDispPosition(void) {
    switch (toolentryTaisenGetBattleType()) {
    case 0:
    case 1:
        _menuCBPokemonWork.f154 = 0x136;
        break;
    case 2:
        _menuCBPokemonWork.f154 = 0;
        break;
    default:
        _menuCBPokemonWork.f154 = 0;
        break;
    }
}

static u8 _menuCBPokemonEntryAllPlayer(void) {
    s32 count = 1;
    s32 versus = toolentryTaisenGetBattleVersus();
    s32 type = toolentryTaisenGetBattleType();
    s32 i;
    switch (type) {
    case 0:
    case 1:
        if (versus == 4) {
            count = 2;
            _menuCBPokemonWork.f150 = 4;
        } else {
            count = 2;
            _menuCBPokemonWork.f150 = versus;
        }
        break;
    case 2:
        count = 4;
        _menuCBPokemonWork.f150 = 4;
        break;
    }
    for (i = 0; i < count; i++) {
        if (_menuCBPokemonEntryGetEntryFlag(i) == 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" {
void menuCBPokemonEntryLoadTex(void) {
    menuFaceLoad_Tool(0, _menuCBPokemonEntryLoadCallBack, 0);
}
}

static Pokemon* _menuCBPokemonEntryLoadCallBack(void* flag) {
    s32 loading = 1;
    Pokemon* pokemon;
    s32 player;
    s32 slot;
    toolentryTaisenGetEntryPlayerNum();
    toolentryTaisenGetBattleType();
    if (flag != 0) {
        *(u8*)flag = 1;
    }
    do {
        if (_menuCBPokemonWork.f2C == 0x18) {
            loading = 0;
            _menuCBPokemonWork.readFlag = 1;
            pokemon = 0;
        } else {
            PokemonEntryFace* face;
            u16 id;
            player = _menuCBPokemonWork.f2C / 6;
            slot = _menuCBPokemonWork.f2C % 6;
            if (menuCBBattleStartGetStatus() == 0) {
                pokemon = toolentryTaisenGetPokemonPtr(player, slot);
            } else if (toolentryTaisenGetEntryPokemonNum(player) <= slot) {
                pokemon = 0;
            } else {
                pokemon = toolentryTaisenGetEntryPokemonPtr(player, slot);
            }
            face = _menuCBPokemonEntryGetFaceBase(player, slot);
            id = menuFaceGetID2(pokemon, _menuCB_pokemonGetDeoxysSel(player, true));
            if (id != 0 && pokemonGetStatus(pokemon, 0, 0x6E, 0) != 0) {
                loading = 0;
                face->active = 1;
                face->face = id;
                uToolPokemon_faceId = id;
                _menuCBPokemonWork.f2C++;
            } else {
                face->active = 0;
                _menuCBPokemonWork.f2C++;
            }
        }
    } while (loading != 0);
    return pokemon;
}

static PokemonEntryFace* _menuCBPokemonEntryGetFaceBase(long player, long slot) {
    return &_menuCBPokemonWork.faces[player][slot];
}

extern "C" {
void menuCBPokemonEntryPokemonFaceFree(void) {
    menuCBPokemonEntryTexWorkInit();
}

s32 menuCBPokemonEntryDispPokemonFace(s32 a, s32 b, u32 player, s32 slot) {
    PokemonEntryFace* face = _menuCBPokemonEntryGetFaceBase(player, slot);
    if (face->active != 0) {
        menuFaceDispFromID(a, b, face->face);
        return 1;
    }
    return 0;
}
}
