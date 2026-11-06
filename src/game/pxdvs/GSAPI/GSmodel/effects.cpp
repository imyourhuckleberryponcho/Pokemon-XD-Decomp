#include <dolphin/types.h>
#include <game/gcdata.h>
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
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct GScamera;
enum GSgfxIndTexMtxID { GSgfxIndTexMtxID_draft_dummy };
struct GSgfxLayer;
struct GSgfxLayerConfig;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxLayerOffset { GSgfxLayerOffset_draft_dummy };
enum GSgfxLayerType { GSgfxLayerType_draft_dummy };
struct GSgfxMatrixStack;
enum GSgfxTgenFunc { GSgfxTgenFunc_draft_dummy };
enum GSgfxTgenSrc { GSgfxTgenSrc_draft_dummy };
enum GSgfxTunitFunc { GSgfxTunitFunc_draft_dummy };
struct GSgfxVF;
struct GSmaterial;
struct GSmtx;
struct GSpart;
struct GSparticleBank;
struct GSparticleGenerator;
struct GStexture;
struct GSvec;
struct ModelBank;
typedef f32 Mtx[3][4];
struct Vec;
struct _GSmodel;

extern "C++" {
struct GScamera {
    u8 _draft[1];
};
#include <game/gsgfxlayer.h>
#include <game/gsmodellayout.h>

struct GSgfxLayer : public GSgfxLayerData {
    void tunitIndTexMtx(GSgfxIndTexMtxID, float(*)[3], signed char);
#ifdef __MWERKS__
    s32 tunitFunc(unsigned char, GSgfxTunitFunc);
#else
    void tunitFunc(unsigned char id, GSgfxTunitFunc func);
#endif
    static GStexture* GetFBTexture();
#ifdef __MWERKS__
    s32 tgenFunc(unsigned char, GSgfxTgenFunc, GSgfxTgenSrc, GSmtx*, bool, GSmtx*);
#else
    void tgenFunc(unsigned char id, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* mtx, bool normalize, GSmtx* postMtx);
#endif
    void SetLayerVisibility(bool);
#ifdef __MWERKS__
    s32 dlDrawExt(unsigned char*, u32);
#else
    void dlDrawExt(unsigned char* p0, u32 p1);
#endif
    bool IsLayerVisible();
};
struct GSgfxLayerConfig {
    u8 _draft[1];
    static void Remove(GSgfxLayerID);
#ifdef __MWERKS__
    static s32 Add(char*, u32, u32, u32, GSgfxLayerType, bool, bool, bool, GSgfxLayerID, GSgfxLayerOffset);
#else
    static GSgfxLayerID Add(char* name, u32 width, u32 height, u32 count, GSgfxLayerType type, bool clearColor,
                                   bool clearAlpha, bool clearDepth, GSgfxLayerID relative, GSgfxLayerOffset offset);
#endif
};
struct GSgfxMatrixStack {
    void* mBase;
    u8* mTop;
    void* mLast;
    void pushMult(GSmtx*);
#ifdef __MWERKS__
    s32 pop();
#else
    void pop();
#endif
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSmaterial {
    u8 _draft[1];
};
struct GSmtx {
    f32 m[3][4];
};
struct GSpart {
    u8 _draft[1];
};
struct GSparticleBank {
    u8 _draft[1];
};
struct GSparticleGenerator {
    u8 _draft[1];
};
struct GStexture {
    u8 _draft[1];
};
struct GSvec {
    f32 x, y, z;
};
struct ModelBank {
    u8 _draft[1];
};
struct Vec {
    f32 x, y, z;
};
struct _GSmodel {
    u8 _draft[1];
};

extern "C" {
void C_MTXLightPerspective(Mtx m, f32 fovY, f32 aspect, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
GScamera* GScameraGetActiveCamera(void);
void GScameraGetPerspective(GScamera* camera, f32* fov, f32* aspect, f32* near, f32* far);
void GScameraGetPosition(GScamera* camera, f32* position);
void GScameraLoadActiveCameraMatrix(GSgfxLayerID id);
struct GSgfxLayer* GSgfxLayerFindByID(GCsint id);
GSgfxLayer* GSgfxLayerFindByName(const char* name);
s32 GSgfxPerfbarCPUEntry(s32);
void GSgfxVFCreate(GSgfxVF* vf);
void GSgfxVFFree(GSgfxVF*);
void GSgfxVFInit(GSgfxVF* vf);
void GSgfxVFSetArray(GSgfxVF* vf, s32, s32, void*, s32, s32);
void GSgfxVFSetElement(GSgfxVF* vf, s32, s32, s32, s32);
void GSgfxVideoGetEFBSize(u16* w, u16* h);
void GSmaterialGetTexture(GSmaterial* material, GStexture* texture);
ModelBank* GSmemAllocClr(u32 size);
void GSmemFree(void* ptr);
void GSmodelCreateDistortion(void *p0, u16 p1, u8 p2, u8 p3);
void GSmodelEnableDistortion(void *p0);
void GSmodelFreeDistortion(void *p0);
GSpart* GSmodelGetPart(_GSmodel* model, s32 index);
void GSmodelGetPosition(_GSmodel* model, GSvec* position);
void GSmodelGetRotation(_GSmodel* model, GSvec* rotation);
void GSpartFree(GSpart* part);
GSmaterial* GSpartGetMaterial(GSpart* part, u32 index);
void GSpartGetMatrix(GSpart* part, Mtx out);
void GSpartGetTransform(GSpart* part, GSvec* pos, GSvec* rot, GSvec* scale);
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank* bank, s32 index, s32);
void GSparticleSetGeneratorPosition(GSparticleGenerator* gen, Vec* pos);
s32 GSparticleSetGeneratorRotation(s32, s32*);
s32 GSparticleSetGeneratorScale(s32, f32*, s32, s32);
void GStextureFree(GStexture* tex);
void GStextureSetFilter(GStexture* tex, s32 minFilter, s32 magFilter, u32 mipFilter);
void GStextureSetWrap(GStexture* tex, u32 wrapS, u32 wrapT);
asm void PSMTXConcat(const register Mtx a, const register Mtx b, register Mtx ab);
asm void PSMTXCopy(const register Mtx src, register Mtx dst);
f32 PSVECDistance(const register Vec* a, const register Vec* b);
void* memset(void* dst, int val, size_t n);
extern _GSmodel* _modelTopPtr;
}
extern "C++" {
static void _modelDrawDistortionSub(_GSmodel* p0, GSgfxLayer* p1, GSmtx* p2, GSvec* p3);
void modelDistortionRender();
void modelDustUpdate(_GSmodel* p0);
}
s8 g_distortion_layer_name[0x14] = "model distortion";
static u8 g_distortion_layer_ref_count;
void modelDistortionRender() {
    Mtx unksp20;
    Vec sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    u8 temp_r31;
    GSgfxLayer *temp_r29;
    GStexture *temp_r3_3;
    _GSmodel *var_r28;
    _GSmodel *var_r4;
    GScamera *temp_r3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r27;
    u8 temp_r3_2;
    u8 temp_r4;
    u8 var_r5;

    temp_r29 = GSgfxLayerFindByName((const char*)g_distortion_layer_name);
    temp_r3 = GScameraGetActiveCamera();
    if ((temp_r3 != NULL) && (temp_r29 != NULL)) {
        temp_r3_2 = ((GSgfxLayer*)(temp_r29))->IsLayerVisible();
        if (temp_r3_2 != 0) {
            temp_r3_3 = GSgfxLayer::GetFBTexture();
            if (temp_r3_3 != NULL) {
                var_r4 = _modelTopPtr;
                var_r5 = 0;
                while (var_r4 != NULL) {
                    temp_r3_4 = M2C_NAMED(((GSmodelLayout*)(var_r4)), s32 *, 0x0, flags);
                    if ((temp_r3_4 & 0x04000000) && (temp_r3_4 & 0x80000) == 0x80000) {
                        var_r5 = 1;
                        break;
                    }
                    var_r4 = M2C_NAMED(((GSmodelLayout*)(var_r4)), _GSmodel **, 0x4, next);
                }
                if (var_r5 != 0) {
                    temp_r27 = GSgfxPerfbarCPUEntry(0x8080FF);
                    temp_r4 = M2C_NAMED(temp_r29, u8 *, 0x16A7, hw.fogEnable);
                    M2C_NAMED(temp_r29, u8 *, 0x16A7, hw.fogEnable) = 0U;
                    temp_r31 = temp_r4 != 0;
                    M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x40);
                    GScameraLoadActiveCameraMatrix((GSgfxLayerID)(M2C_NAMED(temp_r29, s32 *, 0x28, id)));
                    GScameraGetPerspective((GScamera*)(temp_r3), (f32*)(&sp10), (f32*)(&spC), (f32*)(&sp8), (f32*)(&sp8));
                    GScameraGetPosition((GScamera*)(temp_r3), (f32*)(&sp14));
                    C_MTXLightPerspective(unksp20, sp10, spC, 0.5f, -0.5f, 0.5f, 0.5f);
                    M2C_NAMED(temp_r29, s32 *, 0xD8C, hw.cullMode) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x16B8, dirty[0].raster) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16B8, dirty[0].raster) | 2);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 2);
                    M2C_NAMED(temp_r29, s32 *, 0x1770, dirty[1].raster) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1770, dirty[1].raster) | 2);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 2);
                    M2C_NAMED(temp_r29, s32 *, 0xD90, hw.clipMode) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x16B8, dirty[0].raster) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16B8, dirty[0].raster) | 4);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 2);
                    M2C_NAMED(temp_r29, s32 *, 0x1770, dirty[1].raster) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1770, dirty[1].raster) | 4);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 2);
                    M2C_NAMED(temp_r29, s8 *, 0xD88, hw.coPlanar) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x16B8, dirty[0].raster) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16B8, dirty[0].raster) | 8);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 2);
                    M2C_NAMED(temp_r29, s32 *, 0x1770, dirty[1].raster) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1770, dirty[1].raster) | 8);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 2);
                    M2C_NAMED(temp_r29, s16 *, 0xD70, hw.scissor[0]) = 0;
                    M2C_NAMED(temp_r29, s16 *, 0xD72, hw.scissor[1]) = 0;
                    GSgfxVideoGetEFBSize((u16*)(((u8*)(temp_r29) + 0xD74)), (u16*)(((u8*)(temp_r29) + 0xD76)));
                    M2C_NAMED(temp_r29, s32 *, 0x16B8, dirty[0].raster) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16B8, dirty[0].raster) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 2);
                    M2C_NAMED(temp_r29, s32 *, 0x1770, dirty[1].raster) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1770, dirty[1].raster) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 2);
                    M2C_NAMED(temp_r29, s8 *, 0x1656, hw.colorUpdate) = 1;
                    M2C_NAMED(temp_r29, s8 *, 0x1657, hw.alphaUpdate) = 0;
                    M2C_NAMED(temp_r29, s8 *, 0x1658, hw.zUpdate) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 4);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 4);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x40);
                    M2C_NAMED(temp_r29, s8 *, 0x165C, hw.zEnable) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0x1660, hw.zFunc) = 3;
                    M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 8);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 8);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x1664, hw.alphaComp0) = 7;
                    M2C_NAMED(temp_r29, s8 *, 0x1670, hw.alphaRef0) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x1668, hw.alphaCmpOp) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x166C, hw.alphaComp1) = 7;
                    M2C_NAMED(temp_r29, s8 *, 0x1671, hw.alphaRef1) = 0;
                    M2C_NAMED(temp_r29, s8 *, 0x1672, hw.zCompLoc) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 0x10);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 0x10);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x40);
                    M2C_NAMED(temp_r29, s8 *, 0x1654, hw.dstAlphaEnable) = 0;
                    M2C_NAMED(temp_r29, u8 *, 0x1655, hw.dstAlpha) = 0xFF;
                    M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 2);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 2);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x40);
                    M2C_NAMED(temp_r29, s8 *, 0x1674, hw.dither) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 0x20);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 0x20);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x40);
                    if ((s32) M2C_NAMED(temp_r29, s32 *, 0x1994, curPass) != 1) {
                        M2C_NAMED(temp_r29, s32 *, 0x1994, curPass) = 1;
                        M2C_NAMED(temp_r29, u8 **, 0x1990, curFifo) = (u8 *) ((u8*)temp_r29 + 0x1818 + M2C_NAMED(temp_r29, s32 *, 0x1994, curPass) * 0xBC);
                    }
                    M2C_NAMED(temp_r29, s32 *, 0x1644, hw.blend[0]) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0x1648, hw.blend[1]) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0x164C, hw.blend[2]) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x1650, hw.blend[3]) = 5;
                    M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x40);
                    M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x40);
                    M2C_NAMED(temp_r29, s8 *, 0xEAC, hw.nTevStages) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0x16CC, dirty[0].tev) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16CC, dirty[0].tev) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 8);
                    M2C_NAMED(temp_r29, s32 *, 0x1784, dirty[1].tev) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1784, dirty[1].tev) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 8);
                    M2C_NAMED(temp_r29, s8 *, 0x14B0, hw.nIndStages) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0x16EC, dirty[0].indStage) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16EC, dirty[0].indStage) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x80);
                    M2C_NAMED(temp_r29, s32 *, 0x17A4, dirty[1].indStage) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17A4, dirty[1].indStage) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x80);
                    M2C_NAMED(temp_r29, s8 *, 0xC70, hw.nTexGens) = 2;
                    M2C_NAMED(temp_r29, s32 *, 0x16AC, dirty[0].geom) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16AC, dirty[0].geom) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1764, dirty[1].geom) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1764, dirty[1].geom) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 1);
                    M2C_NAMED(temp_r29, s8 *, 0xDB8, hw.nChans) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x16BC, dirty[0].lightDirty) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16BC, dirty[0].lightDirty) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 4);
                    M2C_NAMED(temp_r29, s32 *, 0x1774, dirty[1].lightDirty) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1774, dirty[1].lightDirty) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 4);
                    ((GSgfxLayer*)(temp_r29))->tunitFunc(0U, (GSgfxTunitFunc)(3));
                    M2C_NAMED(temp_r29, s32 *, 0xEB0, hw.tevOrder[0][0]) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0xEB4, hw.tevOrder[0][1]) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0xEB8, hw.tevOrder[0][2]) = 0xFF;
                    M2C_NAMED(temp_r29, s32 *, 0x16D0, dirty[0].tevOrder) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16D0, dirty[0].tevOrder) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 8);
                    M2C_NAMED(temp_r29, s32 *, 0x1788, dirty[1].tevOrder) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1788, dirty[1].tevOrder) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 8);
                    if (((GStexture *) M2C_NAMED(temp_r29, GStexture **, 0x1744, dirty[0].tex[1]) != temp_r3_3) || ((GStexture *) M2C_NAMED(temp_r29, GStexture **, 0x17FC, dirty[1].tex[1]) != temp_r3_3) || ((u8) M2C_FIELD(temp_r3_3, u8 *, 7) != 0)) {
                        M2C_NAMED(temp_r29, GStexture **, 0x1744, dirty[0].tex[1]) = temp_r3_3;
                        M2C_NAMED(temp_r29, s32 *, 0x173C, dirty[0].texMask) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x173C, dirty[0].texMask) | 2);
                        M2C_NAMED(temp_r29, GStexture **, 0x17FC, dirty[1].tex[1]) = temp_r3_3;
                        M2C_NAMED(temp_r29, s32 *, 0x17F4, dirty[1].texMask) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17F4, dirty[1].texMask) | 2);
                    }
                    M2C_NAMED(temp_r29, s32 *, 0x14B4, hw.indOrder[0][0]) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x14B8, hw.indOrder[0][1]) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x16F0, dirty[0].indOrder) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16F0, dirty[0].indOrder) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x80);
                    M2C_NAMED(temp_r29, s32 *, 0x17A8, dirty[1].indOrder) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17A8, dirty[1].indOrder) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x80);
                    M2C_NAMED(temp_r29, s32 *, 0x14D4, hw.indScale[0][0]) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x14D8, hw.indScale[0][1]) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x16F4, dirty[0].indScale) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16F4, dirty[0].indScale) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x80);
                    M2C_NAMED(temp_r29, s32 *, 0x17AC, dirty[1].indScale) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17AC, dirty[1].indScale) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x80);
                    M2C_NAMED(temp_r29, s32 *, 0x1420, hw.ind[0].type) = 2;
                    M2C_NAMED(temp_r29, s8 *, 0x1424, hw.ind[0].v.ind.indId) = 0;
                    M2C_NAMED(temp_r29, s8 *, 0x1425, hw.ind[0].v.ind.pad[0]) = 1;
                    M2C_NAMED(temp_r29, s8 *, 0x1426, hw.ind[0].v.ind.pad[1]) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x1428, hw.ind[0].v.ind.fmt) = 1;
                    M2C_NAMED(temp_r29, s32 *, 0x16E8, dirty[0].ind) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16E8, dirty[0].ind) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 8);
                    M2C_NAMED(temp_r29, s32 *, 0x17A0, dirty[1].ind) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17A0, dirty[1].ind) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 8);
                    ((GSgfxLayer*)(temp_r29))->tgenFunc(0U, (GSgfxTgenFunc)(1), (GSgfxTgenSrc)(4), (GSmtx*)(NULL), 0U, (GSmtx*)(NULL));
                    M2C_NAMED(temp_r29, s8 *, 0xD44, hw.texOffsets[0][0]) = 0;
                    M2C_NAMED(temp_r29, s8 *, 0xD45, hw.texOffsets[0][1]) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x16B4, dirty[0].texOffsets) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16B4, dirty[0].texOffsets) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x176C, dirty[1].texOffsets) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x176C, dirty[1].texOffsets) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 1);
                    var_r28 = _modelTopPtr;
                    while (var_r28 != NULL) {
                        temp_r3_5 = M2C_NAMED(((GSmodelLayout*)(var_r28)), s32 *, 0x0, flags);
                        if ((temp_r3_5 & 0x04000000) && ((u32) ((temp_r3_5 & 0x80000) + 0xFFF80000) == 0U)) {
                            _modelDrawDistortionSub((_GSmodel*)(var_r28), (GSgfxLayer*)(temp_r29), (GSmtx*)(&unksp20), (GSvec*)((GSvec *) &sp14));
                        }
                        var_r28 = M2C_NAMED(((GSmodelLayout*)(var_r28)), _GSmodel **, 0x4, next);
                    }
                    M2C_NAMED(temp_r29, s32 *, 0x1420, hw.ind[0].type) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x16E8, dirty[0].ind) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16E8, dirty[0].ind) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 8);
                    M2C_NAMED(temp_r29, s32 *, 0x17A0, dirty[1].ind) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17A0, dirty[1].ind) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 8);
                    M2C_NAMED(temp_r29, s8 *, 0x14B0, hw.nIndStages) = 0;
                    M2C_NAMED(temp_r29, s32 *, 0x16EC, dirty[0].indStage) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16EC, dirty[0].indStage) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x80);
                    M2C_NAMED(temp_r29, s32 *, 0x17A4, dirty[1].indStage) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17A4, dirty[1].indStage) | 1);
                    M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x80);
                    if (temp_r31 != 0) {
                        M2C_NAMED(temp_r29, u8 *, 0x16A7, hw.fogEnable) = temp_r31;
                        M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 0x40);
                        M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 0x40);
                        if (temp_r31 != 0) {
                            M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 0x200);
                            M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 0x200);
                            if ((u8) M2C_NAMED(temp_r29, u8 *, 0x16A6, hw.fogRangeEnable) != 0) {
                                M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x170C, dirty[0].pe) | 0x100);
                                M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x17C4, dirty[1].pe) | 0x100);
                            }
                        }
                        M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x16A8, dirty[0].groups) | 0x40);
                        M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) = (s32) (M2C_NAMED(temp_r29, s32 *, 0x1760, dirty[1].groups) | 0x40);
                    }
                    GSgfxPerfbarCPUEntry(temp_r27);
                }
            }
        }
    }
}
}

extern "C++" {
struct DistortionVtxDesc {
    gc_bes32 attr;
    gc_bes32 type;
    gc_bes32 cnt;
    gc_bes32 compType;
    u8 frac;
    u8 pad11;
    gc_be16 stride;
    gc_ptr32(void) data;
};

struct EffPartView {
    u8 inUse;
    u8 pad;
    u16 index;
    void* model;
    u8* jobj;
};
struct EffJObjView {
    void* classInfo;
    u16 refCount;
    u16 refCountIndividual;
    void* next;
    void* parent;
    void* child;
    s32 flags;
    u8* dobj;
};
struct EffDObjView {
    void* classInfo;
    void* next;
    void* mobj;
    u8* pobj;
};
struct EffPObjView {
    void* classInfo;
    void* next;
    DistortionVtxDesc* verts;
    u16 flags;
    u16 n_display;
    u8* display;
};

static void _modelDrawDistortionSub(_GSmodel* model, GSgfxLayer* layer, GSmtx* view, GSvec* camPos) {
    if ((M2C_NAMED(((GSmodelLayout*)(model)), s32 *, 0x0, flags) & 0x80000) == 0x80000 && M2C_NAMED(((GSmodelLayout*)(model)), u32 *, 0x61C, unk61C) != 0) {
        u8* dl = M2C_NAMED(((GSmodelLayout*)(model)), u8 **, 0x614, unk614);
        if (dl != NULL) {
            GSpart* part = GSmodelGetPart(model, M2C_NAMED(((GSmodelLayout*)(model)), u16 *, 0x610, unk610));
            if (part != NULL) {
                GSmtx partMtx;
                GSmtx texMtx;
                GSmtx concat;
                f32 ind[2][3];
                Vec pos;
                f32 dist;
                f32 scale;
                u8 flags;
                u8* tex;

                GSpartGetMatrix(part, partMtx.m);
                pos.x = partMtx.m[0][3];
                pos.y = partMtx.m[1][3];
                pos.z = partMtx.m[2][3];
                GSpartFree(part);
                dist = PSVECDistance(&pos, (Vec*)camPos);
                if (dist < 1.0f) {
                    dist = 1.0f;
                }
                scale = 1.0f / dist;
                memset(ind, 0, sizeof(ind));
                flags = M2C_NAMED(((GSmodelLayout*)(model)), u8 *, 0x613, unk613);
                if (flags & 1) {
                    if (flags & 4) {
                        ind[0][1] = -0.5f * scale;
                    } else {
                        ind[0][1] = 0.5f * scale;
                    }
                }
                flags = M2C_NAMED(((GSmodelLayout*)(model)), u8 *, 0x613, unk613);
                if (flags & 2) {
                    if (flags & 8) {
                        ind[1][2] = -0.5f * scale;
                    } else {
                        ind[1][2] = 0.5f * scale;
                    }
                }
                tex = M2C_NAMED(((GSmodelLayout*)(model)), u8 **, 0x618, unk618);
                if (M2C_NAMED(layer, u8 **, 0x1740, dirty[0].tex[0]) != tex || M2C_NAMED(layer, u8 **, 0x17F8, dirty[1].tex[0]) != tex || tex[7] != 0) {
                    M2C_NAMED(layer, u8 **, 0x1740, dirty[0].tex[0]) = tex;
                    M2C_NAMED(layer, s32 *, 0x173C, dirty[0].texMask) |= 1;
                    M2C_NAMED(layer, u8 **, 0x17F8, dirty[1].tex[0]) = tex;
                    M2C_NAMED(layer, s32 *, 0x17F4, dirty[1].texMask) |= 1;
                }
                M2C_NAMED(layer, GSgfxMatrixStack **, 0x19A0, matrixStack)->pushMult(&partMtx);
                PSMTXConcat(view->m, (f32(*)[4])(M2C_NAMED(layer, GSgfxMatrixStack **, 0x19A0, matrixStack)->mTop + 4), concat.m);
                texMtx = concat;
                PSMTXCopy(texMtx.m, partMtx.m);
                layer->tgenFunc(1, (GSgfxTgenFunc)0, (GSgfxTgenSrc)0, &partMtx, 0, NULL);
                layer->tunitIndTexMtx((GSgfxIndTexMtxID)1, ind, 1);
                M2C_NAMED(layer, u32 *, 0x199C, curVF) = M2C_NAMED(((GSmodelLayout*)(model)), u32 *, 0x61C, unk61C);
                layer->dlDrawExt(((EffPObjView*)dl)->display, ((EffPObjView*)dl)->n_display << 5);
                M2C_NAMED(layer, GSgfxMatrixStack **, 0x19A0, matrixStack)->pop();
            }
        }
    }
}
}

extern "C" {
void GSmodelFreeDistortion(void *p0) {
    GSgfxLayer *temp_r3;
    GSgfxLayer *temp_ret;
    s32 temp_r4;
    u8 temp_r3_3;
    u8 *temp_r3_2;

    temp_r4 = M2C_NAMED(((GSmodelLayout*)(p0)), s32 *, 0x0, flags);
    if ((u32) ((temp_r4 & 0x80000) + 0xFFF80000) == 0U) {
        M2C_NAMED(((GSmodelLayout*)(p0)), s32 *, 0x0, flags) = (s32) (temp_r4 & 0xFFF7FFFF);
        temp_r3 = GSgfxLayerFindByName((const char*)g_distortion_layer_name);
        if (temp_r3 != NULL) {
            ((GSgfxLayer*)(temp_r3))->SetLayerVisibility(0U);
        }
    }
    M2C_NAMED(((GSmodelLayout*)(p0)), s16 *, 0x610, unk610) = 0;
    M2C_NAMED(((GSmodelLayout*)(p0)), s8 *, 0x612, unk612) = 0;
    M2C_NAMED(((GSmodelLayout*)(p0)), s32 *, 0x614, unk614) = 0;
    temp_r3_2 = M2C_NAMED(((GSmodelLayout*)(p0)), u8 **, 0x618, unk618);
    if (temp_r3_2 != NULL) {
        GSmemFree((void*)(temp_r3_2));
        M2C_NAMED(((GSmodelLayout*)(p0)), u8 **, 0x618, unk618) = NULL;
        if ((u8) g_distortion_layer_ref_count != 0) {
            g_distortion_layer_ref_count--;
            if (g_distortion_layer_ref_count == 0) {
                temp_ret = GSgfxLayerFindByName((const char*)g_distortion_layer_name);
                if (temp_ret != NULL) {
                    GSgfxLayerConfig::Remove(M2C_NAMED(temp_ret, GSgfxLayerID *, 0x28, id));
                }
            }
        }
    }
    GSgfxVF* vf = M2C_NAMED(((GSmodelLayout*)(p0)), GSgfxVF **, 0x61C, unk61C);
    if (vf != NULL) {
        GSgfxVFFree(vf);
        operator delete((void*)(M2C_NAMED(((GSmodelLayout*)(p0)), u8 **, 0x61C, unk61C)));
        M2C_NAMED(((GSmodelLayout*)(p0)), u8 **, 0x61C, unk61C) = NULL;
    }
}
}

extern "C" {

void GSmodelCreateDistortion(void *model, u16 partIndex, u8 material, u8 flags) {
    GSpart* part;
    GSgfxLayer* layer;
    GSmaterial* mat;
    u8* dl;
    u8* shape;
    u8* sub;
    DistortionVtxDesc* desc;

    if (M2C_NAMED(((GSmodelLayout*)(model)), ModelBank **, 0x618, unk618) == NULL && partIndex != 0) {
        part = GSmodelGetPart((_GSmodel*)model, partIndex);
        if (part != NULL) {
            shape = ((EffPartView*)part)->jobj;
            mat = GSpartGetMaterial(part, material);
            GSpartFree(part);
            if (mat != NULL && (((EffJObjView*)shape)->flags & 0x4020 ? 0 : 1) && (sub = ((EffJObjView*)shape)->dobj) != NULL) {
                dl = ((EffDObjView*)sub)->pobj;
                if (dl != NULL && ((EffPObjView*)dl)->verts != NULL && ((EffPObjView*)dl)->n_display != 0 && ((EffPObjView*)dl)->display != 0 &&
                    (((EffPObjView*)dl)->flags & 0x3000) != 0x1000) {
                    M2C_NAMED(((GSmodelLayout*)(model)), u16 *, 0x610, unk610) = partIndex;
                    M2C_NAMED(((GSmodelLayout*)(model)), u8 *, 0x612, unk612) = material;
                    M2C_NAMED(((GSmodelLayout*)(model)), u8 **, 0x614, unk614) = dl;
                    M2C_NAMED(((GSmodelLayout*)(model)), ModelBank **, 0x618, unk618) = GSmemAllocClr(0x80);
                    if (M2C_NAMED(((GSmodelLayout*)(model)), ModelBank **, 0x618, unk618) != NULL) {
                        if (flags == 0) {
                            flags = 1;
                        }
                        M2C_NAMED(((GSmodelLayout*)(model)), u8 *, 0x613, unk613) = flags;
                        GSmaterialGetTexture(mat, (GStexture*)M2C_NAMED(((GSmodelLayout*)(model)), ModelBank **, 0x618, unk618));
                        GStextureSetWrap((GStexture*)M2C_NAMED(((GSmodelLayout*)(model)), ModelBank **, 0x618, unk618), 0, 0);
                        GStextureSetFilter((GStexture*)M2C_NAMED(((GSmodelLayout*)(model)), ModelBank **, 0x618, unk618), 2, 2, 0);
                        layer = GSgfxLayerFindByName((const char*)g_distortion_layer_name);
                        if (layer == NULL) {
                            layer = (GSgfxLayer*)GSgfxLayerFindByID(GSgfxLayerConfig::Add((char*)g_distortion_layer_name, 0, 0x1400, 2,
                                                                                           (GSgfxLayerType)4, 0, 0, 0, (GSgfxLayerID)2,
                                                                                           (GSgfxLayerOffset)2));
                            if (layer != NULL) {
                                layer->SetLayerVisibility(0);
                            }
                        }
                        g_distortion_layer_ref_count++;
                        if (layer == NULL) {
                            GStextureFree((GStexture*)M2C_NAMED(((GSmodelLayout*)(model)), ModelBank **, 0x618, unk618));
                            M2C_NAMED(((GSmodelLayout*)(model)), ModelBank **, 0x618, unk618) = NULL;
                            M2C_NAMED(((GSmodelLayout*)(model)), u8 **, 0x614, unk614) = NULL;
                        }
                        M2C_NAMED(((GSmodelLayout*)(model)), u32 *, 0x61C, unk61C) = (u32)operator new(0x440);
                        if (M2C_NAMED(((GSmodelLayout*)(model)), u32 *, 0x61C, unk61C) != 0) {
                            GSgfxVFInit((GSgfxVF*)M2C_NAMED(((GSmodelLayout*)(model)), u32 *, 0x61C, unk61C));
                            GSgfxVFCreate((GSgfxVF*)M2C_NAMED(((GSmodelLayout*)(model)), u32 *, 0x61C, unk61C));
                            s32 attr;
                            for (desc = ((EffPObjView*)dl)->verts; (attr = desc->attr) != 0xFF; desc++) {
                                if (attr >= 9 || attr < 0) {
                                    GSgfxVFSetElement((GSgfxVF*)M2C_NAMED(((GSmodelLayout*)(model)), u32 *, 0x61C, unk61C), attr, desc->cnt, desc->compType,
                                                      desc->frac);
                                }
                                if (desc->type != 1) {
                                    GSgfxVFSetArray((GSgfxVF*)M2C_NAMED(((GSmodelLayout*)(model)), u32 *, 0x61C, unk61C), desc->attr, desc->type, desc->data,
                                                    (u8)desc->stride, 0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
}

extern "C" {
void GSmodelEnableDistortion(void *p0) {
    GSgfxLayer *temp_r3;

    if (((u32) ((M2C_NAMED(((GSmodelLayout*)(p0)), s32 *, 0x0, flags) & 0x80000) + 0xFFF80000) != 0U) && ((u32) M2C_NAMED(((GSmodelLayout*)(p0)), u32 *, 0x614, unk614) != 0U) && ((u32) M2C_NAMED(((GSmodelLayout*)(p0)), u32 *, 0x618, unk618) != 0U)) {
        temp_r3 = GSgfxLayerFindByName((const char*)g_distortion_layer_name);
        if (temp_r3 != NULL) {
            ((GSgfxLayer*)(temp_r3))->SetLayerVisibility(1U);
            M2C_NAMED(((GSmodelLayout*)(p0)), s32 *, 0x0, flags) = (s32) (M2C_NAMED(((GSmodelLayout*)(p0)), s32 *, 0x0, flags) | 0x80000);
        }
    }
}
}

extern "C++" {
struct ModelDust {
    f32 lastHeight;
    u8 emitPart;
    u8 checkPart;
    u8 armed;
    u8 active;
};

void modelDustUpdate(_GSmodel* model) {
    GSpart* part;
    GSvec pos;
    GSvec partPos;
    GSvec rot;
    GSvec scale;
    ModelDust* dust;
    GSparticleGenerator* gen;
    s32 i;
    f32 height;

    if (M2C_NAMED(((GSmodelLayout*)(model)), GSparticleBank **, 0x5F8, unk5F8) == NULL) {
        return;
    }
    GSmodelGetPosition(model, &pos);
    GSmodelGetRotation(model, &rot);
    f32 s = M2C_NAMED(((GSmodelLayout*)(model)), f32 *, 0x60C, unk60C);
    scale.x = s;
    scale.y = s;
    scale.z = s;
    dust = (ModelDust*)((u8*)model + 0x5FC);
    for (i = 0; i < 2; i++, dust++) {
        if (dust->active == 0) {
            continue;
        }
        part = GSmodelGetPart(model, dust->checkPart);
        if (part == NULL) {
            continue;
        }
        GSpartGetTransform(part, &partPos, NULL, NULL);
        GSpartFree(part);
        height = partPos.y - pos.y;
        if (height < dust->lastHeight - 0.00001f) {
            dust->armed = 1;
        } else if (dust->armed) {
            dust->armed = 0;
            gen = GSparticleCreateGenerator(M2C_NAMED(((GSmodelLayout*)(model)), GSparticleBank **, 0x5F8, unk5F8), 0, 0);
            if (gen != NULL) {
                part = GSmodelGetPart(model, dust->emitPart);
                if (part == NULL) {
                    continue;
                }
                GSpartGetTransform(part, &partPos, NULL, NULL);
                GSpartFree(part);
                GSparticleSetGeneratorPosition(gen, (Vec*)&partPos);
                GSparticleSetGeneratorRotation((GCsptr)gen, (s32*)&rot);
                GSparticleSetGeneratorScale((GCsptr)gen, (f32*)&scale, 0, 0);
            }
        }
        dust->lastHeight = height;
    }
}
}
