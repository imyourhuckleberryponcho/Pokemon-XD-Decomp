#include <dolphin/types.h>

struct BlendState {
    u8 pad[0xbc];
};

struct GSmtx44 {
    f32 m[4][4];
};

class GSgfxLayer {
public:
    u8 pad0[0x28];
    s32 id;
    u8 pad2c[0xd54 - 0x2c];
    s32 projType;
    f32 proj[6];
    u8 pad_d70[0xd8c - 0xd70];
    s32 d8c;
    u8 pad_d90[0x1644 - 0xd90];
    s32 blendOp;
    s32 blendSrc;
    s32 blendDst;
    s32 blendLogic;
    u8 pad_1654[2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 zUpdate;
    u8 pad_1659[3];
    u8 zEnable;
    u8 pad_165d[3];
    s32 zFunc;
    s32 f1664;
    s32 f1668;
    s32 f166c;
    u8 f1670;
    u8 f1671;
    u8 f1672;
    u8 pad_1673[0x1684 - 0x1673];
    f32 nearZ;
    f32 farZ;
    u8 pad_168c[0x16a6 - 0x168c];
    u8 f16a6;
    u8 f16a7;
    u32 dirty16a8;
    u32 dirty16ac;
    u8 pad_16b0[8];
    u32 dirty16b8;
    u8 pad_16bc[0x170c - 0x16bc];
    u32 dirty170c;
    u8 pad_1710[0x1760 - 0x1710];
    u32 dirty1760;
    u32 dirty1764;
    u8 pad_1768[8];
    u32 dirty1770;
    u8 pad_1774[0x17c4 - 0x1774];
    u32 dirty17c4;
    u8 pad_17c8[0x1818 - 0x17c8];
    BlendState blendTable[2];
    BlendState* curBlend;
    s32 curBlendIdx;
    u8 pad_1998[0x19a0 - 0x1998];
    struct GSlayerCam* cam;
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

extern GSmtx44 mtxIdent;
extern "C" {
PrimData primData;
void* memcpy(void*, const void*, u32);
s32 GSgfxLayerGetActive(void);
GSgfxLayer* GSgfxLayerFindByID(s32 id);
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
        if (l->curBlendIdx != 0) {
            l->curBlendIdx = 0;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 0;
        l->blendSrc = 1;
        l->blendDst = 1;
        l->blendLogic = 5;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 1: {
        GSgfxLayer* l = primData.layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 1;
        l->blendSrc = 4;
        l->blendDst = 5;
        l->blendLogic = 5;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 2: {
        GSgfxLayer* l = primData.layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 1;
        l->blendSrc = 1;
        l->blendDst = 1;
        l->blendLogic = 5;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    case 3: {
        GSgfxLayer* l = primData.layer;
        if (l->curBlendIdx != 1) {
            l->curBlendIdx = 1;
            l->curBlend = &l->blendTable[l->curBlendIdx];
        }
        l->blendOp = 3;
        l->blendSrc = 1;
        l->blendDst = 1;
        l->blendLogic = 5;
        l->dirty170c |= 1;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 1;
        l->dirty1760 |= 0x40;
        break;
    }
    }
}

}

static inline void primSetDepthTest(u8 a, u8 b, u8 c) {
    GSgfxLayer* l = primData.layer;
    l->colorUpdate = a;
    l->alphaUpdate = b;
    l->zUpdate = c;
    l->dirty170c |= 4;
    l->dirty16a8 |= 0x40;
    l->dirty17c4 |= 4;
    l->dirty1760 |= 0x40;
}

static inline void primSetZ(u8 enable, s32 func) {
    GSgfxLayer* l = primData.layer;
    l->zEnable = enable;
    l->zFunc = func;
    l->dirty170c |= 8;
    l->dirty16a8 |= 0x40;
    l->dirty17c4 |= 8;
    l->dirty1760 |= 0x40;
}

static inline void primSetAlphaCompare(s32 a, u8 b, s32 c, s32 d, u8 e, u8 f) {
    GSgfxLayer* l = primData.layer;
    l->f1664 = a;
    l->f1670 = b;
    l->f1668 = c;
    l->f166c = d;
    l->f1671 = e;
    l->f1672 = f;
    l->dirty170c |= 0x10;
    l->dirty16a8 |= 0x40;
    l->dirty17c4 |= 0x10;
    l->dirty1760 |= 0x40;
}

static inline void primSetMisc() {
    GSgfxLayer* l = primData.layer;
    l->d8c = 0;
    l->dirty16b8 |= 2;
    l->dirty16a8 |= 2;
    l->dirty1770 |= 2;
    l->dirty1760 |= 2;
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
    GSgfxLayerSetActive(primData.layer->id);
    GScameraLoadActiveCameraMatrix(primData.layer->id);
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
    layer->projType = 1;
    layer->proj[0] = mtx[0];
    layer->proj[1] = mtx[3];
    layer->proj[2] = mtx[5];
    layer->proj[3] = mtx[7];
    layer->proj[4] = mtx[10];
    layer->proj[5] = mtx[11];
    GSlayerCam* cam = layer->cam;
    memcpy(cam->data + 1, &mtxIdent, 0x30);
    cam->data[0] |= 1;
    layer->nearZ = 0.0f;
    layer->farZ = 30000.0f;
    if (layer->f16a7) {
        if (layer->f16a6) {
            layer->dirty170c |= 0x100;
            layer->dirty17c4 |= 0x100;
        }
        layer->dirty170c |= 0x40;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 0x40;
        layer->dirty1760 |= 0x40;
    }
    layer->dirty16ac |= 0x20;
    layer->dirty16a8 |= 1;
    layer->dirty1764 |= 0x20;
    layer->dirty1760 |= 1;
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
