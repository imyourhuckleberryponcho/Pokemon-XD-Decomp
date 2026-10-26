



#define HSD_FILE_NAME "generator.c"

#include <dolphin/types.h>


#define _MATH_H_
extern f32 __float_nan[];
extern f32 __float_min[];
#define NAN (__float_nan[0])
double sin(double x);
double cos(double x);
double tan(double x);
double atan2(double y, double x);

inline f32 sinf(f32 x) { return (f32) sin(x); }
inline f32 cosf(f32 x) { return (f32) cos(x); }
inline f32 tanf(f32 x) { return (f32) tan(x); }
inline f32 atan2f(f32 y, f32 x) { return (f32) atan2(y, x); }
double __fabs(double x);
inline double fabs(double x)
{
    return __fabs(x);
}

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
    Vec3 vel_copy;
    Vec3 emit_pos;
    Vec3 tmpvec;
    Vec3 vec;
    Mtx rot_mtx;
    Mtx mtx_x;
    Mtx mtx_y;
    Mtx mtx_z;
    Vec3 look_dir;
    Vec3 cam_up;
    Vec3 cross1;
    Vec3 vel_norm;
    Mtx trig_mtx;
    f32 cur_angle;
    f32 angle_step;
    f32 scale_x;
    f32 scale_y;
    f32 scale_z;
    f32 vel_mag;
    f32 angle1;
    f32 cone_angle;
    f32 dist;
    f32 radius;
    f32 elevation;
    f32 angle3;

    angle3 = angle1 = 0.0f;
    if (gp->count < 1.0f) {
        return gp->count;
    }

    vel_copy.x = gp->vel.x;
    vel_copy.y = gp->vel.y;
    vel_copy.z = gp->vel.z;
    scale_x = gp->scale.x;
    scale_y = gp->scale.y;
    scale_z = gp->scale.z;
    if ((gp->type & 0xF) == 2 && (gp->flags & 0x80)) {
        vel_copy.x *= scale_x;
        vel_copy.y *= scale_y;
        vel_copy.z *= scale_z;
    }

    vel_mag = sqrtf(vel_copy.z * vel_copy.z +
                    (vel_copy.x * vel_copy.x + vel_copy.y * vel_copy.y));

    PSMTXIdentity(rot_mtx);

    if (!(gp->kind & 0x30000)) {
        PSMTXRotRad(mtx_x, 'X', gp->rot.x);
        PSMTXRotRad(mtx_y, 'Y', gp->rot.y);
        PSMTXRotRad(mtx_z, 'Z', gp->rot.z);
        PSMTXConcat(mtx_y, mtx_x, mtx_x);
        PSMTXConcat(mtx_z, mtx_x, mtx_x);

        vec.x = mtx_x[0][0];
        vec.y = mtx_x[1][0];
        vec.z = mtx_x[2][0];
        PSVECNormalize(&vec, &vec);
        rot_mtx[0][0] = vec.x;
        rot_mtx[1][0] = vec.y;
        rot_mtx[2][0] = vec.z;

        vec.x = mtx_x[0][1];
        vec.y = mtx_x[1][1];
        vec.z = mtx_x[2][1];
        PSVECNormalize(&vec, &vec);
        rot_mtx[0][1] = vec.x;
        rot_mtx[1][1] = vec.y;
        rot_mtx[2][1] = vec.z;

        vec.x = mtx_x[0][2];
        vec.y = mtx_x[1][2];
        vec.z = mtx_x[2][2];
        PSVECNormalize(&vec, &vec);
        rot_mtx[0][2] = vec.x;
        rot_mtx[1][2] = vec.y;
        rot_mtx[2][2] = vec.z;

        rot_mtx[2][3] = 0.0f;
        rot_mtx[1][3] = 0.0f;
        rot_mtx[0][3] = 0.0f;
    }

    if (gp->kind & 0x10000) {
        HSD_ASSERT(626, psCamera);
        look_dir.x = psCamera->eyepos->pos.x - gp->pos.x;
        look_dir.y = psCamera->eyepos->pos.y - gp->pos.y;
        look_dir.z = psCamera->eyepos->pos.z - gp->pos.z;
        PSVECNormalize(&look_dir, &look_dir);
        HSD_CObjGetUpVector(psCamera, &cam_up);
        PSVECNormalize(&cam_up, &cam_up);
        PSVECCrossProduct(&cam_up, &look_dir, &cross1);
        PSVECCrossProduct(&look_dir, &cross1, &cam_up);

        rot_mtx[0][0] = cross1.x;
        rot_mtx[1][0] = cross1.y;
        rot_mtx[2][0] = cross1.z;
        rot_mtx[0][1] = cam_up.x;
        rot_mtx[1][1] = cam_up.y;
        rot_mtx[2][1] = cam_up.z;
        rot_mtx[0][2] = look_dir.x;
        rot_mtx[1][2] = look_dir.y;
        rot_mtx[2][2] = look_dir.z;
    }

    if ((gp->type & 0xF) != 1 && vel_mag > FLT_EPSILON) {
        f32 yaw;
        f32 sin_yaw;
        f32 cos_yaw;
        f32 pitch;
        f32 sin_pitch;
        f32 cos_pitch;

        vel_norm.x = gp->vel.x;
        vel_norm.y = gp->vel.y;
        vel_norm.z = gp->vel.z;
        PSVECNormalize(&vel_norm, &vel_norm);

        if (fabs(vel_norm.z) < FLT_MIN) {
            if (vel_norm.y >= 0.0f) {
                yaw = 1.5707964f;
            } else {
                yaw = -1.5707964f;
            }
        } else {
            yaw = atan2fInline(vel_norm.y, vel_norm.z);
        }
        sin_yaw = sinf(yaw);
        cos_yaw = cosf(yaw);

        {
            f32 projected_z = vel_norm.y * sin_yaw + vel_norm.z * cos_yaw;

            if (fabs(projected_z) < FLT_MIN) {
                if (vel_norm.x >= 0.0f) {
                    pitch = 1.5707964f;
                } else {
                    pitch = -1.5707964f;
                }
            } else {
                pitch = atan2fInline(vel_norm.x, projected_z);
            }
        }
        sin_pitch = sinf(pitch);
        cos_pitch = cosf(pitch);

        trig_mtx[0][0] = cos_pitch;
        trig_mtx[0][1] = 0.0f;
        trig_mtx[0][2] = sin_pitch;
        trig_mtx[0][3] = 0.0f;
        trig_mtx[1][0] = -sin_yaw * sin_pitch;
        trig_mtx[1][1] = cos_yaw;
        trig_mtx[1][2] = sin_yaw * cos_pitch;
        trig_mtx[1][3] = 0.0f;
        trig_mtx[2][0] = -cos_yaw * sin_pitch;
        trig_mtx[2][1] = -sin_yaw;
        trig_mtx[2][2] = cos_yaw * cos_pitch;
        trig_mtx[2][3] = 0.0f;
        PSMTXConcat(rot_mtx, trig_mtx, rot_mtx);
    }
    elevation = vel_mag;

    if ((gp->type & 0xF) == 2) {
        if (fabs(rot_mtx[2][2]) < FLT_MIN) {
            if (rot_mtx[1][2] >= 0.0f) {
                angle1 = 1.5707964f;
            } else {
                angle1 = -1.5707964f;
            }
        } else {
            angle1 = atan2fInline(rot_mtx[1][2], rot_mtx[2][2]);
        }
        {
            f32 comb = rot_mtx[1][2] * sinf(angle1) + rot_mtx[2][2] * cosf(angle1);

            if (fabs(comb) < FLT_MIN) {
                if (rot_mtx[0][2] >= 0.0f) {
                    angle3 = 1.5707964f;
                } else {
                    angle3 = -1.5707964f;
                }
            } else {
                angle3 = atan2fInline(rot_mtx[0][2], comb);
            }
        }
    }







    if (gp->angle < 0.0f) {
        switch (gp->type & 0xF) {
        case 0:
        case 3:
        case 4: {
            f32 min_a = gp->aux.cone.minAngle;
            f32 rnd = HSD_Randf();
            f32 step = (gp->aux.cone.maxAngle - min_a) / (f32) (s32) gp->count;

            angle_step = step;
            cur_angle = step * rnd + min_a;
            break;
        }
        case 6:
        case 7: {
            f32 min_a = gp->aux.cone.minAngle;
            f32 rnd = HSD_Randf();
            f32 step = (gp->aux.cone.maxAngle - min_a) / (f32) (s32) gp->count;

            angle_step = step;
            cur_angle = step * rnd + min_a;
            break;
        }
        default:
            cur_angle = (f32) (2.0 * (M_PI * HSD_Randf()));
            angle_step = (f32) ((2.0 * M_PI) / (s32) gp->count);
            break;
        }
    }

    while (gp->count >= 1.0f) {
        switch (gp->type & 0xF) {
        case 0:
        case 3:
        case 4:
        case 6:
        case 7:
            if (gp->radius < 0.0f) {
                dist = -gp->radius;
                radius = 1.0f;
            } else {
                radius = HSD_Randf();
                if ((gp->type & 0xF) == 3 || (gp->type & 0xF) == 4) {
                    radius = sqrtf(radius);
                }
                dist = radius * gp->radius;
            }

            switch (gp->type & 0xF) {
            case 6:
                if (gp->angle < 0.0f) {
                    cur_angle += angle_step;
                    if (fabs(dist) < FLT_MIN) {
                        if (gp->aux.cone.height >= 0.0f) {
                            cone_angle = -gp->angle;
                        } else {
                            cone_angle = (f32) (M_PI - gp->angle);
                        }
                    } else {
                        cone_angle =
                            (f32) (M_PI_2 - atan2fInline(gp->aux.cone.height, dist) -
                                   gp->angle);
                    }
                } else {
                    f32 min_angle = gp->aux.cone.minAngle;

                    cur_angle = (gp->aux.cone.maxAngle - min_angle) *
                                    HSD_Randf() +
                                min_angle;
                    if (fabs(dist) < FLT_MIN) {
                        if (gp->aux.cone.height >= 0.0f) {
                            cone_angle = gp->angle;
                        } else {
                            cone_angle = (f32) (M_PI + gp->angle);
                        }
                    } else {
                        cone_angle =
                            (f32) (gp->angle +
                                   (M_PI_2 -
                                    atan2fInline(gp->aux.cone.height, dist)));
                    }
                }
                break;
            case 7:
                if (gp->angle < 0.0f) {
                    cone_angle = (f32) (M_PI_2 - gp->angle);
                    cur_angle += angle_step;
                } else {
                    cur_angle = gp->aux.cone.minAngle;
                    cur_angle = (gp->aux.cone.maxAngle - cur_angle) *
                                    HSD_Randf() +
                                cur_angle;
                    cone_angle = (f32) (M_PI_2 + gp->angle);
                }
                break;
            default:
                if (gp->angle < 0.0f) {
                    cone_angle = -gp->angle;
                    cur_angle += angle_step;
                    cone_angle = radius * cone_angle;
                } else {
                    cur_angle = gp->aux.cone.minAngle;
                    cur_angle = (gp->aux.cone.maxAngle - cur_angle) *
                                    HSD_Randf() +
                                cur_angle;
                    cone_angle = radius * gp->angle;
                }
                break;
            }

            emit_pos.x = dist * cosf(cur_angle);
            emit_pos.y = dist * sinf(cur_angle);

            if ((gp->type & 0xF) == 6 || (gp->type & 0xF) == 7) {
                emit_pos.z = HSD_Randf();
                if ((gp->type & 0xF) == 6) {
                    emit_pos.x *= 1.0f - emit_pos.z;
                    emit_pos.y *= 1.0f - emit_pos.z;
                }
                emit_pos.z *= gp->aux.cone.height;
            } else {
                emit_pos.z = 0.0f;
            }

            {
                f32 sin_ca = elevation * sinf(cone_angle);

                vec.x = sin_ca * cosf(cur_angle);
                vec.y = sin_ca * sinf(cur_angle);
                vec.z = elevation * cosf(cone_angle);
            }

            if ((gp->type & 0xF) == 3) {
                vec.x *= radius;
                vec.y *= radius;
                vec.z *= radius;
            }

            PSMTXMultVec(rot_mtx, &emit_pos, &emit_pos);
            emit_pos.x += gp->pos.x;
            emit_pos.y += gp->pos.y;
            emit_pos.z += gp->pos.z;
            PSMTXMultVec(rot_mtx, &vec, &vec);

            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind,
                               gp->texGroup, gp->cmdList, gp->life, 0,
                               emit_pos.x, emit_pos.y, emit_pos.z,
                               vec.x * scale_x, vec.y * scale_y,
                               vec.z * scale_z, gp->size, gp->grav,
                               gp->fric, gp);
            break;

        case 1: {
            f32 rnd = HSD_Randf();

            emit_pos.x = rnd * gp->aux.line.x2;
            emit_pos.y = rnd * gp->aux.line.y2;
            emit_pos.z = rnd * gp->aux.line.z2;

            PSMTXMultVec(rot_mtx, &emit_pos, &emit_pos);
            emit_pos.x += gp->pos.x;
            emit_pos.y += gp->pos.y;
            emit_pos.z += gp->pos.z;
            PSMTXMultVec(rot_mtx, &vel_copy, &vec);

            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind,
                               gp->texGroup, gp->cmdList, gp->life, 0,
                               emit_pos.x, emit_pos.y, emit_pos.z,
                               vec.x * scale_x, vec.y * scale_y,
                               vec.z * scale_z, gp->size, gp->grav,
                               gp->fric, gp);
            break;
        }

        case 2:
            if (gp->radius < 0.0f) {
                dist = 1.0f;
            } else {
                dist = HSD_Randf();
            }
            if (gp->angle < 0.0f) {
                cur_angle += angle_step;
            } else {
                cur_angle = (f32) (2.0 * (M_PI * HSD_Randf()));
            }
            gp->aux.line.x2 = elevation;
            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind | 4,
                               gp->texGroup, gp->cmdList, gp->life, 0,
                               0.0f, 0.0f, 0.0f, cur_angle, dist, 0.0f,
                               gp->size, angle1, angle3, gp);
            break;

        case 5:
            emit_pos.x = HSD_Randf();
            emit_pos.y = HSD_Randf();
            emit_pos.z = HSD_Randf();

            switch (gp->aux.rect.flag) {
            case 0:
                break;
            case 1:
                emit_pos.x = emit_pos.x > 0.5f ? 1.0f : 0.0f;
                break;
            case 2:
                emit_pos.y = emit_pos.y > 0.5f ? 1.0f : 0.0f;
                break;
            case 3: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->aux.rect.x;

                if (rnd > a2 / (a2 + gp->aux.rect.y)) {
                    emit_pos.y = emit_pos.y > 0.5f ? 1.0f : 0.0f;
                } else {
                    emit_pos.x = emit_pos.x > 0.5f ? 1.0f : 0.0f;
                }
                break;
            }
            case 4:
                emit_pos.z = emit_pos.z > 0.5f ? 1.0f : 0.0f;
                break;
            case 5: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->aux.rect.x;

                if (rnd > a2 / (a2 + gp->aux.rect.z)) {
                    emit_pos.z = emit_pos.z > 0.5f ? 1.0f : 0.0f;
                } else {
                    emit_pos.x = emit_pos.x > 0.5f ? 1.0f : 0.0f;
                }
                break;
            }
            case 6: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->aux.rect.y;

                if (rnd > a2 / (a2 + gp->aux.rect.z)) {
                    emit_pos.z = emit_pos.z > 0.5f ? 1.0f : 0.0f;
                } else {
                    emit_pos.y = emit_pos.y > 0.5f ? 1.0f : 0.0f;
                }
                break;
            }
            case 7: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->aux.rect.z;
                f32 b2 = gp->aux.rect.y;
                f32 c2 = gp->aux.rect.x;
                f32 r0 = 1.0f / (c2 * (b2 + a2) + b2 * a2);

                if (rnd < r0 * (c2 * b2)) {
                    emit_pos.z = emit_pos.z > 0.5f ? 1.0f : 0.0f;
                } else if (rnd > 1.0f - r0 * (c2 * a2)) {
                    emit_pos.y = emit_pos.y > 0.5f ? 1.0f : 0.0f;
                } else {
                    emit_pos.x = emit_pos.x > 0.5f ? 1.0f : 0.0f;
                }
                break;
            }
            }

            emit_pos.x -= 0.5f;
            emit_pos.y -= 0.5f;
            emit_pos.z -= 0.5f;

            tmpvec.x = gp->aux.rect.xx * emit_pos.x +
                       gp->aux.rect.yx * emit_pos.y +
                       gp->aux.rect.zx * emit_pos.z;
            tmpvec.y = gp->aux.rect.xy * emit_pos.x +
                       gp->aux.rect.yy * emit_pos.y +
                       gp->aux.rect.zy * emit_pos.z;
            tmpvec.z = gp->aux.rect.xz * emit_pos.x +
                       gp->aux.rect.yz * emit_pos.y +
                       gp->aux.rect.zz * emit_pos.z;

            PSMTXMultVec(rot_mtx, &tmpvec, &emit_pos);
            emit_pos.x += gp->pos.x;
            emit_pos.y += gp->pos.y;
            emit_pos.z += gp->pos.z;

            {
                f32 mag = sqrtf(gp->aux.rect.zx * gp->aux.rect.zx +
                                gp->aux.rect.zy * gp->aux.rect.zy +
                                gp->aux.rect.zz * gp->aux.rect.zz);
                f32 scale = elevation / mag;

                vec.x = gp->aux.rect.zx * scale;
                vec.y = gp->aux.rect.zy * scale;
                vec.z = gp->aux.rect.zz * scale;
            }

            PSMTXMultVec(rot_mtx, &vec, &vec);

            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind,
                               gp->texGroup, gp->cmdList, gp->life, 0,
                               emit_pos.x, emit_pos.y, emit_pos.z,
                               vec.x * scale_x, vec.y * scale_y,
                               vec.z * scale_z, gp->size, gp->grav,
                               gp->fric, gp);
            break;

        case 8: {
            f32 lat;
            f32 lon;

            if (0.0f == gp->aux.sphere.latRange) {
                lat = (f32) (M_PI * HSD_Randf());
            } else {
                lat = gp->aux.sphere.latRange * HSD_Randf();
            }
            lon = (f32) (2.0 * (M_PI * HSD_Randf()));
            {
                f32 r2 = gp->radius;

                if (r2 < 0.0f) {
                    dist = -r2;
                } else {
                    dist = r2 * HSD_Randf();
                }
            }

            vec.x = sinf(lat) * cosf(lon);
            vec.y = sinf(lat) * sinf(lon);
            vec.z = cosf(lat);

            PSMTXMultVec(rot_mtx, &vec, &emit_pos);

            vec.x = emit_pos.x * gp->aux.sphere.speed;
            vec.y = emit_pos.y * gp->aux.sphere.speed;
            vec.z = emit_pos.z * gp->aux.sphere.speed;

            if (gp->radius >= 0.0f && gp->aux.sphere.speed < 0.0f) {
                f32 scale = dist / gp->radius;

                vec.x *= scale;
                vec.y *= scale;
                vec.z *= scale;
            }

            emit_pos.x = dist * emit_pos.x + gp->pos.x;
            emit_pos.y = dist * emit_pos.y + gp->pos.y;
            emit_pos.z = dist * emit_pos.z + gp->pos.z;

            psGenerateParticle(gp->linkNo, gp->bank, 0, gp->kind,
                               gp->texGroup, gp->cmdList, gp->life, 0,
                               emit_pos.x, emit_pos.y, emit_pos.z,
                               vec.x * scale_x, vec.y * scale_y,
                               vec.z * scale_z, gp->size, gp->grav,
                               gp->fric, gp);
            break;
        }

        default:
            if (psExtExecGenFunc != 0) {
                psExtExecGenFunc(gp, rot_mtx);
            }
            break;
        }

        gp->count -= 1.0f;
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
                gp->aux.sphere.latMid = atan2f(gp->vel.y, mag);
            }
            if (fabs(gp->vel.x) < FLT_MIN) {
                if (gp->vel.z >= 0.0F) {
                    gp->aux.sphere.lonMid = 1.5707964F;
                } else {
                    gp->aux.sphere.lonMid = -1.5707964F;
                }
            } else {
                gp->aux.sphere.lonMid = atan2f(gp->vel.z, gp->vel.x);
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

