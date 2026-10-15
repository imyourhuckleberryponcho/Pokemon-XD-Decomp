// STATUS (rough draft, rd_mm): 41/41 functions, 16 exact, byte-weighted ~84% with extra_cflags ["-inline noauto"]
// (+ pool_strings off in-file). Remaining: _menuModelMakeLoadInfo is 4-param here (callee reads r6) but the target symbol
// is ...PokemonUs (3 params) -> pair it by renaming the symbols.txt entry to ...UsUc/Usb; function-local statics (upVec/target
// guards in AdjustCamera/AdjustCamera2), light colour constants (.sdata2 0xFFFFFFFF/0x808080FF locals) and the weak
// __sinit position still differ. Weakest: SetupViewport 72%/75%, menuModelInit 76%, AdjustCamera 87%, LoadThread 87%.
#include <dolphin/types.h>
#pragma pool_strings off

#include <game/pxdvs/app/pokemon/pokemon.hpp>
struct GSbound;

struct GSvec {
    f32 x, y, z;
    GSvec() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
};

// one queued load request (kind 1 = Pokemon sequence, 0 = floor object)
struct MENU_MODEL_LOAD {
    u8 kind;     // 0x00
    u8 pad1[3];
    union {
        u32 id;
        struct {
            u16 form;
            u16 waza;
        } pk;
    };           // 0x04 (objects: u32 id)
    s32 rnd;     // 0x08
    u16 c;       // 0x0C
    u8 shadow;   // 0x0E
    u8 anim;     // 0x0F
};

struct MENU_MODEL {
    u8 state;       // 0x00
    u8 loading;     // 0x01
    u8 inited;      // 0x02
    u8 visible;     // 0x03
    s8 clip;        // 0x04
    u8 pad5[7];
    f32 progress;   // 0x0C
    MENU_MODEL_LOAD pending; // 0x10
    MENU_MODEL_LOAD cur;     // 0x20
    u32 model;      // 0x30
    u32 wazaSeq;    // 0x34
    u32 nextModel;  // 0x38
    u32 nextWaza;   // 0x3C
    f32 angle[3];   // 0x40
    f32 offset[3];  // 0x4C
    u32 thread;     // 0x58
    s32 x;          // 0x5C
    s32 y;          // 0x60
    s32 w;          // 0x64
    s32 h;          // 0x68
    u32 camera;     // 0x6C
    u32 light[3];   // 0x70
    f32 zoom;       // 0x7C
    s32 waitCount;  // 0x80
    u8 f84;         // 0x84
    u8 pad85[3];
    f32 camRot[3];  // 0x88
    u8 mtx[0x30];   // 0x94
    u8 sizeValid;   // 0xC4
    u8 pad[3];
    f32 size[3];    // 0xC8
    f32 min[3];     // 0xD4
    f32 max[3];     // 0xE0
};

struct PokemonMenuAnim {
    u16 id;
    u16 index;
};

extern "C" {
void C_MTXLookAt(void* m, f32* pos, void* target, void* up);
void GSboundGetMinMax(u32 bound, void* min, void* max, s32, s32, s32, s32);
void GSboundGetSize(void* out, s32, s32);
u32 GScameraCreate();
void GScameraFree(u32 c);
void GScameraGetPerspective(u32 c, f32* fov, f32* aspect, f32* n, f32* f);
void GScameraLookAt(u32 c, void* target, void* up);
void GScameraSetPerspective(u32 c, f32 fov, f32 aspect, f32 n, f32 f);
void GScameraSetPosition(u32 c, f32* pos);
void GScameraSetRotation(u32 c, f32* rot);
void GScameraSetScissor(s32 on, s32 x, s32 y, s32 w, s32 h);
void GScameraSetViewport(u32 c, s32 on, f32 x0, f32 y0, f32 x1, f32 y1);
s32 GSfloorGetCurrentFloorGroupID();
u8 GSlightCreate();
void GSlightFree(u8 l);
void GSlightSetActive(u8 l, s32 on);
void GSlightSetColor(u8 l, void* col);
void GSlightSetPosition(u8 l, void* pos);
void GSlightSetTarget(u8 l, void* pos);
void GSlightSetType(u8 l, s32 type);
void GSlogWrite(const char* fmt, ...);
u8 GSmodelCanAnimate(u32 m);
u16 GSmodelCenterNull(u32 m);
void GSmodelFree(u32 m);
u32 GSmodelGetBound(u32 m);
u32 GSmodelGetPart(u32 m, u16 i);
void GSmodelGetPosition(u32 m, void* pos);
void GSmodelSetAnimIndex(u32 m, s32 i);
void GSmodelSetAnimRate(u32 m, f32 r);
void GSmodelSetAnimType(u32 m, s32 t);
void GSmodelSetBoundCheck(u32 m, s32 on);
void GSmodelSetPosition(u32 m, void* pos);
void GSmodelSetRenderCamera(u32 m, u32 cam);
void GSmodelSetRenderLayer(u32 m, s32 n, void* layers);
void GSmodelSetVisibility(u32 m, s32 v);
void GSmodelStartAnimation(u32 m);
void GSpartFree(u32 p);
void GSpartGetTransform(void* out, s32, s32);
void GSthreadClose(u32 t);
u32 GSthreadCreate(s32, s32, s32, s32, s32, s32 (*fn)(void*));
u32 GSthreadGetCurrentThread();
u8 GSthreadIsRunning(u32 t);
void GSthreadSetArgs(s32 n, void* a);
void GSthreadSwitch();
void PSMTXConcat(void* a, void* b, void* c);
void PSMTXInverse(void* a, void* b);
void PSMTXMultVec(void* m, f32* a, f32* b);
void PSMTXRotRad(void* m, s32 axis, f32 rad);
void PSVECAdd(f32* a, f32* b, f32* c);
f32 PSVECDistance(f32* a, f32* b);
void PSVECSubtract(f32* a, f32* b, f32* c);
void Sequence_DoAnimation(u32 s, u8 anim);
void Sequence_Free(u32 s);
u32 Sequence_GetGSmodel(u32 s);
s32 Sequence_GetModelSize(u32 s);
u32 Sequence_LoadPokemon(u16 form, s32 rnd, u8 shadow);
u32 Sequence_LoadWaza(u32 seq, s32 a, s32 b);
void Sequence_SetCamera(u32 s, u32 cam);
void Sequence_SetVisibility(u32 s, s32 v);
void WazaSequence_Free(u32 w);
u8 WazaSequence_IsActive(u32 w);
void WazaSequence_Start(u32 w, s32 a);
void WazaSequence_Stop(u32 w);
u32 floorOpenObject(s32 id);
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
void memoGetScaleAngle(u16 id, f32* scale, void* angle);
u8 menuFaceCheckLoading();
u8 pokemonGetAnnonKatati(s32 rnd);
u8 pokemonIsJoutaiDataId(Pokemon* p, u16 id);
f64 tan(f64);
u8 wazaSequenceSysIsValidWaza();
void wazaSequenceSysSetVisibilityAll(s32 v);
extern PokemonMenuAnim* pokemon_menu_animation;
extern u32* pokemon_menu_animation_number;
extern u8 _modeloff;
}

static s32 _menuModelRef;
static u8 _checkLarge;

static GSvec _testpos;
static GSvec _testPos;
static GSvec _testPos2D;
static GSvec _lightOffset;

static s32 _layerID = 2;
static f32 _menuModelScaleMultiValue = 1.0f;
static f32 _camFov = 35.0f;
static u32 _lightColor = 0x808080FF;
static s32 _waitframe = 3;
static f32 _disp_scale = 0.7f;
static u8 _litonoff[3] = { 1, 1, 1 };

static s32 _menuModelAdjustCamera2(MENU_MODEL* a, MENU_MODEL* b);
static s32 _menuModelAdjustCamera(MENU_MODEL* m, bool first);
static u8 _menuModelCmpLoadInfo(MENU_MODEL_LOAD* a, MENU_MODEL_LOAD* b);
static s32 _menuModelLoadThread(MENU_MODEL* m);
static void _menuModelMakeLoadInfo(MENU_MODEL_LOAD* out, Pokemon* p, u16 waza, bool shadow);
static void _menuModelSetupViewport2(MENU_MODEL* a, MENU_MODEL* b);
static void _menuModelSetupViewport(MENU_MODEL* m);
static s32 _menuModelTerm(MENU_MODEL* m);
static void _menuModelRenderOff(MENU_MODEL* m);
extern "C" u8 menuModelCompareObject(MENU_MODEL* m, s32 id);
extern "C" u8 menuModelComparePokemon(MENU_MODEL* m, Pokemon* p);
extern "C" s32 menuModelFree(MENU_MODEL* m);
extern "C" s32 menuModelFreeNext(MENU_MODEL* m);
extern "C" void menuModelWazaFree(MENU_MODEL* m);
extern "C" u8 menuModelGetPokemonAnimationIndexByPointer(Pokemon* p);
extern "C" u8 menuModelGetPokemonAnimationIndexByID(u16 id);

void menuModelGetPkxRndFromPokemonForSeqenceLoad(u32& rnd, u16& species, Pokemon* p) {
    species = pokemonGetStatus(0, pokemonGetStatus(p, 0, 0x6E, 0), 0x66, 0);
    rnd = p->getRnd();
    switch (species) {
    case 0xC9:
        rnd = pokemonGetAnnonKatati(rnd);
        return;
    case 0x19A:
        rnd = 0;
        return;
    case 0xF9:
        if (p->isDarkPokemon() != 0) species = 0x1A1;
        rnd = 0;
        return;
    }
}

extern "C" {

void menuModelReSetScale(void) {
    _menuModelScaleMultiValue = 1.0f;
}

void menuModelSetScale(f32 s) {
    _menuModelScaleMultiValue = s;
}

f32 menuModelGetScale(f32 s) {
    return s * _menuModelScaleMultiValue;
}

u8 menuModelGetPokemonAnimationIndexByID(u16 id) {
    PokemonMenuAnim* a = pokemon_menu_animation;
    for (u32 n = *pokemon_menu_animation_number; n > 0; n--, a++) {
        if (a->index == id) return a->id - 1;
    }
    return 0;
}

u8 menuModelGetPokemonAnimationIndexByPointer(Pokemon* p) {
    return menuModelGetPokemonAnimationIndexByID(p->getPokemonDataId());
}

void menuModelSetCameraRotation(MENU_MODEL* m, GSvec* v) {
    m->camRot[0] = v->x;
    m->camRot[1] = v->y;
    m->camRot[2] = v->z;
}

f32* menuModelGetCameraRotation(MENU_MODEL* m) {
    return m->camRot;
}

u32 menuModelGetModelPtr(MENU_MODEL* m) {
    if (m->cur.kind != 0) return Sequence_GetGSmodel(m->model);
    return m->model;
}

void menuModelSetClip(MENU_MODEL* m, s8 c) {
    m->clip = c;
}

void menuModelSetZoom(MENU_MODEL* m, f32 z) {
    m->zoom = z;
}

void menuModelSetOffset(MENU_MODEL* m, GSvec* v) {
    m->offset[0] = v->x;
    m->offset[1] = v->y;
    m->offset[2] = v->z;
}

void menuModelSetAngle(MENU_MODEL* m, GSvec* v) {
    m->angle[0] = v->x;
    m->angle[1] = v->y;
    m->angle[2] = v->z;
}

void menuModelAdjustCamera2(MENU_MODEL* a, MENU_MODEL* b) {
    _menuModelAdjustCamera2(a, b);
}

void menuModelAdjustCamera(MENU_MODEL* m) {
    _menuModelAdjustCamera(m, true);
}

s32 menuModelSetMotion(MENU_MODEL* m, s32 anim) {
    if (m == 0) return 0;
    if (m->loading != 0) {
        if (m->pending.kind == 0) m->pending.rnd = anim;
    } else if (m->cur.kind == 0) {
        m->cur.rnd = anim;
        if (GSmodelCanAnimate(m->model) != 0) {
            GSmodelSetAnimIndex(m->model, m->cur.rnd);
            GSmodelSetAnimRate(m->model, 0.5f);
            GSmodelStartAnimation(m->model);
        }
    }
    return 1;
}

s32 menuModelRender2(MENU_MODEL* a, MENU_MODEL* b) {
    if (a == 0) return 0;
    if (b == 0) return 0;
    if (a->state != 2) return 0;
    if (b->state != 2) return 0;
    u32 ma, mb;
    if (a->cur.kind != 0) ma = Sequence_GetGSmodel(a->model);
    else ma = a->model;
    if (b->cur.kind != 0) mb = Sequence_GetGSmodel(b->model);
    else mb = b->model;
    if (ma == 0) return 0;
    if (mb == 0) return 0;
    if (a->cur.kind != 0) Sequence_SetCamera(a->model, a->camera);
    else GSmodelSetRenderCamera(a->model, a->camera);
    if (b->cur.kind != 0) Sequence_SetCamera(b->model, a->camera);
    else GSmodelSetRenderCamera(b->model, a->camera);
    _menuModelSetupViewport2(a, b);
    u32* l = a->light;
    u8* on = _litonoff;
    for (s32 i = 0; i < 3; i++, l++, on++) {
        if (*l != 0) GSlightSetActive(*on, 0);
    }
    return 0;
}

s32 menuModelRender(MENU_MODEL* m) {
    if (_modeloff != 0) return 0;
    if (m->visible == 0) return 0;
    if (m == 0) return 0;
    if (m->state != 2) return 0;
    u32 mdl;
    if (m->cur.kind != 0) {
        if (m->model == 0) return 0;
        mdl = Sequence_GetGSmodel(m->model);
    } else {
        mdl = m->model;
    }
    if (mdl == 0) return 0;
    if (m->cur.kind != 0) Sequence_SetCamera(m->model, m->camera);
    else GSmodelSetRenderCamera(m->model, m->camera);
    _menuModelSetupViewport(m);
    u32* l = m->light;
    u8* on = _litonoff;
    for (s32 i = 0; i < 3; i++, l++, on++) {
        if (*l != 0) GSlightSetActive(*on, 0);
    }
    if (m->cur.kind != 0 && m->wazaSeq != 0 && wazaSequenceSysIsValidWaza() == 1 && WazaSequence_IsActive(m->wazaSeq) == 0) {
        WazaSequence_Start(m->wazaSeq, 0);
        Sequence_DoAnimation(m->model, m->cur.anim);
    }
    return 0;
}

}

static void _menuModelRenderOff(MENU_MODEL* m) {
    if (m->cur.kind != 0) {
        if (m->model != 0) Sequence_SetVisibility(m->model, 0);
        if (m->wazaSeq != 0 && wazaSequenceSysIsValidWaza() == 1 && WazaSequence_IsActive(m->wazaSeq) == 1) {
            WazaSequence_Stop(m->wazaSeq);
        }
    } else if (m->model != 0) {
        GSmodelSetVisibility(m->model, 0);
    }
}

extern "C" {

void menuModelRenderOffAll(MENU_MODEL* m) {
    _menuModelRenderOff(m);
}

s32 menuModelCheck(MENU_MODEL* m, u8 wait) {
    if (m == 0) return 0;
    if (wait != 0) {
        while (1) {
            if (m->thread == 0 && m->state != 1) return 0;
            GSthreadSwitch();
        }
    }
    if (m->thread == 0) return 0;
    return m->state == 1;
}

s32 menuModelFreeNext(MENU_MODEL* m) {
    if (m == 0) return 0;
    m->loading = 0;
    if (m->pending.kind != 0) {
        if (m->nextModel != 0) {
            Sequence_SetVisibility(m->nextModel, 0);
            Sequence_Free(m->nextModel);
            m->nextModel = 0;
        }
    } else if (m->nextModel != 0) {
        GSmodelFree(m->nextModel);
        m->nextModel = 0;
    }
    m->state = 0;
    return 1;
}

void menuModelWazaFree(MENU_MODEL* m) {
    if (m != 0 && m->cur.kind != 0 && m->wazaSeq != 0) {
        WazaSequence_Free(m->wazaSeq);
        m->wazaSeq = 0;
    }
}

s32 menuModelFree(MENU_MODEL* m) {
    if (m == 0) return 0;
    m->loading = 0;
    if (m->cur.kind != 0) {
        if (m->model != 0) {
            Sequence_SetVisibility(m->model, 0);
            Sequence_Free(m->model);
            m->model = 0;
        }
    } else if (m->model != 0) {
        GSmodelFree(m->model);
        m->model = 0;
    }
    m->state = 0;
    return 1;
}

s32 fn_80112AAC(MENU_MODEL* m, Pokemon* p) {
    if (m == 0) return 0;
    if (menuModelComparePokemon(m, p) != 0) return 0;
    if (m->state != 0) {
        if (m->state >= 0) {
        }
    } else {
        m->state = 1;
    }
    _menuModelMakeLoadInfo(&m->pending, p, 0, false);
    m->loading = 1;
    if (m->thread != 0) {
        if (GSthreadIsRunning(m->thread) != 0) return 1;
        GSthreadClose(m->thread);
    }
    wazaSequenceSysSetVisibilityAll(0);
    m->thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (s32(*)(void*))_menuModelLoadThread);
    if (m->thread != 0) GSthreadSetArgs(1, m);
    return 1;
}

s32 menuModelLoadPokemon(MENU_MODEL* m, Pokemon* p) {
    if (m == 0) return 0;
    if (menuModelComparePokemon(m, p) != 0) return 0;
    if (m->state != 0) {
        if (m->state >= 0) {
        }
    } else {
        m->state = 1;
    }
    _menuModelMakeLoadInfo(&m->pending, p, 0, true);
    m->loading = 1;
    if (m->thread != 0) {
        if (GSthreadIsRunning(m->thread) != 0) return 1;
        GSthreadClose(m->thread);
    }
    wazaSequenceSysSetVisibilityAll(0);
    m->thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (s32(*)(void*))_menuModelLoadThread);
    if (m->thread != 0) GSthreadSetArgs(1, m);
    return 1;
}

s32 menuModelLoad(MENU_MODEL* m, s32 id) {
    if (m == 0) return 0;
    if (menuModelCompareObject(m, id) != 0) return 0;
    if (m->state != 0) {
        if (m->state >= 0) {
        }
    } else {
        m->state = 1;
    }
    m->pending.kind = 0;
    m->pending.id = id;
    m->loading = 1;
    if (m->thread != 0) {
        if (GSthreadIsRunning(m->thread) != 0) return 1;
        GSthreadClose(m->thread);
    }
    m->thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (s32(*)(void*))_menuModelLoadThread);
    if (m->thread != 0) GSthreadSetArgs(1, m);
    return 0;
}

u8 menuModelComparePokemon(MENU_MODEL* m, Pokemon* p) {
    MENU_MODEL_LOAD info;
    if (m == 0) return 0;
    _menuModelMakeLoadInfo(&info, p, 0, true);
    if (m->loading != 0) return _menuModelCmpLoadInfo(&m->pending, &info);
    return _menuModelCmpLoadInfo(&m->cur, &info);
}

}

extern "C" u8 menuModelCompareObject(MENU_MODEL* m, s32 id) {
    MENU_MODEL_LOAD info;
    if (m == 0) return 0;
    info.kind = 0;
    info.id = id;
    if (m->loading != 0) return _menuModelCmpLoadInfo(&m->pending, &info);
    return _menuModelCmpLoadInfo(&m->cur, &info);
}

extern "C" void menuModelTerm(MENU_MODEL* m) {
    _menuModelTerm(m);
}

static s32 _menuModelTerm(MENU_MODEL* m) {
    if (m == 0) return 0;
    if (m->inited == 0) return 0;
    if (_menuModelRef <= 0) {
        GSlogWrite("[%s] 必要以上に開放しようとしました\n", __FUNCTION__);
        return 0;
    }
    m->loading = 0;
    m->inited = 0;
    if (GSthreadGetCurrentThread() != 0) {
        while (m->thread != 0) {
            if (GSthreadIsRunning(m->thread) == 0) {
                GSthreadClose(m->thread);
                break;
            }
            GSthreadSwitch();
        }
    } else if (m->thread != 0) {
        GSthreadClose(m->thread);
        m->thread = 0;
    }
    u8 freeNext = 0;
    if (m->model != m->nextModel) freeNext = 1;
    menuModelFree(m);
    if (freeNext != 0) menuModelFreeNext(m);
    u32* l = m->light;
    for (s32 i = 0; i < 3; i++, l++) {
        if (*l != 0) {
            GSlightFree(*l);
            *l = 0;
        }
    }
    if (m->camera != 0) {
        GScameraFree(m->camera);
        m->camera = 0;
    }
    _menuModelRef -= 1;
    return 1;
}

extern "C" s32 menuModelInit(MENU_MODEL* m, s32 w, s32 h) {
    f32 pos[3];
    f32 rot[3];
    f32 target[3];
    struct Col { u8 r, g, b, a; };
    Col white = { 0xFF, 0xFF, 0xFF, 0xFF };
    Col amb = { 0x80, 0x80, 0x80, 0xFF };
    f32 pos2[3];
    pos[0] = 15.0f;
    pos[1] = 15.0f;
    pos[2] = 15.0f;
    rot[0] = 0.0f;
    rot[1] = 0.0f;
    rot[2] = 0.0f;
    target[0] = 0.0f;
    target[1] = 0.0f;
    target[2] = 0.0f;
    if (m == 0) return 0;
    memset(m, 0, 0xEC);
    m->inited = 1;
    m->visible = 1;
    m->progress = 0.0f;
    if (_menuModelRef >= 4) {
        GSlogWrite("[%s] 参照回数上限オーバー\n", __FUNCTION__);
        return 0;
    }
    m->w = w;
    m->h = h;
    m->x = 0;
    m->y = 0;
    m->f84 = 1;
    m->zoom = 1.0f;
    m->clip = 1;
    m->angle[0] = 0.0f;
    m->angle[1] = 0.0f;
    m->angle[2] = 0.0f;
    m->offset[0] = 0.0f;
    m->offset[1] = 0.0f;
    m->offset[2] = 0.0f;
    m->camera = GScameraCreate();
    if (m->camera == 0) {
        GSlogWrite("[%s] カメラの確保に失敗\n", __FUNCTION__);
        return 0;
    }
    GScameraSetPosition(m->camera, pos);
    GScameraSetRotation(m->camera, rot);
    u32* slot = m->light;
    for (s32 i = 0; i < 3; i++, slot++) {
        u32 l = GSlightCreate();
        if (l != 0) {
            switch (i) {
            case 0:
                GSlightSetType(l, 0);
                {
                    Col c = amb;
                    GSlightSetColor(l, &c);
                }
                break;
            case 1:
                GSlightSetType(l, 1);
                {
                    Col c = white;
                    GSlightSetColor(l, &c);
                }
                GSlightSetPosition(l, pos);
                GSlightSetTarget(l, target);
                break;
            case 2:
                pos[0] = 10.0f;
                pos[1] = 10.0f;
                pos[2] = 10.0f;
                GSlightSetType(l, 2);
                {
                    Col c = white;
                    GSlightSetColor(l, &c);
                }
                GSlightSetPosition(l, pos);
                GSlightSetTarget(l, target);
                break;
            }
            GSlightSetActive(l, 0);
            *slot = l;
        }
    }
    m->camRot[0] = 0.0f;
    m->camRot[1] = 0.0f;
    m->camRot[2] = 0.0f;
    _menuModelRef += 1;
    return 1;
}

extern "C" s32 menuModelSetSize(MENU_MODEL* m, s32 x, s32 y, s32 w, s32 h) {
    if (m == 0) return 0;
    m->x = x;
    m->y = y;
    m->w = w;
    m->h = h;
    return 1;
}

static s32 _menuModelLoadThread(MENU_MODEL* m) {
    u32 model;
    if (m == 0) return 0;
    m->progress = 0.0f;
    if (m->loading == 0) return 0;
    while (menuFaceCheckLoading() != 0) GSthreadSwitch();
    wazaSequenceSysSetVisibilityAll(0);
    _menuModelRenderOff(m);
    if (m->cur.pk.waza != 0) menuModelWazaFree(m);
    while (1) {
        if (m->model != m->nextModel) menuModelFreeNext(m);
        m->state = 1;
        m->loading = 0;
        m->cur = m->pending;
        if (m->cur.kind != 0) {
            m->nextModel = Sequence_LoadPokemon(m->cur.pk.form, m->cur.rnd, m->cur.shadow);
            if (m->nextModel == 0) {
                m->state = 0;
                return 0;
            }
            model = Sequence_GetGSmodel(m->nextModel);
            if (model == 0) {
                m->state = 0;
                return 0;
            }
            if (m->cur.pk.waza != 0) {
                m->nextWaza = Sequence_LoadWaza(m->nextModel, 4, 0);
                if (m->nextWaza != 0) WazaSequence_Start(m->nextWaza, 0);
            }
            Sequence_DoAnimation(m->nextModel, m->cur.anim);
        } else {
            m->nextModel = floorOpenObject(m->cur.id);
            if (m->nextModel == 0) return 0;
            if (GSmodelCanAnimate(m->nextModel) != 0) {
                GSmodelSetAnimIndex(m->nextModel, m->cur.rnd);
                GSmodelSetAnimRate(m->nextModel, 0.5f);
                GSmodelStartAnimation(m->nextModel);
            }
            model = m->nextModel;
        }
        GSmodelSetVisibility(model, 0);
        GSmodelSetAnimType(model, 1);
        GSmodelSetRenderLayer(model, 1, &_layerID);
        GSmodelSetBoundCheck(model, 0);
        if (m->loading != 1) break;
    }
    menuModelFree(m);
    m->state = 1;
    m->waitCount = 0;
    m->model = m->nextModel;
    m->wazaSeq = m->nextWaza;
    _menuModelAdjustCamera(m, false);
    m->sizeValid = 0;
    m->nextModel = 0;
    m->nextWaza = 0;
    m->state = 2;
    m->thread = 0;
    return 1;
}

static inline f32 modelSizeScale(s32 sz) {
    switch (sz) {
    case -2: return 0.8f;
    case -1: return 0.9f;
    case 0: return 1.0f;
    case 1: return 1.1f;
    case 2: return 1.15f;
    case 3: return 1.2f;
    default: return 1.0f;
    }
}

static s32 _menuModelAdjustCamera2(MENU_MODEL* a, MENU_MODEL* b) {
    f32 persp[4];
    u8 mtxA[0x30];
    u8 mtxB[0x30];
    f32 camPos[3];
    f32 spos[3];
    f32 tpos[3];
    f32 lpos[3];
    f32 ltgt[3];
    f32 scaleAngle[3];
    u32 col;
    u32 modelA;
    u32 modelB;
    f32 sizeScale;
    static GSvec upVec2;
    static GSvec target2;
    upVec2.y = 1.0f;
    if (a == 0) return 0;
    if (b == 0) return 0;
    if (a->cur.kind != 0) {
        modelA = Sequence_GetGSmodel(a->model);
        sizeScale = modelSizeScale(Sequence_GetModelSize(a->model));
        memoGetScaleAngle(*(u16*)&a->cur.pk.form, &scaleAngle[0], &scaleAngle[1]);
    } else {
        modelA = a->model;
        sizeScale = 1.0f;
        scaleAngle[0] = 1.0f;
    }
    if (b != 0) modelB = b->model;
    if (modelA == 0) {
        a->state = 0;
        return 0;
    }
    if (modelB == 0) return 0;
    if (a->sizeValid == 0) {
        u32 bound = GSmodelGetBound(modelA);
        if (bound == 0) return 0;
        GSboundGetSize(a->size, 0, 0);
        GSboundGetMinMax(bound, a->min, a->max, 0, 0, 0, 0);
        a->sizeValid = 1;
    }
    if (b->sizeValid == 0) {
        u32 bound = GSmodelGetBound(modelB);
        if (bound == 0) return 0;
        GSboundGetSize(b->size, 0, 0);
        GSboundGetMinMax(bound, b->min, b->max, 0, 0, 0, 0);
        b->sizeValid = 1;
    }
    f32 depth = a->size[1];
    f32 width = a->size[0] + b->size[0];
    if (depth == b->size[1]) {
    } else {
        depth = b->size[1];
    }
    f32 mid = (width * 0.5f) + -b->size[0];
    GSmodelGetPosition(modelA, spos);
    spos[1] = 0.0f;
    spos[2] = 0.0f;
    spos[0] = -(a->size[0] * 0.5f) + mid;
    PSVECAdd(spos, a->offset, spos);
    GSmodelSetPosition(modelA, spos);
    GSmodelGetPosition(modelB, tpos);
    tpos[1] = 0.0f;
    tpos[2] = 0.0f;
    tpos[0] = (b->size[0] * 0.5f) + mid;
    PSVECAdd(tpos, b->offset, tpos);
    GSmodelSetPosition(modelB, tpos);
    if (a->camera == 0) return 0;
    GScameraGetPerspective(a->camera, &persp[0], &persp[1], &persp[2], &persp[3]);
    persp[1] = 1.3333334f;
    persp[0] = _camFov;
    f32 dispScale;
    switch (*(u16*)&a->cur.pk.form) {
    case 0x4E:
    case 0x82:
    case 0x90:
    case 0x96:
    case 0xD0:
    case 0xF3:
    case 0xFA:
        dispScale = _disp_scale;
        break;
    default:
        dispScale = 1.0f;
        break;
    }
    if (width > depth) {
    } else {
        width = depth;
    }
    f32 t = (f32)tan(0.017453292f * persp[0] * 0.5f);
    f32 zoom = a->zoom;
    f32 f5 = 0.8f * (width / sizeScale);
    f32 dist = f5 / t;
    upVec2.x = 0.0f;
    target2.y = 0.75f * depth;
    camPos[0] = 0.0f;
    camPos[1] = 0.0f;
    camPos[2] = ((dist * scaleAngle[0]) / dispScale) / zoom;
    PSMTXRotRad(mtxA, 0x58, a->camRot[0]);
    PSMTXRotRad(mtxB, 0x59, -a->camRot[1]);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXMultVec(mtxA, camPos, camPos);
    GScameraSetPosition(a->camera, camPos);
    GScameraSetPerspective(a->camera, persp[0], persp[1], persp[2], persp[3]);
    GScameraLookAt(a->camera, &upVec2, &target2);
    C_MTXLookAt(a->mtx, camPos, &upVec2, &target2);
    memcpy(&col, &_lightColor, 4);
    memcpy(lpos, camPos, 0xC);
    lpos[0] = lpos[0] + _lightOffset.x;
    lpos[1] = lpos[1] + _lightOffset.y;
    lpos[2] = lpos[2] + _lightOffset.z;
    GSlightSetType(a->light[2], 2);
    GSlightSetColor((u8)a->light[2], &col);
    GSlightSetPosition((u8)a->light[2], lpos);
    GSlightSetTarget((u8)a->light[2], ltgt);
    return 1;
}

static void _menuModelSetupViewport2(MENU_MODEL* a, MENU_MODEL* b) {
    if (a->camera != 0) {
        f32 x = (f32)a->x;
        f32 y = (f32)a->y;
        f32 w = (f32)a->w;
        f32 w0 = w;
        f32 h = (f32)a->h;
        f32 h0 = h;
        bool wider = w > h;
        if (wider) w = 1.3333334f * h;
        if (!wider) h = w / 1.3333334f;
        x = x + (0.5f * (w0 - w));
        y = y + (0.5f * (h0 - h));
        if (a->clip != 0) GScameraSetScissor(1, (s32)x, (s32)y, (s32)w, (s32)h);
        else GScameraSetScissor(0, 0, 0, 0x280, 0x1E0);
        GScameraSetViewport(a->camera, 1, x, y, (0.5f * w) + x, (0.5f * h) + y);
        if (a->waitCount < _waitframe) a->waitCount++;
        if (a->waitCount >= _waitframe) {
            if (a->cur.kind != 0) {
                Sequence_SetVisibility(a->model, 1);
                Sequence_SetCamera(a->model, a->camera);
            } else {
                GSmodelSetVisibility(a->model, 1);
                GSmodelSetRenderCamera(a->model, a->camera);
            }
            if (b->cur.kind != 0) {
                Sequence_SetVisibility(b->model, 1);
                Sequence_SetCamera(b->model, a->camera);
                return;
            }
            GSmodelSetVisibility(b->model, 1);
            GSmodelSetRenderCamera(b->model, a->camera);
            return;
        }
        _menuModelRenderOff(a);
        _menuModelRenderOff(b);
    }
}

static s32 _menuModelAdjustCamera(MENU_MODEL* m, bool first) {
    f32 persp[4];
    u8 mtxA[0x30];
    u8 mtxB[0x30];
    u8 mtxInv[0x30];
    f32 camPos[3];
    f32 spos[3];
    f32 partPos[3];
    f32 lpos[3];
    f32 ltgt[3];
    f32 sub[3];
    f32 scaleAngle[3];
    u32 col;
    u32 model;
    f32 sizeScale;
    static GSvec upVec;
    static GSvec target;
    upVec.y = 1.0f;
    if (m == 0) return 0;
    if (m->cur.kind != 0) {
        model = Sequence_GetGSmodel(m->model);
        sizeScale = modelSizeScale(Sequence_GetModelSize(m->model));
        memoGetScaleAngle(*(u16*)&m->cur.pk.form, &scaleAngle[0], &scaleAngle[1]);
    } else {
        model = m->model;
        sizeScale = 1.0f;
        scaleAngle[0] = 1.0f;
    }
    if (model == 0) {
        m->state = 0;
        return 0;
    }
    u32 part = GSmodelGetPart(model, GSmodelCenterNull(model));
    if (part != 0) {
        GSpartGetTransform(partPos, 0, 0);
        GSpartFree(part);
    }
    if (m->sizeValid == 0) {
        u32 bound = GSmodelGetBound(model);
        GSboundGetSize(m->size, 0, 0);
        GSboundGetMinMax(bound, m->min, m->max, 0, 0, 0, 0);
        m->sizeValid = 1;
    }
    spos[0] = 0.0f;
    spos[2] = 0.0f;
    spos[1] = -(m->min[1] + m->max[1]) * 0.5f;
    PSVECAdd(spos, m->offset, spos);
    GSmodelSetPosition(model, spos);
    if (m->camera == 0) return 0;
    GScameraGetPerspective(m->camera, &persp[0], &persp[1], &persp[2], &persp[3]);
    persp[1] = 1.3333334f;
    persp[0] = _camFov;
    if (m->w > m->h) {
    }
    f32 sx = m->size[0];
    f32 sy = m->size[1];
    f32 width;
    if (sx > sy) width = sx;
    else width = sy;
    f32 f4 = width / sizeScale;
    f32 zoom = m->zoom;
    f32 t = (f32)tan(0.017453292f * persp[0] * 0.5f);
    camPos[0] = 0.0f;
    camPos[1] = 0.0f;
    camPos[2] = ((((0.8f * f4) / t) * scaleAngle[0]) / 1.0f) / zoom;
    PSMTXRotRad(mtxA, 0x58, m->angle[0]);
    PSMTXRotRad(mtxB, 0x59, -m->angle[1]);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXMultVec(mtxA, camPos, camPos);
    persp[3] = 4000.0f;
    GScameraSetPosition(m->camera, camPos);
    GScameraSetPerspective(m->camera, persp[0], persp[1], persp[2], persp[3]);
    GScameraLookAt(m->camera, &upVec, &target);
    C_MTXLookAt(m->mtx, camPos, &upVec, &target);
    PSMTXInverse(m->mtx, mtxInv);
    PSVECSubtract(spos, partPos, sub);
    PSVECDistance(ltgt, partPos);
    memcpy(&col, &_lightColor, 4);
    memcpy(ltgt, camPos, 0xC);
    PSVECAdd(ltgt, (f32*)&_lightOffset, lpos);
    ltgt[0] = lpos[0];
    ltgt[1] = lpos[1];
    ltgt[2] = lpos[2];
    PSVECAdd(partPos, (f32*)&_lightOffset, sub);
    partPos[0] = sub[0];
    partPos[1] = sub[1];
    partPos[2] = sub[2];
    GSlightSetType(m->light[2], 2);
    GSlightSetColor((u8)m->light[2], &col);
    GSlightSetPosition((u8)m->light[2], ltgt);
    GSlightSetTarget((u8)m->light[2], partPos);
    return 1;
}

static void _menuModelSetupViewport(MENU_MODEL* m) {
    if (m->camera != 0) {
        s32 x = m->x;
        s32 y = m->y;
        s32 iw = m->w;
        s32 ih = m->h;
        f32 fx = (f32)x;
        f32 fy = (f32)y;
        f32 w = (f32)iw;
        f32 w0 = w;
        f32 h = (f32)ih;
        f32 h0 = h;
        if (_checkLarge != 0) {
            if (w > h) w = 1.3333334f * h;
            else h = w / 1.3333334f;
        } else if (w < h) {
            w = 1.3333334f * h;
        } else {
            h = w / 1.3333334f;
        }
        fx = fx + (0.5f * (w0 - w));
        fy = fy + (0.5f * (h0 - h));
        if (m->clip != 0) GScameraSetScissor(1, (u16)x, (u16)y, (u16)iw, (u16)ih);
        else GScameraSetScissor(0, 0, 0, 0x280, 0x1E0);
        if (fx < 0.0f) fx = 0.0f;
        if (fy < 0.0f) fy = 0.0f;
        GScameraSetViewport(m->camera, 1, fx, fy, (0.5f * w) + fx, (0.5f * h) + fy);
        if (m->waitCount < _waitframe) m->waitCount++;
        if (m->waitCount >= _waitframe) {
            if (m->cur.kind != 0) {
                Sequence_SetVisibility(m->model, 1);
                Sequence_SetCamera(m->model, m->camera);
                return;
            }
            GSmodelSetVisibility(m->model, 1);
            GSmodelSetRenderCamera(m->model, m->camera);
        }
    }
}

static u8 _menuModelCmpLoadInfo(MENU_MODEL_LOAD* a, MENU_MODEL_LOAD* b) {
    u8 kind = a->kind;
    if (kind == b->kind) {
        if (kind != 0) {
            if (a->pk.form == b->pk.form && a->pk.waza == b->pk.waza && (u32)a->rnd == (u32)b->rnd && a->shadow == b->shadow) return 1;
            return 0;
        }
        if (a->id == b->id) return 1;
        return 0;
    }
    return 0;
}

static void _menuModelMakeLoadInfo(MENU_MODEL_LOAD* out, Pokemon* p, u16 waza, bool shadow) {
    out->kind = 1;
    if (pokemonGetStatus(p, 0, 0xC2, 0) != 0) {
        if (pokemonIsJoutaiDataId(p, 0x3E) == 1) out->pk.waza = 0x87;
        else out->pk.waza = 0x25;
    } else {
        out->pk.waza = waza;
    }
    menuModelGetPkxRndFromPokemonForSeqenceLoad(*(u32*)&out->rnd, out->pk.form, p);
    if (shadow != 0) out->shadow = pokemonGetStatus(p, 0, 0xC1, 0) != 0;
    else out->shadow = 0;
    out->anim = menuModelGetPokemonAnimationIndexByPointer(p);
}

