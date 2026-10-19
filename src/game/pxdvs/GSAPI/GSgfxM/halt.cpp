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
enum OSError { OSError_draft_dummy };
enum OSErrorHandler { OSErrorHandler_draft_dummy };

extern "C++" {
// ---- draft declarations ----


extern "C" {
asm void DCFlushRange(register void* addr, register u32 nBytes);
void GSgfxHalt(s32 p0, s32 *p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, f64 p8, f64 p9, f64 p10, f64 p11, f64 p12, f64 p13, f64 p14, f64 p15);
asm BOOL OSDisableInterrupts(void);
void OSPanic(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, f64 p8, f64 p9, f64 p10, f64 p11, f64 p12, f64 p13, f64 p14, f64 p15);
asm BOOL OSRestoreInterrupts(register BOOL level);
OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler);
void* memcpy(void* dst, const void* src, size_t n);
void* memset(void* dst, int val, size_t n);
extern s32 __OSFpscrEnableBits;
extern s32 sp;
}
extern "C++" {
void GSgfxHaltInit();
static s32 _haltAlignmentHandler();
static s32 _haltDSIHandler();
static s32 _haltISIHandler();
static void _haltProcessException();
}
static s32 _haltContext[0xB2];
static s32 _haltExceptionType;
static s8 _haltHandlerInstalled;
static s32 _haltOldDSIHandler;
static s32 _haltISIHandler() {
    M2C_ERROR(/* unknown instruction: mtsprg 0x1, $r3 */);
    M2C_ERROR(/* unknown instruction: mfsrr0 $r3 */);
    M2C_ERROR(/* unknown instruction: mtsprg 0x2, $r3 */);
    M2C_ERROR(/* unknown instruction: mfsrr1 $r3 */);
    M2C_ERROR(/* unknown instruction: mtsprg 0x3, $r3 */);
    M2C_ERROR(/* unknown instruction: mfmsr $r3 */);
    M2C_ERROR(/* unknown instruction: mtsrr1 $r3 */);
    M2C_ERROR(/* unknown instruction: mtsrr0 $r3 */);
    M2C_ERROR(/* unknown instruction: rfi */);
    return 3;
}
}

extern "C++" {
static s32 _haltAlignmentHandler() {
    M2C_ERROR(/* unknown instruction: mtsprg 0x1, $r3 */);
    M2C_ERROR(/* unknown instruction: mfsrr0 $r3 */);
    M2C_ERROR(/* unknown instruction: mtsprg 0x2, $r3 */);
    M2C_ERROR(/* unknown instruction: mfsrr1 $r3 */);
    M2C_ERROR(/* unknown instruction: mtsprg 0x3, $r3 */);
    M2C_ERROR(/* unknown instruction: mfmsr $r3 */);
    M2C_ERROR(/* unknown instruction: mtsrr1 $r3 */);
    M2C_ERROR(/* unknown instruction: mtsrr0 $r3 */);
    M2C_ERROR(/* unknown instruction: rfi */);
    return 5;
}
}

extern "C++" {
static void _haltProcessException() {
    f32 saved_reg_f14;
    f32 saved_reg_f15;
    f32 saved_reg_f16;
    f32 saved_reg_f17;
    f32 saved_reg_f18;
    f32 saved_reg_f19;
    f32 saved_reg_f20;
    f32 saved_reg_f21;
    f32 saved_reg_f22;
    f32 saved_reg_f23;
    f32 saved_reg_f24;
    f32 saved_reg_f25;
    f32 saved_reg_f26;
    f32 saved_reg_f27;
    f32 saved_reg_f28;
    f32 saved_reg_f29;
    f32 saved_reg_f30;
    f32 saved_reg_f31;
    s32 saved_reg_lr;
    s32 saved_reg_r13;
    s32 saved_reg_r14;
    s32 saved_reg_r15;
    s32 saved_reg_r16;
    s32 saved_reg_r17;
    s32 saved_reg_r18;
    s32 saved_reg_r19;
    s32 saved_reg_r2;
    s32 saved_reg_r20;
    s32 saved_reg_r21;
    s32 saved_reg_r22;
    s32 saved_reg_r23;
    s32 saved_reg_r24;
    s32 saved_reg_r25;
    s32 saved_reg_r26;
    s32 saved_reg_r27;
    s32 saved_reg_r28;
    s32 saved_reg_r29;
    s32 saved_reg_r30;
    s32 saved_reg_r31;
    _haltExceptionType = M2C_ERROR(/* Read from unset register $r3 */);
    M2C_FIELD(_haltContext, s32 *, 0) = M2C_ERROR(/* Read from unset register $r0 */);
    _haltContext[1] = (s32) sp;
    _haltContext[2] = saved_reg_r2;
    _haltContext[4] = M2C_ERROR(/* Read from unset register $r4 */);
    _haltContext[5] = M2C_ERROR(/* Read from unset register $r5 */);
    _haltContext[6] = M2C_ERROR(/* Read from unset register $r6 */);
    _haltContext[7] = M2C_ERROR(/* Read from unset register $r7 */);
    _haltContext[8] = M2C_ERROR(/* Read from unset register $r8 */);
    _haltContext[9] = M2C_ERROR(/* Read from unset register $r9 */);
    _haltContext[0xA] = M2C_ERROR(/* Read from unset register $r10 */);
    _haltContext[0xB] = M2C_ERROR(/* Read from unset register $r11 */);
    _haltContext[0xC] = M2C_ERROR(/* Read from unset register $r12 */);
    _haltContext[0xD] = saved_reg_r13;
    _haltContext[0xE] = saved_reg_r14;
    _haltContext[0xF] = saved_reg_r15;
    _haltContext[0x10] = saved_reg_r16;
    _haltContext[0x11] = saved_reg_r17;
    _haltContext[0x12] = saved_reg_r18;
    _haltContext[0x13] = saved_reg_r19;
    _haltContext[0x14] = saved_reg_r20;
    _haltContext[0x15] = saved_reg_r21;
    _haltContext[0x16] = saved_reg_r22;
    _haltContext[0x17] = saved_reg_r23;
    _haltContext[0x18] = saved_reg_r24;
    _haltContext[0x19] = saved_reg_r25;
    _haltContext[0x1A] = saved_reg_r26;
    _haltContext[0x1B] = saved_reg_r27;
    _haltContext[0x1C] = saved_reg_r28;
    _haltContext[0x1D] = saved_reg_r29;
    _haltContext[0x1E] = saved_reg_r30;
    _haltContext[0x1F] = saved_reg_r31;
    _haltContext[3] = M2C_ERROR(/* unknown instruction: mfsprg $r4, 0x1 */);
    _haltContext[0x66] = M2C_ERROR(/* unknown instruction: mfsprg $r4, 0x2 */);
    _haltContext[0x67] = M2C_ERROR(/* unknown instruction: mfsprg $r4, 0x3 */);
    M2C_FIELD(_haltContext, f64 *, 0x90) = (f64) M2C_ERROR(/* Read from unset register $f0 */);
    M2C_FIELD(_haltContext, f64 *, 0x98) = (f64) M2C_ERROR(/* Read from unset register $f1 */);
    M2C_FIELD(_haltContext, f64 *, 0xA0) = (f64) M2C_ERROR(/* Read from unset register $f2 */);
    M2C_FIELD(_haltContext, f64 *, 0xA8) = (f64) M2C_ERROR(/* Read from unset register $f3 */);
    M2C_FIELD(_haltContext, f64 *, 0xB0) = (f64) M2C_ERROR(/* Read from unset register $f4 */);
    M2C_FIELD(_haltContext, f64 *, 0xB8) = (f64) M2C_ERROR(/* Read from unset register $f5 */);
    M2C_FIELD(_haltContext, f64 *, 0xC0) = (f64) M2C_ERROR(/* Read from unset register $f6 */);
    M2C_FIELD(_haltContext, f64 *, 0xC8) = (f64) M2C_ERROR(/* Read from unset register $f7 */);
    M2C_FIELD(_haltContext, f64 *, 0xD0) = (f64) M2C_ERROR(/* Read from unset register $f8 */);
    M2C_FIELD(_haltContext, f64 *, 0xD8) = (f64) M2C_ERROR(/* Read from unset register $f9 */);
    M2C_FIELD(_haltContext, f64 *, 0xE0) = (f64) M2C_ERROR(/* Read from unset register $f10 */);
    M2C_FIELD(_haltContext, f64 *, 0xE8) = (f64) M2C_ERROR(/* Read from unset register $f11 */);
    M2C_FIELD(_haltContext, f64 *, 0xF0) = (f64) M2C_ERROR(/* Read from unset register $f12 */);
    M2C_FIELD(_haltContext, f64 *, 0xF8) = (f64) M2C_ERROR(/* Read from unset register $f13 */);
    M2C_FIELD(_haltContext, f64 *, 0x100) = (f64) saved_reg_f14;
    M2C_FIELD(_haltContext, f64 *, 0x108) = (f64) saved_reg_f15;
    M2C_FIELD(_haltContext, f64 *, 0x110) = (f64) saved_reg_f16;
    M2C_FIELD(_haltContext, f64 *, 0x118) = (f64) saved_reg_f17;
    M2C_FIELD(_haltContext, f64 *, 0x120) = (f64) saved_reg_f18;
    M2C_FIELD(_haltContext, f64 *, 0x128) = (f64) saved_reg_f19;
    M2C_FIELD(_haltContext, f64 *, 0x130) = (f64) saved_reg_f20;
    M2C_FIELD(_haltContext, f64 *, 0x138) = (f64) saved_reg_f21;
    M2C_FIELD(_haltContext, f64 *, 0x140) = (f64) saved_reg_f22;
    M2C_FIELD(_haltContext, f64 *, 0x148) = (f64) saved_reg_f23;
    M2C_FIELD(_haltContext, f64 *, 0x150) = (f64) saved_reg_f24;
    M2C_FIELD(_haltContext, f64 *, 0x158) = (f64) saved_reg_f25;
    M2C_FIELD(_haltContext, f64 *, 0x160) = (f64) saved_reg_f26;
    M2C_FIELD(_haltContext, f64 *, 0x168) = (f64) saved_reg_f27;
    M2C_FIELD(_haltContext, f64 *, 0x170) = (f64) saved_reg_f28;
    M2C_FIELD(_haltContext, f64 *, 0x178) = (f64) saved_reg_f29;
    M2C_FIELD(_haltContext, f64 *, 0x180) = (f64) saved_reg_f30;
    M2C_FIELD(_haltContext, f64 *, 0x188) = (f64) saved_reg_f31;
    M2C_FIELD(_haltContext, f64 *, 0x190) = (f64) M2C_ERROR(/* unknown instruction: mffs $f0 */);
    M2C_SYNC();
    M2C_ERROR(/* unknown instruction: mtfsb0 lt */);
    M2C_ERROR(/* unknown instruction: mtfsb0 cr1gt */);
    _haltContext[0x69] = M2C_ERROR(/* unknown instruction: mfspr $r4, GQR0 */);
    _haltContext[0x6A] = M2C_ERROR(/* unknown instruction: mfspr $r4, GQR1 */);
    _haltContext[0x6B] = M2C_ERROR(/* unknown instruction: mfspr $r4, GQR2 */);
    _haltContext[0x6C] = M2C_ERROR(/* unknown instruction: mfspr $r4, GQR3 */);
    _haltContext[0x6D] = M2C_ERROR(/* unknown instruction: mfspr $r4, GQR4 */);
    _haltContext[0x6E] = M2C_ERROR(/* unknown instruction: mfspr $r4, GQR5 */);
    _haltContext[0x6F] = M2C_ERROR(/* unknown instruction: mfspr $r4, GQR6 */);
    _haltContext[0x70] = M2C_ERROR(/* unknown instruction: mfspr $r4, GQR7 */);
    _haltContext[0x20] = M2C_ERROR(/* unknown instruction: mfcr $r4 */);
    _haltContext[0x21] = saved_reg_lr;
    _haltContext[0x22] = M2C_ERROR(/* Read from unset register $ctr */);
    _haltContext[0x23] = M2C_ERROR(/* unknown instruction: mfxer $r4 */);
    M2C_SYNC();
    M2C_ERROR(/* unknown instruction: mtmsr $r4 */);
    M2C_SYNC();
    GSgfxHalt(_haltExceptionType, _haltContext, M2C_ERROR(/* unknown instruction: mfdsisr $r5 */), M2C_ERROR(/* unknown instruction: mfdar $r6 */), M2C_ERROR(/* Read from unset register $r7 */), M2C_ERROR(/* Read from unset register $r8 */), M2C_ERROR(/* Read from unset register $r9 */), M2C_ERROR(/* Read from unset register $r10 */), M2C_ERROR(/* Read from unset register $f1 */), M2C_ERROR(/* Read from unset register $f2 */), M2C_ERROR(/* Read from unset register $f3 */), M2C_ERROR(/* Read from unset register $f4 */), M2C_ERROR(/* Read from unset register $f5 */), M2C_ERROR(/* Read from unset register $f6 */), M2C_ERROR(/* Read from unset register $f7 */), M2C_ERROR(/* Read from unset register $f8 */));
}
}

extern "C" {
void OSPanic(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, f64 p8, f64 p9, f64 p10, f64 p11, f64 p12, f64 p13, f64 p14, f64 p15) {
    f64 sp60;
    f64 sp58;
    f64 sp50;
    f64 sp48;
    f64 sp40;
    f64 sp38;
    f64 sp30;
    f64 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;

    if (M2C_ERROR(/* Read from unset register $cr0_eq */)) {
        sp28 = p8;
        sp30 = p9;
        sp38 = p10;
        sp40 = p11;
        sp48 = p12;
        sp50 = p13;
        sp58 = p14;
        sp60 = p15;
    }
    sp8 = p0;
    spC = p1;
    sp10 = p2;
    sp14 = p3;
    sp18 = p4;
    sp1C = p5;
    sp20 = p6;
    sp24 = p7;
}
}

extern "C" {
void GSgfxHalt(s32 p0, s32 *p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, f64 p8, f64 p9, f64 p10, f64 p11, f64 p12, f64 p13, f64 p14, f64 p15) {
    f64 sp60;
    f64 sp58;
    f64 sp50;
    f64 sp48;
    f64 sp40;
    f64 sp38;
    f64 sp30;
    f64 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 *spC;
    s32 sp8;

    if (M2C_ERROR(/* Read from unset register $cr0_eq */)) {
        sp28 = p8;
        sp30 = p9;
        sp38 = p10;
        sp40 = p11;
        sp48 = p12;
        sp50 = p13;
        sp58 = p14;
        sp60 = p15;
    }
    sp8 = p0;
    spC = p1;
    sp10 = p2;
    sp14 = p3;
    sp18 = p4;
    sp1C = p5;
    sp20 = p6;
    sp24 = p7;
}
}

extern "C++" {
void GSgfxHaltInit() {
    s32 temp_r30;

    memset((void*)(&_haltOldDSIHandler + 0x190), 0xFF, 0x2C8U);
    OSSetErrorHandler((OSError)(2), (OSErrorHandler)((s32) GSgfxHalt));
    OSSetErrorHandler((OSError)(3), (OSErrorHandler)((s32) GSgfxHalt));
    OSSetErrorHandler((OSError)(5), (OSErrorHandler)((s32) GSgfxHalt));
    OSSetErrorHandler((OSError)(0xF), (OSErrorHandler)((s32) GSgfxHalt));
    __OSFpscrEnableBits = 0x10;
    OSSetErrorHandler((OSError)(0x10), (OSErrorHandler)((s32) GSgfxHalt));
    temp_r30 = OSDisableInterrupts();
    memcpy((void*)(&_haltOldDSIHandler), (const void*)((u8 *)0x80000300), 0x74U);
    memcpy((void*)(&_haltOldDSIHandler + 0x74), (const void*)((u8 *)0x80000400), 0x34U);
    memcpy((void*)(&_haltOldDSIHandler + 0xA8), (const void*)((u8 *)0x80000600), 0x34U);
    memcpy((void*)(&_haltOldDSIHandler + 0xDC), (const void*)((u8 *)0x80000700), 0x34U);
    memcpy((void*)((u8 *)0x80000300), (const void*)(_haltDSIHandler), 0x74U);
    memcpy((void*)((u8 *)0x80000400), (const void*)(_haltISIHandler), 0x34U);
    memcpy((void*)((u8 *)0x80000600), (const void*)(_haltAlignmentHandler), 0x34U);
    DCFlushRange((register void*)((u8 *)0x80000300), 0x1000U);
    _haltHandlerInstalled = 1;
    OSRestoreInterrupts(temp_r30);
}
}
