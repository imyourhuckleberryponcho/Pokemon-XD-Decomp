#include <dolphin/types.h>

struct FloorModule {
    u8 unk0[0x2C];
};

static FloorModule _floorModuleEffectViewer;

extern "C" {

FloorModule* effectViewerGetFloorModule(void) { return &_floorModuleEffectViewer; }

}
