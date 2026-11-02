#include <dolphin/types.h>
typedef union {
    u8 u8;
    u16 u16;
    s16 s16;
    u32 u32;
    f32 f32;
} PPCWGPipe;
volatile PPCWGPipe GXWGFifo : 0xCC008000;
static inline void GXPosition3f32(f32 x, f32 y, f32 z) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

static inline void GXColor4u8(u8 r, u8 g, u8 b, u8 a) {
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;
}
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
enum GSgfxIndTexMtxID { GSgfxIndTexMtxID_draft_dummy };
struct GSgfxLayer;
enum GSgfxLayerPass { GSgfxLayerPass_draft_dummy };
enum GSgfxTgenFunc { GSgfxTgenFunc_draft_dummy };
enum GSgfxTgenSrc { GSgfxTgenSrc_draft_dummy };
struct GSgfxVF;
struct GSmtx;
struct GStexture;
typedef f32 Mtx44[4][4];

extern "C++" {
struct GSgfxLayer {
    u8 _draft[1];
    void FlushState();
    s32 tunitIndTexMtx(GSgfxIndTexMtxID, float(*)[3], signed char);
    void EffectScreenClear(bool, bool, bool);
    void PrepareFBCopy();
    void PrepareDistortion();
    void EffectTextureCopy(GStexture*, bool, unsigned char*, bool, bool, bool);
    s32 beginSurface(unsigned short);
    s32 tgenFunc(unsigned char, GSgfxTgenFunc, GSgfxTgenSrc, GSmtx*, bool, GSmtx*);
    void EffectDistortion();
    s32 endSurface();
    void setRenderStateAndSelect(GSgfxVF*);
    void textureCopy(GSgfxLayerPass, GStexture*, bool, unsigned char*, bool, bool, bool);
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSmtx {
    u8 _draft[1];
};
struct GStexture {
    u8 _draft[1];
};

extern "C" {
GSgfxVF* GSgfxVFGetPredef(s32 id);
s32 GSgfxVideoGetClearColor(s32*);
void GSgfxVideoGetEFBSize(u16* w, u16* h);
s32 GSgfxVideoSetClearColor(s32*);
s32 GSgfx_GCWriteCopyFilter(u8, void*, s32, s32*);
s32 GSgfx_GCWriteCopyTex(s16*, s32);
void GSmtx44Ortho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
s32 GStextureGetGXformat(GStexture* tex, u8 alpha);
void* memcpy(void* dst, const void* src, size_t n);
struct XdBlob30 { u8 data[0x30]; };
extern XdBlob30 mtxIdent;
extern s32 jtbl_1978;
}
extern "C++" {
void* GSgfxVideoGetRenderMode();
s32 GSgfxVideoResetViewport(bool);
}
static s32 _layerTexCopyDefaultFilter = 0x08080A0C;
GStexture* fbTexPtr__10GSgfxLayer;
GStexture* distTexPtr__10GSgfxLayer;
u16 fbTexRefCount__10GSgfxLayer;
u16 distTexRefCount__10GSgfxLayer;

void GSgfxLayer::textureCopy(GSgfxLayerPass p0, GStexture* p1, bool p2, unsigned char* p3, bool p4, bool p5, bool p6) {
    if ((s32) M2C_FIELD(this, s32 *, 0x1994) != p0) {
        M2C_FIELD(this, s32 *, 0x1994) = p0;
        M2C_FIELD(this, u8 **, 0x1990) = (u8 *)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC;
    }
    ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(p1), p2, (unsigned char*)(p3), p4, p5, p6);
}
}

struct GSgfxCopyTexDesc {
    s16 x;
    s16 y;
    u16 w;
    u16 h;
    u16 dstW;
    s32 format;
    s32 mode;
    u8 mipmap;
    u8 clear;
};

static inline void layerSetColorMask(GSgfxLayer* layer, bool r, bool g, bool b) {
    if (r == 1) {
        M2C_FIELD(layer, u8 *, 0x1656) = 1;
    } else {
        M2C_FIELD(layer, u8 *, 0x1656) = 0;
    }
    if (g == 1) {
        M2C_FIELD(layer, u8 *, 0x1657) = 1;
    } else {
        M2C_FIELD(layer, u8 *, 0x1657) = 0;
    }
    if (b == 1) {
        M2C_FIELD(layer, u8 *, 0x1658) = 1;
    } else {
        M2C_FIELD(layer, u8 *, 0x1658) = 0;
    }
    M2C_FIELD(layer, u32 *, 0x170C) |= 4;
    M2C_FIELD(layer, u32 *, 0x16A8) |= 0x40;
    M2C_FIELD(layer, u32 *, 0x17C4) |= 4;
    M2C_FIELD(layer, u32 *, 0x1760) |= 0x40;
}

static inline void layerLoadIdentity(GSgfxLayer* layer) {
    u8* mtx = M2C_FIELD(layer, u8 **, 0x19A0);
    memcpy(M2C_FIELD(mtx, u8 **, 4) + 4, &mtxIdent, 0x30U);
    *M2C_FIELD(mtx, u32 **, 4) |= 1;
}

static inline void layerSetTexture(GSgfxLayer* layer, s32 slot, GStexture* tex) {
    if (M2C_FIELD(layer, GStexture **, 0x1740 + slot * 4) != tex || M2C_FIELD(layer, GStexture **, 0x17F8 + slot * 4) != tex ||
        M2C_FIELD(tex, u8 *, 7) != 0) {
        M2C_FIELD(layer, GStexture **, 0x1740 + slot * 4) = tex;
        M2C_FIELD(layer, u32 *, 0x173C) |= 1 << slot;
        M2C_FIELD(layer, GStexture **, 0x17F8 + slot * 4) = tex;
        M2C_FIELD(layer, u32 *, 0x17F4) |= 1 << slot;
    }
}

static inline void layerSetZMode(GSgfxLayer* layer, bool enable, s32 func) {
    if (enable == 1) {
        M2C_FIELD(layer, u8 *, 0x165C) = 1;
    } else {
        M2C_FIELD(layer, u8 *, 0x165C) = 0;
    }
    M2C_FIELD(layer, s32 *, 0x1660) = func;
    M2C_FIELD(layer, u32 *, 0x170C) |= 8;
    M2C_FIELD(layer, u32 *, 0x16A8) |= 0x40;
    M2C_FIELD(layer, u32 *, 0x17C4) |= 8;
    M2C_FIELD(layer, u32 *, 0x1760) |= 0x40;
}

extern "C++" {
void GSgfxLayer::EffectTextureCopy(GStexture* tex, bool filter, unsigned char* coeffs, bool r, bool g, bool b) {
    u16 w;
    u16 h;
    GSgfxCopyTexDesc desc;
    u8* rm;
    bool mask;
    bool oldR;
    bool oldG;
    bool oldB;
    bool oldZ;
    s32 oldFunc;

    switch (M2C_FIELD(tex, s32 *, 8)) {
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x90:
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
        break;
    default:
        return;
    }
    rm = (u8*)GSgfxVideoGetRenderMode();
    GSgfxVideoGetEFBSize(&w, &h);
    w = M2C_FIELD(tex, u16 *, 0) < w ? M2C_FIELD(tex, u16 *, 0) : w;
    h = M2C_FIELD(tex, u16 *, 2) < h ? M2C_FIELD(tex, u16 *, 2) : h;
    mask = false;
    if (r || g || b) {
        mask = true;
    }
    if (mask == true) {
        oldR = M2C_FIELD(this, u8 *, 0x1656);
        oldG = M2C_FIELD(this, u8 *, 0x1657);
        oldB = M2C_FIELD(this, u8 *, 0x1658);
        oldZ = M2C_FIELD(this, u8 *, 0x165C);
        oldFunc = M2C_FIELD(this, s32 *, 0x1660);
        layerSetColorMask(this, r, g, b);
        layerSetZMode(this, true, 7);
    }
    FlushState();
    if (filter) {
        if (coeffs == NULL) {
            GSgfx_GCWriteCopyFilter(rm[0x19], rm + 0x1A, 1, &_layerTexCopyDefaultFilter);
        } else {
            GSgfx_GCWriteCopyFilter(rm[0x19], rm + 0x1A, 1, (s32*)coeffs);
        }
    } else {
        GSgfx_GCWriteCopyFilter(rm[0x19], rm + 0x1A, 0, NULL);
    }
    desc.x = 0;
    desc.y = 0;
    desc.w = w;
    desc.h = h;
    desc.dstW = w;
    desc.format = GStextureGetGXformat(tex, 0);
    desc.mode = 3;
    desc.mipmap = 0;
    desc.clear = mask;
    GSgfx_GCWriteCopyTex((s16*)&desc, M2C_FIELD(tex, s32 *, 0x28));
    if (mask == true) {
        layerSetColorMask(this, oldR, oldG, oldB);
        layerSetZMode(this, oldZ, oldFunc);
    }
    M2C_FIELD(this, u32 *, 4) |= 0x30000000;
}
}

extern "C++" {
void GSgfxLayer::EffectScreenClear(bool p0, bool p1, bool p2) {
    Mtx44 m;
    f32 left;
    f32 top;
    f32 right;
    f32 bottom;
    f32 z;

    if ((p0 != 0) || (p1 != 0) || (p2 != 0)) {
        if (p0 == 1) {
            M2C_FIELD(this, s8 *, 0x1656) = 1;
        } else {
            M2C_FIELD(this, s8 *, 0x1656) = 0;
        }
        if (p1 == 1) {
            M2C_FIELD(this, s8 *, 0x1657) = 1;
        } else {
            M2C_FIELD(this, s8 *, 0x1657) = 0;
        }
        if (p2 == 1) {
            M2C_FIELD(this, s8 *, 0x1658) = 1;
        } else {
            M2C_FIELD(this, s8 *, 0x1658) = 0;
        }
        M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 4);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 4);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
        GSmtx44Ortho(m, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
        M2C_FIELD(this, s32 *, 0xD54) = 1;
        M2C_FIELD(this, f32 *, 0xD58) = m[0][0];
        M2C_FIELD(this, f32 *, 0xD5C) = m[0][3];
        M2C_FIELD(this, f32 *, 0xD60) = m[1][1];
        M2C_FIELD(this, f32 *, 0xD64) = m[1][3];
        M2C_FIELD(this, f32 *, 0xD68) = m[2][2];
        M2C_FIELD(this, f32 *, 0xD6C) = m[2][3];
        layerLoadIdentity(this);
        M2C_FIELD(this, f32 *, 0x1684) = 0.0f;
        M2C_FIELD(this, f32 *, 0x1688) = 30000.0f;
        if ((u8) M2C_FIELD(this, u8 *, 0x16A7) != 0) {
            if ((u8) M2C_FIELD(this, u8 *, 0x16A6) != 0) {
                M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x100);
                M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x100);
            }
            M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x40);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x40);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
        }
        M2C_FIELD(this, s32 *, 0x16AC) = (s32) (M2C_FIELD(this, s32 *, 0x16AC) | 0x20);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 1);
        M2C_FIELD(this, s32 *, 0x1764) = (s32) (M2C_FIELD(this, s32 *, 0x1764) | 0x20);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 1);
        M2C_FIELD(this, s32 *, 0x1644) = 0;
        M2C_FIELD(this, s32 *, 0x1648) = 1;
        M2C_FIELD(this, s32 *, 0x164C) = 1;
        M2C_FIELD(this, s32 *, 0x1650) = 5;
        M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 1);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 1);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
        M2C_FIELD(this, s8 *, 0x165C) = 0;
        M2C_FIELD(this, s32 *, 0x1660) = 3;
        M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 8);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 8);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
        M2C_FIELD(this, s32 *, 0x1664) = 7;
        M2C_FIELD(this, s8 *, 0x1670) = 0;
        M2C_FIELD(this, s32 *, 0x1668) = 0;
        M2C_FIELD(this, s32 *, 0x166C) = 7;
        M2C_FIELD(this, s8 *, 0x1671) = 0;
        M2C_FIELD(this, s8 *, 0x1672) = 1;
        M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x10);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x10);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
        M2C_FIELD(this, s32 *, 0xD8C) = 0;
        M2C_FIELD(this, s32 *, 0x16B8) = (s32) (M2C_FIELD(this, s32 *, 0x16B8) | 2);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 2);
        M2C_FIELD(this, s32 *, 0x1770) = (s32) (M2C_FIELD(this, s32 *, 0x1770) | 2);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 2);
        M2C_FIELD(this, s32 *, 0xD90) = 1;
        M2C_FIELD(this, s32 *, 0x16B8) = (s32) (M2C_FIELD(this, s32 *, 0x16B8) | 4);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 2);
        M2C_FIELD(this, s32 *, 0x1770) = (s32) (M2C_FIELD(this, s32 *, 0x1770) | 4);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 2);
        ((GSgfxLayer*)(this))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(0)));
        M2C_FIELD(this, s32 *, 0x1998) = 0x98;
        left = 0.0f;
        top = 0.0f;
        right = 640.0f;
        bottom = 480.0f;
        z = 29999.0f;
        ((GSgfxLayer*)(this))->beginSurface(4U);
        GXPosition3f32(left, top, z);
        GXColor4u8(0, 0, 0, 0);
        GXPosition3f32(right, top, z);
        GXColor4u8(0, 0, 0, 0);
        GXPosition3f32(left, bottom, z);
        GXColor4u8(0, 0, 0, 0);
        GXPosition3f32(right, bottom, z);
        GXColor4u8(0, 0, 0, 0);
        ((GSgfxLayer*)(this))->endSurface();
    }
}
}

extern "C++" {
void GSgfxLayer::EffectDistortion() {
    s32 sp8;
    Mtx44 m;

    if ((u8) M2C_FIELD(this, u8 *, 0x16A7) != 0) {
        M2C_FIELD(this, u8 *, 0x16A7) = 0U;
        M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x40);
        M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x40);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
    }
    if ((s32) M2C_FIELD(this, s32 *, 0x1994) != 1) {
        M2C_FIELD(this, s32 *, 0x1994) = 1;
        M2C_FIELD(this, u8 **, 0x1990) = (u8 *)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC;
    }
    ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(distTexPtr__10GSgfxLayer), 1U, (unsigned char*)(NULL), 0U, 0U, 0U);
    GSgfxVideoResetViewport(1U);
    M2C_FIELD(this, s32 *, 0x1604) = 0;
    M2C_FIELD(this, s32 *, 0x1608) = 1;
    M2C_FIELD(this, s32 *, 0x160C) = 2;
    M2C_FIELD(this, s32 *, 0x1610) = 3;
    M2C_FIELD(this, s32 *, 0x1708) = (s32) (M2C_FIELD(this, s32 *, 0x1708) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x20);
    M2C_FIELD(this, s32 *, 0x17C0) = (s32) (M2C_FIELD(this, s32 *, 0x17C0) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x20);
    M2C_FIELD(this, s32 *, 0xD8C) = 2;
    M2C_FIELD(this, s32 *, 0x16B8) = (s32) (M2C_FIELD(this, s32 *, 0x16B8) | 2);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 2);
    M2C_FIELD(this, s32 *, 0x1770) = (s32) (M2C_FIELD(this, s32 *, 0x1770) | 2);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 2);
    M2C_FIELD(this, s32 *, 0x1644) = 0;
    M2C_FIELD(this, s32 *, 0x1648) = 1;
    M2C_FIELD(this, s32 *, 0x164C) = 1;
    M2C_FIELD(this, s32 *, 0x1650) = 5;
    M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
    M2C_FIELD(this, s8 *, 0x1656) = 1;
    M2C_FIELD(this, s8 *, 0x1657) = 0;
    M2C_FIELD(this, s8 *, 0x1658) = 0;
    M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 4);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 4);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
    M2C_FIELD(this, s8 *, 0x165C) = 0;
    M2C_FIELD(this, s32 *, 0x1660) = 3;
    M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 8);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 8);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
    M2C_FIELD(this, s32 *, 0x1664) = 7;
    M2C_FIELD(this, s8 *, 0x1670) = 0;
    M2C_FIELD(this, s32 *, 0x166C) = 7;
    M2C_FIELD(this, s8 *, 0x1671) = 0;
    M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x10);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
    M2C_FIELD(this, s8 *, 0x1672) = 1;
    M2C_FIELD(this, s32 *, 0x1668) = 0;
    M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x10);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
    M2C_FIELD(this, s32 *, 0xD90) = 0;
    M2C_FIELD(this, s32 *, 0x16B8) = (s32) (M2C_FIELD(this, s32 *, 0x16B8) | 4);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 2);
    M2C_FIELD(this, s32 *, 0x1770) = (s32) (M2C_FIELD(this, s32 *, 0x1770) | 4);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 2);
    M2C_FIELD(this, s8 *, 0xC70) = 1;
    M2C_FIELD(this, s32 *, 0x16AC) = (s32) (M2C_FIELD(this, s32 *, 0x16AC) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 1);
    M2C_FIELD(this, s32 *, 0x1764) = (s32) (M2C_FIELD(this, s32 *, 0x1764) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 1);
    ((GSgfxLayer*)(this))->tgenFunc(0U, (GSgfxTgenFunc)(1), (GSgfxTgenSrc)(4), (GSmtx*)(NULL), 0U, (GSmtx*)(NULL));
    M2C_FIELD(this, s8 *, 0xEAC) = 1;
    M2C_FIELD(this, s32 *, 0x16CC) = (s32) (M2C_FIELD(this, s32 *, 0x16CC) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
    M2C_FIELD(this, s32 *, 0x1784) = (s32) (M2C_FIELD(this, s32 *, 0x1784) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
    M2C_FIELD(this, s8 *, 0x14B0) = 1;
    M2C_FIELD(this, s32 *, 0x16EC) = (s32) (M2C_FIELD(this, s32 *, 0x16EC) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x80);
    M2C_FIELD(this, s32 *, 0x17A4) = (s32) (M2C_FIELD(this, s32 *, 0x17A4) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x80);
    M2C_FIELD(this, s8 *, 0xDB8) = 0;
    M2C_FIELD(this, s32 *, 0x16BC) = (s32) (M2C_FIELD(this, s32 *, 0x16BC) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 4);
    M2C_FIELD(this, s32 *, 0x1774) = (s32) (M2C_FIELD(this, s32 *, 0x1774) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 4);
    M2C_FIELD(this, s32 *, 0x14B4) = 0;
    M2C_FIELD(this, s32 *, 0x14B8) = 1;
    M2C_FIELD(this, s32 *, 0x16F0) = (s32) (M2C_FIELD(this, s32 *, 0x16F0) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x80);
    M2C_FIELD(this, s32 *, 0x17A8) = (s32) (M2C_FIELD(this, s32 *, 0x17A8) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x80);
    M2C_FIELD(this, s32 *, 0x14D4) = 0;
    M2C_FIELD(this, s32 *, 0x14D8) = 0;
    M2C_FIELD(this, s32 *, 0x16F4) = (s32) (M2C_FIELD(this, s32 *, 0x16F4) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x80);
    M2C_FIELD(this, s32 *, 0x17AC) = (s32) (M2C_FIELD(this, s32 *, 0x17AC) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x80);
    ((GSgfxLayer*)(this))->tunitIndTexMtx((GSgfxIndTexMtxID)(1), (float(*)[3])(this + 0x19BC), M2C_FIELD(this, s8 *, 0x19B8));
    M2C_FIELD(this, s32 *, 0x1420) = 2;
    M2C_FIELD(this, s8 *, 0x1424) = 0;
    M2C_FIELD(this, s8 *, 0x1425) = 0;
    M2C_FIELD(this, s8 *, 0x1426) = 0;
    M2C_FIELD(this, s32 *, 0x1428) = 1;
    M2C_FIELD(this, s32 *, 0x16E8) = (s32) (M2C_FIELD(this, s32 *, 0x16E8) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
    M2C_FIELD(this, s32 *, 0x17A0) = (s32) (M2C_FIELD(this, s32 *, 0x17A0) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
    M2C_FIELD(this, s32 *, 0xEB0) = 0;
    M2C_FIELD(this, s32 *, 0xEB4) = 0;
    M2C_FIELD(this, s32 *, 0xEB8) = 0xFF;
    M2C_FIELD(this, s32 *, 0x16D0) = (s32) (M2C_FIELD(this, s32 *, 0x16D0) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
    M2C_FIELD(this, s32 *, 0x1788) = (s32) (M2C_FIELD(this, s32 *, 0x1788) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
    M2C_FIELD(this, s32 *, 0x1170) = 0;
    M2C_FIELD(this, s32 *, 0x1174) = 0;
    M2C_FIELD(this, s32 *, 0x1178) = 0;
    M2C_FIELD(this, s8 *, 0x117C) = 0;
    M2C_FIELD(this, s32 *, 0x1180) = 0;
    M2C_FIELD(this, s32 *, 0x16DC) = (s32) (M2C_FIELD(this, s32 *, 0x16DC) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
    M2C_FIELD(this, s32 *, 0x1794) = (s32) (M2C_FIELD(this, s32 *, 0x1794) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
    M2C_FIELD(this, s32 *, 0x12B0) = 0;
    M2C_FIELD(this, s32 *, 0x12B4) = 0;
    M2C_FIELD(this, s32 *, 0x12B8) = 0;
    M2C_FIELD(this, s8 *, 0x12BC) = 0;
    M2C_FIELD(this, s32 *, 0x12C0) = 0;
    M2C_FIELD(this, s32 *, 0x16E0) = (s32) (M2C_FIELD(this, s32 *, 0x16E0) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
    M2C_FIELD(this, s32 *, 0x1798) = (s32) (M2C_FIELD(this, s32 *, 0x1798) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
    M2C_FIELD(this, s32 *, 0xF70) = 0xF;
    M2C_FIELD(this, s32 *, 0xF74) = 0xF;
    M2C_FIELD(this, s32 *, 0xF78) = 0xF;
    M2C_FIELD(this, s32 *, 0xF7C) = 8;
    M2C_FIELD(this, s32 *, 0x16D4) = (s32) (M2C_FIELD(this, s32 *, 0x16D4) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
    M2C_FIELD(this, s32 *, 0x178C) = (s32) (M2C_FIELD(this, s32 *, 0x178C) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
    M2C_FIELD(this, s32 *, 0x1070) = 7;
    M2C_FIELD(this, s32 *, 0x1074) = 7;
    M2C_FIELD(this, s32 *, 0x1078) = 7;
    M2C_FIELD(this, s32 *, 0x107C) = 7;
    M2C_FIELD(this, s32 *, 0x16D8) = (s32) (M2C_FIELD(this, s32 *, 0x16D8) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
    M2C_FIELD(this, s32 *, 0x1790) = (s32) (M2C_FIELD(this, s32 *, 0x1790) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
    layerSetTexture(this, 0, fbTexPtr__10GSgfxLayer);
    layerSetTexture(this, 1, distTexPtr__10GSgfxLayer);
    M2C_FIELD(this, GSgfxVF **, 0x199C) = GSgfxVFGetPredef(8);
    GSmtx44Ortho(m, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    M2C_FIELD(this, s32 *, 0xD54) = 1;
    M2C_FIELD(this, f32 *, 0xD58) = m[0][0];
    M2C_FIELD(this, f32 *, 0xD5C) = m[0][3];
    M2C_FIELD(this, f32 *, 0xD60) = m[1][1];
    M2C_FIELD(this, f32 *, 0xD64) = m[1][3];
    M2C_FIELD(this, f32 *, 0xD68) = m[2][2];
    M2C_FIELD(this, f32 *, 0xD6C) = m[2][3];
    layerLoadIdentity(this);
    M2C_FIELD(this, f32 *, 0x1684) = 0.0f;
    M2C_FIELD(this, f32 *, 0x1688) = 30000.0f;
    if ((u8) M2C_FIELD(this, u8 *, 0x16A7) != 0) {
        if ((u8) M2C_FIELD(this, u8 *, 0x16A6) != 0) {
            M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x100);
            M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x100);
        }
        M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x40);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x40);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
    }
    M2C_FIELD(this, s32 *, 0x16AC) = (s32) (M2C_FIELD(this, s32 *, 0x16AC) | 0x20);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 1);
    M2C_FIELD(this, s32 *, 0x1764) = (s32) (M2C_FIELD(this, s32 *, 0x1764) | 0x20);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 1);
    M2C_FIELD(this, s32 *, 0x1998) = 0x98;
    ((GSgfxLayer*)(this))->beginSurface(4U);
    GXWGFifo.s16 = 0;
    GXWGFifo.s16 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.s16 = 640;
    GXWGFifo.s16 = 0;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 0;
    GXWGFifo.s16 = 0;
    GXWGFifo.s16 = 480;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 1;
    GXWGFifo.s16 = 640;
    GXWGFifo.s16 = 480;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    ((GSgfxLayer*)(this))->endSurface();
    M2C_FIELD(this, s8 *, 0x14B0) = 0;
    M2C_FIELD(this, s32 *, 0x16EC) = (s32) (M2C_FIELD(this, s32 *, 0x16EC) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x80);
    M2C_FIELD(this, s32 *, 0x17A4) = (s32) (M2C_FIELD(this, s32 *, 0x17A4) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x80);
    M2C_FIELD(this, s32 *, 0x1420) = 0;
    M2C_FIELD(this, s32 *, 0x16E8) = (s32) (M2C_FIELD(this, s32 *, 0x16E8) | 1);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
    M2C_FIELD(this, s32 *, 0x17A0) = (s32) (M2C_FIELD(this, s32 *, 0x17A0) | 1);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
    ((GSgfxLayer*)(this))->FlushState();
    sp8 = M2C_FIELD(this, s32 *, 0x19B4);
    GSgfxVideoSetClearColor(&sp8);
    GSgfxVideoResetViewport(0U);
}
}
extern "C++" {
void GSgfxLayer::PrepareDistortion() {
    volatile s32 sp10;
    s32 spC;
    s32 sp8;

    sp10 = jtbl_1978;
    if (!(M2C_FIELD(this, s32 *, 4) & 0x200) || ((u32) M2C_FIELD(this, u32 *, 0x19A4) != (u32)fbTexPtr__10GSgfxLayer)) {
        if ((s32) M2C_FIELD(this, s32 *, 0x1994) != 1) {
            M2C_FIELD(this, s32 *, 0x1994) = 1;
            M2C_FIELD(this, u8 **, 0x1990) = (u8 *)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC;
        }
        M2C_FIELD(this, s32 *, 0x1604) = 2;
        M2C_FIELD(this, s32 *, 0x1608) = 2;
        M2C_FIELD(this, s32 *, 0x160C) = 2;
        M2C_FIELD(this, s32 *, 0x1610) = 3;
        M2C_FIELD(this, s32 *, 0x1708) = (s32) (M2C_FIELD(this, s32 *, 0x1708) | 1);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x20);
        M2C_FIELD(this, s32 *, 0x17C0) = (s32) (M2C_FIELD(this, s32 *, 0x17C0) | 1);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x20);
        spC = M2C_FIELD(this, s32 *, 0x19B4);
        GSgfxVideoGetClearColor(&spC);
        sp8 = sp10;
        GSgfxVideoSetClearColor(&sp8);
        ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(fbTexPtr__10GSgfxLayer), 0U, (unsigned char*)(NULL), 1U, 1U, 0U);
    }
}
}

extern "C++" {
void GSgfxLayer::PrepareFBCopy() {
    if (!(M2C_FIELD(this, s32 *, 4) & 0x200) || ((u32) M2C_FIELD(this, u32 *, 0x19A4) != (u32)fbTexPtr__10GSgfxLayer)) {
        if ((s32) M2C_FIELD(this, s32 *, 0x1994) != 1) {
            M2C_FIELD(this, s32 *, 0x1994) = 1;
            M2C_FIELD(this, u8 **, 0x1990) = (u8 *)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC;
        }
        ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(fbTexPtr__10GSgfxLayer), 0U, (unsigned char*)(NULL), 0U, 0U, 0U);
    }
}
}
