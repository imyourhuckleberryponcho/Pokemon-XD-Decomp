#include <dolphin/types.h>

// Menu files were built without the peephole optimizer.
#pragma peephole off

struct CURSOR {
    s16 top;
    s16 pos;
};

struct MENU_MODEL;

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    s8 seqSet;
    u8 unk3;
    void* seq;
    u8 unk8[0x14];
    s32 layer;
    u8 unk20[0x48];
    struct MEMO_CONTENTS* contents;
    u8 unk6C[0x27];
    u8 alpha;
    u8 unk94[0x10];
    u8 unkA4;
    u8 unkA5;
};

struct tagSPRITE_WORK {
    u8 unk0[6];
    s16 id;
    u8 unk8[0x14];
    s32 layer;
    u8 unk20[0x44];
    u8 colorR;
    u8 colorG;
    u8 colorB;
};

struct MenuItem {
    u8 unk0[0xA];
    s16 width;
    s16 height;
};

struct WindowKeyInfo {
    u16 unk0;
    u16 unk2;
    u16 trigger;
    u16 unk6;
};

struct MEMO_CONTENTS {
    CURSOR* cursor;
};

class menuPdaMemoXD {
public:
    void PokemonHeight(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents);
    void PokemonWeight(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents);
    void PokemonSyuzoku(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents);
    void PokemonAisyou(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents);
    void SetJoutaiSprite(tagWINDOW_WORK* window, unsigned short joutai);
    unsigned short GetAisyouIndex(unsigned short index);
    void PokemonTokuseiSetumei(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents,
                               unsigned short slot);
    void PokemonTokusei(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents, unsigned short slot);
    void PokemonType(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents, unsigned short slot);
    void PokemonName(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents);
    CURSOR* Main(CURSOR* cursor);
    void Button(tagWINDOW_WORK* window);
    void Ctrl(tagWINDOW_WORK* window);
    void Cursor(tagWINDOW_WORK* window);
    void SetModelAngle(short item);
    void OokisaCameraControl();
    void CameraControl();
    void Release();
    void LoadPokemon(CURSOR* cursor);
    void Init(CURSOR* cursor);
    long TaskOpen();
    void TaskClose(tagWINDOW_WORK* window, bool sync);
    bool TaskCloseCheck();
    void _menuClose(long menuID, bool sync);

    CURSOR* cursor;
    u8 unk4[4];
    s32 item;
    s32 prevItem;
    s32 menuID;
    f32 angleX;
    f32 angleY;
    f32 angleZ;
    f32 zoom;
    u8 unk24[0xE8 - 0x24];
};

extern "C" {
void* __nw__FUl(unsigned long);
void __dl__FPv(void*);
void* __nwa__FUl(unsigned long);
void __dla__FPv(void*);
double atan2(double, double);
void PSVECAdd(f32*, f32*, f32*);
s32 GSinputButtonsPressed(s32);
s8 GSinputGetRightStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
void GSmodelDestroyLinkedParticles(void);
u32 GSmsgGetCharLength(u16*);
u16* GSmsgGetGSchar(u32);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
void GSmsgPrintRight(s32, s32, s32, s32, s32, u32, u32);
void GSsndPlayNow(u32);
u16 memoDataGetCount(s32);
void menuClose(s32);
void menuCloseSync(s32, bool);
MenuItem* menuItemBiosGetPtr(s32, s32);
f32* menuModelGetCameraRotation(MENU_MODEL*);
void* menuModelGetModelPtr(MENU_MODEL*);
void menuModelSetAngle(MENU_MODEL*, f32*);
void menuModelSetCameraRotation(MENU_MODEL*, f32*);
void menuModelSetZoom(MENU_MODEL*, f32);
s32 menuOpenCustom(s32, ...);
void* menuPdaGetRes(void);
void* menuPdaGetSubres(void);
void menuPdaMemoListDispPokemonModel(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
f32 menuPdaMemoListGetDefaultAngle(s16);
MENU_MODEL* menuPdaMemoListGetMenuModelWork(void);
void* menuPdaMemoListGetPokemonDataPointer(long);
u16 menuPdaMemoListGetPokemonID(long);
s32 menuPdaMemoListGetPokemonName(long);
u8 menuPdaMemoListIsLoadHero(void);
u8 menuPdaMemoListIsTermModel(void);
void menuPdaMemoListLoadHero(bool);
void menuPdaMemoListLoadPokemon(long);
void menuPdaMemoListSetHeroMotion(void);
void menuPdaMemoWave(long);
void menuPdaMemoWaveHook(void);
void menuPdaMemoWaveInit(void);
void menuPdaSetSubres(s32, s32);
void menuPlaySe(void*, s32);
void msgctrlSetValue(s32, u32);
s32 pokecoloGetLanguage(void);
u16 pokemonDataBiosGetHeight(void*);
void* pokemonDataBiosGetPtr(u16);
u8 pokemonDataBiosGetTokuseiDataId(void*, u16);
u32 pokemonDataBiosGetTypeName(void*);
u16 pokemonDataBiosGetWeight(void*);
u8 pokemonDataBiosGetZokuseiDataId(void*, u16);
u32 pokemonTokuseiDataBiosGetDoc(void*);
u32 pokemonTokuseiDataBiosGetName(void*);
void* pokemonTokuseiDataBiosGetPtr(u8);
u8 winSeqCheckMove(s32);
void winSeqSetMenu(void*, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
void windowDrawSprite(s32, s32, tagWINDOW_WORK*, s32, s32, s32);
s32 windowGetActiveID(void);
WindowKeyInfo* windowGetKeyInfo(void);
s32 zokuseiGetPokemonSpriteID(void*, u16);
s32 zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16, s16*, s32);
s32 zokuseiGetWazaJoutai_PokemonId(u16, s32);
}

static menuPdaMemoXD* pMemo;
static CURSOR _cursor;
static u8 _akagi;
static s16 heightBuf[12];

extern "C" {

void menuPdaMemoXDHeight(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
void menuPdaMemoXDWeight(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
s32 menuPdaMemoXDGetItem(void);

void menuPdaMemoBackHook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    menuPdaGetRes();
    menuPdaGetSubres();
    switch (sprite->id) {
    case 0xC4:
        if (menuPdaMemoXDGetItem() == 0) {
            winSpriteSetDisp(sprite, 1);
            msgctrlSetValue(0x34, memoDataGetCount(0));
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0xB9:
        if (menuPdaMemoXDGetItem() == 3) {
            menuPdaMemoListDispPokemonModel(window, sprite, 0);
        }
        break;
    case 0xBB:
        if (menuPdaMemoXDGetItem() == 0) {
            menuPdaMemoListDispPokemonModel(window, sprite, 1);
        }
        break;
    case 0xBA:
        if (menuPdaMemoXDGetItem() == 1) {
            menuPdaMemoListDispPokemonModel(window, sprite, 2);
        }
        break;
    case 0x1C7:
        if (menuPdaMemoXDGetItem() == 2) {
            menuPdaMemoListDispPokemonModel(window, sprite, 3);
        }
        break;
    case 0x16A:
        if (menuPdaMemoXDGetItem() == 2) {
            winSpriteSetDisp(sprite, 1);
            menuPdaMemoXDWeight(window, sprite);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x16B:
        if (menuPdaMemoXDGetItem() == 2) {
            winSpriteSetDisp(sprite, 1);
            menuPdaMemoXDHeight(window, sprite);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    default:
        if (sprite->id >= 0xBB) {
            if (menuPdaMemoXDGetItem() == 1) {
                winSpriteSetDisp(sprite, 1);
            } else {
                winSpriteSetDisp(sprite, 0);
            }
        } else if (sprite->id >= 0xB5) {
            if (menuPdaMemoXDGetItem() == 3) {
                winSpriteSetDisp(sprite, 1);
            } else {
                winSpriteSetDisp(sprite, 0);
            }
        } else if (sprite->id >= 0xB1) {
            if (menuPdaMemoXDGetItem() == 0) {
                winSpriteSetDisp(sprite, 1);
            } else {
                winSpriteSetDisp(sprite, 0);
            }
        } else if (sprite->id >= 0xAD) {
            if (menuPdaMemoXDGetItem() == 1 || menuPdaMemoXDGetItem() == 2) {
                winSpriteSetDisp(sprite, 1);
            } else {
                winSpriteSetDisp(sprite, 0);
            }
        }
        break;
    }
}

void menuPdaMemoXDHeight(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (pMemo != 0) {
        sprite->colorR = 0xD5;
        sprite->colorG = 0xAA;
        sprite->colorB = 0x33;
        pMemo->PokemonHeight(window, sprite, (MEMO_CONTENTS*)pMemo);
    }
}

void menuPdaMemoXDWeight(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (pMemo != 0) {
        sprite->colorR = 0xD5;
        sprite->colorG = 0xAA;
        sprite->colorB = 0x33;
        pMemo->PokemonWeight(window, sprite, (MEMO_CONTENTS*)pMemo);
    }
}

s32 menuPdaMemoXDGetItem(void) {
    if (pMemo == 0) {
        return 0;
    }
    return pMemo->item;
}

s32 menuPdaMemoXDHook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (pMemo == 0) {
        return 0;
    }
    switch (sprite->id) {
    case 0xFD:
        pMemo->PokemonType(window, sprite, (MEMO_CONTENTS*)pMemo, 0);
        break;
    case 0xFE:
        pMemo->PokemonType(window, sprite, (MEMO_CONTENTS*)pMemo, 1);
        break;
    case 0x103:
        pMemo->PokemonTokusei(window, sprite, (MEMO_CONTENTS*)pMemo, 0);
        break;
    case 0x102:
        pMemo->PokemonTokusei(window, sprite, (MEMO_CONTENTS*)pMemo, 1);
        break;
    case 0x105:
        pMemo->PokemonSyuzoku(window, sprite, (MEMO_CONTENTS*)pMemo);
        break;
    case 0x106:
        pMemo->PokemonName(window, sprite, (MEMO_CONTENTS*)pMemo);
        break;
    case 0x100:
        sprite->colorR = 0xD5;
        sprite->colorG = 0xAA;
        sprite->colorB = 0x33;
        pMemo->PokemonWeight(window, sprite, (MEMO_CONTENTS*)pMemo);
        break;
    case 0x101:
        sprite->colorR = 0xD5;
        sprite->colorG = 0xAA;
        sprite->colorB = 0x33;
        pMemo->PokemonHeight(window, sprite, (MEMO_CONTENTS*)pMemo);
        break;
    case 0x104:
        sprite->colorR = 0xD5;
        sprite->colorG = 0xAA;
        sprite->colorB = 0x33;
        break;
    case 0x10B:
        menuPdaMemoWaveHook();
        break;
    default:
        pMemo->PokemonAisyou(window, sprite, (MEMO_CONTENTS*)pMemo);
        break;
    case 0x15A:
        pMemo->PokemonTokuseiSetumei(window, sprite, (MEMO_CONTENTS*)pMemo, 0);
        break;
    case 0x15B:
        pMemo->PokemonTokusei(window, sprite, (MEMO_CONTENTS*)pMemo, 0);
        break;
    case 0x157:
        pMemo->PokemonTokuseiSetumei(window, sprite, (MEMO_CONTENTS*)pMemo, 1);
        break;
    case 0x158:
        pMemo->PokemonTokusei(window, sprite, (MEMO_CONTENTS*)pMemo, 1);
        break;
    case 0x15D:
        pMemo->PokemonSyuzoku(window, sprite, (MEMO_CONTENTS*)pMemo);
        break;
    case 0x15E:
        pMemo->PokemonName(window, sprite, (MEMO_CONTENTS*)pMemo);
        break;
    case 0x155:
        pMemo->PokemonType(window, sprite, (MEMO_CONTENTS*)pMemo, 0);
        break;
    case 0x156:
        pMemo->PokemonType(window, sprite, (MEMO_CONTENTS*)pMemo, 1);
        break;
    case 0x15C:
        msgctrlSetValue(0x4D, (u32)GSmsgGetGSchar(0x3B68));
        msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0x3B69));
        GSmsgPrint2(window->layer, 0, 0, window->alpha | ~0xFF, 0x4278);
        break;
    case 0x159: {
        CURSOR* cursor = window->contents->cursor;
        u16 mon = (u16)(u32)pokemonDataBiosGetPtr(menuPdaMemoListGetPokemonID(cursor->pos + cursor->top));
        u8 first = pokemonDataBiosGetTokuseiDataId(0, 0);
        u8 second = pokemonDataBiosGetTokuseiDataId((void*)mon, 1);
        if (second == first) {
            second = 0;
        }
        if ((u16)second != 0) {
            msgctrlSetValue(0x4D, (u32)GSmsgGetGSchar(0x3B68));
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0x3B6A));
            GSmsgPrint2(window->layer, 0, 0, window->alpha | ~0xFF, 0x4278);
        }
        break;
    }
    }
    return 0;
}

CURSOR* menuPdaMemoXDMain(CURSOR* cursor) {
    pMemo = new menuPdaMemoXD;
    pMemo->Init(cursor);
    pMemo->Main(cursor);
    menuPdaMemoXD* memo = pMemo;
    if (memo != 0) {
        memo->Release();
        delete memo;
    }
    pMemo = 0;
    return &_cursor;
}

void menuPdaMemoXDButton(tagWINDOW_WORK* window) {
    if (pMemo != 0) {
        pMemo->Button(window);
    }
}

s32 menuPdaMemoXDCursor(tagWINDOW_WORK* window) {
    if (pMemo == 0) {
        return 0;
    }
    pMemo->Cursor(window);
    return 0;
}

s32 menuPdaMemoXDCtrl(tagWINDOW_WORK* window) {
    if (pMemo == 0) {
        return 0;
    }
    pMemo->Ctrl(window);
    return 0;
}

}

void menuPdaMemoXD::PokemonHeight(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    void* data = menuPdaMemoListGetPokemonDataPointer(c->pos + c->top);
    MenuItem* item = menuItemBiosGetPtr(0x7C, sprite->id);
    s32 layer = winSpriteGetLayerID(window, sprite);
    u16 height = pokemonDataBiosGetHeight(data);
    if (pokecoloGetLanguage() == 2) {
        u32 inches = (u32)(0.5f + 39.37f * ((f32)height / 10.0f));
        s32 value = (inches % 12) + (inches / 12) * 100;
        s32 pos = 7;
        s32 digits = 3;
        heightBuf[9] = 0;
        heightBuf[8] = 0x27;
        heightBuf[7] = 0x27;
        for (;;) {
            s32 digit = value % 10;
            value /= 10;
            if (digits > 0 || digit != 0) {
                digits--;
                pos--;
                heightBuf[pos] = digit + 0x30;
                if (digits == 1) {
                    pos--;
                    heightBuf[pos] = 0x27;
                }
                continue;
            }
            break;
        }
        msgctrlSetValue(0x37, (u32)&heightBuf[pos]);
        GSmsgPrintRight(layer, 0, 0, item->width, item->height, window->alpha | ~0xFF, 0x4276);
        return;
    }
    msgctrlSetValue(0x34, height / 10);
    msgctrlSetValue(0x35, height % 10);
    GSmsgPrintRect(layer, 0, 0, item->width, item->height, window->alpha | ~0xFF, 0x3BA2);
}

void menuPdaMemoXD::PokemonWeight(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    void* data = menuPdaMemoListGetPokemonDataPointer(c->pos + c->top);
    MenuItem* item = menuItemBiosGetPtr(0x7C, sprite->id);
    s32 layer = winSpriteGetLayerID(window, sprite);
    u16 weight = pokemonDataBiosGetWeight(data);
    if (pokecoloGetLanguage() == 2) {
        u32 pounds = (u32)(2.2045856f * (f32)weight + 0.5f);
        msgctrlSetValue(0x34, pounds / 10);
        msgctrlSetValue(0x35, pounds % 10);
        GSmsgPrintRect(layer, 0, 0, item->width, item->height, window->alpha | ~0xFF, 0x3BA1);
        return;
    }
    msgctrlSetValue(0x34, weight / 10);
    msgctrlSetValue(0x35, weight % 10);
    GSmsgPrintRect(layer, 0, 0, item->width, item->height, window->alpha | ~0xFF, 0x3BA1);
}

void menuPdaMemoXD::PokemonSyuzoku(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    void* data = menuPdaMemoListGetPokemonDataPointer(c->pos + c->top);
    msgctrlSetValue(0x31, pokemonDataBiosGetTypeName(data));
    GSmsgPrint2(window->layer, 0, 0, window->alpha | ~0xFF, 0x3B9B);
}

void menuPdaMemoXD::PokemonAisyou(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents) {
    const s32 spriteIDs[17] = { 0x144, 0x145, 0x146, 0x147, 0x148, 0x149, 0x14A, 0x14B, 0x14C,
                                       0x14D, 0x14E, 0x14F, 0x150, 0x151, 0x152, 0x153, 0x154 };
    s16 types[2];
    CURSOR* c = contents->cursor;
    s32 index = c->pos + c->top;
    void* data = menuPdaMemoListGetPokemonDataPointer(index);
    u16 i = 0;
    s32 id = menuPdaMemoListGetPokemonID(index);
    while (i < 0x11) {
        if (sprite->id == spriteIDs[i]) {
            break;
        }
        i++;
    }
    u16 defense = GetAisyouIndex(i);
    types[0] = pokemonDataBiosGetZokuseiDataId(data, 0);
    s32 count = 1;
    u8 second = pokemonDataBiosGetZokuseiDataId(data, 1);
    types[1] = second;
    if (second != 0) {
        count = 2;
    }
    s32 joutai;
    if (_akagi != 0) {
        joutai = zokuseiGetWazaJoutai_PokemonId(defense, id);
    } else {
        joutai = zokuseiGetWazaJoutaiAsDefenseZokuseiAry(defense, types, count);
    }
    SetJoutaiSprite(window, joutai);
}

void menuPdaMemoXD::SetJoutaiSprite(tagWINDOW_WORK* window, unsigned short joutai) {
    const u16 joutaiIDs[4] = { 0x43, 0x42, 0x3F, 0x41 };
    const u16 spriteIDs[4] = { 0x16A, 0x16B, 0x16C, 0x16D };
    for (u16 i = 0; i < 4; i++) {
        if (joutai == joutaiIDs[i]) {
            windowDrawSprite(0, 0, window, spriteIDs[i], 0, window->layer);
        }
    }
}

unsigned short menuPdaMemoXD::GetAisyouIndex(unsigned short index) {
    const u16 table[18] = { 0, 1, 3, 4, 2, 6, 5, 7, 8, 0xA, 0xB, 0xD, 0xC, 0xF, 0xE, 0x10, 0x11, 9 };
    if (index > 0x12) {
        return 0;
    }
    return table[index];
}

void menuPdaMemoXD::PokemonTokuseiSetumei(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents,
                                          unsigned short slot) {
    CURSOR* c = contents->cursor;
    u16 mon = (u16)(u32)pokemonDataBiosGetPtr(menuPdaMemoListGetPokemonID(c->pos + c->top));
    MenuItem* item = menuItemBiosGetPtr(0x7E, sprite->id);
    GSmsgGetGSchar(0x3BBC);
    u8 first = pokemonDataBiosGetTokuseiDataId((void*)mon, 0);
    u8 tokusei = pokemonDataBiosGetTokuseiDataId((void*)mon, slot);
    if (slot != 0 && tokusei == first) {
        tokusei = 0;
    }
    if ((u16)tokusei != 0) {
        void* data = pokemonTokuseiDataBiosGetPtr(tokusei);
        u16* text = GSmsgGetGSchar(pokemonTokuseiDataBiosGetDoc(data));
        u32 length = GSmsgGetCharLength(text);
        s32 size = (length + 2) * 2;
        u16* line1 = (u16*)new u16[size / 2];
        u16* line2 = (u16*)new u16[size / 2];
        (void)line1;
        (void)line2;
        (void)item;
        (void)window;
        __dla__FPv(line1);
        __dla__FPv(line2);
    }
}

void menuPdaMemoXD::PokemonTokusei(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents,
                                   unsigned short slot) {
    CURSOR* c = contents->cursor;
    u16 mon = (u16)(u32)pokemonDataBiosGetPtr(menuPdaMemoListGetPokemonID(c->pos + c->top));
    u8 first = pokemonDataBiosGetTokuseiDataId(0, 0);
    u8 tokusei = pokemonDataBiosGetTokuseiDataId((void*)mon, slot);
    if (slot == 0) {
        if (tokusei != 0) {
            void* data = pokemonTokuseiDataBiosGetPtr(tokusei);
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(data)));
            GSmsgPrint2(window->layer, 0, 0, window->alpha | ~0xFF, 0x4278);
        }
    } else if (tokusei != 0 && tokusei != first) {
        void* data = pokemonTokuseiDataBiosGetPtr(tokusei);
        msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(data)));
        GSmsgPrint2(window->layer, 0, 0, window->alpha | ~0xFF, 0x4278);
    }
}

void menuPdaMemoXD::PokemonType(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents,
                                unsigned short slot) {
    CURSOR* c = contents->cursor;
    void* mon = pokemonDataBiosGetPtr(menuPdaMemoListGetPokemonID(c->pos + c->top));
    if (slot == 0) {
        windowDrawSprite(0, 0, window, zokuseiGetPokemonSpriteID(mon, slot), 0, window->layer);
        return;
    }
    u16 first = zokuseiGetPokemonSpriteID(mon, 0);
    u16 second = zokuseiGetPokemonSpriteID(mon, slot);
    if (second != 0 && first != second) {
        windowDrawSprite(0, 0, window, second, 0, window->layer);
    }
}

void menuPdaMemoXD::PokemonName(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, MEMO_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    u32 name = menuPdaMemoListGetPokemonName(c->pos + c->top);
    if (name == 0) {
        name = (u32)GSmsgGetGSchar(1);
    }
    msgctrlSetValue(0x37, name);
    GSmsgPrint2(window->layer, 0, 0, window->alpha | ~0xFF, 0x4275);
}

CURSOR* menuPdaMemoXD::Main(CURSOR* cursor) {
    _cursor.pos = cursor->pos;
    _cursor.top = cursor->top;
    for (;;) {
        this->cursor = &_cursor;
        if (TaskOpen() == -1) {
            break;
        }
        s32 item = this->item;
        if (item == prevItem && item == 1) {
            menuPdaMemoWave(_cursor.pos + _cursor.top);
        }
    }
    TaskClose(0, true);
    menuPdaSetSubres(-1, 1);
    menuPdaMemoListLoadHero(false);
    return &_cursor;
}

void menuPdaMemoXD::Button(tagWINDOW_WORK* window) {
    if (window != 0) {
        u16 trigger = windowGetKeyInfo()->trigger;
        menuPdaGetRes();
        menuPdaGetSubres();
        if (winSeqCheckMove((s32)window->seq) == 0) {
            if ((trigger & 0x10) != 0) {
                s32 item = this->item;
                if (item == 1) {
                    prevItem = item;
                    this->item = item;
                    window->unkA4 = 1;
                }
            }
            if ((trigger & 0x20) != 0) {
                window->unkA4 = 1;
                window->unkA5 = 1;
            }
        }
    }
}

void menuPdaMemoXD::Ctrl(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x132);
            window->seqSet = 1;
            menuPdaSetSubres(-1, 2);
        }
        break;
    case 2:
        if (item == 2 && menuPdaMemoListIsLoadHero() == 0) {
            menuPdaMemoListSetHeroMotion();
        }
        break;
    case 3:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x136);
            window->seqSet = 1;
        }
        break;
    }
}

void menuPdaMemoXD::Cursor(tagWINDOW_WORK* window) {
    CURSOR* c = window->contents->cursor;
    WindowKeyInfo* key = windowGetKeyInfo();
    int count = memoDataGetCount(0);
    u16 repeat = key->unk6;
    int visible = 8;
    s16 newItem = item;
    if (menuPdaMemoListIsTermModel() != 1) {
        int prev = c->pos + c->top;
        if (count < 8) {
            visible = count;
        }
        s16 oldItem = item;
        if ((repeat & 1) != 0) {
            if (prev != 0) {
                GSsndPlayNow(0x450);
            }
            c->pos -= 1;
            if (newItem == 1 && c->pos + c->top >= 0) {
                SetModelAngle(1);
            }
            if (newItem == 2) {
                f32* rot = menuModelGetCameraRotation(menuPdaMemoListGetMenuModelWork());
                rot[0] = 0.0f;
                rot[1] = 0.0f;
                rot[2] = 0.0f;
            }
        } else if ((repeat & 2) != 0) {
            if (count - 1 != c->pos + c->top) {
                GSsndPlayNow(0x450);
            }
            c->pos += 1;
            if (newItem == 1 && count != c->pos + c->top) {
                SetModelAngle(1);
            }
            if (newItem == 2) {
                f32* rot = menuModelGetCameraRotation(menuPdaMemoListGetMenuModelWork());
                rot[0] = 0.0f;
                rot[1] = 0.0f;
                rot[2] = 0.0f;
            }
        } else if ((repeat & 4) != 0) {
            if (TaskCloseCheck() != 0) {
                if (newItem == 1) {
                    menuPdaMemoWaveInit();
                }
                if (newItem > 0) {
                    GSsndPlayNow(0x453);
                    TaskClose(window, false);
                    newItem -= 1;
                    prevItem = item;
                    item = newItem;
                }
                SetModelAngle(newItem);
            }
        } else if ((repeat & 8) != 0 && TaskCloseCheck() != 0) {
            if (newItem == 1) {
                menuPdaMemoWaveInit();
            }
            if (newItem < 3) {
                GSsndPlayNow(0x453);
                TaskClose(window, false);
                newItem += 1;
                prevItem = item;
                item = newItem;
            }
            SetModelAngle(newItem);
        }
        s32 cur = item;
        if ((s16)cur == 1) {
            CameraControl();
        } else if ((s16)cur == 2) {
            OokisaCameraControl();
        }
        s16 pos = c->pos;
        if (pos < 0) {
            c->top += pos;
            c->pos = 0;
            if (c->top < 0) {
                c->top = 0;
                c->pos = 0;
            }
        } else if (pos >= visible) {
            s16 last = visible - 1;
            c->top += pos - last;
            c->pos = last;
            if (c->top + c->pos >= count) {
                c->pos = last;
                c->top = count - visible;
            }
        }
        if (prev != c->pos + c->top) {
            LoadPokemon(c);
            menuPlaySe(window->seq, 1);
        }
        if (oldItem != item) {
            menuPlaySe(window->seq, 1);
        }
    }
}

void menuPdaMemoXD::SetModelAngle(short item) {
    switch (item) {
    case 1:
        angleX = 0.0f;
        angleY = 0.0f;
        angleZ = 0.0f;
        break;
    case 2:
        angleX = 0.0f;
        angleY = 0.0f;
        angleZ = 0.0f;
        break;
    default: {
        f32 z = menuPdaMemoListGetDefaultAngle(2);
        f32 y = menuPdaMemoListGetDefaultAngle(1);
        angleX = menuPdaMemoListGetDefaultAngle(0);
        angleY = y;
        angleZ = z;
        break;
    }
    }
    if (item == 1) {
        zoom = 0.6f;
    } else {
        zoom = 1.0f;
    }
    menuModelSetAngle(menuPdaMemoListGetMenuModelWork(), &angleX);
    menuModelSetZoom(menuPdaMemoListGetMenuModelWork(), zoom);
    f32 rot[3];
    rot[0] = 0.0f;
    rot[1] = 0.0f;
    rot[2] = 0.0f;
    menuModelSetCameraRotation(menuPdaMemoListGetMenuModelWork(), rot);
    if (item == 2) {
        menuPdaMemoListLoadHero(true);
        return;
    }
    menuPdaMemoListLoadHero(false);
}

void menuPdaMemoXD::OokisaCameraControl() {
    f32 delta[3];
    delta[0] = 0.0f;
    delta[1] = 0.0f;
    delta[2] = 0.0f;
    s8 stickX = GSinputGetRightStickXData(1, 1);
    s8 stickY = GSinputGetRightStickYData(1, 1);
    f32* rot = menuModelGetCameraRotation(menuPdaMemoListGetMenuModelWork());
    atan2((f64)stickY, (f64)stickX);
    f32 dy = -3.1415927f * (f32)stickY * 0.0078125f;
    delta[0] = 0.016666668f * dy;
    delta[1] = 0.016666668f * (3.1415927f * (f32)stickX * 0.0078125f);
    PSVECAdd(rot, delta, rot);
    if (rot[0] >= 0.7853982f) {
        rot[0] = 0.7853982f;
    }
    if (rot[0] <= -0.7853982f) {
        rot[0] = -0.7853982f;
    }
    menuModelSetCameraRotation(menuPdaMemoListGetMenuModelWork(), rot);
}

void menuPdaMemoXD::CameraControl() {
    f32 delta[3];
    delta[0] = 0.0f;
    delta[1] = 0.0f;
    delta[2] = 0.0f;
    s8 stickX = GSinputGetRightStickXData(1, 1);
    s8 stickY = GSinputGetRightStickYData(1, 1);
    atan2((f64)stickY, (f64)stickX);
    f32 dy = -3.1415927f * (f32)stickY * 0.0078125f;
    delta[0] = 0.016666668f * dy;
    delta[1] = 0.016666668f * (3.1415927f * (f32)stickX * 0.0078125f);
    PSVECAdd(&angleX, delta, &angleX);
    if (angleX >= 1.5707964f) {
        angleX = 1.5707964f - delta[0];
    }
    if (angleX <= -1.5707964f) {
        angleX = -1.5707964f - delta[0];
    }
    if ((GSinputButtonsPressed(1) & 0x20) != 0) {
        if (zoom <= 1.2f) {
            zoom = zoom + 0.016666668f;
        }
    } else if ((GSinputButtonsPressed(1) & 0x40) != 0) {
        if (zoom > 0.3f) {
            zoom = zoom - 0.016666668f;
        }
    }
    menuModelSetAngle(menuPdaMemoListGetMenuModelWork(), &angleX);
    menuModelSetZoom(menuPdaMemoListGetMenuModelWork(), zoom);
}

void menuPdaMemoXD::Release() {
}

void menuPdaMemoXD::LoadPokemon(CURSOR* c) {
    menuPdaMemoListLoadPokemon(c->pos + c->top);
}

void menuPdaMemoXD::Init(CURSOR* c) {
    prevItem = item;
    item = 0;
    prevItem = 0;
    menuID = 0x7C;
    cursor = &_cursor;
    angleZ = 0.0f;
    angleY = 0.0f;
    angleX = 0.0f;
    zoom = 0.75f;
    SetModelAngle(0);
    menuModelSetZoom(menuPdaMemoListGetMenuModelWork(), zoom);
}

long menuPdaMemoXD::TaskOpen() {
    long result = -1;
    switch (item) {
    case 0:
        menuCloseSync(0x7C, 1);
        return menuOpenCustom(0x7C, windowGetActiveID(), 0, 0, 1, 1, this);
    case 1:
    case 2:
        return menuOpenCustom(0x7D, windowGetActiveID(), 0, 0, 1, 1, this);
    case 3:
        menuCloseSync(0x7E, 1);
        result = menuOpenCustom(0x7E, windowGetActiveID(), 0, 0, 1, 1, this);
        break;
    }
    return result;
}

void menuPdaMemoXD::TaskClose(tagWINDOW_WORK* window, bool sync) {
    s32 cur = item;
    if (window != 0) {
        window->unkA4 = 1;
    }
    if (menuModelGetModelPtr(menuPdaMemoListGetMenuModelWork()) != 0) {
        GSmodelDestroyLinkedParticles();
    }
    switch (cur) {
    case 0:
        if (winSeqCheckMove(0x7C) == 0) {
            _menuClose(0x7C, sync);
        }
        break;
    case 1:
        if (winSeqCheckMove(0x7D) == 0) {
            _menuClose(0x7D, sync);
            menuPdaMemoWaveInit();
        }
        break;
    case 2:
        if (winSeqCheckMove(0x7D) == 0) {
            _menuClose(0x7D, sync);
        }
        break;
    case 3:
        if (winSeqCheckMove(0x7E) == 0) {
            _menuClose(0x7E, sync);
        }
        break;
    }
}

bool menuPdaMemoXD::TaskCloseCheck() {
    u16 id = 0;
    switch (item) {
    case 0:
        id = 0x7C;
        break;
    case 1:
        id = 0x7D;
        break;
    case 2:
        id = 0x7D;
        break;
    case 3:
        id = 0x7E;
        break;
    }
    if (id == 0) {
        return true;
    }
    return winSeqCheckMove(id) == 0;
}

void menuPdaMemoXD::_menuClose(long menuID, bool sync) {
    menuClose(menuID);
    menuCloseSync(menuID, sync);
}
