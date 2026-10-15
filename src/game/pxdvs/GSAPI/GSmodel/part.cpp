#include <dolphin/types.h>

struct _HSD_JObj;

struct _GSmodel {
    u32 flags;
    u8 unk4[8];
    _HSD_JObj* jobj;
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
 // Models with an attached null have one extra joint.
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
