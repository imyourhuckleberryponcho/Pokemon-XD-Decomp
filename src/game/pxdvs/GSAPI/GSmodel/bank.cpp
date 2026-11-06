#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/gsmodelview.h>

struct ModelBank;

struct _GSmodel {
    u32 flags;
    _GSmodel* next;
    u32 childFlags;
    void* jobj;
    void* blendJObj;
    void* blendDest;
    f32 position[3];
    f32 rotation[3];
    f32 scale[3];
    GSmodelBoundView bound;
    void* camera;
    u16 flags2;
    u16 unk62;
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

struct ModelBank {
    u32 flags;
    ModelBank* next;
    _GSmodel models[8];
};

extern "C" {
static ModelBank* _modelBankList;
_GSmodel* _modelTopPtr;
ModelBank* GSmemAllocClr(u32 size);
void GSmemFree(void* ptr);
void* memset(void* ptr, int value, u32 size);
}

static inline void bankInitialize(ModelBank* bank) {
    bank->flags = 2;
    bank->next = 0;
    for (int i = 0; i < 8; ++i) {
        bank->models[i].flags = 0;
        bank->models[i].unk62 = 0;
        bank->models[i].next = 0;
    }
}

static inline u8 bankContains(ModelBank* head, ModelBank* bank) {
    for (ModelBank* cursor = head; cursor; cursor = cursor->next) {
        if (cursor == bank) return 1;
    }
    return 0;
}
static inline ModelBank* bankFindModel(_GSmodel* model) {
    for (ModelBank* bank = _modelBankList; bank; bank = bank->next) {
        if (!(bank->flags & 2)) {
            for (int i = 0; i < 8; ++i) {
                if (&bank->models[i] == model) return bank;
            }
        }
    }
    return 0;
}
static inline _GSmodel* bankFindFree(ModelBank* bank) {
    for (int i = 0; i < 8; ++i) {
        _GSmodel* model = &bank->models[i];
        if (!(model->flags & 1)) return model;
    }
    return 0;
}
static inline void bankUpdateFlags(ModelBank* bank) {
    int usedCount = 0;
    int freeCount = 0;
    bank->flags &= ~6;
    for (int i = 0; i < 8; ++i) {
        u32 flags = bank->models[i].flags & 1;
        if (flags) ++usedCount;
        if (!flags) ++freeCount;
    }
    if (usedCount == 8) bank->flags |= 4;
    else if (freeCount == 8) bank->flags |= 2;
}
static inline void bankRemove(ModelBank* bank) {
    ModelBank* head = _modelBankList;
    if (bankContains(head, bank)) {
        if (head == bank) {
            bank->flags &= ~1;
            _modelBankList = bank->next;
        } else {
            while (head != 0) {
                ModelBank* next = head->next;
                if (next == bank) {
                    head->next = bank->next;
                    bank->flags &= ~1;
                    break;
                }
                head = next;
            }
        }
    }
}
void modelBankReleaseModel(_GSmodel* model) {
    ModelBank* bank;
    ModelBank* bankCursor;
    _GSmodel* modelCursor;

    bank = bankFindModel(model);

    if (_modelTopPtr == model) {
        _modelTopPtr = model->next;
    } else {
        modelCursor = _modelTopPtr;
        while (modelCursor != 0 && modelCursor->next != model) {
            modelCursor = modelCursor->next;
        }
        modelCursor->next = model->next;
    }

    model->flags = 0;
    model->next = 0;
    bankUpdateFlags(bank);

    bankCursor = _modelBankList;
    while (bankCursor != 0) {
        if ((bankCursor->flags & 2) != 0 && bankCursor->next != 0) {
            bankRemove(bankCursor);
            GSmemFree(bankCursor);
            return;
        }
        bankCursor = bankCursor->next;
    }
}

_GSmodel* modelBankGetFreeModel(void) {
    ModelBank* bank = _modelBankList;
    _GSmodel* model;
    _GSmodel* cursor;
    ModelBank* newBank;

    while (bank != 0 && (bank->flags & 4) != 0) {
        bank = bank->next;
    }
    if (bank == 0) {
        newBank = GSmemAllocClr(sizeof(ModelBank));
        if (newBank == 0) {
            newBank = 0;
        } else {
            bankInitialize(newBank);
        }
        bank = newBank;
        if (newBank == 0) return 0;
        if (bankContains(_modelBankList, newBank) != 1) {
            newBank->next = _modelBankList;
            _modelBankList = newBank;
            newBank->flags |= 1;
        }
    }

    model = bankFindFree(bank);
    memset(model, 0, sizeof(*model));
    model->flags = 1;

    bankUpdateFlags(bank);

    model->next = 0;
    if (_modelTopPtr == 0) {
        _modelTopPtr = model;
    } else {
        cursor = _modelTopPtr;
        while (cursor->next != 0) {
            cursor = cursor->next;
        }
        cursor->next = model;
    }
    return model;
}

void modelBankInit(void) {
    ModelBank* head;
    ModelBank* bank = GSmemAllocClr(sizeof(ModelBank));

    if (bank == 0) {
        bank = 0;
    } else {
        bankInitialize(bank);
    }
    head = _modelBankList;
    if (bankContains(head, bank) != 1) {
        bank->next = head;
        _modelBankList = bank;
        bank->flags |= 1;
    }
}

