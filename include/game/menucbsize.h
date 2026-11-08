#ifndef GAME_MENUCBSIZE_H
#define GAME_MENUCBSIZE_H
#ifdef __MWERKS__
#define MENUCB_SIZE 0xB5F4
#else
#define MENUCB_SIZE (0xB5F4 + (sizeof(void*) - 4) * 37)
#endif
#endif
