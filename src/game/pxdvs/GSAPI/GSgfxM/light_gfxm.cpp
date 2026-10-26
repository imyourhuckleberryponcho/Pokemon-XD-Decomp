#include <dolphin/types.h>
#include <dolphin/gx/GXLighting.h>

struct GSvec {
    f32 x, y, z;
};

struct GSgfxColAu8 {
    u8 r, g, b, a;
};

extern "C" {
void PSVECNormalize(const GSvec* src, GSvec* dst);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
}

enum {
    LIGHT_DIRTY_COLOR = 1 << 0,
    LIGHT_DIRTY_POS = 1 << 1,
    LIGHT_DIRTY_DIR = 1 << 2,
    LIGHT_DIRTY_ATTN = 1 << 3,
    LIGHT_DIRTY_SPOT = 1 << 4,
    LIGHT_DIRTY_HALF = 1 << 5,
    LIGHT_DIRTY_SHININESS = 1 << 6,
};

enum GSgfxLightType {
    GS_GFX_LIGHT_SPECULAR,
    GS_GFX_LIGHT_SPOT,
    GS_GFX_LIGHT_DIFFUSE,
};

class GSgfxLight {
public:
    GSgfxLight();
    void MakeDiff(GSgfxColAu8* color, GSvec* pos, bool infinite);
    void MakeSpec(GSgfxColAu8* color, GSvec* dir, f32 shininess, GSvec* half);
    u32 Load(u8 id);

    void SetColor(GSgfxColAu8* color) {
        m_color.r = color->r;
        m_color.g = color->g;
        m_color.b = color->b;
        m_color.a = color->a;
        m_dirty |= LIGHT_DIRTY_COLOR;
    }
    void SetDir(GSvec* dir) {
        m_dir.x = dir->x;
        m_dir.y = dir->y;
        m_dir.z = dir->z;
        m_dirty |= LIGHT_DIRTY_DIR;
    }
    void SetHalfAngle(GSvec* half) {
        m_attn[0] = half->x;
        m_attn[1] = half->y;
        m_attn[2] = half->z;
        m_dirty |= LIGHT_DIRTY_HALF;
    }
    void SetShininess(f32 shininess) {
        m_attn[3] = shininess;
        m_dirty |= LIGHT_DIRTY_SHININESS;
    }

    u16 m_dirty;
    GSgfxLightType m_type;
    GXColor m_color;
    GSvec m_pos;
    GSvec m_dir;
    f32 m_attn[6];
    GXLightObj m_obj;
    u8 m_id;
};

u32 GSgfxLight::Load(u8 id) {
    u32 mask;

    if (m_dirty & LIGHT_DIRTY_COLOR) {
        GXInitLightColor(&m_obj, m_color);
    }
    switch (m_type) {
    case GS_GFX_LIGHT_SPECULAR:
        if (m_dirty & LIGHT_DIRTY_HALF) {
            GXInitSpecularDirHA(&m_obj, m_dir.x, m_dir.y, m_dir.z, m_attn[0], m_attn[1], m_attn[2]);
        } else if (m_dirty & LIGHT_DIRTY_DIR) {
            GXInitSpecularDir(&m_obj, m_dir.x, m_dir.y, m_dir.z);
        }
        if (m_dirty & LIGHT_DIRTY_SHININESS) {
            GXInitLightAttn(&m_obj, 0.0f, 0.0f, 1.0f, m_attn[3] / 2.0f, 0.0f, 1.0f - m_attn[3] / 2.0f);
        }
        break;
    case GS_GFX_LIGHT_SPOT:
        if (m_dirty & LIGHT_DIRTY_DIR) {
            GXInitLightDir(&m_obj, m_dir.x, m_dir.y, m_dir.z);
        }
        if (m_dirty & LIGHT_DIRTY_SPOT) {
            GXInitLightSpot(&m_obj, m_attn[0], *(GXSpotFn*)&m_attn[1]);
            GXInitLightDistAttn(&m_obj, m_attn[2], m_attn[3], *(GXDistAttnFn*)&m_attn[4]);
        } else if (m_dirty & LIGHT_DIRTY_ATTN) {
            GXInitLightAttn(&m_obj, m_attn[0], m_attn[1], m_attn[2], m_attn[3], m_attn[4], m_attn[5]);
        }
    case GS_GFX_LIGHT_DIFFUSE:
        if (m_dirty & LIGHT_DIRTY_POS) {
            GXInitLightPos(&m_obj, m_pos.x, m_pos.y, m_pos.z);
        }
        break;
    }
    m_dirty = 0;
    m_id = id;
    mask = 1 << id;
    GXLoadLightObjImm(&m_obj, (GXLightID)mask);
    return mask;
}

void GSgfxLight::MakeSpec(GSgfxColAu8* color, GSvec* dir, f32 shininess, GSvec* half) {
    m_dirty = 0;
    m_type = GS_GFX_LIGHT_SPECULAR;
    SetColor(color);
    SetDir(dir);
    SetShininess(shininess);
    if (half != NULL) {
        SetHalfAngle(half);
    }
}

void GSgfxLight::MakeDiff(GSgfxColAu8* color, GSvec* pos, bool infinite) {
    m_dirty = 0;
    m_type = GS_GFX_LIGHT_DIFFUSE;
    SetColor(color);
    if (infinite) {
        GSvec n;
        PSVECNormalize(pos, &n);
        f32 x = n.x;
        f32 y = n.y;
        f32 z = n.z;
        m_pos.x = x;
        m_pos.y = y;
        m_pos.z = z;
        PSVECScale(&m_pos, &m_pos, -1e18f);
    } else {
        m_pos.x = pos->x;
        m_pos.y = pos->y;
        m_pos.z = pos->z;
    }
    m_dirty |= LIGHT_DIRTY_POS;
}

GSgfxLight::GSgfxLight() {
    m_color.r = 0xFF;
    m_color.g = 0xFF;
    m_color.b = 0xFF;
    m_color.a = 0xFF;
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    GXInitLightColor(&m_obj, m_color);
    GXInitLightPos(&m_obj, 0.0f, 0.0f, 0.0f);
    m_type = GS_GFX_LIGHT_DIFFUSE;
    m_dirty = 0;
}
