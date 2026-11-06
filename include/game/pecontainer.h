#ifndef GAME_PECONTAINER_H
#define GAME_PECONTAINER_H

struct peEmitterNode;
struct peNode;
class peContainer;
struct _peEmitter;
struct _peShape;
struct _peModel;
struct _peDistortion;
struct _peParticle;
struct _peParticleStrip;

#define PE_CONTAINER_MEMBERS                                                                                   \
    peEmitterNode* emitter;                                                                         \
    peContainer* next;                                       \
    void* buffer;                                           \
    peNode* freeList;                                                                         \
    peNode* activeList;                                                                         \
    u16 count;                                                                         \
    u16 maxCount;                                                                         \
    u8 dirty;                                                                         \
    u8 started;

#ifdef __MWERKS__
#define PE_DL_SIZE 0x10
#define PE_DL_ALIGN
#else
#define PE_DL_SIZE 0x20
#define PE_DL_ALIGN alignas(8)
#endif
#ifdef __MWERKS__
#define PE_DL_VF(dlp) (*(GSgfxVF**)((dlp) + 0xC))
#else
struct peDLRaw { u16 flags; u16 stride; u8* data; u32 size; void* vf; };
#define PE_DL_VF(dlp) ((GSgfxVF*)((peDLRaw*)(dlp))->vf)
#endif

#ifdef __MWERKS__
#define PE_DL_W16(q, T, i, v) (((T*)(q))[i] = (v))
#else
#include <game/gcdata.h>
#define PE_DL_W16(q, T, i, v) gc_wr16((u8*)(q) + 2 * (i), (u16)(T)(v))
#endif

#define PE_RENDER_MEMBERS_DL(dldecl)                                                                           \
    u8 swapPending;                                                                       \
    u8 cur;                                                                       \
    u32 bufSize;                                                                       \
    PE_DL_ALIGN dldecl;                                                                       \
    u8* bufA;                                                                       \
    u8* bufB;                                                                       \
    u16 tokens[2];
#define PE_RENDER_MEMBERS PE_RENDER_MEMBERS_DL(u8 dl[2][PE_DL_SIZE])

#ifdef __MWERKS__
#define PE_NODE_SIZE(gc, T) (gc)
#else
#define PE_NODE_SIZE(gc, T) sizeof(T)
#endif

struct peNodeHead {
    f32 life0;
    f32 life;
    f32 pos[3];
    f32 vel[3];
    void* xform;
    f32 speed;
    peNode* link28;
    peNode* link2C;
};
#ifdef __MWERKS__
#define PE_NODE_XFORM(n) (*(u8**)((u8*)(n) + 0x20))
#define PE_NODE_LINK28(n) (*(peNode**)((u8*)(n) + 0x28))
#define PE_NODE_LINK2C(n) (*(peNode**)((u8*)(n) + 0x2C))
#define PE_NODE_F(n, T, off) (*(T*)((u8*)(n) + (off)))
#else
#define PE_NODE_XFORM(n) (*(u8**)&((peNodeHead*)(n))->xform)
#define PE_NODE_LINK28(n) (((peNodeHead*)(n))->link28)
#define PE_NODE_LINK2C(n) (((peNodeHead*)(n))->link2C)
#define PE_NODE_F(n, T, off) (*(T*)((u8*)(n) + (off) - 0x30 + sizeof(peNodeHead)))
#endif

struct peEmitterNodeView {
    peNodeHead head;
    u8 body[0xCC];
    void* def;
    peContainer* containers;
};
#ifdef __MWERKS__
#define PE_EMITTER_DEF_M2C(e, T) (*(T)((s8 *)(e) + (0xFC)))
#define PE_EMITTER_DEF_RAW(e, T) (*(T)((u8*)(e) + 0xfc))
#else
#define PE_EMITTER_DEF_M2C(e, T) (*(T)&((peEmitterNodeView*)(e))->def)
#define PE_EMITTER_DEF_RAW(e, T) (*(T)&((peEmitterNodeView*)(e))->def)
#endif

#define PE_EMITTER_CONTAINER_MEMBERS _peEmitter* data;
#define PE_SHAPE_CONTAINER_MEMBERS _peShape* shape;
#define PE_MODEL_CONTAINER_MEMBERS _peModel* model;
#define PE_PARTICLE_CONTAINER_MEMBERS                                                                          \
    peNode** sorted;                                                                             \
    _peParticle* data;                                                                             \
    f32 uv[8];
#define PE_STRIP_CONTAINER_MEMBERS                                                                             \
    _peParticleStrip* data;                                                                         \
    u32 unk58;                                                                         \
    u8 unk5C;
#define PE_DISTORTION_CONTAINER_MEMBERS                                                                        \
    _peDistortion* data;                                                                            \
    f32 uv[8];

#endif
