// STATUS: 5/6 exact (all but _lensFlareRender, empty stub; 4.7 KB not started)
#include <dolphin/types.h>
#include <libc/string.h>

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct GStexture;

struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(struct GSgfxLayer* layer, GSgfxLayerPass pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 unk18;
};

class GSgfxLayer {
public:
    void SetLayerVisibility(bool visible);
};

struct Vec {
    f32 x, y, z;
};

struct LensFlareElem {
    u16 id;
    u16 unk2;
    u32 offset;
};

struct LensFlareData {
    u32 magic;
    u16 count;
    u16 elemOffset;
    u32 flags;
};

class LensFlare {
public:
    LensFlare() {
        m_visible = 0;
        m_sun.x = 0.0f;
        m_sun.y = 0.0f;
        m_sun.z = 0.0f;
        m_data = 0;
        m_elems = 0;
    }

    u8 m_visible;
    Vec m_sun;
    f32 m_scale;
    LensFlareData* m_data;
    LensFlareElem* m_elems;
    GStexture* m_textures[64];
};

extern "C" {
GSgfxLayer* GSgfxLayerFindByID(s32 id);
GStexture* GStextureLoad(u32 data);
void GStextureSetFilter(GStexture* tex, s32 minFilter, s32 magFilter, s32);
}
void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);

static void _lensFlareRender(GSgfxLayer* layer, GSgfxLayerPass pass);

static LensFlare* _lfLensFlarePtrs[4];
static bool gModuleInited;

extern "C" {

void GSlensFlareSetVisible(u32 id, bool visible) {
    if (gModuleInited) {
        if (id != 0) {
            u32 idx = id - 1;
            if (_lfLensFlarePtrs[idx] != 0) {
                if (visible != _lfLensFlarePtrs[idx]->m_visible) {
                    _lfLensFlarePtrs[idx]->m_visible = visible;
                    if (_lfLensFlarePtrs[idx]->m_data->flags & 8) {
                        GSgfxLayer* layer = GSgfxLayerFindByID(5);
                        if (layer != 0) {
                            layer->SetLayerVisibility(visible);
                        }
                    }
                }
            }
        }
    }
}

void GSlensFlareSetSunPosition(u32 id, Vec* pos) {
    if (gModuleInited) {
        if (id != 0) {
            u32 idx = id - 1;
            LensFlare* lf = _lfLensFlarePtrs[idx];
            if (lf != 0) {
                lf->m_sun.x = pos->x;
                lf->m_sun.y = pos->y;
                lf->m_sun.z = pos->z;
            }
        }
    }
}

void GSlensFlareFree(u32 id) {
    if (gModuleInited) {
        if (id != 0) {
            LensFlare** slot = &_lfLensFlarePtrs[id - 1];
            if (*slot != 0) {
                delete *slot;
                *slot = 0;
            }
        }
    }
}

u32 GSlensFlareLoad(u8* data) {
    LensFlare* lf;
    u32 i;
    GStexture* tex;
    s32 n;
    LensFlareElem* e;
    if (!gModuleInited) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (_lfLensFlarePtrs[i] == 0) {
            lf = new LensFlare();
            if (lf == 0) {
                lf = 0;
            } else {
                lf->m_data = (LensFlareData*)data;
                if (lf->m_data->magic != 0x7B1EE3F2) {
                    delete lf;
                    lf = 0;
                } else {
                    lf->m_elems = (LensFlareElem*)((u8*)lf->m_data + 0x2c);
                    e = (LensFlareElem*)((u8*)lf->m_elems + (lf->m_data->elemOffset << 4));
                    for (n = 0; n < lf->m_data->count; e++, n++) {
                        e->offset = e->offset + (u32)data;
                        tex = GStextureLoad(e->offset);
                        GStextureSetFilter(tex, 2, 2, 0);
                        if (tex == 0) {
                            delete lf;
                            lf = 0;
                            goto done;
                        }
                        lf->m_textures[e->id] = tex;
                    }
                    lf->m_scale = 1.0f;
                }
            }
        done:
            _lfLensFlarePtrs[i] = lf;
            return (_lfLensFlarePtrs[i] != 0) ? i + 1 : 0;
        }
    }
    return 0;
}

void GSlensFlareInit(void) {
    memset(_lfLensFlarePtrs, 0, sizeof(_lfLensFlarePtrs));
    if (!gModuleInited) {
        GSgfxRenderModule module = {0, 0, _lensFlareRender, 0, 0, 0, 0xB29A48E1};
        GSgfxRenderModuleRegister(0x80, &module, 0);
        gModuleInited = true;
    }
}

}

static void _lensFlareRender(GSgfxLayer* layer, GSgfxLayerPass pass) {
}
