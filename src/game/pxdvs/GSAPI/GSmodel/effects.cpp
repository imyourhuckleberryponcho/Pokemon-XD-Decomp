// Not yet decompiled.
#include <dolphin/types.h>
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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
enum Mtx { Mtx_draft_dummy };
struct Vec;
struct _GSmodel;

extern "C++" {
// ---- draft declarations ----
struct GScamera {
    u8 _draft[1];
};
struct GSgfxLayer {
    u8 _draft[1];
    s32 tunitIndTexMtx(GSgfxIndTexMtxID, float(*)[3], signed char);
    s32 tunitFunc(unsigned char, GSgfxTunitFunc);
    GStexture* GetFBTexture();
    s32 tgenFunc(unsigned char, GSgfxTgenFunc, GSgfxTgenSrc, GSmtx*, bool, GSmtx*);
    void SetLayerVisibility(bool);
    s32 dlDrawExt(unsigned char*, unsigned long);
    bool IsLayerVisible();
};
struct GSgfxLayerConfig {
    u8 _draft[1];
    void Remove(GSgfxLayerID);
    s32 Add(char*, unsigned long, unsigned long, unsigned long, GSgfxLayerType, bool, bool, bool, GSgfxLayerID, GSgfxLayerOffset);
};
struct GSgfxMatrixStack {
    u8 _draft[1];
    void pushMult(GSmtx*);
    s32 pop();
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSmaterial {
    u8 _draft[1];
};
struct GSmtx {
    u8 _draft[1];
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
    u8 _draft[1];
};
struct ModelBank {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
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
int GSgfxLayerFindByID(int id);
GSgfxLayer* GSgfxLayerFindByName(const char* name);
s32 GSgfxPerfbarCPUEntry(s32);
void GSgfxVFCreate(GSgfxVF* vf);
s32 GSgfxVFFree();
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
u32 GSpartGetMaterial(u8);
s32 GSpartGetMatrix(s32*);
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
    f32 unksp20;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    u8 temp_r31;
    GSgfxLayer *temp_r29;
    GStexture *temp_r3_3;
    _GSmodel *var_r28;
    _GSmodel *var_r4;
    s32 temp_cr0_eq;
    GScamera *temp_r3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r27;
    u8 temp_r3_2;
    u8 temp_r4;
    u8 var_r5;

    temp_r29 = GSgfxLayerFindByName((const char*)("model distortion"));
    temp_r3 = GScameraGetActiveCamera();
    if ((temp_r3 != NULL) && (temp_r29 != NULL)) {
        temp_r3_2 = ((GSgfxLayer*)(temp_r29))->IsLayerVisible();
        if (temp_r3_2 != 0) {
            temp_r3_3 = ((GSgfxLayer*)((GSgfxLayer *) temp_r3_2))->GetFBTexture();
            if (temp_r3_3 != NULL) {
                var_r4 = _modelTopPtr;
                var_r5 = 0;
loop_9:
                if (var_r4 != NULL) {
                    temp_r3_4 = M2C_FIELD(var_r4, s32 *, 0);
                    if ((temp_r3_4 & 0x04000000) && ((u32) ((temp_r3_4 & 0x80000) + 0xFFF80000) == 0U)) {
                        var_r5 = 1;
                    } else {
                        var_r4 = M2C_FIELD(var_r4, _GSmodel **, 4);
                        goto loop_9;
                    }
                }
                if (var_r5 != 0) {
                    temp_r27 = GSgfxPerfbarCPUEntry(0x8080FF);
                    temp_r4 = M2C_FIELD(temp_r29, u8 *, 0x16A7);
                    M2C_FIELD(temp_r29, u8 *, 0x16A7) = 0U;
                    temp_r31 = temp_r4 != 0;
                    M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x40);
                    GScameraLoadActiveCameraMatrix((GSgfxLayerID)(M2C_FIELD(temp_r29, s32 *, 0x28)));
                    GScameraGetPerspective((GScamera*)(temp_r3), (f32*)(&sp10), (f32*)(&spC), (f32*)(&sp8), (f32*)(&sp8));
                    GScameraGetPosition((GScamera*)(temp_r3), (f32*)(&sp14));
                    C_MTXLightPerspective((Mtx)((s32) &unksp20), sp10, spC, 0.5f, -0.5f, 0.5f, 0.5f);
                    M2C_FIELD(temp_r29, s32 *, 0xD8C) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x16B8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16B8) | 2);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 2);
                    M2C_FIELD(temp_r29, s32 *, 0x1770) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1770) | 2);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 2);
                    M2C_FIELD(temp_r29, s32 *, 0xD90) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x16B8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16B8) | 4);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 2);
                    M2C_FIELD(temp_r29, s32 *, 0x1770) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1770) | 4);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 2);
                    M2C_FIELD(temp_r29, s8 *, 0xD88) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x16B8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16B8) | 8);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 2);
                    M2C_FIELD(temp_r29, s32 *, 0x1770) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1770) | 8);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 2);
                    M2C_FIELD(temp_r29, s16 *, 0xD70) = 0;
                    M2C_FIELD(temp_r29, s16 *, 0xD72) = 0;
                    GSgfxVideoGetEFBSize((u16*)(((u8*)(temp_r29) + 0xD74)), (u16*)(((u8*)(temp_r29) + 0xD76)));
                    M2C_FIELD(temp_r29, s32 *, 0x16B8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16B8) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 2);
                    M2C_FIELD(temp_r29, s32 *, 0x1770) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1770) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 2);
                    M2C_FIELD(temp_r29, s8 *, 0x1656) = 1;
                    M2C_FIELD(temp_r29, s8 *, 0x1657) = 0;
                    M2C_FIELD(temp_r29, s8 *, 0x1658) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 4);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 4);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x40);
                    M2C_FIELD(temp_r29, s8 *, 0x165C) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0x1660) = 3;
                    M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 8);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 8);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x1664) = 7;
                    M2C_FIELD(temp_r29, s8 *, 0x1670) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x1668) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x166C) = 7;
                    M2C_FIELD(temp_r29, s8 *, 0x1671) = 0;
                    M2C_FIELD(temp_r29, s8 *, 0x1672) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 0x10);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 0x10);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x40);
                    M2C_FIELD(temp_r29, s8 *, 0x1654) = 0;
                    M2C_FIELD(temp_r29, s8 *, 0x1655) = 0xFF;
                    M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 2);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 2);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x40);
                    M2C_FIELD(temp_r29, s8 *, 0x1674) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 0x20);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 0x20);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x40);
                    if ((s32) M2C_FIELD(temp_r29, s32 *, 0x1994) != 1) {
                        M2C_FIELD(temp_r29, s32 *, 0x1994) = 1;
                        M2C_FIELD(temp_r29, u8 **, 0x1990) = (u8 *) (temp_r29 + ((M2C_FIELD(temp_r29, s32 *, 0x1994) * 0xBC) + 0x1818));
                    }
                    M2C_FIELD(temp_r29, s32 *, 0x1644) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0x1648) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0x164C) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x1650) = 5;
                    M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x40);
                    M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x40);
                    M2C_FIELD(temp_r29, s8 *, 0xEAC) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0x16CC) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16CC) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 8);
                    M2C_FIELD(temp_r29, s32 *, 0x1784) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1784) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 8);
                    M2C_FIELD(temp_r29, s8 *, 0x14B0) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0x16EC) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16EC) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x80);
                    M2C_FIELD(temp_r29, s32 *, 0x17A4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17A4) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x80);
                    M2C_FIELD(temp_r29, s8 *, 0xC70) = 2;
                    M2C_FIELD(temp_r29, s32 *, 0x16AC) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16AC) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1764) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1764) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 1);
                    M2C_FIELD(temp_r29, s8 *, 0xDB8) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x16BC) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16BC) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 4);
                    M2C_FIELD(temp_r29, s32 *, 0x1774) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1774) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 4);
                    ((GSgfxLayer*)(temp_r29))->tunitFunc(0U, (GSgfxTunitFunc)(3));
                    M2C_FIELD(temp_r29, s32 *, 0xEB0) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0xEB4) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0xEB8) = 0xFF;
                    M2C_FIELD(temp_r29, s32 *, 0x16D0) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16D0) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 8);
                    M2C_FIELD(temp_r29, s32 *, 0x1788) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1788) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 8);
                    if (((GStexture *) M2C_FIELD(temp_r29, GStexture **, 0x1744) != temp_r3_3) || ((GStexture *) M2C_FIELD(temp_r29, GStexture **, 0x17FC) != temp_r3_3) || ((u8) M2C_FIELD(temp_r3_3, u8 *, 7) != 0)) {
                        M2C_FIELD(temp_r29, GStexture **, 0x1744) = temp_r3_3;
                        M2C_FIELD(temp_r29, s32 *, 0x173C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x173C) | 2);
                        M2C_FIELD(temp_r29, GStexture **, 0x17FC) = temp_r3_3;
                        M2C_FIELD(temp_r29, s32 *, 0x17F4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17F4) | 2);
                    }
                    M2C_FIELD(temp_r29, s32 *, 0x14B4) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x14B8) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x16F0) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16F0) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x80);
                    M2C_FIELD(temp_r29, s32 *, 0x17A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17A8) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x80);
                    M2C_FIELD(temp_r29, s32 *, 0x14D4) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x14D8) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x16F4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16F4) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x80);
                    M2C_FIELD(temp_r29, s32 *, 0x17AC) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17AC) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x80);
                    M2C_FIELD(temp_r29, s32 *, 0x1420) = 2;
                    M2C_FIELD(temp_r29, s8 *, 0x1424) = 0;
                    M2C_FIELD(temp_r29, s8 *, 0x1425) = 1;
                    M2C_FIELD(temp_r29, s8 *, 0x1426) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x1428) = 1;
                    M2C_FIELD(temp_r29, s32 *, 0x16E8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16E8) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 8);
                    M2C_FIELD(temp_r29, s32 *, 0x17A0) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17A0) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 8);
                    ((GSgfxLayer*)(temp_r29))->tgenFunc(0U, (GSgfxTgenFunc)(1), (GSgfxTgenSrc)(4), (GSmtx*)(NULL), 0U, (GSmtx*)(NULL));
                    M2C_FIELD(temp_r29, s8 *, 0xD44) = 0;
                    M2C_FIELD(temp_r29, s8 *, 0xD45) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x16B4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16B4) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x176C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x176C) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 1);
                    var_r28 = _modelTopPtr;
                    while (var_r28 != NULL) {
                        temp_r3_5 = M2C_FIELD(var_r28, s32 *, 0);
                        if ((temp_r3_5 & 0x04000000) && ((u32) ((temp_r3_5 & 0x80000) + 0xFFF80000) == 0U)) {
                            _modelDrawDistortionSub((_GSmodel*)(var_r28), (GSgfxLayer*)(temp_r29), (GSmtx*)(&unksp20), (GSvec*)((GSvec *) &sp14));
                        }
                        var_r28 = M2C_FIELD(var_r28, _GSmodel **, 4);
                    }
                    temp_cr0_eq = temp_r31 == 0;
                    M2C_FIELD(temp_r29, s32 *, 0x1420) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x16E8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16E8) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 8);
                    M2C_FIELD(temp_r29, s32 *, 0x17A0) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17A0) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 8);
                    M2C_FIELD(temp_r29, s8 *, 0x14B0) = 0;
                    M2C_FIELD(temp_r29, s32 *, 0x16EC) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16EC) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x80);
                    M2C_FIELD(temp_r29, s32 *, 0x17A4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17A4) | 1);
                    M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x80);
                    if (temp_cr0_eq) {
                        M2C_FIELD(temp_r29, u8 *, 0x16A7) = temp_r31;
                        M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 0x40);
                        M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 0x40);
                        if (temp_cr0_eq) {
                            M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 0x200);
                            M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 0x200);
                            if ((u8) M2C_FIELD(temp_r29, u8 *, 0x16A6) != 0) {
                                M2C_FIELD(temp_r29, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x170C) | 0x100);
                                M2C_FIELD(temp_r29, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x17C4) | 0x100);
                            }
                        }
                        M2C_FIELD(temp_r29, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x16A8) | 0x40);
                        M2C_FIELD(temp_r29, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r29, s32 *, 0x1760) | 0x40);
                    }
                    GSgfxPerfbarCPUEntry(temp_r27);
                }
            }
        }
    }
}
}

extern "C++" {
static void _modelDrawDistortionSub(_GSmodel* p0, GSgfxLayer* p1, GSmtx* p2, GSvec* p3) {
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp98;
    s32 spA8;
    s32 spB8;
    s32 unksp8C;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp2C;
    f32 sp28;
    f32 sp18;
    s32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    GSpart *temp_r3;
    f32 temp_f31;
    f32 var_f1;
    u8 temp_r3_2;
    u8 temp_r3_3;
    u8 *temp_r31;
    u8 *temp_r3_4;

    if (((u32) ((M2C_FIELD(p0, s32 *, 0) & 0x80000) + 0xFFF80000) == 0U) && ((u32) M2C_FIELD(p0, u32 *, 0x61C) != 0U)) {
        temp_r31 = M2C_FIELD(p0, u8 **, 0x614);
        if (temp_r31 != NULL) {
            temp_r3 = GSmodelGetPart((_GSmodel*)(p0), (s32) M2C_FIELD(p0, u16 *, 0x610));
            if (temp_r3 != NULL) {
                GSpartGetMatrix((s32 *) temp_r3);
                sp8 = sp98;
                spC = spA8;
                sp10 = spB8;
                GSpartFree((GSpart*)(temp_r3));
                var_f1 = PSVECDistance((const register Vec*)((Vec *) &sp8), (const register Vec*)((Vec *) p3));
                if (var_f1 < 1.0f) {
                    var_f1 = 1.0f;
                }
                temp_f31 = 1.0f / var_f1;
                memset((void*)(&sp14), 0, 0x18U);
                temp_r3_2 = M2C_FIELD(p0, u8 *, 0x613);
                if (temp_r3_2 & 1) {
                    if (temp_r3_2 & 4) {
                        sp18 = -0.5f * temp_f31;
                    } else {
                        sp18 = 0.5f * temp_f31;
                    }
                }
                temp_r3_3 = M2C_FIELD(p0, u8 *, 0x613);
                if (temp_r3_3 & 2) {
                    if (temp_r3_3 & 8) {
                        sp28 = -0.5f * temp_f31;
                    } else {
                        sp28 = 0.5f * temp_f31;
                    }
                }
                temp_r3_4 = M2C_FIELD(p0, u8 **, 0x618);
                if (((u8 *) M2C_FIELD(p1, u8 **, 0x1740) != temp_r3_4) || ((u8 *) M2C_FIELD(p1, u8 **, 0x17F8) != temp_r3_4) || ((u8) M2C_FIELD(temp_r3_4, u8 *, 7) != 0)) {
                    M2C_FIELD(p1, u8 **, 0x1740) = temp_r3_4;
                    M2C_FIELD(p1, s32 *, 0x173C) = (s32) (M2C_FIELD(p1, s32 *, 0x173C) | 1);
                    M2C_FIELD(p1, u8 **, 0x17F8) = temp_r3_4;
                    M2C_FIELD(p1, s32 *, 0x17F4) = (s32) (M2C_FIELD(p1, s32 *, 0x17F4) | 1);
                }
                ((GSgfxMatrixStack*)(M2C_FIELD(p1, GSgfxMatrixStack **, 0x19A0)))->pushMult((GSmtx*)(&unksp8C));
                PSMTXConcat((const Mtx)((s32) p2), (const Mtx)(M2C_FIELD(M2C_FIELD(p1, GSgfxMatrixStack **, 0x19A0), s32 *, 4) + 4), (Mtx)((s32) &sp2C));
                sp5C = sp2C;
                sp60 = sp30;
                sp64 = sp34;
                sp68 = sp38;
                sp6C = sp3C;
                sp70 = sp40;
                sp74 = sp44;
                sp78 = sp48;
                sp7C = sp4C;
                sp80 = sp50;
                sp84 = sp54;
                sp88 = sp58;
                PSMTXCopy((const Mtx)((s32) &sp5C), (Mtx)((s32) &unksp8C));
                ((GSgfxLayer*)(p1))->tgenFunc(1U, (GSgfxTgenFunc)(0), (GSgfxTgenSrc)(0), (GSmtx*)(&unksp8C), 0U, (GSmtx*)(NULL));
                ((GSgfxLayer*)(p1))->tunitIndTexMtx((GSgfxIndTexMtxID)(1), (float(*)[3])(&sp14), 1);
                M2C_FIELD(p1, u32 *, 0x199C) = (u32) M2C_FIELD(p0, u32 *, 0x61C);
                ((GSgfxLayer*)(p1))->dlDrawExt((unsigned char*)(M2C_FIELD(temp_r31, u8 **, 0x10)), M2C_FIELD(temp_r31, u16 *, 0xE) << 5);
                ((GSgfxMatrixStack*)(M2C_FIELD(p1, GSgfxMatrixStack **, 0x19A0)))->pop();
            }
        }
    }
}
}

extern "C" {
void GSmodelFreeDistortion(void *p0) {
    GSgfxLayer *temp_r3;
    GSgfxLayer *temp_r3_4;
    GSgfxLayer *temp_ret;
    s32 temp_r4;
    u8 temp_r3_3;
    u8 *temp_r3_2;

    temp_r4 = M2C_FIELD(p0, s32 *, 0);
    if ((u32) ((temp_r4 & 0x80000) + 0xFFF80000) == 0U) {
        M2C_FIELD(p0, s32 *, 0) = (s32) (temp_r4 & 0xFFF7FFFF);
        temp_r3 = GSgfxLayerFindByName((const char*)("model distortion"));
        if (temp_r3 != NULL) {
            ((GSgfxLayer*)(temp_r3))->SetLayerVisibility(0U);
        }
    }
    M2C_FIELD(p0, s16 *, 0x610) = 0;
    M2C_FIELD(p0, s8 *, 0x612) = 0;
    M2C_FIELD(p0, s32 *, 0x614) = 0;
    temp_r3_2 = M2C_FIELD(p0, u8 **, 0x618);
    if (temp_r3_2 != NULL) {
        GSmemFree((void*)(temp_r3_2));
        M2C_FIELD(p0, u8 **, 0x618) = NULL;
        if ((u8) g_distortion_layer_ref_count != 0) {
            temp_r3_3 = g_distortion_layer_ref_count - 1;
            g_distortion_layer_ref_count = temp_r3_3;
            if (temp_r3_3 == 0) {
                temp_ret = GSgfxLayerFindByName((const char*)("model distortion"));
                temp_r3_4 = temp_ret;
                if (temp_r3_4 != NULL) {
                    ((GSgfxLayerConfig*)(M2C_FIELD(temp_r3_4, GSgfxLayerConfig **, 0x28)))->Remove((GSgfxLayerID)((s32) (u32) (u64) temp_ret));
                }
            }
        }
    }
    if ((u8 *) M2C_FIELD(p0, u8 **, 0x61C) != NULL) {
        GSgfxVFFree();
        operator delete((void*)(M2C_FIELD(p0, u8 **, 0x61C)));
        M2C_FIELD(p0, u8 **, 0x61C) = NULL;
    }
}
}

extern "C" {
void GSmodelCreateDistortion(void *p0, u16 p1, u8 p2, u8 p3) {
    s32 spC;
    s32 sp8;
    GSgfxLayer *temp_r3_3;
    GSgfxLayer *var_r28;
    GSpart *temp_r3;
    s32 temp_r4;
    s32 temp_r5;
    u32 temp_r26;
    u32 temp_r3_4;
    u8 var_r30;
    u8 *temp_r25;
    u8 *temp_r31;
    u8 *temp_r3_2;
    u8 *var_r25;

    var_r30 = p3;
    if (((ModelBank *) M2C_FIELD(p0, ModelBank **, 0x618) == NULL) && (p1 != 0)) {
        temp_r3 = GSmodelGetPart((_GSmodel*)((_GSmodel *) p0), (s32) p1);
        if (temp_r3 != NULL) {
            temp_r25 = M2C_FIELD(temp_r3, u8 **, 8);
            temp_r26 = GSpartGetMaterial((u8) temp_r3);
            GSpartFree((GSpart*)(temp_r3));
            if ((temp_r26 != 0) && !(M2C_FIELD(temp_r25, s32 *, 0x14) & 0x4020)) {
                temp_r3_2 = M2C_FIELD(temp_r25, u8 **, 0x18);
                if (temp_r3_2 != NULL) {
                    temp_r31 = M2C_FIELD(temp_r3_2, u8 **, 0xC);
                    if ((temp_r31 != NULL) && ((u8 *) M2C_FIELD(temp_r31, u8 **, 8) != NULL) && ((u16) M2C_FIELD(temp_r31, u16 *, 0xE) != 0) && ((u32) M2C_FIELD(temp_r31, u32 *, 0x10) != 0U) && ((s32) (M2C_FIELD(temp_r31, u16 *, 0xC) & 0x3000) != 0x1000)) {
                        M2C_FIELD(p0, u16 *, 0x610) = p1;
                        M2C_FIELD(p0, u8 *, 0x612) = p2;
                        M2C_FIELD(p0, u8 **, 0x614) = temp_r31;
                        M2C_FIELD(p0, ModelBank **, 0x618) = GSmemAllocClr(0x80U);
                        if ((ModelBank *) M2C_FIELD(p0, ModelBank **, 0x618) != NULL) {
                            if (var_r30 == 0) {
                                var_r30 = 1;
                            }
                            M2C_FIELD(p0, u8 *, 0x613) = var_r30;
                            GSmaterialGetTexture((GSmaterial*)((GSmaterial *) temp_r26), (GStexture*)((GStexture *) M2C_FIELD(p0, ModelBank **, 0x618)));
                            GStextureSetWrap((GStexture*)((GStexture *) M2C_FIELD(p0, ModelBank **, 0x618)), 0U, 0U);
                            GStextureSetFilter((GStexture*)((GStexture *) M2C_FIELD(p0, ModelBank **, 0x618)), 2, 2, 0U);
                            var_r28 = GSgfxLayerFindByName((const char*)("model distortion"));
                            if (var_r28 == NULL) {
                                sp8 = 2;
                                spC = 2;
                                temp_r3_3 = (GSgfxLayer *)(GSgfxLayerFindByID(((GSgfxLayerConfig*)((GSgfxLayerConfig *) "model distortion"))->Add((char*)(NULL), 0x1400U, 2U, 4U, (GSgfxLayerType)(0), 0U, 0U, M2C_ERROR(/* Unable to find stack arg 0x0 in block */), (GSgfxLayerID)(M2C_ERROR(/* Unable to find stack arg 0x4 in block */)), (GSgfxLayerOffset)(M2C_ERROR(/* Unable to find stack arg 0x8 in block */)))));
                                var_r28 = temp_r3_3;
                                if (var_r28 != NULL) {
                                    ((GSgfxLayer*)(temp_r3_3))->SetLayerVisibility(0U);
                                }
                            }
                            g_distortion_layer_ref_count += 1;
                            if (var_r28 == NULL) {
                                GStextureFree((GStexture*)((GStexture *) M2C_FIELD(p0, ModelBank **, 0x618)));
                                M2C_FIELD(p0, ModelBank **, 0x618) = NULL;
                                M2C_FIELD(p0, u8 **, 0x614) = NULL;
                            }
                            M2C_FIELD(p0, u32 *, 0x61C) = (unsigned long)(operator new(0x440U));
                            temp_r3_4 = M2C_FIELD(p0, u32 *, 0x61C);
                            if (temp_r3_4 != 0) {
                                GSgfxVFInit((GSgfxVF*)((GSgfxVF *) temp_r3_4));
                                GSgfxVFCreate((GSgfxVF*)((GSgfxVF *) M2C_FIELD(p0, u32 *, 0x61C)));
                                var_r25 = M2C_FIELD(temp_r31, u8 **, 8);
loop_27:
                                temp_r4 = M2C_FIELD(var_r25, s32 *, 0);
                                if (temp_r4 != 0xFF) {
                                    if ((temp_r4 >= 9) || (temp_r4 < 0)) {
                                        GSgfxVFSetElement((GSgfxVF*)((GSgfxVF *) M2C_FIELD(p0, u32 *, 0x61C)), temp_r4, M2C_FIELD(var_r25, s32 *, 8), M2C_FIELD(var_r25, s32 *, 0xC), (s32) M2C_FIELD(var_r25, u8 *, 0x10));
                                    }
                                    temp_r5 = M2C_FIELD(var_r25, s32 *, 4);
                                    if (temp_r5 != 1) {
                                        GSgfxVFSetArray((GSgfxVF*)((GSgfxVF *) M2C_FIELD(p0, u32 *, 0x61C)), M2C_FIELD(var_r25, s32 *, 0), temp_r5, (void*)(M2C_FIELD(var_r25, u8 **, 0x14)), (s32) (u8) M2C_FIELD(var_r25, u16 *, 0x12), 0);
                                    }
                                    var_r25 += 0x18;
                                    goto loop_27;
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

    if (((u32) ((M2C_FIELD(p0, s32 *, 0) & 0x80000) + 0xFFF80000) != 0U) && ((u32) M2C_FIELD(p0, u32 *, 0x614) != 0U) && ((u32) M2C_FIELD(p0, u32 *, 0x618) != 0U)) {
        temp_r3 = GSgfxLayerFindByName((const char*)("model distortion"));
        if (temp_r3 != NULL) {
            ((GSgfxLayer*)(temp_r3))->SetLayerVisibility(1U);
            M2C_FIELD(p0, s32 *, 0) = (s32) (M2C_FIELD(p0, s32 *, 0) | 0x80000);
        }
    }
}
}

extern "C++" {
void modelDustUpdate(_GSmodel* p0) {
    s32 sp24;
    s32 sp30;
    s32 unksp14;
    s32 unksp20;
    s32 unksp2C;
    f32 sp10;
    f32 spC;
    f32 sp8;
    GSpart *temp_r3;
    GSpart *temp_r3_3;
    GSparticleGenerator *temp_r3_2;
    f32 temp_f0;
    f32 temp_f31;
    s32 var_r28;
    u8 *var_r30;

    if ((GSparticleBank *) M2C_FIELD(p0, GSparticleBank **, 0x5F8) != NULL) {
        GSmodelGetPosition((_GSmodel*)(p0), (GSvec*)(&unksp2C));
        GSmodelGetRotation((_GSmodel*)(p0), (GSvec*)(&unksp14));
        temp_f0 = M2C_FIELD(p0, f32 *, 0x60C);
        var_r30 = ((u8*)(p0) + 0x5FC);
        var_r28 = 0;
        sp8 = temp_f0;
        spC = temp_f0;
        sp10 = temp_f0;
        do {
            if ((u8) M2C_FIELD(var_r30, u8 *, 7) != 0) {
                temp_r3 = GSmodelGetPart((_GSmodel*)(p0), (s32) M2C_FIELD(var_r30, u8 *, 5));
                if (temp_r3 != NULL) {
                    GSpartGetTransform((GSpart*)(temp_r3), (GSvec*)(&unksp20), (GSvec*)(NULL), (GSvec*)(NULL));
                    GSpartFree((GSpart*)(temp_r3));
                    temp_f31 = sp24 - sp30;
                    if (temp_f31 < (M2C_FIELD(var_r30, f32 *, 0) - 0.00001f)) {
                        M2C_FIELD(var_r30, u8 *, 6) = 1U;
                        goto block_10;
                    }
                    if (((u8) M2C_FIELD(var_r30, u8 *, 6) != 0) && (M2C_FIELD(var_r30, u8 *, 6) = 0U, temp_r3_2 = GSparticleCreateGenerator((GSparticleBank*)(M2C_FIELD(p0, GSparticleBank **, 0x5F8)), 0, 0), ((temp_r3_2 == NULL) == 0))) {
                        temp_r3_3 = GSmodelGetPart((_GSmodel*)(p0), (s32) M2C_FIELD(var_r30, u8 *, 4));
                        if (temp_r3_3 != NULL) {
                            GSpartGetTransform((GSpart*)(temp_r3_3), (GSvec*)(&unksp20), (GSvec*)(NULL), (GSvec*)(NULL));
                            GSpartFree((GSpart*)(temp_r3_3));
                            GSparticleSetGeneratorPosition((GSparticleGenerator*)(temp_r3_2), (Vec*)(&unksp20));
                            GSparticleSetGeneratorRotation((s32) temp_r3_2, &unksp14);
                            GSparticleSetGeneratorScale((s32) temp_r3_2, &sp8, 0, 0);
                            goto block_10;
                        }
                    } else {
block_10:
                        M2C_FIELD(var_r30, f32 *, 0) = temp_f31;
                    }
                }
            }
            var_r28 += 1;
            var_r30 += 8;
        } while (var_r28 < 2);
    }
}
}
