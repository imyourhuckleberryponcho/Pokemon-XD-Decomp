#include <dolphin/types.h>
#include <game/shared/menu_work.h>
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
struct GSvec;
struct tagSEQ_WORK;
struct tagSPRITE_WORK;
struct tagWINDOW_WORK;

#pragma peephole off

static void _menuFieldMenuCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, long index);
static void _menuFieldFlashCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, long index);
static void _menuFieldCursorCheck(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, long index);
static void _menuFieldDrawItemSub(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, long index);

extern "C" {

static s32 barcolor = 0xC0C0D000;
static f32 _cursorSec = 0.8f;
static f32 _max_alpha = 255.0f;
static f32 _min_alpha = 200.0f;
static u8 _openFieldMenu;
static f32 _fieldMenuTimer;
static u32 _soundEnvID;
static s32 _soundEnvVol;
static f32 _menuFieldCursorAngle;
static f32 _menuFiledAlpha[5];

struct GSvec {
    f32 x, y, z;
    GSvec();
};

struct HeroMoveEvent {
    GSvec pos[3];
    u32 unk24[3];
    u16 eventID;
    u16 pad32;
};

extern "C" {
u32 GSflagGet(u32 id);
u8 GSgfxVideoGetVsyncRate(void);
s32 GSgfxVideoSetLockFrameRate(s32);
void GSmodelAllPauseAnimation(void);
void GSmodelAllUnpauseAnimation(void);
u32 GSmsgGetRect(u32);
s32 GSmsgPrint2(s32, s16, s16, s32, u32);
void GSsndPopVolumeALL(u32 time, u32 bgm, u32 se);
void GSsndPushVolumeALL(s32 vol, s32 time, u32 bgm, u32 se);
void GSthreadSwitch(void);
s32 __construct_array(s32*, void*, s32, s32, s32);
s8 fadeCheck(bool);
s32 floorEventExecScript(s32, u16);
void floorFieldCameraPause();
void floorFieldCameraUnpause();
s32 fn_80233AB4();
void heroMoveAddAutoEvent(s32, s32, s32, s32, s32);
s32 heroMoveCheckEvent(HeroMoveEvent*);
void heroMoveInitEvent();
void heroMoveTermEvent();
void mailMainReceiveTerminate(void);
void menuClose(s32 menuID);
void menuCloseCustom(s32 menuID, s32, s32);
void menuCloseSync(s32 menuID, s32);
void menuCreateOffScreen(f32, f32);
s32 menuFieldMain(u8 p0);
s32 menuFieldMainCtrl(void *p0);
f32 menuGetLastTime();
u8 menuGetOffScreenFlag();
void menuIntUnderTakerDispIconOff2(void);
void menuIntUnderTakerDispIconRestore2(void);
void menuOffScreenRelease(void);
s32 menuOpen(s32 menuID, s32);
void menuPdaOpen(void);
s32 menuPocket2GetItemScript(u16);
u16 menuPocket2Open(s32, s32*, s32);
void menuPokemonOpen(s32, s32, s32);
void menuReleaseOffScreen(f32);
void menuReport(void);
s32 pokecoloGetRomVersion(void);
s32 scriptContinueSave();
double sin(double x);
u32 soundGetEnvID();
s32 soundGetVolume();
s32 soundSetVolumeID(u32, s32, s32);
f32 timeGetLastFrameSec(void);
void winAnimeCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
void winSeqSetMenu(s32 menuID, u32 id);
void winSetSequence(tagSEQ_WORK* s, u32 id);
void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on);
void __ct__5GSvecFv();
}
extern "C++" {
static void _animAlpha(long p0);
static s32 _menuFieldCheckCursor(long p0);
static u8 _menuFieldCheckPDA();
static void _menuFieldCursorCheck(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, long p2);
static void _menuFieldDrawItemSub(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, long p2);
static void _menuFieldFlashCursor(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, long p2);
static void _menuFieldMenuCursor(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, long p2);
}
void menuFieldDrawItem2(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x15:
        _menuFieldDrawItemSub(window, sprite, 0);
        break;
    case 0x16:
        _menuFieldDrawItemSub(window, sprite, 1);
        break;
    case 0x17:
        _menuFieldDrawItemSub(window, sprite, 2);
        break;
    case 0x18:
        _menuFieldDrawItemSub(window, sprite, 3);
        break;
    case 0x19:
        _menuFieldDrawItemSub(window, sprite, 4);
        break;
    case 0x1A:
        _menuFieldFlashCursor(window, sprite, 0);
        break;
    case 0x1B:
        _menuFieldFlashCursor(window, sprite, 1);
        break;
    case 0x1C:
        _menuFieldFlashCursor(window, sprite, 2);
        break;
    case 0x1D:
        _menuFieldFlashCursor(window, sprite, 3);
        break;
    case 0x1E:
        _menuFieldFlashCursor(window, sprite, 4);
        break;
    case 0x66B:
        _menuFieldMenuCursor(window, sprite, 0);
        break;
    case 0x66C:
        _menuFieldMenuCursor(window, sprite, 1);
        break;
    case 0x66D:
        _menuFieldMenuCursor(window, sprite, 2);
        break;
    case 0x66E:
        _menuFieldMenuCursor(window, sprite, 3);
        break;
    case 0x66F:
        _menuFieldMenuCursor(window, sprite, 4);
        break;
    case 0x1F:
        _menuFieldCursorCheck(window, sprite, 0);
        break;
    case 0x20:
        _menuFieldCursorCheck(window, sprite, 1);
        break;
    case 0x21:
        _menuFieldCursorCheck(window, sprite, 2);
        break;
    case 0x22:
        _menuFieldCursorCheck(window, sprite, 3);
        break;
    case 0x23:
        _menuFieldCursorCheck(window, sprite, 4);
        break;
    case 0x2C3:
        _menuFieldDrawItemSub(window, sprite, 0);
        break;
    case 0x2C4:
        _menuFieldDrawItemSub(window, sprite, 1);
        break;
    case 0x2C5:
        _menuFieldDrawItemSub(window, sprite, 2);
        break;
    case 0x2C6:
        _menuFieldDrawItemSub(window, sprite, 3);
        break;
    case 0x2C7:
        _menuFieldFlashCursor(window, sprite, 0);
        break;
    case 0x2C8:
        _menuFieldFlashCursor(window, sprite, 1);
        break;
    case 0x2C9:
        _menuFieldFlashCursor(window, sprite, 2);
        break;
    case 0x2CA:
        _menuFieldFlashCursor(window, sprite, 3);
        break;
    case 0x670:
        _menuFieldMenuCursor(window, sprite, 0);
        break;
    case 0x671:
        _menuFieldMenuCursor(window, sprite, 1);
        break;
    case 0x672:
        _menuFieldMenuCursor(window, sprite, 2);
        break;
    case 0x673:
        _menuFieldMenuCursor(window, sprite, 3);
        break;
    case 0x2CB:
        _menuFieldCursorCheck(window, sprite, 0);
        break;
    case 0x2CC:
        _menuFieldCursorCheck(window, sprite, 1);
        break;
    case 0x2CD:
        _menuFieldCursorCheck(window, sprite, 2);
        break;
    case 0x2CE:
        _menuFieldCursorCheck(window, sprite, 3);
        break;
    }
}
extern "C++" {
static void _menuFieldMenuCursor(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, long p2) {
    s16 temp_r0;

    temp_r0 = M2C_FIELD(p0, s16 *, 0x9E);
    s16 prev = M2C_FIELD(p0, s16 *, 0xA2);
    if (temp_r0 == p2) {
        if (prev != temp_r0) {
            winAnimeCursor((tagWINDOW_WORK*)(p0), (tagSPRITE_WORK*)(p1));
            _fieldMenuTimer = 0.0f;
        }
        winSpriteSetDisp((tagSPRITE_WORK*)(p1), 1U);
    } else {
        winSpriteSetDisp((tagSPRITE_WORK*)(p1), 0U);
    }
    if ((s8) M2C_FIELD(p0, u8 *, 1) == 3) {
        winSetSequence((tagSEQ_WORK*)(((u8*)(p1) + 0xC)), 0U);
    }
}
}

extern "C++" {
static void _menuFieldFlashCursor(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, long p2) {
    if ((s16) M2C_FIELD(p0, s16 *, 0x9E) == p2) {
        M2C_FIELD(p1, f32 *, 0x70) = (f32) _menuFieldCursorAngle;
        winSpriteSetDisp((tagSPRITE_WORK*)(p1), 1U);
        return;
    }
    winSpriteSetDisp((tagSPRITE_WORK*)(p1), 0U);
}
}

extern "C++" {
static void _menuFieldCursorCheck(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, long p2) {
    s32 color = M2C_FIELD(p0, s16 *, 0x9E);
    winSpriteSetDisp(p1, 0U);
    if (M2C_FIELD(p1, u32 *, 0x4C) != 0) {
        if (color == p2) {
            color = 0xF0F0F0FF;
        } else {
            color = 0xF0F0F080;
        }
        p2 = (s16)((M2C_FIELD(p1, s16 *, 0x54) - (s16)(GSmsgGetRect(M2C_FIELD(p1, u32 *, 0x4C)) >> 16)) / 2);
        s16 y = (M2C_FIELD(p1, s16 *, 0x56) - (s16)(u16)GSmsgGetRect(M2C_FIELD(p1, u32 *, 0x4C))) / 2 - 2;
        GSmsgPrint2(M2C_FIELD(p0, s32 *, 0x1C), p2, y, color, M2C_FIELD(p1, u32 *, 0x4C));
    }
}
}

extern "C++" {
static void _menuFieldDrawItemSub(tagWINDOW_WORK* p0, tagSPRITE_WORK* p1, long p2) {
    f32 temp_f0;
    f32 temp_f2;
    s16 temp_r31;

    temp_r31 = M2C_FIELD(p0, s16 *, 0x9E);
    temp_f2 = (255.0f * timeGetLastFrameSec()) / 0.4f;
    if (temp_r31 == p2) {
        winSpriteSetDisp((tagSPRITE_WORK*)(p1), 1U);
        _animAlpha(p2);
    } else {
        temp_f0 = _menuFiledAlpha[p2];
        if (temp_f0 > 0.0f) {
            _menuFiledAlpha[p2] = temp_f0 - temp_f2;
            if (_menuFiledAlpha[p2] < 0.0f) {
                _menuFiledAlpha[p2] = 0.0f;
            }
        }
    }
    M2C_FIELD(p1, s32 *, 0x64) = (s32) (barcolor | (u8) (s32) _menuFiledAlpha[p2]);
}
}

extern "C++" {
static void _animAlpha(long p0) {
    f32 temp_f1;
    f32 temp_f31;
    f32 var_f1;

    temp_f1 = _fieldMenuTimer + ((3.1415927f * (2.0f * menuGetLastTime())) / _cursorSec);
    _fieldMenuTimer = temp_f1;
    if (temp_f1 >= 6.2831855f) {
        _fieldMenuTimer = temp_f1 - 6.2831855f;
    }
    temp_f31 = _max_alpha - _min_alpha;
    f32 s = (1.0f + (f32) sin((f64) _fieldMenuTimer)) / 2.0f;
    f32 v = temp_f31 * s;
    var_f1 = _min_alpha + v;
    if (var_f1 > 255.0f) {
        var_f1 = 255.0f;
    }
    _menuFiledAlpha[p0] = var_f1;
}
}

extern "C" {
s32 menuFieldMainCtrl(void *p0) {
    switch ((s8) M2C_FIELD(p0, u8 *, 1)) {
    case 0:
        if ((s8) M2C_FIELD(p0, u8 *, 2) == 0) {
            winSeqSetMenu(M2C_FIELD(p0, s32 *, 4), 1U);
            int i;
            s16 cur = M2C_FIELD(p0, s16 *, 0x9E);
            _fieldMenuTimer = 0.0f;
            f32* alpha = _menuFiledAlpha;
            for (i = 0; i < 5; i++) {
                if (cur == i) {
                    *alpha = 255.0f;
                } else {
                    *alpha = 0.0f;
                }
                alpha++;
            }
            M2C_FIELD(p0, u8 *, 2) = 1U;
        }
        break;
    case 3:
        if ((s8) M2C_FIELD(p0, u8 *, 2) == 0) {
            winSeqSetMenu(M2C_FIELD(p0, s32 *, 4), 7U);
            M2C_FIELD(p0, u8 *, 2) = 1U;
        }
        break;
    }
    return 0;
}
}

extern "C" {
s32 menuFieldMain(u8 p0) {
    HeroMoveEvent events[4];
    s32 sp8;
    HeroMoveEvent* var_r28;
    s32 temp_r29;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r3_7;
    s32 var_r27;
    s32 var_r27_2;
    s32 temp_r3_6;
    u16 var_r31;
    u32 temp_r3_2;

    if (fadeCheck(0) != 0) {
        return 0;
    }
    temp_r29 = heroMoveCheckEvent(events);
    var_r28 = events;
    for (var_r27 = 0; var_r27 < temp_r29; var_r27++) {
        floorEventExecScript(4, var_r28->eventID);
        var_r28++;
    }
    menuIntUnderTakerDispIconOff2();
    heroMoveInitEvent();
    mailMainReceiveTerminate();
    GSthreadSwitch();
    floorFieldCameraPause();
    GSmodelAllPauseAnimation();
    _openFieldMenu = 1;
    GSthreadSwitch();
    menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    while (menuGetOffScreenFlag() == 0) {
        GSthreadSwitch();
    }
    temp_r3_2 = soundGetEnvID();
    _soundEnvID = temp_r3_2;
    if (temp_r3_2 != 0) {
        _soundEnvVol = soundGetVolume();
    }
    GSsndPushVolumeALL(0x55, 0x1F4, 1U, 1U);
    GSgfxVideoSetLockFrameRate(0);
    if (GSflagGet(0x30DU) == 0) {
        if (_menuFieldCheckPDA() != 0) {
            var_r27_2 = 0x57;
        } else {
            var_r27_2 = 0x58;
        }
    } else {
        var_r27_2 = 0x70;
    }
    fn_80233AB4();
    switch ((s32) p0) {
    case 0:
        if (GSflagGet(0x30DU) == 0) {
            while (1) {
                GSgfxVideoSetLockFrameRate(0);
                _menuFiledAlpha[0] = 255.0f;
                _menuFiledAlpha[1] = 255.0f;
                _menuFiledAlpha[2] = 255.0f;
                _menuFiledAlpha[3] = 255.0f;
                _menuFiledAlpha[4] = 255.0f;
                temp_r3_3 = _menuFieldCheckCursor(menuOpen(var_r27_2, 1));
                if (temp_r3_3 == 0) {
                    menuCloseCustom(var_r27_2, 0, 1);
                    menuPokemonOpen(1, 0, 0);
                    GSmodelAllPauseAnimation();
                } else if (temp_r3_3 == 1) {
                    menuCloseCustom(var_r27_2, 0, 1);
                    menuPdaOpen();
                    GSmodelAllPauseAnimation();
                } else if (temp_r3_3 == 2) {
                    menuCloseCustom(var_r27_2, 0, 1);
                    var_r31 = menuPocket2Open(0, &sp8, 0);
                    GSmodelAllPauseAnimation();
                    if (var_r31 == 0) {
                        continue;
                    }
                    temp_r3_4 = menuPocket2GetItemScript(var_r31);
                    if ((u32)temp_r3_4 != 0xFFFFFFFF) {
                        heroMoveAddAutoEvent(temp_r3_4, (s32) var_r31, sp8, 0, 0);
                    }
                    break;
                } else if (temp_r3_3 == 3) {
                    menuCloseCustom(var_r27_2, 0, 1);
                    menuReport();
                } else {
                    break;
                }
                GSthreadSwitch();
            }
        } else {
            while (1) {
                GSgfxVideoSetLockFrameRate(0);
                temp_r3_5 = menuOpen(var_r27_2, 1);
                if (temp_r3_5 == 0) {
                    menuClose(var_r27_2);
                    menuPokemonOpen(1, 0, 0);
                } else if (temp_r3_5 == 1) {
                    if (scriptContinueSave() == 1) {
                        menuOffScreenRelease();
                        _openFieldMenu = 0;
                        GSthreadSwitch();
                    }
                } else {
                    break;
                }
            }
        }
        break;
    case 1:
        var_r31 = menuPocket2Open(0, &sp8, 0);
        if (var_r31 != 0) {
            temp_r3_7 = menuPocket2GetItemScript(var_r31);
            if ((u32)temp_r3_7 != 0xFFFFFFFF) {
                heroMoveAddAutoEvent(temp_r3_7, (s32) var_r31, sp8, 0, 0);
            }
        }
        break;        break;
    case 2:
    case 3:
        break;
    }
    menuPocket2GetItemScript(var_r31);
    GSsndPopVolumeALL(0x1F4U, 1U, 1U);
    if ((u32) _soundEnvID == soundGetEnvID()) {
        soundSetVolumeID(_soundEnvID, 0x1F4, _soundEnvVol);
    }
    GSthreadSwitch();
    menuClose(var_r27_2);
    menuReleaseOffScreen(20.0f / GSgfxVideoGetVsyncRate());
    menuCloseSync(var_r27_2, 1);
    GSgfxVideoSetLockFrameRate(1);
    heroMoveTermEvent();
    GSmodelAllUnpauseAnimation();
    floorFieldCameraUnpause();
    _openFieldMenu = 0;
    menuIntUnderTakerDispIconRestore2();
    return 0;
}
}

extern "C++" {
GSvec::GSvec() {
}
}

u8 menuFieldIsOpen(void) {
    return _openFieldMenu;
}
extern "C++" {
static s32 _menuFieldCheckCursor(long p0) {
    s32 var_r3;

    if (_menuFieldCheckPDA() != 0) {
        return p0;
    }
    var_r3 = p0;
    if (p0 >= 1) {
        var_r3 = p0 + 1;
    }
    return var_r3;
}
}

extern "C++" {
static u8 _menuFieldCheckPDA() {
    if (pokecoloGetRomVersion() == 1) {
        return 1U;
    }
    return GSflagGet(0x3F1U) != 0;
}
}

}
