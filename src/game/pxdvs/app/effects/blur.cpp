#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
#include <libc/string.h>

struct GSgfxVF;
struct GStexture {
    u8 unk0[7];
    u8 unk7;
};
struct GSmodel;
struct GSparticleBank;

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct BlendState {
    u8 pad[0xbc];
};

struct GSmtx44 {
    f32 m[4][4];
};

class GSgfxLayer {
public:
    void setRenderStateAndSelect(struct GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();
    u16 tokenMark();

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
    u8 pad_199c[0x19a0 - 0x199c];
    struct GSlayerCam* cam;
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};

extern "C" {
void GSmtx44Ortho(f32* mtx, f32, f32, f32, f32, f32, f32);
GSgfxVF* GSgfxVFGetPredef(s32 id);
bool GSgfxEndBackFBCapture(GStexture* texture);
typedef bool (*GSgfxBackFBCallback)(GStexture* texture, u32 frame, void* user);
bool GSgfxBeginBackFBCapture(GStexture* texture, GSgfxBackFBCallback callback, void* user);
void GSgfxTokenWaitForClear(u16 token);
GStexture* GStextureCreate(u16 width, u16 height, s32 format, s32, s32);
void GStextureFree(GStexture* texture);
void GScameraLoadActiveCameraMatrix(s32 id);
bool GSmodelIsAnimating(GSmodel* model);
f32 GSmodelGetAnimFrame(GSmodel* model);
f32 GSmodelGetAnimRate(GSmodel* model);
void GSmodelSetAnimFrame(GSmodel* model, f32 frame);
void GSmodelSetPEdescr(GSmodel* model, u8* desc);
void GSmodelResetPEdescr(GSmodel* model);
void GSmodelSetRenderFlags(GSmodel* model, u32 flags);
void GSmodelResetRenderFlags(GSmodel* model);
void GSmodelInitMaterialAlpha(GSmodel* model);
void GSmodelSetMaterialAlpha(GSmodel* model, f32 alpha);
void GSmodelResetMaterialAlpha(GSmodel* model);
GSparticleBank* GSmodelGetLinkedGSparticleBank(GSmodel* model);
void GSmodelForceAnimTransformUpdate(GSmodel* model);
void GSmodelDrawModel(GSmodel* model, GSgfxLayer* layer, GSgfxLayerPass pass);
void GSmodelAdvanceAnimation(GSmodel* model, f32 dt);
void GSparticleDisactivateBank(GSparticleBank* bank);
void GSparticleActivateBank(GSparticleBank* bank);
void GSparticleSetBankVisibility(GSparticleBank* bank, bool visible);
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

class blurEffect : public GSeffect {
public:
    blurEffect(bool useFramebuffer);
    virtual ~blurEffect();
    virtual bool _start();
    virtual void _stop();
    virtual void _render(GSgfxLayer* layer, GSgfxLayerPass pass);
    void RenderFB(GSgfxLayer* layer);

    union {
        GStexture* m_tex;
        GSmodel* m_model;
    };
    u16 m_token;
    bool m_captured;
    u8 m_pad13;
    u8 m_useFB;
    u8 m_pad15[3];
    f32 m_strength;
};

static inline void __OSf32tou8(register f32 arg, volatile register u8* out) {
    asm { psq_st arg, 0(out), 1, 2 }
}

static inline u8 OSf32tou8(f32 in) {
    u8 out;
    __OSf32tou8(in, &out);
    return out;
}

blurEffect::~blurEffect() {
    Stop();
    if (m_useFB != 0) {
        if (m_tex != 0) {
            if (m_token != 0) {
                GSgfxTokenWaitForClear(m_token);
                m_token = 0;
            }
            GStextureFree(m_tex);
        }
    }
}

void blurEffect::_stop() {
    if (m_useFB != 0) {
        GSgfxEndBackFBCapture(m_tex);
        m_captured = 0;
    }
}

bool blurEffectRenderFBCallback(GStexture* texture, u32 frame, void* user);

void blurEffect::_render(GSgfxLayer* layer, GSgfxLayerPass pass) {
    if (m_useFB != 0) {
        if (layer->id == 6 && pass == 1) {
            RenderFB(layer);
        }
    } else if (m_model != 0) {
        if (layer->id == 2 && pass == 0) {
            if (GSmodelIsAnimating(m_model)) {
                s32 count = (s32)(20.0f * m_strength + 0.5f);
                if (count != 0) {
                    static u8 pedesc[12] = {0x13, 0x00, 0x00, 0xFF, 0x01, 0x04, 0x05, 0x0F, 0x01, 0x07, 0x00, 0x07};
                    f32 rate;
                    s32 i;
                    f32 half;
                    f32 inv;
                    GSparticleBank* bank;
                    f32 frame;
                    f32 start;
                    frame = GSmodelGetAnimFrame(m_model);
                    rate = GSmodelGetAnimRate(m_model);
                    start = frame - rate * (f32)count;
                    if (start < 0.0f) {
                        count = (s32)(frame / rate);
                        start = 0.0f;
                    }
                    if (count != 0 && !(start >= frame)) {
                        GSmodelSetPEdescr(m_model, pedesc);
                        GSmodelSetRenderFlags(m_model, 0x20);
                        GSmodelInitMaterialAlpha(m_model);
                        GScameraLoadActiveCameraMatrix(-1);
                        bank = GSmodelGetLinkedGSparticleBank(m_model);
                        if (bank != 0) {
                            GSparticleDisactivateBank(bank);
                            GSparticleSetBankVisibility(bank, false);
                        }
                        GSmodelSetAnimFrame(m_model, start);
                        i = 1;
                        inv = 1.0f / (f32)count;
                        half = 0.5f * rate;
                        while (start + half < frame) {
                            f32 t = (f32)i * inv;
                            start += rate;
                            i++;
                            GSmodelSetMaterialAlpha(m_model, 0.5f * t * t);
                            GSmodelForceAnimTransformUpdate(m_model);
                            GSmodelDrawModel(m_model, layer, pass);
                            GSmodelAdvanceAnimation(m_model, 1.0f);
                        }
                        GSmodelResetMaterialAlpha(m_model);
                        GSmodelResetRenderFlags(m_model);
                        GSmodelResetPEdescr(m_model);
                        GSmodelSetAnimFrame(m_model, frame);
                        GSmodelForceAnimTransformUpdate(m_model);
                        GSmodelDrawModel(m_model, layer, pass);
                        if (bank != 0) {
                            GSparticleActivateBank(bank);
                            GSparticleSetBankVisibility(bank, true);
                        }
                    }
                }
            }
        }
    }
}

bool blurEffect::_start() {
    if (m_useFB != 0) {
        if (m_tex == 0) {
            return false;
        }
        m_captured = 0;
        GSgfxBeginBackFBCapture(m_tex, blurEffectRenderFBCallback, this);
    }
    return true;
}

blurEffect::blurEffect(bool useFramebuffer) {
    m_tex = 0;
    m_model = 0;
    m_token = 0;
    m_captured = 0;
    m_useFB = useFramebuffer;
    m_strength = 0.0f;
    if (useFramebuffer) {
        m_tex = GStextureCreate(0, 0, 0x44, 0, 0);
    }
}

void blurEffect::RenderFB(GSgfxLayer* layer) {
    if (m_captured != 0) {
        f32 mtx[16];
        u8 alpha = OSf32tou8(255.0f * m_strength);
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
        if (layer->curBlendIdx != 1) {
            layer->curBlendIdx = 1;
            layer->curBlend = &layer->blendTable[layer->curBlendIdx];
        }
        layer->blendOp = 1;
        layer->blendSrc = 4;
        layer->blendDst = 5;
        layer->blendLogic = 5;
        layer->dirty170c |= 1;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 1;
        layer->dirty1760 |= 0x40;
        layer->zEnable = 0;
        layer->zFunc = 7;
        layer->dirty170c |= 8;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 8;
        layer->dirty1760 |= 0x40;
        layer->colorUpdate = 1;
        layer->alphaUpdate = 1;
        layer->zUpdate = 0;
        layer->dirty170c |= 4;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 4;
        layer->dirty1760 |= 0x40;
        layer->d8c = 0;
        layer->dirty16b8 |= 2;
        layer->dirty16a8 |= 2;
        layer->dirty1770 |= 2;
        layer->dirty1760 |= 2;
        layer->setRenderStateAndSelect(GSgfxVFGetPredef(5));
        GStexture* tex = m_tex;
        if (layer->tex1740 != tex || layer->tex17f8 != tex || tex->unk7 != 0) {
            layer->tex1740 = tex;
            layer->dirty173c |= 1;
            layer->tex17f8 = tex;
            layer->dirty17f4 |= 1;
        }
        layer->primType = 0x98;
        layer->beginSurface(4);
        {
            f32 zero = 0.0f;
            f32 w = 640.0f;
            f32 one = 1.0f;
            f32 h = 480.0f;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = alpha;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = w;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = alpha;
            GXWGFifo.f32 = one;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = h;
            GXWGFifo.f32 = zero;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = alpha;
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = one;
            GXWGFifo.f32 = w;
            GXWGFifo.f32 = h;
            GXWGFifo.f32 = zero;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = 0xFF;
            GXWGFifo.u8 = alpha;
            GXWGFifo.f32 = one;
            GXWGFifo.f32 = one;
        }
        layer->endSurface();
        m_token = layer->tokenMark();
    }
}

bool blurEffectRenderFBCallback(GStexture* texture, u32 frame, void* user) {
    blurEffect* effect = (blurEffect*)user;
    effect->m_captured = (texture == effect->m_tex);
    return effect->m_captured;
}
