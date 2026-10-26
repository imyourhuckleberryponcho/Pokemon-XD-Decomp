#include <dolphin/types.h>

struct GStexture;

enum GSgfxLayerPass {
    GS_GFX_LAYER_PASS_0
};

class GSgfxLayer {
public:
    void GetFifoSize(unsigned long* size, unsigned long* used);
    void textureCopy(GSgfxLayerPass pass, GStexture* texture, bool clear, u8* clearColor, bool, bool, bool);
};

extern "C" {
u32 GStextureGetFormat(GStexture* texture);
void GStextureSetWrap(GStexture* texture, s32 wrapS, s32 wrapT);
void GStextureSetFilter(GStexture* texture, s32 minFilter, s32 magFilter, s32);
void* GStextureLockImage(GStexture* texture, s32 level);
void GStextureUnlockImage(GStexture* texture);
}

typedef bool (*GSgfxBackFBCallback)(GStexture* texture, u32 frame, void* user);

struct GSgfxBackFB {
    u8 active;
    GStexture* texture;
    GSgfxBackFBCallback callback;
    void* user;
    u32 frame;
};

#define BACK_FB_MAX 4

static GSgfxBackFB gfxBackFBList[BACK_FB_MAX];
static bool _backFBIsCapturing;

static inline GSgfxBackFB* _backFBFind(GStexture* texture) {
    GSgfxBackFB* fb = gfxBackFBList;
    int i;
    for (i = 0; i < BACK_FB_MAX; i++, fb++) {
        if (fb->active == 1 && fb->texture == texture) {
            return fb;
        }
    }
    return NULL;
}

static inline GSgfxBackFB* _backFBFindFree() {
    GSgfxBackFB* fb = gfxBackFBList;
    int i;
    for (i = 0; i < BACK_FB_MAX; i++, fb++) {
        if (fb->active == 0) {
            return fb;
        }
    }
    return NULL;
}

extern "C" {

bool GSgfxEndBackFBCapture(GStexture* texture) {
    GSgfxBackFB* fb = _backFBFind(texture);
    int i;
    if (fb == NULL) {
        return false;
    }
    GStextureUnlockImage(fb->texture);
    fb->active = 0;
    _backFBIsCapturing = false;
    for (i = 0; i < BACK_FB_MAX; i++) {
        if (gfxBackFBList[i].active == 1) {
            _backFBIsCapturing = true;
            break;
        }
    }
    return true;
}

bool GSgfxBeginBackFBCapture(GStexture* texture, GSgfxBackFBCallback callback, void* user) {
    GSgfxBackFB* fb;

    switch (GStextureGetFormat(texture)) {
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x90:
        break;
    default:
        return false;
    }
    if (_backFBFind(texture) != NULL) {
        return false;
    }
    fb = _backFBFindFree();
    if (fb == NULL) {
        return false;
    }
    fb->active = 1;
    fb->texture = texture;
    fb->callback = callback;
    fb->user = user;
    fb->frame = 0;
    GStextureSetWrap(fb->texture, 0, 0);
    GStextureSetFilter(fb->texture, 2, 2, 0);
    GStextureLockImage(fb->texture, 0);
    _backFBIsCapturing = true;
    return true;
}

}

void GSgfxBackFBDoFrame(GSgfxLayer* layer) {
    GSgfxBackFB* fb;
    unsigned long size;
    unsigned long used;
    u32 i;
    GSgfxLayerPass pass;
    GSgfxLayerPass selectedPass;

    if (!_backFBIsCapturing) {
        return;
    }
    layer->GetFifoSize(&size, &used);
    selectedPass = used != 0 ? (GSgfxLayerPass)1 : GS_GFX_LAYER_PASS_0;
    pass = selectedPass;
    for (i = 0, fb = gfxBackFBList; i < BACK_FB_MAX; i++, fb++) {
        if (fb->active == 1) {
            layer->textureCopy(pass, fb->texture, true, NULL, false, false, false);
            if (fb->callback != NULL && !fb->callback(fb->texture, fb->frame, fb->user)) {
                GSgfxEndBackFBCapture(fb->texture);
            }
            fb->frame++;
        }
    }
}

void GSgfxBackFBInit() {
    int i;
    for (i = 0; i < BACK_FB_MAX; i++) {
        gfxBackFBList[i].active = 0;
    }
    _backFBIsCapturing = false;
}
