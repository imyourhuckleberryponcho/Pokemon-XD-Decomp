#include <dolphin/types.h>

typedef void (*MenuItemHook)();

// One selectable item / sprite slot of a menu (28 bytes). The tables are indexed by
// MenuDataEntry.itemIndex; `next` links the entries of a menu in order (-1 ends the list).
typedef struct MenuItemEntry {
    u8 flags;            // 0x00 (0x80 = selected, 0x40, 0x01)
    u8 flags2;           // 0x01
    u8 unk2;             // 0x02 (0xFF for most entries)
    u8 unk3;             // 0x03
    u16 imageId;         // 0x04 background/image resource id (0 for sprite items)
    s16 x;               // 0x06
    s16 y;               // 0x08
    s16 w;               // 0x0A
    s16 h;               // 0x0C
    s16 spriteId;        // 0x0E index into _menu_sprite
    u32 msgId;           // 0x10 message id (0 = none)
    MenuItemHook hook;   // 0x14 per-item draw/update callback
    s16 next;            // 0x18 index of the next item (-1 = last)
    s16 unk1A;           // 0x1A
} MenuItemEntry;

MenuItemEntry _menu_item[] = {
    /* 0 */ { 0xC0, 0x00, 0xFF, 0x00, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    /* 1 */ { 0x00, 0x00, 0xFF, 0x00, 0x0060, 0, 0, 0, 0, 0, 0, 0, 2, 0 },
    /* 2 */ { 0x80, 0x00, 0xFF, 0x00, 0, 0, 0, 0, 0, 0x00BE, 0xEB94, 0, 3, 0 },
    /* 3 */ { 0x80, 0x00, 0xFF, 0x00, 0, 0, 20, 0, 0, 0x00BE, 0xEB95, 0, 4, 0 },
    /* 4 */ { 0xC0, 0x00, 0xFF, 0x00, 0, 0, 40, 0, 0, 0x00BE, 0xEB96, 0, 5, 0 },
    /* 5 */ { 0xC0, 0x00, 0xFF, 0x00, 0x0039, 0, 0, 640, 480, 0, 0, 0, 6, 0 },
    /* 6 */ { 0xC0, 0x00, 0xFF, 0x00, 0x003A, 0, 0, 640, 480, 0, 0, 0, 7, 0 },
    /* 7 */ { 0x40, 0x00, 0xFF, 0x00, 0x0342, 0, 0, 640, 480, 0, 0, 0, -1, 0 },
};

