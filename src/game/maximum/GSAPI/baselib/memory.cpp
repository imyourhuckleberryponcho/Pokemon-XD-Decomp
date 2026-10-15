// Compiled as C (see configure.py): struct copies only match C codegen.
#include <dolphin/types.h>

#pragma pool_strings off

void __assert(const char* file, s32 line, const char* expr);

typedef struct HSD_MemoryCallbacks {
    void* (*alloc)(u32 size, u32 align, u32 flags);
    void (*free)(void* ptr);
    void* unk8;
    void* unkC;
    s32 (*check_own)(void* ptr);
} HSD_MemoryCallbacks;

static HSD_MemoryCallbacks __mem_cb;

void* HSD_Alloc(u32 size) { return __mem_cb.alloc(size, 32, 0); }

void HSD_Free(void* ptr) { __mem_cb.free(ptr); }

s32 _HSD_MemCheckOwn(void* ptr) { return __mem_cb.check_own(ptr); }

void _HSD_MemSetCallbacks(HSD_MemoryCallbacks* cb, u32 size) {
    if (size != sizeof(__mem_cb)) {
        __assert("memory.c", 19, "size == sizeof(__mem_cb)");
    }
    __mem_cb = *cb;
}
