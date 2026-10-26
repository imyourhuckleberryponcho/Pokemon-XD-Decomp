#include <dolphin/types.h>

#pragma peephole off

struct GSresID;

namespace GSscript {

class tigaVariant {
public:
    void setInteger(long value);
    void setPeople(GSresID* res);

    s16 type;
    void* value;
};

class Tiga {
public:
    bool isMapping();
    int getNameToFuncId(const char* name);
    GSresID* searchResID(unsigned long group, unsigned long id);
    int runParamsWait(int func, tigaVariant* args, int numArgs, tigaVariant* result);
    u8 runParams(int func, tigaVariant* args, int numArgs, bool thread);
    s32 getResultValue(long handle);
    bool isRunningThread(long handle);
    void blockThread(long handle);
    void unblockThread(long handle);
};

}

using namespace GSscript;

Tiga* floorGetCurentScript();
Tiga* floorGetCommonScript();

#define SCRIPT_MODE_COMMON 2

extern "C" {

s32 floorGetCurentScriptMode(void);
int floorGetScriptMode(u32 func);
u8 floorExecScriptInteger(int func, s32 a, s32 b, s32 c, s32 d);
u8 floorExecScriptIntegerThread(int func, s32 a, s32 b, s32 c, s32 d);

static s32 _floorScriputResult;

u8 floorExecScriptIntegerByNameThread(const char* name, s32 a, s32 b, s32 c, s32 d) {
    Tiga* script = floorGetCurentScript();
    int func;
    if (script == NULL) {
        return 0;
    }
    if (!script->isMapping()) {
        return 0;
    }
    func = script->getNameToFuncId(name);
    if (func == 0) {
        return 0;
    }
    return floorExecScriptIntegerThread(func, a, b, c, d);
}

u8 floorExecScriptIntegerByName(const char* name, s32 a, s32 b, s32 c, s32 d) {
    Tiga* script = floorGetCurentScript();
    int func;
    if (script == NULL) {
        return 0;
    }
    if (!script->isMapping()) {
        return 0;
    }
    func = script->getNameToFuncId(name);
    if (func == 0) {
        return 0;
    }
    return floorExecScriptInteger(func, a, b, c, d);
}

u8 floorExecScriptRes(int func, u32 group, u32 id) {
    int mode;
    GSresID* res;
    tigaVariant arg;
    u8 handle;

    if (floorGetCurentScript() == NULL) {
        return 0;
    }
    mode = floorGetScriptMode(func);
    res = floorGetCurentScript()->searchResID(group, id);
    if (res == NULL) {
        return 0;
    }
    arg.setPeople(res);
    if (mode == SCRIPT_MODE_COMMON) {
        handle = floorGetCommonScript()->runParamsWait(func, &arg, 1, NULL);
        _floorScriputResult = floorGetCommonScript()->getResultValue(handle);
    } else {
        handle = floorGetCurentScript()->runParamsWait(func, &arg, 1, NULL);
        _floorScriputResult = floorGetCurentScript()->getResultValue(handle);
    }
    return handle;
}

u8 floorExecScriptResThread(int func, u32 group, u32 id) {
    int mode;
    GSresID* res;
    tigaVariant arg;

    if (floorGetCurentScript() == NULL) {
        return 0;
    }
    mode = floorGetScriptMode(func);
    res = floorGetCurentScript()->searchResID(group, id);
    if (res == NULL) {
        return 0;
    }
    arg.setPeople(res);
    if (mode == SCRIPT_MODE_COMMON) {
        return floorGetCommonScript()->runParams(func, &arg, 1, true);
    }
    return floorGetCurentScript()->runParams(func, &arg, 1, true);
}

s32 floorGetScriptResult(void) {
    return _floorScriputResult;
}

u8 floorExecScriptInteger(int func, s32 a, s32 b, s32 c, s32 d) {
    int mode;
    tigaVariant args[4];
    u8 handle;

    if (floorGetCurentScript() == NULL) {
        return 0;
    }
    mode = floorGetScriptMode(func);
    args[0].setInteger(a);
    args[1].setInteger(b);
    args[2].setInteger(c);
    args[3].setInteger(d);
    if (mode == SCRIPT_MODE_COMMON) {
        handle = floorGetCommonScript()->runParamsWait(func, args, 4, NULL);
        _floorScriputResult = floorGetCommonScript()->getResultValue(handle);
    } else {
        handle = floorGetCurentScript()->runParamsWait(func, args, 4, NULL);
        _floorScriputResult = floorGetCurentScript()->getResultValue(handle);
    }
    return handle;
}

u8 floorExecScriptIntegerThread(int func, s32 a, s32 b, s32 c, s32 d) {
    int mode = floorGetScriptMode(func);
    tigaVariant args[4];

    if (floorGetCurentScript() == NULL) {
        return 0;
    }
    args[0].setInteger(a);
    args[1].setInteger(b);
    args[2].setInteger(c);
    args[3].setInteger(d);
    if (mode == SCRIPT_MODE_COMMON) {
        return floorGetCommonScript()->runParams(func, args, 4, true);
    }
    return floorGetCurentScript()->runParams(func, args, 4, true);
}

bool floorIsRunningThread(long handle) {
    Tiga* script = floorGetCurentScript();
    if (script == NULL) {
        return false;
    }
    return script->isRunningThread(handle);
}

void floorBlockScriptThread(long handle) {
    if (floorGetCurentScript() != NULL) {
        floorGetCurentScript()->blockThread(handle);
    }
}

void floorUnblockScriptThread(long handle) {
    if (floorGetCurentScript() != NULL) {
        floorGetCurentScript()->unblockThread(handle);
    }
}

int floorGetScriptMode(u32 func) {
    if ((func & 0xFFFF0000) == 0x05960000) {
        return SCRIPT_MODE_COMMON;
    }
    if (floorGetCurentScriptMode() == 1) {
        return 3;
    }
    return 0;
}

}

inline void tigaVariant::setPeople(GSresID* res) {
    type = 0x23;
    value = res;
}
