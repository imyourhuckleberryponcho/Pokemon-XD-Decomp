// WIP (NonMatching): only the load order of the spriteSetOffset y math differs now.
#include <dolphin/types.h>

// Menu files were built without the peephole optimizer.
#pragma peephole off

struct MewWazaWindow {
    s8 flags;
    s8 state;
    u8 unk2[2];
    s32 unk4;
    u8 unk8[0x84];
    s16 x;
    s16 y;
    u8 unk90[3];
    u8 alpha;
};

struct MewWazaItem {
    u8 unk0[6];
    s16 id;
    u8 unk8[0x48];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

struct WindowFreeWork {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

static char* _GetMewWazaName(long index);

extern "C" {

WindowFreeWork* windowGetFreeWork(MewWazaWindow* window);
s32 winSpriteGetLayerID(MewWazaWindow* window, MewWazaItem* item);
void* GSgfxLayerFindByID(s32 layer);
void spriteSetOffset(s32 layer, s16 x, s16 y);
void spriteSetEnv(s32 layer);
void* GSmsgGetGSchar(char* str);
void msgctrlSetValue(s32 id, void* value);
void GSmsgPrint2(s32 layer, s32, s32, u32 color, u32 msgID);
void menuSubDrawMsgWindow2(s32 layer, s32, s32, s16 width, s16 height, u8 alpha, s32);
void GSmsgMain(s32 layer, s32, s32, bool);
u16 mewWazaGet(long index);
void* wazaDataBiosGetPtr(u16 id);
char* wazaDataBiosGetName(void* data);

s32 menuMewWazaGetMenuDataID(void) {
    return 0x10C;
}

s32 menuMewWazaDraw(MewWazaWindow* window, MewWazaItem* item) {
    WindowFreeWork* work = windowGetFreeWork(window);
    s32 layer = winSpriteGetLayerID(window, item);
    s16 height;
    s16 width;
    s32 top;

    GSgfxLayerFindByID(layer);
    height = item->height;
    top = height - 4;
    spriteSetOffset(layer, window->x + item->x, window->y + (item->y + (s16)(top - height)));
    width = item->width;
    spriteSetEnv(layer);

    switch (item->id) {
    case 0x2C:
        {
            void* name = GSmsgGetGSchar(_GetMewWazaName(0));
            msgctrlSetValue(0x4D, name);
        }
        GSmsgPrint2(layer, 0, 0, window->alpha | 0xFFFFFF00, 0xC72D);
        break;
    case 0x2D:
        msgctrlSetValue(0x4D, GSmsgGetGSchar(_GetMewWazaName(1)));
        GSmsgPrint2(layer, 0, 0, window->alpha | 0xFFFFFF00, 0xC72E);
        break;
    case 0x2E:
        msgctrlSetValue(0x4D, GSmsgGetGSchar(_GetMewWazaName(2)));
        GSmsgPrint2(layer, 0, 0, window->alpha | 0xFFFFFF00, 0xC72F);
        break;
    case 0x2F:
        msgctrlSetValue(0x4D, GSmsgGetGSchar(_GetMewWazaName(3)));
        GSmsgPrint2(layer, 0, 0, window->alpha | 0xFFFFFF00, 0xC730);
        break;
    case 0x2B:
        menuSubDrawMsgWindow2(layer, 0, -2, width, height, window->alpha, 1);
        GSmsgPrint2(layer, 0, 0, window->alpha | 0xFFFFFF00, 0xC722);
        switch (window->state) {
        case 0:
        case 1:
            break;
        case 2:
            if (window->unk4 != 20) {
                GSmsgMain(layer, work->unk0, work->unk8, !(window->flags & 4));
                work->unk8 = 0;
            }
            break;
        case 3:
        case 5:
            break;
        }
        break;
    }
    return 0;
}

}

static char* _GetMewWazaName(long index) {
    return wazaDataBiosGetName(wazaDataBiosGetPtr(mewWazaGet(index)));
}
