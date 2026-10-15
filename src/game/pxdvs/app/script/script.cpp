// Script helper functions called from the script command handlers.
// Built with -inline deferred: functions are written in reverse object order.
// WIP: being written from the bottom of the object upwards.
#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct GSvec { f32 x, y, z; };
struct FloorCharacter;
typedef u16 char16;
struct HeroPokemonGetParam {
    u8 trainerSexID;
    u8 catchLevel;
    u16 pokemonDataID;
    u16 shadowPokemonDataID;
    u16 friendLevel;
    u16 move1;
    u16 move2;
    u16 move3;
    u16 move4;
    u32 trainerRnd;
    char16* trainerNamePtr;
    char16* nicknamePtr;
    u32 catchFloorID;
    u32 exp;
};
class DarkPokemon {
public:
    void setCatchBallID(u16);
    void setCatchFloorId(u16);
    void setUpdate(bool);
    void setSnatchIndex(u8);
    void setRnd(u32);
};
struct Pokemon {
    DarkPokemon* getDarkPokemon();
    u32 getRnd() const;
};
struct Hero {
    s32 getFollowerResID();
    u32 getHeroRnd() const;
    s32 pokemonGet(HeroPokemonGetParam*, bool);
    Pokemon* getPokemon(long, bool&);
    u8 getMeetDarkPokemonCount() const;
    void setMeetDarkPokemonCount(u8);
};
struct PeopleRangeInfo_t {
    s32 index;
    s32 hit;
    GSvec pos;
    f32 distance;
};
struct CursorPos { s16 x; s16 y; };
enum GSmodelAnimType {};
class tagPeopleWork {
public:
    u8 reserved0[0x10];
    u32 flags;
    u8 reserved14[0x8];
    s32 info;
    u8 reserved20[0x28];
    s32 anim;
    u8 reserved4C[0xE0];
    f32 frame;
    void setAnimType(GSmodelAnimType);
    void setAnimIndex(int);
    void setAnimFrame(f32);
    void setAnimRate(f32, bool);
};
class GSeffect {
public:
    bool m_active;
    bool m_visible;
    GSeffect* m_next;
    bool Start();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32 dt);
    virtual void _render(void* layer, int pass);
    virtual void _fastRender();
    virtual ~GSeffect();
};
class glowEffect : public GSeffect {
public:
    f32 scale;
    u8 r;
    u8 g;
    u8 b;
    u8 subtract;
    u8 mode;
    glowEffect();
    virtual ~glowEffect();
};
class PCBOX {
public:
    static PCBOX* getPointer();
    Pokemon* getPokemon(s8, s8);
};
class FloorBgmMask {
public:
    void startMECallback();
    void endMECallback();
};

#define ABS(x) ((x) > 0 ? (x) : -(x))

extern "C" {
u32 GSinputButtonsPressed(s32);
s8 GSinputGetLeftStickXData(s32, s32);
s8 GSinputGetLeftStickYData(s32, s32);
FloorCharacter* floorCharacterBiosGetCurrentPtr(s32);
void floorCharacterBiosSetVisibility(FloorCharacter*, u8);
void floorCharacterBiosSetPos(FloorCharacter*, GSvec*);
Hero* savedataGetStatus(s32, s32);
Pokemon* heroBiosGetPokemonPtr(Hero*, u16);
u8 pokemonCheckValid(Pokemon*);
u8 pokemonBiosGetDarkFlag(Pokemon*);
f32 pokemonGetDp(Pokemon*);
s32 pokemonGetStatus(Pokemon*, s32, s32, s32);
void etctoolSetPokemonNakigoe(u16);
s32 heroPokemonGetBlacky(Hero*, s32);
s32 heroPokemonGetEifie(Hero*, s32);
s32 heroPokemonGetPrasle(Hero*, s32);
s32 heroPokemonGetHouou(Hero*, s32);
s32 heroPokemonGetPikachu(Hero*, s32);
s32 heroPokemonGetCelebi(Hero*, s32);
void* memset(void*, int, u32);
u8 heroBiosGetSexDataId(Hero*);
u32 heroBiosGetRnd(Hero*);
char16* heroBiosGetNamePtr(Hero*);
u32 floorGetCurrent();
char16* GSmsgGetGSchar(s32);
s32 pokecoloGetLanguage();
void GScharMakeFromSJIS(char16*, const char*);
u16 pokemonDB_GetGrowDataId(u16);
void* pokemonGrowDataBiosGetPtr(u16);
u32 pokemonGrowDataBiosGetExp(void*, u8);
void darkPokemonBiosSetStatusRnd(u16, u8, s8);
void exribbonSetEarthRibbon(Pokemon*);
s32 heroGetStatus(Hero*, s32, u16);
void heroSetStatus(Hero*, s32, s32);
s32 floorEventGetTresure(s32, s32, s32);
s32 heroItemAddItemDataId(Hero*, u16, u16, s32);
s32 heroItemDecItemDataId(Hero*, u16, u16, s32);
s32 heroItemCheckHaveItemDataId(Hero*, u16);
void GScolsys2SetObjEnable(s32, u8);
void heroAddPokedoru(Hero*, s32);
void heroDecPokedoru(Hero*, s32);
void heroAddPokecoupon(Hero*, s32);
void heroDecPokecoupon(Hero*, s32);
void GSflagOn(s32);
void GSflagOff(s32);
void* fightEncountDataBiosGetPtr(u16);
u8 fightEncountDataBiosGetZenmetuFlag(void*);
void floorExecSoundScript();
void scriptBattleMountainEnd(s32);
void floorSetFadeScript(s32, s32);
s32 fightEncount(u16);
u16 fightGetFightResultId();
u8 fightFloorIsGcHeroWin(s32, u16);
void GSthreadSwitch();
void fadeSet(u16, f32);
struct GSlight;
Hero* getHeroPtr__4HeroFv();
s32 getFollowerID__4HeroFv(Hero*);
f32 GSgfxVideoGetLastRenderTime();
u8 GSgfxVideoGetVsyncRate();
u32 HSD_Rand();
void floorSetOffscreenIndex(s32);
void floorOffscreenPlayWait();
void heroMoveInitEvent();
void heroMoveTermEvent();
void winMsgOpenFieldWithSE(s32, s32, s32, s32);
void winMsgCloseField(s32);
void heroMoveJoinMember(s32);
void heroMoveDismissMember(s32);
u8 memoDataSetMemoFlag(s32);
GSlight* GSresGetResourceAllGroup(s32);
void GSlogWrite(const char*, ...);
void GSlightSetActive(GSlight*, u8);
void GSlightSetAnimIndex(GSlight*, s32);
void GSlightSetAnimRate(GSlight*, f32);
void GSlightSetAnimFrame(GSlight*, f32);
void GSlightSetAnimType(GSlight*, s32);
void GSlightStartAnimation(GSlight*);
void GSlightStopAnimation(GSlight*);
u8 GSlightHasAnimationEnded(GSlight*);
u8 heroMoveGetResID(s32*, s32*, u8);
void heroMoveChkHinderClear(u8);

struct _GSmodel;
struct GSpart;
struct FloorDoor {
    s8 motionOpen;
    s8 motionClose;
    u8 reserved2[3];
    s8 animOn;
    s8 animOff;
    u8 reserved7;
    u8 part;
    u8 reserved9[0xB];
    u32 resID;
};
extern FloorDoor* floor_door_list;
extern u32* floor_door_list_number;
_GSmodel* floorGetResource(s32, s32);
void GSmodelUseRootJointAnimation(_GSmodel*, s32);
void* floorDataBiosGetPtr(s32);
s32 floorDataBiosGetGroupID(void*);
void peopleAttach(s32, s32, s32, s32, s32);
void peopleSetPosXYZ(s32, s32, f32, f32, f32);
void peopleSetRotXYZ(s32, s32, f32, f32, f32);
void peopleSetPos(s32, s32, GSvec*);
void peopleSetSpeedRate(s32, s32, f32);
void peopleWalkTo(s32, s32, s32, GSvec*);
u8 peopleMoveCheck(s32, s32, s32);
void peopleRotateToAngle(s32, s32, f32, f32);
void peopleDetach(s32, s32, s32);
void GSsndPlayNow(s32);
void GSsndStopNow(s32);
GSpart* GSmodelGetPart(_GSmodel*, s32);
void GSpartGetTransform(GSpart*, GSvec*, GSvec*, GSvec*);
void GSpartFree(GSpart*);
u8 GSmodelCanAnimate(_GSmodel*);
void GSmodelSetAnimIndex(_GSmodel*, s32);
void GSmodelGetFrameCount(_GSmodel*, f32*, s32);
void GSmodelSetAnimFrame(_GSmodel*, f32);
void GSmodelSetAnimRate(_GSmodel*, f32);
void GSmodelSetAnimType(_GSmodel*, s32);
void GSmodelStartAnimation(_GSmodel*);
u8 GSmodelHasAnimationEnded(_GSmodel*);

void peopleRemoveNeckTarget(s32, s32, f32);
void peopleSetNeckTargetHero(s32, s32);
void peopleSetFlagOn(s32, s32, s32);
void peopleSetFlagOff(s32, s32, s32);

s32 menuGetCursorFromItemID(s32, s32);
void cursorBiosSetPos(s32, CursorPos);
void menuFieldMain(s32);
tagPeopleWork* peopleGet(s32, s32);
_GSmodel* peopleBiosGetModelPtr(tagPeopleWork*);
f32 peopleViewerGetPlaySpeedRate(tagPeopleWork*);
void GSmodelSetTexAnimIndex(_GSmodel*, s32);
void GSmodelSetTexAnimFrame(_GSmodel*, f32);
void GSmodelSetTexAnimRate(_GSmodel*, f32);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon*, u16);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
_GSmodel* GSresGetResource(s32, s32);
s32 floorGetCurrentGroupID();
void GSlensFlareSetVisible(_GSmodel*, u8);
void GSlensFlareSetSunPosition(_GSmodel*, GSvec*);
FloorBgmMask* floorSound_getBgmMaskObj();
u32 soundGetBGMID();
s32 soundGetEnvID();
s32 soundGetVolume();
void GSsndPause(s32, u32, s32);
void GSsndContinue(s32, u32, s32);
void soundSetVolumeID(s32, u32, s32);
u8 soundPlayME(u32, u32, u8);

double cos(double);
double sin(double);
void PSVECAdd(const GSvec*, const GSvec*, GSvec*);
void PSVECSubtract(const GSvec*, const GSvec*, GSvec*);
void PSVECScale(const GSvec*, GSvec*, f32);
void PSVECNormalize(const GSvec*, GSvec*);
void PSVECCrossProduct(const GSvec*, const GSvec*, GSvec*);
f32 PSVECDistance(const GSvec*, const GSvec*);
u8 GScolsys2HitCollision(GSvec*, GSvec*, f32, u8);
s32 GScolsys2UtilGetCpPlaneLine(GSvec*, f32*, GSvec*, GSvec*, GSvec*, GSvec*);
u8 peopleInsideCheck(GSvec*, GSvec*, GSvec*, f32);
void peopleGetPos(s32, s32, GSvec*);
void* peopleInfoBiosGetPtr(s32);
f32 peopleInfoBiosGetColBallSize(void*);
void qsort(void*, u32, u32, int (*)(const void*, const void*));
void peopleInitEvent(s32, s32);
void peopleTermEvent(s32, s32);
void peopleGetNeckPos(s32, s32, GSvec*);
void peopleRotateToXYZ(s32, s32, f32, f32, f32, f32);

static s32 _scriptEventColID = -1;
static glowEffect* m_glow;
static GSvec _vHizukiWalkkPos[3];
static s32 _vHizukiWalkPosCount;
void GSflagSet(s32, s32);
u32 GSflagGet(s32);

s32 scriptIsMoveButtonPush()
{
    s32 ret = 0;
    if (GSinputButtonsPressed(1) & 0xF) {
        ret = 1;
    }
    if (ABS(GSinputGetLeftStickXData(1, 0)) > 2) {
        ret = 1;
    }
    if (ABS(GSinputGetLeftStickYData(1, 0)) > 2) {
        ret = 1;
    }
    return ret;
}

s32 scriptIsButtonPush()
{
    s32 ret = scriptIsMoveButtonPush();
    if (GSinputButtonsPressed(1) & 0x1F70) {
        ret = 1;
    }
    return ret;
}

s32 scriptIsTrigerPush()
{
    s32 ret = 0;
    if (GSinputButtonsPressed(1) & 0x1F70) {
        ret = 1;
    }
    return ret;
}

s32 scriptFloorCharSetDisp(s32 id, s32 disp)
{
    floorCharacterBiosSetVisibility(floorCharacterBiosGetCurrentPtr(id), disp != 0);
    return 1;
}

s32 scriptFloorCharSetPos(s32 id, f32 x, f32 y, f32 z)
{
    GSvec pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    floorCharacterBiosSetPos(floorCharacterBiosGetCurrentPtr(id), &pos);
    return 1;
}

s32 scriptGetPokemonNum()
{
    Hero* hero;
    u16 i;
    u16 count = 0;
    hero = savedataGetStatus(0, 2);
    for (i = 0; i < 6; i++) {
        if (pokemonCheckValid(heroBiosGetPokemonPtr(hero, i))) {
            count++;
        }
    }
    return count;
}

u16 scriptGetDarkPokemonNum()
{
    Hero* hero;
    Pokemon* pokemon;
    u16 i;
    int count = 0;
    hero = savedataGetStatus(0, 2);
    for (i = 0; i < 6; i++) {
        pokemon = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(pokemon) && pokemonBiosGetDarkFlag(pokemon)) {
            count++;
        }
    }
    return count;
}

u16 scriptGetDarkPointZeroPokemonNum()
{
    Hero* hero;
    Pokemon* pokemon;
    u16 i;
    int count = 0;
    hero = savedataGetStatus(0, 2);
    for (i = 0; i < 6; i++) {
        pokemon = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(pokemon) && pokemonBiosGetDarkFlag(pokemon) && pokemonGetDp(pokemon) == 0.0f) {
            count++;
        }
    }
    return count;
}

s32 scriptGetPokemonNickName(s32 index)
{
    if (index >= 6) {
        return 0;
    }
    Pokemon* pokemon = heroBiosGetPokemonPtr(savedataGetStatus(0, 2), index);
    if (pokemon == 0) {
        return 0;
    }
    return pokemonGetStatus(pokemon, 0, 0x77, 0);
}

void scriptPlayPokemonNakigoe(u16 id)
{
    etctoolSetPokemonNakigoe(id);
}

s32 scriptCatchPokemon(s32 kind)
{
    static u16 rnd_status_id[6] = { 0x93, 0x94, 0x95, 0x96, 0x97, 0x98 };
    char16 nickname[0x20];
    HeroPokemonGetParam param;
    Hero* hero = savedataGetStatus(0, 2);
    u8 type = kind;

    switch (type) {
    case 1: return heroPokemonGetBlacky(hero, 0x259);
    case 2: return heroPokemonGetEifie(hero, 0x259);
    case 3: return heroPokemonGetPrasle(hero, 0x259);
    case 4: return heroPokemonGetHouou(hero, 0xFF);
    case 5: return heroPokemonGetPikachu(hero, 0xFF);
    case 6: return heroPokemonGetCelebi(hero, 0xFF);
    }

    memset(&param, 0, sizeof(param));
    param.pokemonDataID = 0;
    param.shadowPokemonDataID = 0;
    param.catchLevel = 5;
    param.friendLevel = 0x46;
    param.move1 = 1;
    param.trainerSexID = heroBiosGetSexDataId(hero);
    param.trainerRnd = heroBiosGetRnd(hero);
    param.trainerNamePtr = heroBiosGetNamePtr(hero);
    param.catchFloorID = floorGetCurrent();
    param.exp = 0;

    switch (type) {
    case 7:
        param.pokemonDataID = 0xAF;
        param.shadowPokemonDataID = 0x51;
        param.catchLevel = 0x19;
        param.friendLevel = 0;
        param.move1 = 0x10A;
        param.move2 = 0xA1;
        param.move3 = 0xF6;
        param.move4 = 0x10E;
        break;
    case 8:
        param.pokemonDataID = 0xEF;
        param.catchLevel = 0x14;
        param.trainerSexID = 0;
        param.trainerRnd = 0xA1B8;
        param.trainerNamePtr = GSmsgGetGSchar(0x1828);
        param.move1 = 8;
        param.move2 = 7;
        param.move3 = 9;
        param.move4 = 0xEE;
        switch (pokecoloGetLanguage()) {
        case 2: GScharMakeFromSJIS(nickname, "ZAPRONG"); break;
        case 3: GScharMakeFromSJIS(nickname, "ZAPRONG"); break;
        case 4: GScharMakeFromSJIS(nickname, "ZAPRONG"); break;
        case 5: GScharMakeFromSJIS(nickname, "ZAPRONG"); break;
        case 6: GScharMakeFromSJIS(nickname, "ZAPRONG"); break;
        default: GScharMakeFromSJIS(nickname, "ZAPRONG"); break;
        }
        param.nicknamePtr = nickname;
        break;
    case 9:
        param.pokemonDataID = 0x164;
        param.catchLevel = 0x14;
        param.trainerSexID = 0;
        param.trainerRnd = 0x911D;
        param.trainerNamePtr = GSmsgGetGSchar(0x17B9);
        param.move1 = 0xDF;
        param.move2 = 0x5D;
        param.move3 = 0xF7;
        param.move4 = 0xC5;
        break;
    case 10:
        param.pokemonDataID = 0xD5;
        param.catchLevel = 0x14;
        param.trainerSexID = 0;
        param.trainerRnd = 0x911D;
        param.trainerNamePtr = GSmsgGetGSchar(0x17B9);
        param.move1 = 0x5C;
        param.move2 = 0xA4;
        param.move3 = 0xBC;
        param.move4 = 0xE3;
        break;
    case 11:
        param.pokemonDataID = 0xF6;
        param.catchLevel = 0x14;
        param.trainerSexID = 0;
        param.trainerRnd = 0x911D;
        param.trainerNamePtr = GSmsgGetGSchar(0x17B9);
        param.move1 = 0xC9;
        param.move2 = 0x15D;
        param.move3 = 0x2C;
        param.move4 = 0xC8;
        break;
    case 12:
        param.pokemonDataID = 0x98;
        param.move1 = 0xF6;
        param.move2 = 0x21;
        param.move3 = 0x2D;
        param.move4 = 0x152;
        break;
    case 13:
        param.pokemonDataID = 0x9B;
        param.move1 = 0xB3;
        param.move2 = 0x21;
        param.move3 = 0x2B;
        param.move4 = 0x133;
        break;
    case 14:
        param.pokemonDataID = 0x9E;
        param.move1 = 0xF2;
        param.move2 = 0xA;
        param.move3 = 0x2B;
        param.move4 = 0x134;
        break;
    }

    void* grow = pokemonGrowDataBiosGetPtr(pokemonDB_GetGrowDataId(param.pokemonDataID));
    if (grow == 0) {
        return 0;
    }
    param.exp = pokemonGrowDataBiosGetExp(grow, param.catchLevel);
    if (param.pokemonDataID) {
        param.trainerRnd = (hero->getHeroRnd() & 0xFFFF0000) | (param.trainerRnd & 0xFFFF);
        s32 slot = hero->pokemonGet(&param, true);
        if (param.shadowPokemonDataID) {
            bool found;
            Pokemon* pokemon = hero->getPokemon((s16)slot, found);
            DarkPokemon* dark = pokemon->getDarkPokemon();
            if (dark) {
                dark->setCatchBallID(4);
                dark->setCatchFloorId(param.catchFloorID);
                dark->setUpdate(true);
                u8 count = hero->getMeetDarkPokemonCount();
                hero->setMeetDarkPokemonCount(count + 1);
                dark->setSnatchIndex(count);
                dark->setRnd(pokemon->getRnd());
                for (int i = 0; i < 6; i++) {
                    darkPokemonBiosSetStatusRnd(param.shadowPokemonDataID, i, pokemonGetStatus(pokemon, 0, rnd_status_id[i], 0));
                }
            }
        }
        return slot;
    }
    return -2;
}

u16 scriptGetEarthRibbon()
{
    Hero* hero;
    Pokemon* pokemon;
    u16 i;
    int count = 0;
    hero = savedataGetStatus(0, 2);
    for (i = 0; i < 6; i++) {
        pokemon = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(pokemon)) {
            exribbonSetEarthRibbon(pokemon);
            count++;
        }
    }
    return count;
}

void scriptStoreTemochiPokemon(Hero* hero)
{
    s32 flags[6][2];
    flags[0][0] = 0x908;
    flags[1][0] = 0x909;
    flags[2][0] = 0x90A;
    flags[3][0] = 0x90B;
    flags[4][0] = 0x90C;
    flags[5][0] = 0x90D;
    flags[0][1] = 0x90E;
    flags[1][1] = 0x90F;
    flags[2][1] = 0x910;
    flags[3][1] = 0x911;
    flags[4][1] = 0x912;
    flags[5][1] = 0x913;
    for (int i = 0; i < 6; i++) {
        Pokemon* pokemon = (Pokemon*)heroGetStatus(hero, 3, i);
        if (pokemon && pokemonCheckValid(pokemon)) {
            u16 species = pokemonGetStatus(pokemon, 0, 0x6E, 0);
            s32 id = pokemonGetStatus(pokemon, 0, 0x6F, 0);
            GSflagSet(flags[i][1], species);
            GSflagSet(flags[i][0], id);
        }
    }
}

s32 scriptCheckTemochiPokemon(Hero* hero)
{
    s32 flags[6][2];
    flags[0][0] = 0x908;
    flags[1][0] = 0x909;
    flags[2][0] = 0x90A;
    flags[3][0] = 0x90B;
    flags[4][0] = 0x90C;
    flags[5][0] = 0x90D;
    flags[0][1] = 0x90E;
    flags[1][1] = 0x90F;
    flags[2][1] = 0x910;
    flags[3][1] = 0x911;
    flags[4][1] = 0x912;
    flags[5][1] = 0x913;
    u8 used[6];
    int i;
    int j;
    int k;
    Pokemon* pokemon;
    for (i = 0; i < 6; i++) {
        used[i] = 0;
    }
    for (i = 0; i < 6; i++) {
        if (GSflagGet(flags[i][1]) == 0) {
            continue;
        }
        for (j = 0; j < 6; j++) {
            if (used[j] == 0) {
                pokemon = (Pokemon*)heroGetStatus(hero, 3, j);
                if (pokemon && pokemonCheckValid(pokemon)) {
                    pokemonGetStatus(pokemon, 0, 0x6E, 0);
                    u32 id = pokemonGetStatus(pokemon, 0, 0x6F, 0);
                    if (id == GSflagGet(flags[i][0])) {
                        break;
                    }
                }
            }
        }
        if (j >= 6) {
            return 1;
        }
        used[j] = 1;
    }
    for (k = 0; k < 6; k++) {
        if (used[k] == 0) {
            pokemon = (Pokemon*)heroGetStatus(hero, 3, k);
            if (pokemon && pokemonCheckValid(pokemon)) {
                return 1;
            }
        }
    }
    return 0;
}

s32 scriptGetItem(s32 group, s32 id)
{
    return floorEventGetTresure(4, group, id);
}

s32 scriptAddItem(s32 item, s32 count)
{
    s32 ret;
    if (count > 0) {
        ret = heroItemAddItemDataId(0, item, count, -1);
    } else if (count < 0) {
        count = -count;
        ret = heroItemDecItemDataId(0, item, count, -1);
    }
    return ret;
}

u8 scriptHaveItem(s32 item)
{
    return heroItemCheckHaveItemDataId(0, item);
}

void scriptSetCol(s32 id, u8 enable)
{
    if (id >= 0) {
        GScolsys2SetObjEnable(id, enable);
    }
}

s32 scriptSetEventColID(s32 id)
{
    s32 old = _scriptEventColID;
    _scriptEventColID = id;
    return old;
}

s32 scriptGetEventColID()
{
    return _scriptEventColID;
}

void scriptSetEventCol(u8 enable)
{
    scriptSetCol(scriptGetEventColID(), enable);
}

s32 scriptGetPokedoru()
{
    return heroGetStatus(0, 0xC, 0);
}

s32 scriptAddPokedoru(s32 n)
{
    if (n >= 0) {
        heroAddPokedoru(0, n);
    } else {
        heroDecPokedoru(0, -n);
    }
    return scriptGetPokedoru();
}

s32 scriptGetPremium()
{
    return GSflagGet(0x319);
}

void scriptSetPremium(s32 n)
{
    GSflagSet(0x319, n);
}

s32 scriptAddPremium(s32 n)
{
    s32 value = GSflagGet(0x319);
    value += n;
    GSflagSet(0x319, value);
    return value;
}

s32 scriptGetPoint()
{
    return heroGetStatus(0, 0xD, 0);
}

void scriptSetPoint(s32 n)
{
    heroSetStatus(0, 0xD, n);
}

s32 scriptAddPoint(s32 n)
{
    scriptGetPoint();
    if (n >= 0) {
        heroAddPokecoupon(0, n);
    } else {
        heroDecPokecoupon(0, -n);
    }
    return scriptGetPoint();
}

u16 scriptEncount(u16 id, u8 fade, s32 noFade)
{
    s32 result;
    u8 lost = 0;
    GSflagOff(0x323);
    void* data = fightEncountDataBiosGetPtr(id);
    if (GSflagGet(0x30D)) {
        GSflagOff(0x323);
        if (GSflagGet(0x30D)) {
            floorExecSoundScript();
        } else {
            scriptBattleMountainEnd(0);
            floorSetFadeScript(0, 0x5960008);
        }
    } else {
        if (fade || noFade) {
            GSflagOn(0x323);
        }
        result = fightEncount(id);
        if (fightEncountDataBiosGetZenmetuFlag(data) && !fightFloorIsGcHeroWin(0, fightGetFightResultId())) {
            GSthreadSwitch();
            GSthreadSwitch();
            GSthreadSwitch();
            lost = 1;
        }
        if (noFade == 0 && !lost && fade) {
            fadeSet(2, 0.5f);
        }
    }
    GSflagOff(0x323);
    return result;
}

void scriptWaitTime(f32 time)
{
    f32 elapsed = 0.0f;
    while (elapsed < time) {
        GSthreadSwitch();
        elapsed += GSgfxVideoGetLastRenderTime() / (f32)GSgfxVideoGetVsyncRate();
    }
}

u32 scriptGetRandom(u32 range)
{
    u32 low = HSD_Rand();
    u32 high = HSD_Rand() << 16;
    return (high | low) % range;
}

s32 controlTVScreen()
{
    floorSetOffscreenIndex(-1);
    floorOffscreenPlayWait();
    return 1;
}

s32 controlTV(s32)
{
    heroMoveInitEvent();
    controlTVScreen();
    scriptWaitTime(3.0f);
    winMsgOpenFieldWithSE(1, 1, 0, 5);
    winMsgCloseField(1);
    heroMoveTermEvent();
    return 1;
}

void scriptPartyChange(u8 join)
{
    getHeroPtr__4HeroFv();
    if (join) {
        heroSetStatus(0, 0x18, 1);
        heroMoveJoinMember(1);
    } else {
        heroSetStatus(0, 0x18, 0);
        heroMoveDismissMember(1);
    }
}

u8 scriptSetMemoFlag()
{
    return memoDataSetMemoFlag(0);
}

void scriptLightSetDisp(s32 id, s32 disp)
{
    GSlight* light = GSresGetResourceAllGroup(id);
    if (light == 0) {
        GSlogWrite("ライト[%d]の取得にしっぱい\n", id);
    } else {
        GSlightSetActive(light, disp != 0);
    }
}

void scriptLightSetMotion(s32 id, s32 anim, s32 frame, s32 loop)
{
    GSlight* light = GSresGetResourceAllGroup(id);
    if (light == 0) {
        GSlogWrite("ライト[%d]の取得にしっぱい\n", id);
    } else {
        GSlightSetAnimIndex(light, anim);
        GSlightSetAnimRate(light, 0.5f);
        GSlightSetAnimFrame(light, frame);
        if (loop) {
            GSlightSetAnimType(light, 1);
        } else {
            GSlightSetAnimType(light, 0);
        }
        GSlightStartAnimation(light);
    }
}

void scriptLightStopMotion(s32 id)
{
    GSlight* light = GSresGetResourceAllGroup(id);
    if (light == 0) {
        GSlogWrite("ライト[%d]の取得にしっぱい\n", id);
    } else {
        GSlightStopAnimation(light);
    }
}

s32 scriptLighgtWaitMotion(s32 id, s32 wait)
{
    GSlight* light = GSresGetResourceAllGroup(id);
    if (light == 0) {
        GSlogWrite("ライト[%d]の取得にしっぱい\n", id);
        return 0;
    }
    for (;;) {
        if (GSlightHasAnimationEnded(light)) {
            return 0;
        }
        if (!wait) {
            break;
        }
        GSthreadSwitch();
    }
    return 0;
}

void scriptCheckHizukiFollow()
{
    s32 group;
    s32 id;
    Hero* hero = getHeroPtr__4HeroFv();
    if (heroMoveGetResID(&group, &id, getFollowerID__4HeroFv(hero))) {
        heroMoveChkHinderClear(getFollowerID__4HeroFv(hero));
    }
}

s32 floorEventCtrlElevatorFollower(s32 floorID, u32 doorIndex, u16 mode, u32 type);
s32 floorEventCtrlElevatorHero(s32 floorID, u32 doorIndex, u16 mode, u32 type);

s32 scriptHeroCtrlElevator(s32 floorID, u32 doorIndex, u16 mode, u32 type)
{
    Hero* hero = getHeroPtr__4HeroFv();
    if (type >= 2 && type <= 5) {
        return floorEventCtrlElevatorHero(floorID, doorIndex, mode, type);
    }
    u8 follower = getFollowerID__4HeroFv(hero);
    if (follower == 0) {
        return floorEventCtrlElevatorHero(floorID, doorIndex, mode, type);
    }
    return floorEventCtrlElevatorFollower(floorID, doorIndex, mode, type);
}

}

static void _scriptEventSetMotion(_GSmodel* model, s16 anim, f32 frame)
{
    if (model && anim >= 0) {
        GSmodelSetAnimIndex(model, anim);
        GSmodelSetAnimFrame(model, frame);
        GSmodelSetAnimRate(model, 0.5f);
        GSmodelSetAnimType(model, 0);
        GSmodelStartAnimation(model);
    }
}

static void _scriptEventWaitMotion(_GSmodel* model)
{
    if (model == 0) {
        return;
    }
    while (!GSmodelHasAnimationEnded(model)) {
        GSthreadSwitch();
    }
}

static u8 _peopleMoveCheckTime(u32 group, u32 id, f32 time)
{
    while (time > 0.0f) {
        if (!peopleMoveCheck(group, id, 0)) {
            return 0;
        }
        GSthreadSwitch();
        time -= GSgfxVideoGetLastRenderTime() / (f32)GSgfxVideoGetVsyncRate();
    }
    return 1;
}

extern "C" {

s32 floorEventCtrlElevatorHero(s32 floorID, u32 doorIndex, u16 mode, u32 type)
{
    FloorDoor* door;
    _GSmodel* model;
    s16 anim;
    f32 frame = 0.0f;
    s32 group;
    GSpart* part;
    s32 sound;
    anim = -1;
    getHeroPtr__4HeroFv();
    if (doorIndex >= *floor_door_list_number) {
        return -1;
    }
    door = &floor_door_list[doorIndex];
    if (door->resID == 0) {
        return -1;
    }
    model = floorGetResource(floorID, door->resID);
    if (model == 0) {
        return -1;
    }
    GSmodelUseRootJointAnimation(model, 1);
    group = floorDataBiosGetGroupID(floorDataBiosGetPtr(floorID));
    if (type >= 2 && type <= 5) {
        peopleAttach(0, 100, group, door->resID, door->part);
        peopleSetPosXYZ(0, 100, 0.0f, 0.0f, 0.0f);
        _scriptEventSetMotion(model, mode, 0.0f);
        return 0;
    }
    switch (mode) {
    case 1:
    case 2:
    case 0x81:
    case 0x82: {
        GSvec pos;
        GSvec target;
        _scriptEventSetMotion(model, door->motionOpen, frame);
        sound = mode & 0x80;
        if (sound) {
            GSsndPlayNow(0x27);
        }
        _scriptEventWaitMotion(model);
        part = GSmodelGetPart(model, door->part);
        GSpartGetTransform(part, &pos, 0, 0);
        GSpartFree(part);
        if (mode & 1) {
            peopleSetSpeedRate(0, 100, 2.0f);
            peopleWalkTo(0, 100, 1, &pos);
            peopleMoveCheck(0, 100, 1);
            peopleRotateToAngle(0, 100, 0.0f, 2.0f);
        } else {
            peopleDetach(0, 100, 0);
            GSpart* part2 = GSmodelGetPart(model, door->part);
            GSpartGetTransform(part2, &pos, 0, 0);
            GSpartFree(part2);
            target = pos;
            peopleSetPos(0, 100, &target);
            peopleSetSpeedRate(0, 100, 2.0f);
            target.z += 25.0f;
            peopleWalkTo(0, 100, 1, &target);
            scriptWaitTime(0.5f);
        }
        _scriptEventSetMotion(model, door->motionClose, frame);
        if (sound) {
            GSsndPlayNow(0x27);
        }
        _scriptEventWaitMotion(model);
        peopleMoveCheck(0, 100, 1);
        peopleSetSpeedRate(0, 100, 1.0f);
        break;
    }
    case 0xC0:
        _scriptEventWaitMotion(model);
        if (mode & 0x80) {
            GSsndStopNow(0x29);
            GSsndPlayNow(0x2A);
        }
        break;
    case 0x100:
        break;
    default:
        if (mode & 4) {
            anim = door->animOn;
        } else if (mode & 8) {
            anim = door->animOff;
        }
        if (anim < 0) {
            return -1;
        }
        if (!GSmodelCanAnimate(model)) {
            return -1;
        }
        if (mode & 0x20) {
            peopleAttach(0, 100, group, door->resID, door->part);
            if (type) {
                peopleSetPosXYZ(0, 100, 0.0f, 0.0f, 0.0f);
                peopleSetRotXYZ(0, 100, 0.0f, 0.0f, 0.0f);
            } else {
                peopleSetPosXYZ(0, 100, 0.0f, 0.0f, 0.0f);
                peopleSetRotXYZ(0, 100, 0.0f, 0.0f, 0.0f);
            }
        }
        if (mode & 0x10) {
            GSmodelSetAnimIndex(model, anim);
            GSmodelGetFrameCount(model, &frame, 0);
            frame -= 1.0f;
        }
        _scriptEventSetMotion(model, anim, frame);
        if (mode & 0x40) {
            floorEventCtrlElevatorHero(floorID, doorIndex, 0xC0, type);
        } else if (mode & 0x80) {
            GSsndPlayNow(0x29);
        }
        break;
    }
    GSmodelGetFrameCount(model, &frame, 0);
    return 100.0f * (2.0f * frame / (f32)GSgfxVideoGetVsyncRate());
}

s32 floorEventCtrlElevatorFollower(s32 floorID, u32 doorIndex, u16 mode, u32 type)
{
    Hero* hero;
    FloorDoor* door;
    _GSmodel* model;
    s16 anim;
    f32 frame = 0.0f;
    u8 ok;
    s32 group;
    GSpart* part;
    s32 sound;
    anim = -1;
    ok = 0;
    hero = getHeroPtr__4HeroFv();
    if (doorIndex >= *floor_door_list_number) {
        return -1;
    }
    door = &floor_door_list[doorIndex];
    if (door->resID == 0) {
        return -1;
    }
    model = floorGetResource(floorID, door->resID);
    if (model == 0) {
        return -1;
    }
    GSmodelUseRootJointAnimation(model, 1);
    group = floorDataBiosGetGroupID(floorDataBiosGetPtr(floorID));
    if (type >= 2 && type <= 5) {
        peopleAttach(0, 100, group, door->resID, door->part);
        peopleAttach(0, hero->getFollowerResID(), group, door->resID, door->part);
        switch (type) {
        case 2:
            peopleSetPosXYZ(0, 100, 0.0f, 0.0f, 5.0f);
            peopleSetPosXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, -5.0f);
            break;
        case 3:
            peopleSetPosXYZ(0, 100, 0.0f, 0.0f, -5.0f);
            peopleSetPosXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, 5.0f);
            break;
        case 4:
            peopleSetPosXYZ(0, 100, 5.0f, 0.0f, 0.0f);
            peopleSetPosXYZ(0, hero->getFollowerResID(), -5.0f, 0.0f, 0.0f);
            break;
        case 5:
            peopleSetPosXYZ(0, 100, -5.0f, 0.0f, 0.0f);
            peopleSetPosXYZ(0, hero->getFollowerResID(), 5.0f, 0.0f, 0.0f);
            break;
        }
        peopleRemoveNeckTarget(0, hero->getFollowerResID(), 1.0f);
        _scriptEventSetMotion(model, mode, 0.0f);
        return 0;
    }
    switch (mode) {
    case 1:
    case 2:
    case 0x81:
    case 0x82: {
        GSvec pos;
        GSvec heroPos;
        GSvec followerPos;
        _scriptEventSetMotion(model, door->motionOpen, frame);
        sound = mode & 0x80;
        if (sound) {
            GSsndPlayNow(0x27);
        }
        _scriptEventWaitMotion(model);
        part = GSmodelGetPart(model, door->part);
        GSpartGetTransform(part, &pos, 0, 0);
        GSpartFree(part);
        if (mode & 1) {
            peopleRemoveNeckTarget(0, hero->getFollowerResID(), 1.0f);
            peopleSetSpeedRate(0, 100, 2.0f);
            peopleSetSpeedRate(0, hero->getFollowerResID(), 2.0f);
            pos.z -= 5.0f;
            peopleWalkTo(0, 100, 1, &pos);
            followerPos.x = pos.x;
            followerPos.y = pos.y;
            followerPos.z = 10.0f + pos.z;
            scriptWaitTime(0.2f);
            if (_vHizukiWalkPosCount != 0) {
                for (int i = 0; i < _vHizukiWalkPosCount; i++) {
                    peopleWalkTo(0, hero->getFollowerResID(), 1, &_vHizukiWalkkPos[i]);
                    ok = _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
                    if (ok) {
                        break;
                    }
                }
            }
            if (!ok) {
                peopleWalkTo(0, hero->getFollowerResID(), 1, &followerPos);
            }
            peopleMoveCheck(0, 100, 1);
            if (!ok) {
                ok = _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
            }
            peopleRotateToAngle(0, 100, 0.0f, 2.0f);
            if (!ok) {
                peopleRotateToAngle(0, hero->getFollowerResID(), 0.0f, 2.0f);
            }
        } else {
            peopleDetach(0, 100, 0);
            peopleDetach(0, hero->getFollowerResID(), 0);
            peopleSetNeckTargetHero(0, hero->getFollowerResID());
            part = GSmodelGetPart(model, door->part);
            GSpartGetTransform(part, &pos, 0, 0);
            GSpartFree(part);
            heroPos.x = pos.x;
            heroPos.y = pos.y;
            heroPos.z = 5.0f + pos.z;
            peopleSetPos(0, 100, &heroPos);
            followerPos.x = pos.x;
            followerPos.y = pos.y;
            followerPos.z = pos.z - 5.0f;
            peopleSetPos(0, hero->getFollowerResID(), &followerPos);
            heroPos.z += 25.0f;
            followerPos.z += 25.0f;
            peopleSetSpeedRate(0, 100, 2.0f);
            peopleSetSpeedRate(0, hero->getFollowerResID(), 2.0f);
            peopleSetFlagOff(0, 100, 0x2000);
            peopleSetFlagOff(0, hero->getFollowerResID(), 0x2000);
            peopleWalkTo(0, 100, 1, &heroPos);
            scriptWaitTime(0.2f);
            peopleWalkTo(0, hero->getFollowerResID(), 1, &followerPos);
            scriptWaitTime(0.5f);
        }
        _scriptEventSetMotion(model, door->motionClose, frame);
        if (sound) {
            GSsndPlayNow(0x27);
        }
        _scriptEventWaitMotion(model);
        peopleMoveCheck(0, 100, 1);
        peopleMoveCheck(0, hero->getFollowerResID(), 1);
        peopleSetSpeedRate(0, 100, 1.0f);
        peopleSetSpeedRate(0, hero->getFollowerResID(), 1.0f);
        break;
    }
    case 0xC0:
        _scriptEventWaitMotion(model);
        if (mode & 0x80) {
            GSsndStopNow(0x29);
            GSsndPlayNow(0x2A);
        }
        break;
    case 0x100:
        break;
    default:
        if (mode & 4) {
            anim = door->animOn;
        } else if (mode & 8) {
            anim = door->animOff;
        }
        if (anim < 0) {
            return -1;
        }
        if (!GSmodelCanAnimate(model)) {
            return -1;
        }
        peopleSetFlagOn(0, 100, 0x2000);
        peopleSetFlagOn(0, hero->getFollowerResID(), 0x2000);
        if (mode & 0x20) {
            peopleAttach(0, 100, group, door->resID, door->part);
            peopleAttach(0, hero->getFollowerResID(), group, door->resID, door->part);
            if (type) {
                peopleSetPosXYZ(0, 100, 0.0f, 0.0f, 5.0f);
                peopleSetRotXYZ(0, 100, 0.0f, 0.0f, 0.0f);
                peopleSetPosXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, -5.0f);
                peopleSetRotXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, 0.0f);
            } else {
                peopleSetPosXYZ(0, 100, 0.0f, 0.0f, -5.0f);
                peopleSetRotXYZ(0, 100, 0.0f, 0.0f, 0.0f);
                peopleSetPosXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, 5.0f);
                peopleSetRotXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, 0.0f);
            }
            peopleRemoveNeckTarget(0, hero->getFollowerResID(), 1.0f);
        }
        if (mode & 0x10) {
            GSmodelSetAnimIndex(model, anim);
            GSmodelGetFrameCount(model, &frame, 0);
            frame -= 1.0f;
        }
        _scriptEventSetMotion(model, anim, frame);
        if (mode & 0x40) {
            floorEventCtrlElevatorHero(floorID, doorIndex, 0xC0, type);
            peopleSetFlagOff(0, 100, 0x2000);
            peopleSetFlagOff(0, hero->getFollowerResID(), 0x2000);
        } else if (mode & 0x80) {
            GSsndPlayNow(0x29);
        }
        break;
    }
    GSmodelGetFrameCount(model, &frame, 0);
    return 100.0f * (2.0f * frame / (f32)GSgfxVideoGetVsyncRate());
}

void scriptOpenItemMenu()
{
    CursorPos pos;
    s32 cursor = menuGetCursorFromItemID(0x2C, 0x9B);
    if (cursor < 0) {
        cursor = 0;
    }
    pos.x = 0;
    pos.y = (s8)cursor;
    cursorBiosSetPos(2, pos);
    menuFieldMain(1);
}

}

static u32 _searchPeopleColiInfo(GSvec* center, f32 radius, PeopleRangeInfo_t* info, int count, GSvec* target)
{
    int i;
    u32 mask = 0;
    for (i = 0; i < count; i++, info++) {
        GSvec offset;
        info->index = i;
        f32 angle = (f32)i * (6.2831855f / (f32)count);
        offset.x = radius * (f32)cos(angle);
        offset.y = 0.0f;
        offset.z = radius * (f32)sin(angle);
        PSVECAdd(&offset, center, &info->pos);
        if (GScolsys2HitCollision(center, &info->pos, 4.0f, 0)) {
            info->hit = 1;
            mask |= 1 << i;
        } else {
            info->hit = 0;
        }
        info->distance = PSVECDistance(&info->pos, target);
    }
    return mask;
}

static u8 _checkCrossPeople(GSvec* from, GSvec* to, GSvec* lineStart, GSvec* lineEnd)
{
    GSvec p2;
    GSvec p1;
    GSvec p0;
    GSvec dirB;
    GSvec dirA;
    GSvec cross;
    GSvec normal;
    f32 t;
    p0.x = from->x;
    p0.y = from->y;
    p0.z = from->z;
    p1.x = to->x;
    p1.y = to->y;
    p1.z = to->z;
    p2.x = p1.x;
    p2.y = p1.y;
    p2.z = p1.z;
    p2.y = 1.0f;
    PSVECSubtract(&p0, &p1, &dirA);
    PSVECNormalize(&dirA, &dirA);
    PSVECSubtract(&p0, &p2, &dirB);
    PSVECNormalize(&dirB, &dirB);
    PSVECCrossProduct(&dirA, &dirB, &normal);
    if (GScolsys2UtilGetCpPlaneLine(&cross, &t, &normal, &p0, lineStart, lineEnd) == 0) {
        return 0;
    }
    if (t < 0.0f || t > 1.0f) {
        return 0;
    }
    return 1;
}

static int _fnDistanceSortFunc(const void* a, const void* b)
{
    if (((const PeopleRangeInfo_t*)a)->distance == ((const PeopleRangeInfo_t*)b)->distance) {
        return 0;
    }
    if (((const PeopleRangeInfo_t*)a)->distance > ((const PeopleRangeInfo_t*)b)->distance) {
        return 1;
    }
    return -1;
}

extern "C" {

u8 scriptPeopleInsideCheck(GSvec* a, GSvec* b, GSvec* point, f32 radius)
{
    GSvec p;
    GSvec mid;
    p.x = point->x;
    p.y = point->y;
    p.z = point->z;
    if (PSVECDistance(a, b) < 20.0f) {
        return peopleInsideCheck(a, b, &p, radius);
    }
    PSVECAdd(a, b, &mid);
    PSVECScale(&mid, &mid, 0.5f);
    if (peopleInsideCheck(a, &mid, &p, radius)) {
        return 1;
    }
    return peopleInsideCheck(&mid, b, &p, radius);
}

s32 scriptHizukiAway(s32 group, s32 id)
{
    PeopleRangeInfo_t info[8];
    GSvec neck;
    GSvec followerPos;
    GSvec heroPos;
    GSvec targetPos;
    s32 heroGroup;
    s32 heroID;
    s32 followerGroup;
    s32 followerID;
    Hero* hero;
    GSvec* pos;
    PeopleRangeInfo_t* entry;
    u8 ok;
    int i;

    followerPos.x = 0.0f;
    followerPos.y = 0.0f;
    followerPos.z = 0.0f;
    hero = getHeroPtr__4HeroFv();
    if (!heroMoveGetResID(&followerGroup, &followerID, getFollowerID__4HeroFv(hero))) {
        return 0;
    }
    peopleGetPos(followerGroup, followerID, &followerPos);
    if (!heroMoveGetResID(&heroGroup, &heroID, 0)) {
        return 0;
    }
    peopleGetPos(heroGroup, heroID, &heroPos);
    tagPeopleWork* work = peopleGet(group, id);
    if (work == 0) {
        return 0;
    }
    peopleGetPos(group, id, &targetPos);
    void* peopleInfo = peopleInfoBiosGetPtr(work->info);
    if (peopleInfo == 0) {
        return 0;
    }
    f32 size = peopleInfoBiosGetColBallSize(peopleInfo);
    size += 1.0f;
    if (!scriptPeopleInsideCheck(&heroPos, &targetPos, &followerPos, 1.0f + size)) {
        return 0;
    }

    _searchPeopleColiInfo(&heroPos, 8.0f, info, 8, &followerPos);
    qsort(info, 8, sizeof(PeopleRangeInfo_t), _fnDistanceSortFunc);
    for (i = 0; i < 8; i++) {
        entry = &info[i];
        if (entry->hit == 1) {
            continue;
        }
        pos = &entry->pos;
        if (scriptPeopleInsideCheck(&heroPos, &targetPos, pos, 4.0f)) {
            continue;
        }
        if (scriptPeopleInsideCheck(&followerPos, pos, &heroPos, 4.0f)) {
            continue;
        }
        if (_checkCrossPeople(&heroPos, &targetPos, &followerPos, pos)) {
            continue;
        }
        peopleInitEvent(followerGroup, followerID);
        peopleWalkTo(followerGroup, followerID, 1, pos);
        ok = _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
        if (!ok && (entry->index & 1)) {
            s32 next = -1;
            if (entry->index == 3 || entry->index == 5) {
                next = 4;
            }
            if (entry->index == 1 || entry->index == 7) {
                next = 0;
            }
            PeopleRangeInfo_t* other = info;
            for (int j = 0; j < 8; j++) {
                if (other->index == next) {
                    break;
                }
                other++;
            }
            if (other->hit == 0 && !scriptPeopleInsideCheck(&heroPos, &targetPos, &other->pos, 4.0f)) {
                peopleWalkTo(followerGroup, followerID, 1, &other->pos);
                ok = _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
            }
        }
        if (!ok) {
            peopleGetNeckPos(followerGroup, followerID, &neck);
            peopleRotateToXYZ(followerGroup, followerID, neck.x, neck.y, neck.z, 1.0f);
            _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
        }
        peopleTermEvent(followerGroup, followerID);
        return 0;
    }

    _searchPeopleColiInfo(&followerPos, 8.0f, info, 8, &followerPos);
    qsort(info, 8, sizeof(PeopleRangeInfo_t), _fnDistanceSortFunc);
    for (i = 0; i < 8; i++) {
        entry = &info[i];
        if (entry->hit == 1) {
            continue;
        }
        pos = &entry->pos;
        if (scriptPeopleInsideCheck(&followerPos, pos, &heroPos, 4.0f)) {
            continue;
        }
        if (_checkCrossPeople(&heroPos, &targetPos, &followerPos, pos)) {
            continue;
        }
        if (scriptPeopleInsideCheck(&heroPos, &targetPos, pos, 4.0f)) {
            continue;
        }
        peopleInitEvent(followerGroup, followerID);
        peopleWalkTo(followerGroup, followerID, 1, pos);
        if (!_peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f)) {
            peopleGetNeckPos(followerGroup, followerID, &neck);
            peopleRotateToXYZ(followerGroup, followerID, neck.x, neck.y, neck.z, 1.0f);
            _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
        }
        peopleTermEvent(followerGroup, followerID);
        return 0;
    }
    return 0;
}


s32 scriptSetEndedMotion(s32 group, s32 id, s32 anim, u8 loop)
{
    tagPeopleWork* work = peopleGet(group, id);
    if (work == 0) {
        return 0;
    }
    _GSmodel* model = peopleBiosGetModelPtr(work);
    if (model == 0) {
        return 0;
    }
    work->setAnimType((GSmodelAnimType)0);
    for (;;) {
        if (GSmodelHasAnimationEnded(model)) {
            break;
        }
        GSthreadSwitch();
    }
    work->anim = anim;
    work->frame = 0.0f;
    work->setAnimIndex(anim);
    work->setAnimFrame(0.0f);
    work->setAnimRate(0.5f, true);
    GSmodelSetTexAnimIndex(model, anim);
    GSmodelSetTexAnimFrame(model, 0.0f);
    GSmodelSetTexAnimRate(model, 0.5f * peopleViewerGetPlaySpeedRate(work));
    if (loop) {
        work->setAnimType((GSmodelAnimType)1);
    } else {
        work->setAnimType((GSmodelAnimType)0);
    }
    work->flags |= 0x4000;
    return 1;
}

s32 scriptPokemonRememberWaza(Pokemon* pokemon, s32 waza)
{
    s32 found = 0;
    for (int i = 0; i < 4; i++) {
        if (waza == pokemonBiosGetPokemonWazaDataId(pokemon, i)) {
            found = 1;
        }
    }
    return found;
}

s32 scriptPokemonTeachWazaIndex(s32 waza)
{
    switch (waza) {
    case 0x22: return 0;
    case 0x26: return 1;
    case 0x45: return 2;
    case 0x66: return 3;
    case 0x8A: return 4;
    case 0x56: return 5;
    case 0xA4: return 6;
    case 0xC4: return 7;
    case 0xCF: return 8;
    case 0x8F: return 9;
    case 0x78: return 10;
    case 0xAB: return 11;
    }
    return -1;
}

void scriptGlowStart(f32 scale, u8 r, u8 g, u8 b, u8 additive, u8 mode)
{
    if (m_glow == 0) {
        m_glow = new glowEffect();
    }
    m_glow->scale = scale;
    m_glow->r = r;
    m_glow->g = g;
    m_glow->b = b;
    if (additive) {
        m_glow->subtract = 0;
    } else {
        m_glow->subtract = 1;
    }
    m_glow->mode = mode;
    m_glow->Start();
}

void scriptGlowEnd()
{
    if (m_glow) {
        delete m_glow;
        m_glow = 0;
    }
}

void scriptSetLensFlare(u32 resID, u8 visible, f32 x, f32 y, f32 z)
{
    if (resID) {
        _GSmodel* flare = GSresGetResource(floorGetCurrentGroupID(), resID);
        if (flare) {
            GSlensFlareSetVisible(flare, 0);
            GSvec pos;
            pos.x = x;
            pos.y = y;
            pos.z = z;
            GSlensFlareSetSunPosition(flare, &pos);
            GSlensFlareSetVisible(flare, visible);
        }
    }
}

s32 pcBoxAllSearchPokemon(s32 id)
{
    for (s8 box = 0; box < 8; box++) {
        for (s8 slot = 0; slot < 30; slot++) {
            if (id == pokemonBiosGetPokemonDataId(PCBOX::getPointer()->getPokemon(box, slot))) {
                return 1;
            }
        }
    }
    return 0;
}

u8 scriptSoundOpenPlayME(u32 id, u32 time, u8 flag)
{
    u32 bgm;
    s32 env;
    s32 volume;
    u8 ret;
    FloorBgmMask* mask;
    f32 wait;
    mask = floorSound_getBgmMaskObj();
    wait = (f32)time / 1000.0f;
    bgm = soundGetBGMID();
    env = soundGetEnvID();
    volume = soundGetVolume();
    GSflagSet(0x8FA, 1);
    if (mask) {
        mask->startMECallback();
    }
    if (bgm != -1) {
        GSsndPause(bgm, time, 0);
        soundSetVolumeID(env, time, 0);
        scriptWaitTime(wait);
    }
    ret = soundPlayME(id, time, flag);
    if (id != -1) {
        GSsndContinue(bgm, time, 0);
        soundSetVolumeID(env, time, volume);
        scriptWaitTime(wait);
    }
    if (mask) {
        mask->endMECallback();
    }
    GSflagSet(0x8FA, 0);
    return ret;
}
}
