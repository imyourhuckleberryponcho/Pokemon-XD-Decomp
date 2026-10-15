// WIP 121/142. GENERATED from build/scratch/cbx/g*.inc by assemble.py (edit snippets or stop regenerating).
// STATUS: 121/142 functions exact (26.3 KB of 66.4 KB). Needs extra_cflags=["-inline noauto,deferred"]
// (source is written bottom-to-top). Missing (not written yet): menuTool_Rule00_Ctrl, menuTool_tunaideGCEntry00_Ctrl, menuCB_Rule01_Disp,
// menuCB_Rule02_Disp, menuCB_Rule00_Disp, menuCB_Tunaide02_Disp, menuCB_Tunaide01_3_Disp, menuCB_tunaideGCEntry_Disp/00/02/03/04 Disp(+_1),
// menuCB_error00_Disp, menuCB_GBAConnect_Disp. Not exact: tunaide00_Ctrl (1 dead 'b'), tunaidePokemonSelect1_Ctrl (reg), Tunaide01_Disp (reg),
// tunaideGCEntry01_Disp_Sub. Data (bss/sdata/jump tables) layout still differs until all functions exist.
// Colosseum-battle menu "tool" callbacks (menuTool_*_Ctrl/Button, menuCB_*_Disp).
#include <dolphin/types.h>

// Menu files were built without the peephole optimizer.
#pragma peephole off
#pragma pool_strings off

struct tagWINDOW_WORK {
    u8 used;
    s8 state;
    s8 seqSet;
    u8 pad3;
    s32 seq;
    u8 pad8[0x14];
    void* sprites;
    u8 pad20[0x6C];
    s16 value;
    u8 pad8E[5];
    u8 alpha;
    u8 pad94[0xA];
    s16 select;
    u8 padA0[4];
    u8 done;
    u8 cancel;
};

struct tagSPRITE_WORK {
    u8 pad0[6];
    s16 id;
    u8 pad8[0x44];
    u32 msg;
    s16 unk50;
    s16 unk52;
    s16 x;
    s16 y;
    u8 pad58[0xC];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

struct KeyInfo {
    u16 on;
    u16 up;
    u16 trg;
    u16 rep;
    u16 rel;
    u8 pad_a[0x10];
};

struct RuleData {
    u8 f00;
    u8 f01;
    u8 f02;
    u8 f03;
    u8 f04;
    u8 f05;
    u8 f06;
    u8 f07;
    u8 f08;
    u8 f09;
    u8 f0A;
    u8 f0B;
    u8 f0C;
    u8 f0D;
    u8 f0E;
    u8 f0F;
    u8 f10;
    u8 f11;
    u8 f12;
    u8 f13;
    u8 f14;
    u8 f15;
    u8 f16;
    u8 f17;
    u8 f18;
    u8 f19;
    u8 f1A;
    u8 f1B;
    u8 f1C;
    u8 f1D;
    u8 f1E;
    u8 f1F;
    u8 f20;
    u8 f21;
    u8 f22;
    u8 f23;
    u8 f24;
    u8 f25;
    u8 f26;
    u8 f27;
};

struct GCBEntry {
    s16 value;
    s16 flag;
    u8 pad4[0x8C];
};

struct GCB {
    u8 pad0[0xC];
    s32 cur;
    u8 pad10[0x9922];
    GCBEntry entries[4];
};

struct CBTrainer {
    u16 id;
    u16 face;
    u8 pad4[0x131C];
};

struct CB {
    u8 pad0[0x4];
    s32 unk4;
    s32 unk8;
    u8 padC[0x4];
    s32 unk10;
    u8 pad14[0x4];
    CBTrainer trainers[4];
    u8 pad4C98[0x4FE0];
    RuleData* unk9C78;
    u8 pad9C7C[0x1358];
    s32 unkAFD4;
    s32 unkAFD8;
    s32 unkAFDC;
    s32 unkAFE0;
    s32 unkAFE4;
    u8 padAFE8[0x4];
    s32 unkAFEC;
    u8 padAFF0[0x4];
    s32 unkAFF4;
    s32 unkAFF8;
    s32 unkAFFC;
    s32 unkB000;
    s32 unkB004;
    s32 unkB008;
    s32 unkB00C;
    u8 padB010[0x4];
    s32 unkB014;
    s32 unkB018;
    s32 unkB01C;
    s32 unkB020;
    s32 unkB024;
    s32 unkB028;
    s32 unkB02C;
    s32 unkB030;
    s32 unkB034;
    u8 padB038[0x1C];
    s32 unkB054;
    s32 unkB058;
    s32 unkB05C;
    s32 unkB060;
    s32 unkB064;
    s32 unkB068;
    s32 unkB06C;
    u8 padB070[0x4];
    s32 unkB074;
    s32 unkB078;
    s32 unkB07C;
    u8 padB080[0x4];
    s32 unkB084;
    s32 unkB088;
    s32 unkB08C;
    u8 padB090[0x44];
    s32 unkB0D4;
    s32 unkB0D8;
    s32 unkB0DC;
    s32 unkB0E0;
    s32 unkB0E4;
    s32 unkB0E8;
    s32 unkB0EC;
    s32 unkB0F0;
    s32 unkB0F4;
    s32 unkB0F8;
    s32 unkB0FC;
    u8 padB100[0x4];
    s32 unkB104;
    s32 unkB108;
    s32 unkB10C;
    s32 unkB110;
    s32 unkB114;
    s32 unkB118;
    s32 unkB11C;
    u8 padB120[0x4];
    s32 unkB124;
    s32 unkB128;
    s32 unkB12C;
    s32 unkB130;
    s32 unkB134;
    u8 padB138[0x4];
    s32 unkB13C;
    s32 unkB140;
    s32 unkB144;
    s32 unkB148;
    s32 unkB14C;
    s32 unkB150;
    s32 unkB154;
    s32 unkB158;
    s32 unkB15C;
    u8 padB160[0x8];
    s32 unkB168;
    s32 unkB16C;
    s32 unkB170;
    s32 unkB174;
    s32 unkB178;
    u8 padB17C[0x18];
    s32 unkB194;
    s32 unkB198;
    s32 unkB19C;
    s32 unkB1A0;
    u8 padB1A4[0x30];
    s32 unkB1D4;
    s32 unkB1D8;
    s32 unkB1DC;
    s32 unkB1E0;
};

extern "C" {
extern CB _CB;
extern GCB* pGCB;

void menuCB_SE_Play(s32);
void menuCB_DispEffect(tagWINDOW_WORK*);
void menuSetStatus(s32, s32);
bool pauseIsPause(void);
KeyInfo* windowGetKeyInfo(void);
KeyInfo* windowGetKeyInfo2(void);
u16 windowGetKeyRepeat(void);
void menuCB_AlphaGet(tagWINDOW_WORK*);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
void menuCB_SpriteDispCheckONorOFF(tagSPRITE_WORK*, bool);
void menuCB_Cursol_Disp_AlphaSet(tagWINDOW_WORK*, tagSPRITE_WORK*, bool);
void GSmsgPrint2(void*, s32, s32, u32, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void menuSubDrawCursorBackAnimeOnOffAuto(tagWINDOW_WORK*, s32, s32, s32, s32, s32, u8, s32);
void menuCBPokemonEntryPokemonFaceFree(void);
bool GSinputIsConnected(s32);
void menuCBPokemonEntryDispPokemonFace_AFTER(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32);
void menuCBPokemonEntryDispPokemonFace_BEFORE(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32);
void toobattle_drawHeroName2(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
void menuCBBattleBABatuMark(tagSPRITE_WORK*, s32, s32);
void menuCBBattleStartDispTrainerFaceSub(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
void menuCB_BattleBA_FacePanelSet(tagSPRITE_WORK*, s32, s32);
void menuCB_BattleBA_HPBarDispSet(tagSPRITE_WORK*, s32, s32);
void menuCB_PrintXP(tagSPRITE_WORK*, s32);
void menuCB_Trainer_Error_Disp(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32);
void menuCB_RuleMessageTblDisp(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
void toobattle_drawHeroName(tagWINDOW_WORK*, s32);
void menuCB_RuleItemFlagDisp(tagWINDOW_WORK*);
void menuCB_RuleItemNameEntry(tagWINDOW_WORK*);
void menuCBMessageCenterDisp(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
void menuCBMessageYCenterDisp(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
void menuCB_RuleDispColorChenge(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
void menuCB_RuleDispColorChenge_flag(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
void menuCBRULE_EditNameDisp(s32);
bool menuCB_GCStatusDispMode(tagSPRITE_WORK*, s32);
void menuCBPokemonEntryDisp(tagSPRITE_WORK*);
void menuCBPokemonEntryGCControlDisp(tagSPRITE_WORK*, s32);
void menuCBPokemonWazaTYPE(tagWINDOW_WORK*, s32, s32, s32);
void menuCBPokemonTYPE1(tagWINDOW_WORK*, s32, s32);
void menuCBPokemonTYPE2(tagWINDOW_WORK*, s32, s32);
void menuCBPokemonStatusDisp(tagWINDOW_WORK*, s32, s32, s32, s32);
void menuCBPokemonWazaNAME(tagWINDOW_WORK*, s32, s32, s32);
void menuCBPokemonTOKUSEI(tagWINDOW_WORK*, s32, s32);
void menuCBPokemonName(tagWINDOW_WORK*, s32, s32, s32);
void menuCB_BattleEntryPokemonSelectDisp(tagSPRITE_WORK*, u32, s32);
void menuCBPokemonEntryDispPokemonFace(tagWINDOW_WORK*, tagSPRITE_WORK*, u32, s32);
void menuCBPokemonEntryBallAnaDisp(tagSPRITE_WORK*, u32, s32);
void menuCBPokemonEntryBallDisp(tagSPRITE_WORK*, u32, s32);
bool menuCBPokemonGetItemDataId(u32, s32);
void menuCBPokemonSexOnly(tagWINDOW_WORK*, u32, s32, s32);
void menuCBPokemonNameOnly(tagWINDOW_WORK*, u32, s32, s32);
void toobattle_drawHeroNames(tagWINDOW_WORK*, u32);
void* menuSpriteBiosGetPtr(s32);
void menuCB_SetSprite(tagSPRITE_WORK*, void*);
void menuCB2DPokemonItemDisp(tagSPRITE_WORK*, u32, s32);
void menuCBPokemonName_nido(tagWINDOW_WORK*, u32, s32, s32);
void menuCBPokemonNameOrg(tagWINDOW_WORK*, u32, s32, s32);
void menuCBPokemonHP(tagWINDOW_WORK*, u32, s32, s32);
void menuCBPokemonLevel(tagWINDOW_WORK*, u32, s32, s32);
void menuCBPokemonItemName(tagWINDOW_WORK*, u32, s32, s32);
void FlashSystemSetPlayFrameLabel(u32, const char*, const char*);
void FlashSystemSetNowFrameLabel(u32, const char*);
void FlashSystemSetLoopFlag(u32, bool);
s32 pokecoloGetCountryCode(void);
u32 GSmsgGetRect(s32);
void menuCBGCEntryTypeIndex(void);
bool menuCBPokemonCheck(u32, s32);
void msgctrlSetValue(s32, s32);
KeyInfo* windowGetPortKeyInfo(s32);
s32 toolentryTaisenGetControlerType(s32);
void menuItemBiosSetSelectFlag(s32, s32, s32);
bool gbaCommandIsConnected(s32);
u32 toolbattle_trainerFace(s32);
bool toolBattle_tunaideMenu02menuTempBuffGet(s32);
void toolBattle_tunaideMenu02menuTempBuffSet(s32);
void winSeqSetMenu(s32, s32);
void spriteClearScissor(void*);
void fn_80080390(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
void menuCB_MenuDispCheckONorOFF(tagWINDOW_WORK*, bool);
void menuCB_MenuDispCheckONorOFF_RULE(tagWINDOW_WORK*, s32);
void menuCB_MenuDispCheckONorOFF_TUNAIDESUB(tagWINDOW_WORK*, s32);
s32 menuCB_GetDisconnectedGBA(void);
void menuCBPokemonEntryButtonTask_20041006(void);
s32 menuCBPokemonEntryPokemonNumMin(s32);
s32 toolentryTaisengetEtnryPokemonOrderNum(s32);
u16 toolentryTaisenGetHomePlace(s32);
s32 menuCBBios_ParticipationPokemonMax(void);
u16 toolentryTaisenGetPokemonNum(s32);
u32 GSinputButtonsPressed(s32);
bool menuCBBattleBANextMenu(tagWINDOW_WORK*);
s32 menuCBBattleStartGetStatus(void);
u32 windowSearchID(s32);
}

struct GbaConnectWork {
    s32 state[4];
    u8 pad10[0x18];
    s32 unk28;
    u8 pad2C[0x20];
};
extern "C" GbaConnectWork gbaConectGBA_Connect_WORK;

static s32 tunaide02_last_kakunin_flag;

static void menuCB_RuleCustomMainCursolColorChenge(tagSPRITE_WORK*);
static void _menuCB_Rule_Page_Chenge_Init(void);
static void menuCB_tunaidePokemonSelect1_Disp_Sub(tagWINDOW_WORK*, tagSPRITE_WORK*, u32);
static void menuCB_tunaidePokemonSelect0_Disp_Sub(tagWINDOW_WORK*, tagSPRITE_WORK*, s32);
static void menuCB_tunaideGCEntry01_Disp_Sub(tagWINDOW_WORK*, tagSPRITE_WORK*, u32, u32);

class CAnt {
public:
    static void systemUpdate(bool);
};

//---

static const s32 PlayerNumber[5] = {0x20F, 0x20E, 0x20D, 0x20C, 0x20B};
static const s32 Small_Face_Char[7] = {0x208, 0x209, 0x20A, 0x210, 0x211, 0x212, 0x213};
static const s32 Big_Face_Char[7] = {0x201, 0x202, 0x203, 0x204, 0x205, 0x206, 0x207};
static const s32 PCBOXBG_Char[8] = {0x325, 0x326, 0x327, 0x328, 0x329, 0x32A, 0x32B, 0x32C};
static const s32 BATTLE_FIELD_Char[7] = {0x2A7, 0x2A9, 0x2A8, 0x2A6, 0x2A5, 0x2A4, 0x2D7};
static const s32 MENU_ITEM_TOOL_IMASUGU00_SETUMEI_Tbl[3] = {0x43B8, 0x43B9, 0x4364};
static const s32 MENU_ITEM_TOOL_IMASUGU01_SETUMEI_Tbl[5] = {0x443E, 0x443F, 0x4440, 0x4441, 0x4442};
static const s32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_Tbl[6] = {0x4360, 0x4361, 0x4362, 0x4363, 0x4364, 0x4418};
static const s32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_1_Tbl[4] = {0x436A, 0x436B, 0x436C, 0x436D};
static const s32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_3_Tbl[7] = {0x437D, 0x437E, 0x4380, 0x4382, 0x4383, 0x4384, 0x4385};
static const s32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_4_Tbl[6] = {0x438D, 0x438F, 0x438E, 0x4390, 0x4390, 0x4390};
static const s32 MENU_ITEM_TOOL_TUNAIDE01_SETUMEI_Tbl[4] = {0x4366, 0x4367, 0x4368, 0x4369};
static const s32 MENU_ITEM_TOOL_TUNAIDE01_FIELD_A_Tbl[7] = {0x4374, 0x4375, 0x4377, 0x4379, 0x437A, 0x437B, 0x437C};
static const s32 MENU_ITEM_TOOL_TUNAIDE01_RULE_A_Tbl[3] = {0x4387, 0x4389, 0x4388};
static const s32 MENU_ITEM_TOOL_SANKA00_RELIVE_TITLE_Tbl[9] = {0x43EC, 0x43ED, 0x43EE, 0x43EF, 0x43F0, 0x43F1, 0x43F2, 0x43F3, 0x43F4};
static const s32 _error01_cursol_item_tbl[14] = {0x4DD, 0x4DE, 0x4DF, 0x4E0, 0x4E1, 0x4E2, 0x4E3, 0x4E4, 0x4E5, 0x4E6, 0x4E7, 0x4E8, 0x4E9, 0x4EA};
static const s32 GCEntryStatusDispPosition[38] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2};
static const s32 Port_Icon_Char[2] = {0x3C8, 0x3C9};
static const s32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_2_Tbl[2] = {0x4371, 0x4372};
static const s32 MENU_ITEM_TOOL_TUNAIDE01_BATTLE_A_Tbl[2] = {0x436F, 0x4370};


extern "C" {
void menuTool_imasugu00_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_AlphaGet(window);
}
}

extern "C" {
void menuTool_imasugu00_Button(tagWINDOW_WORK* window) {
    if (!pauseIsPause()) {
        if (windowGetKeyInfo()->trg & 0x10) {
            if (_CB.unkAFD4 == 2) {
                _CB.unkB054 = 1;
            }
            window->done = 1;
            menuCB_SE_Play(0x11);
            return;
        }
        if (windowGetKeyInfo()->trg & 0x20) {
            window->done = 1;
            _CB.unkB054 = 1;
            menuCB_SE_Play(0x12);
            return;
        }
        if (windowGetKeyRepeat() & 1) {
            if (_CB.unkAFD4 == 0) {
                _CB.unkAFD4 = 2;
            } else {
                _CB.unkAFD4--;
            }
            menuCB_SE_Play(0x10);
            return;
        }
        if (windowGetKeyRepeat() & 2) {
            if (_CB.unkAFD4 == 2) {
                _CB.unkAFD4 = 0;
            } else {
                _CB.unkAFD4++;
            }
            menuCB_SE_Play(0x10);
            return;
        }
        if ((windowGetKeyInfo()->trg | windowGetKeyInfo2()->trg) & 0xC) {
            switch (_CB.unkAFD4) {
            case 0:
                _CB.unkAFD4 = 2;
                break;
            case 1:
                _CB.unkAFD4 = 2;
                break;
            case 2:
                _CB.unkAFD4 = 0;
                break;
            }
            menuCB_SE_Play(0x10);
        }
    }
}
}

static void _menuCB_imasugu00_disp_sub_color(tagSPRITE_WORK* sprite, u8 color) {
    if (windowSearchID(0x106)) {
        sprite->b = color;
        sprite->g = color;
        sprite->r = color;
        return;
    }
    sprite->b = 0xFF;
    sprite->g = 0xFF;
    sprite->r = 0xFF;
}

static void _menuCB_imasugu00_disp_sub(tagSPRITE_WORK* sprite, s8 index, u8 color) {
    if (_CB.unkAFD4 == index) {
        winSpriteSetDisp(sprite, 1);
        _menuCB_imasugu00_disp_sub_color(sprite, color);
        return;
    }
    winSpriteSetDisp(sprite, 0);
}

static void _menuCB_imasugu00_disp_sub1(tagSPRITE_WORK* sprite, s8 index) {
    _menuCB_imasugu00_disp_sub(sprite, index, 0x7F);
}

static void _menuCB_imasugu00_disp_sub2(tagSPRITE_WORK* sprite, s8 index) {
    _menuCB_imasugu00_disp_sub(sprite, index, 0xFF);
}

static void _menuCB_imasugu00_disp_sub3(tagSPRITE_WORK* sprite, s8 index) {
    if (_CB.unkAFD4 != index) {
        _menuCB_imasugu00_disp_sub_color(sprite, 0x7F);
    }
}

extern "C" {
void menuCB_Imasugu00_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x64E:
    case 0x64F:
    case 0x650:
    case 0x651:
    case 0x652:
    case 0x653:
    case 0x654:
        _menuCB_imasugu00_disp_sub3(sprite, 0);
        break;
    case 0x65C:
    case 0x65D:
    case 0x65E:
    case 0x65F:
    case 0x660:
        _menuCB_imasugu00_disp_sub2(sprite, 0);
        break;
    case 0x666:
    case 0x667:
    case 0x668:
        _menuCB_imasugu00_disp_sub1(sprite, 0);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, windowSearchID(0x106) == 0);
        break;
    case 0x655:
    case 0x656:
    case 0x657:
    case 0x658:
    case 0x659:
    case 0x65A:
    case 0x65B:
        _menuCB_imasugu00_disp_sub3(sprite, 1);
        break;
    case 0x661:
    case 0x662:
    case 0x663:
    case 0x664:
    case 0x665:
        _menuCB_imasugu00_disp_sub2(sprite, 1);
        break;
    case 0x669:
    case 0x66A:
    case 0x66B:
        _menuCB_imasugu00_disp_sub1(sprite, 1);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, windowSearchID(0x106) == 0);
        break;
    case 0x671:
        sprite->msg = 0x43B4;
        break;
    case 0x673:
        if (windowSearchID(0x106)) {
            sprite->msg = 0x43BA;
        } else {
            sprite->msg = 0x43B5;
        }
        break;
    case 0x674:
        sprite->msg = 0x43B6;
        _menuCB_imasugu00_disp_sub3(sprite, 0);
        break;
    case 0x675:
        sprite->msg = 0x43B7;
        _menuCB_imasugu00_disp_sub3(sprite, 1);
        break;
    case 0x672:
        if (windowSearchID(0x106)) {
            sprite->msg = MENU_ITEM_TOOL_IMASUGU01_SETUMEI_Tbl[_CB.unkAFD8];
        } else {
            sprite->msg = MENU_ITEM_TOOL_IMASUGU00_SETUMEI_Tbl[_CB.unkAFD4];
        }
        break;
    case 0x676:
        if (windowSearchID(0x106)) {
            winSpriteSetDisp(sprite, 0);
        } else {
            winSpriteSetDisp(sprite, 1);
        }
        break;
    case 0x677:
        if (windowSearchID(0x106)) {
            winSpriteSetDisp(sprite, 0);
        } else {
            _menuCB_imasugu00_disp_sub1(sprite, 2);
            menuCB_Cursol_Disp_AlphaSet(window, sprite, true);
        }
        break;
    case 0x678:
        if (windowSearchID(0x106)) {
            winSpriteSetDisp(sprite, 0);
        } else {
            winSpriteSetDisp(sprite, 1);
            fn_80080390(window, sprite, 0x435E);
        }
        break;
    case 0x66D:
        _menuCB_imasugu00_disp_sub3(sprite, 0);
        break;
    case 0x66C:
        _menuCB_imasugu00_disp_sub3(sprite, 1);
        break;
    }
}
}

extern "C" {
void menuTool_imasugu01_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
}
}

extern "C" {
void menuTool_imasugu01_Button(tagWINDOW_WORK* window) {
    _CB.unkAFD8 = window->select;
    if (!pauseIsPause()) {
        if (windowGetKeyInfo()->trg & 0x10) {
            window->done = 1;
            menuCBPokemonEntryPokemonFaceFree();
            if (_CB.unkAFD4 == 1) {
                if (GSinputIsConnected(2)) {
                    _CB.unkB0E0 = 2;
                    return;
                }
                _CB.unkB0E0 = 1;
                return;
            }
            _CB.unkB0E0 = 0;
            return;
        }
        if (windowGetKeyInfo()->trg & 0x20) {
            window->done = 1;
            window->cancel = 1;
            _CB.unkB058 = 1;
        }
    }
}
}

extern "C" {
void menuCB_Imasugu01_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x537:
        sprite->msg = 0;
        GSmsgPrint2(window->sprites, 0, 0, window->alpha | 0xFFFFFF00, 0x43BB);
        GSmsgPrint2(window->sprites, 0, 0x25, window->alpha | 0xFFFFFF00, 0x43BC);
        GSmsgPrint2(window->sprites, 0, 0x4A, window->alpha | 0xFFFFFF00, 0x43BD);
        GSmsgPrint2(window->sprites, 0, 0x6F, window->alpha | 0xFFFFFF00, 0x43BE);
        GSmsgPrint2(window->sprites, 0, 0x94, window->alpha | 0xFFFFFF00, 0x43BF);
        return;
    case 0x531: {
        winSpriteSetDisp(sprite, 0);
        s16 sel = window->select;
        if (sel >= 0) {
            menuSubDrawCursorBackAnimeOnOffAuto(window, winSpriteGetLayerID(window, sprite), 0, sel * 0x25, sprite->x, sprite->y,
                                                window->alpha, 1);
        }
        return;
    }
    }
}
}

extern "C" {
void menuTool_imasugu02_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
}
}

extern "C" {
void menuTool_imasugu02_Button(tagWINDOW_WORK* window) {
    _CB.unkAFDC = window->select;
    if (!pauseIsPause()) {
        if (windowGetKeyInfo()->trg & 0x10) {
            window->done = 1;
            return;
        }
        if (windowGetKeyInfo()->trg & 0x20) {
            window->done = 1;
            window->cancel = 1;
            _CB.unkB05C = 1;
        }
    }
}
}

extern "C" {
void menuCB_Imasugu02_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x512:
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkAFD4 != 0));
        break;
    case 0x511:
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkAFD4 == 0));
        break;
    case 0x529:
        sprite->msg = 0x43b4;
        break;
    case 0x527:
        sprite->msg = 0x426c;
        break;
    case 0x526:
        sprite->msg = 0x426d;
        break;
    case 0x528:
        sprite->msg = 0x43c0;
        break;
    case 0x4FC:
        menuCBPokemonEntryDispPokemonFace(window, sprite, 0x0, 0x0);
        break;
    case 0x4FD:
        menuCBPokemonEntryDispPokemonFace(window, sprite, 0x0, 0x1);
        break;
    case 0x4FE:
        menuCBPokemonEntryDispPokemonFace(window, sprite, 0x1, 0x0);
        break;
    case 0x4FF:
        menuCBPokemonEntryDispPokemonFace(window, sprite, 0x1, 0x1);
        break;
    case 0x516:
        menuCBPokemonName(window, 0x0, 0x0, 0x1);
        break;
    case 0x517:
        menuCBPokemonLevel(window, 0x0, 0x0, 0x1);
        break;
    case 0x518:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(0x0, 0x0));
        break;
    case 0x519:
        menuCBPokemonHP(window, 0x0, 0x0, 0x1);
        break;
    case 0x51A:
        menuCBPokemonName(window, 0x0, 0x1, 0x1);
        break;
    case 0x51B:
        menuCBPokemonLevel(window, 0x0, 0x1, 0x1);
        break;
    case 0x51C:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(0x0, 0x1));
        break;
    case 0x51D:
        menuCBPokemonHP(window, 0x0, 0x1, 0x1);
        break;
    case 0x51E:
        menuCBPokemonName(window, 0x1, 0x0, 0x1);
        break;
    case 0x51F:
        menuCBPokemonLevel(window, 0x1, 0x0, 0x1);
        break;
    case 0x520:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(0x1, 0x0));
        break;
    case 0x521:
        menuCBPokemonHP(window, 0x1, 0x0, 0x1);
        break;
    case 0x522:
        menuCBPokemonName(window, 0x1, 0x1, 0x1);
        break;
    case 0x523:
        menuCBPokemonLevel(window, 0x1, 0x1, 0x1);
        break;
    case 0x524:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(0x1, 0x1));
        break;
    case 0x525:
        menuCBPokemonHP(window, 0x1, 0x1, 0x1);
        break;
    case 0x513: {
        winSpriteSetDisp(sprite, 0);
        s16 sel = window->select;
        if (sel >= 0) {
            menuSubDrawCursorBackAnimeOnOffAuto(window, winSpriteGetLayerID(window, sprite), 0, sel * 0x25, sprite->x, sprite->y,
                                                window->alpha, 0);
        }
        break;
    }
    }
}
}

static void _menuCB_TunaideSub_Page_Chenge_Init(void) {
    _CB.unkB144 = _CB.unkAFE4;
    _CB.unkB148 = 0xFF;
    _CB.unkB14C = 0xF;
    menuCB_SE_Play(0x10);
}

extern "C" {
void menuTool_tunaide00_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    if (_CB.unkB114 == 0 && _CB.unkB10C < 2 && !pauseIsPause()) {
        if (_CB.unkB144 != -1) {
            if (_CB.unkB14C == 0xFF) {
                _CB.unkB144 = -1;
            } else {
                _CB.unkB148 -= 0x28;
                _CB.unkB14C += 0x28;
                if (_CB.unkB14C >= 0xFF) {
                    _CB.unkB14C = 0xFF;
                    _CB.unkB148 = 0xF;
                }
                return;
            }
        }
        if (_CB.unkB10C == 1) {
            switch (_CB.unkAFE4) {
            case 0:
                if (windowGetKeyRepeat() & 1) {
                    if (_CB.unkAFF4 != 0) {
                        _CB.unkAFF4--;
                    } else {
                        _CB.unkAFF4 = 3;
                    }
                    menuCB_SE_Play(0x10);
                } else if (windowGetKeyRepeat() & 2) {
                    if (_CB.unkAFF4 != 3) {
                        _CB.unkAFF4++;
                    } else {
                        _CB.unkAFF4 = 0;
                    }
                    menuCB_SE_Play(0x10);
                }
                break;
            case 1:
                if (windowGetKeyRepeat() & 3) {
                    _CB.unkAFF8 ^= 1;
                    menuCB_SE_Play(0x10);
                }
                break;
            case 2:
                if (windowGetKeyRepeat() & 1) {
                    _CB.unkB000 = _CB.unkAFFC;
                    if (_CB.unkAFFC != 0) {
                        _CB.unkAFFC--;
                    }
                    if (_CB.unkB000 != _CB.unkAFFC) {
                        _CB.unkB114 = 1;
                        menuCB_SE_Play(0x10);
                    }
                }
                if ((windowGetKeyRepeat() & 2) && _CB.unkB114 == 0) {
                    _CB.unkB000 = _CB.unkAFFC;
                    if (_CB.unkAFFC != 6) {
                        _CB.unkAFFC++;
                    }
                    if (_CB.unkB000 != _CB.unkAFFC) {
                        _CB.unkB114 = 3;
                        menuCB_SE_Play(0x10);
                    }
                }
                break;
            case 3:
                if (windowGetKeyRepeat() & 1) {
                    if (_CB.unkB004 != 0) {
                        _CB.unkB004--;
                    } else {
                        _CB.unkB004 = 5;
                    }
                    menuCB_SE_Play(0x10);
                } else if (windowGetKeyRepeat() & 2) {
                    if (_CB.unkB004 != 5) {
                        _CB.unkB004++;
                    } else {
                        _CB.unkB004 = 0;
                    }
                    menuCB_SE_Play(0x10);
                }
                break;
            }
            if (windowGetKeyInfo()->trg & 0x10) {
                menuCB_SE_Play(0x11);
                if (_CB.unkAFE4 == 3) {
                    _CB.unkB10C = 2;
                    return;
                }
                _CB.unkB10C = 0;
                return;
            }
            if (windowGetKeyInfo()->trg & 0x20) {
                menuCB_SE_Play(0x12);
                switch (_CB.unkAFE4) {
                case 0:
                    _CB.unkAFF4 = _CB.unkB074;
                    break;
                case 1:
                    _CB.unkAFF8 = _CB.unkB078;
                    break;
                case 2:
                    _CB.unkAFFC = _CB.unkB07C;
                    break;
                case 3:
                    _CB.unkB004 = _CB.unkB084;
                    break;
                }
                _CB.unkB10C = 0;
            }
            return;
        } else if (_CB.unkB064 == 0) {
            if (windowGetKeyInfo()->trg & 0x20) {
                menuCB_SE_Play(0x12);
                _CB.unkB064 = 2;
                return;
            }
            if (windowGetKeyInfo()->trg & 0x10) {
                menuCB_SE_Play(0x11);
                if (_CB.unkAFE4 == 4) {
                    _CB.unkB064 = 2;
                    return;
                }
                if (_CB.unkAFE4 == 5) {
                    _CB.unkB064 = 1;
                    return;
                }
                switch (_CB.unkAFE4) {
                case 0:
                    _CB.unkB074 = _CB.unkAFF4;
                    break;
                case 1:
                    _CB.unkB078 = _CB.unkAFF8;
                    break;
                case 2:
                    _CB.unkB07C = _CB.unkAFFC;
                    break;
                case 3:
                    _CB.unkB084 = _CB.unkB004;
                    break;
                }
                _CB.unkB10C = 1;
                return;
            } else if (windowGetKeyRepeat() & 1) {
                _menuCB_TunaideSub_Page_Chenge_Init();
                if (_CB.unkAFE4 == 0) {
                    _CB.unkAFE4 = 5;
                } else {
                    _CB.unkAFE4--;
                }
                if (_CB.unkAFE4 == 1 && _CB.unkAFF4 >= 2) {
                    _CB.unkAFE4 = 0;
                }
            } else if (windowGetKeyRepeat() & 2) {
                _menuCB_TunaideSub_Page_Chenge_Init();
                if (_CB.unkAFE4 == 5) {
                    _CB.unkAFE4 = 0;
                } else {
                    _CB.unkAFE4++;
                }
                if (_CB.unkAFE4 == 1 && _CB.unkAFF4 >= 2) {
                    _CB.unkAFE4 = 2;
                }
            } else if (windowGetKeyRepeat() & 8) {
                _menuCB_TunaideSub_Page_Chenge_Init();
                switch (_CB.unkAFE4) {
                case 0:
                case 1:
                case 2:
                case 3:
                    _CB.unkAFE4 = 4;
                    break;
                case 4:
                    _CB.unkAFE4 = 5;
                    break;
                case 5:
                    _CB.unkAFE4 = 0;
                    break;
                }
            } else if (windowGetKeyRepeat() & 4) {
                _menuCB_TunaideSub_Page_Chenge_Init();
                switch (_CB.unkAFE4) {
                case 0:
                case 1:
                case 2:
                case 3:
                    _CB.unkAFE4 = 5;
                    break;
                case 4:
                    _CB.unkAFE4 = 0;
                    break;
                case 5:
                    _CB.unkAFE4 = 4;
                    break;
                }
            }
        }
    }
}
}

extern "C" {
void menuTool_tunaide00_Button(void) {
}
}

extern "C" {
void menuCB_Tunaide00_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x41:
        sprite->msg = 0x435C;
        return;
    case 0x3F:
        sprite->msg = 0x435D;
        return;
    case 0x40:
        if (_CB.unkB10C == 0) {
            sprite->msg = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_Tbl[_CB.unkAFE4];
            return;
        }
        switch (_CB.unkAFE4) {
        case 0:
            sprite->msg = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_1_Tbl[_CB.unkAFF4];
            return;
        case 1:
            sprite->msg = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_2_Tbl[_CB.unkAFF8];
            return;
        case 2:
            sprite->msg = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_3_Tbl[_CB.unkAFFC];
            return;
        case 3:
            sprite->msg = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_4_Tbl[_CB.unkB004];
            return;
        }
        break;
    }
}
}

extern "C" {
void menuTool_tunaide01_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    CAnt::systemUpdate(true);
    menuCB_AlphaGet(window);
}
}

extern "C" {
void menuTool_tunaide01_Button(void) {
}
}

static void _menuCB_tunaide01_disp_sub_color(tagSPRITE_WORK* sprite, u8 color) {
    if (_CB.unkB10C != 0) {
        sprite->b = color;
        sprite->g = color;
        sprite->r = color;
        return;
    }
    sprite->b = 0xFF;
    sprite->g = 0xFF;
    sprite->r = 0xFF;
}

static void _menuCB_tunaide01_disp_sub_color2(tagSPRITE_WORK* sprite, bool flag) {
    if (_CB.unkB10C != 1 && !flag) {
        sprite->b = 0x7F;
        sprite->g = 0x7F;
        sprite->r = 0x7F;
        return;
    }
    sprite->b = 0xFF;
    sprite->g = 0xFF;
    sprite->r = 0xFF;
}

static void _menuCB_tunaide01_disp_sub(tagSPRITE_WORK* sprite, s8 index, u8 color) {
    if (_CB.unkAFE4 == index) {
        winSpriteSetDisp(sprite, 1);
        _menuCB_tunaide01_disp_sub_color(sprite, color);
        return;
    }
    winSpriteSetDisp(sprite, 0);
}

static void _menuCB_tunaide01_disp_sub1(tagSPRITE_WORK* sprite, s8 index) {
    _menuCB_tunaide01_disp_sub(sprite, index, 0xFF);
}

static void _menuCB_tunaide01_disp_sub2(tagSPRITE_WORK* sprite, s8 index) {
    _menuCB_tunaide01_disp_sub(sprite, index, 0xFF);
}

static void _menuCB_tunaide01_disp_sub3(tagSPRITE_WORK* sprite, s8 index) {
    if (_CB.unkAFE4 != index) {
        _menuCB_tunaide01_disp_sub_color(sprite, 0x7F);
    }
}

extern "C" {
void menuCB_Tunaide01_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
        _menuCB_tunaide01_disp_sub3(sprite, 0);
        return;
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
        _menuCB_tunaide01_disp_sub2(sprite, 0);
        return;
    case 0x4D:
    case 0x4E:
    case 0x4F:
        _menuCB_tunaide01_disp_sub1(sprite, 0);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkAFE4 == 0 && _CB.unkB10C == 0);
        return;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
        _menuCB_tunaide01_disp_sub3(sprite, 1);
        return;
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5A:
        _menuCB_tunaide01_disp_sub2(sprite, 1);
        return;
    case 0x5B:
    case 0x5C:
    case 0x5D:
        _menuCB_tunaide01_disp_sub1(sprite, 1);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkAFE4 == 1 && _CB.unkB10C == 0);
        return;
    case 0x5E:
    case 0x5F:
    case 0x60:
    case 0x61:
    case 0x62:
    case 0x63:
        _menuCB_tunaide01_disp_sub3(sprite, 2);
        return;
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
        _menuCB_tunaide01_disp_sub2(sprite, 2);
        return;
    case 0x69:
    case 0x6A:
    case 0x6B:
        _menuCB_tunaide01_disp_sub1(sprite, 2);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkAFE4 == 2 && _CB.unkB10C == 0);
        return;
    case 0x6C:
    case 0x6D:
    case 0x6E:
    case 0x6F:
    case 0x70:
    case 0x71:
        _menuCB_tunaide01_disp_sub3(sprite, 3);
        return;
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
        _menuCB_tunaide01_disp_sub2(sprite, 3);
        return;
    case 0x77:
    case 0x78:
    case 0x79:
        _menuCB_tunaide01_disp_sub1(sprite, 3);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkAFE4 == 3 && _CB.unkB10C == 0);
        return;
    case 0x7C:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFE4 == 4);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkAFE4 == 4 && _CB.unkB064 == 0);
        return;
    case 0x7A:
        _menuCB_tunaide01_disp_sub3(sprite, 4);
        return;
    case 0x7D:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFE4 == 5);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkAFE4 == 5 && _CB.unkB064 == 0);
        return;
    case 0x7B:
        _menuCB_tunaide01_disp_sub3(sprite, 5);
        return;
    case 0x7E:
        sprite->msg = 0x4365;
        _menuCB_tunaide01_disp_sub3(sprite, 0);
        return;
    case 0x68B:
        sprite->msg = MENU_ITEM_TOOL_TUNAIDE01_SETUMEI_Tbl[_CB.unkAFF4];
        _menuCB_tunaide01_disp_sub3(sprite, 0);
        return;
    case 0x7F:
        sprite->msg = 0x436E;
        _menuCB_tunaide01_disp_sub3(sprite, 1);
        return;
    case 0x80:
        sprite->msg = MENU_ITEM_TOOL_TUNAIDE01_BATTLE_A_Tbl[_CB.unkAFF8];
        if (_CB.unkAFF4 >= 2) {
            sprite->msg = 0x440F;
        }
        _menuCB_tunaide01_disp_sub3(sprite, 1);
        return;
    case 0x81:
        sprite->msg = 0x4373;
        _menuCB_tunaide01_disp_sub3(sprite, 2);
        return;
    case 0x82:
        sprite->msg = MENU_ITEM_TOOL_TUNAIDE01_FIELD_A_Tbl[_CB.unkAFFC];
        _menuCB_tunaide01_disp_sub3(sprite, 2);
        return;
    case 0x83:
        sprite->msg = 0x4386;
        _menuCB_tunaide01_disp_sub3(sprite, 3);
        return;
    case 0x84:
        if (_CB.unkB004 >= 3) {
            sprite->msg = 0;
            menuCBRULE_EditNameDisp(_CB.unkB004);
        } else {
            sprite->msg = MENU_ITEM_TOOL_TUNAIDE01_RULE_A_Tbl[_CB.unkB004];
        }
        _menuCB_tunaide01_disp_sub3(sprite, 3);
        return;
    case 0x85:
        fn_80080390(window, sprite, 0x435E);
        _menuCB_tunaide01_disp_sub3(sprite, 4);
        return;
    case 0x86:
        fn_80080390(window, sprite, 0x435F);
        _menuCB_tunaide01_disp_sub3(sprite, 5);
        return;
    }
}
}

extern "C" {
void menuTool_tunaide_back_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
}
}

extern "C" {
void menuTool_tunaide01_1_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF_TUNAIDESUB(window, 0);
}
}

extern "C" {
void menuTool_tunaide01_1_Button(void) {
}
}

extern "C" {
void menuCB_Tunaide01_1_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x3CF:
    case 0x3D0:
    case 0x3D1:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFF4 == 0);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkB10C == 1);
        break;
    case 0x3D2:
    case 0x3D3:
    case 0x3D4:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFF4 == 1);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkB10C == 1);
        break;
    case 0x3D5:
    case 0x3D6:
    case 0x3D7:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFF4 == 2);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkB10C == 1);
        break;
    case 0x3D8:
    case 0x3D9:
    case 0x3DA:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFF4 == 3);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkB10C == 1);
        break;
    case 0x3BF:
    case 0x3CC:
    case 0x3CE:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkAFF4 == 0);
        break;
    case 0x3C0:
    case 0x3C3:
    case 0x3C4:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkAFF4 == 1);
        break;
    case 0x3C1:
    case 0x3C5:
    case 0x3C6:
    case 0x3C7:
    case 0x3CD:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkAFF4 == 2);
        break;
    case 0x3C2:
    case 0x3C8:
    case 0x3C9:
    case 0x3CA:
    case 0x3CB:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkAFF4 == 3);
        break;
    }
}
}

extern "C" {
void menuTool_tunaide01_2_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF_TUNAIDESUB(window, 1);
}
}

extern "C" {
void menuTool_tunaide01_2_Button(void) {
}
}

extern "C" {
void menuCB_Tunaide01_2_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x29A:
    case 0x29B:
    case 0x29C:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFF8 == 0);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkB10C == 1);
        return;
    case 0x29D:
    case 0x29E:
    case 0x29F:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFF8 == 1);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, _CB.unkB10C == 1);
        return;
    case 0x679:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkAFF8 == 0);
        return;
    case 0x2A0:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkAFF8 == 1);
        return;
    }
}
}

extern "C" {
void menuTool_tunaide01_3_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF_TUNAIDESUB(window, 2);
}
}

extern "C" {
void menuTool_tunaide01_3_Button(void) {
}
}

extern "C" {
void menuTool_tunaide01_4_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF_TUNAIDESUB(window, 3);
}
}

extern "C" {
void menuTool_tunaide01_4_Button(void) {
}
}

extern "C" {
void menuCB_Tunaide01_4_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x3DB:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C == 1 && _CB.unkB004 == 0);
        break;
    case 0x3DC:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C == 1 && _CB.unkB004 == 1);
        break;
    case 0x3DD:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C == 1 && _CB.unkB004 == 2);
        break;
    case 0x3DE:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C == 1 && _CB.unkB004 == 3);
        break;
    case 0x3DF:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C == 1 && _CB.unkB004 == 4);
        break;
    case 0x3E0:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C == 1 && _CB.unkB004 == 5);
        break;
    case 0x3E1:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C != 1 && _CB.unkB004 == 0);
        break;
    case 0x3E2:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C != 1 && _CB.unkB004 == 1);
        break;
    case 0x3E3:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C != 1 && _CB.unkB004 == 2);
        break;
    case 0x3E4:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C != 1 && _CB.unkB004 == 3);
        break;
    case 0x3E5:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C != 1 && _CB.unkB004 == 4);
        break;
    case 0x3E6:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB10C != 1 && _CB.unkB004 == 5);
        break;
    case 0x3E7:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkB004 == 0);
        menuCB_RuleMessageTblDisp(window, sprite, 0);
        break;
    case 0x3E8:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkB004 == 1);
        menuCB_RuleMessageTblDisp(window, sprite, 1);
        break;
    case 0x3E9:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkB004 == 2);
        menuCB_RuleMessageTblDisp(window, sprite, 2);
        break;
    case 0x3EA:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkB004 == 3);
        menuCB_RuleMessageTblDisp(window, sprite, 3);
        break;
    case 0x3EB:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkB004 == 4);
        menuCB_RuleMessageTblDisp(window, sprite, 4);
        break;
    case 0x3EC:
        _menuCB_tunaide01_disp_sub_color2(sprite, _CB.unkB004 == 5);
        menuCB_RuleMessageTblDisp(window, sprite, 5);
        break;
    }
}
}

extern "C" {
void menuTool_tunaide02_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    if (menuCB_GetDisconnectedGBA()) {
        _CB.unkB194 = 1;
        window->done = 1;
        window->cancel = 1;
    }
}
}

extern "C" {
void menuTool_tunaide02_Button(tagWINDOW_WORK* window) {
    u8 ports[4] = {1, 2, 4, 8};
    u16 key[4];
    if (_CB.unk8 == 2) {
        for (s32 i = 0; i < 4; i++) {
            key[i] = windowGetPortKeyInfo(ports[toolentryTaisenGetControlerType(i) - 1])->trg;
        }
        if (_CB.unkB0D4 == 0xF) {
            tunaide02_last_kakunin_flag = 1;
            if (key[0] & 0x20) {
                window->done = 1;
                window->cancel = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
                return;
            }
            if (key[0] & 0x800) {
                window->done = 1;
                menuCB_SE_Play(0x11);
            }
        } else {
            tunaide02_last_kakunin_flag = 0;
            if ((key[0] & 0x10) && toolBattle_tunaideMenu02menuTempBuffGet(1) == 0) {
                toolBattle_tunaideMenu02menuTempBuffSet(1);
                menuCB_SE_Play(0x11);
            }
            if ((key[1] & 0x10) && toolBattle_tunaideMenu02menuTempBuffGet(2) == 0) {
                toolBattle_tunaideMenu02menuTempBuffSet(2);
                menuCB_SE_Play(0x11);
            }
            if ((key[2] & 0x10) && toolBattle_tunaideMenu02menuTempBuffGet(4) == 0) {
                toolBattle_tunaideMenu02menuTempBuffSet(4);
                menuCB_SE_Play(0x11);
            }
            if ((key[3] & 0x10) && toolBattle_tunaideMenu02menuTempBuffGet(8) == 0) {
                toolBattle_tunaideMenu02menuTempBuffSet(8);
                menuCB_SE_Play(0x11);
            }
            if ((key[3] | (key[2] | (key[0] | key[1]))) & 0x20) {
                window->done = 1;
                window->cancel = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
            }
        }
    } else if (toolbattle_trainerFace(0)) {
        key[1] = windowGetPortKeyInfo(ports[toolentryTaisenGetControlerType(1) - 1])->trg;
        key[2] = windowGetPortKeyInfo(ports[toolentryTaisenGetControlerType(2) - 1])->trg;
        if (_CB.unkB0D4 == 6) {
            tunaide02_last_kakunin_flag = 2;
            if (key[1] & 0x20) {
                window->done = 1;
                window->cancel = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
                return;
            }
            if (key[1] & 0x800) {
                window->done = 1;
                menuCB_SE_Play(0x11);
            }
        } else {
            tunaide02_last_kakunin_flag = 0;
            if ((key[1] & 0x10) && toolBattle_tunaideMenu02menuTempBuffGet(2) == 0) {
                toolBattle_tunaideMenu02menuTempBuffSet(2);
                menuCB_SE_Play(0x11);
            }
            if ((key[2] & 0x10) && toolBattle_tunaideMenu02menuTempBuffGet(4) == 0) {
                toolBattle_tunaideMenu02menuTempBuffSet(4);
                menuCB_SE_Play(0x11);
            }
            if ((key[1] | key[2]) & 0x20) {
                window->done = 1;
                window->cancel = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
            }
        }
    } else {
        key[0] = windowGetPortKeyInfo(ports[toolentryTaisenGetControlerType(0) - 1])->trg;
        key[1] = windowGetPortKeyInfo(ports[toolentryTaisenGetControlerType(1) - 1])->trg;
        if (_CB.unkB0D4 == 3) {
            tunaide02_last_kakunin_flag = 1;
            if (key[0] & 0x20) {
                window->done = 1;
                window->cancel = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
                return;
            }
            if (key[0] & 0x800) {
                window->done = 1;
                menuCB_SE_Play(0x11);
            }
        } else {
            tunaide02_last_kakunin_flag = 0;
            if ((key[0] & 0x10) && toolBattle_tunaideMenu02menuTempBuffGet(1) == 0) {
                toolBattle_tunaideMenu02menuTempBuffSet(1);
                menuCB_SE_Play(0x11);
            }
            if ((key[1] & 0x10) && toolBattle_tunaideMenu02menuTempBuffGet(2) == 0) {
                toolBattle_tunaideMenu02menuTempBuffSet(2);
                menuCB_SE_Play(0x11);
            }
            if ((key[0] | key[1]) & 0x20) {
                window->done = 1;
                window->cancel = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
            }
        }
    }
}
}

extern "C" {
void menuTool_tunaide03_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    if (menuCB_GetDisconnectedGBA()) {
        _CB.unkB198 = 1;
        window->done = 1;
        window->cancel = 1;
    }
    menuCB_AlphaGet(window);
}
}

extern "C" {
void menuTool_tunaide03_Button(tagWINDOW_WORK* window) {
    if (!pauseIsPause()) {
        if (windowGetKeyInfo()->trg & 0x10) {
            window->done = 1;
            menuCB_SE_Play(0x11);
            return;
        }
        if (windowGetKeyInfo()->trg & 0x20) {
            window->done = 1;
            window->cancel = 1;
            _CB.unkB06C = 1;
            menuCB_SE_Play(0x12);
            return;
        }
        if ((windowGetKeyInfo()->trg | windowGetKeyInfo2()->trg) & 3) {
            switch (_CB.unkAFEC) {
            case 0:
                _CB.unkAFEC = 2;
                break;
            case 1:
                _CB.unkAFEC = 3;
                break;
            case 2:
                _CB.unkAFEC = 0;
                break;
            case 3:
                _CB.unkAFEC = 1;
                break;
            }
            menuCB_SE_Play(0x10);
        }
        if ((windowGetKeyInfo()->trg | windowGetKeyInfo2()->trg) & 0xC) {
            switch (_CB.unkAFEC) {
            case 0:
                _CB.unkAFEC = 1;
                break;
            case 1:
                _CB.unkAFEC = 0;
                break;
            case 2:
                _CB.unkAFEC = 3;
                break;
            case 3:
                _CB.unkAFEC = 2;
                break;
            }
            menuCB_SE_Play(0x10);
        }
    }
}
}

extern "C" {
void menuCB_Tunaide03_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x63D:
        sprite->msg = 0x440e;
        break;
    case 0x64A:
        fn_80080390(window, sprite, 0x435e);
        break;
    case 0x5FB:
    case 0x60D:
    case 0x61F:
        menuCB_SetSprite(sprite, menuSpriteBiosGetPtr(Small_Face_Char[toolbattle_trainerFace(0x0)]));
        break;
    case 0x5FC:
    case 0x616:
    case 0x628:
        menuCB_SetSprite(sprite, menuSpriteBiosGetPtr(Small_Face_Char[toolbattle_trainerFace(0x1)]));
        break;
    case 0x604:
    case 0x60E:
    case 0x629:
        menuCB_SetSprite(sprite, menuSpriteBiosGetPtr(Small_Face_Char[toolbattle_trainerFace(0x2)]));
        break;
    case 0x605:
    case 0x617:
    case 0x620:
        menuCB_SetSprite(sprite, menuSpriteBiosGetPtr(Small_Face_Char[toolbattle_trainerFace(0x3)]));
        break;
    case 0x62D:
    case 0x62E:
    case 0x62F:
    case 0x630:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFEC == 0);
        break;
    case 0x631:
    case 0x632:
    case 0x633:
    case 0x634:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFEC == 1);
        break;
    case 0x635:
    case 0x636:
    case 0x637:
    case 0x638:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFEC == 2);
        break;
    case 0x639:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkAFEC == 3);
        menuCB_Cursol_Disp_AlphaSet(window, sprite, 0x1);
        break;
    case 0x63E:
    case 0x642:
    case 0x646:
        toobattle_drawHeroName(window, 0x0);
        break;
    case 0x63F:
    case 0x644:
    case 0x648:
        toobattle_drawHeroName(window, 0x1);
        break;
    case 0x640:
    case 0x643:
    case 0x649:
        toobattle_drawHeroName(window, 0x2);
        break;
    case 0x641:
    case 0x645:
    case 0x647:
        toobattle_drawHeroName(window, 0x3);
        break;
    }
}
}

extern "C" {
void menuTool_error00_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_AlphaGet(window);
}
}

extern "C" {
void menuTool_error00_Button(tagWINDOW_WORK* window) {
    if (!pauseIsPause()) {
        if (windowGetKeyInfo()->trg & 0x10) {
            window->done = 1;
            menuCB_SE_Play(0x11);
            return;
        }
        if (windowGetKeyInfo()->trg & 0x20) {
            window->done = 1;
            _CB.unkB088 = 1;
            menuCB_SE_Play(0x12);
            return;
        }
        if (_CB.unkB0DC != -1) {
            if (windowGetKeyRepeat() & 1) {
                if (_CB.unkB008 == 6) {
                    _CB.unkB008 = _CB.unkB0DC;
                    menuCB_SE_Play(0x10);
                    return;
                }
                if (_CB.unkB008 != 0) {
                    _CB.unkB008--;
                    menuCB_SE_Play(0x10);
                    return;
                }
            }
            if ((windowGetKeyRepeat() & 2) && _CB.unkB008 < _CB.unkB0DC) {
                _CB.unkB008++;
                menuCB_SE_Play(0x10);
                return;
            }
            if ((windowGetKeyInfo()->trg | windowGetKeyInfo2()->trg) & 0xC) {
                if (_CB.unkB008 == 6) {
                    _CB.unkB008 = 0;
                    menuCB_SE_Play(0x10);
                    return;
                }
                _CB.unkB008 = 6;
                menuCB_SE_Play(0x10);
            }
        } else {
            _CB.unkB008 = 6;
        }
    }
}
}

extern "C" {
void menuTool_error01_Ctrl(tagWINDOW_WORK* window) {
    if (window->state == 2) {
        s32 i = 0;
        for (; i <= _CB.unkB0E4; i++) {
            menuItemBiosSetSelectFlag(0xA7, _error01_cursol_item_tbl[i], 1);
        }
        for (; i < 14; i++) {
            menuItemBiosSetSelectFlag(0xA7, _error01_cursol_item_tbl[i], 0);
        }
    }
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
}
}

extern "C" {
void menuTool_error01_Button(tagWINDOW_WORK* window) {
    _CB.unkB00C = window->select;
    if (!pauseIsPause()) {
        if (windowGetKeyInfo()->trg & 0x10) {
            window->done = 1;
            return;
        }
        if (windowGetKeyInfo()->trg & 0x20) {
            _CB.unkB08C = 1;
            window->done = 1;
            window->cancel = 1;
        }
    }
}
}

extern "C" {
void menuCB_error01_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x4DC: {
        winSpriteSetDisp(sprite, 0);
        s16 sel = window->select;
        if (sel >= 0) {
            s32 base = 0;
            if (sel >= 7) {
                base = 0xA0;
            }
            menuSubDrawCursorBackAnimeOnOffAuto(window, winSpriteGetLayerID(window, sprite), base, (window->select % 7) << 5, sprite->x,
                                                sprite->y, window->alpha, 1);
        }
        return;
    }
    case 0x4EC:
        menuCB_Trainer_Error_Disp(window, sprite, _CB.unkB008, 0);
        return;
    case 0x4EB:
        menuCB_Trainer_Error_Disp(window, sprite, _CB.unkB008, 1);
        return;
    case 0x4ED:
        sprite->msg = 0x43C3;
        break;
    }
}
}

extern "C" {
void menuTool_GBAConnect_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    if (window->state == 2) {
        if (gbaConectGBA_Connect_WORK.state[0] == 5 && !gbaCommandIsConnected(1)) {
            gbaConectGBA_Connect_WORK.state[0] = 7;
            gbaConectGBA_Connect_WORK.unk28 = 8;
        }
        if (gbaConectGBA_Connect_WORK.state[1] == 5 && !gbaCommandIsConnected(2)) {
            gbaConectGBA_Connect_WORK.state[1] = 7;
            gbaConectGBA_Connect_WORK.unk28 = 8;
        }
        if (gbaConectGBA_Connect_WORK.state[2] == 5 && !gbaCommandIsConnected(3)) {
            gbaConectGBA_Connect_WORK.state[2] = 7;
            gbaConectGBA_Connect_WORK.unk28 = 8;
        }
        if (gbaConectGBA_Connect_WORK.state[3] == 5 && !gbaCommandIsConnected(4)) {
            gbaConectGBA_Connect_WORK.state[3] = 7;
            gbaConectGBA_Connect_WORK.unk28 = 8;
        }
    }
}
}

extern "C" {
void menuTool_GBAConnect_Button(void) {
}
}

extern "C" {
void menuCB_GBAConnect_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0xF1:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lwz r0, 0x0(r5) | cmpwi r0, 0xa | beq .L_800772A8 | cmpwi r0, 0x5 | bne .L_800772AC
        break;
    case 0xF2:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lwz r0, 0x4(r4) | subfic r0, r0, 0x5 | cntlzw r0, r0 | srwi r4, r0, 5
        break;
    case 0xF3:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lwz r0, 0x8(r4) | subfic r0, r0, 0x5 | cntlzw r0, r0 | srwi r4, r0, 5
        break;
    case 0xF4:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lwz r0, 0xc(r4) | subfic r0, r0, 0x5 | cntlzw r0, r0 | srwi r4, r0, 5
        break;
    case 0xF5:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lwz r0, 0x0(r5) | cmpwi r0, 0xb | beq .L_8007734C | cmpwi r0, 0x6 | beq .L_8007734C | cmpwi r0, 0x7 | bne .L_80077350
        break;
    case 0xF6:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lwz r0, 0x4(r5) | cmpwi r0, 0x6 | beq .L_8007737C | cmpwi r0, 0x7 | bne .L_80077380
        break;
    case 0xF7:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lwz r0, 0x8(r5) | cmpwi r0, 0x6 | beq .L_800773AC | cmpwi r0, 0x7 | bne .L_800773B0
        break;
    case 0xF8:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lwz r0, 0xc(r5) | cmpwi r0, 0x6 | beq .L_800773DC | cmpwi r0, 0x7 | bne .L_800773E0
        break;
    case 0xDE:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x30(r5) | extsb r0, r0 | cmpwi r0, 0x1 | beq .L_80077414 | cmpwi r0, 0x4 | beq .L_80077414
        break;
    case 0xE2:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x30(r5) | extsb r0, r0 | cmpwi r0, 0x1 | beq .L_80077448 | cmpwi r0, 0x4 | beq .L_80077448
        break;
    case 0xE6:
 // RAW: lis r3, gbaConectGBA_Connect_WORK@ha | addi r3, r3, gbaConectGBA_Connect_WORK@l | lbz r0, 0x30(r3) | extsb r0, r0 | cmpwi r0, 0x1 | beq .L_80077470 | cmpwi r0, 0x4 | bne .L_80077480
        break;
    case 0xEA:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x30(r4) | extsb r5, r0 | subfic r4, r5, 0x1 | subi r0, r5, 0x1 | or r0, r4, r0 | srwi r4, r0, 31
        break;
    case 0xEE:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x30(r5) | extsb r0, r0 | cmpwi r0, 0x1 | beq .L_80077594 | cmpwi r0, 0x4 | bne .L_80077598
        break;
    case 0xEF:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x30(r5) | extsb r0, r0 | cmpwi r0, 0x1 | beq .L_800775C8 | cmpwi r0, 0x4 | bne .L_800775CC
        break;
    case 0xF0:
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r5, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x30(r5) | extsb r0, r0 | cmpwi r0, 0x1 | beq .L_800775FC | cmpwi r0, 0x4 | bne .L_80077600
        break;
    case 0xE7:
 // RAW: lis r3, gbaConectGBA_Connect_WORK@ha | addi r4, r3, gbaConectGBA_Connect_WORK@l | lbz r0, 0x49(r4) | cmplwi r0, 0x0 | beq .L_80077634 | lha r3, 0x50(r31) | sth r3, 0x36(r4) | lha r3, 0x52(r31) | sth r3, 0x3e(r4) | stb r0, 0x49(r4)
        break;
    case 0xE0:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x32(r4) | extsb r4, r0 | neg r0, r4 | or r0, r0, r4 | srwi r4, r0, 31
        break;
    case 0xE4:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x32(r4) | extsb r4, r0 | neg r0, r4 | or r0, r0, r4 | srwi r4, r0, 31
        break;
    case 0xE8:
        winSpriteSetDisp(sprite, 0x0);
 // RAW: lis r3, gbaConectGBA_Connect_WORK@ha | addi r4, r3, gbaConectGBA_Connect_WORK@l | lbz r0, 0x32(r4) | extsb r0, r0 | cmpwi r0, 0x0 | bne .L_80077734
        break;
    case 0xEC:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x32(r4) | extsb r4, r0 | neg r0, r4 | or r0, r0, r4 | srwi r4, r0, 31
        break;
    case 0xE1:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x33(r4) | extsb r4, r0 | neg r0, r4 | or r0, r0, r4 | srwi r4, r0, 31
        break;
    case 0xE5:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x33(r4) | extsb r4, r0 | neg r0, r4 | or r0, r0, r4 | srwi r4, r0, 31
        break;
    case 0xE9:
        winSpriteSetDisp(sprite, 0x0);
 // RAW: lis r3, gbaConectGBA_Connect_WORK@ha | addi r4, r3, gbaConectGBA_Connect_WORK@l | lbz r0, 0x33(r4) | extsb r0, r0 | cmpwi r0, 0x0 | bne .L_80077880
        break;
    case 0xED:
        menuCB_SpriteDispCheckONorOFF(sprite, sprite);
 // RAW: lis r4, gbaConectGBA_Connect_WORK@ha | addi r4, r4, gbaConectGBA_Connect_WORK@l | lbz r0, 0x33(r4) | extsb r4, r0 | neg r0, r4 | or r0, r0, r4 | srwi r4, r0, 31
        break;
    case 0xFB:
        sprite->msg = 0x441c;
        break;
    case 0xFC:
        sprite->msg = 0x441d;
        break;
    case 0xFD:
        sprite->msg = 0x435e;
        break;
    }
}
}

extern "C" {
void menuTool_BattleBA01_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
}
}

extern "C" {
void menuTool_BattleBA01_Button(tagWINDOW_WORK* window) {
    if (!pauseIsPause() && (windowGetKeyInfo()->trg & 0x10)) {
        window->done = 1;
    }
}
}

extern "C" {
void menuTool_BattleBA03_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    if (_CB.unk4 == 0 && menuCBBattleStartGetStatus() == 0 && menuCB_GetDisconnectedGBA()) {
        _CB.unkB19C = 1;
        window->done = 1;
        window->cancel = 1;
    }
}
}

extern "C" {
void menuTool_BattleBA03_Button(tagWINDOW_WORK* window) {
    if (!pauseIsPause() && menuCBBattleBANextMenu(window) && (windowGetKeyInfo()->trg & 0x20)) {
        window->done = 1;
    }
}
}

extern "C" {
void menuCB_BattleBeforeAfter3_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0xFF:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x0, 0x0);
        break;
    case 0x100:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x0, 0x1);
        break;
    case 0x101:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x0, 0x2);
        break;
    case 0x102:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x0, 0x3);
        break;
    case 0x103:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x0, 0x4);
        break;
    case 0x104:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x0, 0x5);
        break;
    case 0x2B4:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x1, 0x0);
        break;
    case 0x2B5:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x1, 0x1);
        break;
    case 0x2B6:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x1, 0x2);
        break;
    case 0x2B7:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x1, 0x3);
        break;
    case 0x2B8:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x1, 0x4);
        break;
    case 0x2B9:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x1, 0x5);
        break;
    case 0x2BA:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x2, 0x0);
        break;
    case 0x2BB:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x2, 0x1);
        break;
    case 0x2BC:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x2, 0x2);
        break;
    case 0x2BD:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x2, 0x3);
        break;
    case 0x2BE:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x2, 0x4);
        break;
    case 0x2BF:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x2, 0x5);
        break;
    case 0x2C0:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x3, 0x0);
        break;
    case 0x2C1:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x3, 0x1);
        break;
    case 0x2C2:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x3, 0x2);
        break;
    case 0x2C3:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x3, 0x3);
        break;
    case 0x2C4:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x3, 0x4);
        break;
    case 0x2C5:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0x3, 0x5);
        break;
    case 0x2AE:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x0, 0x0);
        break;
    case 0x2AF:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x0, 0x1);
        break;
    case 0x2B0:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x0, 0x2);
        break;
    case 0x2B1:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x0, 0x3);
        break;
    case 0x2B2:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x0, 0x4);
        break;
    case 0x2B3:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x0, 0x5);
        break;
    case 0x10B:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x1, 0x0);
        break;
    case 0x10C:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x1, 0x1);
        break;
    case 0x10D:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x1, 0x2);
        break;
    case 0x10E:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x1, 0x3);
        break;
    case 0x10F:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x1, 0x4);
        break;
    case 0x110:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x1, 0x5);
        break;
    case 0x117:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x2, 0x0);
        break;
    case 0x118:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x2, 0x1);
        break;
    case 0x119:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x2, 0x2);
        break;
    case 0x11A:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x2, 0x3);
        break;
    case 0x11B:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x2, 0x4);
        break;
    case 0x11C:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x2, 0x5);
        break;
    case 0x123:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x3, 0x0);
        break;
    case 0x124:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x3, 0x1);
        break;
    case 0x125:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x3, 0x2);
        break;
    case 0x126:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x3, 0x3);
        break;
    case 0x127:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x3, 0x4);
        break;
    case 0x128:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0x3, 0x5);
        break;
    case 0x14E:
        toobattle_drawHeroName2(window, sprite, 0x3);
        break;
    case 0x14D:
        toobattle_drawHeroName2(window, sprite, 0x2);
        break;
    case 0x14C:
        toobattle_drawHeroName2(window, sprite, 0x1);
        break;
    case 0x14B:
        toobattle_drawHeroName2(window, sprite, 0x0);
        break;
    case 0x12F:
        menuCBBattleBABatuMark(sprite, 0x3, 0x0);
        break;
    case 0x130:
        menuCBBattleBABatuMark(sprite, 0x3, 0x1);
        break;
    case 0x131:
        menuCBBattleBABatuMark(sprite, 0x3, 0x2);
        break;
    case 0x132:
        menuCBBattleBABatuMark(sprite, 0x3, 0x3);
        break;
    case 0x133:
        menuCBBattleBABatuMark(sprite, 0x3, 0x4);
        break;
    case 0x134:
        menuCBBattleBABatuMark(sprite, 0x3, 0x5);
        break;
    case 0x135:
        menuCBBattleBABatuMark(sprite, 0x2, 0x0);
        break;
    case 0x136:
        menuCBBattleBABatuMark(sprite, 0x2, 0x1);
        break;
    case 0x137:
        menuCBBattleBABatuMark(sprite, 0x2, 0x2);
        break;
    case 0x138:
        menuCBBattleBABatuMark(sprite, 0x2, 0x3);
        break;
    case 0x139:
        menuCBBattleBABatuMark(sprite, 0x2, 0x4);
        break;
    case 0x13A:
        menuCBBattleBABatuMark(sprite, 0x2, 0x5);
        break;
    case 0x13B:
        menuCBBattleBABatuMark(sprite, 0x1, 0x0);
        break;
    case 0x13C:
        menuCBBattleBABatuMark(sprite, 0x1, 0x1);
        break;
    case 0x13D:
        menuCBBattleBABatuMark(sprite, 0x1, 0x2);
        break;
    case 0x13E:
        menuCBBattleBABatuMark(sprite, 0x1, 0x3);
        break;
    case 0x13F:
        menuCBBattleBABatuMark(sprite, 0x1, 0x4);
        break;
    case 0x140:
        menuCBBattleBABatuMark(sprite, 0x1, 0x5);
        break;
    case 0x141:
        menuCBBattleBABatuMark(sprite, 0x0, 0x0);
        break;
    case 0x142:
        menuCBBattleBABatuMark(sprite, 0x0, 0x1);
        break;
    case 0x143:
        menuCBBattleBABatuMark(sprite, 0x0, 0x2);
        break;
    case 0x144:
        menuCBBattleBABatuMark(sprite, 0x0, 0x3);
        break;
    case 0x145:
        menuCBBattleBABatuMark(sprite, 0x0, 0x4);
        break;
    case 0x146:
        menuCBBattleBABatuMark(sprite, 0x0, 0x5);
        break;
    case 0x148:
        menuCBBattleStartDispTrainerFaceSub(window, sprite, 0x3);
        break;
    case 0x147:
        menuCBBattleStartDispTrainerFaceSub(window, sprite, 0x2);
        break;
    case 0x149:
        menuCBBattleStartDispTrainerFaceSub(window, sprite, 0x1);
        break;
    case 0x14A:
        menuCBBattleStartDispTrainerFaceSub(window, sprite, 0x0);
        break;
    case 0x105:
        menuCB_BattleBA_FacePanelSet(sprite, 0x0, 0x0);
        break;
    case 0x106:
        menuCB_BattleBA_FacePanelSet(sprite, 0x0, 0x1);
        break;
    case 0x107:
        menuCB_BattleBA_FacePanelSet(sprite, 0x0, 0x2);
        break;
    case 0x108:
        menuCB_BattleBA_FacePanelSet(sprite, 0x0, 0x3);
        break;
    case 0x109:
        menuCB_BattleBA_FacePanelSet(sprite, 0x0, 0x4);
        break;
    case 0x10A:
        menuCB_BattleBA_FacePanelSet(sprite, 0x0, 0x5);
        break;
    case 0x111:
        menuCB_BattleBA_FacePanelSet(sprite, 0x1, 0x0);
        break;
    case 0x112:
        menuCB_BattleBA_FacePanelSet(sprite, 0x1, 0x1);
        break;
    case 0x113:
        menuCB_BattleBA_FacePanelSet(sprite, 0x1, 0x2);
        break;
    case 0x114:
        menuCB_BattleBA_FacePanelSet(sprite, 0x1, 0x3);
        break;
    case 0x115:
        menuCB_BattleBA_FacePanelSet(sprite, 0x1, 0x4);
        break;
    case 0x116:
        menuCB_BattleBA_FacePanelSet(sprite, 0x1, 0x5);
        break;
    case 0x11D:
        menuCB_BattleBA_FacePanelSet(sprite, 0x2, 0x0);
        break;
    case 0x11E:
        menuCB_BattleBA_FacePanelSet(sprite, 0x2, 0x1);
        break;
    case 0x11F:
        menuCB_BattleBA_FacePanelSet(sprite, 0x2, 0x2);
        break;
    case 0x120:
        menuCB_BattleBA_FacePanelSet(sprite, 0x2, 0x3);
        break;
    case 0x121:
        menuCB_BattleBA_FacePanelSet(sprite, 0x2, 0x4);
        break;
    case 0x122:
        menuCB_BattleBA_FacePanelSet(sprite, 0x2, 0x5);
        break;
    case 0x129:
        menuCB_BattleBA_FacePanelSet(sprite, 0x3, 0x0);
        break;
    case 0x12A:
        menuCB_BattleBA_FacePanelSet(sprite, 0x3, 0x1);
        break;
    case 0x12B:
        menuCB_BattleBA_FacePanelSet(sprite, 0x3, 0x2);
        break;
    case 0x12C:
        menuCB_BattleBA_FacePanelSet(sprite, 0x3, 0x3);
        break;
    case 0x12D:
        menuCB_BattleBA_FacePanelSet(sprite, 0x3, 0x4);
        break;
    case 0x12E:
        menuCB_BattleBA_FacePanelSet(sprite, 0x3, 0x5);
        break;
    case 0x1D4:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x0, 0x0);
        break;
    case 0x1D5:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x0, 0x1);
        break;
    case 0x1D6:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x0, 0x2);
        break;
    case 0x1D7:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x0, 0x3);
        break;
    case 0x1D8:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x0, 0x4);
        break;
    case 0x1D9:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x0, 0x5);
        break;
    case 0x1DA:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x1, 0x0);
        break;
    case 0x1DB:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x1, 0x1);
        break;
    case 0x1DC:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x1, 0x2);
        break;
    case 0x1DD:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x1, 0x3);
        break;
    case 0x1DE:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x1, 0x4);
        break;
    case 0x1DF:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x1, 0x5);
        break;
    case 0x1E0:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x2, 0x0);
        break;
    case 0x1E1:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x2, 0x1);
        break;
    case 0x1E2:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x2, 0x2);
        break;
    case 0x1E3:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x2, 0x3);
        break;
    case 0x1E4:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x2, 0x4);
        break;
    case 0x1E5:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x2, 0x5);
        break;
    case 0x1E6:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x3, 0x0);
        break;
    case 0x1E7:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x3, 0x1);
        break;
    case 0x1E8:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x3, 0x2);
        break;
    case 0x1E9:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x3, 0x3);
        break;
    case 0x1EA:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x3, 0x4);
        break;
    case 0x1EB:
        menuCB_BattleBA_HPBarDispSet(sprite, 0x3, 0x5);
        break;
    case 0x2AA:
        menuCB_PrintXP(sprite, 0x0);
        break;
    case 0x2AB:
        menuCB_PrintXP(sprite, 0x1);
        break;
    case 0x2AC:
        menuCB_PrintXP(sprite, 0x2);
        break;
    case 0x2AD:
        menuCB_PrintXP(sprite, 0x3);
        break;
    }
}
}

extern "C" {
void menuTool_BattleBA04_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    if (_CB.unk4 == 0 && menuCBBattleStartGetStatus() == 0 && menuCB_GetDisconnectedGBA()) {
        _CB.unkB19C = 1;
        window->done = 1;
        window->cancel = 1;
    }
}
}

extern "C" {
void menuTool_BattleBA04_Button(tagWINDOW_WORK* window) {
    if (!pauseIsPause() && menuCBBattleBANextMenu(window) && (windowGetKeyInfo()->trg & 0x20)) {
        window->done = 1;
    }
}
}

extern "C" {
void menuCB_BattleBeforeAfter4_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x2C6:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0, 0);
        break;
    case 0x2C7:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0, 1);
        break;
    case 0x2C8:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0, 2);
        break;
    case 0x2C9:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0, 3);
        break;
    case 0x2CA:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0, 4);
        break;
    case 0x2CB:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0, 5);
        break;
    case 0x2CC:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 1, 0);
        break;
    case 0x2CD:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 1, 1);
        break;
    case 0x2CE:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 1, 2);
        break;
    case 0x2CF:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 1, 3);
        break;
    case 0x2D0:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 1, 4);
        break;
    case 0x2D1:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 1, 5);
        break;
    case 0x14F:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0, 0);
        break;
    case 0x150:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0, 1);
        break;
    case 0x151:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0, 2);
        break;
    case 0x155:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0, 3);
        break;
    case 0x156:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0, 4);
        break;
    case 0x157:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0, 5);
        break;
    case 0x15B:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 1, 0);
        break;
    case 0x15C:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 1, 1);
        break;
    case 0x15D:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 1, 2);
        break;
    case 0x161:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 1, 3);
        break;
    case 0x162:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 1, 4);
        break;
    case 0x163:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 1, 5);
        break;
    case 0x177:
        toobattle_drawHeroName2(window, sprite, 0);
        break;
    case 0x178:
        toobattle_drawHeroName2(window, sprite, 1);
        break;
    case 0x167:
        menuCBBattleBABatuMark(sprite, 1, 3);
        break;
    case 0x168:
        menuCBBattleBABatuMark(sprite, 1, 4);
        break;
    case 0x169:
        menuCBBattleBABatuMark(sprite, 1, 5);
        break;
    case 0x16A:
        menuCBBattleBABatuMark(sprite, 1, 0);
        break;
    case 0x16B:
        menuCBBattleBABatuMark(sprite, 1, 1);
        break;
    case 0x16C:
        menuCBBattleBABatuMark(sprite, 1, 2);
        break;
    case 0x16D:
        menuCBBattleBABatuMark(sprite, 0, 3);
        break;
    case 0x16E:
        menuCBBattleBABatuMark(sprite, 0, 4);
        break;
    case 0x16F:
        menuCBBattleBABatuMark(sprite, 0, 5);
        break;
    case 0x170:
        menuCBBattleBABatuMark(sprite, 0, 0);
        break;
    case 0x171:
        menuCBBattleBABatuMark(sprite, 0, 1);
        break;
    case 0x172:
        menuCBBattleBABatuMark(sprite, 0, 2);
        break;
    case 0x173:
        menuCBBattleStartDispTrainerFaceSub(window, sprite, 0);
        break;
    case 0x174:
        menuCBBattleStartDispTrainerFaceSub(window, sprite, 1);
        break;
    case 0x152:
        menuCB_BattleBA_FacePanelSet(sprite, 0, 0);
        break;
    case 0x153:
        menuCB_BattleBA_FacePanelSet(sprite, 0, 1);
        break;
    case 0x154:
        menuCB_BattleBA_FacePanelSet(sprite, 0, 2);
        break;
    case 0x158:
        menuCB_BattleBA_FacePanelSet(sprite, 0, 3);
        break;
    case 0x159:
        menuCB_BattleBA_FacePanelSet(sprite, 0, 4);
        break;
    case 0x15A:
        menuCB_BattleBA_FacePanelSet(sprite, 0, 5);
        break;
    case 0x15E:
        menuCB_BattleBA_FacePanelSet(sprite, 1, 0);
        break;
    case 0x15F:
        menuCB_BattleBA_FacePanelSet(sprite, 1, 1);
        break;
    case 0x160:
        menuCB_BattleBA_FacePanelSet(sprite, 1, 2);
        break;
    case 0x164:
        menuCB_BattleBA_FacePanelSet(sprite, 1, 3);
        break;
    case 0x165:
        menuCB_BattleBA_FacePanelSet(sprite, 1, 4);
        break;
    case 0x166:
        menuCB_BattleBA_FacePanelSet(sprite, 1, 5);
        break;
    case 0x1EC:
        menuCB_BattleBA_HPBarDispSet(sprite, 0, 0);
        break;
    case 0x1ED:
        menuCB_BattleBA_HPBarDispSet(sprite, 0, 1);
        break;
    case 0x1EE:
        menuCB_BattleBA_HPBarDispSet(sprite, 0, 2);
        break;
    case 0x1EF:
        menuCB_BattleBA_HPBarDispSet(sprite, 0, 3);
        break;
    case 0x1F0:
        menuCB_BattleBA_HPBarDispSet(sprite, 0, 4);
        break;
    case 0x1F1:
        menuCB_BattleBA_HPBarDispSet(sprite, 0, 5);
        break;
    case 0x1F2:
        menuCB_BattleBA_HPBarDispSet(sprite, 1, 0);
        break;
    case 0x1F3:
        menuCB_BattleBA_HPBarDispSet(sprite, 1, 1);
        break;
    case 0x1F4:
        menuCB_BattleBA_HPBarDispSet(sprite, 1, 2);
        break;
    case 0x1F5:
        menuCB_BattleBA_HPBarDispSet(sprite, 1, 3);
        break;
    case 0x1F6:
        menuCB_BattleBA_HPBarDispSet(sprite, 1, 4);
        break;
    case 0x1F7:
        menuCB_BattleBA_HPBarDispSet(sprite, 1, 5);
        break;
    case 0x175:
        menuCB_PrintXP(sprite, 0);
        break;
    case 0x176:
        menuCB_PrintXP(sprite, 1);
        break;
    }
}
}

extern "C" {
void menuTool_BattleBA05_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    if (_CB.unk4 == 0 && menuCBBattleStartGetStatus() == 0 && menuCB_GetDisconnectedGBA()) {
        _CB.unkB19C = 1;
        window->done = 1;
        window->cancel = 1;
    }
}
}

extern "C" {
void menuTool_BattleBA05_Button(tagWINDOW_WORK* window) {
    if (!pauseIsPause() && menuCBBattleBANextMenu(window) && (windowGetKeyInfo()->trg & 0x20)) {
        window->done = 1;
    }
}
}

extern "C" {
void menuCB_BattleBeforeAfter5_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x2D2:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0, 0);
        break;
    case 0x2D3:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0, 1);
        break;
    case 0x2D4:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 0, 2);
        break;
    case 0x2D5:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 1, 0);
        break;
    case 0x2D6:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 1, 1);
        break;
    case 0x2D7:
        menuCBPokemonEntryDispPokemonFace_AFTER(window, sprite, 1, 2);
        break;
    case 0x179:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0, 0);
        break;
    case 0x17A:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0, 1);
        break;
    case 0x17B:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 0, 2);
        break;
    case 0x17F:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 1, 0);
        break;
    case 0x180:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 1, 1);
        break;
    case 0x181:
        menuCBPokemonEntryDispPokemonFace_BEFORE(window, sprite, 1, 2);
        break;
    case 0x18F:
        toobattle_drawHeroName2(window, sprite, 0);
        break;
    case 0x190:
        toobattle_drawHeroName2(window, sprite, 1);
        break;
    case 0x185:
        menuCBBattleBABatuMark(sprite, 1, 0);
        break;
    case 0x186:
        menuCBBattleBABatuMark(sprite, 1, 1);
        break;
    case 0x187:
        menuCBBattleBABatuMark(sprite, 1, 2);
        break;
    case 0x188:
        menuCBBattleBABatuMark(sprite, 0, 0);
        break;
    case 0x189:
        menuCBBattleBABatuMark(sprite, 0, 1);
        break;
    case 0x18A:
        menuCBBattleBABatuMark(sprite, 0, 2);
        break;
    case 0x18B:
        menuCBBattleStartDispTrainerFaceSub(window, sprite, 0);
        break;
    case 0x18C:
        menuCBBattleStartDispTrainerFaceSub(window, sprite, 1);
        break;
    case 0x17C:
        menuCB_BattleBA_FacePanelSet(sprite, 0, 0);
        break;
    case 0x17D:
        menuCB_BattleBA_FacePanelSet(sprite, 0, 1);
        break;
    case 0x17E:
        menuCB_BattleBA_FacePanelSet(sprite, 0, 2);
        break;
    case 0x182:
        menuCB_BattleBA_FacePanelSet(sprite, 1, 0);
        break;
    case 0x183:
        menuCB_BattleBA_FacePanelSet(sprite, 1, 1);
        break;
    case 0x184:
        menuCB_BattleBA_FacePanelSet(sprite, 1, 2);
        break;
    case 0x1F8:
        menuCB_BattleBA_HPBarDispSet(sprite, 0, 0);
        break;
    case 0x1F9:
        menuCB_BattleBA_HPBarDispSet(sprite, 0, 1);
        break;
    case 0x1FA:
        menuCB_BattleBA_HPBarDispSet(sprite, 0, 2);
        break;
    case 0x1FB:
        menuCB_BattleBA_HPBarDispSet(sprite, 1, 0);
        break;
    case 0x1FC:
        menuCB_BattleBA_HPBarDispSet(sprite, 1, 1);
        break;
    case 0x1FD:
        menuCB_BattleBA_HPBarDispSet(sprite, 1, 2);
        break;
    case 0x18D:
        menuCB_PrintXP(sprite, 0);
        break;
    case 0x18E:
        if (_CB.unk4 == 1 && _CB.unkAFD4 == 0) {
            menuCB_SetSprite(sprite, menuSpriteBiosGetPtr(PlayerNumber[4]));
            break;
        }
        menuCB_PrintXP(sprite, 1);
        break;
    }
}
}

extern "C" {
void menuTool_BattleBA06_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
}
}

extern "C" {
void menuTool_BattleBA06_Button(void) {
}
}

extern "C" {
void menuCB_BattleBeforeAfter6_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x4B8:
    case 0x4B9:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk10 == 0);
        break;
    case 0x4BA:
    case 0x4BB:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk10 == 1);
        break;
    case 0x4BC:
    case 0x4BD:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk10 == 2);
        break;
    case 0x4BE:
    case 0x4BF:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk10 == 5);
        break;
    case 0x4C0:
    case 0x4C1:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk10 == 3);
        break;
    case 0x4C2:
    case 0x4C3:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk10 == 4);
        break;
    }
}
}

extern "C" {
void menuTool_tunaideGCEntry_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    CAnt::systemUpdate(true);
    menuCB_AlphaGet(window);
}
}

extern "C" {
void menuTool_tunaideGCEntry_Button(void) {
}
}

extern "C" {
void menuTool_tunaideGCEntry00_Button(void) {
}
}

extern "C" {
void menuTool_tunaideGCEntry01_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
}
}

extern "C" {
void menuTool_tunaideGCEntry01_Button(tagWINDOW_WORK* window) {
    if (!pauseIsPause()) {
        if (_CB.unkB0FC == 3 && (windowGetKeyInfo()->trg & 0x30)) {
            _CB.unkB0FC = 0;
            return;
        }
        if (_CB.unkB0F4 == 1) {
            window->done = 1;
            return;
        }
        if (_CB.unkB0FC == 1) {
            window->done = 1;
        }
    }
}
}

extern "C" {
void menuCB_tunaideGCEntry01_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (_CB.unkB0F4 != 1 && _CB.unkB150 == 0) {
        menuCBGCEntryTypeIndex();
        menuCBPokemonCheck(_CB.unkB1D4, _CB.unkB1D8);
    }
    switch (sprite->id) {
    case 0x587:
    case 0x588:
    case 0x589:
    case 0x58A:
    case 0x58B:
    case 0x58C:
    case 0x58D:
    case 0x58E:
    case 0x58F:
        if (_CB.unkB0FC >= 2) {
            _CB.unkB0FC = 3;
            winSpriteSetDisp(sprite, 1);
            return;
        }
        winSpriteSetDisp(sprite, 0);
        break;
    case 0x590:
        if (_CB.unkB0FC >= 2) {
            msgctrlSetValue(0x34, _CB.unkB1E0);
            msgctrlSetValue(0x2F, _CB.unkB1E0);
            sprite->msg = _CB.unkB1DC;
            winSpriteSetDisp(sprite, 1);
            return;
        }
        winSpriteSetDisp(sprite, 0);
        break;
    }
}
}

extern "C" {
void menuCB_tunaideGCEntry01_Disp_UP(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    u32 type;
    s32 sub;
    u32 state;
    if (_CB.unkB0F4 == 1 || _CB.unkB150 != 0) {
        state = 2;
    } else {
        menuCBGCEntryTypeIndex();
        type = _CB.unkB1D4;
        sub = _CB.unkB1D8;
        if (type == 5) {
            state = GCEntryStatusDispPosition[_CB.unkB0F8];
        } else {
            state = 0;
        }
        if (!menuCBPokemonCheck(type, sub)) {
            state = 3;
        }
    }
    if (state == 0) {
        winSpriteSetDisp(sprite, 1);
        menuCB_tunaideGCEntry01_Disp_Sub(window, sprite, type, sub);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}
}

extern "C" {
void menuCB_tunaideGCEntry01_Disp_DOWN(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    u32 type;
    s32 sub;
    u32 state;
    if (_CB.unkB0F4 == 1 || _CB.unkB150 != 0) {
        state = 2;
    } else {
        menuCBGCEntryTypeIndex();
        type = _CB.unkB1D4;
        sub = _CB.unkB1D8;
        if (type == 5) {
            state = GCEntryStatusDispPosition[_CB.unkB0F8];
        } else {
            state = 0;
        }
        if (!menuCBPokemonCheck(type, sub)) {
            state = 3;
        }
    }
    if (state == 1) {
        winSpriteSetDisp(sprite, 1);
        menuCB_tunaideGCEntry01_Disp_Sub(window, sprite, type, sub);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}
}

static void menuCB_tunaideGCEntry01_Disp_Sub(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, u32 type, u32 sub) {
    switch (sprite->id) {
    case 0x57B:
    case 0x57C:
        menuCB2DPokemonItemDisp(sprite, type, sub);
        break;
    case 0x57D:
    case 0x582:
        menuCBPokemonName_nido(window, type, sub, 0);
        break;
    case 0x57E:
    case 0x583:
        menuCBPokemonNameOrg(window, type, sub, 0);
        break;
    case 0x57F:
    case 0x584:
        menuCBPokemonLevel(window, type, sub, 0);
        break;
    case 0x580:
    case 0x585:
        menuCBPokemonHP(window, type, sub, 0);
        break;
    case 0x581:
    case 0x586:
        menuCBPokemonItemName(window, type, sub, 0);
        break;
    }
}

extern "C" {
void menuTool_tunaideGCEntry02_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF(window, _CB.unkB0F0 == 1);
    if (_CB.unkB150 != 0 && _CB.unkB0F0 == 1) {
        window->value = _CB.unkB158;
    }
}
}

extern "C" {
void menuTool_tunaideGCEntry02_Button(void) {
}
}

extern "C" {
void menuTool_tunaideGCEntry03_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF(window, _CB.unkB0F0 == 0);
    if (_CB.unkB150 != 0 && _CB.unkB0F0 == 0) {
        window->value = _CB.unkB158;
    }
}
}

extern "C" {
void menuTool_tunaideGCEntry03_Button(void) {
}
}

extern "C" {
void menuTool_tunaideGCEntry04_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF(window, _CB.unkB0F0 == 2);
    if (_CB.unkB150 != 0 && _CB.unkB0F0 == 2) {
        window->value = _CB.unkB158;
    }
}
}

extern "C" {
void menuTool_tunaideGCEntry04_Button(void) {
}
}

extern "C" {
void menuTool_tunaidePokemonSelect0_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
}
}

extern "C" {
void menuTool_tunaidePokemonSelect0_Button(void) {
}
}

extern "C" {
void menuCB_tunaidePokemonSelect0_Disp_L(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s32 index = _CB.unkB104;
    if (index == -1) {
        winSpriteSetDisp(sprite, 0);
        return;
    }
    if (!menuCBPokemonCheck(0, index)) {
        winSpriteSetDisp(sprite, 0);
        return;
    }
    if (toolentryTaisenGetHomePlace(0) != 0) {
        winSpriteSetDisp(sprite, 0);
        return;
    }
    if (menuCB_GCStatusDispMode(sprite, 0)) {
        menuCB_tunaidePokemonSelect0_Disp_Sub(window, sprite, index);
    }
}
}

extern "C" {
void menuCB_tunaidePokemonSelect0_Disp_R(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s32 index = _CB.unkB104;
    if (index == -1) {
        winSpriteSetDisp(sprite, 0);
        return;
    }
    if (!menuCBPokemonCheck(0, index)) {
        winSpriteSetDisp(sprite, 0);
        return;
    }
    if (toolentryTaisenGetHomePlace(0) != 0) {
        winSpriteSetDisp(sprite, 0);
        return;
    }
    if (menuCB_GCStatusDispMode(sprite, 1)) {
        menuCB_tunaidePokemonSelect0_Disp_Sub(window, sprite, index);
    }
}
}

static void menuCB_tunaidePokemonSelect0_Disp_Sub(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, s32 index) {
    switch (sprite->id) {
    case 0x256:
    case 0x291:
        menuCBPokemonEntryDispPokemonFace(window, sprite, 0x0, index);
        break;
    case 0x266:
    case 0x288:
        menuCBPokemonWazaTYPE(window, 0x0, index, 0x0);
        break;
    case 0x265:
    case 0x289:
        menuCBPokemonWazaTYPE(window, 0x0, index, 0x1);
        break;
    case 0x264:
    case 0x28B:
        menuCBPokemonWazaTYPE(window, 0x0, index, 0x2);
        break;
    case 0x263:
    case 0x27E:
        menuCBPokemonWazaTYPE(window, 0x0, index, 0x3);
        break;
    case 0x268:
    case 0x286:
        menuCBPokemonTYPE1(window, 0x0, index);
        break;
    case 0x267:
    case 0x287:
        menuCBPokemonTYPE2(window, 0x0, index);
        break;
    case 0x269:
    case 0x27D:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(0x0, index));
        break;
    case 0x26A:
    case 0x296:
        menuCBPokemonStatusDisp(window, 0x0, index, 0x0, 0x4);
        break;
    case 0x26B:
    case 0x27C:
        menuCBPokemonStatusDisp(window, 0x0, index, 0x0, 0x3);
        break;
    case 0x26C:
    case 0x28D:
        menuCBPokemonStatusDisp(window, 0x0, index, 0x0, 0x2);
        break;
    case 0x26D:
    case 0x299:
        menuCBPokemonStatusDisp(window, 0x0, index, 0x0, 0x1);
        break;
    case 0x26E:
    case 0x27B:
        menuCBPokemonStatusDisp(window, 0x0, index, 0x0, 0x0);
        break;
    case 0x26F:
    case 0x293:
        menuCBPokemonWazaNAME(window, 0x0, index, 0x3);
        break;
    case 0x270:
    case 0x298:
        menuCBPokemonWazaNAME(window, 0x0, index, 0x2);
        break;
    case 0x271:
    case 0x28A:
        menuCBPokemonWazaNAME(window, 0x0, index, 0x1);
        break;
    case 0x272:
    case 0x295:
        menuCBPokemonWazaNAME(window, 0x0, index, 0x0);
        break;
    case 0x273:
    case 0x297:
        menuCBPokemonTOKUSEI(window, 0x0, index);
        break;
    case 0x274:
    case 0x27A:
        menuCBPokemonItemName(window, 0x0, index, 0x1);
        break;
    case 0x275:
    case 0x290:
        menuCBPokemonHP(window, 0x0, index, 0x1);
        break;
    case 0x276:
    case 0x279:
        menuCBPokemonLevel(window, 0x0, index, 0x1);
        break;
    case 0x278:
    case 0x294:
        menuCBPokemonName(window, 0x0, index, 0x1);
        break;
    }
}

extern "C" {
void menuTool_tunaidePokemonSelect1_Ctrl(tagWINDOW_WORK* window) {
    u16 count;
    menuCB_DispEffect(window);
    _CB.unkB104 = -1;
    menuSetStatus(window->seq, 0x10);
    if (menuCB_GetDisconnectedGBA()) {
        _CB.unkB1A0 = 1;
        return;
    }
    menuCBPokemonEntryButtonTask_20041006();
    if (_CB.unkB108 < 1 && !pauseIsPause()) {
        if (windowGetKeyInfo()->trg & 0x10) {
            count = menuCBPokemonEntryPokemonNumMin(0);
            if (toolentryTaisengetEtnryPokemonOrderNum(0) >= count && toolentryTaisenGetHomePlace(0) == 0) {
                _CB.unkB108 = 1;
                return;
            }
        }
        if (toolentryTaisenGetHomePlace(0) == 0) {
            count = menuCBBios_ParticipationPokemonMax();
            u16 num = toolentryTaisenGetPokemonNum(0);
            if (num < count) {
                count = num;
            }
            if (count == toolentryTaisengetEtnryPokemonOrderNum(0)) {
                _CB.unkB108 = 1;
                return;
            }
        }
        if (windowGetKeyInfo()->on & 0x400) {
            u32 pad = GSinputButtonsPressed(1);
            if (pad & 0x400) {
                _CB.unkB104 = 5;
            }
            if (pad & 2) {
                _CB.unkB104 = 4;
            }
            if (pad & 4) {
                _CB.unkB104 = 3;
            }
            if (pad & 0x800) {
                _CB.unkB104 = 2;
            }
            if (pad & 8) {
                _CB.unkB104 = 1;
            }
            if (pad & 1) {
                _CB.unkB104 = 0;
            }
        }
    }
}
}

extern "C" {
void menuTool_tunaidePokemonSelect1_Button(void) {
}
}

extern "C" {
void menuCB_tunaidePokemonSelect1_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x4B7: {
        s32 msg;
        if (pGCB->entries[pGCB->cur].flag == 0) {
            msgctrlSetValue(0x2F, pGCB->entries[pGCB->cur].value);
            msg = 0x443B;
        } else {
            msg = 0x43B3;
        }
        GSmsgPrint2(window->sprites, 0, 0, window->alpha | 0xFFFFFF00, msg);
        return;
    }
    case 0x4B4:
        sprite->msg = 0x43FB;
        menuCBPokemonEntryDisp(sprite);
        return;
    case 0x4B5:
        sprite->msg = 0x43FA;
        menuCBPokemonEntryDisp(sprite);
        if (pGCB->entries[pGCB->cur].flag == 0) {
            winSpriteSetDisp(sprite, 0);
        }
        return;
    case 0x4B6:
        sprite->msg = 0x43FC;
        menuCBPokemonEntryDisp(sprite);
        return;
    case 0x3F4:
    case 0x3F5:
    case 0x3F6:
    case 0x3F8:
    case 0x3F9:
        menuCBPokemonEntryDisp(sprite);
        return;
    case 0x3F7:
        menuCBPokemonEntryDisp(sprite);
        if (pGCB->entries[pGCB->cur].flag == 0) {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x4B3:
        menuCBPokemonEntryGCControlDisp(sprite, 0);
        return;
    case 0x4B2:
        menuCBPokemonEntryGCControlDisp(sprite, 1);
        return;
    case 0x4B1:
        menuCBPokemonEntryGCControlDisp(sprite, 2);
        return;
    case 0x4B0:
        menuCBPokemonEntryGCControlDisp(sprite, 3);
        return;
    case 0x4AF:
        menuCBPokemonEntryGCControlDisp(sprite, 4);
        return;
    case 0x4AE:
        menuCBPokemonEntryGCControlDisp(sprite, 5);
        break;
    }
}
}

extern "C" {
void menuCB_tunaidePokemonSelect1_Disp_LU(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    menuCB_tunaidePokemonSelect1_Disp_Sub(window, sprite, 0);
}
}

extern "C" {
void menuCB_tunaidePokemonSelect1_Disp_LD(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    menuCB_tunaidePokemonSelect1_Disp_Sub(window, sprite, 1);
}
}

extern "C" {
void menuCB_tunaidePokemonSelect1_Disp_RU(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (menuCB_GCStatusDispMode(sprite, 0)) {
        menuCB_tunaidePokemonSelect1_Disp_Sub(window, sprite, 2);
    }
}
}

extern "C" {
void menuCB_tunaidePokemonSelect1_Disp_RD(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (menuCB_GCStatusDispMode(sprite, 0)) {
        menuCB_tunaidePokemonSelect1_Disp_Sub(window, sprite, 3);
    }
}
}

static void menuCB_tunaidePokemonSelect1_Disp_Sub(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, u32 type) {
    switch (sprite->id) {
    case 0x3FA:
    case 0x427:
    case 0x454:
    case 0x481:
        menuCB_BattleEntryPokemonSelectDisp(sprite, type, 0x0);
        break;
    case 0x3FB:
    case 0x428:
    case 0x455:
    case 0x482:
        menuCB_BattleEntryPokemonSelectDisp(sprite, type, 0x1);
        break;
    case 0x3FC:
    case 0x429:
    case 0x456:
    case 0x483:
        menuCB_BattleEntryPokemonSelectDisp(sprite, type, 0x2);
        break;
    case 0x3FD:
    case 0x42A:
    case 0x457:
    case 0x484:
        menuCB_BattleEntryPokemonSelectDisp(sprite, type, 0x3);
        break;
    case 0x3FE:
    case 0x42B:
    case 0x458:
    case 0x485:
        menuCB_BattleEntryPokemonSelectDisp(sprite, type, 0x4);
        break;
    case 0x3FF:
    case 0x42C:
    case 0x459:
    case 0x486:
        menuCB_BattleEntryPokemonSelectDisp(sprite, type, 0x5);
        break;
    case 0x400:
    case 0x42D:
    case 0x45A:
    case 0x487:
        menuCBPokemonEntryDispPokemonFace(window, sprite, type, 0x0);
        break;
    case 0x401:
    case 0x42E:
    case 0x45B:
    case 0x488:
        menuCBPokemonEntryDispPokemonFace(window, sprite, type, 0x1);
        break;
    case 0x402:
    case 0x42F:
    case 0x45C:
    case 0x489:
        menuCBPokemonEntryDispPokemonFace(window, sprite, type, 0x2);
        break;
    case 0x403:
    case 0x430:
    case 0x45D:
    case 0x48A:
        menuCBPokemonEntryDispPokemonFace(window, sprite, type, 0x3);
        break;
    case 0x404:
    case 0x431:
    case 0x45E:
    case 0x48B:
        menuCBPokemonEntryDispPokemonFace(window, sprite, type, 0x4);
        break;
    case 0x405:
    case 0x432:
    case 0x45F:
    case 0x48C:
        menuCBPokemonEntryDispPokemonFace(window, sprite, type, 0x5);
        break;
    case 0x407:
    case 0x434:
    case 0x461:
    case 0x48E:
        menuCBPokemonEntryBallAnaDisp(sprite, type, 0x1);
        break;
    case 0x408:
    case 0x435:
    case 0x462:
    case 0x48F:
        menuCBPokemonEntryBallAnaDisp(sprite, type, 0x2);
        break;
    case 0x409:
    case 0x436:
    case 0x463:
    case 0x490:
        menuCBPokemonEntryBallAnaDisp(sprite, type, 0x3);
        break;
    case 0x40A:
    case 0x437:
    case 0x464:
    case 0x491:
        menuCBPokemonEntryBallAnaDisp(sprite, type, 0x4);
        break;
    case 0x40B:
    case 0x438:
    case 0x465:
    case 0x492:
        menuCBPokemonEntryBallAnaDisp(sprite, type, 0x5);
        break;
    case 0x40C:
    case 0x439:
    case 0x466:
    case 0x493:
        menuCBPokemonEntryBallAnaDisp(sprite, type, 0x6);
        break;
    case 0x40D:
    case 0x43A:
    case 0x467:
    case 0x494:
        menuCBPokemonEntryBallDisp(sprite, type, 0x1);
        break;
    case 0x40E:
    case 0x43B:
    case 0x468:
    case 0x495:
        menuCBPokemonEntryBallDisp(sprite, type, 0x2);
        break;
    case 0x40F:
    case 0x43C:
    case 0x469:
    case 0x496:
        menuCBPokemonEntryBallDisp(sprite, type, 0x3);
        break;
    case 0x410:
    case 0x43D:
    case 0x46A:
    case 0x497:
        menuCBPokemonEntryBallDisp(sprite, type, 0x4);
        break;
    case 0x411:
    case 0x43E:
    case 0x46B:
    case 0x498:
        menuCBPokemonEntryBallDisp(sprite, type, 0x5);
        break;
    case 0x412:
    case 0x43F:
    case 0x46C:
    case 0x499:
        menuCBPokemonEntryBallDisp(sprite, type, 0x6);
        break;
    case 0x413:
    case 0x440:
    case 0x46D:
    case 0x49A:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(type, 0x5));
        break;
    case 0x414:
    case 0x441:
    case 0x46E:
    case 0x49B:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(type, 0x4));
        break;
    case 0x415:
    case 0x442:
    case 0x46F:
    case 0x49C:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(type, 0x3));
        break;
    case 0x416:
    case 0x443:
    case 0x470:
    case 0x49D:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(type, 0x2));
        break;
    case 0x417:
    case 0x444:
    case 0x471:
    case 0x49E:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(type, 0x1));
        break;
    case 0x418:
    case 0x445:
    case 0x472:
    case 0x49F:
        menuCB_SpriteDispCheckONorOFF(sprite, menuCBPokemonGetItemDataId(type, 0x0));
        break;
    case 0x419:
    case 0x446:
    case 0x473:
    case 0x4A0:
        menuCB_SetSprite(sprite, menuSpriteBiosGetPtr(PlayerNumber[_CB.trainers[type].face]));
        break;
    case 0x41A:
    case 0x447:
    case 0x474:
    case 0x4A1:
        menuCBPokemonSexOnly(window, type, 0x5, 0x1);
        break;
    case 0x41B:
    case 0x448:
    case 0x475:
    case 0x4A2:
        menuCBPokemonSexOnly(window, type, 0x4, 0x1);
        break;
    case 0x41C:
    case 0x449:
    case 0x476:
    case 0x4A3:
        menuCBPokemonSexOnly(window, type, 0x3, 0x1);
        break;
    case 0x41D:
    case 0x44A:
    case 0x477:
    case 0x4A4:
        menuCBPokemonSexOnly(window, type, 0x2, 0x1);
        break;
    case 0x41E:
    case 0x44B:
    case 0x478:
    case 0x4A5:
        menuCBPokemonSexOnly(window, type, 0x1, 0x1);
        break;
    case 0x41F:
    case 0x44C:
    case 0x479:
    case 0x4A6:
        menuCBPokemonSexOnly(window, type, 0x0, 0x1);
        break;
    case 0x420:
    case 0x44D:
    case 0x47A:
    case 0x4A7:
        menuCBPokemonNameOnly(window, type, 0x5, 0x0);
        break;
    case 0x421:
    case 0x44E:
    case 0x47B:
    case 0x4A8:
        menuCBPokemonNameOnly(window, type, 0x4, 0x0);
        break;
    case 0x422:
    case 0x44F:
    case 0x47C:
    case 0x4A9:
        menuCBPokemonNameOnly(window, type, 0x3, 0x0);
        break;
    case 0x423:
    case 0x450:
    case 0x47D:
    case 0x4AA:
        menuCBPokemonNameOnly(window, type, 0x2, 0x0);
        break;
    case 0x424:
    case 0x451:
    case 0x47E:
    case 0x4AB:
        menuCBPokemonNameOnly(window, type, 0x1, 0x0);
        break;
    case 0x425:
    case 0x452:
    case 0x47F:
    case 0x4AC:
        menuCBPokemonNameOnly(window, type, 0x0, 0x0);
        break;
    case 0x426:
    case 0x453:
    case 0x480:
    case 0x4AD:
        toobattle_drawHeroNames(window, type);
        break;
    }
}

extern "C" {
void menuTool_Cursol_Ctrl(tagWINDOW_WORK* window) {
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF(window, _CB.unkB108 == 1);
}
}

extern "C" {
void menuTool_Cursol_Button(tagWINDOW_WORK* window) {
    if (_CB.unkB108 == 1) {
        if (_CB.unkB110 != 0) {
            _CB.unkB110--;
            return;
        }
        _CB.unkAFE0 = window->select;
        if (!pauseIsPause()) {
            if (windowGetKeyInfo()->trg & 0x10) {
                _CB.unkB060 = 1;
                return;
            }
            if (windowGetKeyInfo()->trg & 0x20) {
                _CB.unkAFE0 = 1;
                _CB.unkB060 = 1;
            }
        }
    }
}
}

extern "C" {
void menuCB_Cursol_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s32 country = pokecoloGetCountryCode();
    s16 sel;
    if (country != 0 && country >= 0 && country < 3) {
        s16 width = GSmsgGetRect(0x42FB) >> 16;
        s16 width2 = GSmsgGetRect(0x426A) >> 16;
        s16 width3 = GSmsgGetRect(0x3B2A) >> 16;
        if (width < width2) {
            width = width2;
        }
        if (width < width3) {
            width = width3;
        }
        switch (sprite->id) {
        case 0x4C7:
        case 0x4CA:
        case 0x4CD:
            sprite->x = width + 0x14;
            break;
        case 0x4C8:
        case 0x4CB:
        case 0x4CE:
            sprite->unk50 = width + 0x5E;
            break;
        }
    }
    switch (sprite->id) {
    case 0x4CF: {
        winSpriteSetDisp(sprite, 0);
        sel = window->select;
        if (sel >= 0) {
            menuSubDrawCursorBackAnimeOnOffAuto(window, winSpriteGetLayerID(window, sprite), 0, sel * 0x23, sprite->x, sprite->y,
                                                window->alpha, 1);
        }
    }
    case 0x4D1:
        sprite->msg = 0x426A;
        return;
    case 0x4D2:
        sprite->msg = 0x3B2A;
        return;
    case 0x4D0:
        sprite->msg = 0x42FB;
        return;
    }
}
}

extern "C" {
void menuTool_Rule00_Button(void) {
}
}

static void _menuCB_Rule_Page_Chenge_Init(void) {
    _CB.unkB124 = _CB.unkB118;
    _CB.unkB128 = 0xFF;
    _CB.unkB12C = 0xF;
}

static void menuCB_RuleCustomMainCursolColorChenge(tagSPRITE_WORK* sprite) {
    if (_CB.unkB11C != 0) {
        sprite->b = 0x7F;
        sprite->g = 0x7F;
        sprite->r = 0x7F;
        return;
    }
    sprite->b = 0xFF;
    sprite->g = 0xFF;
    sprite->r = 0xFF;
}

extern "C" {
void menuTool_Rule01_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(window, 0);
}
}

extern "C" {
void menuTool_Rule01_Button(void) {
}
}

extern "C" {
void menuTool_Rule02_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(window, 1);
}
}

extern "C" {
void menuTool_Rule02_Button(void) {
}
}

extern "C" {
void menuTool_Rule03_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(window, 2);
}
}

extern "C" {
void menuTool_Rule03_Button(void) {
}
}

extern "C" {
void menuCB_Rule03_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x34C:
        menuCBMessageYCenterDisp(window, sprite, 0x43D4);
        break;
    case 0x34D:
        menuCBMessageYCenterDisp(window, sprite, 0x43D5);
        break;
    case 0x34E:
        menuCBMessageYCenterDisp(window, sprite, 0x43D7);
        break;
    case 0x34F:
        menuCBMessageCenterDisp(window, sprite, 0x43E5);
        break;
    case 0x350:
        menuCBMessageCenterDisp(window, sprite, 0x43E6);
        break;
    case 0x351:
        menuCBMessageCenterDisp(window, sprite, 0x43E1);
        break;
    case 0x352:
        menuCBMessageCenterDisp(window, sprite, 0x43E2);
        break;
    case 0x353:
        menuCBMessageCenterDisp(window, sprite, 0x43E7);
        break;
    case 0x354:
        menuCBMessageCenterDisp(window, sprite, 0x43E8);
        break;
    case 0x33D:
    case 0x33E:
    case 0x33F:
        menuCB_RuleCustomMainCursolColorChenge(sprite);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB01C == 0);
        break;
    case 0x340:
    case 0x341:
    case 0x342:
        menuCB_RuleCustomMainCursolColorChenge(sprite);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB01C == 1);
        break;
    case 0x343:
    case 0x344:
    case 0x345:
        menuCB_RuleCustomMainCursolColorChenge(sprite);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB01C == 2);
        break;
    case 0x346:
        menuCB_RuleDispColorChenge(window, sprite, 0x30);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk9C78->f19 == 1);
        break;
    case 0x347:
        menuCB_RuleDispColorChenge(window, sprite, 0x30);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk9C78->f19 != 1);
        break;
    case 0x348:
        menuCB_RuleDispColorChenge(window, sprite, 0x31);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk9C78->f0E == 1);
        break;
    case 0x349:
        menuCB_RuleDispColorChenge(window, sprite, 0x31);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk9C78->f0E != 1);
        break;
    case 0x34A:
        menuCB_RuleDispColorChenge(window, sprite, 0x32);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk9C78->f10 != 1);
        break;
    case 0x34B:
        menuCB_RuleDispColorChenge(window, sprite, 0x32);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unk9C78->f10 == 1);
        break;
    }
}
}

extern "C" {
void menuTool_Rule04_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(window, 3);
}
}

extern "C" {
void menuTool_Rule04_Button(void) {
}
}

extern "C" {
void menuCB_Rule04_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x36D:
        menuCBMessageYCenterDisp(window, sprite, 0x43d8);
        break;
    case 0x36E:
        menuCBMessageYCenterDisp(window, sprite, 0x43d9);
        break;
    case 0x36F:
        menuCBMessageYCenterDisp(window, sprite, 0x43d6);
        break;
    case 0x370:
        menuCBMessageYCenterDisp(window, sprite, 0x43da);
        break;
    case 0x371:
        menuCBMessageCenterDisp(window, sprite, 0x43e7);
        break;
    case 0x372:
        menuCBMessageCenterDisp(window, sprite, 0x43e8);
        break;
    case 0x373:
        menuCBMessageCenterDisp(window, sprite, 0x43e7);
        break;
    case 0x374:
        menuCBMessageCenterDisp(window, sprite, 0x43e8);
        break;
    case 0x375:
        menuCBMessageCenterDisp(window, sprite, 0x43e1);
        break;
    case 0x376:
        menuCBMessageCenterDisp(window, sprite, 0x43e2);
        break;
    case 0x377:
        menuCBMessageCenterDisp(window, sprite, 0x43e7);
        break;
    case 0x378:
        menuCBMessageCenterDisp(window, sprite, 0x43e8);
        break;
    case 0x359:
    case 0x35A:
    case 0x35B:
        menuCB_RuleCustomMainCursolColorChenge(sprite);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB020 == 0));
        break;
    case 0x35C:
    case 0x35D:
    case 0x35E:
        menuCB_RuleCustomMainCursolColorChenge(sprite);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB020 == 1));
        break;
    case 0x35F:
    case 0x360:
    case 0x361:
        menuCB_RuleCustomMainCursolColorChenge(sprite);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB020 == 2));
        break;
    case 0x362:
    case 0x363:
    case 0x364:
        menuCB_RuleCustomMainCursolColorChenge(sprite);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB020 == 3));
        break;
    case 0x365:
        menuCB_RuleDispColorChenge(window, sprite, 0x40);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unk9C78->f11 == 1));
        break;
    case 0x366:
        menuCB_RuleDispColorChenge(window, sprite, 0x40);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unk9C78->f11 != 1));
        break;
    case 0x367:
        menuCB_RuleDispColorChenge(window, sprite, 0x41);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unk9C78->f12 != 1));
        break;
    case 0x368:
        menuCB_RuleDispColorChenge(window, sprite, 0x41);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unk9C78->f12 == 1));
        break;
    case 0x369:
        menuCB_RuleDispColorChenge(window, sprite, 0x42);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unk9C78->f0F == 1));
        break;
    case 0x36A:
        menuCB_RuleDispColorChenge(window, sprite, 0x42);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unk9C78->f0F != 1));
        break;
    case 0x36B:
        menuCB_RuleDispColorChenge(window, sprite, 0x43);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unk9C78->f13 != 1));
        break;
    case 0x36C:
        menuCB_RuleDispColorChenge(window, sprite, 0x43);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unk9C78->f13 == 1));
        break;
    }
}
}

extern "C" {
void menuTool_Rule05_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(window, 4);
}
}

extern "C" {
void menuTool_Rule05_Button(void) {
}
}

extern "C" {
void menuCB_Rule05_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x387:
        menuCBMessageCenterDisp(window, sprite, 0x4414);
        break;
    case 0x388:
        menuCBMessageYCenterDisp(window, sprite, 0x43DB);
        break;
    case 0x389:
        menuCBMessageYCenterDisp(window, sprite, 0x43DC);
        break;
    case 0x38A:
        menuCBMessageCenterDisp(window, sprite, 0x43E7);
        break;
    case 0x38B:
        menuCBMessageCenterDisp(window, sprite, 0x43E8);
        break;
    case 0x38C:
        menuCBMessageCenterDisp(window, sprite, 0x43E7);
        break;
    case 0x38D:
        menuCBMessageCenterDisp(window, sprite, 0x43E8);
        break;
    case 0x37C:
    case 0x37D:
    case 0x37E:
        menuCB_RuleCustomMainCursolColorChenge(sprite);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB024 == 0);
        break;
    case 0x37F:
    case 0x380:
    case 0x381:
        menuCB_RuleCustomMainCursolColorChenge(sprite);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB024 == 1);
        break;
    case 0x386:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB024 == 2);
        menuCB_RuleDispColorChenge_flag(window, sprite, 1);
        break;
    case 0x382:
        menuCB_RuleDispColorChenge(window, sprite, 0x50);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB030 == 0);
        break;
    case 0x383:
        menuCB_RuleDispColorChenge(window, sprite, 0x50);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB030 == 1);
        break;
    case 0x384:
        menuCB_RuleDispColorChenge(window, sprite, 0x51);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB034 == 0);
        break;
    case 0x385:
        menuCB_RuleDispColorChenge(window, sprite, 0x51);
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB034 == 1);
        break;
    }
}
}

extern "C" {
void menuTool_Rule06_Ctrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
    menuSetStatus(window->seq, 0x10);
    if (_CB.unkB130 != 0) {
        _CB.unkB134 += _CB.unkB130;
        if (_CB.unkB134 <= 0) {
            _CB.unkB134 = 0;
            _CB.unkB130 = 0;
        }
        if (_CB.unkB134 >= 0x1F4) {
            _CB.unkB134 = 0x1F4;
            _CB.unkB130 = 0;
        }
    }
    window->value = _CB.unkB134;
}
}

extern "C" {
void menuTool_Rule06_Button(void) {
}
}

extern "C" {
void menuCB_Rule06_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x39A:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB028 != 0));
        break;
    case 0x39B:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB028 != 52));
        break;
    case 0x39C:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 0));
        break;
    case 0x39D:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 1));
        break;
    case 0x39E:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 2));
        break;
    case 0x39F:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 3));
        break;
    case 0x3A0:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 4));
        break;
    case 0x3A1:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 5));
        break;
    case 0x3A2:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 6));
        break;
    case 0x3A3:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 7));
        break;
    case 0x3A4:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 8));
        break;
    case 0x3A5:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 9));
        break;
    case 0x3A6:
        menuCB_RuleDispColorChenge(window, sprite, 0x21);
        menuCB_SpriteDispCheckONorOFF(sprite, (_CB.unkB02C == 10));
        break;
    case 0x3AD:
        menuCB_RuleItemFlagDisp(window);
        break;
    case 0x3AF:
        menuCB_RuleItemNameEntry(window);
        break;
    case 0x3AE:
        menuCBMessageCenterDisp(window, sprite, 0x4415);
        break;
    }
}
}

extern "C" {
void menuTool_MASK_Ctrl(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x189);
            window->seqSet = 1;
        }
        break;
    case 3:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x191);
            window->seqSet = 1;
            spriteClearScissor(window->sprites);
        }
        break;
    }
}
}

extern "C" {
void menuTool_FlashCtrl(tagWINDOW_WORK* window) {
    menuCB_DispEffect(window);
}
}

extern "C" {
void menuCB_Flash01_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x4C4:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB13C == 0);
        if (_CB.unkB13C != 0) {
            _CB.unkB13C--;
        }
        break;
    }
}
}

extern "C" {
void menuCB_Flash02_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x4C5:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB140 == 0);
        if (_CB.unkB140 != 0) {
            _CB.unkB140--;
        }
        break;
    }
}
}

extern "C" {
void menuCB_Flash_gba_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (_CB.unkB168 == 2) {
        switch (_CB.unkB16C) {
        case 0:
            FlashSystemSetPlayFrameLabel(0x214D3000, "01", "01");
            FlashSystemSetNowFrameLabel(0x214D3000, "01");
            _CB.unkB168--;
            break;
        case 1:
            FlashSystemSetPlayFrameLabel(0x214D3000, "02", "02");
            FlashSystemSetNowFrameLabel(0x214D3000, "02");
            _CB.unkB168--;
            break;
        case 2:
            FlashSystemSetPlayFrameLabel(0x214D3000, "03", "03");
            FlashSystemSetNowFrameLabel(0x214D3000, "03");
            _CB.unkB168--;
            break;
        case 3:
            FlashSystemSetPlayFrameLabel(0x214D3000, "04", "04");
            FlashSystemSetNowFrameLabel(0x214D3000, "04");
            _CB.unkB168--;
            break;
        default:
            winSpriteSetDisp(sprite, 0);
            return;
        }
        FlashSystemSetLoopFlag(0x214D3000, true);
    }
    s32 state = gbaConectGBA_Connect_WORK.state[_CB.unkB16C];
    if (state != 3 && state != 4) {
        winSpriteSetDisp(sprite, 0);
        return;
    }
    switch (sprite->id) {
    case 0x5ED:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB168 == 0);
        if (_CB.unkB168 != 0) {
            _CB.unkB168--;
        }
        break;
    }
}
}

extern "C" {
void menuCB_Flash_VS_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (_CB.unkB174 != 0) {
        FlashSystemSetPlayFrameLabel(0x21533000, "end_keep", "end");
        FlashSystemSetNowFrameLabel(0x21533000, "end_keep");
        _CB.unkB174 = 0;
    }
    switch (sprite->id) {
    case 0x5F2:
    case 0x5F3:
    case 0x5F4:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB170 == 0);
        if (_CB.unkB170 != 0) {
            _CB.unkB170--;
        }
        break;
    }
}
}

extern "C" {
void menuCB_Flash_WINLOSE_Disp(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x5EE:
        menuCB_SpriteDispCheckONorOFF(sprite, _CB.unkB178 == 0);
        if (_CB.unkB178 != 0) {
            _CB.unkB178--;
        }
        break;
    }
}
}

extern "C" {
void menuTool_tunaideGCEntry02_1_Ctrl(tagWINDOW_WORK* window) {
    menuCB_MenuDispCheckONorOFF(window, _CB.unkB150 != 0);
    window->value = 0x180;
    if (_CB.unkB150 != 0 && _CB.unkB15C == 1) {
        window->value = _CB.unkB154;
    }
}
}

extern "C" {
void menuTool_tunaideGCEntry04_1_Ctrl(tagWINDOW_WORK* window) {
    menuCB_MenuDispCheckONorOFF(window, _CB.unkB150 != 0);
    window->value = 0x180;
    if (_CB.unkB150 != 0 && _CB.unkB15C == 2) {
        window->value = _CB.unkB154;
    }
}
}

extern "C" {
void menuTool_tunaideGCEntry03_1_Ctrl(tagWINDOW_WORK* window) {
    menuCB_MenuDispCheckONorOFF(window, _CB.unkB150 != 0);
    window->value = 0x180;
    if (_CB.unkB150 != 0 && _CB.unkB15C == 0) {
        window->value = _CB.unkB154;
    }
}
}
