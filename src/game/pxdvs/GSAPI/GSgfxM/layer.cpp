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
enum ASM { ASM_draft_dummy };
struct GXFifoObj;
enum Mtx44 { Mtx44_draft_dummy };
enum PrimColor { PrimColor_draft_dummy };
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
    u32 pad[3];
public:
    ~GSgfxMatrixStack();
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
    struct RenderHook {
        int pass;
        void* end;
        void (*callback)(void*);
        void* arg;
    } hooks[4];

    static GStexture* fbTexPtr;
    static u16 fbTexRefCount;
    static GStexture* distTexPtr;
    static u16 distTexRefCount;
public:
    s32 EffectTextureCopy(GStexture*, bool, unsigned char*, bool, bool, bool);
    void SetupFifo();
    ~GSgfxLayer();
    s32 EffectScreenClear(bool, bool, bool);
    s32 EffectDistortion();
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

extern "C++" {
struct GXFifoObj {
    u8 _draft[1];
};

extern "C" {
void GSmemFree(void* ptr);
void GSmtx44Ortho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
s32 GSprimDraw2DHLine(s32*, f32, f32, f32);
s32 GSprimDraw2DQuadWH(s32*, s32, f32, f32, f32, f32, f32);
void GSprimSetLineWidth(f32 w);
void GSprimSetQuadVertexOrder(s32 order);
void GSprimSetTextColor(PrimColor color);
void GSprimSetTextSize(f32 xpel, f32 ypel);
void GSprimSetTextWidth(f32 w);
void GSprimWriteChar(char c, f32 x, f32 y);
void GSprimWriteStr(f32 x, f32 y, char* fmt, ...);
GXFifoObj* GXGetCPUFifo(void);
extern u32 _layerStateLastHWState;
extern GStexture* fbTexPtr__10GSgfxLayer;
extern u16 fbTexRefCount__10GSgfxLayer;
extern s32 mtxIdent;
extern s32 jtbl_1809;
extern s32 jtbl_1810;
extern s32 jtbl_1811;
extern s32 jtbl_1812;
extern s32 jtbl_1813;
extern s32 jtbl_1814;
extern s32 jtbl_1815;
extern s32 c_localstatic3_GSgfxPerfColorToGSgfxCol;
}
extern "C++" {
s32 GSgfxGPUSetFifoWritePtr(GSgfx_GCFifoObj*, void*);
void GSgfxLayerBuildRenderList();
void GSgfxLayerRenderStats(GSgfxLayer* p0);
s32 GSgfxRenderAddToFifoList(GSgfx_GCFifoObj*, void*, void*, unsigned long, void (*)(void*), void*);
void GSgfxRenderModuleDoRender(GSgfxLayer* layer, GSgfxLayerPass pass);
s32 GSgfxRenderWaitForDrawComplete();
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
    if (o->write >= o->read) {
        count = o->write - o->read;
    } else {
        count = o->end - o->read;
        count += o->write - o->base;
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
        wr = FIFO_OBJ(f)->write;
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
    r.v = *(volatile u32*)0xCC003014;
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
        wr = FIFO_OBJ(f)->write;
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
        *(GSgfxLayer**)&gsgfxState->activeLayer = layer;
    }
}

struct RedirectLegend {
    char sym;
    GSgfxLayer* layer;
    s32 pass;
    s32 offset;
};

void GSgfxLayerRenderStats(GSgfxLayer* p0) {
    s32 sp24;
    s32 saved_reg_r25;
    s32 saved_reg_r26;
    f32 spB8;
    f32 spC0;
    f32 spC8;
    f32 spD4;
    f32 spD8;
    s32 sp128;
    s32 sp124;
    s32 sp120;
    s32 sp11C;
    s32 sp118;
    s32 sp114;
    s32 sp110;
    s32 sp10C;
    s32 sp108;
    s32 sp104;
    s32 sp100;
    s32 spFC;
    s32 spF8;
    s32 spF4;
    s32 spF0;
    s32 spEC;
    f32 spAC;
    s8 sp9E;
    s32 sp8C;
    s8 sp88;
    s8 sp87;
    volatile s8 sp86;
    volatile s8 sp85;
    s8 sp84;
    u8 var_r6;
    u32 sp7C;
    u32 sp78;
    u32 sp74;
    u32 sp70;
    u32 sp6C;
    u32 sp68;
    s32 var_r21;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    f32 var_f27;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    u8 spF;
    u8 spE;
    u8 spD;
    u8 spC;
    u8 spB;
    u8 spA;
    u8 sp9;
    u8 sp8;
    s32 *temp_r24;
    s32 *temp_r3_2;
    s32 *var_r20;
    s32 *var_r3;
    s32 *var_r4_3;
    s32 *var_r6_2;
    f32 var_f26;
    f32 var_f26_2;
    s32 saved_reg_f26;
    f32 var_f27_2;
    s32 *temp_r3;
    s32 *var_r17;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r16_2;
    s32 temp_r22;
    s32 var_r18;
    s32 sp64;
    s32 var_r25;
    s32 var_r26;
    s32 var_r30;
    s32 var_r31;
    s32 var_r4;
    s8 var_r0_2;
    u32 temp_r7;
    u32 var_r0;
    u32 var_r5;
    u8 temp_r4;
    u8 var_r0_3;
    u8 var_r0_4;
    u8 var_r3_2;
    u8 var_r3_3;
    u8 var_r3_4;
    u8 var_r3_5;
    u8 var_r4_2;
    s32 sp80;
    u8 *temp_r16;
    u8 *temp_r4_2;
    u8 *temp_r4_3;

    RedirectLegend legend[4] = {
        { '#', NULL, 2, 0 },
        { '$', NULL, 2, 0 },
        { '=', NULL, 2, 0 },
        { '+', NULL, 2, 0 },
    };
    var_r25 = saved_reg_r25;
    var_r26 = saved_reg_r26;
    var_f26 = saved_reg_f26;
    sp80 = jtbl_1810;
    sp64 = jtbl_1811;
    sp60 = jtbl_1812;
    sp5C = jtbl_1813;
    sp58 = jtbl_1814;
    sp54 = jtbl_1815;
    if ((u8) _layerRenderStats != 0) {
        var_r31 = 0;
        var_r30 = 0;
        GSprimSetRenderLayer((GSgfxLayer*)(p0));
        GSprimSetQuadVertexOrder(0);
        GSprimSetLineWidth(1.0f);
        GSprimSetTextSize(10.0f, 10.0f);
        GSprimSetTextWidth(1.0f);
        M2C_FIELD(p0, s32 *, 0x1644) = 1;
        M2C_FIELD(p0, s32 *, 0x1648) = 4;
        M2C_FIELD(p0, s32 *, 0x164C) = 5;
        M2C_FIELD(p0, s32 *, 0x1650) = 5;
        M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 1);
        M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 1);
        M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 0x40);
        GSmtx44Ortho((Mtx44)((s32) &spAC), 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
        M2C_FIELD(p0, s32 *, 0xD54) = 1;
        M2C_FIELD((u16)p0, f32 *, 0xD58) = spAC;
        M2C_FIELD(p0, f32 *, 0xD5C) = spB8;
        M2C_FIELD(p0, f32 *, 0xD60) = spC0;
        M2C_FIELD(p0, f32 *, 0xD64) = spC8;
        M2C_FIELD(p0, f32 *, 0xD68) = spD4;
        M2C_FIELD(p0, f32 *, 0xD6C) = spD8;
        temp_r16 = M2C_FIELD(p0, u8 **, 0x19A0);
        memcpy((void*)(M2C_FIELD(temp_r16, s32 **, 4) + 4), (const void*)(&mtxIdent), 0x30U);
        temp_r3 = M2C_FIELD(temp_r16, s32 **, 4);
        *temp_r3 |= 1;
        M2C_FIELD(p0, f32 *, 0x1684) = 0.0f;
        M2C_FIELD(p0, f32 *, 0x1688) = 30000.0f;
        if ((u8) M2C_FIELD(p0, u8 *, 0x16A7) != 0) {
            if ((u8) M2C_FIELD(p0, u8 *, 0x16A6) != 0) {
                M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 0x100);
                M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 0x100);
            }
            M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 0x40);
            M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 0x40);
            M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 0x40);
        }
        M2C_FIELD(p0, s32 *, 0x16AC) = (s32) (M2C_FIELD(p0, s32 *, 0x16AC) | 0x20);
        var_r4 = 0;
        M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 1);
        M2C_FIELD(p0, s32 *, 0x1764) = (s32) (M2C_FIELD(p0, s32 *, 0x1764) | 0x20);
        M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 1);
        M2C_FIELD(p0, s8 *, 0x1656) = 1;
        M2C_FIELD(p0, s8 *, 0x1657) = 0;
        M2C_FIELD(p0, s8 *, 0x1658) = 0;
        M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 4);
        M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 4);
        M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 0x40);
        M2C_FIELD(p0, s8 *, 0x165C) = 0;
        M2C_FIELD(p0, s32 *, 0x1660) = 3;
        M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 8);
        M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 8);
        M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 0x40);
        M2C_FIELD(p0, s32 *, 0x1664) = 7;
        M2C_FIELD(p0, s8 *, 0x1670) = 0;
        M2C_FIELD(p0, s32 *, 0x1668) = 0;
        M2C_FIELD(p0, s32 *, 0x166C) = 7;
        M2C_FIELD(p0, s8 *, 0x1671) = 0;
        M2C_FIELD(p0, s8 *, 0x1672) = 1;
        M2C_FIELD(p0, s32 *, 0x170C) = (s32) (M2C_FIELD(p0, s32 *, 0x170C) | 0x10);
        M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(p0, s32 *, 0x17C4) = (s32) (M2C_FIELD(p0, s32 *, 0x17C4) | 0x10);
        M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 0x40);
        M2C_FIELD(p0, s32 *, 0xD8C) = 0;
        M2C_FIELD(p0, s32 *, 0x16B8) = (s32) (M2C_FIELD(p0, s32 *, 0x16B8) | 2);
        M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 2);
        M2C_FIELD(p0, s32 *, 0x1770) = (s32) (M2C_FIELD(p0, s32 *, 0x1770) | 2);
        M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 2);
        M2C_FIELD(p0, s32 *, 0xD90) = 1;
        M2C_FIELD(p0, s32 *, 0x16B8) = (s32) (M2C_FIELD(p0, s32 *, 0x16B8) | 4);
        M2C_FIELD(p0, s32 *, 0x16A8) = (s32) (M2C_FIELD(p0, s32 *, 0x16A8) | 2);
        M2C_FIELD(p0, s32 *, 0x1770) = (s32) (M2C_FIELD(p0, s32 *, 0x1770) | 4);
        M2C_FIELD(p0, s32 *, 0x1760) = (s32) (M2C_FIELD(p0, s32 *, 0x1760) | 2);
        var_r3 = (long *)(_layerBottom);
        while (var_r3 != NULL) {
            var_r3 = (long *)(*var_r3);
            var_r4 += 1;
        }
        sp50 = sp80;
        GSprimDraw2DQuadWH(&sp50, sp80, 10.0f, 22.0f, 620.0f, (12.0f * (f32) var_r4) + 28.0f, M2C_ERROR( ));
        sp4C = sp5C;
        GSprimSetTextColor((PrimColor)((s32) &sp4C));
        GSprimSetTextSize(10.0f, 10.0f);
        GSprimWriteStr(25.0f, 29.0f, (char*)("#"));
        GSprimWriteStr(50.0f, 29.0f, (char*)("ID"));
        GSprimWriteStr(85.0f, 29.0f, (char*)("Name"));
        GSprimWriteStr(245.0f, 29.0f, (char*)("TCAZ"));
        GSprimWriteStr(295.0f, 29.0f, (char*)("Opaque"));
        GSprimWriteStr(470.0f, 29.0f, (char*)("Xluc"));
        var_r21 = 0;
        sp48 = sp58;
        GSprimDraw2DHLine(&sp48, 20.0f, 620.0f, 42.0f);
        var_r20 = (long *)(_layerBottom);
loop_138:
        if (var_r20 != NULL) {
            temp_r22 = M2C_FIELD(var_r20, s32 *, 0x28);
            temp_r24 = M2C_FIELD(var_r20, s32 **, 0);
            f32 kc8463 = 12.0f;
            f32 kc8495 = 47.0f;
            var_f26 = (kc8463 * (f32) var_r21) + kc8495;
            if (temp_r22 < 8) {
                var_r5 = _layerPerfColor[temp_r22];
            } else {
                var_r5 = (unsigned long)(_layerPerfUserColor);
            }
            temp_r4 = (u8) (var_r5 >> 0x10U);
            M2C_FIELD(&c_localstatic3_GSgfxPerfColorToGSgfxCol, u8 *, 1) = (u8) (var_r5 >> 8U);
            M2C_FIELD(&c_localstatic3_GSgfxPerfColorToGSgfxCol, s8 *, 2) = (s8) var_r5;
            M2C_FIELD(&c_localstatic3_GSgfxPerfColorToGSgfxCol, u8 *, 0) = temp_r4;
            M2C_FIELD(&c_localstatic3_GSgfxPerfColorToGSgfxCol, s8 *, 3) = 0xFF;
            sp44 = (s32) M2C_FIELD(&c_localstatic3_GSgfxPerfColorToGSgfxCol, u8 *, 0);
            GSprimDraw2DQuadWH(&sp44, (s32) temp_r4, 20.0f, var_f26 - 1.0f, 50.0f, 12.0f, M2C_ERROR( ));
            sp40 = sp5C;
            GSprimSetTextColor((PrimColor)((s32) &sp40));
            GSprimWriteStr(25.0f, var_f26, (char*)("%d"), var_r21);
            GSprimWriteStr(55.0f, var_f26, (char*)("%d"), temp_r22);
            if (&spF != NULL) {
                spF = ((u32) M2C_FIELD(var_r20, u32 *, 4) >> 1U) & 1;
            }
            if (&spE != NULL) {
                spE = ((u32) M2C_FIELD(var_r20, u32 *, 4) >> 2U) & 1;
            }
            if ((u32) (M2C_FIELD(var_r20, u32 *, 4) & 1) != 1) {
                sp3C = sp64;
                GSprimSetTextColor((PrimColor)((s32) &sp3C));
                spF = 0;
                spE = 0;
            }
            GSprimSetTextSize(8.5f, 10.0f);
            if ((s32) (strlen((const char*)((s8 *) (var_r20 + 8))) + 1) <= 0x13) {
                memcpy((void*)(&sp8C), (const void*)(var_r20 + 8), strlen((const char*)((s8 *) (var_r20 + 8))) + 1);
            } else {
                memcpy((void*)(&sp8C), (const void*)(var_r20 + 8), 0x12U);
                sp9E = 0;
            }
            GSprimWriteStr(85.0f, var_f26, (char*)("%s"), &sp8C);
            GSprimSetTextSize(10.0f, 10.0f);
            if (M2C_FIELD(var_r20, u32 *, 4) & 0x200) {
                var_r0 = M2C_FIELD(var_r20, u32 *, 0x19A4);
            } else {
                var_r0 = 0U;
            }
            var_r0_2 = 0x58;
            if (var_r0 != 0U) {
                var_r0_2 = 0x4F;
            }
            sp84 = var_r0_2;
            temp_r3_2 = M2C_FIELD(var_r20, s32 **, 0);
            if (temp_r3_2 == NULL) {
                var_r6 = 0;
                var_r4_2 = 0;
                var_r3_2 = 0;
            } else {
                if (&sp8 != NULL) {
                    sp8 = ((u32) M2C_FIELD(temp_r3_2, u32 *, 4) >> 6U) & 1;
                }
                if (&sp9 != NULL) {
                    sp9 = ((u32) M2C_FIELD(temp_r3_2, u32 *, 4) >> 7U) & 1;
                }
                if (&spA != NULL) {
                    spA = ((u32) M2C_FIELD(temp_r3_2, u32 *, 4) >> 8U) & 1;
                }
                temp_r7 = M2C_FIELD(var_r20, u32 *, 4);
                var_r3_3 = 0;
                if ((temp_r7 & 8) || (sp8 != 0)) {
                    var_r3_3 = 1;
                }
                var_r3_4 = 0;
                var_r6 = var_r3_3 != 0;
                if ((temp_r7 & 0x10) || (sp9 != 0)) {
                    var_r3_4 = 1;
                }
                var_r3_5 = 0;
                var_r4_2 = var_r3_4 != 0;
                if ((temp_r7 & 0x20) || (spA != 0)) {
                    var_r3_5 = 1;
                }
                var_r3_2 = var_r3_5 != 0;
            }
            if (&spD != NULL) {
                spD = var_r6;
            }
            if (&spC != NULL) {
                spC = var_r4_2;
            }
            if (&spB != NULL) {
                spB = var_r3_2;
            }
            if (spD == 1) {
                sp85 = 0x4F;
            } else {
                sp85 = 0x58;
            }
            if (spC == 1) {
                sp86 = 0x4F;
            } else {
                sp86 = 0x58;
            }
            if (spB == 1) {
                sp87 = 0x4F;
            } else {
                sp87 = 0x58;
            }
            if ((temp_r24 != NULL) && ((u32) (M2C_FIELD(temp_r24, s32 *, 4) & 1) == 1)) {
                temp_r0 = M2C_FIELD(temp_r24, s32 *, 0x2C);
                switch (temp_r0) {
                case 1:
                    sp85 = 0x2B;
                    sp86 = 0x2B;
                case 4:
                    sp84 = 0x2B;
                    break;
                }
            }
            sp88 = 0;
            GSprimWriteStr(245.0f, var_f26, (char*)(&sp84), var_r4_2);
            if (&sp7C != NULL) {
                if ((u32) M2C_FIELD(var_r20, u32 *, 0x1818) != 0U) {
                    sp7C = M2C_FIELD(var_r20, u32 *, 0x18C8);
                } else {
                    sp7C = 0;
                }
            }
            if (&sp78 != NULL) {
                if ((u32) M2C_FIELD(var_r20, u32 *, 0x18D4) != 0U) {
                    sp78 = M2C_FIELD(var_r20, u32 *, 0x1984);
                } else {
                    sp78 = 0;
                }
            }
            if (&sp74 != NULL) {
                if ((u32) M2C_FIELD(var_r20, u32 *, 0x1818) != 0U) {
                    sp74 = M2C_FIELD(var_r20, u32 *, 0x18D0);
                } else {
                    sp74 = 0;
                }
            }
            if (&sp70 != NULL) {
                if ((u32) M2C_FIELD(var_r20, u32 *, 0x18D4) != 0U) {
                    sp70 = M2C_FIELD(var_r20, u32 *, 0x198C);
                } else {
                    sp70 = 0;
                }
            }
            if (&sp6C != NULL) {
                sp6C = M2C_FIELD(var_r20, u32 *, 0x181C);
            }
            if (&sp68 != NULL) {
                sp68 = M2C_FIELD(var_r20, u32 *, 0x18D8);
            }
            var_f27 = 295.0f;
            if ((u32) M2C_FIELD(var_r20, u32 *, 0x1818) == 0U) {
                var_r0_3 = 0;
            } else if ((u8) M2C_FIELD(var_r20, u8 *, 0x18AC) == 0) {
                var_r0_3 = 0;
            } else {
                temp_r4_2 = (unsigned char *)((s32*)legend + var_r30);
                if ((temp_r4_2 + 4) != NULL) {
                    temp_r0_2 = M2C_FIELD(var_r20, s32 *, 0x18B0);
                    if (temp_r0_2 == -1) {
                        var_r26 = 0;
                    } else if (temp_r0_2 < 0x10) {
                        var_r26 = (long)(_layerIDTable[temp_r0_2]);
                    }
                    M2C_FIELD(temp_r4_2, s32 *, 4) = var_r26;
                }
                if ((temp_r4_2 + 8) != NULL) {
                    M2C_FIELD(temp_r4_2, s32 *, 8) = (s32) M2C_FIELD(var_r20, s32 *, 0x18B4);
                }
                if ((temp_r4_2 + 0xC) != NULL) {
                    M2C_FIELD(temp_r4_2, s32 *, 0xC) = (s32) M2C_FIELD(var_r20, s32 *, 0x18B8);
                }
                var_r0_3 = 1;
            }
            if (var_r0_3 == 1) {
                sp38 = sp54;
                GSprimSetTextColor((PrimColor)((s32) &sp38));
                GSprimWriteChar((s8) *((s32*)legend + var_r30), 295.0f, var_f26);
                var_r31 += 1;
                var_r30 += 0x10;
                f32 kc15772 = 295.0f;
                f32 kc15810 = 11.0f;
                var_f27 = kc15772 + kc15810;
            }
            sp34 = sp5C;
            GSprimSetTextColor((PrimColor)((s32) &sp34));
            if (sp6C != 0) {
                if (spF == 0) {
                    sp30 = sp64;
                    GSprimSetTextColor((PrimColor)((s32) &sp30));
                } else if (sp7C == 0) {
                    sp2C = sp60;
                    GSprimSetTextColor((PrimColor)((s32) &sp2C));
                }
                if (sp7C != 0) {
                    f32 kc16339 = 0.0009765625f;
                    f32 kc16388 = 0.0009765625f;
                    f32 kc16437 = 0.5f;
                    f32 kc16477 = 0.0009765625f;
                    GSprimWriteStr(var_f27, var_f26, "%.1f/%dK (%dK)", (u32) ((f32) sp6C * kc16339), (u32) (((f32) sp74 * kc16388) + kc16437), (f32) sp7C * kc16477);
                } else {
                    f32 kc16727 = 0.0009765625f;
                    f32 kc16776 = 0.0009765625f;
                    f32 kc16825 = 0.5f;
                    GSprimWriteStr(var_f27, var_f26, "---/%dK (%dK)", (u32) ((f32) sp6C * kc16727), (u32) (((f32) sp74 * kc16776) + kc16825));
                }
            }
            var_f27_2 = 470.0f;
            if ((u32) M2C_FIELD(var_r20, u32 *, 0x18D4) == 0U) {
                var_r0_4 = 0;
            } else if ((u8) M2C_FIELD(var_r20, u8 *, 0x1968) == 0) {
                var_r0_4 = 0;
            } else {
                temp_r4_3 = (unsigned char *)((s32*)legend + var_r30);
                if ((temp_r4_3 + 4) != NULL) {
                    temp_r0_3 = M2C_FIELD(var_r20, s32 *, 0x196C);
                    if (temp_r0_3 == -1) {
                        var_r25 = 0;
                    } else if (temp_r0_3 < 0x10) {
                        var_r25 = (long)(_layerIDTable[temp_r0_3]);
                    }
                    M2C_FIELD(temp_r4_3, s32 *, 4) = var_r25;
                }
                if ((temp_r4_3 + 8) != NULL) {
                    M2C_FIELD(temp_r4_3, s32 *, 8) = (s32) M2C_FIELD(var_r20, s32 *, 0x1970);
                }
                if ((temp_r4_3 + 0xC) != NULL) {
                    M2C_FIELD(temp_r4_3, s32 *, 0xC) = (s32) M2C_FIELD(var_r20, s32 *, 0x1974);
                }
                var_r0_4 = 1;
            }
            if (var_r0_4 == 1) {
                sp28 = sp54;
                GSprimSetTextColor((PrimColor)((s32) &sp28));
                GSprimWriteChar((s8) *((s32*)legend + var_r30), 470.0f, var_f26);
                var_r31 += 1;
                var_r30 += 0x10;
                f32 kc18405 = 470.0f;
                f32 kc18443 = 11.0f;
                var_f27_2 = kc18405 + kc18443;
            }
            sp24 = sp5C;
            GSprimSetTextColor((PrimColor)((s32) &sp24));
            if (sp68 != 0) {
                if (spE == 0) {
                    sp20 = sp64;
                    GSprimSetTextColor((PrimColor)((s32) &sp20));
                } else if (sp78 == 0) {
                    if (sp1C < sp60) sp1C = sp60;
                    GSprimSetTextColor((PrimColor)((s32) &sp1C));
                }
                if (sp78 != 0) {
                    f32 kc18974 = 0.0009765625f;
                    f32 kc19023 = 0.0009765625f;
                    f32 kc19072 = 0.5f;
                    f32 kc19112 = 0.0009765625f;
                    GSprimWriteStr(var_f27_2, var_f26, "%.1f/%dK (%dK)", (u32) ((f32) sp68 * kc18974), (u32) (((f32) sp70 * kc19023) + kc19072), (f32) sp78 * kc19112);
                } else {
                    f32 kc19364 = 0.0009765625f;
                    f32 kc19413 = 0.0009765625f;
                    f32 kc19462 = 0.5f;
                    GSprimWriteStr(var_f27_2, var_f26, "---/%dK (%dK)", (u32) ((f32) sp68 * kc19364), (u32) (((f32) sp70 * kc19413) + kc19462));
                }
            }
            var_r20 = temp_r24;
            var_r21 += 1;
            goto loop_138;
        }
        if (var_r31 > 0) {
            sp18 = sp80;
            GSprimDraw2DQuadWH(&sp18, 0x43300000, 10.0f, (12.0f * (f32) var_r21) + 50.0f, 620.0f, (12.0f * (f32) var_r31) + 4.0f, 12.0f);
            var_r17 = &spEC;
            var_r18 = 0;
            f32 kc20051 = 18.0f;
            var_f26_2 = var_f26 + kc20051;
            while (var_r18 < var_r31) {
                sp14 = sp54;
                GSprimSetTextColor((PrimColor)((s32) &sp14));
                GSprimWriteChar((s8) M2C_FIELD(var_r17, u8 *, 0), 40.0f, var_f26_2);
                sp10 = sp5C;
                GSprimSetTextColor((PrimColor)((s32) &sp10));
                temp_r16_2 = M2C_FIELD(var_r17, s32 *, 4);
                if ((s32) (strlen((const char*)(temp_r16_2 + 8)) + 1) <= 0x13) {
                    memcpy((void*)(&sp8C), (const void*)(temp_r16_2 + 8), strlen((const char*)(temp_r16_2 + 8)) + 1);
                } else {
                    memcpy((void*)(&sp8C), (const void*)(temp_r16_2 + 8), 0x12U);
                    sp9E = 0;
                }
                var_r6_2 = (long *)("xluc");
                if ((s32) M2C_FIELD(var_r17, s32 *, 8) == 0) {
                    var_r6_2 = (long *)("opaque");
                }
                var_r4_3 = (long *)("after");
                var_r4_3 = !((s32) M2C_FIELD(var_r17, s32 *, 0xC) == 1) ? var_r4_3 : (long *)("before");
                GSprimWriteStr(60.0f, var_f26_2, "redirected %s: %s %s pass", var_r4_3, &sp8C, var_r6_2);
                var_f26_2 += 12.0f;
                var_r17 += 0x10;
                var_r18 += 1;
            }
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
extern "C++" {
void GSgfxLayer::SendFifoToRenderer(_gsgfxLayerFifo* fifo) {
    PassFifo* f = (PassFifo*)fifo;
    u32* start;
    u32 n;
    u8 empty;
    int i;
    RenderHook* hook;

    if (f->data != NULL) {
        if (FIFO_OBJ(f) == (GSgfx_GCFifoObj*)GXGetCPUFifo()) {
            layerFlushFifo(f);
        }
        f->unk8c = FIFO_OBJ(f)->write;
    }
    start = (u32*)f->unk88;
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
        GSlogWrite("fifo overflow in [%s]: %s pass", name, curPass != 0 ? "xluc" : "opaque");
        return;
    }
    start = (u32*)f->unk88;
    hook = hooks;
    for (i = 0; i < 4; i++, hook++) {
        if (hook->callback == NULL) {
            break;
        }
        if (&passes[hook->pass] == f) {
            GSgfxRenderAddToFifoList(FIFO_OBJ(f), start, hook->end, f->color, hook->callback, hook->arg);
            start = (u32*)hook->end;
        }
    }
    GSgfxRenderAddToFifoList(FIFO_OBJ(f), start, (void*)f->unk8c, f->color, NULL, NULL);
}
}

extern "C++" {
void GSgfxLayer::Prerender() {
    enum TsE { TsE0 };
    enum TsE spD;
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
    u8 *temp_r3;

    ((GSgfxLayer*)((u16)this))->PrerenderPass((GSgfxLayerPass)(0));
    ((GSgfxLayer*)(this))->PrerenderPass((GSgfxLayerPass)(1));
    temp_r3 = M2C_FIELD(this, u8 **, 0);
    if (temp_r3 == NULL) {
        var_r6 = 0;
        var_r4 = 0;
        var_r3 = 0;
    } else {
        if (&sp8 != NULL) {
            sp8 = ((u32) M2C_FIELD(temp_r3, u32 *, 4) >> 6U) & 1;
        }
        if (&sp9 != NULL) {
            sp9 = ((u32) M2C_FIELD(temp_r3, u32 *, 4) >> 7U) & 1;
        }
        if (&spA != NULL) {
            spA = ((u32) M2C_FIELD(temp_r3, u32 *, 4) >> 8U) & 1;
        }
        temp_r7 = M2C_FIELD(this, s32 *, 4);
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
        spD = (enum TsE)(var_r6);
    }
    if (&spC != NULL) {
        spC = var_r4;
    }
    if (&spB != NULL) {
        spB = var_r3;
    }
    if ((u32) M2C_FIELD(this, u32 *, 0x18D4) != 0U) {
        if ((s32) M2C_FIELD(this, s32 *, 0x1994) != 1) {
            M2C_FIELD(this, s32 *, 0x1994) = 1;
            M2C_FIELD(this, u8 **, 0x1990) = (u8 *) ((u8*)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC);
        }
    } else if ((s32) M2C_FIELD(this, s32 *, 0x1994) != 0) {
        M2C_FIELD(this, s32 *, 0x1994) = 0;
        M2C_FIELD(this, u8 **, 0x1990) = (u8 *) ((u8*)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC);
    }
    if (M2C_FIELD(this, s32 *, 4) & 1) {
        temp_r0 = M2C_FIELD(this, s32 *, 0x2C);
        switch (temp_r0) {
        case 4:
            break;
        case 1:
            ((GSgfxLayer*)(this))->EffectDistortion();
            break;
        }
    }
    if (M2C_FIELD(this, s32 *, 4) & 0x200) {
        temp_r0_2 = M2C_FIELD(this, s32 *, 0x19A8);
        switch (temp_r0_2) {
        case 0:
            ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(M2C_FIELD(this, GStexture **, 0x19A4)), 0U, (unsigned char*)(NULL), spD, spC, spB);
            return;
        case 1:
            ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(M2C_FIELD(this, GStexture **, 0x19A4)), 1U, (unsigned char*)(NULL), spD, spC, spB);
            return;
        case 2:
            ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(M2C_FIELD(this, GStexture **, 0x19A4)), 1U, (unsigned char*)((u8*)this + 0x19AC), spD, spC, spB);
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
        GSgfxGPUSetFifoWritePtr(FIFO_OBJ(f), (void*)passes[pass].unk88);
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
    if ((u32)_layerStateLastHWState == (u32)((u8*)this + 0x30)) {
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
        passes[0].unk88 = FIFO_OBJ(&passes[0])->write;
    }
    if (passes[1].data != NULL) {
        if (FIFO_OBJ(&passes[1]) == (GSgfx_GCFifoObj*)GXGetCPUFifo()) {
            layerFlushFifo(&passes[1]);
        }
        passes[1].unk88 = FIFO_OBJ(&passes[1])->write;
    }
    passes[0].unkB0 = passes[0].unkB4;
    passes[1].unkB0 = passes[1].unkB4;
    passes[0].unkAC = 0;
    passes[0].unkAE = 0;
    passes[1].unkAC = 0;
    passes[1].unkAE = 0;
    ((GSgfxLayer*)(this))->InvalidateState();
    if ((s32) M2C_FIELD(this, s32 *, 0x2C) != 1) {
        var_r0_3 = M2C_FIELD(this, u8 *, 0x16A7) != 0;
    } else {
        var_r0_3 = 0;
    }
    M2C_FIELD(this, u8 *, 0x16A7) = var_r0_3;
    M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x40);
    M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x40);
    if (var_r0_3 != 0) {
        M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x200);
        M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x200);
        if ((u8) M2C_FIELD(this, u8 *, 0x16A6) != 0) {
            M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x100);
            M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x100);
        }
    }
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
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
        *slot = 0;
        src->redirectOffset = 0;
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
