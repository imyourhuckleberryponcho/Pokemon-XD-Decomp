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
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct CAM_STORE;
enum EVOLUTION_WINDOW_TYPE { EVOLUTION_WINDOW_TYPE_draft_dummy };
enum FADE_CTRL { FADE_CTRL_draft_dummy };
struct GScamera;
struct GSvec;
struct Pokemon;
struct PokemonData;
enum STEP { STEP_draft_dummy };
struct Sequence;
struct WORK;
struct WazaSequence;
struct _GSmodel;

extern "C" {

extern "C++" {
struct CAM_STORE {
    f32 pos[3];
    f32 rot[3];
    f32 target[3];
    f32 targetOfs[3];
    f32 fovy;
};
struct GScamera {
    u8 _draft[1];
};
struct GSvec {
    u8 _draft[1];
};
struct Pokemon {
    u8 data[0xC4];
};
struct PokemonData {
    u8 _draft[1];
};
struct Sequence {
    u8 _draft[1];
};
struct WORK {
    u8 data[0x30];
};
struct WazaSequence {
    u8 _draft[1];
};
struct _GSmodel {
    u8 _draft[1];
};
struct _struct_CancelStep_0x8 {
     u32 unk0;                             
     s32 unk4;                             
};
struct _struct_StepSeqTbl_0x8 {
     u16 unk0;                             
     s32 unk4;                             
};
extern "C" {
GScamera* GScameraGetActiveCamera(void);
void GScameraGetPerspective(GScamera* camera, f32* fov, f32* aspect, f32* near, f32* far);
u8 GSfloorPop(void);
u8 GSfloorPush(u32 id);
u32 GSinputButtonsChanged(s32 pad);
u32 GSinputButtonsPressed(s32 pad);
void GSmodelSetAnimType(_GSmodel* model, s32 type);
void GSmodelSetForceUseFractionalFramesFlag(_GSmodel* model, u8 enable);
void GSmodelSetSkipFractionalFramesFlag(_GSmodel* model, u8 enable);
void* GSresGetResourceAllGroup(u32 id);
void GSsndGetPushVolumeID(u32 id, u8* buf);
s32 GSsndGetStatus(u32 id);
u8 GSsndPlayNow(u32 id);
void GSsndSetPushVolumeID(u32 id, u8* buf);
void GSthreadSwitch(void);
s32 Sequence_GetGSmodel(s32);
WazaSequence* Sequence_GetWaza(Sequence* sequence, u16 wzxID, u32 kind);
u32 Sequence_LoadPokemon(u16, u32, u32);
void* Sequence_LoadWaza(Sequence* sequence, u16 wazaID, u8 kind, s32);
s32 Sequence_SetVisibility(u32, s32);
void WazaSequence_Free(WazaSequence* sequence);
bool WazaSequence_IsActive(WazaSequence* sequence);
void WazaSequence_Start(WazaSequence* sequence, s32);
void cameraGetPosition(GSvec* pos);
void cameraGetRotation(GSvec* rot);
void cameraGetTargetOfs(GSvec* ofs);
void cameraGetTargetPos(GSvec* pos);
void cameraSetFov(f32 fov);
void cameraSetPosition(GSvec* pos);
void cameraSetRotation(GSvec* rot);
void cameraSetTargetOfs(GSvec* ofs);
void cameraSetTargetPos(GSvec* pos);
u8 cameraSetType(u8 type);
void evolution();
void evolutionMain();
s32 evolutionOpen(void*, void*, s32, u16*, s32, u8*);
s32 evolutionStart(s32 *p0, s32 *p1, s32 p2, u16 *p3, s32 p4, u8 *p5);
s32 evolutionWazaLearn(Pokemon* p0, u32 p1, s8 *p2, EVOLUTION_WINDOW_TYPE p3, void *p4, u32 *p5);
extern "C++" static s32 evolution__Main(WORK* work, int mode, Pokemon* pokemon, Pokemon* evolved, u16* moves, s32 count, u8* result);
s8 fadeCheck(bool);
void fadeSet(s32 type, f32 time);
void floorSetFadeScript(u32 out, u32 in);
void floorWaitForChange(void);
s32 menuPokemonStatusOpenWazaLearn(Pokemon* pokemon, u16 sel);
s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 initial);
s8 menuSubOpenYesNoField(void);
void msgctrlSetValue(s32 id, u32 value);
void pokemonBiosCopy(Pokemon* pokeDst, const Pokemon* pokeSrc);
char* pokemonBiosGetNicknamePtr(Pokemon* poke);
u16 pokemonBiosGetPokemonDataId(Pokemon* poke);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon* poke, u16 wazaNum);
u32 pokemonBiosGetRnd(Pokemon* poke);
bool pokemonCheckValid(Pokemon* pokemon);
PokemonData* pokemonDataBiosGetPtr(u16 pokeNum);
u16 pokemonDataBiosGetVoice(PokemonData* pdata);
u32 pokemonGetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index);
void pokemonWazaCreate(Pokemon* pokemon, u16 wazaNum, u16 waza);
u32 soundGetBGMID(void);
s32 soundGetEnvID();
s32 soundGetVolume(s32);
void soundOpenPlay(s32, s32, s32);
void soundOpenPlayEnv(u32 id, s32, s32 volume);
void soundOpenPlayME(u32 id, u32, u8 volume);
s32 soundStop(s32, s32);
s32 soundStopEnv(s32);
u32 timeGetLastFrameTime(void);
s32 wazaSequenceSysEnableLayerChange();
void winMsgClose(bool flag);
void winMsgCloseField(bool flag);
s32 winMsgOpen(s8 type, void* msg, bool a, bool b);
s32 winMsgOpenField(void* msg, bool a, bool b);
}
extern "C++" {
static s8 cbWazaForget(Pokemon* p0, unsigned short p1, long p2);
static void closeMsgWin(EVOLUTION_WINDOW_TYPE p0);
static s32 dispMsgYesNo(unsigned long p0, EVOLUTION_WINDOW_TYPE p1);
static void dispMsg(unsigned long p0, EVOLUTION_WINDOW_TYPE p1);
static s32 doWazaSequence(WORK* p0, STEP p1, int p2, FADE_CTRL p3);
static s32 evolutionDemo(WORK* p0, int p1, Pokemon* p2, Pokemon* p3);
static u16 getPkxID(Pokemon* p0);
static PokemonData* getPokemonData(Pokemon* pokemon);
static s32 getStepSeq(WORK* p0, STEP p1);
static s32 getYesNo(EVOLUTION_WINDOW_TYPE p0);
static s32 loadAll(WORK* p0, Pokemon* p1, Pokemon* p2);
static u8 loadSequenceAfter(WORK* p0, Pokemon* p1);
static u8 loadSequenceBefore(WORK* p0, Pokemon* p1);
static u32 loadSequence(Pokemon* p0, int p1);
static void openMsgWin(unsigned long p0, EVOLUTION_WINDOW_TYPE p1);
static s32 playPokemonVoice(Pokemon* p0);
static void restoreCamera(CAM_STORE* p0);
static void restoreSound(WORK* p0);
static void stopSound(WORK* p0);
static void storeCamera(CAM_STORE* p0);
static void toVisible(WORK* p0, int p1, int p2);
static void waitTime(float p0);
static void wazaSeqEnd(WORK* p0);
static s32 wazaSeqStart(WORK* p0, STEP p1);
static s32 wazaSeqUpdate(WORK* p0);
}
static const struct _struct_StepSeqTbl_0x8 StepSeqTbl[5] = { { 0x4A, 0 }, { 0x5E, 1 }, { 0x5B, 0 }, { 0x5C, 0 }, { 0x5D, 0 } };
struct EvolutionParameter {
    void* pokemon;
    void* evolved;
    s32 mode;
    s32 x0C;
    u16* moves;
    u8* result;
    s32 ret;
};
static EvolutionParameter Parameter;
static const struct _struct_CancelStep_0x8 CancelStep[3] = { { 0x1E0U, 2 }, { 0x21CU, 3 }, { 0x1770U, 4 } };
static void restoreCamera(CAM_STORE* p0) {
    cameraSetType(2U);
    cameraSetPosition((GSvec*)((GSvec *) p0));
    cameraSetRotation((GSvec*)(((u8*)(p0) + 0xC)));
    cameraSetTargetPos((GSvec*)(((u8*)(p0) + 0x18)));
    cameraSetTargetOfs((GSvec*)(((u8*)(p0) + 0x24)));
    cameraSetFov(M2C_FIELD(p0, f32 *, 0x30));
}
}

extern "C++" {
static void storeCamera(CAM_STORE* p0) {
    f32 v3C[3];
    f32 v30[3];
    f32 v24[3];
    f32 v18[3];
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;

    cameraGetPosition((GSvec*)(v3C));
    cameraGetRotation((GSvec*)(v30));
    cameraGetTargetPos((GSvec*)(v24));
    cameraGetTargetOfs((GSvec*)(v18));
    GScameraGetPerspective((GScamera*)(GScameraGetActiveCamera()), (f32*)(&sp14), (f32*)(&sp10), (f32*)(&spC), (f32*)(&sp8));
    M2C_FIELD(p0, f32 *, 0) = v3C[0];
    M2C_FIELD(p0, f32 *, 4) = v3C[1];
    M2C_FIELD(p0, f32 *, 8) = v3C[2];
    M2C_FIELD(p0, f32 *, 0xC) = v30[0];
    M2C_FIELD(p0, f32 *, 0x10) = v30[1];
    M2C_FIELD(p0, f32 *, 0x14) = v30[2];
    M2C_FIELD(p0, f32 *, 0x18) = v24[0];
    M2C_FIELD(p0, f32 *, 0x1C) = v24[1];
    M2C_FIELD(p0, f32 *, 0x20) = v24[2];
    M2C_FIELD(p0, f32 *, 0x24) = v18[0];
    M2C_FIELD(p0, f32 *, 0x28) = v18[1];
    M2C_FIELD(p0, f32 *, 0x2C) = v18[2];
    M2C_FIELD(p0, f32 *, 0x30) = sp14;
}
}

extern "C++" {
static void restoreSound(WORK* p0) {
    u32 temp_r3;
    u32 temp_r3_2;

    temp_r3 = M2C_FIELD(p0, u32 *, 0xC);
    if (temp_r3 != 0) {
        soundOpenPlay((s32) temp_r3, 0x32, (s32) (u8) M2C_FIELD(p0, s32 *, 0x14));
        GSsndSetPushVolumeID(M2C_FIELD(p0, u32 *, 0xC), (u8*)(((u8*)(p0) + 0x1C)));
    }
    temp_r3_2 = M2C_FIELD(p0, u32 *, 0x10);
    if (temp_r3_2 != 0) {
        soundOpenPlayEnv(temp_r3_2, 0x32, (s32) (u8) M2C_FIELD(p0, s32 *, 0x18));
        GSsndSetPushVolumeID(M2C_FIELD(p0, u32 *, 0x10), (u8*)(((u8*)(p0) + 0x20)));
    }
}
}

extern "C++" {
static void stopSound(WORK* p0) {
    u32 temp_r3;
    s32 temp_r3_2;
    s32 var_r29;
    s32 var_r28;

    temp_r3 = soundGetBGMID();
    if (temp_r3 != 0) {
        GSsndGetPushVolumeID(temp_r3, (u8*)(((u8*)(p0) + 0x1C)));
        var_r29 = soundGetVolume((s32) temp_r3);
        soundOpenPlay(8, 0x32, 0xFF);
    } else {
        var_r29 = 0;
    }
    temp_r3_2 = soundGetEnvID();
    if (temp_r3_2 != 0) {
        GSsndGetPushVolumeID((u32) temp_r3_2, (u8*)(((u8*)(p0) + 0x20)));
        var_r28 = soundGetVolume(temp_r3_2);
        soundStopEnv(0x32);
    } else {
        var_r28 = 0;
    }
    M2C_FIELD(p0, u32 *, 0xC) = temp_r3;
    M2C_FIELD(p0, s32 *, 0x10) = temp_r3_2;
    M2C_FIELD(p0, s32 *, 0x14) = var_r29;
    M2C_FIELD(p0, s32 *, 0x18) = var_r28;
}
}

extern "C++" {
static PokemonData* getPokemonData(Pokemon* p0) {
    if (p0 == NULL) {
        return NULL;
    }
    if (pokemonCheckValid((Pokemon*)(p0)) == 0) {
        return NULL;
    }
    return pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId((Pokemon*)(p0)));
}
}

extern "C++" {
static s32 playPokemonVoice(Pokemon* p0) {
    PokemonData *temp_r3_2;
    s32 temp_r3;

    temp_r3_2 = getPokemonData((Pokemon*)(p0));
    if (temp_r3_2 == NULL) {
        return 0U;
    }
    temp_r3 = pokemonDataBiosGetVoice((PokemonData*)(temp_r3_2));
    GSsndPlayNow((u32) temp_r3);
    return temp_r3;
}
}

extern "C++" {
static s32 dispMsgYesNo(unsigned long p0, EVOLUTION_WINDOW_TYPE p1) {
    s32 temp_r31;
    openMsgWin(p0, (EVOLUTION_WINDOW_TYPE)(p1));
    temp_r31 = getYesNo((EVOLUTION_WINDOW_TYPE)(p1));
    closeMsgWin((EVOLUTION_WINDOW_TYPE)(p1));
    switch (temp_r31) {
    case 0x0:
        return 0;
    case 0x1:
        return 1;
    default:
        return 2;
    }
}
}

extern "C++" {
static s32 getYesNo(EVOLUTION_WINDOW_TYPE p0) {
    if (p0 == 0) {
        return menuSubOpenYesNoField();
    }
    return menuSubOpenYesNo(0U, -1, -1, 0);
}
}

extern "C++" {
static void dispMsg(unsigned long p0, EVOLUTION_WINDOW_TYPE p1) {
    openMsgWin(p0, (EVOLUTION_WINDOW_TYPE)(p1));
    closeMsgWin((EVOLUTION_WINDOW_TYPE)(p1));
}
}

extern "C++" {
static void closeMsgWin(EVOLUTION_WINDOW_TYPE p0) {
    if (p0 == 0) {
        winMsgCloseField(1U);
        return;
    }
    winMsgClose(1U);
}
}

extern "C++" {
static void openMsgWin(unsigned long p0, EVOLUTION_WINDOW_TYPE p1) {
    if (p1 == 0) {
        winMsgOpenField((void*)((u8 *) p0), 1U, 0U);
        return;
    }
    winMsgOpen(2, (void*)((u8 *) p0), 1U, 0U);
}
}

extern "C++" {
static void waitTime(float p0) {
    f32 var_f29;

    var_f29 = 0.0f;
    while (var_f29 < (60.0f * p0)) {
        GSthreadSwitch();
        var_f29 += (f32) timeGetLastFrameTime();
    }
}
}

extern "C++" {
static u16 getPkxID(Pokemon* p0) {
    u16 temp_r3;
    u16 temp_r3_2;
    u16 var_r3;

    temp_r3 = pokemonGetStatus((void*)(p0), 0U, 0x6EU, 0U);
    if (temp_r3 == 0) {
        return 0xFFFFU;
    }
    temp_r3_2 = pokemonGetStatus((void*)(NULL), temp_r3, 0x66U, 0U);
    var_r3 = 0xFFFF;
    if (temp_r3_2 != 0) {
        var_r3 = temp_r3_2;
    }
    return var_r3;
}
}

extern "C++" {
static u32 loadSequence(Pokemon* pokemon, int step) {
    s32 i;
    u32 seq;
    u16 id;
    u32 rnd;

    id = getPkxID(pokemon);
    if (id == 0xFFFF) {
        return 0;
    }
    rnd = pokemonBiosGetRnd(pokemon);
    seq = Sequence_LoadPokemon(id, rnd, pokemonGetStatus(pokemon, 0, 0xC1, 0) != 0);
    if (seq == 0) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (step == StepSeqTbl[i].unk4 && Sequence_LoadWaza((Sequence*)seq, StepSeqTbl[i].unk0, 4, 0) == NULL) {
            break;
        }
    }
    if (i < 5) {
        return 0;
    }
    return seq;
}
}

extern "C++" {
static u8 loadSequenceAfter(WORK* p0, Pokemon* p1) {
    u32 temp_r3;

    temp_r3 = loadSequence((Pokemon*)(p1), 1);
    if (temp_r3 == 0) {
        return 0U;
    }
    M2C_FIELD(p0, u32 *, 4) = temp_r3;
    return 1U;
}
}

extern "C++" {
static u8 loadSequenceBefore(WORK* p0, Pokemon* p1) {
    u32 temp_r3;

    temp_r3 = loadSequence((Pokemon*)(p1), 0);
    if (temp_r3 == 0) {
        return 0U;
    }
    (*(s32*)(p0)) = temp_r3;
    return 1U;
}
}

extern "C++" {
static void toVisible(WORK* p0, int p1, int p2) {
    u32 var_r3;

    if (p1 != 0) {
        var_r3 = M2C_FIELD(p0, u32 *, 4);
    } else {
        var_r3 = M2C_FIELD(p0, u32 *, 0);
    }
    Sequence_SetVisibility(var_r3, p2 != 0);
}
}

extern "C++" {
static s32 loadAll(WORK* p0, Pokemon* p1, Pokemon* p2) {
    _GSmodel *temp_r3;

    temp_r3 = (_GSmodel *)(GSresGetResourceAllGroup(0x0FB31000U));
    if (temp_r3 != NULL) {
        GSmodelSetForceUseFractionalFramesFlag((_GSmodel*)(temp_r3), 1U);
        GSmodelSetSkipFractionalFramesFlag((_GSmodel*)(temp_r3), 1U);
    }
    M2C_FIELD(p0, s32 *, 0) = 0;
    M2C_FIELD(p0, s32 *, 4) = 0;
    if ((loadSequenceBefore((WORK*)(p0), (Pokemon*)(p1)) != 0) && (loadSequenceAfter((WORK*)(p0), (Pokemon*)(p2)) != 0)) {
        return 1;
    }
    return 0;
}
}

extern "C" {
s32 evolutionWazaLearn(Pokemon* p0, u32 p1, s8 *p2, EVOLUTION_WINDOW_TYPE p3, void *p4, u32 *p5) {
    s32 slot;

    for (slot = 0; slot < 4; slot++) {
        if (pokemonBiosGetPokemonWazaDataId(p0, slot) == 0) {
            break;
        }
    }
    if (slot >= 4) {
        char* name = pokemonBiosGetNicknamePtr(p0);
        msgctrlSetValue(0x32, (u32)name);
        u16 waza = p1;
        msgctrlSetValue(0x39, waza);
        while (true) {
            if (dispMsgYesNo(0xC36A, p3) == 0) {
                if (p4 != NULL) {
                    slot = ((s8 (*)(Pokemon*, u32, u32*))p4)(p0, p1, p5);
                } else {
                    slot = 0;
                }
                if (slot >= 0) {
                    break;
                }
            }
            msgctrlSetValue(0x32, (u32)name);
            msgctrlSetValue(0x39, waza);
            if (dispMsgYesNo(0xC36B, p3) == 0) {
                dispMsg(0xC36C, p3);
                return 0;
            }
        }
        msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(p0));
        msgctrlSetValue(0x5D, 0x21);
        msgctrlSetValue(0x39, pokemonBiosGetPokemonWazaDataId(p0, slot));
        openMsgWin(0xC36D, p3);
    }
    soundOpenPlayME(0x3C7, 0, 0xFF);
    msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(p0));
    msgctrlSetValue(0x39, (u16)p1);
    dispMsg(0xC36E, p3);
    *p2 = slot;
    return 1;
}
}

extern "C++" {
static s8 cbWazaForget(Pokemon* p0, unsigned short p1, long p2) {
    CAM_STORE store;
    s32 var_r31;

    fadeSet(3, 0.5f);
    fadeCheck(1);
    storeCamera(&store);
    var_r31 = menuPokemonStatusOpenWazaLearn((Pokemon*)(p0), p1);
    if (var_r31 >= 4) {
        var_r31 = -1;
    }
    loadSequenceAfter((WORK*)((WORK *) p2), (Pokemon*)(p0));
    GSmodelSetAnimType((_GSmodel*)(Sequence_GetGSmodel(M2C_FIELD(p2, s32 *, 4))), 1);
    toVisible((WORK*)((WORK *) p2), 1, 1);
    restoreCamera(&store);
    fadeSet(2, 0.5f);
    fadeCheck(1);
    return (s8) var_r31;
}
}

extern "C++" {
static s32 doWazaSequence(WORK* work, STEP step, int canSkip, FADE_CTRL fade) {
    CAM_STORE cam;
    WazaSequence* seq;
    s32 time = 0;
    s32 skipped = 0;

    if (step < 0 || step >= 5) {
        return 0;
    }
    seq = Sequence_GetWaza(StepSeqTbl[step].unk4 != 0 ? M2C_FIELD(work, Sequence **, 4) : M2C_FIELD(work, Sequence **, 0), StepSeqTbl[step].unk0, 4);
    WazaSequence_Start(seq, 1);
    while (skipped == 0) {
        if (fade & 0xA) {
            fadeSet((fade & 2) ? 2 : 4, 0.5f);
            fade = (FADE_CTRL)(fade & ~0xA);
        }
        if (WazaSequence_IsActive(seq) == 0) {
            break;
        }
        GSthreadSwitch();
        storeCamera(&cam);
        time += timeGetLastFrameTime();
        if (canSkip != 0 && (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x200)) {
            skipped = 1;
        }
    }
    restoreCamera(&cam);
    if (fade & 0x14) {
        fadeSet((fade & 4) ? 3 : 5, 0.5f);
        fadeCheck(1);
    }
    WazaSequence_Free(seq);
    if (skipped != 0) {
        return time;
    }
    return -1;
}
}

extern "C++" {
static void wazaSeqEnd(WORK* p0) {
    s32 temp_r31;

    temp_r31 = M2C_FIELD(p0, s32 *, 8);
    WazaSequence_Free((WazaSequence*)(Sequence_GetWaza((Sequence*)(getStepSeq((WORK*)(p0), (STEP)(temp_r31))), StepSeqTbl[temp_r31].unk0, 4U)));
}
}

extern "C++" {
static s32 wazaSeqUpdate(WORK* p0) {
    s32 temp_r31;

    temp_r31 = M2C_FIELD(p0, s32 *, 8);
    return WazaSequence_IsActive((WazaSequence*)(Sequence_GetWaza((Sequence*)(getStepSeq((WORK*)(p0), (STEP)(temp_r31))), StepSeqTbl[temp_r31].unk0, 4U))) != 0;
}
}

extern "C++" {
static s32 getStepSeq(WORK* p0, STEP p1) {
    if ((s32) StepSeqTbl[p1].unk4 != 0) {
        return M2C_FIELD(p0, s32 *, 4);
    }
    return M2C_FIELD(p0, s32 *, 0);
}
}

extern "C++" {
static s32 wazaSeqStart(WORK* p0, STEP p1) {
    if ((p1 < 0) || (p1 >= 5)) {
        return 0;
    }
    WazaSequence_Start((WazaSequence*)(Sequence_GetWaza((Sequence*)(getStepSeq((WORK*)(p0), (STEP)(p1))), StepSeqTbl[p1].unk0, 4U)), 1);
    M2C_FIELD(p0, s32 *, 8) = p1;
    return 1;
}
}

extern "C++" {
static s32 evolutionDemo(WORK* work, int canCancel, Pokemon* pokemon, Pokemon* evolved) {
    s32 first;
    u32 voice;
    u32 elapsed;
    s32 cancelled;
    s32 state;
    s32 wait;
    s32 step;

    toVisible(work, 0, 1);
    char* name = pokemonBiosGetNicknamePtr(pokemon);
    msgctrlSetValue(0x32, (u32)name);
    openMsgWin(0xC419, (EVOLUTION_WINDOW_TYPE)0);
    voice = playPokemonVoice(pokemon);
    wazaSeqStart(work, (STEP)0);
    first = 1;
    cancelled = 0;
    state = 0;
    elapsed = 0;
    while (elapsed < 0x23A) {
        if (canCancel != 0 && elapsed >= 0x78 && state >= 2 && (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x200)) {
            cancelled = 1;
            break;
        }
        if (wazaSeqUpdate(work) == 0) {
            break;
        }
        switch (state) {
        case 0:
            if (GSsndGetStatus(voice) != 2) {
                soundOpenPlay(0x3D0, 0, 0xFF);
                wait = 0;
                state = 1;
            }
            break;
        case 1:
            if (GSsndGetStatus(0x3D0) != 2) {
                wait += timeGetLastFrameTime();
                if (wait >= 0x1E) {
                    soundOpenPlay(0x3D1, 0, 0xFF);
                    state = 2;
                }
            }
            break;
        }
        if (first != 0) {
            fadeSet(2, 0.5f);
            first = 0;
        }
        GSthreadSwitch();
        elapsed += timeGetLastFrameTime();
    }
    fadeSet(5, 0.5f);
    while (fadeCheck(0) != 0) {
        wazaSeqUpdate(work);
        GSthreadSwitch();
    }
    wazaSeqEnd(work);
    waitTime(1.0f);
    if (cancelled != 0) {
        closeMsgWin((EVOLUTION_WINDOW_TYPE)0);
        soundStop(0x3D1, 0x32);
        step = 0;
        if (CancelStep[0].unk0 < elapsed) {
            step = 1;
            if (CancelStep[1].unk0 < elapsed) {
                step = 2;
            }
        }
        doWazaSequence(work, (STEP)CancelStep[step].unk4, 0, (FADE_CTRL)8);
        voice = playPokemonVoice(pokemon);
        while (GSsndGetStatus(voice) == 2) {
            GSthreadSwitch();
        }
        msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(pokemon));
        dispMsg(0xC41B, (EVOLUTION_WINDOW_TYPE)0);
        fadeSet(3, 0.5f);
        fadeCheck(1);
        return 0;
    }
    toVisible(work, 0, 0);
    toVisible(work, 1, 1);
    doWazaSequence(work, (STEP)1, 0, (FADE_CTRL)8);
    closeMsgWin((EVOLUTION_WINDOW_TYPE)0);
    soundStop(0x3D1, 0x32);
    voice = playPokemonVoice(evolved);
    while (GSsndGetStatus(voice) == 2) {
        GSthreadSwitch();
    }
    msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(pokemon));
    u16 id = pokemonBiosGetPokemonDataId(evolved);
    msgctrlSetValue(0x4E, id);
    msgctrlSetValue(0x5D, 0x3CF);
    dispMsg(0xC41A, (EVOLUTION_WINDOW_TYPE)0);
    waitTime(0.5f);
    return 1;
}
}

extern "C" {
extern "C++" {
static s32 evolution__Main(WORK* work, int mode, Pokemon* pokemon, Pokemon* evolved, u16* moves, s32 count, u8* result) {
    u8 sel;
    Pokemon copy;
    s32 i;
    u16 waza;
    u32* arg = (u32*)work;

    stopSound(work);
    s32 ok = evolutionDemo(work, mode, pokemon, evolved);
    restoreSound(work);
    if (ok == 0) {
        return 0;
    }
    pokemonBiosCopy(&copy, evolved);
    for (i = 0; i < count; i++) {
        u16 waza = *moves;
        if (evolutionWazaLearn(&copy, waza, (s8*)&sel, (EVOLUTION_WINDOW_TYPE)0, cbWazaForget, arg) != 0) {
            pokemonWazaCreate(&copy, sel, waza);
        } else {
            sel = 0xFF;
        }
        moves++;
        *result = sel;
        result++;
    }
    fadeSet(3, 0.5f);
    fadeCheck(1);
    return 1;
}
}
}

extern "C" {
s32 evolutionStart(s32 *p0, s32 *p1, s32 p2, u16 *p3, s32 p4, u8 *p5) {
    WORK unksp8;
    wazaSequenceSysEnableLayerChange();
    if (loadAll((WORK*)(&unksp8), (Pokemon*)((Pokemon *) p0), (Pokemon*)((Pokemon *) p1)) == 0) {
        return 2;
    }
    if (evolution__Main(&unksp8, p2, (Pokemon*)p0, (Pokemon*)p1, p3, p4, p5) == 0) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void evolution() {
    Parameter.ret = evolutionStart((s32*)Parameter.pokemon, (s32*)Parameter.evolved, Parameter.mode, Parameter.moves, Parameter.x0C, Parameter.result);
    GSfloorPop();
    floorSetFadeScript(0U, 0U);
}
}
void evolutionExit(void) {
}
extern "C" {
void evolutionMain() {
    evolution();
}
}

void evolutionInit(void) {
}
extern "C" {
s32 evolutionOpen(void* p0, void* p1, s32 p2, u16* p3, s32 p4, u8* p5) {
    EvolutionParameter* param = &Parameter;
    param->pokemon = p0;
    param->evolved = p1;
    param->mode = p2;
    param->x0C = p4;
    param->moves = p3;
    param->result = p5;
    GSfloorPush(0x386U);
    floorSetFadeScript(0U, 0U);
    floorWaitForChange();
    return Parameter.ret;
}
}

}
