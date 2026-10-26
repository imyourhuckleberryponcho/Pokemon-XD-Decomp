

#include <dolphin/types.h>
#include <dolphin/gx/GXStruct.h>

#pragma pool_strings off

struct Vec;
struct HSD_CObj;
typedef struct _HSD_AObj {
    u32 flags;
    f32 curr_frame;
    f32 rewind_frame;
    f32 end_frame;
} HSD_AObj;
struct HSD_ClassInfo;
struct HSD_LObj;

struct GSgfxLayer;
enum GSgfxLayerPass { GS_GFX_LAYER_PASS_0 };
struct GSgfxRenderModule {
    void (*init)(void* user);
    void (*preUpdate)(f32 dt);
    void (*render)(GSgfxLayer* layer, GSgfxLayerPass pass);
    void (*renderFast)(void);
    void (*postUpdate)(f32 dt);
    void (*frameUpdate)(void);
    u32 id;
};
void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* user);

struct GSlightWObjDesc {
    char* class_name;
    f32 x, y, z;
    void* robjdesc;
};

struct GSlightLightDesc {
    char* class_name;
    GSlightLightDesc* next;
    u16 flags;
    u16 attnflags;
    GXColor color;
    GSlightWObjDesc* position;
    GSlightWObjDesc* interest;
    void* u;
};

struct GSlightDesc {
    GSlightLightDesc* lightDesc;
    void** anims;
};

struct GSlight {
    u8 used;
    u8 active;
    u8 canAnimate;
    u8 animating;
    s32 type;
    GSlightDesc* desc;
    HSD_LObj* lobj;
    GSlightWObjDesc positionDesc;
    GSlightWObjDesc interestDesc;
    GSlightLightDesc lightDesc;
    f32 cutoff;
    u32 animCount;
    s32 animType;
    u32 animIndex;
    f32 rate;
    f32 frame;
    f32 frameCount;
    u8 ended;
    s8 direction;
};

struct GSlightState {
    u8 active;
    u8 animating;
    u8 ended;
    s8 direction;
    f32 position[3];
    f32 interest[3];
    u32 animIndex;
    f32 frame;
    f32 rate;
    s32 animType;
};

struct HSD_ObjHeader {
    void** class_info;
    u16 ref_count;
};

extern "C" {
void* memset(void*, int, u32);
void __assert(const char*, int, const char*);
void* GSmemAlloc(u32 size);
u8 GSgfxVideoGetVsyncRate(void);
void HSD_ForeachAnim(void* object, u32 type, u32 mask, void* func, u32 callback_type, ...);
void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate);
void HSD_LObjDeleteCurrentAll(HSD_LObj*);
void HSD_LObjAddCurrentAll(HSD_LObj*);
void HSD_LObjSetupInit(HSD_CObj*);
HSD_LObj* HSD_LObjLoadDesc(GSlightLightDesc*);
void HSD_LObjReqAnimAll(HSD_LObj*, f32);
void HSD_LObjAnimAll(HSD_LObj*);
void HSD_LObjReqAnim(HSD_LObj*, f32);
void HSD_LObjAnim(HSD_LObj*);
void HSD_LObjRemoveAnimAll(HSD_LObj*);
void HSD_LObjAddAnimAll(HSD_LObj*, void*);
void HSD_LObjSetPosition(HSD_LObj*, f32*);
void* HSD_LObjGetPosition(HSD_LObj*, f32*);
void HSD_LObjSetInterest(HSD_LObj*, f32*);
void* HSD_LObjGetInterest(HSD_LObj*, f32*);
u32 HSD_LObjGetFlags(HSD_LObj*);
void HSD_LObjSetFlags(HSD_LObj*, u32);
void HSD_LObjClearFlags(HSD_LObj*, u32);
void HSD_LObjSetColor(HSD_LObj*, GXColor);
void HSD_LObjGetColor(HSD_LObj*, GXColor*);
}

static GSlight* _lightStructList;
static u32 _lightStructCount;
static f32 _frameCount;

static void _lightPreUpdate(f32 dt);
static void _lightPostUpdate(f32 dt);

static inline f32 HSD_AObjGetEndFrame(HSD_AObj* aobj)
{
    if (aobj == 0) {
        __assert("aobj.h", 0xAC, "aobj");
    }
    return aobj->end_frame;
}

static inline GSlight* _lightGetFree(void)
{
    GSlight* light = _lightStructList;
    u32 i;

    for (i = 0; i < _lightStructCount; i++, light++) {
        if (light->used == 0) {
            return light;
        }
    }
    return 0;
}

static inline int _objRefDec(HSD_ObjHeader* obj)
{
    u16 ref_count = obj->ref_count;
    int ret = ref_count == (u16)-1;

    if (ret) {
        return ret;
    }
    obj->ref_count = ref_count - 1;
    return ref_count == 0;
}

static inline void _lightUnref(HSD_LObj* lobj)
{
    HSD_ObjHeader* obj = (HSD_ObjHeader*)lobj;

    if (obj == 0) {
        return;
    }
    if (_objRefDec(obj)) {
        if (obj != 0) {
            ((void (*)(void*))obj->class_info[0x30 / 4])(obj);
            ((void (*)(void*))obj->class_info[0x34 / 4])(obj);
        }
    }
}

void lightGetFrameCount(HSD_AObj* aobj)
{
    _frameCount = 1.0f + HSD_AObjGetEndFrame(aobj);
}

extern "C" {

void GSlightInit(u32 count)
{
    GSgfxRenderModule module = { 0, _lightPreUpdate, 0, 0, _lightPostUpdate, 0, 0xB29A48E1 };
    u32 i;

    _lightStructCount = count;
    _lightStructList = (GSlight*)GSmemAlloc(count * sizeof(GSlight));
    if (_lightStructList != 0) {
        for (i = 0; i < _lightStructCount; i++) {
            _lightStructList[i].used = 0;
        }
        GSgfxRenderModuleRegister(4, &module, 0);
    }
}

GSlight* GSlightCreate(void)
{
    GSlight* light = _lightGetFree();

    if (light == 0) {
        return 0;
    }
    memset(light, 0, sizeof(GSlight));
    light->positionDesc.class_name = 0;
    light->positionDesc.x = 0.0f;
    light->positionDesc.y = 0.0f;
    light->positionDesc.z = 0.0f;
    light->positionDesc.robjdesc = 0;
    light->interestDesc.class_name = 0;
    light->interestDesc.x = 0.0f;
    light->interestDesc.y = 0.0f;
    light->interestDesc.z = 0.0f;
    light->interestDesc.robjdesc = 0;
    light->cutoff = 16.0f;
    light->lightDesc.class_name = 0;
    light->lightDesc.next = 0;
    light->lightDesc.flags = 4;
    light->lightDesc.attnflags = 0;
    light->lightDesc.color.r = 0x80;
    light->lightDesc.color.g = 0x80;
    light->lightDesc.color.b = 0x80;
    light->lightDesc.color.a = 0;
    light->lightDesc.position = &light->positionDesc;
    light->lightDesc.interest = &light->interestDesc;
    light->lightDesc.u = &light->cutoff;
    light->lobj = HSD_LObjLoadDesc(&light->lightDesc);
    light->used = 1;
    light->active = 0;
    return light;
}

void GSlightSetAnimIndex(GSlight* light, u32 index);

GSlight* GSlightLoad(GSlightDesc* desc)
{
    GSlight* light = _lightGetFree();

    if (light == 0) {
        return 0;
    }
    memset(light, 0, sizeof(GSlight));
    light->desc = desc;
    light->lobj = HSD_LObjLoadDesc(light->desc->lightDesc);
    light->used = 1;
    light->active = 0;
    light->animating = 0;
    if (light->desc->anims != 0) {
        light->canAnimate = 1;
        light->rate = 1.0f;
        light->animType = 1;
        light->ended = 0;
        for (light->animCount = 0; light->desc->anims[light->animCount] != 0; light->animCount++) {
        }
        GSlightSetAnimIndex(light, 0);
    } else {
        light->canAnimate = 0;
    }
    return light;
}

void GSlightFree(GSlight* light)
{
    _lightUnref(light->lobj);
    light->active = 0;
    light->used = 0;
}

void GSlightSetType(GSlight* light, s32 type)
{
    HSD_LObjClearFlags(light->lobj, 3);
    switch (type) {
    case 0:
        HSD_LObjSetFlags(light->lobj, 0);
        break;
    case 1:
        HSD_LObjSetFlags(light->lobj, 1);
        break;
    case 2:
        HSD_LObjSetFlags(light->lobj, 2);
        break;
    case 3:
        HSD_LObjSetFlags(light->lobj, 3);
        break;
    }
    light->type = type;
}

void GSlightSetColor(GSlight* light, const GXColor* color)
{
    GXColor c;

    c.r = color->r;
    c.g = color->g;
    c.b = color->b;
    c.a = color->a;
    HSD_LObjSetColor(light->lobj, c);
}

void GSlightSetPosition(GSlight* light, f32* position)
{
    HSD_LObjSetPosition(light->lobj, position);
}

void GSlightSetTarget(GSlight* light, f32* target)
{
    HSD_LObjSetInterest(light->lobj, target);
}

void GSlightSetActive(GSlight* light, u8 active)
{
    light->active = active;
}

void GSlightGetColor(GSlight* light, GXColor* color)
{
    if (color != 0) {
        HSD_LObjGetColor(light->lobj, color);
    }
}

s32 GSlightGetType(GSlight* light)
{
    switch (HSD_LObjGetFlags(light->lobj) & 3) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    default:
        return 0xFF;
    }
}

bool GSlightGetPosition(GSlight* light, f32* position)
{
    return HSD_LObjGetPosition(light->lobj, position) != 0;
}

void GSlightGetTarget(GSlight* light, f32* target)
{
    HSD_LObjGetInterest(light->lobj, target);
}

u8 GSlightGetActive(GSlight* light)
{
    return light->active;
}

u8 GSlightCanAnimate(GSlight* light)
{
    return light->canAnimate;
}

void GSlightSetAnimFrame(GSlight* light, f32 frame);

void GSlightSetAnimIndex(GSlight* light, u32 index)
{
    if (light->canAnimate) {
        HSD_LObjRemoveAnimAll(light->lobj);
        if (index <= light->animCount) {
            light->animIndex = index;
            HSD_LObjAddAnimAll(light->lobj, light->desc->anims[light->animIndex]);
            HSD_LObjReqAnimAll(light->lobj, 0.0f);
            _frameCount = 0.0f;
            HSD_ForeachAnim(light->lobj, 7, 0xFFFF, lightGetFrameCount, 0);
            light->frameCount = _frameCount;
            GSlightSetAnimFrame(light, 0.0f);
        }
    }
}

void GSlightSetAnimRate(GSlight* light, f32 rate)
{
    if (light->canAnimate) {
        if (GSgfxVideoGetVsyncRate() == 50) {
            rate *= 1.2f;
        }
        light->rate = rate;
        HSD_ForeachAnim(light->lobj, 7, 0xFFFF, HSD_AObjSetRate, 1, light->rate);
    }
}

void GSlightSetAnimFrame(GSlight* light, f32 frame)
{
    if (light->canAnimate) {
        light->frame = frame;
        HSD_ForeachAnim(light->lobj, 7, 0xFFFF, HSD_AObjSetRate, 1, 0.0f);
        HSD_LObjReqAnim(light->lobj, light->frame);
        HSD_LObjAnim(light->lobj);
        HSD_ForeachAnim(light->lobj, 7, 0xFFFF, HSD_AObjSetRate, 1, light->rate);
    }
}

void GSlightSetAnimType(GSlight* light, s32 type)
{
    light->animType = type;
}

void GSlightStartAnimation(GSlight* light)
{
    if (light->canAnimate) {
        light->animating = 1;
        light->ended = 0;
        light->direction = 1;
    }
}

void GSlightStopAnimation(GSlight* light)
{
    light->animating = 0;
}

u8 GSlightHasAnimationEnded(GSlight* light)
{
    return light->ended;
}

void GSlightPushState(GSlight* light, GSlightState* state)
{
    state->active = light->active;
    state->animating = light->animating;
    HSD_LObjGetPosition(light->lobj, state->position);
    HSD_LObjGetInterest(light->lobj, state->interest);
    state->animIndex = light->animIndex;
    state->frame = light->frame;
    state->rate = light->rate;
    state->animType = light->animType;
    state->ended = light->ended;
    state->direction = light->direction;
}

void GSlightPopState(GSlight* light, GSlightState* state)
{
    state->active = light->active;
    HSD_LObjSetPosition(light->lobj, state->position);
    switch (GSlightGetType(light)) {
    case 2:
    case 3:
        HSD_LObjSetInterest(light->lobj, state->interest);
        break;
    }
    GSlightSetAnimIndex(light, state->animIndex);
    GSlightSetAnimFrame(light, state->frame);
    GSlightSetAnimRate(light, state->rate);
    light->animType = state->animType;
    light->ended = state->ended;
    light->direction = state->direction;
    if (light->animating) {
        GSlightStartAnimation(light);
    }
}

}

static void _lightPreUpdate(f32 dt)
{
    u32 i;
    GSlight* light;

    for (i = 0; i < _lightStructCount; i++) {
        light = &_lightStructList[i];
        if (light->used == 1 && light->animating == 1) {
            HSD_LObjReqAnimAll(light->lobj, light->frame);
            HSD_LObjAnimAll(light->lobj);
        }
    }
}

static void _lightPostUpdate(f32 dt)
{
    u32 i;
    GSlight* light;
    f32 end;
    f32 step;
    s32 type;

    for (i = 0; i < _lightStructCount; i++) {
        light = &_lightStructList[i];
        if (light->used == 1 && light->animating == 1) {
            step = light->rate * dt;
            end = light->frameCount - 1.0f;
            type = light->animType;
            if (light->direction == -1) {
                light->frame -= step;
            } else if (light->direction == 1) {
                light->frame += step;
            }
            switch (type) {
            case 0:
                if (light->frame >= end - 0.1f) {
                    light->ended = 1;
                    light->direction = 0;
                    light->frame = end - 0.1f;
                }
                break;
            case 1:
                if (light->frame >= end) {
                    light->frame -= end;
                }
                break;
            case 2:
                if (light->frame >= end) {
                    light->direction = -1;
                } else if (light->frame <= 0.0f) {
                    light->direction = 1;
                }
                break;
            }
        }
    }
}

static inline s32 _lightGetFirstActive(void)
{
    GSlight* light = _lightStructList;
    u32 i;

    for (i = 0; i < _lightStructCount; light++, i++) {
        if (light->used == 1 && light->active != 0) {
            return i;
        }
    }
    return -1;
}

extern "C" {

void GSlightDeleteCurrentAll(void);

void GSlightSetupLights(HSD_CObj* cobj)
{
    GSlight* prev;
    s32 first;
    u32 i;
    GSlight* light;

    GSlightDeleteCurrentAll();
    first = _lightGetFirstActive();
    if (first != -1) {
        prev = &_lightStructList[first];
        for (i = first + 1; i < _lightStructCount; i++) {
            light = &_lightStructList[i];
            if (light->used == 1 && light->active != 0) {
                *(HSD_LObj**)((u8*)prev->lobj + 0xC) = light->lobj;
                prev = light;
            }
        }
        *(HSD_LObj**)((u8*)prev->lobj + 0xC) = 0;
        HSD_LObjAddCurrentAll(_lightStructList[first].lobj);
    }
    HSD_LObjSetupInit(cobj);
}

void GSlightDeleteCurrentAll(void)
{
    HSD_LObjDeleteCurrentAll(0);
}

}
