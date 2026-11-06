#include <game/gcdata.h>
#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gsmodelview.h>

struct Vec {
    f32 x, y, z;
};

struct GSmtx {
    f32 m[3][4];
};

struct GSbound {
    u16 flags;
    u16 type;
    void* data;
    GSmodelBoundDataView u;
};

struct GSmodel {
    u32 flags;
    void* next;
    void* set;
    void* jobj;
    void* blendJObj;
    void* blendDest;
    Vec translate;
    Vec rotate;
    Vec scale;
    GSbound bound;
    void* camera;
    u16 flags2;
    u16 token;
    u8 layers[8];
    u32 animCount;
    u32 texAnimCount;
    s32 animType;
    u32 animIndex;
    f32 animRate;
    f32 animFrame;
    f32 animReqFrame;
    f32 animEndFrame;
    void* animAObj;
    s32 blendAnimType;
    u32 blendAnimIndex;
    f32 blendAnimRate;
    f32 blendAnimFrame;
    f32 blendAnimReqFrame;
    f32 blendAnimEndFrame;
    void* blendAnimAObj;
    s32 texAnimType;
    u32 texAnimIndex;
    f32 texAnimRate;
    f32 texAnimFrame;
    f32 texAnimReqFrame;
    f32 texAnimEndFrame;
    void* texAnimAObj;
    GSmodelPartMixView partMix[12];
    f32 blendFactor;
    u8 animDirty;
    u8 texAnimDirty;
    u8 unk21E[2];
    void* animEndedCallback;
    void* animEndedCallbackArg;
    GSmodelPartAnimView partAnim[16];
    s32 attachMode;
    void* attachModel;
    u32 attachIndex;
    f32 attachPosition[3];
    f32 attachRotation[3];
    f32 attachScale[3];
    void* unk5D8;
    u32 particleAttachMode;
    void* materials;
    u32 materialCount;
    u32 shadowSurfaceCount;
    void* shadowSurfaces;
    void* shadowLight;
    f32 groundPlane;
    GCuptr unk5F8;
    f32 unk5FC;
    u8 unk600[4];
    f32 unk604;
    u8 unk608[4];
    f32 unk60C;
    u16 unk610;
    u8 unk612;
    u8 unk613;
    u32 unk614;
    u32 unk618;
    u32 unk61C;
    s32 vertexCount;
    s32 polygonCount;
};

#ifdef __MWERKS__
struct _HSD_PObj {
    u8 unk0[8];
    void* display;
    u8 unkC[2];
    u16 n_display;
    void* vertices;
};
#else
struct _HSD_PObj {
    void* pcClass;
    void* pcNext;
    void* display;
    u8 unkC[2];
    u16 n_display;
    void* vertices;
};
#endif

enum GSgfxPrimType {
    GS_GFX_PRIM_TYPE_0
};

struct GSgfxParseCallbacks {
    void (*beginSurface)(GSgfxPrimType type, unsigned short n, u32 attr, void* user);
    void* unk4;
    void (*vertex)(u32 attr, void* data, void* user);
    void* unkC;
    void* unk10;
};

struct BoundParseContext {
    GSmodel* model;
    GSmtx* mtx;
    GSmtx* envelopeMtx;
    u32 attr;
};

extern "C" {
u8 GSboundHasAnimData(GSbound* bound);
void GSboundReset(GSbound* bound);
void GSboundAddPoint(GSbound* bound, f32 x, f32 y, f32 z);
GSbound* GSmodelGetBound(GSmodel* model);
void GSmodelForceAnimTransformUpdate(GSmodel* model);
void GSmodelParse(GSmodel* model, s32, void (*callback)(_HSD_PObj*, GSmtx*, GSmtx*, GSmtx*, void*), void* user);
void GSgfxParseDisplayList(void* display, void* vertices, u32 size, GSgfxParseCallbacks* callbacks, void* user);
void PSMTXMultVec(const GSmtx* m, const Vec* src, Vec* dst);
}

static void _modelBoundPObj(_HSD_PObj* pobj, GSmtx* mtx0, GSmtx* mtx, GSmtx* envelopeMtx, void* user);
static void _modelBoundVertex(u32 attr, void* data, void* user);
static void _modelBoundBeginSurface(GSgfxPrimType type, unsigned short n, u32 attr, void* user);

extern "C" {

void GSmodelRecalculateBound(GSmodel* model) {
    void* saved5D8;
    Vec translate;
    Vec rotate;
    Vec scale;

    if (GSboundHasAnimData(&model->bound)) {
        return;
    }
    GSboundReset(&model->bound);

    saved5D8 = model->unk5D8;
    model->unk5D8 = 0;
    translate = model->translate;
    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = 0.0f;
    rotate = model->rotate;
    model->rotate.x = 0.0f;
    model->rotate.y = 0.0f;
    model->rotate.z = 0.0f;
    scale = model->scale;
    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;
    GSmodelForceAnimTransformUpdate(model);
    GSmodelParse(model, 1, _modelBoundPObj, model);
    model->unk5D8 = saved5D8;
    model->translate = translate;
    model->rotate = rotate;
    model->scale = scale;
}

}

static void _modelBoundPObj(_HSD_PObj* pobj, GSmtx* mtx0, GSmtx* mtx, GSmtx* envelopeMtx, void* user) {
    static GSgfxParseCallbacks cblist = { _modelBoundBeginSurface, NULL, _modelBoundVertex, NULL, NULL };
    BoundParseContext context;
    context.model = (GSmodel*)user;
    context.mtx = mtx;
    context.envelopeMtx = envelopeMtx;
    GSgfxParseDisplayList(pobj->display, pobj->vertices, pobj->n_display << 5, &cblist, &context);
}

static void _modelBoundVertex(u32 attr, void* data, void* user) {
    static s32 mtxidx = 0;
    BoundParseContext* context = (BoundParseContext*)user;
    GSmtx* mtx;

    if (attr & 1) {
        mtxidx = *(u8*)data / 3;
    }
    if (attr & 2) {
        if (context->attr & 1) {
            mtx = &context->envelopeMtx[mtxidx];
        } else {
            mtx = context->mtx;
        }
        gc_bef32* src = (gc_bef32*)data;
        Vec pos;
        f32 x, y, z;
        z = src[2];
        y = src[1];
        x = src[0];
        pos.x = x;
        pos.y = y;
        pos.z = z;
        PSMTXMultVec(mtx, &pos, &pos);
        GSboundAddPoint(GSmodelGetBound(context->model), pos.x, pos.y, pos.z);
    }
}

static void _modelBoundBeginSurface(GSgfxPrimType type, unsigned short n, u32 attr, void* user) {
    ((BoundParseContext*)user)->attr = attr;
}
