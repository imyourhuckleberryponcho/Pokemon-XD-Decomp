#include <dolphin/types.h>

#pragma peephole off

struct AddsubEntry {
    u32 v[5];
};

struct PokemonPartData {
    u32 v[6];
};

struct AiData {
    u32 v[8];
};

extern "C" {

AddsubEntry* fightTrainerAiValueAddsubDataBiosGetPtr(u32 id);
PokemonPartData* fightTrainerPokemonPartDataBiosGetPtr(u16 id);
AiData* fightTrainerAiDataBiosGetPtr(u16 id);
s32 menuOpenCustom(s32 menuID, ...);
void menuCloseCustom(s32 menuID, s32, s32);
s32 menuOpen(s32 menuID, s32);
s32 menuGetCursorItemID(s32 menuID);
u32 fightTrainerGetStatus(void* trainer, u16 id, u32 kind, u32 arg);
void fightTrainerSetStatus(void* trainer, u16 id, u32 kind, u32 arg, u32 value);
u8 menuSubOpenNumberInput(u32 value, s32* out, u8 digits, s16 x, s16 y, bool close);
void menuSubCloseNumberInput(void);
s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, bool initial);
s32 dbgMenuFightGetZokuseiDataId(u32 id);
s32 dbgMenuFightGetWazaTypeId(u8 type);

void dbgMenuFightTrainerDataStatusInputDigit(u16 id, u32 field, u32 index, s32 maximum, s32 minimum);
void dbgMenuFightTrainerDataStatusInputFlag(u16 id, u32 field);

}

static AddsubEntry _old_fight_trainer_ai_value_addsub_data[0x2D7];

extern "C" {

s32 dbgMenuFightTrainerAiAddsubDataComboEditSub(void) {
    u32 index;
    AddsubEntry* src;
    AddsubEntry* dst;
    s32 result;

    index = 0;
    while ((u16)index < 0x2D7) {
        src = fightTrainerAiValueAddsubDataBiosGetPtr(index);
        dst = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
        index++;
        *dst = *src;
    }

    while (1) {
        result = menuOpenCustom(0x1b, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1b, 0, 1);

            index = 0;
            while ((u16)index < 0x2D7) {
                dst = fightTrainerAiValueAddsubDataBiosGetPtr(index);
                src = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
                index++;
                *dst = *src;
            }

            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
            } else {
                menuCloseCustom(0x55, 0, 1);
                menuCloseCustom(0x1b, 0, 1);
                return 1;
            }
        }
    }
}

s32 dbgMenuFightTrainerAiAddsubDataItemEditSub(void) {
    u32 index;
    AddsubEntry* src;
    AddsubEntry* dst;
    s32 result;

    index = 0;
    while ((u16)index < 0x2D7) {
        src = fightTrainerAiValueAddsubDataBiosGetPtr(index);
        dst = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
        index++;
        *dst = *src;
    }

    while (1) {
        result = menuOpenCustom(0x1a, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1a, 0, 1);

            index = 0;
            while ((u16)index < 0x2D7) {
                dst = fightTrainerAiValueAddsubDataBiosGetPtr(index);
                src = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
                index++;
                *dst = *src;
            }

            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
            } else {
                menuCloseCustom(0x55, 0, 1);
                menuCloseCustom(0x1a, 0, 1);
                return 1;
            }
        }
    }
}

s32 dbgMenuFightTrainerAiAddsubDataWazaUsewazaEditSub(void) {
    u32 index;
    AddsubEntry* src;
    AddsubEntry* dst;
    s32 result;

    index = 0;
    while ((u16)index < 0x2D7) {
        src = fightTrainerAiValueAddsubDataBiosGetPtr(index);
        dst = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
        index++;
        *dst = *src;
    }

    while (1) {
        result = menuOpenCustom(0x1e, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1e, 0, 1);

            index = 0;
            while ((u16)index < 0x2D7) {
                dst = fightTrainerAiValueAddsubDataBiosGetPtr(index);
                src = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
                index++;
                *dst = *src;
            }

            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x1e)) {
        case 0xE7:
            dbgMenuFightTrainerDataStatusInputDigit(0x38, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xE8:
            dbgMenuFightTrainerDataStatusInputDigit(0x39, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xE9:
            dbgMenuFightTrainerDataStatusInputDigit(0x3a, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xEA:
            dbgMenuFightTrainerDataStatusInputDigit(0x3b, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xEB:
            dbgMenuFightTrainerDataStatusInputDigit(0x3c, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xEC:
            dbgMenuFightTrainerDataStatusInputDigit(0x40, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xED:
            dbgMenuFightTrainerDataStatusInputDigit(0x44, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xEE:
            dbgMenuFightTrainerDataStatusInputDigit(0x45, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xEF:
            dbgMenuFightTrainerDataStatusInputDigit(0x47, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xF0:
            dbgMenuFightTrainerDataStatusInputDigit(0x48, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xF1:
            dbgMenuFightTrainerDataStatusInputDigit(0x46, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xF2:
            dbgMenuFightTrainerDataStatusInputDigit(0x41, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xF3:
            dbgMenuFightTrainerDataStatusInputDigit(0x42, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xF4:
            dbgMenuFightTrainerDataStatusInputDigit(0x43, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xF5:
            dbgMenuFightTrainerDataStatusInputDigit(0x3d, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xF6:
            dbgMenuFightTrainerDataStatusInputDigit(0x3e, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xF7:
            dbgMenuFightTrainerDataStatusInputDigit(0x3f, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        }
    }
    menuCloseCustom(0x1e, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerAiAddsubDataWazaDefpokemonEditSub(void) {
    u32 index;
    AddsubEntry* src;
    AddsubEntry* dst;
    s32 result;

    index = 0;
    while ((u16)index < 0x2D7) {
        src = fightTrainerAiValueAddsubDataBiosGetPtr(index);
        dst = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
        index++;
        *dst = *src;
    }

    while (1) {
        result = menuOpenCustom(0x19, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x19, 0, 1);

            index = 0;
            while ((u16)index < 0x2D7) {
                dst = fightTrainerAiValueAddsubDataBiosGetPtr(index);
                src = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
                index++;
                *dst = *src;
            }

            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        menuGetCursorItemID(0x19);
    }
    menuCloseCustom(0x19, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerAiAddsubDataIrekaeDasuEditSub(void) {
    u32 index;
    AddsubEntry* src;
    AddsubEntry* dst;
    s32 result;

    index = 0;
    while ((u16)index < 0x2D7) {
        src = fightTrainerAiValueAddsubDataBiosGetPtr(index);
        dst = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
        index++;
        *dst = *src;
    }

    while (1) {
        result = menuOpenCustom(0x1d, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1d, 0, 1);

            index = 0;
            while ((u16)index < 0x2D7) {
                dst = fightTrainerAiValueAddsubDataBiosGetPtr(index);
                src = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
                index++;
                *dst = *src;
            }

            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x1d)) {
        case 0xCD:
            dbgMenuFightTrainerDataStatusInputDigit(0x1d, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xCE:
            dbgMenuFightTrainerDataStatusInputDigit(0x1e, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xCF:
            dbgMenuFightTrainerDataStatusInputDigit(0x1f, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD0:
            dbgMenuFightTrainerDataStatusInputDigit(0x21, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD1:
            dbgMenuFightTrainerDataStatusInputDigit(0x22, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD2:
            dbgMenuFightTrainerDataStatusInputDigit(0x23, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD3:
            dbgMenuFightTrainerDataStatusInputDigit(0x24, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD4:
            dbgMenuFightTrainerDataStatusInputDigit(0x25, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD5:
            dbgMenuFightTrainerDataStatusInputDigit(0x26, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD6:
            dbgMenuFightTrainerDataStatusInputDigit(0x27, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD7:
            dbgMenuFightTrainerDataStatusInputDigit(0x20, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD8:
            dbgMenuFightTrainerDataStatusInputDigit(0x30, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xD9:
            dbgMenuFightTrainerDataStatusInputDigit(0x28, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xDA:
            dbgMenuFightTrainerDataStatusInputDigit(0x29, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xDB:
            dbgMenuFightTrainerDataStatusInputDigit(0x2a, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xDC:
            dbgMenuFightTrainerDataStatusInputDigit(0x2b, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        }
    }
    menuCloseCustom(0x1d, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerAiAddsubDataIrekaeModosuEditSub(void) {
    u32 index;
    AddsubEntry* src;
    AddsubEntry* dst;
    s32 result;

    index = 0;
    while ((u16)index < 0x2D7) {
        src = fightTrainerAiValueAddsubDataBiosGetPtr(index);
        dst = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
        index++;
        *dst = *src;
    }

    while (1) {
        result = menuOpenCustom(0x1c, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1c, 0, 1);

            index = 0;
            while ((u16)index < 0x2D7) {
                dst = fightTrainerAiValueAddsubDataBiosGetPtr(index);
                src = &_old_fight_trainer_ai_value_addsub_data[(u16)index];
                index++;
                *dst = *src;
            }

            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x1c)) {
        case 0xB3:
            dbgMenuFightTrainerDataStatusInputDigit(0x1, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xB4:
            dbgMenuFightTrainerDataStatusInputDigit(0x2, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xB5:
            dbgMenuFightTrainerDataStatusInputDigit(0x3, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xB6:
            dbgMenuFightTrainerDataStatusInputDigit(0x4, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xB7:
            dbgMenuFightTrainerDataStatusInputDigit(0x5, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xB8:
            dbgMenuFightTrainerDataStatusInputDigit(0x6, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xB9:
            dbgMenuFightTrainerDataStatusInputDigit(0x7, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xBA:
            dbgMenuFightTrainerDataStatusInputDigit(0x8, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xBB:
            dbgMenuFightTrainerDataStatusInputDigit(0x19, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xBC:
            dbgMenuFightTrainerDataStatusInputDigit(0x9, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xBD:
            dbgMenuFightTrainerDataStatusInputDigit(0xa, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xBE:
            dbgMenuFightTrainerDataStatusInputDigit(0xb, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xBF:
            dbgMenuFightTrainerDataStatusInputDigit(0xc, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC0:
            dbgMenuFightTrainerDataStatusInputDigit(0xd, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC1:
            dbgMenuFightTrainerDataStatusInputDigit(0xe, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC2:
            dbgMenuFightTrainerDataStatusInputDigit(0xf, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC3:
            dbgMenuFightTrainerDataStatusInputDigit(0x10, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC4:
            dbgMenuFightTrainerDataStatusInputDigit(0x11, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC5:
            dbgMenuFightTrainerDataStatusInputDigit(0x12, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC6:
            dbgMenuFightTrainerDataStatusInputDigit(0x13, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC7:
            dbgMenuFightTrainerDataStatusInputDigit(0x14, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC8:
            dbgMenuFightTrainerDataStatusInputDigit(0x15, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xC9:
            dbgMenuFightTrainerDataStatusInputDigit(0x16, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xCA:
            dbgMenuFightTrainerDataStatusInputDigit(0x17, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        case 0xCB:
            dbgMenuFightTrainerDataStatusInputDigit(0x18, 0x3e, 0x0, 0xc8, -0xc8);
            break;
        }
    }
    menuCloseCustom(0x1c, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerPokemonPartDataEditSub(u16 id) {
    PokemonPartData* data;
    PokemonPartData backup;
    s32 result;
    s32 v;

    if (id == 0) {
        return 1;
    }
    data = fightTrainerPokemonPartDataBiosGetPtr(id);
    backup = *data;
    while (1) {
        result = menuOpenCustom(0x1f, 0, 0, 0, 1, 1, id);
        if (result == -1) {
            menuCloseCustom(0x1f, 0, 1);
            *data = backup;
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x1f)) {
        case 0xFC:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0x1, 0x64, 0x0);
            break;
        case 0xFD:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0x2, 0x64, 0x0);
            break;
        case 0xFE:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0x3, 0x64, 0x0);
            break;
        case 0xFF:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0x4, 0x64, 0x0);
            break;
        case 0x100:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0x5, 0x64, 0x0);
            break;
        case 0x101:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0x6, 0x64, 0x0);
            break;
        case 0x102:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0x7, 0x64, 0x0);
            break;
        case 0x103:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0x8, 0x64, 0x0);
            break;
        case 0x104:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0x9, 0x64, 0x0);
            break;
        case 0x105:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0xa, 0x64, 0x0);
            break;
        case 0x108:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xc, 0xd, 0x64, 0x0);
            break;
        }
    }
    menuCloseCustom(0x1f, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerAiDataEditSub(u16 id) {
    AiData* data;
    AiData backup;
    s32 result;
    s32 v;

    if (id == 0) {
        return 1;
    }
    data = fightTrainerAiDataBiosGetPtr(id);
    backup = *data;
    while (1) {
        result = menuOpenCustom(0x18, 0, 0, 0, 1, 1, id);
        if (result == -1) {
            menuCloseCustom(0x18, 0, 1);
            *data = backup;
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x18)) {
        case 0x8E:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x25, 0x0, 0x64, 0x0);
            break;
        case 0x8F:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x26, 0x0, 0x64, 0x0);
            break;
        case 0x90:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x27, 0x0, 0x64, 0x0);
            break;
        case 0x91:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x2c, 0x0, 0x64, 0x0);
            break;
        case 0x92:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x37, 0x0, 0x64, 0x0);
            break;
        case 0x93:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x1f);
            break;
        case 0x94:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x20);
            break;
        case 0x95:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x23);
            break;
        case 0x96:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x24);
            break;
        case 0x97:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x28);
            break;
        case 0x98:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x29);
            break;
        case 0x99:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x2a);
            break;
        case 0x9A:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x2b);
            break;
        case 0x9B:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x2d);
            break;
        case 0x9C:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x30);
            break;
        case 0x9D:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x31);
            break;
        case 0x9E:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x32);
            break;
        case 0x9F:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x33);
            break;
        case 0xA0:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x34);
            break;
        case 0xA1:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x36);
            break;
        case 0xA2:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x35, 0x0, 0x64, 0x0);
            break;
        case 0xA3:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x2e, 0x0, 0x54, 0x0);
            break;
        case 0xA4:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x2f, 0x0, 0x54, 0x0);
            break;
        case 0xA6:
            v = (u16)fightTrainerGetStatus(0, id, 0x39, 0x0);
            v = dbgMenuFightGetZokuseiDataId(v);
            if (v >= 0) {
                fightTrainerSetStatus(0, id, 0x39, 0x0, v);
            }
            break;
        case 0xA7:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x3a, 0x0, 0x64, 0x0);
            break;
        case 0xA8:
            v = (u16)fightTrainerGetStatus(0, id, 0x39, 0x1);
            v = dbgMenuFightGetZokuseiDataId(v);
            if (v >= 0) {
                fightTrainerSetStatus(0, id, 0x39, 0x1, v);
            }
            break;
        case 0xA9:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x3a, 0x1, 0x64, 0x0);
            break;
        case 0xAB:
            v = fightTrainerGetStatus(0, id, 0x3b, 0x0);
            v = dbgMenuFightGetWazaTypeId(v);
            if (v >= 0) {
                fightTrainerSetStatus(0, id, 0x3b, 0x0, v);
            }
            break;
        case 0xAC:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x3c, 0x0, 0x64, 0x0);
            break;
        case 0xAD:
            v = fightTrainerGetStatus(0, id, 0x3b, 0x1);
            v = dbgMenuFightGetWazaTypeId(v);
            if (v >= 0) {
                fightTrainerSetStatus(0, id, 0x3b, 0x1, v);
            }
            break;
        case 0xAE:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x3c, 0x1, 0x64, 0x0);
            break;
        case 0xAF:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x21);
            break;
        case 0xB0:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x22);
            break;
        case 0xB1:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x38, 0x1, 0x64, 0x0);
            break;
        }
    }
    menuCloseCustom(0x18, 0, 1);
    return 1;
}

void dbgMenuFightTrainerDataStatusInputDigit(u16 id, u32 field, u32 index, s32 maximum, s32 minimum) {
    s32 value;
    u8 result;

    result = menuSubOpenNumberInput(fightTrainerGetStatus(0, id, field, index), &value, 0, 0x32, 0x32, 0);
    if (result == 1) {
        if (value > maximum) {
            value = maximum;
        }
        if (value < minimum) {
            value = minimum;
        }
        fightTrainerSetStatus(0, id, field, index, value);
    }
    menuSubCloseNumberInput();
}

void dbgMenuFightTrainerDataStatusInputFlag(u16 id, u32 field) {
    s8 answer = menuSubOpenYesNo(0x7F, -1, -1, fightTrainerGetStatus(0, id, field, 0) == 0);

    if (answer == 0) {
        fightTrainerSetStatus(0, id, field, 0, 1);
    } else if (answer == 1) {
        fightTrainerSetStatus(0, id, field, 0, 0);
    }
}

}
