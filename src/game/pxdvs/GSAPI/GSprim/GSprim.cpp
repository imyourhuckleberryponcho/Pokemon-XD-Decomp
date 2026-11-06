#include <dolphin/types.h>
#include <game/gcptr.h>

struct BlendState {
    u8 pad[0xbc];
};

struct GSmtx44 {
    f32 m[4][4];
};

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};

struct PrimData {
    GSgfxLayer* layer;
    s32 f4;
    f32 lineWidth;
    s32 fc;
    s32 quadOrder;
    s32 quadVtx;
};

extern "C" GSmtx44 mtxIdent;
extern "C" {
PrimData primData;
void* memcpy(void*, const void*, u32);
s32 GSgfxLayerGetActive(void);
GSgfxLayer* GSgfxLayerFindByID(GCsptr id);
void GSgfxLayerSetActive(s32 id);
void GScameraLoadActiveCameraMatrix(s32 id);
void GSmtx44Ortho(f32* mtx, f32, f32, f32, f32, f32, f32);
void GSprimSetTextSize(f32, f32);
void GSprimSetTextWidth(f32);
void GSprimSetBlendMode(s32);

void GSprimSetQuadVertexOrder(s32 order) {
    primData.quadOrder = order;
    switch (order) {
    case 0:
        primData.quadVtx = 0x98;
        break;
    case 1:
        primData.quadVtx = 0x80;
        break;
    }
}

void GSprimSetLineWidth(f32 w) {
    primData.lineWidth = w;
    primData.f4 = 0;
}

void GSprimSetBlendMode(s32 mode) {
    switch (mode) {
    case 0: {
        GSgfxLayer* l = primData.layer;
        if ((*(s32*)&l->curPass) != 0) {
            (*(s32*)&l->curPass) = 0;
            l->curFifo = &l->passes[l->curPass];
        }
        (*(s32*)&l->hw.blend[0]) = 0;
        (*(s32*)&l->hw.blend[1]) = 1;
        (*(s32*)&l->hw.blend[2]) = 1;
        (*(s32*)&l->hw.blend[3]) = 5;
        (*(u32*)&l->dirty[0].pe) |= 1;
        (*(u32*)&l->dirty[0].groups) |= 0x40;
        (*(u32*)&l->dirty[1].pe) |= 1;
        (*(u32*)&l->dirty[1].groups) |= 0x40;
        break;
    }
    case 1: {
        GSgfxLayer* l = primData.layer;
        if ((*(s32*)&l->curPass) != 1) {
            (*(s32*)&l->curPass) = 1;
            l->curFifo = &l->passes[l->curPass];
        }
        (*(s32*)&l->hw.blend[0]) = 1;
        (*(s32*)&l->hw.blend[1]) = 4;
        (*(s32*)&l->hw.blend[2]) = 5;
        (*(s32*)&l->hw.blend[3]) = 5;
        (*(u32*)&l->dirty[0].pe) |= 1;
        (*(u32*)&l->dirty[0].groups) |= 0x40;
        (*(u32*)&l->dirty[1].pe) |= 1;
        (*(u32*)&l->dirty[1].groups) |= 0x40;
        break;
    }
    case 2: {
        GSgfxLayer* l = primData.layer;
        if ((*(s32*)&l->curPass) != 1) {
            (*(s32*)&l->curPass) = 1;
            l->curFifo = &l->passes[l->curPass];
        }
        (*(s32*)&l->hw.blend[0]) = 1;
        (*(s32*)&l->hw.blend[1]) = 1;
        (*(s32*)&l->hw.blend[2]) = 1;
        (*(s32*)&l->hw.blend[3]) = 5;
        (*(u32*)&l->dirty[0].pe) |= 1;
        (*(u32*)&l->dirty[0].groups) |= 0x40;
        (*(u32*)&l->dirty[1].pe) |= 1;
        (*(u32*)&l->dirty[1].groups) |= 0x40;
        break;
    }
    case 3: {
        GSgfxLayer* l = primData.layer;
        if ((*(s32*)&l->curPass) != 1) {
            (*(s32*)&l->curPass) = 1;
            l->curFifo = &l->passes[l->curPass];
        }
        (*(s32*)&l->hw.blend[0]) = 3;
        (*(s32*)&l->hw.blend[1]) = 1;
        (*(s32*)&l->hw.blend[2]) = 1;
        (*(s32*)&l->hw.blend[3]) = 5;
        (*(u32*)&l->dirty[0].pe) |= 1;
        (*(u32*)&l->dirty[0].groups) |= 0x40;
        (*(u32*)&l->dirty[1].pe) |= 1;
        (*(u32*)&l->dirty[1].groups) |= 0x40;
        break;
    }
    }
}

}

static inline void primSetDepthTest(u8 a, u8 b, u8 c) {
    GSgfxLayer* l = primData.layer;
    (*(u8*)&l->hw.colorUpdate) = a;
    (*(u8*)&l->hw.alphaUpdate) = b;
    (*(u8*)&l->hw.zUpdate) = c;
    (*(u32*)&l->dirty[0].pe) |= 4;
    (*(u32*)&l->dirty[0].groups) |= 0x40;
    (*(u32*)&l->dirty[1].pe) |= 4;
    (*(u32*)&l->dirty[1].groups) |= 0x40;
}

static inline void primSetZ(u8 enable, s32 func) {
    GSgfxLayer* l = primData.layer;
    (*(u8*)&l->hw.zEnable) = enable;
    (*(s32*)&l->hw.zFunc) = func;
    (*(u32*)&l->dirty[0].pe) |= 8;
    (*(u32*)&l->dirty[0].groups) |= 0x40;
    (*(u32*)&l->dirty[1].pe) |= 8;
    (*(u32*)&l->dirty[1].groups) |= 0x40;
}

static inline void primSetAlphaCompare(s32 a, u8 b, s32 c, s32 d, u8 e, u8 f) {
    GSgfxLayer* l = primData.layer;
    (*(s32*)&l->hw.alphaComp0) = a;
    (*(u8*)&l->hw.alphaRef0) = b;
    (*(s32*)&l->hw.alphaCmpOp) = c;
    (*(s32*)&l->hw.alphaComp1) = d;
    (*(u8*)&l->hw.alphaRef1) = e;
    (*(u8*)&l->hw.zCompLoc) = f;
    (*(u32*)&l->dirty[0].pe) |= 0x10;
    (*(u32*)&l->dirty[0].groups) |= 0x40;
    (*(u32*)&l->dirty[1].pe) |= 0x10;
    (*(u32*)&l->dirty[1].groups) |= 0x40;
}

static inline void primSetMisc() {
    GSgfxLayer* l = primData.layer;
    (*(s32*)&l->hw.cullMode) = 0;
    (*(u32*)&l->dirty[0].raster) |= 2;
    (*(u32*)&l->dirty[0].groups) |= 2;
    (*(u32*)&l->dirty[1].raster) |= 2;
    (*(u32*)&l->dirty[1].groups) |= 2;
}

void GSprimSetRenderLayer(GSgfxLayer* layer) {
    if (layer == 0) {
        layer = GSgfxLayerFindByID(GSgfxLayerGetActive());
    }
    primData.layer = layer;
}

void GSprimSetup3DRender(GSgfxLayer* layer) {
    if (layer == 0) {
        layer = GSgfxLayerFindByID(GSgfxLayerGetActive());
    }
    primData.layer = layer;
    GSgfxLayerSetActive((*(s32*)&primData.layer->id));
    GScameraLoadActiveCameraMatrix((*(s32*)&primData.layer->id));
    primSetDepthTest(1, 1, 1);
    primSetZ(1, 3);
    primSetAlphaCompare(7, 0, 0, 7, 0, 1);
    primSetMisc();
    GSprimSetBlendMode(0);
    GSprimSetQuadVertexOrder(0);
    GSprimSetLineWidth(1.0f);
    GSprimSetTextSize(10.0f, 10.0f);
    GSprimSetTextWidth(1.0f);
}

void GSprimSetup2DRender(GSgfxLayer* layer) {
    f32 mtx[16];
    GSgfxLayer* l = layer;
    if (layer == 0) {
        l = GSgfxLayerFindByID(GSgfxLayerGetActive());
    }
    layer = l;
    primData.layer = layer;
    GSmtx44Ortho(mtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    (*(s32*)&layer->hw.projType) = 1;
    ((f32*)layer->hw.proj)[0] = mtx[0];
    ((f32*)layer->hw.proj)[1] = mtx[3];
    ((f32*)layer->hw.proj)[2] = mtx[5];
    ((f32*)layer->hw.proj)[3] = mtx[7];
    ((f32*)layer->hw.proj)[4] = mtx[10];
    ((f32*)layer->hw.proj)[5] = mtx[11];
    GSlayerCam* cam = (*(GSlayerCam**)&layer->matrixStack);
    memcpy(cam->data + 1, &mtxIdent, 0x30);
    cam->data[0] |= 1;
    (*(f32*)&layer->hw.fogNear) = 0.0f;
    (*(f32*)&layer->hw.fogFar) = 30000.0f;
    if ((*(u8*)&layer->hw.fogEnable)) {
        if ((*(u8*)&layer->hw.fogRangeEnable)) {
            (*(u32*)&layer->dirty[0].pe) |= 0x100;
            (*(u32*)&layer->dirty[1].pe) |= 0x100;
        }
        (*(u32*)&layer->dirty[0].pe) |= 0x40;
        (*(u32*)&layer->dirty[0].groups) |= 0x40;
        (*(u32*)&layer->dirty[1].pe) |= 0x40;
        (*(u32*)&layer->dirty[1].groups) |= 0x40;
    }
    (*(u32*)&layer->dirty[0].geom) |= 0x20;
    (*(u32*)&layer->dirty[0].groups) |= 1;
    (*(u32*)&layer->dirty[1].geom) |= 0x20;
    (*(u32*)&layer->dirty[1].groups) |= 1;
    primSetDepthTest(1, 0, 0);
    primSetZ(0, 3);
    primSetAlphaCompare(7, 0, 0, 7, 0, 1);
    primSetMisc();
    GSprimSetBlendMode(0);
    GSprimSetQuadVertexOrder(0);
    GSprimSetLineWidth(1.0f);
    GSprimSetTextSize(10.0f, 10.0f);
    GSprimSetTextWidth(1.0f);
}
