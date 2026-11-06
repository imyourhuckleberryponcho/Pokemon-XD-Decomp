#include <dolphin/types.h>
#include <game/effects.h>

struct GSgfxLayer;

struct GSmodel;

extern "C" {
void GSmodelDisableEnvMap(GSmodel* model);
bool GSmodelIsEnvMapEnabled(GSmodel* model);
void GSmodelEnableEnvMap(GSmodel* model, u32 texture, u32 texture2, f32 blend);
void GSmodelSetEnvMapBlendValue(GSmodel* model, f32 blend);
}

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
