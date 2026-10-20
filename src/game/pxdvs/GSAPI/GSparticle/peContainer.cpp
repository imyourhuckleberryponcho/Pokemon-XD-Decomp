// STATUS (dPart): needs extra_cflags -inline deferred (source written bottom-to-top; LAYOUT OK). 12/16 exact;
// peRenderContainer ctor 86% (reg alloc of locals + debug-stat add order), PreUpdate 97% (dl[cur].flags|=2 form),
// peContainer ctor 98% (stats pointer/0xa8 constant register). Not linkable until those are exact.
#include <dolphin/types.h>

extern "C" {
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
void DCFlushRange(void*, u32);
}

class GSgfxLayer {
public:
    u16 tokenMark();
    void SetLayerVisibility(bool visible);
};

enum GSgfxLayerID { GS_LAYER_DUMMY };
enum GSgfxPrimType { GS_PRIM_DUMMY };
struct GSgfxVF;

struct GSgfxDL {
    u16 flags;  // 0x00
    u16 count;  // 0x02
    u8* data;   // 0x04
    u32 size;   // 0x08
    u32 pad;

    bool valid() const { return (flags & 1) == 1; }
    u8* colorPtr() { return (flags & 1) ? data + 3 : 0; }
    u16 vertCount() { return (flags & 1) ? count : 0; }
};

extern "C" {
void GSgfxDLCreate(GSgfxDL* dl, GSgfxPrimType prim, GSgfxVF* vf, u16 count);
void GSgfxDLFree(GSgfxDL* dl);
void GSgfxTokenWaitForClear(u16 token);
GSgfxLayer* GSgfxLayerFindByID(GSgfxLayerID id);
u32 GSmemGetSize(void* p);
void GSmemFree(void* p);
void* GSmemAllocClr(u32 size);
void* GSmemAllocAlignClr(u32 size, u32 align);
}

extern GSgfxLayer* g_current_layer;
extern u16 g_bank_token;

struct ParticleDebugStats {
    u32 pad0;
    u32 nodeMem;
    u32 dlMem;
    u32 bufMem;
    u32 pad10;
    u32 total;
    u32 pad18[3];
};
extern ParticleDebugStats g_particle_debug_stats;

struct peEmitParamsC {
    u32 flags;
};
struct peEmitterNode {
    u8 pad0[0xFC];
    peEmitParamsC* params;
};

class peNode {
public:
    u8 pad[0x28];
    peNode* prev;  // 0x28
    peNode* next;  // 0x2c
};

class peContainer {
public:
    peEmitterNode* emitter;  // 0x00
    u32 unk4;                // 0x04
    void* buffer;            // 0x08
    peNode* freeList;        // 0x0c
    peNode* activeList;      // 0x10
    u16 count;               // 0x14
    u16 maxCount;            // 0x16
    u8 dirty;                // 0x18
    u8 started;              // 0x19

    peContainer(peEmitterNode* e, u32 nodeSize, u16 max);
    virtual ~peContainer();
    virtual void Start();
    virtual void PreUpdate();
    virtual void Emit(u16 n) = 0;
    virtual void Update(f32 dt) = 0;
    virtual void Render() = 0;
    virtual void Stop() = 0;

    void MoveNode(peNode* node, peNode* after);
    void RemoveAll();
    void RemoveNode(peNode* node);
    u16 CreateNodes(u16 n);
    static void SetLayerVisibility(GSgfxLayerID id, bool visible);
};

class peRenderContainer : public peContainer {
public:
    u8 swapPending;  // 0x20
    u8 cur;          // 0x21
    u32 bufSize;     // 0x24
    GSgfxDL dl[2];   // 0x28
    u8* bufA;        // 0x48
    u8* bufB;        // 0x4c
    u16 tokens[2];   // 0x50

    peRenderContainer(peEmitterNode* e, u32 nodeSize, u16 max, GSgfxVF* vf, GSgfxPrimType prim, u8 vertsPerNode,
                      u8 bytesPerVert, bool dbl);
    virtual ~peRenderContainer();
    virtual void Start() = 0;
    virtual void PreUpdate();
    void ResetSwap();
    void InitSwap();
    void ResolveMultipleSwap();
    void MarkForSwap();
};

peContainer::peContainer(peEmitterNode* e, u32 nodeSize, u16 max) {
    emitter = e;
    unk4 = 0;
    buffer = 0;
    freeList = 0;
    activeList = 0;
    count = 0;
    maxCount = max;
    dirty = 0;
    started = 0;
    peNode* node;
    u32 hasPos = (emitter->params->flags >> 6) & 1;
    u32 total = max * nodeSize;
    if (hasPos) {
        total += max * 0x28;
    }
    buffer = GSmemAllocClr(total);
    if (!buffer) {
        return;
    }
    u32 sz = GSmemGetSize(buffer);
    g_particle_debug_stats.nodeMem += sz;
    g_particle_debug_stats.total += sz;
    freeList = (peNode*)buffer;
    u8* cur = (u8*)freeList;
    peNode* prevNode = 0;
    for (u32 i = 0; i < max; i++) {
        node = (peNode*)cur;
        cur += nodeSize;
        if (hasPos) {
            *(u8**)((u8*)node + 0x20) = cur;
            cur += 0x28;
        } else {
            *(u8**)((u8*)node + 0x20) = (u8*)e + 0xa8;
        }
        node->next = prevNode;
        if (prevNode) {
            prevNode->prev = node;
        }
        prevNode = node;
    }
    dirty = 1;
}

peContainer::~peContainer() {
    if (buffer) {
        u32 sz = GSmemGetSize(buffer);
        g_particle_debug_stats.nodeMem -= sz;
        g_particle_debug_stats.total -= sz;
        GSmemFree(buffer);
        buffer = 0;
    }
}

void peContainer::Start() {
    if (!started) {
        started = 1;
    }
}

void peContainer::PreUpdate() {}

void peContainer::SetLayerVisibility(GSgfxLayerID id, bool visible) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer) {
        layer->SetLayerVisibility(visible);
    }
}

u16 peContainer::CreateNodes(u16 n) {
    peNode* p;
    peNode* first = freeList;
    if (!first) {
        return 0;
    }
    peNode* last = first;
    u16 i = 1;
    for (; (p = last->prev) && i < n; i++) {
        last = p;
    }
    if (p) {
        p->next = 0;
    }
    freeList = last->prev;
    peNode* a = activeList;
    last->prev = a;
    if (a) {
        a->next = last;
    }
    first->next = 0;
    activeList = first;
    count += i;
    dirty = 1;
    return i;
}

void peContainer::RemoveNode(peNode* node) {
    peNode* p = node->prev;
    peNode* n = node->next;
    if (p) {
        p->next = n;
    }
    if (n) {
        n->prev = p;
    } else {
        activeList = p;
    }
    node->next = 0;
    peNode* f = freeList;
    node->prev = f;
    if (f) {
        f->next = node;
    }
    freeList = node;
    count--;
    dirty = 1;
}

void peContainer::RemoveAll() {
    peNode* tail = activeList;
    if (!tail) {
        return;
    }
    while (tail->prev) {
        tail = tail->prev;
    }
    peNode* f = freeList;
    tail->prev = f;
    if (f) {
        f->next = tail;
    }
    freeList = activeList;
    activeList = 0;
    count = 0;
    dirty = 1;
}

void peContainer::MoveNode(peNode* node, peNode* after) {
    peNode* p = node->prev;
    peNode* n = node->next;
    if (p) {
        p->next = n;
    }
    if (n) {
        n->prev = p;
    } else {
        activeList = p;
    }
    peNode* t = after->next;
    after->next = node;
    node->prev = after;
    node->next = t;
    if (t) {
        t->prev = node;
    } else {
        activeList = node;
    }
}

peRenderContainer::peRenderContainer(peEmitterNode* e, u32 nodeSize, u16 max, GSgfxVF* vf, GSgfxPrimType prim,
                                     u8 vertsPerNode, u8 bytesPerVert, bool dbl)
    : peContainer(e, nodeSize, max) {
    u32 aligned;
    u32 total = max * bytesPerVert;
    swapPending = 0;
    cur = 0;
    bufSize = 0;
    memset(&dl[0], 0, 0x10);
    memset(&dl[1], 0, 0x10);
    bufA = 0;
    bufB = 0;
    tokens[0] = 0;
    tokens[1] = 0;
    aligned = (total + 31) & ~31;
    u8* mem = (u8*)GSmemAllocAlignClr(dbl ? aligned * 2 : aligned, 0x20);
    if (!mem) {
        return;
    }
    u32 verts = max * vertsPerNode;
    GSgfxDLCreate(&dl[0], prim, vf, verts);
    if (!dl[0].valid()) {
        if ((u16)mem) {
            GSmemFree(mem);
        }
        return;
    }
    if (dbl) {
        GSgfxDLCreate(&dl[1], prim, vf, verts);
    }
    u32 sz = GSmemGetSize(mem);
    g_particle_debug_stats.dlMem += dl[0].size + dl[1].size;
    g_particle_debug_stats.total += dl[0].size + dl[1].size + sz;
    g_particle_debug_stats.bufMem += sz;
    if (dl[1].valid()) {
        DCFlushRange(mem, aligned * 2);
        u8* p = mem + 0x40000000;
        bufA = p;
        bufB = p + aligned;
    } else {
        DCFlushRange(mem, total);
        bufA = mem + 0x40000000;
    }
    bufSize = total;
    memset(dl[0].colorPtr(), 0xff, max * (vertsPerNode * dl[0].vertCount()));
    dl[0].flags |= 2;
    if (dl[1].valid()) {
        memset(dl[1].colorPtr(), 0xff, max * (vertsPerNode * dl[1].vertCount()));
        dl[1].flags |= 2;
    }
}

peRenderContainer::~peRenderContainer() {
    if (dl[0].valid()) {
        u32 s = dl[0].size;
        g_particle_debug_stats.dlMem -= s;
        g_particle_debug_stats.total -= s;
        GSgfxDLFree(&dl[0]);
        if (dl[1].valid()) {
            u32 s2 = dl[1].size;
            g_particle_debug_stats.dlMem -= s2;
            g_particle_debug_stats.total -= s2;
            GSgfxDLFree(&dl[1]);
        }
        if (bufA) {
            bufA = (u8*)((u32)bufA - 0x40000000);
            u32 sz = GSmemGetSize(bufA);
            g_particle_debug_stats.bufMem -= sz;
            g_particle_debug_stats.total -= sz;
            if (bufA) {
                GSmemFree(bufA);
                bufA = 0;
            }
        }
    }
}

void peRenderContainer::PreUpdate() {
    if (started) {
        if (dl[0].valid()) {
            if (tokens[cur]) {
                GSgfxTokenWaitForClear(tokens[cur]);
                tokens[cur] = 0;
            }
            if (dl[1].valid()) {
                if (swapPending) {
                    swapPending = 0;
                    if (dirty) {
                        memcpy(dl[cur].data, dl[cur == 0].data, dl[0].size);
                        GSgfxDL* d = &dl[cur];
                        d->flags |= 2;
                        dirty = 0;
                    }
                }
            }
        }
    }
}

void peRenderContainer::MarkForSwap() {
    if (dl[0].valid()) {
        g_bank_token = g_current_layer->tokenMark();
        tokens[cur] = g_bank_token;
        if (dl[1].valid()) {
            cur ^= 1;
            swapPending = 1;
        }
    }
}

void peRenderContainer::ResolveMultipleSwap() {
    if (dl[0].valid()) {
        if (dl[1].valid()) {
            if (swapPending) {
                cur ^= 1;
                swapPending = 0;
            }
        }
    }
}

void peRenderContainer::InitSwap() {
    if (dl[0].valid()) {
        tokens[0] = 0;
        dl[0].flags |= 2;
        if (dl[1].valid()) {
            tokens[1] = 0;
            dl[1].flags |= 2;
        }
    }
}

void peRenderContainer::ResetSwap() {}
