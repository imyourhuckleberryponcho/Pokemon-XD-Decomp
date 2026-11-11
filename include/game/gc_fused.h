#ifndef GAME_GC_FUSED_H
#define GAME_GC_FUSED_H
#if defined(__MWERKS__) && defined(GC_FUSED_CHECK)
static double gcChkAdd(double p, double c) { return p + c; }
static double gcChkSub(double p, double c) { return p - c; }
static double gcChkSubR(double c, double p) { return c - p; }
#define GC_MADD(a, b, c) gcChkAdd((a) * (b), (c))
#define GC_MADDR(c, a, b) gcChkAdd((a) * (b), (c))
#define GC_MSUB(a, b, c) gcChkSub((a) * (b), (c))
#define GC_MSUBR(c, a, b) gcChkSubR((c), (a) * (b))
#define GC_MADD_TO(x, a, b) ((x) = gcChkAdd((a) * (b), (x)))
#define GC_MSUB_FROM(x, a, b) ((x) = gcChkSubR((x), (a) * (b)))
#ifdef __cplusplus
struct GcChk { double v; };
static GcChk gcChk(double p) { GcChk r; r.v = p; return r; }
static double operator+(GcChk p, double c) { return p.v + c; }
static double operator+(double c, GcChk p) { return c + p.v; }
static double operator-(GcChk p, double c) { return p.v - c; }
static double operator-(double c, GcChk p) { return c - p.v; }
static double operator-(GcChk p) { return -p.v; }
static float& operator+=(float& x, GcChk p) { x = (float)(x + p.v); return x; }
static float& operator-=(float& x, GcChk p) { x = (float)(x - p.v); return x; }
static double& operator+=(double& x, GcChk p) { x = x + p.v; return x; }
static double& operator-=(double& x, GcChk p) { x = x - p.v; return x; }
#define GC_FUSED(a, b) gcChk((a) * (b))
#endif
#elif defined(__MWERKS__)
#define GC_FUSED(a, b) ((a) * (b))
#define GC_MADD(a, b, c) ((a) * (b) + (c))
#define GC_MADDR(c, a, b) ((c) + (a) * (b))
#define GC_MSUB(a, b, c) ((a) * (b) - (c))
#define GC_MSUBR(c, a, b) ((c) - (a) * (b))
#define GC_MADD_TO(x, a, b) ((x) += (a) * (b))
#define GC_MSUB_FROM(x, a, b) ((x) -= (a) * (b))
#else

#if defined(_MSC_VER)
#include <corecrt.h>
#ifdef __cplusplus
extern "C" {
#endif
_ACRTIMP double __cdecl fma(double _X, double _Y, double _Z);
#ifdef __cplusplus
}
#endif
#define GC_FUSED_FMA(a, b, c) fma((a), (b), (c))
#else
#define GC_FUSED_FMA(a, b, c) __builtin_fma((a), (b), (c))
#endif

static inline float gcMaddS(float a, float b, float c) { return (float)((double)a * (double)b + (double)c); }
static inline float gcMsubS(float a, float b, float c) { return (float)((double)a * (double)b - (double)c); }
static inline float gcMsubRS(float a, float b, float c) { return -(float)((double)a * (double)b - (double)c); }
static inline double gcMaddD(double a, double b, double c) { return GC_FUSED_FMA(a, b, c); }
static inline double gcMsubD(double a, double b, double c) { return GC_FUSED_FMA(a, b, -c); }
static inline double gcMsubRD(double a, double b, double c) { return -GC_FUSED_FMA(a, b, -c); }

#ifdef __cplusplus
template <class T> struct GcFused {
    T a, b;
    operator T() const { return a * b; }
};

template <class A, class B> inline GcFused<decltype(A() * B())> gcFused(A a, B b) {
    typedef decltype(A() * B()) T;
    static_assert(sizeof(T) == sizeof(float) || sizeof(T) == sizeof(double), "GC_FUSED: float or double product");
    GcFused<T> p = {(T)a, (T)b};
    return p;
}
#define GC_FUSED(a, b) gcFused((a), (b))

inline float gcFusedAdd(const GcFused<float>& p, float c) { return gcMaddS(p.a, p.b, c); }
inline float gcFusedSub(const GcFused<float>& p, float c) { return gcMsubS(p.a, p.b, c); }
inline float gcFusedSubFrom(float c, const GcFused<float>& p) { return gcMsubRS(p.a, p.b, c); }
inline double gcFusedAdd(const GcFused<double>& p, double c) { return gcMaddD(p.a, p.b, c); }
inline double gcFusedSub(const GcFused<double>& p, double c) { return gcMsubD(p.a, p.b, c); }
inline double gcFusedSubFrom(double c, const GcFused<double>& p) { return gcMsubRD(p.a, p.b, c); }

template <class T, class C> struct GcFusedResult { typedef decltype(T() + C()) type; };
template <class T, class C> inline typename GcFusedResult<T, C>::type operator+(const GcFused<T>& p, C c) {
    typedef typename GcFusedResult<T, C>::type R;
    if (sizeof(R) > sizeof(T)) return (R)(T)p + (R)c;
    return (R)gcFusedAdd(p, (T)c);
}
template <class T, class C> inline typename GcFusedResult<T, C>::type operator+(C c, const GcFused<T>& p) {
    typedef typename GcFusedResult<T, C>::type R;
    if (sizeof(R) > sizeof(T)) return (R)c + (R)(T)p;
    return (R)gcFusedAdd(p, (T)c);
}
template <class T, class C> inline typename GcFusedResult<T, C>::type operator-(const GcFused<T>& p, C c) {
    typedef typename GcFusedResult<T, C>::type R;
    if (sizeof(R) > sizeof(T)) return (R)(T)p - (R)c;
    return (R)gcFusedSub(p, (T)c);
}
template <class T, class C> inline typename GcFusedResult<T, C>::type operator-(C c, const GcFused<T>& p) {
    typedef typename GcFusedResult<T, C>::type R;
    if (sizeof(R) > sizeof(T)) return (R)c - (R)(T)p;
    return (R)gcFusedSubFrom((T)c, p);
}
template <class T, class C> inline C& operator+=(C& x, const GcFused<T>& p) { x = (C)(x + p); return x; }
template <class T, class C> inline C& operator-=(C& x, const GcFused<T>& p) { x = (C)(x - p); return x; }
template <class T> inline T operator-(const GcFused<T>& p) { return -(T)p; }

#define GC_MADD(a, b, c) (GC_FUSED(a, b) + (c))
#define GC_MADDR(c, a, b) ((c) + GC_FUSED(a, b))
#define GC_MSUB(a, b, c) (GC_FUSED(a, b) - (c))
#define GC_MSUBR(c, a, b) ((c) - GC_FUSED(a, b))
#define GC_MADD_TO(x, a, b) ((x) += GC_FUSED(a, b))
#define GC_MSUB_FROM(x, a, b) ((x) -= GC_FUSED(a, b))

#else
static inline double gcMaddPlain(float a, float b, double c) { return (double)(a * b) + c; }
static inline double gcMsubPlain(float a, float b, double c) { return (double)(a * b) - c; }
static inline double gcMsubRPlain(float a, float b, double c) { return c - (double)(a * b); }
#define GC_FUSED_PICK(p, c, S, D, P) _Generic((p), float: _Generic((c), double: P, long double: P, default: S), default: D)
#define GC_FUSED(a, b) GC_FUSED_is_for_Cplusplus_use_GC_MADD_in_C_files
#define GC_MADD(a, b, c) GC_FUSED_PICK((a) * (b), (c), gcMaddS, gcMaddD, gcMaddPlain)((a), (b), (c))
#define GC_MADDR(c, a, b) GC_FUSED_PICK((a) * (b), (c), gcMaddS, gcMaddD, gcMaddPlain)((a), (b), (c))
#define GC_MSUB(a, b, c) GC_FUSED_PICK((a) * (b), (c), gcMsubS, gcMsubD, gcMsubPlain)((a), (b), (c))
#define GC_MSUBR(c, a, b) GC_FUSED_PICK((a) * (b), (c), gcMsubRS, gcMsubRD, gcMsubRPlain)((a), (b), (c))
#define GC_MADD_TO(x, a, b) ((x) = GC_MADDR((x), a, b))
#define GC_MSUB_FROM(x, a, b) ((x) = GC_MSUBR((x), a, b))
#endif
#endif
#endif
