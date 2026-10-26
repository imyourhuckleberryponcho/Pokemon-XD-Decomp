#pragma cplusplus on

extern inline float sqrtf(float x) {
    static const double _half=.5;
    static const double _three=3.0;
    volatile float y;
    if(x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = _half*guess*(_three - guess*guess*x);
        guess = _half*guess*(_three - guess*guess*x);
        guess = _half*guess*(_three - guess*guess*x);
        y=(float)(x*guess);
        return y ;
    }
    return x ;
}   

extern inline float sqrt(float x) {
    static const double _half=.5;
    static const double _three=3.0;
    volatile float y;
    if(x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = _half*guess*(_three - guess*guess*x);
        guess = _half*guess*(_three - guess*guess*x);
        guess = _half*guess*(_three - guess*guess*x);
        guess = _half*guess*(_three - guess*guess*x);

        y=(float)(x*guess);
        return y ;
    }
    return x ;
}

extern inline float fabs(float x) {
#if __MIPS__
    return fabsf(x);
#else
    (*(int*)&x)&=0x7fffffff;
    return  x;
#endif
}

extern inline float fabsf(float x) {
    return __fabsf(x);
}

extern float cosf(float);
extern inline float cos(float x) {
    return cosf(x);
}

inline float floor(float x) {
    int i=(int)x;   
    float y=x-(float)i; 

    if(!y || x > 8388608.0f)
    return x ;

    if(x < 0) 
    return (float)--i;  
    return (float)i;
}

#pragma cplusplus reset
