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
struct DarkPokemon;
struct DeckDarkPokemon;
enum darkPokemonWhere { darkPokemonWhere_draft_dummy };
struct darkpokemonIterateListener;

extern "C" {
// ---- draft declarations ----
struct DarkPokemon {
    u8 _draft[1];
    f32 getDarkPoint() const;
    void setPlace(darkPokemonWhere, unsigned char);
    void setDarkPoint(float);
};
struct DeckDarkPokemon {
    u8 _draft[1];
    bool isScenarioPokemon() const;
};
struct darkpokemonIterateListener {
    u8 _draft[1];
};

extern "C" {
DarkPokemon* darkPokemonGetDarkPokemon(u32);
s32 darkPokemonGetMeetNum();
s32 darkPokemonGetReliveNum(void);
s32 darkPokemonGetSnatchSuccessNum(void);
u8 darkpokemonCheckUnderTaker();
void darkpokemonValInit();
u32 deckGetDarkPokemonSize(void);
DeckDarkPokemon* deckGetDeckDarkPokemon(u32 index);
void deckInitDarkPokemon(void);
void* savedataGetStatus(void* save, s32 kind);
extern s32 __vt__36openDarkPokeInfo;
}
extern "C++" {
s32 darkpokemonScenarioPokemonIterate(darkpokemonIterateListener* p0);
}
s32 __vt__26darkpokemonIterateListener;
u8 darkpokemonCheckUnderTaker() { return 0; }
extern "C" {
s32 darkPokemonGetReliveNum() { return 0; }
extern "C" {
s32 darkPokemonGetSnatchSuccessNum() { return 0; }
extern "C" {
s32 darkPokemonGetMeetNum() { return 0; }
extern "C++" {
s32 darkpokemonScenarioPokemonIterate(darkpokemonIterateListener* p0) {
    u32 var_r31;
    DeckDarkPokemon *temp_r30;
    DarkPokemon *temp_r29;

    if (p0 == NULL) {
        return 0;
    }
    var_r31 = 0;
loop_9:
    if (var_r31 >= deckGetDarkPokemonSize()) {
        return 1;
    }
    temp_r30 = deckGetDeckDarkPokemon(var_r31);
    temp_r29 = darkPokemonGetDarkPokemon(var_r31);
    if ((temp_r30 != NULL) && (temp_r29 != NULL) && (((DeckDarkPokemon*)(temp_r30))->isScenarioPokemon() != 0) && (M2C_FIELD((*(s32*)(p0)), u8 (**)(darkpokemonIterateListener *, u32, DeckDarkPokemon *, DarkPokemon *), 8)(p0, (u16)var_r31, temp_r30, temp_r29) == 0)) {
        return 0;
    }
    var_r31 += 1;
    goto loop_9;
}
}

extern "C" {
void darkpokemonValInit() {
    savedataGetStatus((void*)(NULL), 0xF);
    deckInitDarkPokemon();
}
}

extern "C++" {
void DarkPokemon::setPlace(darkPokemonWhere p0, unsigned char p1) {
    M2C_FIELD(this, s32 *, 0) = (s32) ((M2C_FIELD(this, s32 *, 0) & ~0x38000) | ((p0 << 0xF) & 0x38000));
    M2C_FIELD(this, u8 *, 0x11) = 0U;
    switch (p0) {                                   /* irregular */
    case 1:
        if (p1 <= 6U) {
            M2C_FIELD(this, u8 *, 0x11) = p1;
            return;
        }
        return;
    case 2:
        M2C_FIELD(this, u8 *, 0x11) = p1;
        return;
    case 3:
        M2C_FIELD((u16)this, u8 *, 0x11) = p1;
        return;
    }
}
}

extern "C++" {
f32 DarkPokemon::getDarkPoint() const {
    return (f32) M2C_FIELD(this, s32 *, 0x24);
}
}

extern "C++" {
void DarkPokemon::setDarkPoint(float p0) {
    f32 var_f0;
    s32 temp_r4;

    var_f0 = 65535.0f;
    temp_r4 = (s32) p0;
    if ((f32) temp_r4 < 65535.0f) {
        var_f0 = (f32) temp_r4;
    }
    M2C_FIELD(this, s32 *, 0x24) = (s32) var_f0;
}
}

extern "C" {
DarkPokemon* darkPokemonGetDarkPokemon(u32 p0) {
    u8 *temp_r3;

    temp_r3 = (unsigned char *)(savedataGetStatus((void*)(NULL), 0xF));
    if (p0 < 0x80U) {
        return (DarkPokemon *)(temp_r3 + (p0 * 0x48));
    }
    return NULL;
}
}
}
}
}
}
