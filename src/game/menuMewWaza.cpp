#include <dolphin/types.h>
#include <game/gcptr.h>

#pragma peephole off

struct MewWazaWindow {
    s8 flags;
    s8 state;
    u8 unk2[2];
    s32 unk4;
    u8 unk8[0x4];
    void* slotC;
    void* slot10;
    void* slot14;
    u8 pad18[0xC];
    void* slot24;
    void* slot28;
    void* slot2C;
    u8 pad30[0x38];
    void* slot68;
    void* slot6C;
    void* slot70;
    void* slot74;
    void* slot78;
    void* slot7C;
    void* slot80;
    void* slot84;
    u8 pad88[0x4];
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

static char* _GetMewWazaName(s32 index);

extern "C" {

WindowFreeWork* windowGetFreeWork(MewWazaWindow* window);
s32 winSpriteGetLayerID(MewWazaWindow* window, MewWazaItem* item);
void* GSgfxLayerFindByID(GCsptr layer);
void spriteSetOffset(s32 layer, s16 x, s16 y);
void spriteSetEnv(s32 layer);
void* GSmsgGetGSchar(char* str);
void msgctrlSetValue(s32 id, void* value);
void GSmsgPrint2(s32 layer, s32, s32, u32 color, u32 msgID);
void menuSubDrawMsgWindow2(s32 layer, s32, s32, s32 width, s32 height, u8 alpha, s32);
void GSmsgMain(s32 layer, s32, s32, bool);
u16 mewWazaGet(s32 index);
void* wazaDataBiosGetPtr(u16 id);
char* wazaDataBiosGetName(void* data);

s32 menuMewWazaGetMenuDataID(void) {
    return 0x10C;
}

s32 menuMewWazaDraw(MewWazaWindow* window, MewWazaItem* item) {
    WindowFreeWork* work = windowGetFreeWork(window);
    s32 layer = winSpriteGetLayerID(window, item);
    s32 width;
    s16 height;

    GSgfxLayerFindByID(layer);
    width = item->width;
    height = item->height;
    s16 d = item->height - 4 - height;
    spriteSetOffset(layer, window->x + item->x, window->y + item->y + d);
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

static char* _GetMewWazaName(s32 index) {
    return wazaDataBiosGetName(wazaDataBiosGetPtr(mewWazaGet(index)));
}
