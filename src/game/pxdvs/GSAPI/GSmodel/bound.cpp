#include <dolphin/types.h>

struct Vec {
    f32 x, y, z;
};

struct GSmtx {
    f32 m[3][4];
};

struct GSbound {
    u8 unk0[0x10];
};

struct GSmodel {
    u8 unk0[0x18];
    Vec translate;
    Vec rotate;
    Vec scale;
    GSbound bound;
    u8 unk4C[0x5D8 - 0x4C];
    s32 unk5D8;
};

struct _HSD_PObj {
    u8 unk0[8];
    void* display;
    u8 unkC[2];
    u16 n_display;
    void* vertices;
};

enum GSgfxPrimType {
    GS_GFX_PRIM_TYPE_0
};

struct GSgfxParseCallbacks {
    void (*beginSurface)(GSgfxPrimType type, unsigned short n, unsigned long attr, void* user);
    void* unk4;
    void (*vertex)(unsigned long attr, void* data, void* user);
    void* unkC;
    void* unk10;
};

struct BoundParseContext {
    GSmodel* model;
    GSmtx* mtx;
    GSmtx* envelopeMtx;
    unsigned long attr;
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
static void _modelBoundVertex(unsigned long attr, void* data, void* user);
static void _modelBoundBeginSurface(GSgfxPrimType type, unsigned short n, unsigned long attr, void* user);

extern "C" {

void GSmodelRecalculateBound(GSmodel* model) {
    s32 saved5D8;
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

static void _modelBoundVertex(unsigned long attr, void* data, void* user) {
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
        f32* src = (f32*)data;
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

static void _modelBoundBeginSurface(GSgfxPrimType type, unsigned short n, unsigned long attr, void* user) {
    ((BoundParseContext*)user)->attr = attr;
}
