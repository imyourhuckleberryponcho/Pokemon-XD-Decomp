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
struct PokemonData;

extern "C" {
// ---- draft declarations ----
struct PokemonData {
    u8 _draft[1];
};

extern "C" {
u8 pokemonDB_GetZokuseiDataId(u16 id, u16 idx);
u8 pokemonDataBiosGetZokuseiDataId(PokemonData* pdata, u16 index);
u16 zokuseiBiosGetSpriteID(u16 id);
u16 zokuseiBiosGetWazaJoutai(u32 id, u32 target);
s32 zokuseiGetAisyouValue(u16 p0, u8 p1, u8 p2);
s32 zokuseiGetPokemonSpriteID(s32 p0, u16 p1);
void zokuseiGetWazaJoutai(u16 p0, u16 p1);
s32 zokuseiGetWazaJoutai_PokemonId(u16 p0, u16 p1);
extern u32* pokemon_data_number;
extern u32* zokusei_data_number;
}

// ---- draft declarations ----


extern "C" {
s32 zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16 p0, s32 p1, u16 p2);
}

s32 zokuseiGetPokemonSpriteID(s32 p0, u16 p1) {
    s32 sp8;

    sp8 = p0;
    if (p1 >= 2U) {
        return 0;
    }
    return zokuseiBiosGetSpriteID((u16) pokemonDataBiosGetZokuseiDataId((PokemonData*)((PokemonData *) sp8), p1));
}
}

extern "C" {
s32 zokuseiGetAisyouValue(u16 p0, u8 p1, u8 p2) {
    volatile u8 sp8;
    s32 var_r31;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 var_r29;

    var_r31 = 0;
    sp8 = p1;
    var_r29 = 0;
    while (var_r29 < (u32) *zokusei_data_number) {
        if (var_r29 != 9) {
            if (sp8 == 1) {
                temp_r3 = zokuseiBiosGetWazaJoutai((u32) p0, (u32) var_r29);
                switch (temp_r3) {                  /* switch 1; irregular */
                case 0x43:                          /* switch 1 */
                    if (p2 != 1) {
                        var_r31 -= 0xA;
                    }
                    break;
                case 0x42:                          /* switch 1 */
                    if (p2 != 1) {
                        var_r31 -= 0xA;
                    }
                    break;
                case 0x41:                          /* switch 1 */
                    if (p2 != 2) {
                        var_r31 += 0xA;
                    }
                    break;
                }
            } else {
                temp_r3_2 = zokuseiBiosGetWazaJoutai((u32) var_r29, (u32) p0);
                switch (temp_r3_2) {                /* switch 2; irregular */
                case 0x43:                          /* switch 2 */
                    if (p2 != 2) {
                        var_r31 += 0xA;
                    }
                    break;
                case 0x42:                          /* switch 2 */
                    if (p2 != 2) {
                        var_r31 += 0xA;
                    }
                    break;
                case 0x41:                          /* switch 2 */
                    if ((u8)p2 != 1) {
                        var_r31 -= 0xA;
                    }
                    break;
                }
            }
        }
        var_r29 += 1;
    }
    return var_r31;
}
extern "C" {
s32 zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16 p0, s32 p1, u16 p2) {
    u16 spA;
    u16 sp8;
    u16 temp_r3;
    u16 var_r29;
    u16 var_r30;
    u16 var_r31;

    var_r30 = 0;
    var_r29 = 0;
    sp8 = p0;
    var_r31 = 0;
    spA = p2;
loop_9:
    if (var_r31 >= spA) {
        if ((var_r30 == 0) && (var_r29 == 0)) {
            return 0x3F;
        }
        if (var_r30 == var_r29) {
            return 0x3F;
        }
        if (var_r30 > var_r29) {
            return 0x41;
        }
        return 0x42;
    }
    if ((u16) *((u8 *)p1 + ((var_r31 * 2) & 0x1FFFE)) != 9) {
        temp_r3 = zokuseiBiosGetWazaJoutai((u32) sp8, (u32) *((u8 *)p1 + ((var_r31 * 2) & 0x1FFFE)));
        switch (temp_r3) {                          /* irregular */
        case 0x43:
            return 0x43;
        case 0x41:
            var_r30 += 1;
            goto block_8;
        case 0x42:
            var_r29 += 1;
            goto block_8;
        }
    } else {
block_8:
        var_r31 += 1;
        goto loop_9;
    }
}
}

}

extern "C" {
extern "C" {
s32 zokuseiGetWazaJoutai_PokemonId(u16 p0, u16 p1) {
    s32 spA;
    u16 sp8;
    s32 var_r31;
    u16 temp_r3_2;
    u16 var_r27;
    u16 var_r28;
    u16 var_r29;
    u16 var_r30;
    u8 temp_r3;
    u8 var_r26;

    sp8 = p0;
    if (p1 > (u32) *pokemon_data_number) {
        return 0;
    }
    var_r27 = 0;
    var_r26 = 0;
    while (var_r26 < 2U) {
        temp_r3 = pokemonDB_GetZokuseiDataId(p1, (u16) var_r26);
        if (temp_r3 != 9) {
            *(&spA + ((var_r27 * 2) & 0x1FFFE)) = (s16) temp_r3;
            var_r27 += 1;
        }
        var_r26 += 1;
    }
    var_r29 = 0;
    var_r30 = 0;
    var_r28 = 0;
loop_16:
    if (var_r28 >= var_r27) {
        if ((var_r29 == 0) && (var_r30 == 0)) {
            var_r31 = 0x3F;
        } else if (var_r29 == var_r30) {
            var_r31 = 0x3F;
        } else if (var_r29 > var_r30) {
            var_r31 = 0x41;
        } else {
            var_r31 = 0x42;
        }
    } else if (*(&spA + ((var_r28 * 2) & 0x1FFFE)) != 9) {
        temp_r3_2 = zokuseiBiosGetWazaJoutai((u32) sp8, (u32) *(&spA + ((var_r28 * 2) & 0x1FFFE)));
        switch (temp_r3_2) {                        /* irregular */
        case 0x43:
            var_r31 = 0x43;
            break;
        case 0x41:
            var_r29 += 1;
            goto block_15;
        case 0x42:
            var_r30 += 1;
            goto block_15;
        }
    } else {
block_15:
        var_r28 += 1;
        goto loop_16;
    }
    return var_r31;
}
}

extern "C" {
void zokuseiGetWazaJoutai(u16 p0, u16 p1) {
    u16 spA;
    u16 sp8;

    sp8 = p0;
    spA = p1;
    zokuseiBiosGetWazaJoutai((u32) p0, (u32) p1);
}
}
}
