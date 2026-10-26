#include <dolphin/types.h>
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

#pragma peephole off
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
struct FightTrainerKindData;
struct Hero;
struct char16;

struct MenuCBBattleStartWork {
    u32 unk0;
    s32 status;
    u8 unk8[0x140];
};

extern "C" {

extern MenuCBBattleStartWork _menuCBBattleStartWork;

extern "C++" {
struct FightTrainerKindData {
    u8 _draft[1];
};
struct Hero {
    u8 _draft[1];
};
struct char16 {
    u8 _draft[1];
};
struct _struct__menuCBBattleStartWork_0x8 {
     s32 unk0;                             
     s32 unk4;                             
};
struct _struct_menuCBBattleStartDispWork_0x18 {
     s32 unk0;                            
     s32 unk4;                            
     s32 unk8;                            
     s32 unkC;                            
     s32 unk10;                           
     s32 unk14;                           
};
extern "C" {
void GScharCpy(char16*, const char16*);
void GSfsysFree(u32 id);
u8 GSfsysReadIDEX(u32 id, u32 idx, void (*cb)(long, void*, long), void* user, u32 c);
char* GSmsgGetGSchar(u32 msg);
void GSresFreeGroup(u32 grp);
void GSresFreeResource(u32 grp, u32 id);
void* GSresGetResourceAllGroup(u32 id);
s32 GSsndGetStatus(u32 id);
u32 HSD_Rand(void);
static void __sinit_menuCB_BattleStart_cpp();
u8 fightTrainerDB_GetKindDataId(u16 id);
u32 fightTrainerKindDataBiosGetPrefixName(FightTrainerKindData* data);
FightTrainerKindData* fightTrainerKindDataBiosGetPtr(u16 id);
u16* heroBiosGetNamePtr(Hero* hero);
s32 menuCBPokemonEntryLoadTex();
s32 menuCBPokemonEntryTexWorkInit();
u32 menuCB_BattleStartSoundCheck();
void soundOpenPlay(s32, s32, s32);
u32 toolentryGetTrainerBicFaceResID(s32 player, s32 flag);
u32 toolentryGetTrainerSamllFaceResID(s32 player, s32 flag);
s32 toolentryTaisenGetBattleType(void);
u16 toolentryTaisenGetEntryPokemonNum(s32 player);
Hero* toolentryTaisenGetHeroPtr(s32 player);
u16 toolentryTaisenGetPokemonNum(s32 player);
u16 toolentryTaisenGetTrainerDataID(s32 player);
extern s32 jtbl_2154;
}
extern "C++" {
static u8 _menuCBBattleCheckTrainer(long p0, long p1);
static void _menuCBBattleStartDispTrainerTexCallBack(long p0, void* p1, long p2);
static s32 _menuCBBattleStartGetTrainerFaceSize();
static void _menuCBBattleStartSetIndexDouble(long p0, unsigned short p1);
static void _menuCBBattleStartSetIndexMulti(long p0, unsigned short p1);
static void _menuCBBattleStartSetIndexSingle(long p0, unsigned short p1);
static void _menuCBBattleStartSetIndex();
static void _menuCBBattleStartSetTrainerData();
static void _menuCBBattleStartWorkInit();
}
static struct _struct_menuCBBattleStartDispWork_0x18 menuCBBattleStartDispWork[4];
MenuCBBattleStartWork _menuCBBattleStartWork;
s32 menuCBBattleStartResID;
extern "C++" {
extern "C++" {
extern "C++" {
extern "C++" {

extern "C++" {

extern "C" {
void menuCBBattleStartDispTrainerInit();
void menuCBBattleStartInit(s32 p0, s32 p1);
void menuCBBattleStartTrainerFaceFree();
void menuCBBattleStartTrainerLoadTex();
extern s32 jtbl_2145;
extern s32 jtbl_2136;
}

}

extern "C" {

}

}

}
}
}
}

extern "C++" {
extern "C++" {

}

extern "C" {
extern "C" {
extern "C" {

extern "C++" {
struct MenuCBBattleStartTrainerTexture {
    void* texture;
    u32 resource;
};

struct MenuCBBattleStartTrainerTextureState {
    u8 pad0[0xC];
    MenuCBBattleStartTrainerTexture entries[4];
    s32 current;
    s32 count;
};

#pragma dont_inline on

#pragma dont_inline reset
extern "C" {
extern "C" {
static void __sinit_menuCB_BattleStart_cpp() {
}
__declspec(section ".ctors") extern void* const __sinit_menuCB_BattleStart_cpp_reference = __sinit_menuCB_BattleStart_cpp;
}

extern "C" {
void menuCBBattleStartTrainerFaceFree() {
    u8* p;
    u32 group;
    s32 i;

    if (_menuCBBattleStartGetTrainerFaceSize() != 0) {
        group = 0x5C3;
    } else {
        group = 0x5C4;
    }
    GSfsysFree(group);
    GSresFreeGroup(group);
    p = (u8*)&_menuCBBattleStartWork + 0xC;
    if (_menuCBBattleStartGetTrainerFaceSize() == 0) {
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30) = 4;
    } else {
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30) = 2;
    }
    for (i = 0; i < M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30); i++) {
        GSresFreeResource(group, M2C_FIELD(p, u32 *, 4));
        p += 8;
    }
    menuCBBattleStartDispTrainerInit();
}
}

static void _menuCBBattleStartDispTrainerTexCallBack(long unused, void* done, long arg) {
    MenuCBBattleStartTrainerTexture* completed = (MenuCBBattleStartTrainerTexture*)done;
    MenuCBBattleStartTrainerTextureState* state;
    MenuCBBattleStartTrainerTexture* entry;
    u32 resource;
    u32 imageId;
    s32 keepLoading;

    keepLoading = 1;
    if (completed != 0) {
        completed->texture = GSresGetResourceAllGroup(completed->resource);
    }

    state = (MenuCBBattleStartTrainerTextureState*)&_menuCBBattleStartWork;
    do {
        if (state->current == state->count) {
            keepLoading = 0;
        } else {
            if (_menuCBBattleStartGetTrainerFaceSize() != 0) {
                if (state->current % 2 != 0) {
                    resource = toolentryGetTrainerBicFaceResID(1, 0);
                } else {
                    resource = toolentryGetTrainerBicFaceResID(0, 1);
                }
            } else if (state->current < 2) {
                resource = toolentryGetTrainerSamllFaceResID(state->current, 1);
            } else {
                resource = toolentryGetTrainerSamllFaceResID(state->current, 0);
            }

            if (_menuCBBattleStartGetTrainerFaceSize() != 0) {
                imageId = 0x5C3;
            } else {
                imageId = 0x5C4;
            }
            entry = &((MenuCBBattleStartTrainerTextureState*)&_menuCBBattleStartWork)->entries[state->current];
            entry->resource = resource;
            entry->texture = GSresGetResourceAllGroup(entry->resource);
            if (entry->texture != 0) {
                state->current++;
            } else {
                GSfsysReadIDEX(imageId, resource, _menuCBBattleStartDispTrainerTexCallBack, entry, resource);
                keepLoading = 0;
                state->current++;
            }
        }
    } while (keepLoading != 0);
}

extern "C++" {
static s32 _menuCBBattleStartGetTrainerFaceSize() {
    s32 temp_r3;

    temp_r3 = toolentryTaisenGetBattleType();
    return (s32) ((u32) ((2 - temp_r3) | (temp_r3 - 2)) >> 0x1FU);
}
}

extern "C" {
void menuCBBattleStartTrainerLoadTex() {
    _menuCBBattleStartGetTrainerFaceSize();
    M2C_FIELD(&_menuCBBattleStartWork, s8 *, 0x34) = 1;
    _menuCBBattleStartDispTrainerTexCallBack(0, (void*)(NULL), 0);
}
}

extern "C" {
void menuCBBattleStartDispTrainerInit() {
    u8* work = (u8*)&_menuCBBattleStartWork;
    M2C_FIELD(work, s8 *, 0x34) = 0;
    M2C_FIELD(work, s32 *, 0x2C) = 0;
    if (_menuCBBattleStartGetTrainerFaceSize() == 0) {
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30) = 4;
    } else {
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x30) = 2;
    }
    M2C_FIELD(work, s32 *, 0x10) = 0;
    M2C_FIELD(work, s32 *, 0xC) = 0;
    M2C_FIELD(work, s32 *, 0x18) = 0;
    M2C_FIELD(work, s32 *, 0x14) = 0;
    M2C_FIELD(work, s32 *, 0x20) = 0;
    M2C_FIELD(work, s32 *, 0x1C) = 0;
    M2C_FIELD(work, s32 *, 0x28) = 0;
    M2C_FIELD(work, s32 *, 0x24) = 0;
}
}

extern "C" {
void menuCBBattleStartInit(s32 p0, s32 p1) {
    s32 temp_r0;

    _menuCBBattleStartSetTrainerData();
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0) = p0;
    M2C_FIELD(&_menuCBBattleStartWork, s32 *, 4) = p1;
    _menuCBBattleStartSetIndex();
    switch (p1) {
    case 0:
        menuCBPokemonEntryTexWorkInit();
        menuCBPokemonEntryLoadTex();
        temp_r0 = (u16)HSD_Rand() % 3;
        switch (temp_r0) {
        case 0:
            M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x3D2;
            break;
        case 1:
            M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x3F5;
            break;
        case 2:
            M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x3F6;
            break;
        case 3:
        default:
            M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x3F7;
            break;
        }
        soundOpenPlay(M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124), 0, 0xFF);
        return;
    case 1:
        menuCBPokemonEntryTexWorkInit();
        menuCBPokemonEntryLoadTex();
        M2C_FIELD(&_menuCBBattleStartWork, s32 *, 0x124) = 0x5DB;
        soundOpenPlay(0x5DB, 0, 0xFF);
        return;
    }
}
}

static u8 _menuCBBattleCheckTrainer(long p0, long p1) {
    s32 temp_r3;
    u8 var_r31;

    var_r31 = 1;
    temp_r3 = toolentryTaisenGetBattleType();
    if (p1 == 2) {
        if (temp_r3 != 2) {
            var_r31 = 0;
        }
    } else if (temp_r3 == 2) {
        var_r31 = 0;
    }
    return var_r31;
}

extern "C++" {
static void _menuCBBattleStartSetTrainerData() {
    char16* dst;
    u16* name;

    s32 type = toolentryTaisenGetBattleType();
    if (_menuCBBattleCheckTrainer(1, type) != 0) {
        name = heroBiosGetNamePtr((Hero*)(toolentryTaisenGetHeroPtr(1)));
        dst = (char16 *)((u8*)&_menuCBBattleStartWork + 0x12C);
        if (dst != NULL) {
            GScharCpy(dst, (const char16*)name);
        } else {
            GScharCpy(dst, (const char16*)(GSmsgGetGSchar(1U)));
        }
        M2C_FIELD(&_menuCBBattleStartWork, u32 *, 0x144) = fightTrainerKindDataBiosGetPrefixName((FightTrainerKindData*)(fightTrainerKindDataBiosGetPtr((u8) fightTrainerDB_GetKindDataId(toolentryTaisenGetTrainerDataID(1)))));
    }
}
}

s32 menuCBBattleStartGetStatus(void) {
    return _menuCBBattleStartWork.status;
}

void menuCBBattleStartSetStatus(s32 status) {
    _menuCBBattleStartWork.status = status;
}

u32 menuCB_BattleStartSoundCheck() {
    s32 temp_r3;

    temp_r3 = GSsndGetStatus(M2C_FIELD(&_menuCBBattleStartWork, u32 *, 0x124));
    return (u32) ((2 - temp_r3) | (temp_r3 - 2)) >> 0x1FU;
}

static void _menuCBBattleStartWorkInit() {
    struct _struct_menuCBBattleStartDispWork_0x18* p = menuCBBattleStartDispWork;
    for (int i = 0; i < 4; i++, p++) {
        p->unk0 = 0;
        p->unk4 = 1;
        p->unk8 = 2;
        p->unkC = 3;
        p->unk10 = 4;
        p->unk14 = 5;
    }
}

extern "C++" {
static void _menuCBBattleStartSetIndexMulti(long idx, unsigned short kind) {
    u16 i;
    u16 n;
    s32* dst = (s32*)&menuCBBattleStartDispWork[idx];
    for (i = 0; i < kind; i++) {
        dst[i] = i;
    }
    n = kind;
    for (i = kind; i < 6; i++) {
        dst[i] = n++;
    }
}
}

extern "C++" {
static void _menuCBBattleStartSetIndexSingle(long idx, unsigned short kind) {
    struct _struct_menuCBBattleStartDispWork_0x18* dst = &menuCBBattleStartDispWork[idx];
    struct _struct_menuCBBattleStartDispWork_0x18 tbl[6] = {{1, 2, 0, 3, 4, 5}, {2, 0, 1, 3, 4, 5}, {0, 1, 2, 3, 4, 5}, {0, 1, 2, 3, 4, 5}, {0, 1, 2, 3, 4, 5}, {0, 1, 2, 3, 4, 5}};
    struct _struct_menuCBBattleStartDispWork_0x18* src = &tbl[kind - 1];
    *dst = *src;
}
}

extern "C++" {
static void _menuCBBattleStartSetIndexDouble(long idx, unsigned short kind) {
    struct _struct_menuCBBattleStartDispWork_0x18* dst = &menuCBBattleStartDispWork[idx];
    struct _struct_menuCBBattleStartDispWork_0x18 tbl[6] = {{0, 1, 2, 3, 4, 5}, {0, 1, 2, 3, 4, 5}, {0, 1, 2, 3, 4, 5}, {4, 0, 1, 5, 2, 3}, {0, 1, 2, 3, 4, 5}, {0, 1, 2, 3, 4, 5}};
    struct _struct_menuCBBattleStartDispWork_0x18* src = &tbl[kind - 1];
    *dst = *src;
}
}

static void _menuCBBattleStartSetIndex() {
    s32 type = toolentryTaisenGetBattleType();
    u16 nums[4] = {6, 6, 6, 6};
    s32 i;

    _menuCBBattleStartWorkInit();
    switch ((s32) M2C_FIELD(&_menuCBBattleStartWork, s32 *, 4)) {
    case 0:
        for (i = 0; i < 4; i++) {
            nums[i] = toolentryTaisenGetPokemonNum(i);
        }
        break;
    case 1:
        for (i = 0; i < 4; i++) {
            nums[i] = toolentryTaisenGetEntryPokemonNum(i);
        }
        break;
    }
    switch (type) {
    case 0:
        for (i = 0; i < 2; i++) {
            _menuCBBattleStartSetIndexSingle(i, nums[i]);
        }
        break;
    case 1:
        for (i = 0; i < 2; i++) {
            _menuCBBattleStartSetIndexDouble(i, nums[i]);
        }
        break;
    case 2:
        for (i = 0; i < 4; i++) {
            _menuCBBattleStartSetIndexMulti(i, nums[i]);
        }
        break;
    }
}
}
}
}
}
}
}

}
