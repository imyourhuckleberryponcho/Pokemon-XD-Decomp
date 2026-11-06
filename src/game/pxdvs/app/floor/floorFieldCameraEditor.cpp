#include <game/declspec.h>
#include <game/pxdvs/app/floor/floorData.h>
#include <dolphin/types.h>
#include <game/gcptr.h>
#pragma peephole off

struct GSvec {
    f32 x, y, z;
    GSvec();
    void clear();
};
struct GSfloor_dd_;
enum GSgfxPrimType {};
enum GSgfxBlendType {};
enum GSgfxBlendFactor {};
enum GSgfxLayerPass {};
enum GSgfxCullType {};
enum GSgfxACmpFunc {};
enum GSgfxAlphaOp {};
enum GSgfxZCmpFunc {};
struct GStexture;
struct GSgfxVF;

struct GSgfxDirty {
    u32 groups;
    u32 words[36];
    u32 textureMask;
    GStexture* textures[8];
};
struct GSgfxBlendSet {
    u8 unk0[0xBC];
};

#define GFX_DIRTY(word, bits, group)  \
    (&dirty[0].geom)[word] |= (bits);   \
    dirty[0].groups |= (group);       \
    (&dirty[1].geom)[word] |= (bits);   \
    dirty[1].groups |= (group);

extern "C" {
#ifdef __MWERKS__
#define GX_WGPIPE (*(volatile union { u8 u8; s16 s16; f32 f32; }*)0xCC008000)
#else
#define GX_WGPIPE GXWGFifo
#endif
static void GXParam1u8(u8 v);
static void GXParam1f32(f32 v);
}

enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
enum GSgfxLayerType { GSgfxLayerType_draft_dummy };
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void beginSurface(u16 n);
    void endSurface();
    void setRenderStateAndSelect(GSgfxVF* vf);

    void color4u8(u8 r, u8 g, u8 b, u8 a);
    void vertex3f(f32 x, f32 y, f32 z);
    void primitiveType(GSgfxPrimType t);
    void blendMode(GSgfxBlendType type, GSgfxBlendFactor src, GSgfxBlendFactor dst, bool pass);
    void SetRenderPass(GSgfxLayerPass pass);
    void cullMode(GSgfxCullType mode);
    void alphaCompare(bool enable, GSgfxACmpFunc f0, u8 ref0, GSgfxAlphaOp op, GSgfxACmpFunc f1, u8 ref1);
    void zCompare(bool enable, GSgfxZCmpFunc func);
    void pixelMode(bool cu, bool au, bool di);

};

namespace std {
DECL_WEAK float cosf(float);
DECL_WEAK float sinf(float);
}

struct FieldCameraState {
    u8 toggle;
    u8 pad1[3];
    GSvec pos;
    f32 dist;
    f32 height;
    f32 rotY;
    f32 radius;
    f32 width;
    f32 angle;
    u8 pad2[8];
    f32 fov;
};

struct FieldCameraEditorData {
    FieldCameraState* state;
    void** list;
    u32 count;
    void* mem0;
    void* mem1;
    u32 floorID;
    FloorFieldCameraHolder* savedField;
    u32 gapp;
    u8 testing;
    u8 mode;
};

void floorInitFieldCamera(GSfloor_dd_* floor);
extern "C" {
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
FloorData* floorDataBiosGetPtr(u32 key);
void* floorDataBiosGetFieldCameraListPtr(FloorData* floor);
u8 floorFieldCameraGetMode();
int GSgappCreate(s32 type, u8 priority, void* arg, void (*func)());
void GSgappTerminate(int id);
s32 GSfloorGetCurrent();
void GScameraLoadActiveCameraMatrix(int id);
u8* GScameraGetActiveCamera();
u8 cameraGetType();
void cameraGetTargetOfs(GSvec* ofs);
f32 cameraGetDistance();
f32 cameraGetHeight();
f32 cameraGetRotY();
f32 cameraGetFov();
u8 dbgMenuIsOpen();
bool menuIsCheck(s32 id);
u32 GSinputButtonsChanged(s32 pad);
u32 GSinputButtonsPressed(s32 pad);
GSgfxLayer* GSgfxLayerFindByID(GCsint id);
GSgfxVF* GSgfxVFBuildTemp(int, int, int, int, int, int, int, int, int);
void GSvecCopy(GSvec* dst, GSvec* src);

static FieldCameraEditorData gFieldCameraEditorData;

u8 floorFieldCameraEditorGetMode();
void floorFieldCameraEditorStopTest();
void floorReleaseFieldCameraEditor();
void floorUpdateFieldCameraEditor();

u8 floorFieldCameraEditorGetMode() { return gFieldCameraEditorData.mode; }

void floorReleaseFieldCameraEditor() {
    floorFieldCameraEditorStopTest();
    if (gFieldCameraEditorData.gapp != 0) {
        GSgappTerminate(gFieldCameraEditorData.gapp);
    }
    GSmemFree(gFieldCameraEditorData.mem1);
    GSmemFree(gFieldCameraEditorData.mem0);
    memset(&gFieldCameraEditorData, 0, sizeof(gFieldCameraEditorData));
}

void floorInitFieldCameraEditor(u32 floorID) {
    void* mem;
    u32* cams;
    u32 size;
    FloorData* floor = floorDataBiosGetPtr(floorID);
    u32 count;
    void* arr;
    floorReleaseFieldCameraEditor();
    if (floor != 0) {
        gFieldCameraEditorData.gapp = GSgappCreate(1, 0x7f, 0, floorUpdateFieldCameraEditor);
        if (gFieldCameraEditorData.gapp != 0) {
            mem = GSmemAlloc(8);
            if (mem != 0) {
                gFieldCameraEditorData.list = (void**)mem;
                gFieldCameraEditorData.mem0 = mem;
                cams = (u32*)floorDataBiosGetFieldCameraListPtr(floor);
                gFieldCameraEditorData.floorID = floorID;
                gFieldCameraEditorData.savedField = floor->fieldCamera;
                gFieldCameraEditorData.mode = floorFieldCameraGetMode();
                gFieldCameraEditorData.list[0] = &gFieldCameraEditorData.count;
                if (cams != 0) {
                    count = *(u32*)cams[0];
                    if (count != 0) {
                        size = count * 0x34;
                        arr = GSmemAlloc(size);
                        if (arr == 0) {
                            goto fail;
                        }
                        gFieldCameraEditorData.count = count;
                        gFieldCameraEditorData.mem1 = arr;
                        gFieldCameraEditorData.list[1] = arr;
                        memcpy(gFieldCameraEditorData.list[1], (void*)cams[1], size);
                    }
                }
                return;
            }
        }
    }
fail:
    floorReleaseFieldCameraEditor();
}

f32 floorFieldCameraEditorUnused() { return 1.0f; }

void floorUpdateFieldCameraEditor() {
    FieldCameraState* st = gFieldCameraEditorData.state;
    int i;
    FloorData* a = floorDataBiosGetPtr(GSfloorGetCurrent());
    FloorData* b = floorDataBiosGetPtr(gFieldCameraEditorData.floorID);
    if (a == 0 || a != b) {
        floorReleaseFieldCameraEditor();
        return;
    }
    if (gFieldCameraEditorData.testing == 0 && st != 0) {
        GSvec pos;
        GSvec ofs;
        pos.clear();
        if (cameraGetType() == 5) {
            GScameraLoadActiveCameraMatrix(-1);
            u8* cam = GScameraGetActiveCamera();
            if (cam != 0) {
                GSvecCopy(&pos, (GSvec*)(cam + 0xFC));
                cameraGetTargetOfs(&ofs);
                if (floorFieldCameraEditorGetMode() == 1 && dbgMenuIsOpen() == 0 && menuIsCheck(0x23) == 0) {
                    if (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x10) {
                        st->toggle ^= 1;
                    }
                    if (st->toggle != 0) {
                        if (GSinputButtonsPressed(1) & 0x40) {
                            if (GSinputButtonsPressed(1) & 0x100) {
                                st->angle += 0.1f;
                            } else if (GSinputButtonsPressed(1) & 0x200) {
                                st->angle -= 0.1f;
                            }
                        } else if (GSinputButtonsPressed(1) & 0x20) {
                            if (GSinputButtonsPressed(1) & 0x100) {
                                st->width += 0.1f;
                                if (st->width > 20.0f) {
                                    st->width = 20.0f;
                                }
                            } else if (GSinputButtonsPressed(1) & 0x200) {
                                st->width -= 0.1f;
                                if (st->width < 1.0f) {
                                    st->width = 1.0f;
                                }
                            }
                        }
                    } else if (GSinputButtonsPressed(1) & 0x100) {
                        st->radius += 1.0f;
                        if (st->radius > 500.0f) {
                            st->radius = 500.0f;
                        }
                    } else if (GSinputButtonsPressed(1) & 0x200) {
                        st->radius -= 1.0f;
                        if (st->radius < 5.0f) {
                            st->radius = 5.0f;
                        }
                    }
                    GSgfxLayer* l = GSgfxLayerFindByID(2);
                    if (l != 0) {
                        GScameraLoadActiveCameraMatrix(2);
                        l->pixelMode(1, 1, 0);
                        l->zCompare(0, (GSgfxZCmpFunc)7);
                        l->alphaCompare(0, (GSgfxACmpFunc)7, 0, (GSgfxAlphaOp)0, (GSgfxACmpFunc)7, 0);
                        l->cullMode((GSgfxCullType)0);
                        l->blendMode((GSgfxBlendType)1, (GSgfxBlendFactor)4, (GSgfxBlendFactor)1, 1);
                        l->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0));
                        if (st->toggle != 0) {
                            l->primitiveType((GSgfxPrimType)0x80);
                            f32 c = std::cosf(st->angle);
                            f32 s = std::sinf(st->angle);
                            f32 r = st->radius;
                            f32 w = st->width * r;
                            l->beginSurface(4);
                            l->vertex3f(pos.x + r * c + w * s, 0.1f + (pos.y - ofs.y), (pos.z - r * s) + w * c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->vertex3f((pos.x - r * c) + w * s, 0.1f + (pos.y - ofs.y), pos.z + r * s + w * c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->vertex3f((pos.x - r * c) - w * s, 0.1f + (pos.y - ofs.y), (pos.z + r * s) - w * c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->vertex3f((pos.x + r * c) - w * s, 0.1f + (pos.y - ofs.y), (pos.z - r * s) - w * c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->endSurface();
                        } else {
                            l->primitiveType((GSgfxPrimType)0xA0);
                            l->beginSurface(0x12);
                            l->vertex3f(pos.x, 0.1f + (pos.y - ofs.y), pos.z);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            for (i = 0; i < 0x11; i++) {
                                f32 a = 0.3926991f * (f32)i;
                                l->vertex3f(st->radius * std::cosf(a) + pos.x, 0.1f + (pos.y - ofs.y), st->radius * std::sinf(a) + pos.z);
                                l->color4u8(0x80, 0x80, 0x80, 0x80);
                            }
                            l->endSurface();
                        }
                    }
                }
                st->pos.x = pos.x;
                st->pos.y = pos.y - ofs.y;
                st->pos.z = pos.z;
                st->dist = cameraGetDistance();
                st->height = cameraGetHeight();
                st->rotY = cameraGetRotY();
                st->fov = cameraGetFov();
            }
        }
    }
}

void floorFieldCameraEditorStopTest() {
    gFieldCameraEditorData.testing = 0;
    if (gFieldCameraEditorData.floorID != 0) {
        FloorData* f = floorDataBiosGetPtr(gFieldCameraEditorData.floorID);
        if (f != 0) {
            f->fieldCamera = gFieldCameraEditorData.savedField;
            floorInitFieldCamera((GSfloor_dd_*)f);
        }
    }
}

u32 floorFieldCameraEditorGetFloorID() { return gFieldCameraEditorData.floorID; }
}

void GSgfxLayer::color4u8(u8 r, u8 g, u8 b, u8 a) {
    GXParam1u8(r);
    GXParam1u8(g);
    GXParam1u8(b);
    GXParam1u8(a);
}

void GSgfxLayer::vertex3f(f32 x, f32 y, f32 z) {
    GXParam1f32(x);
    GXParam1f32(y);
    GXParam1f32(z);
}

void GSgfxLayer::primitiveType(GSgfxPrimType t) {
    unk1998 = t;
}

void GSgfxLayer::blendMode(GSgfxBlendType type, GSgfxBlendFactor src, GSgfxBlendFactor dst, bool pass) {
    if (type == 0) {
        if (pass == 1) {
            SetRenderPass((GSgfxLayerPass)0);
        }
        hw.blend[0] = 0;
        hw.blend[1] = 1;
        hw.blend[2] = 1;
        hw.blend[3] = 5;
    } else {
        if (pass == 1) {
            SetRenderPass((GSgfxLayerPass)1);
        }
        hw.blend[0] = (u32)type;
        hw.blend[1] = (u32)src;
        hw.blend[2] = (u32)dst;
        hw.blend[3] = 5;
    }
    GFX_DIRTY(24, 1, 0x40)
}

void GSgfxLayer::SetRenderPass(GSgfxLayerPass pass) {
    if (curPass == (s32)pass) {
        return;
    }
    curPass = (s32)pass;
    curFifo = (GSgfxLayerData::PassFifo*)LAYER_CUR_PASS(this);
}

void GSgfxLayer::cullMode(GSgfxCullType mode) {
    hw.cullMode = (u32)mode;
    GFX_DIRTY(3, 2, 2)
}

void GSgfxLayer::alphaCompare(bool enable, GSgfxACmpFunc f0, u8 ref0, GSgfxAlphaOp op, GSgfxACmpFunc f1, u8 ref1) {
    if (enable == 1) {
        hw.alphaComp0 = (u32)f0;
        hw.alphaRef0 = ref0;
        hw.alphaCmpOp = (u32)op;
        hw.alphaComp1 = (u32)f1;
        hw.alphaRef1 = ref1;
        hw.zCompLoc = 0;
    } else {
        hw.alphaComp0 = 7;
        hw.alphaRef0 = 0;
        hw.alphaCmpOp = 0;
        hw.alphaComp1 = 7;
        hw.alphaRef1 = 0;
        hw.zCompLoc = 1;
    }
    GFX_DIRTY(24, 0x10, 0x40)
}

void GSgfxLayer::zCompare(bool enable, GSgfxZCmpFunc func) {
    if (enable == 1) {
        hw.zEnable = 1;
    } else {
        hw.zEnable = 0;
    }
    hw.zFunc = (u32)func;
    GFX_DIRTY(24, 8, 0x40)
}

void GSgfxLayer::pixelMode(bool cu, bool au, bool di) {
    if (cu == 1) {
        hw.colorUpdate = 1;
    } else {
        hw.colorUpdate = 0;
    }
    if (au == 1) {
        hw.alphaUpdate = 1;
    } else {
        hw.alphaUpdate = 0;
    }
    if (di == 1) {
        hw.zUpdate = 1;
    } else {
        hw.zUpdate = 0;
    }
    GFX_DIRTY(24, 4, 0x40)
}

#pragma peephole on
extern "C" {
static void GXParam1u8(u8 v) { GX_WGPIPE.u8 = v; }
static void GXParam1f32(f32 v) { GX_WGPIPE.f32 = v; }
}

extern "C" {
#pragma push
#pragma optimization_level 2
void GSvecCopy(GSvec* dst, GSvec* src) {
    f32 x = src->x;
    f32 y = src->y;
    dst->x = x;
    f32 z = src->z;
    dst->y = y;
    dst->z = z;
}
#pragma pop
}
