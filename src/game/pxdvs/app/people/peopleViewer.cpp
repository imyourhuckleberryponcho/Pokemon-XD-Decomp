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

extern f32 m_play_speed_rate;

extern "C++" {
struct GSgfxLayer {
    u8 _draft[1];
};
struct GSlight {
    u8 _draft[1];
};
struct GSvec {
    f32 x, y, z;
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
    u8 _draft[1];
};
struct tagPeopleWork {
    u8 _draft[1];
};
struct _struct_anim_str_0x28 {
     char pad0[4];
     u32 unk4;
     char name[0x20];
};
struct _struct_char_tbl_0xC {
     char pad0[4];
     s32 unk4;                             
     _struct_motiontype_str_0x20 *unk8;    
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
u32 GSmodelIsAnimating(_GSmodel* model);
void GSmodelSetAnimIndex(_GSmodel* model, u32 index);
void GSmodelStartAnimation(_GSmodel* model);
void GSmodelStopAnimation(_GSmodel* model);
void GSprimDraw2DQuad(GXColor color, f32 x, f32 y, f32 w, f32 h);
void GSprimSetBlendMode(s32 mode);
void GSthreadSwitch(void);
f32 PSVECDistance(const register Vec* a, const register Vec* b);
static void __sinit_peopleViewer_cpp();
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
extern GXColor jtbl_2208;
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
static GSvec init_chara_pos;
static GSvec init_chara_rot;
static GSvec init_hero_pos;
static GSvec init_hero_rot;
static struct _struct_anim_str_0x28 anim_str[0x88];
static struct _struct_char_tbl_0xC char_tbl[0xB9];
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
static s8 m_run_parameter_str[0x100];
static s8 m_walk_parameter_str[0x100];
static struct _struct_motiontype_str_0x20 motiontype_str[5];
extern "C++" {

extern "C++" {

extern "C" {
s32 peopleViewerDisplayDaemonInfo(void *p0);
void peopleViewerSetHeroPos();
}
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

extern "C" {
void peopleViewerThread() {
    _peopleViewerInit();
loop_1:
    _peopleViewerMain();
    GSthreadSwitch();
    goto loop_1;
}
extern "C++" {
#pragma push
#pragma peephole off
static void _peopleViewerInit() {
    u32 temp_r31;
    s8 spD;
    volatile s8 spC;
    s32 sp8;
    GSlight *temp_r3_4;
    Hero *temp_r3;
    f32 *temp_r3_3;
    f32 temp_f1;
    tagPeopleWork *temp_r3_2;
    u32 temp_r30;
    volatile s8 spE;
    GXColor color;
    GXColor copy;

    if (GSfloorGetCurrent() == 0xFA1U) {
        m_b_speak_mode = 0;
        m_b_play_stop = 0;
        m_b_change_chara = 0;
        m_b_rinto_disp = 0;
        peoplePartAnimationSpeakStop((tagPeopleWork*)(m_pChara));
        temp_r3 = Hero::getHeroPtr();
        temp_r31 = ((Hero*)(temp_r3))->getFollowerGrpID();
        temp_r30 = ((Hero*)(temp_r3))->getFollowerResID();
        peopleSetDisp(0, 0x64, m_b_rinto_disp);
        peopleSetDisp((s32) temp_r31, (s32) temp_r30, 0U);
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
                copy = color;
                GSlightSetColor(temp_r3_4, &copy);
            }
        }
    }
}
#pragma pop
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
            if ((s32) m_current_motion_type != 5) {
                if ((s32) m_current_motion_type < 5) {

                }
            } else {
                _peopleViewerFallMotion();
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
        if ((s32) m_current_motion_type != 5) {
            if ((s32) m_current_motion_type < 5) {

            }
        } else {
            _peopleViewerFallMotion();
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

}

extern "C++" {
extern "C++" {
extern "C" {
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
static void _peopleViewerDrawParams() {
    u32 sp10;
    u32 spC;
    s32 sp8;
    s32 *temp_r4;
    s32 temp_r3;

    temp_r4 = (long *)("SNATCHDAN_0000");
    GSprimSetup2DRender((GSgfxLayer*)(GSgfxLayerFindByID(7)));
    GSprimSetBlendMode(1);
    GSprimDraw2DQuad(jtbl_2208, 10.0f, 10.0f, 630.0f, 72.0f);
    gimmickBoxDrawString((long)(0), (long)(0), (_struct_motiontype_str_0x20 *)(temp_r4 + 0x9D0));
    gimmickBoxDrawString(0, 1, char_tbl[m_char_number].unk8);
    gimmickBoxDrawInt(0, 2, m_char_number);
    gimmickBoxDrawString((long)(0xC), (long)(0), (_struct_motiontype_str_0x20 *)(temp_r4 + 0x9DC));
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
    if (M2C_ERROR()) {
        gimmickBoxDrawString((long)(0), (long)(8), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA04));
    } else {
        gimmickBoxDrawString((long)(0), (long)(8), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA10));
    }
    if ((u8) M2C_FIELD((u16)m_pChara, u8 *, 0x14D) != 0) {
        gimmickBoxDrawString((long)(0), (long)(9), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA1C));
    } else {
        gimmickBoxDrawString((long)(0), (long)(9), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA28));
    }
    if ((u8) M2C_FIELD((u16)m_pChara, u8 *, 0x154) != 0) {
        gimmickBoxDrawString((long)(0), (long)(0xB), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA34));
    } else {
        gimmickBoxDrawString((long)(0), (long)(0xB), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA48));
    }
    if ((u8) M2C_FIELD(m_pChara, u8 *, 0x155) != 0) {
        gimmickBoxDrawString((long)(0), (long)(0xC), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA5C));
    } else {
        gimmickBoxDrawString((long)(0), (long)(0xC), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA6C));
    }
    gimmickBoxDrawString((long)(0), (long)(0xE), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA7C));
    gimmickBoxDrawFloat(0, 0xF, M2C_FIELD(m_pChara, f32 *, 0x68));
    gimmickBoxDrawFloat(0, 0x10, M2C_FIELD(m_pChara, f32 *, 0x6C));
    gimmickBoxDrawFloat(0, 0x11, M2C_FIELD(m_pChara, f32 *, 0x70));
    gimmickBoxDrawString((long)(0), (long)(0x13), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA88));
    gimmickBoxDrawFloat(0, 0x14, M2C_FIELD(m_pChara, f32 *, 0x8C));
    gimmickBoxDrawString((long)(0), (long)(0x16), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xA94));
    gimmickBoxDrawFloat(0, 0x17, M2C_FIELD(m_pChara, f32 *, 0x80));
    gimmickBoxDrawFloat(0, 0x18, M2C_FIELD(m_pChara, f32 *, 0x84));
    gimmickBoxDrawFloat(0, 0x19, M2C_FIELD(m_pChara, f32 *, 0x88));
    gimmickBoxDrawString((long)(0), (long)(0x1B), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xAA0));
    gimmickBoxDrawFloat(0, 0x1C, PSVECDistance((const register Vec*)(m_pChara + 0x68), (const register Vec*)(peopleBiosGetPosPtr((PeopleWork*)((PeopleWork *) m_pChara)))));
    u8 cmpv = GSmodelIsAnimating((_GSmodel*)(M2C_FIELD(m_pChara, _GSmodel **, 8)));
    if (cmpv != 0) {
        gimmickBoxDrawString((long)(0), (long)(3), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xAC0));
        return;
    }
    gimmickBoxDrawString((long)(0), (long)(3), (_struct_motiontype_str_0x20 *)(temp_r4 + 0xACC));
}

}

extern "C" {
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
bool peopleViewerIsCheckNpc(s32 *p0) {
    if (GSfloorGetCurrent() != 0xFA1U) {
        return false;
    }
    return M2C_FIELD(p0, s32 *, 0x18) == 0;
}
}
}
}
}
}
}
f32 peopleViewerGetPlaySpeedRate(void) {
    return m_play_speed_rate;
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

void peopleViewerSetPlaySpeedRate(f32 value) {
    m_play_speed_rate = value;
}
extern "C++" {
static void _setAnimIndex(_GSmodel* p0, int p1) {
    GSmodelSetAnimIndex((_GSmodel*)(p0), (u32) p1);
}
}

extern "C" {
static void __sinit_peopleViewer_cpp() {
    init_chara_pos.x = 0.0f;
    init_chara_pos.y = 0.0f;
    init_chara_pos.z = 0.0f;
    init_chara_rot.x = 0.0f;
    init_chara_rot.y = 0.0f;
    init_chara_rot.z = 0.0f;
    init_hero_pos.x = 0.0f;
    init_hero_pos.y = 0.0f;
    init_hero_pos.z = 6.0f;
    init_hero_rot.x = 0.0f;
    init_hero_rot.y = 0.0f;
    init_hero_rot.z = 0.0f;
}
}

}
