#define FP_NAN 1
#define FP_INFINITE 2
#define FP_ZERO 3
#define FP_NORMAL 4
#define FP_SUBNORMAL 5

extern int __float_nan[];
#define NAN (*(float*)__float_nan)

double tan(double x);
double sin(double x);
double cos(double x);
double acos(double x);
int __fpclassifyf(float x);

// Inline copy of __fpclassifyf (the out-of-line one is emitted at the end).
static inline int __fpclassifyf_inline(float x) {
    switch ((*(int*)&x) & 0x7f800000) {
    case 0x7f800000:
        if ((*(int*)&x) & 0x007fffff) {
            return FP_NAN;
        } else {
            return FP_INFINITE;
        }
    case 0:
        if ((*(int*)&x) & 0x007fffff) {
            return FP_SUBNORMAL;
        } else {
            return FP_ZERO;
        }
    }
    return FP_NORMAL;
}

#define isnan(x) (__fpclassifyf_inline(x) == FP_NAN)

__declspec(weak) double fabs(double x) {
    return __fabs(x);
}

__declspec(weak) float sqrtf(float x) {
    static const double _half = .5;
    static const double _three = 3.0;

    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        return (float)(x * guess);
    } else if (x < 0.0) {
        return NAN;
    } else if (isnan(x)) {
        return NAN;
    }
    return x;
}

__declspec(weak) float tanf(float x) {
    return (float)tan((double)x);
}

__declspec(weak) float sinf(float x) {
    return (float)sin((double)x);
}

__declspec(weak) float cosf(float x) {
    return (float)cos((double)x);
}

__declspec(weak) float acosf(float x) {
    return (float)acos((double)x);
}

__declspec(weak) int __fpclassifyf(float x) {
    switch ((*(int*)&x) & 0x7f800000) {
    case 0x7f800000:
        if ((*(int*)&x) & 0x007fffff) {
            return FP_NAN;
        } else {
            return FP_INFINITE;
        }
    case 0:
        if ((*(int*)&x) & 0x007fffff) {
            return FP_SUBNORMAL;
        } else {
            return FP_ZERO;
        }
    }
    return FP_NORMAL;
}
