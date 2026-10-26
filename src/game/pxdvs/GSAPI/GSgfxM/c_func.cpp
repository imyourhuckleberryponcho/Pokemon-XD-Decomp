#include <dolphin/types.h>

typedef f32 Mtx[3][4];

struct GSgfxDL;
struct GSgfxVF;
struct GScamera;

struct GStexture {
    u8 unk0[7];
    u8 reload;
};

struct GSgfxTevOp {
    u32 op;
    u32 bias;
    u32 scale;
    u8 clamp;
    u32 reg;
};

struct GSgfxDirty {
    u32 groups;
    u32 words[36];
    u32 textureMask;
    GStexture* textures[8];
};

struct GSgfxBlendSet {
    u8 unk0[0xBC];
};

struct GSgfxMtxEntry {
    u32 flags;
    Mtx mtx;
    Mtx invXpose;
};

struct GSgfxMtxStack {
    u32 unk0;
    GSgfxMtxEntry* top;
};

class GSgfxLayer {
public:
    void tokenMark();
    void dlDraw(GSgfxDL* dl);
    void setRenderStateAndSelect(GSgfxVF* vf);
    void endSurface();
    void beginSurface(unsigned short num);

    u8 unk0[0xD34];
    u8 lineWidth;
    u8 unkD35[0x3];
    u32 lineTexOffsets;
    u8 unkD3C[0x50];
    u32 cullMode;
    u8 unkD90[0x1E0];
    u32 colorArgs[16][4];
    u32 alphaArgs[16][4];
    GSgfxTevOp colorOps[16];
    GSgfxTevOp alphaOps[16];
    u8 unk13F0[0x254];
    u32 blendType;
    u32 blendSrc;
    u32 blendDst;
    u32 blendLogicOp;
    u8 unk1654[0x2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 dither;
    u8 unk1659[0x3];
    u8 zEnable;
    u8 unk165D[0x3];
    u32 zFunc;
    u32 alphaComp0;
    u32 alphaOp;
    u32 alphaComp1;
    u8 alphaRef0;
    u8 alphaRef1;
    u8 alphaCompareOff;
    u8 unk1673[0x35];
    GSgfxDirty dirty[2];
    GSgfxBlendSet blendSets[2];
    GSgfxBlendSet* blendSet;
    s32 blendIndex;
    u32 primType;
    u8 unk199C[0x4];
    GSgfxMtxStack* mtxStack;
    u8 unk19A4[4];
};

struct GSgfxState {
    u8 unk0[0xC40];
    GSgfxLayer* layer;
};

#define GFX_DIRTY(l, word, bits, group) \
    (l)->dirty[0].words[word] |= (bits); \
    (l)->dirty[0].groups |= (group);     \
    (l)->dirty[1].words[word] |= (bits); \
    (l)->dirty[1].groups |= (group);

#define GX_WGPIPE (*(volatile union { u8 u8; s16 s16; f32 f32; }*)0xCC008000)

extern "C" {

extern GSgfxState* gsgfxState;

void PSMTXInvXpose(const Mtx src, Mtx dst);
GScamera* GScameraGetActiveCamera(void);
Mtx* GScameraGetMatrixPtr(GScamera* camera);
Mtx* GScameraGetInvMatrixPtr(GScamera* camera);
Mtx* GScameraGetProjMatrixPtr(GScamera* camera);

Mtx* GSgfxMatrixGetPtr(int which) {
    GScamera* camera;
    switch (which) {
    case 0:
        return &gsgfxState->layer->mtxStack->top->mtx;
    case 1: {
        GSgfxMtxStack* stack = gsgfxState->layer->mtxStack;
        GSgfxMtxEntry* top = stack->top;
        if (top->flags & 1) {
            PSMTXInvXpose(top->mtx, top->invXpose);
            stack->top->flags &= ~1;
        }
        return &stack->top->invXpose;
    }
    }
    camera = GScameraGetActiveCamera();
    if (camera == NULL) {
        return NULL;
    }
    switch (which) {
    case 2:
        return GScameraGetMatrixPtr(camera);
    case 3:
        return GScameraGetInvMatrixPtr(camera);
    case 4:
        return GScameraGetProjMatrixPtr(camera);
    }
    return NULL;
}

void GSgfxTokenMark(void) {
    gsgfxState->layer->tokenMark();
}

void GSgfxDLDraw(GSgfxDL* dl) {
    gsgfxState->layer->dlDraw(dl);
}

void GSgfxSetupRenderAndSelect(GSgfxVF* vf) {
    gsgfxState->layer->setRenderStateAndSelect(vf);
}

void GSgfxSetTUnitUserAlphaArg(u8 unit, u32 a, u32 b, u32 c, u32 d) {
    GSgfxLayer* l = gsgfxState->layer;
    u32 bit = 1 << (u32)unit;
    l->alphaArgs[unit][0] = a;
    l->alphaArgs[unit][1] = b;
    l->alphaArgs[unit][2] = c;
    l->alphaArgs[unit][3] = d;
    GFX_DIRTY(l, 11, bit, 8)
}

void GSgfxSetTUnitUserAlphaOp(u8 unit, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
    GSgfxLayer* l = gsgfxState->layer;
    l->alphaOps[unit].op = op;
    l->alphaOps[unit].bias = bias;
    l->alphaOps[unit].scale = scale;
    l->alphaOps[unit].clamp = clamp != 0;
    l->alphaOps[unit].reg = reg;
    GFX_DIRTY(l, 13, 1 << unit, 8)
}

void GSgfxSetTUnitUserColorArg(u8 unit, u32 a, u32 b, u32 c, u32 d) {
    GSgfxLayer* l = gsgfxState->layer;
    u32 bit = 1 << (u32)unit;
    l->colorArgs[unit][0] = a;
    l->colorArgs[unit][1] = b;
    l->colorArgs[unit][2] = c;
    l->colorArgs[unit][3] = d;
    GFX_DIRTY(l, 10, bit, 8)
}

void GSgfxSetTUnitUserColorOp(u8 unit, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
    GSgfxLayer* l = gsgfxState->layer;
    l->colorOps[unit].op = op;
    l->colorOps[unit].bias = bias;
    l->colorOps[unit].scale = scale;
    l->colorOps[unit].clamp = clamp != 0;
    l->colorOps[unit].reg = reg;
    GFX_DIRTY(l, 12, 1 << unit, 8)
}

void GSgfxSelectTexture(u8 map, GStexture* texture) {
    GSgfxLayer* l = gsgfxState->layer;
    if (l->dirty[0].textures[map] == texture && l->dirty[1].textures[map] == texture && !texture->reload) {
        return;
    }
    l->dirty[0].textures[map] = texture;
    l->dirty[0].textureMask |= 1 << map;
    l->dirty[1].textures[map] = texture;
    l->dirty[1].textureMask |= 1 << map;
}

void GSgfxCullMode(u32 mode) {
    GSgfxLayer* l = gsgfxState->layer;
    l->cullMode = mode;
    GFX_DIRTY(l, 3, 2, 2)
}

void GSgfxAlphaCompare(u8 enable, u32 comp0, u8 ref0, u32 op, u32 comp1, u8 ref1) {
    GSgfxLayer* l = gsgfxState->layer;
    if (enable == 1) {
        l->alphaComp0 = comp0;
        l->alphaRef0 = ref0;
        l->alphaOp = op;
        l->alphaComp1 = comp1;
        l->alphaRef1 = ref1;
        l->alphaCompareOff = 0;
    } else {
        l->alphaComp0 = 7;
        l->alphaRef0 = 0;
        l->alphaOp = 0;
        l->alphaComp1 = 7;
        l->alphaRef1 = 0;
        l->alphaCompareOff = 1;
    }
    GFX_DIRTY(l, 24, 0x10, 0x40)
}

void GSgfxZCompare(u8 enable, u32 func) {
    GSgfxLayer* l = gsgfxState->layer;
    if (enable == 1) {
        l->zEnable = 1;
    } else {
        l->zEnable = 0;
    }
    l->zFunc = func;
    GFX_DIRTY(l, 24, 8, 0x40)
}

void GSgfxPixelMode(u8 colorUpdate, u8 alphaUpdate, u8 dither) {
    GSgfxLayer* l = gsgfxState->layer;
    if (colorUpdate == 1) {
        l->colorUpdate = 1;
    } else {
        l->colorUpdate = 0;
    }
    if (alphaUpdate == 1) {
        l->alphaUpdate = 1;
    } else {
        l->alphaUpdate = 0;
    }
    if (dither == 1) {
        l->dither = 1;
    } else {
        l->dither = 0;
    }
    GFX_DIRTY(l, 24, 4, 0x40)
}

void GSgfxBlendMode(int type, u32 src, u32 dst) {
    GSgfxLayer* l = gsgfxState->layer;
    if (type == 0) {
        if (l->blendIndex != 0) {
            l->blendIndex = 0;
            l->blendSet = &l->blendSets[l->blendIndex];
        }
        l->blendType = 0;
        l->blendSrc = 1;
        l->blendDst = 1;
        l->blendLogicOp = 5;
    } else {
        if (l->blendIndex != 1) {
            l->blendIndex = 1;
            l->blendSet = &l->blendSets[l->blendIndex];
        }
        l->blendType = type;
        l->blendSrc = src;
        l->blendDst = dst;
        l->blendLogicOp = 5;
    }
    GFX_DIRTY(l, 24, 1, 0x40)
}

void GSgfxSetLineWidth(f32 width) {
    GSgfxLayer* l = gsgfxState->layer;
    l->lineWidth = 6.0f * width;
    l->lineTexOffsets = 0;
    GFX_DIRTY(l, 0, 4, 1)
}

void GSgfxTexCoord2f(f32 s, f32 t) {
    GX_WGPIPE.f32 = s;
    GX_WGPIPE.f32 = t;
}

void GSgfxColor4u8(u8 r, u8 g, u8 b, u8 a) {
    GX_WGPIPE.u8 = r;
    GX_WGPIPE.u8 = g;
    GX_WGPIPE.u8 = b;
    GX_WGPIPE.u8 = a;
}

void GSgfxVertex2s16(s16 x, s16 y) {
    GX_WGPIPE.s16 = x;
    GX_WGPIPE.s16 = y;
}

void GSgfxVertex2f(f32 x, f32 y) {
    GX_WGPIPE.f32 = x;
    GX_WGPIPE.f32 = y;
}

void GSgfxVertex3f(f32 x, f32 y, f32 z) {
    GX_WGPIPE.f32 = x;
    GX_WGPIPE.f32 = y;
    GX_WGPIPE.f32 = z;
}

void GSgfxEndSurface(void) {
    gsgfxState->layer->endSurface();
}

void GSgfxBeginSurface(unsigned short num) {
    gsgfxState->layer->beginSurface(num);
}

void GSgfxSetPrimitiveType(u32 type) {
    gsgfxState->layer->primType = type;
}

}
