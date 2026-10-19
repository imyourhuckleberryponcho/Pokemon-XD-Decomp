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
struct GSgfxLayer;
enum Mtx { Mtx_draft_dummy };
enum Mtx44 { Mtx44_draft_dummy };
struct Point3d;
struct Vec;

extern "C" {
// ---- draft declarations ----
struct GSgfxLayer {
    u8 _draft[1];
};
struct Point3d {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
};
struct _struct__spriteWork_0x10 {
     f32 unk0;                            
     f32 unk4;                            
     f32 unk8;                            
     f32 unkC;                            
};
extern "C" {
void C_MTXLookAt(Mtx m, const Point3d* camPos, const Vec* camUp, const Point3d* target);
int GSgfxLayerFindByID(int id);
void GSgfxVideoGetEFBSize(u16* w, u16* h);
void GSmtx44Perspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f);
asm void PSMTXConcat(const register Mtx a, const register Mtx b, register Mtx ab);
GSgfxLayer* floorGetMenuLayerID(void);
void* memcpy(void* dst, const void* src, size_t n);
void spriteClearEnv();
void spriteClearScissor();
void spriteSetOffset(s32 p0, s16 p1, s16 p2);
double tan(double x);
extern void* _TargetLayer;
extern s32 mtxIdent;
}
static u8 _spriteWork[1];
#pragma peephole off
// ---- draft declarations ----


extern "C" {
void spriteGetOffset(s32 p0, s16 *p1, s16 *p2);
void spriteSetEnv(s32 p0);
void spriteSetScissor(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4);
}

void spriteClearScissor() {
    u8 *temp_r3;

    temp_r3 = (unsigned char *)(GSgfxLayerFindByID(M2C_ERROR(/* Read from unset register $r3 */)));
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        M2C_FIELD(temp_r3, s16 *, 0xD70) = 0;
        M2C_FIELD(temp_r3, s16 *, 0xD72) = 0;
        GSgfxVideoGetEFBSize((u16*)(temp_r3 + 0xD74), (u16*)(temp_r3 + 0xD76));
        M2C_FIELD(temp_r3, s32 *, 0x16B8) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x16B8) | 1);
        M2C_FIELD(temp_r3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x16A8) | 2);
        M2C_FIELD(temp_r3, s32 *, 0x1770) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x1770) | 1);
        M2C_FIELD(temp_r3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x1760) | 2);
    }
}
extern "C" {
void spriteSetScissor(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4) {
    f32 temp_f5;
    f32 temp_f6;
    s16 var_r0;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    struct _struct__spriteWork_0x10 *temp_r31;
    u8 *temp_r3;

    if ((u32)(p0) == (s32)floorGetMenuLayerID()) {
        var_r0 = 0;
    } else if (p0 == 7) {
        var_r0 = 1;
    } else {
        var_r0 = 2;
    }
    temp_r31 = (_struct__spriteWork_0x10 *)(&_spriteWork[var_r0]);
    temp_r3 = (unsigned char *)(GSgfxLayerFindByID(p0));
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        temp_f5 = temp_r31->unk8;
        temp_f6 = temp_r31->unkC;
        var_r27 = (s32) ((f32) (s32) (temp_r31->unk0 + (f32) p1) * temp_f5);
        var_r28 = (s32) ((f32) (s32) (temp_r31->unk4 + (f32) p2) * temp_f6);
        var_r29 = (s32) ((f32) p3 * temp_f5);
        var_r30 = (s32) ((f32) p4 * temp_f6);
        if (var_r27 >= 0x280) {
            var_r27 = 0x280;
        }
        if (var_r28 >= 0x1E0) {
            var_r28 = 0x1E0;
        }
        if (var_r29 >= 0x280) {
            var_r29 = 0x280;
        }
        if (var_r30 >= 0x1E0) {
            var_r30 = 0x1E0;
        }
        if (var_r27 < 0) {
            var_r27 = 0;
        }
        if (var_r28 < 0) {
            var_r28 = 0;
        }
        if (var_r29 < 0) {
            var_r29 = 0;
        }
        if (var_r30 < 0) {
            var_r30 = 0;
        }
        M2C_FIELD(temp_r3, u16 *, 0xD70) = (u16) var_r27;
        M2C_FIELD(temp_r3, u16 *, 0xD72) = (u16) var_r28;
        M2C_FIELD(temp_r3, u16 *, 0xD74) = (u16) var_r29;
        M2C_FIELD(temp_r3, u16 *, 0xD76) = (u16) var_r30;
        M2C_FIELD(temp_r3, s32 *, 0x16B8) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x16B8) | 1);
        M2C_FIELD(temp_r3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x16A8) | 2);
        M2C_FIELD(temp_r3, s32 *, 0x1770) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x1770) | 1);
        M2C_FIELD(temp_r3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x1760) | 2);
    }
}
}

#pragma peephole reset
}

extern "C" {
extern "C" {
void spriteClearEnv() {
    u8 *temp_r3;

    temp_r3 = (unsigned char *)(GSgfxLayerFindByID(M2C_ERROR(/* Read from unset register $r3 */)));
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        if ((s32) M2C_FIELD(temp_r3, s32 *, 0x1994) != 1) {
            M2C_FIELD(temp_r3, s32 *, 0x1994) = 1;
            M2C_FIELD(temp_r3, u8 **, 0x1990) = (u8 *) (temp_r3 + ((M2C_FIELD(temp_r3, s32 *, 0x1994) * 0xBC) + 0x1818));
        }
        M2C_FIELD(temp_r3, s32 *, 0x1644) = 1;
        M2C_FIELD(temp_r3, s32 *, 0x1648) = 4;
        M2C_FIELD(temp_r3, s32 *, 0x164C) = 5;
        M2C_FIELD(temp_r3, s32 *, 0x1650) = 5;
        M2C_FIELD(temp_r3, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x170C) | 1);
        M2C_FIELD(temp_r3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(temp_r3, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x17C4) | 1);
        M2C_FIELD(temp_r3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x1760) | 0x40);
    }
}
extern "C" {
void spriteSetEnv(s32 p0) {
    f32 sp34;
    f32 sp40;
    f32 sp44;
    f32 sp54;
    f32 sp58;
    s32 sp6C;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f4;
    s16 var_r0;
    s32 *temp_r3_2;
    s32 *temp_r3_4;
    s32 temp_r3_3;
    struct _struct__spriteWork_0x10 *temp_r31;
    u8 *temp_r31_2;
    u8 *temp_r31_3;
    u8 *temp_r31_4;
    u8 *temp_r3;

    if ((u32)(p0) == (s32)floorGetMenuLayerID()) {
        var_r0 = 0;
    } else if (p0 == 7) {
        var_r0 = 1;
    } else {
        var_r0 = 2;
    }
    temp_r31 = (_struct__spriteWork_0x10 *)(&_spriteWork[var_r0]);
    temp_r3 = (unsigned char *)(GSgfxLayerFindByID(p0));
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        temp_f29 = 640.0f / temp_r31->unk8;
        temp_f28 = 480.0f / temp_r31->unkC;
        temp_f31 = temp_f29 * 0.5f;
        temp_f30 = temp_f28 * 0.5f;
        temp_f2 = temp_f30 / (f32) tan(5.1826099e-315);
        sp1C = 0.0f;
        sp8 = 0.0f;
        temp_f4 = temp_f30 - temp_r31->unk4;
        sp28 = temp_f2;
        temp_f2_2 = temp_f31 - temp_r31->unk0;
        spC = -1.0f;
        sp20 = temp_f2_2;
        sp24 = temp_f4;
        sp14 = temp_f2_2;
        sp18 = temp_f4;
        sp10 = 0.0f;
        C_MTXLookAt((Mtx)((s32) &sp6C), (const Point3d*)((Point3d *) &sp20), (const Vec*)((Vec *) &sp8), (const Point3d*)((Point3d *) &sp14));
        temp_r31_2 = (unsigned char *)(_TargetLayer);
        GSmtx44Perspective((Mtx44)((s32) &sp2C), 30.0f, -(temp_f29 / temp_f28), 0.1f, 30000.0f);
        M2C_FIELD(temp_r31_2, s32 *, 0xD54) = 0;
        M2C_FIELD(temp_r31_2, f32 *, 0xD58) = sp2C;
        M2C_FIELD(temp_r31_2, f32 *, 0xD5C) = sp34;
        M2C_FIELD(temp_r31_2, f32 *, 0xD60) = sp40;
        M2C_FIELD(temp_r31_2, f32 *, 0xD64) = sp44;
        M2C_FIELD(temp_r31_2, f32 *, 0xD68) = sp54;
        M2C_FIELD(temp_r31_2, f32 *, 0xD6C) = sp58;
        M2C_FIELD(temp_r31_2, f32 *, 0x1684) = 0.1f;
        M2C_FIELD(temp_r31_2, f32 *, 0x1688) = 30000.0f;
        if ((u8) M2C_FIELD(temp_r31_2, u8 *, 0x16A7) != 0) {
            if ((u8) M2C_FIELD(temp_r31_2, u8 *, 0x16A6) != 0) {
                M2C_FIELD(temp_r31_2, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x170C) | 0x100);
                M2C_FIELD(temp_r31_2, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x17C4) | 0x100);
            }
            M2C_FIELD(temp_r31_2, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x170C) | 0x40);
            M2C_FIELD(temp_r31_2, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x16A8) | 0x40);
            M2C_FIELD(temp_r31_2, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x17C4) | 0x40);
            M2C_FIELD(temp_r31_2, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x1760) | 0x40);
        }
        M2C_FIELD(temp_r31_2, s32 *, 0x16AC) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x16AC) | 0x20);
        M2C_FIELD(temp_r31_2, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x16A8) | 1);
        M2C_FIELD(temp_r31_2, s32 *, 0x1764) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x1764) | 0x20);
        M2C_FIELD(temp_r31_2, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r31_2, s32 *, 0x1760) | 1);
        temp_r31_3 = M2C_FIELD(_TargetLayer, u8 **, 0x19A0);
        memcpy((void*)(M2C_FIELD(temp_r31_3, s32 **, 4) + 4), (const void*)(&mtxIdent), 0x30U);
        temp_r3_2 = M2C_FIELD(temp_r31_3, s32 **, 4);
        *temp_r3_2 |= 1;
        temp_r31_4 = M2C_FIELD(_TargetLayer, u8 **, 0x19A0);
        temp_r3_3 = (long)(M2C_FIELD(temp_r31_4, s32 **, 4) + 4);
        PSMTXConcat((const Mtx)(temp_r3_3), (const Mtx)((s32) &sp6C), (Mtx)(temp_r3_3));
        temp_r3_4 = M2C_FIELD(temp_r31_4, s32 **, 4);
        *temp_r3_4 |= 1;
        if ((s32) M2C_FIELD(_TargetLayer, s32 *, 0x1994) != 1) {
            M2C_FIELD(_TargetLayer, s32 *, 0x1994) = 1;
            M2C_FIELD(_TargetLayer, u8 **, 0x1990) = (u8 *) ((u8 *)_TargetLayer + ((M2C_FIELD(_TargetLayer, s32 *, 0x1994) * 0xBC) + 0x1818));
        }
        M2C_FIELD(_TargetLayer, s32 *, 0x1644) = 1;
        M2C_FIELD(_TargetLayer, s32 *, 0x1648) = 4;
        M2C_FIELD(_TargetLayer, s32 *, 0x164C) = 5;
        M2C_FIELD(_TargetLayer, s32 *, 0x1650) = 5;
        M2C_FIELD(_TargetLayer, s32 *, 0x170C) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x170C) | 1);
        M2C_FIELD(_TargetLayer, s32 *, 0x16A8) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(_TargetLayer, s32 *, 0x17C4) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x17C4) | 1);
        M2C_FIELD(_TargetLayer, s32 *, 0x1760) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x1760) | 0x40);
        M2C_FIELD(_TargetLayer, s8 *, 0x1656) = 1;
        M2C_FIELD(_TargetLayer, s8 *, 0x1657) = 0;
        M2C_FIELD(_TargetLayer, s8 *, 0x1658) = 1;
        M2C_FIELD(_TargetLayer, s32 *, 0x170C) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x170C) | 4);
        M2C_FIELD(_TargetLayer, s32 *, 0x16A8) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(_TargetLayer, s32 *, 0x17C4) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x17C4) | 4);
        M2C_FIELD(_TargetLayer, s32 *, 0x1760) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x1760) | 0x40);
        M2C_FIELD(_TargetLayer, s32 *, 0x1664) = 7;
        M2C_FIELD(_TargetLayer, s8 *, 0x1670) = 0;
        M2C_FIELD(_TargetLayer, s32 *, 0x1668) = 0;
        M2C_FIELD(_TargetLayer, s32 *, 0x166C) = 7;
        M2C_FIELD(_TargetLayer, s8 *, 0x1671) = 0;
        M2C_FIELD(_TargetLayer, s8 *, 0x1672) = 1;
        M2C_FIELD(_TargetLayer, s32 *, 0x170C) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x170C) | 0x10);
        M2C_FIELD(_TargetLayer, s32 *, 0x16A8) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(_TargetLayer, s32 *, 0x17C4) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x17C4) | 0x10);
        M2C_FIELD(_TargetLayer, s32 *, 0x1760) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x1760) | 0x40);
        M2C_FIELD(_TargetLayer, s8 *, 0x165C) = 0;
        M2C_FIELD(_TargetLayer, s32 *, 0x1660) = 3;
        M2C_FIELD(_TargetLayer, s32 *, 0x170C) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x170C) | 8);
        M2C_FIELD(_TargetLayer, s32 *, 0x16A8) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x16A8) | 0x40);
        M2C_FIELD(_TargetLayer, s32 *, 0x17C4) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x17C4) | 8);
        M2C_FIELD(_TargetLayer, s32 *, 0x1760) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x1760) | 0x40);
        M2C_FIELD(_TargetLayer, s32 *, 0xD8C) = 0;
        M2C_FIELD(_TargetLayer, s32 *, 0x16B8) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x16B8) | 2);
        M2C_FIELD(_TargetLayer, s32 *, 0x16A8) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x16A8) | 2);
        M2C_FIELD(_TargetLayer, s32 *, 0x1770) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x1770) | 2);
        M2C_FIELD(_TargetLayer, s32 *, 0x1760) = (s32) (M2C_FIELD(_TargetLayer, s32 *, 0x1760) | 2);
    }
}
}

extern "C" {
void spriteGetOffset(s32 p0, s16 *p1, s16 *p2) {
    s16 var_r0;
    struct _struct__spriteWork_0x10 *temp_r3;

    if ((u32)(p0) == (s32)floorGetMenuLayerID()) {
        var_r0 = 0;
    } else if (p0 == 7) {
        var_r0 = 1;
    } else {
        var_r0 = 2;
    }
    temp_r3 = (_struct__spriteWork_0x10 *)(&_spriteWork[var_r0]);
    if (p1 != NULL) {
        *p1 = (s16) temp_r3->unk0;
    }
    if (p2 != NULL) {
        *p2 = (s16) temp_r3->unk4;
    }
}
}

extern "C" {
void spriteSetOffset(s32 p0, s16 p1, s16 p2) {
    s16 var_r5;
    struct _struct__spriteWork_0x10 *temp_r4;

    if ((u32)(p0) == (s32)floorGetMenuLayerID()) {
        var_r5 = 0;
    } else if (p0 == 7) {
        var_r5 = 1;
    } else {
        var_r5 = 2;
    }
    temp_r4 = (_struct__spriteWork_0x10 *)(&_spriteWork[var_r5]);
    temp_r4->unk0 = (f32) p1;
    temp_r4->unk4 = (f32) p2;
}
}

}

}
