// WIP (NonMatching): logic is complete; register allocation and stack layout still differ in all
// three functions (the original keeps the parameters in the highest registers in the Array/Sun loops).
#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

typedef f32 GSmtx[3][4];

struct ColTri {
    GSvec v[3];
    GSvec normal;
};

struct ColMesh {
    ColTri* tris;
    u32 numTris;
};

struct ColObj {
    u8 unk0[0x38];
    ColMesh* mesh;
    u8 unk3C[4];
};

struct CCDFileHead {
    ColObj* objs;
    u32 numObjs;
};

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

// Returns -1 if any segment can't be tested, else whether any new segment hit the triangle.
static int getCpSegPolyArray(bool* hits, GSvec* start, GSvec* ends, unsigned long num, GSvec* tri, GSvec* normal) {
    u32 i;
    bool hit = false;
    bool valid = true;
    GSvec cp;
    f32 t;

    for (i = 0; i < num; i++, ends++, hits++) {
        if (*hits) {
            continue;
        }
        if (PSVECSquareDistance(start, ends) < 0.00001f) {
            valid = false;
        } else if (!GScolsys2UtilGetCpPlaneLine(&cp, &t, normal, tri, start, ends)) {
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

extern "C" {

bool GScolsys2SunArray(bool* hits, GSvec* start, GSvec* ends, u32 num) {
    bool found;
    CCDFileHead* head;
    ColObj* obj;
    int result;
    u32 i;

    if (GScolsys2GetCCDFileHead() == NULL) {
        return false;
    }
    memset(hits, 0, num);
    found = false;
    head = GScolsys2GetCCDFileHead();
    obj = head->objs;
    for (i = 0; i < head->numObjs; i++, obj++) {
        bool enable;
        u32 j;
        GSmtx mtx;
        GSmtx rot;
        GSvec normal;
        GSvec verts[3];
        ColTri* tri;
        ColMesh* mesh;

        GScolsys2GetObjEnable(i, &enable);
        if (!enable) {
            continue;
        }
        mesh = obj->mesh;
        if (mesh == NULL) {
            continue;
        }
        tri = mesh->tris;
        GScolsys2GetObjMatrix(mtx, i);
        GScolsys2GetObjRotMatrix(rot, i);
        result = 0;
        for (j = 0; j < mesh->numTris; j++, tri++) {
            int k;
            int res;
            PSMTXMultVec(rot, &tri->normal, &normal);
            for (k = 0; k < 3; k++) {
                PSMTXMultVec(mtx, &tri->v[k], &verts[k]);
            }
            res = getCpSegPolyArray(hits, start, ends, num, verts, &normal);
            if (res < 0) {
                result = -1;
                break;
            }
            if (res > 0) {
                result = 1;
            }
        }
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
            PSMTXMultVec(rot, &tri->normal, &normal);
            for (k = 0; k < 3; k++) {
                PSMTXMultVec(mtx, &tri->v[k], &verts[k]);
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
