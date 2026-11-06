#include <dolphin/types.h>
#include <game/gcptr.h>
#include <dolphin/gx/GXVert.h>

#pragma peephole off

struct tagWINDOW_WORK {
    u8 unk0[0xC];
    void* slotC;
    void* slot10;
    void* slot14;
    u8 pad18[0xC];
    void* slot24;
    void* slot28;
    void* slot2C;
    u8 pad30[0x38];
    void* slot68;
    void* slot6C;
    void* slot70;
    void* slot74;
    void* slot78;
    void* slot7C;
    void* slot80;
    void* slot84;
    u8 pad88[0xB];
    u8 alpha;
};

struct tagSPRITE_WORK {
    void* unk0;
    s8 flags;
    u8 unk5[0x7];
    void* slotC;
    u8 pad10[0x38];
    void* slot48;
    void* slot4C;
    u8 pad50[0x17];
    u8 alpha;
};

struct MenuItem {
    u8 unk0[0xA];
    s16 width;
    s16 height;
};

struct GSgfxVF;

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

};

extern "C" {
f32 timeGetLastFrameSec(void);
s32 winSpriteGetLayerID(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
GSgfxLayer* GSgfxLayerFindByID(GCsptr id);
MenuItem* menuItemBiosGetPtr(s32 menuID, s32 itemID);
GSgfxVF* GSgfxVFGetPredef(s32 id);
u8 menuSubAnimAlpha(tagWINDOW_WORK* window);
void winSpriteSetDisp(tagSPRITE_WORK* sprite, s32 disp);

void menuPdaSubCalcAlpha(f32* alpha, s32 count, s32 selected) {
    f32 step = 255.0f * timeGetLastFrameSec();
    f32 fadeIn = step / 0.1f;
    f32 fadeOut = step / 0.2f;
    f32* p = alpha;
    s32 i;

    for (i = 0; i < count; p++, i++) {
        if (selected == i) {
            if (*p < 255.0f) {
                *p += fadeIn;
                if (*p > 255.0f) {
                    *p = 255.0f;
                }
            }
        } else {
            if (*p > 0.0f) {
                *p -= fadeOut;
                if (*p < 0.0f) {
                    *p = 0.0f;
                }
            }
        }
    }
}

void menuPdaSubInitAlpha(f32* alpha, s32 count, s32 selected) {
    s32 i;
    for (i = 0; i < count; alpha++, i++) {
        if (selected == i) {
            *alpha = 255.0f;
        } else {
            *alpha = 0.0f;
        }
    }
}

void menuPdaSubCalcPositon(f32* pos, f32 target, f32 speed) {
    f32 cur;
    f32 diff;
    f32 step = 30.0f * (speed * timeGetLastFrameSec());
    cur = *pos;

    diff = target - cur;
    if ((diff > 0.0f ? diff : -diff) >= 100.0f) {
        step *= 30.0f;
    }
    if (diff < 0.0f) {
        step = -step;
    }
    *pos = cur + step;
    diff = target - *pos;
    if ((diff > 0.0f ? diff : -diff) <= (step > 0.0f ? step : -step)) {
        *pos = target;
    }
}

void menuPdaSubScrollBar(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, s32 menuID, s32 itemID, u32 color, s32 total,
                         s32 visible, s16* top) {
    GSgfxLayer* layer = GSgfxLayerFindByID(winSpriteGetLayerID(window, sprite));
    MenuItem* item;
    f32 scale;
    f32 y0;
    f32 y1;

    if (layer == NULL) {
        return;
    }
    if (total > visible) {
        sprite->flags |= 2;
    } else {
        sprite->flags &= ~2;
        return;
    }

    item = menuItemBiosGetPtr(menuID, itemID);
    scale = (f32)item->height / (f32)total;
    y0 = scale * (f32)*top;
    y1 = scale * (f32)(*top + visible);

    if ((*(s32*)&layer->curPass) != 1) {
        (*(s32*)&layer->curPass) = 1;
        layer->curFifo = &layer->passes[layer->curPass];
    }
    (*(s32*)&layer->hw.blend[0]) = 1;
    (*(s32*)&layer->hw.blend[1]) = 4;
    (*(s32*)&layer->hw.blend[2]) = 5;
    (*(s32*)&layer->hw.blend[3]) = 5;
    (*(u32*)&layer->dirty[0].pe) |= 1;
    (*(u32*)&layer->dirty[0].groups) |= 0x40;
    (*(u32*)&layer->dirty[1].pe) |= 1;
    (*(u32*)&layer->dirty[1].groups) |= 0x40;
    (*(u32*)&layer->unk1998) = 0x80;
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(3));
    layer->beginSurface(4);
    GXWGFifo.s16 = 1;
    GXWGFifo.s16 = y0;
    GXWGFifo.u32 = color | window->alpha;
    GXWGFifo.s16 = (s16)(item->width - 2);
    GXWGFifo.s16 = y0;
    GXWGFifo.u32 = color | window->alpha;
    GXWGFifo.s16 = (s16)(item->width - 2);
    GXWGFifo.s16 = y1;
    GXWGFifo.u32 = color | window->alpha;
    GXWGFifo.s16 = 1;
    GXWGFifo.s16 = y1;
    GXWGFifo.u32 = color | window->alpha;
    layer->endSurface();
}

void menuPdaSubCheckUpDownCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, s16* top, s32 total, s32 visible,
                                 u8 isUp) {
    sprite->alpha = menuSubAnimAlpha(window);
    if (isUp) {
        if (total <= visible || *top == 0) {
            winSpriteSetDisp(sprite, 0);
        } else {
            winSpriteSetDisp(sprite, 1);
        }
    } else {
        if (total <= visible || visible == total - *top) {
            winSpriteSetDisp(sprite, 0);
        } else {
            winSpriteSetDisp(sprite, 1);
        }
    }
}

}
