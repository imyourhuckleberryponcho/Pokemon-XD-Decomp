// STATUS: 2/5 exact (GScolsys2HitCollision, GScolsys2HitNpcCollision); default flags, LAYOUT/CONST OK.
// checkHitMdl 98.5% (pass 2/3 loop var regs), checkHitFixedMdl 96.7% (float prelude/int regs),
// checkHitCollision 93.9% (param/local register priority: target keeps iter/hitCount/i above alt/hitOut).
#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

struct GSmtx {
    f32 m[3][4];
};

struct CCD_TRI {
    GSvec verts[3];  // 0x00
    GSvec normal;    // 0x24
    u16 flags;       // 0x30
    u8 pad32[2];
};

struct CCD_GRID_CELL {
    u32 first;
    u32 count;
};

struct CCD_HITMDL_HEAD {
    CCD_TRI* tris;         // 0x00
    u32 numTris;           // 0x04
    CCD_GRID_CELL* cells;  // 0x08
    u32* indices;          // 0x0C
    u16 cellsX;            // 0x10
    u16 cellsZ;            // 0x12
    f32 cellWidth;         // 0x14
    f32 cellDepth;         // 0x18
    f32 minX;              // 0x1C
    f32 minZ;              // 0x20
};

struct CCD_OBJ {
    u8 unk0[0x28];
    CCD_HITMDL_HEAD* hit;     // 0x28
    u8 unk2C[8];
    CCD_HITMDL_HEAD* hitAlt;  // 0x34
    u8 unk38[4];
    u16 flags;  // 0x3C
    u8 pad3E[2];
};

struct CCD_FILEHEAD {
    CCD_OBJ* objs;
    u32 numObjs;
};

extern "C" {
void PSMTXMultVec(const GSmtx* m, const GSvec* src, GSvec* dst);
f32 PSVECSquareDistance(const GSvec* a, const GSvec* b);
f32 PSVECDistance(const GSvec* a, const GSvec* b);
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* ab);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
CCD_FILEHEAD* GScolsys2GetCCDFileHead(void);
void GScolsys2GetObjEnable(u32 index, bool* enable);
void GScolsys2GetObjMatrix(GSmtx* m, u32 index);
void GScolsys2GetObjRotMatrix(GSmtx* m, u32 index);
f32 GScolsy2UtilGetSidePlanePoint(GSvec* normal, GSvec* verts, GSvec* point);
void GScolsy2UtilGetCpPlanePoint(GSvec* out, GSvec* normal, GSvec* verts, GSvec* point);
bool GScolsy2UtilChkInTri(GSvec* point, GSvec* verts, GSvec* normal);
f32 GScolsys2UtilGetCpLinePoint(GSvec* out, GSvec* start, GSvec* end, GSvec* point);
void GScolsy2UtilGetPointExtentionLine(GSvec* out, GSvec* start, GSvec* end, f32 length);
}

static inline bool chkFace(GSvec* verts, GSvec* normal, GSvec* pos, f32 radiusSq, GSvec* hit) {
    GSvec cp;

    if (GScolsy2UtilGetSidePlanePoint(normal, verts, pos) < 0.0f) {
        return false;
    }
    GScolsy2UtilGetCpPlanePoint(&cp, normal, verts, pos);
    if (PSVECSquareDistance(&cp, pos) >= radiusSq) {
        return false;
    }
    if (!GScolsy2UtilChkInTri(&cp, verts, normal)) {
        return false;
    }
    *hit = cp;
    return true;
}

static inline bool chkEdges(CCD_TRI* tri, GSvec* verts, GSvec* normal, GSvec* pos, f32 radiusSq, GSvec* hit) {
    u16 mask[3] = {1, 2, 4};
    u16 flags;
    s32 j;
    GSvec cp;

    flags = tri->flags;
    if (GScolsy2UtilGetSidePlanePoint(normal, verts, pos) < 0.0f) {
        return false;
    }
    for (j = 0; j < 3; j++) {
        if (flags & mask[j]) {
            s32 next = j + 1;
            f32 d;
            if (next >= 3) {
                next = 0;
            }
            d = GScolsys2UtilGetCpLinePoint(&cp, &verts[j], &verts[next], pos);
            if (!(d < 0.0f) && !(d > 1.0f) && PSVECSquareDistance(&cp, pos) < radiusSq) {
                *hit = cp;
                return true;
            }
        }
    }
    return false;
}

static inline bool chkVerts(CCD_TRI* tri, GSvec* verts, GSvec* normal, GSvec* pos, f32 radiusSq, GSvec* hit) {
    u16 mask[3] = {1, 2, 4};
    u16 flags;
    s32 j;

    flags = tri->flags;
    if (GScolsy2UtilGetSidePlanePoint(normal, verts, pos) < 0.0f) {
        return false;
    }
    for (j = 0; j < 3; j++) {
        s32 other = j + 2;
        if (other >= 3) {
            other -= 3;
        }
        if ((flags & mask[j]) && (flags & mask[other]) && PSVECSquareDistance(&verts[j], pos) < radiusSq) {
            *hit = verts[j];
            return true;
        }
    }
    return false;
}

static bool checkHitFixedMdl(GSvec* pos, f32 radius, CCD_HITMDL_HEAD* head, GSvec* hitOut) {
    f32 minX, minZ, maxX, maxZ;
    s32 x0, z0, x1, z1;
    s32 gx, gz;
    u32 t;
    bool found;
    GSvec hit;
    GSvec cp;
    f32 radiusSq;
    CCD_GRID_CELL* cell;
    u32* index;
    CCD_TRI* tri;

    minX = pos->x - radius;
    minZ = pos->z - radius;
    maxX = pos->x + radius;
    maxZ = pos->z + radius;
    x0 = (minX - head->minX) / head->cellWidth;
    if (x0 < 0) {
        x0 = 0;
    }
    z0 = (minZ - head->minZ) / head->cellDepth;
    if (z0 < 0) {
        z0 = 0;
    }
    x1 = (maxX - head->minX) / head->cellWidth;
    if (x1 > head->cellsX - 1) {
        x1 = head->cellsX - 1;
    }
    z1 = (maxZ - head->minZ) / head->cellDepth;
    if (z1 > head->cellsZ - 1) {
        z1 = head->cellsZ - 1;
    }
    radiusSq = radius * radius;

    found = false;
    for (gz = z0; gz <= z1 && !found; gz++) {
        cell = &head->cells[x0 + gz * head->cellsX];
        for (gx = x0; gx <= x1 && !found; gx++, cell++) {
            index = &head->indices[cell->first];
            for (t = 0; t < cell->count && !found; t++, index++) {
                tri = &head->tris[*index];
                found = chkFace(tri->verts, &tri->normal, pos, radiusSq, &hit);
            }
        }
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }

    found = false;
    for (gz = z0; gz <= z1 && !found; gz++) {
        cell = &head->cells[x0 + gz * head->cellsX];
        for (gx = x0; gx <= x1 && !found; gx++, cell++) {
            index = &head->indices[cell->first];
            for (t = 0; t < cell->count && !found; t++, index++) {
                tri = &head->tris[*index];
                if (tri->flags & 7) {
                    found = chkEdges(tri, tri->verts, &tri->normal, pos, radiusSq, &hit);
                }
            }
        }
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }

    found = false;
    for (gz = z0; gz <= z1 && !found; gz++) {
        cell = &head->cells[x0 + gz * head->cellsX];
        for (gx = x0; gx <= x1 && !found; gx++, cell++) {
            index = &head->indices[cell->first];
            for (t = 0; t < cell->count && !found; t++, index++) {
                tri = &head->tris[*index];
                if (tri->flags & 7) {
                    found = chkVerts(tri, tri->verts, &tri->normal, pos, radiusSq, &hit);
                }
            }
        }
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }
    return false;
}

static bool checkHitMdl(GSvec* pos, f32 radius, CCD_HITMDL_HEAD* head, GSmtx* mtx, GSmtx* rot, GSvec* hitOut) {
    GSvec verts[3];
    GSvec normal;
    GSvec hit;
    GSvec cp;
    f32 radiusSq = radius * radius;
    CCD_TRI* tri;
    u32 i;
    s32 j;
    bool found;

    i = 0;
    tri = head->tris;
    found = false;
    for (; i < head->numTris && !found; i++, tri++) {
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, &tri->verts[j], &verts[j]);
        }
        PSMTXMultVec(rot, &tri->normal, &normal);
        found = chkFace(verts, &normal, pos, radiusSq, &hit);
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }

    i = 0;
    tri = head->tris;
    found = false;
    for (; i < head->numTris && !found; i++, tri++) {
        if (tri->flags & 7) {
            for (j = 0; j < 3; j++) {
                PSMTXMultVec(mtx, &tri->verts[j], &verts[j]);
            }
            PSMTXMultVec(rot, &tri->normal, &normal);
            found = chkEdges(tri, verts, &normal, pos, radiusSq, &hit);
        }
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }

    i = 0;
    tri = head->tris;
    found = false;
    for (; i < head->numTris && !found; i++, tri++) {
        if (tri->flags & 7) {
            for (j = 0; j < 3; j++) {
                PSMTXMultVec(mtx, &tri->verts[j], &verts[j]);
            }
            PSMTXMultVec(rot, &tri->normal, &normal);
            found = chkVerts(tri, verts, &normal, pos, radiusSq, &hit);
        }
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }
    return false;
}

static bool checkHitCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hitOut, bool alt) {
    GSvec cur;
    GSvec tmp;
    GSvec* tmpPtr;
    s32 iter;
    s32 hitCount;
    u32 i;
    CCD_FILEHEAD* head;
    CCD_OBJ* obj;
    CCD_HITMDL_HEAD* hit;
    bool enable;
    bool result;

    cur = *end;
    head = GScolsys2GetCCDFileHead();
    tmpPtr = &tmp;
    if (hitOut == 0) {
        tmpPtr = 0;
    }
    iter = 0;
    do {
        obj = head->objs;
        hitCount = 0;
        for (i = 0; i < head->numObjs; i++, obj++) {
            GScolsys2GetObjEnable(i, &enable);
            if (!enable) {
                continue;
            }
            if (alt) {
                hit = obj->hitAlt;
                if (hit == 0) {
                    continue;
                }
            } else {
                hit = obj->hit;
                if (hit == 0) {
                    continue;
                }
            }
            if (obj->flags & 1) {
                GSmtx mtx;
                GSmtx rotMtx;
                GScolsys2GetObjMatrix(&mtx, i);
                GScolsys2GetObjRotMatrix(&rotMtx, i);
                result = checkHitMdl(&cur, radius, hit, &mtx, &rotMtx, tmpPtr);
            } else {
                result = checkHitFixedMdl(&cur, radius, hit, tmpPtr);
            }
            if (result) {
                if (hitOut == 0) {
                    return true;
                }
                hitCount++;
                if (tmpPtr) {
                    cur.x = tmpPtr->x;
                    cur.y = tmpPtr->y;
                    cur.z = tmpPtr->z;
                }
            }
        }
        if (hitCount <= 0) {
            break;
        }
        iter++;
    } while (iter < 10);

    if (iter <= 0) {
        return false;
    }
    *hitOut = cur;
    return true;
}

extern "C" {
bool GScolsys2HitNpcCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hitOut) {
    GSvec p2;
    GSvec p1;
    GSvec dir;
    f32 step;
    f32 dist;
    f32 t2;
    f32 t;

    if (GScolsys2GetCCDFileHead() == 0) {
        return false;
    }
    dist = PSVECDistance(start, end);
    step = 0.0f;
    if (dist > step) {
        step = radius / dist;
        if (step > 1.0f) {
            step = 1.0f;
        }
    }
    PSVECSubtract(end, start, &dir);
    for (t = 0.0f; t < 1.0f; t += step) {
        t2 = t + step;
        if (t2 > 1.0f) {
            t2 = 1.0f;
        }
        PSVECScale(&dir, &p1, t);
        PSVECAdd(&p1, start, &p1);
        PSVECScale(&dir, &p2, t2);
        PSVECAdd(&p2, start, &p2);
        if (checkHitCollision(&p1, &p2, radius, hitOut, true)) {
            return true;
        }
        if (step <= 0.0f) {
            break;
        }
    }
    return false;
}

bool GScolsys2HitCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hitOut) {
    GSvec p2;
    GSvec p1;
    GSvec dir;
    f32 step;
    f32 dist;
    f32 t2;
    f32 t;

    if (GScolsys2GetCCDFileHead() == 0) {
        return false;
    }
    dist = PSVECDistance(start, end);
    step = 0.0f;
    if (dist > step) {
        step = radius / dist;
        if (step > 1.0f) {
            step = 1.0f;
        }
    }
    PSVECSubtract(end, start, &dir);
    for (t = 0.0f; t < 1.0f; t += step) {
        t2 = t + step;
        if (t2 > 1.0f) {
            t2 = 1.0f;
        }
        PSVECScale(&dir, &p1, t);
        PSVECAdd(&p1, start, &p1);
        PSVECScale(&dir, &p2, t2);
        PSVECAdd(&p2, start, &p2);
        if (checkHitCollision(&p1, &p2, radius, hitOut, false)) {
            return true;
        }
        if (step <= 0.0f) {
            break;
        }
    }
    return false;
}
}
