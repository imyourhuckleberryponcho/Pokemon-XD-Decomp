#include <dolphin/types.h>

struct Vec3 {
    f32 x, y, z;
};

struct GSvec : Vec3 {
    GSvec();
};

struct GSmtx {
    f32 m[3][4];
};

extern struct {
    GSvec v[3];
    Vec3 normal;
    u16 id;
} eventTriDummy;
#define EventTri __typeof__(eventTriDummy)

struct ThruTri {
    Vec3 v[3];
    Vec3 normal;
    u16 flags;
    u16 id;
};

struct GridCell {
    u32 first;
    u32 count;
};

struct CCD_THRUMDL_HEAD {
    ThruTri* tris;
    u32 numTris;
    GridCell* cells;
    u32* indices;
    u16 cellsX;
    u16 cellsZ;
    f32 cellWidth;
    f32 cellDepth;
    f32 minX;
    f32 minZ;
};

struct ThruObj {
    u8 unk0[0x2C];
    CCD_THRUMDL_HEAD* thru;
    u8 unk30[0xC];
    u16 flags;
    u8 pad3E[2];
};

struct CCDFileHead {
    ThruObj* objs;
    u32 numObjs;
};

extern "C" {
f32 PSVECDotProduct(const Vec3* a, const Vec3* b);
f32 PSVECSquareDistance(const Vec3* a, const Vec3* b);
f32 PSVECMag(const Vec3* v);
void PSVECSubtract(const Vec3* a, const Vec3* b, Vec3* dst);
void PSVECScale(const Vec3* src, Vec3* dst, f32 scale);
void PSVECAdd(const Vec3* a, const Vec3* b, Vec3* dst);
void PSMTXMultVec(const GSmtx* m, const Vec3* src, Vec3* dst);
CCDFileHead* GScolsys2GetCCDFileHead(void);
void GScolsys2GetObjEnable(u32 index, bool* enable);
void GScolsys2GetObjMatrix(GSmtx* m, u32 index);
void GScolsys2GetObjRotMatrix(GSmtx* m, u32 index);
bool GScolsys2UtilGetCpPlaneLine(Vec3* cp, f32* t, Vec3* normal, Vec3* tri, Vec3* start, Vec3* end);
f32 GScolsys2UtilGetCpLinePoint(Vec3* out, Vec3* start, Vec3* end, Vec3* point);
f32 GScolsy2UtilGetSidePlanePoint(Vec3* normal, Vec3* verts, Vec3* point);
void GScolsy2UtilGetCpPlanePoint(Vec3* out, Vec3* normal, Vec3* verts, Vec3* point);
bool GScolsy2UtilChkInTri(Vec3* p, Vec3* tri, Vec3* normal);
}

static inline bool chkFace(Vec3* verts, Vec3* normal, Vec3* pos, f32 radiusSq) {
    Vec3 cp;

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
    return true;
}

static inline bool chkEdges(ThruTri* tri, Vec3* verts, Vec3* normal, Vec3* pos, f32 radiusSq) {
    u16 mask[3] = {1, 2, 4};
    u16 flags;
    s32 j;
    Vec3 cp;

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
                return true;
            }
        }
    }
    return false;
}

static inline bool chkVerts(ThruTri* tri, Vec3* verts, Vec3* normal, Vec3* pos, f32 radiusSq) {
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
            return true;
        }
    }
    return false;
}

static inline void copyEvent(EventTri* dst, EventTri* src) {
    dst->v[0].x = src->v[0].x; dst->v[0].y = src->v[0].y; dst->v[0].z = src->v[0].z;
    dst->v[1].x = src->v[1].x; dst->v[1].y = src->v[1].y; dst->v[1].z = src->v[1].z;
    dst->v[2].x = src->v[2].x; dst->v[2].y = src->v[2].y; dst->v[2].z = src->v[2].z;
    dst->normal = src->normal;
    dst->id = src->id;
}

static int getMdlEventListPass(GSvec* start, GSvec* end, CCD_THRUMDL_HEAD* head, GSmtx* mtx, GSmtx* rot,
                               EventTri* out) {
    EventTri* cur;
    ThruTri* tri;
    u32 i;
    int count;
    Vec3 verts[3];
    Vec3 normal;
    Vec3 dir;
    Vec3 cp;
    f32 t;

    count = 0;
    PSVECSubtract(end, start, &dir);
    cur = out;
    i = 0;
    tri = head->tris;
    for (; i < head->numTris && count < 4; i++, tri++) {
        int j;

        for (j = 0; j < count; j++) {
            if (tri->id == out[j].id) {
                break;
            }
        }
        if (j < count) {
            continue;
        }
        PSMTXMultVec(rot, &tri->normal, &normal);
        if (PSVECDotProduct(&normal, &dir) >= 0.0f) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, &tri->v[j], &verts[j]);
        }
        bool hit;
        if (!GScolsys2UtilGetCpPlaneLine(&cp, &t, &normal, verts, start, end)) {
            hit = false;
        } else if (t < 0.0f || t > 1.0f) {
            hit = false;
        } else if (!GScolsy2UtilChkInTri(&cp, verts, &normal)) {
            hit = false;
        } else {
            hit = true;
        }
        if (hit) {
            u16 id = tri->id;
            count++;
            cur->v[0].x = verts[0].x; cur->v[0].y = verts[0].y; cur->v[0].z = verts[0].z;
            cur->v[1].x = verts[1].x; cur->v[1].y = verts[1].y; cur->v[1].z = verts[1].z;
            cur->v[2].x = verts[2].x; cur->v[2].y = verts[2].y; cur->v[2].z = verts[2].z;
            cur->normal = normal;
            cur->id = id;
            cur++;
        }
    }
    return count;
}

static inline int getFixedMdlEventListPass(GSvec* start, GSvec* end, CCD_THRUMDL_HEAD* mdl, EventTri* temp) {
    u32 m;
    Vec3 cp;
    f32 t;
    Vec3 dir;
    int j;
    int n;
    ThruTri* tri;
    Vec3* normal;

    PSVECSubtract(end, start, &dir);
    n = 0;
    tri = mdl->tris;
    m = 0;
    for (; m < mdl->numTris && n < 4; m++, tri++) {
        for (j = 0; j < n; j++) {
            if (tri->id == temp[j].id) {
                break;
            }
        }
        if (j < n) {
            continue;
        }
        if (PSVECDotProduct(&tri->normal, &dir) >= 0.0f) {
            continue;
        }
        normal = &tri->normal;
        bool hit;
        if (!GScolsys2UtilGetCpPlaneLine(&cp, &t, normal, tri->v, start, end)) {
            hit = false;
        } else if (t < 0.0f || t > 1.0f) {
            hit = false;
        } else if (!GScolsy2UtilChkInTri(&cp, tri->v, normal)) {
            hit = false;
        } else {
            hit = true;
        }
        if (hit) {
            u16 id = tri->id;
            n++;
            (temp)->v[0].x = tri->v[0].x; (temp)->v[0].y = tri->v[0].y; (temp)->v[0].z = tri->v[0].z;
            (temp)->v[1].x = tri->v[1].x; (temp)->v[1].y = tri->v[1].y; (temp)->v[1].z = tri->v[1].z;
            (temp)->v[2].x = tri->v[2].x; (temp)->v[2].y = tri->v[2].y; (temp)->v[2].z = tri->v[2].z;
            (temp)->normal = tri->normal;
            (temp)->id = id;
            (temp)++;
        }
    }
    return n;
}

extern "C" {
int GScolsys2ThruPassEventID(GSvec* start, GSvec* end, EventTri* out) {
    u32 i;
    int count = 0;
    CCDFileHead* head;
    ThruObj* obj;
    EventTri temp[4];
    Vec3 dir;
    bool enable;
    GSmtx mtx;
    GSmtx rot;

    head = GScolsys2GetCCDFileHead();
    if (head == 0) {
        return 0;
    }
    obj = head->objs;
    for (i = 0; i < head->numObjs && count < 4; i++, obj++) {
        EventTri* src;
        int n;
        int k;
        CCD_THRUMDL_HEAD* mdl;

        GScolsys2GetObjEnable(i, &enable);
        if (!enable) {
            continue;
        }
        mdl = obj->thru;
        if (mdl == 0) {
            continue;
        }
        if (obj->flags & 1) {
            GScolsys2GetObjMatrix(&mtx, i);
            GScolsys2GetObjRotMatrix(&rot, i);
            n = getMdlEventListPass(start, end, mdl, &mtx, &rot, temp);
        } else {
            n = getFixedMdlEventListPass(start, end, mdl, temp);
        }
        src = temp;
        for (k = 0; k < n && count < 4; src++, k++) {
            int j;
            for (j = 0; j < count; j++) {
                u32 rf_t = out[j].id;
                if (rf_t == src->id) {
                    break;
                }
            }
            if (j >= count) {
                copyEvent(&out[count++], src);
            }
        }
    }
    return count;
}
}

static int getFixedMdlEventList(GSvec* pos, GSvec* dir, f32 radius, CCD_THRUMDL_HEAD* head, EventTri* out) {
    f32 minX, minZ, maxX, maxZ;
    s32 x0, z0, x1, z1;
    s32 gx, gz;
    EventTri* cur;
    int count;
    int j;
    f32 radiusSq;
    GridCell* cell;
    u32* index;
    ThruTri* tri;
    u32 t;

    count = 0;
    minX = pos->x - radius;
    maxX = pos->x + radius;
    minZ = pos->z - radius;
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

    cur = out;
    for (gz = z0; gz <= z1 && count < 4; gz++) {
        cell = &head->cells[x0 + gz * head->cellsX];
        for (gx = x0; gx <= x1 && count < 4; gx++, cell++) {
            index = &head->indices[cell->first];
            for (t = 0; t < cell->count && count < 4; t++, index++) {
                tri = &head->tris[*index];
                for (j = 0; j < count; j++) {
                    if (tri->id == out[j].id) {
                        break;
                    }
                }
                if (j < count) {
                    continue;
                }
                if (PSVECDotProduct(&tri->normal, dir) >= 0.0f) {
                    continue;
                }
                if (chkFace(tri->v, &tri->normal, pos, radiusSq)) {
                    u16 id = tri->id;
                    cur = &out[count];
                    count++;
                    cur->v[0].x = tri->v[0].x; cur->v[0].y = tri->v[0].y; cur->v[0].z = tri->v[0].z;
                    cur->v[1].x = tri->v[1].x; cur->v[1].y = tri->v[1].y; cur->v[1].z = tri->v[1].z;
                    cur->v[2].x = tri->v[2].x; cur->v[2].y = tri->v[2].y; cur->v[2].z = tri->v[2].z;
                    cur->normal = tri->normal;
                    cur->id = id;
                }
            }
        }
    }

    cur = out + count;
    for (gz = z0; gz <= z1 && count < 4; gz++) {
        cell = &head->cells[x0 + gz * head->cellsX];
        for (gx = x0; gx <= x1 && count < 4; gx++, cell++) {
            index = &head->indices[cell->first];
            for (t = 0; t < cell->count && count < 4; t++, index++) {
                tri = &head->tris[*index];
                if (!(tri->flags & 7)) {
                    continue;
                }
                for (j = 0; j < count; j++) {
                    if (tri->id == out[j].id) {
                        break;
                    }
                }
                if (j < count) {
                    continue;
                }
                if (PSVECDotProduct(&tri->normal, dir) >= 0.0f) {
                    continue;
                }
                if (chkEdges(tri, tri->v, &tri->normal, pos, radiusSq)) {
                    u16 id = tri->id;
                    cur = &out[count];
                    count++;
                    cur->v[0].x = tri->v[0].x; cur->v[0].y = tri->v[0].y; cur->v[0].z = tri->v[0].z;
                    cur->v[1].x = tri->v[1].x; cur->v[1].y = tri->v[1].y; cur->v[1].z = tri->v[1].z;
                    cur->v[2].x = tri->v[2].x; cur->v[2].y = tri->v[2].y; cur->v[2].z = tri->v[2].z;
                    cur->normal = tri->normal;
                    cur->id = id;
                }
            }
        }
    }

    cur = out + count;
    for (gz = z0; gz <= z1 && count < 4; gz++) {
        cell = &head->cells[x0 + gz * head->cellsX];
        for (gx = x0; gx <= x1 && count < 4; gx++, cell++) {
            index = &head->indices[cell->first];
            for (t = 0; t < cell->count && count < 4; t++, index++) {
                tri = &head->tris[*index];
                if (!(tri->flags & 7)) {
                    continue;
                }
                for (j = 0; j < count; j++) {
                    if (tri->id == out[j].id) {
                        break;
                    }
                }
                if (j < count) {
                    continue;
                }
                if (PSVECDotProduct(&tri->normal, dir) >= 0.0f) {
                    continue;
                }
                if (chkVerts(tri, tri->v, &tri->normal, pos, radiusSq)) {
                    u16 id = tri->id;
                    cur = &out[count];
                    count++;
                    cur->v[0].x = tri->v[0].x; cur->v[0].y = tri->v[0].y; cur->v[0].z = tri->v[0].z;
                    cur->v[1].x = tri->v[1].x; cur->v[1].y = tri->v[1].y; cur->v[1].z = tri->v[1].z;
                    cur->v[2].x = tri->v[2].x; cur->v[2].y = tri->v[2].y; cur->v[2].z = tri->v[2].z;
                    cur->normal = tri->normal;
                    cur->id = id;
                }
            }
        }
    }
    return count;
}

static int getMdlEventList(GSvec* pos, GSvec* dir, f32 radius, CCD_THRUMDL_HEAD* head, GSmtx* mtx, GSmtx* rot,
                           EventTri* out) {
    Vec3 verts[3];
    Vec3 normal;
    f32 radiusSq = radius * radius;
    int count;
    ThruTri* tri;
    u32 i;
    EventTri* cur;
    s32 j;

    count = 0;
    cur = out;
    tri = head->tris;
    for (i = 0; i < head->numTris && count < 4; i++, tri++) {
        for (j = 0; j < count; j++) {
            if (tri->id == out[j].id) {
                break;
            }
        }
        if (j < count) {
            continue;
        }
        PSMTXMultVec(rot, &tri->normal, &normal);
        if (PSVECDotProduct(&normal, dir) >= 0.0f) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, &tri->v[j], &verts[j]);
        }
        if (chkFace(verts, &normal, pos, radiusSq)) {
            u16 id = tri->id;
            count++;
            cur->v[0].x = verts[0].x; cur->v[0].y = verts[0].y; cur->v[0].z = verts[0].z;
            cur->v[1].x = verts[1].x; cur->v[1].y = verts[1].y; cur->v[1].z = verts[1].z;
            cur->v[2].x = verts[2].x; cur->v[2].y = verts[2].y; cur->v[2].z = verts[2].z;
            cur->normal = normal;
            cur->id = id;
            cur++;
        }
    }

    cur = out + count;
    tri = head->tris;
    for (i = 0; i < head->numTris && count < 4; i++, tri++) {
        if (!(tri->flags & 7)) {
            continue;
        }
        for (j = 0; j < count; j++) {
            if (tri->id == out[j].id) {
                break;
            }
        }
        if (j < count) {
            continue;
        }
        PSMTXMultVec(rot, &tri->normal, &normal);
        if (PSVECDotProduct(&normal, dir) >= 0.0f) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, &tri->v[j], &verts[j]);
        }
        if (chkEdges(tri, verts, &normal, pos, radiusSq)) {
            u16 id = tri->id;
            count++;
            cur->v[0].x = verts[0].x; cur->v[0].y = verts[0].y; cur->v[0].z = verts[0].z;
            cur->v[1].x = verts[1].x; cur->v[1].y = verts[1].y; cur->v[1].z = verts[1].z;
            cur->v[2].x = verts[2].x; cur->v[2].y = verts[2].y; cur->v[2].z = verts[2].z;
            cur->normal = normal;
            cur->id = id;
            cur++;
        }
    }

    cur = out + count;
    tri = head->tris;
    for (i = 0; i < head->numTris && count < 4; i++, tri++) {
        if (!(tri->flags & 7)) {
            continue;
        }
        for (j = 0; j < count; j++) {
            if (tri->id == out[j].id) {
                break;
            }
        }
        if (j < count) {
            continue;
        }
        PSMTXMultVec(rot, &tri->normal, &normal);
        if (PSVECDotProduct(&normal, dir) >= 0.0f) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, &tri->v[j], &verts[j]);
        }
        if (chkVerts(tri, verts, &normal, pos, radiusSq)) {
            u16 id = tri->id;
            count++;
            cur->v[0].x = verts[0].x; cur->v[0].y = verts[0].y; cur->v[0].z = verts[0].z;
            cur->v[1].x = verts[1].x; cur->v[1].y = verts[1].y; cur->v[1].z = verts[1].z;
            cur->v[2].x = verts[2].x; cur->v[2].y = verts[2].y; cur->v[2].z = verts[2].z;
            cur->normal = normal;
            cur->id = id;
            cur++;
        }
    }
    return count;
}

static int getEventList(GSvec* pos, GSvec* dir, f32 radius, EventTri* out) {
    CCDFileHead* head;
    ThruObj* obj;
    u32 i;
    int count = 0;
    EventTri temp[4];
    bool enable;
    GSmtx mtx;
    GSmtx rot;

    head = GScolsys2GetCCDFileHead();
    obj = head->objs;
    for (i = 0; i < head->numObjs && count < 4; i++, obj++) {
        CCD_THRUMDL_HEAD* mdl;
        int n;
        int k;

        GScolsys2GetObjEnable(i, &enable);
        if (!enable) {
            continue;
        }
        mdl = obj->thru;
        if (mdl == 0) {
            continue;
        }
        if (obj->flags & 1) {
            GScolsys2GetObjMatrix(&mtx, i);
            GScolsys2GetObjRotMatrix(&rot, i);
            n = getMdlEventList(pos, dir, radius, mdl, &mtx, &rot, temp);
        } else {
            n = getFixedMdlEventList(pos, dir, radius, mdl, temp);
        }
        for (k = 0; k < n && count < 4; k++) {
            int j;
            for (j = 0; j < count; j++) {
                if (out[j].id == temp[k].id) {
                    break;
                }
            }
            if (j >= count) {
                copyEvent(&out[count++], &temp[k]);
            }
        }
    }
    return count;
}

extern "C" {
int GScolsys2ThruGetEventID(GSvec* start, GSvec* end, f32 radius, EventTri* out) {
    EventTri temp[4];
    Vec3 dir;
    f32 t;
    int count = 0;
    int n;
    EventTri* src;
    int k;
    int j;
    f32 mag;
    f32 step;
    Vec3 p;
    f32 t2;

    if (GScolsys2GetCCDFileHead() == 0) {
        return 0;
    }
    PSVECSubtract(end, start, &dir);
    mag = PSVECMag(&dir);
    if (mag <= 0.0f) {
        return 0;
    }
    step = radius / mag;
    if (step > 1.0f) {
        step = 1.0f;
    }
    for (t = 0.0f; t < 1.0f && count < 4; t += step) {
        t2 = t + step;
        if (t2 > 1.0f) {
            t2 = 1.0f;
        }
        PSVECScale(&dir, &p, t2);
        PSVECAdd(&p, start, &p);
        n = getEventList((GSvec*)&p, (GSvec*)&dir, radius, temp);
        src = temp;
        for (k = 0; k < n && count < 4; src++, k++) {
            for (j = 0; j < count; j++) {
                if (src->id == out[j].id) {
                    break;
                }
            }
            if (j >= count) {
                copyEvent(&out[count++], src);
            }
        }
        if (step <= 0.0f) {
            break;
        }
    }
    return count;
}
}
