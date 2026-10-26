#include <dolphin/types.h>

#pragma pool_strings off
#pragma peephole off

struct Pokemon;
struct Hero;
struct GSvec;
struct ScriptPeople { s32 group; s32 object; };
namespace GSscript {
void tigaErrMessage(const char*);
struct tigaVariant;
struct tigaArrayFixed { tigaVariant* get(int); };
struct tigaVariant {
    s16 type;
    u16 flags;
    union { s32 integer; f32 real; void* pointer; } value;
    s32 getCnvInteger();
    GSvec* getCnvVector();
    inline s32 getInteger() {
        if (type == 1) return value.integer;
        if (type == 2) return (s32)value.real;
        return getCnvInteger();
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
    inline void setInteger(s32 n) { type = 1; value.integer = n; }
    inline void setPokemon(Pokemon* p) { type = 0x25; value.pointer = p; }
};
}
struct HeroScriptContext {
    u8 reserved[0x10];
    GSscript::tigaVariant result;
    u8 reserved18[0x20];
    char text[0x100];
};
class AppScript {
    u8 reserved[0x914];
    HeroScriptContext* context;
public:
    s32 cmpHero(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
};

extern "C" {
Hero* getHeroPtr__4HeroFv();
Pokemon* getPokemon__4HeroFl(Hero*, s32);
u8 deletePokemon__4HeroFl(Hero*, s32);
void setHeroStyle__4HeroFUcb(Hero*, u8, u8);
u8 getLegendPokemonSize__4HeroCFv(Hero*);
void* getPointer__11CReliveHallFv();
u8 isReliveReadyPokemonExist__11CReliveHallFv(void*);
void* getPointer__5PCBOXFv();
u8 isPokemonFull__5PCBOXFv(void*);
char* strncpy(char*, const char*, u32);
s32 heroMoveInit(GSvec*, GSvec*);
s32 heroMoveMain();
void heroMoveInitEvent();
void heroMoveTermEvent();
void heroMoveAddAutoEvent(s32, s32, s32, s32, s32);
void scriptPartyChange(u8);
u8 heroMoveSetNeckMode(s32, s32);
u8 scriptCheckHizukiFollow();
s32 scriptHeroCtrlElevator(u16, s32, u16, s32);
s32 scriptHizukiAway(s32, s32);
s32 scriptGetItem(s32, s32);
s32 scriptAddItem(s32, s32);
s32 scriptHaveItem(s32);
s32 scriptAddPokedoru(s32);
s32 scriptGetPokedoru();
s32 scriptGetPremium();
void scriptSetPremium(s32);
s32 scriptAddPremium(s32);
s32 scriptGetPokemonNum();
s32 scriptGetDarkPokemonNum();
const char* scriptGetPokemonNickName(s32);
s16 scriptCatchPokemon(u8);
s32 scriptGetDarkPointZeroPokemonNum();
void recoveryPokemon();
s32 scriptBattleMountainEnd(u8);
s32 heroGetLivingPokemonCount();
s32 heroGetEmptySlot();
s32 heroGetPokeomCount();
u8 heroIsMinePokemon(Hero*, Pokemon*);
void peopleChangeFollower(s32);
s32 heroGetFollower();
void heroSetFollower(s32, s32, s32);
void heroSetFollowerWithID(u8, u8);
s32 darkPokemonGetSnatchSuccessNum();
void heroMoveSlowStop();
void scriptStoreTemochiPokemon();
u8 scriptCheckTemochiPokemon();
void recoveryEventCommon(s32);
void recoveryEventPC(s32, s32, s32, s32*, s32*);
s32 darkPokemonGetReliveNum();
s32 scriptGetEarthRibbon();
s32 scriptGetPoint();
void scriptSetPoint(s32);
void scriptAddPoint(s32);
u16 darkpokemonBiosGetScenarioNum();
void heroMoveSetSmoothFloorLink(u8);
s32 floorEventGetTresureEx(u8, s32, s32, u8);
u8 pcBoxAllSearchPokemon(s32);
}

s32 AppScript::cmpHero(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    Hero* hero = getHeroPtr__4HeroFv();
    switch (command) {
    case 0x10: {
        GSvec* b;
        void* a = (void*)args[1].getVector();
        b = args[2].getVector();
        result->setInteger(heroMoveInit((GSvec*)a, b));
        break;
    }
    case 0x11: result->setInteger(heroMoveMain()); break;
    case 0x12: heroMoveInitEvent(); break;
    case 0x13: heroMoveTermEvent(); break;
    case 0x14: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        s32 c = args[3].getInteger();
        s32 d = args[4].getInteger();
        s32 e = args[5].getInteger();
        heroMoveAddAutoEvent(a, b, c, d, e);
        break;
    }
    case 0x15: scriptPartyChange(args[1].getInteger() != 0); break;
    case 0x16: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        result->setInteger(heroMoveSetNeckMode(a, b));
        break;
    }
    case 0x17: result->setInteger(scriptCheckHizukiFollow()); break;
    case 0x18: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        s32 c = args[3].getInteger();
        s32 d = args[4].getInteger();
        u16 firstArgument = (u16)a;
        result->setInteger(scriptHeroCtrlElevator((s32)firstArgument, b, c, d));
        break;
    }
    case 0x19: {
        ScriptPeople* p = (ScriptPeople*)args[1].getObject(0x23, "people not access");
        result->setInteger(scriptHizukiAway(p->group, p->object));
        break;
    }
    case 0x1A: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        result->setInteger(scriptGetItem(a, b));
        break;
    }
    case 0x1B: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        result->setInteger(scriptAddItem(a, b));
        break;
    }
    case 0x1C: result->setInteger(scriptHaveItem(args[1].getInteger())); break;
    case 0x1D: result->setInteger(scriptAddPokedoru(args[1].getInteger())); break;
    case 0x1E: result->setInteger(scriptGetPokedoru()); break;
    case 0x1F: result->setInteger(scriptGetPremium()); break;
    case 0x20: scriptSetPremium(args[1].getInteger()); break;
    case 0x21: result->setInteger(scriptAddPremium(args[1].getInteger())); break;
    case 0x22: result->setInteger(scriptGetPokemonNum()); break;
    case 0x23: result->setInteger(scriptGetDarkPokemonNum()); break;
    case 0x24: {
        const char* name = scriptGetPokemonNickName(args[1].getInteger());
        strncpy(context->text, name, 0xFF);
        context->result.value.pointer = context->text;
        context->result.type = 3;
        break;
    }
    case 0x25: result->setInteger(scriptCatchPokemon(args[1].getInteger())); break;
    case 0x26: result->setInteger(scriptGetDarkPointZeroPokemonNum()); break;
    case 0x27: recoveryPokemon(); break;
    case 0x28: result->setInteger(scriptBattleMountainEnd(args[1].getInteger() != 0) != 0); break;
    case 0x29: result->setInteger(heroGetLivingPokemonCount()); break;
    case 0x2A: result->setInteger(heroGetEmptySlot()); break;
    case 0x2B: result->setInteger(heroGetPokeomCount()); break;
    case 0x2C: result->setPokemon(getPokemon__4HeroFl(hero, (u16)args[1].getInteger())); break;
    case 0x2D: result->setInteger(heroIsMinePokemon(hero, (Pokemon*)args[1].getObject(0x25, "pokemon not access"))); break;
    case 0x2E: peopleChangeFollower(args[1].getInteger()); break;
    case 0x2F: result->setInteger(heroGetFollower()); break;
    case 0x30: {
        ScriptPeople* p = (ScriptPeople*)args[1].getObject(0x23, "people not access");
        s32 n = args[2].getInteger();
        heroSetFollower(p->group, p->object, n);
        break;
    }
    case 0x36: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        heroSetFollowerWithID(a, b);
    }
    case 0x31: result->setInteger(darkPokemonGetSnatchSuccessNum()); break;
    case 0x32: heroMoveSlowStop(); break;
    case 0x33: result->setInteger(isReliveReadyPokemonExist__11CReliveHallFv(getPointer__11CReliveHallFv())); break;
    case 0x34: result->setInteger(isPokemonFull__5PCBOXFv(getPointer__5PCBOXFv())); break;
    case 0x35: result->setInteger(getLegendPokemonSize__4HeroCFv(hero)); break;
    case 0x37: scriptStoreTemochiPokemon(); break;
    case 0x38: result->setInteger(scriptCheckTemochiPokemon()); break;
    case 0x39: recoveryEventCommon(args[1].getInteger()); break;
    case 0x3A: {
        s32 party[6];
        s32 boxes[7];
        u16 i;
        for (i = 0; i < 6; i++) {
            GSscript::tigaArrayFixed* a = (GSscript::tigaArrayFixed*)args[2].getObject(7, "pokemon not access");
            s32 value = a->get(i)->getInteger();
            party[i] = value;
        }
        for (i = 0; i < 7; i++) {
            GSscript::tigaArrayFixed* a = (GSscript::tigaArrayFixed*)args[3].getObject(7, "pokemon not access");
            s32 value = a->get(i)->getInteger();
            boxes[i] = value;
        }
        recoveryEventPC(0, 0, args[1].getInteger(), party, boxes);
        break;
    }
    case 0x3B: result->setInteger(darkPokemonGetReliveNum()); break;
    case 0x3C: result->setInteger(scriptGetEarthRibbon()); break;
    case 0x3D: result->setInteger(scriptGetPoint()); break;
    case 0x3E: scriptSetPoint(args[1].getInteger()); break;
    case 0x3F: scriptAddPoint(args[1].getInteger()); break;
    case 0x40: result->setInteger(darkpokemonBiosGetScenarioNum()); break;
    case 0x41: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        setHeroStyle__4HeroFUcb(hero, a, b != 0);
        break;
    }
    case 0x42: heroMoveSetSmoothFloorLink(args[1].getInteger() != 0); break;
    case 0x43: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        s32 c = args[3].getInteger();
        s32 d = args[4].getInteger();
        s32 flag = d != 0;
        result->setInteger(floorEventGetTresureEx(a, b, c, flag));
        break;
    }
    case 0x44: result->setInteger(pcBoxAllSearchPokemon(args[1].getInteger())); break;
    case 0x45: result->setInteger(deletePokemon__4HeroFl(hero, args[1].getInteger())); break;
    }
    return 0;
}

