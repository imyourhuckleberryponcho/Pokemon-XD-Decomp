#include <dolphin/types.h>

extern "C" {
void GSmemFree(void* ptr);
void* GSmemAlloc(u32 size);
bool GSmemIsInitialized(void);
}

void operator delete[](void* ptr) {
    void* volatile p = ptr;
    GSmemFree(p);
}

void operator delete(void* ptr) {
    void* volatile p = ptr;
    GSmemFree(p);
}

void* operator new[](size_t size) {
    volatile size_t s = size;
    if (GSmemIsInitialized()) {
        return GSmemAlloc(s);
    }
    return NULL;
}

void* operator new(size_t size) {
    if (GSmemIsInitialized()) {
        if (size < 0x40) {
            volatile s32 unused = 0;
        }
        return GSmemAlloc(size);
    }
    return NULL;
}
