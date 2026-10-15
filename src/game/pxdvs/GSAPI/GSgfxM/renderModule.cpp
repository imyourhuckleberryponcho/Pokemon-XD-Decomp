#include <dolphin/types.h>

struct GSgfxLayer;

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

// Callbacks a render module provides; any of them may be NULL.
struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(GSgfxLayer* layer, GSgfxLayerPass pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    void* unk18;
};

struct RenderModuleNode {
    RenderModuleNode* next;
    u8 used;
    u8 priority;
    GSgfxRenderModule module;
};

extern "C" {
extern int __float_epsilon[];
void* memcpy(void* dst, const void* src, unsigned long n);
void* memset(void* dst, int c, unsigned long n);
}

static RenderModuleNode _renderModuleList[9];
static RenderModuleNode* _renderModuleBottom;
static bool _renderModuleIsRendering;

bool GSgfxRenderModuleIsRendering() {
    return _renderModuleIsRendering;
}

void GSgfxRenderModuleDoPostUpdate(f32 dt) {
    RenderModuleNode* node;
    u32 frames = dt + *(f32*)__float_epsilon;
    u32 i;

    for (i = 0; i < frames; i++) {
        for (node = _renderModuleBottom; node != NULL; node = node->next) {
            if (node->module.frameUpdate != NULL) {
                node->module.frameUpdate();
            }
        }
    }
    for (node = _renderModuleBottom; node != NULL; node = node->next) {
        if (node->module.postUpdate != NULL) {
            node->module.postUpdate(dt);
        }
    }
}

void GSgfxRenderModuleDoRender(GSgfxLayer* layer, GSgfxLayerPass pass) {
    RenderModuleNode* node;
    _renderModuleIsRendering = true;
    for (node = _renderModuleBottom; node != NULL; node = node->next) {
        if (node->module.render != NULL) {
            node->module.render(layer, pass);
        }
    }
    _renderModuleIsRendering = false;
}

void GSgfxRenderModuleDoRenderFast() {
    RenderModuleNode* node;
    _renderModuleIsRendering = true;
    for (node = _renderModuleBottom; node != NULL; node = node->next) {
        if (node->module.renderFast != NULL) {
            node->module.renderFast();
        }
    }
    _renderModuleIsRendering = false;
}

void GSgfxRenderModuleDoPreUpdate(f32 dt) {
    RenderModuleNode* node;
    for (node = _renderModuleBottom; node != NULL; node = node->next) {
        if (node->module.preUpdate != NULL) {
            node->module.preUpdate(dt);
        }
    }
}

static inline void _renderModuleRemove(RenderModuleNode* node) {
    RenderModuleNode* prev;
    if (_renderModuleBottom == node) {
        _renderModuleBottom = node->next;
    } else {
        for (prev = _renderModuleBottom; prev != NULL; prev = prev->next) {
            if (prev->next == node) {
                break;
            }
        }
        prev->next = node->next;
    }
    node->next = NULL;
}

static inline void _renderModuleInsert(RenderModuleNode* node, u8 priority) {
    RenderModuleNode* prev;
    RenderModuleNode* cur;
    node->priority = priority;
    prev = _renderModuleBottom;
    if (prev == NULL || prev->priority > priority) {
        node->next = prev;
        _renderModuleBottom = node;
    } else {
        for (cur = prev->next; cur != NULL; cur = cur->next) {
            if (cur->priority > priority) {
                break;
            }
            prev = cur;
        }
        node->next = cur;
        prev->next = node;
    }
}

void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user) {
    s32 i;

    for (i = 0; i < 9; i++) {
        RenderModuleNode* node = &_renderModuleList[i];
        if (!node->used) {
            node->used = true;
            node->priority = 0;
            node->next = _renderModuleBottom;
            _renderModuleBottom = node;
            memcpy(&node->module, module, 0x1C);
            if (node->priority != priority) {
                _renderModuleRemove(node);
                _renderModuleInsert(node, priority);
            }
            if (module->init != NULL) {
                module->init(user);
            }
            return;
        }
    }
}

void GSgfxRenderModuleInit() {
    memset(_renderModuleList, 0, sizeof(_renderModuleList));
    _renderModuleBottom = NULL;
    _renderModuleIsRendering = false;
}
