#include <dolphin/types.h>

#pragma peephole off

// One offscreen render target: a movie or an animated model drawn into a texture that
// replaces a texture of a floor model.
struct OffscreenData {
    u8 isMovie;
    u8 anim;
    u16 index;
    u16 width;
    u16 height;
    u32 targetResID;
    u32 sourceID;
    u32 cameraResID;
};

struct OffscreenHeader {
    u32* count;
    OffscreenData* data;
};

struct FloorData {
    u8 unk0[0x28];
    OffscreenHeader** offscreen;
};

struct GStexture;
struct GSmodel;

extern "C" {
void* memset(void* dst, int val, unsigned long n);
GStexture* GStextureCreate(u16 width, u16 height, s32 format, s32, s32);
void GStextureFree(GStexture* tex);
void GSmoviePlay(u32 movie, s32, int loop, GStexture* tex);
void GSmoviePlayWait(u32 movie);
void GSmovieStop(u32 movie);
u32 floorGetCurrentGroupID(void);
void* GSresGetResource(u32 group, u32 id);
void GSmodelSetTextureChange(void* model, GStexture* tex);
void GSmodelResetTextureChange(void* model);
GSmodel* floorOpenModel(u32 group, u32 id);
void GSmodelSetVisibility(GSmodel* model, s32 visible);
void GSmodelLinkTexAnimToAnim(GSmodel* model, s32);
void GSmodelSetAnimIndex(GSmodel* model, u8 index);
void GSmodelStartAnimation(GSmodel* model);
void GSmodelForceAnimTransformUpdate(GSmodel* model);
void GSmodelFree(GSmodel* model);
}

static void _floorFreeOffscreenData();

static OffscreenData _userOffData;
static s32 _lastOffIdx = -1;
static OffscreenData* _offRootDataPtr;
static u32 _offRootDataCnt;
static OffscreenData* _offData;
static GStexture* _offTex;
static GSmodel* _offMdl;
static void* _offCam;

#define OFFSCREEN_TEX_FORMAT 0x44
#define USER_OFFSCREEN_INDEX 1000

extern "C" {

// Plays a movie into a texture of a floor model.
u8 floorMoviePlay(u32 movie, s32 arg1, int loop, u32 targetResID, u16 width, u16 height) {
    _floorFreeOffscreenData();
    _offData = &_userOffData;
    _offData->isMovie = true;
    _offData->index = USER_OFFSCREEN_INDEX;
    _offData->targetResID = targetResID;
    _offData->sourceID = movie;
    _offData->anim = loop;
    _offData->width = width;
    _offData->height = height;
    _offData->cameraResID = 0;
    _offTex = GStextureCreate(_offData->width, _offData->height, OFFSCREEN_TEX_FORMAT, 0, 0);
    if (_offTex == NULL) {
        _offData = NULL;
        return false;
    }
    GSmoviePlay(_offData->sourceID, arg1, loop, _offTex);
    GSmodelSetTextureChange(GSresGetResource(floorGetCurrentGroupID(), _offData->targetResID), _offTex);
    _lastOffIdx = USER_OFFSCREEN_INDEX;
    return true;
}

void floorOffscreenPlayWait(void) {
 // Only movies can be waited for.
    if (_offData == NULL || _offMdl != NULL) {
        return;
    }
    GSmoviePlayWait(_offData->sourceID);
}

GStexture* floorGetActiveOffscreenTexture(void) {
    return _offTex;
}

// Switches to the floor's offscreen entry with this index.
u8 floorSetOffscreenIndex(s32 index) {
    u32 i;
    u8 found;
    OffscreenData* data;

    if (_lastOffIdx == index) {
        return true;
    }
    _floorFreeOffscreenData();
    found = false;
    _offData = _offRootDataPtr;
    for (i = _offRootDataCnt; i != 0; i--) {
        if (_offData->index == index) {
            found = true;
            break;
        }
        _offData++;
    }
    if (!found) {
        _offData = NULL;
        return false;
    }
    _offTex = GStextureCreate(_offData->width, _offData->height, OFFSCREEN_TEX_FORMAT, 0, 0);
    if (_offTex == NULL) {
        _offData = NULL;
        return false;
    }
    data = _offData;
    if (!data->isMovie) {
        _offMdl = floorOpenModel(floorGetCurrentGroupID(), data->sourceID);
        GSmodelSetVisibility(_offMdl, false);
        GSmodelLinkTexAnimToAnim(_offMdl, true);
        GSmodelSetAnimIndex(_offMdl, _offData->anim);
        GSmodelStartAnimation(_offMdl);
    } else {
        GSmoviePlay(data->sourceID, 0, data->anim != 0, _offTex);
    }
    _offCam = GSresGetResource(floorGetCurrentGroupID(), _offData->cameraResID);
    GSmodelSetTextureChange(GSresGetResource(floorGetCurrentGroupID(), _offData->targetResID), _offTex);
    _lastOffIdx = index;
    return true;
}

void floorReleaseOffscreen(void) {
    _floorFreeOffscreenData();
    _offRootDataPtr = NULL;
    _offRootDataCnt = 0;
}

void floorUpdateOffscreen(void) {
 // Movies update themselves; models need their animation pushed.
    if (_offData == NULL || _offMdl == NULL) {
        return;
    }
    GSmodelForceAnimTransformUpdate(_offMdl);
}

void floorInitOffscreen(FloorData* floor) {
    if (floor->offscreen != NULL) {
        _offRootDataPtr = (*floor->offscreen)->data;
        if (_offRootDataPtr != NULL) {
            _offRootDataCnt = *(*floor->offscreen)->count;
            if (_offRootDataCnt != 0) {
                memset(&_userOffData, 0, sizeof(OffscreenData));
            }
        }
    }
}

}

static void _floorFreeOffscreenData() {
    if (_offData == NULL) {
        return;
    }
    if (_offData->isMovie == true) {
        GSmovieStop(_offData->sourceID);
    }
    GSmodelResetTextureChange(GSresGetResource(floorGetCurrentGroupID(), _offData->targetResID));
    if (_offTex != NULL) {
        GStextureFree(_offTex);
        _offTex = NULL;
    }
    if (_offMdl != NULL) {
        GSmodelFree(_offMdl);
        _offMdl = NULL;
    }
    _offCam = NULL;
    _offData = NULL;
    _lastOffIdx = -1;
}

extern "C" {

void floorOffscreenMainInit(void) {}

}
