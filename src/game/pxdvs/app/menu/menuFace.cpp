#include <dolphin/types.h>
#pragma peephole off
#pragma pool_strings off

struct Pokemon;
struct FightPokemon;
struct GStexture;
struct tagWINDOW_WORK;

struct GSvec2 {
    f32 x;
    f32 y;
};
struct GSivec2 {
    s16 x;
    s16 y;
};

struct SpriteBody {
    u8 b[0x3C];
};

struct tagSPRITE_WORK {
    struct tagSPRITE_WORK* next;
    u8 kind;
    u8 flags;
    s16 id;
    s32 unk8;
    SpriteBody body;
    s32 unk48;
    s32 unk4C;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    u32 tex;
    s16 sx;
    s16 sy;
    s16 sw;
    s16 sh;
    s32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    u8 unk74;
    u8 unk75;
    u8 unk76;
    void copy(const tagSPRITE_WORK& o) {
        next = o.next;
        kind = o.kind;
        flags = o.flags;
        id = o.id;
        unk8 = o.unk8;
        body = o.body;
        unk48 = o.unk48;
        unk4C = o.unk4C;
        x = o.x;
        y = o.y;
        w = o.w;
        h = o.h;
        tex = o.tex;
        sx = o.sx;
        sy = o.sy;
        sw = o.sw;
        sh = o.sh;
        unk64 = o.unk64;
        unk68 = o.unk68;
        unk6C = o.unk6C;
        unk70 = o.unk70;
        unk74 = o.unk74;
        unk75 = o.unk75;
        unk76 = o.unk76;
    }
};

typedef Pokemon* (*FaceFn)(void*);

struct FaceEntry {
    u32 texID;
    u16 faceId;
    u8 state;
    s8 texIdx;
    FaceFn fn;
    void* arg;
};

struct FaceRes {
    u8 pad0[7];
    u8 flag;
    s32 cnt;
    u8 pad0C[0x1C];
    s32 off28;
    u8 pad2C[0x1C];
    s32 off48;
};

struct FaceIdPair {
    u16 a;
    u16 b;
};

static FaceIdPair unknown_face_id_tbl[0x1C] = {
    {0x0305, 0x0321}, {0x0306, 0x0322}, {0x0307, 0x0323}, {0x0308, 0x0324}, {0x0309, 0x0325},
    {0x030A, 0x0326}, {0x030B, 0x0327}, {0x030C, 0x0328}, {0x030D, 0x0329}, {0x030E, 0x032A},
    {0x030F, 0x032B}, {0x0310, 0x032C}, {0x0311, 0x032D}, {0x0312, 0x032E}, {0x0313, 0x032F},
    {0x0314, 0x0330}, {0x0315, 0x0331}, {0x0316, 0x0332}, {0x0317, 0x0333}, {0x0318, 0x0334},
    {0x0319, 0x0335}, {0x031A, 0x0336}, {0x031B, 0x0337}, {0x031C, 0x0338}, {0x031D, 0x0339},
    {0x031E, 0x033A}, {0x031F, 0x033B}, {0x0320, 0x033C},
};

struct FaceTex {
    u32 unk0;
    void* data;
};

extern "C" {
u32 pokemonGetStatus(void* ptr, u16 id, u16 kind, u16 index);
u8 pokemonGetFightPokemonDeoxysSel(FightPokemon*);
u32 pokemonBiosGetRnd(Pokemon*);
u8 pokemonBiosGetTamagoFlag(Pokemon*);
u8 pokemonCheckRare(Pokemon*);
bool pokemonCheckValid(Pokemon*);
u8 pokemonGetAnnonKatati(u32);
u8 pokemonIsDarkPokemon(Pokemon*);
void GSthreadSwitch();
void GSfsysFree(u32);
u8 GSfsysReadIDEX(u32 id, u32 idx, s32 a, s32 b, s32 c);
void GSresFreeResource(u32 grp, u32 id);
void* GSresGetResource(u32 grp, u32 id);
void* GSresGetResourceAllGroup(u32 id);
void GSresRegisterResource(void* mem, u32 grp, u32 id, void* freeFunc);
void* GSmemAlloc(u32);
void* GSmemAllocAlign(u32, u32);
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
void DCFlushRange(void*, u32);
void GXInvalidateTexAll();
void GStextureFree(GStexture*);
u16 GStextureGetXsize(GStexture*);
u16 GStextureGetYsize(GStexture*);
GStexture* GStextureLoad(GStexture*);
void winSpriteDrawTexture(tagWINDOW_WORK*, tagSPRITE_WORK*);
extern u16 uToolPokemon_faceId;
}
bool menuFaceBiosGetRareFlag(u16 id);
u32 menuFaceBiosGetTexID(u16 id);

static s32 _menuFaceListNum;
static FaceEntry* pMenuFaceList;
static FaceTex* pMenuFaceTexList;
static u8 _menuFaceLoadCallBackFlag;
static u8 _testType;

static s32 _unloadTexture(void*, u32, u32);
static s32 _menuFaceGetListNum();
static s32 _menuFaceSearchList(u16 id);
static s32 _menuFaceAddList(u16 id, FaceFn fn, void* arg);
static void _menuFaceLoadCallBack(s32, void*, s32);
static u16 _menuFaceGetIDSub(Pokemon* p, u8 a, s8 b);
static s32 _menuFaceDispFromID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id, GSvec2* ofs);
static s32 _menuFaceDispFromID3(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id, GSivec2* a, GSivec2* b);

extern "C" {
u16 menuFaceGetID(Pokemon* p);
u16 menuFaceGetID2(Pokemon* p, u8 a);
u16 menuFaceGetID3(Pokemon* p, u8 a, s8 b);
u32 menuFaceGetTexID(u16 id);
s8 menuFaceSearchEnable(u16 id);
u8 menuFaceCheckLoading();
s32 menuFaceLoadFromID(u16 id, FaceFn fn, void* arg);
s32 menuFaceLoadFromID_Tool(u16 id, FaceFn fn, void* arg);
void menuFaceDispFromID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id);

s32 menuFaceLoadFightPokemon(FightPokemon* fp, FaceFn fn, void* arg) {
    Pokemon* p = (Pokemon*)pokemonGetStatus(fp, 0, 0xCC, 0);
    u8 sel = pokemonGetFightPokemonDeoxysSel(fp);
    u16 id = menuFaceGetID2(p, sel);
    menuFaceLoadFromID(id, fn, arg);
    while (1) {
        if (menuFaceSearchEnable(id) != 0) {
            break;
        }
        GSthreadSwitch();
    }
    if ((u16)(id - 0x33F) <= 1 || id == 0x33E) {
        id = 0x181;
        menuFaceLoadFromID(0x181, fn, arg);
        while (1) {
            if (menuFaceSearchEnable(0x181) != 0) {
                break;
            }
            GSthreadSwitch();
        }
    }
    if ((u16)(id - 0x343) <= 1 || id == 0x342) {
        menuFaceLoadFromID(0x303, fn, arg);
        while (1) {
            if (menuFaceSearchEnable(0x303) != 0) {
                break;
            }
            GSthreadSwitch();
        }
    }
    return 1;
}

void menuFaceLoad_Tool(Pokemon* p, FaceFn fn, void* arg) {
    menuFaceLoadFromID_Tool(menuFaceGetID2(p, 0), fn, arg);
}

void menuFaceLoad(Pokemon* p, FaceFn fn, void* arg) {
    menuFaceLoadFromID(menuFaceGetID(p), fn, arg);
}

s32 menuFaceLoadFromID_Tool(u16 id, FaceFn fn, void* arg) {
    u32 tex;
    for (;;) {
        if (id == 0) {
            Pokemon* p = 0;
            if (fn != 0) {
                p = fn(arg);
            }
            if (p != 0) {
                id = uToolPokemon_faceId;
            }
        }
        if (id == 0) {
            if (menuFaceCheckLoading()) {
                return 0;
            }
            s32 n = _menuFaceGetListNum();
            s32 i;
            FaceEntry* e = pMenuFaceList;
            for (i = 0; i < n; e++, i++) {
                if (e->state == 0) {
                    id = pMenuFaceList[i].faceId;
                    break;
                }
            }
            if (i == n) {
                GSfsysFree(0x5C0);
                return 0;
            }
        } else {
            if (_menuFaceSearchList(id) >= 0) {
                _menuFaceAddList(id, fn, arg);
                id = 0;
                continue;
            }
            _menuFaceAddList(id, fn, arg);
        }
        tex = menuFaceGetTexID(id);
        if (tex == 0) {
            id = 0;
            continue;
        }
        if (menuFaceCheckLoading()) {
            return 1;
        }
        pMenuFaceList[_menuFaceSearchList(id)].state = 1;
        _menuFaceLoadCallBackFlag = 0;
        GSfsysReadIDEX(0x5C0, tex, (s32)_menuFaceLoadCallBack, 0, id);
        return 1;
    }
}

s32 menuFaceLoadFromID(u16 id, FaceFn fn, void* arg) {
    u32 tex;
    for (;;) {
        if (id == 0) {
            Pokemon* p = 0;
            if (fn != 0) {
                p = fn(arg);
            }
            if (p != 0) {
                id = menuFaceGetID(p);
            }
        }
        if (id == 0) {
            if (menuFaceCheckLoading()) {
                return 0;
            }
            s32 n = _menuFaceGetListNum();
            s32 i;
            FaceEntry* e = pMenuFaceList;
            for (i = 0; i < n; e++, i++) {
                if (e->state == 0) {
                    id = pMenuFaceList[i].faceId;
                    break;
                }
            }
            if (i == n) {
                GSfsysFree(0x5C0);
                return 0;
            }
        } else {
            if (_menuFaceSearchList(id) >= 0) {
                _menuFaceAddList(id, fn, arg);
                id = 0;
                continue;
            }
            _menuFaceAddList(id, fn, arg);
        }
        tex = menuFaceGetTexID(id);
        if (tex == 0) {
            id = 0;
            continue;
        }
        if (menuFaceCheckLoading()) {
            return 1;
        }
        pMenuFaceList[_menuFaceSearchList(id)].state = 1;
        _menuFaceLoadCallBackFlag = 1;
        GSfsysReadIDEX(0x5C0, tex, (s32)_menuFaceLoadCallBack, 0, id);
        return 1;
    }
}

u8 menuFaceCheckLoading() {
    int n = _menuFaceGetListNum();
    FaceEntry* e = pMenuFaceList;
    for (int i = 0; i < n; e++, i++) {
        if (e->state == 1) {
            return 1;
        }
    }
    return 0;
}
}

static void _menuFaceLoadCallBack(s32, void*, s32 arg) {
    u16 id = arg;
    FaceEntry* e;
    u32 texID = menuFaceGetTexID(id);
    s32 idx = _menuFaceSearchList(id);
    if (idx < 0) {
        if (texID != 0) {
            GSresFreeResource(0x5C0, texID);
        }
    } else {
        e = &pMenuFaceList[idx];
        FaceRes* res = (FaceRes*)GSresGetResource(0x5C0, texID);
        res->flag = 0;
        res->off28 -= (s32)res;
        if (res->cnt <= 1) {
            res->off48 -= (s32)res;
        }
        memcpy(pMenuFaceTexList[e->texIdx].data, res, 0x1F60);
        GSresFreeResource(0x5C0, texID);
        GStexture* tex = GStextureLoad((GStexture*)pMenuFaceTexList[e->texIdx].data);
        GSresRegisterResource(tex, 0x5C0, texID, (void*)_unloadTexture);
        DCFlushRange(tex, 0x1F60);
        GXInvalidateTexAll();
        e->state = 2;
        if (_menuFaceLoadCallBackFlag != 0) {
            menuFaceLoadFromID(0, e->fn, e->arg);
            return;
        }
        menuFaceLoadFromID_Tool(0, e->fn, e->arg);
    }
}

extern "C" {
void menuFaceDisp(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, Pokemon* p) {
    menuFaceDispFromID(w, sp, menuFaceGetID(p));
}

s32 menuFaceDispFromID3(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id, GSivec2* a, GSivec2* b) {
    return _menuFaceDispFromID3(w, sp, id, a, b);
}

s32 menuFaceDispFromID2(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id, GSvec2* ofs) {
    return _menuFaceDispFromID(w, sp, id, ofs);
}

void menuFaceDispFromID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id) {
    _menuFaceDispFromID(w, sp, id, 0);
}
}

static s32 _menuFaceDispFromID3(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id, GSivec2* a, GSivec2* b) {
    static tagSPRITE_WORK sprite_work;
    if (menuFaceSearchEnable(id) != 1) {
        return 0;
    }
    u32 texID = menuFaceGetTexID(id);
    if (texID == 0) {
        return 0;
    }
    GStexture* tex = (GStexture*)GSresGetResourceAllGroup(texID);
    if (tex == 0) {
        return 0;
    }
    sprite_work.copy(*sp);
    sprite_work.tex = texID;
    if (b != 0) {
        sprite_work.x = b->x;
        sprite_work.y = b->y;
    } else {
        sprite_work.x = 0;
        sprite_work.y = 0;
    }
    sprite_work.sx = 0;
    sprite_work.sy = 0;
    sprite_work.sw = 42;
    sprite_work.sh = 42;
    if (menuFaceBiosGetRareFlag(id) && GStextureGetYsize(tex) > 42) {
        sprite_work.sy = 42;
    }
    sprite_work.w = a->x;
    sprite_work.h = a->y;
    if (a->x < 0 && GStextureGetXsize(tex) > 42) {
        sprite_work.sx = 42;
        s16 v = a->x;
        sprite_work.w = v < 0 ? -v : v;
    }
    winSpriteDrawTexture(w, &sprite_work);
    return 1;
}

static s32 _menuFaceDispFromID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id, GSvec2* ofs) {
    static tagSPRITE_WORK sprite_work;
    if (menuFaceSearchEnable(id) != 1) {
        return 0;
    }
    u32 texID = menuFaceGetTexID(id);
    if (texID == 0) {
        return 0;
    }
    GStexture* tex = (GStexture*)GSresGetResourceAllGroup(texID);
    if (tex == 0) {
        return 0;
    }
    sprite_work.copy(*sp);
    sprite_work.tex = texID;
    if (ofs != 0) {
        sprite_work.x = ofs->x;
        sprite_work.y = ofs->y;
    } else {
        sprite_work.x = 0;
        sprite_work.y = 0;
    }
    sprite_work.sx = 0;
    sprite_work.sy = 0;
    sprite_work.sw = 42;
    sprite_work.sh = 42;
    if (menuFaceBiosGetRareFlag(id) && GStextureGetYsize(tex) > 42) {
        sprite_work.sy = 42;
    }
    if (sprite_work.w < 0 && GStextureGetXsize(tex) > 42) {
        int v = sprite_work.w;
        sprite_work.sx = 42;
        if (v < 0) {
            v = -v;
        }
        sprite_work.w = (s16)v;
    }
    winSpriteDrawTexture(w, &sprite_work);
    return 1;
}

extern "C" {
u32 menuFaceGetTexID(u16 id) {
    return menuFaceBiosGetTexID(id);
}

u16 menuFaceGetID3(Pokemon* p, u8 a, s8 b) {
    return _menuFaceGetIDSub(p, a, b);
}

u16 menuFaceGetID2(Pokemon* p, u8 a) {
    return _menuFaceGetIDSub(p, a, -1);
}

u16 menuFaceGetID(Pokemon* p) {
    return _menuFaceGetIDSub(p, _testType, -1);
}
}

static u16 _menuFaceGetIDSub(Pokemon* p, u8 a, s8 b) {
    if (p == 0) {
        return 0;
    }
    if (pokemonCheckValid(p) == 0) {
        return 0x33D;
    }
    if (pokemonBiosGetTamagoFlag(p) != 0) {
        return 0x33D;
    }
    u16 data;
    u8 rare = pokemonCheckRare(p);
    if (b >= 0) {
        rare = b != 0;
    }
    data = pokemonGetStatus(p, 0, 0x6E, 0);
    if (data == 0x19A) {
        if (rare == 0) {
            if (a == 1) {
                return 0x340;
            }
            if (a == 2) {
                return 0x33F;
            }
            if (a == 3) {
                return 0x33E;
            }
            return pokemonGetStatus(0, data, 0x5B, 0);
        }
        if (a == 1) {
            return 0x344;
        }
        if (a == 2) {
            return 0x343;
        }
        if (a == 3) {
            return 0x342;
        }
        return pokemonGetStatus(0, data, 0x5B, 1);
    }
    if (data == 0xF9) {
        if (pokemonIsDarkPokemon(p) != 0) {
            return 0x345;
        }
        if (rare == 0) {
            return pokemonGetStatus(0, data, 0x5B, 0);
        }
        return pokemonGetStatus(0, data, 0x5B, 1);
    }
    if (data == 0xC9) {
        u32 rnd = pokemonBiosGetRnd(p);
        int k = (u8)pokemonGetAnnonKatati(rnd);
        if (rare == 0) {
            return unknown_face_id_tbl[k].a;
        }
        return unknown_face_id_tbl[k].b;
    }
    if (rare == 0) {
        return pokemonGetStatus(0, data, 0x5B, 0);
    }
    return pokemonGetStatus(0, data, 0x5B, 1);
}

extern "C" {
s8 menuFaceSearchEnable(u16 id) {
    s32 i = _menuFaceSearchList(id);
    if (i < 0) {
        return -1;
    }
    return pMenuFaceList[i].state == 2;
}
}

static s32 _menuFaceAddList(u16 id, FaceFn fn, void* arg) {
    u32 tex;
    s32 n;
    s32 idx;
    s32 i;
    FaceEntry* d;
    u8 fState;
    u32 fTex;
    FaceFn fFn;
    void* fArg;
    u16 fFace;
    s8 fIdx;
    u32 eTex;
    u16 eFace;
    u8 eState;
    s8 eIdx;
    FaceFn eFn;
    void* eArg;
    tex = menuFaceGetTexID(id);
    if (tex == 0) {
        return -2;
    }
    n = _menuFaceGetListNum();
    idx = _menuFaceSearchList(id);
    if (idx < 0) {
        if (n == _menuFaceListNum) {
            fArg = pMenuFaceList[0].arg;
            fFace = pMenuFaceList[0].faceId;
            fIdx = pMenuFaceList[0].texIdx;
            fFn = pMenuFaceList[0].fn;
            fState = pMenuFaceList[0].state;
            fTex = pMenuFaceList[0].texID;
            if (fState == 2) {
                GSresFreeResource(0x5C0, fTex);
            }
            for (i = 0; i < n - 1; i++) {
                pMenuFaceList[i] = pMenuFaceList[i + 1];
            }
            n = _menuFaceListNum - 1;
            d = &pMenuFaceList[n];
            d->texID = fTex;
            d->faceId = fFace;
            d->state = fState;
            d->texIdx = fIdx;
            d->fn = fFn;
            d->arg = fArg;
        }
        pMenuFaceList[n].texID = tex;
        pMenuFaceList[n].faceId = id;
        pMenuFaceList[n].state = 0;
        pMenuFaceList[n].fn = fn;
        pMenuFaceList[n].arg = arg;
        return n;
    }
    eTex = pMenuFaceList[idx].texID;
    eFace = pMenuFaceList[idx].faceId;
    eState = pMenuFaceList[idx].state;
    eIdx = pMenuFaceList[idx].texIdx;
    eFn = pMenuFaceList[idx].fn;
    eArg = pMenuFaceList[idx].arg;
    for (; idx < n - 1; idx++) {
        pMenuFaceList[idx] = pMenuFaceList[idx + 1];
    }
    d = &pMenuFaceList[idx];
    d->texID = eTex;
    d->faceId = eFace;
    d->state = eState;
    d->texIdx = eIdx;
    d->fn = eFn;
    d->arg = eArg;
    return idx;
}

static s32 _menuFaceGetListNum() {
    FaceEntry* e = pMenuFaceList;
    int i;
    for (i = 0; i < _menuFaceListNum; e++, i++) {
        if (e->texID == 0) {
            break;
        }
    }
    return i;
}

static s32 _menuFaceSearchList(u16 id) {
    u32 tex = menuFaceGetTexID(id);
    FaceEntry* e = pMenuFaceList;
    for (int i = 0; i < _menuFaceListNum; e++, i++) {
        if (tex == e->texID) {
            return i;
        }
    }
    return -1;
}

extern "C" {
void menuFaceAllocMemory() {
}

void menuFaceInit(s32 n) {
    s32 i;
    _menuFaceListNum = n;
    if (pMenuFaceList == 0) {
        pMenuFaceList = (FaceEntry*)GSmemAlloc(n * sizeof(FaceEntry));
    }
    memset(pMenuFaceList, 0, _menuFaceListNum * sizeof(FaceEntry));
    if (pMenuFaceTexList == 0) {
        pMenuFaceTexList = (FaceTex*)GSmemAlloc(_menuFaceListNum * sizeof(FaceTex));
    }
    memset(pMenuFaceTexList, 0, _menuFaceListNum * sizeof(FaceTex));
    for (i = 0; i < _menuFaceListNum; i++) {
        if (pMenuFaceTexList[i].data == 0) {
            pMenuFaceTexList[i].data = GSmemAllocAlign(0x1F60, 0x20);
        }
        memset(pMenuFaceTexList[i].data, 0, 0x1F60);
        pMenuFaceList[i].texIdx = i;
    }
}
}

static s32 _unloadTexture(void* tex, u32, u32) {
    GStextureFree((GStexture*)tex);
    return 1;
}
