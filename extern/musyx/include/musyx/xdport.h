#ifndef _MUSYX_XDPORT
#define _MUSYX_XDPORT
#include <stdint.h>
#ifndef MUSY_PC_PTR
#define MUSY_PC_PTR(v) ((void*)(uintptr_t)(u32)(v))
#endif
#ifndef MUSY_ADDR32
#define MUSY_ADDR32(p) ((u32)(uintptr_t)(p))
#endif
#ifndef MUSY_MALLOC
#define MUSY_MALLOC(n) malloc(n)
#endif
#ifndef MUSY_FREE
#define MUSY_FREE(p) free(p)
#endif
#endif
