#ifndef GAME_PCALLOC_H
#define GAME_PCALLOC_H
#ifndef __MWERKS__
#ifndef PORT_ALLOC_HOOK
#include <stdlib.h>
#define PC_ALLOC(n) malloc(n)
#define PC_CALLOC(n, size) calloc((n), (size))
#define PC_REALLOC(p, n) realloc((p), (n))
#define PC_FREE(p) free(p)
#endif
#endif
#endif
