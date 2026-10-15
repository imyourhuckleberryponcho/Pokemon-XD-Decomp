// WIP (NonMatching): _memAllocCallback and GSmemGetSysdolAllocator keep locals in saved registers
// (r29-r31) in the original even when not needed; flags, compiler versions and `register` did not help.
#include <dolphin/types.h>

class GSmemPoolAllocator {
public:
    bool isRegistration(void* cell);
    void freeCell(void* cell);
    void* allocCell();
};

extern "C" {
u32 GSmemGetLargestFree(void);
void GSmemFree(void* ptr);
void* GSmemAlloc(u32 size);
GSmemPoolAllocator* GSmemCreatePool(u32 num, u32 size);
void HSD_SetInitParameter(s32 param, ...);
GSmemPoolAllocator* GSmemGetSysdolAllocator(u32 size);
}

// Small sysdolphin (HSD) allocations come from fixed-size pools; larger ones from the heap.
GSmemPoolAllocator* _Sysdol8Allocator;
GSmemPoolAllocator* _Sysdol12Allocator;
GSmemPoolAllocator* _Sysdol20Allocator;
GSmemPoolAllocator* _Sysdol28Allocator;
GSmemPoolAllocator* _Sysdol48Allocator;

static BOOL _memCheckOwnCallback(void* ptr) {
    return TRUE;
}

static void _memClearCallback() {}

static u32 _memGetRemainCallback() {
    return GSmemGetLargestFree();
}

static void _memFreeCallback(void* ptr) {
    if (ptr == NULL) {
        return;
    }
    if (_Sysdol12Allocator->isRegistration(ptr)) {
        _Sysdol12Allocator->freeCell(ptr);
    } else if (_Sysdol20Allocator->isRegistration(ptr)) {
        _Sysdol20Allocator->freeCell(ptr);
    } else if (_Sysdol28Allocator->isRegistration(ptr)) {
        _Sysdol28Allocator->freeCell(ptr);
    } else if (_Sysdol48Allocator->isRegistration(ptr)) {
        _Sysdol48Allocator->freeCell(ptr);
    } else {
        GSmemFree(ptr);
    }
}

static void* _memAllocCallback(unsigned long size, unsigned long, unsigned long) {
    void* ptr;
    GSmemPoolAllocator* allocator;

    if (size == 0) {
        return NULL;
    }
    if (size < 0x40) {
        allocator = GSmemGetSysdolAllocator(size);
        if (allocator != NULL) {
            ptr = allocator->allocCell();
            if (ptr != NULL) {
                return ptr;
            }
        }
    }
    return GSmemAlloc(size);
}

extern "C" {

GSmemPoolAllocator* GSmemGetSysdolAllocator(u32 size) {
    GSmemPoolAllocator* allocator = NULL;
    switch (size) {
    case 8:
        allocator = _Sysdol8Allocator;
        break;
    case 12:
        allocator = _Sysdol12Allocator;
        break;
    case 20:
        allocator = _Sysdol20Allocator;
        break;
    case 28:
        allocator = _Sysdol28Allocator;
        break;
    case 48:
        allocator = _Sysdol48Allocator;
        break;
    }
    return allocator;
}

void GSmemInitSysdolAllocator(void) {
    _Sysdol8Allocator = GSmemCreatePool(4000, 8);
    _Sysdol12Allocator = GSmemCreatePool(8000, 12);
    _Sysdol20Allocator = GSmemCreatePool(3000, 20);
    _Sysdol28Allocator = GSmemCreatePool(5000, 28);
    _Sysdol48Allocator = GSmemCreatePool(5000, 48);
    HSD_SetInitParameter(2, _memAllocCallback, _memFreeCallback, _memGetRemainCallback, _memClearCallback,
                         _memCheckOwnCallback, 0);
}

}
