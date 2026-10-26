#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>

#pragma peephole off

struct tagWINDOW_WORK {
    u8 unk0[0x93];
    u8 alpha;
};

struct tagSPRITE_WORK {
    u8 unk0[4];
    s8 flags;
    u8 unk5[0x62];
    u8 alpha;
};

struct MenuItem {
    u8 unk0[0xA];
    s16 width;
    s16 height;
};

struct GSgfxVF;

class GSgfxLayer {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

    u8 unk0[0x1644];
    s32 unk1644;
    s32 unk1648;
    s32 unk164C;
    s32 unk1650;
    u8 unk1654[0x16A8 - 0x1654];
    u32 unk16A8;
    u8 unk16AC[0x170C - 0x16AC];
    u32 unk170C;
    u8 unk1710[0x1760 - 0x1710];
    u32 unk1760;
    u8 unk1764[0x17C4 - 0x1764];
    u32 unk17C4;
    u8 unk17C8[0x1818 - 0x17C8];
    u8 surfaces[2][0xBC];
    void* curSurface;
    s32 curSurfaceIdx;
    u32 unk1998;
};

extern "C" {
f32 timeGetLastFrameSec(void);
s32 winSpriteGetLayerID(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
GSgfxLayer* GSgfxLayerFindByID(s32 id);
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

    if (layer->curSurfaceIdx != 1) {
        layer->curSurfaceIdx = 1;
        layer->curSurface = layer->surfaces[layer->curSurfaceIdx];
    }
    layer->unk1644 = 1;
    layer->unk1648 = 4;
    layer->unk164C = 5;
    layer->unk1650 = 5;
    layer->unk170C |= 1;
    layer->unk16A8 |= 0x40;
    layer->unk17C4 |= 1;
    layer->unk1760 |= 0x40;
    layer->unk1998 = 0x80;
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
