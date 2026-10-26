#include <dolphin/types.h>

#pragma peephole off

struct FlashTestItem {
    u8 unk0[6];
    s16 id;
};

extern "C" {

s32 winSpriteGetLayerID(void* window, FlashTestItem* item);
void winSpriteSetDisp(FlashTestItem* item, u8 disp);
void windowDrawSprite(s32 x, s32 y, void* window, u16 spriteID, s32, s32 layer);
void menuClose(s32 menuID);
s32 menuOpen(s32 menuID, s32);
void FlashSystemSetLoopFlag(u32 id, s32 loop);

static f32 spritePos[2] = { 0.0f, 0.0f };
static u16 spriteIDs[4] = { 0x2E1, 0x2E2, 0x2E3, 0x2E4 };
static u8 partDisp[4] = { 1, 1, 1, 1 };
static u8 baseDisp = 1;
static u8 drawSprites[8];

s32 fn_8000FDA8(void* window, FlashTestItem* item) {
    s32 layer = winSpriteGetLayerID(window, item);
    switch (item->id) {
    case 0x155:
        winSpriteSetDisp(item, baseDisp);
        break;
    case 0x68F:
        winSpriteSetDisp(item, partDisp[0]);
        break;
    case 0x690:
        winSpriteSetDisp(item, partDisp[1]);
        break;
    case 0x691:
        winSpriteSetDisp(item, partDisp[2]);
        break;
    case 0x692:
        winSpriteSetDisp(item, partDisp[3]);
        break;
    case 0x698:
        if (drawSprites[0]) {
            windowDrawSprite(spritePos[0], spritePos[1], window, spriteIDs[0], 0, layer);
            windowDrawSprite(spritePos[0], spritePos[1], window, spriteIDs[1], 0, layer);
            windowDrawSprite(spritePos[0], spritePos[1], window, spriteIDs[2], 0, layer);
            windowDrawSprite(spritePos[0], spritePos[1], window, spriteIDs[3], 0, layer);
        }
        break;
    }
    return 0;
}

#pragma force_active on

void fn_8000FF78(void) {
    menuClose(0x4E);
}

void fn_8000FF9C(void) {
    menuOpen(0x4E, 1);
}

void menuFlashTestInit(void) {
    FlashSystemSetLoopFlag(0x17883000, 1);
}

#pragma force_active reset

}
