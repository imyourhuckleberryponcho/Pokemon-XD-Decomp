// STATUS: 2/5 exact (dtor, ctor); _render 99.6%, _renderScale 87%, _renderOffset 82% (registers/stack temps); LAYOUT OK, CONST OK
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

class GSgfxLayer {
public:
    void cunitChannelGen(u8 chan, GSgfxCunitAlpha alpha, GSgfxCunitSrc src0, GSgfxCunitSrc src1, u32 lights,
                         GSgfxLight** light, GSgfxLightType lightType, GSgfxDiffuseFunc diffuse);
    void tgenFunc(u8 index, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* mtx, bool normalize, GSmtx* post);
    GStexture* GetTextureCopy();
    void SetTextureCopy(GStexture* tex, bool clear, u8* clearColor);
    void beginSurface(u16 count);
    void endSurface();
    u16 tokenMark();

    u8 pad0[0x28];
    GSgfxLayerID id;
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
    u8 pad_1710[0x173c - 0x1710];
    u32 dirty173c;
    void* tex1740;
    u8 pad_1744[0x1760 - 0x1744];
    u32 dirty1760;
    u32 dirty1764;
    u8 pad_1768[8];
    u32 dirty1770;
    u8 pad_1774[0x17c4 - 0x1774];
    u32 dirty17c4;
    u8 pad_17c8[0x17f4 - 0x17c8];
    u32 dirty17f4;
    void* tex17f8;
    u8 pad_17fc[0x1818 - 0x17fc];
    BlendState blendTable[2];
    BlendState* curBlend;
    s32 curBlendIdx;
    u32 primType;
    GSgfxVF* vf;
    GSlayerCam* cam;
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
extern GSmtx44 mtxIdent;

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

// From the Dolphin SDK's OSFastCast.h (GQR2 is set up for u8 conversion).
static inline f32 __OSu8tof32(register const u8* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 2 }
    return ret;
}

static inline f32 OSu8tof32(u8 in) {
    u8 tmp = in;
    return __OSu8tof32(&tmp);
}

static inline void __OSf32tou8(register f32 arg, volatile register u8* out) {
    asm { psq_st arg, 0(out), 1, 2 }
}

static inline u8 OSf32tou8(f32 in) {
    u8 out;
    __OSf32tou8(in, &out);
    return out;
}

// Glow: re-draws a copy of the screen with several offset passes (box/gaussian-like blur).
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
        if (layer->id == 6 && pass == 1) {
            GSgfxLayer* src = GSgfxLayerFindByID(texture_layer_id);
            if (src != 0) {
                GStexture* tex = src->GetTextureCopy();
                if (tex != 0) {
                    f32 mtx[16];
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
                    s32 dst = 1;
                    if (m_additive != 0) {
                        dst = 5;
                    }
                    if (layer->curBlendIdx != 1) {
                        layer->curBlendIdx = 1;
                        layer->curBlend = &layer->blendTable[layer->curBlendIdx];
                    }
                    layer->blendOp = 1;
                    layer->blendSrc = 4;
                    layer->blendDst = dst;
                    layer->blendLogic = 5;
                    layer->dirty170c |= 1;
                    layer->dirty16a8 |= 0x40;
                    layer->dirty17c4 |= 1;
                    layer->dirty1760 |= 0x40;
                    layer->colorUpdate = 1;
                    layer->alphaUpdate = 1;
                    layer->zUpdate = 0;
                    layer->dirty170c |= 4;
                    layer->dirty16a8 |= 0x40;
                    layer->dirty17c4 |= 4;
                    layer->dirty1760 |= 0x40;
                    layer->f1664 = 7;
                    layer->f1670 = 0;
                    layer->f1668 = 0;
                    layer->f166c = 7;
                    layer->f1671 = 0;
                    layer->f1672 = 1;
                    layer->dirty170c |= 0x10;
                    layer->dirty16a8 |= 0x40;
                    layer->dirty17c4 |= 0x10;
                    layer->dirty1760 |= 0x40;
                    layer->zEnable = 0;
                    layer->zFunc = 3;
                    layer->dirty170c |= 8;
                    layer->dirty16a8 |= 0x40;
                    layer->dirty17c4 |= 8;
                    layer->dirty1760 |= 0x40;
                    layer->d8c = 2;
                    layer->dirty16b8 |= 2;
                    layer->dirty16a8 |= 2;
                    layer->dirty1770 |= 2;
                    layer->dirty1760 |= 2;
                    if (layer->tex1740 != tex || layer->tex17f8 != tex || tex->unk7 != 0) {
                        layer->tex1740 = tex;
                        layer->dirty173c |= 1;
                        layer->tex17f8 = tex;
                        layer->dirty17f4 |= 1;
                    }
                    layer->primType = 0x80;
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

// One vertex: s16 position, white color with alpha, then texture coordinates.
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
    f32 weights[2];
    weights[0] = 0.24197073f;
    weights[1] = 0.053990968f;
    f32 size = 0.25f * OSu8tof32(m_samples);
    u32 i;
    u32 j;

    layer->vf = GSgfxVFBuildTemp(0, 2, 0, 0, 1, 5, 4, 1, 4);
    *(u8*)((u8*)layer + 0xdb8) = 1;
    *(u32*)((u8*)layer + 0x16bc) |= 1;
    layer->dirty16a8 |= 4;
    *(u32*)((u8*)layer + 0x1774) |= 1;
    layer->dirty1760 |= 4;
    layer->cunitChannelGen(0, (GSgfxCunitAlpha)1, (GSgfxCunitSrc)1, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2,
                           (GSgfxDiffuseFunc)0);
    *(u8*)((u8*)layer + 0xc70) = 4;
    layer->dirty16ac |= 1;
    layer->dirty16a8 |= 1;
    layer->dirty1764 |= 1;
    layer->dirty1760 |= 1;
    *(u8*)((u8*)layer + 0xeac) = 4;
    *(u32*)((u8*)layer + 0x16cc) |= 1;
    layer->dirty16a8 |= 8;
    *(u32*)((u8*)layer + 0x1784) |= 1;
    layer->dirty1760 |= 8;
    for (i = 0; (u8)i < 4; i++) {
        u8 stage = (u8)i;
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
        a = (u8*)layer + (u8)i * 0x14;
        bit = 1 << stage;
        *(u32*)(a + 0x1170) = 0;
        *(u32*)(a + 0x1174) = 0;
        *(u32*)(a + 0x1178) = v;
        *(u8*)(a + 0x117c) = ((u8)i == 3);
        *(u32*)(a + 0x1180) = 0;
        *(u32*)((u8*)layer + 0x16dc) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x1794) |= bit;
        layer->dirty1760 |= 8;
        last = false;
        if (m_flag != 0) {
            if ((u8)i == 3) {
                last = true;
            }
        }
        v = 0;
        if (last) {
            v = 3;
        }
        *(u32*)(a + 0x12b0) = 0;
        *(u32*)(a + 0x12b4) = 0;
        *(u32*)(a + 0x12b8) = v;
        *(u8*)(a + 0x12bc) = ((u8)i == 3);
        *(u32*)(a + 0x12c0) = 0;
        *(u32*)((u8*)layer + 0x16e0) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x1798) |= bit;
        layer->dirty1760 |= 8;
        b = (u8*)layer + (u8)i * 16;
        v = 0xf;
        if ((u8)i == 0) {
            v = 0;
        }
        *(u32*)(b + 0xf70) = 8;
        *(u32*)(b + 0xf74) = 0xf;
        *(u32*)(b + 0xf78) = 0xf;
        *(u32*)((u8*)layer + 0x16d4) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x178c) |= bit;
        layer->dirty1760 |= 8;
        v = 7;
        *(u32*)(b + 0xf7c) = v;
        switch ((u8)i) {
        case 0:
                v = 0;
            break;
        }
        *(u32*)(b + 0x1070) = 7;
        *(u32*)(b + 0x1074) = 5;
        *(u32*)(b + 0x1078) = 4;
        *(u32*)(b + 0x107c) = v;
        *(u32*)((u8*)layer + 0x16d8) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x1790) |= bit;
        layer->dirty1760 |= 8;
        c = (u8*)layer + (u8)i * 12;
        *(u32*)(c + 0xeb0) = stage;
        *(u32*)(c + 0xeb4) = 0;
        *(u32*)(c + 0xeb8) = 4;
        *(u32*)((u8*)layer + 0x16d0) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x1788) |= bit;
        layer->dirty1760 |= 8;
    }
    layer->beginSurface((u16)((m_passes * 4) * (m_passes + 1)));
    for (i = 0; (u8)i < m_passes; i++) {
        f32 step = size * OSu8tof32((u8)(i + 1));
        f32 kc3439 = 0.0015625f;
        f32 dx = step * kc3439;
        f32 dy = 0.0020833334f * (size * OSu8tof32((u8)(i + 1)));
        u8 alpha = OSf32tou8(0.25f * (255.0f * (m_strength * weights[(u8)i])) + 0.5f);
        _glowHead(0, 0, alpha);
        _glowTex2(-dx, 0.0f);
        _glowTex2(0.0f, -dy);
        _glowTex2(dx, 0.0f);
        _glowTex2(0.0f, dy);
        _glowHead(640, 0, alpha);
        _glowTex2(1.0f - dx, 0.0f);
        _glowTex2(1.0f, -dy);
        _glowTex2(1.0f + dx, 0.0f);
        _glowTex2(1.0f, dy);
        _glowHead(640, 480, alpha);
        _glowTex2(1.0f - dx, 1.0f);
        _glowTex2(1.0f, 1.0f - dy);
        _glowTex2(1.0f + dx, 1.0f);
        _glowTex2(1.0f, 1.0f + dy);
        _glowHead(0, 480, alpha);
        _glowTex2(-dx, 1.0f);
        _glowTex2(0.0f, 1.0f - dy);
        _glowTex2(dx, 1.0f);
        _glowTex2(0.0f, 1.0f + dy);
        for (j = 0; (u8)j < m_passes; j++) {
            u32 alphaj = OSf32tou8(0.25f * (255.0f * ((m_strength * weights[(u8)i]) * weights[(u8)j])) + 0.5f);
            f32 dyj = 0.0020833334f * (size * OSu8tof32((u8)(j + 1)));
            _glowHead(0, 0, alphaj);
            _glowTex2(-dx, -dyj);
            _glowTex2(-dx, dyj);
            _glowTex2(dx, -dyj);
            _glowTex2(dx, dyj);
            _glowHead(640, 0, alphaj);
            _glowTex2(1.0f - dx, -dyj);
            _glowTex2(1.0f - dx, dyj);
            _glowTex2(1.0f + dx, -dyj);
            _glowTex2(1.0f + dx, dyj);
            _glowHead(640, 480, alphaj);
            _glowTex2(1.0f - dx, 1.0f - dyj);
            _glowTex2(1.0f - dx, 1.0f + dyj);
            _glowTex2(1.0f + dx, 1.0f - dyj);
            _glowTex2(1.0f + dx, 1.0f + dyj);
            _glowHead(0, 480, alphaj);
            _glowTex2(-dx, 1.0f - dyj);
            _glowTex2(-dx, 1.0f + dyj);
            _glowTex2(dx, 1.0f - dyj);
            _glowTex2(dx, 1.0f + dyj);
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
    u32 i;

    layer->vf = GSgfxVFBuildTemp(0, 2, 0, 0, 1, 5, 2, 1, 4);
    *(u8*)((u8*)layer + 0xdb8) = 1;
    *(u32*)((u8*)layer + 0x16bc) |= 1;
    layer->dirty16a8 |= 4;
    *(u32*)((u8*)layer + 0x1774) |= 1;
    layer->dirty1760 |= 4;
    layer->cunitChannelGen(0, (GSgfxCunitAlpha)1, (GSgfxCunitSrc)1, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2,
                           (GSgfxDiffuseFunc)0);
    *(u8*)((u8*)layer + 0xc70) = 2;
    layer->dirty16ac |= 1;
    layer->dirty16a8 |= 1;
    layer->dirty1764 |= 1;
    layer->dirty1760 |= 1;
    *(u8*)((u8*)layer + 0xeac) = 2;
    *(u32*)((u8*)layer + 0x16cc) |= 1;
    layer->dirty16a8 |= 8;
    *(u32*)((u8*)layer + 0x1784) |= 1;
    layer->dirty1760 |= 8;
    for (i = 0; (u8)i < 2; i++) {
        u8 stage = (u8)i;
        bool last;
        u32 bit;
        u32 v;
        u8* a;
        u8* b;
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
        a = (u8*)layer + (u8)i * 0x14;
        bit = 1 << stage;
        *(u32*)(a + 0x1170) = 0;
        *(u32*)(a + 0x1174) = 0;
        *(u32*)(a + 0x1178) = v;
        *(u8*)(a + 0x117c) = ((u8)i == 1);
        *(u32*)(a + 0x1180) = 0;
        *(u32*)((u8*)layer + 0x16dc) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x1794) |= bit;
        layer->dirty1760 |= 8;
        last = false;
        if (m_flag != 0) {
            if ((u8)i == 1) {
                last = true;
            }
        }
        v = 0;
        if (last) {
            v = 3;
        }
        *(u32*)(a + 0x12b0) = 0;
        *(u32*)(a + 0x12b4) = 0;
        *(u32*)(a + 0x12b8) = v;
        *(u8*)(a + 0x12bc) = ((u8)i == 1);
        *(u32*)(a + 0x12c0) = 0;
        *(u32*)((u8*)layer + 0x16e0) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x1798) |= bit;
        layer->dirty1760 |= 8;
        b = (u8*)layer + (u8)i * 16;
        v = 0xf;
        if ((u8)i == 0) {
            v = 0;
        }
        *(u32*)(b + 0xf70) = 8;
        *(u32*)(b + 0xf74) = 0xf;
        *(u32*)(b + 0xf78) = 0xf;
        *(u32*)(b + 0xf7c) = v;
        *(u32*)((u8*)layer + 0x16d4) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x178c) |= bit;
        layer->dirty1760 |= 8;
        v = 7;
        if ((u8)i == 0) {
            v = 0;
        }
        *(u32*)(b + 0x1070) = 7;
        *(u32*)(b + 0x1074) = 5;
        *(u32*)(b + 0x1078) = 4;
        *(u32*)(b + 0x107c) = v;
        *(u32*)((u8*)layer + 0x16d8) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x1790) |= bit;
        layer->dirty1760 |= 8;
        c = (u8*)layer + (u8)i * 12;
        *(u32*)(c + 0xeb0) = stage;
        *(u32*)(c + 0xeb4) = 0;
        *(u32*)(c + 0xeb8) = 4;
        *(u32*)((u8*)layer + 0x16d0) |= bit;
        layer->dirty16a8 |= 8;
        *(u32*)((u8*)layer + 0x1788) |= bit;
        layer->dirty1760 |= 8;
    }
    layer->beginSurface((u16)(m_passes * 8));
    for (i = 0; (u8)i < m_passes * 2; i++) {
        f32 ox = (size * OSu8tof32((u8)(i + 1)));
        ox *= 0.0015625f;
        f32 oy = 0.0020833334f;
        oy *= (size * OSu8tof32((u8)(i + 1)));
        u8 alpha = OSf32tou8(0.25f * (255.0f * (m_strength * weights[(u8)i])) + 0.5f);
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
