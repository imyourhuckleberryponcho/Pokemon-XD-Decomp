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

#define COL_ABS(x) ((x) > 0.0f ? (x) : -(x))

// Edge test (same as getCpPolyVec in GScolsys2Walk): the edge deltas are written in place so they
// become the inline's own temporaries, which gives retail's float-register order.
static inline f32 colEdgeSide(f32 ez, f32 ex, f32 z, f32 x, f32 pz, f32 px)
{
    ez -= z;
    ex -= x;
    return ex * (pz - z) - ez * (px - x);
}

BOOL GScolsy2UtilChkInTri(GSvec* point, GSvec* verts, GSvec* normal)
{
    GSvec pts[3];
    f32 absX;
    f32 absY;
    f32 absZ;
    f32 facing;
    s32 u;
    s32 v;
    f32 minY;
    f32 minX;
    f32 maxY;
    f32 maxX;
    f32 px;
    f32 py;
    s32 i;
    s32 next;

    absX = COL_ABS(normal->x);
    absY = COL_ABS(normal->y);
    absZ = COL_ABS(normal->z);
    if (absX < absY) {
        if (absY < absZ) {
            facing = normal->z;
            u = 0;
            v = 1;
        } else {
            facing = normal->y;
            u = 2;
            v = 0;
        }
    } else if (absX > absZ) {
        facing = -normal->x;
        u = 2;
        v = 1;
    } else {
        facing = normal->z;
        u = 0;
        v = 1;
    }

    if (facing < 0.0f) {
        for (i = 0; i < 3; i++) {
            pts[i].x = (&verts[i].x)[u];
            pts[i].y = (&verts[i].x)[v];
        }
    } else {
        for (i = 0; i < 3; i++) {
            pts[i].x = (&verts[2 - i].x)[u];
            pts[i].y = (&verts[2 - i].x)[v];
        }
    }

    minX = minY = 1000000.0f;
    maxX = maxY = -1000000.0f;
    px = (&point->x)[u];
    py = (&point->x)[v];
    for (i = 0; i < 3; i++) {
        f32 x;
        f32 y;

        x = pts[i].x;
        if (minX > x) {
            minX = x;
        }
        y = pts[i].y;
        if (minY > y) {
            minY = y;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (maxY < y) {
            maxY = y;
        }
    }
    if (minX > px || minY > py || maxX < px || maxY < py) {
        return 0;
    }

    for (i = 0; i < 3; i++) {
        f32 x;
        f32 y;

        next = i + 1;
        if (next >= 3) {
            next = 0;
        }
        x = pts[i].x;
        y = pts[i].y;
        if (colEdgeSide(pts[next].y, pts[next].x, y, x, py, px) > 0.0f) {
            return 0;
        }
    }
    return 1;
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
