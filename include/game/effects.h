#ifndef GAME_EFFECTS_H
#define GAME_EFFECTS_H

#include <dolphin/types.h>

struct GSgfxLayer;
struct GSmodel;
struct GStexture;
struct _GSparticleBank;
struct GSparticleGenerator;
struct BoneFillOwner;
enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};
enum enumNullJointName {
    NULL_JOINT_0
};

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

#if defined(__MWERKS__) && !defined(BLUR_EFFECT_SOURCE)
    GStexture* m_tex;
#else
    union {
        GStexture* m_tex;
        GSmodel* m_model;
    };
#endif
    u16 m_token;
    bool m_captured;
    u8 m_pad13;
    u8 m_useFB;
    u8 m_pad15[3];
    f32 m_strength;
};

class boneFillEffect : public GSeffect {
public:
    boneFillEffect(_GSparticleBank* bank, enumNullJointName from, enumNullJointName to, f32 length);
    virtual ~boneFillEffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32 dt);

    _GSparticleBank* m_bank;
    GSparticleGenerator* m_generator;
    BoneFillOwner* m_owner;
    enumNullJointName m_from;
    enumNullJointName m_to;
    s32 m_parts[2];
    f32 m_length;
};

class envMapEffect : public GSeffect {
public:
    envMapEffect(u32 texture, u32 texture2);
    virtual ~envMapEffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32 dt);

    GSmodel* m_model;
    u32 m_texture;
    u32 m_texture2;
    f32 m_blend;
};

class filterEffect : public GSeffect {
public:
    filterEffect();
    filterEffect(bool invert, bool mono);
    virtual ~filterEffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32 dt);
    void UpdateModulation();
    void InitModulation();

    void* m_target;
    u8 m_saved[4];
    u8 m_resetPE;
    u8 m_useSaved;
    u8 m_hasSaved;
    u8 m_pad17;
    u8 m_modulate;
    u8 m_color[4];
};

#endif
