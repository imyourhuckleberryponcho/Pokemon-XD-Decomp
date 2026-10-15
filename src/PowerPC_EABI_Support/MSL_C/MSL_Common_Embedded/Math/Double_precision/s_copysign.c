#define __HI(x) *(int*)&x

double copysign(double x, double y) {
    __HI(x) = (__HI(x) & 0x7FFFFFFF) | (__HI(y) & 0x80000000);
    return x;
}
