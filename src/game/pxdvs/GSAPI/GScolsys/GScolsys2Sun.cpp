#include <dolphin/types.h>
#include <game/gcdata.h>
#include <game/gcptr.h>

struct GSvec {
    f32 x, y, z;
};

typedef f32 GSmtx[3][4];

struct ColTri {
    gc_vec(GSvec) v[3];
    gc_vec(GSvec) normal;
};

struct ColMesh {
    gc_ptr32(ColTri) tris;
    gc_be32 numTris;
};

struct ColObj {
    u8 unk0[0x38];
    gc_ptr32(ColMesh) mesh;
    u8 unk3C[4];
};

struct CCDFileHead {
    gc_ptr32(ColObj) objs;
    gc_be32 numObjs;
};
#ifndef __MWERKS__
static_assert(sizeof(ColTri) == 0x30, "ColTri stride in the CCD file");
static_assert(sizeof(ColObj) == 0x40, "ColObj stride in the CCD file");
#endif

extern "C" {
f32 PSVECSquareDistance(const GSvec* a, const GSvec* b);
f32 PSVECDistance(const GSvec* a, const GSvec* b);
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* dst);
void PSMTXMultVec(const GSmtx m, const GSvec* src, GSvec* dst);
void* memset(void* dst, int c, unsigned long n);
CCDFileHead* GScolsys2GetCCDFileHead(void);
void GScolsys2GetObjEnable(u32 index, bool* enable);
void GScolsys2GetObjMatrix(GSmtx m, u32 index);
void GScolsys2GetObjRotMatrix(GSmtx m, u32 index);
bool GScolsys2UtilGetCpPlaneLine(GSvec* cp, f32* t, GSvec* normal, GSvec* tri, GSvec* start, GSvec* end);
bool GScolsy2UtilChkInTri(GSvec* p, GSvec* tri, GSvec* normal);
}

static int getCpSegPolyArray(bool* hits, GSvec* start, GSvec* ends, u32 num, GSvec* tri, GSvec* normal) {
    u32 i;
    bool hit = false;
    bool valid = true;
    GSvec cp;
    f32 t;
    GSvec* end = ends;

    for (i = 0; i < num; i++, end++, hits++) {
        if (*hits) {
            continue;
        }
        if (PSVECSquareDistance(start, end) < 0.00001f) {
            valid = false;
        } else if (!GScolsys2UtilGetCpPlaneLine(&cp, &t, normal, tri, start, end)) {
            valid = false;
        } else if (t < 0.0f || t > 1.0f) {
            valid = false;
        } else if (!GScolsy2UtilChkInTri(&cp, tri, normal)) {
            valid = false;
        } else {
            hit = true;
            *hits = true;
        }
    }
    if (valid) {
        return -1;
    }
    return hit != false;
}

static inline bool checkSegTri(GSvec* start, GSvec* end, GSvec* tri, GSvec* normal) {
    GSvec cp;
    f32 t;
    if (!GScolsys2UtilGetCpPlaneLine(&cp, &t, normal, tri, start, end)) {
        return false;
    }
    if (t < 0.0f || t > 1.0f) {
        return false;
    }
    if (!GScolsy2UtilChkInTri(&cp, tri, normal)) {
        return false;
    }
    return true;
}

static inline int checkMeshArray(bool* hits, GSvec* start, GSvec* ends, u32 num, ColMesh* mesh, GSmtx mtx, GSmtx rot,
                                  GSvec* normal, GSvec* verts) {
    u32 j;
    ColTri* tri = mesh->tris;
    int result = 0;
    for (j = 0; j < mesh->numTris; j++, tri++) {
        int k;
        int res;
        PSMTXMultVec(rot, GC_VEC3P(GSvec, &tri->normal), normal);
        for (k = 0; k < 3; k++) {
            PSMTXMultVec(mtx, GC_VEC3P(GSvec, &tri->v[k]), &verts[k]);
        }
        res = getCpSegPolyArray(hits, start, ends, num, verts, normal);
        if (res < 0) {
            return -1;
        }
        if (res > 0) {
            result = 1;
        }
    }
    return result;
}

extern "C" {

static inline ColMesh * colObjMesh(ColObj * p) { return p->mesh; }

bool GScolsys2SunArray(bool* hits, GSvec* start, GSvec* ends, u32 num) {
    bool found;
    CCDFileHead* head;
    int result;
    u32 i;
    ColObj* obj;

    if (GScolsys2GetCCDFileHead() == NULL) {
        return false;
    }
    memset(hits, 0, num);
    found = false;
    head = GScolsys2GetCCDFileHead();
    obj = head->objs;
    for (i = 0; i < head->numObjs; i++, obj++) {
        GSmtx rot;
        GSmtx mtx;
        bool enable;
        GSvec normal;
        GSvec verts[3];
        ColMesh* mesh;

        GScolsys2GetObjEnable(i, &enable);
        if (!enable) {
            continue;
        }
        mesh = colObjMesh(obj);
        if (mesh == NULL) {
            continue;
        }
        GScolsys2GetObjMatrix(mtx, i);
        GScolsys2GetObjRotMatrix(rot, i);
        result = checkMeshArray(hits, start, ends, num, mesh, mtx, rot, &normal, verts);
        if (result < 0) {
            found = true;
            break;
        }
        if (result > 0) {
            found = true;
        }
    }
    return found;
}

bool GScolsys2Sun(GSvec* start, GSvec* end) {
    CCDFileHead* head;
    ColObj* obj;
    u32 i;
    GSvec dir;

    if (GScolsys2GetCCDFileHead() == NULL) {
        return false;
    }
    if (PSVECDistance(end, start) <= 0.0f) {
        return false;
    }
    head = GScolsys2GetCCDFileHead();
    PSVECSubtract(end, start, &dir);
    obj = head->objs;
    for (i = 0; i < head->numObjs; i++, obj++) {
        GSmtx rot;
        u32 j;
        GSmtx mtx;
        bool enable;
        GSvec normal;
        GSvec verts[3];
        ColTri* tri;
        ColMesh* mesh;
        bool hit;

        GScolsys2GetObjEnable(i, &enable);
        if (!enable) {
            continue;
        }
        mesh = obj->mesh;
        if (mesh == NULL) {
            continue;
        }
        GScolsys2GetObjMatrix(mtx, i);
        GScolsys2GetObjRotMatrix(rot, i);
        tri = mesh->tris;
        for (j = 0; j < mesh->numTris; j++, tri++) {
            int k;
            PSMTXMultVec(rot, GC_VEC3P(GSvec, &tri->normal), &normal);
            for (k = 0; k < 3; k++) {
                PSMTXMultVec(mtx, GC_VEC3P(GSvec, &tri->v[k]), &verts[k]);
            }
            if (checkSegTri(start, end, verts, &normal)) {
                hit = true;
                goto done;
            }
        }
        hit = false;
    done:
        if (hit) {
            return true;
        }
    }
    return false;
}

}
