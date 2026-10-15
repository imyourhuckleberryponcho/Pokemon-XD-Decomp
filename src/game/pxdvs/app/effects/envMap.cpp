#include <dolphin/types.h>

struct GSgfxLayer;
enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct GSmodel;

extern "C" {
void GSmodelDisableEnvMap(GSmodel* model);
bool GSmodelIsEnvMapEnabled(GSmodel* model);
void GSmodelEnableEnvMap(GSmodel* model, u32 texture, u32 texture2, f32 blend);
void GSmodelSetEnvMapBlendValue(GSmodel* model, f32 blend);
}

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

// Applies an environment map to a model while active.
class envMapEffect : public GSeffect {
public:
    virtual ~envMapEffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32 dt);

    GSmodel* m_model;
    u32 m_texture;
    u32 m_texture2;
    f32 m_blend;
};

envMapEffect::~envMapEffect() {
    Stop();
}

void envMapEffect::_stop() {
    if (m_model != NULL) {
        GSmodelDisableEnvMap(m_model);
    }
}

bool envMapEffect::_update(f32 dt) {
    if (m_model == NULL) {
        return false;
    }
    if (!GSmodelIsEnvMapEnabled(m_model)) {
        GSmodelEnableEnvMap(m_model, m_texture, m_texture2, m_blend);
    } else {
        GSmodelSetEnvMapBlendValue(m_model, m_blend);
    }
    return true;
}

bool envMapEffect::_start() {
    if (m_model == NULL) {
        return false;
    }
    GSmodelEnableEnvMap(m_model, m_texture, m_texture2, m_blend);
    return true;
}
