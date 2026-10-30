#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>

#pragma peephole off
#pragma pool_strings off

struct Pokemon {
    u8 data[0xC4];
};

struct GSgfxVF;
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
void GSprimSetup2DRender(GSgfxLayer*);
extern "C" {
GSgfxLayer* GSgfxLayerFindByID(s32);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
}
static inline void vertexA(s16 x, s16 y, f32 u, f32 v, u8 a) {
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = a;
    GXWGFifo.f32 = u;
    GXWGFifo.f32 = v;
}

struct CAntPos {
    s16 x;
    s16 y;
};

struct CAnt {
    u32 active;
    u8 pad4[4];
    s16 x;
    s16 y;
    u8 pad0C[4];
    u8 alpha;
    u8 pad11[0x23];
    void initByPokemonAndSetColorAnimationInAny(Pokemon*);
    void setAnimation(long);
    void drawAndUpdate();
    void use();
    static void systemUsecountReset();
    static void systemUnUseResourceRelease();
    void setPos(CAntPos pos) {
        x = pos.x;
        y = pos.y;
    }
};

struct ErrEntry {
    u8 a7 : 1, a6 : 1, a5 : 1, a4 : 1, a3 : 1, a2 : 1, a1 : 1, a0 : 1;
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
    u8 pad[2];
};

struct CBWork {
    u8 pad0[0x8];
    s32 unk8;
    u8 padC[0x992A];
    u8 ruleStr[0x90];
    u8 pad99C6[0x2B2];
    u8* rule;
    u8 pad9C7C[0x8];
    ErrEntry err[4][6];
    u8 pad9CE4[0x978];
    u8 hero[1];
    u8 padA65D[0x983];
    s32 unkAFE0;
    s32 unkAFE4;
    u8 padAFE8[0x2C];
    s32 unkB014;
    u8 padB018[0x10];
    s32 scroll;
    u8 padB02C[0xA8];
    u32 tempBuff;
    s32 errPlayer;
    u8 padB0DC[0x8];
    s32 unkB0E4;
    s32 unkB0E8;
    s32 unkB0EC;
    s32 unkB0F0;
    u8 padB0F4[0x4];
    s32 unkB0F8;
    s32 unkB0FC;
    s32 unkB100;
    u8 padB104[0x14];
    s32 unkB118;
    u32 unkB11C;
    u8 padB120[0x4];
    s32 unkB124;
    s32 unkB128;
    s32 unkB12C;
    u8 padB130[0x8];
    s32 unkB138;
    u8 padB13C[0x8];
    s32 unkB144;
    s32 unkB148;
    s32 unkB14C;
    u8 padB150[0x84];
    s32 unkB1D4;
    s32 unkB1D8;
    s32 unkB1DC;
    s32 unkB1E0;
    u8 padB1E4[0x2BC];
    u8 unkB4A0;
    u8 padB4A1[0x83];
    Pokemon* relive[8][4];
};
struct CBMsgWin {
    u8 pad0[6];
    s16 id;
    u8 pad8[0x44];
    s32 unk4C;
};

struct tagWINDOW_WORK {
    u8 pad0;
    s8 kind;
    s8 state;
    u8 pad3;
    s32 menuId;
    u8 pad8[0x14];
    s32 layer;
    u8 pad20[0x6C];
    s16 x8C;
    u8 pad8E[5];
    u8 alpha;
    u8 pad94[0x10];
    u8 unkA4;
};
typedef tagWINDOW_WORK CBWin;

struct CBSprite {
    u8 pad0[6];
    s16 itemId;
};

struct CBMenuItem {
    u8 pad0[6];
    s16 x, y, w, h;
};

struct CBItem {
    u8 pad0[0x50];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    u8 pad58[0xC];
    u8 cr, cg, cb;
    u8 alpha;
    f32 scaleX;
    f32 scaleY;
};

struct MenuSpriteVal {
    s16 unk0;
    s16 unk2;
    s16 x;
    s16 y;
};

void menuPtSpriteDrawColor(u16, long, long, long, long, u32);
void menuPtSpriteDrawColor(u16, long, long, u32);

extern "C" {
extern CBWork _CB;
struct BSEnt {
    u32 pad;
    GStexture* tex;
};
struct BattleStartWork {
    u8 pad0[8];
    BSEnt ent[4];
    u8 pad28[4];
    s32 a, b;
};
extern BattleStartWork _menuCBBattleStartWork;
void msgctrlSetValue(s32, void*);
u32 GSmsgGetRect(s32);
void GSmsgPrint2(s32, s32, s32, u32, s32);
void GSsndPlay(s32, s32, s32);
void GSsndStop(s32, s32, s32);
u8 menuSubAnimAlpha(void);
f32 timeGetLastFrameSec(void);
double fmod(double, double);
void* menuSpriteBiosGetPtr(s32);
void menuCB_MenuDispCheckONorOFF(CBWin*, bool);
void menuCB_SpriteDispCheckONorOFF(CBSprite*, bool);
u8 menuCBPokemonCheck(u32, u32);
void* pokemonBiosGetNicknamePtr(Pokemon*);
u16 pokemonGetSoubiItemDataId(Pokemon*);
s32 heroItemCheckAddItemDataId(void*, u16);
void heroItemAddItemDataId(void*, u16, s32, s32);
s32 heroItemDecItemDataId(void*, u16, s32, u8);
u16 pokemonDoItemSoubi(Pokemon*, u16, s32);
struct CBRule {
    u8 pad[8];
    s32 unk8;
};
CBRule* menuCBBios_CurrentRule(void);
u16 menuPocket2Call(s32, s32, void*);
u8 menuPocket2GetLastSlotID(void);
void menuCBRule_ErrorFlagSetItemGetTiming(void*, Pokemon*, u32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
s32 menuSubOpenSelect2(s32, s32*, s32, s32, s32, s32, s32, s32);
void menuPokemonStatusOpenFromPokemonChange(Pokemon*, s32, s32);
u8 menuCBPokemonEntryGetReadFlag(void);
void menuCB_SetSprite(CBWin*, void*);
u16 toolentryTaisenGetBattlePlayerID(s32);
s32 toolentryTaisenGetHomePlace(s32);
u16 toolentryTaisenGetEntryPokemonNum(s32);
Pokemon* toolentryTaisenGetEntryPokemonPtr(s32, s32);
s32 menuCBBattleStartGetStatus(void);
u16 toolentryTaisenGetHomePlaceX(s32);
void menuCBPokemonEntryDispPokemonFace(s32, s32, s32, s32);
u8 menuCBPokemonEntryDisp(CBSprite*);
u8 menuCBPokemonGetDataId(s32, s32);
u16* heroBiosGetNamePtr(void*);
void* pokemonDataBiosGetPtr(u16);
s32 zokuseiGetPokemonSpriteID(void*, s32);
void windowDrawSprite(s32, s32, CBWin*, u16, s32, s32);
u8 GSinputIsConnected(s32);
u8 gbaCommandIsConnected(s32);
void menuSetDisp(s32, s32);
void winSpriteSetDisp(void*, s32);
u8 fightReadResourceID(s32, s32);
void fightFreeResourceID(s32, s32);
s32 winSpriteGetLayerID(CBWin*, CBSprite*);
CBMenuItem* menuItemBiosGetPtr(s32, s32);
void spriteSetScissor(s32, s32, s32, s32, s32);
void spriteClearScissor(s32);
u16 menuCBRule_RegulationItemID(s32);
u8 itemDataCheckValid(u16);
void* itemDataBiosGetPtr(u16);
s32 itemDataBiosGetName(void*);
u16* GSmsgGetGSchar(s32);
MenuSpriteVal* menuSpriteBiosGetValPtr(void*);
void pokemonAllKaihuku(Pokemon*);
void menuCB_SE_Play(s32);
s32 fn_8007E634(s32);
void* savedataGetStatus(s32, s32);
Pokemon* heroBiosGetPokemonPtr(void*, u16);
Pokemon* toolentryTaisenGetPokemonPtr(u32, u32);
void* memcpy(void*, const void*, u32);
void pokemonInit(Pokemon*);
void menuCBGCEntryTypeIndex(void);
void toolBattleRuleErrorFlagClear(s32, u32);
void menuCBRule_ErrorFlagSetPokemonGetTiming(void*, Pokemon*, u32);
u8 menuCB_Trainer_Error_Check(u32, s32);
u32 pokemonGetStatus(Pokemon*, u16, u16, u16);
u16 pokemonGetStatusU16(Pokemon*, s32, s32, s32);
void menuCBGCDelPokemon(void);
void menuCBMessageCenterDisp(CBWin*, CBItem*, s32);
s32 pokecoloGetCountryCode(void);
u8 pokemonCheckValid(Pokemon*);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
void GSthreadSwitch(void);
void* windowGetKeyInfo(void);
void GSfsysReadWait(s32);
void GSfsysFree(s32);
void GSresFreeGroup(s32);
void menuTopOpenFlashBack(void);
void menuCB_FlashStart(s32);
void menuCB_FlashEnd(s32);
void fadeSet(s32, f32);
void menuOpen(s32, s32);
void menuCloseCustom(s32, s32, s32);
void menuOpenCustom(s32, ...);
s32 windowGetActiveID(void);
s32 menuCB_GetDisconnectedGBA(void);
void heroBiosCopy(void*, void*);
void menuCBPokemonEntryPokemonFaceFree(void);
void menuCBBattleStartSetStatus(s32);
void menuCBPokemonEntryLoadTex(void);
void menuCBpokemonFaceReadWait(void);
u8 menuCBPokemonGetDataId_NULL(s32, s32);
void winSeqSetMenu(s32, u32);
void menuCBRule_ErrorFlagSet(void*, s32);
void menuCBRule_ErrorFlagSetOkPushTiming(void*);
u16 menuCBBios_ParticipationPokemonMax(void);
u16 toolentryTaisenGetPokemonNum(s32);
u16 toolentryTaisengetEtnryPokemonOrderNum(s32);
u8 menuCB_BattleStartSoundCheck(void);
u8 FlashSystemIsLastFrame(u32);
void* menuCBBios_GetTrainerOrgImmediately(void);
s32 menuCBTrainerBios_GetHomePlace(void*);
u8 heroBiosGetSexDataId(void*);
void spriteSetOffset(s32, s32, s32);
void spriteSetEnv(s32);
u8 pokemonBiosGetTamagoFlag(Pokemon*);
u8 menuSubGetPokemonSexForDisp(Pokemon*);
u8 menuSubGetPokemonSexForFightDisp(Pokemon*);
void GSmsgPrintRight(s32, s32, s32, s32, s32, u32, s32);
u16 pokemonGetTokuseiDataId(Pokemon*);
u32 pokemonTokuseiDataBiosGetPtr(u16);
u32 pokemonTokuseiDataBiosGetName(u32);
u16 heroBiosGetRnd(void*);
void GScharMakeFromSJIS(u16*, char*);
int sprintf(char*, const char*, ...);
u32 wazaGetStatus(void*, u16, u16, u32);
u16 zokuseiBiosGetSmallSpriteID(u16);
u16 pokemonBiosGetHp(Pokemon*);
u16 pokemonBiosGetMaxHp(Pokemon*);
u8 pokemonDataBiosGetZokuseiDataId(void*, u16);
u16 pokemon_GetPokemonDataId(Pokemon*);
u32 pokemonDB_GetName(u16);
void* memset(void*, int, u32);
bool pauseIsPause(void);
}
struct CBHP {
    u8 pad[0xB1E4];
    s16 wait;
    u8 pad2[2];
    f32 f0[4][6];
    f32 f1[4][6];
    f32 f2[4][6];
    f32 f3[4][6];
    f32 f4[4][6];
    f32 f5[4][6];
};
struct CBBall {
    u8 pad[0xB426];
    s16 x[4][6];
    s16 y[4][6];
    u8 pad2;
    s8 on[4][6];
};
#define CBH (*(CBHP*)&_CB)
struct CBRuleData {
    s16 v[3];
    u8 pad6[0xE];
    s16 c14;
    s16 c16;
    s16 pad18;
    s16 c1a;
    s16 c1c;
};
#define RULE ((CBRuleData*)_CB.rule)
static inline void ruleDispTitle(CBWin* win, CBItem* item) {
    s16 w = GSmsgGetRect(0x4416) >> 16;
    GSmsgPrint2(win->layer, (s16)(item->w / 2 - w / 2), 0, win->alpha | ~0xFF, 0x4416);
}
#define CBB (*(CBBall*)&_CB)
#define CB32(o) (*(s32*)((u8*)&_CB + (o)))
#define CBF32(o) (*(f32*)((u8*)&_CB + (o)))
#define CB16(o) (*(s16*)((u8*)&_CB + (o)))
#define CB8(o) (*(s8*)((u8*)&_CB + (o)))

class CReliveStage {
public:
    Pokemon* getDancerPointer(long);
    Pokemon* getVisitorPointer();
    void insertDancer(Pokemon&, long);
    void pickupDancer(Pokemon&, long);
};

class CReliveHall {
public:
    static CReliveHall* getPointer();
    CReliveStage* getStage(long);
};

struct PCBOX {
    static PCBOX* getPointer();
    Pokemon* getPokemon(s8, s8);
    u16* getPokemonBoxName(s8);
};

static CAnt ant[0x24];
static CAnt antR[0x1E];
static CAnt antL[0x1E];

static Pokemon* menuCBPokemonPtrGet(u32, u32);
static void _menuCB_errorMsgDisp2(u32);
static void _menuCB_errorMsgDisp(u32);
static void _menuCB_PokemonStatusDispBeforeJob(u32);
static void _menuCB_PokemonStatusDispAfterJob(u32);
static u32 err_msgID[14];
static u32 err_msgID2[14];
static u16 battleEndHPStartFlag;
static u16 battleEndHPEndFlag;
static f32 _f_menuCB_circleAnimationTime;
static u32 backup_type[6];
static u32 backup_index[6];

static s32 submenurule_msg1[3] = {0x4391, 0x4392, 0x4395};
static s32 submenurule_msg2[4] = {0x4391, 0x4393, 0x4394, 0x4395};
static s32 submenu_msg1[3] = {0x4398, 0x4399, 0x439A};
static s32 submenu_msg2[4] = {0x439B, 0x4399, 0x439C, 0x439A};
static s32 submenu_msg3[3] = {0x439D, 0x439E, 0x439A};
static s16 submenu1_x[30] = {0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
                             0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28};
static s16 submenu1_y[30] = {0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136,
                             0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x64,  0x64,
                             0x64,  0x64,  0x64,  0x64,  0x64,  0x64,  0x64,  0x64,  0x64,  0x64};
static u8 _ruleCursolDispColorATbl[64] = {
    0xFF, 0xFB, 0xF7, 0xF3, 0xEF, 0xEA, 0xE6, 0xE2, 0xDE, 0xD9, 0xD5, 0xD1, 0xCD, 0xC8, 0xC4, 0xC0,
    0xBC, 0xB8, 0xB3, 0xAF, 0xAB, 0xA7, 0xA2, 0x9E, 0x9A, 0x96, 0x91, 0x8D, 0x89, 0x85, 0x80, 0x80,
    0x85, 0x89, 0x8D, 0x91, 0x96, 0x9A, 0x9E, 0xA2, 0xA7, 0xAB, 0xAF, 0xB3, 0xB8, 0xBC, 0xC0, 0xC4,
    0xC8, 0xCD, 0xD1, 0xD5, 0xD9, 0xDE, 0xE2, 0xE6, 0xEA, 0xEF, 0xF3, 0xF7, 0xFB, 0xFF, 0xFF, 0xFF,
};
static s32 submenu_msg1s[2] = {0x4399, 0x439A};
static const s32 BATTLE_BA_FACEWAKU_Char[2] = {0x233, 0x234};
static const s32 BATTLE_BA_XP_PRINT_Char[4] = {0x20F, 0x20E, 0x20D, 0x20C};
static const s32 BATTLE_BA_HP_Bar_Char[3] = {0x2B8, 0x2B9, 0x2BA};
static void _drawStrings(CBWin*, u16*, long, long, u32);
static void _menuCBPokemonName(tagWINDOW_WORK*, u32, u32, u32, bool);
struct CBKeyInfo {
    u8 pad[4];
    u16 buttons;
};

extern "C" {
void fn_8007E5AC(CBWin* a, CBMsgWin* w);
s32 fn_8007E634(s32 msg);
void fn_8007F43C(CBWin* win, CBItem* item, void* str, s32 unused, s32 y, s32 msg);
void menuCB_SE_Stop(s32 id);
void menuCB_SE_Play(s32 id);
void menuCB_Cursol_Disp_AlphaSet(CBWin* win, CBItem* item, u8 flag);
void menuCB_AlphaGet(CBWin* win);
void menuCB_GCEntryCursolDisp(CBWin* win, void* unused, u8 flag);
void menuCB_GCPokemonHPandWAZA_MAX();
void menuCB_RuleMessageTblDisp(CBWin* win, CBItem* item, s32 idx);
void menuCB_RuleDispColorChenge_flag(CBWin* win, CBItem* item, u8 flag);
void menuCB_RuleDispColorChenge(CBWin* win, CBItem* item, u32 n);
void menuCB_RuleItemFlagDisp(CBWin* win, CBSprite* sprite);
void menuCB_RuleItemNameEntry(CBWin* win, CBSprite* sprite);
void menuCBRuleNumberDisp(CBWin* win, CBItem* item, s32 digit);
void menuCBMessageYCenterDisp(CBWin* win, CBItem* item, s32 msg);
void fn_80080390(CBWin* win, CBItem* item, s32 msg);
void menuCBMessageCenterDisp(CBWin* win, CBItem* item, s32 msg);
void menuCB_RuleNameChengeAfterJob(u8 first);
void menuCB_RuleNameChengeBeforeJob(u8 first);
void menuCB_MenuDispCheckONorOFF_RULE(CBWin* win, s32 idx);
void menuCB_MenuDispCheckONorOFF_TUNAIDESUB(CBWin* win, s32 idx);
void menuCB_MenuDispCheckONorOFF(CBWin* win, bool on);
void menuCB_SpriteDispCheckONorOFF(CBSprite* sprite, bool on);
void menuCB_GCEntry_ItemKeepJob();
void menuCB_GCEntry_ItemGiveJob();
void menuCBRULE_EditNameDispLarge(CBWin* win, s32 idx);
void menuCBRULE_EditNameDisp(CBWin* win, CBItem* item, s32 idx);
void menuCB_GCEntry_PokemonStatusDisp();
s32 menuCB_GCEntry_SubWindow_Disp(void);
void menuCB_TUNAIDE01_Rule_SELECT(void);
void menuCB_GCEntry_OkPushErrorCheck(void);
void menuCB_WaitGCControler1();
void menuCB_GBADisconnectedErrorJob(void);
void menuCBPokemonEntryGCControlDisp(CBSprite* sprite, s32 b);
void menuCBPokemonEntryBallAnaDisp(CBItem* item, s32 player, u32 idx);
void menuCBPokemonEntryBallDisp(CBItem* item, s32 player, u32 idx);
u8 menuCBPokemonEntryDispPokemonFace_AFTER(s32 a, s32 b, s32 c, s32 d);
u8 menuCBPokemonEntryDispPokemonFace_BEFORE(s32 a, s32 b, s32 c, s32 d);
void menuCB_BattleEntryPokemonSelectDisp(CBSprite* sprite, u32 a, u32 b);
u8 menuCB_GCStatusDispMode(CBSprite* sprite, s32 mode);
u8 menuCBPokemonEntryDisp(CBSprite* sprite);
void menuCBGCEntryTypeIndex(void);
void menuCBGCDelPokemon(void);
void menuCBGCEntryPokemon(void);
void menuCBReliveHallCursolInit(void);
void menuCBPCBOXTitleNameDisp(CBWin* win, CBItem* item, s8 box, s32 x);
void menuCBReliveTitleNameDisp(CBWin* win, CBItem* item, s32 id, s32 x);
void menuCBGCEntryTitleDisp(CBWin* win, CBItem* item, s32 msg, s32 x);
u8 menuCBPokemonCheck(u32 a, u32 b);
void menuCBPokemonItemName(CBWin* win, u32 type, u32 index, s32 mode);
void menuCBPokemonWazaNAME(CBWin* win, u32 type, u32 index, u32 slot);
void menuCBPokemonWazaTYPE(CBWin* win, u32 type, u32 index, u32 slot);
void menuCBPokemonTYPE2(CBWin* win, u32 type, u32 index);
void menuCBPokemonTYPE1(CBWin* win, u32 a, u32 b);
void menuCBPokemonStatusDisp(CBWin* win, u32 type, u32 index, s32 mode, s32 kind);
void menuCBPokemonTOKUSEI(CBWin* win, u32 type, u32 index);
void menuCBPokemonHP(CBWin* win, u32 type, u32 index, s32 mode);
void menuCBPokemonLevel(CBWin* win, u32 type, u32 index, s32 mode);
void menuCBPokemonNameOrg(CBWin* win, u32 type, u32 index, s32 mode);
void menuCBPokemonSexOnly(CBWin* win, u32 type, u32 index, s32 mode);
void menuCBPokemonNameOnly(CBWin* win, u32 type, u32 index, s32 mode);
void menuCBPokemonName(CBWin* win, u32 a, u32 b, u32 c);
void menuCBPokemonName_nido(CBWin* win, u32 a, u32 b, u32 c);
void menuCB2DPokemonItemDisp(CBSprite* sprite, u32 a, u32 b);
void menuCB2DPokemonClearSHIFT(u32 dir);
void menuCB2DPokemonALLClear(void);
void menuCB2DPokemonDisp2(CBWin* win, CBItem* item, u32 type, u32 index);
void menuCB2DPokemonDisp(CBWin* win, CBItem* item, u32 type, u32 index);
s32 menuCBBattleBANextMenu(CBWin* win);
void menuCBBattleBABatuMark(CBItem* sprite, s32 p, s32 i);
void menuCBBattleEndSetPokemonHP(void);
void menuCB_BattleBA_HPBarDispSet(CBItem* sprite, s32 p, s32 i);
void menuCB_BattleBA_FacePanelSet(void* sprite, s32 a, s32 b);
void menuCB_DispEffect(CBWin* win);
s32 menuCB_BattleBA_PokemonEntryNum(void);
void menuCB_PrintXP(CBWin* win, s32 player);
void menuCBBattleStartDispTrainerFaceSub(CBWin* win, CBItem* item, s32 idx);
void menuCBPokemonMaruWaku_ErrorSet(CBItem* item, s32 idx);
void menuCBPokemonItem_ErrorSet(CBItem* item, s32 idx);
u8 menuCBPokemon_ErrorDispSet(void* sprite, s32 idx);
bool toolBattle_tunaideMenu02menuTempBuffGet(u32 mask);
void toolBattle_tunaideMenu02menuTempBuffSet(u32 mask);
void menuCB_Trainer_Error_Disp(CBWin* win, CBItem* item, s32 idx, s32 mode);
void toolBattleRuleErrorFlagClear(s32 player, u32 idx);
u8 menuCB_Trainer_Error_Check(u32 player, s32 idx);
void menuCB_Pokemon_ErrorDisp(void* src, s8 player);
void menuCBtrainerFaceReadWait();
void menuCBpokemonFaceReadWait();
void toobattle_drawHeroName2(CBWin* win, CBItem* item, s32 player);
void toobattle_drawHeroNames(CBWin* win, s32 player);
void toobattle_drawHeroName(CBWin* win, s32 player);
void toolbattle_drawHeroID(CBWin* win, s32 player);
s32 toolbattle_trainerFace(void);
u8 menuCBPokemonGetDataId_NULL(s32 a, s32 b);
u8 menuCBPokemonGetDataId(s32 a, s32 b);
u8 menuCBPokemonGetItemDataId(u32 a, u32 b);
}

extern "C" {
void fn_8007E5AC(CBWin* a, CBMsgWin* w) {
    switch (w->id) {
    case 0x2B7:
        menuCBMessageCenterDisp(a, (CBItem*)w, 0xD11E);
        break;
    case 0x2B8:
        menuCBMessageCenterDisp(a, (CBItem*)w, 0xD11F);
        break;
    case 0x4D1:
        w->unk4C = 0xD160;
        break;
    case 0x433:
        menuCBMessageCenterDisp(a, (CBItem*)w, 0x3BD6);
        break;
    }
}

s32 fn_8007E634(s32 msg) {
    switch (pokecoloGetCountryCode()) {
    case 0:
        return msg;
    case 1:
    case 2:
        switch (msg) {
        case 0x4278:
            return 0x4279;
        case 0x4276:
            return 0x4277;
        case 0x427C:
            return 0x4352;
        case 0x427B:
            return 0x4351;
        }
    }
    return 0x56C;
}
}

static s32 _menuCB_NotDarkWaza(s32 id) {
    if (id < 0x176 && id >= 0x164) {
        return 0;
    }
    return id;
}

static void _menuCB_ErrorTAMAGOCheck() {
    int i;
    for (i = 0; i < 6; i++) {
        if (_CB.err[_CB.errPlayer][i].a2) {
            _CB.err[_CB.errPlayer][i].a5 = 0;
            _CB.err[_CB.errPlayer][i].a4 = 0;
            _CB.err[_CB.errPlayer][i].b3 = 0;
        }
        if (_CB.err[_CB.errPlayer][i].b1) {
            _CB.err[_CB.errPlayer][i].a5 = 0;
            _CB.err[_CB.errPlayer][i].a4 = 0;
            _CB.err[_CB.errPlayer][i].b3 = 0;
            _CB.err[_CB.errPlayer][i].a2 = 1;
        }
        if (_CB.err[_CB.errPlayer][i].b4 && _CB.err[_CB.errPlayer][i].b6) {
            _CB.err[_CB.errPlayer][i].b6 = 0;
        }
    }
}

static void _menuCB2DPokemonNewSet2(u32 type, u32 base, u32 count, u8 kind) {
    Pokemon* p;
    u32 i;
    for (i = 0; i < count; i++) {
        p = menuCBPokemonPtrGet(type, base | i);
        if (p && pokemonCheckValid(p)) {
            switch (kind) {
            case 0:
                antR[i].initByPokemonAndSetColorAnimationInAny(p);
                antR[i].setAnimation(0);
                break;
            case 1:
                antL[i].initByPokemonAndSetColorAnimationInAny(p);
                antL[i].setAnimation(0);
                break;
            case 2:
                ant[i].initByPokemonAndSetColorAnimationInAny(p);
                ant[i].setAnimation(0);
                break;
            }
        }
    }
}

static void _menuCB2DPokemonNewSet(u8 kind) {
    if (kind == 2) {
        _menuCB2DPokemonNewSet2(4, 0, 6, kind);
        return;
    }
    switch (_CB.unkB0F0) {
    case 0:
        switch (kind) {
        case 0:
            _menuCB2DPokemonNewSet2(5, 0, 0x1E, kind);
            break;
        case 1:
            if (_CB.unkB4A0 == 1) {
                _menuCB2DPokemonNewSet2(6, 0x80000, 5, kind);
            } else {
                _menuCB2DPokemonNewSet2(5, 0x70000, 0x1E, kind);
            }
            break;
        }
        break;
    case 1:
        switch (kind) {
        case 0:
            if (_CB.unkB0E8 == 7) {
                if (_CB.unkB4A0 == 1) {
                    _menuCB2DPokemonNewSet2(6, 0, 5, kind);
                } else {
                    _menuCB2DPokemonNewSet2(4, 0, 6, kind);
                }
            } else {
                _menuCB2DPokemonNewSet2(5, (_CB.unkB0E8 + 1) << 16, 0x1E, kind);
            }
            break;
        case 1:
            if (_CB.unkB0E8 == 0) {
                _menuCB2DPokemonNewSet2(4, 0, 6, kind);
            } else {
                _menuCB2DPokemonNewSet2(5, (_CB.unkB0E8 - 1) << 16, 0x1E, kind);
            }
            break;
        }
        break;
    case 2:
        switch (kind) {
        case 0:
            if (_CB.unkB0EC == 8) {
                _menuCB2DPokemonNewSet2(4, 0, 6, kind);
            } else {
                _menuCB2DPokemonNewSet2(6, (_CB.unkB0EC + 1) << 16, 5, kind);
            }
            break;
        case 1:
            if (_CB.unkB0EC == 0) {
                _menuCB2DPokemonNewSet2(5, 0x70000, 0x1E, kind);
            } else {
                _menuCB2DPokemonNewSet2(6, (_CB.unkB0EC - 1) << 16, 5, kind);
            }
            break;
        }
        break;
    }
}

static void _menuCB_errorMsgDisp2(u32 msg) {
    winMsgOpen(2, msg, 1, 0);
    winMsgClose(1);
}

static void _menuCB_errorMsgDisp(u32 msg) {
    winMsgOpen(2, msg, 1, 1);
    do {
        GSthreadSwitch();
    } while ((((CBKeyInfo*)windowGetKeyInfo())->buttons & 0x30) == 0);
    winMsgClose(1);
}

static void _menuCB_PokemonStatusDispAfterJob(u32 first) {
    if (first == 0) {
        GSfsysReadWait(0x88C);
        menuTopOpenFlashBack();
        menuCB_FlashStart(0);
        fadeSet(2, 0.5f);
    }
    menuCB_SE_Play(0x14);
    menuOpen(0xBB, 0);
    menuOpen(0xBD, 0);
    menuOpen(0xBE, 0);
    menuOpen(0xBF, 0);
    menuOpen(0x10D, 0);
    menuOpen(0x10F, 0);
    menuOpen(0x10E, 0);
    menuOpen(0xC2, 0);
}

static void _menuCB_PokemonStatusDispBeforeJob(u32 first) {
    if (first == 0) {
        menuCB_FlashEnd(1);
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xBC, 0, 0);
    menuCloseCustom(0xC2, 0, 0);
    menuCloseCustom(0x10E, 0, 0);
    menuCloseCustom(0x10F, 0, 0);
    menuCloseCustom(0x10D, 0, 0);
    menuCloseCustom(0xBF, 0, 0);
    menuCloseCustom(0xBE, 0, 0);
    menuCloseCustom(0xBD, 0, 0);
    menuCloseCustom(0xBB, 0, 1);
    if (first == 0) {
        GSfsysFree(0x88C);
        GSresFreeGroup(0x88C);
    }
}

static void _menuCBGCDelPokemon() {
    u32 i;
    u32 index;
    Pokemon* cur;
    u32 type;
    Pokemon* dst;
    switch (_CB.unkB0F8) {
    case 30:
        i = 0;
        break;
    case 31:
        i = 1;
        break;
    case 32:
        i = 2;
        break;
    case 33:
        i = 3;
        break;
    case 34:
        i = 4;
        break;
    case 35:
        i = 5;
        break;
    }
    type = backup_type[i];
    index = backup_index[i];
    backup_type[i] = 0;
    backup_index[i] = 0;
    menuCBGCEntryTypeIndex();
    cur = menuCBPokemonPtrGet(_CB.unkB1D4, _CB.unkB1D8);
    switch (pokecoloGetCountryCode()) {
    case 0:
        if (type != 6) {
            memcpy(menuCBPokemonPtrGet(type, index), cur, 0xC4);
            pokemonInit(cur);
        } else {
            CReliveHall::getPointer()->getStage(index >> 16)->insertDancer(*cur, 0);
        }
        break;
    case 1:
    case 2:
        memcpy(menuCBPokemonPtrGet(type, index), cur, 0xC4);
        pokemonInit(cur);
        break;
    }
    for (; i < 5; i++) {
        dst = menuCBPokemonPtrGet(7, i);
        backup_type[i] = backup_type[i + 1];
        backup_index[i] = backup_index[i + 1];
        backup_type[i + 1] = 0;
        backup_index[i + 1] = 0;
        cur = menuCBPokemonPtrGet(7, i + 1);
        memcpy(dst, cur, 0xC4);
        pokemonInit(cur);
    }
    _CB.unkB100--;
}

static u8 menuCBGCEntry_ErrorDisp(u32 type, u32 index) {
    u32 idx = _CB.unkB100 - 1;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    toolBattleRuleErrorFlagClear(0, idx);
    menuCBRule_ErrorFlagSetPokemonGetTiming(_CB.hero, p, idx);
    _CB.errPlayer = 0;
    if (menuCB_Trainer_Error_Check(idx, -1)) {
        menuCBGCDelPokemon();
        _CB.unkB0FC = 2;
        if (_CB.err[_CB.errPlayer][idx].a7) {
            _CB.unkB1DC = 0x43AF;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a6) {
            _CB.unkB1DC = 0x43A2;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a5 || _CB.err[_CB.errPlayer][idx].a4) {
            _CB.unkB1DC = 0x43B0;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a3) {
            _CB.unkB1DC = 0x43A5;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a2) {
            _CB.unkB1DC = 0x43A6;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a1) {
            _CB.unkB1DC = 0x43A7;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].a0 || _CB.err[_CB.errPlayer][idx].b1) {
            _CB.unkB1DC = 0x43A8;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b7) {
            _CB.unkB1DC = 0x43A9;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b6) {
            _CB.unkB1DC = 0x43AA;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b5) {
            _CB.unkB1DC = 0x43AB;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b4) {
            _CB.unkB1DC = 0x43AC;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b3) {
            _CB.unkB1DC = 0x43AD;
            return 0;
        }
        if (_CB.err[_CB.errPlayer][idx].b2) {
            _CB.unkB1DC = 0x43AE;
            return 0;
        }
        return 0;
    }
    return 1;
}

static u8 _menuCBPokemonEntryGetlevel(Pokemon* p) {
    return pokemonGetStatus(p, 0, 0x7A, 0);
}

static u32 menuCBPokemonGetIndex(u32 type, u32 index) {
    switch (type) {
    case 4:
        break;
    case 5:
        index = (u16)index;
        break;
    case 6:
        index = (u16)index;
        break;
    case 7:
        index += 0x1E;
        break;
    }
    return index;
}

static Pokemon* menuCBPokemonPtrGet(u32 type, u32 index) {
    u16 lo;
    u32 hi;
    Pokemon* p;
    if ((u16)index >= 0x24) {
        return 0;
    }
    if ((u16)index >= 0x1E && (u16)index <= 0x23) {
        type = 7;
        index = (u16)index - 0x1E;
    }
    switch (type) {
    case 4:
        p = heroBiosGetPokemonPtr(savedataGetStatus(0, 2), (u16)index);
        break;
    case 5:
        p = PCBOX::getPointer()->getPokemon((s8)(index >> 16), (s8)(u16)index);
        break;
    case 6: {
        CReliveHall* hall = CReliveHall::getPointer();
        hi = index >> 16;
        CReliveStage* stage = hall->getStage(hi);
        lo = (u16)index;
        if (lo == 4) {
            p = stage->getVisitorPointer();
        } else {
            switch (pokecoloGetCountryCode()) {
            case 0:
                p = stage->getDancerPointer(lo);
                break;
            case 1:
            case 2:
                p = _CB.relive[hi][lo];
                break;
            }
        }
        break;
    }
    case 7:
        p = heroBiosGetPokemonPtr(_CB.hero, (u16)index);
        break;
    case 0:
    case 1:
    case 2:
    case 3:
        p = toolentryTaisenGetPokemonPtr(type, index);
        break;
    }
    return p;
}

extern "C" {
void fn_8007F43C(CBWin* win, CBItem* item, void* str, s32 unused, s32 y, s32 msg) {
    s16 w;
    s16 x;
    msgctrlSetValue(0x37, str);
    w = GSmsgGetRect(msg) >> 16;
    x = item->w / 2 - w / 2;
    GSmsgPrint2(win->layer, x, y, win->alpha | ~0xFF, msg);
}
}

static void _drawStrings(CBWin* win, u16* str, long x, long y, u32 msg) {
    msgctrlSetValue(0x37, str);
    GSmsgPrint2(win->layer, x, y, win->alpha | ~0xFF, msg);
}

extern "C" {
void menuCB_SE_Stop(s32 id) {
    GSsndStop(id, 0, 0);
}

void menuCB_SE_Play(s32 id) {
    GSsndPlay(id, 0, 0);
}

void menuCB_Cursol_Disp_AlphaSet(CBWin* win, CBItem* item, u8 flag) {
    if (flag) {
        if (win->alpha == 0xFF) {
            item->alpha = _CB.unkB138;
        } else {
            item->alpha = win->alpha;
        }
    } else {
        if (win->alpha >= 0x7F) {
            item->alpha = 0x7F;
        } else {
            item->alpha = win->alpha;
        }
    }
}

void menuCB_AlphaGet(CBWin* win) {
    if (win->alpha == 0xFF) {
        _CB.unkB138 = menuSubAnimAlpha();
    } else {
        _CB.unkB138 = win->alpha;
    }
}

void menuCB_GCEntryCursolDisp(CBWin* win, void* unused, u8 flag) {
    f32 t;
    f32 k;
    s16 a;
    s16 b;
    int y;
    int n;
    u32 color;
    int x;
    MenuSpriteVal* v;
    if (flag) {
        t = _f_menuCB_circleAnimationTime / 0.5f;
        if (t > 0.5f) {
            t = 1.0f - t;
        }
        k = 2.0f * t;
        _f_menuCB_circleAnimationTime = _f_menuCB_circleAnimationTime + timeGetLastFrameSec();
        if (_f_menuCB_circleAnimationTime >= 0.5f) {
            _f_menuCB_circleAnimationTime = fmod(_f_menuCB_circleAnimationTime, 0.5);
        }
        color = win->alpha | ~0xFF;
        v = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x216));
        x = v->x;
        y = v->y;
        n = (s16)(5.0f * k);
        if (n > 4) {
            n = 4;
        }
        a = n + 4;
        menuPtSpriteDrawColor(0x216, a, a, x, y, color);
        b = 0x32 - n;
        menuPtSpriteDrawColor(0x216, b, a, -x, y, color);
        menuPtSpriteDrawColor(0x216, a, b, x, -y, color);
        menuPtSpriteDrawColor(0x216, b, b, -x, -y, color);
        menuPtSpriteDrawColor(0x214, 7, 0x23, color);
    }
}

void menuCB_GCPokemonHPandWAZA_MAX() {
    u32 i;
    for (i = 0; i < 6; i++) {
        Pokemon* p = menuCBPokemonPtrGet(4, i);
        if (p) {
            pokemonAllKaihuku(p);
        }
    }
}

void menuCB_RuleMessageTblDisp(CBWin* win, CBItem* item, s32 idx) {
    u16 buf[0x1F];
    u16* s;
    s16 x;
    int i;
    if (idx >= 3) {
        msgctrlSetValue(0x37, &_CB.ruleStr[idx * 0x90]);
    } else {
        switch (idx) {
        case 0:
            s = GSmsgGetGSchar(0x4387);
            break;
        case 1:
            s = GSmsgGetGSchar(0x4389);
            break;
        case 2:
            s = GSmsgGetGSchar(0x4388);
            break;
        }
        for (i = 0; i < 0x1F; i++) {
            if (s) {
                if (*s == 0xFFFF) {
                    s += 2;
                }
                buf[i] = *s;
                if (*s) {
                    s++;
                }
            } else {
                buf[i] = 0;
            }
        }
        msgctrlSetValue(0x37, buf);
    }
    x = item->w / 2 - ((s16)(GSmsgGetRect(fn_8007E634(0x4276)) >> 16)) / 2;
    GSmsgPrint2(win->layer, x, 0, (*(u32*)&item->cr & ~0xFF) | win->alpha, fn_8007E634(0x4276));
}

void menuCB_RuleDispColorChenge_flag(CBWin* win, CBItem* item, u8 flag) {
    if (flag) {
        item->cb = 0xFF;
        item->cg = 0xFF;
        item->cr = 0xFF;
        item->alpha = _CB.unkB138;
    } else {
        item->cb = 0x7F;
        item->cg = 0x7F;
        item->cr = 0x7F;
        item->alpha = win->alpha;
    }
}

void menuCB_RuleDispColorChenge(CBWin* win, CBItem* item, u32 n) {
    if (n == _CB.unkB11C) {
        item->cb = 0xFF;
        item->cg = 0xFF;
        item->cr = 0xFF;
        item->alpha = _CB.unkB138;
    } else {
        item->cb = 0x7F;
        item->cg = 0x7F;
        item->cr = 0x7F;
        item->alpha = win->alpha;
    }
}

void menuCB_RuleItemFlagDisp(CBWin* win, CBSprite* sprite) {
    s32 layer;
    CBMenuItem* base;
    CBMenuItem* item;
    s16 y;
    s32 last;
    s32 first;
    layer = winSpriteGetLayerID(win, sprite);
    base = menuItemBiosGetPtr(win->menuId, 0x3AB);
    item = menuItemBiosGetPtr(win->menuId, sprite->itemId);
    y = -(_CB.scroll * 0x18);
    if (_CB.scroll == 0) {
        first = 0;
    } else {
        first = _CB.scroll - 1;
        y += first * 0x18;
    }
    last = first + 0xD;
    if (last >= 0x3E) {
        last = 0x3E;
    }
    spriteSetScissor(layer, base->x - item->x, base->y - item->y, item->w, item->h);
    for (; first <= last; first++, y += 0x18) {
        if (first == 0x3E) {
            GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, 1);
        } else if (_CB.rule[first + 0x52]) {
            GSmsgPrint2(win->layer, 0, y, win->alpha | 0xFF3F0000, 0x43E4);
        } else {
            GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, 0x43E3);
        }
    }
    spriteClearScissor(layer);
}

void menuCB_RuleItemNameEntry(CBWin* win, CBSprite* sprite) {
    s32 layer;
    s32 i;
    CBMenuItem* item;
    s16 y;
    s32 first;
    s32 last;
    CBMenuItem* base;
    u16 id;
    layer = winSpriteGetLayerID(win, sprite);
    base = menuItemBiosGetPtr(win->menuId, 0x3AC);
    item = menuItemBiosGetPtr(win->menuId, sprite->itemId);
    y = -(_CB.scroll * 0x18);
    if (_CB.scroll == 0) {
        first = 0;
    } else {
        first = _CB.scroll - 1;
        y += first * 0x18;
    }
    last = first + 0xD;
    if (last >= 0x3E) {
        last = 0x3E;
    }
    spriteSetScissor(layer, base->x - item->x, base->y - item->y, item->w, item->h);
    for (i = first; i <= last; i++, y += 0x18) {
        id = menuCBRule_RegulationItemID(i);
        if (id == 0) {
            GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, 0x4345);
        } else {
            if (itemDataCheckValid(id)) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(id))));
            }
            GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, fn_8007E634(0x4276));
        }
    }
    spriteClearScissor(layer);
}

void menuCBRuleNumberDisp(CBWin* win, CBItem* item, s32 digit) {
    s16 x;
    s32 n;
    s16 v;
    s16 w;
    switch (digit) {
    case 0:
        n = RULE->v[0] / 100;
        break;
    case 1:
        n = RULE->v[0] % 100 / 10;
        break;
    case 2:
        n = RULE->v[0] % 10;
        break;
    case 3:
        n = RULE->v[1] / 100;
        break;
    case 4:
        n = RULE->v[1] % 100 / 10;
        break;
    case 5:
        n = RULE->v[1] % 10;
        break;
    case 6:
        n = RULE->v[2] / 100;
        break;
    case 7:
        n = RULE->v[2] % 100 / 10;
        break;
    case 8:
        n = RULE->v[2] % 10;
        break;
    case 9:
        v = RULE->c14;
        if (v & 0x8000) {
            ruleDispTitle(win, item);
            return;
        }
        n = v / 10;
        break;
    case 10:
        v = RULE->c14;
        if (v & 0x8000) {
            ruleDispTitle(win, item);
            return;
        }
        n = v % 10;
        break;
    case 11:
        v = RULE->c16;
        if (v & 0x8000) {
            ruleDispTitle(win, item);
            return;
        }
        n = v / 10;
        break;
    case 12:
        v = RULE->c16;
        if (v & 0x8000) {
            ruleDispTitle(win, item);
            return;
        }
        n = v % 10;
        break;
    case 13:
        if (RULE->c1c == 1) {
            ruleDispTitle(win, item);
            return;
        }
        v = RULE->c1a;
        n = v % 10;
        break;
    }
    msgctrlSetValue(0x34, (void*)n);
    msgctrlSetValue(0x2F, (void*)n);
    w = GSmsgGetRect(fn_8007E634(0x427B)) >> 16;
    x = item->w / 2 - w / 2;
    GSmsgPrint2(win->layer, x, 0, win->alpha | ~0xFF, fn_8007E634(0x427B));
}

void menuCBMessageYCenterDisp(CBWin* win, CBItem* item, s32 msg) {
    u16 h;
    s16 y;
    h = GSmsgGetRect(msg);
    y = item->h / 2 - (s16)h / 2;
    GSmsgPrint2(win->layer, 0, y, win->alpha | ~0xFF, msg);
}

void fn_80080390(CBWin* win, CBItem* item, s32 msg) {
    switch (pokecoloGetCountryCode()) {
    case 0:
        *(s32*)((u8*)item + 0x4C) = msg;
        break;
    case 1:
    case 2:
        menuCBMessageCenterDisp(win, item, msg);
        break;
    }
}

void menuCBMessageCenterDisp(CBWin* win, CBItem* item, s32 msg) {
    s16 w;
    s16 x;
    w = GSmsgGetRect(msg) >> 16;
    x = item->w / 2 - w / 2;
    GSmsgPrint2(win->layer, x, 0, (*(u32*)&item->cr & ~0xFF) | win->alpha, msg);
}

void menuCB_RuleNameChengeAfterJob(u8 first) {
    if (first) {
        GSfsysReadWait(0x88C);
        menuTopOpenFlashBack();
        menuCB_FlashStart(0);
        GSthreadSwitch();
        GSthreadSwitch();
        GSthreadSwitch();
        GSthreadSwitch();
    }
    menuCB_SE_Play(0x14);
    menuOpen(0xA9, 0);
    menuOpen(0xCE, 0);
    menuOpen(0xCB, 0);
    menuOpen(0xCC, 0);
    menuOpen(0xCD, 0);
    menuOpen(0xAA, 0);
    menuOpen(0xF7, 0);
}

void menuCB_RuleNameChengeBeforeJob(u8 first) {
    if (first) {
        menuCB_FlashEnd(1);
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xF7, 0, 0);
    menuCloseCustom(0xAA, 0, 0);
    menuCloseCustom(0xCD, 0, 0);
    menuCloseCustom(0xCC, 0, 0);
    menuCloseCustom(0xCB, 0, 0);
    menuCloseCustom(0xCE, 0, 0);
    menuCloseCustom(0xA9, 0, 1);
    if (first) {
        if (fightReadResourceID(0x842, 0x195F3400) == 0) {
            fightFreeResourceID(0x842, 0x195F3400);
        }
        GSfsysFree(0x88C);
        GSresFreeGroup(0x88C);
    }
}

void menuCB_MenuDispCheckONorOFF_RULE(CBWin* win, s32 idx) {
    if (_CB.unkB124 != -1) {
        menuSetDisp(win->menuId, 0);
        if (_CB.unkB124 == idx) {
            menuSetDisp(win->menuId, 1);
            win->alpha = _CB.unkB128;
        }
        if (_CB.unkB118 == idx) {
            menuSetDisp(win->menuId, 1);
            win->alpha = _CB.unkB12C;
        }
    } else {
        if (idx == 1) {
            menuCB_MenuDispCheckONorOFF(win, _CB.unkB118 == idx || _CB.unkB118 == 5);
            return;
        }
        menuCB_MenuDispCheckONorOFF(win, _CB.unkB118 == idx);
    }
}

void menuCB_MenuDispCheckONorOFF_TUNAIDESUB(CBWin* win, s32 idx) {
    if (_CB.unkB144 != -1) {
        menuSetDisp(win->menuId, 0);
        if (_CB.unkB144 == idx) {
            menuSetDisp(win->menuId, 1);
            win->alpha = _CB.unkB148;
        }
        if (_CB.unkAFE4 == idx) {
            menuSetDisp(win->menuId, 1);
            win->alpha = _CB.unkB14C;
        }
    } else {
        menuCB_MenuDispCheckONorOFF(win, _CB.unkAFE4 == idx);
    }
}

void menuCB_MenuDispCheckONorOFF(CBWin* win, bool on) {
    if (on) {
        menuSetDisp(win->menuId, 1);
    } else {
        menuSetDisp(win->menuId, 0);
    }
}

void menuCB_SpriteDispCheckONorOFF(CBSprite* sprite, bool on) {
    if (on) {
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}

void menuCB_GCEntry_ItemKeepJob() {
    Pokemon* p;
    u8* hero;
    u16 item;
    u16 old;
    void* nick;
    p = menuCBPokemonPtrGet(_CB.unkB1D4, _CB.unkB1D8);
    nick = pokemonBiosGetNicknamePtr(p);
    hero = _CB.hero;
    msgctrlSetValue(0x32, nick);
    item = pokemonGetSoubiItemDataId(p);
    if (item != 0) {
        if (heroItemCheckAddItemDataId(hero, item) <= 0) {
            _menuCB_errorMsgDisp2(0x3ACF);
            return;
        }
        heroItemAddItemDataId(hero, item, 1, -1);
        old = pokemonDoItemSoubi(p, 0, 0);
        msgctrlSetValue(0x2D, (void*)old);
        _menuCB_errorMsgDisp2(0x3ACD);
    } else {
        _menuCB_errorMsgDisp2(0x3ACE);
    }
}

void menuCB_GCEntry_ItemGiveJob() {
    Pokemon* p;
    u16 old;
    u8 slot;
    u8* hero;
    u16 chosen;
    int answer;
    u16 cur;
    void* nick;
    u32 idx;
    p = menuCBPokemonPtrGet(_CB.unkB1D4, _CB.unkB1D8);
    nick = pokemonBiosGetNicknamePtr(p);
    hero = _CB.hero;
    msgctrlSetValue(0x32, nick);
    if (menuCBBios_CurrentRule()->unk8 == 1) {
        _menuCB_errorMsgDisp(0x43A9);
        return;
    }
    menuOpen(0xE6, 1);
    chosen = menuPocket2Call(5, 0, hero);
    slot = menuPocket2GetLastSlotID();
    menuCloseCustom(0xE6, 0, 1);
    if (chosen != 0) {
        idx = (u16)_CB.unkB1D8 - 0x1E;
        toolBattleRuleErrorFlagClear(0, idx);
        old = pokemonDoItemSoubi(p, 0, 0);
        pokemonDoItemSoubi(p, chosen, 1);
        menuCBRule_ErrorFlagSetItemGetTiming(hero, p, idx);
        pokemonDoItemSoubi(p, 0, 0);
        pokemonDoItemSoubi(p, old, 1);
        if (menuCB_Trainer_Error_Check(idx, 9)) {
            _menuCB_errorMsgDisp(0x43AA);
            return;
        }
        if (menuCB_Trainer_Error_Check(idx, 10)) {
            _menuCB_errorMsgDisp(0x43AB);
            return;
        }
        if (menuCB_Trainer_Error_Check(idx, 11)) {
            _menuCB_errorMsgDisp(0x43AC);
            return;
        }
        cur = pokemonGetSoubiItemDataId(p);
        if (cur != 0) {
            msgctrlSetValue(0x2D, (void*)cur);
            winMsgOpen(2, 0x3ACA, 1, 0);
            switch (pokecoloGetCountryCode()) {
            case 0:
                answer = menuSubOpenYesNo(0, 0x3C, 0xD2, 0);
                break;
            case 1:
            case 2:
                answer = menuSubOpenYesNo(0, 0x3C, 0xC8, 0);
                break;
            }
            winMsgClose(1);
            if (answer == 0) {
                if (heroItemDecItemDataId(hero, chosen, 1, (u8)slot) != 0) {
                    _menuCB_errorMsgDisp2(0x3ACF);
                    return;
                }
                if (heroItemCheckAddItemDataId(hero, cur) <= 0) {
                    heroItemAddItemDataId(hero, chosen, 1, -1);
                    _menuCB_errorMsgDisp2(0x3ACF);
                    return;
                }
                heroItemAddItemDataId(hero, cur, 1, -1);
                old = pokemonDoItemSoubi(p, 0, 0);
                pokemonDoItemSoubi(p, chosen, 1);
                msgctrlSetValue(0x2D, (void*)old);
                msgctrlSetValue(0x2E, (void*)chosen);
                _menuCB_errorMsgDisp2(0x3ACB);
            }
        } else if (heroItemDecItemDataId(hero, chosen, 1, (u8)slot) == 0) {
            pokemonDoItemSoubi(p, chosen, 1);
            msgctrlSetValue(0x2D, (void*)chosen);
            _menuCB_errorMsgDisp2(0x3ACC);
        }
    }
}

void menuCBRULE_EditNameDispLarge(CBWin* win, s32 idx) {
    u16 buf[0x1F];
    u16* s;
    int i;
    s32 n;
    if (idx >= 3) {
        msgctrlSetValue(0x37, &_CB.ruleStr[idx * 0x90]);
    } else {
        switch (idx) {
        case 0:
            s = GSmsgGetGSchar(0x4387);
            break;
        case 1:
            s = GSmsgGetGSchar(0x4389);
            break;
        case 2:
            s = GSmsgGetGSchar(0x4388);
            break;
        }
        for (i = 0; i < 0x1F; i++) {
            if (s) {
                if (*s == 0xFFFF) {
                    s += 2;
                }
                buf[i] = *s;
                if (*s) {
                    s++;
                }
            } else {
                buf[i] = 0;
            }
        }
        msgctrlSetValue(0x37, buf);
    }
    GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4275);
    if (_CB.unkB118 == 5) {
        msgctrlSetValue(0x34, (void*)2);
    } else {
        msgctrlSetValue(0x34, (void*)(_CB.unkB118 + 1));
    }
    msgctrlSetValue(0x2F, (void*)_CB.unkB1E0);
    GSmsgPrint2(win->layer, 0x1CE, 0, win->alpha | ~0xFF, 0x427A);
    GSmsgPrint2(win->layer, 0x1E4, 2, win->alpha | ~0xFF, 0x4417);
    msgctrlSetValue(0x34, (void*)(n = _CB.unkB014 != -1 ? 5 : 4));
    msgctrlSetValue(0x2F, (void*)n);
    GSmsgPrint2(win->layer, 0x1FA, 0, win->alpha | ~0xFF, 0x427A);
}

void menuCBRULE_EditNameDisp(CBWin* win, CBItem* item, s32 idx) {
    msgctrlSetValue(0x37, &_CB.ruleStr[idx * 0x90]);
    GSmsgPrint2(win->layer, 0, 0, (*(u32*)&item->cr & ~0xFF) | win->alpha, 0x4277);
}

void menuCB_GCEntry_PokemonStatusDisp() {
    Pokemon* p = menuCBPokemonPtrGet(_CB.unkB1D4, _CB.unkB1D8);
    _menuCB_PokemonStatusDispBeforeJob(0);
    menuPokemonStatusOpenFromPokemonChange(p, 0, 0);
    _menuCB_PokemonStatusDispAfterJob(0);
}

s32 menuCB_GCEntry_SubWindow_Disp(void) {
    s16 x;
    s16 y;
    u16 idx;
    if (CB32(0xAFF0) == 1) {
        winMsgOpen(2, 0x43A1, 1, 0);
        switch (pokecoloGetCountryCode()) {
        case 0:
            _CB.unkAFE0 = menuSubOpenYesNo(0, 0x3C, 0xD2, 0);
            break;
        case 1:
        case 2:
            _CB.unkAFE0 = menuSubOpenYesNo(0, 0x3C, 0xC8, 0);
            break;
        }
        if (_CB.unkAFE0 == -1) {
            _CB.unkAFE0 = 1;
        }
        winMsgClose(0);
        return _CB.unkAFE0;
    }
    menuCBGCEntryTypeIndex();
    idx = _CB.unkB1D8;
    if (idx >= 0x1E && idx <= 0x23) {
        _CB.unkAFE0 = menuSubOpenSelect2(0, submenu_msg2, 4, 0x28, 0x64, 0, 4, 1);
        if (_CB.unkAFE0 == -1) {
            _CB.unkAFE0 = 3;
        }
        switch (_CB.unkAFE0) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            winMsgOpen(2, 0x43A0, 0, 0);
            _CB.unkAFE0 = menuSubOpenSelect2(0, submenu_msg3, 3, 0x28, 0x64, 0, 3, 1);
            if (_CB.unkAFE0 == -1) {
                _CB.unkAFE0 = 2;
            }
            switch (_CB.unkAFE0) {
            case 0:
                winMsgClose(0);
                return 4;
            case 1:
                return 5;
            case 2:
                winMsgClose(0);
                return 6;
            }
        case 3:
            return 6;
        }
    } else {
        x = 0x104;
        y = 0xC8;
        switch (_CB.unkB0F0) {
        case 0:
            break;
        case 1:
            x = submenu1_x[idx];
            y = submenu1_y[idx];
            break;
        case 2:
        case 3:
            break;
        }
        if (_CB.unkB100 == 6) {
            _CB.unkAFE0 = menuSubOpenSelect2(0, submenu_msg1s, 2, x, y, 0, 2, 1);
            if (_CB.unkAFE0 == -1) {
                _CB.unkAFE0 = 1;
            }
        } else {
            _CB.unkAFE0 = menuSubOpenSelect2(0, submenu_msg1, 3, x, y, 0, 3, 1);
            if (_CB.unkAFE0 == -1) {
                _CB.unkAFE0 = 2;
            }
        }
        if (_CB.unkB100 == 6) {
            switch (_CB.unkAFE0) {
            case 0:
                return 2;
            case 1:
                return 6;
            }
        } else {
            switch (_CB.unkAFE0) {
            case 0:
                return 0;
            case 1:
                return 2;
            case 2:
                return 6;
            }
        }
    }
    return 6;
}

void menuCB_TUNAIDE01_Rule_SELECT(void) {
    switch (CB32(0xB004)) {
    case 0:
    case 1:
    case 2:
        _CB.unkAFE0 = menuSubOpenSelect2(0, submenurule_msg1, 3, 0x28, 0xF4, _CB.unkAFE0, 3, 1);
        if (_CB.unkAFE0 == -1) {
            _CB.unkAFE0 = 2;
        }
        break;
    case 3:
    case 4:
    case 5:
        _CB.unkAFE0 = menuSubOpenSelect2(0, submenurule_msg2, 4, 0x28, 0xD4, _CB.unkAFE0, 4, 1);
        if (_CB.unkAFE0 == -1) {
            _CB.unkAFE0 = 3;
        }
        _CB.unkAFE0 = _CB.unkAFE0 + 0x10;
        break;
    }
    switch (_CB.unkAFE0) {
    case 0:
    case 16:
        CB32(0xB10C) = 0;
        break;
    case 2:
    case 19:
        CB32(0xB10C) = 1;
        break;
    }
}

void menuCB_GCEntry_OkPushErrorCheck(void) {
    void* hero;
    u32 j;
    u32 i;
    for (i = 0; i < 6; i++) {
        toolBattleRuleErrorFlagClear(0, i);
    }
    hero = (u8*)&_CB + 0xA65C;
    menuCBRule_ErrorFlagSet(hero, 0);
    for (u32 i_loop = 0; i_loop < 6; i_loop++) {
        if (menuCB_Trainer_Error_Check(i_loop, 8)) {
            _CB.unkB1DC = 0x43A9;
            _CB.unkB0FC = 2;
            return;
        }
        if (menuCB_Trainer_Error_Check(i_loop, 9)) {
            _CB.unkB1E0 = i_loop + 1;
            _CB.unkB1DC = 0x4410;
            _CB.unkB0FC = 2;
            return;
        }
        if (menuCB_Trainer_Error_Check(i_loop, 10)) {
            _CB.unkB1DC = 0x43AB;
            _CB.unkB0FC = 2;
            return;
        }
        if (menuCB_Trainer_Error_Check(i_loop, 11)) {
            _CB.unkB1DC = 0x43AC;
            _CB.unkB0FC = 2;
            return;
        }
    }
    for (j = 0; j < 6; j++) {
        toolBattleRuleErrorFlagClear(0, j);
    }
    menuCBRule_ErrorFlagSetOkPushTiming(hero);
    if (menuCB_Trainer_Error_Check(0, -1)) {
        _CB.unkB0FC = 2;
        if (_CB.err[_CB.errPlayer][0].b2) {
            _CB.unkB1DC = 0x43AE;
        }
    }
}

void menuCB_WaitGCControler1() {
    if (!GSinputIsConnected(1)) {
        winMsgOpen(2, gbaCommandIsConnected(1) ? 0x442D : 0x4436, 0, 0);
        while (!GSinputIsConnected(1)) {
            GSthreadSwitch();
        }
        winMsgClose(1);
    }
}

void menuCB_GBADisconnectedErrorJob(void) {
    s32 r = menuCB_GetDisconnectedGBA();
    switch (r) {
    case 0:
        if (gbaCommandIsConnected(1)) {
            winMsgOpen(2, 0x442D, 0, 0);
            while (!GSinputIsConnected(1)) {
                GSthreadSwitch();
            }
        } else {
            winMsgOpen(2, 0x442C, 1, 0);
        }
        break;
    case 1:
        winMsgOpen(2, 0x4438, 0, 0);
        while (!GSinputIsConnected(1)) {
            GSthreadSwitch();
        }
        break;
    default:
        if (gbaCommandIsConnected(1)) {
            winMsgOpen(2, 0x442D, 0, 0);
            while (!GSinputIsConnected(1)) {
                GSthreadSwitch();
            }
        } else {
            msgctrlSetValue(0x2F, (void*)r);
            winMsgOpen(2, 0x442B, 1, 0);
        }
        break;
    }
    winMsgClose(1);
    menuCB_WaitGCControler1();
}

void menuCBPokemonEntryGCControlDisp(CBSprite* sprite, s32 b) {
    if (menuCBPokemonEntryDisp(sprite)) {
        if (!menuCBPokemonGetDataId(0, b)) {
            winSpriteSetDisp(sprite, 0);
        }
    }
}

void menuCBPokemonEntryBallAnaDisp(CBItem* item, s32 player, u32 idx) {
    u32 max = menuCBBios_ParticipationPokemonMax();
    u16 num = toolentryTaisenGetPokemonNum(player);
    CBB.x[player][idx] = item->x;
    if (CBB.on[player][idx] == 0) {
        CBB.y[player][idx] = 0x32;
    }
    num = num < max ? num : max;
    if (idx > num) {
        winSpriteSetDisp(item, 0);
        return;
    }
    winSpriteSetDisp(item, 1);
}

void menuCBPokemonEntryBallDisp(CBItem* item, s32 player, u32 idx) {
    enum TsE { TsE0 };
    s8* flag;
    u16 max = (u16)menuCBBios_ParticipationPokemonMax();
    u16 num = toolentryTaisenGetPokemonNum(player);
    enum TsE order = (enum TsE)(toolentryTaisengetEtnryPokemonOrderNum(player));
    num = num < max ? num : max;
    if (idx > num || idx > order) {
        if (pauseIsPause()) {
            if (CBB.on[player][idx] == 0) {
                winSpriteSetDisp(item, 0);
                return;
            }
            winSpriteSetDisp(item, 1);
            return;
        }
        winSpriteSetDisp(item, 0);
        CBB.on[player][idx] = 0;
        return;
    }
    if (pauseIsPause()) {
        flag = &CBB.on[player][idx];
        if (*flag != 1) {
            winSpriteSetDisp(item, 0);
            *flag = 0;
            return;
        }
    }
    CBB.on[player][idx] = 1;
    item->x = CBB.x[player][idx] + CBB.y[player][idx];
    if (CBB.y[player][idx] != 0) {
        CBB.y[player][idx] -= 5;
    }
    winSpriteSetDisp(item, 1);
    if (*(s32*)((u8*)&_CB + player * 0x1320 + idx * 4 + 0x1C) == 0xF) {
        winSpriteSetDisp(item, 0);
    }
}

u8 menuCBPokemonEntryDispPokemonFace_AFTER(s32 a, s32 b, s32 c, s32 d) {
    if (menuCBBattleStartGetStatus() != 0) {
        menuCBPokemonEntryDispPokemonFace(a, b, c, d);
        return 1;
    }
    return 0;
}

u8 menuCBPokemonEntryDispPokemonFace_BEFORE(s32 a, s32 b, s32 c, s32 d) {
    if (menuCBBattleStartGetStatus() == 0) {
        menuCBPokemonEntryDispPokemonFace(a, b, c, d);
        return 1;
    }
    return 0;
}

void menuCB_BattleEntryPokemonSelectDisp(CBSprite* sprite, u32 a, u32 b) {
    menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonCheck(a, b) == 0);
}

u8 menuCB_GCStatusDispMode(CBSprite* sprite, s32 mode) {
    if (_CB.unk8 == 2) {
        if (mode == 0) {
            winSpriteSetDisp(sprite, 1);
            return 1;
        }
        winSpriteSetDisp(sprite, 0);
        return 0;
    }
    if (mode == 1) {
        winSpriteSetDisp(sprite, 1);
        return 1;
    }
    winSpriteSetDisp(sprite, 0);
    return 0;
}

u8 menuCBPokemonEntryDisp(CBSprite* sprite) {
    u8 ok = 1;
    switch ((u16)toolentryTaisenGetHomePlace(0)) {
    case 0:
        winSpriteSetDisp(sprite, 1);
        break;
    default:
        winSpriteSetDisp(sprite, 0);
        ok = 0;
        break;
    }
    return ok;
}

void menuCBGCEntryTypeIndex(void) {
    switch (_CB.unkB0F0) {
    case 0:
        _CB.unkB1D4 = 4;
        _CB.unkB1D8 = _CB.unkB0F8;
        return;
    case 1:
        _CB.unkB1D4 = 5;
        _CB.unkB1D8 = (u16)_CB.unkB0F8 | ((_CB.unkB0E8 << 16) & 0xFFFF0000);
        return;
    case 2:
        _CB.unkB1D4 = 6;
        _CB.unkB1D8 = (u16)_CB.unkB0F8 | ((_CB.unkB0EC << 16) & 0xFFFF0000);
        return;
    case 3:
        _CB.unkB1D4 = 7;
        _CB.unkB1D8 = _CB.unkB0F8;
        return;
    }
}

void menuCBGCDelPokemon(void) {
    s32 saved = _CB.unkB0F8;
    switch (_CB.unkB100) {
    case 1:
        _CB.unkB0F8 = 0x1E;
        break;
    case 2:
        _CB.unkB0F8 = 0x1F;
        break;
    case 3:
        _CB.unkB0F8 = 0x20;
        break;
    case 4:
        _CB.unkB0F8 = 0x21;
        break;
    case 5:
        _CB.unkB0F8 = 0x22;
        break;
    case 6:
        _CB.unkB0F8 = 0x23;
        break;
    }
    _menuCBGCDelPokemon();
    _CB.unkB0F8 = saved;
}

void menuCBGCEntryPokemon(void) {
    u32 type;
    Pokemon* src;
    Pokemon* slot;
    u32 index;
    menuCBGCEntryTypeIndex();
    if (menuCBPokemonCheck(_CB.unkB1D4, _CB.unkB1D8)) {
        if (_CB.unkB0F8 >= 0x1E) {
            _menuCBGCDelPokemon();
            return;
        }
        if (_CB.unkB100 != 6) {
            menuCBGCEntryTypeIndex();
            type = _CB.unkB1D4;
            index = _CB.unkB1D8;
            backup_type[_CB.unkB100] = type;
            backup_index[_CB.unkB100] = index;
            slot = menuCBPokemonPtrGet(7, _CB.unkB100);
            switch (pokecoloGetCountryCode()) {
            case 0:
                if (type != 6) {
                    src = menuCBPokemonPtrGet(type, index);
                    memcpy(slot, src, 0xC4);
                    pokemonInit(src);
                } else {
                    if (_CB.unkB0F8 == 4) {
                        backup_type[_CB.unkB100] = 0;
                        backup_index[_CB.unkB100] = 0;
                        _CB.unkB0FC = 2;
                        _CB.unkB1DC = 0x43A5;
                        return;
                    }
                    CReliveHall::getPointer()->getStage(index >> 16)->pickupDancer(*slot, index & 0xFFFF);
                }
                break;
            case 1:
            case 2:
                if (type == 6 && _CB.unkB0F8 == 4) {
                    backup_type[_CB.unkB100] = 0;
                    backup_index[_CB.unkB100] = 0;
                    _CB.unkB0FC = 2;
                    _CB.unkB1DC = 0x43A5;
                    return;
                }
                src = menuCBPokemonPtrGet(type, index);
                memcpy(slot, src, 0xC4);
                pokemonInit(src);
                break;
            }
            _CB.unkB100 = _CB.unkB100 + 1;
            if (menuCBGCEntry_ErrorDisp(type, _CB.unkB100 + 0x1D) != 0 && _CB.unkB100 == 6) {
                _CB.unkB0F8 = 0x25;
            }
        }
    }
}

void menuCBReliveHallCursolInit(void) {
    s32 hi;
    u32 i;
    s32 e = _CB.unkB0EC;
    if (_CB.unkB0F8 <= 4) {
        hi = (e << 16) & 0xFFFF0000;
        if (menuCBPokemonCheck(6, _CB.unkB0F8 | hi) == 0) {
            for (i = 0; i < 5; i++) {
                if (menuCBPokemonCheck(6, i | hi) != 0) {
                    _CB.unkB0F8 = (s8)i;
                    break;
                }
            }
            if ((u32)_CB.unkB0F8 != i) {
                _CB.unkB0F8 = 0x1E;
            }
        }
    }
}

void menuCBPCBOXTitleNameDisp(CBWin* win, CBItem* item, s8 box, s32 x) {
    s16 w;
    s16 x1;
    spriteSetScissor(win->layer, 0, 0, 0xD1, 0x12);
    msgctrlSetValue(0x37, PCBOX::getPointer()->getPokemonBoxName((u16)box));
    w = GSmsgGetRect(0x4277) >> 16;
    x1 = item->w / 2 - w / 2;
    x1 += x;
    GSmsgPrint2(win->layer, x1, 0, win->alpha | ~0xFF, 0x4277);
    spriteClearScissor(win->layer);
}

void menuCBReliveTitleNameDisp(CBWin* win, CBItem* item, s32 id, s32 x) {
    s16 w;
    s16 x1;
    spriteSetScissor(win->layer, 0, 0, 0xD1, 0x12);
    msgctrlSetValue(0x37, GSmsgGetGSchar(id));
    w = GSmsgGetRect(0x4277) >> 16;
    x1 = item->w / 2 - w / 2;
    x1 += x;
    GSmsgPrint2(win->layer, x1, 0, win->alpha | ~0xFF, 0x4277);
    spriteClearScissor(win->layer);
}

void menuCBGCEntryTitleDisp(CBWin* win, CBItem* item, s32 msg, s32 x) {
    s16 w;
    s16 x1;
    spriteSetScissor(win->layer, 0, 0, 0xD1, 0x12);
    msgctrlSetValue(0x37, heroBiosGetNamePtr(_CB.hero));
    w = GSmsgGetRect(msg) >> 16;
    x1 = item->w / 2 - w / 2;
    x1 += x;
    GSmsgPrint2(win->layer, x1, 0, win->alpha | ~0xFF, msg);
    spriteClearScissor(win->layer);
}

u8 menuCBPokemonCheck(u32 a, u32 b) {
    Pokemon* p = menuCBPokemonPtrGet(a, b);
    if (p && pokemonCheckValid(p)) {
        return 1;
    }
    return 0;
}

void menuCBPokemonItemName(CBWin* win, u32 type, u32 index, s32 mode) {
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    s32 name = 1;
    if (p && pokemonCheckValid(p)) {
        u16 item = pokemonGetSoubiItemDataId(p);
        if (item != 0) {
            name = itemDataBiosGetName(itemDataBiosGetPtr(item));
        }
    }
    msgctrlSetValue(0x37, GSmsgGetGSchar(name));
    switch (mode) {
    case 0:
        GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, fn_8007E634(0x4278));
        return;
    case 1:
        GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, fn_8007E634(0x4276));
        return;
    }
}

void menuCBPokemonWazaNAME(CBWin* win, u32 type, u32 index, u32 slot) {
    s32 n;
    u32 lv;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    if (p && pokemonCheckValid(p)) {
        u16 waza = pokemonGetStatus(p, 0, 0x7F, slot);
        if (waza == 0) {
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x3AF4);
            return;
        }
        u32 nameId = wazaGetStatus(0, waza, 1, 0);
        if (nameId != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(nameId));
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4279);
            switch (pokecoloGetCountryCode()) {
            case 0:
                n = 10;
                lv = pokemonGetStatus(p, 0, 0x80, slot);
                if (lv < 10) {
                    n = 11;
                }
                msgctrlSetValue(0x34, (void*)lv);
                GSmsgPrint2(win->layer, n * 0xD, 0, win->alpha | ~0xFF, 0x427C);
                break;
            case 1:
            case 2:
                msgctrlSetValue(0x34, (void*)pokemonGetStatus(p, 0, 0x80, slot));
                GSmsgPrintRight(win->layer, 0x82, 0, 0x1A, 0, win->alpha | ~0xFF, fn_8007E634(0x427C));
                break;
            }
        }
    }
}

void menuCBPokemonWazaTYPE(CBWin* win, u32 type, u32 index, u32 slot) {
    s32 sprite;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    if (p && pokemonCheckValid(p)) {
        u16 waza = pokemonGetStatus(p, 0, 0x7F, slot);
        s32 w = _menuCB_NotDarkWaza(waza);
        switch (w) {
        case 0:
            sprite = 0;
            break;
        case 0x176:
            sprite = 0x193;
            break;
        default:
            sprite = zokuseiBiosGetSmallSpriteID(wazaGetStatus(0, waza, 3, 0));
            break;
        }
        if ((u32)sprite != 0) {
            windowDrawSprite(0, 0, win, sprite, 0, win->layer);
        }
    }
}

void menuCBPokemonTYPE2(CBWin* win, u32 type, u32 index) {
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    void* pd = pokemonDataBiosGetPtr(pokemonGetStatus(p, 0, 0x6E, 0));
    u32 t;
    t = pokemonDataBiosGetZokuseiDataId(pd, 0);
    if (t != pokemonDataBiosGetZokuseiDataId(pd, 1)) {
        u16 sprite = zokuseiGetPokemonSpriteID(pd, 1);
        if (sprite) {
            windowDrawSprite(0, 0, win, sprite, 0, win->layer);
        }
    }
}

void menuCBPokemonTYPE1(CBWin* win, u32 a, u32 b) {
    Pokemon* p = menuCBPokemonPtrGet(a, b);
    u16 id = pokemonGetStatus(p, 0, 0x6E, 0);
    u16 sprite = zokuseiGetPokemonSpriteID(pokemonDataBiosGetPtr(id), 0);
    if (sprite) {
        windowDrawSprite(0, 0, win, sprite, 0, win->layer);
    }
}

void menuCBPokemonStatusDisp(CBWin* win, u32 type, u32 index, s32 mode, s32 kind) {
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    s32 value;
    s32 n;
    if (p && pokemonCheckValid(p)) {
        switch (kind) {
        case 0:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x43F5);
            value = (u16)pokemonGetStatus(p, 0, 0x88, 0);
            break;
        case 1:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x43F6);
            value = (u16)pokemonGetStatus(p, 0, 0x89, 0);
            break;
        case 2:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x43F7);
            value = (u16)pokemonGetStatus(p, 0, 0x8A, 0);
            break;
        case 3:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x43F8);
            value = (u16)pokemonGetStatus(p, 0, 0x8B, 0);
            break;
        case 4:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x43F9);
            value = (u16)pokemonGetStatus(p, 0, 0x8C, 0);
            break;
        }
        msgctrlSetValue(0x34, (void*)value);
        msgctrlSetValue(0x2F, (void*)value);
        switch (pokecoloGetCountryCode()) {
        case 0:
            n = 5;
            if (value < 10) {
                n = 6;
            }
            if (value < 100) {
                n += 1;
            }
            switch (mode) {
            case 0:
                GSmsgPrint2(win->layer, n * 0xD, 0, win->alpha | ~0xFF, 0x427C);
                break;
            case 1:
                GSmsgPrint2(win->layer, n * 0x12, 0, win->alpha | ~0xFF, 0x427B);
                break;
            }
            break;
        case 1:
        case 2:
            switch (mode) {
            case 0:
                GSmsgPrintRight(win->layer, 0x3A, 0, 0x27, 0, win->alpha | ~0xFF, fn_8007E634(0x427C));
                break;
            case 1:
                GSmsgPrintRight(win->layer, 0x51, 0, 0x36, 0, win->alpha | ~0xFF, fn_8007E634(0x427B));
                break;
            }
            break;
        }
    }
}

void menuCBPokemonTOKUSEI(CBWin* win, u32 type, u32 index) {
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    s32 name = 1;
    if (p && pokemonCheckValid(p)) {
        name = pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(pokemonGetTokuseiDataId(p)));
    }
    msgctrlSetValue(0x37, GSmsgGetGSchar(name));
    switch (pokecoloGetCountryCode()) {
    case 0:
        GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x435A);
        GSmsgPrint2(win->layer, 0x5A, 0, win->alpha | ~0xFF, 0x4276);
        break;
    case 1:
    case 2:
        GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x445B);
        GSmsgPrint2(win->layer, (s16)(GSmsgGetRect(0x445B) >> 16), 0, win->alpha | ~0xFF, 0x4277);
        break;
    }
}

void menuCBPokemonHP(CBWin* win, u32 type, u32 index, s32 mode) {
    u16 hp;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    if (p && pokemonCheckValid(p)) {
        hp = pokemonBiosGetHp(p);
        msgctrlSetValue(0x34, (void*)hp);
        msgctrlSetValue(0x2F, (void*)hp);
        switch (mode) {
        case 0:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x43EA);
            switch (pokecoloGetCountryCode()) {
            case 1:
            case 2:
                GSmsgPrint2(win->layer, 0x1B, 0, win->alpha | ~0xFF, 0x427C);
                break;
            }
            break;
        case 3:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, fn_8007E634(0x427C));
            return;
        case 1:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4397);
            switch (pokecoloGetCountryCode()) {
            case 1:
            case 2:
                GSmsgPrint2(win->layer, 0x26, 0, win->alpha | ~0xFF, 0x427B);
                break;
            }
            break;
        case 2:
            break;
        }
    }
}

void menuCBPokemonLevel(CBWin* win, u32 type, u32 index, s32 mode) {
    u8 lv;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    if (p == 0 || pokemonCheckValid(p) == 0 || pokemonBiosGetTamagoFlag(p) != 0) {
        return;
    }
    {
        lv = _menuCBPokemonEntryGetlevel(p);
        msgctrlSetValue(0x34, (void*)lv);
        msgctrlSetValue(0x2F, (void*)lv);
        switch (mode) {
        case 0:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x43E9);
            switch (pokecoloGetCountryCode()) {
            case 1:
            case 2:
                GSmsgPrint2(win->layer, 0x1B, 0, win->alpha | ~0xFF, 0x427C);
                break;
            }
            break;
        case 3:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, fn_8007E634(0x427C));
            return;
        case 1:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4396);
            switch (pokecoloGetCountryCode()) {
            case 1:
            case 2:
                GSmsgPrint2(win->layer, 0x26, 0, win->alpha | ~0xFF, 0x427B);
                break;
            }
            break;
        case 2:
            break;
        }
    }
}

void menuCBPokemonNameOrg(CBWin* win, u32 type, u32 index, s32 mode) {
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    s32 name = 1;
    if (p && pokemonCheckValid(p)) {
        name = pokemonDB_GetName(pokemon_GetPokemonDataId(p));
    }
    msgctrlSetValue(0x37, GSmsgGetGSchar(name));
    switch (mode) {
    case 0:
        GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4279);
        return;
    case 1:
        GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4277);
        return;
    }
}

void menuCBPokemonSexOnly(CBWin* win, u32 type, u32 index, s32 mode) {
    u32 msg;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    if (p && pokemonCheckValid(p)) {
        u8 sex = menuSubGetPokemonSexForFightDisp(p);
        switch (sex) {
        case 0:
            msg = 0x9C5;
            break;
        case 1:
            msg = 0x9C6;
            break;
        case 2:
        default:
            msg = 1;
            break;
        }
        if (msg != 1) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(msg));
            switch (mode) {
            case 0:
                GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4278);
                return;
            case 1:
                GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4276);
                break;
            }
        }
    }
}

void menuCBPokemonNameOnly(CBWin* win, u32 type, u32 index, s32 mode) {
    u16* name;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    if (p && pokemonCheckValid(p)) {
        name = (u16*)pokemonBiosGetNicknamePtr(p);
        if (name == 0) {
            name = GSmsgGetGSchar(1);
        }
        msgctrlSetValue(0x37, name);
        switch (mode) {
        case 0:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4279);
            return;
        case 1:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4277);
            break;
        }
    }
}
}

static void _menuCBPokemonName(CBWin* win, u32 type, u32 index, u32 mode, bool nido) {
    u16* name;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    u8 bad = 0;
    u32 sexMsg;
    if (p) {
        if (!pokemonCheckValid(p)) {
            if ((s32)pokemonGetStatus(p, 0, 0x6E, 0) == 0) {
                return;
            }
            name = GSmsgGetGSchar(0x56C);
            bad = 1;
        } else {
            name = (u16*)pokemonBiosGetNicknamePtr(p);
            if (name == 0) {
                name = GSmsgGetGSchar(1);
            }
            if (pokemonBiosGetTamagoFlag(p) == 1) {
                name = GSmsgGetGSchar(0x56B);
            }
        }
        msgctrlSetValue(0x37, name);
        switch (mode) {
        case 0:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4279);
            break;
        case 1:
            GSmsgPrint2(win->layer, 0, 0, win->alpha | ~0xFF, 0x4277);
            break;
        }
        if (pokemonBiosGetTamagoFlag(p) == 1 || bad != 0) {
            return;
        }
        {
            s32 sex;
            if (nido) {
                sex = menuSubGetPokemonSexForDisp(p);
            } else {
                sex = menuSubGetPokemonSexForFightDisp(p);
            }
            switch (sex) {
            case 0:
                sexMsg = 0x9C5;
                break;
            case 1:
                sexMsg = 0x9C6;
                break;
            case 2:
            default:
                sexMsg = 0;
                break;
            }
            if (sexMsg != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(sexMsg));
                switch (pokecoloGetCountryCode()) {
                case 0:
                    switch (mode) {
                    case 0:
                        GSmsgPrint2(win->layer, 0x46, 0, win->alpha | ~0xFF, 0x4278);
                        break;
                    case 1:
                        GSmsgPrint2(win->layer, 0x5A, 0, win->alpha | ~0xFF, 0x4276);
                        break;
                    }
                    break;
                case 1:
                case 2:
                    switch (mode) {
                    case 0:
                        GSmsgPrint2(win->layer, 0x5A, 0, win->alpha | ~0xFF, 0x4278);
                        break;
                    case 1:
                        GSmsgPrint2(win->layer, 0x6E, 0, win->alpha | ~0xFF, 0x4276);
                        break;
                    }
                    break;
                }
            }
        }
    }
}

extern "C" {
void menuCBPokemonName(CBWin* win, u32 a, u32 b, u32 c) {
    _menuCBPokemonName(win, a, b, c, false);
}

void menuCBPokemonName_nido(CBWin* win, u32 a, u32 b, u32 c) {
    _menuCBPokemonName(win, a, b, c, true);
}

void menuCB2DPokemonItemDisp(CBSprite* sprite, u32 a, u32 b) {
    Pokemon* p = menuCBPokemonPtrGet(a, b);
    winSpriteSetDisp(sprite, 0);
    if (p && pokemonCheckValid(p) && pokemonGetSoubiItemDataId(p)) {
        winSpriteSetDisp(sprite, 1);
    }
}

void menuCB2DPokemonClearSHIFT(u32 dir) {
    u32 i;
    if (dir == 0) {
        memcpy(antL, ant, 0x618);
        memcpy(ant, antR, 0x618);
        memset(antR, 0, 0x618);
    } else {
        memcpy(antR, ant, 0x618);
        memcpy(ant, antL, 0x618);
        memset(antL, 0, 0x618);
    }
    CAnt::systemUsecountReset();
    for (i = 0; i < 0x24; i++) {
        ant[i].use();
    }
    for (i = 0; i < 0x1E; i++) {
        antR[i].use();
        antL[i].use();
    }
    CAnt::systemUnUseResourceRelease();
    CB32(0xB154) = 0;
    if (dir == 0) {
        CB32(0xB150) = -0x10;
        CB32(0xB158) = 0x180;
    } else {
        CB32(0xB150) = 0x10;
        CB32(0xB158) = -0x180;
    }
    CB32(0xB15C) = _CB.unkB0F0;
    CB32(0xB160) = _CB.unkB0E8;
    CB32(0xB164) = _CB.unkB0EC;
}

void menuCB2DPokemonALLClear(void) {
    u32 i;
    CAnt::systemUsecountReset();
    CAnt::systemUnUseResourceRelease();
    memset(ant, 0, 0x750);
    memset(antL, 0, 0x618);
    memset(antR, 0, 0x618);
    _CB.unkB0F0 = 0;
    _menuCB2DPokemonNewSet(2);
    _menuCB2DPokemonNewSet(0);
    _menuCB2DPokemonNewSet(1);
    for (i = 0; i < 0x24; i++) {
        ant[i].use();
    }
    for (i = 0; i < 0x1E; i++) {
        antR[i].use();
        antL[i].use();
    }
}

void menuCB2DPokemonDisp2(CBWin* win, CBItem* item, u32 type, u32 index) {
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    u32 i = menuCBPokemonGetIndex(type, index);
    CAntPos pos;
    CAnt* a;
    if (p && pokemonCheckValid(p)) {
        spriteSetOffset(win->layer, 0, 0);
        spriteClearScissor(win->layer);
        spriteSetEnv(win->layer);
        if (i < 0x1E) {
            spriteSetScissor(win->layer, 0x12, 0x51, 0x180, 0x140);
        }
        pos.x = item->x + win->x8C + 0x20;
        pos.y = item->y + 0x20;
        if ((s16)CB32(0xB150) < 0) {
            a = &antR[i];
            a->initByPokemonAndSetColorAnimationInAny(p);
            antR[i].setPos(pos);
            a->setAnimation(0);
            GSprimSetup2DRender(0);
            if (a->active != 0) {
                antR[i].alpha = win->alpha;
                a->drawAndUpdate();
            }
        } else {
            a = &antL[i];
            a->initByPokemonAndSetColorAnimationInAny(p);
            antL[i].setPos(pos);
            a->setAnimation(0);
            GSprimSetup2DRender(0);
            if (a->active != 0) {
                antL[i].alpha = win->alpha;
                a->drawAndUpdate();
            }
        }
    }
}

void menuCB2DPokemonDisp(CBWin* win, CBItem* item, u32 type, u32 index) {
    CAnt* a;
    Pokemon* p = menuCBPokemonPtrGet(type, index);
    u32 i = menuCBPokemonGetIndex(type, index);
    volatile CAntPos pos;
    if (i == 0x1E) {
        _menuCB2DPokemonNewSet(0);
        _menuCB2DPokemonNewSet(1);
    }
    if (p && pokemonCheckValid(p)) {
        spriteSetOffset(win->layer, 0, 0);
        spriteClearScissor(win->layer);
        spriteSetEnv(win->layer);
        if (i < 0x1E) {
            spriteSetScissor(win->layer, 0x12, 0x51, 0x180, 0x140);
        }
        u16 rf_t = item->x;
        pos.x = rf_t + win->x8C + 0x20;
        pos.y = item->y + 0x20;
        a = &ant[i];
        a->initByPokemonAndSetColorAnimationInAny(p);
        ant[i].setPos(pos);
        a->setAnimation(0);
        GSprimSetup2DRender(0);
        if (a->active != 0) {
            ant[i].alpha = win->alpha;
            a->drawAndUpdate();
        }
    }
}

s32 menuCBBattleBANextMenu(CBWin* win) {
    if (pauseIsPause()) {
        return 0;
    }
    if (menuCBBattleStartGetStatus() == 0) {
        if (CBH.wait == 0) {
            if (menuCB_BattleStartSoundCheck()) {
                win->unkA4 = 1;
            }
            if (FlashSystemIsLastFrame(0x21533000)) {
                return 1;
            }
            return 0;
        }
        CBH.wait--;
        return 0;
    }
    if (battleEndHPEndFlag == 0) {
        win->unkA4 = 1;
        return 0;
    }
    if (--battleEndHPEndFlag == 0x37 && CB32(0xB180) != 0) {
        menuCB_SE_Stop(0x5D0);
    }
    return 0;
}

void menuCBBattleBABatuMark(CBItem* sprite, s32 p, s32 i) {
    if (menuCBBattleStartGetStatus() == 0 || menuCBPokemonGetDataId(p, i) == 0) {
        winSpriteSetDisp(sprite, 0);
        return;
    }
    if (CBH.f1[p][i] == 0.0f && CBH.f0[p][i] == 0.0f) {
        winSpriteSetDisp(sprite, 1);
        CBH.f4[p][i] = CBH.f4[p][i] + CBH.f5[p][i];
        if (CBH.f4[p][i] >= 1.0f) {
            CBH.f4[p][i] = 1.0f;
        }
        f32 v = CBH.f4[p][i];
        sprite->scaleY = v;
        sprite->scaleX = v;
        return;
    }
    winSpriteSetDisp(sprite, 0);
}

void menuCBBattleEndSetPokemonHP(void) {
    f32 total = 0.0f;
    Pokemon* mon;
    s32 p;
    s32 i;
    for (p = 0; p < 4; p++) {
        for (i = 0; i < 6; i++) {
            mon = toolentryTaisenGetEntryPokemonPtr(p, i);
            if (mon) {
                CBH.f0[p][i] = pokemonBiosGetHp(mon);
                CBH.f1[p][i] = pokemonBiosGetMaxHp(mon);
                CBH.f2[p][i] = pokemonBiosGetMaxHp(mon);
                CBH.f3[p][i] = (CBH.f2[p][i] - CBH.f0[p][i]) / 60.0f;
                total += CBH.f3[p][i];
                CBH.f4[p][i] = 0.0f;
                CBH.f5[p][i] = 0.06666667f;
            } else {
                CBH.f2[p][i] = 100.0f;
                CBH.f5[p][i] = 0.0f;
                CBH.f4[p][i] = 0.0f;
                CBH.f3[p][i] = 0.0f;
                CBH.f1[p][i] = 0.0f;
                CBH.f0[p][i] = 0.0f;
            }
        }
    }
    if (total != 0.0f) {
        CB32(0xB180) = 0x5D0;
    } else {
        CB32(0xB180) = 0;
    }
    battleEndHPStartFlag = 0x1E;
    battleEndHPEndFlag = 0x87;
}

void menuCB_BattleBA_HPBarDispSet(CBItem* sprite, s32 p, s32 i) {
    if (menuCBBattleStartGetStatus() != 0 && menuCBPokemonGetDataId(p, i) != 0) {
        winSpriteSetDisp(sprite, 1);
        if (battleEndHPStartFlag == 0) {
            CBH.f1[p][i] = CBH.f1[p][i] - CBH.f3[p][i];
            f32 lo = CBH.f0[p][i];
            if (CBH.f1[p][i] < lo) {
                CBH.f1[p][i] = lo;
            }
        } else {
            if (!pauseIsPause()) {
                battleEndHPStartFlag = battleEndHPStartFlag - 1;
            }
            if (battleEndHPStartFlag == 0 && CB32(0xB180) != 0) {
                menuCB_SE_Play(0x5D0);
            }
        }
        f32 max = CBH.f2[p][i];
        f32 cur = CBH.f1[p][i];
        s16 w = 48.0f * ((max - (max - cur)) / max);
        if (20.0f * max / 100.0f >= cur) {
            menuCB_SetSprite((CBWin*)sprite, menuSpriteBiosGetPtr(BATTLE_BA_HP_Bar_Char[2]));
        } else if (50.0f * max / 100.0f >= cur) {
            menuCB_SetSprite((CBWin*)sprite, menuSpriteBiosGetPtr(BATTLE_BA_HP_Bar_Char[1]));
        } else {
            menuCB_SetSprite((CBWin*)sprite, menuSpriteBiosGetPtr(BATTLE_BA_HP_Bar_Char[0]));
        }
        sprite->w = w;
        return;
    }
    winSpriteSetDisp(sprite, 0);
}

void menuCB_BattleBA_FacePanelSet(void* sprite, s32 a, s32 b) {
    if (menuCBPokemonGetDataId(a, b) != 0) {
        winSpriteSetDisp(sprite, 1);
        if (menuCBBattleStartGetStatus() == 0) {
            menuCB_SetSprite((CBWin*)sprite, menuSpriteBiosGetPtr(BATTLE_BA_FACEWAKU_Char[1]));
            return;
        }
        menuCB_SetSprite((CBWin*)sprite, menuSpriteBiosGetPtr(BATTLE_BA_FACEWAKU_Char[0]));
        return;
    }
    winSpriteSetDisp(sprite, 0);
}

void menuCB_DispEffect(CBWin* win) {
    switch (win->kind) {
    case 0:
        if (win->state == 0) {
            winSeqSetMenu(win->menuId, 0x189);
            win->state = 1;
        }
        break;
    case 3:
        if (win->state == 0) {
            if (CB32(0xB184) == 0) {
                winSeqSetMenu(win->menuId, 0x18D);
                win->state = 1;
                spriteClearScissor(win->layer);
                return;
            }
            win->state = 1;
            menuSetDisp(win->menuId, 0);
        }
        break;
    }
}

s32 menuCB_BattleBA_PokemonEntryNum(void) {
    s32 count[2];
    s32 i;
    s32 j;
    for (i = 0; i < 2; i++) {
        count[i] = 0;
        for (j = 0; j < 6; j++) {
            if (menuCBPokemonGetDataId(i, j) != 0) {
                count[i]++;
            }
        }
    }
    if (count[0] >= 4 || count[1] >= 4) {
        return 1;
    }
    return 0;
}

void menuCB_PrintXP(CBWin* win, s32 player) {
    menuCB_SetSprite(win, menuSpriteBiosGetPtr(BATTLE_BA_XP_PRINT_Char[toolentryTaisenGetBattlePlayerID(player)]));
}

void menuCBBattleStartDispTrainerFaceSub(CBWin* win, CBItem* item, s32 idx) {
    u8 alpha = win->alpha;
    GStexture* tex;
    GSgfxLayer* layer;
    layer = GSgfxLayerFindByID(win->layer);
    tex = (0, _menuCBBattleStartWork.ent[idx].tex);
    if (tex != 0) {
        layer->primitive = 0x98;
        layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 1, 1, 4));
        if (((layer->tex1740 != tex) || (layer->tex17F8 != tex)) || (tex->flag != 0)) {
            layer->tex1740 = tex;
            layer->f173C |= 1;
            layer->tex17F8 = tex;
            layer->f17F4 |= 1;
        }
        layer->beginSurface(4);
        f32 zero = 0.0f;
        f32 one = 1.0f;
        vertexA(0, 0, zero, zero, alpha);
        vertexA(item->w, 0, one, zero, alpha);
        vertexA(0, item->h, zero, one, alpha);
        vertexA(item->w, item->h, one, one, alpha);
        layer->endSurface();
    }
}

void menuCBPokemonMaruWaku_ErrorSet(CBItem* item, s32 idx) {
    if (menuCB_Trainer_Error_Check(idx, -1) == 0) {
        winSpriteSetDisp(item, 0);
        return;
    }
    if (menuCBPokemonGetDataId(_CB.errPlayer, idx) != 0) {
        item->cr = 0xBF;
        item->cg = 0;
        item->cb = 0;
        winSpriteSetDisp(item, 1);
        return;
    }
    if (menuCBPokemonGetDataId_NULL(_CB.errPlayer, idx) != 0) {
        item->cr = 0xBF;
        item->cg = 0;
        item->cb = 0;
        winSpriteSetDisp(item, 1);
        return;
    }
    winSpriteSetDisp(item, 0);
}

void menuCBPokemonItem_ErrorSet(CBItem* item, s32 idx) {
    if (menuCBPokemonGetItemDataId(_CB.errPlayer, (s32)idx) != 0) {
        int sum = menuCB_Trainer_Error_Check(idx, 8);
        sum += menuCB_Trainer_Error_Check(idx, 9);
        sum += menuCB_Trainer_Error_Check(idx, 10);
        sum += menuCB_Trainer_Error_Check(idx, 11);
        if (sum != 0) {
            item->cr = 0xBF;
            item->cg = 0;
            item->cb = 0;
        }
        winSpriteSetDisp(item, 1);
        return;
    }
    winSpriteSetDisp(item, 0);
}
}

static u8 _menuCBPokemon_ErrorDispSet(long idx) {
    if (menuCBPokemonGetDataId(_CB.errPlayer, idx) == 0) {
        return menuCBPokemonGetDataId_NULL(_CB.errPlayer, idx) != 0;
    }
    return 1;
}

extern "C" {
u8 menuCBPokemon_ErrorDispSet(void* sprite, s32 idx) {
    if (menuCBPokemonGetDataId(_CB.errPlayer, idx) != 0) {
        winSpriteSetDisp(sprite, 1);
    } else if (menuCBPokemonGetDataId_NULL(_CB.errPlayer, idx) != 0) {
        winSpriteSetDisp(sprite, 1);
        return 1;
    } else {
        winSpriteSetDisp(sprite, 0);
        return 0;
    }
    return 1;
}

bool toolBattle_tunaideMenu02menuTempBuffGet(u32 mask) {
    return (_CB.tempBuff & mask) != 0;
}

void toolBattle_tunaideMenu02menuTempBuffSet(u32 mask) {
    if (_CB.tempBuff & mask) {
        return;
    }
    _CB.tempBuff |= mask;
}

void menuCB_Trainer_Error_Disp(CBWin* win, CBItem* item, s32 idx, s32 mode) {
    s32 i;
    for (i = 0; i < 14; i++) {
        err_msgID[i] = 0;
        err_msgID2[i] = 0;
    }
    _CB.unkB0E4 = 0;
    if (_CB.err[_CB.errPlayer][idx].a7) {
        err_msgID[_CB.unkB0E4] = 0x43FD;
        err_msgID2[_CB.unkB0E4] = 0x43AF;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].a6) {
        err_msgID[_CB.unkB0E4] = 0x43FE;
        err_msgID2[_CB.unkB0E4] = 0x43A2;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].a5 || _CB.err[_CB.errPlayer][idx].a4) {
        err_msgID[_CB.unkB0E4] = 0x43FF;
        err_msgID2[_CB.unkB0E4] = 0x43B0;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].a3) {
        err_msgID[_CB.unkB0E4] = 0x4400;
        err_msgID2[_CB.unkB0E4] = 0x43A5;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].a2) {
        err_msgID[_CB.unkB0E4] = 0x4401;
        err_msgID2[_CB.unkB0E4] = 0x43A6;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].a1) {
        err_msgID[_CB.unkB0E4] = 0x4402;
        err_msgID2[_CB.unkB0E4] = 0x43A7;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].a0 || _CB.err[_CB.errPlayer][idx].b1) {
        err_msgID[_CB.unkB0E4] = 0x4403;
        err_msgID2[_CB.unkB0E4] = 0x43A8;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].b7) {
        err_msgID[_CB.unkB0E4] = 0x4404;
        err_msgID2[_CB.unkB0E4] = 0x43A9;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].b6) {
        err_msgID[_CB.unkB0E4] = 0x4405;
        err_msgID2[_CB.unkB0E4] = 0x43AA;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].b5) {
        err_msgID[_CB.unkB0E4] = 0x4406;
        err_msgID2[_CB.unkB0E4] = 0x43AB;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].b4) {
        err_msgID[_CB.unkB0E4] = 0x4407;
        err_msgID2[_CB.unkB0E4] = 0x43AC;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].b3) {
        err_msgID[_CB.unkB0E4] = 0x4408;
        err_msgID2[_CB.unkB0E4] = 0x43AD;
        _CB.unkB0E4++;
    }
    if (_CB.err[_CB.errPlayer][idx].b2) {
        err_msgID[_CB.unkB0E4] = 0x4409;
        err_msgID2[_CB.unkB0E4] = 0x43AE;
        _CB.unkB0E4++;
    }
    err_msgID[_CB.unkB0E4] = 0x435E;
    err_msgID2[_CB.unkB0E4] = 0;
    switch (mode) {
    case 0:
        idx = 0;
        break;
    case 1:
        idx = 7;
        break;
    }
    *(s32*)((u8*)item + 0x4C) = err_msgID[idx];
    if (err_msgID[idx + 1] != 0) {
        GSmsgPrint2(win->layer, 0, 0x20, win->alpha | ~0xFF, err_msgID[idx + 1]);
    }
    if (err_msgID[idx + 2] != 0) {
        GSmsgPrint2(win->layer, 0, 0x40, win->alpha | ~0xFF, err_msgID[idx + 2]);
    }
    if (err_msgID[idx + 3] != 0) {
        GSmsgPrint2(win->layer, 0, 0x60, win->alpha | ~0xFF, err_msgID[idx + 3]);
    }
    if (err_msgID[idx + 4] != 0) {
        GSmsgPrint2(win->layer, 0, 0x80, win->alpha | ~0xFF, err_msgID[idx + 4]);
    }
    if (err_msgID[idx + 5] != 0) {
        GSmsgPrint2(win->layer, 0, 0xA0, win->alpha | ~0xFF, err_msgID[idx + 5]);
    }
    if (err_msgID[idx + 6] != 0) {
        GSmsgPrint2(win->layer, 0, 0xC0, win->alpha | ~0xFF, err_msgID[idx + 6]);
    }
}

void toolBattleRuleErrorFlagClear(s32 player, u32 idx) {
    *(s32*)&_CB.err[player][idx] = 0;
}

u8 menuCB_Trainer_Error_Check(u32 player, s32 idx) {
    switch (idx) {
    case 0:
        return _CB.err[_CB.errPlayer][player].a7 != 0;
    case 1:
        return _CB.err[_CB.errPlayer][player].a6 != 0;
    case 2:
        return _CB.err[_CB.errPlayer][player].a5 != 0;
    case 3:
        return _CB.err[_CB.errPlayer][player].a4 != 0;
    case 4:
        return _CB.err[_CB.errPlayer][player].a3 != 0;
    case 5:
        return _CB.err[_CB.errPlayer][player].a2 != 0;
    case 6:
        return _CB.err[_CB.errPlayer][player].a1 != 0;
    case 7:
        return _CB.err[_CB.errPlayer][player].a0 != 0;
    case 8:
        return _CB.err[_CB.errPlayer][player].b7 != 0;
    case 9:
        return _CB.err[_CB.errPlayer][player].b6 != 0;
    case 10:
        return _CB.err[_CB.errPlayer][player].b5 != 0;
    case 11:
        return _CB.err[_CB.errPlayer][player].b4 != 0;
    case 12:
        return _CB.err[_CB.errPlayer][player].b3 != 0;
    case 13:
        return _CB.err[_CB.errPlayer][player].b2 != 0;
    case 14:
        return _CB.err[_CB.errPlayer][player].b1 != 0;
    case -1:
        return *(u32*)&_CB.err[_CB.errPlayer][player] != 0;
    }
    return 1;
}

void menuCB_Pokemon_ErrorDisp(void* src, s8 player) {
    void* cur;
    void* backup;
    _CB.errPlayer = player;
    menuCBPokemonEntryPokemonFaceFree();
    menuCBBattleStartSetStatus(0);
    backup = (u8*)&_CB + 0x9CE4;
    cur = (u8*)&_CB + player * 0x1320 + 0x9BC;
    heroBiosCopy(backup, cur);
    heroBiosCopy(cur, src);
    menuCBPokemonEntryLoadTex();
    menuCBpokemonFaceReadWait();
    CB32(0xB088) = 0;
    CB32(0xB008) = 0;
    _menuCB_ErrorTAMAGOCheck();
    CB32(0xB0DC) = 5;
    if (!_menuCBPokemon_ErrorDispSet(5)) {
        CB32(0xB0DC) = 4;
    }
    if (!_menuCBPokemon_ErrorDispSet(4)) {
        CB32(0xB0DC) = 3;
    }
    if (!_menuCBPokemon_ErrorDispSet(3)) {
        CB32(0xB0DC) = 2;
    }
    if (!_menuCBPokemon_ErrorDispSet(2)) {
        CB32(0xB0DC) = 1;
    }
    if (!_menuCBPokemon_ErrorDispSet(1)) {
        CB32(0xB0DC) = 0;
    }
    if (!_menuCBPokemon_ErrorDispSet(0)) {
        CB32(0xB0DC) = -1;
    }
    menuCB_SE_Play(0x14);
    for (;;) {
        menuOpen(0xA6, 1);
        if (CB32(0xB008) == 6 || CB32(0xB088) == 1) {
            break;
        }
        CB32(0xB08C) = 0;
        CB32(0xB00C) = 0;
        for (;;) {
            menuOpenCustom(0xA7, windowGetActiveID(), &CB32(0xB00C), 0, 1, 0);
            if (CB32(0xB00C) == _CB.unkB0E4 || CB32(0xB08C) == 1) {
                break;
            }
            _menuCB_errorMsgDisp(err_msgID2[CB32(0xB00C)]);
        }
        menuCloseCustom(0xA7, 0, 1);
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xA6, 0, 1);
    menuCBPokemonEntryPokemonFaceFree();
    heroBiosCopy(cur, backup);
}

void menuCBtrainerFaceReadWait() {
    for (;;) {
        if (_menuCBBattleStartWork.a == _menuCBBattleStartWork.b) {
            break;
        }
        GSthreadSwitch();
    }
}

void menuCBpokemonFaceReadWait() {
    for (;;) {
        if (menuCBPokemonEntryGetReadFlag()) {
            break;
        }
        GSthreadSwitch();
    }
}

void toobattle_drawHeroName2(CBWin* win, CBItem* item, s32 player) {
    void* hero = (u8*)&_CB + player * 0x1320 + 0x9BC;
    switch (pokecoloGetCountryCode()) {
    case 0:
        _drawStrings(win, heroBiosGetNamePtr(hero), 0, 0, fn_8007E634(0x4276));
        break;
    case 1:
    case 2:
        fn_8007F43C(win, item, heroBiosGetNamePtr(hero), 0, 0, fn_8007E634(0x4276));
        break;
    }
}

void toobattle_drawHeroNames(CBWin* win, s32 player) {
    _drawStrings(win, heroBiosGetNamePtr((u8*)&_CB + player * 0x1320 + 0x9BC), 0, 0, fn_8007E634(0x4278));
}

void toobattle_drawHeroName(CBWin* win, s32 player) {
    _drawStrings(win, heroBiosGetNamePtr((u8*)&_CB + player * 0x1320 + 0x563C), 0, 0, fn_8007E634(0x4276));
}

#pragma push
#pragma optimization_level 2
void toolbattle_drawHeroID(CBWin* win, s32 player) {
    u16 wide[129];
    char str[128];
    u32 rnd = heroBiosGetRnd((u8*)&_CB + player * 0x1320 + 0x563C);
    u8 d0 = rnd % 10;
    u8 d1 = rnd / 10 % 10;
    u8 d2 = rnd / 100 % 10;
    u8 d3 = rnd / 1000 % 10;
    u8 d4 = rnd / 10000 % 10;
    sprintf(str, "%1d%1d%1d%1d%1d", d4, d3, d2, d1, d0);
    GScharMakeFromSJIS(wide, str);
    _drawStrings(win, wide, 0, 0, 0x43C4);
}
#pragma pop

s32 toolbattle_trainerFace(void) {
    void* org = menuCBBios_GetTrainerOrgImmediately();
    switch (menuCBTrainerBios_GetHomePlace(org)) {
    case 0:
        return 0;
    case 1:
        switch (heroBiosGetSexDataId((u8*)org + 0x9A4)) {
        case 0:
            return 3;
        case 1:
            return 4;
        case 2:
            break;
        }
        break;
    case 2:
        switch (heroBiosGetSexDataId((u8*)org + 0x9A4)) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            break;
        }
        break;
    case 3:
        switch (heroBiosGetSexDataId((u8*)org + 0x9A4)) {
        case 0:
            return 5;
        case 1:
            return 6;
        case 2:
            break;
        }
        break;
    }
    return 3;
}

u8 menuCBPokemonGetDataId_NULL(s32 a, s32 b) {
    Pokemon* p;
    if (menuCBBattleStartGetStatus() == 0) {
        p = toolentryTaisenGetPokemonPtr(a, b);
    } else if (toolentryTaisenGetEntryPokemonNum(a) <= b) {
        p = 0;
    } else {
        p = toolentryTaisenGetEntryPokemonPtr(a, b);
    }
    if (p) {
        return pokemonGetStatus(p, 0, 0x6E, 0) != 0;
    }
    return 0;
}

u8 menuCBPokemonGetDataId(s32 a, s32 b) {
    Pokemon* p;
    if (menuCBBattleStartGetStatus() == 0) {
        p = toolentryTaisenGetPokemonPtr(a, b);
    } else if (toolentryTaisenGetEntryPokemonNum(a) <= b) {
        p = 0;
    } else {
        p = toolentryTaisenGetEntryPokemonPtr(a, b);
    }
    if (p) {
        return pokemonCheckValid(p) != 0;
    }
    return 0;
}

u8 menuCBPokemonGetItemDataId(u32 a, u32 b) {
    return pokemonGetSoubiItemDataId(toolentryTaisenGetPokemonPtr(a, b)) != 0;
}
}
