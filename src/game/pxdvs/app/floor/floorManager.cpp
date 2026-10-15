// STATUS: 122/123 exact with -inline off; .text order OK. makeSaveData: registers only (data/p coalescing).
// Blocker: .data order (target __vt__12FloorManager before mainThread's jump table). Findings 2026-10-15:
// MWCC emits vtables at EOF; only code still deferred at EOF (-inline deferred or #pragma defer_codegen on)
// is generated after them. But full deferral emits the FloorStackList/Tiga/... weak inlines right after
// their callers, while the target has them at the end. Reversed+deferred variant (data OK, weak order wrong):
// build/scratch/floorManager_defer_variant.cpp (122/123, uses #pragma defer_codegen on/off).
#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct GSfloor_dd_;
struct FloorModuleInterface;
struct GSthread;

enum FloorState {
    FLOOR_STATE_0,
    FLOOR_STATE_1,
    FLOOR_STATE_2,
    FLOOR_STATE_3,
    FLOOR_STATE_4,
    FLOOR_STATE_5,
    FLOOR_STATE_6,
    FLOOR_STATE_7,
    FLOOR_STATE_8
};

enum FloorStateMode {
    FLOOR_STATE_MODE_0,
    FLOOR_STATE_MODE_1,
    FLOOR_STATE_MODE_2,
    FLOOR_STATE_MODE_3
};

enum FloorEnterMode {
    FLOOR_ENTER_MODE_0,
    FLOOR_ENTER_MODE_1,
    FLOOR_ENTER_MODE_2,
    FLOOR_ENTER_MODE_3
};

enum FloorModuleType {
    FLOOR_MODULE_TYPE_0,
    FLOOR_MODULE_TYPE_1,
    FLOOR_MODULE_TYPE_2,
    FLOOR_MODULE_TYPE_ALL = 0xFF
};

enum floorTask {
    FLOOR_TASK_0,
    FLOOR_TASK_1,
    FLOOR_TASK_2,
    FLOOR_TASK_3,
    FLOOR_TASK_4,
    FLOOR_TASK_5,
    FLOOR_TASK_6
};

class GSBinWriteStream {
public:
    GSBinWriteStream(unsigned long size);
    ~GSBinWriteStream();
    u8* getTop() const;

    u8* m_top;
    u8* m_buffer;
    u32 m_size;
    u8* m_cursor;
    u8 m_owned;
};

namespace GSscript {

class Tiga {
public:
    bool isMapping();
    u32 getStateSize();
    void makeStateData(GSBinWriteStream* stream);
    u8 restoreStateData(void* data, unsigned long size);
    void executeThread(float dt);
    void mappingScript(char* name);
    void unmappingScript();

    u8 m_reserved[0x93c];
    void* m_mapped;
    u8 m_reserved2[0x44];
    virtual ~Tiga();
};

} // namespace GSscript

class AppScript : public GSscript::Tiga {
public:
    AppScript();
    ~AppScript();

    u8 m_waza[0x38];
};

class FloorModuleList {
public:
    FloorModuleList(unsigned long num);
    void unblockModule(unsigned long id);
    void blockModule(unsigned long id);
    u8 registerScriptModule(u8 kind, unsigned long a, unsigned long b, unsigned long c, unsigned long d);
    u8 registerModule(u8 kind, unsigned long id, FloorModuleInterface* module);
    void* makePushState(FloorStateMode mode);
    u32 getPushStateSize() const;
    void unregisterModuleGroup(unsigned long group);
    void blockModuleGroup(unsigned long group);
    void unblockModuleGroup(unsigned long group);
    void killModuleGroup(unsigned long group);
    void restorePopState(void* data, FloorStateMode mode, bool flag);
    void executeAll(unsigned int floorID, FloorState state, FloorModuleType type, FloorEnterMode mode, unsigned long group);
    void waitFloorScript(FloorState state);

    u8 m_reserved[0x10];
    u32 m_pushStateSize;
    virtual ~FloorModuleList();
};

class FloorStack {
public:
    void addResource(unsigned long group, unsigned long id);
    void freeAllResource();
    void freeResource(unsigned long group, unsigned long id);
    void reallocPushData();
    void setPushState(void* data, unsigned long size);
    void setFloorID(unsigned long floorID);
    void clearFlag();
    void setPushFlag();
    AppScript* getScriptModule();
    void setUpdateState(FloorState state);
    FloorState getUpdateState();
    void* getPushState();
    u32 getGroupID() const;
    u32 getFloorID() const;
    u8 isPopFlag();
    u8 isPushFlag();
    FloorModuleType getType();
    void setType(FloorModuleType type);

    u32 m_groupID;
    u32 m_floorID;
    void* m_pushData;
    u32 m_pushSize;
    u8 m_pushFlag;
    u8 m_popFlag;
    AppScript* m_script;
    FloorModuleType m_type;
    GSthread* m_thread;
    u8 m_resources[0x200];
    FloorState m_updateState;
};

class FloorStackList {
public:
    FloorStackList(unsigned long num);
    ~FloorStackList();
    void unblock();
    void block();
    void setGroupID(unsigned long groupID);
    void setPushState(void* data, unsigned long size);
    void setUpdateState(FloorState state);
    int getObjective();
    GSfloor_dd_* getGSfloor();
    int getStateMode();
    FloorStack* pop();
    FloorStack* push(unsigned int floorID);

    void freeResource(unsigned long group, unsigned long id);
    FloorStack* getCurrentStack();
    FloorStack* getTopOfStack();
    void addResource(unsigned long group, unsigned long id);
    FloorStack* getBottomOfStack();
    void freeState();
    void clearState();
    void* getPushState();
    void reallocPushData();
    void setPushFlag();
    void setFloorID(unsigned long id);
    void clearFlag();
    u32 getGroupID();
    void freeAllResource();
    AppScript* getScriptModule();
    bool isFloorPushd() const;
    u8 isPopFlag();
    u8 isPushFlag();
    u32 getFloorID();
    bool isPopReady() const;
    bool isPushReady() const;

    FloorStack* m_stacks;
    s32 m_depth;
    u32 m_num;
};

struct SaveHeader {
    u32 m_magic;
    u32 m_valid;
    u32 m_size;
    u32 m_unkC;
    u32 m_unk10;
    u32 m_total;
    u16 m_floorID;
};

struct StateDataPtr {
    SaveHeader* m_header;
    u8* m_data;
    u8* m_end;
};

class FloorManager {
public:
    FloorModuleList* m_modules;
    FloorStackList* m_stacks;
    floorTask m_task;
    floorTask m_nextTask;
    u32 m_nextFloor;
    u8 m_changing;
    FloorModuleType m_commonType;
    AppScript m_common;
    u32 m_maxSize;
    u16 m_maxID;
    virtual ~FloorManager();

    FloorManager();
    void init(unsigned long numStacks, unsigned long numModules);
    u8 open(unsigned int floorID);
    u8 close();
    u8 push(unsigned int floorID);
    u8 pop();
    u8 change(unsigned int floorID);
    u8 popAndChange(unsigned int floorID);
    u32 getCurrentFloorID();
    u32 getNextFloorID();
    u32 getCurrentFloorGroupID();
    u8 isPush();
    u8 isPop();
    bool isFloorPushed();
    AppScript* getCurrentScript();
    void mappingScript(char* name);
    void unmappingScript(char* name);
    void mappingCommonScript(char* name);
    int getCurrentEnterMode();
    bool getCurrentScriptMode();
    void waitForChange();
    void scriptUpdate();
    void load(GSfloor_dd_* floor, FloorEnterMode mode);
    void unload(GSfloor_dd_* floor, bool full, FloorEnterMode mode);
    u8 update(FloorStack* stack);
    void execPreFunction(FloorStack* stack, FloorEnterMode mode);
    void execPostFunction(FloorStack* stack, FloorEnterMode mode);
    void mainThread();
    u8 makeSaveData(u8** data, u32* size);
    SaveHeader* getStateData(StateDataPtr* ptr);
    FloorState getFloorState();

    void freeResource(unsigned long group, unsigned long id) {
        m_stacks->freeResource(group, id);
    }
    void addResource(unsigned long group, unsigned long id) {
        m_stacks->addResource(group, id);
    }
    void unblockModule(unsigned long id) {
        if (m_modules != 0) {
            m_modules->unblockModule(id);
        }
    }
    void blockModule(unsigned long id) {
        if (m_modules != 0) {
            m_modules->blockModule(id);
        }
    }
    u8 registerScriptModule(u8 kind, unsigned long a, unsigned long b, unsigned long c, unsigned long d) {
        if (m_modules == 0) {
            return 0;
        }
        return m_modules->registerScriptModule(kind, a, b, c, d);
    }
    u8 registerModule(u8 kind, unsigned long id, FloorModuleInterface* module) {
        if (m_modules == 0) {
            return 0;
        }
        return m_modules->registerModule(kind, id, module);
    }
    GSscript::Tiga* getCommonScript() {
        return &m_common;
    }
    floorTask getTaskMode() const {
        return m_task;
    }
    unsigned int makeFloorGroupID(unsigned int floorID) {
        return floorID + 0x5001;
    }
    void changeTaskMode(floorTask task) {
        m_task = task;
    }
    void setCommonScriptType(FloorModuleType type) {
        m_commonType = type;
    }
    void setNextTaskMode(floorTask task) {
        m_nextTask = task;
    }
};

extern "C" {
void* savedataGetStatus(s32, s32);
u8 floorExecScriptIntegerByName(const char* name, s32 a, s32 b, s32 c, s32 d);
s32 floorGetLocalHeapHandle(void);
s32 GSmemSetCurrentHeap(s32 heap);
void* GSthreadCreate(s32, s32, s32, s32, s32, void*);
void GSthreadSetName(void*, const char*);
void GSthreadSwitch(void);
void GSthreadTerminateGroup(u32 group);
s32 fn_8005C8C4(void);
char* tableResBiosGetResPtr(s32);
int memcmp(const void*, const void*, unsigned long);
void* memcpy(void* dst, const void* src, unsigned long n);
void* GSmemAllocClr(u32 size);
void GSmemFree(void* ptr);
void GSlogWrite(const char*, ...);
void floorDelayPostFunc(void);
void floorExecFadeOut(void);
void floorExecFadeIn(void);
u8 floorDataBiosGetFloorKind(GSfloor_dd_* data);
u32 floorDataBiosGetFloorID(GSfloor_dd_* data);
u32 floorDataBiosGetFileGroupID(GSfloor_dd_* data);
u32 floorDataBiosGetGroupID(GSfloor_dd_* data);
void* floorDataBiosGetPtr(u32 key);
void floorSetFadeScript(u32 script, u32 arg);
void underTakerMenuResore(void);
void flooSetFrameRate(void);
void floorSetContinueMode(u8 mode);
u8 floorIsContinueMode(void);
u8 floorCheckFightKind(u32 floorID);
void floorCheckFade(void);
void GSfsysFree(u32);
void GSresFreeGroup(u32);
void psRemoveParticle(void);
void psRemoveGenerator(void);
void psRemoveAppSRT(void);
void GSlightDeleteCurrentAll(void);
void GSmodelFreeAllShadowTextures(void);
s32 gamedatasaveGetStatus(s32, s32);
void fn_8005C068(u8);
void floorLayerConfig(u32 floorID, u8 kind);
void GSfsysReadWait(u32);
void floorInitWazaSequence(u32 floorID);
f32 timeGetLastFrameSec(void);
void* __nw__FUl(unsigned long);

s32 floorGetCurrent(void);
s32 floorGetCurrentFloorGroupID(void);
bool floorIsFloorPushed(void);
u8 floorIsPop(void);
u8 floorIsPush(void);
u8 floorChange(u32);
u8 floorPop(void);
u8 floorPush(u32);
u8 floorOpen(u32);
}

GSscript::Tiga* floorGetCurentScript();
GSscript::Tiga* floorGetCommonScript();

static FloorManager* _floorManager;

extern "C" {

void GSfloorSetData(void) {}

s32 GSfloorGetCurrent(void) {
    return floorGetCurrent();
}

s32 GSfloorGetCurrentFloorGroupID(void) {
    return floorGetCurrentFloorGroupID();
}

bool GSfloorIsFloorPushed(void) {
    return floorIsFloorPushed();
}

u8 GSfloorIsPop(void) {
    return floorIsPop();
}

u8 GSfloorIsPush(void) {
    return floorIsPush();
}

u8 GSfloorChange(u32 id) {
    return floorChange(id);
}

u8 GSfloorPop(void) {
    return floorPop();
}

u8 GSfloorPush(u32 id) {
    return floorPush(id);
}

u8 GSfloorOpen(u32 id) {
    return floorOpen(id);
}

void GSfloorStart(void) {}

int floorCheckAnywaySaveData(void) {
    SaveHeader* header = (SaveHeader*)savedataGetStatus(0, 0x16);
    return header->m_valid != 0;
}

void floorMemoryCardSaveCallback(void) {
    floorExecScriptIntegerByName("anywaysave_callback", GSfloorGetCurrentFloorGroupID(), 0, 0, 0);
}

u8 floorMakeSaveData(u8** data, u32* size) {
    _floorManager->makeSaveData(data, size);
    return 1;
}

void floorFreeResource(u32 group, u32 id) {
    _floorManager->freeResource(group, id);
}

void floorAddResource(u32 group, u32 id) {
    _floorManager->addResource(group, id);
}

void floorWaitForChange(void) {
    _floorManager->waitForChange();
}

void* floorCreateThread(s32 a, u32 stackSize, s32 c, void* func);

void* floorCreateThreadLocal(s32 a, u32 stackSize, s32 c, void* func) {
    s32 prev = GSmemSetCurrentHeap(floorGetLocalHeapHandle());
    void* thread = floorCreateThread(a, stackSize, c, func);
    GSmemSetCurrentHeap(prev);
    return thread;
}

void* floorCreateThread(s32 a, u32 stackSize, s32 c, void* func) {
    if (func == 0) {
        return 0;
    }
    if (stackSize == 0) {
        stackSize = 0x4000;
    }
    return GSthreadCreate(a, floorGetCurrentFloorGroupID(), stackSize, 1, c, func);
}

void floorUnblockModule(u32 id) {
    if (_floorManager != 0) {
        _floorManager->unblockModule(id);
    }
}

void floorBlockModule(u32 id) {
    if (_floorManager != 0) {
        _floorManager->blockModule(id);
    }
}

u8 floorRegisterScriptModule(u8 kind, u32 a, u32 b, u32 c, u32 d) {
    if (_floorManager == 0) {
        return 0;
    }
    return _floorManager->registerScriptModule(kind, a, b, c, d);
}

u8 floorRegisterModule(u8 kind, u32 id, FloorModuleInterface* module) {
    if (_floorManager == 0) {
        return 0;
    }
    return _floorManager->registerModule(kind, id, module);
}

FloorState floorGetFloorState(void) {
    return _floorManager->getFloorState();
}

void floorMappingCommonScript(void) {
    char* res = tableResBiosGetResPtr(fn_8005C8C4());
    if (res != 0 && _floorManager != 0) {
        if (memcmp(res, "TCOD", 4) == 0) {
            _floorManager->mappingCommonScript(res);
        } else {
            _floorManager->mappingCommonScript(0);
        }
    }
}

void floorUnmappingScript(char* name) {
    if (_floorManager != 0) {
        if (memcmp(name, "TCOD", 4) == 0) {
            _floorManager->unmappingScript(0);
        }
    }
}

void floorMappingScript(char* name) {
    if (_floorManager != 0) {
        if (memcmp(name, "TCOD", 4) == 0) {
            _floorManager->mappingScript(name);
        } else {
            _floorManager->mappingScript(0);
        }
    }
}

u8 floorIsCurentScriptMode(void) {
    GSscript::Tiga* script = _floorManager->getCurrentScript();
    if (script != 0 && script->isMapping()) {
        return 1;
    }
    return 0;
}

bool floorGetCurentScriptMode(void) {
    return _floorManager->getCurrentScriptMode();
}

}

GSscript::Tiga* floorGetCommonScript() {
    return _floorManager->getCommonScript();
}

GSscript::Tiga* floorGetCurentScript() {
    return _floorManager->getCurrentScript();
}

extern "C" {

bool floorIsFloorPushed(void) {
    return _floorManager->isFloorPushed();
}

u8 floorIsPop(void) {
    return _floorManager->isPop();
}

u8 floorIsPush(void) {
    return _floorManager->isPush();
}

s32 floorGetCurrentFloorGroupID(void) {
    return _floorManager->getCurrentFloorGroupID();
}

s32 floorGetNextChangeID(void) {
    return _floorManager->getNextFloorID();
}

s32 floorGetCurrent(void) {
    return _floorManager->getCurrentFloorID();
}

u8 floorChange(u32 id) {
    return _floorManager->change(id);
}

u8 floorPopAndChange(u32 id) {
    return _floorManager->popAndChange(id);
}

u8 floorPop(void) {
    return _floorManager->pop();
}

u8 floorPush(u32 id) {
    return _floorManager->push(id);
}

u8 floorOpen(u32 id) {
    return _floorManager->open(id);
}

}

static void _floorMainThread();
static void _floorScriptThread();

extern "C" {

void GSfloorInit(u32 a, u32 b, u32 c, u32 d) {
    _floorManager = new FloorManager();
    _floorManager->init(a, b + c + d);
}

}

static void _floorScriptThread() {
    while (true) {
        if (_floorManager != 0) {
            _floorManager->scriptUpdate();
        }
        floorDelayPostFunc();
        GSthreadSwitch();
    }
}

static void _floorMainThread() {
    _floorManager->mainThread();
}

FloorState FloorManager::getFloorState() {
    FloorStack* stack = m_stacks->getCurrentStack();
    if (stack != 0) {
        if (getTaskMode() == FLOOR_TASK_2) {
            return stack->getUpdateState();
        }
        return FLOOR_STATE_0;
    }
    return FLOOR_STATE_0;
}

SaveHeader* FloorManager::getStateData(StateDataPtr* ptr) {
    SaveHeader* header = (SaveHeader*)savedataGetStatus(0, 0x16);
    if (ptr != 0) {
        ptr->m_header = header;
        if (ptr->m_header->m_valid == 0) {
            return 0;
        }
        ptr->m_data = (u8*)ptr->m_header + 0x20;
        ptr->m_end = ptr->m_data + ptr->m_header->m_size;
        if (m_maxSize < ptr->m_header->m_total) {
            m_maxSize = ptr->m_header->m_total;
            m_maxID = ptr->m_header->m_floorID;
        }
    }
    return header;
}

// Original had a script-loading routine here that the linker stripped; it keeps the string alive.
static void _floorScriptLoadError() {
    GSlogWrite("Script load error.");
}

u8 FloorManager::makeSaveData(u8** data, u32* size) {
    if (data == 0 || size == 0) {
        return 0;
    }
    GSscript::Tiga* script = m_stacks->getBottomOfStack()->getScriptModule();
    if (script == 0) {
        return 0;
    }
    u32 stateSize = script->getStateSize();
    GSBinWriteStream stream(stateSize);
    script->makeStateData(&stream);
    void* pushState = m_modules->makePushState(FLOOR_STATE_MODE_3);
    u32 pushSize = m_modules->getPushStateSize();
    *size = 0x20 + stateSize + pushSize;
    *data = (u8*)GSmemAllocClr(*size);
    u8* p = *data;
    SaveHeader* header = (SaveHeader*)p;
    if (m_maxSize < *size) {
        m_maxSize = *size;
        m_maxID = getCurrentFloorID();
    }
    memcpy(header, "ANSW", 4);
    p += 0x20;
    header->m_valid = *size;
    header->m_size = stateSize;
    header->m_unkC = pushSize;
    header->m_unk10 = 0;
    header->m_total = m_maxSize;
    header->m_floorID = m_maxID;
    memcpy(p, stream.getTop(), stateSize);
    p += stateSize;
    memcpy(p, pushState, pushSize);
    if (pushState != 0) {
        GSmemFree(pushState);
    }
    GSlogWrite("------------------------------------\n");
    GSlogWrite("header size       = %dbytes\n", 0x20);
    GSlogWrite("script state size = %dbytes\n", stateSize);
    GSlogWrite("system state size = %dbytes\n", pushSize);
    GSlogWrite("total             = %dbytes(max %d)\n", *size, m_maxSize);
    return 1;
}

void FloorManager::mainThread() {
    while (true) {
        switch (getTaskMode()) {
        case FLOOR_TASK_0:
            GSthreadSwitch();
            break;
        case FLOOR_TASK_1: {
            load(m_stacks->getGSfloor(), (FloorEnterMode)m_stacks->getObjective());
            m_stacks->setUpdateState(FLOOR_STATE_2);
            changeTaskMode(FLOOR_TASK_2);
            break;
        }
        case FLOOR_TASK_2:
            if (update(m_stacks->getCurrentStack()) == 1) {
                GSthreadSwitch();
            } else {
                changeTaskMode(m_nextTask);
            }
            break;
        case FLOOR_TASK_3:
            m_modules->unregisterModuleGroup(m_stacks->getGroupID());
            unload(m_stacks->getGSfloor(), true, FLOOR_ENTER_MODE_0);
            m_stacks->clearFlag();
            if (m_nextFloor != -1) {
                m_stacks->setFloorID(m_nextFloor);
                m_stacks->setGroupID(makeFloorGroupID(m_nextFloor));
                changeTaskMode(FLOOR_TASK_1);
            } else {
                changeTaskMode(FLOOR_TASK_0);
            }
            break;
        case FLOOR_TASK_4: {
            floorExecFadeOut();
            m_stacks->setPushFlag();
            void* state = m_modules->makePushState((FloorStateMode)m_stacks->getStateMode());
            m_stacks->setPushState(state, m_modules->getPushStateSize());
            execPostFunction(m_stacks->getCurrentStack(), FLOOR_ENTER_MODE_1);
            u8 kind = floorDataBiosGetFloorKind(m_stacks->getGSfloor());
            unload(m_stacks->getGSfloor(), false, FLOOR_ENTER_MODE_1);
            m_modules->blockModuleGroup(m_stacks->getGroupID());
            m_stacks->block();
            if (kind == 1) {
                m_stacks->reallocPushData();
            }
            m_stacks->push(m_nextFloor);
            changeTaskMode(FLOOR_TASK_1);
            break;
        }
        case FLOOR_TASK_5: {
            m_modules->unregisterModuleGroup(m_stacks->getGroupID());
            m_nextFloor = floorDataBiosGetFloorID(m_stacks->getGSfloor());
            unload(m_stacks->getGSfloor(), true, FLOOR_ENTER_MODE_2);
            m_stacks->pop();
            load(m_stacks->getGSfloor(), FLOOR_ENTER_MODE_2);
            m_modules->restorePopState(m_stacks->getPushState(), (FloorStateMode)m_stacks->getStateMode(), true);
            m_stacks->clearState();
            m_stacks->setUpdateState(FLOOR_STATE_2);
            changeTaskMode(FLOOR_TASK_2);
            break;
        }
        case FLOOR_TASK_6: {
            u32 next = m_nextFloor;
            m_modules->unregisterModuleGroup(m_stacks->getGroupID());
            unload(m_stacks->getGSfloor(), true, FLOOR_ENTER_MODE_2);
            m_stacks->pop();
            m_stacks->freeState();
            m_stacks->clearFlag();
            m_modules->killModuleGroup(m_stacks->getGroupID());
            execPostFunction(m_stacks->getCurrentStack(), FLOOR_ENTER_MODE_0);
            m_nextFloor = next;
            m_changing = 1;
            changeTaskMode(FLOOR_TASK_3);
            break;
        }
        }
    }
}

void FloorManager::execPostFunction(FloorStack* stack, FloorEnterMode mode) {
    floorExecFadeOut();
    if (mode == FLOOR_ENTER_MODE_1) {
        m_modules->executeAll(stack->getFloorID(), FLOOR_STATE_6, FLOOR_MODULE_TYPE_0, mode, -1);
    } else {
        m_modules->executeAll(stack->getFloorID(), FLOOR_STATE_6, FLOOR_MODULE_TYPE_ALL, mode, -1);
    }
    GSthreadSwitch();
    if (mode != FLOOR_ENTER_MODE_1) {
        m_modules->waitFloorScript(FLOOR_STATE_6);
    }
}

void FloorManager::execPreFunction(FloorStack* stack, FloorEnterMode mode) {
    u8 restored = 0;
    StateDataPtr state;
    flooSetFrameRate();
    if (mode == FLOOR_ENTER_MODE_3 && getStateData(&state) == 0) {
        mode = FLOOR_ENTER_MODE_0;
    }
    if (mode == FLOOR_ENTER_MODE_2 || mode == FLOOR_ENTER_MODE_3) {
        m_modules->executeAll(stack->getFloorID(), FLOOR_STATE_2, FLOOR_MODULE_TYPE_0, mode, stack->getGroupID());
    } else {
        m_modules->executeAll(stack->getFloorID(), FLOOR_STATE_2, FLOOR_MODULE_TYPE_ALL, mode, -1);
    }
    GSthreadSwitch();
    m_modules->waitFloorScript(FLOOR_STATE_2);
    if (mode == FLOOR_ENTER_MODE_3) {
        m_modules->restorePopState(state.m_end, FLOOR_STATE_MODE_3, false);
        GSscript::Tiga* script = stack->getScriptModule();
        if (script != 0) {
            restored = script->restoreStateData(state.m_data, state.m_header->m_size);
        }
        if (restored == 0) {
            m_modules->executeAll(stack->getFloorID(), FLOOR_STATE_2, FLOOR_MODULE_TYPE_2, mode, stack->getGroupID());
            GSthreadSwitch();
            m_modules->waitFloorScript(FLOOR_STATE_2);
            stack->setUpdateState(FLOOR_STATE_4);
        } else {
            floorExecScriptIntegerByName("anywaysave_restart", GSfloorGetCurrentFloorGroupID(), 0, 0, 0);
            underTakerMenuResore();
            floorSetFadeScript(0x5960009, 0x5960019);
            stack->setUpdateState(FLOOR_STATE_5);
        }
    } else if (stack->isPopFlag()) {
        m_modules->unblockModuleGroup(stack->getGroupID());
        m_stacks->unblock();
        stack->setUpdateState(FLOOR_STATE_5);
    } else {
        stack->setUpdateState(FLOOR_STATE_4);
    }
    floorExecFadeIn();
}

u8 FloorManager::update(FloorStack* stack) {
    switch (stack->getUpdateState()) {
    case FLOOR_STATE_2:
        execPreFunction(stack, (FloorEnterMode)getCurrentEnterMode());
        stack->clearFlag();
        break;
    case FLOOR_STATE_4: {
        m_modules->executeAll(stack->getFloorID(), FLOOR_STATE_4, FLOOR_MODULE_TYPE_ALL, (FloorEnterMode)getCurrentEnterMode(), -1);
        if (stack->getUpdateState() == FLOOR_STATE_4) {
            stack->setUpdateState(FLOOR_STATE_5);
        }
        break;
    }
    case FLOOR_STATE_5:
        floorSetContinueMode(0);
        m_modules->executeAll(stack->getFloorID(), FLOOR_STATE_4, FLOOR_MODULE_TYPE_0, FLOOR_ENTER_MODE_0, -1);
        break;
    case FLOOR_STATE_6:
        execPostFunction(stack, FLOOR_ENTER_MODE_0);
        return 0;
    }
    return 1;
}

void FloorManager::unload(GSfloor_dd_* floor, bool full, FloorEnterMode mode) {
    if (!floorCheckFightKind(m_nextFloor)) {
        floorCheckFade();
    }
    u32 id = floorDataBiosGetFloorID(floor);
    m_modules->executeAll(id, FLOOR_STATE_8, FLOOR_MODULE_TYPE_0, mode, -1);
    if (full) {
        GSthreadTerminateGroup(GSfloorGetCurrentFloorGroupID());
    }
    GSfsysFree(floorDataBiosGetFileGroupID(floor));
    GSresFreeGroup(floorDataBiosGetGroupID(floor));
    m_stacks->freeAllResource();
    psRemoveParticle();
    psRemoveGenerator();
    psRemoveAppSRT();
    GSlightDeleteCurrentAll();
    GSmodelFreeAllShadowTextures();
    m_changing = 0;
}

void FloorManager::load(GSfloor_dd_* floor, FloorEnterMode mode) {
    u32 fsys = floorDataBiosGetFileGroupID(floor);
    fn_8005C068(gamedatasaveGetStatus(0, 0xb));
    m_modules->executeAll(floorDataBiosGetFloorID(floor), FLOOR_STATE_1, FLOOR_MODULE_TYPE_0, mode, -1);
    floorLayerConfig(floorDataBiosGetFloorID(floor), floorDataBiosGetFloorKind(floor));
    GSlogWrite("\n------------------>>> Floor %d loading... fsysid=[%d]\n\n", floorDataBiosGetFloorID(floor), fsys);
    GSfsysReadWait(fsys);
    floorInitWazaSequence(floorDataBiosGetFloorID(floor));
    GSthreadSwitch();
    GSthreadSwitch();
}

void FloorManager::scriptUpdate() {
    FloorStack* stack = m_stacks->getCurrentStack();
    if (stack != 0) {
        GSscript::Tiga* script = stack->getScriptModule();
        if (script != 0) {
            script->executeThread(timeGetLastFrameSec());
        }
    }
}

void FloorManager::waitForChange() {
    while (m_changing) {
        GSthreadSwitch();
    }
}

bool FloorManager::getCurrentScriptMode() {
    return m_stacks->getCurrentStack()->getType() == FLOOR_MODULE_TYPE_2;
}

int FloorManager::getCurrentEnterMode() {
    FloorStack* stack = m_stacks->getCurrentStack();
    if (floorIsContinueMode()) {
        return 3;
    }
    if (stack->isPopFlag()) {
        return 2;
    }
    return stack->isPushFlag() != 0;
}

void FloorManager::mappingCommonScript(char* name) {
    if (name != 0) {
        if (memcmp(name, "TCOD", 4) == 0) {
            setCommonScriptType(FLOOR_MODULE_TYPE_2);
            m_common.mappingScript(name);
        } else {
            setCommonScriptType(FLOOR_MODULE_TYPE_1);
        }
    } else {
        setCommonScriptType(FLOOR_MODULE_TYPE_1);
    }
}

void FloorManager::unmappingScript(char* name) {
    FloorStack* stack = m_stacks->getCurrentStack();
    if (stack != 0) {
        if (stack->getScriptModule() != 0) {
            stack->getScriptModule()->unmappingScript();
        }
        stack->setType(FLOOR_MODULE_TYPE_1);
    }
}

void FloorManager::mappingScript(char* name) {
    FloorStack* stack = m_stacks->getCurrentStack();
    if (stack != 0 && name != 0) {
        if (memcmp(name, "TCOD", 4) == 0) {
            stack->setType(FLOOR_MODULE_TYPE_2);
            if (stack->getScriptModule() != 0) {
                stack->getScriptModule()->mappingScript(name);
            }
        } else {
            stack->setType(FLOOR_MODULE_TYPE_1);
        }
    } else {
        stack->setType(FLOOR_MODULE_TYPE_1);
    }
}

AppScript* FloorManager::getCurrentScript() {
    return m_stacks->getScriptModule();
}

bool FloorManager::isFloorPushed() {
    return m_stacks->isFloorPushd();
}

u8 FloorManager::isPop() {
    return m_stacks->isPopFlag();
}

u8 FloorManager::isPush() {
    return m_stacks->isPushFlag();
}

u32 FloorManager::getCurrentFloorGroupID() {
    return m_stacks->getGroupID();
}

u32 FloorManager::getNextFloorID() {
    return m_nextFloor;
}

u32 FloorManager::getCurrentFloorID() {
    return m_stacks->getFloorID();
}

u8 FloorManager::popAndChange(unsigned int floorID) {
    if (getTaskMode() != FLOOR_TASK_2) {
        return 0;
    }
    floorSetFadeScript(0x5960009, 0x5960008);
    if (!m_stacks->isPopReady()) {
        return 0;
    }
    close();
    setNextTaskMode(FLOOR_TASK_6);
    m_nextFloor = floorID;
    m_changing = 1;
    return 1;
}

u8 FloorManager::change(unsigned int floorID) {
    if (getTaskMode() != FLOOR_TASK_2) {
        return 0;
    }
    if (floorDataBiosGetPtr(floorID) == 0) {
        return 0;
    }
    floorSetFadeScript(0x5960009, 0x5960008);
    close();
    setNextTaskMode(FLOOR_TASK_3);
    m_nextFloor = floorID;
    m_changing = 1;
    return 1;
}

u8 FloorManager::pop() {
    if (getTaskMode() != FLOOR_TASK_2) {
        return 0;
    }
    floorSetFadeScript(0x5960009, 0x5960008);
    if (!m_stacks->isPopReady()) {
        return 0;
    }
    close();
    setNextTaskMode(FLOOR_TASK_5);
    m_changing = 1;
    return 1;
}

u8 FloorManager::push(unsigned int floorID) {
    floorSetFadeScript(0x5960009, 0x5960008);
    if (!m_stacks->isPushReady()) {
        return 0;
    }
    changeTaskMode(FLOOR_TASK_4);
    m_nextFloor = floorID;
    m_changing = 1;
    return 1;
}

u8 FloorManager::close() {
    if (getTaskMode() != FLOOR_TASK_2) {
        return 0;
    }
    m_modules->killModuleGroup(m_stacks->getGroupID());
    m_stacks->setUpdateState(FLOOR_STATE_6);
    m_nextFloor = -1;
    return 1;
}

u8 FloorManager::open(unsigned int floorID) {
    if (getTaskMode() != FLOOR_TASK_0) {
        return 0;
    }
    if (floorDataBiosGetPtr(floorID) == 0) {
        return 0;
    }
    m_stacks->setFloorID(floorID);
    m_stacks->setGroupID(makeFloorGroupID(floorID));
    m_stacks->setUpdateState(FLOOR_STATE_2);
    changeTaskMode(FLOOR_TASK_1);
    return 1;
}

void FloorManager::init(unsigned long numStacks, unsigned long numModules) {
    if (m_modules != 0) {
        delete m_modules;
        m_modules = 0;
    }
    if (m_stacks != 0) {
        delete m_stacks;
        m_stacks = 0;
    }
    m_modules = new FloorModuleList(numModules);
    m_stacks = new FloorStackList(numStacks);
    changeTaskMode(FLOOR_TASK_0);
    GSthreadSetName(GSthreadCreate(0, 0x7d0, 0x4000, 1, 1, (void*)_floorMainThread), "floorMainThread");
    GSthreadSetName(GSthreadCreate(1, 0x7d0, 0x1000, 1, 1, (void*)_floorScriptThread), "scriptUpdate");
}

FloorManager::~FloorManager() {
    if (m_modules != 0) {
        delete m_modules;
        m_modules = 0;
    }
    if (m_stacks != 0) {
        delete m_stacks;
        m_stacks = 0;
    }
}

FloorManager::FloorManager() {
    m_changing = 0;
    m_modules = 0;
    m_stacks = 0;
    m_maxSize = 0;
    m_maxID = 0;
}

extern "C" void* GSmemAlloc(u32 size);

// Inline members defined after their callers: emitted as weak out-of-line functions.
inline void FloorStackList::freeResource(unsigned long group, unsigned long id) {
    getCurrentStack()->freeResource(group, id);
}

inline FloorStack* FloorStackList::getCurrentStack() {
    return getTopOfStack();
}

inline FloorStack* FloorStackList::getTopOfStack() {
    return m_stacks + m_depth;
}

inline void FloorStackList::addResource(unsigned long group, unsigned long id) {
    getCurrentStack()->addResource(group, id);
}

inline FloorState FloorStack::getUpdateState() {
    return m_updateState;
}

inline FloorStack* FloorStackList::getBottomOfStack() {
    return m_stacks;
}

inline void FloorStackList::freeState() {
    GSmemFree(getCurrentStack()->getPushState());
    clearState();
}

inline void* FloorStack::getPushState() {
    return m_pushData;
}

inline void FloorStackList::clearState() {
    getCurrentStack()->setPushState(0, 0);
}

inline void* FloorStackList::getPushState() {
    return getCurrentStack()->getPushState();
}

inline void FloorStackList::reallocPushData() {
    getCurrentStack()->reallocPushData();
}

inline void FloorStackList::setPushFlag() {
    getCurrentStack()->setPushFlag();
}

inline void FloorStackList::setFloorID(unsigned long id) {
    getCurrentStack()->setFloorID(id);
}

inline void FloorStackList::clearFlag() {
    getCurrentStack()->clearFlag();
}

inline u32 FloorStackList::getGroupID() {
    return getCurrentStack()->getGroupID();
}

inline u32 FloorStack::getGroupID() const {
    return m_groupID;
}

inline u32 FloorStack::getFloorID() const {
    return m_floorID;
}

inline u8 FloorStack::isPopFlag() {
    return m_popFlag;
}

inline void FloorStack::setUpdateState(FloorState state) {
    m_updateState = state;
}

inline void FloorStackList::freeAllResource() {
    getCurrentStack()->freeAllResource();
}

inline FloorModuleType FloorStack::getType() {
    return m_type;
}

inline u8 FloorStack::isPushFlag() {
    return m_pushFlag;
}

inline void FloorStack::setType(FloorModuleType type) {
    m_type = type;
}

inline AppScript* FloorStackList::getScriptModule() {
    return getCurrentStack()->getScriptModule();
}

inline bool FloorStackList::isFloorPushd() const {
    return m_depth != 0;
}

inline u8 FloorStackList::isPopFlag() {
    return getCurrentStack()->isPopFlag();
}

inline u8 FloorStackList::isPushFlag() {
    return getCurrentStack()->isPushFlag();
}

inline u32 FloorStackList::getFloorID() {
    return getCurrentStack()->getFloorID();
}

inline bool FloorStackList::isPopReady() const {
    return m_depth > 0;
}

inline bool FloorStackList::isPushReady() const {
    return m_num - 1 > m_depth;
}

inline bool GSscript::Tiga::isMapping() {
    return m_mapped != 0;
}

inline u8* GSBinWriteStream::getTop() const {
    return m_top;
}

inline GSBinWriteStream::GSBinWriteStream(unsigned long size) {
    u8* p = (u8*)GSmemAlloc(size);
    m_buffer = p;
    m_cursor = p;
    m_top = p;
    m_size = size;
    m_owned = 1;
}

inline u32 FloorModuleList::getPushStateSize() const {
    return m_pushStateSize;
}
