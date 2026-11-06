#ifndef __MWERKS__
#include <game/psq.h>
#endif
#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
#include <libc/string.h>

#pragma pool_strings off

struct GSgfxVF;
struct GSgfxLight;
struct GSmtx;
struct GStexture {
    u8 unk0[7];
    u8 unk7;
};

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};
enum GSgfxLayerID {};
enum GSgfxLayerOffset {};
enum GSgfxLayerType {};
enum GSgfxCunitAlpha {};
enum GSgfxCunitSrc {};
enum GSgfxLightType {};
enum GSgfxDiffuseFunc {};
enum GSgfxTgenFunc {};
enum GSgfxTgenSrc {};

struct GSmtx44 {
    f32 m[4][4];
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};

struct BlendState {
    u8 pad[0xbc];
};

#define LF(type, off) (*(type*)((u8*)this + (off)))

#include <game/gsgfxlayer.h>
#ifdef __MWERKS__
#define GLOW_HW(T, p, off, m) (*(T*)(p + (off)))
#else
#define GLOW_HW(T, p, off, m) (*(T*)&layer->hw.m)
#endif

struct GSgfxLayer : public GSgfxLayerData {
public:
    void cunitChannelGen(u8 chan, GSgfxCunitAlpha alpha, GSgfxCunitSrc src0, GSgfxCunitSrc src1, u32 lights,
                         GSgfxLight** light, GSgfxLightType lightType, GSgfxDiffuseFunc diffuse);
    void tgenFunc(u8 index, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* mtx, bool normalize, GSmtx* post);
    GStexture* GetTextureCopy();
    void SetTextureCopy(GStexture* tex, bool clear, u8* clearColor);
    void beginSurface(u16 count);
    void endSurface();
    u16 tokenMark();

};

class GSgfxLayerConfig {
public:
    static void Remove(GSgfxLayerID id);
    static GSgfxLayerID Add(char* name, u32 width, u32 height, u32 count, GSgfxLayerType type, bool clearColor,
                            bool clearAlpha, bool clearDepth, GSgfxLayerID relative, GSgfxLayerOffset offset);
};

extern "C" {
GSgfxLayer* GSgfxLayerFindByID(GSgfxLayerID id);
void GSgfxTokenWaitForClear(u16 token);
void GSmtx44Ortho(f32* mtx, f32, f32, f32, f32, f32, f32);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
}
extern "C" GSmtx44 mtxIdent;

class GSeffect {
public:
    bool m_active;
    bool m_visible;
    GSeffect* m_next;

    GSeffect();
    bool Start();
    void Stop();

    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32 dt);
    virtual void _render(GSgfxLayer* layer, GSgfxLayerPass pass);
    virtual void _fastRender();
    virtual ~GSeffect();
};

static inline f32 __OSu8tof32(register const u8* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 2 }
#else
    ret = PSQ_LOAD(arg, 0, 2);
#endif
    return ret;
}

static inline f32 OSu8tof32(u8 in) {
    return __OSu8tof32(&in);
}

static inline u8 __OSf32tou8(register f32 inF) {
    u32 tmp;
    register u32* tmpPtr = &tmp;
    register u8 ret;
#ifdef __MWERKS__
    asm {
        psq_st inF, 0(tmpPtr), 1, 2
        lbz ret, 0(tmpPtr)
    }
#else
    PSQ_STORE(tmpPtr, 0, inF, 2);
    ret = *(u8*)tmpPtr;
#endif
    return ret;
}

static inline u8 OSf32tou8(f32 in) {
    return __OSf32tou8(in);
}

class glowEffect : public GSeffect {
public:
    glowEffect();
    virtual ~glowEffect();
    virtual void _render(GSgfxLayer* layer, GSgfxLayerPass pass);
    void _renderOffset(GSgfxLayer* layer);
    void _renderScale(GSgfxLayer* layer);

    f32 m_strength;
    u8 m_samples;
    u8 m_additive;
    u8 m_flag;
    u8 m_mode;
    u8 m_passes;

    static GSgfxLayerID texture_layer_id;
    static u16 token;
    static u8 layer_reference;
};

GSgfxLayerID glowEffect::texture_layer_id = (GSgfxLayerID)-1;
u16 glowEffect::token;
u8 glowEffect::layer_reference;

glowEffect::~glowEffect() {
    Stop();
    if (layer_reference != 0) {
        if (--layer_reference == 0) {
            GSgfxLayer* layer = GSgfxLayerFindByID(texture_layer_id);
            if (token != 0) {
                GSgfxTokenWaitForClear(token);
                token = 0;
            }
            if (layer != 0) {
                layer->SetTextureCopy(0, false, 0);
            }
            GSgfxLayerConfig::Remove(texture_layer_id);
            texture_layer_id = (GSgfxLayerID)-1;
        }
    }
}

void glowEffect::_render(GSgfxLayer* layer, GSgfxLayerPass pass) {
    if (texture_layer_id != (GSgfxLayerID)-1) {
        if ((*(GSgfxLayerID*)&layer->id) == 6 && pass == 1) {
            GSgfxLayer* src = GSgfxLayerFindByID(texture_layer_id);
            if (src != 0) {
                GStexture* tex = src->GetTextureCopy();
                if (tex != 0) {
                    f32 mtx[16];
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
                    s32 dst = 1;
                    if (m_additive != 0) {
                        dst = 5;
                    }
                    if ((*(s32*)&layer->curPass) != 1) {
                        (*(s32*)&layer->curPass) = 1;
                        layer->curFifo = &layer->passes[layer->curPass];
                    }
                    (*(s32*)&layer->hw.blend[0]) = 1;
                    (*(s32*)&layer->hw.blend[1]) = 4;
                    (*(s32*)&layer->hw.blend[2]) = dst;
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
                    (*(u8*)&layer->hw.zEnable) = 0;
                    (*(s32*)&layer->hw.zFunc) = 3;
                    (*(u32*)&layer->dirty[0].pe) |= 8;
                    (*(u32*)&layer->dirty[0].groups) |= 0x40;
                    (*(u32*)&layer->dirty[1].pe) |= 8;
                    (*(u32*)&layer->dirty[1].groups) |= 0x40;
                    (*(s32*)&layer->hw.cullMode) = 2;
                    (*(u32*)&layer->dirty[0].raster) |= 2;
                    (*(u32*)&layer->dirty[0].groups) |= 2;
                    (*(u32*)&layer->dirty[1].raster) |= 2;
                    (*(u32*)&layer->dirty[1].groups) |= 2;
                    if ((*(void**)&layer->dirty[0].tex[0]) != tex || (*(void**)&layer->dirty[1].tex[0]) != tex || tex->unk7 != 0) {
                        (*(void**)&layer->dirty[0].tex[0]) = tex;
                        (*(u32*)&layer->dirty[0].texMask) |= 1;
                        (*(void**)&layer->dirty[1].tex[0]) = tex;
                        (*(u32*)&layer->dirty[1].texMask) |= 1;
                    }
                    (*(u32*)&layer->unk1998) = 0x80;
                    switch (m_mode) {
                    case 1:
                        _renderScale(layer);
                        break;
                    case 0:
                    default:
                        _renderOffset(layer);
                        break;
                    }
                    token = layer->tokenMark();
                }
            }
        }
    }
}

static inline void _glowHead(s16 x, s16 y, u8 alpha) {
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = alpha;
}

static inline void _glowTex2(f32 a, f32 b) {
    GXWGFifo.f32 = a;
    GXWGFifo.f32 = b;
}

void glowEffect::_renderOffset(GSgfxLayer* layer) {
    u32 stage;
    f32 weights[2];
    weights[0] = 0.24197073f;
    weights[1] = 0.053990968f;
    f32 size = 0.25f * OSu8tof32(m_samples);
    f32 zero = 0.0f;
    f32 one = 1.0f;
    u8 i;
    u32 j;

    (*(GSgfxVF**)&layer->curVF) = GSgfxVFBuildTemp(0, 2, 0, 0, 1, 5, 4, 1, 4);
    LAYER_F(layer, u8*, 0xDB8, hw.nChans) = 1;
    LAYER_F(layer, u32*, 0x16BC, dirty[0].lightDirty) |= 1;
    (*(u32*)&layer->dirty[0].groups) |= 4;
    LAYER_F(layer, u32*, 0x1774, dirty[1].lightDirty) |= 1;
    (*(u32*)&layer->dirty[1].groups) |= 4;
    layer->cunitChannelGen(0, (GSgfxCunitAlpha)1, (GSgfxCunitSrc)1, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2,
                           (GSgfxDiffuseFunc)0);
    LAYER_F(layer, u8*, 0xC70, hw.nTexGens) = 4;
    (*(u32*)&layer->dirty[0].geom) |= 1;
    (*(u32*)&layer->dirty[0].groups) |= 1;
    (*(u32*)&layer->dirty[1].geom) |= 1;
    (*(u32*)&layer->dirty[1].groups) |= 1;
    LAYER_F(layer, u8*, 0xEAC, hw.nTevStages) = 4;
    LAYER_F(layer, u32*, 0x16CC, dirty[0].tev) |= 1;
    (*(u32*)&layer->dirty[0].groups) |= 8;
    LAYER_F(layer, u32*, 0x1784, dirty[1].tev) |= 1;
    (*(u32*)&layer->dirty[1].groups) |= 8;
    for (i = 0; i < 4; i++) {
        stage = i;
        bool last;
        u32 bit;
        u32 v;
        u8* a;
        u8* b;
        u8* c;
        layer->tgenFunc(i, (GSgfxTgenFunc)1, (GSgfxTgenSrc)(stage + 4), 0, false, 0);
        last = false;
        if (m_flag != 0) {
            if (stage == 3) {
                last = true;
            }
        }
        v = 0;
        if (last) {
            v = 3;
        }
        a = (u8*)layer + i * 0x14;
        GLOW_HW(u32, a, 0x1178, colorOp[i].scale) = v;
        bit = 1 << stage;
        GLOW_HW(u32, a, 0x1174, colorOp[i].bias) = 0;
        GLOW_HW(u32, a, 0x1170, colorOp[i].op) = 0;
        GLOW_HW(u8, a, 0x117c, colorOp[i].clamp) = (i == 3);
        GLOW_HW(u32, a, 0x1180, colorOp[i].reg) = 0;
        LAYER_F(layer, u32*, 0x16DC, dirty[0].colorOp) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x1794, dirty[1].colorOp) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
        last = false;
        if (m_flag != 0) {
            if (i == 3) {
                last = true;
            }
        }
        v = 0;
        if (last) {
            v = 3;
        }
        GLOW_HW(u32, a, 0x12b0, alphaOp[i].op) = 0;
        GLOW_HW(u32, a, 0x12b8, alphaOp[i].scale) = v;
        GLOW_HW(u32, a, 0x12b4, alphaOp[i].bias) = 0;
        GLOW_HW(u8, a, 0x12bc, alphaOp[i].clamp) = (i == 3);
        GLOW_HW(u32, a, 0x12c0, alphaOp[i].reg) = 0;
        LAYER_F(layer, u32*, 0x16E0, dirty[0].alphaOp) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x1798, dirty[1].alphaOp) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
        b = (u8*)layer + i * 16;
        GLOW_HW(u32, b, 0xf70, colorIn[i][0]) = 8;
        GLOW_HW(u32, b, 0xf74, colorIn[i][1]) = 0xf;
        GLOW_HW(u32, b, 0xf78, colorIn[i][2]) = 0xf;
        v = 0xf;
        if (i != 0) {
            v = 0;
        }
        GLOW_HW(u32, b, 0xf7c, colorIn[i][3]) = v;
        LAYER_F(layer, u32*, 0x16D4, dirty[0].colorIn) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x178C, dirty[1].colorIn) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
        GLOW_HW(u32, b, 0x1070, alphaIn[i][0]) = 7;
        GLOW_HW(u32, b, 0x1074, alphaIn[i][1]) = 5;
        GLOW_HW(u32, b, 0x1078, alphaIn[i][2]) = 4;
        v = 7;
        if (i != 0) {
            v = 0;
        }
        GLOW_HW(u32, b, 0x107c, alphaIn[i][3]) = v;
        LAYER_F(layer, u32*, 0x16D8, dirty[0].alphaIn) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x1790, dirty[1].alphaIn) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
        c = (u8*)layer + stage * 12;
        GLOW_HW(u32, c, 0xeb0, tevOrder[stage][0]) = stage;
        GLOW_HW(u32, c, 0xeb4, tevOrder[stage][1]) = 0;
        GLOW_HW(u32, c, 0xeb8, tevOrder[stage][2]) = 4;
        LAYER_F(layer, u32*, 0x16D0, dirty[0].tevOrder) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x1788, dirty[1].tevOrder) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
    }
    layer->beginSurface((u16)((m_passes * 4) * (m_passes + 1)));
    for (i = 0; i < m_passes; i++) {
        f32 dx = 0.0015625f * (size * OSu8tof32((u8)(i + 1)));
        f32 dy = 0.0020833334f * (size * OSu8tof32((u8)(i + 1)));
        u8 alpha = OSf32tou8(0.25f * (255.0f * (m_strength * weights[i])) + 0.5f);
        _glowHead(0, 0, alpha);
        _glowTex2(-dx, zero);
        _glowTex2(zero, -dy);
        _glowTex2(dx, zero);
        _glowTex2(zero, dy);
        _glowHead(640, 0, alpha);
        _glowTex2(one - dx, zero);
        _glowTex2(one, -dy);
        _glowTex2(one + dx, zero);
        _glowTex2(one, dy);
        _glowHead(640, 480, alpha);
        _glowTex2(one - dx, one);
        _glowTex2(one, one - dy);
        _glowTex2(one + dx, one);
        _glowTex2(one, one + dy);
        _glowHead(0, 480, alpha);
        _glowTex2(-dx, one);
        _glowTex2(zero, one - dy);
        _glowTex2(dx, one);
        _glowTex2(zero, one + dy);
        for (j = 0; (u8)j < m_passes; j++) {
            u32 alphaj = OSf32tou8(0.25f * (255.0f * ((m_strength * weights[i]) * weights[(u8)j])) + 0.5f);
            f32 dyj = 0.0020833334f * (size * OSu8tof32((u8)(j + 1)));
            _glowHead(0, 0, alphaj);
            _glowTex2(-dx, -dyj);
            _glowTex2(-dx, dyj);
            _glowTex2(dx, -dyj);
            _glowTex2(dx, dyj);
            _glowHead(640, 0, alphaj);
            _glowTex2(one - dx, -dyj);
            _glowTex2(one - dx, dyj);
            _glowTex2(one + dx, -dyj);
            _glowTex2(one + dx, dyj);
            _glowHead(640, 480, alphaj);
            _glowTex2(one - dx, one - dyj);
            _glowTex2(one - dx, one + dyj);
            _glowTex2(one + dx, one - dyj);
            _glowTex2(one + dx, one + dyj);
            _glowHead(0, 480, alphaj);
            _glowTex2(-dx, one - dyj);
            _glowTex2(-dx, one + dyj);
            _glowTex2(dx, one - dyj);
            _glowTex2(dx, one + dyj);
        }
    }
    layer->endSurface();
}

void glowEffect::_renderScale(GSgfxLayer* layer) {
    f32 weights[4];
    weights[0] = 0.17603268f;
    weights[1] = 0.12098537f;
    weights[2] = 0.0647588f;
    weights[3] = 0.026995484f;
    f32 size = 0.25f * OSu8tof32(m_samples);
    u8 i;

    (*(GSgfxVF**)&layer->curVF) = GSgfxVFBuildTemp(0, 2, 0, 0, 1, 5, 2, 1, 4);
    LAYER_F(layer, u8*, 0xDB8, hw.nChans) = 1;
    LAYER_F(layer, u32*, 0x16BC, dirty[0].lightDirty) |= 1;
    (*(u32*)&layer->dirty[0].groups) |= 4;
    LAYER_F(layer, u32*, 0x1774, dirty[1].lightDirty) |= 1;
    (*(u32*)&layer->dirty[1].groups) |= 4;
    layer->cunitChannelGen(0, (GSgfxCunitAlpha)1, (GSgfxCunitSrc)1, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2,
                           (GSgfxDiffuseFunc)0);
    LAYER_F(layer, u8*, 0xC70, hw.nTexGens) = 2;
    (*(u32*)&layer->dirty[0].geom) |= 1;
    (*(u32*)&layer->dirty[0].groups) |= 1;
    (*(u32*)&layer->dirty[1].geom) |= 1;
    (*(u32*)&layer->dirty[1].groups) |= 1;
    LAYER_F(layer, u8*, 0xEAC, hw.nTevStages) = 2;
    LAYER_F(layer, u32*, 0x16CC, dirty[0].tev) |= 1;
    (*(u32*)&layer->dirty[0].groups) |= 8;
    LAYER_F(layer, u32*, 0x1784, dirty[1].tev) |= 1;
    (*(u32*)&layer->dirty[1].groups) |= 8;
    for (i = 0; i < 2; i++) {
        u32 stage = i;
        bool last;
        u32 bit;
        u8* b;
        u8* a;
        u32 v;
        u8* c;
        layer->tgenFunc(i, (GSgfxTgenFunc)1, (GSgfxTgenSrc)(stage + 4), 0, false, 0);
        last = false;
        if (m_flag != 0) {
            if (stage == 1) {
                last = true;
            }
        }
        v = 0;
        if (last) {
            v = 3;
        }
        a = (u8*)layer + i * 0x14;
        bit = 1 << stage;
        GLOW_HW(u32, a, 0x1170, colorOp[i].op) = 0;
        GLOW_HW(u32, a, 0x1174, colorOp[i].bias) = 0;
        GLOW_HW(u32, a, 0x1178, colorOp[i].scale) = v;
        GLOW_HW(u8, a, 0x117c, colorOp[i].clamp) = (i == 1);
        GLOW_HW(u32, a, 0x1180, colorOp[i].reg) = 0;
        LAYER_F(layer, u32*, 0x16DC, dirty[0].colorOp) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x1794, dirty[1].colorOp) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
        last = false;
        if (m_flag != 0) {
            if (i == 1) {
                last = true;
            }
        }
        v = 0;
        if (last) {
            v = 3;
        }
        GLOW_HW(u32, a, 0x12b0, alphaOp[i].op) = 0;
        GLOW_HW(u32, a, 0x12b4, alphaOp[i].bias) = 0;
        GLOW_HW(u32, a, 0x12b8, alphaOp[i].scale) = v;
        GLOW_HW(u8, a, 0x12bc, alphaOp[i].clamp) = (i == 1);
        GLOW_HW(u32, a, 0x12c0, alphaOp[i].reg) = 0;
        LAYER_F(layer, u32*, 0x16E0, dirty[0].alphaOp) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x1798, dirty[1].alphaOp) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
        b = (u8*)layer + i * 16;
        GLOW_HW(u32, b, 0xf70, colorIn[i][0]) = 8;
        GLOW_HW(u32, b, 0xf74, colorIn[i][1]) = 0xf;
        GLOW_HW(u32, b, 0xf78, colorIn[i][2]) = 0xf;
        v = 0xf;
        if (i != 0) {
            v = 0;
        }
        GLOW_HW(u32, b, 0xf7c, colorIn[i][3]) = v;
        LAYER_F(layer, u32*, 0x16D4, dirty[0].colorIn) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x178C, dirty[1].colorIn) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
        GLOW_HW(u32, b, 0x1070, alphaIn[i][0]) = 7;
        GLOW_HW(u32, b, 0x1074, alphaIn[i][1]) = 5;
        GLOW_HW(u32, b, 0x1078, alphaIn[i][2]) = 4;
        v = 7;
        if (i != 0) {
            v = 0;
        }
        GLOW_HW(u32, b, 0x107c, alphaIn[i][3]) = v;
        LAYER_F(layer, u32*, 0x16D8, dirty[0].alphaIn) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x1790, dirty[1].alphaIn) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
        c = (u8*)layer + i * 12;
        GLOW_HW(u32, c, 0xeb0, tevOrder[i][0]) = stage;
        GLOW_HW(u32, c, 0xeb4, tevOrder[i][1]) = 0;
        GLOW_HW(u32, c, 0xeb8, tevOrder[i][2]) = 4;
        LAYER_F(layer, u32*, 0x16D0, dirty[0].tevOrder) |= bit;
        (*(u32*)&layer->dirty[0].groups) |= 8;
        LAYER_F(layer, u32*, 0x1788, dirty[1].tevOrder) |= bit;
        (*(u32*)&layer->dirty[1].groups) |= 8;
    }
    layer->beginSurface((u16)(m_passes * 8));
    for (i = 0; i < m_passes * 2; i++) {
        f32 ox = 0.0015625f * (size * OSu8tof32((u8)(i + 1)));
        f32 oy = 0.0020833334f * (size * OSu8tof32((u8)(i + 1)));
        u8 alpha = OSf32tou8(255.0f * (m_strength * weights[i]) + 0.5f);
        _glowHead(0, 0, alpha);
        _glowTex2(-ox, -oy);
        _glowTex2(ox, oy);
        _glowHead(640, 0, alpha);
        _glowTex2(1.0f + ox, -oy);
        _glowTex2(1.0f - ox, oy);
        _glowHead(640, 480, alpha);
        _glowTex2(1.0f + ox, 1.0f + oy);
        _glowTex2(1.0f - ox, 1.0f - oy);
        _glowHead(0, 480, alpha);
        _glowTex2(-ox, 1.0f + oy);
        _glowTex2(ox, 1.0f - oy);
    }
    layer->endSurface();
}

glowEffect::glowEffect() {
    m_strength = 1.0f;
    m_samples = 12;
    m_additive = 1;
    m_flag = 0;
    m_mode = 1;
    m_passes = 1;
    if (texture_layer_id == (GSgfxLayerID)-1) {
        texture_layer_id = GSgfxLayerConfig::Add("glow effect", 0, 0x400, 1, (GSgfxLayerType)0, false, false, false,
                                                 (GSgfxLayerID)6, (GSgfxLayerOffset)1);
        GSgfxLayer* layer = GSgfxLayerFindByID(texture_layer_id);
        if (layer != 0) {
            layer->SetTextureCopy((GStexture*)0xFEFEFEFE, false, 0);
        }
    }
    layer_reference++;
}
