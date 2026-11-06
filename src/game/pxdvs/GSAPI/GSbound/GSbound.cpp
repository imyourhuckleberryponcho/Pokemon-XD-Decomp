#include <dolphin/types.h>
#include <dolphin/mtx.h>
#include <dolphin/gx/GXVert.h>

class GSgfxMatrixStack {
public:
    void pushMult(struct GSmtx* mtx);
    void pop();
};

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderState(bool, u8, bool);
    void beginSurface(u16 count);
    void endSurface();

};

struct BoundAnim;
#ifdef __MWERKS__
struct GSbound {
 u16 flags;
 u16 type;
 void* data;
 f32 minX;
 f32 minY;
 f32 minZ;
 f32 maxX;
 f32 maxY;
 f32 maxZ;
};
#define BOUND_ANIM_INDEX(b) (*(s32*) &(b)->minX)
#define BOUND_ANIM_FRAME(b) ((b)->minY)
#define BOUND_ANIM(b) (*(BoundAnim**) &(b)->minZ)
#define BOUND_ANIM_TABLE(b) (*(u16***) &(b)->maxX)
#define BOUND_ANIM_TABLE_PTR(b) (*(void**) &(b)->maxX)
#else
struct GSbound {
    u16 flags;
    u16 type;
    void* data;
    union {
        struct {
            f32 minX, minY, minZ, maxX, maxY, maxZ;
        };
        struct {
            s32 animIndex;
            f32 animFrame;
            BoundAnim* anim;
            u16** animTable;
        };
    };
};
#define BOUND_ANIM_INDEX(b) ((b)->animIndex)
#define BOUND_ANIM_FRAME(b) ((b)->animFrame)
#define BOUND_ANIM(b) ((b)->anim)
#define BOUND_ANIM_TABLE(b) ((b)->animTable)
#define BOUND_ANIM_TABLE_PTR(b) (*(void**) &(b)->animTable)
#endif

struct BoundAnim {
    u16 count;
    u16 pad;
};

struct BoundData3 {
    Vec pos;
    Quaternion rot;
    Vec scale;
};

extern "C" {
void* memset(void* dst, int c, unsigned long n);
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
void GScameraLoadActiveCameraMatrix(s32 id);
void* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 GSgfxProjectFastList(const Vec* points, Vec* screen, u32 count);
void GSmodelGetPosition(void* model, Vec* v);
void GSmodelGetRotation(void* model, Vec* v);
void GSmodelGetScale(void* model, Vec* v);
void GSmodelGetRootPosition(void* model, Vec* v);
void GSmodelGetRootRotation(void* model, Vec* v);
void GSmodelGetRootScale(void* model, Vec* v);
bool GSmodelIsRootNullAdded(void* model);
int EulerToQuat(Vec* euler, Quaternion* q);
void C_QUATMtx(Quaternion* r, const Mtx m);
void GSboundGetMinMax(GSbound* b, Vec* min, Vec* max, bool scale, bool rot, bool trans, bool ignoreRoot);
}

void GSboundDraw(GSbound* b, GSgfxLayer* layer);
extern "C" void GSboundGetSize(GSbound* b, Vec* size, bool scale, bool rot);
extern "C" void GSboundAddPoint(GSbound* b, f32 x, f32 y, f32 z);

static inline void _boundGenPointList(Vec* points, Vec* mm)
{
    points[0].x = mm[0].x;
    points[0].y = mm[0].y;
    points[0].z = mm[0].z;
    points[1].x = mm[0].x;
    points[1].y = mm[0].y;
    points[1].z = mm[1].z;
    points[2].x = mm[0].x;
    points[2].y = mm[1].y;
    points[2].z = mm[0].z;
    points[3].x = mm[0].x;
    points[3].y = mm[1].y;
    points[3].z = mm[1].z;
    points[4].x = mm[1].x;
    points[4].y = mm[0].y;
    points[4].z = mm[0].z;
    points[5].x = mm[1].x;
    points[5].y = mm[0].y;
    points[5].z = mm[1].z;
    points[6].x = mm[1].x;
    points[6].y = mm[1].y;
    points[6].z = mm[0].z;
    points[7].x = mm[1].x;
    points[7].y = mm[1].y;
    points[7].z = mm[1].z;
}

extern "C" {

void GSboundCreate(GSbound* b, BoundAnim* anim)
{
    memset(b, 0, sizeof(GSbound));
    if (anim == 0) {
        b->flags |= 1;
    } else {
        s32 i;
        u16* p;
        BOUND_ANIM(b) = anim;
        BOUND_ANIM_INDEX(b) = 0;
        BOUND_ANIM_FRAME(b) = 0.0f;
        BOUND_ANIM_TABLE_PTR(b) = GSmemAlloc((BOUND_ANIM(b))->count * sizeof(u16*));
        p = (u16*) (BOUND_ANIM(b) + 1);
        for (i = 0; i < (BOUND_ANIM(b))->count; i++) {
            BOUND_ANIM_TABLE(b)[i] = p;
            p = (u16*) ((u8*) (p + 2) + p[1] * 0x18);
        }
        b->flags |= 8;
    }
}

void GSboundFree(GSbound* b)
{
    b->type = 0;
    if (b->flags & 8) {
        GSmemFree(BOUND_ANIM_TABLE_PTR(b));
        BOUND_ANIM_TABLE_PTR(b) = 0;
    }
}

void GSboundSetDataPtr(GSbound* b, s32 type, void* data)
{
    if (data == 0) {
        b->type = 0;
        return;
    }
    b->type = type;
    switch (type) {
    case 1:
    case 2:
    case 3:
        b->data = data;
        break;
    default:
        b->type = 0;
        b->data = 0;
        break;
    }
}

void GSboundReset(GSbound* b)
{
    if (b->flags & 8) {
        return;
    }
    b->flags |= 1;
}

void GSboundAddPoint(GSbound* b, f32 x, f32 y, f32 z)
{
    if (b->flags & 8) {
        return;
    }
    if (b->flags & 1) {
        b->minX = x;
        b->minY = y;
        b->minZ = z;
        b->maxX = x;
        b->maxY = y;
        b->maxZ = z;
        b->flags &= ~1;
        return;
    }
    if (x < b->minX) {
        b->minX = x;
    }
    if (y < b->minY) {
        b->minY = y;
    }
    if (z < b->minZ) {
        b->minZ = z;
    }
    if (x > b->maxX) {
        b->maxX = x;
    }
    if (y > b->maxY) {
        b->maxY = y;
    }
    if (z > b->maxZ) {
        b->maxZ = z;
    }
}

}

static s32 _boundIsInScreenView(Vec* screen)
{
    s32 i;
    u8 orCode = 0;
    u8 andCode = 0x1f;
    for (i = 0; i < 8; i++) {
        u8 code;
        if (screen[i].x < 0.0f) {
            code = 1;
        } else if (screen[i].x > 640.0f) {
            code = 2;
        } else {
            code = 0;
        }
        if (screen[i].y < 0.0f) {
            code |= 4;
        } else if (screen[i].y > 480.0f) {
            code |= 8;
        }
        if (screen[i].z == -1.0f) {
            code |= 0x10;
        }
        orCode |= code;
        andCode &= code;
    }
    if (orCode == 0) {
        return 2;
    } else if (andCode != 0) {
        return 0;
    } else {
        return 1;
    }
}

extern "C" {

s32 GSboundIsInViewFast(GSbound* b)
{
    Vec mm[2];
    Vec points[8];
    Vec screen[8];

    if (b->flags & 4) {
        return 2;
    }
    GSboundGetMinMax(b, &mm[0], &mm[1], true, true, true, false);
    _boundGenPointList(points, mm);
    if (GSgfxProjectFastList(points, screen, 8) != 2) {
        return 2;
    }
    return _boundIsInScreenView(screen);
}

void GSboundAlwaysInView(GSbound* b, bool enable)
{
    if (enable) {
        b->flags |= 4;
    } else {
        b->flags &= ~4;
    }
}

}

void GSboundDraw(GSbound* b, GSgfxLayer* layer)
{
    Mtx m;
    Mtx sm;
    Mtx tm;
    Mtx qm;
    Mtx qm3;
    Vec size;
    Vec center;
    Vec rot;
    Quaternion q;
    Vec mx;
    Vec mn;
    f32 cx;
    f32 lo = -0.5f;
    f32 hi = 0.5f;

    if ((*(s32*)&layer->curPass) == 1 && !(b->flags & 1)) {
        GSboundGetSize(b, &size, true, false);
        if (!(PSVECSquareMag(&size) < 0.00001f)) {
            GScameraLoadActiveCameraMatrix((*(s32*)&layer->id));
            (*(u8*)&layer->hw.colorUpdate) = 1;
            (*(u8*)&layer->hw.alphaUpdate) = 1;
            (*(u8*)&layer->hw.zUpdate) = 0;
            (*(u32*)&layer->dirty[0].pe) |= 4;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 4;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(u8*)&layer->hw.zEnable) = 0;
            (*(s32*)&layer->hw.zFunc) = 3;
            (*(u32*)&layer->dirty[0].pe) |= 8;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 8;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(s32*)&layer->hw.alphaComp0) = 7;
            (*(u8*)&layer->hw.alphaRef0) = 0;
            (*(s32*)&layer->hw.alphaCmpOp) = 0;
            (*(s32*)&layer->hw.alphaComp1) = 7;
            (*(u8*)&layer->hw.alphaRef1) = 0;
            (*(u8*)&layer->hw.zCompLoc) = 1;
            (*(u32*)&layer->dirty[0].pe) |= 0x10;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 0x10;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(s32*)&layer->hw.cullMode) = 0;
            (*(u32*)&layer->dirty[0].raster) |= 2;
            (*(u32*)&layer->dirty[0].groups) |= 2;
            (*(u32*)&layer->dirty[1].raster) |= 2;
            (*(u32*)&layer->dirty[1].groups) |= 2;
            if ((*(s32*)&layer->curPass) != 1) {
                (*(s32*)&layer->curPass) = 1;
                layer->curFifo = &layer->passes[layer->curPass];
            }
            (*(s32*)&layer->hw.blend[0]) = 1;
            (*(s32*)&layer->hw.blend[1]) = 4;
            (*(s32*)&layer->hw.blend[2]) = 1;
            (*(s32*)&layer->hw.blend[3]) = 5;
            (*(u32*)&layer->dirty[0].pe) |= 1;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 1;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(s32*)&layer->hw.clipMode) = 0;
            (*(u32*)&layer->dirty[0].raster) |= 4;
            (*(u32*)&layer->dirty[0].groups) |= 2;
            (*(u32*)&layer->dirty[1].raster) |= 4;
            (*(u32*)&layer->dirty[1].groups) |= 2;
            (*(u8*)&layer->hw.lineWidth) = 6;
            (*(s32*)&layer->hw.lineOffset) = 0;
            (*(u32*)&layer->dirty[0].geom) |= 4;
            (*(u32*)&layer->dirty[0].groups) |= 1;
            (*(u32*)&layer->dirty[1].geom) |= 4;
            (*(u32*)&layer->dirty[1].groups) |= 1;
            layer->setRenderState(true, 0, false);
            layer->curVF = (GSgfxVF*)GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0);
            PSMTXScale(m, size.x, size.y, size.z);
            switch (b->type) {
            case 1:
                GSmodelGetRotation(b->data, &rot);
                EulerToQuat(&rot, &q);
                PSMTXQuat(qm, &q);
                PSMTXConcat(qm, m, m);
                break;
            case 2: {
                PSMTXCopy(*(Mtx*) b->data, tm);
                tm[0][3] = 0.0f;
                tm[1][3] = 0.0f;
                tm[2][3] = 0.0f;
                Mtx* src = (Mtx*) b->data;
                f32 s0 = PSVECMag((Vec*) &(*src)[0][0]);
                f32 s1 = PSVECMag((Vec*) &(*src)[1][0]);
                PSMTXScale(sm, s0, s1, PSVECMag((Vec*) &(*src)[2][0]));
                PSMTXInverse(sm, sm);
                PSMTXConcat(sm, tm, tm);
                PSMTXConcat(tm, m, m);
                break;
            }
            case 3:
                PSMTXQuat(qm3, &((BoundData3*) b->data)->rot);
                PSMTXConcat(qm3, m, m);
                break;
            }
            GSboundGetMinMax(b, &mn, &mx, true, true, true, false);
            PSVECAdd(&mn, &mx, &center);
            PSVECScale(&center, &center, 0.5f);
            PSMTXTransApply(m, m, center.x, center.y, center.z);
            (*(GSgfxMatrixStack**)&layer->matrixStack)->pushMult((GSmtx*) m);
            (*(u32*)&layer->unk1998) = 0x80;
            layer->beginSurface(0x18);
            for (cx = lo; cx < 1.0f; cx += 1.0f) {
                GXWGFifo.f32 = cx;
                GXWGFifo.f32 = lo;
                GXWGFifo.f32 = lo;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = cx;
                GXWGFifo.f32 = hi;
                GXWGFifo.f32 = lo;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = cx;
                GXWGFifo.f32 = hi;
                GXWGFifo.f32 = hi;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = cx;
                GXWGFifo.f32 = lo;
                GXWGFifo.f32 = hi;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = lo;
                GXWGFifo.f32 = cx;
                GXWGFifo.f32 = lo;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = hi;
                GXWGFifo.f32 = cx;
                GXWGFifo.f32 = lo;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = hi;
                GXWGFifo.f32 = cx;
                GXWGFifo.f32 = hi;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = lo;
                GXWGFifo.f32 = cx;
                GXWGFifo.f32 = hi;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = lo;
                GXWGFifo.f32 = lo;
                GXWGFifo.f32 = cx;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = hi;
                GXWGFifo.f32 = lo;
                GXWGFifo.f32 = cx;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = hi;
                GXWGFifo.f32 = hi;
                GXWGFifo.f32 = cx;
                GXWGFifo.u32 = 0x80808040;
                GXWGFifo.f32 = lo;
                GXWGFifo.f32 = hi;
                GXWGFifo.f32 = cx;
                GXWGFifo.u32 = 0x80808040;
            }
            layer->endSurface();
            (*(u8*)&layer->hw.zEnable) = 1;
            (*(s32*)&layer->hw.zFunc) = 3;
            (*(u32*)&layer->dirty[0].pe) |= 8;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 8;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            if ((*(s32*)&layer->curPass) != 1) {
                (*(s32*)&layer->curPass) = 1;
                layer->curFifo = &layer->passes[layer->curPass];
            }
            (*(s32*)&layer->hw.blend[0]) = 1;
            (*(s32*)&layer->hw.blend[1]) = 4;
            (*(s32*)&layer->hw.blend[2]) = 5;
            (*(s32*)&layer->hw.blend[3]) = 5;
            (*(u32*)&layer->dirty[0].pe) |= 1;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 1;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(u32*)&layer->unk1998) = 0xb0;
            layer->beginSurface(5);
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = hi;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = hi;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            layer->endSurface();
            layer->beginSurface(5);
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = hi;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = hi;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            layer->endSurface();
            (*(u32*)&layer->unk1998) = 0xa8;
            layer->beginSurface(8);
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = lo;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = hi;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = hi;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = hi;
            GXWGFifo.u32 = 0x80808080;
            GXWGFifo.f32 = hi;
            GXWGFifo.f32 = lo;
            GXWGFifo.f32 = hi;
            GXWGFifo.u32 = 0x80808080;
            layer->endSurface();
            (*(GSgfxMatrixStack**)&layer->matrixStack)->pop();
        }
    }
}

extern "C" {

u8 GSboundHasAnimData(GSbound* b)
{
    return (b->flags >> 3) & 1;
}

void GSboundSetAnimIndex(GSbound* b, s32 index)
{
    if (!(b->flags & 8)) {
        return;
    }
    BOUND_ANIM_INDEX(b) = index;
    BOUND_ANIM_FRAME(b) = 0.0f;
}

void GSboundSetAnimFrame(GSbound* b, f32 frame)
{
    if (b->flags & 8) {
        u16** table = BOUND_ANIM_TABLE(b);
        u16 count = table[BOUND_ANIM_INDEX(b)][1];
        if (frame >= (f32) count) {
            frame = (f32) (count - 1);
        }
        BOUND_ANIM_FRAME(b) = frame;
    }
}

void GSboundGetMinMax(GSbound* b, Vec* min, Vec* max, bool scale, bool rot, bool trans, bool ignoreRoot)
{
    Mtx m;
    Mtx qm;
    Mtx qm2;
    Mtx qm3;
    Mtx qm4;
    Vec v;
    Quaternion q;
    Quaternion q2;

    if (b->flags & 8) {
        u16** table = BOUND_ANIM_TABLE(b);
        f32* entry = (f32*) ((u8*) table[BOUND_ANIM_INDEX(b)] + (s32) BOUND_ANIM_FRAME(b) * 0x18);
        min->x = entry[1];
        min->y = entry[2];
        min->z = entry[3];
        max->x = entry[4];
        max->y = entry[5];
        max->z = entry[6];
    } else {
        min->x = b->minX;
        min->y = b->minY;
        min->z = b->minZ;
        max->x = b->maxX;
        max->y = b->maxY;
        max->z = b->maxZ;
    }
    switch (b->type) {
    case 1:
        if (ignoreRoot || GSmodelIsRootNullAdded(b->data) == 0) {
            PSMTXIdentity(m);
        } else {
            GSmodelGetRootScale(b->data, &v);
            PSMTXScale(m, v.x, v.y, v.z);
            GSmodelGetRootRotation(b->data, &v);
            EulerToQuat(&v, &q);
            PSMTXQuat(qm, &q);
            PSMTXConcat(qm, m, m);
            GSmodelGetRootPosition(b->data, &v);
            PSMTXTransApply(m, m, v.x, v.y, v.z);
        }
        if (scale) {
            GSmodelGetScale(b->data, &v);
            PSMTXScaleApply(m, m, v.x, v.y, v.z);
        }
        if (rot) {
            GSmodelGetRotation(b->data, &v);
            EulerToQuat(&v, &q);
            PSMTXQuat(qm2, &q);
            PSMTXConcat(qm2, m, m);
        }
        if (trans) {
            GSmodelGetPosition(b->data, &v);
            PSMTXTransApply(m, m, v.x, v.y, v.z);
        }
        PSMTXMultVec(m, min, min);
        PSMTXMultVec(m, max, max);
        return;
    case 2: {
        if (scale && rot && trans) {
            PSMTXMultVec((f32(*)[4]) b->data, min, min);
            PSMTXMultVec((f32(*)[4]) b->data, max, max);
            return;
        }
        if (scale && rot) {
            PSMTXMultVecSR((f32(*)[4]) b->data, min, min);
            PSMTXMultVecSR((f32(*)[4]) b->data, max, max);
            return;
        }
        if (scale) {
            f32 (*src)[4] = (f32(*)[4]) b->data;
            f32 sx = PSVECMag((Vec*) &src[0][0]);
            f32 sy = PSVECMag((Vec*) &src[1][0]);
            PSMTXScale(m, sx, sy, PSVECMag((Vec*) &src[2][0]));
        } else if (rot) {
            C_QUATMtx(&q2, (f32(*)[4]) b->data);
            PSMTXQuat(m, &q2);
        }
        if (trans) {
            f32 (*src)[4] = (f32(*)[4]) b->data;
            PSMTXTransApply(m, m, src[0][3], src[1][3], src[2][3]);
        }
        PSMTXMultVec(m, min, min);
        PSMTXMultVec(m, max, max);
        return;
    }
    case 3: {
        if (scale) {
            BoundData3* d = (BoundData3*) b->data;
            min->x *= d->scale.x;
            min->y *= d->scale.y;
            min->z *= d->scale.z;
            d = (BoundData3*) b->data;
            max->x *= d->scale.x;
            max->y *= d->scale.y;
            max->z *= d->scale.z;
        }
        if (rot) {
            PSMTXQuat(qm3, &((BoundData3*) b->data)->rot);
            PSMTXMultVecSR(qm3, min, min);
            PSMTXQuat(qm4, &((BoundData3*) b->data)->rot);
            PSMTXMultVecSR(qm4, max, max);
        }
        if (trans) {
            PSVECAdd(min, &((BoundData3*) b->data)->pos, min);
            PSVECAdd(max, &((BoundData3*) b->data)->pos, max);
        }
        return;
    }
    }
}

void GSboundGetSize(GSbound* b, Vec* size, bool scale, bool rot)
{
    Mtx m;
    Mtx sm;
    Vec mn;
    Vec mx;
    Vec v;
    Quaternion q;
    Vec diff;
    f32 sz;
    f32 sy;
    f32 sx;
    s32 i;

    GSboundGetMinMax(b, &mn, &mx, scale, false, false, false);
    PSVECSubtract(&mx, &mn, &diff);
    f32 dx = diff.x;
    f32 dy = diff.y;
    f32 dz = diff.z;
    size->x = dx;
    size->y = dy;
    size->z = dz;
    if (size->x < 0.0f) {
        size->x = -size->x;
    }
    if (size->y < 0.0f) {
        size->y = -size->y;
    }
    if (size->z < 0.0f) {
        size->z = -size->z;
    }
    if (!rot) {
        return;
    }
    switch (b->type) {
    case 1:
        GSmodelGetRotation(b->data, &v);
        EulerToQuat(&v, &q);
        PSMTXQuat(m, &q);
        break;
    case 2: {
        PSMTXCopy((f32(*)[4]) b->data, m);
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        f32 (*src)[4] = (f32(*)[4]) b->data;
        f32 a = PSVECMag((Vec*) &src[0][0]);
        f32 c = PSVECMag((Vec*) &src[1][0]);
        PSMTXScale(sm, a, c, PSVECMag((Vec*) &src[2][0]));
        PSMTXInverse(sm, sm);
        PSMTXConcat(sm, m, m);
        break;
    }
    case 3:
        PSMTXQuat(m, &((BoundData3*) b->data)->rot);
        break;
    default:
        return;
    }
    sx = size->x;
    sy = size->y;
    sz = size->z;
    PSMTXMultVec(m, size, size);
    for (s32 i_loop = 0; i_loop < 3; i_loop++) {
        f32* p = &v.x + i_loop;
        v.x = sx;
        v.y = sy;
        v.z = sz;
        *p *= -1.0f;
        PSMTXMultVec(m, &v, &v);
        if (v.x < 0.0f) {
            v.x = -v.x;
        }
        if (v.y < 0.0f) {
            v.y = -v.y;
        }
        if (v.z < 0.0f) {
            v.z = -v.z;
        }
        if (v.x > size->x) {
            size->x = v.x;
        }
        if (v.y > size->y) {
            size->y = v.y;
        }
        if (v.z > size->z) {
            size->z = v.z;
        }
    }
}

void GSboundGetWorldPosition(GSbound* b, Vec* out)
{
    Vec mn;
    Vec mx;
    GSboundGetMinMax(b, &mn, &mx, true, true, true, false);
    PSVECAdd(&mn, &mx, out);
    PSVECScale(out, out, 0.5f);
}

void GSboundGetLocalPosition(GSbound* b, Vec* out)
{
    Vec mn;
    Vec mx;
    GSboundGetMinMax(b, &mn, &mx, false, false, false, false);
    PSVECAdd(&mn, &mx, out);
    PSVECScale(out, out, 0.5f);
}

void GSboundGetShadowVolume(GSbound* out, GSbound* b, Vec* plane, f32 height)
{
    Vec corners[8];
    Mtx m;
    Mtx qm;
    Vec mm[2];
    Vec t3;
    Vec center;
    Quaternion q;
    Vec t;
    Vec t5;
    Vec s2;
    Vec t2;
    Vec t4;
    Vec t6;
    Vec r;
    Vec sum;
    Vec s;
    f32 dh;
    Vec* p;
    s32 i;

    memset(out, 0, sizeof(GSbound));
    out->flags |= 1;
    GSboundGetMinMax(b, &mm[0], &mm[1], false, false, false, false);
    _boundGenPointList(corners, mm);
    PSVECAdd(&mm[0], &mm[1], &sum);
    t = sum;
    PSVECScale(&t, &t2, 0.5f);
    center = t2;
    switch (b->type) {
    case 1:
        GSmodelGetScale(b->data, &t3);
        PSMTXScale(m, t3.x, t3.y, t3.z);
        GSmodelGetRotation(b->data, &t3);
        EulerToQuat(&t3, &q);
        PSMTXQuat(qm, &q);
        PSMTXConcat(qm, m, m);
        GSmodelGetPosition(b->data, &t3);
        PSMTXTransApply(m, m, t3.x, t3.y, t3.z);
        break;
    case 2:
        PSMTXCopy((f32(*)[4]) b->data, m);
        break;
    case 3: {
        BoundData3* d = (BoundData3*) b->data;
        PSMTXScale(m, d->scale.x, d->scale.y, d->scale.z);
        Mtx qm3;
        PSMTXQuat(qm3, &((BoundData3*) b->data)->rot);
        PSMTXConcat(qm3, m, m);
        d = (BoundData3*) b->data;
        PSMTXTransApply(m, m, d->pos.x, d->pos.y, d->pos.z);
        break;
    }
    default:
        PSMTXIdentity(m);
        break;
    }
    dh = plane->y - height;
    if (!(dh < 0.00001f && dh > -0.00001f)) {
        p = corners;
        for (i = 0; i < 8; i++, p++) {
            PSVECSubtract(p, &center, p);
            PSMTXMultVec(m, p, p);
            PSMTXMultVecSR(m, &center, &t4);
            t5 = t4;
            PSVECAdd(p, &t5, p);
            PSVECSubtract(p, plane, &t6);
            t3 = t6;
            f32 den = t3.y - height;
            if (!(t3.y < 0.00001f && t3.y > -0.00001f)) {
                PSVECScale(&t3, &s, dh / den);
                s2 = s;
                PSVECSubtract(plane, &s2, &r);
                *p = r;
                GSboundAddPoint(out, p->x, p->y, p->z);
            }
        }
    }
}

void GSboundGetShadowSize(Vec* out, GSbound* b, Vec* p1, Vec* p2, Vec* dir)
{
    f32 s1;
    Vec mn;
    Vec mx;
    Vec up;
    Vec right;
    Vec fwd;
    Quaternion q;
    Vec n;
    Vec n2;
    Vec x1;
    Vec x2;
    Vec x3;
    Vec d;
    Vec c[4];
    Mtx m;
    Mtx sm;
    f32 a;
    f32 s0;
    f32 maxA;
    f32 maxB;
    f32 bb;
    Vec* cp;

    PSVECNormalize(dir, &n);
    up = n;
    PSVECSubtract(p2, p1, &n2);
    fwd = n2;
    PSVECNormalize(&fwd, &fwd);
    PSVECCrossProduct(&up, &fwd, &x1);
    right = x1;
    PSVECNormalize(&right, &right);
    PSVECCrossProduct(&fwd, &right, &x2);
    up = x2;
    GSboundGetMinMax(b, &mn, &mx, true, false, false, false);
    switch (b->type) {
    case 1:
        GSmodelGetRotation(b->data, &fwd);
        EulerToQuat(&fwd, &q);
        PSMTXQuat(m, &q);
        break;
    case 2: {
        PSMTXCopy((f32(*)[4]) b->data, m);
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        f32 (*src)[4] = (f32(*)[4]) b->data;
        s0 = PSVECMag((Vec*) &src[0][0]);
        s1 = PSVECMag((Vec*) &src[1][0]);
        PSMTXScale(sm, s0, s1, PSVECMag((Vec*) &src[2][0]));
        PSMTXInverse(sm, sm);
        PSMTXConcat(sm, m, m);
        break;
    }
    case 3:
        PSMTXQuat(m, &((BoundData3*) b->data)->rot);
        break;
    default:
        PSMTXIdentity(m);
        break;
    }
    PSVECSubtract(&mx, &mn, &x3);
    fwd = x3;
    if (fwd.x < 0.0f) {
        fwd.x = -fwd.x;
    }
    if (fwd.y < 0.0f) {
        fwd.y = -fwd.y;
    }
    if (fwd.z < 0.0f) {
        fwd.z = -fwd.z;
    }
    c[0] = fwd;
    c[1] = fwd;
    c[1].y *= -1.0f;
    c[2] = fwd;
    c[2].x *= -1.0f;
    c[3] = fwd;
    c[3].x *= -1.0f;
    c[3].y *= -1.0f;
    maxA = 0.0f;
    maxB = 0.0f;
    cp = c;
    for (s32 i_loop = 0; i_loop < 4; i_loop++, cp++) {
        PSMTXMultVec(m, cp, cp);
        if (PSVECDotProduct(cp, &right) > 0.0f) {
            a = PSVECDotProduct(cp, &right);
        } else {
            f32 t = PSVECDotProduct(cp, &right);
            a = -t;
        }
        if (PSVECDotProduct(cp, &up) > 0.0f) {
            bb = PSVECDotProduct(cp, &up);
        } else {
            bb = -PSVECDotProduct(cp, &up);
        }
        if (a > maxA) {
            maxA = a;
        }
        if (bb > maxB) {
            maxB = bb;
        }
    }
    out->x = maxA;
    out->y = 0.0f;
    out->z = maxB;
}

}
