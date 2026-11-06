#ifndef __MWERKS__
#include <game/gcdata.h>
#include <game/psq.h>
#endif
#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gcdata.h>
#include <dolphin/gx/GXVert.h>
#include <libc/string.h>

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct GStexture {
    u8 unk0[7];
    u8 unk7;
};

struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(struct GSgfxLayer* layer, GSgfxLayerPass pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 unk18;
};

struct GSgfxVF;
struct GSlayerCam {
    u32 pad;
    u32* data;
};

struct BlendState {
    u8 pad[0xbc];
};

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void SetLayerVisibility(bool visible);
    void setRenderStateAndSelect(GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

};

struct Vec {
    f32 x, y, z;
};

struct LensFlareElem {
    gc_be16 id;
    gc_be16 unk2;
    gc_be32 offset;
};

struct LensFlareData {
    gc_be32 magic;
    gc_be16 texCount;
    gc_be16 elemCount;
    gc_be32 flags;
    gc_be32 maxDist;
    gc_be32 fadeStart;
    gc_be32 glowStart;
    gc_bef32 glowStrength;
    gc_bef32 glowStrengthBack;
    gc_bef32 sizeRef;
    gc_bef32 minDist;
    gc_bef32 sunRadius;
};

struct LensFlareParam {
    u8 flags;
    u8 pad1;
    gc_be16 tex;
    gc_bef32 pos;
    gc_bef32 size;
    u8 r, g, b, a;
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
    LensFlareParam* m_elems;
    GStexture* m_textures[64];
};

extern "C" {
GSgfxLayer* GSgfxLayerFindByID(GCsptr id);
GStexture* GStextureLoad(u32 data);
void GStextureSetFilter(GStexture* tex, s32 minFilter, s32 magFilter, s32);
}
void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);

static void _lensFlareRender(GSgfxLayer* layer, GSgfxLayerPass pass);
struct GScamera;
struct GSvec : Vec {
    GSvec() {}
    void set(f32 _x, f32 _y, f32 _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};
struct GSmtx44 {
    f32 m[4][4];
};
extern "C" GSmtx44 mtxIdent;
extern "C" {
GScamera* GScameraGetActiveCamera(void);
void* GScameraGetMatrixPtr(GScamera* camera);
void GScameraGetPosition(GScamera* camera, f32* position);
void GScameraLoadActiveCameraMatrix(s32 id);
bool GScolsys2Sun(Vec* start, Vec* end);
bool GScolsys2SunArray(bool* hits, GSvec* start, GSvec* ends, u32 num);
s32 GSgfxProjectFast(const Vec* in, Vec* out);
void GSgfxProjectSetupParameters(void);
GSgfxVF* GSgfxVFGetPredef(s32 id);
void GSmtx44Ortho(f32* mtx, f32, f32, f32, f32, f32, f32);
u16 GStextureGetXsize(GStexture* tex);
u16 GStextureGetYsize(GStexture* tex);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
f32 PSVECMag(const Vec* v);
void PSMTXConcat(const f32 (*a)[4], const f32 (*b)[4], f32 (*ab)[4]);
void PSMTXRotRad(f32 (*m)[4], char axis, f32 rad);
void PSMTXTransApply(const f32 (*src)[4], f32 (*dst)[4], f32 x, f32 y, f32 z);
double atan2(double y, double x);
}

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
                    lf->m_elems = (LensFlareParam*)((u8*)lf->m_data + 0x2c);
                    e = (LensFlareElem*)((u8*)lf->m_elems + (lf->m_data->elemCount << 4));
                    for (n = 0; n < lf->m_data->texCount; e++, n++) {
                        e->offset = e->offset + GC_ADDR32(data);
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

static inline f32 __OSu8tof32(register const u8* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 2 }
#else
    ret = PSQ_LOAD(arg, 0, 2);
#endif
    return ret;
}

static inline f32 OSu8tof32(u8 in) {
    u8 tmp = in;
    return __OSu8tof32(&tmp);
}

static inline f32 __OSu16tof32(register const u16* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 3 }
#else
    ret = PSQ_LOAD(arg, 0, 3);
#endif
    return ret;
}

static inline f32 OSu16tof32(u16 in) {
    u16 tmp = in;
    return __OSu16tof32(&tmp);
}

static inline void __OSf32tou8(register f32 arg, volatile register u8* out) {
#ifdef __MWERKS__
    asm { psq_st arg, 0(out), 1, 2 }
#else
    PSQ_STORE(out, 0, arg, 2);
#endif
}

static inline u8 OSf32tou8(f32 in) {
    u8 out;
    __OSf32tou8(in, &out);
    return out;
}

static inline u8 __OSf32tou8b(register f32 inF) {
    u8 tmp;
    register u8* tmpPtr = &tmp;
#ifdef __MWERKS__
    asm { psq_st inF, 0(tmpPtr), 1, 2 }
#else
    PSQ_STORE(tmpPtr, 0, inF, 2);
#endif
    return *tmpPtr;
}

static inline void OSf32tou8p(f32* in, u8* out) {
    *out = __OSf32tou8b(*in);
}

static inline void _lfSub(GSvec* out, const Vec* sun, const Vec* dir, f32 k) {
    Vec t, u, v;
    PSVECScale(dir, &t, k);
    u = t;
    PSVECSubtract(sun, &u, &v);
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
}

static inline void _lfAdd(GSvec* out, const Vec* sun, const Vec* dir, f32 k) {
    Vec t, u, v;
    PSVECScale(dir, &t, k);
    u = t;
    PSVECAdd(sun, &u, &v);
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
}

#pragma peephole off
static void _lensFlareRender(GSgfxLayer* layer, GSgfxLayerPass pass) {
    u8 projReady = 0;
    u8 orthoReady = 0;
    s32 id = (*(s32*)&layer->id);
    u16 i;
    f32 dist, cx, cy;
    f32 x0, y0, x1, sz;
    f32 fade, bright, refSize, farDist, baseSize, ang;
    if (pass != 1 || (id != 6 && id != 5)) {
        return;
    }
    {
    for (i = 0; i < 4; i++) {
        LensFlare* lf = _lfLensFlarePtrs[i];
        LensFlareData* d;
        GSvec up;
        GSvec right;
        GSvec camPos;
        GSvec scr;
        Vec proj;
        s32 status;
        if (lf == 0) {
            continue;
        }
        if (lf->m_visible == 0) {
            continue;
        }
        d = lf->m_data;
        if ((*(s32*)&layer->type) == 1) {
            if (!(d->flags & 8)) {
                continue;
            }
        }
        if (!projReady) {
            GScamera* cam = GScameraGetActiveCamera();
            f32* m;
            if (cam == 0) {
                return;
            }
            GScameraLoadActiveCameraMatrix(-1);
            m = (f32*)GScameraGetMatrixPtr(cam);
            GScameraGetPosition(cam, (f32*)&camPos);
            cx = 320.0f;
            cy = 240.0f;
            up.set(m[1], m[5], m[9]);
            right.set(m[0], m[4], m[8]);
            GSgfxProjectSetupParameters();
            projReady = 1;
        }
        status = GSgfxProjectFast(&lf->m_sun, &proj);
        if (status == 0) {
            continue;
        }
        scr.x = proj.x - cx;
        scr.y = proj.y - cy;
        scr.z = 0.0f;
        dist = PSVECMag(&scr);
        if (dist > (f32)d->maxDist) {
            continue;
        }
        bright = 1.0f;
        if (d->flags & 0x10) {
            if (d->flags & 0x20) {
                GSvec pts[21];
                bool hits[57];
                f32 step = 0.2f * d->sunRadius;
                u16 j;
                for (j = 0; j < 5; j++) {
                    f32 k = step * OSu16tof32(j);
                    _lfSub(&pts[j], &lf->m_sun, &up, k);
                    _lfAdd(&pts[j + 5], &lf->m_sun, &up, k);
                    _lfSub(&pts[j + 10], &lf->m_sun, &right, k);
                    _lfAdd(&pts[j + 15], &lf->m_sun, &right, k);
                }
                pts[20].x = lf->m_sun.x;
                pts[20].y = lf->m_sun.y;
                pts[20].z = lf->m_sun.z;
                if (GScolsys2SunArray(hits, &camPos, pts, 21) == 1) {
                    bright = hits[20] ? 0.0f : 2.0f;
                    for (j = 0; j < 20; j++) {
                        bright += hits[j] ? 0.0f : 1.0f;
                    }
                    bright /= 22.0f;
                }
            } else {
                if (GScolsys2Sun(&lf->m_sun, &camPos) == 1) {
                    continue;
                }
            }
        }
        if (!orthoReady) {
            f32 mtx[16];
            GScameraLoadActiveCameraMatrix(id);
            GSmtx44Ortho(mtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
            (*(s32*)&layer->hw.projType) = 1;
            ((f32*)layer->hw.proj)[0] = mtx[0];
            ((f32*)layer->hw.proj)[1] = mtx[3];
            ((f32*)layer->hw.proj)[2] = mtx[5];
            ((f32*)layer->hw.proj)[3] = mtx[7];
            ((f32*)layer->hw.proj)[4] = mtx[10];
            ((f32*)layer->hw.proj)[5] = mtx[11];
            GSlayerCam* cam = (*(GSlayerCam**)&layer->matrixStack);
            memcpy(cam->data + 1, &mtxIdent, 0x30);
            cam->data[0] |= 1;
            (*(f32*)&layer->hw.fogNear) = 0.0f;
            (*(f32*)&layer->hw.fogFar) = 30000.0f;
            if ((*(u8*)&layer->hw.fogEnable)) {
                if ((*(u8*)&layer->hw.fogRangeEnable)) {
                    (*(u32*)&layer->dirty[0].pe) |= 0x100;
                    (*(u32*)&layer->dirty[1].pe) |= 0x100;
                }
                (*(u32*)&layer->dirty[0].pe) |= 0x40;
                (*(u32*)&layer->dirty[0].groups) |= 0x40;
                (*(u32*)&layer->dirty[1].pe) |= 0x40;
                (*(u32*)&layer->dirty[1].groups) |= 0x40;
            }
            (*(u32*)&layer->dirty[0].geom) |= 0x20;
            (*(u32*)&layer->dirty[0].groups) |= 1;
            (*(u32*)&layer->dirty[1].geom) |= 0x20;
            (*(u32*)&layer->dirty[1].groups) |= 1;
            (*(u8*)&layer->hw.colorUpdate) = 1;
            (*(u8*)&layer->hw.alphaUpdate) = 1;
            (*(u8*)&layer->hw.zUpdate) = 0;
            (*(u32*)&layer->dirty[0].pe) |= 4;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 4;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(u8*)&layer->hw.zEnable) = 0;
            (*(s32*)&layer->hw.zFunc) = 3;
            (*(u32*)&layer->dirty[0].pe) |= 8;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 8;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(s32*)&layer->hw.cullMode) = 2;
            (*(u32*)&layer->dirty[0].raster) |= 2;
            (*(u32*)&layer->dirty[0].groups) |= 2;
            (*(u32*)&layer->dirty[1].raster) |= 2;
            (*(u32*)&layer->dirty[1].groups) |= 2;
            (*(u32*)&layer->unk1998) = 0x98;
            if ((*(s32*)&layer->curPass) != 1) {
                (*(s32*)&layer->curPass) = 1;
                layer->curFifo = &layer->passes[layer->curPass];
            }
            (*(s32*)&layer->hw.blend[0]) = 1;
            (*(s32*)&layer->hw.blend[1]) = 4;
            (*(s32*)&layer->hw.blend[2]) = 1;
            (*(s32*)&layer->hw.blend[3]) = 5;
            (*(u32*)&layer->dirty[0].pe) |= 1;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 1;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            orthoReady = 1;
        }
        if (status == 2) {
            refSize = 1.0f;
            LensFlareParam* e = lf->m_elems;
            s32 n = d->elemCount;
            bool anchored;
            n = d->elemCount;
            while (n != 0) {
                n--;
                if (e->flags & 1) {
                    refSize = e->size;
                    break;
                }
                e++;
            }
            farDist = dist;
            if (dist < d->minDist) {
                farDist = d->minDist;
            }
            if (dist < (f32)d->fadeStart) {
                fade = 1.0f;
            } else {
                fade = ((f32)(d->maxDist - d->fadeStart) - (dist - (f32)d->fadeStart)) / (f32)(d->maxDist - d->fadeStart);
                if (fade < 0.0f) {
                    fade = 0.0f;
                } else if (fade > 1.0f) {
                    fade = 1.0f;
                }
            }
            baseSize = d->sizeRef;
            anchored = d->flags & 1;
            layer->setRenderStateAndSelect(GSgfxVFGetPredef(5));
            e = lf->m_elems;
            n = d->elemCount;
            while (n-- != 0) {
                GSlayerCam* cam;
                GStexture* tex;
                u8 cr, cg, cb, ca;
                if ((*(s32*)&layer->type) == 1 && !(e->flags & 2)) {
                    e++;
                    continue;
                }
                cam = (*(GSlayerCam**)&layer->matrixStack);
                tex = lf->m_textures[e->tex];
                memcpy(cam->data + 1, &mtxIdent, 0x30);
                cam->data[0] |= 1;
                sz = e->size;
                if (e->flags & 1) {
                    GSlayerCam* c2 = (*(GSlayerCam**)&layer->matrixStack);
                    PSMTXTransApply((f32(*)[4])(c2->data + 1), (f32(*)[4])(c2->data + 1), proj.x, proj.y, 0.0f);
                    c2->data[0] |= 1;
                } else {
                    Vec off;
                    GSlayerCam* c2;
                    PSVECScale(&scr, &off, 1.0f / e->pos);
                    if (anchored) {
                        f32 t;
                        if (e->pos > 0.0f && e->pos < 1.0f) {
                            t = 1.0f / e->pos - 1.0f;
                        } else {
                            t = 1.0f - 1.0f / e->pos;
                        }
                        f32 adj = t * (800.0f / farDist) * (baseSize / refSize - 1.0f);
                        sz *= 1.0f + adj;
                    } else {
                        sz *= 1.0f + (baseSize - 1.0f) * PSVECMag(&off) / 800.0f;
                    }
                    c2 = (*(GSlayerCam**)&layer->matrixStack);
                    PSMTXTransApply((f32(*)[4])(c2->data + 1), (f32(*)[4])(c2->data + 1), off.x + cx, off.y + cy, 0.0f);
                    c2->data[0] |= 1;
                }
                x0 = -(sz * (f32)(GStextureGetXsize(tex) >> 1));
                y0 = -(sz * (f32)(GStextureGetYsize(tex) >> 1));
                x1 = sz * (f32)(GStextureGetXsize(tex) >> 1);
                sz = sz * (f32)(GStextureGetYsize(tex) >> 1);
                if (d->flags & 2) {
                    if (d->flags & 4) {
                        f32 m[12];
                        ang = (f32)atan2(scr.y, scr.x);
                        cam = (*(GSlayerCam**)&layer->matrixStack);
                        PSMTXRotRad((f32(*)[4])m, 'X', 0.0f);
                        PSMTXConcat((f32(*)[4])(cam->data + 1), (f32(*)[4])m, (f32(*)[4])(cam->data + 1));
                        PSMTXRotRad((f32(*)[4])m, 'Y', 0.0f);
                        PSMTXConcat((f32(*)[4])(cam->data + 1), (f32(*)[4])m, (f32(*)[4])(cam->data + 1));
                        PSMTXRotRad((f32(*)[4])m, 'Z', -ang);
                        PSMTXConcat((f32(*)[4])(cam->data + 1), (f32(*)[4])m, (f32(*)[4])(cam->data + 1));
                        cam->data[0] |= 1;
                    } else {
                        f32 m2[12];
                        ang = (f32)atan2(scr.y, scr.x);
                        cam = (*(GSlayerCam**)&layer->matrixStack);
                        PSMTXRotRad((f32(*)[4])m2, 'X', 0.0f);
                        PSMTXConcat((f32(*)[4])(cam->data + 1), (f32(*)[4])m2, (f32(*)[4])(cam->data + 1));
                        PSMTXRotRad((f32(*)[4])m2, 'Y', 0.0f);
                        PSMTXConcat((f32(*)[4])(cam->data + 1), (f32(*)[4])m2, (f32(*)[4])(cam->data + 1));
                        PSMTXRotRad((f32(*)[4])m2, 'Z', ang);
                        PSMTXConcat((f32(*)[4])(cam->data + 1), (f32(*)[4])m2, (f32(*)[4])(cam->data + 1));
                        cam->data[0] |= 1;
                    }
                }
                cr = OSf32tou8(fade * OSu8tof32(e->r));
                cg = OSf32tou8(fade * OSu8tof32(e->g));
                cb = OSf32tou8(fade * OSu8tof32(e->b));
                ca = OSf32tou8(bright * (lf->m_scale * (fade * OSu8tof32(e->a))) + 0.5f);
                if ((*(GStexture**)&layer->dirty[0].tex[0]) != tex || (*(GStexture**)&layer->dirty[1].tex[0]) != tex || tex->unk7 != 0) {
                    (*(GStexture**)&layer->dirty[0].tex[0]) = tex;
                    (*(u32*)&layer->dirty[0].texMask) |= 1;
                    (*(GStexture**)&layer->dirty[1].tex[0]) = tex;
                    (*(u32*)&layer->dirty[1].texMask) |= 1;
                }
                layer->beginSurface(4);
                {
                    f32 zero = 0.0f;
                    f32 one = 1.0f;
                    GXWGFifo.f32 = x0; GXWGFifo.f32 = y0; GXWGFifo.f32 = zero;
                    GXWGFifo.u8 = cr; GXWGFifo.u8 = cg; GXWGFifo.u8 = cb; GXWGFifo.u8 = ca;
                    GXWGFifo.f32 = zero; GXWGFifo.f32 = zero;
                    GXWGFifo.f32 = x1; GXWGFifo.f32 = y0; GXWGFifo.f32 = zero;
                    GXWGFifo.u8 = cr; GXWGFifo.u8 = cg; GXWGFifo.u8 = cb; GXWGFifo.u8 = ca;
                    GXWGFifo.f32 = one; GXWGFifo.f32 = zero;
                    GXWGFifo.f32 = x0; GXWGFifo.f32 = sz; GXWGFifo.f32 = zero;
                    GXWGFifo.u8 = cr; GXWGFifo.u8 = cg; GXWGFifo.u8 = cb; GXWGFifo.u8 = ca;
                    GXWGFifo.f32 = zero; GXWGFifo.f32 = one;
                    GXWGFifo.f32 = x1; GXWGFifo.f32 = sz; GXWGFifo.f32 = zero;
                    GXWGFifo.u8 = cr; GXWGFifo.u8 = cg; GXWGFifo.u8 = cb; GXWGFifo.u8 = ca;
                    GXWGFifo.f32 = one; GXWGFifo.f32 = one;
                }
                layer->endSurface();
                e++;
            }
            if ((*(s32*)&layer->type) == 0) {
                if (dist < (f32)d->fadeStart) {
                    f32 glow;
                    if (dist < (f32)d->glowStart) {
                        glow = d->glowStrength;
                    } else {
                        glow = d->glowStrength * (((f32)(d->fadeStart - d->glowStart) - (dist - (f32)d->glowStart)) / (f32)(d->fadeStart - d->glowStart));
                        if (glow < 0.0f) {
                            glow = 0.0f;
                        } else if (glow > 1.0f) {
                            glow = 1.0f;
                        }
                    }
                    {
    s32 ga = (s32)(255.0f * glow);
    GSlayerCam* cam;
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
    cam = (*(GSlayerCam**)&layer->matrixStack);
    memcpy(cam->data + 1, &mtxIdent, 0x30);
    cam->data[0] |= 1;
    layer->beginSurface(4);
    {
        f32 zero = 0.0f;
        f32 w = 640.0f;
        f32 h = 480.0f;
        u8 a0, a1, a2, a3;
        GXWGFifo.f32 = zero; GXWGFifo.f32 = zero; GXWGFifo.f32 = zero;
        a0 = OSf32tou8(255.0f * lf->m_scale * bright + 0.5f);
        GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = a0;
        GXWGFifo.f32 = w; GXWGFifo.f32 = zero; GXWGFifo.f32 = zero;
        a1 = OSf32tou8(255.0f * lf->m_scale * bright + 0.5f);
        GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = a1;
        GXWGFifo.f32 = zero; GXWGFifo.f32 = h; GXWGFifo.f32 = zero;
        a2 = OSf32tou8(255.0f * lf->m_scale * bright + 0.5f);
        GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = a2;
        GXWGFifo.f32 = w; GXWGFifo.f32 = h; GXWGFifo.f32 = zero;
        a3 = OSf32tou8(255.0f * lf->m_scale * bright + 0.5f);
        GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = a3;
    }
    layer->endSurface();
                    }
                }
            }
        } else if ((*(s32*)&layer->type) == 0) {
            f32 glow;
            PSVECSubtract(&camPos, &lf->m_sun, &scr);
            PSVECAdd(&camPos, &scr, &scr);
            if (GSgfxProjectFast(&scr, &proj) == 2) {
                scr.x = proj.x - cx;
                scr.y = proj.y - cy;
                scr.z = 0.0f;
                dist = PSVECMag(&scr);
                if (dist > 0.00001f && dist < (f32)d->maxDist && dist < (f32)d->fadeStart) {
                    if (dist < (f32)d->glowStart) {
                        glow = d->glowStrengthBack;
                    } else {
                        glow = d->glowStrengthBack * (((f32)(d->fadeStart - d->glowStart) - (dist - (f32)d->glowStart)) / (f32)(d->fadeStart - d->glowStart));
                        if (glow < 0.0f) {
                            glow = 0.0f;
                        } else if (glow > 1.0f) {
                            glow = 1.0f;
                        }
                    }
                    {
    s32 ga = (s32)(255.0f * glow);
    GSlayerCam* cam;
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
    cam = (*(GSlayerCam**)&layer->matrixStack);
    memcpy(cam->data + 1, &mtxIdent, 0x30);
    cam->data[0] |= 1;
    layer->beginSurface(4);
    {
        f32 zero = 0.0f;
        f32 w = 640.0f;
        f32 h = 480.0f;
        u8 a0, a1, a2, a3;
        GXWGFifo.f32 = zero; GXWGFifo.f32 = zero; GXWGFifo.f32 = zero;
        a0 = OSf32tou8(255.0f * lf->m_scale * bright + 0.5f);
        GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = a0;
        GXWGFifo.f32 = w; GXWGFifo.f32 = zero; GXWGFifo.f32 = zero;
        a1 = OSf32tou8(255.0f * lf->m_scale * bright + 0.5f);
        GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = a1;
        GXWGFifo.f32 = zero; GXWGFifo.f32 = h; GXWGFifo.f32 = zero;
        a2 = OSf32tou8(255.0f * lf->m_scale * bright + 0.5f);
        GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = a2;
        GXWGFifo.f32 = w; GXWGFifo.f32 = h; GXWGFifo.f32 = zero;
        a3 = OSf32tou8(255.0f * lf->m_scale * bright + 0.5f);
        GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = ga; GXWGFifo.u8 = a3;
    }
    layer->endSurface();
                    }
                }
            }
        }
    }
    }
}
#pragma peephole reset
