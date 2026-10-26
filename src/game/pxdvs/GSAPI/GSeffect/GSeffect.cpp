#include <dolphin/types.h>

struct GSgfxLayer;

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(GSgfxLayer* layer, GSgfxLayerPass pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 unk18;
};

void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);

extern "C" u8 GSgfxVideoGetVsyncRate(void);

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

static GSeffect* g_effects_list;

static void _effectUpdate(f32 dt);
static void _effectRender(GSgfxLayer* layer, GSgfxLayerPass pass);
static void _effectFastRender();

extern "C" void GSeffectInitSystem(void) {
    GSgfxRenderModule module = { NULL, _effectUpdate, _effectRender, _effectFastRender, NULL, NULL, 0xB29A48E1 };
    GSgfxRenderModuleRegister(0x60, &module, NULL);
}

static void _effectFastRender() {
    GSeffect* effect;
    for (effect = g_effects_list; effect != NULL; effect = effect->m_next) {
        if (effect->m_active && effect->m_visible) {
            effect->_fastRender();
        }
    }
}

static void _effectRender(GSgfxLayer* layer, GSgfxLayerPass pass) {
    GSeffect* effect;
    for (effect = g_effects_list; effect != NULL; effect = effect->m_next) {
        if (effect->m_active && effect->m_visible) {
            effect->_render(layer, pass);
        }
    }
}

static void _effectUpdate(f32 dt) {
    GSeffect* effect;
    for (effect = g_effects_list; effect != NULL; effect = effect->m_next) {
        f32 step = dt / GSgfxVideoGetVsyncRate();
        if (effect->m_active && !effect->_update(step) && effect->m_active) {
            effect->_stop();
            effect->m_active = false;
            effect->m_visible = false;
        }
    }
}

GSeffect::~GSeffect() {
    GSeffect* prev = g_effects_list;
    if (this == g_effects_list) {
        g_effects_list = m_next;
        m_next = NULL;
    } else {
        for (; prev != NULL; prev = prev->m_next) {
            if (prev->m_next == this) {
                prev->m_next = m_next;
                m_next = NULL;
                break;
            }
        }
    }
}

void GSeffect::Stop() {
    if (m_active) {
        _stop();
        m_active = false;
        m_visible = false;
    }
}

bool GSeffect::Start() {
    if (_start()) {
        m_active = true;
        m_visible = true;
    } else {
        m_active = false;
        m_visible = false;
    }
    return m_active;
}

void GSeffect::_fastRender() {}

void GSeffect::_render(GSgfxLayer* layer, GSgfxLayerPass pass) {}

bool GSeffect::_update(f32 dt) {
    return true;
}

void GSeffect::_stop() {}

bool GSeffect::_start() {
    return true;
}

GSeffect::GSeffect() {
    m_active = false;
    m_visible = false;
    m_next = NULL;
    m_next = g_effects_list;
    g_effects_list = this;
}
