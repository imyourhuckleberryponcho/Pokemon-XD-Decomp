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
struct GSbound;
struct GSgfxDL;
struct GSgfxLayer;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxPrimType { GSgfxPrimType_draft_dummy };
struct GSgfxVF;
enum Mtx { Mtx_draft_dummy };
struct Quaternion;
struct Vec;
struct _EmitParams;
struct _peParticleStrip;
struct peColorSpline;
struct peContainer;
struct peEmitterNode;
struct peNode;
struct peParticleStripContainer;
struct peParticleStripNode;
struct peRenderContainer;
struct peSpline;

extern "C++" {
// ---- draft declarations ----
struct GSbound {
    u8 _draft[1];
};
struct GSgfxDL {
    u8 _draft[1];
};
struct GSgfxLayer {
    u8 _draft[1];
    s32 dlDraw(GSgfxDL*);
};
struct GSgfxVF {
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
struct _peParticleStrip {
    u8 _draft[1];
};
struct peColorSpline {
    u8 _draft[1];
};
struct peContainer {
    u8 _draft[1];
    s32 RemoveNode(peNode*);
    s32 SetLayerVisibility(GSgfxLayerID, bool);
    u16 CreateNodes(unsigned short);
    s32 RemoveAll();
};
struct peEmitterNode {
    u8 _draft[1];
};
struct peNode {
    u8 _draft[1];
    bool Update(peEmitterNode*, float);
    void Start(peEmitterNode*, _EmitParams*);
};
struct peParticleStripContainer {
    u8 _draft[1];
    void Stop();
    peParticleStripContainer(peEmitterNode*, _peParticleStrip*, unsigned short);
    void Start();
    void Update(float);
    void RearrangeIndices();
    void Render();
    ~peParticleStripContainer();
    static u16 Emit(unsigned short);
};
struct peParticleStripNode {
    u8 _draft[1];
    void UpdateRenderData(peEmitterNode*, _peParticleStrip*, char*, float);
};
struct peRenderContainer {
    u8 _draft[1];
    s32 ResetSwap();
    s32 InitSwap();
    ~peRenderContainer();
    s32 ResolveMultipleSwap();
    peRenderContainer(peEmitterNode*, unsigned long, unsigned short, GSgfxVF*, GSgfxPrimType, unsigned char, unsigned char, bool);
    s32 MarkForSwap();
};
struct peSpline {
    u8 _draft[1];
};

extern "C" {
void GSboundAddPoint(GSbound* bound, f32 x, f32 y, f32 z);
void GSgfxVFSetArray(GSgfxVF* vf, s32, s32, void*, s32, s32);
f32 HSD_Randf(void);
asm void PSMTXMultVecSR(const register Mtx m, const register Vec* src, register Vec* dst);
void PSMTXQuat(register Mtx m, const register Quaternion* q);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double fmod(double x, double y);
s32 particleEngineSetupBlendMode(s32, void*);
s32 particleEngineSetupTevStages(s32, u32, u32);
s32 particleEngineSetupTexture(s32, s32*, s32, s32, s32, s32);
void peColorSplineGetValue(u8* out, peColorSpline* s, f32 t);
f32 peSplineGetValue(peSpline* s, f32 t);
extern GSbound* g_currentBound;
extern GSgfxLayer* g_current_layer;
extern _EmitParams* g_emitParams;
extern GSgfxVF g_ext_vertex_format;
extern s32 g_particle_debug_stats;
extern s32 g_render_pass;
extern GSgfxVF g_vertex_format;
extern s32 this_;
}
s32 __vt__24peParticleStripContainer;
#pragma optimize_for_size on
void peParticleStripContainer::RearrangeIndices() {
    s16 spC;
    s16 spA;
    s16 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f1;
    f32 var_f2;
    s16 var_r7;
    s16 var_r8;
    s32 temp_r28;
    s32 temp_r28_2;
    s32 temp_r29_2;
    s32 temp_r29_3;
    s32 var_r26;
    s32 temp_r29;
    u16 temp_r5;
    u16 var_r24_2;
    u32 temp_r12;
    u32 temp_r6;
    u8 temp_r9;
    u8 var_r0;
    s32 var_r24;
    u8 var_r4;
    u8 *temp_r30;
    u8 *temp_r9_2;
    u8 *var_r26_2;
    u8 *var_r6;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) != 0) {
        var_r7 = 0;
        temp_r5 = M2C_FIELD(this, u16 *, 0x14);
        var_r8 = 0;
        temp_r6 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), u32 *, 0);
        temp_r12 = (temp_r6 >> 0x12U) & 1;
        if (temp_r5 >= 2U) {
            if (temp_r6 & 0x10000) {
                spC = temp_r5 - 1;
                var_f1 = 1.0f / M2C_ERROR(/* psq_l unimplemented */);
            } else {
                var_f1 = M2C_FIELD(M2C_FIELD(M2C_FIELD(this, u8 **, 0), u8 **, 0xFC), f32 *, 8);
            }
            if (temp_r12 != 0) {
                var_r4 = 0xC;
                var_r24 = 8;
                var_r0 = 0x30;
            } else {
                var_r4 = 0xB;
                var_r24 = 6;
                var_r0 = 0x2C;
            }
            temp_r9 = M2C_FIELD(this, u8 *, 0x21);
            var_r6 = M2C_FIELD(this, u8 **, 0x10);
            temp_r30 = (unsigned char *)(this + ((temp_r9 * 0x10) + 0x28));
            while (var_r6 != NULL) {
                M2C_FIELD(var_r6, s16 *, 0x32) = var_r7;
                temp_r29 = M2C_FIELD(var_r6, u16 *, 0x30) * var_r4;
                temp_r9_2 = (unsigned char *)(M2C_FIELD((this + (temp_r9 * 4)), s32 *, 0x48) + (M2C_FIELD(var_r6, u16 *, 0x30) * var_r0));
                if (M2C_FIELD(temp_r30, u16 *, 0) & 1) {
                    var_r26 = M2C_FIELD(temp_r30, s32 *, 4) + 3;
                } else {
                    var_r26 = 0;
                }
                var_r24_2 = 0;
                var_r26_2 = (unsigned char *)(var_r26 + ((var_r7 * 2) & 0x1FFFE));
                if (temp_r12 != 0) {
                    while (var_r24_2 < 2U) {
                        temp_r29_2 = (var_r24_2 * 2) & 0x1FFFE;
                        temp_r28 = var_r24_2 * 3;
                        var_r24_2 += 1;
                        M2C_FIELD(var_r26_2, s16 *, 0) = (s16) (temp_r29 + temp_r28);
                        M2C_FIELD(var_r26_2, u16 *, 2) = temp_r29;
                        M2C_FIELD(var_r26_2, u16 *, 4) = temp_r29;
                        M2C_FIELD(var_r26_2, s16 *, 6) = (s16) (temp_r29 + temp_r29_2);
                        var_r26_2 += 8;
                    }
                } else {
                    while (var_r24_2 < 2U) {
                        temp_r29_3 = (var_r24_2 * 2) & 0x1FFFE;
                        temp_r28_2 = var_r24_2 * 3;
                        var_r24_2 += 1;
                        M2C_FIELD(var_r26_2, s16 *, 0) = (s16) (temp_r29 + temp_r28_2);
                        M2C_FIELD(var_r26_2, u16 *, 2) = temp_r29;
                        M2C_FIELD(var_r26_2, s16 *, 4) = (s16) (temp_r29 + temp_r29_3);
                        var_r26_2 += 6;
                    }
                }
                if ((u32) ((temp_r6 >> 0x11U) & 1) != 0) {
                    spA = (M2C_FIELD(this, u16 *, 0x14) - var_r8) - 1;
                    var_f2 = M2C_ERROR(/* psq_l unimplemented */);
                } else {
                    sp8 = var_r8;
                    var_f2 = M2C_ERROR(/* psq_l unimplemented */);
                }
                if ((u32) ((temp_r6 >> 0xFU) & 1) != 0) {
                    temp_f0 = -((var_f2 * var_f1) - 1.0f);
                    M2C_FIELD(temp_r9_2, f32 *, 0x24) = temp_f0;
                    M2C_FIELD(temp_r9_2, f32 *, 0x1C) = temp_f0;
                } else {
                    temp_f0_2 = var_f2 * var_f1;
                    M2C_FIELD(temp_r9_2, f32 *, 0x24) = temp_f0_2;
                    M2C_FIELD(temp_r9_2, f32 *, 0x1C) = temp_f0_2;
                }
                var_r7 += var_r24;
                var_r8 += 1;
                M2C_FIELD(temp_r9_2, f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), f32 *, 0x14);
                M2C_FIELD(temp_r9_2, f32 *, 0x28) = (f32) M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), f32 *, 0x18);
                var_r6 = M2C_FIELD(var_r6, u8 **, 0x28);
            }
            M2C_FIELD(temp_r30, u16 *, 0) = (u16) (M2C_FIELD(temp_r30, u16 *, 0) | 2);
        }
    }
}
#pragma optimize_for_size reset
}

extern "C++" {
void peParticleStripContainer::Stop() {
    s16 *var_r6_2;
    s32 temp_cr0_eq;
    s32 var_r6;
    s32 var_r4;
    u32 temp_r30;
    u8 *temp_r7;
    u8 *var_r8;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) != 0) {
        M2C_FIELD(M2C_FIELD(this, u8 **, 0x1C), s32 (**)(), 0x10)();
        M2C_FIELD(this, u8 *, 0x19) = 0U;
        temp_r30 = *M2C_FIELD(this, u32 **, 0x54);
        if (temp_r30 & 0x400000) {
            ((peContainer*)((peContainer *)1))->SetLayerVisibility((GSgfxLayerID)(0), M2C_ERROR(/* Read from unset register $r5 */));
        }
        if (temp_r30 & 0x800000) {
            ((peContainer*)((peContainer *)3))->SetLayerVisibility((GSgfxLayerID)(0), M2C_ERROR(/* Read from unset register $r5 */));
        }
        if (temp_r30 & 0x01000000) {
            ((peContainer*)((peContainer *)5))->SetLayerVisibility((GSgfxLayerID)(0), M2C_ERROR(/* Read from unset register $r5 */));
        }
        var_r8 = M2C_FIELD(this, u8 **, 0x10);
        while (var_r8 != NULL) {
            temp_r7 = (unsigned char *)(this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28));
            if (M2C_FIELD(temp_r7, u16 *, 0) & 1) {
                var_r6 = M2C_FIELD(temp_r7, s32 *, 4) + 3;
            } else {
                var_r6 = 0;
            }
            var_r4 = 2;
            var_r6_2 = (short *)(var_r6 + (M2C_FIELD(var_r8, u16 *, 0x32) * 2));
loop_14:
            temp_cr0_eq = var_r4 == 0;
            var_r4 -= 1;
            if (temp_cr0_eq == 0) {
                M2C_FIELD(var_r6_2, u16 *, 0) = 0xFFFF;
                M2C_FIELD(var_r6_2, u16 *, 2) = 0xFFFF;
                M2C_FIELD(var_r6_2, u16 *, 4) = 0xFFFF;
                var_r6_2 += 6;
                if ((u32) (((u32) *M2C_FIELD(this, u32 **, 0x54) >> 0x12U) & 1) != 0) {
                    *var_r6_2 = 0xFFFF;
                    var_r6_2 += 2;
                }
                goto loop_14;
            }
            M2C_FIELD(temp_r7, u16 *, 0) = (u16) (M2C_FIELD(temp_r7, u16 *, 0) | 2);
            var_r8 = M2C_FIELD(var_r8, u8 **, 0x28);
        }
        ((peContainer*)((peContainer *) this))->RemoveAll();
        ((peRenderContainer*)((peRenderContainer *) this))->ResetSwap();
    }
}
}

extern "C++" {
void peParticleStripContainer::Render() {
    s32 sp10;
    s32 sp14;
    u8 sp1F;
    u8 sp1E;
    u8 sp1D;
    u8 sp1C;
    s32 sp18;
    s16 spC;
    s16 spA;
    u16 sp8;
    GSgfxVF *var_r28;
    f32 temp_f30;
    f32 var_f1;
    f32 var_f29;
    s32 *temp_r29_2;
    s32 temp_cr0_eq;
    s32 temp_r0;
    s32 var_r7;
    s32 var_r7_2;
    s32 var_r7_3;
    s32 var_r8;
    s32 var_r8_2;
    s32 var_r8_3;
    u32 temp_r26;
    u32 temp_r30;
    u32 temp_r31;
    u32 temp_r4;
    s32 temp_r0_2;
    u8 var_r0;
    u8 var_r28_2;
    u8 *temp_r29;
    u8 *temp_r4_2;

    temp_cr0_eq = (u8) M2C_FIELD(this, u8 *, 0x19) == 0;
    if (temp_cr0_eq == 0) {
        if (temp_cr0_eq != 0) {
            var_r0 = 0;
        } else {
            temp_r4 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), u32 *, 0);
            if ((u16) M2C_FIELD(this, u16 *, 0x14) < 2U) {
                var_r0 = 0;
            } else if ((s32) g_render_pass != 1) {
                var_r0 = 0;
            } else {
                temp_r0 = M2C_FIELD(g_current_layer, s32 *, 0x28);
                switch (temp_r0) {                  /* irregular */
                case 0:
                    if (temp_r4 & 0x100000) {
                        var_r0 = 1;
                    } else {
block_31:
                        var_r0 = 0;
                    }
                    break;
                case 2:
                    if (temp_r4 & 0x200000) {
                        var_r0 = 1;
                    } else if (!(temp_r4 & 0x01F00040)) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 4:
                    if (temp_r4 & 0x40) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 1:
                    if (temp_r4 & 0x400000) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 3:
                    if (temp_r4 & 0x800000) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 5:
                    if (temp_r4 & 0x01000000) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                default:
                    var_r0 = 0;
                    break;
                }
            }
        }
        if (var_r0 != 0) {
            ((peRenderContainer*)((peRenderContainer *) this))->ResolveMultipleSwap();
            temp_r31 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), u32 *, 0);
            M2C_FIELD(g_current_layer, s32 *, 0xD8C) = 0;
            temp_r30 = (temp_r31 >> 0x12U) & 1;
            M2C_FIELD(g_current_layer, s32 *, 0x16B8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16B8) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1770) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1770) | 2);
            M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 2);
            particleEngineSetupBlendMode(temp_r31 & 7, g_current_layer);
            temp_r0_2 = M2C_FIELD(this, u8 *, 0x21);
            temp_r4_2 = (unsigned char *)(this + ((temp_r0_2 * 0x10) + 0x28));
            temp_r29 = M2C_FIELD((this + (temp_r0_2 * 4)), u8 **, 0x48);
            if (M2C_FIELD(temp_r4_2, u16 *, 0) & 1) {
                var_r28 = M2C_FIELD(temp_r4_2, GSgfxVF **, 0xC);
            } else {
                var_r28 = NULL;
            }
            if (temp_r30 != 0) {
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 9, 3, (void*)(temp_r29), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xB, 3, (void*)(temp_r29 + 0x18), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xC, 3, (void*)(temp_r29 + 0x2C), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xD, 3, (void*)(temp_r29 + 0x1C), 4, M2C_FIELD(this, s32 *, 0x24));
            } else {
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 9, 3, (void*)(temp_r29), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xB, 3, (void*)(temp_r29 + 0x18), 4, M2C_FIELD(this, s32 *, 0x24));
                GSgfxVFSetArray((GSgfxVF*)(var_r28), 0xD, 3, (void*)(temp_r29 + 0x1C), 4, M2C_FIELD(this, s32 *, 0x24));
            }
            if (temp_r31 & 0x400) {
                var_r28_2 = M2C_FIELD(this, u8 *, 0x5C);
                temp_r29_2 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), s32 **, 0x1C);
                if (temp_r31 & 0x1000) {
                    spC = (s16) *temp_r29_2;
                    var_f29 = M2C_ERROR(/* psq_l unimplemented */);
                    temp_r26 = (temp_r31 >> 0xDU) & 1;
                    particleEngineSetupTevStages(0, temp_r30, temp_r26);
                    if (temp_r26 != 0) {
                        var_f29 -= 1.0f;
                    }
                    if (temp_r31 & 0x04000000) {
                        var_f1 = (var_f29 * (M2C_FIELD(M2C_FIELD(M2C_FIELD(this, u8 **, 0), u8 **, 0xFC), f32 *, 0x28) - M2C_FIELD(this, f32 *, 0x58))) / M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), f32 *, 4);
                    } else {
                        var_f1 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), f32 *, 4) * (var_f29 * (1.0f - (M2C_FIELD(this, f32 *, 0x58) / M2C_FIELD(M2C_FIELD(M2C_FIELD(this, u8 **, 0), u8 **, 0xFC), f32 *, 0x28))));
                    }
                    spA = (s16) var_r28_2;
                    temp_f30 = (f32) fmod((f64) (var_f1 + M2C_ERROR(/* psq_l unimplemented */)), (f64) var_f29);
                    var_r28_2 = (u8) (u16) (sp14 % (u16) *temp_r29_2);
                    if (temp_r26 != 0) {
                        sp8 = (u16) var_r28_2;
                        var_r8 = 0;
                        sp1F = sp10;
                        sp1E = sp10;
                        sp1D = sp10;
                        sp1C = sp10;
                        M2C_FIELD(g_current_layer, s32 *, 0x14F4) = (s32) sp1C;
                        sp18 = (s32) sp1C;
                        M2C_FIELD(g_current_layer, s32 *, 0x16F8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16F8) | 1);
                        M2C_FIELD(g_current_layer, s32 *, 0x16A8) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x16A8) | 0x10);
                        M2C_FIELD(g_current_layer, s32 *, 0x17B0) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x17B0) | 1);
                        M2C_FIELD(g_current_layer, s32 *, 0x1760) = (s32) (M2C_FIELD(g_current_layer, s32 *, 0x1760) | 0x10);
                        if (temp_r31 & 0x20) {
                            var_r8 = 2;
                        }
                        var_r7 = 0;
                        if (temp_r31 & 0x10) {
                            var_r7 = 2;
                        }
                        particleEngineSetupTexture(1, M2C_FIELD((temp_r29_2 + ((var_r28_2 * 4) & 0x3FFFC)), s32 **, 8), 0, (temp_r31 >> 8U) & 3, var_r7, var_r8);
                    }
                } else {
                    particleEngineSetupTevStages(0, temp_r30, 0U);
                }
                var_r8_2 = 0;
                if (temp_r31 & 0x20) {
                    var_r8_2 = 2;
                }
                var_r7_2 = 0;
                if (temp_r31 & 0x10) {
                    var_r7_2 = 2;
                }
                particleEngineSetupTexture(0, M2C_FIELD((temp_r29_2 + ((var_r28_2 * 4) & 0x3FFFC)), s32 **, 4), 0, (temp_r31 >> 8U) & 3, var_r7_2, var_r8_2);
            } else {
                particleEngineSetupTevStages(0, temp_r30, 0U);
                var_r8_3 = 0;
                if (temp_r31 & 0x20) {
                    var_r8_3 = 2;
                }
                var_r7_3 = 0;
                if (temp_r31 & 0x10) {
                    var_r7_3 = 2;
                }
                particleEngineSetupTexture(0, M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), s32 **, 0x1C), 0, (temp_r31 >> 8U) & 3, var_r7_3, var_r8_3);
            }
            ((GSgfxLayer*)(g_current_layer))->dlDraw((GSgfxDL*)(this + ((M2C_FIELD(this, u8 *, 0x21) * 0x10) + 0x28)));
            ((peRenderContainer*)((peRenderContainer *) this))->MarkForSwap();
        }
    }
}
}

extern "C++" {
void peParticleStripContainer::Update(float p0) { }
extern "C++" {
u16 peParticleStripContainer::Emit(unsigned short p0) { return 0; }
extern "C++" {
void peParticleStripContainer::Start() {
    s32 spC;
    s16 sp8;
    s32 temp_r31;

    if ((u8) M2C_FIELD(this, u8 *, 0x19) == 0) {
        M2C_FIELD(this, u8 *, 0x19) = 1U;
        temp_r31 = M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), s32 *, 0);
        ((peRenderContainer*)((peRenderContainer *) this))->InitSwap();
        if (temp_r31 & 0x400000) {
            ((peContainer*)((peContainer *)1))->SetLayerVisibility((GSgfxLayerID)(1), M2C_ERROR(/* Read from unset register $r5 */));
        }
        if (temp_r31 & 0x800000) {
            ((peContainer*)((peContainer *)3))->SetLayerVisibility((GSgfxLayerID)(1), M2C_ERROR(/* Read from unset register $r5 */));
        }
        if (temp_r31 & 0x01000000) {
            ((peContainer*)((peContainer *)5))->SetLayerVisibility((GSgfxLayerID)(1), M2C_ERROR(/* Read from unset register $r5 */));
        }
        if ((u32) (temp_r31 & 0xC00) == 0xC00) {
            sp8 = (s16) *M2C_FIELD(M2C_FIELD(this, u8 **, 0x54), s32 **, 0x1C);
            HSD_Randf();
            M2C_FIELD(this, u8 *, 0x5C) = spC;
        } else {
            M2C_FIELD(this, u8 *, 0x5C) = 0U;
        }
        M2C_FIELD(this, f32 *, 0x58) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(this, u8 **, 0), u8 **, 0xFC), f32 *, 0x28);
    }
}
}

extern "C++" {
peParticleStripContainer::~peParticleStripContainer() {
    if (this != NULL) {
        M2C_FIELD(this, s32 **, 0x1C) = &__vt__24peParticleStripContainer;
        M2C_FIELD(&g_particle_debug_stats, s32 *, 4) = (s32) (M2C_FIELD(&g_particle_debug_stats, s32 *, 4) - 0x60);
        M2C_FIELD(&g_particle_debug_stats, s32 *, 0x14) = (s32) (M2C_FIELD(&g_particle_debug_stats, s32 *, 0x14) - 0x60);
        ((peRenderContainer*)((peRenderContainer *) this))->~peRenderContainer();
        if ((s16) M2C_ERROR(/* Read from unset register $r4 */) > 0) {
            operator delete((void*)(this));
        }
    }
    return;
}
}

extern "C++" {
peParticleStripContainer::peParticleStripContainer(peEmitterNode* p0, _peParticleStrip* p1, unsigned short p2) {
    s32 sp8;
    GSgfxVF *var_r7;
    s16 var_r4;
    u32 temp_r0;
    u32 temp_r5;
    u8 var_r8;
    u8 *var_r3;

    var_r8 = 0x2C;
    temp_r0 = (*(s32*)(p1));
    temp_r5 = temp_r0 & 0x40000;
    if (temp_r5 != 0) {
        var_r8 = 0x30;
    }
    sp8 = (temp_r0 >> 0x13U) & 1;
    var_r7 = &g_vertex_format;
    if (temp_r5 != 0) {
        var_r7 = &g_ext_vertex_format;
    }
    ((peRenderContainer*)((peRenderContainer *) this))->peRenderContainer((peEmitterNode*)(p0), 0x40U, p2, (GSgfxVF*)(var_r7), (GSgfxPrimType)(0x98), 2U, var_r8, M2C_ERROR(/* Unable to find stack arg 0x0 in block */));
    var_r4 = 0;
    M2C_FIELD(this, _peParticleStrip **, 0x54) = p1;
    M2C_FIELD(this, s32 **, 0x1C) = &__vt__24peParticleStripContainer;
    var_r3 = M2C_FIELD(this, u8 **, 0xC);
    M2C_FIELD(this, s8 *, 0x5C) = 0xFF;
    while (var_r3 != NULL) {
        M2C_FIELD(var_r3, s16 *, 0x30) = var_r4;
        M2C_FIELD(var_r3, s16 *, 0x32) = var_r4;
        var_r4 += 1;
        var_r3 = M2C_FIELD(var_r3, u8 **, 0x28);
    }
    M2C_FIELD(&g_particle_debug_stats, s32 *, 4) = (s32) (M2C_FIELD(&g_particle_debug_stats, s32 *, 4) + 0x60);
    M2C_FIELD(&g_particle_debug_stats, s32 *, 0x14) = (s32) (M2C_FIELD(&g_particle_debug_stats, s32 *, 0x14) + 0x60);
    return;
}
}

extern "C++" {
void peParticleStripNode::UpdateRenderData(peEmitterNode* p0, _peParticleStrip* p1, char* p2, float p3) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp24;
    s32 sp28;
    s32 spC;
    f32 unksp20;
    s32 sp80;
    s32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    u8 sp1F;
    u8 sp1E;
    u8 sp1D;
    u8 sp1C;
    u8 spA;
    u8 sp9;
    u8 sp8;
    Vec *temp_r5;
    Vec *temp_r5_2;
    f32 var_f1;
    peSpline *temp_r3;
    u32 temp_r27;
    u32 temp_r30;
    u8 *var_r31;

    temp_r5 = M2C_FIELD(this, Vec **, 0x20);
    temp_r27 = M2C_FIELD(p1, u32 *, 0);
    temp_r30 = (temp_r27 >> 0x12U) & 1;
    sp48 = M2C_FIELD(this, f32 *, 0xC) * M2C_FIELD(temp_r5, f32 *, 0x20);
    sp4C = M2C_FIELD(this, f32 *, 0x10) * M2C_FIELD(temp_r5, f32 *, 0x24);
    sp44 = M2C_FIELD(this, f32 *, 8) * M2C_FIELD(temp_r5, f32 *, 0x1C);
    PSMTXQuat((Mtx)((s32) &sp80), (const Quaternion *)((const register Quaternion*)(((u8*)(temp_r5) + 0xC))));
    PSMTXMultVecSR((const Mtx)((s32) &sp80), (const Vec *)((const register Vec*)((Vec *) &sp44)), (Vec *)((register Vec*)((Vec *) &sp44)));
    PSVECAdd((const register Vec*)((Vec *) &sp44), (const register Vec*)(M2C_FIELD(this, Vec **, 0x20)), (register Vec*)((Vec *) &sp44));
    if (temp_r30 != 0) {
        var_r31 = (unsigned char *)(p2 + (M2C_FIELD(this, u16 *, 0x30) * 0x30));
    } else {
        var_r31 = (unsigned char *)(p2 + (M2C_FIELD(this, u16 *, 0x30) * 0x2C));
    }
    temp_r5_2 = M2C_FIELD(this, Vec **, 0x20);
    sp3C = M2C_FIELD(this, f32 *, 0x38) * M2C_FIELD(temp_r5_2, f32 *, 0x20);
    sp40 = M2C_FIELD(this, f32 *, 0x3C) * M2C_FIELD(temp_r5_2, f32 *, 0x24);
    sp38 = M2C_FIELD(this, f32 *, 0x34) * M2C_FIELD(temp_r5_2, f32 *, 0x1C);
    PSMTXQuat((Mtx)((s32) &sp50), (const Quaternion *)((const register Quaternion*)(((u8*)(temp_r5_2) + 0xC))));
    PSMTXMultVecSR((const Mtx)((s32) &sp50), (const Vec *)((const register Vec*)((Vec *) &sp38)), (Vec *)((register Vec*)((Vec *) &sp38)));
    if (temp_r27 & 0x4000) {
        PSVECScale((const register Vec*)((Vec *) &sp38), (register Vec*)(&unksp20), 0.5f);
        sp2C = unksp20;
        sp30 = sp24;
        sp34 = sp28;
        PSVECSubtract((const register Vec*)((Vec *) &sp44), (const register Vec*)((Vec *) &sp2C), (register Vec*)((Vec *) &sp44));
    }
    M2C_FIELD(var_r31, f32 *, 0) = sp44;
    M2C_FIELD(var_r31, f32 *, 4) = sp48;
    M2C_FIELD(var_r31, f32 *, 8) = sp4C;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp44, sp48, sp4C);
    }
    PSVECAdd((const register Vec*)((Vec *) &sp44), (const register Vec*)((Vec *) &sp38), (register Vec*)((Vec *) &sp44));
    M2C_FIELD(var_r31, f32 *, 0xC) = sp44;
    M2C_FIELD(var_r31, f32 *, 0x10) = sp48;
    M2C_FIELD(var_r31, f32 *, 0x14) = sp4C;
    if ((GSbound *) g_currentBound != NULL) {
        GSboundAddPoint((GSbound*)(g_currentBound), sp44, sp48, sp4C);
    }
    peColorSplineGetValue((u8*)(&sp1C), (peColorSpline*)(M2C_FIELD(p1, peColorSpline **, 8)), p3);
    spA = sp1C;
    sp9 = sp1D;
    sp1C = sp14;
    sp8 = sp1E;
    sp1D = sp10;
    sp1E = spC;
    temp_r3 = M2C_FIELD(p1, peSpline **, 0x10);
    if ((temp_r3 == NULL) || !(M2C_FIELD(temp_r3, u8 *, 0) & 3)) {

    } else {
        var_f1 = M2C_FIELD(temp_r3, f32 *, 8) - p3;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
        if (var_f1 == 0.00001f) {

        } else {
            peSplineGetValue((peSpline*)(temp_r3), p3);
        }
    }
    sp1F = sp18;
    M2C_FIELD(var_r31, s32 *, 0x18) = (s32) sp1C;
    if (temp_r30 != 0) {
        peColorSplineGetValue((u8*)(&sp1C), (peColorSpline*)(M2C_FIELD(p1, peColorSpline **, 0xC)), p3);
        M2C_FIELD(var_r31, s32 *, 0x2C) = (s32) sp1C;
    }
}
}
}
}
