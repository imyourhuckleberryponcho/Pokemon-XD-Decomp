#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
#include <game/shared/menu_work.h>

#pragma peephole off
#pragma pool_strings off

struct GSgfxVF;
struct Pokemon;
struct Hero;
struct FIGHT_FLOOR;

enum GSgfxLayerID { GSgfxLayerID0 };
enum SHEET { SHEET0, SHEET1 };
enum DAKUON_MODE { DAKUON_NONE = 0, DAKUON_DAKU = 1, DAKUON_HAN = 1 };

struct GStexture {
    u8 pad0[7];
    u8 flag;
};

class GSgfxLayer {
public:
    u8 pad0[0x173C];
    u32 f173C;
    GStexture* tex1740;
    u8 pad1744[0x17F4 - 0x1744];
    u32 f17F4;
    GStexture* tex17F8;
    u8 pad17FC[0x1998 - 0x17FC];
    u32 primitive;
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

struct NAME_ENTRY_ARG {
    u16 defName[12];
    u16* name;
    s32 mode;
    s32 param;
    s32* sheet;
    s32* curX;
    s32* curY;
    f32* animTime;
    s32* nameCurX;
    s32* defSheetCurPosX;
    s32* defSheetCurPosY;
    s32* defNamePokemonCurPosX;
    s32* defNameBoxCurPosX;
    s32* defNameTrainerCurPosX;
};

struct MODE_DATA {
    u32 titleMsg;
    s32 maxLen;
    const u32* defNames;
    s32 defCount;
};

struct SHEET_DATA {
    u32 unk0;
    u32 xButtonMsg;
    u32 rows[8];
    u32 pad28;
};

struct BALL_WORK {
    s32 active;
    f32 x;
    f32 y;
    f32 scale;
    f32 maxScale;
    s32 color;
    u8 alpha;
    f32 time;
    f32 life;
};

struct MENU_MODEL {
    MENU_MODEL() {}
    u8 unk0[0x24];
    u16 pokemonID;
    u8 unk26[0xEC - 0x26];
};

struct NAME_ENTRY_WORK {
    u16 name[12];
    s32 mode;
    s32 param;
    s32 result;
    s32 fadeOut;
    s32 onFloor;
    s32 pad2C;
};

struct MenuItem {
    u8 unk0[0xA];
    s16 w;
    s16 h;
};

struct MenuSpriteVal {
    u8 unk0[4];
    s16 w;
    s16 h;
};

static inline u32 colorAlpha(tagWINDOW_WORK* w) { return *(u32*)w->color; }
static inline NAME_ENTRY_ARG* entryArg(tagWINDOW_WORK* w) { return (NAME_ENTRY_ARG*)w->params[0]; }

extern "C" {
void winSpriteSetDisp(tagSPRITE_WORK*, bool);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void menuSubDrawCursorBackAnimeOnOffAuto(tagWINDOW_WORK*, s32, s32, s32, s32, s32, u8, u8);
GSgfxLayer* GSgfxLayerFindByID(s32);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 heroGetStatus(Hero*, u32, u16);
Pokemon* fightFloorGetDefPokemonPtr(FIGHT_FLOOR*);
u8 pokemonGetSex(Pokemon*);
bool pokemonCheckValid(Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
void msgctrlSetValue(s32, u32);
u16* GSmsgGetGSchar(u32);
s32 GSmsgGetLength(u32);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void windowDrawSprite(s16, s16, void*, u16, u32, s32);
double sin(double);
}

static const u32 DefKenName[3] = {0x3B20, 0x3B21, 0x3B22};
static const u32 DefHizukiName[3] = {0x3B20, 0x3B21, 0x3B22};

static const MODE_DATA ModeData[7] = {
    {0x3B11, 7, DefKenName, 3},
    {0x3B11, 7, DefHizukiName, 3},
    {0x3B12, 10, 0, 0},
    {0x3B13, 8, 0, 0},
    {0x3B12, 10, 0, 0},
    {0x3B12, 10, 0, 0},
    {0x3C33, 10, 0, 0},
};

static const SHEET_DATA SheetData[2] = {
    {0x0B570200, 0x3B14, {0x3AFD, 0x3AFE, 0x3AFF, 0x3B00, 0x3BF4, 0x3BF5, 0, 0}, 0},
    {0x023C5700, 0x3B15, {0x3B01, 0x3B02, 0x3B03, 0x3B04, 0x3BF6, 0x3BF7, 0, 0}, 0},
};

static BALL_WORK BallWork[30];
static MENU_MODEL MenuModel;
static NAME_ENTRY_WORK NameEntryWork;

static s32 Sheet;
static s32 SheetCurX;
static s32 SheetCurY;
static f32 SheetCurAnimTime;
static s32 NameCurX;
static s32 DefSheetCurPosX;
static s32 DefSheetCurPosY;
static s32 DefNamePokemonCurPosX;
static s32 DefNameBoxCurPosX;
static s32 DefNameTrainerCurPosX;

extern const u32 DakuHanTbl[2] = {0, 0x3B1B};

static s32 menuNameEntryDrawNameCursor(tagWINDOW_WORK*, tagSPRITE_WORK*, int, int);
static s32 menuNameEntryDrawNameText(tagWINDOW_WORK*, tagSPRITE_WORK*, int, int);
static void putGScharL(GSgfxLayerID, int, int, unsigned long, unsigned short);
static u16 getCharSheet(SHEET, int, int);
static int getSpchar(unsigned short);

extern "C" {
u8 GSsndPlayNow(u32);
s32 winMsgOpen(s8, void*, bool, bool);
void winMsgClose(bool);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
u32 windowGetKeyRepeat(void);
u32 windowGetKeyTrg(void);
void winSeqSetMenu(s32, u32);
void dbgMenuSetEnable(u8);
void GScharCpy(u16*, const u16*);
s32 GScharCmp(const u16*, const u16*);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, ...);
void menuClose(s32);
void menuCloseSync(s32, s32);
}

static int setName(unsigned short*, int, int);
static int getName(unsigned short*, int, int);

struct S16x2 {
    s16 a;
    s16 b;
};

struct MODEL_ARG {
    s32 mode;
    s32 param;
};

extern "C" {
MenuItem* menuItemBiosGetPtr(s32, s32);
void menuModelAdjustCamera(MENU_MODEL*);
void menuModelSetSize(MENU_MODEL*, s16, s16, s16, s16);
void menuModelSetClip(MENU_MODEL*, s32);
void menuModelSetAngle(MENU_MODEL*, f32*);
void menuModelSetZoom(MENU_MODEL*, f32);
void menuModelSetOffset(MENU_MODEL*, f32*);
GStexture* menuModelRender(MENU_MODEL*);
void menuModelInit(MENU_MODEL*, s32, s32);
void menuModelLoad(MENU_MODEL*, u32);
void menuModelLoadPokemon(MENU_MODEL*, Pokemon*);
void menuModelCheck(MENU_MODEL*, s32);
void menuModelTerm(MENU_MODEL*);
void menuModelSetMotion(MENU_MODEL*, s32);
void* menuSpriteBiosGetPtr(u32);
MenuSpriteVal* menuSpriteBiosGetValPtr(void*);
void windowDrawSprite2(s32, s32, s32, s32, s32, tagWINDOW_WORK*, u16, s32, s32);
f32 HSD_Randf(void);
void* peopleInfoBiosGetPtr(u32);
void peopleInfoBiosGetMotion(void*, u8, s32*, u8*);
void FlashSystemSetPlayFrameLabel(u32, const char*, const char*);
void FlashSystemSetLoopFlag(u32, s32);
void FlashSystemSetNowFrameLabel(u32, const char*);
void fadeSet(s32, f32);
void fadeCheck(s32);
void GSfloorPush(u32);
void GSfloorPop(void);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
void menuTitleBattleSelectFree(void);
bool menuIsCheck(s32);
void menuSetDisp(s32, s32);
void heroSetStatus(Hero*, u32, u32);
void pokemonBiosSetNicknamePtr(Pokemon*, void*);
u16* pokemonBiosGetNicknamePtr(Pokemon*);
void pcboxSetPokemonBoxName(void*, s8, u16*);
u16* pcboxGetPokemonBoxName(void*, s8);
}

#define DRAW_TITLE(msg)                                                         {                                                                               tw = GSmsgGetRect(msg) >> 16;                                           s32 layer = winSpriteGetLayerID(w, sp);                                     s32 d = sp->w - tw;                                                         GSmsgPrint2(layer, d / 2, 0, w->alpha | ~0xFF, msg);                    }

struct SELECT_ARG {
    const u32* list;
    s32 count;
};

static inline void vertex(s16 x, s16 y, f32 u, f32 v) {
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.f32 = u;
    GXWGFifo.f32 = v;
}

extern "C" {
s32 menuNameEntryDrawBkCur(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawNamePokemonWaku(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawNameTrainerCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawNameRuleText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawNameTrainerText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawNameBoxText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawNamePokemonText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawStartCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawBCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDraw50Cursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDraw50Text(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawXButtonText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryDrawTitle(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryCursor(tagWINDOW_WORK* w);
s32 menuNameEntryCtrl(tagWINDOW_WORK* w);
s32 menuNameEntrySelectDrawSelText3(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntrySelectDrawSelText2(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntrySelectDrawSelText1(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
void menuNameEntrySelectButton(tagWINDOW_WORK* w);
s32 menuNameEntrySelectCtrl(tagWINDOW_WORK* w);
s32 menuNameEntryBackDrawHumanModel(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryBackDrawPokemonModel(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryBackDrawBall(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
s32 menuNameEntryBackCtrl(tagWINDOW_WORK* w);
void menuNameEntry(void);
s32 menuNameEntryCall(s32 mode, s32 param);
void menuNameEntryGetLastName(u16* out);
s32 menuNameEntryOpenNoFade(s32 mode, s32 param);
s32 menuNameEntryOpen(s32 mode, s32 param);
void menuNameEntryButton(void);
}

static void drawTexture(GStexture* tex, tagSPRITE_WORK* sp, GSgfxLayerID id);
static s32 menuNameEntryDrawNameCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, int len, int kind);
static s32 menuNameEntryDrawNameText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, int len, int kind);
static void drawControlCursor(NAME_ENTRY_ARG* a, tagSPRITE_WORK* sp);
static u16 getCharSheet(SHEET sheet, int idx, int row);
static int getGScharLen(unsigned short* s);
static void putGScharL(GSgfxLayerID layer, int x, int y, unsigned long color, unsigned short ch);
static u16 exchangeDakuon(unsigned short ch, DAKUON_MODE mode);
static int confirmName(unsigned short* name);
static bool backNameCursor(NAME_ENTRY_ARG* a);
static int getSpchar(unsigned short ch);
static void change50Sheet(NAME_ENTRY_ARG* a);
static int selectLetter(NAME_ENTRY_ARG* a);
static int chkValidName(unsigned short* name);
static int inputName(unsigned short* name, unsigned short* defName, int mode, int param, int flag);
static void setDefNameText(tagSPRITE_WORK* sp, unsigned long msg);
static int selectName(unsigned short* name, const unsigned long* list, int count);
static void ballMain1(BALL_WORK* b);
static void generateBall(void);
static void ballMain(void);
static void loadModel(long id, MENU_MODEL* model, int mode, int param);
static int setName(unsigned short* name, int mode, int param);
static int getName(unsigned short* out, int mode, int param);
static int chkParam(int mode, int param);
static int pushNameEntryFloor(int mode, int param, int flag);

s32 menuNameEntryOpen(s32 mode, s32 param) {
    int ids[4] = {0x37, 0x40, 0x38, 0x41};
    s32 result;
    int i;
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 0);
        }
    }
    result = pushNameEntryFloor(mode, param, 1);
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 1);
        }
    }
    return result;
}

s32 menuNameEntryOpenNoFade(s32 mode, s32 param) {
    return pushNameEntryFloor(mode, param, 0);
}

static int pushNameEntryFloor(int mode, int param, int flag) {
    if (chkParam(mode, param) == 0) {
        return 0;
    }
    NameEntryWork.name[0] = 0;
    NameEntryWork.mode = mode;
    NameEntryWork.param = param;
    NameEntryWork.result = 0;
    NameEntryWork.fadeOut = flag;
    NameEntryWork.onFloor = 1;
    GSfloorPush(0x390);
    if (flag == 0) {
        floorSetFadeScript(0, 0x05960008);
    }
    floorWaitForChange();
    return NameEntryWork.result;
}

void menuNameEntryGetLastName(u16* out) {
    GScharCpy(out, NameEntryWork.name);
}

s32 menuNameEntryCall(s32 mode, s32 param) {
    if (chkParam(mode, param) == 0) {
        return 0;
    }
    NameEntryWork.name[0] = 0;
    NameEntryWork.mode = mode;
    NameEntryWork.param = param;
    NameEntryWork.result = 0;
    NameEntryWork.onFloor = 0;
    menuNameEntry();
    return NameEntryWork.result;
}

static int chkParam(int mode, int param) {
    int ok = 1;
    switch (mode) {
    case 2:
        if (!pokemonCheckValid((Pokemon*)heroGetStatus(0, 3, (u16)param))) {
            ok = 0;
        }
        break;
    case 3:
        if (param < 0 || param >= 8) {
            ok = 0;
        }
        break;
    case 4:
        if (!pokemonCheckValid(fightFloorGetDefPokemonPtr(0))) {
            ok = 0;
        }
        break;
    case 0:
    case 1:
    case 5:
    case 6:
        break;
    default:
        ok = 0;
        break;
    }
    return ok;
}

static int getName(unsigned short* out, int mode, int param) {
    u16* src;
    switch (mode) {
    case 0:
        src = GSmsgGetGSchar(DefKenName[0]);
        break;
    case 1:
        src = GSmsgGetGSchar(DefHizukiName[0]);
        break;
    case 2: {
        Pokemon* p = (Pokemon*)heroGetStatus(0, 3, (u16)param);
        if (!pokemonCheckValid(p)) {
            src = 0;
        } else {
            src = pokemonBiosGetNicknamePtr(p);
        }
        break;
    }
    case 5:
        src = pokemonBiosGetNicknamePtr((Pokemon*)param);
        break;
    case 3:
        src = pcboxGetPokemonBoxName(0, (s8)param);
        break;
    case 4: {
        Pokemon* p = fightFloorGetDefPokemonPtr(0);
        if (!pokemonCheckValid(p)) {
            src = 0;
        } else {
            src = pokemonBiosGetNicknamePtr(p);
        }
        break;
    }
    case 6:
        src = (u16*)param;
        break;
    default:
        src = 0;
        break;
    }
    if (src == 0) {
        return 0;
    }
    GScharCpy(out, src);
    return 1;
}

static int setName(unsigned short* name, int mode, int param) {
    Pokemon* p;
    int ok = 1;
    switch (mode) {
    case 1:
        heroSetStatus(0, 0x17, (u32)name);
        break;
    case 2: {
        p = (Pokemon*)heroGetStatus(0, 3, (u16)param);
        if (!pokemonCheckValid(p)) {
            ok = 0;
        } else {
            pokemonBiosSetNicknamePtr(p, name);
        }
        break;
    }
    case 5:
        pokemonBiosSetNicknamePtr((Pokemon*)param, name);
        break;
    case 3:
        pcboxSetPokemonBoxName(0, (s8)param, name);
        break;
    case 4: {
        p = fightFloorGetDefPokemonPtr(0);
        if (!pokemonCheckValid(p)) {
            ok = 0;
        } else {
            pokemonBiosSetNicknamePtr(p, name);
        }
        break;
    }
    case 6:
        GScharCpy((u16*)param, name);
        break;
    case 0:
        break;
    default:
        ok = 0;
        break;
    }
    return ok;
}

void menuNameEntry(void) {
    u16 buf[12];
    MODEL_ARG arg;
    if (getName(buf, NameEntryWork.mode, NameEntryWork.param) == 0) {
        buf[0] = 0;
    }
    loadModel(0x68, &MenuModel, NameEntryWork.mode, NameEntryWork.param);
    FlashSystemSetPlayFrameLabel(0x22063000, "start", "end");
    FlashSystemSetLoopFlag(0x22063000, 0);
    FlashSystemSetNowFrameLabel(0x22063000, "start");
    arg.mode = NameEntryWork.mode;
    arg.param = NameEntryWork.param;
    menuOpenCustom(0x68, windowGetActiveID(), 0, 0, 1, 1, (s32)&arg);
    if (NameEntryWork.onFloor == 0) {
        fadeSet(2, 0.5f);
        fadeCheck(1);
    }
    if (ModeData[NameEntryWork.mode].defCount > 0) {
        int again = 1;
        while (again != 0) {
            const MODE_DATA* md = &ModeData[NameEntryWork.mode];
            switch (selectName(NameEntryWork.name, md->defNames, md->defCount)) {
            case 1:
                if (inputName(NameEntryWork.name, buf, NameEntryWork.mode, NameEntryWork.param, 0) != 0) {
                    again = 0;
                }
                break;
            case 2:
                again = 0;
                break;
            default:
                again = 0;
                break;
            }
        }
    } else {
        inputName(NameEntryWork.name, buf, NameEntryWork.mode, NameEntryWork.param, 1);
    }
    fadeSet(3, 0.5f);
    fadeCheck(1);
    menuModelTerm(&MenuModel);
    menuClose(0x68);
    menuCloseSync(0x68, 1);
    setName(NameEntryWork.name, NameEntryWork.mode, NameEntryWork.param);
    if (GScharCmp(NameEntryWork.name, buf) == 0) {
        NameEntryWork.result = 0;
    } else {
        NameEntryWork.result = 1;
    }
    if (NameEntryWork.mode == 0) {
        menuTitleBattleSelectFree();
    }
    if (NameEntryWork.onFloor != 0) {
        GSfloorPop();
        if (NameEntryWork.fadeOut != 0) {
            floorSetFadeScript(0, 0x05960008);
        } else {
            floorSetFadeScript(0, 0);
        }
    }
}

static void loadModel(long id, MENU_MODEL* model, int mode, int param) {
    u32 res[4] = {0x16C90400, 0x16C70400, 0, 0x10560400};
    s32 index;
    switch (mode) {
    case 2:
    case 4:
    case 5:
        index = 0x280;
        break;
    case 3:
    case 6:
    default:
        index = 0x27F;
        break;
    }
    MenuItem* item = menuItemBiosGetPtr(id, index);
    menuModelInit(model, item->w, item->h);
    switch (mode) {
    case 0:
    case 1: {
        u32 resID = res[mode];
        s32 motion;
        u8 loop;
        menuModelLoad(model, resID);
        peopleInfoBiosGetMotion(peopleInfoBiosGetPtr(resID), 1, &motion, &loop);
        menuModelSetMotion(model, motion);
        break;
    }
    case 2: {
        Pokemon* p = (Pokemon*)heroGetStatus(0, 3, (u16)param);
        if (pokemonCheckValid(p)) {
            menuModelLoadPokemon(model, p);
        }
        break;
    }
    case 5:
        menuModelLoadPokemon(model, (Pokemon*)param);
        break;
    case 3:
        menuModelLoad(model, res[mode]);
        break;
    case 4: {
        Pokemon* p = fightFloorGetDefPokemonPtr(0);
        if (pokemonCheckValid(p)) {
            menuModelLoadPokemon(model, p);
        }
        break;
    }
    case 6:
        break;
    }
    menuModelCheck(model, 1);
}

s32 menuNameEntryBackCtrl(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            int i;
            for (i = 0; i < 30; i++) {
                BallWork[i].active = 0;
            }
            for (i = 0; i < 600; i++) {
                ballMain();
            }
            w->seqSet = 1;
        }
        break;
    case 2:
        ballMain();
        break;
    case 3:
        if (w->seqSet == 0) {
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

static void ballMain(void) {
    generateBall();
    int i;
    for (i = 0; i < 30; i++) {
        if (BallWork[i].active != 0) {
            ballMain1(&BallWork[i]);
        }
    }
}

static void generateBall(void) {
    if (HSD_Randf() > 0.1f) {
        return;
    }
    int i;
    for (i = 0; i < 30; i++) {
        if (BallWork[i].active == 0) {
            break;
        }
    }
    if (i < 30) {
        BallWork[i].active = 1;
        BallWork[i].x = 640.0f * HSD_Randf();
        BallWork[i].y = 480.0f * HSD_Randf();
        BallWork[i].scale = 0.001f;
        BallWork[i].maxScale = 1.999f * HSD_Randf() + 0.001f;
        BallWork[i].color = -0x100;
        BallWork[i].alpha = 0x80;
        BallWork[i].time = 0.0f;
        BallWork[i].life = 60.0f * HSD_Randf() + 120.0f;
    }
}

static void ballMain1(BALL_WORK* b) {
    if (b->active != 0) {
        if ((b->time += 1.0f) >= b->life) {
            b->active = 0;
        }
        f32 t = b->time / b->life;
        b->scale = b->maxScale * t;
        b->alpha = (u8)(128.0f * (1.0f - t));
    }
}

s32 menuNameEntryBackDrawBall(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int i;
    MenuSpriteVal* val = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x1E));
    s16 vw = val->w;
    s16 vh = val->h;
    f32 half = 0.5f;
    for (i = 0; i < 30; i++) {
        if (BallWork[i].active != 0) {
            f32 sw = vw * BallWork[i].scale;
            f32 sh = vh * BallWork[i].scale;
            s32 color = BallWork[i].color | BallWork[i].alpha;
            f32 px = BallWork[i].x - sw * half;
            f32 py = BallWork[i].y - sh * half;
            windowDrawSprite2((s32)(half + px), (s32)(half + py), (s32)(half + sw), (s32)(half + sh), color, w, 0x1E, 0,
                              winSpriteGetLayerID(w, sp));
        }
    }
    return 0;
}

s32 menuNameEntryBackDrawPokemonModel(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    s32 mode = ((MODEL_ARG*)w->params[0])->mode;
    if (mode == 2 || mode == 4 || mode == 5) {
        S16x2 pos = {0, 0x78};
        S16x2 size = {0x12C, 0x12C};
        f32 angle[3];
        f32 offset[3];
        f32 zoom = 1.2f;
        angle[0] = 0.0f;
        angle[1] = 0.3f;
        angle[2] = 0.0f;
        offset[0] = 0.0f;
        offset[1] = 0.0f;
        offset[2] = 0.0f;
        switch (MenuModel.pokemonID) {
        case 0x28:
        case 0x3E:
        case 0x47:
        case 0x57:
        case 0x5F:
        case 0x60:
        case 0x6C:
        case 0xA3:
        case 0xAE:
        case 0xC0:
        case 0xE6:
        case 0x154:
        case 0x18E:
            zoom = 1.0f;
            break;
        case 0x1A:
        case 0x7B:
        case 0x97:
        case 0x143:
            zoom = 0.9f;
            break;
        case 0xE9:
            zoom = 0.8f;
            break;
        case 0xD0:
            zoom = 0.95f;
            break;
        }
        menuItemBiosGetPtr(w->menuID, sp->id);
        menuModelAdjustCamera(&MenuModel);
        menuModelSetSize(&MenuModel, pos.a, pos.b, size.a, size.b);
        menuModelSetClip(&MenuModel, 0);
        menuModelSetAngle(&MenuModel, angle);
        menuModelSetZoom(&MenuModel, zoom);
        menuModelSetOffset(&MenuModel, offset);
        GStexture* tex = menuModelRender(&MenuModel);
        if (tex != 0) {
            drawTexture(tex, sp, (GSgfxLayerID)winSpriteGetLayerID(w, sp));
        }
    }
    return 0;
}

s32 menuNameEntryBackDrawHumanModel(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    s32 mode = ((MODEL_ARG*)w->params[0])->mode;
    if (mode == 0 || mode == 1) {
        S16x2 pos = {0, 0x50};
        S16x2 size = {0x208, 0x12C};
        f32 angle[3];
        f32 offset[3];
        angle[0] = 0.0f;
        angle[1] = 0.3f;
        angle[2] = 0.0f;
        offset[0] = -4.0f;
        offset[1] = 0.0f;
        offset[2] = 0.0f;
        menuItemBiosGetPtr(w->menuID, sp->id);
        menuModelAdjustCamera(&MenuModel);
        menuModelSetSize(&MenuModel, pos.a, pos.b, size.a, size.b);
        menuModelSetClip(&MenuModel, 0);
        menuModelSetAngle(&MenuModel, angle);
        menuModelSetZoom(&MenuModel, 1.4f);
        menuModelSetOffset(&MenuModel, offset);
        GStexture* tex = menuModelRender(&MenuModel);
        if (tex != 0) {
            drawTexture(tex, sp, (GSgfxLayerID)winSpriteGetLayerID(w, sp));
        }
    }
    return 0;
}

static int selectName(unsigned short* name, const unsigned long* list, int count) {
    int r;
    int ok;
    u16* chosen;
    for (;;) {
        SELECT_ARG arg;
        arg.list = list;
        arg.count = count;
        r = menuOpenCustom(0x65, windowGetActiveID(), 0, 0, 1, 1, (s32)&arg);
        if (r == 0) {
            GSsndPlayNow(0x11);
            ok = 0;
            break;
        } else if (r == 4 || r == -1) {
            GSsndPlayNow(0x11);
            ok = 0;
            break;
        } else {
            chosen = GSmsgGetGSchar(list[r - 1]);
            if (confirmName(chosen)) {
                ok = 1;
                break;
            }
        }
    }
    menuClose(0x65);
    menuCloseSync(0x65, 1);
    if (ok) {
        GScharCpy(name, chosen);
        return 0;
    }
    if (r != 0) {
        return 2;
    }
    return 1;
}

s32 menuNameEntrySelectCtrl(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x58);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x5C);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

void menuNameEntrySelectButton(tagWINDOW_WORK* w) {
    u16 trg = windowGetKeyTrg();
    if (trg & 0x20) {
        w->cancel = 1;
        w->done = 1;
    }
    if (trg & 0x10) {
        w->done = 1;
    }
}

s32 menuNameEntrySelectDrawSelText1(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    setDefNameText(sp, (*(SELECT_ARG**)&w->params[0])->list[0]);
    return 0;
}

s32 menuNameEntrySelectDrawSelText2(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    setDefNameText(sp, (*(SELECT_ARG**)&w->params[0])->list[1]);
    return 0;
}

s32 menuNameEntrySelectDrawSelText3(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    setDefNameText(sp, (*(SELECT_ARG**)&w->params[0])->list[2]);
    return 0;
}

static void setDefNameText(tagSPRITE_WORK* sp, unsigned long msg) {
    msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
    sp->msgID = 0x4276;
}

static int inputName(unsigned short* name, unsigned short* defName, int mode, int param, int flag) {
    NAME_ENTRY_ARG arg;
    u16* result;
    int ok;
    int done = 0;
    GScharCpy(arg.defName, defName);
    *name = 0;
    arg.name = name;
    arg.mode = mode;
    arg.param = param;
    Sheet = 0;
    arg.sheet = &Sheet;
    SheetCurX = 0;
    arg.curX = &SheetCurX;
    SheetCurY = 0;
    arg.curY = &SheetCurY;
    SheetCurAnimTime = 0.0f;
    arg.animTime = &SheetCurAnimTime;
    NameCurX = 0;
    arg.nameCurX = &NameCurX;
    arg.defSheetCurPosX = &DefSheetCurPosX;
    arg.defSheetCurPosY = &DefSheetCurPosY;
    arg.defNamePokemonCurPosX = &DefNamePokemonCurPosX;
    arg.defNameBoxCurPosX = &DefNameBoxCurPosX;
    arg.defNameTrainerCurPosX = &DefNameTrainerCurPosX;
    dbgMenuSetEnable(0);
    while (done == 0) {
        menuOpenCustom(0x66, windowGetActiveID(), 0, 0, 1, 1, (s32)&arg);
        if (chkValidName(arg.name)) {
            result = arg.name;
        } else {
            result = arg.defName;
        }
        ok = confirmName(result);
        if (flag == 0) {
            done = 1;
            if (ok == 0) {
                NameEntryWork.name[0] = 0;
            }
        } else if (ok != 0) {
            done = 1;
        }
    }
    dbgMenuSetEnable(1);
    menuClose(0x66);
    menuCloseSync(0x66, 1);
    if (ok != 0) {
        GScharCpy(NameEntryWork.name, result);
        return 1;
    }
    return 0;
}

static int chkValidName(unsigned short* name) {
    int len = getGScharLen(name);
    if (len <= 0) {
        return 0;
    }
    u16* sp = GSmsgGetGSchar(0x3B1D);
    int i;
    for (i = 0; i < len; i++, name++) {
        if (*name != *sp) {
            break;
        }
    }
    if (i >= len) {
        return 0;
    }
    return 1;
}

void menuNameEntryButton(void) {}

s32 menuNameEntryCtrl(tagWINDOW_WORK* w) {
    NAME_ENTRY_ARG* a = entryArg(w);
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x58);
            *a->animTime = 0.0f;
            w->seqSet = 1;
        }
        break;
    case 2:
        if ((*a->animTime += 0.033333335f) >= 1.0f) {
            *a->animTime -= 1.0f;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x5C);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

s32 menuNameEntryCursor(tagWINDOW_WORK* w) {
    u32 rep0 = windowGetKeyRepeat();
    u16 trg = windowGetKeyTrg();
    NAME_ENTRY_ARG* a = entryArg(w);
    if (trg & 0x40) {
        change50Sheet(a);
        GSsndPlayNow(0x14);
        return 0;
    }
    if (trg & 0x10) {
        if (selectLetter(a)) {
            w->done = 1;
            return 0;
        }
        if (getGScharLen(a->name) >= ModeData[a->mode].maxLen) {
            *a->curX = 10;
            *a->curY = 7;
        }
        return 0;
    }
    if (trg & 0x20) {
        if (backNameCursor(a)) {
            GSsndPlayNow(0x12);
        }
        return 0;
    }
    if (trg & 0x400) {
        change50Sheet(a);
        GSsndPlayNow(0x14);
        return 0;
    }
    if (trg & 0x800) {
        w->done = 1;
        return 0;
    }
    u16 rep = rep0;
    if (rep & 8) {
        int x = *a->curX + 1;
        if (*a->curY < 6) {
            if (x < 11) {
                GSsndPlayNow(0x10);
            } else {
                x = 10;
            }
        } else if (x > 7) {
            x = 7;
        } else {
            GSsndPlayNow(0x10);
        }
        *a->curX = x;
    }
    if (rep & 4) {
        int x = *a->curX - 1;
        if (*a->curY > 5 && x > 6) {
            x = 6;
        }
        if (x < 0) {
            x = 0;
        } else {
            GSsndPlayNow(0x10);
        }
        *a->curX = x;
    }
    if (rep & 2) {
        int y = *a->curY;
        if (*a->curX >= 11) {
            if (y == 1) {
                y += 2;
            } else {
                y += 1;
            }
        } else {
            y += 1;
        }
        if (y >= 8) {
            y = 7;
        } else {
            GSsndPlayNow(0x10);
        }
        *a->curY = y;
    }
    if (rep & 1) {
        int y = *a->curY;
        if (*a->curX >= 11) {
            if (y == 2) {
                y -= 2;
            } else {
                y -= 1;
            }
        } else {
            y -= 1;
        }
        if (y < 0) {
            y = 0;
        } else {
            GSsndPlayNow(0x10);
        }
        *a->curY = y;
    }
    return 0;
}

static int selectLetter(NAME_ENTRY_ARG* a) {
    u16 ch;
    int ret = 0;
    u32 snd = 0;
    int x = *a->curX;
    int y = *a->curY;
    int kind;
    if (y > 5 && x > 6) {
        switch (y) {
        case 7:
            kind = 5;
            break;
        default:
            kind = 4;
            break;
        }
    } else {
        ch = getCharSheet((SHEET)*a->sheet, x, y);
        if (ch == 0) {
            ch = *GSmsgGetGSchar(0x3B1D);
        }
        kind = getSpchar(ch);
    }
    switch (kind) {
    case 1:
    case 2: {
        DAKUON_MODE mode;
        if (kind == 1) {
            mode = DAKUON_DAKU;
        } else {
            mode = DAKUON_HAN;
        }
        int pos = *a->nameCurX - 1;
        if (pos >= 0) {
            u16* name = a->name;
            int off = pos * 2;
            u16 r = exchangeDakuon(*(u16*)((u8*)name + off), mode);
            if (r != 0) {
                *(u16*)((u8*)name + off) = r;
            }
        }
        snd = 0x11;
        break;
    }
    case 4:
        if (backNameCursor(a)) {
            snd = 0x12;
        }
        break;
    case 5:
        ret = 1;
        break;
    case 3:
        change50Sheet(a);
        snd = 0x14;
        break;
    case 0:
        ch = *GSmsgGetGSchar(0x3B1D);
    default: {
        int pos;
        int max = ModeData[a->mode].maxLen;
        pos = *a->nameCurX;
        if (pos >= max) {
            pos = max - 1;
        }
        int np = pos + 1;
        u16* q = a->name + pos;
        q[0] = ch;
        q[1] = 0;
        if (np >= max + 1) {
            np = max;
        }
        snd = 0x11;
        *a->nameCurX = np;
        break;
    }
    }
    if (snd != 0) {
        GSsndPlayNow(snd);
    }
    return ret;
}

static void change50Sheet(NAME_ENTRY_ARG* a) {
    s32* p = a->sheet;
    s32 v = *p;
    v++;
    if (v >= 2) {
        v = 0;
    }
    *p = v;
}

static int getSpchar(unsigned short ch) {
    u16* p = GSmsgGetGSchar(0x3B1E);
    if (ch == *p) {
        return 0;
    }
    return 6;
}

static bool backNameCursor(NAME_ENTRY_ARG* a) {
    int pos = *a->nameCurX;
    if (pos <= 0) {
        return false;
    }
    pos--;
    a->name[pos] = 0;
    *a->nameCurX = pos;
    return true;
}

static int confirmName(unsigned short* name) {
    GSsndPlayNow(0x1D);
    msgctrlSetValue(0x4D, (u32)name);
    winMsgOpen(2, (void*)0x3B1A, 1, 0);
    s32 r = menuSubOpenYesNo(0, 0x2C, 0xC0, 0);
    winMsgClose(1);
    if (r == 1 || r == -1) {
        return 0;
    }
    return 1;
}

static u16 exchangeDakuon(unsigned short ch, DAKUON_MODE mode) {
    int k = 0;
    const u32* t = DakuHanTbl;
    int len;
    int i;
    u16* p;
    for (; k < 2; t++, k++) {
        if (*t == 0) {
            continue;
        }
        len = GSmsgGetLength(*t);
        p = GSmsgGetGSchar(*t) + 1;
        for (i = 1; i < len; i += 2, p += 2) {
            if (*p == ch) {
                break;
            }
        }
        if (i < len) {
            break;
        }
    }
    if (k >= 2) {
        k = 0;
    }
    if (k == mode) {
        return ch;
    }
    if (k == DAKUON_DAKU || k == DAKUON_HAN) {
        ch = p[-1];
    }
    if (mode == DAKUON_NONE) {
        return ch;
    }
    len = GSmsgGetLength(DakuHanTbl[mode]);
    p = GSmsgGetGSchar(DakuHanTbl[mode]);
    for (i = 0; i < len; i += 2, p += 2) {
        if (*p == ch) {
            break;
        }
    }
    if (i >= len) {
        return 0;
    }
    return p[1];
}

s32 menuNameEntryDrawTitle(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    NAME_ENTRY_ARG* a;
    u32 tw;
    if (w->menuID == 0x65) {
        DRAW_TITLE(0x3B11)
    } else {
        a = entryArg(w);
        switch (a->mode) {
        case 2: {
            Pokemon* p = (Pokemon*)heroGetStatus(0, 3, (u16)a->param);
            u16 id;
            if (pokemonCheckValid(p)) {
                id = pokemonBiosGetPokemonDataId(p);
            } else {
                id = 1;
            }
            msgctrlSetValue(0x4E, id);
            DRAW_TITLE(ModeData[a->mode].titleMsg)
            break;
        }
        case 5: {
            u16 id = pokemonBiosGetPokemonDataId((Pokemon*)a->param);
            msgctrlSetValue(0x4E, id);
            DRAW_TITLE(ModeData[a->mode].titleMsg)
            break;
        }
        case 4: {
            Pokemon* p = fightFloorGetDefPokemonPtr(0);
            u16 id;
            if (pokemonCheckValid(p)) {
                id = pokemonBiosGetPokemonDataId(p);
            } else {
                id = 1;
            }
            msgctrlSetValue(0x4E, id);
            DRAW_TITLE(ModeData[a->mode].titleMsg)
            break;
        }
        default:
            DRAW_TITLE(ModeData[a->mode].titleMsg)
            break;
        }
    }
    return 0;
}

s32 menuNameEntryDrawXButtonText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int sheet = *entryArg(w)->sheet + 1;
    if (sheet >= 2) {
        sheet -= 2;
    }
    if (sheet >= 0 && sheet < 2) {
        GSmsgPrint2(winSpriteGetLayerID(w, sp), 0, 0, w->alpha | ~0xFF, SheetData[sheet].xButtonMsg);
    }
    return 0;
}

s32 menuNameEntryDraw50Text(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int x;
    int y;
    int col;
    int row;
    SHEET sheet;
    u16 ch;
    sheet = (SHEET)*entryArg(w)->sheet;
    for (row = 0, y = 0; row < 8; y += 0x1E, row++) {
        for (col = 0, x = -2; (ch = getCharSheet(sheet, col, row)) != 0; x += 0x1A, col++) {
            putGScharL((GSgfxLayerID)winSpriteGetLayerID(w, sp), x, y, w->alpha | ~0xFF, ch);
        }
    }
    return 0;
}

static void putGScharL(GSgfxLayerID layer, int x, int y, unsigned long color, unsigned short ch) {
    u16 buf[2];
    buf[0] = ch;
    buf[1] = 0;
    msgctrlSetValue(0x37, (u32)buf);
    s16 w = GSmsgGetRect(0x4275) >> 16;
    GSmsgPrint2(layer, x + (0x1B - w) / 2, y, color, 0x4275);
}

static int getGScharLen(unsigned short* s) {
    int n = 0;
    for (; *s != 0; s++, n++) {
    }
    return n;
}

static u16 getCharSheet(SHEET sheet, int idx, int row) {
    if (sheet < 0 || sheet >= 2) {
        return 0;
    }
    if (row < 0 || row >= 8) {
        return 0;
    }
    u32 msg = SheetData[sheet].rows[row];
    if (msg == 0) {
        return 0;
    }
    s32 len = GSmsgGetLength(msg);
    if (idx < 0 || idx >= len) {
        return 0;
    }
    u16* s = GSmsgGetGSchar(msg);
    if (s[0] == 0xFFFF) {
        s += 2;
    }
    return s[idx];
}

s32 menuNameEntryDraw50Cursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    NAME_ENTRY_ARG* a = entryArg(w);
    winSpriteSetDisp(sp, 0);
    if (*a->curY < 6) {
        if (*a->curX < 11) {
            windowDrawSprite(*a->curX * 0x1A, *a->curY * 0x1E, w, 0x153, 0, winSpriteGetLayerID(w, sp));
        }
    } else if (*a->curX < 7) {
        windowDrawSprite(*a->curX * 0x1A, *a->curY * 0x1E, w, 0x153, 0, winSpriteGetLayerID(w, sp));
    }
    return 0;
}

s32 menuNameEntryDrawBCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    drawControlCursor(entryArg(w), sp);
    return 0;
}

s32 menuNameEntryDrawStartCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    drawControlCursor(entryArg(w), sp);
    return 0;
}

static void drawControlCursor(NAME_ENTRY_ARG* a, tagSPRITE_WORK* sp) {
    s32 x = *a->curX;
    s32 y = *a->curY;
    winSpriteSetDisp(sp, 0);
    if (y > 5 && x > 6) {
        int id;
        if (y == 6) {
            id = 0x305;
        } else {
            id = 0x304;
        }
        if (id == sp->id) {
            winSpriteSetDisp(sp, 1);
        }
    }
}

static s32 menuNameEntryDrawNameText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, int len, int kind) {
    NAME_ENTRY_ARG* a = entryArg(w);
    if (a->mode == 1) {
        if (kind == 0) {
            sp->alpha = 0xFF;
        } else {
            sp->alpha = 0;
        }
    } else if (a->mode != kind) {
        sp->alpha = 0;
    } else {
        sp->alpha = 0xFF;
    }
    if (sp->alpha != 0) {
        int i = 0;
        int x = 0;
        u16 c;
        u16* p = a->name;
        for (; (c = *p) != 0; x += 0x1A, i++, p++) {
            putGScharL((GSgfxLayerID)winSpriteGetLayerID(w, sp), x, 0, w->alpha | ~0xFF, c);
        }
        if (i < ModeData[a->mode].maxLen && w->done == 0) {
            u16 ch = getCharSheet((SHEET)*a->sheet, *a->curX, *a->curY);
            if (ch != 0 && getSpchar(ch) == 6) {
                f32 s = sin(2.0f * (3.14f * *a->animTime));
                putGScharL((GSgfxLayerID)winSpriteGetLayerID(w, sp), i * 0x1A, 0, (u8)(128.0f * (1.0f + s)) | ~0xFF, ch);
            }
        }
        sp->alpha = 0xFF;
    }
    return 0;
}

s32 menuNameEntryDrawNamePokemonText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    NAME_ENTRY_ARG* a = entryArg(w);
    s32 m = a->mode;
    if (m == 6) {
        return 0;
    } else if (m == 3) {
        return 0;
    } else if (m == 0) {
        return 0;
    }
    return menuNameEntryDrawNameText(w, sp, 10, m);
}

s32 menuNameEntryDrawNameBoxText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    return menuNameEntryDrawNameText(w, sp, 8, 3);
}

s32 menuNameEntryDrawNameTrainerText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    return menuNameEntryDrawNameText(w, sp, 7, 0);
}

s32 menuNameEntryDrawNameRuleText(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    return menuNameEntryDrawNameText(w, sp, 10, 6);
}

static s32 menuNameEntryDrawNameCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, int len, int kind) {
    NAME_ENTRY_ARG* a = entryArg(w);
    int max = ModeData[a->mode].maxLen;
    int cur = *a->nameCurX;
    int n = 0;
    int flag = 0;
    if (cur >= max) {
        cur = max - 1;
    }
    winSpriteSetDisp(sp, 0);
    switch (sp->id) {
    case 0x8ED:
        n++;
    case 0x8EC:
        n++;
    case 0x30B:
        n++;
    case 0x30A:
        n++;
    case 0x309:
        n++;
    case 0x308:
        n++;
    case 0x307: {
        s32 m = a->mode;
        if (m >= 7 || m < 2) {
            flag = 1;
        }
        break;
    }
    case 0x68D:
        n++;
    case 0x68C:
        n++;
    case 0x68B:
        n++;
    case 0x68A:
        n++;
    case 0x689:
        n++;
    case 0x688:
        n++;
    case 0x687:
        n++;
    case 0x686:
        n++;
    case 0x685:
        n++;
    case 0x684:
        switch (kind) {
        case 2:
        case 4:
        case 5:
        case 6:
            flag = 1;
            break;
        case 3:
            if (n != 0 && n != 9) {
                flag = 1;
                n--;
            }
            break;
        }
        break;
    }
    if (flag != 0) {
        if (n == cur) {
            f32 s = sin(2.0f * (3.14f * *a->animTime));
            sp->alpha = (u8)(128.0f * (1.0f + s));
            winSpriteSetDisp(sp, 1);
        } else if (n < cur) {
            sp->alpha = 0xFF;
            winSpriteSetDisp(sp, 1);
        }
    }
    return 0;
}

s32 menuNameEntryDrawNameTrainerCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    NAME_ENTRY_ARG* a = entryArg(w);
    s32 m = a->mode;
    if (m == 6) {
        return menuNameEntryDrawNameCursor(w, sp, 10, 6);
    } else if (m == 3) {
        return menuNameEntryDrawNameCursor(w, sp, 8, 3);
    } else if (m == 2) {
        return menuNameEntryDrawNameCursor(w, sp, 10, 2);
    } else if (m == 4) {
        return menuNameEntryDrawNameCursor(w, sp, 10, 4);
    } else if (m == 5) {
        return menuNameEntryDrawNameCursor(w, sp, 10, 5);
    } else {
        return menuNameEntryDrawNameCursor(w, sp, 7, 0);
    }
}

s32 menuNameEntryDrawNamePokemonWaku(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    NAME_ENTRY_ARG* a = entryArg(w);
    int n = 0;
    Pokemon* poke;
    int flag = 0;
    switch (sp->id) {
    case 0x675:
    case 0x676:
    case 0x677:
    case 0x678:
    case 0x679:
    case 0x8EA:
    case 0x8EB: {
        s32 m = a->mode;
        if (m >= 7 || m < 2) {
            flag = 1;
        }
        break;
    }
    case 0x683:
        n++;
    case 0x682:
        n++;
    case 0x681:
        n++;
    case 0x680:
        n++;
    case 0x67F:
        n++;
    case 0x67E:
        n++;
    case 0x67D:
        n++;
    case 0x67C:
        n++;
    case 0x67B:
        n++;
    case 0x67A: {
        switch (a->mode) {
        case 2:
        case 4:
        case 5:
        case 6:
            flag = 1;
            break;
        case 3:
            if (n != 0 && n != 9) {
                flag = 1;
            }
            break;
        }
        break;
    }
    case 0x876: {
        poke = 0;
        switch (a->mode) {
        case 2:
            poke = (Pokemon*)heroGetStatus(0, 3, (u16)a->param);
            break;
        case 4:
            poke = fightFloorGetDefPokemonPtr(0);
            break;
        case 5:
            poke = (Pokemon*)a->param;
            break;
        }
        if (poke != 0) {
            if (pokemonGetSex(poke) == 0) {
                flag = 0x9C5;
            } else if (pokemonGetSex(poke) == 1) {
                flag = 0x9C6;
            }
            if (flag != 0) {
                msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(flag));
                GSmsgPrint2(winSpriteGetLayerID(w, sp), 0, 0, colorAlpha(w), 0x4275);
                flag = 0;
            }
        }
        break;
    }
    }
    winSpriteSetDisp(sp, 0);
    if (flag != 0) {
        winSpriteSetDisp(sp, 1);
    }
    return 0;
}

static void drawTexture(GStexture* tex, tagSPRITE_WORK* sp, GSgfxLayerID id) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (layer != 0) {
        layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 1, 1, 4));
        if (layer->tex1740 != tex || layer->tex17F8 != tex || tex->flag != 0) {
            layer->tex1740 = tex;
            layer->f173C |= 1;
            layer->tex17F8 = tex;
            layer->f17F4 |= 1;
        }
        layer->primitive = 0x98;
        layer->beginSurface(4);
        f32 zero = 0.0f;
        f32 one = 1.0f;
        vertex(0, 0, zero, zero);
        vertex(sp->w, 0, one, zero);
        vertex(0, sp->h, zero, one);
        vertex(sp->w, sp->h, one, one);
        layer->endSurface();
    }
}

s32 menuNameEntryDrawBkCur(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    winSpriteSetDisp(sp, 0);
    s16 pos = w->cursor;
    if (pos >= 0) {
        menuSubDrawCursorBackAnimeOnOffAuto(w, winSpriteGetLayerID(w, sp), 0, pos << 5, sp->w, sp->h, w->alpha, 1);
    }
    return 0;
}
