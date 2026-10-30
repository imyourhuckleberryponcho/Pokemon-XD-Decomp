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
struct GSgfxVF;

struct GSgfxVFAttr {
    s32 type;
    u32 unk4;
    u32 unk8;
    u8 unkC;
    u8 padD[3];
};
struct GSgfxVFComp {
    s32 type;
    s32 unk4;
};
struct GSgfxVFFmt {
    u16 flags;
    u8 unk2;
    u8 unk3;
    s32 type;
    u32 unk8;
    u32 unkC;
};
struct GSgfxVF {
    u16 flags;
    u8 colorCount;
    u8 textureCount;
    u32 index;
    GSgfxVFAttr attr[27];
    GSgfxVFComp comp[27];
    GSgfxVFFmt fmt[27];
};

extern "C" {

struct GSgfxLayer {
    u8 _draft[1];
    void ResetVertexFormat(GSgfxVF*);
};
struct _struct__vfPredefFmt_0x440 {
     GSgfxVF unk0;                       
     char pad0[0x440 - sizeof(GSgfxVF)];
};
extern "C" {
GSgfxLayer* GSgfxLayerGetLayerList();
GSgfxVF* GSgfxVFBuildTemp(s32 posType, s32 posCnt, u8 hasNormal, s32 normalType, u8 numColors, s32 colorFmt, u8 numTex, s32 texType, s32 texFmt);
void GSgfxVFCreate(GSgfxVF* vf);
void GSgfxVFFree(GSgfxVF* vf);
GSgfxVF* GSgfxVFGetPredef(s32 id);
s32 GSgfxVFHasElement(s32 p0, s32 p1);
void GSgfxVFInit(GSgfxVF* vf);
void GSgfxVFSetArray(GSgfxVF* vf, s32, s32, void*, s32, u32);
void GSgfxVFSetElement(GSgfxVF* vf, s32, s32, s32, s32);
void* memset(void* dst, int val, size_t n);
}
extern "C++" {
void GSgfxVFInit();
}
static u32 _vfAllocIndex;
static GSgfxVF _vfPredefFmt[9] = {
    {
        0x8001, 1, 0, 7,
        { { 9, 1, 4, 0 }, { 0xB, 1, 5, 0 }, { 0xFF, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
        { { 9, 1 }, { 0xB, 1 }, { 0xFF, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        { { 0, 0, 0, 0xFF, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },
    },
    {
        0x8001, 1, 0, 7,
        { { 9, 1, 3, 0 }, { 0xB, 1, 5, 0 }, { 0xFF, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
        { { 9, 1 }, { 0xB, 1 }, { 0xFF, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        { { 0, 0, 0, 0xFF, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },
    },
    {
        0x8001, 1, 0, 7,
        { { 9, 0, 4, 0 }, { 0xB, 1, 5, 0 }, { 0xFF, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
        { { 9, 1 }, { 0xB, 1 }, { 0xFF, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        { { 0, 0, 0, 0xFF, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },
    },
    {
        0x8001, 1, 0, 7,
        { { 9, 0, 3, 0 }, { 0xB, 1, 5, 0 }, { 0xFF, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
        { { 9, 1 }, { 0xB, 1 }, { 0xFF, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        { { 0, 0, 0, 0xFF, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },
    },
    {
        0x8001, 0, 1, 7,
        { { 9, 1, 4, 0 }, { 0xD, 1, 4, 0 }, { 0xFF, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
        { { 9, 1 }, { 0xD, 1 }, { 0xFF, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        { { 0, 0, 0, 0xFF, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },
    },
    {
        0x8001, 1, 1, 7,
        { { 9, 1, 4, 0 }, { 0xB, 1, 5, 0 }, { 0xD, 1, 4, 0 }, { 0xFF, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
        { { 9, 1 }, { 0xB, 1 }, { 0xD, 1 }, { 0xFF, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        { { 0, 0, 0, 0xFF, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },
    },
    {
        0x8001, 1, 1, 7,
        { { 9, 0, 4, 0 }, { 0xB, 1, 5, 0 }, { 0xD, 1, 4, 0 }, { 0xFF, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
        { { 9, 1 }, { 0xB, 1 }, { 0xD, 1 }, { 0xFF, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        { { 0, 0, 0, 0xFF, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },
    },
    {
        0x8001, 1, 1, 7,
        { { 9, 0, 3, 0 }, { 0xB, 1, 5, 0 }, { 0xD, 1, 4, 0 }, { 0xFF, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
        { { 9, 1 }, { 0xB, 1 }, { 0xD, 1 }, { 0xFF, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        { { 0, 0, 0, 0xFF, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },
    },
    {
        0x8001, 0, 1, 7,
        { { 9, 0, 3, 0 }, { 0xD, 1, 0, 0 }, { 0xFF, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
        { { 9, 1 }, { 0xD, 1 }, { 0xFF, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        { { 0, 0, 0, 0xFF, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },
    },
};
static s32 _vfElemTable[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0x19, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14, 0xFF };
static s32 _vfLocal[0x110];

extern "C" {
void GSgfxVFRemoveElement(void* p, s32 type);
}

u8 GSgfxVFGetTextureCount(GSgfxVF* vf) {
    return vf->textureCount;
}

u8 GSgfxVFGetColorCount(GSgfxVF* vf) {
    return vf->colorCount;
}
extern "C" {
static inline GSgfxVFComp* vfFindComp(GSgfxVF* vf, s32 type) {
    GSgfxVFComp* c;
    s32 t;
    for (c = vf->comp; (t = c->type) != 0xFF; c++) {
        if (t == type) {
            return c;
        }
    }
    return NULL;
}

static inline GSgfxVFAttr* vfFindAttr(GSgfxVF* vf, s32 type) {
    GSgfxVFAttr* a;
    s32 t;
    for (a = vf->attr; (t = a->type) != 0xFF; a++) {
        if (t == type) {
            return a;
        }
    }
    return NULL;
}

static inline GSgfxVFFmt* vfFindFmt(GSgfxVF* vf, s32 type) {
    GSgfxVFFmt* f;
    s32 t;
    for (f = vf->fmt; (t = f->type) != 0xFF; f++) {
        if (t == type) {
            return f;
        }
    }
    return NULL;
}

static inline GSgfxVFFmt* vfFindInsertPos(GSgfxVF* vf, u32 idx) {
    s32* p = &_vfElemTable[idx];
    while (idx != 0) {
        GSgfxVFFmt* f;
        idx--;
        f = vfFindFmt(vf, *--p);
        if (f != NULL) {
            return f + 1;
        }
    }
    return NULL;
}

static inline u32 vfElemIndex(s32 type) {
    s32* p;
    u32 idx;
    s32 t;
    for (idx = 0, p = _vfElemTable; (t = *p) != 0xFF; p++, idx++) {
        if (type == t) {
            return idx;
        }
    }
    return 0;
}

void GSgfxVFSetArray(GSgfxVF* vf, s32 type, s32 compData, void* array, s32 size, u32 stride) {
    GSgfxVFFmt* fmt;

    if (array != NULL || stride == 0xFFFFFFFF || (array != NULL && stride != 0)) {
    vfFindComp(vf, type)->unk4 = compData;
    fmt = vfFindFmt(vf, type);
    if (fmt == NULL) {
        GSgfxVFFmt* f;
        GSgfxVFFmt* ins = vfFindInsertPos(vf, vfElemIndex(type));
        if (ins == NULL) {
            ins = vf->fmt;
        }
        for (f = ins; f->type != 0xFF; f++) {
        }
        for (; f >= ins; f--) {
            f[1].type = f->type;
            f[1].unk8 = f->unk8;
            f[1].unk2 = f->unk2;
        }
        fmt = ins;
    }
    fmt->flags = 0;
    fmt->type = type;
    fmt->unk8 = (u32)array;
    fmt->unk2 = size;
    fmt->unkC = stride;
    if ((fmt->unk8 & 0xC0000000) == 0x80000000) {
        fmt->flags |= 1;
    }
    vf->flags |= 0xC;
    }
}
extern "C" {
void GSgfxVFRemoveElement(void* p, s32 type) {
    GSgfxVFFmt* n;
    GSgfxVF* vf = (GSgfxVF*)p;
    u8 removed = 0;
    u8 i;

    GSgfxVFComp* c = vfFindComp(vf, type);
    if (c != NULL) {
        GSgfxVFComp* n = c + 1;
        while (c->type != 0xFF) {
            c->type = n->type;
            c->unk4 = n->unk4;
            n++;
            c++;
        }
        removed = 1;
    }
    if (type >= 9 || type < 0) {
        GSgfxVFAttr* a = vfFindAttr(vf, type);
        if (a != NULL) {
            GSgfxVFAttr* n = a + 1;
            while (a->type != 0xFF) {
                a->type = n->type;
                a->unk4 = n->unk4;
                a->unk8 = n->unk8;
                a->unkC = n->unkC;
                n++;
                a++;
            }
            removed = 1;
        }
        GSgfxVFFmt* f = vfFindFmt(vf, type);
        if (f != NULL) {
            n = f + 1;
            while (f->type != 0xFF) {
                f->type = n->type;
                f->unk8 = n->unk8;
                f->unk2 = n->unk2;
                n++;
                f++;
            }
            removed = 1;
        }
    }
    if (removed != 1) {
        return;
    }
    vf->textureCount = vf->colorCount = i = 0;
    vf->flags &= ~8;
    for (; i < 2; i++) {
        if (vfFindAttr(vf, i + 0xB) == NULL) {
            break;
        }
        vf->colorCount++;
    }
    for (i = 0; i < 8; i++) {
        if (vfFindAttr(vf, i + 0xD) == NULL) {
            break;
        }
        vf->textureCount++;
    }
    for (i = 0; i < 27; i++) {
        if (vf->comp[i].type == 0xFF) {
            break;
        }
        if (vf->comp[i].unk4 == 2 || vf->comp[i].unk4 == 3) {
            vf->flags |= 8;
            break;
        }
    }
    vf->flags |= 6;
}
}

}

extern "C" {
extern "C" {
static inline GSgfxVFComp* vfFindCompInsertPos(GSgfxVF* vf, u32 idx) {
    s32* p = &_vfElemTable[idx];
    while (idx != 0) {
        GSgfxVFComp* c;
        idx--;
        c = vfFindComp(vf, *--p);
        if (c != NULL) {
            return c + 1;
        }
    }
    return NULL;
}

static inline GSgfxVFAttr* vfFindAttrInsertPos(GSgfxVF* vf, u32 idx) {
    s32* p = &_vfElemTable[idx];
    while (idx != 0) {
        GSgfxVFAttr* a;
        idx--;
        a = vfFindAttr(vf, *--p);
        if (a != NULL) {
            return a + 1;
        }
    }
    return NULL;
}

void GSgfxVFSetElement(GSgfxVF* vf, s32 type, s32 compType, s32 compCount, s32 frac) {
    u8 i;

    GSgfxVFRemoveElement(vf, type);
    {
        GSgfxVFComp* ins = vfFindCompInsertPos(vf, vfElemIndex(type));
        GSgfxVFComp* c;
        if (ins == NULL) {
            ins = vf->comp;
        }
        for (c = ins; c->type != 0xFF; c++) {
        }
        for (; c >= ins; c--) {
            c[1].type = c->type;
            c[1].unk4 = c->unk4;
        }
        ins->type = type;
        ins->unk4 = 1;
    }
    if (type >= 9 || type < 0) {
        GSgfxVFAttr* a;
        GSgfxVFAttr* ins = vfFindAttrInsertPos(vf, vfElemIndex(type));
        if (ins == NULL) {
            ins = vf->attr;
        }
        for (a = ins; a->type != 0xFF; a++) {
        }
        for (; a >= ins; a--) {
            a[1].type = a->type;
            a[1].unk4 = a->unk4;
            a[1].unk8 = a->unk8;
            a[1].unkC = a->unkC;
        }
        ins->unk8 = compCount;
        ins->type = type;
        ins->unk4 = compType;
        ins->unkC = frac;
    }
    vf->textureCount = vf->colorCount = i = 0;
    vf->flags &= ~8;
    for (; i < 2; i++) {
        if (vfFindAttr(vf, i + 0xB) == NULL) {
            break;
        }
        vf->colorCount++;
    }
    for (i = 0; i < 8; i++) {
        if (vfFindAttr(vf, i + 0xD) == NULL) {
            break;
        }
        vf->textureCount++;
    }
    for (i = 0; i < 27; i++) {
        if (vf->comp[i].type == 0xFF) {
            break;
        }
        if (vf->comp[i].unk4 == 2 || vf->comp[i].unk4 == 3) {
            vf->flags |= 8;
            break;
        }
    }
    vf->flags |= 6;
}
}

extern "C" {
struct GSgfxVFElement {
    s32 type;
    s32 data;
};

static inline GSgfxVFElement* vfFindElement(GSgfxVF* vf, s32 type) {
    GSgfxVFElement* e;
    s32 t;
    for (e = (GSgfxVFElement*)((u8*)vf + 0x1B8); (t = e->type) != 0xFF; e++) {
        if (t == type) {
            return e;
        }
    }
    return NULL;
}

s32 GSgfxVFHasElement(s32 vf, s32 type) {
    if (vfFindElement((GSgfxVF*)vf, type) != NULL) {
        return 1;
    }
    return 0;
}

void GSgfxVFFree(GSgfxVF* vf) {
    GSgfxLayer* layer;
    if (vf != (GSgfxVF*)_vfLocal && (vf->flags & 1)) {
        vf->flags &= ~1;
        for (layer = GSgfxLayerGetLayerList(); layer != NULL; layer = *(GSgfxLayer**)layer) {
            layer->ResetVertexFormat(vf);
        }
    }
}

}

}

u32 GSgfxVFIsUsed(GSgfxVF* vf) {
    return vf->flags & 1;
}
extern "C" {
GSgfxVF* GSgfxVFGetPredef(s32 p0) {
    return (GSgfxVF *) &_vfPredefFmt[p0];
}
}

extern "C" {
void GSgfxVFCreate(GSgfxVF* vf) {
    int i;
    u32 index = _vfAllocIndex;
    u32 next = index + 1;
    if (next >= 8) {
        next = 0;
    }
    _vfAllocIndex = next;
    vf->index = index;
    vf->flags |= 1;
    for (i = 0; i < 27; i++) {
        vf->attr[i].type = 0xFF;
    }
    for (i = 0; i < 27; i++) {
        vf->comp[i].type = 0xFF;
    }
    for (i = 0; i < 27; i++) {
        vf->fmt[i].type = 0xFF;
    }
    vf->flags |= 6;
}
}

extern "C" {
void GSgfxVFInit(GSgfxVF* p0) {
    memset((void*)(p0), 0, 0x440U);
}
}

extern "C" {
GSgfxVF* GSgfxVFBuildTemp(s32 posType, s32 posCnt, u8 hasNormal, s32 normalType, u8 numColors, s32 colorFmt,
                          u8 numTex, s32 texType, s32 texFmt) {
    GSgfxVF* vf;
    GSgfxVFAttr* attr;
    GSgfxVFComp* comp;
    s32 i;

    if (normalType == 2) {
        return NULL;
    }
    if (numColors > 2) {
        return NULL;
    }
    if (numTex > 8) {
        return NULL;
    }
    if (colorFmt < 0) {
        return NULL;
    }
    if (texFmt > 4) {
        return NULL;
    }
    vf = (GSgfxVF*)_vfLocal;
    attr = &vf->attr[1];
    comp = &vf->comp[1];
    vf->attr[0].type = 9;
    vf->attr[0].unk4 = posType;
    vf->attr[0].unk8 = posCnt;
    vf->attr[0].unkC = 0;
    vf->comp[0].type = 9;
    vf->comp[0].unk4 = 1;
    if (hasNormal == 1) {
        switch (normalType) {
        case 0:
            attr->unk4 = 0;
            attr->type = 0xA;
            comp->type = 0xA;
            break;
        case 1:
            attr->unk4 = 1;
            attr->type = 0x19;
            comp->type = 0x19;
            break;
        }
        attr->unk8 = 4;
        attr->unkC = 0;
        attr++;
        comp->unk4 = 1;
        comp++;
    }
    for (i = 0; i < numColors; i++) {
        switch (colorFmt) {
        case 0:
        case 1:
            attr->unk4 = 0;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            attr->unk4 = 1;
            break;
        }
        attr->type = i + 0xB;
        attr->unk8 = colorFmt;
        attr->unkC = 0;
        attr++;
        comp->type = i + 0xB;
        comp->unk4 = 1;
        comp++;
    }
    for (i = 0; i < numTex; i++) {
        attr->type = i + 0xD;
        attr->unk4 = texType;
        attr->unk8 = texFmt;
        attr->unkC = 0;
        attr++;
        comp->type = i + 0xD;
        comp->unk4 = 1;
        comp++;
    }
    attr->type = 0xFF;
    comp->type = 0xFF;
    vf->fmt[0].type = 0xFF;
    ((GSgfxVF*)_vfLocal)->colorCount = numColors;
    ((GSgfxVF*)_vfLocal)->textureCount = numTex;
    ((GSgfxVF*)_vfLocal)->flags |= 6;
    return (GSgfxVF*)_vfLocal;
}
}

extern "C++" {
void GSgfxVFInit() {
    int i;
    GSgfxVF* vf = (GSgfxVF*)_vfLocal;
    _vfAllocIndex = 0;
    u32 index = _vfAllocIndex;
    u32 next = index + 1;
    if (next >= 8) {
        next = 0;
    }
    _vfAllocIndex = next;
    vf->index = index;
    vf->flags |= 1;
    for (i = 0; i < 27; i++) {
        vf->attr[i].type = 0xFF;
    }
    for (i = 0; i < 27; i++) {
        vf->comp[i].type = 0xFF;
    }
    for (i = 0; i < 27; i++) {
        vf->fmt[i].type = 0xFF;
    }
    vf->flags |= 6;
}
}

}
