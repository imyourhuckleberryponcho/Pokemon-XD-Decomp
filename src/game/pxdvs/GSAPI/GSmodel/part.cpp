#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gsmodelview.h>

struct _HSD_JObj;

struct _GSmodel {
    u32 flags;
    _GSmodel* next;
    void* set;
    _HSD_JObj* jobj;
    void* blendJObj;
    void* blendDest;
    f32 position[3];
    f32 rotation[3];
    f32 scale[3];
    GSmodelBoundView bound;
    void* camera;
    u16 flags2;
    u16 token;
    u8 layers[8];
    u32 animCount;
    u32 texAnimCount;
    s32 animType;
    u32 animIndex;
    f32 animRate;
    f32 animFrame;
    f32 animReqFrame;
    f32 animEndFrame;
    void* animAObj;
    s32 blendAnimType;
    u32 blendAnimIndex;
    f32 blendAnimRate;
    f32 blendAnimFrame;
    f32 blendAnimReqFrame;
    f32 blendAnimEndFrame;
    void* blendAnimAObj;
    s32 texAnimType;
    u32 texAnimIndex;
    f32 texAnimRate;
    f32 texAnimFrame;
    f32 texAnimReqFrame;
    f32 texAnimEndFrame;
    void* texAnimAObj;
    GSmodelPartMixView partMix[12];
    f32 blendFactor;
    u8 animDirty;
    u8 texAnimDirty;
    u8 unk21E[2];
    void* animEndedCallback;
    void* animEndedCallbackArg;
    GSmodelPartAnimView partAnim[16];
    s32 attachMode;
    _GSmodel* attachModel;
    u32 attachIndex;
    f32 attachPosition[3];
    f32 attachRotation[3];
    f32 attachScale[3];
    void* particleBank;
    u32 particleAttachMode;
    void* materials;
    u32 materialCount;
    u32 shadowSurfaceCount;
    void* shadowSurfaces;
    void* shadowLight;
    f32 groundPlane;
    GCuptr unk5F8;
    f32 unk5FC;
    u8 unk600[4];
    f32 unk604;
    u8 unk608[4];
    f32 unk60C;
    u16 unk610;
    u8 unk612;
    u8 unk613;
    GCuptr unk614;
    GCuptr unk618;
    GCuptr unk61C;
    s32 vertexCount;
    s32 polygonCount;
};

struct GSpart {
    u8 unk0[2];
    s16 index;
    _GSmodel* model;
    _HSD_JObj* jobj;
};

_HSD_JObj* modelGetRenderJObj(_GSmodel* model);

extern "C" {
void HSD_JObjWalkTree(_HSD_JObj* jobj, void (*callback)(_HSD_JObj*, void**, int), void** arg);
_HSD_JObj* GSpartGetJObjPtr(_HSD_JObj* root, s32 index);
GSpart* GSpartCreate(void);
}

static u32 _modelCurPartIdx;
static u32 _modelDestPartIdx;
static _HSD_JObj* _modelFoundJObj;

static void _modelFindJObj(_HSD_JObj* jobj, void** arg, int);

extern "C" {

s32 GSmodelGetPartCount(_GSmodel* model) {
    _modelCurPartIdx = 0;
    _modelDestPartIdx = -1;
    HSD_JObjWalkTree(model->jobj, _modelFindJObj, NULL);
    if ((model->flags & 0x20000) == 0x20000) {
        _modelCurPartIdx--;
    }
    return _modelCurPartIdx;
}

GSpart* GSmodelGetPart(_GSmodel* model, s32 index) {
    s32 jobjIndex = index;
    _HSD_JObj* jobj;
    GSpart* part;

    if ((model->flags & 0x20000) == 0x20000) {
        jobjIndex++;
    }
    jobj = GSpartGetJObjPtr(modelGetRenderJObj(model), jobjIndex);
    if (jobj == NULL) {
        return NULL;
    }
    part = GSpartCreate();
    if (part == NULL) {
        return NULL;
    }
    part->model = model;
    part->jobj = jobj;
    part->index = index;
    return part;
}

}

static void _modelFindJObj(_HSD_JObj* jobj, void** arg, int) {
    if (_modelCurPartIdx++ == _modelDestPartIdx) {
        _modelFoundJObj = jobj;
    }
}
