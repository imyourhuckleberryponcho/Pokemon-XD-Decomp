#ifndef SYSDOLPHIN_BASELIB_PSDISP_H
#define SYSDOLPHIN_BASELIB_PSDISP_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#define PS_NUM_LINK 0x10

void psDispBeginFrame(void);
int psDispHasRenderData(u32 target_link);
void psDispSetProjection(void* proj);
void psDispParticles(u32 target_link, u32 sw, void* camera);
HSD_Particle* particleSort(s32, HSD_Particle**, HSD_Particle**);
void setVtxDesc(s32);

#endif
