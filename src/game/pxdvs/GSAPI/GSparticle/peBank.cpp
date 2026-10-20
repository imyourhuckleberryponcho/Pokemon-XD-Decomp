// STATUS (dPart): default flags (+pool_strings off pragma), LAYOUT OK. 13/19 exact; near-misses: _peConvertFileData 97.6% (callee-saved
// register numbering only), peBankCreate 95%, peBankFreeFile 95%, peBankLoadFile 82%, peBankRender 99.6% (slw operand regs),
// _peFreeInternalBankData 99.7% (bne/b layout).
#include <dolphin/types.h>

#pragma pool_strings off

struct GSbound;
struct GSmtx;
struct GStexture;
struct HSD_AObj;
struct HSD_Joint;
struct GSvec;
struct GSgfxColAu8;
struct HSD_JObj;

class GSgfxMatrixStack {
public:
    void push(GSmtx* m);
    void pop();
};

struct GSgfxLayer {
    u8 pad0[0x28];
    s32 id;  // 0x28
    u8 pad2C[0x19A0 - 0x2C];
    GSgfxMatrixStack* matrixStack;  // 0x19A0
};

struct HSD_Archive {
    u8 pad[0x48];
};

class GSgfxLight {
public:
    u8 pad[0x80];
    GSgfxLight();
    void MakeDiff(GSgfxColAu8* color, GSvec* pos, bool infinite);
    void MakeSpec(GSgfxColAu8* color, GSvec* dir, f32 shininess, GSvec* half);
};

extern "C" {
void* memset(void*, int, u32);
GStexture* GStextureLoad(GStexture* tex);
s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, u32 size);
void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, const char* symbol);
HSD_JObj* HSD_JObjLoadJoint(HSD_Joint* j);
void HSD_JObjAddAnimAll(HSD_JObj* j, void* a, void* b, void* c);
void HSD_JObjReqAnimAll(HSD_JObj* j, f32 frame);
void HSD_JObjAnimAll(HSD_JObj* j);
void HSD_AObjSetFlags(HSD_AObj* a, u32 flags);
void HSD_AObjClearFlags(HSD_AObj* a, u32 flags);
void HSD_AObjSetRate(HSD_AObj* a, f32 rate);
void HSD_ForeachAnim(void* object, u32 type, u32 mask, void* func, u32 callback_type, ...);
void _modelGetEndFrame(HSD_AObj* aobj, f32* endFrame);
u16 shapeGenerateIndex();
u8 shapeLoad(u16 id, void* data);
extern GSvec zeroVector;
extern GSvec zAxisVector;
void GSboundCreate(GSbound* b, int a);
void GSboundFree(GSbound* b);
void GSboundReset(GSbound* b);
void GSboundAlwaysInView(GSbound* b, int v);
int GSboundIsInViewFast(GSbound* b);
bool GSgfxTokenCleared(u16 token);
void GSgfxTokenWaitForClear(u16 token);
u8 GSgfxVideoGetVsyncRate();
u32 GSmemGetSize(void* p);
void GStextureFree(GStexture* t);
void HSD_JObjUnref(HSD_JObj* j);
f32 HSD_Randf();
u8 particleEnginePrepareRender(void* h);
u8 particleEnginePrepareUpdate(void* h);
u32 shapeGetUsedMemorySize(u16 id);
void shapeRelease(u16 id);
void* __nw__FUl(u32);
void __dl__FPv(void*);
}
void GSboundDraw(GSbound* b, GSgfxLayer* layer);
void* operator new[](u32);
void operator delete[](void*);

struct Vec3 {
    f32 x, y, z;
};
struct Quat {
    f32 x, y, z, w;
};

struct _EmitParams {
    f32 life;
    f32 speed;
    Vec3 pos;
    Vec3 vel;
    Vec3 xpos;
    Quat xrot;
    Vec3 xscale;
    _EmitParams() {
        life = 0.0f;
        speed = 0.0f;
    }
};

// Emitter parameters of a particle effect.
struct _particleData;
struct _peEmitter {
    u32 flags;           // 0x00
    u8 pad4[8];
    f32 base;            // 0x0C
    f32 range;           // 0x10
    u8 pad14[8];
    f32 mode;            // 0x1C
    u8 pad20[0x138 - 0x20];
    _particleData* children;  // 0x138
};

struct _peModelData {
    u32 flags;  // 0x00
    u8 pad4[0x48];
    HSD_JObj* jobj;  // 0x4C
};

struct _peDataBlock {
    u8 pad0[0x78];
    void* buf78;
    void* buf7c;
};

struct peEmitterNode {
    u8 pad0[0x20];
    void* f20;
    u8 pad24[4];
    u32 f28;
    u32 f2c;
    u8 pad30[0xCC];
    u32* flagsPtr;  // 0xFC
    u32 f100;

    peEmitterNode() {
        f20 = 0;
        f28 = 0;
        f2c = 0;
        flagsPtr = 0;
        f100 = 0;
    }
    void Init(_peEmitter* e);
    void Release();
    void SetLastLoop();
    void Start(peEmitterNode* parent, _peEmitter* e, _EmitParams* p);
    void Stop(_peEmitter* e);
    u8 Update(peEmitterNode* parent, _peEmitter* e, f32 dt);
    void Render(_peEmitter* e);
};

struct _particleData;

struct peBankParams {
    f32 f[10];
};

struct _gpdResourceItem {
    u8 id;        // 0x00
    u8 flags;     // 0x01
    u16 size;     // 0x02
    s32 type;     // 0x04
    void* data;   // 0x08
};

struct _gpdHeader {
    u32 magic;     // 0x00
    u32 version;   // 0x04
    u16 dataCount; // 0x08
    u16 count;     // 0x0A
    u8 refCount;   // 0x0C
    u8 pad0d[3];
    _gpdResourceItem items[1];  // 0x10
};

// A loaded particle effect instance.
struct peBank {
    _gpdHeader* file;      // 0x00
    peEmitterNode node;    // 0x04
    struct _particleData* data;  // 0x108
    f32 params[10];        // 0x10C
    u32 flags;             // 0x134
    u32 renderMask;        // 0x138
    u16 token;             // 0x13C
    u16 maxParticles;      // 0x13E
    GSbound* boundPtr() { return (GSbound*)((u8*)this + 0x140); }
    u8 bound[0x20];        // 0x140
    void* engine;          // 0x160
    peBank* next;          // 0x164
};

struct _particleData {
    u32 pad0;
    s32 type;      // 0x04
    union {
        _peEmitter* emitter;  // 0x08
        _peModelData* model;
        _peDataBlock* block;
    };
    _particleData* next;  // 0x0C
};

peBank* g_currentBank;
GSbound* g_currentBound;
u16 g_bank_token;
extern GSgfxLayer* g_current_layer;
extern s32 g_render_pass;
extern GSmtx* g_CameraMatrix;
extern peBank* g_particleBanks;
_EmitParams* g_emitParams;
u16 g_maxEmitParams;
peBank* g_emitParamsBank;

struct ParticleDebugStats {
    u32 emitMem;   // 0x00
    u32 bankMem;   // 0x04
    u32 pad8;
    u32 pad0c;
    u32 shapeMem;  // 0x10
    u32 total;     // 0x14
    u32 pad18[3];
};
extern ParticleDebugStats g_particle_debug_stats;


extern "C" {
// Dolphin SDK OSFastCast.h (GQR3 is set up for u16 conversion).
static inline u16 __OSf32tou16(register f32 inF) {
    f32 tmp;
    register f32* tmpPtr = &tmp;
    asm { psq_st inF, 0(tmpPtr), 1, 3 }
    return *(u16*)tmpPtr;
}

static inline void OSf32tou16(f32* in, u16* out) {
    *out = __OSf32tou16(*in);
}

inline u16 GScast_float_to_u16(f32 f) {
    u16 r;
    OSf32tou16(&f, &r);
    return r;
}

inline f32 GSrandf() {
    return HSD_Randf();
}
}


static bool _peConvertFileData(_gpdHeader* h, _gpdResourceItem* items, _particleData* data, const char* name);
static inline u16 _peBankCalculateMaxParticles(_particleData* data, f32 scale);
static void _peFreeInternalBankData(_particleData* data);

extern "C" {

s32 peBankIsInfinite(peBank* bank) {
    if (bank == 0) {
        return 0;
    }
    if (bank->flags & 1) {
        return *bank->node.flagsPtr & 1;
    }
    return 0;
}

f32 peBankGetLife(peBank* bank) {
    if (bank == 0) {
        return 0.0f;
    }
    if (bank->flags & 1) {
        return *(f32*)((u8*)bank + 8);
    }
    return 0.0f;
}

void peBankStopLoop(peBank* bank) {
    u8 inf;
    if (bank == 0) {
        inf = 0;
    } else if (!(bank->flags & 1)) {
        inf = 0;
    } else {
        inf = *bank->node.flagsPtr & 1;
    }
    if (inf) {
        bank->node.SetLastLoop();
    }
}

void peBankStop(peBank* bank) {
    if (bank != 0 && (bank->flags & 1)) {
        g_currentBank = bank;
        g_currentBound = (bank->flags & 0x10) ? (GSbound*)bank->bound : 0;
        bank->node.Stop(bank->data->emitter);
        bank->flags = 0;
    }
}

void peBankRender(peBank* bank) {
    if (bank != 0 && (bank->flags & 1) && (bank->flags & 4) && (bank->flags & 8)) {
        s32 mask = 1 << g_current_layer->id;
        if (g_render_pass == 1) {
            mask <<= 16;
        }
        if (!(bank->renderMask & mask)) {
            g_currentBank = bank;
            g_currentBound = (bank->flags & 0x10) ? (GSbound*)bank->bound : 0;
            if (particleEnginePrepareRender(bank->engine)) {
                bank->renderMask |= mask;
                g_current_layer->matrixStack->push(g_CameraMatrix);
                g_bank_token = 0;
                bank->node.Render(bank->data->emitter);
                if (g_bank_token != 0) {
                    bank->token = g_bank_token;
                }
                if ((bank->flags & 0x10) && (bank->flags & 0x20) && g_current_layer->id == 4 && g_render_pass == 1) {
                    GSboundDraw((GSbound*)bank->bound, g_current_layer);
                }
                g_current_layer->matrixStack->pop();
            }
        }
    }
}

void peBankUpdate(peBank* bank, f32 dt) {
    if (bank != 0 && (bank->flags & 1) && !(bank->flags & 2)) {
        if (bank->token != 0 && GSgfxTokenCleared(bank->token)) {
            bank->token = 0;
        }
        if (particleEnginePrepareUpdate(bank->engine)) {
            g_currentBank = bank;
            if (bank->flags & 0x10) {
                g_currentBound = (GSbound*)bank->bound;
                GSboundReset(g_currentBound);
                GSboundAlwaysInView(g_currentBound, 0);
            } else {
                g_currentBound = 0;
            }
            if ((f32)bank->node.Update(0, bank->data->emitter, dt) <= 0.0f) {
                bank->node.Stop(bank->data->emitter);
                bank->flags = 0;
                return;
            }
            if (g_currentBound == 0 || GSboundIsInViewFast(g_currentBound)) {
                bank->flags |= 8;
            } else {
                bank->flags &= ~8;
            }
        }
    }
}

s32 peBankStart(peBank* bank) {
    static _EmitParams params;
    if (bank == 0) {
        return 0;
    }
    params.life = 1.0f;
    peBankStop(bank);
    g_currentBank = bank;
    g_currentBound = 0;
    _peEmitter* em = bank->data->emitter;
    bank->flags = 5;
    if (em->flags & 0x20000) {
        bank->flags |= 0x10;
        g_currentBound = (GSbound*)bank->bound;
        GSboundReset(g_currentBound);
        GSboundAlwaysInView(g_currentBound, 0);
    }
    bank->node.Start(0, bank->data->emitter, &params);
    bank->token = 0;
    return 1;
}


void peBankFree(peBank* bank) {
    if (bank != 0) {
        peBankStop(bank);
        if (bank->token != 0) {
            GSgfxTokenWaitForClear(bank->token);
            bank->token = 0;
        }
        bank->node.Release();
        bank->file->refCount--;
        GSboundFree((GSbound*)bank->bound);
        if (bank != 0 && g_maxEmitParams != 0 && bank == g_emitParamsBank) {
            _EmitParams* ep = g_emitParams;
            g_particle_debug_stats.total -= g_particle_debug_stats.emitMem;
            g_particle_debug_stats.emitMem = 0;
            if (ep != 0) {
                operator delete[]((u8*)ep - 0x10);
            }
            g_emitParams = 0;
            g_emitParamsBank = 0;
            g_maxEmitParams = 0;
            for (peBank* b = g_particleBanks; b != 0; b = b->next) {
                if (b != bank) {
                    u16 n = b->maxParticles;
                    if (n > g_maxEmitParams) {
                        g_emitParamsBank = b;
                        g_maxEmitParams = (n + 9) & ~9;
                    }
                }
            }
            u16 m = g_maxEmitParams;
            if (m != 0) {
                g_emitParams = new _EmitParams[m];
                g_particle_debug_stats.emitMem += g_maxEmitParams * sizeof(_EmitParams);
                g_particle_debug_stats.total += g_maxEmitParams * sizeof(_EmitParams);
            }
        }
        peBank* b = g_particleBanks;
        peBank* prev = 0;
        while (b != 0) {
            if (b == bank) {
                break;
            }
            prev = b;
            b = b->next;
        }
        if (prev != 0) {
            prev->next = b->next;
        } else {
            g_particleBanks = b->next;
        }
        b->next = 0;
        u32 sz = GSmemGetSize(bank);
        g_particle_debug_stats.bankMem -= sz;
        g_particle_debug_stats.total -= sz;
        if (bank != 0) {
            __dl__FPv(bank);
        }
    }
}

peBank* peBankCreate(_gpdHeader* file) {
    if (file == 0) {
        return 0;
    }
    peBank* bank = new peBank;
    _gpdResourceItem* items = file->items;
    if (bank == 0) {
        return 0;
    }
    u32 sz = GSmemGetSize(bank);
    g_particle_debug_stats.bankMem += sz;
    g_particle_debug_stats.total += sz;
    GSboundCreate((GSbound*)bank->bound, 0);
    _particleData* data = (_particleData*)(items + file->count);
    bank->file = file;
    file->refCount++;
    memset(&bank->node, 0, 0x104);
    bank->data = data;
    bank->params[0] = 0.0f;
    bank->params[1] = 0.0f;
    bank->params[2] = 0.0f;
    bank->params[3] = 0.0f;
    bank->params[4] = 0.0f;
    bank->params[5] = 0.0f;
    bank->params[6] = 1.0f;
    bank->params[7] = 1.0f;
    bank->params[8] = 1.0f;
    bank->params[9] = 1.0f;
    bank->flags = 0;
    bank->renderMask = 0;
    bank->token = 0;
    bank->engine = 0;
    peBank* b = g_particleBanks;
    if (b != 0) {
        while (b->next != 0) {
            b = b->next;
        }
        b->next = bank;
    } else {
        g_particleBanks = bank;
    }
    bank->next = 0;
    g_currentBank = bank;
    bank->node.f20 = bank->params;
    bank->node.Init(data->emitter);
    bank->maxParticles = _peBankCalculateMaxParticles(data, 4.0f / (f32)GSgfxVideoGetVsyncRate());
    if (bank != 0 && bank->maxParticles > g_maxEmitParams) {
        if (g_emitParams != 0) {
            u32 old = g_particle_debug_stats.emitMem;
            g_particle_debug_stats.total -= old;
            g_particle_debug_stats.emitMem = 0;
            if (g_emitParams != 0) {
                operator delete[]((u8*)g_emitParams - 0x10);
            }
        }
        g_emitParamsBank = bank;
        u16 m = ((bank->maxParticles + 9) / 10);
        m *= 10;
        g_maxEmitParams = m;
        g_emitParams = new _EmitParams[m];
        g_particle_debug_stats.emitMem += g_maxEmitParams * sizeof(_EmitParams);
        g_particle_debug_stats.total += g_maxEmitParams * sizeof(_EmitParams);
    }
    return bank;
}

void peBankFreeFile(_gpdHeader* file) {
    if (file->magic != 0x1F056DA || file->version != 0x30002) {
        return;
    }
    if (file->refCount == 0) {
        _gpdResourceItem* items = file->items;
        _peFreeInternalBankData((_particleData*)(items + file->count));
        int n = file->count;
        _gpdResourceItem* it = items;
        for (; n != 0; it++, n--) {
            if ((it->flags & 0x40) == 0x40) {
                switch (it->type) {
                case 0:
                    GStextureFree((GStexture*)it->data);
                    break;
                case 3: {
                    u16 id = (u16)((s32)it->data - 1);
                    u32 m = shapeGetUsedMemorySize(id);
                    g_particle_debug_stats.shapeMem -= m;
                    g_particle_debug_stats.total -= m;
                    shapeRelease(id);
                    break;
                }
                case 2: {
                    u32* arr = (u32*)it->data;
                    GStexture** t = (GStexture**)(arr + 1);
                    u32 i = 0;
                    u32 cnt = arr[0];
                    for (; i < cnt; i++, t++) {
                        if (*t != 0) {
                            GStextureFree(*t);
                        }
                    }
                    break;
                }
                }
            }
        }
    }

}

_gpdHeader* peBankLoadFile(_gpdHeader* file) {
    _gpdResourceItem* items = file->items;
    if (_peConvertFileData(file, items, (_particleData*)(items + file->count), (const char*)file)) {
        return file;
    }
    return 0;
}

}

static inline u16 _peBankCalculateMaxParticles(_particleData* data, f32 scale) {
    if (data->type != 0) {
        return 0;
    }
    _peEmitter* e = data->emitter;
    f32 v = e->range * GSrandf() + e->base;
    u16 n;
    if (e->mode <= 0.00001f) {
        n = GScast_float_to_u16(0.5f + v);
    } else {
        v *= scale;
        n = GScast_float_to_u16(0.5f + v);
    }
    if (n == 0) {
        n = 1;
    }
    for (_particleData* c = e->children; c != 0; c = c->next) {
        u16 m = _peBankCalculateMaxParticles(c, scale);
        if (m > n) {
            n = m;
        }
    }
    if (n > 1000) {
        n = 1000;
    }
    return n;
}

static void _peFreeInternalBankData(_particleData* data) {
    void* p = data->emitter;
    if (p == 0) {
        return;
    }
    switch (data->type) {
    case 0:
        if (p == 0) {
            break;
        }
        for (_particleData* c = ((_peEmitter*)p)->children; c != 0; c = c->next) {
            _peFreeInternalBankData(c);
        }
        break;
    case 2: {
        _peModelData* m = (_peModelData*)p;
        if (m == 0) {
            break;
        }
        if (m->flags & 0x40) {
            break;
        }
        if (m->jobj != 0) {
            HSD_JObjUnref(m->jobj);
            return;
        }
        return;
    }
    case 4: {
        _peDataBlock* b = (_peDataBlock*)p;
        if (b->buf78 != 0) {
            g_particle_debug_stats.bankMem -= 0x80;
            g_particle_debug_stats.total -= 0x80;
            __dl__FPv(b->buf78);
            b->buf78 = 0;
        }
        if (b->buf7c != 0) {
            g_particle_debug_stats.bankMem -= 0x80;
            g_particle_debug_stats.total -= 0x80;
            __dl__FPv(b->buf7c);
            b->buf7c = 0;
        }
        break;
    }
    }
}

static inline bool isOffset(u32 v) {
    return v != 0 && v < 0x80000000;
}

#define PF(p, off) (*(u32*)((u8*)(p) + (off)))

static inline void fix(u32* slot, u32 base) {
    u32 v = *slot;
    if (isOffset(v)) {
        v += base;
    }
    *slot = v;
}

struct _peT1 {
    u32 flags;  // 0x00
    u8 p4[0x40];
    union {
        struct {
            f32 a, b, c, d;
        } f;
        s16 s[4];
    } q;       // 0x44
    s32 res;   // 0x54
};

struct _peT6 {
    u32 flags;  // 0x00
    u8 p4[0x18];
    s32 res;    // 0x1C
};

struct _peT3 {
    u8 p0[0x60];
    s32 res;    // 0x60
};

struct _peT2 {
    u32 flags;  // 0x00
    u8 p4[0x48];
    s32 res;    // 0x4C
    f32 endFrame;  // 0x50
    f32 frame;     // 0x54
};

struct _peT4 {
    u32 flags;  // 0x00
    u8 p4[0x68];
    u8 color[4];   // 0x6C
    f32 shine;     // 0x70
    s32 res;       // 0x74
    GSgfxLight* diff;  // 0x78
    GSgfxLight* spec;  // 0x7C
};

static bool _peConvertFileData(_gpdHeader* h, _gpdResourceItem* items, _particleData* data, const char* name) {
    if (h->magic != 0x1F056DA || h->version != 0x30002) {
        return false;
    }
    if (h->refCount != 0) {
        return true;
    }
    u32 n = h->count;
    u32 m = h->dataCount;
    _gpdResourceItem* it = items;
    for (; n != 0; n--, it++) {
        u32 v = (u32)it->data;
        if (isOffset(v)) {
            v += (u32)name;
        }
        it->data = (void*)v;
        it->flags &= ~0x40;
        switch (it->type) {
        case 0: {
            GStexture* tex = GStextureLoad((GStexture*)it->data);
            if (tex != 0) {
                it->flags |= 0x40;
            }
            it->data = tex;
            break;
        }
        case 1: {
            HSD_Archive archive;
            u8 f = it->flags;
            HSD_ArchiveParse(&archive, (u8*)it->data, (it->size << 5) - (f & 0x17));
            void* addr = HSD_ArchiveGetPublicAddress(&archive, "scene_data");
            if (addr != 0) {
                it->flags |= 0x40;
            }
            it->data = addr;
            break;
        }
        case 2: {
            if (it->data == 0) {
                break;
            }
            u32* arr = (u32*)it->data;
            u32 cnt = arr[0];
            u32* e = arr + 1;
            u32 i = 0;
            for (; i < cnt; i++, e++) {
                u32 ev = *e;
                if (isOffset(ev)) {
                    ev += (u32)it->data;
                }
                *e = ev;
                *e = (u32)GStextureLoad((GStexture*)*e);
            }
            it->flags |= 0x40;
            break;
        }
        case 3: {
            u16 idx = shapeGenerateIndex() + 1;
            if (idx != 0) {
                u32 id = idx - 1;
                if (shapeLoad(id, it->data)) {
                    u32 mem = shapeGetUsedMemorySize(id);
                    g_particle_debug_stats.shapeMem += mem;
                    g_particle_debug_stats.total += mem;
                    it->flags |= 0x40;
                } else {
                    idx = 0;
                }
            }
            it->data = (void*)(u32)idx;
            break;
        }
        }
    }
    for (; m != 0; m--, data++) {
        fix((u32*)&data->emitter, (u32)name);
        fix((u32*)&data->next, (u32)name);
        void* p = data->emitter;
        if (p == 0) {
            continue;
        }
        switch (data->type) {
        case 0:
            fix(&PF(p, 0x138), (u32)name);
            fix(&PF(p, 0x14), (u32)name);
            fix(&PF(p, 0x130), (u32)name);
            fix(&PF(p, 0x134), (u32)name);
            fix(&PF(p, 0xB8), (u32)name);
            fix(&PF(p, 0xBC), (u32)name);
            fix(&PF(p, 0xC0), (u32)name);
            fix(&PF(p, 0xD0), (u32)name);
            fix(&PF(p, 0xD4), (u32)name);
            fix(&PF(p, 0xD8), (u32)name);
            fix(&PF(p, 0xE8), (u32)name);
            fix(&PF(p, 0xEC), (u32)name);
            fix(&PF(p, 0xF0), (u32)name);
            fix(&PF(p, 0x10C), (u32)name);
            fix(&PF(p, 0x110), (u32)name);
            fix(&PF(p, 0x114), (u32)name);
            fix(&PF(p, 0x124), (u32)name);
            fix(&PF(p, 0x128), (u32)name);
            fix(&PF(p, 0x12C), (u32)name);
            break;
        case 1: {
            _peT1* t = (_peT1*)p;
            u32 k = h->count;
            _gpdResourceItem* r = items;
            for (; k != 0; k--, r++) {
                if (t->res == r->id) {
                    if (r->type == 2) {
                        t->flags |= 0x100000;
                        t->res = ((r->flags & 0x40) == 0x40) ? (s32)r->data : 0;
                    } else {
                        t->flags &= ~0x100000;
                        t->res = ((r->flags & 0x40) == 0x40) ? (s32)r->data : 0;
                    }
                    break;
                }
            }
            if (k == 0) {
                t->res = 0;
            }
            fix(&PF(p, 0x34), (u32)name);
            fix(&PF(p, 0x14), (u32)name);
            fix(&PF(p, 0x18), (u32)name);
            fix(&PF(p, 0x38), (u32)name);
            fix(&PF(p, 0x3C), (u32)name);
            if (PF(p, 0x3C) == 0) {
                t->flags &= ~0x2000000;
            }
            fix(&PF(p, 0x40), (u32)name);
            if (!(t->flags & 8)) {
                f32 scale = 1024.0f;
                f32 a = t->q.f.a;
                f32 b = t->q.f.b;
                t->q.s[0] = (s16)(scale * a);
                t->q.s[1] = (s16)(scale * b);
                f32 c = t->q.f.c;
                f32 d = t->q.f.d;
                t->q.s[2] = (s16)(scale * c);
                t->q.s[3] = (s16)(scale * d);
                t->q.f.d = 0.0f;
                t->q.f.c = 0.0f;
                t->flags |= 8;
            }
            break;
        }
        case 6: {
            _peT6* t = (_peT6*)p;
            u32 k = h->count;
            _gpdResourceItem* r = items;
            for (; k != 0; k--, r++) {
                if (t->res == r->id) {
                    if (r->type == 2) {
                        t->flags |= 0x400;
                        if (t->flags & 0x2000) {
                            t->flags &= ~0x40000;
                        }
                        t->res = ((r->flags & 0x40) == 0x40) ? (s32)r->data : 0;
                    } else {
                        t->flags &= ~0x400;
                        t->res = ((r->flags & 0x40) == 0x40) ? (s32)r->data : 0;
                    }
                    break;
                }
            }
            if (k == 0) {
                t->res = 0;
            }
            fix(&PF(p, 0x8), (u32)name);
            fix(&PF(p, 0xC), (u32)name);
            if (PF(p, 0xC) == 0) {
                t->flags &= ~0x40000;
            }
            fix(&PF(p, 0x10), (u32)name);
            break;
        }
        case 3: {
            _peT3* t = (_peT3*)p;
            u32 k = h->count;
            _gpdResourceItem* r = items;
            for (; k != 0; k--, r++) {
                if (t->res == r->id) {
                    t->res = ((r->flags & 0x40) == 0x40) ? (s32)r->data : 0;
                    break;
                }
            }
            if (k == 0) {
                t->res = 0;
            }
            fix(&PF(p, 0x30), (u32)name);
            fix(&PF(p, 0x14), (u32)name);
            fix(&PF(p, 0x18), (u32)name);
            fix(&PF(p, 0x34), (u32)name);
            break;
        }
        case 2: {
            _peT2* t = (_peT2*)p;
            u32 k = h->count;
            _gpdResourceItem* r = items;
            for (; k != 0; k--, r++) {
                if (t->res == r->id) {
                    if ((t->flags & 0x40) && r->type == 3) {
                        t->res = ((r->flags & 0x40) == 0x40) ? (s32)r->data : 0;
                        break;
                    }
                    if (r->type == 1) {
                        void* d = ((r->flags & 0x40) == 0x40) ? r->data : 0;
                        if (d == 0) {
                            break;
                        }
                        u32** scene = (u32**)**(u32**)d;
                        HSD_JObj* jobj = HSD_JObjLoadJoint((HSD_Joint*)*(u32*)scene[0]);
                        if (jobj == 0) {
                            t->res = 0;
                            break;
                        }
                        t->res = (s32)jobj;
                        t->frame = 0.0f;
                        t->endFrame = 0.0f;
                        void* a = 0;
                        void* b = 0;
                        void* c = 0;
                        if (scene[1] != 0) {
                            a = *(void**)scene[1];
                        }
                        if (scene[2] != 0) {
                            b = *(void**)scene[2];
                        }
                        if (scene[3] != 0) {
                            c = *(void**)scene[3];
                        }
                        HSD_JObjAddAnimAll(jobj, a, b, c);
                        if (t->flags & 4) {
                            HSD_ForeachAnim(jobj, 6, 0xFFFF, (void*)HSD_AObjSetFlags, 3, 0x20000000);
                        } else {
                            HSD_ForeachAnim(jobj, 6, 0xFFFF, (void*)HSD_AObjClearFlags, 3, 0x20000000);
                        }
                        HSD_ForeachAnim(jobj, 6, 0xFFFF, (void*)HSD_AObjSetRate, 1, 0.0);
                        HSD_ForeachAnim(jobj, 6, 0xFFFF, (void*)_modelGetEndFrame, 2, &t->endFrame);
                        HSD_JObjReqAnimAll(jobj, 0.0f);
                        HSD_JObjAnimAll(jobj);
                        t->endFrame = t->endFrame / 60.0f;
                        break;
                    }
                    t->res = 0;
                    break;
                }
            }
            if (k == 0) {
                t->res = 0;
            }
            fix(&PF(p, 0x34), (u32)name);
            fix(&PF(p, 0x38), (u32)name);
            fix(&PF(p, 0x3C), (u32)name);
            fix(&PF(p, 0x40), (u32)name);
            fix(&PF(p, 0x44), (u32)name);
            fix(&PF(p, 0x48), (u32)name);
            break;
        }
        case 4: {
            _peT4* t = (_peT4*)p;
            u32 k = h->count;
            _gpdResourceItem* r = items;
            for (; k != 0; k--, r++) {
                if (t->res == r->id) {
                    t->res = ((r->flags & 0x40) == 0x40) ? (s32)r->data : 0;
                    break;
                }
            }
            if (k == 0) {
                t->res = 0;
            }
            fix(&PF(p, 0x4C), (u32)name);
            fix(&PF(p, 0x50), (u32)name);
            fix(&PF(p, 0x34), (u32)name);
            fix(&PF(p, 0x38), (u32)name);
            fix(&PF(p, 0x3C), (u32)name);
            fix(&PF(p, 0x40), (u32)name);
            fix(&PF(p, 0x44), (u32)name);
            fix(&PF(p, 0x48), (u32)name);
            if (t->flags & 0x200) {
                GSgfxLight* l = new GSgfxLight;
                if (l != 0) {
                    g_particle_debug_stats.bankMem += 0x80;
                    g_particle_debug_stats.total += 0x80;
                    l->MakeDiff((GSgfxColAu8*)t->color, &zeroVector, false);
                    t->diff = l;
                    if (t->flags & 0x400) {
                        GSgfxLight* l2 = new GSgfxLight;
                        if (l2 != 0) {
                            g_particle_debug_stats.bankMem += 0x80;
                            g_particle_debug_stats.total += 0x80;
                            l2->MakeSpec((GSgfxColAu8*)t->color, &zAxisVector, t->shine, 0);
                            t->spec = l2;
                        } else {
                            t->flags &= ~0x400;
                        }
                    }
                } else {
                    t->flags &= ~0x600;
                }
            }
            break;
        }
        }
    }
    return true;
}
