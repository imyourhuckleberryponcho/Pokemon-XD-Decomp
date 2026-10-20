// Partial: only GSgfxLayer::endSurface is written so far.
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
struct GSgfxDL;
enum GSgfxDiffuseFunc { GSgfxDiffuseFunc_draft_dummy };
enum GSgfxIndTexMtxID { GSgfxIndTexMtxID_draft_dummy };
struct GSgfxLayer;
struct GSgfxLight;
enum GSgfxLightType { GSgfxLightType_draft_dummy };
enum GSgfxTgenFunc { GSgfxTgenFunc_draft_dummy };
enum GSgfxTgenSrc { GSgfxTgenSrc_draft_dummy };
enum GSgfxTunitFunc { GSgfxTunitFunc_draft_dummy };
struct GSmtx;
enum GXTexMtxType { GXTexMtxType_draft_dummy };
struct GXVtxDescList;

extern "C" u8 gsgfx_layer_inPrimitive;

class GSgfxLayer {
public:
    void endSurface();
public: // draft
    void tokenMark();
    void tunitIndTexMtx(GSgfxIndTexMtxID, float(*)[3], signed char);
    void drawOctahedron();
    void dlDraw(GSgfxDL*);
    void drawDodecaedron();
    void tgenFunc(unsigned char, GSgfxTgenFunc, GSgfxTgenSrc, GSmtx*, bool, GSmtx*);
    void cunitChannelGen(unsigned char, GSgfxCunitAlpha, GSgfxCunitSrc, GSgfxCunitSrc, unsigned long, GSgfxLight**, GSgfxLightType, GSgfxDiffuseFunc);
    void drawIcosahedron();
    void SetDistortionParams(float(*)[3], signed char);
    void beginSurface(unsigned short);
    void drawCube();
    void drawSphere(unsigned char, unsigned char);
    void InvalidateState();
    void drawCylinder(unsigned char);
    s32 SetupFifo();
    void drawSphere(unsigned char);
    void FlushState();
    void tunitFunc(unsigned char, GSgfxTunitFunc);
    void drawTorus(float, unsigned char, unsigned char);
    void dlDrawExt(unsigned char*, unsigned long);
};

// ---- draft declarations ----
struct GSgfxDL {
    u8 _draft[1];
};
struct GSgfxLight {
    u8 _draft[1];
};
struct GSmtx {
    u8 _draft[1];
};
struct GXVtxDescList {
    u8 _draft[1];
};

extern "C" {
asm void DCStoreRange(register void* addr, register u32 nBytes);
s32 GSgfx_GCWriteIndTexMtx(s32, s32, s32);
void GXDrawCube(void);
void GXDrawCylinder(u8 numEdges);
void GXDrawDodeca(void);
void GXDrawIcosahedron(void);
void GXDrawOctahedron(void);
void GXDrawSphere(u8 numMajor, u8 numMinor);
void GXDrawSphere1(u8 depth);
void GXDrawTorus(f32 rc, u8 numc, u8 numt);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXSetVtxDescv(const GXVtxDescList *attrPtr);
void* memset(void* dst, int val, size_t n);
extern s32 arg_sp8;
extern s32 this_;
}
extern "C++" {
u16 GSgfxTokenMark_Sub();
}

// ---- draft declarations ----




extern "C++" {
void GSgfxLayer::SetDistortionParams(float(*p0)[3], signed char p1) {
    M2C_FIELD(this, f32 *, 0x19BC) = (f32) M2C_FIELD(p0, f32 *, 0);
    M2C_FIELD(this, f32 *, 0x19C0) = (f32) M2C_FIELD(p0, f32 *, 4);
    M2C_FIELD(this, f32 *, 0x19C4) = (f32) M2C_FIELD(p0, f32 *, 8);
    M2C_FIELD(this, f32 *, 0x19C8) = (f32) M2C_FIELD(p0, f32 *, 0xC);
    M2C_FIELD(this, f32 *, 0x19CC) = (f32) M2C_FIELD(p0, f32 *, 0x10);
    M2C_FIELD(this, f32 *, 0x19D0) = (f32) M2C_FIELD(p0, f32 *, 0x14);
    M2C_FIELD(this, s8 *, 0x19B8) = p1;
}
}

extern "C++" {
void GSgfxLayer::tokenMark() {
    ((GSgfxLayer*)(this))->SetupFifo();
    GSgfxTokenMark_Sub();
}
}

extern "C++" {
void GSgfxLayer::tunitIndTexMtx(GSgfxIndTexMtxID p0, float(*p1)[3], signed char p2) {
    s32 temp_r30;
    u8 temp_r4;

    ((GSgfxLayer*)(this))->SetupFifo();
    GSgfx_GCWriteIndTexMtx(p0, (s32) p1, (s32) p2);
    temp_r30 = M2C_FIELD(this, s32 *, 0x1994);
    temp_r4 = temp_r30 == 0;
    if ((u32) M2C_FIELD((this + (temp_r4 * 0xBC)), u32 *, 0x1818) != 0U) {
        if (temp_r30 != (s32) temp_r4) {
            M2C_FIELD(this, s32 *, 0x1994) = (s32) temp_r4;
            M2C_FIELD(this, u8 **, 0x1990) = (u8 *) ((u8*)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC);
        }
        ((GSgfxLayer*)(this))->SetupFifo();
        GSgfx_GCWriteIndTexMtx(p0, (s32) p1, (s32) p2);
        if ((s32) M2C_FIELD(this, s32 *, 0x1994) != temp_r30) {
            M2C_FIELD(this, s32 *, 0x1994) = temp_r30;
            M2C_FIELD(this, u8 **, 0x1990) = (u8 *) ((u8*)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC);
        }
        ((GSgfxLayer*)(this))->SetupFifo();
    }
}
}

extern "C++" {


extern "C++" {
void GSgfxLayer::drawSphere(unsigned char p0) {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(M2C_FIELD(this, s32 *, 0x199C) + 0x1B8));
    GXDrawSphere1(p0);
    ((GSgfxLayer*)(this))->InvalidateState();
}
}










extern "C++" {
void GSgfxLayer::drawSphere(unsigned char p0, unsigned char p1) {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(M2C_FIELD(this, s32 *, 0x199C) + 0x1B8));
    GXDrawSphere(p1, p0);
    ((GSgfxLayer*)(this))->InvalidateState();
}
}
}

extern "C++" {
void GSgfxLayer::tgenFunc(unsigned char p0, GSgfxTgenFunc p1, GSgfxTgenSrc p2, GSmtx* p3, bool p4, GSmtx* p5) {
    f32 temp_f1;
    f32 temp_f1_2;
    s32 temp_r30;
    s32 temp_r31;
    int temp_r3;
    u8 temp_r4_2;
    u8 var_r5;
    u8 *temp_r4;

    temp_r4 = (unsigned char *)(this + temp_r31);
    M2C_FIELD(temp_r4, s32 *, 0xC88) = 0;
    temp_r31 = 0x18;
    temp_r31 *= p0;
    var_r5 = 0;
    M2C_FIELD(temp_r4, s32 *, 0xC74) = p1;
    M2C_FIELD(temp_r4, s32 *, 0xC78) = p2;
    M2C_FIELD(temp_r4, u8 *, 0xC80) = p4;
    if (p3 == NULL) {
        M2C_FIELD(temp_r4, s32 *, 0xC7C) = 0x3C;
    } else {
        var_r5 = 1;
        M2C_FIELD(temp_r4, s32 *, 0xC7C) = (s32) ((p0 * 3) + 0x1E);
    }
    if (p5 == NULL) {
        M2C_FIELD((this + temp_r31), s32 *, 0xC84) = 0x7D;
    } else {
        var_r5 = 1;
        M2C_FIELD((this + temp_r31), s32 *, 0xC84) = (s32) ((p0 * 3) + 0x40);
    }
    if (var_r5 == 1) {
        temp_f1 = M2C_BITWISE(f32, ((GSgfxLayer*)(this))->SetupFifo());
        if (p3 != NULL) {
            if (p1 == 1) {
                GXLoadTexMtxImm((const float (*)[4])&(temp_f1), (unsigned long)((u32) p3), (GXTexMtxType)(M2C_FIELD((this + temp_r31), s32 *, 0xC7C)));
            } else {
                GXLoadTexMtxImm((const float (*)[4])&(temp_f1), (unsigned long)((u32) p3), (GXTexMtxType)(M2C_FIELD((this + temp_r31), s32 *, 0xC7C)));
            }
        }
        if (p5 != NULL) {
            GXLoadTexMtxImm(M2C_ERROR(/* Read from unset register $f1 */), (u32) p3, (GXTexMtxType)(M2C_FIELD((this + temp_r31), s32 *, 0xC84)));
        }
        temp_r30 = M2C_FIELD(this, s32 *, 0x1994);
        temp_r4_2 = temp_r30 == 0;
        if ((u32) M2C_FIELD((this + (temp_r4_2 * 0xBC)), u32 *, 0x1818) != 0U) {
            if (temp_r30 != (s32) temp_r4_2) {
                M2C_FIELD(this, s32 *, 0x1994) = (s32) temp_r4_2;
                M2C_FIELD(this, u8 **, 0x1990) = (u8 *) ((u8*)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC);
            }
            temp_f1_2 = M2C_BITWISE(f32, ((GSgfxLayer*)(this))->SetupFifo());
            if (p3 != NULL) {
                if (p1 == 1) {
                    GXLoadTexMtxImm((const float (*)[4])&(temp_f1_2), (unsigned long)((u32) p3), (GXTexMtxType)(M2C_FIELD((this + temp_r31), s32 *, 0xC7C)));
                } else {
                    GXLoadTexMtxImm((const float (*)[4])&(temp_f1_2), (unsigned long)((u32) p3), (GXTexMtxType)(M2C_FIELD((this + temp_r31), s32 *, 0xC7C)));
                }
            }
            if (p5 != NULL) {
                GXLoadTexMtxImm(M2C_ERROR(/* Read from unset register $f1 */), (u32) p3, (GXTexMtxType)(M2C_FIELD((this + temp_r31), s32 *, 0xC84)));
            }
            if ((s32) M2C_FIELD(this, s32 *, 0x1994) != temp_r30) {
                M2C_FIELD(this, s32 *, 0x1994) = temp_r30;
                M2C_FIELD(this, u8 **, 0x1990) = (u8 *) ((u8*)this + 0x1818 + M2C_FIELD(this, s32 *, 0x1994) * 0xBC);
            }
            ((GSgfxLayer*)(this))->SetupFifo();
        }
    }
    temp_r3 = 1 << p0;
    M2C_FIELD(this, s32 *, 0x16B0) = (s32) (M2C_FIELD(this, s32 *, 0x16B0) | temp_r3);
    M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 1);
    M2C_FIELD(this, s32 *, 0x1768) = (s32) (M2C_FIELD(this, s32 *, 0x1768) | temp_r3);
    M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 1);
}
}

extern "C++" {
void GSgfxLayer::tunitFunc(unsigned char p0, GSgfxTunitFunc p1) {
    u8 *temp_r9;
    u8 *temp_r9_2;
    u8 *temp_r7;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_3;
    u8 *temp_r30;
    u8 *temp_r10_2;
    u8 *temp_r11;
    u8 *temp_r11_2;
    u8 *temp_r12;
    u8 *temp_r12_2;
    u8 *temp_r29;
    u8 *temp_r29_2;
    u8 *temp_r10;
    u8 *temp_r31;
    s32 temp_r0_3;
    u8 *temp_r7_2;
    u8 *temp_r8;
    u8 *temp_r8_2;
    s32 temp_r0;
    s32 temp_r0_2;

    if ((u32) p1 <= 7U) {
        switch (p1) {
        case 0:
            temp_r29 = (unsigned char *)(this + (p0 * 0x14));
            temp_r9 = (unsigned char *)(this + ((p0 * 0x10) & 0xFF0));
            M2C_FIELD(temp_r29, s32 *, 0x1170) = 0;
            temp_r0 = 1 << p0;
            M2C_FIELD(temp_r29, s32 *, 0x1174) = 0;
            M2C_FIELD(temp_r29, s32 *, 0x1178) = 0;
            M2C_FIELD(temp_r29, s8 *, 0x117C) = 1;
            M2C_FIELD(temp_r29, s32 *, 0x1180) = 0;
            M2C_FIELD(this, s32 *, 0x16DC) = (s32) (M2C_FIELD(this, s32 *, 0x16DC) | temp_r0);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1794) = (s32) (M2C_FIELD(this, s32 *, 0x1794) | temp_r0);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r9, s32 *, 0xF70) = 0xF;
            M2C_FIELD(temp_r9, s32 *, 0xF74) = 0xA;
            M2C_FIELD(temp_r9, s32 *, 0xF78) = 8;
            M2C_FIELD(temp_r9, s32 *, 0xF7C) = 0xF;
            M2C_FIELD(this, s32 *, 0x16D4) = (s32) (M2C_FIELD(this, s32 *, 0x16D4) | temp_r0);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x178C) = (s32) (M2C_FIELD(this, s32 *, 0x178C) | temp_r0);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r29, s32 *, 0x12B0) = 0;
            M2C_FIELD(temp_r29, s32 *, 0x12B4) = 0;
            M2C_FIELD(temp_r29, s32 *, 0x12B8) = 0;
            M2C_FIELD(temp_r29, s8 *, 0x12BC) = 1;
            M2C_FIELD(temp_r29, s32 *, 0x12C0) = 0;
            M2C_FIELD(this, s32 *, 0x16E0) = (s32) (M2C_FIELD(this, s32 *, 0x16E0) | temp_r0);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1798) = (s32) (M2C_FIELD(this, s32 *, 0x1798) | temp_r0);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r9, s32 *, 0x1070) = 7;
            M2C_FIELD(temp_r9, s32 *, 0x1074) = 5;
            M2C_FIELD(temp_r9, s32 *, 0x1078) = 4;
            M2C_FIELD(temp_r9, s32 *, 0x107C) = 7;
            M2C_FIELD(this, s32 *, 0x16D8) = (s32) (M2C_FIELD(this, s32 *, 0x16D8) | temp_r0);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1790) = (s32) (M2C_FIELD(this, s32 *, 0x1790) | temp_r0);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            return;
        case 1:
            temp_r29_2 = (unsigned char *)(this + (p0 * 0x14));
            temp_r9_2 = (unsigned char *)(this + ((p0 * 0x10) & 0xFF0));
            M2C_FIELD(temp_r29_2, s32 *, 0x1170) = 0;
            temp_r0_2 = 1 << p0;
            M2C_FIELD(temp_r29_2, s32 *, 0x1174) = 0;
            M2C_FIELD(temp_r29_2, s32 *, 0x1178) = 0;
            M2C_FIELD(temp_r29_2, s8 *, 0x117C) = 1;
            M2C_FIELD(temp_r29_2, s32 *, 0x1180) = 0;
            M2C_FIELD(this, s32 *, 0x16DC) = (s32) (M2C_FIELD(this, s32 *, 0x16DC) | temp_r0_2);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1794) = (s32) (M2C_FIELD(this, s32 *, 0x1794) | temp_r0_2);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r9_2, s32 *, 0xF70) = 0xA;
            M2C_FIELD(temp_r9_2, s32 *, 0xF74) = 8;
            M2C_FIELD(temp_r9_2, s32 *, 0xF78) = 9;
            M2C_FIELD(temp_r9_2, s32 *, 0xF7C) = 0xF;
            M2C_FIELD(this, s32 *, 0x16D4) = (s32) (M2C_FIELD(this, s32 *, 0x16D4) | temp_r0_2);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x178C) = (s32) (M2C_FIELD(this, s32 *, 0x178C) | temp_r0_2);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r29_2, s32 *, 0x12B0) = 0;
            M2C_FIELD(temp_r29_2, s32 *, 0x12B4) = 0;
            M2C_FIELD(temp_r29_2, s32 *, 0x12B8) = 0;
            M2C_FIELD(temp_r29_2, s8 *, 0x12BC) = 1;
            M2C_FIELD(temp_r29_2, s32 *, 0x12C0) = 0;
            M2C_FIELD(this, s32 *, 0x16E0) = (s32) (M2C_FIELD(this, s32 *, 0x16E0) | temp_r0_2);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1798) = (s32) (M2C_FIELD(this, s32 *, 0x1798) | temp_r0_2);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r9_2, s32 *, 0x1070) = 7;
            M2C_FIELD(temp_r9_2, s32 *, 0x1074) = 7;
            M2C_FIELD(temp_r9_2, s32 *, 0x1078) = 7;
            M2C_FIELD(temp_r9_2, s32 *, 0x107C) = 5;
            M2C_FIELD(this, s32 *, 0x16D8) = (s32) (M2C_FIELD(this, s32 *, 0x16D8) | temp_r0_2);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1790) = (s32) (M2C_FIELD(this, s32 *, 0x1790) | temp_r0_2);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            return;
        case 2:
            temp_r31 = (unsigned char *)(this + (p0 * 0x14));
            temp_r10 = (unsigned char *)(this + ((p0 * 0x10) & 0xFF0));
            M2C_FIELD(temp_r31, s32 *, 0x1170) = 0;
            temp_r0_3 = 1 << p0;
            M2C_FIELD(temp_r31, s32 *, 0x1174) = 0;
            M2C_FIELD(temp_r31, s32 *, 0x1178) = 0;
            M2C_FIELD(temp_r31, s8 *, 0x117C) = 1;
            M2C_FIELD(temp_r31, s32 *, 0x1180) = 0;
            M2C_FIELD(this, s32 *, 0x16DC) = (s32) (M2C_FIELD(this, s32 *, 0x16DC) | temp_r0_3);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1794) = (s32) (M2C_FIELD(this, s32 *, 0x1794) | temp_r0_3);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r10, s32 *, 0xF70) = 0xA;
            M2C_FIELD(temp_r10, s32 *, 0xF74) = 0xC;
            M2C_FIELD(temp_r10, s32 *, 0xF78) = 8;
            M2C_FIELD(temp_r10, s32 *, 0xF7C) = 0xF;
            M2C_FIELD(this, s32 *, 0x16D4) = (s32) (M2C_FIELD(this, s32 *, 0x16D4) | temp_r0_3);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x178C) = (s32) (M2C_FIELD(this, s32 *, 0x178C) | temp_r0_3);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r31, s32 *, 0x12B0) = 0;
            M2C_FIELD(temp_r31, s32 *, 0x12B4) = 0;
            M2C_FIELD(temp_r31, s32 *, 0x12B8) = 0;
            M2C_FIELD(temp_r31, s8 *, 0x12BC) = 1;
            M2C_FIELD(temp_r31, s32 *, 0x12C0) = 0;
            M2C_FIELD(this, s32 *, 0x16E0) = (s32) (M2C_FIELD(this, s32 *, 0x16E0) | temp_r0_3);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1798) = (s32) (M2C_FIELD(this, s32 *, 0x1798) | temp_r0_3);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r10, s32 *, 0x1070) = 7;
            M2C_FIELD(temp_r10, s32 *, 0x1074) = 5;
            M2C_FIELD(temp_r10, s32 *, 0x1078) = 4;
            M2C_FIELD(temp_r10, s32 *, 0x107C) = 7;
            M2C_FIELD(this, s32 *, 0x16D8) = (s32) (M2C_FIELD(this, s32 *, 0x16D8) | temp_r0_3);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1790) = (s32) (M2C_FIELD(this, s32 *, 0x1790) | temp_r0_3);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            return;
        case 3:
            temp_r11 = (unsigned char *)(this + (p0 * 0x14));
            temp_r7 = (unsigned char *)(this + ((p0 * 0x10) & 0xFF0));
            M2C_FIELD(temp_r11, s32 *, 0x1170) = 0;
            temp_r0_4 = 1 << p0;
            M2C_FIELD(temp_r11, s32 *, 0x1174) = 0;
            M2C_FIELD(temp_r11, s32 *, 0x1178) = 0;
            M2C_FIELD(temp_r11, s8 *, 0x117C) = 1;
            M2C_FIELD(temp_r11, s32 *, 0x1180) = 0;
            M2C_FIELD(this, s32 *, 0x16DC) = (s32) (M2C_FIELD(this, s32 *, 0x16DC) | temp_r0_4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1794) = (s32) (M2C_FIELD(this, s32 *, 0x1794) | temp_r0_4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r7, s32 *, 0xF70) = 8;
            M2C_FIELD(temp_r7, s32 *, 0xF74) = 0xF;
            M2C_FIELD(temp_r7, s32 *, 0xF78) = 0xF;
            M2C_FIELD(temp_r7, s32 *, 0xF7C) = 0xF;
            M2C_FIELD(this, s32 *, 0x16D4) = (s32) (M2C_FIELD(this, s32 *, 0x16D4) | temp_r0_4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x178C) = (s32) (M2C_FIELD(this, s32 *, 0x178C) | temp_r0_4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r11, s32 *, 0x12B0) = 0;
            M2C_FIELD(temp_r11, s32 *, 0x12B4) = 0;
            M2C_FIELD(temp_r11, s32 *, 0x12B8) = 0;
            M2C_FIELD(temp_r11, s8 *, 0x12BC) = 1;
            M2C_FIELD(temp_r11, s32 *, 0x12C0) = 0;
            M2C_FIELD(this, s32 *, 0x16E0) = (s32) (M2C_FIELD(this, s32 *, 0x16E0) | temp_r0_4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1798) = (s32) (M2C_FIELD(this, s32 *, 0x1798) | temp_r0_4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r7, s32 *, 0x1070) = 4;
            M2C_FIELD(temp_r7, s32 *, 0x1074) = 7;
            M2C_FIELD(temp_r7, s32 *, 0x1078) = 7;
            M2C_FIELD(temp_r7, s32 *, 0x107C) = 7;
            M2C_FIELD(this, s32 *, 0x16D8) = (s32) (M2C_FIELD(this, s32 *, 0x16D8) | temp_r0_4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1790) = (s32) (M2C_FIELD(this, s32 *, 0x1790) | temp_r0_4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            return;
        case 4:
            temp_r11_2 = (unsigned char *)(this + (p0 * 0x14));
            temp_r7_2 = (unsigned char *)(this + ((p0 * 0x10) & 0xFF0));
            M2C_FIELD(temp_r11_2, s32 *, 0x1170) = 0;
            temp_r0_5 = 1 << p0;
            M2C_FIELD(temp_r11_2, s32 *, 0x1174) = 0;
            M2C_FIELD(temp_r11_2, s32 *, 0x1178) = 0;
            M2C_FIELD(temp_r11_2, s8 *, 0x117C) = 1;
            M2C_FIELD(temp_r11_2, s32 *, 0x1180) = 0;
            M2C_FIELD(this, s32 *, 0x16DC) = (s32) (M2C_FIELD(this, s32 *, 0x16DC) | temp_r0_5);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1794) = (s32) (M2C_FIELD(this, s32 *, 0x1794) | temp_r0_5);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r7_2, s32 *, 0xF70) = 0xA;
            M2C_FIELD(temp_r7_2, s32 *, 0xF74) = 0xF;
            M2C_FIELD(temp_r7_2, s32 *, 0xF78) = 0xF;
            M2C_FIELD(temp_r7_2, s32 *, 0xF7C) = 0xF;
            M2C_FIELD(this, s32 *, 0x16D4) = (s32) (M2C_FIELD(this, s32 *, 0x16D4) | temp_r0_5);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x178C) = (s32) (M2C_FIELD(this, s32 *, 0x178C) | temp_r0_5);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r11_2, s32 *, 0x12B0) = 0;
            M2C_FIELD(temp_r11_2, s32 *, 0x12B4) = 0;
            M2C_FIELD(temp_r11_2, s32 *, 0x12B8) = 0;
            M2C_FIELD(temp_r11_2, s8 *, 0x12BC) = 1;
            M2C_FIELD(temp_r11_2, s32 *, 0x12C0) = 0;
            M2C_FIELD(this, s32 *, 0x16E0) = (s32) (M2C_FIELD(this, s32 *, 0x16E0) | temp_r0_5);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1798) = (s32) (M2C_FIELD(this, s32 *, 0x1798) | temp_r0_5);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r7_2, s32 *, 0x1070) = 5;
            M2C_FIELD(temp_r7_2, s32 *, 0x1074) = 7;
            M2C_FIELD(temp_r7_2, s32 *, 0x1078) = 7;
            M2C_FIELD(temp_r7_2, s32 *, 0x107C) = 7;
            M2C_FIELD(this, s32 *, 0x16D8) = (s32) (M2C_FIELD(this, s32 *, 0x16D8) | temp_r0_5);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1790) = (s32) (M2C_FIELD(this, s32 *, 0x1790) | temp_r0_5);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            return;
        case 5:
            temp_r4 = 1 << p0;
            temp_r8 = (unsigned char *)(this + ((p0 * 0x10) & 0xFF0));
            temp_r12 = (unsigned char *)(this + (p0 * 0x14));
            M2C_FIELD(temp_r12, s32 *, 0x1170) = 0;
            M2C_FIELD(temp_r12, s32 *, 0x1174) = 0;
            M2C_FIELD(temp_r12, s32 *, 0x1178) = 0;
            M2C_FIELD(temp_r12, s8 *, 0x117C) = 1;
            M2C_FIELD(temp_r12, s32 *, 0x1180) = 0;
            M2C_FIELD(this, s32 *, 0x16DC) = (s32) (M2C_FIELD(this, s32 *, 0x16DC) | temp_r4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1794) = (s32) (M2C_FIELD(this, s32 *, 0x1794) | temp_r4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r8, s32 *, 0xF70) = 8;
            M2C_FIELD(temp_r8, s32 *, 0xF74) = 0xF;
            M2C_FIELD(temp_r8, s32 *, 0xF78) = 0xF;
            M2C_FIELD(temp_r8, s32 *, 0xF7C) = 0;
            M2C_FIELD(this, s32 *, 0x16D4) = (s32) (M2C_FIELD(this, s32 *, 0x16D4) | temp_r4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x178C) = (s32) (M2C_FIELD(this, s32 *, 0x178C) | temp_r4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r12, s32 *, 0x12B0) = 0;
            M2C_FIELD(temp_r12, s32 *, 0x12B4) = 0;
            M2C_FIELD(temp_r12, s32 *, 0x12B8) = 0;
            M2C_FIELD(temp_r12, s8 *, 0x12BC) = 1;
            M2C_FIELD(temp_r12, s32 *, 0x12C0) = 0;
            M2C_FIELD(this, s32 *, 0x16E0) = (s32) (M2C_FIELD(this, s32 *, 0x16E0) | temp_r4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1798) = (s32) (M2C_FIELD(this, s32 *, 0x1798) | temp_r4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r8, s32 *, 0x1070) = 4;
            M2C_FIELD(temp_r8, s32 *, 0x1074) = 7;
            M2C_FIELD(temp_r8, s32 *, 0x1078) = 7;
            M2C_FIELD(temp_r8, s32 *, 0x107C) = 0;
            M2C_FIELD(this, s32 *, 0x16D8) = (s32) (M2C_FIELD(this, s32 *, 0x16D8) | temp_r4);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1790) = (s32) (M2C_FIELD(this, s32 *, 0x1790) | temp_r4);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            return;
        case 6:
            temp_r4_2 = 1 << p0;
            temp_r8_2 = (unsigned char *)(this + ((p0 * 0x10) & 0xFF0));
            temp_r12_2 = (unsigned char *)(this + (p0 * 0x14));
            M2C_FIELD(temp_r12_2, s32 *, 0x1170) = 0;
            M2C_FIELD(temp_r12_2, s32 *, 0x1174) = 0;
            M2C_FIELD(temp_r12_2, s32 *, 0x1178) = 0;
            M2C_FIELD(temp_r12_2, s8 *, 0x117C) = 1;
            M2C_FIELD(temp_r12_2, s32 *, 0x1180) = 0;
            M2C_FIELD(this, s32 *, 0x16DC) = (s32) (M2C_FIELD(this, s32 *, 0x16DC) | temp_r4_2);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1794) = (s32) (M2C_FIELD(this, s32 *, 0x1794) | temp_r4_2);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r8_2, s32 *, 0xF70) = 0xA;
            M2C_FIELD(temp_r8_2, s32 *, 0xF74) = 0xF;
            M2C_FIELD(temp_r8_2, s32 *, 0xF78) = 0xF;
            M2C_FIELD(temp_r8_2, s32 *, 0xF7C) = 0;
            M2C_FIELD(this, s32 *, 0x16D4) = (s32) (M2C_FIELD(this, s32 *, 0x16D4) | temp_r4_2);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x178C) = (s32) (M2C_FIELD(this, s32 *, 0x178C) | temp_r4_2);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r12_2, s32 *, 0x12B0) = 0;
            M2C_FIELD(temp_r12_2, s32 *, 0x12B4) = 0;
            M2C_FIELD(temp_r12_2, s32 *, 0x12B8) = 0;
            M2C_FIELD(temp_r12_2, s8 *, 0x12BC) = 1;
            M2C_FIELD(temp_r12_2, s32 *, 0x12C0) = 0;
            M2C_FIELD(this, s32 *, 0x16E0) = (s32) (M2C_FIELD(this, s32 *, 0x16E0) | temp_r4_2);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1798) = (s32) (M2C_FIELD(this, s32 *, 0x1798) | temp_r4_2);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r8_2, s32 *, 0x1070) = 5;
            M2C_FIELD(temp_r8_2, s32 *, 0x1074) = 7;
            M2C_FIELD(temp_r8_2, s32 *, 0x1078) = 7;
            M2C_FIELD(temp_r8_2, s32 *, 0x107C) = 0;
            M2C_FIELD(this, s32 *, 0x16D8) = (s32) (M2C_FIELD(this, s32 *, 0x16D8) | temp_r4_2);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1790) = (s32) (M2C_FIELD(this, s32 *, 0x1790) | temp_r4_2);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            return;
        case 7:
            temp_r4_3 = 1 << p0;
            temp_r30 = (unsigned char *)(this + (p0 * 0x14));
            temp_r10_2 = (unsigned char *)(this + ((p0 * 0x10) & 0xFF0));
            M2C_FIELD(temp_r30, s32 *, 0x1170) = 0;
            M2C_FIELD(temp_r30, s32 *, 0x1174) = 0;
            M2C_FIELD(temp_r30, s32 *, 0x1178) = 0;
            M2C_FIELD(temp_r30, s8 *, 0x117C) = 1;
            M2C_FIELD(temp_r30, s32 *, 0x1180) = 0;
            M2C_FIELD(this, s32 *, 0x16DC) = (s32) (M2C_FIELD(this, s32 *, 0x16DC) | temp_r4_3);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1794) = (s32) (M2C_FIELD(this, s32 *, 0x1794) | temp_r4_3);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r10_2, s32 *, 0xF70) = 0xF;
            M2C_FIELD(temp_r10_2, s32 *, 0xF74) = 0xA;
            M2C_FIELD(temp_r10_2, s32 *, 0xF78) = 8;
            M2C_FIELD(temp_r10_2, s32 *, 0xF7C) = 0;
            M2C_FIELD(this, s32 *, 0x16D4) = (s32) (M2C_FIELD(this, s32 *, 0x16D4) | temp_r4_3);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x178C) = (s32) (M2C_FIELD(this, s32 *, 0x178C) | temp_r4_3);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r30, s32 *, 0x12B0) = 0;
            M2C_FIELD(temp_r30, s32 *, 0x12B4) = 0;
            M2C_FIELD(temp_r30, s32 *, 0x12B8) = 0;
            M2C_FIELD(temp_r30, s8 *, 0x12BC) = 1;
            M2C_FIELD(temp_r30, s32 *, 0x12C0) = 0;
            M2C_FIELD(this, s32 *, 0x16E0) = (s32) (M2C_FIELD(this, s32 *, 0x16E0) | temp_r4_3);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1798) = (s32) (M2C_FIELD(this, s32 *, 0x1798) | temp_r4_3);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            M2C_FIELD(temp_r10_2, s32 *, 0x1070) = 7;
            M2C_FIELD(temp_r10_2, s32 *, 0x1074) = 5;
            M2C_FIELD(temp_r10_2, s32 *, 0x1078) = 4;
            M2C_FIELD(temp_r10_2, s32 *, 0x107C) = 0;
            M2C_FIELD(this, s32 *, 0x16D8) = (s32) (M2C_FIELD(this, s32 *, 0x16D8) | temp_r4_3);
            M2C_FIELD(this, s32 *, 0x16A8) = (s32) (M2C_FIELD(this, s32 *, 0x16A8) | 8);
            M2C_FIELD(this, s32 *, 0x1790) = (s32) (M2C_FIELD(this, s32 *, 0x1790) | temp_r4_3);
            M2C_FIELD(this, s32 *, 0x1760) = (s32) (M2C_FIELD(this, s32 *, 0x1760) | 8);
            break;
        }
    }
}
}

extern "C++" {
void GSgfxLayer::cunitChannelGen(unsigned char p0, GSgfxCunitAlpha p1, GSgfxCunitSrc p2, GSgfxCunitSrc p3, unsigned long p4, GSgfxLight** p5, GSgfxLightType p6, GSgfxDiffuseFunc p7) {
    GSgfxLight **var_r4;
    u8 *var_r3;
    s32 temp_r29;
    s32 temp_r4;
    int temp_r4_2;
    s32 temp_r4_3;
    s32 var_ctr;
    s32 var_ctr_2;
    GSgfxLight **var_r5_2;
    s32 var_r28;
    u32 temp_r6;
    u32 temp_r6_2;
    u32 temp_r6_3;
    u32 temp_r6_4;
    u32 temp_r6_5;
    u32 temp_r6_6;
    u32 var_r6;
    u32 var_r6_2;
    u8 var_r31;
    u8 *temp_r3;
    s32 var_r27;
    u8 *var_r5;

    var_r28 = arg_sp8;
    var_r27 = p6;
    temp_r29 = p0 + 2;
    var_r31 = 0;
    if ((p5 != NULL) && (p4 != 0)) {
        var_r31 = 1;
    }
    if (var_r31 == 0) {
        var_r27 = 2;
        var_r28 = 0;
    } else if (var_r27 == 0) {
        var_r28 = 0;
    }
    if ((p1 == 0) || (p1 == 2)) {
        temp_r4 = p0 * 0x38;
        var_r5 = (unsigned char *)(((s32)this) + temp_r4);
        M2C_FIELD(var_r5, u8 *, 0xDBC) = var_r31;
        M2C_FIELD(var_r5, s32 *, 0xDC0) = p2;
        M2C_FIELD(var_r5, s32 *, 0xDC4) = p3;
        M2C_FIELD(var_r5, s32 *, 0xDC8) = 0;
        M2C_FIELD(var_r5, s32 *, 0xDCC) = var_r28;
        M2C_FIELD(var_r5, s32 *, 0xDD0) = var_r27;
        if (var_r31 != 0) {
            var_r4 = p5;
            var_r6 = 0U;
            var_ctr = 2;
            do {
                if (var_r6 < p4) {
                    M2C_FIELD(var_r5, GSgfxLight **, 0xDD4) = (GSgfxLight *) M2C_FIELD(var_r4, GSgfxLight **, 0);
                } else {
                    M2C_FIELD(var_r5, GSgfxLight **, 0xDD4) = NULL;
                }
                temp_r6 = var_r6 + 1;
                if (temp_r6 < p4) {
                    M2C_FIELD(var_r5, s32 *, 0xDD8) = (s32) M2C_FIELD(var_r4, s32 *, 4);
                } else {
                    M2C_FIELD(var_r5, s32 *, 0xDD8) = 0;
                }
                temp_r6_2 = temp_r6 + 1;
                if (temp_r6_2 < p4) {
                    M2C_FIELD(var_r5, s32 *, 0xDDC) = (s32) M2C_FIELD(var_r4, s32 *, 8);
                } else {
                    M2C_FIELD(var_r5, s32 *, 0xDDC) = 0;
                }
                temp_r6_3 = temp_r6_2 + 1;
                if (temp_r6_3 < p4) {
                    M2C_FIELD(var_r5, s32 *, 0xDE0) = (s32) M2C_FIELD(var_r4, s32 *, 0xC);
                } else {
                    M2C_FIELD(var_r5, s32 *, 0xDE0) = 0;
                }
                var_r4 += 0x10;
                var_r5 += 0x10;
                var_r6 = temp_r6_3 + 1;
                var_ctr -= 1;
            } while (var_ctr != 0);
        } else {
            memset((void*)(((s32)this) + (temp_r4 + 0xDD4)), 0, 0x20U);
        }
        temp_r4_2 = 1 << p0;
        M2C_FIELD(((s32)this), s32 *, 0x16C0) = (s32) (M2C_FIELD(((s32)this), s32 *, 0x16C0) | temp_r4_2);
        M2C_FIELD(((s32)this), s32 *, 0x1778) = (s32) (M2C_FIELD(((s32)this), s32 *, 0x1778) | temp_r4_2);
    }
    if ((p1 == 1) || (p1 == 2)) {
        temp_r3 = (unsigned char *)(((s32)this) + (temp_r29 * 0x38));
        M2C_FIELD(temp_r3, u8 *, 0xDBC) = var_r31;
        M2C_FIELD(temp_r3, s32 *, 0xDC0) = p2;
        M2C_FIELD(temp_r3, s32 *, 0xDC4) = p3;
        M2C_FIELD(temp_r3, s32 *, 0xDC8) = 0;
        M2C_FIELD(temp_r3, s32 *, 0xDCC) = var_r28;
        M2C_FIELD(temp_r3, s32 *, 0xDD0) = var_r27;
        if (var_r31 != 0) {
            var_r6_2 = 0U;
            var_r5_2 = p5;
            var_r3 = (unsigned char *)(((s32)this) + (p0 * 0x38));
            var_ctr_2 = 2;
            do {
                if (var_r6_2 < p4) {
                    M2C_FIELD(var_r3, GSgfxLight **, 0xDD4) = (GSgfxLight *) M2C_FIELD(var_r5_2, GSgfxLight **, 0);
                } else {
                    M2C_FIELD(var_r3, GSgfxLight **, 0xDD4) = NULL;
                }
                temp_r6_4 = var_r6_2 + 1;
                if (temp_r6_4 < p4) {
                    M2C_FIELD(var_r3, s32 *, 0xDD8) = (s32) M2C_FIELD(var_r5_2, s32 *, 4);
                } else {
                    M2C_FIELD(var_r3, s32 *, 0xDD8) = 0;
                }
                temp_r6_5 = temp_r6_4 + 1;
                if (temp_r6_5 < p4) {
                    M2C_FIELD(var_r3, s32 *, 0xDDC) = (s32) M2C_FIELD(var_r5_2, s32 *, 8);
                } else {
                    M2C_FIELD(var_r3, s32 *, 0xDDC) = 0;
                }
                temp_r6_6 = temp_r6_5 + 1;
                if (temp_r6_6 < p4) {
                    M2C_FIELD(var_r3, s32 *, 0xDE0) = (s32) M2C_FIELD(var_r5_2, s32 *, 0xC);
                } else {
                    M2C_FIELD(var_r3, s32 *, 0xDE0) = 0;
                }
                var_r5_2 += 0x10;
                var_r3 += 0x10;
                var_r6_2 = temp_r6_6 + 1;
                var_ctr_2 -= 1;
            } while (var_ctr_2 != 0);
        } else {
            memset((void*)(((s32)this) + ((p0 * 0x38) + 0xDD4)), 0, 0x20U);
        }
        temp_r4_3 = 1 << temp_r29;
        M2C_FIELD(((s32)this), s32 *, 0x16C0) = (s32) (M2C_FIELD(((s32)this), s32 *, 0x16C0) | temp_r4_3);
        M2C_FIELD(((s32)this), s32 *, 0x1778) = (s32) (M2C_FIELD(((s32)this), s32 *, 0x1778) | temp_r4_3);
    }
    M2C_FIELD(((s32)this), s32 *, 0x16A8) = (s32) (M2C_FIELD(((s32)this), s32 *, 0x16A8) | 4);
    M2C_FIELD(((s32)this), s32 *, 0x1760) = (s32) (M2C_FIELD(((s32)this), s32 *, 0x1760) | 4);
}
}

extern "C++" {
void GSgfxLayer::drawTorus(float p0, unsigned char p1, unsigned char p2) {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(M2C_FIELD(this, s32 *, 0x199C) + 0x1B8));
    GXDrawTorus(p0, p1, p2);
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawOctahedron() {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(M2C_FIELD(this, s32 *, 0x199C) + 0x1B8));
    GXDrawOctahedron();
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawIcosahedron() {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(M2C_FIELD(this, s32 *, 0x199C) + 0x1B8));
    GXDrawIcosahedron();
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawDodecaedron() {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(M2C_FIELD(this, s32 *, 0x199C) + 0x1B8));
    GXDrawDodeca();
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawCylinder(unsigned char p0) {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(M2C_FIELD(this, s32 *, 0x199C) + 0x1B8));
    GXDrawCylinder(p0);
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::drawCube() {
    ((GSgfxLayer*)(this))->FlushState();
    GXSetVtxDescv((const GXVtxDescList *)(M2C_FIELD(this, s32 *, 0x199C) + 0x1B8));
    GXDrawCube();
    ((GSgfxLayer*)(this))->InvalidateState();
}
}

extern "C++" {
void GSgfxLayer::dlDraw(GSgfxDL* p0) {
    s32 temp_r31;

    if (M2C_FIELD(p0, u16 *, 0) & 2) {
        DCStoreRange((register void*)(M2C_FIELD(p0, u8 **, 4)), M2C_FIELD(p0, u32 *, 8));
        M2C_FIELD(p0, u16 *, 0) = (u16) (M2C_FIELD(p0, u16 *, 0) & 0xFFFFFFFD);
    }
    temp_r31 = M2C_FIELD(this, s32 *, 0x199C);
    M2C_FIELD(this, s32 *, 0x199C) = (s32) M2C_FIELD(p0, s32 *, 0xC);
    ((GSgfxLayer*)(this))->FlushState();
    *(s8 *)0xCC008000 = 0x40;
    *(s8 *)0xCC008000 = (signed char)((u8 *) M2C_FIELD(p0, u8 **, 4));
    *(s8 *)0xCC008000 = (u32) M2C_FIELD(p0, u32 *, 8);
    M2C_FIELD(this, s32 *, 0x199C) = temp_r31;
}
}

extern "C++" {
void GSgfxLayer::dlDrawExt(unsigned char* p0, unsigned long p1) {
    M2C_FIELD(M2C_FIELD(this, u8 **, 0x199C), s32 *, 4) = 0;
    ((GSgfxLayer*)(this))->FlushState();
    *(s8 *)0xCC008000 = 0x40;
    *(s8 *)0xCC008000 = (signed char)(p0);
    *(s8 *)0xCC008000 = p1;
}
}

void GSgfxLayer::endSurface() {
    gsgfx_layer_inPrimitive = 0;
}

extern "C++" {
void GSgfxLayer::beginSurface(unsigned short p0) {
    ((GSgfxLayer*)(this))->FlushState();
    *(s8 *)0xCC008000 = M2C_FIELD(this, s32 *, 0x1998) | M2C_FIELD(M2C_FIELD(this, u8 **, 0x199C), s32 *, 4);
    gsgfx_layer_inPrimitive = 1;
    *(s8 *)0xCC008000 = p0;
}
}
