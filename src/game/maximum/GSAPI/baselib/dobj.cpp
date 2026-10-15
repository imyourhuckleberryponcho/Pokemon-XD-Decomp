// Compiled as C with deferred inlining (see configure.py): functions come out in reverse
// source order. Based on the Melee decomp's dobj.c; XD's version also runs the DObj's own
// animation in HSD_DObjAnim and has HSD_DObjCountVertices.
#include <game/maximum/GSAPI/baselib/class.h>

#pragma pool_strings off

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

typedef struct HSD_MObj {
    HSD_ClassInfo* class_info;
    u32 rendermode;
} HSD_MObj;

typedef struct HSD_MObjInfo {
    HSD_ClassInfo parent;
    void (*setup)(HSD_MObj* mobj, u32 rendermode);
    void* unk40[4];
    void (*unset)(HSD_MObj* mobj, u32 rendermode);
} HSD_MObjInfo;

typedef struct HSD_PObj {
    HSD_ClassInfo* class_info;
    struct HSD_PObj* next;
} HSD_PObj;

typedef struct HSD_PObjInfo {
    HSD_ClassInfo parent;
    void (*disp)(HSD_PObj* pobj, MtxPtr vmtx, MtxPtr pmtx, u32 rendermode);
} HSD_PObjInfo;

typedef struct HSD_AObj HSD_AObj;
typedef struct HSD_MObjDesc HSD_MObjDesc;
typedef struct HSD_PObjDesc HSD_PObjDesc;
typedef struct HSD_ShapeAnim HSD_ShapeAnim;

typedef struct HSD_MatAnim {
    struct HSD_MatAnim* next;
} HSD_MatAnim;

typedef struct HSD_ShapeAnimDObj {
    struct HSD_ShapeAnimDObj* next;
    HSD_ShapeAnim* shapeanim;
} HSD_ShapeAnimDObj;

typedef struct HSD_DObj {
    HSD_ClassInfo* class_info;
    struct HSD_DObj* next;
    HSD_MObj* mobj;
    HSD_PObj* pobj;
    HSD_AObj* aobj;
    u32 flags;
} HSD_DObj;

typedef struct HSD_DObjDesc {
    char* class_name;
    struct HSD_DObjDesc* next;
    HSD_MObjDesc* mobjdesc;
    HSD_PObjDesc* pobjdesc;
} HSD_DObjDesc;

typedef struct HSD_DObjInfo {
    HSD_ClassInfo parent;
    void (*disp)(HSD_DObj* dobj, MtxPtr vmtx, MtxPtr pmtx, u32 rendermode);
    s32 (*load)(HSD_DObj* dobj, HSD_DObjDesc* desc);
    void (*update)(void* obj, u32 type, void* val);
} HSD_DObjInfo;

#define HSD_DOBJ(o) ((HSD_DObj*)(o))
#define HSD_DOBJ_INFO(i) ((HSD_DObjInfo*)(i))
#define HSD_DOBJ_METHOD(o) HSD_DOBJ_INFO(HSD_CLASS_METHOD(o))
#define HSD_MOBJ_METHOD(o) ((HSD_MObjInfo*)HSD_CLASS_METHOD(o))
#define HSD_POBJ_METHOD(o) ((HSD_PObjInfo*)HSD_CLASS_METHOD(o))

void HSD_AObjRemove(HSD_AObj* aobj);
void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj, void (*update)(void* obj, u32 type, void* val));
void HSD_PObjRemoveAnimAllByFlags(HSD_PObj* pobj, u32 flags);
void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags);
void HSD_PObjAddAnimAll(HSD_PObj* pobj, HSD_ShapeAnim* shapeanim);
void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim);
void HSD_PObjReqAnimAllByFlags(HSD_PObj* pobj, f32 startframe, u32 flags);
void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags);
void HSD_PObjAnimAll(HSD_PObj* pobj);
void HSD_MObjAnim(HSD_MObj* mobj);
HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* desc);
HSD_PObj* HSD_PObjLoadDesc(HSD_PObjDesc* desc);
void HSD_PObjResolveRefsAll(HSD_PObj* pobj, HSD_PObjDesc* desc);
void HSD_PObjCountVertices(HSD_PObj* pobj, s32* nverts, s32* nprims);
void HSD_MObjSetCurrent(HSD_MObj* mobj);
void HSD_MObjRemove(HSD_MObj* mobj);
void HSD_PObjRemoveAll(HSD_PObj* pobj);

static void DObjInfoInit(void);
HSD_DObjInfo hsdDObj = {{{DObjInfoInit}}};

static HSD_ClassInfo* default_class = NULL;

static HSD_DObj* current_dobj = NULL;

HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc);
HSD_DObj* HSD_DObjAlloc(void);
void HSD_DObjDisp(HSD_DObj* dobj, MtxPtr vmtx, MtxPtr pmtx, u32 rendermode);

void HSD_DObjSetCurrent(HSD_DObj* dobj) {
    current_dobj = dobj;
}

u32 HSD_DObjGetFlags(HSD_DObj* dobj) {
    if (dobj != NULL) {
        return dobj->flags;
    }
    return 0;
}

void HSD_DObjSetFlags(HSD_DObj* dobj, u32 flags) {
    if (dobj != NULL) {
        dobj->flags |= flags;
    }
}

void HSD_DObjClearFlags(HSD_DObj* dobj, u32 flags) {
    if (dobj != NULL) {
        dobj->flags &= ~flags;
    }
}

void HSD_DObjModifyFlags(HSD_DObj* dobj, u32 flags, u32 mask) {
    if (dobj == NULL) {
        return;
    }
    dobj->flags = (dobj->flags & ~mask) | (flags & mask);
}

void HSD_DObjRemoveAnimByFlags(HSD_DObj* dobj, u32 flags) {
    if (dobj == NULL) {
        return;
    }
    if ((flags & 2) != 0) {
        HSD_AObjRemove(dobj->aobj);
        dobj->aobj = NULL;
    }
    HSD_PObjRemoveAnimAllByFlags(dobj->pobj, flags);
    HSD_MObjRemoveAnimByFlags(dobj->mobj, flags);
}

void HSD_DObjRemoveAnimAllByFlags(HSD_DObj* dobj, u32 flags) {
    HSD_DObj* dp;
    if (dobj == NULL) {
        return;
    }
    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjRemoveAnimByFlags(dp, flags);
    }
}

void HSD_DObjAddAnim(HSD_DObj* dobj, HSD_MatAnim* mat_anim, HSD_ShapeAnimDObj* sh_anim) {
    if (dobj == NULL) {
        return;
    }
    HSD_PObjAddAnimAll(dobj->pobj, sh_anim != NULL ? sh_anim->shapeanim : NULL);
    HSD_MObjAddAnim(dobj->mobj, mat_anim);
}

#define next_p(p) ((p) != NULL ? (p)->next : NULL)

void HSD_DObjAddAnimAll(HSD_DObj* dobj, HSD_MatAnim* matanim, HSD_ShapeAnimDObj* shapeanimdobj) {
    HSD_DObj* dp;
    HSD_MatAnim* ma;
    HSD_ShapeAnimDObj* sd;
    if (dobj == NULL) {
        return;
    }
    for (dp = dobj, ma = matanim, sd = shapeanimdobj; dp != NULL; dp = dp->next, ma = next_p(ma), sd = next_p(sd)) {
        HSD_DObjAddAnim(dp, ma, sd);
    }
}

void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, f32 startframe, u32 flags) {
    if (dobj == NULL) {
        return;
    }
    HSD_PObjReqAnimAllByFlags(dobj->pobj, startframe, flags);
    HSD_MObjReqAnimByFlags(dobj->mobj, startframe, flags);
}

void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, f32 startframe, u32 flags) {
    HSD_DObj* dp;
    if (dobj == NULL) {
        return;
    }
    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, startframe, flags);
    }
}

void HSD_DObjReqAnimAll(HSD_DObj* dobj, f32 startframe) {
    HSD_DObj* dp;
    if (dobj == NULL) {
        return;
    }
    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, startframe, 0x7FF);
    }
}

void HSD_DObjAnim(HSD_DObj* dobj) {
    if (dobj == NULL) {
        return;
    }
    HSD_AObjInterpretAnim(dobj->aobj, dobj, HSD_DOBJ_METHOD(dobj)->update);
    HSD_PObjAnimAll(dobj->pobj);
    HSD_MObjAnim(dobj->mobj);
}

void HSD_DObjAnimAll(HSD_DObj* dobj) {
    HSD_DObj* dp;
    if (dobj == NULL) {
        return;
    }
    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjAnim(dp);
    }
}

static s32 DObjLoad(HSD_DObj* dobj, HSD_DObjDesc* desc) {
    dobj->next = HSD_DObjLoadDesc(desc->next);
    dobj->mobj = HSD_MObjLoadDesc(desc->mobjdesc);
    dobj->pobj = HSD_PObjLoadDesc(desc->pobjdesc);

    if (dobj->mobj != NULL) {
        switch (dobj->mobj->rendermode & 0x60000000) {
        case 0:
            HSD_DObjModifyFlags(dobj, 2, 0xE);
            break;
        case 0x40000000:
            HSD_DObjModifyFlags(dobj, 8, 0xE);
            break;
        case 0x60000000:
            HSD_DObjModifyFlags(dobj, 4, 0xE);
            break;
        default:
            OSReport("mobj has unexpected blending flags (0x%x).", dobj->mobj->rendermode);
            HSD_Panic("dobj.c", 319, "");
        }
    }
    return 0;
}

HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc) {
    HSD_DObj* dobj;
    HSD_ClassInfo* info;

    if (desc == NULL) {
        return NULL;
    }
    if (desc->class_name == NULL || (info = hsdSearchClassInfo(desc->class_name)) == NULL) {
        dobj = HSD_DObjAlloc();
    } else {
        dobj = HSD_DOBJ(hsdNew(info));
        if (dobj == NULL) {
            __assert("dobj.c", 385, "dobj");
        }
    }
    HSD_DOBJ_METHOD(dobj)->load(dobj, desc);
    return dobj;
}

void HSD_DObjRemove(HSD_DObj* dobj) {
    hsdDelete(dobj);
}

void HSD_DObjRemoveAll(HSD_DObj* dobj) {
    HSD_DObj* next;
    for (; dobj != NULL; dobj = next) {
        next = dobj->next;
        HSD_DObjRemove(dobj);
    }
}

HSD_DObj* HSD_DObjAlloc(void) {
    HSD_DObj* dobj = hsdNew(default_class ? default_class : HSD_CLASS_INFO(&hsdDObj));
    if (dobj == NULL) {
        __assert("dobj.c", 532, "dobj");
    }
    return dobj;
}

void HSD_DObjResolveRefs(HSD_DObj* dobj, HSD_DObjDesc* desc) {
    if (dobj == NULL || desc == NULL) {
        return;
    }
    HSD_PObjResolveRefsAll(dobj->pobj, desc->pobjdesc);
}

void HSD_DObjResolveRefsAll(HSD_DObj* dobj, HSD_DObjDesc* desc) {
    for (; dobj != NULL && desc != NULL; dobj = dobj->next, desc = desc->next) {
        HSD_DObjResolveRefs(dobj, desc);
    }
}

void HSD_DObjCountVertices(HSD_DObj* dobj, s32* nverts, s32* nprims) {
    s32 total_verts = 0;
    s32 total_prims = 0;
    for (; dobj != NULL; dobj = dobj->next) {
        s32 verts;
        s32 prims;
        HSD_PObjCountVertices(dobj->pobj, &verts, &prims);
        total_verts += verts;
        total_prims += prims;
    }
    if (nverts != NULL) {
        *nverts = total_verts;
    }
    if (nprims != NULL) {
        *nprims = total_prims;
    }
}

void HSD_DObjDisp(HSD_DObj* dobj, MtxPtr vmtx, MtxPtr pmtx, u32 rendermode) {
    HSD_PObj* p;

    HSD_MObjSetCurrent(dobj->mobj);
    if ((rendermode & 0x4000000) == 0) {
        HSD_MOBJ_METHOD(dobj->mobj)->setup(dobj->mobj, rendermode);
    }
    for (p = dobj->pobj; p != NULL; p = p->next) {
        HSD_POBJ_METHOD(p)->disp(p, vmtx, pmtx, rendermode);
    }
    if ((rendermode & 0x4000000) == 0) {
        HSD_MOBJ_METHOD(dobj->mobj)->unset(dobj->mobj, rendermode);
    }
    HSD_MObjSetCurrent(NULL);
}

static void DObjRelease(HSD_Class* o) {
    HSD_DObj* dobj = HSD_DOBJ(o);

    HSD_MObjRemove(dobj->mobj);
    HSD_PObjRemoveAll(dobj->pobj);
    HSD_AObjRemove(dobj->aobj);

    HSD_PARENT_INFO(&hsdDObj)->release(o);
}

static void DObjAmnesia(HSD_ClassInfo* info) {
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    HSD_PARENT_INFO(&hsdDObj)->amnesia(info);
}

static void DObjInfoInit(void) {
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdDObj), HSD_CLASS_INFO(&hsdClass), "sysdolphin_base_library", "hsd_dobj",
                     sizeof(HSD_DObjInfo), sizeof(HSD_DObj));

    HSD_CLASS_INFO(&hsdDObj)->release = DObjRelease;
    HSD_CLASS_INFO(&hsdDObj)->amnesia = DObjAmnesia;
    HSD_DOBJ_INFO(&hsdDObj)->disp = HSD_DObjDisp;
    HSD_DOBJ_INFO(&hsdDObj)->load = DObjLoad;
}
