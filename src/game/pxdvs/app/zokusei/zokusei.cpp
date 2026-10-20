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
u16 zokuseiGetPokemonSpriteID(PokemonData* pdata, u16 index);
u16 zokuseiGetWazaJoutai(u16 id, u16 target);
s32 zokuseiGetWazaJoutai_PokemonId(u16 p0, u16 p1);
extern u32* pokemon_data_number;
extern u32* zokusei_data_number;
}

// ---- draft declarations ----


extern "C" {
s32 zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16 type, u16* arr, u16 count);
}

u16 zokuseiGetPokemonSpriteID(PokemonData* pdata, u16 index) {
    if (index >= 2) {
        return 0;
    }
    return zokuseiBiosGetSpriteID(pokemonDataBiosGetZokuseiDataId(pdata, index));
}
}

extern "C" {
s32 zokuseiGetAisyouValue(u16 type, u8 attack, u8 side) {
    s32 value;
    u16 result;
    u16 i;
    u16 code1;
    u16 code2;

    value = 0;
    for (i = 0; i < *zokusei_data_number; i++) {
        if (i == 9) {
            continue;
        }
        if (attack == 1) {
            code1 = zokuseiBiosGetWazaJoutai(type, i);
            result = code1;
            if (result == 0x43) {
                if (side != 1) {
                    value -= 10;
                }
            } else if (result == 0x42) {
                if (side != 1) {
                    value -= 10;
                }
            } else if (result == 0x41) {
                if (side != 2) {
                    value += 10;
                }
            }
        } else {
            code2 = zokuseiBiosGetWazaJoutai(i, type);
            result = code2;
            if (result == 0x43) {
                if (side != 2) {
                    value += 10;
                }
            } else if (result == 0x42) {
                if (side != 2) {
                    value += 10;
                }
            } else if (result == 0x41) {
                if (side != 1) {
                    value -= 10;
                }
            }
        }
    }
    return value;
}
s32 zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16 type, u16* arr, u16 count) {
    u16 i;
    u16 countA = 0;
    u16 countB = 0;
    u16 e;
    u16 code;
    u16 result;

    for (i = 0; i < count; i++) {
        if (arr[i] == 9) {
            continue;
        }
        e = arr[i];
        code = zokuseiBiosGetWazaJoutai((u32)type, (u32)e);
        result = code;
        if (result == 0x43) {
            return 0x43;
        }
        if (result == 0x41) {
            countA++;
            continue;
        }
        if (result == 0x42) {
            countB++;
        }
    }
    if (countA == 0 && countB == 0) {
        return 0x3f;
    }
    if (countA == countB) {
        return 0x3f;
    }
    if (countA > countB) {
        return 0x41;
    }
    return 0x42;
}

}

extern "C" {
extern "C" {
s32 zokuseiGetWazaJoutai_PokemonId(u16 type, u16 pokemon) {
    u16 types[4];
    u16 count;
    u8 i;
    u16 id;

    if (pokemon > *pokemon_data_number) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 2; i++) {
        id = pokemonDB_GetZokuseiDataId(pokemon, i);
        if (id != 9) {
            types[count] = id;
            count++;
        }
    }
    return zokuseiGetWazaJoutaiAsDefenseZokuseiAry(type, types, count);
}
}

extern "C" {
u16 zokuseiGetWazaJoutai(u16 id, u16 target) {
    return zokuseiBiosGetWazaJoutai(id, target);
}
}
}
