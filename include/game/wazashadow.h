#ifndef GAME_WAZASHADOW_H
#define GAME_WAZASHADOW_H
#ifdef __MWERKS__
typedef u32 WazaShadowAddr;
typedef s32 WazaShadowListAddr;
#else
#include <stdint.h>
typedef uintptr_t WazaShadowAddr;
typedef intptr_t WazaShadowListAddr;
#endif
#endif
