

#include <game/maximum/GSAPI/baselib/class.h>

#pragma pool_strings off

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct HSD_Obj {
    HSD_Class parent;
    u16 ref_count;
    u16 ref_count_individual;
} HSD_Obj;

typedef HSD_ClassInfo HSD_ObjInfo;
extern HSD_ObjInfo hsdObj;

typedef struct HSD_AObj {
    u32 flags;
    f32 curr_frame;
    f32 rewind_frame;
    f32 end_frame;
    f32 framerate;
    void* fobj;
    struct HSD_Obj* hsd_obj;
} HSD_AObj;

typedef struct HSD_AObjDesc HSD_AObjDesc;
typedef struct HSD_RObj HSD_RObj;
typedef struct HSD_RObjDesc HSD_RObjDesc;
typedef struct HSD_RObjAnimJoint HSD_RObjAnimJoint;
typedef struct HSD_Spline HSD_Spline;

typedef struct HSD_JObj {
    HSD_Obj object;
    struct HSD_JObj* next;
    struct HSD_JObj* parent;
    struct HSD_JObj* child;
    u32 flags;
    union {
        HSD_Spline* spline;
    } u;
    f32 rotate[4];
    Vec3 scale;
    Vec3 translate;
    Mtx mtx;
} HSD_JObj;

#define JOBJ_USER_DEF_MTX (1 << 23)
#define JOBJ_MTX_DIRTY (1 << 6)

typedef union HSD_ObjData {
    f32 fv;
} HSD_ObjData;

typedef struct HSD_WObj {
    HSD_Obj parent;
    u32 flags;
    Vec3 pos;
    HSD_AObj* aobj;
    HSD_RObj* robj;
} HSD_WObj;

typedef struct HSD_WObjDesc {
    char* class_name;
    Vec3 pos;
    HSD_RObjDesc* robjdesc;
} HSD_WObjDesc;

typedef struct HSD_WObjInfo {
    HSD_ObjInfo parent;
    s32 (*load)(HSD_WObj* wobj, HSD_WObjDesc* desc);
    void (*update)(void* obj, s32 type, HSD_ObjData* val);
} HSD_WObjInfo;

typedef struct HSD_WObjAnim {
    HSD_AObjDesc* aobjdesc;
    HSD_RObjAnimJoint* robjanim;
} HSD_WObjAnim;

#define HSD_WOBJ_INFO(i) ((HSD_WObjInfo*)(i))
#define HSD_WOBJ_METHOD(o) HSD_WOBJ_INFO(HSD_CLASS_METHOD(o))

void HSD_AObjRemove(HSD_AObj* aobj);
void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame);
HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* desc);
void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj, void (*update)(void* obj, s32 type, HSD_ObjData* val));
void HSD_RObjRemoveAnimAll(HSD_RObj* robj);
void HSD_RObjReqAnimAll(HSD_RObj* robj, f32 frame);
void HSD_RObjAddAnimAll(HSD_RObj* robj, HSD_RObjAnimJoint* anim);
void HSD_RObjAnimAll(HSD_RObj* robj);
void HSD_RObjRemoveAll(HSD_RObj* robj);
HSD_RObj* HSD_RObjLoadDesc(HSD_RObjDesc* desc);
void HSD_RObjResolveRefsAll(HSD_RObj* robj, HSD_RObjDesc* desc);
void HSD_JObjSetupMatrixSub(HSD_JObj* jobj);
void splArcLengthPoint(Vec3* p, HSD_Spline* spline, f32 t);
void PSMTXMultVec(const MtxPtr m, const Vec3* src, Vec3* dst);


static inline s32 HSD_JObjMtxIsDirty(HSD_JObj* jobj) {
    s32 result;
    if (jobj == NULL) {
        __assert("jobj.h", 605, "jobj");
    }
    result = FALSE;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY)) {
        result = TRUE;
    }
    return result;
}

static inline void HSD_JObjSetupMatrix(HSD_JObj* jobj) {
    if (jobj == NULL || !HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetupMatrixSub(jobj);
}

static void WObjInfoInit(void);

HSD_WObjInfo hsdWObj = {{{WObjInfoInit}}};

static HSD_ClassInfo* default_class = NULL;

void HSD_WObjSetPosition(HSD_WObj* wobj, Vec3* pos);
void HSD_WObjSetPositionX(HSD_WObj* wobj, f32 val);
void HSD_WObjSetPositionY(HSD_WObj* wobj, f32 val);
void HSD_WObjSetPositionZ(HSD_WObj* wobj, f32 val);
HSD_WObj* HSD_WObjAlloc(void);

void HSD_WObjRemoveAnim(HSD_WObj* wobj) {
    if (wobj != NULL) {
        HSD_AObjRemove(wobj->aobj);
        wobj->aobj = NULL;
        HSD_RObjRemoveAnimAll(wobj->robj);
    }
}

void HSD_WObjReqAnim(HSD_WObj* wobj, f32 frame) {
    if (wobj != NULL) {
        HSD_AObjReqAnim(wobj->aobj, frame);
        HSD_RObjReqAnimAll(wobj->robj, frame);
    }
}

void HSD_WObjAddAnim(HSD_WObj* wobj, HSD_WObjAnim* anim) {
    if (wobj != NULL && anim != NULL) {
        if (wobj->aobj != NULL) {
            HSD_AObjRemove(wobj->aobj);
        }
        wobj->aobj = HSD_AObjLoadDesc(anim->aobjdesc);
        HSD_RObjAddAnimAll(wobj->robj, anim->robjanim);
    }
}

static void WObjUpdateFunc(void* obj, s32 type, HSD_ObjData* val) {
    HSD_WObj* wobj;
    Vec3 p;
    HSD_JObj* jp;

    wobj = obj;
    if (wobj != NULL) {
        switch (type) {
        case 4: {
            if (val->fv < 0.0f) {
                val->fv = 0.0f;
            }
            if (1.0f < val->fv) {
                val->fv = 1.0f;
            }
            if (wobj->aobj == NULL) {
                __assert("wobj.c", 152, "wobj->aobj");
            }
            jp = (HSD_JObj*)wobj->aobj->hsd_obj;
            if (jp == NULL) {
                __assert("wobj.c", 154, "jp");
            }
            if (jp->u.spline == NULL) {
                __assert("wobj.c", 155, "jp->u.spline");
            }
            splArcLengthPoint(&p, jp->u.spline, val->fv);
            HSD_WObjSetPosition(wobj, &p);
            wobj->flags |= 1;
        } break;

        case 5:
            HSD_WObjSetPositionX(wobj, val->fv);
            break;

        case 6:
            HSD_WObjSetPositionY(wobj, val->fv);
            break;

        case 7:
            HSD_WObjSetPositionZ(wobj, val->fv);
            break;
        }
    }
}

void HSD_WObjInterpretAnim(HSD_WObj* wobj) {
    if (wobj != NULL) {
        HSD_AObjInterpretAnim(wobj->aobj, wobj, HSD_WOBJ_METHOD(wobj)->update);
        HSD_RObjAnimAll(wobj->robj);
    }
}

static s32 WObjLoad(HSD_WObj* wobj, HSD_WObjDesc* desc) {
    HSD_WObjSetPosition(wobj, &desc->pos);
    if (wobj->robj != NULL) {
        HSD_RObjRemoveAll(wobj->robj);
    }
    wobj->robj = HSD_RObjLoadDesc(desc->robjdesc);
    HSD_RObjResolveRefsAll(wobj->robj, desc->robjdesc);
    return 0;
}

void HSD_WObjInit(HSD_WObj* wobj, HSD_WObjDesc* desc) {
    if (wobj == NULL || desc == NULL) {
        return;
    }
    HSD_WObjSetPosition(wobj, &desc->pos);
    if (wobj->robj != NULL) {
        HSD_RObjRemoveAll(wobj->robj);
    }
    wobj->robj = HSD_RObjLoadDesc(desc->robjdesc);
    HSD_RObjResolveRefsAll(wobj->robj, desc->robjdesc);
}

HSD_WObj* HSD_WObjLoadDesc(HSD_WObjDesc* desc) {
    if (desc != NULL) {
        HSD_WObj* wobj;
        HSD_ClassInfo* info;
        if (desc->class_name == NULL || !(info = hsdSearchClassInfo(desc->class_name))) {
            wobj = HSD_WObjAlloc();
        } else {
            wobj = hsdNew(info);
            if (wobj == NULL) {
                __assert("wobj.c", 260, "wobj");
            }
        }
        HSD_WOBJ_METHOD(wobj)->load(wobj, desc);
        return wobj;
    }
    return NULL;
}

void HSD_WObjSetPosition(HSD_WObj* wobj, Vec3* pos) {
    if (wobj == NULL || pos == NULL) {
        return;
    }
    wobj->pos = *pos;
    wobj->flags |= 0x2;
    wobj->flags &= 0xFFFFFFFE;
}

void HSD_WObjSetPositionX(HSD_WObj* wobj, f32 val) {
    HSD_JObj* jp;
    if (wobj != NULL) {
        if ((wobj->flags & 1) != 0) {
            if (wobj->aobj != NULL && wobj->aobj->hsd_obj != NULL) {
                jp = (HSD_JObj*)wobj->aobj->hsd_obj;
                HSD_JObjSetupMatrix((HSD_JObj*)wobj->aobj->hsd_obj);
                PSMTXMultVec(jp->mtx, &wobj->pos, &wobj->pos);
            }
            wobj->flags &= 0xFFFFFFFE;
        }
        wobj->pos.x = val;
        wobj->flags |= 0x2;
    }
}

void HSD_WObjSetPositionY(HSD_WObj* wobj, f32 val) {
    HSD_JObj* jp;
    if (wobj != NULL) {
        if ((wobj->flags & 1) != 0) {
            if (wobj->aobj != NULL && wobj->aobj->hsd_obj != NULL) {
                jp = (HSD_JObj*)wobj->aobj->hsd_obj;
                HSD_JObjSetupMatrix((HSD_JObj*)wobj->aobj->hsd_obj);
                PSMTXMultVec(jp->mtx, &wobj->pos, &wobj->pos);
            }
            wobj->flags &= 0xFFFFFFFE;
        }
        wobj->pos.y = val;
        wobj->flags |= 0x2;
    }
}

void HSD_WObjSetPositionZ(HSD_WObj* wobj, f32 val) {
    HSD_JObj* jp;
    if (wobj != NULL) {
        if ((wobj->flags & 1) != 0) {
            if (wobj->aobj != NULL && wobj->aobj->hsd_obj != NULL) {
                jp = (HSD_JObj*)wobj->aobj->hsd_obj;
                HSD_JObjSetupMatrix((HSD_JObj*)wobj->aobj->hsd_obj);
                PSMTXMultVec(jp->mtx, &wobj->pos, &wobj->pos);
            }
            wobj->flags &= 0xFFFFFFFE;
        }
        wobj->pos.z = val;
        wobj->flags |= 0x2;
    }
}

void HSD_WObjGetPosition(HSD_WObj* wobj, Vec3* vec) {
    HSD_JObj* jp;
    if (wobj == NULL || vec == NULL) {
        return;
    }
    if ((wobj->flags & 1) != 0) {
        if (wobj->aobj != NULL && wobj->aobj->hsd_obj != NULL) {
            jp = (HSD_JObj*)wobj->aobj->hsd_obj;
            HSD_JObjSetupMatrix((HSD_JObj*)wobj->aobj->hsd_obj);
            PSMTXMultVec(jp->mtx, &wobj->pos, &wobj->pos);
        }
        wobj->flags &= 0xFFFFFFFE;
    }
    *vec = wobj->pos;
}

HSD_WObj* HSD_WObjAlloc(void) {
    HSD_WObj* wobj = hsdNew(default_class ? default_class : HSD_CLASS_INFO(&hsdWObj));
    if (wobj == NULL) {
        __assert("wobj.c", 599, "wobj");
    }
    return wobj;
}

static void WObjRelease(HSD_Class* o) {
    HSD_WObj* wobj = (HSD_WObj*)o;
    HSD_RObjRemoveAll(wobj->robj);
    HSD_AObjRemove(wobj->aobj);
    HSD_PARENT_INFO(&hsdWObj)->release(o);
}

static void WObjAmnesia(HSD_ClassInfo* info) {
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    HSD_PARENT_INFO(&hsdWObj)->amnesia(info);
}

static void WObjInfoInit(void) {
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdWObj), HSD_CLASS_INFO(&hsdObj), "sysdolphin_base_library", "had_wobj",
                     sizeof(HSD_WObjInfo), sizeof(HSD_WObj));
    HSD_CLASS_INFO(&hsdWObj)->release = WObjRelease;
    HSD_CLASS_INFO(&hsdWObj)->amnesia = WObjAmnesia;
    HSD_WOBJ_INFO(&hsdWObj)->load = WObjLoad;
    HSD_WOBJ_INFO(&hsdWObj)->update = WObjUpdateFunc;
}
