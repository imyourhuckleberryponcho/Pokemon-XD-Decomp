// GSmodel parsing: walks a model's joint tree like HSD_JObjDispAll and hands every
// PObj (with its view/position/envelope matrices) to a user callback instead of drawing.
#include <dolphin/types.h>

#pragma pool_strings off

struct GSmtx {
    f32 m[3][4];

    GSmtx() {}
};

typedef struct _HSD_JObj HSD_JObj;
typedef struct _HSD_DObj HSD_DObj;
typedef struct _HSD_PObj HSD_PObj;

struct HSD_Envelope {
    HSD_Envelope* next;   // 0x00
    HSD_JObj* jobj;       // 0x04
    f32 weight;           // 0x08
};

struct HSD_SList {
    HSD_SList* next;      // 0x00
    void* data;           // 0x04
};

struct _HSD_PObj {
    u8 unk0[0x4];
    HSD_PObj* next;       // 0x04
    u8 unk8[0x4];
    u16 flags;            // 0x0C
    u8 unkE[0x6];
    union {
        HSD_JObj* jobj;
        HSD_SList* envelope_list;
    } u;                  // 0x14
};

struct _HSD_DObj {
    u8 unk0[0x4];
    HSD_DObj* next;       // 0x04
    u8 unk8[0x4];
    HSD_PObj* pobj;       // 0x0C
    u8 unk10[0x4];
    u32 flags;            // 0x14
};

struct _HSD_JObj {
    u8 unk0[0x8];
    HSD_JObj* next;       // 0x08
    HSD_JObj* parent;     // 0x0C
    HSD_JObj* child;      // 0x10
    u32 flags;            // 0x14
    HSD_DObj* dobj;       // 0x18
    u8 unk1C[0x28];
    GSmtx mtx;            // 0x44
    u8 unk74[0x4];
    GSmtx* envelopemtx;   // 0x78
};

#define JOBJ_HIDDEN (1 << 4)
#define JOBJ_PTCL (1 << 5)
#define JOBJ_MTX_DIRTY (1 << 6)
#define JOBJ_INSTANCE (1 << 12)
#define JOBJ_SPLINE (1 << 14)
#define JOBJ_USER_DEF_MTX (1 << 23)

enum HSD_TrspMask {
    HSD_TRSP_NONE = 0,
    HSD_TRSP_OPA = 1,
    HSD_TRSP_XLU = 2,
    HSD_TRSP_TEXEDGE = 4,
    HSD_TRSP_ALL = 7
};

struct _GSmodel;

typedef void (*GSmodelParseFunc)(HSD_PObj* pobj, GSmtx* vmtx, GSmtx* pmtx, GSmtx* mtxStack, void* arg);

HSD_JObj* modelGetRenderJObj(_GSmodel* model);

extern "C" {
void __assert(const char* file, s32 line, const char* expr);
void* memcpy(void* dst, const void* src, unsigned long n);
extern GSmtx mtxIdent;

void HSD_JObjSetupMatrixSub(HSD_JObj* jobj);
void HSD_JObjSetCurrent(HSD_JObj* jobj);
HSD_JObj* HSD_JObjGetCurrent(void);
void HSD_JObjMakePositionMtx(HSD_JObj* jobj, GSmtx* vmtx, GSmtx* pmtx);
void HSD_DObjSetCurrent(HSD_DObj* dobj);
void HSD_PObjClearMtxMark(s32 idx, u32 mark);
void HSD_PObjGetMtxMark(s32 idx, void** obj, u32* mark);
void HSD_PObjSetMtxMark(s32 idx, void* obj, u32 mark);
GSmtx* _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* jobj, GSmtx* mtx);
void HSD_MtxScaledAdd(GSmtx* src, GSmtx* addend, GSmtx* dst, f32 scale);
void PSMTXInverse(const GSmtx* src, GSmtx* inv);
void PSMTXConcat(const GSmtx* a, const GSmtx* b, GSmtx* ab);
void PSMTXCopy(const GSmtx* src, GSmtx* dst);

// Inline helpers from HSD's jobj.h (asserts carry that header's line numbers).
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj* jobj) {
    u8 result;
    if (!jobj) {
        __assert("jobj.h", 605, "jobj");
    }
    result = false;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY)) {
        result = true;
    }
    return result;
}

static inline void HSD_JObjSetupMatrix(HSD_JObj* jobj) {
    if (!jobj || !HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetupMatrixSub(jobj);
}

}

static inline void _modelParseLoadEnvelopeMatrix(HSD_PObj* pobj, GSmtx* vmtx, GSmtx* pmtx, GSmtx* mtxStack) {
    GSmtx tmp;
    GSmtx mtx;
    GSmtx node;
    GSmtx* nodeMtx;
    GSmtx* src;
    HSD_SList* list;
    HSD_JObj* jobj;
    int i;

    jobj = HSD_JObjGetCurrent();
    HSD_PObjClearMtxMark(0, 2);
    nodeMtx = _HSD_mkEnvelopeModelNodeMtx(jobj, &node);
    list = pobj->u.envelope_list;
    for (i = 0; i < 10 && list != 0; i++, list = list->next, mtxStack++) {
        HSD_Envelope* envelope = (HSD_Envelope*)list->data;

        if (envelope == 0) {
            __assert("parse.cpp", 108, "envelope");
        }
        if (envelope->weight >= 1.0f) {
            HSD_JObjSetupMatrix(envelope->jobj);
            if (nodeMtx != 0) {
                PSMTXConcat(&envelope->jobj->mtx, envelope->jobj->envelopemtx, &mtx);
                src = &mtx;
            } else {
                src = &envelope->jobj->mtx;
            }
        } else {
            mtx.m[2][3] = 0.0f;
            mtx.m[2][2] = 0.0f;
            mtx.m[2][1] = 0.0f;
            mtx.m[2][0] = 0.0f;
            mtx.m[1][3] = 0.0f;
            mtx.m[1][2] = 0.0f;
            mtx.m[1][1] = 0.0f;
            mtx.m[1][0] = 0.0f;
            mtx.m[0][3] = 0.0f;
            mtx.m[0][2] = 0.0f;
            mtx.m[0][1] = 0.0f;
            mtx.m[0][0] = 0.0f;
            for (; envelope != 0; envelope = envelope->next) {
                HSD_JObj* jp;

                if (envelope->jobj == 0) {
                    __assert("parse.cpp", 133, "envelope->jobj");
                }
                jp = envelope->jobj;
                HSD_JObjSetupMatrix(jp);
                if (jp->mtx.m == 0) {
                    __assert("parse.cpp", 136, "jp->mtx");
                }
                if (jp->envelopemtx == 0) {
                    __assert("parse.cpp", 137, "jp->envelopemtx");
                }
                PSMTXConcat(&jp->mtx, jp->envelopemtx, &tmp);
                HSD_MtxScaledAdd(&tmp, &mtx, &mtx, envelope->weight);
            }
            src = &mtx;
        }
        if (nodeMtx != 0) {
            PSMTXConcat(src, nodeMtx, &mtx);
        }
        PSMTXConcat(vmtx, src, &tmp);
        PSMTXCopy(&tmp, mtxStack);
    }
}

static inline void _modelParseDObjDisp(HSD_DObj* dobj, GSmtx* vmtx, GSmtx* pmtx, bool rendering, GSmodelParseFunc func, void* arg) {
    HSD_PObj* pobj;

    for (pobj = dobj->pobj; pobj != 0; pobj = pobj->next) {
        static GSmtx mtxStack[10];

        if (pobj->flags & 0x800) {
            continue;
        }
        if (rendering) {
            switch (pobj->flags & 0x3000) {
            case 0:
                if (pobj->u.jobj == 0) {
                    HSD_JObj* jobj = HSD_JObjGetCurrent();
                    void* markObj;
                    u32 mark;

                    HSD_PObjGetMtxMark(0, &markObj, &mark);
                    if (markObj != jobj || mark != 1) {
                        HSD_PObjSetMtxMark(0, jobj, 1);
                        PSMTXCopy(pmtx, &mtxStack[0]);
                    }
                } else {
                    bool setup0 = false;
                    bool setup1 = false;
                    HSD_JObj* jobj = HSD_JObjGetCurrent();
                    void* markObj;
                    u32 mark;

                    HSD_PObjGetMtxMark(0, &markObj, &mark);
                    if (markObj != jobj && mark != 1) {
                        setup0 = true;
                    }
                    HSD_PObjSetMtxMark(0, jobj, 1);
                    HSD_PObjGetMtxMark(1, &markObj, &mark);
                    if (markObj != pobj->u.jobj && mark != 1) {
                        setup1 = true;
                    }
                    HSD_PObjSetMtxMark(1, pobj->u.jobj, 1);
                    if (setup0 || setup1) {
                        if (setup0) {
                            PSMTXCopy(pmtx, &mtxStack[0]);
                        }
                        if (setup1) {
                            GSmtx mtx;
                            HSD_JObjSetupMatrix(pobj->u.jobj);
                            PSMTXConcat(vmtx, &pobj->u.jobj->mtx, &mtx);
                            PSMTXCopy(&mtx, &mtxStack[1]);
                        }
                    }
                }
                break;
            case 0x1000: {
                HSD_JObj* jobj = HSD_JObjGetCurrent();
                void* markObj;
                u32 mark;

                HSD_PObjGetMtxMark(0, &markObj, &mark);
                if (markObj != jobj || mark != 1) {
                    HSD_PObjSetMtxMark(0, jobj, 1);
                    PSMTXCopy(pmtx, &mtxStack[0]);
                }
                break;
            }
            case 0x2000:
                _modelParseLoadEnvelopeMatrix(pobj, vmtx, pmtx, mtxStack);
                break;
            }
        }
        if ((pobj->flags & 0x3000) == 0x1000) {
            func(pobj, vmtx, pmtx, 0, arg);
        } else if (func != 0) {
            if (rendering) {
                func(pobj, vmtx, pmtx, mtxStack, arg);
            } else {
                func(pobj, vmtx, pmtx, 0, arg);
            }
        }
    }
}

static inline void _modelParseJObjDispSub(HSD_JObj* jobj, GSmtx* vmtx, GSmtx* pmtx, HSD_TrspMask trsp_mask, bool rendering, GSmodelParseFunc func, void* arg) {
    HSD_DObj* dobj;

    HSD_JObjSetCurrent(jobj);
    HSD_PObjClearMtxMark(0, 0);
    for (dobj = jobj->dobj; dobj != 0; dobj = dobj->next) {
        if (!(dobj->flags & 1) && (dobj->flags & (trsp_mask << 1))) {
            HSD_DObjSetCurrent(dobj);
            _modelParseDObjDisp(dobj, vmtx, pmtx, rendering, func, arg);
        }
    }
    HSD_DObjSetCurrent(0);
    HSD_JObjSetCurrent(0);
}

static inline void _modelParseJObjDispDObj(HSD_JObj* jobj, GSmtx* vmtx, HSD_TrspMask trsp_mask, bool rendering, GSmodelParseFunc func, void* arg) {
    if (!(jobj->flags & JOBJ_HIDDEN)) {
        u32 mask = jobj->flags & (trsp_mask << 18);
        if (mask) {
            GSmtx pmtx;

            HSD_JObjSetupMatrix(jobj);
            if (vmtx == 0) {
                static GSmtx foo;
                memcpy(&foo, &mtxIdent, sizeof(GSmtx));
                vmtx = &foo;
            }
            HSD_JObjMakePositionMtx(jobj, vmtx, &pmtx);
            if (mask & (HSD_TRSP_OPA << 18)) {
                _modelParseJObjDispSub(jobj, vmtx, &pmtx, HSD_TRSP_OPA, rendering, func, arg);
            }
            if (mask & (HSD_TRSP_TEXEDGE << 18)) {
                _modelParseJObjDispSub(jobj, vmtx, &pmtx, HSD_TRSP_TEXEDGE, rendering, func, arg);
            }
            if (mask & (HSD_TRSP_XLU << 18)) {
                _modelParseJObjDispSub(jobj, vmtx, &pmtx, HSD_TRSP_XLU, rendering, func, arg);
            }
        }
    }
}

static inline void _modelParseJObjDisp(HSD_JObj* jobj, GSmtx* vmtx, HSD_TrspMask trsp_mask, bool rendering, GSmodelParseFunc func, void* arg) {
    if (jobj != 0 && !(jobj->flags & (JOBJ_SPLINE | JOBJ_PTCL))) {
        _modelParseJObjDispDObj(jobj, vmtx, trsp_mask, rendering, func, arg);
    }
}

static inline void _modelParseSetupInstanceMtx(GSmtx* vmtx, HSD_JObj* jobj, GSmtx* mtx) {
    HSD_JObjSetupMatrix(jobj);
    HSD_JObjSetupMatrix(jobj->child);
    PSMTXInverse(&jobj->child->mtx, mtx);
    PSMTXConcat(&jobj->mtx, mtx, mtx);
    if (vmtx != 0) {
        PSMTXConcat(vmtx, mtx, mtx);
    }
}

static inline void _modelParseJObjDispAll(HSD_JObj* jobj, GSmtx* vmtx, HSD_TrspMask trsp_mask, bool rendering, GSmodelParseFunc func, void* arg) {
    if (jobj == 0) {
        return;
    }
    if (jobj->flags & JOBJ_INSTANCE) {
        GSmtx mtx;

        if (jobj->flags & JOBJ_HIDDEN) {
            return;
        }
        _modelParseSetupInstanceMtx(vmtx, jobj, &mtx);
        _modelParseJObjDispAll(jobj->child, &mtx, trsp_mask, rendering, func, arg);
    } else {
        if (jobj->flags & (trsp_mask << 18)) {
            _modelParseJObjDisp(jobj, vmtx, trsp_mask, rendering, func, arg);
        }
        if (jobj->flags & (trsp_mask << 28)) {
            HSD_JObj* child;
            for (child = jobj->child; child != 0; child = child->next) {
                _modelParseJObjDispAll(child, vmtx, trsp_mask, rendering, func, arg);
            }
        }
    }
}

extern "C" {

void GSmodelParse(_GSmodel* model, bool rendering, GSmodelParseFunc func, void* arg) {
    _modelParseJObjDispAll(modelGetRenderJObj(model), 0, HSD_TRSP_ALL, rendering, func, arg);
}

}
