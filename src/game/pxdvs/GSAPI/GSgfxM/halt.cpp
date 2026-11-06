
#include <dolphin/types.h>

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
#ifndef __MWERKS__
#include <dolphin/os.h>
#endif
#ifdef __MWERKS__
enum OSError { OSError_draft_dummy };
enum OSErrorHandler { OSErrorHandler_draft_dummy };
#endif


extern "C" {
#ifdef __MWERKS__
asm void DCFlushRange(register void* addr, register u32 nBytes);
#endif
#ifdef __MWERKS__
asm BOOL OSDisableInterrupts(void);
#endif
#ifdef __MWERKS__
asm BOOL OSRestoreInterrupts(register BOOL level);
#endif
#ifdef __MWERKS__
OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler);
#endif
void* memcpy(void* dst, const void* src, size_t n);
void* memset(void* dst, int val, size_t n);
#ifdef __MWERKS__
extern s32 __OSFpscrEnableBits;
#endif
void GSgfxHalt(s32 type, s32* context, ...);
void OSPanic(const char* file, s32 line, const char* msg, ...);
}
void GSgfxHaltInit();
static void _haltDSIHandler();
static void _haltISIHandler();
static void _haltAlignmentHandler();
static void _haltProcessException();


static u8 _haltOldDSIHandler[0x74];
static u8 _haltOldISIHandler[0x34];
static u8 _haltOldAlignmentHandler[0x34];
static u8 _haltOldProgramHandler[0x34];
static u8 _haltTex[0x80];
static s32 _haltContext[0xB2];
static u8 _haltCallStack[0x3C];
static s8 _haltHandlerInstalled;
static s32 _haltExceptionType;

#ifdef __MWERKS__
static asm void _haltDSIHandler() {
    nofralloc
    mtsprg 1, r3
    mtsprg 2, r4
    mfdsisr r3
    lis r4, 0x40
    and r3, r3, r4
    cmplwi r3, 0
    beq L_notDSI
    lis r3, _haltOldDSIHandler@h
    ori r3, r3, _haltOldDSIHandler@l
    lis r4, 0x3fff
    ori r4, r4, 0xffff
    and r3, r3, r4
    mtctr r3
    mfsprg r3, 1
    mfsprg r4, 2
    bctr
L_notDSI:
    mfsprg r4, 2
    mfsrr0 r3
    mtsprg 2, r3
    mfsrr1 r3
    mtsprg 3, r3
    mfmsr r3
    ori r3, r3, 0x2030
    mtsrr1 r3
    lis r3, _haltProcessException@h
    ori r3, r3, _haltProcessException@l
    mtsrr0 r3
    li r3, 2
    rfi
}
#else
static void _haltDSIHandler() { }
#endif

#ifdef __MWERKS__
static asm void _haltISIHandler() {
    nofralloc
    mtsprg 1, r3
    mfsrr0 r3
    mtsprg 2, r3
    mfsrr1 r3
    mtsprg 3, r3
    mfmsr r3
    ori r3, r3, 0x2030
    mtsrr1 r3
    lis r3, _haltProcessException@h
    ori r3, r3, _haltProcessException@l
    mtsrr0 r3
    li r3, 3
    rfi
}
#else
static void _haltISIHandler() { }
#endif

#ifdef __MWERKS__
static asm void _haltAlignmentHandler() {
    nofralloc
    mtsprg 1, r3
    mfsrr0 r3
    mtsprg 2, r3
    mfsrr1 r3
    mtsprg 3, r3
    mfmsr r3
    ori r3, r3, 0x2030
    mtsrr1 r3
    lis r3, _haltProcessException@h
    ori r3, r3, _haltProcessException@l
    mtsrr0 r3
    li r3, 5
    rfi
}
#else
static void _haltAlignmentHandler() { }
#endif

#ifdef __MWERKS__
static asm void _haltProcessException() {
    nofralloc
    stw r3, _haltExceptionType
    lis r3, _haltContext@h
    ori r3, r3, _haltContext@l
    stw r0, 0x0(r3)
    stw r1, 0x4(r3)
    stw r2, 0x8(r3)
    stw r4, 0x10(r3)
    stw r5, 0x14(r3)
    stw r6, 0x18(r3)
    stw r7, 0x1c(r3)
    stw r8, 0x20(r3)
    stw r9, 0x24(r3)
    stw r10, 0x28(r3)
    stw r11, 0x2c(r3)
    stw r12, 0x30(r3)
    stw r13, 0x34(r3)
    stw r14, 0x38(r3)
    stw r15, 0x3c(r3)
    stw r16, 0x40(r3)
    stw r17, 0x44(r3)
    stw r18, 0x48(r3)
    stw r19, 0x4c(r3)
    stw r20, 0x50(r3)
    stw r21, 0x54(r3)
    stw r22, 0x58(r3)
    stw r23, 0x5c(r3)
    stw r24, 0x60(r3)
    stw r25, 0x64(r3)
    stw r26, 0x68(r3)
    stw r27, 0x6c(r3)
    stw r28, 0x70(r3)
    stw r29, 0x74(r3)
    stw r30, 0x78(r3)
    stw r31, 0x7c(r3)
    mfsprg r4, 1
    stw r4, 0xc(r3)
    mfsprg r4, 2
    stw r4, 0x198(r3)
    mfsprg r4, 3
    stw r4, 0x19c(r3)
    stfd f0, 0x90(r3)
    stfd f1, 0x98(r3)
    stfd f2, 0xa0(r3)
    stfd f3, 0xa8(r3)
    stfd f4, 0xb0(r3)
    stfd f5, 0xb8(r3)
    stfd f6, 0xc0(r3)
    stfd f7, 0xc8(r3)
    stfd f8, 0xd0(r3)
    stfd f9, 0xd8(r3)
    stfd f10, 0xe0(r3)
    stfd f11, 0xe8(r3)
    stfd f12, 0xf0(r3)
    stfd f13, 0xf8(r3)
    stfd f14, 0x100(r3)
    stfd f15, 0x108(r3)
    stfd f16, 0x110(r3)
    stfd f17, 0x118(r3)
    stfd f18, 0x120(r3)
    stfd f19, 0x128(r3)
    stfd f20, 0x130(r3)
    stfd f21, 0x138(r3)
    stfd f22, 0x140(r3)
    stfd f23, 0x148(r3)
    stfd f24, 0x150(r3)
    stfd f25, 0x158(r3)
    stfd f26, 0x160(r3)
    stfd f27, 0x168(r3)
    stfd f28, 0x170(r3)
    stfd f29, 0x178(r3)
    stfd f30, 0x180(r3)
    stfd f31, 0x188(r3)
    mffs f0
    stfd f0, 0x190(r3)
    sync
    lfd f0, 0x90(r3)
    mtfsb0 0
    mtfsb0 5
    mfspr r4, GQR0
    stw r4, 0x1a4(r3)
    mfspr r4, GQR1
    stw r4, 0x1a8(r3)
    mfspr r4, GQR2
    stw r4, 0x1ac(r3)
    mfspr r4, GQR3
    stw r4, 0x1b0(r3)
    mfspr r4, GQR4
    stw r4, 0x1b4(r3)
    mfspr r4, GQR5
    stw r4, 0x1b8(r3)
    mfspr r4, GQR6
    stw r4, 0x1bc(r3)
    mfspr r4, GQR7
    stw r4, 0x1c0(r3)
    mfcr r4
    stw r4, 0x80(r3)
    mflr r4
    stw r4, 0x84(r3)
    mfctr r4
    stw r4, 0x88(r3)
    mfxer r4
    stw r4, 0x8c(r3)
    mfdsisr r5
    mfdar r6
    lwz r4, 0x19c(r3)
    sync
    mtmsr r4
    sync
    lwz r3, _haltExceptionType
    lis r4, _haltContext@h
    ori r4, r4, _haltContext@l
    b GSgfxHalt
}
#else
static void _haltProcessException() { }
#endif

void OSPanic(const char* file, s32 line, const char* msg, ...) {
}

void GSgfxHalt(s32 type, s32* context, ...) {
}

extern "C++" {
void GSgfxHaltInit() {
    BOOL enabled;

    memset(_haltContext, 0xFF, sizeof(_haltContext));
    OSSetErrorHandler((OSError)2, (OSErrorHandler)GSgfxHalt);
    OSSetErrorHandler((OSError)3, (OSErrorHandler)GSgfxHalt);
    OSSetErrorHandler((OSError)5, (OSErrorHandler)GSgfxHalt);
    OSSetErrorHandler((OSError)0xF, (OSErrorHandler)GSgfxHalt);
    __OSFpscrEnableBits = 0x10;
    OSSetErrorHandler((OSError)0x10, (OSErrorHandler)GSgfxHalt);
    enabled = OSDisableInterrupts();
    memcpy(_haltOldDSIHandler, (void*)0x80000300, sizeof(_haltOldDSIHandler));
    memcpy(_haltOldISIHandler, (void*)0x80000400, sizeof(_haltOldISIHandler));
    memcpy(_haltOldAlignmentHandler, (void*)0x80000600, sizeof(_haltOldAlignmentHandler));
    memcpy(_haltOldProgramHandler, (void*)0x80000700, sizeof(_haltOldProgramHandler));
    memcpy((void*)0x80000300, (void*)_haltDSIHandler, 0x74);
    memcpy((void*)0x80000400, (void*)_haltISIHandler, 0x34);
    memcpy((void*)0x80000600, (void*)_haltAlignmentHandler, 0x34);
    DCFlushRange((void*)0x80000300, 0x1000);
    _haltHandlerInstalled = 1;
    OSRestoreInterrupts(enabled);
}
}
