#include <dolphin/types.h>

class GSgfxLayer;

void GSgfxCaptureRenderFrameNumber(GSgfxLayer*) {}

void GSgfxCaptureUpdate(void*) {}

extern "C" {

void GSgfxCaptureMovieStop(void) {}

void GSgfxCaptureMovieStart(void) {}

void GSgfxCaptureSetTarget(void) {}

}
