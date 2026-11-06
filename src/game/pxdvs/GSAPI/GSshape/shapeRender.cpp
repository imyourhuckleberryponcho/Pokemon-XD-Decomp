#include <dolphin/types.h>
#include <game/gcdata.h>
#ifndef __MWERKS__
#include <stddef.h>
#endif

struct tagGScol4ub {
    u8 r, g, b, a;
};
typedef f32 Mtx34[3][4];
struct GSmtx {
    Mtx34 m;
};
struct GsVec2 {
    f32 v[2];
};
struct GStexture {
    u8 unk0[7];
    u8 reload;
};
struct GSgfxVF;
enum GSgfxLayerID {};
enum GSgfxLayerPass {};
enum GSgfxTgenFunc {};
enum GSgfxTgenSrc {};

struct tagGsFilePrimKeyFrame {
    u8 unk0[4];
    u32 time;
    u8 visible;
    u8 unk9[3];
    u8 texAnim[4];
    f32 scale[3];
    f32 trans[3];
    f32 pivot[3];
    f32 rot[3];
    u8 color[4];
    f32 radius[2];
    u8 unk4C[8];
    f32 showAngle[2];
    f32 texScale[4][2];
    f32 texOffset[4][2];
    u8 texColor[4][4];
    u8 texColorLow[4][4];
    u8 nScale[3];
    u8 nTrans[3];
    u8 nPivot[3];
    u8 nRot[3];
    u8 nColor[4];
    u8 nRadius[2];
    u8 unkCE[2];
    u8 nShowAngle[2];
    u8 nTexScale[4][2];
    u8 nTexOffset[4][2];
    u8 nTexColor[4][4];
    u8 nTexColorLow[4][4];
    u8 unk102[2];
    const f32* cScale[3];
    const f32* cTrans[3];
    const f32* cPivot[3];
    const f32* cRot[3];
    const f32* cColor[4];
    const f32* cRadius[2];
    const f32* unk14C[2];
    const f32* cShowAngle[2];
    const f32* cTexScale[4][2];
    const f32* cTexOffset[4][2];
    const f32* cTexColor[4][4];
    const f32* cTexColorLow[4][4];
    u16 nDeformU;
    u16 nDeformV;
    const f32* deformU;
    const f32* deformV;
    u16 nTwist;
    u8 unk22A[2];
    const f32* twist;
    u8 unk230[0xC];
    u8 gradKind;
    u8 unk23D[3];
    u16 nGrad0;
    u16 nGrad1;
    const tagGScol4ub* grad0;
    const tagGScol4ub* grad1;
};

struct tagGsFilePrimObjectEntry {
    u8 unk0[4];
    u16 shapeIndex;
    u16 count;
    u32 frameOffset;
    u8 unkC[2];
    u8 radius;
    u8 unkF;
    u8 showAngle;
    u8 twist;
    u8 twistKey;
    u8 colorKey;
    u8 colorMode;
    u8 uvDeform;
    u8 uvDeformKey;
    u8 unk17;
    u8 texAnim[4];
};

class GsKeyObject {
public:
    bool GetShapeMatrix(GSmtx* scaleMtx, GSmtx* mtx, const tagGsFilePrimObjectEntry* entry, u8 count,
                        const u8* order, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                        f32 t) const;
    bool GetGradationParameter(u8* kind, tagGScol4ub* out, const tagGsFilePrimKeyFrame* a,
                               const tagGsFilePrimKeyFrame* b, f32 t) const;
    bool GetTwistParameter(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const;
    bool GetDeformParameterV(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                             f32 t) const;
    bool GetDeformParameterU(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                             f32 t) const;
    bool GetLinearParameterV(f32* out, const tagGsFilePrimKeyFrame* a);
    bool GetLinearParameterU(f32* out, const tagGsFilePrimKeyFrame* a);
    tagGScol4ub GetTextureColorLow(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t,
                                   u32 idx) const;
    tagGScol4ub GetTextureColor(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t,
                                u32 idx) const;
    GsVec2 GetTextureOffset(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t, u32 idx) const;
    GsVec2 GetTextureScale(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t, u32 idx) const;
    bool GetShapeShowAngle(f32* o0, f32* o1, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                           f32 t) const;
    bool GetShapeRadius(f32* o0, f32* o1, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                        f32 t) const;
    f32 GetShapeColorAlpha(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const;
    tagGScol4ub GetShapeColor(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const;
    bool GetFrameInterval(u32 frame, tagGsFilePrimKeyFrame*& a, tagGsFilePrimKeyFrame*& b, f32& t);

    tagGsFilePrimObjectEntry* entry;
    tagGsFilePrimKeyFrame** frames;
    u8 enabled;
    u8 pad9[3];
    GSmtx texMtx[4];
    GSmtx mtxA;
    GSmtx mtxB;
};

struct GsShapeTexInfo {
    u8 unk0[4];
    u16 index;
    u8 unk6[5];
    u8 kind;
    f32 u0;
    f32 u1;
    f32 v0;
    f32 v1;
};

struct GsShapeData {
    u8 unk0[4];
    u8 enabled;
    u8 unk5[3];
    u8 mode;
    u8 vertexColorKind;
    u8 unkA[4];
    u16 vertCount;
    f32* pos;
    u32* col;
    f32* tex;
    void* vertexColors;
    u8 unk20[6];
    u16 texCount;
    GsShapeTexInfo* texInfo[4];
    u8 unk38[0xCD - 0x38];
    u8 billboard;
    u8 unkCE[0xDC - 0xCE];
};

struct GsShapeTexture {
    void* info;
    GStexture* tex;
};

struct GSgfxMatrixEntry {
    int unk0;
    GSmtx m;
};
struct GSgfxMatrixStack {
    void push(GSmtx* m);
    void pushMult(GSmtx* m);
    void pop();
    GSgfxMatrixEntry* base;
    GSgfxMatrixEntry* top;
    GSgfxMatrixEntry* last;
};

#define GFX_DIRTY(word, bits, group)  \
    (&dirty[0].geom)[word] |= (bits); \
    dirty[0].groups |= (group);       \
    (&dirty[1].geom)[word] |= (bits); \
    dirty[1].groups |= (group);

enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void textureCopy(GSgfxLayerPass pass, GStexture* tex, bool a, u8* b, bool c, bool d, bool e);
    void tgenFunc(u8 unit, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* m, bool normalize, GSmtx* post);

    inline void tevStageCount(u8 n) {
        (*(u8*)&this->hw.nTevStages) = n;
        GFX_DIRTY(8, 1, 8)
    }
    inline void tevColor(u8 i, tagGScol4ub c) {
        *(u32*)&((tagGScol4ub*)this->hw.kcolor)[i] = *(u32*)&c;
        GFX_DIRTY(19, 1 << i, 0x10)
    }

};

class GsShapeObject {
public:
    int GetPolygonCount();
    bool FreeShapeDrawBuffer(s16 idx);
    bool CreateShapeDrawBuffer(s16 idx);
    void MakeMatrixBillboard(GSmtx* m, f32 f);
    bool DeformVertexCoord(bool useUV, const f32* A, const f32* B, bool own, f32 f1, f32 f2, bool angOwn, f32 f3,
                           f32 f4, bool scaled, const f32* C);
    bool WaveTextureCoord(u32 idx, f32 u, f32 v, const GSmtx* m, bool keep);
    bool DeformTextureCoord(u32 idx, bool a, const f32* A, const f32* B, bool b, const f32* C);
    bool RefractTextureCoord(f32 u, f32 v, GSmtx* m1, GSmtx* m2, GSmtx* m3, f32 f);
    bool ShadeVertexColor(GSmtx* m1, GSmtx* m2, GSmtx* m3, f32 f, bool b);
    void SetVertexColorGradation(u8 perVertex, const tagGScol4ub* colors, int mode, f32 f, bool b);
    void SetVertexColorAlpha(int mode, int type, f32 f, bool b);
    void SetVertexColorSpecify(const tagGScol4ub& c, bool b);
    void SetStateTexture(GSgfxLayer* l, GsShapeTexture* texes, GStexture* override);
    void SetStateMode(GSgfxLayer* layer);
    void FreeDisplayListShape();
    void CallDisplayListShape(GSgfxLayer* layer, s16 s, u8 c);
    void MakeDisplayListShape();

    GsShapeData* data;
    u8 vf[0x440];
    void* posArray;
    void* colArray;
    void* texArray[4];
    u8 numTev;
    tagGScol4ub tevColor[4];
    u8 pad46D[3];
    GSmtx mtx;
    void* dl;
    void* drawBuf[256];
};

struct GsShapeAnimHeader {
    u8 unk0[4];
    u32 frameCount;
    u32 fps;
    u16 keyCount;
    u8 unkE[2];
    u32 keyOffset;
    u8 loopMode;
    u8 orderCount;
    u8 unk16[2];
    u8 order[1];
};

class GsShapeRender {
public:
    void ExecuteFreeInstance();
    void SwapBuffers();
    GSgfxLayerID GetLayerId() const;
    s32 GetInstancedMemorySizeAll();
    s32 GetUsedMemorySizeAll();
    void FreeShapeRenderDrawBuffer(s16 id);
    s16 CreateShapeRenderDrawBuffer();
    void Render(s16 id, GSgfxLayerID layer);
    void Update(f32 time, s16 id);
    bool LoadShapeRender(void* file);
    void FreeShapeRender();
    void InitShapeRender();

    inline void FlushFreeList();

    u8 loaded;
    u8 pad1[3];
    u32 frame;
    s32 unk8;
    GSgfxLayerID layerId;
    u32 unk10;
    GsShapeAnimHeader* anim;
    u16 keyCount;
    u8 pad1A[2];
    GsKeyObject* keys;
    u16 shapeCount;
    u8 pad22[2];
    GsShapeObject* shapes;
    u16 texCount;
    u8 pad2A[2];
    GsShapeTexture* texes;
    u16 maxU;
    u16 maxV;
    u16 maxTwist;
    u16 maxGrad;
    f32* paramU;
    f32* paramV;
    f32* paramTwist;
    tagGScol4ub* paramGrad;
    GStexture* refractTex;
    s16 usedCount;
    s16 searchIndex;
    u8 used[256];
    u8 releasedBuf;
    u8 bufIndex;
    u16 tokens[2][256];
    u8 pad552[2];
    s32 polygonCount;
    s32 usedMemory;
    s32 instancedMemory;
    s16 freeCount[2];
    s16 freeList[2][256];
};

extern "C" {
void OSReport(const char* fmt, ...);
extern GSmtx mtxIdent;
void* memcpy(void* dst, const void* src, u32 n);
void* memset(void* dst, int c, u32 n);
void* GSmemAlloc(u32 size);
void GSmemFree(void* p);
GStexture* GStextureCreate(u16 width, u16 height, s32 format, s32 tlutFormat, u8 mipLevels);
GStexture* GStextureLoad(void* data, void* info);
void GStextureFree(GStexture* tex);
void GStextureSetWrap(GStexture* tex, u32 wrapS, u32 wrapT);
void GSgfxTokenWaitForClear(u16 token);
u16 GSgfxTokenMark(void);
GSgfxLayer* GSgfxLayerFindByID(GSgfxLayerID id);
void* GScameraGetActiveCamera(void);
void GScameraGetPerspective(void* camera, f32* fov, f32* aspect, f32* nearZ, f32* farZ);
void GSgfxVFInit(GSgfxVF* vf, s32 a, s32 b, s32 c, s32 d);
void GSgfxVFCreate(GSgfxVF* vf);
void GSgfxVFFree(GSgfxVF* vf);
void GSgfxVFSetElement(GSgfxVF* vf, s32 a, s32 b, s32 c, s32 d);
void PSMTXScale(f32 m[3][4], f32 x, f32 y, f32 z);
void PSMTXScaleApply(const f32 src[3][4], f32 dst[3][4], f32 x, f32 y, f32 z);
void PSMTXTrans(f32 m[3][4], f32 x, f32 y, f32 z);
void PSMTXTransApply(const f32 src[3][4], f32 dst[3][4], f32 x, f32 y, f32 z);
}

extern "C" {
s32 g_instancedMemorySizeAll;
}

template <class T>
static inline void relocate(T*& p, u8* base) {
    p = (T*)((u8*)p + (u32)base);
}

#ifndef __MWERKS__
struct ShapeDoneSet {
    u32* slot;
    u32 cap;
    u32 used;
};

static bool _shapeFirstTime(ShapeDoneSet* set, u32 off) {
    u32 key = off + 1;
    u32 i;
    if (set->used * 2 >= set->cap) {
        ShapeDoneSet big;
        big.cap = set->cap != 0 ? set->cap * 2 : 1024;
        big.used = 0;
        big.slot = (u32*)GSmemAlloc(big.cap * sizeof(u32));
        memset(big.slot, 0, big.cap * sizeof(u32));
        for (i = 0; i < set->cap; i++) {
            if (set->slot[i] != 0) {
                _shapeFirstTime(&big, set->slot[i] - 1);
            }
        }
        if (set->slot != 0) {
            GSmemFree(set->slot);
        }
        *set = big;
    }
    for (i = (key * 2654435761u) & (set->cap - 1);; i = (i + 1) & (set->cap - 1)) {
        if (set->slot[i] == key) {
            return false;
        }
        if (set->slot[i] == 0) {
            set->slot[i] = key;
            set->used++;
            return true;
        }
    }
}

static void _shapeFix32(ShapeDoneSet* set, u8* base, u32 off, u32 n) {
    u32 i;
    if (n == 0 || off == 0 || !_shapeFirstTime(set, off)) {
        return;
    }
    for (i = 0; i < n; i++) {
        GC_FIX32(*(u32*)(base + off + i * 4));
    }
}

static void _shapeEntryToNative(ShapeDoneSet* set, u8* base, u32 off) {
    u8* e = base + off;
    u32 o;
    if (!_shapeFirstTime(set, off | 0x80000000)) {
        return;
    }
    GC_FIX16(*(u16*)(e + 0x4));
    GC_FIX16(*(u16*)(e + 0x6));
    GC_FIX32(*(u32*)(e + 0x8));
    for (o = 0x38; o < 0x58; o += 4) {
        GC_FIX32(*(u32*)(e + o));
    }
    for (o = 0x70; o < 0x7C; o += 4) {
        GC_FIX32(*(u32*)(e + o));
    }
    for (o = 0x94; o < 0xB4; o += 4) {
        GC_FIX32(*(u32*)(e + o));
    }
}

static tagGsFilePrimKeyFrame* _shapeKeyFrameToNative(ShapeDoneSet* set, u8* base, u32 off, const tagGsFilePrimObjectEntry* entry) {
    u8* g = base + off;
    tagGsFilePrimKeyFrame* kf = (tagGsFilePrimKeyFrame*)GSmemAlloc(sizeof(tagGsFilePrimKeyFrame));
    const f32** slots = (const f32**)&kf->cScale[0];
    const u8* counts = &kf->nScale[0];
    u32 i;
    memset(kf, 0, sizeof(tagGsFilePrimKeyFrame));
    memcpy(kf, g, 0x104);
    GC_FIX32(kf->time);
    GC_FIXF32N(kf->scale, 12);
    GC_FIXF32N(kf->radius, 2);
    GC_FIXF32N(kf->showAngle, 2);
    GC_FIXF32N(kf->texScale, 16);
    for (i = 0; i < 70; i++) {
        u32 o = GC_AT(u32, g, 0x104 + i * 4);
        slots[i] = (const f32*)(base + o);
        if (i != 18 && i != 19) {
            _shapeFix32(set, base, o, counts[i] * 2);
        }
    }
    kf->nDeformU = GC_AT(u16, g, 0x21C);
    kf->nDeformV = GC_AT(u16, g, 0x21E);
    kf->deformU = (const f32*)(base + GC_AT(u32, g, 0x220));
    kf->deformV = (const f32*)(base + GC_AT(u32, g, 0x224));
    kf->nTwist = GC_AT(u16, g, 0x228);
    memcpy(kf->unk22A, g + 0x22A, 2);
    kf->twist = (const f32*)(base + GC_AT(u32, g, 0x22C));
    memcpy(kf->unk230, g + 0x230, 0xC);
    kf->gradKind = g[0x23C];
    memcpy(kf->unk23D, g + 0x23D, 3);
    kf->nGrad0 = GC_AT(u16, g, 0x240);
    kf->nGrad1 = GC_AT(u16, g, 0x242);
    kf->grad0 = (const tagGScol4ub*)(base + GC_AT(u32, g, 0x244));
    kf->grad1 = (const tagGScol4ub*)(base + GC_AT(u32, g, 0x248));
    if (entry->uvDeform == 1 || entry->twist == 1 || entry->radius == 1 || entry->showAngle == 1) {
        _shapeFix32(set, base, GC_AT(u32, g, 0x220), kf->nDeformU);
        _shapeFix32(set, base, GC_AT(u32, g, 0x224), kf->nDeformV);
    }
    if (entry->twist != 0) {
        _shapeFix32(set, base, GC_AT(u32, g, 0x22C), kf->nTwist);
    }
    return kf;
}

static GsShapeData* _shapeDataToNative(ShapeDoneSet* set, u8* base, u32 off) {
    u8* g = base + off;
    GsShapeData* d = (GsShapeData*)GSmemAlloc(sizeof(GsShapeData));
    u8* tail = (u8*)d + offsetof(GsShapeData, unk38) - 0x38;
    u32 n;
    u32 k;
    memset(d, 0, sizeof(GsShapeData));
    memcpy(d, g, 0x10);
    memcpy(d->unk20, g + 0x20, 8);
    memcpy(d->unk38, g + 0x38, 0xDC - 0x38);
    GC_FIX16(*(u16*)((u8*)d + 0xA));
    GC_FIX16(*(u16*)((u8*)d + 0xC));
    GC_FIX16(d->vertCount);
    GC_FIX16(d->texCount);
    GC_FIX16(*(u16*)(tail + 0x38));
    GC_FIX32(*(u32*)(tail + 0x3C));
    GC_FIX32(*(u32*)(tail + 0x40));
    for (k = 0x5C; k < 0x6C; k += 4) {
        GC_FIX32(*(u32*)(tail + k));
    }
    GC_FIX32(*(u32*)(tail + 0xC8));
    GC_FIX32(*(u32*)(tail + 0xD0));
    n = d->vertCount;
    d->pos = (f32*)(base + GC_AT(u32, g, 0x10));
    d->col = (u32*)(base + GC_AT(u32, g, 0x14));
    d->tex = (f32*)(base + GC_AT(u32, g, 0x18));
    _shapeFix32(set, base, GC_AT(u32, g, 0x10), n * 3);
    _shapeFix32(set, base, GC_AT(u32, g, 0x18), n * 2);
    if (GC_AT(u32, g, 0x1C) != 0) {
        d->vertexColors = base + GC_AT(u32, g, 0x1C);
        _shapeFix32(set, base, GC_AT(u32, g, 0x1C), n * 3);
    }
    for (k = 0; k < d->texCount && k < 4; k++) {
        u32 o = GC_AT(u32, g, 0x28 + k * 4);
        if (o != 0) {
            u8* ti = base + o;
            d->texInfo[k] = (GsShapeTexInfo*)ti;
            if (_shapeFirstTime(set, o | 0x40000000)) {
                GC_FIX16(*(u16*)(ti + 4));
                GC_FIXF32N(ti + 0xC, 4);
            }
        }
    }
    return d;
}
#endif

static inline u8 isBillboard(const GsShapeData* d) {
    u8 r = 0;
    if (d->billboard >= 1 && d->billboard <= 3) {
        r = 1;
    }
    return r;
}

inline void GsShapeRender::FlushFreeList() {
    s16 i;
    for (i = 0; i < freeCount[bufIndex]; i++) {
        s16 id = freeList[bufIndex][i];
        if (tokens[bufIndex == 0][id] != 0) {
            GSgfxTokenWaitForClear(tokens[bufIndex == 0][id]);
        }
        if (tokens[bufIndex][id] != 0) {
            GSgfxTokenWaitForClear(tokens[bufIndex][id]);
        }
        tokens[0][id] = 0;
        tokens[1][id] = 0;
        for (u16 j = 0; j < shapeCount; j++) {
            if (shapes[j].FreeShapeDrawBuffer(id) == 1) {
                GsShapeData* d = shapes[0].data;
                s32 size = d->vertCount * (d->texCount * 8 + 0x10) * 2;
                instancedMemory -= size;
                g_instancedMemorySizeAll -= size;
            }
        }
        usedCount--;
        used[id] = 0;
    }
    freeCount[bufIndex] = 0;
}

void GsShapeRender::InitShapeRender() {
    loaded = 0;
    frame = 0;
    unk8 = -1;
    anim = 0;
    keyCount = 0;
    keys = 0;
    shapeCount = 0;
    shapes = 0;
    texCount = 0;
    texes = 0;
    maxU = 0;
    paramU = 0;
    maxV = 0;
    paramV = 0;
    maxTwist = 0;
    paramTwist = 0;
    maxGrad = 0;
    paramGrad = 0;
    refractTex = 0;
    unk10 = 0;
    usedCount = 0;
    searchIndex = 0;
    memset(used, 0, 0x100);
    releasedBuf = 0xFF;
    bufIndex = 0;
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 0x100; j++) {
            tokens[i][j] = 0;
        }
    }
    polygonCount = 0;
    usedMemory = 0;
    instancedMemory = 0;
    freeCount[0] = 0;
    freeCount[1] = 0;
}

void GsShapeRender::FreeShapeRender() {
    s32 j;
    s32 i;
    loaded = 0;
    frame = 0;
    unk8 = -1;
    anim = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 0x100; j++) {
            if (tokens[i][j] != 0) {
                GSgfxTokenWaitForClear(tokens[i][j]);
                tokens[i][j] = 0;
            }
        }
    }
    for (i = 0; i < shapeCount; i++) {
        GsShapeObject* s = &shapes[i];
        GSgfxVFFree((GSgfxVF*)s->vf);
        s->posArray = 0;
        s->colArray = 0;
        s->texArray[0] = 0;
        s->texArray[1] = 0;
        s->texArray[2] = 0;
        s->texArray[3] = 0;
        s->FreeDisplayListShape();
    }
    i = 0;
    do {
        if (used[i] == 1) {
            for (j = 0; j < shapeCount; j++) {
                if (shapes[j].FreeShapeDrawBuffer(i) == 1) {
                    GsShapeData* d = shapes[0].data;
                    s32 size = d->vertCount * (d->texCount * 8 + 0x10) * 2;
                    instancedMemory -= size;
                    g_instancedMemorySizeAll -= size;
                }
                used[i] = 0;
            }
        }
        i++;
        usedCount = 0;
    } while (i < 0x100);
#ifndef __MWERKS__
    for (i = 0; keys != 0 && i < keyCount; i++) {
        for (s32 j = 0; j < keys[i].entry->count; j++) {
            GSmemFree(keys[i].frames[j]);
        }
        GSmemFree(keys[i].frames);
    }
    for (i = 0; shapes != 0 && i < shapeCount; i++) {
        GSmemFree(shapes[i].data);
    }
#endif
    if (keys != 0) {
        GSmemFree(keys);
        keyCount = 0;
        keys = 0;
    }
    if (shapes != 0) {
        GSmemFree(shapes);
        shapeCount = 0;
        shapes = 0;
    }
    if (texes != 0) {
        GSmemFree(texes);
        texCount = 0;
        texes = 0;
    }
    if (paramU != 0) {
        GSmemFree(paramU);
        maxU = 0;
        paramU = 0;
    }
    if (paramV != 0) {
        GSmemFree(paramV);
        maxV = 0;
        paramV = 0;
    }
    if (paramTwist != 0) {
        GSmemFree(paramTwist);
        maxTwist = 0;
        paramTwist = 0;
    }
    if (paramGrad != 0) {
        GSmemFree(paramGrad);
        maxGrad = 0;
        paramGrad = 0;
    }
    if (refractTex != 0) {
        GStextureFree(refractTex);
        refractTex = 0;
    }
    polygonCount = 0;
    usedMemory = 0;
    instancedMemory = 0;
    freeCount[0] = 0;
    freeCount[1] = 0;
}

bool GsShapeRender::LoadShapeRender(void* file) {
    tagGsFilePrimObjectEntry* entry;
    u8* base = (u8*)file;
    loaded = 0;
    FreeShapeRender();
    switch (base[0xA]) {
    case 0:
        layerId = (GSgfxLayerID)2;
        break;
    case 1:
        layerId = (GSgfxLayerID)4;
        break;
    default:
        layerId = (GSgfxLayerID)2;
        break;
    }
#ifdef __MWERKS__
    anim = (GsShapeAnimHeader*)(base + *(u32*)(base + 0xC));
#else
    {
        static void* s_loaded[64];
        static u32 s_loadedCount;
        for (u32 k = 0; k < s_loadedCount && k < 64; k++) {
            if (s_loaded[k] == file) {
                OSReport("LoadShapeRender: file %p loaded a second time (shape data swapped twice)\n", file);
            }
        }
        s_loaded[s_loadedCount++ & 63] = file;
    }
    ShapeDoneSet done = {0, 0, 0};
    u8* pcShapeSec = base + GC_AT(u32, base, 0x10);
    u8* pcTexSec = base + GC_AT(u32, base, 0x14);
    const u16 pcShapeCount = GC_AT(u16, pcShapeSec, 4);
    u32* const pcShapeOffsets = (u32*)(base + GC_AT(u32, pcShapeSec, 8));
    const u16 pcTexCount = GC_AT(u16, pcTexSec, 4);
    u32* const pcTexOffsets = (u32*)(base + GC_AT(u32, pcTexSec, 8));
    anim = (GsShapeAnimHeader*)(base + GC_AT(u32, base, 0xC));
    GC_FIX32(anim->frameCount);
    GC_FIX32(anim->fps);
    GC_FIX16(anim->keyCount);
    GC_FIX32(anim->keyOffset);
#endif
    GsShapeAnimHeader* ah = anim;
    u32* keyOffsets = (u32*)(base + ah->keyOffset);
    keyCount = ah->keyCount;
    keys = (GsKeyObject*)GSmemAlloc(anim->keyCount * sizeof(GsKeyObject));
    u16 maxUV_U = 0, maxUV_V = 0, maxTw = 0, maxGr = 0;
    for (int i = 0; i < keyCount; i++) {
        GsKeyObject* key = &keys[i];
#ifdef __MWERKS__
        key->entry = (tagGsFilePrimObjectEntry*)(base + keyOffsets[i]);
        key->frames = (tagGsFilePrimKeyFrame**)(base + key->entry->frameOffset);
#else
        _shapeEntryToNative(&done, base, GC_AT(u32, &keyOffsets[i], 0));
        key->entry = (tagGsFilePrimObjectEntry*)(base + GC_AT(u32, &keyOffsets[i], 0));
        key->frames = (tagGsFilePrimKeyFrame**)GSmemAlloc(key->entry->count * sizeof(tagGsFilePrimKeyFrame*));
#endif
        entry = key->entry;
        for (s32 j = 0; j < entry->count; j++) {
#ifdef __MWERKS__
            tagGsFilePrimKeyFrame* kf = (tagGsFilePrimKeyFrame*)(base + (u32)key->frames[j]);
            key->frames[j] = kf;
            relocate(kf->cScale[0], base);
            relocate(kf->cScale[1], base);
            relocate(kf->cScale[2], base);
            relocate(kf->cTrans[0], base);
            relocate(kf->cTrans[1], base);
            relocate(kf->cTrans[2], base);
            relocate(kf->cPivot[0], base);
            relocate(kf->cPivot[1], base);
            relocate(kf->cPivot[2], base);
            relocate(kf->cRot[0], base);
            relocate(kf->cRot[1], base);
            relocate(kf->cRot[2], base);
            relocate(kf->cColor[0], base);
            relocate(kf->cColor[1], base);
            relocate(kf->cColor[2], base);
            relocate(kf->cColor[3], base);
            relocate(kf->cRadius[0], base);
            relocate(kf->cRadius[1], base);
            relocate(kf->unk14C[0], base);
            relocate(kf->unk14C[1], base);
            relocate(kf->cShowAngle[0], base);
            relocate(kf->cShowAngle[1], base);
            for (int p = 0; p < 4; p++) {
                relocate(kf->cTexScale[p][0], base);
                relocate(kf->cTexScale[p][1], base);
                relocate(kf->cTexOffset[p][0], base);
                relocate(kf->cTexOffset[p][1], base);
                relocate(kf->cTexColor[p][0], base);
                relocate(kf->cTexColor[p][1], base);
                relocate(kf->cTexColor[p][2], base);
                relocate(kf->cTexColor[p][3], base);
                relocate(kf->cTexColorLow[p][0], base);
                relocate(kf->cTexColorLow[p][1], base);
                relocate(kf->cTexColorLow[p][2], base);
                relocate(kf->cTexColorLow[p][3], base);
            }
            relocate(kf->deformU, base);
            relocate(kf->deformV, base);
            relocate(kf->twist, base);
            relocate(kf->grad0, base);
            relocate(kf->grad1, base);
#else
            tagGsFilePrimKeyFrame* kf = _shapeKeyFrameToNative(
                &done, base, GC_AT(u32, base + entry->frameOffset, j * 4), entry);
            key->frames[j] = kf;
#endif
            if (entry->uvDeform == 1 || entry->twist == 1 || entry->radius == 1 || entry->showAngle == 1) {
                u16 nu = kf->nDeformU;
                if (maxUV_U < nu) {
                    maxUV_U = nu;
                }
                u16 nv = kf->nDeformV;
                if (maxUV_V < nv) {
                    maxUV_V = nv;
                }
            }
            if (entry->twist != 0) {
                u16 nt = kf->nTwist;
                if (maxTw < nt) {
                    maxTw = nt;
                }
            }
            if (entry->colorKey != 0 && entry->colorMode == 1) {
                if (kf->gradKind == 0) {
                    u16 n0 = kf->nGrad0;
                    if (maxGr < n0) {
                        maxGr = n0;
                    }
                } else {
                    u16 n1 = kf->nGrad1;
                    if (maxGr < n1) {
                        maxGr = n1;
                    }
                }
            }
        }
    }
#ifdef __MWERKS__
    u8* shapeSec = base + *(u32*)(base + 0x10);
    u32* shapeOffsets = (u32*)(base + *(u32*)(shapeSec + 8));
    shapeCount = *(u16*)(shapeSec + 4);
#else
    u32* shapeOffsets = pcShapeOffsets;
    shapeCount = pcShapeCount;
#endif
    shapes = (GsShapeObject*)GSmemAlloc(shapeCount * sizeof(GsShapeObject));
    s32 i;
    bool needRefract;
    for (i = 0, needRefract = false; i < shapeCount; i++) {
#ifdef __MWERKS__
        u8* sd = base + shapeOffsets[i];
        shapes[i].data = (GsShapeData*)sd;
        *(u32*)(sd + 0x10) += (u32)base;
        *(u32*)(sd + 0x14) += (u32)base;
        *(u32*)(sd + 0x18) += (u32)base;
        if (*(u32*)(sd + 0x1C) != 0) {
            *(u32*)(sd + 0x1C) += (u32)base;
        }
        GsShapeData* d = (GsShapeData*)sd;
        for (s32 k = 0; k < d->texCount; k++) {
            if (*(u32*)(sd + 0x28 + k * 4) != 0) {
                *(u32*)(sd + 0x28 + k * 4) += (u32)base;
            }
        }
#else
        GsShapeData* d = _shapeDataToNative(&done, base, GC_AT(u32, &shapeOffsets[i], 0));
        shapes[i].data = d;
#endif
        if (d->enabled == 1 && d->mode == 8) {
            needRefract = true;
        }
        memset(shapes[i].drawBuf, 0, sizeof(shapes[i].drawBuf));
    }
#ifdef __MWERKS__
    u8* texSec = base + *(u32*)(base + 0x14);
    u32* texOffsets = (u32*)(base + *(u32*)(texSec + 8));
    texCount = *(u16*)(texSec + 4);
#else
    if (done.slot != 0) {
        GSmemFree(done.slot);
    }
    u32* texOffsets = pcTexOffsets;
    texCount = pcTexCount;
#endif
    if (texCount != 0) {
        texes = (GsShapeTexture*)GSmemAlloc((texCount * 8) & 0x7FFF8);
    } else {
        texes = 0;
    }
    for (s32 i = 0; i < texCount; i++) {
#ifdef __MWERKS__
        u8* ti = base + texOffsets[i];
        texes[i].info = ti;
        texes[i].tex = GStextureLoad(base + *(u32*)(ti + 0x14), ti);
#else
        u8* ti = base + GC_AT(u32, &texOffsets[i], 0);
        texes[i].info = ti;
        texes[i].tex = GStextureLoad(base + GC_AT(u32, ti, 0x14), ti);
#endif
        GStextureSetWrap(texes[i].tex, 1, 1);
    }
    for (s32 i = 0; i < shapeCount; i++) {
        s32 k = 0;
        u8 n = 0;
        GsShapeObject* s = &shapes[i];
        for (k = 0; k < s->data->texCount; k++) {
            n++;
            if (k < 2) {
                GsShapeTexInfo* ti = s->data->texInfo[k];
                if (*((u8*)texes[ti->index].info + 0xE) != 0) {
                    n += 2;
                } else {
                    n += 1;
                }
            }
        }
        if (n != 0) {
            n = n + 1;
        }
        s->numTev = n;
    }
    for (s32 i = 0; i < shapeCount; i++) {
        GsShapeData* d;
        GsShapeObject* s;
        s = &shapes[i];
        d = s->data;
        s32 attrs[4] = {13, 14, 15, 16};
        s->posArray = 0;
        s->colArray = 0;
        s->texArray[0] = 0;
        s->texArray[1] = 0;
        s->texArray[2] = 0;
        s->texArray[3] = 0;
        GSgfxVFInit((GSgfxVF*)s->vf, attrs[3], attrs[2], attrs[1], attrs[0]);
        GSgfxVFCreate((GSgfxVF*)s->vf);
        GSgfxVFSetElement((GSgfxVF*)s->vf, 9, 1, 4, 0);
        GSgfxVFSetElement((GSgfxVF*)s->vf, 0xB, 1, 5, 0);
        for (s32 k = 0; k < d->texCount; k++) {
            GSgfxVFSetElement((GSgfxVF*)s->vf, attrs[k], 1, 4, 0);
        }
        s->dl = 0;
        s->MakeDisplayListShape();
    }
    if (maxUV_U != 0) {
        maxU = maxUV_U;
        paramU = (f32*)GSmemAlloc(maxU * 4);
    }
    if (maxUV_V != 0) {
        maxV = maxUV_V;
        paramV = (f32*)GSmemAlloc(maxV * 4);
    }
    if (maxTw != 0) {
        maxTwist = maxTw;
        paramTwist = (f32*)GSmemAlloc(maxTwist * 4);
    }
    if (maxGr != 0) {
        maxGrad = maxGr;
        paramGrad = (tagGScol4ub*)GSmemAlloc(maxGrad * 4);
    }
    if (needRefract == 1) {
        refractTex = GStextureCreate(0, 0, 0x45, 0, 0);
    }
#ifndef __MWERKS__
    for (s32 i = 0; i < keyCount; i++) {
        if (keys[i].entry->shapeIndex >= shapeCount) {
            OSReport("LoadShapeRender %p: key %d/%d names shape %u of %u (entry at file +0x%x, frames %u, anim keys %u; header +0xC/+0x10/+0x14 = %x/%x/%x)\n",
                     file, i, keyCount, keys[i].entry->shapeIndex, shapeCount,
                     (u32)((u8*)keys[i].entry - base), keys[i].entry->count, anim->keyCount,
                     (u32)GC_AT(u32, base, 0xC), (u32)GC_AT(u32, base, 0x10), (u32)GC_AT(u32, base, 0x14));
        }
    }
#endif
    polygonCount = 0;
    for (s32 i = 0; i < shapeCount; i++) {
        u32 i_c = i;
        polygonCount += shapes[i_c].GetPolygonCount();
    }
    loaded = 1;
    usedMemory = 0;
    usedMemory += 0x964;
    usedMemory += keyCount * sizeof(GsKeyObject);
    usedMemory += shapeCount * 0x8A4;
    usedMemory += texCount * 8;
    if (refractTex != 0) {
        usedMemory += 0x12C080;
    }
    instancedMemory = 0;
    freeCount[0] = 0;
    freeCount[1] = 0;
    return true;
}

static inline u32 calcFrame(const GsShapeAnimHeader* hdr, f32 time) {
    if (hdr == 0) {
        return 0;
    }
    u32 f = (u32)(time * (f32)hdr->fps);
    if (hdr->loopMode == 1) {
        f = f % (hdr->frameCount - 1);
    } else if (hdr->loopMode == 2) {
        if (f > hdr->frameCount - 1) {
            f = hdr->frameCount - 1;
        }
    }
    return f;
}

void GsShapeRender::Update(f32 time, s16 id) {
    GsKeyObject* key;
    tagGsFilePrimObjectEntry* entry;
    GsShapeObject* shape;
    GsShapeData* data;
    if (loaded == 0) {
        return;
    }
    if (anim == 0) {
        return;
    }
    frame = calcFrame(anim, time);
    if (frame >= anim->frameCount) {
        return;
    }
    if (id >= 0 && id < 0x100) {
        if (tokens[bufIndex][id] != 0) {
            GSgfxTokenWaitForClear(tokens[bufIndex][id]);
            tokens[bufIndex][id] = 0;
        }
    }
    for (s32 i = 0; i < keyCount; i++) {
        f32 ox;
        GsShapeTexInfo* info;
        GSmtx* m;
        key = &keys[i];
        entry = key->entry;
        shape = &shapes[entry->shapeIndex];
        data = shape->data;
        tagGsFilePrimKeyFrame* a;
        tagGsFilePrimKeyFrame* b;
        f32 t;
        if (data->enabled == 0 || !key->GetFrameInterval(frame, a, b, t)) {
            continue;
        }
        key->enabled = (a->visible != 0);
        if (a->visible == 0) {
            continue;
        }
        if (id >= 0 && id < 0x100 && shape->drawBuf[id] != 0) {
            u32 off = 0;
            u32 vc = data->vertCount;
            if (bufIndex != 0) {
                off = vc * (data->texCount * 8 + 0x10);
            }
            u8* base = (u8*)shape->drawBuf[id] + off;
            shape->posArray = base;
            u8* col = base + vc * 0xC;
            shape->colArray = col;
            for (s32 k = 0; k < 4; k++) {
                if (k < data->texCount) {
                    shape->texArray[k] = col + vc * (k * 8 + 4);
                }
            }
        } else {
            shape->posArray = 0;
            shape->colArray = 0;
            shape->texArray[0] = 0;
            shape->texArray[1] = 0;
            shape->texArray[2] = 0;
            shape->texArray[3] = 0;
        }
        s32 deformKey;
        if (entry->uvDeform == 1 && entry->uvDeformKey == 1) {
            deformKey = 1;
        } else {
            deformKey = 0;
        }
        s32 twistKey;
        if (entry->twist == 1 && entry->twistKey == 1) {
            twistKey = 1;
        } else {
            twistKey = 0;
        }
        if (deformKey == 1 || twistKey == 1 || entry->radius == 1 || entry->showAngle == 1) {
            if (deformKey == 1) {
                key->GetDeformParameterU(paramU, a, b, t);
                key->GetDeformParameterV(paramV, a, b, t);
            } else {
                key->GetLinearParameterU(paramU, a);
                key->GetLinearParameterV(paramV, b);
            }
            f32 r0 = 0.0f;
            f32 r1 = 0.0f;
            f32 s0 = 0.0f;
            f32 s1 = 0.0f;
            if (entry->radius == 1) {
                key->GetShapeRadius(&r0, &r1, a, b, t);
            }
            if (entry->showAngle == 1) {
                key->GetShapeShowAngle(&s0, &s1, a, b, t);
            }
            if (twistKey == 1) {
                key->GetTwistParameter(paramTwist, a, b, t);
            }
            shape->DeformVertexCoord(deformKey != 0, paramU, paramV, entry->radius != 0, r0, r1,
                                     entry->showAngle != 0, s0, s1, (bool)twistKey, paramTwist);
        }
        GsShapeAnimHeader* h = anim;
        key->GetShapeMatrix(&key->mtxA, &key->mtxB, (tagGsFilePrimObjectEntry*)data, h->orderCount, h->order, a, b, t);
        s32 deformTex;
        if (entry->uvDeform == 1 && entry->uvDeformKey == 0) {
            deformTex = 1;
        } else {
            deformTex = 0;
        }
        s32 twistTex;
        if (entry->twist == 1 && entry->twistKey == 0) {
            twistTex = 1;
        } else {
            twistTex = 0;
        }
        bool twistOn = twistTex != 0;
        bool deformOn = deformTex != 0;
        for (u8 k = 0; k < data->texCount; k++) {
            if ((deformTex == 1 || twistTex == 1) && (refractTex == 0 || k != 0)) {
                if (deformTex != 0) {
                    key->GetDeformParameterU(paramU, a, b, t);
                    key->GetDeformParameterV(paramV, a, b, t);
                }
                if (twistTex != 0) {
                    key->GetTwistParameter(paramTwist, a, b, t);
                }
                shape->DeformTextureCoord(k, deformOn, paramU, paramV, twistOn, paramTwist);
            }
            if (data->mode == 0xA && data->texCount != 0) {
                GsVec2 off = key->GetTextureOffset(a, b, t, 0);
                GsVec2 scl = key->GetTextureScale(a, b, t, 0);
                off.v[0] = off.v[0] * scl.v[0];
                off.v[1] = off.v[1] * scl.v[1];
                shape->WaveTextureCoord(k, off.v[0], off.v[1], &key->mtxA, false);
            }
            info = shape->data->texInfo[k];
            if (data->mode == 8 && k == 0) {
                memcpy(&key->texMtx[k], &mtxIdent, 0x30);
            } else if (entry->texAnim[k] == 1) {
                f32 oy;
                f32 sx;
                f32 sy;
                if (entry->texAnim[k] == 1) {
                    GsVec2 off = key->GetTextureOffset(a, b, t, k);
                    oy = off.v[1];
                    ox = off.v[0];
                    GsVec2 scl = key->GetTextureScale(a, b, t, k);
                    sy = scl.v[1];
                    sx = scl.v[0];
                }
                if (a->texAnim[k] != 0) {
                    if (info->kind == 0) {
                        m = &key->texMtx[k];
                        m->m[0][0] = 0.0f;
                        m->m[0][1] = 1.0f;
                        m->m[0][2] = 0.0f;
                        m->m[0][3] = 0.0f;
                        m->m[1][0] = 1.0f;
                        m->m[1][1] = 0.0f;
                        m->m[1][2] = 0.0f;
                        m->m[1][3] = 0.0f;
                        m->m[2][0] = 0.0f;
                        m->m[2][1] = 0.0f;
                        m->m[2][2] = 1.0f;
                        m->m[2][3] = 0.0f;
                        PSMTXTransApply(m->m, m->m, -ox, -oy, 0.0f);
                        PSMTXScaleApply(m->m, m->m, sx, sy, 0.0f);
                    } else {
                        m = &key->texMtx[k];
                        m->m[0][0] = 0.0f;
                        m->m[0][1] = 1.0f;
                        m->m[0][2] = 0.0f;
                        m->m[0][3] = 0.0f;
                        m->m[1][0] = 1.0f;
                        m->m[1][1] = 0.0f;
                        m->m[1][2] = 0.0f;
                        m->m[1][3] = 0.0f;
                        m->m[2][0] = 0.0f;
                        m->m[2][1] = 0.0f;
                        m->m[2][2] = 1.0f;
                        m->m[2][3] = 0.0f;
                        PSMTXScaleApply(m->m, m->m, sx, sy, 0.0f);
                        PSMTXTransApply(m->m, m->m, -ox, -oy, 0.0f);
                    }
                } else if (info->kind == 0) {
                    m = &key->texMtx[k];
                    PSMTXTrans(m->m, -ox, -oy, 0.0f);
                    PSMTXScaleApply(m->m, m->m, sx, sy, 0.0f);
                } else {
                    m = &key->texMtx[k];
                    PSMTXScale(m->m, sx, sy, 0.0f);
                    PSMTXTransApply(m->m, m->m, -ox, -oy, 0.0f);
                }
            } else {
                GSmtx* m = &key->texMtx[k];
                PSMTXScale(m->m, info->u1 - info->u0, info->v1 - info->v0, 0.0f);
                PSMTXTransApply(m->m, m->m, info->u0, info->v0, 0.0f);
            }
        }
        if (data->vertexColorKind == 0) {
            if (entry->colorKey == 1) {
                if (entry->colorMode == 0) {
                    tagGScol4ub col = key->GetShapeColor(a, b, t);
                    shape->SetVertexColorSpecify(col, true);
                } else {
                    f32 alpha = key->GetShapeColorAlpha(a, b, t);
                    u8 kind;
                    key->GetGradationParameter(&kind, paramGrad, a, b, t);
                    shape->SetVertexColorGradation(kind, paramGrad, data->mode, alpha, true);
                }
            } else {
                f32 alpha = key->GetShapeColorAlpha(a, b, t);
                shape->SetVertexColorAlpha(entry->colorMode, data->mode, alpha, true);
            }
        }
        shape->tevColor[0] = key->GetTextureColor(a, b, t, 0);
        shape->tevColor[1] = key->GetTextureColorLow(a, b, t, 0);
        shape->tevColor[1].a = 0xFF;
        if (data->texCount > 1) {
            shape->tevColor[2] = key->GetTextureColor(a, b, t, 1);
            shape->tevColor[3] = key->GetTextureColorLow(a, b, t, 1);
        }
    }
}

void GsShapeRender::Render(s16 id, GSgfxLayerID layerID) {
    if (loaded == 0) {
        return;
    }
    if (frame >= anim->frameCount) {
        return;
    }
    GSmtx* viewMtx;
    GSmtx* camMtx;
    GSgfxLayer* layer = GSgfxLayerFindByID(layerID);
    f32 fov, aspect;
    f32 nearZ = 0.1f;
    f32 farZ;
    void* camera = GScameraGetActiveCamera();
    if (camera != 0) {
        GScameraGetPerspective(camera, &fov, &aspect, &nearZ, &farZ);
    }
    camMtx = &(*(GSgfxMatrixStack**)&layer->matrixStack)->top->m;
    if (camMtx == 0) {
        return;
    }
    s32 i;
    for (i = 0; i < keyCount; i++) {
        GsKeyObject* key = &keys[i];
        tagGsFilePrimObjectEntry* entry = key->entry;
        GsShapeObject* shape = &shapes[entry->shapeIndex];
        GsShapeData* data = shape->data;
        if (data->enabled == 0 || key->enabled == 0) {
            continue;
        }
        bool bb = isBillboard(data) != 0;
        if (bb == 1) {
            shape->MakeMatrixBillboard(camMtx, nearZ);
        }
        if (bb == 1) {
            viewMtx = &shape->mtx;
        } else {
            viewMtx = camMtx;
        }
        if (data->vertexColorKind != 0 && shape->data->vertexColors != 0) {
            tagGsFilePrimKeyFrame* a;
            tagGsFilePrimKeyFrame* b;
            f32 t;
            if (!key->GetFrameInterval(frame, a, b, t)) {
                continue;
            }
            if (entry->colorKey == 1) {
                if (entry->colorMode == 0) {
                    tagGScol4ub col = key->GetShapeColor(a, b, t);
                    shape->SetVertexColorSpecify(col, false);
                } else {
                    f32 alpha = key->GetShapeColorAlpha(a, b, t);
                    u8 kind;
                    key->GetGradationParameter(&kind, paramGrad, a, b, t);
                    shape->SetVertexColorGradation(kind, paramGrad, data->mode, alpha, false);
                }
            } else {
                f32 alpha = key->GetShapeColorAlpha(a, b, t);
                shape->SetVertexColorAlpha(entry->colorMode, data->mode, alpha, false);
            }
            shape->ShadeVertexColor(&key->mtxB, &key->mtxA, viewMtx, nearZ, entry->radius != 0);
        }
        if (data->mode == 8 && data->texCount != 0) {
            tagGsFilePrimKeyFrame* a;
            tagGsFilePrimKeyFrame* b;
            f32 t;
            if (!key->GetFrameInterval(frame, a, b, t)) {
                continue;
            }
            GsVec2 off = key->GetTextureOffset(a, b, t, 0);
            GsVec2 scl = key->GetTextureScale(a, b, t, 0);
            off.v[0] = off.v[0] * scl.v[0];
            off.v[1] = off.v[1] * scl.v[1];
            shape->RefractTextureCoord(off.v[0], off.v[1], &key->mtxB, &key->mtxA, viewMtx, nearZ);
        }
    }
GSgfxTgenSrc srcs[8] = {(GSgfxTgenSrc)4, (GSgfxTgenSrc)5, (GSgfxTgenSrc)6, (GSgfxTgenSrc)7,
                            (GSgfxTgenSrc)8, (GSgfxTgenSrc)9, (GSgfxTgenSrc)10, (GSgfxTgenSrc)11};
    for (i = 0; i < keyCount; i++) {
        GsKeyObject* key = &keys[i];
        GsShapeObject* shape = &shapes[key->entry->shapeIndex];
        GsShapeData* data = shape->data;
        if (data->enabled == 0 || key->enabled == 0) {
            continue;
        }
        u8 texN = data->texCount;
        if (texN != 0) {
            layer->setRenderStateAndSelect((GSgfxVF*)shape->vf);
            layer->tevStageCount(shape->numTev);
            layer->tevColor(0, shape->tevColor[0]);
            layer->tevColor(1, shape->tevColor[1]);
            layer->tevColor(2, shape->tevColor[2]);
            layer->tevColor(3, shape->tevColor[3]);
        } else {
            layer->setRenderStateAndSelect((GSgfxVF*)shape->vf);
        }
        shape->SetStateMode(layer);
        if (data->mode == 8 && refractTex != 0) {
            layer->textureCopy((*(GSgfxLayerPass*)&layer->curPass), refractTex, false, 0, false, false, false);
        }
        shape->SetStateTexture(layer, texes, data->mode == 8 ? refractTex : 0);
        for (u8 k = 0; k < texN; k++) {
            layer->tgenFunc(k, (GSgfxTgenFunc)1, srcs[k], &key->texMtx[k], false, 0);
        }
        bool bb = isBillboard(data) != 0;
        if (bb == 1) {
            (*(GSgfxMatrixStack**)&layer->matrixStack)->push(&shape->mtx);
        }
        (*(GSgfxMatrixStack**)&layer->matrixStack)->pushMult(&key->mtxB);
        (*(GSgfxMatrixStack**)&layer->matrixStack)->pushMult(&key->mtxA);
        shape->CallDisplayListShape(layer, id, bufIndex);
        (*(GSgfxMatrixStack**)&layer->matrixStack)->pop();
        (*(GSgfxMatrixStack**)&layer->matrixStack)->pop();
        if (bb == 1) {
            (*(GSgfxMatrixStack**)&layer->matrixStack)->pop();
        }
        if (texN != 0) {
            layer->tevStageCount(1);
        }
    }
    if (id >= 0 && id < 0x100) {
        tokens[bufIndex][id] = GSgfxTokenMark();
    }
}

static f32 placeholderU32(u32 v) { return (f32)v; }

s16 GsShapeRender::CreateShapeRenderDrawBuffer() {
    FlushFreeList();
    u16 n;
    for (n = 0; n < 0x100; n++) {
        if (used[searchIndex] == 0) {
            used[searchIndex] = 1;
            break;
        }
        searchIndex++;
        if (searchIndex >= 0x100) {
            searchIndex = 0;
        }
    }
    if (n == 0x100) {
        return -1;
    }
    if (usedCount >= 0x100) {
        return -1;
    }
    usedCount++;
    u16 i = 0;
    while (i < shapeCount) {
        if (shapes[i].CreateShapeDrawBuffer(searchIndex) == 0) {
            for (s32 j = 0; j < (s32)i; j++) {
                if (shapes[j].FreeShapeDrawBuffer(searchIndex) == 1) {
                    GsShapeData* d = shapes[0].data;
                    s32 size = d->vertCount * (d->texCount * 8 + 0x10) * 2;
                    instancedMemory -= size;
                    g_instancedMemorySizeAll -= size;
                }
            }
            return -1;
        }
        i++;
        GsShapeData* d = shapes[0].data;
        s32 size = d->vertCount * (d->texCount * 8 + 0x10) * 2;
        instancedMemory += size;
        g_instancedMemorySizeAll += size;
    }
    return searchIndex;
}

void GsShapeRender::FreeShapeRenderDrawBuffer(s16 id) {
    if (id < 0 || id >= 0x100) {
        return;
    }
    u8 other = (bufIndex == 0);
#ifdef __MWERKS__
    s16* b = (s16*)this + other;
#define SR_FREECOUNT b[0x560 / 2]
#else
    s16* b = &freeCount[other];
#define SR_FREECOUNT b[0]
#endif
    if (SR_FREECOUNT >= 0x100) {
        bufIndex = other;
        FlushFreeList();
        bufIndex = (bufIndex == 0);
    }
    freeList[other][SR_FREECOUNT] = id;
    SR_FREECOUNT++;
#undef SR_FREECOUNT
}

s32 GsShapeRender::GetUsedMemorySizeAll() {
    return usedMemory;
}

s32 GsShapeRender::GetInstancedMemorySizeAll() {
    return instancedMemory;
}

GSgfxLayerID GsShapeRender::GetLayerId() const {
    return layerId;
}

void GsShapeRender::SwapBuffers() {
    bufIndex = (bufIndex == 0);
    ExecuteFreeInstance();
}

void GsShapeRender::ExecuteFreeInstance() {
    if (releasedBuf == bufIndex) {
        bufIndex = (bufIndex == 0);
        FlushFreeList();
        bufIndex = (bufIndex == 0);
    }
    FlushFreeList();
    releasedBuf = bufIndex;
}
