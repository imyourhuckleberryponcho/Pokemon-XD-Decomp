#include <dolphin/types.h>
#include <dolphin/os.h>

extern "C" {

extern u32* __hsd_rand_seed_hold;
void GSmathInitCosTable(void);

static inline void OSInitFastCast(void) {
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr GQR2, r3
        li r3, 5
        oris r3, r3, 5
        mtspr GQR3, r3
        li r3, 6
        oris r3, r3, 6
        mtspr GQR4, r3
        li r3, 7
        oris r3, r3, 7
        mtspr GQR5, r3
    }
}

static inline void OSSetGQR6(register u32 value) {
    asm {
        mtspr GQR6, value
    }
}

void GSmathInit(void) {
    OSInitFastCast();
    OSSetGQR6(0x06070607);
    *__hsd_rand_seed_hold = OSGetTime();
    GSmathInitCosTable();
}

}
