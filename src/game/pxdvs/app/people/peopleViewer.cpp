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

#pragma pool_strings off
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
struct GSgfxLayer;
struct GSlight;
struct GSvec;
struct GXColor { u8 r, g, b, a; };
struct Hero;
struct PeopleInfo;
struct PeopleWork;
struct Vec;
struct _GSmodel;
struct _struct_motiontype_str_0x20;
struct tagPeopleWork;

extern "C" {

extern "C++" {
struct GSgfxLayer {
    u8 _draft[1];
};
struct GSlight {
    u8 _draft[1];
};
struct GSvec {
    f32 x, y, z;
    GSvec() {}
    GSvec(f32 _x, f32 _y, f32 _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};
struct Hero {
    u8 _draft[1];
    static Hero* getHeroPtr();
    u32 getFollowerResID();
    u32 getFollowerGrpID();
};
struct PeopleInfo {
    u8 _draft[1];
};
struct PeopleWork {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
};
struct _GSmodel {
    u8 _draft[1];
};
struct _struct_motiontype_str_0x20 {
    char name[0x20];
};
struct tagPeopleWork {
    u8 _draft[1];
};
struct _struct_anim_str_0x28 {
    u32 id;
    u32 unk4;
    char name[0x20];
};
struct _struct_char_tbl_0xC {
    u32 id;
    s32 unk4;
    const char* name;
};
extern "C" {
s32 GSfloorGetCurrent(void);
int GSgfxLayerFindByID(int id);
u8 GSgfxVideoGetVsyncRate(void);
u32 GSinputButtonsChanged(s32 pad);
u32 GSinputButtonsPressed(s32 pad);
void GSlightSetColor(GSlight* light, const GXColor* color);
f32 GSmodelGetAnimFrame(_GSmodel* model);
void GSmodelGetAnimIndex(_GSmodel* model, u32* index, u32* blendIndex);
s32 GSmodelGetAnimType(_GSmodel* model);
void GSmodelGetFrameCount(_GSmodel* model, f32* count, f32* blendCount);
u8 GSmodelIsAnimating(_GSmodel* model);
void GSmodelSetAnimIndex(_GSmodel* model, u32 index);
void GSmodelStartAnimation(_GSmodel* model);
void GSmodelStopAnimation(_GSmodel* model);
void GSprimDraw2DQuad(GXColor color, f32 x, f32 y, f32 w, f32 h);
void GSprimSetBlendMode(s32 mode);
void GSthreadSwitch(void);
f32 PSVECDistance(const register Vec* a, const register Vec* b);
u8 cameraSetType(u8 type);
s32 dbgMenuIsOpen(void);
void gimmickBoxDrawFloat(s32, s32, f32);
s32 gimmickBoxDrawInt(s32, s32, s32);
s32 gimmickBoxDrawString(s32, s32, struct _struct_motiontype_str_0x20*);
f32 gimmickBoxGetFrameCount(f32*, s32);
s32 gimmickSetMotion(s32, s32, s32, s32, s32);
void* lightGetLight(s32 index);
void peopleBiosGetPos(PeopleWork* work, GSvec* out);
void* peopleBiosGetPosPtr(PeopleWork* work);
f32* peopleBiosGetPrevPosPtr(PeopleWork* work);
void peopleBiosSetFlagOff(PeopleWork* work, u32 flags);
void peopleBiosSetRot(PeopleWork* work, void* rotation);
u32 peopleGetHumanID(s32, s32);
void peopleGetPos(s32, s32, GSvec*);
s32 peopleGetRot(s32, s32, s32*);
PeopleInfo* peopleInfoBiosGetPtr(u32 modelResID);
f32 peopleInfoBiosGetRunLength(PeopleInfo* info);
f32 peopleInfoBiosGetWalkLength(PeopleInfo* info);
void peopleMoveNeckTarget(s32, s32, s32, s32, f32);
void peoplePartAnimationBlinkOnce(tagPeopleWork* people);
void peoplePartAnimationBlinkStart(tagPeopleWork* people);
void peoplePartAnimationBlinkStop(tagPeopleWork* people);
void peoplePartAnimationSpeakStart(tagPeopleWork* people);
void peoplePartAnimationSpeakStop(tagPeopleWork* people);
void peopleReadObject(s32, s32, s32);
void peopleRemoveNeckTarget(s32, s32, f32);
f32* peopleSearchID();
void peopleSetDisp(s32, s32, u8);
void peopleSetFlagOff(s32, s32, s32);
void peopleSetMotion(u32, u32, u32, u32, u32);
s32 peopleSetPos(s32, s32, f32*);
void peopleSetRot(s32, s32, GSvec*);
s32 peopleViewerDisplayAnimRate(s32* pw, f32 p0);
s32 peopleViewerDisplayMoveRotInfo(s32* pw, f32 p0);
s32 peopleViewerDisplayRandWalk(void *p0);
bool peopleViewerIsCheckNpc(s32 *p0);
void peopleViewerThread();
int sprintf(char* s, const char* format, ...);
u32 timeGetLastFrameTime(void);
extern s32 init;
}
extern "C++" {
void GSprimSetup2DRender(GSgfxLayer* layer);
static void _peopleViewerDrawParams();
static s32 _peopleViewerFallMotion();
static void _peopleViewerFallReady(float p0);
static struct _struct_motiontype_str_0x20* _peopleViewerGetActName(long p0);
static void _peopleViewerGetWalkAndRunInfo();
static void _peopleViewerInitChara();
static void _peopleViewerInit();
static void _peopleViewerMain();
static void _peopleViewerStartAnimation();
static void _setAnimIndex(_GSmodel* p0, int p1);
}
static GSvec init_chara_pos(0.0f, 0.0f, 0.0f);
static GSvec init_chara_rot(0.0f, 0.0f, 0.0f);
static GSvec init_hero_pos(0.0f, 0.0f, 6.0f);
static GSvec init_hero_rot(0.0f, 0.0f, 0.0f);
static struct _struct_char_tbl_0xC char_tbl[0xb9] = {
    {0x260, 0x16c50400, "SNATCHDAN_0000"},
    {0x261, 0x16c60400, "SNATCHDAN_0100"},
    {0x262, 0x16c70400, "MANA_0000"},
    {0x263, 0x16c80400, "MANA_0100"},
    {0x264, 0x16c90400, "RINTO_0000"},
    {0x313, 0x18c90400, "AGENT1_F_0000"},
    {0x314, 0x19170400, "AGENT1_F_0100"},
    {0x315, 0x19180400, "AGENT1_M_0000"},
    {0x316, 0x19190400, "AGENT1_M_0100"},
    {0x317, 0x191a0400, "AGENT2_M_0000"},
    {0x318, 0x191b0400, "AGENT2_M_0100"},
    {0x319, 0x191c0400, "AGENT3_M_0000"},
    {0x31a, 0x191d0400, "AGENT3_M_0100"},
    {0x31b, 0x191e0400, "ARDOS_0000"},
    {0x31c, 0x191f0400, "ARDOS_0100"},
    {0x31d, 0x19200400, "BABA1_0000"},
    {0x31e, 0x19220400, "BABA1_0100"},
    {0x31f, 0x19230400, "BARTEN_0000"},
    {0x320, 0x19240400, "BIGBOSS_0000"},
    {0x321, 0x19250400, "BIGBOSS_0100"},
    {0x322, 0x19260400, "BIGBOSS_1000"},
    {0x323, 0x19270400, "BIGBOSS_1100"},
    {0x324, 0x19280400, "BOY_0000"},
    {0x325, 0x19290400, "CASTER_A_0000"},
    {0x326, 0x192a0400, "CASTER_A_0100"},
    {0x327, 0x192b0400, "DR_FAD_0000"},
    {0x328, 0x192c0400, "DR_FAD_0100"},
    {0x329, 0x192d0400, "ELDES_0000"},
    {0x32a, 0x192e0400, "ELDES_0100"},
    {0x32b, 0x192f0400, "GADERI_0000"},
    {0x32c, 0x19300400, "GADERI_0100"},
    {0x32d, 0x19310400, "GBA_EMR_F_0100"},
    {0x32e, 0x19320400, "GBA_EMR_M_0100"},
    {0x32f, 0x19330400, "GBA_FL_F_0100"},
    {0x330, 0x19340400, "GBA_FL_M_0100"},
    {0x331, 0x19360400, "GBA_RS_F_0100"},
    {0x332, 0x19370400, "GBA_RS_M_0100"},
    {0x333, 0x19380400, "GINZARU_0000"},
    {0x334, 0x19390400, "GINZARU_0100"},
    {0x335, 0x193a0400, "GIRL_0000"},
    {0x336, 0x195a0400, "GIRL_1100"},
    {0x337, 0x193b0400, "GONZA_0000"},
    {0x338, 0x193c0400, "GONZA_0100"},
    {0x339, 0x193d0400, "GYM_F_0000"},
    {0x33a, 0x193e0400, "GYM_F_1000"},
    {0x33b, 0x19420400, "GYM_F_1100"},
    {0x33c, 0x19430400, "GYMA_M_0000"},
    {0x33d, 0x19440400, "GYMA_M_1000"},
    {0x33e, 0x19450400, "GYMA_M_1100"},
    {0x33f, 0x19460400, "GYMA_M_2000"},
    {0x340, 0x19470400, "GYMA_M_2100"},
    {0x341, 0x1a780400, "GYMA_M_3000"},
    {0x342, 0x1a790400, "GYMA_M_3100"},
    {0x343, 0x1a7a0400, "GYMB_M_0000"},
    {0x344, 0x19480400, "GYMB_M_0100"},
    {0x345, 0x19490400, "GYMB_M_1000"},
    {0x346, 0x194a0400, "GYMB_M_1100"},
    {0x347, 0x197b0400, "GYMB_M_2000"},
    {0x348, 0x1ad30400, "GYMB_M_2100"},
    {0x349, 0x1ad40400, "HEBOY_0000"},
    {0x34a, 0x1ad50400, "HEBOY_0100"},
    {0x34b, 0x1ad80400, "HEXA_0000"},
    {0x34c, 0x15ec0400, "HEXA_0100"},
    {0x34d, 0x1a630400, "HEXA_1000"},
    {0x34e, 0x1a640400, "HEXA_1100"},
    {0x34f, 0x1a650400, "HEXA_2000"},
    {0x350, 0x1a660400, "HEXA_2100"},
    {0x351, 0x1a670400, "HEXA_3000"},
    {0x352, 0x1a680400, "HEXA_3100"},
    {0x353, 0x1a690400, "HEXA_4000"},
    {0x354, 0x1a6a0400, "HEXA_4100"},
    {0x355, 0x1a6b0400, "HEXA_5000"},
    {0x356, 0x1a6c0400, "HEXA_5100"},
    {0x357, 0x1a6d0400, "HUNTER_F_0000"},
    {0x358, 0x1a6e0400, "HUNTER_F_0100"},
    {0x359, 0x1a6f0400, "INFO_0000"},
    {0x35a, 0x1a700400, "IPPAN_F_0000"},
    {0x35b, 0x1a710400, "IPPAN_F_0100"},
    {0x35c, 0x1a720400, "IPPAN_M_0000"},
    {0x35d, 0x1a730400, "IPPAN_M_0100"},
    {0x35e, 0x1a740400, "JIJI1_0000"},
    {0x35f, 0x1a750400, "JIJI1_0100"},
    {0x360, 0x1a760400, "JIJI2_0000"},
    {0x361, 0x171c0400, "JUGGLER_0000"},
    {0x362, 0x1a7b0400, "JUGGLER_0100"},
    {0x363, 0x1a7c0400, "KLEIN_0000"},
    {0x364, 0x1a7d0400, "KLEIN_0100"},
    {0x365, 0x1a7e0400, "KURO_0000"},
    {0x366, 0x1a7f0400, "KURO_0100"},
    {0x367, 0x1a800400, "LAYLA_0000"},
    {0x368, 0x1a830400, "LAYLA_0100"},
    {0x369, 0x1ade0400, "LILYA_0000"},
    {0x36a, 0x1adf0400, "LILYA_0100"},
    {0x36b, 0x1ae00400, "LOGAN_0000"},
    {0x36c, 0x1ae40400, "LOGAN_0100"},
    {0x36d, 0x1ae50400, "MAGE_0000"},
    {0x36e, 0x1ae60400, "MAGE_0100"},
    {0x36f, 0x18540400, "MAGIC_0000"},
    {0x370, 0x18550400, "MAGIC_1000"},
    {0x371, 0x16c70400, "MANA_0000"},
    {0x372, 0x16c80400, "MANA_0100"},
    {0x373, 0x171d0400, "MASTER_0000"},
    {0x374, 0x171e0400, "MCGROUDON_0100"},
    {0x375, 0x15ed0400, "MCGROUDON_1100"},
    {0x376, 0x15ee0400, "MIRRABO_0000"},
    {0x377, 0x15ef0400, "MIRRABO_0100"},
    {0x378, 0x15f00400, "NIKU_F_0000"},
    {0x379, 0x15f20400, "NIKU_F_0100"},
    {0x37a, 0x15f30400, "NIKU_M_0000"},
    {0x37b, 0x15f40400, "NIKU_M_0100"},
    {0x37c, 0x15f50400, "NIKU_M_1000"},
    {0x37d, 0x15f60400, "NIKU_M_1100"},
    {0x37e, 0x15f70400, "OBASAN_0000"},
    {0x37f, 0x15f80400, "OBO_0000"},
    {0x380, 0x15f90400, "OBO_0100"},
    {0x381, 0x15fa0400, "OJISAN1_0000"},
    {0x382, 0x15fb0400, "OJISAN1_0100"},
    {0x383, 0x15fc0400, "OJISAN2_0000"},
    {0x384, 0x160a0400, "OJO_0000"},
    {0x385, 0x160b0400, "OJO_0100"},
    {0x386, 0x16920400, "OJO_1000"},
    {0x387, 0x16930400, "OJO_1100"},
    {0x388, 0x16940400, "PC_F_0000"},
    {0x389, 0x16950400, "PC_F_1000"},
    {0x38a, 0x16960400, "REN_0000"},
    {0x38b, 0x16970400, "REN_0100"},
    {0x38c, 0x16980400, "RESEARCH_F_0000"},
    {0x38d, 0x16990400, "RESEARCH1_M_0000"},
    {0x38e, 0x169a0400, "RESEARCH2_M_0000"},
    {0x38f, 0x169b0400, "RESEARCH2_M_0100"},
    {0x390, 0x169c0400, "RIDER_M_0100"},
    {0x391, 0x169d0400, "RIDER_M_1000"},
    {0x392, 0x16c90400, "RINTO_0000"},
    {0x393, 0x169e0400, "RINTO_0100"},
    {0x394, 0x169f0400, "RINTO_1000"},
    {0x395, 0x16a00400, "RINTO_1100"},
    {0x396, 0x16a10400, "SAILOR1_0000"},
    {0x397, 0x16a20400, "SAILOR1_0100"},
    {0x398, 0x16a30400, "SAILOR2_0000"},
    {0x399, 0x16a40400, "SAILOR2_0100"},
    {0x39a, 0x160f0400, "SAILOR2_1100"},
    {0x39b, 0x16a50400, "SAILOR3_0000"},
    {0x39c, 0x16a60400, "SAILOR3_0100"},
    {0x39d, 0x16a70400, "SEIGI_0000"},
    {0x39e, 0x16a80400, "SENSEI_0000"},
    {0x39f, 0x16a90400, "SENSEI_0100"},
    {0x3a0, 0x171f0400, "SETSUMA_0000"},
    {0x3a1, 0x17200400, "SHIHO_0000"},
    {0x3a2, 0x17210400, "SHIHO_0100"},
    {0x3a3, 0x17220400, "SHOP_M_0000"},
    {0x3a4, 0x17230400, "SILVER_0000"},
    {0x3a5, 0x17240400, "SILVER_0100"},
    {0x3a6, 0x17250400, "SLED_0000"},
    {0x3a7, 0x17260400, "SLED_0100"},
    {0x3a8, 0x16c50400, "SNATCHDAN_0000"},
    {0x3a9, 0x16c60400, "SNATCHDAN_0100"},
    {0x3aa, 0x17280400, "SPORT_F_0000"},
    {0x3ab, 0x17290400, "SPORT_F_0100"},
    {0x3ac, 0x172a0400, "SPORT_M_0000"},
    {0x3ad, 0x172b0400, "SPORT_M_0100"},
    {0x3ae, 0x17aa0400, "TESSLA_0000"},
    {0x3af, 0x17ab0400, "TESSLA_0100"},
    {0x3b0, 0x18070400, "THIEF_F_0000"},
    {0x3b1, 0x18080400, "THIEF_F_0100"},
    {0x3b2, 0x172c0400, "THIEF_F_1000"},
    {0x3b3, 0x172d0400, "THIEF_F_1100"},
    {0x3b4, 0x172e0400, "THIEF_M_1000"},
    {0x3b5, 0x17ac0400, "TOROY_0000"},
    {0x3b6, 0x17ad0400, "TOROY_0100"},
    {0x3b7, 0x172f0400, "TRAINER_F_0000"},
    {0x3b8, 0x177e0400, "TRAINER_F_0100"},
    {0x3b9, 0x177f0400, "TRAINER_M_0000"},
    {0x3ba, 0x17820400, "TRAINER_M_0100"},
    {0x3bb, 0x17830400, "TV_CREW_0000"},
    {0x3bc, 0x17c90400, "URANAI_0000"},
    {0x3bd, 0x17310400, "WARUGAKI_0000"},
    {0x3be, 0x17320400, "WARUGAKI_0100"},
    {0x3bf, 0x17330400, "WAZZLE_0000"},
    {0x3c0, 0x17340400, "WAZZLE_0100"},
    {0x3c1, 0x17350400, "WILLY_0000"},
    {0x3c2, 0x17810400, "WILLY_0100"},
    {0x3c3, 0x17840400, "WORKER_0000"},
    {0x3c4, 0x17850400, "WORKER_0100"},
    {0x3c5, 0x17860400, "ZACK_0000"},
    {0x3c6, 0x17870400, "ZACK_0100"},
};
static struct _struct_anim_str_0x28 anim_str[0x88] = {
    {0x275, 0x0, "STILL"},
    {0x276, 0x1, "BLINK_LOOP"},
    {0x277, 0x2, "SPEAK_LOOP"},
    {0x278, 0x3, "IDLE0_LOOP"},
    {0x279, 0x4, "WALK_START"},
    {0x27a, 0x5, "WALK_LOOP"},
    {0x27b, 0x6, "WALK_END"},
    {0x27c, 0x7, "RUN_START"},
    {0x27d, 0x8, "RUN_LOOP"},
    {0x27e, 0x9, "RUN_END"},
    {0x27f, 0xa, "SEAT_LOOP"},
    {0x280, 0xb, "CHAT1_START"},
    {0x281, 0xc, "CHAT1_LOOP"},
    {0x282, 0xd, "CHAT1_END"},
    {0x283, 0xe, "CHAT2_START"},
    {0x284, 0xf, "CHAT2_LOOP"},
    {0x285, 0x10, "CHAT2_END"},
    {0x286, 0x11, "DUEL_START"},
    {0x287, 0x12, "DUEL_LOOP"},
    {0x288, 0x13, "IDLE_1"},
    {0x289, 0x14, "IDLE_2"},
    {0x28a, 0x15, "IDLE_3"},
    {0x28b, 0x16, "IDLE_4"},
    {0x28c, 0x17, "IDLE_5"},
    {0x28d, 0x18, "IDLE_6"},
    {0x28e, 0x19, "IDLE_7"},
    {0x28f, 0x1a, "IDLE_8"},
    {0x290, 0x1b, "IDLE_9"},
    {0x291, 0x1c, "IDLE_10"},
    {0x292, 0x1d, "IDLE_11"},
    {0x293, 0x1e, "IDLE_12"},
    {0x294, 0x1f, "BPUSH_START"},
    {0x295, 0x20, "BPUSH_LOOP"},
    {0x296, 0x21, "BPUSH_END"},
    {0x297, 0x22, "FALL_1"},
    {0x298, 0x23, "CRANE_START"},
    {0x299, 0x24, "CRANE_LOOP"},
    {0x29a, 0x25, "CRANE_END"},
    {0x29b, 0x26, "FALL_2_START"},
    {0x29c, 0x27, "FALL_2_LOOP"},
    {0x29d, 0x28, "FALL_2_END"},
    {0x29e, 0x29, "SIDESTEP_L"},
    {0x29f, 0x2a, "SIDESTEP_R"},
    {0x2a0, 0x2b, "BACKWALK_LOOP"},
    {0x2a1, 0x2c, "RIGHT_TURN"},
    {0x2a2, 0x2d, "LEFT_TURN"},
    {0x2a3, 0x37, "B_IDLE"},
    {0x2a4, 0x38, "B_THROW"},
    {0x2a5, 0x39, "B_APPEAL"},
    {0x2a6, 0x3a, "B_WIN_START"},
    {0x2a7, 0x3b, "B_WIN_LOOP"},
    {0x2a8, 0x3c, "B_DEFEAT_START"},
    {0x2a9, 0x3d, "B_DEFEAT_LOOP"},
    {0x2aa, 0x3e, "B_SNATCH"},
    {0x2ab, 0x3f, "B_DETECT"},
    {0x2ac, 0x40, "B_WORRY"},
    {0x2ae, 0x4b, "EVT_01"},
    {0x2af, 0x4c, "EVT_02"},
    {0x2b0, 0x4d, "EVT_03"},
    {0x2b1, 0x4e, "EVT_04"},
    {0x2b2, 0x4f, "EVT_05"},
    {0x2b3, 0x50, "EVT_06"},
    {0x2b4, 0x51, "EVT_07"},
    {0x2b5, 0x52, "EVT_08"},
    {0x2b6, 0x53, "EVT_09"},
    {0x2b7, 0x54, "EVT_10"},
    {0x2b8, 0x55, "EVT_11"},
    {0x2b9, 0x56, "EVT_12"},
    {0x2ba, 0x57, "EVT_13"},
    {0x2bb, 0x58, "EVT_14"},
    {0x2bc, 0x59, "EVT_15"},
    {0x2bd, 0x5a, "EVT_16"},
    {0x2be, 0x5b, "EVT_17"},
    {0x2bf, 0x5c, "EVT_18"},
    {0x2c0, 0x5d, "EVT_19"},
    {0x2c1, 0x5e, "EVT_20"},
    {0x2c2, 0x5f, "EVT_21"},
    {0x2c3, 0x60, "EVT_22"},
    {0x2c4, 0x61, "EVT_23"},
    {0x2c5, 0x62, "EVT_24"},
    {0x2c6, 0x63, "EVT_25"},
    {0x2c7, 0x64, "EVT_26"},
    {0x2c8, 0x65, "EVT_27"},
    {0x2c9, 0x66, "EVT_28"},
    {0x2ca, 0x67, "EVT_29"},
    {0x2cb, 0x68, "EVT_30"},
    {0x2cc, 0x69, "EVT_31"},
    {0x2cd, 0x6a, "EVT_32"},
    {0x2ce, 0x6b, "EVT_33"},
    {0x2cf, 0x6c, "EVT_34"},
    {0x2d0, 0x6d, "EVT_35"},
    {0x2d1, 0x6e, "EVT_36"},
    {0x2d2, 0x6f, "EVT_37"},
    {0x2d3, 0x70, "EVT_38"},
    {0x2d4, 0x71, "EVT_39"},
    {0x2d5, 0x72, "EVT_40"},
    {0x2d6, 0x73, "EVT_41"},
    {0x2d7, 0x74, "EVT_42"},
    {0x2d8, 0x75, "EVT_43"},
    {0x2d9, 0x76, "EVT_44"},
    {0x2da, 0x77, "EVT_45"},
    {0x2db, 0x78, "EVT_46"},
    {0x2dc, 0x79, "EVT_47"},
    {0x2dd, 0x7a, "EVT_48"},
    {0x2de, 0x7b, "EVT_49"},
    {0x2df, 0x7c, "EVT_50"},
    {0x2e0, 0x7d, "EVT_51"},
    {0x2e1, 0x7e, "EVT_52"},
    {0x2e2, 0x7f, "EVT_53"},
    {0x2e3, 0x80, "EVT_54"},
    {0x2e4, 0x81, "EVT_55"},
    {0x2e5, 0x82, "EVT_56"},
    {0x2e6, 0x83, "EVT_57"},
    {0x2e7, 0x84, "EVT_58"},
    {0x2e8, 0x85, "EVT_59"},
    {0x2e9, 0x86, "EVT_60"},
    {0x2ea, 0x87, "EVT_61"},
    {0x2eb, 0x88, "EVT_62"},
    {0x2ec, 0x89, "EVT_63"},
    {0x2ed, 0x8a, "EVT_64"},
    {0x2ee, 0x8b, "EVT_65"},
    {0x2ef, 0x8c, "EVT_66"},
    {0x2f0, 0x8d, "EVT_67"},
    {0x2f1, 0x8e, "EVT_68"},
    {0x2f2, 0x8f, "EVT_69"},
    {0x2f3, 0x90, "EVT_70"},
    {0x2f4, 0x91, "EVT_71"},
    {0x2f5, 0x92, "EVT_72"},
    {0x2f6, 0x93, "EVT_73"},
    {0x2f7, 0x94, "EVT_74"},
    {0x2f8, 0x95, "EVT_75"},
    {0x2f9, 0x96, "EVT_76"},
    {0x2fa, 0x97, "EVT_77"},
    {0x2fb, 0x98, "EVT_78"},
    {0x2fc, 0x99, "EVT_79"},
    {0x2fd, 0x9a, "EVT_80"},
};
static struct _struct_motiontype_str_0x20 motiontype_str[5] = {
    {"OnTheSpot"},
    {"Walk"},
    {"Run"},
    {"RamdomWalk"},
    {"Fall"},
};
static u8 m_b_change_chara;
static s32 m_char_number;
static tagPeopleWork* m_pChara;
static f32* m_pKen;
static PeopleInfo* m_pCharaInfo;
static f32 m_fall_start_anim_num;
static f32 m_fall_loop_anim_num;
static f32 m_fall_end_anim_num;
static f32 m_fall_end_frame_count;
static f32 m_fall_height;
static f32 m_fall_speed;
static s32 m_current_motion_type;
static u32 m_anim_number;
static u8 m_b_rinto_disp;
static u8 m_b_play_stop;
static u8 m_b_speak_mode;
static s8 m_walk_parameter_str[0x100];
static s8 m_run_parameter_str[0x100];
static f32 m_play_speed_rate = 1.0f;
extern "C++" {

extern "C++" {

extern "C" {
s32 peopleViewerDisplayDaemonInfo(void *p0);
void peopleViewerSetHeroPos();
}
}
}
}
}

extern "C++" {
#pragma push
}

extern "C++" {
#pragma peephole off
}

extern "C++" {
#pragma pop
}

extern "C" {
static inline f32 _pvDist(Vec* a, Vec* b) {
    return PSVECDistance(a, b);
}
}
extern "C++" static void _peopleViewerInitChara();
extern "C++" static s32 _peopleViewerFallMotion();
extern "C++" static void _peopleViewerFallReady(float height);
extern "C" void peopleViewerThread();
extern "C++" static void _peopleViewerInit();
extern "C++" static void _peopleViewerMain();
extern "C" void peopleViewerSetHeroPos();
extern "C++" static void _peopleViewerGetWalkAndRunInfo();
extern "C++" static struct _struct_motiontype_str_0x20* _peopleViewerGetActName(long id);
extern "C++" static void _peopleViewerDrawParams();
extern "C" s32 peopleViewerDisplayDaemonInfo(void *p0);
extern "C" s32 peopleViewerDisplayRandWalk(void *p0);
extern "C" s32 peopleViewerDisplayMoveRotInfo(s32* pw, f32 p0);
extern "C" s32 peopleViewerDisplayAnimRate(s32* pw, f32 p0);
extern "C" bool peopleViewerIsCheckNpc(s32 *p0);
extern "C" f32 peopleViewerGetPlaySpeedRate(void);
extern "C++" static void _peopleViewerStartAnimation();
extern "C" void peopleViewerSetPlaySpeedRate(f32 value);
extern "C++" static void _setAnimIndex(_GSmodel* p0, int p1);

extern "C++" {
static void _setAnimIndex(_GSmodel* p0, int p1) {
    GSmodelSetAnimIndex((_GSmodel*)(p0), (u32) p1);
}
}

extern "C" {
void peopleViewerSetPlaySpeedRate(f32 value) {
    m_play_speed_rate = value;
}
}

extern "C++" {
static void _peopleViewerStartAnimation() {
    u32 spC;
    u32 sp8;

    GSmodelGetAnimIndex((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)), (u32*)(&spC), (u32*)(&sp8));
    _setAnimIndex((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)), (s32) spC);
    GSmodelStartAnimation((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)));
}
}

extern "C" {
f32 peopleViewerGetPlaySpeedRate(void) {
    return m_play_speed_rate;
}
}

extern "C" {
bool peopleViewerIsCheckNpc(s32 *p0) {
    if (GSfloorGetCurrent() != 0xFA1U) {
        return false;
    }
    return M2C_FIELD(p0, s32 *, 0x18) == 0;
}
}

extern "C" {
s32 peopleViewerDisplayAnimRate(s32* pw, f32 p0) {
    if (peopleViewerIsCheckNpc(pw) == 0) {
        return 0;
    }
    gimmickBoxDrawString((long)(0x1E), (long)(5), (_struct_motiontype_str_0x20 *)("animRate"));
    gimmickBoxDrawFloat(0x26, 5, p0);
    return 1;
}
}

extern "C" {
s32 peopleViewerDisplayMoveRotInfo(s32* pw, f32 p0) {
    if (peopleViewerIsCheckNpc(pw) == 0) {
        return 0;
    }
    gimmickBoxDrawString((long)(0x1E), (long)(0xB), (_struct_motiontype_str_0x20 *)("dest_diff_rot"));
    gimmickBoxDrawFloat(0x28, 0xB, p0);
    return 1;
}
}

extern "C" {
s32 peopleViewerDisplayRandWalk(void *p0) {
    if (peopleViewerIsCheckNpc((s32 *) p0) == 0) {
        return 0;
    }
    gimmickBoxDrawString((long)(0), (long)(6), (_struct_motiontype_str_0x20 *)("randWait"));
    gimmickBoxDrawFloat(0xA, 6, M2C_FIELD(p0, f32 *, 0x90));
    if ((p0 != NULL) && ((_GSmodel *) M2C_FIELD(p0, _GSmodel **, 8) != NULL)) {
        gimmickBoxDrawString((long)(0), (long)(7), (_struct_motiontype_str_0x20 *)("AnimFrame"));
        gimmickBoxDrawFloat(0xA, 7, GSmodelGetAnimFrame((_GSmodel*)(M2C_FIELD(p0, _GSmodel **, 8))));
    }
    return 1;
}
}

extern "C" {
s32 peopleViewerDisplayDaemonInfo(void *p0) {
    if (peopleViewerIsCheckNpc((s32 *) p0) == 0) {
        return 0;
    }
    gimmickBoxDrawString(0x1E, 3, (_struct_motiontype_str_0x20 *)("moveSpeed"));
    gimmickBoxDrawFloat(0x26, 3, M2C_FIELD(p0, f32 *, 0x28));
    gimmickBoxDrawString(0x1E, 4, (_struct_motiontype_str_0x20 *)("realDist"));
    gimmickBoxDrawFloat(0x26, 4, _pvDist((Vec*)peopleBiosGetPosPtr((PeopleWork*)p0), (Vec*)peopleBiosGetPrevPosPtr((PeopleWork*)p0)));
    gimmickBoxDrawString(0x1E, 7, (_struct_motiontype_str_0x20 *)("neck rot"));
    gimmickBoxDrawFloat(0x26, 7, M2C_FIELD(p0, f32 *, 0xE0));
    gimmickBoxDrawFloat(0x26, 8, M2C_FIELD(p0, f32 *, 0xE4));
    gimmickBoxDrawFloat(0x26, 9, M2C_FIELD(p0, f32 *, 0xE8));
    gimmickBoxDrawString(0x1E, 0xD, (_struct_motiontype_str_0x20 *)("pos"));
    gimmickBoxDrawFloat(0x26, 0xE, ((GSvec*)peopleBiosGetPosPtr((PeopleWork*)p0))->x);
    gimmickBoxDrawFloat(0x26, 0xF, ((GSvec*)peopleBiosGetPosPtr((PeopleWork*)p0))->y);
    gimmickBoxDrawFloat(0x26, 0x10, ((GSvec*)peopleBiosGetPosPtr((PeopleWork*)p0))->z);
    return 1;
}
}

extern "C++" {
static void _peopleViewerDrawParams() {
    u32 sp10;
    u32 spC;
    s32 sp8;
    s32 temp_r3;

    GSprimSetup2DRender((GSgfxLayer*)(GSgfxLayerFindByID(7)));
    GSprimSetBlendMode(1);
    GXColor back = {0x20, 0x20, 0xFF, 0x20};
    GSprimDraw2DQuad(back, 10.0f, 10.0f, 630.0f, 72.0f);
    gimmickBoxDrawString((long)(0), (long)(0), (_struct_motiontype_str_0x20 *)("Character"));
    gimmickBoxDrawString(0, 1, (struct _struct_motiontype_str_0x20*)char_tbl[m_char_number].name);
    gimmickBoxDrawInt(0, 2, m_char_number);
    gimmickBoxDrawString((long)(0xC), (long)(0), (_struct_motiontype_str_0x20 *)("Animation"));
    GSmodelGetAnimIndex((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)), (u32*)(&sp10), (u32*)(&spC));
    if ((s32) sp10 < 0) {
        gimmickBoxDrawString((long)(0xC), (long)(1), (_struct_motiontype_str_0x20 *)("NONE"));
    } else {
        gimmickBoxDrawString(0xC, 1, _peopleViewerGetActName((s32) sp10));
    }
    if ((s32) spC < 0) {
        gimmickBoxDrawString((long)(0xC), (long)(2), (_struct_motiontype_str_0x20 *)("NONE"));
    } else {
        gimmickBoxDrawString(0xC, 2, _peopleViewerGetActName((s32) spC));
    }
    temp_r3 = GSmodelGetAnimType((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)));
    if (temp_r3 == 1) {
        gimmickBoxDrawString((long)(0xC), (long)(3), (_struct_motiontype_str_0x20 *)("Loop"));
    } else if (temp_r3 == 0) {
        gimmickBoxDrawString((long)(0xC), (long)(3), (_struct_motiontype_str_0x20 *)("Once"));
    } else {
        gimmickBoxDrawString((long)(0xC), (long)(3), (_struct_motiontype_str_0x20 *)("Error"));
    }
    gimmickBoxDrawString(0x18, 0, (_struct_motiontype_str_0x20 *)("Motion Type"));
    gimmickBoxDrawString(0x18, 1, &motiontype_str[m_current_motion_type]);
    gimmickBoxDrawInt(0x18, 2, m_current_motion_type);
    gimmickBoxDrawString(0x24, 0, (_struct_motiontype_str_0x20 *)("Play Speed Rate"));
    gimmickBoxDrawFloat(0x24, 1, m_play_speed_rate);
    if (M2C_FIELD(m_pChara, u8 *, 0x14C) != 0) {
        gimmickBoxDrawString(0, 8, (_struct_motiontype_str_0x20 *)("BLINK ON"));
    } else {
        gimmickBoxDrawString(0, 8, (_struct_motiontype_str_0x20 *)("BLINK OFF"));
    }
    if (M2C_FIELD(m_pChara, u8 *, 0x14D) != 0) {
        gimmickBoxDrawString(0, 9, (_struct_motiontype_str_0x20 *)("SPEAK ON"));
    } else {
        gimmickBoxDrawString(0, 9, (_struct_motiontype_str_0x20 *)("SPEAK OFF"));
    }
    if (M2C_FIELD(m_pChara, u8 *, 0x154) != 0) {
        gimmickBoxDrawString(0, 0xB, (_struct_motiontype_str_0x20 *)("GSmodel Enabled."));
    } else {
        gimmickBoxDrawString(0, 0xB, (_struct_motiontype_str_0x20 *)("GSmodel Disabled."));
    }
    if (M2C_FIELD(m_pChara, u8 *, 0x155) != 0) {
        gimmickBoxDrawString(0, 0xC, (_struct_motiontype_str_0x20 *)("Manual Motion."));
    } else {
        gimmickBoxDrawString(0, 0xC, (_struct_motiontype_str_0x20 *)("Auto Motion."));
    }
    gimmickBoxDrawString(0, 0xE, (_struct_motiontype_str_0x20 *)("targetPos"));
    gimmickBoxDrawFloat(0, 0xF, M2C_FIELD(m_pChara, f32 *, 0x68));
    gimmickBoxDrawFloat(0, 0x10, M2C_FIELD(m_pChara, f32 *, 0x6C));
    gimmickBoxDrawFloat(0, 0x11, M2C_FIELD(m_pChara, f32 *, 0x70));
    gimmickBoxDrawString((long)(0), (long)(0x13), (_struct_motiontype_str_0x20 *)("randRadius"));
    gimmickBoxDrawFloat(0, 0x14, M2C_FIELD(m_pChara, f32 *, 0x8C));
    gimmickBoxDrawString((long)(0), (long)(0x16), (_struct_motiontype_str_0x20 *)("randCenter"));
    gimmickBoxDrawFloat(0, 0x17, M2C_FIELD(m_pChara, f32 *, 0x80));
    gimmickBoxDrawFloat(0, 0x18, M2C_FIELD(m_pChara, f32 *, 0x84));
    gimmickBoxDrawFloat(0, 0x19, M2C_FIELD(m_pChara, f32 *, 0x88));
    gimmickBoxDrawString((long)(0), (long)(0x1B), (_struct_motiontype_str_0x20 *)("distance: from pos to target"));
    gimmickBoxDrawFloat(0, 0x1C, PSVECDistance((const register Vec*)(m_pChara + 0x68), (const register Vec*)(peopleBiosGetPosPtr((PeopleWork*)((PeopleWork *) m_pChara)))));
    if (GSmodelIsAnimating((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)))) {
        gimmickBoxDrawString(0, 3, (_struct_motiontype_str_0x20 *)("Animating"));
    } else {
        gimmickBoxDrawString(0, 3, (_struct_motiontype_str_0x20 *)("Anim Stopping"));
    }
}
}

extern "C++" {
static struct _struct_motiontype_str_0x20* _peopleViewerGetActName(long id) {
    for (s32 i = 0; i < 0x88; i++) {
        if ((u32)id == anim_str[i].unk4) {
            return (_struct_motiontype_str_0x20*)anim_str[i].name;
        }
    }
    return 0;
}
}

extern "C++" {
static void _peopleViewerGetWalkAndRunInfo() {
    f32 sp8;

    _setAnimIndex((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)), 5);
    GSmodelGetFrameCount((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)), (f32*)(&sp8), (f32*)(NULL));
    sprintf((char*)(m_walk_parameter_str), (const char*)("WalkLength = %f frameTime = %f"), peopleInfoBiosGetWalkLength((PeopleInfo*)(m_pCharaInfo)), sp8);
    _setAnimIndex((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)), 8);
    GSmodelGetFrameCount((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)), (f32*)(&sp8), (f32*)(NULL));
    sprintf((char*)(m_run_parameter_str), (const char*)("RunLength = %f frameTime = %f"), peopleInfoBiosGetRunLength((PeopleInfo*)(m_pCharaInfo)), sp8);
}
}

extern "C" {
void peopleViewerSetHeroPos() {
    GSvec heroPos;
    GSvec charaPos;

    if (GSfloorGetCurrent() != 0xFA1U || m_pKen == NULL || M2C_FIELD(m_pKen, u32*, 8) == 0 || m_pChara == NULL ||
        M2C_FIELD(m_pChara, u32*, 8) == 0) {
        return;
    }
    if ((u32)(m_current_motion_type - 1) <= 2 || m_current_motion_type == 4) {
        peopleBiosGetPos((PeopleWork*)m_pKen, &heroPos);
        peopleBiosGetPos((PeopleWork*)m_pChara, &charaPos);
        heroPos.x = charaPos.x;
        if (m_current_motion_type == 3 || m_current_motion_type == 4) {
            heroPos.z = charaPos.z + (init_hero_pos.z - init_chara_pos.z);
        }
        static bool bTest = true;
        if (bTest) {
            peopleSetPos(0, 0x64, (f32*)&heroPos);
        }
    }
}
}

extern "C++" {
static void _peopleViewerMain() {
    u32 temp_r31_3;
    Hero *temp_r3;
    u32 temp_r30;
    u32 temp_r31_2;
    s32 sp8;
    u32 var_r3;

    if (GSfloorGetCurrent() == 0xFA1U) {
        if (GSinputButtonsPressed(1) & (u32)(GSinputButtonsChanged(1)) & 0x40) {
            peoplePartAnimationBlinkOnce((tagPeopleWork*)(m_pChara));
        }
        if (GSinputButtonsPressed(1) & 0x200) {
            peopleMoveNeckTarget(0, 0x64, 0xFA1, 0, 1.0f);
        }
        if (GSinputButtonsPressed(1) & 0x100) {
            peopleRemoveNeckTarget(0, 0x64, 0.0f);
        }
        temp_r31_2 = GSinputButtonsChanged(1);
        var_r3 = GSinputButtonsPressed(1);
        if (var_r3 & temp_r31_2 & 0x10) {
            if ((u8) M2C_FIELD(m_pChara, u8 *, 0x14D) != 0) {
                peoplePartAnimationSpeakStop((tagPeopleWork*)(m_pChara));
            } else {
                peoplePartAnimationSpeakStart((tagPeopleWork*)(m_pChara));
            }
            var_r3 = (u32) m_pChara;
            m_b_speak_mode = M2C_FIELD(var_r3, u8 *, 0x14D);
        }
        temp_r3 = Hero::getHeroPtr();
        temp_r31_3 = ((Hero*)(temp_r3))->getFollowerGrpID();
        temp_r30 = ((Hero*)(temp_r3))->getFollowerResID();
        peopleSetDisp(0, 0x64, m_b_rinto_disp);
        peopleSetDisp((s32) temp_r31_3, (s32) temp_r30, 0U);
        peopleSetFlagOff(0, 0x64, 0x100);
        peopleSetFlagOff(0, 0x64, 0x400);
        peopleSetFlagOff(0xFA1, 0, 0x100);
        peopleSetFlagOff(0xFA1, 0, 0x400);
        if ((u8) m_b_change_chara != 0) {
            peopleReadObject(0xFA1, 0, char_tbl[m_char_number].unk4);
            m_pCharaInfo = peopleInfoBiosGetPtr(M2C_FIELD(m_pChara, u32 *, 0x1C));
            M2C_FIELD(m_pChara, u8 *, 0x14C) = 0U;
            _peopleViewerGetWalkAndRunInfo();
            m_b_change_chara = 0;
            m_anim_number = 0;
            _peopleViewerInitChara();
        }
        u8 cmpv = (u16)dbgMenuIsOpen();
        if (cmpv != 0) {
            m_b_play_stop = 1;
            GSmodelStopAnimation((_GSmodel*)(M2C_FIELD(m_pKen, _GSmodel **, 8)));
            GSmodelStopAnimation((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)));
        } else {
            switch (m_current_motion_type) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                break;
            case 5:
                _peopleViewerFallMotion();
                break;
            }
            if ((u8) m_b_play_stop != 0) {
                m_b_play_stop = 0;
                _peopleViewerStartAnimation();
                if ((u8) m_b_speak_mode != 0) {
                    peoplePartAnimationSpeakStart((tagPeopleWork*)(m_pChara));
                } else {
                    peoplePartAnimationSpeakStop((tagPeopleWork*)(m_pChara));
                }
                if ((u8) M2C_FIELD(m_pChara, u8 *, 0x14C) != 0) {
                    peoplePartAnimationBlinkStart((tagPeopleWork*)(m_pChara));
                }
            }
        }
        switch (m_current_motion_type) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
        case 5:
            _peopleViewerFallMotion();
            break;
        }
        if (((_GSmodel *) M2C_FIELD(m_pKen, _GSmodel **, 8) != NULL) && ((_GSmodel *) M2C_FIELD(m_pChara, _GSmodel **, 8) != NULL)) {
            GSvec pos;
            peopleBiosGetPos((PeopleWork*)m_pKen, &pos);
            _peopleViewerDrawParams();
            dbgMenuIsOpen();
        }
    }
}
}

extern "C++" {
static void _peopleViewerInit() {
    GSlight *temp_r3_4;
    Hero *temp_r3;
    f32 *temp_r3_3;
    f32 temp_f1;
    tagPeopleWork *temp_r3_2;
    GXColor color;

    if (GSfloorGetCurrent() == 0xFA1U) {
        m_b_speak_mode = 0;
        m_b_play_stop = 0;
        m_b_change_chara = 0;
        m_b_rinto_disp = 0;
        peoplePartAnimationSpeakStop((tagPeopleWork*)(m_pChara));
        temp_r3 = Hero::getHeroPtr();
        u32 grp = temp_r3->getFollowerGrpID();
        u32 res = temp_r3->getFollowerResID();
        peopleSetDisp(0, 0x64, m_b_rinto_disp);
        peopleSetDisp((s32) grp, (s32) res, 0U);
        peopleSetFlagOff(0, 0x64, 0x100);
        peopleSetFlagOff(0, 0x64, 0x400);
        peopleSetFlagOff(0xFA1, 0, 0x100);
        peopleSetFlagOff(0xFA1, 0, 0x400);
        m_current_motion_type = 0;
        peopleGetHumanID(0xFA1, 0);
        temp_r3_2 = (tagPeopleWork *)(peopleSearchID());
        m_pChara = temp_r3_2;
        if (temp_r3_2 != NULL) {
            peopleGetHumanID(0, 0x64);
            temp_r3_3 = peopleSearchID();
            m_pKen = temp_r3_3;
            if (temp_r3_3 != NULL) {
                peopleGetPos(0, 0x64, (GSvec*)(&init_hero_pos));
                peopleGetRot(0, 0x64, (s32*)&init_hero_rot);
                m_pCharaInfo = peopleInfoBiosGetPtr(M2C_FIELD(m_pChara, u32 *, 0x1C));
                temp_f1 = gimmickBoxGetFrameCount((f32 *) m_pChara, 0x28);
                m_fall_end_frame_count = temp_f1;
                m_fall_end_anim_num = temp_f1;
                peopleReadObject(0xFA1, 0, char_tbl->unk4);
                _peopleViewerGetWalkAndRunInfo();
                _peopleViewerInitChara();
                peopleBiosSetFlagOff((PeopleWork*)((PeopleWork *) m_pKen), 8U);
                peopleBiosSetFlagOff((PeopleWork*)((PeopleWork *) m_pChara), 8U);
                m_play_speed_rate = 1.0f;
                cameraSetType(5U);
                temp_r3_4 = (GSlight *)(lightGetLight(0));
                color.r = 0xFF;
                color.g = 0xFF;
                color.b = 0xFF;
                GXColor c = color;
                GSlightSetColor(temp_r3_4, &c);
            }
        }
    }
}
}

extern "C" {
void peopleViewerThread() {
    _peopleViewerInit();
loop_1:
    _peopleViewerMain();
    GSthreadSwitch();
    goto loop_1;
}
}

extern "C++" {
static void _peopleViewerFallReady(float height) {
    GSvec pos;

    peopleGetPos(0xFA1, 0, &pos);
    m_fall_height = height;
    pos.y = height;
    m_fall_start_anim_num = 0.0f;
    m_fall_loop_anim_num = 0.0f;
    m_fall_end_anim_num = 0.0f;
    m_anim_number = 0;
    m_fall_speed = 0.0f;
    peopleSetPos(0xFA1, 0, (float*)&pos);
}
}

extern "C++" {
static s32 _peopleViewerFallMotion() {
    GSvec pos;
    f32 vsync;
    f32 speed;
    f32 fall;
    f32 y;

    peopleGetPos(0xFA1, 0, &pos);
    vsync = GSgfxVideoGetVsyncRate();
    speed = m_play_speed_rate * (30.0f * timeGetLastFrameTime() / vsync);
    fall = 1.3f * speed;
    y = pos.y - fall;
    if (y > 0.0f) {
        if (m_fall_loop_anim_num > 0.0f) {
            pos.y = y;
            if (y < 0.0f) {
                pos.y = 0.0f;
            }
        }
        peopleSetPos(0xFA1, 0, (f32*)&pos);
        m_anim_number = 0x27;
        gimmickSetMotion(0xFA1, 0, 0x27, (s32)m_fall_loop_anim_num, 1);
        m_fall_loop_anim_num += speed;
    } else if (m_fall_end_anim_num < m_fall_end_frame_count) {
        pos.y = 0.0f;
        peopleSetPos(0xFA1, 0, (f32*)&pos);
        m_anim_number = 0x28;
        gimmickSetMotion(0xFA1, 0, 0x28, (s32)m_fall_end_anim_num, 0);
        m_fall_end_anim_num += speed;
    } else {
        _peopleViewerFallReady(m_fall_height);
        return 1;
    }
    return 0;
}
}

extern "C++" {
static void _peopleViewerInitChara() {
    M2C_FIELD(m_pChara, s8 *, 0x54) = 0;
    m_anim_number = 0;
    peoplePartAnimationBlinkStop((tagPeopleWork*)(m_pChara));
    peoplePartAnimationSpeakStop((tagPeopleWork*)(m_pChara));
    peopleSetMotion(0xFA1U, 0U, m_anim_number, 0U, 1U);
    peopleSetPos(0xFA1, 0, (f32*)&init_chara_pos);
    peopleSetRot(0xFA1, 0, &init_chara_rot);
    peopleSetPos(0, 0x64, (f32*)&init_hero_pos);
    peopleSetRot(0, 0x64, &init_hero_rot);
    M2C_FIELD(m_pChara, s8 *, 0x54) = 6;
    static f32 degree = 0.0f;
    GSvec rot;
    rot.x = 0.0f;
    rot.y = 0.017453292f * degree;
    rot.z = 0.0f;
    peopleBiosSetRot((PeopleWork*)m_pChara, (void*)&rot);
}
}

extern "C++" {
static void _peopleViewerResetPlaySpeed() {
    m_play_speed_rate = 1.0f;
}
}
