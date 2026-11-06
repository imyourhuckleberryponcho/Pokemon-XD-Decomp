#include <dolphin/types.h>
#include <game/gcptr.h>
#include <dolphin/mtx.h>
#include <dolphin/gx/GXVert.h>
#pragma pool_strings off

struct GSmtx {
    f32 m[3][4];
};

enum GSgfxLayerID { GS_LAYER_0, GS_LAYER_1, GS_LAYER_2 };

struct GSgfxVF;

class GSgfxMatrixStack {
public:
    void pushMult(GSmtx* mtx);
    void pop();
};

enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

};

struct GsShapeAnimHeader {
    u8 unk0[4];
    u32 frameCount;
    u32 fps;
    u8 unkC[8];
    u8 flag;
};

class GsShapeRender {
public:
    void SwapBuffers();
    GSgfxLayerID GetLayerId() const;
    s32 GetInstancedMemorySizeAll();
    s32 GetUsedMemorySizeAll();
    void FreeShapeRenderDrawBuffer(s16 id);
    s16 CreateShapeRenderDrawBuffer();
    void Render(s16 id, GSgfxLayerID layer);
    void Update(f32 time, s16 id);
    bool LoadShapeRender(void* file);
    void FreeShapeRender();
    void InitShapeRender();

    u8 loaded;
    u8 pad1[0xF];
    void* slot10;
    GsShapeAnimHeader* anim;
    u8 pad18[0x4];
    void* slot1C;
    u8 pad20[0x4];
    void* slot24;
    u8 pad28[0x4];
    void* slot2C;
    u8 pad30[0x8];
    void* slot38;
    void* slot3C;
    void* slot40;
    void* slot44;
    void* slot48;
    u8 pad4C[0x918];
};

struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(GSgfxLayer* layer, s32 pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 unk18;
};

void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);

extern "C" {
void* GSmemAlloc(u32 size);
void* GSmemAllocClr(u32 size);
void GSmemFree(void* p);
u8 GSgfxVideoGetVsyncRate(void);
f32 GSgfxVideoGetLastRenderTime(void);
GSgfxLayer* GSgfxLayerFindByID(GCsint id);
void GScameraLoadActiveCameraMatrix(int id);
GSgfxVF* GSgfxVFGetPredef(s32 id);
u32 GSgfxPerfbarCPUEntry(u32 id);
void GSprint(s32 layer, s32 x, s32 y, s32 color, const char* fmt, ...);
extern s32 g_instancedMemorySizeAll;
void shapePrimitiveEditorRender(GSgfxLayerID layerId);
}

static s16 g_primitiveInstanceId = -1;
static u8 g_primitiveEditorMode;
static u8 g_moduleInited;
static f32 g_primitiveFrameSec;
static u16 g_primitiveAnimation;
static u16 g_shapeRenderNum;
static GsShapeRender** g_shapeRender;

static inline GSgfxLayerID getEditorLayer() {
    if (g_primitiveEditorMode == 0) {
        return GS_LAYER_2;
    }
    if (g_shapeRenderNum != 0) {
        GsShapeRender* r = g_shapeRender[0];
        if (r != 0 && r->anim != 0) {
            return r->GetLayerId();
        }
    }
    return GS_LAYER_2;
}

static void _shapePreUpdate(f32 dt) {
    u16 i;
    for (i = 0; i < g_shapeRenderNum; i++) {
        GsShapeRender* r = g_shapeRender[i];
        if (r != 0 && r->anim != 0) {
            r->SwapBuffers();
        }
    }
}

static void _shapeFastRender() {
    if (g_primitiveEditorMode != 0) {
        GSgfxLayerID id = getEditorLayer();
        u32 perf = GSgfxPerfbarCPUEntry(0xFF00);
        shapePrimitiveEditorRender(id);
        GSgfxPerfbarCPUEntry(perf);
    }
}

extern "C" {

static inline void _shapeFreeAll() {
    u16 i;
    for (i = 0; i < g_shapeRenderNum; i++) {
        if (g_shapeRender[i] != 0) {
            g_shapeRender[i]->FreeShapeRender();
            GSmemFree(g_shapeRender[i]);
            g_shapeRender[i] = 0;
        }
    }
}

s32 shapeInit(u16 count) {
    g_primitiveEditorMode = 0;
    _shapeFreeAll();
    if (g_shapeRender != 0) {
        GSmemFree(g_shapeRender);
        g_shapeRender = 0;
    }
    g_shapeRenderNum = 0;
    if (g_moduleInited == 0) {
        GSgfxRenderModule module = {0, _shapePreUpdate, 0, _shapeFastRender, 0, 0, 0xB29A48E1};
        GSgfxRenderModuleRegister(0x50, &module, 0);
        g_moduleInited = 1;
    }
    g_shapeRender = (GsShapeRender**)GSmemAllocClr(count * sizeof(GsShapeRender*));
    if (g_shapeRender == 0) {
        g_shapeRenderNum = 0;
        return 0;
    }
    g_shapeRenderNum = count;
    return 1;
}

s32 shapeLoad(u16 index, void* file) {
    if (index >= g_shapeRenderNum) {
        return 0;
    }
    if (g_shapeRender[index] != 0) {
        GSmemFree(g_shapeRender[index]);
    }
    g_shapeRender[index] = (GsShapeRender*)GSmemAlloc(sizeof(GsShapeRender));
    if (g_shapeRender[index] == 0) {
        return 0;
    }
    g_shapeRender[index]->InitShapeRender();
    g_shapeRender[index]->LoadShapeRender(file);
    return 1;
}

void shapeUpdate(u16 index, f32 time, s16 id) {
    if (index < g_shapeRenderNum && g_shapeRender[index] != 0) {
        g_shapeRender[index]->Update(time, id);
    }
}

void shapeRender(u16 index, s16 id, GSgfxLayerID layer) {
    if (index < g_shapeRenderNum && g_shapeRender[index] != 0) {
        g_shapeRender[index]->Render(id, layer);
    }
}

void shapeRelease(u16 index) {
    if (index < g_shapeRenderNum && g_shapeRender[index] != 0) {
        g_shapeRender[index]->FreeShapeRender();
        GSmemFree(g_shapeRender[index]);
        g_shapeRender[index] = 0;
    }
}

s32 shapeGenerateIndex() {
    GsShapeRender* r;
    u16 i;
    for (i = 0; i < g_shapeRenderNum; i++) {
        r = g_shapeRender[i];
        if (r == 0) {
            return i;
        }
        if (r->anim == 0) {
            return i;
        }
    }
    return -1;
}

s16 shapeCreatePrimitiveInstance(u16 index) {
    if (index >= g_shapeRenderNum) {
        return -1;
    }
    if (g_shapeRender[index] == 0) {
        return -1;
    }
    return g_shapeRender[index]->CreateShapeRenderDrawBuffer();
}

void shapeFreePrimitiveInstance(u16 index, s16 id) {
    if (index < g_shapeRenderNum && g_shapeRender[index] != 0) {
        g_shapeRender[index]->FreeShapeRenderDrawBuffer(id);
    }
}

s32 shapeGetUsedMemorySize(u16 index) {
    if (index >= g_shapeRenderNum) {
        return 0;
    }
    if (g_shapeRender[index] == 0) {
        return 0;
    }
    return g_shapeRender[index]->GetUsedMemorySizeAll();
}

s32 shapeGetInstancedMemorySizeAll() {
    return g_instancedMemorySizeAll;
}

static inline void _shapeUpdateAll() {
    for (u16 i = 0; i < g_shapeRenderNum; i++) {
        if (g_shapeRender[i] != 0) {
            shapeUpdate(i, g_primitiveFrameSec, g_primitiveInstanceId);
        }
    }
}

void shapePrimitiveEditorRender(GSgfxLayerID layerId) {
    GSgfxLayer* layer;
    s32 usedMemory;
    s32 instancedMemory;
    Mtx m;
    f32 rate;
    f32 zero = 0.0f;
    f32 ten = 10.0f;

    if (g_primitiveEditorMode != 0) {
        if (layerId == getEditorLayer()) {
            switch (g_primitiveAnimation) {
            case 0:
                rate = GSgfxVideoGetVsyncRate();
                g_primitiveFrameSec += GSgfxVideoGetLastRenderTime() / rate;
                _shapeUpdateAll();
                break;
            case 1:
                _shapeUpdateAll();
                if (g_shapeRenderNum != 0) {
                    GsShapeRender* r = g_shapeRender[0];
                    if (r != 0 && r->anim != 0 && r->anim->fps >= 1) {
                        g_primitiveFrameSec += 1.0f / r->anim->fps;
                    }
                }
                g_primitiveAnimation = 2;
                break;
            case 2:
                break;
            }
            layer = GSgfxLayerFindByID(layerId);
            GScameraLoadActiveCameraMatrix(layerId);
            PSMTXRotRad(m, 'Y', -1.5707964f);
            PSMTXTransApply(m, m, 0.0f, 0.1f, 0.0f);
            (*(GSgfxMatrixStack**)&layer->matrixStack)->pushMult((GSmtx*)m);
            layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
            (*(s32*)&layer->hw.cullMode) = 0;
            (*(u32*)&layer->dirty[0].raster) |= 2;
            (*(u32*)&layer->dirty[0].groups) |= 2;
            (*(u32*)&layer->dirty[1].raster) |= 2;
            (*(u32*)&layer->dirty[1].groups) |= 2;
            (*(u32*)&layer->unk1998) = 0xA8;
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
            (*(u8*)&layer->hw.lineWidth) = 6;
            (*(s32*)&layer->hw.lineOffset) = 0;
            (*(u32*)&layer->dirty[0].geom) |= 4;
            (*(u32*)&layer->dirty[0].groups) |= 1;
            (*(u32*)&layer->dirty[1].geom) |= 4;
            (*(u32*)&layer->dirty[1].groups) |= 1;
            layer->beginSurface(6);
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.f32 = ten;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = ten;
            GXWGFifo.f32 = zero;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = ten;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            layer->endSurface();

            usedMemory = 0;
            instancedMemory = 0;
            for (u16 i = 0; i < g_shapeRenderNum; i++) {
                if (g_shapeRender[i] != 0) {
                    if (g_shapeRender[i]->loaded == 1 && g_shapeRender[i]->anim != 0) {
                        g_shapeRender[i]->anim->flag = 1;
                    }
                    shapeRender(i, g_primitiveInstanceId, layerId);
                    usedMemory += g_shapeRender[i]->GetUsedMemorySizeAll();
                    instancedMemory += g_shapeRender[i]->GetInstancedMemorySizeAll();
                }
            }
            GSprint(getEditorLayer(), 0x226, 0x1E, -1, "%dKB", instancedMemory / 1024);
            (*(GSgfxMatrixStack**)&layer->matrixStack)->pop();
        }
    }
}

}
