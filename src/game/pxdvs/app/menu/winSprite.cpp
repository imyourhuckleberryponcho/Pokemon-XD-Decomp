#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>

#pragma peephole off
#pragma pool_strings off

struct GSgfxVF;
struct GStexture {
    u8 pad0[7];
    u8 flag;
};

struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
};

struct Quat4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

class GSgfxLayer {
public:
    u8 pad0[0x28];
    s32 layerID;
    u8 pad2c[0xD34 - 0x2C];
    u8 colorCount;
    u8 padD35[3];
    u32 colorMode;
    u8 padD3C[0x1644 - 0xD3C];
    s32 s1644;
    s32 s1648;
    s32 s164C;
    s32 s1650;
    u8 pad1654[0x1664 - 0x1654];
    s32 s1664;
    s32 s1668;
    s32 s166C;
    u8 b1670;
    u8 b1671;
    u8 b1672;
    u8 pad1673;
    u8 pad1674[0x16A8 - 0x1674];
    u32 flagsA;
    u32 flagsB;
    u8 pad16B0[0x170C - 0x16B0];
    u32 f170C;
    u8 pad1710[0x173C - 0x1710];
    u32 f173C;
    GStexture* tex1740;
    u8 pad1744[0x1760 - 0x1744];
    u32 flagsC;
    u32 flagsD;
    u8 pad1768[0x17C4 - 0x1768];
    u32 f17C4;
    u8 pad17C8[0x17F4 - 0x17C8];
    u32 f17F4;
    GStexture* tex17F8;
    u8 pad17FC[0x1818 - 0x17FC];
    u8 surfaces[2][0xBC];
    void* curSurface;
    s32 curSurfaceIdx;
    u32 primitive;
    u32 f199C;
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

struct SEQ_CMD {
    u8 rel : 1;
    u8 ease : 2;
    u8 keep : 2;
    u8 rest : 3;
    u8 type;
    s16 arg;
    s32 a;
    s32 b;
};

struct tagSEQ_WORK {
    SEQ_CMD* cmds;
    s16 idx;
    s16 delay;
    u8 posMode;
    u8 colMode;
    u8 scaleMode;
    u8 loopActive;
    s16 sx;
    s16 sy;
    s16 ex;
    s16 ey;
    s16 pframe;
    s16 pdur;
    u8 scol[4];
    u8 ecol[4];
    s16 cframe;
    s16 cdur;
    f32 ssx;
    f32 ssy;
    f32 esx;
    f32 esy;
    s16 sframe;
    s16 sdur;
    s16 loopCount;
    u8 enabled;
    u8 pad3b;
};

struct SEQ_WORK_COMMON {
    s16 x;
    s16 y;
    u8 color[4];
    s16 baseX;
    s16 baseY;
    f32 sx;
    f32 sy;
    u32 tex;
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    s8 flags;
    u8 pad21[3];
};

struct tagSPRITE_WORK {
    tagSPRITE_WORK* next;
    s8 kind;
    u8 flags;
    s16 id;
    u32 tex;
    tagSEQ_WORK seq;
    void* callback;
    void* msg;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    u32 tex2;
    s16 u;
    s16 v;
    s16 uw;
    s16 uh;
    u8 color[4];
    f32 sx;
    f32 sy;
    f32 rot;
    u8 b74;
    u8 b75;
    u8 b76;
    u8 pad77;
};

struct tagWINDOW_WORK {
    s8 used;
    s8 state;
    u8 pad2[2];
    s32 menuID;
    u8 pad8[0x14];
    s32 layerID;
    u8 pad20[4];
    tagSPRITE_WORK* itemSprites;
    tagSPRITE_WORK* cursorSprites;
    tagSEQ_WORK seq;
    u8 pad_68[0x24];
    s16 offX;
    s16 offY;
    u8 color[4];
    u8 pad_94[0xa];
    s16 cursor;
    u8 pad_a0[2];
    s16 cursorPrev;
    u8 pad_a4[0x18];
};

struct MENU_DATA {
    u8 f0a : 3;
    u8 f0b : 5;
    u8 pad[5];
    s16 firstItem;
    s16 x;
    s16 y;
};

struct MENU_ITEM {
    u8 flags0;
    u8 flags1;
    u8 alpha;
    u8 pad3;
    s16 spriteID;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
};

struct MENU_SPRITE_VAL {
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    u32 tex;
};

extern "C" {
void* memset(void*, int, u32);
void* GSmemAlloc(s32);
void GSlogWrite(const char*, ...);
s32 timeGetLastFrameTime(void);
void* menuSeqBiosGetPtr(u32);
MENU_DATA* menuDataBiosGetPtr(s32);
MENU_ITEM* menuItemBiosGetPtr(s32, s16);
void* menuSpriteBiosGetPtr(u32);
MENU_SPRITE_VAL* menuSpriteBiosGetValPtr(void*);
tagWINDOW_WORK* windowSearchID(s32);
s32 windowGetActiveID(void);
s32 dbgMenuGetLayerID(void);
s32 floorGetMenuLayerID(void);
s32 menuBiosGetCursorSize(tagWINDOW_WORK*);
GSgfxLayer* GSgfxLayerFindByID(s32);
void spriteSetOffset(s32, s16, s16);
void spriteSetEnv(s32);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void menuSubDrawSimpleWindow(s32, s32, s32, s32, s32);
void menuSubDrawNormalWindow2(s32, s32, s32, s32, s32, u8);
void menuSubDrawMsgWindow2(s32, s32, s32, s32, s32, u8, u8);
void menuSubDrawCursorBack(s32, s32, s32, s32, s32, u8, u8);
void menuSubDrawCursorBackAnimeOnOff(s32, s32, s32, s32, s32, u8, u8, u8);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, void*);
void FlashSystemPlay(u32);
void FlashSystemDraw(u32, tagWINDOW_WORK*, tagSPRITE_WORK*);
void* GSresGetResourceAllGroup(u32);
u16 GStextureGetXsize(GStexture*);
u16 GStextureGetYsize(GStexture*);
void C_QUATRotAxisRad(Quat4*, const Vec3f*, f32);
void GSvecTransformQuat(Vec3f*, const Quat4*, Vec3f*);
f64 sqrt(f64);
void winSetSequence(tagSEQ_WORK*, u32);
void winSpriteDrawTexture(tagWINDOW_WORK*, tagSPRITE_WORK*);
extern Vec3f yAxisVector;
}

static tagSPRITE_WORK* _spriteWork;

static void _spriteSetAlphaMode(GSgfxLayer* l, u8 mode);
static void _winSeqMoveSub(SEQ_WORK_COMMON* c, tagSEQ_WORK* s);
static void _winSeqMoveMenu(tagWINDOW_WORK* w);

extern "C" {

s32 winSpriteGetLayerID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp)
{
    MENU_DATA* md = menuDataBiosGetPtr(w->menuID);
    if (w->layerID == dbgMenuGetLayerID()) {
        return dbgMenuGetLayerID();
    }
    if (md->f0a == 3) {
        s32 l = dbgMenuGetLayerID();
        if (w->layerID != l) {
            w->layerID = l;
        }
        return l;
    }
    if (sp->b74 == 0) {
        return 7;
    }
    return floorGetMenuLayerID();
}

void winSpriteInit(void)
{
    void* p = GSmemAlloc(0xEA60);
    _spriteWork = (tagSPRITE_WORK*)p;
    if (p != 0) {
        memset(p, 0, 0xEA60);
    }
}

tagSPRITE_WORK* winSpriteAdd(tagSPRITE_WORK** head)
{
    tagSPRITE_WORK* sp;
    s32 i;
    tagSPRITE_WORK* p;
    if (head == 0) {
        return 0;
    }
    sp = _spriteWork;
    for (i = 500; i > 0; i--) {
        if (sp->kind == 0) {
            memset(sp, 0, 0x78);
            p = (tagSPRITE_WORK*)head;
            sp->kind = 7;
            sp->sx = 1.0f;
            sp->sy = 1.0f;
            *(s32*)sp->color = -1;
            while (p->next != 0) {
                p = p->next;
            }
            p->next = sp;
            return sp;
        }
        sp++;
    }
    GSlogWrite("Error!! winSpriteAdd() [スプライトワーク不足]\n");
    return 0;
}

void winSpriteRelease(tagSPRITE_WORK* head)
{
    tagSPRITE_WORK* p;
    if (head == 0) {
        return;
    }
    p = head;
    while (p->next != 0) {
        p->next->kind = 0;
        p = p->next;
    }
    head->next = 0;
}

void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on)
{
    if (sp == 0) {
        return;
    }
    if (on) {
        sp->kind |= 2;
    } else {
        sp->kind &= ~2;
    }
}

bool winSpriteGetDisp(tagSPRITE_WORK* sp)
{
    if (sp == 0) {
        return false;
    }
    return (sp->kind & 2) != 0;
}

}

static void _spriteSetAlphaMode(GSgfxLayer* l, u8 mode)
{
    switch (mode) {
    case 0:
        l->s1664 = 7;
        l->b1670 = 0;
        l->s1668 = 0;
        l->s166C = 7;
        l->b1671 = 0;
        l->b1672 = 1;
        l->f170C |= 0x10;
        l->flagsA |= 0x40;
        l->f17C4 |= 0x10;
        l->flagsC |= 0x40;
        if (l->curSurfaceIdx != 1) {
            l->curSurfaceIdx = 1;
            l->curSurface = l->surfaces[l->curSurfaceIdx];
        }
        l->s1644 = 1;
        l->s1648 = 4;
        l->s164C = 5;
        l->s1650 = 5;
        l->f170C |= 1;
        l->flagsA |= 0x40;
        l->f17C4 |= 1;
        l->flagsC |= 0x40;
        break;
    case 1:
        l->s1664 = 4;
        l->b1670 = 0;
        l->s1668 = 1;
        l->s166C = 0;
        l->b1671 = 0;
        l->b1672 = 0;
        l->f170C |= 0x10;
        l->flagsA |= 0x40;
        l->f17C4 |= 0x10;
        l->flagsC |= 0x40;
        if (l->curSurfaceIdx != 1) {
            l->curSurfaceIdx = 1;
            l->curSurface = l->surfaces[l->curSurfaceIdx];
        }
        l->s1644 = 1;
        l->s1648 = 2;
        l->s164C = 0;
        l->s1650 = 5;
        l->f170C |= 1;
        l->flagsA |= 0x40;
        l->f17C4 |= 1;
        l->flagsC |= 0x40;
        break;
    case 2:
        l->s1664 = 7;
        l->b1670 = 0;
        l->s1668 = 0;
        l->s166C = 7;
        l->b1671 = 0;
        l->b1672 = 1;
        l->f170C |= 0x10;
        l->flagsA |= 0x40;
        l->f17C4 |= 0x10;
        l->flagsC |= 0x40;
        if (l->curSurfaceIdx != 1) {
            l->curSurfaceIdx = 1;
            l->curSurface = l->surfaces[l->curSurfaceIdx];
        }
        l->s1644 = 1;
        l->s1648 = 4;
        l->s164C = 1;
        l->s1650 = 5;
        l->f170C |= 1;
        l->flagsA |= 0x40;
        l->f17C4 |= 1;
        l->flagsC |= 0x40;
        break;
    }
}

extern "C" {

void winAnimeCursor(tagWINDOW_WORK* w, tagSPRITE_WORK* sp)
{
    menuBiosGetCursorSize(w);
    if (w->cursorPrev != w->cursor) {
        winSetSequence(&sp->seq, 0x141);
    }
    if (w->state == 3) {
        winSetSequence(&sp->seq, 0);
    }
}

static inline void wsPos(s16 x, s16 y);
static inline void wsCol(u8 r, u8 g, u8 b, u8 a);

void winSpriteDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp)
{
    u8 b;
    u8 a;
    u32 color;
    GSgfxLayer* gfx;
    s32 layer;
    u8 g;
    u8 r;

    GSgfxLayerFindByID(w->layerID);
    layer = winSpriteGetLayerID(w, sp);
    gfx = GSgfxLayerFindByID(layer);
    _spriteSetAlphaMode(gfx, sp->b75);
    if (sp->flags & 8) {
        spriteSetOffset(layer, w->offX + sp->x, w->offY + sp->y);
        spriteSetEnv(layer);
        ((void (*)(tagWINDOW_WORK*, tagSPRITE_WORK*))sp->callback)(w, sp);
        spriteSetOffset(layer, w->offX, w->offY);
        spriteSetEnv(layer);
        _spriteSetAlphaMode(gfx, sp->b75);
    } else {
        spriteSetEnv(layer);
    }
    if (!winSpriteGetDisp(sp)) {
        return;
    }
    r = sp->color[0] * w->color[0] / 255;
    g = sp->color[1] * w->color[1] / 255;
    b = sp->color[2] * w->color[2] / 255;
    a = sp->color[3] * w->color[3] / 255;
    color = (r << 24) | (g << 16) | (b << 8) | a;
    if (a == 0) {
        return;
    }
    if (sp->flags & 1) {
        menuSpriteBiosGetPtr(menuItemBiosGetPtr(w->menuID, sp->id)->spriteID);
        winSpriteDrawTexture(w, sp);
    }
    if (sp->flags & 2) {
        switch ((u32)sp->tex - 0x10000) {
        case 0:
            gfx->primitive = 0x90;
            gfx->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
            gfx->beginSurface(3);
            wsPos(sp->x, sp->y);
            wsCol(r, g, b, a);
            wsPos(sp->x + sp->u, sp->y + sp->v);
            wsCol(r, g, b, a);
            wsPos(sp->x + sp->w, sp->y + sp->h);
            wsCol(r, g, b, a);
            gfx->endSurface();
            break;
        case 1:
            menuSubDrawSimpleWindow(gfx->layerID, sp->x, sp->y, sp->w, sp->h);
            break;
        case 4:
            menuSubDrawNormalWindow2(gfx->layerID, sp->x, sp->y, sp->w, sp->h, a);
            break;
        case 5:
            menuSubDrawMsgWindow2(gfx->layerID, sp->x, sp->y, sp->w, sp->h, a, 1);
            break;
        case 6: {
            MENU_ITEM* item = menuItemBiosGetPtr(w->menuID, sp->id);
            tagWINDOW_WORK* active = windowSearchID(windowGetActiveID());
            if (item->spriteID == 0xbd) {
                if (w == active) {
                    menuSubDrawCursorBack(gfx->layerID, sp->x, sp->y, item->w, item->h, a, 0);
                } else {
                    menuSubDrawCursorBackAnimeOnOff(gfx->layerID, sp->x, sp->y, item->w, item->h, a, 0, 0);
                }
            } else {
                menuSubDrawCursorBackAnimeOnOff(gfx->layerID, sp->x, sp->y, item->w, item->h, a, 0, 0);
            }
            break;
        }
        case 7: {
            MENU_ITEM* item = menuItemBiosGetPtr(w->menuID, sp->id);
            tagWINDOW_WORK* active = windowSearchID(windowGetActiveID());
            if (item->spriteID == 0xc3) {
                if (w == active) {
                    menuSubDrawCursorBack(gfx->layerID, sp->x, sp->y, item->w, item->h, a, 1);
                } else {
                    menuSubDrawCursorBackAnimeOnOff(gfx->layerID, sp->x, sp->y, item->w, item->h, a, 1, 0);
                }
            } else {
                menuSubDrawCursorBackAnimeOnOff(gfx->layerID, sp->x, sp->y, item->w, item->h, a, 1, 0);
            }
            break;
        }
        case 2: {
            u8 r2 = (u16)sp->u * r / 255;
            u8 g2 = (u16)sp->v * g / 255;
            u8 b2 = (u16)sp->uw * b / 255;
            gfx->primitive = 0x98;
            gfx->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
            gfx->beginSurface(4);
            wsPos(sp->x, sp->y);
            wsCol(r2, g2, b2, a);
            wsPos(sp->x + sp->w, sp->y);
            wsCol(r2, g2, b2, a);
            wsPos(sp->x, sp->y + sp->h);
            wsCol(r2, g2, b2, a);
            wsPos(sp->x + sp->w, sp->y + sp->h);
            wsCol(r2, g2, b2, a);
            gfx->endSurface();
            break;
        }
        case 8: {
            u8 r2 = (u16)sp->u * r / 255;
            u8 g2 = (u16)sp->v * g / 255;
            u8 b2 = (u16)sp->uw * b / 255;
            gfx->colorCount = 6;
            gfx->colorMode = 0;
            gfx->flagsB |= 4;
            gfx->flagsA |= 1;
            gfx->flagsD |= 4;
            gfx->flagsC |= 1;
            gfx->primitive = 0xb0;
            gfx->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
            gfx->beginSurface(5);
            wsPos(sp->x, sp->y);
            wsCol(r2, g2, b2, a);
            wsPos(sp->x + sp->w, sp->y);
            wsCol(r2, g2, b2, a);
            wsPos(sp->x + sp->w, sp->y + sp->h);
            wsCol(r2, g2, b2, a);
            wsPos(sp->x, sp->y + sp->h);
            wsCol(r2, g2, b2, a);
            wsPos(sp->x, sp->y);
            wsCol(r2, g2, b2, a);
            gfx->endSurface();
            break;
        }
        case 3: {
            u8 r2 = (u16)sp->u * r / 255;
            u8 g2 = (u16)sp->v * g / 255;
            u8 b2 = (u16)sp->uw * b / 255;
            gfx->colorCount = 6;
            gfx->colorMode = 0;
            gfx->flagsB |= 4;
            gfx->flagsA |= 1;
            gfx->flagsD |= 4;
            gfx->flagsC |= 1;
            gfx->primitive = 0xa8;
            gfx->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
            gfx->beginSurface(2);
            wsPos(sp->x, sp->y);
            wsCol(r2, g2, b2, a);
            wsPos(sp->w, sp->h);
            wsCol(r2, g2, b2, a);
            gfx->endSurface();
            break;
        }
        }
    }
    if (sp->msg != 0) {
        GSmsgPrintRect(layer, sp->x, sp->y, sp->w, sp->h, color, sp->msg);
    }
    if (sp->flags & 0x10) {
        menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(sp->tex2));
        FlashSystemPlay(sp->tex);
        FlashSystemDraw(sp->tex, w, sp);
    }
}

}

extern "C" {

static inline void wsPos(s16 x, s16 y)
{
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
}

static inline void wsCol(u8 r, u8 g, u8 b, u8 a)
{
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;
}

void winSpriteDrawTexture(tagWINDOW_WORK* w, tagSPRITE_WORK* sp)
{
    static f32 xy[8];
    static f32 st[8];
    static f32 cxy[2];
    GSgfxLayer* gfx = GSgfxLayerFindByID(winSpriteGetLayerID(w, sp));
    u8 r = sp->color[0] * w->color[0] / 255;
    u8 g = sp->color[1] * w->color[1] / 255;
    u8 b = sp->color[2] * w->color[2] / 255;
    u8 a = sp->color[3] * w->color[3] / 255;
    GStexture* tex = (GStexture*)GSresGetResourceAllGroup(sp->tex2);
    s16 left;
    s16 width;
    s16 top;
    s16 height;
    s16 px;
    s16 py;
    Quat4 q;
    Vec3f v;
    s32 i;

    if (tex != 0) {
        if (gfx->tex1740 != tex || gfx->tex17F8 != tex || tex->flag != 0) {
            gfx->tex1740 = tex;
            gfx->f173C |= 1;
            gfx->tex17F8 = tex;
            gfx->f17F4 |= 1;
        }
        switch (sp->b76) {
        case 0:
        default: {
            s32 aw = sp->w < 0 ? -sp->w : sp->w;
            if (sp->uw != aw) {
                if (sp->uw < 0) {
                    left = sp->u;
                    width = sp->uw < 0 ? -sp->uw : sp->uw;
                } else {
                    width = sp->uw - 2;
                    left = sp->u + 1;
                }
                if (width < 0) {
                    width = 0;
                }
            } else {
                left = sp->u;
                width = sp->uw;
            }
            {
                s32 ah = sp->h < 0 ? -sp->h : sp->h;
                if (sp->uh != ah) {
                    if (sp->uh < 0) {
                        top = sp->v;
                        height = sp->uh < 0 ? -sp->uh : sp->uh;
                    } else {
                        height = sp->uh - 2;
                        top = sp->v + 1;
                    }
                    if (height < 0) {
                        height = 0;
                    }
                } else {
                    top = sp->v;
                    height = sp->uh;
                }
            }
            break;
        }
        case 1:
        case 2:
        case 3:
            left = sp->u;
            width = sp->uw;
            top = sp->v;
            height = sp->uh;
            break;
        }
        st[0] = st[2] = (f32)left / (f32)GStextureGetXsize(tex);
        st[4] = st[6] = (f32)(left + width) / (f32)GStextureGetXsize(tex);
        st[1] = st[7] = (f32)(top + height) / (f32)GStextureGetYsize(tex);
        st[3] = st[5] = (f32)top / (f32)GStextureGetYsize(tex);
    } else {
        st[0] = st[2] = 0.0f;
        st[4] = st[6] = 1.0f;
        st[1] = st[7] = 1.0f;
        st[3] = st[5] = 0.0f;
    }
    switch (sp->b76) {
    case 0:
    default:
        px = sp->x;
        py = sp->y;
        width = sp->w < 0 ? -sp->w : sp->w;
        height = sp->h < 0 ? -sp->h : sp->h;
        break;
    case 1:
        px = sp->x + ((sp->w < 0 ? -sp->w : sp->w) - sp->uw) / 2;
        py = sp->y + ((sp->h < 0 ? -sp->h : sp->h) - sp->uh) / 2;
        break;
    case 2:
        px = sp->x;
        py = sp->y + ((sp->h < 0 ? -sp->h : sp->h) - sp->uh);
        break;
    case 3:
        px = sp->x + ((sp->w < 0 ? -sp->w : sp->w) - sp->uw);
        py = sp->y + ((sp->h < 0 ? -sp->h : sp->h) - sp->uh);
        break;
    }
    f32 half = 0.5f;
    cxy[0] = (f32)(s16)width * half + (f32)(s16)px;
    cxy[1] = (f32)(s16)height * half + (f32)(s16)py;
    if (sp->w < 0) {
        xy[0] = xy[2] = (f32)(px + width) - cxy[0];
        xy[4] = xy[6] = (f32)px - cxy[0];
    } else {
        xy[0] = xy[2] = (f32)px - cxy[0];
        xy[4] = xy[6] = (f32)(px + width) - cxy[0];
    }
    if (sp->h < 0) {
        xy[1] = xy[7] = (f32)py - cxy[1];
        xy[3] = xy[5] = (f32)(py + height) - cxy[1];
    } else {
        xy[1] = xy[7] = (f32)(py + height) - cxy[1];
        xy[3] = xy[5] = (f32)py - cxy[1];
    }
    if (sp->rot != 0.0f) {
        C_QUATRotAxisRad(&q, &yAxisVector, sp->rot);
    } else {
        q.x = 0.0f;
        q.y = 0.0f;
        q.z = 0.0f;
        q.w = 1.0f;
    }
    gfx->primitive = 0x80;
    gfx->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 1, 1, 4));
    gfx->beginSurface(4);
    for (i = 0; i < 4; i++) {
        v.x = xy[i * 2];
        v.y = 0.0f;
        v.z = xy[i * 2 + 1];
        GSvecTransformQuat(&v, &q, &v);
        xy[i * 2] = v.x * sp->sx;
        xy[i * 2 + 1] = v.z * sp->sy;
        GXWGFifo.s16 = cxy[0] + xy[i * 2];
        GXWGFifo.s16 = cxy[1] + xy[i * 2 + 1];
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        GXWGFifo.f32 = st[i * 2];
        GXWGFifo.f32 = st[i * 2 + 1];
    }
    gfx->endSurface();
}

void winSetSequence(tagSEQ_WORK* s, u32 id)
{
    if ((u16)id == 0) {
        s->cmds = 0;
        s->idx = 0;
    } else {
        memset(s, 0, 0x3c);
        s->cmds = (SEQ_CMD*)menuSeqBiosGetPtr((u16)id);
    }
}

void winSeqSetMenu(s32 menuID, u32 id)
{
    tagWINDOW_WORK* w = windowSearchID(menuID);
    if (w != 0) {
        winSetSequence(&w->seq, id);
        _winSeqMoveMenu(w);
    }
}

bool winSeqIsCheck(s32 menuID, u16 id)
{
    tagWINDOW_WORK* w = windowSearchID(menuID);
    if (w != 0 && w->seq.cmds == menuSeqBiosGetPtr(id)) {
        return true;
    }
    return false;
}

}

static void _winSeqMoveSub(SEQ_WORK_COMMON* c, tagSEQ_WORK* s)
{
    bool done = false;
    u32 i;
    s32 t = timeGetLastFrameTime();
    if (t > 2) {
        t = 2;
    }
    for (i = 0; i < t; i++) {
        if (s->cmds == 0) {
            break;
        }
        if (s->posMode != 0) {
            s->pframe++;
            switch (s->posMode) {
            case 1: {
                f32 f = (f32)s->pframe / (f32)s->pdur;
                c->x = f * (f32)(s->ex - s->sx) + (f32)s->sx;
                c->y = f * (f32)(s->ey - s->sy) + (f32)s->sy;
                break;
            }
            case 2: {
                f32 f = (f32)s->pframe * (f32)s->pframe / (f32)s->pdur / (f32)s->pdur;
                c->x = f * (f32)(s->ex - s->sx) + (f32)s->sx;
                c->y = f * (f32)(s->ey - s->sy) + (f32)s->sy;
                break;
            }
            case 3: {
                f32 f = sqrt((f64)s->pframe) / sqrt((f64)s->pdur);
                c->x = f * (f32)(s->ex - s->sx) + (f32)s->sx;
                c->y = f * (f32)(s->ey - s->sy) + (f32)s->sy;
                break;
            }
            }
            if (s->pframe >= s->pdur) {
                s->posMode = 0;
            }
        }
        if (s->colMode != 0) {
            s->cframe++;
            switch (s->colMode) {
            case 1: {
                f32 f = (f32)s->cframe / (f32)s->cdur;
                c->color[0] = f * (f32)(s->ecol[0] - s->scol[0]) + (f32)s->scol[0];
                c->color[1] = f * (f32)(s->ecol[1] - s->scol[1]) + (f32)s->scol[1];
                c->color[2] = f * (f32)(s->ecol[2] - s->scol[2]) + (f32)s->scol[2];
                c->color[3] = f * (f32)(s->ecol[3] - s->scol[3]) + (f32)s->scol[3];
                break;
            }
            }
            if (s->cframe >= s->cdur) {
                s->colMode = 0;
            }
        }
        if (s->scaleMode != 0) {
            s->sframe++;
            switch (s->scaleMode) {
            case 1: {
                f32 f = (f32)s->sframe / (f32)s->sdur;
                c->sx = f * (s->esx - s->ssx) + s->ssx;
                c->sy = f * (s->esy - s->ssy) + s->ssy;
                break;
            }
            }
            if (s->sframe >= s->sdur) {
                s->scaleMode = 0;
            }
        }
        while (true) {
            SEQ_CMD* cmd;
            if (s->delay > 0) {
                s->delay--;
                break;
            }
            cmd = &s->cmds[s->idx];
            switch (cmd->type) {
            case 0:
                s->cmds = 0;
                done = true;
                s->idx = 0;
                break;
            case 1:
                s->delay = cmd->arg;
                break;
            case 3:
            case 9:
                if (cmd->type == 9) {
                    s->ex = c->baseX;
                    s->ey = c->baseY;
                } else {
                    switch (cmd->rel) {
                    case 0:
                        s->ex = cmd->a;
                        s->ey = cmd->b;
                        break;
                    case 1:
                        s->ex = c->x + cmd->a;
                        s->ey = c->y + cmd->b;
                        break;
                    }
                }
                if (cmd->keep & 1) {
                    s->ex = c->x;
                }
                if (cmd->keep & 2) {
                    s->ey = c->y;
                }
                s->pdur = cmd->arg;
                if (s->pdur == 0) {
                    c->x = s->ex;
                    c->y = s->ey;
                    s->posMode = 0;
                } else {
                    s->sx = c->x;
                    s->sy = c->y;
                    s->pframe = 0;
                    switch (cmd->ease) {
                    case 0:
                        s->posMode = 1;
                        break;
                    case 1:
                        s->posMode = 2;
                        break;
                    case 2:
                        s->posMode = 3;
                        break;
                    case 3:
                        s->posMode = 1;
                        break;
                    }
                }
                break;
            case 7:
                s->scol[0] = c->color[0];
                s->scol[1] = c->color[1];
                s->scol[2] = c->color[2];
                s->scol[3] = c->color[3];
                s->ecol[0] = (u32)cmd->a >> 24;
                s->ecol[1] = ((u32)cmd->a >> 16) & 0xFF;
                s->ecol[2] = ((u32)cmd->a >> 8) & 0xFF;
                s->ecol[3] = cmd->a;
                s->cframe = 0;
                s->cdur = cmd->arg;
                s->colMode = 1;
                if (s->cdur == 0) {
                    c->color[0] = s->ecol[0];
                    c->color[1] = s->ecol[1];
                    c->color[2] = s->ecol[2];
                    c->color[3] = s->ecol[3];
                    s->colMode = 0;
                }
                break;
            case 6:
                s->ssx = c->sx;
                s->ssy = c->sy;
                s->esx = (f32)cmd->a / 100.0f;
                s->esy = (f32)cmd->b / 100.0f;
                s->sframe = 0;
                s->sdur = cmd->arg;
                s->scaleMode = 1;
                if (s->sdur == 0) {
                    c->sx = s->esx;
                    c->sy = s->esy;
                    s->scaleMode = 0;
                }
                break;
            case 2:
                if (cmd->a != 0) {
                    c->flags |= 2;
                } else {
                    c->flags &= ~2;
                }
                break;
            case 11:
                if (cmd->a != 0) {
                    s->enabled = 1;
                } else {
                    s->enabled = 0;
                }
                break;
            case 10:
                if (s->loopActive == 0) {
                    s->loopActive = 1;
                    s->loopCount = cmd->arg;
                }
                if (cmd->rel == 0) {
                    s->loopCount--;
                }
                if (s->loopCount < 0) {
                    s->loopCount = 0;
                    s->loopActive = 0;
                    break;
                }
                s->idx = cmd->a;
                continue;
            case 8: {
                MENU_SPRITE_VAL* val = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(cmd->a));
                c->tex = val->tex;
                c->u = val->u;
                c->v = val->v;
                c->w = val->w;
                c->h = val->h;
                break;
            }
            case 4:
            case 5:
                break;
            }
            if (done) {
                break;
            }
            s->idx++;
        }
    }
}

static void _winSeqMoveMenu(tagWINDOW_WORK* w)
{
    static SEQ_WORK_COMMON seqTemp;
    seqTemp.x = w->offX;
    seqTemp.y = w->offY;
    *(u32*)seqTemp.color = *(u32*)w->color;
    seqTemp.flags = w->used;
    seqTemp.baseX = menuDataBiosGetPtr(w->menuID)->x;
    seqTemp.baseY = menuDataBiosGetPtr(w->menuID)->y;
    _winSeqMoveSub(&seqTemp, &w->seq);
    w->offX = seqTemp.x;
    w->offY = seqTemp.y;
    *(u32*)w->color = *(u32*)seqTemp.color;
    w->used = seqTemp.flags;
}

static void _winSeqMoveSprite(s32 menuID, tagSPRITE_WORK* sp)
{
    static SEQ_WORK_COMMON seqTemp;
    seqTemp.x = sp->x;
    seqTemp.y = sp->y;
    *(u32*)seqTemp.color = *(u32*)sp->color;
    seqTemp.sx = sp->sx;
    seqTemp.sy = sp->sy;
    seqTemp.flags = sp->kind;
    seqTemp.tex = sp->tex2;
    seqTemp.u = sp->u;
    seqTemp.v = sp->v;
    seqTemp.w = sp->uw;
    seqTemp.h = sp->uh;
    seqTemp.baseX = menuItemBiosGetPtr(menuID, sp->id)->x;
    seqTemp.baseY = menuItemBiosGetPtr(menuID, sp->id)->y;
    _winSeqMoveSub(&seqTemp, &sp->seq);
    sp->x = seqTemp.x;
    sp->y = seqTemp.y;
    *(u32*)sp->color = *(u32*)seqTemp.color;
    sp->sx = seqTemp.sx;
    sp->sy = seqTemp.sy;
    sp->kind = seqTemp.flags;
    sp->tex2 = seqTemp.tex;
    sp->u = seqTemp.u;
    sp->v = seqTemp.v;
    sp->uw = seqTemp.w;
    sp->uh = seqTemp.h;
}

extern "C" {

void winSeqMoveMenu(tagWINDOW_WORK* w)
{
    tagSPRITE_WORK* sp;
    _winSeqMoveMenu(w);
    for (sp = w->itemSprites; sp != 0; sp = sp->next) {
        _winSeqMoveSprite(w->menuID, sp);
    }
    for (sp = w->cursorSprites; sp != 0; sp = sp->next) {
        _winSeqMoveSprite(w->menuID, sp);
    }
}

bool winSeqCheckMove(s32 menuID)
{
    tagWINDOW_WORK* w = windowSearchID(menuID);
    tagSPRITE_WORK* sp;
    if (w == 0) {
        return false;
    }
    if (w->seq.cmds != 0) {
        return true;
    }
    for (sp = w->itemSprites; sp != 0; sp = sp->next) {
        if (sp->seq.cmds != 0 && sp->seq.enabled == 0) {
            return true;
        }
    }
    return false;
}

}
