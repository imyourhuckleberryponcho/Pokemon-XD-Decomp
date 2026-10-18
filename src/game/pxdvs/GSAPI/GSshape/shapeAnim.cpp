// Draft (NonMatching): GsKeyObject animation. 1 of 16 exact, rest 77-98%. Default flags give LAYOUT OK.
// Draft: GS shape key-frame animation (GsKeyObject). Struct layouts derived from the asm.
#include <dolphin/types.h>

struct tagGScol4ub {
    u8 r, g, b, a;
};
typedef f32 Mtx34[3][4];
struct GSmtx {
    Mtx34 m;
};

struct GsVec2 {
    f32 v[2];
};

struct tagGsFilePrimObjectEntry {
    u8 unk0[0x6D];
    u8 hasRot;
    u8 hasAxisB;
    u8 hasAxisA;
    f32 pos[3];
    u8 unk7C[0x94 - 0x7C];
    f32 axisB[3];
    f32 axisA[3];
    f32 angleB;
    f32 angleA;
};

struct tagGsFilePrimKeyFrame {
    u8 unk0[4];
    u32 time;
    u8 unk8[8];
    f32 scale[3];
    f32 trans[3];
    f32 pivot[3];
    f32 rot[3];
    u8 color[4];
    f32 radius[2];
    u8 unk4C[8];
    f32 showAngle[2];
    f32 texScale[4][2];
    f32 texOffset[4][2];
    u8 texColor[4][4];
    u8 texColorLow[4][4];
    u8 nScale[3];
    u8 nTrans[3];
    u8 nPivot[3];
    u8 nRot[3];
    u8 nColor[4];
    u8 nRadius[2];
    u8 unkCE[2];
    u8 nShowAngle[2];
    u8 nTexScale[4][2];
    u8 nTexOffset[4][2];
    u8 nTexColor[4][4];
    u8 nTexColorLow[4][4];
    u8 unk102[2];
    const f32* cScale[3];
    const f32* cTrans[3];
    const f32* cPivot[3];
    const f32* cRot[3];
    const f32* cColor[4];
    const f32* cRadius[2];
    u8 unk14C[8];
    const f32* cShowAngle[2];
    const f32* cTexScale[4][2];
    const f32* cTexOffset[4][2];
    const f32* cTexColor[4][4];
    const f32* cTexColorLow[4][4];
    u16 nDeformU;
    u16 nDeformV;
    const f32* deformU;
    const f32* deformV;
    u16 nTwist;
    u8 unk22A[2];
    const f32* twist;
    u8 unk230[0xC];
    u8 gradKind;
    u8 unk23D[3];
    u16 nGrad0;
    u16 nGrad1;
    const tagGScol4ub* grad0;
    const tagGScol4ub* grad1;
};

struct GsKeyHeader {
    u8 unk0[6];
    u16 count;
    u8 unk8[0x14];
    u8 texFlag[4];
    u8 unk20[0x18];
    f32 rangeScale;
    f32 rangeTrans;
    f32 rangePivot;
    f32 rangeRot;
    f32 rangeRadius;
    f32 rangeShowAngle;
    f32 rangeTexOffset;
    f32 rangeTexScale;
};

class GsKeyObject {
public:
    bool GetShapeMatrix(GSmtx* scaleMtx, GSmtx* mtx, const tagGsFilePrimObjectEntry* entry, u8 count,
                        const u8* order, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                        f32 t) const;
    bool GetGradationParameter(u8* kind, tagGScol4ub* out, const tagGsFilePrimKeyFrame* a,
                               const tagGsFilePrimKeyFrame* b, f32 t) const;
    bool GetTwistParameter(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const;
    bool GetDeformParameterV(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                             f32 t) const;
    bool GetDeformParameterU(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                             f32 t) const;
    bool GetLinearParameterV(f32* out, const tagGsFilePrimKeyFrame* a);
    bool GetLinearParameterU(f32* out, const tagGsFilePrimKeyFrame* a);
    tagGScol4ub GetTextureColorLow(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t,
                                   u32 idx) const;
    tagGScol4ub GetTextureColor(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t,
                                u32 idx) const;
    GsVec2 GetTextureOffset(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t, u32 idx) const;
    GsVec2 GetTextureScale(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t, u32 idx) const;
    bool GetShapeShowAngle(f32* o0, f32* o1, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                           f32 t) const;
    bool GetShapeRadius(f32* o0, f32* o1, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                        f32 t) const;
    f32 GetShapeColorAlpha(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const;
    tagGScol4ub GetShapeColor(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const;
    bool GetFrameInterval(u32 frame, tagGsFilePrimKeyFrame*& a, tagGsFilePrimKeyFrame*& b, f32& t);

    GsKeyHeader* header;
    tagGsFilePrimKeyFrame** frames;
};

extern "C" {
extern GSmtx mtxIdent;
void* memcpy(void* dst, const void* src, u32 n);
void PSMTXConcat(const f32 a[3][4], const f32 b[3][4], f32 ab[3][4]);
void PSMTXRotAxisRad(f32 m[3][4], const f32* axis, f32 rad);
void PSMTXRotRad(f32 m[3][4], char axis, f32 rad);
void PSMTXScale(f32 m[3][4], f32 x, f32 y, f32 z);
void PSMTXScaleApply(const f32 src[3][4], f32 dst[3][4], f32 x, f32 y, f32 z);
void PSMTXTransApply(const f32 src[3][4], f32 dst[3][4], f32 x, f32 y, f32 z);
}

inline double fabs(double x) {
    return __fabs(x);
}

// Evaluates a Bezier curve whose points are (time, value) pairs, three pairs per segment.
static inline f32 bezier(const f32* pts, u8 count, f32 t) {
    s32 n = (count - 1) / 3 + 1;
    s32 k;
    for (k = 0; k < n; k++) {
        if (t < pts[k * 6])
            break;
    }
    if (k == 0)
        return pts[1];
    if (k == n)
        return pts[(n - 1) * 6 + 1];
    const f32* seg = pts + (k - 1) * 6;
    f32 u = (t - seg[0]) / (pts[k * 6] - seg[0]);
    f32 iu = 1.0f - u;
    f32 iu2 = iu * iu;
    f32 u2 = u * u;
    return seg[7] * (u2 * u) + (seg[5] * (3.0f * u2 * iu) + (seg[1] * (iu2 * iu) + seg[3] * (3.0f * u * iu2)));
}

bool GsKeyObject::GetShapeMatrix(GSmtx* scaleMtx, GSmtx* mtx, const tagGsFilePrimObjectEntry* entry, u8 count,
                                 const u8* order, const tagGsFilePrimKeyFrame* a,
                                 const tagGsFilePrimKeyFrame* b, f32 t) const {
    f32 rot[3];
    f32 pivot[3];
    f32 trans[3];
    f32 scale[3];
    f32 it = 1.0f - t;
    int i;
    for (i = 0; i < 3; i++) {
        if (a->nScale[i] != 0) {
            scale[i] = header->rangeScale * bezier(a->cScale[i], a->nScale[i], t);
        } else {
            scale[i] = it * a->scale[i] + t * b->scale[i];
        }
    }
    for (i = 0; i < 3; i++) {
        if (a->nTrans[i] != 0) {
            trans[i] = header->rangeTrans * bezier(a->cTrans[i], a->nTrans[i], t);
        } else {
            trans[i] = it * a->trans[i] + t * b->trans[i];
        }
    }
    for (i = 0; i < 3; i++) {
        if (a->nPivot[i] != 0) {
            pivot[i] = header->rangePivot * bezier(a->cPivot[i], a->nPivot[i], t);
        } else {
            pivot[i] = it * a->pivot[i] + t * b->pivot[i];
        }
    }
    for (i = 0; i < 3; i++) {
        if (a->nRot[i] != 0) {
            rot[i] = header->rangeRot * bezier(a->cRot[i], a->nRot[i], t);
        } else {
            rot[i] = it * a->rot[i] + t * b->rot[i];
        }
    }
    f32 npx = -pivot[0];
    f32 npy = -pivot[1];
    f32 npz = -pivot[2];
    f32 sx = scale[0], sy = scale[1], sz = scale[2];
    f32 rx = rot[0], ry = rot[1], rz = rot[2];
    f32 tx = trans[0], ty = trans[1], tz = trans[2];
    f32 px = pivot[0], py = pivot[1], pz = pivot[2];
    u8 identityScale = 1;
    memcpy(mtx, &mtxIdent, 0x30);
    for (int n = 0; n < count; n++, order++) {
        switch (*order) {
        case 4:
            if (n != 0) {
                if ((f32)fabs(sx - 1.0f) > 0.00001f || (f32)fabs(sy - 1.0f) > 0.00001f ||
                    (f32)fabs(sz - 1.0f) > 0.00001f) {
                    PSMTXTransApply(mtx->m, mtx->m, npx, npy, npz);
                    PSMTXScaleApply(mtx->m, mtx->m, sx, sy, sz);
                    PSMTXTransApply(mtx->m, mtx->m, px, py, pz);
                    identityScale = 0;
                }
            }
            break;
        case 0:
            PSMTXTransApply(mtx->m, mtx->m, tx, ty, tz);
            break;
        case 1:
            if ((f32)fabs(rx) > 0.00001f) {
                GSmtx r;
                PSMTXTransApply(mtx->m, mtx->m, npx, npy, npz);
                PSMTXRotRad(r.m, 'X', 0.017453292f * rx);
                PSMTXConcat(r.m, mtx->m, mtx->m);
                PSMTXTransApply(mtx->m, mtx->m, px, py, pz);
            }
            break;
        case 2:
            if ((f32)fabs(ry) > 0.00001f) {
                GSmtx r;
                PSMTXTransApply(mtx->m, mtx->m, npx, npy, npz);
                PSMTXRotRad(r.m, 'Y', 0.017453292f * ry);
                PSMTXConcat(r.m, mtx->m, mtx->m);
                PSMTXTransApply(mtx->m, mtx->m, px, py, pz);
            }
            break;
        case 3:
            if ((f32)fabs(rz) > 0.00001f) {
                GSmtx r;
                PSMTXTransApply(mtx->m, mtx->m, npx, npy, npz);
                PSMTXRotRad(r.m, 'Z', 0.017453292f * rz);
                PSMTXConcat(r.m, mtx->m, mtx->m);
                PSMTXTransApply(mtx->m, mtx->m, px, py, pz);
            }
            break;
        }
    }
    if (identityScale == 1) {
        PSMTXScale(scaleMtx->m, sx, sz, sy);
    } else {
        memcpy(scaleMtx, &mtxIdent, 0x30);
    }
    if (entry->hasRot != 0) {
        if (entry->hasAxisA != 0) {
            f32 axis[3];
            GSmtx r;
            axis[0] = entry->axisA[0];
            axis[1] = entry->axisA[1];
            axis[2] = entry->axisA[2];
            PSMTXRotAxisRad(r.m, axis, entry->angleA);
            PSMTXConcat(r.m, scaleMtx->m, scaleMtx->m);
        }
        if (entry->hasAxisB != 0) {
            f32 axis[3];
            GSmtx r;
            axis[0] = entry->axisB[0];
            axis[1] = entry->axisB[1];
            axis[2] = entry->axisB[2];
            PSMTXRotAxisRad(r.m, axis, entry->angleB);
            PSMTXConcat(r.m, scaleMtx->m, scaleMtx->m);
        }
        PSMTXTransApply(scaleMtx->m, scaleMtx->m, entry->pos[0], entry->pos[1], entry->pos[2]);
    }
    return true;
}

bool GsKeyObject::GetGradationParameter(u8* kind, tagGScol4ub* out, const tagGsFilePrimKeyFrame* a,
                                        const tagGsFilePrimKeyFrame* b, f32 t) const {
    const tagGScol4ub* pa;
    const tagGScol4ub* pb;
    u32 n;
    *kind = a->gradKind;
    if (a->gradKind == 0) {
        pa = a->grad0;
        pb = b->grad0;
        n = a->nGrad0;
    } else {
        pa = a->grad1;
        pb = b->grad1;
        n = a->nGrad1;
    }
    f32 it = 1.0f - t;
    for (u32 i = 0; i < n; i++, out++, pa++, pb++) {
        out->r = (s8)(it * (f32)pa->r + t * (f32)pb->r);
        out->g = (s8)(it * (f32)pa->g + t * (f32)pb->g);
        out->b = (s8)(it * (f32)pa->b + t * (f32)pb->b);
        out->a = (s8)(it * (f32)pa->a + t * (f32)pb->a);
    }
    return true;
}

bool GsKeyObject::GetTwistParameter(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                                    f32 t) const {
    u32 n = a->nTwist;
    const f32* pa = a->twist;
    const f32* pb = b->twist;
    for (u32 i = 0; i < n; i++) {
        out[i] = (1.0f - t) * pa[i] + t * pb[i];
    }
    return true;
}

bool GsKeyObject::GetDeformParameterV(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                                      f32 t) const {
    u32 n = a->nDeformV;
    const f32* pa = a->deformV;
    const f32* pb = b->deformV;
    for (u32 i = 0; i < n; i++) {
        out[i] = (1.0f - t) * pa[i] + t * pb[i];
    }
    return true;
}

bool GsKeyObject::GetDeformParameterU(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                                      f32 t) const {
    u32 n = a->nDeformU;
    const f32* pa = a->deformU;
    const f32* pb = b->deformU;
    for (u32 i = 0; i < n; i++) {
        out[i] = (1.0f - t) * pa[i] + t * pb[i];
    }
    return true;
}

bool GsKeyObject::GetLinearParameterV(f32* out, const tagGsFilePrimKeyFrame* a) {
    u32 n = a->nDeformV;
    f32 last = (f32)(n - 1);
    for (u32 i = 0; i < n; i++) {
        out[i] = (f32)i / last;
    }
    return true;
}

bool GsKeyObject::GetLinearParameterU(f32* out, const tagGsFilePrimKeyFrame* a) {
    u32 n = a->nDeformU;
    f32 last = (f32)(n - 1);
    for (u32 i = 0; i < n; i++) {
        out[i] = (f32)i / last;
    }
    return true;
}

tagGScol4ub GsKeyObject::GetTextureColorLow(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b,
                                            f32 t, u32 idx) const {
    tagGScol4ub col;
    f32 v[4];
    if (header->texFlag[idx] == 0) {
        const u8* src = frames[0]->texColorLow[idx];
        col.r = src[0];
        col.g = src[1];
        col.b = src[2];
        col.a = src[3];
        return col;
    }
    f32 it = 1.0f - t;
    for (int i = 0; i < 4; i++) {
        if (a->nTexColorLow[idx][i] != 0) {
            v[i] = 255.0f * bezier(a->cTexColorLow[idx][i], a->nTexColorLow[idx][i], t);
            if (v[i] < 0.0f) {
                v[i] = 0.0f;
            } else if (v[i] > 255.0f) {
                v[i] = 255.0f;
            }
        } else {
            v[i] = it * (f32)a->texColorLow[idx][i] + t * (f32)b->texColorLow[idx][i];
        }
    }
    col.r = (s8)v[0];
    col.g = (s8)v[1];
    col.b = (s8)v[2];
    col.a = (s8)v[3];
    return col;
}

tagGScol4ub GsKeyObject::GetTextureColor(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t,
                                         u32 idx) const {
    tagGScol4ub col;
    f32 v[4];
    if (header->texFlag[idx] == 0) {
        const u8* src = frames[0]->texColor[idx];
        col.r = src[0];
        col.g = src[1];
        col.b = src[2];
        col.a = src[3];
        return col;
    }
    f32 it = 1.0f - t;
    for (int i = 0; i < 4; i++) {
        if (a->nTexColor[idx][i] != 0) {
            v[i] = 255.0f * bezier(a->cTexColor[idx][i], a->nTexColor[idx][i], t);
            if (v[i] < 0.0f) {
                v[i] = 0.0f;
            } else if (v[i] > 255.0f) {
                v[i] = 255.0f;
            }
        } else {
            v[i] = it * (f32)a->texColor[idx][i] + t * (f32)b->texColor[idx][i];
        }
    }
    col.r = (s8)v[0];
    col.g = (s8)v[1];
    col.b = (s8)v[2];
    col.a = (s8)v[3];
    return col;
}

GsVec2 GsKeyObject::GetTextureOffset(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t,
                                   u32 idx) const {
    GsVec2 r;
    f32* v = r.v;
    f32 it = 1.0f - t;
    for (int i = 0; i < 2; i++) {
        if (a->nTexOffset[idx][i] != 0) {
            v[i] = header->rangeTexOffset * bezier(a->cTexOffset[idx][i], a->nTexOffset[idx][i], t);
        } else {
            v[i] = it * a->texOffset[idx][i] + t * b->texOffset[idx][i];
        }
    }
    return r;
}

GsVec2 GsKeyObject::GetTextureScale(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t,
                                  u32 idx) const {
    GsVec2 r;
    f32* v = r.v;
    f32 it = 1.0f - t;
    for (int i = 0; i < 2; i++) {
        if (a->nTexScale[idx][i] != 0) {
            v[i] = header->rangeTexScale * bezier(a->cTexScale[idx][i], a->nTexScale[idx][i], t);
        } else {
            v[i] = it * a->texScale[idx][i] + t * b->texScale[idx][i];
        }
    }
    return r;
}

bool GsKeyObject::GetShapeShowAngle(f32* o0, f32* o1, const tagGsFilePrimKeyFrame* a,
                                    const tagGsFilePrimKeyFrame* b, f32 t) const {
    f32* dst[2] = {o0, o1};
    f32 it = 1.0f - t;
    for (int i = 0; i < 2; i++) {
        if (a->nShowAngle[i] != 0) {
            *dst[i] = header->rangeShowAngle * bezier(a->cShowAngle[i], a->nShowAngle[i], t);
        } else {
            *dst[i] = a->showAngle[i] * it + b->showAngle[i] * t;
        }
    }
    return true;
}

bool GsKeyObject::GetShapeRadius(f32* o0, f32* o1, const tagGsFilePrimKeyFrame* a,
                                 const tagGsFilePrimKeyFrame* b, f32 t) const {
    f32* dst[2] = {o0, o1};
    f32 it = 1.0f - t;
    for (int i = 0; i < 2; i++) {
        if (a->nRadius[i] != 0) {
            *dst[i] = header->rangeRadius * bezier(a->cRadius[i], a->nRadius[i], t);
            if (*dst[i] < 0.0f) {
                *dst[i] = 0.0f;
            }
        } else {
            *dst[i] = a->radius[i] * it + b->radius[i] * t;
        }
    }
    return true;
}

f32 GsKeyObject::GetShapeColorAlpha(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    f32 v;
    f32 it = 1.0f - t;
    if (a->nColor[3] != 0) {
        v = 255.0f * bezier(a->cColor[3], a->nColor[3], t);
        if (v < 0.0f) {
            v = 0.0f;
        } else if (v > 255.0f) {
            v = 255.0f;
        }
    } else {
        v = it * (f32)a->color[3] + t * (f32)b->color[3];
    }
    return v / 255.0f;
}

tagGScol4ub GsKeyObject::GetShapeColor(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    tagGScol4ub col;
    f32 v[4];
    f32 it = 1.0f - t;
    for (int i = 0; i < 4; i++) {
        if (a->nColor[i] != 0) {
            v[i] = 255.0f * bezier(a->cColor[i], a->nColor[i], t);
            if (v[i] < 0.0f) {
                v[i] = 0.0f;
            } else if (v[i] > 255.0f) {
                v[i] = 255.0f;
            }
        } else {
            v[i] = it * (f32)a->color[i] + t * (f32)b->color[i];
        }
    }
    col.r = (s8)v[0];
    col.g = (s8)v[1];
    col.b = (s8)v[2];
    col.a = (s8)v[3];
    return col;
}

bool GsKeyObject::GetFrameInterval(u32 frame, tagGsFilePrimKeyFrame*& a, tagGsFilePrimKeyFrame*& b, f32& t) {
    for (u32 i = 0; i < header->count; i++) {
        if (frame <= frames[i]->time) {
            u32 prev = i;
            if (i != 0) {
                prev = i - 1;
            }
            a = frames[prev];
            b = frames[i];
            if (i != prev) {
                t = (f32)(frame - a->time) / (f32)(b->time - a->time);
            } else {
                t = 0.0f;
            }
            return true;
        }
    }
    return false;
}
