

#include <dolphin/types.h>

#pragma pool_strings off

void __assert(const char* file, s32 line, const char* expr);
void* HSD_Alloc(u32 size);
void HSD_Free(void* ptr);
s32 HSD_GetNbBits(u32 mask);

typedef struct HSD_ObjAllocData {
    u8 limit_enabled : 1;
    u8 flags : 7;
    u8 unk1[7];
    u32 used;
    u32 free;
    u32 peak;
    u32 num_limit;
    u32 heap_limit_size;
    u32 heap_limit_num;
    u32 size;
    u32 align;
    struct HSD_ObjAllocData* next;
} HSD_ObjAllocData;

static struct {
    void* curr;
    void* top;
    u32 remain;
    u32 size;
} obj_heap = { 0, 0, -1, -1 };

static HSD_ObjAllocData* alloc_datas;

void HSD_ObjSetHeap(u32 size, void* ptr) {
    obj_heap.curr = obj_heap.top = ptr;
    obj_heap.remain = obj_heap.size = size;
}

void* HSD_ObjAlloc(HSD_ObjAllocData* data) {
    if (data->limit_enabled && data->used >= data->num_limit) {
        return NULL;
    }
    data->used++;
    if (data->used > data->peak) {
        data->peak = data->used;
    }
    return HSD_Alloc(data->size);
}

void HSD_ObjFree(HSD_ObjAllocData* data, void* obj) {
    data->used--;
    HSD_Free(obj);
}

void HSD_ObjAllocInit(HSD_ObjAllocData* data, u32 size, u32 align) {
    HSD_ObjAllocData** p;

    if (data == NULL) {
        __assert("objalloc.c", 381, "data");
    }
    if (data != NULL) {
        HSD_ObjAllocData* cur;
        for (p = &alloc_datas; (cur = *p) != NULL;) {
            if (cur == data) {
                *p = cur->next;
            } else {
                p = &cur->next;
            }
        }
    } else {
        alloc_datas = NULL;
    }
    memset(data, 0, sizeof(HSD_ObjAllocData));
    data->num_limit = -1;
    data->heap_limit_size = 0;
    data->heap_limit_num = -1;
    if (!(align <= 32)) {
        __assert("objalloc.c", 392, "align <= 32");
    }
    if (!(HSD_GetNbBits(align) == 1)) {
        __assert("objalloc.c", 393, "HSD_GetNbBits(align) == 1");
    }
    data->align = align;
    data->size = (size + data->align - 1) & ~(data->align - 1);
    data->next = alloc_datas;
    alloc_datas = data;
}

void _HSD_ObjAllocForgetMemory(void) { alloc_datas = NULL; }
