// STATUS (dFFCE): needs extra_cflags=["-inline off"] (weak GSgfxLayer setters stay out-of-line) + peephole off (in file).
// 16/18 exact. floorUpdateFieldCameraEditor 99.45% (f29/f30 swap: radius vs sin in the quad branch), GSvecCopy 98.3%
// (load order x,y,z,... not reproduced). LAYOUT: target has the weak methods in later .text sections (after GetFloorID); we emit them
// right after Update. floorFieldCameraEditorUnused is a placeholder that pulls 1.0f into .sdata2 first (stripped function).
#include <dolphin/types.h>
#pragma peephole off

struct GSvec {
    f32 x, y, z;
    GSvec();
    void clear();
};
struct GSfloor_dd_;
struct FloorData {
    u8 unk0[0x14];
    u32 unk14;
};
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
    dirty[0].words[word] |= (bits);   \
    dirty[0].groups |= (group);       \
    dirty[1].words[word] |= (bits);   \
    dirty[1].groups |= (group);

extern "C" {
#define GX_WGPIPE (*(volatile union { u8 u8; s16 s16; f32 f32; }*)0xCC008000)
static void GXParam1u8(u8 v);
static void GXParam1f32(f32 v);
}

class GSgfxLayer {
public:
    void beginSurface(u16 n);
    void endSurface();
    void setRenderStateAndSelect(GSgfxVF* vf);

    void color4u8(u8 r, u8 g, u8 b, u8 a) {
        GXParam1u8(r);
        GXParam1u8(g);
        GXParam1u8(b);
        GXParam1u8(a);
    }
    void vertex3f(f32 x, f32 y, f32 z) {
        GXParam1f32(x);
        GXParam1f32(y);
        GXParam1f32(z);
    }
    void primitiveType(GSgfxPrimType t) { primType = t; }
    void blendMode(GSgfxBlendType type, GSgfxBlendFactor src, GSgfxBlendFactor dst, bool pass) {
        if (type == 0) {
            if (pass == 1) {
                SetRenderPass((GSgfxLayerPass)0);
            }
            blendType = 0;
            blendSrc = 1;
            blendDst = 1;
            blendLogicOp = 5;
        } else {
            if (pass == 1) {
                SetRenderPass((GSgfxLayerPass)1);
            }
            blendType = (u32)type;
            blendSrc = (u32)src;
            blendDst = (u32)dst;
            blendLogicOp = 5;
        }
        GFX_DIRTY(24, 1, 0x40)
    }
    void SetRenderPass(GSgfxLayerPass pass) {
        if (renderPass == (s32)pass) {
            return;
        }
        renderPass = (s32)pass;
        blendSet = (GSgfxBlendSet*)((u8*)this + 0x1818 + renderPass * 0xBC);
    }
    void cullMode(GSgfxCullType mode) {
        cullType = (u32)mode;
        GFX_DIRTY(3, 2, 2)
    }
    void alphaCompare(bool enable, GSgfxACmpFunc f0, u8 ref0, GSgfxAlphaOp op, GSgfxACmpFunc f1, u8 ref1) {
        if (enable == 1) {
            alphaComp0 = (u32)f0;
            alphaRef0 = ref0;
            alphaOp = (u32)op;
            alphaComp1 = (u32)f1;
            alphaRef1 = ref1;
            alphaCompareOff = 0;
        } else {
            alphaComp0 = 7;
            alphaRef0 = 0;
            alphaOp = 0;
            alphaComp1 = 7;
            alphaRef1 = 0;
            alphaCompareOff = 1;
        }
        GFX_DIRTY(24, 0x10, 0x40)
    }
    void zCompare(bool enable, GSgfxZCmpFunc func) {
        if (enable == 1) {
            zEnable = 1;
        } else {
            zEnable = 0;
        }
        zFunc = (u32)func;
        GFX_DIRTY(24, 8, 0x40)
    }
    void pixelMode(bool cu, bool au, bool di) {
        if (cu == 1) {
            colorUpdate = 1;
        } else {
            colorUpdate = 0;
        }
        if (au == 1) {
            alphaUpdate = 1;
        } else {
            alphaUpdate = 0;
        }
        if (di == 1) {
            dither = 1;
        } else {
            dither = 0;
        }
        GFX_DIRTY(24, 4, 0x40)
    }

    u8 unk0[0xD8C];
    u32 cullType;
    u8 unkD90[0x8B4];
    u32 blendType;
    u32 blendSrc;
    u32 blendDst;
    u32 blendLogicOp;
    u8 unk1654[0x2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 dither;
    u8 unk1659[0x3];
    u8 zEnable;
    u8 unk165D[0x3];
    u32 zFunc;
    u32 alphaComp0;
    u32 alphaOp;
    u32 alphaComp1;
    u8 alphaRef0;
    u8 alphaRef1;
    u8 alphaCompareOff;
    u8 unk1673[0x35];
    GSgfxDirty dirty[2];
    GSgfxBlendSet blendSets[2];
    GSgfxBlendSet* blendSet;
    s32 renderPass;
    GSgfxPrimType primType;
};

namespace std {
__declspec(weak) float cosf(float);
__declspec(weak) float sinf(float);
} // namespace std

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
    u32 savedField;
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
GSgfxLayer* GSgfxLayerFindByID(int id);
GSgfxVF* GSgfxVFBuildTemp(int, int, int, int, int, int, int, int, int);
inline void GSvecCopy(GSvec* dst, GSvec* src) {
    f32 x = src->x;
    f32 y = src->y;
    dst->x = x;
    f32 z = src->z;
    dst->y = y;
    dst->z = z;
}

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
    memset(&gFieldCameraEditorData, 0, 0x24);
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
                gFieldCameraEditorData.savedField = floor->unk14;
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

// Placeholder for a function the linker stripped; it pulled 1.0f into .sdata2 first.
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
                            f32 rc = r * c;
                            r = s * r;
                            s = s * w;
                            c = w * c;
                            l->vertex3f(pos.x + rc + s, 0.1f + (pos.y - ofs.y), (pos.z - r) + c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->vertex3f((pos.x - rc) + s, 0.1f + (pos.y - ofs.y), pos.z + r + c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->vertex3f((pos.x - rc) - s, 0.1f + (pos.y - ofs.y), (pos.z + r) - c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->vertex3f((pos.x + rc) - s, 0.1f + (pos.y - ofs.y), (pos.z - r) - c);
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
            f->unk14 = gFieldCameraEditorData.savedField;
            floorInitFieldCamera((GSfloor_dd_*)f);
        }
    }
}

u32 floorFieldCameraEditorGetFloorID() { return gFieldCameraEditorData.floorID; }
}

#pragma peephole on
extern "C" {
static void GXParam1u8(u8 v) { GX_WGPIPE.u8 = v; }
static void GXParam1f32(f32 v) { GX_WGPIPE.f32 = v; }
}
