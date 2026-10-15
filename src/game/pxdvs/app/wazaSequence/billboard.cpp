// STATUS: 5/5 exact, LAYOUT OK, CONST OK; needs extra_cflags -inline deferred (source bottom-to-top)
#include <dolphin/types.h>

struct GSgfxLayer;
enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct Vec {
    f32 x, y, z;
};

struct GSmodel;
struct GSbound;
struct GScamera;
struct GSparticleBank;
struct GSparticleGenerator;

extern "C" {
double tan(double x);
void PSVECAdd(const Vec* a, const Vec* b, Vec* dst);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* dst);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECNormalize(const Vec* src, Vec* dst);

GScamera* cameraGetActive(void);
void GScameraLoadActiveCameraMatrix(s32 id);
void GScameraGetPosition(GScamera* cam, Vec* pos);
void GScameraGetLookAt(GScamera* cam, Vec* a, Vec* b);
void GScameraGetPerspective(GScamera* cam, f32* fov, f32* aspect, f32* near, f32* far);

void GSparticleFree(GSparticleBank* bank);
void GSparticleDestroyAllGenerators(GSparticleBank* bank, s32 children);
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* bank, s32 index, s32);
u32 GSparticleGetGeneratorLife(GSparticleGenerator* gen);
void GSparticleSetGeneratorPosition(GSparticleGenerator* gen, Vec* pos);

void GSresFreeResource(u32 group, u32 id);
void GSresIsUniqueID(u32 group, u32 id, u32);
void* GSresGetResource(u32 group, u32 id);
s32 wazaSequenceSysGetResID(void);
void loadModel(void* archive, u32 group, u32 index, u32 id);

bool GSmodelCanAnimate(GSmodel* model);
bool GSmodelHasAnimationEnded(GSmodel* model);
bool GSmodelCanTexAnimate(GSmodel* model);
bool GSmodelHasTexAnimationEnded(GSmodel* model);
void GSmodelStopAnimation(GSmodel* model);
void GSmodelStopTexAnimation(GSmodel* model);
void GSmodelStartAnimation(GSmodel* model);
void GSmodelStartTexAnimation(GSmodel* model);
void GSmodelSetVisibility(GSmodel* model, bool visible);
void GSmodelSetBoundCheck(GSmodel* model, bool check);
void GSmodelSetRenderLayer(GSmodel* model, s32 count, s32* layers);
void GSmodelSetAnimIndex(GSmodel* model, s32 index);
void GSmodelSetAnimType(GSmodel* model, s32 type);
void GSmodelSetAnimRate(GSmodel* model, f32 rate);
void GSmodelSetAnimFrame(GSmodel* model, f32 frame);
void GSmodelSetTexAnimIndex(GSmodel* model, s32 index);
void GSmodelSetTexAnimType(GSmodel* model, s32 type);
void GSmodelSetTexAnimRate(GSmodel* model, f32 rate);
void GSmodelSetTexAnimFrame(GSmodel* model, f32 frame);
GSbound* GSmodelGetBound(GSmodel* model);
void GSmodelSetPosition(GSmodel* model, Vec* pos);
void GSmodelSetScale(GSmodel* model, Vec* scale);
void GSboundGetSize(GSbound* bound, Vec* size, s32, s32);
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

struct BillboardData {
    s32 size;
    void* archive;
    s32 unk8;
    s32 unkC;
    s32 animIndex;
    s32 particleIndex;
    s32 animType;
};

// Camera-facing quad: a model and/or particle generator placed in front of the camera.
class billboardEffect : public GSeffect {
public:
    billboardEffect(u8** stream);
    virtual ~billboardEffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32 dt);

    u32 m_resID;
    u32 m_resID2;
    GSmodel* m_model;
    GSparticleBank* m_bank;
    s32 m_animType;
    u16 m_animIndex;
    u16 m_particleIndex;
    GSparticleGenerator* m_generator;
};

billboardEffect::billboardEffect(u8** stream) {
    void* archive;
    BillboardData* data = (BillboardData*)*stream;
    m_animIndex = data->animIndex;
    switch (data->animType) {
    case 0:
        m_animType = 0;
        break;
    case 1:
        m_animType = 1;
        break;
    }
    m_particleIndex = data->particleIndex;
    *stream = *stream + 0x20;
    *stream = (u8*)((u32)(*stream + 0x1f) & ~0x1f);
    m_model = 0;
    m_bank = 0;
    m_generator = 0;
    m_resID = 0;
    archive = data->archive;
    if (archive != 0) {
        m_resID = wazaSequenceSysGetResID();
        loadModel(archive, 0x4e20, 0, m_resID);
        GSresIsUniqueID(0x4e20, m_resID, 0);
        m_model = (GSmodel*)GSresGetResource(0x4e20, m_resID);
        if (m_model != 0) {
            GSmodelSetVisibility(m_model, false);
        }
    }
    *stream = *stream + (((u32)data->size + 0x1f) & ~0x1f);
    m_resID2 = 0;
}

bool billboardEffect::_start() {
    if (m_model == 0 && m_bank == 0) {
        return false;
    }
    if (m_bank != 0) {
        m_generator = GSparticleCreateGenerator(m_bank, m_particleIndex, 1);
    }
    if (m_model != 0) {
        s32 layers[1] = {6};
        GSmodelSetVisibility(m_model, true);
        GSmodelSetBoundCheck(m_model, false);
        GSmodelSetRenderLayer(m_model, 1, layers);
        if (GSmodelCanAnimate(m_model)) {
            GSmodelSetAnimIndex(m_model, m_animIndex);
            GSmodelSetAnimType(m_model, m_animType);
            GSmodelSetAnimRate(m_model, 0.5f);
            GSmodelSetAnimFrame(m_model, 0.0f);
            GSmodelStartAnimation(m_model);
        }
        if (GSmodelCanTexAnimate(m_model)) {
            GSmodelSetTexAnimIndex(m_model, m_animIndex);
            GSmodelSetTexAnimType(m_model, m_animType);
            GSmodelSetTexAnimRate(m_model, 0.5f);
            GSmodelSetTexAnimFrame(m_model, 0.0f);
            GSmodelStartTexAnimation(m_model);
        }
    }
    return true;
}

bool billboardEffect::_update(f32 dt) {
    GScamera* cam = cameraGetActive();
    bool result = false;
    Vec pos;
    Vec scale;
    Vec target;
    Vec lookAt;
    Vec size;
    f32 fov, near, aspect, far;

    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    if (cam != 0) {
        GScameraLoadActiveCameraMatrix(6);
        GScameraGetPosition(cam, &pos);
        GScameraGetLookAt(cam, &lookAt, &target);
        PSVECSubtract(&target, &pos, &lookAt);
        PSVECNormalize(&lookAt, &lookAt);
        GScameraGetPerspective(cam, &fov, &aspect, &near, &far);
        near += 1.0f;
        fov = 0.017453292f * fov;
        fov *= 0.5f;
        scale.y = 2.0f * near * (f32)tan(fov);
        scale.x = scale.y * aspect;
        scale.z = 0.0f;
        PSVECScale(&lookAt, &lookAt, near);
        PSVECAdd(&pos, &lookAt, &pos);
    }
    if (m_generator != 0) {
        if (GSparticleGetGeneratorLife(m_generator) != 0) {
            GSparticleSetGeneratorPosition(m_generator, &pos);
            result = true;
        }
    }
    if (m_model != 0) {
        if ((GSmodelCanAnimate(m_model) && !GSmodelHasAnimationEnded(m_model)) ||
            (GSmodelCanTexAnimate(m_model) && !GSmodelHasTexAnimationEnded(m_model))) {
            GSboundGetSize(GSmodelGetBound(m_model), &size, 0, 0);
            scale.x = scale.x / size.x;
            scale.y = scale.y / size.y;
            GSmodelSetPosition(m_model, &pos);
            GSmodelSetScale(m_model, &scale);
            result = true;
        }
    }
    return result;
}

void billboardEffect::_stop() {
    if (m_bank != 0) {
        GSparticleDestroyAllGenerators(m_bank, 1);
    }
    if (m_model != 0) {
        GSmodelStopAnimation(m_model);
        GSmodelStopTexAnimation(m_model);
        GSmodelSetVisibility(m_model, false);
    }
}

billboardEffect::~billboardEffect() {
    Stop();
    if (m_bank != 0) {
        GSparticleFree(m_bank);
    }
    if (m_resID != 0) {
        GSresFreeResource(0x4e20, m_resID);
    }
    if (m_resID2 != 0) {
        GSresFreeResource(0x4e20, m_resID2);
    }
}
