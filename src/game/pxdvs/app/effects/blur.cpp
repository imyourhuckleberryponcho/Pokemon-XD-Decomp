#ifndef __MWERKS__
#include <game/psq.h>
#endif
#include <dolphin/types.h>
#define BLUR_EFFECT_SOURCE
#include <game/effects.h>
#include <dolphin/gx/GXVert.h>
#include <libc/string.h>

struct GSgfxVF;
struct GStexture {
    u8 unk0[7];
    u8 unk7;
};
struct GSmodel;
struct GSparticleBank;

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
    void setRenderStateAndSelect(struct GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();
    u16 tokenMark();

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
extern "C" GSmtx44 mtxIdent;

static inline void __OSf32tou8(register f32 arg, volatile register u8* out) {
#ifdef __MWERKS__
    asm { psq_st arg, 0(out), 1, 2 }
#else
    PSQ_STORE(out, 0, arg, 2);
#endif
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
        if ((*(s32*)&layer->id) == 6 && pass == 1) {
            RenderFB(layer);
        }
    } else if (m_model != 0) {
        if ((*(s32*)&layer->id) == 2 && pass == 0) {
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
        if ((*(s32*)&layer->curPass) != 1) {
            (*(s32*)&layer->curPass) = 1;
            layer->curFifo = &layer->passes[layer->curPass];
        }
        (*(s32*)&layer->hw.blend[0]) = 1;
        (*(s32*)&layer->hw.blend[1]) = 4;
        (*(s32*)&layer->hw.blend[2]) = 5;
        (*(s32*)&layer->hw.blend[3]) = 5;
        (*(u32*)&layer->dirty[0].pe) |= 1;
        (*(u32*)&layer->dirty[0].groups) |= 0x40;
        (*(u32*)&layer->dirty[1].pe) |= 1;
        (*(u32*)&layer->dirty[1].groups) |= 0x40;
        (*(u8*)&layer->hw.zEnable) = 0;
        (*(s32*)&layer->hw.zFunc) = 7;
        (*(u32*)&layer->dirty[0].pe) |= 8;
        (*(u32*)&layer->dirty[0].groups) |= 0x40;
        (*(u32*)&layer->dirty[1].pe) |= 8;
        (*(u32*)&layer->dirty[1].groups) |= 0x40;
        (*(u8*)&layer->hw.colorUpdate) = 1;
        (*(u8*)&layer->hw.alphaUpdate) = 1;
        (*(u8*)&layer->hw.zUpdate) = 0;
        (*(u32*)&layer->dirty[0].pe) |= 4;
        (*(u32*)&layer->dirty[0].groups) |= 0x40;
        (*(u32*)&layer->dirty[1].pe) |= 4;
        (*(u32*)&layer->dirty[1].groups) |= 0x40;
        (*(s32*)&layer->hw.cullMode) = 0;
        (*(u32*)&layer->dirty[0].raster) |= 2;
        (*(u32*)&layer->dirty[0].groups) |= 2;
        (*(u32*)&layer->dirty[1].raster) |= 2;
        (*(u32*)&layer->dirty[1].groups) |= 2;
        layer->setRenderStateAndSelect(GSgfxVFGetPredef(5));
        GStexture* tex = m_tex;
        if ((*(void**)&layer->dirty[0].tex[0]) != tex || (*(void**)&layer->dirty[1].tex[0]) != tex || tex->unk7 != 0) {
            (*(void**)&layer->dirty[0].tex[0]) = tex;
            (*(u32*)&layer->dirty[0].texMask) |= 1;
            (*(void**)&layer->dirty[1].tex[0]) = tex;
            (*(u32*)&layer->dirty[1].texMask) |= 1;
        }
        (*(u32*)&layer->unk1998) = 0x98;
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
