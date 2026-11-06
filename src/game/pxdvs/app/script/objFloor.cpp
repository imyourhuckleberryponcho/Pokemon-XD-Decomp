#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/tigadata.h>
#ifndef __MWERKS__
struct CReliveStage;
struct CReliveHall { public: static CReliveHall* getPointer(); CReliveStage* getStage(s32); bool isReliveReadyDarkLugiaExist(); s32 getReliveReadyVisitorQuantity(); };
struct Hero { public: static Hero* getHeroPtr(); u16 itemQuantity(u16); u8 getHeroStyle() const; void setBattleResumeFloorID(uint); void setBattleResumeFloorIndex(u8); u8 getFollowerID(); u32 getFollowerGrpID(); u32 getFollowerResID(); void setFollowerGrpID(u32); void setFollowerResID(u32); void setFollowerID(u8); };
u8 menuReliveHallTutorialGetIsCancelExit();
#define getHeroPtr__4HeroFv(...) ((Hero*)Hero::getHeroPtr(__VA_ARGS__))
#define setBattleResumeFloorID__4HeroFUi(o, ...) (((Hero*)(o))->setBattleResumeFloorID(__VA_ARGS__))
#define setBattleResumeFloorIndex__4HeroFUc(o, ...) (((Hero*)(o))->setBattleResumeFloorIndex(__VA_ARGS__))
#define getPointer__11CReliveHallFv(...) ((void*)CReliveHall::getPointer(__VA_ARGS__))
#define isReliveReadyDarkLugiaExist__11CReliveHallFv(o, ...) ((u8)((CReliveHall*)(o))->isReliveReadyDarkLugiaExist(__VA_ARGS__))
#define getReliveReadyVisitorQuantity__11CReliveHallFv(o, ...) ((s32)((CReliveHall*)(o))->getReliveReadyVisitorQuantity(__VA_ARGS__))
#define menuReliveHallTutorialGetIsCancelExit__Fv(...) ((u8)menuReliveHallTutorialGetIsCancelExit(__VA_ARGS__))
#endif

#pragma pool_strings off
#pragma peephole off

struct Pokemon;
struct Hero;
struct GSvec { f32 x, y, z; };
struct ScriptPeople { s32 group; s32 object; };
namespace GSscript {
void tigaErrMessage(const char*);
struct tigaVariant;
struct tigaArrayFixed { tigaVariant* get(int); };
struct tigaVariant {
    gc_bes16 type;
    gc_be16 flags;
    union { gc_bes32 integer; gc_bef32 real; gc_ptr32(void) pointer; } value;
    s32 getCnvInteger();
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
    inline void setPokemon(Pokemon* p) { type = 0x25; value.pointer = p; }
};
}
struct HeroScriptContext {
    GSSCRIPT_TIGACONTEXT_DATA(GSscript::tigaVariant, GSvec)
};
struct AppScript {
    GSSCRIPT_TIGA_DATA(GSscript::TigaChankView, GSscript::TigaObjManagerView, HeroScriptContext)
    virtual ~AppScript();
    GSscript::tigaWaza waza[7];
public:
    s32 cmpFloor(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
};

extern "C" {
#ifdef __MWERKS__
Hero* getHeroPtr__4HeroFv();
#endif
#ifdef __MWERKS__
void setBattleResumeFloorID__4HeroFUi(Hero*, u32);
#endif
#ifdef __MWERKS__
void setBattleResumeFloorIndex__4HeroFUc(Hero*, u8);
#endif
#ifdef __MWERKS__
void* getPointer__11CReliveHallFv();
#endif
#ifdef __MWERKS__
u8 isReliveReadyDarkLugiaExist__11CReliveHallFv(void*);
#endif
#ifdef __MWERKS__
s32 getReliveReadyVisitorQuantity__11CReliveHallFv(void*);
#endif
#ifdef __MWERKS__
u8 menuReliveHallTutorialGetIsCancelExit__Fv();
#endif
s32 GSfloorGetCurrent();
s32 floorGetCurrentGroupID();
s32 floorGetNextFloorID();
s32 floorGetNextPosIndex();
s32 floorGetPrevFloorID();
void GSfloorPush(s32);
void GSmodelSetShadowDistLimits(f32, f32);
void floorChangePos(s32, s16, f32, f32, f32);
void floorClearReturnPoint();
u8 floorDataBiosGetPosListData(s32, GSvec*, f32*);
s32 floorEventChangeTresure(s32, u16, u8);
s32 floorEventCtrlDoor(s32, s32, u8);
s32 floorEventCtrlElevator(s32, s32, u16, s32, s32);
void floorEventSetTresureDisp(s32, PCARG(u8, u32));
void floorLink(s32, s32);
void floorLinkWithSE(s32, s32, s32);
void floorMoviePlay(s32, PCARG(u8, s32), PCARG(u8, int), s32, u16, u16);
void floorOffscreenPlayWait();
void floorRegisterCamera(s32, s32);
void floorRegisterLight(s32, s32);
void floorReleaseOffscreen();
void floorSetFadeScript(s32, s32);
u8 floorSetOffscreenIndex(s32);
void floorWaitForChange();
void menuBattleDeBingo();
u8 menuBattleDeBingoGetEpoint();
u8 menuBattleDeBingoGetLine();
u8 menuBattleDeBingoGetMball();
u8 menuBattleDeBingoGetMode();
u8 menuBattleDeBingoGetNum();
u8 menuBattleDeBingoGetResult();
s32 menuBattleDiskGetResult();
s32 menuBattleDiskGetSelectID();
void menuBattleDiskOpen();
void menuBattleDiskOpenFight();
void menuMoveDemo(s32);
void menuTitle();
void menuWorldMapMXMain();
s32 scriptFloorCharSetDisp(s32, s32);
s32 scriptFloorCharSetPos(s32, f32, f32, f32);
}

s32 AppScript::cmpFloor(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    Hero* hero = getHeroPtr__4HeroFv();
    switch (command) {
    case 0x10: result->setInteger(GSfloorGetCurrent()); break;
    case 0x11: result->setInteger(floorGetCurrentGroupID()); break;
    case 0x12: result->setInteger(floorGetPrevFloorID()); break;
    case 0x13: result->setInteger(floorGetNextFloorID()); break;
    case 0x14: result->setInteger(floorGetNextPosIndex()); break;
    case 0x15:
        setBattleResumeFloorID__4HeroFUi(hero, args[1].getInteger());
        setBattleResumeFloorIndex__4HeroFUc(hero, args[3].getInteger());
        break;
    case 0x16: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        floorLink(a, b);
        floorWaitForChange();
        break;
    }
    case 0x17: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        s32 c = args[3].getInteger();
        floorLinkWithSE(a, b, c);
        floorWaitForChange();
        break;
    }
    case 0x18: {
        result->setInteger(floorEventCtrlDoor(args[1].getInteger(), args[2].getInteger(), args[3].getInteger()));
        break;
    }
    case 0x19: {
        result->setInteger(floorEventCtrlElevator(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), 0, 0));
        break;
    }
    case 0x29: {
        ScriptPeople* p = (ScriptPeople*)args[4].getObject(0x23, "people not access");
        result->setInteger(floorEventCtrlElevator(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), p->group, p->object));
        break;
    }
    case 0x1A: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        floorEventSetTresureDisp(a, b != 0);
        break;
    }
    case 0x1B: {
        result->setInteger(floorEventChangeTresure(args[1].getInteger(), args[2].getInteger(), args[3].getInteger()));
        break;
    }
    case 0x1C: {
        result->setInteger(scriptFloorCharSetDisp(args[1].getInteger(), args[2].getInteger()));
        break;
    }
    case 0x1D: {
        result->setInteger(scriptFloorCharSetPos(args[1].getInteger(), args[2].getSingle(), args[3].getSingle(), args[4].getSingle()));
        break;
    }
    case 0x1E: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        floorSetFadeScript(a, b);
        break;
    }
    case 0x1F:
        setBattleResumeFloorID__4HeroFUi(hero, args[1].getInteger());
        setBattleResumeFloorIndex__4HeroFUc(hero, args[3].getInteger());
        break;
    case 0x20:
        setBattleResumeFloorID__4HeroFUi(hero, args[1].getInteger());
        setBattleResumeFloorIndex__4HeroFUc(hero, args[3].getInteger());
        break;
    case 0x21: floorClearReturnPoint(); break;
    case 0x22:
        result->setInteger(floorSetOffscreenIndex(args[1].getInteger()));
        floorOffscreenPlayWait();
        break;
    case 0x23: {
        GSvec* p = args[1].getVector();
        s32 a = args[1].getInteger();
        result->setInteger(scriptFloorCharSetPos(a, p->x, p->y, p->z));
        break;
    }
    case 0x25: menuTitle(); break;
    case 0x24: menuWorldMapMXMain(); break;
    case 0x26: GSfloorPush(args[1].getInteger()); floorWaitForChange(); break;
    case 0x27: GSfloorPush(0x3A6); floorWaitForChange(); break;
    case 0x28: GSfloorPush(0x3A3); floorWaitForChange(); break;
    case 0x2A: {
        s32 a = args[1].getInteger();
        f32 x = args[2].getSingle();
        f32 y = args[3].getSingle();
        f32 z = args[4].getSingle();
        s32 b = args[5].getInteger();
        floorChangePos(a, b, x, y, z);
        break;
    }
    case 0x2B: GSfloorPush(0x3A7); floorWaitForChange(); break;
    case 0x2C: menuBattleDeBingo(); floorWaitForChange(); break;
    case 0x2D: result->setInteger(menuBattleDeBingoGetResult()); break;
    case 0x2E: result->setInteger(menuBattleDeBingoGetLine()); break;
    case 0x2F: {
        GSvec p;
        if (!floorDataBiosGetPosListData(args[1].getInteger(), &p, 0)) {
            result->setInteger(0);
            return 1;
        }
        context->vector = p;
        context->regs[0].value.pointer = &context->vector;
        context->regs[0].type = 4;
        break;
    }
    case 0x30: {
        f32 angle;
        if (!floorDataBiosGetPosListData(args[1].getInteger(), 0, &angle)) {
            result->setInteger(0);
            return 1;
        }
        result->setSingle(angle);
        break;
    }
    case 0x31: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        floorLink(a, b);
        s32 c = args[3].getInteger();
        s32 d = args[4].getInteger();
        floorSetFadeScript(c, d);
        floorWaitForChange();
        break;
    }
    case 0x32: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        s32 c = args[3].getInteger();
        s32 d = args[4].getInteger();
        s32 e = args[5].getInteger();
        s32 f = args[6].getInteger();
        floorMoviePlay(a, b != 0, c != 0, d, e, f);
        floorOffscreenPlayWait();
        break;
    }
    case 0x33: menuBattleDiskOpen(); floorWaitForChange(); break;
    case 0x34: result->setInteger(menuBattleDiskGetSelectID()); break;
    case 0x35: result->setInteger(menuBattleDiskGetResult()); break;
    case 0x36: result->setInteger(menuBattleDeBingoGetNum()); break;
    case 0x37: result->setInteger(menuBattleDeBingoGetEpoint()); break;
    case 0x38: result->setInteger(menuBattleDeBingoGetMball()); break;
    case 0x39: result->setInteger(isReliveReadyDarkLugiaExist__11CReliveHallFv(getPointer__11CReliveHallFv())); break;
    case 0x3A: {
        s32 a = args[1].getInteger();
        floorRegisterLight(floorGetCurrentGroupID(), a);
        break;
    }
    case 0x3B: {
        s32 a = args[1].getInteger();
        floorRegisterCamera(floorGetCurrentGroupID(), a);
        break;
    }
    case 0x3C: menuBattleDiskOpenFight(); floorWaitForChange(); break;
    case 0x3D: floorReleaseOffscreen(); break;
    case 0x3E: result->setInteger(menuReliveHallTutorialGetIsCancelExit__Fv()); break;
    case 0x3F: menuMoveDemo(args[1].getInteger()); break;
    case 0x40: result->setInteger(isReliveReadyDarkLugiaExist__11CReliveHallFv(getPointer__11CReliveHallFv())); break;
    case 0x41: result->setInteger(menuBattleDeBingoGetMode()); break;
    case 0x42: result->setInteger(getReliveReadyVisitorQuantity__11CReliveHallFv(getPointer__11CReliveHallFv())); break;
    case 0x43: {
        f32 a = args[1].getSingle();
        f32 b = args[2].getSingle();
        GSmodelSetShadowDistLimits(a, b);
        break;
    }
    }
    return 0;
}
