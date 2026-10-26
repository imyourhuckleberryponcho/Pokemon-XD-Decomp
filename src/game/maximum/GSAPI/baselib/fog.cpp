#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#pragma pool_strings off

typedef struct HSD_CObj HSD_CObj;

typedef struct HSD_FogAdj {
    void* class_info;
    u32 ref_count;
    u32 flags;
    s16 center;
    u16 width;
    Mtx44 mtx;
} HSD_FogAdj;

typedef struct HSD_Fog {
    void* class_info;
    u32 ref_count;
    GXFogType type;
    HSD_FogAdj* fog_adj;
    f32 start;
    f32 end;
    GXColor color;
} HSD_Fog;

HSD_CObj* HSD_CObjGetCurrent(void);
f32 HSD_CObjGetNear(HSD_CObj* cobj);
f32 HSD_CObjGetFar(HSD_CObj* cobj);
void HSD_Panic(const char* file, u32 line, const char* msg);

void HSD_FogSet(HSD_Fog* fog) {
    u32 flags;
    HSD_FogAdj* adj;
    HSD_CObj* cobj;
    s32 center;
    s32 width;
    f32(*pmtx)[4];
    Mtx44 mtx;
    GXFogAdjTable table;
    f32 vp[6];
    f32 proj[7];
    GXColor color;

    if (fog == NULL) {
        GXColor zero = { 0 };
        GXSetFog(GX_FOG_NONE, 0.0F, 0.0F, 0.0F, 0.0F, zero);
        return;
    }
    cobj = HSD_CObjGetCurrent();
    if (cobj == NULL) {
        HSD_Panic("fog.c", 87, "You must specify CObj first.\n");
    }
    color = fog->color;
    GXSetFog(fog->type, fog->start, fog->end, HSD_CObjGetNear(cobj), HSD_CObjGetFar(cobj), color);

    adj = fog != NULL ? fog->fog_adj : 0;
    flags = adj != NULL ? adj->flags : 0;
    if (adj != NULL && (flags & 7)) {
        GXGetViewportv(vp);
        if (flags & 1) {
            center = vp[0] + vp[2] * ((adj != NULL ? adj->center : -1) + 320) / 640.0F;
        } else {
            f32 half = 0.5F;
            center = vp[0] + vp[2] * half;
        }
        if (flags & 2) {
            width = adj != NULL ? adj->width : -1;
        } else {
            width = vp[2];
        }
        if (flags & 4) {
            pmtx = adj != NULL ? adj->mtx : NULL;
        } else {
            pmtx = mtx;
            memset(pmtx, 0, sizeof(Mtx44));
            GXGetProjectionv(proj);
            switch ((s32)proj[0]) {
            case GX_PERSPECTIVE:
                mtx[0][0] = proj[1];
                mtx[0][2] = proj[2];
                mtx[1][1] = proj[3];
                mtx[1][2] = proj[4];
                mtx[2][2] = proj[5];
                mtx[2][3] = proj[6];
                mtx[3][2] = -1.0F;
                break;
            default:
                mtx[0][0] = proj[1];
                mtx[0][3] = proj[2];
                mtx[1][1] = proj[3];
                mtx[1][3] = proj[4];
                mtx[2][2] = proj[5];
                mtx[2][3] = proj[6];
                mtx[3][3] = 1.0F;
                break;
            }
        }
        GXInitFogAdjTable(&table, width, pmtx);
        GXSetFogRangeAdj(GX_ENABLE, center, &table);
    } else {
        GXSetFogRangeAdj(GX_DISABLE, 0, NULL);
    }
}

void HSD_FogInitDefaults(HSD_Fog* fog) {
    fog->start = 0.0F;
    fog->end = 1.0F;
}
