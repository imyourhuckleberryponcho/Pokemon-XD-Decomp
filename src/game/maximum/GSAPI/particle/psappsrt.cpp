#include <dolphin/types.h>

#pragma pool_strings off

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct Quaternion {
    f32 x, y, z, w;
} Quaternion;

struct HSD_Generator;

typedef struct HSD_psAppSRT {
    struct HSD_psAppSRT* next;
    struct HSD_Generator* gp;
    Vec3 translate;
    Quaternion rot;
    Vec3 scale;
    u8 status;
    u8 frameNum;
    u16 usedCount;
    u8 unk34[0x38];
    void (*freefunc)(struct HSD_psAppSRT* srt);
    u16 idnum;
    u8 xA2;
} HSD_psAppSRT;

typedef struct HSD_Generator {
    u8 unk0[0x18];
    u16 idnum;
    u8 unk1A[0x36];
    HSD_psAppSRT* appsrt;
} HSD_Generator;

typedef struct HSD_Particle {
    u8 unk0[0x90];
    HSD_psAppSRT* appsrt;
} HSD_Particle;

void* HSD_Alloc(u32 size);
void HSD_Free(void* ptr);
void* memset(void* dst, int val, unsigned long n);

extern u16 numActivePSAppSRT;
extern u16 numPeakPSAppSRT;

static HSD_psAppSRT* freeAppSRT;
static u16 psSizeofAppSRT;

s32 psInitAppSRT(s32 num, u32 size) {
    s32 i;
    HSD_psAppSRT* srt;

    numActivePSAppSRT = 0;
    numPeakPSAppSRT = 0;
    psSizeofAppSRT = size;
    freeAppSRT = NULL;
    for (i = 0; i < num; i++) {
        srt = HSD_Alloc(size);
        if (srt == NULL) {
            return i;
        }
        memset(srt, 0, (s32)size);
        srt->next = freeAppSRT;
        freeAppSRT = srt;
    }
    return i;
}

void psRemoveAppSRT(void) {
    HSD_psAppSRT* srt;
    HSD_psAppSRT* next;

    for (srt = freeAppSRT; srt != NULL; srt = next) {
        next = srt->next;
        HSD_Free(srt);
    }
    freeAppSRT = NULL;
}

HSD_psAppSRT* psAddGeneratorAppSRT(HSD_Generator* gp, u8 status) {
    u16 idnum = gp->idnum;
    HSD_psAppSRT* srt;

    if (freeAppSRT == NULL) {
        freeAppSRT = HSD_Alloc(psSizeofAppSRT);
        if (freeAppSRT != NULL) {
            memset(freeAppSRT, 0, psSizeofAppSRT);
        }
    }
    if ((srt = freeAppSRT) != NULL) {
        freeAppSRT = srt->next;
        srt->next = NULL;
        srt->usedCount = 1;
        srt->frameNum = 0;
        srt->status = status;
        srt->translate.z = 0.0F;
        srt->translate.y = 0.0F;
        srt->translate.x = 0.0F;
        srt->rot.z = 0.0F;
        srt->rot.y = 0.0F;
        srt->rot.x = 0.0F;
        srt->scale.z = 1.0F;
        srt->scale.y = 1.0F;
        srt->scale.x = 1.0F;
        srt->freefunc = NULL;
        srt->xA2 = 0;
        srt->gp = NULL;
        srt->idnum = idnum;
        numActivePSAppSRT++;
        if (numActivePSAppSRT > numPeakPSAppSRT) {
            numPeakPSAppSRT = numActivePSAppSRT;
        }
    }
    return gp->appsrt = srt;
}

s32 psAttachParticleAppSRT(HSD_Particle* pp, HSD_psAppSRT* srt) {
    if (srt == NULL || pp == NULL || pp->appsrt != NULL) {
        return -1;
    }
    pp->appsrt = srt;
    return ++srt->usedCount;
}

s32 psAttachGeneratorAppSRT(HSD_Generator* gp, HSD_psAppSRT* srt) {
    if (srt == NULL || gp == NULL || gp->appsrt != NULL) {
        return -1;
    }
    gp->appsrt = srt;
    return ++srt->usedCount;
}

s32 psRemoveParticleAppSRT(HSD_Particle* pp);
s32 psRemoveGeneratorAppSRT(HSD_Generator* gp);

s32 psChangeParticleAppSRT(HSD_Particle* pp, HSD_psAppSRT* srt) {
    if (srt == NULL || pp == NULL) {
        return -1;
    }
    if (pp->appsrt != NULL) {
        psRemoveParticleAppSRT(pp);
    }
    pp->appsrt = srt;
    return ++srt->usedCount;
}

s32 psChangeGeneratorAppSRT(HSD_Generator* gp, HSD_psAppSRT* srt) {
    if (srt == NULL || gp == NULL) {
        return -1;
    }
    if (gp->appsrt != NULL) {
        psRemoveGeneratorAppSRT(gp);
    }
    gp->appsrt = srt;
    return ++srt->usedCount;
}

static inline void psFreeAppSRT(HSD_psAppSRT* srt) {
    if (srt->freefunc != NULL) {
        srt->freefunc(srt);
    }
    srt->next = freeAppSRT;
    freeAppSRT = srt;
    numActivePSAppSRT--;
}

s32 psRemoveParticleAppSRT(HSD_Particle* pp) {
    HSD_psAppSRT* srt;
    s32 count;

    srt = pp->appsrt;
    if (srt == NULL) {
        return -1;
    }
    count = --srt->usedCount;
    if (count == 0) {
        srt = pp->appsrt;
        psFreeAppSRT(srt);
    }
    pp->appsrt = NULL;
    return count;
}

s32 psRemoveGeneratorAppSRT(HSD_Generator* gp) {
    HSD_psAppSRT* srt;
    s32 count;

    srt = gp->appsrt;
    if (srt == NULL) {
        return -1;
    }
    if (srt->gp == gp) {
        srt->gp = NULL;
    }
    srt = gp->appsrt;
    count = --srt->usedCount;
    if (count == 0) {
        srt = gp->appsrt;
        psFreeAppSRT(srt);
    }
    gp->appsrt = NULL;
    return count;
}
