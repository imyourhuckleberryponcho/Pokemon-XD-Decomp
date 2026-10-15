#include <dolphin/types.h>

// WIP (GXXE01): 28 instruction differences remain, all register choices in
// message substitution and money/coupon/item menu calls. Keep NonMatching.
// Scratch comparison: build/scratch/match_menu.py. Verify the full DOL before
// marking this unit matching; normalized instruction diffs hide branch targets.

// The retail unit uses separate strings and disables peephole optimization.
#pragma pool_strings off
#pragma peephole off

// Script values are eight-byte tagged unions in the retail interpreter.
struct Pokemon;
struct Hero;
struct GSvec { f32 x, y, z; };
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
    char* getCnvString(char*);
    inline char* getString(char* buffer) {
        if (type == 8) return (char*)value.pointer;
        return getCnvString(buffer);
    }
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
    u8 reserved[0x10];
    GSscript::tigaVariant result;
    u8 reserved18[0x20];
    char text[0x100];
    GSvec vector;
};
class AppScript {
    u8 reserved[0x914];
    HeroScriptContext* context;
    u8 reserved918[0x3C];
    char* conversionBuffer;
    u8 reserved958[0x28];
    void* thread;
public:
    s32 cmpMenu(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
};

extern "C" {
void GSthreadSwitch();
void setSaveFlag__Q28GSscript10TigaThreadFb(void*, bool);
void* GSmsgGetGSchar(s32);
void msgctrlSetValue(s32, u32);
void peopleBlock();
void peopleUnblock();
void scriptOpenItemMenu();
s32 scriptPokemonTeachWazaIndex(s32);
s32 winMsgOpenField(s32, u8, u8);
s32 winMsgOpenFieldWithSE(s32, u8, u8, u8);
s32 winMsgOpenFight(s32, u8, u8);
void winMsgCloseField(u8);
void winMsgCloseFight(u8);
s8 menuSubOpenYesNoField();
s8 menuSubOpenYesNo(u8, s16, s16, s32);
s32 menuSubOpenColosseumEnter(s32);
s32 menuSubOpenSelect2(u8, s32*, s32, s32, s32, s32, s32, u8);
u8 menuSubOpenNumberInputDigit(s32, s32*);
s32 menuOpen(s32, u8);
void menuClose(s32);
s32 menuGetCursor(s32);
s32 menuSetCursor(s32, s32);
s32 menuPokemonOpen(s32, u16, s32);
s32 menuPokemonStatus();
s32 menuPokemonStatusOpenWazaList(u8);
s32 menuNameEntryOpen(s32, s32);
void menuNameEntry();
void menuShopOpen(s32);
void menuPda();
void menuPokemonChange();
s32 menuScriptTutorial();
s32 menuScriptEevee();
void menuScriptOpenWorldMap(u16);
void menuIntUnderTakerMenuOpen();
void menuIntUnderTakerMenuClose();
void menuScriptUsohachi();
void menuScriptUsohachi2();
s32 menuScriptWazaMeijin(s32);
s32 menuScriptWazaBasan(u8*);
void menuScriptSetWazaOboetaFlag(u16);
void menuScriptMoneyOpen(s16, s16);
void menuScriptMoneyClose();
u8 menuScriptWazaBasanCheck();
void menuScriptCouponOpen(s8, s8);
void menuScriptCouponClose();
void menuOrreColosseum(u16);
u16 menuOrreColosseumGetResult();
void menuScriptPdaAddFunc(s32);
void menuPocket2AddItemScript(s32, s32);
s32 mewWazaSequence();
u16 mewWazaGet(s32);
}

s32 AppScript::cmpMenu(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    s32 choices[128];
    s32 number;
    u8 moveLearned;
    switch (command) {
    case 0x10: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        s32 c = args[3].getInteger();
        result->setInteger(winMsgOpenField(a, b != 0, c != 0));
        break;
    }
    case 0x11: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        s32 c = args[3].getInteger();
        s32 d = args[4].getInteger();
        result->setInteger(winMsgOpenFieldWithSE(a, b != 0, c != 0, d));
        break;
    }
    case 0x12: winMsgCloseField(args[1].getInteger() != 0); break;
    case 0x13: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        s32 c = args[3].getInteger();
        result->setInteger(winMsgOpenFight(a, b != 0, c != 0));
        break;
    }
    case 0x14: winMsgCloseFight(args[1].getInteger() != 0); break;
    case 0x15: result->setInteger(menuSubOpenYesNoField()); break;
    case 0x16: {
        s32 arg0 = args[1].getInteger();
        s32 arg1 = args[2].getInteger();
        s32 arg2 = args[3].getInteger();
        result->setInteger(menuSubOpenYesNo(arg0, arg1, arg2, args[4].getInteger()));
        break;
    }
    case 0x17: result->setInteger(menuSubOpenColosseumEnter(args[1].getInteger())); break;
    case 0x18: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        result->setInteger(menuOpen(a, b != 0));
        break;
    }
    case 0x19: menuClose(args[1].getInteger()); break;
    case 0x1A: result->setInteger(menuGetCursor(args[1].getInteger())); break;
    case 0x1B: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        result->setInteger(menuSetCursor(a, b));
        break;
    }
    case 0x1C:
        if (args[1].getInteger() == 0x4D) {
            msgctrlSetValue(0x4D, (u32)GSmsgGetGSchar(args[2].getInteger()));
        } else {
            if (args[2].type == 0x25) {
                s32 a = args[1].getInteger();
                msgctrlSetValue(a, (u32)args[2].getObject(0x25, "pokemon not access"));
            } else if (args[2].type == 1) {
                s32 a = args[1].getInteger();
                msgctrlSetValue(a, args[2].getInteger());
            } else if (args[2].type == 8) {
                s32 a = args[1].getInteger();
                msgctrlSetValue(a, (u32)args[2].getString(conversionBuffer));
            } else if (args[2].type == 2) {
                s32 a = args[1].getInteger();
                msgctrlSetValue(a, (u32)args[2].getSingle());
            }
        }
        break;
    case 0x1D: {
        if (args[2].getInteger() >= 128) {
            result->setInteger(0);
            return 1;
        }
        for (s32 i = 0; args[2].getInteger() > i; i++) {
            GSscript::tigaArrayFixed* array = (GSscript::tigaArrayFixed*)args[1].getObject(7, "pokemon not access");
            choices[i] = array->get(i)->getInteger();
        }
        s32 arg0 = args[2].getInteger();
        s32 arg1 = args[3].getInteger();
        s32 arg2 = args[4].getInteger();
        s32 arg3 = args[5].getInteger();
        result->setInteger(menuSubOpenSelect2(0, choices, arg0, arg1, arg2, arg3, args[2].getInteger(), 1));
        break;
    }
    case 0x20: result->setInteger(menuPokemonOpen(6, 0, 0)); break;
    case 0x21: result->setInteger(menuPokemonOpen(6, 0, 0)); break;
    case 0x22: result->setInteger(menuPokemonStatus()); break;
    case 0x23: result->setInteger(menuPokemonStatusOpenWazaList(args[1].getInteger())); break;
    case 0x24: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        result->setInteger(menuNameEntryOpen(a, b));
        break;
    }
    case 0x25: menuNameEntry(); break;
    case 0x27: peopleBlock(); menuShopOpen(args[1].getInteger()); peopleUnblock(); break;
    case 0x29: menuPda(); break;
    case 0x2A: setSaveFlag__Q28GSscript10TigaThreadFb(thread, false); menuPokemonChange(); break;
    case 0x32: scriptOpenItemMenu(); break;
    case 0x38:
        if (menuSubOpenNumberInputDigit(args[1].getInteger(), &number) == 1) result->setInteger(number);
        else result->setInteger(-1);
        break;
    case 0x39: result->setInteger(menuScriptTutorial()); break;
    case 0x3A: result->setInteger(menuScriptEevee()); break;
    case 0x3B: {
        if (args[3].getInteger() >= 128) {
            result->setInteger(0);
            return 1;
        }
        for (s32 i = 0; args[3].getInteger() > i; i++) {
            GSscript::tigaArrayFixed* array = (GSscript::tigaArrayFixed*)args[2].getObject(7, "pokemon not access");
            choices[i] = array->get(i)->getInteger();
        }
        s32 a = args[1].getInteger();
        s32 b = args[3].getInteger();
        s32 c = args[4].getInteger();
        s32 d = args[5].getInteger();
        s32 e = args[6].getInteger();
        s32 f = args[7].getInteger();
        s32 g = args[8].getInteger();
        s32 flag = g != 0;
        result->setInteger(menuSubOpenSelect2(a, choices, b, c, d, e, f, flag));
        break;
    }
    case 0x3C: GSthreadSwitch(); menuScriptOpenWorldMap(args[1].getInteger()); break;
    case 0x3D: menuIntUnderTakerMenuOpen(); break;
    case 0x3E: menuIntUnderTakerMenuClose(); break;
    case 0x3F: menuScriptUsohachi(); break;
    case 0x40: result->setInteger(menuScriptWazaMeijin(args[1].getInteger())); break;
    case 0x41: GSthreadSwitch(); result->setInteger(menuScriptWazaBasan(&moveLearned)); break;
    case 0x42: GSthreadSwitch(); menuScriptSetWazaOboetaFlag(args[1].getInteger()); break;
    case 0x43: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        menuScriptMoneyOpen(a, b);
        break;
    }
    case 0x44: menuScriptMoneyClose(); break;
    case 0x45: result->setInteger(menuScriptWazaBasanCheck()); break;
    case 0x46: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        s8 first = (s8)a;
        menuScriptCouponOpen((s32)first, b);
        break;
    }
    case 0x47: menuScriptCouponClose(); break;
    case 0x48: menuOrreColosseum(args[1].getInteger()); break;
    case 0x49: menuScriptUsohachi2(); break;
    case 0x4A: result->setInteger(menuOrreColosseumGetResult()); break;
    case 0x4B: menuScriptPdaAddFunc(args[1].getInteger()); break;
    case 0x4C: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        menuPocket2AddItemScript(a, b);
        break;
    }
    case 0x4D: result->setInteger(mewWazaSequence()); break;
    case 0x4E: result->setInteger(mewWazaGet(args[1].getInteger())); break;
    case 0x4F: result->setInteger(menuPokemonOpen(8, scriptPokemonTeachWazaIndex(args[1].getInteger()), 0)); break;
    }
    return 0;
}
