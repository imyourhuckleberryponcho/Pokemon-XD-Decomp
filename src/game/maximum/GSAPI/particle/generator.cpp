// STATUS: 12/13 functions exact, LAYOUT/CONST/CALLS/DATA OK. generateParticle 99.45%: only float register
// allocation differs (scaleX/Y/Z, velMag, angle3 land in f27..f24 instead of f26/f29/f28/f27/f23). Needs
// extra_cflags=["-lang=c", "-inline deferred", "-i include/hsd_ref", "-i include/libc"] (already set).
// Particle generators (XD's older design: own active/free/standby lists). Compiled as C with
// deferred inlining: functions come out in reverse source order.
#define HSD_FILE_NAME "generator.c"

#include <dolphin/types.h>

/* XD's MSL <math.h> inlines (sqrtf with its NaN checks), not include/libc's. */
#define _MATH_H_
extern f32 __float_nan[];
extern f32 __float_min[];
#define NAN (__float_nan[0])
double sin(double x);
double cos(double x);
double tan(double x);
double atan2(double y, double x);
double __fabs(double x);
#define fabs(x) __fabs(x)

inline int __fpclassifyf(float x)
{
    switch ((*(s32*) &x) & 0x7F800000) {
    case 0x7F800000:
        if ((*(s32*) &x) & 0x007FFFFF) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(s32*) &x) & 0x007FFFFF) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

inline float sqrtf(float x)
{
    if (x > 0.0f) {
        double guess = __frsqrte((double) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (float) (x * guess);
    } else if (x < 0.0) {
        return NAN;
    } else if (__fpclassifyf(x) == 1) {
        return NAN;
    }
    return x;
}

inline float atan2fInline(float y, float x)
{
    float r = (float) atan2(y, x);
    return r;
}

#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/object.h>
#include <sysdolphin/baselib/wobj.h>
#include <sysdolphin/baselib/psappsrt.h>
#include <sysdolphin/baselib/psstructs.h>
#include <sysdolphin/baselib/random.h>
#include <string.h>

#pragma pool_strings off

void* HSD_Alloc(u32 size);
void HSD_Free(void* ptr);
void psRemoveGeneratorAppSRT(HSD_Generator* gp);
extern int __float_epsilon[];
#undef FLT_EPSILON
#define FLT_EPSILON (*(f32*) __float_epsilon)
#undef FLT_MIN
#define FLT_MIN (__float_min[0])

extern s32 psNumCmdList[64];
extern HSD_PSCmdList** psCmdListArray[64];
extern HSD_PSTexGroup** psTexGroupArray[64];
void psKillAllGenerator(void);
void psKillGenerator(HSD_Generator* gp);

static u16 psIDNum = 0x100;

static void (*psExtExecGenFunc)(HSD_Generator*, Mtx);
static void (*psExtCreateGenFunc)(HSD_Generator*);
static HSD_CObj* psCamera;
HSD_Generator* freeGenerator;
HSD_Generator* activeGenerator;
HSD_Generator* lastGP;
static HSD_SList* standbyGenerator;
extern u16 numActiveGenerators;
extern u16 numPeakGenerators;

u16 psGetNewIDNum(void)
{
    psIDNum++;
    if (psIDNum < 0x100) {
        psIDNum = 0x100;
    }
    return psIDNum;
}

void genPosUpdate(HSD_Generator* gp)
{
    HSD_JObj* jobj;
    if (gp != NULL && !(gp->flags & 2) && (gp->flags & 1)) {
        jobj = gp->jobj;
        if (jobj != NULL) {
            HSD_JObjSetupMatrix(jobj);
            gp->pos.x = gp->jobj->mtx[0][3];
            gp->pos.y = gp->jobj->mtx[1][3];
            gp->pos.z = gp->jobj->mtx[2][3];
        }
    }
}

void psInitGenerator(int num)
{
    HSD_Generator* gp;
    int i;
    activeGenerator = NULL;
    freeGenerator = NULL;
    for (i = num - 1; i >= 0; i--) {
        gp = HSD_Alloc(sizeof(HSD_Generator));
        memset(gp, 0, sizeof(HSD_Generator));
        if (gp == NULL) {
            return;
        }
        gp->next = freeGenerator;
        freeGenerator = gp;
    }
    numActiveGenerators = 0;
    numPeakGenerators = 0;
    standbyGenerator = NULL;
    psCamera = NULL;
    psExtExecGenFunc = NULL;
    psExtCreateGenFunc = NULL;
    lastGP = NULL;
}

static inline void cobjUnref(HSD_CObj* cobj)
{
    if (cobj != NULL && ref_DEC(cobj)) {
        if (cobj != NULL) {
            HSD_OBJECT_METHOD(cobj)->release((HSD_Class*) cobj);
            HSD_OBJECT_METHOD(cobj)->destroy((HSD_Class*) cobj);
        }
    }
}

static inline HSD_Generator* killGenerator(HSD_Generator* gp)
{
    HSD_psAppSRT* srt;
    HSD_Generator* prev = lastGP;
    if (gp->type & 0x80) {
        psKillGeneratorChild(gp);
    }
    if (gp->numChild != 0) {
        gp->random = 0.0F;
        gp->genLife = 1;
        return gp;
    }
    if (gp->type & 0x3800) {
        srt = gp->appsrt;
        if (srt != NULL && srt->gp == gp && srt->usedCount != 1) {
            gp->random = 0.0F;
            gp->genLife = 1;
            return gp;
        }
    }
    if (prev == NULL) {
        activeGenerator = gp->next;
    } else {
        prev->next = gp->next;
    }
    if (gp->appsrt != NULL) {
        psRemoveGeneratorAppSRT(gp);
    }
    gp->next = freeGenerator;
    freeGenerator = gp;
    numActiveGenerators--;
    return prev;
}

void psRemoveGenerator(void)
{
    HSD_Generator* next;
    HSD_Generator* gp;
    psKillAllParticle();
    psKillAllGenerator();
    for (gp = freeGenerator; gp != NULL; gp = next) {
        next = gp->next;
        HSD_Free(gp);
    }
    freeGenerator = NULL;
    if (psCamera != NULL) {
        if (psCamera != NULL) {
            cobjUnref(psCamera);
        }
        psCamera = NULL;
    }
}

void psKillGenerator(HSD_Generator* gp)
{
    HSD_Generator* cur;
    cur = activeGenerator;
    lastGP = NULL;
    while (cur != NULL) {
        if (cur == gp) {
            lastGP = killGenerator(gp);
            if (lastGP != NULL) {
                while (lastGP->next != NULL) {
                    lastGP = lastGP->next;
                }
            } else if (activeGenerator != NULL) {
                lastGP = activeGenerator;
                while (lastGP->next != NULL) {
                    lastGP = lastGP->next;
                }
            }
            return;
        }
        lastGP = cur;
        cur = cur->next;
    }
}

void psKillGeneratorID(u16 idnum)
{
    HSD_Generator* gp;
    HSD_Generator* next;
    gp = activeGenerator;
    lastGP = NULL;
    while (gp != NULL) {
        next = gp->next;
        if (gp->idnum == idnum) {
            lastGP = killGenerator(gp);
        } else {
            lastGP = gp;
        }
        gp = next;
    }
}

void psKillAllGenerator(void)
{
    HSD_Generator* gp;
    HSD_Generator* next;
    for (gp = activeGenerator; gp != NULL; gp = next) {
        next = gp->next;
        psKillGenerator(gp);
    }
    while (standbyGenerator != NULL) {
        standbyGenerator = HSD_SListRemove(standbyGenerator);
    }
}


static inline f32 homeValue(f32 value)
{
    return value;
}

static f32 generateParticle(HSD_Generator* gp)
{
    Mtx rotMtx;
    Mtx mtxX;
    Mtx mtxY;
    Mtx mtxZ;
    Mtx trigMtx;
    Vec3 velCopy;
    Vec3 emitPos;
    Vec3 tmpvec;
    Vec3 vec;
    Vec3 lookDir;
    Vec3 camUp;
    Vec3 cross1;
    Vec3 velNorm;
    f32 scaleX;
    f32 scaleY;
    f32 scaleZ;
    f64 eps;
    f32 velMag;
    f32 angle1;
    f32 sinAz;
    f32 cosAz;
    f32 elevation;
    f32 angle3;
    f32 curAngle;
    f32 coneAngle;
    f32 sinEl;
    f32 radius;
    f32 angleStep;
    f32 tmp;

    angle3 = angle1 = 0.0F;
    if (gp->count < 1.0F) {
        return gp->count;
    }

    velCopy.x = gp->vel.x;
    velCopy.y = gp->vel.y;
    velCopy.z = gp->vel.z;
    scaleX = gp->scale.x;
    scaleY = gp->scale.y;
    scaleZ = gp->scale.z;
    if ((gp->type & 0xF) == 2 && (gp->flags & 0x80)) {
        velCopy.x *= scaleX;
        velCopy.y *= scaleY;
        velCopy.z *= scaleZ;
    }

    velMag = sqrtf(velCopy.z * velCopy.z + (velCopy.x * velCopy.x + velCopy.y * velCopy.y));

    PSMTXIdentity(rotMtx);

    if (!(gp->kind & 0x30000)) {
        PSMTXRotRad(mtxX, 'X', gp->rot.x);
        PSMTXRotRad(mtxY, 'Y', gp->rot.y);
        PSMTXRotRad(mtxZ, 'Z', gp->rot.z);
        PSMTXConcat(mtxY, mtxX, mtxX);
        PSMTXConcat(mtxZ, mtxX, mtxX);

        vec.x = mtxX[0][0];
        vec.y = mtxX[1][0];
        vec.z = mtxX[2][0];
        PSVECNormalize(&vec, &vec);
        rotMtx[0][0] = vec.x;
        rotMtx[1][0] = vec.y;
        rotMtx[2][0] = vec.z;

        vec.x = mtxX[0][1];
        vec.y = mtxX[1][1];
        vec.z = mtxX[2][1];
        PSVECNormalize(&vec, &vec);
        rotMtx[0][1] = vec.x;
        rotMtx[1][1] = vec.y;
        rotMtx[2][1] = vec.z;

        vec.x = mtxX[0][2];
        vec.y = mtxX[1][2];
        vec.z = mtxX[2][2];
        PSVECNormalize(&vec, &vec);
        rotMtx[0][2] = vec.x;
        rotMtx[1][2] = vec.y;
        rotMtx[2][2] = vec.z;

        rotMtx[2][3] = 0.0F;
        rotMtx[1][3] = 0.0F;
        rotMtx[0][3] = 0.0F;
    }

    if (gp->kind & 0x10000) {
        if (psCamera == NULL) {
            __assert("generator.c", 626, "psCamera");
        }
        lookDir.x = psCamera->eyepos->pos.x - gp->pos.x;
        lookDir.y = psCamera->eyepos->pos.y - gp->pos.y;
        lookDir.z = psCamera->eyepos->pos.z - gp->pos.z;
        PSVECNormalize(&lookDir, &lookDir);
        HSD_CObjGetUpVector(psCamera, &camUp);
        PSVECNormalize(&camUp, &camUp);
        PSVECCrossProduct(&camUp, &lookDir, &cross1);
        PSVECCrossProduct(&lookDir, &cross1, &camUp);

        rotMtx[0][0] = cross1.x;
        rotMtx[1][0] = cross1.y;
        rotMtx[2][0] = cross1.z;
        rotMtx[0][1] = camUp.x;
        rotMtx[1][1] = camUp.y;
        rotMtx[2][1] = camUp.z;
        rotMtx[0][2] = lookDir.x;
        rotMtx[1][2] = lookDir.y;
        rotMtx[2][2] = lookDir.z;
    }

    if ((gp->type & 0xF) != 1 && velMag > FLT_EPSILON) {
        velNorm.x = gp->vel.x;
        velNorm.y = gp->vel.y;
        velNorm.z = gp->vel.z;
        PSVECNormalize(&velNorm, &velNorm);

        if (fabs(velNorm.z) < FLT_MIN) {
            if (velNorm.y >= 0.0F) {
                sinAz = 1.5707964F;
            } else {
                sinAz = -1.5707964F;
            }
        } else {
            sinAz = atan2fInline(velNorm.y, velNorm.z);
        }
        cosAz = (f32) sin(sinAz);
        sinAz = (f32) cos(sinAz);

        {
            f32 projectedZ = velNorm.y * cosAz + velNorm.z * sinAz;
            if (fabs(projectedZ) < FLT_MIN) {
                if (velNorm.x >= 0.0F) {
                    elevation = 1.5707964F;
                } else {
                    elevation = -1.5707964F;
                }
            } else {
                elevation = atan2fInline(velNorm.x, projectedZ);
            }
        }
        sinEl = (f32) sin(elevation);
        {
            f32 cosEl = (f32) cos(elevation);
            f32 negCosAz = -cosAz;

            trigMtx[0][0] = cosEl;
            trigMtx[0][1] = 0.0F;
            trigMtx[0][2] = sinEl;
            trigMtx[0][3] = 0.0F;
            trigMtx[1][0] = negCosAz * sinEl;
            trigMtx[1][1] = sinAz;
            trigMtx[1][2] = cosAz * cosEl;
            trigMtx[1][3] = 0.0F;
            trigMtx[2][0] = -sinAz * sinEl;
            trigMtx[2][1] = negCosAz;
            trigMtx[2][2] = sinAz * cosEl;
            trigMtx[2][3] = 0.0F;
        }
        PSMTXConcat(rotMtx, trigMtx, rotMtx);
    }
    elevation = velMag;

    if ((gp->type & 0xF) == 2) {
        if (fabs(rotMtx[2][2]) < FLT_MIN) {
            if (rotMtx[1][2] >= 0.0F) {
                angle1 = 1.5707964F;
            } else {
                angle1 = -1.5707964F;
            }
        } else {
            angle1 = atan2fInline(rotMtx[1][2], rotMtx[2][2]);
        }
        {
            f32 c1 = (f32) cos(angle1);
            f32 s1 = (f32) sin(angle1);
            f32 comb = rotMtx[1][2] * s1 + rotMtx[2][2] * c1;
            if (fabs(comb) < FLT_MIN) {
                if (rotMtx[0][2] >= 0.0F) {
                    angle3 = 1.5707964F;
                } else {
                    angle3 = -1.5707964F;
                }
            } else {
                angle3 = atan2fInline(rotMtx[0][2], comb);
            }
        }
    }

    if (gp->angle < 0.0F) {
        switch (gp->type & 0xF) {
        case 0:
        case 3:
        case 4: {
            f32 minA = gp->aux.disc.minAngle;
            f32 rnd = HSD_Randf();
            f32 step = (gp->aux.disc.maxAngle - minA) / (f32) (s32) gp->count;
            angleStep = step;
            curAngle = step * rnd + minA;
            break;
        }
        case 6:
        case 7: {
            f32 minA = gp->aux.cone.minAngle;
            f32 rnd = HSD_Randf();
            f32 step = (gp->aux.cone.maxAngle - minA) / (f32) (s32) gp->count;
            angleStep = step;
            curAngle = step * rnd + minA;
            break;
        }
        default: {
            f32 rnd = HSD_Randf();
            curAngle = (f32) ((eps = M_PI * (f64) homeValue(rnd)) * 2.0);
            angleStep = (f32) ((2.0 * M_PI) / (f64) (s32) gp->count);
            break;
        }
        }
    }

    eps = 0.001F;
    while (gp->count >= 1.0F) {
        switch (gp->type & 0xF) {
        case 0:
        case 3:
        case 4:
        case 6:
        case 7: {
            if (gp->radius < 0.0F) {
                sinAz = -gp->radius;
                radius = 1.0F;
            } else {
                radius = HSD_Randf();
                if ((gp->type & 0xF) == 3 || (gp->type & 0xF) == 4) {
                    radius = sqrtf(radius);
                }
                sinAz = radius * gp->radius;
            }

            switch (gp->type & 0xF) {
            case 6:
                if (gp->angle < 0.0F) {
                    tmp = curAngle + angleStep;
                    curAngle = tmp;
                    if (fabs(sinAz) < FLT_MIN) {
                        if (gp->aux.cone.height >= 0.0F) {
                            coneAngle = -gp->angle;
                        } else {
                            coneAngle = (f32) (M_PI - gp->angle);
                        }
                    } else {
                        coneAngle = (f32) (M_PI_2 - atan2fInline(gp->aux.cone.height, sinAz) - gp->angle);
                    }
                } else {
                    {
                        f32 minAngle = gp->aux.cone.minAngle;
                        curAngle = minAngle;
                    }
                    {
                        f32 rnd = HSD_Randf();
                        coneAngle = gp->aux.cone.maxAngle - curAngle;
                        curAngle = coneAngle * rnd + curAngle;
                        coneAngle = radius * gp->angle;
                    }
                    if (fabs(sinAz) < FLT_MIN) {
                        if (gp->aux.cone.height >= 0.0F) {
                            coneAngle = gp->angle;
                        } else {
                            coneAngle = (f32) (M_PI + gp->angle);
                        }
                    } else {
                        coneAngle = (f32) (gp->angle + (M_PI_2 - atan2fInline(gp->aux.cone.height, sinAz)));
                    }
                }
                break;
            case 7:
                if (gp->angle < 0.0F) {
                    coneAngle = (f32) (M_PI_2 - gp->angle);
                    tmp = curAngle + angleStep;
                    curAngle = tmp;
                } else {
                    {
                        f32 minAngle = gp->aux.disc.minAngle;
                        curAngle = minAngle;
                    }
                    {
                        f32 rnd = HSD_Randf();
                        coneAngle = gp->aux.disc.maxAngle - curAngle;
                        curAngle = coneAngle * rnd + curAngle;
                        coneAngle = (f32) (M_PI_2 + gp->angle);
                    }
                }
                break;
            default:
                if (gp->angle < 0.0F) {
                    coneAngle = -gp->angle;
                    curAngle += angleStep;
                    coneAngle = radius * coneAngle;
                } else {
                    curAngle = gp->aux.disc.minAngle;
                    {
                        f32 rnd = HSD_Randf();
                        coneAngle = radius * gp->angle;
                        sinEl = gp->aux.disc.maxAngle - curAngle;
                        curAngle = sinEl * rnd + curAngle;
                    }
                }
                break;
            }

            cosAz = curAngle;
            emitPos.x = sinAz * (f32) cos(cosAz);
            emitPos.y = sinAz * (f32) sin(cosAz);

            if ((gp->type & 0xF) == 6 || (gp->type & 0xF) == 7) {
                emitPos.z = HSD_Randf();
                if ((gp->type & 0xF) == 6) {
                    emitPos.x *= (1.0F - emitPos.z);
                    emitPos.y *= (1.0F - emitPos.z);
                }
                emitPos.z *= gp->aux.cone.height;
            } else {
                emitPos.z = 0.0F;
            }

            {
                f32 sinCa = elevation * (f32) sin(coneAngle);
                vec.x = sinCa * (f32) cos(cosAz);
                vec.y = sinCa * (f32) sin(cosAz);
                vec.z = elevation * (f32) cos(coneAngle);
            }

            if ((gp->type & 0xF) == 3) {
                vec.x *= radius;
                vec.y *= radius;
                vec.z *= radius;
            }

            PSMTXMultVec(rotMtx, &emitPos, &emitPos);
            emitPos.x += gp->pos.x;
            emitPos.y += gp->pos.y;
            emitPos.z += gp->pos.z;

            PSMTXMultVec(rotMtx, &vec, &vec);

            curAngle = cosAz;
            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind, gp->texGroup, gp->cmdList, gp->life, 0, emitPos.x,
                               emitPos.y, emitPos.z, vec.x * scaleX, vec.y * scaleY, vec.z * scaleZ, gp->size, gp->grav, gp->fric, gp);
            break;
        }

        case 1: {
            f32 rnd = HSD_Randf();
            emitPos.x = rnd * gp->aux.line.x2;
            emitPos.y = rnd * gp->aux.line.y2;
            emitPos.z = rnd * gp->aux.line.z2;

            PSMTXMultVec(rotMtx, &emitPos, &emitPos);
            emitPos.x += gp->pos.x;
            emitPos.y += gp->pos.y;
            emitPos.z += gp->pos.z;

            PSMTXMultVec(rotMtx, &velCopy, &vec);

            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind, gp->texGroup, gp->cmdList, gp->life, 0, emitPos.x,
                               emitPos.y, emitPos.z, vec.x * scaleX, vec.y * scaleY, vec.z * scaleZ, gp->size, gp->grav, gp->fric, gp);
            break;
        }

        case 2: {
            if (gp->radius < 0.0F) {
                sinAz = 1.0F;
            } else {
                sinAz = HSD_Randf();
            }
            if (gp->angle < 0.0F) {
                curAngle += angleStep;
            } else {
                f32 rnd = HSD_Randf();
                curAngle = (f32) (2.0 * (M_PI * (f64) homeValue(rnd)));
            }
            gp->aux.line.x2 = elevation;
            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind | 4, gp->texGroup, gp->cmdList, gp->life, 0, 0.0F,
                               0.0F, 0.0F, curAngle, sinAz, 0.0F, gp->size, angle1, angle3, gp);
            break;
        }

        case 5: {
            emitPos.x = HSD_Randf();
            emitPos.y = HSD_Randf();
            emitPos.z = HSD_Randf();

            switch (gp->aux.rect.flag) {
            case 0:
                break;
            case 1:
                emitPos.x = emitPos.x > 0.5F ? 1.0F : 0.0F;
                break;
            case 2:
                emitPos.y = emitPos.y > 0.5F ? 1.0F : 0.0F;
                break;
            case 3: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->aux.rect.x;
                if (rnd > a2 / (a2 + gp->aux.rect.y)) {
                    emitPos.y = emitPos.y > 0.5F ? 1.0F : 0.0F;
                } else {
                    emitPos.x = emitPos.x > 0.5F ? 1.0F : 0.0F;
                }
                break;
            }
            case 4:
                emitPos.z = emitPos.z > 0.5F ? 1.0F : 0.0F;
                break;
            case 5: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->aux.rect.x;
                if (rnd > a2 / (a2 + gp->aux.rect.z)) {
                    emitPos.z = emitPos.z > 0.5F ? 1.0F : 0.0F;
                } else {
                    emitPos.x = emitPos.x > 0.5F ? 1.0F : 0.0F;
                }
                break;
            }
            case 6: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->aux.rect.y;
                if (rnd > a2 / (a2 + gp->aux.rect.z)) {
                    emitPos.z = emitPos.z > 0.5F ? 1.0F : 0.0F;
                } else {
                    emitPos.y = emitPos.y > 0.5F ? 1.0F : 0.0F;
                }
                break;
            }
            case 7: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->aux.rect.z;
                f32 b2 = gp->aux.rect.y;
                f32 c2 = gp->aux.rect.x;
                f32 r0 = 1.0F / (c2 * (b2 + a2) + b2 * a2);
                if (rnd < r0 * (c2 * b2)) {
                    emitPos.z = emitPos.z > 0.5F ? 1.0F : 0.0F;
                } else {
                    if (rnd > 1.0F - r0 * (c2 * a2)) {
                        emitPos.y = emitPos.y > 0.5F ? 1.0F : 0.0F;
                    } else {
                        emitPos.x = emitPos.x > 0.5F ? 1.0F : 0.0F;
                    }
                }
                break;
            }
            default:
                break;
            }

            emitPos.x -= 0.5F;
            emitPos.y -= 0.5F;
            emitPos.z -= 0.5F;

            tmpvec.x = gp->aux.rect.xx * emitPos.x + gp->aux.rect.yx * emitPos.y + gp->aux.rect.zx * emitPos.z;
            tmpvec.y = gp->aux.rect.xy * emitPos.x + gp->aux.rect.yy * emitPos.y + gp->aux.rect.zy * emitPos.z;
            tmpvec.z = gp->aux.rect.xz * emitPos.x + gp->aux.rect.yz * emitPos.y + gp->aux.rect.zz * emitPos.z;

            PSMTXMultVec(rotMtx, &tmpvec, &emitPos);
            emitPos.x += gp->pos.x;
            emitPos.y += gp->pos.y;
            emitPos.z += gp->pos.z;

            {
                f32 scale = elevation / sqrtf(gp->aux.rect.zx * gp->aux.rect.zx + gp->aux.rect.zy * gp->aux.rect.zy +
                                              gp->aux.rect.zz * gp->aux.rect.zz);
                vec.x = gp->aux.rect.zx * scale;
                vec.y = gp->aux.rect.zy * scale;
                vec.z = gp->aux.rect.zz * scale;
            }

            PSMTXMultVec(rotMtx, &vec, &vec);

            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind, gp->texGroup, gp->cmdList, gp->life, 0, emitPos.x,
                               emitPos.y, emitPos.z, vec.x * scaleX, vec.y * scaleY, vec.z * scaleZ, gp->size, gp->grav, gp->fric, gp);
            break;
        }

        case 8: {
            f32 r2;
            if (0.0F == gp->aux.cone.height) {
                tmp = (f32) (M_PI * (f64) HSD_Randf());
            } else {
                tmp = HSD_Randf() * gp->aux.cone.height;
            }
            radius = tmp;
            coneAngle = (f32) (2.0 * (M_PI * (f64) homeValue(HSD_Randf())));
            r2 = gp->radius;
            if (r2 < 0.0F) {
                sinAz = -r2;
            } else {
                sinAz = r2 * HSD_Randf();
            }
            vec.x = (f32) sin(radius) * (f32) cos(coneAngle);
            vec.y = (f32) sin(radius) * (f32) sin(coneAngle);
            vec.z = (f32) cos(radius);

            PSMTXMultVec(rotMtx, &vec, &emitPos);

            vec.x = emitPos.x * gp->aux.sphere.speed;
            vec.y = emitPos.y * gp->aux.sphere.speed;
            vec.z = emitPos.z * gp->aux.sphere.speed;

            if (gp->radius >= 0.0F && gp->aux.sphere.speed < 0.0F) {
                f32 scale = sinAz / gp->radius;
                vec.x *= scale;
                vec.y *= scale;
                vec.z *= scale;
            }

            emitPos.x = sinAz * emitPos.x + gp->pos.x;
            emitPos.y = sinAz * emitPos.y + gp->pos.y;
            emitPos.z = sinAz * emitPos.z + gp->pos.z;

            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind, gp->texGroup, gp->cmdList, gp->life, 0, emitPos.x,
                               emitPos.y, emitPos.z, vec.x * scaleX, vec.y * scaleY, vec.z * scaleZ, gp->size, gp->grav, gp->fric, gp);
            break;
        }

        default:
            if (psExtExecGenFunc != NULL) {
                psExtExecGenFunc(gp, rotMtx);
            }
            break;
        }

        gp->count -= 1.0F;
    }

    return gp->count;
}

void psExecGenerator(int mask)
{
    HSD_Generator* gp;
    while (standbyGenerator != NULL) {
        standbyGenerator = HSD_SListRemove(standbyGenerator);
    }
    gp = activeGenerator;
    lastGP = NULL;
    while (gp != NULL) {
        if (mask & (1 << (gp->linkNo + 16))) {
            lastGP = gp;
            gp = gp->next;
        } else if (gp->kind & 0x800) {
            lastGP = gp;
            gp = gp->next;
        } else {
            genPosUpdate(gp);
            if (gp->random < 0.0F) {
                gp->count = gp->count - gp->random;
            } else {
                gp->count = gp->random * HSD_Randf() + gp->count;
            }
            if (gp->count >= 1.0F) {
                gp->count = generateParticle(gp);
            }
            if (gp->genLife != 0 && --gp->genLife == 0) {
                if (gp->dummy == 0) {
                    lastGP = killGenerator(gp);
                } else {
                    gp->kind |= 0x800;
                }
                if (lastGP != NULL) {
                    gp = lastGP->next;
                } else {
                    gp = activeGenerator;
                }
            } else {
                lastGP = gp;
                gp = gp->next;
            }
        }
    }
}

static inline HSD_Generator* allocGenerator(void)
{
    HSD_Generator* gp;

    if (freeGenerator == NULL) {
        freeGenerator = HSD_Alloc(sizeof(HSD_Generator));
        memset(freeGenerator, 0, sizeof(HSD_Generator));
    }
    gp = freeGenerator;
    if (gp == NULL) {
        return NULL;
    } else {
        numActiveGenerators++;
        if (numActiveGenerators > numPeakGenerators) {
            numPeakGenerators = numActiveGenerators;
        }
        freeGenerator = gp->next;
        if (lastGP == NULL || lastGP->next == NULL) {
            if (activeGenerator == NULL) {
                gp->next = NULL;
                activeGenerator = gp;
            } else {
                gp->next = activeGenerator->next;
                activeGenerator->next = gp;
            }
        } else {
            gp->next = lastGP->next->next;
            lastGP->next->next = gp;
        }
        gp->idnum = psGetNewIDNum();
        gp->appsrt = NULL;
        gp->dummy = 0;
    }
    return gp;
}

HSD_Generator* psCreateGeneratorID(int linkNo, int bank, int id)
{
    HSD_Generator* gp;

    if (bank >= 64) {
        return NULL;
    }
    if (linkNo >= 8) {
        return NULL;
    }
    if (id >= psNumCmdList[bank]) {
        return NULL;
    }
    if (psCmdListArray[bank][id] == NULL) {
        return NULL;
    }

    gp = allocGenerator();

    if (gp != NULL) {
        gp->type = psCmdListArray[bank][id]->type;
        gp->bank = bank;
        gp->linkNo = linkNo;
        gp->index = id;
        gp->camera = NULL;
        gp->kind = psCmdListArray[bank][id]->kind;
        gp->texGroup = psCmdListArray[bank][id]->texGroup;
        gp->life = psCmdListArray[bank][id]->life;
        gp->genLife = psCmdListArray[bank][id]->genLife;
        gp->pos.z = 0.0F;
        gp->pos.y = 0.0F;
        gp->pos.x = 0.0F;
        gp->vel.x = psCmdListArray[bank][id]->vx;
        gp->vel.y = psCmdListArray[bank][id]->vy;
        gp->vel.z = psCmdListArray[bank][id]->vz;
        gp->grav = psCmdListArray[bank][id]->grav;
        gp->fric = psCmdListArray[bank][id]->fric;
        gp->size = psCmdListArray[bank][id]->size;
        gp->cmdList = psCmdListArray[bank][id]->cmdList;
        gp->radius = psCmdListArray[bank][id]->radius;
        gp->angle = psCmdListArray[bank][id]->angle;
        gp->random = psCmdListArray[bank][id]->random;

        if (gp->kind & 0x100) {
            if (gp->random < 0.0F) {
                gp->count = (1.0F + gp->random > FLT_EPSILON) ? 1.0F : 0.0F;
            } else {
                gp->count = 1.0F - FLT_EPSILON;
            }
        } else if (gp->random < 0.0F) {
            gp->count = 0.0F;
        } else {
            gp->count = HSD_Randf();
        }

        {
            HSD_PSTexGroup* tg = psTexGroupArray[bank][gp->texGroup];
            if (tg != NULL && tg->palflag != 0) {
                gp->kind |= 0x10;
            }
        }

        gp->numChild = 0;

        switch (gp->type & 0xF) {
        case 0:
        case 3:
        case 4: {
            HSD_PSCmdList* c = psCmdListArray[bank][id];
            f32 p1 = c->param1;
            if (p1 == 0.0F && c->param2 == 0.0F) {
                gp->aux.disc.minAngle = 0.0F;
                gp->aux.disc.maxAngle = 6.2831855F;
            } else {
                gp->aux.disc.minAngle = p1;
                gp->aux.disc.maxAngle = psCmdListArray[bank][id]->param2;
            }
            break;
        }
        case 1:
            gp->aux.line.x2 = psCmdListArray[bank][id]->param1;
            gp->aux.line.y2 = psCmdListArray[bank][id]->param2;
            gp->aux.line.z2 = psCmdListArray[bank][id]->param3;
            break;
        case 2:
            break;
        case 6:
        case 7: {
            HSD_PSCmdList* c = psCmdListArray[bank][id];
            f32 p1 = c->param1;
            if (p1 == 0.0F && c->param2 == 0.0F) {
                gp->aux.cone.minAngle = 0.0F;
                gp->aux.cone.maxAngle = 6.2831855F;
            } else {
                gp->aux.cone.minAngle = p1;
                gp->aux.cone.maxAngle = psCmdListArray[bank][id]->param2;
            }
            gp->aux.cone.height = psCmdListArray[bank][id]->param3;
            break;
        }
        case 5: {
            gp->aux.rect.xx = gp->aux.rect.x = psCmdListArray[bank][id]->param1;
            gp->aux.rect.yy = gp->aux.rect.y = psCmdListArray[bank][id]->param2;
            gp->aux.rect.zz = gp->aux.rect.z = psCmdListArray[bank][id]->param3;
            gp->aux.rect.zy = 0.0F;
            gp->aux.rect.zx = 0.0F;
            gp->aux.rect.yz = 0.0F;
            gp->aux.rect.yx = 0.0F;
            gp->aux.rect.xz = 0.0F;
            gp->aux.rect.xy = 0.0F;
            gp->aux.rect.flag = 0;
            if (psCmdListArray[bank][id]->param1 < 0.0F) {
                gp->aux.rect.flag |= 1;
            }
            if (psCmdListArray[bank][id]->param2 < 0.0F) {
                gp->aux.rect.flag |= 2;
            }
            if (psCmdListArray[bank][id]->param3 < 0.0F) {
                gp->aux.rect.flag |= 4;
            }
            break;
        }
        case 8: {
            f32 mag;
            gp->aux.sphere.speed = sqrtf(gp->vel.z * gp->vel.z + (gp->vel.x * gp->vel.x + gp->vel.y * gp->vel.y));
            mag = sqrtf(gp->vel.x * gp->vel.x + gp->vel.z * gp->vel.z);
            if (mag < FLT_MIN) {
                if (gp->vel.y >= 0.0F) {
                    gp->aux.sphere.latMid = 1.5707964F;
                } else {
                    gp->aux.sphere.latMid = -1.5707964F;
                }
            } else {
                gp->aux.sphere.latMid = (f32) atan2(gp->vel.y, mag);
            }
            if (fabs(gp->vel.x) < FLT_MIN) {
                if (gp->vel.z >= 0.0F) {
                    gp->aux.sphere.lonMid = 1.5707964F;
                } else {
                    gp->aux.sphere.lonMid = -1.5707964F;
                }
            } else {
                gp->aux.sphere.lonMid = (f32) atan2(gp->vel.z, gp->vel.x);
            }
            gp->aux.sphere.latRange = psCmdListArray[bank][id]->param1;
            if (gp->aux.sphere.latRange < 0.0F) {
                gp->aux.sphere.latRange = -gp->aux.sphere.latRange;
                gp->aux.sphere.speed = -gp->aux.sphere.speed;
            }
            gp->aux.sphere.lonRange = psCmdListArray[bank][id]->param2;
            break;
        }
        default:
            if (psExtCreateGenFunc != NULL) {
                psExtCreateGenFunc(gp);
            }
            break;
        }

        if (gp->kind & 0x20000) {
            gp->type |= 0x800;
            psAddGeneratorAppSRT(gp, 0);
            if (gp->appsrt != NULL) {
                gp->appsrt->xA2 = 1;
                gp->appsrt->gp = gp;
            }
        }

        gp->flags = 2;
        gp->jobj = NULL;
        gp->rot.z = 0.0F;
        gp->rot.y = 0.0F;
        gp->rot.x = 0.0F;
        gp->scale.z = 1.0F;
        gp->scale.y = 1.0F;
        gp->scale.x = 1.0F;
        gp->scale2.z = 1.0F;
        gp->scale2.y = 1.0F;
        gp->scale2.x = 1.0F;
    }
    return gp;
}

void psSetBillboardCamera(HSD_CObj* cobj)
{
    if (cobj != psCamera) {
        if (psCamera != NULL) {
            cobjUnref(psCamera);
        }
        if (cobj != NULL) {
            ref_INC(cobj);
        }
        psCamera = cobj;
    }
}

void psGeneratorSetCamera(HSD_Generator* gp, HSD_CObj* cobj)
{
    gp->camera = cobj;
}

void* psGeneratorGetCamera(HSD_Generator* gp)
{
    return gp->camera;
}

