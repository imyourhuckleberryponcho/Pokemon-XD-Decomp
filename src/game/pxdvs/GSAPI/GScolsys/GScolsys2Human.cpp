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
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct GSCOLSYS2_HUMAN;
enum GSgfxLayerID { GSgfxLayerID_draft_dummy };
struct GSgfxVF;
struct GSvec;
struct GSwalkHit;
struct PeopleWork;
struct Vec;
struct tagPeopleWork;

extern "C" {
struct GSCOLSYS2_HUMAN {
    u8 _draft[1];
};
struct GSgfxVF {
    u8 _draft[1];
};
struct GSvec {
    f32 x, y, z;
};
struct GSwalkHit {
    f32 height;
    u8 unk4[8];
};
struct PeopleWork {
    u8 _draft[1];
};
struct Vec {
    u8 _draft[1];
};
struct tagPeopleWork {
    u8 _draft[1];
    bool isFollower() const;
    bool isHero() const;
};

extern "C" {
void GScameraLoadActiveCameraMatrix(GSgfxLayerID id);
void* GScolsys2GetCurFloor();
s32 GScolsys2HumanAddCurrentFloor(s32 *p0, void *p1);
s32 GScolsys2HumanCollision(int p0, s32 p1, s32 p2, s32 p3);
void GScolsys2HumanDispColision();
s32 GScolsys2HumanEnable(s32 index, u8 enable);
f32 GScolsys2HumanGetHumanRadius(s32 p0);
f32 GScolsys2HumanGetWalkHighest(void *p0);
s32 GScolsys2WalkGetHeight(GSvec* pos, GSwalkHit* outHits);
void GSgfxBeginSurface(unsigned short num);
void GSgfxBlendMode(int type, u32 src, u32 dst);
void GSgfxColor4u8(u8 r, u8 g, u8 b, u8 a);
void GSgfxCullMode(u32 mode);
void GSgfxEndSurface(void);
void GSgfxLayerSetActive(int id);
void GSgfxPixelMode(u8 colorUpdate, u8 alphaUpdate, u8 dither);
void GSgfxSetLineWidth(f32 width);
void GSgfxSetPrimitiveType(u32 type);
void GSgfxSetupRenderAndSelect(GSgfxVF* vf);
s32 GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32);
void GSgfxVertex3f(f32 x, f32 y, f32 z);
asm void PSVECAdd(const register Vec* a, const register Vec* b, register Vec* ab);
f32 PSVECDistance(const register Vec* a, const register Vec* b);
void PSVECScale(const register Vec* src, register Vec* dst, register f32 scale);
asm void PSVECSubtract(const register Vec* a, const register Vec* b, register Vec* a_b);
double cos(double x);
u8 gimmickBoxFixDistanceForPushBox(f32*, s32, f32, f32, f32);
u8 gimmickBoxIsBox(s32);
s32 heroGetFollower();
s32 heroMoveGetHeroPos(s32*);
void* peopleBiosGetPosPtr(PeopleWork* work);
u32 peopleGetHumanID(s32, s32);
void peopleGetPos(s32, s32, GSvec*);
f32 peopleGetTalkDistance(s32, s32);
s32 peopleSearchID();
double sin(double x);
extern f32 __float_nan[];
}
extern "C++" {
static u8 checkCollisionHeadToHead(GSCOLSYS2_HUMAN* p0, GSCOLSYS2_HUMAN* p1, GSvec* p2, GSvec* p3);
static u8 checkCollision(GSCOLSYS2_HUMAN* p0, int p1, GSvec* p2, GSvec* p3, GSvec* p4);
}

extern "C" {
f32 GScolsys2HumanGetWalkHeight(void *p0);
inline double fabs(double x) { return __fabs(x); }
}

inline int __fpclassifyf(float x)
{
    switch ((*(s32*) &x) & 0x7F800000) {
    case 0x7F800000:
        if ((*(s32*) &x) & 0x007FFFFF) {
            return 1;
        } else {
            return 2;
        }
    case 0:
        if ((*(s32*) &x) & 0x007FFFFF) {
            return 5;
        } else {
            return 3;
        }
    }
    return 4;
}

inline float sqrtf(float x)
{
    if (x > 0.0f) {
        double guess = __frsqrte((double) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return (float) (x * guess);
    } else if (x < 0.0) {
        return __float_nan[0];
    } else if (__fpclassifyf(x) == 1) {
        return __float_nan[0];
    }
    return x;
}
static f32 fix_S2135;
static u8 init_S2136;
struct HumanEvent {
    s32 key0;
    u32 key1;
    f32 radius;
    f32 height;
    u16 flags;
    u8 unk12[2];
};

struct HumanFloor {
    u8 unk0[0xA00];
    HumanEvent events[48];
};

static inline s32 GScolsys2HumanGetEvent(s32 index, HumanEvent** out)
{
    HumanFloor* floor;
    HumanEvent* event;

    if (index < 0 || index >= 48) {
        return 4;
    }
    floor = (HumanFloor*)GScolsys2GetCurFloor();
    if (floor == NULL) {
        return 1;
    }
    event = &floor->events[index];
    if ((event->flags & 1) == 0) {
        return 4;
    }
    *out = event;
    return 0;
}

f32 GScolsys2HumanGetHumanRadius(s32 index) {
    HumanEvent* event;
    if (GScolsys2HumanGetEvent(index, &event) != 0) {
        return 0.0f;
    }
    return event->radius;
}
}

extern "C" {
void GScolsys2HumanDispColision() {
    volatile f32 sp18;
    f32 sp14;
    volatile f32 sp10;
    f32 temp_f28;
    volatile f32 temp_f26;
    f32 temp_f27;
    f32 temp_f27_2;
    volatile s32 sp8;
    f32 temp_f28_2;
    f32 temp_f4;
    s32 var_r29;
    s32 var_r29_2;
    u16 temp_r3_2;
    u8 *temp_r3;
    u8 *var_r28;

    temp_r3 = (unsigned char *)(GScolsys2GetCurFloor());
    if (temp_r3 != NULL) {
        GSgfxLayerSetActive(2);
        GScameraLoadActiveCameraMatrix((GSgfxLayerID)(2));
        GSgfxCullMode(0U);
        sp8 = 0;
        GSgfxSetupRenderAndSelect((GSgfxVF*)(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0)));
        GSgfxBlendMode(1, 4U, 5U);
        GSgfxPixelMode(1U, 1U, 1U);
        GSgfxSetLineWidth(2.0f);
        var_r28 = temp_r3 + 0xA00;
        while (var_r28 != (u8 *) (temp_r3 + 0xDC0)) {
            temp_r3_2 = M2C_FIELD(var_r28, u16 *, 0x10);
            if ((temp_r3_2 & 1) && !(temp_r3_2 & 2)) {
                sp18 = 0.0f;
                sp10 = 0.0f;
                peopleGetPos(M2C_FIELD(var_r28, s32 *, 0), M2C_FIELD(var_r28, s32 *, 4), (GSvec*)((GSvec *) &sp10));
                GSgfxSetPrimitiveType(0xA0U);
                GSgfxBeginSurface(0x12U);
                GSgfxVertex3f(sp10, 0.1f + sp14, sp18);
                GSgfxColor4u8(0U, 0x7FU, 0x7FU, 0xC0U);
                sp14 = 0.0f;
                var_r29 = 0;
                do {
                    temp_f27 = (f32) var_r29;
                    temp_f27 *= 0.3926991f;
                    temp_f28 = (f32) sin((f64) temp_f27);
                    temp_f4 = M2C_FIELD(var_r28, f32 *, 8);
                    GSgfxVertex3f((temp_f4 * (f32) cos((f64) temp_f27)) + sp10, 0.1f + sp14, (temp_f4 * temp_f28) + sp18);
                    GSgfxColor4u8(0U, 0x7FU, 0x7FU, 0xC0U);
                    var_r29 += 1;
                } while (var_r29 < 0x11);
                GSgfxEndSurface();
                GSgfxSetPrimitiveType(0xB0U);
                GSgfxBeginSurface(0x11U);
                temp_f26 = M2C_FIELD(var_r28, f32 *, 8) + peopleGetTalkDistance(M2C_FIELD(var_r28, s32 *, 0), M2C_FIELD(var_r28, s32 *, 4));
                var_r29_2 = 0;
                do {
                    temp_f27_2 = 0.3926991f * (f32) var_r29_2;
                    temp_f28_2 = (f32) sin((f64) temp_f27_2);
                    GSgfxVertex3f((temp_f26 * (f32) cos((f64) temp_f27_2)) + sp10, 0.15f + sp14, (temp_f26 * temp_f28_2) + sp18);
                    GSgfxColor4u8(0x7FU, 0x7FU, 0xFFU, 0xC0U);
                    var_r29_2 += 1;
                } while (var_r29_2 < 0x11);
                GSgfxEndSurface();
            }
            var_r28 += 0x14;
        }
    }
}
extern "C++" {
static u8 checkCollisionHeadToHead(GSCOLSYS2_HUMAN* p0, GSCOLSYS2_HUMAN* p1, GSvec* p2, GSvec* p3) {
    volatile f32 sp14;
    s32 sp10;
    bool temp_r31;
    f32 sp8;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f2;
    f32 temp_f3;
    f32 var_f31;
    f32 var_f30;
    f32 var_f29;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;
    s32 temp_r3;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 var_r0;
    f32 spC;
    u8 *temp_r3_2;

    peopleGetHumanID(M2C_FIELD(p0, s32 *, 0), M2C_FIELD(p0, s32 *, 4));
    temp_r3 = peopleSearchID();
    if (temp_r3 == 0) {
        return 0;
    }
    temp_r3_2 = (unsigned char *)(peopleBiosGetPosPtr((PeopleWork*)((PeopleWork *) temp_r3)));
    if (temp_r3_2 == NULL) {
        return 0;
    }
    var_f29 = M2C_FIELD(p2, f32 *, 8) - M2C_FIELD(temp_r3_2, f32 *, 8);
    var_f30 = M2C_FIELD(p2, f32 *, 0) - M2C_FIELD(temp_r3_2, f32 *, 0);
    var_f31 = (var_f30 * var_f30) + (var_f29 * var_f29);
    var_f31 = sqrtf(var_f31);
    temp_f3 = M2C_FIELD(p0, f32 *, 8);
    spC = temp_f3 + M2C_FIELD(p1, f32 *, 8);
    temp_r31 = gimmickBoxFixDistanceForPushBox(&spC, temp_r3, var_f30, var_f29, temp_f3) == 0;
    if (gimmickBoxIsBox(temp_r3) != 0) {
        heroMoveGetHeroPos(&sp10);
        temp_f1_4 = (M2C_FIELD(temp_r3_2, f32 *, 4) + M2C_FIELD(p0, f32 *, 0xC)) - sp14;
        if ((temp_f1_4 < 0.00001f) && (temp_f1_4 > -0.00001f) && (temp_r31 == 0)) {
            return 0;
        }
        goto block_29;
    }
    temp_f2 = M2C_FIELD(p2, f32 *, 4);
    temp_f1_5 = M2C_FIELD(temp_r3_2, f32 *, 4);
    if ((temp_f1_5 >= (temp_f2 + M2C_FIELD(p1, f32 *, 0xC))) || (M2C_ERROR( ), (((temp_f1_5 + M2C_FIELD(p0, f32 *, 0xC)) == temp_f2) != 0))) {
        return 0;
    }
block_29:
    if (var_f31 >= spC) {
        return 0;
    }
    if (var_f31 <= 0.0f) {
        var_f30 = 1.0f;
        var_f31 = 1.0f;
    }
    peopleGetHumanID(M2C_FIELD(p1, s32 *, 0), M2C_FIELD(p1, s32 *, 4));
    temp_r3_4 = peopleSearchID();
    if (temp_r3_4 == 0) {
        return 0;
    }
    if ((gimmickBoxIsBox(temp_r3) != 0) || (gimmickBoxIsBox(temp_r3) != 0)) {
        temp_f28 = M2C_FIELD(peopleBiosGetPosPtr((PeopleWork*)((PeopleWork *) temp_r3_4)), f32 *, 4);
        if ((f32) fabs(M2C_FIELD(peopleBiosGetPosPtr((PeopleWork*)((PeopleWork *) temp_r3)), f32 *, 4) - temp_f28) > 2.0f) {
            return 0;
        }
    }
    if ((s8) init_S2136 == 0) {
        init_S2136 = 1;
        fix_S2135 = 0.99f;
    }
    if (heroGetFollower() != 0U) {
        if ((((tagPeopleWork*)((tagPeopleWork *) temp_r3_4))->isHero() != 0) && (((tagPeopleWork*)((tagPeopleWork *) temp_r3))->isFollower() != 0)) {
            spC *= fix_S2135;
        } else if ((((tagPeopleWork*)((tagPeopleWork *) temp_r3))->isHero() != 0) && (((tagPeopleWork*)((tagPeopleWork *) temp_r3_4))->isFollower() != 0)) {
            spC *= fix_S2135;
        }
    }
    if (var_f31 >= spC) {
        return 0;
    }
    temp_f28_2 = (0.0001f + spC) / var_f31;
    if ((gimmickBoxIsBox(temp_r3) != 0) && (temp_r31 != 0)) {
        if (fabs(var_f30) > (f32) fabs(var_f29)) {
            var_f30 *= temp_f28_2;
        } else {
            var_f29 *= temp_f28_2;
        }
    } else {
        var_f30 *= temp_f28_2;
        var_f29 *= temp_f28_2;
    }
    if (p3 != NULL) {
        M2C_FIELD(p3, f32 *, 4) = (f32) M2C_FIELD(p2, f32 *, 4);
        M2C_FIELD(p3, f32 *, 8) = (f32) (M2C_FIELD(temp_r3_2, f32 *, 8) + var_f29);
        M2C_FIELD(p3, f32 *, 0) = (f32) (M2C_FIELD(temp_r3_2, f32 *, 0) + var_f30);
    }
    return 1;
}
}

}

extern "C++" {
extern "C++" {
#pragma peephole off
static u8 checkCollision(GSCOLSYS2_HUMAN* human, int index, GSvec* start, GSvec* end, GSvec* out) {
    GSvec push;
    GSvec pos;
    HumanFloor* floor;
    s32 i;
    s32 count;
    HumanEvent* ev;
    GSvec* pushp = &push;

    pos = *end;
    floor = (HumanFloor*)GScolsys2GetCurFloor();
    count = 0;
    do {
        for (ev = floor->events, i = 0; i < 48; i++, ev++) {
            if (i != index && (ev->flags & 1) && !(ev->flags & 2) &&
                checkCollisionHeadToHead((GSCOLSYS2_HUMAN*)ev, human, &pos, pushp)) {
                break;
            }
        }
        if (i >= 48) {
            break;
        }
        count++;
        pos = *pushp;
    } while (count < 10);
    if (count <= 0) {
        return 0;
    }
    {
        f32 x = pos.x;
        f32 y = pos.y;
        f32 z = pos.z;
        if (out != NULL) {
            out->x = x;
            out->y = y;
            out->z = z;
        }
    }
    return 1;
}
#pragma peephole reset
}

extern "C" {

s32 GScolsys2HumanCollision(int index, s32 start, s32 end, s32 result) {
    HumanEvent* event;
    f32 delta[3];
    f32 segmentStart[3];
    f32 segmentEnd[3];
    f32 distance;
    f32 step;
    f32 t;
    f32 next;
    s32 status;

    status = GScolsys2HumanGetEvent(index, &event);
    if (status != 0) {
        return status;
    }

    distance = PSVECDistance((Vec*)start, (Vec*)end);
    if (distance > 0.0f) {
        step = event->radius / distance;
        if (step > 1.0f) {
            step = 1.0f;
        }
    } else {
        step = 0.0f;
    }
    PSVECSubtract((Vec*)end, (Vec*)start, (Vec*)delta);
    t = 0.0f;
    while (t < 1.0f) {
        next = t + step;
        if (next > 1.0f) {
            next = 1.0f;
        }
        PSVECScale((Vec*)delta, (Vec*)segmentStart, t);
        PSVECAdd((Vec*)segmentStart, (Vec*)start, (Vec*)segmentStart);
        PSVECScale((Vec*)delta, (Vec*)segmentEnd, next);
        PSVECAdd((Vec*)segmentEnd, (Vec*)start, (Vec*)segmentEnd);
        if (checkCollision((GSCOLSYS2_HUMAN*)event, index, (GSvec*)segmentStart, (GSvec*)segmentEnd,
                           (GSvec*)result)) {
            return 6;
        }
        if (step <= 0.0f) {
            break;
        }
        t += step;
    }
    return 7;
}
}

extern "C" {
s32 GScolsys2HumanEnable(s32 index, u8 enable)
{
    HumanEvent* event;
    s32 result;

    result = GScolsys2HumanGetEvent(index, &event);
    if (result != 0) {
        return result;
    }
    if (enable != 0) {
        event->flags &= ~2;
    } else {
        event->flags |= 2;
    }
    return 0;
}
}

extern "C" {
s32 GScolsys2HumanAddCurrentFloor(s32* outIndex, void* p1) {
    HumanEvent* src = (HumanEvent*)p1;
    HumanFloor* floor;
    s32 i;

    floor = (HumanFloor*)GScolsys2GetCurFloor();
    if (floor == NULL) {
        return 1;
    }
    for (i = 0; i < 48; i++) {
        if ((floor->events[i].flags & 1) == 0) {
            break;
        }
    }
    if (i >= 48) {
        return 5;
    }
    floor->events[i].key0 = src->key0;
    floor->events[i].key1 = src->key1;
    if (src->key1 == 0x65 || src->key1 == 0x68 || src->key1 == 0x69) {
        floor->events[i].radius = 3.0f;
    } else {
        floor->events[i].radius = src->radius;
    }
    floor->events[i].height = src->height;
    floor->events[i].flags = 0;
    floor->events[i].flags |= 1;
    *outIndex = i;
    return 0;
}
extern "C" {
f32 GScolsys2HumanGetWalkHeight(void* p0) {
    GSvec* p = (GSvec*)p0;
    GSvec pos;
    GSwalkHit hits[8];
    s32 n;
    s32 i;
    f32 h;
    f32 max;
    f32 below;
    u8 found;
    f32 result;
    f32 d;
    f32 dist;

    pos.x = p->x;
    pos.y = p->y;
    pos.z = p->z;
    n = GScolsys2WalkGetHeight(&pos, hits);
    if (n >= 2) {
        below = -1000000.0f;
        found = 0;
        max = below;
        for (i = 0; i < n; i++) {
            h = hits[i].height;
            if (max < h) {
                max = h;
            }
            if (!(h - pos.y >= 10.0f) && below < h) {
                below = h;
                found = 1;
            }
        }
        if (found) {
            pos.y = below;
        } else {
            pos.y = max;
        }
        if ((f32)fabs(pos.y - p->y) >= 10.0f) {
            result = hits[0].height;
            dist = (f32)fabs(p->y - result);
            for (i = 1; i < n; i++) {
                d = (f32)fabs(p->y - hits[i].height);
                if (dist >= d) {
                    if (dist > d) {
                        dist = d;
                        result = hits[i].height;
                    } else if (result < hits[i].height) {
                        result = hits[i].height;
                    }
                }
            }
            pos.y = result;
        }
    } else if (n > 0) {
        pos.y = hits[0].height;
    } else {
        pos.y = 0.0f;
    }
    return pos.y;
}
}

}

extern "C" {
extern "C" {
f32 GScolsys2HumanGetWalkHighest(void* p0) {
    GSvec* p = (GSvec*)p0;
    GSvec pos;
    GSwalkHit hits[9];
    s32 n;
    s32 i;
    f32 max;

    pos.x = p->x;
    pos.y = p->y;
    pos.z = p->z;
    n = GScolsys2WalkGetHeight(&pos, hits);
    if (n >= 2) {
        max = -1000000.0f;
        for (i = 0; i < n; i++) {
            if (max < hits[i].height) {
                max = hits[i].height;
            }
        }
        return max;
    }
    if (n > 0) {
        return hits[0].height;
    }
    return 0.0f;
}
}
}
}
