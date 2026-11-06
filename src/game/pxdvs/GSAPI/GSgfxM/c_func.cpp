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
    void* base;
    GSgfxMtxEntry* top;
};

enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxLayerType { GSgfxLayerType_draft_dummy };
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    u16 tokenMark();
    void dlDraw(GSgfxDL* dl);
    void setRenderStateAndSelect(GSgfxVF* vf);
    void endSurface();
    void beginSurface(unsigned short num);

};

#include <game/gsgfxstate.h>

#define GFX_DIRTY(l, word, bits, group) \
    (&(l)->dirty[0].geom)[word] |= (bits); \
    (l)->dirty[0].groups |= (group);     \
    (&(l)->dirty[1].geom)[word] |= (bits); \
    (l)->dirty[1].groups |= (group);

#ifdef __MWERKS__
#define GX_WGPIPE (*(volatile union { u8 u8; s16 s16; f32 f32; }*)0xCC008000)
#else
#define GX_WGPIPE GXWGFifo
#endif

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
        return &((GSgfxMtxStack*)gsgfxState->layer->matrixStack)->top->mtx;
    case 1: {
        GSgfxMtxStack* stack = ((GSgfxMtxStack*)gsgfxState->layer->matrixStack);
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
    l->hw.alphaIn[unit][0] = a;
    l->hw.alphaIn[unit][1] = b;
    l->hw.alphaIn[unit][2] = c;
    l->hw.alphaIn[unit][3] = d;
    GFX_DIRTY(l, 11, bit, 8)
}

void GSgfxSetTUnitUserAlphaOp(u8 unit, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
    GSgfxLayer* l = gsgfxState->layer;
    l->hw.alphaOp[unit].op = op;
    l->hw.alphaOp[unit].bias = bias;
    l->hw.alphaOp[unit].scale = scale;
    l->hw.alphaOp[unit].clamp = clamp != 0;
    l->hw.alphaOp[unit].reg = reg;
    GFX_DIRTY(l, 13, 1 << unit, 8)
}

void GSgfxSetTUnitUserColorArg(u8 unit, u32 a, u32 b, u32 c, u32 d) {
    GSgfxLayer* l = gsgfxState->layer;
    u32 bit = 1 << (u32)unit;
    l->hw.colorIn[unit][0] = a;
    l->hw.colorIn[unit][1] = b;
    l->hw.colorIn[unit][2] = c;
    l->hw.colorIn[unit][3] = d;
    GFX_DIRTY(l, 10, bit, 8)
}

void GSgfxSetTUnitUserColorOp(u8 unit, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg) {
    GSgfxLayer* l = gsgfxState->layer;
    l->hw.colorOp[unit].op = op;
    l->hw.colorOp[unit].bias = bias;
    l->hw.colorOp[unit].scale = scale;
    l->hw.colorOp[unit].clamp = clamp != 0;
    l->hw.colorOp[unit].reg = reg;
    GFX_DIRTY(l, 12, 1 << unit, 8)
}

void GSgfxSelectTexture(u8 map, GStexture* texture) {
    GSgfxLayer* l = gsgfxState->layer;
    if ((GStexture*)l->dirty[0].tex[map] == texture && (GStexture*)l->dirty[1].tex[map] == texture && !texture->reload) {
        return;
    }
    l->dirty[0].tex[map] = (GSgfxTex*)texture;
    l->dirty[0].texMask |= 1 << map;
    l->dirty[1].tex[map] = (GSgfxTex*)texture;
    l->dirty[1].texMask |= 1 << map;
}

void GSgfxCullMode(u32 mode) {
    GSgfxLayer* l = gsgfxState->layer;
    l->hw.cullMode = mode;
    GFX_DIRTY(l, 3, 2, 2)
}

void GSgfxAlphaCompare(u8 enable, u32 comp0, u8 ref0, u32 op, u32 comp1, u8 ref1) {
    GSgfxLayer* l = gsgfxState->layer;
    if (enable == 1) {
        l->hw.alphaComp0 = comp0;
        l->hw.alphaRef0 = ref0;
        l->hw.alphaCmpOp = op;
        l->hw.alphaComp1 = comp1;
        l->hw.alphaRef1 = ref1;
        l->hw.zCompLoc = 0;
    } else {
        l->hw.alphaComp0 = 7;
        l->hw.alphaRef0 = 0;
        l->hw.alphaCmpOp = 0;
        l->hw.alphaComp1 = 7;
        l->hw.alphaRef1 = 0;
        l->hw.zCompLoc = 1;
    }
    GFX_DIRTY(l, 24, 0x10, 0x40)
}

void GSgfxZCompare(u8 enable, u32 func) {
    GSgfxLayer* l = gsgfxState->layer;
    if (enable == 1) {
        l->hw.zEnable = 1;
    } else {
        l->hw.zEnable = 0;
    }
    l->hw.zFunc = func;
    GFX_DIRTY(l, 24, 8, 0x40)
}

void GSgfxPixelMode(u8 colorUpdate, u8 alphaUpdate, u8 dither) {
    GSgfxLayer* l = gsgfxState->layer;
    if (colorUpdate == 1) {
        l->hw.colorUpdate = 1;
    } else {
        l->hw.colorUpdate = 0;
    }
    if (alphaUpdate == 1) {
        l->hw.alphaUpdate = 1;
    } else {
        l->hw.alphaUpdate = 0;
    }
    if (dither == 1) {
        l->hw.zUpdate = 1;
    } else {
        l->hw.zUpdate = 0;
    }
    GFX_DIRTY(l, 24, 4, 0x40)
}

void GSgfxBlendMode(int type, u32 src, u32 dst) {
    GSgfxLayer* l = gsgfxState->layer;
    if (type == 0) {
        if (l->curPass != 0) {
            l->curPass = 0;
            l->curFifo = &l->passes[l->curPass];
        }
        l->hw.blend[0] = 0;
        l->hw.blend[1] = 1;
        l->hw.blend[2] = 1;
        l->hw.blend[3] = 5;
    } else {
        if (l->curPass != 1) {
            l->curPass = 1;
            l->curFifo = &l->passes[l->curPass];
        }
        l->hw.blend[0] = type;
        l->hw.blend[1] = src;
        l->hw.blend[2] = dst;
        l->hw.blend[3] = 5;
    }
    GFX_DIRTY(l, 24, 1, 0x40)
}

void GSgfxSetLineWidth(f32 width) {
    GSgfxLayer* l = gsgfxState->layer;
    l->hw.lineWidth = 6.0f * width;
    l->hw.lineOffset = 0;
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
    gsgfxState->layer->unk1998 = type;
}

}
