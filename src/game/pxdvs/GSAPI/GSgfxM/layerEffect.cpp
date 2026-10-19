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
enum GSgfxIndTexMtxID { GSgfxIndTexMtxID_draft_dummy };
struct GSgfxLayer;
enum GSgfxLayerPass { GSgfxLayerPass_draft_dummy };
enum GSgfxTgenFunc { GSgfxTgenFunc_draft_dummy };
enum GSgfxTgenSrc { GSgfxTgenSrc_draft_dummy };
struct GSgfxVF;
struct GSmtx;
struct GStexture;
enum Mtx44 { Mtx44_draft_dummy };

extern "C++" {
// ---- draft declarations ----
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
s32 GSgfxVideoGetClearColor(s32*, s32);
void GSgfxVideoGetEFBSize(u16* w, u16* h);
s32 GSgfxVideoSetClearColor(s32*);
s32 GSgfx_GCWriteCopyFilter(u8, void*, s32, s32*);
s32 GSgfx_GCWriteCopyTex(s16*, s32);
void GSmtx44Ortho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
s32 GStextureGetGXformat(GStexture* tex, u8 alpha);
void* memcpy(void* dst, const void* src, size_t n);
extern s32 mtxIdent;
extern s32 jtbl_1978;
}
extern "C++" {
void* GSgfxVideoGetRenderMode();
s32 GSgfxVideoResetViewport(bool);
}
static s32 _layerTexCopyDefaultFilter = 0x08080A0C;
GStexture* distTexPtr__10GSgfxLayer;
GStexture* fbTexPtr__10GSgfxLayer;
// ---- draft declarations ----



void GSgfxLayer::textureCopy(GSgfxLayerPass p0, GStexture* p1, bool p2, unsigned char* p3, bool p4, bool p5, bool p6) {
    if ((s32) M2C_FIELD(this, s32 *, 0x1994) != p0) {
        M2C_FIELD(this, s32 *, 0x1994) = p0;
        M2C_FIELD(this, u8 **, 0x1990) = (u8 *) (this + ((M2C_FIELD(this, s32 *, 0x1994) * 0xBC) + 0x1818));
    }
    ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(p1), p2, (unsigned char*)(p3), p4, p5, p6);
}
}

extern "C++" {
void GSgfxLayer::EffectTextureCopy(GStexture* p0, bool p1, unsigned char* p2, bool p3, bool p4, bool p5) {
    s32 saved_reg_r25;
    s32 saved_reg_r26;
    s32 saved_reg_r27;
    s32 saved_reg_r28;
    s32 saved_reg_r29;
    u8 sp21;
    s8 sp20;
    s32 sp1C;
    s32 sp18;
    u16 sp14;
    u16 sp12;
    u16 sp10;
    s16 spE;
    s16 spC;
    u16 spA;
    u16 sp8;
    s32 var_r25;
    u16 temp_r0_2;
    u16 temp_r0_3;
    u16 var_r3;
    u16 var_r3_2;
    u8 var_r26;
    u8 var_r27;
    u8 var_r28;
    u8 var_r29;
    u8 var_r31;
    u8 *temp_r30;

    var_r25 = saved_reg_r25;
    var_r26 = saved_reg_r26;
    var_r27 = saved_reg_r27;
    var_r28 = saved_reg_r28;
    var_r29 = saved_reg_r29;
    if ((M2C_FIELD(p0, s32 *, 8)) != 0x90) {
        if ((M2C_FIELD(p0, s32 *, 8)) < 0x90) {
            if ((M2C_FIELD(p0, s32 *, 8)) < 0x46) {
                if ((M2C_FIELD(p0, s32 *, 8)) < 0x40) {
                    return;
                }
                goto block_8;
            }
        } else if ((M2C_FIELD(p0, s32 *, 8)) < 0xA4) {
            if ((M2C_FIELD(p0, s32 *, 8)) < 0xA0) {
                return;
            }
            goto block_8;
        }
    } else {
block_8:
        temp_r30 = (unsigned char *)(GSgfxVideoGetRenderMode());
        GSgfxVideoGetEFBSize((u16*)(&spA), (u16*)(&sp8));
        var_r3 = spA;
        temp_r0_2 = M2C_FIELD(p0, u16 *, 0);
        if (temp_r0_2 < var_r3) {
            var_r3 = temp_r0_2;
        }
        spA = var_r3;
        var_r3_2 = sp8;
        temp_r0_3 = M2C_FIELD(p0, u16 *, 2);
        if (temp_r0_3 < var_r3_2) {
            var_r3_2 = temp_r0_3;
        }
        sp8 = var_r3_2;
        var_r31 = 0;
        if ((p3 != 0) || (p4 != 0) || (p5 != 0)) {
            var_r31 = 1;
        }
        if (var_r31 == 1) {
            var_r25 = M2C_FIELD(this, s32 *, 0x1660);
            var_r29 = M2C_FIELD(this, u8 *, 0x1656) != 0;
            var_r28 = M2C_FIELD(this, u8 *, 0x1657) != 0;
            var_r27 = M2C_FIELD(this, u8 *, 0x1658) != 0;
            var_r26 = M2C_FIELD(this, u8 *, 0x165C) != 0;
            if (p3 == 1) {
                M2C_FIELD(this, u8 *, 0x1656) = 1U;
            } else {
                M2C_FIELD(this, u8 *, 0x1656) = 0U;
            }
            if (p4 == 1) {
                M2C_FIELD(this, u8 *, 0x1657) = 1U;
            } else {
                M2C_FIELD(this, u8 *, 0x1657) = 0U;
            }
            if (p5 == 1) {
                M2C_FIELD(this, u8 *, 0x1658) = 1U;
            } else {
                M2C_FIELD(this, u8 *, 0x1658) = 0U;
            }
            M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
            M2C_FIELD(this, u8 *, 0x165C) = 1U;
            M2C_FIELD(this, s32 *, 0x1660) = 7;
            M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 8);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 8);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
        }
        ((GSgfxLayer*)(this))->FlushState();
        if (p1 != 0) {
            if (p2 == NULL) {
                GSgfx_GCWriteCopyFilter(M2C_FIELD(temp_r30, u8 *, 0x19), temp_r30 + 0x1A, 1, &_layerTexCopyDefaultFilter);
            } else {
                GSgfx_GCWriteCopyFilter(M2C_FIELD(temp_r30, u8 *, 0x19), temp_r30 + 0x1A, 1, (s32 *) p2);
            }
        } else {
            GSgfx_GCWriteCopyFilter(M2C_FIELD(temp_r30, u8 *, 0x19), temp_r30 + 0x1A, 0, NULL);
        }
        spC = 0;
        spE = 0;
        sp10 = spA;
        sp12 = sp8;
        sp14 = spA;
        sp18 = GStextureGetGXformat((GStexture*)(p0), 0U);
        sp1C = 3;
        sp20 = 0;
        sp21 = var_r31;
        GSgfx_GCWriteCopyTex(&spC, M2C_FIELD(p0, s32 *, 0x28));
        if (var_r31 == 1) {
            if (var_r29 == 1) {
                M2C_FIELD(this, u8 *, 0x1656) = 1U;
            } else {
                M2C_FIELD(this, u8 *, 0x1656) = 0U;
            }
            if (var_r28 == 1) {
                M2C_FIELD(this, u8 *, 0x1657) = 1U;
            } else {
                M2C_FIELD(this, u8 *, 0x1657) = 0U;
            }
            if (var_r27 == 1) {
                M2C_FIELD(this, u8 *, 0x1658) = 1U;
            } else {
                M2C_FIELD(this, u8 *, 0x1658) = 0U;
            }
            M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
            if (var_r26 == 1) {
                M2C_FIELD(this, u8 *, 0x165C) = 1U;
            } else {
                M2C_FIELD(this, u8 *, 0x165C) = 0U;
            }
            M2C_FIELD(this, s32 *, 0x1660) = var_r25;
            M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 8);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 8);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
        }
        M2C_FIELD(this, s32 *, 4) = (s32) (M2C_FIELD(this, s32 *, 4) | 0x30000000);
    }
}
extern "C++" {
void GSgfxLayer::PrepareDistortion() {
    s32 sp10;
    s32 spC;
    s32 sp8;

    sp10 = jtbl_1978;
    if (!(M2C_FIELD(this, s32 *, 4) & 0x200) || ((u32) M2C_FIELD(this, u32 *, 0x19A4) != (u32)fbTexPtr__10GSgfxLayer)) {
        if ((s32) M2C_FIELD(this, s32 *, 0x1994) != 1) {
            M2C_FIELD(this, s32 *, 0x1994) = 1;
            M2C_FIELD(this, u8 **, 0x1990) = (u8 *) (this + ((M2C_FIELD(this, s32 *, 0x1994) * 0xBC) + 0x1818));
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
        GSgfxVideoGetClearColor(&spC, 2);
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
            M2C_FIELD(this, u8 **, 0x1990) = (u8 *) (this + ((M2C_FIELD(this, s32 *, 0x1994) * 0xBC) + 0x1818));
        }
        ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(fbTexPtr__10GSgfxLayer), 0U, (unsigned char*)(NULL), 0U, 0U, 0U);
    }
}
}

}

extern "C++" {
void GSgfxLayer::EffectScreenClear(bool p0, bool p1, bool p2) {
    f32 sp14;
    f32 sp1C;
    f32 sp24;
    f32 sp30;
    f32 sp34;
    f32 sp8;
    s32 *temp_r3;
    u8 *temp_r30;

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
        GSmtx44Ortho((Mtx44)((s32) &sp8), 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
        M2C_FIELD(this, s32 *, 0xD54) = 1;
        M2C_FIELD(this, f32 *, 0xD58) = sp8;
        M2C_FIELD(this, f32 *, 0xD5C) = sp14;
        M2C_FIELD(this, f32 *, 0xD60) = sp1C;
        M2C_FIELD(this, f32 *, 0xD64) = sp24;
        M2C_FIELD(this, f32 *, 0xD68) = sp30;
        M2C_FIELD(this, f32 *, 0xD6C) = sp34;
        temp_r30 = M2C_FIELD(this, u8 **, 0x19A0);
        memcpy((void*)(M2C_FIELD(temp_r30, s32 **, 4) + 4), (const void*)(&mtxIdent), 0x30U);
        temp_r3 = M2C_FIELD(temp_r30, s32 **, 4);
        *temp_r3 |= 1;
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
        ((GSgfxLayer*)(this))->beginSurface(4U);
        *(f32 *)0xCC008000 = 0.0f;
        *(f32 *)0xCC008000 = 0.0f;
        *(f32 *)0xCC008000 = 29999.0f;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 640.0f;
        *(f32 *)0xCC008000 = 0.0f;
        *(f32 *)0xCC008000 = 29999.0f;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0.0f;
        *(f32 *)0xCC008000 = 480.0f;
        *(f32 *)0xCC008000 = 29999.0f;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 640.0f;
        *(f32 *)0xCC008000 = 480.0f;
        *(f32 *)0xCC008000 = 29999.0f;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        *(f32 *)0xCC008000 = 0;
        ((GSgfxLayer*)(this))->endSurface();
    }
}
}

extern "C++" {
void GSgfxLayer::EffectDistortion() {
    volatile f32 sp18;
    f32 sp20;
    f32 sp28;
    f32 sp34;
    f32 sp38;
    f32 spC;
    s32 sp8;
    s32 *temp_r3;

    if ((u8) M2C_FIELD(this, u8 *, 0x16A7) != 0) {
        M2C_FIELD(this, u8 *, 0x16A7) = 0U;
        M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x40);
        M2C_FIELD(this, s32 *, 0x17C4) = (s32) (M2C_FIELD(this, s32 *, 0x17C4) | 0x40);
        M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 0x40);
    }
    if ((s32) M2C_FIELD(this, s32 *, 0x1994) != 1) {
        M2C_FIELD(this, s32 *, 0x1994) = 1;
        M2C_FIELD(this, u8 **, 0x1990) = (u8 *) (this + ((M2C_FIELD(this, s32 *, 0x1994) * 0xBC) + 0x1818));
    }
    ((GSgfxLayer*)(this))->EffectTextureCopy((GStexture*)(distTexPtr__10GSgfxLayer), 1U, (unsigned char*)(NULL), 0U, 0U, 0U);
    GSgfxVideoResetViewport(1U);
    M2C_FIELD(this, s32 *, 0x1604) = 0;
    M2C_FIELD(this, s32 *, 0x1608) = 1;
    M2C_FIELD(this, s32 *, 0x160C) = 2;
    M2C_FIELD(this, s32 *, 0x1610) = 3;
    M2C_FIELD((s32)this, s32 *, 0x1708) = (s32) (M2C_FIELD(this, s32 *, 0x1708) | 1);
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
    M2C_FIELD(this, s32 *, 0x1668) = 0;
    M2C_FIELD(this, s32 *, 0x166C) = 7;
    M2C_FIELD(this, s8 *, 0x1671) = 0;
    M2C_FIELD(this, s8 *, 0x1672) = 1;
    M2C_FIELD(this, s32 *, 0x170C) = (s32) (M2C_FIELD(this, s32 *, 0x170C) | 0x10);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 0x40);
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
    ((GSgfxLayer*)(this))->tunitIndTexMtx((GSgfxIndTexMtxID)(1), (float(*)[3])(this + 0x19BC), (s8) M2C_FIELD(this, u8 *, 0x19B8));
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
    if (((GStexture *) M2C_FIELD(this, GStexture **, 0x1740) != (GStexture *) fbTexPtr__10GSgfxLayer) || ((GStexture *) M2C_FIELD(this, GStexture **, 0x17F8) != (GStexture *) fbTexPtr__10GSgfxLayer) || ((u8) M2C_FIELD(fbTexPtr__10GSgfxLayer, u8 *, 7) != 0)) {
        M2C_FIELD(this, GStexture **, 0x1740) = (GStexture *) fbTexPtr__10GSgfxLayer;
        M2C_FIELD(this, s32 *, 0x173C) = (s32) (M2C_FIELD(this, s32 *, 0x173C) | 1);
        M2C_FIELD(this, GStexture **, 0x17F8) = (GStexture *) fbTexPtr__10GSgfxLayer;
        M2C_FIELD(this, s32 *, 0x17F4) = (s32) (M2C_FIELD(this, s32 *, 0x17F4) | 1);
    }
    if (((GStexture *) M2C_FIELD(this, GStexture **, 0x1744) != (GStexture *) distTexPtr__10GSgfxLayer) || ((GStexture *) M2C_FIELD(this, GStexture **, 0x17FC) != (GStexture *) distTexPtr__10GSgfxLayer) || ((u8) M2C_FIELD(distTexPtr__10GSgfxLayer, u8 *, 7) != 0)) {
        M2C_FIELD(this, GStexture **, 0x1744) = (GStexture *) distTexPtr__10GSgfxLayer;
        M2C_FIELD(this, s32 *, 0x173C) = (s32) (M2C_FIELD(this, s32 *, 0x173C) | 2);
        M2C_FIELD(this, GStexture **, 0x17FC) = (GStexture *) distTexPtr__10GSgfxLayer;
        M2C_FIELD(this, s32 *, 0x17F4) = (s32) (M2C_FIELD(this, s32 *, 0x17F4) | 2);
    }
    M2C_FIELD(this, GSgfxVF **, 0x199C) = GSgfxVFGetPredef(8);
    GSmtx44Ortho((Mtx44)((s32) &spC), 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    M2C_FIELD(this, s32 *, 0xD54) = 1;
    M2C_FIELD(this, f32 *, 0xD5C) = sp18;
    M2C_FIELD(this, f32 *, 0xD58) = spC;
    M2C_FIELD(this, f32 *, 0xD60) = sp20;
    M2C_FIELD(this, f32 *, 0xD64) = sp28;
    M2C_FIELD(this, f32 *, 0xD68) = sp34;
    M2C_FIELD(this, f32 *, 0xD6C) = sp38;
    memcpy((void*)(M2C_FIELD((M2C_FIELD(this, u8 **, 0x19A0)), s32 **, 4) + 4), (const void*)(&mtxIdent), 0x30U);
    temp_r3 = M2C_FIELD((M2C_FIELD(this, u8 **, 0x19A0)), s32 **, 4);
    *temp_r3 |= 1;
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
    *(s16 *)0xCC008000 = 0;
    *(s16 *)0xCC008000 = 0;
    *(s16 *)0xCC008000 = 0;
    *(s16 *)0xCC008000 = 0;
    *(s16 *)0xCC008000 = 0x280;
    *(s16 *)0xCC008000 = 0;
    *(s16 *)0xCC008000 = 1;
    *(s16 *)0xCC008000 = 0;
    *(s16 *)0xCC008000 = 0;
    *(s16 *)0xCC008000 = 0x1E0;
    *(s16 *)0xCC008000 = 0;
    *(s16 *)0xCC008000 = 1;
    *(s16 *)0xCC008000 = 0x280;
    *(s16 *)0xCC008000 = 0x1E0;
    *(s16 *)0xCC008000 = 1;
    *(s16 *)0xCC008000 = 1;
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

