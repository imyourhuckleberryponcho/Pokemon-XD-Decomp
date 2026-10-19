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
struct GSCOLSYS2_HUMAN;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
struct GSgfxVF;
struct GSvec;
struct GSwalkHit;
struct PeopleWork;
struct Vec;
struct tagPeopleWork;

extern "C" {
// ---- draft declarations ----
struct GSCOLSYS2_HUMAN {
    u8 _draft[1];
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSvec {
    u8 _draft[1];
};
struct GSwalkHit {
    u8 _draft[1];
};
struct PeopleWork {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
};
struct tagPeopleWork {
    u8 _draft[1];
    bool isFollower() const;
    bool isHero() const;
};

extern "C" {
void GScameraLoadActiveCameraMatrix(GSgfxLayerID id);
void* GScolsys2GetCurFloor();
s32 GScolsys2HumanAddCurrentFloor(s32 *p0, void *p1);
s32 GScolsys2HumanCollision(s32 p0, s32 p1, s32 p2, s32 p3);
void GScolsys2HumanDispColision();
void GScolsys2HumanEnable(s32 id);
f32 GScolsys2HumanGetHumanRadius(s32 p0);
f32 GScolsys2HumanGetWalkHeight(void *p0);
f32 GScolsys2HumanGetWalkHighest(void *p0);
s32 GScolsys2WalkGetHeight(GSvec* pos, GSwalkHit* outHits);
void GSgfxBeginSurface(unsigned short num);
void GSgfxBlendMode(int type, u32 src, u32 dst);
void GSgfxColor4u8(u8 r, u8 g, u8 b, u8 a);
void GSgfxCullMode(u32 mode);
void GSgfxEndSurface(void);
void GSgfxLayerSetActive(int id);
void GSgfxPixelMode(u8 colorUpdate, u8 alphaUpdate, u8 dither);
void GSgfxSetLineWidth(f32 width);
void GSgfxSetPrimitiveType(u32 type);
void GSgfxSetupRenderAndSelect(GSgfxVF* vf);
s32 GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32);
void GSgfxVertex3f(f32 x, f32 y, f32 z);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
f32 PSVECDistance(const register Vec* a, const register Vec* b);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double cos(double x);
u8 gimmickBoxFixDistanceForPushBox(f32*, s32, f32, f32, f32);
u8 gimmickBoxIsBox(s32);
s32 heroGetFollower();
s32 heroMoveGetHeroPos(s32*);
void* peopleBiosGetPosPtr(PeopleWork* work);
u32 peopleGetHumanID(s32, s32);
void peopleGetPos(s32, s32, GSvec*);
f32 peopleGetTalkDistance(s32, s32);
s32 peopleSearchID();
double sin(double x);
extern f32 __float_nan;
extern s32 fabs;
}
extern "C++" {
static u8 checkCollisionHeadToHead(GSCOLSYS2_HUMAN* p0, GSCOLSYS2_HUMAN* p1, GSvec* p2, GSvec* p3);
static u8 checkCollision(GSCOLSYS2_HUMAN* p0, int p1, GSvec* p2, GSvec* p3, GSvec* p4);
}

f32 GScolsys2HumanGetHumanRadius(s32 p0) {
    s32 saved_reg_r31;
    s32 var_r0;
    u8 *temp_r3;
    u8 *temp_r4;
    u8 *var_r31;

    var_r31 = (unsigned char *)(saved_reg_r31);
    if ((p0 < 0) || (p0 >= 0x30)) {
        var_r0 = 4;
    } else {
        temp_r3 = (unsigned char *)(GScolsys2GetCurFloor());
        if (temp_r3 == NULL) {
            var_r0 = 1;
        } else {
            temp_r4 = temp_r3 + ((p0 * 0x14) + 0xA00);
            if (!(M2C_FIELD(temp_r4, u16 *, 0x10) & 1)) {
                var_r0 = 4;
            } else {
                var_r31 = temp_r4;
                var_r0 = 0;
            }
        }
    }
    if (var_r0 != 0) {
        return 0.0f;
    }
    return M2C_FIELD(var_r31, f32 *, 8);
}
}

extern "C" {
void GScolsys2HumanDispColision() {
    f32 sp18;
    f32 sp14;
    f32 sp10;
    s32 sp8;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f4;
    s32 var_r29;
    s32 var_r29_2;
    u16 temp_r3_2;
    u8 *temp_r3;
    u8 *var_r28;

    temp_r3 = (unsigned char *)(GScolsys2GetCurFloor());
    if (temp_r3 != NULL) {
        GSgfxLayerSetActive(2);
        GScameraLoadActiveCameraMatrix((GSgfxLayerID)(2));
        GSgfxCullMode(0U);
        sp8 = 0;
        GSgfxSetupRenderAndSelect((GSgfxVF*)(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0)));
        GSgfxBlendMode(1, 4U, 5U);
        GSgfxPixelMode(1U, 1U, 1U);
        GSgfxSetLineWidth(2.0f);
        var_r28 = temp_r3 + 0xA00;
loop_10:
        if (var_r28 != (u8 *) (temp_r3 + 0xDC0)) {
            temp_r3_2 = M2C_FIELD(var_r28, u16 *, 0x10);
            if ((temp_r3_2 & 1) && !(temp_r3_2 & 2)) {
                sp18 = 0.0f;
                sp14 = 0.0f;
                sp10 = 0.0f;
                peopleGetPos(M2C_FIELD(var_r28, s32 *, 0), M2C_FIELD(var_r28, s32 *, 4), (GSvec*)((GSvec *) &sp10));
                GSgfxSetPrimitiveType(0xA0U);
                GSgfxBeginSurface(0x12U);
                GSgfxVertex3f(sp10, 0.1f + sp14, sp18);
                GSgfxColor4u8(0U, 0x7FU, 0x7FU, 0xC0U);
                var_r29 = 0;
                do {
                    temp_f27 = 0.3926991f * (f32) var_r29;
                    temp_f28 = (f32) sin((f64) temp_f27);
                    temp_f4 = M2C_FIELD(var_r28, f32 *, 8);
                    GSgfxVertex3f((temp_f4 * (f32) cos((f64) temp_f27)) + sp10, 0.1f + sp14, (temp_f4 * temp_f28) + sp18);
                    GSgfxColor4u8(0U, 0x7FU, 0x7FU, 0xC0U);
                    var_r29 += 1;
                } while (var_r29 < 0x11);
                GSgfxEndSurface();
                GSgfxSetPrimitiveType(0xB0U);
                GSgfxBeginSurface(0x11U);
                var_r29_2 = 0;
                temp_f26 = M2C_FIELD(var_r28, f32 *, 8) + peopleGetTalkDistance(M2C_FIELD(var_r28, s32 *, 0), M2C_FIELD(var_r28, s32 *, 4));
                do {
                    temp_f27_2 = 0.3926991f * (f32) var_r29_2;
                    temp_f28_2 = (f32) sin((f64) temp_f27_2);
                    GSgfxVertex3f((temp_f26 * (f32) cos((f64) temp_f27_2)) + sp10, 0.15f + sp14, (temp_f26 * temp_f28_2) + sp18);
                    GSgfxColor4u8(0x7FU, 0x7FU, 0xFFU, 0xC0U);
                    var_r29_2 += 1;
                } while (var_r29_2 < 0x11);
                GSgfxEndSurface();
            }
            var_r28 += 0x14;
            goto loop_10;
        }
    }
}
}

extern "C++" {
static u8 checkCollisionHeadToHead(GSCOLSYS2_HUMAN* p0, GSCOLSYS2_HUMAN* p1, GSvec* p2, GSvec* p3) { return 0; }
extern "C++" {
#pragma peephole off
static u8 checkCollision(GSCOLSYS2_HUMAN* p0, int p1, GSvec* p2, GSvec* p3, GSvec* p4) {
    s32 sp18;
    s32 sp1C;
    s32 unksp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    GSCOLSYS2_HUMAN *var_r28;
    s32 var_r29;
    s32 var_r30;
    u16 temp_r3;
    u8 *temp_r31;

    sp8 = M2C_FIELD(p3, f32 *, 0);
    spC = M2C_FIELD(p3, f32 *, 4);
    sp10 = M2C_FIELD(p3, f32 *, 8);
    temp_r31 = (unsigned char *)(GScolsys2GetCurFloor());
    var_r29 = 0;
loop_1:
    var_r28 = (GSCOLSYS2_HUMAN *)(temp_r31 + 0xA00);
    var_r30 = 0;
loop_2:
    if ((var_r30 == p1) || (temp_r3 = M2C_FIELD(var_r28, u16 *, 0x10), (((temp_r3 & 1) == 0) != 0)) || (temp_r3 & 2) || (checkCollisionHeadToHead((GSCOLSYS2_HUMAN*)(var_r28), (GSCOLSYS2_HUMAN*)(p0), (GSvec*)((GSvec *) &sp8), (GSvec*)(&unksp14)) == 0)) {
        var_r30 += 1;
        var_r28 += 0x14;
        if (var_r30 < 0x30) {
            goto loop_2;
        }
    }
    if (var_r30 < 0x30) {
        var_r29 += 1;
        sp8 = unksp14;
        spC = sp18;
        sp10 = sp1C;
        if (var_r29 < 0xA) {
            goto loop_1;
        }
    }
    if (var_r29 <= 0) {
        return 0U;
    }
    if (p4 != NULL) {
        M2C_FIELD(p4, f32 *, 0) = sp8;
        M2C_FIELD(p4, f32 *, 4) = spC;
        M2C_FIELD(p4, f32 *, 8) = sp10;
    }
    return 1U;
}
#pragma peephole reset
}

extern "C" {
s32 GScolsys2HumanCollision(s32 p0, s32 p1, s32 p2, s32 p3) {
    s32 saved_reg_r31;
    s32 unksp14;
    s32 unksp20;
    s32 unksp8;
    GSCOLSYS2_HUMAN *temp_r4;
    GSCOLSYS2_HUMAN *var_r31;
    f32 temp_f1;
    f32 var_f27;
    f32 var_f28;
    f32 var_f29;
    s32 var_r3;
    u8 *temp_r3;

    var_r31 = (GSCOLSYS2_HUMAN *)(saved_reg_r31);
    if ((p0 < 0) || (p0 >= 0x30)) {
        var_r3 = 4;
    } else {
        temp_r3 = (unsigned char *)(GScolsys2GetCurFloor());
        if (temp_r3 == NULL) {
            var_r3 = 1;
        } else {
            temp_r4 = (GSCOLSYS2_HUMAN *)(temp_r3 + ((p0 * 0x14) + 0xA00));
            if (!(M2C_FIELD(temp_r4, u16 *, 0x10) & 1)) {
                var_r3 = 4;
            } else {
                var_r31 = temp_r4;
                var_r3 = 0;
            }
        }
    }
    if (var_r3 != 0) {
        return var_r3;
    }
    temp_f1 = PSVECDistance((const register Vec*)((Vec *) p1), (const register Vec*)((Vec *) p2));
    if (temp_f1 > 0.0f) {
        var_f29 = M2C_FIELD(var_r31, f32 *, 8) / temp_f1;
        if (var_f29 > 1.0f) {
            var_f29 = 1.0f;
        }
    } else {
        var_f29 = 0.0f;
    }
    PSVECSubtract((const register Vec*)((Vec *) p2), (const register Vec*)((Vec *) p1), (register Vec*)(&unksp20));
    var_f28 = 0.0f;
loop_21:
    if (!(var_f28 < 1.0f)) {
        goto block_22;
    }
    var_f27 = var_f28 + var_f29;
    if (var_f27 > 1.0f) {
        var_f27 = 1.0f;
    }
    PSVECScale((const register Vec*)(&unksp20), (register Vec*)(&unksp14), var_f28);
    PSVECAdd((const register Vec*)(&unksp14), (const register Vec*)((Vec *) p1), (register Vec*)(&unksp14));
    PSVECScale((const register Vec*)(&unksp20), (register Vec*)(&unksp8), var_f27);
    PSVECAdd((const register Vec*)(&unksp8), (const register Vec*)((Vec *) p1), (register Vec*)(&unksp8));
    if (checkCollision((GSCOLSYS2_HUMAN*)(var_r31), p0, (GSvec*)(&unksp14), (GSvec*)(&unksp8), (GSvec*)((GSvec *) p3)) != 0) {
        return 6;
    }
    M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
    if (var_f29 != 0.0f) {
        var_f28 += var_f29;
        goto loop_21;
    }
block_22:
    return 7;
}
}

extern "C" {
void GScolsys2HumanEnable(s32 p0) {
    s32 saved_reg_r31;
    s32 var_r3;
    u8 *temp_r3;
    u8 *temp_r4;
    u8 *var_r31;

    var_r31 = (unsigned char *)(saved_reg_r31);
    if ((p0 < 0) || (p0 >= 0x30)) {
        var_r3 = 4;
    } else {
        temp_r3 = (unsigned char *)(GScolsys2GetCurFloor());
        if (temp_r3 == NULL) {
            var_r3 = 1;
        } else {
            temp_r4 = temp_r3 + ((p0 * 0x14) + 0xA00);
            if (!(M2C_FIELD(temp_r4, u16 *, 0x10) & 1)) {
                var_r3 = 4;
            } else {
                var_r31 = temp_r4;
                var_r3 = 0;
            }
        }
    }
    if (var_r3 != 0) {
        return;
    }
    if ((u8) M2C_ERROR(/* Read from unset register $r4 */) != 0) {
        M2C_FIELD(var_r31, u16 *, 0x10) = (u16) (M2C_FIELD(var_r31, u16 *, 0x10) & 0xFFFFFFFD);
    } else {
        M2C_FIELD(var_r31, u16 *, 0x10) = (u16) (M2C_FIELD(var_r31, u16 *, 0x10) | 2);
    }
}
}

extern "C" {
s32 GScolsys2HumanAddCurrentFloor(s32 *p0, void *p1) {
    s32 temp_r5;
    s32 var_ctr;
    s32 var_r6;
    u32 temp_r0;
    u8 *temp_r3;
    u8 *temp_r4;
    u8 *temp_r4_2;
    u8 *var_r4;

    temp_r3 = (unsigned char *)(GScolsys2GetCurFloor());
    if (temp_r3 == NULL) {
        return 1;
    }
    var_r4 = temp_r3;
    var_r6 = 0;
    var_ctr = 6;
loop_3:
    if (M2C_FIELD(var_r4, u16 *, 0xA10) & 1) {
        var_r6 += 1;
        if (M2C_FIELD(var_r4, u16 *, 0xA24) & 1) {
            var_r6 += 1;
            if (M2C_FIELD(var_r4, u16 *, 0xA38) & 1) {
                var_r6 += 1;
                if (M2C_FIELD(var_r4, u16 *, 0xA4C) & 1) {
                    var_r6 += 1;
                    if (M2C_FIELD(var_r4, u16 *, 0xA60) & 1) {
                        var_r6 += 1;
                        if (M2C_FIELD(var_r4, u16 *, 0xA74) & 1) {
                            var_r6 += 1;
                            if (M2C_FIELD(var_r4, u16 *, 0xA88) & 1) {
                                var_r6 += 1;
                                if (M2C_FIELD(var_r4, u16 *, 0xA9C) & 1) {
                                    var_r4 += 0xA0;
                                    var_r6 += 1;
                                    var_ctr -= 1;
                                    if (var_ctr != 0) {
                                        goto loop_3;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (var_r6 >= 0x30) {
        return 5;
    }
    temp_r5 = var_r6 * 0x14;
    temp_r4 = temp_r3 + temp_r5;
    M2C_FIELD(temp_r4, s32 *, 0xA00) = (s32) M2C_FIELD(p1, s32 *, 0);
    M2C_FIELD(temp_r4, u32 *, 0xA04) = (u32) M2C_FIELD(p1, u32 *, 4);
    temp_r0 = M2C_FIELD(p1, u32 *, 4);
    if ((temp_r0 == 0x65U) || (temp_r0 == 0x68U) || (temp_r0 == 0x69U)) {
        M2C_FIELD((temp_r3 + temp_r5), f32 *, 0xA08) = 3.0f;
    } else {
        M2C_FIELD(temp_r4, f32 *, 0xA08) = (f32) M2C_FIELD(p1, f32 *, 8);
    }
    temp_r4_2 = temp_r3 + temp_r5;
    M2C_FIELD(temp_r4_2, f32 *, 0xA0C) = (f32) M2C_FIELD(p1, f32 *, 0xC);
    M2C_FIELD(temp_r4_2, u16 *, 0xA10) = 0U;
    M2C_FIELD(temp_r4_2, u16 *, 0xA10) = (u16) (M2C_FIELD(temp_r4_2, u16 *, 0xA10) | 1);
    *p0 = var_r6;
    return 0;
}
}

extern "C" {
f32 GScolsys2HumanGetWalkHeight(void *p0) { return 0; }
extern "C" {
f32 GScolsys2HumanGetWalkHighest(void *p0) {
    s32 unksp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 *var_r4;
    f32 temp_f0;
    f32 var_f1;
    s32 temp_r3;
    s32 var_ctr;

    sp8 = M2C_FIELD(p0, f32 *, 0);
    spC = M2C_FIELD(p0, f32 *, 4);
    sp10 = M2C_FIELD(p0, f32 *, 8);
    temp_r3 = GScolsys2WalkGetHeight((GSvec*)((GSvec *) &sp8), (GSwalkHit*)(&unksp14));
    if (temp_r3 >= 2) {
        var_r4 = (float *)(&unksp14);
        var_f1 = -1000000.0f;
        var_ctr = temp_r3;
        if (temp_r3 > 0) {
            do {
                temp_f0 = *var_r4;
                if (var_f1 < temp_f0) {
                    var_f1 = temp_f0;
                }
                var_r4 += 0xC;
                var_ctr -= 1;
            } while (var_ctr != 0);
            return var_f1;
        }
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return var_f1;
    }
    if (temp_r3 > 0) {
        return unksp14;
    }
    var_f1 = 0.0f;
    return var_f1;
}
}
}
}
