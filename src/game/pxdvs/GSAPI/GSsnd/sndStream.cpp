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
enum ASM { ASM_draft_dummy };
struct SndStream;

extern "C" {
// ---- draft declarations ----
struct SndStream {
    u8 _draft[1];
};

extern "C" {
asm void DCFlushRange(register void* addr, register u32 nBytes);
u32 GSfsysStreamGetCacheSize(void);
s32 GSfsysStreamGetData(u32 gid, u32 id, u32 dst, u32 size, u32 offset, u32 a, u32 b, u32 c);
asm BOOL OSDisableInterrupts(void);
void OSReport(const char* msg, ...);
asm BOOL OSRestoreInterrupts(register BOOL level);
static void _sndStreamARAMUpdate(void *p0, void *p1);
u32 _sndStreamCallback(void*, u32, void*, u32, u32);
void _sndStreamCtrl(SndStream* s, u32 mode);
static void _sndStreamFadePostProcess(void *p0);
void _sndStreamGetData(SndStream* s, void (*cb)());
void _sndStreamGetDataCallback_ACTIVATE();
void _sndStreamGetDataCallback_EXEC_UPDATE();
void _sndStreamGetDataCallback_START();
static u8 _sndStreamNibble_GetHeaderPos(u16 p0);
u32 _sndStreamNibble_HeaderOFF2ON(u32 p0, s32 p1);
u32 _sndStreamNibble_HeaderON2OFF(u32 v);
void _sndStreamPrepareGetData(SndStream* s);
static void _sndStreamPrepareGetDataCallback(u8 p0, u8 p1, void *p2);
static void _sndStreamPrepareGetDataCallback_Exec(void *p0, void *p1, void *p2, u8 p3, u8 p4);
static void _sndStreamPrepareGetData_Exec(void *p0, s32 p1);
static void _sndStreamPrepareGetData_GetNewData(void *p0, void *p1, u8 p2);
static void _sndStreamPrepareGetData_GetOldData(void *p0, s32 p1, void *p2);
void* memcpy(void* dst, const void* src, size_t n);
void* memset(void* dst, int val, size_t n);
s32 sndStreamADPCMParameter(s32, void*);
s32 sndStreamARAMUpdate(s32, u32, u32, s32, s32);
s32 sndStreamActivate(s32);
void sndStreamDeactivate(u32 stid);
s32 sndStreamFrq(s32, s32);
s32 sndStreamMixParameterEx(s32, u8, s32, s32, s32, s32);
s32 sndStreamMixParameterVolume(s32, s32, s32, s32, u8, f32, f32);
extern s32 snd_data;
}

void _sndStreamPrepareGetData(SndStream* p0) {
    SndStream *temp_r0;
    SndStream *var_r4;
    s32 temp_r31;

    temp_r31 = OSDisableInterrupts();
    temp_r0 = M2C_FIELD(p0, SndStream **, 0);
    if (temp_r0 != NULL) {
        var_r4 = temp_r0;
    } else {
        var_r4 = p0;
    }
    if ((u8) M2C_FIELD(((u8*)(var_r4) + (M2C_FIELD(p0, u8 *, 0x3B) << 6) + M2C_FIELD(p0, u8 *, 0x3F)), u8 *, 0xAE) == 0) {
        _sndStreamPrepareGetData_Exec(p0, (s32) var_r4);
    }
    OSRestoreInterrupts(temp_r31);
}
}

extern "C" {
static void _sndStreamPrepareGetData_Exec(void *p0, s32 p1) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD((p1 + (M2C_FIELD(p0, u8 *, 0x3B) << 6)), s32 *, 0xBC);
    switch (temp_r0) {                              /* irregular */
    case 1:
        _sndStreamPrepareGetData_GetNewData(p0, (u8 *) p1, M2C_ERROR(/* Read from unset register $r5 */));
        return;
    case 3:
        _sndStreamPrepareGetData_GetOldData(p0, p1, M2C_ERROR(/* Read from unset register $r5 */));
        /* fallthrough */
    case 2:
        return;
    }
}
}

extern "C" {
static void _sndStreamPrepareGetData_GetOldData(void *p0, s32 p1, void *p2) {
    u8 *temp_r5;

    temp_r5 = (unsigned char *)(p1 + ((M2C_FIELD(p0, u8 *, 0x3B) << 6) + 0x80));
    M2C_FIELD(temp_r5, s32 *, 0x3C) = 4;
    _sndStreamPrepareGetDataCallback_Exec(p0, (u8 *) p1, temp_r5, (u8) M2C_FIELD(temp_r5, s32 *, 0x38), (u8) p2);
}
}

extern "C" {
static void _sndStreamPrepareGetData_GetNewData(void *p0, void *p1, u8 p2) {
    s32 temp_r30;
    u32 var_r7;
    u8 *temp_r31;
    u8 *temp_r5;

    temp_r31 = (u8*)(p1) + ((M2C_FIELD(p0, u8 *, 0x3B) << 6) + 0x80);
    temp_r30 = M2C_FIELD(temp_r31, s32 *, 0x3C);
    M2C_FIELD(temp_r31, s32 *, 0x3C) = 2;
    temp_r5 = (unsigned char *)(M2C_FIELD(p0, s32 *, 0x10) + 0x10000);
    if ((u32) M2C_FIELD(p0, u32 *, 0) != 0U) {
        var_r7 = M2C_FIELD(p1, u32 *, 0x24) + ((u32) M2C_FIELD(p0, u32 *, 0x14) >> 1U);
    } else {
        var_r7 = M2C_FIELD(p1, u32 *, 0x24);
    }
    if (((s32) M2C_FIELD(p1, s32 *, 0x5C) == 0) && ((u32) M2C_FIELD(p0, u32 *, 0x1C) >= (u32) M2C_FIELD(p1, u32 *, 0x4C))) {
        memset((void*)(temp_r5), 0, 0x8000U);
        _sndStreamPrepareGetDataCallback(0U, (u8)p2, p0);
        return;
    }
    if (GSfsysStreamGetData(M2C_FIELD(p1, u32 *, 0x28), M2C_FIELD(p1, u32 *, 0x2C), (u32) temp_r5, 0x8000U, var_r7, (u32) _sndStreamPrepareGetDataCallback, (u32) p2, (u32) p0) == 0) {
        M2C_FIELD(temp_r31, s32 *, 0x3C) = temp_r30;
    }
}
}

extern "C" {
static void _sndStreamPrepareGetDataCallback(u8 p0, u8 p1, void *p2) {
    s32 temp_r4;
    u32 temp_r0_2;
    u32 temp_r3;
    u32 temp_r5;
    u8 *var_r30;
    u8 *temp_r0;
    u8 *var_r29;
    u8 var_r27;

    temp_r0 = M2C_FIELD(p2, u8 **, 0);
    if (temp_r0 != NULL) {
        var_r30 = temp_r0;
        var_r29 = (unsigned char *)(p2);
    } else {
        var_r30 = (unsigned char *)(p2);
        var_r29 = M2C_FIELD(p2, u8 **, 4);
    }
    temp_r4 = M2C_FIELD(p2, u8 *, 0x3B) << 6;
    temp_r3 = _sndStreamNibble_HeaderOFF2ON(M2C_FIELD(p2, u32 *, 0x1C), temp_r4);
    temp_r5 = temp_r3 + 0x10000;
    if (((s32) M2C_FIELD(var_r30, s32 *, 0x5C) == 1) && ((u8) M2C_FIELD(var_r30, u8 *, 0x71) == 1) && (temp_r0_2 = M2C_FIELD(var_r30, s32 *, 0x60) - 2, ((temp_r3 > temp_r0_2) == 0)) && (temp_r0_2 < temp_r5)) {
        var_r27 = _sndStreamNibble_GetHeaderPos(temp_r0_2);
    } else {
        var_r27 = 0;
    }
    M2C_FIELD(p2, u32 *, 0x1C) = (u32) (M2C_FIELD(p2, u32 *, 0x1C) + ((u32) M2C_FIELD(p2, u32 *, 0x18) >> 1U));
    if (((s32) M2C_FIELD(var_r30, s32 *, 0x5C) == 1) && ((u32) M2C_FIELD(p2, u32 *, 0x1C) >= (u32) M2C_FIELD(var_r30, u32 *, 0x78))) {
        M2C_FIELD(p2, u32 *, 0x1C) = (u32) M2C_FIELD(var_r30, u32 *, 0x74);
        M2C_FIELD(var_r30, u8 *, 0x71) = 1U;
    }
    M2C_FIELD(p2, s8 *, 0x3C) = 1;
    if (((u8) M2C_FIELD(var_r30, u8 *, 0x3C) != 0) && ((u8) M2C_FIELD(var_r29, u8 *, 0x3C) != 0)) {
        M2C_FIELD(var_r30, u32 *, 0x24) = (u32) (M2C_FIELD(var_r30, u32 *, 0x24) + M2C_FIELD(var_r30, s32 *, 0x14));
        if ((u32) M2C_FIELD(var_r30, u32 *, 0x24) >= (u32) (M2C_FIELD(var_r30, s32 *, 0x50) & 0x3FFFFFFE)) {
            M2C_FIELD(var_r30, u32 *, 0x24) = 0U;
        } else if ((u32) M2C_FIELD(var_r30, u32 *, 0x24) >= GSfsysStreamGetCacheSize()) {
            M2C_FIELD(var_r30, u32 *, 0x24) = 0U;
        }
        M2C_FIELD(var_r29, u8 *, 0x3C) = 0U;
        M2C_FIELD(var_r30, u8 *, 0x3C) = 0U;
    }
    _sndStreamPrepareGetDataCallback_Exec(p2, var_r30, var_r30 + (temp_r4 + 0x80), var_r27, p1);
}
}

extern "C" {
static void _sndStreamPrepareGetDataCallback_Exec(void *p0, void *p1, void *p2, u8 p3, u8 p4) {
    s32 temp_r8;
    u32 var_r28;
    u32 temp_r7;
    u8 *temp_r31;
    u8 *var_r3;

    temp_r31 = (u8*)(p2) + ((p4 * 4) & 0x3FC);
    var_r28 = 0x8000 - p3;
    temp_r8 = M2C_FIELD(p0, s32 *, 0x10);
    temp_r7 = M2C_FIELD((s32)temp_r31, u32 *, 0x30);
    if (p4 != 0) {
        var_r3 = (unsigned char *)(temp_r8 + (((u32) M2C_FIELD(p0, u32 *, 0x14) >> 1U) + temp_r7));
    } else {
        var_r3 = (unsigned char *)(temp_r8 + temp_r7);
    }
    if ((u32) (temp_r7 + var_r28) > -0x8000U) {
        var_r28 = 0x8000 - temp_r7;
        M2C_FIELD(p2, s32 *, 0x38) = (s32) (p3 + var_r28);
        M2C_FIELD(p2, s32 *, 0x3C) = 3;
    } else {
        M2C_FIELD(p2, s32 *, 0x38) = 0;
        M2C_FIELD(p2, s32 *, 0x3C) = 1;
    }
    memcpy((void*)(var_r3), (const void*)(temp_r8 + 0x10000 + p3), var_r28);
    M2C_FIELD(temp_r31, u32 *, 0x30) = (u32) (M2C_FIELD(temp_r31, u32 *, 0x30) + var_r28);
    if ((u32) M2C_FIELD(temp_r31, u32 *, 0x30) >= -0x8000U) {
        M2C_FIELD(temp_r31, u32 *, 0x30) = 0U;
        M2C_FIELD(((u8 *)p2 + p4), s8 *, 0x2E) = 1;
        return;
    }
    M2C_FIELD(((u8 *)p2 + p4), s8 *, 0x2E) = 0;
}
}

extern "C" {
static u8 _sndStreamNibble_GetHeaderPos(u16 p0) {
    return (u32) ((f64) p0 * 0.5) & 0xFFFFFFF8;
}
}

extern "C" {
u32 _sndStreamNibble_HeaderOFF2ON(u32 p0, s32 p1) {
    return (u32) ((f64) p0 * 1.1428571428571428);
}
}

extern "C" {
u32 _sndStreamNibble_HeaderON2OFF(u32 p0) {
    return (u32) ((f64) p0 * 0.875);
}
}

extern "C" {
u32 _sndStreamCallback(void* p0, u32 p1, void* p2, u32 p3, u32 p4) {
    s32 spC;
    s32 sp8;
    f32 temp_f1;
    f32 temp_f5;
    f32 temp_f6;
    f32 var_f31;
    u8 temp_r4_2;
    u32 temp_r0;
    u32 var_r29;
    u32 var_r30;
    u8 temp_r3;
    u8 temp_r4;
    u16 temp_r6;
    u8 temp_r7;
    u8 temp_r7_2;
    u8 *temp_r3_2;
    u8 *var_r3;
    u8 *var_r3_2;

    temp_r0 = M2C_FIELD(p4, u32 *, 0);
    if (temp_r0 != 0) {
        var_r30 = temp_r0;
        var_r29 = p4;
    } else {
        var_r30 = p4;
        var_r29 = M2C_FIELD(p4, u32 *, 4);
    }
    if ((p0 == NULL) && (p2 == NULL) && (p1 == 0) && (p3 == 0)) {
        OSReport((const char*)("--- Drop Stream Voice!! ---\n"));
        M2C_FIELD(var_r30, s32 *, 8) = 0xD;
        M2C_FIELD(var_r29, s32 *, 8) = 0xD;
        return 0U;
    }
    temp_r3 = M2C_FIELD(p4, u8 *, 0x38);
    if ((u8) M2C_FIELD(p4, u8 *, 0x37) != temp_r3) {
        temp_r6 = M2C_FIELD(p4, u16 *, 0x34);
        if (temp_r6 == 0) {
            M2C_FIELD(p4, u8 *, 0x37) = temp_r3;
            _sndStreamFadePostProcess((u8 *) p4);
        } else {
            temp_r7 = M2C_FIELD(p4, u8 *, 0x3A);
            temp_r4 = M2C_FIELD(p4, u8 *, 0x39);
            temp_f5 = (f32) temp_r3;
            spC = (s32) temp_r7;
            sp8 = 0x43300000;
            temp_f6 = ((temp_f5 - (f32) temp_r7) / (f32) temp_r6) * (f32) (temp_r4 * 0x14);
            M2C_FIELD(p4, u8 *, 0x39) = (u8) (temp_r4 + 1);
            var_f31 = (f32) temp_r7 + temp_f6;
            if ((temp_f6 > 0.0f) && (M2C_ERROR(/* unknown instruction: cror eq, gt, eq */), ((var_f31 == temp_f5) != 0))) {
                var_f31 = temp_f5;
                _sndStreamFadePostProcess((u8 *) p4);
            } else if (temp_f6 < 0.0f) {
                M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
                if (var_f31 == temp_f5) {
                    var_f31 = temp_f5;
                    _sndStreamFadePostProcess((u8 *) p4);
                }
            }
            M2C_FIELD(p4, u8 *, 0x37) = (u8) (s32) var_f31;
        }
    }
    if (((u8) M2C_FIELD(p4, u8 *, 0x3D) == 1) || ((u8) M2C_FIELD(p4, u8 *, 0x3E) == 1)) {
        sndStreamMixParameterVolume(M2C_FIELD(p4, s32 *, 0xC), 0, 0, 0, M2C_ERROR(/* Read from unset register $r7 */), M2C_ERROR(/* Read from unset register $f1 */), M2C_ERROR(/* Read from unset register $f2 */));
    } else {
        temp_r7_2 = M2C_FIELD(p4, u8 *, 0x37);
        temp_f1 = (f32) temp_r7_2 * ((f32) M2C_FIELD((snd_data + (M2C_FIELD(p4, s32 *, 0x30) * 0xC)), u8 *, 1) * 0.0078125f);
        sndStreamMixParameterVolume(M2C_FIELD(p4, s32 *, 0xC), (s32) temp_f1, 0, 0, temp_r7_2, temp_f1, M2C_BITWISE(f32, 4503599627370496.0));
    }
    if ((s32) M2C_FIELD(p4, s32 *, 8) != 9) {
        return 0U;
    }
    if (((s32) M2C_FIELD(var_r30, s32 *, 0x5C) == 0) && ((u8) M2C_FIELD((var_r30 + M2C_FIELD(var_r30, u8 *, 0x3F)), u8 *, 0xAE) == 1) && ((u8) M2C_FIELD((var_r30 + M2C_FIELD(var_r29, u8 *, 0x3F)), u8 *, 0xEE) == 1) && ((u32) (p1 + (p3 + M2C_FIELD(p4, s32 *, 0x20))) >= (u32) M2C_FIELD(var_r30, u32 *, 0x7C))) {
        sndStreamDeactivate(M2C_FIELD(var_r30, u32 *, 0xC));
        M2C_FIELD(var_r30, s32 *, 8) = 0xA;
        sndStreamDeactivate(M2C_FIELD(var_r29, u32 *, 0xC));
        M2C_FIELD(var_r29, s32 *, 8) = 0xA;
        return 0U;
    }
    if ((u32) (p1 + p3) < (u32) ((u32) M2C_FIELD(p4, u32 *, 0x18) >> 1U)) {
        return 0U;
    }
    temp_r4_2 = M2C_FIELD(var_r30, u8 *, 0x3F);
    if (((u8) M2C_FIELD((var_r30 + temp_r4_2), u8 *, 0xAE) == 1) && ((u8) M2C_FIELD((var_r30 + M2C_FIELD(var_r29, u8 *, 0x3F)), u8 *, 0xEE) == 1)) {
        if (temp_r4_2 != 0) {
            var_r3 = M2C_FIELD(var_r30, u8 **, 0x10) + ((u32) M2C_FIELD(var_r30, u32 *, 0x14) >> 1U);
        } else {
            var_r3 = M2C_FIELD(var_r30, u8 **, 0x10);
        }
        DCFlushRange((register void*)(var_r3), (u32) M2C_FIELD(var_r30, u32 *, 0x14) >> 1U);
        _sndStreamARAMUpdate((void *)((u8 *) var_r30), (void *)(var_r30 + ((M2C_FIELD(var_r30, u8 *, 0x3B) << 6) + 0x80)));
        M2C_FIELD((var_r30 + M2C_FIELD(var_r30, u8 *, 0x3B)), s8 *, 0x72) = 1;
        M2C_FIELD(var_r30, u32 *, 0x20) = (u32) (M2C_FIELD(var_r30, u32 *, 0x20) + ((u32) M2C_FIELD(p4, u32 *, 0x18) >> 1U));
        if (((s32) M2C_FIELD(var_r30, s32 *, 0x5C) == 1) && ((u32) M2C_FIELD(var_r30, u32 *, 0x20) >= (u32) M2C_FIELD(var_r30, u32 *, 0x78))) {
            M2C_FIELD(var_r30, u32 *, 0x20) = (u32) M2C_FIELD(var_r30, u32 *, 0x74);
        }
        if ((u8) M2C_FIELD(var_r29, u8 *, 0x3F) != 0) {
            var_r3_2 = M2C_FIELD(var_r29, u8 **, 0x10) + ((u32) M2C_FIELD(var_r29, u32 *, 0x14) >> 1U);
        } else {
            var_r3_2 = M2C_FIELD(var_r29, u8 **, 0x10);
        }
        DCFlushRange((register void*)(var_r3_2), (u32) M2C_FIELD(var_r29, u32 *, 0x14) >> 1U);
        _sndStreamARAMUpdate((void *)((u8 *) var_r29), (void *)(var_r30 + ((M2C_FIELD(var_r29, u8 *, 0x3B) << 6) + 0x80)));
        M2C_FIELD((var_r30 + M2C_FIELD(var_r29, u8 *, 0x3B)), s8 *, 0x72) = 1;
        M2C_FIELD(var_r29, u32 *, 0x20) = (u32) (M2C_FIELD(var_r29, u32 *, 0x20) + ((u32) M2C_FIELD(p4, u32 *, 0x18) >> 1U));
        if (((s32) M2C_FIELD(var_r30, s32 *, 0x5C) == 1) && ((u32) M2C_FIELD(var_r29, u32 *, 0x20) >= (u32) M2C_FIELD(var_r30, u32 *, 0x78))) {
            M2C_FIELD(var_r29, u32 *, 0x20) = (u32) M2C_FIELD(var_r30, u32 *, 0x74);
        }
    }
    temp_r3_2 = (unsigned char *)(var_r30 + M2C_FIELD(p4, u8 *, 0x3B));
    if ((u8) M2C_FIELD((s32)temp_r3_2, u8 *, 0x72) == 1) {
        M2C_FIELD(temp_r3_2, u8 *, 0x72) = 0U;
        return (u32) M2C_FIELD(p4, u32 *, 0x18) >> 1U;
    }
    return 0U;
}
}

extern "C" {
static void _sndStreamFadePostProcess(void *p0) {
    _sndStreamCtrl((SndStream*)((SndStream *) p0), (u32) M2C_FIELD(p0, u8 *, 0x36));
}
}

extern "C" {
void _sndStreamCtrl(SndStream* p0, u32 p1) {
    switch ((s32) (u8) p1) {                        /* irregular */
    case 1:
        M2C_FIELD(p0, s32 *, 8) = 0xA;
        return;
    case 2:
        M2C_FIELD(p0, s8 *, 0x3D) = 1;
        return;
    case 3:
        M2C_FIELD(p0, s8 *, 0x3D) = 1;
        return;
    default:
    case 0:
        M2C_FIELD(p0, s8 *, 0x3D) = 0;
        return;
    }
}
}

extern "C" {
void _sndStreamGetData(SndStream* p0, void (*p1)()) {
    u8 temp_r4;
    SndStream *var_r3;
    s32 temp_r31;
    SndStream *temp_r0;
    u8 *var_r3_2;

    temp_r31 = OSDisableInterrupts();
    temp_r0 = M2C_FIELD(p0, SndStream **, 0);
    if (temp_r0 != NULL) {
        var_r3 = temp_r0;
    } else {
        var_r3 = p0;
    }
    temp_r4 = M2C_FIELD(p0, u8 *, 0x3F);
    if ((u8) M2C_FIELD(((u8*)(var_r3) + (M2C_FIELD(p0, u8 *, 0x3B) << 6) + temp_r4), u8 *, 0xAE) == 0) {
        OSRestoreInterrupts(temp_r31);
        return;
    }
    if (temp_r4 != 0) {
        var_r3_2 = M2C_FIELD(p0, u8 **, 0x10) + ((u32) M2C_FIELD(p0, u32 *, 0x14) >> 1U);
    } else {
        var_r3_2 = M2C_FIELD(p0, u8 **, 0x10);
    }
    DCFlushRange((register void*)(var_r3_2), (u32) M2C_FIELD(p0, u32 *, 0x14) >> 1U);
    if (p1 != NULL) {
        ((s32 (*)(s32, s32, SndStream *)) p1)(0, 0, p0);
    }
    OSRestoreInterrupts(temp_r31);
}
}

extern "C" {
void _sndStreamGetDataCallback_ACTIVATE() {
    u8 *var_r31;
    u8 temp_r7;
    u8 *temp_r0_2;
    u8 *temp_r30;
    u8 *var_r29;
    volatile s32 temp_r0;

    temp_r30 = M2C_ERROR(/* Read from unset register $r5 */);
    temp_r0 = M2C_FIELD(M2C_ERROR(/* Read from unset register $r5 */), s32 *, 8);
    if (temp_r0 < 8) {
        if (temp_r0 < 6) {
            return;
        }
        temp_r0_2 = M2C_FIELD(temp_r30, u8 **, 0);
        if (temp_r0_2 != NULL) {
            var_r29 = temp_r0_2;
            var_r31 = temp_r30;
        } else {
            var_r29 = temp_r30;
            var_r31 = M2C_FIELD(temp_r30, u8 **, 4);
        }
        temp_r7 = M2C_FIELD(temp_r30, u8 *, 0x3B);
        sndStreamMixParameterEx(M2C_FIELD(temp_r30, s32 *, 0xC), M2C_FIELD(temp_r30, u8 *, 0x37), 0x7F & ((s32) (-(s32) temp_r7 | temp_r7) >> 0x1F), 0, 0, 0);
        sndStreamFrq(M2C_FIELD(temp_r30, s32 *, 0xC), M2C_FIELD(var_r29, s32 *, 0x48));
        sndStreamADPCMParameter(M2C_FIELD(temp_r30, s32 *, 0xC), var_r29 + ((M2C_FIELD(temp_r30, u8 *, 0x3B) << 6) + 0x80));
        M2C_FIELD(temp_r30, s32 *, 8) = 8;
        if (((s32) M2C_FIELD(var_r29, s32 *, 8) == 8) && ((s32) M2C_FIELD(var_r31, s32 *, 8) == 8)) {
            _sndStreamARAMUpdate(var_r29, var_r29 + ((M2C_FIELD(var_r29, u8 *, 0x3B) << 6) + 0x80));
            sndStreamActivate(M2C_FIELD(var_r29, s32 *, 0xC));
            M2C_FIELD(var_r29, s32 *, 8) = 9;
            _sndStreamARAMUpdate(var_r31, var_r29 + ((M2C_FIELD(var_r31, u8 *, 0x3B) << 6) + 0x80));
            sndStreamActivate(M2C_FIELD(var_r31, s32 *, 0xC));
            M2C_FIELD(var_r31, s32 *, 8) = 9;
        }
    }
}
}

extern "C" {
void _sndStreamGetDataCallback_START() { }
extern "C" {
void _sndStreamGetDataCallback_EXEC_UPDATE() { }
extern "C" {
static void _sndStreamARAMUpdate(void *p0, void *p1) {
    u32 var_r4;

    if ((u8) M2C_FIELD((s32)p0, u8 *, 0x3F) != 0) {
        var_r4 = (u32) M2C_FIELD(p0, u32 *, 0x18) >> 1U;
    } else {
        var_r4 = 0;
    }
    sndStreamARAMUpdate(M2C_FIELD(p0, s32 *, 0xC), var_r4, (u32) M2C_FIELD(p0, u32 *, 0x18) >> 1U, 0, 0);
    M2C_FIELD(((u8 *)p1 + M2C_FIELD(p0, u8 *, 0x3F)), s8 *, 0x2E) = 0;
    M2C_FIELD(p0, u8 *, 0x3F) = (u8) (M2C_FIELD(p0, u8 *, 0x3F) ^ 1);
}
}
}
}
