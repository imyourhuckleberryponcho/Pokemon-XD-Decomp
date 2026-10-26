#ifndef _FDLIBM_H
#define _FDLIBM_H

#define __HI(x) *(int*)&x
#define __LO(x) *(1 + (int*)&x)

double __kernel_sin(double x, double y, int iy);
double __kernel_cos(double x, double y);
double __kernel_tan(double x, double y, int k);
int __ieee754_rem_pio2(double x, double* y);
int __kernel_rem_pio2(double* x, double* y, int e0, int nx, int prec, const int* ipio2);

double scalbn(double x, int n);
double copysign(double x, double y);
double floor(double x);
double sqrt(double x);
double atan(double x);

inline double fabs(double x) {
    return __fabs(x);
}

extern int errno;
#define EDOM 33

extern int __float_nan[];
#define NAN (*(float*)__float_nan)

#endif
