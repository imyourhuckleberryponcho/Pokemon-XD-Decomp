// STATUS (snC): 12/23 exact with extra_cflags=["-inline noauto"]. Stubs (empty): menuCB_PokemonEntry, ButtonTask_20041006, EntCheck, EntCheckGBA. WIP: DeoxysParamCustom 72%, TexWorkInit 66%, WorkInit 92%.
// Pokemon entry screen for battle (menuCB_PokemonEntry).
#include <dolphin/types.h>

#pragma peephole off

class Pokemon;

struct GSinputDevice;

struct PokemonEntryFace {
    u8 active;
    u8 pad1;
    u16 face;
    u32 value;
    u32 pad8;
};

struct PokemonEntryWork {
    s32 f0;                       // 0x00
    bool entryFlag[4];            // 0x04
    s8 trainerKind[4];            // 0x08
    s32 fC;                       // 0x0C
    u8 pad10[0x1C];               // 0x10
    s32 f2C;                      // 0x2C
    PokemonEntryFace faces[4][6]; // 0x30
    s32 f150;                     // 0x150
    s32 f154;                     // 0x154
    u8 readFlag;                  // 0x158
    u8 pad159[7];                 // 0x159
    f32 track[4][12];             // 0x160 (player * 0x30)
    f32 f220;                     // 0x220
    s32 f224;                     // 0x224
    u8 pad228[4];                 // 0x228
    u8 connected;                 // 0x22C
    u8 pad22D[3];                 // 0x22D
    s32 f230;                     // 0x230
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
s32 menuCBBattleStartGetStatus(u16);
void menuCBBattleStartTrainerFaceFree(void);
void menuCB_SE_Play(s32, s32, s32);
void menuCB_GBADisconnectedErrorJob(void);
void* menuFaceLoad_Tool(s32, Pokemon* (*)(void*), s32);
u16 menuFaceGetID2(Pokemon*, u8);
void menuFaceDispFromID(s32, s32, u16);
u32 pokemonGetStatus(Pokemon*, u16, u16, u16);
u8 pokemon_GetSeikaku(Pokemon*);
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
static void _menuCBPokemonEntryEntCheckGBA(GSinputDevice* dev, long player);
static void _menuCBPokemonEntryEntCheck(GSinputDevice* dev, long player);
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

static void _menuCB_DeoxysParamCustom(Pokemon* pokemon, u16 player) {
    u32 level = pokemonGetStatus(pokemon, 0, 0x7A, 0);
    u32 seikaku = pokemon_GetSeikaku(pokemon);
    u32 b0 = pokemonGetStatus(pokemon, 0, 0x94, 0);
    u32 b1 = pokemonGetStatus(pokemon, 0, 0x95, 0);
    u32 b2 = pokemonGetStatus(pokemon, 0, 0x96, 0);
    u32 b3 = pokemonGetStatus(pokemon, 0, 0x97, 0);
    u32 b4 = pokemonGetStatus(pokemon, 0, 0x98, 0);
    u32 e0 = pokemonGetStatus(pokemon, 0, 0x8E, 0);
    u32 e1 = pokemonGetStatus(pokemon, 0, 0x8F, 0);
    u32 e2 = pokemonGetStatus(pokemon, 0, 0x90, 0);
    u32 e3 = pokemonGetStatus(pokemon, 0, 0x91, 0);
    u32 e4 = pokemonGetStatus(pokemon, 0, 0x92, 0);
    u32 s0 = (level * (b0 + (_GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][0] * 2 + e0 / 4))) / 100;
    u32 s1 = (level * (b1 + (_GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][1] * 2 + e1 / 4))) / 100;
    u32 s2 = (level * (b2 + (_GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][2] * 2 + e2 / 4))) / 100;
    u32 s3 = (level * (b3 + (_GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][3] * 2 + e3 / 4))) / 100;
    u32 s4 = (level * (b4 + (_GBA_DeokisisuParamTable[_menuCB_pokemonGetDeoxysSel(player, false)][4] * 2 + e4 / 4))) / 100;
    u16 r0 = pokemonAdjustValueBySeikaku(seikaku, 0x88, s0 + 5);
    u16 r1 = pokemonAdjustValueBySeikaku(seikaku, 0x89, s1 + 5);
    u16 r2 = pokemonAdjustValueBySeikaku(seikaku, 0x8A, s2 + 5);
    u16 r3 = pokemonAdjustValueBySeikaku(seikaku, 0x8B, s3 + 5);
    u16 r4 = pokemonAdjustValueBySeikaku(seikaku, 0x8C, s4 + 5);
    pokemonBiosSetPhyAtk(pokemon, r0);
    pokemonBiosSetPhyDef(pokemon, r1);
    pokemonBiosSetSpeAtk(pokemon, r2);
    pokemonBiosSetSpeDef(pokemon, r3);
    pokemonBiosSetNimbleness(pokemon, r4);
}

static u8 _menuCB_pokemonGetDeoxysSel(u16 player, bool flag) {
    u8 sel = 0;
    u16 slot = *(u32*)((u8*)_CB + player * 0x1320 + 0x3C) - 1;
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
s32 menuCB_PokemonEntry(void) {
    return 0;
}

void menuCBPokemonEntryButtonTask_20041006(void) {
}
}

static void _menuCBPokemonEntryEntCheckGBA(GSinputDevice* dev, long player) {
}

static void _menuCBPokemonEntryEntCheckDebug(long) {
}

static void _menuCBPokemonEntryEntCheck(GSinputDevice* dev, long player) {
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
    void** p = trainers;
    s8* w = (s8*)&_menuCBPokemonWork;
    s32 i = 0;
    do {
        *p = menuCBBios_GetTrainerFromVersusBattleID(i);
        if (*p != 0) {
            w[8] = *(s32*)((u8*)*p + 0x28);
        } else {
            w[8] = -1;
        }
        p++;
        w++;
        i++;
    } while (i < 4);
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
        s32 pad = menuCBTrainerBios_GetControlerID();
        s32 hero = menuCBBios_GetHeroImmediately(i);
        _menuCBPokemonEntrySetEntryFlag(i, false);
        if (*(s32*)((u8*)trainer + 4) != 0) {
            s32 mode;
            u16 min;
            gbaCommandSendWazaText(pad, hero);
            if (type == 1) {
                mode = 2;
            } else {
                mode = 1;
            }
            min = menuCBPokemonEntryPokemonNumMin(i);
            gbaCommandEntryRequest(pad, _menuCBPokemonEntryPokemonNum(i), min, mode);
        }
    }
    i = 0;
    do {
        toolentryTaisenInitPokemonOrder(i);
        i++;
    } while (i < 4);
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
        for (j = 0; j < 6; j++) {
            _menuCBPokemonWork.faces[i][j].active = 0;
            _menuCBPokemonWork.faces[i][j].value = 0;
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
            player = (u16)(_menuCBPokemonWork.f2C / 6);
            slot = _menuCBPokemonWork.f2C % 6;
            if (menuCBBattleStartGetStatus(_menuCBPokemonWork.f2C / 6) == 0) {
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

s32 menuCBPokemonEntryDispPokemonFace(s32 a, s32 b, u16 player, s32 slot) {
    PokemonEntryFace* face = _menuCBPokemonEntryGetFaceBase(player, slot);
    if (face->active != 0) {
        menuFaceDispFromID(a, b, face->face);
        return 1;
    }
    return 0;
}
}
