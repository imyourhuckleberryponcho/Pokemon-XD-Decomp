#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

extern "C" {
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* ab);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
f32 PSVECMag(const GSvec* v);

BOOL GScolsys2UtilGetCpPlaneLine(GSvec* out, f32* tOut, GSvec* normal, GSvec* planePoint, GSvec* lineStart,
                                 GSvec* lineEnd) {
    GSvec direction;
    f32 denominator;
    f32 t;

    PSVECSubtract(lineEnd, lineStart, &direction);
    if ((denominator = normal->x * direction.x + normal->y * direction.y + normal->z * direction.z) == 0.0f) {
        return FALSE;
    }

    t = (normal->x * (planePoint->x - lineStart->x) + normal->y * (planePoint->y - lineStart->y) +
         normal->z * (planePoint->z - lineStart->z)) /
        denominator;
    PSVECScale(&direction, &direction, t);
    PSVECAdd(&direction, lineStart, out);
    *tOut = t;
    return TRUE;
}

f32 GScolsys2UtilGetCpLinePoint(GSvec* out, GSvec* start, GSvec* end, GSvec* point) {
    GSvec direction;
    f32 lengthSquared;
    f32 t;

    PSVECSubtract(end, start, &direction);
    lengthSquared = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
    if (0.0f == lengthSquared) {
        out->x = start->x;
        out->y = start->y;
        out->z = start->z;
        return 0.0f;
    }

    t = (direction.x * (point->x - start->x) + direction.y * (point->y - start->y) +
         direction.z * (point->z - start->z)) /
        lengthSquared;
    PSVECScale(&direction, &direction, t);
    PSVECAdd(&direction, start, out);
    return t;
}

void GScolsy2UtilGetPointExtentionLine(GSvec* out, GSvec* start, GSvec* end, f32 length) {
    GSvec v;

    PSVECSubtract(end, start, &v);
    f32 mag = PSVECMag(&v);
    if (0.0f == mag) {
        return;
    }
    PSVECScale(&v, &v, length / mag);
    PSVECAdd(&v, start, out);
}

BOOL GScolsy2UtilChkInTri(GSvec* point, GSvec* verts, GSvec* normal) {
    f32* pointValues = (f32*)point;
    GSvec projected[3];
    f32 absX;
    f32 absY;
    f32 absZ;
    f32 orientation;
    f32 pu;
    f32 pv;
    f32 minU;
    f32 minV;
    f32 maxU;
    f32 maxV;
    s32 u;
    s32 v;
    s32 i;

    absX = normal->x > 0.0f ? normal->x : -normal->x;
    absY = normal->y > 0.0f ? normal->y : -normal->y;
    absZ = normal->z > 0.0f ? normal->z : -normal->z;

    if (absX < absY) {
        if (absY < absZ) {
            orientation = normal->z;
            u = 0;
            v = 1;
        } else {
            orientation = normal->y;
            u = 2;
            v = 0;
        }
    } else if (absX > absZ) {
        orientation = -normal->x;
        u = 2;
        v = 1;
    } else {
        orientation = normal->z;
        u = 0;
        v = 1;
    }

    if (orientation < 0.0f) {
        for (i = 0; i < 3; i++) {
            projected[i].x = ((f32*)&verts[i])[u];
            projected[i].y = ((f32*)&verts[i])[v];
        }
    } else {
        for (i = 0; i < 3; i++) {
            projected[i].x = ((f32*)&verts[2 - i])[u];
            projected[i].y = ((f32*)&verts[2 - i])[v];
        }
    }

    pu = pointValues[u];
    pv = pointValues[v];
    minU = minV = 1000000.0f;
    maxU = maxV = -1000000.0f;
    for (i = 0; i < 3; i++) {
        if (minU > projected[i].x) {
            minU = projected[i].x;
        }
        if (minV > projected[i].y) {
            minV = projected[i].y;
        }
        if (maxU < projected[i].x) {
            maxU = projected[i].x;
        }
        if (maxV < projected[i].y) {
            maxV = projected[i].y;
        }
    }

    if (minU > pointValues[u] || minV > pointValues[v] || maxU < pointValues[u] || maxV < pointValues[v]) {
        return FALSE;
    }

    for (i = 0; i < 3; i++) {
        s32 next = i + 1;
        if (next >= 3) {
            next = 0;
        }
        if ((projected[next].y - projected[i].y) * (pu - projected[i].x) -
                (projected[next].x - projected[i].x) * (pv - projected[i].y) >
            0.0f) {
            return FALSE;
        }
    }
    return TRUE;
}

void GScolsy2UtilGetCpPlanePoint(GSvec* out, GSvec* normal, GSvec* verts, GSvec* point) {
    f32 scale;

    scale = (normal->x * (verts->x - point->x) + normal->y * (verts->y - point->y) +
             normal->z * (verts->z - point->z)) /
            (normal->x * normal->x + normal->y * normal->y + normal->z * normal->z);
    PSVECScale(normal, out, scale);
    PSVECAdd(out, point, out);
}
}
