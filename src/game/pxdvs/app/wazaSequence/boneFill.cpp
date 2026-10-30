#include <dolphin/types.h>

struct GSgfxLayer;
enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct Vec {
    f32 x, y, z;
};

struct _GSparticleBank;
struct GSparticleGenerator;
struct GSmodel;
struct GSpart;

enum enumNullJointName {
    NULL_JOINT_0
};

struct NullJointTable {
    u8 unk0[0x4C];
    s32 joints[1];
};

struct BoneFillOwner {
    u8 unk0[0x52];
    u8 tableIndex;
    u8 unk53[0x41];
    GSmodel* model;
    u8 unk98[4];
    u8* tables;
};

extern "C" {
double asin(double x);
double atan2(double y, double x);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* dst);
f32 PSVECMag(const Vec* v);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
}

extern "C" {
void GSparticleDestroyGenerator(GSparticleGenerator* gen, bool);
bool GSparticleIsGeneratorAlive(GSparticleGenerator* gen);
void GSparticleSetGeneratorPosition(GSparticleGenerator* gen, Vec* pos);
void GSparticleSetGeneratorScale(GSparticleGenerator* gen, Vec* scale, s32, s32);
void GSparticleSetGeneratorRotation(GSparticleGenerator* gen, Vec* rot);
GSparticleGenerator* GSparticleCreateGenerator(_GSparticleBank* bank, s32, s32);
GSpart* GSmodelGetPart(GSmodel* model, s32 id);
void GSpartGetTransform(GSpart* part, Vec* pos, Vec* rot, Vec* scale);
void GSpartFree(GSpart* part);
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

boneFillEffect::~boneFillEffect() {
    Stop();
}

void boneFillEffect::_stop() {
    m_owner = NULL;
    if (m_generator != NULL) {
        GSparticleDestroyGenerator(m_generator, true);
        m_generator = NULL;
    }
}

static inline GSmodel* _ownerModel(BoneFillOwner* owner) {
    return owner->model;
}

bool boneFillEffect::_update(f32 dt) {
    GSmodel* model;
    GSpart* part;
    Vec pos[2];
    Vec scale;
    Vec dir;
    Vec rot;
    Vec diff;
    f32 len;
    s32 i;

    if (m_owner == NULL) {
        return false;
    }
    if (m_generator == NULL) {
        return false;
    }
    model = _ownerModel(m_owner);
    if (model == NULL) {
        return false;
    }
    if (!GSparticleIsGeneratorAlive(m_generator)) {
        return false;
    }
    for (i = 0; i < 2; i++) {
        part = GSmodelGetPart(model, m_parts[i]);
        if (part == NULL) {
            return false;
        }
        GSpartGetTransform(part, &pos[i], NULL, NULL);
        GSpartFree(part);
    }
    GSparticleSetGeneratorPosition(m_generator, &pos[0]);
    PSVECSubtract(&pos[1], &pos[0], &diff);
    dir = diff;
    len = PSVECMag(&dir);
    scale.x = scale.y = scale.z = len / m_length;
    GSparticleSetGeneratorScale(m_generator, &scale, 0, 0);
    if (len > 0.00001f) {
        if (0.0f != len) {
            PSVECScale(&dir, &dir, 1.0f / len);
        }
        rot.x = -(f32)asin(dir.y);
        rot.y = (f32)atan2(dir.x, dir.z);
        rot.z = 0.0f;
        GSparticleSetGeneratorRotation(m_generator, &rot);
    }
    return true;
}

bool boneFillEffect::_start() {
    NullJointTable* table;

    if (m_bank == NULL) {
        return false;
    }
    if (m_owner == NULL) {
        return false;
    }
    if (m_owner->model == NULL) {
        return false;
    }
    table = (NullJointTable*)(m_owner->tables + m_owner->tableIndex * 0xD0);
    if (table == NULL) {
        return false;
    }
    m_parts[0] = table->joints[m_from];
    if (m_parts[0] < 0) {
        return false;
    }
    m_parts[1] = table->joints[m_to];
    if (m_parts[1] < 0) {
        return false;
    }
    m_generator = GSparticleCreateGenerator(m_bank, 0, 0);
    if (m_generator != NULL) {
        return _update(0.0f);
    }
    return false;
}

boneFillEffect::boneFillEffect(_GSparticleBank* bank, enumNullJointName from, enumNullJointName to, f32 length) {
    m_bank = bank;
    m_generator = NULL;
    m_owner = NULL;
    m_length = length;
    m_from = from;
    m_to = to;
}
