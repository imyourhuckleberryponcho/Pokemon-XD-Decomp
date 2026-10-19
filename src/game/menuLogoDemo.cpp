// WIP (smallmenu, 2026-10-15): 59/62 exact. Needs -inline noauto,deferred (source bottom-to-top); LAYOUT/CONST/CALLS/DATA OK. Non-exact: _setTextureWindow, _menuSoundReadWave (regs), fn_80085E88 (jumptable symbol name only).
#pragma peephole off
#pragma pool_strings off
#include <dolphin/types.h>
#include <game/shared/menu_work.h>

struct GStexture;
struct GSvec2 {
    f32 x, y;
};
struct GSgfxColAu8 {
    union {
        u32 rgba;
        u8 v[4];
    };
};

struct OSThread2 {
    u8 pad[0x318];
};

struct OPDEMO_SE_SEQUENCE_dd_ {
    u16 time;
    u16 id;
    u16 pad;
};

struct CURSOR {
    s16 top;
    s16 pos;
};

struct KeyInfo2 {
    u8 pad0[4];
    u16 buttons;
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};

struct GSmtx44 {
    f32 m[4][4];
};

class GSgfxLayer {
public:
    u8 pad0[0xd54];
    s32 projType;
    f32 proj[6];
    u8 pad_d70[0x1684 - 0xd70];
    f32 nearZ;
    f32 farZ;
    u8 pad_168c[0x16a6 - 0x168c];
    u8 f16a6;
    u8 f16a7;
    u32 dirty16a8;
    u32 dirty16ac;
    u8 pad_16b0[0x170c - 0x16b0];
    u32 dirty170c;
    u8 pad_1710[0x1760 - 0x1710];
    u32 dirty1760;
    u32 dirty1764;
    u8 pad_1768[0x17c4 - 0x1768];
    u32 dirty17c4;
    u8 pad_17c8[0x19a0 - 0x17c8];
    GSlayerCam* cam;
};

extern "C" {
extern GSmtx44 mtxIdent;
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
double sin(double);
void fadeSet(s32 type, f32 time);
void fadeCheck(s32);
void GSthreadSwitch(void);
u8 GSmoviePlayCheck(u32 movie);
void GSmoviePlay(u32 movie, s32, int loop, GStexture* tex);
void GSmovieStop(u32 movie);
void soundOpenPlay(s32, s32, s32);
void soundOpenPlayFadeOutIn(s32, s32, s32, s32);
void soundInitBGM(void);
void soundInit(void);
void soundOpenWave(u32 id);
void floorLink(u32 floorID, u32 posIndex);
void floorSetFadeScript(u32 out, u32 in);
u32 floorGetPrevFloorID(void);
u8 GSfloorChange(u32 id);
bool GSflagTest(u32 id);
void winSeqSetMenu(s32 menuID, u32 id);
bool winSeqCheckMove(s32 menuID);
void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on);
s32 winSpriteGetLayerID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
KeyInfo2* windowGetKeyInfo(void);
void* savedataGetStatus(void* save, s32 kind);
void gamedatasaveSetStatus(void* ptr, u32 kind, u32 value);
u32 gamedatasaveGetStatus(void* ptr, u32 kind);
void* memcardMemAllocForSavedata(void);
void* memcardMemFreeForSavedata(void* ptr);
s32 memcardTaskCall(s32, s32, s32);
u32 heroGetStatus(void* hero, u32 selector, u16 index);
void winMsgOpen(s32 type, s32 msg, s32 a, s32 b);
void winMsgClose(bool flag);
s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 initial);
s32 GSmovieGetStatus(u32 id);
bool pauseIsPause(void);
f32 pokecoloGetFrameTime(void);
void menuClose(s32 menuID);
s32 menuOpen(s32 menuID, s32);
void menuCloseSync(s32 menuID, s32);
void menuOpenCustom(s32 menuID, ...);
void menuCloseCustom(s32 menuID, s32, s32);
void menuSetPosition(s32 menuID, s16 x, s16 y);
void menuTitleSetStartStatus(s32);
s32 GSfsysGetDriveStatus(void);
u32 GSinputButtonsChanged(s32 pad);
u32 GSinputButtonsPressed(s32 pad);
void GSinputReadStart(void);
void GSinputReadEnd(void);
s32 GSinputRead(s32);
u8 GSgfxVideoGetVsyncRate(void);
f32 GSgfxVideoGetLastRenderTime(void);
void GSgfxVideoSetMode(s32, s32, s32, s32, s32);
void GSgfxVideoSetFilter(u8* filter);
f32 timeGetLastFrameSec(void);
s32 pokecoloGetRomVersion(void);
void floorLayerConfig(u32 floorID, u8 kind);
GSgfxLayer* GSgfxLayerFindByID(s32 id);
void GSprimSetBlendMode(s32 mode);
void GSprimSetQuadVertexOrder(s32 order);
void GSprimDraw2DTexQuad4V(GSvec2* pos, GSvec2* uv, GStexture* tex, GSgfxColAu8 col);
void GSmtx44Ortho(f32* m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void* GSresGetResourceAllGroup(u32 id);
s32 GSfsysGetStatus(u32 id);
void GSfsysReadWait(u32 id);
void GSfsysFree(u32 id);
void GSfsysInit(u32, u32, u32, u32);
void GSsndInit(u32 a, u32 maxStack, u32 b, u32 maxListener, u32 maxEmitter);
void GSlogWrite(const char*, ...);
void fn_8005C8CC(void);
s32 windowGetActiveID(void);
u8 windowCheckCursor(s32 id, u8 wait);
s32 windowGetValue(s32 id);
tagWINDOW_WORK* windowSearchID(s32 id);
u32 OSGetResetCode(void);
u32 OSGetProgressiveMode(void);
void OSSetProgressiveMode(u32 on);
u32 VIGetDTVStatus(void);
void VIWaitForRetrace(void);
s32 OSCreateThread(OSThread2* thread, void* (*func)(void*), void* param, void* stack, u32 stackSize, s32 priority, u16 attr);
s32 OSResumeThread(OSThread2* thread);
}

void GSprimSetup2DRender(GSgfxLayer* layer);
static void _menuSetScreenFilter(bool on);
static void _menuSoundReadWave(u32 a, u32 b, u32 c, u32 d);
static void _menuSoundReadWaveWait(void);
static void _menuWait(f32 time);
static u32 _PlaySE(OPDEMO_SE_SEQUENCE_dd_* seq, u32 count, u32 i);
static u32 _menuOpeningDemo_SE(u32 i);
static u32 _menuAutoDemo_SE(u32 i);
static void _NintendoInit(void);
static void _NintendoMain(void);
static void _NintendoExit(void);
static void _NintendoWarningInit(void);
static void _NintendoWarningMain(void);
static void _NintendoWarningExit(void);
static void _menuNintendoWarningButtonNormal(tagWINDOW_WORK* w);
static void _setTextureWindow(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, GStexture* tex);
static void _setTexture(GStexture* tex, GSvec2* pos, GSvec2* uv, GSgfxColAu8 col);
static void _ProgressiveModeChange(void);
static void _ProgressiveModeMain(void);
static void _ProgressiveModeSeq(void);
static void _NormalModeSeq(void);
static s8 _ProgressiveModeYesNo(s16 x, s16 y, s32 initial);
static void _menuGSfsysInitWait(void);
static void _menuGSfsysInit(void);
static void* _menuGSfsysInitThread(void* p);
static void* _menuSoundReadWaveThread(void* p);
extern "C" {
void menuNintendoWarning(void);
void fn_80087254(void);
void fn_80087314(u8 x);
}
void menuGSfsysInitWait(void);
void menuGSfsysInit(void);

static OPDEMO_SE_SEQUENCE_dd_ _se_sequence[33] = {
    {0x03DF, 0x0424, 0x03B9}, {0x0412, 0x0428, 0x0000}, {0x0433, 0x0429, 0x0000}, {0x043B, 0x03A3, 0x0000},
    {0x046C, 0x03A1, 0x0000}, {0x049D, 0x0424, 0x03B9}, {0x04D0, 0x03AD, 0x0000}, {0x057C, 0x013F, 0x0000},
    {0x05BE, 0x0155, 0x0000}, {0x05C8, 0x0156, 0x0000}, {0x05E8, 0x0170, 0x0000}, {0x0605, 0x00CE, 0x0000},
    {0x0667, 0x03C3, 0x0000}, {0x0669, 0x03B9, 0x0000}, {0x06CF, 0x0193, 0x0000}, {0x070B, 0x0180, 0x0000},
    {0x0764, 0x01C3, 0x03B9}, {0x078D, 0x01BF, 0x0000}, {0x07DB, 0x03FA, 0x0000}, {0x080D, 0x03FB, 0x0000},
    {0x0823, 0x03FC, 0x0000}, {0x0842, 0x03A3, 0x0000}, {0x086B, 0x0371, 0x0000}, {0x0883, 0x0373, 0x0000},
    {0x08FB, 0x01D2, 0x0000}, {0x0918, 0x03B9, 0x0000}, {0x098F, 0x01D9, 0x0000}, {0x09B6, 0x041B, 0x0000},
    {0x09C2, 0x03EB, 0x0000}, {0x09D0, 0x01DA, 0x0000}, {0x0A08, 0x03B1, 0x0000}, {0x0A3B, 0x03B8, 0x0000},
    {0x0BB8, 0x0000, 0x0000},
};
static OPDEMO_SE_SEQUENCE_dd_ _opening_se_sequence[3] = {
    {0x013D, 0x016A, 0x0000},
    {0x05C3, 0x016A, 0x0000},
    {0x0BB8, 0x0000, 0x0000},
};

static u32 _progressive_mode_change = (u32)-1;
static s32 _sound_wave_complete;
static s32 _gsfsysinit_complete;
static u8 _menuMainExec;
static f32 _warningSeqTimer;
static s32 _warningSeq;
static f32 _warningTimer;
extern "C" {
double lbl_804EA9F0;
}

static inline int _IsRestart(void)
{
    return (OSGetResetCode() & 0x80000000) ? 1 : 0;
}

static void _menuWait(f32 time)
{
    f32 elapsed = 0.0f;
    while (elapsed < time) {
        GSthreadSwitch();
        elapsed += GSgfxVideoGetLastRenderTime() / (f32)GSgfxVideoGetVsyncRate();
    }
}

static void* _menuSoundReadWaveThread(void* p)
{
    u32* a = (u32*)p;
    if (a[0] != 0) {
        soundOpenWave(a[0]);
    }
    if (a[1] != 0) {
        soundOpenWave(a[1]);
    }
    if (a[2] != 0) {
        soundOpenWave(a[2]);
    }
    if (a[3] != 0) {
        soundOpenWave(a[3]);
    }
    _sound_wave_complete--;
    return 0;
}

static void _menuSoundReadWave(u32 a, u32 b, u32 c, u32 d)
{
    static u8 stack[0x1000];
    static OSThread2 thread;
    static u32 arg[4];
    arg[0] = a;
    arg[1] = b;
    arg[2] = c;
    arg[3] = d;
    _sound_wave_complete++;
    OSCreateThread(&thread, _menuSoundReadWaveThread, arg, stack + 0xffc, 0x1000, 0x10, 1);
    OSResumeThread(&thread);
}

static void _menuSoundReadWaveWait(void)
{
    while (_sound_wave_complete != 0) {
        GSthreadSwitch();
    }
}

static s8 _ProgressiveModeYesNo(s16 x, s16 y, s32 initial)
{
    f32 timer;
    s8 prev;
    s8 result;
    if (initial != 0) {
        initial = 1;
    }
    menuOpenCustom(0x35, windowGetActiveID(), &initial, 8, 0, 0);
    if (x >= 0 && y >= 0) {
        menuSetPosition(0x35, x, y);
    }
    timer = 0.0f;
    prev = -1;
    while (timer < 10.0f) {
        if (!windowCheckCursor(0x35, 0)) {
            result = windowGetValue(0x35);
            break;
        }
        s16 cur = windowSearchID(0x35)->cursor;
        if (prev != cur) {
            timer = 0.0f;
            prev = cur;
        }
        GSthreadSwitch();
        timer += GSgfxVideoGetLastRenderTime() / (f32)GSgfxVideoGetVsyncRate();
    }
    if (timer >= 10.0f) {
        result = windowSearchID(0x35)->cursor;
    }
    menuCloseCustom(0x35, 0, 1);
    return result;
}

static void _menuSetScreenFilter(bool on)
{
    static u8 filt_off[7] = {0, 0, 0x15, 0x16, 0x15, 0, 0};
    static u8 filt_on[7] = {8, 8, 0xA, 0xC, 0xA, 8, 8};
    if (on) {
        GSgfxVideoSetFilter(filt_on);
    } else {
        GSgfxVideoSetFilter(filt_off);
    }
}

static void* _menuGSfsysInitThread(void* p)
{
    GSfsysInit(0x40, 0, 0, 0);
    _gsfsysinit_complete = 1;
    return 0;
}

static void _menuGSfsysInit(void)
{
    static u8 stack[0x1000];
    static OSThread2 thread;
    if (_gsfsysinit_complete != 1) {
        OSCreateThread(&thread, _menuGSfsysInitThread, 0, stack + 0xffc, 0x1000, 0x10, 1);
        OSResumeThread(&thread);
    }
}

static void _menuGSfsysInitWait(void)
{
    while (_gsfsysinit_complete == 0) {
        GSthreadSwitch();
    }
}

extern "C" {
void menuGSfsysInit(void)
{
    _menuGSfsysInit();
}
}

extern "C" {
void menuGSfsysInitWait(void)
{
    _menuGSfsysInitWait();
}
}

static void _NintendoWarningInit(void)
{
    GSprimSetup2DRender(GSgfxLayerFindByID(7));
    _warningSeq = 0;
    _warningSeqTimer = 0.0f;
    menuOpen(0x112, 1);
}

static void _NintendoWarningMain(void)
{
}

static void _NintendoWarningExit(void)
{
    GSgfxLayerFindByID(7);
    menuClose(0x112);
    menuCloseSync(0x112, 1);
}

static void _NintendoInit(void)
{
    floorLayerConfig(0, 5);
    if (pokecoloGetRomVersion() != 1) {
        _ProgressiveModeMain();
    } else {
        fn_80087254();
    }
    _ProgressiveModeChange();
    GSprimSetup2DRender(GSgfxLayerFindByID(7));
    if (pokecoloGetRomVersion() != 1) {
        menuNintendoWarning();
    } else {
        menuGSfsysInit();
    }
    menuGSfsysInitWait();
    GSfsysReadWait(0xd);
    menuOpen(0x17, 0);
    fadeSet(2, 0.5f);
    fn_8005C8CC();
    memset((void*)0x80001801, 0, 0x17ff);
    GSfsysFree(0xd);
}

static void _ProgressiveModeSeq(void)
{
    GSthreadSwitch();
    winMsgOpen(1, 0x4a39, 1, 1);
    if (_ProgressiveModeYesNo(0x2d, 0xbe, 0) == 0) {
        if (_IsRestart() == 1) {
            if (OSGetProgressiveMode() == 0) {
                _progressive_mode_change = 1;
            }
        } else {
            _progressive_mode_change = 1;
        }
        winMsgOpen(1, 0x4a3a, 1, 1);
        _menuWait(2.0f);
    } else {
        if (_IsRestart() == 1) {
            if (OSGetProgressiveMode() == 1) {
                _progressive_mode_change = 0;
            }
        } else {
            _progressive_mode_change = 0;
        }
        winMsgOpen(1, 0x4a3b, 1, 1);
        _menuWait(2.0f);
    }
    winMsgClose(1);
}

static void _ProgressiveModeMain(void)
{
    _progressive_mode_change = (u32)-1;
    VIWaitForRetrace();
    VIWaitForRetrace();
    if (!_IsRestart()) {
        if (VIGetDTVStatus() == 1) {
            if (OSGetProgressiveMode() == 1) {
                _ProgressiveModeSeq();
            } else {
                GSthreadSwitch();
                GSinputReadStart();
                if (GSinputButtonsPressed(1) & 0x200) {
                    _ProgressiveModeSeq();
                } else {
                    _NormalModeSeq();
                }
                GSinputReadEnd();
            }
        } else {
            _NormalModeSeq();
            OSSetProgressiveMode(0);
        }
    } else {
        _NormalModeSeq();
    }
}

extern "C" {
void fn_80087314(u8 x)
{
    _progressive_mode_change = (x == 1) ? 1 : 0;
    fadeCheck(1);
    _menuWait(2.0f);
}
}

extern "C" {
void fn_80087254(void)
{
    s32 r;
    _progressive_mode_change = (u32)-1;
    VIWaitForRetrace();
    VIWaitForRetrace();
    if (!_IsRestart()) {
        do {
            GSthreadSwitch();
            GSinputReadStart();
            r = GSinputRead(1);
            GSinputReadEnd();
        } while (r != 0);
        GSinputReadStart();
        if (GSinputButtonsPressed(1) & 0x200) {
            fn_80087314(0);
        } else if (VIGetDTVStatus() == 1) {
            fn_80087314(1);
        } else {
            fn_80087314(0);
        }
        GSinputReadEnd();
    }
}
}

static void _NormalModeSeq(void)
{
    GSthreadSwitch();
    fadeCheck(1);
    _menuWait(2.0f);
}

static void _NintendoMain(void)
{
    s32 st;
    while (1) {
        st = GSfsysGetStatus(10);
        if (st < 0) {
            GSlogWrite("読み出しエラー\n");
        }
        if (st == 0) {
            break;
        }
        GSthreadSwitch();
    }
    GSsndInit(2, 1, 0x20, 1, 0x10);
    soundInit();
    _menuSoundReadWave(1, 0, 0, 0);
    _menuSoundReadWaveWait();
}

static void _ProgressiveModeChange(void)
{
    if ((s32)_progressive_mode_change != -1) {
        GSgfxVideoGetVsyncRate();
        OSSetProgressiveMode(_progressive_mode_change);
        if (_progressive_mode_change == 1) {
            GSgfxVideoSetMode(0, 1, 0, 1, 1);
        } else {
            GSgfxVideoSetMode(0, 1, 0, 1, 0);
        }
    }
}

static void _NintendoExit(void)
{
    _menuSoundReadWave(3, 0, 0, 0);
    fadeSet(3, 0.5f);
    fadeCheck(1);
    menuClose(0x17);
    _menuSoundReadWaveWait();
}

extern "C" {
void menuNintendoWarning(void)
{
    _NintendoWarningInit();
    _NintendoWarningMain();
    _NintendoWarningExit();
}
}

static void _setTexture(GStexture* tex, GSvec2* pos, GSvec2* uv, GSgfxColAu8 col)
{
    GSprimDraw2DTexQuad4V(pos, uv, tex, col);
}

static void _setTextureWindow(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, GStexture* tex)
{
    GSvec2 pos[4];
    GSvec2 uv[4];
    GSgfxColAu8 col;
    u16 a;
    pos[0].x = (f32)sp->x;
    pos[0].y = (f32)sp->y;
    pos[1].x = (f32)(sp->x + sp->w);
    pos[1].y = (f32)sp->y;
    pos[2].x = (f32)(sp->x + sp->w);
    pos[2].y = (f32)(sp->y + sp->h);
    pos[3].x = (f32)sp->x;
    pos[3].y = (f32)(sp->y + sp->h);
    uv[0].x = 0.0f;
    uv[0].y = 0.0f;
    uv[1].x = 1.0f;
    uv[1].y = 0.0f;
    uv[2].x = 1.0f;
    uv[2].y = 1.0f;
    uv[3].x = 0.0f;
    uv[3].y = 1.0f;
    col.v[0] = 0xff;
    col.v[1] = 0xff;
    col.v[2] = 0xff;
    a = (u16)(w->alpha * sp->alpha) / 255;
    if (a > 255) {
        a = 255;
    }
    col.v[3] = a;
    _setTexture(tex, pos, uv, col);
}

extern "C" {
void menuNintendoWarningHook(tagWINDOW_WORK* w, tagSPRITE_WORK* sp)
{
    GSgfxLayer* layer = GSgfxLayerFindByID(7);
    f32 mtx[16];
    GSmtx44Ortho(mtx, -23.0f, 448.0f, 0.0f, 608.0f, 0.0f, -30000.0f);
    layer->projType = 1;
    layer->proj[0] = mtx[0];
    layer->proj[1] = mtx[3];
    layer->proj[2] = mtx[5];
    layer->proj[3] = mtx[7];
    layer->proj[4] = mtx[10];
    layer->proj[5] = mtx[11];
    GSlayerCam* cam = layer->cam;
    memcpy(cam->data + 1, &mtxIdent, 0x30);
    cam->data[0] |= 1;
    layer->nearZ = 0.0f;
    layer->farZ = 30000.0f;
    if (layer->f16a7) {
        if (layer->f16a6) {
            layer->dirty170c |= 0x100;
            layer->dirty17c4 |= 0x100;
        }
        layer->dirty170c |= 0x40;
        layer->dirty16a8 |= 0x40;
        layer->dirty17c4 |= 0x40;
        layer->dirty1760 |= 0x40;
    }
    layer->dirty16ac |= 0x20;
    layer->dirty16a8 |= 1;
    layer->dirty1764 |= 0x20;
    layer->dirty1760 |= 1;
    GSprimSetup2DRender(layer);
    GSprimSetBlendMode(1);
    GSprimSetQuadVertexOrder(1);
    switch (sp->id) {
    case 0x31:
        if (_warningSeq >= 2) {
            if (_warningTimer > 1.0f) {
                _warningTimer = 0.0f;
            }
            f32 sv = (f32)sin(3.1415927f * _warningTimer);
            sp->alpha = (u8)(255.0f * sv);
            winSpriteSetDisp(sp, true);
            GStexture* t = (GStexture*)GSresGetResourceAllGroup(0x215a1200);
            _setTextureWindow(w, sp, t);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x30:
        _setTextureWindow(w, sp, (GStexture*)GSresGetResourceAllGroup(0x21591200));
        break;
    }
}
}

static void _menuNintendoWarningButtonNormal(tagWINDOW_WORK* w)
{
    if (w != 0) {
        if (windowGetKeyInfo()->buttons & 0xFF0) {
            w->done = 1;
        }
    }
}

extern "C" {
void menuNintendoWarningButton(tagWINDOW_WORK* w)
{
    if (_warningSeq == 2) {
        _menuNintendoWarningButtonNormal(w);
    } else if (_warningSeq == 3) {
        w->done = 1;
    }
}
}

extern "C" {
void menuNintendoWarningCtrl(tagWINDOW_WORK* w)
{
    f32 dt = timeGetLastFrameSec();
    switch (w->state) {
    case 0:
        _warningSeq = 0;
        _warningSeqTimer = 0.0f;
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x1cc);
            w->seqSet = 1;
            menuGSfsysInit();
        }
        break;
    case 2:
        switch (_warningSeq) {
        case 0:
            if (!winSeqCheckMove(w->menuID)) {
                _warningSeq = 1;
            }
            break;
        case 1:
            _warningSeqTimer += dt;
            if (_warningSeqTimer >= 1.5f) {
                _warningSeq = 2;
                _warningTimer = 0.0f;
            }
            break;
        case 2:
            _warningTimer += dt;
            _warningSeqTimer += dt;
            if (_warningSeqTimer >= 60.0f) {
                _warningSeq = 3;
            }
            break;
        case 3:
            _warningTimer += dt;
            break;
        }
        break;
    case 3:
        _warningTimer += dt;
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x1d0);
            w->seqSet = 1;
        }
        break;
    }
}
}

extern "C" {
void menuNintendo(void)
{
    _NintendoInit();
    _NintendoMain();
    _NintendoExit();
}
}

extern "C" {
void menuNintendoInit(void)
{
}
}

extern "C" {
void menuNintendoMain(void)
{
}
}

extern "C" {
void menuNintendoExit(void)
{
}
}

extern "C" {
void menuTpcInit(void)
{
    _menuMainExec = 0;
    fadeSet(2, 0.0f);
    fadeCheck(1);
    soundInitBGM();
    GSmoviePlay(0x7d9, 1, 0, 0);
    soundOpenPlay(8, 0, 0x7f);
    memset((void*)0x80001803, 0, 0x17fd);
}
}

extern "C" {
void menuTpcMain(void)
{
    if (_menuMainExec != 1) {
        while (GSmoviePlayCheck(0x7d9) == 1) {
            GSthreadSwitch();
        }
    }
    GSfloorChange(0x39a);
    floorSetFadeScript(0, 0);
    _menuMainExec = 1;
}
}

extern "C" {
void menuTpcExit(void)
{
    fadeSet(3, 0.0f);
    fadeCheck(1);
}
}

extern "C" {
void menuGeniusInit(void)
{
    _menuMainExec = 0;
    _menuSoundReadWave(2, 0, 0, 0);
    _menuSoundReadWaveWait();
    fadeSet(2, 0.0f);
    fadeCheck(1);
    GSmoviePlay(0x7da, 1, 0, 0);
    soundOpenPlay(8, 0, 0x7f);
    memset((void*)0x80001805, 0, 0x17fb);
}
}

extern "C" {
void menuGeniusMain(void)
{
    if (_menuMainExec != 1) {
        while (GSmoviePlayCheck(0x7da) == 1) {
            GSthreadSwitch();
        }
    }
    GSfloorChange(0x384);
    floorSetFadeScript(0, 0x5960008);
    _menuMainExec = 1;
}
}

extern "C" {
void menuGeniusExit(void)
{
    fadeSet(3, 0.0f);
    fadeCheck(1);
}
}

extern "C" {
void menuBattleDemoInit(void)
{
}
}

extern "C" {
void menuBattleDemoMain(void)
{
}
}

extern "C" {
void menuBattleDemoExit(void)
{
}
}

static u32 _PlaySE(OPDEMO_SE_SEQUENCE_dd_* seq, u32 count, u32 i)
{
    if (i >= count) {
        return i;
    }
    if ((s32)seq[i].time <= 0) {
        i++;
    }
    return i;
}

static u32 _menuAutoDemo_SE(u32 i)
{
    return _PlaySE(_se_sequence, 0x21, i);
}

extern "C" {
void menuAutoDemoInit(void)
{
    fadeSet(2, 0.0f);
    fadeCheck(1);
    _menuSetScreenFilter(false);
    GSmoviePlay(0x7dc, 0, 0, 0);
    soundOpenPlay(8, 0, 0x7f);
}
}

extern "C" {
void menuAutoDemoMain(void)
{
    u32 se = 0;
    while (GSmoviePlayCheck(0x7dc) == 1) {
        s32 st = GSfsysGetDriveStatus();
        if (st == 0xb || st == 5) {
            GSthreadSwitch();
            continue;
        }
        u32 changed = GSinputButtonsChanged(1);
        u32 pressed = GSinputButtonsPressed(1);
        if ((pressed & changed) & 0x1300) {
            GSmovieStop(0x7dc);
            menuTitleSetStartStatus(1);
            break;
        }
        se = _menuAutoDemo_SE(se);
        GSthreadSwitch();
    }
    soundOpenPlayFadeOutIn(8, 1000, 0, 0x7f);
    GSfloorChange(0x384);
    floorSetFadeScript(0, 0x5960008);
}
}

extern "C" {
void menuAutoDemoExit(void)
{
    fadeSet(3, 0.0f);
    fadeCheck(1);
    _menuSetScreenFilter(true);
}
}

extern "C" {
void menuEndingDemoInit(void)
{
    fadeSet(2, 0.0f);
    fadeCheck(1);
    _menuSetScreenFilter(false);
    GSmoviePlay(0x8eb, 0, 0, 0);
    soundOpenPlay(8, 0, 0x7f);
}
}

extern "C" {
void menuEndingDemoMain(void)
{
    u32 prev = floorGetPrevFloorID();
    while (GSmoviePlayCheck(0x8eb) == 1) {
        GSfsysGetDriveStatus();
        GSthreadSwitch();
    }
    soundOpenPlayFadeOutIn(8, 1000, 0, 0x7f);
    if (prev == 0x4a) {
        if (GSflagTest(0x8ea)) {
            floorLink(0x8c, 0);
            floorSetFadeScript(0, 0);
        } else {
            GSfloorChange(0x39f);
            floorSetFadeScript(0, 0x5960008);
        }
    } else {
        GSfloorChange(0x384);
        floorSetFadeScript(0, 0x5960008);
    }
}
}

extern "C" {
void menuEndingDemoExit(void)
{
    fadeSet(3, 0.0f);
    fadeCheck(1);
    _menuSetScreenFilter(true);
}
}

extern "C" {
void menuStaffRollInit(void)
{
    fadeSet(2, 0.0f);
    fadeCheck(1);
}
}

extern "C" {
void menuStaffRollMain(void)
{
    s32 r;
    void* backup;
    if (floorGetPrevFloorID() != 0x384) {
        void* st = savedataGetStatus(0, 1);
        gamedatasaveSetStatus(st, 5, 0x8a);
        gamedatasaveSetStatus(st, 7, 0x8f);
        gamedatasaveSetStatus(st, 8, 2);
        backup = memcardMemAllocForSavedata();
        memcpy(backup, savedataGetStatus(0, 0), 0x27fd0);
    retry:
        winMsgOpen(2, 0x3c38, 1, 0);
        r = menuSubOpenYesNo(0, 0x3c, 0xaa, 0);
        if (r != 0) {
            winMsgOpen(2, 0x3c39, 1, 0);
            if (menuSubOpenYesNo(0, 0x3c, 0xaa, 1) == 0) {
                goto done;
            }
            goto retry;
        } else {
            if (memcardTaskCall(3, 2, 0) == 3 && gamedatasaveGetStatus(0, 4) != 0) {
                u32 ha = heroGetStatus(savedataGetStatus(backup, 2), 2, 0);
                u32 hb = heroGetStatus(0, 2, 0);
                if (ha == hb || gamedatasaveGetStatus(backup, 4) == 0) {
                    winMsgOpen(2, 0x3bf3, 1, 0);
                    r = menuSubOpenYesNo(0, 0x3c, 0xaa, 0);
                }
            }
            memcpy(savedataGetStatus(0, 0), backup, 0x27fd0);
            if (r != 0) {
                goto retry;
            }
            if (memcardTaskCall(0xe, 2, 0) != 4) {
                goto retry;
            }
        }
    done:
        winMsgClose(1);
        memcardMemFreeForSavedata(backup);
    }
    GSmoviePlay(0x7dd, 0, 0, 0);
    soundOpenPlay(8, 0, 0x7f);
    while (GSmovieGetStatus(0x7dd) < 0) {
        GSthreadSwitch();
    }
    lbl_804EA9F0 = 0.0;
    u8 flag = 0;
    while (GSmoviePlayCheck(0x7dd) == 1) {
        if (!pauseIsPause()) {
            lbl_804EA9F0 += pokecoloGetFrameTime();
        }
        if (lbl_804EA9F0 >= 193.12f) {
            if (flag == 1) {
                flag = 0;
                menuClose(0xe0);
            }
        } else if (lbl_804EA9F0 >= 186.16f) {
            if (flag == 0) {
                flag = 1;
                menuOpen(0xe0, 0);
            }
        }
        GSthreadSwitch();
    }
    soundOpenPlay(8, 0, 0x7f);
    floorGetPrevFloorID();
    GSfloorChange(0x384);
    floorSetFadeScript(0, 0x5960008);
}
}

extern "C" {
void menuStaffRollExit(void)
{
    fadeSet(3, 0.0f);
    fadeCheck(1);
}
}

extern "C" {
void fn_8008617C(void)
{
}
}

extern "C" {
void fn_800860E8(tagWINDOW_WORK* w)
{
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x1d4);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x1d8);
            w->seqSet = 1;
        }
        break;
    }
}
}

static u32 _menuOpeningDemo_SE(u32 i)
{
    return _PlaySE(_opening_se_sequence, 3, i);
}

extern "C" {
void menuOpeningDemoInit(void)
{
    fadeSet(2, 0.0f);
    fadeCheck(1);
    GSmoviePlay(0x7db, 0, 0, 0);
    soundOpenPlay(8, 0, 0x7f);
}
}

extern "C" {
void menuOpeningDemoMain(void)
{
    u32 se = 0;
    while (GSmoviePlayCheck(0x7db) == 1) {
        se = _menuOpeningDemo_SE(se);
        GSthreadSwitch();
    }
    soundOpenPlay(8, 0, 0x7f);
    floorLink(0x8d, 0);
    floorSetFadeScript(0, 0x5960008);
}
}

extern "C" {
void menuOpeningDemoExit(void)
{
    fadeSet(3, 0.0f);
    fadeCheck(1);
}
}

extern "C" {
void fn_80085E88(tagWINDOW_WORK* w, tagSPRITE_WORK* sp)
{
    u32 msg = 0;
    u32 col = w->alpha | 0xFFFFFF00;
    CURSOR cur = *(CURSOR*)&w->top;
    switch (sp->id) {
    case 0xA2:
        msg = 0x4a43;
        break;
    case 0xA3:
        msg = 0x4a44;
        break;
    case 0x9E:
        if (cur.pos == 0) {
            winSpriteSetDisp(sp, true);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x9F:
        if (cur.pos == 1) {
            winSpriteSetDisp(sp, true);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0xA4:
        msg = 0x4a45;
        break;
    case 0xA5:
        msg = 0x4a46;
        break;
    default:
        msg = 0;
        break;
    case 0xA0:
    case 0xA1:
        break;
    }
    if (msg != 0) {
        GSmsgPrintRect(winSpriteGetLayerID(w, sp), 0, -2, sp->w, sp->h, col, msg);
    }
}
}

extern "C" {
void fn_80085E3C(tagWINDOW_WORK* w)
{
    if (w != 0) {
        if (windowGetKeyInfo()->buttons & 0x10) {
            w->done = 1;
        }
    }
}
}
