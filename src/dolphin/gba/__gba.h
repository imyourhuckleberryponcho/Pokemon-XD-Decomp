#ifndef _GBA_GBAPRIV_H_
#define _GBA_GBAPRIV_H_

#include <dolphin/os.h>
#include <dolphin/si.h>
#include <dolphin/dsp.h>
#include <string.h>

#define GBA_READY 0
#define GBA_NOT_READY 1
#define GBA_BUSY 2

#define GBA_JSTAT_MASK 0x3A

typedef void (*GBACallback)(s32 chan, s32 ret);
typedef void (*GBATransferCallback)(s32 chan);

typedef struct GBASecParams {
    u8 data[0x40];
} GBASecParams;

typedef struct GBAControl {
 u8 output[5];
 u8 input[5];
 s32 outputBytes;
 s32 inputBytes;
 u8* status;
 u8* ptr;
 GBACallback callback;
 s32 ret;
 OSThreadQueue threadQueue;
 OSTime delay;
 GBATransferCallback proc;
 u8 bootInfo[0xBC];
 GBASecParams* param;
 u8 padFC[4];
} GBAControl;

extern GBAControl __GBA[4];
extern BOOL __GBAReset;

void __GBASyncCallback(s32 chan, s32 ret);
s32 __GBASync(s32 chan);
s32 __GBATransfer(s32 chan, s32 w1, s32 w2, GBATransferCallback callback);

void GBAInit(void);
s32 GBAGetStatusAsync(s32 chan, u8* status, GBACallback callback);
s32 GBAGetStatus(s32 chan, u8* status);
s32 GBAResetAsync(s32 chan, u8* status, GBACallback callback);
s32 GBAReset(s32 chan, u8* status);
s32 GBAReadAsync(s32 chan, u8* dst, u8* status, GBACallback callback);
s32 GBARead(s32 chan, u8* dst, u8* status);
s32 GBAWriteAsync(s32 chan, u8* src, u8* status, GBACallback callback);
s32 GBAWrite(s32 chan, u8* src, u8* status);

#endif
