#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

typedef f32 GSmtx[3][4];

struct CCD_TRI {
    GSvec verts[3];  // 0x00
    GSvec normal;    // 0x24
    u8 attr;         // 0x30
    u8 layer;        // 0x31
    u8 pad32[2];
};

struct CCD_GRID_CELL {
    u32 first;
    u32 count;
};

struct CCD_GRID {
    CCD_TRI* tris;        // 0x00
    u32 numTris;          // 0x04
    CCD_GRID_CELL* cells; // 0x08
    u32* indices;         // 0x0C
    u16 cellsX;           // 0x10
    u16 cellsZ;           // 0x12
    f32 cellWidth;        // 0x14
    f32 cellDepth;        // 0x18
    f32 minX;             // 0x1C
    f32 minZ;             // 0x20
};

struct CCD_TRILIST {
    CCD_TRI* tris;
    u32 count;
};

struct CCD_OBJ {
    u8 unk0[0x24];
    void* walk;      // 0x24
    u8 unk28[0x14];
    u16 flags;       // 0x3C
    u8 unk3E[2];
};

struct CCD_FILEHEAD {
    CCD_OBJ* objs;
    u32 numObjs;
};

struct GSwalkHit {
    f32 height;
    u16 attrHi;
    u16 attrLo;
    u8 layer;
    u8 subLayer;
    u8 pad[2];
};

extern "C" {
void PSMTXMultVec(const GSmtx m, const GSvec* src, GSvec* dst);
CCD_FILEHEAD* GScolsys2GetCCDFileHead(void);
void GScolsys2GetObjEnable(u32 index, bool* enable);
void GScolsys2GetObjMatrix(GSmtx m, u32 index);
void GScolsys2GetObjRotMatrix(GSmtx m, u32 index);
s32 GScolsys2WalkGetHeight(GSvec* pos, GSwalkHit* hits);
}

static bool getCpPolyVec(GSvec* out, GSvec* point, GSvec* vertices, GSvec* plane);

static inline bool addHit(GSwalkHit* hits, s32 count, GSwalkHit* dst, f32 height, CCD_TRI* tri) {
    s32 i;
    for (i = 0; i < count; i++, hits++) {
        if (height == hits->height) {
            break;
        }
    }
    if (i < count) {
        return false;
    }
    dst->height = height;
    dst->attrHi = ((tri->attr >> 4) == 0xF) ? 0xFFFF : (tri->attr >> 4);
    dst->attrLo = ((tri->attr & 0xF) == 0xF) ? 0xFFFF : (tri->attr & 0xF);
    dst->layer = tri->layer >> 4;
    dst->subLayer = tri->layer & 0xF;
    return true;
}

extern "C" {
BOOL GScolsys2WalkGetLayer(GSvec* pos, u8* layer, u8* subLayer) {
    GSwalkHit hits[8];
    s32 count;
    s32 i;
    s32 closest;
    f32 distance;
    f32 closestDistance;

    count = GScolsys2WalkGetHeight(pos, hits);
    if (count <= 0) {
        return FALSE;
    }

    distance = pos->y - hits[0].height;
    distance = distance > 0.0f ? distance : -distance;
    closest = 0;
    closestDistance = distance;
    for (i = 1; i < count; i++) {
        distance = pos->y - hits[i].height;
        distance = distance > 0.0f ? distance : -distance;
        if (closestDistance > distance) {
            closest = i;
            closestDistance = distance;
        }
    }

    *layer = hits[closest].layer;
    *subLayer = hits[closest].subLayer;
    return TRUE;
}
}

static bool getCpPolyVec(GSvec* out, GSvec* point, GSvec* vertices, GSvec* plane) {
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    s32 i;

    minX = minZ = 1000000.0f;
    maxX = maxZ = -1000000.0f;
    for (i = 0; i < 3; i++) {
        if (minX > vertices[i].x) {
            minX = vertices[i].x;
        }
        if (minZ > vertices[i].z) {
            minZ = vertices[i].z;
        }
        if (maxX < vertices[i].x) {
            maxX = vertices[i].x;
        }
        if (maxZ < vertices[i].z) {
            maxZ = vertices[i].z;
        }
    }

    if (minX > point->x || minZ > point->z || maxX < point->x || maxZ < point->z) {
        return false;
    }

    for (i = 0; i < 3; i++) {
        s32 next = i + 1;
        if (next >= 3) {
            next = 0;
        }
        if ((vertices[next].x - vertices[i].x) * (point->z - vertices[i].z) -
                (vertices[next].z - vertices[i].z) * (point->x - vertices[i].x) >
            0.0f) {
            return false;
        }
    }

    if (0.0f == plane->y) {
        return false;
    }
    out->x = point->x;
    out->y = point->y + -(plane->y * (point->y - vertices[0].y) + plane->x * (point->x - vertices[0].x) +
                          plane->z * (point->z - vertices[0].z)) /
                            plane->y;
    out->z = point->z;
    return true;
}

extern "C" {
s32 GScolsys2WalkGetHeight(GSvec* pos, GSwalkHit* outHits) {
    CCD_FILEHEAD* head;
    CCD_OBJ* obj;
    s32 total;
    u32 objIndex;
    bool enable;
    total = 0;

    head = GScolsys2GetCCDFileHead();
    if (head == 0) {
        return 0;
    }

    obj = head->objs;
    for (objIndex = 0; objIndex < head->numObjs && total < 8; objIndex++, obj++) {
        GSwalkHit temp[8];
        GSwalkHit* dst;
        GSwalkHit* src;
        s32 count;
        s32 i;
        void* walk;
        GSvec hit;

        GScolsys2GetObjEnable(objIndex, &enable);
        if (!enable) {
            continue;
        }
        walk = obj->walk;
        if (walk == 0) {
            continue;
        }

        if (obj->flags & 1) {
            GSmtx mtx;
            GSmtx rotMtx;
            GSvec verts[3];
            GSvec normal;
            CCD_TRILIST* list = (CCD_TRILIST*)walk;
            CCD_TRI* tri;
            u32 t;

            GScolsys2GetObjMatrix(mtx, objIndex);
            GScolsys2GetObjRotMatrix(rotMtx, objIndex);
            count = 0;
            tri = list->tris;
            dst = temp;
            for (t = 0; t < list->count && count < 8; t++, tri++) {
                for (i = 0; i < 3; i++) {
                    PSMTXMultVec(mtx, &tri->verts[i], &verts[i]);
                }
                PSMTXMultVec(rotMtx, &tri->normal, &normal);
                if (!getCpPolyVec(&hit, pos, verts, &normal)) {
                    continue;
                }
                if (addHit(temp, count, dst, hit.y, tri)) {
                    dst++;
                    count++;
                }
            }
        } else {
            CCD_GRID* grid = (CCD_GRID*)walk;
            CCD_GRID_CELL* cell;
            u32* index;
            CCD_TRI* tri;
            s32 cx;
            s32 cz;
            u32 t;

            count = 0;
            cx = (pos->x - grid->minX) / grid->cellWidth;
            if (cx < 0 || cx >= grid->cellsX) {
                goto copy;
            }
            cz = (pos->z - grid->minZ) / grid->cellDepth;
            if (cz < 0 || cz >= grid->cellsZ) {
                goto copy;
            }
            cell = &grid->cells[cx + cz * grid->cellsX];
            index = &grid->indices[cell->first];
            dst = temp;
            for (t = 0; t < cell->count && count < 8; t++, index++) {
                tri = &grid->tris[*index];
                if (!getCpPolyVec(&hit, pos, tri->verts, &tri->normal)) {
                    continue;
                }
                if (addHit(temp, count, dst, hit.y, tri)) {
                    dst++;
                    count++;
                }
            }
        }
    copy:
        src = temp;
        for (i = 0; i < count && total < 8; i++) {
            *outHits++ = *src++;
            total++;
        }
    }

    return total;
}
}
