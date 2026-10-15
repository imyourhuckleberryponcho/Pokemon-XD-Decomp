// Compiled as C with deferred inlining (see configure.py). Particle system front end: generator
// flag setters, family kill/visibility helpers, point JObj table and the particle bank setup.
// the struct layouts are XD's own.
#include <dolphin/types.h>

#pragma pool_strings off

typedef struct PSGenerator PSGenerator;
typedef struct PSParticle PSParticle;

struct PSGenerator {
    /* 0x00 */ PSGenerator* next;
    /* 0x04 */ u32 flags;
    /* 0x08 */ u8 pad08[0x08];
    /* 0x10 */ u16 maxLife;
    /* 0x12 */ u16 angleFlags;
    /* 0x14 */ u8 bank;
    /* 0x15 */ u8 linkNo;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ u16 familyId;
    /* 0x1A */ u8 pad1A[0x1E];
    /* 0x38 */ f32 gravity;
    /* 0x3C */ f32 friction;
    /* 0x40 */ u8 pad40[4];
    /* 0x44 */ f32 radius;
    /* 0x48 */ u8 pad48[4];
    /* 0x4C */ u32 childCount;
    /* 0x50 */ void* appSRT;
    /* 0x54 */ f32 shape[12];
    /* 0x84 */ u8 pad84[8];
    /* 0x8C */ u16 generatorFlags;
    /* 0x8E */ u16 index;
    /* 0x90 */ u8 pad90[0x18];
    /* 0xA8 */ void* linkedJObj;
    /* 0xAC */ f32 angleRadiusScale[3];
};

struct PSParticle {
    /* 0x00 */ PSParticle* next;
    /* 0x04 */ u32 kind; /* also used as flags */
    /* 0x08 */ u8 bank;
    /* 0x09 */ u8 texGroup;
    /* 0x0A */ u8 poseNum;
    /* 0x0B */ u8 palNum;
    /* 0x0C */ u16 sizeCount;
    /* 0x0E */ u16 primColCount;
    /* 0x10 */ u16 envColCount;
    /* 0x12 */ u8 primCol[4];
    /* 0x16 */ u8 envCol[4];
    /* 0x1A */ u16 cmdWait;
    /* 0x1C */ u8 loopCount;
    /* 0x1D */ u8 linkNo;
    /* 0x1E */ u16 familyId;
    /* 0x20 */ u8* cmdList;
    /* 0x24 */ u16 cmdPtr;
    /* 0x26 */ u16 cmdMarkPtr;
    /* 0x28 */ u16 cmdLoopPtr;
    /* 0x2A */ u16 life;
    /* 0x2C */ f32 vel[3];
    /* 0x38 */ f32 grav;
    /* 0x3C */ f32 fric;
    /* 0x40 */ f32 pos[3];
    /* 0x4C */ f32 size;
    /* 0x50 */ f32 rotate;
    /* 0x54 */ u16 aCmpCount;
    /* 0x56 */ u8 aCmpMode;
    /* 0x57 */ u8 aCmpParam1;
    /* 0x58 */ u8 aCmpParam2;
    /* 0x59 */ u8 pJObjOfs;
    /* 0x5A */ u16 matColCount;
    /* 0x5C */ u16 ambColCount;
    /* 0x5E */ u16 rotateCount;
    /* 0x60 */ u8 pad60[4];
    /* 0x64 */ f32 sizeTarget;
    /* 0x68 */ f32 rotateTarget;
    /* 0x6C */ u16 primColRemain;
    /* 0x6E */ u16 envColRemain;
    /* 0x70 */ u8 pad70[8];
    /* 0x78 */ u16 matColRemain;
    /* 0x7A */ u16 ambColRemain;
    /* 0x7C */ u16 aCmpRemain;
    /* 0x7E */ u8 pad7E[2];
    /* 0x80 */ u8 matRGB;
    /* 0x81 */ u8 matA;
    /* 0x82 */ u8 ambRGB;
    /* 0x83 */ u8 ambA;
    /* 0x84 */ u8 pad84[4];
    /* 0x88 */ f32 trail;
    /* 0x8C */ PSGenerator* owner;
    /* 0x90 */ void* appSRT;
};

#define PS_FLAG_HIDDEN 0x20000000
#define PS_FLAG_POINT_JOBJ 0x8000

typedef struct PSTexGroup {
    u32 num;     /* 0x00 */
    u32 fmt;     /* 0x04 */
    u32 tlutfmt; /* 0x08 */
    u32 width;   /* 0x0C */
    u32 height;  /* 0x10 */
    u16 palnum;  /* 0x14 */
    u16 palflag; /* 0x16 */
    u8* texTable[1]; /* 0x18 */
} PSTexGroup;

typedef struct PSFormGroup {
    u32 num;
    u8* formTable[1];
} PSFormGroup;

typedef struct PSCmdList {
    u16 type;     /* 0x00 */
    u16 texGroup; /* 0x02 */
    u16 genLife;  /* 0x04 */
    u16 life;     /* 0x06 */
    u32 kind;     /* 0x08 */
    f32 grav;     /* 0x0C */
    f32 fric;     /* 0x10 */
    f32 vx;       /* 0x14 */
    f32 vy;       /* 0x18 */
    f32 vz;       /* 0x1C */
    f32 radius;   /* 0x20 */
    f32 angle;    /* 0x24 */
    f32 random;   /* 0x28 */
    f32 size;     /* 0x2C */
    f32 param1;   /* 0x30 */
    f32 param2;   /* 0x34 */
    f32 param3;   /* 0x38 */
    u8 cmdList[1]; /* 0x3C */
} PSCmdList;

/* Source order is the reverse of the link order (-inline deferred). */
void* psPointJObj[8];
s32 psNumCmdList[64];
s32 psNumTexGroup[64];
PSCmdList** psCmdListArray[64];
PSTexGroup** psTexGroupArray[64];
PSFormGroup** psFormGroupArray[64];
u32* ptclref[64];

extern PSGenerator* activeGenerator;
/* Source order is the reverse of the link order (-inline deferred). */
u16 numActiveParticles;
u16 numActiveGenerators;
u16 numActivePSAppSRT;
u16 numPeakParticles;
u16 numPeakGenerators;
u16 numPeakPSAppSRT;
u16 g_ps_token;

PSParticle* _psListGetFirst(s32 linkNo);
PSParticle* _psListNew(PSParticle** head, s32 linkNo);
void _psListClear(void);
void _psLinkInit(int num);
void psKillAllGenerator(void);
u16 psGetNewIDNum(void);
void psAttachParticleAppSRT(PSParticle* pp, void* appSRT);
void psInterpretParticle0(PSParticle* pp, void* parent);
void OSPanic(const char* file, s32 line, const char* msg, ...);
void _psListDelete(PSParticle* pp, PSParticle* parent);
s32 psRemoveParticleAppSRT(PSParticle* pp);
void psKillGeneratorID(s32 familyId);
void HSD_JObjUnref(void* jobj);
void __assert(const char* file, u32 line, const char* msg);

PSParticle* psGenerateParticle0(PSParticle** head, s32 linkNo, s32 bank, void* unused6, s32 unused7,
                                u32 kind, u16 texGroup, u8* cmdList, s32 life, f32 x, f32 y, f32 z,
                                f32 vx, f32 vy, f32 vz, f32 size, f32 grav, f32 fric, s32 palflag,
                                PSGenerator* gp, s32 flgInterpret);
void psInitDataBankLocate(int* cmdBank, int* texBank, int* formBank);

/* Returns the successor (read first): as psKillParticle's own local it is coloured like retail
 * in the inlined callers. */
static inline PSParticle* psKillParticle(PSParticle* pp)
{
    PSParticle* next;
    PSParticle* prev;
    PSParticle* p;

    next = pp->next;
    prev = NULL;
    for (p = _psListGetFirst(pp->linkNo); p != NULL; p = p->next) {
        if (p == pp) {
            if (pp->owner != NULL) {
                pp->owner->childCount--;
            }
            if (pp->appSRT != NULL) {
                psRemoveParticleAppSRT(pp);
            }
            if (p->kind & PS_FLAG_POINT_JOBJ) {
                u32 slotIdx = (p->kind >> 12) & 0x7;
                void* jobj = psPointJObj[slotIdx];

                if (jobj != NULL) {
                    HSD_JObjUnref(jobj);
                    psPointJObj[slotIdx] = NULL;
                }
            }
            _psListDelete(p, prev);
            break;
        }
        prev = p;
    }
    return next;
}

void psInitDataBankLocate(int* cmdBank, int* texBank, int* formBank)
{
    int i;
    int num;
    int num2;
    PSCmdList** base;
    int* ptr;
    int* group;
    int* groups;
    u32 fi;
    PSFormGroup* fg;
    int j;
    int k;
    int num_groups;

    switch (*(u16*) cmdBank) {
    case 0:
        num2 = cmdBank[1];
        base = (PSCmdList**) (cmdBank + 2);
        num = 0;
        for (i = 0; i < num2; i++) {
            cmdBank[i + 2] += (int) cmdBank;
        }
        break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
        num = cmdBank[1];
        num2 = cmdBank[2] + num;
        base = (PSCmdList**) (cmdBank + 3 - num);
        ptr = cmdBank;
        for (j = 0; j < cmdBank[2]; j++) {
            if (ptr[3] != 0) {
                ptr[3] += (int) cmdBank;
            }
            ptr++;
        }
        break;
    }

    for (i = num; i < num2; i++) {
        if (base[i] != NULL) {
            base[i]->kind &= 0xF1FFFFFF;
            base[i]->kind |= 0x08000000;
        }
    }

    num_groups = texBank[0];
    group = groups = texBank + 1;
    for (k = 1; k <= num_groups; k++) {
        if (group[0] != 0) {
            group[0] += (int) texBank;
        }
        group++;
    }

    for (k = 0; k < num_groups; k++) {
        PSTexGroup* tg = (PSTexGroup*) groups[k];

        if (tg != NULL) {
            u32 ti;

            for (ti = 0; ti < ((PSTexGroup*) groups[k])->num; ti++) {
                if (((PSTexGroup*) groups[k])->texTable[ti] != NULL) {
                    ((PSTexGroup*) groups[k])->texTable[ti] += (u32) texBank;
                }
            }
            tg = (PSTexGroup*) groups[k];
            if (tg->fmt == 8 || tg->fmt == 9 || tg->fmt == 10) {
                if (tg->palflag & 1) {
                    if (tg->texTable[tg->num] != NULL) {
                        tg->texTable[tg->num] += (u32) texBank;
                    }
                } else if (tg->palnum != 0) {
                    for (ti = tg->num; ti < ((PSTexGroup*) groups[k])->num + ((PSTexGroup*) groups[k])->palnum; ti++) {
                        if (((PSTexGroup*) groups[k])->texTable[ti] != NULL) {
                            ((PSTexGroup*) groups[k])->texTable[ti] += (u32) texBank;
                        }
                    }
                } else {
                    for (ti = tg->num; ti < ((PSTexGroup*) groups[k])->num * 2; ti++) {
                        if (((PSTexGroup*) groups[k])->texTable[ti] != NULL) {
                            ((PSTexGroup*) groups[k])->texTable[ti] += (u32) texBank;
                        }
                    }
                }
            }
        }
    }

    if (formBank == NULL) {
        return;
    }
    for (i = 1; i <= num_groups; i++) {
        if (formBank[i] != 0) {
            formBank[i] += (int) formBank;
            fg = (PSFormGroup*) formBank[i];
            for (fi = 0; fi < fg->num; fi++) {
                if (fg->formTable[fi] != NULL) {
                    fg->formTable[fi] += (u32) formBank;
                }
            }
        }
    }
}

static inline void psInitDataBankLoad(int bank, const int* cmdBank, const int* texBank,
                                      u32* ref, const int* formBank)
{
    u16 version;

    if (formBank != NULL && *formBank != *texBank) {
        OSPanic("particle.c", 98, "illigal form data (strange number of group)\n");
    }

    ptclref[bank] = ref;
    psNumTexGroup[bank] = *texBank;
    psTexGroupArray[bank] = (PSTexGroup**) (texBank + 1);

    if (formBank != NULL) {
        psFormGroupArray[bank] = (PSFormGroup**) (formBank + 1);
    } else {
        psFormGroupArray[bank] = NULL;
    }

    version = *(u16*) cmdBank;
    switch (version) {
    case 0:
        psNumCmdList[bank] = cmdBank[1];
        psCmdListArray[bank] = (PSCmdList**) (cmdBank + 2);
        break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43: {
        s32 count = cmdBank[1];
        psNumCmdList[bank] = cmdBank[2] + count;
        psCmdListArray[bank] = (PSCmdList**) (cmdBank + 3 - count);
        break;
    }
    default:
        OSPanic("particle.c", 128, "psInitDataBanks: unknown version\n");
    }
}

void psInitDataBank(int bank, int* cmdBank, int* texBank, u32* ref, int* formBank)
{
    if (bank < 0x40) {
        psInitDataBankLocate(cmdBank, texBank, formBank);
        psInitDataBankLoad(bank, cmdBank, texBank, ref, formBank);
    }
}

void psInitParticle(int num)
{
    int i;

    _psLinkInit(num);
    numActiveParticles = 0;
    numPeakParticles = 0;

    for (i = 0; i < 64; i++) {
        psNumCmdList[i] = 0;
        psNumTexGroup[i] = 0;
        psCmdListArray[i] = NULL;
        psTexGroupArray[i] = NULL;
        psFormGroupArray[i] = NULL;
        ptclref[i] = NULL;
    }

    for (i = 0; i < 8; i++) {
        psPointJObj[i] = NULL;
    }
}

void psKillAllParticle(void);
static inline void psClearPointJObj(void);

void psRemoveParticle(void)
{
    int i;

    psKillAllParticle();
    psKillAllGenerator();
    _psListClear();

    for (i = 0; i < 64; i++) {
        psNumCmdList[i] = 0;
        psNumTexGroup[i] = 0;
        psCmdListArray[i] = NULL;
        psTexGroupArray[i] = NULL;
        psFormGroupArray[i] = NULL;
        ptclref[i] = NULL;
    }

    psClearPointJObj();
}

PSParticle* psGenerateParticle0(PSParticle** head, s32 linkNo, s32 bank, void* unused6, s32 unused7,
                                u32 kind, u16 texGroup, u8* cmdList, s32 life, f32 x, f32 y, f32 z,
                                f32 vx, f32 vy, f32 vz, f32 size, f32 grav, f32 fric, s32 palflag,
                                PSGenerator* gp, s32 flgInterpret)
{
    PSParticle* pp = _psListNew(head, linkNo);

    if (pp == NULL) {
        return NULL;
    }

    if (gp != NULL) {
        pp->familyId = gp->familyId;
    } else {
        pp->familyId = psGetNewIDNum();
    }

    pp->appSRT = NULL;
    if (gp != NULL && gp->appSRT != NULL) {
        psAttachParticleAppSRT(pp, gp->appSRT);
    }

    pp->bank = bank;
    pp->linkNo = linkNo;
    pp->kind = kind;
    pp->texGroup = texGroup;
    pp->pos[0] = x;
    pp->pos[1] = y;
    pp->pos[2] = z;
    pp->vel[0] = vx;
    pp->vel[1] = vy;
    pp->vel[2] = vz;
    pp->size = size;
    pp->grav = grav;
    pp->fric = fric;
    pp->life = life + 1;
    pp->cmdList = cmdList;
    pp->cmdMarkPtr = 0;
    pp->cmdPtr = 0;
    if (palflag) {
        pp->kind |= 0x10;
    }
    pp->cmdWait = cmdList != NULL;
    pp->poseNum = 0;
    pp->palNum = 0xFF;
    pp->primCol[3] = 0xFF;
    pp->primCol[2] = 0xFF;
    pp->primCol[1] = 0xFF;
    pp->primCol[0] = 0xFF;
    pp->envCol[3] = 0;
    pp->envCol[2] = 0;
    pp->envCol[1] = 0;
    pp->envCol[0] = 0;
    pp->envColCount = 0;
    pp->primColCount = 0;
    pp->sizeCount = 0;
    pp->envColRemain = 0;
    pp->primColRemain = 0;
    pp->aCmpMode = 0x33;
    if (((pp->kind >> 22) & 3) >= 2) {
        pp->aCmpParam1 = 0;
    } else {
        pp->aCmpParam1 = 1;
    }
    pp->aCmpParam2 = 0xFF;
    pp->aCmpRemain = 0;
    pp->aCmpCount = 0;
    pp->rotateCount = 0;
    pp->rotateTarget = 0.0f;
    pp->sizeTarget = 0.0f;
    pp->rotate = 0.0f;
    pp->owner = gp;
    if (gp != NULL) {
        gp->childCount++;
    }
    pp->pJObjOfs = 0;
    pp->matColRemain = 0;
    pp->matColCount = 0;
    pp->matRGB = 0xFF;
    pp->matA = 0xFF;
    pp->ambColRemain = 0;
    pp->ambColCount = 0;
    pp->ambRGB = 0xFF;
    pp->ambA = 0xFF;
    pp->trail = 1.0f;

    if (flgInterpret) {
        psInterpretParticle0(pp, NULL);
    }

    return pp;
}

PSParticle* psGenerateParticleID0(PSParticle** head, s32 linkNo, s32 bank, s32 id, s32 flgInterpret)
{
    PSCmdList* cmd;
    PSTexGroup* tex;
    s32 palflag;

    if (linkNo >= 8) {
        return NULL;
    }
    if (bank >= 0x40) {
        return NULL;
    }
    if (id >= psNumCmdList[bank]) {
        return NULL;
    }
    cmd = psCmdListArray[bank][id];
    if (cmd == NULL) {
        return NULL;
    }
    tex = psTexGroupArray[bank][cmd->texGroup];
    palflag = tex != NULL ? tex->palflag : 0;
    return psGenerateParticle0(head, linkNo, bank, tex, 0, cmd->kind, cmd->texGroup, cmd->cmdList,
                               cmd->life, 0.0f, 0.0f, 0.0f, cmd->vx, cmd->vy, cmd->vz, cmd->size,
                               cmd->grav, cmd->fric, palflag, NULL, flgInterpret);
}

PSParticle* psGenerateParticle(s32 linkNo, s32 bank, s32 a, u32 kind, u16 texGroup, u8* cmdList,
                               s32 life, s32 palflag, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz,
                               f32 size, f32 grav, f32 fric, PSGenerator* gp)
{
    return psGenerateParticle0(NULL, linkNo, bank, (void*) kind, a, kind, texGroup, cmdList, life, x,
                               y, z, vx, vy, vz, size, grav, fric, palflag, gp, 1);
}

void psKillAllParticle(void)
{
    PSParticle* pp;
    int i;

    for (i = 0; i < 16; i++) {
        pp = _psListGetFirst(i);
        while (pp != NULL) {
            pp = psKillParticle(pp);
        }
    }
}

static inline void psClearPointJObj(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (psPointJObj[i] != NULL) {
            HSD_JObjUnref(psPointJObj[i]);
            psPointJObj[i] = NULL;
        }
    }
}

void psSetPointJObj(s32 index, void* jobj)
{
    void** slot;
    s32 i;

    if (index < 0 || index > 8) {
        return;
    }

    if (index != 0) {
        void* oldJObj;

        slot = psPointJObj;
        slot += index;
        oldJObj = *--slot;
        if (oldJObj == jobj) {
            return;
        }
        if (oldJObj != NULL) {
            HSD_JObjUnref(oldJObj);
        }
        *slot = jobj;

        if (jobj != NULL) {
            u16* refCount = (u16*) ((u8*) jobj + 4);

            (*refCount)++;
            if (*refCount == 0xFFFF) {
                __assert("object.h", 0x5D, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
            }
        }
    } else {
        slot = psPointJObj;
        i = 0;
        while (i < 8) {
            if (*slot == jobj) {
                HSD_JObjUnref(*slot);
                *slot = NULL;
            }
            i++;
            slot++;
        }
    }
}

void psSetPointJObjNodup(void* jobj, s32 index)
{
    void** slot;
    s32 i;

    if (index < 0 || index > 8) {
        return;
    }

    i = 0;
    do {
        if (psPointJObj[i] == jobj) {
            HSD_JObjUnref(psPointJObj[i]);
            psPointJObj[i] = NULL;
        }
        i++;
    } while (i < 8);

    if (index != 0) {
        void* oldJObj;

        slot = psPointJObj;
        slot += index;
        oldJObj = *--slot;
        if (oldJObj != NULL) {
            HSD_JObjUnref(oldJObj);
        }
        *slot = jobj;

        if (jobj != NULL) {
            u16* refCount = (u16*) ((u8*) jobj + 4);

            (*refCount)++;
            if (*refCount == 0xFFFF) {
                __assert("object.h", 0x5D, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
            }
        }
    }
}

void psDeletePntJObjwithParticle(PSParticle* pp)
{
    if (pp->kind & PS_FLAG_POINT_JOBJ) {
        u32 slotIdx = (pp->kind >> 12) & 0x7;
        void* jobj = psPointJObj[slotIdx];

        if (jobj != NULL) {
            HSD_JObjUnref(jobj);
            psPointJObj[slotIdx] = NULL;
        }
    }
}

void psKillFamily(s32 familyId, s32 linkNo)
{
    PSParticle* next;
    PSParticle* parent = NULL;
    PSParticle* pp;

    pp = _psListGetFirst(linkNo);

    while (pp != NULL) {
        next = pp->next;

        if (pp->familyId == (u16) familyId) {
            if (pp->owner != NULL) {
                pp->owner->childCount--;
            }
            if (pp->appSRT != NULL) {
                psRemoveParticleAppSRT(pp);
            }
            if (pp->kind & PS_FLAG_POINT_JOBJ) {
                u32 slotIdx = (pp->kind >> 12) & 0x7;
                void* jobj = psPointJObj[slotIdx];

                if (jobj != NULL) {
                    HSD_JObjUnref(jobj);
                    psPointJObj[slotIdx] = NULL;
                }
            }
            _psListDelete(pp, parent);
        } else {
            parent = pp;
        }
        pp = next;
    }

    psKillGeneratorID(familyId);
}

void psKillGeneratorChild(PSGenerator* gen)
{
    PSParticle* next;
    PSParticle* parent = NULL;
    PSParticle* pp;
    u16 familyId = gen->familyId;

    pp = _psListGetFirst(gen->linkNo);

    while (pp != NULL) {
        next = pp->next;

        if (pp->familyId == familyId && pp->owner != NULL && pp->owner == gen) {
            if (pp->owner != NULL) {
                pp->owner->childCount--;
            }
            if (pp->appSRT != NULL) {
                psRemoveParticleAppSRT(pp);
            }
            if (pp->kind & PS_FLAG_POINT_JOBJ) {
                u32 slotIdx = (pp->kind >> 12) & 0x7;
                void* jobj = psPointJObj[slotIdx];

                if (jobj != NULL) {
                    HSD_JObjUnref(jobj);
                    psPointJObj[slotIdx] = NULL;
                }
            }
            _psListDelete(pp, parent);
        } else {
            parent = pp;
        }
        pp = next;
    }
}

u32 psGetGeneratorChildMaxLife(PSGenerator* gen)
{
    u32 maxLife = gen->maxLife;
    PSGenerator* child = activeGenerator;

    while (child != NULL) {
        if (child->familyId == gen->familyId && child->maxLife > maxLife) {
            maxLife = child->maxLife;
        }
        child = child->next;
    }

    return maxLife;
}

u32 psGetParticleChildCount(PSGenerator* gen)
{
    u32 count = 0;
    PSGenerator* child = activeGenerator;

    while (child != NULL) {
        if (child->familyId == gen->familyId) {
            count += child->childCount;
        }
        child = child->next;
    }

    return count;
}

void psLinkChildGensToJObj(PSGenerator* gen, void* jobj)
{
    gen->generatorFlags |= 0x1;
    gen->linkedJObj = jobj;
}

void psUnlinkChildGensFromJObj(PSGenerator* gen)
{
    gen->generatorFlags = (u16) (gen->generatorFlags & ~0x1);
}

void psSetVelocityRotationInLocal(PSGenerator* gen, u8 enabled)
{
    if (enabled) {
        gen->generatorFlags |= 0x4;
    } else {
        gen->generatorFlags = (u16) (gen->generatorFlags & ~0x4);
    }
}

void psSetOffsetRotationInLocal(PSGenerator* gen, u8 enabledA, u8 enabledB)
{
    if (enabledA) {
        gen->generatorFlags |= 0x8;
        if (enabledB) {
            gen->generatorFlags |= 0x10;
        } else {
            gen->generatorFlags = (u16) (gen->generatorFlags & ~0x10);
        }
    } else {
        gen->generatorFlags = (u16) (gen->generatorFlags & ~0x8);
        gen->generatorFlags = (u16) (gen->generatorFlags & ~0x10);
    }
}

void psSetParticleTexScaling(PSGenerator* gen, u8 enabled)
{
    if (enabled) {
        gen->generatorFlags |= 0x20;
    } else {
        gen->generatorFlags = (u16) (gen->generatorFlags & ~0x20);
    }
}

void psSetTornadoScaling(PSGenerator* gen, u8 enabledA, u8 enabledB)
{
    if (enabledA) {
        gen->generatorFlags |= 0x40;
    } else {
        gen->generatorFlags = (u16) (gen->generatorFlags & ~0x40);
    }

    if (enabledB) {
        gen->generatorFlags |= 0x80;
    } else {
        gen->generatorFlags = (u16) (gen->generatorFlags & ~0x80);
    }
}

void psSetNodeScaling(PSGenerator* gen, u8 enabled)
{
    if (enabled) {
        gen->generatorFlags |= 0x100;
    } else {
        gen->generatorFlags = (u16) (gen->generatorFlags & ~0x100);
    }
}

void psSetRandomVelocityScaling(PSGenerator* gen, u8 enabled)
{
    if (enabled) {
        gen->generatorFlags |= 0x200;
    } else {
        gen->generatorFlags = (u16) (gen->generatorFlags & ~0x200);
    }
}

void psSetGeneratorAngleRadiusScale(PSGenerator* gen, f32* scale, u8 scaleMotion)
{
    f32 avg = (scale[0] + scale[1] + scale[2]) / 3.0f;
    int bank = gen->bank;
    int index = gen->index;

    switch (gen->angleFlags & 0xF) {
    case 0:
    case 3:
    case 4:
        gen->shape[0] = avg * psCmdListArray[bank][index]->param1;
        gen->shape[1] = avg * psCmdListArray[bank][index]->param2;
        break;
    case 1:
        gen->shape[0] = scale[0] * psCmdListArray[bank][index]->param1;
        gen->shape[1] = scale[1] * psCmdListArray[bank][index]->param2;
        gen->shape[2] = scale[2] * psCmdListArray[bank][index]->param3;
        break;
    case 6:
    case 7:
        gen->shape[0] = avg * psCmdListArray[bank][index]->param1;
        gen->shape[1] = avg * psCmdListArray[bank][index]->param2;
        gen->shape[2] = avg * psCmdListArray[bank][index]->param3;
        break;
    case 5: {
        f32 v;
        v = scale[0] * psCmdListArray[bank][index]->param1;
        gen->shape[0] = v;
        gen->shape[3] = v;
        v = scale[1] * psCmdListArray[bank][index]->param2;
        gen->shape[1] = v;
        gen->shape[7] = v;
        v = scale[2] * psCmdListArray[bank][index]->param3;
        gen->shape[2] = v;
        gen->shape[11] = v;
        break;
    }
    case 8:
        gen->shape[2] = avg * psCmdListArray[bank][index]->param1;
        gen->shape[4] = avg * psCmdListArray[bank][index]->param2;
        break;
    }

    gen->radius = avg * psCmdListArray[bank][index]->radius;
    if (scaleMotion == 1) {
        gen->gravity = gen->gravity * avg;
        gen->friction = gen->friction * avg;
        gen->generatorFlags |= 0x1000;
    }
    gen->angleRadiusScale[0] = scale[0];
    gen->angleRadiusScale[1] = scale[1];
    gen->angleRadiusScale[2] = scale[2];
}

void psSetParticleVisibility(PSGenerator* gen, u8 visible)
{
    PSParticle* pp;
    PSGenerator* g;

    for (pp = _psListGetFirst(gen->linkNo); pp != NULL; pp = pp->next) {
        if (pp->familyId == gen->familyId) {
            if (visible) {
                pp->kind &= ~PS_FLAG_HIDDEN;
            } else {
                pp->kind |= PS_FLAG_HIDDEN;
            }
        }
    }

    for (g = activeGenerator; g != NULL; g = g->next) {
        if (g->familyId == gen->familyId) {
            if (visible) {
                g->flags &= ~PS_FLAG_HIDDEN;
            } else {
                g->flags |= PS_FLAG_HIDDEN;
            }
        }
    }
}

void psSetToken(u16 token)
{
    g_ps_token = token;
}
