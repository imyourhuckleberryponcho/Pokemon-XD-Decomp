// WIP (NonMatching): Setup functions match; in GSgfxProjectFast(List) the camera-vector loads
// (inv[0..2][2], inv[0..2][3]) come out in a different order/registers. Aggregate init matches
// Fast but turns into a template copy inside the FastList loop.
#include <dolphin/types.h>
#include <dolphin/mtx.h>

struct GScamera;

extern "C" {
void GXProject(f32 x, f32 y, f32 z, const f32 mtx[3][4], const f32* pm, const f32* vp, f32* sx, f32* sy, f32* sz);
MtxPtr GSgfxMatrixGetPtr(s32 id);
MtxPtr GScameraGetProjMatrixPtr(GScamera* camera);
MtxPtr GScameraGetInvMatrixPtr(GScamera* camera);
MtxPtr GScameraGetMatrixPtr(GScamera* camera);
}

static f32 g_projViewPort[6] = {0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f};
static f32 g_projProjectParams[7];
static MtxPtr g_projCameraMatrix;
static MtxPtr g_projInvCameraMatrix;
static MtxPtr g_projProjectMatrix;

static inline void VecSet(Vec* v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

#define VEC_SET(v, x_, y_, z_) \
    do {                       \
        f32 _z;                \
        f32 _y;                \
        f32 _x = (x_);         \
        _y = (y_);             \
        _z = (z_);             \
        (v)->x = _x;           \
        (v)->y = _y;           \
        (v)->z = _z;           \
    } while (0)

enum {
    PROJECT_FAILED,
    PROJECT_CLIPPED,
    PROJECT_OK,
    PROJECT_PARTIAL,
};

// Projects one point to the screen. Points behind the camera come out mirrored with z = -1.
static inline s32 _GSgfxProject(const Vec* in, Vec* out) {
    Vec camDir;
    Vec rel;
    f32 depth;

    VEC_SET(&camDir, g_projInvCameraMatrix[0][2], g_projInvCameraMatrix[1][2], g_projInvCameraMatrix[2][2]);
    VEC_SET(&rel, g_projInvCameraMatrix[0][3], g_projInvCameraMatrix[1][3], g_projInvCameraMatrix[2][3]);
    PSVECSubtract(in, &rel, &rel);
    depth = PSVECDotProduct(&camDir, &rel);
    if (depth <= -g_projProjectMatrix[2][3] && depth >= g_projProjectMatrix[2][3]) {
        return PROJECT_CLIPPED;
    }
    GXProject(in->x, in->y, in->z, g_projCameraMatrix, g_projProjectParams, g_projViewPort, &out->x, &out->y,
              &out->z);
    if (depth > 0.0f) {
        out->x = -out->x;
        out->y = -out->y;
        out->z = -1.0f;
    }
    return PROJECT_OK;
}

static inline void _GSgfxProjectSetup(MtxPtr camera, MtxPtr invCamera, MtxPtr project) {
    g_projCameraMatrix = camera;
    g_projInvCameraMatrix = invCamera;
    g_projProjectMatrix = project;
    if (g_projCameraMatrix != NULL && project != NULL) {
        g_projProjectParams[0] = 0.0f;
        g_projProjectParams[1] = project[0][0];
        g_projProjectParams[2] = project[0][2];
        g_projProjectParams[3] = project[1][1];
        g_projProjectParams[4] = project[1][2];
        g_projProjectParams[5] = project[2][2];
        g_projProjectParams[6] = project[2][3];
        g_projViewPort[0] = 0.0f;
        g_projViewPort[1] = 0.0f;
        g_projViewPort[2] = 640.0f;
        g_projViewPort[3] = 480.0f;
        g_projViewPort[4] = 0.0f;
        g_projViewPort[5] = 1.0f;
    }
}

extern "C" {

s32 GSgfxProjectFastList(const Vec* points, Vec* screen, u32 count) {
    s32 result;
    Vec* out = screen;
    const Vec* in = points;
    u32 visible;
    u32 i;

    if (g_projCameraMatrix == NULL || g_projProjectMatrix == NULL) {
        result = PROJECT_FAILED;
    } else {
    visible = count;
    result = PROJECT_OK;
    for (i = 0; i < count; i++, in++, out++) {
        s32 ret;
        Vec rel;
        Vec camDir;
        f32 depth;

        VEC_SET(&camDir, g_projInvCameraMatrix[0][2], g_projInvCameraMatrix[1][2], g_projInvCameraMatrix[2][2]);
        VEC_SET(&rel, g_projInvCameraMatrix[0][3], g_projInvCameraMatrix[1][3], g_projInvCameraMatrix[2][3]);
        PSVECSubtract(in, &rel, &rel);
        depth = PSVECDotProduct(&camDir, &rel);
        if (depth <= -g_projProjectMatrix[2][3] && depth >= g_projProjectMatrix[2][3]) {
            ret = PROJECT_CLIPPED;
        } else {
            GXProject(in->x, in->y, in->z, g_projCameraMatrix, g_projProjectParams, g_projViewPort, &out->x,
                      &out->y, &out->z);
            if (depth > 0.0f) {
                out->x = -out->x;
                out->y = -out->y;
                out->z = -1.0f;
            }
            ret = PROJECT_OK;
        }
        if (ret == PROJECT_CLIPPED) {
            result = PROJECT_PARTIAL;
            visible--;
            out->x = out->y = out->z = 1.0f;
        }
    }
    if (visible == 0) {
        result = PROJECT_CLIPPED;
    }
    }
    return result;
}

s32 GSgfxProjectFast(const Vec* in, Vec* out) {
    if (g_projCameraMatrix == NULL || g_projProjectMatrix == NULL) {
        return PROJECT_FAILED;
    }
    return _GSgfxProject(in, out);
}

void GSgfxProjectSetupCameraParameters(GScamera* camera) {
    if (camera == NULL) {
        MtxPtr project = GSgfxMatrixGetPtr(4);
        MtxPtr invCamera = GSgfxMatrixGetPtr(3);
        _GSgfxProjectSetup(GSgfxMatrixGetPtr(2), invCamera, project);
    } else {
        MtxPtr project = GScameraGetProjMatrixPtr(camera);
        MtxPtr invCamera = GScameraGetInvMatrixPtr(camera);
        _GSgfxProjectSetup(GScameraGetMatrixPtr(camera), invCamera, project);
    }
}

void GSgfxProjectSetupParameters(void) {
    MtxPtr project = GSgfxMatrixGetPtr(4);
    MtxPtr invCamera = GSgfxMatrixGetPtr(3);
    _GSgfxProjectSetup(GSgfxMatrixGetPtr(2), invCamera, project);
}

}
