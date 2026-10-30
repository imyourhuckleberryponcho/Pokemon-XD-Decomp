#include <dolphin/types.h>

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
    u8 unk10[0xC];
    void* vertexColors;
    u8 unk20[6];
    u16 texCount;
    GsShapeTexInfo* texInfo[4];
    u8 unk38[0xCD - 0x38];
    u8 billboard;
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
    int unk0;
    GSgfxMatrixEntry* top;
};

#define GFX_DIRTY(word, bits, group)  \
    dirty0Words[word] |= (bits);      \
    dirty0Groups |= (group);          \
    dirty1Words[word] |= (bits);      \
    dirty1Groups |= (group);

class GSgfxLayer {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void textureCopy(GSgfxLayerPass pass, GStexture* tex, bool a, u8* b, bool c, bool d, bool e);
    void tgenFunc(u8 unit, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* m, bool normalize, GSmtx* post);

    inline void tevStageCount(u8 n) {
        numTevStages = n;
        GFX_DIRTY(8, 1, 8)
    }
    inline void tevColor(u8 i, tagGScol4ub c) {
        *(u32*)&tevColors[i] = *(u32*)&c;
        GFX_DIRTY(19, 1 << i, 0x10)
    }

    u8 unk0[0xEAC];
    u8 numTevStages;
    u8 unkEAD[0x14F4 - 0xEAD];
    tagGScol4ub tevColors[4];
    u8 unk1504[0x16A8 - 0x1504];
    u32 dirty0Groups;
    u32 dirty0Words[36];
    u8 unk173C[0x1760 - 0x173C];
    u32 dirty1Groups;
    u32 dirty1Words[36];
    u8 unk17F4[0x1994 - 0x17F4];
    GSgfxLayerPass pass;
    u8 unk1998[8];
    GSgfxMatrixStack* matStack;
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
    u32 dl;
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

s32 g_instancedMemorySizeAll;

template <class T>
static inline void relocate(T*& p, u8* base) {
    p = (T*)((u8*)p + (u32)base);
}

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
    s32 id = 0;
    do {
        if (used[id] == 1) {
            for (i = 0; id < shapeCount; i++) {
                if (shapes[i].FreeShapeDrawBuffer(i) == 1) {
                    GsShapeData* d = shapes[0].data;
                    s32 size = d->vertCount * (d->texCount * 8 + 0x10) * 2;
                    instancedMemory -= size;
                    g_instancedMemorySizeAll -= size;
                }
                used[id] = 0;
            }
        }
        id++;
        usedCount = 0;
    } while (id < 0x100);
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
    anim = (GsShapeAnimHeader*)(base + *(u32*)(base + 0xC));
    GsShapeAnimHeader* ah = anim;
    u32* keyOffsets = (u32*)(base + ah->keyOffset);
    keyCount = ah->keyCount;
    keys = (GsKeyObject*)GSmemAlloc(anim->keyCount * 0x12C);
    u16 maxUV_U = 0, maxUV_V = 0, maxTw = 0, maxGr = 0;
    for (int i = 0; i < keyCount; i++) {
        GsKeyObject* key = &keys[i];
        key->entry = (tagGsFilePrimObjectEntry*)(base + keyOffsets[i]);
        key->frames = (tagGsFilePrimKeyFrame**)(base + key->entry->frameOffset);
        entry = key->entry;
        for (s32 j = 0; j < entry->count; j++) {
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
    u8* shapeSec = base + *(u32*)(base + 0x10);
    u32* shapeOffsets = (u32*)(base + *(u32*)(shapeSec + 8));
    shapeCount = *(u32*)(shapeSec + 4);
    shapes = (GsShapeObject*)GSmemAlloc(shapeCount * 0x8A4);
    s32 i;
    volatile bool needRefract;
    for (i = 0, needRefract = false; i < shapeCount; i++) {
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
        if (d->enabled == 1 && d->mode == 8) {
            needRefract = true;
        }
        memset(shapes[i].drawBuf, 0, 0x400);
    }
    u8* texSec = base + *(u32*)(base + 0x14);
    u32* texOffsets = (u32*)(base + *(u32*)(texSec + 8));
    texCount = *(u32*)(texSec + 4);
    if (texCount != 0) {
        texes = (GsShapeTexture*)GSmemAlloc((texCount * 8) & 0x7FFF8);
    } else {
        texes = 0;
    }
    for (s32 i = 0; i < texCount; i++) {
        u8* ti = base + texOffsets[i];
        texes[i].info = ti;
        texes[i].tex = GStextureLoad(base + *(u32*)(ti + 0x14), ti);
        GStextureSetWrap(texes[i].tex, 1, 1);
    }
    for (s32 i = 0; i < shapeCount; i++) {
        s32 k = 0;
        s32 n = 0;
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
    polygonCount = 0;
    for (s32 i = 0; i < shapeCount; i++) {
        u32 i_c = i;
        polygonCount += shapes[i_c].GetPolygonCount();
    }
    loaded = 1;
    usedMemory = 0;
    usedMemory += 0x964;
    usedMemory += keyCount * 0x12C;
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
        GsKeyObject* key = &keys[i];
        tagGsFilePrimObjectEntry* entry = key->entry;
        GsShapeObject* shape = &shapes[entry->shapeIndex];
        GsShapeData* data = shape->data;
        tagGsFilePrimKeyFrame* a;
        tagGsFilePrimKeyFrame* b;
        f32 t;
        if (data->enabled == 0 || !key->GetFrameInterval((u16)frame, a, b, t)) {
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
        bool deformKey = (entry->uvDeform == 1 && entry->uvDeformKey == 1);
        u8 twistKey = (entry->twist == 1 && entry->twistKey == 1);
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
        bool deformTex = (entry->uvDeform == 1 && entry->uvDeformKey == 0);
        bool twistTex = (entry->twist == 1 && entry->twistKey == 0);
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
            info = data->texInfo[k];
            if (data->mode == 8 && k == 0) {
                memcpy(&key->texMtx[k], &mtxIdent, 0x30);
            } else if (entry->texAnim[k] == 1) {
                volatile GsVec2 off = key->GetTextureOffset(a, b, t, k);
                f32 oy = off.v[1];
                ox = off.v[0];
                volatile GsVec2 scl = key->GetTextureScale(a, b, t, k);
                f32 sx;
                f32 sy;
                sy = scl.v[1];
                sx = scl.v[0];
                m = &key->texMtx[k];
                if (a->texAnim[k] != 0) {
                    if (info->kind == 0) {
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
                    PSMTXTrans(m->m, -ox, -oy, 0.0f);
                    PSMTXScaleApply(m->m, m->m, sx, sy, 0.0f);
                } else {
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
    camMtx = &layer->matStack->top->m;
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
            layer->textureCopy(layer->pass, refractTex, false, 0, false, false, false);
        }
        GStexture* over;
        if (data->mode == 8) {
            over = refractTex;
        } else {
            over = 0;
        }
        shape->SetStateTexture(layer, texes, over);
        for (u8 k = 0; k < texN; k++) {
            layer->tgenFunc(k, (GSgfxTgenFunc)1, srcs[k], &key->texMtx[k], false, 0);
        }
        bool bb = isBillboard(data) != 0;
        if (bb == 1) {
            layer->matStack->push(&shape->mtx);
        }
        layer->matStack->pushMult(&key->mtxB);
        layer->matStack->pushMult(&key->mtxA);
        shape->CallDisplayListShape(layer, id, bufIndex);
        layer->matStack->pop();
        layer->matStack->pop();
        if (bb == 1) {
            layer->matStack->pop();
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
    s16* b = (s16*)this + other;
    if (b[0x560 / 2] >= 0x100) {
        bufIndex = other;
        FlushFreeList();
        bufIndex = (bufIndex == 0);
    }
    freeList[other][b[0x560 / 2]] = id;
    b[0x560 / 2]++;
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
