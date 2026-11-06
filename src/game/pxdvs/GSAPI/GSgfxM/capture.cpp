#include <dolphin/types.h>

struct GSgfxLayer;

void GSgfxCaptureRenderFrameNumber(GSgfxLayer*) {}

void GSgfxCaptureUpdate(void*) {}

extern "C" {

void GSgfxCaptureMovieStop(void) {}

void GSgfxCaptureMovieStart(void) {}

void GSgfxCaptureSetTarget(void) {}

}
