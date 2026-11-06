#include <game/gcdata.h>
#include <dolphin/types.h>
#include <game/gcptr.h>
#include <dolphin/gx/GXVert.h>
#ifdef __MWERKS__
#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)
#else
#define GXFifoNV GXWGFifo
#endif

#pragma peephole off
#pragma pool_strings off

extern "C" {
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
}

struct GSpart;
struct GSmodel;
struct GSlight;
struct GSmaterial;
struct GStexture;
struct GSgfxVF;
struct GSgfxLight;
struct GSmtx;
enum GSpartMixType { GSpartMixType0 };
enum GSgfxLayerID {};
enum GSgfxLayerOffset {};
enum GSgfxLayerType {};
enum GSgfxCunitAlpha {};
enum GSgfxCunitSrc {};
enum GSgfxLightType {};
enum GSgfxDiffuseFunc {};
enum GSgfxTgenFunc {};
enum GSgfxTgenSrc {};
enum MENU_POKEMON_CB_TYPE_UNUSED {};

template <typename T>
struct PocketVec {
    T x, y;
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};
struct BlendState {
    u8 pad[0xbc];
};
struct GSmtx44 {
    f32 m[4][4];
};

#define U8_AT(o) (*(u8*)((u8*)this + (o)))
#define U32_AT(o) (*(u32*)((u8*)this + (o)))

#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void cunitChannelGen(u8 chan, GSgfxCunitAlpha alpha, GSgfxCunitSrc src0, GSgfxCunitSrc src1, u32 lights,
                         GSgfxLight** light, GSgfxLightType lightType, GSgfxDiffuseFunc diffuse);
    void tgenFunc(u8 index, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* mtx, bool normalize, GSmtx* post);
    void SetTextureCopy(GStexture* tex, bool clear, u8* clearColor);
    void SetClearFlags(bool color, bool alpha, bool depth);
    void beginSurface(u16 count);
    void endSurface();

    inline void mark(u32 sum, u32 off, u32 bit)
    {
#ifdef __MWERKS__
        U32_AT(off) |= bit;
        U32_AT(0x16a8) |= sum;
        U32_AT(off + 0xb8) |= bit;
        U32_AT(0x1760) |= sum;
#else
        GSL_IN(this, u32, dirty[0], 0x16a8, off) |= bit;
        dirty[0].groups |= sum;
        GSL_IN(this, u32, dirty[1], 0x1760, off + 0xb8) |= bit;
        dirty[1].groups |= sum;
#endif
    }

};

class GSgfxLayerConfig {
public:
    static void Remove(GSgfxLayerID id);
    static void Move(GSgfxLayerID id, GSgfxLayerID relative, GSgfxLayerOffset offset);
    static GSgfxLayerID Add(char* name, u32 width, u32 height, u32 count, GSgfxLayerType type, bool clearColor,
                            bool clearAlpha, bool clearDepth, GSgfxLayerID relative, GSgfxLayerOffset offset);
};

typedef struct _GSmodel _GSmodel;
struct GSmtx44x { f32 m[4][4]; };
struct _GSparticleGen;
enum GSattachMode {};
struct GSlightT;
extern "C" {
GSgfxLayer* GSgfxLayerFindByID(GCsptr);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void GSmtx44Ortho(f32*, f32, f32, f32, f32, f32, f32);
void* HSD_ArchiveGetPublicAddress(void*, const char*);
void spriteSetOffset(s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
GStexture* GStextureCreate(u16, u16, s32, s32, u8);
void GStextureFree(GStexture*);
void* GSresGetResourceAllGroup(u32);
void GSresFreeResource(u32, u32);
void GSresRegisterResource(void*, u32, u32, bool (*)(void*, u32, u32));
u32 floorReadMakeModelResID(u32);
u32 floorReadMakeLightResID(u32);
void floorSetLightInfo(u32, u32);
void GSlogWrite(const char*, ...);
void* GSmodelLoad(void*, void*);
void GSmodelSetRenderLayer(void*, s32, s32*);
void GSmodelSetVisibility(void*, bool);
u32 GSmodelCanAnimate(void*);
void GSmodelSetAnimIndex(void*, u32);
void GSmodelSetAnimRate(void*, f32);
void GSmodelStartAnimation(void*);
u32 GSmodelCanTexAnimate(void*);
void GSmodelSetTexAnimIndex(void*, u32);
void GSmodelSetTexAnimRate(void*, f32);
void GSmodelStartTexAnimation(void*);
void GSmodelFree(void*);
void* GSlightLoad(void*);
void GSlightFree(void*);
void GSlightSetType(void*, s32);
void GSlightSetActive(void*, u8);
u32 GSlightCanAnimate(void*);
void GSlightSetAnimIndex(void*, u32);
void GSlightSetAnimRate(void*, f32);
void GSlightStartAnimation(void*);
u32 GSmodelDetachFromGSpart(void*, u8);
void* GSmodelGetPart(void*, s32);
void GSmodelAttachToGSpart(void*, void*, s32, u8, u8);
void GSpartFree(void*);
void* GSparticleCreateGenerator(void*, s32, s32);
void GSparticleAttachGeneratorToGSpart(void*, void*, s32, bool, bool, bool);
void GSparticleDetachGeneratorFromGSpart(void*, bool);
f32 GSmodelGetAnimFrameCount(void*, u32);
f32 GSmodelGetAnimFrame(void*);
void GSmodelStopAnimation(void*);
u8 GSmodelIsAnimating(void*);
void GSmodelSetAnimFrame(void*, f32);
void GSmodelSetAnimType(void*, s32);
}
extern "C" GSmtx44 mtxIdent;

static inline void fifoColor(u8 r, u8 g, u8 b, s32 a)
{
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;
}

class WorldMapModel {
public:
    void releaseOffscreenData();
    void renderOffscreenData(f32 alpha);
    void initializeOffscreenData();
    void* SetModel(u32 groupID, u32 modelID, bool);
    void UnloadModel(u32 groupID, u32 modelID);
    void ObjectVisibility(u32 id, bool);
    void Visibility(u32 id, bool);
    bool ModelDetach(u32 id);
    bool ModelAttach(u32 a, u32 b, s32 part, GSattachMode mode);
    _GSparticleGen* SetModelPartPaticle(u32 a, u32 b, s32 part, GSattachMode mode, bool, bool, bool);
    void DetachModelPartPaticle(_GSparticleGen* gen, bool);
    void* makeArchiveHeader(u32 id);
    f32 GetAnimeFrameCount(u32 id, u32 motion);
    f32 GetAnimeFrame(u32 id);
    void StopMotion(u32 id);
    bool CheckMotion(u32 id);
    void SetMotion(u32 id, s16 motion, f32 frame, bool loop);
    void SetLayerID(u32 id, s32 count, GSgfxLayerID* layers);
    void* GetModelPtr(u32 id);

    GStexture* mOffscreenData;
};

struct ArchiveHeader {
    gc_ptr32(gc_ptr32(void)) models;
    gc_ptr32(void) pad;
    gc_ptr32(gc_ptr32(void)) lights;
};

static bool _unloadModel(void*, u32, u32);
static bool _unloadLight(void*, u32, u32);

void WorldMapModel::releaseOffscreenData()
{
    GSgfxLayer* layer = GSgfxLayerFindByID(2);
    layer->SetClearFlags(false, false, false);
    layer->SetTextureCopy(0, false, 0);
    GSgfxLayerConfig::Move((GSgfxLayerID)2, (GSgfxLayerID)4, (GSgfxLayerOffset)1);
    if (mOffscreenData != 0) {
        GStextureFree(mOffscreenData);
        mOffscreenData = 0;
    }
}

void WorldMapModel::renderOffscreenData(f32 alphaF)
{
#define LU8(o) (*(u8*)((u8*)layer + (o)))
#define LU32(o) (*(u32*)((u8*)layer + (o)))
    u8 alpha = 255.0f * alphaF;
    if (mOffscreenData != 0) {
        GSgfxLayer* layer = GSgfxLayerFindByID(4);
        if (layer != 0) {
            GSgfxVF* vf = GSgfxVFBuildTemp(0, 2, 0, 0, 1, 5, 1, 1, 0);
            spriteSetOffset(4, 0, 0);
            spriteClearScissor(4);
            spriteSetEnv(4);
            f32 mtx[16];
            GSmtx44Ortho(mtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
            (*(s32*)&layer->hw.projType) = 1;
            ((f32*)layer->hw.proj)[0] = mtx[0];
            ((f32*)layer->hw.proj)[1] = mtx[3];
            ((f32*)layer->hw.proj)[2] = mtx[5];
            ((f32*)layer->hw.proj)[3] = mtx[7];
            ((f32*)layer->hw.proj)[4] = mtx[10];
            ((f32*)layer->hw.proj)[5] = mtx[11];
            GSlayerCam* cam = (*(GSlayerCam**)&layer->matrixStack);
            memcpy(cam->data + 1, &mtxIdent, 0x30);
            cam->data[0] |= 1;
            (*(f32*)&layer->hw.fogNear) = 0.0f;
            (*(f32*)&layer->hw.fogFar) = 30000.0f;
            if ((*(u8*)&layer->hw.fogEnable)) {
                if ((*(u8*)&layer->hw.fogRangeEnable)) {
                    (*(u32*)&layer->dirty[0].pe) |= 0x100;
                    (*(u32*)&layer->dirty[1].pe) |= 0x100;
                }
                (*(u32*)&layer->dirty[0].pe) |= 0x40;
                (*(u32*)&layer->dirty[0].groups) |= 0x40;
                (*(u32*)&layer->dirty[1].pe) |= 0x40;
                (*(u32*)&layer->dirty[1].groups) |= 0x40;
            }
            layer->mark(1, 0x16ac, 0x20);
            (*(u8*)&layer->hw.colorUpdate) = 1;
            (*(u8*)&layer->hw.alphaUpdate) = 0;
            (*(u8*)&layer->hw.zUpdate) = 0;
            layer->mark(0x40, 0x170c, 4);
            (*(u8*)&layer->hw.zEnable) = 0;
            (*(s32*)&layer->hw.zFunc) = 7;
            layer->mark(0x40, 0x170c, 8);
            (*(s32*)&layer->hw.cullMode) = 2;
            layer->mark(2, 0x16b8, 2);
            (*(u32*)&layer->unk1998) = 0x80;
            (*(GSgfxVF**)&layer->curVF) = vf;
            LU8(0xc70) = 1;
            layer->mark(1, 0x16ac, 1);
            layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
            LU8(0xdb8) = 1;
            layer->mark(4, 0x16bc, 1);
            layer->cunitChannelGen(0, (GSgfxCunitAlpha)2, (GSgfxCunitSrc)1, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2,
                                   (GSgfxDiffuseFunc)0);
            LU8(0xeac) = 1;
            layer->mark(8, 0x16cc, 1);
            LU32(0xeb0) = 0;
            LU32(0xeb4) = 0;
            LU32(0xeb8) = 4;
            layer->mark(8, 0x16d0, 1);
            LU32(0x1170) = 0;
            LU32(0x1174) = 0;
            LU32(0x1178) = 0;
            LU8(0x117c) = 1;
            LU32(0x1180) = 0;
            layer->mark(8, 0x16dc, 1);
            LU32(0xf70) = 0xF;
            LU32(0xf74) = 0xF;
            LU32(0xf78) = 0xF;
            LU32(0xf7c) = 8;
            layer->mark(8, 0x16d4, 1);
            LU32(0x12b0) = 0;
            LU32(0x12b4) = 0;
            LU32(0x12b8) = 0;
            LU8(0x12bc) = 1;
            LU32(0x12c0) = 0;
            layer->mark(8, 0x16e0, 1);
            LU32(0x1070) = 7;
            LU32(0x1074) = 5;
            LU32(0x1078) = 4;
            LU32(0x107c) = 7;
            layer->mark(8, 0x16d8, 1);
            if ((*(s32*)&layer->curPass) != 1) {
                (*(s32*)&layer->curPass) = 1;
                layer->curFifo = &layer->passes[layer->curPass];
            }
            (*(s32*)&layer->hw.blend[0]) = 1;
            (*(s32*)&layer->hw.blend[1]) = 4;
            (*(s32*)&layer->hw.blend[2]) = 5;
            (*(s32*)&layer->hw.blend[3]) = 5;
            layer->mark(0x40, 0x170c, 1);
            GStexture* t = mOffscreenData;
            if ((*(GStexture**)&layer->dirty[0].tex[0]) != t || (*(GStexture**)&layer->dirty[1].tex[0]) != t || ((u8*)t)[7] != 0) {
                (*(GStexture**)&layer->dirty[0].tex[0]) = t;
                (*(u32*)&layer->dirty[0].texMask) |= 1;
                (*(GStexture**)&layer->dirty[1].tex[0]) = t;
                (*(u32*)&layer->dirty[1].texMask) |= 1;
            }
            layer->beginSurface(4);
            GXFifoNV.s16 = 0;
            GXFifoNV.s16 = 0;
            GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = alpha;
            GXFifoNV.u8 = 0;
            GXFifoNV.u8 = 0;
            GXFifoNV.s16 = 640;
            GXFifoNV.s16 = 0;
            GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = alpha;
            GXFifoNV.u8 = 1;
            GXFifoNV.u8 = 0;
            GXFifoNV.s16 = 640;
            GXFifoNV.s16 = 480;
            GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = alpha;
            GXFifoNV.u8 = 1;
            GXFifoNV.u8 = 1;
            GXFifoNV.s16 = 0;
            GXFifoNV.s16 = 480;
            GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = 0xFF; GXFifoNV.u8 = alpha;
            GXFifoNV.u8 = 0;
            GXFifoNV.u8 = 1;
            layer->endSurface();
        }
    }
#undef LU8
#undef LU32
}

void WorldMapModel::initializeOffscreenData()
{
    mOffscreenData = GStextureCreate(0, 0, 0x45, 0, 0);
    if (mOffscreenData != 0) {
        GSgfxLayerConfig::Move((GSgfxLayerID)2, (GSgfxLayerID)0, (GSgfxLayerOffset)1);
        GSgfxLayer* l2 = GSgfxLayerFindByID(2);
        l2->SetTextureCopy(mOffscreenData, false, 0);
        l2->SetClearFlags(true, true, true);
    }
}

void* WorldMapModel::SetModel(u32 groupID, u32 modelID, bool attachLights)
{
    s32 layer[1] = { 0 };
    u32 base;
    u32 k;
    ArchiveHeader* hdr;
    u32 i = 0;
    s32 j = 0;
    u32 id;
    void* l;
    hdr = (ArchiveHeader*)makeArchiveHeader(modelID);
    if (hdr == 0) {
        return 0;
    }
    if (hdr->models != 0) {
        base = floorReadMakeModelResID(modelID);
        k = 0;
        while (GC_AT(void*, hdr->models, k) != 0) {
            void* m = GSmodelLoad(GC_AT(void*, hdr->models, k), 0);
            id = base | i;
            GSresFreeResource(groupID, id);
            GSresRegisterResource(m, groupID, id, _unloadModel);
            GSmodelSetRenderLayer(m, 1, layer);
            if (m == 0) {
                GSlogWrite("Error! %s: couldn't load model %d\n", __FUNCTION__);
                GSlogWrite("\x83\x82\x83\x66\x83\x8B\x82\xCC\x8F\x89\x8A\xFA\x89\xBB\x82\xC9\x8E\xB8\x94\x73\n");
            } else {
                GSmodelSetVisibility(m, 1);
                if ((u8)GSmodelCanAnimate(m) != 0) {
                    GSmodelSetAnimIndex(m, 0);
                    GSmodelSetAnimRate(m, 0.5f);
                    GSmodelStartAnimation(m);
                }
                if ((u8)GSmodelCanTexAnimate(m) != 0) {
                    GSmodelSetTexAnimIndex(m, 0);
                    GSmodelSetTexAnimRate(m, 0.5f);
                    GSmodelStartTexAnimation(m);
                }
            }
            k += 4;
            i++;
        }
    }
    if (hdr->lights != 0) {
        base = floorReadMakeLightResID(modelID);
        k = 0;
        while (GC_AT(void*, hdr->lights, k) != 0) {
            l = GSlightLoad(GC_AT(void*, hdr->lights, k));
            if (l == 0) {
                GSlogWrite("Error! floorReadMapPostFunc: couldn't load light %d\n", j);
                GSlogWrite("\x83\x89\x83\x43\x83\x67\x82\xCC\x8F\x89\x8A\xFA\x89\xBB\x82\xC9\x8E\xB8\x94\x73\n");
            } else {
                GSresRegisterResource(l, groupID, base | j, _unloadLight);
                if (attachLights && l != 0) {
                    if (j == 0) {
                        GSlightSetType(l, 0);
                    } else {
                        GSlightSetType(l, 1);
                    }
                    GSlightSetActive(l, 1);
                    if ((u8)GSlightCanAnimate(l) != 0) {
                        GSlightSetAnimIndex(l, 0);
                        GSlightSetAnimRate(l, 0.5f);
                        GSlightStartAnimation(l);
                    }
                }
            }
            k += 4;
            j++;
        }
    }
    return hdr;
}

void WorldMapModel::UnloadModel(u32 groupID, u32 modelID)
{
    u32 base;
    ArchiveHeader* hdr;
    u32 k;
    u32 i = 0;
    u32 j = 0;
    hdr = (ArchiveHeader*)makeArchiveHeader(modelID);
    if (hdr != 0) {
        if (hdr->models != 0) {
            base = floorReadMakeModelResID(modelID);
            k = 0;
            while (GC_AT(u32, hdr->models, k) != 0) {
                GSresFreeResource(groupID, base | i);
                k += 4;
                i++;
            }
        }
        if (hdr->lights != 0) {
            base = floorReadMakeLightResID(modelID);
            k = 0;
            while (GC_AT(u32, hdr->lights, k) != 0) {
                GSresFreeResource(groupID, base | j);
                k += 4;
                j++;
            }
            floorSetLightInfo(base, j);
        } else {
            floorSetLightInfo(0, 0);
        }
    }
}

void WorldMapModel::ObjectVisibility(u32 id, bool visible)
{
    u32 k;
    ArchiveHeader* hdr = (ArchiveHeader*)makeArchiveHeader(id);
    u32 res = floorReadMakeModelResID(id);
    if (hdr->models != 0) {
        k = 0;
        while (GC_AT(u32, hdr->models, k) != 0) {
            Visibility(res, visible);
            res++;
            k += 4;
        }
    }
}

void WorldMapModel::Visibility(u32 id, bool visible)
{
    void* m = GSresGetResourceAllGroup(id);
    if (m != 0) {
        GSmodelSetVisibility(m, visible);
    }
}

bool WorldMapModel::ModelDetach(u32 id)
{
    void* m = GSresGetResourceAllGroup(id);
    if (m == 0) {
        return false;
    }
    GSmodelDetachFromGSpart(m, 1);
    return true;
}

bool WorldMapModel::ModelAttach(u32 a, u32 b, s32 part, GSattachMode mode)
{
    void* m = GSresGetResourceAllGroup(a);
    if (m == 0) {
        return false;
    }
    void* target = GSresGetResourceAllGroup(b);
    if (target == 0) {
        return false;
    }
    void* p = GSmodelGetPart(target, part);
    GSmodelAttachToGSpart(m, p, 7, 0, 1);
    GSpartFree(p);
    return true;
}

_GSparticleGen* WorldMapModel::SetModelPartPaticle(u32 a, u32 b, s32 part, GSattachMode mode, bool x, bool y, bool z)
{
    void* gen;
    void* p = GSmodelGetPart(GSresGetResourceAllGroup(a), part);
    gen = GSparticleCreateGenerator(GSresGetResourceAllGroup(b), 0, 0);
    GSparticleAttachGeneratorToGSpart(gen, p, mode, x, y, z);
    GSpartFree(p);
    return (_GSparticleGen*)gen;
}

void WorldMapModel::DetachModelPartPaticle(_GSparticleGen* gen, bool b)
{
    GSparticleDetachGeneratorFromGSpart(gen, b);
}

static bool _unloadModel(void* p, u32, u32)
{
    GSmodelFree(p);
    return true;
}

static bool _unloadLight(void* p, u32, u32)
{
    GSlightFree(p);
    return true;
}

void* WorldMapModel::makeArchiveHeader(u32 id)
{
    return HSD_ArchiveGetPublicAddress(GSresGetResourceAllGroup(id), "scene_data");
}

f32 WorldMapModel::GetAnimeFrameCount(u32 id, u32 motion)
{
    void* m = GSresGetResourceAllGroup(id);
    if (m == 0) {
        return 0.0f;
    }
    return GSmodelGetAnimFrameCount(m, motion);
}

f32 WorldMapModel::GetAnimeFrame(u32 id)
{
    void* m = GSresGetResourceAllGroup(id);
    if (m == 0) {
        return 0.0f;
    }
    return GSmodelGetAnimFrame(m);
}

void WorldMapModel::StopMotion(u32 id)
{
    void* m = GSresGetResourceAllGroup(id);
    if (m != 0) {
        GSmodelStopAnimation(m);
    }
}

bool WorldMapModel::CheckMotion(u32 id)
{
    void* m = GSresGetResourceAllGroup(id);
    if (m == 0) {
        return false;
    }
    return GSmodelIsAnimating(m) != 0;
}

void WorldMapModel::SetMotion(u32 id, s16 motion, f32 frame, bool loop)
{
    void* m = GSresGetResourceAllGroup(id);
    if (m != 0) {
        GSmodelSetAnimIndex(m, motion);
        GSmodelSetAnimFrame(m, frame);
        GSmodelSetAnimRate(m, 0.5f);
        if (loop) {
            GSmodelSetAnimType(m, 1);
        } else {
            GSmodelSetAnimType(m, 0);
        }
        GSmodelStartAnimation(m);
    }
}

void WorldMapModel::SetLayerID(u32 id, s32 count, GSgfxLayerID* layers)
{
    void* m = GSresGetResourceAllGroup(id);
    if (m != 0) {
        GSmodelSetRenderLayer(m, 1, (s32*)layers);
    }
}

void* WorldMapModel::GetModelPtr(u32 id)
{
    return GSresGetResourceAllGroup(id);
}
