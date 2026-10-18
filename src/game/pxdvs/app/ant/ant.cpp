// STATUS: 9/20 exact with extra_cflags ["-inline deferred"] (written bottom-to-top). LAYOUT/CONST/CALLS OK; DATA differs only in
// .sdata2 constant order (target's first constant is 1.0f; probably a dead-stripped earlier function used it first).
// Not exact: dispTexture 98.8%, allRequestCancel 97.3% (base pointer register), setAnimation/use/drawAndUpdate* /initByPokemon*
// ~86-87%, draw 3004B 82%. Data format guesses: CAnt is 0x34 bytes.
#include <game/pxdvs/app/pokemon/pokemon.hpp>

extern "C" {
void* memset(void*, int, u32);
void GSfsysFree(u32 id);
s32 GSfsysGetStatus(u32 id);
u8 GSfsysReadID(u32 id, u32 idx);
void GSgfxBeginSurface(unsigned short num);
void GSgfxColor4u8(u8 r, u8 g, u8 b, u8 a);
void GSgfxEndSurface(void);
void GSgfxSetPrimitiveType(u32 type);
void GSgfxSetTUnitUserAlphaArg(u8 unit, u32 a, u32 b, u32 c, u32 d);
void GSgfxSetTUnitUserAlphaOp(u8 unit, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg);
void GSgfxSetTUnitUserColorArg(u8 unit, u32 a, u32 b, u32 c, u32 d);
void GSgfxSetTUnitUserColorOp(u8 unit, u32 op, u32 bias, u32 scale, u8 clamp, u32 reg);
void GSgfxTexCoord2f(f32 s, f32 t);
void GSgfxVertex2s16(s16 x, s16 y);
u8 GSgfxVideoGetVsyncRate(void);
void GSprimSetBlendMode(s32 mode);
void GSresFreeGroup(u32 grp);
void GSresFreeResource(u32 grp, u32 id);
void* GSresGetResource(u32 grp, u32 id);
void GSthreadSwitch(void);
u32 pokemonDB_GetPokebodyId(u16 id, u16 idx);
u8 pokemonGetAnnonKatati(u32 rnd);
f32 timeGetLastFrameSec(void);
void windowDrawSprite(s16 x, s16 y, void* ctx, u16 key, u32 flags, s32 layer);
extern u16 menuRelivehallPcBoxDefaultPokemonSprite;
}

struct GStexture;
struct GSgfxVF;
extern "C" void GSgfxSelectTexture(u8 map, GStexture* texture);
extern "C" void GSgfxSetupRenderAndSelect(GSgfxVF* vf);
extern "C" u16 GStextureGetXsize(GStexture* tex);
extern "C" u16 GStextureGetYsize(GStexture* tex);
extern "C" GSgfxVF* GSgfxVFBuildTemp(int, int, int, int, int, int, int, int, int);

struct GSgfxColAu8 {
    u8 r, g, b, a;
};

template <typename T>
struct PocketVec {
    T x, y;
    static PocketVec<T> zero;
};

struct PokeDanceEntry {
    u32 key;
    void* data;
    s32 use;
};

struct PokeDanceTbl {
    PokeDanceEntry e[240];
    s32 loading;
};

PokeDanceTbl _pokeDance;

static GSgfxColAu8 colorWhite = { 0xFF, 0xFF, 0xFF, 0xFF };
static GSgfxColAu8 colorPurple = { 0x3C, 0x0C, 0xFF, 0xFF };
static GSgfxColAu8 colorNone = { 0, 0, 0, 0 };

struct CAnt {
    u32 key;
    void* res;
    PocketVec<short> pos;
    f32 scale;
    u8 alpha;
    s32 hidden;
    s16 anim, scriptIdx;
    f32 timer;
    s32 offX, offY, frame;
    f32 wait;
    s32 colorMode;

    static f32 colorAnimationTimeDark;
    static f32 colorAnimationTimeReliveReady;

    void drawAndUpdateWithOffset(PocketVec<short> off);
    void drawAndUpdate(PocketVec<short> p);
    void drawAndUpdate();
    void draw(PocketVec<short> off);
    void setAnimation(long a);
    void use();
    void initByPokemonAndSetColorAnimationInReliveHallVisitor(Pokemon*);
    void initByPokemonAndSetColorAnimationInAny(Pokemon*);
    void initByPokemon(Pokemon*);
    void init();
    static void systemUnUseResourceRelease();
    static void systemUsecountReset();
    static void systemUpdate(bool);
    static void waitEndOfReading();
    static void allRequestCancel();
    static void systemFree();
    static void systemInit();

    inline bool isValid() { return key != 0; }
    inline void* getRes();
    inline void step();
    inline void update();
};

f32 CAnt::colorAnimationTimeDark;
f32 CAnt::colorAnimationTimeReliveReady;

static inline int antFindOrAlloc(u32 key) {
    int idx = -1;
    for (int i = 0; i < 240; i++) {
        if (_pokeDance.e[i].key == 0) break;
        if (_pokeDance.e[i].key == key) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        idx = 0;
        for (int k = 0; k < 240; k++) {
            if (_pokeDance.e[idx].key == 0) break;
            idx++;
        }
        memset(&_pokeDance.e[idx], 0, sizeof(PokeDanceEntry));
        _pokeDance.e[idx].key = key;
    }
    return idx;
}

static inline void* antLookup(u32 key) {
    int idx = antFindOrAlloc(key);
    _pokeDance.e[idx].use = 1;
    return _pokeDance.e[idx].data;
}

inline void* CAnt::getRes() {
    if (key == 0) return 0;
    if (res == 0) res = antLookup(key);
    return res;
}

// one step of the animation script
inline void CAnt::step() {
    wait = 0.0f;
    timer = 0.0f;
    u32 k = key;
    void* r;
    if (k == 0) {
        r = 0;
    } else {
        r = res;
        if (r == 0) {
            res = antLookup(k);
            r = res;
        }
    }
    if (r != 0) {
        u8* s = (u8*)r + *(u16*)((u8*)r + anim * 2 + 0x10);
        u8 f = s[scriptIdx++];
        if (f & 2) {
            wait = (f32)(s[scriptIdx++] * 18 / 10) / 60.0f;
        }
        if (f & 4) {
            offX = s[scriptIdx++];
            offY = s[scriptIdx++];
        }
        if (f & 1) {
            frame = s[scriptIdx++];
        }
        if (f & 8) {
            scriptIdx = scriptIdx - s[scriptIdx];
        }
    }
}

inline void CAnt::update() {
    if (wait == 0.0f || (timer = timer + timeGetLastFrameSec(), !(timer < -((0.5f * (1.0f / (f32)GSgfxVideoGetVsyncRate())) - wait)))) {
        if (isValid()) step();
    }
}

static inline void antCompact() {
    PokeDanceTbl* t = &_pokeDance;
    u32 n = 0;
    int w = 0;
    t->e[t->loading].use = 2;
    for (u32 i = 0; i < 240; i++) {
        PokeDanceEntry* s = &t->e[i];
        if (s->key == 0) break;
        if (s->use != 0) {
            n++;
            PokeDanceEntry* d = &_pokeDance.e[w++];
            d->key = s->key;
            d->data = s->data;
            d->use = s->use;
        } else if (s->data != 0) {
            GSresFreeResource(0x825, s->key);
        }
    }
    for (; n < 240; n++) memset(&_pokeDance.e[n], 0, sizeof(PokeDanceEntry));
    PokeDanceEntry* e = t->e;
    for (int idx = 0; idx < 240; e++, idx++) {
        if (e->key == 0) return;
        if (e->use == 2) {
            e->use = 1;
            t->loading = idx;
            return;
        }
    }
}

static inline void antPoll() {
    if (_pokeDance.loading != -1) {
        PokeDanceEntry* e = &_pokeDance.e[_pokeDance.loading];
        if (GSfsysGetStatus(0x825) == 0) {
            e->data = GSresGetResource(0x825, e->key);
            if (e->data != 0) _pokeDance.loading = -1;
        }
    }
}

void antReadPostFunc(void*, unsigned long) {
}

namespace {
void dispTexture(GStexture* tex, f32 x, f32 y, int sx, int sy, int w, int h, GSgfxColAu8 col, f32 scale, u8 alpha) {
    u16 tw = GStextureGetXsize(tex);
    u16 th = GStextureGetYsize(tex);
    f32 u0 = (f32)sx / (f32)tw;
    f32 v0 = (f32)sy / (f32)th;
    f32 u1 = u0 + (f32)w / (f32)tw;
    f32 v1 = v0 + (f32)h / (f32)th;
    if (scale != 1.0f) {
        int hw = w / 2;
        int hh = h / 2;
        w = (int)((f32)w * scale);
        h = (int)((f32)h * scale);
        x = (x + (f32)hw) - (f32)(w / 2);
        y = (y + (f32)hh) - (f32)(h / 2);
    }
    GSgfxSetupRenderAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 1, 1, 4));
    if (alpha != 0xFF) {
        col.a = alpha;
        GSgfxSetTUnitUserColorArg(0, 0xF, 0xF, 0xF, 8);
        GSgfxSetTUnitUserColorOp(0, 0, 0, 0, 1, 0);
        GSgfxSetTUnitUserAlphaArg(0, 7, 5, 4, 7);
        GSgfxSetTUnitUserAlphaOp(0, 0, 0, 0, 1, 0);
    } else {
        GSgfxSetTUnitUserColorArg(0, 8, 0xA, 0xB, 0xF);
        GSgfxSetTUnitUserColorOp(0, 0, 0, 0, 1, 0);
        GSgfxSetTUnitUserAlphaArg(0, 7, 7, 7, 4);
        GSgfxSetTUnitUserAlphaOp(0, 0, 0, 0, 1, 0);
    }
    GSprimSetBlendMode(1);
    u8 r = col.r, g = col.g, b = col.b, a = col.a;
    s16 px = (s16)x;
    s16 py = (s16)y;
    GSgfxSelectTexture(0, tex);
    GSgfxSetPrimitiveType(0x98);
    GSgfxBeginSurface(4);
    GSgfxVertex2s16(px, py);
    GSgfxColor4u8(r, g, b, a);
    GSgfxTexCoord2f(u0, v0);
    int qx = px + w;
    GSgfxVertex2s16(qx, py);
    GSgfxColor4u8(r, g, b, a);
    GSgfxTexCoord2f(u1, v0);
    int qy = py + h;
    GSgfxVertex2s16(px, qy);
    GSgfxColor4u8(r, g, b, a);
    GSgfxTexCoord2f(u0, v1);
    GSgfxVertex2s16(qx, qy);
    GSgfxColor4u8(r, g, b, a);
    GSgfxTexCoord2f(u1, v1);
    GSgfxEndSurface();
}
}

GStexture* antGetGStexture(void* r) {
    return (GStexture*)((u8*)r + *(u32*)((u8*)r + 0xC));
}

void CAnt::systemInit() {
    memset(&_pokeDance, 0, 0xB44);
    _pokeDance.loading = -1;
}

void CAnt::systemFree() {
    while (1) {
        antPoll();
        if (_pokeDance.loading == -1) break;
        GSthreadSwitch();
    }
    GSfsysFree(0x825);
    GSresFreeGroup(0x825);
    memset(&_pokeDance, 0, 0xB44);
}

void CAnt::allRequestCancel() {
    for (int i = 0; i < 240; i++) {
        PokeDanceEntry* e = &_pokeDance.e[i];
        if (i != _pokeDance.loading && e->key != 0 && e->data == 0) e->use = 0;
    }
    antCompact();
}

void CAnt::waitEndOfReading() {
    while (1) {
        antPoll();
        if (_pokeDance.loading == -1) break;
        GSthreadSwitch();
    }
}

void CAnt::systemUpdate(bool start) {
    antPoll();
    if (_pokeDance.loading == -1 && start) {
        PokeDanceEntry* e = _pokeDance.e;
        for (int i = 0; i < 240; e++, i++) {
            if (e->key == 0) break;
            if (e->key != 0 && e->data == 0) {
                GSfsysReadID(0x825, e->key);
                _pokeDance.loading = i;
                break;
            }
        }
    }
    colorAnimationTimeDark += timeGetLastFrameSec();
    colorAnimationTimeReliveReady += timeGetLastFrameSec();
    if (colorAnimationTimeDark > 1.0f) colorAnimationTimeDark -= 1.0f;
    if (colorAnimationTimeReliveReady > 1.0f) colorAnimationTimeReliveReady -= 1.0f;
}

void CAnt::systemUsecountReset() {
    for (int i = 0; i < 240; i++) _pokeDance.e[i].use = 0;
}

void CAnt::systemUnUseResourceRelease() {
    antCompact();
}

void CAnt::init() {
    memset(this, 0, 0x34);
    scale = 1.0f;
    alpha = 0xFF;
}

void CAnt::initByPokemon(Pokemon* p) {
    memset(this, 0, 0x34);
    scale = 1.0f;
    alpha = 0xFF;
    if (p->checkValid()) {
        u16 id = p->getPokemonDataId();
        if (id == 0xC9) {
            u32 tbl[56] = {
                0x1E4C3200, 0x1E4D3200, 0x1E4E3200, 0x1E4F3200, 0x1E503200, 0x1E513200, 0x1E523200, 0x1E533200,
                0x1E543200, 0x1E573200, 0x1E583200, 0x1E593200, 0x1E5A3200, 0x1E5B3200, 0x1E5C3200, 0x1E5D3200,
                0x1E5E3200, 0x1E5F3200, 0x1E603200, 0x1E613200, 0x1E623200, 0x1E633200, 0x1E643200, 0x1E653200,
                0x1E663200, 0x1E673200, 0x1E683200, 0x1E693200, 0x1E6A3200, 0x1E6B3200, 0x1E6C3200, 0x1E6D3200,
                0x1E6E3200, 0x1E713200, 0x1E723200, 0x1E733200, 0x1E743200, 0x1E753200, 0x1E763200, 0x1E773200,
                0x1E783200, 0x1E793200, 0x1E7A3200, 0x1E7B3200, 0x1E7C3200, 0x1E7D3200, 0x1E7E3200, 0x1E7F3200,
                0x1E803200, 0x1E813200, 0x1E823200, 0x1E833200, 0x1E553200, 0x1E563200, 0x1E6F3200, 0x1E703200
            };
            int form = pokemonGetAnnonKatati(pokemonGetStatus(p, 0, 0x6F, 0));
            if (pokemonCheckRare(p)) {
                key = tbl[form * 2 + 1];
            } else {
                key = tbl[form * 2];
            }
        } else if (id == 0xF9 && p->isDarkPokemon()) {
            key = 0x20083200;
        } else {
            key = pokemonDB_GetPokebodyId(id, p->isRare());
        }
        u32 k = key;
        if (k != 0 && res == 0) {
            res = antLookup(k);
        }
    }
}

void CAnt::initByPokemonAndSetColorAnimationInAny(Pokemon* p) {
    initByPokemon(p);
    if (p->isDarkPokemon()) {
        if (p->getDarkPoint() > 0.0f) {
            colorMode = 1;
            return;
        }
        colorMode = 2;
    }
}

void CAnt::initByPokemonAndSetColorAnimationInReliveHallVisitor(Pokemon* p) {
    initByPokemon(p);
    if (p->isDarkPokemon()) {
        if (p->getDarkPoint() > 0.0f) {
            colorMode = 1;
            return;
        }
        colorMode = 2;
    }
}

void CAnt::use() {
    if (key != 0) {
        int idx = antFindOrAlloc(key);
        _pokeDance.e[idx].use = 1;
    }
}

void CAnt::setAnimation(long a) {
    anim = a;
    scriptIdx = 0;
    timer = 0.0f;
    offX = 0;
    offY = 0;
    frame = 0;
    wait = 0.0f;
    if (isValid()) step();
}

void CAnt::draw(PocketVec<short> off) {
    if (key != 0) {
        if (hidden == 1) return;
        PocketVec<short> p;
        p.x = pos.x + off.x;
        p.y = pos.y + off.y;
        if (getRes() == 0) {
            windowDrawSprite(p.x - 0x18, p.y - 0x18, 0, menuRelivehallPcBoxDefaultPokemonSprite, 0, 7);
            return;
        }
        GSgfxColAu8 col;
        switch (colorMode) {
        case 1: {
            f32 f = colorAnimationTimeDark - 0.5f;
            col = colorPurple;
            if (f < 0.0f) f = -f;
            col.a = (s8)(255.0f * ((0.76f * -((2.0f * f) - 1.0f)) + 0.16f));
            break;
        }
        case 0:
            col = colorNone;
            break;
        case 2: {
            f32 f = colorAnimationTimeReliveReady - 0.5f;
            if (f < 0.0f) f = -f;
            f32 t = -((2.0f * f) - 1.0f);
            f32 u = 1.0f - t;
            if (t > 0.5) {
                col.a = (s8)(255.0f * t);
            } else {
                col.a = 0x80;
            }
            col.r = (s8)((f32)colorWhite.r * t + (f32)colorPurple.r * u);
            col.g = (s8)((f32)colorWhite.g * t + (f32)colorPurple.g * u);
            col.b = (s8)((f32)colorWhite.b * t + (f32)colorPurple.b * u);
            break;
        }
        }
        u8* r = (u8*)getRes();
        GStexture* tex = r ? antGetGStexture(r) : 0;
        GStextureGetXsize(tex);
        GStextureGetYsize(tex);
        r = (u8*)getRes();
        u8* tbl = r + *(u32*)(r + 4);
        u8* ent = tbl + frame * 4;
        u8* sp = tbl + *(u16*)(ent + 2);
        for (int i = 0; i < *(u16*)ent; i++) {
            u16* s = (u16*)sp;
            dispTexture(tex, (f32)(p.x + (offX + (s16)s[4])), (f32)(p.y + (offY + (s16)s[5] + 0x20)), s[0], s[1], s[2], s[3], col, scale, alpha);
            sp += 0x1C;
        }
    }
}

void CAnt::drawAndUpdate() {
    if (isValid()) {
        PocketVec<short> z = PocketVec<short>::zero;
        draw(z);
        update();
    }
}

void CAnt::drawAndUpdate(PocketVec<short> p) {
    if (isValid()) {
        pos = p;
        PocketVec<short> z = PocketVec<short>::zero;
        draw(z);
        update();
    }
}

void CAnt::drawAndUpdateWithOffset(PocketVec<short> off) {
    if (isValid()) {
        PocketVec<short> o = off;
        draw(o);
        update();
    }
}
