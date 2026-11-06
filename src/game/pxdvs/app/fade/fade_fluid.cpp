#pragma peephole off
#include <dolphin/types.h>
#include <game/gcptr.h>
#pragma pool_strings off
#include <dolphin/gx/GXVert.h>

struct GSgfxVF;
struct GStexture {
    u8 unk0[7];
    u8 unk7;
};

struct BlendState {
    u8 pad[0xbc];
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderStateAndSelect(struct GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

};

struct GSvec {
    f32 x, y, z;
    void set(f32 a, f32 b, f32 c) {
        x = a;
        y = b;
        z = c;
    }
};

struct GSvec2 {
    f32 x, y;
};

struct FadeFluidWork {
    u32 columns;
    u32 rows;
    f32 accel;
    f32 damping;
    f32 neighbor;
    f32 limit;
    f32 timeStep;
    f32 cellSize;
    f32 xScale;
    f32 yScale;
    GSvec* heightPage[2];
    GSvec* velocityX;
    GSvec* velocityY;
    GSvec2* texCoord;
    u8 pad_3C[4];
};

extern "C" {
GSgfxLayer* GSgfxLayerFindByID(GCsint id);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void spriteSetEnv(int layerID);
void GSlerpGetLinearInterpolationVector(GSvec* out, GSvec* a, GSvec* b, f32 t);
void GSmemFree(void* ptr);
void* GSmemAllocAlign(u32 size, u32 align);
s32 GSmemGetCurrentHeap();
s32 GSmemSetAllocMethodHeap(s32 heap, s32 method);
void OSReport(const char* msg, ...);
}

#ifdef __cplusplus
extern "C" f32 __float_nan[];
#else
extern f32 __float_nan[];
#endif

union FadeFloatShape {
    f32 value;
    s32 bits;
};

static inline f32 fadeSqrtf(f32 value) {
    FadeFloatShape shape;
    f64 estimate;
    s32 exponent;
    s32 fpclass;

    if (value > 0.0f) {
        const f64 half = 0.5;
        const f64 three = 3.0;

        estimate = __frsqrte(value);
        estimate = half * estimate * (three - value * (estimate * estimate));
        estimate = half * estimate * (three - value * (estimate * estimate));
        estimate = half * estimate * (three - value * (estimate * estimate));
        return (f32)(value * estimate);
    }
    if ((f64)value < 0.0) {
        return __float_nan[0];
    }

    shape.value = value;
    exponent = shape.bits & 0x7F800000;
    switch (exponent) {
    case 0x7F800000:
        fpclass = (shape.bits & 0x007FFFFF) != 0 ? 1 : 2;
        break;
    case 0:
        fpclass = (shape.bits & 0x007FFFFF) != 0 ? 5 : 3;
        break;
    default:
        fpclass = 4;
        break;
    }
    if (fpclass == 1) {
        return __float_nan[0];
    }
    return value;
}

static FadeFluidWork _fadeFluidWork;
static u32 _fadeFluidSw;

static void _fadeFluidSetShockSub(u32 x, u32 y, f32 strength);
static void _fadeFluidDoFree(void* ptr);
static void* _fadeFluidDoMalloc(u32 size);

extern "C" {

void fadeFluidDispSecond(int layerID, GStexture* tex, f32 progress, f32 blend) {
    enum TsE { TsE0 };
    GSvec** page;
    GSvec2* tc;
    u32 row1;
    s32 y;
    u32 row0;
    GSgfxLayer* layer = GSgfxLayerFindByID(layerID);
    GSvec interpolated;
    GSvec to;
    GSvec from;
    enum TsE alpha;
    u32 x;

    to.z = to.y = to.x = 1.0f;
    from.z = from.y = from.x = 0.0f;
    GSlerpGetLinearInterpolationVector(&interpolated, &to, &from, blend);
    alpha = (enum TsE)((s32)(255.0f * interpolated.x));
    alpha = (enum TsE)((s32)((f32)alpha * (1.0f - progress)));
    spriteSetEnv(layerID);
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
    (*(u8*)&layer->hw.colorUpdate) = 1;
    (*(u8*)&layer->hw.alphaUpdate) = 1;
    (*(u8*)&layer->hw.zUpdate) = 0;
    (*(u32*)&layer->dirty[0].pe) |= 4;
    (*(u32*)&layer->dirty[0].groups) |= 0x40;
    (*(u32*)&layer->dirty[1].pe) |= 4;
    (*(u32*)&layer->dirty[1].groups) |= 0x40;
    (*(u8*)&layer->hw.zEnable) = 0;
    (*(s32*)&layer->hw.zFunc) = 1;
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
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 1, 1, 4));
    if ((*(void**)&layer->dirty[0].tex[0]) != tex || (*(void**)&layer->dirty[1].tex[0]) != tex || tex->unk7 != 0) {
        (*(void**)&layer->dirty[0].tex[0]) = tex;
        (*(u32*)&layer->dirty[0].texMask) |= 1;
        (*(void**)&layer->dirty[1].tex[0]) = tex;
        (*(u32*)&layer->dirty[1].texMask) |= 1;
    }
    FadeFluidWork* work = &_fadeFluidWork;
    u32 stride = work->columns + 1;
    f32 xScale = work->xScale;
    f32 yScale = work->yScale;
    for (y = 0; y < work->rows; y++) {
        (*(u32*)&layer->unk1998) = 0x98;
        layer->beginSurface(stride * 2);
        page = &_fadeFluidWork.heightPage[_fadeFluidSw];
        row0 = y * stride;
        row1 = (y + 1) * stride;
        tc = work->texCoord;
        for (x = 0; x < stride; x++) {
            GSvec* p0 = &(*page)[x + row0];
            GSvec2* t0 = &tc[x + row0];
            GXPosition3f32(p0->x * xScale, p0->y * yScale, p0->z * xScale);
            GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
            GXTexCoord2f32(t0->x, t0->y);
            GSvec* p1 = &(*page)[x + row1];
            GSvec2* t1 = &tc[x + row1];
            GXPosition3f32(p1->x * xScale, p1->y * yScale, p1->z * xScale);
            GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
            GXTexCoord2f32(t1->x, t1->y);
        }
        layer->endSurface();
    }
}

void fadeFluidDisp(GStexture* tex, f32 progress, f32 blend) {
    enum TsE { TsE0 };
    GSvec** page;
    GSvec2* tc;
    u32 row1;
    s32 y;
    u32 row0;
    GSgfxLayer* layer = GSgfxLayerFindByID(7);
    GSvec interpolated;
    GSvec to;
    GSvec from;
    enum TsE alpha;
    u32 x;

    to.z = to.y = to.x = 1.0f;
    from.z = from.y = from.x = 0.0f;
    GSlerpGetLinearInterpolationVector(&interpolated, &to, &from, blend);
    alpha = (enum TsE)((s32)(255.0f * interpolated.x));
    alpha = (enum TsE)((s32)((f32)alpha * (1.0f - progress)));
    spriteSetEnv(7);
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
    (*(u8*)&layer->hw.colorUpdate) = 1;
    (*(u8*)&layer->hw.alphaUpdate) = 1;
    (*(u8*)&layer->hw.zUpdate) = 0;
    (*(u32*)&layer->dirty[0].pe) |= 4;
    (*(u32*)&layer->dirty[0].groups) |= 0x40;
    (*(u32*)&layer->dirty[1].pe) |= 4;
    (*(u32*)&layer->dirty[1].groups) |= 0x40;
    (*(u8*)&layer->hw.zEnable) = 0;
    (*(s32*)&layer->hw.zFunc) = 1;
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
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 1, 1, 4));
    if ((*(void**)&layer->dirty[0].tex[0]) != tex || (*(void**)&layer->dirty[1].tex[0]) != tex || tex->unk7 != 0) {
        (*(void**)&layer->dirty[0].tex[0]) = tex;
        (*(u32*)&layer->dirty[0].texMask) |= 1;
        (*(void**)&layer->dirty[1].tex[0]) = tex;
        (*(u32*)&layer->dirty[1].texMask) |= 1;
    }
    (*(u32*)&layer->unk1998) = 0x98;
    FadeFluidWork* work = &_fadeFluidWork;
    u32 stride = work->columns + 1;
    f32 xScale = work->xScale;
    f32 yScale = work->yScale;
    for (y = 0; y < work->rows; y++) {
        layer->beginSurface(stride * 2);
        page = &_fadeFluidWork.heightPage[_fadeFluidSw];
        row0 = y * stride;
        row1 = (y + 1) * stride;
        tc = work->texCoord;
        for (x = 0; x < stride; x++) {
            GSvec* p0 = &(*page)[x + row0];
            GSvec2* t0 = &tc[x + row0];
            GXPosition3f32(p0->x * xScale, p0->y * yScale, p0->z * xScale);
            GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
            GXTexCoord2f32(t0->x, t0->y);
            GSvec* p1 = &(*page)[x + row1];
            GSvec2* t1 = &tc[x + row1];
            GXPosition3f32(p1->x * xScale, p1->y * yScale, p1->z * xScale);
            GXColor4u8(0xFF, 0xFF, 0xFF, (u8)alpha);
            GXTexCoord2f32(t1->x, t1->y);
        }
        layer->endSurface();
    }
}

void fadeFluidSetShockSecond(GSvec* position, f32 strength) {
    f32 cellSize = _fadeFluidWork.cellSize;
    u32 x = position->x / cellSize;
    u32 y = position->y / cellSize;
    f32 edge, corner;

    _fadeFluidSetShockSub(x, y, strength);
    edge = 0.5f * strength;
    corner = 0.25f * strength;
    _fadeFluidSetShockSub(x - 1, y - 1, corner);
    _fadeFluidSetShockSub(x, y - 1, edge);
    _fadeFluidSetShockSub(x + 1, y - 1, corner);
    _fadeFluidSetShockSub(x - 1, y, edge);
    _fadeFluidSetShockSub(x + 1, y, edge);
    _fadeFluidSetShockSub(x - 1, y + 1, corner);
    _fadeFluidSetShockSub(x, y + 1, edge);
    _fadeFluidSetShockSub(x + 1, y + 1, corner);
}

void fadeFluidEvaluateSecond(void) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    GSvec* source;
    u32 rowStride = fluid->columns + 1;
    s32 x;
    s32 y;
    f32 accel = fluid->accel;
    f32 damping = fluid->damping;
    f32 neighbor = fluid->neighbor;

    for (y = 1; y < fluid->rows; y++) {
        u32 row = y * rowStride;
        GSvec* destination;
        source = _fadeFluidWork.heightPage[_fadeFluidSw] + row;
        destination = _fadeFluidWork.heightPage[1 - _fadeFluidSw] + row;

        for (x = 1; x < fluid->columns; x++) {
            destination[x].z =
                accel * source[x].z + damping * destination[x].z +
                neighbor * (source[x + 1].z + source[x - 1].z + source[x + rowStride].z +
                            source[x - rowStride].z);
        }
    }
    _fadeFluidSw = 1 - _fadeFluidSw;
}

void fadeFluidSetShock(GSvec* position, f32 strength) {
    f32 cellSize = _fadeFluidWork.cellSize;
    u32 x = position->x / cellSize;
    u32 y = position->y / cellSize;

    _fadeFluidSetShockSub(x, y, strength);
    strength *= 0.5f;
    _fadeFluidSetShockSub(x - 1, y - 1, strength);
    _fadeFluidSetShockSub(x, y - 1, strength);
    _fadeFluidSetShockSub(x + 1, y - 1, strength);
    _fadeFluidSetShockSub(x - 1, y, strength);
    _fadeFluidSetShockSub(x + 1, y, strength);
    _fadeFluidSetShockSub(x - 1, y + 1, strength);
    _fadeFluidSetShockSub(x, y + 1, strength);
    _fadeFluidSetShockSub(x + 1, y + 1, strength);
}

}

static void _fadeFluidSetShockSub(u32 x, u32 y, f32 strength) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    u32 columns = fluid->columns;

    if (x > columns) {
        return;
    }
    if (y > fluid->rows) {
        return;
    }

    ((f32*)fluid->heightPage[_fadeFluidSw])[3 * (x + (y * (columns + 1))) + 2] -= strength;
}

extern "C" {

void fadeFluidEvaluate(void) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    FadeFluidWork* work;
    u32 rowStride = fluid->columns + 1;
    GSvec* source;
    s32 x;
    s32 y;
    f32 accel = fluid->accel;
    f32 damping = fluid->damping;
    f32 neighbor = fluid->neighbor;

    for (y = 1; y < fluid->rows; y++) {
        u32 row = y * rowStride;
        GSvec* destination;
        source = _fadeFluidWork.heightPage[_fadeFluidSw] + row;
        destination = _fadeFluidWork.heightPage[1 - _fadeFluidSw] + row;

        for (x = 1; x < fluid->columns; x++) {
            destination[x].z =
                accel * source[x].z + damping * destination[x].z +
                neighbor * (source[x + 1].z + source[x - 1].z + source[x + rowStride].z +
                            source[x - rowStride].z);
        }
    }

    _fadeFluidSw = 1 - _fadeFluidSw;
    work = &_fadeFluidWork;
    for (y = 1; y < fluid->rows; y++) {
        u32 row = y * rowStride;
        GSvec* height = _fadeFluidWork.heightPage[_fadeFluidSw] + row;
        GSvec* velocityX = work->velocityX + row;
        GSvec* velocityY = work->velocityY + row;

        for (x = 1; x < work->columns; x++) {
            velocityX[x].x = height[x - 1].z - height[x + 1].z;
            velocityX[x].y = height[x - rowStride].z - height[x + rowStride].z;
            velocityY[x].z = height[x + 1].z - height[x - 1].z;
        }
    }
}

void fadeFluidCalcParms(f32 dt) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    f32 c = fluid->limit;
    f32 d = fluid->cellSize;
    f32 c2 = c * c;
    f32 d2 = d * d;
    f32 mt = fluid->timeStep * dt;
    f32 ct = dt * c2;
    f32 f1 = (dt * ct) / d2;
    f32 f2 = 1.0f / (2.0f + mt);
    f32 k1;
    f32 k2;
    f32 k3;

    k1 = 4.0f - 8.0f * f1;
    fluid->accel = k1 * f2;
    k2 = mt - 2.0f;
    fluid->damping = f2 * k2;
    k3 = 2.0f * f1;
    fluid->neighbor = k3 * f2;
}

void fadeFluidQuit(void) {
    FadeFluidWork* fluid0 = &_fadeFluidWork;
    FadeFluidWork* fluid1;
    FadeFluidWork* fluid2;
    FadeFluidWork* fluid3;
    FadeFluidWork* fluid4;

    if (fluid0->heightPage[0] != 0) {
        _fadeFluidDoFree(fluid0->heightPage[0]);
    }

    fluid1 = &_fadeFluidWork;
    if (fluid1->heightPage[1] != 0) {
        _fadeFluidDoFree(fluid1->heightPage[1]);
    }

    fluid2 = &_fadeFluidWork;
    if (fluid2->velocityX != 0) {
        _fadeFluidDoFree(fluid2->velocityX);
    }

    fluid3 = &_fadeFluidWork;
    if (fluid3->velocityY != 0) {
        _fadeFluidDoFree(fluid3->velocityY);
    }

    fluid4 = &_fadeFluidWork;
    if (fluid4->texCoord != 0) {
        _fadeFluidDoFree(fluid4->texCoord);
    }

    fluid0->heightPage[0] = 0;
    fluid1->heightPage[1] = 0;
    fluid2->velocityX = 0;
    fluid3->velocityY = 0;
    fluid4->texCoord = 0;
}

inline float fadeFluidInitInline(f32 arg0) { return 2.0f * arg0; }

void fadeFluidInit(u32 columns, u32 rows, f32 cellSize, f32 calcStep, f32 waveLimit, f32 timeStep) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    u32 pointCount;
    u32 vectorBytes;
    s32 x;
    s32 y;
    u32 index;
    f32 velocity;
    f32 texStepX;
    f32 texStepY;
    f32 maximumLimit;

    fluid->xScale = 640.0f / (f32)columns;
    pointCount = (columns + 1) * (rows + 1);
    vectorBytes = pointCount * sizeof(GSvec);
    fluid->yScale = 480.0f / (f32)rows;
    fluid->columns = columns;
    fluid->rows = rows;
    _fadeFluidWork.heightPage[0] = (GSvec*)_fadeFluidDoMalloc(vectorBytes);
    _fadeFluidWork.heightPage[1] = (GSvec*)_fadeFluidDoMalloc(vectorBytes);
    _fadeFluidSw = 0;
    _fadeFluidWork.velocityX = (GSvec*)_fadeFluidDoMalloc(vectorBytes);
    _fadeFluidWork.velocityY = (GSvec*)_fadeFluidDoMalloc(vectorBytes);
    _fadeFluidWork.texCoord = (GSvec2*)_fadeFluidDoMalloc(pointCount * sizeof(GSvec2));

    maximumLimit = (cellSize / (2.0f * calcStep)) * fadeSqrtf(2.0f + timeStep);
    if (!(0.0f < waveLimit && waveLimit < maximumLimit)) {
        OSReport("Warning: fadeFluid c parm. Limit Over!! -> 0.0f < %f < %f\n", waveLimit,
                 maximumLimit);
        waveLimit = maximumLimit - 1.0e-6f;
    }
    _fadeFluidWork.cellSize = cellSize;
    _fadeFluidWork.limit = waveLimit;
    _fadeFluidWork.timeStep = timeStep;
    fadeFluidCalcParms(calcStep);

    velocity = fadeFluidInitInline(cellSize);
    texStepX = 1.0f / (f32)_fadeFluidWork.columns;
    texStepY = 1.0f / (f32)fluid->rows;
    index = 0;
    for (y = 0; y <= rows; y++) {
        for (x = 0; x <= columns; x++) {
            _fadeFluidWork.heightPage[0][index].set(cellSize * (f32)x, cellSize * (f32)y, 0.0f);
            _fadeFluidWork.heightPage[1][index] = _fadeFluidWork.heightPage[0][index];
            _fadeFluidWork.velocityX[index].set(0.0f, 0.0f, velocity);
            _fadeFluidWork.velocityY[index].set(velocity, 0.0f, 0.0f);
            _fadeFluidWork.texCoord[index].x = texStepX * (f32)x;
            _fadeFluidWork.texCoord[index].y = texStepY * (f32)y;
            index++;
        }
    }
}

}

static void _fadeFluidDoFree(void* ptr) {
    GSmemFree(ptr);
}

static void* _fadeFluidDoMalloc(u32 size) {
    void* mem;
    s32 old = GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(), 3);
    mem = GSmemAllocAlign(size, 0x20);
    GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(), old);
    return mem;
}
