#include <dolphin/types.h>

typedef void (*MenuItemHook)();

typedef struct MenuItemEntry {
    u8 flags;
    u8 flags2;
    u8 unk2;
    u8 unk3;
    u16 imageId;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 spriteId;
    u32 msgId;
    MenuItemHook hook;
    s16 next;
    s16 unk1A;
} MenuItemEntry;

MenuItemEntry _menu_item[] = {
 { 0xC0, 0x00, 0xFF, 0x00, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
 { 0x00, 0x00, 0xFF, 0x00, 0x0060, 0, 0, 0, 0, 0, 0, 0, 2, 0 },
 { 0x80, 0x00, 0xFF, 0x00, 0, 0, 0, 0, 0, 0x00BE, 0xEB94, 0, 3, 0 },
 { 0x80, 0x00, 0xFF, 0x00, 0, 0, 20, 0, 0, 0x00BE, 0xEB95, 0, 4, 0 },
 { 0xC0, 0x00, 0xFF, 0x00, 0, 0, 40, 0, 0, 0x00BE, 0xEB96, 0, 5, 0 },
 { 0xC0, 0x00, 0xFF, 0x00, 0x0039, 0, 0, 640, 480, 0, 0, 0, 6, 0 },
 { 0xC0, 0x00, 0xFF, 0x00, 0x003A, 0, 0, 640, 480, 0, 0, 0, 7, 0 },
 { 0x40, 0x00, 0xFF, 0x00, 0x0342, 0, 0, 640, 480, 0, 0, 0, -1, 0 },
};

