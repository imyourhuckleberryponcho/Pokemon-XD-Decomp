// Draft (written from asm).
#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

struct PeopleWork {
    u8 unk0[0x1C];
    u32 modelResID;  // 0x1C
};

struct PeopleInfo;

extern "C" {
PeopleWork* peopleGet(s32 group, s32 id);
f32* peopleBiosGetPosPtr(PeopleWork* work);
f32* peopleBiosGetPrevPosPtr(PeopleWork* work);
void peopleBiosSetPos(PeopleWork* work, void* position);
PeopleInfo* peopleInfoBiosGetPtr(u32 modelResID);
f32 peopleInfoBiosGetColBallSize(PeopleInfo* info);
void* GSresGetResource(u32 group, u32 id);
void GSgfxLayerSetActive(int id);
void GScameraLoadActiveCameraMatrix(int id);
void GSgfxCullMode(u32 mode);
void* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void GSgfxSetupRenderAndSelect(void* vf);
void GSgfxBlendMode(int type, u32 src, u32 dst);
void GSgfxZCompare(u8 enable, u32 func);
void GSgfxPixelMode(u8 colorUpdate, u8 alphaUpdate, u8 dither);
void GSgfxAlphaCompare(u8 enable, u32 comp0, u8 ref0, u32 op, u32 comp1, u8 ref1);
void GSgfxSetPrimitiveType(u32 type);
void GSgfxBeginSurface(unsigned short num);
void GSgfxVertex3f(f32 x, f32 y, f32 z);
void GSgfxColor4u8(u8 r, u8 g, u8 b, u8 a);
void GSgfxEndSurface(void);
void GScolsy2UtilGetPointExtentionLine(GSvec* out, GSvec* start, GSvec* end, f32 length);
f32 GScolsy2UtilGetSidePlanePoint(GSvec* normal, GSvec* verts, GSvec* point);
void GScolsy2UtilGetCpPlanePoint(GSvec* out, GSvec* normal, GSvec* verts, GSvec* point);
BOOL GScolsy2UtilChkInTri(GSvec* point, GSvec* verts, GSvec* normal);
bool GScolsys2HitCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hitOut);
void heroMoveSetLockFrame(s32 frames);
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* ab);
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
void PSVECNormalize(const GSvec* src, GSvec* unit);
f32 PSVECMag(const GSvec* v);
f32 PSVECDotProduct(const GSvec* a, const GSvec* b);
f32 PSVECSquareDistance(const GSvec* a, const GSvec* b);
}

static u8 _peopleGetCrossPoint(GSvec* proj, GSvec* pt, f32 radius, GSvec* a, GSvec* b, GSvec* normal);
static u8 getCpPointPoly(GSvec* out, GSvec* pt, f32 radius, GSvec* verts, GSvec* normal);

static inline void debugColor() {
    GSgfxColor4u8(0, 0x80, 0xFF, 0xC0);
}

static inline f32 getColBallSize(PeopleWork* work) {
    PeopleInfo* info = peopleInfoBiosGetPtr(work->modelResID);
    if (info != 0) {
        return peopleInfoBiosGetColBallSize(info);
    }
    return 4.0f;
}

extern "C" {

u8 peopleLineCheck(s32 group, s32 id, f32 x1, f32 z1, f32 x2, f32 z2, f32 unused, u8 apply) {
    PeopleWork* work;
    GSvec step;
    GSvec lineA;
    GSvec lineB;
    GSvec prev;
    GSvec pos;
    GSvec delta;
    GSvec hit;
    GSvec diff;
    GSvec result;
    GSvec proj;
    GSvec offset;
    GSvec dir;
    GSvec toPrev;
    PeopleInfo* info;
    f32 size;
    f32 stepLen;
    f32 radius;
    f32 t;
    f32 next;
    f32 dot;
    f32* p;
    u8* res;

    work = peopleGet(group, id);
    if (work == 0) {
        return 0;
    }
    p = peopleBiosGetPosPtr(work);
    pos.x = p[0];
    pos.y = p[1];
    pos.z = p[2];
    p = peopleBiosGetPrevPosPtr(work);
    prev.x = p[0];
    prev.y = p[1];
    prev.z = p[2];
    PSVECSubtract(&pos, &prev, &delta);
    lineA.x = x1;
    lineA.y = pos.y;
    lineA.z = z1;
    lineB.x = x2;
    lineB.y = pos.y;
    lineB.z = z2;

    res = (u8*)GSresGetResource(0, 2);
    if (res != 0 && *res != 0) {
        GSgfxLayerSetActive(2);
        GScameraLoadActiveCameraMatrix(2);
        GSgfxCullMode(0);
        GSgfxSetupRenderAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0));
        GSgfxBlendMode(1, 4, 5);
        GSgfxZCompare(1, 1);
        GSgfxPixelMode(1, 1, 1);
        GSgfxAlphaCompare(0, 7, 0, 0, 7, 0);
        GSgfxSetPrimitiveType(0x98);
        GSgfxBeginSurface(4);
        GSgfxVertex3f(x1, pos.y - 50.0f, z1);
        debugColor();
        GSgfxVertex3f(x1, 50.0f + pos.y, z1);
        debugColor();
        GSgfxVertex3f(x2, pos.y - 50.0f, z2);
        debugColor();
        GSgfxVertex3f(x2, 50.0f + pos.y, z2);
        debugColor();
        GSgfxEndSurface();
    }

    info = peopleInfoBiosGetPtr(work->modelResID);
    if (info != 0) {
        size = peopleInfoBiosGetColBallSize(info);
    } else {
        size = 4.0f;
    }
    radius = size;
    f32 mag = PSVECMag(&delta);
    stepLen = mag;
    if (stepLen > 0.0f) {
        stepLen = size / stepLen;
        if (stepLen > 1.0f) {
            stepLen = 1.0f;
        }
    } else {
        stepLen = 1.0f;
    }

    PSVECSubtract(&lineB, &lineA, &dir);
    if (PSVECMag(&dir) < 0.0001f) {
        return 0;
    }
    PSVECNormalize(&dir, &dir);
    PSVECSubtract(&prev, &lineA, &toPrev);
    dot = PSVECDotProduct(&toPrev, &dir);
    PSVECScale(&dir, &toPrev, dot);
    PSVECAdd(&toPrev, &lineA, &proj);
    PSVECSubtract(&prev, &proj, &offset);

    for (t = 0.0f; t < 1.0f; t += stepLen) {
        next = t + stepLen;
        if (next > 1.0f) {
            next = 1.0f;
        }
        PSVECScale(&delta, &step, next);
        PSVECAdd(&prev, &step, &step);
        if (_peopleGetCrossPoint(&proj, &step, radius, &lineA, &lineB, &offset)) {
            if (apply) {
                GScolsy2UtilGetPointExtentionLine(&result, &proj, &step, 0.0001f + radius);
                if (GScolsys2HitCollision(&prev, &result, 4.0f, &hit)) {
                    PSVECSubtract(&hit, &result, &diff);
                    PSVECAdd(&result, &diff, &result);
                }
                peopleBiosSetPos(work, &result);
                heroMoveSetLockFrame(1);
            }
            return 1;
        }
    }
    return 0;
}

}

static u8 _peopleGetCrossPoint(GSvec* proj, GSvec* pt, f32 radius, GSvec* a, GSvec* b, GSvec* normal) {
    GSvec v[3];

    v[0].x = a->x;
    v[0].y = proj->y - 50.0f;
    v[0].z = a->z;
    v[1].x = b->x;
    v[1].y = proj->y - 50.0f;
    v[1].z = b->z;
    v[2].x = a->x;
    v[2].y = 50.0f + proj->y;
    v[2].z = a->z;
    if (getCpPointPoly(proj, pt, radius, v, normal)) {
        return 1;
    }
    v[0].x = b->x;
    v[0].y = proj->y - 50.0f;
    v[0].z = b->z;
    v[1].x = b->x;
    v[1].y = 50.0f + proj->y;
    v[1].z = b->z;
    if (getCpPointPoly(proj, pt, radius, v, normal)) {
        return 1;
    }
    v[0].x = b->x;
    v[0].y = proj->y - 50.0f;
    v[0].z = b->z;
    v[1].x = a->x;
    v[1].y = proj->y - 50.0f;
    v[1].z = a->z;
    v[2].x = a->x;
    v[2].y = 50.0f + proj->y;
    v[2].z = a->z;
    if (getCpPointPoly(proj, pt, radius, v, normal)) {
        return 1;
    }
    v[1].x = a->x;
    v[1].y = 50.0f + proj->y;
    v[1].z = a->z;
    v[2].x = b->x;
    v[2].y = 50.0f + proj->y;
    v[2].z = b->z;
    return getCpPointPoly(proj, pt, radius, v, normal) != 0;
}

static u8 getCpPointPoly(GSvec* out, GSvec* pt, f32 radius, GSvec* verts, GSvec* normal) {
    GSvec cp;

    if (GScolsy2UtilGetSidePlanePoint(normal, verts, pt) < 0.0f) {
        return 0;
    }
    GScolsy2UtilGetCpPlanePoint(&cp, normal, verts, pt);
    if (PSVECSquareDistance(&cp, pt) >= radius * radius) {
        return 0;
    }
    if (GScolsy2UtilChkInTri(&cp, verts, normal) == 0) {
        return 0;
    }
    out->x = cp.x;
    out->y = cp.y;
    out->z = cp.z;
    return 1;
}

extern "C" {

u8 peopleRectCheck(s32 group, s32 id, f32 x1, f32 z1, f32 x2, f32 z2) {
    PeopleWork* work = peopleGet(group, id);
    f32* p;
    f32 px, py, pz;
    f32 yh;
    f32 minX, maxX, minZ, maxZ;
    u8* res;

    if (work == 0) {
        return 0;
    }
    p = peopleBiosGetPosPtr(work);
    px = p[0];
    py = p[1];
    pz = p[2];

    res = (u8*)GSresGetResource(0, 2);
    if (res != 0 && *res != 0) {
        GSgfxLayerSetActive(2);
        GScameraLoadActiveCameraMatrix(2);
        GSgfxCullMode(0);
        GSgfxSetupRenderAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0));
        GSgfxBlendMode(1, 4, 5);
        GSgfxZCompare(1, 1);
        GSgfxPixelMode(1, 1, 1);
        GSgfxAlphaCompare(0, 7, 0, 0, 7, 0);
        GSgfxSetPrimitiveType(0x98);
        GSgfxBeginSurface(10);
        GSgfxVertex3f(x1, py, z1);
        debugColor();
        yh = 50.0f + py;
        GSgfxVertex3f(x1, yh, z1);
        debugColor();
        GSgfxVertex3f(x1, py, z2);
        debugColor();
        GSgfxVertex3f(x1, yh, z2);
        debugColor();
        GSgfxVertex3f(x2, py, z2);
        debugColor();
        GSgfxVertex3f(x2, yh, z2);
        debugColor();
        GSgfxVertex3f(x2, py, z1);
        debugColor();
        GSgfxVertex3f(x2, yh, z1);
        debugColor();
        GSgfxVertex3f(x1, py, z1);
        debugColor();
        GSgfxVertex3f(x1, yh, z1);
        debugColor();
        GSgfxEndSurface();
    }

    if (x1 < x2) {
        minX = x1;
        maxX = x2;
    } else {
        minX = x2;
        maxX = x1;
    }
    if (z1 < z2) {
        minZ = z1;
        maxZ = z2;
    } else {
        minZ = z2;
        maxZ = z1;
    }
    if (minX <= px && px <= maxX && minZ <= pz && pz <= maxZ) {
        return 1;
    }
    return 0;
}

}
