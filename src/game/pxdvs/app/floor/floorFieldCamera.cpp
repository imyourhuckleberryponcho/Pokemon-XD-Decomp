#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
    GSvec();
};
struct GSfloor_dd_;
struct GSvec2 {
    f32 x, z;
};
struct GSmtx {
    f32 m[3][4];
    GSmtx();
};

enum FloorStateMode { FSM_0, FSM_1, FSM_2, FSM_3 };
enum FloorEnterMode { FEM_0, FEM_1, FEM_2 };

struct FloorModuleInterface {
    u8 unk0[4];
    void (*enterFloor)(unsigned int, FloorEnterMode);
    u8 unk8[8];
    void (*exitFloor)(unsigned int, FloorEnterMode);
    u8 unk14[4];
    const char* (*getModuleName)();
    void (*makeStateData)(FloorStateMode, void*, u32);
    void (*restoreStateData)(FloorStateMode, void*, u32);
    u32 (*getStateSize)(FloorStateMode);
    u32 (*getMagicNumber)();
};

struct FieldCamera {
    u8 kind;        // 0x00
    u8 pad1[3];
    f32 posX;       // 0x04
    f32 posY;       // 0x08
    f32 posZ;       // 0x0C
    f32 distance;   // 0x10
    f32 height;     // 0x14
    f32 rotY;       // 0x18
    f32 radius;     // 0x1C
    f32 ratio;      // 0x20
    f32 angle;      // 0x24
    f32 powValue;   // 0x28
    f32 blendTime;  // 0x2C
    f32 fov;        // 0x30
};
struct FieldCameraHeader {
    u32* count;
    FieldCamera* list;
};

class GSBinWriteStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    void* allocation;
    u8 writing;
    GSBinWriteStream();
    GSBinWriteStream(void* data, u32 length);
    ~GSBinWriteStream();
    void writeU8(u8 n);
    void writeS8(s8 n);
    void writeBool(bool n);
    void writeU16(u16 n);
    void writeU32(u32 n);
    void writeFloat(f32 n);
    s32 getWriteSize() const;
};
class GSBinWriteSizeStream : public GSBinWriteStream {
public:
    GSBinWriteSizeStream();
    ~GSBinWriteSizeStream();
};
class GSBinReadStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    GSBinReadStream(void* data, u32 length);
    u8 readU8();
    bool readBool();
    u16 readU16();
    u32 readU32();
    f32 readFloat();
};

namespace std {
__declspec(weak) float pow(float, float);
__declspec(weak) float powf(float, float);
__declspec(weak) float cosf(float);
__declspec(weak) float atan2f(float, float);
__declspec(weak) float sinf(float);
inline float sqrtf(float);
} // namespace std
#pragma dont_inline reset

extern "C" {
int __fpclassifyf(float);
extern float __float_nan[];
void FloorModuleInterface_clear(FloorModuleInterface*);
s32 floorRegisterModule(s32, s32, FloorModuleInterface*);
void* floorDataBiosGetPtr();
void* floorDataBiosGetCurrentPtr();
FieldCameraHeader* floorDataBiosGetFieldCameraListPtr(void*);
double pow(double, double);
double cos(double);
double sin(double);
double atan2(double, double);
double __frsqrte(double);
void GSlogWrite(const char*, ...);
void GSmemFree(void*);
void __dl__FPv(void*);
void* GSresGetResource(u32, u32);
void GSmodelGetPosition(void*, GSvec*);
void GSvecSet(GSvec*, f32, f32, f32);
void PSVECAdd(const GSvec*, const GSvec*, GSvec*);
f32 PSVECSquareDistance(const GSvec*, const GSvec*);
void PSMTXMultVec(const GSmtx*, const GSvec*, GSvec*);
void PSMTXRotRad(GSmtx*, char, f32);
u8 GSgfxVideoGetVsyncRate();
f32 GSgfxVideoGetLastRenderTime(u8);
u8 cameraGetType();
void cameraGetTargetPos(GSvec*);
void cameraGetTargetOfs(GSvec*);
f32 cameraGetHeight();
f32 cameraGetDistance();
f32 cameraGetRotY();
f32 cameraGetFov();
void cameraSetHeight(f32);
void cameraSetDistance(f32);
void cameraSetRotY(f32);
void cameraSetFov(f32);
void cameraMoveTargetOfs(u32, GSvec*, f32);
void cameraMoveTargetOfsAcc(f32);
void cameraMoveTargetPos(u32, GSvec*, f32);
void cameraMoveTargetPosAcc(f32);
void cameraMovePosition(u32, GSvec*, f32);
void cameraMovePositionAcc(f32);
void cameraMoveRotation(u32, GSvec*, f32);
void cameraMoveRotationAcc(f32);
void GSvecAdd(GSvec*, const GSvec*, const GSvec*);
void GSvecTransform(GSvec*, const GSmtx*, const GSvec*);
f32 GSvecSquareDistance(const GSvec*, const GSvec*);
f32 GSvec2Length(const GSvec2*);
void GSvec2Rot(GSvec2*, const GSvec2*, f32);
void GSvec2Sub(GSvec2*, const GSvec2*, const GSvec2*);
void GSvec2Set(GSvec2*, f32, f32);
void GSmtxMakeYRotation(GSmtx*, f32);
}

static void _fieldCameraExitFloor(unsigned int, FloorEnterMode);
static void _fieldCameraEnterFloor(unsigned int, FloorEnterMode);
static const char* _fieldCameraGetModuleName();
static u32 _fieldCameraGetMagicNumber();
static u32 _fieldCameraGetStateSize(FloorStateMode);
static void _fieldCameraRestoreStateData(FloorStateMode, void*, u32);
static void _fieldCameraMakeStateData(FloorStateMode, void*, u32);
void floorReleaseFieldCamera();
void floorInitFieldCamera(GSfloor_dd_*);
static void _floorFieldCameraSetParams(f32, f32, f32, f32);
static void _floorFieldCameraGetTargetPos(GSvec*);
static void _floorFieldCameraDetectMode();
static u8 _floorFieldCameraCalculateBlendParams(GSvec*, f32*, f32*, f32*, f32*);
static u8 _floorFieldCameraCalculatePathParams(GSvec*, f32*, f32*, f32*, f32*);
extern "C" void floorUpdateFieldCamera();

static FloorModuleInterface _fieldCameraModule;
static f32 gCameraInitFOV = 30.0f;
static f32 gCameraFOV = 30.0f;
static f32 g_BlendingMaxTime = 1.0f;
static s32 _fieldCamera_hModule;
static u32 gNumFieldCameras;
static FieldCamera* gFieldCameraList;
static bool gFieldCameraEnabled;
static u8 gFieldCameraPause;
static bool gCameraVarsInitialised;
static u8 g_updateMode;
static bool g_Blending;
static u16 g_currentIndex;
static f32 gCameraInitHeight;
static f32 gCameraHeight;
static f32 gCameraInitDistance;
static f32 gCameraDistance;
static f32 gCameraInitRotY;
static f32 gCameraRotY;
static f32 gPowValue;
static f32 g_BlendingTime;

extern "C" {

void floorFieldCameraInit() {
    FloorModuleInterface_clear(&_fieldCameraModule);
    _fieldCameraModule.makeStateData = _fieldCameraMakeStateData;
    _fieldCameraModule.restoreStateData = _fieldCameraRestoreStateData;
    _fieldCameraModule.getStateSize = _fieldCameraGetStateSize;
    _fieldCameraModule.getMagicNumber = _fieldCameraGetMagicNumber;
    _fieldCameraModule.getModuleName = _fieldCameraGetModuleName;
    _fieldCameraModule.enterFloor = _fieldCameraEnterFloor;
    _fieldCameraModule.exitFloor = _fieldCameraExitFloor;
    _fieldCamera_hModule = floorRegisterModule(0xA, 0, &_fieldCameraModule);
}

}

static void _fieldCameraExitFloor(unsigned int, FloorEnterMode mode) {
    if (mode != FEM_1) {
        floorReleaseFieldCamera();
    }
}

static void _fieldCameraEnterFloor(unsigned int, FloorEnterMode mode) {
    GSfloor_dd_* floor = (GSfloor_dd_*)floorDataBiosGetPtr();
    if (floor == 0 || (mode != FEM_0 && mode != FEM_1)) {
        return;
    }
    floorInitFieldCamera(floor);
}

static const char* _fieldCameraGetModuleName() {
    return "field camera";
}

static u32 _fieldCameraGetMagicNumber() {
    return 0x15;
}

static u32 _fieldCameraGetStateSize(FloorStateMode mode) {
    if (mode == FSM_3 || mode == FSM_1) {
        GSBinWriteSizeStream stream;
        stream.writeU16(0x3C7);
        stream.writeU8(0);
        stream.writeBool(gFieldCameraEnabled);
        stream.writeBool(gCameraVarsInitialised);
        stream.writeBool(g_Blending);
        stream.writeU16(g_currentIndex);
        stream.writeFloat(gCameraInitHeight);
        stream.writeFloat(gCameraHeight);
        stream.writeFloat(gCameraInitDistance);
        stream.writeFloat(gCameraDistance);
        stream.writeFloat(gCameraInitRotY);
        stream.writeFloat(gCameraRotY);
        stream.writeFloat(gCameraInitFOV);
        stream.writeFloat(gCameraFOV);
        stream.writeFloat(gPowValue);
        stream.writeFloat(g_BlendingTime);
        stream.writeFloat(g_BlendingMaxTime);
        return stream.getWriteSize();
    }
    return 0;
}

static void _fieldCameraRestoreStateData(FloorStateMode mode, void* data, u32 size) {
    if (mode == FSM_3 || mode == FSM_1) {
        GSBinReadStream stream(data, size);
        void* floor;
        if (stream.readU16() == 0x3C7 && stream.readU8() == 0 && (floor = floorDataBiosGetCurrentPtr()) != 0) {
            FieldCameraHeader* header = floorDataBiosGetFieldCameraListPtr(floor);
            if (header != 0) {
                gNumFieldCameras = *header->count;
                gFieldCameraList = header->list;
                gFieldCameraEnabled = stream.readBool();
                gCameraVarsInitialised = stream.readBool();
                g_Blending = stream.readBool();
                g_currentIndex = stream.readU16();
                gCameraInitHeight = stream.readFloat();
                gCameraHeight = stream.readFloat();
                gCameraInitDistance = stream.readFloat();
                gCameraDistance = stream.readFloat();
                gCameraInitRotY = stream.readFloat();
                gCameraRotY = stream.readFloat();
                gCameraInitFOV = stream.readFloat();
                gCameraFOV = stream.readFloat();
                gPowValue = stream.readFloat();
                g_BlendingTime = stream.readFloat();
                g_BlendingMaxTime = stream.readFloat();
                _floorFieldCameraDetectMode();
                floorUpdateFieldCamera();
            }
        }
    }
}

static void _fieldCameraMakeStateData(FloorStateMode mode, void* data, u32 size) {
    if (mode == FSM_3 || mode == FSM_1) {
        GSBinWriteStream stream(data, size);
        stream.writeU16(0x3C7);
        stream.writeU8(0);
        stream.writeBool(gFieldCameraEnabled);
        stream.writeBool(gCameraVarsInitialised);
        stream.writeBool(g_Blending);
        stream.writeU16(g_currentIndex);
        stream.writeFloat(gCameraInitHeight);
        stream.writeFloat(gCameraHeight);
        stream.writeFloat(gCameraInitDistance);
        stream.writeFloat(gCameraDistance);
        stream.writeFloat(gCameraInitRotY);
        stream.writeFloat(gCameraRotY);
        stream.writeFloat(gCameraInitFOV);
        stream.writeFloat(gCameraFOV);
        stream.writeFloat(gPowValue);
        stream.writeFloat(g_BlendingTime);
        stream.writeFloat(g_BlendingMaxTime);
    }
}

extern "C" u8 floorFieldCameraGetMode() {
    return g_updateMode;
}

void floorReleaseFieldCamera() {
    gNumFieldCameras = 0;
    gFieldCameraList = 0;
}

void floorInitFieldCamera(GSfloor_dd_* floor) {
    FieldCameraHeader* header = floorDataBiosGetFieldCameraListPtr(floor);
    gNumFieldCameras = 0;
    gFieldCameraList = 0;
    gCameraVarsInitialised = 0;
    gFieldCameraEnabled = 1;
    gCameraHeight = 0.0f;
    gCameraDistance = 0.0f;
    gCameraRotY = 0.0f;
    gCameraFOV = 30.0f;
    gPowValue = 0.0f;
    if (header != 0) {
        gNumFieldCameras = *header->count;
        gFieldCameraList = header->list;
        _floorFieldCameraDetectMode();
        g_currentIndex = 0;
        gCameraInitHeight = gCameraHeight = gFieldCameraList->height;
        gCameraInitDistance = gCameraDistance = gFieldCameraList->distance;
        gCameraInitRotY = gCameraRotY = gFieldCameraList->rotY;
        gCameraInitFOV = gCameraFOV = gFieldCameraList->fov;
        gPowValue = gFieldCameraList->powValue;
        g_Blending = 0;
        g_BlendingTime = 0.0f;
        floorUpdateFieldCamera();
    }
}

extern "C" {

void floorUpdateFieldCamera() {
    GSvec target;
    if (gFieldCameraEnabled && !gFieldCameraPause && cameraGetType() == 0 && gNumFieldCameras != 0) {
        f32 distance, height, rotY, fov;
        if (gNumFieldCameras == 1) {
            _floorFieldCameraSetParams(gFieldCameraList->height, gFieldCameraList->distance,
                                       gFieldCameraList->rotY, gFieldCameraList->fov);
            return;
        }
        cameraGetTargetPos(&target);
        height = gCameraHeight;
        distance = gCameraDistance;
        rotY = gCameraRotY;
        fov = gCameraFOV;
        switch (g_updateMode) {
        case 1:
            if (!_floorFieldCameraCalculatePathParams(&target, &height, &distance, &rotY, &fov)) {
                return;
            }
            if (gCameraVarsInitialised && g_Blending && g_BlendingMaxTime > 0.0f) {
                u8 rate;
                f32 frate = rate = GSgfxVideoGetVsyncRate();
                g_BlendingTime = g_BlendingTime + GSgfxVideoGetLastRenderTime(rate) / frate;
                if (g_BlendingTime >= g_BlendingMaxTime) {
                    g_Blending = 0;
                    gCameraHeight = height;
                    gCameraDistance = distance;
                    gCameraRotY = rotY;
                    gCameraFOV = fov;
                } else {
                    f32 t = g_BlendingTime / g_BlendingMaxTime;
                    if (gPowValue < -0.00001f) {
                        gCameraHeight = t * (height - gCameraInitHeight) + gCameraInitHeight;
                        gCameraDistance = t * (distance - gCameraInitDistance) + gCameraInitDistance;
                        gCameraRotY = t * (rotY - gCameraInitRotY) + gCameraInitRotY;
                        gCameraFOV = t * (fov - gCameraInitFOV) + gCameraInitFOV;
                    } else if (gPowValue < 0.19999f) {
                        t = t * t;
                        gCameraHeight += t * (height - gCameraHeight);
                        gCameraDistance += t * (distance - gCameraDistance);
                        gCameraRotY += t * (rotY - gCameraRotY);
                        gCameraFOV += t * (fov - gCameraFOV);
                    } else {
                        u8 flip = 0;
                        f32 s = t * 2.0f;
                        if (s > 1.0f) {
                            flip = 1;
                            s = 2.0f - s;
                        }
                        f32 c = std::cosf(1.5707964f * s);
                        f32 e = std::pow(1.0f - c, gPowValue);
                        if (flip) {
                            e = 2.0f - e;
                        }
                        e = e * 0.5f;
                        gCameraHeight = e * (height - gCameraInitHeight) + gCameraInitHeight;
                        gCameraDistance = e * (distance - gCameraInitDistance) + gCameraInitDistance;
                        gCameraRotY = e * (rotY - gCameraInitRotY) + gCameraInitRotY;
                        gCameraFOV = e * (fov - gCameraInitFOV) + gCameraInitFOV;
                    }
                }
            } else {
                g_Blending = 0;
                gCameraInitHeight = gCameraHeight = height;
                gCameraInitDistance = gCameraDistance = distance;
                gCameraInitRotY = gCameraRotY = rotY;
                gCameraInitFOV = gCameraFOV = fov;
                gCameraVarsInitialised = 1;
            }
            break;
        case 0:
        default:
            if (!_floorFieldCameraCalculateBlendParams(&target, &height, &distance, &rotY, &fov)) {
                return;
            }
            if (gCameraVarsInitialised) {
                gCameraHeight = 0.5f * gCameraHeight + 0.5f * height;
                gCameraDistance = 0.5f * gCameraDistance + 0.5f * distance;
                gCameraRotY = 0.5f * gCameraRotY + 0.5f * rotY;
                gCameraFOV = 0.5f * gCameraFOV + 0.5f * fov;
            } else {
                gCameraHeight = height;
                gCameraDistance = distance;
                gCameraRotY = rotY;
                gCameraFOV = fov;
                gCameraVarsInitialised = 1;
            }
            break;
        }
        _floorFieldCameraSetParams(gCameraHeight, gCameraDistance, gCameraRotY, gCameraFOV);
    }
}

void floorFieldCameraBlend(f32 time) {
    GSvec target;
    GSvec targetOfs;
    GSvec position;
    GSvec rotation;
    GSvec offset;
    GSmtx mtx;
    if (gFieldCameraEnabled && !gFieldCameraPause && cameraGetType() == 0 && gNumFieldCameras != 0) {
        f32 distance, height, rotY, fov;
        _floorFieldCameraGetTargetPos(&target);
        cameraGetTargetOfs(&targetOfs);
        if (gNumFieldCameras == 1) {
            height = gFieldCameraList->height;
            distance = gFieldCameraList->distance;
            rotY = gFieldCameraList->rotY;
            fov = gFieldCameraList->fov;
        } else {
            height = cameraGetHeight();
            distance = cameraGetDistance();
            rotY = cameraGetRotY();
            fov = cameraGetFov();
            switch (g_updateMode) {
            case 1:
                if (!_floorFieldCameraCalculatePathParams(&target, &height, &distance, &rotY, &fov)) {
                    return;
                }
                break;
            case 0:
            default:
                if (!_floorFieldCameraCalculateBlendParams(&target, &height, &distance, &rotY, &fov)) {
                    return;
                }
                break;
            }
        }
        GSvecSet(&offset, 0.0f, height, distance);
        GSmtxMakeYRotation(&mtx, rotY);
        GSvecTransform(&offset, &mtx, &offset);
        GSvecAdd(&position, &target, &targetOfs);
        GSvecAdd(&position, &position, &offset);
        rotation.y = rotY;
        rotation.x = -std::atan2f(height, distance);
        rotation.z = 0.0f;
        cameraMoveTargetOfs(0, &targetOfs, time);
        cameraMoveTargetOfsAcc(0.08f);
        cameraMoveTargetPos(0, &target, time);
        cameraMoveTargetPosAcc(0.08f);
        cameraMovePosition(0, &position, time);
        cameraMovePositionAcc(0.08f);
        cameraMoveRotation(0, &rotation, time);
        cameraMoveRotationAcc(0.08f);
        cameraSetFov(fov);
    }
}

s32 floorFieldCameraDataExist() {
    s32 exist = 0;
    if (gNumFieldCameras != 0 && gFieldCameraList != 0) {
        exist = 1;
    }
    return exist;
}

u8 floorFieldCameraGetEnabled() {
    return gFieldCameraEnabled;
}

void floorFieldCameraUnpause() {
    gFieldCameraPause = 0;
}

void floorFieldCameraPause() {
    gFieldCameraPause = 1;
}

void floorFieldCameraDisable() {
    gFieldCameraEnabled = 0;
}

void floorFieldCameraEnable() {
    gFieldCameraEnabled = 1;
    gCameraVarsInitialised = 0;
    floorFieldCameraUnpause();
}

}

static u8 _floorFieldCameraCalculateBlendParams(GSvec* target, f32* outHeight, f32* outDistance, f32* outRotY,
                                                f32* outFov) {
    GSvec pos;
    f32 weightSum = 0.0f;
    f32 distance = 0.0f;
    f32 height = 0.0f;
    f32 rotY = 0.0f;
    f32 fov = 0.0f;
    for (u32 i = 0; i < gNumFieldCameras; i++) {
        FieldCamera* cam = &gFieldCameraList[i];
        GSvecSet(&pos, cam->posX, target->y, cam->posZ);
        f32 sq = GSvecSquareDistance(&pos, target);
        if (sq > 1.0f) {
            f32 w = 0.001f / sq;
            weightSum += w;
            distance += cam->distance * w;
            height += cam->height * w;
            rotY += cam->rotY * w;
            fov += cam->fov * w;
        } else {
            weightSum = 1.0f;
            height = cam->height;
            distance = cam->distance;
            rotY = cam->rotY;
            fov = cam->fov;
            break;
        }
    }
    if (weightSum == 0.0f) {
        GSlogWrite("floorUpdateFieldCamera: error updating field camera - divide by zero!");
        return 0;
    }
    f32 inv = 1.0f / weightSum;
    *outHeight = height * inv;
    *outDistance = distance * inv;
    *outRotY = rotY * inv;
    *outFov = fov * inv;
    return 1;
}

static u8 _floorFieldCameraCalculatePathParams(GSvec* target, f32* outHeight, f32* outDistance, f32* outRotY,
                                               f32* outFov) {
    FieldCamera* cam;
    u16 i;
    GSvec2 d;
    GSvec2 p;
    GSvec2Set(&p, target->x, target->z);
    FieldCamera* cur = gFieldCameraList + g_currentIndex;
    *outHeight = cur->height;
    *outDistance = cur->distance;
    *outRotY = cur->rotY;
    *outFov = cur->fov;
    GSvec2Set(&d, cur->posX, cur->posZ);
    GSvec2Sub(&d, &d, &p);
    if (cur->kind != 0) {
        GSvec2Rot(&d, &d, -cur->angle);
        f32 ax = d.x;
        if (ax < 0.0f) {
            ax = -ax;
        }
        f32 radius = cur->radius;
        if (ax < radius) {
            f32 az = d.z;
            if (az < 0.0f) {
                az = -az;
            }
            if (az < radius * cur->ratio) {
                return 1;
            }
        }
    } else if (GSvec2Length(&d) <= cur->radius) {
        return 1;
    }
    cam = gFieldCameraList;
    for (i = 0; i < gNumFieldCameras; i++, cam++) {
        if (i != g_currentIndex) {
            u8 inside = 0;
            GSvec2Set(&d, cam->posX, cam->posZ);
            GSvec2Sub(&d, &d, &p);
            if (cam->kind != 0) {
                GSvec2Rot(&d, &d, -cam->angle);
                f32 ax = d.x;
                if (ax < 0.0f) {
                    ax = -ax;
                }
                f32 radius = cam->radius;
                if (ax < radius) {
                    f32 az = d.z;
                    if (az < 0.0f) {
                        az = -az;
                    }
                    if (az < radius * cam->ratio) {
                        inside = 1;
                    }
                }
            } else if (GSvec2Length(&d) <= cam->radius) {
                inside = 1;
            }
            if (inside) {
                *outHeight = cam->height;
                *outDistance = cam->distance;
                *outRotY = cam->rotY;
                *outFov = cam->fov;
                g_currentIndex = i;
                gCameraInitHeight = gCameraHeight;
                gCameraInitDistance = gCameraDistance;
                gCameraInitRotY = gCameraRotY;
                gCameraInitFOV = gCameraFOV;
                gPowValue = cam->powValue;
                g_Blending = 1;
                g_BlendingTime = 0.0f;
                g_BlendingMaxTime = cam->blendTime;
                break;
            }
        }
    }
    return 1;
}

static void _floorFieldCameraSetParams(f32 height, f32 distance, f32 rotY, f32 fov) {
    cameraSetHeight(height);
    cameraSetDistance(distance);
    cameraSetRotY(rotY);
    cameraSetFov(fov);
}

static void _floorFieldCameraGetTargetPos(GSvec* pos) {
    void* model = GSresGetResource(0, 0x64);
    if (model != 0) {
        GSmodelGetPosition(model, pos);
        return;
    }
    cameraGetTargetPos(pos);
}

static void _floorFieldCameraDetectMode() {
    FieldCamera* cam = gFieldCameraList;
    g_updateMode = 0;
    for (u32 i = 0; i < gNumFieldCameras; i++, cam++) {
        if (cam->radius <= 0.001f) {
            return;
        }
        if (cam->blendTime >= 0.0f) {
            continue;
        }
        return;
    }
    g_updateMode = 1;
}

// Inline helpers defined after their callers.
inline s32 GSBinWriteStream::getWriteSize() const { return current - begin; }
inline void GSBinWriteStream::writeFloat(f32 n) {
    union { u32 i; f32 f; } v;
    v.f = n;
    writeU32(v.i);
}
inline void GSBinWriteStream::writeU32(u32 n) {
    if (!writing) {
        current += 4;
    } else {
        *current++ = n >> 24;
        *current++ = n >> 16;
        *current++ = n >> 8;
        *current++ = n;
    }
}
inline void GSBinWriteStream::writeBool(bool n) {
    int v;
    if (n) {
        v = 1;
    } else {
        v = 0;
    }
    writeS8(v);
}
inline void GSBinWriteStream::writeS8(s8 n) { writeU8(n); }
inline void GSBinWriteStream::writeU8(u8 n) {
    if (!writing) {
        current++;
    } else {
        *current++ = n;
    }
}
inline void GSBinWriteStream::writeU16(u16 n) {
    if (!writing) {
        current += 2;
    } else {
        int m = n;
        *current++ = m >> 8;
        *current++ = m;
    }
}
inline GSBinWriteSizeStream::~GSBinWriteSizeStream() {}
inline GSBinWriteStream::~GSBinWriteStream() {
    if (allocation) {
        GSmemFree(allocation);
    }
}
inline GSBinWriteSizeStream::GSBinWriteSizeStream() {
    current = 0;
    allocation = 0;
    begin = 0;
    size = 0x10000000;
    writing = 0;
}
inline GSBinWriteStream::GSBinWriteStream() {
    current = 0;
    allocation = 0;
    begin = 0;
    size = 0;
    writing = 0;
}
inline f32 GSBinReadStream::readFloat() {
    union { u32 i; f32 f; } v;
    v.i = readU32();
    return v.f;
}
inline u32 GSBinReadStream::readU32() {
    u8* p = current;
    u32 n = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
    current += 4;
    return n;
}
inline bool GSBinReadStream::readBool() { return readU8() != 0; }
inline u8 GSBinReadStream::readU8() { return *current++; }
inline u16 GSBinReadStream::readU16() {
    u8* p = current;
    u16 n = (p[0] << 8) | p[1];
    current += 2;
    return n;
}
inline GSBinReadStream::GSBinReadStream(void* data, u32 length) {
    begin = current = (u8*)data;
    size = length;
}
inline GSBinWriteStream::GSBinWriteStream(void* data, u32 length) {
    allocation = 0;
    current = (u8*)data;
    begin = (u8*)data;
    size = length;
    writing = 1;
}



#pragma dont_inline on
namespace std {
__declspec(weak) float pow(float x, float y) { return powf(x, y); }
__declspec(weak) float powf(float x, float y) { return (float)::pow((double)x, (double)y); }
__declspec(weak) float cosf(float x) { return (float)::cos((double)x); }
__declspec(weak) float atan2f(float y, float x) { return (float)::atan2((double)y, (double)x); }
__declspec(weak) float sinf(float x) { return (float)::sin((double)x); }
} // namespace std
#pragma dont_inline reset

extern "C" {
inline void GSvecAdd(GSvec* r, const GSvec* a, const GSvec* b) { PSVECAdd(a, b, r); }
inline void GSvecTransform(GSvec* r, const GSmtx* m, const GSvec* v) { PSMTXMultVec(m, v, r); }
inline f32 GSvecSquareDistance(const GSvec* a, const GSvec* b) { return PSVECSquareDistance(a, b); }
inline f32 GSvec2Length(const GSvec2* v) { return std::sqrtf(v->x * v->x + v->z * v->z); }
inline void GSvec2Rot(GSvec2* r, const GSvec2* v, f32 angle) {
    f32 c = std::cosf(angle);
    f32 s = std::sinf(angle);
    f32 z = v->z;
    f32 x = v->x;
    r->x = x * c + z * s;
    r->z = -x * s + z * c;
}
#pragma scheduling off
inline void GSvec2Sub(GSvec2* r, const GSvec2* a, const GSvec2* b) {
    r->x = a->x - b->x;
    r->z = a->z - b->z;
}
#pragma scheduling reset
inline void GSvec2Set(GSvec2* v, f32 x, f32 z) {
    v->x = x;
    v->z = z;
}
inline void GSmtxMakeYRotation(GSmtx* m, f32 angle) { PSMTXRotRad(m, 'Y', angle); }
}



namespace std {
inline float sqrtf(float x) {
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (float)(x * guess);
    } else if (x < 0.0) {
        return __float_nan[0];
    } else if (__fpclassifyf(x) == 1) {
        return __float_nan[0];
    }
    return x;
}
} // namespace std
