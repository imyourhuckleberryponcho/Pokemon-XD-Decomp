#include <dolphin/types.h>
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
struct GSgfxLayer {
    u8 _draft[1];
    s32 dlDraw(GSgfxDL*);
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
    peEmitterNode* emitter;
    u32 unk4;
    void* buffer;
    peNode* freeList;
    peNode* activeList;
    u16 count;
    u16 maxCount;
    u8 dirty;
    u8 started;

    peContainer(peEmitterNode* e, unsigned long nodeSize, unsigned short max);
    virtual ~peContainer();
    virtual void Start();
    virtual void PreUpdate();
    virtual u16 Emit(unsigned short n) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Stop() = 0;

    static void SetLayerVisibility(GSgfxLayerID, bool);
    s32 RemoveNode(peNode*);
    u16 CreateNodes(unsigned short);
    s32 RemoveAll();
    s32 MoveNode(peNode*, peNode*);
};
class peRenderContainer : public peContainer {
public:
    u8 swapPending;
    u8 cur;
    u32 bufSize;
    u8 dl[2][0x10];
    u8* bufA;
    u8* bufB;
    u16 tokens[2];

    peRenderContainer(peEmitterNode*, unsigned long, unsigned short, GSgfxVF*, GSgfxPrimType, unsigned char, unsigned char, bool);
    virtual ~peRenderContainer();
    virtual void PreUpdate();
    s32 InitSwap();
    s32 ResetSwap();
    s32 MarkForSwap();
    s32 ResolveMultipleSwap();
};
class peParticleStripContainer : public peRenderContainer {
public:
    void hideNode(struct peNodeView* n);
    bool updateNode(struct peNodeView* n, f32 dt);
    _peParticleStrip* data;
    u32 unk58;
    u8 unk5C;

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
s32 particleEngineSetupTexture(s32, s32*, s32, s32, s32, s32);
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
#pragma optimize_for_size on

void peParticleStripContainer::RearrangeIndices() {
    u8 *temp_r9_2;
    u8 *var_r6;
    s16 spA;
    volatile s16 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f1;
    f32 var_f2;
    s16 var_r7;
    u32 temp_r12;
    s32 temp_r28;
    s32 temp_r28_2;
    s32 temp_r29_2;
    s32 temp_r29_3;
    s32 var_r26;
    s32 var_r24;
    u8 *temp_r30;
    s32 temp_r29;
    s16 var_r8;
    u32 temp_r6;
    u8 temp_r9;
    u8 var_r0;
    u16 var_r24_2;
    u8 var_r4;
    u16 temp_r5;
    u8 *var_r26_2;
    s16 spC;

    if (M2C_FIELD(this, u8 *, 0x19) != 0) {
        var_r7 = 0;
        temp_r5 = M2C_FIELD(this, u16 *, 0x14);
        var_r8 = 0;
        temp_r6 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), u32 *, 0);
        temp_r12 = (temp_r6 >> 0x12U) & 1;
        if (temp_r5 >= 2U) {
            if (temp_r6 & 0x10000) {
                spC = temp_r5 - 1;
                var_f1 = 1.0f / M2C_ERROR( );
            } else {
                var_f1 = M2C_FIELD(M2C_FIELD(M2C_FIELD(this, u8 **, 0), u8 **, 0xFC), f32 *, 8);
            }
            if (temp_r12 != 0) {
                var_r0 = 0x30;
                var_r24 = 8;
                var_r4 = 0xC;
            } else {
                var_r0 = 0x2C;
                var_r24 = 6;
                var_r4 = 0xB;
            }
            temp_r9 = M2C_FIELD(this, u8 *, 0x21);
            var_r6 = M2C_FIELD(this, u8 **, 0x10);
            temp_r30 = (unsigned char *)((u8*)this + ((temp_r9 * 0x10) + 0x28));
            while (var_r6 != NULL) {
                temp_r29 = M2C_FIELD(var_r6, u16 *, 0x30) * var_r4;
                M2C_FIELD(var_r6, s16 *, 0x32) = var_r7;
                temp_r9_2 = (unsigned char *)(M2C_FIELD(((u8*)this + (temp_r9 * 4)), s32 *, 0x48) + (M2C_FIELD(var_r6, u16 *, 0x30) * var_r0));
                if (M2C_FIELD(temp_r30, u16 *, 0) & 1) {
                    var_r26 = M2C_FIELD(temp_r30, s32 *, 4) + 3;
                } else {
                    var_r26 = 0;
                }
                var_r24_2 = 0;
                var_r26_2 = (unsigned char *)(var_r26 + ((var_r7 * 2) & 0x1FFFE));
                if (temp_r12 != 0) {
                    while (var_r24_2 < 2U) {
                        temp_r28 = var_r24_2 * 3;
                        temp_r29_2 = (var_r24_2 * 2) & 0x1FFFE;
                        var_r24_2 += 1;
                        M2C_FIELD(var_r26_2, s16 *, 0) = (s16) (temp_r28 + temp_r29);
                        M2C_FIELD(var_r26_2, u16 *, 2) = temp_r29;
                        M2C_FIELD(var_r26_2, s16 *, 6) = (s16) (temp_r29_2 + temp_r29);
                        M2C_FIELD(var_r26_2, u16 *, 4) = temp_r29;
                        var_r26_2 += 8;
                    }
                } else {
                    while (var_r24_2 < 2U) {
                        temp_r29_3 = (var_r24_2 * 2) & 0x1FFFE;
                        temp_r28_2 = var_r24_2 * 3;
                        var_r24_2 += 1;
                        M2C_FIELD(var_r26_2, s16 *, 0) = (s16) (temp_r29 + temp_r28_2);
                        M2C_FIELD(var_r26_2, s16 *, 4) = (s16) (temp_r29_3 + temp_r29);
                        M2C_FIELD(var_r26_2, u16 *, 2) = temp_r29;
                        var_r26_2 += 6;
                    }
                }
                if ((u32) ((temp_r6 >> 0x11U) & 1) != 0) {
                    spA = (M2C_FIELD(this, u16 *, 0x14) - var_r8) - 1;
                    var_f2 = M2C_ERROR( );
                } else {
                    sp8 = var_r8;
                    var_f2 = M2C_ERROR( );
                }
                if ((u32) ((temp_r6 >> 0xFU) & 1) != 0) {
                    temp_f0 = -((var_f2 * var_f1) - 1.0f);
                    M2C_FIELD(temp_r9_2, f32 *, 0x24) = temp_f0;
                    M2C_FIELD(temp_r9_2, f32 *, 0x1C) = temp_f0;
                } else {
                    temp_f0_2 = var_f2 * var_f1;
                    M2C_FIELD(temp_r9_2, f32 *, 0x24) = temp_f0_2;
                    M2C_FIELD(temp_r9_2, f32 *, 0x1C) = temp_f0_2;
                }
                var_r7 += var_r24;
                var_r8 += 1;
                M2C_FIELD(temp_r9_2, f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), f32 *, 0x14);
                M2C_FIELD(temp_r9_2, f32 *, 0x28) = (f32) M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), f32 *, 0x18);
                var_r6 = M2C_FIELD(var_r6, u8 **, 0x28);
            }
            M2C_FIELD(temp_r30, u16 *, 0) = (u16) (M2C_FIELD(temp_r30, u16 *, 0) | 2);
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
    f32 value;
    f32 time;
};
struct GSColor {
    u8 r, g, b, a;
};

struct peStripDef {
    u32 flags;
    u8 pad4[4];
    peColorSpline* color;
    peColorSpline* color2;
    peSpline* alpha;
};

struct peStripNodeData {
    f32 life0;
    f32 life;
    Vec pos;
    Vec vel;
    peXformP* xform;
    u8 pad24[0xc];
    u16 index;
    u8 pad32[2];
    Vec extent;
};

struct peEmitterNodeData {
    u8 pad0[0x38];
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
    *dst = t;
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
    asm { psq_l ret, 0(arg), 1, 2 }
    return ret;
}

static inline f32 OSu8tof32(u8 in) {
    return __OSu8tof32(&in);
}

static inline u8 OSf32tou8(register f32 inF) {
    u8 out;
    u8* outP = &out;
    register u8* ptr = outP;
    asm { psq_st inF, 0(ptr), 1, 2 }
    return *ptr;
}

struct peDLView {
    u16 flags;
    u16 stride;
    u8* buf;
    u8 pad8[8];
};

struct peNodeView {
    u8 pad0[0x28];
    peNodeView* next;
    u8 pad2c[6];
    u16 vtx;
};

inline void peParticleStripContainer::hideNode(peNodeView* n) {
    peDLView* d = (peDLView*)dl[cur];
    u16* idx;
    u32 hasColor2 = (*(u32*)data >> 18) & 1;
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
        u32 flags = *(u32*)data;
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
    if (!M2C_FIELD(c, u8 *, 0x19)) {
        return false;
    }
    u32 flags = M2C_FIELD(M2C_FIELD(c, u8 **, 0x54), u32 *, 0);
    if (M2C_FIELD(c, u16 *, 0x14) < 2U) {
        return false;
    }
    if (g_render_pass != 1) {
        return false;
    }
    switch (M2C_FIELD(g_current_layer, s32 *, 0x28)) {
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

extern "C++" {
void peParticleStripContainer::Render() {
    u32 temp_r31;
    u32 temp_r30;
    volatile s32 sp14;
    u8 sp1F;
    u8 sp1E;
    u8 sp1D;
    volatile u8 sp1C;
    s32 sp18;
    s16 spC;
    s16 spA;
    u16 sp8;
    GSgfxVF *var_r28;
    f32 temp_f30;
    volatile f32 var_f1;
    f32 var_f29;
    s32 *temp_r29_2;
    u8 var_r28_2;
    s32 temp_r0;
    s32 var_r7;
    s32 var_r7_2;
    s32 var_r7_3;
    s32 var_r8;
    s32 var_r8_2;
    s32 var_r8_3;
    u32 temp_r26;
    s32 sp10;
    u32 temp_r4;
    s32 temp_r0_2;
    u8 var_r0;
    s32 temp_cr0_eq;
    u8 *temp_r29;
    u8 *temp_r4_2;

    if (M2C_FIELD(this, u8 *, 0x19)) {
        if (canRender(this)) {
            ((peRenderContainer*)((peRenderContainer *) this))->ResolveMultipleSwap();
            temp_r31 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), u32 *, 0);
            M2C_FIELD(g_current_layer, s32 *, 0xD8C) = 0;
            temp_r30 = (temp_r31 >> 0x12U) & 1;
            {
                GSgfxLayer* l = g_current_layer;
                layerMark(l, 2, 0x16B8, 2);
            }
            particleEngineSetupBlendMode(temp_r31 & 7);
            temp_r29 = M2C_FIELD(((u8*)this + (temp_r0_2 * 4)), u8 **, 0x48);
            temp_r0_2 = M2C_FIELD(this, u8 *, 0x21);
            temp_r4_2 = (unsigned char *)((u8*)this + ((temp_r0_2 * 0x10) + 0x28));
            if (M2C_FIELD(temp_r4_2, u16 *, 0) & 1) {
                var_r28 = M2C_FIELD(temp_r4_2, GSgfxVF **, 0xC);
            } else {
                var_r28 = NULL;
            }
            if (temp_r30 != 0) {
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 9, 3, (void*)(temp_r29), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xB, 3, (void*)(temp_r29 + 0x18), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xC, 3, (void*)(temp_r29 + 0x2C), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xD, 3, (void*)(temp_r29 + 0x1C), 4, M2C_FIELD(this, s32 *, 0x24));
            } else {
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 9, 3, (void*)(temp_r29), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xB, 3, (void*)(temp_r29 + 0x18), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xD, 3, (void*)(temp_r29 + 0x1C), 4, M2C_FIELD(this, s32 *, 0x24));
            }
            if (temp_r31 & 0x400) {
                var_r28_2 = M2C_FIELD(this, u8 *, 0x5C);
                temp_r29_2 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), s32 **, 0x1C);
                if (temp_r31 & 0x1000) {
                    spC = (s16) *temp_r29_2;
                    var_f29 = M2C_ERROR( );
                    temp_r26 = (temp_r31 >> 0xDU) & 1;
                    particleEngineSetupTevStages(0, temp_r30, temp_r26);
                    if (temp_r26 != 0) {
                        var_f29 -= 1.0f;
                    }
                    if (temp_r31 & 0x04000000) {
                        var_f1 = (var_f29 * (M2C_FIELD(M2C_FIELD(M2C_FIELD(this, u8 **, 0), u8 **, 0xFC), f32 *, 0x28) - M2C_FIELD(this, f32 *, 0x58))) / M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), f32 *, 4);
                    } else {
                        var_f1 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), f32 *, 4) * (var_f29 * (1.0f - (M2C_FIELD(this, f32 *, 0x58) / M2C_FIELD(M2C_FIELD(M2C_FIELD(this, u8 **, 0), u8 **, 0xFC), f32 *, 0x28))));
                    }
                    spA = (s16) var_r28_2;
                    temp_f30 = (f32) fmod((f64) (var_f1 + M2C_ERROR( )), (f64) var_f29);
                    var_r28_2 = (u8) (u16) (sp14 % (u16) *temp_r29_2);
                    if (temp_r26 != 0) {
                        sp8 = (u16) var_r28_2;
                        var_r8 = 0;
                        sp1F = sp10;
                        sp1E = sp10;
                        sp1D = sp10;
                        sp1C = sp10;
                        M2C_FIELD(g_current_layer, s32 *, 0x14F4) = (s32) sp1C;
                        sp18 = (s32) sp1C;
                        {
                            GSgfxLayer* l = g_current_layer;
                            layerMark(l, 0x10, 0x16F8, 1);
                        }
                        var_r8 = !(temp_r31 & 0x20) ? var_r8 : 2;
                        var_r7 = 0;
                        if (temp_r31 & 0x10) {
                            var_r7 = 2;
                        }
                        particleEngineSetupTexture(1, M2C_FIELD((temp_r29_2 + ((var_r28_2 * 4) & 0x3FFFC)), s32 **, 8), 0, (temp_r31 >> 8U) & 3, var_r7, var_r8);
                    }
                } else {
                    particleEngineSetupTevStages(0, temp_r30, 0U);
                }
                var_r8_2 = 0;
                var_r8_2 = !(temp_r31 & 0x20) ? var_r8_2 : 2;
                var_r7_2 = 0;
                if (temp_r31 & 0x10) {
                    var_r7_2 = 2;
                }
                particleEngineSetupTexture(0, M2C_FIELD((temp_r29_2 + ((var_r28_2 * 4) & 0x3FFFC)), s32 **, 4), 0, (temp_r31 >> 8U) & 3, var_r7_2, var_r8_2);
            } else {
                particleEngineSetupTevStages(0, temp_r30, 0U);
                var_r8_3 = 0;
                if (temp_r31 & 0x20) {
                    var_r8_3 = 2;
                }
                var_r7_3 = 0;
                if (temp_r31 & 0x10) {
                    var_r7_3 = 2;
                }
                particleEngineSetupTexture(0, M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), s32 **, 0x1C), 0, (temp_r31 >> 8U) & 3, var_r7_3, var_r8_3);
            }
            ((GSgfxLayer*)(g_current_layer))->dlDraw((GSgfxDL*)((u8*)this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28)));
            ((peRenderContainer*)((peRenderContainer *) this))->MarkForSwap();
        }
    }
}
}

extern "C++" {
inline bool peParticleStripContainer::updateNode(peNodeView* node, f32 dt) {
    peStripNodeData* n = (peStripNodeData*)node;
    _peParticleStrip* p = data;
    peEmitterNode* e = emitter;
    char* buf = (char*)(&bufA)[cur];
    if (buf == NULL) {
        return false;
    }
    if ((((peDLView*)dl[cur])->flags & 1) != 1) {
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
    u32 flags;
    u8 pad4[0x1c];
    Vec dir;
    f32 lenBase;
    f32 lenRange;
};

struct _EmitParamsS {
    u8 data[0x48];
};

static inline f32 __OSu16tof32S(register const u16* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 3 }
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
        f32 phase = (*(f32**)(e + 0xfc))[2] * u16tof32S(*(u16*)(e + 0x4a) + total - left);
        peStripDefE* p = (peStripDefE*)data;
        peDLView* d = (peDLView*)dl[cur];
        if ((d->flags & 1) == 1) {
            peStripNodeData* n = (peStripNodeData*)node;
            ((peNode*)n)->Start(emitter, (_EmitParams*)params);
            if (p->flags & 0x2000000) {
                vecScale(&n->extent, &p->dir, 10.0f * (phase * p->lenRange + p->lenBase));
            } else {
                vecScale(&n->extent, &p->dir, 10.0f * (HSD_Randf() * p->lenRange + p->lenBase));
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
    volatile s32 spC;
    volatile s16 sp8;
    s32 temp_r31;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        M2C_FIELD(this, u8 *, 0x19) = 1U;
        temp_r31 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), s32 *, 0);
        ((peRenderContainer*)((peRenderContainer *) this))->InitSwap();
        if (temp_r31 & 0x400000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)1, true);
        }
        if (temp_r31 & 0x800000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)3, true);
        }
        if (temp_r31 & 0x01000000) {
            peContainer::SetLayerVisibility((GSgfxLayerID)5, true);
        }
        if ((u32) (temp_r31 & 0xC00) == 0xC00) {
            sp8 = (s16) *M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), s32 **, 0x1C);
            HSD_Randf();
            M2C_FIELD((u16)this, u8 *, 0x5C) = spC;
        } else {
            M2C_FIELD(this, u8 *, 0x5C) = 0U;
        }
        M2C_FIELD(this, f32 *, 0x58) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(this, u8 **, 0), u8 **, 0xFC), f32 *, 0x28);
    }
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
    : peRenderContainer(p0, 0x40, p2, (*(u32*)p1 & 0x40000) ? &g_ext_vertex_format : &g_vertex_format, (GSgfxPrimType)0x98, 2,
                        (*(u32*)p1 & 0x40000) ? 0x30 : 0x2C, (*(u32*)p1 >> 19) & 1) {
    peNode* node;
    u16 i;

    data = p1;
    unk5C = 0xFF;
    i = 0;
    for (node = freeList; node != 0; node = M2C_FIELD(node, peNode **, 0x28)) {
        M2C_FIELD(node, u16 *, 0x30) = i;
        M2C_FIELD(node, u16 *, 0x32) = i;
        i++;
    }
    g_particle_debug_stats.unk4 += 0x60;
    g_particle_debug_stats.unk14 += 0x60;
}
#pragma pop
}

extern "C++" {
void peParticleStripNode::UpdateRenderData(peEmitterNode* emitter, _peParticleStrip* strip, char* out, float t) {
    Vec ext;
    Vec half;
    peEmitterNodeData* e = (peEmitterNodeData*)emitter;
    peStripDef* p = (peStripDef*)strip;
    u32 flags = p->flags;
    u32 hasColor2 = (flags >> 18) & 1;
    Vec pos;
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
        c.g = OSf32tou8(e->color[1] * OSu8tof32(c.g));
        c.r = OSf32tou8(e->color[0] * OSu8tof32(c.r));
        c.b = OSf32tou8(e->color[2] * OSu8tof32(c.b));
        *(GSColor*)(out + 0x18) = c;
        c.a = OSf32tou8(255.0f * e->color[3] * evalSpline(p->alpha, t));
        if (hasColor2) {
            peColorSplineGetValue((u8*)&c, p->color2, t);
            *(GSColor*)(out + 0x2c) = c;
        }
    }
}
}
}
}
