#include <dolphin/types.h>

extern "C" {

s32 _HSD_MemCheckOwn(void* p);

u32 __hsd_rand_seed_default = 1;
u32* __hsd_rand_seed_hold = &__hsd_rand_seed_default;

static inline void HSD_RandNext(void) {
    *__hsd_rand_seed_hold = *__hsd_rand_seed_hold * 214013 + 2531011;
}

void _HSD_RandForgetMemory(void) {
    if (_HSD_MemCheckOwn(__hsd_rand_seed_hold)) {
        __hsd_rand_seed_hold = &__hsd_rand_seed_default;
    }
}

s32 HSD_Randi(s32 max) {
    HSD_RandNext();
    return max * (s32)(*__hsd_rand_seed_hold >> 16) / 65536;
}

f32 HSD_Randf(void) {
    HSD_RandNext();
    return (*__hsd_rand_seed_hold >> 16) / 65536.0f;
}

u32 HSD_Rand(void) {
    HSD_RandNext();
    return *__hsd_rand_seed_hold >> 16;
}

}
