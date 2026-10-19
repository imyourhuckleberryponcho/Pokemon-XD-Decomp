#include <dolphin/types.h>

#pragma peephole off

extern "C" {
s32 floorGetCurrentGroupID(void);
u32 HSD_Rand(void);
void cameraPlayAnime(s32 groupID, u32 anime, s32, f32 frame);
void GSthreadSwitch(void);
void GSfloorPop(void);
}

class WorldMapModel {
public:
    WorldMapModel() : mOffscreenData(0) {}
    ~WorldMapModel() {
        if (mOffscreenData != 0) {
            releaseOffscreenData();
        }
    }
    void releaseOffscreenData();
    void SetModel(u32 groupID, u32 modelID, bool);
    void SetMotion(u32 modelID, s16 motion, f32 frame, bool);
    f32 GetAnimeFrameCount(u32 modelID, u32 motion);
    f32 GetAnimeFrame(u32 modelID);

    void* mOffscreenData;
};

class WorldMapMoveDemo : public WorldMapModel {
public:
    ~WorldMapMoveDemo() {}
    void Main();
};

struct MoveDemoAnime {
    s16 motion;
    u32 cameraAnime;
};

static MoveDemoAnime _animeTable[15] = {
    { 0, 0x1B491800 }, { 1, 0x1B781800 }, { 2, 0x1B791800 }, { 3, 0x1B7A1800 }, { 4, 0x1B7B1800 },
    { 5, 0x1B7C1800 }, { 6, 0x1B7D1800 }, { 7, 0x1B7E1800 }, { 8, 0x1B7F1800 }, { 9, 0x1B801800 },
    { 10, 0x1B811800 }, { 11, 0x1B821800 }, { 12, 0x1B831800 }, { 13, 0x1B841800 }, { 14, 0x1B851800 },
};

static WorldMapMoveDemo* pMoveDemo;

extern "C" {

// Kept via FORCEACTIVE in config/GXXE01/module/ldscript.lcf (used from REL modules).
void menuWorldMapMoveDemoExit(void) {
    if (pMoveDemo != NULL) {
        delete pMoveDemo;
        pMoveDemo = NULL;
    }
}

void menuWorldMapMoveDemoMain(void) {
    if (pMoveDemo != NULL) {
        pMoveDemo->Main();
    }
}

void menuWorldMapMoveDemoInit(void) { pMoveDemo = new WorldMapMoveDemo; }

}

void WorldMapMoveDemo::Main() {
    s32 groupID = floorGetCurrentGroupID();
    MoveDemoAnime* anime;
    f32 frameCount;
    SetModel(groupID, 0x1B4A0400, false);
    anime = &_animeTable[(u16)((u16)HSD_Rand() % 15)];
    cameraPlayAnime(groupID, anime->cameraAnime, 0, 0.0f);
    SetMotion(0x1B4A1000, anime->motion, 0.0f, false);
    frameCount = GetAnimeFrameCount(0x1B4A1000, anime->motion);
    for (;;) {
        if (frameCount - 30.0f < GetAnimeFrame(0x1B4A1000)) {
            break;
        }
        GSthreadSwitch();
    }
    GSfloorPop();
}
