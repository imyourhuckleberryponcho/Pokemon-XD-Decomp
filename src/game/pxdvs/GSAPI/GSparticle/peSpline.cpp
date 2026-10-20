// STATUS: default flags, LAYOUT OK, CONST OK. peSplineGetValue 96.3% (float register numbering
// of w/u2 in the Hermite case), peColorSplineGetValue 95.9% (integer register numbering of count/keys/idx).
// Uses the SDK OSFastCast u8<->f32 inlines (psq_l/psq_st with GQR2). Not linkable yet.
#include <dolphin/types.h>

struct peColorSpline {
    u8 count;    // 0x0
    u8 index;    // 0x1
    u8 pad2[2];
    u8 cur[3];   // 0x4
    u8 pad7;
    f32 lastT;   // 0x8
    u8 keys[1][4]; // 0xC: count RGBA keys, then count f32 times, then count f32 inverse intervals
};

struct peSpline {
    u8 flags;    // 0x0: bits 0-1 type, bit 2 allows overshoot below zero
    u8 count;    // 0x1
    u8 pad2[2];
    f32 cur;     // 0x4
    f32 lastT;   // 0x8
    f32 data[1]; // 0xC
};

// From the Dolphin SDK's OSFastCast.h (GQR2 is set up for u8 conversion).
static inline f32 __OSu8tof32(register const u8* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, 2 }
    return ret;
}

static inline f32 OSu8tof32(u8 in) {
    u8 tmp = in;
    return __OSu8tof32(&tmp);
}

static inline void __OSf32tou8(register f32 arg, volatile register u8* out) {
    asm { psq_st arg, 0(out), 1, 2 }
}

static inline u8 OSf32tou8(f32 in) {
    u32 out;
    __OSf32tou8(in, (u8*)&out);
    return *(u8*)&out;
}

static inline void lerpColor(u8* out, peColorSpline* s, u8* keys, f32 t) {
    f32 r0 = OSu8tof32(keys[0]);
    f32 g0 = OSu8tof32(keys[1]);
    f32 b0 = OSu8tof32(keys[2]);
    f32 r1 = OSu8tof32(keys[4]);
    f32 g1 = OSu8tof32(keys[5]);
    f32 b1 = OSu8tof32(keys[6]);
    s->cur[0] = OSf32tou8(r0 + t * (r1 - r0));
    s->cur[1] = OSf32tou8(g0 + t * (g1 - g0));
    s->cur[2] = OSf32tou8(b0 + t * (b1 - b0));
    out[0] = s->cur[0];
    out[1] = s->cur[1];
    out[2] = s->cur[2];
}

static inline f32 hermite(f32 p0, f32 p1, f32 m0, f32 m1, f32 h00, f32 h01, f32 h10, f32 h11, f32 w) {
    return w * (h10 * m0 + h11 * m1) + (h01 * p1 + h00 * p0);
}

extern "C" {

void peColorSplineGetValue(u8* out, peColorSpline* s, f32 t) {
    u8 count = s->count;
    u8 idx;
    u8 (*keys)[4];
    if (count >= 2) {
        keys = s->keys;
        f32* times;
        if (t <= 0.0f) {
            out[0] = keys[0][0];
            out[1] = keys[0][1];
            out[2] = keys[0][2];
            return;
        }
        if (t >= 1.0f) {
            keys += count - 1;
            out[0] = keys[0][0];
            out[1] = keys[0][1];
            out[2] = keys[0][2];
            return;
        }
        f32 diff = s->lastT - t;
        if (diff < 0.0f) {
            diff = -diff;
        }
        if (diff <= 0.00001f) {
            out[0] = s->cur[0];
            out[1] = s->cur[1];
            out[2] = s->cur[2];
            return;
        }
        s->lastT = t;
        if (count == 2)
            lerpColor(out, s, keys[0], t);
        else {
            f32* inv;
            idx = s->index;
            f32 u;
            times = (f32*)(keys + count);
            inv = times + count;
            if (t < times[idx]) {
                idx = 0;
                s->index = 0;
            }
            while (times[idx + 1] < t) {
                idx++;
                s->index = idx;
                if (idx >= count) {
                    return;
                }
            }
            u = (t - times[idx]) * inv[idx];
            keys += idx;
            lerpColor(out, s, keys[0], u);
        }
    }
}

f32 peSplineGetValue(peSpline* s, f32 t) {
    u8 type = s->flags & 3;
    u8 n;
    u8 i;
    f32* data;
    if (type == 0) {
        return 1.0f;
    }
    n = s->count - 1;
    if (n < 1) {
        return 1.0f;
    }
    data = s->data;
    if (t <= 0.0f) {
        return data[0];
    }
    if (t >= 1.0f) {
        return data[n];
    }
    s->lastT = t;
    if (n == 1) {
        switch (type) {
        case 1:
        case 3:
            s->cur = data[4] * t + data[0];
            break;
        case 2:
            s->cur = data[1];
            break;
        }
        return s->cur;
    } else {
        f32 w;
        i = 0;
        f32* p = data + (n + 1);
        while ((w = *p) < t) {
            i++;
            t -= w;
            p++;
            if (i >= n) {
                return 1.0f;
            }
        }
        f32* q = p + n;
        f32* d = data + i;
        f32* r = q + n;
        t = t * *q;
        switch (type) {
        case 3: {
            f32 u2 = t * t;
            f32 u3 = u2 * t;
            f32 a = u3 - u2;
            f32 b = (u2 + u2) - u3;
            f32 c = a - u2;
            f32 h01 = b - a;
            f32 h00 = 1.0f - h01;
            f32 h10 = t + c;
            f32 lo = (s->flags & 4) ? -1.0f : 0.0f;
            f32 v = hermite(d[0], d[1], r[0], r[n], h00, h01, h10, a, w);
            if (v < lo) {
                v = lo;
            } else if (v > 1.0f) {
                v = 1.0f;
            }
            s->cur = v;
            break;
        }
        case 1:
            s->cur = r[0] * t + d[0];
            break;
        case 2:
            s->cur = d[1];
            break;
        }
        return s->cur;
    }
}

}
