#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
#include <libc/string.h>

struct GSgfxVF {
    u8 data[0x440];
};

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(struct GSgfxLayer* layer, GSgfxLayerPass pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 unk18;
};

struct BlendState {
    u8 pad[0xbc];
};

struct GSmtx44 {
    f32 m[4][4];
};

class GSgfxLayer {
public:
    void setRenderStateAndSelect(struct GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

    u8 pad0[0x28];
    s32 id;
    u8 pad2c[0xd54 - 0x2c];
    s32 projType;
    f32 proj[6];
    u8 pad_d70[0xd8c - 0xd70];
    s32 d8c;
    u8 pad_d90[0x1644 - 0xd90];
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
    s32 f1664;
    s32 f1668;
    s32 f166c;
    u8 f1670;
    u8 f1671;
    u8 f1672;
    u8 pad_1673[0x1684 - 0x1673];
    f32 nearZ;
    f32 farZ;
    u8 pad_168c[0x16a6 - 0x168c];
    u8 f16a6;
    u8 f16a7;
    u32 dirty16a8;
    u32 dirty16ac;
    u8 pad_16b0[8];
    u32 dirty16b8;
    u8 pad_16bc[0x170c - 0x16bc];
    u32 dirty170c;
    u8 pad_1710[0x1760 - 0x1710];
    u32 dirty1760;
    u32 dirty1764;
    u8 pad_1768[8];
    u32 dirty1770;
    u8 pad_1774[0x17c4 - 0x1774];
    u32 dirty17c4;
    u8 pad_17c8[0x1818 - 0x17c8];
    BlendState blendTable[2];
    BlendState* curBlend;
    s32 curBlendIdx;
    u32 primType;
    u8 pad_199c[0x19a0 - 0x199c];
    struct GSlayerCam* cam;
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};

struct GSfilterEntry {
    u8 index;
    u8 used;
    u8 active;
};

struct GSfilterColor {
    u8 r, g, b, a;
};

struct GSfilterData {
    GSfilterEntry* entries;
    GSfilterColor* colors;
    s16 verts[8];
    GSgfxVF vf;
    u8 max;
    u8 used;
    u8 active;
};

extern "C" {
void* GSmemAlloc(u32 size);
void DCFlushRange(void* addr, u32 size);
void GSgfxVFInit(GSgfxVF* vf);
void GSgfxVFCreate(GSgfxVF* vf);
void GSgfxVFSetElement(GSgfxVF* vf, s32, s32, s32, s32);
void GSgfxVFSetArray(GSgfxVF* vf, s32, s32, void*, s32, s32);
void GSmtx44Ortho(f32* mtx, f32, f32, f32, f32, f32, f32);
void GScameraLoadActiveCameraMatrix(s32 id);
}
void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);

extern GSmtx44 mtxIdent;
static GSfilterData filtersData;

static void _filterRender(GSgfxLayer* layer, GSgfxLayerPass pass);

extern "C" {

GSfilterEntry* gsDefaultFilterPtr;
static bool gModuleInited;

GSfilterEntry* GSfilterCreate(GSfilterColor* color) {
    GSfilterEntry* e;
    u8 max;
    u8 i;
    max = filtersData.max;
    if (filtersData.used < max) {
        e = filtersData.entries;
        for (i = 0; i < max; i++, e++) {
            if (e->used == 0) {
                GSfilterColor* c = &filtersData.colors[i];
                c->r = color->r;
                c->g = color->g;
                c->b = color->b;
                c->a = color->a;
                if (color->a != 0 && e->active == 0) {
                    e->active = 1;
                    filtersData.active++;
                }
                e->used = 1;
                filtersData.used++;
                return e;
            }
        }
    }
    return 0;
}

void GSfilterFree(GSfilterEntry* e) {
    if (e->used == 0) {
        return;
    }
    e->used = 0;
    if (e->active != 0) {
        e->active = 0;
        filtersData.active--;
    }
    filtersData.used--;
}

void GSfilterSetColor(GSfilterEntry* e, GSfilterColor* color) {
    if (e->used != 0) {
        GSfilterColor* c = &filtersData.colors[e->index];
        c->r = color->r;
        c->g = color->g;
        c->b = color->b;
        c->a = color->a;
        DCFlushRange(c, 4);
        if (color->a != 0) {
            if (e->active == 0) {
                e->active = 1;
                filtersData.active++;
            }
        } else if (e->active != 0) {
            e->active = 0;
            filtersData.active--;
        }
    }
}

}

static void _filterRender(GSgfxLayer* layer, GSgfxLayerPass pass) {
    if (layer->id == 6) {
        switch (pass) {
        case 1:
        if (filtersData.used != 0 && filtersData.active != 0) {
            f32 mtx[16];
            u8 max = filtersData.max;
            GSfilterEntry* e = filtersData.entries;
            GSmtx44Ortho(mtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
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
            if (layer->curBlendIdx != 1) {
                layer->curBlendIdx = 1;
                layer->curBlend = &layer->blendTable[layer->curBlendIdx];
            }
            layer->blendOp = 1;
            layer->blendSrc = 4;
            layer->blendDst = 5;
            layer->blendLogic = 5;
            layer->dirty170c |= 1;
            layer->dirty16a8 |= 0x40;
            layer->dirty17c4 |= 1;
            layer->dirty1760 |= 0x40;
            layer->colorUpdate = 1;
            layer->alphaUpdate = 1;
            layer->zUpdate = 0;
            layer->dirty170c |= 4;
            layer->dirty16a8 |= 0x40;
            layer->dirty17c4 |= 4;
            layer->dirty1760 |= 0x40;
            layer->f1664 = 7;
            layer->f1670 = 0;
            layer->f1668 = 0;
            layer->f166c = 7;
            layer->f1671 = 0;
            layer->f1672 = 1;
            layer->dirty170c |= 0x10;
            layer->dirty16a8 |= 0x40;
            layer->dirty17c4 |= 0x10;
            layer->dirty1760 |= 0x40;
            layer->zEnable = 0;
            layer->zFunc = 3;
            layer->dirty170c |= 8;
            layer->dirty16a8 |= 0x40;
            layer->dirty17c4 |= 8;
            layer->dirty1760 |= 0x40;
            layer->d8c = 0;
            layer->dirty16b8 |= 2;
            layer->dirty16a8 |= 2;
            layer->dirty1770 |= 2;
            layer->dirty1760 |= 2;
            layer->setRenderStateAndSelect(&filtersData.vf);
            layer->primType = 0x80;
            layer->beginSurface((u16)(filtersData.active * 4));
            {
                u8 i;
                GSfilterColor* c = filtersData.colors;
                for (i = 0; i < max; i++, e++, c++) {
                    if (e->active != 0) {
                        GXWGFifo.u8 = 0;
                        GXWGFifo.u32 = *(u32*)c;
                        GXWGFifo.u8 = 1;
                        GXWGFifo.u32 = *(u32*)c;
                        GXWGFifo.u8 = 2;
                        GXWGFifo.u32 = *(u32*)c;
                        GXWGFifo.u8 = 3;
                        GXWGFifo.u32 = *(u32*)c;
                    }
                }
            }
            layer->endSurface();
        }
        }
    }
}

extern "C" {

void GSfilterInitialise(u8 count) {
    memset(&filtersData, 0, sizeof(filtersData));
    u8* data = (u8*)GSmemAlloc(count * 7);
    if (data != 0) {
        memset(data, 0, count * 7);
        filtersData.entries = (GSfilterEntry*)data;
        filtersData.colors = (GSfilterColor*)(data + count * 3);
        filtersData.verts[0] = 0;
        filtersData.verts[1] = 0;
        filtersData.verts[2] = 0;
        filtersData.verts[3] = 480;
        filtersData.verts[4] = 640;
        filtersData.verts[5] = 480;
        filtersData.verts[6] = 640;
        filtersData.verts[7] = 0;
        filtersData.max = count;
        GSgfxVFInit(&filtersData.vf);
        GSgfxVFCreate(&filtersData.vf);
        GSgfxVFSetElement(&filtersData.vf, 9, 0, 2, 0);
        GSgfxVFSetElement(&filtersData.vf, 11, 1, 5, 0);
        GSgfxVFSetArray(&filtersData.vf, 9, 2, filtersData.verts, 4, 16);
        {
            GSfilterEntry* e = filtersData.entries;
            u8 i;
            for (i = 0; i < count; i++, e++) {
                e->index = i;
            }
        }
        GSfilterColor zero;
        zero.r = 0;
        zero.g = 0;
        zero.b = 0;
        zero.a = 0;
        gsDefaultFilterPtr = GSfilterCreate(&zero);
        if (!gModuleInited) {
            GSgfxRenderModule module = {0, 0, _filterRender, 0, 0, 0, 0xB29A48E1};
            GSgfxRenderModuleRegister(0x9c, &module, 0);
            gModuleInited = true;
        }
    }
}

}
