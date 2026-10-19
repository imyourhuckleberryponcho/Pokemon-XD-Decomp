#include <dolphin/types.h>
#include <libc/stdarg.h>

// Menu files were built without the peephole optimizer.
#pragma peephole off
#pragma pool_strings off

struct tagWINDOW_WORK;

// One entry of the menu item table (MENU_ITEM).
struct MENU_ITEM_dd_ {
    u8 selectable : 1;
    u8 last : 1;
    u8 spriteType : 2;
    u8 low : 4;
    u8 top2 : 2;
    u8 rest1 : 6;
    u8 alpha;
    u8 pad3;
    s16 spriteID;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 cursorSprite;
    void* msg;
    void* callback;
    s16 next;
};
typedef MENU_ITEM_dd_ MENU_ITEM;

struct MENU_DATA {
    u8 f0a : 3;
    u8 f0b : 2;
    u8 f0c : 1;
    u8 f0d : 1;
    u8 f0e : 1;
    u8 f1a : 4;
    u8 f1b : 3;
    u8 f1c : 1;
    u8 f2a : 3;
    u8 f2b : 5;
    u8 pad3;
    u8 cursorID;
    u8 pad5;
    s16 firstItem;
    s16 x;
    s16 y;
    u8 pad_c[8];
    void (*callback)(tagWINDOW_WORK*);
};

struct MENU_SPRITE {
    u16 last : 1;
    u16 fit : 1;
    u16 type : 2;
    u16 seq : 12;
    u8 pad2;
    s8 offX;
    s8 offY;
    u8 alpha;
    u8 pad6[0x3e];
    s16 next;
};

struct MENU_SPRITE_VAL {
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    u32 tex;
};

// Window sprite node (a winSprite list entry).
struct tagSPRITE_WORK {
    u8 pad0[4];
    u8 kind;
    u8 flags;
    s16 id;
    u32 tex;
    u8 seq[0x3c];
    u32 callback;
    u32 msg;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    u32 tex2;
    s16 u;
    s16 v;
    s16 uw;
    s16 uh;
    union {
        u32 color;
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        } c;
    };
    f32 sx;
    f32 sy;
    f32 f70;
    u8 b74;
    u8 b75;
    u8 b76;
    u8 pad77;
};

struct KeyInfo {
    u16 on;
    u16 up;
    u16 trg;
    u16 rep;
    u16 rel;
    u8 pad_a[0x10];
};

struct WinSys {
    u16 count;
    u8 pad_2[6];
    s32 activeID;
    tagWINDOW_WORK* pool;
    tagWINDOW_WORK* head;
    KeyInfo key;
    KeyInfo port[4];
    u8 pad_96[10];
};

union Cursor {
    u32 raw;
    struct {
        s16 x;
        s16 y;
    } p;
};

struct tagWINDOW_WORK {
    u8 used;
    u8 state;
    s8 seqSet;
    u8 pad3;
    s32 menuID;
    u8 pad8;
    s8 priority;
    u8 closeFlag;
    u8 enablePort;
    tagWINDOW_WORK* parent;
    tagWINDOW_WORK* next;
    tagWINDOW_WORK* prev;
    u8 flag18;
    u8 itemNum;
    u8 flags1a;
    u8 closeFlags;
    s32 layerID;
    u8 flags20;
    u8 pad_21[3];
    tagSPRITE_WORK* itemSprites;
    tagSPRITE_WORK* cursorSprites;
    u8 pad_2c[0x3c];
    u32 params[8];
    u8 pad_88[4];
    s16 offX;
    s16 offY;
    s32 pad_90;
    f32 f94;
    f32 f98;
    s16 cursorX;
    s16 cursor;
    u8 pad_a0[4];
    u8 pad_a4;
    u8 pad_a5;
    u8 pad_a6[2];
    u8 freeWork[0x10];
    void* alloc;
};

typedef tagWINDOW_WORK WINDOW_WORK;

extern "C" {
void* GSmemAlloc(s32);
void GSmemFree(void*);
void* memset(void*, int, u32);
MENU_SPRITE* menuSpriteBiosGetPtr(u32);
MENU_SPRITE_VAL* menuSpriteBiosGetValPtr(MENU_SPRITE*);
MENU_DATA* menuDataBiosGetPtr(s32);
MENU_ITEM* menuItemBiosGetPtr(s32 menuID, s16 idx);
s32 menuItemBiosGetLayerID(s32);
s32 floorGetMenuLayerID(void);
void spriteGetOffset(s32, s16*, s16*);
void winSpriteDraw(void*, void*);
tagSPRITE_WORK* winSpriteAdd(void*);
void winSpriteRelease(void*);
void winSpriteInit(void);
void winSetSequence(void*, u32);
void GSlogWrite(const char*, ...);
u32 GSthreadGetCurrentThread(void);
void GSthreadSwitch(void);
s32 menuGetCursorItemID(s32);
void menuPlaySe(s32, s32);
Cursor cursorBiosGetPos(u32);
u8 menuGetEnablePort(void);
u32 GSmsgGetRect(void*);
KeyInfo* windowGetKeyInfo(void);
KeyInfo* windowGetKeyInfo2(void);
tagWINDOW_WORK* windowSearchID(s32);
s32 windowGetActiveID(void);
void windowDrawSprite2(s16, s16, s16, s16, u32, void*, u16, u32, s32);
}

WinSys winSysWork;
WinSys winSysWork2;

static s32 _windowCreateItemSprite(tagWINDOW_WORK* w);
static void _windowSetCloseFlag(tagWINDOW_WORK* w, bool b);
static bool _windowCheckParent(tagWINDOW_WORK* w, tagWINDOW_WORK* p);
static s32 _windowDeleteWork(tagWINDOW_WORK* w);
static s32 _winInsertWork(tagWINDOW_WORK* w, s8 pri);
static tagWINDOW_WORK* _winGetNewWork(void);
static void _winCalcWindowSize(long menuID, const MENU_ITEM* item, short* outW, short* outH);

extern "C" {

void* windowGetAllocPtr(tagWINDOW_WORK* w)
{
    if (w != 0) {
        return w->alloc;
    }
    return 0;
}

void* windowAllocMemory(tagWINDOW_WORK* w, s32 size)
{
    if (w == 0) {
        return 0;
    }
    if (w->alloc != 0) {
        GSmemFree(w->alloc);
        w->alloc = 0;
    }
    if (size <= 0) {
        return 0;
    }
    w->alloc = GSmemAlloc(size);
    if (w->alloc == 0) {
        return 0;
    }
    if (w->alloc == 0) {
        return 0;
    }
    return w->alloc;
}

void* windowGetFreeWork(tagWINDOW_WORK* w)
{
    if (w != 0) {
        return w->freeWork;
    }
    return 0;
}

void windowSetParam(tagWINDOW_WORK* w, u32 idx, u32 value)
{
    if (w == 0) {
        return;
    }
    w->params[idx] = value;
}

u32 windowGetParam(tagWINDOW_WORK* w, u32 idx)
{
    if (w != 0) {
        return w->params[idx];
    }
    return 0;
}

void windowDrawSprite(s16 x, s16 y, void* ctx, u16 key, u32 flags, s32 layer)
{
    if (key != 0) {
        MENU_SPRITE_VAL* val = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(key));
        windowDrawSprite2(x, y, val->w, val->h, -1, ctx, key, flags, layer);
    }
}

void windowDrawSpriteCursor(s16 x, s16 y, u32 color0, void* ctx, u16 key, u32 flags, s32 layer, f32* off,
                            u32 color1)
{
    tagSPRITE_WORK sp;
    tagWINDOW_WORK ctxbuf;
    tagSPRITE_WORK* spp = &sp;
    s32 i = 0;
    MENU_SPRITE_VAL* val;
    MENU_SPRITE* info;

    info = menuSpriteBiosGetPtr(key);
    while (true) {
        val = menuSpriteBiosGetValPtr(info);
        memset(spp, 0, 0x78);
        spp->kind = 7;
        if (i == 0) {
            spp->color = color0;
        } else {
            spp->color = color1;
        }
        spp->sx = 1.0f;
        spp->sy = 1.0f;
        if (layer == floorGetMenuLayerID()) {
            spp->b74 = 1;
        }
        if (info->type == 1) {
            spp->flags |= 1;
            spp->tex2 = val->tex;
        } else if (info->type == 2) {
            spp->flags |= 2;
            spp->tex = val->tex;
        } else if (info->type == 3) {
            spp->flags |= 0x10;
            spp->tex = val->tex;
        }
        if (i == 0) {
            spp->x = (s16)(x + info->offX);
            spp->y = (s16)(y + info->offY);
        } else {
            spp->x = (s16)(x + (info->offX + (s32)off[0]));
            spp->y = (s16)(y + (info->offY + (s32)off[1]));
        }
        spp->w = val->w;
        spp->h = val->h;
        spp->u = val->u;
        spp->v = val->v;
        spp->uw = val->w;
        spp->uh = val->h;
        spp->c.a = spp->c.a * info->alpha / 255;
        if (flags & 1) {
            spp->w = -spp->w;
        }
        if (flags & 2) {
            spp->h = -spp->h;
        }
        if (ctx == 0) {
            ctx = &ctxbuf;
            memset(ctx, 0, 0xbc);
            spriteGetOffset(layer, &ctxbuf.offX, &ctxbuf.offY);
            ctxbuf.layerID = layer;
            ctxbuf.pad_90 = -1;
        }
        winSpriteDraw(ctx, spp);
        if (info->last) {
            break;
        }
        i++;
        info = menuSpriteBiosGetPtr(info->next);
    }
}

void windowDrawSprite2(s16 x, s16 y, s16 w, s16 h, u32 color, void* ctx, u16 key, u32 flags, s32 layer)
{
    tagSPRITE_WORK sp;
    tagWINDOW_WORK ctxbuf;
    tagSPRITE_WORK* spp = &sp;
    MENU_SPRITE_VAL* val;
    MENU_SPRITE* info;

    info = menuSpriteBiosGetPtr(key);
    while (true) {
        val = menuSpriteBiosGetValPtr(info);
        memset(spp, 0, 0x78);
        spp->kind = 7;
        spp->color = color;
        spp->sx = 1.0f;
        spp->sy = 1.0f;
        if (layer == floorGetMenuLayerID()) {
            spp->b74 = 1;
        }
        if (info->type == 1) {
            spp->flags |= 1;
            spp->tex2 = val->tex;
        } else if (info->type == 2) {
            spp->flags |= 2;
            spp->tex = val->tex;
        } else if (info->type == 3) {
            spp->flags |= 0x10;
            spp->tex = val->tex;
        }
        spp->x = (s16)(x + info->offX);
        spp->y = (s16)(y + info->offY);
        spp->w = w;
        spp->h = h;
        spp->u = val->u;
        spp->v = val->v;
        spp->uw = val->w;
        spp->uh = val->h;
        spp->c.a = spp->c.a * info->alpha / 255;
        if (flags & 1) {
            spp->w = -w;
        }
        if (flags & 2) {
            spp->h = -spp->h;
        }
        if (ctx == 0) {
            ctx = &ctxbuf;
            memset(ctx, 0, 0xbc);
            spriteGetOffset(layer, &ctxbuf.offX, &ctxbuf.offY);
            ctxbuf.layerID = layer;
            ctxbuf.pad_90 = -1;
        }
        winSpriteDraw(ctx, spp);
        if (info->last) {
            break;
        }
        info = menuSpriteBiosGetPtr(info->next);
    }
}

void windowDrawSprite3(s16 x, s16 y, s16 w, s16 h, u32 color, void* ctx, u16 key, s16 du, s16 dv, s16 uw, s16 uh,
                       u32 flags, s32 layer)
{
    tagSPRITE_WORK sp;
    tagWINDOW_WORK ctxbuf;
    tagSPRITE_WORK* spp = &sp;
    MENU_SPRITE_VAL* val;
    MENU_SPRITE* info;

    info = menuSpriteBiosGetPtr(key);
    while (true) {
        val = menuSpriteBiosGetValPtr(info);
        memset(spp, 0, 0x78);
        spp->kind = 7;
        spp->color = color;
        spp->sx = 1.0f;
        spp->sy = 1.0f;
        if (layer == floorGetMenuLayerID()) {
            spp->b74 = 1;
        }
        if (info->type == 1) {
            spp->flags |= 1;
            spp->tex2 = val->tex;
        } else if (info->type == 2) {
            spp->flags |= 2;
            spp->tex = val->tex;
        } else if (info->type == 3) {
            spp->flags |= 0x10;
            spp->tex = val->tex;
        }
        spp->x = (s16)(x + info->offX);
        spp->y = (s16)(y + info->offY);
        spp->w = w;
        spp->h = h;
        spp->u = (s16)(val->u + du);
        spp->v = (s16)(val->v + dv);
        spp->uw = uw;
        spp->uh = uh;
        spp->c.a = spp->c.a * info->alpha / 255;
        if (flags & 1) {
            spp->w = -w;
        }
        if (flags & 2) {
            spp->h = -spp->h;
        }
        if (ctx == 0) {
            ctx = &ctxbuf;
            memset(ctx, 0, 0xbc);
            spriteGetOffset(layer, &ctxbuf.offX, &ctxbuf.offY);
            ctxbuf.layerID = layer;
            ctxbuf.pad_90 = -1;
        }
        winSpriteDraw(ctx, spp);
        if (info->last) {
            break;
        }
        info = menuSpriteBiosGetPtr(info->next);
    }
}

#pragma dont_inline on
tagSPRITE_WORK* windowGetCursorToItem(tagWINDOW_WORK* w)
{
    MENU_DATA* md = menuDataBiosGetPtr(w->menuID);
    MENU_ITEM* item = menuItemBiosGetPtr(w->menuID, md->firstItem);
    s32 idx = 0;
    while (true) {
        if (item->selectable) {
            if (w->cursor == idx) {
                return (tagSPRITE_WORK*)item;
            }
            idx++;
        }
        if (item->last) {
            break;
        }
        item = menuItemBiosGetPtr(w->menuID, item->next);
    }
    return 0;
}
#pragma dont_inline reset

s32 windowGetValue(s32 id)
{
    tagWINDOW_WORK* w = windowSearchID(id);
    s32 r;
    if (w != 0) {
        if (w->pad_a5 != 0) {
            r = -1;
        } else {
            MENU_DATA* md = menuDataBiosGetPtr(w->menuID);
            if (md != 0) {
                switch (md->f0b) {
                case 0:
                    r = 0;
                    break;
                case 1:
                    r = w->cursorX + w->cursor;
                    break;
                case 2:
                    r = *(s32*)w->pad_88;
                    break;
                case 3:
                    r = menuGetCursorItemID(id);
                    break;
                }
            } else {
                r = w->cursorX + w->cursor;
            }
        }
    } else {
        r = -1;
    }
    return r;
}

Cursor windowGetCursor(s32 id)
{
    Cursor def = {0};
    Cursor ret;
    tagWINDOW_WORK* w = windowSearchID(id);
    if (w != 0) {
        ret = *(Cursor*)&w->cursorX;
    } else {
        ret = def;
    }
    return ret;
}

s32 windowCheckCursor(s32 id, u8 wait)
{
    while (true) {
        tagWINDOW_WORK* w = windowSearchID(id);
        if (w == 0) {
            GSlogWrite("%s(0x%08x)  ウィンドウが存在しない\n", __FUNCTION__, id);
            return 0;
        }
        if (w->pad_a4 != 0) {
            return 0;
        }
        if (w->pad_a5 != 0) {
            return 0;
        }
        if (wait == 0) {
            break;
        }
        if (GSthreadGetCurrentThread() == 0) {
            GSlogWrite("%s(0x%08x)  スレッドから呼ぶようにしてください\n", __FUNCTION__, id);
            break;
        }
        GSthreadSwitch();
    }
    return 1;
}

#pragma dont_inline on
s32 windowGetActiveID(void)
{
    return winSysWork.activeID;
}
#pragma dont_inline reset

tagSPRITE_WORK* windowSearchItemID(tagWINDOW_WORK* w, u32 id)
{
    tagSPRITE_WORK* sp;
    if (w == 0) {
        return 0;
    }
    sp = w->itemSprites;
    u16 key = id;
    while (sp != 0) {
        if (sp->id == key) {
            return sp;
        }
        sp = *(tagSPRITE_WORK**)sp;
    }
    return 0;
}

#pragma dont_inline on
tagWINDOW_WORK* windowSearchID(s32 id)
{
    tagWINDOW_WORK* w;
    if (id <= 0) {
        return 0;
    }
    w = winSysWork.head;
    while (w != 0) {
        if (w->menuID == id) {
            return w;
        }
        w = w->next;
    }
    return 0;
}
#pragma dont_inline reset

void windowCloseMain(tagWINDOW_WORK* w)
{
    MENU_DATA* md = menuDataBiosGetPtr(w->menuID);
    if (md->callback != 0) {
        w->state = 5;
        md->callback(w);
    }
    _windowDeleteWork(w);
}

s32 windowClose(tagWINDOW_WORK* w, u32 flags)
{
    tagWINDOW_WORK* d;
    tagWINDOW_WORK* c;
    tagWINDOW_WORK* a;
    bool found = false;
    bool setClose = (flags & 4) != 0;
    u32 chain = flags & 2;

    if (chain == 0) {
        for (c = winSysWork.head; c != 0; c = c->next) {
            if (_windowCheckParent(c, w)) {
                _windowSetCloseFlag(c, setClose);
            }
        }
    }
    if ((flags & 1) == 0 && w != 0) {
        _windowSetCloseFlag(w, setClose);
        if (chain != 0) {
            for (c = winSysWork.head; c != 0; c = c->next) {
                if (c->parent == w) {
                    c->parent = w->parent;
                }
            }
        }
    }
    a = windowSearchID(windowGetActiveID());
    while (a != 0) {
        if (a->closeFlag != 0 || a->flag18 != 0) {
            for (d = winSysWork.head; d != 0; d = d->next) {
                if (d->closeFlag == 0 && d->flag18 == 0 && _windowCheckParent(d, a->parent)) {
                    found = true;
                    winSysWork.activeID = d->menuID;
                }
            }
            if (found) {
                break;
            }
        } else {
            winSysWork.activeID = a->menuID;
            break;
        }
        a = a->parent;
    }
    if (a == 0) {
        winSysWork.activeID = 0;
    }
    return 0;
}

}

static void _windowSetCloseFlag(tagWINDOW_WORK* w, bool b)
{
    if (b == 0 || menuDataBiosGetPtr(w->menuID)->f0e == 0) {
        w->closeFlag = 1;
    }
}

static s32 _windowCreateItemSprite(tagWINDOW_WORK* w)
{
    s16 id = menuDataBiosGetPtr(w->menuID)->firstItem;
    MENU_ITEM* item = menuItemBiosGetPtr(w->menuID, id);
    tagSPRITE_WORK* sp;
    MENU_SPRITE* ms;
    MENU_SPRITE_VAL* val;
    s16 cw;
    s16 ch;

    winSpriteRelease(&w->itemSprites);
    _winCalcWindowSize(w->menuID, item, &cw, &ch);
    while (true) {
        item = menuItemBiosGetPtr(w->menuID, (s32)id);
        sp = (tagSPRITE_WORK*)winSpriteAdd(&w->itemSprites);
        if (sp == 0) {
            winSpriteRelease(&w->itemSprites);
            return 1;
        }
        sp->id = id;
        sp->x = item->x;
        sp->y = item->y;
        sp->w = item->w;
        sp->h = item->h;
        sp->c.a = item->alpha;
        sp->b75 = item->spriteType;
        sp->b74 = item->low;
        sp->b76 = item->top2;
        if (item->spriteID != 0) {
            ms = menuSpriteBiosGetPtr(item->spriteID);
            val = menuSpriteBiosGetValPtr(ms);
            if (ms->type == 1) {
                sp->flags |= 1;
                sp->tex2 = val->tex;
            } else if (ms->type == 2) {
                sp->flags |= 2;
                sp->tex = val->tex;
            } else if (ms->type == 3) {
                sp->flags |= 0x10;
                sp->tex = val->tex;
            }
            sp->u = val->u;
            sp->v = val->v;
            sp->uw = val->w;
            sp->uh = val->h;
            sp->c.a = sp->c.a * ms->alpha / 255;
            if (ms->fit) {
                sp->w = cw;
                sp->h = ch;
            }
            if (ms->seq != 0) {
                winSetSequence(sp->seq, ms->seq);
            }
        }
        sp->msg = (u32)item->msg;
        if (item->callback != 0) {
            sp->flags |= 8;
            sp->callback = (u32)item->callback;
        }
        if (item->last) {
            break;
        }
        id = item->next;
    }
    return 0;
}

extern "C" {

void windowCreateCursorSprite(tagWINDOW_WORK* w)
{
    MENU_DATA* md = menuDataBiosGetPtr(w->menuID);
    tagSPRITE_WORK* cur;
    MENU_ITEM* sel = (MENU_ITEM*)windowGetCursorToItem(w);
    MENU_SPRITE* ms;
    s32 i;
    MENU_SPRITE_VAL* val;
    tagSPRITE_WORK* sp;

    if (sel != 0) {
        winSpriteRelease(&w->cursorSprites);
        if (sel->cursorSprite != 0) {
            ms = menuSpriteBiosGetPtr(sel->cursorSprite);
            i = 0;
            while (true) {
                val = menuSpriteBiosGetValPtr(ms);
                sp = (tagSPRITE_WORK*)winSpriteAdd(&w->cursorSprites);
                if (sp == 0) {
                    winSpriteRelease(&w->cursorSprites);
                    break;
                }
                if (ms->type == 1) {
                    sp->flags |= 1;
                    sp->tex2 = val->tex;
                } else if (ms->type == 2) {
                    sp->flags |= 2;
                    sp->tex = val->tex;
                } else if (ms->type == 3) {
                    sp->flags |= 0x10;
                    sp->tex = val->tex;
                }
                sp->id = md->firstItem;
                sp->x = sel->x + ms->offX;
                sp->y = sel->y + ms->offY;
                sp->w = val->w;
                sp->h = val->h;
                sp->u = val->u;
                sp->v = val->v;
                sp->uw = val->w;
                sp->uh = val->h;
                sp->c.a = ms->alpha;
                if (ms->seq != 0) {
                    winSetSequence(sp->seq, ms->seq);
                }
                if (i != 0) {
                    winSetSequence(sp->seq, 0x141);
                }
                if (ms->last) {
                    break;
                }
                ms = menuSpriteBiosGetPtr(ms->next);
                i++;
            }
        }
    }
}

tagWINDOW_WORK* windowOpen(s32* cursorOut, s32 menuID, s32 parentID, u32 closeFlags, s32 num, va_list args)
{
    tagWINDOW_WORK* w;
    tagWINDOW_WORK* parent;
    MENU_DATA* md;
    MENU_ITEM* item;
    s32 layer;
    s8 pri;
    tagWINDOW_WORK* p;
    s32 i;

    parent = windowSearchID(parentID);
    if (parent != 0) {
        layer = parent->layerID;
    } else {
        layer = menuItemBiosGetLayerID(menuID);
    }
    if (layer == -1) {
        return 0;
    }
    md = menuDataBiosGetPtr(menuID);
    w = windowSearchID(menuID);
    if (w == 0) {
        if (md->f0d != 0) {
            pri = 100;
        } else if ((closeFlags & 2) != 0) {
            pri = 100;
        } else {
            if (parentID == 0) {
                parentID = windowGetActiveID();
            }
            parent = windowSearchID(parentID);
            if (parent != 0) {
                pri = parent->priority + 1;
            } else {
                pri = 0;
            }
            if (pri > 100) {
                pri = 100;
            }
        }
        w = _winGetNewWork();
        if (w == 0) {
            return 0;
        }
        w->state = 0;
        w->menuID = menuID;
        w->priority = pri;
        w->flags1a = md->f1b;
        w->parent = parent;
        w->offX = md->x;
        w->offY = md->y;
        w->layerID = layer;
        w->flags20 = md->f0a;
        item = menuItemBiosGetPtr(menuID, md->firstItem);
        while (true) {
            if (item->selectable) {
                w->itemNum++;
            }
            if (item->last) {
                break;
            }
            item = menuItemBiosGetPtr(menuID, item->next);
        }
        _windowCreateItemSprite(w);
        _winInsertWork(w, pri);
        menuPlaySe(menuID, 4);
    } else {
        w->pad_a4 = 0;
        w->pad_a5 = 0;
        w->state = 0;
        w->seqSet = 1;
    }
    if (cursorOut == 0) {
        if (md->cursorID != 0) {
            Cursor c = cursorBiosGetPos(md->cursorID);
            w->cursorX = c.p.x;
            w->cursor = c.p.y;
        }
    } else {
        w->cursorX = 0;
        w->cursor = (s8)*cursorOut;
    }
    windowCreateCursorSprite(w);
    w->enablePort = menuGetEnablePort();
    w->closeFlags = closeFlags;
    if (num > 8) {
        num = 8;
    }
    p = w;
    for (i = 0; i < num; i++) {
        p->params[0] = va_arg(args, u32);
        p = (tagWINDOW_WORK*)((u8*)p + 4);
    }
    if (md->f2a == 0) {
        w->pad_a4 = 1;
    } else if ((closeFlags & 4) == 0) {
        winSysWork.activeID = menuID;
    }
    if (winSysWork.activeID != menuID) {
        w->flag18 = 1;
    }
    if (md->callback != 0) {
        md->callback(w);
    }
    if (w->seqSet != 0) {
        w->closeFlag = 0;
        w->state = 2;
        w->seqSet = 0;
    }
    return w;
}

}

static bool _windowCheckParent(tagWINDOW_WORK* w, tagWINDOW_WORK* p)
{
    if (w == p) {
        return false;
    }
    while (w != 0) {
        w = w->parent;
        if (w == p) {
            return true;
        }
    }
    return false;
}

static s32 _windowDeleteWork(tagWINDOW_WORK* w)
{
    if (w == 0) {
        return 0;
    }
    if (w->prev == 0) {
        winSysWork.head = w->next;
    } else {
        w->prev->next = w->next;
    }
    if (w->next != 0) {
        w->next->prev = w->prev;
    }
    winSpriteRelease(&w->itemSprites);
    winSpriteRelease(&w->cursorSprites);
    if (w->alloc != 0) {
        if (w->alloc != 0) {
            GSmemFree(w->alloc);
            w->alloc = 0;
        }
    }
    w->used = 0;
    w->menuID = 0;
    return 0;
}

static s32 _winInsertWork(tagWINDOW_WORK* w, s8 pri)
{
    tagWINDOW_WORK* c;
    if (winSysWork.head == 0) {
        winSysWork.head = w;
    } else {
        c = winSysWork.head;
        while (true) {
            if (c->priority > pri) {
                w->prev = c->prev;
                w->next = c;
                if (c->prev == 0) {
                    winSysWork.head = w;
                } else {
                    c->prev->next = w;
                }
                c->prev = w;
                break;
            }
            if (c->next == 0) {
                c->next = w;
                w->prev = c;
                w->next = 0;
                break;
            }
            c = c->next;
        }
    }
    return 0;
}

static tagWINDOW_WORK* _winGetNewWork(void)
{
    tagWINDOW_WORK* w = winSysWork.pool;
    u16 n = winSysWork.count;
    s32 i;
    for (i = n; i > 0; i--) {
        if ((s8)w->used == 0) {
            memset(w, 0, 0xbc);
            w->used = 7;
            w->f94 = 1.0f;
            w->f98 = 1.0f;
            w->pad_90 = -1;
            return w;
        }
        w++;
    }
    GSlogWrite("Error!! _winGetNewWork() [ワークの確保に失敗]\n");
    return 0;
}

static void _winCalcWindowSize(long menuID, const MENU_ITEM* item, short* outW, short* outH)
{
    s32 minX = 0x280;
    s32 minY = 0x1e0;
    s32 maxX = 0;
    s32 maxY = 0;
    u32 rect;
    s16 rw;
    s16 rh;

    *outW = 0;
    *outH = 0;
    while (true) {
        menuSpriteBiosGetPtr(item->spriteID);
        if (item->msg != 0) {
            rect = GSmsgGetRect(item->msg);
        } else {
            rect = 0;
        }
        rw = rect >> 16;
        rh = (u16)rect;
        if (minX > item->x) {
            minX = item->x;
        }
        if (maxX < item->x + item->w) {
            maxX = item->x + item->w;
        }
        if (maxX < item->x + rw) {
            maxX = item->x + rw;
        }
        if (minY > item->y) {
            minY = item->y;
        }
        if (maxY < item->y + item->h) {
            maxY = item->y + item->h;
        }
        if (maxY < item->y + rh) {
            maxY = item->y + rh;
        }
        if (item->last) {
            break;
        }
        item = menuItemBiosGetPtr(menuID, item->next);
    }
    *outW = maxX - minX;
    *outH = maxY - minY;
}

extern "C" {

void windowInit(u16 count)
{
    s32 size;
    void* p;
    memset(&winSysWork, 0, 0xa0);
    memset(&winSysWork2, 0, 0xa0);
    size = count * 0xbc;
    p = GSmemAlloc(size);
    winSysWork.pool = (tagWINDOW_WORK*)p;
    if (p == 0) {
        GSlogWrite("windowInitの初期化に失敗しました\n");
    } else {
        winSysWork.count = count;
        memset(p, 0, size);
        winSpriteInit();
    }
}

KeyInfo* windowGetPortKeyInfo2(u8 ports)
{
    static KeyInfo key;
    u8 bits[4] = {1, 2, 4, 8};
    s32 i;
    memset(&key, 0, 0x1a);
    for (i = 0; i < 4; i++) {
        KeyInfo* k = &winSysWork2.port[i];
        if (ports & bits[i]) {
            key.on |= k->on;
            key.up |= k->up;
            key.trg |= k->trg;
            key.rep |= k->rep;
            key.rel |= k->rel;
        }
    }
    return &key;
}

KeyInfo* windowGetPortKeyInfo(u8 ports)
{
    static KeyInfo key;
    u8 bits[4] = {1, 2, 4, 8};
    s32 i;
    memset(&key, 0, 0x1a);
    for (i = 0; i < 4; i++) {
        KeyInfo* k = &winSysWork.port[i];
        if (ports & bits[i]) {
            key.on |= k->on;
            key.up |= k->up;
            key.trg |= k->trg;
            key.rep |= k->rep;
            key.rel |= k->rel;
        }
    }
    return &key;
}

u32 windowGetKeyTrg(void)
{
    u32 r = windowGetKeyInfo()->trg;
    u32 r2;
    if ((windowGetKeyInfo()->on & 0xf) != 0) {
        r2 = 0;
    } else {
        r2 = windowGetKeyInfo2()->trg;
    }
    r |= r2;
    return r;
}

u16 windowGetKeyOn(void)
{
    u16 r = windowGetKeyInfo()->on;
    u16 r2;
    if ((r & 0xf) != 0) {
        r2 = 0;
    } else {
        r2 = windowGetKeyInfo2()->on;
    }
    r |= r2;
    return r;
}

u32 windowGetKeyRepeat(void)
{
    u32 r = windowGetKeyInfo()->rep;
    u32 r2;
    if ((windowGetKeyInfo()->on & 0xf) != 0) {
        r2 = 0;
    } else {
        r2 = windowGetKeyInfo2()->rep;
    }
    r |= r2;
    return r;
}

KeyInfo* windowGetKeyInfo2(void)
{
    return &winSysWork2.key;
}

KeyInfo* windowGetKeyInfo(void)
{
    return &winSysWork.key;
}

}
