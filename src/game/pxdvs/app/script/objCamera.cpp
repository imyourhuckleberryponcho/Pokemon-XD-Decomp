#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/tigadata.h>

#pragma pool_strings off
#pragma peephole off

struct GSvec { f32 x, y, z; GSvec() {} GSvec(f32 ax, f32 ay, f32 az) : x(ax), y(ay), z(az) {} };
struct ScriptPeople { s32 group; s32 object; };
namespace GSscript {
void tigaErrMessage(const char*);
struct tigaVariant {
    gc_bes16 type;
    gc_be16 flags;
    union { gc_bes32 integer; gc_bef32 real; gc_ptr32(void) pointer; } value;
    s32 getCnvInteger();
    GSvec* getCnvVector();
    f32 getCnvSingle();
    inline f32 getSingle() {
        if (type == 1) return (f32)value.integer;
        if (type == 2) return value.real;
        return getCnvSingle();
    }
    inline s32 getInteger() {
        if (type == 1) return value.integer;
        if (type == 2) return (s32)value.real;
        return getCnvInteger();
    }
    inline GSvec* getVector() {
        if (type == 4) return (GSvec*)value.pointer;
        return getCnvVector();
    }
    inline void* getObject(s16 expected, const char* message) {
        if (type == expected) return value.pointer;
        tigaErrMessage(message);
        return 0;
    }
    inline void setSingle(f32 n) { type = 2; value.real = n; }
    inline void setInteger(s32 n) { type = 1; value.integer = n; }
};
}
struct CameraScriptContext {
    GSSCRIPT_TIGACONTEXT_DATA(GSscript::tigaVariant, GSvec)
};
struct AppScript {
    GSSCRIPT_TIGA_DATA(GSscript::TigaChankView, GSscript::TigaObjManagerView, CameraScriptContext)
    virtual ~AppScript();
    GSscript::tigaWaza waza[7];
public:
    s32 cmpCamera(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
};

extern "C" {
void* GSresGetResource(s32, s32);
void GScameraSetPosition(void*, GSvec*);
void GScameraGetPerspective(void*, f32*, f32*, f32*, f32*);
void GScameraSetPerspective(void*, f32, f32, f32, f32);
s32 floorGetCurrentGroupID();
void floorFieldCameraEnable();
void floorFieldCameraDisable();
void floorFieldCameraBlend(f32);
void cameraSetFloorDefault(f32, f32, f32);
u8 cameraSetType(u8);
void cameraSetTarget(s32, s32);
void cameraSetTargetExt(s32, s32, s32);
void cameraSetTargetPosXYZ(f32, f32, f32);
void cameraSetTargetOfsXYZ(f32, f32, f32);
void cameraSetPartTargetOffset(GSvec*);
void cameraSetPosition(GSvec*);
void cameraSetRotationXYZ(f32, f32, f32);
void cameraPlayAnime(s32, s32, bool, f32);
void cameraStopAnime();
void cameraPauseAnime();
void cameraResumeAnime();
u8 cameraWaitSyncAnime(u8);
void cameraSetAnimeRate(f32);
void cameraMoveTarget(u8, s32, s32, f32);
#ifdef __MWERKS__
void cameraMoveTargetXYZ(u8, f32, f32, f32, f32);
#else
void cameraMoveTargetXYZ(f32 x, f32 y, f32 z, f32 time);
#define cameraMoveTargetXYZ(mode, ...) ((void)(mode), cameraMoveTargetXYZ(__VA_ARGS__))
#endif
void cameraMoveTargetPosAcc(f32);
#ifdef __MWERKS__
void cameraMovePositionXYZ(u8, f32, f32, f32, f32);
#else
void cameraMovePositionXYZ(f32 x, f32 y, f32 z, f32 time);
#define cameraMovePositionXYZ(mode, ...) ((void)(mode), cameraMovePositionXYZ(__VA_ARGS__))
#endif
void cameraMovePositionAcc(f32);
#ifdef __MWERKS__
void cameraMoveRotationXYZ(u8, f32, f32, f32, f32);
#else
void cameraMoveRotationXYZ(f32 x, f32 y, f32 z, f32 time);
#define cameraMoveRotationXYZ(mode, ...) ((void)(mode), cameraMoveRotationXYZ(__VA_ARGS__))
#endif
void cameraMoveRotationAcc(f32);
u8 cameraMoveEndCheck(u8);
#ifdef __MWERKS__
void cameraMoveFov(u8, f32, f32);
#else
void cameraMoveFov(f32 fov, f32 time);
#define cameraMoveFov(mode, ...) ((void)(mode), cameraMoveFov(__VA_ARGS__))
#endif
void cameraMoveFovAcc(f32);
void cameraSetHeight(f32);
void cameraSetDistance(f32);
void cameraSetRotY(f32);
void cameraSetFov(f32);
f32 cameraGetFov();
void cameraGetPosition(GSvec*);
void cameraGetRotation(GSvec*);
void cameraUpdate();
void cameraReturn(f32, PCARG(u8, s32));
}

s32 AppScript::cmpCamera(int command, GSscript::tigaVariant* args, GSscript::tigaVariant* result)
{
    GSvec vec;
    switch (command) {
    case 0x10: {
        f32 a = args[1].getSingle();
        f32 b = args[2].getSingle();
        cameraSetFloorDefault(a, b, args[3].getSingle());
        break;
    }
    case 0x11:
        if (args[1].getInteger() == 3) {
            floorFieldCameraDisable();
        }
        cameraSetType(args[1].getInteger());
        break;
    case 0x12: {
        ScriptPeople* p = (ScriptPeople*)args[1].getObject(0x23, "people not access");
        cameraSetTarget(p->group, p->object);
        break;
    }
    case 0x3D: {
        s32 a = args[1].getInteger();
        cameraSetTarget(floorGetCurrentGroupID(), a);
        break;
    }
    case 0x13: {
        f32 a = args[1].getSingle();
        f32 b = args[2].getSingle();
        cameraSetTargetPosXYZ(a, b, args[3].getSingle());
        break;
    }
    case 0x14: {
        GSvec* v = args[1].getVector();
        cameraSetTargetPosXYZ(v->x, v->y, v->z);
        break;
    }
    case 0x15: {
        f32 a = args[1].getSingle();
        f32 b = args[2].getSingle();
        cameraSetTargetOfsXYZ(a, b, args[3].getSingle());
        break;
    }
    case 0x16: {
        GSvec* v = args[1].getVector();
        cameraSetTargetOfsXYZ(v->x, v->y, v->z);
        break;
    }
    case 0x17: {
        void* res = GSresGetResource(0, 0);
        vec = GSvec(args[1].getSingle(), args[2].getSingle(), args[3].getSingle());
        cameraSetPosition(&vec);
        GScameraSetPosition(res, &vec);
        break;
    }
    case 0x18: {
        void* res = GSresGetResource(0, 0);
        cameraSetPosition(args[1].getVector());
        GScameraSetPosition(res, args[1].getVector());
        break;
    }
    case 0x19: {
        f32 a = args[1].getSingle();
        f32 b = args[2].getSingle();
        cameraSetRotationXYZ(a, b, args[3].getSingle());
        break;
    }
    case 0x1A: {
        GSvec* v = args[1].getVector();
        cameraSetRotationXYZ(v->x, v->y, v->z);
        break;
    }
    case 0x1B: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        f32 frame = args[3].getSingle();
        cameraPlayAnime(a, b, args[4].getInteger(), frame);
        break;
    }
    case 0x1C: cameraStopAnime(); break;
    case 0x1D: cameraPauseAnime(); break;
    case 0x1E: cameraResumeAnime(); break;
    case 0x1F: result->setInteger(cameraWaitSyncAnime(args[1].getInteger() != 0)); break;
    case 0x20: cameraSetAnimeRate(args[1].getSingle()); break;
    case 0x21: {
        ScriptPeople* p = (ScriptPeople*)args[2].getObject(0x23, "people not access");
        cameraSetType(args[1].getInteger());
        cameraMoveTarget(args[1].getInteger(), p->group, p->object, args[3].getSingle());
        break;
    }
    case 0x22:
        cameraSetType(args[1].getInteger());
        cameraMoveTargetXYZ(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger(), args[5].getInteger());
        break;
    case 0x23: {
        GSvec* v = args[2].getVector();
        cameraSetType(args[1].getInteger());
        cameraMoveTargetXYZ(args[1].getInteger(), v->x, v->y, v->z, args[3].getSingle());
        break;
    }
    case 0x24:
        cameraSetType(args[1].getInteger());
        cameraMovePositionXYZ(args[1].getInteger(), args[2].getSingle(), args[3].getSingle(), args[4].getSingle(), args[5].getSingle());
        break;
    case 0x25: {
        GSvec* v = args[2].getVector();
        cameraSetType(args[1].getInteger());
        cameraMovePositionXYZ(args[1].getInteger(), v->x, v->y, v->z, args[3].getSingle());
        break;
    }
    case 0x26:
        cameraSetType(args[1].getInteger());
        cameraMoveRotationXYZ(args[1].getSingle(), args[2].getSingle(), args[3].getSingle(), args[4].getSingle(), args[5].getSingle());
        break;
    case 0x27: {
        GSvec* v = args[2].getVector();
        cameraSetType(args[1].getInteger());
        cameraMoveRotationXYZ(args[1].getInteger(), v->x, v->y, v->z, args[3].getSingle());
        break;
    }
    case 0x28: result->setInteger(cameraMoveEndCheck(args[1].getInteger() != 0)); break;
    case 0x29: cameraSetHeight(args[1].getSingle()); break;
    case 0x2A: cameraSetDistance(args[1].getSingle()); break;
    case 0x2B: cameraSetRotY(args[1].getSingle()); break;
    case 0x2C: {
        void* res = GSresGetResource(0, 0);
        f32 fov, aspect, nearZ, farZ;
        GScameraGetPerspective(res, &fov, &aspect, &nearZ, &farZ);
        fov = args[1].getSingle();
        cameraSetFov(fov);
        GScameraSetPerspective(res, fov, aspect, nearZ, farZ);
        break;
    }
    case 0x2D: cameraUpdate(); break;
    case 0x2E: {
        f32 time = args[1].getSingle();
        cameraReturn(time, args[2].getInteger() != 0);
        break;
    }
    case 0x2F:
        cameraSetType(0);
        floorFieldCameraEnable();
        break;
    case 0x30:
        floorFieldCameraDisable();
        cameraSetType(3);
        break;
    case 0x31: floorFieldCameraBlend(args[1].getSingle()); break;
    case 0x32: result->setSingle(cameraGetFov()); break;
    case 0x33: {
        cameraGetPosition(&vec);
        context->vector = vec;
        context->regs[0].value.pointer = &context->vector;
        context->regs[0].type = 4;
        break;
    }
    case 0x34: {
        cameraGetRotation(&vec);
        context->vector = vec;
        context->regs[0].value.pointer = &context->vector;
        context->regs[0].type = 4;
        break;
    }
    case 0x3A:
        cameraMoveTargetXYZ(args[1].getInteger(), args[2].getInteger(), args[3].getInteger(), args[4].getInteger(), args[5].getInteger());
        cameraMoveTargetPosAcc(args[6].getSingle());
        break;
    case 0x39: {
        GSvec* v = args[2].getVector();
        cameraMoveTargetXYZ(args[1].getInteger(), v->x, v->y, v->z, args[3].getSingle());
        cameraMoveTargetPosAcc(args[4].getSingle());
        break;
    }
    case 0x36:
        cameraMovePositionXYZ(args[1].getInteger(), args[2].getSingle(), args[3].getSingle(), args[4].getSingle(), args[5].getSingle());
        cameraMovePositionAcc(args[6].getSingle());
        break;
    case 0x35: {
        GSvec* v = args[2].getVector();
        cameraMovePositionXYZ(args[1].getInteger(), v->x, v->y, v->z, args[3].getSingle());
        cameraMovePositionAcc(args[4].getSingle());
        break;
    }
    case 0x38:
        cameraMoveRotationXYZ(args[1].getSingle(), args[2].getSingle(), args[3].getSingle(), args[4].getSingle(), args[5].getSingle());
        cameraMoveRotationAcc(args[6].getSingle());
        break;
    case 0x37: {
        GSvec* v = args[2].getVector();
        cameraMoveRotationXYZ(args[1].getInteger(), v->x, v->y, v->z, args[3].getSingle());
        cameraMoveRotationAcc(args[4].getSingle());
        break;
    }
    case 0x3B:
        cameraMoveFov(args[1].getInteger(), args[2].getSingle(), args[3].getSingle());
        break;
    case 0x3C:
        cameraMoveFov(args[1].getInteger(), args[2].getSingle(), args[3].getSingle());
        cameraMoveFovAcc(args[4].getSingle());
        break;
    case 0x3E: {
        s32 a = args[1].getInteger();
        s32 b = args[2].getInteger();
        cameraSetTargetExt(floorGetCurrentGroupID(), a, b);
        break;
    }
    case 0x3F: cameraSetPartTargetOffset(args[1].getVector()); break;
    }
    return 0;
}
