#include <dolphin/types.h>
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
enum Mtx { Mtx_draft_dummy };
struct PeopleWork;
struct Vec;

extern "C++" {
struct FloorData {
    u8 _draft[1];
};
struct GScamera {
    u8 _draft[1];
};
struct GSgfxLayer {
    u8 _draft[1];
    s32 endSurface();
    s32 beginSurface(unsigned short);
    void setRenderStateAndSelect(GSgfxVF*);
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSlight {
    u8 _draft[1];
};
struct GSstreamFileOutput {
    u8 _draft[1];
    bool open(const char*);
    GSstreamFileOutput();
    ~GSstreamFileOutput();
    bool writePrintf(const char*, ...);
};
struct GSvec {
    u8 _draft[1];
};
struct GXColor {
    u8 _draft[1];
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
    void dispInfo(GSlight*, long, long, bool);
    void editCommand();
};
struct PeopleWork {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
};

extern "C" {
GScamera* GScameraGetActiveCamera(void);
void GScameraGetFrontVector(GScamera* camera, f32* front);
void GScameraGetPosition(GScamera* camera, f32* position);
void GScameraLoadActiveCameraMatrix(GSgfxLayerID id);
int GSgfxLayerFindByID(int id);
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

struct _struct_widthArray_S2051_0x8 {
     f32 unk0;                             
     f32 unk4;                             
};
static struct _struct_widthArray_S2051_0x8 widthArray_S2051[4] = { { -1.0f, -1.0f }, { 1.0f, -1.0f }, { 1.0f, 1.0f }, { -1.0f, 1.0f } };
void LightEditor::editDirection(GSlight* p0) {
    s32 var_r29;
    s32 var_r30;
    volatile s32 sp3C;
    volatile s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    volatile s32 sp64;
    s32 unksp14;
    volatile s32 spC8;
    volatile s32 spC4;
    f32 sp2C;
    s32 spBC;
    s32 spB8;
    s32 spB4;
    s32 spB0;
    s32 spAC;
    s32 spA8;
    s32 spA4;
    volatile s32 spA0;
    volatile s32 sp9C;
    s32 sp98;
    s32 sp68;
    s32 sp38;
    s32 spC0;
    f32 sp28;
    volatile f32 sp24;
    f32 sp20;
    volatile f32 sp10;
    f32 spC;
    volatile f32 sp8;
    u32 sp30;
    f32 temp_f31;
    f32 temp_f31_2;
    s32 temp_r28_2;
    s32 temp_r28_3;
    f32 temp_f30;
    s32 sp34;
    f32 var_f28;

    temp_f31 = GSgfxVideoGetLastRenderTime();
    var_f28 = 1000.0f;
    temp_r28_2 = GSinputButtonsPressed(1) & (u32)(GSinputButtonsChanged(1));
    temp_r28_3 = peopleBiosGetMaxNum();
    var_r30 = (u8) M2C_FIELD(this, u8 *, 4);
    if (temp_r28_2 & 0x20) {
        var_r29 = 0;
loop_7:
        if (var_r29 < temp_r28_3) {
            var_r30 += 1;
            if (temp_r28_3 <= var_r30) {
                var_r30 = 0;
            }
            if (peopleBiosGetState((PeopleWork*)(peopleBiosGetWorkPtr((s32) var_r30))) == 3U) {
                M2C_FIELD(this, u8 *, 4) = (u8) var_r30;
            } else {
                var_r29 += 1;
                goto loop_7;
            }
        }
    }
    GSlightGetPosition((GSlight*)(p0), (f32*)(&sp2C));
    sp20 = sp2C;
    sp24 = sp30;
    sp28 = sp34;
    PSVECNormalize((const register Vec*)((Vec *) &sp20), (register Vec*)((Vec *) &sp20));
    temp_f30 = temp_f31 * (f32) GSinputGetLeftStickXData(1, 0);
    temp_f31_2 = temp_f31 * (f32) GSinputGetLeftStickYData(1, 0);
    GSinputGetRightStickXData(1, 0);
    GSinputGetRightStickYData(1, 0);
    if (!(GSinputButtonsPressed(1) & 0x40)) {
        var_f28 = 1000.0f * 4.0f;
    }
    sp28 = sp34;
    sp24 = sp30;
    PSVECNormalize((const register Vec*)((Vec *) &sp20), (register Vec*)((Vec *) &sp20));
    sp20 = sp2C;
    sp8 = 0.0f;
    spC = 1.0f;
    sp10 = 0.0f;
    if ((sp20 < 0.00001f) && (sp20 > -0.00001f) && (sp28 < 0.00001f) && (sp28 > -0.00001f)) {
        if (sp24 > 0.0f) {
            sp8 = 1.0f;
            spC = 0.0f;
            sp10 = 0.0f;
        } else {
            sp8 = 1.0f;
            spC = 0.0f;
            sp10 = 0.0f;
        }
    }
    PSVECCrossProduct((const register Vec*)((Vec *) &sp20), (const register Vec*)((Vec *) &sp8), (register Vec*)(&unksp14));
    PSMTXRotAxisRad((Mtx)((s32) &sp38), (const Vec*)(&unksp14), -(temp_f31_2 / var_f28));
    sp98 = sp38;
    sp9C = sp3C;
    spA0 = sp40;
    spA4 = sp44;
    spA8 = sp48;
    spAC = sp4C;
    spB0 = sp50;
    spB4 = sp54;
    spB8 = sp58;
    spBC = sp5C;
    spC0 = sp60;
    spC4 = sp64;
    PSMTXCopy((const Mtx)((s32) &sp98), (Mtx)((s32) &spC8));
    PSMTXRotRad((Mtx)((s32) &sp68), 0x59, temp_f30 / var_f28);
    PSMTXConcat((const Mtx)((s32) &sp68), (const Mtx)((s32) &spC8), (Mtx)((s32) &spC8));
    PSMTXMultVec((const Mtx)(&spC8), (const Vec *)((const register Vec*)((Vec *) &sp2C)), (Vec *)((register Vec*)((Vec *) &sp2C)));
    GSlightSetPosition((GSlight*)(p0), (f32*)(&sp2C));
}
}

extern "C++" {
void LightEditor::editPosition(GSlight* p0) {
    s32 sp18;
    s32 sp1C;
    s32 sp30;
    s32 sp34;
    u32 unksp14;
    u8 unksp5C[sizeof(s32) + 64];
    f32 sp50;
    f32 sp2C;
    f32 sp6C;
    volatile f32 sp28;
    f32 sp20;
    f32 sp54;
    f32 sp4C;
    volatile f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp70;
    f32 sp68;
    f32 sp24;
    f32 var_f30;
    f32 sp8;
    GScamera *temp_r3;
    GScamera *temp_r3_2;
    f32 *var_r29;
    f32 var_f29;
    f32 temp_f28;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 var_f0;
    f32 var_f1;
    f32 temp_f27;
    f32 sp58;
    f32 var_f31;
    s8 temp_r0;

    temp_f30 = GSgfxVideoGetLastRenderTime();
    var_f31 = 64.0f;
    temp_r3 = GScameraGetActiveCamera();
    GScameraGetPosition((GScamera*)(temp_r3), (f32*)(&sp68));
    GScameraGetFrontVector((GScamera*)(temp_r3), (f32*)(&sp2C));
    sp20 = 0.0f;
    sp24 = 1.0f;
    sp28 = 0.0f;
    PSVECCrossProduct((const register Vec*)((Vec *) &sp2C), (const register Vec*)((Vec *) &sp20), (register Vec*)(&unksp14));
    PSVECCrossProduct((const register Vec*)((Vec *) &sp2C), (const register Vec*)(&unksp14), (register Vec*)((Vec *) &sp20));
    sp48 = 0.0f;
    sp50 = 0.0f;
    sp54 = 0.0f;
    sp58 = 0.0f;
    sp44 = 0.0f;
    sp4C = 0.0f;
    sp38 = 0.0f;
    sp3C = 0.0f;
    sp40 = 0.0f;
    GSlightGetPosition((GSlight*)(p0), (f32*)(&sp68));
    var_f29 = temp_f30 * (f32) GSinputGetLeftStickXData(1, 0);
    temp_f28 = (f32) GSinputGetLeftStickYData(1, 0);
    temp_f28 *= temp_f30;
    temp_f27 = temp_f30 * (f32) GSinputGetRightStickXData(1, 0);
    temp_f30_2 = temp_f30 * (f32) GSinputGetRightStickYData(1, 0);
    if (temp_f27 < 0.0f) {
        var_f1 = -temp_f27;
    } else {
        var_f1 = temp_f27;
    }
    if (var_f29 < 0.0f) {
        var_f0 = -var_f29;
    } else {
        var_f0 = var_f29;
    }
    if (var_f0 < var_f1) {
        var_f29 = temp_f27;
    }
    if (GSinputButtonsPressed(1) & 0x40) {
        var_f31 = (f32) (5.51221563e-315 * 0.25);
    }
    sp50 = unksp14;
    sp54 = sp18;
    sp58 = sp1C;
    PSVECScale((const register Vec*)((Vec *) &sp50), (register Vec*)((Vec *) &sp50), var_f29 / var_f31);
    sp48 = sp24;
    sp4C = sp28;
    PSVECScale((const register Vec*)((Vec *) &sp44), (register Vec*)((Vec *) &sp44), temp_f28 / var_f31);
    sp38 = sp2C;
    sp44 = sp20;
    sp3C = sp30;
    sp40 = sp34;
    PSVECScale((const register Vec*)((Vec *) &sp38), (register Vec*)((Vec *) &sp38), -temp_f30_2 / var_f31);
    PSVECAdd((const register Vec*)((Vec *) &sp50), (const register Vec*)((Vec *) &sp44), (register Vec*)(&unksp5C));
    PSVECAdd((const register Vec*)((Vec *) &sp68), (const register Vec*)(&unksp5C), (register Vec*)((Vec *) &sp68));
    PSVECAdd((const register Vec*)(&unksp5C), (const register Vec*)((Vec *) &sp38), (register Vec*)(&unksp5C));
    if ((s32) M2C_FIELD(this, s8 *, 1) == 2) {
        temp_r0 = M2C_FIELD(this, s8 *, 2);
        var_r29 = NULL;
        var_f30 = 0.1f;
        switch ((s8) temp_r0) {
        case 0:
            var_r29 = &sp68;
            break;
        case 1:
            var_r29 = &sp6C;
            break;
        case 2:
            var_r29 = &sp70;
            break;
        }
        if (var_r29 != NULL) {
            if (GSinputButtonsPressed(1) & 0x40) {
                var_f30 = 1.0f;
            }
            if (GSinputButtonsRepeat(1) & 0x400) {
                *var_r29 -= var_f30;
            }
            if (GSinputButtonsRepeat(1) & 0x800) {
                *var_r29 += var_f30;
            }
        }
    }
    if (GSinputButtonsRepeat(1) & 0x10) {
        M2C_FIELD(this, s8 *, 3) = (s8) ((s8) M2C_FIELD(this, s8 *, 3) == 0);
        if ((s8) M2C_FIELD(this, s8 *, 3) != 0) {
            peopleGetPos(0, 0x64, (GSvec*)((GSvec *) &sp68));
            sp6C += 18.0f;
        } else {
            temp_r3_2 = GScameraGetActiveCamera();
            GScameraGetPosition((GScamera*)(temp_r3_2), (f32*)(&sp68));
            GScameraGetFrontVector((GScamera*)(temp_r3_2), (f32*)(&sp8));
            PSVECScale((const register Vec*)((Vec *) &sp8), (register Vec*)((Vec *) &sp8), 50.0f);
            PSVECAdd((const register Vec*)((Vec *) &sp68), (const register Vec*)((Vec *) &sp8), (register Vec*)((Vec *) &sp68));
        }
    }
    GSlightSetPosition((GSlight*)(p0), (f32*)(&sp68));
}
}

extern "C++" {
void LightEditor::editType(GSlight* p0) {
    s32 temp_r30;
    s32 var_r29;

    if (((s8) M2C_FIELD(this, u8 *, 1) == 0) && (GSresGetResourceAllGroup(floorDataBiosGetShadowLightID((FloorData*)(floorDataBiosGetCurrentPtr()))) != p0)) {
        temp_r30 = GSlightGetType((GSlight*)((u16)p0));
        var_r29 = 0xFF;
        if (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x400) {
            switch (temp_r30) {
            case 0:
                var_r29 = 3;
                break;
            case 1:
                var_r29 = 0;
                break;
            case 2:
                var_r29 = 1;
                break;
            case 3:
                var_r29 = 2;
                break;
            }
        }
        if (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x800) {
            switch (temp_r30) {
            case 0:
                var_r29 = 1;
                break;
            case 1:
                var_r29 = 2;
                break;
            case 2:
                var_r29 = 3;
                break;
            case 3:
                var_r29 = 0;
                break;
            }
        }
        if (var_r29 != 0xFF) {
            GSlightSetType((GSlight*)(p0), var_r29);
        }
    }
}
}

extern "C++" {
void LightEditor::editCommand() {
    f32 sp1C;
    f32 sp20;
    volatile f32 sp9;
    f32 sp18;
    f32 unksp24;
    f32 unksp8;
    f32 spA;
    f32 spC;
    u8 temp_ret;
    s32 *var_r29;
    s32 var_r28;
    s32 temp_r3;
    s32 var_r27;
    s8 *temp_r4;
    f32 var_f1;
    GSlight *temp_r26;
    bool temp_r31_2;

    temp_r4 = (signed char *)("lightinfo.txt");
    ((GSstreamFileOutput*)(&unksp24))->GSstreamFileOutput();
    if (!(GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x100)) {
        ((GSstreamFileOutput*)(&unksp24))->~GSstreamFileOutput();
        return;
    }
    temp_ret = ((GSstreamFileOutput*)(&unksp24))->open((const char*)((u16)temp_r4));
    if (temp_ret == 0) {
        ((GSstreamFileOutput*)(&unksp24))->~GSstreamFileOutput();
        return;
    }
    ((GSstreamFileOutput*)(&unksp24))->writePrintf((const char*)(temp_r4 + 0x10), M2C_BITWISE(f32, temp_ret));
    var_r27 = 0;
    while (var_r27 < lightGetLightSize()) {
        temp_r26 = (GSlight *)(lightGetLight(var_r27));
        temp_r31_2 = GSresGetResourceAllGroup(floorDataBiosGetShadowLightID((FloorData*)(floorDataBiosGetCurrentPtr()))) == temp_r26;
        var_r28 = 0;
        temp_r3 = GSlightGetType((GSlight*)(temp_r26));
        switch (temp_r3) {
        case 0:
            var_r29 = (long *)("Amb");
            break;
        case 1:
            var_r29 = (long *)("Dir");
            var_r28 = 1;
            break;
        case 2:
            var_r29 = (long *)("Pnt");
            var_r28 = 1;
            break;
        case 3:
            var_r29 = (long *)("Spt");
            var_r28 = 1;
            break;
        default:
            var_r29 = (long *)("???");
            break;
        }
        GSlightGetPosition((GSlight*)(temp_r26), (f32*)(&sp18));
        GSlightGetTarget((GSlight*)(temp_r26), (f32*)(&spC));
        GSlightGetColor((GSlight*)(temp_r26), (GXColor*)(&unksp8));
        var_f1 = M2C_BITWISE(f32, ((GSstreamFileOutput*)(&unksp24))->writePrintf((const char*)(temp_r4 + 0x28), unksp8, spA, sp9, M2C_BITWISE(f32, ((GSstreamFileOutput*)(&unksp24))->writePrintf((const char*)("%s: "), var_r29))));
        if (var_r28 != 0) {
            var_f1 = M2C_BITWISE(f32, ((GSstreamFileOutput*)(&unksp24))->writePrintf((const char*)(temp_r4 + 0x34), sp18, sp1C, sp20));
        }
        if (temp_r31_2 != 0) {
            var_f1 = M2C_BITWISE(f32, ((GSstreamFileOutput*)(&unksp24))->writePrintf((const char*)(temp_r4 + 0x48), var_f1));
        }
        ((GSstreamFileOutput*)(&unksp24))->writePrintf((const char*)("\n"), var_f1);
        var_r27 += 1;
    }
    ((GSstreamFileOutput*)(&unksp24))->~GSstreamFileOutput();
}
}

extern "C++" {
extern "C++" {
extern "C++" {
void LightEditor::editUpdate() {
    u32 sp8;
    s32 sp14;
    u8 sp12;
    u8 sp11;
    s32 var_r29;
    s32 unksp10;
    GSgfxLayer *temp_r3_6;
    GSlight *temp_r3_3;
    f32 temp_f1;
    u16 temp_r30;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_7;
    u32 spC;
    s32 var_r29_2;
    s32 var_r31;
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
            M2C_FIELD(this, u8 *, 0) = (u8) (M2C_FIELD(this, u8 *, 0) + 1);
        }
        if ((s8) M2C_FIELD(this, u8 *, 0) >= lightGetLightSize()) {
            M2C_FIELD(this, u8 *, 0) = -1U;
        }
        if (temp_r3 & 8) {
            M2C_FIELD(this, u8 *, 0) = (u8) (M2C_FIELD(this, u8 *, 0) - 1);
        }
        if ((s8) M2C_FIELD(this, u8 *, 0) < -1) {
            M2C_FIELD(this, u8 *, 0) = (u8) (lightGetLightSize() - 1);
        }
        temp_r3_2 = M2C_FIELD(this, u8 *, 0);
        if ((s8) temp_r3_2 < 0) {
            ((LightEditor*)(this))->editCommand();
            goto block_59;
        }
        temp_r3_3 = (GSlight *)(lightGetLight((s32) temp_r3_2));
        if (temp_r3_3 != NULL) {
            temp_r31 = GSlightGetType((GSlight*)(temp_r3_3));
            if (temp_r3 & 2) {
                temp_r3_4 = M2C_FIELD(this, u8 *, 1);
                switch (temp_r3_4) {
                case 0:
                    M2C_FIELD(this, u8 *, 1) = 1U;
                    M2C_FIELD(this, u8 *, 2) = 0U;
                    break;
                case 1:
                    M2C_FIELD((u8)this, u8 *, 2) = (u8) (M2C_FIELD((u16)this, u8 *, 2) + 1);
                    if ((s8) M2C_FIELD(this, u8 *, 2) > 2) {
                        if (temp_r31 == 0) {
                            M2C_FIELD(this, u8 *, 1) = 0U;
                        } else {
                            M2C_FIELD(this, u8 *, 1) = 2U;
                        }
                        M2C_FIELD(this, u8 *, 2) = 0U;
                    }
                    break;
                case 2:
                    M2C_FIELD((u8)this, u8 *, 2) = (u8) (M2C_FIELD((u16)this, u8 *, 2) + 1);
                    if ((s8) M2C_FIELD(this, u8 *, 2) > 2) {
                        M2C_FIELD(this, u8 *, 1) = 0U;
                        M2C_FIELD(this, u8 *, 2) = 0U;
                    }
                    break;
                }
            }
            if (temp_r3 & 1) {
                temp_r3_5 = M2C_FIELD(this, u8 *, 1);
                switch (temp_r3_5) {
                case 0:
                    if (temp_r31 == 0) {
                        M2C_FIELD(this, u8 *, 1) = 1U;
                        M2C_FIELD(this, u8 *, 2) = 2U;
                    } else {
                        M2C_FIELD(this, u8 *, 1) = 2U;
                    }
                    M2C_FIELD(this, u8 *, 2) = 2U;
                    break;
                case 1:
                    M2C_FIELD((u8)this, u8 *, 2) = (u8) (M2C_FIELD((u16)this, u8 *, 2) - 1);
                    if ((s8) M2C_FIELD(this, u8 *, 2) < 0) {
                        M2C_FIELD(this, u8 *, 1) = 0U;
                        M2C_FIELD(this, u8 *, 2) = 0U;
                    }
                    break;
                case 2:
                    M2C_FIELD((u8)this, u8 *, 2) = (u8) (M2C_FIELD((u16)this, u8 *, 2) - 1);
                    if ((s8) M2C_FIELD(this, u8 *, 2) < 0) {
                        M2C_FIELD((u8)this, u8 *, 1) = 1U;
                        M2C_FIELD(this, u8 *, 2) = 2U;
                    }
                    break;
                }
            }
            ((LightEditor*)(this))->editType((GSlight*)(temp_r3_3));
            var_r30 = NULL;
            if ((s32) M2C_FIELD(this, u8 *, 1) == 1) {
                GSlightGetColor((GSlight*)(temp_r3_3), (GXColor*)(&unksp10));
                temp_r0 = M2C_FIELD(this, u8 *, 2);
                switch ((s8) temp_r0) {
                case 0:
                    var_r30 = (unsigned char *)(&unksp10);
                    break;
                case 1:
                    var_r30 = &sp11;
                    break;
                case 2:
                    var_r30 = &sp12;
                    break;
                }
                if (var_r30 != NULL) {
                    if (GSinputButtonsRepeat(1) & 0x400) {
                        *var_r30 -= 1;
                    }
                    if (GSinputButtonsRepeat(1) & 0x800) {
                        *var_r30 += 1;
                    }
                    sp14 = unksp10;
                    GSlightSetColor((GSlight*)(temp_r3_3), (const GXColor*)((GXColor *) &sp14));
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
        temp_r30 = dbgMenuGetLayerID();
        floorGetLightInfo((u32*)(&sp8), (u32*)(&spC));
        spC = lightGetLightSize();
        temp_r3_6 = (GSgfxLayer *)(GSgfxLayerFindByID(2));
        if (temp_r3_6 != NULL) {
            GSprimSetup3DRender((GSgfxLayer*)(temp_r3_6));
        }
        var_r29 = 0;
        while (var_r29 < (s32) spC) {
            ((LightEditor*)(this))->dispLightModel((GSlight*)(lightGetLight(var_r29)), (s8) M2C_FIELD(this, u8 *, 0) == var_r29);
            var_r29 += 1;
        }
        var_r31 = 0x1E;
        var_r29_2 = 0;
        while (var_r29_2 < (s32) spC) {
            ((LightEditor*)(this))->dispInfo((GSlight*)(lightGetLight(var_r29_2)), 0x14, var_r31, (s8) M2C_FIELD(this, u8 *, 0) == var_r29_2);
            var_r31 += 0xD;
            var_r29_2 += 1;
        }
        if (temp_r30 != -1) {
            var_r6 = -1;
            if (M2C_FIELD(this, u8 *, 0) < 0) {
                var_r6 = -0x7F01;
            }
            GSprint(temp_r30, 0x14, var_r31, var_r6, (const char*)("save"));
        }
        temp_r3_7 = dbgMenuGetLayerID();
        if (temp_r3_7 != -1) {
            temp_ret = cameraGetType();
            temp_f1 = M2C_BITWISE(f32, temp_ret);
            if (temp_ret == 6) {
                GSprint((u16)temp_r3_7, 0x1F4, 0x20, -1, (const char*)("camera mode"), temp_f1);
                return;
            }
            GSprint((u16)temp_r3_7, 0x1F4, 0x20, -1, (const char*)("light mode"), temp_f1);
        }
    }
}
}

extern "C++" {
void LightEditor::init() {
    M2C_FIELD(this, s8 *, 4) = 0;
    M2C_FIELD(this, s8 *, 0) = 0;
    M2C_FIELD(this, s8 *, 1) = 0;
    M2C_FIELD(this, f32 *, 8) = 1.0f;
    M2C_FIELD(this, s8 *, 3) = 0;
}
}

extern "C++" {
LightEditor::LightEditor() {
    M2C_FIELD(this, s8 *, 4) = 0;
    M2C_FIELD(this, s8 *, 0) = 0;
    M2C_FIELD(this, s8 *, 1) = 0;
    M2C_FIELD(this, f32 *, 8) = 1.0f;
    M2C_FIELD(this, s8 *, 3) = 0;
}
}
}
}

extern "C++" {
#pragma push
#pragma dont_inline on
extern "C++" {
void LightEditor::dispInfo(GSlight* p0, long p1, long p2, bool p3) {
    f32 sp1C;
    s32 *var_r8;
    volatile s32 sp9;
    f32 sp18;
    u8 unksp8;
    volatile s32 spA;
    volatile f32 sp20;
    s32 temp_r3;
    u8 var_r29;
    s32 temp_ret;
    s32 var_r24;
    s32 var_r3;
    s32 var_r6;
    s32 var_r6_10;
    s32 var_r6_11;
    s32 var_r6_3;
    s32 var_r6_5;
    s32 var_r6_6;
    s32 var_r6_8;
    bool temp_r31;
    s32 temp_r3_2;
    u8 var_r3_2;
    u8 var_r3_3;
    u8 var_r6_2;
    u8 var_r6_4;
    u8 var_r6_7;
    u8 var_r6_9;
    f32 spC;

    var_r29 = 0;
    temp_r31 = GSresGetResourceAllGroup(floorDataBiosGetShadowLightID((FloorData*)(floorDataBiosGetCurrentPtr()))) == p0;
    temp_r3 = dbgMenuGetLayerID();
    if (temp_r3 != -1) {
        var_r3 = -1;
        var_r3 = p3 == 0 ? var_r3 : -0x7F01;
        GSlightGetActive((GSlight*)(p0));
        GSlightGetPosition((GSlight*)(p0), (f32*)(&sp18));
        GSlightGetTarget((GSlight*)(p0), (f32*)(&spC));
        GSlightGetColor((GSlight*)(p0), (GXColor*)(&unksp8));
        GSlightCanAnimate((GSlight*)(p0));
        temp_ret = GSlightGetType((GSlight*)(p0));
        temp_r3_2 = temp_ret;
        switch (temp_r3_2) {
        case 0:
            var_r8 = (long *)("Amb");
            break;
        case 1:
            var_r8 = (long *)("Dir");
            var_r29 = 1;
            break;
        case 2:
            var_r8 = (long *)("Pnt");
            var_r29 = 1;
            break;
        case 3:
            var_r8 = (long *)("Spt");
            var_r29 = 1;
            break;
        default:
            var_r8 = (long *)("???");
            break;
        }
        var_r6 = -1;
        var_r6 = !((s8) M2C_FIELD(this, u8 *, 1) == 0) ? var_r6 : var_r3;
        GSprint(temp_r3, p1, p2, var_r6, (const char*)("%s:"), var_r8, M2C_BITWISE(f32, temp_ret));
        var_r6_2 = 0;
        var_r6_2 = !(((s8) M2C_FIELD((s32)this, u8 *, 2) == 0) && ((s32) M2C_FIELD(this, u8 *, 1) == 1)) ? var_r6_2 : 1;
        var_r6_3 = -1;
        var_r6_3 = var_r6_2 == 0 ? var_r6_3 : var_r3;
        GSprint(temp_r3, p1 + 0x34, p2, var_r6_3, (const char*)("(%02x,"), unksp8);
        var_r6_4 = 0;
        if (!(((s32) M2C_FIELD(this, u8 *, 2) == 1) && ((s32) M2C_FIELD(this, u8 *, 1) == 1))) {
            var_r6_4 = var_r6_4;
        } else {
            var_r6_4 = 1;
        }
        var_r6_5 = -1;
        var_r6_5 = var_r6_4 == 0 ? var_r6_5 : var_r3;
        GSprint(temp_r3, p1 + 0x5B, p2, var_r6_5, (const char*)("%02x,"), sp9);
        var_r3_2 = 0;
        var_r3_2 = !(((s32) M2C_FIELD(this, u8 *, 2) == 2) && ((s32) M2C_FIELD(this, u8 *, 1) == 1)) ? var_r3_2 : 1;
        var_r6_6 = -1;
        var_r6_6 = var_r3_2 == 0 ? var_r6_6 : var_r3;
        GSprint(temp_r3, p1 + 0x7A, p2, var_r6_6, (const char*)("%02x)"), spA);
        var_r24 = var_r6_6;
        if (var_r29 != 0) {
            var_r6_7 = 0;
            var_r6_7 = !(((s8) M2C_FIELD(this, u8 *, 2) == 0) && ((s32) M2C_FIELD(this, u8 *, 1) == 2)) ? var_r6_7 : 1;
            var_r6_8 = -1;
            var_r6_8 = var_r6_7 == 0 ? var_r6_8 : var_r3;
            GSprint(temp_r3, p1 + 0xB6, p2, var_r6_8, (const char*)("(%.2f,"), sp18);
            var_r6_9 = 0;
            var_r6_9 = !(((s32) M2C_FIELD(this, u8 *, 2) == 1) && ((s32) M2C_FIELD(this, u8 *, 1) == 2)) ? var_r6_9 : 1;
            var_r6_10 = -1;
            var_r6_10 = var_r6_9 == 0 ? var_r6_10 : var_r3;
            GSprint(temp_r3, p1 + 0xF7, p2, var_r6_10, (const char*)(" %.2f,"), sp1C);
            var_r3_3 = 0;
            var_r3_3 = !(((s32) M2C_FIELD(this, u8 *, 2) == 2) && ((s32) M2C_FIELD(this, u8 *, 1) == 2)) ? var_r3_3 : 1;
            var_r6_11 = -1;
            var_r6_11 = var_r3_3 == 0 ? var_r6_11 : var_r3;
            var_r24 = var_r6_11;
            GSprint(temp_r3, p1 + 0x130, p2, var_r6_11, (const char*)(" %.2f)"), sp20);
        }
        if (temp_r31 != 0) {
            GSprint(temp_r3, p1 + 0x17E, p2, var_r24, (const char*)("(shadow)"));
        }
    }
}
}
#pragma pop
}

extern "C++" {
void LightEditor::dispLightModel(GSlight* p0, bool p1) {
    f32 var_f31;
    f32 sp9;
    f32 spA;
    f32 unksp8;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    PeopleWork *temp_r3;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 var_f0;
    f32 sp44;
    s32 temp_r3_3;
    struct _struct_widthArray_S2051_0x8 *temp_r11;
    struct _struct_widthArray_S2051_0x8 *temp_r11_2;
    struct _struct_widthArray_S2051_0x8 *temp_r11_3;
    struct _struct_widthArray_S2051_0x8 *temp_r11_4;
    struct _struct_widthArray_S2051_0x8 *temp_r4;
    struct _struct_widthArray_S2051_0x8 *temp_r4_2;
    struct _struct_widthArray_S2051_0x8 *temp_r4_3;
    struct _struct_widthArray_S2051_0x8 *temp_r4_4;
    struct _struct_widthArray_S2051_0x8 *temp_r4_5;
    struct _struct_widthArray_S2051_0x8 *temp_r4_6;
    struct _struct_widthArray_S2051_0x8 *temp_r4_7;
    struct _struct_widthArray_S2051_0x8 *temp_r4_8;
    u8 *temp_r3_2;

    var_f31 = 0.5f;
    if (GSlightGetActive((GSlight*)(p0)) != 0) {
        if (p1 != 0) {
            if (((f32) sin((f64) M2C_FIELD(this, f32 *, 8)) / 2.0f) < 0.0f) {
                var_f0 = -((f32) sin((f64) M2C_FIELD(this, f32 *, 8)) / 2.0f);
            } else {
                var_f0 = (f32) sin((f64) M2C_FIELD(this, f32 *, 8)) / 2.0f;
            }
            var_f31 = 0.5f + var_f0;
            M2C_FIELD(this, f32 *, 8) = (f32) (M2C_FIELD(this, f32 *, 8) + 0.1f);
            if (M2C_FIELD(this, f32 *, 8) > 6.2831855f) {
                M2C_FIELD(this, f32 *, 8) = 0.0f;
            }
        }
        if (GSlightGetType((GSlight*)(p0)) != 0) {
            GSlightGetPosition((GSlight*)(p0), (f32*)(&sp3C));
            GSlightGetTarget((GSlight*)(p0), (f32*)(&sp24));
            GSlightGetColor((GSlight*)(p0), (GXColor*)(&unksp8));
            if (GSlightGetType((GSlight*)(p0)) == 1) {
                temp_r3 = peopleBiosGetWorkPtr((s32) (s8) M2C_FIELD(this, u8 *, 4));
                if (temp_r3 != NULL) {
                    temp_r3_2 = (unsigned char *)(peopleBiosGetPosPtr((PeopleWork*)(temp_r3)));
                    sp18 = M2C_FIELD(temp_r3_2, f32 *, 0);
                    sp1C = M2C_FIELD(temp_r3_2, f32 *, 4);
                    sp20 = M2C_FIELD(temp_r3_2, f32 *, 8);
                    sp30 = sp3C;
                    sp34 = sp40;
                    sp38 = sp44;
                    PSVECNormalize((const register Vec*)((Vec *) &sp30), (register Vec*)((Vec *) &sp30));
                    spC = sp30;
                    sp10 = sp34;
                    sp14 = sp38;
                    PSVECScale((const register Vec*)((Vec *) &spC), (register Vec*)((Vec *) &spC), 20.0f);
                    PSVECAdd((const register Vec*)((Vec *) &spC), (const register Vec*)((Vec *) &sp18), (register Vec*)((Vec *) &sp3C));
                    sp40 += 5.0f;
                }
            }
            temp_r3_3 = GSgfxLayerFindByID(2);
            if (temp_r3_3 != 0) {
                GScameraLoadActiveCameraMatrix((GSgfxLayerID)(M2C_FIELD(temp_r3_3, s32 *, 0x28)));
                M2C_FIELD(temp_r3_3, s8 *, 0x1656) = 1;
                M2C_FIELD(temp_r3_3, s8 *, 0x1657) = 1;
                M2C_FIELD(temp_r3_3, s8 *, 0x1658) = 1;
                M2C_FIELD(temp_r3_3, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x170C) | 4);
                M2C_FIELD(temp_r3_3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16A8) | 0x40);
                M2C_FIELD(temp_r3_3, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x17C4) | 4);
                M2C_FIELD(temp_r3_3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1760) | 0x40);
                M2C_FIELD(temp_r3_3, s8 *, 0x165C) = 1;
                M2C_FIELD(temp_r3_3, s32 *, 0x1660) = 1;
                M2C_FIELD(temp_r3_3, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x170C) | 8);
                M2C_FIELD(temp_r3_3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16A8) | 0x40);
                M2C_FIELD(temp_r3_3, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x17C4) | 8);
                M2C_FIELD(temp_r3_3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1760) | 0x40);
                M2C_FIELD(temp_r3_3, s32 *, 0x1664) = 7;
                M2C_FIELD(temp_r3_3, s8 *, 0x1670) = 0;
                M2C_FIELD(temp_r3_3, s32 *, 0x1668) = 0;
                M2C_FIELD(temp_r3_3, s32 *, 0x166C) = 7;
                M2C_FIELD(temp_r3_3, s8 *, 0x1671) = 0;
                M2C_FIELD(temp_r3_3, s8 *, 0x1672) = 1;
                M2C_FIELD(temp_r3_3, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x170C) | 0x10);
                M2C_FIELD(temp_r3_3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16A8) | 0x40);
                M2C_FIELD(temp_r3_3, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x17C4) | 0x10);
                M2C_FIELD(temp_r3_3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1760) | 0x40);
                M2C_FIELD(temp_r3_3, s32 *, 0xD8C) = 0;
                M2C_FIELD(temp_r3_3, s32 *, 0x16B8) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16B8) | 2);
                M2C_FIELD(temp_r3_3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16A8) | 2);
                M2C_FIELD(temp_r3_3, s32 *, 0x1770) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1770) | 2);
                M2C_FIELD(temp_r3_3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1760) | 2);
                if ((s32) M2C_FIELD(temp_r3_3, s32 *, 0x1994) != 1) {
                    M2C_FIELD(temp_r3_3, s32 *, 0x1994) = 1;
                    M2C_FIELD(temp_r3_3, s32 *, 0x1990) = (s32) (temp_r3_3 + ((M2C_FIELD(temp_r3_3, s32 *, 0x1994) * 0xBC) + 0x1818));
                }
                M2C_FIELD(temp_r3_3, s32 *, 0x1644) = 1;
                M2C_FIELD(temp_r3_3, s32 *, 0x1648) = 4;
                M2C_FIELD(temp_r3_3, s32 *, 0x164C) = 5;
                M2C_FIELD(temp_r3_3, s32 *, 0x1650) = 5;
                M2C_FIELD(temp_r3_3, s32 *, 0x170C) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x170C) | 1);
                M2C_FIELD(temp_r3_3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16A8) | 0x40);
                M2C_FIELD(temp_r3_3, s32 *, 0x17C4) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x17C4) | 1);
                M2C_FIELD(temp_r3_3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1760) | 0x40);
                ((GSgfxLayer*)((GSgfxLayer *) temp_r3_3))->setRenderStateAndSelect((GSgfxVF*)(GSgfxVFGetPredef(0)));
                M2C_FIELD(temp_r3_3, s32 *, 0x1998) = 0x80;
                ((GSgfxLayer*)((GSgfxLayer *) temp_r3_3))->beginSurface(0x18U);
                temp_f3 = sp3C + var_f31;
                temp_f4 = sp3C - var_f31;
                *(f32 *)0xCC008000 = temp_f3;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051->unk0) + sp40;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051->unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = temp_f3;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[1].unk0) + sp40;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[1].unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = temp_f3;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[2].unk0) + sp40;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[2].unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = temp_f3;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[3].unk0) + sp40;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[3].unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = temp_f4;
                temp_r4 = &widthArray_S2051[3 - 0];
                temp_f3_2 = sp40 + var_f31;
                *(f32 *)0xCC008000 = (var_f31 * temp_r4->unk0) + sp40;
                temp_r4_2 = &widthArray_S2051[3 - 1];
                *(f32 *)0xCC008000 = (var_f31 * temp_r4->unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = temp_f4;
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_2->unk0) + sp40;
                temp_r4_3 = &widthArray_S2051[3 - 2];
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_2->unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = temp_f4;
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_3->unk0) + sp40;
                temp_r4_4 = &widthArray_S2051[3 - 3];
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_3->unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = temp_f4;
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_4->unk0) + sp40;
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_4->unk4) + sp44;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = unksp8;
                temp_f4_2 = sp40 - var_f31;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051->unk0) + sp3C;
                *(f32 *)0xCC008000 = temp_f3_2;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[1].unk0) + sp3C;
                *(f32 *)0xCC008000 = temp_f3_2;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051->unk4) + sp44;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[1].unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[2].unk0) + sp3C;
                *(f32 *)0xCC008000 = temp_f3_2;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[2].unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[3].unk0) + sp3C;
                *(f32 *)0xCC008000 = temp_f3_2;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[3].unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                temp_f3_3 = sp44 + var_f31;
                temp_r4_5 = &widthArray_S2051[3 - 0];
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_5->unk0) + sp3C;
                *(f32 *)0xCC008000 = temp_f4_2;
                temp_r4_6 = &widthArray_S2051[3 - 1];
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_5->unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_6->unk0) + sp3C;
                *(f32 *)0xCC008000 = temp_f4_2;
                temp_r4_7 = &widthArray_S2051[3 - 2];
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_6->unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_7->unk0) + sp3C;
                *(f32 *)0xCC008000 = temp_f4_2;
                temp_r4_8 = &widthArray_S2051[3 - 3];
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_7->unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_8->unk0) + sp3C;
                *(f32 *)0xCC008000 = temp_f4_2;
                *(f32 *)0xCC008000 = (var_f31 * temp_r4_8->unk4) + sp44;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                temp_f4_3 = sp44 - var_f31;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051->unk0) + sp3C;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051->unk4) + sp40;
                *(f32 *)0xCC008000 = temp_f3_3;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[1].unk0) + sp3C;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[1].unk4) + sp40;
                *(f32 *)0xCC008000 = temp_f3_3;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[2].unk0) + sp3C;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[2].unk4) + sp40;
                *(f32 *)0xCC008000 = temp_f3_3;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[3].unk0) + sp3C;
                *(f32 *)0xCC008000 = (var_f31 * widthArray_S2051[3].unk4) + sp40;
                *(f32 *)0xCC008000 = temp_f3_3;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                temp_r11 = &widthArray_S2051[3 - 0];
                *(f32 *)0xCC008000 = (var_f31 * temp_r11->unk0) + sp3C;
                temp_r11_2 = &widthArray_S2051[3 - 1];
                *(f32 *)0xCC008000 = (var_f31 * temp_r11->unk4) + sp40;
                *(f32 *)0xCC008000 = temp_f4_3;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * temp_r11_2->unk0) + sp3C;
                temp_r11_3 = &widthArray_S2051[3 - 2];
                *(f32 *)0xCC008000 = (var_f31 * temp_r11_2->unk4) + sp40;
                *(f32 *)0xCC008000 = temp_f4_3;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * temp_r11_3->unk0) + sp3C;
                temp_r11_4 = &widthArray_S2051[3 - 3];
                *(f32 *)0xCC008000 = (var_f31 * temp_r11_3->unk4) + sp40;
                *(f32 *)0xCC008000 = temp_f4_3;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                *(f32 *)0xCC008000 = (var_f31 * temp_r11_4->unk0) + sp3C;
                *(f32 *)0xCC008000 = (var_f31 * temp_r11_4->unk4) + sp40;
                *(f32 *)0xCC008000 = temp_f4_3;
                *(f32 *)0xCC008000 = unksp8;
                *(f32 *)0xCC008000 = sp9;
                *(f32 *)0xCC008000 = spA;
                *(f32 *)0xCC008000 = 0xFF;
                ((GSgfxLayer*)((GSgfxLayer *) temp_r3_3))->endSurface();
                if (p1 != 0) {
                    M2C_FIELD(temp_r3_3, s32 *, 0x1998) = 0xA8;
                    M2C_FIELD(temp_r3_3, s8 *, 0xD34) = 0xC;
                    M2C_FIELD(temp_r3_3, s32 *, 0xD38) = 0;
                    M2C_FIELD(temp_r3_3, s32 *, 0x16AC) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16AC) | 4);
                    M2C_FIELD(temp_r3_3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16A8) | 1);
                    M2C_FIELD(temp_r3_3, s32 *, 0x1764) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1764) | 4);
                    M2C_FIELD(temp_r3_3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1760) | 1);
                    ((GSgfxLayer*)((GSgfxLayer *) temp_r3_3))->beginSurface(6U);
                    *(u8 *)0xCC008000 = sp3C;
                    *(u8 *)0xCC008000 = (f32) (sp40 - 100.0f);
                    *(u8 *)0xCC008000 = sp44;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = sp3C;
                    *(u8 *)0xCC008000 = (f32) (100.0f + sp40);
                    *(u8 *)0xCC008000 = sp44;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = (f32) (sp3C - 100.0f);
                    *(u8 *)0xCC008000 = sp40;
                    *(u8 *)0xCC008000 = sp44;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = (f32) (100.0f + sp3C);
                    *(u8 *)0xCC008000 = sp40;
                    *(u8 *)0xCC008000 = sp44;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = sp3C;
                    *(u8 *)0xCC008000 = sp40;
                    *(u8 *)0xCC008000 = (f32) (sp44 - 100.0f);
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = sp3C;
                    *(u8 *)0xCC008000 = sp40;
                    *(u8 *)0xCC008000 = (f32) (100.0f + sp44);
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = 0xFF;
                    ((GSgfxLayer*)((GSgfxLayer *) temp_r3_3))->endSurface();
                }
                if (GSlightGetType((GSlight*)(p0)) == 1) {
                    PSVECScale((const register Vec*)((Vec *) &sp30), (register Vec*)((Vec *) &sp30), 10.0f);
                    M2C_FIELD(temp_r3_3, s32 *, 0x1998) = 0xB0;
                    M2C_FIELD(temp_r3_3, s8 *, 0xD34) = 0xC;
                    M2C_FIELD(temp_r3_3, s32 *, 0xD38) = 0;
                    M2C_FIELD(temp_r3_3, s32 *, 0x16AC) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16AC) | 4);
                    M2C_FIELD(temp_r3_3, s32 *, 0x16A8) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x16A8) | 1);
                    M2C_FIELD(temp_r3_3, s32 *, 0x1764) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1764) | 4);
                    M2C_FIELD(temp_r3_3, s32 *, 0x1760) = (s32) (M2C_FIELD(temp_r3_3, s32 *, 0x1760) | 1);
                    ((GSgfxLayer*)((GSgfxLayer *) temp_r3_3))->beginSurface(2U);
                    *(u8 *)0xCC008000 = sp3C;
                    *(u8 *)0xCC008000 = sp40;
                    *(u8 *)0xCC008000 = sp44;
                    *(u8 *)0xCC008000 = unksp8;
                    *(u8 *)0xCC008000 = sp9;
                    *(u8 *)0xCC008000 = spA;
                    *(u8 *)0xCC008000 = 0xFF;
                    *(u8 *)0xCC008000 = (f32) (sp3C - sp30);
                    *(u8 *)0xCC008000 = (f32) (sp40 - sp34);
                    *(u8 *)0xCC008000 = (f32) (sp44 - sp38);
                    *(u8 *)0xCC008000 = unksp8;
                    *(u8 *)0xCC008000 = sp9;
                    *(u8 *)0xCC008000 = spA;
                    *(u8 *)0xCC008000 = 0xFF;
                    ((GSgfxLayer*)((GSgfxLayer *) temp_r3_3))->endSurface();
                }
            }
        }
    }
}
}
