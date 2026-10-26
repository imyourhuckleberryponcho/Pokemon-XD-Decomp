#ifndef _DOLPHIN_RUNTIME_H
#define _DOLPHIN_RUNTIME_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

u32 __cvt_fp2unsigned(f64);

void* __copy(char*, char*, size_t);

#ifdef __cplusplus
};
#endif

#endif
