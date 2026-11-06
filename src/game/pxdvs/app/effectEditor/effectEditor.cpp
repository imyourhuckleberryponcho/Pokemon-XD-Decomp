#include <dolphin/types.h>

struct FloorModule {
#ifdef __MWERKS__
    u8 unk0[0x2C];
#else
    void* slot[11];
#endif
};

static FloorModule _floorModuleEffectViewer;

extern "C" {

FloorModule* effectViewerGetFloorModule(void) { return &_floorModuleEffectViewer; }

}
