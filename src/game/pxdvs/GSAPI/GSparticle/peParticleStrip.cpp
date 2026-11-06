#ifndef __MWERKS__
#include <game/psq.h>
#endif
#include <dolphin/types.h>
#include <game/gcdata.h>
#include <game/gsvfarray.h>
#include <game/pecontainer.h>
#include <game/gcfield.h>
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct GSbound;
struct GSgfxDL;
struct GSgfxLayer;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxPrimType { GSgfxPrimType_draft_dummy };
struct GSgfxVF;
typedef f32 Mtx[3][4];
struct Quaternion;
struct Vec;
struct _EmitParams;
struct _peParticleStrip;
struct peColorSpline;
class peContainer;
struct peEmitterNode;
struct peNode;
class peParticleStripContainer;
struct peParticleStripNode;
class peRenderContainer;
struct peSpline;

extern "C++" {
struct GSbound {
    u8 _draft[1];
};
struct GSgfxDL {
    u8 _draft[1];
};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
#ifdef __MWERKS__
    s32 dlDraw(GSgfxDL*);
#else
    void dlDraw(GSgfxDL* p0);
#endif
};
struct GSgfxVF {
    u8 data[0x440];
};
struct Quaternion {
    f32 x, y, z, w;
};
struct Vec {
    f32 x, y, z;
};
struct _EmitParams {
    u8 _draft[1];
};
struct _peParticleStrip {
    u8 _draft[1];
};
struct peColorSpline {
    u8 _draft[1];
};
class peContainer {
public:
    PE_CONTAINER_MEMBERS

    peContainer(peEmitterNode* e, u32 nodeSize, unsigned short max);
    virtual ~peContainer();
    virtual void Start();
    virtual void PreUpdate();
    virtual u16 Emit(unsigned short n) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Stop() = 0;

    static void SetLayerVisibility(GSgfxLayerID, bool);
#ifdef __MWERKS__
    s32 RemoveNode(peNode*);
#else
    void RemoveNode(peNode* node);
#endif
    u16 CreateNodes(unsigned short);
#ifdef __MWERKS__
    s32 RemoveAll();
#else
    void RemoveAll();
#endif
    s32 MoveNode(peNode*, peNode*);
};
class peRenderContainer : public peContainer {
public:
    PE_RENDER_MEMBERS

    peRenderContainer(peEmitterNode*, u32, unsigned short, GSgfxVF*, GSgfxPrimType, unsigned char, unsigned char, bool);
    virtual ~peRenderContainer();
    virtual void PreUpdate();
#ifdef __MWERKS__
    s32 InitSwap();
#else
    void InitSwap();
#endif
#ifdef __MWERKS__
    s32 ResetSwap();
#else
    void ResetSwap();
#endif
#ifdef __MWERKS__
    s32 MarkForSwap();
#else
    void MarkForSwap();
#endif
#ifdef __MWERKS__
    s32 ResolveMultipleSwap();
#else
    void ResolveMultipleSwap();
#endif
};
class peParticleStripContainer : public peRenderContainer {
public:
    PE_STRIP_CONTAINER_MEMBERS
    void hideNode(struct peNodeView* n);
    bool updateNode(struct peNodeView* n, f32 dt);

    peParticleStripContainer(peEmitterNode*, _peParticleStrip*, unsigned short);
    virtual ~peParticleStripContainer();
    virtual void Start();
    virtual u16 Emit(unsigned short);
    virtual void Update(float);
    virtual void Render();
    virtual void Stop();
    void RearrangeIndices();
};
struct peEmitterNode {
    u8 _draft[1];
};
struct peNode {
    u8 _draft[1];
    bool Update(peEmitterNode*, float);
    void Start(peEmitterNode*, _EmitParams*);
};
struct peParticleStripNode {
    u8 _draft[1];
    void UpdateRenderData(peEmitterNode*, _peParticleStrip*, char*, float);
};
struct peSpline {
    u8 _draft[1];
};

extern "C" {
void GSboundAddPoint(GSbound* bound, f32 x, f32 y, f32 z);
void GSgfxVFSetArray(GSgfxVF* vf, s32, s32, void*, s32, s32);
f32 HSD_Randf(void);
asm void PSMTXMultVecSR(const register Mtx m, const register Vec* src, register Vec* dst);
void PSMTXQuat(register Mtx m, const register Quaternion* q);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double fmod(double x, double y);
s32 particleEngineSetupBlendMode(s32);
s32 particleEngineSetupTevStages(s32, u32, u32);
enum GStexFilter { GS_TEXFILTER_NEAR = 0, GS_TEXFILTER_LINEAR = 2 };
void particleEngineSetupTexture(u8, s32, s32, s32, s32, s32);
void peColorSplineGetValue(u8* out, peColorSpline* s, f32 t);
f32 peSplineGetValue(peSpline* s, f32 t);
extern GSbound* g_currentBound;
extern GSgfxLayer* g_current_layer;
extern _EmitParams* g_emitParams;
extern GSgfxVF g_ext_vertex_format;
struct ParticleDebugStats {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
};
extern ParticleDebugStats g_particle_debug_stats;
extern s32 g_render_pass;
extern GSgfxVF g_vertex_format;
extern s32 this_;
}
static inline f32 __peS16tof32(register const s16* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 3 }
#else
    ret = PSQ_LOAD(arg, 0, 3);
#endif
    return ret;
}

static inline f32 peS16tof32(s16 in) {
    s16 tmp = in;
    return __peS16tof32(&tmp);
}

static inline void __peF32tou8(register f32 arg, volatile register u8* out) {
#ifdef __MWERKS__
    asm { psq_st arg, 0(out), 1, 2 }
#else
    PSQ_STORE(out, 0, arg, 2);
#endif
}

static inline u8 peF32tou8(f32 in) {
    u32 out;
    __peF32tou8(in, (u8*)&out);
    return *(u8*)&out;
}

static inline void __peF32tou16(register f32 arg, volatile register u16* out) {
#ifdef __MWERKS__
    asm { psq_st arg, 0(out), 1, 3 }
#else
    PSQ_STORE(out, 0, arg, 3);
#endif
}

static inline u16 peF32tou16(f32 in) {
    u32 out;
    __peF32tou16(in, (u16*)&out);
    return *(u16*)&out;
}

struct peColor {
    u8 r, g, b, a;
};

static inline void peSetKColor(GSgfxLayer* layer, int id, peColor c) {
#ifdef __MWERKS__
    ((u32*)((u8*)layer + 0x14F4))[id] = *(u32*)&c;
#else
    *(u32*)&layer->hw.kcolor[id] = *(u32*)&c;
#endif
    M2C_NAMED(layer, u32 *, 0x16F8, dirty[0].kcolor) |= 1 << id;
    M2C_NAMED(layer, u32 *, 0x16A8, dirty[0].groups) |= 0x10;
    M2C_NAMED(layer, u32 *, 0x17B0, dirty[1].kcolor) |= 1 << id;
    M2C_NAMED(layer, u32 *, 0x1760, dirty[1].groups) |= 0x10;
}

struct peDLView {
    u16 flags;
    u16 stride;
    u8* buf;
    u8 pad8[8];
};

struct peStripRNode {
    u8 pad0[0x20];
    void* slot20;
    u8 pad24[0x4];
    peStripRNode* next;
    void* slot2C;
    u16 index;
    u16 vtx;
};

#pragma optimize_for_size on

void peParticleStripContainer::RearrangeIndices() {
    if (started) {
        u16 vtx = 0;
        u16 nodeIdx = 0;
        u32 flags = GC_AT(u32, data, 0);
        u32 hasColor2 = (flags >> 18) & 1;
        if (count >= 2) {
            f32 scale;
            u8* fc = PE_EMITTER_DEF_M2C(emitter, u8 **);
            if (flags & 0x10000) {
                scale = 1.0f / peS16tof32(count - 1);
            } else {
                scale = GC_AT(f32, fc, 8);
            }
            u32 invert = (flags >> 15) & 1;
            u32 reverse = (flags >> 17) & 1;
            u8 idxMul;
            u8 step;
            u8 stride;
            if (hasColor2) {
                idxMul = 0xC;
                step = 8;
                stride = 0x30;
            } else {
                idxMul = 0xB;
                step = 6;
                stride = 0x2C;
            }
            u8* buf = (&bufA)[cur];
            peDLView* d = (peDLView*)dl[cur];
            for (peStripRNode* node = (peStripRNode*)activeList; node != NULL; node = node->next) {
                f32* v = (f32*)(buf + node->index * stride);
                node->vtx = vtx;
                u16 base = node->index * idxMul;
                u16* idx;
                if (d->flags & 1) {
                    idx = (u16*)(d->buf + 3);
                } else {
                    idx = NULL;
                }
                idx += vtx;
                u16 i = 0;
                if (hasColor2) {
                    for (; i < 2; i++) {
                        idx[0] = base + i * 3;
                        idx[1] = base;
                        idx[2] = base;
                        idx[3] = base + i * 2;
                        idx += 4;
                    }
                } else {
                    for (; i < 2; i++) {
                        idx[0] = base + i * 3;
                        idx[1] = base;
                        idx[2] = base + i * 2;
                        idx += 3;
                    }
                }
                f32 t;
                if (reverse) {
                    t = peS16tof32(count - nodeIdx - 1);
                } else {
                    t = peS16tof32(nodeIdx);
                }
                if (invert) {
                    f32 x = 1.0f - t * scale;
                    v[9] = x;
                    v[7] = x;
                } else {
                    f32 x = t * scale;
                    v[9] = x;
                    v[7] = x;
                }
                vtx += step;
                nodeIdx++;
                v[8] = GC_AT(f32, data, 0x14);
                v[10] = GC_AT(f32, data, 0x18);
            }
            d->flags |= 2;
        }
    }
}

#pragma optimize_for_size reset
}

extern "C++" {
struct peXformP {
    Vec pos;
    Quaternion rot;
    Vec scale;
};
struct peSplineHdr {
    u8 flags;
    gc_bef32 value;
    gc_bef32 time;
};
struct GSColor {
    u8 r, g, b, a;
};

struct peStripDef {
    gc_be32 flags;
    u8 pad4[4];
    gc_ptr32(peColorSpline) color;
    gc_ptr32(peColorSpline) color2;
    gc_ptr32(peSpline) alpha;
};

struct peStripNodeData {
    f32 life0;
    f32 life;
    Vec pos;
    Vec vel;
    peXformP* xform;
    u8 pad24[0x4];
    void* slot28;
    void* slot2C;
    u16 index;
    u8 pad32[2];
    Vec extent;
};

struct peEmitterNodeData {
    u8 pad0[0x20];
    void* slot20;
    u8 pad24[0x4];
    void* slot28;
    void* slot2C;
    u8 pad30[0x8];
    f32 color[4];
};

static inline f32 evalSpline(peSpline* sp, f32 t) {
    peSplineHdr* s = (peSplineHdr*)sp;
    if (s == 0 || (s->flags & 3) == 0) {
        return 1.0f;
    }
    f32 d = s->time - t;
    if (d < 0.0f) {
        d = -d;
    }
    if (d <= 0.00001f) {
        return s->value;
    }
    return peSplineGetValue(sp, t);
}

static inline void rotateBy(Vec* v, Quaternion* q) {
    Mtx m;
    PSMTXQuat(m, q);
    PSMTXMultVecSR(m, v, v);
}

static inline void vecScale(Vec* dst, Vec* a, f32 k) {
    Vec t;
    PSVECScale(a, &t, k);
    f32 z, y, x;
    x = t.x;
    y = t.y;
    z = t.z;
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

static inline void emitPoint(char* out, Vec* v) {
    ((Vec*)out)->x = v->x;
    ((Vec*)out)->y = v->y;
    ((Vec*)out)->z = v->z;
    if (g_currentBound != NULL) {
        GSboundAddPoint(g_currentBound, v->x, v->y, v->z);
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
    return __OSu8tof32(&in);
}

static inline u8 OSf32tou8(register f32 inF) {
    u32 tmp;
    register u32* tmpPtr = &tmp;
    register u8 ret;
#ifdef __MWERKS__
    asm {
        psq_st inF, 0(tmpPtr), 1, 2
        lbz ret, 0(tmpPtr)
    }
#else
    PSQ_STORE(tmpPtr, 0, inF, 2);
    ret = *(u8*)tmpPtr;
#endif
    return ret;
}

struct peNodeView {
    u8 pad0[0x20];
    void* slot20;
    u8 pad24[0x4];
    peNodeView* next;
    void* slot2C;
    u8 pad30[0x2];
    u16 vtx;
};

inline void peParticleStripContainer::hideNode(peNodeView* n) {
    peDLView* d = (peDLView*)dl[cur];
    u16* idx;
    u16 hasColor2 = (GC_AT(u32, data, 0) >> 18) & 1;
    if (d->flags & 1) {
        idx = (u16*)(d->buf + 3);
    } else {
        idx = NULL;
    }
    idx += n->vtx;
    for (u16 i = 2; i-- != 0;) {
        idx[0] = 0xffff;
        idx[1] = 0xffff;
        idx[2] = 0xffff;
        idx += 3;
        if (hasColor2) {
            *idx = 0xffff;
            idx += 1;
        }
    }
    d->flags |= 2;
}

void peParticleStripContainer::Stop() {
    if (started) {
        PreUpdate();
        started = 0;
        u32 flags = GC_AT(u32, data, 0);
        if (flags & 0x400000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, false);
        }
        if (flags & 0x800000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, false);
        }
        if (flags & 0x1000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, false);
        }
        for (peNodeView* n = (peNodeView*)activeList; n != NULL; n = n->next) {
            hideNode(n);
        }
        RemoveAll();
        ResetSwap();
    }
}
}

#define LAYER_FIELD(l, T, off) (*(T*)((u8*)(l) + (off)))
static inline void layerMark(GSgfxLayer* l, u32 sum, u32 off, u32 bit) {
    LAYER_FIELD(l, u32, off) |= bit;
    LAYER_FIELD(l, u32, 0x16A8) |= sum;
    LAYER_FIELD(l, u32, off + 0xB8) |= bit;
    LAYER_FIELD(l, u32, 0x1760) |= sum;
}

static inline bool canRender(peParticleStripContainer* c) {
    if (!c->started) {
        return false;
    }
    u32 flags = GC_AT(u32, c->data, 0);
    if (c->count < 2U) {
        return false;
    }
    if (g_render_pass != 1) {
        return false;
    }
    switch (M2C_NAMED(g_current_layer, s32 *, 0x28, id)) {
    case 0:
        if (flags & 0x100000) {
            return true;
        }
        break;
    case 2:
        if (flags & 0x200000) {
            return true;
        }
        if (!(flags & 0x01F00040)) {
            return true;
        }
        break;
    case 4:
        if (flags & 0x40) {
            return true;
        }
        break;
    case 1:
        if (flags & 0x400000) {
            return true;
        }
        break;
    case 3:
        if (flags & 0x800000) {
            return true;
        }
        break;
    case 5:
        if (flags & 0x01000000) {
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}

static inline void setCull(GSgfxLayer* layer, s32 mode) {
    M2C_NAMED(layer, s32 *, 0xD8C, hw.cullMode) = mode;
    M2C_NAMED(layer, s32 *, 0x16B8, dirty[0].raster) |= 2;
    M2C_NAMED(layer, s32 *, 0x16A8, dirty[0].groups) |= 2;
    M2C_NAMED(layer, s32 *, 0x1770, dirty[1].raster) |= 2;
    M2C_NAMED(layer, s32 *, 0x1760, dirty[1].groups) |= 2;
}

extern "C++" {
void peParticleStripContainer::Render() {
    if (started) {
        if (canRender(this)) {
            ResolveMultipleSwap();
            u32 flags = GC_AT(u32, data, 0);
            u32 tex = (flags >> 18) & 1;
            setCull(g_current_layer, 0);
            particleEngineSetupBlendMode(flags & 7);
            GSgfxVF* vf;
            u8* dlp = dl[cur];
            u8* buf = (&bufA)[cur];
            if (*(u16*)dlp & 1) {
                vf = PE_DL_VF(dlp);
            } else {
                vf = 0;
            }
            if (tex) {
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 9, 3, buf, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xB, 3, buf + 0x18, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xC, 3, buf + 0x2C, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xD, 3, buf + 0x1C, 4, bufSize);
            } else {
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 9, 3, buf, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xB, 3, buf + 0x18, 4, bufSize);
                GSGFX_VF_SET_ARRAY_NATIVE(vf, 0xD, 3, buf + 0x1C, 4, bufSize);
            }
            if (flags & 0x400) {
                gc_bes32* texList;
                u16 frame = unk5C;
                texList = (gc_bes32*)GC_AT(s32*, data, 0x1C);
                if (flags & 0x1000) {
                    f32 count = peS16tof32(*texList);
                    u32 blend = (flags >> 13) & 1;
                    particleEngineSetupTevStages(0, tex, blend);
                    if (blend) {
                        count -= 1.0f;
                    }
                    f32 alpha;
                    f32 t;
                    if (flags & 0x04000000) {
                        t = (count * (GC_AT(f32, PE_EMITTER_DEF_M2C(emitter, u8 **), 0x28) - *(f32*)&unk58)) /
                            GC_AT(f32, data, 4);
                    } else {
                        t = GC_AT(f32, data, 4) *
                            (count * (1.0f - *(f32*)&unk58 / GC_AT(f32, PE_EMITTER_DEF_M2C(emitter, u8 **), 0x28)));
                    }
                    f32 pos = fmod(t + peS16tof32(frame), count);
                    frame = peF32tou16(pos) % (u16)*texList;
                    if (blend) {
                        alpha = pos - peS16tof32(frame);
                        alpha *= 255.0f;
                        u8 a = peF32tou8(alpha);
                        peColor kc;
                        kc.r = kc.g = kc.b = kc.a = a;
                        peSetKColor(g_current_layer, 0, kc);
                        s32 t2 = texList[frame + 2];
                        particleEngineSetupTexture(1, t2, 0, (flags >> 8) & 3,
                                                   (flags & 0x10) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR,
                                                   (flags & 0x20) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR);
                    }
                } else {
                    particleEngineSetupTevStages(0, tex, 0);
                }
                s32 t1 = texList[frame + 1];
                particleEngineSetupTexture(0, t1, 0, (flags >> 8) & 3,
                                           (flags & 0x10) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR,
                                           (flags & 0x20) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR);
            } else {
                particleEngineSetupTevStages(0, tex, 0);
                particleEngineSetupTexture(0, GC_AT(s32, data, 0x1C), 0, (flags >> 8) & 3,
                                           (flags & 0x10) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR,
                                           (flags & 0x20) ? GS_TEXFILTER_LINEAR : GS_TEXFILTER_NEAR);
            }
            g_current_layer->dlDraw((GSgfxDL*)dl[cur]);
            MarkForSwap();
        }
    }
}
}

extern "C++" {
inline bool peParticleStripContainer::updateNode(peNodeView* node, f32 dt) {
    char* buf = (char*)(&bufA)[cur];
    peDLView* d = (peDLView*)dl[cur];
    peStripNodeData* n = (peStripNodeData*)node;
    _peParticleStrip* p = data;
    peEmitterNode* e = emitter;
    if (buf == NULL) {
        return false;
    }
    if ((d->flags & 1) != 1) {
        return false;
    }
    if (!((peNode*)n)->Update(e, dt)) {
        return false;
    }
    ((peParticleStripNode*)n)->UpdateRenderData(e, p, buf, 1.0f - n->life / n->life0);
    return true;
}

void peParticleStripContainer::Update(float dt) {
    if (started) {
        peNodeView* n = (peNodeView*)activeList;
        while (n != NULL) {
            peNodeView* next = n->next;
            if (!updateNode(n, dt)) {
                hideNode(n);
                RemoveNode((peNode*)n);
            }
            n = next;
        }
        *(f32*)&unk58 -= dt;
        RearrangeIndices();
    }
}
}

extern "C++" {
struct peStripDefE {
    gc_be32 flags;
    u8 pad4[0x1c];
    gc_vec(Vec) dir;
    gc_bef32 lenBase;
    gc_bef32 lenRange;
};

struct _EmitParamsS {
    u8 data[0x48];
};

static inline f32 __OSu16tof32S(register const u16* arg) {
    register f32 ret;
#ifdef __MWERKS__
    asm { psq_l ret, 0(arg), 1, 3 }
#else
    ret = PSQ_LOAD(arg, 0, 3);
#endif
    return ret;
}

static inline f32 u16tof32S(u16 v) {
    return __OSu16tof32S(&v);
}

u16 peParticleStripContainer::Emit(unsigned short count) {
    if (!started) {
        return 0;
    }
    u16 left = CreateNodes(count);
    _EmitParamsS* params = (_EmitParamsS*)g_emitParams;
    peNodeView* node = (peNodeView*)activeList;
    peNodeView* next;
    u16 created = left;
    u16 total = left;
    while (left != 0) {
        u8* e = (u8*)emitter;
        next = node->next;
        f32 phase = (PE_EMITTER_DEF_RAW(e, f32**))[2] * u16tof32S(PE_NODE_F(e, u16, 0x4a) + total - left);
        peStripDefE* p = (peStripDefE*)data;
        peDLView* d = (peDLView*)dl[cur];
        if ((d->flags & 1) == 1) {
            peStripNodeData* n = (peStripNodeData*)node;
            ((peNode*)n)->Start(emitter, (_EmitParams*)params);
            if (p->flags & 0x2000000) {
                vecScale(&n->extent, GC_VEC3P(Vec, &p->dir), 10.0f * (phase * p->lenRange + p->lenBase));
            } else {
                f32 r = HSD_Randf();
                vecScale(&n->extent, GC_VEC3P(Vec, &p->dir), 10.0f * (p->lenRange * r + p->lenBase));
            }
            d->flags |= 2;
        }
        node = next;
        left--;
        params++;
    }
    return created;
}
}

extern "C++" {
extern "C++" {
extern "C++" {
void peParticleStripContainer::Start() {
    if (THIS_F(u8 *, 0x19, started) != 0) {
        return;
    }
    THIS_F(u8 *, 0x19, started) = 1;
    u32 flags = *THIS_F(u32 **, 0x54, data);
    InitSwap();
    if (flags & 0x400000) {
        peContainer::SetLayerVisibility((GSgfxLayerID)1, true);
    }
    if (flags & 0x800000) {
        peContainer::SetLayerVisibility((GSgfxLayerID)3, true);
    }
    if (flags & 0x01000000) {
        peContainer::SetLayerVisibility((GSgfxLayerID)5, true);
    }
    if ((flags & 0xC00) == 0xC00) {
        f32 range = u16tof32S(GC_AT(s32, GC_AT(s32*, THIS_F(u8 **, 0x54, data), 0x1C), 0));
        THIS_F(u8 *, 0x5C, unk5C) = OSf32tou8(range * HSD_Randf());
    } else {
        THIS_F(u8 *, 0x5C, unk5C) = 0;
    }
    THIS_F(f32 *, 0x58, unk58) = GC_AT(f32, PE_EMITTER_DEF_M2C(THIS_F(u8 **, 0, emitter), u8 **), 0x28);
}
}

extern "C++" {
peParticleStripContainer::~peParticleStripContainer() {
    g_particle_debug_stats.unk4 -= 0x60;
    g_particle_debug_stats.unk14 -= 0x60;
}
}

extern "C++" {
#pragma push
#pragma dont_inline off
peParticleStripContainer::peParticleStripContainer(peEmitterNode* p0, _peParticleStrip* p1, unsigned short p2)
    : peRenderContainer(p0, PE_NODE_SIZE(0x40, peStripNodeData), p2, (GC_AT(u32, p1, 0) & 0x40000) ? &g_ext_vertex_format : &g_vertex_format, (GSgfxPrimType)0x98, 2,
                        (GC_AT(u32, p1, 0) & 0x40000) ? 0x30 : 0x2C, (GC_AT(u32, p1, 0) >> 19) & 1) {
    peNode* node;
    u16 i;

    data = p1;
    unk5C = 0xFF;
    i = 0;
    for (node = freeList; node != 0; node = PE_NODE_LINK28(node)) {
        PE_NODE_F(node, u16, 0x30) = i;
        PE_NODE_F(node, u16, 0x32) = i;
        i++;
    }
    g_particle_debug_stats.unk4 += 0x60;
    g_particle_debug_stats.unk14 += 0x60;
}
#pragma pop
}

extern "C++" {
void peParticleStripNode::UpdateRenderData(peEmitterNode* emitter, _peParticleStrip* strip, char* out_in, float t) {
    char* out = out_in;
    Vec pos;
    Vec ext;
    Vec half;
    peEmitterNodeData* e = (peEmitterNodeData*)emitter;
    peStripDef* p = (peStripDef*)strip;
    u32 flags = p->flags;
    u32 hasColor2 = (flags >> 18) & 1;
    peStripNodeData* n = (peStripNodeData*)this;

    {
        f32 py = n->pos.y * n->xform->scale.y;
        f32 pz = n->pos.z * n->xform->scale.z;
        f32 px = n->pos.x * n->xform->scale.x;
        pos.x = px;
        pos.y = py;
        pos.z = pz;
    }
    rotateBy(&pos, &n->xform->rot);
    PSVECAdd(&pos, &n->xform->pos, &pos);
    if (hasColor2) {
        out += n->index * 0x30;
    } else {
        out += n->index * 0x2c;
    }
    {
        f32 ey = n->extent.y * n->xform->scale.y;
        f32 ez = n->extent.z * n->xform->scale.z;
        f32 ex = n->extent.x * n->xform->scale.x;
        ext.x = ex;
        ext.y = ey;
        ext.z = ez;
    }
    rotateBy(&ext, &n->xform->rot);
    if (flags & 0x4000) {
        vecScale(&half, &ext, 0.5f);
        PSVECSubtract(&pos, &half, &pos);
    }
    emitPoint(out, &pos);
    PSVECAdd(&pos, &ext, &pos);
    emitPoint(out + 0xc, &pos);
    {
        GSColor c;
        peColorSplineGetValue((u8*)&c, p->color, t);
        c.r = OSf32tou8(e->color[0] * OSu8tof32(c.r));
        c.g = OSf32tou8(e->color[1] * OSu8tof32(c.g));
        c.b = OSf32tou8(e->color[2] * OSu8tof32(c.b));
        c.a = OSf32tou8(255.0f * e->color[3] * evalSpline(p->alpha, t));
        *(u32*)(out + 0x18) = *(u32*)&c;
        if (hasColor2) {
            peColorSplineGetValue((u8*)&c, p->color2, t);
            *(u32*)(out + 0x2c) = *(u32*)&c;
        }
    }
}
}
}
}
