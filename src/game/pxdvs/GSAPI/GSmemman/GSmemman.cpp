// Partial: small wrappers; the rest of the unit is not written yet.
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
enum OSHeapHandle { OSHeapHandle_draft_dummy };

extern "C" {

static u8 _memInitialized;
static u16 _currentLayer;
static u32 _currentHeap = -1;

void* OSAllocFromHeap(s32 heap, u32 size);
void OSFreeToHeap(s32 heap, void* ptr);
s32 OSSetAllocMethodHeap(s32 heap, s32 method);
u32 OSGetHeapFreeSize(s32 heap, s32 a, u32* out);
void OSShrinkHeap(s32 heap, void* ptr, u32 size);
s32 OSGetHeapType(s32 heap);
u32 OSReferentSize(void* ptr);
void* memset(void* dst, int c, u32 n);
u32 GSmemGetCurrentHeap(void);
void* GSmemAllocHeap(s32 heap, u32 size);
void* GSmemAllocAlignHeap(s32 heap, u32 size, u16 align);
void* GSmemAllocFillHeap(s32 heap, u32 size, u8 fill);
void* GSmemAllocClrHeap(s32 heap, u32 size);
void GSmemFreeHeap(s32 heap, void* ptr);
void GSmemShrinkHeap(s32 heap, void* ptr, u32 size);


extern "C" {
// ---- draft declarations ----


extern "C" {
s32 GSmemCheckHeap(s32 p0);
s32 GSmemCreateExternalHeap(s32 p0, s32 p1, s32 p2, s32 p3);
s32 GSmemCreateHeap(void* lo, void* hi);
void GSmemDumpHeap(s32 p0);
void* GSmemInit(void* lo, void* hi, s32);
void GSmemInitPool(void);
u8 GSmemIsInitialized(void);
s32 GSmemVisitHeapAllocated(s32, void*, s32, s32*);
s32 OSCheckHeap(OSHeapHandle heap);
s32 OSCreateExternalHeap(s32, s32, s32, s32);
OSHeapHandle OSCreateHeap(void* start, void* end);
s32 OSGetHeapSize(s32);
void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps);
}
extern "C++" {
static void _dumpHeapVisitor(void* p0, unsigned long p1, void* p2, void* p3);
}

s32 GSmemCheckHeap(s32 heap) {
    return (u32)OSCheckHeap((OSHeapHandle)heap) >> 31 ^ 1;
}
}
u32 GSmemGetLargestFree(void) {
    u32 size;
    OSGetHeapFreeSize(GSmemGetCurrentHeap(), 0, &size);
    return size;
}

u32 GSmemGetSize(void* ptr) {
    if (ptr == 0) {
        return 0;
    }
    return OSReferentSize(ptr);
}

void GSmemFree(void* ptr) {
    if (ptr != 0) {
        GSmemFreeHeap(GSmemGetCurrentHeap(), ptr);
    }
}

void GSmemShrink(void* ptr, u32 size) {
    GSmemShrinkHeap(GSmemGetCurrentHeap(), ptr, size);
}

void* GSmemAllocAlignClr(u32 size, u16 align) {
    void* p = GSmemAllocAlignHeap(GSmemGetCurrentHeap(), size, align);
    if (p != 0) {
        memset(p, 0, size);
    }
    return p;
}

void* GSmemAllocAlignFromEnd(u32 size, u16 align) {
    return GSmemAllocAlignHeap(GSmemGetCurrentHeap(), size, align);
}

void* GSmemAllocAlign(u32 size, u16 align) {
    return GSmemAllocAlignHeap(GSmemGetCurrentHeap(), size, align);
}

void* GSmemAllocClr(u32 size) {
    return GSmemAllocClrHeap(GSmemGetCurrentHeap(), size);
}

void* GSmemAlloc(u32 size) {
    return GSmemAllocHeap(GSmemGetCurrentHeap(), size);
}
extern "C++" {
static void _dumpHeapVisitor(void* p0, unsigned long p1, void* p2, void* p3) {
}
}

extern "C" {
void GSmemDumpHeap(s32 heap) {
    s32 size;
    s32 largest;
    s32 free;
    s32 used;
    s32 count;

    count = 0;
    GSmemVisitHeapAllocated(heap, (void*)_dumpHeapVisitor, 0, &count);
    OSGetHeapFreeSize(heap, (s32)&free, (u32*)&largest);
    size = OSGetHeapSize(heap);
    used = size - free;
}
}


u32 GSmemGetHeapFreeSize(s32 heap, s32 a, u32* out) {
    return OSGetHeapFreeSize(heap, a, out);
}

void GSmemFreeHeap(s32 heap, void* ptr) {
    OSFreeToHeap(heap, ptr);
}

void GSmemShrinkHeap(s32 heap, void* ptr, u32 size) {
    OSShrinkHeap(heap, ptr, size);
}

void* GSmemAllocAlignHeap(s32 heap, u32 size, u16 align) {
    if (align <= 0x20) {
        return GSmemAllocHeap(heap, size);
    }
    return 0;
}

void* GSmemAllocClrHeap(s32 heap, u32 size) {
    return GSmemAllocFillHeap(heap, size, 0);
}

void* GSmemAllocFillHeap(s32 heap, u32 size, u8 fill) {
    void* p = GSmemAllocHeap(heap, size);
    if (p == 0) {
        return 0;
    }
    if (OSGetHeapType(heap) == 0) {
        memset(p, fill, size);
    }
    return p;
}

void* GSmemAllocHeap(s32 heap, u32 size) {
    void* p = OSAllocFromHeap(heap, size);
    return p;
}

s32 GSmemSetAllocMethodHeap(s32 heap, s32 method) {
    return OSSetAllocMethodHeap(heap, method);
}


u16 GSmemGetCurrentLayer(void) {
    return _currentLayer;
}

s32 GSmemSetCurrentHeap(s32 heap) {
    s32 old = GSmemGetCurrentHeap();
    _currentHeap = heap;
    return old;
}

u32 GSmemGetCurrentHeap(void) {
    return _currentHeap;
}
extern "C" {
s32 GSmemCreateExternalHeap(s32 p0, s32 p1, s32 p2, s32 p3) {
    if (!GSmemIsInitialized()) {
        return -1;
    }
    return OSCreateExternalHeap(p0, p1, p2, p3);
}
}

extern "C" {
s32 GSmemCreateHeap(void* start, void* end) {
    if (!GSmemIsInitialized()) {
        return -1;
    }
    return OSCreateHeap(start, end);
}
}

extern "C" {
#pragma optimize_for_size on
void* GSmemInit(void* start, void* end, s32 maxHeaps) {
    void* arena;
    _currentHeap = -1;
    _currentLayer = 0;
    arena = OSInitAlloc(start, end, maxHeaps);
    _memInitialized = 1;
    GSmemInitPool();
    return arena;
}
#pragma optimize_for_size reset
}


u8 GSmemIsInitialized(void) {
    return _memInitialized;
}

}
