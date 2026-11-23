#include <dolphin/types.h>
#include <game/gcptr.h>
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
enum ASM { ASM_draft_dummy };
struct GXFifoObj;
#ifdef __MWERKS__
#endif
typedef f32 Mtx44[4][4];
struct StatCol { u8 r, g, b, a; };
#pragma pool_strings off

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
    void* mBase;
    void* mTop;
    void* mLast;
public:
    ~GSgfxMatrixStack();
};

#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
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

    static GStexture* fbTexPtr;
    static u16 fbTexRefCount;
    static GStexture* distTexPtr;
    static u16 distTexRefCount;
public:
#ifdef __MWERKS__
    s32 EffectTextureCopy(GStexture*, bool, unsigned char*, bool, bool, bool);
#else
    void EffectTextureCopy(GStexture* tex, bool filter, unsigned char* coeffs, bool r, bool g, bool b);
#endif
    void SetupFifo();
    ~GSgfxLayer();
#ifdef __MWERKS__
    s32 EffectScreenClear(bool, bool, bool);
#else
    void EffectScreenClear(bool p0, bool p1, bool p2);
#endif
#ifdef __MWERKS__
    s32 EffectDistortion();
#else
    void EffectDistortion();
#endif
};

#include <game/gsgfxfifo.h>
#ifdef __MWERKS__
#define CPU_FIFO_WRITE_REG (*(volatile u32*)0xCC003014)
#else
#define CPU_FIFO_WRITE_REG PortGX_ReadCPUFifoWriteReg()
#endif
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
#include <game/gsgfxstate.h>
#include <game/ppcops.h>
#include "game/gcdata.h"
extern "C" GSgfxState* gsgfxState;

extern "C" u8 gsgfx_layer_inPrimitive;
extern "C" void* gsgfx_layer_activeFifo;
void* gsgfx_layer_activeFifo;
u8 gsgfx_layer_inPrimitive;
static GSgfxLayer* _layerBottom;
static u8 _layerRenderStats;
static u32 _layerPerfColor[8] = {0xFF, 0x8000, 0x800000, 0x8080, 0x800080, 0x808000, 0x80FF, 0x808080};
static u32 _layerPerfUserColor[2] = {0xFF8000, 0};
static GSgfxLayer* _layerIDTable[16];

extern "C" {

extern "C++" {
struct GXFifoObj {
    u8 _draft[1];
};

extern "C" {
void GSmemFree(void* ptr);
void GSmtx44Ortho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void GSprimDraw2DHLine(StatCol color, f32 x0, f32 x1, f32 y);
void GSprimDraw2DQuadWH(StatCol color, f32 x, f32 y, f32 w, f32 h);
void GSprimSetLineWidth(f32 w);
void GSprimSetQuadVertexOrder(s32 order);
void GSprimSetTextColor(StatCol color);
void GSprimSetTextSize(f32 xpel, f32 ypel);
void GSprimSetTextWidth(f32 w);
void GSprimWriteChar(char c, f32 x, f32 y);
void GSprimWriteStr(f32 x, f32 y, char* fmt, ...);
GXFifoObj* GXGetCPUFifo(void);
extern u8* _layerStateLastHWState;
#ifdef __MWERKS__
extern GStexture* fbTexPtr__10GSgfxLayer;
extern u16 fbTexRefCount__10GSgfxLayer;
#else
#define fbTexPtr__10GSgfxLayer GSgfxLayer::fbTexPtr
#define distTexPtr__10GSgfxLayer GSgfxLayer::distTexPtr
#define fbTexRefCount__10GSgfxLayer GSgfxLayer::fbTexRefCount
#define distTexRefCount__10GSgfxLayer GSgfxLayer::distTexRefCount
#endif
extern f32 mtxIdent[3][4];
#ifdef __MWERKS__
extern StatCol c_localstatic3_GSgfxPerfColorToGSgfxCol;
#else
static StatCol c_localstatic3_GSgfxPerfColorToGSgfxCol;
#endif
}
extern "C++" {
#ifdef __MWERKS__
s32 GSgfxGPUSetFifoWritePtr(GSgfx_GCFifoObj*, void*);
#else
void GSgfxGPUSetFifoWritePtr(GSgfx_GCFifoObj* f, void* ptr);
#endif
void GSgfxLayerBuildRenderList();
void GSgfxLayerRenderStats(GSgfxLayer* p0);
void GSgfxRenderAddToFifoList(GSgfx_GCFifoObj*, void*, void*, u32, void (*)(void*), void*);
void GSgfxRenderModuleDoRender(GSgfxLayer* layer, GSgfxLayerPass pass);
#ifdef __MWERKS__
s32 GSgfxRenderWaitForDrawComplete();
#else
void GSgfxRenderWaitForDrawComplete();
#endif
void GSprimSetRenderLayer(GSgfxLayer* layer);
}

static inline void layerClearRedirect(GSgfxLayer::PassFifo* src) {
    GSgfxLayer* t;
    int rid = src->redirectId;
    if (rid == -1) {
        t = 0;
    } else if (rid < 16) {
        t = _layerIDTable[rid];
    }
    GSgfxLayer::PassFifo* dst = &t->passes[src->redirectPass];
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

#define FIFO_OBJ(f) ((GSgfx_GCFifoObj*)(f)->gxFifo)

static inline bool fifoBusy(GSgfx_GCFifoObj* o) {
    u32 count;
    if (o->breakpointReached == 1) {
        return false;
    }
    if ((u32)o->write >= (u32)o->read) {
        count = (u32)o->write - (u32)o->read;
    } else {
        count = (u32)o->end - (u32)o->read;
        count += (u32)o->write - (u32)o->base;
    }
    return count >= o->hi;
}

static inline void layerCalcFifoUsage(GSgfxLayer::PassFifo* f) {
    u32 used;
    u32 wr;
    u32 rd;

    rd = f->unk88;
    if (rd == 0) {
        used = 0;
    } else {
        wr = (u32)FIFO_OBJ(f)->write;
        if (wr >= rd) {
            used = wr - rd;
            used += f->unkAC * f->size;
        } else {
            used = (u32)f->data + f->size - rd;
            used += wr - (u32)f->data;
            if (f->unkAC == 0) {
                GSlogWrite("fifo wrap check flag failure!\n");
                GSlogWrite("ptr  =%08X, size =%08X\n", f->data, f->size);
                GSlogWrite("start=%08X, write=%08X\n", f->unk88, wr);
                GSlogWrite("reg  =%08X\n", CPU_FIFO_WRITE_REG);
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
}

static inline void layerFlushFifo(GSgfxLayer::PassFifo* f) {
    union {
        volatile u32 v;
    } r;
    GSgfx_GCFifoObj* obj = FIFO_OBJ(f);
    u32 bit;
    u32 used;
    u32 rd;
    u32 wr;
    GSgfxRenderWaitData w;

    GXSaveCPUFifo(obj);
    r.v = CPU_FIFO_WRITE_REG;
    bit = (r.v >> 26) & 1;
    if (bit == 1) {
        GXSetCPUFifo(GSgfxGPUGetImmediateFifo());
        GXSetCPUFifo(obj);
    }
    if (bit == 1) {
        f->unkAC++;
    }
    rd = f->unk88;
    if (rd == 0) {
        used = 0;
    } else {
        wr = (u32)FIFO_OBJ(f)->write;
        if (wr >= rd) {
            used = wr - rd;
            used += f->unkAC * f->size;
        } else {
            used = (u32)f->data + f->size - rd;
            used += wr - (u32)f->data;
            if (f->unkAC == 0) {
                GSlogWrite("fifo wrap check flag failure!\n");
                GSlogWrite("ptr  =%08X, size =%08X\n", f->data, f->size);
                GSlogWrite("start=%08X, write=%08X\n", f->unk88, wr);
                GSlogWrite("reg  =%08X\n", CPU_FIFO_WRITE_REG);
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
    GSgfxRenderWaitInit(&w);
    while (fifoBusy(FIFO_OBJ(f)) == 1) {
        GSgfxRenderWaitTick(&w);
    }
    GSgfxRenderWaitExit(&w);
}

static inline void layerUpdateActiveFifoStats() {
    GSgfxLayer::PassFifo* f;

    if (gsgfx_gpu_mode == 1 || (f = (GSgfxLayer::PassFifo*)gsgfx_layer_activeFifo) == NULL) {
        return;
    }
    layerFlushFifo(f);
}

static inline void layerSetupFifo(GSgfxLayer* layer) {
    if (gsgfx_gpu_mode == 2 && (GSgfxLayer::PassFifo*)gsgfx_layer_activeFifo != layer->curFifo) {
        layerUpdateActiveFifoStats();
        GXSetCPUFifo(FIFO_OBJ(layer->curFifo));
        gsgfx_layer_activeFifo = layer->curFifo;
        gsgfxState->layer = layer;
    }
}

struct RedirectLegend {
    char sym;
    GSgfxLayer* layer;
    s32 pass;
    s32 offset;
};

static inline StatCol* perfColor(u32 color) {
    static StatCol c;
    c.g = color >> 8;
    c.b = color;
    c.r = color >> 16;
    c.a = 0xFF;
    return &c;
}

struct StatMtxEntry {
    u32 flags;
    f32 m[3][4];
};

static inline bool statsLegendFill(GSgfxLayer::PassFifo& pf, RedirectLegend* e) {
#ifdef __MWERKS__
    GSgfxLayer* target;
#else
    GSgfxLayer* target = NULL;
#endif
    if (pf.data == NULL) {
        return false;
    }
    if (pf.flag == 0) {
        return false;
    }
    if (&e->layer != NULL) {
        if (pf.redirectId == -1) {
            target = NULL;
        } else if (pf.redirectId < 0x10) {
            target = _layerIDTable[pf.redirectId];
        }
        e->layer = target;
    }
    if (&e->pass != NULL) {
        e->pass = pf.redirectPass;
    }
    if (&e->offset != NULL) {
        e->offset = pf.redirectOffset;
    }
    return true;
}

#ifdef __MWERKS__
#define LEGEND_AT(off) ((RedirectLegend*)((u8*)legend + (off)))
#else
#define LEGEND_AT(off) (&legend[(off) >> 4])
#endif

void GSgfxLayerRenderStats(GSgfxLayer* p0) {
    RedirectLegend legend[4] = {
        { '#', NULL, 2, 0 },
        { '$', NULL, 2, 0 },
        { '=', NULL, 2, 0 },
        { '+', NULL, 2, 0 },
    };
    Mtx44 ortho;
    char nameBuf[0x20];
    char tcaz[5];
    StatCol colBg = { 0x20, 0x20, 0x20, 0xC0 };
    u32 limit0, limit1, used0, used1, size0, size1;
    StatCol colLine = { 0x60, 0x60, 0x60, 0xFF };
    StatCol colDim = { 0xA0, 0xA0, 0xA0, 0xFF };
    StatCol colText = { 0xFF, 0xFF, 0xFF, 0xFF };
    StatCol colHead = { 0xFF, 0xFF, 0x00, 0xFF };
    StatCol colMark = { 0xE0, 0x40, 0x40, 0xFF };
    u8 bFlag1, bFlag2, bR0, bR1, bR2, bNextC, bNextB, bNextA;
    bool r0v, r1v, r2v;
    f32 y;
    GSgfxMatrixStack* ms;
    GSgfxLayer* cur;
    s32 numLayers;
    s32 legendCount;
    s32 legendOff;
    s32 i;
    GSgfxLayer* next;

    f32 kb = 0.0009765625f;
    if (_layerRenderStats == 0) {
        return;
    }
    legendCount = 0;
    legendOff = 0;
    GSprimSetRenderLayer(p0);
    GSprimSetQuadVertexOrder(0);
    GSprimSetLineWidth(1.0f);
    GSprimSetTextSize(10.0f, 10.0f);
    GSprimSetTextWidth(1.0f);
    p0->hw.blend[0] = 1;
    p0->hw.blend[1] = 4;
    p0->hw.blend[2] = 5;
    p0->hw.blend[3] = 5;
    p0->dirty[0].pe |= 1;
    p0->dirty[0].groups |= 0x40;
    p0->dirty[1].pe |= 1;
    p0->dirty[1].groups |= 0x40;
    GSmtx44Ortho(ortho, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    p0->hw.projType = 1;
    p0->hw.proj[0] = ortho[0][0];
    p0->hw.proj[1] = ortho[0][3];
    p0->hw.proj[2] = ortho[1][1];
    p0->hw.proj[3] = ortho[1][3];
    p0->hw.proj[4] = ortho[2][2];
    p0->hw.proj[5] = ortho[2][3];
    ms = p0->matrixStack;
    memcpy(&((StatMtxEntry*)ms->mTop)->m, mtxIdent, 0x30U);
    ((StatMtxEntry*)ms->mTop)->flags |= 1;
    p0->hw.fogNear = 0.0f;
    p0->hw.fogFar = 30000.0f;
    if (p0->hw.fogEnable != 0) {
        if (p0->hw.fogRangeEnable != 0) {
            p0->dirty[0].pe |= 0x100;
            p0->dirty[1].pe |= 0x100;
        }
        p0->dirty[0].pe |= 0x40;
        p0->dirty[0].groups |= 0x40;
        p0->dirty[1].pe |= 0x40;
        p0->dirty[1].groups |= 0x40;
    }
    p0->dirty[0].geom |= 0x20;
    p0->dirty[0].groups |= 1;
    p0->dirty[1].geom |= 0x20;
    p0->dirty[1].groups |= 1;
    p0->hw.colorUpdate = 1;
    p0->hw.alphaUpdate = 0;
    p0->hw.zUpdate = 0;
    p0->dirty[0].pe |= 4;
    p0->dirty[0].groups |= 0x40;
    p0->dirty[1].pe |= 4;
    p0->dirty[1].groups |= 0x40;
    p0->hw.zEnable = 0;
    p0->hw.zFunc = 3;
    p0->dirty[0].pe |= 8;
    p0->dirty[0].groups |= 0x40;
    p0->dirty[1].pe |= 8;
    p0->dirty[1].groups |= 0x40;
    p0->hw.alphaComp0 = 7;
    p0->hw.alphaRef0 = 0;
    p0->hw.alphaCmpOp = 0;
    p0->hw.alphaComp1 = 7;
    p0->hw.alphaRef1 = 0;
    p0->hw.zCompLoc = 1;
    p0->dirty[0].pe |= 0x10;
    p0->dirty[0].groups |= 0x40;
    p0->dirty[1].pe |= 0x10;
    p0->dirty[1].groups |= 0x40;
    p0->hw.cullMode = 0;
    p0->dirty[0].raster |= 2;
    p0->dirty[0].groups |= 2;
    p0->dirty[1].raster |= 2;
    p0->dirty[1].groups |= 2;
    p0->hw.clipMode = 1;
    p0->dirty[0].raster |= 4;
    p0->dirty[0].groups |= 2;
    p0->dirty[1].raster |= 4;
    p0->dirty[1].groups |= 2;

    numLayers = 0;
    for (cur = _layerBottom; cur != NULL; cur = cur->next) {
        numLayers++;
    }
    GSprimDraw2DQuadWH(colBg, 10.0f, 22.0f, 620.0f, 12.0f * (f32)numLayers + 28.0f);
    GSprimSetTextColor(colText);
    GSprimSetTextSize(10.0f, 10.0f);
    GSprimWriteStr(25.0f, 29.0f, "#");
    GSprimWriteStr(50.0f, 29.0f, "ID");
    GSprimWriteStr(85.0f, 29.0f, "Name");
    GSprimWriteStr(245.0f, 29.0f, "TCAZ");
    GSprimWriteStr(295.0f, 29.0f, "Opaque");
    GSprimWriteStr(470.0f, 29.0f, "Xluc");
    GSprimDraw2DHLine(colHead, 20.0f, 620.0f, 42.0f);
    cur = _layerBottom;
    i = 0;
    while (cur != NULL) {
        s32 id = cur->id;
        f32 x;
        next = cur->next;
        y = 12.0f * (f32)i + 47.0f;
        GSprimDraw2DQuadWH(*perfColor(id < 8 ? _layerPerfColor[id] : _layerPerfUserColor[0]), 20.0f, y - 1.0f, 50.0f, 12.0f);
        GSprimSetTextColor(colText);
        GSprimWriteStr(25.0f, y, "%d", i);
        GSprimWriteStr(55.0f, y, "%d", id);
        if (&bFlag1 != NULL) {
            bFlag1 = (cur->flags >> 1) & 1;
        }
        if (&bFlag2 != NULL) {
            bFlag2 = (cur->flags >> 2) & 1;
        }
        if ((cur->flags & 1) != 1) {
            GSprimSetTextColor(colLine);
            bFlag1 = 0;
            bFlag2 = 0;
        }
        GSprimSetTextSize(8.5f, 10.0f);
        if ((u8)strlen(cur->name) + 1 <= 0x13) {
            memcpy(nameBuf, cur->name, (u8)strlen(cur->name) + 1);
        } else {
            memcpy(nameBuf, cur->name, 0x12);
            nameBuf[0x12] = 0;
        }
        GSprimWriteStr(85.0f, y, "%s", nameBuf);
        GSprimSetTextSize(10.0f, 10.0f);
        tcaz[0] = ((cur->flags & 0x200) ? cur->texCopy : NULL) != NULL ? 'O' : 'X';
        if (cur->next == NULL) {
            r2v = r1v = r0v = 0;
        } else {
            GSgfxLayer* n = cur->next;
            u32 fl;
            u8 t;
            if (&bNextA != NULL) {
                bNextA = (n->flags >> 6) & 1;
            }
            if (&bNextB != NULL) {
                bNextB = (n->flags >> 7) & 1;
            }
            if (&bNextC != NULL) {
                bNextC = (n->flags >> 8) & 1;
            }
            fl = cur->flags;
            t = 0;
            if ((fl & 8) || bNextA != 0) {
                t = 1;
            }
            r0v = t != 0;
            t = 0;
            t = !((fl & 0x10) || bNextB != 0) ? t : 1;
            r1v = t != 0;
            t = 0;
            t = !((fl & 0x20) || bNextC != 0) ? t : 1;
            r2v = t != 0;
        }
        if (&bR0 != NULL) {
            bR0 = r0v;
        }
        if (&bR1 != NULL) {
            bR1 = r1v;
        }
        if (&bR2 != NULL) {
            bR2 = r2v;
        }
        if (bR0 == 1) {
            tcaz[1] = 'O';
        } else {
            tcaz[1] = 'X';
        }
        if (bR1 == 1) {
            tcaz[2] = 'O';
        } else {
            tcaz[2] = 'X';
        }
        if (bR2 == 1) {
            tcaz[3] = 'O';
        } else {
            tcaz[3] = 'X';
        }
        if (next != NULL && (next->flags & 1) == 1) {
            switch (next->type) {
            case 1:
                tcaz[1] = '+';
                tcaz[2] = '+';
            case 4:
                tcaz[0] = '+';
                break;
            }
        }
        tcaz[4] = 0;
        GSprimWriteStr(245.0f, y, tcaz);
        if (&limit0 != NULL) {
            if (cur->passes[0].data != NULL) {
                limit0 = cur->passes[0].unkB0;
            } else {
                limit0 = 0;
            }
        }
        if (&limit1 != NULL) {
            if (cur->passes[1].data != NULL) {
                limit1 = cur->passes[1].unkB0;
            } else {
                limit1 = 0;
            }
        }
        if (&used0 != NULL) {
            if (cur->passes[0].data != NULL) {
                used0 = cur->passes[0].unkB8;
            } else {
                used0 = 0;
            }
        }
        if (&used1 != NULL) {
            if (cur->passes[1].data != NULL) {
                used1 = cur->passes[1].unkB8;
            } else {
                used1 = 0;
            }
        }
        if (&size0 != NULL) {
            size0 = cur->passes[0].size;
        }
        if (&size1 != NULL) {
            size1 = cur->passes[1].size;
        }

        x = 295.0f;
        if (statsLegendFill(cur->passes[0], LEGEND_AT(legendOff)) == 1) {
            GSprimSetTextColor(colMark);
            GSprimWriteChar(LEGEND_AT(legendOff)->sym, 295.0f, y);
            legendCount++;
            legendOff += 0x10;
            x = 11.0f;
            x += 295.0f;
        }
        GSprimSetTextColor(colText);
        if (size0 != 0) {
            if (bFlag1 == 0) {
                GSprimSetTextColor(colLine);
            } else if (limit0 == 0) {
                GSprimSetTextColor(colDim);
            }
            if (limit0 != 0) {
                GSprimWriteStr(x, y, "%.1f/%dK (%dK)", GC_F2U32((f32)size0 * kb), GC_F2U32((f32)used0 * kb + 0.5f), (f32)limit0 * kb);
            } else {
                GSprimWriteStr(x, y, "---/%dK (%dK)", GC_F2U32((f32)size0 * kb), GC_F2U32((f32)used0 * kb + 0.5f));
            }
        }
        x = 470.0f;
        if (statsLegendFill(cur->passes[1], LEGEND_AT(legendOff)) == 1) {
            GSprimSetTextColor(colMark);
            GSprimWriteChar(LEGEND_AT(legendOff)->sym, 470.0f, y);
            legendCount++;
            legendOff += 0x10;
            x = 470.0f + 11.0f;
        }
        GSprimSetTextColor(colText);
        if (size1 != 0) {
            if (bFlag2 == 0) {
                GSprimSetTextColor(colLine);
            } else if (limit1 == 0) {
                GSprimSetTextColor(colDim);
            }
            if (limit1 != 0) {
                GSprimWriteStr(x, y, "%.1f/%dK (%dK)", GC_F2U32((f32)size1 * kb), GC_F2U32((f32)used1 * kb + 0.5f), (f32)limit1 * kb);
            } else {
                GSprimWriteStr(x, y, "---/%dK (%dK)", GC_F2U32((f32)size1 * kb), GC_F2U32((f32)used1 * kb + 0.5f));
            }
        }
        cur = next;
        i++;
    }
    if (legendCount > 0) {
        s32 k;
        GSprimDraw2DQuadWH(colBg, 10.0f, 12.0f * (f32)i + 50.0f, 620.0f, 12.0f * (f32)legendCount + 4.0f);
        y += 18.0f;
        for (k = 0; k < legendCount; k++) {
            RedirectLegend* e = &legend[k];
            GSprimSetTextColor(colMark);
            GSprimWriteChar(e->sym, 40.0f, y);
            GSprimSetTextColor(colText);
            if ((u8)strlen(e->layer->name) + 1 <= 0x13) {
                memcpy(nameBuf, e->layer->name, (u8)strlen(e->layer->name) + 1);
            } else {
                memcpy(nameBuf, e->layer->name, 0x12);
                nameBuf[0x12] = 0;
            }
            GSprimWriteStr(60.0f, y, "redirected %s: %s %s pass", e->offset == 1 ? "before" : "after", nameBuf, e->pass == 0 ? "opaque" : "xluc");
            y += 12.0f;
        }
    }
}
}
u8 GSgfxLayerGetStatsRenderMode() {
    return _layerRenderStats;
}

void GSgfxLayerSetStatsRenderMode(u8 mode) {
    _layerRenderStats = mode;
}
extern "C++" {
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

void GSgfxLayerBuildRenderList() {
    GSgfxLayer* l;

    if (_layerBottom != NULL) {
        layerUpdateActiveFifoStats();
        for (l = _layerBottom; l != NULL; l = l->next) {
            l->BuildRenderList();
        }
    }
}

extern "C" {

int GSgfxLayerGetActive() {
    for (int i = 0; i < 16; i++) {
        if ((GSgfxLayer*)_layerIDTable[i] == gsgfxState->layer) {
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

GSgfxLayer* GSgfxLayerFindByID(GCsint id) {
    if (id == -1) {
        return 0;
    }
    if (id >= 16) {
        return (GSgfxLayer*)id;
    }
    return (GSgfxLayer*)_layerIDTable[id];
}

void GSgfxLayerSetActive(int id) {
    if (id >= 16) {
        return;
    }
    gsgfxState->layer = _layerIDTable[id];
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
    memset(hwState, 0, (u32)((u8*)((GSgfxLayerData*)0)->dirty - (u8*)((GSgfxLayerData*)0)->hwState));
    matrixStack = (GC_NEW_NOTE(sizeof(GSgfxMatrixStack), 12) new GSgfxMatrixStack(depth));
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
    memset(pad19b4, 0, 0x20);
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
    hooks[0].callback = 0;
    hooks[1].callback = 0;
    hooks[2].callback = 0;
    hooks[3].callback = 0;
}

void GSgfxLayer::BuildRenderList() {
    BuildRenderListPass((GSgfxLayerPass)0);
    BuildRenderListPass((GSgfxLayerPass)1);
}
extern "C++" {
void GSgfxLayer::SendFifoToRenderer(_gsgfxLayerFifo* fifo) {
    PassFifo* f = (PassFifo*)fifo;
    u32* start;
    u32 n;
    bool empty;
    int i;
    RenderHook* hook;

    if (f->data != NULL) {
        if (FIFO_OBJ(f) == (GSgfx_GCFifoObj*)GXGetCPUFifo()) {
            layerFlushFifo(f);
        }
        f->unk8c = (u32)FIFO_OBJ(f)->write;
    }
    start = PC_PTR(u32*, f->unk88);
    n = f->unk8c - (u32)start;
    if (n == 0) {
        empty = 1;
    } else if (n != 0x20) {
        empty = 0;
    } else {
        empty = (start[0] | start[1] | start[2] | start[3] | start[4] | start[5] | start[6] | start[7]) == 0;
    }
    if (empty == 1) {
        GSgfxGPUSetFifoWritePtr(FIFO_OBJ(f), start);
        f->unk8c = f->unk88;
        f->unkAC = 0;
        f->unkAE = 0;
    }
    layerCalcFifoUsage(f);
    if (f->unkAE == 1) {
        GSlogWrite("fifo overflow in [%s]: %s pass", name, curPass == 0 ? "opaque" : "xluc");
        return;
    }
    start = PC_PTR(u32*, f->unk88);
    for (i = 0; i < 4; i++) {
        hook = &hooks[i];
        if (hook->callback == NULL) {
            break;
        }
        if (&passes[hook->pass] == f) {
            GSgfxRenderAddToFifoList(FIFO_OBJ(f), start, hook->end, f->color, hook->callback, hook->arg);
            start = (u32*)hook->end;
        }
    }
    GSgfxRenderAddToFifoList(FIFO_OBJ(f), start, PC_PTR(void*, f->unk8c), f->color, NULL, NULL);
}
}

extern "C++" {
void GSgfxLayer::Prerender() {
    bool spD;
    bool spC;
    bool spB;
    u8 spA;
    u8 sp9;
    bool var_r6;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r7;
    bool var_r3;
    u8 var_r3_2;
    u8 var_r3_3;
    u8 var_r3_4;
    bool var_r4;
    u8 sp8;
    GSgfxLayer* temp_r3;

    ((GSgfxLayer*)(this))->PrerenderPass((GSgfxLayerPass)(0));
    ((GSgfxLayer*)(this))->PrerenderPass((GSgfxLayerPass)(1));
    temp_r3 = next;
    if (temp_r3 == NULL) {
        var_r3 = var_r4 = var_r6 = 0;
    } else {
        if (&sp8 != NULL) {
            sp8 = ((u32) temp_r3->flags >> 6U) & 1;
        }
        if (&sp9 != NULL) {
            sp9 = ((u32) temp_r3->flags >> 7U) & 1;
        }
        if (&spA != NULL) {
            spA = ((u32) temp_r3->flags >> 8U) & 1;
        }
        temp_r7 = flags;
        var_r3_2 = 0;
        if ((temp_r7 & 8) || (sp8 != 0)) {
            var_r3_2 = 1;
        }
        var_r3_3 = 0;
        var_r6 = var_r3_2 != 0;
        var_r3_3 = !((temp_r7 & 0x10) || (sp9 != 0)) ? var_r3_3 : 1;
        var_r3_4 = 0;
        var_r4 = var_r3_3 != 0;
        var_r3_4 = !((temp_r7 & 0x20) || (spA != 0)) ? var_r3_4 : 1;
        var_r3 = var_r3_4 != 0;
    }
    if (&spD != NULL) {
        spD = var_r6;
    }
    if (&spC != NULL) {
        spC = var_r4;
    }
    if (&spB != NULL) {
        spB = var_r3;
    }
    if (passes[1].data != NULL) {
        if (curPass != 1) {
            curPass = 1;
            curFifo = &passes[curPass];
        }
    } else if (curPass != 0) {
        curPass = 0;
        curFifo = &passes[curPass];
    }
    if (flags & 1) {
        temp_r0 = type;
        switch (temp_r0) {
        case 0:
            break;
        case 1:
            ((GSgfxLayer*)(this))->EffectDistortion();
            break;
        case 4:
            break;
        }
    }
    if (flags & 0x200) {
        temp_r0_2 = texCopyMode;
        switch (temp_r0_2) {
        case 0:
            ((GSgfxLayer*)(this))->EffectTextureCopy(texCopy, 0U, (unsigned char*)(NULL), spD, spC, spB);
            return;
        case 1:
            ((GSgfxLayer*)(this))->EffectTextureCopy(texCopy, 1U, (unsigned char*)(NULL), spD, spC, spB);
            return;
        case 2:
            ((GSgfxLayer*)(this))->EffectTextureCopy(texCopy, 1U, texCopyData, spD, spC, spB);
            return;
        }
    } else {
        ((GSgfxLayer*)(this))->EffectScreenClear(spD, spC, spB);
    }
}
}

extern "C++" {
void GSgfxLayer::PrerenderPass(GSgfxLayerPass pass) {
    PassFifo* active;
    PassFifo* f;
    u32 mask;

    if (passes[pass].data != NULL) {
        mask = 5;
        if (pass == 0) {
            mask = 3;
        }
        if (mask == (mask & flags)) {
            if (curPass != pass) {
                curPass = pass;
                curFifo = &passes[curPass];
            }
            layerSetupFifo(this);
            GSgfxRenderModuleDoRender(this, pass);
            return;
        }
        f = &passes[pass];
        if (f == (active = (PassFifo*)gsgfx_layer_activeFifo)) {
            layerFlushFifo(active);
        }
        GSgfxGPUSetFifoWritePtr(FIFO_OBJ(f), PC_PTR(void*, passes[pass].unk88));
        passes[pass].unk8c = passes[pass].unk88;
        passes[pass].unkAC = 0;
        passes[pass].unkAE = 0;
        InvalidateState();
    }
}
}

extern "C++" {
GSgfxLayer::~GSgfxLayer() {
    PassFifo* fifo;
    GSgfxLayer* l;

    GSgfxRenderWaitForDrawComplete();
    if (passes[0].data != NULL && passes[0].flag != 0) {
        layerClearRedirect(&passes[0]);
    }
    if (passes[1].data != NULL && passes[1].flag != 0) {
        layerClearRedirect(&passes[1]);
    }
    SetLayerType((GSgfxLayerType)0);
    flags &= ~0x200;
    if (fbTexPtr__10GSgfxLayer != NULL && texCopy == fbTexPtr__10GSgfxLayer) {
        fbTexRefCount__10GSgfxLayer--;
        if (fbTexRefCount__10GSgfxLayer == 0) {
            GStextureFree(fbTexPtr__10GSgfxLayer);
            fbTexPtr__10GSgfxLayer = NULL;
        }
    }
    texCopy = NULL;
    texCopyMode = 0;
    if (_layerBottom == this) {
        _layerBottom = next;
    } else {
        for (l = _layerBottom; l != NULL && l->next != this; l = l->next) {
        }
        l->next = next;
    }
    fifo = (PassFifo*)gsgfx_layer_activeFifo;
    if (fifo != NULL && (fifo == &passes[0] || fifo == &passes[1])) {
        layerFlushFifo(fifo);
        GXSetCPUFifo(GSgfxGPUGetImmediateFifo());
        gsgfx_layer_activeFifo = NULL;
    }
    if ((GCuptr)_layerStateLastHWState == (GCuptr)hwState) {
        _layerStateLastHWState = 0;
    }
    delete matrixStack;
    _layerIDTable[id] = 0;
    if (passes[0].data != NULL) {
        GSmemFree(passes[0].data);
        passes[0].data = NULL;
    }
    if (passes[1].data != NULL) {
        GSmemFree(passes[1].data);
        passes[1].data = NULL;
    }
}
}

extern "C++" {
void GSgfxLayer::SetupFifo() {
    layerSetupFifo(this);
}
}

extern "C++" {
void GSgfxLayer::MarkAndInvalidate() {
    u32 temp_r28;
    s32 temp_r4_3;
    s32 unksp18;
    u32 spC;
    u32 sp8;
    GXFifoObj *temp_r30;
    GXFifoObj *temp_r30_2;
    s32 temp_r4;
    s32 unksp10;
    volatile u32 temp_r0;
    volatile u32 temp_r0_2;
    u32 temp_r27;
    u32 temp_r27_2;
    u32 temp_r27_3;
    u32 temp_r3;
    u32 temp_r3_2;
    u32 temp_r4_2;
    u32 temp_r4_4;
    u32 temp_r5;
    u32 temp_r5_2;
    u32 temp_r5_3;
    u32 temp_r5_4;
    u32 temp_r6;
    u32 temp_r6_2;
    u32 var_r27;
    u32 var_r28;
    u32 var_r4;
    u32 var_r4_2;
    u8 var_r0;
    u8 var_r0_2;
    u8 var_r0_3;

    if (passes[0].data != NULL) {
        if (FIFO_OBJ(&passes[0]) == (GSgfx_GCFifoObj*)GXGetCPUFifo()) {
            layerFlushFifo(&passes[0]);
        }
        passes[0].unk88 = (u32)FIFO_OBJ(&passes[0])->write;
    }
    if (passes[1].data != NULL) {
        if (FIFO_OBJ(&passes[1]) == (GSgfx_GCFifoObj*)GXGetCPUFifo()) {
            layerFlushFifo(&passes[1]);
        }
        passes[1].unk88 = (u32)FIFO_OBJ(&passes[1])->write;
    }
    passes[0].unkB0 = passes[0].unkB4;
    passes[1].unkB0 = passes[1].unkB4;
    passes[0].unkAC = 0;
    passes[0].unkAE = 0;
    passes[1].unkAC = 0;
    passes[1].unkAE = 0;
    ((GSgfxLayer*)(this))->InvalidateState();
    if (type != 1) {
        var_r0_3 = hw.fogEnable != 0;
    } else {
        var_r0_3 = 0;
    }
    hw.fogEnable = var_r0_3;
    dirty[0].pe = (s32) (dirty[0].pe | 0x40);
    dirty[1].pe = (s32) (dirty[1].pe | 0x40);
    if (var_r0_3 != 0) {
        dirty[0].pe = (s32) (dirty[0].pe | 0x200);
        dirty[1].pe = (s32) (dirty[1].pe | 0x200);
        if ((u8) hw.fogRangeEnable != 0) {
            dirty[0].pe = (s32) (dirty[0].pe | 0x100);
            dirty[1].pe = (s32) (dirty[1].pe | 0x100);
        }
    }
    dirty[0].groups = (s32) (dirty[0].groups | 0x40);
    dirty[1].groups = (s32) (dirty[1].groups | 0x40);
}
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
        if (src->flag == 0) {
            return;
        }
        layerClearRedirect(src);
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
void GSgfxLayerUpdateActiveFifoStats() {
    GSgfxLayer::PassFifo* f;

    if (gsgfx_gpu_mode == 1 || (f = (GSgfxLayer::PassFifo*)gsgfx_layer_activeFifo) == NULL) {
        return;
    }
    layerFlushFifo(f);
}
