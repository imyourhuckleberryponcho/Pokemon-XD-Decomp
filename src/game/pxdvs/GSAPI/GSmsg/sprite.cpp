#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gcdata.h>
#include <dolphin/mtx.h>

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
};

struct SpriteWork {
    f32 offX;
    f32 offY;
    f32 scaleX;
    f32 scaleY;
};

extern "C" {
GSgfxLayer* GSgfxLayerFindByID(GCsptr id);
void GSgfxVideoGetEFBSize(u16* w, u16* h);
void GSmtx44Perspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f);
s32 floorGetMenuLayerID(void);
void* memcpy(void* dst, const void* src, u32 n);
double tan(double x);
extern GSgfxLayer* _TargetLayer;
extern Mtx mtxIdent;
}

static SpriteWork _spriteWork[3] = {
    {0.0f, 0.0f, 1.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
};

#pragma peephole off

extern "C" {

void spriteClearScissor(s32 layer) {
    GSgfxLayer* l = GSgfxLayerFindByID(layer);
    _TargetLayer = l;
    if (l != 0) {
        (*(u16*)&l->hw.scissor[0]) = 0;
        (*(u16*)&l->hw.scissor[1]) = 0;
        GSgfxVideoGetEFBSize(&(*(u16*)&l->hw.scissor[2]), &(*(u16*)&l->hw.scissor[3]));
        (*(u32*)&l->dirty[0].raster) |= 1;
        (*(u32*)&l->dirty[0].groups) |= 2;
        (*(u32*)&l->dirty[1].raster) |= 1;
        (*(u32*)&l->dirty[1].groups) |= 2;
    }
}

#pragma push
#pragma opt_lifetimes off
void spriteSetScissor(s32 layer, s32 x, s32 y, s32 w, s32 h) {
    s16 idx;
    if (layer == floorGetMenuLayerID()) {
        idx = 0;
    } else if (layer == 7) {
        idx = 1;
    } else {
        idx = 2;
    }
    SpriteWork* work = &_spriteWork[idx];
    GSgfxLayer* l = GSgfxLayerFindByID(layer);
    _TargetLayer = l;
    if (l != 0) {
        x = work->offX + (f32)x;
        y = work->offY + (f32)y;
        f32 scaleX = work->scaleX;
        f32 scaleY = work->scaleY;
        x = (f32)x * scaleX;
        y = (f32)y * scaleY;
        w = (f32)w * scaleX;
        h = (f32)h * scaleY;
        if (x >= 640) {
            x = 640;
        }
        if (y >= 480) {
            y = 480;
        }
        if (w >= 640) {
            w = 640;
        }
        if (h >= 480) {
            h = 480;
        }
        if (x < 0) {
            x = 0;
        }
        if (y < 0) {
            y = 0;
        }
        if (w < 0) {
            w = 0;
        }
        if (h < 0) {
            h = 0;
        }
        (*(u16*)&l->hw.scissor[0]) = x;
        (*(u16*)&l->hw.scissor[1]) = y;
        (*(u16*)&l->hw.scissor[2]) = w;
        (*(u16*)&l->hw.scissor[3]) = h;
        (*(u32*)&l->dirty[0].raster) |= 1;
        (*(u32*)&l->dirty[0].groups) |= 2;
        (*(u32*)&l->dirty[1].raster) |= 1;
        (*(u32*)&l->dirty[1].groups) |= 2;
    }
}
#pragma pop

void spriteClearEnv(s32 layer) {
    GSgfxLayer* l = GSgfxLayerFindByID(layer);
    _TargetLayer = l;
    if (l != 0) {
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
    }
}

void spriteSetEnv(s32 layer) {
    s16 idx;
    if (layer == floorGetMenuLayerID()) {
        idx = 0;
    } else if (layer == 7) {
        idx = 1;
    } else {
        idx = 2;
    }
    SpriteWork* work = &_spriteWork[idx];
    GSgfxLayer* l = GSgfxLayerFindByID(layer);
    _TargetLayer = l;
    if (l != 0) {
        Mtx view;
        Mtx44 proj;
        Vec eye;
        Vec at;
        Vec up;
        f32 cx;
        f32 cy;
        f32 width = 640.0f / work->scaleX;
        f32 height = 480.0f / work->scaleY;
        f32 kc520 = 0.5f;
        cx = width * kc520;
        f32 kc544 = 0.5f;
        cy = height * kc544;
        f32 fov = 0.2617994f;
        f32 dist = cy / (f32)tan(fov);
        eye.y = cy - work->offY;
        eye.z = dist;
        eye.x = cx - work->offX;
        at.x = cx - work->offX;
        at.y = cy - work->offY;
        at.z = 0.0f;
        up.x = 0.0f;
        up.y = -1.0f;
        up.z = 0.0f;
        C_MTXLookAt(view, &eye, &up, &at);
        l = _TargetLayer;
        GSmtx44Perspective(proj, 30.0f, -(width / height), 0.1f, 30000.0f);

        (*(s32*)&l->hw.projType) = 0;
        ((f32*)l->hw.proj)[0] = proj[0][0];
        ((f32*)l->hw.proj)[1] = proj[0][2];
        ((f32*)l->hw.proj)[2] = proj[1][1];
        ((f32*)l->hw.proj)[3] = proj[1][2];
        ((f32*)l->hw.proj)[4] = proj[2][2];
        ((f32*)l->hw.proj)[5] = proj[2][3];
        (*(f32*)&l->hw.fogNear) = 0.1f;
        (*(f32*)&l->hw.fogFar) = 30000.0f;
        if ((*(u8*)&l->hw.fogEnable) != 0) {
            if ((*(u8*)&l->hw.fogRangeEnable) != 0) {
                (*(u32*)&l->dirty[0].pe) |= 0x100;
                (*(u32*)&l->dirty[1].pe) |= 0x100;
            }
            (*(u32*)&l->dirty[0].pe) |= 0x40;
            (*(u32*)&l->dirty[0].groups) |= 0x40;
            (*(u32*)&l->dirty[1].pe) |= 0x40;
            (*(u32*)&l->dirty[1].groups) |= 0x40;
        }
        (*(u32*)&l->dirty[0].geom) |= 0x20;
        (*(u32*)&l->dirty[0].groups) |= 1;
        (*(u32*)&l->dirty[1].geom) |= 0x20;
        (*(u32*)&l->dirty[1].groups) |= 1;

        GSlayerCam* cam = (*(GSlayerCam**)&_TargetLayer->matrixStack);
        memcpy(cam->data + 1, mtxIdent, sizeof(Mtx));
        cam->data[0] |= 1;
        cam = (*(GSlayerCam**)&_TargetLayer->matrixStack);
        PSMTXConcat((MtxPtr)(cam->data + 1), view, (MtxPtr)(cam->data + 1));
        cam->data[0] |= 1;

        l = _TargetLayer;
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

        l = _TargetLayer;
        (*(u8*)&l->hw.colorUpdate) = 1;
        (*(u8*)&l->hw.alphaUpdate) = 0;
        (*(u8*)&l->hw.zUpdate) = 1;
        (*(u32*)&l->dirty[0].pe) |= 4;
        (*(u32*)&l->dirty[0].groups) |= 0x40;
        (*(u32*)&l->dirty[1].pe) |= 4;
        (*(u32*)&l->dirty[1].groups) |= 0x40;

        l = _TargetLayer;
        (*(s32*)&l->hw.alphaComp0) = 7;
        (*(u8*)&l->hw.alphaRef0) = 0;
        (*(s32*)&l->hw.alphaCmpOp) = 0;
        (*(s32*)&l->hw.alphaComp1) = 7;
        (*(u8*)&l->hw.alphaRef1) = 0;
        (*(u8*)&l->hw.zCompLoc) = 1;
        (*(u32*)&l->dirty[0].pe) |= 0x10;
        (*(u32*)&l->dirty[0].groups) |= 0x40;
        (*(u32*)&l->dirty[1].pe) |= 0x10;
        (*(u32*)&l->dirty[1].groups) |= 0x40;

        l = _TargetLayer;
        (*(u8*)&l->hw.zEnable) = 0;
        (*(s32*)&l->hw.zFunc) = 3;
        (*(u32*)&l->dirty[0].pe) |= 8;
        (*(u32*)&l->dirty[0].groups) |= 0x40;
        (*(u32*)&l->dirty[1].pe) |= 8;
        (*(u32*)&l->dirty[1].groups) |= 0x40;

        l = _TargetLayer;
        (*(s32*)&l->hw.cullMode) = 0;
        (*(u32*)&l->dirty[0].raster) |= 2;
        (*(u32*)&l->dirty[0].groups) |= 2;
        (*(u32*)&l->dirty[1].raster) |= 2;
        (*(u32*)&l->dirty[1].groups) |= 2;
    }
}

void spriteGetOffset(s32 layer, s16* x, s16* y) {
    s16 idx;
    if (layer == floorGetMenuLayerID()) {
        idx = 0;
    } else if (layer == 7) {
        idx = 1;
    } else {
        idx = 2;
    }
    SpriteWork* work = &_spriteWork[idx];
    if (x != 0) {
        *x = work->offX;
    }
    if (y != 0) {
        *y = work->offY;
    }
}

void spriteSetOffset(s32 layer, s16 x, s16 y) {
    s16 idx;
    if (layer == floorGetMenuLayerID()) {
        idx = 0;
    } else if (layer == 7) {
        idx = 1;
    } else {
        idx = 2;
    }
    SpriteWork* work = &_spriteWork[idx];
    work->offX = x;
    work->offY = y;
}

}
