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
enum GSgfxCunitAlpha { GSgfxCunitAlpha_draft_dummy };
enum GSgfxCunitSrc { GSgfxCunitSrc_draft_dummy };
enum GSgfxDiffuseFunc { GSgfxDiffuseFunc_draft_dummy };
struct GSgfxLayer;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
struct GSgfxLight;
enum GSgfxLightType { GSgfxLightType_draft_dummy };
struct GSgfxMatrixStack;
enum GSgfxTunitKReg { GSgfxTunitKReg_draft_dummy };
struct GSgfxVF;
struct GSmtx;
enum Mtx { Mtx_draft_dummy };
struct Quaternion;
struct Vec;
struct _EmitParams;
struct _peShape;
struct peColorSpline;
struct peContainer;
struct peEmitterNode;
struct peNode;
struct peShapeContainer;
struct peShapeNode;
struct peSpline;
struct peXform;

extern "C++" {
// ---- draft declarations ----
struct GSgfxLayer {
    u8 _draft[1];
    s32 drawIcosahedron();
    s32 drawCylinder(unsigned char);
    s32 drawSphere(unsigned char, unsigned char);
    s32 cunitChannelGen(unsigned char, GSgfxCunitAlpha, GSgfxCunitSrc, GSgfxCunitSrc, unsigned long, GSgfxLight**, GSgfxLightType, GSgfxDiffuseFunc);
    s32 drawOctahedron();
    s32 drawSphere(unsigned char);
    s32 drawDodecaedron();
    s32 drawCube();
    s32 drawTorus(float, unsigned char, unsigned char);
    void tunitKRegSel(unsigned char, GSgfxTunitKReg);
};
struct GSgfxLight {
    u8 _draft[1];
};
struct GSgfxMatrixStack {
    u8 _draft[1];
    s32 pop();
    void pushMult(GSmtx*);
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSmtx {
    u8 _draft[1];
};
struct Quaternion {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
};
struct _EmitParams {
    u8 _draft[1];
};
struct _peShape {
    u8 _draft[1];
};
struct peColorSpline {
    u8 _draft[1];
};
struct peContainer {
    u8 _draft[1];
    s32 MoveNode(peNode*, peNode*);
    s32 RemoveAll();
    u16 CreateNodes(unsigned short);
    s32 SetLayerVisibility(GSgfxLayerID, bool);
    ~peContainer();
    s32 RemoveNode(peNode*);
    peContainer(peEmitterNode*, unsigned long, unsigned short);
};
struct peEmitterNode {
    u8 _draft[1];
};
struct peNode {
    u8 _draft[1];
    bool Update(peEmitterNode*, float);
    void Start(peEmitterNode*, _EmitParams*);
};
struct peShapeContainer {
    u8 _draft[1];
    void Update(float);
    void Stop();
    static u16 Emit(unsigned short);
    ~peShapeContainer();
    void Start();
    void Render();
    peShapeContainer(peEmitterNode*, _peShape*, unsigned short);
};
struct peShapeNode {
    u8 _draft[1];
    u8 Update(peEmitterNode*, _peShape*, float);
    void Start(peEmitterNode*, _peShape*, _EmitParams*);
    void Render(_peShape*);
};
struct peSpline {
    u8 _draft[1];
};
struct peXform {
    u8 _draft[1];
};

extern "C" {
int EulerToQuat(Vec* euler, Quaternion* q);
s32 GSboundAlwaysInView(s32);
GSgfxVF* GSgfxVFGetPredef(s32 id);
f32 HSD_Randf(void);
asm void PSMTXConcat(const register Mtx a, const register Mtx b, register Mtx ab);
asm void PSMTXMultVec(const register Mtx m, const register Vec* src, register Vec* dst);
asm void PSMTXMultVecSR(const register Mtx m, const register Vec* src, register Vec* dst);
void PSMTXQuat(register Mtx m, const register Quaternion* q);
void PSMTXScale(register Mtx m, register f32 xS, register f32 yS, register f32 zS);
asm void PSMTXTransApply(const register Mtx src, register Mtx dst, register f32 xT, register f32 yT, register f32 zT);
void PSQUATMultiply(const register Quaternion* p, const register Quaternion* q, register Quaternion* pq);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
asm f32 PSVECDotProduct(const register Vec* a, const register Vec* b);
void PSVECNormalize(const register Vec* src, register Vec* unit);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
f32 PSVECSquareMag(const register Vec* v);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double atan2(double y, double x);
s32 particleEngineSetDefaultRenderState(s32);
s32 particleEngineSetupBlendMode(s32);
s32 particleEngineSetupTexture(s32, s32, s32, s32, s32, s32);
void peColorSplineGetValue(u8* out, peColorSpline* s, f32 t);
void peNodeTransformsConcat(peXform* out, peXform* a, peXform* b, bool useGfx);
f32 peSplineGetValue(peSpline* s, f32 t);
extern f32 __float_nan;
extern Vec g_CameraLookDir;
extern s32 g_CameraMatrix;
extern Vec g_CameraPosition;
extern u32 g_currentBound;
extern GSgfxLayer* g_current_layer;
extern _EmitParams* g_emitParams;
extern s32 g_particle_debug_stats;
extern s32 g_render_pass;
extern s32 unitScaleVector;
extern s32 jtbl_1954;
extern s32 this_;
extern s32 jtbl_1843;
}
s32 __vt__16peShapeContainer;
// ---- draft declarations ----



void peShapeContainer::Stop() {
    if ((u8) M2C_FIELD(this, u8 *, 0x19) != 0) {
        M2C_FIELD(M2C_FIELD(this, u8 **, 0x1C), s32 (**)(), 0x10)();
        M2C_FIELD(this, u8 *, 0x19) = 0U;
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x800000) {
            ((peContainer*)((peContainer *)1))->SetLayerVisibility((GSgfxLayerID)(0), M2C_ERROR(/* Read from unset register $r5 */));
        }
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x01000000) {
            ((peContainer*)((peContainer *)3))->SetLayerVisibility((GSgfxLayerID)(0), M2C_ERROR(/* Read from unset register $r5 */));
        }
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x02000000) {
            ((peContainer*)((peContainer *)5))->SetLayerVisibility((GSgfxLayerID)(0), M2C_ERROR(/* Read from unset register $r5 */));
        }
        ((peContainer*)((peContainer *) this))->RemoveAll();
    }
}
}

extern "C++" {
extern "C++" {

extern "C++" {
void peShapeContainer::Render() {
    f32 sp24;
    f32 sp28;
    volatile f32 unksp20;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    GSgfxLight *sp1C;
    GSgfxLight *sp18;
    GSgfxLight *sp14;
    GSgfxLight *sp10;
    s32 sp8;
    GSgfxLight *temp_r11;
    GSgfxLight *temp_r9;
    _peShape *temp_r5;
    peShapeNode *var_r30_2;
    s32 temp_cr0_eq;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r31;
    s32 temp_r4;
    s32 temp_r9_2;
    s32 var_r7;
    s32 var_r8;
    u8 var_r0;
    u8 var_r30;
    u8 var_r7_2;

    temp_cr0_eq = (u8) M2C_FIELD(this, u8 *, 0x19) == 0;
    if (temp_cr0_eq == 0) {
        if (temp_cr0_eq != 0) {
            var_r0 = 0;
        } else {
            temp_r4 = M2C_FIELD(M2C_FIELD(this, _peShape **, 0x20), s32 *, 0);
            if ((u16) M2C_FIELD(this, u16 *, 0x14) == 0) {
                var_r0 = 0;
            } else if ((s32) g_render_pass != 1) {
                var_r0 = 0;
            } else {
                temp_r0 = M2C_FIELD(g_current_layer, s32 *, 0x28);
                switch (temp_r0) {                  /* switch 1; irregular */
                case 0:                             /* switch 1 */
                    if (temp_r4 & 0x200000) {
                        var_r0 = 1;
                    } else {
block_31:
                        var_r0 = 0;
                    }
                    break;
                case 2:                             /* switch 1 */
                    if (temp_r4 & 0x400000) {
                        var_r0 = 1;
                    } else if (!(temp_r4 & 0x03E00008)) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 4:                             /* switch 1 */
                    if (temp_r4 & 8) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 1:                             /* switch 1 */
                    if (temp_r4 & 0x800000) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 3:                             /* switch 1 */
                    if (temp_r4 & 0x01000000) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 5:                             /* switch 1 */
                    if (temp_r4 & 0x02000000) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                default:                            /* switch 1 */
                    var_r0 = 0;
                    break;
                }
            }
        }
        if (var_r0 != 0) {
            temp_r31 = M2C_FIELD(M2C_FIELD(this, _peShape **, 0x20), s32 *, 0);
            if (temp_r31 & 0x800) {
                M2C_FIELD(g_current_layer, s32 *, 0xD8C) = 2;
                M2C_FIELD(g_current_layer, s32 *, 0x16B8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16B8) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1770) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1770) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 2);
            } else {
                M2C_FIELD(g_current_layer, s32 *, 0xD8C) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x16B8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16B8) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1770) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1770) | 2);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 2);
            }
            var_r8 = 0;
            if (temp_r31 & 0x40) {
                var_r8 = 2;
            }
            var_r7 = 0;
            if (temp_r31 & 0x20) {
                var_r7 = 2;
            }
            particleEngineSetupTexture(0, M2C_FIELD(M2C_FIELD(this, _peShape **, 0x20), s32 *, 0x74), 0, 0, var_r7, var_r8);
            particleEngineSetupBlendMode(2);
            if (temp_r31 & 0x200) {
                temp_r9 = M2C_FIELD(M2C_FIELD(this, _peShape **, 0x20), GSgfxLight **, 0x78);
                sp14 = temp_r9;
                var_r30 = 1;
                sp18 = M2C_FIELD(&jtbl_1954, GSgfxLight **, 0);
                M2C_FIELD((u16)g_current_layer, s8 *, 0xEAC) = 1;
                sp1C = M2C_FIELD(&jtbl_1954, GSgfxLight **, 4);
                M2C_FIELD(g_current_layer, s32 *, 0x16CC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16CC) | 1);
                sp18 = temp_r9;
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1784) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1784) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s8 *, 0xDB8) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x16BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16BC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 4);
                M2C_FIELD(g_current_layer, s32 *, 0x1774) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1774) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 4);
                M2C_FIELD(g_current_layer, s32 *, 0x1170) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1174) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1178) = 0;
                M2C_FIELD(g_current_layer, s8 *, 0x117C) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x1180) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x16DC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16DC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1794) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1794) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x12B0) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x12B4) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x12B8) = 0;
                M2C_FIELD(g_current_layer, s8 *, 0x12BC) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x12C0) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x16E0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E0) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1798) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1798) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0xF70) = 0xF;
                M2C_FIELD(g_current_layer, s32 *, 0xF74) = 0xA;
                M2C_FIELD(g_current_layer, s32 *, 0xF78) = 8;
                M2C_FIELD(g_current_layer, s32 *, 0xF7C) = 0xF;
                M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1544) = 0x1C;
                M2C_FIELD(g_current_layer, s32 *, 0x1700) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1700) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x10);
                M2C_FIELD(g_current_layer, s32 *, 0x17B8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17B8) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x10);
                M2C_FIELD(g_current_layer, s32 *, 0x1070) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x1074) = 6;
                M2C_FIELD(g_current_layer, s32 *, 0x1078) = 4;
                M2C_FIELD(g_current_layer, s32 *, 0x107C) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                PSMTXMultVec((const Mtx)(g_CameraMatrix), (const Vec *)((const register Vec*)(M2C_FIELD(this, _peShape **, 0x20) + 0x5C)), (Vec *)((register Vec*)(&unksp20)));
                temp_r0_2 = M2C_FIELD(sp14, s32 *, 4);
                sp38 = unksp20;
                sp3C = sp24;
                sp40 = sp28;
                switch (temp_r0_2) {                /* switch 2; irregular */
                case 2:                             /* switch 2 */
                    M2C_FIELD(sp14, f32 *, 0xC) = unksp20;
                    M2C_FIELD(sp14, f32 *, 0x10) = sp24;
                    M2C_FIELD(sp14, f32 *, 0x14) = sp28;
                default:                            /* switch 2 */
block_48:
                    M2C_FIELD(sp14, u16 *, 0) = (u16) (M2C_FIELD(sp14, u16 *, 0) | 2);
                    break;
                case 1:                             /* switch 2 */
                    M2C_FIELD(sp14, f32 *, 0xC) = unksp20;
                    M2C_FIELD(sp14, f32 *, 0x10) = sp24;
                    M2C_FIELD(sp14, f32 *, 0x14) = sp28;
                    goto block_48;
                }
                sp8 = 2;
                ((GSgfxLayer*)(g_current_layer))->cunitChannelGen(0U, (GSgfxCunitAlpha)(0), (GSgfxCunitSrc)(0), (GSgfxCunitSrc)(0), 1U, (GSgfxLight**)(&sp14), (GSgfxLightType)(2), (GSgfxDiffuseFunc)(M2C_ERROR(/* Unable to find stack arg 0x0 in block */)));
                if (temp_r31 & 0x400) {
                    temp_r11 = M2C_FIELD(M2C_FIELD(this, _peShape **, 0x20), GSgfxLight **, 0x7C);
                    sp10 = temp_r11;
                    M2C_FIELD(g_current_layer, s8 *, 0xEAC) = 2;
                    var_r30 = 2;
                    sp1C = temp_r11;
                    M2C_FIELD(g_current_layer, s32 *, 0x16CC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16CC) | 1);
                    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0x1784) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1784) | 1);
                    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0xEBC) = 0xFF;
                    M2C_FIELD(g_current_layer, s32 *, 0xEC0) = 0xFF;
                    M2C_FIELD(g_current_layer, s32 *, 0xEC4) = 5;
                    M2C_FIELD(g_current_layer, s32 *, 0x16D0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D0) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0x1788) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1788) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0x1184) = 0;
                    M2C_FIELD(g_current_layer, s32 *, 0x1188) = 0;
                    M2C_FIELD(g_current_layer, s32 *, 0x118C) = 0;
                    M2C_FIELD(g_current_layer, s8 *, 0x1190) = 1;
                    M2C_FIELD(g_current_layer, s32 *, 0x1194) = 0;
                    M2C_FIELD(g_current_layer, s32 *, 0x16DC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16DC) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0x1794) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1794) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0x12C4) = 0;
                    M2C_FIELD(g_current_layer, s32 *, 0x12C8) = 0;
                    M2C_FIELD(g_current_layer, s32 *, 0x12CC) = 0;
                    M2C_FIELD(g_current_layer, s8 *, 0x12D0) = 0;
                    M2C_FIELD(g_current_layer, s32 *, 0x12D4) = 0;
                    M2C_FIELD(g_current_layer, s32 *, 0x16E0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E0) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0x1798) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1798) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0xF80) = 0xF;
                    M2C_FIELD(g_current_layer, s32 *, 0xF84) = 0xA;
                    M2C_FIELD(g_current_layer, s32 *, 0xF88) = 0xC;
                    M2C_FIELD(g_current_layer, s32 *, 0xF8C) = 0;
                    M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0x1080) = 7;
                    M2C_FIELD(g_current_layer, s32 *, 0x1084) = 7;
                    M2C_FIELD(g_current_layer, s32 *, 0x1088) = 7;
                    M2C_FIELD(g_current_layer, s32 *, 0x108C) = 0;
                    M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                    M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 2);
                    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                    M2C_FIELD(g_current_layer, s8 *, 0xDB8) = 2;
                    M2C_FIELD(g_current_layer, s32 *, 0x16BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16BC) | 1);
                    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 4);
                    M2C_FIELD(g_current_layer, s32 *, 0x1774) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1774) | 1);
                    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 4);
                    sp8 = 2;
                    ((GSgfxLayer*)(g_current_layer))->cunitChannelGen(1U, (GSgfxCunitAlpha)(0), (GSgfxCunitSrc)(0), (GSgfxCunitSrc)(0), 1U, (GSgfxLight**)(&sp10), (GSgfxLightType)(0), (GSgfxDiffuseFunc)(M2C_ERROR(/* Unable to find stack arg 0x0 in block */)));
                    if (PSVECSquareMag((const register Vec*)(M2C_FIELD(this, _peShape **, 0x20) + 0x5C)) < 0.00001f) {
                        sp2C = 0.0f;
                        sp30 = -1.0f;
                        sp34 = 0.0f;
                    } else {
                        temp_r5 = M2C_FIELD(this, _peShape **, 0x20);
                        sp30 = -M2C_FIELD(temp_r5, f32 *, 0x60);
                        sp2C = -M2C_FIELD(temp_r5, f32 *, 0x5C);
                        sp34 = -M2C_FIELD(temp_r5, f32 *, 0x64);
                        PSVECNormalize((const register Vec*)((Vec *) &sp2C), (register Vec*)((Vec *) &sp2C));
                    }
                    PSMTXMultVecSR((const Mtx)(g_CameraMatrix), (const Vec *)((const register Vec*)((Vec *) &sp2C)), (Vec *)((register Vec*)((Vec *) &sp2C)));
                    temp_r0_3 = M2C_FIELD(sp10, s32 *, 4);
                    if (temp_r0_3 < 2) {
                        if (temp_r0_3 < 0) {

                        } else {
                            M2C_FIELD(sp10, f32 *, 0x18) = sp2C;
                            M2C_FIELD(sp10, f32 *, 0x1C) = sp30;
                            M2C_FIELD(sp10, f32 *, 0x20) = sp34;
                            M2C_FIELD(sp10, u16 *, 0) = (u16) (M2C_FIELD(sp10, u16 *, 0) | 4);
                        }
                    }
                }
                var_r7_2 = 0;
                M2C_FIELD(g_current_layer, u8 *, 0xD94) = var_r30;
loop_62:
                if (var_r7_2 < 8U) {
                    if (var_r7_2 < var_r30) {
                        temp_r9_2 = (var_r7_2 * 4) & 0x3FC;
                        *((u8*)(g_current_layer) + (temp_r9_2 + 0xD98)) = (unsigned char)(*(&sp18 + temp_r9_2));
                    } else {
                        *((u8*)(g_current_layer) + (((var_r7_2 * 4) & 0x3FC) + 0xD98)) = 0;
                    }
                    var_r7_2 += 1;
                    goto loop_62;
                }
                M2C_FIELD(g_current_layer, s32 *, 0x16BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16BC) | 0x10);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 4);
                M2C_FIELD(g_current_layer, s32 *, 0x1774) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1774) | 0x10);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 4);
            } else {
                M2C_FIELD(g_current_layer, s8 *, 0xDB8) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x16BC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16BC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 4);
                M2C_FIELD(g_current_layer, s32 *, 0x1774) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1774) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 4);
                M2C_FIELD(g_current_layer, s8 *, 0xEAC) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x16CC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16CC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1784) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1784) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0xEB0) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0xEB4) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0xEB8) = 0xFF;
                M2C_FIELD(g_current_layer, s32 *, 0x16D0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D0) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1788) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1788) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1170) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1174) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x1178) = 0;
                M2C_FIELD(g_current_layer, s8 *, 0x117C) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x1180) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x16DC) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16DC) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1794) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1794) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x12B0) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x12B4) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x12B8) = 0;
                M2C_FIELD(g_current_layer, s8 *, 0x12BC) = 1;
                M2C_FIELD(g_current_layer, s32 *, 0x12C0) = 0;
                M2C_FIELD(g_current_layer, s32 *, 0x16E0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16E0) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1798) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1798) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                ((GSgfxLayer*)(g_current_layer))->tunitKRegSel(0U, (GSgfxTunitKReg)(0));
                M2C_FIELD(g_current_layer, s32 *, 0xF70) = 0xF;
                M2C_FIELD(g_current_layer, s32 *, 0xF74) = 0xE;
                M2C_FIELD(g_current_layer, s32 *, 0xF78) = 8;
                M2C_FIELD(g_current_layer, s32 *, 0xF7C) = 0xF;
                M2C_FIELD(g_current_layer, s32 *, 0x16D4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D4) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x178C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x178C) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1070) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x1074) = 6;
                M2C_FIELD(g_current_layer, s32 *, 0x1078) = 4;
                M2C_FIELD(g_current_layer, s32 *, 0x107C) = 7;
                M2C_FIELD(g_current_layer, s32 *, 0x16D8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16D8) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 8);
                M2C_FIELD(g_current_layer, s32 *, 0x1790) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1790) | 1);
                M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 8);
            }
            M2C_FIELD(g_current_layer, GSgfxVF **, 0x199C) = GSgfxVFGetPredef(4);
            var_r30_2 = M2C_FIELD(this, peShapeNode **, 0x10);
loop_67:
            if (var_r30_2 != NULL) {
                ((peShapeNode*)(var_r30_2))->Render((_peShape*)(M2C_FIELD(this, _peShape **, 0x20)));
                var_r30_2 = M2C_FIELD(var_r30_2, peShapeNode **, 0x28);
                goto loop_67;
            }
            particleEngineSetDefaultRenderState(1);
        }
    }
}
}
void GSgfxLayer::tunitKRegSel(unsigned char p0, GSgfxTunitKReg p1) {
    u8 *temp_r5_2;
    s32 temp_r6_2;
    u8 *temp_r5_4;
    s32 temp_r6_4;
    u8 *temp_r5;
    s32 temp_r6;
    u8 *temp_r5_3;
    s32 temp_r6_3;

    switch (p1) {                                   /* irregular */
    case 0:
        temp_r5 = (unsigned char *)(this + ((p0 * 4) & 0x3FC));
        M2C_FIELD(temp_r5, s32 *, 0x1504) = 0xC;
        temp_r6 = 1 << p0;
        M2C_FIELD(this, s32 *, 0x16FC) = (s32) (M2C_FIELD(this, s32 *, 0x16FC) | temp_r6);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B4) = (s32) (M2C_FIELD(this, s32 *, 0x17B4) | temp_r6);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        M2C_FIELD(temp_r5, s32 *, 0x1544) = 0x1C;
        M2C_FIELD(this, s32 *, 0x1700) = (s32) (M2C_FIELD(this, s32 *, 0x1700) | temp_r6);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B8) = (s32) (M2C_FIELD(this, s32 *, 0x17B8) | temp_r6);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        return;
    case 1:
        temp_r5_2 = (unsigned char *)(this + ((p0 * 4) & 0x3FC));
        M2C_FIELD(temp_r5_2, s32 *, 0x1504) = 0xD;
        temp_r6_2 = 1 << p0;
        M2C_FIELD(this, s32 *, 0x16FC) = (s32) (M2C_FIELD(this, s32 *, 0x16FC) | temp_r6_2);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B4) = (s32) (M2C_FIELD(this, s32 *, 0x17B4) | temp_r6_2);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        M2C_FIELD(temp_r5_2, s32 *, 0x1544) = 0x1D;
        M2C_FIELD(this, s32 *, 0x1700) = (s32) (M2C_FIELD(this, s32 *, 0x1700) | temp_r6_2);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B8) = (s32) (M2C_FIELD(this, s32 *, 0x17B8) | temp_r6_2);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        return;
    case 2:
        temp_r5_3 = (unsigned char *)(this + ((p0 * 4) & 0x3FC));
        M2C_FIELD(temp_r5_3, s32 *, 0x1504) = 0xE;
        temp_r6_3 = 1 << p0;
        M2C_FIELD(this, s32 *, 0x16FC) = (s32) (M2C_FIELD(this, s32 *, 0x16FC) | temp_r6_3);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B4) = (s32) (M2C_FIELD(this, s32 *, 0x17B4) | temp_r6_3);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        M2C_FIELD(temp_r5_3, s32 *, 0x1544) = 0x1E;
        M2C_FIELD(this, s32 *, 0x1700) = (s32) (M2C_FIELD(this, s32 *, 0x1700) | temp_r6_3);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B8) = (s32) (M2C_FIELD(this, s32 *, 0x17B8) | temp_r6_3);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        return;
    case 3:
        temp_r5_4 = (unsigned char *)(this + ((p0 * 4) & 0x3FC));
        M2C_FIELD(temp_r5_4, s32 *, 0x1504) = 0xF;
        temp_r6_4 = 1 << p0;
        M2C_FIELD(this, s32 *, 0x16FC) = (s32) (M2C_FIELD(this, s32 *, 0x16FC) | temp_r6_4);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B4) = (s32) (M2C_FIELD(this, s32 *, 0x17B4) | temp_r6_4);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        M2C_FIELD(temp_r5_4, s32 *, 0x1544) = 0x1F;
        M2C_FIELD(this, s32 *, 0x1700) = (s32) (M2C_FIELD(this, s32 *, 0x1700) | temp_r6_4);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x10);
        M2C_FIELD(this, s32 *, 0x17B8) = (s32) (M2C_FIELD(this, s32 *, 0x17B8) | temp_r6_4);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x10);
        return;
    }
}
extern "C++" {
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
#pragma push
#pragma dont_inline on
}

}

extern "C++" {
extern "C++" {
#pragma peephole off
u16 peShapeContainer::Emit(unsigned short p0) {
    _EmitParams *var_r30;
    peShapeNode *temp_r29;
    peShapeNode *var_r3;
    s32 temp_r28;
    s32 var_r31;

    if ((u8) M2C_FIELD(this_, u8 *, 0x19) == 0) {
        return 0U;
    }
    var_r31 = ((peContainer*)((peContainer *) this_))->CreateNodes(p0);
    var_r30 = g_emitParams;
    var_r3 = M2C_FIELD(this_, peShapeNode **, 0x10);
    temp_r28 = var_r31;
    while (var_r31 != 0) {
        temp_r29 = M2C_FIELD(var_r3, peShapeNode **, 0x28);
        ((peShapeNode*)(var_r3))->Start((peEmitterNode*)(M2C_FIELD(this_, peEmitterNode **, 0)), (_peShape*)(M2C_FIELD(this_, _peShape **, 0x20)), (_EmitParams*)(var_r30));
        var_r3 = temp_r29;
        var_r31 -= 1;
        var_r30 += 0x48;
    }
    return temp_r28;
}
#pragma peephole reset
}

extern "C++" {
void peShapeContainer::Start() {
    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        M2C_FIELD(this, u8 *, 0x19) = 1U;
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x800000) {
            ((peContainer*)((peContainer *)1))->SetLayerVisibility((GSgfxLayerID)(1), M2C_ERROR(/* Read from unset register $r5 */));
        }
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x01000000) {
            ((peContainer*)((peContainer *)3))->SetLayerVisibility((GSgfxLayerID)(1), M2C_ERROR(/* Read from unset register $r5 */));
        }
        if (*M2C_FIELD(this, s32 **, 0x20) & 0x02000000) {
            ((peContainer*)((peContainer *)5))->SetLayerVisibility((GSgfxLayerID)(1), M2C_ERROR(/* Read from unset register $r5 */));
        }
    }
}
}

extern "C++" {
peShapeContainer::~peShapeContainer() {
    if (this != NULL) {
        M2C_FIELD(this, s32 **, 0x1C) = &__vt__16peShapeContainer;
        M2C_FIELD(&g_particle_debug_stats, s32 *, 4) = (s32) (M2C_FIELD(&g_particle_debug_stats, s32 *, 4) - 0x24);
        M2C_FIELD(&g_particle_debug_stats, s32 *, 0x14) = (s32) (M2C_FIELD(&g_particle_debug_stats, s32 *, 0x14) - 0x24);
        ((peContainer*)((peContainer *) this))->~peContainer();
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
peShapeContainer::peShapeContainer(peEmitterNode* p0, _peShape* p1, unsigned short p2) {
    ((peContainer*)((peContainer *) this))->peContainer((peEmitterNode*)(p0), 0x9CU, p2);
    M2C_FIELD(this, _peShape **, 0x20) = p1;
    M2C_FIELD(this, s32 **, 0x1C) = &__vt__16peShapeContainer;
    M2C_FIELD(&g_particle_debug_stats, s32 *, 4) = (s32) (M2C_FIELD(&g_particle_debug_stats, s32 *, 4) + 0x24);
    M2C_FIELD(&g_particle_debug_stats, s32 *, 0x14) = (s32) (M2C_FIELD(&g_particle_debug_stats, s32 *, 0x14) + 0x24);
    return;
}
}

extern "C++" {
void peShapeNode::Render(_peShape* p0) {
    f32 unksp50;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r5;
    u32 temp_r0;

    temp_r31 = M2C_FIELD(p0, s32 *, 0);
    temp_r4 = M2C_FIELD(this, s32 *, 0x98);
    sp1C = jtbl_1843;
    M2C_FIELD(g_current_layer, s32 *, 0x14F4) = temp_r4;
    sp18 = temp_r4;
    M2C_FIELD(g_current_layer, s32 *, 0x16F8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16F8) | 1);
    M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x10);
    M2C_FIELD(g_current_layer, s32 *, 0x17B0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17B0) | 1);
    M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x10);
    if (temp_r31 & 0x200) {
        temp_r5 = M2C_FIELD(this, s32 *, 0x98);
        temp_r4_2 = M2C_FIELD(p0, s32 *, 0x68);
        sp10 = temp_r5;
        M2C_FIELD(g_current_layer, s32 *, 0xE9C) = temp_r4_2;
        M2C_FIELD(g_current_layer, s32 *, 0xEA4) = temp_r5;
        sp14 = temp_r4_2;
        M2C_FIELD(g_current_layer, s32 *, 0x16C4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16C4) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x16C8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16C8) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 4);
        M2C_FIELD(g_current_layer, s32 *, 0x177C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x177C) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x1780) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1780) | 1);
        M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 4);
        if (temp_r31 & 0x400) {
            temp_r3 = M2C_FIELD(this, s32 *, 0x98);
            sp8 = temp_r3;
            M2C_FIELD(g_current_layer, s32 *, 0xEA0) = (s32) jtbl_1843;
            M2C_FIELD(g_current_layer, s32 *, 0xEA8) = temp_r3;
            spC = jtbl_1843;
            M2C_FIELD(g_current_layer, s32 *, 0x16C4) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16C4) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x16C8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16C8) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 4);
            M2C_FIELD(g_current_layer, s32 *, 0x177C) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x177C) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1780) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1780) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 4);
        }
    }
    PSMTXQuat((Mtx)((s32) &sp20), (const Quaternion *)((const register Quaternion*)(this + 0x3C)));
    PSMTXScale((Mtx)((s32) &unksp50), (float)(M2C_FIELD(this, f32 *, 0x4C)), (float)(M2C_FIELD(this, f32 *, 0x50)), (float)(M2C_FIELD(this, f32 *, 0x54)));
    PSMTXConcat((const Mtx)(&sp20), (const Mtx)((s32) &unksp50), (Mtx)((s32) &unksp50));
    PSMTXTransApply((const Mtx)((s32) &unksp50), (Mtx)((s32) &unksp50), (float)(M2C_FIELD(this, f32 *, 0x30)), (float)(M2C_FIELD(this, f32 *, 0x34)), (float)(M2C_FIELD(this, f32 *, 0x38)));
    ((GSgfxMatrixStack*)(M2C_FIELD(g_current_layer, GSgfxMatrixStack **, 0x19A0)))->pushMult((GSmtx*)(&unksp50));
    temp_r0 = temp_r31 & 7;
    switch (temp_r0) {
    case 0:
        ((GSgfxLayer*)(g_current_layer))->drawCube();
        break;
    case 1:
        ((GSgfxLayer*)(g_current_layer))->drawCylinder(M2C_FIELD(p0, u8 *, 0x59));
        break;
    case 2:
        ((GSgfxLayer*)(g_current_layer))->drawDodecaedron();
        break;
    case 3:
        ((GSgfxLayer*)(g_current_layer))->drawIcosahedron();
        break;
    case 4:
        ((GSgfxLayer*)(g_current_layer))->drawOctahedron();
        break;
    case 7:
        ((GSgfxLayer*)(g_current_layer))->drawTorus(M2C_FIELD(p0, f32 *, 0x54), M2C_FIELD(p0, u8 *, 0x58), M2C_FIELD(p0, u8 *, 0x59));
        break;
    case 6:
        ((GSgfxLayer*)(g_current_layer))->drawSphere(M2C_FIELD(p0, u8 *, 0x59));
        break;
    default:
        ((GSgfxLayer*)(g_current_layer))->drawSphere(M2C_FIELD(p0, u8 *, 0x58), M2C_FIELD(p0, u8 *, 0x59));
        break;
    }
    ((GSgfxMatrixStack*)(M2C_FIELD(g_current_layer, GSgfxMatrixStack **, 0x19A0)))->pop();
}
}

extern "C++" {
u8 peShapeNode::Update(peEmitterNode* p0, _peShape* p1, float p2) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp34;
    s32 sp38;
    s32 sp40;
    s32 sp44;
    s32 spC;
    s32 unksp20;
    s32 unksp30;
    s32 unksp3C;
    s32 unksp54;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    s32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp1C;
    u8 spA;
    u8 sp9;
    u8 sp8;
    Quaternion *temp_r3_6;
    f32 temp_f1_4;
    f32 temp_f31;
    f32 var_f0;
    f32 var_f1;
    f32 var_f1_10;
    f32 var_f1_11;
    f32 var_f1_12;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f1_6;
    f32 var_f1_7;
    f32 var_f1_8;
    f32 var_f1_9;
    f32 var_f2;
    f32 var_f2_2;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;
    peSpline *temp_r3_10;
    peSpline *temp_r3_3;
    peSpline *temp_r3_4;
    peSpline *temp_r3_5;
    peSpline *temp_r3_7;
    peSpline *temp_r3_8;
    peSpline *temp_r3_9;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r0;

    if (((peNode*)((peNode *) this))->Update((peEmitterNode*)(p0), p2) == 0) {
        return 0U;
    }
    temp_r3 = *M2C_FIELD(p0, s32 **, 0xFC);
    temp_f31 = 1.0f - (M2C_FIELD(this, f32 *, 4) / M2C_FIELD(this, f32 *, 0));
    if (temp_r3 & 0x400) {
        sp64 = M2C_FIELD(this, f32 *, 0x14);
        sp68 = M2C_FIELD(this, f32 *, 0x18);
        sp6C = M2C_FIELD(this, f32 *, 0x1C);
        if (temp_r3 & 0x40) {
            PSMTXQuat((Mtx)((s32) &sp8C), (const Quaternion *)((const register Quaternion*)(M2C_FIELD(this, peXform **, 0x20) + 0xC)));
            PSMTXMultVecSR((const Mtx)((s32) &sp8C), (const Vec *)((const register Vec*)((Vec *) &sp64)), (Vec *)((register Vec*)((Vec *) &sp64)));
        }
        var_f2 = (sp64 * sp64) + (sp6C * sp6C);
        if (var_f2 > 0.0f) {
            temp_f1 = __frsqrte(var_f2);
            temp_f1_2 = 0.5 * temp_f1 * -(((f64) var_f2 * (temp_f1 * temp_f1)) - 3.0);
            temp_f1_3 = 0.5 * temp_f1_2 * -(((f64) var_f2 * (temp_f1_2 * temp_f1_2)) - 3.0);
            var_f2 = (f32) ((f64) var_f2 * (0.5 * temp_f1_3 * -(((f64) var_f2 * (temp_f1_3 * temp_f1_3)) - 3.0)));
        } else if (var_f2 < M2C_BITWISE(f32, 0.0)) {
            var_f2 = __float_nan;
        } else {
            sp1C = var_f2;
            temp_r3_2 = M2C_BITWISE(s32, sp1C) & 0x7F800000;
            switch (temp_r3_2) {                    /* irregular */
            case 0x7F800000:
                if (M2C_BITWISE(s32, sp1C) & 0x7FFFFF) {
                    var_r0 = 1;
                } else {
                    var_r0 = 2;
                }
                break;
            case 0x0:
                if (M2C_BITWISE(s32, sp1C) & 0x7FFFFF) {
                    var_r0 = 5;
                } else {
                    var_r0 = 3;
                }
                break;
            default:
                var_r0 = 4;
                break;
            }
            if (var_r0 == 1) {
                var_f2 = __float_nan;
            }
        }
        sp80 = (f32) atan2(-sp68, (f64) var_f2);
        temp_f1_4 = (f32) atan2((f64) sp64, (f64) sp6C);
        sp88 = 0.0f;
        sp84 = temp_f1_4;
        EulerToQuat((Vec*)((Vec *) &sp80), (Quaternion*)(this + 0x68));
    } else if (M2C_FIELD(p1, s32 *, 0) & 0x100) {
        temp_r3_3 = M2C_FIELD(p1, peSpline **, 0x34);
        if ((temp_r3_3 == NULL) || !(M2C_FIELD(temp_r3_3, u8 *, 0) & 3)) {
            var_f1 = 1.0f;
        } else {
            var_f1_2 = M2C_FIELD(temp_r3_3, f32 *, 8) - temp_f31;
            if (var_f1_2 < 0.0f) {
                var_f1_2 = -var_f1_2;
            }
            M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
            if (var_f1_2 == 0.00001f) {
                var_f1 = M2C_FIELD(temp_r3_3, f32 *, 4);
            } else {
                var_f1 = peSplineGetValue((peSpline*)(temp_r3_3), temp_f31);
            }
        }
        sp80 = M2C_FIELD(p1, f32 *, 4) * var_f1;
        temp_r3_4 = M2C_FIELD(p1, peSpline **, 0x38);
        if ((temp_r3_4 == NULL) || !(M2C_FIELD(temp_r3_4, u8 *, 0) & 3)) {
            var_f1_3 = 1.0f;
        } else {
            var_f1_4 = M2C_FIELD(temp_r3_4, f32 *, 8) - temp_f31;
            if (var_f1_4 < 0.0f) {
                var_f1_4 = -var_f1_4;
            }
            M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
            if (var_f1_4 == 0.00001f) {
                var_f1_3 = M2C_FIELD(temp_r3_4, f32 *, 4);
            } else {
                var_f1_3 = peSplineGetValue((peSpline*)(temp_r3_4), temp_f31);
            }
        }
        sp84 = M2C_FIELD(p1, f32 *, 8) * var_f1_3;
        temp_r3_5 = M2C_FIELD(p1, peSpline **, 0x3C);
        if ((temp_r3_5 == NULL) || !(M2C_FIELD(temp_r3_5, u8 *, 0) & 3)) {
            var_f1_5 = 1.0f;
        } else {
            var_f1_6 = M2C_FIELD(temp_r3_5, f32 *, 8) - temp_f31;
            if (var_f1_6 < 0.0f) {
                var_f1_6 = -var_f1_6;
            }
            M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
            if (var_f1_6 == 0.00001f) {
                var_f1_5 = M2C_FIELD(temp_r3_5, f32 *, 4);
            } else {
                var_f1_5 = peSplineGetValue((peSpline*)(temp_r3_5), temp_f31);
            }
        }
        sp88 = M2C_FIELD(p1, f32 *, 0xC) * var_f1_5;
        EulerToQuat((Vec*)((Vec *) &sp80), (Quaternion*)(this + 0x68));
    } else {
        PSVECScale((const register Vec*)(this + 0x8C), (register Vec*)(&unksp30), p2);
        sp80 = unksp30;
        sp84 = sp34;
        sp88 = sp38;
        EulerToQuat((Vec*)((Vec *) &sp80), (Quaternion*)(&unksp54));
        temp_r3_6 = (Quaternion *)(this + 0x68);
        PSQUATMultiply((const register Quaternion*)(temp_r3_6), (const register Quaternion*)(&unksp54), (register Quaternion*)(temp_r3_6));
    }
    temp_r3_7 = M2C_FIELD(p1, peSpline **, 0x40);
    if ((temp_r3_7 == NULL) || !(M2C_FIELD(temp_r3_7, u8 *, 0) & 3)) {
        var_f1_7 = 1.0f;
    } else {
        var_f1_8 = M2C_FIELD(temp_r3_7, f32 *, 8) - temp_f31;
        if (var_f1_8 < 0.0f) {
            var_f1_8 = -var_f1_8;
        }
        M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
        if (var_f1_8 == 0.00001f) {
            var_f1_7 = M2C_FIELD(temp_r3_7, f32 *, 4);
        } else {
            var_f1_7 = peSplineGetValue((peSpline*)(temp_r3_7), temp_f31);
        }
    }
    sp80 = M2C_FIELD(this, f32 *, 0x78) * var_f1_7;
    temp_r3_8 = M2C_FIELD(p1, peSpline **, 0x44);
    if ((temp_r3_8 == NULL) || !(M2C_FIELD(temp_r3_8, u8 *, 0) & 3)) {
        var_f1_9 = 1.0f;
    } else {
        var_f1_10 = M2C_FIELD(temp_r3_8, f32 *, 8) - temp_f31;
        if (var_f1_10 < 0.0f) {
            var_f1_10 = -var_f1_10;
        }
        M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
        if (var_f1_10 == 0.00001f) {
            var_f1_9 = M2C_FIELD(temp_r3_8, f32 *, 4);
        } else {
            var_f1_9 = peSplineGetValue((peSpline*)(temp_r3_8), temp_f31);
        }
    }
    sp84 = M2C_FIELD(this, f32 *, 0x7C) * var_f1_9;
    temp_r3_9 = M2C_FIELD(p1, peSpline **, 0x48);
    if ((temp_r3_9 == NULL) || !(M2C_FIELD(temp_r3_9, u8 *, 0) & 3)) {
        var_f2_2 = 1.0f;
    } else {
        var_f1_11 = M2C_FIELD(temp_r3_9, f32 *, 8) - temp_f31;
        if (var_f1_11 < 0.0f) {
            var_f1_11 = -var_f1_11;
        }
        M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
        if (var_f1_11 == 0.00001f) {
            var_f2_2 = M2C_FIELD(temp_r3_9, f32 *, 4);
        } else {
            var_f2_2 = peSplineGetValue((peSpline*)(temp_r3_9), temp_f31);
        }
    }
    sp88 = M2C_FIELD(this, f32 *, 0x80) * var_f2_2;
    peColorSplineGetValue((u8*)(this + 0x98), (peColorSpline*)(M2C_FIELD(p1, peColorSpline **, 0x4C)), temp_f31);
    spA = M2C_FIELD(this, u8 *, 0x98);
    M2C_FIELD(this, u8 *, 0x98) = sp14;
    sp9 = M2C_FIELD(this, u8 *, 0x99);
    M2C_FIELD(this, u8 *, 0x99) = sp10;
    sp8 = M2C_FIELD(this, u8 *, 0x9A);
    M2C_FIELD(this, u8 *, 0x9A) = spC;
    temp_r3_10 = M2C_FIELD(p1, peSpline **, 0x50);
    if ((temp_r3_10 == NULL) || !(M2C_FIELD(temp_r3_10, u8 *, 0) & 3)) {

    } else {
        var_f1_12 = M2C_FIELD(temp_r3_10, f32 *, 8) - temp_f31;
        if (var_f1_12 < 0.0f) {
            var_f1_12 = -var_f1_12;
        }
        M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
        if (var_f1_12 == 0.00001f) {

        } else {
            peSplineGetValue((peSpline*)(temp_r3_10), temp_f31);
        }
    }
    M2C_FIELD(this, u8 *, 0x9B) = sp18;
    if (M2C_FIELD(this, s32 *, 0x88) & 1) {
        var_f0 = -M2C_FIELD(this, f32 *, 0x68);
    } else {
        var_f0 = M2C_FIELD(this, f32 *, 0x68);
    }
    sp70 = var_f0;
    if (M2C_FIELD(this, s32 *, 0x88) & 2) {
        sp74 = -M2C_FIELD(this, f32 *, 0x6C);
    } else {
        sp74 = M2C_FIELD(this, f32 *, 0x6C);
    }
    if (M2C_FIELD(this, s32 *, 0x88) & 4) {
        sp78 = -M2C_FIELD(this, f32 *, 0x70);
    } else {
        sp78 = M2C_FIELD(this, f32 *, 0x70);
    }
    sp7C = M2C_FIELD(this, f32 *, 0x74);
    spBC = M2C_FIELD(this, f32 *, 8);
    spC0 = M2C_FIELD(this, f32 *, 0xC);
    spC4 = M2C_FIELD(this, f32 *, 0x10);
    PSQUATMultiply((const register Quaternion*)(this + 0x58), (const register Quaternion*)((Quaternion *) &sp70), (register Quaternion*)(&unksp20));
    spC8 = unksp20;
    spCC = sp24;
    spD0 = sp28;
    spD4 = sp2C;
    spD8 = sp80;
    spDC = sp84;
    spE0 = sp88;
    peNodeTransformsConcat((peXform*)(this + 0x30), (peXform*)(M2C_FIELD(this, peXform **, 0x20)), (peXform*)((peXform *) &spBC), 0U);
    PSVECSubtract((const register Vec*)(this + 0x30), (const register Vec*)(&g_CameraPosition), (register Vec*)(&unksp3C));
    sp48 = unksp3C;
    sp4C = sp40;
    sp50 = sp44;
    M2C_FIELD(this, f32 *, 0x84) = PSVECDotProduct((const register Vec*)(&g_CameraLookDir), (const register Vec*)((Vec *) &sp48));
    return 1U;
}
}

extern "C++" {
#pragma optimize_for_size on
void peShapeNode::Start(peEmitterNode* p0, _peShape* p1, _EmitParams* p2) {
    f32 sp10;
    f32 spC;
    f32 unksp8;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    Vec *temp_r3;
    s32 temp_r31;

    temp_r31 = M2C_FIELD(p1, s32 *, 0);
    ((peNode*)((peNode *) this))->Start((peEmitterNode*)(p0), (_EmitParams*)(p2));
    M2C_FIELD(this, s32 *, 0x88) = 0;
    PSVECScale((const register Vec*)(((u8*)(p1) + 0x28)), (register Vec*)(&unksp8), HSD_Randf());
    temp_r3 = (Vec *)(this + 0x78);
    M2C_FIELD(this, f32 *, 0x78) = unksp8;
    M2C_FIELD(this, f32 *, 0x7C) = spC;
    M2C_FIELD(this, f32 *, 0x80) = sp10;
    PSVECAdd((const register Vec*)(temp_r3), (const register Vec*)(((u8*)(p1) + 0x1C)), (register Vec*)(temp_r3));
    M2C_FIELD(this, f32 *, 0x58) = 0.0f;
    M2C_FIELD(this, f32 *, 0x5C) = 0.0f;
    M2C_FIELD(this, f32 *, 0x60) = 0.0f;
    M2C_FIELD(this, f32 *, 0x64) = 1.0f;
    M2C_FIELD(this, f32 *, 0x30) = 0.0f;
    M2C_FIELD(this, f32 *, 0x34) = 0.0f;
    M2C_FIELD(this, f32 *, 0x38) = 0.0f;
    M2C_FIELD(this, f32 *, 0x3C) = 0.0f;
    M2C_FIELD(this, f32 *, 0x40) = 0.0f;
    M2C_FIELD(this, f32 *, 0x44) = 0.0f;
    M2C_FIELD(this, f32 *, 0x48) = 1.0f;
    M2C_FIELD(this, f32 *, 0x4C) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 0);
    M2C_FIELD(this, f32 *, 0x50) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 4);
    M2C_FIELD(this, f32 *, 0x54) = (f32) M2C_FIELD(&unitScaleVector, f32 *, 8);
    if (!(*M2C_FIELD(p0, s32 **, 0xFC) & 0x400)) {
        EulerToQuat((Vec*)(((u8*)(p1) + 4)), (Quaternion*)(this + 0x68));
        if (temp_r31 & 0x1C7000) {
            if (temp_r31 & 0x1000) {
                sp14 = 6.2831855f * HSD_Randf();
            } else {
                sp14 = 0.0f;
            }
            if (temp_r31 & 0x2000) {
                sp18 = 6.2831855f * HSD_Randf();
            } else {
                sp18 = 0.0f;
            }
            if (temp_r31 & 0x4000) {
                sp1C = 6.2831855f * HSD_Randf();
            } else {
                sp1C = 0.0f;
            }
            if ((temp_r31 & 0x40000) && (HSD_Randf() < 0.5f)) {
                M2C_FIELD(this, s32 *, 0x88) = (s32) (M2C_FIELD(this, s32 *, 0x88) | 1);
            }
            if ((temp_r31 & 0x80000) && (HSD_Randf() < 0.5f)) {
                M2C_FIELD(this, s32 *, 0x88) = (s32) (M2C_FIELD(this, s32 *, 0x88) | 2);
            }
            if ((temp_r31 & 0x100000) && (HSD_Randf() < 0.5f)) {
                M2C_FIELD(this, s32 *, 0x88) = (s32) (M2C_FIELD(this, s32 *, 0x88) | 4);
            }
            EulerToQuat((Vec*)((Vec *) &sp14), (Quaternion*)(this + 0x58));
        }
    }
    M2C_FIELD(this, f32 *, 0x8C) = (f32) M2C_FIELD(p1, f32 *, 0x10);
    M2C_FIELD(this, f32 *, 0x90) = (f32) M2C_FIELD(p1, f32 *, 0x14);
    M2C_FIELD(this, f32 *, 0x94) = (f32) M2C_FIELD(p1, f32 *, 0x18);
    if (temp_r31 & 0x8000) {
        M2C_FIELD(this, f32 *, 0x8C) = (f32) (M2C_FIELD(this, f32 *, 0x8C) * HSD_Randf());
    }
    if (temp_r31 & 0x10000) {
        M2C_FIELD(this, f32 *, 0x90) = (f32) (M2C_FIELD(this, f32 *, 0x90) * HSD_Randf());
    }
    if (temp_r31 & 0x20000) {
        M2C_FIELD(this, f32 *, 0x94) = (f32) (M2C_FIELD(this, f32 *, 0x94) * HSD_Randf());
    }
}
#pragma optimize_for_size reset
}
}
}
