#include <dolphin/types.h>
#include "game/gc_fused.h"
#include <game/gcdata.h>
#include <game/gcptr.h>
#include <game/pxdvs/app/floor/floorData.h>
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#pragma pool_strings off
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct FloorData;
struct GScamera;
struct GSgfxLayer;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
struct GSgfxVF;
struct GSlight;
struct GSstreamFileOutput;
struct GSvec;
struct GXColor;
struct LightEditor;
typedef f32 Mtx[3][4];
struct PeopleWork;
struct Vec;

extern "C++" {
struct GScamera {
    u8 _draft[1];
};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
#ifdef __MWERKS__
    s32 endSurface();
#else
    void endSurface();
#endif
#ifdef __MWERKS__
    s32 beginSurface(unsigned short);
#else
    void beginSurface(unsigned short p0);
#endif
    void setRenderStateAndSelect(GSgfxVF*);
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSlight {
    u8 _draft[1];
};
struct GSstreamFileOutput {
    u8 data[0x14];
    bool open(const char*);
    GSstreamFileOutput();
    ~GSstreamFileOutput();
    bool writePrintf(const char*, ...);
};
struct GSvec {
    f32 x, y, z;
};
struct GXColor {
    u8 r, g, b, a;
};
struct LightEditor {
    u8 _draft[1];
    void editUpdate();
    LightEditor();
    void dispLightModel(GSlight*, bool);
    void init();
    void editDirection(GSlight*);
    void editType(GSlight*);
    void editPosition(GSlight*);
    void dispInfo(GSlight*, s32, s32, bool);
    void editCommand();
};
struct PeopleWork {
    u8 _draft[1];
};
struct Vec {
    f32 x, y, z;
};

extern "C" {
GScamera* GScameraGetActiveCamera(void);
void GScameraGetFrontVector(GScamera* camera, f32* front);
void GScameraGetPosition(GScamera* camera, f32* position);
void GScameraLoadActiveCameraMatrix(GSgfxLayerID id);
struct GSgfxLayer* GSgfxLayerFindByID(GCsint id);
GSgfxVF* GSgfxVFGetPredef(s32 id);
f32 GSgfxVideoGetLastRenderTime(void);
u32 GSinputButtonsChanged(s32 pad);
u32 GSinputButtonsPressed(s32 pad);
s32 GSinputButtonsRepeat(s32);
s8 GSinputGetLeftStickXData(s32 pad, s32 mode);
s8 GSinputGetLeftStickYData(s32 pad, s32 mode);
s8 GSinputGetRightStickXData(s32 pad, s32 mode);
s8 GSinputGetRightStickYData(s32 pad, s32 mode);
u8 GSlightCanAnimate(GSlight* light);
u8 GSlightGetActive(GSlight* light);
void GSlightGetColor(GSlight* light, GXColor* color);
bool GSlightGetPosition(GSlight* light, f32* position);
void GSlightGetTarget(GSlight* light, f32* target);
s32 GSlightGetType(GSlight* light);
void GSlightSetColor(GSlight* light, const GXColor* color);
void GSlightSetPosition(GSlight* light, f32* position);
void GSlightSetType(GSlight* light, s32 type);
void GSprint(s32 layer, s32 x, s32 y, s32 color, const char* fmt, ...);
void* GSresGetResourceAllGroup(u32 id);
asm void PSMTXConcat(const register Mtx a, const register Mtx b, register Mtx ab);
asm void PSMTXCopy(const register Mtx src, register Mtx dst);
asm void PSMTXMultVec(const register Mtx m, const register Vec* src, register Vec* dst);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
asm void PSVECCrossProduct(const register Vec* a, const register Vec* b, register Vec* axb);
void PSVECNormalize(const register Vec* src, register Vec* unit);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
u8 cameraGetType(void);
u8 cameraSetType(u8 type);
s32 dbgMenuGetLayerID(void);
FloorData* floorDataBiosGetCurrentPtr(void);
u32 floorDataBiosGetShadowLightID(FloorData* floor);
void floorGetLightInfo(u32* a, u32* b);
void* lightGetLight(s32 index);
s32 lightGetLightSize(void);
s32 peopleBiosGetMaxNum(void);
void* peopleBiosGetPosPtr(PeopleWork* work);
s32 peopleBiosGetState(PeopleWork* work);
PeopleWork* peopleBiosGetWorkPtr(s32 index);
void peopleGetPos(s32, s32, GSvec*);
double sin(double x);
}
extern "C++" {
void GSprimSetup3DRender(GSgfxLayer* layer);
}

#ifdef __MWERKS__
typedef union { u8 u8; f32 f32; } LightWGPipe;
volatile LightWGPipe GXWGFifo : 0xCC008000;
#endif
#define FIFO_F32(v) (GXWGFifo.f32 = (v))
#define FIFO_U8(v) (GXWGFifo.u8 = (v))
static inline void lightPosition3f32(f32 x, f32 y, f32 z) { FIFO_F32(x); FIFO_F32(y); FIFO_F32(z); }
static inline void lightColor4u8(u8 r, u8 g, u8 b, u8 a) { FIFO_U8(r); FIFO_U8(g); FIFO_U8(b); FIFO_U8(a); }
#define FIFO_COLOR3(r, g, b) (FIFO_U8(r), FIFO_U8(g), FIFO_U8(b), FIFO_U8(0xFF))
#define FIFO_COLOR(c) (FIFO_U8((c).r), FIFO_U8((c).g), FIFO_U8((c).b), FIFO_U8(0xFF))

LightEditor::LightEditor() {
    M2C_FIELD(this, s8 *, 4) = 0;
    M2C_FIELD(this, s8 *, 0) = 0;
    M2C_FIELD(this, s8 *, 1) = 0;
    M2C_FIELD(this, f32 *, 8) = 1.0f;
    M2C_FIELD(this, s8 *, 3) = 0;
}

void LightEditor::init() {
    M2C_FIELD(this, s8 *, 4) = 0;
    M2C_FIELD(this, s8 *, 0) = 0;
    M2C_FIELD(this, s8 *, 1) = 0;
    M2C_FIELD(this, f32 *, 8) = 1.0f;
    M2C_FIELD(this, s8 *, 3) = 0;
}

static inline void dispAll(LightEditor* e, s32 layer) {
    u32 info;
    u32 count;
    GSgfxLayer* layer3d;
    s32 y;
    s32 color;

    floorGetLightInfo((u32*)(&info), (u32*)(&count));
    count = lightGetLightSize();
    layer3d = (GSgfxLayer *)(GSgfxLayerFindByID(2));
    if (layer3d != NULL) {
        GSprimSetup3DRender((GSgfxLayer*)(layer3d));
    }
    for (s32 i = 0; i < (s32) count; i++) {
        e->dispLightModel((GSlight*)(lightGetLight(i)), (s8) M2C_FIELD(e, u8 *, 0) == i);
    }
    y = 0x1E;
    for (s32 i = 0; i < (s32) count; i++) {
        e->dispInfo((GSlight*)(lightGetLight(i)), 0x14, y, (s8) M2C_FIELD(e, u8 *, 0) == i);
        y += 0xD;
    }
    if (layer != -1) {
        color = (M2C_FIELD(e, s8 *, 0) < 0) ? -0x7F01 : -1;
        GSprint(layer, 0x14, y, color, (const char*)("save"));
    }
}

void LightEditor::editUpdate() {
    u32 sp14;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r31;
    s32 temp_r30;
    GXColor unksp10;
    u32 spC;
    u32 sp8;
    GSgfxLayer *layer3d;
    GSlight *temp_r3_3;
    f32 temp_f1;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_7;
    s32 var_r6;
    u8 *var_r30;
    u8 temp_r0;
    u8 temp_r3_2;
    u8 temp_r3_4;
    u8 temp_r3_5;
    u8 temp_ret;

    GSgfxVideoGetLastRenderTime();
    temp_r3 = GSinputButtonsRepeat(1);
    if (temp_r3 & 0x1000) {
        if (cameraGetType() == 6) {
            cameraSetType(3U);
        } else {
            cameraSetType(6U);
        }
    }
    if (cameraGetType() != 6) {
        if (temp_r3 & 4) {
            M2C_FIELD(this, s8 *, 0) += 1;
        }
        if (M2C_FIELD(this, s8 *, 0) >= lightGetLightSize()) {
            M2C_FIELD(this, s8 *, 0) = -1;
        }
        if (temp_r3 & 8) {
            M2C_FIELD(this, s8 *, 0) -= 1;
        }
        if (M2C_FIELD(this, s8 *, 0) < -1) {
            M2C_FIELD(this, s8 *, 0) = lightGetLightSize() - 1;
        }
        if (M2C_FIELD(this, s8 *, 0) < 0) {
            ((LightEditor*)(this))->editCommand();
            goto block_59;
        }
        temp_r3_3 = (GSlight *)(lightGetLight(M2C_FIELD(this, s8 *, 0)));
        if (temp_r3_3 != NULL) {
            temp_r31 = GSlightGetType((GSlight*)(temp_r3_3));
            if (temp_r3 & 2) {
                if (M2C_FIELD(this, s8 *, 1) == 0) {
                    M2C_FIELD(this, s8 *, 1) = 1;
                    M2C_FIELD(this, s8 *, 2) = 0;
                } else if (M2C_FIELD(this, s8 *, 1) == 1) {
                    M2C_FIELD(this, s8 *, 2) += 1;
                    if (M2C_FIELD(this, s8 *, 2) > 2) {
                        if (temp_r31 == 0) {
                            M2C_FIELD(this, s8 *, 1) = 0;
                        } else {
                            M2C_FIELD(this, s8 *, 1) = 2;
                        }
                        M2C_FIELD(this, s8 *, 2) = 0;
                    }
                } else if (M2C_FIELD(this, s8 *, 1) == 2) {
                    M2C_FIELD(this, s8 *, 2) += 1;
                    if (M2C_FIELD(this, s8 *, 2) > 2) {
                        M2C_FIELD(this, s8 *, 1) = 0;
                        M2C_FIELD(this, s8 *, 2) = 0;
                    }
                }
            }
            if (temp_r3 & 1) {
                if (M2C_FIELD(this, s8 *, 1) == 0) {
                    if (temp_r31 == 0) {
                        M2C_FIELD(this, s8 *, 1) = 1;
                        M2C_FIELD(this, s8 *, 2) = 2;
                    } else {
                        M2C_FIELD(this, s8 *, 1) = 2;
                    }
                    M2C_FIELD(this, s8 *, 2) = 2;
                } else if (M2C_FIELD(this, s8 *, 1) == 1) {
                    M2C_FIELD(this, s8 *, 2) -= 1;
                    if (M2C_FIELD(this, s8 *, 2) < 0) {
                        M2C_FIELD(this, s8 *, 1) = 0;
                        M2C_FIELD(this, s8 *, 2) = 0;
                    }
                } else if (M2C_FIELD(this, s8 *, 1) == 2) {
                    M2C_FIELD(this, s8 *, 2) -= 1;
                    if (M2C_FIELD(this, s8 *, 2) < 0) {
                        M2C_FIELD(this, s8 *, 1) = 1;
                        M2C_FIELD(this, s8 *, 2) = 2;
                    }
                }
            }
            ((LightEditor*)(this))->editType((GSlight*)(temp_r3_3));
            var_r30 = NULL;
            if ((s32) M2C_FIELD(this, u8 *, 1) == 1) {
                GSlightGetColor((GSlight*)(temp_r3_3), &unksp10);
                temp_r0 = M2C_FIELD(this, u8 *, 2);
                switch ((s8) temp_r0) {
                case 0:
                    var_r30 = &unksp10.r;
                    break;
                case 1:
                    var_r30 = &unksp10.g;
                    break;
                case 2:
                    var_r30 = &unksp10.b;
                    break;
                }
                if (var_r30 != NULL) {
                    if (GSinputButtonsRepeat(1) & 0x400) {
                        *var_r30 -= 1;
                    }
                    if (GSinputButtonsRepeat(1) & 0x800) {
                        *var_r30 += 1;
                    }
                    sp14 = *(u32*)&unksp10;
                    GSlightSetColor((GSlight*)(temp_r3_3), (GXColor*)&sp14);
                }
            }
            if (temp_r31 == 1) {
                ((LightEditor*)(this))->editDirection((GSlight*)(temp_r3_3));
            } else {
                ((LightEditor*)(this))->editPosition((GSlight*)(temp_r3_3));
            }
            goto block_59;
        }
    } else {
block_59:
        dispAll(this, dbgMenuGetLayerID());
        temp_r3_7 = dbgMenuGetLayerID();
        if (temp_r3_7 != -1) {
            if (cameraGetType() == 6) {
                GSprint(temp_r3_7, 0x1F4, 0x20, -1, "camera mode");
                return;
            }
            GSprint(temp_r3_7, 0x1F4, 0x20, -1, "light mode");
        }
    }
}

#pragma push
#pragma dont_inline on
void LightEditor::dispInfo(GSlight* p0, s32 p1, s32 p2, bool p3) {
    Vec pos;
    Vec tgt;
    GXColor col;
    u32 layer2;
    s32 last;
    s32 layer;
    s32 colr;
    bool shadow;
    bool isLight;
    const char* name;
    s32 type;
    s32 hl;

    isLight = 0;
    shadow = GSresGetResourceAllGroup(floorDataBiosGetShadowLightID((FloorData*)(floorDataBiosGetCurrentPtr()))) == p0;
    layer = dbgMenuGetLayerID();
    if (layer != -1) {
        hl = p3 ? -0x7F01 : -1;
        GSlightGetActive(p0);
        GSlightGetPosition(p0, &pos.x);
        GSlightGetTarget(p0, &tgt.x);
        GSlightGetColor(p0, &col);
        GSlightCanAnimate(p0);
        type = GSlightGetType(p0);
        switch (type) {
        case 0:
            name = "Amb";
            break;
        case 1:
            name = "Dir";
            isLight = 1;
            break;
        case 2:
            name = "Pnt";
            isLight = 1;
            break;
        case 3:
            name = "Spt";
            isLight = 1;
            break;
        default:
            name = "???";
            break;
        }
        colr = -1;
        if (M2C_FIELD(this, s8 *, 1) == 0) {
            colr = hl;
        }
        layer2 = layer;
        GSprint(layer, p1, p2, colr, "%s:", name);
        colr = ((M2C_FIELD(this, s8 *, 2) == 0) && (M2C_FIELD(this, s8 *, 1) == 1)) ? hl : -1;
        GSprint(layer2, p1 + 0x34, p2, colr, "(%02x,", col.r);
        colr = ((M2C_FIELD(this, s8 *, 2) == 1) && (M2C_FIELD(this, s8 *, 1) == 1)) ? hl : -1;
        GSprint(layer2, p1 + 0x5B, p2, colr, "%02x,", col.g);
        colr = ((M2C_FIELD(this, s8 *, 2) == 2) && (M2C_FIELD(this, s8 *, 1) == 1)) ? hl : -1;
        last = colr;
        GSprint(layer2, p1 + 0x7A, p2, colr, "%02x)", col.b);
        if (isLight) {
            colr = ((M2C_FIELD(this, s8 *, 2) == 0) && (M2C_FIELD(this, s8 *, 1) == 2)) ? hl : -1;
            GSprint(layer2, p1 + 0xB6, p2, colr, "(%.2f,", pos.x);
            colr = ((M2C_FIELD(this, s8 *, 2) == 1) && (M2C_FIELD(this, s8 *, 1) == 2)) ? hl : -1;
            GSprint(layer2, p1 + 0xF7, p2, colr, " %.2f,", pos.y);
            colr = ((M2C_FIELD(this, s8 *, 2) == 2) && (M2C_FIELD(this, s8 *, 1) == 2)) ? hl : -1;
            last = colr;
            GSprint(layer2, p1 + 0x130, p2, colr, " %.2f)", pos.z);
        }
        if (shadow) {
            GSprint(layer2, p1 + 0x17E, p2, last, "(shadow)");
        }
    }
}
#pragma pop

void LightEditor::dispLightModel(GSlight* light, bool selected) {
    static f32 widthArray[4][2] = { { -1.0f, -1.0f }, { 1.0f, -1.0f }, { 1.0f, 1.0f }, { -1.0f, 1.0f } };
    f32 size = 0.5f;
    GSvec pos;
    GSvec dir;
    GSvec target;
    GSvec peoplePos;
    GSvec tmp;
    GXColor col;
    int i;
    if (GSlightGetActive(light) != 0) {
        if (selected != 0) {
            f32 pulse;
            if (((f32)sin((f64)M2C_FIELD(this, f32*, 8)) / 2.0f) < 0.0f) {
                pulse = -((f32)sin((f64)M2C_FIELD(this, f32*, 8)) / 2.0f);
            } else {
                pulse = (f32)sin((f64)M2C_FIELD(this, f32*, 8)) / 2.0f;
            }
            size += pulse;
            M2C_FIELD(this, f32*, 8) += 0.1f;
            if (M2C_FIELD(this, f32*, 8) > 6.2831855f) {
                M2C_FIELD(this, f32*, 8) = 0.0f;
            }
        }
        if (GSlightGetType(light) != 0) {
            GSlightGetPosition(light, (f32*)&pos);
            GSlightGetTarget(light, (f32*)&target);
            GSlightGetColor(light, &col);
            if (GSlightGetType(light) == 1) {
                PeopleWork* work = peopleBiosGetWorkPtr(M2C_FIELD(this, s8*, 4));
                if (work != NULL) {
                    GSvec* wp = (GSvec*)peopleBiosGetPosPtr(work);
                    peoplePos.x = wp->x;
                    peoplePos.y = wp->y;
                    peoplePos.z = wp->z;
                    dir.x = pos.x;
                    dir.y = pos.y;
                    dir.z = pos.z;
                    PSVECNormalize((const Vec*)&dir, (Vec*)&dir);
                    tmp.x = dir.x;
                    tmp.y = dir.y;
                    tmp.z = dir.z;
                    PSVECScale((const Vec*)&tmp, (Vec*)&tmp, 20.0f);
                    PSVECAdd((const Vec*)&tmp, (const Vec*)&peoplePos, (Vec*)&pos);
                    pos.y += 5.0f;
                }
            }
            GSgfxLayer* layer = (GSgfxLayer*)GSgfxLayerFindByID(2);
            if (layer != 0) {
                GScameraLoadActiveCameraMatrix((GSgfxLayerID)(M2C_NAMED(layer, s32*, 0x28, id)));
                M2C_NAMED(layer, s8*, 0x1656, hw.colorUpdate) = 1;
                M2C_NAMED(layer, s8*, 0x1657, hw.alphaUpdate) = 1;
                M2C_NAMED(layer, s8*, 0x1658, hw.zUpdate) = 1;
                M2C_NAMED(layer, s32*, 0x170C, dirty[0].pe) = (s32)(M2C_NAMED(layer, s32*, 0x170C, dirty[0].pe) | 4);
                M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) = (s32)(M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) | 0x40);
                M2C_NAMED(layer, s32*, 0x17C4, dirty[1].pe) = (s32)(M2C_NAMED(layer, s32*, 0x17C4, dirty[1].pe) | 4);
                M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) = (s32)(M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) | 0x40);
                M2C_NAMED(layer, s8*, 0x165C, hw.zEnable) = 1;
                M2C_NAMED(layer, s32*, 0x1660, hw.zFunc) = 1;
                M2C_NAMED(layer, s32*, 0x170C, dirty[0].pe) = (s32)(M2C_NAMED(layer, s32*, 0x170C, dirty[0].pe) | 8);
                M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) = (s32)(M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) | 0x40);
                M2C_NAMED(layer, s32*, 0x17C4, dirty[1].pe) = (s32)(M2C_NAMED(layer, s32*, 0x17C4, dirty[1].pe) | 8);
                M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) = (s32)(M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) | 0x40);
                M2C_NAMED(layer, s32*, 0x1664, hw.alphaComp0) = 7;
                M2C_NAMED(layer, s8*, 0x1670, hw.alphaRef0) = 0;
                M2C_NAMED(layer, s32*, 0x1668, hw.alphaCmpOp) = 0;
                M2C_NAMED(layer, s32*, 0x166C, hw.alphaComp1) = 7;
                M2C_NAMED(layer, s8*, 0x1671, hw.alphaRef1) = 0;
                M2C_NAMED(layer, s8*, 0x1672, hw.zCompLoc) = 1;
                M2C_NAMED(layer, s32*, 0x170C, dirty[0].pe) = (s32)(M2C_NAMED(layer, s32*, 0x170C, dirty[0].pe) | 0x10);
                M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) = (s32)(M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) | 0x40);
                M2C_NAMED(layer, s32*, 0x17C4, dirty[1].pe) = (s32)(M2C_NAMED(layer, s32*, 0x17C4, dirty[1].pe) | 0x10);
                M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) = (s32)(M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) | 0x40);
                M2C_NAMED(layer, s32*, 0xD8C, hw.cullMode) = 0;
                M2C_NAMED(layer, s32*, 0x16B8, dirty[0].raster) = (s32)(M2C_NAMED(layer, s32*, 0x16B8, dirty[0].raster) | 2);
                M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) = (s32)(M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) | 2);
                M2C_NAMED(layer, s32*, 0x1770, dirty[1].raster) = (s32)(M2C_NAMED(layer, s32*, 0x1770, dirty[1].raster) | 2);
                M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) = (s32)(M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) | 2);
                if ((s32)M2C_NAMED(layer, s32*, 0x1994, curPass) != 1) {
                    M2C_NAMED(layer, s32*, 0x1994, curPass) = 1;
                    M2C_NAMED(layer, s32*, 0x1990, curFifo) = (GCsptr)((u8*)layer + 0x1818 + M2C_NAMED(layer, s32*, 0x1994, curPass) * 0xBC);
                }
                M2C_NAMED(layer, s32*, 0x1644, hw.blend[0]) = 1;
                M2C_NAMED(layer, s32*, 0x1648, hw.blend[1]) = 4;
                M2C_NAMED(layer, s32*, 0x164C, hw.blend[2]) = 5;
                M2C_NAMED(layer, s32*, 0x1650, hw.blend[3]) = 5;
                M2C_NAMED(layer, s32*, 0x170C, dirty[0].pe) = (s32)(M2C_NAMED(layer, s32*, 0x170C, dirty[0].pe) | 1);
                M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) = (s32)(M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) | 0x40);
                M2C_NAMED(layer, s32*, 0x17C4, dirty[1].pe) = (s32)(M2C_NAMED(layer, s32*, 0x17C4, dirty[1].pe) | 1);
                M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) = (s32)(M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) | 0x40);
                layer->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(0)));
                M2C_NAMED(layer, s32*, 0x1998, unk1998) = 0x80;
                layer->beginSurface(0x18U);
                for (i = 0; i < 4; i++) {
                    lightPosition3f32(pos.x + size, GC_FUSED(size, widthArray[i][0]) + pos.y, GC_FUSED(size, widthArray[i][1]) + pos.z);
                    lightColor4u8(col.r, col.g, col.b, 0xFF);
                }
                for (i = 0; i < 4; i++) {
                    lightPosition3f32(pos.x - size, GC_FUSED(size, widthArray[3 - i][0]) + pos.y, GC_FUSED(size, widthArray[3 - i][1]) + pos.z);
                    lightColor4u8(col.r, col.g, col.b, 0xFF);
                }
                for (i = 0; i < 4; i++) {
                    lightPosition3f32(GC_FUSED(size, widthArray[i][0]) + pos.x, pos.y + size, GC_FUSED(size, widthArray[i][1]) + pos.z);
                    lightColor4u8(col.r, col.g, col.b, 0xFF);
                }
                for (i = 0; i < 4; i++) {
                    lightPosition3f32(GC_FUSED(size, widthArray[3 - i][0]) + pos.x, pos.y - size, GC_FUSED(size, widthArray[3 - i][1]) + pos.z);
                    lightColor4u8(col.r, col.g, col.b, 0xFF);
                }
                for (i = 0; i < 4; i++) {
                    lightPosition3f32(GC_FUSED(size, widthArray[i][0]) + pos.x, GC_FUSED(size, widthArray[i][1]) + pos.y, pos.z + size);
                    lightColor4u8(col.r, col.g, col.b, 0xFF);
                }
                for (i = 0; i < 4; i++) {
                    lightPosition3f32(GC_FUSED(size, widthArray[3 - i][0]) + pos.x, GC_FUSED(size, widthArray[3 - i][1]) + pos.y, pos.z - size);
                    lightColor4u8(col.r, col.g, col.b, 0xFF);
                }
                layer->endSurface();
                if (selected != 0) {
                    M2C_NAMED(layer, s32*, 0x1998, unk1998) = 0xA8;
                    M2C_NAMED(layer, s8*, 0xD34, hw.lineWidth) = 0xC;
                    M2C_NAMED(layer, s32*, 0xD38, hw.lineOffset) = 0;
                    M2C_NAMED(layer, s32*, 0x16AC, dirty[0].geom) = (s32)(M2C_NAMED(layer, s32*, 0x16AC, dirty[0].geom) | 4);
                    M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) = (s32)(M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) | 1);
                    M2C_NAMED(layer, s32*, 0x1764, dirty[1].geom) = (s32)(M2C_NAMED(layer, s32*, 0x1764, dirty[1].geom) | 4);
                    M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) = (s32)(M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) | 1);
                    layer->beginSurface(6U);
                    FIFO_F32(pos.x);
                    FIFO_F32(pos.y - 100.0f);
                    FIFO_F32(pos.z);
                    FIFO_U8(255);
                    FIFO_U8(0);
                    FIFO_U8(0);
                    FIFO_U8(0xFF);
                    FIFO_F32(pos.x);
                    FIFO_F32(pos.y + 100.0f);
                    FIFO_F32(pos.z);
                    FIFO_U8(255);
                    FIFO_U8(0);
                    FIFO_U8(0);
                    FIFO_U8(0xFF);
                    FIFO_F32(pos.x - 100.0f);
                    FIFO_F32(pos.y);
                    FIFO_F32(pos.z);
                    FIFO_U8(0);
                    FIFO_U8(255);
                    FIFO_U8(0);
                    FIFO_U8(0xFF);
                    FIFO_F32(pos.x + 100.0f);
                    FIFO_F32(pos.y);
                    FIFO_F32(pos.z);
                    FIFO_U8(0);
                    FIFO_U8(255);
                    FIFO_U8(0);
                    FIFO_U8(0xFF);
                    FIFO_F32(pos.x);
                    FIFO_F32(pos.y);
                    FIFO_F32(pos.z - 100.0f);
                    FIFO_U8(0);
                    FIFO_U8(0);
                    FIFO_U8(255);
                    FIFO_U8(0xFF);
                    FIFO_F32(pos.x);
                    FIFO_F32(pos.y);
                    FIFO_F32(pos.z + 100.0f);
                    FIFO_U8(0);
                    FIFO_U8(0);
                    FIFO_U8(255);
                    FIFO_U8(0xFF);
                    layer->endSurface();
                }
                if (GSlightGetType(light) == 1) {
                    PSVECScale((const Vec*)&dir, (Vec*)&dir, 10.0f);
                    M2C_NAMED(layer, s32*, 0x1998, unk1998) = 0xB0;
                    M2C_NAMED(layer, s8*, 0xD34, hw.lineWidth) = 0xC;
                    M2C_NAMED(layer, s32*, 0xD38, hw.lineOffset) = 0;
                    M2C_NAMED(layer, s32*, 0x16AC, dirty[0].geom) = (s32)(M2C_NAMED(layer, s32*, 0x16AC, dirty[0].geom) | 4);
                    M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) = (s32)(M2C_NAMED(layer, s32*, 0x16A8, dirty[0].groups) | 1);
                    M2C_NAMED(layer, s32*, 0x1764, dirty[1].geom) = (s32)(M2C_NAMED(layer, s32*, 0x1764, dirty[1].geom) | 4);
                    M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) = (s32)(M2C_NAMED(layer, s32*, 0x1760, dirty[1].groups) | 1);
                    layer->beginSurface(2U);
                    FIFO_F32(pos.x);
                    FIFO_F32(pos.y);
                    FIFO_F32(pos.z);
                    FIFO_COLOR(col);
                    FIFO_F32(pos.x - dir.x);
                    FIFO_F32(pos.y - dir.y);
                    FIFO_F32(pos.z - dir.z);
                    FIFO_COLOR(col);
                    layer->endSurface();
                }
            }
        }
    }
}

static void lightEditorSaveUnused(s32 layer, s32 y, s32 color) {
    GSprint(layer, 0x14, y, color, "save");
}

void LightEditor::editCommand() {
    GXColor color;
    GSlight* light;
    GSvec pos;
    const char* name;
    bool hasPos;
    GSvec target;
    GSstreamFileOutput out;

    if (!(GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x100)) {
        return;
    }
    if (!out.open("lightinfo.txt")) {
        return;
    }
    out.writePrintf("//type, color, pos/dir\n");
    for (s32 i = 0; i < lightGetLightSize(); i++) {
        bool shadow;
        light = (GSlight*)lightGetLight(i);
        shadow = GSresGetResourceAllGroup(floorDataBiosGetShadowLightID((FloorData*)floorDataBiosGetCurrentPtr())) == light;
        hasPos = false;
        switch (GSlightGetType(light)) {
        case 0:
            name = "Amb";
            break;
        case 1:
            name = "Dir";
            hasPos = true;
            break;
        case 2:
            name = "Pnt";
            hasPos = true;
            break;
        case 3:
            name = "Spt";
            hasPos = true;
            break;
        default:
            name = "???";
            break;
        }
        GSlightGetPosition(light, (f32*)&pos);
        GSlightGetTarget(light, (f32*)&target);
        GSlightGetColor(light, &color);
        out.writePrintf("%s: ", name);
        out.writePrintf("(%d,%d,%d) ", color.r, color.b, color.g);
        if (hasPos) {
            out.writePrintf("(%.2f,%.2f,%.2f)", pos.x, pos.y, pos.z);
        }
        if (shadow) {
            out.writePrintf("\t// shadow light");
        }
        out.writePrintf("\n");
    }
}

void LightEditor::editType(GSlight* light) {
    s32 type;
    s32 next;

    if (M2C_FIELD(this, s8 *, 1) != 0) {
        return;
    }
    if (GSresGetResourceAllGroup(floorDataBiosGetShadowLightID((FloorData*)floorDataBiosGetCurrentPtr())) == light) {
        return;
    }
    type = GSlightGetType(light);
    next = 0xFF;
    if (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x400) {
        if (type == 0) {
            next = 3;
        } else if (type == 1) {
            next = 0;
        } else if (type == 2) {
            next = 1;
        } else if (type == 3) {
            next = 2;
        }
    }
    if (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x800) {
        if (type == 0) {
            next = 1;
        } else if (type == 1) {
            next = 2;
        } else if (type == 2) {
            next = 3;
        } else if (type == 3) {
            next = 0;
        }
    }
    if (next != 0xFF) {
        GSlightSetType(light, next);
    }
}

void LightEditor::editPosition(GSlight* p0) {
    f32* sel;
    GScamera* cam;
    f32 ry;
    f32 step;
    f32 dx;
    f32 dy;
    f32 dt;
    f32 rx;
    f32 scale;
    f32 a0;
    f32 a1;
    Vec pos;
    Vec sum;
    Vec va;
    Vec vb;
    Vec vc;
    Vec front;
    Vec up;
    Vec cross;
    Vec tmp;

    dt = GSgfxVideoGetLastRenderTime();
    scale = 64.0f;
    cam = GScameraGetActiveCamera();
    GScameraGetPosition(cam, &pos.x);
    GScameraGetFrontVector(cam, &front.x);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    PSVECCrossProduct(&front, &up, &cross);
    PSVECCrossProduct(&front, &cross, &up);
    va.x = 0.0f;
    va.y = 0.0f;
    va.z = 0.0f;
    vb.x = 0.0f;
    vb.y = 0.0f;
    vb.z = 0.0f;
    vc.x = 0.0f;
    vc.y = 0.0f;
    vc.z = 0.0f;
    GSlightGetPosition(p0, &pos.x);
    dx = dt * (f32) GSinputGetLeftStickXData(1, 0);
    dy = dt * (f32) GSinputGetLeftStickYData(1, 0);
    rx = dt * (f32) GSinputGetRightStickXData(1, 0);
    ry = dt * (f32) GSinputGetRightStickYData(1, 0);
    if (rx < 0.0f) {
        a1 = -rx;
    } else {
        a1 = rx;
    }
    if (dx < 0.0f) {
        a0 = -dx;
    } else {
        a0 = dx;
    }
    if (a0 < a1) {
        dx = rx;
    }
    if (GSinputButtonsPressed(1) & 0x40) {
        scale *= 0.25;
    }
    va.x = cross.x;
    va.y = cross.y;
    va.z = cross.z;
    PSVECScale(&va, &va, dx / scale);
    vb.x = up.x;
    vb.y = up.y;
    vb.z = up.z;
    PSVECScale(&vb, &vb, dy / scale);
    vc.x = front.x;
    vc.y = front.y;
    vc.z = front.z;
    PSVECScale(&vc, &vc, -ry / scale);
    PSVECAdd(&va, &vb, &sum);
    PSVECAdd(&sum, &vc, &sum);
    PSVECAdd(&pos, &sum, &pos);
    if ((s32) M2C_FIELD(this, s8 *, 1) == 2) {
        sel = NULL;
        step = 0.1f;
        switch (M2C_FIELD(this, s8 *, 2)) {
        case 0:
            sel = &pos.x;
            break;
        case 1:
            sel = &pos.y;
            break;
        case 2:
            sel = &pos.z;
            break;
        }
        if (sel != NULL) {
            if (GSinputButtonsPressed(1) & 0x40) {
                step = 1.0f;
            }
            if (GSinputButtonsRepeat(1) & 0x400) {
                *sel -= step;
            }
            if (GSinputButtonsRepeat(1) & 0x800) {
                *sel += step;
            }
        }
    }
    if (GSinputButtonsRepeat(1) & 0x10) {
        M2C_FIELD(this, s8 *, 3) = (s8) ((s8) M2C_FIELD(this, s8 *, 3) == 0);
        if ((s8) M2C_FIELD(this, s8 *, 3) != 0) {
            peopleGetPos(0, 0x64, (GSvec*)&pos);
            pos.y += 18.0f;
        } else {
            GScamera* cam2 = GScameraGetActiveCamera();
            GScameraGetPosition(cam2, &pos.x);
            GScameraGetFrontVector(cam2, &tmp.x);
            PSVECScale(&tmp, &tmp, 50.0f);
            PSVECAdd(&pos, &tmp, &pos);
        }
    }
    GSlightSetPosition(p0, &pos.x);
}

struct MtxBox {
    f32 m[3][4];
};

void LightEditor::editDirection(GSlight* p0) {
    s32 i;
    s32 sel;
    s32 maxNum;
    s32 pressed;
    f32 dt;
    f32 stepX;
    f32 stepY;
    f32 rotY;
    f32 rotX;
    f32 scale;
    Mtx acc;
    MtxBox copy;
    Mtx rotB;
    Mtx rotA;
    Vec pos;
    Vec dir;
    Vec cross;
    Vec up;

    dt = GSgfxVideoGetLastRenderTime();
    scale = 1000.0f;
    pressed = GSinputButtonsPressed(1) & GSinputButtonsChanged(1);
    maxNum = peopleBiosGetMaxNum();
    sel = M2C_FIELD(this, s8 *, 4);
    if (pressed & 0x20) {
        for (i = 0; i < maxNum; i++) {
            sel += 1;
            if (sel >= maxNum) {
                sel = 0;
            }
            if (peopleBiosGetState(peopleBiosGetWorkPtr(sel)) == 3U) {
                M2C_FIELD(this, u8 *, 4) = (u8) sel;
                break;
            }
        }
    }
    GSlightGetPosition(p0, &pos.x);
    dir.x = pos.x;
    dir.y = pos.y;
    dir.z = pos.z;
    PSVECNormalize(&dir, &dir);
    stepX = dt * (f32) GSinputGetLeftStickXData(1, 0);
    stepY = dt * (f32) GSinputGetLeftStickYData(1, 0);
    GSinputGetRightStickXData(1, 0);
    GSinputGetRightStickYData(1, 0);
    if (!(GSinputButtonsPressed(1) & 0x40)) {
        scale *= 4.0f;
    }
    rotX = stepX / scale;
    rotY = stepY / scale;
    dir.x = pos.x;
    dir.y = pos.y;
    dir.z = pos.z;
    PSVECNormalize(&dir, &dir);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    if ((dir.x < 0.00001f) && (dir.x > -0.00001f) && (dir.z < 0.00001f) && (dir.z > -0.00001f)) {
        if (dir.y > 0.0f) {
            up.x = 1.0f;
            up.y = 0.0f;
            up.z = 0.0f;
        } else {
            up.x = 1.0f;
            up.y = 0.0f;
            up.z = 0.0f;
        }
    }
    PSVECCrossProduct(&dir, &up, &cross);
    PSMTXRotAxisRad(rotA, &cross, -rotY);
    copy = *(MtxBox*)rotA;
    PSMTXCopy(copy.m, acc);
    PSMTXRotRad(rotB, 0x59, rotX);
    PSMTXConcat(rotB, acc, acc);
    PSMTXMultVec(acc, &pos, &pos);
    GSlightSetPosition(p0, &pos.x);
}
}

static void lightEditorStepUnused(f32* v) {
    f32 step = 0.1f;
    if (GSinputButtonsPressed(1) & 0x40) {
        step = 1.0f;
    }
    *v += step;
}
