#include <dolphin/types.h>
#include <game/gcdata.h>
#include <game/gsvfarray.h>
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

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void setRenderStateAndSelect(struct GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

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

extern "C" GSmtx44 mtxIdent;
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
    if ((*(s32*)&layer->id) == 6) {
        switch (pass) {
        case 1:
        if (filtersData.used != 0 && filtersData.active != 0) {
            f32 mtx[16];
            u8 max = filtersData.max;
            GSfilterEntry* e = filtersData.entries;
            GSmtx44Ortho(mtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
            (*(s32*)&layer->hw.projType) = 1;
            ((f32*)layer->hw.proj)[0] = mtx[0];
            ((f32*)layer->hw.proj)[1] = mtx[3];
            ((f32*)layer->hw.proj)[2] = mtx[5];
            ((f32*)layer->hw.proj)[3] = mtx[7];
            ((f32*)layer->hw.proj)[4] = mtx[10];
            ((f32*)layer->hw.proj)[5] = mtx[11];
            GSlayerCam* cam = (*(GSlayerCam**)&layer->matrixStack);
            memcpy(cam->data + 1, &mtxIdent, 0x30);
            cam->data[0] |= 1;
            (*(f32*)&layer->hw.fogNear) = 0.0f;
            (*(f32*)&layer->hw.fogFar) = 30000.0f;
            if ((*(u8*)&layer->hw.fogEnable)) {
                if ((*(u8*)&layer->hw.fogRangeEnable)) {
                    (*(u32*)&layer->dirty[0].pe) |= 0x100;
                    (*(u32*)&layer->dirty[1].pe) |= 0x100;
                }
                (*(u32*)&layer->dirty[0].pe) |= 0x40;
                (*(u32*)&layer->dirty[0].groups) |= 0x40;
                (*(u32*)&layer->dirty[1].pe) |= 0x40;
                (*(u32*)&layer->dirty[1].groups) |= 0x40;
            }
            (*(u32*)&layer->dirty[0].geom) |= 0x20;
            (*(u32*)&layer->dirty[0].groups) |= 1;
            (*(u32*)&layer->dirty[1].geom) |= 0x20;
            (*(u32*)&layer->dirty[1].groups) |= 1;
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
            (*(u8*)&layer->hw.colorUpdate) = 1;
            (*(u8*)&layer->hw.alphaUpdate) = 1;
            (*(u8*)&layer->hw.zUpdate) = 0;
            (*(u32*)&layer->dirty[0].pe) |= 4;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 4;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(s32*)&layer->hw.alphaComp0) = 7;
            (*(u8*)&layer->hw.alphaRef0) = 0;
            (*(s32*)&layer->hw.alphaCmpOp) = 0;
            (*(s32*)&layer->hw.alphaComp1) = 7;
            (*(u8*)&layer->hw.alphaRef1) = 0;
            (*(u8*)&layer->hw.zCompLoc) = 1;
            (*(u32*)&layer->dirty[0].pe) |= 0x10;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 0x10;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(u8*)&layer->hw.zEnable) = 0;
            (*(s32*)&layer->hw.zFunc) = 3;
            (*(u32*)&layer->dirty[0].pe) |= 8;
            (*(u32*)&layer->dirty[0].groups) |= 0x40;
            (*(u32*)&layer->dirty[1].pe) |= 8;
            (*(u32*)&layer->dirty[1].groups) |= 0x40;
            (*(s32*)&layer->hw.cullMode) = 0;
            (*(u32*)&layer->dirty[0].raster) |= 2;
            (*(u32*)&layer->dirty[0].groups) |= 2;
            (*(u32*)&layer->dirty[1].raster) |= 2;
            (*(u32*)&layer->dirty[1].groups) |= 2;
            layer->setRenderStateAndSelect(&filtersData.vf);
            (*(u32*)&layer->unk1998) = 0x80;
            layer->beginSurface((u16)(filtersData.active * 4));
            {
                u8 i;
                GSfilterColor* c = filtersData.colors;
                for (i = 0; i < max; i++, e++, c++) {
                    if (e->active != 0) {
                        GXWGFifo.u8 = 0;
                        GXWGFifo.u32 = GC_BYTES32(c);
                        GXWGFifo.u8 = 1;
                        GXWGFifo.u32 = GC_BYTES32(c);
                        GXWGFifo.u8 = 2;
                        GXWGFifo.u32 = GC_BYTES32(c);
                        GXWGFifo.u8 = 3;
                        GXWGFifo.u32 = GC_BYTES32(c);
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
        GSGFX_VF_SET_ARRAY_NATIVE(&filtersData.vf, 9, 2, filtersData.verts, 4, 16);
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
