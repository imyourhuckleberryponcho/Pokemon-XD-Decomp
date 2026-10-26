#include <dolphin/types.h>

#pragma pool_strings off

struct GSgfxLayer;
enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct GSfilterEntry;
struct GSmodel;

struct SceneData {
    void** models;
};

extern "C" {
GSfilterEntry* GSfilterCreate(u8* color);
void GSfilterSetColor(GSfilterEntry* filter, u8* color);
void GSfilterFree(GSfilterEntry* filter);

void GSlogWrite(const char* fmt, ...);

u32 floorGetCurrentGroupID(void);
u8* floorDataBiosGetCurrentPtr(void);
u32 floorDataBiosGetMapResID(u8* ptr);
u32 floorReadMakeModelResID(u32 id);
void* GSresGetResource(u32 group, u32 id);
void* HSD_ArchiveGetPublicAddress(void* archive, const char* name);

bool GSmodelIsModulationEnabled(GSmodel* model);
void GSmodelGetModulationColor(GSmodel* model, u8* color);
void GSmodelDisableModulation(GSmodel* model);
void GSmodelSetModulationColor(GSmodel* model, u8* color);
void GSmodelEnableModulation(GSmodel* model, u8* color);
void GSmodelResetPEdescr(GSmodel* model);
void GSmodelSetPEdescr(GSmodel* model, u8* desc);
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

class filterEffect : public GSeffect {
public:
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

filterEffect::~filterEffect() {
    Stop();
}

bool filterEffect::_update(f32 dt) {
    if (m_modulate != 0) {
        UpdateModulation();
    } else if (m_target != 0) {
        GSfilterSetColor((GSfilterEntry*)m_target, m_color);
    } else {
        return false;
    }
    return true;
}

static inline u32 _getMapResID() {
    return floorDataBiosGetMapResID(floorDataBiosGetCurrentPtr());
}

void filterEffect::_stop() {
    if (m_modulate != 0) {
        if (m_target != 0) {
            if (m_hasSaved != 0) {
                GSmodelSetModulationColor((GSmodel*)m_target, m_saved);
            } else {
                GSmodelDisableModulation((GSmodel*)m_target);
            }
            if (m_resetPE != 0) {
                GSmodelResetPEdescr((GSmodel*)m_target);
            }
        } else {
            u32 base;
            SceneData* scene;
            u32 mapRes;
            u32 i;
            u32 group;
            void* res;
            GSmodel* model;
            group = floorGetCurrentGroupID();
            mapRes = _getMapResID();
            i = 0;
            res = GSresGetResource(group, mapRes);
            if (res != 0) {
                scene = (SceneData*)HSD_ArchiveGetPublicAddress(res, "scene_data");
                if (scene != 0) {
                    if (scene->models != 0) {
                        base = floorReadMakeModelResID(mapRes);
                        while (scene->models[i] != 0) {
                            model = (GSmodel*)GSresGetResource(group, base | i);
                            if (model != 0) {
                                GSmodelDisableModulation(model);
                                if (m_resetPE != 0) {
                                    GSmodelResetPEdescr(model);
                                }
                            }
                            i++;
                        }
                    }
                }
            }
        }
    } else if (m_target != 0) {
        GSfilterFree((GSfilterEntry*)m_target);
    }
}

bool filterEffect::_start() {
    if (m_modulate != 0) {
        InitModulation();
    } else {
        m_target = GSfilterCreate(m_color);
        if (m_target == 0) {
            GSlogWrite("filterStart: Could not start filter effect - invalid filter!\n");
            return false;
        }
    }
    return true;
}

void filterEffect::UpdateModulation() {
    u8 color[4];
    if (m_hasSaved != 0) {
        f32 v = ((f32)m_saved[0] + (f32)m_color[0]) - 128.0f;
        if (v < 0.0f) {
            v = 0.0f;
        } else if (v > 255.0f) {
            v = 255.0f;
        }
        color[0] = (u8)v;
        v = ((f32)m_saved[1] + (f32)m_color[1]) - 128.0f;
        if (v < 0.0f) {
            v = 0.0f;
        } else if (v > 255.0f) {
            v = 255.0f;
        }
        color[1] = (u8)v;
        v = ((f32)m_saved[2] + (f32)m_color[2]) - 128.0f;
        if (v < 0.0f) {
            v = 0.0f;
        } else if (v > 255.0f) {
            v = 255.0f;
        }
        color[2] = (u8)v;
        color[3] = (u8)(((f32)m_saved[3] * (f32)m_color[3]) / 255.0f);
    } else {
        color[0] = m_color[0];
        color[1] = m_color[1];
        color[2] = m_color[2];
        color[3] = m_color[3];
    }
    if (m_target != 0) {
        GSmodelSetModulationColor((GSmodel*)m_target, color);
    } else {
        u32 group = floorGetCurrentGroupID();
        u32 mapRes = floorDataBiosGetMapResID(floorDataBiosGetCurrentPtr());
        u32 i = 0;
        void* res = GSresGetResource(group, mapRes);
        if (res != 0) {
            SceneData* scene = (SceneData*)HSD_ArchiveGetPublicAddress(res, "scene_data");
            if (scene != 0) {
                if (scene->models != 0) {
                    u32 base = floorReadMakeModelResID(mapRes);
                    while (scene->models[i] != 0) {
                        GSmodel* model = (GSmodel*)GSresGetResource(group, base | i);
                        if (model != 0) {
                            GSmodelSetModulationColor(model, color);
                        }
                        i++;
                    }
                }
            }
        }
    }
}

void filterEffect::InitModulation() {
    static u8 pedesc[12] = {0x33, 0x00, 0x00, 0xFF, 0x01, 0x04, 0x05, 0x0F, 0x01, 0x04, 0x01, 0x00};
    m_hasSaved = 0;
    if (m_target != 0) {
        if (m_resetPE != 0) {
            GSmodelSetPEdescr((GSmodel*)m_target, pedesc);
        }
        if (!GSmodelIsModulationEnabled((GSmodel*)m_target)) {
            GSmodelEnableModulation((GSmodel*)m_target, m_color);
        } else if (m_useSaved != 0) {
            m_hasSaved = 1;
            GSmodelGetModulationColor((GSmodel*)m_target, m_saved);
        } else {
            GSmodelSetModulationColor((GSmodel*)m_target, m_color);
        }
    } else {
        u32 group = floorGetCurrentGroupID();
        u32 mapRes = floorDataBiosGetMapResID(floorDataBiosGetCurrentPtr());
        u32 i = 0;
        void* res = GSresGetResource(group, mapRes);
        if (res != 0) {
            SceneData* scene = (SceneData*)HSD_ArchiveGetPublicAddress(res, "scene_data");
            if (scene != 0) {
                if (scene->models != 0) {
                    u32 base = floorReadMakeModelResID(mapRes);
                    while (scene->models[i] != 0) {
                        GSmodel* model = (GSmodel*)GSresGetResource(group, base | i);
                        if (model != 0) {
                            if (m_resetPE != 0) {
                                GSmodelSetPEdescr(model, pedesc);
                            }
                            GSmodelEnableModulation(model, m_color);
                        }
                        i++;
                    }
                }
            }
        }
    }
}
