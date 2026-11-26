#ifndef GAME_PCBOXES_H
#define GAME_PCBOXES_H
#include <dolphin/types.h>

#define PC_PCBOX_GC 8
#define PC_PCBOX_MAX 32

#ifdef __MWERKS__
#define PC_PCBOX_COUNT() 8
#define PC_PCBOX_PREV(x) (((x) + 7) % 8)
#define PC_PCBOX_NEXT(x) (((x) + 1) % 8)
#define PC_PCBOX_BG(x) (x)
#else
#ifdef __cplusplus
extern "C" {
#endif
extern s32 (*PortXD_PcBoxCount)(void);
extern void* (*PortXD_PcBoxExtraBox)(s32 box);
extern s32 (*PortXD_PcBoxGetLastView)(void);
extern void (*PortXD_PcBoxSetLastView)(s32 box);
s32 pcboxCount(void);
void pcboxMakeDefaultName(u16* dst, s32 boxNumber1Based);
#ifdef __cplusplus
}
#endif
#define PC_PCBOX_COUNT() pcboxCount()
#define PC_PCBOX_PREV(x) (((x) + pcboxCount() - 1) % pcboxCount())
#define PC_PCBOX_NEXT(x) (((x) + 1) % pcboxCount())
#define PC_PCBOX_BG(x) ((x) % 8)
#endif

#endif
