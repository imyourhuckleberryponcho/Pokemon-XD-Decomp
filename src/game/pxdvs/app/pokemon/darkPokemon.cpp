// Matching. Dark Pokemon records + iteration over scenario dark Pokemon with function-local listener classes
// (openDarkPokeInfo). Their compiler-numbered names ($39/$29/$19/$6) are mapped onto the target names in
// config/GXXE01/symbols.txt (retail numbers 2060.., a precompiled header shifted its counter).
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
    s32 getStatus() const;
    u8 isSnach() const;
    u8 isRelive() const;
    u16 getCatchFloorId() const;
};
struct DeckDarkPokemon {
    u8 _draft[1];
    bool isScenarioPokemon() const;
    u8 getWorth() const;
};
}
// Callback interface of darkpokemonScenarioPokemonIterate: exec is called for every scenario dark Pokemon
// and stops the iteration when it returns 0.
class darkpokemonIterateListener {
public:
    virtual u8 exec(u32 index, DeckDarkPokemon* deck, DarkPokemon* dark) = 0;
};
extern "C" {

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
}
extern "C++" {
s32 darkpokemonScenarioPokemonIterate(darkpokemonIterateListener* listener);
}
u8 darkpokemonCheckUnderTaker() {
    class openDarkPokeInfo : public darkpokemonIterateListener {
    public:
        s32 count;
        openDarkPokeInfo() : count(0) {}
        virtual u8 exec(u32 index, DeckDarkPokemon* deck, DarkPokemon* dark) {
            if (dark->getStatus() == 2 && !dark->isSnach() && deck->getWorth() && dark->getCatchFloorId() != 0xB5) {
                count++;
            }
            return 1;
        }
    } info;
    darkpokemonScenarioPokemonIterate(&info);
    return info.count != 0;
}
extern "C" {
s32 darkPokemonGetReliveNum() {
    class openDarkPokeInfo : public darkpokemonIterateListener {
    public:
        s32 count;
        openDarkPokeInfo() : count(0) {}
        virtual u8 exec(u32 index, DeckDarkPokemon* deck, DarkPokemon* dark) {
            if (dark->isRelive()) {
                count++;
            }
            return 1;
        }
    } info;
    darkpokemonScenarioPokemonIterate(&info);
    return info.count;
}
extern "C" {
s32 darkPokemonGetSnatchSuccessNum() {
    class openDarkPokeInfo : public darkpokemonIterateListener {
    public:
        s32 count;
        openDarkPokeInfo() : count(0) {}
        virtual u8 exec(u32 index, DeckDarkPokemon* deck, DarkPokemon* dark) {
            if (dark->isSnach()) {
                count++;
            }
            return 1;
        }
    } info;
    darkpokemonScenarioPokemonIterate(&info);
    return info.count;
}
extern "C" {
s32 darkPokemonGetMeetNum() {
    class openDarkPokeInfo : public darkpokemonIterateListener {
    public:
        s32 count;
        openDarkPokeInfo() : count(0) {}
        virtual u8 exec(u32 index, DeckDarkPokemon* deck, DarkPokemon* dark) {
            if (dark->getStatus() > 0) {
                count++;
            }
            return 1;
        }
    } info;
    darkpokemonScenarioPokemonIterate(&info);
    return info.count;
}
extern "C++" {
s32 darkpokemonScenarioPokemonIterate(darkpokemonIterateListener* listener) {
    u32 i;
    if (listener == NULL) {
        return 0;
    }
    for (i = 0; i < deckGetDarkPokemonSize(); i++) {
        DeckDarkPokemon* deck = deckGetDeckDarkPokemon(i);
        DarkPokemon* dark = darkPokemonGetDarkPokemon(i);
        if (deck != NULL && dark != NULL && deck->isScenarioPokemon() && listener->exec(i, deck, dark) == 0) {
            return 0;
        }
    }
    return 1;
}
}

extern "C" {
void darkpokemonValInit() {
    savedataGetStatus((void*)(NULL), 0xF);
    deckInitDarkPokemon();
}
}

extern "C++" {
void DarkPokemon::setPlace(darkPokemonWhere where, unsigned char id) {
    M2C_FIELD(this, s32 *, 0) = (s32) ((M2C_FIELD(this, s32 *, 0) & ~0x38000) | ((where << 0xF) & 0x38000));
    M2C_FIELD(this, u8 *, 0x11) = 0;
    if (where == 1) {
        if (id <= 6) {
            M2C_FIELD(this, u8 *, 0x11) = id;
        }
    } else if (where == 2) {
        M2C_FIELD(this, u8 *, 0x11) = id;
    } else if (where == 3) {
        M2C_FIELD(this, u8 *, 0x11) = id;
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
    s32 point = p0;
    M2C_FIELD(this, s32 *, 0x24) = (s32)((f32)point < 65535.0f ? (f32)point : 65535.0f);
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
