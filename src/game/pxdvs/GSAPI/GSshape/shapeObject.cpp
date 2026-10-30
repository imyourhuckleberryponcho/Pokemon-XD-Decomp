#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
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
enum Mtx { Mtx_draft_dummy };
struct Vec;
#define fabs(x) __fabs(x)
#define fabsf(x) __fabsf(x)
extern f32 __float_nan[];
#define NAN (__float_nan[0])

struct GStexture {
    u8 unk0[7];
    u8 reload;
};

enum GSgfxTunitOp {};
enum GSgfxTunitBias {};
enum GSgfxTunitScale {};
enum GSgfxTunitReg {};
enum GSgfxTunitAArg {};
enum GSgfxTunitCArg {};

struct Vec3 {
    f32 x, y, z;
    Vec3() {}
    Vec3(f32 _x, f32 _y, f32 _z) {
        x = _x;
        y = _y;
        z = _z;
    }
    Vec3& operator=(const Vec3& o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
};
typedef f32 Mtx34[3][4];
struct GSmtx {
    Mtx34 m;
};
struct tagGScol4ub {
    u8 r, g, b, a;
};
struct GSgfxVF;
struct GSgfxDL;
struct GSmtx;

struct GSgfxDirty {
    u32 groups;
    u32 words[36];
    u32 textureMask;
    GStexture* textures[8];
};

struct GSgfxBlendSet {
    u8 unk0[0xBC];
};

#define GFX_DIRTY(word, bits, group)  \
    dirty[0].words[word] |= (bits);   \
    dirty[0].groups |= (group);       \
    dirty[1].words[word] |= (bits);   \
    dirty[1].groups |= (group);

struct GSgfxTunitMap {
    u32 texCoord;
    u32 texMap;
    u32 color;
};

struct GSgfxTevOp {
    u32 op;
    u32 bias;
    u32 scale;
    u8 clamp;
    u32 reg;
};

class GSgfxLayer {
public:
    void beginSurface(u16 n);
    void endSurface();
    void dlDraw(GSgfxDL* dl);

    void tunitAlphaOp(u8 unit, GSgfxTunitOp op, GSgfxTunitBias bias, GSgfxTunitScale scale, bool clamp,
                      GSgfxTunitReg reg) {
        alphaOps[unit].op = op;
        alphaOps[unit].bias = bias;
        alphaOps[unit].scale = scale;
        alphaOps[unit].clamp = clamp;
        alphaOps[unit].reg = reg;
        GFX_DIRTY(13, 1 << unit, 8)
    }
    void tunitAlphaArg(u8 unit, GSgfxTunitAArg a, GSgfxTunitAArg b, GSgfxTunitAArg c, GSgfxTunitAArg d) {
        alphaArgs[unit][0] = a;
        alphaArgs[unit][1] = b;
        alphaArgs[unit][2] = c;
        alphaArgs[unit][3] = d;
        GFX_DIRTY(11, 1 << unit, 8)
    }
    void tunitColorOp(u8 unit, GSgfxTunitOp op, GSgfxTunitBias bias, GSgfxTunitScale scale, bool clamp,
                      GSgfxTunitReg reg) {
        colorOps[unit].op = op;
        colorOps[unit].bias = bias;
        colorOps[unit].scale = scale;
        colorOps[unit].clamp = clamp;
        colorOps[unit].reg = reg;
        GFX_DIRTY(12, 1 << unit, 8)
    }
    void tunitColorArg(u8 unit, GSgfxTunitCArg a, GSgfxTunitCArg b, GSgfxTunitCArg c, GSgfxTunitCArg d) {
        colorArgs[unit][0] = a;
        colorArgs[unit][1] = b;
        colorArgs[unit][2] = c;
        colorArgs[unit][3] = d;
        GFX_DIRTY(10, 1 << unit, 8)
    }
    void tunitMapping(u8 stage, u8 a, u8 b, u8 c) {
        tunitMaps[stage].texCoord = a;
        tunitMaps[stage].texMap = b;
        if (c != 0xFF) {
            tunitMaps[stage].color = c + 4;
        } else {
            tunitMaps[stage].color = 0xFF;
        }
        *(u32*)((u8*)this + 0x16D0) |= 1 << stage;
        *(u32*)((u8*)this + 0x16A8) |= 8;
        *(u32*)((u8*)this + 0x1788) |= 1 << stage;
        *(u32*)((u8*)this + 0x1760) |= 8;
    }
    void texSelect(u8 map, GStexture* texture) {
        if (dirty[0].textures[map] == texture && dirty[1].textures[map] == texture && !texture->reload) {
            return;
        }
        dirty[0].textures[map] = texture;
        dirty[0].textureMask |= 1 << map;
        dirty[1].textures[map] = texture;
        dirty[1].textureMask |= 1 << map;
    }

    void zCompare(u8 enable, u32 func) {
        if (enable == 1) {
            zEnable = 1;
        } else {
            zEnable = 0;
        }
        zFunc = func;
        GFX_DIRTY(24, 8, 0x40)
    }
    void pixelMode(u8 cu, u8 au, u8 di) {
        if (cu == 1) {
            colorUpdate = 1;
        } else {
            colorUpdate = 0;
        }
        if (au == 1) {
            alphaUpdate = 1;
        } else {
            alphaUpdate = 0;
        }
        if (di == 1) {
            dither = 1;
        } else {
            dither = 0;
        }
        GFX_DIRTY(24, 4, 0x40)
    }
    void setCullMode(u32 mode) {
        cullMode = mode;
        GFX_DIRTY(3, 2, 2)
    }
    void blendMode(int type, u32 src, u32 dst) {
        if (type == 0) {
            if (blendIndex != 0) {
                blendIndex = 0;
                blendSet = &blendSets[blendIndex];
            }
            blendType = 0;
            blendSrc = 1;
            blendDst = 1;
            blendLogicOp = 5;
        } else {
            if (blendIndex != 1) {
                blendIndex = 1;
                blendSet = &blendSets[blendIndex];
            }
            blendType = type;
            blendSrc = src;
            blendDst = dst;
            blendLogicOp = 5;
        }
        GFX_DIRTY(24, 1, 0x40)
    }

    u8 unk0[0xD8C];
    u32 cullMode;
    u8 unkD90[0x120];
    GSgfxTunitMap tunitMaps[16];
    u32 colorArgs[16][4];
    u32 alphaArgs[16][4];
    GSgfxTevOp colorOps[16];
    GSgfxTevOp alphaOps[16];
    u8 unk13F0[0x114];
    u32 kcolorSel[16];
    u32 kalphaSel[16];
    u8 unk1584[0xC0];
    u32 blendType;
    u32 blendSrc;
    u32 blendDst;
    u32 blendLogicOp;
    u8 unk1654[0x2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 dither;
    u8 unk1659[0x3];
    u8 zEnable;
    u8 unk165D[0x3];
    u32 zFunc;
    u8 unk1664[0x44];
    GSgfxDirty dirty[2];
    GSgfxBlendSet blendSets[2];
    GSgfxBlendSet* blendSet;
    s32 blendIndex;
    u32 primType;
    GSgfxVF* curVF;
};

struct GsShapeTexture {
    struct Info {
        u8 unk0[0xE];
        u8 mode;
    }* info;
    GStexture* tex;
};

struct GsShapeTexInfo {
    u8 unk0[4];
    u16 index;
    u8 filter;
    u8 filterB;
    u8 wrapS;
    u8 wrapT;
    u8 kind;
};

struct GsShapeData {
    u8 unk0[5];
    u8 unk5;
    u8 unk6;
    u8 pad7;
    u8 mode;
    u8 unk9;
    u16 cols;
    u16 rows;
    u16 vertCount;
    f32* pos;
    u32* col;
    f32* tex;
    Vec3* pos2;
    u8 unk20[0x26 - 0x20];
    u16 texCount;
    GsShapeTexInfo* texInfo[4];
    u16 kind;
    u8 pad3A[2];
    f32 sizeX;
    f32 sizeY;
    u8 unk44[0x5C - 0x44];
    f32 angle;
    f32 angle2;
    f32 pitchA;
    f32 pitchB;
    u8 unk6C[0xC8 - 0x6C];
    f32 height;
    u8 unkCC;
    u8 billboard;
    u8 unkCE;
    u8 unkCF;
    f32 sharp;
    u8 unkD4[4];
    u8 cull;
};

extern "C" {
void PSVECScale(const Vec3* src, Vec3* dst, f32 s);
void PSVECAdd(const Vec3* a, const Vec3* b, Vec3* ab);
void PSMTXMultVecSR(const f32 m[3][4], const Vec3* src, Vec3* dst);
void PSMTXScale(f32 m[3][4], f32 x, f32 y, f32 z);
void PSMTXTransApply(const f32 src[3][4], f32 dst[3][4], f32 x, f32 y, f32 z);
void PSMTXConcat(const f32 a[3][4], const f32 b[3][4], f32 ab[3][4]);
void PSMTXRotRad(f32 m[3][4], char axis, f32 rad);
void PSMTXRotAxisRad(f32 m[3][4], const Vec3* axis, f32 rad);
f32 PSVECMag(const Vec3* v);
void PSVECNormalize(const Vec3* src, Vec3* dst);
void PSVECCrossProduct(const Vec3* a, const Vec3* b, Vec3* ab);
f32 PSVECDotProduct(const Vec3* a, const Vec3* b);
double acos(double);
double tan(double);
double sin(double);
double cos(double);
extern GSmtx mtxIdent;
void GStextureSetFilter(GStexture* tex, s32 minFilter, s32 magFilter, u32 mipFilter);
void GStextureSetWrap(GStexture* tex, u32 wrapS, u32 wrapT);
void* GSmemAlloc(u32 size);
void GSmemFree(void* p);
void* memcpy(void* dst, const void* src, u32 n);
void* memset(void* dst, int c, u32 n);
void GSgfxVFSetArray(GSgfxVF* vf, s32, s32, void*, s32, s32);
void GSgfxDLPrimitiveType(int type);
void GSgfxDLBeginSurface(u16 count);
void GSgfxDLEndSurface(void);
void GSgfxDLBegin(void* dl, void* buf, int rows, u16 size);
void GSgfxDLEnd(void);
void GSgfxDLFree(void* dl);
}

class GsShapeObject {
public:
    int GetPolygonCount();
    bool FreeShapeDrawBuffer(s16 idx);
    bool CreateShapeDrawBuffer(s16 idx);
    inline bool SetupVF(u16 n);
    inline f32 RimFromDot(f32 dot);
    inline f32 RimFactor(Vec3* n, Vec3* v);
    void MakeMatrixBillboard(GSmtx* m, f32 f);
    bool DeformVertexCoordCylinderEx(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2, bool angOwn,
                                     f32 f3, bool scaled, const f32* C);
    bool DeformVertexCoord(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2, bool angOwn, f32 f3,
                           f32 f4, bool scaled, const f32* C);
    bool DeformVertexCoordSpiral(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2, bool angOwn,
                                 f32 f3, f32 f4, bool scaled, const f32* C);
    bool DeformVertexCoordSphere(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2, bool angOwn,
                                 f32 f3, f32 f4, bool scaled, const f32* C);
    bool DeformVertexCoordTorus(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2, bool angOwn,
                                f32 f3, f32 f4, bool scaled, const f32* C);
    bool WaveTextureCoord(u32 idx, f32 u, f32 v, const GSmtx* m, bool keep);
    bool DeformTextureCoord(u32 idx, bool a, const f32* A, const f32* B, bool b, const f32* C);
    bool RefractTextureCoord(f32 u, f32 v, GSmtx* m1, GSmtx* m2, GSmtx* m3, f32 f);
    bool ShadeVertexColor(GSmtx* m1, GSmtx* m2, GSmtx* m3, f32 f, bool b);
    void SetVertexColorGradation(u8 perVertex, const tagGScol4ub* colors, int mode, f32 f, bool b);
    void SetVertexColorAlpha(int mode, int type, f32 f, bool b);
    void SetVertexColorSpecify(const tagGScol4ub& c, bool b);
    void SetStateTexture(GSgfxLayer* l, GsShapeTexture* texes, GStexture* override);
    void SetStateMode(GSgfxLayer* layer);
    void MakeShapeGfxDL();
    void DrawShapeGfx(GSgfxLayer* layer, s16 s, u8 c);
    void FreeDisplayListShape();
    void CallDisplayListShape(GSgfxLayer* layer, s16 s, u8 c);
    void MakeDisplayListShape();

    GsShapeData* data;
    u8 vf[0x440];
    void* posArray;
    void* colArray;
    void* texArray[9];
    GSmtx mtx;
    void* dl;
    void* drawBuf[256];
};

extern "C" {
f32 PSVECSquareMag(const Vec3* v);
void PSMTXCopy(const f32 src[3][4], f32 dst[3][4]);
void PSMTXMultVec(const f32 m[3][4], const Vec3* src, Vec3* dst);
void GXProject(f32 x, f32 y, f32 z, const f32 mv[3][4], const f32* proj, const f32* vp, f32* sx, f32* sy, f32* sz);
f32* GSgfxMatrixGetPtr(int which);
}

struct Vec {
    u8 _draft[1];
};

extern "C" {
extern s32 jtbl_1816;
extern s32 jtbl_1815;
}

inline int __fpclassifyf(float x) {
    switch ((*(s32*)&x) & 0x7F800000) {
    case 0x7F800000:
        if ((*(s32*)&x) & 0x007FFFFF) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(s32*)&x) & 0x007FFFFF) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

inline float sqrtf(float x) {
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (float)(x * guess);
    } else if (x < 0.0) {
        return NAN;
    } else if (__fpclassifyf(x) == 1) {
        return NAN;
    }
    return x;
}

static inline Vec3 vscale(const Vec3* v, f32 s) {
    Vec3 r;
    PSVECScale(v, &r, s);
    return r;
}

static inline Vec3 vadd(const Vec3& a, const Vec3& b) {
    Vec3 r;
    PSVECAdd(&a, &b, &r);
    return r;
}

int GsShapeObject::GetPolygonCount() {
    return data->cols * data->rows * 2;
}

bool GsShapeObject::FreeShapeDrawBuffer(s16 idx) {
    if (idx < 0 || idx >= 0x100) {
        return false;
    }
    if (drawBuf[idx] != 0) {
        GSmemFree(drawBuf[idx]);
        drawBuf[idx] = 0;
        return true;
    }
    return false;
}

bool GsShapeObject::CreateShapeDrawBuffer(s16 idx) {
    if (idx < 0 || idx >= 0x100) {
        return false;
    }
    drawBuf[idx] = GSmemAlloc(data->vertCount * (data->texCount * 8 + 0x10) * 2);
    if (drawBuf[idx] == 0) {
        return false;
    }
    u16 n = data->vertCount;
    int i = 0;
    int o;
    int t;
    int size = n * 12;
    int s4 = n * 4;
    int s8 = n * 8;
    for (; i < 2; i++) {
        int off = 0;
        if (i != 0) {
            off = n * (data->texCount * 8 + 0x10);
        }
        u8* base = (u8*)drawBuf[idx] + off;
        memcpy(base, data->pos, size);
        u8* p = base + size;
        memcpy(p, data->col, s4);
        t = 0;
        o = 0;
        for (; t < data->texCount; t++, o += 8) {
            memcpy(p + n * (o + 4), data->tex, s8);
        }
    }
    return true;
}

inline bool GsShapeObject::SetupVF(u16 n) {
    const int attrs[4] = {13, 14, 15, 16};
    if (posArray == 0) {
        return false;
    }
    if (posArray != 0) {
        GSgfxVFSetArray((GSgfxVF*)vf, 9, 3, posArray, 12, n * 12);
    } else {
        return false;
    }
    if (colArray != 0) {
        GSgfxVFSetArray((GSgfxVF*)vf, 11, 3, colArray, 4, n * 4);
    } else {
        return false;
    }
    int i;
    for (i = 0; i < data->texCount; i++) {
        if (texArray[i] != 0) {
            GSgfxVFSetArray((GSgfxVF*)vf, attrs[i], 3, texArray[i], 8, n * 8);
        } else {
            return false;
        }
    }
    return true;
}

void GsShapeObject::SetStateTexture(GSgfxLayer* l, GsShapeTexture* texes, GStexture* override);

#pragma push
#pragma dont_inline on
#define LAYER_DIRTY(word, bits, group)     l->dirty[0].words[word] |= (bits);     l->dirty[0].groups |= (group);         l->dirty[1].words[word] |= (bits);     l->dirty[1].groups |= (group);
#define KCOLOR(s, v) l->kcolorSel[(u8)(s)] = (v); LAYER_DIRTY(20, 1 << (u8)(s), 0x10)
#define KALPHA(s, v) l->kalphaSel[(u8)(s)] = (v); LAYER_DIRTY(21, 1 << (u8)(s), 0x10)
#define CARG(s, a, b, c, d) l->tunitColorArg(s, (GSgfxTunitCArg)(a), (GSgfxTunitCArg)(b), (GSgfxTunitCArg)(c), (GSgfxTunitCArg)(d))
#define AARG(s, a, b, c, d) l->tunitAlphaArg(s, (GSgfxTunitAArg)(a), (GSgfxTunitAArg)(b), (GSgfxTunitAArg)(c), (GSgfxTunitAArg)(d))
#define COP(s, op, reg) l->tunitColorOp(s, (GSgfxTunitOp)(op), (GSgfxTunitBias)0, (GSgfxTunitScale)0, true, (GSgfxTunitReg)(reg))
#define AOP(s, op, reg) l->tunitAlphaOp(s, (GSgfxTunitOp)(op), (GSgfxTunitBias)0, (GSgfxTunitScale)0, true, (GSgfxTunitReg)(reg))

void GsShapeObject::SetStateTexture(GSgfxLayer* l, GsShapeTexture* texes, GStexture* override) {
    const int kcolor[4] = {12, 13, 14, 15};
    enum TsE { TsE0 };
    const int kalpha[4] = {28, 29, 30, 31};
    int kalphaLast = kalpha[1];
    u8 stage = 0;
    u8 ti = 0;
    u8 texN = data->texCount;
    int last = texN - 1;
    for (; ti < texN; ti++) {
        int map = ti;
        GsShapeTexInfo* info = data->texInfo[ti];
        GsShapeTexture* t = texes + info->index;
        int mip = 1;
        if (info->filter) {
            mip = 2;
        }
        int mag = 1;
        if (info->filterB) {
            mag = 2;
        }
        int min = 1;
        if (info->filter) {
            min = 2;
        }
        GStextureSetFilter(t->tex, min, mag, mip);
        GStextureSetWrap(t->tex, info->wrapS, info->wrapT);
        GStexture* tex = t->tex;
        if (ti == 0 && override != 0) {
            tex = override;
        }
        if (data->mode == 10 && ti == 0 && data->texCount >= 2) {
            u32 s1;
            l->texSelect(map, tex);
            l->tunitMapping(stage, map, map, 0);
            CARG(stage, 15, 15, 15, 15);
            COP(stage, 0, 0);
            AARG(stage, 7, 7, 7, 7);
            AOP(stage, 0, 0);
            s1 = stage + 1;
            l->tunitMapping(s1, map, map, 0);
            CARG(s1, 15, 15, 15, 15);
            COP(s1, 0, 0);
            AARG(s1, 7, 7, 7, 7);
            AOP(s1, 0, 0);
            stage += 2;
            if (t->info->mode == 1) {
                l->tunitMapping(stage, map, map, 0);
                CARG(stage, 15, 15, 15, 15);
                COP(stage, 0, 0);
                AARG(stage, 7, 7, 7, 7);
                AOP(stage, 0, 0);
                stage += 1;
            }
        } else if (ti < 2) {
            if (t->info->mode != 0) {
                int s1 = stage + 1;
                int s2 = stage + 2;
                KCOLOR(stage, kcolor[map * 2]);
                KALPHA(stage, kalpha[map * 2]);
                KCOLOR(s1, kcolor[map * 2 + 1]);
                KALPHA(s1, kalpha[map * 2 + 1]);
                KALPHA(s2, kalphaLast);
                l->texSelect(map, tex);
                l->tunitMapping(stage, map, map, 0);
                CARG(stage, 15, 15, 15, 14);
                COP(stage, 0, 1);
                AARG(stage, 7, 6, 4, 7);
                AOP(stage, 0, 1);
                l->tunitMapping(s1, map, map, 0);
                CARG(s1, 14, 2, 8, 15);
                COP(s1, 0, 2);
                AARG(s1, 7, 7, 7, 1);
                AOP(s1, 0, 2);
                l->tunitMapping(s2, map, map, 0);
                switch (info->kind) {
                case 0:
                    CARG(s2, 15, 4, ti == 0 ? (GSgfxTunitCArg)12 : (GSgfxTunitCArg)0, 15);
                    COP(s2, 0, 0);
                    AARG(s2, 7, 2, ti == 0 ? (GSgfxTunitAArg)6 : (GSgfxTunitAArg)0, 7);
                    AOP(s2, 0, 0);
                    break;
                case 2:
                    CARG(s2, ti == 0 ? (GSgfxTunitCArg)4 : (GSgfxTunitCArg)0, 4, 9, 15);
                    COP(s2, 0, 0);
                    AARG(s2, ti == 0 ? (GSgfxTunitAArg)2 : (GSgfxTunitAArg)0, 2, 4, 7);
                    AOP(s2, 0, 0);
                    break;
                case 3:
                    CARG(s2, 15, 15, 15, 4);
                    COP(s2, 0, 0);
                    AARG(s2, 7, 7, 7, 2);
                    AOP(s2, 0, 0);
                    break;
                case 4:
                    CARG(s2, 4, 15, 15, ti == 0 ? (GSgfxTunitCArg)15 : (GSgfxTunitCArg)0);
                    COP(s2, 0, 0);
                    AARG(s2, 2, 7, 7, ti == 0 ? (GSgfxTunitAArg)7 : (GSgfxTunitAArg)0);
                    AOP(s2, 0, 0);
                    break;
                case 5:
                    CARG(s2, 4, 15, 15, ti == 0 ? (GSgfxTunitCArg)15 : (GSgfxTunitCArg)0);
                    COP(s2, ti != 0, 0);
                    AARG(s2, 2, 7, 7, ti == 0 ? (GSgfxTunitAArg)7 : (GSgfxTunitAArg)0);
                    AOP(s2, 0, 0);
                    break;
                case 9:
                    CARG(s2, 15, 15, 15, ti == 0 ? (GSgfxTunitCArg)4 : (GSgfxTunitCArg)0);
                    COP(s2, 0, 0);
                    AARG(s2, 7, 2, ti == 0 ? (GSgfxTunitAArg)6 : (GSgfxTunitAArg)0, 7);
                    AOP(s2, 0, 0);
                    break;
                default:
                    CARG(s2, 4, 15, 15, ti == 0 ? (GSgfxTunitCArg)10 : (GSgfxTunitCArg)0);
                    COP(s2, 0, 0);
                    AARG(s2, 2, 7, 7, ti == 0 ? (GSgfxTunitAArg)5 : (GSgfxTunitAArg)0);
                    AOP(s2, 0, 0);
                    break;
                }
                stage += 3;
            } else {
                int s1 = stage + 1;
                KCOLOR(stage, kcolor[map * 2]);
                KALPHA(stage, kalpha[map * 2]);
                KALPHA(s1, kalphaLast);
                l->texSelect(map, tex);
                l->tunitMapping(stage, map, map, 0);
                CARG(stage, 15, 14, 8, 15);
                COP(stage, 0, 1);
                AARG(stage, 7, 6, 4, 7);
                AOP(stage, 0, 1);
                l->tunitMapping(s1, map, map, 0);
                switch (info->kind) {
                case 0:
                    CARG(s1, 15, ti == 0 ? (GSgfxTunitCArg)12 : (GSgfxTunitCArg)0, 2, 15);
                    COP(s1, 0, 0);
                    AARG(s1, 7, ti == 0 ? (GSgfxTunitAArg)6 : (GSgfxTunitAArg)0, 1, 7);
                    AOP(s1, 0, 0);
                    break;
                case 2:
                    CARG(s1, ti == 0 ? (GSgfxTunitCArg)12 : (GSgfxTunitCArg)0, 2, 9, 15);
                    COP(s1, 0, 0);
                    AARG(s1, ti == 0 ? (GSgfxTunitAArg)6 : (GSgfxTunitAArg)0, 1, 4, 7);
                    AOP(s1, 0, 0);
                    break;
                case 3:
                    CARG(s1, 15, 8, 14, 15);
                    COP(s1, 0, 0);
                    AARG(s1, 7, 4, 6, 7);
                    AOP(s1, 0, 0);
                    break;
                case 4:
                    CARG(s1, 2, 15, 15, ti == 0 ? (GSgfxTunitCArg)15 : (GSgfxTunitCArg)0);
                    COP(s1, 0, 0);
                    AARG(s1, 1, 7, 7, ti == 0 ? (GSgfxTunitAArg)7 : (GSgfxTunitAArg)0);
                    AOP(s1, 0, 0);
                    break;
                case 5:
                    CARG(s1, 2, 15, 15, ti == 0 ? (GSgfxTunitCArg)15 : (GSgfxTunitCArg)0);
                    COP(s1, ti != 0, 0);
                    AARG(s1, 1, 7, 7, ti == 0 ? (GSgfxTunitAArg)7 : (GSgfxTunitAArg)0);
                    AOP(s1, 0, 0);
                    break;
                case 9:
                    CARG(s1, 15, 15, 15, ti == 0 ? (GSgfxTunitCArg)8 : (GSgfxTunitCArg)0);
                    COP(s1, 0, 0);
                    AARG(s1, 7, ti == 0 ? (GSgfxTunitAArg)6 : (GSgfxTunitAArg)0, 1, 7);
                    AOP(s1, 0, 0);
                    break;
                default:
                    CARG(s1, 2, 15, 15, ti == 0 ? (GSgfxTunitCArg)15 : (GSgfxTunitCArg)0);
                    COP(s1, 0, 0);
                    AARG(s1, 1, 7, 7, ti == 0 ? (GSgfxTunitAArg)7 : (GSgfxTunitAArg)0);
                    AOP(s1, 0, 0);
                    break;
                }
                stage += 2;
            }
        } else {
            l->texSelect(map, tex);
            l->tunitMapping(stage, map, map, 0);
            switch (info->kind) {
            case 0:
                CARG(stage, 15, 8, 0, 15);
                COP(stage, 0, 0);
                AARG(stage, 7, 4, 0, 7);
                AOP(stage, 0, 0);
                break;
            case 2:
                CARG(stage, 0, 8, 9, 15);
                COP(stage, 0, 0);
                AARG(stage, 4, 7, 7, 0);
                AOP(stage, 0, 0);
                break;
            case 3:
                CARG(stage, 15, 15, 15, 8);
                COP(stage, 0, 0);
                AARG(stage, 4, 7, 7, 0);
                AOP(stage, 0, 0);
                break;
            case 4:
                CARG(stage, 8, 15, 15, 0);
                COP(stage, 0, 0);
                AARG(stage, 4, 7, 7, 0);
                AOP(stage, 0, 0);
                break;
            case 5:
                CARG(stage, 8, 15, 15, 0);
                COP(stage, 1, 0);
                AARG(stage, 4, 7, 7, 0);
                AOP(stage, 0, 0);
                break;
            case 9:
                CARG(stage, 15, 15, 15, 0);
                COP(stage, 0, 0);
                AARG(stage, 7, 4, 0, 7);
                AOP(stage, 0, 0);
                break;
            default:
                CARG(stage, 8, 15, 15, 0);
                COP(stage, 0, 0);
                AARG(stage, 4, 7, 7, 0);
                AOP(stage, 0, 0);
                break;
            }
            stage += 1;
        }
        if (map == last) {
            l->tunitMapping(stage, map, map, 0);
            CARG(stage, 15, 10, 0, 15);
            COP(stage, 0, 0);
            AARG(stage, 7, 5, 0, 7);
            AOP(stage, 0, 0);
            stage += 1;
        }
    }
}

#undef LAYER_DIRTY
#undef KCOLOR
#undef KALPHA
#undef CARG
#undef AARG
#undef COP
#undef AOP
#pragma pop

void GsShapeObject::SetStateMode(GSgfxLayer* l) {
    int b = data->unk5 != 0;
    int a = data->unk6 != 0;
    if (data->mode == 8) {
        b = true;
        a = true;
    }
    l->zCompare(b, 1);
    l->pixelMode(1, 1, a);
    l->setCullMode(data->cull);
    u8 mode = data->mode;
    if (mode == 10 && data->texCount >= 2) {
        u8 k = data->texInfo[1]->kind;
        switch (k) {
        case 2:
        case 4:
            mode = k;
        }
    }
    switch (mode) {
    case 4:
        l->blendMode(1, 4, 1);
        break;
    case 5:
        l->blendMode(3, 4, 1);
        break;
    case 2:
        l->blendMode(1, 4, 5);
        break;
    case 8:
        l->blendMode(1, 4, 5);
        break;
    case 10:
        l->blendMode(1, 4, 5);
        break;
    default:
        l->blendMode(1, 4, 5);
        break;
    }
}

void GsShapeObject::MakeShapeGfxDL() {
    u16 i;
    u16 base0;
    u16 texN = data->texCount;
    u16 cols1 = data->cols + 1;
    GSgfxDLPrimitiveType(0x98);
    for (i = 0; i < data->rows; i++) {
        base0 = i * cols1;
        GSgfxDLBeginSurface(cols1 * 2);
        u16 base1 = (i + 1) * cols1;
        u16 j;
        for (j = 0; j < cols1; j++) {
            u16 a = j + base0;
            u16 b = j + base1;
            u16 k;
            GXWGFifo.u16 = a;
            GXWGFifo.u16 = a;
            for (k = 0; k < texN; k++) {
                GXWGFifo.u16 = a;
            }
            GXWGFifo.u16 = b;
            GXWGFifo.u16 = b;
            for (k = 0; k < texN; k++) {
                GXWGFifo.u16 = b;
            }
        }
        GSgfxDLEndSurface();
    }
}

void GsShapeObject::DrawShapeGfx(GSgfxLayer* layer, s16 s, u8 c) {
    u16 b;
    u16 a;
    u16 i;
    u16 base0;
    u16 texN = data->texCount;
    u16 n = data->cols + 1;
    bool ok = SetupVF(data->vertCount);
    u16 j;
    u16 k;
    u16 base1;
    if (ok) {
        layer->curVF = (GSgfxVF*)vf;
        layer->primType = 0x98;
        for (i = 0; i < data->rows; i++) {
            base0 = i * n;
            layer->beginSurface(n * 2);
            base1 = (i + 1) * n;
            for (j = 0; j < n; j++) {
                a = j + base0;
                b = j + base1;
                GXWGFifo.u16 = a;
                GXWGFifo.u16 = a;
                for (k = 0; k < texN; k++) {
                    GXWGFifo.u16 = a;
                }
                GXWGFifo.u16 = b;
                GXWGFifo.u16 = b;
                for (k = 0; k < texN; k++) {
                    GXWGFifo.u16 = b;
                }
            }
            layer->endSurface();
        }
    }
}

void GsShapeObject::FreeDisplayListShape() {
    if (dl != 0) {
        GSgfxDLFree(dl);
        GSmemFree(dl);
        dl = 0;
    }
}

void GsShapeObject::CallDisplayListShape(GSgfxLayer* layer, s16 s, u8 c) {
    if (dl != 0) {
        SetupVF(data->vertCount);
        layer->dlDraw((GSgfxDL*)dl);
    } else {
        DrawShapeGfx(layer, s, c);
    }
}

void GsShapeObject::MakeDisplayListShape() {
    dl = GSmemAlloc(0x10);
    if (dl != 0) {
        u16 rows = data->rows;
        u16 size = rows * ((data->cols + 1) * 2);
        memset(dl, 0, 0x10);
        GSgfxDLBegin(dl, vf, rows, size);
        MakeShapeGfxDL();
        GSgfxDLEnd();
    }
}

bool GsShapeObject::RefractTextureCoord(f32 u, f32 v, GSmtx* m1, GSmtx* m2, GSmtx* m3, f32 f);

inline f32 GsShapeObject::RimFromDot(f32 dot) {
    f32 d = (f32)fabs(dot);
    f32 sharp = data->sharp;
    if (d > 1.0f || sharp < 0.00001f) {
        return 1.0f;
    }
    f32 s = sqrtf(1.0f - d);
    f32 th = 1.0f - sharp;
    f32 r;
    if (s <= th) {
        r = 1.0f;
    } else {
        f32 c = (f32)cos((1.5707964f * (s - th)) / sharp);
        r = c * c;
    }
    return r;
}

inline f32 GsShapeObject::RimFactor(Vec3* n, Vec3* v) {
    if (PSVECSquareMag(n) > 9.9999994e-11f && PSVECSquareMag(v) > 9.9999994e-11f) {
        PSVECNormalize(n, n);
        PSVECNormalize(v, v);
        return RimFromDot(PSVECDotProduct(n, v));
    }
    return 0.0f;
}

extern "C++" {
bool GsShapeObject::RefractTextureCoord(f32 u, f32 v, GSmtx* m1, GSmtx* m2, GSmtx* m3, f32 f) {
    int iu;
    f32* proj = GSgfxMatrixGetPtr(4);
    int layer = 0;
    f32 projArr[7];
    f32 vp[6];
    projArr[0] = 0.0f;
    projArr[1] = proj[0];
    projArr[2] = proj[2];
    projArr[3] = proj[5];
    projArr[4] = proj[6];
    projArr[5] = proj[10];
    projArr[6] = proj[11];
    vp[0] = 0.0f;
    vp[2] = 640.0f;
    vp[1] = 0.0f;
    vp[3] = 480.0f;
    vp[4] = 0.0f;
    vp[5] = 1.0f;
    Mtx34 tmp;
    Mtx34 viewMtx;
    int texBytes = data->vertCount * 8;
    for (; layer < data->texCount; layer++) {
        Vec3* pos = data->pos2;
        Vec3* src = (Vec3*)data->pos;
        if (pos == 0) {
            continue;
        }
        f32* out = (f32*)texArray[layer];
        if (out == 0) {
            continue;
        }
        if (layer == 0) {
            PSMTXCopy(m2->m, tmp);
            PSMTXConcat(m1->m, tmp, tmp);
            PSMTXConcat(m3->m, tmp, tmp);
            memcpy(viewMtx, tmp, 0x30);
        } else {
            PSMTXCopy(m2->m, tmp);
            memcpy(out, data->tex, texBytes);
        }
        int cols1 = data->cols + 1;
        int rows1 = data->rows + 1;
        if (u > 1.0f) {
            u -= (f32)(int)u;
        } else if (u < 0.0f) {
            u -= (f32)((int)u - 1);
        }
        if (v > 1.0f) {
            v -= (f32)(int)v;
        } else if (v < 0.0f) {
            v -= (f32)((int)v - 1);
        }
        int y;
        int lastCol;
        lastCol = cols1 - 1;
        y = 0;
        int base = 0;
        iu = (int)(u * data->cols) % data->cols;
        int iv = (int)(v * data->rows) % data->rows;
        f32 fu = data->cols * (u - (f32)iu / data->cols);
        f32 fv = (v - (f32)iv / data->rows);
        fv *= data->rows;
        fu = fu - (f32)(int)fu;
        fv = fv - (f32)(int)fv;
        f32 w01 = fu * (1.0f - fv);
        f32 w11 = (1.0f - fu) * (1.0f - fv);
        f32 w00 = fv * fu;
        f32 w10 = (1.0f - fu) * fv;
        for (; y < rows1; y++) {
            int o2 = base * 8;
            int o = base * 12;
            int x;
            for (x = 0; x < cols1; x++) {
                u16 r = data->rows;
                u16 c = data->cols;
                int a = (x + iu) % c;
                int b = (y + iv) % r;
                Vec3 p;
                if (a == 0 && x == cols1 - 1) {
                    a = c;
                }
                if (b == 0 && y == rows1 - 1) {
                    b = r;
                }
                int k = a + b * cols1;
                if (a == lastCol) {
                    if (b == rows1 - 1) {
                        p = pos[k];
                    } else {
                        int k2 = cols1 + k;
                        Vec3 s0 = vscale(&pos[k2 + 1], w00);
                        Vec3 s1 = vscale(&pos[k2], w10);
                        Vec3 s2 = vscale(&pos[k - 1], w01);
                        Vec3 s3 = vscale(&pos[k], w11);
                        Vec3 t0 = vadd(s3, s2);
                        Vec3 t1 = vadd(t0, s1);
                        p = vadd(t1, s0);
                    }
                } else if (b == rows1 - 1) {
                    int k2 = k - cols1;
                    Vec3 s0 = vscale(&pos[k2 + 1], w00);
                    Vec3 s1 = vscale(&pos[k2], w10);
                    Vec3 s2 = vscale(&pos[k + 1], w01);
                    Vec3 s3 = vscale(&pos[k], w11);
                    Vec3 t0 = vadd(s3, s2);
                    Vec3 t1 = vadd(t0, s1);
                    p = vadd(t1, s0);
                } else {
                    int k2 = cols1 + k;
                    Vec3 s0 = vscale(&pos[k2 + 1], w00);
                    Vec3 s1 = vscale(&pos[k2], w10);
                    Vec3 s2 = vscale(&pos[k + 1], w01);
                    Vec3 s3 = vscale(&pos[k], w11);
                    Vec3 t0 = vadd(s3, s2);
                    Vec3 t1 = vadd(t0, s1);
                    p = vadd(t1, s0);
                }
                PSMTXMultVecSR(tmp, &p, &p);
                Vec3* sv = (Vec3*)((u8*)src + o);
                f32* q = (f32*)((u8*)out + o2);
                if (layer == 0) {
                    f32 sx;
                    f32 sy;
                    f32 sz;
                    GXProject(sv->x, sv->y, sv->z, viewMtx, projArr, vp, &sx, &sy, &sz);
                    if ((f32)fabs(p.x) > 0.00001f || (f32)fabs(p.y) > 0.00001f || (f32)fabs(p.z) > 0.00001f) {
                        PSVECNormalize(&p, &p);
                        if (p.x <= 0.0f) {
                            sx = sx * (1.0f + p.x);
                        } else {
                            sx = p.x * (640.0f - sx) + sx;
                        }
                        if (p.y <= 0.0f) {
                            sy = -p.y * (480.0f - sy) + sy;
                        } else {
                            sy = sy * (1.0f - p.y);
                        }
                    }
                    q[0] = sx / 640.0f;
                    q[1] = sy / 480.0f;
                } else {
                    q[0] += p.x;
                    q[1] += p.y;
                }
                o2 += 8;
                o += 12;
            }
            base += cols1;
        }
    }
    return true;
}
}

bool GsShapeObject::ShadeVertexColor(GSmtx* m1, GSmtx* m2, GSmtx* m3, f32 f, bool b) {
    if (colArray == 0) {
        return false;
    }
    Mtx34 m;
    Mtx34 rot;
    Vec3 nIn;
    Vec3 pIn;
    Vec3 nv;
    Vec3 pv;
    Vec3 up;
    Vec3 axisCross;
    PSMTXCopy(m2->m, m);
    PSMTXConcat(m1->m, m, m);
    PSMTXConcat(m3->m, m, m);
    Vec3* normals;
    Vec3* pos;
    u8* col;
    int o;
    int i;
    int n;
    i = 0;
    o = 0;
    col = (u8*)colArray;
    n = data->vertCount;
    normals = data->pos2;
    pos = (Vec3*)data->pos;
    for (; i < n; i++, normals++, pos++, col += 4, o += 4) {
        nIn.x = normals->x;
        nIn.y = normals->y;
        nIn.z = normals->z;
        pIn.x = pos->x;
        pIn.y = pos->y;
        pIn.z = pos->z;
        PSMTXMultVecSR(m, &nIn, &nv);
        PSMTXMultVec(m, &pIn, &pv);
        f32 depth = pv.z;
        pv.z = depth - f;
        f32 factor;
        if (data->unk9 == 1) {
            nv.y = 0.0f;
            pv.y = 0.0f;
            factor = RimFactor(&nv, &pv);
        } else if (data->unk9 == 2) {
            nv.x = 0.0f;
            pv.x = 0.0f;
            factor = RimFactor(&nv, &pv);
        } else if (data->unk9 == 3) {
            if ((data->kind == 31 && data->unkCE == 1 && b == 0) || (data->kind == 32 && data->unkCC % 2 == 0)) {
                up.x = 0.0f;
                up.y = 0.0f;
                up.z = 1.0f;
                PSMTXMultVecSR(m, &up, &up);
                PSVECCrossProduct(&pv, &up, &axisCross);
                if (PSVECSquareMag(&axisCross) > 9.9999994e-11f && PSVECSquareMag(&pv) > 9.9999994e-11f) {
                    PSVECNormalize(&axisCross, &axisCross);
                    PSVECNormalize(&pv, &pv);
                    PSMTXRotAxisRad(rot, &axisCross, 1.5707964f - (f32)acos(PSVECDotProduct(&up, &pv)));
                    PSMTXMultVecSR(rot, &nv, &nv);
                    factor = RimFromDot(PSVECDotProduct(&nv, &pv));
                } else {
                    factor = 0.0f;
                }
            } else {
                factor = RimFactor(&nv, &pv);
            }
        } else {
            factor = 1.0f;
        }
        if (depth > 0.0f && f > 0.00001f) {
            f32 k;
            if (depth > f) {
                k = 0.0f;
            } else {
                k = (f - depth) / f;
            }
            factor *= k;
        }
        switch (data->mode) {
        case 2:
        case 8:
        case 10:
            ((u8*)colArray)[o + 3] = (u8)(factor * col[3]);
            break;
        default:
            ((u8*)colArray)[o] = (u8)(factor * col[0]);
            ((u8*)colArray)[o + 1] = (u8)(factor * col[1]);
            ((u8*)colArray)[o + 2] = (u8)(factor * col[2]);
            break;
        }
    }
    return true;
}

static inline f32 dotXZ(f32 bx, f32 ax, f32 bz, f32 az) {
    return ax * bx + az * bz;
}

static inline bool billboardAxisY(GSmtx* out, f32 vx, f32 vz, f32 tx, f32 ty, f32 tz) {
    Vec3 v;
    Mtx34 rn;
    Mtx34 rp;
    v.x = vx;
    v.y = 0.0f;
    v.z = vz;
    if ((f32)fabs(v.x) > 0.00001f || (f32)fabs(v.z) > 0.00001f) {
        PSVECNormalize(&v, &v);
        f32 d = dotXZ(v.x, 0.0f, v.z, 1.0f);
        if (d >= -1.0f && d <= 1.0f) {
            f32 a = (f32)acos(d);
            if (v.x > 0.0f) {
                PSMTXRotRad(rp, 'Y', a);
                PSMTXConcat(rp, out->m, out->m);
            } else {
                PSMTXRotRad(rn, 'Y', -a);
                PSMTXConcat(rn, out->m, out->m);
            }
            return true;
        }
    }
    return false;
}

static inline bool billboardAxisFree(GSmtx* out, f32 vx, f32 vy, f32 vz) {
    Vec3 axis;
    Vec3 dir;
    Vec3 up;
    up.x = 0.0f;
    up.y = 0.0f;
    up.z = 1.0f;
    dir.x = vx;
    dir.y = vy;
    dir.z = vz;
    if ((f32)fabs(dir.x) > 0.00001f || (f32)fabs(dir.y) > 0.00001f || (f32)fabs(dir.z) > 0.00001f) {
        PSVECNormalize(&dir, &dir);
        PSVECCrossProduct(&up, &dir, &axis);
        if ((f32)fabs(axis.x) > 0.00001f || (f32)fabs(axis.y) > 0.00001f || (f32)fabs(axis.z) > 0.00001f) {
            PSVECNormalize(&axis, &axis);
            f32 d = PSVECDotProduct(&up, &dir);
            if (d >= -1.0f && d <= 1.0f) {
                Mtx34 r;
                PSMTXRotAxisRad(r, &axis, (f32)acos(d));
                PSMTXConcat(r, out->m, out->m);
                return true;
            }
        }
    }
    return false;
}

void GsShapeObject::MakeMatrixBillboard(GSmtx* m, f32 f) {
    f32 tx = m->m[0][3];
    f32 ty = m->m[1][3];
    f32 tz = m->m[2][3];
    f32 sx = PSVECMag((Vec3*)&m->m[0][0]);
    f32 sy = PSVECMag((Vec3*)&m->m[1][0]);
    PSMTXScale(mtx.m, sx, sy, PSVECMag((Vec3*)&m->m[2][0]));
    switch (data->billboard) {
    case 1:
        PSMTXTransApply(mtx.m, mtx.m, tx, ty, tz);
        break;
    case 2:
        if (!billboardAxisY(&mtx, -tx, f - tz, tx, ty, tz)) {
            memcpy(&mtx, &mtxIdent, 0x30);
        }
        PSMTXTransApply(mtx.m, mtx.m, tx, ty, tz);
        break;
    case 3:
        if (!billboardAxisFree(&mtx, -tx, -ty, f - tz)) {
            memcpy(&mtx, &mtxIdent, 0x30);
        }
        PSMTXTransApply(mtx.m, mtx.m, tx, ty, tz);
        break;
    }
}

static inline f32 fabsFloat(f32 x) {
    (*(int*)&x) &= 0x7fffffff;
    return x;
}

static inline f32 reduceAngle(f32 x) {
    f32 a = x;
    if (x > 3.1415927f) {
        a = x - 6.2831855f * (f32)(int)(x / 6.2831855f);
        if (a > 3.1415927f) {
            a -= 6.2831855f;
        }
    } else if (x < -3.1415927f) {
        a = x - 6.2831855f * (f32)(int)(x / 6.2831855f);
        if (a < -3.1415927f) {
            a += 6.2831855f;
        }
    }
    return a;
}

static inline void fastSinCos(f32 x, f32* ps, f32* pc) {
    f32 a = reduceAngle(x);
    f32 t = 2.0f * (a < -1.5707964f ? -3.1415927f - a : (a <= 1.5707964f ? a : 3.1415927f - a));
    f32 t2 = t * t;
    f32 s = t * (t2 * (t2 * (-0.0000015500992f * t2 + 0.00026041668f) + -0.020833334f) + 0.5f);
    f32 c = t2 * (t2 * (-0.00002170139f * t2 + 0.0026041667f) + -0.125f) + 1.0f;
    if (fabsFloat(a) > 1.5707964f) {
        c = -c;
    }
    *ps = s;
    *pc = c;
}

bool GsShapeObject::WaveTextureCoord(u32 idx, f32 u, f32 v, const GSmtx* m, bool keep) {
    int x;
    f32* out = (f32*)texArray[idx];
    if (out == 0) {
        return false;
    }
    if (idx == 0 && data->texCount >= 2) {
        return false;
    }
    Vec3* pos = data->pos2;
    if (pos == 0) {
        return false;
    }
    if (!keep) {
        memcpy(out, data->tex, data->vertCount * 8);
    }
    int cols1 = data->cols + 1;
    int rows1 = data->rows + 1;
    if (u > 1.0f) {
        u -= (f32)(int)u;
    } else if (u < 0.0f) {
        u -= (f32)((int)u - 1);
    }
    if (v > 1.0f) {
        v -= (f32)(int)v;
    } else if (v < 0.0f) {
        v -= (f32)((int)v - 1);
    }
    int lastCol = cols1 - 1;
    int y = 0;
    int base = 0;
    int iu = (int)(u * data->cols) % data->cols;
    int iv = (int)(v * data->rows) % data->rows;
    f32 fu = data->cols * (u - (f32)iu / data->cols);
    f32 fv = data->rows * (v - (f32)iv / data->rows);
    fu = fu - (f32)(int)fu;
    fv = fv - (f32)(int)fv;
    f32 w00 = fu * fv;
    f32 w10 = (1.0f - fu) * fv;
    f32 w01 = fu * (1.0f - fv);
    f32 w11 = (1.0f - fu) * (1.0f - fv);
    for (; y < rows1; y++) {
        int o = base * 8;
        for (x = 0; x < cols1; x++) {
            u16 c = data->cols;
            u16 r = data->rows;
            int a = (x + iu) % c;
            int b = (y + iv) % r;
            Vec3 p;
            if (a == 0 && x == cols1 - 1) {
                a = c;
            }
            if (b == 0 && y == rows1 - 1) {
                b = r;
            }
            int k = a + b * cols1;
            if (a == lastCol || b == rows1 - 1) {
                p = pos[k];
            } else {
                int k2 = k + cols1;
                Vec3 s0 = vscale(&pos[k2 + 1], w00);
                Vec3 s1 = vscale(&pos[k2], w10);
                Vec3 s2 = vscale(&pos[k + 1], w01);
                Vec3 s3 = vscale(&pos[k], w11);
                Vec3 t0 = vadd(s3, s2);
                Vec3 t1 = vadd(t0, s1);
                p = vadd(t1, s0);
            }
            PSMTXMultVecSR(m->m, &p, &p);
            f32* q = (f32*)((u8*)out + o);
            q[0] += p.x;
            q[1] += p.y;
            o += 8;
        }
        base += cols1;
    }
    return true;
}

bool GsShapeObject::DeformTextureCoord(u32 idx, bool a, const f32* A, const f32* B, bool b, const f32* C) {
    if (texArray[idx] == 0) {
        return false;
    }
    int rows = data->rows;
    int j;
    f32* out = (f32*)texArray[idx];
    int cols = data->cols + 1;
    f32* src = (f32*)data->tex;
    rows += 1;
    f32 off = 0.0f;
    int i = 0;
    for (; i < rows; i++, B++, C++) {
        if (b == 1) {
            off = *C;
        }
        if (a == 1) {
            for (j = 0; j < cols; j++) {
                out[0] = off + A[j];
                out[1] = *B;
                out += 2;
            }
        } else {
            for (j = 0; j < cols; j++) {
                out[0] = src[0] + off;
                out[1] = src[1];
                out += 2;
                src += 2;
            }
        }
    }
    return true;
}

bool GsShapeObject::DeformVertexCoordTorus(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2,
                                           bool angOwn, f32 f3, f32 f4, bool scaled, const f32* C);

bool GsShapeObject::DeformVertexCoordSphere(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2,
                                            bool angOwn, f32 f3, f32 f4, bool scaled, const f32* C);

void GsShapeObject::SetVertexColorAlpha(int mode, int type, f32 f, bool b);

extern "C++" {
bool GsShapeObject::DeformVertexCoordTorus(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2,
                                           bool angOwn, f32 f3, f32 f4, bool scaled, const f32* C) {
    if (posArray == 0) {
        return false;
    }
    Vec3* out = (Vec3*)posArray;
    int cols1 = data->cols + 1;
    int rows1 = data->rows + 1;
    if (!own) {
        f1 = data->sizeX;
        f2 = data->sizeY;
    }
    if (!angOwn) {
        f3 = data->angle;
        f4 = data->angle2;
    }
    if (f3 < 0.00001f) {
        f3 = 0.00001f;
    }
    if (f3 > 360.0f) {
        f3 = 360.0f;
    }
    if (f4 < 0.00001f) {
        f4 = 0.00001f;
    }
    if (f4 > 360.0f) {
        f4 = 360.0f;
    }
    f32 start;
    if (f3 < 0.00001f) {
        start = 0.0f;
    } else {
        start = 0.5f * (360.0f - f3);
    }
    start += 90.0f;
    f32 start2;
    if (f4 < 0.00001f) {
        start2 = 0.0f;
    } else {
        start2 = 0.5f * (360.0f - f4);
    }
    start2 += 180.0f;
    int i;
    const f32* b = B;
    for (i = 0; i < rows1; i++, b++) {
        f32 t;
        if (useUV) {
            t = *b;
        } else {
            t = (f32)i / (f32)(rows1 - 1);
        }
        f32 sn2;
        f32 cs2;
        fastSinCos(f4 * 0.017453292f * t + start2 * 0.017453292f, &sn2, &cs2);
        f32 z = f2 * sn2;
        f32 r = f2 * cs2 + f1;
        const f32* a = A;
        int j;
        for (j = 0; j < cols1; j++, a++, out++) {
            f32 u;
            if (useUV) {
                u = *a;
            } else {
                u = (f32)j / (f32)(cols1 - 1);
            }
            f32 ang = f3 * 0.017453292f * u + start * 0.017453292f;
            f32 sn;
            f32 cs;
            if (j == 0 || j == cols1 - 1) {
                sn = (f32)sin(ang);
                cs = (f32)cos(ang);
            } else {
                fastSinCos(ang, &sn, &cs);
            }
            out->x = r * cs;
            out->y = r * sn;
            out->z = z;
        }
    }
    return true;
}
}

extern "C++" {
bool GsShapeObject::DeformVertexCoordSphere(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2,
                                            bool angOwn, f32 f3, f32 f4, bool scaled, const f32* C) {
    if (posArray == 0) {
        return false;
    }
    Vec3* out = (Vec3*)posArray;
    int cols1 = data->cols + 1;
    int rows1 = data->rows + 1;
    if (!angOwn) {
        f3 = data->angle;
        f4 = data->angle2;
    }
    if (f3 < 0.00001f) {
        f3 = 0.00001f;
    }
    if (f3 > 360.0f) {
        f3 = 360.0f;
    }
    if (f4 < 0.00001f) {
        f4 = 0.00001f;
    }
    if (f4 > 360.0f) {
        f4 = 360.0f;
    }
    f32 start;
    if (f3 < 0.00001f) {
        start = 0.0f;
    } else {
        start = 0.5f * (360.0f - f3);
    }
    start += 90.0f;
    f32 start2;
    if (data->unkCF == 0) {
        start2 = 0.017453292f * (0.5f * -f4);
    } else {
        start2 = -1.5707964f;
    }
    if (!own) {
        f1 = data->sizeX;
    }
    f32 scale;
    int i;
    const f32* b = B;
    const f32* c = C;
    for (i = 0; i < rows1; i++, b++, c++) {
        f32 t;
        if (scaled == 1) {
            scale = 1.0f + *c;
        }
        if (useUV) {
            t = *b;
        } else {
            t = (f32)i / (f32)(rows1 - 1);
        }
        f32 sn2;
        f32 cs2;
        fastSinCos(0.017453292f * f4 * t + start2, &sn2, &cs2);
        f32 r = f1 * cs2;
        f32 z = f1 * sn2;
        const f32* a = A;
        int j;
        for (j = 0; j < cols1; j++, a++, out++) {
            f32 u;
            if (useUV) {
                u = *a;
            } else {
                u = (f32)j / (f32)(cols1 - 1);
            }
            f32 rr = r;
            f32 ang = f3 * 0.017453292f * u + start * 0.017453292f;
            if (scaled == 1) {
                rr = r * scale;
            }
            f32 sn;
            f32 cs;
            if (j == 0 || j == cols1 - 1) {
                sn = (f32)sin(ang);
                cs = (f32)cos(ang);
            } else {
                fastSinCos(ang, &sn, &cs);
            }
            out->x = rr * cs;
            out->y = rr * sn;
            out->z = z;
        }
    }
    return true;
}
}

bool GsShapeObject::DeformVertexCoordSpiral(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2,
                                            bool angOwn, f32 f3, f32 f4, bool scaled, const f32* C) {
    int j;
    f32 q;
    if (posArray == 0) {
        return false;
    }
    Vec3* out = (Vec3*)posArray;
    int cols1 = data->cols + 1;
    int rows1 = data->rows + 1;
    f32 scale;
    Vec3* normals = 0;
    if (!own) {
        f1 = data->sizeX;
        f2 = data->sizeY;
    }
    if (angOwn) {
        normals = data->pos2;
    } else {
        f3 = data->angle;
        f4 = data->angle2;
    }
    f32 diff = f2 - f1;
    f32 height = data->height;
    f32 ang0 = 0.017453292f * f3;
    f32 dang = 0.017453292f * (f4 - f3);
    f32 hh = height * height;
    f32 dd = diff * diff;
    f32 pitchA = data->pitchA;
    f32 pitchB = data->pitchB;
    f32 len = sqrtf(hh + dd);
    bool even = data->unkCC % 2 == 0;
    bool two = data->unkCC == 2;
    f32 qh = 0.25f * hh;
    f32 shrink = 1.0f;
    shrink -= 2.0f / (f32)data->cols;
    int i;
    for (i = 0; i < rows1; i++, B++, C++) {
        f32 t;
        if (scaled == 1) {
            scale = 1.0f + *C;
        }
        if (useUV) {
            t = *B;
        } else {
            t = (f32)i / (f32)(rows1 - 1);
        }
        for (j = 0; j < (u8)cols1; j++) {
            const f32* a = &A[j];
            f32 u;
            if (useUV) {
                u = *a;
            } else {
                u = (f32)j / (f32)(cols1 - 1);
            }
            f32 inv = 1.0f - u;
            f32 w = u;
            f32 ang = ang0 + dang * u;
            f32 z0 = pitchA * inv;
            z0 += pitchB * u;
            f32 sn;
            f32 cs;
            f32 r;
            if (even || len < 0.00001f) {
                if (two) {
                    w = (u - 0.5f) * shrink + 0.5f;
                    r = f1 * (1.0f - w) + f2 * w;
                    f32 h = height * (f32)fabs(w - 0.5f);
                    q = -(h * h - qh);
                    if (q > 0.0f) {
                        r += sqrtf(q);
                    }
                } else {
                    r = f1 * inv + f2 * u;
                }
                if (scaled == 1) {
                    r *= scale;
                }
                fastSinCos(ang, &sn, &cs);
                out->x = r * cs;
                out->y = r * sn;
                out->z = z0 * t + (height * w - 0.5f * z0);
            } else {
                f32 w2 = z0 / len;
                f32 v2 = (u - 0.5f) * (1.0f - w2) + 0.5f;
                f32 m = -(0.5f * w2 - v2);
                m += w2 * t;
                if (two) {
                    m = ((m - 0.5f) * shrink) + 0.5f;
                    r = f1 * (1.0f - m) + f2 * m;
                    f32 h = height * (f32)fabs(m - 0.5f);
                    f32 q = -(h * h - qh);
                    if (q > 0.0f) {
                        r += sqrtf(q);
                    }
                } else {
                    r = f1 * (1.0f - m) + f2 * m;
                }
                if (scaled == 1) {
                    r *= scale;
                }
                fastSinCos(ang, &sn, &cs);
                f32 hz = w2 * height;
                out->x = r * cs;
                out->y = r * sn;
                out->z = hz * t + (height * v2 - 0.5f * hz);
            }
            out++;
            if (normals != 0) {
                normals->x = cs;
                normals->y = sn;
                normals->z = 0.0f;
                normals++;
            }
        }
    }
    return true;
}

bool GsShapeObject::DeformVertexCoordCylinderEx(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2,
                                                bool angOwn, f32 f3, bool scaled, const f32* C) {
    int j;
    if (posArray == 0) {
        return false;
    }
    Vec3* out = (Vec3*)posArray;
    int cols1 = data->cols + 1;
    int rows1 = data->rows + 1;
    f32 scale;
    f3 = angOwn ? f3 : data->angle;
    if (f3 < 0.00001f) {
        f3 = 0.0f;
    }
    if (f3 > 360.0f) {
        f3 = 360.0f;
    }
    f32 start;
    if (f3 < 0.00001f) {
        start = 0.0f;
    } else {
        start = 0.5f * (360.0f - f3);
    }
    f32 angStep = f3 * 0.017453292f;
    start = (start + 90.0f) * 0.017453292f;
    if (!own) {
        f1 = data->sizeX;
        f2 = data->sizeY;
    }
    f32 rad = f1 - f2;
    f32 height = data->height;
    int i;
    const f32* b = B;
    const f32* c = C;
    for (i = 0; i < rows1; i++, c++, b++) {
        f32 t;
        const f32* a = A;
        if (scaled == 1) {
            scale = 1.0f + *c;
        }
        if (useUV) {
            t = *b;
        } else {
            t = (f32)i / (f32)(rows1 - 1);
        }
        f32 r = rad * t + f2;
        f32 z = height * t;
        for (j = 0; j < cols1; j++, a++, out++) {
            f32 u;
            if (useUV) {
                u = *a;
            } else {
                u = (f32)j / (f32)(cols1 - 1);
            }
            f32 rr = r;
            f32 ang = angStep * u + start;
            f32 sn;
            f32 cs;
            if (scaled == 1) {
                rr = r * scale;
            }
            if (j == 0 || j == cols1 - 1) {
                sn = (f32)sin(ang);
                cs = (f32)cos(ang);
            } else {
                fastSinCos(ang, &sn, &cs);
            }
            out->x = rr * cs;
            out->y = rr * sn;
            out->z = z;
        }
    }
    return true;
}

bool GsShapeObject::DeformVertexCoord(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2,
                                      bool angOwn, f32 f3, f32 f4, bool scaled, const f32* C) {
    GsShapeData* d = data;
    int rows1;
    int cols1;
    Vec3* out;
    f32 offY;
    f32 offX;
    f32 sy;
    f32 sx;
    f32 shear;
    int i;
    int j;
    f32 z;
    f32 t;
    f32 dx;
    f32 y;
    f32 u;
    switch (d->kind) {
    case 30: {
        out = (Vec3*)posArray;
        if (out == 0) {
            return false;
        }
        sx = d->sizeX;
        offX = 0.5f * -sx;
        sy = d->sizeY;
        offY = 0.5f * -sy;
        cols1 = d->cols + 1;
        rows1 = d->rows + 1;
        shear = 0.0f;
        f3 = angOwn ? f3 : d->angle;
        if ((f32)fabs(f3) > 0.00001f) {
            shear = data->sizeY * (f32)tan(0.017453292f * f3);
        }
        i = 0;
        const f32* b = B;
        const f32* c = C;
        for (; i < rows1; i++, c++, b++) {
            z = scaled ? *c : 0.0f;
            if (useUV) {
                t = *b;
            } else {
                t = (f32)i / (f32)(rows1 - 1);
            }
            const f32* a = A;
            dx = shear * t;
            y = sy * t + offY;
            for (j = 0; j < cols1; j++, a++, out++) {
                if (useUV) {
                    u = *a;
                } else {
                    u = (f32)j / (f32)(cols1 - 1);
                }
                out->x = sx * u + offX + dx;
                out->y = y;
                out->z = z;
            }
        }
        return true;
    }
    case 31:
        return DeformVertexCoordCylinderEx(useUV, A, B, own, f1, f2, angOwn, f3, scaled, C);
    case 32:
        return DeformVertexCoordSpiral(useUV, A, B, own, f1, f2, angOwn, f3, f4, scaled, C);
    case 33:
        return DeformVertexCoordSphere(useUV, A, B, own, f1, f2, angOwn, f3, f4, scaled, C);
    case 34:
        return DeformVertexCoordTorus(useUV, A, B, own, f1, f2, angOwn, f3, f4, scaled, C);
    }
    return false;
}

void GsShapeObject::SetVertexColorGradation(u8 perVertex, const tagGScol4ub* colors, int mode, f32 f, bool b) {
    if (colArray != 0) {
            int cols = data->cols + 1;
        int rows = data->rows + 1;
        tagGScol4ub* dst = (tagGScol4ub*)colArray;
        int i;
        int j;
        if (mode == 2 || mode == 4) {
            for (i = 0; i < rows; i++) {
                const tagGScol4ub* s = colors;
                if (perVertex == 0) {
                    for (j = 0; j < cols; j++, s++, dst++) {
                        dst->r = s->r;
                        dst->g = s->g;
                        dst->b = s->b;
                        dst->a = (u8)(f * s->a);
                    }
                } else {
                    for (j = 0; j < cols; j++, dst++) {
                        dst->r = colors[i].r;
                        dst->g = colors[i].g;
                        dst->b = colors[i].b;
                        dst->a = (u8)(f * colors[i].a);
                    }
                }
            }
        } else {
            for (i = 0; i < rows; i++) {
                const tagGScol4ub* s = colors;
                if (perVertex == 0) {
                    for (j = 0; j < cols; j++, s++, dst++) {
                        dst->r = (u8)(f * ((f32)s->r * ((f32)s->a / 255.0f)));
                        dst->g = (u8)(f * ((f32)s->g * ((f32)s->a / 255.0f)));
                        dst->b = (u8)(f * ((f32)s->b * ((f32)s->a / 255.0f)));
                        dst->a = s->a;
                    }
                } else {
                    for (j = 0; j < cols; j++, dst++) {
                        dst->r = (u8)(f * ((f32)colors[i].r * ((f32)colors[i].a / 255.0f)));
                        dst->g = (u8)(f * ((f32)colors[i].g * ((f32)colors[i].a / 255.0f)));
                        dst->b = (u8)(f * ((f32)colors[i].b * ((f32)colors[i].a / 255.0f)));
                        dst->a = colors[i].a;
                    }
                }
            }
        }
    }
}

extern "C++" {
void GsShapeObject::SetVertexColorAlpha(int mode, int type, f32 f, bool b) {
    if (colArray != 0) {
        int cols = data->cols + 1;
        int rows = data->rows + 1;
        tagGScol4ub* src = (tagGScol4ub*)data->col;
        tagGScol4ub* dst = (tagGScol4ub*)colArray;
        int j;
        int i;
        if (mode == 0) {
            if (type != 5) {
                u8 a = (u8)(255.0f * f);
                for (i = 0; i < rows; i++) {
                    for (j = 0; j < cols; j++) {
                        dst->r = src->r;
                        dst->g = src->g;
                        dst->b = src->b;
                        dst->a = a;
                        dst++;
                        src++;
                    }
                }
            } else {
                for (i = 0; i < rows; i++) {
                    for (j = 0; j < cols; j++) {
                        dst->r = (u8)(src->r * f);
                        dst->g = (u8)(src->g * f);
                        dst->b = (u8)(src->b * f);
                        dst->a = 0xFF;
                        dst++;
                        src++;
                    }
                }
            }
        } else if (type != 5) {
            for (i = 0; i < rows; i++) {
                for (j = 0; j < cols; j++) {
                    dst->r = src->r;
                    dst->g = src->g;
                    dst->b = src->b;
                    dst->a = (u8)(src->a * f);
                    dst++;
                    src++;
                }
            }
        } else {
            for (i = 0; i < rows; i++) {
                for (j = 0; j < cols; j++) {
                    u8 a = src->a;
                    u8 r = src->r;
                    u8 g = src->g;
                    u8 bl = src->b;
                    f32 s = (a / 255.0f) * f;
                    dst->r = (u8)(r * s);
                    dst->g = (u8)(g * s);
                    dst->b = (u8)(bl * s);
                    dst->a = a;
                    dst++;
                    src++;
                }
            }
        }
    }
}
}

void GsShapeObject::SetVertexColorSpecify(const tagGScol4ub& c, bool b) {
    if (colArray != 0) {
        int j;
        int i;
        int cols = data->cols + 1;
        int rows = data->rows + 1;
        tagGScol4ub* p = (tagGScol4ub*)colArray;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                p->r = c.r;
                p->g = c.g;
                p->b = c.b;
                p->a = c.a;
                p++;
            }
        }
    }
}
