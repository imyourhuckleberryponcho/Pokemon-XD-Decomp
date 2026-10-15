#ifndef _MSL_TYPES_H
#define _MSL_TYPES_H

// Basic types for the MetroWerks runtime/MSL sources (ported from the Pikmin 2 decomp).
typedef int BOOL;
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef unsigned long size_t;

#ifndef __cplusplus
typedef u16 wchar_t;
#endif

#define TRUE 1
#define FALSE 0
#define NULL 0

#endif
