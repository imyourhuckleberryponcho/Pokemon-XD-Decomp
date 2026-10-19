#include <dolphin/types.h>

// AppScript: the game's script object (command handlers for the game-specific
// script classes, extension functions and methods).
// STATUS: 34/36 exact. Left: fncPrintf (its 0x100 zero buffer template must be
// the first .rodata object; the original created it earlier in the file) and execExtendGlobalFunction
// (0x99 PSVECDistance argument order/register, 0x9B/0x9D argument scheduling).
#pragma pool_strings off
#pragma peephole off

struct GSvec { f32 x, y, z; };
struct Pokemon {
    u8 isLegend() const;
};
struct _GSmodel;
struct GSlight;
struct GXColor { u8 r, g, b, a; };
struct ScriptPeople { s32 group; s32 object; };
struct GSresID { s32 group; s32 id; };

namespace GSscript {
void tigaErrMessage(const char*);
struct tigaVariant;
struct tigaArrayFixed { tigaVariant* get(int); };
struct tigaWaza { void* sequence; void* waza; };
struct tigaVariant {
    s16 type;
    u16 flags;
    union { s32 integer; f32 real; void* pointer; } value;
    s32 getCnvInteger();
    char* getCnvString(char*);
    GSvec* getCnvVector();
    f32 getCnvSingle();
    inline f32 getSingle() {
        if (type == 1) return (f32)value.integer;
        if (type == 2) return value.real;
        return getCnvSingle();
    }
    inline s32 getInteger() {
        if (type == 1) return value.integer;
        if (type == 2) return (s32)value.real;
        return getCnvInteger();
    }
    inline char* getString(char* buf) {
        if (type == 3) return (char*)value.pointer;
        return getCnvString(buf);
    }
    inline GSvec* getVector() {
        if (type == 4) return (GSvec*)value.pointer;
        return getCnvVector();
    }
    inline void* getObject(s16 expected, const char* message) {
        if (type == expected) return value.pointer;
        tigaErrMessage(message);
        return 0;
    }
    inline void setSingle(f32 n) { type = 2; value.real = n; }
    inline void setInteger(s32 n) { type = 1; value.integer = n; }
    inline void setObject(s16 t, void* p) { type = t; value.pointer = p; }
    inline void dupIfNeeded();
};
struct TigaThread {
    u8 reserved[0x14C];
    s32 line;
};
struct TigaObjManager {
    s32 getResourceIdx(GSresID*);
    GSresID* newResource();
    GSresID* getResource(int);
};
struct tigaCellMemory {
    void dupVariant(tigaVariant*);
};
struct TigaContext {
    u8 reserved[0x10];
    tigaVariant result;
    u8 reserved18[0x120];
    GSvec vector;
};
class Tiga {
public:
    u8 reserved[0x18];
    TigaObjManager objManager;
    u8 reserved19[0x8F7];
    tigaCellMemory* cellMemory;
    TigaContext* context;
    u8 reserved918[0x1C];
    s32 wazaCount;
    u8 reserved938[0x1C];
    char* stringBuffer;
    u8 reserved958[0xC];
    ScriptPeople* people;
    s32 objectCount;
    void** objects;
    u8 reserved970[0x10];
    TigaThread* thread;

    static Tiga* m_cpCurrentObject;

    Tiga();
    virtual s32 execExtendMethod(int, int, tigaVariant*, tigaVariant*);
    virtual s32 execExtendGlobalFunction(int, tigaVariant*, tigaVariant*);
    virtual s32 getExtendVariable(tigaVariant*, int, int);
    virtual s32 setExtendVariable(tigaVariant*, int, int);
    virtual void mapping();
    virtual void unmapping();
    virtual ~Tiga();
    void runParamsWait(int, tigaVariant*, int, tigaVariant*);
    inline void setRpVec(const GSvec* v) {
        context->vector = *v;
        context->result.value.pointer = &context->vector;
        context->result.type = 4;
    }
};
}

namespace GSscript {
inline void tigaVariant::dupIfNeeded()
{
    if (type != 1 && type != 2) {
        Tiga::m_cpCurrentObject->cellMemory->dupVariant(this);
    }
}
}

class AppScript : public GSscript::Tiga {
public:
    GSscript::tigaWaza waza[7];

    AppScript();
    virtual s32 execExtendMethod(int, int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    virtual s32 execExtendGlobalFunction(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    virtual s32 getExtendVariable(GSscript::tigaVariant*, int, int);
    virtual s32 setExtendVariable(GSscript::tigaVariant*, int, int);
    virtual void mapping();
    virtual void unmapping();
    virtual ~AppScript();
    void unload();
    s32 fncPrintf(GSscript::tigaVariant*);
    s32 cmpPeople(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpCamera(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpFloor(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpMenu(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpHero(int, GSscript::tigaVariant*, GSscript::tigaVariant*);

    s32 cmpEsaba(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpDarkPokemon(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpWaza(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpSodateya(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpTv(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpDirection(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpMail(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpPad(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpSound(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpCol(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpModel(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpLight(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpFight(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpFade(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpTask(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 cmpPokemon(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 commonCall(GSscript::tigaVariant*, GSscript::tigaVariant*);
    s32 orFlagTest(GSscript::tigaVariant*);
    s32 andFlagTest(GSscript::tigaVariant*);
    GSscript::tigaWaza* allocWazaPtr();
    void freeWazaPtr(GSscript::tigaWaza*);
};

enum darkPokemonStatus {};
enum darkPokemonWhere {};
class DarkPokemon {
public:
    s32 getStatus() const;
    u16 getPokemonID() const;
    void setStatus(darkPokemonStatus);
    void addStatus(darkPokemonStatus);
    void setSnatchIndex(u8);
    void setCatchFloorId(u16);
    void setUpdate(bool);
    void setPlace(darkPokemonWhere, u8);
};
class Hero {
public:
    u8 getMeetDarkPokemonCount() const;
    void setMeetDarkPokemonCount(u8);
};
GSscript::Tiga* floorGetCommonScript();
class FIGHT_ENCOUNT {
public:
    u8 getDirtyFlag() const;
    void clear();
    u16 getField() const;
    void setField(u16);
    u16 getMsg(u8) const;
    void setMsg(u8, u16);
    s32 getAddMode() const;
    u8 getAddPlace() const;
    u8 getAddID() const;
    void setAddMode(u8);
    void setAddPlace(u8);
    void setAddID(u8);
    s32 getSwapMode() const;
    u16 getSwapDeckNO() const;
    void setSwapMode(u8);
    void setSwapDeckNO(u16);
    void setFightMode(u8);
    s32 getDestroyFlag() const;
    void setDestroyFlag(u8);
    u8 getTrainerKind() const;
    void setTrainerKind(u8);
    s32 getRoundNo() const;
    void setRoundNo(u32);
};

extern "C" {
void soundOpenPlayME(s32, s32, u8);
u8 soundPlayME(s32, s32, u8);
u8 soundOpenPlay(s32, s32, u8);
u8 soundOpenPlayEnv(s32, s32, u8);
u8 soundStop(s32, s32);
u8 soundStopEnv(s32);
u8 soundCreateEmitter(s32, f32, f32, f32);
u8 soundCreateListener();
u8 soundSetVolume(s32, s32);
u8 scriptSoundOpenPlayME(s32, s32, u8);
u8 soundSetVolumeID(s32, s32, s32);
u8 soundOpenPlayFadeOutIn(s32, s32, s32, u8);
u8 soundOpenPlayEnvFadeOutIn(s32, s32, s32, u8);
s32 soundGetBGMID();
void peopleTalkMessageBgmMask(u8);
void peopleTalkMessageBgmSetFadeSpeed(f32, f32);
void peopleTalkMessageBgmSetVolumeRate(f32);
void soundPlayWait(s32);
void scriptSetCol(s32, u8);
s32 scriptGetEventColID();
void scriptSetEventCol(u8);
s32 scriptModelOpen(s32);
void scriptModelClose(s32);
void scriptModelSetDisp(s32, s32);
void scriptModelSetMotion(s32, s32, s32, s32);
void scriptModelStopMotion(s32);
s32 scriptModelWaitMotion(s32, s32);
s32 scriptModelAttach(s32, s32, s32);
s32 scriptModelDetach(s32);
void scriptModelSetParticle(s32, s32, u8);
void scriptModelDeleteParticle(s32, u8);
void scriptModelSetMotionRate(s32, s32, s32, f32, s32);
s32 scriptModelSetEndedMotion(s32, s32, u8);
void scriptModelPartPaticle(s32, s32, s32);
void scriptModelSetFractionalFramesFlag(s32, u8);
s32 floorGetCurrentGroupID();
void* GSresGetResource(s32, s32);
void* GSmodelGetPart(void*, s32);
void GSpartGetTransform(void*, GSvec*, GSvec*, GSvec*);
void GSpartFree(void*);
void GSmodelAddPosition(void*, GSvec*);
void GSmodelIterateList(void (*)(_GSmodel*, void*), void*);
void GSmodelSetVisibility(_GSmodel*, u8);
void GSmodelSetBoundCheck(void*, u8);
void GSmodelRecalculateBound(void*);
void GSmodelUseRootJointAnimation(void*, s32);
void scriptLightSetDisp(s32, s32);
void scriptLightSetMotion(s32, s32, s32, s32);
void scriptLightStopMotion(s32);
s32 scriptLighgtWaitMotion(s32, s32);
GSlight* lightGetLight(s32);
void GSlightSetType(GSlight*, s32);
void GSlightSetPosition(GSlight*, GSvec*);
void GSlightSetColor(GSlight*, GXColor);
void GSlightGetPosition(GSlight*, GSvec*);
s32 scriptEncount(u16, u8, s32);
u16 fightEncount(u16);
u16 fightGetFightResultId();
void fightSoundOpenPlay(u8);
void fightSoundOpenPlayEnv(u8);
FIGHT_ENCOUNT* fightEncountGetStrObj();
void fightEncountAnnihilationRecovery();
void fadeSet(u16, f32);
s8 fadeCheck(u8);
void floorExecScriptInteger(s32, s32, s32, s32, s32);
void floorExecScriptIntegerThread(s32, s32, s32, s32, s32);
void floorExecScriptIntegerByName(const char*, s32, s32, s32, s32);
void floorExecScriptIntegerByNameThread(const char*, s32, s32, s32, s32);
s32 floorGetScriptResult();
void scriptWaitTime(f32);
void scriptPlayPokemonNakigoe(u16);
void pokemonPlayVoice(Pokemon*);
void pokemonWazaCopy(Pokemon*, u16, u16);
void pokemonWazaForget(Pokemon*, s32);
s32 pokemonGetWazaCount(Pokemon*);
u8 pokemonBiosGetCatchBallId(Pokemon*);
char* pokemon_GetNicknamePtr(Pokemon*);
u8 pokemonBiosGetDarkFlag(Pokemon*);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon*, u16);
u16 pokemonBiosGetHp(Pokemon*);
s32 pokemonBiosGetDp(Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
u16 pokemonBiosGetFriend(Pokemon*);
s32 pokemonDB_GetName(u16);
u16 pokemonBiosGetItemDataId(Pokemon*);
s32 pokemonBiosGetCatchTrainerRnd(Pokemon*);
s8 pokemonSetWazaStatus(Pokemon*, u16, u8);
s32 scriptPokemonRememberWaza(Pokemon*, s32);
s32 scriptPokemonTeachWazaIndex(s32);
u8 pokemonDB_GetTeachWaza(u16, u16);
s32 menuPokemonStatusOpenWazaLearn(Pokemon*, u16);
s32 menuPokemonStatusOpenWazaLearnList(Pokemon*, u16);
u8 GSflagTest(u32);
void WazaSequence_Stop(void*);
void* memset(void*, int, u32);
int sprintf(char*, const char*, ...);
void GSlogWrite(const char*, ...);
extern u32* flag_data_number;
void GSflagOn(u32);
void GSflagOff(u32);
void GSflagSet(u32, s32);
s32 GSflagGet(u32);
s32 scriptGetRandom(s32);
void darkPokemonBiosSetInfomation(u16, u16);
void floorSetDispScriptInfo(u8);
void floorSetHumanColision(u8);
u8 floorGetHumanColision();
void peopleSetTresureSearchDistance(u16, f32);
char* GSmsgGetGSchar(s32);
s32 floorTresureGetResID(u16);
u8 wazaDB_GetHidenFlag(u16);
f32 PSVECDistance(GSvec*, GSvec*);
void GSresFreeResource(s32, s32);
void scriptGlowStart(f32, u8, u8, u8, u8, u8);
void scriptGlowEnd();
void scriptSetLensFlare(s32, u8, f32, f32, f32);
u8 GSgfxVideoGetVsyncRate();
s32 pokecoloGetCountryCode();
s32 pokecoloGetLanguage();
void GSthreadSwitch();
s32 esabaSet(s32);
u16 esabaGetPokemonID(s32);
void esabaSetEsaNum(s32, s32);
s32 esabaGetEsaNum(s32);
u8 esabaGetPokemonIsRare(s32);
Hero* savedataGetStatus(s32, s32);
DarkPokemon* darkPokemonGetDarkPokemon(u16);
void* Sequence_CreateNull();
void* Sequence_LoadWaza(void*, u16, u8, u8);
void Sequence_SetPosition(void*, GSvec*);
void Sequence_SetRotation(void*, GSvec*);
void Sequence_SetScale(void*, GSvec*);
void Sequence_Free(void*);
void WazaSequence_Start(void*, s32);
u8 WazaSequence_IsActive(void*);
void WazaSequence_Free(void*);
s32 sodateyaGetPokemonLevelUpValue();
s32 sodateyaGetPokemonDPValue();
void sodateyaRaise(s32);
void sodateyaReclaim(s32);
s32 sodateyaCalcPrice(s32);
s32 sodateyaeChekcRais();
Pokemon* sodateyaGetPokemonPtr(s32);
s32 controlTV(s32);
s32 controlTVScreen();
void evolution();
void preReliveSetParameter(s32, s32, u8);
void reliveMain();
void preReliveDisplayHokoraParticle();
s32 menuUseItemScriptCologn(s32, s32);
s32 underTakerGetMiraboPlace();
void underTakerMiraboDisAppear();
void mailMainSendByScrpt(u16);
u8 scriptSetMemoFlag();
void menuScriptReciveMail();
void menuScriptReadMail(s32);
s32 scriptIsButtonPush();
s32 scriptIsMoveButtonPush();
s32 scriptIsTrigerPush();
s32 gamedatasaveGetStatus(s32, s32);
void* floorCreateThread(s32, s32, s32, void*);
void GSthreadSetArgs(void*, s32, ...);
s32 GSinputButtonsPressed(s32);
void GSinputMotorStart(s32, u8, u8, u32, u8);
}

#define DEG_TO_RAD 0.017453292f

extern "C" {
void appScriptPlayME_Thread(u8 open, s32 id, s32 a, u8 b)
{
    if (open) {
        soundOpenPlayME(id, a, b);
    } else {
        soundPlayME(id, a, b);
    }
}

void appScriptCommonCall(int function)
{
    floorGetCommonScript()->runParamsWait(function, 0, 0, 0);
}
}

s32 AppScript::cmpEsaba(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10:
        GSthreadSwitch();
        result->setInteger(esabaSet(args[1].getInteger()));
        if (result->getInteger()) {
            soundOpenPlay(0x576, 0, 0xFF);
        }
        break;
    case 0x11: result->setInteger(esabaGetPokemonID(args[1].getInteger())); break;
    case 0x12: esabaSetEsaNum(args[1].getInteger(), args[2].getInteger()); break;
    case 0x13: result->setInteger(esabaGetEsaNum(args[1].getInteger())); break;
    case 0x14: result->setInteger(esabaGetPokemonIsRare(args[1].getInteger())); break;
    }
    return 0;
}

s32 AppScript::cmpDarkPokemon(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    Hero* hero = savedataGetStatus(0, 2);
    DarkPokemon* dark = darkPokemonGetDarkPokemon(args[1].getInteger());
    if (dark == 0) {
        result->setInteger(0);
        return 1;
    }
    switch (command) {
    case 0x10:
        if (dark->getStatus() == 4) {
            result->setInteger(1);
        } else {
            result->setInteger(0);
        }
        break;
    case 0x11:
        if (dark->getStatus() >= 3) {
            result->setInteger(1);
        } else {
            result->setInteger(0);
        }
        break;
    case 0x12: dark->setStatus((darkPokemonStatus)args[2].getInteger()); break;
    case 0x13: result->setInteger(dark->getPokemonID()); break;
    case 0x14: result->setInteger(dark->getStatus()); break;
    case 0x15: {
        u8 count = hero->getMeetDarkPokemonCount();
        hero->setMeetDarkPokemonCount(count + 1);
        dark->setSnatchIndex(count);
        dark->addStatus((darkPokemonStatus)1);
        dark->setCatchFloorId(0xB5);
        dark->setUpdate(true);
        break;
    }
    case 0x16: dark->setPlace((darkPokemonWhere)args[2].getInteger(), args[3].getInteger()); break;
    }
    return 0;
}

s32 AppScript::cmpWaza(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    GSscript::tigaWaza* waza;
    switch (command) {
    case 0x10:
        waza = allocWazaPtr();
        if (waza == 0) break;
        waza->sequence = Sequence_CreateNull();
        result->setObject(0x3A, waza);
        wazaCount++;
        break;
    case 0x11:
        waza = (GSscript::tigaWaza*)args[0].getObject(0x3A, "waza not access");
        if (waza == 0) break;
        if (waza->waza == 0) {
            waza->waza = Sequence_LoadWaza(waza->sequence, args[1].getInteger(), args[2].getInteger(), args[3].getInteger());
        }
        WazaSequence_Start(waza->waza, 0);
        if (args[4].getInteger() == 1) {
            while (WazaSequence_IsActive(waza->waza)) {
                GSthreadSwitch();
            }
        }
        break;
    case 0x12:
        waza = (GSscript::tigaWaza*)args[0].getObject(0x3A, "waza not access");
        if (waza == 0) break;
        Sequence_SetPosition(waza->sequence, args[1].getVector());
        break;
    case 0x13: {
        waza = (GSscript::tigaWaza*)args[0].getObject(0x3A, "waza not access");
        if (waza == 0) break;
        GSvec* rot = args[1].getVector();
        rot->x = DEG_TO_RAD * rot->x;
        rot->y = DEG_TO_RAD * rot->y;
        rot->z = DEG_TO_RAD * rot->z;
        Sequence_SetRotation(waza->sequence, rot);
        break;
    }
    case 0x14:
        waza = (GSscript::tigaWaza*)args[0].getObject(0x3A, "waza not access");
        if (waza == 0) break;
        Sequence_SetScale(waza->sequence, args[1].getVector());
        break;
    case 0x15:
        waza = (GSscript::tigaWaza*)args[0].getObject(0x3A, "waza not access");
        if (waza == 0) break;
        while (WazaSequence_IsActive(waza->waza)) {
            GSthreadSwitch();
        }
        break;
    case 0x16:
        waza = (GSscript::tigaWaza*)args[0].getObject(0x3A, "waza not access");
        if (waza) {
            if (waza->waza) WazaSequence_Free(waza->waza);
            if (waza->sequence) Sequence_Free(waza->sequence);
            freeWazaPtr(waza);
        }
        wazaCount--;
        break;
    }
    return 0;
}

s32 AppScript::cmpSodateya(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x11: result->setInteger(sodateyaGetPokemonLevelUpValue()); break;
    case 0x12: result->setInteger(sodateyaGetPokemonDPValue()); break;
    case 0x13: sodateyaRaise(args[1].getInteger()); break;
    case 0x14: sodateyaReclaim(args[1].getInteger()); break;
    case 0x16: result->setInteger(sodateyaCalcPrice(args[1].getInteger())); break;
    case 0x17: result->setInteger(sodateyaeChekcRais()); break;
    case 0x18: result->setObject(0x25, sodateyaGetPokemonPtr(0)); break;
    }
    return 0;
}

s32 AppScript::cmpTv(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10: result->setInteger(controlTV(args[1].getInteger())); break;
    case 0x11: result->setInteger(controlTVScreen()); break;
    }
    return 0;
}

s32 AppScript::cmpDirection(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10: evolution(); break;
    case 0x11: preReliveSetParameter(args[1].getInteger(), args[2].getInteger(), args[3].getInteger() != 0); break;
    case 0x12: reliveMain(); break;
    case 0x13: preReliveDisplayHokoraParticle(); break;
    case 0x14: result->setInteger(menuUseItemScriptCologn(args[1].getInteger(), args[2].getInteger())); break;
    case 0x15: result->setInteger(underTakerGetMiraboPlace()); break;
    case 0x16: underTakerMiraboDisAppear(); break;
    }
    return 0;
}

s32 AppScript::cmpMail(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10: mailMainSendByScrpt(args[1].getInteger()); break;
    case 0x11: result->setInteger(scriptSetMemoFlag()); break;
    case 0x12: menuScriptReciveMail(); break;
    case 0x13: menuScriptReadMail(args[1].getInteger()); break;
    case 0x14:
        menuScriptReciveMail();
        mailMainSendByScrpt(args[1].getInteger());
        menuScriptReadMail(args[1].getInteger());
        break;
    }
    return 0;
}

s32 motorFun(u8 a, u8 b, u32 time, u8 c, bool enable);

s32 AppScript::cmpPad(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10: result->setInteger(scriptIsButtonPush()); break;
    case 0x11: result->setInteger(scriptIsMoveButtonPush()); break;
    case 0x12: result->setInteger(scriptIsTrigerPush()); break;
    case 0x13:
        if (gamedatasaveGetStatus(0, 9) == 0) {
            void* thread = floorCreateThread(0x80, 0, 1, (void*)motorFun);
            GSthreadSetArgs(thread, 5, args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger(), 1);
        }
        break;
    case 0x14: result->setInteger(GSinputButtonsPressed(1)); break;
    }
    return 0;
}

s32 motorFun(u8 a, u8 b, u32 time, u8 c, bool enable)
{
    u32 n = time;
    if (!enable) {
        return 0;
    }
    while (n != 0) {
        GSinputMotorStart(1, a, b, time, c);
        GSthreadSwitch();
        n--;
    }
    return 0;
}

s32 AppScript::cmpSound(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10: result->setInteger(soundOpenPlay(args[1].getInteger(), args[2].getInteger(), args[3].getInteger())); break;
    case 0x11: result->setInteger(soundOpenPlayEnv(args[1].getInteger(), args[2].getInteger(), args[3].getInteger())); break;
    case 0x12: result->setInteger(soundStop(args[1].getInteger(), args[2].getInteger())); break;
    case 0x13: result->setInteger(soundStopEnv(args[1].getInteger())); break;
    case 0x14: result->setInteger(soundCreateEmitter(args[1].getInteger(), args[2].getSingle(), args[3].getSingle(), args[4].getSingle())); break;
    case 0x15: result->setInteger(soundCreateListener()); break;
    case 0x16: result->setInteger(soundSetVolume(args[1].getInteger(), args[2].getInteger())); break;
    case 0x17: result->setInteger(scriptSoundOpenPlayME(args[1].getInteger(), args[2].getInteger(), args[3].getInteger())); break;
    case 0x18: result->setInteger(soundSetVolumeID(args[1].getInteger(), args[2].getInteger(), args[3].getInteger())); break;
    case 0x19: result->setInteger(soundOpenPlayFadeOutIn(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger())); break;
    case 0x1A: result->setInteger(soundOpenPlayEnvFadeOutIn(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger())); break;
    case 0x1B: result->setInteger(soundGetBGMID()); break;
    case 0x1C: peopleTalkMessageBgmMask(args[1].getInteger() != 0); break;
    case 0x1D: peopleTalkMessageBgmSetFadeSpeed(args[1].getSingle(), args[2].getSingle()); break;
    case 0x1E: peopleTalkMessageBgmSetVolumeRate(args[1].getSingle()); break;
    case 0x1F: soundPlayWait(args[1].getInteger()); break;
    case 0x20: result->setInteger(soundPlayME(args[1].getInteger(), args[2].getInteger(), args[3].getInteger())); break;
    case 0x21: {
        void* thread = floorCreateThread(0x80, 0, 1, (void*)appScriptPlayME_Thread);
        GSthreadSetArgs(thread, 4, args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger());
        break;
    }
    }
    return 0;
}

s32 AppScript::cmpCol(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10: scriptSetCol(args[1].getInteger(), args[2].getInteger() != 0); break;
    case 0x11: scriptGetEventColID(); break;
    case 0x12: scriptSetEventCol(args[1].getInteger() != 0); break;
    }
    return 0;
}

static void _appScriptModelSetVisibility(_GSmodel* model, void* visible);

s32 AppScript::cmpModel(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    void* model;
    switch (command) {
    case 0x10: result->setInteger(scriptModelOpen(args[1].getInteger())); break;
    case 0x11: scriptModelClose(args[1].getInteger()); break;
    case 0x12: scriptModelSetDisp(args[1].getInteger(), args[2].getInteger()); break;
    case 0x13: scriptModelSetMotion(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger()); break;
    case 0x14: scriptModelStopMotion(args[1].getInteger()); break;
    case 0x15: result->setInteger(scriptModelWaitMotion(args[1].getInteger(), args[2].getInteger())); break;
    case 0x16: result->setInteger(scriptModelAttach(args[1].getInteger(), args[2].getInteger(), args[3].getInteger())); break;
    case 0x17: result->setInteger(scriptModelDetach(args[1].getInteger())); break;
    case 0x18: scriptModelSetParticle(args[1].getInteger(), args[2].getInteger(), args[3].getInteger()); break;
    case 0x19: scriptModelDeleteParticle(args[1].getInteger(), args[2].getInteger() != 0); break;
    case 0x1A: {
        model = GSresGetResource(floorGetCurrentGroupID(), args[1].getInteger());
        if (model == 0) {
            return 0;
        }
        void* part = GSmodelGetPart(model, args[2].getInteger());
        GSvec pos;
        GSpartGetTransform(part, &pos, 0, 0);
        GSpartFree(part);
        setRpVec(&pos);
        break;
    }
    case 0x1B:
        model = GSresGetResource(floorGetCurrentGroupID(), args[1].getInteger());
        if (model == 0) {
            return 0;
        }
        GSmodelAddPosition(model, args[2].getVector());
        break;
    case 0x1C: GSmodelIterateList(_appScriptModelSetVisibility, (void*)args[1].getInteger()); break;
    case 0x1D: scriptModelSetMotionRate(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getSingle(), args[5].getInteger()); break;
    case 0x1E:
        model = GSresGetResource(floorGetCurrentGroupID(), args[1].getInteger());
        GSmodelSetBoundCheck(model, args[2].getInteger() != 0);
        break;
    case 0x1F: result->setInteger(scriptModelSetEndedMotion(args[1].getInteger(), args[2].getInteger(), args[3].getInteger() != 0)); break;
    case 0x20: scriptModelPartPaticle(args[1].getInteger(), args[2].getInteger(), args[3].getInteger()); break;
    case 0x21: scriptModelSetFractionalFramesFlag(args[1].getInteger(), args[2].getInteger() != 0); break;
    case 0x22: GSmodelRecalculateBound(GSresGetResource(floorGetCurrentGroupID(), args[1].getInteger())); break;
    case 0x23: GSmodelUseRootJointAnimation(GSresGetResource(floorGetCurrentGroupID(), args[1].getInteger()), 1); break;
    }
    return 0;
}

static void _appScriptModelSetVisibility(_GSmodel* model, void* visible)
{
    GSmodelSetVisibility(model, visible != 0);
}

s32 AppScript::cmpLight(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10: scriptLightSetDisp(args[1].getInteger(), args[2].getInteger()); break;
    case 0x11: scriptLightSetMotion(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger()); break;
    case 0x12: scriptLightStopMotion(args[1].getInteger()); break;
    case 0x13: result->setInteger(scriptLighgtWaitMotion(args[1].getInteger(), args[2].getInteger())); break;
    case 0x14: {
        GSlight* light = lightGetLight(args[1].getInteger());
        GSlightSetType(light, args[2].getInteger());
        break;
    }
    case 0x15: {
        GSlight* light = lightGetLight(args[1].getInteger());
        GSlightSetPosition(light, args[2].getVector());
        break;
    }
    case 0x16: {
        GSlight* light = lightGetLight(args[1].getInteger());
        GXColor color;
        color.r = args[2].getInteger();
        color.g = args[3].getInteger();
        color.b = args[4].getInteger();
        color.a = args[5].getInteger();
        GSlightSetColor(light, color);
        break;
    }
    case 0x17: {
        GSvec pos;
        GSlightGetPosition(lightGetLight(args[1].getInteger()), &pos);
        setRpVec(&pos);
        break;
    }
    }
    return 0;
}

s32 AppScript::cmpFight(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    FIGHT_ENCOUNT* encount;
    switch (command) {
    case 0x10: result->setInteger(scriptEncount(args[1].getInteger(), args[2].getInteger() != 0, args[3].getInteger())); break;
    case 0x11: result->setInteger(fightEncount(args[1].getInteger())); break;
    case 0x12: result->setInteger(fightGetFightResultId()); break;
    case 0x13: fightSoundOpenPlay(args[1].getInteger() != 0); break;
    case 0x14: fightSoundOpenPlayEnv(args[1].getInteger() != 0); break;
    case 0x15:
        if (darkPokemonGetDarkPokemon(args[1].getInteger())->getStatus() > 2) {
            fightEncount(args[2].getInteger());
        } else {
            fightEncount(args[3].getInteger());
        }
        break;
    case 0x16: result->value.pointer = fightEncountGetStrObj(); break;
    case 0x17:
        encount = fightEncountGetStrObj();
        if (encount->getDirtyFlag() == 1) {
            encount->clear();
        }
        encount->setField(args[1].getInteger());
        break;
    case 0x18: result->setInteger(fightEncountGetStrObj()->getField()); break;
    case 0x19:
        encount = fightEncountGetStrObj();
        result->setInteger(encount->getMsg(args[1].getInteger()));
        break;
    case 0x1A:
        encount = fightEncountGetStrObj();
        if (encount->getDirtyFlag() == 1) {
            encount->clear();
        }
        encount->setMsg(args[1].getInteger(), args[2].getInteger());
        break;
    case 0x1B: result->setInteger(fightEncountGetStrObj()->getAddMode()); break;
    case 0x1C: result->setInteger(fightEncountGetStrObj()->getAddPlace()); break;
    case 0x1D: result->setInteger(fightEncountGetStrObj()->getAddID()); break;
    case 0x1E:
        encount = fightEncountGetStrObj();
        if (encount->getDirtyFlag() == 1) {
            encount->clear();
        }
        encount->setAddMode(args[1].getInteger());
        encount->setAddPlace(args[2].getInteger());
        encount->setAddID(args[3].getInteger());
        break;
    case 0x1F: result->setInteger(fightEncountGetStrObj()->getSwapMode()); break;
    case 0x20: result->setInteger(fightEncountGetStrObj()->getSwapDeckNO()); break;
    case 0x21:
        encount = fightEncountGetStrObj();
        if (encount->getDirtyFlag() == 1) {
            encount->clear();
        }
        encount->setSwapMode(args[1].getInteger());
        encount->setSwapDeckNO((u8)args[2].getInteger());
        break;
    case 0x22: result->setInteger(fightEncountGetStrObj()->getSwapDeckNO()); break;
    case 0x23:
        encount = fightEncountGetStrObj();
        if (encount->getDirtyFlag() == 1) {
            encount->clear();
        }
        encount->setFightMode(args[1].getInteger());
        break;
    case 0x24: result->setInteger(fightEncountGetStrObj()->getDestroyFlag()); break;
    case 0x25:
        encount = fightEncountGetStrObj();
        if (encount->getDirtyFlag() == 1) {
            encount->clear();
        }
        encount->setDestroyFlag(args[1].getInteger());
        break;
    case 0x26: result->setInteger(fightEncountGetStrObj()->getTrainerKind()); break;
    case 0x27:
        encount = fightEncountGetStrObj();
        if (encount->getDirtyFlag() == 1) {
            encount->clear();
        }
        encount->setTrainerKind(args[1].getInteger());
        break;
    case 0x28: fightEncountAnnihilationRecovery(); break;
    case 0x29: result->setInteger(fightEncountGetStrObj()->getRoundNo()); break;
    case 0x2A:
        encount = fightEncountGetStrObj();
        if (encount->getDirtyFlag() == 1) {
            encount->clear();
        }
        encount->setRoundNo(args[1].getInteger());
        break;
    }
    return 0;
}

s32 AppScript::cmpFade(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10: fadeSet(args[1].getInteger(), args[2].getSingle()); break;
    case 0x11: result->setInteger(fadeCheck(args[1].getInteger() != 0)); break;
    }
    return 0;
}

s32 AppScript::cmpTask(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    switch (command) {
    case 0x10: floorExecScriptInteger(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger(), args[5].getInteger()); break;
    case 0x11: floorExecScriptIntegerThread(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger(), args[5].getInteger()); break;
    case 0x12: floorExecScriptIntegerByName(args[1].getString(stringBuffer), args[2].getInteger(), args[3].getInteger(), args[4].getInteger(), args[5].getInteger()); break;
    case 0x13: floorExecScriptIntegerByNameThread(args[1].getString(stringBuffer), args[2].getInteger(), args[3].getInteger(), args[4].getInteger(), args[5].getInteger()); break;
    case 0x14: result->setInteger(floorGetScriptResult()); break;
    case 0x15: scriptWaitTime(args[1].getSingle()); break;
    }
    return 0;
}

s32 AppScript::cmpPokemon(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    Pokemon* pokemon;
    if (command != 0x10) {
        if (args[0].type != 0x25) {
            result->setInteger(0);
            return 1;
        }
        pokemon = (Pokemon*)args[0].getObject(0x25, "pokemon not access");
    }
    switch (command) {
    case 0x10: scriptPlayPokemonNakigoe(args[1].getInteger()); break;
    case 0x13: pokemonPlayVoice(pokemon); break;
    case 0x12: pokemonWazaCopy(pokemon, args[1].getInteger(), args[2].getInteger()); break;
    case 0x11: pokemonWazaForget(pokemon, args[1].getInteger()); break;
    case 0x14: result->setInteger(pokemonGetWazaCount(pokemon)); break;
    case 0x15: result->setInteger(pokemonBiosGetCatchBallId(pokemon)); break;
    case 0x16: result->setObject(8, pokemon_GetNicknamePtr(pokemon)); break;
    case 0x18: result->setInteger(pokemonBiosGetDarkFlag(pokemon)); break;
    case 0x19: result->setInteger(pokemonBiosGetPokemonWazaDataId(pokemon, args[1].getInteger())); break;
    case 0x1A: result->setInteger(pokemonBiosGetHp(pokemon)); break;
    case 0x1B: result->setInteger(pokemonBiosGetDp(pokemon)); break;
    case 0x1C: result->setInteger(pokemonBiosGetPokemonDataId(pokemon)); break;
    case 0x1D: result->setInteger(pokemon->isLegend()); break;
    case 0x1E: result->setInteger(pokemonBiosGetFriend(pokemon)); break;
    case 0x1F: result->setInteger(pokemonDB_GetName(pokemonBiosGetPokemonDataId(pokemon))); break;
    case 0x20: result->setInteger(pokemonBiosGetItemDataId(pokemon)); break;
    case 0x21: result->setInteger(pokemonBiosGetCatchTrainerRnd(pokemon)); break;
    case 0x22: result->setInteger(pokemonSetWazaStatus(pokemon, args[1].getInteger(), args[2].getInteger() != 0)); break;
    case 0x23: result->setInteger(scriptPokemonRememberWaza(pokemon, args[1].getInteger())); break;
    case 0x24:
        result->setInteger(pokemonDB_GetTeachWaza(pokemonBiosGetPokemonDataId(pokemon), scriptPokemonTeachWazaIndex(args[1].getInteger())));
        break;
    case 0x25: result->setInteger(menuPokemonStatusOpenWazaLearn(pokemon, args[1].getInteger())); break;
    case 0x26: result->setInteger(menuPokemonStatusOpenWazaLearnList(pokemon, args[1].getInteger())); break;
    }
    return 0;
}

s32 AppScript::commonCall(GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    s32 function = args[0].getInteger();
    s32 count = args[1].getInteger();
    floorGetCommonScript()->runParamsWait(function, &args[2], count, 0);
    return 1;
}

s32 AppScript::orFlagTest(GSscript::tigaVariant* args)
{
    int index = 1;
    u8 result = 0;
    const char* p;
    for (p = args[0].getString(stringBuffer); *p != 0; p++) {
        if (*p == '0') {
            if (GSflagTest(args[index].getInteger()) == 0) {
                result = 1;
            }
            index++;
        } else if (*p == '1') {
            if (GSflagTest(args[index].getInteger()) == 1) {
                result = 1;
            }
            index++;
        } else {
            return -1;
        }
    }
    return result;
}

s32 AppScript::andFlagTest(GSscript::tigaVariant* args)
{
    int index = 1;
    u8 result = 1;
    const char* p;
    for (p = args[0].getString(stringBuffer); *p != 0; p++) {
        if (*p == '0') {
            if (GSflagTest(args[index].getInteger()) == 1) {
                result = 0;
            }
            index++;
        } else if (*p == '1') {
            if (GSflagTest(args[index].getInteger()) == 0) {
                result = 0;
            }
            index++;
        } else {
            return -1;
        }
    }
    return result;
}

s32 AppScript::fncPrintf(GSscript::tigaVariant* args)
{
    char buf[0x100] = { 0 };
    int len = 0;
    int argn = 1;
    const char* fmt;

    for (fmt = args[0].getString(stringBuffer); *fmt != 0; fmt++) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 'd' || *fmt == 'D') {
                if (args[argn].type == 1) {
                    len = sprintf(buf, "%s%d", buf, args[argn].getInteger());
                } else {
                    GSlogWrite("script error line[%d] : printf argument %d error \n", m_cpCurrentObject->thread->line, argn);
                    return 0;
                }
            } else if (*fmt == 'f' || *fmt == 'F') {
                if (args[argn].type == 2) {
                    len = sprintf(buf, "%s%f", buf, args[argn].getSingle());
                } else {
                    GSlogWrite("script error line[%d] : printf argument %d error \n", m_cpCurrentObject->thread->line, argn);
                    return 0;
                }
            } else if (*fmt == 's' || *fmt == 'S') {
                if (args[argn].type == 3) {
                    len = sprintf(buf, "%s%s", buf, args[argn].getString(stringBuffer));
                } else {
                    GSlogWrite("script error line[%d] : printf argument %d error \n", m_cpCurrentObject->thread->line, argn);
                    return 0;
                }
            } else if (*fmt == 'c' || *fmt == 'C') {
                if (args[argn].type == 3) {
                    len = sprintf(buf, "%s%c", buf, args[argn].getString(stringBuffer));
                } else {
                    GSlogWrite("script error line[%d] : printf argument %d error \n", m_cpCurrentObject->thread->line, argn);
                    return 0;
                }
            } else if (*fmt == 'v' || *fmt == 'V') {
                if (args[argn].type == 4) {
                    GSvec* v = args[argn].getVector();
                    len = sprintf(buf, "%s x:%f y:%f z:%f", buf, v->x, v->y, v->z);
                } else {
                    GSlogWrite("script error line[%d] : printf argument %d error \n", m_cpCurrentObject->thread->line, argn);
                    return 0;
                }
            } else if (*fmt == 'p' || *fmt == 'P') {
                if (args[argn].type == 0x23) {
                    ScriptPeople* people = (ScriptPeople*)args[argn].getObject(0x23, "people not access");
                    len = sprintf(buf, "%s grpID:%d resID:%d", buf, people->group, people->object);
                } else {
                    GSlogWrite("script error line[%d] : printf argument %d error \n", m_cpCurrentObject->thread->line, argn);
                    return 0;
                }
            }
            argn++;
        } else if (*fmt == '\\') {
            fmt++;
            if (*fmt == 'n') {
                sprintf(buf, "%s\n", buf);
                GSlogWrite(buf);
                for (int i = 0; i < 0x100; i++) {
                    buf[i] = 0;
                }
                len = 0;
            } else if (*fmt == 't') {
                len = sprintf(buf, "%s\t", buf);
            }
        } else {
            buf[len] = *fmt;
            len++;
        }
    }
    if (buf[len] != '\n' && len != 0) {
        buf[len] = '\n';
        GSlogWrite(buf);
    }
    return 0;
}

s32 AppScript::setExtendVariable(GSscript::tigaVariant*, int, int)
{
    return 0;
}

s32 AppScript::getExtendVariable(GSscript::tigaVariant* v, int id, int)
{
    if (id >= 0x80 && id <= 0x120) {
        v->setObject(0x23, &people[id - 0x80]);
        return 1;
    }
    if (id >= 0x200 && id <= 0x2FF) {
        s32 n = id - 0x200;
        if (n >= 0 && n < objectCount) {
            v->setObject(7, objects[n]);
        } else {
            v->setInteger(0);
        }
        return 1;
    }
    return 0;
}

s32 AppScript::execExtendGlobalFunction(int function, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    GSresID id;
    GSresID* res;
    switch (function) {
    case 0x81: {
        int id = args[0].getInteger();
        if (id != 0 && id <= *flag_data_number) GSflagOn(id);
        break;
    }
    case 0x82: {
        u32 id = args[0].getInteger();
        if (id != 0 && id <= *flag_data_number) GSflagOff(id);
        break;
    }
    case 0x83: {
        u32 id = args[0].getInteger();
        s32 value = args[1].getInteger();
        if (id != 0 && id <= *flag_data_number) GSflagSet(id, value);
        break;
    }
    case 0x84: {
        u32 id = args[0].getInteger();
        if (id != 0 && id <= *flag_data_number) result->setInteger(GSflagTest(id));
        break;
    }
    case 0x85: {
        u32 id = args[0].getInteger();
        if (id != 0 && id <= *flag_data_number) result->setInteger(GSflagGet(id));
        break;
    }
    case 0x88: fncPrintf(args); break;
    case 0x89: result->setInteger(scriptGetRandom(args[0].getInteger())); break;
    case 0x8A: darkPokemonBiosSetInfomation(args[0].getInteger(), args[1].getInteger()); break;
    case 0x8B: result->setInteger(andFlagTest(args)); break;
    case 0x8C: result->setInteger(orFlagTest(args)); break;
    case 0x8E: commonCall(args, result); break;
    case 0x8F: floorSetDispScriptInfo(args[0].getInteger() != 0); break;
    case 0x91: floorSetHumanColision(args[0].getInteger() != 0); break;
    case 0x92: result->setInteger(floorGetHumanColision()); break;
    case 0x93: peopleSetTresureSearchDistance(args[0].getInteger(), args[1].getSingle()); break;
    case 0x94: result->setObject(8, GSmsgGetGSchar(args[0].getInteger())); break;
    case 0x95: {
        id.group = floorGetCurrentGroupID();
        id.id = floorTresureGetResID(args[0].getInteger());
        s32 index = m_cpCurrentObject->objManager.getResourceIdx(&id);
        if (index == -1) {
            res = m_cpCurrentObject->objManager.newResource();
            if (res) {
                *res = id;
            }
        } else {
            res = m_cpCurrentObject->objManager.getResource(index);
        }
        result->setObject(0x23, res);
        result->dupIfNeeded();
        break;
    }
    case 0x96: result->setInteger(pokemonDB_GetName(args[0].getInteger())); break;
    case 0x97: {
        result->setInteger(((GSscript::tigaArrayFixed*)args[0].getObject(7, "pokemon not access"))->get(args[1].getInteger())->getInteger());
        break;
    }
    case 0x98: result->setInteger(wazaDB_GetHidenFlag(args[0].getInteger())); break;
    case 0x99: {
        result->setSingle(PSVECDistance(args[0].getVector(), args[1].getVector()));
        break;
    }
    case 0x9A:
        if (args[0].type == 0x23) {
            ScriptPeople* people = (ScriptPeople*)args[0].getObject(0x23, "people not access");
            GSresFreeResource(floorGetCurrentGroupID(), people->object);
        } else if (args[0].type == 1) {
            s32 res = args[0].getInteger();
            GSresFreeResource(floorGetCurrentGroupID(), res);
        }
        break;
    case 0x9B: scriptGlowStart(args[0].getSingle(), args[1].getInteger(), args[2].getInteger() != 0, args[3].getInteger() != 0, args[4].getInteger() != 0, args[5].getInteger()); break;
    case 0x9C: scriptGlowEnd(); break;
    case 0x9D: scriptSetLensFlare(args[0].getInteger(), args[1].getSingle() != 0.0f, args[2].getSingle(), args[3].getSingle(), args[4].getSingle()); break;
    case 0x9E: {
        id.group = floorGetCurrentGroupID();
        id.id = args[0].getInteger();
        s32 index = m_cpCurrentObject->objManager.getResourceIdx(&id);
        if (index == -1) {
            res = m_cpCurrentObject->objManager.newResource();
            if (res) {
                *res = id;
            }
        } else {
            res = m_cpCurrentObject->objManager.getResource(index);
        }
        result->setObject(0x23, res);
        result->dupIfNeeded();
        break;
    }
    case 0x9F: result->setSingle(GSgfxVideoGetVsyncRate()); break;
    case 0xA0: result->setInteger(pokecoloGetCountryCode()); break;
    case 0xA1: result->setInteger(pokecoloGetLanguage()); break;
    }
    return 0;
}

s32 AppScript::execExtendMethod(int classID, int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    s32 ret = 0;
    switch (classID) {
    case 0x23: ret = cmpPeople(command, args, result); break;
    case 0x21: ret = cmpCamera(command, args, result); break;
    case 0x25: ret = cmpPokemon(command, args, result); break;
    case 0x26: ret = cmpFloor(command, args, result); break;
    case 0x27: ret = cmpTask(command, args, result); break;
    case 0x28: ret = cmpMenu(command, args, result); break;
    case 0x29: ret = cmpFade(command, args, result); break;
    case 0x2A: ret = cmpFight(command, args, result); break;
    case 0x2B: ret = cmpHero(command, args, result); break;
    case 0x2C: ret = cmpLight(command, args, result); break;
    case 0x2D: ret = cmpModel(command, args, result); break;
    case 0x2E: ret = cmpCol(command, args, result); break;
    case 0x2F: ret = cmpSound(command, args, result); break;
    case 0x30: ret = cmpPad(command, args, result); break;
    case 0x31: ret = cmpMail(command, args, result); break;
    case 0x32: ret = cmpDirection(command, args, result); break;
    case 0x33: ret = cmpTv(command, args, result); break;
    case 0x34: ret = cmpSodateya(command, args, result); break;
    case 0x3A: ret = cmpWaza(command, args, result); break;
    case 0x3B: ret = cmpDarkPokemon(command, args, result); break;
    case 0x3C: ret = cmpEsaba(command, args, result); break;
    }
    return ret;
}

void AppScript::unload()
{
    for (GSscript::tigaWaza* w = waza; w != &waza[7]; w++) {
        if (w->waza != 0 || w->sequence != 0) {
            if (w->waza) {
                WazaSequence_Stop(w->waza);
                WazaSequence_Free(w->waza);
            }
            if (w->sequence) {
                Sequence_Free(w->sequence);
            }
            wazaCount--;
            w->sequence = 0;
            w->waza = 0;
        }
    }
}

void AppScript::freeWazaPtr(GSscript::tigaWaza* p)
{
    if (p == 0) return;
    for (GSscript::tigaWaza* w = waza; w != &waza[7]; w++) {
        if (w == p) {
            p->sequence = 0;
            p->waza = 0;
        }
    }
}

GSscript::tigaWaza* AppScript::allocWazaPtr()
{
    for (GSscript::tigaWaza* w = waza; w != &waza[7]; w++) {
        if (w->sequence == 0) {
            w->sequence = 0;
            w->waza = 0;
            return w;
        }
    }
    return 0;
}

void AppScript::unmapping() {}

void AppScript::mapping()
{
    memset(waza, 0, sizeof(waza));
}

AppScript::~AppScript() {}

AppScript::AppScript()
{
    memset(waza, 0, sizeof(waza));
}

AppScript* scriptCreateAppScript()
{
    return new AppScript;
}
