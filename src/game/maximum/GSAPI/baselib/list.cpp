

#include <dolphin/types.h>

#pragma pool_strings off


void __assert(const char* file, s32 line, const char* expr);

typedef struct HSD_ObjAllocData {
    u8 unk0[0x2C];
} HSD_ObjAllocData;

typedef struct HSD_SList {
    struct HSD_SList* next;
    void* data;
} HSD_SList;

void* GSmemGetSysdolAllocator(s32 size);
s32 GSmemGetFreePool(void* pool);
void* GSmemAllocPool(void* pool);
u8 GSmemIsRegistrationPool(void* pool, void* ptr);
void GSmemFreePool(void* pool, void* ptr);
void* HSD_ObjAlloc(HSD_ObjAllocData* data);
void HSD_ObjFree(HSD_ObjAllocData* data, void* obj);
void HSD_ObjAllocInit(HSD_ObjAllocData* data, u32 size, u32 align);

static HSD_ObjAllocData s_alloc_data;
static HSD_ObjAllocData d_alloc_data;

void HSD_ListInitAllocData(void) {
    HSD_ObjAllocInit(&s_alloc_data, sizeof(HSD_SList), 4);
    HSD_ObjAllocInit(&d_alloc_data, 0xC, 4);
}

HSD_ObjAllocData* HSD_SListGetAllocData(void) { return &s_alloc_data; }

HSD_ObjAllocData* HSD_DListGetAllocData(void) { return &d_alloc_data; }

HSD_SList* HSD_SListAlloc(void) {
    HSD_SList* list;
    void* pool = GSmemGetSysdolAllocator(8);
    if (pool != NULL && GSmemGetFreePool(pool) != 0) {
        list = (HSD_SList*)GSmemAllocPool(pool);
        if (list == NULL) {
            __assert("list.c", 88, "list");
        }
        return list;
    }
    list = (HSD_SList*)HSD_ObjAlloc(&s_alloc_data);
    if (list == NULL) {
        __assert("list.c", 96, "list");
    }
    memset(list, 0, sizeof(HSD_SList));
    return list;
}

HSD_SList* HSD_SListPrepend(HSD_SList* list, void* data) {
    HSD_SList* prev;
    prev = HSD_SListAlloc();
    prev->data = data;
    if (prev == NULL) {
        __assert("list.c", 231, "prev");
    }
    prev->next = list;
    return prev;
}



HSD_SList* HSD_SListAllocAndPrepend(HSD_SList* list, void* data) {
    HSD_SList* prev = (HSD_SList*)HSD_ObjAlloc(&s_alloc_data);
    if (prev == NULL) {
        __assert("list.c", 200, "prev");
    }
    prev->data = data;
    prev->next = list;
    return prev;
}

HSD_SList* HSD_SListRemove(HSD_SList* list) {
    void* pool;
    HSD_SList* next;
    if (list != NULL) {
        next = list->next;
        pool = GSmemGetSysdolAllocator(8);
        if (pool != NULL && GSmemIsRegistrationPool(pool, list)) {
            GSmemFreePool(pool, list);
        } else {
            HSD_ObjFree(&s_alloc_data, list);
        }
        return next;
    }
    return 0;
}
