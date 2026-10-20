// 2D sprite environment for a graphics layer: per-layer offset/scale, scissor box and the orthographic-looking
// perspective camera used to draw menu sprites.
#include <dolphin/types.h>
#include <dolphin/mtx.h>

struct BlendState {
    u8 pad[0xbc];
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};

class GSgfxLayer {
public:
    u8 pad0[0xd54];
    s32 projType;
    f32 proj[6];
    u16 scissorX;
    u16 scissorY;
    u16 scissorW;
    u16 scissorH;
    u8 pad_d78[0xd8c - 0xd78];
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
    GSlayerCam* cam;
};

struct SpriteWork {
    f32 offX;
    f32 offY;
    f32 scaleX;
    f32 scaleY;
};

extern "C" {
GSgfxLayer* GSgfxLayerFindByID(s32 id);
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
        l->scissorX = 0;
        l->scissorY = 0;
        GSgfxVideoGetEFBSize(&l->scissorW, &l->scissorH);
        l->dirty16b8 |= 1;
        l->dirty16a8 |= 2;
        l->dirty1770 |= 1;
        l->dirty1760 |= 2;
    }
}

void spriteSetScissor(s32 layer, s32 x, s32 y, s32 w, s32 h) {
    enum TsE { TsE0 };
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
        s32 sx = work->offX + (f32)x;
        enum TsE sy = (enum TsE)(work->offY + (f32)y);
        f32 scaleX = work->scaleX;
        f32 scaleY = work->scaleY;
        sx = (f32)sx * scaleX;
        sy = (enum TsE)((f32)sy * scaleY);
        w = (f32)w * scaleX;
        h = (f32)h * scaleY;
        if (sx >= 640) {
            sx = 640;
        }
        if (sy >= 480) {
            sy = (enum TsE)(480);
        }
        if (w >= 640) {
            w = 640;
        }
        if (h >= 480) {
            h = 480;
        }
        if (sx < 0) {
            sx = 0;
        }
        if (sy < 0) {
            sy = (enum TsE)(0);
        }
        if (w < 0) {
            w = 0;
        }
        if (h < 0) {
            h = 0;
        }
        l->scissorX = sx;
        l->scissorY = sy;
        l->scissorW = w;
        l->scissorH = h;
        l->dirty16b8 |= 1;
        l->dirty16a8 |= 2;
        l->dirty1770 |= 1;
        l->dirty1760 |= 2;
    }
}

void spriteClearEnv(s32 layer) {
    GSgfxLayer* l = GSgfxLayerFindByID(layer);
    _TargetLayer = l;
    if (l != 0) {
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
        up.z = 0.0f;
        up.x = 0.0f;
        at.y = cy - work->offY;
        eye.x = cx - work->offX;
        eye.y = cy - work->offY;
        eye.z = dist;
        up.y = -1.0f;
        at.z = 0.0f;
        at.x = cx - work->offX;
        C_MTXLookAt(view, &eye, &up, &at);
        GSmtx44Perspective(proj, 30.0f, -(width / height), 0.1f, 30000.0f);

        l = _TargetLayer;
        l->projType = 0;
        l->proj[0] = proj[0][0];
        l->proj[1] = proj[0][2];
        l->proj[2] = proj[1][1];
        l->proj[3] = proj[1][2];
        l->proj[4] = proj[2][2];
        l->proj[5] = proj[2][3];
        l->nearZ = 0.1f;
        l->farZ = 30000.0f;
        if (l->f16a7 != 0) {
            if (l->f16a6 != 0) {
                l->dirty170c |= 0x100;
                l->dirty17c4 |= 0x100;
            }
            l->dirty170c |= 0x40;
            l->dirty16a8 |= 0x40;
            l->dirty17c4 |= 0x40;
            l->dirty1760 |= 0x40;
        }
        l->dirty16ac |= 0x20;
        l->dirty16a8 |= 1;
        l->dirty1764 |= 0x20;
        l->dirty1760 |= 1;

        GSlayerCam* cam = _TargetLayer->cam;
        memcpy(cam->data + 1, mtxIdent, sizeof(Mtx));
        cam->data[0] |= 1;
        cam = _TargetLayer->cam;
        PSMTXConcat((MtxPtr)(cam->data + 1), view, (MtxPtr)(cam->data + 1));
        cam->data[0] |= 1;

        l = _TargetLayer;
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

        l = _TargetLayer;
        l->colorUpdate = 1;
        l->alphaUpdate = 0;
        l->zUpdate = 1;
        l->dirty170c |= 4;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 4;
        l->dirty1760 |= 0x40;

        l = _TargetLayer;
        l->f1664 = 7;
        l->f1670 = 0;
        l->f1668 = 0;
        l->f166c = 7;
        l->f1671 = 0;
        l->f1672 = 1;
        l->dirty170c |= 0x10;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 0x10;
        l->dirty1760 |= 0x40;

        l = _TargetLayer;
        l->zEnable = 0;
        l->zFunc = 3;
        l->dirty170c |= 8;
        l->dirty16a8 |= 0x40;
        l->dirty17c4 |= 8;
        l->dirty1760 |= 0x40;

        l = _TargetLayer;
        l->d8c = 0;
        l->dirty16b8 |= 2;
        l->dirty16a8 |= 2;
        l->dirty1770 |= 2;
        l->dirty1760 |= 2;
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
