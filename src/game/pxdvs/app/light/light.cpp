#include <dolphin/types.h>

#pragma pool_strings off

enum FloorEnterMode {
    FLOOR_ENTER_MODE_0
};

// Callbacks a floor (map) module registers with the floor system.
struct FloorModuleInterface {
    u32 unk0;
    void (*initialize)(unsigned int groupID, FloorEnterMode mode);
    void (*update)(unsigned int groupID, FloorEnterMode mode);
    u32 unkC;
    void (*finalize)(unsigned int groupID, FloorEnterMode mode);
    u32 unk14;
    const char* (*getModuleName)(void);
    u8 unk1C[0x10];
};

class LightEditor {
public:
    LightEditor();
    void init();
    void editUpdate();

private:
    u8 unk0[0xC];
};

extern "C" {
void floorGetLightInfo(u32* base, s32* num);
void* GSresGetResourceAllGroup(u32 id);
u32 GSfloorGetCurrentFloorGroupID(void);
void GSthreadBlockGroup(u32 groupID);
void GSthreadUnblockGroup(u32 groupID);
void GSlightFree(void* light);
u32 GSinputButtonsChanged(s32 pad);
u32 GSinputButtonsPressed(s32 pad);
void GSinputClearButtonData(s32 pad, u32 buttons);
void FloorModuleInterface_clear(FloorModuleInterface* iface);
s32 floorRegisterModule(s32 priority, s32, FloorModuleInterface* iface);
}

static FloorModuleInterface _floorModuleLight;
static s32 _hModuleLight;
static u8 _eventLightSize;
static void* _eventGSlight;
static bool _debugMode;
static LightEditor* _lightEditor;

extern "C" {

void* lightGetLight(s32 index) {
    u32 base;
    s32 num;
    floorGetLightInfo(&base, &num);
    if (index < num) {
        return GSresGetResourceAllGroup(base | index);
    }
    if (index == num) {
        return _eventGSlight;
    }
    return NULL;
}

s32 lightGetLightSize(void) {
    s32 num = 0;
    floorGetLightInfo(NULL, &num);
    if (_eventGSlight != NULL) {
        num++;
    }
    return num;
}

bool lightIsDebugMode(void) {
    return _debugMode;
}

void lightSetDebugMode(bool on) {
    _debugMode = on;
    if (on) {
        GSthreadBlockGroup(GSfloorGetCurrentFloorGroupID());
    } else {
        GSthreadUnblockGroup(GSfloorGetCurrentFloorGroupID());
    }
}

}

static const char* _lightGetModuleName() {
    return "light";
}

static void _lightFinalize(unsigned int groupID, FloorEnterMode mode) {
    if (_eventGSlight != NULL) {
        GSlightFree(_eventGSlight);
        _eventGSlight = NULL;
    }
    _eventLightSize = 0;
    _debugMode = false;
}

static void _lightUpdate(unsigned int groupID, FloorEnterMode mode) {
    if ((GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x200) && _debugMode) {
        GSinputClearButtonData(1, 0x200);
        _debugMode = false;
        GSthreadUnblockGroup(GSfloorGetCurrentFloorGroupID());
    }
    if (_debugMode) {
        _lightEditor->editUpdate();
    }
}

static void _lightInitialize(unsigned int groupID, FloorEnterMode mode) {
    _eventLightSize = 0;
    _debugMode = false;
    _lightEditor->init();
}

extern "C" void lightInit(void) {
    FloorModuleInterface_clear(&_floorModuleLight);
    _floorModuleLight.initialize = _lightInitialize;
    _floorModuleLight.update = _lightUpdate;
    _floorModuleLight.finalize = _lightFinalize;
    _floorModuleLight.getModuleName = _lightGetModuleName;
    _hModuleLight = floorRegisterModule(0x80, 0, &_floorModuleLight);
    _debugMode = false;
    _eventLightSize = 0;
    _eventGSlight = NULL;
    _lightEditor = new LightEditor;
}
