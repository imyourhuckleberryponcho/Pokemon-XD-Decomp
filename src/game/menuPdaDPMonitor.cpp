#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/gcptr.h>
#include <game/gcdata.h>
#include <game/statusval.h>
#include <dolphin/gx/GXVert.h>
#ifdef __MWERKS__
#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)
#else
#define GXFifoNV GXWGFifo
#endif

#pragma peephole off

enum darkPokemonWhere { place0, place1, place2, place3, place4, place5, place6 };

struct DarkPokemon {
public:
    u8 unk0x0[60];
    u16 getPokemonID() const;
    s32 getInitDarkPointDirect() const;
    s32 getDarkPointDirect() const;
    s32 getStatus() const;
    void setUpdate(bool update);
    bool isUpdate() const;
    bool isSnach() const;
    bool isRelive() const;
#ifdef __MWERKS__
    u16 getCatchBallID() const;
#else
    u8 getCatchBallID() const;
#endif
    u16 getCatchFloorId() const;
    u16 getOrgTrainer() const;
    const u16* getTrainerName() const;
    u32 getRnd() const;
};

struct CURSOR {
    s16 top;
    s16 pos;
};

struct DPM_CONTENTS {
    CURSOR* cursor;
};

struct MENU_MODEL {
    u8 unk0[0x58];
    void* slot58;
    u8 pad5C[0x10];
    void* slot6C;
    void* slot70;
    void* slot74;
    void* slot78;
    u8 pad7C[0x70];
};

struct MenuItem {
    u8 unk0[6];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    s8 seqSet;
    u8 unk3;
    s32 seq;
    u8 unk8[0x4];
    void* slotC;
    void* slot10;
    void* slot14;
    u8 pad18[0x4];
    s32 layer;
    u8 unk20[0x4];
    void* slot24;
    void* slot28;
    void* slot2C;
    u8 pad30[0x38];
    DPM_CONTENTS* contents;
    void* slot6C;
    void* slot70;
    void* slot74;
    void* slot78;
    void* slot7C;
    void* slot80;
    void* slot84;
    u8 pad88[0xB];
    u8 alpha;
    u8 unk94[0x10];
    u8 unkA4;
    u8 unkA5;
};

struct tagSPRITE_WORK {
    void* unk0;
    s8 flags;
    u8 unk5;
    s16 id;
    u8 unk8[0x4];
    void* slotC;
    u8 pad10[0xC];
    s32 layer;
    u8 unk20[0x28];
    void* slot48;
    void* slot4C;
    u8 pad50[0x4];
    s16 width;
    s16 height;
};

struct WindowKeyInfo {
    u16 unk0;
    u16 unk2;
    u16 trigger;
};

struct GStexture {
    u8 pad0[7];
    u8 flag;
};

struct GSgfxVF;
enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

static inline void dpmVertex(tagWINDOW_WORK* window, s16 x, s16 y, f32 u, f32 v) {
    GXFifoNV.s16 = x;
    GXFifoNV.s16 = y;
    GXColor4u8(0xFF, 0xFF, 0xFF, window->alpha);
    GXFifoNV.f32 = u;
    GXFifoNV.f32 = v;
}

class menuPdaDPM {
public:
    menuPdaDPM(CURSOR* cursor);
    ~menuPdaDPM();
    void Release();
    void LoadPokemon(CURSOR* cursor);
    void Init(CURSOR* cursor);
    CURSOR* Main(CURSOR* cursor);
    void Button(tagWINDOW_WORK* window);
    void Ctrl(tagWINDOW_WORK* window);
    void Cursor(tagWINDOW_WORK* window);
    void SetViewFlag(CURSOR* cursor);
    void DispPokemonModel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents);
    void DarkPokemonRelive(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents);
    void DarkPokemonRibbon(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents);
    void DarkPokemonInfo(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents);
    void DarkPokemonPlace(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents);
    void PokemonName(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents);
    void PokemonSex(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents);
    void PokemonBall(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents);
    void _menuClose(s32 menuID);
    void* GetPokemonPointer(s32 index);

    s32 rnd;
    u8 pokemon[0xC4];
    MENU_MODEL model;
};

extern "C" {
#ifdef __MWERKS__
void* __nw__FUl(u32);
void __dl__FPv(void*);
#else
#define __nw__FUl(n) (operator new(n))
#define __dl__FPv(p) (operator delete(p))
#endif
GSgfxLayer* GSgfxLayerFindByID(GCsptr);
GSgfxVF* GSgfxVFGetPredef(s32);
u16 * GSmsgGetGSchar(u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void GSsndPlayNow(u32);
DarkPokemon* darkPokemonGetDarkPokemon(u32);
u32 floorGetPlaceName(PCARG(u16, u32));
StatusS32 gamedataGetStatus(s32, s32);
u16 mballBiosGetSpriteID(u16);
void menuClose(s32);
void menuCloseSync(s32, s32);
void menuDrawReliveUpdate(void);
MenuItem* menuItemBiosGetPtr(s32, s32);
void menuModelAdjustCamera(MENU_MODEL*);
u8 menuModelCheck(MENU_MODEL*, s32);
void menuModelInit(MENU_MODEL*, s32, s32);
void menuModelLoadPokemon(MENU_MODEL*, void*);
GStexture* menuModelRender(MENU_MODEL*);
void menuModelSetAngle(MENU_MODEL*, f32*);
void menuModelSetSize(MENU_MODEL*, s32, s32, s32, s32);
void menuModelSetZoom(MENU_MODEL*, f32);
void menuModelTerm(MENU_MODEL*);
s32 menuOpenCustom(s32, ...);
s32 menuPdaDPMListDispRelive(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32, s32, u8, u8);
s32 menuPdaDPMListGetDPNum(void);
DarkPokemon* menuPdaDPMListGetDPointer(s32);
u16 menuPdaDPMListGetDarkPokemonID(s32);
u32 menuPdaDPMListGetDarkPokemonPlaceMsgID(s32, u8*);
s32 menuPdaDPMListGetDarkpokemonID(s32);
s32 menuPdaDPMListGetPokemonID(s32);
u32 menuPdaDPMListGetPokemonName(s32);
void menuPdaSetSubres(s32, s32);
void menuPlaySe(s32 menuID, s32);
void msgctrlSetValue(s32, GCuptr);
void pokemonBiosSetDarkpokemonDataId(void*, s32);
void pokemonBiosSetRnd(void*, s32);
void pokemonCreate(void*, s32, s32, s32);
s32 pokemonCreateRndFit(void*, s32, s32, s32, s32);
u8 pokemonGetSex(void*);
u8 winSeqCheckMove(s32 menuID);
void winSeqSetMenu(s32 menuID, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void windowDrawSprite(s32, s32, tagWINDOW_WORK*, u16, s32, s32);
s32 windowGetActiveID(void);
WindowKeyInfo* windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
}

static menuPdaDPM* _pDPM;
static CURSOR _cursor;

extern "C" {

s32 menuPdaDPMCallBack(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (_pDPM == 0) {
        return 0;
    }
    DPM_CONTENTS* contents = window->contents;
    switch (sprite->id) {
    case 0x68:
        _pDPM->DispPokemonModel(window, sprite, contents);
        break;
    case 0x62:
        _pDPM->DarkPokemonRibbon(window, sprite, contents);
        break;
    case 0x69:
        _pDPM->DarkPokemonInfo(window, sprite, contents);
        break;
    case 0x67:
        _pDPM->DarkPokemonRelive(window, sprite, contents);
        break;
    case 0x6A:
        _pDPM->DarkPokemonPlace(window, sprite, contents);
        break;
    case 0x6D:
        _pDPM->PokemonName(window, sprite, contents);
        break;
    case 0x6C:
        _pDPM->PokemonSex(window, sprite, contents);
        break;
    case 0x61:
        _pDPM->PokemonBall(window, sprite, contents);
        break;
    }
    return 0;
}

void menuPdaDPMButton(tagWINDOW_WORK* window) {
    if (_pDPM != 0) {
        _pDPM->Button(window);
    }
}

s32 menuPdaDPMCursor(tagWINDOW_WORK* window) {
    if (_pDPM == 0) {
        return 0;
    }
    _pDPM->Cursor(window);
    return 0;
}

s32 menuPdaDPMCtrl(tagWINDOW_WORK* window) {
    if (_pDPM == 0) {
        return 0;
    }
    _pDPM->Ctrl(window);
    return 0;
}

CURSOR* menuPdaDPMon(CURSOR* cursor) {
    _pDPM = new menuPdaDPM(cursor);
    _pDPM->Main(cursor);
    delete _pDPM;
    _pDPM = 0;
    return &_cursor;
}

}

menuPdaDPM::~menuPdaDPM() {
    Release();
}

menuPdaDPM::menuPdaDPM(CURSOR* cursor) {
    Init(cursor);
}

void menuPdaDPM::Release() {
    menuModelTerm(&model);
}

void menuPdaDPM::LoadPokemon(CURSOR* cursor) {
    void* mon = GetPokemonPointer(cursor->pos + cursor->top);
    menuModelLoadPokemon(&model, mon);
}

void menuPdaDPM::Init(CURSOR* cursor) {
    MenuItem* item = menuItemBiosGetPtr(0x75, 0x68);
    menuModelInit(&model, item->width, item->height);
    LoadPokemon(cursor);
}

CURSOR* menuPdaDPM::Main(CURSOR* cursor) {
    _cursor.pos = cursor->pos;
    _cursor.top = cursor->top;
    CURSOR* contents;
    do {
        contents = &_cursor;
    } while (menuOpenCustom(0x75, windowGetActiveID(), 0, 0, 1, 1, &contents) != -1);
    _menuClose(0x75);
    return &_cursor;
}

void menuPdaDPM::Button(tagWINDOW_WORK* window) {
    if (window != 0 && winSeqCheckMove(window->seq) == 0 && (windowGetKeyInfo()->trigger & 0x20) != 0) {
        window->unkA4 = 1;
        window->unkA5 = 1;
    }
}

void menuPdaDPM::Ctrl(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x132);
            window->seqSet = 1;
            menuPdaSetSubres(0, 2);
        }
        break;
    case 2:
        menuDrawReliveUpdate();
        break;
    case 3:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x136);
            window->seqSet = 1;
        }
        break;
    }
}

void menuPdaDPM::Cursor(tagWINDOW_WORK* window) {
    int prev;
    windowGetKeyInfo();
    s8 last;
    CURSOR* c = window->contents->cursor;
    int n = menuPdaDPMListGetDPNum();
    int visible = 10;
    u16 key = windowGetKeyRepeat();
    s16 oldPos = c->pos;
    s16 oldTop = c->top;
    prev = oldPos;
    prev += oldTop;
    if (n < 10) {
        visible = n;
    }
    if ((key & 1) != 0) {
        if (prev != 0) {
            GSsndPlayNow(0x450);
        }
        c->pos -= 1;
    } else if ((key & 2) != 0) {
        if (n - 1 != oldPos + oldTop) {
            GSsndPlayNow(0x450);
        }
        c->pos += 1;
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
        c->top += pos - (visible - 1);
        last = visible - 1;
        c->pos = last;
        if (c->top + c->pos >= n) {
            c->pos = last;
            c->top = (s8)(n - visible);
        }
    }
    if (prev != c->pos + c->top) {
        SetViewFlag(c);
        LoadPokemon(c);
        menuPlaySe(window->seq, 1);
    }
}

void menuPdaDPM::SetViewFlag(CURSOR* cursor) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(menuPdaDPMListGetDarkPokemonID(cursor->pos + cursor->top));
    if (dark->isUpdate()) {
        dark->setUpdate(false);
    }
}

void menuPdaDPM::DispPokemonModel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents) {
    f32 angle[3];
    angle[0] = 0.0f;
    angle[1] = 0.3f;
    angle[2] = 0.0f;
    if (menuModelCheck(&model, 0) == 0) {
        MenuItem* item = menuItemBiosGetPtr(0x75, 0x68);
        menuModelAdjustCamera(&model);
        menuModelSetAngle(&model, angle);
        menuModelSetSize(&model, item->x, item->y, item->width, item->height);
        menuModelSetZoom(&model, 0.85f);
        menuModelRender(&model);
        GStexture* tex = menuModelRender(&model);
        if (tex != 0) {
            GSgfxLayer* layer = GSgfxLayerFindByID(window->layer);
            if (layer != 0) {
                (*(u32*)&layer->unk1998) = 0x98;
                layer->setRenderStateAndSelect(GSgfxVFGetPredef(7));
                if ((*(GStexture**)&layer->dirty[0].tex[0]) != tex || (*(GStexture**)&layer->dirty[1].tex[0]) != tex || tex->flag != 0) {
                    (*(GStexture**)&layer->dirty[0].tex[0]) = tex;
                    (*(u32*)&layer->dirty[0].texMask) |= 1;
                    (*(GStexture**)&layer->dirty[1].tex[0]) = tex;
                    (*(u32*)&layer->dirty[1].texMask) |= 1;
                }
                layer->beginSurface(4);
                f32 zero = 0.0f;
                f32 one = 1.0f;
                dpmVertex(window, 0, 0, zero, zero);
                dpmVertex(window, sprite->width, 0, one, zero);
                dpmVertex(window, 0, sprite->height, zero, one);
                dpmVertex(window, sprite->width, sprite->height, one, one);
                layer->endSurface();
            }
        }
    }
}

void menuPdaDPM::DarkPokemonRelive(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    menuPdaDPMListDispRelive(window, sprite, 0, 0, c->pos + c->top, window->alpha, 1);
}

void menuPdaDPM::DarkPokemonRibbon(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    DarkPokemon* dark = menuPdaDPMListGetDPointer(c->pos + c->top);
    if (dark->getStatus() >= 4) {
        sprite->flags |= 2;
    } else {
        sprite->flags &= ~2;
    }
}

void menuPdaDPM::DarkPokemonInfo(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    DarkPokemon* dark = menuPdaDPMListGetDPointer(c->pos + c->top);
    u16 floorID = (u16)dark->getCatchFloorId();
    s32 status = dark->getStatus();
    s32 layer = winSpriteGetLayerID(window, sprite);
    u32 msg;
    if (dark->getPokemonID() == 0xAF) {
        msg = 0x3C2F;
    } else if (status >= 3) {
        msg = 0x3B63;
    } else {
        msg = 0x3B65;
    }
    if (floorID == 0xB5) {
        msg = 0x3C30;
    }
    if (msg != 0) {
        dark->getOrgTrainer();
        u32 place = floorGetPlaceName(floorID);
        if (place == 0) {
            place = 0x3BA8;
        }
        u32 placeName = GC_ADDR32(GSmsgGetGSchar(place));
        msgctrlSetValue(0x4D, placeName);
        msgctrlSetValue(0x57, (GCuptr)dark->getTrainerName());
        GSmsgPrint2(layer, 0, 0, window->alpha | ~0xFF, msg);
    }
}

void menuPdaDPM::DarkPokemonPlace(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    u8 floor;
    u32 msg = menuPdaDPMListGetDarkPokemonPlaceMsgID(c->pos + c->top, &floor);
    if (msg != 0) {
        msgctrlSetValue(0x2F, floor + 1);
        u32 name = GC_ADDR32(GSmsgGetGSchar(msg));
        msgctrlSetValue(0x37, name);
        GSmsgPrint2(window->layer, 0, 0, window->alpha | ~0xFF, 0x4275);
    }
}

void menuPdaDPM::PokemonName(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    u32 name = menuPdaDPMListGetPokemonName(c->pos + c->top);
    if (name == 0) {
        name = GC_ADDR32(GSmsgGetGSchar(1));
    }
    msgctrlSetValue(0x37, name);
    GSmsgPrint2(window->layer, 0, 0, window->alpha | ~0xFF, 0x4275);
}

void menuPdaDPM::PokemonSex(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    int index = c->pos + c->top;
    void* mon;
    DarkPokemon* dark = menuPdaDPMListGetDPointer(index);
    mon = GetPokemonPointer(index);
    u32 darkRnd = dark->getRnd();
    pokemonBiosSetRnd(mon, darkRnd);
    u8 sex = pokemonGetSex(mon);
    pokemonBiosSetRnd(mon, rnd);
    u32 name;
    if (sex == 0x80) {
        name = GC_ADDR32(GSmsgGetGSchar(1));
    } else {
        switch (sex) {
        case 0:
            name = GC_ADDR32(GSmsgGetGSchar(0x9C5));
            break;
        case 1:
            name = GC_ADDR32(GSmsgGetGSchar(0x9C6));
            break;
        case 2:
            name = GC_ADDR32(GSmsgGetGSchar(1));
            break;
        default:
            name = GC_ADDR32(GSmsgGetGSchar(0x9C6));
            break;
        }
    }
    if (dark->getCatchFloorId() == 0xB5 && sex != 2) {
        name = GC_ADDR32(GSmsgGetGSchar(0x9C7));
    }
    msgctrlSetValue(0x37, name);
    GSmsgPrint2(window->layer, 0, 0, window->alpha | ~0xFF, 0x4275);
}

void menuPdaDPM::PokemonBall(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, DPM_CONTENTS* contents) {
    CURSOR* c = contents->cursor;
    DarkPokemon* dark = menuPdaDPMListGetDPointer(c->pos + c->top);
    if (dark->isSnach()) {
        u16 id = mballBiosGetSpriteID(dark->getCatchBallID());
        if (id != 0) {
            windowDrawSprite(0, 0, window, id, 0, window->layer);
        }
    }
}

void menuPdaDPM::_menuClose(s32 menuID) {
    menuClose(menuID);
    menuCloseSync(menuID, 1);
}

void* menuPdaDPM::GetPokemonPointer(s32 index) {
    s32 id = menuPdaDPMListGetPokemonID(index);
    pokemonCreate(pokemon, id, 0xA, gamedataGetStatus(0, 1));
    DarkPokemon* dark = menuPdaDPMListGetDPointer(index);
    s32 darkID = menuPdaDPMListGetDarkpokemonID(index);
    dark->getDarkPointDirect();
    rnd = pokemonCreateRndFit(pokemon, -1, -1, 0, 0);
    pokemonBiosSetRnd(pokemon, rnd);
    if (!dark->isRelive()) {
        pokemonBiosSetDarkpokemonDataId(pokemon, darkID);
    } else {
        pokemonBiosSetDarkpokemonDataId(pokemon, 0);
    }
    return pokemon;
}
