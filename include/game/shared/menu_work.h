#ifndef GAME_SHARED_MENU_WORK_H
#define GAME_SHARED_MENU_WORK_H
// Shared layouts of the menu window/sprite work records .
// Offsets verified by compiling the definitions of 25 (window) / 22 (sprite) matched or WIP menu
// sources (tools/structoffsets.py). Field TYPES matter for matching (u8 vs s8 -> lbz vs lbz+extsb):
// the type used here is the majority type; known alternatives are noted. If your target asm
// disagrees, declare your own copy in the .cpp (existing matched files keep theirs on purpose).
// Unknown areas are padding. Owner module: game/pxdvs/app/menu/window.cpp (full size 0xBC).
#include <dolphin/types.h>

struct tagSPRITE_WORK;
struct tagSEQ_WORK;

struct tagWINDOW_WORK {
    u8 used;                       // 0x00 (s8 in winSprite.cpp)
    s8 state;                      // 0x01 (16 files s8, 2 u8)
    s8 seqSet;                     // 0x02
    u8 pad3;                       // 0x03
    s32 menuID;                    // 0x04 (window.cpp; several menu files call it `void* seq`)
    u8 pad8;                       // 0x08
    s8 priority;                   // 0x09
    u8 closeFlag;                  // 0x0A
    u8 enablePort;                 // 0x0B
    tagWINDOW_WORK* parent;        // 0x0C
    tagWINDOW_WORK* next;          // 0x10
    tagWINDOW_WORK* prev;          // 0x14
    u8 flag18;                     // 0x18
    u8 itemNum;                    // 0x19
    u8 flags1a;                    // 0x1A
    u8 closeFlags;                 // 0x1B
    s32 layer;                     // 0x1C layer ID (12 files `layer`, 2 `layerID`)
    u8 flags20;                    // 0x20
    u8 pad21[3];                   // 0x21
    tagSPRITE_WORK* itemSprites;   // 0x24
    tagSPRITE_WORK* cursorSprites; // 0x28
    u8 seq[0x3C];                  // 0x2C tagSEQ_WORK (see winSprite.cpp)
    u32 params[8];                 // 0x68 per-menu parameter/content pointer (contents/param/source)
    s32 cursor88;                  // 0x88 (3 files `cursor`, 1 `result`)
    s16 x;                         // 0x8C offX
    s16 y;                         // 0x8E offY
    u8 color[3];                   // 0x90
    u8 alpha;                      // 0x93 (11 files)
    f32 f94;                       // 0x94
    f32 f98;                       // 0x98
    s16 top;                       // 0x9C list top / cursorX
    s16 cursor;                    // 0x9E current cursor/pos
    s16 unkA0;                     // 0xA0
    s16 prevCursor;                // 0xA2
    u8 done;                       // 0xA4 (button done)
    u8 cancel;                     // 0xA5 (button cancel)
    u8 padA6[2];                   // 0xA6
    u8 freeWork[0x10];             // 0xA8
    void* alloc;                   // 0xB8
};

struct tagSPRITE_WORK {
    tagSPRITE_WORK* next;          // 0x00
    s8 kind;                       // 0x04 (u8/flags in some files)
    u8 flags;                      // 0x05 (bit 0x08 = offset mode, see winSpriteDraw)
    s16 id;                        // 0x06 sprite/item ID
    u8 pad8[0x14];                 // 0x08
    s32 layer;                     // 0x1C
    u8 pad20[0x28];                // 0x20
    void* hook;                    // 0x48 callback
    s32 msgID;                     // 0x4C
    s16 x;                         // 0x50
    s16 y;                         // 0x52
    s16 w;                         // 0x54
    s16 h;                         // 0x56
    s32 unk58;                     // 0x58 texture
    s16 sx;                        // 0x5C
    s16 sy;                        // 0x5E
    s16 sw;                        // 0x60
    s16 sh;                        // 0x62
    u8 r;                          // 0x64 color (some files: u32 color)
    u8 g;                          // 0x65
    u8 b;                          // 0x66
    u8 alpha;                      // 0x67
};

#endif
