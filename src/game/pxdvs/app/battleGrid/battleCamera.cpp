// Draft (dr4). Camera director for battle grid scenes (random camera + waza cameras).
#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
};

class NullSequence {
public:
    virtual ~NullSequence();
    virtual void Update(f32 dt);
    virtual void GetPosition(GSvec* pos);
    virtual void GetRotation(GSvec* rot);
    virtual void GetScale(GSvec* scale);
    virtual void SetPosition(GSvec* pos);
    virtual void SetRotation(GSvec* rot);
    virtual void SetScale(GSvec* scale);
    virtual void SetVisibility(bool visible);

    u16 m_unk4;
    bool m_visible;
    u8 m_unk7;
    s32 m_kind;
};

struct SequenceSection {
    u8 pad0[8];
    u32 flags;
    u8 padC[0x4c - 0xC];
    u32 parts[1];
};

class ModelSequence : public NullSequence {
public:
    u8 unkC[0x3c - 0xC];
    u32 targetId;
    u8 unk40[0x52 - 0x40];
    u8 section;
    u8 unk53;
    u8 flags54;
    u8 isEnemy;
    u8 hasParent;
    u8 unk57[0x94 - 0x57];
    void* model;
    u8 unk98[4];
    u8* sections;

    f32 GetModelScale(bool raw) const;
};

class WazaSequence {
public:
    u8 unk0[8];
    u32 flags;
    u8 unkC[2];
    u8 kind;
    u8 unkF[0x16 - 0xF];
    u8 partKind;
    u8 unk17[0x1c - 0x17];
    u32 resource;
    u8 unk20[4];
    NullSequence* target;
};

struct BattleGridEntry {
    ModelSequence* slot;
    ModelSequence* pokemon[2];
    u16 count;
    u8 arg1;
    u8 arg2;
};

struct BattleGrid {
    BattleGridEntry entries[4];
    u16 count;
    u16 pokemonCount;
};

struct wazaSequenceCameraParams {
    s32 motion;
    f32 size;
    f32 height;
    f32 rotationMin;
    f32 rotationMax;
    f32 rotationBase;
    f32 heightMin;
    f32 heightMax;
    f32 distanceMin;
    f32 distanceMax;
    f32 nearLength;
    f32 middleLength;
    f32 farLength;
};

struct FOVKey {
    f32 start;
    f32 end;
    f32 startTime;
    f32 endTime;
};

extern "C" {
extern BattleGrid gBattleGrid;
extern GSvec zeroVector;
extern GSvec unitScaleVector;
extern f32 __float_nan[];
extern FOVKey gFOVlist[2];
extern f32 gCurrentFOV;
extern f32 gCurrentFOVTime;

u32 HSD_Rand(void);
f32 HSD_Randf(void);
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* a_b);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
f32 GSlerpGetLinearInterpolationFloat(f32 a, f32 b, f32 t);
u8 GSgfxVideoGetVsyncRate(void);
f32 GSgfxVideoGetLastRenderTime(void);
void* GSresGetResource(u32 grp, u32 id);
u16 GSmodelCenterNull(void* model);
u8 GSmodelIsRootNullAdded(void* model);
void GSmodelGetRootPosition(void* model, GSvec* pos);
void* GSmodelGetBound(void* model);
void GSboundGetMinMax(void* bound, GSvec* min, GSvec* max, s32, s32, s32, s32);
void* GSmodelGetPart(void* model, s32 index);
void GSpartGetTransform(void* part, GSvec* pos, GSvec* rot, GSvec* scale);
void GSpartFree(void* part);

u8 fightFloor_GetTrainer(void* floor);
u8 fightPokemonGetNonTrainerPokemonIsActiveFlag(void);
u8 floorDataBiosGetFloorKind(void* floor);
u8 wazaSequenceSysIsValidSequence(NullSequence* seq);
u8 wazaSequenceSysIsValidWaza(WazaSequence* waza);
u16 battleGridGetNumPokemonsForTrainer(NullSequence* seq);
void battleGridResetModelVisibilityFlags(void);
f32 battleGridGetDistance(bool side);
f32 battleGridGetUnscaledDistance(bool side);
void battleGridGetNormalisedScale(GSvec* scale);

u8 cameraSetType(u8 type);
void cameraMoveStop(void);
u8 cameraMoveEndCheckSpecial(u8 wait);
void cameraStopAnime(void);
void cameraSetOffsetPosition(GSvec* pos);
void cameraSetOffsetRotation(GSvec* rot);
void cameraSetOffsetScale(GSvec* scale);
void cameraSetMirrorFlag(u8 flag);
void cameraSetPosition(GSvec* pos);
void cameraMovePosition(int mode, GSvec* pos, f32 time);
void cameraMoveRotationXYZ(int mode, f32 x, f32 y, f32 z, f32 time);
void cameraMoveFov(int mode, f32 fov, f32 time);
void cameraMoveTargetOfs(int mode, GSvec* ofs, f32 time);
void cameraSetFov(f32 fov);
void cameraSetTargetPos(GSvec* pos);
void cameraSetTargetOfs(GSvec* ofs);
void cameraSetTargetExt(u32 group, u32 id, s32 part);
void cameraRefreshTargetPos(void);
void cameraPlayOffsetAnime(u32 group, u32 id, s32 frame, u8 loop);
void cameraSetDistance(f32 distance);
void cameraSetHeight(f32 height);
void cameraSetRotY(f32 rotY);
void cameraUpdate(void);
void cameraGetPosition(GSvec* pos);
void cameraGetTargetPos(GSvec* pos);
void cameraMovePositionAcc(f32 rate);
void cameraMoveRotationAcc(f32 rate);
void cameraMoveFovAcc(f32 rate);
void fn_80196A14(u8 on);
}

void _wazaSequenceCameraCalculateParams(ModelSequence* modelSequence, int flags, wazaSequenceCameraParams* params);
void _wazaSequenceCameraSelectMotion(ModelSequence* modelSequence, WazaSequence* wazaSequence,
                                     wazaSequenceCameraParams* params);
void _wazaSequenceCameraDoPosition(ModelSequence* modelSequence, wazaSequenceCameraParams* params, f32 scale,
                                   bool reverse);
void _wazaSequenceCameraDoFOV(ModelSequence* modelSequence, wazaSequenceCameraParams* params, int flags, f32 scale);
void _wazaSequenceCameraGetFOVRange(wazaSequenceCameraParams* params, f32* lowFov, f32* highFov, f32 radius);

// From the Dolphin SDK's OSFastCast.h (GQR3 is set up for u16 conversion).
static inline u16 __OSf32tou16(register f32 inF) {
    u16 tmp;
    register u16* tmpPtr = &tmp;
    asm { psq_st inF, 0(tmpPtr), 1, 3 }
    return *tmpPtr;
}

static inline f32 Lerp(f32 a, f32 b, f32 t) {
    return a + (b - a) * t;
}

static inline f32 WazaSqrtf(f32 x) {
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (f32)(x * guess);
    } else if (x < 0.0) {
        return *__float_nan;
    } else {
        union {
            f32 f;
            s32 i;
        } u;
        s32 cls;
        u.f = x;
        switch (u.i & 0x7F800000) {
        case 0x7F800000:
            if (u.i & 0x007FFFFF) {
                cls = 1;
            } else {
                cls = 2;
            }
            break;
        case 0:
            if (u.i & 0x007FFFFF) {
                cls = 5;
            } else {
                cls = 3;
            }
            break;
        default:
            cls = 4;
            break;
        }
        if (cls == 1) {
            return *__float_nan;
        }
    }
    return x;
}

static inline ModelSequence* AsModel(NullSequence* seq) {
    ModelSequence* r;
    if (seq->m_kind == 1) {
        r = (ModelSequence*)seq;
    } else {
        r = 0;
    }
    return r;
}

static inline u32 GetTargetPart(ModelSequence* ms, WazaSequence* active) {
    u32 part;
    if (ms->model == 0) {
        part = 0;
    } else if (active != 0) {
        SequenceSection* sec = (SequenceSection*)(ms->sections + ms->section * 0xd0);
        if ((sec->flags & 0x20) || active->partKind == 0x10) {
            part = (u16)GSmodelCenterNull(ms->model);
        } else {
            part = sec->parts[active->partKind];
        }
    } else {
        part = GSmodelCenterNull(ms->model);
    }
    return part;
}

WazaSequence* gActiveWazaSequenceCamera;
static u8 gBattleGridSimpleCamera;
static u8 g_mode;
static u8 g_enable_battle_camera;

static f32 gLoopCameraWaitTime = 3.0f;
static s32 gLastSelectedIndex = -1;

static void _battleCameraStartRandom(ModelSequence* seq);
static void _battleCameraUpdateWaza(void);

static inline void ClearCameraState(void) {
    battleGridResetModelVisibilityFlags();
    cameraMoveStop();
    cameraSetOffsetPosition(&zeroVector);
    cameraSetOffsetRotation(&zeroVector);
    cameraSetOffsetScale(&unitScaleVector);
    cameraSetMirrorFlag(0);
}

static inline void StopWazaCamera(void) {
    if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera)) {
        if (gActiveWazaSequenceCamera->resource != 0) {
            cameraStopAnime();
        }
    }
    gActiveWazaSequenceCamera = 0;
}

extern "C" {

void battleCameraDisable(void) {
    g_enable_battle_camera = 0;
}

u8 battleCameraIsSimple(void) {
    return gBattleGridSimpleCamera;
}

void battleCameraDoFull(void) {
    gBattleGridSimpleCamera = 0;
}

void battleCameraDoSimple(void) {
    gBattleGridSimpleCamera = 1;
}

void battleCameraInit(void* floor) {
    g_mode = 0;
    gActiveWazaSequenceCamera = 0;
    gLastSelectedIndex = -1;
    gLoopCameraWaitTime = 3.0f;
    gBattleGridSimpleCamera = 0;
    g_enable_battle_camera = floor != 0 && floorDataBiosGetFloorKind(floor) == 2;
}

void battleCameraStartRandom(u8 simple);

void battleCameraUpdate(void) {
    switch (g_mode) {
    case 2:
        _battleCameraUpdateWaza();
        break;
    case 1:
        if (!cameraMoveEndCheckSpecial(0)) {
            ClearCameraState();
            switch (g_mode) {
            case 2:
                StopWazaCamera();
                g_mode = 0;
                break;
            case 1:
                g_mode = 3;
                break;
            case 3:
                g_mode = 0;
                break;
            }
        }
        break;
    case 3:
        battleCameraStartRandom(gBattleGridSimpleCamera);
        break;
    }
}

void battleCameraStop(void) {
    ClearCameraState();
    switch (g_mode) {
    case 2:
        StopWazaCamera();
        g_mode = 0;
        break;
    case 1:
        g_mode = 3;
        break;
    case 3:
        g_mode = 0;
        break;
    }
}

void battleCameraStartRandom(u8 simple) {
    int count = gBattleGrid.pokemonCount;
    int i;
    int j;
    int idx;
    int n;
    BattleGridEntry* grp;

    if (g_enable_battle_camera && g_mode != 1) {
        if (count == 0) {
            _battleCameraStartRandom(0);
        } else {
            if (count == 1) {
                idx = 0;
            } else {
                idx = (u16)HSD_Rand() % count;
                while (idx == gLastSelectedIndex) {
                    idx = (u16)HSD_Rand() % count;
                }
            }
            gLastSelectedIndex = idx;
            n = 0;
            grp = gBattleGrid.entries;
            for (i = 0; i < 4; i++, grp++) {
                if (grp->slot != 0) {
                    for (j = 0; j < 2; j++) {
                        if (grp->pokemon[j] != 0) {
                            if (n == idx) {
                                _battleCameraStartRandom(grp->pokemon[j]);
                                gLoopCameraWaitTime = 3.0f;
                                return;
                            }
                            n++;
                        }
                    }
                }
            }
        }
    }
}

}  // extern "C"

static inline void DoPreset(GSvec* t, GSvec* a, GSvec* b, f32 time, f32 fov) {
    f32 s = battleGridGetUnscaledDistance(true);
    s = battleGridGetDistance(true) / s;
    PSVECScale(a, a, s);
    PSVECScale(b, b, s);
    if (HSD_Randf() < 0.5f) {
        cameraSetType(2);
        cameraSetPosition(a);
        cameraMovePosition(2, b, time);
        cameraSetFov(fov);
        cameraSetTargetPos(t);
        cameraSetTargetOfs(&zeroVector);
    } else {
        cameraSetType(2);
        cameraSetPosition(b);
        cameraMovePosition(2, a, time);
        cameraSetFov(fov);
        cameraSetTargetPos(t);
        cameraSetTargetOfs(&zeroVector);
    }
}

static inline void DoTracked(GSvec* t, GSvec* a, GSvec* b, f32 fov) {
    f32 r = HSD_Randf();
    cameraSetType(2);
    cameraSetPosition(a);
    cameraMovePosition(2, b, 3.0f + r);
    cameraSetFov(fov);
    cameraSetTargetPos(t);
    cameraSetTargetOfs(&zeroVector);
}

static void _battleCameraStartRandom(ModelSequence* seq) {
    wazaSequenceCameraParams params;
    GSvec cur;
    GSvec a;
    GSvec b;
    GSvec t;
    u8 pattern;
    u8 nonTrainerActive;
    bool again;
    bool isTrainer;
    int flags;
    f32 dir;
    f32 d1;
    f32 d0;
    f32 dur;
    f32 rot2;
    f32 fov2;
    f32 rot1;
    f32 dist2;
    f32 fov1;
    f32 height;
    f32 dist1;
    f32 r;
    f32 lowA, highA, lowB, highB;
    static u8 old_pos_pattern[2] = {12, 12};

    isTrainer = fightFloor_GetTrainer(0) != 0;
    nonTrainerActive = fightPokemonGetNonTrainerPokemonIsActiveFlag();
    flags = 0;
    if (!g_enable_battle_camera) {
        return;
    }
    if (!wazaSequenceSysIsValidSequence(seq) || seq->m_visible == 0) {
        seq = 0;
    }
    ClearCameraState();
    switch (g_mode) {
    case 2:
        StopWazaCamera();
        break;
    case 1:
    case 3:
        break;
    }
    g_mode = 1;
    again = true;
    while (again) {
        bool noParent = (seq == 0 || seq->hasParent == 0);
        pattern = (u16)HSD_Rand() % (noParent ? 10 : 12);
        if (pattern != old_pos_pattern[0] && pattern != old_pos_pattern[1]) {
            again = false;
        }
        if (!isTrainer && pattern == 3) {
            again = true;
        }
    }
    old_pos_pattern[1] = old_pos_pattern[0];
    old_pos_pattern[0] = pattern;
    if (seq != 0 && seq->hasParent == 0) {
        switch (battleGridGetNumPokemonsForTrainer(seq)) {
        case 1:
            flags = 7;
            break;
        case 2:
            flags = 1;
            break;
        }
    }
    if (seq != 0) {
        _wazaSequenceCameraCalculateParams(seq, flags, &params);
    }
    switch (pattern) {
    case 0:
        t.z = t.y = t.x = 0.0f;
        a.x = -20.0f; a.y = 27.5f; a.z = 110.0f;
        b.x = 20.0f; b.y = 27.5f; b.z = 110.0f;
        DoPreset(&t, &a, &b, 4.0f, 60.0f);
        return;
    case 1:
        t.z = t.y = t.x = 0.0f;
        a.x = 110.0f; a.y = 27.5f; a.z = 0.0f;
        b.x = 110.0f; b.y = 27.5f; b.z = 20.0f;
        DoPreset(&t, &a, &b, 2.5f, 60.0f);
        return;
    case 2:
        t.z = t.y = t.x = 0.0f;
        a.x = -110.0f; a.y = 27.5f; a.z = 20.0f;
        b.x = -110.0f; b.y = 27.5f; b.z = 0.0f;
        DoPreset(&t, &a, &b, 2.5f, 60.0f);
        return;
    case 3:
        t.z = t.y = t.x = 0.0f;
        a.x = -65.0f; a.y = 27.5f; a.z = 100.0f;
        b.x = -100.0f; b.y = 27.5f; b.z = 65.0f;
        DoPreset(&t, &a, &b, 4.0f, 60.0f);
        return;
    case 4:
        t.z = t.y = t.x = 0.0f;
        a.x = 100.0f; a.y = 27.5f; a.z = 65.0f;
        b.x = 65.0f; b.y = 27.5f; b.z = 100.0f;
        DoPreset(&t, &a, &b, 4.0f, 60.0f);
        return;
    case 5:
        if ((isTrainer || nonTrainerActive) && HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        t.x = -d1 * dir; t.y = 5.0f; t.z = 0.0f;
        a.x = d1 * dir; a.y = 5.0f; a.z = d1;
        b.x = 0.2f * d1 * dir; b.y = 5.0f; b.z = d1;
        DoTracked(&t, &a, &b, 40.0f);
        return;
    case 6:
        if (HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        d0 = battleGridGetDistance(false);
        t.x = -d0 * dir; t.y = 0.0f; t.z = 0.0f;
        a.x = dir * (d1 + d0); a.y = 5.0f; a.z = 0.7f * d1;
        b.x = a.x; b.y = 5.0f; b.z = 0.7f * -d1;
        DoTracked(&t, &a, &b, 30.0f);
        return;
    case 7:
        if ((isTrainer || nonTrainerActive) && HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        d0 = battleGridGetDistance(false);
        t.x = -d0 * dir; t.y = 5.0f; t.z = 0.0f;
        a.x = 0.0f; a.y = 5.0f; a.z = 0.7f * d1;
        b.x = 0.0f; b.y = 5.0f; b.z = 0.7f * -d1;
        DoTracked(&t, &a, &b, 60.0f);
        return;
    case 8: {
        f32 hiA = 2.0f * HSD_Randf() + 5.0f;
        f32 hiB = 2.0f * HSD_Randf() + 5.0f;
        r = HSD_Randf();
        if (r < 0.5f) {
            hiA *= -1.0f;
        }
        if (!(r < 0.5f)) {
            hiB *= -1.0f;
        }
        if (HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        d0 = battleGridGetDistance(false);
        t.x = -d1 * dir; t.y = 0.0f; t.z = 0.0f;
        a.x = dir * (d1 + d0); a.y = 5.0f; a.z = hiA;
        b.x = a.x; b.y = 20.0f; b.z = hiB;
        DoTracked(&t, &a, &b, 20.0f);
        return;
    }
    case 9:
        if (HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        d0 = battleGridGetDistance(false);
        t.x = -d0 * dir; t.y = 5.0f; t.z = 0.0f;
        a.x = dir * (d1 + d0); a.y = 2.0f; a.z = 0.25f * d1;
        b.x = a.x; b.y = 2.0f; b.z = 0.25f * -d1;
        DoTracked(&t, &a, &b, 15.0f);
        return;
    case 10:
        dist1 = Lerp(params.distanceMin, params.distanceMax, HSD_Randf());
        dist2 = Lerp(params.distanceMin, params.distanceMax, HSD_Randf());
        if (dist1 < dist2) {
            f32 tmp = dist2;
            dist2 = dist1;
            dist1 = tmp;
        }
        height = Lerp(params.heightMin, params.heightMax, HSD_Randf());
        if (seq->isEnemy != 0) {
            rot1 = HSD_Randf();
            rot1 *= params.rotationBase - (params.rotationMax - params.rotationMin);
        } else {
            rot1 = (params.rotationMax - params.rotationMin) * HSD_Randf() + (params.rotationBase + params.rotationMin);
        }
        rot2 = rot1;
        break;
    case 11:
        dist1 = Lerp(params.distanceMin, params.distanceMax, HSD_Randf());
        dist2 = dist1;
        height = Lerp(params.heightMin, params.heightMax, HSD_Randf());
        if (seq->isEnemy != 0) {
            rot1 = HSD_Randf();
            rot1 *= params.rotationBase - (params.rotationMax - params.rotationMin);
            rot2 = HSD_Randf();
            rot2 *= params.rotationBase - (params.rotationMax - params.rotationMin);
        } else {
            rot2 = (params.rotationMax - params.rotationMin) * HSD_Randf() + (params.rotationBase + params.rotationMin);
            rot1 = (params.rotationMax - params.rotationMin) * HSD_Randf() + (params.rotationBase + params.rotationMin);
        }
        break;
    default:
        dist1 = Lerp(params.distanceMin, params.distanceMax, HSD_Randf());
        dist2 = dist1;
        height = Lerp(params.heightMin, params.heightMax, HSD_Randf());
        if (seq->isEnemy != 0) {
            rot1 = HSD_Randf();
            rot1 *= params.rotationBase - (params.rotationMax - params.rotationMin);
        } else {
            rot1 = (params.rotationMax - params.rotationMin) * HSD_Randf() + (params.rotationBase + params.rotationMin);
        }
        rot2 = rot1;
        break;
    }

    {
        f32 hsq = height;
        hsq *= height;
        _wazaSequenceCameraGetFOVRange(&params, &lowA, &highA, WazaSqrtf(dist1 * dist1 + hsq));
        _wazaSequenceCameraGetFOVRange(&params, &lowB, &highB, WazaSqrtf(dist2 * dist2 + hsq));
    }
    switch ((u8)((u16)HSD_Rand() % 3)) {
    case 1:
        fov2 = Lerp(lowA, highA, HSD_Randf());
        fov1 = Lerp(lowB, highB, HSD_Randf());
        if (fov2 < fov1) {
            f32 tmp = fov1;
            fov1 = fov2;
            fov2 = tmp;
        }
        break;
    case 2:
        fov2 = Lerp(lowA, highA, HSD_Randf());
        fov1 = Lerp(lowB, highB, HSD_Randf());
        if (fov2 > fov1) {
            f32 tmp = fov1;
            fov1 = fov2;
            if (fov2 < tmp) fov2 = tmp;
        }
        break;
    case 0:    default:
        fov1 = Lerp(lowA, highA, HSD_Randf());
        fov2 = fov1;
        break;
    }
    dur = HSD_Randf();
    dur += 3.0f;
    cameraMoveStop();
    cameraSetType(7);
    fn_80196A14(1);
    {
        void* model = seq->model;
        u32 id = seq->targetId;
        u32 part;
        if (model != 0) {
            part = GSmodelCenterNull(model);
        } else {
            part = 0;
        }
        cameraSetTargetExt(20000, id, part);
    }
    cameraRefreshTargetPos();
    cameraSetTargetExt(0, 0, -1);
    cameraSetDistance(dist1);
    cameraSetHeight(height);
    cameraSetRotY(rot2);
    cameraSetFov(fov2);
    cameraUpdate();
    cameraGetPosition(&cur);
    cameraGetTargetPos(&t);
    PSVECSubtract(&cur, &t, &cur);
    PSVECScale(&cur, &cur, dist2 / dist1);
    cur.y = height;
    PSVECAdd(&cur, &t, &cur);
    cameraMovePosition(7, &cur, dur);
    cameraMoveRotationXYZ(7, 0.0f, rot1, 0.0f, dur);
    cameraMoveFov(7, fov1, dur);
    cameraMovePositionAcc(dur * (0.25f / (f32)GSgfxVideoGetVsyncRate()));
    cameraMoveRotationAcc(dur * (0.25f / (f32)GSgfxVideoGetVsyncRate()));
    cameraMoveFovAcc(dur * (0.25f / (f32)GSgfxVideoGetVsyncRate()));
}

extern "C" {

void battleCameraStartWaza(WazaSequence* waza) {
    wazaSequenceCameraParams params;
    GSvec rootPos;
    GSvec pos;
    GSvec rot;
    GSvec scale;
    GSvec boundMid;
    GSvec boundMin;
    GSvec boundMax;
    GSvec tmpPos;
    GSvec tmpPos2;
    GSvec boundSum;
    ModelSequence* ms;
    void* model;
    bool reverse;
    int flags;
    f32 scaleTime;
    u32 f;

    scaleTime = 1.0f;
    reverse = false;
    flags = 0;
    ClearCameraState();
    switch (g_mode) {
    case 2:
        StopWazaCamera();
        g_mode = 0;
        break;
    case 1:
        g_mode = 3;
        break;
    case 3:
        g_mode = 0;
        break;
    }
    if (wazaSequenceSysIsValidWaza(waza)) {
        ms = AsModel(waza->target);
        if (ms != 0) {
            model = ms->model;
            if (model != 0) {
                if (GSmodelIsRootNullAdded(model)) {
                    GSmodelGetRootPosition(model, &rootPos);
                } else {
                    rootPos.x = 0.0f;
                    rootPos.y = 0.0f;
                    rootPos.z = 0.0f;
                }
                gActiveWazaSequenceCamera = waza;
                g_mode = 2;
                if (ms->isEnemy != 0 && !(waza->flags & 0x80)) {
                    reverse = true;
                }
                if (waza->resource != 0 && GSresGetResource(20000, waza->resource) != 0) {
                    u8 flags = 0;
                    if (reverse) {
                        flags = 4;
                    }
                    cameraPlayOffsetAnime(20000, waza->resource, 0, 0);
                    f = waza->flags;
                    if (f & 4) {
                        pos.z = pos.y = pos.x = 0.0f;
                        rot.z = rot.y = rot.x = 0.0f;
                        if (ms->isEnemy != 0 && (f & 0x02000000)) {
                            rot.y = 3.1415927f;
                        }
                        if (waza->flags & 0x00800000) {
                            battleGridGetNormalisedScale(&scale);
                            if (waza->flags & 0x01000000) {
                                scale.y = 1.0f;
                            }
                        } else {
                            scale.z = scale.y = scale.x = 1.0f;
                        }
                    } else {
                        ms->GetPosition(&pos);
                        ms->GetRotation(&rot);
                        if (waza->flags & 0x20000000) {
                            scale.x = scale.y = scale.z = 1.0f;
                        } else {
                            f32 s = ms->GetModelScale(true);
                            scale.z = s;
                            scale.y = s;
                            scale.x = s;
                        }
                        if (waza->flags & 0x4000) {
                            GSboundGetMinMax(GSmodelGetBound(model), &boundMin, &boundMax, 1, 1, 0, 0);
                            PSVECAdd(&boundMin, &boundMax, &boundSum);
                            boundMid = boundSum;
                            PSVECScale(&boundMid, &boundMid, 0.5f);
                            PSVECAdd(&pos, &boundMid, &pos);
                        }
                        if (waza->kind == 2 && (ms->flags54 & 1) == 1) {
                            pos.y = pos.y + rootPos.y;
                        }
                    }
                    cameraSetMirrorFlag(flags);
                    cameraMoveStop();
                    cameraSetOffsetPosition(&pos);
                    cameraSetOffsetRotation(&rot);
                    cameraSetOffsetScale(&scale);
                    cameraUpdate();
                } else {
                    if (ms->hasParent != 0) {
                        f = waza->flags;
                        if (f & 0x200000) {
                            flags = 3;
                        } else if (f & 0x200) {
                            flags = 4;
                        } else if (f & 0x400000) {
                            ms->GetPosition(&tmpPos);
                            if (tmpPos.z < 0.0f) {
                                flags = 4;
                            } else {
                                flags = 5;
                            }
                        }
                    } else {
                        switch (battleGridGetNumPokemonsForTrainer(ms)) {
                        case 1:
                            if (waza->flags & 0x400000) {
                                flags = 7;
                            } else {
                                flags = 6;
                            }
                            break;
                        case 2:
                            if (waza->flags & 0x200000) {
                                flags = 1;
                            } else {
                                flags = 2;
                            }
                        default:
                            f = waza->flags;
                            if (f & 0x200000) {
                                flags = 3;
                            } else if (f & 0x200) {
                                flags = 4;
                            } else if (f & 0x400000) {
                                ms->GetPosition(&tmpPos2);
                                if (tmpPos2.z < 0.0f) {
                                    flags = 4;
                                } else {
                                    flags = 5;
                                }
                            }
                            break;
                        }
                        scaleTime = 2.0f;
                    }
                    f = waza->flags;
                    if (f & 0x400) {
                        flags |= 0x80;
                    } else if (f & 0x800) {
                        flags |= 0x100;
                    } else if (f & 0x1000) {
                        flags |= 0x200;
                    }
                    cameraMoveStop();
                    cameraSetType(7);
                    {
                        u32 id = ms->targetId;
                        cameraSetTargetExt(20000, id, GetTargetPart(ms, gActiveWazaSequenceCamera));
                    }
                    cameraRefreshTargetPos();
                    cameraSetTargetExt(0, 0, -1);
                    _wazaSequenceCameraCalculateParams(ms, flags, &params);
                    _wazaSequenceCameraSelectMotion(ms, waza, &params);
                    _wazaSequenceCameraDoPosition(ms, &params, scaleTime, reverse);
                    _wazaSequenceCameraDoFOV(ms, &params, flags, scaleTime);
                    cameraUpdate();
                }
            }
        }
    }
}

}  // extern "C"

static void _battleCameraUpdateWaza(void) {
    ModelSequence* ms;
    FOVKey* key = gFOVlist;
    f32 t;
    int i;

    if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) && gActiveWazaSequenceCamera->resource == 0) {
        ms = AsModel(gActiveWazaSequenceCamera->target);
        {
            f32 frames = 0.5f + GSgfxVideoGetLastRenderTime();
            u16 frameCount = __OSf32tou16(frames);
            u32 part = GetTargetPart(ms, gActiveWazaSequenceCamera);
            if (!(gActiveWazaSequenceCamera->flags & 0x40000000)) {
                void* partObj = GSmodelGetPart(ms->model, part);
                if (partObj != 0) {
                    GSvec ofs;
                    GSvec cur;
                    GSpartGetTransform(partObj, &ofs, 0, 0);
                    ms->NullSequence::GetPosition(&cur);
                    PSVECSubtract(&ofs, &cur, &ofs);
                    cameraMoveTargetOfs(7, &ofs, 0.25f);
                    GSpartFree(partObj);
                }
            }
            t = gCurrentFOVTime + (f32)frameCount / (f32)GSgfxVideoGetVsyncRate();
            gCurrentFOVTime = t;
        }
        for (i = 0; i < 2; i++, key++) {
            if (t <= key->startTime) {
                gCurrentFOV = key->start;
                break;
            }
            if (t <= key->endTime) {
                gCurrentFOV = GSlerpGetLinearInterpolationFloat(key->start, key->end,
                                                                (t - key->startTime) / (key->endTime - key->startTime));
                break;
            }
            gCurrentFOV = key->end;
        }
        cameraSetFov(gCurrentFOV);
    }
}
