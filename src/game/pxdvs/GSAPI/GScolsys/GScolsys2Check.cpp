#include <dolphin/types.h>

struct Vec3 {
    f32 x, y, z;
};

struct GSvec : Vec3 {
    GSvec();
};

struct GSnorm : Vec3 {};

struct GSmtx {
    f32 m[3][4];
};

extern struct {
    GSvec v[3];
    GSnorm normal;
    u16 id;
} eventTriDummy;
#define EventTri __typeof__(eventTriDummy)

struct CheckTri {
    Vec3 v[3];
    Vec3 normal;
    u16 id;
};

struct CCD_CHECKMDL_HEAD {
    CheckTri* tris;
    u32 numTris;
};

struct CheckObj {
    u8 unk0[0x30];
    CCD_CHECKMDL_HEAD* mdl;
    u8 unk34[0xc];
};

struct CCDFileHead {
    CheckObj* objs;
    u32 numObjs;
};

extern "C" {
f32 PSVECDistance(const Vec3* a, const Vec3* b);
f32 PSVECDotProduct(const Vec3* a, const Vec3* b);
void PSVECSubtract(const Vec3* a, const Vec3* b, Vec3* dst);
void PSMTXMultVec(const GSmtx* m, const Vec3* src, Vec3* dst);
CCDFileHead* GScolsys2GetCCDFileHead(void);
void GScolsys2GetObjEnable(u32 index, bool* enable);
void GScolsys2GetObjMatrix(GSmtx* m, u32 index);
void GScolsys2GetObjRotMatrix(GSmtx* m, u32 index);
bool GScolsys2UtilGetCpPlaneLine(Vec3* cp, f32* t, Vec3* normal, Vec3* tri, Vec3* start, Vec3* end);
bool GScolsy2UtilChkInTri(Vec3* p, Vec3* tri, Vec3* normal);
}

static bool getMdlEventList(GSvec* start, GSvec* end, GSvec* dir, CCD_CHECKMDL_HEAD* mdl, GSmtx* mtx, GSmtx* rot, EventTri* out) {
    EventTri* cur = out;
    CheckTri* tri;
    u32 i;
    int count;

    count = 0;
    i = 0;
    tri = mdl->tris;

    for (; i < mdl->numTris && count < 4; i++, tri++) {
        Vec3 normal;
        Vec3 verts[3];
        Vec3 cp;
        f32 t;
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
        if (PSVECDotProduct(&normal, dir) >= 0.0f) {
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
            cur->normal.x = normal.x; cur->normal.y = normal.y; cur->normal.z = normal.z;
            cur->id = id;
            cur++;
        }
    }
    return count != 0;
}

static int getEventList(GSvec* start, GSvec* end, EventTri* out) {
    GSmtx mtx;
    Vec3 dir;
    bool enable;
    CheckObj* obj;
    CCD_CHECKMDL_HEAD* mdl;
    CCDFileHead* head;
    EventTri* src;
    u32 i;
    int count = 0;
    int k;
    u32 rf_t;
    EventTri temp[4];
    int j;
    GSmtx rot;
    int n;

    head = GScolsys2GetCCDFileHead();
    PSVECSubtract(end, start, &dir);
    obj = head->objs;
    for (i = 0; i < head->numObjs && count < 4; i++, obj++) {

        GScolsys2GetObjEnable(i, &enable);
        if (!enable) {
            continue;
        }
        mdl = obj->mdl;
        if (mdl == 0) {
            continue;
        }
        GScolsys2GetObjMatrix(&mtx, i);
        GScolsys2GetObjRotMatrix(&rot, i);
        n = getMdlEventList(start, end, (GSvec*)&dir, mdl, &mtx, &rot, temp);
        src = temp;
        for (k = 0; k < n && count < 4; src++, k++) {
            for (j = 0; j < count; j++) {
                rf_t = out[j].id;
                if (rf_t == src->id) {
                    break;
                }
            }
            if (j >= count) {
                out[count++] = *src;
            }
        }
    }
    return count;
}

extern "C" {
int GScolsys2CheckGetEventID(GSvec* start, GSvec* end, EventTri* out) {
    if (GScolsys2GetCCDFileHead() == 0) {
        return 0;
    }
    if (PSVECDistance(end, start) <= 0.0f) {
        return 0;
    }
    return getEventList(start, end, out);
}
}
