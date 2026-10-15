// WIP (NonMatching): GSgfxLayer (render lists, passes, layer list).
// Not done: RenderStats, SendFifoToRenderer, Prerender(Pass), SetupFifo, MarkAndInvalidate, dtor, UpdateActiveFifoStats
// (the fifo-stats code is inlined into several of these; string pool base hoisting not reproduced).
#include <dolphin/types.h>

struct GStexture;
struct GSgfxVF;
struct _gsgfxLayerFifo;
enum GSgfxLayerID {};
enum GSgfxLayerOffset {
    LAYER_OFFSET_NONE = 0,
    LAYER_OFFSET_ABOVE = 1,
    LAYER_OFFSET_BELOW = 2,
    LAYER_OFFSET_TOP = 3,
    LAYER_OFFSET_BOTTOM = 4,
};
enum GSgfxLayerType {};
enum GSgfxLayerPass {};

class GSgfxMatrixStack {
public:
    GSgfxMatrixStack(u32 depth);
    u32 pad[3];
};

class GSgfxLayer {
public:
    GSgfxLayer(GSgfxLayerID id, char* name, u32 w, u32 h, u32 depth, GSgfxLayerType type);
    void LoadHWState();
    void InvalidateState();
    void PrepareNextFrame();
    void BuildRenderList();
    void BuildRenderListPass(GSgfxLayerPass pass);
    void SetPassRedirect(GSgfxLayerPass pass, bool enable, GSgfxLayer* target, GSgfxLayerPass tpass, GSgfxLayerOffset off);
    void SetLayerType(GSgfxLayerType t);
    void CreateFifo(GSgfxLayerPass pass, u32 size);
    void SendFifoToRenderer(_gsgfxLayerFifo* fifo);
    void MarkAndInvalidate();
    void PrepareDistortion();
    void PrepareFBCopy();
    void Prerender();
    void PrerenderPass(GSgfxLayerPass pass);
    void GetFifoSize(u32* width, u32* height);
    GStexture* GetTextureCopy();
    void SetTextureCopy(GStexture* tex, bool a, u8* data);
    void SetWantClearFlags(bool color, bool alpha, bool depth);
    void SetClearFlags(bool color, bool alpha, bool depth);
    void SetPassVisibility(bool a, bool b);
    bool IsLayerVisible();
    void SetLayerVisibility(bool visible);
    void SetPriority(GSgfxLayerOffset offset, GSgfxLayer* relative);
    static GStexture* GetFBTexture();
    static GSgfxLayer* GetLayerList();

    GSgfxLayer* next;
    u32 flags;
    char name[0x20];
    GSgfxLayerID id;
    GSgfxLayerType type;
    u8 pad30[0x1818 - 0x30];
    struct PassFifo {
        void* data;
        u32 size;
        u8 gxFifo[0x80];
        u32 unk88;
        u32 unk8c;
        u32 color;
        u8 flag;
        int redirectId;
        int redirectPass;
        int redirectOffset;
        _gsgfxLayerFifo* pre;
        _gsgfxLayerFifo* post;
        u16 unkAC;
        u16 unkAE;
        u32 unkB0;
        u32 unkB4;
        u32 unkB8;
    } passes[2];
    PassFifo* curFifo;
    int curPass;
    u32 unk1998;
    GSgfxVF* curVF;
    GSgfxMatrixStack* matrixStack;
    GStexture* texCopy;
    u32 texCopyMode;
    u8 texCopyData[7];
    u8 visCount;
    u8 pad19b4[4];
    u8 distFlag;
    u8 pad19b9[3];
    f32 distParams[6];
    u8 pad19d4[0x1a14 - 0x19d4];

    static GStexture* fbTexPtr;
    static u16 fbTexRefCount;
    static GStexture* distTexPtr;
    static u16 distTexRefCount;
};

struct GSgfx_GCFifoObj {
    u32 base;
    u32 end;
    u32 size;
    u32 hi;
    u32 lo;
    u32 read;
    u32 write;
    u8 pad[0x4c - 0x1c];
    u32 breakpointReached;
};
struct GSgfxRenderWaitData {
    u32 unk0;
    u32 unk4;
};
void GSgfxRenderWaitInit(GSgfxRenderWaitData*);
void GSgfxRenderWaitTick(GSgfxRenderWaitData*);
void GSgfxRenderWaitExit(GSgfxRenderWaitData*);
GSgfx_GCFifoObj* GSgfxGPUGetImmediateFifo();
void GSgfxGPUInitFifoBase(GSgfx_GCFifoObj*, void*, u32);
void GSgfxGPUEnterBufferedMode(GSgfx_GCFifoObj*);
extern "C" {
void* GSmemAlloc(u32);
void GXSaveCPUFifo(GSgfx_GCFifoObj*);
void GXSetCPUFifo(GSgfx_GCFifoObj*);
void GXResetWriteGatherPipe();
void GSlogWrite(const char*, ...);
void GSgfx_GCInitState();
void DCFlushRange(void*, u32);
void GXInitFifoPtrs(GSgfx_GCFifoObj*, void*, void*);
void* memset(void*, int, u32);
extern int gsgfx_gpu_mode;
void GStextureFree(GStexture*);
GStexture* GStextureCreate(int, int, int, int, int);
u32 strlen(const char*);
int stricmp(const char*, const char*);
void* memcpy(void*, const void*, u32);
}

void GSgfxRenderModuleDoRenderFast();
struct GSgfxState {
    u8 pad[0xc40];
    GSgfxLayerID activeLayer;
};
extern "C" GSgfxState* gsgfxState;

GStexture* GSgfxLayer::fbTexPtr;
u16 GSgfxLayer::fbTexRefCount;
GStexture* GSgfxLayer::distTexPtr;
u16 GSgfxLayer::distTexRefCount;

static GSgfxLayer* _layerBottom;
static u8 _layerRenderStats;
extern "C" u8 gsgfx_layer_inPrimitive;
extern "C" void* gsgfx_layer_activeFifo;
static u32 _layerPerfColor[8] = {0xFF, 0x8000, 0x800000, 0x8080, 0x800080, 0x808000, 0x80FF, 0x808080};
static u32 _layerPerfUserColor[2] = {0xFF8000, 0};
static GSgfxLayer* _layerIDTable[16];

extern "C" {

u8 GSgfxLayerGetStatsRenderMode() {
    return _layerRenderStats;
}

void GSgfxLayerSetStatsRenderMode(u8 mode) {
    _layerRenderStats = mode;
}

}

void GSgfxLayerInvalidateAll() {
    GSgfxLayer* l;
    for (l = _layerBottom; l != 0; l = l->next) {
        l->InvalidateState();
    }
}

void GSgfxLayerPrepareNextFrame() {
    if (_layerBottom != 0) {
        GSgfxLayer* l;
        for (l = _layerBottom; l != 0; l = l->next) {
            l->PrepareNextFrame();
        }
    }
}

extern "C" {

int GSgfxLayerGetActive() {
    for (int i = 0; i < 16; i++) {
        if ((GSgfxLayer*)_layerIDTable[i] == (GSgfxLayer*)gsgfxState->activeLayer) {
            return i;
        }
    }
    return -1;
}

}

void GSgfxLayer::GetFifoSize(u32* width, u32* height) {
    if (width != 0) {
        *width = passes[0].size;
    }
    if (height != 0) {
        *height = passes[1].size;
    }
}

GStexture* GSgfxLayer::GetTextureCopy() {
    if (flags & 0x200) {
        return texCopy;
    }
    return 0;
}

void GSgfxLayer::SetTextureCopy(GStexture* tex, bool a, u8* data) {
    if (tex == 0) {
        flags &= ~0x200;
        if (fbTexPtr != 0 && texCopy == fbTexPtr) {
            fbTexRefCount--;
            if (fbTexRefCount == 0) {
                GStextureFree(fbTexPtr);
                fbTexPtr = 0;
            }
        }
        texCopy = 0;
    } else {
        if (tex == (GStexture*)0xFEFEFEFE) {
            fbTexRefCount++;
            if (fbTexRefCount == 1) {
                fbTexPtr = GStextureCreate(0, 0, 0x45, 0, 0);
                if (fbTexPtr == 0) {
                    fbTexRefCount = 0;
                    return;
                }
            }
            tex = fbTexPtr;
        }
        flags |= 0x200;
        texCopy = tex;
    }
    if (!a) {
        texCopyMode = 0;
    } else if (data == 0) {
        texCopyMode = 1;
    } else {
        texCopyMode = 2;
        memcpy(texCopyData, data, 7);
    }
}

void GSgfxLayer::SetWantClearFlags(bool color, bool alpha, bool depth) {
    flags &= ~0x1c0;
    if (color) {
        flags |= 0x40;
    }
    if (alpha) {
        flags |= 0x80;
    }
    if (depth) {
        flags |= 0x100;
    }
}

void GSgfxLayer::SetClearFlags(bool color, bool alpha, bool depth) {
    flags &= ~0x38;
    if (color) {
        flags |= 0x8;
    }
    if (alpha) {
        flags |= 0x10;
    }
    if (depth) {
        flags |= 0x20;
    }
}

void GSgfxLayer::SetPassVisibility(bool a, bool b) {
    if (a == 1) {
        flags |= 2;
    } else {
        flags &= ~2;
    }
    if (b == 1) {
        flags |= 4;
    } else {
        flags &= ~4;
    }
}

bool GSgfxLayer::IsLayerVisible() {
    return flags & 1;
}

void GSgfxLayer::SetLayerVisibility(bool visible) {
    if (visible == 1) {
        visCount++;
    } else if (visCount != 0) {
        visCount--;
    }
}

GStexture* GSgfxLayer::GetFBTexture() {
    return fbTexPtr;
}

GSgfxLayer* GSgfxLayer::GetLayerList() {
    return _layerBottom;
}

extern "C" {
GSgfxLayer* GSgfxLayerGetLayerList() {
    return _layerBottom;
}
}

extern "C" {

int GSgfxLayerFindByID(int id) {
    if (id == -1) {
        return 0;
    }
    if (id >= 16) {
        return id;
    }
    return (int)_layerIDTable[id];
}

void GSgfxLayerSetActive(int id) {
    if (id >= 16) {
        return;
    }
    gsgfxState->activeLayer = (GSgfxLayerID)(int)_layerIDTable[id];
}

}

static inline GSgfxLayer* findByName(const char* name) {
    GSgfxLayer* l;
    for (l = _layerBottom; l != 0; l = l->next) {
        char buf[0x20];
        if ((u8)strlen(l->name) + 1 <= 0x20) {
            memcpy(buf, l->name, (u8)strlen(l->name) + 1);
        } else {
            memcpy(buf, l->name, 0x1f);
            buf[0x1f] = 0;
        }
        if (stricmp(buf, name) == 0) {
            return l;
        }
    }
    return 0;
}

GSgfxLayer::GSgfxLayer(GSgfxLayerID id, char* name, u32 w, u32 h, u32 depth, GSgfxLayerType type) {
    if (w == 0 && h == 0) {
        return;
    }
    if (name == 0 || findByName(name) != 0) {
        return;
    }
    if (depth == 0) {
        return;
    }
    this->id = id;
    flags = 7;
    visCount = 1;
    this->type = (GSgfxLayerType)0;
    SetLayerType(type);
    curPass = 2;
    u32 len = strlen(name) + 1;
    if (len > 0x20) {
        len = 0x20;
    }
    memcpy(this->name, name, len);
    this->name[len - 1] = 0;
    CreateFifo((GSgfxLayerPass)0, w);
    CreateFifo((GSgfxLayerPass)1, h);
    LoadHWState();
    GSgfx_GCInitState();
    memset((u8*)this + 0x30, 0, 0x1678);
    matrixStack = new GSgfxMatrixStack(depth);
    if (_layerBottom == 0) {
        _layerBottom = this;
        next = 0;
    } else {
        GSgfxLayer* l = _layerBottom;
        while (l->next != 0) {
            l = l->next;
        }
        next = l->next;
        l->next = this;
    }
    curVF = 0;
    unk1998 = 0x98;
    texCopy = 0;
    texCopyMode = 0;
    memset((u8*)this + 0x19b4, 0, 0x20);
    PrepareNextFrame();
    if (passes[0].data != 0) {
        if (curPass != 0) {
            curPass = 0;
            curFifo = &passes[curPass];
        }
    } else {
        if (curPass != 1) {
            curPass = 1;
            curFifo = &passes[curPass];
        }
    }
    _layerIDTable[this->id] = this;
}

void GSgfxLayer::PrepareNextFrame() {
    MarkAndInvalidate();
    switch ((int)type) {
    case 0:
        break;
    case 1:
        PrepareDistortion();
        break;
    case 4:
        PrepareFBCopy();
        break;
    }
    *(u32*)((u8*)this + 0x19dc) = 0;
    *(u32*)((u8*)this + 0x19ec) = 0;
    *(u32*)((u8*)this + 0x19fc) = 0;
    *(u32*)((u8*)this + 0x1a0c) = 0;
}

void GSgfxLayer::BuildRenderList() {
    BuildRenderListPass((GSgfxLayerPass)0);
    BuildRenderListPass((GSgfxLayerPass)1);
}

void GSgfxLayer::BuildRenderListPass(GSgfxLayerPass pass) {
    PassFifo* p = &passes[pass];
    if (p->pre != 0) {
        SendFifoToRenderer(p->pre);
    }
    if (passes[pass].data != 0 && p->flag == 0) {
        SendFifoToRenderer((_gsgfxLayerFifo*)p);
    }
    if (p->post != 0) {
        SendFifoToRenderer(p->post);
    }
}

GSgfxLayer* GSgfxLayerPrerender() {
    GSgfxLayer* l;
    GSgfxLayer* last;
    GSgfxRenderModuleDoRenderFast();
    for (l = _layerBottom; l != 0; l = l->next) {
        if (l->visCount != 0) {
            l->flags |= 1;
        } else {
            l->flags &= ~1;
        }
    }
    for (l = _layerBottom; l != 0; l = l->next) {
        l->Prerender();
        last = l;
    }
    return last;
}

void GSgfxLayerInit() {
    for (int i = 0; i < 16; i++) {
        _layerIDTable[i] = 0;
    }
    _layerBottom = 0;
    gsgfx_layer_inPrimitive = 0;
}

extern "C" {

int GSgfxLayerFindByName_C(const char* name) {
    GSgfxLayer* l = findByName(name);
    if (l == 0) {
        return -1;
    }
    return l->id;
}

GSgfxLayer* GSgfxLayerFindByName(const char* name) {
    GSgfxLayer* l;
    for (l = _layerBottom; l != 0; l = l->next) {
        char buf[0x20];
        if ((u8)strlen(l->name) + 1 <= 0x20) {
            memcpy(buf, l->name, (u8)strlen(l->name) + 1);
        } else {
            memcpy(buf, l->name, 0x1f);
            buf[0x1f] = 0;
        }
        if (stricmp(buf, name) == 0) {
            return l;
        }
    }
    return 0;
}

}

void GSgfxLayer::SetPassRedirect(GSgfxLayerPass pass, bool enable, GSgfxLayer* target, GSgfxLayerPass tpass,
                                 GSgfxLayerOffset off) {
    if (enable == 1) {
        PassFifo* src = &passes[pass];
        PassFifo* dst = &target->passes[tpass];
        _gsgfxLayerFifo** slot;
        if (off == LAYER_OFFSET_ABOVE) {
            slot = &dst->pre;
        } else {
            slot = &dst->post;
        }
        src->flag = 1;
        src->redirectId = target->id;
        src->redirectPass = tpass;
        src->redirectOffset = off;
        *slot = (_gsgfxLayerFifo*)src;
    } else {
        if (passes[pass].data == 0) {
            return;
        }
        PassFifo* src = &passes[pass];
        GSgfxLayer* t;
        if (src->flag == 0) {
            return;
        }
        int rid = src->redirectId;
        if (rid == -1) {
            t = 0;
        } else if (rid < 16) {
            t = _layerIDTable[rid];
        }
        PassFifo* dst = &t->passes[src->redirectPass];
        _gsgfxLayerFifo** slot;
        if (src->redirectOffset == LAYER_OFFSET_ABOVE) {
            slot = &dst->pre;
        } else {
            slot = &dst->post;
        }
        src->flag = 0;
        src->redirectId = -1;
        src->redirectPass = 2;
        src->redirectOffset = 0;
        *slot = 0;
    }
}

void GSgfxLayer::CreateFifo(GSgfxLayerPass pass, u32 size) {
    PassFifo* f = &passes[pass];
    f->data = 0;
    f->size = 0;
    memset(f->gxFifo, 0, 0x80);
    if ((int)id < 8) {
        f->color = _layerPerfColor[id];
    } else {
        f->color = _layerPerfUserColor[0];
    }
    f->unkAC = 0;
    f->unkAE = 0;
    f->unkB0 = 0;
    f->unkB4 = 0;
    f->unkB8 = 0;
    f->unk88 = 0;
    f->unk8c = 0;
    f->flag = 0;
    f->redirectId = -1;
    f->redirectPass = 2;
    f->redirectOffset = 0;
    f->pre = 0;
    f->post = 0;
    if (size != 0) {
        f->size = (size + 0x1f) & ~0x1f;
        f->data = GSmemAlloc(f->size);
        DCFlushRange(f->data, f->size);
        GSgfxGPUInitFifoBase((GSgfx_GCFifoObj*)f->gxFifo, f->data, f->size);
        GXInitFifoPtrs((GSgfx_GCFifoObj*)f->gxFifo, f->data, f->data);
        if (gsgfx_gpu_mode == 0) {
            gsgfx_layer_activeFifo = f;
            GSgfxGPUEnterBufferedMode((GSgfx_GCFifoObj*)f->gxFifo);
        }
    }
}

void GSgfxLayer::SetPriority(GSgfxLayerOffset offset, GSgfxLayer* relative) {
    GSgfxLayer* l;
    if (_layerBottom == this) {
        _layerBottom = next;
    } else {
        for (l = _layerBottom; l != 0; l = l->next) {
            if (l->next == this) {
                l->next = next;
                break;
            }
        }
    }
    switch (offset) {
    case LAYER_OFFSET_NONE:
        break;
    case LAYER_OFFSET_ABOVE:
        l = _layerBottom;
        if (l == 0 || l == relative) {
            _layerBottom = this;
            next = l;
            return;
        }
        while (l->next != 0) {
            if (l->next == relative) {
                break;
            }
            l = l->next;
        }
        next = l->next;
        l->next = this;
        return;
    case LAYER_OFFSET_BELOW:
        for (l = _layerBottom; l != 0; l = l->next) {
            if (l == relative) {
                next = l->next;
                l->next = this;
                return;
            }
        }
        return;
    case LAYER_OFFSET_TOP:
        next = _layerBottom;
        _layerBottom = this;
        return;
    case LAYER_OFFSET_BOTTOM:
        l = _layerBottom;
        next = 0;
        if (l == 0) {
            _layerBottom = this;
            return;
        }
        for (; l->next != 0; l = l->next) {
        }
        l->next = this;
        return;
    }
}

void GSgfxLayer::SetLayerType(GSgfxLayerType newType) {
    bool oldDist = false;
    bool newDist = false;
    bool oldFB = false;
    bool newFB = false;
    if (newType != type) {
        switch ((int)type) {
        case 1:
            oldDist = true;
            oldFB = true;
            break;
        case 4:
            oldFB = true;
            break;
        }
        switch ((int)newType) {
        case 1:
            distParams[0] = 0.0f;
            distParams[1] = 0.5f;
            distParams[2] = 0.0f;
            distParams[3] = 0.0f;
            distParams[4] = 0.5f;
            distParams[5] = 0.0f;
            distFlag = 0;
            newDist = true;
            newFB = true;
            break;
        case 4:
            newFB = true;
            break;
        }
        if (oldFB && !newFB) {
            fbTexRefCount--;
            if (fbTexRefCount == 0) {
                GStextureFree(fbTexPtr);
                fbTexPtr = 0;
            }
        } else if (!oldFB && newFB) {
            fbTexRefCount++;
            if (fbTexRefCount == 1) {
                fbTexPtr = GStextureCreate(0, 0, 0x45, 0, 0);
                if (fbTexPtr == 0) {
                    type = (GSgfxLayerType)0;
                    fbTexRefCount = 0;
                    return;
                }
            }
        }
        if (oldDist && !newDist) {
            distTexRefCount--;
            if (distTexRefCount == 0) {
                GStextureFree(distTexPtr);
                distTexPtr = 0;
            }
        } else if (!oldDist && newDist) {
            distTexRefCount++;
            if (distTexRefCount == 1) {
                distTexPtr = GStextureCreate(0, 0, 0xa3, 0, 0);
                if (distTexPtr == 0) {
                    type = (GSgfxLayerType)0;
                    distTexRefCount = 0;
                    fbTexRefCount--;
                    if (fbTexRefCount == 0) {
                        GStextureFree(fbTexPtr);
                        fbTexPtr = 0;
                    }
                    return;
                }
            }
        }
        type = newType;
    }
}

static inline bool fifoBusy(GSgfx_GCFifoObj* o) {
    if (o->breakpointReached == 1) {
        return false;
    }
    u32 count;
    if (o->write >= o->read) {
        count = o->write - o->read;
    } else {
        count = (o->end - o->read) + (o->write - o->base);
    }
    return count > o->hi;
}

void GSgfxLayerUpdateActiveFifoStats() {
    if (gsgfx_gpu_mode == 1) {
        return;
    }
    GSgfxLayer::PassFifo* f = (GSgfxLayer::PassFifo*)gsgfx_layer_activeFifo;
    if (f == 0) {
        return;
    }
    GSgfx_GCFifoObj* obj = (GSgfx_GCFifoObj*)f->gxFifo;
    GXSaveCPUFifo(obj);
    union {
        u32 v;
    } r;
    r.v = *(volatile u32*)0xCC003014;
    u32 bit = (r.v >> 26) & 1;
    if (bit == 1) {
        GXSetCPUFifo(GSgfxGPUGetImmediateFifo());
        GXSetCPUFifo(obj);
    }
    if (bit == 1) {
        f->unkAC++;
    }
    u32 rd = f->unk88;
    u32 used;
    if (rd == 0) {
        used = 0;
    } else {
        u32 wr = obj->write;
        if (wr >= rd) {
            used = wr - rd + f->unkAC * f->size;
        } else {
            used = ((u32)f->data + f->size - rd) + (wr - (u32)f->data);
            if (f->unkAC == 0) {
                GSlogWrite("fifo wrap check flag failure!\n");
                GSlogWrite("ptr  =%08X, size =%08X\n", f->data, f->size);
                GSlogWrite("start=%08X, write=%08X\n", f->unk88, wr);
                GSlogWrite("reg  =%08X\n", *(volatile u32*)0xCC003014);
                f->unkAC++;
            }
            used += (f->unkAC - 1) * f->size;
        }
    }
    f->unkB4 = used;
    if (f->unkB4 > f->unkB8) {
        f->unkB8 = f->unkB4;
    }
    if (f->unkB4 >= f->size) {
        f->unkAE = 1;
    }
    GXResetWriteGatherPipe();
    GSgfxRenderWaitData w;
    GSgfxRenderWaitInit(&w);
    while (fifoBusy(obj) == 1) {
        GSgfxRenderWaitTick(&w);
    }
    GSgfxRenderWaitExit(&w);
}
