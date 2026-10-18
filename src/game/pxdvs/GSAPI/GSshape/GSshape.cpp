// Draft (written from asm). Needs -inline deferred (source is bottom-to-top).
#include <dolphin/types.h>
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

class GSgfxLayer {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

    u8 pad0[0xd34];
    u8 d34;
    u8 padd35[3];
    s32 d38;
    u8 padd3c[0xd8c - 0xd3c];
    s32 d8c;
    u8 padd90[0x1644 - 0xd90];
    s32 blendOp;
    s32 blendSrc;
    s32 blendDst;
    s32 blendLogic;
    u8 pad1654[0x16a8 - 0x1654];
    u32 dirty16a8;
    u32 dirty16ac;
    u8 pad16b0[8];
    u32 dirty16b8;
    u8 pad16bc[0x170c - 0x16bc];
    u32 dirty170c;
    u8 pad1710[0x1760 - 0x1710];
    u32 dirty1760;
    u32 dirty1764;
    u8 pad1768[8];
    u32 dirty1770;
    u8 pad1774[0x17c4 - 0x1774];
    u32 dirty17c4;
    u8 pad17c8[0x1818 - 0x17c8];
    u8 blendTable[2][0xbc];
    u8* curBlend;
    s32 curBlendIdx;
    u32 primType;
    s32 vf;
    GSgfxMatrixStack* matrixStack;
};

struct GsShapeAnimHeader {
    u8 unk0[4];
    u32 frameCount;
    u32 fps;
    u8 unkC[8];
    u8 flag;  // 0x14
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
    u8 pad1[0x13];
    GsShapeAnimHeader* anim;  // 0x14
    u8 pad18[0x964 - 0x18];
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
GSgfxLayer* GSgfxLayerFindByID(int id);
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

s32 shapeInit(u16 count) {
    u16 i;
    g_primitiveEditorMode = 0;
    for (i = 0; i < g_shapeRenderNum; i++) {
        if (g_shapeRender[i] != 0) {
            g_shapeRender[i]->FreeShapeRender();
            GSmemFree(g_shapeRender[i]);
            g_shapeRender[i] = 0;
        }
    }
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
    g_shapeRender = (GsShapeRender**)GSmemAllocClr(count * 4);
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
                for (u16 i = 0; i < g_shapeRenderNum; i++) {
                    if (g_shapeRender[i] != 0) {
                        shapeUpdate(i, g_primitiveFrameSec, g_primitiveInstanceId);
                    }
                }
                break;
            case 1:
                for (u16 i = 0; i < g_shapeRenderNum; i++) {
                    if (g_shapeRender[i] != 0) {
                        shapeUpdate(i, g_primitiveFrameSec, g_primitiveInstanceId);
                    }
                }
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
            layer->matrixStack->pushMult((GSmtx*)m);
            layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
            layer->d8c = 0;
            layer->dirty16b8 |= 2;
            layer->dirty16a8 |= 2;
            layer->dirty1770 |= 2;
            layer->dirty1760 |= 2;
            layer->primType = 0xA8;
            if (layer->curBlendIdx != 1) {
                layer->curBlendIdx = 1;
                layer->curBlend = layer->blendTable[layer->curBlendIdx];
            }
            layer->blendOp = 1;
            layer->blendSrc = 4;
            layer->blendDst = 5;
            layer->blendLogic = 5;
            layer->dirty170c |= 1;
            layer->dirty16a8 |= 0x40;
            layer->dirty17c4 |= 1;
            layer->dirty1760 |= 0x40;
            layer->d34 = 6;
            layer->d38 = 0;
            layer->dirty16ac |= 4;
            layer->dirty16a8 |= 1;
            layer->dirty1764 |= 4;
            layer->dirty1760 |= 1;
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
            layer->matrixStack->pop();
        }
    }
}

}
