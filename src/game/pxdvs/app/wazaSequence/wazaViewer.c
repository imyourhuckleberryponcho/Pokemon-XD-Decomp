#include <dolphin/types.h>

typedef struct WazaViewerData {
    u8 unk0[0x16];
    u8 unk16;
    u8 unk17;
    u8 unk18[0x30 - 0x18];
    s32 unk30;
    u8 unk34[4];
} WazaViewerData;

WazaViewerData wazaViewerData;
