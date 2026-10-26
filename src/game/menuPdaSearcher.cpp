#pragma peephole off
#pragma pool_strings off
#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
#include <game/shared/menu_work.h>

struct GStexture;
struct GSgfxVF;
struct GSgfxLight;
struct GSmtx;
enum GSgfxCunitAlpha {};
enum GSgfxCunitSrc {};
enum GSgfxLightType {};
enum GSgfxDiffuseFunc {};
enum GSgfxTgenFunc {};
enum GSgfxTgenSrc {};

struct BlendState {
    u8 pad[0xbc];
};

struct MenuSpriteVal2 {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s32 res;
};

struct WorldMapFlagData {
    u8 pad0[4];
    u32 flag;
    u8 pad8[0x1c];
};

#define U8_AT(o) (*(u8*)((u8*)this + (o)))
#define U32_AT(o) (*(u32*)((u8*)this + (o)))
#define U8_AT_L(l, o) (*(u8*)((u8*)(l) + (o)))
#define U32_AT_L(l, o) (*(u32*)((u8*)(l) + (o)))

class GSgfxLayer {
public:
    void cunitChannelGen(u8 chan, GSgfxCunitAlpha alpha, GSgfxCunitSrc src0, GSgfxCunitSrc src1, u32 lights,
                         GSgfxLight** light, GSgfxLightType lightType, GSgfxDiffuseFunc diffuse);
    void tgenFunc(u8 index, GSgfxTgenFunc func, GSgfxTgenSrc src, GSmtx* mtx, bool normalize, GSmtx* post);
    void beginSurface(u16 count);
    void endSurface();
    void setRenderStateAndSelect(GSgfxVF* vf);

    inline void mark(u32 sum, u32 off, u32 bit)
    {
        U32_AT(off) |= bit;
        U32_AT(0x16a8) |= sum;
        U32_AT(off + 0xb8) |= bit;
        U32_AT(0x1760) |= sum;
    }

    u8 pad0[0xdb8];
    u8 padDb8;
    u8 pad1[0x1644 - 0xdb9];
    s32 blendOp;
    s32 blendSrc;
    s32 blendDst;
    s32 blendLogic;
    u8 pad_1654[2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 zUpdate;
    u8 pad_1659[3];
    u8 zEnable;
    u8 pad_165d[3];
    s32 zFunc;
    u8 pad_1664[0x16a8 - 0x1664];
    u32 dirty16a8;
    u8 pad_16ac[0x173c - 0x16ac];
    u32 dirty173c;
    GStexture* tex1740;
    u8 pad_1744[0x17f4 - 0x1744];
    u32 dirty17f4;
    GStexture* tex17f8;
    u8 pad_17fc[0x1818 - 0x17fc];
    BlendState blendTable[2];
    BlendState* curBlend;
    s32 curBlendIdx;
    u32 primType;
};

extern "C" {
double sin(double);
double cos(double);
f32 timeGetLastFrameSec(void);
s32 winSpriteGetLayerID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
GSgfxLayer* GSgfxLayerFindByID(s32 id);
void* menuSpriteBiosGetPtr(u32 id);
MenuSpriteVal2* menuSpriteBiosGetValPtr(void* sprite);
void* menuItemBiosGetPtr(s32 menuID, s32 index);
void* GSresGetResourceAllGroup(u32 id);
u16 GStextureGetXsize(void* tex);
u16 GStextureGetYsize(void* tex);
f32 GSlerpGetLinearInterpolationFloat(f32 a, f32 b, f32 t);
GSgfxVF* GSgfxVFGetPredef(s32 id);
void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on);
void winSeqSetMenu(s32 menuID, u32 id);
u32 GSmsgGetRect(s32 msg);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
u16 esabaGetPokemonID(s32 index);
s32 esabaGetEsaNum(s32 index);
s32 esabaGetDigestRate(void);
u32 GSflagGet(u32 id);
s32 menuOpen(s32 menuID, s32);
void menuClose(s32 menuID);
void menuCloseSync(s32 menuID, s32);
struct SearcherKeyInfo {
    u8 pad0[4];
    u16 buttons;
};
SearcherKeyInfo* windowGetKeyInfo(void);
extern WorldMapFlagData* worldmapXD_data;
extern u32* esabadata_number;
}

static void _animMojiCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id);
static void _animCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id);
static void _updateTimer(u16 id);
static void _esaPrintMsg(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u32 msg);
static void _esaNumSet(tagSPRITE_WORK* sp, u16 meter);
static u8 _getWorldMapFlag(u16 id);
static void _esaMonInit(void);
static void _menuClose(s32 id);
static f32 _gettLastTime(void);

extern "C" {
s32 _esaMeterIndex0[10] = {0x198, 0x199, 0x19A, 0x19B, 0x19C, 0x19D, 0x19E, 0x19F, 0x1A0, 0x1A1};
s32 _esaMeterIndex1[10] = {0x1A2, 0x1A3, 0x1A4, 0x1A7, 0x1A5, 0x1A6, 0x1A8, 0x1A9, 0x1AA, 0x1AB};
s32 _esaMeterIndex2[10] = {0x1AC, 0x1AD, 0x1AE, 0x1AF, 0x1B0, 0x1B1, 0x1B2, 0x1B3, 0x1B4, 0x1B5};
s32* _esaMeterIndex[3] = {_esaMeterIndex0, _esaMeterIndex1, _esaMeterIndex2};
}

static f32 _esaTimer[3];
static f32 _maxscale[2] = {0.5f, 1.5f};
static f32 _startangle;

static f32 _gettLastTime(void)
{
    return timeGetLastFrameSec();
}

static void _menuClose(s32 id)
{
    menuClose(id);
    menuCloseSync(id, 1);
}

extern "C" {
void menuPdaSearcher(void)
{
    menuOpen(0x77, 0);
    do {
    } while (menuOpen(0x6d, 1) >= 0);
    _menuClose(0x6d);
    _menuClose(0x77);
}
}

extern "C" {
void fn_80042BDC(tagWINDOW_WORK* w)
{
    if (w != 0) {
        if (windowGetKeyInfo()->buttons & 0x20) {
            w->done = 1;
            w->cancel = 1;
        }
    }
}
}

static void _esaMonInit(void)
{
    u32 i;
    for (i = 0; i < *esabadata_number; i++) {
        _esaTimer[i] = 0.0f;
    }
}

static u8 _getWorldMapFlag(u16 id)
{
    u16 ids[3] = {0xF, 0x10, 0x11};
    if (id > 2) {
        return 0;
    }
    return GSflagGet(*(u32*)((u8*)worldmapXD_data + ids[id] * 0x24 + 4)) != 0;
}

extern "C" {
s32 menuPdaSearcherCtrl(tagWINDOW_WORK* w)
{
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x132);
            w->seqSet = 1;
            _esaMonInit();
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x136);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}
}

static void _esaNumSet(tagSPRITE_WORK* sp, u16 meter)
{
    s32* tbl = _esaMeterIndex[meter];
    s32 num = esabaGetEsaNum(meter);
    if (num == 0) {
        winSpriteSetDisp(sp, false);
    }
    s32 i;
    for (i = 0; i < 10; i++) {
        if (sp->id == tbl[i]) {
            break;
        }
    }
    if (num >= i + 1) {
        winSpriteSetDisp(sp, true);
    } else {
        winSpriteSetDisp(sp, false);
    }
}

static void _esaPrintMsg(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u32 msg)
{
    u32 col = w->alpha | 0xFFFFFF00;
    u32 rect = GSmsgGetRect(msg);
    GSmsgPrintRect(w->layer, (s16)((u32)(sp->w - (rect >> 16)) >> 1), 0, sp->w, sp->h, col, msg);
}

static void _updateTimer(u16 id)
{
    f32 rate = (f32)esabaGetDigestRate();
    f32 dt = _gettLastTime();
    f32 two = 2.0f * dt;
    _esaTimer[id] += 3.1415927f * two / (rate / 100.0f);
    if (_esaTimer[id] > 6.2831855f) {
        _esaTimer[id] -= 6.2831855f;
    }
}

static void _animCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id)
{
    _updateTimer(id);
    f32 s;
    f32 t = _esaTimer[id] / 6.2831855f;
    f32 v = 1.0f - t;
    v = 255.0f * v;
    if (v >= 255.0f) {
        v = 255.0f;
    }
    sp->alpha = (u8)(w->alpha * (u8)(s32)v / 255);
    f32 scale = GSlerpGetLinearInterpolationFloat(_maxscale[0], _maxscale[1], t);
    GSgfxLayer* layer = GSgfxLayerFindByID(winSpriteGetLayerID(w, sp));
    void* spr = menuSpriteBiosGetPtr(0x2de);
    MenuSpriteVal2* val = menuSpriteBiosGetValPtr(spr);
    void* tex = GSresGetResourceAllGroup(val->res);
    u16 xs = GStextureGetXsize(tex);
    u32 ys = GStextureGetYsize(tex);
    f32 radius = scale * (f32)(val->w / 2);
    f32 angle = _startangle;
    menuItemBiosGetPtr(w->menuID, sp->id);
    f32 tc[4][3];
    f32 u0 = (f32)val->x / (f32)xs;
    s8 rf_t = val->y;
    f32 v0 = (f32)rf_t / (f32)ys;
    f32 v1 = (f32)(val->y + val->h) / (f32)ys;
    f32 u1 = (f32)(val->w + val->x) / (f32)xs;
    tc[3][1] = tc[2][1] = v1;
    tc[0][0] = tc[3][0] = u0;
    tc[1][0] = tc[2][0] = u1;
    tc[0][1] = tc[1][1] = v0;
    f32 cx = (f32)(val->w / 2);
    f32 cy = (f32)(val->h / 2);

    layer->colorUpdate = 1;
    layer->alphaUpdate = 0;
    layer->zUpdate = 0;
    layer->mark(0x40, 0x170c, 4);
    layer->zEnable = 0;
    layer->zFunc = 7;
    layer->mark(0x40, 0x170c, 8);
    if (layer->curBlendIdx != 1) {
        layer->curBlendIdx = 1;
        layer->curBlend = &layer->blendTable[layer->curBlendIdx];
    }
    layer->blendOp = 1;
    layer->blendSrc = 4;
    layer->blendDst = 5;
    layer->blendLogic = 5;
    layer->mark(0x40, 0x170c, 1);
    U8_AT_L(layer, 0xc70) = 1;
    layer->mark(1, 0x16ac, 1);
    layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
    layer->padDb8 = 1;
    layer->mark(4, 0x16bc, 1);
    layer->cunitChannelGen(0, (GSgfxCunitAlpha)2, (GSgfxCunitSrc)1, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2,
                           (GSgfxDiffuseFunc)0);
    U8_AT_L(layer, 0xeac) = 1;
    layer->mark(8, 0x16cc, 1);
    U32_AT_L(layer, 0xeb0) = 0;
    U32_AT_L(layer, 0xeb4) = 0;
    U32_AT_L(layer, 0xeb8) = 4;
    layer->mark(8, 0x16d0, 1);
    U32_AT_L(layer, 0x1170) = 0;
    U32_AT_L(layer, 0x1174) = 0;
    U32_AT_L(layer, 0x1178) = 0;
    U8_AT_L(layer, 0x117c) = 1;
    U32_AT_L(layer, 0x1180) = 0;
    layer->mark(8, 0x16dc, 1);
    U32_AT_L(layer, 0xf70) = 0xF;
    U32_AT_L(layer, 0xf74) = 0xF;
    U32_AT_L(layer, 0xf78) = 0xF;
    U32_AT_L(layer, 0xf7c) = 8;
    layer->mark(8, 0x16d4, 1);
    U32_AT_L(layer, 0x12b0) = 0;
    U32_AT_L(layer, 0x12b4) = 0;
    U32_AT_L(layer, 0x12b8) = 0;
    U8_AT_L(layer, 0x12bc) = 1;
    U32_AT_L(layer, 0x12c0) = 0;
    layer->mark(8, 0x16e0, 1);
    U32_AT_L(layer, 0x1070) = 7;
    U32_AT_L(layer, 0x1074) = 5;
    U32_AT_L(layer, 0x1078) = 4;
    U32_AT_L(layer, 0x107c) = 7;
    layer->mark(8, 0x16d8, 1);
    layer->primType = 0x80;
    GSgfxVF* vf = GSgfxVFGetPredef(7);
    layer->primType = 0xa0;
    layer->setRenderStateAndSelect(vf);
    if (layer->tex1740 != (GStexture*)tex || layer->tex17f8 != (GStexture*)tex || ((u8*)tex)[7] != 0) {
        layer->tex1740 = (GStexture*)tex;
        layer->dirty173c |= 1;
        layer->tex17f8 = (GStexture*)tex;
        layer->dirty17f4 |= 1;
    }
    layer->beginSurface(4);
    for (s32 i = 0; i < 4; i++) {
        s = (f32)sin(angle);
        f32 c = (f32)cos(angle);
        f32 tu = tc[i][0];
        f32 tv = tc[i][1];
        angle += 1.5707964f;
        GXWGFifo.s16 = (s16)(radius * s + cx);
        GXWGFifo.s16 = (s16)(radius * c + cy);
        GXWGFifo.u8 = sp->alpha;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.f32 = tu;
        GXWGFifo.f32 = tv;
    }
    layer->endSurface();
}

static void _animMojiCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp, u16 id)
{
    f32 c = (f32)cos(_esaTimer[id]);
    f32 s = 1.0f + c;
    f32 v = 0.5f * s;
    v = 255.0f * v;
    if (v >= 255.0f) {
        v = 255.0f;
    }
    sp->alpha = (u8)(w->alpha * (u8)(s32)v / 255);
}

extern "C" {
s32 menuPdaSeatcherHook(tagWINDOW_WORK* w, tagSPRITE_WORK* sp)
{
    switch (sp->id) {
    case 0x1B7:
        if (_getWorldMapFlag(0)) {
            _esaPrintMsg(w, sp, 0x3c17);
        }
        break;
    case 0x1B8:
        if (_getWorldMapFlag(1)) {
            _esaPrintMsg(w, sp, 0x3c18);
        }
        break;
    case 0x1B9:
        if (_getWorldMapFlag(2)) {
            _esaPrintMsg(w, sp, 0x3c19);
        }
        break;
    case 0x1BA:
        if (_getWorldMapFlag(0)) {
            _esaPrintMsg(w, sp, 0x3c17);
        }
        break;
    case 0x1BB:
        if (_getWorldMapFlag(1)) {
            _esaPrintMsg(w, sp, 0x3c18);
        }
        break;
    case 0x1BC:
        if (_getWorldMapFlag(2)) {
            _esaPrintMsg(w, sp, 0x3c19);
        }
        break;
    case 0x1BD:
        if (_getWorldMapFlag(0)) {
            winSpriteSetDisp(sp, true);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x1BE:
        if (_getWorldMapFlag(1)) {
            winSpriteSetDisp(sp, true);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x1BF:
        if (_getWorldMapFlag(2)) {
            winSpriteSetDisp(sp, true);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x1C0:
        if (_getWorldMapFlag(0) && esabaGetPokemonID(0) != 0) {
            winSpriteSetDisp(sp, true);
            _animCursor(w, sp, 0);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x1C1:
        if (_getWorldMapFlag(1) && esabaGetPokemonID(1) != 0) {
            winSpriteSetDisp(sp, true);
            _animCursor(w, sp, 1);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x1C2:
        if (_getWorldMapFlag(2) && esabaGetPokemonID(2) != 0) {
            winSpriteSetDisp(sp, true);
            _animCursor(w, sp, 2);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x1C3:
        if (_getWorldMapFlag(0) && esabaGetPokemonID(0) != 0) {
            winSpriteSetDisp(sp, true);
            _animMojiCursor(w, sp, 0);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x1C4:
        if (_getWorldMapFlag(1) && esabaGetPokemonID(1) != 0) {
            winSpriteSetDisp(sp, true);
            _animMojiCursor(w, sp, 1);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x1C5:
        if (_getWorldMapFlag(2) && esabaGetPokemonID(2) != 0) {
            winSpriteSetDisp(sp, true);
            _animMojiCursor(w, sp, 2);
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x198: case 0x199: case 0x19A: case 0x19B: case 0x19C:
    case 0x19D: case 0x19E: case 0x19F: case 0x1A0: case 0x1A1:
        _esaNumSet(sp, 0);
        break;
    case 0x1A2: case 0x1A3: case 0x1A4: case 0x1A5: case 0x1A6:
    case 0x1A7: case 0x1A8: case 0x1A9: case 0x1AA: case 0x1AB:
        _esaNumSet(sp, 1);
        break;
    case 0x1AC: case 0x1AD: case 0x1AE: case 0x1AF: case 0x1B0:
    case 0x1B1: case 0x1B2: case 0x1B3: case 0x1B4: case 0x1B5:
        _esaNumSet(sp, 2);
        break;
    }
    return 0;
}
}
