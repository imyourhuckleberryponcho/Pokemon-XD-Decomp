



#include <dolphin/types.h>

#pragma pool_strings off

#define PS_NUM_LINK 16
#define HSD_ASSERT_LINE(line, cond) ((cond) ? ((void) 0) : __assert("pslist.c", line, #cond))

typedef struct HSD_Particle HSD_Particle;
struct HSD_Particle {
 HSD_Particle* next;
 u32 kind;
 u8 pad08[0x15];
 u8 linkNo;
 u8 pad1E[0x94 - 0x1E];
};

typedef struct {
    HSD_Particle* head;
    HSD_Particle* tail;
} psSortBucket;

void* HSD_Alloc(u32 size);
void HSD_Free(void* ptr);
void* memset(void* dst, int val, unsigned long n);
void __assert(const char* file, u32 line, const char* msg);

extern u16 numActiveParticles;
extern u16 numPeakParticles;

static HSD_Particle* freeParticle;
HSD_Particle* activeParticle[PS_NUM_LINK];
static s32 sortDirty[PS_NUM_LINK];
static HSD_Particle* activeParticleXLU[PS_NUM_LINK];

s32 _psLinkInit(s32 num)
{
    int i;
    HSD_Particle* pp;

    for (i = 0; i < PS_NUM_LINK; i++) {
        activeParticle[i] = NULL;
        sortDirty[i] = 0;
        activeParticleXLU[i] = NULL;
    }
    freeParticle = NULL;

    for (num--; num >= 0; num--) {
        pp = (HSD_Particle*) HSD_Alloc(sizeof(HSD_Particle));
        memset(pp, 0, sizeof(HSD_Particle));
        if (pp == NULL) {
            return -1;
        }
        pp->next = freeParticle;
        freeParticle = pp;
    }
    return num;
}

void _psListClear(void)
{
    HSD_Particle* pp;
    HSD_Particle* next;
    s32 i;

    for (pp = freeParticle; pp != NULL; pp = next) {
        next = pp->next;
        HSD_Free(pp);
    }
    freeParticle = NULL;

    for (i = 0; i < PS_NUM_LINK; i++) {
        for (pp = activeParticle[i]; pp != NULL; pp = next) {
            next = pp->next;
            HSD_Free(pp);
        }
        activeParticle[i] = NULL;
        sortDirty[i] = 0;
        activeParticleXLU[i] = NULL;
    }
}

HSD_Particle* _psListNew(HSD_Particle** parent, s32 linkNo)
{
    HSD_Particle* pp;

    if (freeParticle == NULL) {
        freeParticle = (HSD_Particle*) HSD_Alloc(sizeof(HSD_Particle));
        memset(freeParticle, 0, sizeof(HSD_Particle));
    }
    pp = freeParticle;
    if (pp == NULL) {
        return NULL;
    }
    numActiveParticles++;
    if (numActiveParticles > numPeakParticles) {
        numPeakParticles = numActiveParticles;
    }
    freeParticle = pp->next;
    if (parent == NULL) {
        pp->next = activeParticle[linkNo];
        activeParticle[linkNo] = pp;
    } else {
        pp->next = *parent;
        *parent = pp;
    }
    sortDirty[linkNo] = 1;
    return pp;
}

void _psListDelete(HSD_Particle* pp, HSD_Particle* parent)
{
    sortDirty[pp->linkNo] = 1;
    if (parent == NULL) {
        HSD_ASSERT_LINE(136, activeParticle[pp->linkNo] == pp);
        activeParticle[pp->linkNo] = pp->next;
    } else {
        HSD_ASSERT_LINE(139, parent->next == pp);
        parent->next = pp->next;
    }
    pp->next = freeParticle;
    freeParticle = pp;
    numActiveParticles--;
}

HSD_Particle* _psListGetFirst(s32 linkNo)
{
    HSD_ASSERT_LINE(152, linkNo >= 0 && linkNo < PS_NUM_LINK);
    return activeParticle[linkNo];
}

HSD_Particle* particleSort(s32 linkNo, HSD_Particle** texEdge, HSD_Particle** xlu)
{
    psSortBucket buckets[16];
    HSD_Particle* pp;
    HSD_Particle* next;
    HSD_Particle* head0;
    HSD_Particle* head1;
    HSD_Particle** tail0;
    HSD_Particle** tail1;
    HSD_Particle* result;
    s32 idx;
    s32 i;

    pp = activeParticle[linkNo];
    if (sortDirty[linkNo] == 0) {
        if (pp == NULL) {
            *texEdge = NULL;
            *xlu = NULL;
            return NULL;
        }
        if (pp->kind & 8) {
            *texEdge = pp;
        } else {
            *texEdge = NULL;
        }
        *xlu = activeParticleXLU[linkNo];
        return pp;
    }

    sortDirty[linkNo] = 0;
    if (pp == NULL) {
        activeParticleXLU[linkNo] = NULL;
        *texEdge = NULL;
        *xlu = NULL;
        return NULL;
    }

    memset(buckets, 0, sizeof(buckets));
    idx = ((pp->kind >> 25) & 7) + (((pp->kind & 8) ? 0 : 1) * 8);
    buckets[idx].head = pp;
    for (next = pp->next; next != NULL; next = next->next) {
        if ((pp->kind ^ next->kind) & 0x0E000008) {
            buckets[idx].tail = pp;
            idx = ((next->kind >> 25) & 7) + (((next->kind & 8) ? 0 : 1) * 8);
            if (buckets[idx].head == NULL) {
                buckets[idx].head = next;
            } else {
                buckets[idx].tail->next = next;
            }
        }
        pp = next;
    }
    buckets[idx].tail = pp;

    tail0 = NULL;
    head0 = NULL;
    tail1 = NULL;
    head1 = NULL;
    for (i = 0; i < 8; i++) {
        if (buckets[i].head != NULL) {
            if (head0 == NULL) {
                head0 = buckets[i].head;
            } else {
                *tail0 = buckets[i].head;
            }
            tail0 = &buckets[i].tail->next;
        }
    }
    for (i = 8; i < 16; i++) {
        if (buckets[i].head != NULL) {
            if (head1 == NULL) {
                head1 = buckets[i].head;
            } else {
                *tail1 = buckets[i].head;
            }
            tail1 = &buckets[i].tail->next;
        }
    }

    result = NULL;
    if (tail0 != NULL) {
        result = head0;
        *tail0 = head1;
    }
    if (tail1 != NULL) {
        if (result == NULL) {
            result = head1;
        }
        *tail1 = NULL;
    }
    activeParticle[linkNo] = result;
    activeParticleXLU[linkNo] = head1;
    *texEdge = head0;
    *xlu = head1;
    return result;
}
